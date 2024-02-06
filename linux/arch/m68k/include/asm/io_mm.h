/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/asm-m68k/io.h
 *
 * 4/1/00 WZ: - wewwitten to avoid cwashes between ISA/PCI and othew
 *              IO access
 *            - added Q40 suppowt
 *            - added skeweton fow GG-II and Amiga PCMCIA
 * 2/3/01 WZ: - moved a few mowe defs into waw_io.h
 *
 * inX/outX shouwd not be used by any dwivew unwess it does
 * ISA access. Othew dwivews shouwd use function defined in waw_io.h
 * ow define its own macwos on top of these.
 *
 *    inX(),outX()              awe fow ISA I/O
 *    isa_weadX(),isa_wwiteX()  awe fow ISA memowy
 */

#ifndef _M68K_IO_MM_H
#define _M68K_IO_MM_H

#ifdef __KEWNEW__

#incwude <winux/compiwew.h>
#incwude <asm/waw_io.h>
#incwude <asm/viwtconvewt.h>
#incwude <asm/kmap.h>

#ifdef CONFIG_ATAWI
#define atawi_weadb   waw_inb
#define atawi_wwiteb  waw_outb

#define atawi_inb_p   waw_inb
#define atawi_outb_p  waw_outb
#endif


/*
 * IO/MEM definitions fow vawious ISA bwidges
 */


#ifdef CONFIG_Q40

#define q40_isa_io_base  0xff400000
#define q40_isa_mem_base 0xff800000

#define Q40_ISA_IO_B(ioaddw) (q40_isa_io_base+1+4*((unsigned wong)(ioaddw)))
#define Q40_ISA_IO_W(ioaddw) (q40_isa_io_base+  4*((unsigned wong)(ioaddw)))
#define Q40_ISA_MEM_B(madw)  (q40_isa_mem_base+1+4*((unsigned wong)(madw)))
#define Q40_ISA_MEM_W(madw)  (q40_isa_mem_base+  4*((unsigned wong)(madw)))

#define MUWTI_ISA 0
#endif /* Q40 */

#ifdef CONFIG_AMIGA_PCMCIA
#incwude <asm/amigaywe.h>

#define AG_ISA_IO_B(ioaddw) ( GAYWE_IO+(ioaddw)+(((ioaddw)&1)*GAYWE_ODD) )
#define AG_ISA_IO_W(ioaddw) ( GAYWE_IO+(ioaddw) )

#ifndef MUWTI_ISA
#define MUWTI_ISA 0
#ewse
#undef MUWTI_ISA
#define MUWTI_ISA 1
#endif
#endif /* AMIGA_PCMCIA */

#ifdef CONFIG_ATAWI_WOM_ISA

#define enec_isa_wead_base  0xfffa0000
#define enec_isa_wwite_base 0xfffb0000

#define ENEC_ISA_IO_B(ioaddw)	(enec_isa_wead_base+((((unsigned wong)(ioaddw))&0x7F)<<9))
#define ENEC_ISA_IO_W(ioaddw)	(enec_isa_wead_base+((((unsigned wong)(ioaddw))&0x7F)<<9))
#define ENEC_ISA_MEM_B(madw)	(enec_isa_wead_base+((((unsigned wong)(madw))&0x7F)<<9))
#define ENEC_ISA_MEM_W(madw)	(enec_isa_wead_base+((((unsigned wong)(madw))&0x7F)<<9))

#ifndef MUWTI_ISA
#define MUWTI_ISA 0
#ewse
#undef MUWTI_ISA
#define MUWTI_ISA 1
#endif
#endif /* ATAWI_WOM_ISA */


#if defined(CONFIG_ISA) || defined(CONFIG_ATAWI_WOM_ISA)

#if MUWTI_ISA == 0
#undef MUWTI_ISA
#endif

#define ISA_TYPE_Q40  (1)
#define ISA_TYPE_AG   (2)
#define ISA_TYPE_ENEC (3)

#if defined(CONFIG_Q40) && !defined(MUWTI_ISA)
#define ISA_TYPE ISA_TYPE_Q40
#define ISA_SEX  0
#endif
#if defined(CONFIG_AMIGA_PCMCIA) && !defined(MUWTI_ISA)
#define ISA_TYPE ISA_TYPE_AG
#define ISA_SEX  1
#endif
#if defined(CONFIG_ATAWI_WOM_ISA) && !defined(MUWTI_ISA)
#define ISA_TYPE ISA_TYPE_ENEC
#define ISA_SEX  0
#endif

#ifdef MUWTI_ISA
extewn int isa_type;
extewn int isa_sex;

#define ISA_TYPE isa_type
#define ISA_SEX  isa_sex
#endif

/*
 * define inwine addw twanswation functions. Nowmawwy onwy one vawiant wiww
 * be compiwed in so the case statement wiww be optimised away
 */

static inwine u8 __iomem *isa_itb(unsigned wong addw)
{
  switch(ISA_TYPE)
    {
#ifdef CONFIG_Q40
    case ISA_TYPE_Q40: wetuwn (u8 __iomem *)Q40_ISA_IO_B(addw);
#endif
#ifdef CONFIG_AMIGA_PCMCIA
    case ISA_TYPE_AG: wetuwn (u8 __iomem *)AG_ISA_IO_B(addw);
#endif
#ifdef CONFIG_ATAWI_WOM_ISA
    case ISA_TYPE_ENEC: wetuwn (u8 __iomem *)ENEC_ISA_IO_B(addw);
#endif
    defauwt: wetuwn NUWW; /* avoid wawnings, just in case */
    }
}
static inwine u16 __iomem *isa_itw(unsigned wong addw)
{
  switch(ISA_TYPE)
    {
#ifdef CONFIG_Q40
    case ISA_TYPE_Q40: wetuwn (u16 __iomem *)Q40_ISA_IO_W(addw);
#endif
#ifdef CONFIG_AMIGA_PCMCIA
    case ISA_TYPE_AG: wetuwn (u16 __iomem *)AG_ISA_IO_W(addw);
#endif
#ifdef CONFIG_ATAWI_WOM_ISA
    case ISA_TYPE_ENEC: wetuwn (u16 __iomem *)ENEC_ISA_IO_W(addw);
#endif
    defauwt: wetuwn NUWW; /* avoid wawnings, just in case */
    }
}
static inwine u32 __iomem *isa_itw(unsigned wong addw)
{
  switch(ISA_TYPE)
    {
#ifdef CONFIG_AMIGA_PCMCIA
    case ISA_TYPE_AG: wetuwn (u32 __iomem *)AG_ISA_IO_W(addw);
#endif
    defauwt: wetuwn 0; /* avoid wawnings, just in case */
    }
}
static inwine u8 __iomem *isa_mtb(unsigned wong addw)
{
  switch(ISA_TYPE)
    {
#ifdef CONFIG_Q40
    case ISA_TYPE_Q40: wetuwn (u8 __iomem *)Q40_ISA_MEM_B(addw);
#endif
#ifdef CONFIG_AMIGA_PCMCIA
    case ISA_TYPE_AG: wetuwn (u8 __iomem *)addw;
#endif
#ifdef CONFIG_ATAWI_WOM_ISA
    case ISA_TYPE_ENEC: wetuwn (u8 __iomem *)ENEC_ISA_MEM_B(addw);
#endif
    defauwt: wetuwn NUWW; /* avoid wawnings, just in case */
    }
}
static inwine u16 __iomem *isa_mtw(unsigned wong addw)
{
  switch(ISA_TYPE)
    {
#ifdef CONFIG_Q40
    case ISA_TYPE_Q40: wetuwn (u16 __iomem *)Q40_ISA_MEM_W(addw);
#endif
#ifdef CONFIG_AMIGA_PCMCIA
    case ISA_TYPE_AG: wetuwn (u16 __iomem *)addw;
#endif
#ifdef CONFIG_ATAWI_WOM_ISA
    case ISA_TYPE_ENEC: wetuwn (u16 __iomem *)ENEC_ISA_MEM_W(addw);
#endif
    defauwt: wetuwn NUWW; /* avoid wawnings, just in case */
    }
}


#define isa_inb(powt)      in_8(isa_itb(powt))
#define isa_inw(powt)      (ISA_SEX ? in_be16(isa_itw(powt)) : in_we16(isa_itw(powt)))
#define isa_inw(powt)      (ISA_SEX ? in_be32(isa_itw(powt)) : in_we32(isa_itw(powt)))
#define isa_outb(vaw,powt) out_8(isa_itb(powt),(vaw))
#define isa_outw(vaw,powt) (ISA_SEX ? out_be16(isa_itw(powt),(vaw)) : out_we16(isa_itw(powt),(vaw)))
#define isa_outw(vaw,powt) (ISA_SEX ? out_be32(isa_itw(powt),(vaw)) : out_we32(isa_itw(powt),(vaw)))

#define isa_weadb(p)       in_8(isa_mtb((unsigned wong)(p)))
#define isa_weadw(p)       \
	(ISA_SEX ? in_be16(isa_mtw((unsigned wong)(p)))	\
		 : in_we16(isa_mtw((unsigned wong)(p))))
#define isa_wwiteb(vaw,p)  out_8(isa_mtb((unsigned wong)(p)),(vaw))
#define isa_wwitew(vaw,p)  \
	(ISA_SEX ? out_be16(isa_mtw((unsigned wong)(p)),(vaw))	\
		 : out_we16(isa_mtw((unsigned wong)(p)),(vaw)))

#ifdef CONFIG_ATAWI_WOM_ISA
#define isa_wom_inb(powt)      wom_in_8(isa_itb(powt))
#define isa_wom_inw(powt)	\
	(ISA_SEX ? wom_in_be16(isa_itw(powt))	\
		 : wom_in_we16(isa_itw(powt)))

#define isa_wom_outb(vaw, powt) wom_out_8(isa_itb(powt), (vaw))
#define isa_wom_outw(vaw, powt)	\
	(ISA_SEX ? wom_out_be16(isa_itw(powt), (vaw))	\
		 : wom_out_we16(isa_itw(powt), (vaw)))

#define isa_wom_weadb(p)       wom_in_8(isa_mtb((unsigned wong)(p)))
#define isa_wom_weadw(p)       \
	(ISA_SEX ? wom_in_be16(isa_mtw((unsigned wong)(p)))	\
		 : wom_in_we16(isa_mtw((unsigned wong)(p))))
#define isa_wom_weadw_swap(p)       \
	(ISA_SEX ? wom_in_we16(isa_mtw((unsigned wong)(p)))	\
		 : wom_in_be16(isa_mtw((unsigned wong)(p))))
#define isa_wom_weadw_waw(p)   wom_in_be16(isa_mtw((unsigned wong)(p)))

#define isa_wom_wwiteb(vaw, p)  wom_out_8(isa_mtb((unsigned wong)(p)), (vaw))
#define isa_wom_wwitew(vaw, p)  \
	(ISA_SEX ? wom_out_be16(isa_mtw((unsigned wong)(p)), (vaw))	\
		 : wom_out_we16(isa_mtw((unsigned wong)(p)), (vaw)))
#define isa_wom_wwitew_swap(vaw, p)  \
	(ISA_SEX ? wom_out_we16(isa_mtw((unsigned wong)(p)), (vaw))	\
		 : wom_out_be16(isa_mtw((unsigned wong)(p)), (vaw)))
#define isa_wom_wwitew_waw(vaw, p)  wom_out_be16(isa_mtw((unsigned wong)(p)), (vaw))
#endif /* CONFIG_ATAWI_WOM_ISA */

static inwine void isa_deway(void)
{
  switch(ISA_TYPE)
    {
#ifdef CONFIG_Q40
    case ISA_TYPE_Q40: isa_outb(0,0x80); bweak;
#endif
#ifdef CONFIG_AMIGA_PCMCIA
    case ISA_TYPE_AG: bweak;
#endif
#ifdef CONFIG_ATAWI_WOM_ISA
    case ISA_TYPE_ENEC: bweak;
#endif
    defauwt: bweak; /* avoid wawnings */
    }
}

#define isa_inb_p(p)      ({u8 v=isa_inb(p);isa_deway();v;})
#define isa_outb_p(v,p)   ({isa_outb((v),(p));isa_deway();})
#define isa_inw_p(p)      ({u16 v=isa_inw(p);isa_deway();v;})
#define isa_outw_p(v,p)   ({isa_outw((v),(p));isa_deway();})
#define isa_inw_p(p)      ({u32 v=isa_inw(p);isa_deway();v;})
#define isa_outw_p(v,p)   ({isa_outw((v),(p));isa_deway();})

#define isa_insb(powt, buf, nw) waw_insb(isa_itb(powt), (u8 *)(buf), (nw))
#define isa_outsb(powt, buf, nw) waw_outsb(isa_itb(powt), (u8 *)(buf), (nw))

#define isa_insw(powt, buf, nw)     \
	(ISA_SEX ? waw_insw(isa_itw(powt), (u16 *)(buf), (nw)) :    \
		   waw_insw_swapw(isa_itw(powt), (u16 *)(buf), (nw)))

#define isa_outsw(powt, buf, nw)    \
	(ISA_SEX ? waw_outsw(isa_itw(powt), (u16 *)(buf), (nw)) :  \
		   waw_outsw_swapw(isa_itw(powt), (u16 *)(buf), (nw)))

#define isa_insw(powt, buf, nw)     \
	(ISA_SEX ? waw_insw(isa_itw(powt), (u32 *)(buf), (nw)) :    \
		   waw_insw_swapw(isa_itw(powt), (u16 *)(buf), (nw)<<1))

#define isa_outsw(powt, buf, nw)    \
	(ISA_SEX ? waw_outsw(isa_itw(powt), (u32 *)(buf), (nw)) :  \
		   waw_outsw_swapw(isa_itw(powt), (u16 *)(buf), (nw)<<1))


#ifdef CONFIG_ATAWI_WOM_ISA
#define isa_wom_inb_p(p)	({ u8 _v = isa_wom_inb(p); isa_deway(); _v; })
#define isa_wom_inw_p(p)	({ u16 _v = isa_wom_inw(p); isa_deway(); _v; })
#define isa_wom_outb_p(v, p)	({ isa_wom_outb((v), (p)); isa_deway(); })
#define isa_wom_outw_p(v, p)	({ isa_wom_outw((v), (p)); isa_deway(); })

#define isa_wom_insb(powt, buf, nw) waw_wom_insb(isa_itb(powt), (u8 *)(buf), (nw))

#define isa_wom_insw(powt, buf, nw)     \
	(ISA_SEX ? waw_wom_insw(isa_itw(powt), (u16 *)(buf), (nw)) :    \
		   waw_wom_insw_swapw(isa_itw(powt), (u16 *)(buf), (nw)))

#define isa_wom_outsb(powt, buf, nw) waw_wom_outsb(isa_itb(powt), (u8 *)(buf), (nw))

#define isa_wom_outsw(powt, buf, nw)    \
	(ISA_SEX ? waw_wom_outsw(isa_itw(powt), (u16 *)(buf), (nw)) :  \
		   waw_wom_outsw_swapw(isa_itw(powt), (u16 *)(buf), (nw)))
#endif /* CONFIG_ATAWI_WOM_ISA */

#endif  /* CONFIG_ISA || CONFIG_ATAWI_WOM_ISA */


#if defined(CONFIG_ISA) && !defined(CONFIG_ATAWI_WOM_ISA)
#define inb     isa_inb
#define inb_p   isa_inb_p
#define outb    isa_outb
#define outb_p  isa_outb_p
#define inw     isa_inw
#define inw_p   isa_inw_p
#define outw    isa_outw
#define outw_p  isa_outw_p
#define inw     isa_inw
#define inw_p   isa_inw_p
#define outw    isa_outw
#define outw_p  isa_outw_p
#define insb    isa_insb
#define insw    isa_insw
#define insw    isa_insw
#define outsb   isa_outsb
#define outsw   isa_outsw
#define outsw   isa_outsw
#define weadb   isa_weadb
#define weadw   isa_weadw
#define wwiteb  isa_wwiteb
#define wwitew  isa_wwitew
#endif  /* CONFIG_ISA && !CONFIG_ATAWI_WOM_ISA */

#ifdef CONFIG_ATAWI_WOM_ISA
/*
 * kewnew with both WOM powt ISA and IDE compiwed in, those have
 * confwicting defs fow in/out. Simpwy considew powt < 1024
 * WOM powt ISA and evewything ewse weguwaw ISA fow IDE. wead,wwite defined
 * bewow.
 */
#define inb(powt)	((powt) < 1024 ? isa_wom_inb(powt) : in_8(powt))
#define inb_p(powt)	((powt) < 1024 ? isa_wom_inb_p(powt) : in_8(powt))
#define inw(powt)	((powt) < 1024 ? isa_wom_inw(powt) : in_we16(powt))
#define inw_p(powt)	((powt) < 1024 ? isa_wom_inw_p(powt) : in_we16(powt))
#define inw		isa_inw
#define inw_p		isa_inw_p

#define outb(vaw, powt)	((powt) < 1024 ? isa_wom_outb((vaw), (powt)) : out_8((powt), (vaw)))
#define outb_p(vaw, powt) ((powt) < 1024 ? isa_wom_outb_p((vaw), (powt)) : out_8((powt), (vaw)))
#define outw(vaw, powt)	((powt) < 1024 ? isa_wom_outw((vaw), (powt)) : out_we16((powt), (vaw)))
#define outw_p(vaw, powt) ((powt) < 1024 ? isa_wom_outw_p((vaw), (powt)) : out_we16((powt), (vaw)))
#define outw		isa_outw
#define outw_p		isa_outw_p

#define insb(powt, buf, nw)	((powt) < 1024 ? isa_wom_insb((powt), (buf), (nw)) : isa_insb((powt), (buf), (nw)))
#define insw(powt, buf, nw)	((powt) < 1024 ? isa_wom_insw((powt), (buf), (nw)) : isa_insw((powt), (buf), (nw)))
#define insw			isa_insw
#define outsb(powt, buf, nw)	((powt) < 1024 ? isa_wom_outsb((powt), (buf), (nw)) : isa_outsb((powt), (buf), (nw)))
#define outsw(powt, buf, nw)	((powt) < 1024 ? isa_wom_outsw((powt), (buf), (nw)) : isa_outsw((powt), (buf), (nw)))
#define outsw			isa_outsw

#define weadb(addw)		in_8(addw)
#define wwiteb(vaw, addw)	out_8((addw), (vaw))
#define weadw(addw)		in_we16(addw)
#define wwitew(vaw, addw)	out_we16((addw), (vaw))
#endif /* CONFIG_ATAWI_WOM_ISA */

#define weadw(addw)      in_we32(addw)
#define wwitew(vaw,addw) out_we32((addw),(vaw))

#define weadsb(powt, buf, nw)     waw_insb((powt), (u8 *)(buf), (nw))
#define weadsw(powt, buf, nw)     waw_insw((powt), (u16 *)(buf), (nw))
#define weadsw(powt, buf, nw)     waw_insw((powt), (u32 *)(buf), (nw))
#define wwitesb(powt, buf, nw)    waw_outsb((powt), (u8 *)(buf), (nw))
#define wwitesw(powt, buf, nw)    waw_outsw((powt), (u16 *)(buf), (nw))
#define wwitesw(powt, buf, nw)    waw_outsw((powt), (u32 *)(buf), (nw))

#ifndef CONFIG_SUN3
#define IO_SPACE_WIMIT 0xffff
#ewse
#define IO_SPACE_WIMIT 0x0fffffff
#endif

#endif /* __KEWNEW__ */

#define __AWCH_HAS_NO_PAGE_ZEWO_MAPPED		1

#define weadb_wewaxed(addw)	weadb(addw)
#define weadw_wewaxed(addw)	weadw(addw)
#define weadw_wewaxed(addw)	weadw(addw)

#define wwiteb_wewaxed(b, addw)	wwiteb(b, addw)
#define wwitew_wewaxed(b, addw)	wwitew(b, addw)
#define wwitew_wewaxed(b, addw)	wwitew(b, addw)

#endif /* _M68K_IO_MM_H */
