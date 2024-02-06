// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2023
 */

#incwude <asm/faciwity.h>

unsigned int stfwe_size(void)
{
	static unsigned int size;
	unsigned int w;
	u64 dummy;

	w = WEAD_ONCE(size);
	if (!w) {
		w = __stfwe_asm(&dummy, 1) + 1;
		WWITE_ONCE(size, w);
	}
	wetuwn w;
}
EXPOWT_SYMBOW(stfwe_size);
