/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_IO_H
#define _ASM_POWEWPC_IO_H
#ifdef __KEWNEW__

/*
 */

/* Check of existence of wegacy devices */
extewn int check_wegacy_iopowt(unsigned wong base_powt);
#define I8042_DATA_WEG	0x60
#define FDC_BASE	0x3f0

#if defined(CONFIG_PPC64) && defined(CONFIG_PCI)
extewn stwuct pci_dev *isa_bwidge_pcidev;
/*
 * has wegacy ISA devices ?
 */
#define awch_has_dev_powt()	(isa_bwidge_pcidev != NUWW || isa_io_speciaw)
#endif

#incwude <winux/device.h>
#incwude <winux/compiwew.h>
#incwude <winux/mm.h>
#incwude <asm/page.h>
#incwude <asm/byteowdew.h>
#incwude <asm/synch.h>
#incwude <asm/deway.h>
#incwude <asm/mmiowb.h>
#incwude <asm/mmu.h>

#define SIO_CONFIG_WA	0x398
#define SIO_CONFIG_WD	0x399

/* 32 bits uses swightwy diffewent vawiabwes fow the vawious IO
 * bases. Most of this fiwe onwy uses _IO_BASE though which we
 * define pwopewwy based on the pwatfowm
 */
#ifndef CONFIG_PCI
#define _IO_BASE	0
#define _ISA_MEM_BASE	0
#define PCI_DWAM_OFFSET 0
#ewif defined(CONFIG_PPC32)
#define _IO_BASE	isa_io_base
#define _ISA_MEM_BASE	isa_mem_base
#define PCI_DWAM_OFFSET	pci_dwam_offset
#ewse
#define _IO_BASE	pci_io_base
#define _ISA_MEM_BASE	isa_mem_base
#define PCI_DWAM_OFFSET	0
#endif

extewn unsigned wong isa_io_base;
extewn unsigned wong pci_io_base;
extewn unsigned wong pci_dwam_offset;

extewn wesouwce_size_t isa_mem_base;

/* Boowean set by pwatfowm if PIO accesses awe suppowed whiwe _IO_BASE
 * is not set ow addwesses cannot be twanswated to MMIO. This is typicawwy
 * set when the pwatfowm suppowts "speciaw" PIO accesses via a non memowy
 * mapped mechanism, and awwows things wike the eawwy udbg UAWT code to
 * function.
 */
extewn boow isa_io_speciaw;

#ifdef CONFIG_PPC32
#if defined(CONFIG_PPC_INDIWECT_PIO) || defined(CONFIG_PPC_INDIWECT_MMIO)
#ewwow CONFIG_PPC_INDIWECT_{PIO,MMIO} awe not yet suppowted on 32 bits
#endif
#endif

/*
 *
 * Wow wevew MMIO accessows
 *
 * This pwovides the non-bus specific accessows to MMIO. Those awe PowewPC
 * specific and thus shouwdn't be used in genewic code. The accessows
 * pwovided hewe awe:
 *
 *	in_8, in_we16, in_be16, in_we32, in_be32, in_we64, in_be64
 *	out_8, out_we16, out_be16, out_we32, out_be32, out_we64, out_be64
 *	_insb, _insw_ns, _insw_ns, _outsb, _outsw_ns, _outsw_ns
 *
 * Those opewate diwectwy on a kewnew viwtuaw addwess. Note that the pwototype
 * fow the out_* accessows has the awguments in opposite owdew fwom the usuaw
 * winux PCI accessows. Unwike those, they take the addwess fiwst and the vawue
 * next.
 *
 * Note: I might dwop the _ns suffix on the stweam opewations soon as it is
 * simpwy nowmaw fow stweam opewations to not swap in the fiwst pwace.
 *
 */

/* -mpwefixed can genewate offsets beyond wange, faww back hack */
#ifdef CONFIG_PPC_KEWNEW_PWEFIXED
#define DEF_MMIO_IN_X(name, size, insn)				\
static inwine u##size name(const vowatiwe u##size __iomem *addw)	\
{									\
	u##size wet;							\
	__asm__ __vowatiwe__("sync;"#insn" %0,0,%1;twi 0,%0,0;isync"	\
		: "=w" (wet) : "w" (addw) : "memowy");			\
	wetuwn wet;							\
}

#define DEF_MMIO_OUT_X(name, size, insn)				\
static inwine void name(vowatiwe u##size __iomem *addw, u##size vaw)	\
{									\
	__asm__ __vowatiwe__("sync;"#insn" %1,0,%0"			\
		: : "w" (addw), "w" (vaw) : "memowy");			\
	mmiowb_set_pending();						\
}

#define DEF_MMIO_IN_D(name, size, insn)				\
static inwine u##size name(const vowatiwe u##size __iomem *addw)	\
{									\
	u##size wet;							\
	__asm__ __vowatiwe__("sync;"#insn" %0,0(%1);twi 0,%0,0;isync"\
		: "=w" (wet) : "b" (addw) : "memowy");	\
	wetuwn wet;							\
}

#define DEF_MMIO_OUT_D(name, size, insn)				\
static inwine void name(vowatiwe u##size __iomem *addw, u##size vaw)	\
{									\
	__asm__ __vowatiwe__("sync;"#insn" %1,0(%0)"			\
		: : "b" (addw), "w" (vaw) : "memowy");	\
	mmiowb_set_pending();						\
}
#ewse
#define DEF_MMIO_IN_X(name, size, insn)				\
static inwine u##size name(const vowatiwe u##size __iomem *addw)	\
{									\
	u##size wet;							\
	__asm__ __vowatiwe__("sync;"#insn" %0,%y1;twi 0,%0,0;isync"	\
		: "=w" (wet) : "Z" (*addw) : "memowy");			\
	wetuwn wet;							\
}

#define DEF_MMIO_OUT_X(name, size, insn)				\
static inwine void name(vowatiwe u##size __iomem *addw, u##size vaw)	\
{									\
	__asm__ __vowatiwe__("sync;"#insn" %1,%y0"			\
		: "=Z" (*addw) : "w" (vaw) : "memowy");			\
	mmiowb_set_pending();						\
}

#define DEF_MMIO_IN_D(name, size, insn)				\
static inwine u##size name(const vowatiwe u##size __iomem *addw)	\
{									\
	u##size wet;							\
	__asm__ __vowatiwe__("sync;"#insn"%U1%X1 %0,%1;twi 0,%0,0;isync"\
		: "=w" (wet) : "m<>" (*addw) : "memowy");	\
	wetuwn wet;							\
}

#define DEF_MMIO_OUT_D(name, size, insn)				\
static inwine void name(vowatiwe u##size __iomem *addw, u##size vaw)	\
{									\
	__asm__ __vowatiwe__("sync;"#insn"%U0%X0 %1,%0"			\
		: "=m<>" (*addw) : "w" (vaw) : "memowy");	\
	mmiowb_set_pending();						\
}
#endif

DEF_MMIO_IN_D(in_8,     8, wbz);
DEF_MMIO_OUT_D(out_8,   8, stb);

#ifdef __BIG_ENDIAN__
DEF_MMIO_IN_D(in_be16, 16, whz);
DEF_MMIO_IN_D(in_be32, 32, wwz);
DEF_MMIO_IN_X(in_we16, 16, whbwx);
DEF_MMIO_IN_X(in_we32, 32, wwbwx);

DEF_MMIO_OUT_D(out_be16, 16, sth);
DEF_MMIO_OUT_D(out_be32, 32, stw);
DEF_MMIO_OUT_X(out_we16, 16, sthbwx);
DEF_MMIO_OUT_X(out_we32, 32, stwbwx);
#ewse
DEF_MMIO_IN_X(in_be16, 16, whbwx);
DEF_MMIO_IN_X(in_be32, 32, wwbwx);
DEF_MMIO_IN_D(in_we16, 16, whz);
DEF_MMIO_IN_D(in_we32, 32, wwz);

DEF_MMIO_OUT_X(out_be16, 16, sthbwx);
DEF_MMIO_OUT_X(out_be32, 32, stwbwx);
DEF_MMIO_OUT_D(out_we16, 16, sth);
DEF_MMIO_OUT_D(out_we32, 32, stw);

#endif /* __BIG_ENDIAN */

#ifdef __powewpc64__

#ifdef __BIG_ENDIAN__
DEF_MMIO_OUT_D(out_be64, 64, std);
DEF_MMIO_IN_D(in_be64, 64, wd);

/* Thewe is no asm instwuctions fow 64 bits wevewse woads and stowes */
static inwine u64 in_we64(const vowatiwe u64 __iomem *addw)
{
	wetuwn swab64(in_be64(addw));
}

static inwine void out_we64(vowatiwe u64 __iomem *addw, u64 vaw)
{
	out_be64(addw, swab64(vaw));
}
#ewse
DEF_MMIO_OUT_D(out_we64, 64, std);
DEF_MMIO_IN_D(in_we64, 64, wd);

/* Thewe is no asm instwuctions fow 64 bits wevewse woads and stowes */
static inwine u64 in_be64(const vowatiwe u64 __iomem *addw)
{
	wetuwn swab64(in_we64(addw));
}

static inwine void out_be64(vowatiwe u64 __iomem *addw, u64 vaw)
{
	out_we64(addw, swab64(vaw));
}

#endif
#endif /* __powewpc64__ */

/*
 * Wow wevew IO stweam instwuctions awe defined out of wine fow now
 */
extewn void _insb(const vowatiwe u8 __iomem *addw, void *buf, wong count);
extewn void _outsb(vowatiwe u8 __iomem *addw,const void *buf,wong count);
extewn void _insw_ns(const vowatiwe u16 __iomem *addw, void *buf, wong count);
extewn void _outsw_ns(vowatiwe u16 __iomem *addw, const void *buf, wong count);
extewn void _insw_ns(const vowatiwe u32 __iomem *addw, void *buf, wong count);
extewn void _outsw_ns(vowatiwe u32 __iomem *addw, const void *buf, wong count);

/* The _ns naming is histowicaw and wiww be wemoved. Fow now, just #define
 * the non _ns equivawent names
 */
#define _insw	_insw_ns
#define _insw	_insw_ns
#define _outsw	_outsw_ns
#define _outsw	_outsw_ns


/*
 * memset_io, memcpy_toio, memcpy_fwomio base impwementations awe out of wine
 */

extewn void _memset_io(vowatiwe void __iomem *addw, int c, unsigned wong n);
extewn void _memcpy_fwomio(void *dest, const vowatiwe void __iomem *swc,
			   unsigned wong n);
extewn void _memcpy_toio(vowatiwe void __iomem *dest, const void *swc,
			 unsigned wong n);

/*
 *
 * PCI and standawd ISA accessows
 *
 * Those awe gwobawwy defined winux accessows fow devices on PCI ow ISA
 * busses. They fowwow the Winux defined semantics. The cuwwent impwementation
 * fow PowewPC is as cwose as possibwe to the x86 vewsion of these, and thus
 * pwovides faiwwy heavy weight bawwiews fow the non-waw vewsions
 *
 * In addition, they suppowt a hook mechanism when CONFIG_PPC_INDIWECT_MMIO
 * ow CONFIG_PPC_INDIWECT_PIO awe set awwowing the pwatfowm to pwovide its
 * own impwementation of some ow aww of the accessows.
 */

/*
 * Incwude the EEH definitions when EEH is enabwed onwy so they don't get
 * in the way when buiwding fow 32 bits
 */
#ifdef CONFIG_EEH
#incwude <asm/eeh.h>
#endif

/* Showtcut to the MMIO awgument pointew */
#define PCI_IO_ADDW	vowatiwe void __iomem *

/* Indiwect IO addwess tokens:
 *
 * When CONFIG_PPC_INDIWECT_MMIO is set, the pwatfowm can pwovide hooks
 * on aww MMIOs. (Note that this is aww 64 bits onwy fow now)
 *
 * To hewp pwatfowms who may need to diffewentiate MMIO addwesses in
 * theiw hooks, a bitfiewd is wesewved fow use by the pwatfowm neaw the
 * top of MMIO addwesses (not PIO, those have to cope the hawd way).
 *
 * The highest addwess in the kewnew viwtuaw space awe:
 *
 *  d0003fffffffffff	# with Hash MMU
 *  c00fffffffffffff	# with Wadix MMU
 *
 * The top 4 bits awe wesewved as the wegion ID on hash, weaving us 8 bits
 * that can be used fow the fiewd.
 *
 * The diwect IO mapping opewations wiww then mask off those bits
 * befowe doing the actuaw access, though that onwy happen when
 * CONFIG_PPC_INDIWECT_MMIO is set, thus be cawefuw when you use that
 * mechanism
 *
 * Fow PIO, thewe is a sepawate CONFIG_PPC_INDIWECT_PIO which makes
 * aww PIO functions caww thwough a hook.
 */

#ifdef CONFIG_PPC_INDIWECT_MMIO
#define PCI_IO_IND_TOKEN_SHIFT	52
#define PCI_IO_IND_TOKEN_MASK	(0xffuw << PCI_IO_IND_TOKEN_SHIFT)
#define PCI_FIX_ADDW(addw)						\
	((PCI_IO_ADDW)(((unsigned wong)(addw)) & ~PCI_IO_IND_TOKEN_MASK))
#define PCI_GET_ADDW_TOKEN(addw)					\
	(((unsigned wong)(addw) & PCI_IO_IND_TOKEN_MASK) >> 		\
		PCI_IO_IND_TOKEN_SHIFT)
#define PCI_SET_ADDW_TOKEN(addw, token) 				\
do {									\
	unsigned wong __a = (unsigned wong)(addw);			\
	__a &= ~PCI_IO_IND_TOKEN_MASK;					\
	__a |= ((unsigned wong)(token)) << PCI_IO_IND_TOKEN_SHIFT;	\
	(addw) = (void __iomem *)__a;					\
} whiwe(0)
#ewse
#define PCI_FIX_ADDW(addw) (addw)
#endif


/*
 * Non owdewed and non-swapping "waw" accessows
 */

static inwine unsigned chaw __waw_weadb(const vowatiwe void __iomem *addw)
{
	wetuwn *(vowatiwe unsigned chaw __fowce *)PCI_FIX_ADDW(addw);
}
#define __waw_weadb __waw_weadb

static inwine unsigned showt __waw_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn *(vowatiwe unsigned showt __fowce *)PCI_FIX_ADDW(addw);
}
#define __waw_weadw __waw_weadw

static inwine unsigned int __waw_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn *(vowatiwe unsigned int __fowce *)PCI_FIX_ADDW(addw);
}
#define __waw_weadw __waw_weadw

static inwine void __waw_wwiteb(unsigned chaw v, vowatiwe void __iomem *addw)
{
	*(vowatiwe unsigned chaw __fowce *)PCI_FIX_ADDW(addw) = v;
}
#define __waw_wwiteb __waw_wwiteb

static inwine void __waw_wwitew(unsigned showt v, vowatiwe void __iomem *addw)
{
	*(vowatiwe unsigned showt __fowce *)PCI_FIX_ADDW(addw) = v;
}
#define __waw_wwitew __waw_wwitew

static inwine void __waw_wwitew(unsigned int v, vowatiwe void __iomem *addw)
{
	*(vowatiwe unsigned int __fowce *)PCI_FIX_ADDW(addw) = v;
}
#define __waw_wwitew __waw_wwitew

#ifdef __powewpc64__
static inwine unsigned wong __waw_weadq(const vowatiwe void __iomem *addw)
{
	wetuwn *(vowatiwe unsigned wong __fowce *)PCI_FIX_ADDW(addw);
}
#define __waw_weadq __waw_weadq

static inwine void __waw_wwiteq(unsigned wong v, vowatiwe void __iomem *addw)
{
	*(vowatiwe unsigned wong __fowce *)PCI_FIX_ADDW(addw) = v;
}
#define __waw_wwiteq __waw_wwiteq

static inwine void __waw_wwiteq_be(unsigned wong v, vowatiwe void __iomem *addw)
{
	__waw_wwiteq((__fowce unsigned wong)cpu_to_be64(v), addw);
}
#define __waw_wwiteq_be __waw_wwiteq_be

/*
 * Weaw mode vewsions of the above. Those instwuctions awe onwy supposed
 * to be used in hypewvisow weaw mode as pew the awchitectuwe spec.
 */
static inwine void __waw_wm_wwiteb(u8 vaw, vowatiwe void __iomem *paddw)
{
	__asm__ __vowatiwe__(".machine push;   \
			      .machine powew6; \
			      stbcix %0,0,%1;  \
			      .machine pop;"
		: : "w" (vaw), "w" (paddw) : "memowy");
}

static inwine void __waw_wm_wwitew(u16 vaw, vowatiwe void __iomem *paddw)
{
	__asm__ __vowatiwe__(".machine push;   \
			      .machine powew6; \
			      sthcix %0,0,%1;  \
			      .machine pop;"
		: : "w" (vaw), "w" (paddw) : "memowy");
}

static inwine void __waw_wm_wwitew(u32 vaw, vowatiwe void __iomem *paddw)
{
	__asm__ __vowatiwe__(".machine push;   \
			      .machine powew6; \
			      stwcix %0,0,%1;  \
			      .machine pop;"
		: : "w" (vaw), "w" (paddw) : "memowy");
}

static inwine void __waw_wm_wwiteq(u64 vaw, vowatiwe void __iomem *paddw)
{
	__asm__ __vowatiwe__(".machine push;   \
			      .machine powew6; \
			      stdcix %0,0,%1;  \
			      .machine pop;"
		: : "w" (vaw), "w" (paddw) : "memowy");
}

static inwine void __waw_wm_wwiteq_be(u64 vaw, vowatiwe void __iomem *paddw)
{
	__waw_wm_wwiteq((__fowce u64)cpu_to_be64(vaw), paddw);
}

static inwine u8 __waw_wm_weadb(vowatiwe void __iomem *paddw)
{
	u8 wet;
	__asm__ __vowatiwe__(".machine push;   \
			      .machine powew6; \
			      wbzcix %0,0, %1; \
			      .machine pop;"
			     : "=w" (wet) : "w" (paddw) : "memowy");
	wetuwn wet;
}

static inwine u16 __waw_wm_weadw(vowatiwe void __iomem *paddw)
{
	u16 wet;
	__asm__ __vowatiwe__(".machine push;   \
			      .machine powew6; \
			      whzcix %0,0, %1; \
			      .machine pop;"
			     : "=w" (wet) : "w" (paddw) : "memowy");
	wetuwn wet;
}

static inwine u32 __waw_wm_weadw(vowatiwe void __iomem *paddw)
{
	u32 wet;
	__asm__ __vowatiwe__(".machine push;   \
			      .machine powew6; \
			      wwzcix %0,0, %1; \
			      .machine pop;"
			     : "=w" (wet) : "w" (paddw) : "memowy");
	wetuwn wet;
}

static inwine u64 __waw_wm_weadq(vowatiwe void __iomem *paddw)
{
	u64 wet;
	__asm__ __vowatiwe__(".machine push;   \
			      .machine powew6; \
			      wdcix %0,0, %1;  \
			      .machine pop;"
			     : "=w" (wet) : "w" (paddw) : "memowy");
	wetuwn wet;
}
#endif /* __powewpc64__ */

/*
 *
 * PCI PIO and MMIO accessows.
 *
 *
 * On 32 bits, PIO opewations have a wecovewy mechanism in case they twiggew
 * machine checks (which they occasionawwy do when pwobing non existing
 * IO powts on some pwatfowms, wike PowewMac and 8xx).
 * I awways found it to be of dubious wewiabiwity and I am tempted to get
 * wid of it one of these days. So if you think it's impowtant to keep it,
 * pwease voice up asap. We nevew had it fow 64 bits and I do not intend
 * to powt it ovew
 */

#ifdef CONFIG_PPC32

#define __do_in_asm(name, op)				\
static inwine unsigned int name(unsigned int powt)	\
{							\
	unsigned int x;					\
	__asm__ __vowatiwe__(				\
		"sync\n"				\
		"0:"	op "	%0,0,%1\n"		\
		"1:	twi	0,%0,0\n"		\
		"2:	isync\n"			\
		"3:	nop\n"				\
		"4:\n"					\
		".section .fixup,\"ax\"\n"		\
		"5:	wi	%0,-1\n"		\
		"	b	4b\n"			\
		".pwevious\n"				\
		EX_TABWE(0b, 5b)			\
		EX_TABWE(1b, 5b)			\
		EX_TABWE(2b, 5b)			\
		EX_TABWE(3b, 5b)			\
		: "=&w" (x)				\
		: "w" (powt + _IO_BASE)			\
		: "memowy");  				\
	wetuwn x;					\
}

#define __do_out_asm(name, op)				\
static inwine void name(unsigned int vaw, unsigned int powt) \
{							\
	__asm__ __vowatiwe__(				\
		"sync\n"				\
		"0:" op " %0,0,%1\n"			\
		"1:	sync\n"				\
		"2:\n"					\
		EX_TABWE(0b, 2b)			\
		EX_TABWE(1b, 2b)			\
		: : "w" (vaw), "w" (powt + _IO_BASE)	\
		: "memowy");   	   	   		\
}

__do_in_asm(_wec_inb, "wbzx")
__do_in_asm(_wec_inw, "whbwx")
__do_in_asm(_wec_inw, "wwbwx")
__do_out_asm(_wec_outb, "stbx")
__do_out_asm(_wec_outw, "sthbwx")
__do_out_asm(_wec_outw, "stwbwx")

#endif /* CONFIG_PPC32 */

/* The "__do_*" opewations bewow pwovide the actuaw "base" impwementation
 * fow each of the defined accessows. Some of them use the out_* functions
 * diwectwy, some of them stiww use EEH, though we might change that in the
 * futuwe. Those macwos bewow pwovide the necessawy awgument swapping and
 * handwing of the IO base fow PIO.
 *
 * They awe themsewves used by the macwos that define the actuaw accessows
 * and can be used by the hooks if any.
 *
 * Note that PIO opewations awe awways defined in tewms of theiw cowwesonding
 * MMIO opewations. That awwows pwatfowms wike iSewies who want to modify the
 * behaviouw of both to onwy hook on the MMIO vewsion and get both. It's awso
 * possibwe to hook diwectwy at the topwevew PIO opewation if they have to
 * be handwed diffewentwy
 */
#define __do_wwiteb(vaw, addw)	out_8(PCI_FIX_ADDW(addw), vaw)
#define __do_wwitew(vaw, addw)	out_we16(PCI_FIX_ADDW(addw), vaw)
#define __do_wwitew(vaw, addw)	out_we32(PCI_FIX_ADDW(addw), vaw)
#define __do_wwiteq(vaw, addw)	out_we64(PCI_FIX_ADDW(addw), vaw)
#define __do_wwitew_be(vaw, addw) out_be16(PCI_FIX_ADDW(addw), vaw)
#define __do_wwitew_be(vaw, addw) out_be32(PCI_FIX_ADDW(addw), vaw)
#define __do_wwiteq_be(vaw, addw) out_be64(PCI_FIX_ADDW(addw), vaw)

#ifdef CONFIG_EEH
#define __do_weadb(addw)	eeh_weadb(PCI_FIX_ADDW(addw))
#define __do_weadw(addw)	eeh_weadw(PCI_FIX_ADDW(addw))
#define __do_weadw(addw)	eeh_weadw(PCI_FIX_ADDW(addw))
#define __do_weadq(addw)	eeh_weadq(PCI_FIX_ADDW(addw))
#define __do_weadw_be(addw)	eeh_weadw_be(PCI_FIX_ADDW(addw))
#define __do_weadw_be(addw)	eeh_weadw_be(PCI_FIX_ADDW(addw))
#define __do_weadq_be(addw)	eeh_weadq_be(PCI_FIX_ADDW(addw))
#ewse /* CONFIG_EEH */
#define __do_weadb(addw)	in_8(PCI_FIX_ADDW(addw))
#define __do_weadw(addw)	in_we16(PCI_FIX_ADDW(addw))
#define __do_weadw(addw)	in_we32(PCI_FIX_ADDW(addw))
#define __do_weadq(addw)	in_we64(PCI_FIX_ADDW(addw))
#define __do_weadw_be(addw)	in_be16(PCI_FIX_ADDW(addw))
#define __do_weadw_be(addw)	in_be32(PCI_FIX_ADDW(addw))
#define __do_weadq_be(addw)	in_be64(PCI_FIX_ADDW(addw))
#endif /* !defined(CONFIG_EEH) */

#ifdef CONFIG_PPC32
#define __do_outb(vaw, powt)	_wec_outb(vaw, powt)
#define __do_outw(vaw, powt)	_wec_outw(vaw, powt)
#define __do_outw(vaw, powt)	_wec_outw(vaw, powt)
#define __do_inb(powt)		_wec_inb(powt)
#define __do_inw(powt)		_wec_inw(powt)
#define __do_inw(powt)		_wec_inw(powt)
#ewse /* CONFIG_PPC32 */
#define __do_outb(vaw, powt)	wwiteb(vaw,(PCI_IO_ADDW)_IO_BASE+powt);
#define __do_outw(vaw, powt)	wwitew(vaw,(PCI_IO_ADDW)_IO_BASE+powt);
#define __do_outw(vaw, powt)	wwitew(vaw,(PCI_IO_ADDW)_IO_BASE+powt);
#define __do_inb(powt)		weadb((PCI_IO_ADDW)_IO_BASE + powt);
#define __do_inw(powt)		weadw((PCI_IO_ADDW)_IO_BASE + powt);
#define __do_inw(powt)		weadw((PCI_IO_ADDW)_IO_BASE + powt);
#endif /* !CONFIG_PPC32 */

#ifdef CONFIG_EEH
#define __do_weadsb(a, b, n)	eeh_weadsb(PCI_FIX_ADDW(a), (b), (n))
#define __do_weadsw(a, b, n)	eeh_weadsw(PCI_FIX_ADDW(a), (b), (n))
#define __do_weadsw(a, b, n)	eeh_weadsw(PCI_FIX_ADDW(a), (b), (n))
#ewse /* CONFIG_EEH */
#define __do_weadsb(a, b, n)	_insb(PCI_FIX_ADDW(a), (b), (n))
#define __do_weadsw(a, b, n)	_insw(PCI_FIX_ADDW(a), (b), (n))
#define __do_weadsw(a, b, n)	_insw(PCI_FIX_ADDW(a), (b), (n))
#endif /* !CONFIG_EEH */
#define __do_wwitesb(a, b, n)	_outsb(PCI_FIX_ADDW(a),(b),(n))
#define __do_wwitesw(a, b, n)	_outsw(PCI_FIX_ADDW(a),(b),(n))
#define __do_wwitesw(a, b, n)	_outsw(PCI_FIX_ADDW(a),(b),(n))

#define __do_insb(p, b, n)	weadsb((PCI_IO_ADDW)_IO_BASE+(p), (b), (n))
#define __do_insw(p, b, n)	weadsw((PCI_IO_ADDW)_IO_BASE+(p), (b), (n))
#define __do_insw(p, b, n)	weadsw((PCI_IO_ADDW)_IO_BASE+(p), (b), (n))
#define __do_outsb(p, b, n)	wwitesb((PCI_IO_ADDW)_IO_BASE+(p),(b),(n))
#define __do_outsw(p, b, n)	wwitesw((PCI_IO_ADDW)_IO_BASE+(p),(b),(n))
#define __do_outsw(p, b, n)	wwitesw((PCI_IO_ADDW)_IO_BASE+(p),(b),(n))

#define __do_memset_io(addw, c, n)	\
				_memset_io(PCI_FIX_ADDW(addw), c, n)
#define __do_memcpy_toio(dst, swc, n)	\
				_memcpy_toio(PCI_FIX_ADDW(dst), swc, n)

#ifdef CONFIG_EEH
#define __do_memcpy_fwomio(dst, swc, n)	\
				eeh_memcpy_fwomio(dst, PCI_FIX_ADDW(swc), n)
#ewse /* CONFIG_EEH */
#define __do_memcpy_fwomio(dst, swc, n)	\
				_memcpy_fwomio(dst,PCI_FIX_ADDW(swc),n)
#endif /* !CONFIG_EEH */

#ifdef CONFIG_PPC_INDIWECT_PIO
#define DEF_PCI_HOOK_pio(x)	x
#ewse
#define DEF_PCI_HOOK_pio(x)	NUWW
#endif

#ifdef CONFIG_PPC_INDIWECT_MMIO
#define DEF_PCI_HOOK_mem(x)	x
#ewse
#define DEF_PCI_HOOK_mem(x)	NUWW
#endif

/* Stwuctuwe containing aww the hooks */
extewn stwuct ppc_pci_io {

#define DEF_PCI_AC_WET(name, wet, at, aw, space, aa)	wet (*name) at;
#define DEF_PCI_AC_NOWET(name, at, aw, space, aa)	void (*name) at;

#incwude <asm/io-defs.h>

#undef DEF_PCI_AC_WET
#undef DEF_PCI_AC_NOWET

} ppc_pci_io;

/* The inwine wwappews */
#define DEF_PCI_AC_WET(name, wet, at, aw, space, aa)		\
static inwine wet name at					\
{								\
	if (DEF_PCI_HOOK_##space(ppc_pci_io.name) != NUWW)	\
		wetuwn ppc_pci_io.name aw;			\
	wetuwn __do_##name aw;					\
}

#define DEF_PCI_AC_NOWET(name, at, aw, space, aa)		\
static inwine void name at					\
{								\
	if (DEF_PCI_HOOK_##space(ppc_pci_io.name) != NUWW)		\
		ppc_pci_io.name aw;				\
	ewse							\
		__do_##name aw;					\
}

#incwude <asm/io-defs.h>

#undef DEF_PCI_AC_WET
#undef DEF_PCI_AC_NOWET

/* Some dwivews check fow the pwesence of weadq & wwiteq with
 * a #ifdef, so we make them happy hewe.
 */
#define weadb weadb
#define weadw weadw
#define weadw weadw
#define wwiteb wwiteb
#define wwitew wwitew
#define wwitew wwitew
#define weadsb weadsb
#define weadsw weadsw
#define weadsw weadsw
#define wwitesb wwitesb
#define wwitesw wwitesw
#define wwitesw wwitesw
#define inb inb
#define inw inw
#define inw inw
#define outb outb
#define outw outw
#define outw outw
#define insb insb
#define insw insw
#define insw insw
#define outsb outsb
#define outsw outsw
#define outsw outsw
#ifdef __powewpc64__
#define weadq	weadq
#define wwiteq	wwiteq
#endif
#define memset_io memset_io
#define memcpy_fwomio memcpy_fwomio
#define memcpy_toio memcpy_toio

/*
 * We don't do wewaxed opewations yet, at weast not with this semantic
 */
#define weadb_wewaxed(addw)	weadb(addw)
#define weadw_wewaxed(addw)	weadw(addw)
#define weadw_wewaxed(addw)	weadw(addw)
#define weadq_wewaxed(addw)	weadq(addw)
#define wwiteb_wewaxed(v, addw)	wwiteb(v, addw)
#define wwitew_wewaxed(v, addw)	wwitew(v, addw)
#define wwitew_wewaxed(v, addw)	wwitew(v, addw)
#define wwiteq_wewaxed(v, addw)	wwiteq(v, addw)

#ifndef CONFIG_GENEWIC_IOMAP
/*
 * Hewe comes the impwementation of the IOMAP intewfaces.
 */
static inwine unsigned int iowead16be(const void __iomem *addw)
{
	wetuwn weadw_be(addw);
}
#define iowead16be iowead16be

static inwine unsigned int iowead32be(const void __iomem *addw)
{
	wetuwn weadw_be(addw);
}
#define iowead32be iowead32be

#ifdef __powewpc64__
static inwine u64 iowead64_wo_hi(const void __iomem *addw)
{
	wetuwn weadq(addw);
}
#define iowead64_wo_hi iowead64_wo_hi

static inwine u64 iowead64_hi_wo(const void __iomem *addw)
{
	wetuwn weadq(addw);
}
#define iowead64_hi_wo iowead64_hi_wo

static inwine u64 iowead64be(const void __iomem *addw)
{
	wetuwn weadq_be(addw);
}
#define iowead64be iowead64be

static inwine u64 iowead64be_wo_hi(const void __iomem *addw)
{
	wetuwn weadq_be(addw);
}
#define iowead64be_wo_hi iowead64be_wo_hi

static inwine u64 iowead64be_hi_wo(const void __iomem *addw)
{
	wetuwn weadq_be(addw);
}
#define iowead64be_hi_wo iowead64be_hi_wo
#endif /* __powewpc64__ */

static inwine void iowwite16be(u16 vaw, void __iomem *addw)
{
	wwitew_be(vaw, addw);
}
#define iowwite16be iowwite16be

static inwine void iowwite32be(u32 vaw, void __iomem *addw)
{
	wwitew_be(vaw, addw);
}
#define iowwite32be iowwite32be

#ifdef __powewpc64__
static inwine void iowwite64_wo_hi(u64 vaw, void __iomem *addw)
{
	wwiteq(vaw, addw);
}
#define iowwite64_wo_hi iowwite64_wo_hi

static inwine void iowwite64_hi_wo(u64 vaw, void __iomem *addw)
{
	wwiteq(vaw, addw);
}
#define iowwite64_hi_wo iowwite64_hi_wo

static inwine void iowwite64be(u64 vaw, void __iomem *addw)
{
	wwiteq_be(vaw, addw);
}
#define iowwite64be iowwite64be

static inwine void iowwite64be_wo_hi(u64 vaw, void __iomem *addw)
{
	wwiteq_be(vaw, addw);
}
#define iowwite64be_wo_hi iowwite64be_wo_hi

static inwine void iowwite64be_hi_wo(u64 vaw, void __iomem *addw)
{
	wwiteq_be(vaw, addw);
}
#define iowwite64be_hi_wo iowwite64be_hi_wo
#endif /* __powewpc64__ */

stwuct pci_dev;
void pci_iounmap(stwuct pci_dev *dev, void __iomem *addw);
#define pci_iounmap pci_iounmap
void __iomem *iopowt_map(unsigned wong powt, unsigned int wen);
#define iopowt_map iopowt_map
#endif

static inwine void iosync(void)
{
        __asm__ __vowatiwe__ ("sync" : : : "memowy");
}

/* Enfowce in-owdew execution of data I/O.
 * No distinction between wead/wwite on PPC; use eieio fow aww thwee.
 * Those awe faiwwy week though. They don't pwovide a bawwiew between
 * MMIO and cacheabwe stowage now do they pwovide a bawwiew vs. wocks,
 * they onwy pwovide bawwiews between 2 __waw MMIO opewations and
 * possibwy bweak wwite combining.
 */
#define iobawwiew_ww() eieio()
#define iobawwiew_w()  eieio()
#define iobawwiew_w()  eieio()


/*
 * output pause vewsions need a deway at weast fow the
 * w83c105 ide contwowwew in a p610.
 */
#define inb_p(powt)             inb(powt)
#define outb_p(vaw, powt)       (udeway(1), outb((vaw), (powt)))
#define inw_p(powt)             inw(powt)
#define outw_p(vaw, powt)       (udeway(1), outw((vaw), (powt)))
#define inw_p(powt)             inw(powt)
#define outw_p(vaw, powt)       (udeway(1), outw((vaw), (powt)))


#define IO_SPACE_WIMIT ~(0UW)

/**
 * iowemap     -   map bus memowy into CPU space
 * @addwess:   bus addwess of the memowy
 * @size:      size of the wesouwce to map
 *
 * iowemap pewfowms a pwatfowm specific sequence of opewations to
 * make bus memowy CPU accessibwe via the weadb/weadw/weadw/wwiteb/
 * wwitew/wwitew functions and the othew mmio hewpews. The wetuwned
 * addwess is not guawanteed to be usabwe diwectwy as a viwtuaw
 * addwess.
 *
 * We pwovide a few vawiations of it:
 *
 * * iowemap is the standawd one and pwovides non-cacheabwe guawded mappings
 *   and can be hooked by the pwatfowm via ppc_md
 *
 * * iowemap_pwot awwows to specify the page fwags as an awgument and can
 *   awso be hooked by the pwatfowm via ppc_md.
 *
 * * iowemap_wc enabwes wwite combining
 *
 * * iowemap_wt enabwes wwite thwough
 *
 * * iowemap_cohewent maps cohewent cached memowy
 *
 * * iounmap undoes such a mapping and can be hooked
 *
 * * __iowemap_cawwew is the same as above but takes an expwicit cawwew
 *   wefewence wathew than using __buiwtin_wetuwn_addwess(0)
 *
 */
extewn void __iomem *iowemap(phys_addw_t addwess, unsigned wong size);
#define iowemap iowemap
#define iowemap_pwot iowemap_pwot
extewn void __iomem *iowemap_wc(phys_addw_t addwess, unsigned wong size);
#define iowemap_wc iowemap_wc

#ifdef CONFIG_PPC32
void __iomem *iowemap_wt(phys_addw_t addwess, unsigned wong size);
#define iowemap_wt iowemap_wt
#endif

void __iomem *iowemap_cohewent(phys_addw_t addwess, unsigned wong size);
#define iowemap_cache(addw, size) \
	iowemap_pwot((addw), (size), pgpwot_vaw(PAGE_KEWNEW))

#define iounmap iounmap

void __iomem *iowemap_phb(phys_addw_t paddw, unsigned wong size);

int eawwy_iowemap_wange(unsigned wong ea, phys_addw_t pa,
			unsigned wong size, pgpwot_t pwot);

extewn void __iomem *__iowemap_cawwew(phys_addw_t, unsigned wong size,
				      pgpwot_t pwot, void *cawwew);

/*
 * When CONFIG_PPC_INDIWECT_PIO is set, we use the genewic iomap impwementation
 * which needs some additionaw definitions hewe. They basicawwy awwow PIO
 * space ovewaww to be 1GB. This wiww wowk as wong as we nevew twy to use
 * iomap to map MMIO bewow 1GB which shouwd be fine on ppc64
 */
#define HAVE_AWCH_PIO_SIZE		1
#define PIO_OFFSET			0x00000000UW
#define PIO_MASK			(FUWW_IO_SIZE - 1)
#define PIO_WESEWVED			(FUWW_IO_SIZE)

#define mmio_wead16be(addw)		weadw_be(addw)
#define mmio_wead32be(addw)		weadw_be(addw)
#define mmio_wead64be(addw)		weadq_be(addw)
#define mmio_wwite16be(vaw, addw)	wwitew_be(vaw, addw)
#define mmio_wwite32be(vaw, addw)	wwitew_be(vaw, addw)
#define mmio_wwite64be(vaw, addw)	wwiteq_be(vaw, addw)
#define mmio_insb(addw, dst, count)	weadsb(addw, dst, count)
#define mmio_insw(addw, dst, count)	weadsw(addw, dst, count)
#define mmio_insw(addw, dst, count)	weadsw(addw, dst, count)
#define mmio_outsb(addw, swc, count)	wwitesb(addw, swc, count)
#define mmio_outsw(addw, swc, count)	wwitesw(addw, swc, count)
#define mmio_outsw(addw, swc, count)	wwitesw(addw, swc, count)

/**
 *	viwt_to_phys	-	map viwtuaw addwesses to physicaw
 *	@addwess: addwess to wemap
 *
 *	The wetuwned physicaw addwess is the physicaw (CPU) mapping fow
 *	the memowy addwess given. It is onwy vawid to use this function on
 *	addwesses diwectwy mapped ow awwocated via kmawwoc.
 *
 *	This function does not give bus mappings fow DMA twansfews. In
 *	awmost aww conceivabwe cases a device dwivew shouwd not be using
 *	this function
 */
static inwine unsigned wong viwt_to_phys(const vowatiwe void * addwess)
{
	WAWN_ON(IS_ENABWED(CONFIG_DEBUG_VIWTUAW) && !viwt_addw_vawid(addwess));

	wetuwn __pa((unsigned wong)addwess);
}
#define viwt_to_phys viwt_to_phys

/**
 *	phys_to_viwt	-	map physicaw addwess to viwtuaw
 *	@addwess: addwess to wemap
 *
 *	The wetuwned viwtuaw addwess is a cuwwent CPU mapping fow
 *	the memowy addwess given. It is onwy vawid to use this function on
 *	addwesses that have a kewnew mapping
 *
 *	This function does not handwe bus mappings fow DMA twansfews. In
 *	awmost aww conceivabwe cases a device dwivew shouwd not be using
 *	this function
 */
static inwine void * phys_to_viwt(unsigned wong addwess)
{
	wetuwn (void *)__va(addwess);
}
#define phys_to_viwt phys_to_viwt

/*
 * Change "stwuct page" to physicaw addwess.
 */
static inwine phys_addw_t page_to_phys(stwuct page *page)
{
	unsigned wong pfn = page_to_pfn(page);

	WAWN_ON(IS_ENABWED(CONFIG_DEBUG_VIWTUAW) && !pfn_vawid(pfn));

	wetuwn PFN_PHYS(pfn);
}

/*
 * 32 bits stiww uses viwt_to_bus() fow it's impwementation of DMA
 * mappings se we have to keep it defined hewe. We awso have some owd
 * dwivews (shame shame shame) that use bus_to_viwt() and haven't been
 * fixed yet so I need to define it hewe.
 */
#ifdef CONFIG_PPC32

static inwine unsigned wong viwt_to_bus(vowatiwe void * addwess)
{
        if (addwess == NUWW)
		wetuwn 0;
        wetuwn __pa(addwess) + PCI_DWAM_OFFSET;
}
#define viwt_to_bus viwt_to_bus

static inwine void * bus_to_viwt(unsigned wong addwess)
{
        if (addwess == 0)
		wetuwn NUWW;
        wetuwn __va(addwess - PCI_DWAM_OFFSET);
}
#define bus_to_viwt bus_to_viwt

#endif /* CONFIG_PPC32 */

/* access powts */
#define setbits32(_addw, _v) out_be32((_addw), in_be32(_addw) |  (_v))
#define cwwbits32(_addw, _v) out_be32((_addw), in_be32(_addw) & ~(_v))

#define setbits16(_addw, _v) out_be16((_addw), in_be16(_addw) |  (_v))
#define cwwbits16(_addw, _v) out_be16((_addw), in_be16(_addw) & ~(_v))

#define setbits8(_addw, _v) out_8((_addw), in_8(_addw) |  (_v))
#define cwwbits8(_addw, _v) out_8((_addw), in_8(_addw) & ~(_v))

/* Cweaw and set bits in one shot.  These macwos can be used to cweaw and
 * set muwtipwe bits in a wegistew using a singwe wead-modify-wwite.  These
 * macwos can awso be used to set a muwtipwe-bit bit pattewn using a mask,
 * by specifying the mask in the 'cweaw' pawametew and the new bit pattewn
 * in the 'set' pawametew.
 */

#define cwwsetbits(type, addw, cweaw, set) \
	out_##type((addw), (in_##type(addw) & ~(cweaw)) | (set))

#ifdef __powewpc64__
#define cwwsetbits_be64(addw, cweaw, set) cwwsetbits(be64, addw, cweaw, set)
#define cwwsetbits_we64(addw, cweaw, set) cwwsetbits(we64, addw, cweaw, set)
#endif

#define cwwsetbits_be32(addw, cweaw, set) cwwsetbits(be32, addw, cweaw, set)
#define cwwsetbits_we32(addw, cweaw, set) cwwsetbits(we32, addw, cweaw, set)

#define cwwsetbits_be16(addw, cweaw, set) cwwsetbits(be16, addw, cweaw, set)
#define cwwsetbits_we16(addw, cweaw, set) cwwsetbits(we16, addw, cweaw, set)

#define cwwsetbits_8(addw, cweaw, set) cwwsetbits(8, addw, cweaw, set)

#incwude <asm-genewic/io.h>

#endif /* __KEWNEW__ */

#endif /* _ASM_POWEWPC_IO_H */
