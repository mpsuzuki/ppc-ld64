AC_PREREQ([2.62])
AC_INIT([ppc-ld64], [0.0.20260109], [https://github.com/mpsuzuki/ppc-ld64/-/issues])

#
# AC_CANONICAL_HOST is expected in future version
#
uname_m=`uname -m`
case "${uname_m}" in
x86_64|amd64)
  # CFLAGS_DEFAULT_TARGET=-Ddefault_is_x86_64
  ;;
i[3-9]86)
  # CFLAGS_DEFAULT_TARGET=-Ddefault_is_i386
  ;;
ppc64|powerpc64)
  # CFLAGS_DEFAULT_TARGET=-Ddefault_is_ppc64
  ;;
ppc|powerpc)
  # CFLAGS_DEFAULT_TARGET=-Ddefault_is_ppc
  ;;
*)
  AC_MSG_WARN([* CPU of this host, ${uname_m}, is unknown for cctool, defaulting to PPC])
  CFLAGS_DEFAULT_TARGET=-Ddefault_is_ppc
  ;;
esac
CFLAGS="${CFLAGS} ${CFLAGS_DEFAULT_TARGET}"
CXXFLAGS="${CXXFLAGS} ${CFLAGS_DEFAULT_TARGET}"

AC_CHECK_PROGS(INSTALL, [ginstall gnu-install install.gnu install installbsd])
AC_SUBST(INSTALL)

AC_PROG_CC
AC_SUBST([CC])
AC_SUBST([CFLAGS])

AC_PROG_CXX
AC_LANG([C++])

AC_MSG_CHECKING([whether ${CXX} ${CXXFLAGS} accepts 'std::make_pair(v1, v2)'])
AC_COMPILE_IFELSE([
    AC_LANG_PROGRAM([
      #include <utility>
    ],[
      int a = 1;
      double b = 2.0;
      auto p = std::make_pair(a, b);
    ])
  ],[
    ac_cv_make_pair_infer=yes
  ],[
    ac_cv_make_pair_infer=no
  ])
AC_MSG_RESULT([${ac_cv_make_pair_infer}])

AC_MSG_CHECKING([whether ${CXX} ${CXXFLAGS} accepts 'std::make_pair<t1, t2>(v1, v2)'])
AC_COMPILE_IFELSE([
    AC_LANG_PROGRAM([
      #include <utility>
    ],[
      int a = 1;
      double b = 2.0;
      auto p = std::make_pair<int, double>(a, b);
    ])
  ],[
    ac_cv_make_pair_explicit=yes
  ],[
    ac_cv_make_pair_explicit=no
  ])
AC_MSG_RESULT([${ac_cv_make_pair_explicit}])

if test "${ac_cv_make_pair_infer}" = yes
then
  CXXFLAGS="${CXXFLAGS} -UUSE_MAKE_PAIR_EXPLICIT"
elif test "${ac_cv_make_pair_explicit}" = yes
then
  AC_MSG_WARN([maybe ${CXX} ${CXXFLAGS} work as pre-C++98 compiler, maybe ld64 cannot be built])
  CXXFLAGS="${CXXFLAGS} -DUSE_MAKE_PAIR_EXPLICIT"
else
  AC_MSG_ERROR([no usable C++ compiler is found])
fi

AC_SUBST([CXX])
AC_SUBST([CXXFLAGS])

AC_ARG_WITH([cctools],[AS_HELP_STRING([--with-cctools],
    [specify dirname of cctools])
  ],[CCTOOLS="${withval}"],[CCTOOLS=./cctools])
AC_SUBST([CCTOOLS])

AC_MSG_CHECKING([whether type of the 2nd argument _NSGetExecutablePath() is uint32_t*])
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM([#include <mach-o/dyld.h>],[
      uint32_t bufSize = 1024;
      _NSGetExecutablePath(NULL, &bufSize);
    ])
  ],[
    AC_MSG_RESULT([yes])
    DEFINE_NS_GET_EXECUTABLE_PATH_BUF_UINT32="-DNS_GET_EXECUTABLE_PATH_BUF_UINT32=1"
  ],[
    AC_MSG_RESULT([no])
    DEFINE_NS_GET_EXECUTABLE_PATH_BUF_UINT32="-UNS_GET_EXECUTABLE_PATH_BUF_UINT32"
  ]
)
AC_SUBST(DEFINE_NS_GET_EXECUTABLE_PATH_BUF_UINT32)


AC_ARG_WITH([lldb],[AS_HELP_STRING([--with-lldb],
    [specify dirname of lldb that has source/Plugins/Process/Utility/libunwind])
  ],[LLDB="${withval}"],[LLDB=./LLDB])
AC_SUBST([LLDB])

AC_ARG_WITH([libunwind],[AS_HELP_STRING([--with-libunwind],
    [specify dirname of libunwind (default is $(LLDB)/source/Plugins/Process/Utility/libunwind])
  ],[UNWIND="${withval}"],[UNWIND='$(LLDB)/source/Plugins/Process/Utility/libunwind/'])
AC_SUBST([UNWIND])

AC_CONFIG_FILES([GNUmakefile])
AC_OUTPUT
