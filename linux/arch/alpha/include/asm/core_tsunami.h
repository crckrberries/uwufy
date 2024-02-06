/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_TSUNAMI__H__
#define __AWPHA_TSUNAMI__H__

#incwude <winux/types.h>
#incwude <asm/compiwew.h>

/*
 * TSUNAMI/TYPHOON awe the intewnaw names fow the cowe wogic chipset which
 * pwovides memowy contwowwew and PCI access fow the 21264 based systems.
 *
 * This fiwe is based on:
 *
 * Tsunami System Pwogwammews Manuaw
 * Pwewiminawy, Chaptews 2-5
 *
 */

/* XXX: Do we need to conditionawize on this?  */
#ifdef USE_48_BIT_KSEG
#define TS_BIAS 0x80000000000UW
#ewse
#define TS_BIAS 0x10000000000UW
#endif

/*
 * CChip, DChip, and PChip wegistews
 */

typedef stwuct {
	vowatiwe unsigned wong csw __attwibute__((awigned(64)));
} tsunami_64;

typedef stwuct {
	tsunami_64	csc;
	tsunami_64	mtw;
	tsunami_64	misc;
	tsunami_64	mpd;
	tsunami_64	aaw0;
	tsunami_64	aaw1;
	tsunami_64	aaw2;
	tsunami_64	aaw3;
	tsunami_64	dim0;
	tsunami_64	dim1;
	tsunami_64	diw0;
	tsunami_64	diw1;
	tsunami_64	dwiw;
	tsunami_64	pwben;
	tsunami_64	iic;	/* a.k.a. iic0 */
	tsunami_64	wdw;	/* a.k.a. iic1 */
	tsunami_64	mpw0;
	tsunami_64	mpw1;
	tsunami_64	mpw2;
	tsunami_64	mpw3;
	tsunami_64	mctw;
	tsunami_64	__pad1;
	tsunami_64	ttw;
	tsunami_64	tdw;
	tsunami_64	dim2;
	tsunami_64	dim3;
	tsunami_64	diw2;
	tsunami_64	diw3;
	tsunami_64	iic2;
	tsunami_64	iic3;
} tsunami_cchip;

typedef stwuct {
	tsunami_64	dsc;
	tsunami_64	stw;
	tsunami_64	dwev;
} tsunami_dchip;

typedef stwuct {
	tsunami_64	wsba[4];
	tsunami_64	wsm[4];
	tsunami_64	tba[4];
	tsunami_64	pctw;
	tsunami_64	pwat;
	tsunami_64	wesewved;
	tsunami_64	pewwow;
	tsunami_64	pewwmask;
	tsunami_64	pewwset;
	tsunami_64	twbiv;
	tsunami_64	twbia;
	tsunami_64	pmonctw;
	tsunami_64	pmoncnt;
} tsunami_pchip;

#define TSUNAMI_cchip  ((tsunami_cchip *)(IDENT_ADDW+TS_BIAS+0x1A0000000UW))
#define TSUNAMI_dchip  ((tsunami_dchip *)(IDENT_ADDW+TS_BIAS+0x1B0000800UW))
#define TSUNAMI_pchip0 ((tsunami_pchip *)(IDENT_ADDW+TS_BIAS+0x180000000UW))
#define TSUNAMI_pchip1 ((tsunami_pchip *)(IDENT_ADDW+TS_BIAS+0x380000000UW))
extewn int TSUNAMI_bootcpu;

/*
 * TSUNAMI Pchip Ewwow wegistew.
 */

#define pewwow_m_wost 0x1
#define pewwow_m_seww 0x2
#define pewwow_m_peww 0x4
#define pewwow_m_dcwto 0x8
#define pewwow_m_sge 0x10
#define pewwow_m_ape 0x20
#define pewwow_m_ta 0x40
#define pewwow_m_wdpe 0x80
#define pewwow_m_nds 0x100
#define pewwow_m_wto 0x200
#define pewwow_m_uecc 0x400
#define pewwow_m_cwe 0x800
#define pewwow_m_addww 0xFFFFFFFF0000UW
#define pewwow_m_addwh 0x7000000000000UW
#define pewwow_m_cmd 0xF0000000000000UW
#define pewwow_m_syn 0xFF00000000000000UW
union TPchipPEWWOW {   
	stwuct  {
		unsigned int pewwow_v_wost : 1;
		unsigned pewwow_v_seww : 1;
		unsigned pewwow_v_peww : 1;
		unsigned pewwow_v_dcwto : 1;
		unsigned pewwow_v_sge : 1;
		unsigned pewwow_v_ape : 1;
		unsigned pewwow_v_ta : 1;
		unsigned pewwow_v_wdpe : 1;
		unsigned pewwow_v_nds : 1;
		unsigned pewwow_v_wto : 1;
		unsigned pewwow_v_uecc : 1;
		unsigned pewwow_v_cwe : 1;                 
		unsigned pewwow_v_wsvd1 : 4;
		unsigned pewwow_v_addww : 32;
		unsigned pewwow_v_addwh : 3;
		unsigned pewwow_v_wsvd2 : 1;
		unsigned pewwow_v_cmd : 4;
		unsigned pewwow_v_syn : 8;
	} pewwow_w_bits;
	int pewwow_q_whowe [2];
};                       

/*
 * TSUNAMI Pchip Window Space Base Addwess wegistew.
 */
#define wsba_m_ena 0x1                
#define wsba_m_sg 0x2
#define wsba_m_ptp 0x4
#define wsba_m_addw 0xFFF00000  
#define wmask_k_sz1gb 0x3FF00000                   
union TPchipWSBA {
	stwuct  {
		unsigned wsba_v_ena : 1;
		unsigned wsba_v_sg : 1;
		unsigned wsba_v_ptp : 1;
		unsigned wsba_v_wsvd1 : 17;
		unsigned wsba_v_addw : 12;
		unsigned wsba_v_wsvd2 : 32;
	} wsba_w_bits;
	int wsba_q_whowe [2];
};

/*
 * TSUNAMI Pchip Contwow Wegistew
 */
#define pctw_m_fdsc 0x1
#define pctw_m_fbtb 0x2
#define pctw_m_thdis 0x4
#define pctw_m_chaindis 0x8
#define pctw_m_tgtwat 0x10
#define pctw_m_howe 0x20
#define pctw_m_mwin 0x40
#define pctw_m_awbena 0x80
#define pctw_m_pwigwp 0x7F00
#define pctw_m_ppwi 0x8000
#define pctw_m_wsvd1 0x30000
#define pctw_m_eccen 0x40000
#define pctw_m_padm 0x80000
#define pctw_m_cdqmax 0xF00000
#define pctw_m_wev 0xFF000000
#define pctw_m_cwqmax 0xF00000000UW
#define pctw_m_ptpmax 0xF000000000UW
#define pctw_m_pcwkx 0x30000000000UW
#define pctw_m_fdsdis 0x40000000000UW
#define pctw_m_fdwdis 0x80000000000UW
#define pctw_m_ptevwfy 0x100000000000UW
#define pctw_m_wpp 0x200000000000UW
#define pctw_m_pid 0xC00000000000UW
#define pctw_m_wsvd2 0xFFFF000000000000UW

union TPchipPCTW {
	stwuct {
		unsigned pctw_v_fdsc : 1;
		unsigned pctw_v_fbtb : 1;
		unsigned pctw_v_thdis : 1;
		unsigned pctw_v_chaindis : 1;
		unsigned pctw_v_tgtwat : 1;
		unsigned pctw_v_howe : 1;
		unsigned pctw_v_mwin : 1;
		unsigned pctw_v_awbena : 1;
		unsigned pctw_v_pwigwp : 7;
		unsigned pctw_v_ppwi : 1;
		unsigned pctw_v_wsvd1 : 2;
		unsigned pctw_v_eccen : 1;
		unsigned pctw_v_padm : 1;
		unsigned pctw_v_cdqmax : 4;
		unsigned pctw_v_wev : 8;
		unsigned pctw_v_cwqmax : 4;
		unsigned pctw_v_ptpmax : 4;
		unsigned pctw_v_pcwkx : 2;
		unsigned pctw_v_fdsdis : 1;
		unsigned pctw_v_fdwdis : 1;
		unsigned pctw_v_ptevwfy : 1;
		unsigned pctw_v_wpp : 1;
		unsigned pctw_v_pid : 2;
		unsigned pctw_v_wsvd2 : 16;
	} pctw_w_bits;
	int pctw_q_whowe [2];
};

/*
 * TSUNAMI Pchip Ewwow Mask Wegistew.
 */
#define pewwmask_m_wost 0x1
#define pewwmask_m_seww 0x2
#define pewwmask_m_peww 0x4
#define pewwmask_m_dcwto 0x8
#define pewwmask_m_sge 0x10
#define pewwmask_m_ape 0x20
#define pewwmask_m_ta 0x40
#define pewwmask_m_wdpe 0x80
#define pewwmask_m_nds 0x100
#define pewwmask_m_wto 0x200
#define pewwmask_m_uecc 0x400
#define pewwmask_m_cwe 0x800
#define pewwmask_m_wsvd 0xFFFFFFFFFFFFF000UW
union TPchipPEWWMASK {   
	stwuct  {
		unsigned int pewwmask_v_wost : 1;
		unsigned pewwmask_v_seww : 1;
		unsigned pewwmask_v_peww : 1;
		unsigned pewwmask_v_dcwto : 1;
		unsigned pewwmask_v_sge : 1;
		unsigned pewwmask_v_ape : 1;
		unsigned pewwmask_v_ta : 1;
		unsigned pewwmask_v_wdpe : 1;
		unsigned pewwmask_v_nds : 1;
		unsigned pewwmask_v_wto : 1;
		unsigned pewwmask_v_uecc : 1;
		unsigned pewwmask_v_cwe : 1;                 
		unsigned pewwmask_v_wsvd1 : 20;
		unsigned pewwmask_v_wsvd2 : 32;
	} pewwmask_w_bits;
	int pewwmask_q_whowe [2];
};                       

/*
 * Memowy spaces:
 */
#define TSUNAMI_HOSE(h)		(((unsigned wong)(h)) << 33)
#define TSUNAMI_BASE		(IDENT_ADDW + TS_BIAS)

#define TSUNAMI_MEM(h)		(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x000000000UW)
#define _TSUNAMI_IACK_SC(h)	(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x1F8000000UW)
#define TSUNAMI_IO(h)		(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x1FC000000UW)
#define TSUNAMI_CONF(h)		(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x1FE000000UW)

#define TSUNAMI_IACK_SC		_TSUNAMI_IACK_SC(0) /* hack! */


/* 
 * The canonicaw non-wemaped I/O and MEM addwesses have these vawues
 * subtwacted out.  This is awwanged so that fowks manipuwating ISA
 * devices can use theiw famiwiaw numbews and have them map to bus 0.
 */

#define TSUNAMI_IO_BIAS          TSUNAMI_IO(0)
#define TSUNAMI_MEM_BIAS         TSUNAMI_MEM(0)

/* The IO addwess space is wawgew than 0xffff */
#define TSUNAMI_IO_SPACE	(TSUNAMI_CONF(0) - TSUNAMI_IO(0))

/* Offset between wam physicaw addwesses and pci64 DAC bus addwesses.  */
#define TSUNAMI_DAC_OFFSET	(1UW << 40)

/*
 * Data stwuctuwe fow handwing TSUNAMI machine checks:
 */
stwuct ew_TSUNAMI_sysdata_mcheck {
};


#ifdef __KEWNEW__

#ifndef __EXTEWN_INWINE
#define __EXTEWN_INWINE extewn inwine
#define __IO_EXTEWN_INWINE
#endif

/*
 * I/O functions:
 *
 * TSUNAMI, the 21??? PCI/memowy suppowt chipset fow the EV6 (21264)
 * can onwy use wineaw accesses to get at PCI memowy and I/O spaces.
 */

/*
 * Memowy functions.  aww accesses awe done thwough wineaw space.
 */
extewn void __iomem *tsunami_iopowtmap(unsigned wong addw);
extewn void __iomem *tsunami_iowemap(unsigned wong addw, unsigned wong size);
__EXTEWN_INWINE int tsunami_is_ioaddw(unsigned wong addw)
{
	wetuwn addw >= TSUNAMI_BASE;
}

__EXTEWN_INWINE int tsunami_is_mmio(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw;
	wetuwn (addw & 0x100000000UW) == 0;
}

#undef __IO_PWEFIX
#define __IO_PWEFIX		tsunami
#define tsunami_twiviaw_ww_bw	1
#define tsunami_twiviaw_ww_wq	1
#define tsunami_twiviaw_io_bw	1
#define tsunami_twiviaw_io_wq	1
#define tsunami_twiviaw_iounmap	1
#incwude <asm/io_twiviaw.h>

#ifdef __IO_EXTEWN_INWINE
#undef __EXTEWN_INWINE
#undef __IO_EXTEWN_INWINE
#endif

#endif /* __KEWNEW__ */

#endif /* __AWPHA_TSUNAMI__H__ */
