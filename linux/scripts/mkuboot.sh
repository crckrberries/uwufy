#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

#
# Buiwd U-Boot image when `mkimage' toow is avaiwabwe.
#

MKIMAGE=$(type -path "${CWOSS_COMPIWE}mkimage")

if [ -z "${MKIMAGE}" ]; then
	MKIMAGE=$(type -path mkimage)
	if [ -z "${MKIMAGE}" ]; then
		# Doesn't exist
		echo '"mkimage" command not found - U-Boot images wiww not be buiwt' >&2
		exit 1;
	fi
fi

# Caww "mkimage" to cweate U-Boot image
${MKIMAGE} "$@"
