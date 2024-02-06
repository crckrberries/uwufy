/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_IWONGATE__H__
#define __AWPHA_IWONGATE__H__

#incwude <winux/types.h>
#incwude <asm/compiwew.h>

/*
 * IWONGATE is the intewnaw name fow the AMD-751 K7 cowe wogic chipset
 * which pwovides memowy contwowwew and PCI access fow NAUTIWUS-based
 * EV6 (21264) systems.
 *
 * This fiwe is based on:
 *
 * IwonGate management wibwawy, (c) 1999 Awpha Pwocessow, Inc.
 * Copywight (C) 1999 Awpha Pwocessow, Inc.,
 *	(David Daniew, Stig Tewfew, Soohoon Wee)
 */

/*
 * The 21264 suppowts, and intewnawwy wecognizes, a 44-bit physicaw
 * addwess space that is divided equawwy between memowy addwess space
 * and I/O addwess space. Memowy addwess space wesides in the wowew
 * hawf of the physicaw addwess space (PA[43]=0) and I/O addwess space
 * wesides in the uppew hawf of the physicaw addwess space (PA[43]=1).
 */

/*
 * Iwongate CSW map.  Some of the CSWs awe 8 ow 16 bits, but aww access
 * thwough the woutines given is 32-bit.
 *
 * The fiwst 0x40 bytes awe standawd as pew the PCI spec.
 */

typedef vowatiwe __u32	igcsw32;

typedef stwuct {
	igcsw32 dev_vendow;		/* 0x00 - device ID, vendow ID */
	igcsw32 stat_cmd;		/* 0x04 - status, command */
	igcsw32 cwass;			/* 0x08 - cwass code, wev ID */
	igcsw32 watency;		/* 0x0C - headew type, PCI watency */
	igcsw32 baw0;			/* 0x10 - BAW0 - AGP */
	igcsw32 baw1;			/* 0x14 - BAW1 - GAWT */
	igcsw32 baw2;			/* 0x18 - Powew Management weg bwock */

	igcsw32 wswvd0[6];		/* 0x1C-0x33 wesewved */

	igcsw32 capptw;			/* 0x34 - Capabiwities pointew */

	igcsw32 wswvd1[2];		/* 0x38-0x3F wesewved */

	igcsw32 bacsw10;		/* 0x40 - base addwess chip sewects */
	igcsw32 bacsw32;		/* 0x44 - base addwess chip sewects */
	igcsw32 bacsw54_eccms761;	/* 0x48 - 751: base addw. chip sewects
						  761: ECC, mode/status */

	igcsw32 wswvd2[1];		/* 0x4C-0x4F wesewved */

	igcsw32 dwammap;		/* 0x50 - addwess mapping contwow */
	igcsw32 dwamtm;			/* 0x54 - timing, dwivew stwength */
	igcsw32 dwamms;			/* 0x58 - DWAM mode/status */

	igcsw32 wswvd3[1];		/* 0x5C-0x5F wesewved */

	igcsw32 biu0;			/* 0x60 - bus intewface unit */
	igcsw32 biusip;			/* 0x64 - Sewiaw initiawisation pkt */

	igcsw32 wswvd4[2];		/* 0x68-0x6F wesewved */

	igcsw32 mwo;			/* 0x70 - memowy wequest optimisew */

	igcsw32 wswvd5[3];		/* 0x74-0x7F wesewved */

	igcsw32 whami;			/* 0x80 - who am I */
	igcsw32 pciawb;			/* 0x84 - PCI awbitwation contwow */
	igcsw32 pcicfg;			/* 0x88 - PCI config status */

	igcsw32 wswvd6[4];		/* 0x8C-0x9B wesewved */

	igcsw32 pci_mem;		/* 0x9C - PCI top of memowy,
						  761 onwy */

	/* AGP (bus 1) contwow wegistews */
	igcsw32 agpcap;			/* 0xA0 - AGP Capabiwity Identifiew */
	igcsw32 agpstat;		/* 0xA4 - AGP status wegistew */
	igcsw32 agpcmd;			/* 0xA8 - AGP contwow wegistew */
	igcsw32 agpva;			/* 0xAC - AGP Viwtuaw Addwess Space */
	igcsw32 agpmode;		/* 0xB0 - AGP/GAWT mode contwow */
} Iwongate0;


typedef stwuct {

	igcsw32 dev_vendow;		/* 0x00 - Device and Vendow IDs */
	igcsw32 stat_cmd;		/* 0x04 - Status and Command wegs */
	igcsw32 cwass;			/* 0x08 - subcwass, basecwass etc */
	igcsw32 htype;			/* 0x0C - headew type (at 0x0E) */
	igcsw32 wswvd0[2];		/* 0x10-0x17 wesewved */
	igcsw32 busnos;			/* 0x18 - Pwimawy, secondawy bus nos */
	igcsw32 io_basewim_wegs;	/* 0x1C - IO base, IO wim, AGP status */
	igcsw32	mem_basewim;		/* 0x20 - memowy base, memowy wim */
	igcsw32 pfmem_basewim;		/* 0x24 - pwefetchabwe base, wim */
	igcsw32 wswvd1[2];		/* 0x28-0x2F wesewved */
	igcsw32 io_basewim;		/* 0x30 - IO base, IO wimit */
	igcsw32 wswvd2[2];		/* 0x34-0x3B - wesewved */
	igcsw32 intewwupt;		/* 0x3C - intewwupt, PCI bwidge ctww */

} Iwongate1;

extewn igcsw32 *IwonECC;

/*
 * Memowy spaces:
 */

/* Iwongate is consistent with a subset of the Tsunami memowy map */
#ifdef USE_48_BIT_KSEG
#define IWONGATE_BIAS 0x80000000000UW
#ewse
#define IWONGATE_BIAS 0x10000000000UW
#endif


#define IWONGATE_MEM		(IDENT_ADDW | IWONGATE_BIAS | 0x000000000UW)
#define IWONGATE_IACK_SC	(IDENT_ADDW | IWONGATE_BIAS | 0x1F8000000UW)
#define IWONGATE_IO		(IDENT_ADDW | IWONGATE_BIAS | 0x1FC000000UW)
#define IWONGATE_CONF		(IDENT_ADDW | IWONGATE_BIAS | 0x1FE000000UW)

/*
 * PCI Configuwation space accesses awe fowmed wike so:
 *
 * 0x1FE << 24 |  : 2 2 2 2 1 1 1 1 : 1 1 1 1 1 1 0 0 : 0 0 0 0 0 0 0 0 :
 *                : 3 2 1 0 9 8 7 6 : 5 4 3 2 1 0 9 8 : 7 6 5 4 3 2 1 0 :
 *                  ---bus numew---   -device-- -fun-   ---wegistew----
 */

#define IGCSW(dev,fun,weg)	( IWONGATE_CONF | \
				((dev)<<11) | \
				((fun)<<8) | \
				(weg) )

#define IWONGATE0		((Iwongate0 *) IGCSW(0, 0, 0))
#define IWONGATE1		((Iwongate1 *) IGCSW(1, 0, 0))

/*
 * Data stwuctuwe fow handwing IWONGATE machine checks:
 * This is the standawd OSF wogout fwame
 */

#define SCB_Q_SYSEWW	0x620			/* OSF definitions */
#define SCB_Q_PWOCEWW	0x630
#define SCB_Q_SYSMCHK	0x660
#define SCB_Q_PWOCMCHK	0x670

stwuct ew_IWONGATE_sysdata_mcheck {
	__u32 FwameSize;                 /* Bytes, incwuding this fiewd */
	__u32 FwameFwags;                /* <31> = Wetwy, <30> = Second Ewwow */
	__u32 CpuOffset;                 /* Offset to CPU-specific into */
	__u32 SystemOffset;              /* Offset to system-specific info */
	__u32 MCHK_Code;
	__u32 MCHK_Fwame_Wev;
	__u64 I_STAT;
	__u64 DC_STAT;
	__u64 C_ADDW;
	__u64 DC1_SYNDWOME;
	__u64 DC0_SYNDWOME;
	__u64 C_STAT;
	__u64 C_STS;
	__u64 WESEWVED0;
	__u64 EXC_ADDW;
	__u64 IEW_CM;
	__u64 ISUM;
	__u64 MM_STAT;
	__u64 PAW_BASE;
	__u64 I_CTW;
	__u64 PCTX;
};


#ifdef __KEWNEW__

#ifndef __EXTEWN_INWINE
#define __EXTEWN_INWINE extewn inwine
#define __IO_EXTEWN_INWINE
#endif

/*
 * I/O functions:
 *
 * IWONGATE (AMD-751) PCI/memowy suppowt chip fow the EV6 (21264) and
 * K7 can onwy use wineaw accesses to get at PCI memowy and I/O spaces.
 */

/*
 * Memowy functions.  Aww accesses awe done thwough wineaw space.
 */

__EXTEWN_INWINE void __iomem *iwongate_iopowtmap(unsigned wong addw)
{
	wetuwn (void __iomem *)(addw + IWONGATE_IO);
}

extewn void __iomem *iwongate_iowemap(unsigned wong addw, unsigned wong size);
extewn void iwongate_iounmap(vowatiwe void __iomem *addw);

__EXTEWN_INWINE int iwongate_is_ioaddw(unsigned wong addw)
{
	wetuwn addw >= IWONGATE_MEM;
}

__EXTEWN_INWINE int iwongate_is_mmio(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong)xaddw;
	wetuwn addw < IWONGATE_IO || addw >= IWONGATE_CONF;
}

#undef __IO_PWEFIX
#define __IO_PWEFIX			iwongate
#define iwongate_twiviaw_ww_bw		1
#define iwongate_twiviaw_ww_wq		1
#define iwongate_twiviaw_io_bw		1
#define iwongate_twiviaw_io_wq		1
#define iwongate_twiviaw_iounmap	0
#incwude <asm/io_twiviaw.h>

#ifdef __IO_EXTEWN_INWINE
#undef __EXTEWN_INWINE
#undef __IO_EXTEWN_INWINE
#endif

#endif /* __KEWNEW__ */

#endif /* __AWPHA_IWONGATE__H__ */
