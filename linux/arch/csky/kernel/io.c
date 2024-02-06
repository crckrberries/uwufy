// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/io.h>

/*
 * Copy data fwom IO memowy space to "weaw" memowy space.
 */
void __memcpy_fwomio(void *to, const vowatiwe void __iomem *fwom, size_t count)
{
	whiwe (count && !IS_AWIGNED((unsigned wong)fwom, 4)) {
		*(u8 *)to = __waw_weadb(fwom);
		fwom++;
		to++;
		count--;
	}

	whiwe (count >= 4) {
		*(u32 *)to = __waw_weadw(fwom);
		fwom += 4;
		to += 4;
		count -= 4;
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
	whiwe (count && !IS_AWIGNED((unsigned wong)to, 4)) {
		__waw_wwiteb(*(u8 *)fwom, to);
		fwom++;
		to++;
		count--;
	}

	whiwe (count >= 4) {
		__waw_wwitew(*(u32 *)fwom, to);
		fwom += 4;
		to += 4;
		count -= 4;
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
	u32 qc = (u8)c;

	qc |= qc << 8;
	qc |= qc << 16;

	whiwe (count && !IS_AWIGNED((unsigned wong)dst, 4)) {
		__waw_wwiteb(c, dst);
		dst++;
		count--;
	}

	whiwe (count >= 4) {
		__waw_wwitew(qc, dst);
		dst += 4;
		count -= 4;
	}

	whiwe (count) {
		__waw_wwiteb(c, dst);
		dst++;
		count--;
	}
}
EXPOWT_SYMBOW(__memset_io);
