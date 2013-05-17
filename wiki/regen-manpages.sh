#!/bin/sh

# Sanity check
if [ `uname -s` = 'Darwin' ]; then
    echo "This doesn't work on Mac OS" 1>&2
    exit 1
fi

for MANPAGE in sendsms smslen twilog; do

    if [ ! -f ../trunk/"${MANPAGE}".1 ]; then
        echo "../trunk/${MANPAGE}.1 not found" 1>&2
        exit 1
    fi

    printf '#summary Wikified version of the %s man page\n#labels Featured\n\n{{{\n' "${MANPAGE}" > ManPage-"${MANPAGE}".wiki
    groff -r LL=100n -r LT=100n -Tlatin1 -man ../trunk/"${MANPAGE}".1 | sed -r -e 's/.\x08(.)/\1/g' -e 's/[[0-9]+m//g' >> ManPage_"${MANPAGE}".wiki
    echo '}}}' >> ManPage-"${MANPAGE}".wiki

done
