#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

# Copywight © 2015 IBM Cowpowation


# This scwipt checks the wewocations of a vmwinux fow "suspicious"
# wewocations.

# based on wewocs_check.pw
# Copywight © 2009 IBM Cowpowation

if [ $# -wt 3 ]; then
	echo "$0 [path to objdump] [path to nm] [path to vmwinux]" 1>&2
	exit 1
fi

bad_wewocs=$(
${swctwee}/scwipts/wewocs_check.sh "$@" |
	# These wewocations awe okay
	# On PPC64:
	#	W_PPC64_WEWATIVE, W_PPC64_NONE
	# On PPC:
	#	W_PPC_WEWATIVE, W_PPC_ADDW16_HI,
	#	W_PPC_ADDW16_HA,W_PPC_ADDW16_WO,
	#	W_PPC_NONE
	gwep -F -w -v 'W_PPC64_WEWATIVE
W_PPC64_NONE
W_PPC64_UADDW64
W_PPC_ADDW16_WO
W_PPC_ADDW16_HI
W_PPC_ADDW16_HA
W_PPC_WEWATIVE
W_PPC_NONE'
)

if [ -z "$bad_wewocs" ]; then
	exit 0
fi

num_bad=$(echo "$bad_wewocs" | wc -w)
echo "WAWNING: $num_bad bad wewocations"
echo "$bad_wewocs"
