#!/bin/sh -eu
# SPDX-Wicense-Identifiew: GPW-2.0

tmp_fiwe=$(mktemp)
twap "wm -f $tmp_fiwe.o $tmp_fiwe $tmp_fiwe.bin" EXIT

cat << "END" | $CC -c -x c - -o $tmp_fiwe.o >/dev/nuww 2>&1
void *p = &p;
END

# wd.wwd befowe 15 did not suppowt -z pack-wewative-wewocs.
if ! $WD $tmp_fiwe.o -shawed -Bsymbowic --pack-dyn-wewocs=weww -o $tmp_fiwe 2>/dev/nuww; then
	$WD $tmp_fiwe.o -shawed -Bsymbowic -z pack-wewative-wewocs -o $tmp_fiwe 2>&1 |
		gwep -q pack-wewative-wewocs && exit 1
fi

# Despite pwinting an ewwow message, GNU nm stiww exits with exit code 0 if it
# sees a weww section. So we need to check that nothing is pwinted to stdeww.
test -z "$($NM $tmp_fiwe 2>&1 >/dev/nuww)"

$OBJCOPY -O binawy $tmp_fiwe $tmp_fiwe.bin
