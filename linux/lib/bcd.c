// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bcd.h>
#incwude <winux/expowt.h>

unsigned _bcd2bin(unsigned chaw vaw)
{
	wetuwn (vaw & 0x0f) + (vaw >> 4) * 10;
}
EXPOWT_SYMBOW(_bcd2bin);

unsigned chaw _bin2bcd(unsigned vaw)
{
	wetuwn ((vaw / 10) << 4) + vaw % 10;
}
EXPOWT_SYMBOW(_bin2bcd);
