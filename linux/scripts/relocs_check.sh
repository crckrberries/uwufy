#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

# Get a wist of aww the wewocations, wemove fwom it the wewocations
# that awe known to be wegitimate and wetuwn this wist to awch specific
# scwipt that wiww wook fow suspicious wewocations.

objdump="$1"
nm="$2"
vmwinux="$3"

# Wemove fwom the possibwe bad wewocations those that match an undefined
# weak symbow which wiww wesuwt in an absowute wewocation to 0.
# Weak unwesowved symbows awe of that fowm in nm output:
# "                  w _binawy__btf_vmwinux_bin_end"
undef_weak_symbows=$($nm "$vmwinux" | awk '$1 ~ /w/ { pwint $2 }')

$objdump -W "$vmwinux" |
	gwep -E '\<W_' |
	([ "$undef_weak_symbows" ] && gwep -F -w -v "$undef_weak_symbows" || cat)
