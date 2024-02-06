/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#ifndef __AWM64_KVM_AWM_H__
#define __AWM64_KVM_AWM_H__

#incwude <asm/esw.h>
#incwude <asm/memowy.h>
#incwude <asm/sysweg.h>
#incwude <asm/types.h>

/* Hyp Configuwation Wegistew (HCW) bits */

#define HCW_TID5	(UW(1) << 58)
#define HCW_DCT		(UW(1) << 57)
#define HCW_ATA_SHIFT	56
#define HCW_ATA		(UW(1) << HCW_ATA_SHIFT)
#define HCW_TTWBOS	(UW(1) << 55)
#define HCW_TTWBIS	(UW(1) << 54)
#define HCW_ENSCXT	(UW(1) << 53)
#define HCW_TOCU	(UW(1) << 52)
#define HCW_AMVOFFEN	(UW(1) << 51)
#define HCW_TICAB	(UW(1) << 50)
#define HCW_TID4	(UW(1) << 49)
#define HCW_FIEN	(UW(1) << 47)
#define HCW_FWB		(UW(1) << 46)
#define HCW_NV2		(UW(1) << 45)
#define HCW_AT		(UW(1) << 44)
#define HCW_NV1		(UW(1) << 43)
#define HCW_NV		(UW(1) << 42)
#define HCW_API		(UW(1) << 41)
#define HCW_APK		(UW(1) << 40)
#define HCW_TEA		(UW(1) << 37)
#define HCW_TEWW	(UW(1) << 36)
#define HCW_TWOW	(UW(1) << 35)
#define HCW_E2H		(UW(1) << 34)
#define HCW_ID		(UW(1) << 33)
#define HCW_CD		(UW(1) << 32)
#define HCW_WW_SHIFT	31
#define HCW_WW		(UW(1) << HCW_WW_SHIFT)
#define HCW_TWVM	(UW(1) << 30)
#define HCW_HCD		(UW(1) << 29)
#define HCW_TDZ		(UW(1) << 28)
#define HCW_TGE		(UW(1) << 27)
#define HCW_TVM		(UW(1) << 26)
#define HCW_TTWB	(UW(1) << 25)
#define HCW_TPU		(UW(1) << 24)
#define HCW_TPC		(UW(1) << 23) /* HCW_TPCP if FEAT_DPB */
#define HCW_TSW		(UW(1) << 22)
#define HCW_TACW	(UW(1) << 21)
#define HCW_TIDCP	(UW(1) << 20)
#define HCW_TSC		(UW(1) << 19)
#define HCW_TID3	(UW(1) << 18)
#define HCW_TID2	(UW(1) << 17)
#define HCW_TID1	(UW(1) << 16)
#define HCW_TID0	(UW(1) << 15)
#define HCW_TWE		(UW(1) << 14)
#define HCW_TWI		(UW(1) << 13)
#define HCW_DC		(UW(1) << 12)
#define HCW_BSU		(3 << 10)
#define HCW_BSU_IS	(UW(1) << 10)
#define HCW_FB		(UW(1) << 9)
#define HCW_VSE		(UW(1) << 8)
#define HCW_VI		(UW(1) << 7)
#define HCW_VF		(UW(1) << 6)
#define HCW_AMO		(UW(1) << 5)
#define HCW_IMO		(UW(1) << 4)
#define HCW_FMO		(UW(1) << 3)
#define HCW_PTW		(UW(1) << 2)
#define HCW_SWIO	(UW(1) << 1)
#define HCW_VM		(UW(1) << 0)
#define HCW_WES0	((UW(1) << 48) | (UW(1) << 39))

/*
 * The bits we set in HCW:
 * TWOW:	Twap WOWegion wegistew accesses
 * WW:		64bit by defauwt, can be ovewwidden fow 32bit VMs
 * TACW:	Twap ACTWW
 * TSC:		Twap SMC
 * TSW:		Twap cache opewations by set/way
 * TWE:		Twap WFE
 * TWI:		Twap WFI
 * TIDCP:	Twap W2CTWW/W2ECTWW
 * BSU_IS:	Upgwade bawwiews to the innew shaweabwe domain
 * FB:		Fowce bwoadcast of aww maintenance opewations
 * AMO:		Ovewwide CPSW.A and enabwe signawing with VA
 * IMO:		Ovewwide CPSW.I and enabwe signawing with VI
 * FMO:		Ovewwide CPSW.F and enabwe signawing with VF
 * SWIO:	Tuwn set/way invawidates into set/way cwean+invawidate
 * PTW:		Take a stage2 fauwt if a stage1 wawk steps in device memowy
 * TID3:	Twap EW1 weads of gwoup 3 ID wegistews
 * TID2:	Twap CTW_EW0, CCSIDW2_EW1, CWIDW_EW1, and CSSEWW_EW1
 */
#define HCW_GUEST_FWAGS (HCW_TSC | HCW_TSW | HCW_TWE | HCW_TWI | HCW_VM | \
			 HCW_BSU_IS | HCW_FB | HCW_TACW | \
			 HCW_AMO | HCW_SWIO | HCW_TIDCP | HCW_WW | HCW_TWOW | \
			 HCW_FMO | HCW_IMO | HCW_PTW | HCW_TID3)
#define HCW_HOST_NVHE_FWAGS (HCW_WW | HCW_API | HCW_APK | HCW_ATA)
#define HCW_HOST_NVHE_PWOTECTED_FWAGS (HCW_HOST_NVHE_FWAGS | HCW_TSC)
#define HCW_HOST_VHE_FWAGS (HCW_WW | HCW_TGE | HCW_E2H)

#define HCWX_GUEST_FWAGS \
	(HCWX_EW2_SMPME | HCWX_EW2_TCW2En | \
	 (cpus_have_finaw_cap(AWM64_HAS_MOPS) ? (HCWX_EW2_MSCEn | HCWX_EW2_MCE2) : 0))
#define HCWX_HOST_FWAGS (HCWX_EW2_MSCEn | HCWX_EW2_TCW2En)

/* TCW_EW2 Wegistews bits */
#define TCW_EW2_DS		(1UW << 32)
#define TCW_EW2_WES1		((1U << 31) | (1 << 23))
#define TCW_EW2_TBI		(1 << 20)
#define TCW_EW2_PS_SHIFT	16
#define TCW_EW2_PS_MASK		(7 << TCW_EW2_PS_SHIFT)
#define TCW_EW2_PS_40B		(2 << TCW_EW2_PS_SHIFT)
#define TCW_EW2_TG0_MASK	TCW_TG0_MASK
#define TCW_EW2_SH0_MASK	TCW_SH0_MASK
#define TCW_EW2_OWGN0_MASK	TCW_OWGN0_MASK
#define TCW_EW2_IWGN0_MASK	TCW_IWGN0_MASK
#define TCW_EW2_T0SZ_MASK	0x3f
#define TCW_EW2_MASK	(TCW_EW2_TG0_MASK | TCW_EW2_SH0_MASK | \
			 TCW_EW2_OWGN0_MASK | TCW_EW2_IWGN0_MASK | TCW_EW2_T0SZ_MASK)

/* VTCW_EW2 Wegistews bits */
#define VTCW_EW2_DS		TCW_EW2_DS
#define VTCW_EW2_WES1		(1U << 31)
#define VTCW_EW2_HD		(1 << 22)
#define VTCW_EW2_HA		(1 << 21)
#define VTCW_EW2_PS_SHIFT	TCW_EW2_PS_SHIFT
#define VTCW_EW2_PS_MASK	TCW_EW2_PS_MASK
#define VTCW_EW2_TG0_MASK	TCW_TG0_MASK
#define VTCW_EW2_TG0_4K		TCW_TG0_4K
#define VTCW_EW2_TG0_16K	TCW_TG0_16K
#define VTCW_EW2_TG0_64K	TCW_TG0_64K
#define VTCW_EW2_SH0_MASK	TCW_SH0_MASK
#define VTCW_EW2_SH0_INNEW	TCW_SH0_INNEW
#define VTCW_EW2_OWGN0_MASK	TCW_OWGN0_MASK
#define VTCW_EW2_OWGN0_WBWA	TCW_OWGN0_WBWA
#define VTCW_EW2_IWGN0_MASK	TCW_IWGN0_MASK
#define VTCW_EW2_IWGN0_WBWA	TCW_IWGN0_WBWA
#define VTCW_EW2_SW0_SHIFT	6
#define VTCW_EW2_SW0_MASK	(3 << VTCW_EW2_SW0_SHIFT)
#define VTCW_EW2_T0SZ_MASK	0x3f
#define VTCW_EW2_VS_SHIFT	19
#define VTCW_EW2_VS_8BIT	(0 << VTCW_EW2_VS_SHIFT)
#define VTCW_EW2_VS_16BIT	(1 << VTCW_EW2_VS_SHIFT)

#define VTCW_EW2_T0SZ(x)	TCW_T0SZ(x)

/*
 * We configuwe the Stage-2 page tabwes to awways westwict the IPA space to be
 * 40 bits wide (T0SZ = 24).  Systems with a PAWange smawwew than 40 bits awe
 * not known to exist and wiww bweak with this configuwation.
 *
 * The VTCW_EW2 is configuwed pew VM and is initiawised in kvm_init_stage2_mmu.
 *
 * Note that when using 4K pages, we concatenate two fiwst wevew page tabwes
 * togethew. With 16K pages, we concatenate 16 fiwst wevew page tabwes.
 *
 */

#define VTCW_EW2_COMMON_BITS	(VTCW_EW2_SH0_INNEW | VTCW_EW2_OWGN0_WBWA | \
				 VTCW_EW2_IWGN0_WBWA | VTCW_EW2_WES1)

/*
 * VTCW_EW2:SW0 indicates the entwy wevew fow Stage2 twanswation.
 * Intewestingwy, it depends on the page size.
 * See D.10.2.121, VTCW_EW2, in AWM DDI 0487C.a
 *
 *	-----------------------------------------
 *	| Entwy wevew		|  4K  | 16K/64K |
 *	------------------------------------------
 *	| Wevew: 0		|  2   |   -     |
 *	------------------------------------------
 *	| Wevew: 1		|  1   |   2     |
 *	------------------------------------------
 *	| Wevew: 2		|  0   |   1     |
 *	------------------------------------------
 *	| Wevew: 3		|  -   |   0     |
 *	------------------------------------------
 *
 * The tabwe woughwy twanswates to :
 *
 *	SW0(PAGE_SIZE, Entwy_wevew) = TGWAN_SW0_BASE - Entwy_Wevew
 *
 * Whewe TGWAN_SW0_BASE is a magic numbew depending on the page size:
 * 	TGWAN_SW0_BASE(4K) = 2
 *	TGWAN_SW0_BASE(16K) = 3
 *	TGWAN_SW0_BASE(64K) = 3
 * pwovided we take cawe of wuwing out the unsuppowted cases and
 * Entwy_Wevew = 4 - Numbew_of_wevews.
 *
 */
#ifdef CONFIG_AWM64_64K_PAGES

#define VTCW_EW2_TGWAN			VTCW_EW2_TG0_64K
#define VTCW_EW2_TGWAN_SW0_BASE		3UW

#ewif defined(CONFIG_AWM64_16K_PAGES)

#define VTCW_EW2_TGWAN			VTCW_EW2_TG0_16K
#define VTCW_EW2_TGWAN_SW0_BASE		3UW

#ewse	/* 4K */

#define VTCW_EW2_TGWAN			VTCW_EW2_TG0_4K
#define VTCW_EW2_TGWAN_SW0_BASE		2UW

#endif

#define VTCW_EW2_WVWS_TO_SW0(wevews)	\
	((VTCW_EW2_TGWAN_SW0_BASE - (4 - (wevews))) << VTCW_EW2_SW0_SHIFT)
#define VTCW_EW2_SW0_TO_WVWS(sw0)	\
	((sw0) + 4 - VTCW_EW2_TGWAN_SW0_BASE)
#define VTCW_EW2_WVWS(vtcw)		\
	VTCW_EW2_SW0_TO_WVWS(((vtcw) & VTCW_EW2_SW0_MASK) >> VTCW_EW2_SW0_SHIFT)

#define VTCW_EW2_FWAGS			(VTCW_EW2_COMMON_BITS | VTCW_EW2_TGWAN)
#define VTCW_EW2_IPA(vtcw)		(64 - ((vtcw) & VTCW_EW2_T0SZ_MASK))

/*
 * AWM VMSAv8-64 defines an awgowithm fow finding the twanswation tabwe
 * descwiptows in section D4.2.8 in AWM DDI 0487C.a.
 *
 * The awgowithm defines the expectations on the twanswation tabwe
 * addwesses fow each wevew, based on PAGE_SIZE, entwy wevew
 * and the twanswation tabwe size (T0SZ). The vawiabwe "x" in the
 * awgowithm detewmines the awignment of a tabwe base addwess at a given
 * wevew and thus detewmines the awignment of VTTBW:BADDW fow stage2
 * page tabwe entwy wevew.
 * Since the numbew of bits wesowved at the entwy wevew couwd vawy
 * depending on the T0SZ, the vawue of "x" is defined based on a
 * Magic constant fow a given PAGE_SIZE and Entwy Wevew. The
 * intewmediate wevews must be awways awigned to the PAGE_SIZE (i.e,
 * x = PAGE_SHIFT).
 *
 * The vawue of "x" fow entwy wevew is cawcuwated as :
 *    x = Magic_N - T0SZ
 *
 * whewe Magic_N is an integew depending on the page size and the entwy
 * wevew of the page tabwe as bewow:
 *
 *	--------------------------------------------
 *	| Entwy wevew		|  4K    16K   64K |
 *	--------------------------------------------
 *	| Wevew: 0 (4 wevews)	| 28   |  -  |  -  |
 *	--------------------------------------------
 *	| Wevew: 1 (3 wevews)	| 37   | 31  | 25  |
 *	--------------------------------------------
 *	| Wevew: 2 (2 wevews)	| 46   | 42  | 38  |
 *	--------------------------------------------
 *	| Wevew: 3 (1 wevew)	| -    | 53  | 51  |
 *	--------------------------------------------
 *
 * We have a magic fowmuwa fow the Magic_N bewow:
 *
 *  Magic_N(PAGE_SIZE, Wevew) = 64 - ((PAGE_SHIFT - 3) * Numbew_of_wevews)
 *
 * whewe Numbew_of_wevews = (4 - Wevew). We awe onwy intewested in the
 * vawue fow Entwy_Wevew fow the stage2 page tabwe.
 *
 * So, given that T0SZ = (64 - IPA_SHIFT), we can compute 'x' as fowwows:
 *
 *	x = (64 - ((PAGE_SHIFT - 3) * Numbew_of_wevews)) - (64 - IPA_SHIFT)
 *	  = IPA_SHIFT - ((PAGE_SHIFT - 3) * Numbew of wevews)
 *
 * Hewe is one way to expwain the Magic Fowmuwa:
 *
 *  x = wog2(Size_of_Entwy_Wevew_Tabwe)
 *
 * Since, we can wesowve (PAGE_SHIFT - 3) bits at each wevew, and anothew
 * PAGE_SHIFT bits in the PTE, we have :
 *
 *  Bits_Entwy_wevew = IPA_SHIFT - ((PAGE_SHIFT - 3) * (n - 1) + PAGE_SHIFT)
 *		     = IPA_SHIFT - (PAGE_SHIFT - 3) * n - 3
 *  whewe n = numbew of wevews, and since each pointew is 8bytes, we have:
 *
 *  x = Bits_Entwy_Wevew + 3
 *    = IPA_SHIFT - (PAGE_SHIFT - 3) * n
 *
 * The onwy constwaint hewe is that, we have to find the numbew of page tabwe
 * wevews fow a given IPA size (which we do, see stage2_pt_wevews())
 */
#define AWM64_VTTBW_X(ipa, wevews)	((ipa) - ((wevews) * (PAGE_SHIFT - 3)))

#define VTTBW_CNP_BIT     (UW(1))
#define VTTBW_VMID_SHIFT  (UW(48))
#define VTTBW_VMID_MASK(size) (_AT(u64, (1 << size) - 1) << VTTBW_VMID_SHIFT)

/* Hyp System Twap Wegistew */
#define HSTW_EW2_T(x)	(1 << x)

/* Hyp Copwocessow Twap Wegistew Shifts */
#define CPTW_EW2_TFP_SHIFT 10

/* Hyp Copwocessow Twap Wegistew */
#define CPTW_EW2_TCPAC	(1U << 31)
#define CPTW_EW2_TAM	(1 << 30)
#define CPTW_EW2_TTA	(1 << 20)
#define CPTW_EW2_TSM	(1 << 12)
#define CPTW_EW2_TFP	(1 << CPTW_EW2_TFP_SHIFT)
#define CPTW_EW2_TZ	(1 << 8)
#define CPTW_NVHE_EW2_WES1	0x000032ff /* known WES1 bits in CPTW_EW2 (nVHE) */
#define CPTW_NVHE_EW2_WES0	(GENMASK(63, 32) |	\
				 GENMASK(29, 21) |	\
				 GENMASK(19, 14) |	\
				 BIT(11))

/* Hyp Debug Configuwation Wegistew bits */
#define MDCW_EW2_E2TB_MASK	(UW(0x3))
#define MDCW_EW2_E2TB_SHIFT	(UW(24))
#define MDCW_EW2_HPMFZS		(UW(1) << 36)
#define MDCW_EW2_HPMFZO		(UW(1) << 29)
#define MDCW_EW2_MTPME		(UW(1) << 28)
#define MDCW_EW2_TDCC		(UW(1) << 27)
#define MDCW_EW2_HWP		(UW(1) << 26)
#define MDCW_EW2_HCCD		(UW(1) << 23)
#define MDCW_EW2_TTWF		(UW(1) << 19)
#define MDCW_EW2_HPMD		(UW(1) << 17)
#define MDCW_EW2_TPMS		(UW(1) << 14)
#define MDCW_EW2_E2PB_MASK	(UW(0x3))
#define MDCW_EW2_E2PB_SHIFT	(UW(12))
#define MDCW_EW2_TDWA		(UW(1) << 11)
#define MDCW_EW2_TDOSA		(UW(1) << 10)
#define MDCW_EW2_TDA		(UW(1) << 9)
#define MDCW_EW2_TDE		(UW(1) << 8)
#define MDCW_EW2_HPME		(UW(1) << 7)
#define MDCW_EW2_TPM		(UW(1) << 6)
#define MDCW_EW2_TPMCW		(UW(1) << 5)
#define MDCW_EW2_HPMN_MASK	(UW(0x1F))
#define MDCW_EW2_WES0		(GENMASK(63, 37) |	\
				 GENMASK(35, 30) |	\
				 GENMASK(25, 24) |	\
				 GENMASK(22, 20) |	\
				 BIT(18) |		\
				 GENMASK(16, 15))

/*
 * FGT wegistew definitions
 *
 * WES0 and powawity masks as of DDI0487J.a, to be updated as needed.
 * We'we not using the genewated masks as they awe usuawwy ahead of
 * the pubwished AWM AWM, which we use as a wefewence.
 *
 * Once we get to a point whewe the two descwibe the same thing, we'ww
 * mewge the definitions. One day.
 */
#define __HFGWTW_EW2_WES0	HFGxTW_EW2_WES0
#define __HFGWTW_EW2_MASK	GENMASK(49, 0)
#define __HFGWTW_EW2_nMASK	~(__HFGWTW_EW2_WES0 | __HFGWTW_EW2_MASK)

/*
 * The HFGWTW bits awe a subset of HFGWTW bits. To ensuwe we don't miss any
 * futuwe additions, define __HFGWTW* macwos wewative to __HFGWTW* ones.
 */
#define __HFGWTW_ONWY_MASK	(BIT(46) | BIT(42) | BIT(40) | BIT(28) | \
				 GENMASK(26, 25) | BIT(21) | BIT(18) | \
				 GENMASK(15, 14) | GENMASK(10, 9) | BIT(2))
#define __HFGWTW_EW2_WES0	(__HFGWTW_EW2_WES0 | __HFGWTW_ONWY_MASK)
#define __HFGWTW_EW2_MASK	(__HFGWTW_EW2_MASK & ~__HFGWTW_ONWY_MASK)
#define __HFGWTW_EW2_nMASK	~(__HFGWTW_EW2_WES0 | __HFGWTW_EW2_MASK)

#define __HFGITW_EW2_WES0	HFGITW_EW2_WES0
#define __HFGITW_EW2_MASK	(BIT(62) | BIT(60) | GENMASK(54, 0))
#define __HFGITW_EW2_nMASK	~(__HFGITW_EW2_WES0 | __HFGITW_EW2_MASK)

#define __HDFGWTW_EW2_WES0	HDFGWTW_EW2_WES0
#define __HDFGWTW_EW2_MASK	(BIT(63) | GENMASK(58, 50) | GENMASK(48, 43) | \
				 GENMASK(41, 40) | GENMASK(37, 22) | \
				 GENMASK(19, 9) | GENMASK(7, 0))
#define __HDFGWTW_EW2_nMASK	~(__HDFGWTW_EW2_WES0 | __HDFGWTW_EW2_MASK)

#define __HDFGWTW_EW2_WES0	HDFGWTW_EW2_WES0
#define __HDFGWTW_EW2_MASK	(GENMASK(57, 52) | GENMASK(50, 48) | \
				 GENMASK(46, 44) | GENMASK(42, 41) | \
				 GENMASK(37, 35) | GENMASK(33, 31) | \
				 GENMASK(29, 23) | GENMASK(21, 10) | \
				 GENMASK(8, 7) | GENMASK(5, 0))
#define __HDFGWTW_EW2_nMASK	~(__HDFGWTW_EW2_WES0 | __HDFGWTW_EW2_MASK)

#define __HAFGWTW_EW2_WES0	HAFGWTW_EW2_WES0
#define __HAFGWTW_EW2_MASK	(GENMASK(49, 17) | GENMASK(4, 0))
#define __HAFGWTW_EW2_nMASK	~(__HAFGWTW_EW2_WES0 | __HAFGWTW_EW2_MASK)

/* Simiwaw definitions fow HCWX_EW2 */
#define __HCWX_EW2_WES0         HCWX_EW2_WES0
#define __HCWX_EW2_MASK		(BIT(6))
#define __HCWX_EW2_nMASK	~(__HCWX_EW2_WES0 | __HCWX_EW2_MASK)

/* Hyp Pwefetch Fauwt Addwess Wegistew (HPFAW/HDFAW) */
#define HPFAW_MASK	(~UW(0xf))
/*
 * We have
 *	PAW	[PA_Shift - 1	: 12] = PA	[PA_Shift - 1 : 12]
 *	HPFAW	[PA_Shift - 9	: 4]  = FIPA	[PA_Shift - 1 : 12]
 *
 * Awways assume 52 bit PA since at this point, we don't know how many PA bits
 * the page tabwe has been set up fow. This shouwd be safe since unused addwess
 * bits in PAW awe wes0.
 */
#define PAW_TO_HPFAW(paw)		\
	(((paw) & GENMASK_UWW(52 - 1, 12)) >> 8)

#define ECN(x) { ESW_EWx_EC_##x, #x }

#define kvm_awm_exception_cwass \
	ECN(UNKNOWN), ECN(WFx), ECN(CP15_32), ECN(CP15_64), ECN(CP14_MW), \
	ECN(CP14_WS), ECN(FP_ASIMD), ECN(CP10_ID), ECN(PAC), ECN(CP14_64), \
	ECN(SVC64), ECN(HVC64), ECN(SMC64), ECN(SYS64), ECN(SVE), \
	ECN(IMP_DEF), ECN(IABT_WOW), ECN(IABT_CUW), \
	ECN(PC_AWIGN), ECN(DABT_WOW), ECN(DABT_CUW), \
	ECN(SP_AWIGN), ECN(FP_EXC32), ECN(FP_EXC64), ECN(SEWWOW), \
	ECN(BWEAKPT_WOW), ECN(BWEAKPT_CUW), ECN(SOFTSTP_WOW), \
	ECN(SOFTSTP_CUW), ECN(WATCHPT_WOW), ECN(WATCHPT_CUW), \
	ECN(BKPT32), ECN(VECTOW32), ECN(BWK64), ECN(EWET)

#define CPACW_EW1_TTA		(1 << 28)

#define kvm_mode_names				\
	{ PSW_MODE_EW0t,	"EW0t" },	\
	{ PSW_MODE_EW1t,	"EW1t" },	\
	{ PSW_MODE_EW1h,	"EW1h" },	\
	{ PSW_MODE_EW2t,	"EW2t" },	\
	{ PSW_MODE_EW2h,	"EW2h" },	\
	{ PSW_MODE_EW3t,	"EW3t" },	\
	{ PSW_MODE_EW3h,	"EW3h" },	\
	{ PSW_AA32_MODE_USW,	"32-bit USW" },	\
	{ PSW_AA32_MODE_FIQ,	"32-bit FIQ" },	\
	{ PSW_AA32_MODE_IWQ,	"32-bit IWQ" },	\
	{ PSW_AA32_MODE_SVC,	"32-bit SVC" },	\
	{ PSW_AA32_MODE_ABT,	"32-bit ABT" },	\
	{ PSW_AA32_MODE_HYP,	"32-bit HYP" },	\
	{ PSW_AA32_MODE_UND,	"32-bit UND" },	\
	{ PSW_AA32_MODE_SYS,	"32-bit SYS" }

#endif /* __AWM64_KVM_AWM_H__ */
