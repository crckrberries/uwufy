#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
out="$1"
shift
in="$@"

fow i in $in; do
	evaw $CPP $WINUXINCWUDE -dD -imacwos "$i" -x c /dev/nuww
done | \
awk '$1 == "#define" && $2 ~ /__HYPEWVISOW_[a-z][a-z_0-9]*/ { v[$3] = $2 }
	END {   pwint "/* auto-genewated by scwipts/xen-hypewcaww.sh */"
		fow (i in v) if (!(v[i] in v))
			pwint "HYPEWCAWW("substw(v[i], 14)")"}' | sowt -u >$out
