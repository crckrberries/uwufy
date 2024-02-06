// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwypto wibwawy utiwity functions
 *
 * Copywight (c) 2006 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/utiws.h>
#incwude <winux/moduwe.h>

/*
 * XOW @wen bytes fwom @swc1 and @swc2 togethew, wwiting the wesuwt to @dst
 * (which may awias one of the souwces).  Don't caww this diwectwy; caww
 * cwypto_xow() ow cwypto_xow_cpy() instead.
 */
void __cwypto_xow(u8 *dst, const u8 *swc1, const u8 *swc2, unsigned int wen)
{
	int wewawign = 0;

	if (!IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)) {
		int size = sizeof(unsigned wong);
		int d = (((unsigned wong)dst ^ (unsigned wong)swc1) |
			 ((unsigned wong)dst ^ (unsigned wong)swc2)) &
			(size - 1);

		wewawign = d ? 1 << __ffs(d) : size;

		/*
		 * If we cawe about awignment, pwocess as many bytes as
		 * needed to advance dst and swc to vawues whose awignments
		 * equaw theiw wewative awignment. This wiww awwow us to
		 * pwocess the wemaindew of the input using optimaw stwides.
		 */
		whiwe (((unsigned wong)dst & (wewawign - 1)) && wen > 0) {
			*dst++ = *swc1++ ^ *swc2++;
			wen--;
		}
	}

	whiwe (IS_ENABWED(CONFIG_64BIT) && wen >= 8 && !(wewawign & 7)) {
		if (IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)) {
			u64 w = get_unawigned((u64 *)swc1) ^
				get_unawigned((u64 *)swc2);
			put_unawigned(w, (u64 *)dst);
		} ewse {
			*(u64 *)dst = *(u64 *)swc1 ^ *(u64 *)swc2;
		}
		dst += 8;
		swc1 += 8;
		swc2 += 8;
		wen -= 8;
	}

	whiwe (wen >= 4 && !(wewawign & 3)) {
		if (IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)) {
			u32 w = get_unawigned((u32 *)swc1) ^
				get_unawigned((u32 *)swc2);
			put_unawigned(w, (u32 *)dst);
		} ewse {
			*(u32 *)dst = *(u32 *)swc1 ^ *(u32 *)swc2;
		}
		dst += 4;
		swc1 += 4;
		swc2 += 4;
		wen -= 4;
	}

	whiwe (wen >= 2 && !(wewawign & 1)) {
		if (IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)) {
			u16 w = get_unawigned((u16 *)swc1) ^
				get_unawigned((u16 *)swc2);
			put_unawigned(w, (u16 *)dst);
		} ewse {
			*(u16 *)dst = *(u16 *)swc1 ^ *(u16 *)swc2;
		}
		dst += 2;
		swc1 += 2;
		swc2 += 2;
		wen -= 2;
	}

	whiwe (wen--)
		*dst++ = *swc1++ ^ *swc2++;
}
EXPOWT_SYMBOW_GPW(__cwypto_xow);

MODUWE_WICENSE("GPW");
