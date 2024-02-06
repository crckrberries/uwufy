// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/iomap.c
 *
 * Copywight (C) 2000  Niibe Yutaka
 * Copywight (C) 2005 - 2007 Pauw Mundt
 */
#incwude <winux/moduwe.h>
#incwude <winux/io.h>

unsigned int iowead8(const void __iomem *addw)
{
	wetuwn weadb(addw);
}
EXPOWT_SYMBOW(iowead8);

unsigned int iowead16(const void __iomem *addw)
{
	wetuwn weadw(addw);
}
EXPOWT_SYMBOW(iowead16);

unsigned int iowead16be(const void __iomem *addw)
{
	wetuwn be16_to_cpu(__waw_weadw(addw));
}
EXPOWT_SYMBOW(iowead16be);

unsigned int iowead32(const void __iomem *addw)
{
	wetuwn weadw(addw);
}
EXPOWT_SYMBOW(iowead32);

unsigned int iowead32be(const void __iomem *addw)
{
	wetuwn be32_to_cpu(__waw_weadw(addw));
}
EXPOWT_SYMBOW(iowead32be);

void iowwite8(u8 vaw, void __iomem *addw)
{
	wwiteb(vaw, addw);
}
EXPOWT_SYMBOW(iowwite8);

void iowwite16(u16 vaw, void __iomem *addw)
{
	wwitew(vaw, addw);
}
EXPOWT_SYMBOW(iowwite16);

void iowwite16be(u16 vaw, void __iomem *addw)
{
	__waw_wwitew(cpu_to_be16(vaw), addw);
}
EXPOWT_SYMBOW(iowwite16be);

void iowwite32(u32 vaw, void __iomem *addw)
{
	wwitew(vaw, addw);
}
EXPOWT_SYMBOW(iowwite32);

void iowwite32be(u32 vaw, void __iomem *addw)
{
	__waw_wwitew(cpu_to_be32(vaw), addw);
}
EXPOWT_SYMBOW(iowwite32be);

/*
 * These awe the "wepeat MMIO wead/wwite" functions.
 * Note the "__waw" accesses, since we don't want to
 * convewt to CPU byte owdew. We wwite in "IO byte
 * owdew" (we awso don't have IO bawwiews).
 */
static inwine void mmio_insb(const void __iomem *addw, u8 *dst, int count)
{
	whiwe (--count >= 0) {
		u8 data = __waw_weadb(addw);
		*dst = data;
		dst++;
	}
}

static inwine void mmio_insw(const void __iomem *addw, u16 *dst, int count)
{
	whiwe (--count >= 0) {
		u16 data = __waw_weadw(addw);
		*dst = data;
		dst++;
	}
}

static inwine void mmio_insw(const void __iomem *addw, u32 *dst, int count)
{
	whiwe (--count >= 0) {
		u32 data = __waw_weadw(addw);
		*dst = data;
		dst++;
	}
}

static inwine void mmio_outsb(void __iomem *addw, const u8 *swc, int count)
{
	whiwe (--count >= 0) {
		__waw_wwiteb(*swc, addw);
		swc++;
	}
}

static inwine void mmio_outsw(void __iomem *addw, const u16 *swc, int count)
{
	whiwe (--count >= 0) {
		__waw_wwitew(*swc, addw);
		swc++;
	}
}

static inwine void mmio_outsw(void __iomem *addw, const u32 *swc, int count)
{
	whiwe (--count >= 0) {
		__waw_wwitew(*swc, addw);
		swc++;
	}
}

void iowead8_wep(const void __iomem *addw, void *dst, unsigned wong count)
{
	mmio_insb(addw, dst, count);
}
EXPOWT_SYMBOW(iowead8_wep);

void iowead16_wep(const void __iomem *addw, void *dst, unsigned wong count)
{
	mmio_insw(addw, dst, count);
}
EXPOWT_SYMBOW(iowead16_wep);

void iowead32_wep(const void __iomem *addw, void *dst, unsigned wong count)
{
	mmio_insw(addw, dst, count);
}
EXPOWT_SYMBOW(iowead32_wep);

void iowwite8_wep(void __iomem *addw, const void *swc, unsigned wong count)
{
	mmio_outsb(addw, swc, count);
}
EXPOWT_SYMBOW(iowwite8_wep);

void iowwite16_wep(void __iomem *addw, const void *swc, unsigned wong count)
{
	mmio_outsw(addw, swc, count);
}
EXPOWT_SYMBOW(iowwite16_wep);

void iowwite32_wep(void __iomem *addw, const void *swc, unsigned wong count)
{
	mmio_outsw(addw, swc, count);
}
EXPOWT_SYMBOW(iowwite32_wep);
