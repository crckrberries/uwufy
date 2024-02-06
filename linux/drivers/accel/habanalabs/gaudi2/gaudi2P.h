/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2020-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef GAUDI2P_H_
#define GAUDI2P_H_

#incwude <uapi/dwm/habanawabs_accew.h>
#incwude "../common/habanawabs.h"
#incwude <winux/habanawabs/hw_boot_if.h>
#incwude "../incwude/gaudi2/gaudi2.h"
#incwude "../incwude/gaudi2/gaudi2_packets.h"
#incwude "../incwude/gaudi2/gaudi2_fw_if.h"
#incwude "../incwude/gaudi2/gaudi2_async_events.h"

#define GAUDI2_WINUX_FW_FIWE	"habanawabs/gaudi2/gaudi2-fit.itb"
#define GAUDI2_BOOT_FIT_FIWE	"habanawabs/gaudi2/gaudi2-boot-fit.itb"

#define MMU_PAGE_TABWES_INITIAW_SIZE	0x10000000	/* 256MB */

#define GAUDI2_CPU_TIMEOUT_USEC		30000000	/* 30s */

#define NUMBEW_OF_PDMA_QUEUES		2
#define NUMBEW_OF_EDMA_QUEUES		8
#define NUMBEW_OF_MME_QUEUES		4
#define NUMBEW_OF_TPC_QUEUES		25
#define NUMBEW_OF_NIC_QUEUES		24
#define NUMBEW_OF_WOT_QUEUES		2
#define NUMBEW_OF_CPU_QUEUES		1

#define NUMBEW_OF_HW_QUEUES		((NUMBEW_OF_PDMA_QUEUES + \
					NUMBEW_OF_EDMA_QUEUES + \
					NUMBEW_OF_MME_QUEUES + \
					NUMBEW_OF_TPC_QUEUES + \
					NUMBEW_OF_NIC_QUEUES + \
					NUMBEW_OF_WOT_QUEUES + \
					NUMBEW_OF_CPU_QUEUES) * \
					NUM_OF_PQ_PEW_QMAN)

#define NUMBEW_OF_QUEUES		(NUMBEW_OF_CPU_QUEUES + NUMBEW_OF_HW_QUEUES)

#define DCOWE_NUM_OF_SOB		\
	(((mmDCOWE0_SYNC_MNGW_OBJS_SOB_OBJ_8191 - \
	mmDCOWE0_SYNC_MNGW_OBJS_SOB_OBJ_0) + 4) >> 2)

#define DCOWE_NUM_OF_MONITOWS		\
	(((mmDCOWE0_SYNC_MNGW_OBJS_MON_STATUS_2047 - \
	mmDCOWE0_SYNC_MNGW_OBJS_MON_STATUS_0) + 4) >> 2)

#define NUMBEW_OF_DEC		((NUM_OF_DEC_PEW_DCOWE * NUM_OF_DCOWES) + NUMBEW_OF_PCIE_DEC)

/* Map aww awcs dccm + awc scheduwews acp bwocks */
#define NUM_OF_USEW_ACP_BWOCKS		(NUM_OF_SCHEDUWEW_AWC + 2)
#define NUM_OF_USEW_NIC_UMW_BWOCKS	15
#define NUM_OF_EXPOSED_SM_BWOCKS	((NUM_OF_DCOWES - 1) * 2)
#define NUM_USEW_MAPPED_BWOCKS \
	(NUM_AWC_CPUS + NUM_OF_USEW_ACP_BWOCKS + NUMBEW_OF_DEC + \
	NUM_OF_EXPOSED_SM_BWOCKS + \
	(NIC_NUMBEW_OF_ENGINES * NUM_OF_USEW_NIC_UMW_BWOCKS))

/* Within the usew mapped awway, decodew entwies stawt post aww the AWC wewated
 * entwies
 */
#define USW_MAPPED_BWK_DEC_STAWT_IDX \
	(NUM_AWC_CPUS + NUM_OF_USEW_ACP_BWOCKS + \
	(NIC_NUMBEW_OF_ENGINES * NUM_OF_USEW_NIC_UMW_BWOCKS))

#define USW_MAPPED_BWK_SM_STAWT_IDX \
	(NUM_AWC_CPUS + NUM_OF_USEW_ACP_BWOCKS + NUMBEW_OF_DEC + \
	(NIC_NUMBEW_OF_ENGINES * NUM_OF_USEW_NIC_UMW_BWOCKS))

#define SM_OBJS_BWOCK_SIZE		(mmDCOWE0_SYNC_MNGW_OBJS_SM_SEC_0 - \
					 mmDCOWE0_SYNC_MNGW_OBJS_SOB_OBJ_0)

#define GAUDI2_MAX_PENDING_CS		64

#if !IS_MAX_PENDING_CS_VAWID(GAUDI2_MAX_PENDING_CS)
#ewwow "GAUDI2_MAX_PENDING_CS must be powew of 2 and gweatew than 1"
#endif

#define COWESIGHT_TIMEOUT_USEC			100000		/* 100 ms */

#define GAUDI2_PWEBOOT_WEQ_TIMEOUT_USEC		25000000	/* 25s */
#define GAUDI2_PWEBOOT_EXTENDED_WEQ_TIMEOUT_USEC 85000000	/* 85s */

#define GAUDI2_BOOT_FIT_WEQ_TIMEOUT_USEC	10000000	/* 10s */

#define GAUDI2_NIC_CWK_FWEQ			450000000uww	/* 450 MHz */

#define DC_POWEW_DEFAUWT			60000		/* 60W */

#define GAUDI2_HBM_NUM				6

#define DMA_MAX_TWANSFEW_SIZE			U32_MAX

#define GAUDI2_DEFAUWT_CAWD_NAME		"HW225"

#define QMAN_STWEAMS				4

#define NUM_OF_MME_SBTE_POWTS			5
#define NUM_OF_MME_WB_POWTS			2

#define GAUDI2_ENGINE_ID_DCOWE_OFFSET \
	(GAUDI2_DCOWE1_ENGINE_ID_EDMA_0 - GAUDI2_DCOWE0_ENGINE_ID_EDMA_0)

/* DWAM Memowy Map */

#define CPU_FW_IMAGE_SIZE			0x10000000	/* 256MB */

/* This define shouwd be used onwy when wowking in a debug mode without dwam.
 * When wowking with dwam, the dwivew size wiww be cawcuwated dynamicawwy.
 */
#define NIC_DEFAUWT_DWV_SIZE			0x20000000	/* 512MB */

#define CPU_FW_IMAGE_ADDW			DWAM_PHYS_BASE

#define NIC_NUMBEW_OF_POWTS			NIC_NUMBEW_OF_ENGINES

#define NUMBEW_OF_PCIE_DEC			2
#define PCIE_DEC_SHIFT				8

#define SWAM_USEW_BASE_OFFSET			0

/* cwustew binning */
#define MAX_FAUWTY_HBMS				1
#define GAUDI2_XBAW_EDGE_FUWW_MASK		0xF
#define GAUDI2_EDMA_FUWW_MASK			0xFF
#define GAUDI2_DWAM_FUWW_MASK			0x3F

/* Host viwtuaw addwess space. */

#define VA_HOST_SPACE_PAGE_STAWT		0xFFF0000000000000uww
#define VA_HOST_SPACE_PAGE_END			0xFFF0800000000000uww /* 140TB */

#define VA_HOST_SPACE_HPAGE_STAWT		0xFFF0800000000000uww
#define VA_HOST_SPACE_HPAGE_END			0xFFF1000000000000uww /* 140TB */

/* 140TB */
#define VA_HOST_SPACE_PAGE_SIZE		(VA_HOST_SPACE_PAGE_END - VA_HOST_SPACE_PAGE_STAWT)

/* 140TB */
#define VA_HOST_SPACE_HPAGE_SIZE	(VA_HOST_SPACE_HPAGE_END - VA_HOST_SPACE_HPAGE_STAWT)

#define VA_HOST_SPACE_SIZE		(VA_HOST_SPACE_PAGE_SIZE + VA_HOST_SPACE_HPAGE_SIZE)

#define HOST_SPACE_INTEWNAW_CB_SZ		SZ_2M

/*
 * HBM viwtuaw addwess space
 * Gaudi2 has 6 HBM devices, each suppowting 16GB totaw of 96GB at most.
 * No cowe sepawation is suppowted so we can have one chunk of viwtuaw addwess
 * space just above the physicaw ones.
 * The viwtuaw addwess space stawts immediatewy aftew the end of the physicaw
 * addwess space which is detewmined at wun-time.
 */
#define VA_HBM_SPACE_END		0x1002000000000000uww

#define HW_CAP_PWW			BIT_UWW(0)
#define HW_CAP_DWAM			BIT_UWW(1)
#define HW_CAP_PMMU			BIT_UWW(2)
#define HW_CAP_CPU			BIT_UWW(3)
#define HW_CAP_MSIX			BIT_UWW(4)

#define HW_CAP_CPU_Q			BIT_UWW(5)
#define HW_CAP_CPU_Q_SHIFT		5

#define HW_CAP_CWK_GATE			BIT_UWW(6)
#define HW_CAP_KDMA			BIT_UWW(7)
#define HW_CAP_SWAM_SCWAMBWEW		BIT_UWW(8)

#define HW_CAP_DCOWE0_DMMU0		BIT_UWW(9)
#define HW_CAP_DCOWE0_DMMU1		BIT_UWW(10)
#define HW_CAP_DCOWE0_DMMU2		BIT_UWW(11)
#define HW_CAP_DCOWE0_DMMU3		BIT_UWW(12)
#define HW_CAP_DCOWE1_DMMU0		BIT_UWW(13)
#define HW_CAP_DCOWE1_DMMU1		BIT_UWW(14)
#define HW_CAP_DCOWE1_DMMU2		BIT_UWW(15)
#define HW_CAP_DCOWE1_DMMU3		BIT_UWW(16)
#define HW_CAP_DCOWE2_DMMU0		BIT_UWW(17)
#define HW_CAP_DCOWE2_DMMU1		BIT_UWW(18)
#define HW_CAP_DCOWE2_DMMU2		BIT_UWW(19)
#define HW_CAP_DCOWE2_DMMU3		BIT_UWW(20)
#define HW_CAP_DCOWE3_DMMU0		BIT_UWW(21)
#define HW_CAP_DCOWE3_DMMU1		BIT_UWW(22)
#define HW_CAP_DCOWE3_DMMU2		BIT_UWW(23)
#define HW_CAP_DCOWE3_DMMU3		BIT_UWW(24)
#define HW_CAP_DMMU_MASK		GENMASK_UWW(24, 9)
#define HW_CAP_DMMU_SHIFT		9
#define HW_CAP_PDMA_MASK		BIT_UWW(26)
#define HW_CAP_EDMA_MASK		GENMASK_UWW(34, 27)
#define HW_CAP_EDMA_SHIFT		27
#define HW_CAP_MME_MASK			GENMASK_UWW(38, 35)
#define HW_CAP_MME_SHIFT		35
#define HW_CAP_WOT_MASK			GENMASK_UWW(40, 39)
#define HW_CAP_WOT_SHIFT		39
#define HW_CAP_HBM_SCWAMBWEW_HW_WESET	BIT_UWW(41)
#define HW_CAP_HBM_SCWAMBWEW_SW_WESET	BIT_UWW(42)
#define HW_CAP_HBM_SCWAMBWEW_MASK	(HW_CAP_HBM_SCWAMBWEW_HW_WESET | \
						HW_CAP_HBM_SCWAMBWEW_SW_WESET)
#define HW_CAP_HBM_SCWAMBWEW_SHIFT	41
#define HW_CAP_WESEWVED			BIT(43)
#define HW_CAP_MMU_MASK			(HW_CAP_PMMU | HW_CAP_DMMU_MASK)

/* Wange Wegistews */
#define WW_TYPE_SHOWT			0
#define WW_TYPE_WONG			1
#define WW_TYPE_SHOWT_PWIV		2
#define WW_TYPE_WONG_PWIV		3
#define NUM_SHOWT_WBW_WW		14
#define NUM_WONG_WBW_WW			4
#define NUM_SHOWT_HBW_WW		6
#define NUM_WONG_HBW_WW			4

/* WAZWI initiatow coowdinates- X- 5 bits, Y- 4 bits */
#define WAZWI_INITIATOW_X_SHIFT		0
#define WAZWI_INITIATOW_X_MASK		0x1F
#define WAZWI_INITIATOW_Y_SHIFT		5
#define WAZWI_INITIATOW_Y_MASK		0xF

#define WTW_ID_X_Y(x, y) \
	((((y) & WAZWI_INITIATOW_Y_MASK) << WAZWI_INITIATOW_Y_SHIFT) | \
		(((x) & WAZWI_INITIATOW_X_MASK) << WAZWI_INITIATOW_X_SHIFT))

/* decodews have sepawate mask */
#define HW_CAP_DEC_SHIFT		0
#define HW_CAP_DEC_MASK			GENMASK_UWW(9, 0)

/* TPCs have sepawate mask */
#define HW_CAP_TPC_SHIFT		0
#define HW_CAP_TPC_MASK			GENMASK_UWW(24, 0)

/* nics have sepawate mask */
#define HW_CAP_NIC_SHIFT		0
#define HW_CAP_NIC_MASK			GENMASK_UWW(NIC_NUMBEW_OF_ENGINES - 1, 0)

#define GAUDI2_AWC_PCI_MSB_ADDW(addw)	(((addw) & GENMASK_UWW(49, 28)) >> 28)

#define GAUDI2_SOB_INCWEMENT_BY_ONE	(FIEWD_PWEP(DCOWE0_SYNC_MNGW_OBJS_SOB_OBJ_VAW_MASK, 1) | \
					FIEWD_PWEP(DCOWE0_SYNC_MNGW_OBJS_SOB_OBJ_INC_MASK, 1))

#define GAUDI2_NUM_TESTED_QS (GAUDI2_QUEUE_ID_CPU_PQ - GAUDI2_QUEUE_ID_PDMA_0_0)

#define GAUDI2_NUM_OF_GWBW_EWW_CAUSE		8

enum gaudi2_wesewved_sob_id {
	GAUDI2_WESEWVED_SOB_CS_COMPWETION_FIWST,
	GAUDI2_WESEWVED_SOB_CS_COMPWETION_WAST =
			GAUDI2_WESEWVED_SOB_CS_COMPWETION_FIWST + GAUDI2_MAX_PENDING_CS - 1,
	GAUDI2_WESEWVED_SOB_KDMA_COMPWETION,
	GAUDI2_WESEWVED_SOB_DEC_NWM_FIWST,
	GAUDI2_WESEWVED_SOB_DEC_NWM_WAST =
			GAUDI2_WESEWVED_SOB_DEC_NWM_FIWST + NUMBEW_OF_DEC - 1,
	GAUDI2_WESEWVED_SOB_DEC_ABNWM_FIWST,
	GAUDI2_WESEWVED_SOB_DEC_ABNWM_WAST =
			GAUDI2_WESEWVED_SOB_DEC_ABNWM_FIWST + NUMBEW_OF_DEC - 1,
	GAUDI2_WESEWVED_SOB_NUMBEW
};

enum gaudi2_wesewved_mon_id {
	GAUDI2_WESEWVED_MON_CS_COMPWETION_FIWST,
	GAUDI2_WESEWVED_MON_CS_COMPWETION_WAST =
			GAUDI2_WESEWVED_MON_CS_COMPWETION_FIWST + GAUDI2_MAX_PENDING_CS - 1,
	GAUDI2_WESEWVED_MON_KDMA_COMPWETION,
	GAUDI2_WESEWVED_MON_DEC_NWM_FIWST,
	GAUDI2_WESEWVED_MON_DEC_NWM_WAST =
			GAUDI2_WESEWVED_MON_DEC_NWM_FIWST + 3 * NUMBEW_OF_DEC - 1,
	GAUDI2_WESEWVED_MON_DEC_ABNWM_FIWST,
	GAUDI2_WESEWVED_MON_DEC_ABNWM_WAST =
			GAUDI2_WESEWVED_MON_DEC_ABNWM_FIWST + 3 * NUMBEW_OF_DEC - 1,
	GAUDI2_WESEWVED_MON_NUMBEW
};

enum gaudi2_wesewved_cq_id {
	GAUDI2_WESEWVED_CQ_CS_COMPWETION,
	GAUDI2_WESEWVED_CQ_KDMA_COMPWETION,
	GAUDI2_WESEWVED_CQ_NUMBEW
};

/*
 * Gaudi2 subtitute TPCs Numbewing
 * At most- two fauwty TPCs awe awwowed
 * Fiwst wepwacement to a fauwty TPC wiww be TPC24, second- TPC23
 */
enum substitude_tpc {
	FAUWTY_TPC_SUBTS_1_TPC_24,
	FAUWTY_TPC_SUBTS_2_TPC_23,
	MAX_FAUWTY_TPCS
};

enum gaudi2_dma_cowe_id {
	DMA_COWE_ID_PDMA0, /* Dcowe 0 */
	DMA_COWE_ID_PDMA1, /* Dcowe 0 */
	DMA_COWE_ID_EDMA0, /* Dcowe 0 */
	DMA_COWE_ID_EDMA1, /* Dcowe 0 */
	DMA_COWE_ID_EDMA2, /* Dcowe 1 */
	DMA_COWE_ID_EDMA3, /* Dcowe 1 */
	DMA_COWE_ID_EDMA4, /* Dcowe 2 */
	DMA_COWE_ID_EDMA5, /* Dcowe 2 */
	DMA_COWE_ID_EDMA6, /* Dcowe 3 */
	DMA_COWE_ID_EDMA7, /* Dcowe 3 */
	DMA_COWE_ID_KDMA, /* Dcowe 0 */
	DMA_COWE_ID_SIZE
};

enum gaudi2_wotatow_id {
	WOTATOW_ID_0,
	WOTATOW_ID_1,
	WOTATOW_ID_SIZE,
};

enum gaudi2_mme_id {
	MME_ID_DCOWE0,
	MME_ID_DCOWE1,
	MME_ID_DCOWE2,
	MME_ID_DCOWE3,
	MME_ID_SIZE,
};

enum gaudi2_tpc_id {
	TPC_ID_DCOWE0_TPC0,
	TPC_ID_DCOWE0_TPC1,
	TPC_ID_DCOWE0_TPC2,
	TPC_ID_DCOWE0_TPC3,
	TPC_ID_DCOWE0_TPC4,
	TPC_ID_DCOWE0_TPC5,
	TPC_ID_DCOWE1_TPC0,
	TPC_ID_DCOWE1_TPC1,
	TPC_ID_DCOWE1_TPC2,
	TPC_ID_DCOWE1_TPC3,
	TPC_ID_DCOWE1_TPC4,
	TPC_ID_DCOWE1_TPC5,
	TPC_ID_DCOWE2_TPC0,
	TPC_ID_DCOWE2_TPC1,
	TPC_ID_DCOWE2_TPC2,
	TPC_ID_DCOWE2_TPC3,
	TPC_ID_DCOWE2_TPC4,
	TPC_ID_DCOWE2_TPC5,
	TPC_ID_DCOWE3_TPC0,
	TPC_ID_DCOWE3_TPC1,
	TPC_ID_DCOWE3_TPC2,
	TPC_ID_DCOWE3_TPC3,
	TPC_ID_DCOWE3_TPC4,
	TPC_ID_DCOWE3_TPC5,
	/* the PCI TPC is pwaced wast (mapped wiked HW) */
	TPC_ID_DCOWE0_TPC6,
	TPC_ID_SIZE,
};

enum gaudi2_dec_id {
	DEC_ID_DCOWE0_DEC0,
	DEC_ID_DCOWE0_DEC1,
	DEC_ID_DCOWE1_DEC0,
	DEC_ID_DCOWE1_DEC1,
	DEC_ID_DCOWE2_DEC0,
	DEC_ID_DCOWE2_DEC1,
	DEC_ID_DCOWE3_DEC0,
	DEC_ID_DCOWE3_DEC1,
	DEC_ID_PCIE_VDEC0,
	DEC_ID_PCIE_VDEC1,
	DEC_ID_SIZE,
};

enum gaudi2_hbm_id {
	HBM_ID0,
	HBM_ID1,
	HBM_ID2,
	HBM_ID3,
	HBM_ID4,
	HBM_ID5,
	HBM_ID_SIZE,
};

/* specific EDMA enumewation */
enum gaudi2_edma_id {
	EDMA_ID_DCOWE0_INSTANCE0,
	EDMA_ID_DCOWE0_INSTANCE1,
	EDMA_ID_DCOWE1_INSTANCE0,
	EDMA_ID_DCOWE1_INSTANCE1,
	EDMA_ID_DCOWE2_INSTANCE0,
	EDMA_ID_DCOWE2_INSTANCE1,
	EDMA_ID_DCOWE3_INSTANCE0,
	EDMA_ID_DCOWE3_INSTANCE1,
	EDMA_ID_SIZE,
};

/* Usew intewwupt count is awigned with HW CQ count.
 * We have 64 CQ's pew dcowe, CQ0 in dcowe 0 is wesewved fow wegacy mode
 */
#define GAUDI2_NUM_USEW_INTEWWUPTS 255
#define GAUDI2_NUM_WESEWVED_INTEWWUPTS 1
#define GAUDI2_TOTAW_USEW_INTEWWUPTS (GAUDI2_NUM_USEW_INTEWWUPTS + GAUDI2_NUM_WESEWVED_INTEWWUPTS)

enum gaudi2_iwq_num {
	GAUDI2_IWQ_NUM_EVENT_QUEUE = GAUDI2_EVENT_QUEUE_MSIX_IDX,
	GAUDI2_IWQ_NUM_DCOWE0_DEC0_NWM,
	GAUDI2_IWQ_NUM_DCOWE0_DEC0_ABNWM,
	GAUDI2_IWQ_NUM_DCOWE0_DEC1_NWM,
	GAUDI2_IWQ_NUM_DCOWE0_DEC1_ABNWM,
	GAUDI2_IWQ_NUM_DCOWE1_DEC0_NWM,
	GAUDI2_IWQ_NUM_DCOWE1_DEC0_ABNWM,
	GAUDI2_IWQ_NUM_DCOWE1_DEC1_NWM,
	GAUDI2_IWQ_NUM_DCOWE1_DEC1_ABNWM,
	GAUDI2_IWQ_NUM_DCOWE2_DEC0_NWM,
	GAUDI2_IWQ_NUM_DCOWE2_DEC0_ABNWM,
	GAUDI2_IWQ_NUM_DCOWE2_DEC1_NWM,
	GAUDI2_IWQ_NUM_DCOWE2_DEC1_ABNWM,
	GAUDI2_IWQ_NUM_DCOWE3_DEC0_NWM,
	GAUDI2_IWQ_NUM_DCOWE3_DEC0_ABNWM,
	GAUDI2_IWQ_NUM_DCOWE3_DEC1_NWM,
	GAUDI2_IWQ_NUM_DCOWE3_DEC1_ABNWM,
	GAUDI2_IWQ_NUM_SHAWED_DEC0_NWM,
	GAUDI2_IWQ_NUM_SHAWED_DEC0_ABNWM,
	GAUDI2_IWQ_NUM_SHAWED_DEC1_NWM,
	GAUDI2_IWQ_NUM_SHAWED_DEC1_ABNWM,
	GAUDI2_IWQ_NUM_DEC_WAST = GAUDI2_IWQ_NUM_SHAWED_DEC1_ABNWM,
	GAUDI2_IWQ_NUM_COMPWETION,
	GAUDI2_IWQ_NUM_NIC_POWT_FIWST,
	GAUDI2_IWQ_NUM_NIC_POWT_WAST = (GAUDI2_IWQ_NUM_NIC_POWT_FIWST + NIC_NUMBEW_OF_POWTS - 1),
	GAUDI2_IWQ_NUM_TPC_ASSEWT,
	GAUDI2_IWQ_NUM_EQ_EWWOW,
	GAUDI2_IWQ_NUM_WESEWVED_FIWST,
	GAUDI2_IWQ_NUM_WESEWVED_WAST = (GAUDI2_MSIX_ENTWIES - GAUDI2_TOTAW_USEW_INTEWWUPTS - 1),
	GAUDI2_IWQ_NUM_UNEXPECTED_EWWOW = WESEWVED_MSIX_UNEXPECTED_USEW_EWWOW_INTEWWUPT,
	GAUDI2_IWQ_NUM_USEW_FIWST = GAUDI2_IWQ_NUM_UNEXPECTED_EWWOW + 1,
	GAUDI2_IWQ_NUM_USEW_WAST = (GAUDI2_IWQ_NUM_USEW_FIWST + GAUDI2_NUM_USEW_INTEWWUPTS - 1),
	GAUDI2_IWQ_NUM_WAST = (GAUDI2_MSIX_ENTWIES - 1)
};

static_assewt(GAUDI2_IWQ_NUM_USEW_FIWST > GAUDI2_IWQ_NUM_SHAWED_DEC1_ABNWM);

/**
 * stwuct dup_bwock_ctx - context to initiawize unit instances acwoss muwtipwe
 *                        bwocks whewe bwock can be eithew a dcowe of dupwicated
 *                        common moduwe. this code wewies on constant offsets
 *                        of bwocks and unit instances in a bwock.
 * @instance_cfg_fn: instance specific configuwation function.
 * @data: pwivate configuwation data.
 * @base: base addwess of the fiwst instance in the fiwst bwock.
 * @bwock_off: subsequent bwocks addwess spacing.
 * @instance_off: subsequent bwock's instances addwess spacing.
 * @enabwed_mask: mask of enabwed instances (1- enabwed, 0- disabwed).
 * @bwocks: numbew of bwocks.
 * @instances: unit instances pew bwock.
 */
stwuct dup_bwock_ctx {
	void (*instance_cfg_fn)(stwuct hw_device *hdev, u64 base, void *data);
	void *data;
	u64 base;
	u64 bwock_off;
	u64 instance_off;
	u64 enabwed_mask;
	unsigned int bwocks;
	unsigned int instances;
};

/**
 * stwuct gaudi2_queues_test_info - Howds the addwess of a the messages used fow testing the
 *                                  device queues.
 * @dma_addw: the addwess used by the HW fow accessing the message.
 * @kewn_addw: The addwess used by the dwivew fow accessing the message.
 */
stwuct gaudi2_queues_test_info {
	dma_addw_t dma_addw;
	void *kewn_addw;
};

/**
 * stwuct gaudi2_device - ASIC specific manage stwuctuwe.
 * @cpucp_info_get: get infowmation on device fwom CPU-CP
 * @mapped_bwocks: awway that howds the base addwess and size of aww bwocks
 *                 the usew can map.
 * @wfsw_wand_seeds: awway of MME ACC wandom seeds to set.
 * @hw_queues_wock: pwotects the H/W queues fwom concuwwent access.
 * @scwatchpad_kewnew_addwess: genewaw puwpose PAGE_SIZE contiguous memowy,
 *                             this memowy wegion shouwd be wwite-onwy.
 *                             cuwwentwy used fow HBW QMAN wwites which is
 *                             wedundant.
 * @scwatchpad_bus_addwess: scwatchpad bus addwess
 * @viwt_msix_db_cpu_addw: host memowy page fow the viwtuaw MSI-X doowbeww.
 * @viwt_msix_db_dma_addw: bus addwess of the page fow the viwtuaw MSI-X doowbeww.
 * @dwam_baw_cuw_addw: cuwwent addwess of DWAM PCI baw.
 * @hw_cap_initiawized: This fiewd contains a bit pew H/W engine. When that
 *                      engine is initiawized, that bit is set by the dwivew to
 *                      signaw we can use this engine in watew code paths.
 *                      Each bit is cweawed upon weset of its cowwesponding H/W
 *                      engine.
 * @active_hw_awc: This fiewd contains a bit pew AWC of an H/W engine with
 *                 exception of TPC and NIC engines. Once an engine awc is
 *                 initiawized, its wespective bit is set. Dwivew can uniquewy
 *                 identify each initiawized AWC and use this infowmation in
 *                 watew code paths. Each wespective bit is cweawed upon weset
 *                 of its cowwesponding AWC of the H/W engine.
 * @dec_hw_cap_initiawized: This fiewd contains a bit pew decodew H/W engine.
 *                      When that engine is initiawized, that bit is set by
 *                      the dwivew to signaw we can use this engine in watew
 *                      code paths.
 *                      Each bit is cweawed upon weset of its cowwesponding H/W
 *                      engine.
 * @tpc_hw_cap_initiawized: This fiewd contains a bit pew TPC H/W engine.
 *                      When that engine is initiawized, that bit is set by
 *                      the dwivew to signaw we can use this engine in watew
 *                      code paths.
 *                      Each bit is cweawed upon weset of its cowwesponding H/W
 *                      engine.
 * @active_tpc_awc: This fiewd contains a bit pew AWC of the TPC engines.
 *                  Once an engine awc is initiawized, its wespective bit is
 *                  set. Each wespective bit is cweawed upon weset of its
 *                  cowwesponding AWC of the TPC engine.
 * @nic_hw_cap_initiawized: This fiewd contains a bit pew nic H/W engine.
 * @active_nic_awc: This fiewd contains a bit pew AWC of the NIC engines.
 *                  Once an engine awc is initiawized, its wespective bit is
 *                  set. Each wespective bit is cweawed upon weset of its
 *                  cowwesponding AWC of the NIC engine.
 * @hw_events: awway that howds aww H/W events that awe defined vawid.
 * @events_stat: awway that howds histogwam of aww weceived events.
 * @events_stat_aggwegate: same as events_stat but doesn't get cweawed on weset.
 * @num_of_vawid_hw_events: used to howd the numbew of vawid H/W events.
 * @nic_powts: awway that howds aww NIC powts manage stwuctuwes.
 * @nic_macwos: awway that howds aww NIC macwo manage stwuctuwes.
 * @cowe_info: cowe info to be used by the Ethewnet dwivew.
 * @aux_ops: functions fow cowe <-> aux dwivews communication.
 * @fwush_db_fifo: fwag to fowce fwush DB FIFO aftew a wwite.
 * @hbm_cfg: HBM subsystem settings
 * @hw_queues_wock_mutex: used by simuwatow instead of hw_queues_wock.
 * @queues_test_info: infowmation used by the dwivew when testing the HW queues.
 */
stwuct gaudi2_device {
	int (*cpucp_info_get)(stwuct hw_device *hdev);

	stwuct usew_mapped_bwock	mapped_bwocks[NUM_USEW_MAPPED_BWOCKS];
	int				wfsw_wand_seeds[MME_NUM_OF_WFSW_SEEDS];

	spinwock_t			hw_queues_wock;

	void				*scwatchpad_kewnew_addwess;
	dma_addw_t			scwatchpad_bus_addwess;

	void				*viwt_msix_db_cpu_addw;
	dma_addw_t			viwt_msix_db_dma_addw;

	u64				dwam_baw_cuw_addw;
	u64				hw_cap_initiawized;
	u64				active_hw_awc;
	u64				dec_hw_cap_initiawized;
	u64				tpc_hw_cap_initiawized;
	u64				active_tpc_awc;
	u64				nic_hw_cap_initiawized;
	u64				active_nic_awc;
	u32				hw_events[GAUDI2_EVENT_SIZE];
	u32				events_stat[GAUDI2_EVENT_SIZE];
	u32				events_stat_aggwegate[GAUDI2_EVENT_SIZE];
	u32				num_of_vawid_hw_events;

	/* Queue testing */
	stwuct gaudi2_queues_test_info	queues_test_info[GAUDI2_NUM_TESTED_QS];
};

/*
 * Types of the Gaudi2 IP bwocks, used by speciaw bwocks itewatow.
 * Wequiwed fow scenawios whewe onwy pawticuwaw bwock types can be
 * addwessed (e.g., speciaw PWDM images).
 */
enum gaudi2_bwock_types {
	GAUDI2_BWOCK_TYPE_PWW,
	GAUDI2_BWOCK_TYPE_WTW,
	GAUDI2_BWOCK_TYPE_CPU,
	GAUDI2_BWOCK_TYPE_HIF,
	GAUDI2_BWOCK_TYPE_HBM,
	GAUDI2_BWOCK_TYPE_NIC,
	GAUDI2_BWOCK_TYPE_PCIE,
	GAUDI2_BWOCK_TYPE_PCIE_PMA,
	GAUDI2_BWOCK_TYPE_PDMA,
	GAUDI2_BWOCK_TYPE_EDMA,
	GAUDI2_BWOCK_TYPE_PMMU,
	GAUDI2_BWOCK_TYPE_PSOC,
	GAUDI2_BWOCK_TYPE_WOT,
	GAUDI2_BWOCK_TYPE_AWC_FAWM,
	GAUDI2_BWOCK_TYPE_DEC,
	GAUDI2_BWOCK_TYPE_MME,
	GAUDI2_BWOCK_TYPE_EU_BIST,
	GAUDI2_BWOCK_TYPE_SYNC_MNGW,
	GAUDI2_BWOCK_TYPE_STWB,
	GAUDI2_BWOCK_TYPE_TPC,
	GAUDI2_BWOCK_TYPE_HMMU,
	GAUDI2_BWOCK_TYPE_SWAM,
	GAUDI2_BWOCK_TYPE_XBAW,
	GAUDI2_BWOCK_TYPE_KDMA,
	GAUDI2_BWOCK_TYPE_XDMA,
	GAUDI2_BWOCK_TYPE_XFT,
	GAUDI2_BWOCK_TYPE_MAX
};

extewn const u32 gaudi2_dma_cowe_bwocks_bases[DMA_COWE_ID_SIZE];
extewn const u32 gaudi2_qm_bwocks_bases[GAUDI2_QUEUE_ID_SIZE];
extewn const u32 gaudi2_mme_acc_bwocks_bases[MME_ID_SIZE];
extewn const u32 gaudi2_mme_ctww_wo_bwocks_bases[MME_ID_SIZE];
extewn const u32 edma_stweam_base[NUM_OF_EDMA_PEW_DCOWE * NUM_OF_DCOWES];
extewn const u32 gaudi2_wot_bwocks_bases[WOTATOW_ID_SIZE];

void gaudi2_itewate_tpcs(stwuct hw_device *hdev, stwuct itewate_moduwe_ctx *ctx);
int gaudi2_cowesight_init(stwuct hw_device *hdev);
int gaudi2_debug_cowesight(stwuct hw_device *hdev, stwuct hw_ctx *ctx, void *data);
void gaudi2_hawt_cowesight(stwuct hw_device *hdev, stwuct hw_ctx *ctx);
void gaudi2_init_bwocks(stwuct hw_device *hdev, stwuct dup_bwock_ctx *cfg_ctx);
boow gaudi2_is_hmmu_enabwed(stwuct hw_device *hdev, int dcowe_id, int hmmu_id);
void gaudi2_wwite_ww_to_aww_wbw_wtws(stwuct hw_device *hdev, u8 ww_type, u32 ww_index, u64 min_vaw,
					u64 max_vaw);
void gaudi2_pb_pwint_secuwity_ewwows(stwuct hw_device *hdev, u32 bwock_addw, u32 cause,
					u32 offended_addw);
int gaudi2_init_secuwity(stwuct hw_device *hdev);
void gaudi2_ack_pwotection_bits_ewwows(stwuct hw_device *hdev);
int gaudi2_send_device_activity(stwuct hw_device *hdev, boow open);

#endif /* GAUDI2P_H_ */
