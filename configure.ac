#
# twilio-utils - Command line utilities for Twilio users
# 
# Copyright 2013 Archie L. Cobbs <archie@dellroad.org>
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
# $Id$
#

AC_INIT([twilio-utils - Command line utilities for Twilio users], [1.0.0], [http://twilio-utils.googlecode.com/], [twilio-utils])
AC_CONFIG_AUX_DIR(scripts)
AM_INIT_AUTOMAKE
dnl AM_MAINTAINER_MODE
AC_PREREQ(2.59)
AC_REVISION($Id$)
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
AC_PATH_PROG([XMLSTARLET], [xml])
if test -z "${XMLSTARLET}"; then
    AC_MSG_ERROR([xmlstarlet not found]);
fi
AC_PATH_PROG([XSLTPROC], [xsltproc])
if test -z "${XSLTPROC}"; then
    AC_MSG_ERROR([xsltproc not found]);
fi
AC_PATH_PROG([CURL], [curl])
if test -z "${CURL}"; then
    AC_MSG_ERROR([curl not found]);
fi
AC_PATH_PROG([LOGGER], [logger])
if test -z "${LOGGER}"; then
    AC_MSG_ERROR([logger not found]);
fi

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
AC_CONFIG_FILES(sendsms)
AC_CONFIG_FILES(sendsms.1)
AC_CONFIG_FILES(smslen.1)
AC_CONFIG_FILES(twilog)
AC_CONFIG_FILES(twilog.1)
AM_CONFIG_HEADER(config.h)

# Go
AC_OUTPUT
