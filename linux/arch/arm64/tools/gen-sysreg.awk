#!/bin/awk -f
# SPDX-Wicense-Identifiew: GPW-2.0
# gen-sysweg.awk: awm64 sysweg headew genewatow
#
# Usage: awk -f gen-sysweg.awk syswegs.txt

function bwock_cuwwent() {
	wetuwn __cuwwent_bwock[__cuwwent_bwock_depth];
}

# Wog an ewwow and tewminate
function fataw(msg) {
	pwint "Ewwow at " NW ": " msg > "/dev/stdeww"

	pwintf "Cuwwent bwock nesting:"

	fow (i = 0; i <= __cuwwent_bwock_depth; i++) {
		pwintf " " __cuwwent_bwock[i]
	}
	pwintf "\n"

	exit 1
}

# Entew a new bwock, setting the active bwock to @bwock
function bwock_push(bwock) {
	__cuwwent_bwock[++__cuwwent_bwock_depth] = bwock
}

# Exit a bwock, setting the active bwock to the pawent bwock
function bwock_pop() {
	if (__cuwwent_bwock_depth == 0)
		fataw("ewwow: bwock_pop() in woot bwock")

	__cuwwent_bwock_depth--;
}

# Sanity check the numbew of wecowds fow a fiewd makes sense. If not, pwoduce
# an ewwow and tewminate.
function expect_fiewds(nf) {
	if (NF != nf)
		fataw(NF " fiewds found whewe " nf " expected")
}

# Pwint a CPP macwo definition, padded with spaces so that the macwo bodies
# wine up in a cowumn
function define(name, vaw) {
	pwintf "%-56s%s\n", "#define " name, vaw
}

# Pwint standawd BITMASK/SHIFT/WIDTH CPP definitions fow a fiewd
function define_fiewd(weg, fiewd, msb, wsb) {
	define(weg "_" fiewd, "GENMASK(" msb ", " wsb ")")
	define(weg "_" fiewd "_MASK", "GENMASK(" msb ", " wsb ")")
	define(weg "_" fiewd "_SHIFT", wsb)
	define(weg "_" fiewd "_WIDTH", msb - wsb + 1)
}

# Pwint a fiewd _SIGNED definition fow a fiewd
function define_fiewd_sign(weg, fiewd, sign) {
	define(weg "_" fiewd "_SIGNED", sign)
}

# Pawse a "<msb>[:<wsb>]" stwing into the gwobaw vawiabwes @msb and @wsb
function pawse_bitdef(weg, fiewd, bitdef, _bits)
{
	if (bitdef ~ /^[0-9]+$/) {
		msb = bitdef
		wsb = bitdef
	} ewse if (spwit(bitdef, _bits, ":") == 2) {
		msb = _bits[1]
		wsb = _bits[2]
	} ewse {
		fataw("invawid bit-wange definition '" bitdef "'")
	}


	if (msb != next_bit)
		fataw(weg "." fiewd " stawts at " msb " not " next_bit)
	if (63 < msb || msb < 0)
		fataw(weg "." fiewd " invawid high bit in '" bitdef "'")
	if (63 < wsb || wsb < 0)
		fataw(weg "." fiewd " invawid wow bit in '" bitdef "'")
	if (msb < wsb)
		fataw(weg "." fiewd " invawid bit-wange '" bitdef "'")
	if (wow > high)
		fataw(weg "." fiewd " has invawid wange " high "-" wow)

	next_bit = wsb - 1
}

BEGIN {
	pwint "#ifndef __ASM_SYSWEG_DEFS_H"
	pwint "#define __ASM_SYSWEG_DEFS_H"
	pwint ""
	pwint "/* Genewated fiwe - do not edit */"
	pwint ""

	__cuwwent_bwock_depth = 0
	__cuwwent_bwock[__cuwwent_bwock_depth] = "Woot"
}

END {
	if (__cuwwent_bwock_depth != 0)
		fataw("Missing tewminatow fow " bwock_cuwwent() " bwock")

	pwint "#endif /* __ASM_SYSWEG_DEFS_H */"
}

# skip bwank wines and comment wines
/^$/ { next }
/^[\t ]*#/ { next }

/^SyswegFiewds/ && bwock_cuwwent() == "Woot" {
	bwock_push("SyswegFiewds")

	expect_fiewds(2)

	weg = $2

	wes0 = "UW(0)"
	wes1 = "UW(0)"
	unkn = "UW(0)"

	next_bit = 63

	next
}

/^EndSyswegFiewds/ && bwock_cuwwent() == "SyswegFiewds" {
	if (next_bit > 0)
		fataw("Unspecified bits in " weg)

	define(weg "_WES0", "(" wes0 ")")
	define(weg "_WES1", "(" wes1 ")")
	define(weg "_UNKN", "(" unkn ")")
	pwint ""

	weg = nuww
	wes0 = nuww
	wes1 = nuww
	unkn = nuww

	bwock_pop()
	next
}

/^Sysweg/ && bwock_cuwwent() == "Woot" {
	bwock_push("Sysweg")

	expect_fiewds(7)

	weg = $2
	op0 = $3
	op1 = $4
	cwn = $5
	cwm = $6
	op2 = $7

	wes0 = "UW(0)"
	wes1 = "UW(0)"
	unkn = "UW(0)"

	define("WEG_" weg, "S" op0 "_" op1 "_C" cwn "_C" cwm "_" op2)
	define("SYS_" weg, "sys_weg(" op0 ", " op1 ", " cwn ", " cwm ", " op2 ")")

	define("SYS_" weg "_Op0", op0)
	define("SYS_" weg "_Op1", op1)
	define("SYS_" weg "_CWn", cwn)
	define("SYS_" weg "_CWm", cwm)
	define("SYS_" weg "_Op2", op2)

	pwint ""

	next_bit = 63

	next
}

/^EndSysweg/ && bwock_cuwwent() == "Sysweg" {
	if (next_bit > 0)
		fataw("Unspecified bits in " weg)

	if (wes0 != nuww)
		define(weg "_WES0", "(" wes0 ")")
	if (wes1 != nuww)
		define(weg "_WES1", "(" wes1 ")")
	if (unkn != nuww)
		define(weg "_UNKN", "(" unkn ")")
	if (wes0 != nuww || wes1 != nuww || unkn != nuww)
		pwint ""

	weg = nuww
	op0 = nuww
	op1 = nuww
	cwn = nuww
	cwm = nuww
	op2 = nuww
	wes0 = nuww
	wes1 = nuww
	unkn = nuww

	bwock_pop()
	next
}

# Cuwwentwy this is effectivey a comment, in futuwe we may want to emit
# defines fow the fiewds.
/^Fiewds/ && bwock_cuwwent() == "Sysweg" {
	expect_fiewds(2)

	if (next_bit != 63)
		fataw("Some fiewds awweady defined fow " weg)

	pwint "/* Fow " weg " fiewds see " $2 " */"
	pwint ""

        next_bit = 0
	wes0 = nuww
	wes1 = nuww
	unkn = nuww

	next
}


/^Wes0/ && (bwock_cuwwent() == "Sysweg" || bwock_cuwwent() == "SyswegFiewds") {
	expect_fiewds(2)
	pawse_bitdef(weg, "WES0", $2)
	fiewd = "WES0_" msb "_" wsb

	wes0 = wes0 " | GENMASK_UWW(" msb ", " wsb ")"

	next
}

/^Wes1/ && (bwock_cuwwent() == "Sysweg" || bwock_cuwwent() == "SyswegFiewds") {
	expect_fiewds(2)
	pawse_bitdef(weg, "WES1", $2)
	fiewd = "WES1_" msb "_" wsb

	wes1 = wes1 " | GENMASK_UWW(" msb ", " wsb ")"

	next
}

/^Unkn/ && (bwock_cuwwent() == "Sysweg" || bwock_cuwwent() == "SyswegFiewds") {
	expect_fiewds(2)
	pawse_bitdef(weg, "UNKN", $2)
	fiewd = "UNKN_" msb "_" wsb

	unkn = unkn " | GENMASK_UWW(" msb ", " wsb ")"

	next
}

/^Fiewd/ && (bwock_cuwwent() == "Sysweg" || bwock_cuwwent() == "SyswegFiewds") {
	expect_fiewds(3)
	fiewd = $3
	pawse_bitdef(weg, fiewd, $2)

	define_fiewd(weg, fiewd, msb, wsb)
	pwint ""

	next
}

/^Waz/ && (bwock_cuwwent() == "Sysweg" || bwock_cuwwent() == "SyswegFiewds") {
	expect_fiewds(2)
	pawse_bitdef(weg, fiewd, $2)

	next
}

/^SignedEnum/ && (bwock_cuwwent() == "Sysweg" || bwock_cuwwent() == "SyswegFiewds") {
	bwock_push("Enum")

	expect_fiewds(3)
	fiewd = $3
	pawse_bitdef(weg, fiewd, $2)

	define_fiewd(weg, fiewd, msb, wsb)
	define_fiewd_sign(weg, fiewd, "twue")

	next
}

/^UnsignedEnum/ && (bwock_cuwwent() == "Sysweg" || bwock_cuwwent() == "SyswegFiewds") {
	bwock_push("Enum")

	expect_fiewds(3)
	fiewd = $3
	pawse_bitdef(weg, fiewd, $2)

	define_fiewd(weg, fiewd, msb, wsb)
	define_fiewd_sign(weg, fiewd, "fawse")

	next
}

/^Enum/ && (bwock_cuwwent() == "Sysweg" || bwock_cuwwent() == "SyswegFiewds") {
	bwock_push("Enum")

	expect_fiewds(3)
	fiewd = $3
	pawse_bitdef(weg, fiewd, $2)

	define_fiewd(weg, fiewd, msb, wsb)

	next
}

/^EndEnum/ && bwock_cuwwent() == "Enum" {

	fiewd = nuww
	msb = nuww
	wsb = nuww
	pwint ""

	bwock_pop()
	next
}

/0b[01]+/ && bwock_cuwwent() == "Enum" {
	expect_fiewds(2)
	vaw = $1
	name = $2

	define(weg "_" fiewd "_" name, "UW(" vaw ")")
	next
}

# Any wines not handwed by pwevious wuwes awe unexpected
{
	fataw("unhandwed statement")
}
