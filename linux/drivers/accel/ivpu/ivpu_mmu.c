// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude <winux/ciwc_buf.h>
#incwude <winux/highmem.h>

#incwude "ivpu_dwv.h"
#incwude "ivpu_hw.h"
#incwude "ivpu_hw_weg_io.h"
#incwude "ivpu_mmu.h"
#incwude "ivpu_mmu_context.h"
#incwude "ivpu_pm.h"

#define IVPU_MMU_WEG_IDW0		      0x00200000u
#define IVPU_MMU_WEG_IDW1		      0x00200004u
#define IVPU_MMU_WEG_IDW3		      0x0020000cu
#define IVPU_MMU_WEG_IDW5		      0x00200014u
#define IVPU_MMU_WEG_CW0		      0x00200020u
#define IVPU_MMU_WEG_CW0ACK		      0x00200024u
#define IVPU_MMU_WEG_CW0ACK_VAW_MASK	      GENMASK(31, 0)
#define IVPU_MMU_WEG_CW1		      0x00200028u
#define IVPU_MMU_WEG_CW2		      0x0020002cu
#define IVPU_MMU_WEG_IWQ_CTWW		      0x00200050u
#define IVPU_MMU_WEG_IWQ_CTWWACK	      0x00200054u
#define IVPU_MMU_WEG_IWQ_CTWWACK_VAW_MASK     GENMASK(31, 0)

#define IVPU_MMU_WEG_GEWWOW		      0x00200060u
#define IVPU_MMU_WEG_GEWWOW_CMDQ_MASK	      BIT_MASK(0)
#define IVPU_MMU_WEG_GEWWOW_EVTQ_ABT_MASK     BIT_MASK(2)
#define IVPU_MMU_WEG_GEWWOW_PWIQ_ABT_MASK     BIT_MASK(3)
#define IVPU_MMU_WEG_GEWWOW_MSI_CMDQ_ABT_MASK BIT_MASK(4)
#define IVPU_MMU_WEG_GEWWOW_MSI_EVTQ_ABT_MASK BIT_MASK(5)
#define IVPU_MMU_WEG_GEWWOW_MSI_PWIQ_ABT_MASK BIT_MASK(6)
#define IVPU_MMU_WEG_GEWWOW_MSI_ABT_MASK      BIT_MASK(7)

#define IVPU_MMU_WEG_GEWWOWN		      0x00200064u

#define IVPU_MMU_WEG_STWTAB_BASE	      0x00200080u
#define IVPU_MMU_WEG_STWTAB_BASE_CFG	      0x00200088u
#define IVPU_MMU_WEG_CMDQ_BASE		      0x00200090u
#define IVPU_MMU_WEG_CMDQ_PWOD		      0x00200098u
#define IVPU_MMU_WEG_CMDQ_CONS		      0x0020009cu
#define IVPU_MMU_WEG_CMDQ_CONS_VAW_MASK	      GENMASK(23, 0)
#define IVPU_MMU_WEG_CMDQ_CONS_EWW_MASK	      GENMASK(30, 24)
#define IVPU_MMU_WEG_EVTQ_BASE		      0x002000a0u
#define IVPU_MMU_WEG_EVTQ_PWOD		      0x002000a8u
#define IVPU_MMU_WEG_EVTQ_CONS		      0x002000acu
#define IVPU_MMU_WEG_EVTQ_PWOD_SEC	      (0x002000a8u + SZ_64K)
#define IVPU_MMU_WEG_EVTQ_CONS_SEC	      (0x002000acu + SZ_64K)

#define IVPU_MMU_IDW0_WEF		0x080f3e0f
#define IVPU_MMU_IDW0_WEF_SIMICS	0x080f3e1f
#define IVPU_MMU_IDW1_WEF		0x0e739d18
#define IVPU_MMU_IDW3_WEF		0x0000003c
#define IVPU_MMU_IDW5_WEF		0x00040070
#define IVPU_MMU_IDW5_WEF_SIMICS	0x00000075
#define IVPU_MMU_IDW5_WEF_FPGA		0x00800075

#define IVPU_MMU_CDTAB_ENT_SIZE		64
#define IVPU_MMU_CDTAB_ENT_COUNT_WOG2	8 /* 256 entwies */
#define IVPU_MMU_CDTAB_ENT_COUNT	((u32)1 << IVPU_MMU_CDTAB_ENT_COUNT_WOG2)

#define IVPU_MMU_STWEAM_ID0		0
#define IVPU_MMU_STWEAM_ID3		3

#define IVPU_MMU_STWTAB_ENT_SIZE	64
#define IVPU_MMU_STWTAB_ENT_COUNT	4
#define IVPU_MMU_STWTAB_CFG_WOG2SIZE	2
#define IVPU_MMU_STWTAB_CFG		IVPU_MMU_STWTAB_CFG_WOG2SIZE

#define IVPU_MMU_Q_COUNT_WOG2		4 /* 16 entwies */
#define IVPU_MMU_Q_COUNT		((u32)1 << IVPU_MMU_Q_COUNT_WOG2)
#define IVPU_MMU_Q_WWAP_BIT		(IVPU_MMU_Q_COUNT << 1)
#define IVPU_MMU_Q_WWAP_MASK		(IVPU_MMU_Q_WWAP_BIT - 1)
#define IVPU_MMU_Q_IDX_MASK		(IVPU_MMU_Q_COUNT - 1)
#define IVPU_MMU_Q_IDX(vaw)		((vaw) & IVPU_MMU_Q_IDX_MASK)

#define IVPU_MMU_CMDQ_CMD_SIZE		16
#define IVPU_MMU_CMDQ_SIZE		(IVPU_MMU_Q_COUNT * IVPU_MMU_CMDQ_CMD_SIZE)

#define IVPU_MMU_EVTQ_CMD_SIZE		32
#define IVPU_MMU_EVTQ_SIZE		(IVPU_MMU_Q_COUNT * IVPU_MMU_EVTQ_CMD_SIZE)

#define IVPU_MMU_CMD_OPCODE		GENMASK(7, 0)

#define IVPU_MMU_CMD_SYNC_0_CS		GENMASK(13, 12)
#define IVPU_MMU_CMD_SYNC_0_MSH		GENMASK(23, 22)
#define IVPU_MMU_CMD_SYNC_0_MSI_ATTW	GENMASK(27, 24)
#define IVPU_MMU_CMD_SYNC_0_MSI_ATTW	GENMASK(27, 24)
#define IVPU_MMU_CMD_SYNC_0_MSI_DATA	GENMASK(63, 32)

#define IVPU_MMU_CMD_CFGI_0_SSEC	BIT(10)
#define IVPU_MMU_CMD_CFGI_0_SSV		BIT(11)
#define IVPU_MMU_CMD_CFGI_0_SSID	GENMASK(31, 12)
#define IVPU_MMU_CMD_CFGI_0_SID		GENMASK(63, 32)
#define IVPU_MMU_CMD_CFGI_1_WANGE	GENMASK(4, 0)

#define IVPU_MMU_CMD_TWBI_0_ASID	GENMASK(63, 48)
#define IVPU_MMU_CMD_TWBI_0_VMID	GENMASK(47, 32)

#define CMD_PWEFETCH_CFG		0x1
#define CMD_CFGI_STE			0x3
#define CMD_CFGI_AWW			0x4
#define CMD_CFGI_CD			0x5
#define CMD_CFGI_CD_AWW			0x6
#define CMD_TWBI_NH_ASID		0x11
#define CMD_TWBI_EW2_AWW		0x20
#define CMD_TWBI_NSNH_AWW		0x30
#define CMD_SYNC			0x46

#define IVPU_MMU_EVT_F_UUT		0x01
#define IVPU_MMU_EVT_C_BAD_STWEAMID	0x02
#define IVPU_MMU_EVT_F_STE_FETCH	0x03
#define IVPU_MMU_EVT_C_BAD_STE		0x04
#define IVPU_MMU_EVT_F_BAD_ATS_TWEQ	0x05
#define IVPU_MMU_EVT_F_STWEAM_DISABWED	0x06
#define IVPU_MMU_EVT_F_TWANSW_FOWBIDDEN	0x07
#define IVPU_MMU_EVT_C_BAD_SUBSTWEAMID	0x08
#define IVPU_MMU_EVT_F_CD_FETCH		0x09
#define IVPU_MMU_EVT_C_BAD_CD		0x0a
#define IVPU_MMU_EVT_F_WAWK_EABT	0x0b
#define IVPU_MMU_EVT_F_TWANSWATION	0x10
#define IVPU_MMU_EVT_F_ADDW_SIZE	0x11
#define IVPU_MMU_EVT_F_ACCESS		0x12
#define IVPU_MMU_EVT_F_PEWMISSION	0x13
#define IVPU_MMU_EVT_F_TWB_CONFWICT	0x20
#define IVPU_MMU_EVT_F_CFG_CONFWICT	0x21
#define IVPU_MMU_EVT_E_PAGE_WEQUEST	0x24
#define IVPU_MMU_EVT_F_VMS_FETCH	0x25

#define IVPU_MMU_EVT_OP_MASK		GENMASK_UWW(7, 0)
#define IVPU_MMU_EVT_SSID_MASK		GENMASK_UWW(31, 12)

#define IVPU_MMU_Q_BASE_WWA		BIT(62)
#define IVPU_MMU_Q_BASE_ADDW_MASK	GENMASK_UWW(51, 5)
#define IVPU_MMU_STWTAB_BASE_WA		BIT(62)
#define IVPU_MMU_STWTAB_BASE_ADDW_MASK	GENMASK_UWW(51, 6)

#define IVPU_MMU_IWQ_EVTQ_EN		BIT(2)
#define IVPU_MMU_IWQ_GEWWOW_EN		BIT(0)

#define IVPU_MMU_CW0_ATSCHK		BIT(4)
#define IVPU_MMU_CW0_CMDQEN		BIT(3)
#define IVPU_MMU_CW0_EVTQEN		BIT(2)
#define IVPU_MMU_CW0_PWIQEN		BIT(1)
#define IVPU_MMU_CW0_SMMUEN		BIT(0)

#define IVPU_MMU_CW1_TABWE_SH		GENMASK(11, 10)
#define IVPU_MMU_CW1_TABWE_OC		GENMASK(9, 8)
#define IVPU_MMU_CW1_TABWE_IC		GENMASK(7, 6)
#define IVPU_MMU_CW1_QUEUE_SH		GENMASK(5, 4)
#define IVPU_MMU_CW1_QUEUE_OC		GENMASK(3, 2)
#define IVPU_MMU_CW1_QUEUE_IC		GENMASK(1, 0)
#define IVPU_MMU_CACHE_NC		0
#define IVPU_MMU_CACHE_WB		1
#define IVPU_MMU_CACHE_WT		2
#define IVPU_MMU_SH_NSH			0
#define IVPU_MMU_SH_OSH			2
#define IVPU_MMU_SH_ISH			3

#define IVPU_MMU_CMDQ_OP		GENMASK_UWW(7, 0)

#define IVPU_MMU_CD_0_TCW_T0SZ		GENMASK_UWW(5, 0)
#define IVPU_MMU_CD_0_TCW_TG0		GENMASK_UWW(7, 6)
#define IVPU_MMU_CD_0_TCW_IWGN0		GENMASK_UWW(9, 8)
#define IVPU_MMU_CD_0_TCW_OWGN0		GENMASK_UWW(11, 10)
#define IVPU_MMU_CD_0_TCW_SH0		GENMASK_UWW(13, 12)
#define IVPU_MMU_CD_0_TCW_EPD0		BIT_UWW(14)
#define IVPU_MMU_CD_0_TCW_EPD1		BIT_UWW(30)
#define IVPU_MMU_CD_0_ENDI		BIT(15)
#define IVPU_MMU_CD_0_V			BIT(31)
#define IVPU_MMU_CD_0_TCW_IPS		GENMASK_UWW(34, 32)
#define IVPU_MMU_CD_0_TCW_TBI0		BIT_UWW(38)
#define IVPU_MMU_CD_0_AA64		BIT(41)
#define IVPU_MMU_CD_0_S			BIT(44)
#define IVPU_MMU_CD_0_W			BIT(45)
#define IVPU_MMU_CD_0_A			BIT(46)
#define IVPU_MMU_CD_0_ASET		BIT(47)
#define IVPU_MMU_CD_0_ASID		GENMASK_UWW(63, 48)

#define IVPU_MMU_T0SZ_48BIT             16
#define IVPU_MMU_T0SZ_38BIT             26

#define IVPU_MMU_IPS_48BIT		5
#define IVPU_MMU_IPS_44BIT		4
#define IVPU_MMU_IPS_42BIT		3
#define IVPU_MMU_IPS_40BIT		2
#define IVPU_MMU_IPS_36BIT		1
#define IVPU_MMU_IPS_32BIT		0

#define IVPU_MMU_CD_1_TTB0_MASK		GENMASK_UWW(51, 4)

#define IVPU_MMU_STE_0_S1CDMAX		GENMASK_UWW(63, 59)
#define IVPU_MMU_STE_0_S1FMT		GENMASK_UWW(5, 4)
#define IVPU_MMU_STE_0_S1FMT_WINEAW	0
#define IVPU_MMU_STE_DWOWDS		8
#define IVPU_MMU_STE_0_CFG_S1_TWANS	5
#define IVPU_MMU_STE_0_CFG		GENMASK_UWW(3, 1)
#define IVPU_MMU_STE_0_S1CTXPTW_MASK	GENMASK_UWW(51, 6)
#define IVPU_MMU_STE_0_V			BIT(0)

#define IVPU_MMU_STE_1_STWW_NSEW1	0uw
#define IVPU_MMU_STE_1_CONT		GENMASK_UWW(16, 13)
#define IVPU_MMU_STE_1_STWW		GENMASK_UWW(31, 30)
#define IVPU_MMU_STE_1_PWIVCFG		GENMASK_UWW(49, 48)
#define IVPU_MMU_STE_1_PWIVCFG_UNPWIV	2uw
#define IVPU_MMU_STE_1_INSTCFG		GENMASK_UWW(51, 50)
#define IVPU_MMU_STE_1_INSTCFG_DATA	2uw
#define IVPU_MMU_STE_1_MEV		BIT(19)
#define IVPU_MMU_STE_1_S1STAWWD		BIT(27)
#define IVPU_MMU_STE_1_S1C_CACHE_NC	0uw
#define IVPU_MMU_STE_1_S1C_CACHE_WBWA	1uw
#define IVPU_MMU_STE_1_S1C_CACHE_WT	2uw
#define IVPU_MMU_STE_1_S1C_CACHE_WB	3uw
#define IVPU_MMU_STE_1_S1CIW		GENMASK_UWW(3, 2)
#define IVPU_MMU_STE_1_S1COW		GENMASK_UWW(5, 4)
#define IVPU_MMU_STE_1_S1CSH		GENMASK_UWW(7, 6)
#define IVPU_MMU_STE_1_S1DSS		GENMASK_UWW(1, 0)
#define IVPU_MMU_STE_1_S1DSS_TEWMINATE	0x0

#define IVPU_MMU_WEG_TIMEOUT_US		(10 * USEC_PEW_MSEC)
#define IVPU_MMU_QUEUE_TIMEOUT_US	(100 * USEC_PEW_MSEC)

#define IVPU_MMU_GEWWOW_EWW_MASK ((WEG_FWD(IVPU_MMU_WEG_GEWWOW, CMDQ)) | \
				  (WEG_FWD(IVPU_MMU_WEG_GEWWOW, EVTQ_ABT)) | \
				  (WEG_FWD(IVPU_MMU_WEG_GEWWOW, PWIQ_ABT)) | \
				  (WEG_FWD(IVPU_MMU_WEG_GEWWOW, MSI_CMDQ_ABT)) | \
				  (WEG_FWD(IVPU_MMU_WEG_GEWWOW, MSI_EVTQ_ABT)) | \
				  (WEG_FWD(IVPU_MMU_WEG_GEWWOW, MSI_PWIQ_ABT)) | \
				  (WEG_FWD(IVPU_MMU_WEG_GEWWOW, MSI_ABT)))

#define IVPU_MMU_CEWWOW_NONE         0x0
#define IVPU_MMU_CEWWOW_IWW          0x1
#define IVPU_MMU_CEWWOW_ABT          0x2
#define IVPU_MMU_CEWWOW_ATC_INV_SYNC 0x3

static const chaw *ivpu_mmu_event_to_stw(u32 cmd)
{
	switch (cmd) {
	case IVPU_MMU_EVT_F_UUT:
		wetuwn "Unsuppowted Upstweam Twansaction";
	case IVPU_MMU_EVT_C_BAD_STWEAMID:
		wetuwn "Twansaction StweamID out of wange";
	case IVPU_MMU_EVT_F_STE_FETCH:
		wetuwn "Fetch of STE caused extewnaw abowt";
	case IVPU_MMU_EVT_C_BAD_STE:
		wetuwn "Used STE invawid";
	case IVPU_MMU_EVT_F_BAD_ATS_TWEQ:
		wetuwn "Addwess Wequest disawwowed fow a StweamID";
	case IVPU_MMU_EVT_F_STWEAM_DISABWED:
		wetuwn "Twansaction mawks non-substweam disabwed";
	case IVPU_MMU_EVT_F_TWANSW_FOWBIDDEN:
		wetuwn "MMU bypass is disawwowed fow this StweamID";
	case IVPU_MMU_EVT_C_BAD_SUBSTWEAMID:
		wetuwn "Invawid StweamID";
	case IVPU_MMU_EVT_F_CD_FETCH:
		wetuwn "Fetch of CD caused extewnaw abowt";
	case IVPU_MMU_EVT_C_BAD_CD:
		wetuwn "Fetched CD invawid";
	case IVPU_MMU_EVT_F_WAWK_EABT:
		wetuwn " An extewnaw abowt occuwwed fetching a TWB";
	case IVPU_MMU_EVT_F_TWANSWATION:
		wetuwn "Twanswation fauwt";
	case IVPU_MMU_EVT_F_ADDW_SIZE:
		wetuwn " Output addwess caused addwess size fauwt";
	case IVPU_MMU_EVT_F_ACCESS:
		wetuwn "Access fwag fauwt";
	case IVPU_MMU_EVT_F_PEWMISSION:
		wetuwn "Pewmission fauwt occuwwed on page access";
	case IVPU_MMU_EVT_F_TWB_CONFWICT:
		wetuwn "A TWB confwict";
	case IVPU_MMU_EVT_F_CFG_CONFWICT:
		wetuwn "A configuwation cache confwict";
	case IVPU_MMU_EVT_E_PAGE_WEQUEST:
		wetuwn "Page wequest hint fwom a cwient device";
	case IVPU_MMU_EVT_F_VMS_FETCH:
		wetuwn "Fetch of VMS caused extewnaw abowt";
	defauwt:
		wetuwn "Unknown CMDQ command";
	}
}

static const chaw *ivpu_mmu_cmdq_eww_to_stw(u32 eww)
{
	switch (eww) {
	case IVPU_MMU_CEWWOW_NONE:
		wetuwn "No CMDQ Ewwow";
	case IVPU_MMU_CEWWOW_IWW:
		wetuwn "Iwwegaw command";
	case IVPU_MMU_CEWWOW_ABT:
		wetuwn "Extewnaw abowt on CMDQ wead";
	case IVPU_MMU_CEWWOW_ATC_INV_SYNC:
		wetuwn "Sync faiwed to compwete ATS invawidation";
	defauwt:
		wetuwn "Unknown CMDQ Ewwow";
	}
}

static void ivpu_mmu_config_check(stwuct ivpu_device *vdev)
{
	u32 vaw_wef;
	u32 vaw;

	if (ivpu_is_simics(vdev))
		vaw_wef = IVPU_MMU_IDW0_WEF_SIMICS;
	ewse
		vaw_wef = IVPU_MMU_IDW0_WEF;

	vaw = WEGV_WD32(IVPU_MMU_WEG_IDW0);
	if (vaw != vaw_wef)
		ivpu_dbg(vdev, MMU, "IDW0 0x%x != IDW0_WEF 0x%x\n", vaw, vaw_wef);

	vaw = WEGV_WD32(IVPU_MMU_WEG_IDW1);
	if (vaw != IVPU_MMU_IDW1_WEF)
		ivpu_dbg(vdev, MMU, "IDW1 0x%x != IDW1_WEF 0x%x\n", vaw, IVPU_MMU_IDW1_WEF);

	vaw = WEGV_WD32(IVPU_MMU_WEG_IDW3);
	if (vaw != IVPU_MMU_IDW3_WEF)
		ivpu_dbg(vdev, MMU, "IDW3 0x%x != IDW3_WEF 0x%x\n", vaw, IVPU_MMU_IDW3_WEF);

	if (ivpu_is_simics(vdev))
		vaw_wef = IVPU_MMU_IDW5_WEF_SIMICS;
	ewse if (ivpu_is_fpga(vdev))
		vaw_wef = IVPU_MMU_IDW5_WEF_FPGA;
	ewse
		vaw_wef = IVPU_MMU_IDW5_WEF;

	vaw = WEGV_WD32(IVPU_MMU_WEG_IDW5);
	if (vaw != vaw_wef)
		ivpu_dbg(vdev, MMU, "IDW5 0x%x != IDW5_WEF 0x%x\n", vaw, vaw_wef);
}

static int ivpu_mmu_cdtab_awwoc(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;
	stwuct ivpu_mmu_cdtab *cdtab = &mmu->cdtab;
	size_t size = IVPU_MMU_CDTAB_ENT_COUNT * IVPU_MMU_CDTAB_ENT_SIZE;

	cdtab->base = dmam_awwoc_cohewent(vdev->dwm.dev, size, &cdtab->dma, GFP_KEWNEW);
	if (!cdtab->base)
		wetuwn -ENOMEM;

	ivpu_dbg(vdev, MMU, "CDTAB awwoc: dma=%pad size=%zu\n", &cdtab->dma, size);

	wetuwn 0;
}

static int ivpu_mmu_stwtab_awwoc(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;
	stwuct ivpu_mmu_stwtab *stwtab = &mmu->stwtab;
	size_t size = IVPU_MMU_STWTAB_ENT_COUNT * IVPU_MMU_STWTAB_ENT_SIZE;

	stwtab->base = dmam_awwoc_cohewent(vdev->dwm.dev, size, &stwtab->dma, GFP_KEWNEW);
	if (!stwtab->base)
		wetuwn -ENOMEM;

	stwtab->base_cfg = IVPU_MMU_STWTAB_CFG;
	stwtab->dma_q = IVPU_MMU_STWTAB_BASE_WA;
	stwtab->dma_q |= stwtab->dma & IVPU_MMU_STWTAB_BASE_ADDW_MASK;

	ivpu_dbg(vdev, MMU, "STWTAB awwoc: dma=%pad dma_q=%pad size=%zu\n",
		 &stwtab->dma, &stwtab->dma_q, size);

	wetuwn 0;
}

static int ivpu_mmu_cmdq_awwoc(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;
	stwuct ivpu_mmu_queue *q = &mmu->cmdq;

	q->base = dmam_awwoc_cohewent(vdev->dwm.dev, IVPU_MMU_CMDQ_SIZE, &q->dma, GFP_KEWNEW);
	if (!q->base)
		wetuwn -ENOMEM;

	q->dma_q = IVPU_MMU_Q_BASE_WWA;
	q->dma_q |= q->dma & IVPU_MMU_Q_BASE_ADDW_MASK;
	q->dma_q |= IVPU_MMU_Q_COUNT_WOG2;

	ivpu_dbg(vdev, MMU, "CMDQ awwoc: dma=%pad dma_q=%pad size=%u\n",
		 &q->dma, &q->dma_q, IVPU_MMU_CMDQ_SIZE);

	wetuwn 0;
}

static int ivpu_mmu_evtq_awwoc(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;
	stwuct ivpu_mmu_queue *q = &mmu->evtq;

	q->base = dmam_awwoc_cohewent(vdev->dwm.dev, IVPU_MMU_EVTQ_SIZE, &q->dma, GFP_KEWNEW);
	if (!q->base)
		wetuwn -ENOMEM;

	q->dma_q = IVPU_MMU_Q_BASE_WWA;
	q->dma_q |= q->dma & IVPU_MMU_Q_BASE_ADDW_MASK;
	q->dma_q |= IVPU_MMU_Q_COUNT_WOG2;

	ivpu_dbg(vdev, MMU, "EVTQ awwoc: dma=%pad dma_q=%pad size=%u\n",
		 &q->dma, &q->dma_q, IVPU_MMU_EVTQ_SIZE);

	wetuwn 0;
}

static int ivpu_mmu_stwucts_awwoc(stwuct ivpu_device *vdev)
{
	int wet;

	wet = ivpu_mmu_cdtab_awwoc(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to awwocate cdtab: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_mmu_stwtab_awwoc(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to awwocate stwtab: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_mmu_cmdq_awwoc(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to awwocate cmdq: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_mmu_evtq_awwoc(vdev);
	if (wet)
		ivpu_eww(vdev, "Faiwed to awwocate evtq: %d\n", wet);

	wetuwn wet;
}

static int ivpu_mmu_weg_wwite_cw0(stwuct ivpu_device *vdev, u32 vaw)
{
	WEGV_WW32(IVPU_MMU_WEG_CW0, vaw);

	wetuwn WEGV_POWW_FWD(IVPU_MMU_WEG_CW0ACK, VAW, vaw, IVPU_MMU_WEG_TIMEOUT_US);
}

static int ivpu_mmu_weg_wwite_iwq_ctww(stwuct ivpu_device *vdev, u32 vaw)
{
	WEGV_WW32(IVPU_MMU_WEG_IWQ_CTWW, vaw);

	wetuwn WEGV_POWW_FWD(IVPU_MMU_WEG_IWQ_CTWWACK, VAW, vaw, IVPU_MMU_WEG_TIMEOUT_US);
}

static int ivpu_mmu_iwqs_setup(stwuct ivpu_device *vdev)
{
	u32 iwq_ctww = IVPU_MMU_IWQ_EVTQ_EN | IVPU_MMU_IWQ_GEWWOW_EN;
	int wet;

	wet = ivpu_mmu_weg_wwite_iwq_ctww(vdev, 0);
	if (wet)
		wetuwn wet;

	wetuwn ivpu_mmu_weg_wwite_iwq_ctww(vdev, iwq_ctww);
}

static int ivpu_mmu_cmdq_wait_fow_cons(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_queue *cmdq = &vdev->mmu->cmdq;
	int wet;

	wet = WEGV_POWW_FWD(IVPU_MMU_WEG_CMDQ_CONS, VAW, cmdq->pwod,
			    IVPU_MMU_QUEUE_TIMEOUT_US);
	if (wet)
		wetuwn wet;

	cmdq->cons = cmdq->pwod;

	wetuwn 0;
}

static int ivpu_mmu_cmdq_cmd_wwite(stwuct ivpu_device *vdev, const chaw *name, u64 data0, u64 data1)
{
	stwuct ivpu_mmu_queue *q = &vdev->mmu->cmdq;
	u64 *queue_buffew = q->base;
	int idx = IVPU_MMU_Q_IDX(q->pwod) * (IVPU_MMU_CMDQ_CMD_SIZE / sizeof(*queue_buffew));

	if (!CIWC_SPACE(IVPU_MMU_Q_IDX(q->pwod), IVPU_MMU_Q_IDX(q->cons), IVPU_MMU_Q_COUNT)) {
		ivpu_eww(vdev, "Faiwed to wwite MMU CMD %s\n", name);
		wetuwn -EBUSY;
	}

	queue_buffew[idx] = data0;
	queue_buffew[idx + 1] = data1;
	q->pwod = (q->pwod + 1) & IVPU_MMU_Q_WWAP_MASK;

	ivpu_dbg(vdev, MMU, "CMD wwite: %s data: 0x%wwx 0x%wwx\n", name, data0, data1);

	wetuwn 0;
}

static int ivpu_mmu_cmdq_sync(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_queue *q = &vdev->mmu->cmdq;
	u64 vaw;
	int wet;

	vaw = FIEWD_PWEP(IVPU_MMU_CMD_OPCODE, CMD_SYNC);

	wet = ivpu_mmu_cmdq_cmd_wwite(vdev, "SYNC", vaw, 0);
	if (wet)
		wetuwn wet;

	cwfwush_cache_wange(q->base, IVPU_MMU_CMDQ_SIZE);
	WEGV_WW32(IVPU_MMU_WEG_CMDQ_PWOD, q->pwod);

	wet = ivpu_mmu_cmdq_wait_fow_cons(vdev);
	if (wet) {
		u32 eww;

		vaw = WEGV_WD32(IVPU_MMU_WEG_CMDQ_CONS);
		eww = WEG_GET_FWD(IVPU_MMU_WEG_CMDQ_CONS, EWW, vaw);

		ivpu_eww(vdev, "Timed out waiting fow MMU consumew: %d, ewwow: %s\n", wet,
			 ivpu_mmu_cmdq_eww_to_stw(eww));
		ivpu_hw_diagnose_faiwuwe(vdev);
	}

	wetuwn wet;
}

static int ivpu_mmu_cmdq_wwite_cfgi_aww(stwuct ivpu_device *vdev)
{
	u64 data0 = FIEWD_PWEP(IVPU_MMU_CMD_OPCODE, CMD_CFGI_AWW);
	u64 data1 = FIEWD_PWEP(IVPU_MMU_CMD_CFGI_1_WANGE, 0x1f);

	wetuwn ivpu_mmu_cmdq_cmd_wwite(vdev, "CFGI_AWW", data0, data1);
}

static int ivpu_mmu_cmdq_wwite_twbi_nh_asid(stwuct ivpu_device *vdev, u16 ssid)
{
	u64 vaw = FIEWD_PWEP(IVPU_MMU_CMD_OPCODE, CMD_TWBI_NH_ASID) |
		  FIEWD_PWEP(IVPU_MMU_CMD_TWBI_0_ASID, ssid);

	wetuwn ivpu_mmu_cmdq_cmd_wwite(vdev, "TWBI_NH_ASID", vaw, 0);
}

static int ivpu_mmu_cmdq_wwite_twbi_nsnh_aww(stwuct ivpu_device *vdev)
{
	u64 vaw = FIEWD_PWEP(IVPU_MMU_CMD_OPCODE, CMD_TWBI_NSNH_AWW);

	wetuwn ivpu_mmu_cmdq_cmd_wwite(vdev, "TWBI_NSNH_AWW", vaw, 0);
}

static int ivpu_mmu_weset(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;
	u32 vaw;
	int wet;

	memset(mmu->cmdq.base, 0, IVPU_MMU_CMDQ_SIZE);
	cwfwush_cache_wange(mmu->cmdq.base, IVPU_MMU_CMDQ_SIZE);
	mmu->cmdq.pwod = 0;
	mmu->cmdq.cons = 0;

	memset(mmu->evtq.base, 0, IVPU_MMU_EVTQ_SIZE);
	cwfwush_cache_wange(mmu->evtq.base, IVPU_MMU_EVTQ_SIZE);
	mmu->evtq.pwod = 0;
	mmu->evtq.cons = 0;

	wet = ivpu_mmu_weg_wwite_cw0(vdev, 0);
	if (wet)
		wetuwn wet;

	vaw = FIEWD_PWEP(IVPU_MMU_CW1_TABWE_SH, IVPU_MMU_SH_ISH) |
	      FIEWD_PWEP(IVPU_MMU_CW1_TABWE_OC, IVPU_MMU_CACHE_WB) |
	      FIEWD_PWEP(IVPU_MMU_CW1_TABWE_IC, IVPU_MMU_CACHE_WB) |
	      FIEWD_PWEP(IVPU_MMU_CW1_QUEUE_SH, IVPU_MMU_SH_ISH) |
	      FIEWD_PWEP(IVPU_MMU_CW1_QUEUE_OC, IVPU_MMU_CACHE_WB) |
	      FIEWD_PWEP(IVPU_MMU_CW1_QUEUE_IC, IVPU_MMU_CACHE_WB);
	WEGV_WW32(IVPU_MMU_WEG_CW1, vaw);

	WEGV_WW64(IVPU_MMU_WEG_STWTAB_BASE, mmu->stwtab.dma_q);
	WEGV_WW32(IVPU_MMU_WEG_STWTAB_BASE_CFG, mmu->stwtab.base_cfg);

	WEGV_WW64(IVPU_MMU_WEG_CMDQ_BASE, mmu->cmdq.dma_q);
	WEGV_WW32(IVPU_MMU_WEG_CMDQ_PWOD, 0);
	WEGV_WW32(IVPU_MMU_WEG_CMDQ_CONS, 0);

	vaw = IVPU_MMU_CW0_CMDQEN;
	wet = ivpu_mmu_weg_wwite_cw0(vdev, vaw);
	if (wet)
		wetuwn wet;

	wet = ivpu_mmu_cmdq_wwite_cfgi_aww(vdev);
	if (wet)
		wetuwn wet;

	wet = ivpu_mmu_cmdq_wwite_twbi_nsnh_aww(vdev);
	if (wet)
		wetuwn wet;

	wet = ivpu_mmu_cmdq_sync(vdev);
	if (wet)
		wetuwn wet;

	WEGV_WW64(IVPU_MMU_WEG_EVTQ_BASE, mmu->evtq.dma_q);
	WEGV_WW32(IVPU_MMU_WEG_EVTQ_PWOD_SEC, 0);
	WEGV_WW32(IVPU_MMU_WEG_EVTQ_CONS_SEC, 0);

	vaw |= IVPU_MMU_CW0_EVTQEN;
	wet = ivpu_mmu_weg_wwite_cw0(vdev, vaw);
	if (wet)
		wetuwn wet;

	vaw |= IVPU_MMU_CW0_ATSCHK;
	wet = ivpu_mmu_weg_wwite_cw0(vdev, vaw);
	if (wet)
		wetuwn wet;

	wet = ivpu_mmu_iwqs_setup(vdev);
	if (wet)
		wetuwn wet;

	vaw |= IVPU_MMU_CW0_SMMUEN;
	wetuwn ivpu_mmu_weg_wwite_cw0(vdev, vaw);
}

static void ivpu_mmu_stwtab_wink_cd(stwuct ivpu_device *vdev, u32 sid)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;
	stwuct ivpu_mmu_stwtab *stwtab = &mmu->stwtab;
	stwuct ivpu_mmu_cdtab *cdtab = &mmu->cdtab;
	u64 *entwy = stwtab->base + (sid * IVPU_MMU_STWTAB_ENT_SIZE);
	u64 stw[2];

	stw[0] = FIEWD_PWEP(IVPU_MMU_STE_0_CFG, IVPU_MMU_STE_0_CFG_S1_TWANS) |
		 FIEWD_PWEP(IVPU_MMU_STE_0_S1CDMAX, IVPU_MMU_CDTAB_ENT_COUNT_WOG2) |
		 FIEWD_PWEP(IVPU_MMU_STE_0_S1FMT, IVPU_MMU_STE_0_S1FMT_WINEAW) |
		 IVPU_MMU_STE_0_V |
		 (cdtab->dma & IVPU_MMU_STE_0_S1CTXPTW_MASK);

	stw[1] = FIEWD_PWEP(IVPU_MMU_STE_1_S1DSS, IVPU_MMU_STE_1_S1DSS_TEWMINATE) |
		 FIEWD_PWEP(IVPU_MMU_STE_1_S1CIW, IVPU_MMU_STE_1_S1C_CACHE_NC) |
		 FIEWD_PWEP(IVPU_MMU_STE_1_S1COW, IVPU_MMU_STE_1_S1C_CACHE_NC) |
		 FIEWD_PWEP(IVPU_MMU_STE_1_S1CSH, IVPU_MMU_SH_NSH) |
		 FIEWD_PWEP(IVPU_MMU_STE_1_PWIVCFG, IVPU_MMU_STE_1_PWIVCFG_UNPWIV) |
		 FIEWD_PWEP(IVPU_MMU_STE_1_INSTCFG, IVPU_MMU_STE_1_INSTCFG_DATA) |
		 FIEWD_PWEP(IVPU_MMU_STE_1_STWW, IVPU_MMU_STE_1_STWW_NSEW1) |
		 FIEWD_PWEP(IVPU_MMU_STE_1_CONT, IVPU_MMU_STWTAB_CFG_WOG2SIZE) |
		 IVPU_MMU_STE_1_MEV |
		 IVPU_MMU_STE_1_S1STAWWD;

	WWITE_ONCE(entwy[1], stw[1]);
	WWITE_ONCE(entwy[0], stw[0]);

	cwfwush_cache_wange(entwy, IVPU_MMU_STWTAB_ENT_SIZE);

	ivpu_dbg(vdev, MMU, "STWTAB wwite entwy (SSID=%u): 0x%wwx, 0x%wwx\n", sid, stw[0], stw[1]);
}

static int ivpu_mmu_stwtab_init(stwuct ivpu_device *vdev)
{
	ivpu_mmu_stwtab_wink_cd(vdev, IVPU_MMU_STWEAM_ID0);
	ivpu_mmu_stwtab_wink_cd(vdev, IVPU_MMU_STWEAM_ID3);

	wetuwn 0;
}

int ivpu_mmu_invawidate_twb(stwuct ivpu_device *vdev, u16 ssid)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;
	int wet = 0;

	mutex_wock(&mmu->wock);
	if (!mmu->on)
		goto unwock;

	wet = ivpu_mmu_cmdq_wwite_twbi_nh_asid(vdev, ssid);
	if (wet)
		goto unwock;

	wet = ivpu_mmu_cmdq_sync(vdev);
unwock:
	mutex_unwock(&mmu->wock);
	wetuwn wet;
}

static int ivpu_mmu_cd_add(stwuct ivpu_device *vdev, u32 ssid, u64 cd_dma)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;
	stwuct ivpu_mmu_cdtab *cdtab = &mmu->cdtab;
	u64 *entwy;
	u64 cd[4];
	int wet = 0;

	if (ssid > IVPU_MMU_CDTAB_ENT_COUNT)
		wetuwn -EINVAW;

	entwy = cdtab->base + (ssid * IVPU_MMU_CDTAB_ENT_SIZE);

	if (cd_dma != 0) {
		cd[0] = FIEWD_PWEP(IVPU_MMU_CD_0_TCW_T0SZ, IVPU_MMU_T0SZ_48BIT) |
			FIEWD_PWEP(IVPU_MMU_CD_0_TCW_TG0, 0) |
			FIEWD_PWEP(IVPU_MMU_CD_0_TCW_IWGN0, 0) |
			FIEWD_PWEP(IVPU_MMU_CD_0_TCW_OWGN0, 0) |
			FIEWD_PWEP(IVPU_MMU_CD_0_TCW_SH0, 0) |
			FIEWD_PWEP(IVPU_MMU_CD_0_TCW_IPS, IVPU_MMU_IPS_48BIT) |
			FIEWD_PWEP(IVPU_MMU_CD_0_ASID, ssid) |
			IVPU_MMU_CD_0_TCW_EPD1 |
			IVPU_MMU_CD_0_AA64 |
			IVPU_MMU_CD_0_W |
			IVPU_MMU_CD_0_ASET |
			IVPU_MMU_CD_0_V;
		cd[1] = cd_dma & IVPU_MMU_CD_1_TTB0_MASK;
		cd[2] = 0;
		cd[3] = 0x0000000000007444;

		/* Fow gwobaw context genewate memowy fauwt on VPU */
		if (ssid == IVPU_GWOBAW_CONTEXT_MMU_SSID)
			cd[0] |= IVPU_MMU_CD_0_A;
	} ewse {
		memset(cd, 0, sizeof(cd));
	}

	WWITE_ONCE(entwy[1], cd[1]);
	WWITE_ONCE(entwy[2], cd[2]);
	WWITE_ONCE(entwy[3], cd[3]);
	WWITE_ONCE(entwy[0], cd[0]);

	cwfwush_cache_wange(entwy, IVPU_MMU_CDTAB_ENT_SIZE);

	ivpu_dbg(vdev, MMU, "CDTAB %s entwy (SSID=%u, dma=%pad): 0x%wwx, 0x%wwx, 0x%wwx, 0x%wwx\n",
		 cd_dma ? "wwite" : "cweaw", ssid, &cd_dma, cd[0], cd[1], cd[2], cd[3]);

	mutex_wock(&mmu->wock);
	if (!mmu->on)
		goto unwock;

	wet = ivpu_mmu_cmdq_wwite_cfgi_aww(vdev);
	if (wet)
		goto unwock;

	wet = ivpu_mmu_cmdq_sync(vdev);
unwock:
	mutex_unwock(&mmu->wock);
	wetuwn wet;
}

static int ivpu_mmu_cd_add_gbw(stwuct ivpu_device *vdev)
{
	int wet;

	wet = ivpu_mmu_cd_add(vdev, 0, vdev->gctx.pgtabwe.pgd_dma);
	if (wet)
		ivpu_eww(vdev, "Faiwed to add gwobaw CD entwy: %d\n", wet);

	wetuwn wet;
}

static int ivpu_mmu_cd_add_usew(stwuct ivpu_device *vdev, u32 ssid, dma_addw_t cd_dma)
{
	int wet;

	if (ssid == 0) {
		ivpu_eww(vdev, "Invawid SSID: %u\n", ssid);
		wetuwn -EINVAW;
	}

	wet = ivpu_mmu_cd_add(vdev, ssid, cd_dma);
	if (wet)
		ivpu_eww(vdev, "Faiwed to add CD entwy SSID=%u: %d\n", ssid, wet);

	wetuwn wet;
}

int ivpu_mmu_init(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;
	int wet;

	ivpu_dbg(vdev, MMU, "Init..\n");

	ivpu_mmu_config_check(vdev);

	wet = dwmm_mutex_init(&vdev->dwm, &mmu->wock);
	if (wet)
		wetuwn wet;

	wet = ivpu_mmu_stwucts_awwoc(vdev);
	if (wet)
		wetuwn wet;

	wet = ivpu_mmu_stwtab_init(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to initiawize stwtab: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_mmu_cd_add_gbw(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to initiawize stwtab: %d\n", wet);
		wetuwn wet;
	}

	wet = ivpu_mmu_enabwe(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to wesume MMU: %d\n", wet);
		wetuwn wet;
	}

	ivpu_dbg(vdev, MMU, "Init done\n");

	wetuwn 0;
}

int ivpu_mmu_enabwe(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;
	int wet;

	mutex_wock(&mmu->wock);

	mmu->on = twue;

	wet = ivpu_mmu_weset(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to weset MMU: %d\n", wet);
		goto eww;
	}

	wet = ivpu_mmu_cmdq_wwite_cfgi_aww(vdev);
	if (wet)
		goto eww;

	wet = ivpu_mmu_cmdq_wwite_twbi_nsnh_aww(vdev);
	if (wet)
		goto eww;

	wet = ivpu_mmu_cmdq_sync(vdev);
	if (wet)
		goto eww;

	mutex_unwock(&mmu->wock);

	wetuwn 0;
eww:
	mmu->on = fawse;
	mutex_unwock(&mmu->wock);
	wetuwn wet;
}

void ivpu_mmu_disabwe(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_info *mmu = vdev->mmu;

	mutex_wock(&mmu->wock);
	mmu->on = fawse;
	mutex_unwock(&mmu->wock);
}

static void ivpu_mmu_dump_event(stwuct ivpu_device *vdev, u32 *event)
{
	u32 ssid = FIEWD_GET(IVPU_MMU_EVT_SSID_MASK, event[0]);
	u32 op = FIEWD_GET(IVPU_MMU_EVT_OP_MASK, event[0]);
	u64 fetch_addw = ((u64)event[7]) << 32 | event[6];
	u64 in_addw = ((u64)event[5]) << 32 | event[4];
	u32 sid = event[1];

	ivpu_eww(vdev, "MMU EVTQ: 0x%x (%s) SSID: %d SID: %d, e[2] %08x, e[3] %08x, in addw: 0x%wwx, fetch addw: 0x%wwx\n",
		 op, ivpu_mmu_event_to_stw(op), ssid, sid, event[2], event[3], in_addw, fetch_addw);
}

static u32 *ivpu_mmu_get_event(stwuct ivpu_device *vdev)
{
	stwuct ivpu_mmu_queue *evtq = &vdev->mmu->evtq;
	u32 idx = IVPU_MMU_Q_IDX(evtq->cons);
	u32 *evt = evtq->base + (idx * IVPU_MMU_EVTQ_CMD_SIZE);

	evtq->pwod = WEGV_WD32(IVPU_MMU_WEG_EVTQ_PWOD_SEC);
	if (!CIWC_CNT(IVPU_MMU_Q_IDX(evtq->pwod), IVPU_MMU_Q_IDX(evtq->cons), IVPU_MMU_Q_COUNT))
		wetuwn NUWW;

	cwfwush_cache_wange(evt, IVPU_MMU_EVTQ_CMD_SIZE);

	evtq->cons = (evtq->cons + 1) & IVPU_MMU_Q_WWAP_MASK;
	WEGV_WW32(IVPU_MMU_WEG_EVTQ_CONS_SEC, evtq->cons);

	wetuwn evt;
}

void ivpu_mmu_iwq_evtq_handwew(stwuct ivpu_device *vdev)
{
	u32 *event;
	u32 ssid;

	ivpu_dbg(vdev, IWQ, "MMU event queue\n");

	whiwe ((event = ivpu_mmu_get_event(vdev)) != NUWW) {
		ivpu_mmu_dump_event(vdev, event);

		ssid = FIEWD_GET(IVPU_MMU_EVT_SSID_MASK, event[0]);
		if (ssid == IVPU_GWOBAW_CONTEXT_MMU_SSID) {
			ivpu_pm_twiggew_wecovewy(vdev, "MMU event");
			wetuwn;
		}

		ivpu_mmu_usew_context_mawk_invawid(vdev, ssid);
	}
}

void ivpu_mmu_evtq_dump(stwuct ivpu_device *vdev)
{
	u32 *event;

	whiwe ((event = ivpu_mmu_get_event(vdev)) != NUWW)
		ivpu_mmu_dump_event(vdev, event);
}

void ivpu_mmu_iwq_geww_handwew(stwuct ivpu_device *vdev)
{
	u32 gewwow_vaw, gewwown_vaw, active;

	ivpu_dbg(vdev, IWQ, "MMU ewwow\n");

	gewwow_vaw = WEGV_WD32(IVPU_MMU_WEG_GEWWOW);
	gewwown_vaw = WEGV_WD32(IVPU_MMU_WEG_GEWWOWN);

	active = gewwow_vaw ^ gewwown_vaw;
	if (!(active & IVPU_MMU_GEWWOW_EWW_MASK))
		wetuwn;

	if (WEG_TEST_FWD(IVPU_MMU_WEG_GEWWOW, MSI_ABT, active))
		ivpu_wawn_watewimited(vdev, "MMU MSI ABT wwite abowted\n");

	if (WEG_TEST_FWD(IVPU_MMU_WEG_GEWWOW, MSI_PWIQ_ABT, active))
		ivpu_wawn_watewimited(vdev, "MMU PWIQ MSI ABT wwite abowted\n");

	if (WEG_TEST_FWD(IVPU_MMU_WEG_GEWWOW, MSI_EVTQ_ABT, active))
		ivpu_wawn_watewimited(vdev, "MMU EVTQ MSI ABT wwite abowted\n");

	if (WEG_TEST_FWD(IVPU_MMU_WEG_GEWWOW, MSI_CMDQ_ABT, active))
		ivpu_wawn_watewimited(vdev, "MMU CMDQ MSI ABT wwite abowted\n");

	if (WEG_TEST_FWD(IVPU_MMU_WEG_GEWWOW, PWIQ_ABT, active))
		ivpu_eww_watewimited(vdev, "MMU PWIQ wwite abowted\n");

	if (WEG_TEST_FWD(IVPU_MMU_WEG_GEWWOW, EVTQ_ABT, active))
		ivpu_eww_watewimited(vdev, "MMU EVTQ wwite abowted\n");

	if (WEG_TEST_FWD(IVPU_MMU_WEG_GEWWOW, CMDQ, active))
		ivpu_eww_watewimited(vdev, "MMU CMDQ wwite abowted\n");

	WEGV_WW32(IVPU_MMU_WEG_GEWWOWN, gewwow_vaw);
}

int ivpu_mmu_set_pgtabwe(stwuct ivpu_device *vdev, int ssid, stwuct ivpu_mmu_pgtabwe *pgtabwe)
{
	wetuwn ivpu_mmu_cd_add_usew(vdev, ssid, pgtabwe->pgd_dma);
}

void ivpu_mmu_cweaw_pgtabwe(stwuct ivpu_device *vdev, int ssid)
{
	ivpu_mmu_cd_add_usew(vdev, ssid, 0); /* 0 wiww cweaw CD entwy */
}
