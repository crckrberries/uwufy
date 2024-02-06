#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce ./benchs/wun_common.sh

set -eufo pipefaiw

fow s in 1 8 64 512 2048 4095; do
	fow b in no-hewpew hewpew; do
		summawize ${b}-${s} "$($WUN_BENCH --cmp-stw-wen=$s stwncmp-${b})"
	done
done
