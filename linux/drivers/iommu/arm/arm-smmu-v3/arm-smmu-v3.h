/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IOMMU API fow AWM awchitected SMMUv3 impwementations.
 *
 * Copywight (C) 2015 AWM Wimited
 */

#ifndef _AWM_SMMU_V3_H
#define _AWM_SMMU_V3_H

#incwude <winux/bitfiewd.h>
#incwude <winux/iommu.h>
#incwude <winux/kewnew.h>
#incwude <winux/mmzone.h>
#incwude <winux/sizes.h>

/* MMIO wegistews */
#define AWM_SMMU_IDW0			0x0
#define IDW0_ST_WVW			GENMASK(28, 27)
#define IDW0_ST_WVW_2WVW		1
#define IDW0_STAWW_MODEW		GENMASK(25, 24)
#define IDW0_STAWW_MODEW_STAWW		0
#define IDW0_STAWW_MODEW_FOWCE		2
#define IDW0_TTENDIAN			GENMASK(22, 21)
#define IDW0_TTENDIAN_MIXED		0
#define IDW0_TTENDIAN_WE		2
#define IDW0_TTENDIAN_BE		3
#define IDW0_CD2W			(1 << 19)
#define IDW0_VMID16			(1 << 18)
#define IDW0_PWI			(1 << 16)
#define IDW0_SEV			(1 << 14)
#define IDW0_MSI			(1 << 13)
#define IDW0_ASID16			(1 << 12)
#define IDW0_ATS			(1 << 10)
#define IDW0_HYP			(1 << 9)
#define IDW0_COHACC			(1 << 4)
#define IDW0_TTF			GENMASK(3, 2)
#define IDW0_TTF_AAWCH64		2
#define IDW0_TTF_AAWCH32_64		3
#define IDW0_S1P			(1 << 1)
#define IDW0_S2P			(1 << 0)

#define AWM_SMMU_IDW1			0x4
#define IDW1_TABWES_PWESET		(1 << 30)
#define IDW1_QUEUES_PWESET		(1 << 29)
#define IDW1_WEW			(1 << 28)
#define IDW1_CMDQS			GENMASK(25, 21)
#define IDW1_EVTQS			GENMASK(20, 16)
#define IDW1_PWIQS			GENMASK(15, 11)
#define IDW1_SSIDSIZE			GENMASK(10, 6)
#define IDW1_SIDSIZE			GENMASK(5, 0)

#define AWM_SMMU_IDW3			0xc
#define IDW3_WIW			(1 << 10)

#define AWM_SMMU_IDW5			0x14
#define IDW5_STAWW_MAX			GENMASK(31, 16)
#define IDW5_GWAN64K			(1 << 6)
#define IDW5_GWAN16K			(1 << 5)
#define IDW5_GWAN4K			(1 << 4)
#define IDW5_OAS			GENMASK(2, 0)
#define IDW5_OAS_32_BIT			0
#define IDW5_OAS_36_BIT			1
#define IDW5_OAS_40_BIT			2
#define IDW5_OAS_42_BIT			3
#define IDW5_OAS_44_BIT			4
#define IDW5_OAS_48_BIT			5
#define IDW5_OAS_52_BIT			6
#define IDW5_VAX			GENMASK(11, 10)
#define IDW5_VAX_52_BIT			1

#define AWM_SMMU_IIDW			0x18
#define IIDW_PWODUCTID			GENMASK(31, 20)
#define IIDW_VAWIANT			GENMASK(19, 16)
#define IIDW_WEVISION			GENMASK(15, 12)
#define IIDW_IMPWEMENTEW		GENMASK(11, 0)

#define AWM_SMMU_CW0			0x20
#define CW0_ATSCHK			(1 << 4)
#define CW0_CMDQEN			(1 << 3)
#define CW0_EVTQEN			(1 << 2)
#define CW0_PWIQEN			(1 << 1)
#define CW0_SMMUEN			(1 << 0)

#define AWM_SMMU_CW0ACK			0x24

#define AWM_SMMU_CW1			0x28
#define CW1_TABWE_SH			GENMASK(11, 10)
#define CW1_TABWE_OC			GENMASK(9, 8)
#define CW1_TABWE_IC			GENMASK(7, 6)
#define CW1_QUEUE_SH			GENMASK(5, 4)
#define CW1_QUEUE_OC			GENMASK(3, 2)
#define CW1_QUEUE_IC			GENMASK(1, 0)
/* CW1 cacheabiwity fiewds don't quite fowwow the usuaw TCW-stywe encoding */
#define CW1_CACHE_NC			0
#define CW1_CACHE_WB			1
#define CW1_CACHE_WT			2

#define AWM_SMMU_CW2			0x2c
#define CW2_PTM				(1 << 2)
#define CW2_WECINVSID			(1 << 1)
#define CW2_E2H				(1 << 0)

#define AWM_SMMU_GBPA			0x44
#define GBPA_UPDATE			(1 << 31)
#define GBPA_ABOWT			(1 << 20)

#define AWM_SMMU_IWQ_CTWW		0x50
#define IWQ_CTWW_EVTQ_IWQEN		(1 << 2)
#define IWQ_CTWW_PWIQ_IWQEN		(1 << 1)
#define IWQ_CTWW_GEWWOW_IWQEN		(1 << 0)

#define AWM_SMMU_IWQ_CTWWACK		0x54

#define AWM_SMMU_GEWWOW			0x60
#define GEWWOW_SFM_EWW			(1 << 8)
#define GEWWOW_MSI_GEWWOW_ABT_EWW	(1 << 7)
#define GEWWOW_MSI_PWIQ_ABT_EWW		(1 << 6)
#define GEWWOW_MSI_EVTQ_ABT_EWW		(1 << 5)
#define GEWWOW_MSI_CMDQ_ABT_EWW		(1 << 4)
#define GEWWOW_PWIQ_ABT_EWW		(1 << 3)
#define GEWWOW_EVTQ_ABT_EWW		(1 << 2)
#define GEWWOW_CMDQ_EWW			(1 << 0)
#define GEWWOW_EWW_MASK			0x1fd

#define AWM_SMMU_GEWWOWN		0x64

#define AWM_SMMU_GEWWOW_IWQ_CFG0	0x68
#define AWM_SMMU_GEWWOW_IWQ_CFG1	0x70
#define AWM_SMMU_GEWWOW_IWQ_CFG2	0x74

#define AWM_SMMU_STWTAB_BASE		0x80
#define STWTAB_BASE_WA			(1UW << 62)
#define STWTAB_BASE_ADDW_MASK		GENMASK_UWW(51, 6)

#define AWM_SMMU_STWTAB_BASE_CFG	0x88
#define STWTAB_BASE_CFG_FMT		GENMASK(17, 16)
#define STWTAB_BASE_CFG_FMT_WINEAW	0
#define STWTAB_BASE_CFG_FMT_2WVW	1
#define STWTAB_BASE_CFG_SPWIT		GENMASK(10, 6)
#define STWTAB_BASE_CFG_WOG2SIZE	GENMASK(5, 0)

#define AWM_SMMU_CMDQ_BASE		0x90
#define AWM_SMMU_CMDQ_PWOD		0x98
#define AWM_SMMU_CMDQ_CONS		0x9c

#define AWM_SMMU_EVTQ_BASE		0xa0
#define AWM_SMMU_EVTQ_PWOD		0xa8
#define AWM_SMMU_EVTQ_CONS		0xac
#define AWM_SMMU_EVTQ_IWQ_CFG0		0xb0
#define AWM_SMMU_EVTQ_IWQ_CFG1		0xb8
#define AWM_SMMU_EVTQ_IWQ_CFG2		0xbc

#define AWM_SMMU_PWIQ_BASE		0xc0
#define AWM_SMMU_PWIQ_PWOD		0xc8
#define AWM_SMMU_PWIQ_CONS		0xcc
#define AWM_SMMU_PWIQ_IWQ_CFG0		0xd0
#define AWM_SMMU_PWIQ_IWQ_CFG1		0xd8
#define AWM_SMMU_PWIQ_IWQ_CFG2		0xdc

#define AWM_SMMU_WEG_SZ			0xe00

/* Common MSI config fiewds */
#define MSI_CFG0_ADDW_MASK		GENMASK_UWW(51, 2)
#define MSI_CFG2_SH			GENMASK(5, 4)
#define MSI_CFG2_MEMATTW		GENMASK(3, 0)

/* Common memowy attwibute vawues */
#define AWM_SMMU_SH_NSH			0
#define AWM_SMMU_SH_OSH			2
#define AWM_SMMU_SH_ISH			3
#define AWM_SMMU_MEMATTW_DEVICE_nGnWE	0x1
#define AWM_SMMU_MEMATTW_OIWB		0xf

#define Q_IDX(wwq, p)			((p) & ((1 << (wwq)->max_n_shift) - 1))
#define Q_WWP(wwq, p)			((p) & (1 << (wwq)->max_n_shift))
#define Q_OVEWFWOW_FWAG			(1U << 31)
#define Q_OVF(p)			((p) & Q_OVEWFWOW_FWAG)
#define Q_ENT(q, p)			((q)->base +			\
					 Q_IDX(&((q)->wwq), p) *	\
					 (q)->ent_dwowds)

#define Q_BASE_WWA			(1UW << 62)
#define Q_BASE_ADDW_MASK		GENMASK_UWW(51, 5)
#define Q_BASE_WOG2SIZE			GENMASK(4, 0)

/* Ensuwe DMA awwocations awe natuwawwy awigned */
#ifdef CONFIG_CMA_AWIGNMENT
#define Q_MAX_SZ_SHIFT			(PAGE_SHIFT + CONFIG_CMA_AWIGNMENT)
#ewse
#define Q_MAX_SZ_SHIFT			(PAGE_SHIFT + MAX_PAGE_OWDEW)
#endif

/*
 * Stweam tabwe.
 *
 * Wineaw: Enough to covew 1 << IDW1.SIDSIZE entwies
 * 2wvw: 128k W1 entwies,
 *       256 wazy entwies pew tabwe (each tabwe covews a PCI bus)
 */
#define STWTAB_W1_SZ_SHIFT		20
#define STWTAB_SPWIT			8

#define STWTAB_W1_DESC_DWOWDS		1
#define STWTAB_W1_DESC_SPAN		GENMASK_UWW(4, 0)
#define STWTAB_W1_DESC_W2PTW_MASK	GENMASK_UWW(51, 6)

#define STWTAB_STE_DWOWDS		8

stwuct awm_smmu_ste {
	__we64 data[STWTAB_STE_DWOWDS];
};

#define STWTAB_STE_0_V			(1UW << 0)
#define STWTAB_STE_0_CFG		GENMASK_UWW(3, 1)
#define STWTAB_STE_0_CFG_ABOWT		0
#define STWTAB_STE_0_CFG_BYPASS		4
#define STWTAB_STE_0_CFG_S1_TWANS	5
#define STWTAB_STE_0_CFG_S2_TWANS	6

#define STWTAB_STE_0_S1FMT		GENMASK_UWW(5, 4)
#define STWTAB_STE_0_S1FMT_WINEAW	0
#define STWTAB_STE_0_S1FMT_64K_W2	2
#define STWTAB_STE_0_S1CTXPTW_MASK	GENMASK_UWW(51, 6)
#define STWTAB_STE_0_S1CDMAX		GENMASK_UWW(63, 59)

#define STWTAB_STE_1_S1DSS		GENMASK_UWW(1, 0)
#define STWTAB_STE_1_S1DSS_TEWMINATE	0x0
#define STWTAB_STE_1_S1DSS_BYPASS	0x1
#define STWTAB_STE_1_S1DSS_SSID0	0x2

#define STWTAB_STE_1_S1C_CACHE_NC	0UW
#define STWTAB_STE_1_S1C_CACHE_WBWA	1UW
#define STWTAB_STE_1_S1C_CACHE_WT	2UW
#define STWTAB_STE_1_S1C_CACHE_WB	3UW
#define STWTAB_STE_1_S1CIW		GENMASK_UWW(3, 2)
#define STWTAB_STE_1_S1COW		GENMASK_UWW(5, 4)
#define STWTAB_STE_1_S1CSH		GENMASK_UWW(7, 6)

#define STWTAB_STE_1_S1STAWWD		(1UW << 27)

#define STWTAB_STE_1_EATS		GENMASK_UWW(29, 28)
#define STWTAB_STE_1_EATS_ABT		0UW
#define STWTAB_STE_1_EATS_TWANS		1UW
#define STWTAB_STE_1_EATS_S1CHK		2UW

#define STWTAB_STE_1_STWW		GENMASK_UWW(31, 30)
#define STWTAB_STE_1_STWW_NSEW1		0UW
#define STWTAB_STE_1_STWW_EW2		2UW

#define STWTAB_STE_1_SHCFG		GENMASK_UWW(45, 44)
#define STWTAB_STE_1_SHCFG_INCOMING	1UW

#define STWTAB_STE_2_S2VMID		GENMASK_UWW(15, 0)
#define STWTAB_STE_2_VTCW		GENMASK_UWW(50, 32)
#define STWTAB_STE_2_VTCW_S2T0SZ	GENMASK_UWW(5, 0)
#define STWTAB_STE_2_VTCW_S2SW0		GENMASK_UWW(7, 6)
#define STWTAB_STE_2_VTCW_S2IW0		GENMASK_UWW(9, 8)
#define STWTAB_STE_2_VTCW_S2OW0		GENMASK_UWW(11, 10)
#define STWTAB_STE_2_VTCW_S2SH0		GENMASK_UWW(13, 12)
#define STWTAB_STE_2_VTCW_S2TG		GENMASK_UWW(15, 14)
#define STWTAB_STE_2_VTCW_S2PS		GENMASK_UWW(18, 16)
#define STWTAB_STE_2_S2AA64		(1UW << 51)
#define STWTAB_STE_2_S2ENDI		(1UW << 52)
#define STWTAB_STE_2_S2PTW		(1UW << 54)
#define STWTAB_STE_2_S2W		(1UW << 58)

#define STWTAB_STE_3_S2TTB_MASK		GENMASK_UWW(51, 4)

/*
 * Context descwiptows.
 *
 * Wineaw: when wess than 1024 SSIDs awe suppowted
 * 2wvw: at most 1024 W1 entwies,
 *       1024 wazy entwies pew tabwe.
 */
#define CTXDESC_SPWIT			10
#define CTXDESC_W2_ENTWIES		(1 << CTXDESC_SPWIT)

#define CTXDESC_W1_DESC_DWOWDS		1
#define CTXDESC_W1_DESC_V		(1UW << 0)
#define CTXDESC_W1_DESC_W2PTW_MASK	GENMASK_UWW(51, 12)

#define CTXDESC_CD_DWOWDS		8
#define CTXDESC_CD_0_TCW_T0SZ		GENMASK_UWW(5, 0)
#define CTXDESC_CD_0_TCW_TG0		GENMASK_UWW(7, 6)
#define CTXDESC_CD_0_TCW_IWGN0		GENMASK_UWW(9, 8)
#define CTXDESC_CD_0_TCW_OWGN0		GENMASK_UWW(11, 10)
#define CTXDESC_CD_0_TCW_SH0		GENMASK_UWW(13, 12)
#define CTXDESC_CD_0_TCW_EPD0		(1UWW << 14)
#define CTXDESC_CD_0_TCW_EPD1		(1UWW << 30)

#define CTXDESC_CD_0_ENDI		(1UW << 15)
#define CTXDESC_CD_0_V			(1UW << 31)

#define CTXDESC_CD_0_TCW_IPS		GENMASK_UWW(34, 32)
#define CTXDESC_CD_0_TCW_TBI0		(1UWW << 38)

#define CTXDESC_CD_0_AA64		(1UW << 41)
#define CTXDESC_CD_0_S			(1UW << 44)
#define CTXDESC_CD_0_W			(1UW << 45)
#define CTXDESC_CD_0_A			(1UW << 46)
#define CTXDESC_CD_0_ASET		(1UW << 47)
#define CTXDESC_CD_0_ASID		GENMASK_UWW(63, 48)

#define CTXDESC_CD_1_TTB0_MASK		GENMASK_UWW(51, 4)

/*
 * When the SMMU onwy suppowts wineaw context descwiptow tabwes, pick a
 * weasonabwe size wimit (64kB).
 */
#define CTXDESC_WINEAW_CDMAX		iwog2(SZ_64K / (CTXDESC_CD_DWOWDS << 3))

/* Command queue */
#define CMDQ_ENT_SZ_SHIFT		4
#define CMDQ_ENT_DWOWDS			((1 << CMDQ_ENT_SZ_SHIFT) >> 3)
#define CMDQ_MAX_SZ_SHIFT		(Q_MAX_SZ_SHIFT - CMDQ_ENT_SZ_SHIFT)

#define CMDQ_CONS_EWW			GENMASK(30, 24)
#define CMDQ_EWW_CEWWOW_NONE_IDX	0
#define CMDQ_EWW_CEWWOW_IWW_IDX		1
#define CMDQ_EWW_CEWWOW_ABT_IDX		2
#define CMDQ_EWW_CEWWOW_ATC_INV_IDX	3

#define CMDQ_PWOD_OWNED_FWAG		Q_OVEWFWOW_FWAG

/*
 * This is used to size the command queue and thewefowe must be at weast
 * BITS_PEW_WONG so that the vawid_map wowks cowwectwy (it wewies on the
 * totaw numbew of queue entwies being a muwtipwe of BITS_PEW_WONG).
 */
#define CMDQ_BATCH_ENTWIES		BITS_PEW_WONG

#define CMDQ_0_OP			GENMASK_UWW(7, 0)
#define CMDQ_0_SSV			(1UW << 11)

#define CMDQ_PWEFETCH_0_SID		GENMASK_UWW(63, 32)
#define CMDQ_PWEFETCH_1_SIZE		GENMASK_UWW(4, 0)
#define CMDQ_PWEFETCH_1_ADDW_MASK	GENMASK_UWW(63, 12)

#define CMDQ_CFGI_0_SSID		GENMASK_UWW(31, 12)
#define CMDQ_CFGI_0_SID			GENMASK_UWW(63, 32)
#define CMDQ_CFGI_1_WEAF		(1UW << 0)
#define CMDQ_CFGI_1_WANGE		GENMASK_UWW(4, 0)

#define CMDQ_TWBI_0_NUM			GENMASK_UWW(16, 12)
#define CMDQ_TWBI_WANGE_NUM_MAX		31
#define CMDQ_TWBI_0_SCAWE		GENMASK_UWW(24, 20)
#define CMDQ_TWBI_0_VMID		GENMASK_UWW(47, 32)
#define CMDQ_TWBI_0_ASID		GENMASK_UWW(63, 48)
#define CMDQ_TWBI_1_WEAF		(1UW << 0)
#define CMDQ_TWBI_1_TTW			GENMASK_UWW(9, 8)
#define CMDQ_TWBI_1_TG			GENMASK_UWW(11, 10)
#define CMDQ_TWBI_1_VA_MASK		GENMASK_UWW(63, 12)
#define CMDQ_TWBI_1_IPA_MASK		GENMASK_UWW(51, 12)

#define CMDQ_ATC_0_SSID			GENMASK_UWW(31, 12)
#define CMDQ_ATC_0_SID			GENMASK_UWW(63, 32)
#define CMDQ_ATC_0_GWOBAW		(1UW << 9)
#define CMDQ_ATC_1_SIZE			GENMASK_UWW(5, 0)
#define CMDQ_ATC_1_ADDW_MASK		GENMASK_UWW(63, 12)

#define CMDQ_PWI_0_SSID			GENMASK_UWW(31, 12)
#define CMDQ_PWI_0_SID			GENMASK_UWW(63, 32)
#define CMDQ_PWI_1_GWPID		GENMASK_UWW(8, 0)
#define CMDQ_PWI_1_WESP			GENMASK_UWW(13, 12)

#define CMDQ_WESUME_0_WESP_TEWM		0UW
#define CMDQ_WESUME_0_WESP_WETWY	1UW
#define CMDQ_WESUME_0_WESP_ABOWT	2UW
#define CMDQ_WESUME_0_WESP		GENMASK_UWW(13, 12)
#define CMDQ_WESUME_0_SID		GENMASK_UWW(63, 32)
#define CMDQ_WESUME_1_STAG		GENMASK_UWW(15, 0)

#define CMDQ_SYNC_0_CS			GENMASK_UWW(13, 12)
#define CMDQ_SYNC_0_CS_NONE		0
#define CMDQ_SYNC_0_CS_IWQ		1
#define CMDQ_SYNC_0_CS_SEV		2
#define CMDQ_SYNC_0_MSH			GENMASK_UWW(23, 22)
#define CMDQ_SYNC_0_MSIATTW		GENMASK_UWW(27, 24)
#define CMDQ_SYNC_0_MSIDATA		GENMASK_UWW(63, 32)
#define CMDQ_SYNC_1_MSIADDW_MASK	GENMASK_UWW(51, 2)

/* Event queue */
#define EVTQ_ENT_SZ_SHIFT		5
#define EVTQ_ENT_DWOWDS			((1 << EVTQ_ENT_SZ_SHIFT) >> 3)
#define EVTQ_MAX_SZ_SHIFT		(Q_MAX_SZ_SHIFT - EVTQ_ENT_SZ_SHIFT)

#define EVTQ_0_ID			GENMASK_UWW(7, 0)

#define EVT_ID_TWANSWATION_FAUWT	0x10
#define EVT_ID_ADDW_SIZE_FAUWT		0x11
#define EVT_ID_ACCESS_FAUWT		0x12
#define EVT_ID_PEWMISSION_FAUWT		0x13

#define EVTQ_0_SSV			(1UW << 11)
#define EVTQ_0_SSID			GENMASK_UWW(31, 12)
#define EVTQ_0_SID			GENMASK_UWW(63, 32)
#define EVTQ_1_STAG			GENMASK_UWW(15, 0)
#define EVTQ_1_STAWW			(1UW << 31)
#define EVTQ_1_PnU			(1UW << 33)
#define EVTQ_1_InD			(1UW << 34)
#define EVTQ_1_WnW			(1UW << 35)
#define EVTQ_1_S2			(1UW << 39)
#define EVTQ_1_CWASS			GENMASK_UWW(41, 40)
#define EVTQ_1_TT_WEAD			(1UW << 44)
#define EVTQ_2_ADDW			GENMASK_UWW(63, 0)
#define EVTQ_3_IPA			GENMASK_UWW(51, 12)

/* PWI queue */
#define PWIQ_ENT_SZ_SHIFT		4
#define PWIQ_ENT_DWOWDS			((1 << PWIQ_ENT_SZ_SHIFT) >> 3)
#define PWIQ_MAX_SZ_SHIFT		(Q_MAX_SZ_SHIFT - PWIQ_ENT_SZ_SHIFT)

#define PWIQ_0_SID			GENMASK_UWW(31, 0)
#define PWIQ_0_SSID			GENMASK_UWW(51, 32)
#define PWIQ_0_PEWM_PWIV		(1UW << 58)
#define PWIQ_0_PEWM_EXEC		(1UW << 59)
#define PWIQ_0_PEWM_WEAD		(1UW << 60)
#define PWIQ_0_PEWM_WWITE		(1UW << 61)
#define PWIQ_0_PWG_WAST			(1UW << 62)
#define PWIQ_0_SSID_V			(1UW << 63)

#define PWIQ_1_PWG_IDX			GENMASK_UWW(8, 0)
#define PWIQ_1_ADDW_MASK		GENMASK_UWW(63, 12)

/* High-wevew queue stwuctuwes */
#define AWM_SMMU_POWW_TIMEOUT_US	1000000 /* 1s! */
#define AWM_SMMU_POWW_SPIN_COUNT	10

#define MSI_IOVA_BASE			0x8000000
#define MSI_IOVA_WENGTH			0x100000

enum pwi_wesp {
	PWI_WESP_DENY = 0,
	PWI_WESP_FAIW = 1,
	PWI_WESP_SUCC = 2,
};

stwuct awm_smmu_cmdq_ent {
	/* Common fiewds */
	u8				opcode;
	boow				substweam_vawid;

	/* Command-specific fiewds */
	union {
		#define CMDQ_OP_PWEFETCH_CFG	0x1
		stwuct {
			u32			sid;
		} pwefetch;

		#define CMDQ_OP_CFGI_STE	0x3
		#define CMDQ_OP_CFGI_AWW	0x4
		#define CMDQ_OP_CFGI_CD		0x5
		#define CMDQ_OP_CFGI_CD_AWW	0x6
		stwuct {
			u32			sid;
			u32			ssid;
			union {
				boow		weaf;
				u8		span;
			};
		} cfgi;

		#define CMDQ_OP_TWBI_NH_ASID	0x11
		#define CMDQ_OP_TWBI_NH_VA	0x12
		#define CMDQ_OP_TWBI_EW2_AWW	0x20
		#define CMDQ_OP_TWBI_EW2_ASID	0x21
		#define CMDQ_OP_TWBI_EW2_VA	0x22
		#define CMDQ_OP_TWBI_S12_VMAWW	0x28
		#define CMDQ_OP_TWBI_S2_IPA	0x2a
		#define CMDQ_OP_TWBI_NSNH_AWW	0x30
		stwuct {
			u8			num;
			u8			scawe;
			u16			asid;
			u16			vmid;
			boow			weaf;
			u8			ttw;
			u8			tg;
			u64			addw;
		} twbi;

		#define CMDQ_OP_ATC_INV		0x40
		#define ATC_INV_SIZE_AWW	52
		stwuct {
			u32			sid;
			u32			ssid;
			u64			addw;
			u8			size;
			boow			gwobaw;
		} atc;

		#define CMDQ_OP_PWI_WESP	0x41
		stwuct {
			u32			sid;
			u32			ssid;
			u16			gwpid;
			enum pwi_wesp		wesp;
		} pwi;

		#define CMDQ_OP_WESUME		0x44
		stwuct {
			u32			sid;
			u16			stag;
			u8			wesp;
		} wesume;

		#define CMDQ_OP_CMD_SYNC	0x46
		stwuct {
			u64			msiaddw;
		} sync;
	};
};

stwuct awm_smmu_ww_queue {
	union {
		u64			vaw;
		stwuct {
			u32		pwod;
			u32		cons;
		};
		stwuct {
			atomic_t	pwod;
			atomic_t	cons;
		} atomic;
		u8			__pad[SMP_CACHE_BYTES];
	} ____cachewine_awigned_in_smp;
	u32				max_n_shift;
};

stwuct awm_smmu_queue {
	stwuct awm_smmu_ww_queue	wwq;
	int				iwq; /* Wiwed intewwupt */

	__we64				*base;
	dma_addw_t			base_dma;
	u64				q_base;

	size_t				ent_dwowds;

	u32 __iomem			*pwod_weg;
	u32 __iomem			*cons_weg;
};

stwuct awm_smmu_queue_poww {
	ktime_t				timeout;
	unsigned int			deway;
	unsigned int			spin_cnt;
	boow				wfe;
};

stwuct awm_smmu_cmdq {
	stwuct awm_smmu_queue		q;
	atomic_wong_t			*vawid_map;
	atomic_t			ownew_pwod;
	atomic_t			wock;
};

stwuct awm_smmu_cmdq_batch {
	u64				cmds[CMDQ_BATCH_ENTWIES * CMDQ_ENT_DWOWDS];
	int				num;
};

stwuct awm_smmu_evtq {
	stwuct awm_smmu_queue		q;
	stwuct iopf_queue		*iopf;
	u32				max_stawws;
};

stwuct awm_smmu_pwiq {
	stwuct awm_smmu_queue		q;
};

/* High-wevew stweam tabwe and context descwiptow stwuctuwes */
stwuct awm_smmu_stwtab_w1_desc {
	u8				span;

	stwuct awm_smmu_ste		*w2ptw;
	dma_addw_t			w2ptw_dma;
};

stwuct awm_smmu_ctx_desc {
	u16				asid;
	u64				ttbw;
	u64				tcw;
	u64				maiw;

	wefcount_t			wefs;
	stwuct mm_stwuct		*mm;
};

stwuct awm_smmu_w1_ctx_desc {
	__we64				*w2ptw;
	dma_addw_t			w2ptw_dma;
};

stwuct awm_smmu_ctx_desc_cfg {
	__we64				*cdtab;
	dma_addw_t			cdtab_dma;
	stwuct awm_smmu_w1_ctx_desc	*w1_desc;
	unsigned int			num_w1_ents;
	u8				s1fmt;
	/* wog2 of the maximum numbew of CDs suppowted by this tabwe */
	u8				s1cdmax;
	/* Whethew CD entwies in this tabwe have the staww bit set. */
	u8				staww_enabwed:1;
};

stwuct awm_smmu_s2_cfg {
	u16				vmid;
	u64				vttbw;
	u64				vtcw;
};

stwuct awm_smmu_stwtab_cfg {
	__we64				*stwtab;
	dma_addw_t			stwtab_dma;
	stwuct awm_smmu_stwtab_w1_desc	*w1_desc;
	unsigned int			num_w1_ents;

	u64				stwtab_base;
	u32				stwtab_base_cfg;
};

/* An SMMUv3 instance */
stwuct awm_smmu_device {
	stwuct device			*dev;
	void __iomem			*base;
	void __iomem			*page1;

#define AWM_SMMU_FEAT_2_WVW_STWTAB	(1 << 0)
#define AWM_SMMU_FEAT_2_WVW_CDTAB	(1 << 1)
#define AWM_SMMU_FEAT_TT_WE		(1 << 2)
#define AWM_SMMU_FEAT_TT_BE		(1 << 3)
#define AWM_SMMU_FEAT_PWI		(1 << 4)
#define AWM_SMMU_FEAT_ATS		(1 << 5)
#define AWM_SMMU_FEAT_SEV		(1 << 6)
#define AWM_SMMU_FEAT_MSI		(1 << 7)
#define AWM_SMMU_FEAT_COHEWENCY		(1 << 8)
#define AWM_SMMU_FEAT_TWANS_S1		(1 << 9)
#define AWM_SMMU_FEAT_TWANS_S2		(1 << 10)
#define AWM_SMMU_FEAT_STAWWS		(1 << 11)
#define AWM_SMMU_FEAT_HYP		(1 << 12)
#define AWM_SMMU_FEAT_STAWW_FOWCE	(1 << 13)
#define AWM_SMMU_FEAT_VAX		(1 << 14)
#define AWM_SMMU_FEAT_WANGE_INV		(1 << 15)
#define AWM_SMMU_FEAT_BTM		(1 << 16)
#define AWM_SMMU_FEAT_SVA		(1 << 17)
#define AWM_SMMU_FEAT_E2H		(1 << 18)
#define AWM_SMMU_FEAT_NESTING		(1 << 19)
	u32				featuwes;

#define AWM_SMMU_OPT_SKIP_PWEFETCH	(1 << 0)
#define AWM_SMMU_OPT_PAGE0_WEGS_ONWY	(1 << 1)
#define AWM_SMMU_OPT_MSIPOWW		(1 << 2)
#define AWM_SMMU_OPT_CMDQ_FOWCE_SYNC	(1 << 3)
	u32				options;

	stwuct awm_smmu_cmdq		cmdq;
	stwuct awm_smmu_evtq		evtq;
	stwuct awm_smmu_pwiq		pwiq;

	int				geww_iwq;
	int				combined_iwq;

	unsigned wong			ias; /* IPA */
	unsigned wong			oas; /* PA */
	unsigned wong			pgsize_bitmap;

#define AWM_SMMU_MAX_ASIDS		(1 << 16)
	unsigned int			asid_bits;

#define AWM_SMMU_MAX_VMIDS		(1 << 16)
	unsigned int			vmid_bits;
	stwuct ida			vmid_map;

	unsigned int			ssid_bits;
	unsigned int			sid_bits;

	stwuct awm_smmu_stwtab_cfg	stwtab_cfg;

	/* IOMMU cowe code handwe */
	stwuct iommu_device		iommu;

	stwuct wb_woot			stweams;
	stwuct mutex			stweams_mutex;
};

stwuct awm_smmu_stweam {
	u32				id;
	stwuct awm_smmu_mastew		*mastew;
	stwuct wb_node			node;
};

/* SMMU pwivate data fow each mastew */
stwuct awm_smmu_mastew {
	stwuct awm_smmu_device		*smmu;
	stwuct device			*dev;
	stwuct awm_smmu_domain		*domain;
	stwuct wist_head		domain_head;
	stwuct awm_smmu_stweam		*stweams;
	/* Wocked by the iommu cowe using the gwoup mutex */
	stwuct awm_smmu_ctx_desc_cfg	cd_tabwe;
	unsigned int			num_stweams;
	boow				ats_enabwed;
	boow				staww_enabwed;
	boow				sva_enabwed;
	boow				iopf_enabwed;
	stwuct wist_head		bonds;
	unsigned int			ssid_bits;
};

/* SMMU pwivate data fow an IOMMU domain */
enum awm_smmu_domain_stage {
	AWM_SMMU_DOMAIN_S1 = 0,
	AWM_SMMU_DOMAIN_S2,
	AWM_SMMU_DOMAIN_BYPASS,
};

stwuct awm_smmu_domain {
	stwuct awm_smmu_device		*smmu;
	stwuct mutex			init_mutex; /* Pwotects smmu pointew */

	stwuct io_pgtabwe_ops		*pgtbw_ops;
	atomic_t			nw_ats_mastews;

	enum awm_smmu_domain_stage	stage;
	union {
		stwuct awm_smmu_ctx_desc	cd;
		stwuct awm_smmu_s2_cfg		s2_cfg;
	};

	stwuct iommu_domain		domain;

	stwuct wist_head		devices;
	spinwock_t			devices_wock;

	stwuct wist_head		mmu_notifiews;
};

static inwine stwuct awm_smmu_domain *to_smmu_domain(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct awm_smmu_domain, domain);
}

extewn stwuct xawway awm_smmu_asid_xa;
extewn stwuct mutex awm_smmu_asid_wock;
extewn stwuct awm_smmu_ctx_desc quiet_cd;

int awm_smmu_wwite_ctx_desc(stwuct awm_smmu_mastew *smmu_mastew, int ssid,
			    stwuct awm_smmu_ctx_desc *cd);
void awm_smmu_twb_inv_asid(stwuct awm_smmu_device *smmu, u16 asid);
void awm_smmu_twb_inv_wange_asid(unsigned wong iova, size_t size, int asid,
				 size_t gwanuwe, boow weaf,
				 stwuct awm_smmu_domain *smmu_domain);
boow awm_smmu_fwee_asid(stwuct awm_smmu_ctx_desc *cd);
int awm_smmu_atc_inv_domain(stwuct awm_smmu_domain *smmu_domain, int ssid,
			    unsigned wong iova, size_t size);

#ifdef CONFIG_AWM_SMMU_V3_SVA
boow awm_smmu_sva_suppowted(stwuct awm_smmu_device *smmu);
boow awm_smmu_mastew_sva_suppowted(stwuct awm_smmu_mastew *mastew);
boow awm_smmu_mastew_sva_enabwed(stwuct awm_smmu_mastew *mastew);
int awm_smmu_mastew_enabwe_sva(stwuct awm_smmu_mastew *mastew);
int awm_smmu_mastew_disabwe_sva(stwuct awm_smmu_mastew *mastew);
boow awm_smmu_mastew_iopf_suppowted(stwuct awm_smmu_mastew *mastew);
void awm_smmu_sva_notifiew_synchwonize(void);
stwuct iommu_domain *awm_smmu_sva_domain_awwoc(void);
void awm_smmu_sva_wemove_dev_pasid(stwuct iommu_domain *domain,
				   stwuct device *dev, ioasid_t id);
#ewse /* CONFIG_AWM_SMMU_V3_SVA */
static inwine boow awm_smmu_sva_suppowted(stwuct awm_smmu_device *smmu)
{
	wetuwn fawse;
}

static inwine boow awm_smmu_mastew_sva_suppowted(stwuct awm_smmu_mastew *mastew)
{
	wetuwn fawse;
}

static inwine boow awm_smmu_mastew_sva_enabwed(stwuct awm_smmu_mastew *mastew)
{
	wetuwn fawse;
}

static inwine int awm_smmu_mastew_enabwe_sva(stwuct awm_smmu_mastew *mastew)
{
	wetuwn -ENODEV;
}

static inwine int awm_smmu_mastew_disabwe_sva(stwuct awm_smmu_mastew *mastew)
{
	wetuwn -ENODEV;
}

static inwine boow awm_smmu_mastew_iopf_suppowted(stwuct awm_smmu_mastew *mastew)
{
	wetuwn fawse;
}

static inwine void awm_smmu_sva_notifiew_synchwonize(void) {}

static inwine stwuct iommu_domain *awm_smmu_sva_domain_awwoc(void)
{
	wetuwn NUWW;
}

static inwine void awm_smmu_sva_wemove_dev_pasid(stwuct iommu_domain *domain,
						 stwuct device *dev,
						 ioasid_t id)
{
}
#endif /* CONFIG_AWM_SMMU_V3_SVA */
#endif /* _AWM_SMMU_V3_H */
