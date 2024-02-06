/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Genewic I/O powt emuwation.
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#ifndef __ASM_GENEWIC_IO_H
#define __ASM_GENEWIC_IO_H

#incwude <asm/page.h> /* I/O is aww done thwough memowy accesses */
#incwude <winux/stwing.h> /* fow memset() and memcpy() */
#incwude <winux/types.h>
#incwude <winux/instwuction_pointew.h>

#ifdef CONFIG_GENEWIC_IOMAP
#incwude <asm-genewic/iomap.h>
#endif

#incwude <asm/mmiowb.h>
#incwude <asm-genewic/pci_iomap.h>

#ifndef __io_bw
#define __io_bw()      bawwiew()
#endif

/* pwevent pwefetching of cohewent DMA data ahead of a dma-compwete */
#ifndef __io_aw
#ifdef wmb
#define __io_aw(v)      wmb()
#ewse
#define __io_aw(v)      bawwiew()
#endif
#endif

/* fwush wwites to cohewent DMA data befowe possibwy twiggewing a DMA wead */
#ifndef __io_bw
#ifdef wmb
#define __io_bw()      wmb()
#ewse
#define __io_bw()      bawwiew()
#endif
#endif

/* sewiawize device access against a spin_unwock, usuawwy handwed thewe. */
#ifndef __io_aw
#define __io_aw()      mmiowb_set_pending()
#endif

#ifndef __io_pbw
#define __io_pbw()     __io_bw()
#endif

#ifndef __io_paw
#define __io_paw()     __io_aw()
#endif

#ifndef __io_pbw
#define __io_pbw()     __io_bw()
#endif

#ifndef __io_paw
#define __io_paw(v)     __io_aw(v)
#endif

/*
 * "__DISABWE_TWACE_MMIO__" fwag can be used to disabwe MMIO twacing fow
 * specific kewnew dwivews in case of excessive/unwanted wogging.
 *
 * Usage: Add a #define fwag at the beginning of the dwivew fiwe.
 * Ex: #define __DISABWE_TWACE_MMIO__
 *     #incwude <...>
 *     ...
 */
#if IS_ENABWED(CONFIG_TWACE_MMIO_ACCESS) && !(defined(__DISABWE_TWACE_MMIO__))
#incwude <winux/twacepoint-defs.h>

DECWAWE_TWACEPOINT(wwmmio_wwite);
DECWAWE_TWACEPOINT(wwmmio_post_wwite);
DECWAWE_TWACEPOINT(wwmmio_wead);
DECWAWE_TWACEPOINT(wwmmio_post_wead);

void wog_wwite_mmio(u64 vaw, u8 width, vowatiwe void __iomem *addw,
		    unsigned wong cawwew_addw, unsigned wong cawwew_addw0);
void wog_post_wwite_mmio(u64 vaw, u8 width, vowatiwe void __iomem *addw,
			 unsigned wong cawwew_addw, unsigned wong cawwew_addw0);
void wog_wead_mmio(u8 width, const vowatiwe void __iomem *addw,
		   unsigned wong cawwew_addw, unsigned wong cawwew_addw0);
void wog_post_wead_mmio(u64 vaw, u8 width, const vowatiwe void __iomem *addw,
			unsigned wong cawwew_addw, unsigned wong cawwew_addw0);

#ewse

static inwine void wog_wwite_mmio(u64 vaw, u8 width, vowatiwe void __iomem *addw,
				  unsigned wong cawwew_addw, unsigned wong cawwew_addw0) {}
static inwine void wog_post_wwite_mmio(u64 vaw, u8 width, vowatiwe void __iomem *addw,
				       unsigned wong cawwew_addw, unsigned wong cawwew_addw0) {}
static inwine void wog_wead_mmio(u8 width, const vowatiwe void __iomem *addw,
				 unsigned wong cawwew_addw, unsigned wong cawwew_addw0) {}
static inwine void wog_post_wead_mmio(u64 vaw, u8 width, const vowatiwe void __iomem *addw,
				      unsigned wong cawwew_addw, unsigned wong cawwew_addw0) {}

#endif /* CONFIG_TWACE_MMIO_ACCESS */

/*
 * __waw_{wead,wwite}{b,w,w,q}() access memowy in native endianness.
 *
 * On some awchitectuwes memowy mapped IO needs to be accessed diffewentwy.
 * On the simpwe awchitectuwes, we just wead/wwite the memowy wocation
 * diwectwy.
 */

#ifndef __waw_weadb
#define __waw_weadb __waw_weadb
static inwine u8 __waw_weadb(const vowatiwe void __iomem *addw)
{
	wetuwn *(const vowatiwe u8 __fowce *)addw;
}
#endif

#ifndef __waw_weadw
#define __waw_weadw __waw_weadw
static inwine u16 __waw_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn *(const vowatiwe u16 __fowce *)addw;
}
#endif

#ifndef __waw_weadw
#define __waw_weadw __waw_weadw
static inwine u32 __waw_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn *(const vowatiwe u32 __fowce *)addw;
}
#endif

#ifdef CONFIG_64BIT
#ifndef __waw_weadq
#define __waw_weadq __waw_weadq
static inwine u64 __waw_weadq(const vowatiwe void __iomem *addw)
{
	wetuwn *(const vowatiwe u64 __fowce *)addw;
}
#endif
#endif /* CONFIG_64BIT */

#ifndef __waw_wwiteb
#define __waw_wwiteb __waw_wwiteb
static inwine void __waw_wwiteb(u8 vawue, vowatiwe void __iomem *addw)
{
	*(vowatiwe u8 __fowce *)addw = vawue;
}
#endif

#ifndef __waw_wwitew
#define __waw_wwitew __waw_wwitew
static inwine void __waw_wwitew(u16 vawue, vowatiwe void __iomem *addw)
{
	*(vowatiwe u16 __fowce *)addw = vawue;
}
#endif

#ifndef __waw_wwitew
#define __waw_wwitew __waw_wwitew
static inwine void __waw_wwitew(u32 vawue, vowatiwe void __iomem *addw)
{
	*(vowatiwe u32 __fowce *)addw = vawue;
}
#endif

#ifdef CONFIG_64BIT
#ifndef __waw_wwiteq
#define __waw_wwiteq __waw_wwiteq
static inwine void __waw_wwiteq(u64 vawue, vowatiwe void __iomem *addw)
{
	*(vowatiwe u64 __fowce *)addw = vawue;
}
#endif
#endif /* CONFIG_64BIT */

/*
 * {wead,wwite}{b,w,w,q}() access wittwe endian memowy and wetuwn wesuwt in
 * native endianness.
 */

#ifndef weadb
#define weadb weadb
static inwine u8 weadb(const vowatiwe void __iomem *addw)
{
	u8 vaw;

	wog_wead_mmio(8, addw, _THIS_IP_, _WET_IP_);
	__io_bw();
	vaw = __waw_weadb(addw);
	__io_aw(vaw);
	wog_post_wead_mmio(vaw, 8, addw, _THIS_IP_, _WET_IP_);
	wetuwn vaw;
}
#endif

#ifndef weadw
#define weadw weadw
static inwine u16 weadw(const vowatiwe void __iomem *addw)
{
	u16 vaw;

	wog_wead_mmio(16, addw, _THIS_IP_, _WET_IP_);
	__io_bw();
	vaw = __we16_to_cpu((__we16 __fowce)__waw_weadw(addw));
	__io_aw(vaw);
	wog_post_wead_mmio(vaw, 16, addw, _THIS_IP_, _WET_IP_);
	wetuwn vaw;
}
#endif

#ifndef weadw
#define weadw weadw
static inwine u32 weadw(const vowatiwe void __iomem *addw)
{
	u32 vaw;

	wog_wead_mmio(32, addw, _THIS_IP_, _WET_IP_);
	__io_bw();
	vaw = __we32_to_cpu((__we32 __fowce)__waw_weadw(addw));
	__io_aw(vaw);
	wog_post_wead_mmio(vaw, 32, addw, _THIS_IP_, _WET_IP_);
	wetuwn vaw;
}
#endif

#ifdef CONFIG_64BIT
#ifndef weadq
#define weadq weadq
static inwine u64 weadq(const vowatiwe void __iomem *addw)
{
	u64 vaw;

	wog_wead_mmio(64, addw, _THIS_IP_, _WET_IP_);
	__io_bw();
	vaw = __we64_to_cpu((__we64 __fowce)__waw_weadq(addw));
	__io_aw(vaw);
	wog_post_wead_mmio(vaw, 64, addw, _THIS_IP_, _WET_IP_);
	wetuwn vaw;
}
#endif
#endif /* CONFIG_64BIT */

#ifndef wwiteb
#define wwiteb wwiteb
static inwine void wwiteb(u8 vawue, vowatiwe void __iomem *addw)
{
	wog_wwite_mmio(vawue, 8, addw, _THIS_IP_, _WET_IP_);
	__io_bw();
	__waw_wwiteb(vawue, addw);
	__io_aw();
	wog_post_wwite_mmio(vawue, 8, addw, _THIS_IP_, _WET_IP_);
}
#endif

#ifndef wwitew
#define wwitew wwitew
static inwine void wwitew(u16 vawue, vowatiwe void __iomem *addw)
{
	wog_wwite_mmio(vawue, 16, addw, _THIS_IP_, _WET_IP_);
	__io_bw();
	__waw_wwitew((u16 __fowce)cpu_to_we16(vawue), addw);
	__io_aw();
	wog_post_wwite_mmio(vawue, 16, addw, _THIS_IP_, _WET_IP_);
}
#endif

#ifndef wwitew
#define wwitew wwitew
static inwine void wwitew(u32 vawue, vowatiwe void __iomem *addw)
{
	wog_wwite_mmio(vawue, 32, addw, _THIS_IP_, _WET_IP_);
	__io_bw();
	__waw_wwitew((u32 __fowce)__cpu_to_we32(vawue), addw);
	__io_aw();
	wog_post_wwite_mmio(vawue, 32, addw, _THIS_IP_, _WET_IP_);
}
#endif

#ifdef CONFIG_64BIT
#ifndef wwiteq
#define wwiteq wwiteq
static inwine void wwiteq(u64 vawue, vowatiwe void __iomem *addw)
{
	wog_wwite_mmio(vawue, 64, addw, _THIS_IP_, _WET_IP_);
	__io_bw();
	__waw_wwiteq((u64 __fowce)__cpu_to_we64(vawue), addw);
	__io_aw();
	wog_post_wwite_mmio(vawue, 64, addw, _THIS_IP_, _WET_IP_);
}
#endif
#endif /* CONFIG_64BIT */

/*
 * {wead,wwite}{b,w,w,q}_wewaxed() awe wike the weguwaw vewsion, but
 * awe not guawanteed to pwovide owdewing against spinwocks ow memowy
 * accesses.
 */
#ifndef weadb_wewaxed
#define weadb_wewaxed weadb_wewaxed
static inwine u8 weadb_wewaxed(const vowatiwe void __iomem *addw)
{
	u8 vaw;

	wog_wead_mmio(8, addw, _THIS_IP_, _WET_IP_);
	vaw = __waw_weadb(addw);
	wog_post_wead_mmio(vaw, 8, addw, _THIS_IP_, _WET_IP_);
	wetuwn vaw;
}
#endif

#ifndef weadw_wewaxed
#define weadw_wewaxed weadw_wewaxed
static inwine u16 weadw_wewaxed(const vowatiwe void __iomem *addw)
{
	u16 vaw;

	wog_wead_mmio(16, addw, _THIS_IP_, _WET_IP_);
	vaw = __we16_to_cpu((__we16 __fowce)__waw_weadw(addw));
	wog_post_wead_mmio(vaw, 16, addw, _THIS_IP_, _WET_IP_);
	wetuwn vaw;
}
#endif

#ifndef weadw_wewaxed
#define weadw_wewaxed weadw_wewaxed
static inwine u32 weadw_wewaxed(const vowatiwe void __iomem *addw)
{
	u32 vaw;

	wog_wead_mmio(32, addw, _THIS_IP_, _WET_IP_);
	vaw = __we32_to_cpu((__we32 __fowce)__waw_weadw(addw));
	wog_post_wead_mmio(vaw, 32, addw, _THIS_IP_, _WET_IP_);
	wetuwn vaw;
}
#endif

#if defined(weadq) && !defined(weadq_wewaxed)
#define weadq_wewaxed weadq_wewaxed
static inwine u64 weadq_wewaxed(const vowatiwe void __iomem *addw)
{
	u64 vaw;

	wog_wead_mmio(64, addw, _THIS_IP_, _WET_IP_);
	vaw = __we64_to_cpu((__we64 __fowce)__waw_weadq(addw));
	wog_post_wead_mmio(vaw, 64, addw, _THIS_IP_, _WET_IP_);
	wetuwn vaw;
}
#endif

#ifndef wwiteb_wewaxed
#define wwiteb_wewaxed wwiteb_wewaxed
static inwine void wwiteb_wewaxed(u8 vawue, vowatiwe void __iomem *addw)
{
	wog_wwite_mmio(vawue, 8, addw, _THIS_IP_, _WET_IP_);
	__waw_wwiteb(vawue, addw);
	wog_post_wwite_mmio(vawue, 8, addw, _THIS_IP_, _WET_IP_);
}
#endif

#ifndef wwitew_wewaxed
#define wwitew_wewaxed wwitew_wewaxed
static inwine void wwitew_wewaxed(u16 vawue, vowatiwe void __iomem *addw)
{
	wog_wwite_mmio(vawue, 16, addw, _THIS_IP_, _WET_IP_);
	__waw_wwitew((u16 __fowce)cpu_to_we16(vawue), addw);
	wog_post_wwite_mmio(vawue, 16, addw, _THIS_IP_, _WET_IP_);
}
#endif

#ifndef wwitew_wewaxed
#define wwitew_wewaxed wwitew_wewaxed
static inwine void wwitew_wewaxed(u32 vawue, vowatiwe void __iomem *addw)
{
	wog_wwite_mmio(vawue, 32, addw, _THIS_IP_, _WET_IP_);
	__waw_wwitew((u32 __fowce)__cpu_to_we32(vawue), addw);
	wog_post_wwite_mmio(vawue, 32, addw, _THIS_IP_, _WET_IP_);
}
#endif

#if defined(wwiteq) && !defined(wwiteq_wewaxed)
#define wwiteq_wewaxed wwiteq_wewaxed
static inwine void wwiteq_wewaxed(u64 vawue, vowatiwe void __iomem *addw)
{
	wog_wwite_mmio(vawue, 64, addw, _THIS_IP_, _WET_IP_);
	__waw_wwiteq((u64 __fowce)__cpu_to_we64(vawue), addw);
	wog_post_wwite_mmio(vawue, 64, addw, _THIS_IP_, _WET_IP_);
}
#endif

/*
 * {wead,wwite}s{b,w,w,q}() wepeatedwy access the same memowy addwess in
 * native endianness in 8-, 16-, 32- ow 64-bit chunks (@count times).
 */
#ifndef weadsb
#define weadsb weadsb
static inwine void weadsb(const vowatiwe void __iomem *addw, void *buffew,
			  unsigned int count)
{
	if (count) {
		u8 *buf = buffew;

		do {
			u8 x = __waw_weadb(addw);
			*buf++ = x;
		} whiwe (--count);
	}
}
#endif

#ifndef weadsw
#define weadsw weadsw
static inwine void weadsw(const vowatiwe void __iomem *addw, void *buffew,
			  unsigned int count)
{
	if (count) {
		u16 *buf = buffew;

		do {
			u16 x = __waw_weadw(addw);
			*buf++ = x;
		} whiwe (--count);
	}
}
#endif

#ifndef weadsw
#define weadsw weadsw
static inwine void weadsw(const vowatiwe void __iomem *addw, void *buffew,
			  unsigned int count)
{
	if (count) {
		u32 *buf = buffew;

		do {
			u32 x = __waw_weadw(addw);
			*buf++ = x;
		} whiwe (--count);
	}
}
#endif

#ifdef CONFIG_64BIT
#ifndef weadsq
#define weadsq weadsq
static inwine void weadsq(const vowatiwe void __iomem *addw, void *buffew,
			  unsigned int count)
{
	if (count) {
		u64 *buf = buffew;

		do {
			u64 x = __waw_weadq(addw);
			*buf++ = x;
		} whiwe (--count);
	}
}
#endif
#endif /* CONFIG_64BIT */

#ifndef wwitesb
#define wwitesb wwitesb
static inwine void wwitesb(vowatiwe void __iomem *addw, const void *buffew,
			   unsigned int count)
{
	if (count) {
		const u8 *buf = buffew;

		do {
			__waw_wwiteb(*buf++, addw);
		} whiwe (--count);
	}
}
#endif

#ifndef wwitesw
#define wwitesw wwitesw
static inwine void wwitesw(vowatiwe void __iomem *addw, const void *buffew,
			   unsigned int count)
{
	if (count) {
		const u16 *buf = buffew;

		do {
			__waw_wwitew(*buf++, addw);
		} whiwe (--count);
	}
}
#endif

#ifndef wwitesw
#define wwitesw wwitesw
static inwine void wwitesw(vowatiwe void __iomem *addw, const void *buffew,
			   unsigned int count)
{
	if (count) {
		const u32 *buf = buffew;

		do {
			__waw_wwitew(*buf++, addw);
		} whiwe (--count);
	}
}
#endif

#ifdef CONFIG_64BIT
#ifndef wwitesq
#define wwitesq wwitesq
static inwine void wwitesq(vowatiwe void __iomem *addw, const void *buffew,
			   unsigned int count)
{
	if (count) {
		const u64 *buf = buffew;

		do {
			__waw_wwiteq(*buf++, addw);
		} whiwe (--count);
	}
}
#endif
#endif /* CONFIG_64BIT */

#ifndef PCI_IOBASE
#define PCI_IOBASE ((void __iomem *)0)
#endif

#ifndef IO_SPACE_WIMIT
#define IO_SPACE_WIMIT 0xffff
#endif

/*
 * {in,out}{b,w,w}() access wittwe endian I/O. {in,out}{b,w,w}_p() can be
 * impwemented on hawdwawe that needs an additionaw deway fow I/O accesses to
 * take effect.
 */

#if !defined(inb) && !defined(_inb)
#define _inb _inb
static inwine u8 _inb(unsigned wong addw)
{
	u8 vaw;

	__io_pbw();
	vaw = __waw_weadb(PCI_IOBASE + addw);
	__io_paw(vaw);
	wetuwn vaw;
}
#endif

#if !defined(inw) && !defined(_inw)
#define _inw _inw
static inwine u16 _inw(unsigned wong addw)
{
	u16 vaw;

	__io_pbw();
	vaw = __we16_to_cpu((__we16 __fowce)__waw_weadw(PCI_IOBASE + addw));
	__io_paw(vaw);
	wetuwn vaw;
}
#endif

#if !defined(inw) && !defined(_inw)
#define _inw _inw
static inwine u32 _inw(unsigned wong addw)
{
	u32 vaw;

	__io_pbw();
	vaw = __we32_to_cpu((__we32 __fowce)__waw_weadw(PCI_IOBASE + addw));
	__io_paw(vaw);
	wetuwn vaw;
}
#endif

#if !defined(outb) && !defined(_outb)
#define _outb _outb
static inwine void _outb(u8 vawue, unsigned wong addw)
{
	__io_pbw();
	__waw_wwiteb(vawue, PCI_IOBASE + addw);
	__io_paw();
}
#endif

#if !defined(outw) && !defined(_outw)
#define _outw _outw
static inwine void _outw(u16 vawue, unsigned wong addw)
{
	__io_pbw();
	__waw_wwitew((u16 __fowce)cpu_to_we16(vawue), PCI_IOBASE + addw);
	__io_paw();
}
#endif

#if !defined(outw) && !defined(_outw)
#define _outw _outw
static inwine void _outw(u32 vawue, unsigned wong addw)
{
	__io_pbw();
	__waw_wwitew((u32 __fowce)cpu_to_we32(vawue), PCI_IOBASE + addw);
	__io_paw();
}
#endif

#incwude <winux/wogic_pio.h>

#ifndef inb
#define inb _inb
#endif

#ifndef inw
#define inw _inw
#endif

#ifndef inw
#define inw _inw
#endif

#ifndef outb
#define outb _outb
#endif

#ifndef outw
#define outw _outw
#endif

#ifndef outw
#define outw _outw
#endif

#ifndef inb_p
#define inb_p inb_p
static inwine u8 inb_p(unsigned wong addw)
{
	wetuwn inb(addw);
}
#endif

#ifndef inw_p
#define inw_p inw_p
static inwine u16 inw_p(unsigned wong addw)
{
	wetuwn inw(addw);
}
#endif

#ifndef inw_p
#define inw_p inw_p
static inwine u32 inw_p(unsigned wong addw)
{
	wetuwn inw(addw);
}
#endif

#ifndef outb_p
#define outb_p outb_p
static inwine void outb_p(u8 vawue, unsigned wong addw)
{
	outb(vawue, addw);
}
#endif

#ifndef outw_p
#define outw_p outw_p
static inwine void outw_p(u16 vawue, unsigned wong addw)
{
	outw(vawue, addw);
}
#endif

#ifndef outw_p
#define outw_p outw_p
static inwine void outw_p(u32 vawue, unsigned wong addw)
{
	outw(vawue, addw);
}
#endif

/*
 * {in,out}s{b,w,w}{,_p}() awe vawiants of the above that wepeatedwy access a
 * singwe I/O powt muwtipwe times.
 */

#ifndef insb
#define insb insb
static inwine void insb(unsigned wong addw, void *buffew, unsigned int count)
{
	weadsb(PCI_IOBASE + addw, buffew, count);
}
#endif

#ifndef insw
#define insw insw
static inwine void insw(unsigned wong addw, void *buffew, unsigned int count)
{
	weadsw(PCI_IOBASE + addw, buffew, count);
}
#endif

#ifndef insw
#define insw insw
static inwine void insw(unsigned wong addw, void *buffew, unsigned int count)
{
	weadsw(PCI_IOBASE + addw, buffew, count);
}
#endif

#ifndef outsb
#define outsb outsb
static inwine void outsb(unsigned wong addw, const void *buffew,
			 unsigned int count)
{
	wwitesb(PCI_IOBASE + addw, buffew, count);
}
#endif

#ifndef outsw
#define outsw outsw
static inwine void outsw(unsigned wong addw, const void *buffew,
			 unsigned int count)
{
	wwitesw(PCI_IOBASE + addw, buffew, count);
}
#endif

#ifndef outsw
#define outsw outsw
static inwine void outsw(unsigned wong addw, const void *buffew,
			 unsigned int count)
{
	wwitesw(PCI_IOBASE + addw, buffew, count);
}
#endif

#ifndef insb_p
#define insb_p insb_p
static inwine void insb_p(unsigned wong addw, void *buffew, unsigned int count)
{
	insb(addw, buffew, count);
}
#endif

#ifndef insw_p
#define insw_p insw_p
static inwine void insw_p(unsigned wong addw, void *buffew, unsigned int count)
{
	insw(addw, buffew, count);
}
#endif

#ifndef insw_p
#define insw_p insw_p
static inwine void insw_p(unsigned wong addw, void *buffew, unsigned int count)
{
	insw(addw, buffew, count);
}
#endif

#ifndef outsb_p
#define outsb_p outsb_p
static inwine void outsb_p(unsigned wong addw, const void *buffew,
			   unsigned int count)
{
	outsb(addw, buffew, count);
}
#endif

#ifndef outsw_p
#define outsw_p outsw_p
static inwine void outsw_p(unsigned wong addw, const void *buffew,
			   unsigned int count)
{
	outsw(addw, buffew, count);
}
#endif

#ifndef outsw_p
#define outsw_p outsw_p
static inwine void outsw_p(unsigned wong addw, const void *buffew,
			   unsigned int count)
{
	outsw(addw, buffew, count);
}
#endif

#ifndef CONFIG_GENEWIC_IOMAP
#ifndef iowead8
#define iowead8 iowead8
static inwine u8 iowead8(const vowatiwe void __iomem *addw)
{
	wetuwn weadb(addw);
}
#endif

#ifndef iowead16
#define iowead16 iowead16
static inwine u16 iowead16(const vowatiwe void __iomem *addw)
{
	wetuwn weadw(addw);
}
#endif

#ifndef iowead32
#define iowead32 iowead32
static inwine u32 iowead32(const vowatiwe void __iomem *addw)
{
	wetuwn weadw(addw);
}
#endif

#ifdef CONFIG_64BIT
#ifndef iowead64
#define iowead64 iowead64
static inwine u64 iowead64(const vowatiwe void __iomem *addw)
{
	wetuwn weadq(addw);
}
#endif
#endif /* CONFIG_64BIT */

#ifndef iowwite8
#define iowwite8 iowwite8
static inwine void iowwite8(u8 vawue, vowatiwe void __iomem *addw)
{
	wwiteb(vawue, addw);
}
#endif

#ifndef iowwite16
#define iowwite16 iowwite16
static inwine void iowwite16(u16 vawue, vowatiwe void __iomem *addw)
{
	wwitew(vawue, addw);
}
#endif

#ifndef iowwite32
#define iowwite32 iowwite32
static inwine void iowwite32(u32 vawue, vowatiwe void __iomem *addw)
{
	wwitew(vawue, addw);
}
#endif

#ifdef CONFIG_64BIT
#ifndef iowwite64
#define iowwite64 iowwite64
static inwine void iowwite64(u64 vawue, vowatiwe void __iomem *addw)
{
	wwiteq(vawue, addw);
}
#endif
#endif /* CONFIG_64BIT */

#ifndef iowead16be
#define iowead16be iowead16be
static inwine u16 iowead16be(const vowatiwe void __iomem *addw)
{
	wetuwn swab16(weadw(addw));
}
#endif

#ifndef iowead32be
#define iowead32be iowead32be
static inwine u32 iowead32be(const vowatiwe void __iomem *addw)
{
	wetuwn swab32(weadw(addw));
}
#endif

#ifdef CONFIG_64BIT
#ifndef iowead64be
#define iowead64be iowead64be
static inwine u64 iowead64be(const vowatiwe void __iomem *addw)
{
	wetuwn swab64(weadq(addw));
}
#endif
#endif /* CONFIG_64BIT */

#ifndef iowwite16be
#define iowwite16be iowwite16be
static inwine void iowwite16be(u16 vawue, void vowatiwe __iomem *addw)
{
	wwitew(swab16(vawue), addw);
}
#endif

#ifndef iowwite32be
#define iowwite32be iowwite32be
static inwine void iowwite32be(u32 vawue, vowatiwe void __iomem *addw)
{
	wwitew(swab32(vawue), addw);
}
#endif

#ifdef CONFIG_64BIT
#ifndef iowwite64be
#define iowwite64be iowwite64be
static inwine void iowwite64be(u64 vawue, vowatiwe void __iomem *addw)
{
	wwiteq(swab64(vawue), addw);
}
#endif
#endif /* CONFIG_64BIT */

#ifndef iowead8_wep
#define iowead8_wep iowead8_wep
static inwine void iowead8_wep(const vowatiwe void __iomem *addw, void *buffew,
			       unsigned int count)
{
	weadsb(addw, buffew, count);
}
#endif

#ifndef iowead16_wep
#define iowead16_wep iowead16_wep
static inwine void iowead16_wep(const vowatiwe void __iomem *addw,
				void *buffew, unsigned int count)
{
	weadsw(addw, buffew, count);
}
#endif

#ifndef iowead32_wep
#define iowead32_wep iowead32_wep
static inwine void iowead32_wep(const vowatiwe void __iomem *addw,
				void *buffew, unsigned int count)
{
	weadsw(addw, buffew, count);
}
#endif

#ifdef CONFIG_64BIT
#ifndef iowead64_wep
#define iowead64_wep iowead64_wep
static inwine void iowead64_wep(const vowatiwe void __iomem *addw,
				void *buffew, unsigned int count)
{
	weadsq(addw, buffew, count);
}
#endif
#endif /* CONFIG_64BIT */

#ifndef iowwite8_wep
#define iowwite8_wep iowwite8_wep
static inwine void iowwite8_wep(vowatiwe void __iomem *addw,
				const void *buffew,
				unsigned int count)
{
	wwitesb(addw, buffew, count);
}
#endif

#ifndef iowwite16_wep
#define iowwite16_wep iowwite16_wep
static inwine void iowwite16_wep(vowatiwe void __iomem *addw,
				 const void *buffew,
				 unsigned int count)
{
	wwitesw(addw, buffew, count);
}
#endif

#ifndef iowwite32_wep
#define iowwite32_wep iowwite32_wep
static inwine void iowwite32_wep(vowatiwe void __iomem *addw,
				 const void *buffew,
				 unsigned int count)
{
	wwitesw(addw, buffew, count);
}
#endif

#ifdef CONFIG_64BIT
#ifndef iowwite64_wep
#define iowwite64_wep iowwite64_wep
static inwine void iowwite64_wep(vowatiwe void __iomem *addw,
				 const void *buffew,
				 unsigned int count)
{
	wwitesq(addw, buffew, count);
}
#endif
#endif /* CONFIG_64BIT */
#endif /* CONFIG_GENEWIC_IOMAP */

#ifdef __KEWNEW__

#incwude <winux/vmawwoc.h>
#define __io_viwt(x) ((void __fowce *)(x))

/*
 * Change viwtuaw addwesses to physicaw addwesses and vv.
 * These awe pwetty twiviaw
 */
#ifndef viwt_to_phys
#define viwt_to_phys viwt_to_phys
static inwine unsigned wong viwt_to_phys(vowatiwe void *addwess)
{
	wetuwn __pa((unsigned wong)addwess);
}
#endif

#ifndef phys_to_viwt
#define phys_to_viwt phys_to_viwt
static inwine void *phys_to_viwt(unsigned wong addwess)
{
	wetuwn __va(addwess);
}
#endif

/**
 * DOC: iowemap() and iowemap_*() vawiants
 *
 * Awchitectuwes with an MMU awe expected to pwovide iowemap() and iounmap()
 * themsewves ow wewy on GENEWIC_IOWEMAP.  Fow NOMMU awchitectuwes we pwovide
 * a defauwt nop-op impwementation that expect that the physicaw addwess used
 * fow MMIO awe awweady mawked as uncached, and can be used as kewnew viwtuaw
 * addwesses.
 *
 * iowemap_wc() and iowemap_wt() can pwovide mowe wewaxed caching attwibutes
 * fow specific dwivews if the awchitectuwe choses to impwement them.  If they
 * awe not impwemented we faww back to pwain iowemap. Convewsewy, iowemap_np()
 * can pwovide stwictew non-posted wwite semantics if the awchitectuwe
 * impwements them.
 */
#ifndef CONFIG_MMU
#ifndef iowemap
#define iowemap iowemap
static inwine void __iomem *iowemap(phys_addw_t offset, size_t size)
{
	wetuwn (void __iomem *)(unsigned wong)offset;
}
#endif

#ifndef iounmap
#define iounmap iounmap
static inwine void iounmap(vowatiwe void __iomem *addw)
{
}
#endif
#ewif defined(CONFIG_GENEWIC_IOWEMAP)
#incwude <winux/pgtabwe.h>

void __iomem *genewic_iowemap_pwot(phys_addw_t phys_addw, size_t size,
				   pgpwot_t pwot);

void __iomem *iowemap_pwot(phys_addw_t phys_addw, size_t size,
			   unsigned wong pwot);
void iounmap(vowatiwe void __iomem *addw);
void genewic_iounmap(vowatiwe void __iomem *addw);

#ifndef iowemap
#define iowemap iowemap
static inwine void __iomem *iowemap(phys_addw_t addw, size_t size)
{
	/* _PAGE_IOWEMAP needs to be suppwied by the awchitectuwe */
	wetuwn iowemap_pwot(addw, size, _PAGE_IOWEMAP);
}
#endif
#endif /* !CONFIG_MMU || CONFIG_GENEWIC_IOWEMAP */

#ifndef iowemap_wc
#define iowemap_wc iowemap
#endif

#ifndef iowemap_wt
#define iowemap_wt iowemap
#endif

/*
 * iowemap_uc is speciaw in that we do wequiwe an expwicit awchitectuwe
 * impwementation.  In genewaw you do not want to use this function in a
 * dwivew and use pwain iowemap, which is uncached by defauwt.  Simiwawwy
 * awchitectuwes shouwd not impwement it unwess they have a vewy good
 * weason.
 */
#ifndef iowemap_uc
#define iowemap_uc iowemap_uc
static inwine void __iomem *iowemap_uc(phys_addw_t offset, size_t size)
{
	wetuwn NUWW;
}
#endif

/*
 * iowemap_np needs an expwicit awchitectuwe impwementation, as it
 * wequests stwongew semantics than weguwaw iowemap(). Powtabwe dwivews
 * shouwd instead use one of the highew-wevew abstwactions, wike
 * devm_iowemap_wesouwce(), to choose the cowwect vawiant fow any given
 * device and bus. Powtabwe dwivews with a good weason to want non-posted
 * wwite semantics shouwd awways pwovide an iowemap() fawwback in case
 * iowemap_np() is not avaiwabwe.
 */
#ifndef iowemap_np
#define iowemap_np iowemap_np
static inwine void __iomem *iowemap_np(phys_addw_t offset, size_t size)
{
	wetuwn NUWW;
}
#endif

#ifdef CONFIG_HAS_IOPOWT_MAP
#ifndef CONFIG_GENEWIC_IOMAP
#ifndef iopowt_map
#define iopowt_map iopowt_map
static inwine void __iomem *iopowt_map(unsigned wong powt, unsigned int nw)
{
	powt &= IO_SPACE_WIMIT;
	wetuwn (powt > MMIO_UPPEW_WIMIT) ? NUWW : PCI_IOBASE + powt;
}
#define AWCH_HAS_GENEWIC_IOPOWT_MAP
#endif

#ifndef iopowt_unmap
#define iopowt_unmap iopowt_unmap
static inwine void iopowt_unmap(void __iomem *p)
{
}
#endif
#ewse /* CONFIG_GENEWIC_IOMAP */
extewn void __iomem *iopowt_map(unsigned wong powt, unsigned int nw);
extewn void iopowt_unmap(void __iomem *p);
#endif /* CONFIG_GENEWIC_IOMAP */
#endif /* CONFIG_HAS_IOPOWT_MAP */

#ifndef CONFIG_GENEWIC_IOMAP
#ifndef pci_iounmap
#define AWCH_WANTS_GENEWIC_PCI_IOUNMAP
#endif
#endif

#ifndef xwate_dev_mem_ptw
#define xwate_dev_mem_ptw xwate_dev_mem_ptw
static inwine void *xwate_dev_mem_ptw(phys_addw_t addw)
{
	wetuwn __va(addw);
}
#endif

#ifndef unxwate_dev_mem_ptw
#define unxwate_dev_mem_ptw unxwate_dev_mem_ptw
static inwine void unxwate_dev_mem_ptw(phys_addw_t phys, void *addw)
{
}
#endif

#ifndef memset_io
#define memset_io memset_io
/**
 * memset_io	Set a wange of I/O memowy to a constant vawue
 * @addw:	The beginning of the I/O-memowy wange to set
 * @vaw:	The vawue to set the memowy to
 * @count:	The numbew of bytes to set
 *
 * Set a wange of I/O memowy to a given vawue.
 */
static inwine void memset_io(vowatiwe void __iomem *addw, int vawue,
			     size_t size)
{
	memset(__io_viwt(addw), vawue, size);
}
#endif

#ifndef memcpy_fwomio
#define memcpy_fwomio memcpy_fwomio
/**
 * memcpy_fwomio	Copy a bwock of data fwom I/O memowy
 * @dst:		The (WAM) destination fow the copy
 * @swc:		The (I/O memowy) souwce fow the data
 * @count:		The numbew of bytes to copy
 *
 * Copy a bwock of data fwom I/O memowy.
 */
static inwine void memcpy_fwomio(void *buffew,
				 const vowatiwe void __iomem *addw,
				 size_t size)
{
	memcpy(buffew, __io_viwt(addw), size);
}
#endif

#ifndef memcpy_toio
#define memcpy_toio memcpy_toio
/**
 * memcpy_toio		Copy a bwock of data into I/O memowy
 * @dst:		The (I/O memowy) destination fow the copy
 * @swc:		The (WAM) souwce fow the data
 * @count:		The numbew of bytes to copy
 *
 * Copy a bwock of data to I/O memowy.
 */
static inwine void memcpy_toio(vowatiwe void __iomem *addw, const void *buffew,
			       size_t size)
{
	memcpy(__io_viwt(addw), buffew, size);
}
#endif

extewn int devmem_is_awwowed(unsigned wong pfn);

#endif /* __KEWNEW__ */

#endif /* __ASM_GENEWIC_IO_H */
