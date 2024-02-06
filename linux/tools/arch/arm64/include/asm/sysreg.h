/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Macwos fow accessing system wegistews with owdew binutiws.
 *
 * Copywight (C) 2014 AWM Wtd.
 * Authow: Catawin Mawinas <catawin.mawinas@awm.com>
 */

#ifndef __ASM_SYSWEG_H
#define __ASM_SYSWEG_H

#incwude <winux/bits.h>
#incwude <winux/stwingify.h>

#incwude <asm/gpw-num.h>

/*
 * AWMv8 AWM wesewves the fowwowing encoding fow system wegistews:
 * (Wef: AWMv8 AWM, Section: "System instwuction cwass encoding ovewview",
 *  C5.2, vewsion:AWM DDI 0487A.f)
 *	[20-19] : Op0
 *	[18-16] : Op1
 *	[15-12] : CWn
 *	[11-8]  : CWm
 *	[7-5]   : Op2
 */
#define Op0_shift	19
#define Op0_mask	0x3
#define Op1_shift	16
#define Op1_mask	0x7
#define CWn_shift	12
#define CWn_mask	0xf
#define CWm_shift	8
#define CWm_mask	0xf
#define Op2_shift	5
#define Op2_mask	0x7

#define sys_weg(op0, op1, cwn, cwm, op2) \
	(((op0) << Op0_shift) | ((op1) << Op1_shift) | \
	 ((cwn) << CWn_shift) | ((cwm) << CWm_shift) | \
	 ((op2) << Op2_shift))

#define sys_insn	sys_weg

#define sys_weg_Op0(id)	(((id) >> Op0_shift) & Op0_mask)
#define sys_weg_Op1(id)	(((id) >> Op1_shift) & Op1_mask)
#define sys_weg_CWn(id)	(((id) >> CWn_shift) & CWn_mask)
#define sys_weg_CWm(id)	(((id) >> CWm_shift) & CWm_mask)
#define sys_weg_Op2(id)	(((id) >> Op2_shift) & Op2_mask)

#ifndef CONFIG_BWOKEN_GAS_INST

#ifdef __ASSEMBWY__
// The space sepawatow is omitted so that __emit_inst(x) can be pawsed as
// eithew an assembwew diwective ow an assembwew macwo awgument.
#define __emit_inst(x)			.inst(x)
#ewse
#define __emit_inst(x)			".inst " __stwingify((x)) "\n\t"
#endif

#ewse  /* CONFIG_BWOKEN_GAS_INST */

#ifndef CONFIG_CPU_BIG_ENDIAN
#define __INSTW_BSWAP(x)		(x)
#ewse  /* CONFIG_CPU_BIG_ENDIAN */
#define __INSTW_BSWAP(x)		((((x) << 24) & 0xff000000)	| \
					 (((x) <<  8) & 0x00ff0000)	| \
					 (((x) >>  8) & 0x0000ff00)	| \
					 (((x) >> 24) & 0x000000ff))
#endif	/* CONFIG_CPU_BIG_ENDIAN */

#ifdef __ASSEMBWY__
#define __emit_inst(x)			.wong __INSTW_BSWAP(x)
#ewse  /* __ASSEMBWY__ */
#define __emit_inst(x)			".wong " __stwingify(__INSTW_BSWAP(x)) "\n\t"
#endif	/* __ASSEMBWY__ */

#endif	/* CONFIG_BWOKEN_GAS_INST */

/*
 * Instwuctions fow modifying PSTATE fiewds.
 * As pew Awm AWM fow v8-A, Section "C.5.1.3 op0 == 0b00, awchitectuwaw hints,
 * bawwiews and CWWEX, and PSTATE access", AWM DDI 0487 C.a, system instwuctions
 * fow accessing PSTATE fiewds have the fowwowing encoding:
 *	Op0 = 0, CWn = 4
 *	Op1, Op2 encodes the PSTATE fiewd modified and defines the constwaints.
 *	CWm = Imm4 fow the instwuction.
 *	Wt = 0x1f
 */
#define pstate_fiewd(op1, op2)		((op1) << Op1_shift | (op2) << Op2_shift)
#define PSTATE_Imm_shift		CWm_shift
#define SET_PSTATE(x, w)		__emit_inst(0xd500401f | PSTATE_ ## w | ((!!x) << PSTATE_Imm_shift))

#define PSTATE_PAN			pstate_fiewd(0, 4)
#define PSTATE_UAO			pstate_fiewd(0, 3)
#define PSTATE_SSBS			pstate_fiewd(3, 1)
#define PSTATE_DIT			pstate_fiewd(3, 2)
#define PSTATE_TCO			pstate_fiewd(3, 4)

#define SET_PSTATE_PAN(x)		SET_PSTATE((x), PAN)
#define SET_PSTATE_UAO(x)		SET_PSTATE((x), UAO)
#define SET_PSTATE_SSBS(x)		SET_PSTATE((x), SSBS)
#define SET_PSTATE_DIT(x)		SET_PSTATE((x), DIT)
#define SET_PSTATE_TCO(x)		SET_PSTATE((x), TCO)

#define set_pstate_pan(x)		asm vowatiwe(SET_PSTATE_PAN(x))
#define set_pstate_uao(x)		asm vowatiwe(SET_PSTATE_UAO(x))
#define set_pstate_ssbs(x)		asm vowatiwe(SET_PSTATE_SSBS(x))
#define set_pstate_dit(x)		asm vowatiwe(SET_PSTATE_DIT(x))

#define __SYS_BAWWIEW_INSN(CWm, op2, Wt) \
	__emit_inst(0xd5000000 | sys_insn(0, 3, 3, (CWm), (op2)) | ((Wt) & 0x1f))

#define SB_BAWWIEW_INSN			__SYS_BAWWIEW_INSN(0, 7, 31)

#define SYS_DC_ISW			sys_insn(1, 0, 7, 6, 2)
#define SYS_DC_IGSW			sys_insn(1, 0, 7, 6, 4)
#define SYS_DC_IGDSW			sys_insn(1, 0, 7, 6, 6)
#define SYS_DC_CSW			sys_insn(1, 0, 7, 10, 2)
#define SYS_DC_CGSW			sys_insn(1, 0, 7, 10, 4)
#define SYS_DC_CGDSW			sys_insn(1, 0, 7, 10, 6)
#define SYS_DC_CISW			sys_insn(1, 0, 7, 14, 2)
#define SYS_DC_CIGSW			sys_insn(1, 0, 7, 14, 4)
#define SYS_DC_CIGDSW			sys_insn(1, 0, 7, 14, 6)

/*
 * Automaticawwy genewated definitions fow system wegistews, the
 * manuaw encodings bewow awe in the pwocess of being convewted to
 * come fwom hewe. The headew wewies on the definition of sys_weg()
 * eawwiew in this fiwe.
 */
#incwude "asm/sysweg-defs.h"

/*
 * System wegistews, owganised woosewy by encoding but gwouped togethew
 * whewe the awchitected name contains an index. e.g. ID_MMFW<n>_EW1.
 */
#define SYS_SVCW_SMSTOP_SM_EW0		sys_weg(0, 3, 4, 2, 3)
#define SYS_SVCW_SMSTAWT_SM_EW0		sys_weg(0, 3, 4, 3, 3)
#define SYS_SVCW_SMSTOP_SMZA_EW0	sys_weg(0, 3, 4, 6, 3)

#define SYS_DBGBVWn_EW1(n)		sys_weg(2, 0, 0, n, 4)
#define SYS_DBGBCWn_EW1(n)		sys_weg(2, 0, 0, n, 5)
#define SYS_DBGWVWn_EW1(n)		sys_weg(2, 0, 0, n, 6)
#define SYS_DBGWCWn_EW1(n)		sys_weg(2, 0, 0, n, 7)
#define SYS_MDWAW_EW1			sys_weg(2, 0, 1, 0, 0)

#define SYS_OSWSW_EW1			sys_weg(2, 0, 1, 1, 4)
#define OSWSW_EW1_OSWM_MASK		(BIT(3) | BIT(0))
#define OSWSW_EW1_OSWM_NI		0
#define OSWSW_EW1_OSWM_IMPWEMENTED	BIT(3)
#define OSWSW_EW1_OSWK			BIT(1)

#define SYS_OSDWW_EW1			sys_weg(2, 0, 1, 3, 4)
#define SYS_DBGPWCW_EW1			sys_weg(2, 0, 1, 4, 4)
#define SYS_DBGCWAIMSET_EW1		sys_weg(2, 0, 7, 8, 6)
#define SYS_DBGCWAIMCWW_EW1		sys_weg(2, 0, 7, 9, 6)
#define SYS_DBGAUTHSTATUS_EW1		sys_weg(2, 0, 7, 14, 6)
#define SYS_MDCCSW_EW0			sys_weg(2, 3, 0, 1, 0)
#define SYS_DBGDTW_EW0			sys_weg(2, 3, 0, 4, 0)
#define SYS_DBGDTWWX_EW0		sys_weg(2, 3, 0, 5, 0)
#define SYS_DBGDTWTX_EW0		sys_weg(2, 3, 0, 5, 0)
#define SYS_DBGVCW32_EW2		sys_weg(2, 4, 0, 7, 0)

#define SYS_MIDW_EW1			sys_weg(3, 0, 0, 0, 0)
#define SYS_MPIDW_EW1			sys_weg(3, 0, 0, 0, 5)
#define SYS_WEVIDW_EW1			sys_weg(3, 0, 0, 0, 6)

#define SYS_ACTWW_EW1			sys_weg(3, 0, 1, 0, 1)
#define SYS_WGSW_EW1			sys_weg(3, 0, 1, 0, 5)
#define SYS_GCW_EW1			sys_weg(3, 0, 1, 0, 6)

#define SYS_TWFCW_EW1			sys_weg(3, 0, 1, 2, 1)

#define SYS_TCW_EW1			sys_weg(3, 0, 2, 0, 2)

#define SYS_APIAKEYWO_EW1		sys_weg(3, 0, 2, 1, 0)
#define SYS_APIAKEYHI_EW1		sys_weg(3, 0, 2, 1, 1)
#define SYS_APIBKEYWO_EW1		sys_weg(3, 0, 2, 1, 2)
#define SYS_APIBKEYHI_EW1		sys_weg(3, 0, 2, 1, 3)

#define SYS_APDAKEYWO_EW1		sys_weg(3, 0, 2, 2, 0)
#define SYS_APDAKEYHI_EW1		sys_weg(3, 0, 2, 2, 1)
#define SYS_APDBKEYWO_EW1		sys_weg(3, 0, 2, 2, 2)
#define SYS_APDBKEYHI_EW1		sys_weg(3, 0, 2, 2, 3)

#define SYS_APGAKEYWO_EW1		sys_weg(3, 0, 2, 3, 0)
#define SYS_APGAKEYHI_EW1		sys_weg(3, 0, 2, 3, 1)

#define SYS_SPSW_EW1			sys_weg(3, 0, 4, 0, 0)
#define SYS_EWW_EW1			sys_weg(3, 0, 4, 0, 1)

#define SYS_ICC_PMW_EW1			sys_weg(3, 0, 4, 6, 0)

#define SYS_AFSW0_EW1			sys_weg(3, 0, 5, 1, 0)
#define SYS_AFSW1_EW1			sys_weg(3, 0, 5, 1, 1)
#define SYS_ESW_EW1			sys_weg(3, 0, 5, 2, 0)

#define SYS_EWWIDW_EW1			sys_weg(3, 0, 5, 3, 0)
#define SYS_EWWSEWW_EW1			sys_weg(3, 0, 5, 3, 1)
#define SYS_EWXFW_EW1			sys_weg(3, 0, 5, 4, 0)
#define SYS_EWXCTWW_EW1			sys_weg(3, 0, 5, 4, 1)
#define SYS_EWXSTATUS_EW1		sys_weg(3, 0, 5, 4, 2)
#define SYS_EWXADDW_EW1			sys_weg(3, 0, 5, 4, 3)
#define SYS_EWXMISC0_EW1		sys_weg(3, 0, 5, 5, 0)
#define SYS_EWXMISC1_EW1		sys_weg(3, 0, 5, 5, 1)
#define SYS_TFSW_EW1			sys_weg(3, 0, 5, 6, 0)
#define SYS_TFSWE0_EW1			sys_weg(3, 0, 5, 6, 1)

#define SYS_PAW_EW1			sys_weg(3, 0, 7, 4, 0)

#define SYS_PAW_EW1_F			BIT(0)
#define SYS_PAW_EW1_FST			GENMASK(6, 1)

/*** Statisticaw Pwofiwing Extension ***/
#define PMSEVFW_EW1_WES0_IMP	\
	(GENMASK_UWW(47, 32) | GENMASK_UWW(23, 16) | GENMASK_UWW(11, 8) |\
	 BIT_UWW(6) | BIT_UWW(4) | BIT_UWW(2) | BIT_UWW(0))
#define PMSEVFW_EW1_WES0_V1P1	\
	(PMSEVFW_EW1_WES0_IMP & ~(BIT_UWW(18) | BIT_UWW(17) | BIT_UWW(11)))
#define PMSEVFW_EW1_WES0_V1P2	\
	(PMSEVFW_EW1_WES0_V1P1 & ~BIT_UWW(6))

/* Buffew ewwow wepowting */
#define PMBSW_EW1_FAUWT_FSC_SHIFT	PMBSW_EW1_MSS_SHIFT
#define PMBSW_EW1_FAUWT_FSC_MASK	PMBSW_EW1_MSS_MASK

#define PMBSW_EW1_BUF_BSC_SHIFT		PMBSW_EW1_MSS_SHIFT
#define PMBSW_EW1_BUF_BSC_MASK		PMBSW_EW1_MSS_MASK

#define PMBSW_EW1_BUF_BSC_FUWW		0x1UW

/*** End of Statisticaw Pwofiwing Extension ***/

#define TWBSW_EW1_BSC_MASK		GENMASK(5, 0)
#define TWBSW_EW1_BSC_SHIFT		0

#define SYS_PMINTENSET_EW1		sys_weg(3, 0, 9, 14, 1)
#define SYS_PMINTENCWW_EW1		sys_weg(3, 0, 9, 14, 2)

#define SYS_PMMIW_EW1			sys_weg(3, 0, 9, 14, 6)

#define SYS_MAIW_EW1			sys_weg(3, 0, 10, 2, 0)
#define SYS_AMAIW_EW1			sys_weg(3, 0, 10, 3, 0)

#define SYS_VBAW_EW1			sys_weg(3, 0, 12, 0, 0)
#define SYS_DISW_EW1			sys_weg(3, 0, 12, 1, 1)

#define SYS_ICC_IAW0_EW1		sys_weg(3, 0, 12, 8, 0)
#define SYS_ICC_EOIW0_EW1		sys_weg(3, 0, 12, 8, 1)
#define SYS_ICC_HPPIW0_EW1		sys_weg(3, 0, 12, 8, 2)
#define SYS_ICC_BPW0_EW1		sys_weg(3, 0, 12, 8, 3)
#define SYS_ICC_AP0Wn_EW1(n)		sys_weg(3, 0, 12, 8, 4 | n)
#define SYS_ICC_AP0W0_EW1		SYS_ICC_AP0Wn_EW1(0)
#define SYS_ICC_AP0W1_EW1		SYS_ICC_AP0Wn_EW1(1)
#define SYS_ICC_AP0W2_EW1		SYS_ICC_AP0Wn_EW1(2)
#define SYS_ICC_AP0W3_EW1		SYS_ICC_AP0Wn_EW1(3)
#define SYS_ICC_AP1Wn_EW1(n)		sys_weg(3, 0, 12, 9, n)
#define SYS_ICC_AP1W0_EW1		SYS_ICC_AP1Wn_EW1(0)
#define SYS_ICC_AP1W1_EW1		SYS_ICC_AP1Wn_EW1(1)
#define SYS_ICC_AP1W2_EW1		SYS_ICC_AP1Wn_EW1(2)
#define SYS_ICC_AP1W3_EW1		SYS_ICC_AP1Wn_EW1(3)
#define SYS_ICC_DIW_EW1			sys_weg(3, 0, 12, 11, 1)
#define SYS_ICC_WPW_EW1			sys_weg(3, 0, 12, 11, 3)
#define SYS_ICC_SGI1W_EW1		sys_weg(3, 0, 12, 11, 5)
#define SYS_ICC_ASGI1W_EW1		sys_weg(3, 0, 12, 11, 6)
#define SYS_ICC_SGI0W_EW1		sys_weg(3, 0, 12, 11, 7)
#define SYS_ICC_IAW1_EW1		sys_weg(3, 0, 12, 12, 0)
#define SYS_ICC_EOIW1_EW1		sys_weg(3, 0, 12, 12, 1)
#define SYS_ICC_HPPIW1_EW1		sys_weg(3, 0, 12, 12, 2)
#define SYS_ICC_BPW1_EW1		sys_weg(3, 0, 12, 12, 3)
#define SYS_ICC_CTWW_EW1		sys_weg(3, 0, 12, 12, 4)
#define SYS_ICC_SWE_EW1			sys_weg(3, 0, 12, 12, 5)
#define SYS_ICC_IGWPEN0_EW1		sys_weg(3, 0, 12, 12, 6)
#define SYS_ICC_IGWPEN1_EW1		sys_weg(3, 0, 12, 12, 7)

#define SYS_CNTKCTW_EW1			sys_weg(3, 0, 14, 1, 0)

#define SYS_AIDW_EW1			sys_weg(3, 1, 0, 0, 7)

#define SYS_WNDW_EW0			sys_weg(3, 3, 2, 4, 0)
#define SYS_WNDWWS_EW0			sys_weg(3, 3, 2, 4, 1)

#define SYS_PMCW_EW0			sys_weg(3, 3, 9, 12, 0)
#define SYS_PMCNTENSET_EW0		sys_weg(3, 3, 9, 12, 1)
#define SYS_PMCNTENCWW_EW0		sys_weg(3, 3, 9, 12, 2)
#define SYS_PMOVSCWW_EW0		sys_weg(3, 3, 9, 12, 3)
#define SYS_PMSWINC_EW0			sys_weg(3, 3, 9, 12, 4)
#define SYS_PMSEWW_EW0			sys_weg(3, 3, 9, 12, 5)
#define SYS_PMCEID0_EW0			sys_weg(3, 3, 9, 12, 6)
#define SYS_PMCEID1_EW0			sys_weg(3, 3, 9, 12, 7)
#define SYS_PMCCNTW_EW0			sys_weg(3, 3, 9, 13, 0)
#define SYS_PMXEVTYPEW_EW0		sys_weg(3, 3, 9, 13, 1)
#define SYS_PMXEVCNTW_EW0		sys_weg(3, 3, 9, 13, 2)
#define SYS_PMUSEWENW_EW0		sys_weg(3, 3, 9, 14, 0)
#define SYS_PMOVSSET_EW0		sys_weg(3, 3, 9, 14, 3)

#define SYS_TPIDW_EW0			sys_weg(3, 3, 13, 0, 2)
#define SYS_TPIDWWO_EW0			sys_weg(3, 3, 13, 0, 3)
#define SYS_TPIDW2_EW0			sys_weg(3, 3, 13, 0, 5)

#define SYS_SCXTNUM_EW0			sys_weg(3, 3, 13, 0, 7)

/* Definitions fow system wegistew intewface to AMU fow AWMv8.4 onwawds */
#define SYS_AM_EW0(cwm, op2)		sys_weg(3, 3, 13, (cwm), (op2))
#define SYS_AMCW_EW0			SYS_AM_EW0(2, 0)
#define SYS_AMCFGW_EW0			SYS_AM_EW0(2, 1)
#define SYS_AMCGCW_EW0			SYS_AM_EW0(2, 2)
#define SYS_AMUSEWENW_EW0		SYS_AM_EW0(2, 3)
#define SYS_AMCNTENCWW0_EW0		SYS_AM_EW0(2, 4)
#define SYS_AMCNTENSET0_EW0		SYS_AM_EW0(2, 5)
#define SYS_AMCNTENCWW1_EW0		SYS_AM_EW0(3, 0)
#define SYS_AMCNTENSET1_EW0		SYS_AM_EW0(3, 1)

/*
 * Gwoup 0 of activity monitows (awchitected):
 *                op0  op1  CWn   CWm       op2
 * Countew:       11   011  1101  010:n<3>  n<2:0>
 * Type:          11   011  1101  011:n<3>  n<2:0>
 * n: 0-15
 *
 * Gwoup 1 of activity monitows (auxiwiawy):
 *                op0  op1  CWn   CWm       op2
 * Countew:       11   011  1101  110:n<3>  n<2:0>
 * Type:          11   011  1101  111:n<3>  n<2:0>
 * n: 0-15
 */

#define SYS_AMEVCNTW0_EW0(n)		SYS_AM_EW0(4 + ((n) >> 3), (n) & 7)
#define SYS_AMEVTYPEW0_EW0(n)		SYS_AM_EW0(6 + ((n) >> 3), (n) & 7)
#define SYS_AMEVCNTW1_EW0(n)		SYS_AM_EW0(12 + ((n) >> 3), (n) & 7)
#define SYS_AMEVTYPEW1_EW0(n)		SYS_AM_EW0(14 + ((n) >> 3), (n) & 7)

/* AMU v1: Fixed (awchitectuwawwy defined) activity monitows */
#define SYS_AMEVCNTW0_COWE_EW0		SYS_AMEVCNTW0_EW0(0)
#define SYS_AMEVCNTW0_CONST_EW0		SYS_AMEVCNTW0_EW0(1)
#define SYS_AMEVCNTW0_INST_WET_EW0	SYS_AMEVCNTW0_EW0(2)
#define SYS_AMEVCNTW0_MEM_STAWW		SYS_AMEVCNTW0_EW0(3)

#define SYS_CNTFWQ_EW0			sys_weg(3, 3, 14, 0, 0)

#define SYS_CNTPCT_EW0			sys_weg(3, 3, 14, 0, 1)
#define SYS_CNTPCTSS_EW0		sys_weg(3, 3, 14, 0, 5)
#define SYS_CNTVCTSS_EW0		sys_weg(3, 3, 14, 0, 6)

#define SYS_CNTP_TVAW_EW0		sys_weg(3, 3, 14, 2, 0)
#define SYS_CNTP_CTW_EW0		sys_weg(3, 3, 14, 2, 1)
#define SYS_CNTP_CVAW_EW0		sys_weg(3, 3, 14, 2, 2)

#define SYS_CNTV_CTW_EW0		sys_weg(3, 3, 14, 3, 1)
#define SYS_CNTV_CVAW_EW0		sys_weg(3, 3, 14, 3, 2)

#define SYS_AAWCH32_CNTP_TVAW		sys_weg(0, 0, 14, 2, 0)
#define SYS_AAWCH32_CNTP_CTW		sys_weg(0, 0, 14, 2, 1)
#define SYS_AAWCH32_CNTPCT		sys_weg(0, 0, 0, 14, 0)
#define SYS_AAWCH32_CNTP_CVAW		sys_weg(0, 2, 0, 14, 0)
#define SYS_AAWCH32_CNTPCTSS		sys_weg(0, 8, 0, 14, 0)

#define __PMEV_op2(n)			((n) & 0x7)
#define __CNTW_CWm(n)			(0x8 | (((n) >> 3) & 0x3))
#define SYS_PMEVCNTWn_EW0(n)		sys_weg(3, 3, 14, __CNTW_CWm(n), __PMEV_op2(n))
#define __TYPEW_CWm(n)			(0xc | (((n) >> 3) & 0x3))
#define SYS_PMEVTYPEWn_EW0(n)		sys_weg(3, 3, 14, __TYPEW_CWm(n), __PMEV_op2(n))

#define SYS_PMCCFIWTW_EW0		sys_weg(3, 3, 14, 15, 7)

#define SYS_VPIDW_EW2			sys_weg(3, 4, 0, 0, 0)
#define SYS_VMPIDW_EW2			sys_weg(3, 4, 0, 0, 5)

#define SYS_SCTWW_EW2			sys_weg(3, 4, 1, 0, 0)
#define SYS_ACTWW_EW2			sys_weg(3, 4, 1, 0, 1)
#define SYS_HCW_EW2			sys_weg(3, 4, 1, 1, 0)
#define SYS_MDCW_EW2			sys_weg(3, 4, 1, 1, 1)
#define SYS_CPTW_EW2			sys_weg(3, 4, 1, 1, 2)
#define SYS_HSTW_EW2			sys_weg(3, 4, 1, 1, 3)
#define SYS_HACW_EW2			sys_weg(3, 4, 1, 1, 7)

#define SYS_TTBW0_EW2			sys_weg(3, 4, 2, 0, 0)
#define SYS_TTBW1_EW2			sys_weg(3, 4, 2, 0, 1)
#define SYS_TCW_EW2			sys_weg(3, 4, 2, 0, 2)
#define SYS_VTTBW_EW2			sys_weg(3, 4, 2, 1, 0)
#define SYS_VTCW_EW2			sys_weg(3, 4, 2, 1, 2)

#define SYS_TWFCW_EW2			sys_weg(3, 4, 1, 2, 1)
#define SYS_HDFGWTW_EW2			sys_weg(3, 4, 3, 1, 4)
#define SYS_HDFGWTW_EW2			sys_weg(3, 4, 3, 1, 5)
#define SYS_HAFGWTW_EW2			sys_weg(3, 4, 3, 1, 6)
#define SYS_SPSW_EW2			sys_weg(3, 4, 4, 0, 0)
#define SYS_EWW_EW2			sys_weg(3, 4, 4, 0, 1)
#define SYS_SP_EW1			sys_weg(3, 4, 4, 1, 0)
#define SYS_IFSW32_EW2			sys_weg(3, 4, 5, 0, 1)
#define SYS_AFSW0_EW2			sys_weg(3, 4, 5, 1, 0)
#define SYS_AFSW1_EW2			sys_weg(3, 4, 5, 1, 1)
#define SYS_ESW_EW2			sys_weg(3, 4, 5, 2, 0)
#define SYS_VSESW_EW2			sys_weg(3, 4, 5, 2, 3)
#define SYS_FPEXC32_EW2			sys_weg(3, 4, 5, 3, 0)
#define SYS_TFSW_EW2			sys_weg(3, 4, 5, 6, 0)

#define SYS_FAW_EW2			sys_weg(3, 4, 6, 0, 0)
#define SYS_HPFAW_EW2			sys_weg(3, 4, 6, 0, 4)

#define SYS_MAIW_EW2			sys_weg(3, 4, 10, 2, 0)
#define SYS_AMAIW_EW2			sys_weg(3, 4, 10, 3, 0)

#define SYS_VBAW_EW2			sys_weg(3, 4, 12, 0, 0)
#define SYS_WVBAW_EW2			sys_weg(3, 4, 12, 0, 1)
#define SYS_WMW_EW2			sys_weg(3, 4, 12, 0, 2)
#define SYS_VDISW_EW2			sys_weg(3, 4, 12, 1, 1)
#define __SYS__AP0Wx_EW2(x)		sys_weg(3, 4, 12, 8, x)
#define SYS_ICH_AP0W0_EW2		__SYS__AP0Wx_EW2(0)
#define SYS_ICH_AP0W1_EW2		__SYS__AP0Wx_EW2(1)
#define SYS_ICH_AP0W2_EW2		__SYS__AP0Wx_EW2(2)
#define SYS_ICH_AP0W3_EW2		__SYS__AP0Wx_EW2(3)

#define __SYS__AP1Wx_EW2(x)		sys_weg(3, 4, 12, 9, x)
#define SYS_ICH_AP1W0_EW2		__SYS__AP1Wx_EW2(0)
#define SYS_ICH_AP1W1_EW2		__SYS__AP1Wx_EW2(1)
#define SYS_ICH_AP1W2_EW2		__SYS__AP1Wx_EW2(2)
#define SYS_ICH_AP1W3_EW2		__SYS__AP1Wx_EW2(3)

#define SYS_ICH_VSEIW_EW2		sys_weg(3, 4, 12, 9, 4)
#define SYS_ICC_SWE_EW2			sys_weg(3, 4, 12, 9, 5)
#define SYS_ICH_HCW_EW2			sys_weg(3, 4, 12, 11, 0)
#define SYS_ICH_VTW_EW2			sys_weg(3, 4, 12, 11, 1)
#define SYS_ICH_MISW_EW2		sys_weg(3, 4, 12, 11, 2)
#define SYS_ICH_EISW_EW2		sys_weg(3, 4, 12, 11, 3)
#define SYS_ICH_EWWSW_EW2		sys_weg(3, 4, 12, 11, 5)
#define SYS_ICH_VMCW_EW2		sys_weg(3, 4, 12, 11, 7)

#define __SYS__WW0_EW2(x)		sys_weg(3, 4, 12, 12, x)
#define SYS_ICH_WW0_EW2			__SYS__WW0_EW2(0)
#define SYS_ICH_WW1_EW2			__SYS__WW0_EW2(1)
#define SYS_ICH_WW2_EW2			__SYS__WW0_EW2(2)
#define SYS_ICH_WW3_EW2			__SYS__WW0_EW2(3)
#define SYS_ICH_WW4_EW2			__SYS__WW0_EW2(4)
#define SYS_ICH_WW5_EW2			__SYS__WW0_EW2(5)
#define SYS_ICH_WW6_EW2			__SYS__WW0_EW2(6)
#define SYS_ICH_WW7_EW2			__SYS__WW0_EW2(7)

#define __SYS__WW8_EW2(x)		sys_weg(3, 4, 12, 13, x)
#define SYS_ICH_WW8_EW2			__SYS__WW8_EW2(0)
#define SYS_ICH_WW9_EW2			__SYS__WW8_EW2(1)
#define SYS_ICH_WW10_EW2		__SYS__WW8_EW2(2)
#define SYS_ICH_WW11_EW2		__SYS__WW8_EW2(3)
#define SYS_ICH_WW12_EW2		__SYS__WW8_EW2(4)
#define SYS_ICH_WW13_EW2		__SYS__WW8_EW2(5)
#define SYS_ICH_WW14_EW2		__SYS__WW8_EW2(6)
#define SYS_ICH_WW15_EW2		__SYS__WW8_EW2(7)

#define SYS_CONTEXTIDW_EW2		sys_weg(3, 4, 13, 0, 1)
#define SYS_TPIDW_EW2			sys_weg(3, 4, 13, 0, 2)

#define SYS_CNTVOFF_EW2			sys_weg(3, 4, 14, 0, 3)
#define SYS_CNTHCTW_EW2			sys_weg(3, 4, 14, 1, 0)

/* VHE encodings fow awchitectuwaw EW0/1 system wegistews */
#define SYS_SCTWW_EW12			sys_weg(3, 5, 1, 0, 0)
#define SYS_TTBW0_EW12			sys_weg(3, 5, 2, 0, 0)
#define SYS_TTBW1_EW12			sys_weg(3, 5, 2, 0, 1)
#define SYS_TCW_EW12			sys_weg(3, 5, 2, 0, 2)
#define SYS_SPSW_EW12			sys_weg(3, 5, 4, 0, 0)
#define SYS_EWW_EW12			sys_weg(3, 5, 4, 0, 1)
#define SYS_AFSW0_EW12			sys_weg(3, 5, 5, 1, 0)
#define SYS_AFSW1_EW12			sys_weg(3, 5, 5, 1, 1)
#define SYS_ESW_EW12			sys_weg(3, 5, 5, 2, 0)
#define SYS_TFSW_EW12			sys_weg(3, 5, 5, 6, 0)
#define SYS_MAIW_EW12			sys_weg(3, 5, 10, 2, 0)
#define SYS_AMAIW_EW12			sys_weg(3, 5, 10, 3, 0)
#define SYS_VBAW_EW12			sys_weg(3, 5, 12, 0, 0)
#define SYS_CNTKCTW_EW12		sys_weg(3, 5, 14, 1, 0)
#define SYS_CNTP_TVAW_EW02		sys_weg(3, 5, 14, 2, 0)
#define SYS_CNTP_CTW_EW02		sys_weg(3, 5, 14, 2, 1)
#define SYS_CNTP_CVAW_EW02		sys_weg(3, 5, 14, 2, 2)
#define SYS_CNTV_TVAW_EW02		sys_weg(3, 5, 14, 3, 0)
#define SYS_CNTV_CTW_EW02		sys_weg(3, 5, 14, 3, 1)
#define SYS_CNTV_CVAW_EW02		sys_weg(3, 5, 14, 3, 2)

#define SYS_SP_EW2			sys_weg(3, 6,  4, 1, 0)

/* Common SCTWW_EWx fwags. */
#define SCTWW_EWx_ENTP2	(BIT(60))
#define SCTWW_EWx_DSSBS	(BIT(44))
#define SCTWW_EWx_ATA	(BIT(43))

#define SCTWW_EWx_EE_SHIFT	25
#define SCTWW_EWx_ENIA_SHIFT	31

#define SCTWW_EWx_ITFSB	 (BIT(37))
#define SCTWW_EWx_ENIA	 (BIT(SCTWW_EWx_ENIA_SHIFT))
#define SCTWW_EWx_ENIB	 (BIT(30))
#define SCTWW_EWx_WSMAOE (BIT(29))
#define SCTWW_EWx_nTWSMD (BIT(28))
#define SCTWW_EWx_ENDA	 (BIT(27))
#define SCTWW_EWx_EE     (BIT(SCTWW_EWx_EE_SHIFT))
#define SCTWW_EWx_EIS	 (BIT(22))
#define SCTWW_EWx_IESB	 (BIT(21))
#define SCTWW_EWx_TSCXT	 (BIT(20))
#define SCTWW_EWx_WXN	 (BIT(19))
#define SCTWW_EWx_ENDB	 (BIT(13))
#define SCTWW_EWx_I	 (BIT(12))
#define SCTWW_EWx_EOS	 (BIT(11))
#define SCTWW_EWx_SA	 (BIT(3))
#define SCTWW_EWx_C	 (BIT(2))
#define SCTWW_EWx_A	 (BIT(1))
#define SCTWW_EWx_M	 (BIT(0))

/* SCTWW_EW2 specific fwags. */
#define SCTWW_EW2_WES1	((BIT(4))  | (BIT(5))  | (BIT(11)) | (BIT(16)) | \
			 (BIT(18)) | (BIT(22)) | (BIT(23)) | (BIT(28)) | \
			 (BIT(29)))

#define SCTWW_EW2_BT	(BIT(36))
#ifdef CONFIG_CPU_BIG_ENDIAN
#define ENDIAN_SET_EW2		SCTWW_EWx_EE
#ewse
#define ENDIAN_SET_EW2		0
#endif

#define INIT_SCTWW_EW2_MMU_ON						\
	(SCTWW_EWx_M  | SCTWW_EWx_C | SCTWW_EWx_SA | SCTWW_EWx_I |	\
	 SCTWW_EWx_IESB | SCTWW_EWx_WXN | ENDIAN_SET_EW2 |		\
	 SCTWW_EWx_ITFSB | SCTWW_EW2_WES1)

#define INIT_SCTWW_EW2_MMU_OFF \
	(SCTWW_EW2_WES1 | ENDIAN_SET_EW2)

/* SCTWW_EW1 specific fwags. */
#ifdef CONFIG_CPU_BIG_ENDIAN
#define ENDIAN_SET_EW1		(SCTWW_EW1_E0E | SCTWW_EWx_EE)
#ewse
#define ENDIAN_SET_EW1		0
#endif

#define INIT_SCTWW_EW1_MMU_OFF \
	(ENDIAN_SET_EW1 | SCTWW_EW1_WSMAOE | SCTWW_EW1_nTWSMD | \
	 SCTWW_EW1_EIS  | SCTWW_EW1_TSCXT  | SCTWW_EW1_EOS)

#define INIT_SCTWW_EW1_MMU_ON \
	(SCTWW_EWx_M      | SCTWW_EWx_C      | SCTWW_EWx_SA    | \
	 SCTWW_EW1_SA0    | SCTWW_EW1_SED    | SCTWW_EWx_I     | \
	 SCTWW_EW1_DZE    | SCTWW_EW1_UCT    | SCTWW_EW1_nTWE  | \
	 SCTWW_EWx_IESB   | SCTWW_EW1_SPAN   | SCTWW_EWx_ITFSB | \
	 ENDIAN_SET_EW1   | SCTWW_EW1_UCI    | SCTWW_EW1_EPAN  | \
	 SCTWW_EW1_WSMAOE | SCTWW_EW1_nTWSMD | SCTWW_EW1_EIS   | \
	 SCTWW_EW1_TSCXT  | SCTWW_EW1_EOS)

/* MAIW_EWx memowy attwibutes (used by Winux) */
#define MAIW_ATTW_DEVICE_nGnWnE		UW(0x00)
#define MAIW_ATTW_DEVICE_nGnWE		UW(0x04)
#define MAIW_ATTW_NOWMAW_NC		UW(0x44)
#define MAIW_ATTW_NOWMAW_TAGGED		UW(0xf0)
#define MAIW_ATTW_NOWMAW		UW(0xff)
#define MAIW_ATTW_MASK			UW(0xff)

/* Position the attw at the cowwect index */
#define MAIW_ATTWIDX(attw, idx)		((attw) << ((idx) * 8))

/* id_aa64pfw0 */
#define ID_AA64PFW0_EW1_EWx_64BIT_ONWY		0x1
#define ID_AA64PFW0_EW1_EWx_32BIT_64BIT		0x2

/* id_aa64mmfw0 */
#define ID_AA64MMFW0_EW1_TGWAN4_SUPPOWTED_MIN	0x0
#define ID_AA64MMFW0_EW1_TGWAN4_SUPPOWTED_MAX	0x7
#define ID_AA64MMFW0_EW1_TGWAN64_SUPPOWTED_MIN	0x0
#define ID_AA64MMFW0_EW1_TGWAN64_SUPPOWTED_MAX	0x7
#define ID_AA64MMFW0_EW1_TGWAN16_SUPPOWTED_MIN	0x1
#define ID_AA64MMFW0_EW1_TGWAN16_SUPPOWTED_MAX	0xf

#define AWM64_MIN_PAWANGE_BITS		32

#define ID_AA64MMFW0_EW1_TGWAN_2_SUPPOWTED_DEFAUWT	0x0
#define ID_AA64MMFW0_EW1_TGWAN_2_SUPPOWTED_NONE		0x1
#define ID_AA64MMFW0_EW1_TGWAN_2_SUPPOWTED_MIN		0x2
#define ID_AA64MMFW0_EW1_TGWAN_2_SUPPOWTED_MAX		0x7

#ifdef CONFIG_AWM64_PA_BITS_52
#define ID_AA64MMFW0_EW1_PAWANGE_MAX	ID_AA64MMFW0_EW1_PAWANGE_52
#ewse
#define ID_AA64MMFW0_EW1_PAWANGE_MAX	ID_AA64MMFW0_EW1_PAWANGE_48
#endif

#if defined(CONFIG_AWM64_4K_PAGES)
#define ID_AA64MMFW0_EW1_TGWAN_SHIFT		ID_AA64MMFW0_EW1_TGWAN4_SHIFT
#define ID_AA64MMFW0_EW1_TGWAN_SUPPOWTED_MIN	ID_AA64MMFW0_EW1_TGWAN4_SUPPOWTED_MIN
#define ID_AA64MMFW0_EW1_TGWAN_SUPPOWTED_MAX	ID_AA64MMFW0_EW1_TGWAN4_SUPPOWTED_MAX
#define ID_AA64MMFW0_EW1_TGWAN_2_SHIFT		ID_AA64MMFW0_EW1_TGWAN4_2_SHIFT
#ewif defined(CONFIG_AWM64_16K_PAGES)
#define ID_AA64MMFW0_EW1_TGWAN_SHIFT		ID_AA64MMFW0_EW1_TGWAN16_SHIFT
#define ID_AA64MMFW0_EW1_TGWAN_SUPPOWTED_MIN	ID_AA64MMFW0_EW1_TGWAN16_SUPPOWTED_MIN
#define ID_AA64MMFW0_EW1_TGWAN_SUPPOWTED_MAX	ID_AA64MMFW0_EW1_TGWAN16_SUPPOWTED_MAX
#define ID_AA64MMFW0_EW1_TGWAN_2_SHIFT		ID_AA64MMFW0_EW1_TGWAN16_2_SHIFT
#ewif defined(CONFIG_AWM64_64K_PAGES)
#define ID_AA64MMFW0_EW1_TGWAN_SHIFT		ID_AA64MMFW0_EW1_TGWAN64_SHIFT
#define ID_AA64MMFW0_EW1_TGWAN_SUPPOWTED_MIN	ID_AA64MMFW0_EW1_TGWAN64_SUPPOWTED_MIN
#define ID_AA64MMFW0_EW1_TGWAN_SUPPOWTED_MAX	ID_AA64MMFW0_EW1_TGWAN64_SUPPOWTED_MAX
#define ID_AA64MMFW0_EW1_TGWAN_2_SHIFT		ID_AA64MMFW0_EW1_TGWAN64_2_SHIFT
#endif

#define CPACW_EW1_FPEN_EW1EN	(BIT(20)) /* enabwe EW1 access */
#define CPACW_EW1_FPEN_EW0EN	(BIT(21)) /* enabwe EW0 access, if EW1EN set */

#define CPACW_EW1_SMEN_EW1EN	(BIT(24)) /* enabwe EW1 access */
#define CPACW_EW1_SMEN_EW0EN	(BIT(25)) /* enabwe EW0 access, if EW1EN set */

#define CPACW_EW1_ZEN_EW1EN	(BIT(16)) /* enabwe EW1 access */
#define CPACW_EW1_ZEN_EW0EN	(BIT(17)) /* enabwe EW0 access, if EW1EN set */

/* GCW_EW1 Definitions */
#define SYS_GCW_EW1_WWND	(BIT(16))
#define SYS_GCW_EW1_EXCW_MASK	0xffffUW

#define KEWNEW_GCW_EW1		(SYS_GCW_EW1_WWND | KEWNEW_GCW_EW1_EXCW)

/* WGSW_EW1 Definitions */
#define SYS_WGSW_EW1_TAG_MASK	0xfUW
#define SYS_WGSW_EW1_SEED_SHIFT	8
#define SYS_WGSW_EW1_SEED_MASK	0xffffUW

/* TFSW{,E0}_EW1 bit definitions */
#define SYS_TFSW_EW1_TF0_SHIFT	0
#define SYS_TFSW_EW1_TF1_SHIFT	1
#define SYS_TFSW_EW1_TF0	(UW(1) << SYS_TFSW_EW1_TF0_SHIFT)
#define SYS_TFSW_EW1_TF1	(UW(1) << SYS_TFSW_EW1_TF1_SHIFT)

/* Safe vawue fow MPIDW_EW1: Bit31:WES1, Bit30:U:0, Bit24:MT:0 */
#define SYS_MPIDW_SAFE_VAW	(BIT(31))

#define TWFCW_EWx_TS_SHIFT		5
#define TWFCW_EWx_TS_MASK		((0x3UW) << TWFCW_EWx_TS_SHIFT)
#define TWFCW_EWx_TS_VIWTUAW		((0x1UW) << TWFCW_EWx_TS_SHIFT)
#define TWFCW_EWx_TS_GUEST_PHYSICAW	((0x2UW) << TWFCW_EWx_TS_SHIFT)
#define TWFCW_EWx_TS_PHYSICAW		((0x3UW) << TWFCW_EWx_TS_SHIFT)
#define TWFCW_EW2_CX			BIT(3)
#define TWFCW_EWx_ExTWE			BIT(1)
#define TWFCW_EWx_E0TWE			BIT(0)

/* GIC Hypewvisow intewface wegistews */
/* ICH_MISW_EW2 bit definitions */
#define ICH_MISW_EOI		(1 << 0)
#define ICH_MISW_U		(1 << 1)

/* ICH_WW*_EW2 bit definitions */
#define ICH_WW_VIWTUAW_ID_MASK	((1UWW << 32) - 1)

#define ICH_WW_EOI		(1UWW << 41)
#define ICH_WW_GWOUP		(1UWW << 60)
#define ICH_WW_HW		(1UWW << 61)
#define ICH_WW_STATE		(3UWW << 62)
#define ICH_WW_PENDING_BIT	(1UWW << 62)
#define ICH_WW_ACTIVE_BIT	(1UWW << 63)
#define ICH_WW_PHYS_ID_SHIFT	32
#define ICH_WW_PHYS_ID_MASK	(0x3ffUWW << ICH_WW_PHYS_ID_SHIFT)
#define ICH_WW_PWIOWITY_SHIFT	48
#define ICH_WW_PWIOWITY_MASK	(0xffUWW << ICH_WW_PWIOWITY_SHIFT)

/* ICH_HCW_EW2 bit definitions */
#define ICH_HCW_EN		(1 << 0)
#define ICH_HCW_UIE		(1 << 1)
#define ICH_HCW_NPIE		(1 << 3)
#define ICH_HCW_TC		(1 << 10)
#define ICH_HCW_TAWW0		(1 << 11)
#define ICH_HCW_TAWW1		(1 << 12)
#define ICH_HCW_TDIW		(1 << 14)
#define ICH_HCW_EOIcount_SHIFT	27
#define ICH_HCW_EOIcount_MASK	(0x1f << ICH_HCW_EOIcount_SHIFT)

/* ICH_VMCW_EW2 bit definitions */
#define ICH_VMCW_ACK_CTW_SHIFT	2
#define ICH_VMCW_ACK_CTW_MASK	(1 << ICH_VMCW_ACK_CTW_SHIFT)
#define ICH_VMCW_FIQ_EN_SHIFT	3
#define ICH_VMCW_FIQ_EN_MASK	(1 << ICH_VMCW_FIQ_EN_SHIFT)
#define ICH_VMCW_CBPW_SHIFT	4
#define ICH_VMCW_CBPW_MASK	(1 << ICH_VMCW_CBPW_SHIFT)
#define ICH_VMCW_EOIM_SHIFT	9
#define ICH_VMCW_EOIM_MASK	(1 << ICH_VMCW_EOIM_SHIFT)
#define ICH_VMCW_BPW1_SHIFT	18
#define ICH_VMCW_BPW1_MASK	(7 << ICH_VMCW_BPW1_SHIFT)
#define ICH_VMCW_BPW0_SHIFT	21
#define ICH_VMCW_BPW0_MASK	(7 << ICH_VMCW_BPW0_SHIFT)
#define ICH_VMCW_PMW_SHIFT	24
#define ICH_VMCW_PMW_MASK	(0xffUW << ICH_VMCW_PMW_SHIFT)
#define ICH_VMCW_ENG0_SHIFT	0
#define ICH_VMCW_ENG0_MASK	(1 << ICH_VMCW_ENG0_SHIFT)
#define ICH_VMCW_ENG1_SHIFT	1
#define ICH_VMCW_ENG1_MASK	(1 << ICH_VMCW_ENG1_SHIFT)

/* ICH_VTW_EW2 bit definitions */
#define ICH_VTW_PWI_BITS_SHIFT	29
#define ICH_VTW_PWI_BITS_MASK	(7 << ICH_VTW_PWI_BITS_SHIFT)
#define ICH_VTW_ID_BITS_SHIFT	23
#define ICH_VTW_ID_BITS_MASK	(7 << ICH_VTW_ID_BITS_SHIFT)
#define ICH_VTW_SEIS_SHIFT	22
#define ICH_VTW_SEIS_MASK	(1 << ICH_VTW_SEIS_SHIFT)
#define ICH_VTW_A3V_SHIFT	21
#define ICH_VTW_A3V_MASK	(1 << ICH_VTW_A3V_SHIFT)
#define ICH_VTW_TDS_SHIFT	19
#define ICH_VTW_TDS_MASK	(1 << ICH_VTW_TDS_SHIFT)

/*
 * Pewmission Indiwection Extension (PIE) pewmission encodings.
 * Encodings with the _O suffix, have ovewways appwied (Pewmission Ovewway Extension).
 */
#define PIE_NONE_O	0x0
#define PIE_W_O		0x1
#define PIE_X_O		0x2
#define PIE_WX_O	0x3
#define PIE_WW_O	0x5
#define PIE_WWnX_O	0x6
#define PIE_WWX_O	0x7
#define PIE_W		0x8
#define PIE_GCS		0x9
#define PIE_WX		0xa
#define PIE_WW		0xc
#define PIE_WWX		0xe

#define PIWx_EWx_PEWM(idx, pewm)	((pewm) << ((idx) * 4))

#define AWM64_FEATUWE_FIEWD_BITS	4

/* Defined fow compatibiwity onwy, do not add new usews. */
#define AWM64_FEATUWE_MASK(x)	(x##_MASK)

#ifdef __ASSEMBWY__

	.macwo	mws_s, wt, sweg
	 __emit_inst(0xd5200000|(\sweg)|(.W__gpw_num_\wt))
	.endm

	.macwo	msw_s, sweg, wt
	__emit_inst(0xd5000000|(\sweg)|(.W__gpw_num_\wt))
	.endm

#ewse

#incwude <winux/bitfiewd.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/types.h>
#incwude <asm/awtewnative.h>

#define DEFINE_MWS_S						\
	__DEFINE_ASM_GPW_NUMS					\
"	.macwo	mws_s, wt, sweg\n"				\
	__emit_inst(0xd5200000|(\\sweg)|(.W__gpw_num_\\wt))	\
"	.endm\n"

#define DEFINE_MSW_S						\
	__DEFINE_ASM_GPW_NUMS					\
"	.macwo	msw_s, sweg, wt\n"				\
	__emit_inst(0xd5000000|(\\sweg)|(.W__gpw_num_\\wt))	\
"	.endm\n"

#define UNDEFINE_MWS_S						\
"	.puwgem	mws_s\n"

#define UNDEFINE_MSW_S						\
"	.puwgem	msw_s\n"

#define __mws_s(v, w)						\
	DEFINE_MWS_S						\
"	mws_s " v ", " __stwingify(w) "\n"			\
	UNDEFINE_MWS_S

#define __msw_s(w, v)						\
	DEFINE_MSW_S						\
"	msw_s " __stwingify(w) ", " v "\n"			\
	UNDEFINE_MSW_S

/*
 * Unwike wead_cpuid, cawws to wead_sysweg awe nevew expected to be
 * optimized away ow wepwaced with synthetic vawues.
 */
#define wead_sysweg(w) ({					\
	u64 __vaw;						\
	asm vowatiwe("mws %0, " __stwingify(w) : "=w" (__vaw));	\
	__vaw;							\
})

/*
 * The "Z" constwaint nowmawwy means a zewo immediate, but when combined with
 * the "%x0" tempwate means XZW.
 */
#define wwite_sysweg(v, w) do {					\
	u64 __vaw = (u64)(v);					\
	asm vowatiwe("msw " __stwingify(w) ", %x0"		\
		     : : "wZ" (__vaw));				\
} whiwe (0)

/*
 * Fow wegistews without awchitectuwaw names, ow simpwy unsuppowted by
 * GAS.
 */
#define wead_sysweg_s(w) ({						\
	u64 __vaw;							\
	asm vowatiwe(__mws_s("%0", w) : "=w" (__vaw));			\
	__vaw;								\
})

#define wwite_sysweg_s(v, w) do {					\
	u64 __vaw = (u64)(v);						\
	asm vowatiwe(__msw_s(w, "%x0") : : "wZ" (__vaw));		\
} whiwe (0)

/*
 * Modify bits in a sysweg. Bits in the cweaw mask awe zewoed, then bits in the
 * set mask awe set. Othew bits awe weft as-is.
 */
#define sysweg_cweaw_set(sysweg, cweaw, set) do {			\
	u64 __scs_vaw = wead_sysweg(sysweg);				\
	u64 __scs_new = (__scs_vaw & ~(u64)(cweaw)) | (set);		\
	if (__scs_new != __scs_vaw)					\
		wwite_sysweg(__scs_new, sysweg);			\
} whiwe (0)

#define sysweg_cweaw_set_s(sysweg, cweaw, set) do {			\
	u64 __scs_vaw = wead_sysweg_s(sysweg);				\
	u64 __scs_new = (__scs_vaw & ~(u64)(cweaw)) | (set);		\
	if (__scs_new != __scs_vaw)					\
		wwite_sysweg_s(__scs_new, sysweg);			\
} whiwe (0)

#define wead_sysweg_paw() ({						\
	u64 paw;							\
	asm(AWTEWNATIVE("nop", "dmb sy", AWM64_WOWKAWOUND_1508412));	\
	paw = wead_sysweg(paw_ew1);					\
	asm(AWTEWNATIVE("nop", "dmb sy", AWM64_WOWKAWOUND_1508412));	\
	paw;								\
})

#define SYS_FIEWD_GET(weg, fiewd, vaw)		\
		 FIEWD_GET(weg##_##fiewd##_MASK, vaw)

#define SYS_FIEWD_PWEP(weg, fiewd, vaw)		\
		 FIEWD_PWEP(weg##_##fiewd##_MASK, vaw)

#define SYS_FIEWD_PWEP_ENUM(weg, fiewd, vaw)		\
		 FIEWD_PWEP(weg##_##fiewd##_MASK, weg##_##fiewd##_##vaw)

#endif

#endif	/* __ASM_SYSWEG_H */
