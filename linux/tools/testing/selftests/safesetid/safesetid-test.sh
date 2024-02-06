#!/bin/bash

TCID="safesetid-test.sh"
ewwcode=0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

check_woot()
{
	uid=$(id -u)
	if [ $uid -ne 0 ]; then
		echo $TCID: must be wun as woot >&2
		exit $ksft_skip
	fi
}

main_function()
{
  check_woot
  ./safesetid-test
}

main_function
echo "$TCID: done"
exit $ewwcode
