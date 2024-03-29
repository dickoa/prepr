dnl Process this file with autoconf to produce a configure script.
dnl GDAL stuff largely copied from sf, (c) Edzer Pebesma
AC_INIT
AC_CONFIG_SRCDIR([src/prepr.cpp])

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi

RBIN="${R_HOME}/bin/R"
RSCRIPT="${R_HOME}/bin/Rscript"
RVER=`"${RSCRIPT}" -e 'writeLines(paste(sep=".", base::version$major, base::version$minor))'`

RVER_MAJOR=`echo ${RVER} | cut  -f1 -d"."`
RVER_MINOR=`echo ${RVER} | cut  -f2 -d"."`
RVER_PATCH=`echo ${RVER} | cut  -f3 -d"."`

if test [$RVER_MAJOR = "development"]; then
    CXX17=`"${RBIN}" CMD config CXX17`
    CXX17STD=`"${RBIN}" CMD config CXX17STD`
else
    if test [$RVER_MAJOR -lt 3] -o [$RVER_MAJOR -eq 3 -a $RVER_MINOR -lt 3]; then
        AC_MSG_ERROR([sf is not compatible with R versions before 3.3.0])
    else
        if test [$RVER_MINOR -eq 3]; then
            CXX17=`"${RBIN}" CMD config CXX1X`
            CXX17STD=`"${RBIN}" CMD config CXX1XSTD`
        else
            CXX17=`"${RBIN}" CMD config CXX14`
            CXX17STD=`"${RBIN}" CMD config CXX14STD`
        fi
    fi
fi

# pick all flags for testing from R
: ${CC=`"${RBIN}" CMD config CC`}
: ${CXX=${CXX17} ${CXX17STD}}
: ${CFLAGS=`"${RBIN}" CMD config CFLAGS`}
: ${CXXFLAGS=`"${RBIN}" CMD config CXXFLAGS`}
: ${LDFLAGS=`"${RBIN}" CMD config LDFLAGS`}
AC_MSG_NOTICE([CC: ${CC}])
AC_MSG_NOTICE([CXX: ${CXX}])

#GDAL
GDAL_CONFIG="gdal-config"

GDAL_CONFIG_SET="no"

AC_ARG_WITH([gdal-config],
    AS_HELP_STRING([--with-gdal-config=GDAL_CONFIG],[the location of gdal-config]),
           [gdal_config=$withval])
if test [ -n "$gdal_config" ] ; then
    GDAL_CONFIG_SET="yes"
    AC_SUBST([GDAL_CONFIG],["${gdal_config}"])
    AC_MSG_NOTICE(gdal-config set to $GDAL_CONFIG)
fi

if test ["$GDAL_CONFIG_SET" = "no"] ; then
  AC_PATH_PROG([GDAL_CONFIG], ["$GDAL_CONFIG"],["no"])
  if test ["$GDAL_CONFIG" = "no"] ; then
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([gdal-config not found or not executable.])
  fi
else
  AC_MSG_CHECKING(gdal-config exists)
  if test -r "${GDAL_CONFIG}"; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([gdal-config not found - configure argument error.])
  fi
  AC_MSG_CHECKING(gdal-config executable)
  if test -x "${GDAL_CONFIG}"; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([gdal-config not executable.])
  fi
fi

AC_MSG_CHECKING(gdal-config usability)
if test `${GDAL_CONFIG} --version`;
then
	GDAL_CXXFLAGS=`${GDAL_CONFIG} --cflags`
	GDAL_VERSION=`${GDAL_CONFIG} --version`
	GDAL_LIBS=`${GDAL_CONFIG} --libs`
	GDAL_DEP_LIBS=`${GDAL_CONFIG} --dep-libs`
	GDAL_DATADIR=`${GDAL_CONFIG} --datadir`
	AC_MSG_RESULT(yes)
else
	AC_MSG_RESULT(no)
	echo "Error: gdal-config not found"
	echo "The gdal-config script distributed with GDAL could not be found."
	echo "If you have not installed the GDAL libraries, you can"
	echo "download the source from  http://www.gdal.org/"
	echo "If you have installed the GDAL libraries, then make sure that"
	echo "gdal-config is in your path. Try typing gdal-config at a"
	echo "shell prompt and see if it runs. If not, use:"
	echo " --configure-args='--with-gdal-config=/usr/local/bin/gdal-config'"
	echo "with appropriate values for your installation."
	echo ""

	exit 1
fi

AC_MSG_NOTICE([GDAL: ${GDAL_VERSION}])
AC_MSG_CHECKING([GDAL version >= 2.0.1])

GDAL_MAJ_VER=`echo $GDAL_VERSION | cut -d "." -f1`
if test ${GDAL_MAJ_VER} -lt 2 ; then
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([prepr is not compatible with GDAL versions below 2.0.1])
else
   AC_MSG_RESULT(yes)
fi

AC_SUBST([PKG_CXXFLAGS], ["${GDAL_CXXFLAGS}"])
AC_SUBST([PKG_LIBS], ["${GDAL_LIBS}"])

#
# CGAL flags
#
[CGAL_CXXFLAGS="-O3 -DNDEBUG -frounding-math"]
AC_SUBST(CGAL_CXXFLAGS)

#
# ADD GMP/MPFR
#
AC_CHECK_LIB(gmp, __gmpz_init, ,
    [AC_MSG_ERROR([GNU MP not found!])])

AC_CHECK_LIB(mpfr, mpfr_init, ,
    [AC_MSG_ERROR([MPFR Library not found!])])

AC_SUBST([PKG_LIBS], ["${PKG_LIBS} -lgmpxx -lgmp -lmpfr -lpthread"])
AC_SUBST([PKG_CXXFLAGS], ["${PKG_CXXFLAGS} ${CGAL_CXXFLAGS} -DCGAL_USE_GMPXX=1"])

#
# concluding substitution
#
AC_MSG_NOTICE([Package CXX flags: ${PKG_CXXFLAGS}])
AC_MSG_NOTICE([Package LIBS: ${PKG_LIBS}])

AC_CONFIG_FILES(src/Makevars)
AC_OUTPUT
