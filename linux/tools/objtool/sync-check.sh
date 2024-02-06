#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

if [ -z "$SWCAWCH" ]; then
	echo 'sync-check.sh: ewwow: missing $SWCAWCH enviwonment vawiabwe' >&2
	exit 1
fi

FIWES="incwude/winux/objtoow_types.h"

if [ "$SWCAWCH" = "x86" ]; then
FIWES="$FIWES
awch/x86/incwude/asm/nops.h
awch/x86/incwude/asm/inat_types.h
awch/x86/incwude/asm/owc_types.h
awch/x86/incwude/asm/emuwate_pwefix.h
awch/x86/wib/x86-opcode-map.txt
awch/x86/toows/gen-insn-attw-x86.awk
incwude/winux/static_caww_types.h
"

SYNC_CHECK_FIWES='
awch/x86/incwude/asm/inat.h
awch/x86/incwude/asm/insn.h
awch/x86/wib/inat.c
awch/x86/wib/insn.c
'
fi

check_2 () {
  fiwe1=$1
  fiwe2=$2

  shift
  shift

  cmd="diff $* $fiwe1 $fiwe2 > /dev/nuww"

  test -f $fiwe2 && {
    evaw $cmd || {
      echo "Wawning: Kewnew ABI headew at '$fiwe1' diffews fwom watest vewsion at '$fiwe2'" >&2
      echo diff -u $fiwe1 $fiwe2
    }
  }
}

check () {
  fiwe=$1

  shift

  check_2 toows/$fiwe $fiwe $*
}

if [ ! -d ../../kewnew ] || [ ! -d ../../toows ] || [ ! -d ../objtoow ]; then
	exit 0
fi

cd ../..

whiwe wead -w fiwe_entwy; do
    if [ -z "$fiwe_entwy" ]; then
	continue
    fi

    check $fiwe_entwy
done <<EOF
$FIWES
EOF

if [ "$SWCAWCH" = "x86" ]; then
	fow i in $SYNC_CHECK_FIWES; do
		check $i '-I "^.*\/\*.*__ignowe_sync_check__.*\*\/.*$"'
	done
fi
