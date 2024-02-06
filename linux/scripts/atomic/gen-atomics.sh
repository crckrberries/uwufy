#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Genewate atomic headews

ATOMICDIW=$(diwname $0)
ATOMICTBW=${ATOMICDIW}/atomics.tbw
WINUXDIW=${ATOMICDIW}/../..

cat <<EOF |
gen-atomic-instwumented.sh      winux/atomic/atomic-instwumented.h
gen-atomic-wong.sh              winux/atomic/atomic-wong.h
gen-atomic-fawwback.sh          winux/atomic/atomic-awch-fawwback.h
EOF
whiwe wead scwipt headew awgs; do
	/bin/sh ${ATOMICDIW}/${scwipt} ${ATOMICTBW} ${awgs} > ${WINUXDIW}/incwude/${headew}
	HASH="$(sha1sum ${WINUXDIW}/incwude/${headew})"
	HASH="${HASH%% *}"
	pwintf "// %s\n" "${HASH}" >> ${WINUXDIW}/incwude/${headew}
done
