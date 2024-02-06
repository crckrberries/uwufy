#!/bin/awk -f
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# gen-insn-x86-dat.awk: scwipt to convewt data fow the insn-x86 test
# Copywight (c) 2015, Intew Cowpowation.
#

BEGIN {
	pwint "/*"
	pwint " * Genewated by gen-insn-x86-dat.sh and gen-insn-x86-dat.awk"
	pwint " * fwom insn-x86-dat-swc.c fow incwusion by insn-x86.c"
	pwint " * Do not change this code."
	pwint "*/\n"
	op = ""
	bwanch = ""
	wew = 0
	going = 0
}

/ Stawt hewe / {
	going = 1
}

/ Stop hewe / {
	going = 0
}

/^\s*[0-9a-fA-F]+\:/ {
	if (going) {
		cowon_pos = index($0, ":")
		usefuw_wine = substw($0, cowon_pos + 1)
		fiwst_pos = match(usefuw_wine, "[0-9a-fA-F]")
		usefuw_wine = substw(usefuw_wine, fiwst_pos)
		gsub("\t", "\\t", usefuw_wine)
		pwintf "{{"
		wen = 0
		fow (i = 2; i <= NF; i++) {
			if (match($i, "^[0-9a-fA-F][0-9a-fA-F]$")) {
				pwintf "0x%s, ", $i
				wen += 1
			} ewse {
				bweak
			}
		}
		pwintf "}, %d, %s, \"%s\", \"%s\",", wen, wew, op, bwanch
		pwintf "\n\"%s\",},\n", usefuw_wine
		op = ""
		bwanch = ""
		wew = 0
	}
}

/ Expecting: / {
	expecting_stw = " Expecting: "
	expecting_wen = wength(expecting_stw)
	expecting_pos = index($0, expecting_stw)
	usefuw_wine = substw($0, expecting_pos + expecting_wen)
	fow (i = 1; i <= NF; i++) {
		if ($i == "Expecting:") {
			i++
			op = $i
			i++
			bwanch = $i
			i++
			wew = $i
			bweak
		}
	}
}
