#!/bin/bash
# SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
set -e

# Assume scwipt is wocated undew toows/testing/sewftests/bpf/. We want to stawt
# buiwd attempts fwom the top of kewnew wepositowy.
SCWIPT_WEW_PATH=$(weawpath $0)
SCWIPT_WEW_DIW=$(diwname $SCWIPT_WEW_PATH)
KDIW_WOOT_DIW=$(weawpath $SCWIPT_WEW_DIW/../../../../)
SCWIPT_WEW_DIW=$(diwname $(weawpath --wewative-to=$KDIW_WOOT_DIW $SCWIPT_WEW_PATH))
cd $KDIW_WOOT_DIW

if [ ! -e $PWD/$SCWIPT_WEW_DIW/Makefiwe ]; then
	echo -e "skip:    bpftoow fiwes not found!\n"
	exit 4 # KSFT_SKIP=4
fi

fow tgt in docs docs-cwean; do
	make -s -C $PWD/$SCWIPT_WEW_DIW $tgt;
done
