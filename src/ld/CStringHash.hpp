#ifndef LD_CSTRINGHASH_HPP
#define LD_CSTRINGHASH_HPP

#include <cstring>
#include <unordered_map>

// A tiny & simple function to calculate a hash value from a string.
struct CStringEquals {
    bool operator()(const char* left, const char* right) const { return (strcmp(left, right) == 0); }
};

struct CStringHash {
    size_t operator()(const char* s) const noexcept {
        size_t h = 0;
        while (*s) {
            h = h * 131 + static_cast<unsigned char>(*s++);
        }
        return h;
    }
};

#endif

