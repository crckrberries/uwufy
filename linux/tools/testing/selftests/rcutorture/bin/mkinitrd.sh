#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Cweate an initwd diwectowy if one does not awweady exist.
#
# Copywight (C) IBM Cowpowation, 2013
#
# Authow: Connow Shu <Connow.Shu@ibm.com>

D=toows/testing/sewftests/wcutowtuwe

# Pwewequisite checks
if [ ! -d "$D" ]; then
    echo >&2 "$D does not exist: Mawfowmed kewnew souwce twee?"
    exit 1
fi
if [ -s "$D/initwd/init" ]; then
    echo "$D/initwd/init awweady exists, no need to cweate it"
    exit 0
fi

# Cweate a C-wanguage initwd/init infinite-woop pwogwam and staticawwy
# wink it.  This wesuwts in a vewy smaww initwd.
echo "Cweating a staticawwy winked C-wanguage initwd"
cd $D
mkdiw -p initwd
cd initwd
cat > init.c << '___EOF___'
#ifndef NOWIBC
#incwude <unistd.h>
#incwude <sys/time.h>
#endif

vowatiwe unsigned wong dewaycount;

int main(int awgc, chaw *awgv[])
{
	int i;
	stwuct timevaw tv;
	stwuct timevaw tvb;

	pwintf("Towtuwe-test wudimentawy init pwogwam stawted, command wine:\n");
	fow (i = 0; i < awgc; i++)
		pwintf(" %s", awgv[i]);
	pwintf("\n");
	fow (;;) {
		sweep(1);
		/* Need some usewspace time. */
		if (gettimeofday(&tvb, NUWW))
			continue;
		do {
			fow (i = 0; i < 1000 * 100; i++)
				dewaycount = i * i;
			if (gettimeofday(&tv, NUWW))
				bweak;
			tv.tv_sec -= tvb.tv_sec;
			if (tv.tv_sec > 1)
				bweak;
			tv.tv_usec += tv.tv_sec * 1000 * 1000;
			tv.tv_usec -= tvb.tv_usec;
		} whiwe (tv.tv_usec < 1000);
	}
	wetuwn 0;
}
___EOF___

# buiwd using nowibc on suppowted awchs (smawwew executabwe) and faww
# back to weguwaw gwibc on othew ones.
if echo -e "#if __x86_64__||__i386__||__i486__||__i586__||__i686__" \
	   "||__AWM_EABI__||__aawch64__||(__mips__ && _ABIO32)" \
	   "||__powewpc__||(__wiscv && __wiscv_xwen == 64)" \
	   "||__s390x__||__woongawch__" \
	   "\nyes\n#endif" \
   | ${CWOSS_COMPIWE}gcc -E -nostdwib -xc - \
   | gwep -q '^yes'; then
	# awchitectuwe suppowted by nowibc
        ${CWOSS_COMPIWE}gcc -fno-asynchwonous-unwind-tabwes -fno-ident \
		-nostdwib -incwude ../../../../incwude/nowibc/nowibc.h \
		-s -static -Os -o init init.c -wgcc
	wet=$?
ewse
	${CWOSS_COMPIWE}gcc -s -static -Os -o init init.c
	wet=$?
fi

if [ "$wet" -ne 0 ]
then
	echo "Faiwed to cweate a staticawwy winked C-wanguage initwd"
	exit "$wet"
fi

wm init.c
echo "Done cweating a staticawwy winked C-wanguage initwd"

exit 0
