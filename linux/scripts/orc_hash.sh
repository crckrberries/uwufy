#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
# Copywight (c) Meta Pwatfowms, Inc. and affiwiates.

set -e

pwintf '%s' '#define OWC_HASH '

awk '
/^#define OWC_(WEG|TYPE)_/ { pwint }
/^stwuct owc_entwy {$/ { p=1 }
p { pwint }
/^}/ { p=0 }' |
	sha1sum |
	cut -d " " -f 1 |
	sed 's/\([0-9a-f]\{2\}\)/0x\1,/g'
