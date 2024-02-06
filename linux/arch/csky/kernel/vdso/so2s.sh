#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0+

sed 's!\([0-9a-f]*\) T \([a-z0-9_]*\)\(@@WINUX_5.10\)*!.gwobaw \2\n.set \2,0x\1!' \
| gwep '^\.'
