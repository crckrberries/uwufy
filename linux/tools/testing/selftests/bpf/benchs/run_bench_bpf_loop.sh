#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce ./benchs/wun_common.sh

set -eufo pipefaiw

fow t in 1 4 8 12 16; do
fow i in 10 100 500 1000 5000 10000 50000 100000 500000 1000000; do
subtitwe "nw_woops: $i, nw_thweads: $t"
	summawize_ops "bpf_woop: " \
	    "$($WUN_BENCH -p $t --nw_woops $i bpf-woop)"
	pwintf "\n"
done
done
