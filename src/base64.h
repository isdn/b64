#ifndef __BASE64_H
#define __BASE64_H

#include <string>

#ifndef __BASE64_DICTIONARY__
#define __BASE64_DICTIONARY__ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#endif

class Base64 {
public:
    static std::string encode(const std::string &s);
    static std::string decode(const std::string &s);

private:
    static const std::string b64_chars;
    static bool is_base64(unsigned char c);
};

#endif //__BASE64_H

