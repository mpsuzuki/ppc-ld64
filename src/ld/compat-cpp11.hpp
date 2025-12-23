#ifndef _COMPAT_CPP11_
#define _COMPAT_CPP11_

#if __cplusplus >= 201103L
# define MAKE_PAIR(t1, t2, v1, v2) std::make_pair(v1, v2)
#else
# define MAKE_PAIR(t1, t2, v1, v2) std::make_pair<t1, t2>(v1, v2)
#endif

#endif
