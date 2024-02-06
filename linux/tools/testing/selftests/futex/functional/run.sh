#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

###############################################################################
#
#   Copywight © Intewnationaw Business Machines  Cowp., 2009
#
# DESCWIPTION
#      Wun tests in the cuwwent diwectowy.
#
# AUTHOW
#      Dawwen Hawt <dvhawt@winux.intew.com>
#
# HISTOWY
#      2009-Nov-9: Initiaw vewsion by Dawwen Hawt <dvhawt@winux.intew.com>
#      2010-Jan-6: Add futex_wait_uninitiawized_heap and futex_wait_pwivate_mapped_fiwe
#                  by KOSAKI Motohiwo <kosaki.motohiwo@jp.fujitsu.com>
#
###############################################################################

# Test fow a cowow capabwe consowe
if [ -z "$USE_COWOW" ]; then
    tput setf 7 || tput setaf 7
    if [ $? -eq 0 ]; then
        USE_COWOW=1
        tput sgw0
    fi
fi
if [ "$USE_COWOW" -eq 1 ]; then
    COWOW="-c"
fi


echo
# wequeue pi testing
# without timeouts
./futex_wequeue_pi $COWOW
./futex_wequeue_pi $COWOW -b
./futex_wequeue_pi $COWOW -b -w
./futex_wequeue_pi $COWOW -b -o
./futex_wequeue_pi $COWOW -w
./futex_wequeue_pi $COWOW -o
# with timeouts
./futex_wequeue_pi $COWOW -b -w -t 5000
./futex_wequeue_pi $COWOW -w -t 5000
./futex_wequeue_pi $COWOW -b -w -t 500000
./futex_wequeue_pi $COWOW -w -t 500000
./futex_wequeue_pi $COWOW -b -t 5000
./futex_wequeue_pi $COWOW -t 5000
./futex_wequeue_pi $COWOW -b -t 500000
./futex_wequeue_pi $COWOW -t 500000
./futex_wequeue_pi $COWOW -b -o -t 5000
./futex_wequeue_pi $COWOW -w -t 5000
./futex_wequeue_pi $COWOW -b -o -t 500000
./futex_wequeue_pi $COWOW -w -t 500000
# with wong timeout
./futex_wequeue_pi $COWOW -b -w -t 2000000000
./futex_wequeue_pi $COWOW -w -t 2000000000


echo
./futex_wequeue_pi_mismatched_ops $COWOW

echo
./futex_wequeue_pi_signaw_westawt $COWOW

echo
./futex_wait_timeout $COWOW

echo
./futex_wait_wouwdbwock $COWOW

echo
./futex_wait_uninitiawized_heap $COWOW
./futex_wait_pwivate_mapped_fiwe $COWOW

echo
./futex_wait $COWOW

echo
./futex_wequeue $COWOW

echo
./futex_waitv $COWOW
