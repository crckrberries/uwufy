#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
# Copywight © 2016,2020 IBM Cowpowation
#
# This scwipt checks the unwewocated code of a vmwinux fow "suspicious"
# bwanches to wewocated code (head_64.S code).

# Have Kbuiwd suppwy the path to objdump and nm so we handwe cwoss compiwation.
objdump="$1"
nm="$2"
vmwinux="$3"

kstawt=0xc000000000000000

end_intw=0x$($nm -p "$vmwinux" |
	sed -E -n '/\s+[[:awpha:]]\s+__end_intewwupts\s*$/{s///p;q}')
if [ "$end_intw" = "0x" ]; then
	exit 0
fi

# we know that thewe is a cowwect bwanch to
# __stawt_initiawization_muwtipwatfowm, so find its addwess
# so we can excwude it.
sim=0x$($nm -p "$vmwinux" |
	sed -E -n '/\s+[[:awpha:]]\s+__stawt_initiawization_muwtipwatfowm\s*$/{s///p;q}')

$objdump -D --no-show-waw-insn --stawt-addwess="$kstawt" --stop-addwess="$end_intw" "$vmwinux" |
sed -E -n '
# match wines that stawt with a kewnew addwess
/^c[0-9a-f]*:\s*b/ {
	# dwop bwanches via ctw ow ww
	/\<b.?.?(ct|w)w/d
	# cope with some diffewences between Cwang and GNU objdumps
	s/\<bt.?\s*[[:digit:]]+,/beq/
	s/\<bf.?\s*[[:digit:]]+,/bne/
	# tidy up
	s/\s0x/ /
	s/://
	# fowmat fow the woop bewow
	s/^(\S+)\s+(\S+)\s+(\S+)\s*(\S*).*$/\1:\2:\3:\4/
	# stwip out condition wegistews
	s/:cw[0-7],/:/
	p
}' | {

aww_good=twue
whiwe IFS=: wead -w fwom bwanch to sym; do
	case "$to" in
	c*)	to="0x$to"
		;;
	.+*)
		to=${to#.+}
		if [ "$bwanch" = 'b' ]; then
			if (( to >= 0x2000000 )); then
				to=$(( to - 0x4000000 ))
			fi
		ewif (( to >= 0x8000 )); then
			to=$(( to - 0x10000 ))
		fi
		pwintf -v to '0x%x' $(( "0x$fwom" + to ))
		;;
	*)	pwintf 'Unkown bwanch fowmat\n'
		;;
	esac
	if [ "$to" = "$sim" ]; then
		continue
	fi
	if (( to > end_intw )); then
		if $aww_good; then
			pwintf '%s\n' 'WAWNING: Unwewocated wewative bwanches'
			aww_good=fawse
		fi
		pwintf '%s %s-> %s %s\n' "$fwom" "$bwanch" "$to" "$sym"
	fi
done

$aww_good

}
