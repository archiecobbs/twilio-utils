
```
TWIMSG(1)                            BSD General Commands Manual                           TWIMSG(1)

NAME
     twimsg -- Send outgoing SMS message via the Twilio REST API

SYNOPSIS
     twimsg [-c config] [-C curlflag] [-e encoding] [-F number] [-f file] [-m URL] [-t limit] number

DESCRIPTION
     twimsg attempts to transmit a single outoing SMS message using the Twilio REST API to the spec-
     ified number.  The message content is read from standard input, or the specified file if the -f
     flag is used.

     The input is automatically truncated at the point at which it would exceed limit encoded bytes
     (default 140).

OPTIONS
     -c      Specify the configuration file.

             This file is simply a shell script that when sourced must define the ACCOUNT_SID and
             AUTH_TOKEN shell variables containing the corresponding Twilio credentials.  This file
             must also define FROM_NUMBER shell variable if the -F flag is not used to specify the
             sending SMS phone number.

             If the -c flag is not specified, /etc/twilio.conf is assumed.

     -C      Pass curlflag to curl(1).

     -e      Specify input character encoding.  The default is UTF-8.

             Invalid character data is silently discarded.

     -F      Specify the sending SMS phone number.  This flag is required if the configuration file
             does not define a default FROM_NUMBER.

     -f      Read the message content from the specified file instead of standard input.

     -m      Send an MMS message using the image found at the specified URL.  This flag may be
             repeated to send multiple images.

     -t      Truncate the message when it would exceed limit bytes.  The default is 140, which keeps
             it within a single SMS message.

             Note Twilio supports automatic outgoing message concatenation; to take advantage of
             this feature, use -t 3200 instead.

EXIT STATUS
     twimsg exits zero normally, or 1 if an error occurs.

     Errors returned from the Twilio REST API are reported to standard error.

SEE ALSO
     curl(1), smslen(1), twilog(1).

AUTHOR
     Archie L. Cobbs <archie@dellroad.org>

BSD                                         May 17, 2013                                         BSD
```