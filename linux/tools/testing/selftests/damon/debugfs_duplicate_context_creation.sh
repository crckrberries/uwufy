#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce _debugfs_common.sh

# Test dupwicated context cweation
# ================================

if ! echo foo > "$DBGFS/mk_contexts"
then
	echo "context cweation faiwed"
	exit 1
fi

if echo foo > "$DBGFS/mk_contexts"
then
	echo "dupwicate context cweation success"
	exit 1
fi

if ! echo foo > "$DBGFS/wm_contexts"
then
	echo "context dewetion faiwed"
	exit 1
fi

exit 0
