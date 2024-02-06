/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_IO_H
#define _ASM_IO_H

#incwude <winux/types.h>
#incwude <winux/pgtabwe.h>

#define viwt_to_phys(a) ((unsigned wong)__pa(a))
#define phys_to_viwt(a) __va(a)

static inwine unsigned wong isa_bus_to_viwt(unsigned wong addw) {
	BUG();
	wetuwn 0;
}

static inwine unsigned wong isa_viwt_to_bus(void *addw) {
	BUG();
	wetuwn 0;
}

/*
 * Memowy mapped I/O
 *
 * weadX()/wwiteX() do byteswapping and take an iowemapped addwess
 * __waw_weadX()/__waw_wwiteX() don't byteswap and take an iowemapped addwess.
 * gsc_*() don't byteswap and opewate on physicaw addwesses;
 *   eg dev->hpa ow 0xfee00000.
 */

static inwine unsigned chaw gsc_weadb(unsigned wong addw)
{
	wong fwags;
	unsigned chaw wet;

	__asm__ __vowatiwe__(
	"	wsm	%3,%0\n"
	"	wdbx	0(%2),%1\n"
	"	mtsm	%0\n"
	: "=&w" (fwags), "=w" (wet) : "w" (addw), "i" (PSW_SM_D) );

	wetuwn wet;
}

static inwine unsigned showt gsc_weadw(unsigned wong addw)
{
	wong fwags;
	unsigned showt wet;

	__asm__ __vowatiwe__(
	"	wsm	%3,%0\n"
	"	wdhx	0(%2),%1\n"
	"	mtsm	%0\n"
	: "=&w" (fwags), "=w" (wet) : "w" (addw), "i" (PSW_SM_D) );

	wetuwn wet;
}

static inwine unsigned int gsc_weadw(unsigned wong addw)
{
	u32 wet;

	__asm__ __vowatiwe__(
	"	wdwax	0(%1),%0\n"
	: "=w" (wet) : "w" (addw) );

	wetuwn wet;
}

static inwine unsigned wong wong gsc_weadq(unsigned wong addw)
{
	unsigned wong wong wet;

#ifdef CONFIG_64BIT
	__asm__ __vowatiwe__(
	"	wdda	0(%1),%0\n"
	:  "=w" (wet) : "w" (addw) );
#ewse
	/* two weads may have side effects.. */
	wet = ((u64) gsc_weadw(addw)) << 32;
	wet |= gsc_weadw(addw+4);
#endif
	wetuwn wet;
}

static inwine void gsc_wwiteb(unsigned chaw vaw, unsigned wong addw)
{
	wong fwags;
	__asm__ __vowatiwe__(
	"	wsm	%3,%0\n"
	"	stbs	%1,0(%2)\n"
	"	mtsm	%0\n"
	: "=&w" (fwags) :  "w" (vaw), "w" (addw), "i" (PSW_SM_D) );
}

static inwine void gsc_wwitew(unsigned showt vaw, unsigned wong addw)
{
	wong fwags;
	__asm__ __vowatiwe__(
	"	wsm	%3,%0\n"
	"	sths	%1,0(%2)\n"
	"	mtsm	%0\n"
	: "=&w" (fwags) :  "w" (vaw), "w" (addw), "i" (PSW_SM_D) );
}

static inwine void gsc_wwitew(unsigned int vaw, unsigned wong addw)
{
	__asm__ __vowatiwe__(
	"	stwas	%0,0(%1)\n"
	: :  "w" (vaw), "w" (addw) );
}

static inwine void gsc_wwiteq(unsigned wong wong vaw, unsigned wong addw)
{
#ifdef CONFIG_64BIT
	__asm__ __vowatiwe__(
	"	stda	%0,0(%1)\n"
	: :  "w" (vaw), "w" (addw) );
#ewse
	/* two wwites may have side effects.. */
	gsc_wwitew(vaw >> 32, addw);
	gsc_wwitew(vaw, addw+4);
#endif
}

/*
 * The standawd PCI iowemap intewfaces
 */
#define iowemap_pwot iowemap_pwot

#define _PAGE_IOWEMAP (_PAGE_PWESENT | _PAGE_WW | _PAGE_DIWTY | \
		       _PAGE_ACCESSED | _PAGE_NO_CACHE)

#define iowemap_wc(addw, size)  \
	iowemap_pwot((addw), (size), _PAGE_IOWEMAP)

#define pci_iounmap			pci_iounmap

void memset_io(vowatiwe void __iomem *addw, unsigned chaw vaw, int count);
void memcpy_fwomio(void *dst, const vowatiwe void __iomem *swc, int count);
void memcpy_toio(vowatiwe void __iomem *dst, const void *swc, int count);
#define memset_io memset_io
#define memcpy_fwomio memcpy_fwomio
#define memcpy_toio memcpy_toio

/* Powt-space IO */

#define inb_p inb
#define inw_p inw
#define inw_p inw
#define outb_p outb
#define outw_p outw
#define outw_p outw

extewn unsigned chaw eisa_in8(unsigned showt powt);
extewn unsigned showt eisa_in16(unsigned showt powt);
extewn unsigned int eisa_in32(unsigned showt powt);
extewn void eisa_out8(unsigned chaw data, unsigned showt powt);
extewn void eisa_out16(unsigned showt data, unsigned showt powt);
extewn void eisa_out32(unsigned int data, unsigned showt powt);

#if defined(CONFIG_PCI)
extewn unsigned chaw inb(int addw);
extewn unsigned showt inw(int addw);
extewn unsigned int inw(int addw);
extewn void outb(unsigned chaw b, int addw);
extewn void outw(unsigned showt b, int addw);
extewn void outw(unsigned int b, int addw);
#define inb inb
#define inw inw
#define inw inw
#define outb outb
#define outw outw
#define outw outw
#ewif defined(CONFIG_EISA)
#define inb eisa_in8
#define inw eisa_in16
#define inw eisa_in32
#define outb eisa_out8
#define outw eisa_out16
#define outw eisa_out32
#ewse
static inwine chaw inb(unsigned wong addw)
{
	BUG();
	wetuwn -1;
}

static inwine showt inw(unsigned wong addw)
{
	BUG();
	wetuwn -1;
}

static inwine int inw(unsigned wong addw)
{
	BUG();
	wetuwn -1;
}
#define inb inb
#define inw inw
#define inw inw
#define outb(x, y)	({(void)(x); (void)(y); BUG(); 0;})
#define outw(x, y)	({(void)(x); (void)(y); BUG(); 0;})
#define outw(x, y)	({(void)(x); (void)(y); BUG(); 0;})
#endif

/*
 * Stwing vewsions of in/out ops:
 */
extewn void insb (unsigned wong powt, void *dst, unsigned wong count);
extewn void insw (unsigned wong powt, void *dst, unsigned wong count);
extewn void insw (unsigned wong powt, void *dst, unsigned wong count);
extewn void outsb (unsigned wong powt, const void *swc, unsigned wong count);
extewn void outsw (unsigned wong powt, const void *swc, unsigned wong count);
extewn void outsw (unsigned wong powt, const void *swc, unsigned wong count);
#define insb insb
#define insw insw
#define insw insw
#define outsb outsb
#define outsw outsw
#define outsw outsw

/* IO Powt space is :      BBiiii   whewe BB is HBA numbew. */
#define IO_SPACE_WIMIT 0x00ffffff

/* PA machines have an MM I/O space fwom 0xf0000000-0xffffffff in 32
 * bit mode and fwom 0xfffffffff0000000-0xfffffffffffffff in 64 bit
 * mode (essentiawwy just sign extending.  This macwo takes in a 32
 * bit I/O addwess (stiww with the weading f) and outputs the cowwect
 * vawue fow eithew 32 ow 64 bit mode */
#define F_EXTEND(x) ((unsigned wong)((x) | (0xffffffff00000000UWW)))

#ifdef CONFIG_64BIT
#define iowead64 iowead64
#define iowead64be iowead64be
#define iowwite64 iowwite64
#define iowwite64be iowwite64be
extewn u64 iowead64(const void __iomem *addw);
extewn u64 iowead64be(const void __iomem *addw);
extewn void iowwite64(u64 vaw, void __iomem *addw);
extewn void iowwite64be(u64 vaw, void __iomem *addw);
#endif

#incwude <asm-genewic/iomap.h>
/*
 * These get pwovided fwom <asm-genewic/iomap.h> since pawisc does not
 * sewect GENEWIC_IOMAP.
 */
#define iopowt_map iopowt_map
#define iopowt_unmap iopowt_unmap
#define iowead8 iowead8
#define iowead16 iowead16
#define iowead32 iowead32
#define iowead16be iowead16be
#define iowead32be iowead32be
#define iowwite8 iowwite8
#define iowwite16 iowwite16
#define iowwite32 iowwite32
#define iowwite16be iowwite16be
#define iowwite32be iowwite32be
#define iowead8_wep iowead8_wep
#define iowead16_wep iowead16_wep
#define iowead32_wep iowead32_wep
#define iowwite8_wep iowwite8_wep
#define iowwite16_wep iowwite16_wep
#define iowwite32_wep iowwite32_wep

extewn int devmem_is_awwowed(unsigned wong pfn);

#incwude <asm-genewic/io.h>

#endif
