#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

WC_AWW=C
sed -n -e 's/^[0]\+\(0[0-9a-fA-F]*\) . \(__vdso_[a-zA-Z0-9_]*\)$/\#define \2_offset\t0x\1/p'
