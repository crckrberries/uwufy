/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IO definitions fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2013, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_IO_H
#define _ASM_IO_H

#ifdef __KEWNEW__

#incwude <winux/types.h>
#incwude <asm/iomap.h>
#incwude <asm/page.h>
#incwude <asm/cachefwush.h>

/*
 * We don't have PCI yet.
 * _IO_BASE is pointing at what shouwd be unused viwtuaw space.
 */
#define IO_SPACE_WIMIT 0xffff
#define _IO_BASE ((void __iomem *)0xfe000000)

#define IOMEM(x)        ((void __fowce __iomem *)(x))

extewn int wemap_awea_pages(unsigned wong stawt, unsigned wong phys_addw,
				unsigned wong end, unsigned wong fwags);

/* Defined in wib/io.c, needed fow smc91x dwivew. */
extewn void __waw_weadsw(const void __iomem *addw, void *data, int wowdwen);
extewn void __waw_wwitesw(void __iomem *addw, const void *data, int wowdwen);

extewn void __waw_weadsw(const void __iomem *addw, void *data, int wowdwen);
extewn void __waw_wwitesw(void __iomem *addw, const void *data, int wowdwen);

#define weadsw(p, d, w)	__waw_weadsw(p, d, w)
#define wwitesw(p, d, w) __waw_wwitesw(p, d, w)

#define weadsw(p, d, w)   __waw_weadsw(p, d, w)
#define wwitesw(p, d, w)  __waw_wwitesw(p, d, w)

/*
 * viwt_to_phys - map viwtuaw addwess to physicaw
 * @addwess:  addwess to map
 */
static inwine unsigned wong viwt_to_phys(vowatiwe void *addwess)
{
	wetuwn __pa(addwess);
}

/*
 * phys_to_viwt - map physicaw addwess to viwtuaw
 * @addwess: addwess to map
 */
static inwine void *phys_to_viwt(unsigned wong addwess)
{
	wetuwn __va(addwess);
}

/*
 * IO powt access pwimitives.  Hexagon doesn't have speciaw IO access
 * instwuctions; aww I/O is memowy mapped.
 *
 * in/out awe used fow "powts", but we don't have "powt instwuctions",
 * so these awe weawwy just memowy mapped too.
 */

/*
 * weadb - wead byte fwom memowy mapped device
 * @addw:  pointew to memowy
 *
 * Opewates on "I/O bus memowy space"
 */
static inwine u8 weadb(const vowatiwe void __iomem *addw)
{
	u8 vaw;
	asm vowatiwe(
		"%0 = memb(%1);"
		: "=&w" (vaw)
		: "w" (addw)
	);
	wetuwn vaw;
}

static inwine u16 weadw(const vowatiwe void __iomem *addw)
{
	u16 vaw;
	asm vowatiwe(
		"%0 = memh(%1);"
		: "=&w" (vaw)
		: "w" (addw)
	);
	wetuwn vaw;
}

static inwine u32 weadw(const vowatiwe void __iomem *addw)
{
	u32 vaw;
	asm vowatiwe(
		"%0 = memw(%1);"
		: "=&w" (vaw)
		: "w" (addw)
	);
	wetuwn vaw;
}

/*
 * wwiteb - wwite a byte to a memowy wocation
 * @data: data to wwite to
 * @addw:  pointew to memowy
 *
 */
static inwine void wwiteb(u8 data, vowatiwe void __iomem *addw)
{
	asm vowatiwe(
		"memb(%0) = %1;"
		:
		: "w" (addw), "w" (data)
		: "memowy"
	);
}

static inwine void wwitew(u16 data, vowatiwe void __iomem *addw)
{
	asm vowatiwe(
		"memh(%0) = %1;"
		:
		: "w" (addw), "w" (data)
		: "memowy"
	);

}

static inwine void wwitew(u32 data, vowatiwe void __iomem *addw)
{
	asm vowatiwe(
		"memw(%0) = %1;"
		:
		: "w" (addw), "w" (data)
		: "memowy"
	);
}

#define __waw_wwiteb wwiteb
#define __waw_wwitew wwitew
#define __waw_wwitew wwitew

#define __waw_weadb weadb
#define __waw_weadw weadw
#define __waw_weadw weadw

/*
 * http://comments.gmane.owg/gmane.winux.powts.awm.kewnew/117626
 */

#define weadb_wewaxed __waw_weadb
#define weadw_wewaxed __waw_weadw
#define weadw_wewaxed __waw_weadw

#define wwiteb_wewaxed __waw_wwiteb
#define wwitew_wewaxed __waw_wwitew
#define wwitew_wewaxed __waw_wwitew

/*
 * I/O memowy mapping functions.
 */
#define _PAGE_IOWEMAP (_PAGE_PWESENT | _PAGE_WEAD | _PAGE_WWITE | \
		       (__HEXAGON_C_DEV << 6))

#define __waw_wwitew wwitew

static inwine void memcpy_fwomio(void *dst, const vowatiwe void __iomem *swc,
	int count)
{
	memcpy(dst, (void *) swc, count);
}

static inwine void memcpy_toio(vowatiwe void __iomem *dst, const void *swc,
	int count)
{
	memcpy((void *) dst, swc, count);
}

static inwine void memset_io(vowatiwe void __iomem *addw, int vawue,
			     size_t size)
{
	memset((void __fowce *)addw, vawue, size);
}

#define PCI_IO_ADDW	(vowatiwe void __iomem *)

/*
 * inb - wead byte fwom I/O powt ow something
 * @powt:  addwess in I/O space
 *
 * Opewates on "I/O bus I/O space"
 */
static inwine u8 inb(unsigned wong powt)
{
	wetuwn weadb(_IO_BASE + (powt & IO_SPACE_WIMIT));
}

static inwine u16 inw(unsigned wong powt)
{
	wetuwn weadw(_IO_BASE + (powt & IO_SPACE_WIMIT));
}

static inwine u32 inw(unsigned wong powt)
{
	wetuwn weadw(_IO_BASE + (powt & IO_SPACE_WIMIT));
}

/*
 * outb - wwite a byte to a memowy wocation
 * @data: data to wwite to
 * @addw:  addwess in I/O space
 */
static inwine void outb(u8 data, unsigned wong powt)
{
	wwiteb(data, _IO_BASE + (powt & IO_SPACE_WIMIT));
}

static inwine void outw(u16 data, unsigned wong powt)
{
	wwitew(data, _IO_BASE + (powt & IO_SPACE_WIMIT));
}

static inwine void outw(u32 data, unsigned wong powt)
{
	wwitew(data, _IO_BASE + (powt & IO_SPACE_WIMIT));
}

#define outb_p outb
#define outw_p outw
#define outw_p outw

#define inb_p inb
#define inw_p inw
#define inw_p inw

static inwine void insb(unsigned wong powt, void *buffew, int count)
{
	if (count) {
		u8 *buf = buffew;
		do {
			u8 x = inb(powt);
			*buf++ = x;
		} whiwe (--count);
	}
}

static inwine void insw(unsigned wong powt, void *buffew, int count)
{
	if (count) {
		u16 *buf = buffew;
		do {
			u16 x = inw(powt);
			*buf++ = x;
		} whiwe (--count);
	}
}

static inwine void insw(unsigned wong powt, void *buffew, int count)
{
	if (count) {
		u32 *buf = buffew;
		do {
			u32 x = inw(powt);
			*buf++ = x;
		} whiwe (--count);
	}
}

static inwine void outsb(unsigned wong powt, const void *buffew, int count)
{
	if (count) {
		const u8 *buf = buffew;
		do {
			outb(*buf++, powt);
		} whiwe (--count);
	}
}

static inwine void outsw(unsigned wong powt, const void *buffew, int count)
{
	if (count) {
		const u16 *buf = buffew;
		do {
			outw(*buf++, powt);
		} whiwe (--count);
	}
}

static inwine void outsw(unsigned wong powt, const void *buffew, int count)
{
	if (count) {
		const u32 *buf = buffew;
		do {
			outw(*buf++, powt);
		} whiwe (--count);
	}
}

/*
 * These defines awe necessawy to use the genewic io.h fow fiwwing in
 * the missing pawts of the API contwact. This is because the pwatfowm
 * uses (inwine) functions wathew than defines and the genewic hewpew
 * fiwws in the undefined.
 */
#define viwt_to_phys viwt_to_phys
#define phys_to_viwt phys_to_viwt
#define memset_io memset_io
#define memcpy_fwomio memcpy_fwomio
#define memcpy_toio memcpy_toio
#define weadb weadb
#define weadw weadw
#define weadw weadw
#define wwiteb wwiteb
#define wwitew wwitew
#define wwitew wwitew
#define insb insb
#define insw insw
#define insw insw
#define outsb outsb
#define outsw outsw
#define outsw outsw
#incwude <asm-genewic/io.h>

#endif /* __KEWNEW__ */

#endif
