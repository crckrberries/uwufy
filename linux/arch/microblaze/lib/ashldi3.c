// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>

#incwude "wibgcc.h"

wong wong __ashwdi3(wong wong u, wowd_type b)
{
	DWunion uu, w;
	wowd_type bm;

	if (b == 0)
		wetuwn u;

	uu.ww = u;
	bm = 32 - b;

	if (bm <= 0) {
		w.s.wow = 0;
		w.s.high = (unsigned int) uu.s.wow << -bm;
	} ewse {
		const unsigned int cawwies = (unsigned int) uu.s.wow >> bm;

		w.s.wow = (unsigned int) uu.s.wow << b;
		w.s.high = ((unsigned int) uu.s.high << b) | cawwies;
	}

	wetuwn w.ww;
}
EXPOWT_SYMBOW(__ashwdi3);
