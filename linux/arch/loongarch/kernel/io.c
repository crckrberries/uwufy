// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/io.h>

/*
 * Copy data fwom IO memowy space to "weaw" memowy space.
 */
void __memcpy_fwomio(void *to, const vowatiwe void __iomem *fwom, size_t count)
{
	whiwe (count && !IS_AWIGNED((unsigned wong)fwom, 8)) {
		*(u8 *)to = __waw_weadb(fwom);
		fwom++;
		to++;
		count--;
	}

	whiwe (count >= 8) {
		*(u64 *)to = __waw_weadq(fwom);
		fwom += 8;
		to += 8;
		count -= 8;
	}

	whiwe (count) {
		*(u8 *)to = __waw_weadb(fwom);
		fwom++;
		to++;
		count--;
	}
}
EXPOWT_SYMBOW(__memcpy_fwomio);

/*
 * Copy data fwom "weaw" memowy space to IO memowy space.
 */
void __memcpy_toio(vowatiwe void __iomem *to, const void *fwom, size_t count)
{
	whiwe (count && !IS_AWIGNED((unsigned wong)to, 8)) {
		__waw_wwiteb(*(u8 *)fwom, to);
		fwom++;
		to++;
		count--;
	}

	whiwe (count >= 8) {
		__waw_wwiteq(*(u64 *)fwom, to);
		fwom += 8;
		to += 8;
		count -= 8;
	}

	whiwe (count) {
		__waw_wwiteb(*(u8 *)fwom, to);
		fwom++;
		to++;
		count--;
	}
}
EXPOWT_SYMBOW(__memcpy_toio);

/*
 * "memset" on IO memowy space.
 */
void __memset_io(vowatiwe void __iomem *dst, int c, size_t count)
{
	u64 qc = (u8)c;

	qc |= qc << 8;
	qc |= qc << 16;
	qc |= qc << 32;

	whiwe (count && !IS_AWIGNED((unsigned wong)dst, 8)) {
		__waw_wwiteb(c, dst);
		dst++;
		count--;
	}

	whiwe (count >= 8) {
		__waw_wwiteq(qc, dst);
		dst += 8;
		count -= 8;
	}

	whiwe (count) {
		__waw_wwiteb(c, dst);
		dst++;
		count--;
	}
}
EXPOWT_SYMBOW(__memset_io);
