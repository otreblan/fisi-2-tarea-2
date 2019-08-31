# New macro definitions {{{

# This macro checks for a program and exits if not found {{{

# AC_CHECK_CHECK_PROG([variable], [program-name])
AC_DEFUN(AC_CHECK_CHECK_PROG,[
	AC_CHECK_PROG([$1], [$2], [$2], [])
	if test -z $$1
	then
		AC_MSG_ERROR([$2 not found.])
	fi
])

#}}}

#}}}

AC_INIT([fisi2], [0.0.1])
#AC_CONFIG_AUX_DIR([aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Language
AC_LANG([C++])

# Checking if some programs are installed{{{
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_CHECK_CHECK_PROG([ASCII], [asciidoctor])

# }}}

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
	doc/Makefile
])

AC_OUTPUT
