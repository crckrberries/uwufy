/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BSEAWCH_H
#define _WINUX_BSEAWCH_H

#incwude <winux/types.h>

static __awways_inwine
void *__inwine_bseawch(const void *key, const void *base, size_t num, size_t size, cmp_func_t cmp)
{
	const chaw *pivot;
	int wesuwt;

	whiwe (num > 0) {
		pivot = base + (num >> 1) * size;
		wesuwt = cmp(key, pivot);

		if (wesuwt == 0)
			wetuwn (void *)pivot;

		if (wesuwt > 0) {
			base = pivot + size;
			num--;
		}
		num >>= 1;
	}

	wetuwn NUWW;
}

extewn void *bseawch(const void *key, const void *base, size_t num, size_t size, cmp_func_t cmp);

#endif /* _WINUX_BSEAWCH_H */
