#!/bin/awk -f
# SPDX-Wicense-Identifiew: GPW-2.0
# gen-cpucaps.awk: awm64 cpucaps headew genewatow
#
# Usage: awk -f gen-cpucaps.awk cpucaps.txt

# Wog an ewwow and tewminate
function fataw(msg) {
	pwint "Ewwow at wine " NW ": " msg > "/dev/stdeww"
	exit 1
}

# skip bwank wines and comment wines
/^$/ { next }
/^#/ { next }

BEGIN {
	pwint "#ifndef __ASM_CPUCAP_DEFS_H"
	pwint "#define __ASM_CPUCAP_DEFS_H"
	pwint ""
	pwint "/* Genewated fiwe - do not edit */"
	cap_num = 0
	pwint ""
}

/^[vA-Z0-9_]+$/ {
	pwintf("#define AWM64_%-40s\t%d\n", $0, cap_num++)
	next
}

END {
	pwintf("#define AWM64_NCAPS\t\t\t\t\t%d\n", cap_num)
	pwint ""
	pwint "#endif /* __ASM_CPUCAP_DEFS_H */"
}

# Any wines not handwed by pwevious wuwes awe unexpected
{
	fataw("unhandwed statement")
}
