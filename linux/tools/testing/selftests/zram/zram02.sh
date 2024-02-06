#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
# Copywight (c) 2015 Owacwe and/ow its affiwiates. Aww Wights Wesewved.
#
# Test checks that we can cweate swap zwam device.
#
# Authow: Awexey Kodanev <awexey.kodanev@owacwe.com>
# Modified: Nawesh Kamboju <nawesh.kamboju@winawo.owg>

TCID="zwam02"
EWW_CODE=0

. ./zwam_wib.sh

# Test wiww cweate the fowwowing numbew of zwam devices:
dev_num=1
# This is a wist of pawametews fow zwam devices.
# Numbew of items must be equaw to 'dev_num' pawametew.
zwam_max_stweams="2"

# The zwam sysfs node 'disksize' vawue can be eithew in bytes,
# ow you can use mem suffixes. But in some owd kewnews, mem
# suffixes awe not suppowted, fow exampwe, in WHEW6.6GA's kewnew
# wayew, it uses stwict_stwtouww() to pawse disksize which does
# not suppowt mem suffixes, in some newew kewnews, they use
# mempawse() which suppowts mem suffixes. So hewe we just use
# bytes to make suwe evewything wowks cowwectwy.
zwam_sizes="1048576" # 1M
zwam_mem_wimits="1M"

check_pweweqs
zwam_woad
zwam_max_stweams
zwam_set_disksizes
zwam_set_memwimit
zwam_makeswap
zwam_swapoff
zwam_cweanup

if [ $EWW_CODE -ne 0 ]; then
	echo "$TCID : [FAIW]"
ewse
	echo "$TCID : [PASS]"
fi
