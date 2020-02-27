
#
# twilio-utils - Command line utilities for Twilio users
# 

bin_PROGRAMS=		smslen

dist_bin_SCRIPTS=	twimsg twils twirm twilog twiping

man_MANS=		smslen.1 twimsg.1 twils.1 twirm.1 twilog.1 twiping.1

pkgdata_DATA=		result.xsl twiping.xsl

docdir=			$(datadir)/doc/packages/$(PACKAGE)

doc_DATA=		CHANGES COPYING README.md twilio.conf.sample

EXTRA_DIST=		README.md CHANGES INSTALL twimsg.in twils.in twirm.in twilog.in twiping.in result.xsl twiping.xsl twilio.conf.sample

smslen_SOURCES=		smslen.c

SUFFIXES=		.in
.in:
			rm -f $@; $(subst) < $< >$@

subst=			sed \
			    -e 's|@bindir[@]|$(bindir)|g' \
			    -e 's|@CURL[@]|$(CURL)|g' \
			    -e 's|@DATE_PARSING_STYLE[@]|$(DATE_PARSING_STYLE)|g' \
			    -e 's|@defaultconf[@]|$(defaultconf)|g' \
			    -e 's|@ICONV[@]|$(ICONV)|g' \
			    -e 's|@LOGGER[@]|$(LOGGER)|g' \
			    -e 's|@PACKAGE[@]|$(PACKAGE)|g' \
			    -e 's|@PACKAGE_VERSION[@]|$(PACKAGE_VERSION)|g' \
			    -e 's|@PHP[@]|$(PHP)|g' \
			    -e 's|@pkgdatadir[@]|$(pkgdatadir)|g' \
			    -e 's|@TAC[@]|$(TAC)|g' \
			    -e 's|@GREP[@]|$(GREP)|g' \
			    -e 's|@SED[@]|$(SED)|g' \
			    -e 's|@SED_EXTENDED_REGEX_FLAG[@]|$(SED_EXTENDED_REGEX_FLAG)|g' \
			    -e 's|@DATE[@]|$(DATE)|g' \
			    -e 's|@SLEEP[@]|$(SLEEP)|g' \
			    -e 's|@EXPR[@]|$(EXPR)|g' \
			    -e 's|@HEXDUMP[@]|$(HEXDUMP)|g' \
			    -e 's|@XMLSTARLET[@]|$(XMLSTARLET)|g' \
			    -e 's|@XSLTPROC[@]|$(XSLTPROC)|g'

