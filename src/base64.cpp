#include "base64.h"

const std::string Base64::b64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

inline bool Base64::is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string Base64::encode(const std::string &s) {
    size_t i = 0, j = 0;
    unsigned char char_array_3[3], char_array_4[4];
    std::string ret;

    for (const char &c : s) {
        char_array_3[i++] = c;
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfcu) >> 2u;
            char_array_4[1] = ((char_array_3[0] & 0x03u) << 4u) + ((char_array_3[1] & 0xf0u) >> 4u);
            char_array_4[2] = ((char_array_3[1] & 0x0fu) << 2u) + ((char_array_3[2] & 0xc0u) >> 6u);
            char_array_4[3] = char_array_3[2] & 0x3fu;
            for (i=0; i<4; i++)
                ret += b64_chars[char_array_4[i]];
            i = 0;
        }
    }
    if (i) {
        for (j=i; j<3; j++)
            char_array_3[j] = '\0';
        char_array_4[0] = (char_array_3[0] & 0xfcu) >> 2u;
        char_array_4[1] = ((char_array_3[0] & 0x03u) << 4u) + ((char_array_3[1] & 0xf0u) >> 4u);
        char_array_4[2] = ((char_array_3[1] & 0x0fu) << 2u) + ((char_array_3[2] & 0xc0u) >> 6u);
        for (j=0; j<i+1; j++)
            ret += b64_chars[char_array_4[j]];
        while(i++ < 3)
            ret += '=';
    }
    return ret;
}

std::string Base64::decode(const std::string &s) {
    size_t i = 0, j = 0, k = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
    size_t in_len = s.size();

    while (in_len-- && (s[k] != '=') && is_base64(s[k])) {
        char_array_4[i++] = s[k];
        k++;
        if (i == 4) {
            for (i=0; i<4; i++)
                char_array_4[i] = b64_chars.find(char_array_4[i]) & 0xffu;
            char_array_3[0] = (char_array_4[0] << 2u) + ((char_array_4[1] & 0x30u) >> 4u);
            char_array_3[1] = ((char_array_4[1] & 0xfu) << 4u) + ((char_array_4[2] & 0x3cu) >> 2u);
            char_array_3[2] = ((char_array_4[2] & 0x3u) << 6u) + char_array_4[3];
            for (i=0; i<3; i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    if (i) {
        for (j=0; j<i; j++)
            char_array_4[j] = b64_chars.find(char_array_4[j]) & 0xffu;
        char_array_3[0] = (char_array_4[0] << 2u) + ((char_array_4[1] & 0x30u) >> 4u);
        char_array_3[1] = ((char_array_4[1] & 0xfu) << 4u) + ((char_array_4[2] & 0x3cu) >> 2u);
        for (j=0; j<i-1; j++)
            ret += char_array_3[j];
    }
    return ret;
}

