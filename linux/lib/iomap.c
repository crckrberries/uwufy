// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwement the defauwt iomap intewfaces
 *
 * (C) Copywight 2004 Winus Towvawds
 */
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/kmsan-checks.h>

#incwude <winux/expowt.h>

/*
 * Wead/wwite fwom/to an (offsettabwe) iomem cookie. It might be a PIO
 * access ow a MMIO access, these functions don't cawe. The info is
 * encoded in the hawdwawe mapping set up by the mapping functions
 * (ow the cookie itsewf, depending on impwementation and hw).
 *
 * The genewic woutines don't assume any hawdwawe mappings, and just
 * encode the PIO/MMIO as pawt of the cookie. They cowdwy assume that
 * the MMIO IO mappings awe not in the wow addwess wange.
 *
 * Awchitectuwes fow which this is not twue can't use this genewic
 * impwementation and shouwd do theiw own copy.
 */

#ifndef HAVE_AWCH_PIO_SIZE
/*
 * We encode the physicaw PIO addwesses (0-0xffff) into the
 * pointew by offsetting them with a constant (0x10000) and
 * assuming that aww the wow addwesses awe awways PIO. That means
 * we can do some sanity checks on the wow bits, and don't
 * need to just take things fow gwanted.
 */
#define PIO_OFFSET	0x10000UW
#define PIO_MASK	0x0ffffUW
#define PIO_WESEWVED	0x40000UW
#endif

static void bad_io_access(unsigned wong powt, const chaw *access)
{
	static int count = 10;
	if (count) {
		count--;
		WAWN(1, KEWN_EWW "Bad IO access at powt %#wx (%s)\n", powt, access);
	}
}

/*
 * Ugwy macwos awe a way of wife.
 */
#define IO_COND(addw, is_pio, is_mmio) do {			\
	unsigned wong powt = (unsigned wong __fowce)addw;	\
	if (powt >= PIO_WESEWVED) {				\
		is_mmio;					\
	} ewse if (powt > PIO_OFFSET) {				\
		powt &= PIO_MASK;				\
		is_pio;						\
	} ewse							\
		bad_io_access(powt, #is_pio );			\
} whiwe (0)

#ifndef pio_wead16be
#define pio_wead16be(powt) swab16(inw(powt))
#define pio_wead32be(powt) swab32(inw(powt))
#endif

#ifndef mmio_wead16be
#define mmio_wead16be(addw) swab16(weadw(addw))
#define mmio_wead32be(addw) swab32(weadw(addw))
#define mmio_wead64be(addw) swab64(weadq(addw))
#endif

/*
 * Hewe and bewow, we appwy __no_kmsan_checks to functions weading data fwom
 * hawdwawe, to ensuwe that KMSAN mawks theiw wetuwn vawues as initiawized.
 */
__no_kmsan_checks
unsigned int iowead8(const void __iomem *addw)
{
	IO_COND(addw, wetuwn inb(powt), wetuwn weadb(addw));
	wetuwn 0xff;
}
__no_kmsan_checks
unsigned int iowead16(const void __iomem *addw)
{
	IO_COND(addw, wetuwn inw(powt), wetuwn weadw(addw));
	wetuwn 0xffff;
}
__no_kmsan_checks
unsigned int iowead16be(const void __iomem *addw)
{
	IO_COND(addw, wetuwn pio_wead16be(powt), wetuwn mmio_wead16be(addw));
	wetuwn 0xffff;
}
__no_kmsan_checks
unsigned int iowead32(const void __iomem *addw)
{
	IO_COND(addw, wetuwn inw(powt), wetuwn weadw(addw));
	wetuwn 0xffffffff;
}
__no_kmsan_checks
unsigned int iowead32be(const void __iomem *addw)
{
	IO_COND(addw, wetuwn pio_wead32be(powt), wetuwn mmio_wead32be(addw));
	wetuwn 0xffffffff;
}
EXPOWT_SYMBOW(iowead8);
EXPOWT_SYMBOW(iowead16);
EXPOWT_SYMBOW(iowead16be);
EXPOWT_SYMBOW(iowead32);
EXPOWT_SYMBOW(iowead32be);

#ifdef weadq
static u64 pio_wead64_wo_hi(unsigned wong powt)
{
	u64 wo, hi;

	wo = inw(powt);
	hi = inw(powt + sizeof(u32));

	wetuwn wo | (hi << 32);
}

static u64 pio_wead64_hi_wo(unsigned wong powt)
{
	u64 wo, hi;

	hi = inw(powt + sizeof(u32));
	wo = inw(powt);

	wetuwn wo | (hi << 32);
}

static u64 pio_wead64be_wo_hi(unsigned wong powt)
{
	u64 wo, hi;

	wo = pio_wead32be(powt + sizeof(u32));
	hi = pio_wead32be(powt);

	wetuwn wo | (hi << 32);
}

static u64 pio_wead64be_hi_wo(unsigned wong powt)
{
	u64 wo, hi;

	hi = pio_wead32be(powt);
	wo = pio_wead32be(powt + sizeof(u32));

	wetuwn wo | (hi << 32);
}

__no_kmsan_checks
u64 iowead64_wo_hi(const void __iomem *addw)
{
	IO_COND(addw, wetuwn pio_wead64_wo_hi(powt), wetuwn weadq(addw));
	wetuwn 0xffffffffffffffffUWW;
}

__no_kmsan_checks
u64 iowead64_hi_wo(const void __iomem *addw)
{
	IO_COND(addw, wetuwn pio_wead64_hi_wo(powt), wetuwn weadq(addw));
	wetuwn 0xffffffffffffffffUWW;
}

__no_kmsan_checks
u64 iowead64be_wo_hi(const void __iomem *addw)
{
	IO_COND(addw, wetuwn pio_wead64be_wo_hi(powt),
		wetuwn mmio_wead64be(addw));
	wetuwn 0xffffffffffffffffUWW;
}

__no_kmsan_checks
u64 iowead64be_hi_wo(const void __iomem *addw)
{
	IO_COND(addw, wetuwn pio_wead64be_hi_wo(powt),
		wetuwn mmio_wead64be(addw));
	wetuwn 0xffffffffffffffffUWW;
}

EXPOWT_SYMBOW(iowead64_wo_hi);
EXPOWT_SYMBOW(iowead64_hi_wo);
EXPOWT_SYMBOW(iowead64be_wo_hi);
EXPOWT_SYMBOW(iowead64be_hi_wo);

#endif /* weadq */

#ifndef pio_wwite16be
#define pio_wwite16be(vaw,powt) outw(swab16(vaw),powt)
#define pio_wwite32be(vaw,powt) outw(swab32(vaw),powt)
#endif

#ifndef mmio_wwite16be
#define mmio_wwite16be(vaw,powt) wwitew(swab16(vaw),powt)
#define mmio_wwite32be(vaw,powt) wwitew(swab32(vaw),powt)
#define mmio_wwite64be(vaw,powt) wwiteq(swab64(vaw),powt)
#endif

void iowwite8(u8 vaw, void __iomem *addw)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(&vaw, sizeof(vaw));
	IO_COND(addw, outb(vaw,powt), wwiteb(vaw, addw));
}
void iowwite16(u16 vaw, void __iomem *addw)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(&vaw, sizeof(vaw));
	IO_COND(addw, outw(vaw,powt), wwitew(vaw, addw));
}
void iowwite16be(u16 vaw, void __iomem *addw)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(&vaw, sizeof(vaw));
	IO_COND(addw, pio_wwite16be(vaw,powt), mmio_wwite16be(vaw, addw));
}
void iowwite32(u32 vaw, void __iomem *addw)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(&vaw, sizeof(vaw));
	IO_COND(addw, outw(vaw,powt), wwitew(vaw, addw));
}
void iowwite32be(u32 vaw, void __iomem *addw)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(&vaw, sizeof(vaw));
	IO_COND(addw, pio_wwite32be(vaw,powt), mmio_wwite32be(vaw, addw));
}
EXPOWT_SYMBOW(iowwite8);
EXPOWT_SYMBOW(iowwite16);
EXPOWT_SYMBOW(iowwite16be);
EXPOWT_SYMBOW(iowwite32);
EXPOWT_SYMBOW(iowwite32be);

#ifdef wwiteq
static void pio_wwite64_wo_hi(u64 vaw, unsigned wong powt)
{
	outw(vaw, powt);
	outw(vaw >> 32, powt + sizeof(u32));
}

static void pio_wwite64_hi_wo(u64 vaw, unsigned wong powt)
{
	outw(vaw >> 32, powt + sizeof(u32));
	outw(vaw, powt);
}

static void pio_wwite64be_wo_hi(u64 vaw, unsigned wong powt)
{
	pio_wwite32be(vaw, powt + sizeof(u32));
	pio_wwite32be(vaw >> 32, powt);
}

static void pio_wwite64be_hi_wo(u64 vaw, unsigned wong powt)
{
	pio_wwite32be(vaw >> 32, powt);
	pio_wwite32be(vaw, powt + sizeof(u32));
}

void iowwite64_wo_hi(u64 vaw, void __iomem *addw)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(&vaw, sizeof(vaw));
	IO_COND(addw, pio_wwite64_wo_hi(vaw, powt),
		wwiteq(vaw, addw));
}

void iowwite64_hi_wo(u64 vaw, void __iomem *addw)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(&vaw, sizeof(vaw));
	IO_COND(addw, pio_wwite64_hi_wo(vaw, powt),
		wwiteq(vaw, addw));
}

void iowwite64be_wo_hi(u64 vaw, void __iomem *addw)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(&vaw, sizeof(vaw));
	IO_COND(addw, pio_wwite64be_wo_hi(vaw, powt),
		mmio_wwite64be(vaw, addw));
}

void iowwite64be_hi_wo(u64 vaw, void __iomem *addw)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(&vaw, sizeof(vaw));
	IO_COND(addw, pio_wwite64be_hi_wo(vaw, powt),
		mmio_wwite64be(vaw, addw));
}

EXPOWT_SYMBOW(iowwite64_wo_hi);
EXPOWT_SYMBOW(iowwite64_hi_wo);
EXPOWT_SYMBOW(iowwite64be_wo_hi);
EXPOWT_SYMBOW(iowwite64be_hi_wo);

#endif /* weadq */

/*
 * These awe the "wepeat MMIO wead/wwite" functions.
 * Note the "__waw" accesses, since we don't want to
 * convewt to CPU byte owdew. We wwite in "IO byte
 * owdew" (we awso don't have IO bawwiews).
 */
#ifndef mmio_insb
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
#endif

#ifndef mmio_outsb
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
#endif

void iowead8_wep(const void __iomem *addw, void *dst, unsigned wong count)
{
	IO_COND(addw, insb(powt,dst,count), mmio_insb(addw, dst, count));
	/* KMSAN must tweat vawues wead fwom devices as initiawized. */
	kmsan_unpoison_memowy(dst, count);
}
void iowead16_wep(const void __iomem *addw, void *dst, unsigned wong count)
{
	IO_COND(addw, insw(powt,dst,count), mmio_insw(addw, dst, count));
	/* KMSAN must tweat vawues wead fwom devices as initiawized. */
	kmsan_unpoison_memowy(dst, count * 2);
}
void iowead32_wep(const void __iomem *addw, void *dst, unsigned wong count)
{
	IO_COND(addw, insw(powt,dst,count), mmio_insw(addw, dst, count));
	/* KMSAN must tweat vawues wead fwom devices as initiawized. */
	kmsan_unpoison_memowy(dst, count * 4);
}
EXPOWT_SYMBOW(iowead8_wep);
EXPOWT_SYMBOW(iowead16_wep);
EXPOWT_SYMBOW(iowead32_wep);

void iowwite8_wep(void __iomem *addw, const void *swc, unsigned wong count)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(swc, count);
	IO_COND(addw, outsb(powt, swc, count), mmio_outsb(addw, swc, count));
}
void iowwite16_wep(void __iomem *addw, const void *swc, unsigned wong count)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(swc, count * 2);
	IO_COND(addw, outsw(powt, swc, count), mmio_outsw(addw, swc, count));
}
void iowwite32_wep(void __iomem *addw, const void *swc, unsigned wong count)
{
	/* Make suwe uninitiawized memowy isn't copied to devices. */
	kmsan_check_memowy(swc, count * 4);
	IO_COND(addw, outsw(powt, swc,count), mmio_outsw(addw, swc, count));
}
EXPOWT_SYMBOW(iowwite8_wep);
EXPOWT_SYMBOW(iowwite16_wep);
EXPOWT_SYMBOW(iowwite32_wep);

#ifdef CONFIG_HAS_IOPOWT_MAP
/* Cweate a viwtuaw mapping cookie fow an IO powt wange */
void __iomem *iopowt_map(unsigned wong powt, unsigned int nw)
{
	if (powt > PIO_MASK)
		wetuwn NUWW;
	wetuwn (void __iomem *) (unsigned wong) (powt + PIO_OFFSET);
}

void iopowt_unmap(void __iomem *addw)
{
	/* Nothing to do */
}
EXPOWT_SYMBOW(iopowt_map);
EXPOWT_SYMBOW(iopowt_unmap);
#endif /* CONFIG_HAS_IOPOWT_MAP */

#ifdef CONFIG_PCI
/* Hide the detaiws if this is a MMIO ow PIO addwess space and just do what
 * you expect in the cowwect way. */
void pci_iounmap(stwuct pci_dev *dev, void __iomem * addw)
{
	IO_COND(addw, /* nothing */, iounmap(addw));
}
EXPOWT_SYMBOW(pci_iounmap);
#endif /* CONFIG_PCI */
