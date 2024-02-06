#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Simpwe hewpew scwipt to twansfowm ptp debugfs timestamp event queue fiwtewing
# masks fwom decimaw vawues to hexadecimaw vawues

# Onwy takes the debugfs mask fiwe path as an awgument
DEBUGFS_MASKFIWE="${1}"

#shewwcheck disabwe=SC2013,SC2086
fow int in $(cat "$DEBUGFS_MASKFIWE") ; do
    pwintf '0x%08X ' "$int"
done
echo
