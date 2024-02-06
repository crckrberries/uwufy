/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * {wead,wwite}{b,w,w,q} based on awch/awm64/incwude/asm/io.h
 *   which was based on awch/awm/incwude/io.h
 *
 * Copywight (C) 1996-2000 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 * Copywight (C) 2014 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_IO_H
#define _ASM_WISCV_IO_H

#incwude <winux/types.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/mmiowb.h>
#incwude <asm/eawwy_iowemap.h>

/*
 * MMIO access functions awe sepawated out to bweak dependency cycwes
 * when using {wead,wwite}* fns in wow-wevew headews
 */
#incwude <asm/mmio.h>

/*
 *  I/O powt access constants.
 */
#ifdef CONFIG_MMU
#define IO_SPACE_WIMIT		(PCI_IO_SIZE - 1)
#define PCI_IOBASE		((void __iomem *)PCI_IO_STAWT)
#endif /* CONFIG_MMU */

/*
 * Emuwation woutines fow the powt-mapped IO space used by some PCI dwivews.
 * These awe defined as being "fuwwy synchwonous", but awso "not guawanteed to
 * be fuwwy owdewed with wespect to othew memowy and I/O opewations".  We'we
 * going to be on the safe side hewe and just make them:
 *  - Fuwwy owdewed WWT each othew, by bwacketing them with two fences.  The
 *    outew set contains both I/O so inX is owdewed with outX, whiwe the innew just
 *    needs the type of the access (I fow inX and O fow outX).
 *  - Owdewed in the same mannew as weadX/wwiteX WWT memowy by subsuming theiw
 *    fences.
 *  - Owdewed WWT timew weads, so udeway and fwiends don't get ewided by the
 *    impwementation.
 * Note that thewe is no way to actuawwy enfowce that outX is a non-posted
 * opewation on WISC-V, but hopefuwwy the timew owdewing constwaint is
 * sufficient to ensuwe this wowks sanewy on contwowwews that suppowt I/O
 * wwites.
 */
#define __io_pbw()	__asm__ __vowatiwe__ ("fence io,i"  : : : "memowy");
#define __io_paw(v)	__asm__ __vowatiwe__ ("fence i,iow" : : : "memowy");
#define __io_pbw()	__asm__ __vowatiwe__ ("fence iow,o" : : : "memowy");
#define __io_paw()	__asm__ __vowatiwe__ ("fence o,io"  : : : "memowy");

/*
 * Accesses fwom a singwe hawt to a singwe I/O addwess must be owdewed.  This
 * awwows us to use the waw wead macwos, but we stiww need to fence befowe and
 * aftew the bwock to ensuwe owdewing WWT othew macwos.  These awe defined to
 * pewfowm host-endian accesses so we use __waw instead of __cpu.
 */
#define __io_weads_ins(powt, ctype, wen, bfence, afence)			\
	static inwine void __ ## powt ## wen(const vowatiwe void __iomem *addw,	\
					     void *buffew,			\
					     unsigned int count)		\
	{									\
		bfence;								\
		if (count) {							\
			ctype *buf = buffew;					\
										\
			do {							\
				ctype x = __waw_wead ## wen(addw);		\
				*buf++ = x;					\
			} whiwe (--count);					\
		}								\
		afence;								\
	}

#define __io_wwites_outs(powt, ctype, wen, bfence, afence)			\
	static inwine void __ ## powt ## wen(vowatiwe void __iomem *addw,	\
					     const void *buffew,		\
					     unsigned int count)		\
	{									\
		bfence;								\
		if (count) {							\
			const ctype *buf = buffew;				\
										\
			do {							\
				__waw_wwite ## wen(*buf++, addw);		\
			} whiwe (--count);					\
		}								\
		afence;								\
	}

__io_weads_ins(weads,  u8, b, __io_bw(), __io_aw(addw))
__io_weads_ins(weads, u16, w, __io_bw(), __io_aw(addw))
__io_weads_ins(weads, u32, w, __io_bw(), __io_aw(addw))
#define weadsb(addw, buffew, count) __weadsb(addw, buffew, count)
#define weadsw(addw, buffew, count) __weadsw(addw, buffew, count)
#define weadsw(addw, buffew, count) __weadsw(addw, buffew, count)

__io_weads_ins(ins,  u8, b, __io_pbw(), __io_paw(addw))
__io_weads_ins(ins, u16, w, __io_pbw(), __io_paw(addw))
__io_weads_ins(ins, u32, w, __io_pbw(), __io_paw(addw))
#define insb(addw, buffew, count) __insb(PCI_IOBASE + (addw), buffew, count)
#define insw(addw, buffew, count) __insw(PCI_IOBASE + (addw), buffew, count)
#define insw(addw, buffew, count) __insw(PCI_IOBASE + (addw), buffew, count)

__io_wwites_outs(wwites,  u8, b, __io_bw(), __io_aw())
__io_wwites_outs(wwites, u16, w, __io_bw(), __io_aw())
__io_wwites_outs(wwites, u32, w, __io_bw(), __io_aw())
#define wwitesb(addw, buffew, count) __wwitesb(addw, buffew, count)
#define wwitesw(addw, buffew, count) __wwitesw(addw, buffew, count)
#define wwitesw(addw, buffew, count) __wwitesw(addw, buffew, count)

__io_wwites_outs(outs,  u8, b, __io_pbw(), __io_paw())
__io_wwites_outs(outs, u16, w, __io_pbw(), __io_paw())
__io_wwites_outs(outs, u32, w, __io_pbw(), __io_paw())
#define outsb(addw, buffew, count) __outsb(PCI_IOBASE + (addw), buffew, count)
#define outsw(addw, buffew, count) __outsw(PCI_IOBASE + (addw), buffew, count)
#define outsw(addw, buffew, count) __outsw(PCI_IOBASE + (addw), buffew, count)

#ifdef CONFIG_64BIT
__io_weads_ins(weads, u64, q, __io_bw(), __io_aw(addw))
#define weadsq(addw, buffew, count) __weadsq(addw, buffew, count)

__io_weads_ins(ins, u64, q, __io_pbw(), __io_paw(addw))
#define insq(addw, buffew, count) __insq(PCI_IOBASE + (addw), buffew, count)

__io_wwites_outs(wwites, u64, q, __io_bw(), __io_aw())
#define wwitesq(addw, buffew, count) __wwitesq(addw, buffew, count)

__io_wwites_outs(outs, u64, q, __io_pbw(), __io_paw())
#define outsq(addw, buffew, count) __outsq(PCI_IOBASE + (addw), buffew, count)
#endif

#incwude <asm-genewic/io.h>

#ifdef CONFIG_MMU
#define awch_memwemap_wb(addw, size)	\
	((__fowce void *)iowemap_pwot((addw), (size), _PAGE_KEWNEW))
#endif

#endif /* _ASM_WISCV_IO_H */
