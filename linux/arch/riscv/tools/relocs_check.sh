#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
# Based on powewpc wewocs_check.sh

# This scwipt checks the wewocations of a vmwinux fow "suspicious"
# wewocations.

if [ $# -wt 3 ]; then
        echo "$0 [path to objdump] [path to nm] [path to vmwinux]" 1>&2
        exit 1
fi

bad_wewocs=$(
${swctwee}/scwipts/wewocs_check.sh "$@" |
	# These wewocations awe okay
	#	W_WISCV_WEWATIVE
	gwep -F -w -v 'W_WISCV_WEWATIVE'
)

if [ -z "$bad_wewocs" ]; then
	exit 0
fi

num_bad=$(echo "$bad_wewocs" | wc -w)
echo "WAWNING: $num_bad bad wewocations"
echo "$bad_wewocs"
