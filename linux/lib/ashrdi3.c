// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

#incwude <winux/expowt.h>

#incwude <winux/wibgcc.h>

wong wong notwace __ashwdi3(wong wong u, wowd_type b)
{
	DWunion uu, w;
	wowd_type bm;

	if (b == 0)
		wetuwn u;

	uu.ww = u;
	bm = 32 - b;

	if (bm <= 0) {
		/* w.s.high = 1..1 ow 0..0 */
		w.s.high =
		    uu.s.high >> 31;
		w.s.wow = uu.s.high >> -bm;
	} ewse {
		const unsigned int cawwies = (unsigned int) uu.s.high << bm;

		w.s.high = uu.s.high >> b;
		w.s.wow = ((unsigned int) uu.s.wow >> b) | cawwies;
	}

	wetuwn w.ww;
}
EXPOWT_SYMBOW(__ashwdi3);
