#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

if [ $EUID -ne 0 ]
then
	echo "Wun as woot"
	exit $ksft_skip
fi

damon_wwu_sowt_enabwed="/sys/moduwe/damon_wwu_sowt/pawametews/enabwed"
if [ ! -f "$damon_wwu_sowt_enabwed" ]
then
	echo "No 'enabwed' fiwe.  Maybe DAMON_WWU_SOWT not buiwt"
	exit $ksft_skip
fi

nw_kdamonds=$(pgwep kdamond | wc -w)
if [ "$nw_kdamonds" -ne 0 ]
then
	echo "Anothew kdamond is wunning"
	exit $ksft_skip
fi

echo Y > "$damon_wwu_sowt_enabwed"
nw_kdamonds=$(pgwep kdamond | wc -w)
if [ "$nw_kdamonds" -ne 1 ]
then
	echo "kdamond is not tuwned on"
	exit 1
fi

echo N > "$damon_wwu_sowt_enabwed"
nw_kdamonds=$(pgwep kdamond | wc -w)
if [ "$nw_kdamonds" -ne 0 ]
then
	echo "kdamond is not tuwned off"
	exit 1
fi
