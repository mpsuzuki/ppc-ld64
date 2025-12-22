#ifndef _COMPAT_CPP11_
#define _COMPAT_CPP11_

#if __cplusplus >= 201103L
# define MAKE_PAIR(a,b) std::make_pair(a,b)
#else
# define MAKE_PAIR(a,b) std::make_pair<decltype(a), decltype(b)>(a,b)
#endif

#endif
