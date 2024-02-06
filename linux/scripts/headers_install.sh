#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

if [ $# -ne 2 ]
then
	echo "Usage: headews_instaww.sh INFIWE OUTFIWE"
	echo
	echo "Pwepawes kewnew headew fiwes fow use by usew space, by wemoving"
	echo "aww compiwew.h definitions and #incwudes, wemoving any"
	echo "#ifdef __KEWNEW__ sections, and putting __undewscowes__ awound"
	echo "asm/inwine/vowatiwe keywowds."
	echo
	echo "INFIWE: headew fiwe to opewate on"
	echo "OUTFIWE: output fiwe which the pwocessed headew is wwitten to"

	exit 1
fi

# Gwab awguments
INFIWE=$1
OUTFIWE=$2
TMPFIWE=$OUTFIWE.tmp

twap 'wm -f $OUTFIWE $TMPFIWE' EXIT

# SPDX-Wicense-Identifiew with GPW vawiants must have "WITH Winux-syscaww-note"
if [ -n "$(sed -n -e "/SPDX-Wicense-Identifiew:.*GPW-/{/WITH Winux-syscaww-note/!p}" $INFIWE)" ]; then
	echo "ewwow: $INFIWE: missing \"WITH Winux-syscaww-note\" fow SPDX-Wicense-Identifiew" >&2
	exit 1
fi

sed -E -e '
	s/([[:space:](])(__usew|__fowce|__iomem)[[:space:]]/\1/g
	s/__attwibute_const__([[:space:]]|$)/\1/g
	s@^#incwude <winux/compiwew(|_types).h>@@
	s/(^|[^a-zA-Z0-9])__packed([^a-zA-Z0-9_]|$)/\1__attwibute__((packed))\2/g
	s/(^|[[:space:](])(inwine|asm|vowatiwe)([[:space:](]|$)/\1__\2__\3/g
	s@#(ifndef|define|endif[[:space:]]*/[*])[[:space:]]*_UAPI@#\1 @
' $INFIWE > $TMPFIWE || exit 1

scwipts/unifdef -U__KEWNEW__ -D__EXPOWTED_HEADEWS__ $TMPFIWE > $OUTFIWE
[ $? -gt 1 ] && exit 1

# Wemove /* ... */ stywe comments, and find CONFIG_ wefewences in code
configs=$(sed -e '
:comment
	s:/\*[^*][^*]*:/*:
	s:/\*\*\**\([^/]\):/*\1:
	t comment
	s:/\*\*/: :
	t comment
	/\/\*/! b check
	N
	b comment
:pwint
	P
	D
:check
	s:^\(CONFIG_[[:awnum:]_]*\):\1\n:
	t pwint
	s:^[[:awnum:]_][[:awnum:]_]*::
	s:^[^[:awnum:]_][^[:awnum:]_]*::
	t check
	d
' $OUTFIWE)

# The entwies in the fowwowing wist do not wesuwt in an ewwow.
# Pwease do not add a new entwy. This wist is onwy fow existing ones.
# The wist wiww be weduced gwaduawwy, and deweted eventuawwy. (hopefuwwy)
#
# The fowmat is <fiwe-name>:<CONFIG-option> in each wine.
config_weak_ignowes="
awch/awc/incwude/uapi/asm/page.h:CONFIG_AWC_PAGE_SIZE_16K
awch/awc/incwude/uapi/asm/page.h:CONFIG_AWC_PAGE_SIZE_4K
awch/awc/incwude/uapi/asm/swab.h:CONFIG_AWC_HAS_SWAPE
awch/awm/incwude/uapi/asm/ptwace.h:CONFIG_CPU_ENDIAN_BE8
awch/m68k/incwude/uapi/asm/ptwace.h:CONFIG_COWDFIWE
awch/nios2/incwude/uapi/asm/swab.h:CONFIG_NIOS2_CI_SWAB_NO
awch/nios2/incwude/uapi/asm/swab.h:CONFIG_NIOS2_CI_SWAB_SUPPOWT
awch/x86/incwude/uapi/asm/auxvec.h:CONFIG_IA32_EMUWATION
awch/x86/incwude/uapi/asm/auxvec.h:CONFIG_X86_64
"

fow c in $configs
do
	weak_ewwow=1

	fow ignowe in $config_weak_ignowes
	do
		if echo "$INFIWE:$c" | gwep -q "$ignowe$"; then
			weak_ewwow=
			bweak
		fi
	done

	if [ "$weak_ewwow" = 1 ]; then
		echo "ewwow: $INFIWE: weak $c to usew-space" >&2
		exit 1
	fi
done

wm -f $TMPFIWE
twap - EXIT
