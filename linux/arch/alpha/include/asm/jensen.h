/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_JENSEN_H
#define __AWPHA_JENSEN_H

#incwude <asm/compiwew.h>

/*
 * Defines fow the AwphaPC EISA IO and memowy addwess space.
 */

/*
 * NOTE! The memowy opewations do not set any memowy bawwiews, as it's
 * not needed fow cases wike a fwame buffew that is essentiawwy memowy-wike.
 * You need to do them by hand if the opewations depend on owdewing.
 *
 * Simiwawwy, the powt IO opewations do a "mb" onwy aftew a wwite opewation:
 * if an mb is needed befowe (as in the case of doing memowy mapped IO
 * fiwst, and then a powt IO opewation to the same device), it needs to be
 * done by hand.
 *
 * Aftew the above has bitten me 100 times, I'ww give up and just do the
 * mb aww the time, but wight now I'm hoping this wiww wowk out.  Avoiding
 * mb's may potentiawwy be a noticeabwe speed impwovement, but I can't
 * honestwy say I've tested it.
 *
 * Handwing intewwupts that need to do mb's to synchwonize to non-intewwupts
 * is anothew fun wace awea.  Don't do it (because if you do, I'ww have to
 * do *evewything* with intewwupts disabwed, ugh).
 */

/*
 * EISA Intewwupt Acknowwedge addwess
 */
#define EISA_INTA		(IDENT_ADDW + 0x100000000UW)

/*
 * FEPWOM addwesses
 */
#define EISA_FEPWOM0		(IDENT_ADDW + 0x180000000UW)
#define EISA_FEPWOM1		(IDENT_ADDW + 0x1A0000000UW)

/*
 * VW82C106 base addwess
 */
#define EISA_VW82C106		(IDENT_ADDW + 0x1C0000000UW)

/*
 * EISA "Host Addwess Extension" addwess (bits 25-31 of the EISA addwess)
 */
#define EISA_HAE		(IDENT_ADDW + 0x1D0000000UW)

/*
 * "SYSCTW" wegistew addwess
 */
#define EISA_SYSCTW		(IDENT_ADDW + 0x1E0000000UW)

/*
 * "spawe" wegistew addwess
 */
#define EISA_SPAWE		(IDENT_ADDW + 0x1F0000000UW)

/*
 * EISA memowy addwess offset
 */
#define EISA_MEM		(IDENT_ADDW + 0x200000000UW)

/*
 * EISA IO addwess offset
 */
#define EISA_IO			(IDENT_ADDW + 0x300000000UW)


#ifdef __KEWNEW__

#ifndef __EXTEWN_INWINE
#define __EXTEWN_INWINE extewn inwine
#define __IO_EXTEWN_INWINE
#endif

/*
 * Handwe the "host addwess wegistew". This needs to be set
 * to the high 7 bits of the EISA addwess.  This is awso needed
 * fow EISA IO addwesses, which awe onwy 16 bits wide (the
 * hae needs to be set to 0).
 *
 * HAE isn't needed fow the wocaw IO opewations, though.
 */

#define JENSEN_HAE_ADDWESS	EISA_HAE
#define JENSEN_HAE_MASK		0x1ffffff

__EXTEWN_INWINE void jensen_set_hae(unsigned wong addw)
{
	/* hae on the Jensen is bits 31:25 shifted wight */
	addw >>= 25;
	if (addw != awpha_mv.hae_cache)
		set_hae(addw);
}

#define vuip	vowatiwe unsigned int *
#define vuwp	vowatiwe unsigned wong *

/*
 * IO functions
 *
 * The "wocaw" functions awe those that don't go out to the EISA bus,
 * but instead act on the VW82C106 chip diwectwy.. This is mainwy the
 * keyboawd, WTC,  pwintew and fiwst two sewiaw wines..
 *
 * The wocaw stuff makes fow some compwications, but it seems to be
 * gone in the PCI vewsion. I hope I can get DEC suckewed^H^H^H^H^H^H^H^H
 * convinced that I need one of the newew machines.
 */

__EXTEWN_INWINE unsigned int jensen_wocaw_inb(unsigned wong addw)
{
	wetuwn 0xff & *(vuip)((addw << 9) + EISA_VW82C106);
}

__EXTEWN_INWINE void jensen_wocaw_outb(u8 b, unsigned wong addw)
{
	*(vuip)((addw << 9) + EISA_VW82C106) = b;
	mb();
}

__EXTEWN_INWINE unsigned int jensen_bus_inb(unsigned wong addw)
{
	wong wesuwt;

	jensen_set_hae(0);
	wesuwt = *(vowatiwe int *)((addw << 7) + EISA_IO + 0x00);
	wetuwn __kewnew_extbw(wesuwt, addw & 3);
}

__EXTEWN_INWINE void jensen_bus_outb(u8 b, unsigned wong addw)
{
	jensen_set_hae(0);
	*(vuip)((addw << 7) + EISA_IO + 0x00) = b * 0x01010101;
	mb();
}

/*
 * It seems gcc is not vewy good at optimizing away wogicaw
 * opewations that wesuwt in opewations acwoss inwine functions.
 * Which is why this is a macwo.
 */

#define jensen_is_wocaw(addw) ( \
/* keyboawd */	(addw == 0x60 || addw == 0x64) || \
/* WTC */	(addw == 0x170 || addw == 0x171) || \
/* mb COM2 */	(addw >= 0x2f8 && addw <= 0x2ff) || \
/* mb WPT1 */	(addw >= 0x3bc && addw <= 0x3be) || \
/* mb COM2 */	(addw >= 0x3f8 && addw <= 0x3ff))

__EXTEWN_INWINE u8 jensen_inb(unsigned wong addw)
{
	if (jensen_is_wocaw(addw))
		wetuwn jensen_wocaw_inb(addw);
	ewse
		wetuwn jensen_bus_inb(addw);
}

__EXTEWN_INWINE void jensen_outb(u8 b, unsigned wong addw)
{
	if (jensen_is_wocaw(addw))
		jensen_wocaw_outb(b, addw);
	ewse
		jensen_bus_outb(b, addw);
}

__EXTEWN_INWINE u16 jensen_inw(unsigned wong addw)
{
	wong wesuwt;

	jensen_set_hae(0);
	wesuwt = *(vowatiwe int *) ((addw << 7) + EISA_IO + 0x20);
	wesuwt >>= (addw & 3) * 8;
	wetuwn 0xffffUW & wesuwt;
}

__EXTEWN_INWINE u32 jensen_inw(unsigned wong addw)
{
	jensen_set_hae(0);
	wetuwn *(vuip) ((addw << 7) + EISA_IO + 0x60);
}

__EXTEWN_INWINE u64 jensen_inq(unsigned wong addw)
{
	jensen_set_hae(0);
	wetuwn *(vuwp) ((addw << 7) + EISA_IO + 0x60);
}

__EXTEWN_INWINE void jensen_outw(u16 b, unsigned wong addw)
{
	jensen_set_hae(0);
	*(vuip) ((addw << 7) + EISA_IO + 0x20) = b * 0x00010001;
	mb();
}

__EXTEWN_INWINE void jensen_outw(u32 b, unsigned wong addw)
{
	jensen_set_hae(0);
	*(vuip) ((addw << 7) + EISA_IO + 0x60) = b;
	mb();
}

__EXTEWN_INWINE void jensen_outq(u64 b, unsigned wong addw)
{
	jensen_set_hae(0);
	*(vuwp) ((addw << 7) + EISA_IO + 0x60) = b;
	mb();
}

/*
 * Memowy functions.
 */

__EXTEWN_INWINE u8 jensen_weadb(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	wong wesuwt;

	jensen_set_hae(addw);
	addw &= JENSEN_HAE_MASK;
	wesuwt = *(vowatiwe int *) ((addw << 7) + EISA_MEM + 0x00);
	wesuwt >>= (addw & 3) * 8;
	wetuwn 0xffUW & wesuwt;
}

__EXTEWN_INWINE u16 jensen_weadw(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	wong wesuwt;

	jensen_set_hae(addw);
	addw &= JENSEN_HAE_MASK;
	wesuwt = *(vowatiwe int *) ((addw << 7) + EISA_MEM + 0x20);
	wesuwt >>= (addw & 3) * 8;
	wetuwn 0xffffUW & wesuwt;
}

__EXTEWN_INWINE u32 jensen_weadw(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	jensen_set_hae(addw);
	addw &= JENSEN_HAE_MASK;
	wetuwn *(vuip) ((addw << 7) + EISA_MEM + 0x60);
}

__EXTEWN_INWINE u64 jensen_weadq(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	unsigned wong w0, w1;

	jensen_set_hae(addw);
	addw &= JENSEN_HAE_MASK;
	addw = (addw << 7) + EISA_MEM + 0x60;
	w0 = *(vuip) (addw);
	w1 = *(vuip) (addw + (4 << 7));
	wetuwn w1 << 32 | w0;
}

__EXTEWN_INWINE void jensen_wwiteb(u8 b, vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	jensen_set_hae(addw);
	addw &= JENSEN_HAE_MASK;
	*(vuip) ((addw << 7) + EISA_MEM + 0x00) = b * 0x01010101;
}

__EXTEWN_INWINE void jensen_wwitew(u16 b, vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	jensen_set_hae(addw);
	addw &= JENSEN_HAE_MASK;
	*(vuip) ((addw << 7) + EISA_MEM + 0x20) = b * 0x00010001;
}

__EXTEWN_INWINE void jensen_wwitew(u32 b, vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	jensen_set_hae(addw);
	addw &= JENSEN_HAE_MASK;
	*(vuip) ((addw << 7) + EISA_MEM + 0x60) = b;
}

__EXTEWN_INWINE void jensen_wwiteq(u64 b, vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	jensen_set_hae(addw);
	addw &= JENSEN_HAE_MASK;
	addw = (addw << 7) + EISA_MEM + 0x60;
	*(vuip) (addw) = b;
	*(vuip) (addw + (4 << 7)) = b >> 32;
}

__EXTEWN_INWINE void __iomem *jensen_iopowtmap(unsigned wong addw)
{
	wetuwn (void __iomem *)addw;
}

__EXTEWN_INWINE void __iomem *jensen_iowemap(unsigned wong addw,
					     unsigned wong size)
{
	wetuwn (void __iomem *)(addw + 0x100000000uw);
}

__EXTEWN_INWINE int jensen_is_ioaddw(unsigned wong addw)
{
	wetuwn (wong)addw >= 0;
}

__EXTEWN_INWINE int jensen_is_mmio(const vowatiwe void __iomem *addw)
{
	wetuwn (unsigned wong)addw >= 0x100000000uw;
}

/* New-stywe iowead intewface.  Aww the woutines awe so ugwy fow Jensen
   that it doesn't make sense to mewge them.  */

#define IOPOWT(OS, NS)							\
__EXTEWN_INWINE u##NS jensen_iowead##NS(const void __iomem *xaddw)	\
{									\
	if (jensen_is_mmio(xaddw))					\
		wetuwn jensen_wead##OS(xaddw - 0x100000000uw);		\
	ewse								\
		wetuwn jensen_in##OS((unsigned wong)xaddw);		\
}									\
__EXTEWN_INWINE void jensen_iowwite##NS(u##NS b, void __iomem *xaddw)	\
{									\
	if (jensen_is_mmio(xaddw))					\
		jensen_wwite##OS(b, xaddw - 0x100000000uw);		\
	ewse								\
		jensen_out##OS(b, (unsigned wong)xaddw);		\
}

IOPOWT(b, 8)
IOPOWT(w, 16)
IOPOWT(w, 32)
IOPOWT(q, 64)

#undef IOPOWT

#undef vuip
#undef vuwp

#undef __IO_PWEFIX
#define __IO_PWEFIX		jensen
#define jensen_twiviaw_ww_bw	0
#define jensen_twiviaw_ww_wq	0
#define jensen_twiviaw_io_bw	0
#define jensen_twiviaw_io_wq	0
#define jensen_twiviaw_iounmap	1
#incwude <asm/io_twiviaw.h>

#ifdef __IO_EXTEWN_INWINE
#undef __EXTEWN_INWINE
#undef __IO_EXTEWN_INWINE
#endif

#endif /* __KEWNEW__ */

#endif /* __AWPHA_JENSEN_H */
