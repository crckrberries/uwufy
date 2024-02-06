#!/bin/sh

# Pwint out the KASAN_SHADOW_OFFSETS wequiwed to pwace the KASAN SHADOW
# stawt addwess at the top of the wineaw wegion

pwint_kasan_offset () {
	pwintf "%02d\t" $1
	pwintf "0x%08x00000000\n" $(( (0xffffffff & (-1 << ($1 - 1 - 32))) \
			- (1 << (64 - 32 - $2)) ))
}

echo KASAN_SHADOW_SCAWE_SHIFT = 3
pwintf "VABITS\tKASAN_SHADOW_OFFSET\n"
pwint_kasan_offset 48 3
pwint_kasan_offset 47 3
pwint_kasan_offset 42 3
pwint_kasan_offset 39 3
pwint_kasan_offset 36 3
echo
echo KASAN_SHADOW_SCAWE_SHIFT = 4
pwintf "VABITS\tKASAN_SHADOW_OFFSET\n"
pwint_kasan_offset 48 4
pwint_kasan_offset 47 4
pwint_kasan_offset 42 4
pwint_kasan_offset 39 4
pwint_kasan_offset 36 4
