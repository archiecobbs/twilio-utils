#
# twilio-utils - Command line utilities for Twilio users
# 
# Copyright 2013 Archie L. Cobbs <archie.cobbs@gmail.com>
# 
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.
#

AC_INIT([twilio-utils - Command line utilities for Twilio users], [1.1.0], [https://github.com/archiecobbs/twilio-utils], [twilio-utils])
AC_CONFIG_AUX_DIR(scripts)
AM_INIT_AUTOMAKE
dnl AM_MAINTAINER_MODE
AC_PREREQ(2.59)
AC_PREFIX_DEFAULT(/usr)
AC_PROG_MAKE_SET

[CFLAGS="-g -O3 -pipe -Wall -Waggregate-return -Wcast-align -Wchar-subscripts -Wcomment -Wformat -Wimplicit -Wmissing-declarations -Wmissing-prototypes -Wnested-externs -Wno-long-long -Wparentheses -Wpointer-arith -Wredundant-decls -Wreturn-type -Wswitch -Wtrigraphs -Wuninitialized -Wunused -Wwrite-strings -Wshadow -Wstrict-prototypes -Wcast-qual $CFLAGS"]
AC_SUBST(CFLAGS)

# Compile flags for Linux
AC_DEFINE(_GNU_SOURCE, 1, GNU functions)
AC_DEFINE(_BSD_SOURCE, 1, BSD functions)
AC_DEFINE(_XOPEN_SOURCE, 500, XOpen functions)

# Compile flags for Mac OS
AC_DEFINE(_DARWIN_C_SOURCE, 1, MacOS functions)

# Check for required programs
AC_PROG_INSTALL
AC_PROG_CC
AC_PATH_PROGS([XMLSTARLET], [xml xmlstarlet])
[if test -z "${XMLSTARLET}"; then]
    AC_MSG_ERROR([xmlstarlet not found]);
[fi]
AC_PATH_PROG([XSLTPROC], [xsltproc])
[if test -z "${XSLTPROC}"; then]
    AC_MSG_ERROR([xsltproc not found]);
[fi]
AC_PATH_PROG([CURL], [curl])
[if test -z "${CURL}"; then]
    AC_MSG_ERROR([curl not found]);
[fi]
AC_PATH_PROG([ICONV], [iconv])
[if test -z "${ICONV}"; then]
    AC_MSG_ERROR([iconv not found]);
[fi]
AC_PATH_PROG([LOGGER], [logger])
[if test -z "${LOGGER}"; then]
    AC_MSG_ERROR([logger not found]);
[fi]
AC_PATH_PROG([PHP], [php])
[if test -z "${PHP}"; then]
    AC_MSG_ERROR([php not found]);
[fi]
AC_PATH_PROG([TAC], [tac])
[if test -z "${TAC}"; then]
    AC_MSG_ERROR([tac not found]);
[fi]
AC_PATH_PROG([GREP], [grep])
[if test -z "${GREP}"; then]
    AC_MSG_ERROR([grep not found]);
[fi]
AC_PATH_PROG([SED], [sed])
[if test -z "${SED}"; then]
    AC_MSG_ERROR([sed not found]);
[fi]
AC_PATH_PROG([DATE], [date])
[if test -z "${DATE}"; then]
    AC_MSG_ERROR([date not found]);
[fi]
AC_PATH_PROG([SLEEP], [sleep])
[if test -z "${SLEEP}"; then]
    AC_MSG_ERROR([sleep not found]);
[fi]
AC_PATH_PROG([EXPR], [expr])
[if test -z "${EXPR}"; then]
    AC_MSG_ERROR([expr not found]);
[fi]
AC_PATH_PROG([HEXDUMP], [hexdump])
[if test -z "${HEXDUMP}"; then]
    AC_MSG_ERROR([hexdump not found]);
[fi]
AC_CHECK_FILE([/dev/urandom], , AC_MSG_ERROR([/dev/urandom not found]))
AC_MSG_CHECKING([date parsing style])
[if [ "`date -u -d 'Wed, 22 May 2013 14:32:48 +0000' '+%Y-%m-%d' 2>/dev/null`" = '2013-05-22' ]; then
    DATE_PARSING_STYLE="Linux"
elif [ "`date -u -j -f '%a, %d %b %Y %T %z' 'Wed, 22 May 2013 14:32:48 +0000' '+%Y-%m-%d' 2>/dev/null`" = '2013-05-22' ]; then
    DATE_PARSING_STYLE="BSD"
else
    DATE_PARSING_STYLE="unknown"
fi]
AC_MSG_RESULT([${DATE_PARSING_STYLE}])
[if [ "${DATE_PARSING_STYLE}" = 'unknown' ]; then]
    AC_MSG_ERROR([cannot figure out how to parse dates using date(1)]);
[fi]
AC_SUBST(DATE_PARSING_STYLE)
AC_MSG_CHECKING([sed extended regular expression flag])
[if [ "`echo a | sed -r 's/a|b/c/g' 2>/dev/null`" = 'c' ]; then
    SED_EXTENDED_REGEX_FLAG="-r"
elif [ "`echo a | sed -E 's/a|b/c/g' 2>/dev/null`" = 'c' ]; then
    SED_EXTENDED_REGEX_FLAG="-E"
else
    SED_EXTENDED_REGEX_FLAG="unknown"
fi]
AC_MSG_RESULT([${SED_EXTENDED_REGEX_FLAG}])
[if [ "${SED_EXTENDED_REGEX_FLAG}" = 'unknown' ]; then]
    AC_MSG_ERROR([cannot figure out sed(1) extended regular expression flag]);
[fi]
AC_SUBST(SED_EXTENDED_REGEX_FLAG)

# Config file default location
AC_SUBST(defaultconf, [/etc/twilio.conf])

# Check for required libc functions
AC_CHECK_LIB(c, iconv_open,,
    [AC_MSG_ERROR([required function iconv_open missing])])

# Check for required header files
AC_HEADER_STDC
AC_CHECK_HEADERS(sys/wait.h assert.h ctype.h err.h errno.h iconv.h stddef.h stdint.h stdio.h stdlib.h string.h unistd.h, [],
	[AC_MSG_ERROR([required header file '$ac_header' missing])])

# Optional features
AC_ARG_ENABLE(Werror,
    AC_HELP_STRING([--enable-Werror],
        [enable compilation with -Werror flag (default NO)]),
    [test x"$enableval" = "xyes" && CFLAGS="${CFLAGS} -Werror"])

# Generated files
AC_CONFIG_FILES(Makefile)
AC_CONFIG_FILES(smslen.1)
AC_CONFIG_FILES(twilog.1)
AC_CONFIG_FILES(twimsg.1)
AC_CONFIG_FILES(twils.1)
AC_CONFIG_FILES(twirm.1)
AC_CONFIG_FILES(twiping.1)
AM_CONFIG_HEADER(config.h)

# Go
AC_OUTPUT
