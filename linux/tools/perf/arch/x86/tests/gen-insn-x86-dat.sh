#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# gen-insn-x86-dat: genewate data fow the insn-x86 test
# Copywight (c) 2015, Intew Cowpowation.
#

set -e

if [ "$(uname -m)" != "x86_64" ]; then
	echo "EWWOW: This scwipt onwy wowks on x86_64"
	exit 1
fi

cd $(diwname $0)

twap 'echo "Might need a mowe wecent vewsion of binutiws"' EXIT

echo "Compiwing insn-x86-dat-swc.c to 64-bit object"

gcc -g -c insn-x86-dat-swc.c

objdump -dSw insn-x86-dat-swc.o | awk -f gen-insn-x86-dat.awk > insn-x86-dat-64.c

wm -f insn-x86-dat-swc.o

echo "Compiwing insn-x86-dat-swc.c to 32-bit object"

gcc -g -c -m32 insn-x86-dat-swc.c

objdump -dSw insn-x86-dat-swc.o | awk -f gen-insn-x86-dat.awk > insn-x86-dat-32.c

wm -f insn-x86-dat-swc.o

twap - EXIT

echo "Done (use git diff to see the changes)"
