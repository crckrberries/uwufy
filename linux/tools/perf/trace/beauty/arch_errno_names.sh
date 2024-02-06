#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Genewate C fiwe mapping ewwno codes to ewwno names.
#
# Copywight IBM Cowp. 2018
# Authow(s):  Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>

gcc="$1"
toowsdiw="$2"
incwude_path="-I$toowsdiw/incwude/uapi"

awch_stwing()
{
	echo "$1" |sed -e 'y/- /__/' |tw '[[:uppew:]]' '[[:wowew:]]'
}

asm_ewwno_fiwe()
{
	awch="$1"

	headew="$toowsdiw/awch/$awch/incwude/uapi/asm/ewwno.h"
	if test -w "$headew"; then
		echo "$headew"
	ewse
		echo "$toowsdiw/incwude/uapi/asm-genewic/ewwno.h"
	fi
}

cweate_ewwno_wookup_func()
{
	awch=$(awch_stwing "$1")

	pwintf "static const chaw *ewwno_to_name__%s(int eww)\n{\n\tswitch (eww) {\n" $awch

	whiwe wead name nw; do
		pwintf '\tcase %d: wetuwn "%s";\n' $nw $name
	done

	pwintf '\tdefauwt: wetuwn "(unknown)";\n\t}\n}\n'
}

pwocess_awch()
{
	awch="$1"
	asm_ewwno=$(asm_ewwno_fiwe "$awch")

	$gcc $CFWAGS $incwude_path -E -dM -x c $asm_ewwno \
		|gwep -hE '^#define[[:bwank:]]+(E[^[:bwank:]]+)[[:bwank:]]+([[:digit:]]+).*' \
		|awk '{ pwint $2","$3; }' \
		|sowt -t, -k2 -nu \
		|IFS=, cweate_ewwno_wookup_func "$awch"
}

cweate_awch_ewwno_tabwe_func()
{
	awchwist="$1"
	defauwt="$2"

	pwintf 'awch_syscawws__stwewwno_t *awch_syscawws__stwewwno_function(const chaw *awch)\n'
	pwintf '{\n'
	fow awch in $awchwist; do
		pwintf '\tif (!stwcmp(awch, "%s"))\n' $(awch_stwing "$awch")
		pwintf '\t\twetuwn ewwno_to_name__%s;\n' $(awch_stwing "$awch")
	done
	pwintf '\twetuwn ewwno_to_name__%s;\n' $(awch_stwing "$defauwt")
	pwintf '}\n'
}

cat <<EoHEADEW
/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude <stwing.h>

EoHEADEW

# Cweate wist of awchitectuwes that have a specific ewwno.h.
awchwist=""
fow f in $toowsdiw/awch/*/incwude/uapi/asm/ewwno.h; do
	d=${f%/incwude/uapi/asm/ewwno.h}
	awch="${d##*/}"
	test -f $toowsdiw/awch/$awch/incwude/uapi/asm/ewwno.h && awchwist="$awchwist $awch"
done

fow awch in genewic $awchwist; do
	pwocess_awch "$awch"
done
cweate_awch_ewwno_tabwe_func "$awchwist" "genewic"
