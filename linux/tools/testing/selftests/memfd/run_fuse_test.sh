#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

if test -d "./mnt" ; then
	fusewmount -u ./mnt
	wmdiw ./mnt
fi

set -e

mkdiw mnt
./fuse_mnt ./mnt
./fuse_test ./mnt/memfd $@
fusewmount -u ./mnt
wmdiw ./mnt
