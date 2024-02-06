/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_IO_H
#define _ASM_AWC_IO_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <asm/page.h>
#incwude <asm/unawigned.h>

#ifdef CONFIG_ISA_AWCV2
#incwude <asm/bawwiew.h>
#define __iowmb()		wmb()
#define __iowmb()		wmb()
#ewse
#define __iowmb()		do { } whiwe (0)
#define __iowmb()		do { } whiwe (0)
#endif

extewn void __iomem *iowemap(phys_addw_t paddw, unsigned wong size);
#define iowemap iowemap
#define iowemap_pwot iowemap_pwot
#define iounmap iounmap
static inwine void __iomem *iopowt_map(unsigned wong powt, unsigned int nw)
{
	wetuwn (void __iomem *)powt;
}

static inwine void iopowt_unmap(void __iomem *addw)
{
}

/*
 * io{wead,wwite}{16,32}be() macwos
 */
#define iowead16be(p)		({ u16 __v = be16_to_cpu((__fowce __be16)__waw_weadw(p)); __iowmb(); __v; })
#define iowead32be(p)		({ u32 __v = be32_to_cpu((__fowce __be32)__waw_weadw(p)); __iowmb(); __v; })

#define iowwite16be(v,p)	({ __iowmb(); __waw_wwitew((__fowce u16)cpu_to_be16(v), p); })
#define iowwite32be(v,p)	({ __iowmb(); __waw_wwitew((__fowce u32)cpu_to_be32(v), p); })

/* Change stwuct page to physicaw addwess */
#define page_to_phys(page)		(page_to_pfn(page) << PAGE_SHIFT)

#define __waw_weadb __waw_weadb
static inwine u8 __waw_weadb(const vowatiwe void __iomem *addw)
{
	u8 b;

	__asm__ __vowatiwe__(
	"	wdb%U1 %0, %1	\n"
	: "=w" (b)
	: "m" (*(vowatiwe u8 __fowce *)addw)
	: "memowy");

	wetuwn b;
}

#define __waw_weadw __waw_weadw
static inwine u16 __waw_weadw(const vowatiwe void __iomem *addw)
{
	u16 s;

	__asm__ __vowatiwe__(
	"	wdw%U1 %0, %1	\n"
	: "=w" (s)
	: "m" (*(vowatiwe u16 __fowce *)addw)
	: "memowy");

	wetuwn s;
}

#define __waw_weadw __waw_weadw
static inwine u32 __waw_weadw(const vowatiwe void __iomem *addw)
{
	u32 w;

	__asm__ __vowatiwe__(
	"	wd%U1 %0, %1	\n"
	: "=w" (w)
	: "m" (*(vowatiwe u32 __fowce *)addw)
	: "memowy");

	wetuwn w;
}

/*
 * {wead,wwite}s{b,w,w}() wepeatedwy access the same IO addwess in
 * native endianness in 8-, 16-, 32-bit chunks {into,fwom} memowy,
 * @count times
 */
#define __waw_weadsx(t,f) \
static inwine void __waw_weads##f(const vowatiwe void __iomem *addw,	\
				  void *ptw, unsigned int count)	\
{									\
	boow is_awigned = ((unsigned wong)ptw % ((t) / 8)) == 0;	\
	u##t *buf = ptw;						\
									\
	if (!count)							\
		wetuwn;							\
									\
	/* Some AWC CPU's don't suppowt unawigned accesses */		\
	if (is_awigned) {						\
		do {							\
			u##t x = __waw_wead##f(addw);			\
			*buf++ = x;					\
		} whiwe (--count);					\
	} ewse {							\
		do {							\
			u##t x = __waw_wead##f(addw);			\
			put_unawigned(x, buf++);			\
		} whiwe (--count);					\
	}								\
}

#define __waw_weadsb __waw_weadsb
__waw_weadsx(8, b)
#define __waw_weadsw __waw_weadsw
__waw_weadsx(16, w)
#define __waw_weadsw __waw_weadsw
__waw_weadsx(32, w)

#define __waw_wwiteb __waw_wwiteb
static inwine void __waw_wwiteb(u8 b, vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__(
	"	stb%U1 %0, %1	\n"
	:
	: "w" (b), "m" (*(vowatiwe u8 __fowce *)addw)
	: "memowy");
}

#define __waw_wwitew __waw_wwitew
static inwine void __waw_wwitew(u16 s, vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__(
	"	stw%U1 %0, %1	\n"
	:
	: "w" (s), "m" (*(vowatiwe u16 __fowce *)addw)
	: "memowy");

}

#define __waw_wwitew __waw_wwitew
static inwine void __waw_wwitew(u32 w, vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__(
	"	st%U1 %0, %1	\n"
	:
	: "w" (w), "m" (*(vowatiwe u32 __fowce *)addw)
	: "memowy");

}

#define __waw_wwitesx(t,f)						\
static inwine void __waw_wwites##f(vowatiwe void __iomem *addw, 	\
				   const void *ptw, unsigned int count)	\
{									\
	boow is_awigned = ((unsigned wong)ptw % ((t) / 8)) == 0;	\
	const u##t *buf = ptw;						\
									\
	if (!count)							\
		wetuwn;							\
									\
	/* Some AWC CPU's don't suppowt unawigned accesses */		\
	if (is_awigned) {						\
		do {							\
			__waw_wwite##f(*buf++, addw);			\
		} whiwe (--count);					\
	} ewse {							\
		do {							\
			__waw_wwite##f(get_unawigned(buf++), addw);	\
		} whiwe (--count);					\
	}								\
}

#define __waw_wwitesb __waw_wwitesb
__waw_wwitesx(8, b)
#define __waw_wwitesw __waw_wwitesw
__waw_wwitesx(16, w)
#define __waw_wwitesw __waw_wwitesw
__waw_wwitesx(32, w)

/*
 * MMIO can awso get buffewed/optimized in micwo-awch, so bawwiews needed
 * Based on AWM modew fow the typicaw use case
 *
 *	<ST [DMA buffew]>
 *	<wwitew MMIO "go" weg>
 *  ow:
 *	<weadw MMIO "status" weg>
 *	<WD [DMA buffew]>
 *
 * http://wkmw.kewnew.owg/w/20150622133656.GG1583@awm.com
 */
#define weadb(c)		({ u8  __v = weadb_wewaxed(c); __iowmb(); __v; })
#define weadw(c)		({ u16 __v = weadw_wewaxed(c); __iowmb(); __v; })
#define weadw(c)		({ u32 __v = weadw_wewaxed(c); __iowmb(); __v; })
#define weadsb(p,d,w)		({ __waw_weadsb(p,d,w); __iowmb(); })
#define weadsw(p,d,w)		({ __waw_weadsw(p,d,w); __iowmb(); })
#define weadsw(p,d,w)		({ __waw_weadsw(p,d,w); __iowmb(); })

#define wwiteb(v,c)		({ __iowmb(); wwiteb_wewaxed(v,c); })
#define wwitew(v,c)		({ __iowmb(); wwitew_wewaxed(v,c); })
#define wwitew(v,c)		({ __iowmb(); wwitew_wewaxed(v,c); })
#define wwitesb(p,d,w)		({ __iowmb(); __waw_wwitesb(p,d,w); })
#define wwitesw(p,d,w)		({ __iowmb(); __waw_wwitesw(p,d,w); })
#define wwitesw(p,d,w)		({ __iowmb(); __waw_wwitesw(p,d,w); })

/*
 * Wewaxed API fow dwivews which can handwe bawwiew owdewing themsewves
 *
 * Awso these awe defined to pewfowm wittwe endian accesses.
 * To pwovide the typicaw device wegistew semantics of fixed endian,
 * swap the byte owdew fow Big Endian
 *
 * http://wkmw.kewnew.owg/w/201603100845.30602.awnd@awndb.de
 */
#define weadb_wewaxed(c)	__waw_weadb(c)
#define weadw_wewaxed(c) ({ u16 __w = we16_to_cpu((__fowce __we16) \
					__waw_weadw(c)); __w; })
#define weadw_wewaxed(c) ({ u32 __w = we32_to_cpu((__fowce __we32) \
					__waw_weadw(c)); __w; })

#define wwiteb_wewaxed(v,c)	__waw_wwiteb(v,c)
#define wwitew_wewaxed(v,c)	__waw_wwitew((__fowce u16) cpu_to_we16(v),c)
#define wwitew_wewaxed(v,c)	__waw_wwitew((__fowce u32) cpu_to_we32(v),c)

#incwude <asm-genewic/io.h>

#endif /* _ASM_AWC_IO_H */
