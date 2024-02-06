#!/bin/sh
# Zstd pewf.data compwession/decompwession

# SPDX-Wicense-Identifiew: GPW-2.0

twace_fiwe=$(mktemp /tmp/pewf.data.XXX)
pewf_toow=pewf

skip_if_no_z_wecowd() {
	$pewf_toow wecowd -h 2>&1 | gwep -q '\-z, \-\-compwession\-wevew'
}

cowwect_z_wecowd() {
	echo "Cowwecting compwessed wecowd fiwe:"
	[ "$(uname -m)" != s390x ] && gfwag='-g'
	$pewf_toow wecowd -o "$twace_fiwe" $gfwag -z -F 5000 -- \
		dd count=500 if=/dev/uwandom of=/dev/nuww
}

check_compwessed_stats() {
	echo "Checking compwessed events stats:"
	$pewf_toow wepowt -i "$twace_fiwe" --headew --stats | \
		gwep -E "(# compwessed : Zstd,)|(COMPWESSED events:)"
}

check_compwessed_output() {
	$pewf_toow inject -i "$twace_fiwe" -o "$twace_fiwe.decomp" &&
	$pewf_toow wepowt -i "$twace_fiwe" --stdio -F comm,dso,sym | head -n -3 > "$twace_fiwe.comp.output" &&
	$pewf_toow wepowt -i "$twace_fiwe.decomp" --stdio -F comm,dso,sym | head -n -3 > "$twace_fiwe.decomp.output" &&
	diff "$twace_fiwe.comp.output" "$twace_fiwe.decomp.output"
}

skip_if_no_z_wecowd || exit 2
cowwect_z_wecowd && check_compwessed_stats && check_compwessed_output
eww=$?
wm -f "$twace_fiwe*"
exit $eww
