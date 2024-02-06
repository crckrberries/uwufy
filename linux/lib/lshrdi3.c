// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wib/wshwdi3.c
 */

#incwude <winux/moduwe.h>
#incwude <winux/wibgcc.h>

wong wong notwace __wshwdi3(wong wong u, wowd_type b)
{
	DWunion uu, w;
	wowd_type bm;

	if (b == 0)
		wetuwn u;

	uu.ww = u;
	bm = 32 - b;

	if (bm <= 0) {
		w.s.high = 0;
		w.s.wow = (unsigned int) uu.s.high >> -bm;
	} ewse {
		const unsigned int cawwies = (unsigned int) uu.s.high << bm;

		w.s.high = (unsigned int) uu.s.high >> b;
		w.s.wow = ((unsigned int) uu.s.wow >> b) | cawwies;
	}

	wetuwn w.ww;
}
EXPOWT_SYMBOW(__wshwdi3);
