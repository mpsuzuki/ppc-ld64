#ifndef LD_CSTRINGHASH_HPP
#define LD_CSTRINGHASH_HPP

#include <cstring>

struct CStringEquals {
    bool operator()(const char* left, const char* right) const { return (strcmp(left, right) == 0); }
};

struct CStringHash {
#if __cplusplus >= 201103L
    size_t operator()(const char* s) const noexcept {
#else
    size_t operator()(const char* s) const {
#endif
        size_t h = 0;
        while (*s) {
            h = h * 131 + static_cast<unsigned char>(*s++);
        }
        return h;
    }
};

#if defined(_LIBCPP_VERSION) && (_LIBCPP_VERSION > 1000)
 #define HAS_CXX11_LIB 1
#elif defined(__GLIBCXX__) && (__GLIBCXX__ > 20130322)
 #define HAS_CXX11_LIB 1
#else
 #define HAS_CXX11_LIB 0
#endif

#if HAS_CXX11_LIB
  #include <map>
  #include <unordered_map>
#else
  #include <ext/hash_map>
#endif

// A tiny & simple function to calculate a hash value from a string.
template <typename V>
class CStringMap {
public:
#if HAS_CXX11_LIB
    using MapT = std::unordered_map<const char*, V, CStringHash, CStringEquals>;
    using iterator = typename MapT::iterator;
    using const_iterator = typename MapT::const_iterator;
    using value_type = typename MapT::value_type;
    using size_type = typename MapT::size_type;
#else
    typedef __gnu_cxx::hash_map<const char*, V, __gnu_cxx::hash<const char*>, CStringEquals> MapT;
    typedef typename MapT::iterator iterator;
    typedef typename MapT::const_iterator const_iterator;
    typedef typename MapT::value_type value_type;
    typedef typename MapT::size_type size_type;
#endif

    // for backward compatibility name of method is lined to C++03 GNU extension.
    void resize(size_t n) {
#if HAS_CXX11_LIB
        map_.reserve(n);
#else
        map_.resize(n);
#endif
    }

    V& operator[](const char* key) { return map_[key]; }
    typename MapT::iterator begin() { return map_.begin(); }
    typename MapT::iterator end() { return map_.end(); }
    typename MapT::iterator find(const char* key) { return map_.find(key); }
    void erase(typename MapT::iterator it) { map_.erase(it); }
    void erase(const char* nm) { map_.erase(nm); }
    void insert(const std::pair<const char*, V>& p) { map_.insert(p); }
    size_t size() { return map_.size(); }

private:
    MapT map_;
};

#if HAS_CXX11_LIB
  #include <set>
  #include <unordered_set>
  using CStringSet = std::unordered_set<const char*, CStringHash, CStringEquals>;
#else
  #include <ext/hash_set>
  typedef __gnu_cxx::hash_set<const char*, __gnu_cxx::hash<const char*>, CStringEquals> CStringSet;
#endif

#endif // LD_CSTRINGHASH_HPP
