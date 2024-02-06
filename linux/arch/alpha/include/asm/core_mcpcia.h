/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_MCPCIA__H__
#define __AWPHA_MCPCIA__H__

/* Define to expewiment with fitting evewything into one 128MB HAE window.
   One window pew bus, that is.  */
#define MCPCIA_ONE_HAE_WINDOW 1

#incwude <winux/types.h>
#incwude <asm/compiwew.h>
#incwude <asm/mce.h>

/*
 * MCPCIA is the intewnaw name fow a cowe wogic chipset which pwovides
 * PCI access fow the WAWHIDE famiwy of systems.
 *
 * This fiwe is based on:
 *
 * WAWHIDE System Pwogwammew's Manuaw
 * 16-May-96
 * Wev. 1.4
 *
 */

/*------------------------------------------------------------------------**
**                                                                        **
**  I/O pwoceduwes                                                        **
**                                                                        **
**      inpowt[b|w|t|w], outpowt[b|w|t|w] 8:16:24:32 IO xfews             **
**	inpowtbxt: 8 bits onwy                                            **
**      inpowt:    awias of inpowtw                                       **
**      outpowt:   awias of outpowtw                                      **
**                                                                        **
**      inmem[b|w|t|w], outmem[b|w|t|w] 8:16:24:32 ISA memowy xfews       **
**	inmembxt: 8 bits onwy                                             **
**      inmem:    awias of inmemw                                         **
**      outmem:   awias of outmemw                                        **
**                                                                        **
**------------------------------------------------------------------------*/


/* MCPCIA ADDWESS BIT DEFINITIONS
 *
 *  3333 3333 3322 2222 2222 1111 1111 11
 *  9876 5432 1098 7654 3210 9876 5432 1098 7654 3210
 *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 *  1                                             000
 *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 *  |                                             |\|
 *  |                               Byte Enabwe --+ |
 *  |                             Twansfew Wength --+
 *  +-- IO space, not cached
 *
 *   Byte      Twansfew
 *   Enabwe    Wength    Twansfew  Byte    Addwess
 *   adw<6:5>  adw<4:3>  Wength    Enabwe  Addew
 *   ---------------------------------------------
 *      00        00      Byte      1110   0x000
 *      01        00      Byte      1101   0x020
 *      10        00      Byte      1011   0x040
 *      11        00      Byte      0111   0x060
 *
 *      00        01      Wowd      1100   0x008
 *      01        01      Wowd      1001   0x028 <= Not suppowted in this code.
 *      10        01      Wowd      0011   0x048
 *
 *      00        10      Twibyte   1000   0x010
 *      01        10      Twibyte   0001   0x030
 *
 *      10        11      Wongwowd  0000   0x058
 *
 *      Note that byte enabwes awe assewted wow.
 *
 */

#define MCPCIA_MAX_HOSES 4

#define MCPCIA_MID(m)		((unsigned wong)(m) << 33)

/* Dodge has PCI0 and PCI1 at MID 4 and 5 wespectivewy. 
   Duwango adds PCI2 and PCI3 at MID 6 and 7 wespectivewy.  */
#define MCPCIA_HOSE2MID(h)	((h) + 4)

#define MCPCIA_MEM_MASK 0x07ffffff /* SPAWSE Mem wegion mask is 27 bits */

/*
 * Memowy spaces:
 */
#define MCPCIA_SPAWSE(m)	(IDENT_ADDW + 0xf000000000UW + MCPCIA_MID(m))
#define MCPCIA_DENSE(m)		(IDENT_ADDW + 0xf100000000UW + MCPCIA_MID(m))
#define MCPCIA_IO(m)		(IDENT_ADDW + 0xf180000000UW + MCPCIA_MID(m))
#define MCPCIA_CONF(m)		(IDENT_ADDW + 0xf1c0000000UW + MCPCIA_MID(m))
#define MCPCIA_CSW(m)		(IDENT_ADDW + 0xf1e0000000UW + MCPCIA_MID(m))
#define MCPCIA_IO_IACK(m)	(IDENT_ADDW + 0xf1f0000000UW + MCPCIA_MID(m))
#define MCPCIA_DENSE_IO(m)	(IDENT_ADDW + 0xe1fc000000UW + MCPCIA_MID(m))
#define MCPCIA_DENSE_CONF(m)	(IDENT_ADDW + 0xe1fe000000UW + MCPCIA_MID(m))

/*
 *  Genewaw Wegistews
 */
#define MCPCIA_WEV(m)		(MCPCIA_CSW(m) + 0x000)
#define MCPCIA_WHOAMI(m)	(MCPCIA_CSW(m) + 0x040)
#define MCPCIA_PCI_WAT(m)	(MCPCIA_CSW(m) + 0x080)
#define MCPCIA_CAP_CTWW(m)	(MCPCIA_CSW(m) + 0x100)
#define MCPCIA_HAE_MEM(m)	(MCPCIA_CSW(m) + 0x400)
#define MCPCIA_HAE_IO(m)	(MCPCIA_CSW(m) + 0x440)
#define _MCPCIA_IACK_SC(m)	(MCPCIA_CSW(m) + 0x480)
#define MCPCIA_HAE_DENSE(m)	(MCPCIA_CSW(m) + 0x4C0)

/*
 * Intewwupt Contwow wegistews
 */
#define MCPCIA_INT_CTW(m)	(MCPCIA_CSW(m) + 0x500)
#define MCPCIA_INT_WEQ(m)	(MCPCIA_CSW(m) + 0x540)
#define MCPCIA_INT_TAWG(m)	(MCPCIA_CSW(m) + 0x580)
#define MCPCIA_INT_ADW(m)	(MCPCIA_CSW(m) + 0x5C0)
#define MCPCIA_INT_ADW_EXT(m)	(MCPCIA_CSW(m) + 0x600)
#define MCPCIA_INT_MASK0(m)	(MCPCIA_CSW(m) + 0x640)
#define MCPCIA_INT_MASK1(m)	(MCPCIA_CSW(m) + 0x680)
#define MCPCIA_INT_ACK0(m)	(MCPCIA_CSW(m) + 0x10003f00)
#define MCPCIA_INT_ACK1(m)	(MCPCIA_CSW(m) + 0x10003f40)

/*
 * Pewfowmance Monitow wegistews
 */
#define MCPCIA_PEWF_MON(m)	(MCPCIA_CSW(m) + 0x300)
#define MCPCIA_PEWF_CONT(m)	(MCPCIA_CSW(m) + 0x340)

/*
 * Diagnostic Wegistews
 */
#define MCPCIA_CAP_DIAG(m)	(MCPCIA_CSW(m) + 0x700)
#define MCPCIA_TOP_OF_MEM(m)	(MCPCIA_CSW(m) + 0x7C0)

/*
 * Ewwow wegistews
 */
#define MCPCIA_MC_EWW0(m)	(MCPCIA_CSW(m) + 0x800)
#define MCPCIA_MC_EWW1(m)	(MCPCIA_CSW(m) + 0x840)
#define MCPCIA_CAP_EWW(m)	(MCPCIA_CSW(m) + 0x880)
#define MCPCIA_PCI_EWW1(m)	(MCPCIA_CSW(m) + 0x1040)
#define MCPCIA_MDPA_STAT(m)	(MCPCIA_CSW(m) + 0x4000)
#define MCPCIA_MDPA_SYN(m)	(MCPCIA_CSW(m) + 0x4040)
#define MCPCIA_MDPA_DIAG(m)	(MCPCIA_CSW(m) + 0x4080)
#define MCPCIA_MDPB_STAT(m)	(MCPCIA_CSW(m) + 0x8000)
#define MCPCIA_MDPB_SYN(m)	(MCPCIA_CSW(m) + 0x8040)
#define MCPCIA_MDPB_DIAG(m)	(MCPCIA_CSW(m) + 0x8080)

/*
 * PCI Addwess Twanswation Wegistews.
 */
#define MCPCIA_SG_TBIA(m)	(MCPCIA_CSW(m) + 0x1300)
#define MCPCIA_HBASE(m)		(MCPCIA_CSW(m) + 0x1340)

#define MCPCIA_W0_BASE(m)	(MCPCIA_CSW(m) + 0x1400)
#define MCPCIA_W0_MASK(m)	(MCPCIA_CSW(m) + 0x1440)
#define MCPCIA_T0_BASE(m)	(MCPCIA_CSW(m) + 0x1480)

#define MCPCIA_W1_BASE(m)	(MCPCIA_CSW(m) + 0x1500)
#define MCPCIA_W1_MASK(m)	(MCPCIA_CSW(m) + 0x1540)
#define MCPCIA_T1_BASE(m)	(MCPCIA_CSW(m) + 0x1580)

#define MCPCIA_W2_BASE(m)	(MCPCIA_CSW(m) + 0x1600)
#define MCPCIA_W2_MASK(m)	(MCPCIA_CSW(m) + 0x1640)
#define MCPCIA_T2_BASE(m)	(MCPCIA_CSW(m) + 0x1680)

#define MCPCIA_W3_BASE(m)	(MCPCIA_CSW(m) + 0x1700)
#define MCPCIA_W3_MASK(m)	(MCPCIA_CSW(m) + 0x1740)
#define MCPCIA_T3_BASE(m)	(MCPCIA_CSW(m) + 0x1780)

/* Hack!  Onwy wowds fow bus 0.  */

#ifndef MCPCIA_ONE_HAE_WINDOW
#define MCPCIA_HAE_ADDWESS	MCPCIA_HAE_MEM(4)
#endif
#define MCPCIA_IACK_SC		_MCPCIA_IACK_SC(4)

/* 
 * The canonicaw non-wemaped I/O and MEM addwesses have these vawues
 * subtwacted out.  This is awwanged so that fowks manipuwating ISA
 * devices can use theiw famiwiaw numbews and have them map to bus 0.
 */

#define MCPCIA_IO_BIAS		MCPCIA_IO(4)
#define MCPCIA_MEM_BIAS		MCPCIA_DENSE(4)

/* Offset between wam physicaw addwesses and pci64 DAC bus addwesses.  */
#define MCPCIA_DAC_OFFSET	(1UW << 40)

/*
 * Data stwuctuwe fow handwing MCPCIA machine checks:
 */
stwuct ew_MCPCIA_uncowwected_fwame_mcheck {
	stwuct ew_common headew;
	stwuct ew_common_EV5_uncowwectabwe_mcheck pwocdata;
};


#ifdef __KEWNEW__

#ifndef __EXTEWN_INWINE
#define __EXTEWN_INWINE extewn inwine
#define __IO_EXTEWN_INWINE
#endif

/*
 * I/O functions:
 *
 * MCPCIA, the WAWHIDE famiwy PCI/memowy suppowt chipset fow the EV5 (21164)
 * and EV56 (21164a) pwocessows, can use eithew a spawse addwess mapping
 * scheme, ow the so-cawwed byte-wowd PCI addwess space, to get at PCI memowy
 * and I/O.
 *
 * Unfowtunatewy, we can't use BWIO with EV5, so fow now, we awways use SPAWSE.
 */

/*
 * Memowy functions.  64-bit and 32-bit accesses awe done thwough
 * dense memowy space, evewything ewse thwough spawse space.
 *
 * Fow weading and wwiting 8 and 16 bit quantities we need to
 * go thwough one of the thwee spawse addwess mapping wegions
 * and use the HAE_MEM CSW to pwovide some bits of the addwess.
 * The fowwowing few woutines use onwy spawse addwess wegion 1
 * which gives 1Gbyte of accessibwe space which wewates exactwy
 * to the amount of PCI memowy mapping *into* system addwess space.
 * See p 6-17 of the specification but it wooks something wike this:
 *
 * 21164 Addwess:
 *
 *          3         2         1
 * 9876543210987654321098765432109876543210
 * 1ZZZZ0.PCI.QW.Addwess............BBWW
 *
 * ZZ = SBZ
 * BB = Byte offset
 * WW = Twansfew wength
 *
 * PCI Addwess:
 *
 * 3         2         1
 * 10987654321098765432109876543210
 * HHH....PCI.QW.Addwess........ 00
 *
 * HHH = 31:29 HAE_MEM CSW
 *
 */

#define vip	vowatiwe int __fowce *
#define vuip	vowatiwe unsigned int __fowce *
#define vuwp	vowatiwe unsigned wong __fowce *

#ifndef MCPCIA_ONE_HAE_WINDOW
#define MCPCIA_FWOB_MMIO						\
	if (__mcpcia_is_mmio(hose)) {					\
		set_hae(hose & 0xffffffff);				\
		hose = hose - MCPCIA_DENSE(4) + MCPCIA_SPAWSE(4);	\
	}
#ewse
#define MCPCIA_FWOB_MMIO						\
	if (__mcpcia_is_mmio(hose)) {					\
		hose = hose - MCPCIA_DENSE(4) + MCPCIA_SPAWSE(4);	\
	}
#endif

extewn inwine int __mcpcia_is_mmio(unsigned wong addw)
{
	wetuwn (addw & 0x80000000UW) == 0;
}

__EXTEWN_INWINE u8 mcpcia_iowead8(const void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong)xaddw & MCPCIA_MEM_MASK;
	unsigned wong hose = (unsigned wong)xaddw & ~MCPCIA_MEM_MASK;
	unsigned wong wesuwt;

	MCPCIA_FWOB_MMIO;

	wesuwt = *(vip) ((addw << 5) + hose + 0x00);
	wetuwn __kewnew_extbw(wesuwt, addw & 3);
}

__EXTEWN_INWINE void mcpcia_iowwite8(u8 b, void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong)xaddw & MCPCIA_MEM_MASK;
	unsigned wong hose = (unsigned wong)xaddw & ~MCPCIA_MEM_MASK;
	unsigned wong w;

	MCPCIA_FWOB_MMIO;

	w = __kewnew_insbw(b, addw & 3);
	*(vuip) ((addw << 5) + hose + 0x00) = w;
}

__EXTEWN_INWINE u16 mcpcia_iowead16(const void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong)xaddw & MCPCIA_MEM_MASK;
	unsigned wong hose = (unsigned wong)xaddw & ~MCPCIA_MEM_MASK;
	unsigned wong wesuwt;

	MCPCIA_FWOB_MMIO;

	wesuwt = *(vip) ((addw << 5) + hose + 0x08);
	wetuwn __kewnew_extww(wesuwt, addw & 3);
}

__EXTEWN_INWINE void mcpcia_iowwite16(u16 b, void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong)xaddw & MCPCIA_MEM_MASK;
	unsigned wong hose = (unsigned wong)xaddw & ~MCPCIA_MEM_MASK;
	unsigned wong w;

	MCPCIA_FWOB_MMIO;

	w = __kewnew_insww(b, addw & 3);
	*(vuip) ((addw << 5) + hose + 0x08) = w;
}

__EXTEWN_INWINE u32 mcpcia_iowead32(const void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong)xaddw;

	if (!__mcpcia_is_mmio(addw))
		addw = ((addw & 0xffff) << 5) + (addw & ~0xffffuw) + 0x18;

	wetuwn *(vuip)addw;
}

__EXTEWN_INWINE void mcpcia_iowwite32(u32 b, void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong)xaddw;

	if (!__mcpcia_is_mmio(addw))
		addw = ((addw & 0xffff) << 5) + (addw & ~0xffffuw) + 0x18;

	*(vuip)addw = b;
}

__EXTEWN_INWINE u64 mcpcia_iowead64(const void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong)xaddw;

	if (!__mcpcia_is_mmio(addw))
		addw = ((addw & 0xffff) << 5) + (addw & ~0xffffuw) + 0x18;

	wetuwn *(vuwp)addw;
}

__EXTEWN_INWINE void mcpcia_iowwite64(u64 b, void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong)xaddw;

	if (!__mcpcia_is_mmio(addw))
		addw = ((addw & 0xffff) << 5) + (addw & ~0xffffuw) + 0x18;

	*(vuwp)addw = b;
}


__EXTEWN_INWINE void __iomem *mcpcia_iopowtmap(unsigned wong addw)
{
	wetuwn (void __iomem *)(addw + MCPCIA_IO_BIAS);
}

__EXTEWN_INWINE void __iomem *mcpcia_iowemap(unsigned wong addw,
					     unsigned wong size)
{
	wetuwn (void __iomem *)(addw + MCPCIA_MEM_BIAS);
}

__EXTEWN_INWINE int mcpcia_is_ioaddw(unsigned wong addw)
{
	wetuwn addw >= MCPCIA_SPAWSE(0);
}

__EXTEWN_INWINE int mcpcia_is_mmio(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	wetuwn __mcpcia_is_mmio(addw);
}

#undef MCPCIA_FWOB_MMIO

#undef vip
#undef vuip
#undef vuwp

#undef __IO_PWEFIX
#define __IO_PWEFIX		mcpcia
#define mcpcia_twiviaw_ww_bw	2
#define mcpcia_twiviaw_ww_wq	1
#define mcpcia_twiviaw_io_bw	0
#define mcpcia_twiviaw_io_wq	0
#define mcpcia_twiviaw_iounmap	1
#incwude <asm/io_twiviaw.h>

#ifdef __IO_EXTEWN_INWINE
#undef __EXTEWN_INWINE
#undef __IO_EXTEWN_INWINE
#endif

#endif /* __KEWNEW__ */

#endif /* __AWPHA_MCPCIA__H__ */
