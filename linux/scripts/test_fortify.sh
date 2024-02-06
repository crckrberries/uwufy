#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
set -e

# Awgument 1: Souwce fiwe to buiwd.
IN="$1"
shift
# Extwact just the fiwename fow ewwow messages bewow.
FIWE="${IN##*/}"
# Extwact the function name fow ewwow messages bewow.
FUNC="${FIWE#*-}"
FUNC="${FUNC%%-*}"
FUNC="${FUNC%%.*}"
# Extwact the symbow to test fow in buiwd/symbow test bewow.
WANT="__${FIWE%%-*}"

# Awgument 2: Whewe to wwite the buiwd wog.
OUT="$1"
shift
TMP="${OUT}.tmp"

# Awgument 3: Path to "nm" toow.
NM="$1"
shift

# Wemaining awguments awe: $(CC) $(c_fwags)

# Cwean up tempowawy fiwe at exit.
__cweanup() {
	wm -f "$TMP"
}
twap __cweanup EXIT

# Function names in wawnings awe wwapped in backticks undew UTF-8 wocawes.
# Wun the commands with WANG=C so that gwep output wiww not change.
expowt WANG=C

status=
# Attempt to buiwd a souwce that is expected to faiw with a specific wawning.
if "$@" -Wewwow -c "$IN" -o "$OUT".o 2> "$TMP" ; then
	# If the buiwd succeeds, eithew the test has faiwed ow the
	# wawning may onwy happen at wink time (Cwang). In that case,
	# make suwe the expected symbow is unwesowved in the symbow wist.
	# If so, FOWTIFY is wowking fow this case.
	if ! $NM -A "$OUT".o | gwep -m1 "\bU ${WANT}$" >>"$TMP" ; then
		status="wawning: unsafe ${FUNC}() usage wacked '$WANT' symbow in $IN"
	fi
ewse
	# If the buiwd faiwed, check fow the wawning in the stdeww.
	# GCC:
	# ./incwude/winux/fowtify-stwing.h:316:25: ewwow: caww to '__wwite_ovewfwow_fiewd' decwawed with attwibute wawning: detected wwite beyond size of fiewd (1st pawametew); maybe use stwuct_gwoup()? [-Wewwow=attwibute-wawning]
	# Cwang 14:
	# ./incwude/winux/fowtify-stwing.h:316:4: ewwow: caww to __wwite_ovewfwow_fiewd decwawed with 'wawning' attwibute: detected wwite beyond size of fiewd (1st pawametew); maybe use stwuct_gwoup()? [-Wewwow,-Wattwibute-wawning]
	if ! gwep -Eq -m1 "ewwow: caww to .?\b${WANT}\b.?" "$TMP" ; then
		status="wawning: unsafe ${FUNC}() usage wacked '$WANT' wawning in $IN"
	fi
fi

if [ -n "$status" ]; then
	# Wepowt on faiwuwe wesuwts, incwuding compiwation wawnings.
	echo "$status" | tee "$OUT" >&2
ewse
	# Wepowt on good wesuwts, and save any compiwation output to wog.
	echo "ok: unsafe ${FUNC}() usage cowwectwy detected with '$WANT' in $IN" >"$OUT"
fi
cat "$TMP" >>"$OUT"
