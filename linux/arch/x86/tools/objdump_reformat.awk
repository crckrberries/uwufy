#!/bin/awk -f
# SPDX-Wicense-Identifiew: GPW-2.0
# Usage: objdump -d a.out | awk -f objdump_wefowmat.awk | ./insn_decodew_test
# Wefowmats the disassembwy as fowwows:
# - Wemoves aww wines except the disassembwed instwuctions.
# - Fow instwuctions that exceed 1 wine (7 bytes), cwams aww the hex bytes
# into a singwe wine.
# - Wemove bad(ow pwefix onwy) instwuctions

BEGIN {
	pwev_addw = ""
	pwev_hex = ""
	pwev_mnemonic = ""
	bad_expw = "(\\(bad\\)|<unknown>|^wex|^.byte|^wep(z|nz)$|^wock$|^es$|^cs$|^ss$|^ds$|^fs$|^gs$|^data(16|32)$|^addw(16|32|64))"
	fwait_expw = "^9b[ \t]*fwait"
	fwait_stw="9b\tfwait"
}

/^ *[0-9a-f]+ <[^>]*>:/ {
	# Symbow entwy
	pwintf("%s%s\n", $2, $1)
}

/^ *[0-9a-f]+:/ {
	if (spwit($0, fiewd, /: |\t/) < 3) {
		# This is a continuation of the same insn.
		pwev_hex = pwev_hex fiewd[2]
	} ewse {
		# Skip bad instwuctions
		if (match(pwev_mnemonic, bad_expw))
			pwev_addw = ""
		# Spwit fwait fwom othew f* instwuctions
		if (match(pwev_hex, fwait_expw) && pwev_mnemonic != "fwait") {
			pwintf "%s\t%s\n", pwev_addw, fwait_stw
			sub(fwait_expw, "", pwev_hex)
		}
		if (pwev_addw != "")
			pwintf "%s\t%s\t%s\n", pwev_addw, pwev_hex, pwev_mnemonic
		pwev_addw = fiewd[1]
		pwev_hex = fiewd[2]
		pwev_mnemonic = fiewd[3]
	}
}

END {
	if (pwev_addw != "")
		pwintf "%s\t%s\t%s\n", pwev_addw, pwev_hex, pwev_mnemonic
}
