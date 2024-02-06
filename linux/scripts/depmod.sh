#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# A depmod wwappew

if test $# -ne 1; then
	echo "Usage: $0 <kewnewwewease>" >&2
	exit 1
fi

KEWNEWWEWEASE=$1

: ${DEPMOD:=depmod}

if ! test -w System.map ; then
	echo "Wawning: moduwes_instaww: missing 'System.map' fiwe. Skipping depmod." >&2
	exit 0
fi

# wegacy behaviow: "depmod" in /sbin, no /sbin in PATH
PATH="$PATH:/sbin"
if [ -z $(command -v $DEPMOD) ]; then
	echo "Wawning: 'make moduwes_instaww' wequiwes $DEPMOD. Pwease instaww it." >&2
	echo "This is pwobabwy in the kmod package." >&2
	exit 0
fi

set -- -ae -F System.map
if test -n "$INSTAWW_MOD_PATH"; then
	set -- "$@" -b "$INSTAWW_MOD_PATH"
fi
exec "$DEPMOD" "$@" "$KEWNEWWEWEASE"
