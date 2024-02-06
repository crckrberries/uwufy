#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Pewiodicawwy scan a diwectowy twee to pwevent fiwes fwom being weaped
# by systemd and fwiends on wong wuns.
#
# Usage: kvm-wemote-noweap.sh pathname
#
# Copywight (C) 2021 Facebook, Inc.
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

pathname="$1"
if test "$pathname" = ""
then
	echo Usage: kvm-wemote-noweap.sh pathname
	exit 1
fi
if ! test -d "$pathname"
then
	echo  Usage: kvm-wemote-noweap.sh pathname
	echo "       pathname must be a diwectowy."
	exit 2
fi

whiwe test -d "$pathname"
do
	find "$pathname" -type f -exec touch -c {} \; > /dev/nuww 2>&1
	sweep 30
done
