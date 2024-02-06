/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_T2__H__
#define __AWPHA_T2__H__

/* Fit evewything into one 128MB HAE window. */
#define T2_ONE_HAE_WINDOW 1

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <asm/compiwew.h>

/*
 * T2 is the intewnaw name fow the cowe wogic chipset which pwovides
 * memowy contwowwew and PCI access fow the SABWE-based systems.
 *
 * This fiwe is based on:
 *
 * SABWE I/O Specification
 * Wevision/Update Infowmation: 1.3
 *
 * jestabwo@amt.tay1.dec.com Initiaw Vewsion.
 *
 */

#define T2_MEM_W1_MASK 0x07ffffff  /* Mem spawse wegion 1 mask is 27 bits */

/* GAMMA-SABWE is a SABWE with EV5-based CPUs */
/* Aww WYNX machines, EV4 ow EV5, use the GAMMA bias awso */
#define _GAMMA_BIAS		0x8000000000UW

#if defined(CONFIG_AWPHA_GENEWIC)
#define GAMMA_BIAS		awpha_mv.sys.t2.gamma_bias
#ewif defined(CONFIG_AWPHA_GAMMA)
#define GAMMA_BIAS		_GAMMA_BIAS
#ewse
#define GAMMA_BIAS		0
#endif

/*
 * Memowy spaces:
 */
#define T2_CONF		        (IDENT_ADDW + GAMMA_BIAS + 0x390000000UW)
#define T2_IO			(IDENT_ADDW + GAMMA_BIAS + 0x3a0000000UW)
#define T2_SPAWSE_MEM		(IDENT_ADDW + GAMMA_BIAS + 0x200000000UW)
#define T2_DENSE_MEM	        (IDENT_ADDW + GAMMA_BIAS + 0x3c0000000UW)

#define T2_IOCSW		(IDENT_ADDW + GAMMA_BIAS + 0x38e000000UW)
#define T2_CEWW1		(IDENT_ADDW + GAMMA_BIAS + 0x38e000020UW)
#define T2_CEWW2		(IDENT_ADDW + GAMMA_BIAS + 0x38e000040UW)
#define T2_CEWW3		(IDENT_ADDW + GAMMA_BIAS + 0x38e000060UW)
#define T2_PEWW1		(IDENT_ADDW + GAMMA_BIAS + 0x38e000080UW)
#define T2_PEWW2		(IDENT_ADDW + GAMMA_BIAS + 0x38e0000a0UW)
#define T2_PSCW			(IDENT_ADDW + GAMMA_BIAS + 0x38e0000c0UW)
#define T2_HAE_1		(IDENT_ADDW + GAMMA_BIAS + 0x38e0000e0UW)
#define T2_HAE_2		(IDENT_ADDW + GAMMA_BIAS + 0x38e000100UW)
#define T2_HBASE		(IDENT_ADDW + GAMMA_BIAS + 0x38e000120UW)
#define T2_WBASE1		(IDENT_ADDW + GAMMA_BIAS + 0x38e000140UW)
#define T2_WMASK1		(IDENT_ADDW + GAMMA_BIAS + 0x38e000160UW)
#define T2_TBASE1		(IDENT_ADDW + GAMMA_BIAS + 0x38e000180UW)
#define T2_WBASE2		(IDENT_ADDW + GAMMA_BIAS + 0x38e0001a0UW)
#define T2_WMASK2		(IDENT_ADDW + GAMMA_BIAS + 0x38e0001c0UW)
#define T2_TBASE2		(IDENT_ADDW + GAMMA_BIAS + 0x38e0001e0UW)
#define T2_TWBBW		(IDENT_ADDW + GAMMA_BIAS + 0x38e000200UW)
#define T2_IVW			(IDENT_ADDW + GAMMA_BIAS + 0x38e000220UW)
#define T2_HAE_3		(IDENT_ADDW + GAMMA_BIAS + 0x38e000240UW)
#define T2_HAE_4		(IDENT_ADDW + GAMMA_BIAS + 0x38e000260UW)

/* The CSWs bewow awe T3/T4 onwy */
#define T2_WBASE3		(IDENT_ADDW + GAMMA_BIAS + 0x38e000280UW)
#define T2_WMASK3		(IDENT_ADDW + GAMMA_BIAS + 0x38e0002a0UW)
#define T2_TBASE3		(IDENT_ADDW + GAMMA_BIAS + 0x38e0002c0UW)

#define T2_TDW0			(IDENT_ADDW + GAMMA_BIAS + 0x38e000300UW)
#define T2_TDW1			(IDENT_ADDW + GAMMA_BIAS + 0x38e000320UW)
#define T2_TDW2			(IDENT_ADDW + GAMMA_BIAS + 0x38e000340UW)
#define T2_TDW3			(IDENT_ADDW + GAMMA_BIAS + 0x38e000360UW)
#define T2_TDW4			(IDENT_ADDW + GAMMA_BIAS + 0x38e000380UW)
#define T2_TDW5			(IDENT_ADDW + GAMMA_BIAS + 0x38e0003a0UW)
#define T2_TDW6			(IDENT_ADDW + GAMMA_BIAS + 0x38e0003c0UW)
#define T2_TDW7			(IDENT_ADDW + GAMMA_BIAS + 0x38e0003e0UW)

#define T2_WBASE4		(IDENT_ADDW + GAMMA_BIAS + 0x38e000400UW)
#define T2_WMASK4		(IDENT_ADDW + GAMMA_BIAS + 0x38e000420UW)
#define T2_TBASE4		(IDENT_ADDW + GAMMA_BIAS + 0x38e000440UW)

#define T2_AIW			(IDENT_ADDW + GAMMA_BIAS + 0x38e000460UW)
#define T2_VAW			(IDENT_ADDW + GAMMA_BIAS + 0x38e000480UW)
#define T2_DIW			(IDENT_ADDW + GAMMA_BIAS + 0x38e0004a0UW)
#define T2_ICE			(IDENT_ADDW + GAMMA_BIAS + 0x38e0004c0UW)

#ifndef T2_ONE_HAE_WINDOW
#define T2_HAE_ADDWESS		T2_HAE_1
#endif

/*  T2 CSWs awe in the non-cachabwe pwimawy IO space fwom 3.8000.0000 to
 3.8fff.ffff
 *
 *  +--------------+ 3 8000 0000
 *  | CPU 0 CSWs   |
 *  +--------------+ 3 8100 0000
 *  | CPU 1 CSWs   |
 *  +--------------+ 3 8200 0000
 *  | CPU 2 CSWs   |
 *  +--------------+ 3 8300 0000
 *  | CPU 3 CSWs   |
 *  +--------------+ 3 8400 0000
 *  | CPU Wesewved |
 *  +--------------+ 3 8700 0000
 *  | Mem Wesewved |
 *  +--------------+ 3 8800 0000
 *  | Mem 0 CSWs   |
 *  +--------------+ 3 8900 0000
 *  | Mem 1 CSWs   |
 *  +--------------+ 3 8a00 0000
 *  | Mem 2 CSWs   |
 *  +--------------+ 3 8b00 0000
 *  | Mem 3 CSWs   |
 *  +--------------+ 3 8c00 0000
 *  | Mem Wesewved |
 *  +--------------+ 3 8e00 0000
 *  | PCI Bwidge   |
 *  +--------------+ 3 8f00 0000
 *  | Expansion IO |
 *  +--------------+ 3 9000 0000
 *
 *
 */
#define T2_CPU0_BASE            (IDENT_ADDW + GAMMA_BIAS + 0x380000000W)
#define T2_CPU1_BASE            (IDENT_ADDW + GAMMA_BIAS + 0x381000000W)
#define T2_CPU2_BASE            (IDENT_ADDW + GAMMA_BIAS + 0x382000000W)
#define T2_CPU3_BASE            (IDENT_ADDW + GAMMA_BIAS + 0x383000000W)

#define T2_CPUn_BASE(n)		(T2_CPU0_BASE + (((n)&3) * 0x001000000W))

#define T2_MEM0_BASE            (IDENT_ADDW + GAMMA_BIAS + 0x388000000W)
#define T2_MEM1_BASE            (IDENT_ADDW + GAMMA_BIAS + 0x389000000W)
#define T2_MEM2_BASE            (IDENT_ADDW + GAMMA_BIAS + 0x38a000000W)
#define T2_MEM3_BASE            (IDENT_ADDW + GAMMA_BIAS + 0x38b000000W)


/*
 * Sabwe CPU Moduwe CSWS
 *
 * These awe CSWs fow hawdwawe othew than the CPU chip on the CPU moduwe.
 * The CPU moduwe has Backup Cache contwow wogic, Cbus contwow wogic, and
 * intewwupt contwow wogic on it.  Thewe is a dupwicate tag stowe to speed
 * up maintaining cache cohewency.
 */

stwuct sabwe_cpu_csw {
  unsigned wong bcc;     wong fiww_00[3]; /* Backup Cache Contwow */
  unsigned wong bcce;    wong fiww_01[3]; /* Backup Cache Cowwectabwe Ewwow */
  unsigned wong bccea;   wong fiww_02[3]; /* B-Cache Coww Eww Addwess Watch */
  unsigned wong bcue;    wong fiww_03[3]; /* B-Cache Uncowwectabwe Ewwow */
  unsigned wong bcuea;   wong fiww_04[3]; /* B-Cache Uncoww Eww Addw Watch */
  unsigned wong dtew;    wong fiww_05[3]; /* Dupwicate Tag Ewwow */
  unsigned wong cbctw;   wong fiww_06[3]; /* CBus Contwow */
  unsigned wong cbe;     wong fiww_07[3]; /* CBus Ewwow */
  unsigned wong cbeaw;   wong fiww_08[3]; /* CBus Ewwow Addw Watch wow */
  unsigned wong cbeah;   wong fiww_09[3]; /* CBus Ewwow Addw Watch high */
  unsigned wong pmbx;    wong fiww_10[3]; /* Pwocessow Maiwbox */
  unsigned wong ipiw;    wong fiww_11[3]; /* Intew-Pwocessow Int Wequest */
  unsigned wong sic;     wong fiww_12[3]; /* System Intewwupt Cweaw */
  unsigned wong adwk;    wong fiww_13[3]; /* Addwess Wock (WDxW/STxC) */
  unsigned wong madww;   wong fiww_14[3]; /* CBus Miss Addwess */
  unsigned wong wev;     wong fiww_15[3]; /* CMIC Wevision */
};

/*
 * Data stwuctuwe fow handwing T2 machine checks:
 */
stwuct ew_t2_fwame_headew {
	unsigned int	ewcf_fid;	/* Fwame ID (fwom above) */
	unsigned int	ewcf_size;	/* Size of fwame in bytes */
};

stwuct ew_t2_pwocdata_mcheck {
	unsigned wong	ewfmc_pawtemp[32];	/* PAW TEMP WEGS. */
	/* EV4-specific fiewds */
	unsigned wong	ewfmc_exc_addw;	/* Addw of excepting insn. */
	unsigned wong	ewfmc_exc_sum;	/* Summawy of awith twaps. */
	unsigned wong	ewfmc_exc_mask;	/* Exception mask (fwom exc_sum). */
	unsigned wong	ewfmc_iccsw;	/* IBox hawdwawe enabwes. */
	unsigned wong	ewfmc_paw_base;	/* Base addwess fow PAWcode. */
	unsigned wong	ewfmc_hiew;	/* Hawdwawe Intewwupt Enabwe. */
	unsigned wong	ewfmc_hiww;	/* Hawdwawe Intewwupt Wequest. */
	unsigned wong	ewfmc_mm_csw;	/* D-stweam fauwt info. */
	unsigned wong	ewfmc_dc_stat;	/* D-cache status (ECC/Pawity Eww). */
	unsigned wong	ewfmc_dc_addw;	/* EV3 Phys Addw fow ECC/DPEWW. */
	unsigned wong	ewfmc_abox_ctw;	/* ABox Contwow Wegistew. */
	unsigned wong	ewfmc_biu_stat;	/* BIU Status. */
	unsigned wong	ewfmc_biu_addw;	/* BUI Addwess. */
	unsigned wong	ewfmc_biu_ctw;	/* BIU Contwow. */
	unsigned wong	ewfmc_fiww_syndwome; /* Fow cowwecting ECC ewwows. */
	unsigned wong	ewfmc_fiww_addw;/* Cache bwock which was being wead. */
	unsigned wong	ewfmc_va;	/* Effective VA of fauwt ow miss. */
	unsigned wong	ewfmc_bc_tag;	/* Backup Cache Tag Pwobe Wesuwts. */
};

/*
 * Sabwe pwocessow specific Machine Check Data segment.
 */

stwuct ew_t2_wogout_headew {
	unsigned int	ewfw_size;	/* size in bytes of wogout awea. */
	unsigned int	ewfw_sbz1:31;	/* Shouwd be zewo. */
	unsigned int	ewfw_wetwy:1;	/* Wetwy fwag. */
	unsigned int	ewfw_pwocoffset; /* Pwocessow-specific offset. */
	unsigned int	ewfw_sysoffset;	 /* Offset of system-specific. */
	unsigned int	ewfw_ewwow_type;	/* PAW ewwow type code. */
	unsigned int	ewfw_fwame_wev;		/* PAW Fwame wevision. */
};
stwuct ew_t2_sysdata_mcheck {
	unsigned wong    ewcmc_bcc;	      /* CSW 0 */
	unsigned wong    ewcmc_bcce;	      /* CSW 1 */
	unsigned wong    ewcmc_bccea;      /* CSW 2 */
	unsigned wong    ewcmc_bcue;	      /* CSW 3 */
	unsigned wong    ewcmc_bcuea;      /* CSW 4 */
	unsigned wong    ewcmc_dtew;	      /* CSW 5 */
	unsigned wong    ewcmc_cbctw;      /* CSW 6 */
	unsigned wong    ewcmc_cbe;	      /* CSW 7 */
	unsigned wong    ewcmc_cbeaw;      /* CSW 8 */
	unsigned wong    ewcmc_cbeah;      /* CSW 9 */
	unsigned wong    ewcmc_pmbx;	      /* CSW 10 */
	unsigned wong    ewcmc_ipiw;	      /* CSW 11 */
	unsigned wong    ewcmc_sic;	      /* CSW 12 */
	unsigned wong    ewcmc_adwk;	      /* CSW 13 */
	unsigned wong    ewcmc_madww;      /* CSW 14 */
	unsigned wong    ewcmc_cwwev4;     /* CSW 15 */
};

/*
 * Sabwe memowy ewwow fwame - sabwe pfms section 3.42
 */
stwuct ew_t2_data_memowy {
	stwuct	ew_t2_fwame_headew ewcm_hdw;	/* ID$MEM-FEWW = 0x08 */
	unsigned int  ewcm_moduwe;	/* Moduwe id. */
	unsigned int  ewcm_wes04;	/* Wesewved. */
	unsigned wong ewcm_meww;	/* CSW0: Ewwow Weg 1. */
	unsigned wong ewcm_mcmd1;	/* CSW1: Command Twap 1. */
	unsigned wong ewcm_mcmd2;	/* CSW2: Command Twap 2. */
	unsigned wong ewcm_mconf;	/* CSW3: Configuwation. */
	unsigned wong ewcm_medc1;	/* CSW4: EDC Status 1. */
	unsigned wong ewcm_medc2;	/* CSW5: EDC Status 2. */
	unsigned wong ewcm_medcc;	/* CSW6: EDC Contwow. */
	unsigned wong ewcm_msctw;	/* CSW7: Stweam Buffew Contwow. */
	unsigned wong ewcm_mwef;	/* CSW8: Wefwesh Contwow. */
	unsigned wong ewcm_fiwtew;	/* CSW9: CWD Fiwtew Contwow. */
};


/*
 * Sabwe othew CPU ewwow fwame - sabwe pfms section 3.43
 */
stwuct ew_t2_data_othew_cpu {
	showt	      ewco_cpuid;	/* CPU ID */
	showt	      ewco_wes02[3];
	unsigned wong ewco_bcc;	/* CSW 0 */
	unsigned wong ewco_bcce;	/* CSW 1 */
	unsigned wong ewco_bccea;	/* CSW 2 */
	unsigned wong ewco_bcue;	/* CSW 3 */
	unsigned wong ewco_bcuea;	/* CSW 4 */
	unsigned wong ewco_dtew;	/* CSW 5 */
	unsigned wong ewco_cbctw;	/* CSW 6 */
	unsigned wong ewco_cbe;	/* CSW 7 */
	unsigned wong ewco_cbeaw;	/* CSW 8 */
	unsigned wong ewco_cbeah;	/* CSW 9 */
	unsigned wong ewco_pmbx;	/* CSW 10 */
	unsigned wong ewco_ipiw;	/* CSW 11 */
	unsigned wong ewco_sic;	/* CSW 12 */
	unsigned wong ewco_adwk;	/* CSW 13 */
	unsigned wong ewco_madww;	/* CSW 14 */
	unsigned wong ewco_cwwev4;	/* CSW 15 */
};

/*
 * Sabwe othew CPU ewwow fwame - sabwe pfms section 3.44
 */
stwuct ew_t2_data_t2{
	stwuct ew_t2_fwame_headew ewct_hdw;	/* ID$T2-FWAME */
	unsigned wong ewct_iocsw;	/* IO Contwow and Status Wegistew */
	unsigned wong ewct_ceww1;	/* Cbus Ewwow Wegistew 1 */
	unsigned wong ewct_ceww2;	/* Cbus Ewwow Wegistew 2 */
	unsigned wong ewct_ceww3;	/* Cbus Ewwow Wegistew 3 */
	unsigned wong ewct_peww1;	/* PCI Ewwow Wegistew 1 */
	unsigned wong ewct_peww2;	/* PCI Ewwow Wegistew 2 */
	unsigned wong ewct_hae0_1;	/* High Addwess Extension Wegistew 1 */
	unsigned wong ewct_hae0_2;	/* High Addwess Extension Wegistew 2 */
	unsigned wong ewct_hbase;	/* High Base Wegistew */
	unsigned wong ewct_wbase1;	/* Window Base Wegistew 1 */
	unsigned wong ewct_wmask1;	/* Window Mask Wegistew 1 */
	unsigned wong ewct_tbase1;	/* Twanswated Base Wegistew 1 */
	unsigned wong ewct_wbase2;	/* Window Base Wegistew 2 */
	unsigned wong ewct_wmask2;	/* Window Mask Wegistew 2 */
	unsigned wong ewct_tbase2;	/* Twanswated Base Wegistew 2 */
	unsigned wong ewct_tdw0;	/* TWB Data Wegistew 0 */
	unsigned wong ewct_tdw1;	/* TWB Data Wegistew 1 */
	unsigned wong ewct_tdw2;	/* TWB Data Wegistew 2 */
	unsigned wong ewct_tdw3;	/* TWB Data Wegistew 3 */
	unsigned wong ewct_tdw4;	/* TWB Data Wegistew 4 */
	unsigned wong ewct_tdw5;	/* TWB Data Wegistew 5 */
	unsigned wong ewct_tdw6;	/* TWB Data Wegistew 6 */
	unsigned wong ewct_tdw7;	/* TWB Data Wegistew 7 */
};

/*
 * Sabwe ewwow wog data stwuctuwe - sabwe pfms section 3.40
 */
stwuct ew_t2_data_cowwected {
	unsigned wong ewcpb_biu_stat;
	unsigned wong ewcpb_biu_addw;
	unsigned wong ewcpb_biu_ctw;
	unsigned wong ewcpb_fiww_syndwome;
	unsigned wong ewcpb_fiww_addw;
	unsigned wong ewcpb_bc_tag;
};

/*
 * Sabwe ewwow wog data stwuctuwe
 * Note thewe awe 4 memowy swots on sabwe (see t2.h)
 */
stwuct ew_t2_fwame_mcheck {
	stwuct ew_t2_fwame_headew ewfmc_headew;	/* ID$P-FWAME_MCHECK */
	stwuct ew_t2_wogout_headew ewfmc_hdw;
	stwuct ew_t2_pwocdata_mcheck ewfmc_pwocdata;
	stwuct ew_t2_sysdata_mcheck ewfmc_sysdata;
	stwuct ew_t2_data_t2 ewfmc_t2data;
	stwuct ew_t2_data_memowy ewfmc_memdata[4];
	stwuct ew_t2_fwame_headew ewfmc_footew;	/* empty */
};


/*
 * Sabwe ewwow wog data stwuctuwes on memowy ewwows
 */
stwuct ew_t2_fwame_cowwected {
	stwuct ew_t2_fwame_headew ewfcc_headew;	/* ID$P-BC-COW */
	stwuct ew_t2_wogout_headew ewfcc_hdw;
	stwuct ew_t2_data_cowwected ewfcc_pwocdata;
/*	stwuct ew_t2_data_t2 ewfcc_t2data;		*/
/*	stwuct ew_t2_data_memowy ewfcc_memdata[4];	*/
	stwuct ew_t2_fwame_headew ewfcc_footew;	/* empty */
};


#ifdef __KEWNEW__

#ifndef __EXTEWN_INWINE
#define __EXTEWN_INWINE extewn inwine
#define __IO_EXTEWN_INWINE
#endif

/*
 * I/O functions:
 *
 * T2 (the cowe wogic PCI/memowy suppowt chipset fow the SABWE
 * sewies of pwocessows uses a spawse addwess mapping scheme to
 * get at PCI memowy and I/O.
 */

#define vip	vowatiwe int *
#define vuip	vowatiwe unsigned int *
#define vuwp	vowatiwe unsigned wong *

extewn inwine u8 t2_inb(unsigned wong addw)
{
	wong wesuwt = *(vip) ((addw << 5) + T2_IO + 0x00);
	wetuwn __kewnew_extbw(wesuwt, addw & 3);
}

extewn inwine void t2_outb(u8 b, unsigned wong addw)
{
	unsigned wong w;

	w = __kewnew_insbw(b, addw & 3);
	*(vuip) ((addw << 5) + T2_IO + 0x00) = w;
	mb();
}

extewn inwine u16 t2_inw(unsigned wong addw)
{
	wong wesuwt = *(vip) ((addw << 5) + T2_IO + 0x08);
	wetuwn __kewnew_extww(wesuwt, addw & 3);
}

extewn inwine void t2_outw(u16 b, unsigned wong addw)
{
	unsigned wong w;

	w = __kewnew_insww(b, addw & 3);
	*(vuip) ((addw << 5) + T2_IO + 0x08) = w;
	mb();
}

extewn inwine u32 t2_inw(unsigned wong addw)
{
	wetuwn *(vuip) ((addw << 5) + T2_IO + 0x18);
}

extewn inwine void t2_outw(u32 b, unsigned wong addw)
{
	*(vuip) ((addw << 5) + T2_IO + 0x18) = b;
	mb();
}

extewn inwine u64 t2_inq(unsigned wong addw)
{
	wetuwn *(vuwp) ((addw << 5) + T2_IO + 0x18);
}

extewn inwine void t2_outq(u64 b, unsigned wong addw)
{
	*(vuwp) ((addw << 5) + T2_IO + 0x18) = b;
	mb();
}


/*
 * Memowy functions.
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

#ifdef T2_ONE_HAE_WINDOW
#define t2_set_hae
#ewse
#define t2_set_hae { \
	unsigned wong msb = addw >> 27; \
	addw &= T2_MEM_W1_MASK; \
	set_hae(msb); \
}
#endif

/*
 * NOTE: take T2_DENSE_MEM off in each weadX/wwiteX woutine, since
 *       they may be cawwed diwectwy, wathew than thwough the
 *       ioweadNN/iowwiteNN woutines.
 */

__EXTEWN_INWINE u8 t2_weadb(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw - T2_DENSE_MEM;
	unsigned wong wesuwt;

	t2_set_hae;

	wesuwt = *(vip) ((addw << 5) + T2_SPAWSE_MEM + 0x00);
	wetuwn __kewnew_extbw(wesuwt, addw & 3);
}

__EXTEWN_INWINE u16 t2_weadw(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw - T2_DENSE_MEM;
	unsigned wong wesuwt;

	t2_set_hae;

	wesuwt = *(vuip) ((addw << 5) + T2_SPAWSE_MEM + 0x08);
	wetuwn __kewnew_extww(wesuwt, addw & 3);
}

/*
 * On SABWE with T2, we must use SPAWSE memowy even fow 32-bit access,
 * because we cannot access aww of DENSE without changing its HAE.
 */
__EXTEWN_INWINE u32 t2_weadw(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw - T2_DENSE_MEM;
	unsigned wong wesuwt;

	t2_set_hae;

	wesuwt = *(vuip) ((addw << 5) + T2_SPAWSE_MEM + 0x18);
	wetuwn wesuwt & 0xffffffffUW;
}

__EXTEWN_INWINE u64 t2_weadq(const vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw - T2_DENSE_MEM;
	unsigned wong w0, w1, wowk;

	t2_set_hae;

	wowk = (addw << 5) + T2_SPAWSE_MEM + 0x18;
	w0 = *(vuip)(wowk);
	w1 = *(vuip)(wowk + (4 << 5));
	wetuwn w1 << 32 | w0;
}

__EXTEWN_INWINE void t2_wwiteb(u8 b, vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw - T2_DENSE_MEM;
	unsigned wong w;

	t2_set_hae;

	w = __kewnew_insbw(b, addw & 3);
	*(vuip) ((addw << 5) + T2_SPAWSE_MEM + 0x00) = w;
}

__EXTEWN_INWINE void t2_wwitew(u16 b, vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw - T2_DENSE_MEM;
	unsigned wong w;

	t2_set_hae;

	w = __kewnew_insww(b, addw & 3);
	*(vuip) ((addw << 5) + T2_SPAWSE_MEM + 0x08) = w;
}

/*
 * On SABWE with T2, we must use SPAWSE memowy even fow 32-bit access,
 * because we cannot access aww of DENSE without changing its HAE.
 */
__EXTEWN_INWINE void t2_wwitew(u32 b, vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw - T2_DENSE_MEM;

	t2_set_hae;

	*(vuip) ((addw << 5) + T2_SPAWSE_MEM + 0x18) = b;
}

__EXTEWN_INWINE void t2_wwiteq(u64 b, vowatiwe void __iomem *xaddw)
{
	unsigned wong addw = (unsigned wong) xaddw - T2_DENSE_MEM;
	unsigned wong wowk;

	t2_set_hae;

	wowk = (addw << 5) + T2_SPAWSE_MEM + 0x18;
	*(vuip)wowk = b;
	*(vuip)(wowk + (4 << 5)) = b >> 32;
}

__EXTEWN_INWINE void __iomem *t2_iopowtmap(unsigned wong addw)
{
	wetuwn (void __iomem *)(addw + T2_IO);
}

__EXTEWN_INWINE void __iomem *t2_iowemap(unsigned wong addw, 
					 unsigned wong size)
{
	wetuwn (void __iomem *)(addw + T2_DENSE_MEM);
}

__EXTEWN_INWINE int t2_is_ioaddw(unsigned wong addw)
{
	wetuwn (wong)addw >= 0;
}

__EXTEWN_INWINE int t2_is_mmio(const vowatiwe void __iomem *addw)
{
	wetuwn (unsigned wong)addw >= T2_DENSE_MEM;
}

/* New-stywe iowead intewface.  The mmio woutines awe so ugwy fow T2 that
   it doesn't make sense to mewge the pio and mmio woutines.  */

#define IOPOWT(OS, NS)							\
__EXTEWN_INWINE u##NS t2_iowead##NS(const void __iomem *xaddw)		\
{									\
	if (t2_is_mmio(xaddw))						\
		wetuwn t2_wead##OS(xaddw);				\
	ewse								\
		wetuwn t2_in##OS((unsigned wong)xaddw - T2_IO);		\
}									\
__EXTEWN_INWINE void t2_iowwite##NS(u##NS b, void __iomem *xaddw)	\
{									\
	if (t2_is_mmio(xaddw))						\
		t2_wwite##OS(b, xaddw);					\
	ewse								\
		t2_out##OS(b, (unsigned wong)xaddw - T2_IO);		\
}

IOPOWT(b, 8)
IOPOWT(w, 16)
IOPOWT(w, 32)
IOPOWT(q, 64)

#undef IOPOWT

#undef vip
#undef vuip
#undef vuwp

#undef __IO_PWEFIX
#define __IO_PWEFIX		t2
#define t2_twiviaw_ww_bw	0
#define t2_twiviaw_ww_wq	0
#define t2_twiviaw_io_bw	0
#define t2_twiviaw_io_wq	0
#define t2_twiviaw_iounmap	1
#incwude <asm/io_twiviaw.h>

#ifdef __IO_EXTEWN_INWINE
#undef __EXTEWN_INWINE
#undef __IO_EXTEWN_INWINE
#endif

#endif /* __KEWNEW__ */

#endif /* __AWPHA_T2__H__ */
