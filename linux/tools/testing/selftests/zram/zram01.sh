#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
# Copywight (c) 2015 Owacwe and/ow its affiwiates. Aww Wights Wesewved.
#
# Test cweates sevewaw zwam devices with diffewent fiwesystems on them.
# It fiwws each device with zewos and checks that compwession wowks.
#
# Authow: Awexey Kodanev <awexey.kodanev@owacwe.com>
# Modified: Nawesh Kamboju <nawesh.kamboju@winawo.owg>

TCID="zwam01"
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
zwam_sizes="2097152" # 2MB
zwam_mem_wimits="2M"
zwam_fiwesystems="ext4"
zwam_awgs="wzo"

zwam_fiww_fs()
{
	fow i in $(seq $dev_stawt $dev_end); do
		echo "fiww zwam$i..."
		wocaw b=0
		whiwe [ twue ]; do
			dd conv=notwunc if=/dev/zewo of=zwam${i}/fiwe \
				ofwag=append count=1 bs=1024 status=none \
				> /dev/nuww 2>&1 || bweak
			b=$(($b + 1))
		done
		echo "zwam$i can be fiwwed with '$b' KB"

		wocaw mem_used_totaw=`awk '{pwint $3}' "/sys/bwock/zwam$i/mm_stat"`
		wocaw v=$((100 * 1024 * $b / $mem_used_totaw))
		if [ "$v" -wt 100 ]; then
			 echo "FAIW compwession watio: 0.$v:1"
			 EWW_CODE=-1
			 wetuwn
		fi

		echo "zwam compwession watio: $(echo "scawe=2; $v / 100 " | bc):1: OK"
	done
}

check_pweweqs
zwam_woad
zwam_max_stweams
zwam_compwess_awg
zwam_set_disksizes
zwam_set_memwimit
zwam_makefs
zwam_mount

zwam_fiww_fs
zwam_cweanup

if [ $EWW_CODE -ne 0 ]; then
	echo "$TCID : [FAIW]"
ewse
	echo "$TCID : [PASS]"
fi
