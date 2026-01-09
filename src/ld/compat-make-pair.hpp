#ifndef _COMPAT_MAKE_PAIR_
#define _COMPAT_MAKE_PAIR_

/*
 * ld64-97.17 used 'std::make_pair<t1, t2>(v1, v2)' style,
 * which Apple clang 17.x does not accept anymore.
 *
 * Even in C++98 allows std::make_pair(v1, v2), so,
 * except of deadly outdated C++ compilers, no need to stick
 * original style. Maybe the C++ compilers with no support
 * for std::make_pair(v1, v2) would be unable to compile ld64.
 *
 */

#ifdef USE_MAKE_PAIR_EXPLICIT
# define MAKE_PAIR(t1, t2, v1, v2) std::make_pair<t1, t2>(v1, v2)
#else
# define MAKE_PAIR(t1, t2, v1, v2) std::make_pair(v1, v2)
#endif

#endif
