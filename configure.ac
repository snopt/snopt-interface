AC_PREREQ(2.69)
AC_INIT([SNOPT-APIs],[7.2-12-3],[optimizers@ccom.ucsd.edu],[snopt-interfaces])

AC_CONFIG_SRCDIR([src/snoptProblem.cpp])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config/m4])

AC_PREFIX_DEFAULT([`pwd`])

user_CFLAGS=${CFLAGS}
user_CXXFLAGS=${CXXFLAGS}
user_LDFLAGS=${LDFLAGS}

# Libtool
LT_INIT
AC_SUBST([LIBTOOL_DEPS])

# Check compilers.
AC_PROG_INSTALL
AC_PROG_FC
AC_PROG_CC
AC_PROG_CXX

AC_FC_LIBRARY_LDFLAGS
AC_SUBST([FCLIBS])

AC_FC_MODULE_OUTPUT_FLAG([],
  [ case $FC in
      *nagfor* ) FC_MODOUT="-mdir ";;
    esac
  ])
AC_FC_MODULE_FLAG([],
  [ case $FC in
      *nagfor* ) FC_MODINC="-mdir ";;
    esac
  ])

AC_SUBST(FC_MODOUT)
AC_SUBST(FC_MODINC)

dnl ----------------------------------------------------------------------------

# BLAS library.
AC_ARG_WITH([blas],
	    [AS_HELP_STRING([--with-blas=<lib>], [use BLAS library <lib>])],
	    [with_blas=${withval} ], [ blas=no ] )
case $with_blas in
	yes | "" | no) blas=no ;;
	-* | */* | *.a | *.so | *.so.* | *.o)
	  blas=yes; BLAS_LIBS="$with_blas" ;;
	*)
	  blas=yes; BLAS_LIBS="-l$with_blas" ;;
esac
AC_SUBST([blas])
AC_SUBST([BLAS_LIBS])

dnl ----------------------------------------------------------------------------

AC_ARG_WITH([snopt],
	    [AS_HELP_STRING([--with-snopt=/path/to/snopt], [location of SNOPT library])],
	    [snopt_dir=${withval}; ], [ snopt_dir=${libdir}; ] )
AC_SUBST([snopt_dir])

dnl ----------------------------------------------------------------------------

CFLAGS="${user_CFLAGS}"
CXXFLAGS="${user_CXXFLAGS}"
LDFLAGS="${user_LDFLAGS}"

AC_SUBST([CFLAGS])
AC_SUBST([CXXFLAGS])

AC_OUTPUT([Makefile])
