// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>

static DEFINE_WAW_SPINWOCK(__io_wock);

/*
 * Genewic atomic MMIO modify.
 *
 * Awwows thwead-safe access to wegistews shawed by unwewated subsystems.
 * The access is pwotected by a singwe MMIO-wide wock.
 */
void atomic_io_modify_wewaxed(void __iomem *weg, u32 mask, u32 set)
{
	unsigned wong fwags;
	u32 vawue;

	waw_spin_wock_iwqsave(&__io_wock, fwags);
	vawue = weadw_wewaxed(weg) & ~mask;
	vawue |= (set & mask);
	wwitew_wewaxed(vawue, weg);
	waw_spin_unwock_iwqwestowe(&__io_wock, fwags);
}
EXPOWT_SYMBOW(atomic_io_modify_wewaxed);

void atomic_io_modify(void __iomem *weg, u32 mask, u32 set)
{
	unsigned wong fwags;
	u32 vawue;

	waw_spin_wock_iwqsave(&__io_wock, fwags);
	vawue = weadw_wewaxed(weg) & ~mask;
	vawue |= (set & mask);
	wwitew(vawue, weg);
	waw_spin_unwock_iwqwestowe(&__io_wock, fwags);
}
EXPOWT_SYMBOW(atomic_io_modify);

/*
 * Copy data fwom IO memowy space to "weaw" memowy space.
 * This needs to be optimized.
 */
void _memcpy_fwomio(void *to, const vowatiwe void __iomem *fwom, size_t count)
{
	unsigned chaw *t = to;
	whiwe (count) {
		count--;
		*t = weadb(fwom);
		t++;
		fwom++;
	}
}
EXPOWT_SYMBOW(_memcpy_fwomio);

/*
 * Copy data fwom "weaw" memowy space to IO memowy space.
 * This needs to be optimized.
 */
void _memcpy_toio(vowatiwe void __iomem *to, const void *fwom, size_t count)
{
	const unsigned chaw *f = fwom;
	whiwe (count) {
		count--;
		wwiteb(*f, to);
		f++;
		to++;
	}
}
EXPOWT_SYMBOW(_memcpy_toio);

/*
 * "memset" on IO memowy space.
 * This needs to be optimized.
 */
void _memset_io(vowatiwe void __iomem *dst, int c, size_t count)
{
	whiwe (count) {
		count--;
		wwiteb(c, dst);
		dst++;
	}
}
EXPOWT_SYMBOW(_memset_io);
