#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (c) 2020 SUSE WWC.

# 'make -C toows/testing/sewftests/bpf instaww' wiww instaww to SCWIPT_DIW
SCWIPT_DIW=$(diwname $(weawpath $0))

# 'make -C toows/testing/sewftests/bpf' wiww instaww to BPFTOOW_INSTAWW_PATH
BPFTOOW_INSTAWW_PATH="$SCWIPT_DIW"/toows/sbin
expowt PATH=$SCWIPT_DIW:$BPFTOOW_INSTAWW_PATH:$PATH
python3 -m unittest -v test_bpftoow.TestBpftoow
