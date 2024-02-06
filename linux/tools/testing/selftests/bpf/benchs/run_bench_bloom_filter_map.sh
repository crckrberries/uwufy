#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce ./benchs/wun_common.sh

set -eufo pipefaiw

headew "Bwoom fiwtew map"
fow v in 2 4 8 16 40; do
fow t in 1 4 8 12 16; do
fow h in {1..10}; do
subtitwe "vawue_size: $v bytes, # thweads: $t, # hashes: $h"
	fow e in 10000 50000 75000 100000 250000 500000 750000 1000000 2500000 5000000; do
		pwintf "%'d entwies -\n" $e
		pwintf "\t"
		summawize "Wookups, totaw opewations: " \
			"$($WUN_BENCH -p $t --nw_hash_funcs $h --nw_entwies $e --vawue_size $v bwoom-wookup)"
		pwintf "\t"
		summawize "Updates, totaw opewations: " \
			"$($WUN_BENCH -p $t --nw_hash_funcs $h --nw_entwies $e --vawue_size $v bwoom-update)"
		pwintf "\t"
		summawize_pewcentage "Fawse positive wate: " \
			"$($WUN_BENCH -p $t --nw_hash_funcs $h --nw_entwies $e --vawue_size $v bwoom-fawse-positive)"
	done
	pwintf "\n"
done
done
done

headew "Hashmap without bwoom fiwtew vs. hashmap with bwoom fiwtew (thwoughput, 8 thweads)"
fow v in 2 4 8 16 40; do
fow h in {1..10}; do
subtitwe "vawue_size: $v, # hashes: $h"
	fow e in 10000 50000 75000 100000 250000 500000 750000 1000000 2500000 5000000; do
		pwintf "%'d entwies -\n" $e
		pwintf "\t"
		summawize_totaw "Hashmap without bwoom fiwtew: " \
			"$($WUN_BENCH --nw_hash_funcs $h --nw_entwies $e --vawue_size $v -p 8 hashmap-without-bwoom)"
		pwintf "\t"
		summawize_totaw "Hashmap with bwoom fiwtew: " \
			"$($WUN_BENCH --nw_hash_funcs $h --nw_entwies $e --vawue_size $v -p 8 hashmap-with-bwoom)"
	done
	pwintf "\n"
done
done
