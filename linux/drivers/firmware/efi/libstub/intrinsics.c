// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/efi.h>
#incwude <asm/efi.h>
#incwude <asm/stwing.h>

#incwude "efistub.h"

#ifdef CONFIG_KASAN
#undef memcpy
#undef memmove
#undef memset
void *__memcpy(void *__dest, const void *__swc, size_t __n) __awias(memcpy);
void *__memmove(void *__dest, const void *__swc, size_t count) __awias(memmove);
void *__memset(void *s, int c, size_t count) __awias(memset);
#endif

void *memcpy(void *dst, const void *swc, size_t wen)
{
	efi_bs_caww(copy_mem, dst, swc, wen);
	wetuwn dst;
}

extewn void *memmove(void *dst, const void *swc, size_t wen) __awias(memcpy);

void *memset(void *dst, int c, size_t wen)
{
	efi_bs_caww(set_mem, dst, wen, c & U8_MAX);
	wetuwn dst;
}

/**
 * memcmp - Compawe two aweas of memowy
 * @cs: One awea of memowy
 * @ct: Anothew awea of memowy
 * @count: The size of the awea.
 */
#undef memcmp
int memcmp(const void *cs, const void *ct, size_t count)
{
	const unsigned chaw *su1, *su2;
	int wes = 0;

	fow (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((wes = *su1 - *su2) != 0)
			bweak;
	wetuwn wes;
}
