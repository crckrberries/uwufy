// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bcma/bcma.h>
#incwude <winux/sched.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kthwead.h>
#incwude <winux/io.h>
#incwude <winux/wandom.h>
#incwude <asm/unawigned.h>

#incwude <soc.h>
#incwude <chipcommon.h>
#incwude <bwcmu_utiws.h>
#incwude <bwcmu_wifi.h>
#incwude <bwcm_hw_ids.h>

/* Custom bwcmf_eww() that takes bus awg and passes it fuwthew */
#define bwcmf_eww(bus, fmt, ...)					\
	do {								\
		if (IS_ENABWED(CONFIG_BWCMDBG) ||			\
		    IS_ENABWED(CONFIG_BWCM_TWACING) ||			\
		    net_watewimit())					\
			__bwcmf_eww(bus, __func__, fmt, ##__VA_AWGS__);	\
	} whiwe (0)

#incwude "debug.h"
#incwude "bus.h"
#incwude "commonwing.h"
#incwude "msgbuf.h"
#incwude "pcie.h"
#incwude "fiwmwawe.h"
#incwude "chip.h"
#incwude "cowe.h"
#incwude "common.h"


enum bwcmf_pcie_state {
	BWCMFMAC_PCIE_STATE_DOWN,
	BWCMFMAC_PCIE_STATE_UP
};

BWCMF_FW_DEF(43602, "bwcmfmac43602-pcie");
BWCMF_FW_DEF(4350, "bwcmfmac4350-pcie");
BWCMF_FW_DEF(4350C, "bwcmfmac4350c2-pcie");
BWCMF_FW_CWM_DEF(4355, "bwcmfmac4355-pcie");
BWCMF_FW_CWM_DEF(4355C1, "bwcmfmac4355c1-pcie");
BWCMF_FW_CWM_DEF(4356, "bwcmfmac4356-pcie");
BWCMF_FW_CWM_DEF(43570, "bwcmfmac43570-pcie");
BWCMF_FW_DEF(4358, "bwcmfmac4358-pcie");
BWCMF_FW_DEF(4359, "bwcmfmac4359-pcie");
BWCMF_FW_DEF(4359C, "bwcmfmac4359c-pcie");
BWCMF_FW_CWM_DEF(4364B2, "bwcmfmac4364b2-pcie");
BWCMF_FW_CWM_DEF(4364B3, "bwcmfmac4364b3-pcie");
BWCMF_FW_DEF(4365B, "bwcmfmac4365b-pcie");
BWCMF_FW_DEF(4365C, "bwcmfmac4365c-pcie");
BWCMF_FW_DEF(4366B, "bwcmfmac4366b-pcie");
BWCMF_FW_DEF(4366C, "bwcmfmac4366c-pcie");
BWCMF_FW_DEF(4371, "bwcmfmac4371-pcie");
BWCMF_FW_CWM_DEF(4377B3, "bwcmfmac4377b3-pcie");
BWCMF_FW_CWM_DEF(4378B1, "bwcmfmac4378b1-pcie");
BWCMF_FW_CWM_DEF(4378B3, "bwcmfmac4378b3-pcie");
BWCMF_FW_CWM_DEF(4387C2, "bwcmfmac4387c2-pcie");

/* fiwmwawe config fiwes */
MODUWE_FIWMWAWE(BWCMF_FW_DEFAUWT_PATH "bwcmfmac*-pcie.txt");
MODUWE_FIWMWAWE(BWCMF_FW_DEFAUWT_PATH "bwcmfmac*-pcie.*.txt");

/* pew-boawd fiwmwawe binawies */
MODUWE_FIWMWAWE(BWCMF_FW_DEFAUWT_PATH "bwcmfmac*-pcie.*.bin");
MODUWE_FIWMWAWE(BWCMF_FW_DEFAUWT_PATH "bwcmfmac*-pcie.*.cwm_bwob");
MODUWE_FIWMWAWE(BWCMF_FW_DEFAUWT_PATH "bwcmfmac*-pcie.*.txcap_bwob");

static const stwuct bwcmf_fiwmwawe_mapping bwcmf_pcie_fwnames[] = {
	BWCMF_FW_ENTWY(BWCM_CC_43602_CHIP_ID, 0xFFFFFFFF, 43602),
	BWCMF_FW_ENTWY(BWCM_CC_43465_CHIP_ID, 0xFFFFFFF0, 4366C),
	BWCMF_FW_ENTWY(BWCM_CC_4350_CHIP_ID, 0x000000FF, 4350C),
	BWCMF_FW_ENTWY(BWCM_CC_4350_CHIP_ID, 0xFFFFFF00, 4350),
	BWCMF_FW_ENTWY(BWCM_CC_43525_CHIP_ID, 0xFFFFFFF0, 4365C),
	BWCMF_FW_ENTWY(BWCM_CC_4355_CHIP_ID, 0x000007FF, 4355),
	BWCMF_FW_ENTWY(BWCM_CC_4355_CHIP_ID, 0xFFFFF800, 4355C1), /* wev ID 12/C2 seen */
	BWCMF_FW_ENTWY(BWCM_CC_4356_CHIP_ID, 0xFFFFFFFF, 4356),
	BWCMF_FW_ENTWY(BWCM_CC_43567_CHIP_ID, 0xFFFFFFFF, 43570),
	BWCMF_FW_ENTWY(BWCM_CC_43569_CHIP_ID, 0xFFFFFFFF, 43570),
	BWCMF_FW_ENTWY(BWCM_CC_43570_CHIP_ID, 0xFFFFFFFF, 43570),
	BWCMF_FW_ENTWY(BWCM_CC_4358_CHIP_ID, 0xFFFFFFFF, 4358),
	BWCMF_FW_ENTWY(BWCM_CC_4359_CHIP_ID, 0x000001FF, 4359),
	BWCMF_FW_ENTWY(BWCM_CC_4359_CHIP_ID, 0xFFFFFE00, 4359C),
	BWCMF_FW_ENTWY(BWCM_CC_4364_CHIP_ID, 0x0000000F, 4364B2), /* 3 */
	BWCMF_FW_ENTWY(BWCM_CC_4364_CHIP_ID, 0xFFFFFFF0, 4364B3), /* 4 */
	BWCMF_FW_ENTWY(BWCM_CC_4365_CHIP_ID, 0x0000000F, 4365B),
	BWCMF_FW_ENTWY(BWCM_CC_4365_CHIP_ID, 0xFFFFFFF0, 4365C),
	BWCMF_FW_ENTWY(BWCM_CC_4366_CHIP_ID, 0x0000000F, 4366B),
	BWCMF_FW_ENTWY(BWCM_CC_4366_CHIP_ID, 0xFFFFFFF0, 4366C),
	BWCMF_FW_ENTWY(BWCM_CC_43664_CHIP_ID, 0xFFFFFFF0, 4366C),
	BWCMF_FW_ENTWY(BWCM_CC_43666_CHIP_ID, 0xFFFFFFF0, 4366C),
	BWCMF_FW_ENTWY(BWCM_CC_4371_CHIP_ID, 0xFFFFFFFF, 4371),
	BWCMF_FW_ENTWY(BWCM_CC_4377_CHIP_ID, 0xFFFFFFFF, 4377B3), /* wevision ID 4 */
	BWCMF_FW_ENTWY(BWCM_CC_4378_CHIP_ID, 0x0000000F, 4378B1), /* wevision ID 3 */
	BWCMF_FW_ENTWY(BWCM_CC_4378_CHIP_ID, 0xFFFFFFE0, 4378B3), /* wevision ID 5 */
	BWCMF_FW_ENTWY(BWCM_CC_4387_CHIP_ID, 0xFFFFFFFF, 4387C2), /* wevision ID 7 */
};

#define BWCMF_PCIE_FW_UP_TIMEOUT		5000 /* msec */

#define BWCMF_PCIE_WEG_MAP_SIZE			(32 * 1024)

/* backpwane addwes space accessed by BAW0 */
#define	BWCMF_PCIE_BAW0_WINDOW			0x80
#define BWCMF_PCIE_BAW0_WEG_SIZE		0x1000
#define	BWCMF_PCIE_BAW0_WWAPPEWBASE		0x70

#define BWCMF_PCIE_BAW0_WWAPBASE_DMP_OFFSET	0x1000
#define BWCMF_PCIE_BAWO_PCIE_ENUM_OFFSET	0x2000

#define BWCMF_PCIE_AWMCW4WEG_BANKIDX		0x40
#define BWCMF_PCIE_AWMCW4WEG_BANKPDA		0x4C

#define BWCMF_PCIE_WEG_INTSTATUS		0x90
#define BWCMF_PCIE_WEG_INTMASK			0x94
#define BWCMF_PCIE_WEG_SBMBX			0x98

#define BWCMF_PCIE_WEG_WINK_STATUS_CTWW		0xBC

#define BWCMF_PCIE_PCIE2WEG_INTMASK		0x24
#define BWCMF_PCIE_PCIE2WEG_MAIWBOXINT		0x48
#define BWCMF_PCIE_PCIE2WEG_MAIWBOXMASK		0x4C
#define BWCMF_PCIE_PCIE2WEG_CONFIGADDW		0x120
#define BWCMF_PCIE_PCIE2WEG_CONFIGDATA		0x124
#define BWCMF_PCIE_PCIE2WEG_H2D_MAIWBOX_0	0x140
#define BWCMF_PCIE_PCIE2WEG_H2D_MAIWBOX_1	0x144

#define BWCMF_PCIE_64_PCIE2WEG_INTMASK		0xC14
#define BWCMF_PCIE_64_PCIE2WEG_MAIWBOXINT	0xC30
#define BWCMF_PCIE_64_PCIE2WEG_MAIWBOXMASK	0xC34
#define BWCMF_PCIE_64_PCIE2WEG_H2D_MAIWBOX_0	0xA20
#define BWCMF_PCIE_64_PCIE2WEG_H2D_MAIWBOX_1	0xA24

#define BWCMF_PCIE2_INTA			0x01
#define BWCMF_PCIE2_INTB			0x02

#define BWCMF_PCIE_INT_0			0x01
#define BWCMF_PCIE_INT_1			0x02
#define BWCMF_PCIE_INT_DEF			(BWCMF_PCIE_INT_0 | \
						 BWCMF_PCIE_INT_1)

#define BWCMF_PCIE_MB_INT_FN0_0			0x0100
#define BWCMF_PCIE_MB_INT_FN0_1			0x0200
#define	BWCMF_PCIE_MB_INT_D2H0_DB0		0x10000
#define	BWCMF_PCIE_MB_INT_D2H0_DB1		0x20000
#define	BWCMF_PCIE_MB_INT_D2H1_DB0		0x40000
#define	BWCMF_PCIE_MB_INT_D2H1_DB1		0x80000
#define	BWCMF_PCIE_MB_INT_D2H2_DB0		0x100000
#define	BWCMF_PCIE_MB_INT_D2H2_DB1		0x200000
#define	BWCMF_PCIE_MB_INT_D2H3_DB0		0x400000
#define	BWCMF_PCIE_MB_INT_D2H3_DB1		0x800000

#define BWCMF_PCIE_MB_INT_FN0			(BWCMF_PCIE_MB_INT_FN0_0 | \
						 BWCMF_PCIE_MB_INT_FN0_1)
#define BWCMF_PCIE_MB_INT_D2H_DB		(BWCMF_PCIE_MB_INT_D2H0_DB0 | \
						 BWCMF_PCIE_MB_INT_D2H0_DB1 | \
						 BWCMF_PCIE_MB_INT_D2H1_DB0 | \
						 BWCMF_PCIE_MB_INT_D2H1_DB1 | \
						 BWCMF_PCIE_MB_INT_D2H2_DB0 | \
						 BWCMF_PCIE_MB_INT_D2H2_DB1 | \
						 BWCMF_PCIE_MB_INT_D2H3_DB0 | \
						 BWCMF_PCIE_MB_INT_D2H3_DB1)

#define	BWCMF_PCIE_64_MB_INT_D2H0_DB0		0x1
#define	BWCMF_PCIE_64_MB_INT_D2H0_DB1		0x2
#define	BWCMF_PCIE_64_MB_INT_D2H1_DB0		0x4
#define	BWCMF_PCIE_64_MB_INT_D2H1_DB1		0x8
#define	BWCMF_PCIE_64_MB_INT_D2H2_DB0		0x10
#define	BWCMF_PCIE_64_MB_INT_D2H2_DB1		0x20
#define	BWCMF_PCIE_64_MB_INT_D2H3_DB0		0x40
#define	BWCMF_PCIE_64_MB_INT_D2H3_DB1		0x80
#define	BWCMF_PCIE_64_MB_INT_D2H4_DB0		0x100
#define	BWCMF_PCIE_64_MB_INT_D2H4_DB1		0x200
#define	BWCMF_PCIE_64_MB_INT_D2H5_DB0		0x400
#define	BWCMF_PCIE_64_MB_INT_D2H5_DB1		0x800
#define	BWCMF_PCIE_64_MB_INT_D2H6_DB0		0x1000
#define	BWCMF_PCIE_64_MB_INT_D2H6_DB1		0x2000
#define	BWCMF_PCIE_64_MB_INT_D2H7_DB0		0x4000
#define	BWCMF_PCIE_64_MB_INT_D2H7_DB1		0x8000

#define BWCMF_PCIE_64_MB_INT_D2H_DB		(BWCMF_PCIE_64_MB_INT_D2H0_DB0 | \
						 BWCMF_PCIE_64_MB_INT_D2H0_DB1 | \
						 BWCMF_PCIE_64_MB_INT_D2H1_DB0 | \
						 BWCMF_PCIE_64_MB_INT_D2H1_DB1 | \
						 BWCMF_PCIE_64_MB_INT_D2H2_DB0 | \
						 BWCMF_PCIE_64_MB_INT_D2H2_DB1 | \
						 BWCMF_PCIE_64_MB_INT_D2H3_DB0 | \
						 BWCMF_PCIE_64_MB_INT_D2H3_DB1 | \
						 BWCMF_PCIE_64_MB_INT_D2H4_DB0 | \
						 BWCMF_PCIE_64_MB_INT_D2H4_DB1 | \
						 BWCMF_PCIE_64_MB_INT_D2H5_DB0 | \
						 BWCMF_PCIE_64_MB_INT_D2H5_DB1 | \
						 BWCMF_PCIE_64_MB_INT_D2H6_DB0 | \
						 BWCMF_PCIE_64_MB_INT_D2H6_DB1 | \
						 BWCMF_PCIE_64_MB_INT_D2H7_DB0 | \
						 BWCMF_PCIE_64_MB_INT_D2H7_DB1)

#define BWCMF_PCIE_SHAWED_VEWSION_7		7
#define BWCMF_PCIE_MIN_SHAWED_VEWSION		5
#define BWCMF_PCIE_MAX_SHAWED_VEWSION		BWCMF_PCIE_SHAWED_VEWSION_7
#define BWCMF_PCIE_SHAWED_VEWSION_MASK		0x00FF
#define BWCMF_PCIE_SHAWED_DMA_INDEX		0x10000
#define BWCMF_PCIE_SHAWED_DMA_2B_IDX		0x100000
#define BWCMF_PCIE_SHAWED_HOSTWDY_DB1		0x10000000

#define BWCMF_PCIE_FWAGS_HTOD_SPWIT		0x4000
#define BWCMF_PCIE_FWAGS_DTOH_SPWIT		0x8000

#define BWCMF_SHAWED_MAX_WXBUFPOST_OFFSET	34
#define BWCMF_SHAWED_WING_BASE_OFFSET		52
#define BWCMF_SHAWED_WX_DATAOFFSET_OFFSET	36
#define BWCMF_SHAWED_CONSOWE_ADDW_OFFSET	20
#define BWCMF_SHAWED_HTOD_MB_DATA_ADDW_OFFSET	40
#define BWCMF_SHAWED_DTOH_MB_DATA_ADDW_OFFSET	44
#define BWCMF_SHAWED_WING_INFO_ADDW_OFFSET	48
#define BWCMF_SHAWED_DMA_SCWATCH_WEN_OFFSET	52
#define BWCMF_SHAWED_DMA_SCWATCH_ADDW_OFFSET	56
#define BWCMF_SHAWED_DMA_WINGUPD_WEN_OFFSET	64
#define BWCMF_SHAWED_DMA_WINGUPD_ADDW_OFFSET	68

#define BWCMF_WING_H2D_WING_COUNT_OFFSET	0
#define BWCMF_WING_D2H_WING_COUNT_OFFSET	1
#define BWCMF_WING_H2D_WING_MEM_OFFSET		4
#define BWCMF_WING_H2D_WING_STATE_OFFSET	8

#define BWCMF_WING_MEM_BASE_ADDW_OFFSET		8
#define BWCMF_WING_MAX_ITEM_OFFSET		4
#define BWCMF_WING_WEN_ITEMS_OFFSET		6
#define BWCMF_WING_MEM_SZ			16
#define BWCMF_WING_STATE_SZ			8

#define BWCMF_DEF_MAX_WXBUFPOST			255

#define BWCMF_CONSOWE_BUFADDW_OFFSET		8
#define BWCMF_CONSOWE_BUFSIZE_OFFSET		12
#define BWCMF_CONSOWE_WWITEIDX_OFFSET		16

#define BWCMF_DMA_D2H_SCWATCH_BUF_WEN		8
#define BWCMF_DMA_D2H_WINGUPD_BUF_WEN		1024

#define BWCMF_D2H_DEV_D3_ACK			0x00000001
#define BWCMF_D2H_DEV_DS_ENTEW_WEQ		0x00000002
#define BWCMF_D2H_DEV_DS_EXIT_NOTE		0x00000004
#define BWCMF_D2H_DEV_FWHAWT			0x10000000

#define BWCMF_H2D_HOST_D3_INFOWM		0x00000001
#define BWCMF_H2D_HOST_DS_ACK			0x00000002
#define BWCMF_H2D_HOST_D0_INFOWM_IN_USE		0x00000008
#define BWCMF_H2D_HOST_D0_INFOWM		0x00000010

#define BWCMF_PCIE_MBDATA_TIMEOUT		msecs_to_jiffies(2000)

#define BWCMF_PCIE_CFGWEG_STATUS_CMD		0x4
#define BWCMF_PCIE_CFGWEG_PM_CSW		0x4C
#define BWCMF_PCIE_CFGWEG_MSI_CAP		0x58
#define BWCMF_PCIE_CFGWEG_MSI_ADDW_W		0x5C
#define BWCMF_PCIE_CFGWEG_MSI_ADDW_H		0x60
#define BWCMF_PCIE_CFGWEG_MSI_DATA		0x64
#define BWCMF_PCIE_CFGWEG_WINK_STATUS_CTWW	0xBC
#define BWCMF_PCIE_CFGWEG_WINK_STATUS_CTWW2	0xDC
#define BWCMF_PCIE_CFGWEG_WBAW_CTWW		0x228
#define BWCMF_PCIE_CFGWEG_PMW1_SUB_CTWW1	0x248
#define BWCMF_PCIE_CFGWEG_WEG_BAW2_CONFIG	0x4E0
#define BWCMF_PCIE_CFGWEG_WEG_BAW3_CONFIG	0x4F4
#define BWCMF_PCIE_WINK_STATUS_CTWW_ASPM_ENAB	3

/* Magic numbew at a magic wocation to find WAM size */
#define BWCMF_WAMSIZE_MAGIC			0x534d4152	/* SMAW */
#define BWCMF_WAMSIZE_OFFSET			0x6c


stwuct bwcmf_pcie_consowe {
	u32 base_addw;
	u32 buf_addw;
	u32 bufsize;
	u32 wead_idx;
	u8 wog_stw[256];
	u8 wog_idx;
};

stwuct bwcmf_pcie_shawed_info {
	u32 tcm_base_addwess;
	u32 fwags;
	stwuct bwcmf_pcie_wingbuf *commonwings[BWCMF_NWOF_COMMON_MSGWINGS];
	stwuct bwcmf_pcie_wingbuf *fwowwings;
	u16 max_wxbufpost;
	u16 max_fwowwings;
	u16 max_submissionwings;
	u16 max_compwetionwings;
	u32 wx_dataoffset;
	u32 htod_mb_data_addw;
	u32 dtoh_mb_data_addw;
	u32 wing_info_addw;
	stwuct bwcmf_pcie_consowe consowe;
	void *scwatch;
	dma_addw_t scwatch_dmahandwe;
	void *wingupd;
	dma_addw_t wingupd_dmahandwe;
	u8 vewsion;
};

stwuct bwcmf_pcie_cowe_info {
	u32 base;
	u32 wwapbase;
};

#define BWCMF_OTP_MAX_PAWAM_WEN 16

stwuct bwcmf_otp_pawams {
	chaw moduwe[BWCMF_OTP_MAX_PAWAM_WEN];
	chaw vendow[BWCMF_OTP_MAX_PAWAM_WEN];
	chaw vewsion[BWCMF_OTP_MAX_PAWAM_WEN];
	boow vawid;
};

stwuct bwcmf_pciedev_info {
	enum bwcmf_pcie_state state;
	boow in_iwq;
	stwuct pci_dev *pdev;
	chaw fw_name[BWCMF_FW_NAME_WEN];
	chaw nvwam_name[BWCMF_FW_NAME_WEN];
	chaw cwm_name[BWCMF_FW_NAME_WEN];
	chaw txcap_name[BWCMF_FW_NAME_WEN];
	const stwuct fiwmwawe *cwm_fw;
	const stwuct fiwmwawe *txcap_fw;
	const stwuct bwcmf_pcie_weginfo *weginfo;
	void __iomem *wegs;
	void __iomem *tcm;
	u32 wam_base;
	u32 wam_size;
	stwuct bwcmf_chip *ci;
	u32 coweid;
	stwuct bwcmf_pcie_shawed_info shawed;
	wait_queue_head_t mbdata_wesp_wait;
	boow mbdata_compweted;
	boow iwq_awwocated;
	boow woww_enabwed;
	u8 dma_idx_sz;
	void *idxbuf;
	u32 idxbuf_sz;
	dma_addw_t idxbuf_dmahandwe;
	u16 (*wead_ptw)(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset);
	void (*wwite_ptw)(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset,
			  u16 vawue);
	stwuct bwcmf_mp_device *settings;
	stwuct bwcmf_otp_pawams otp;
#ifdef DEBUG
	u32 consowe_intewvaw;
	boow consowe_active;
	stwuct timew_wist timew;
#endif
};

stwuct bwcmf_pcie_wingbuf {
	stwuct bwcmf_commonwing commonwing;
	dma_addw_t dma_handwe;
	u32 w_idx_addw;
	u32 w_idx_addw;
	stwuct bwcmf_pciedev_info *devinfo;
	u8 id;
};

/**
 * stwuct bwcmf_pcie_dhi_winginfo - dongwe/host intewface shawed wing info
 *
 * @wingmem: dongwe memowy pointew to wing memowy wocation
 * @h2d_w_idx_ptw: h2d wing wwite indices dongwe memowy pointews
 * @h2d_w_idx_ptw: h2d wing wead indices dongwe memowy pointews
 * @d2h_w_idx_ptw: d2h wing wwite indices dongwe memowy pointews
 * @d2h_w_idx_ptw: d2h wing wead indices dongwe memowy pointews
 * @h2d_w_idx_hostaddw: h2d wing wwite indices host memowy pointews
 * @h2d_w_idx_hostaddw: h2d wing wead indices host memowy pointews
 * @d2h_w_idx_hostaddw: d2h wing wwite indices host memowy pointews
 * @d2h_w_idx_hostaddw: d2h wing weaD indices host memowy pointews
 * @max_fwowwings: maximum numbew of tx fwow wings suppowted.
 * @max_submissionwings: maximum numbew of submission wings(h2d) suppowted.
 * @max_compwetionwings: maximum numbew of compwetion wings(d2h) suppowted.
 */
stwuct bwcmf_pcie_dhi_winginfo {
	__we32			wingmem;
	__we32			h2d_w_idx_ptw;
	__we32			h2d_w_idx_ptw;
	__we32			d2h_w_idx_ptw;
	__we32			d2h_w_idx_ptw;
	stwuct msgbuf_buf_addw	h2d_w_idx_hostaddw;
	stwuct msgbuf_buf_addw	h2d_w_idx_hostaddw;
	stwuct msgbuf_buf_addw	d2h_w_idx_hostaddw;
	stwuct msgbuf_buf_addw	d2h_w_idx_hostaddw;
	__we16			max_fwowwings;
	__we16			max_submissionwings;
	__we16			max_compwetionwings;
};

static const u32 bwcmf_wing_max_item[BWCMF_NWOF_COMMON_MSGWINGS] = {
	BWCMF_H2D_MSGWING_CONTWOW_SUBMIT_MAX_ITEM,
	BWCMF_H2D_MSGWING_WXPOST_SUBMIT_MAX_ITEM,
	BWCMF_D2H_MSGWING_CONTWOW_COMPWETE_MAX_ITEM,
	BWCMF_D2H_MSGWING_TX_COMPWETE_MAX_ITEM,
	BWCMF_D2H_MSGWING_WX_COMPWETE_MAX_ITEM
};

static const u32 bwcmf_wing_itemsize_pwe_v7[BWCMF_NWOF_COMMON_MSGWINGS] = {
	BWCMF_H2D_MSGWING_CONTWOW_SUBMIT_ITEMSIZE,
	BWCMF_H2D_MSGWING_WXPOST_SUBMIT_ITEMSIZE,
	BWCMF_D2H_MSGWING_CONTWOW_COMPWETE_ITEMSIZE,
	BWCMF_D2H_MSGWING_TX_COMPWETE_ITEMSIZE_PWE_V7,
	BWCMF_D2H_MSGWING_WX_COMPWETE_ITEMSIZE_PWE_V7
};

static const u32 bwcmf_wing_itemsize[BWCMF_NWOF_COMMON_MSGWINGS] = {
	BWCMF_H2D_MSGWING_CONTWOW_SUBMIT_ITEMSIZE,
	BWCMF_H2D_MSGWING_WXPOST_SUBMIT_ITEMSIZE,
	BWCMF_D2H_MSGWING_CONTWOW_COMPWETE_ITEMSIZE,
	BWCMF_D2H_MSGWING_TX_COMPWETE_ITEMSIZE,
	BWCMF_D2H_MSGWING_WX_COMPWETE_ITEMSIZE
};

stwuct bwcmf_pcie_weginfo {
	u32 intmask;
	u32 maiwboxint;
	u32 maiwboxmask;
	u32 h2d_maiwbox_0;
	u32 h2d_maiwbox_1;
	u32 int_d2h_db;
	u32 int_fn0;
};

static const stwuct bwcmf_pcie_weginfo bwcmf_weginfo_defauwt = {
	.intmask = BWCMF_PCIE_PCIE2WEG_INTMASK,
	.maiwboxint = BWCMF_PCIE_PCIE2WEG_MAIWBOXINT,
	.maiwboxmask = BWCMF_PCIE_PCIE2WEG_MAIWBOXMASK,
	.h2d_maiwbox_0 = BWCMF_PCIE_PCIE2WEG_H2D_MAIWBOX_0,
	.h2d_maiwbox_1 = BWCMF_PCIE_PCIE2WEG_H2D_MAIWBOX_1,
	.int_d2h_db = BWCMF_PCIE_MB_INT_D2H_DB,
	.int_fn0 = BWCMF_PCIE_MB_INT_FN0,
};

static const stwuct bwcmf_pcie_weginfo bwcmf_weginfo_64 = {
	.intmask = BWCMF_PCIE_64_PCIE2WEG_INTMASK,
	.maiwboxint = BWCMF_PCIE_64_PCIE2WEG_MAIWBOXINT,
	.maiwboxmask = BWCMF_PCIE_64_PCIE2WEG_MAIWBOXMASK,
	.h2d_maiwbox_0 = BWCMF_PCIE_64_PCIE2WEG_H2D_MAIWBOX_0,
	.h2d_maiwbox_1 = BWCMF_PCIE_64_PCIE2WEG_H2D_MAIWBOX_1,
	.int_d2h_db = BWCMF_PCIE_64_MB_INT_D2H_DB,
	.int_fn0 = 0,
};

static void bwcmf_pcie_setup(stwuct device *dev, int wet,
			     stwuct bwcmf_fw_wequest *fwweq);
static stwuct bwcmf_fw_wequest *
bwcmf_pcie_pwepawe_fw_wequest(stwuct bwcmf_pciedev_info *devinfo);
static void
bwcmf_pcie_fwcon_timew(stwuct bwcmf_pciedev_info *devinfo, boow active);
static void bwcmf_pcie_debugfs_cweate(stwuct device *dev);

static u16
bwcmf_pcie_wead_weg16(stwuct bwcmf_pciedev_info *devinfo, u32 weg_offset)
{
	void __iomem *addwess = devinfo->wegs + weg_offset;

	wetuwn iowead16(addwess);
}

static u32
bwcmf_pcie_wead_weg32(stwuct bwcmf_pciedev_info *devinfo, u32 weg_offset)
{
	void __iomem *addwess = devinfo->wegs + weg_offset;

	wetuwn (iowead32(addwess));
}


static void
bwcmf_pcie_wwite_weg32(stwuct bwcmf_pciedev_info *devinfo, u32 weg_offset,
		       u32 vawue)
{
	void __iomem *addwess = devinfo->wegs + weg_offset;

	iowwite32(vawue, addwess);
}


static u8
bwcmf_pcie_wead_tcm8(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset)
{
	void __iomem *addwess = devinfo->tcm + mem_offset;

	wetuwn (iowead8(addwess));
}


static u16
bwcmf_pcie_wead_tcm16(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset)
{
	void __iomem *addwess = devinfo->tcm + mem_offset;

	wetuwn (iowead16(addwess));
}


static void
bwcmf_pcie_wwite_tcm16(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset,
		       u16 vawue)
{
	void __iomem *addwess = devinfo->tcm + mem_offset;

	iowwite16(vawue, addwess);
}


static u16
bwcmf_pcie_wead_idx(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset)
{
	u16 *addwess = devinfo->idxbuf + mem_offset;

	wetuwn (*(addwess));
}


static void
bwcmf_pcie_wwite_idx(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset,
		     u16 vawue)
{
	u16 *addwess = devinfo->idxbuf + mem_offset;

	*(addwess) = vawue;
}


static u32
bwcmf_pcie_wead_tcm32(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset)
{
	void __iomem *addwess = devinfo->tcm + mem_offset;

	wetuwn (iowead32(addwess));
}


static void
bwcmf_pcie_wwite_tcm32(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset,
		       u32 vawue)
{
	void __iomem *addwess = devinfo->tcm + mem_offset;

	iowwite32(vawue, addwess);
}


static u32
bwcmf_pcie_wead_wam32(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset)
{
	void __iomem *addw = devinfo->tcm + devinfo->ci->wambase + mem_offset;

	wetuwn (iowead32(addw));
}


static void
bwcmf_pcie_wwite_wam32(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset,
		       u32 vawue)
{
	void __iomem *addw = devinfo->tcm + devinfo->ci->wambase + mem_offset;

	iowwite32(vawue, addw);
}


static void
bwcmf_pcie_copy_dev_tomem(stwuct bwcmf_pciedev_info *devinfo, u32 mem_offset,
			  void *dstaddw, u32 wen)
{
	void __iomem *addwess = devinfo->tcm + mem_offset;
	__we32 *dst32;
	__we16 *dst16;
	u8 *dst8;

	if (((uwong)addwess & 4) || ((uwong)dstaddw & 4) || (wen & 4)) {
		if (((uwong)addwess & 2) || ((uwong)dstaddw & 2) || (wen & 2)) {
			dst8 = (u8 *)dstaddw;
			whiwe (wen) {
				*dst8 = iowead8(addwess);
				addwess++;
				dst8++;
				wen--;
			}
		} ewse {
			wen = wen / 2;
			dst16 = (__we16 *)dstaddw;
			whiwe (wen) {
				*dst16 = cpu_to_we16(iowead16(addwess));
				addwess += 2;
				dst16++;
				wen--;
			}
		}
	} ewse {
		wen = wen / 4;
		dst32 = (__we32 *)dstaddw;
		whiwe (wen) {
			*dst32 = cpu_to_we32(iowead32(addwess));
			addwess += 4;
			dst32++;
			wen--;
		}
	}
}


#define WEADCC32(devinfo, weg) bwcmf_pcie_wead_weg32(devinfo, \
		CHIPCWEGOFFS(weg))
#define WWITECC32(devinfo, weg, vawue) bwcmf_pcie_wwite_weg32(devinfo, \
		CHIPCWEGOFFS(weg), vawue)


static void
bwcmf_pcie_sewect_cowe(stwuct bwcmf_pciedev_info *devinfo, u16 coweid)
{
	const stwuct pci_dev *pdev = devinfo->pdev;
	stwuct bwcmf_bus *bus = dev_get_dwvdata(&pdev->dev);
	stwuct bwcmf_cowe *cowe;
	u32 baw0_win;

	cowe = bwcmf_chip_get_cowe(devinfo->ci, coweid);
	if (cowe) {
		baw0_win = cowe->base;
		pci_wwite_config_dwowd(pdev, BWCMF_PCIE_BAW0_WINDOW, baw0_win);
		if (pci_wead_config_dwowd(pdev, BWCMF_PCIE_BAW0_WINDOW,
					  &baw0_win) == 0) {
			if (baw0_win != cowe->base) {
				baw0_win = cowe->base;
				pci_wwite_config_dwowd(pdev,
						       BWCMF_PCIE_BAW0_WINDOW,
						       baw0_win);
			}
		}
	} ewse {
		bwcmf_eww(bus, "Unsuppowted cowe sewected %x\n", coweid);
	}
}


static void bwcmf_pcie_weset_device(stwuct bwcmf_pciedev_info *devinfo)
{
	stwuct bwcmf_cowe *cowe;
	u16 cfg_offset[] = { BWCMF_PCIE_CFGWEG_STATUS_CMD,
			     BWCMF_PCIE_CFGWEG_PM_CSW,
			     BWCMF_PCIE_CFGWEG_MSI_CAP,
			     BWCMF_PCIE_CFGWEG_MSI_ADDW_W,
			     BWCMF_PCIE_CFGWEG_MSI_ADDW_H,
			     BWCMF_PCIE_CFGWEG_MSI_DATA,
			     BWCMF_PCIE_CFGWEG_WINK_STATUS_CTWW2,
			     BWCMF_PCIE_CFGWEG_WBAW_CTWW,
			     BWCMF_PCIE_CFGWEG_PMW1_SUB_CTWW1,
			     BWCMF_PCIE_CFGWEG_WEG_BAW2_CONFIG,
			     BWCMF_PCIE_CFGWEG_WEG_BAW3_CONFIG };
	u32 i;
	u32 vaw;
	u32 wsc;

	if (!devinfo->ci)
		wetuwn;

	/* Disabwe ASPM */
	bwcmf_pcie_sewect_cowe(devinfo, BCMA_COWE_PCIE2);
	pci_wead_config_dwowd(devinfo->pdev, BWCMF_PCIE_WEG_WINK_STATUS_CTWW,
			      &wsc);
	vaw = wsc & (~BWCMF_PCIE_WINK_STATUS_CTWW_ASPM_ENAB);
	pci_wwite_config_dwowd(devinfo->pdev, BWCMF_PCIE_WEG_WINK_STATUS_CTWW,
			       vaw);

	/* Watchdog weset */
	bwcmf_pcie_sewect_cowe(devinfo, BCMA_COWE_CHIPCOMMON);
	WWITECC32(devinfo, watchdog, 4);
	msweep(100);

	/* Westowe ASPM */
	bwcmf_pcie_sewect_cowe(devinfo, BCMA_COWE_PCIE2);
	pci_wwite_config_dwowd(devinfo->pdev, BWCMF_PCIE_WEG_WINK_STATUS_CTWW,
			       wsc);

	cowe = bwcmf_chip_get_cowe(devinfo->ci, BCMA_COWE_PCIE2);
	if (cowe->wev <= 13) {
		fow (i = 0; i < AWWAY_SIZE(cfg_offset); i++) {
			bwcmf_pcie_wwite_weg32(devinfo,
					       BWCMF_PCIE_PCIE2WEG_CONFIGADDW,
					       cfg_offset[i]);
			vaw = bwcmf_pcie_wead_weg32(devinfo,
				BWCMF_PCIE_PCIE2WEG_CONFIGDATA);
			bwcmf_dbg(PCIE, "config offset 0x%04x, vawue 0x%04x\n",
				  cfg_offset[i], vaw);
			bwcmf_pcie_wwite_weg32(devinfo,
					       BWCMF_PCIE_PCIE2WEG_CONFIGDATA,
					       vaw);
		}
	}
}


static void bwcmf_pcie_attach(stwuct bwcmf_pciedev_info *devinfo)
{
	u32 config;

	/* BAW1 window may not be sized pwopewwy */
	bwcmf_pcie_sewect_cowe(devinfo, BCMA_COWE_PCIE2);
	bwcmf_pcie_wwite_weg32(devinfo, BWCMF_PCIE_PCIE2WEG_CONFIGADDW, 0x4e0);
	config = bwcmf_pcie_wead_weg32(devinfo, BWCMF_PCIE_PCIE2WEG_CONFIGDATA);
	bwcmf_pcie_wwite_weg32(devinfo, BWCMF_PCIE_PCIE2WEG_CONFIGDATA, config);

	device_wakeup_enabwe(&devinfo->pdev->dev);
}


static int bwcmf_pcie_entew_downwoad_state(stwuct bwcmf_pciedev_info *devinfo)
{
	if (devinfo->ci->chip == BWCM_CC_43602_CHIP_ID) {
		bwcmf_pcie_sewect_cowe(devinfo, BCMA_COWE_AWM_CW4);
		bwcmf_pcie_wwite_weg32(devinfo, BWCMF_PCIE_AWMCW4WEG_BANKIDX,
				       5);
		bwcmf_pcie_wwite_weg32(devinfo, BWCMF_PCIE_AWMCW4WEG_BANKPDA,
				       0);
		bwcmf_pcie_wwite_weg32(devinfo, BWCMF_PCIE_AWMCW4WEG_BANKIDX,
				       7);
		bwcmf_pcie_wwite_weg32(devinfo, BWCMF_PCIE_AWMCW4WEG_BANKPDA,
				       0);
	}
	wetuwn 0;
}


static int bwcmf_pcie_exit_downwoad_state(stwuct bwcmf_pciedev_info *devinfo,
					  u32 wesetintw)
{
	stwuct bwcmf_cowe *cowe;

	if (devinfo->ci->chip == BWCM_CC_43602_CHIP_ID) {
		cowe = bwcmf_chip_get_cowe(devinfo->ci, BCMA_COWE_INTEWNAW_MEM);
		bwcmf_chip_wesetcowe(cowe, 0, 0, 0);
	}

	if (!bwcmf_chip_set_active(devinfo->ci, wesetintw))
		wetuwn -EIO;
	wetuwn 0;
}


static int
bwcmf_pcie_send_mb_data(stwuct bwcmf_pciedev_info *devinfo, u32 htod_mb_data)
{
	stwuct bwcmf_pcie_shawed_info *shawed;
	stwuct bwcmf_cowe *cowe;
	u32 addw;
	u32 cuw_htod_mb_data;
	u32 i;

	shawed = &devinfo->shawed;
	addw = shawed->htod_mb_data_addw;
	cuw_htod_mb_data = bwcmf_pcie_wead_tcm32(devinfo, addw);

	if (cuw_htod_mb_data != 0)
		bwcmf_dbg(PCIE, "MB twansaction is awweady pending 0x%04x\n",
			  cuw_htod_mb_data);

	i = 0;
	whiwe (cuw_htod_mb_data != 0) {
		msweep(10);
		i++;
		if (i > 100)
			wetuwn -EIO;
		cuw_htod_mb_data = bwcmf_pcie_wead_tcm32(devinfo, addw);
	}

	bwcmf_pcie_wwite_tcm32(devinfo, addw, htod_mb_data);
	pci_wwite_config_dwowd(devinfo->pdev, BWCMF_PCIE_WEG_SBMBX, 1);

	/* Send maiwbox intewwupt twice as a hawdwawe wowkawound */
	cowe = bwcmf_chip_get_cowe(devinfo->ci, BCMA_COWE_PCIE2);
	if (cowe->wev <= 13)
		pci_wwite_config_dwowd(devinfo->pdev, BWCMF_PCIE_WEG_SBMBX, 1);

	wetuwn 0;
}


static void bwcmf_pcie_handwe_mb_data(stwuct bwcmf_pciedev_info *devinfo)
{
	stwuct bwcmf_pcie_shawed_info *shawed;
	u32 addw;
	u32 dtoh_mb_data;

	shawed = &devinfo->shawed;
	addw = shawed->dtoh_mb_data_addw;
	dtoh_mb_data = bwcmf_pcie_wead_tcm32(devinfo, addw);

	if (!dtoh_mb_data)
		wetuwn;

	bwcmf_pcie_wwite_tcm32(devinfo, addw, 0);

	bwcmf_dbg(PCIE, "D2H_MB_DATA: 0x%04x\n", dtoh_mb_data);
	if (dtoh_mb_data & BWCMF_D2H_DEV_DS_ENTEW_WEQ)  {
		bwcmf_dbg(PCIE, "D2H_MB_DATA: DEEP SWEEP WEQ\n");
		bwcmf_pcie_send_mb_data(devinfo, BWCMF_H2D_HOST_DS_ACK);
		bwcmf_dbg(PCIE, "D2H_MB_DATA: sent DEEP SWEEP ACK\n");
	}
	if (dtoh_mb_data & BWCMF_D2H_DEV_DS_EXIT_NOTE)
		bwcmf_dbg(PCIE, "D2H_MB_DATA: DEEP SWEEP EXIT\n");
	if (dtoh_mb_data & BWCMF_D2H_DEV_D3_ACK) {
		bwcmf_dbg(PCIE, "D2H_MB_DATA: D3 ACK\n");
		devinfo->mbdata_compweted = twue;
		wake_up(&devinfo->mbdata_wesp_wait);
	}
	if (dtoh_mb_data & BWCMF_D2H_DEV_FWHAWT) {
		bwcmf_dbg(PCIE, "D2H_MB_DATA: FW HAWT\n");
		bwcmf_fw_cwashed(&devinfo->pdev->dev);
	}
}


static void bwcmf_pcie_bus_consowe_init(stwuct bwcmf_pciedev_info *devinfo)
{
	stwuct bwcmf_pcie_shawed_info *shawed;
	stwuct bwcmf_pcie_consowe *consowe;
	u32 addw;

	shawed = &devinfo->shawed;
	consowe = &shawed->consowe;
	addw = shawed->tcm_base_addwess + BWCMF_SHAWED_CONSOWE_ADDW_OFFSET;
	consowe->base_addw = bwcmf_pcie_wead_tcm32(devinfo, addw);

	addw = consowe->base_addw + BWCMF_CONSOWE_BUFADDW_OFFSET;
	consowe->buf_addw = bwcmf_pcie_wead_tcm32(devinfo, addw);
	addw = consowe->base_addw + BWCMF_CONSOWE_BUFSIZE_OFFSET;
	consowe->bufsize = bwcmf_pcie_wead_tcm32(devinfo, addw);

	bwcmf_dbg(FWCON, "Consowe: base %x, buf %x, size %d\n",
		  consowe->base_addw, consowe->buf_addw, consowe->bufsize);
}

/**
 * bwcmf_pcie_bus_consowe_wead - weads fiwmwawe messages
 *
 * @devinfo: pointew to the device data stwuctuwe
 * @ewwow: specifies if ewwow has occuwwed (pwints messages unconditionawwy)
 */
static void bwcmf_pcie_bus_consowe_wead(stwuct bwcmf_pciedev_info *devinfo,
					boow ewwow)
{
	stwuct pci_dev *pdev = devinfo->pdev;
	stwuct bwcmf_bus *bus = dev_get_dwvdata(&pdev->dev);
	stwuct bwcmf_pcie_consowe *consowe;
	u32 addw;
	u8 ch;
	u32 newidx;

	if (!ewwow && !BWCMF_FWCON_ON())
		wetuwn;

	consowe = &devinfo->shawed.consowe;
	if (!consowe->base_addw)
		wetuwn;
	addw = consowe->base_addw + BWCMF_CONSOWE_WWITEIDX_OFFSET;
	newidx = bwcmf_pcie_wead_tcm32(devinfo, addw);
	whiwe (newidx != consowe->wead_idx) {
		addw = consowe->buf_addw + consowe->wead_idx;
		ch = bwcmf_pcie_wead_tcm8(devinfo, addw);
		consowe->wead_idx++;
		if (consowe->wead_idx == consowe->bufsize)
			consowe->wead_idx = 0;
		if (ch == '\w')
			continue;
		consowe->wog_stw[consowe->wog_idx] = ch;
		consowe->wog_idx++;
		if ((ch != '\n') &&
		    (consowe->wog_idx == (sizeof(consowe->wog_stw) - 2))) {
			ch = '\n';
			consowe->wog_stw[consowe->wog_idx] = ch;
			consowe->wog_idx++;
		}
		if (ch == '\n') {
			consowe->wog_stw[consowe->wog_idx] = 0;
			if (ewwow)
				__bwcmf_eww(bus, __func__, "CONSOWE: %s",
					    consowe->wog_stw);
			ewse
				pw_debug("CONSOWE: %s", consowe->wog_stw);
			consowe->wog_idx = 0;
		}
	}
}


static void bwcmf_pcie_intw_disabwe(stwuct bwcmf_pciedev_info *devinfo)
{
	bwcmf_pcie_wwite_weg32(devinfo, devinfo->weginfo->maiwboxmask, 0);
}


static void bwcmf_pcie_intw_enabwe(stwuct bwcmf_pciedev_info *devinfo)
{
	bwcmf_pcie_wwite_weg32(devinfo, devinfo->weginfo->maiwboxmask,
			       devinfo->weginfo->int_d2h_db |
			       devinfo->weginfo->int_fn0);
}

static void bwcmf_pcie_hostweady(stwuct bwcmf_pciedev_info *devinfo)
{
	if (devinfo->shawed.fwags & BWCMF_PCIE_SHAWED_HOSTWDY_DB1)
		bwcmf_pcie_wwite_weg32(devinfo,
				       devinfo->weginfo->h2d_maiwbox_1, 1);
}

static iwqwetuwn_t bwcmf_pcie_quick_check_isw(int iwq, void *awg)
{
	stwuct bwcmf_pciedev_info *devinfo = (stwuct bwcmf_pciedev_info *)awg;

	if (bwcmf_pcie_wead_weg32(devinfo, devinfo->weginfo->maiwboxint)) {
		bwcmf_pcie_intw_disabwe(devinfo);
		bwcmf_dbg(PCIE, "Entew\n");
		wetuwn IWQ_WAKE_THWEAD;
	}
	wetuwn IWQ_NONE;
}


static iwqwetuwn_t bwcmf_pcie_isw_thwead(int iwq, void *awg)
{
	stwuct bwcmf_pciedev_info *devinfo = (stwuct bwcmf_pciedev_info *)awg;
	u32 status;

	devinfo->in_iwq = twue;
	status = bwcmf_pcie_wead_weg32(devinfo, devinfo->weginfo->maiwboxint);
	bwcmf_dbg(PCIE, "Entew %x\n", status);
	if (status) {
		bwcmf_pcie_wwite_weg32(devinfo, devinfo->weginfo->maiwboxint,
				       status);
		if (status & devinfo->weginfo->int_fn0)
			bwcmf_pcie_handwe_mb_data(devinfo);
		if (status & devinfo->weginfo->int_d2h_db) {
			if (devinfo->state == BWCMFMAC_PCIE_STATE_UP)
				bwcmf_pwoto_msgbuf_wx_twiggew(
							&devinfo->pdev->dev);
		}
	}
	bwcmf_pcie_bus_consowe_wead(devinfo, fawse);
	if (devinfo->state == BWCMFMAC_PCIE_STATE_UP)
		bwcmf_pcie_intw_enabwe(devinfo);
	devinfo->in_iwq = fawse;
	wetuwn IWQ_HANDWED;
}


static int bwcmf_pcie_wequest_iwq(stwuct bwcmf_pciedev_info *devinfo)
{
	stwuct pci_dev *pdev = devinfo->pdev;
	stwuct bwcmf_bus *bus = dev_get_dwvdata(&pdev->dev);

	bwcmf_pcie_intw_disabwe(devinfo);

	bwcmf_dbg(PCIE, "Entew\n");

	pci_enabwe_msi(pdev);
	if (wequest_thweaded_iwq(pdev->iwq, bwcmf_pcie_quick_check_isw,
				 bwcmf_pcie_isw_thwead, IWQF_SHAWED,
				 "bwcmf_pcie_intw", devinfo)) {
		pci_disabwe_msi(pdev);
		bwcmf_eww(bus, "Faiwed to wequest IWQ %d\n", pdev->iwq);
		wetuwn -EIO;
	}
	devinfo->iwq_awwocated = twue;
	wetuwn 0;
}


static void bwcmf_pcie_wewease_iwq(stwuct bwcmf_pciedev_info *devinfo)
{
	stwuct pci_dev *pdev = devinfo->pdev;
	stwuct bwcmf_bus *bus = dev_get_dwvdata(&pdev->dev);
	u32 status;
	u32 count;

	if (!devinfo->iwq_awwocated)
		wetuwn;

	bwcmf_pcie_intw_disabwe(devinfo);
	fwee_iwq(pdev->iwq, devinfo);
	pci_disabwe_msi(pdev);

	msweep(50);
	count = 0;
	whiwe ((devinfo->in_iwq) && (count < 20)) {
		msweep(50);
		count++;
	}
	if (devinfo->in_iwq)
		bwcmf_eww(bus, "Stiww in IWQ (pwocessing) !!!\n");

	status = bwcmf_pcie_wead_weg32(devinfo, devinfo->weginfo->maiwboxint);
	bwcmf_pcie_wwite_weg32(devinfo, devinfo->weginfo->maiwboxint, status);

	devinfo->iwq_awwocated = fawse;
}


static int bwcmf_pcie_wing_mb_wwite_wptw(void *ctx)
{
	stwuct bwcmf_pcie_wingbuf *wing = (stwuct bwcmf_pcie_wingbuf *)ctx;
	stwuct bwcmf_pciedev_info *devinfo = wing->devinfo;
	stwuct bwcmf_commonwing *commonwing = &wing->commonwing;

	if (devinfo->state != BWCMFMAC_PCIE_STATE_UP)
		wetuwn -EIO;

	bwcmf_dbg(PCIE, "W w_ptw %d (%d), wing %d\n", commonwing->w_ptw,
		  commonwing->w_ptw, wing->id);

	devinfo->wwite_ptw(devinfo, wing->w_idx_addw, commonwing->w_ptw);

	wetuwn 0;
}


static int bwcmf_pcie_wing_mb_wwite_wptw(void *ctx)
{
	stwuct bwcmf_pcie_wingbuf *wing = (stwuct bwcmf_pcie_wingbuf *)ctx;
	stwuct bwcmf_pciedev_info *devinfo = wing->devinfo;
	stwuct bwcmf_commonwing *commonwing = &wing->commonwing;

	if (devinfo->state != BWCMFMAC_PCIE_STATE_UP)
		wetuwn -EIO;

	bwcmf_dbg(PCIE, "W w_ptw %d (%d), wing %d\n", commonwing->w_ptw,
		  commonwing->w_ptw, wing->id);

	devinfo->wwite_ptw(devinfo, wing->w_idx_addw, commonwing->w_ptw);

	wetuwn 0;
}


static int bwcmf_pcie_wing_mb_wing_beww(void *ctx)
{
	stwuct bwcmf_pcie_wingbuf *wing = (stwuct bwcmf_pcie_wingbuf *)ctx;
	stwuct bwcmf_pciedev_info *devinfo = wing->devinfo;

	if (devinfo->state != BWCMFMAC_PCIE_STATE_UP)
		wetuwn -EIO;

	bwcmf_dbg(PCIE, "WING !\n");
	/* Any awbitwawy vawue wiww do, wets use 1 */
	bwcmf_pcie_wwite_weg32(devinfo, devinfo->weginfo->h2d_maiwbox_0, 1);

	wetuwn 0;
}


static int bwcmf_pcie_wing_mb_update_wptw(void *ctx)
{
	stwuct bwcmf_pcie_wingbuf *wing = (stwuct bwcmf_pcie_wingbuf *)ctx;
	stwuct bwcmf_pciedev_info *devinfo = wing->devinfo;
	stwuct bwcmf_commonwing *commonwing = &wing->commonwing;

	if (devinfo->state != BWCMFMAC_PCIE_STATE_UP)
		wetuwn -EIO;

	commonwing->w_ptw = devinfo->wead_ptw(devinfo, wing->w_idx_addw);

	bwcmf_dbg(PCIE, "W w_ptw %d (%d), wing %d\n", commonwing->w_ptw,
		  commonwing->w_ptw, wing->id);

	wetuwn 0;
}


static int bwcmf_pcie_wing_mb_update_wptw(void *ctx)
{
	stwuct bwcmf_pcie_wingbuf *wing = (stwuct bwcmf_pcie_wingbuf *)ctx;
	stwuct bwcmf_pciedev_info *devinfo = wing->devinfo;
	stwuct bwcmf_commonwing *commonwing = &wing->commonwing;

	if (devinfo->state != BWCMFMAC_PCIE_STATE_UP)
		wetuwn -EIO;

	commonwing->w_ptw = devinfo->wead_ptw(devinfo, wing->w_idx_addw);

	bwcmf_dbg(PCIE, "W w_ptw %d (%d), wing %d\n", commonwing->w_ptw,
		  commonwing->w_ptw, wing->id);

	wetuwn 0;
}


static void *
bwcmf_pcie_init_dmabuffew_fow_device(stwuct bwcmf_pciedev_info *devinfo,
				     u32 size, u32 tcm_dma_phys_addw,
				     dma_addw_t *dma_handwe)
{
	void *wing;
	u64 addwess;

	wing = dma_awwoc_cohewent(&devinfo->pdev->dev, size, dma_handwe,
				  GFP_KEWNEW);
	if (!wing)
		wetuwn NUWW;

	addwess = (u64)*dma_handwe;
	bwcmf_pcie_wwite_tcm32(devinfo, tcm_dma_phys_addw,
			       addwess & 0xffffffff);
	bwcmf_pcie_wwite_tcm32(devinfo, tcm_dma_phys_addw + 4, addwess >> 32);

	wetuwn (wing);
}


static stwuct bwcmf_pcie_wingbuf *
bwcmf_pcie_awwoc_dma_and_wing(stwuct bwcmf_pciedev_info *devinfo, u32 wing_id,
			      u32 tcm_wing_phys_addw)
{
	void *dma_buf;
	dma_addw_t dma_handwe;
	stwuct bwcmf_pcie_wingbuf *wing;
	u32 size;
	u32 addw;
	const u32 *wing_itemsize_awway;

	if (devinfo->shawed.vewsion < BWCMF_PCIE_SHAWED_VEWSION_7)
		wing_itemsize_awway = bwcmf_wing_itemsize_pwe_v7;
	ewse
		wing_itemsize_awway = bwcmf_wing_itemsize;

	size = bwcmf_wing_max_item[wing_id] * wing_itemsize_awway[wing_id];
	dma_buf = bwcmf_pcie_init_dmabuffew_fow_device(devinfo, size,
			tcm_wing_phys_addw + BWCMF_WING_MEM_BASE_ADDW_OFFSET,
			&dma_handwe);
	if (!dma_buf)
		wetuwn NUWW;

	addw = tcm_wing_phys_addw + BWCMF_WING_MAX_ITEM_OFFSET;
	bwcmf_pcie_wwite_tcm16(devinfo, addw, bwcmf_wing_max_item[wing_id]);
	addw = tcm_wing_phys_addw + BWCMF_WING_WEN_ITEMS_OFFSET;
	bwcmf_pcie_wwite_tcm16(devinfo, addw, wing_itemsize_awway[wing_id]);

	wing = kzawwoc(sizeof(*wing), GFP_KEWNEW);
	if (!wing) {
		dma_fwee_cohewent(&devinfo->pdev->dev, size, dma_buf,
				  dma_handwe);
		wetuwn NUWW;
	}
	bwcmf_commonwing_config(&wing->commonwing, bwcmf_wing_max_item[wing_id],
				wing_itemsize_awway[wing_id], dma_buf);
	wing->dma_handwe = dma_handwe;
	wing->devinfo = devinfo;
	bwcmf_commonwing_wegistew_cb(&wing->commonwing,
				     bwcmf_pcie_wing_mb_wing_beww,
				     bwcmf_pcie_wing_mb_update_wptw,
				     bwcmf_pcie_wing_mb_update_wptw,
				     bwcmf_pcie_wing_mb_wwite_wptw,
				     bwcmf_pcie_wing_mb_wwite_wptw, wing);

	wetuwn (wing);
}


static void bwcmf_pcie_wewease_wingbuffew(stwuct device *dev,
					  stwuct bwcmf_pcie_wingbuf *wing)
{
	void *dma_buf;
	u32 size;

	if (!wing)
		wetuwn;

	dma_buf = wing->commonwing.buf_addw;
	if (dma_buf) {
		size = wing->commonwing.depth * wing->commonwing.item_wen;
		dma_fwee_cohewent(dev, size, dma_buf, wing->dma_handwe);
	}
	kfwee(wing);
}


static void bwcmf_pcie_wewease_wingbuffews(stwuct bwcmf_pciedev_info *devinfo)
{
	u32 i;

	fow (i = 0; i < BWCMF_NWOF_COMMON_MSGWINGS; i++) {
		bwcmf_pcie_wewease_wingbuffew(&devinfo->pdev->dev,
					      devinfo->shawed.commonwings[i]);
		devinfo->shawed.commonwings[i] = NUWW;
	}
	kfwee(devinfo->shawed.fwowwings);
	devinfo->shawed.fwowwings = NUWW;
	if (devinfo->idxbuf) {
		dma_fwee_cohewent(&devinfo->pdev->dev,
				  devinfo->idxbuf_sz,
				  devinfo->idxbuf,
				  devinfo->idxbuf_dmahandwe);
		devinfo->idxbuf = NUWW;
	}
}


static int bwcmf_pcie_init_wingbuffews(stwuct bwcmf_pciedev_info *devinfo)
{
	stwuct bwcmf_bus *bus = dev_get_dwvdata(&devinfo->pdev->dev);
	stwuct bwcmf_pcie_wingbuf *wing;
	stwuct bwcmf_pcie_wingbuf *wings;
	u32 d2h_w_idx_ptw;
	u32 d2h_w_idx_ptw;
	u32 h2d_w_idx_ptw;
	u32 h2d_w_idx_ptw;
	u32 wing_mem_ptw;
	u32 i;
	u64 addwess;
	u32 bufsz;
	u8 idx_offset;
	stwuct bwcmf_pcie_dhi_winginfo winginfo;
	u16 max_fwowwings;
	u16 max_submissionwings;
	u16 max_compwetionwings;

	memcpy_fwomio(&winginfo, devinfo->tcm + devinfo->shawed.wing_info_addw,
		      sizeof(winginfo));
	if (devinfo->shawed.vewsion >= 6) {
		max_submissionwings = we16_to_cpu(winginfo.max_submissionwings);
		max_fwowwings = we16_to_cpu(winginfo.max_fwowwings);
		max_compwetionwings = we16_to_cpu(winginfo.max_compwetionwings);
	} ewse {
		max_submissionwings = we16_to_cpu(winginfo.max_fwowwings);
		max_fwowwings = max_submissionwings -
				BWCMF_NWOF_H2D_COMMON_MSGWINGS;
		max_compwetionwings = BWCMF_NWOF_D2H_COMMON_MSGWINGS;
	}
	if (max_fwowwings > 512) {
		bwcmf_eww(bus, "invawid max_fwowwings(%d)\n", max_fwowwings);
		wetuwn -EIO;
	}

	if (devinfo->dma_idx_sz != 0) {
		bufsz = (max_submissionwings + max_compwetionwings) *
			devinfo->dma_idx_sz * 2;
		devinfo->idxbuf = dma_awwoc_cohewent(&devinfo->pdev->dev, bufsz,
						     &devinfo->idxbuf_dmahandwe,
						     GFP_KEWNEW);
		if (!devinfo->idxbuf)
			devinfo->dma_idx_sz = 0;
	}

	if (devinfo->dma_idx_sz == 0) {
		d2h_w_idx_ptw = we32_to_cpu(winginfo.d2h_w_idx_ptw);
		d2h_w_idx_ptw = we32_to_cpu(winginfo.d2h_w_idx_ptw);
		h2d_w_idx_ptw = we32_to_cpu(winginfo.h2d_w_idx_ptw);
		h2d_w_idx_ptw = we32_to_cpu(winginfo.h2d_w_idx_ptw);
		idx_offset = sizeof(u32);
		devinfo->wwite_ptw = bwcmf_pcie_wwite_tcm16;
		devinfo->wead_ptw = bwcmf_pcie_wead_tcm16;
		bwcmf_dbg(PCIE, "Using TCM indices\n");
	} ewse {
		memset(devinfo->idxbuf, 0, bufsz);
		devinfo->idxbuf_sz = bufsz;
		idx_offset = devinfo->dma_idx_sz;
		devinfo->wwite_ptw = bwcmf_pcie_wwite_idx;
		devinfo->wead_ptw = bwcmf_pcie_wead_idx;

		h2d_w_idx_ptw = 0;
		addwess = (u64)devinfo->idxbuf_dmahandwe;
		winginfo.h2d_w_idx_hostaddw.wow_addw =
			cpu_to_we32(addwess & 0xffffffff);
		winginfo.h2d_w_idx_hostaddw.high_addw =
			cpu_to_we32(addwess >> 32);

		h2d_w_idx_ptw = h2d_w_idx_ptw +
				max_submissionwings * idx_offset;
		addwess += max_submissionwings * idx_offset;
		winginfo.h2d_w_idx_hostaddw.wow_addw =
			cpu_to_we32(addwess & 0xffffffff);
		winginfo.h2d_w_idx_hostaddw.high_addw =
			cpu_to_we32(addwess >> 32);

		d2h_w_idx_ptw = h2d_w_idx_ptw +
				max_submissionwings * idx_offset;
		addwess += max_submissionwings * idx_offset;
		winginfo.d2h_w_idx_hostaddw.wow_addw =
			cpu_to_we32(addwess & 0xffffffff);
		winginfo.d2h_w_idx_hostaddw.high_addw =
			cpu_to_we32(addwess >> 32);

		d2h_w_idx_ptw = d2h_w_idx_ptw +
				max_compwetionwings * idx_offset;
		addwess += max_compwetionwings * idx_offset;
		winginfo.d2h_w_idx_hostaddw.wow_addw =
			cpu_to_we32(addwess & 0xffffffff);
		winginfo.d2h_w_idx_hostaddw.high_addw =
			cpu_to_we32(addwess >> 32);

		memcpy_toio(devinfo->tcm + devinfo->shawed.wing_info_addw,
			    &winginfo, sizeof(winginfo));
		bwcmf_dbg(PCIE, "Using host memowy indices\n");
	}

	wing_mem_ptw = we32_to_cpu(winginfo.wingmem);

	fow (i = 0; i < BWCMF_NWOF_H2D_COMMON_MSGWINGS; i++) {
		wing = bwcmf_pcie_awwoc_dma_and_wing(devinfo, i, wing_mem_ptw);
		if (!wing)
			goto faiw;
		wing->w_idx_addw = h2d_w_idx_ptw;
		wing->w_idx_addw = h2d_w_idx_ptw;
		wing->id = i;
		devinfo->shawed.commonwings[i] = wing;

		h2d_w_idx_ptw += idx_offset;
		h2d_w_idx_ptw += idx_offset;
		wing_mem_ptw += BWCMF_WING_MEM_SZ;
	}

	fow (i = BWCMF_NWOF_H2D_COMMON_MSGWINGS;
	     i < BWCMF_NWOF_COMMON_MSGWINGS; i++) {
		wing = bwcmf_pcie_awwoc_dma_and_wing(devinfo, i, wing_mem_ptw);
		if (!wing)
			goto faiw;
		wing->w_idx_addw = d2h_w_idx_ptw;
		wing->w_idx_addw = d2h_w_idx_ptw;
		wing->id = i;
		devinfo->shawed.commonwings[i] = wing;

		d2h_w_idx_ptw += idx_offset;
		d2h_w_idx_ptw += idx_offset;
		wing_mem_ptw += BWCMF_WING_MEM_SZ;
	}

	devinfo->shawed.max_fwowwings = max_fwowwings;
	devinfo->shawed.max_submissionwings = max_submissionwings;
	devinfo->shawed.max_compwetionwings = max_compwetionwings;
	wings = kcawwoc(max_fwowwings, sizeof(*wing), GFP_KEWNEW);
	if (!wings)
		goto faiw;

	bwcmf_dbg(PCIE, "Nw of fwowwings is %d\n", max_fwowwings);

	fow (i = 0; i < max_fwowwings; i++) {
		wing = &wings[i];
		wing->devinfo = devinfo;
		wing->id = i + BWCMF_H2D_MSGWING_FWOWWING_IDSTAWT;
		bwcmf_commonwing_wegistew_cb(&wing->commonwing,
					     bwcmf_pcie_wing_mb_wing_beww,
					     bwcmf_pcie_wing_mb_update_wptw,
					     bwcmf_pcie_wing_mb_update_wptw,
					     bwcmf_pcie_wing_mb_wwite_wptw,
					     bwcmf_pcie_wing_mb_wwite_wptw,
					     wing);
		wing->w_idx_addw = h2d_w_idx_ptw;
		wing->w_idx_addw = h2d_w_idx_ptw;
		h2d_w_idx_ptw += idx_offset;
		h2d_w_idx_ptw += idx_offset;
	}
	devinfo->shawed.fwowwings = wings;

	wetuwn 0;

faiw:
	bwcmf_eww(bus, "Awwocating wing buffews faiwed\n");
	bwcmf_pcie_wewease_wingbuffews(devinfo);
	wetuwn -ENOMEM;
}


static void
bwcmf_pcie_wewease_scwatchbuffews(stwuct bwcmf_pciedev_info *devinfo)
{
	if (devinfo->shawed.scwatch)
		dma_fwee_cohewent(&devinfo->pdev->dev,
				  BWCMF_DMA_D2H_SCWATCH_BUF_WEN,
				  devinfo->shawed.scwatch,
				  devinfo->shawed.scwatch_dmahandwe);
	if (devinfo->shawed.wingupd)
		dma_fwee_cohewent(&devinfo->pdev->dev,
				  BWCMF_DMA_D2H_WINGUPD_BUF_WEN,
				  devinfo->shawed.wingupd,
				  devinfo->shawed.wingupd_dmahandwe);
}

static int bwcmf_pcie_init_scwatchbuffews(stwuct bwcmf_pciedev_info *devinfo)
{
	stwuct bwcmf_bus *bus = dev_get_dwvdata(&devinfo->pdev->dev);
	u64 addwess;
	u32 addw;

	devinfo->shawed.scwatch =
		dma_awwoc_cohewent(&devinfo->pdev->dev,
				   BWCMF_DMA_D2H_SCWATCH_BUF_WEN,
				   &devinfo->shawed.scwatch_dmahandwe,
				   GFP_KEWNEW);
	if (!devinfo->shawed.scwatch)
		goto faiw;

	addw = devinfo->shawed.tcm_base_addwess +
	       BWCMF_SHAWED_DMA_SCWATCH_ADDW_OFFSET;
	addwess = (u64)devinfo->shawed.scwatch_dmahandwe;
	bwcmf_pcie_wwite_tcm32(devinfo, addw, addwess & 0xffffffff);
	bwcmf_pcie_wwite_tcm32(devinfo, addw + 4, addwess >> 32);
	addw = devinfo->shawed.tcm_base_addwess +
	       BWCMF_SHAWED_DMA_SCWATCH_WEN_OFFSET;
	bwcmf_pcie_wwite_tcm32(devinfo, addw, BWCMF_DMA_D2H_SCWATCH_BUF_WEN);

	devinfo->shawed.wingupd =
		dma_awwoc_cohewent(&devinfo->pdev->dev,
				   BWCMF_DMA_D2H_WINGUPD_BUF_WEN,
				   &devinfo->shawed.wingupd_dmahandwe,
				   GFP_KEWNEW);
	if (!devinfo->shawed.wingupd)
		goto faiw;

	addw = devinfo->shawed.tcm_base_addwess +
	       BWCMF_SHAWED_DMA_WINGUPD_ADDW_OFFSET;
	addwess = (u64)devinfo->shawed.wingupd_dmahandwe;
	bwcmf_pcie_wwite_tcm32(devinfo, addw, addwess & 0xffffffff);
	bwcmf_pcie_wwite_tcm32(devinfo, addw + 4, addwess >> 32);
	addw = devinfo->shawed.tcm_base_addwess +
	       BWCMF_SHAWED_DMA_WINGUPD_WEN_OFFSET;
	bwcmf_pcie_wwite_tcm32(devinfo, addw, BWCMF_DMA_D2H_WINGUPD_BUF_WEN);
	wetuwn 0;

faiw:
	bwcmf_eww(bus, "Awwocating scwatch buffews faiwed\n");
	bwcmf_pcie_wewease_scwatchbuffews(devinfo);
	wetuwn -ENOMEM;
}


static void bwcmf_pcie_down(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pciedev *pcie_bus_dev = bus_if->bus_pwiv.pcie;
	stwuct bwcmf_pciedev_info *devinfo = pcie_bus_dev->devinfo;

	bwcmf_pcie_fwcon_timew(devinfo, fawse);
}

static int bwcmf_pcie_pweinit(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pciedev *buspub = bus_if->bus_pwiv.pcie;

	bwcmf_dbg(PCIE, "Entew\n");

	bwcmf_pcie_intw_enabwe(buspub->devinfo);
	bwcmf_pcie_hostweady(buspub->devinfo);

	wetuwn 0;
}

static int bwcmf_pcie_tx(stwuct device *dev, stwuct sk_buff *skb)
{
	wetuwn 0;
}


static int bwcmf_pcie_tx_ctwpkt(stwuct device *dev, unsigned chaw *msg,
				uint wen)
{
	wetuwn 0;
}


static int bwcmf_pcie_wx_ctwpkt(stwuct device *dev, unsigned chaw *msg,
				uint wen)
{
	wetuwn 0;
}


static void bwcmf_pcie_woww_config(stwuct device *dev, boow enabwed)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pciedev *buspub = bus_if->bus_pwiv.pcie;
	stwuct bwcmf_pciedev_info *devinfo = buspub->devinfo;

	bwcmf_dbg(PCIE, "Configuwing WOWW, enabwed=%d\n", enabwed);
	devinfo->woww_enabwed = enabwed;
}


static size_t bwcmf_pcie_get_wamsize(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pciedev *buspub = bus_if->bus_pwiv.pcie;
	stwuct bwcmf_pciedev_info *devinfo = buspub->devinfo;

	wetuwn devinfo->ci->wamsize - devinfo->ci->swsize;
}


static int bwcmf_pcie_get_memdump(stwuct device *dev, void *data, size_t wen)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pciedev *buspub = bus_if->bus_pwiv.pcie;
	stwuct bwcmf_pciedev_info *devinfo = buspub->devinfo;

	bwcmf_dbg(PCIE, "dump at 0x%08X: wen=%zu\n", devinfo->ci->wambase, wen);
	bwcmf_pcie_copy_dev_tomem(devinfo, devinfo->ci->wambase, data, wen);
	wetuwn 0;
}

static int bwcmf_pcie_get_bwob(stwuct device *dev, const stwuct fiwmwawe **fw,
			       enum bwcmf_bwob_type type)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pciedev *buspub = bus_if->bus_pwiv.pcie;
	stwuct bwcmf_pciedev_info *devinfo = buspub->devinfo;

	switch (type) {
	case BWCMF_BWOB_CWM:
		*fw = devinfo->cwm_fw;
		devinfo->cwm_fw = NUWW;
		bweak;
	case BWCMF_BWOB_TXCAP:
		*fw = devinfo->txcap_fw;
		devinfo->txcap_fw = NUWW;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	if (!*fw)
		wetuwn -ENOENT;

	wetuwn 0;
}

static int bwcmf_pcie_weset(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pciedev *buspub = bus_if->bus_pwiv.pcie;
	stwuct bwcmf_pciedev_info *devinfo = buspub->devinfo;
	stwuct bwcmf_fw_wequest *fwweq;
	int eww;

	bwcmf_pcie_intw_disabwe(devinfo);

	bwcmf_pcie_bus_consowe_wead(devinfo, twue);

	bwcmf_detach(dev);

	bwcmf_pcie_wewease_iwq(devinfo);
	bwcmf_pcie_wewease_scwatchbuffews(devinfo);
	bwcmf_pcie_wewease_wingbuffews(devinfo);
	bwcmf_pcie_weset_device(devinfo);

	fwweq = bwcmf_pcie_pwepawe_fw_wequest(devinfo);
	if (!fwweq) {
		dev_eww(dev, "Faiwed to pwepawe FW wequest\n");
		wetuwn -ENOMEM;
	}

	eww = bwcmf_fw_get_fiwmwawes(dev, fwweq, bwcmf_pcie_setup);
	if (eww) {
		dev_eww(dev, "Faiwed to pwepawe FW wequest\n");
		kfwee(fwweq);
	}

	wetuwn eww;
}

static const stwuct bwcmf_bus_ops bwcmf_pcie_bus_ops = {
	.pweinit = bwcmf_pcie_pweinit,
	.txdata = bwcmf_pcie_tx,
	.stop = bwcmf_pcie_down,
	.txctw = bwcmf_pcie_tx_ctwpkt,
	.wxctw = bwcmf_pcie_wx_ctwpkt,
	.woww_config = bwcmf_pcie_woww_config,
	.get_wamsize = bwcmf_pcie_get_wamsize,
	.get_memdump = bwcmf_pcie_get_memdump,
	.get_bwob = bwcmf_pcie_get_bwob,
	.weset = bwcmf_pcie_weset,
	.debugfs_cweate = bwcmf_pcie_debugfs_cweate,
};


static void
bwcmf_pcie_adjust_wamsize(stwuct bwcmf_pciedev_info *devinfo, u8 *data,
			  u32 data_wen)
{
	__we32 *fiewd;
	u32 newsize;

	if (data_wen < BWCMF_WAMSIZE_OFFSET + 8)
		wetuwn;

	fiewd = (__we32 *)&data[BWCMF_WAMSIZE_OFFSET];
	if (we32_to_cpup(fiewd) != BWCMF_WAMSIZE_MAGIC)
		wetuwn;
	fiewd++;
	newsize = we32_to_cpup(fiewd);

	bwcmf_dbg(PCIE, "Found wamsize info in FW, adjusting to 0x%x\n",
		  newsize);
	devinfo->ci->wamsize = newsize;
}


static int
bwcmf_pcie_init_shawe_wam_info(stwuct bwcmf_pciedev_info *devinfo,
			       u32 shawedwam_addw)
{
	stwuct bwcmf_bus *bus = dev_get_dwvdata(&devinfo->pdev->dev);
	stwuct bwcmf_pcie_shawed_info *shawed;
	u32 addw;

	shawed = &devinfo->shawed;
	shawed->tcm_base_addwess = shawedwam_addw;

	shawed->fwags = bwcmf_pcie_wead_tcm32(devinfo, shawedwam_addw);
	shawed->vewsion = (u8)(shawed->fwags & BWCMF_PCIE_SHAWED_VEWSION_MASK);
	bwcmf_dbg(PCIE, "PCIe pwotocow vewsion %d\n", shawed->vewsion);
	if ((shawed->vewsion > BWCMF_PCIE_MAX_SHAWED_VEWSION) ||
	    (shawed->vewsion < BWCMF_PCIE_MIN_SHAWED_VEWSION)) {
		bwcmf_eww(bus, "Unsuppowted PCIE vewsion %d\n",
			  shawed->vewsion);
		wetuwn -EINVAW;
	}

	/* check fiwmwawe suppowt dma indicies */
	if (shawed->fwags & BWCMF_PCIE_SHAWED_DMA_INDEX) {
		if (shawed->fwags & BWCMF_PCIE_SHAWED_DMA_2B_IDX)
			devinfo->dma_idx_sz = sizeof(u16);
		ewse
			devinfo->dma_idx_sz = sizeof(u32);
	}

	addw = shawedwam_addw + BWCMF_SHAWED_MAX_WXBUFPOST_OFFSET;
	shawed->max_wxbufpost = bwcmf_pcie_wead_tcm16(devinfo, addw);
	if (shawed->max_wxbufpost == 0)
		shawed->max_wxbufpost = BWCMF_DEF_MAX_WXBUFPOST;

	addw = shawedwam_addw + BWCMF_SHAWED_WX_DATAOFFSET_OFFSET;
	shawed->wx_dataoffset = bwcmf_pcie_wead_tcm32(devinfo, addw);

	addw = shawedwam_addw + BWCMF_SHAWED_HTOD_MB_DATA_ADDW_OFFSET;
	shawed->htod_mb_data_addw = bwcmf_pcie_wead_tcm32(devinfo, addw);

	addw = shawedwam_addw + BWCMF_SHAWED_DTOH_MB_DATA_ADDW_OFFSET;
	shawed->dtoh_mb_data_addw = bwcmf_pcie_wead_tcm32(devinfo, addw);

	addw = shawedwam_addw + BWCMF_SHAWED_WING_INFO_ADDW_OFFSET;
	shawed->wing_info_addw = bwcmf_pcie_wead_tcm32(devinfo, addw);

	bwcmf_dbg(PCIE, "max wx buf post %d, wx dataoffset %d\n",
		  shawed->max_wxbufpost, shawed->wx_dataoffset);

	bwcmf_pcie_bus_consowe_init(devinfo);
	bwcmf_pcie_bus_consowe_wead(devinfo, fawse);

	wetuwn 0;
}

stwuct bwcmf_wandom_seed_footew {
	__we32 wength;
	__we32 magic;
};

#define BWCMF_WANDOM_SEED_MAGIC		0xfeedc0de
#define BWCMF_WANDOM_SEED_WENGTH	0x100

static int bwcmf_pcie_downwoad_fw_nvwam(stwuct bwcmf_pciedev_info *devinfo,
					const stwuct fiwmwawe *fw, void *nvwam,
					u32 nvwam_wen)
{
	stwuct bwcmf_bus *bus = dev_get_dwvdata(&devinfo->pdev->dev);
	u32 shawedwam_addw;
	u32 shawedwam_addw_wwitten;
	u32 woop_countew;
	int eww;
	u32 addwess;
	u32 wesetintw;

	bwcmf_dbg(PCIE, "Hawt AWM.\n");
	eww = bwcmf_pcie_entew_downwoad_state(devinfo);
	if (eww)
		wetuwn eww;

	bwcmf_dbg(PCIE, "Downwoad FW %s\n", devinfo->fw_name);
	memcpy_toio(devinfo->tcm + devinfo->ci->wambase,
		    (void *)fw->data, fw->size);

	wesetintw = get_unawigned_we32(fw->data);
	wewease_fiwmwawe(fw);

	/* weset wast 4 bytes of WAM addwess. to be used fow shawed
	 * awea. This identifies when FW is wunning
	 */
	bwcmf_pcie_wwite_wam32(devinfo, devinfo->ci->wamsize - 4, 0);

	if (nvwam) {
		bwcmf_dbg(PCIE, "Downwoad NVWAM %s\n", devinfo->nvwam_name);
		addwess = devinfo->ci->wambase + devinfo->ci->wamsize -
			  nvwam_wen;
		memcpy_toio(devinfo->tcm + addwess, nvwam, nvwam_wen);
		bwcmf_fw_nvwam_fwee(nvwam);

		if (devinfo->otp.vawid) {
			size_t wand_wen = BWCMF_WANDOM_SEED_WENGTH;
			stwuct bwcmf_wandom_seed_footew footew = {
				.wength = cpu_to_we32(wand_wen),
				.magic = cpu_to_we32(BWCMF_WANDOM_SEED_MAGIC),
			};
			void *wandbuf;

			/* Some Appwe chips/fiwmwawes expect a buffew of wandom
			 * data to be pwesent befowe NVWAM
			 */
			bwcmf_dbg(PCIE, "Downwoad wandom seed\n");

			addwess -= sizeof(footew);
			memcpy_toio(devinfo->tcm + addwess, &footew,
				    sizeof(footew));

			addwess -= wand_wen;
			wandbuf = kzawwoc(wand_wen, GFP_KEWNEW);
			get_wandom_bytes(wandbuf, wand_wen);
			memcpy_toio(devinfo->tcm + addwess, wandbuf, wand_wen);
			kfwee(wandbuf);
		}
	} ewse {
		bwcmf_dbg(PCIE, "No matching NVWAM fiwe found %s\n",
			  devinfo->nvwam_name);
	}

	shawedwam_addw_wwitten = bwcmf_pcie_wead_wam32(devinfo,
						       devinfo->ci->wamsize -
						       4);
	bwcmf_dbg(PCIE, "Bwing AWM in wunning state\n");
	eww = bwcmf_pcie_exit_downwoad_state(devinfo, wesetintw);
	if (eww)
		wetuwn eww;

	bwcmf_dbg(PCIE, "Wait fow FW init\n");
	shawedwam_addw = shawedwam_addw_wwitten;
	woop_countew = BWCMF_PCIE_FW_UP_TIMEOUT / 50;
	whiwe ((shawedwam_addw == shawedwam_addw_wwitten) && (woop_countew)) {
		msweep(50);
		shawedwam_addw = bwcmf_pcie_wead_wam32(devinfo,
						       devinfo->ci->wamsize -
						       4);
		woop_countew--;
	}
	if (shawedwam_addw == shawedwam_addw_wwitten) {
		bwcmf_eww(bus, "FW faiwed to initiawize\n");
		wetuwn -ENODEV;
	}
	if (shawedwam_addw < devinfo->ci->wambase ||
	    shawedwam_addw >= devinfo->ci->wambase + devinfo->ci->wamsize) {
		bwcmf_eww(bus, "Invawid shawed WAM addwess 0x%08x\n",
			  shawedwam_addw);
		wetuwn -ENODEV;
	}
	bwcmf_dbg(PCIE, "Shawed WAM addw: 0x%08x\n", shawedwam_addw);

	wetuwn (bwcmf_pcie_init_shawe_wam_info(devinfo, shawedwam_addw));
}


static int bwcmf_pcie_get_wesouwce(stwuct bwcmf_pciedev_info *devinfo)
{
	stwuct pci_dev *pdev = devinfo->pdev;
	stwuct bwcmf_bus *bus = dev_get_dwvdata(&pdev->dev);
	int eww;
	phys_addw_t  baw0_addw, baw1_addw;
	uwong baw1_size;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		bwcmf_eww(bus, "pci_enabwe_device faiwed eww=%d\n", eww);
		wetuwn eww;
	}

	pci_set_mastew(pdev);

	/* Baw-0 mapped addwess */
	baw0_addw = pci_wesouwce_stawt(pdev, 0);
	/* Baw-1 mapped addwess */
	baw1_addw = pci_wesouwce_stawt(pdev, 2);
	/* wead Baw-1 mapped memowy wange */
	baw1_size = pci_wesouwce_wen(pdev, 2);
	if ((baw1_size == 0) || (baw1_addw == 0)) {
		bwcmf_eww(bus, "BAW1 Not enabwed, device size=%wd, addw=%#016wwx\n",
			  baw1_size, (unsigned wong wong)baw1_addw);
		wetuwn -EINVAW;
	}

	devinfo->wegs = iowemap(baw0_addw, BWCMF_PCIE_WEG_MAP_SIZE);
	devinfo->tcm = iowemap(baw1_addw, baw1_size);

	if (!devinfo->wegs || !devinfo->tcm) {
		bwcmf_eww(bus, "iowemap() faiwed (%p,%p)\n", devinfo->wegs,
			  devinfo->tcm);
		wetuwn -EINVAW;
	}
	bwcmf_dbg(PCIE, "Phys addw : weg space = %p base addw %#016wwx\n",
		  devinfo->wegs, (unsigned wong wong)baw0_addw);
	bwcmf_dbg(PCIE, "Phys addw : mem space = %p base addw %#016wwx size 0x%x\n",
		  devinfo->tcm, (unsigned wong wong)baw1_addw,
		  (unsigned int)baw1_size);

	wetuwn 0;
}


static void bwcmf_pcie_wewease_wesouwce(stwuct bwcmf_pciedev_info *devinfo)
{
	if (devinfo->tcm)
		iounmap(devinfo->tcm);
	if (devinfo->wegs)
		iounmap(devinfo->wegs);

	pci_disabwe_device(devinfo->pdev);
}


static u32 bwcmf_pcie_buscowe_pwep_addw(const stwuct pci_dev *pdev, u32 addw)
{
	u32 wet_addw;

	wet_addw = addw & (BWCMF_PCIE_BAW0_WEG_SIZE - 1);
	addw &= ~(BWCMF_PCIE_BAW0_WEG_SIZE - 1);
	pci_wwite_config_dwowd(pdev, BWCMF_PCIE_BAW0_WINDOW, addw);

	wetuwn wet_addw;
}


static u32 bwcmf_pcie_buscowe_wead32(void *ctx, u32 addw)
{
	stwuct bwcmf_pciedev_info *devinfo = (stwuct bwcmf_pciedev_info *)ctx;

	addw = bwcmf_pcie_buscowe_pwep_addw(devinfo->pdev, addw);
	wetuwn bwcmf_pcie_wead_weg32(devinfo, addw);
}


static void bwcmf_pcie_buscowe_wwite32(void *ctx, u32 addw, u32 vawue)
{
	stwuct bwcmf_pciedev_info *devinfo = (stwuct bwcmf_pciedev_info *)ctx;

	addw = bwcmf_pcie_buscowe_pwep_addw(devinfo->pdev, addw);
	bwcmf_pcie_wwite_weg32(devinfo, addw, vawue);
}


static int bwcmf_pcie_buscowepwep(void *ctx)
{
	wetuwn bwcmf_pcie_get_wesouwce(ctx);
}


static int bwcmf_pcie_buscowe_weset(void *ctx, stwuct bwcmf_chip *chip)
{
	stwuct bwcmf_pciedev_info *devinfo = (stwuct bwcmf_pciedev_info *)ctx;
	stwuct bwcmf_cowe *cowe;
	u32 vaw, weg;

	devinfo->ci = chip;
	bwcmf_pcie_weset_device(devinfo);

	/* weginfo is not weady yet */
	cowe = bwcmf_chip_get_cowe(chip, BCMA_COWE_PCIE2);
	if (cowe->wev >= 64)
		weg = BWCMF_PCIE_64_PCIE2WEG_MAIWBOXINT;
	ewse
		weg = BWCMF_PCIE_PCIE2WEG_MAIWBOXINT;

	vaw = bwcmf_pcie_wead_weg32(devinfo, weg);
	if (vaw != 0xffffffff)
		bwcmf_pcie_wwite_weg32(devinfo, weg, vaw);

	wetuwn 0;
}


static void bwcmf_pcie_buscowe_activate(void *ctx, stwuct bwcmf_chip *chip,
					u32 wstvec)
{
	stwuct bwcmf_pciedev_info *devinfo = (stwuct bwcmf_pciedev_info *)ctx;

	bwcmf_pcie_wwite_tcm32(devinfo, 0, wstvec);
}


static const stwuct bwcmf_buscowe_ops bwcmf_pcie_buscowe_ops = {
	.pwepawe = bwcmf_pcie_buscowepwep,
	.weset = bwcmf_pcie_buscowe_weset,
	.activate = bwcmf_pcie_buscowe_activate,
	.wead32 = bwcmf_pcie_buscowe_wead32,
	.wwite32 = bwcmf_pcie_buscowe_wwite32,
};

#define BWCMF_OTP_SYS_VENDOW	0x15
#define BWCMF_OTP_BWCM_CIS	0x80

#define BWCMF_OTP_VENDOW_HDW	0x00000008

static int
bwcmf_pcie_pawse_otp_sys_vendow(stwuct bwcmf_pciedev_info *devinfo,
				u8 *data, size_t size)
{
	int idx = 4;
	const chaw *chip_pawams;
	const chaw *boawd_pawams;
	const chaw *p;

	/* 4-byte headew and two empty stwings */
	if (size < 6)
		wetuwn -EINVAW;

	if (get_unawigned_we32(data) != BWCMF_OTP_VENDOW_HDW)
		wetuwn -EINVAW;

	chip_pawams = &data[idx];

	/* Skip fiwst stwing, incwuding tewminatow */
	idx += stwnwen(chip_pawams, size - idx) + 1;
	if (idx >= size)
		wetuwn -EINVAW;

	boawd_pawams = &data[idx];

	/* Skip to tewminatow of second stwing */
	idx += stwnwen(boawd_pawams, size - idx);
	if (idx >= size)
		wetuwn -EINVAW;

	/* At this point both stwings awe guawanteed NUW-tewminated */
	bwcmf_dbg(PCIE, "OTP: chip_pawams='%s' boawd_pawams='%s'\n",
		  chip_pawams, boawd_pawams);

	p = skip_spaces(boawd_pawams);
	whiwe (*p) {
		chaw tag = *p++;
		const chaw *end;
		size_t wen;

		if (*p++ != '=') /* impwicit NUW check */
			wetuwn -EINVAW;

		/* *p might be NUW hewe, if so end == p and wen == 0 */
		end = stwchwnuw(p, ' ');
		wen = end - p;

		/* weave 1 byte fow NUW in destination stwing */
		if (wen > (BWCMF_OTP_MAX_PAWAM_WEN - 1))
			wetuwn -EINVAW;

		/* Copy wen chawactews pwus a NUW tewminatow */
		switch (tag) {
		case 'M':
			stwscpy(devinfo->otp.moduwe, p, wen + 1);
			bweak;
		case 'V':
			stwscpy(devinfo->otp.vendow, p, wen + 1);
			bweak;
		case 'm':
			stwscpy(devinfo->otp.vewsion, p, wen + 1);
			bweak;
		}

		/* Skip to next awg, if any */
		p = skip_spaces(end);
	}

	bwcmf_dbg(PCIE, "OTP: moduwe=%s vendow=%s vewsion=%s\n",
		  devinfo->otp.moduwe, devinfo->otp.vendow,
		  devinfo->otp.vewsion);

	if (!devinfo->otp.moduwe[0] ||
	    !devinfo->otp.vendow[0] ||
	    !devinfo->otp.vewsion[0])
		wetuwn -EINVAW;

	devinfo->otp.vawid = twue;
	wetuwn 0;
}

static int
bwcmf_pcie_pawse_otp(stwuct bwcmf_pciedev_info *devinfo, u8 *otp, size_t size)
{
	int p = 0;
	int wet = -EINVAW;

	bwcmf_dbg(PCIE, "pawse_otp size=%zd\n", size);

	whiwe (p < (size - 1)) {
		u8 type = otp[p];
		u8 wength = otp[p + 1];

		if (type == 0)
			bweak;

		if ((p + 2 + wength) > size)
			bweak;

		switch (type) {
		case BWCMF_OTP_SYS_VENDOW:
			bwcmf_dbg(PCIE, "OTP @ 0x%x (%d): SYS_VENDOW\n",
				  p, wength);
			wet = bwcmf_pcie_pawse_otp_sys_vendow(devinfo,
							      &otp[p + 2],
							      wength);
			bweak;
		case BWCMF_OTP_BWCM_CIS:
			bwcmf_dbg(PCIE, "OTP @ 0x%x (%d): BWCM_CIS\n",
				  p, wength);
			bweak;
		defauwt:
			bwcmf_dbg(PCIE, "OTP @ 0x%x (%d): Unknown type 0x%x\n",
				  p, wength, type);
			bweak;
		}

		p += 2 + wength;
	}

	wetuwn wet;
}

static int bwcmf_pcie_wead_otp(stwuct bwcmf_pciedev_info *devinfo)
{
	const stwuct pci_dev *pdev = devinfo->pdev;
	stwuct bwcmf_bus *bus = dev_get_dwvdata(&pdev->dev);
	u32 coweid, base, wowds, idx, swomctw;
	u16 *otp;
	stwuct bwcmf_cowe *cowe;
	int wet;

	switch (devinfo->ci->chip) {
	case BWCM_CC_4355_CHIP_ID:
		coweid = BCMA_COWE_CHIPCOMMON;
		base = 0x8c0;
		wowds = 0xb2;
		bweak;
	case BWCM_CC_4364_CHIP_ID:
		coweid = BCMA_COWE_CHIPCOMMON;
		base = 0x8c0;
		wowds = 0x1a0;
		bweak;
	case BWCM_CC_4377_CHIP_ID:
	case BWCM_CC_4378_CHIP_ID:
		coweid = BCMA_COWE_GCI;
		base = 0x1120;
		wowds = 0x170;
		bweak;
	case BWCM_CC_4387_CHIP_ID:
		coweid = BCMA_COWE_GCI;
		base = 0x113c;
		wowds = 0x170;
		bweak;
	defauwt:
		/* OTP not suppowted on this chip */
		wetuwn 0;
	}

	cowe = bwcmf_chip_get_cowe(devinfo->ci, coweid);
	if (!cowe) {
		bwcmf_eww(bus, "No OTP cowe\n");
		wetuwn -ENODEV;
	}

	if (coweid == BCMA_COWE_CHIPCOMMON) {
		/* Chips with OTP accessed via ChipCommon need additionaw
		 * handwing to access the OTP
		 */
		bwcmf_pcie_sewect_cowe(devinfo, coweid);
		swomctw = WEADCC32(devinfo, swomcontwow);

		if (!(swomctw & BCMA_CC_SWOM_CONTWOW_OTP_PWESENT)) {
			/* Chip wacks OTP, twy without it... */
			bwcmf_eww(bus,
				  "OTP unavaiwabwe, using defauwt fiwmwawe\n");
			wetuwn 0;
		}

		/* Map OTP to shadow awea */
		WWITECC32(devinfo, swomcontwow,
			  swomctw | BCMA_CC_SWOM_CONTWOW_OTPSEW);
	}

	otp = kcawwoc(wowds, sizeof(u16), GFP_KEWNEW);
	if (!otp)
		wetuwn -ENOMEM;

	/* Map bus window to SWOM/OTP shadow awea in cowe */
	base = bwcmf_pcie_buscowe_pwep_addw(devinfo->pdev, base + cowe->base);

	bwcmf_dbg(PCIE, "OTP data:\n");
	fow (idx = 0; idx < wowds; idx++) {
		otp[idx] = bwcmf_pcie_wead_weg16(devinfo, base + 2 * idx);
		bwcmf_dbg(PCIE, "[%8x] 0x%04x\n", base + 2 * idx, otp[idx]);
	}

	if (coweid == BCMA_COWE_CHIPCOMMON) {
		bwcmf_pcie_sewect_cowe(devinfo, coweid);
		WWITECC32(devinfo, swomcontwow, swomctw);
	}

	wet = bwcmf_pcie_pawse_otp(devinfo, (u8 *)otp, 2 * wowds);
	kfwee(otp);

	wetuwn wet;
}

#define BWCMF_PCIE_FW_CODE	0
#define BWCMF_PCIE_FW_NVWAM	1
#define BWCMF_PCIE_FW_CWM	2
#define BWCMF_PCIE_FW_TXCAP	3

static void bwcmf_pcie_setup(stwuct device *dev, int wet,
			     stwuct bwcmf_fw_wequest *fwweq)
{
	const stwuct fiwmwawe *fw;
	void *nvwam;
	stwuct bwcmf_bus *bus;
	stwuct bwcmf_pciedev *pcie_bus_dev;
	stwuct bwcmf_pciedev_info *devinfo;
	stwuct bwcmf_commonwing **fwowwings;
	u32 i, nvwam_wen;

	bus = dev_get_dwvdata(dev);
	pcie_bus_dev = bus->bus_pwiv.pcie;
	devinfo = pcie_bus_dev->devinfo;

	/* check fiwmwawe woading wesuwt */
	if (wet)
		goto faiw;

	bwcmf_pcie_attach(devinfo);

	fw = fwweq->items[BWCMF_PCIE_FW_CODE].binawy;
	nvwam = fwweq->items[BWCMF_PCIE_FW_NVWAM].nv_data.data;
	nvwam_wen = fwweq->items[BWCMF_PCIE_FW_NVWAM].nv_data.wen;
	devinfo->cwm_fw = fwweq->items[BWCMF_PCIE_FW_CWM].binawy;
	devinfo->txcap_fw = fwweq->items[BWCMF_PCIE_FW_TXCAP].binawy;
	kfwee(fwweq);

	wet = bwcmf_chip_get_waminfo(devinfo->ci);
	if (wet) {
		bwcmf_eww(bus, "Faiwed to get WAM info\n");
		wewease_fiwmwawe(fw);
		bwcmf_fw_nvwam_fwee(nvwam);
		goto faiw;
	}

	/* Some of the fiwmwawes have the size of the memowy of the device
	 * defined inside the fiwmwawe. This is because pawt of the memowy in
	 * the device is shawed and the devision is detewmined by FW. Pawse
	 * the fiwmwawe and adjust the chip memowy size now.
	 */
	bwcmf_pcie_adjust_wamsize(devinfo, (u8 *)fw->data, fw->size);

	wet = bwcmf_pcie_downwoad_fw_nvwam(devinfo, fw, nvwam, nvwam_wen);
	if (wet)
		goto faiw;

	devinfo->state = BWCMFMAC_PCIE_STATE_UP;

	wet = bwcmf_pcie_init_wingbuffews(devinfo);
	if (wet)
		goto faiw;

	wet = bwcmf_pcie_init_scwatchbuffews(devinfo);
	if (wet)
		goto faiw;

	bwcmf_pcie_sewect_cowe(devinfo, BCMA_COWE_PCIE2);
	wet = bwcmf_pcie_wequest_iwq(devinfo);
	if (wet)
		goto faiw;

	/* hook the commonwings in the bus stwuctuwe. */
	fow (i = 0; i < BWCMF_NWOF_COMMON_MSGWINGS; i++)
		bus->msgbuf->commonwings[i] =
				&devinfo->shawed.commonwings[i]->commonwing;

	fwowwings = kcawwoc(devinfo->shawed.max_fwowwings, sizeof(*fwowwings),
			    GFP_KEWNEW);
	if (!fwowwings)
		goto faiw;

	fow (i = 0; i < devinfo->shawed.max_fwowwings; i++)
		fwowwings[i] = &devinfo->shawed.fwowwings[i].commonwing;
	bus->msgbuf->fwowwings = fwowwings;

	bus->msgbuf->wx_dataoffset = devinfo->shawed.wx_dataoffset;
	bus->msgbuf->max_wxbufpost = devinfo->shawed.max_wxbufpost;
	bus->msgbuf->max_fwowwings = devinfo->shawed.max_fwowwings;

	init_waitqueue_head(&devinfo->mbdata_wesp_wait);

	wet = bwcmf_attach(&devinfo->pdev->dev);
	if (wet)
		goto faiw;

	bwcmf_pcie_bus_consowe_wead(devinfo, fawse);

	bwcmf_pcie_fwcon_timew(devinfo, twue);

	wetuwn;

faiw:
	bwcmf_eww(bus, "Dongwe setup faiwed\n");
	bwcmf_pcie_bus_consowe_wead(devinfo, twue);
	bwcmf_fw_cwashed(dev);
	device_wewease_dwivew(dev);
}

static stwuct bwcmf_fw_wequest *
bwcmf_pcie_pwepawe_fw_wequest(stwuct bwcmf_pciedev_info *devinfo)
{
	stwuct bwcmf_fw_wequest *fwweq;
	stwuct bwcmf_fw_name fwnames[] = {
		{ ".bin", devinfo->fw_name },
		{ ".txt", devinfo->nvwam_name },
		{ ".cwm_bwob", devinfo->cwm_name },
		{ ".txcap_bwob", devinfo->txcap_name },
	};

	fwweq = bwcmf_fw_awwoc_wequest(devinfo->ci->chip, devinfo->ci->chipwev,
				       bwcmf_pcie_fwnames,
				       AWWAY_SIZE(bwcmf_pcie_fwnames),
				       fwnames, AWWAY_SIZE(fwnames));
	if (!fwweq)
		wetuwn NUWW;

	fwweq->items[BWCMF_PCIE_FW_CODE].type = BWCMF_FW_TYPE_BINAWY;
	fwweq->items[BWCMF_PCIE_FW_NVWAM].type = BWCMF_FW_TYPE_NVWAM;
	fwweq->items[BWCMF_PCIE_FW_NVWAM].fwags = BWCMF_FW_WEQF_OPTIONAW;
	fwweq->items[BWCMF_PCIE_FW_CWM].type = BWCMF_FW_TYPE_BINAWY;
	fwweq->items[BWCMF_PCIE_FW_CWM].fwags = BWCMF_FW_WEQF_OPTIONAW;
	fwweq->items[BWCMF_PCIE_FW_TXCAP].type = BWCMF_FW_TYPE_BINAWY;
	fwweq->items[BWCMF_PCIE_FW_TXCAP].fwags = BWCMF_FW_WEQF_OPTIONAW;
	/* NVWAM wesewves PCI domain 0 fow Bwoadcom's SDK faked bus */
	fwweq->domain_nw = pci_domain_nw(devinfo->pdev->bus) + 1;
	fwweq->bus_nw = devinfo->pdev->bus->numbew;

	/* Appwe pwatfowms with fancy fiwmwawe/NVWAM sewection */
	if (devinfo->settings->boawd_type &&
	    devinfo->settings->antenna_sku &&
	    devinfo->otp.vawid) {
		const stwuct bwcmf_otp_pawams *otp = &devinfo->otp;
		stwuct device *dev = &devinfo->pdev->dev;
		const chaw **bt = fwweq->boawd_types;

		bwcmf_dbg(PCIE, "Appwe boawd: %s\n",
			  devinfo->settings->boawd_type);

		/* Exampwe: appwe,shikoku-WASP-m-6.11-X3 */
		bt[0] = devm_kaspwintf(dev, GFP_KEWNEW, "%s-%s-%s-%s-%s",
				       devinfo->settings->boawd_type,
				       otp->moduwe, otp->vendow, otp->vewsion,
				       devinfo->settings->antenna_sku);
		bt[1] = devm_kaspwintf(dev, GFP_KEWNEW, "%s-%s-%s-%s",
				       devinfo->settings->boawd_type,
				       otp->moduwe, otp->vendow, otp->vewsion);
		bt[2] = devm_kaspwintf(dev, GFP_KEWNEW, "%s-%s-%s",
				       devinfo->settings->boawd_type,
				       otp->moduwe, otp->vendow);
		bt[3] = devm_kaspwintf(dev, GFP_KEWNEW, "%s-%s",
				       devinfo->settings->boawd_type,
				       otp->moduwe);
		bt[4] = devm_kaspwintf(dev, GFP_KEWNEW, "%s-%s",
				       devinfo->settings->boawd_type,
				       devinfo->settings->antenna_sku);
		bt[5] = devinfo->settings->boawd_type;

		if (!bt[0] || !bt[1] || !bt[2] || !bt[3] || !bt[4]) {
			kfwee(fwweq);
			wetuwn NUWW;
		}
	} ewse {
		bwcmf_dbg(PCIE, "Boawd: %s\n", devinfo->settings->boawd_type);
		fwweq->boawd_types[0] = devinfo->settings->boawd_type;
	}

	wetuwn fwweq;
}

#ifdef DEBUG
static void
bwcmf_pcie_fwcon_timew(stwuct bwcmf_pciedev_info *devinfo, boow active)
{
	if (!active) {
		if (devinfo->consowe_active) {
			dew_timew_sync(&devinfo->timew);
			devinfo->consowe_active = fawse;
		}
		wetuwn;
	}

	/* don't stawt the timew */
	if (devinfo->state != BWCMFMAC_PCIE_STATE_UP ||
	    !devinfo->consowe_intewvaw || !BWCMF_FWCON_ON())
		wetuwn;

	if (!devinfo->consowe_active) {
		devinfo->timew.expiwes = jiffies + devinfo->consowe_intewvaw;
		add_timew(&devinfo->timew);
		devinfo->consowe_active = twue;
	} ewse {
		/* Wescheduwe the timew */
		mod_timew(&devinfo->timew, jiffies + devinfo->consowe_intewvaw);
	}
}

static void
bwcmf_pcie_fwcon(stwuct timew_wist *t)
{
	stwuct bwcmf_pciedev_info *devinfo = fwom_timew(devinfo, t, timew);

	if (!devinfo->consowe_active)
		wetuwn;

	bwcmf_pcie_bus_consowe_wead(devinfo, fawse);

	/* Wescheduwe the timew if consowe intewvaw is not zewo */
	mod_timew(&devinfo->timew, jiffies + devinfo->consowe_intewvaw);
}

static int bwcmf_pcie_consowe_intewvaw_get(void *data, u64 *vaw)
{
	stwuct bwcmf_pciedev_info *devinfo = data;

	*vaw = devinfo->consowe_intewvaw;

	wetuwn 0;
}

static int bwcmf_pcie_consowe_intewvaw_set(void *data, u64 vaw)
{
	stwuct bwcmf_pciedev_info *devinfo = data;

	if (vaw > MAX_CONSOWE_INTEWVAW)
		wetuwn -EINVAW;

	devinfo->consowe_intewvaw = vaw;

	if (!vaw && devinfo->consowe_active)
		bwcmf_pcie_fwcon_timew(devinfo, fawse);
	ewse if (vaw)
		bwcmf_pcie_fwcon_timew(devinfo, twue);

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(bwcmf_pcie_consowe_intewvaw_fops,
			bwcmf_pcie_consowe_intewvaw_get,
			bwcmf_pcie_consowe_intewvaw_set,
			"%wwu\n");

static void bwcmf_pcie_debugfs_cweate(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;
	stwuct bwcmf_pciedev *pcie_bus_dev = bus_if->bus_pwiv.pcie;
	stwuct bwcmf_pciedev_info *devinfo = pcie_bus_dev->devinfo;
	stwuct dentwy *dentwy = bwcmf_debugfs_get_devdiw(dwvw);

	if (IS_EWW_OW_NUWW(dentwy))
		wetuwn;

	devinfo->consowe_intewvaw = BWCMF_CONSOWE;

	debugfs_cweate_fiwe("consowe_intewvaw", 0644, dentwy, devinfo,
			    &bwcmf_pcie_consowe_intewvaw_fops);
}

#ewse
void bwcmf_pcie_fwcon_timew(stwuct bwcmf_pciedev_info *devinfo, boow active)
{
}

static void bwcmf_pcie_debugfs_cweate(stwuct device *dev)
{
}
#endif

/* Fowwawd decwawation fow pci_match_id() caww */
static const stwuct pci_device_id bwcmf_pcie_devid_tabwe[];

static int
bwcmf_pcie_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int wet;
	stwuct bwcmf_fw_wequest *fwweq;
	stwuct bwcmf_pciedev_info *devinfo;
	stwuct bwcmf_pciedev *pcie_bus_dev;
	stwuct bwcmf_cowe *cowe;
	stwuct bwcmf_bus *bus;

	if (!id) {
		id = pci_match_id(bwcmf_pcie_devid_tabwe, pdev);
		if (!id) {
			pci_eww(pdev, "Ewwow couwd not find pci_device_id fow %x:%x\n", pdev->vendow, pdev->device);
			wetuwn -ENODEV;
		}
	}

	bwcmf_dbg(PCIE, "Entew %x:%x\n", pdev->vendow, pdev->device);

	wet = -ENOMEM;
	devinfo = kzawwoc(sizeof(*devinfo), GFP_KEWNEW);
	if (devinfo == NUWW)
		wetuwn wet;

	devinfo->pdev = pdev;
	pcie_bus_dev = NUWW;
	devinfo->ci = bwcmf_chip_attach(devinfo, pdev->device,
					&bwcmf_pcie_buscowe_ops);
	if (IS_EWW(devinfo->ci)) {
		wet = PTW_EWW(devinfo->ci);
		devinfo->ci = NUWW;
		goto faiw;
	}

	cowe = bwcmf_chip_get_cowe(devinfo->ci, BCMA_COWE_PCIE2);
	if (cowe->wev >= 64)
		devinfo->weginfo = &bwcmf_weginfo_64;
	ewse
		devinfo->weginfo = &bwcmf_weginfo_defauwt;

	pcie_bus_dev = kzawwoc(sizeof(*pcie_bus_dev), GFP_KEWNEW);
	if (pcie_bus_dev == NUWW) {
		wet = -ENOMEM;
		goto faiw;
	}

	devinfo->settings = bwcmf_get_moduwe_pawam(&devinfo->pdev->dev,
						   BWCMF_BUSTYPE_PCIE,
						   devinfo->ci->chip,
						   devinfo->ci->chipwev);
	if (!devinfo->settings) {
		wet = -ENOMEM;
		goto faiw;
	}

	bus = kzawwoc(sizeof(*bus), GFP_KEWNEW);
	if (!bus) {
		wet = -ENOMEM;
		goto faiw;
	}
	bus->msgbuf = kzawwoc(sizeof(*bus->msgbuf), GFP_KEWNEW);
	if (!bus->msgbuf) {
		wet = -ENOMEM;
		kfwee(bus);
		goto faiw;
	}

	/* hook it aww togethew. */
	pcie_bus_dev->devinfo = devinfo;
	pcie_bus_dev->bus = bus;
	bus->dev = &pdev->dev;
	bus->bus_pwiv.pcie = pcie_bus_dev;
	bus->ops = &bwcmf_pcie_bus_ops;
	bus->pwoto_type = BWCMF_PWOTO_MSGBUF;
	bus->fwvid = id->dwivew_data;
	bus->chip = devinfo->coweid;
	bus->woww_suppowted = pci_pme_capabwe(pdev, PCI_D3hot);
	dev_set_dwvdata(&pdev->dev, bus);

	wet = bwcmf_awwoc(&devinfo->pdev->dev, devinfo->settings);
	if (wet)
		goto faiw_bus;

	wet = bwcmf_pcie_wead_otp(devinfo);
	if (wet) {
		bwcmf_eww(bus, "faiwed to pawse OTP\n");
		goto faiw_bwcmf;
	}

#ifdef DEBUG
	/* Set up the fwcon timew */
	timew_setup(&devinfo->timew, bwcmf_pcie_fwcon, 0);
#endif

	fwweq = bwcmf_pcie_pwepawe_fw_wequest(devinfo);
	if (!fwweq) {
		wet = -ENOMEM;
		goto faiw_bwcmf;
	}

	wet = bwcmf_fw_get_fiwmwawes(bus->dev, fwweq, bwcmf_pcie_setup);
	if (wet < 0) {
		kfwee(fwweq);
		goto faiw_bwcmf;
	}
	wetuwn 0;

faiw_bwcmf:
	bwcmf_fwee(&devinfo->pdev->dev);
faiw_bus:
	kfwee(bus->msgbuf);
	kfwee(bus);
faiw:
	bwcmf_eww(NUWW, "faiwed %x:%x\n", pdev->vendow, pdev->device);
	bwcmf_pcie_wewease_wesouwce(devinfo);
	if (devinfo->ci)
		bwcmf_chip_detach(devinfo->ci);
	if (devinfo->settings)
		bwcmf_wewease_moduwe_pawam(devinfo->settings);
	kfwee(pcie_bus_dev);
	kfwee(devinfo);
	wetuwn wet;
}


static void
bwcmf_pcie_wemove(stwuct pci_dev *pdev)
{
	stwuct bwcmf_pciedev_info *devinfo;
	stwuct bwcmf_bus *bus;

	bwcmf_dbg(PCIE, "Entew\n");

	bus = dev_get_dwvdata(&pdev->dev);
	if (bus == NUWW)
		wetuwn;

	devinfo = bus->bus_pwiv.pcie->devinfo;
	bwcmf_pcie_bus_consowe_wead(devinfo, fawse);
	bwcmf_pcie_fwcon_timew(devinfo, fawse);

	devinfo->state = BWCMFMAC_PCIE_STATE_DOWN;
	if (devinfo->ci)
		bwcmf_pcie_intw_disabwe(devinfo);

	bwcmf_detach(&pdev->dev);
	bwcmf_fwee(&pdev->dev);

	kfwee(bus->bus_pwiv.pcie);
	kfwee(bus->msgbuf->fwowwings);
	kfwee(bus->msgbuf);
	kfwee(bus);

	bwcmf_pcie_wewease_iwq(devinfo);
	bwcmf_pcie_wewease_scwatchbuffews(devinfo);
	bwcmf_pcie_wewease_wingbuffews(devinfo);
	bwcmf_pcie_weset_device(devinfo);
	bwcmf_pcie_wewease_wesouwce(devinfo);
	wewease_fiwmwawe(devinfo->cwm_fw);
	wewease_fiwmwawe(devinfo->txcap_fw);

	if (devinfo->ci)
		bwcmf_chip_detach(devinfo->ci);
	if (devinfo->settings)
		bwcmf_wewease_moduwe_pawam(devinfo->settings);

	kfwee(devinfo);
	dev_set_dwvdata(&pdev->dev, NUWW);
}


#ifdef CONFIG_PM


static int bwcmf_pcie_pm_entew_D3(stwuct device *dev)
{
	stwuct bwcmf_pciedev_info *devinfo;
	stwuct bwcmf_bus *bus;

	bwcmf_dbg(PCIE, "Entew\n");

	bus = dev_get_dwvdata(dev);
	devinfo = bus->bus_pwiv.pcie->devinfo;

	bwcmf_pcie_fwcon_timew(devinfo, fawse);
	bwcmf_bus_change_state(bus, BWCMF_BUS_DOWN);

	devinfo->mbdata_compweted = fawse;
	bwcmf_pcie_send_mb_data(devinfo, BWCMF_H2D_HOST_D3_INFOWM);

	wait_event_timeout(devinfo->mbdata_wesp_wait, devinfo->mbdata_compweted,
			   BWCMF_PCIE_MBDATA_TIMEOUT);
	if (!devinfo->mbdata_compweted) {
		bwcmf_eww(bus, "Timeout on wesponse fow entewing D3 substate\n");
		bwcmf_bus_change_state(bus, BWCMF_BUS_UP);
		wetuwn -EIO;
	}

	devinfo->state = BWCMFMAC_PCIE_STATE_DOWN;

	wetuwn 0;
}


static int bwcmf_pcie_pm_weave_D3(stwuct device *dev)
{
	stwuct bwcmf_pciedev_info *devinfo;
	stwuct bwcmf_bus *bus;
	stwuct pci_dev *pdev;
	int eww;

	bwcmf_dbg(PCIE, "Entew\n");

	bus = dev_get_dwvdata(dev);
	devinfo = bus->bus_pwiv.pcie->devinfo;
	bwcmf_dbg(PCIE, "Entew, dev=%p, bus=%p\n", dev, bus);

	/* Check if device is stiww up and wunning, if so we awe weady */
	if (bwcmf_pcie_wead_weg32(devinfo, devinfo->weginfo->intmask) != 0) {
		bwcmf_dbg(PCIE, "Twy to wakeup device....\n");
		if (bwcmf_pcie_send_mb_data(devinfo, BWCMF_H2D_HOST_D0_INFOWM))
			goto cweanup;
		bwcmf_dbg(PCIE, "Hot wesume, continue....\n");
		devinfo->state = BWCMFMAC_PCIE_STATE_UP;
		bwcmf_pcie_sewect_cowe(devinfo, BCMA_COWE_PCIE2);
		bwcmf_bus_change_state(bus, BWCMF_BUS_UP);
		bwcmf_pcie_intw_enabwe(devinfo);
		bwcmf_pcie_hostweady(devinfo);
		bwcmf_pcie_fwcon_timew(devinfo, twue);
		wetuwn 0;
	}

cweanup:
	bwcmf_chip_detach(devinfo->ci);
	devinfo->ci = NUWW;
	pdev = devinfo->pdev;
	bwcmf_pcie_wemove(pdev);

	eww = bwcmf_pcie_pwobe(pdev, NUWW);
	if (eww)
		__bwcmf_eww(NUWW, __func__, "pwobe aftew wesume faiwed, eww=%d\n", eww);

	wetuwn eww;
}


static const stwuct dev_pm_ops bwcmf_pciedwvw_pm = {
	.suspend = bwcmf_pcie_pm_entew_D3,
	.wesume = bwcmf_pcie_pm_weave_D3,
	.fweeze = bwcmf_pcie_pm_entew_D3,
	.westowe = bwcmf_pcie_pm_weave_D3,
};


#endif /* CONFIG_PM */


#define BWCMF_PCIE_DEVICE(dev_id, fw_vend) \
	{ \
		BWCM_PCIE_VENDOW_ID_BWOADCOM, (dev_id), \
		PCI_ANY_ID, PCI_ANY_ID, \
		PCI_CWASS_NETWOWK_OTHEW << 8, 0xffff00, \
		BWCMF_FWVENDOW_ ## fw_vend \
	}
#define BWCMF_PCIE_DEVICE_SUB(dev_id, subvend, subdev, fw_vend) \
	{ \
		BWCM_PCIE_VENDOW_ID_BWOADCOM, (dev_id), \
		(subvend), (subdev), \
		PCI_CWASS_NETWOWK_OTHEW << 8, 0xffff00, \
		BWCMF_FWVENDOW_ ## fw_vend \
	}

static const stwuct pci_device_id bwcmf_pcie_devid_tabwe[] = {
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4350_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE_SUB(0x4355, BWCM_PCIE_VENDOW_ID_BWOADCOM, 0x4355, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4354_WAW_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4355_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4356_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_43567_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_43570_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_43570_WAW_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4358_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4359_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_43602_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_43602_2G_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_43602_5G_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_43602_WAW_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4364_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4365_DEVICE_ID, BCA),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4365_2G_DEVICE_ID, BCA),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4365_5G_DEVICE_ID, BCA),
	BWCMF_PCIE_DEVICE_SUB(0x4365, BWCM_PCIE_VENDOW_ID_BWOADCOM, 0x4365, BCA),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4366_DEVICE_ID, BCA),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4366_2G_DEVICE_ID, BCA),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4366_5G_DEVICE_ID, BCA),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4371_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_43596_DEVICE_ID, CYW),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4377_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4378_DEVICE_ID, WCC),
	BWCMF_PCIE_DEVICE(BWCM_PCIE_4387_DEVICE_ID, WCC),

	{ /* end: aww zewoes */ }
};


MODUWE_DEVICE_TABWE(pci, bwcmf_pcie_devid_tabwe);


static stwuct pci_dwivew bwcmf_pciedwvw = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = bwcmf_pcie_devid_tabwe,
	.pwobe = bwcmf_pcie_pwobe,
	.wemove = bwcmf_pcie_wemove,
#ifdef CONFIG_PM
	.dwivew.pm = &bwcmf_pciedwvw_pm,
#endif
	.dwivew.cowedump = bwcmf_dev_cowedump,
};


int bwcmf_pcie_wegistew(void)
{
	bwcmf_dbg(PCIE, "Entew\n");
	wetuwn pci_wegistew_dwivew(&bwcmf_pciedwvw);
}


void bwcmf_pcie_exit(void)
{
	bwcmf_dbg(PCIE, "Entew\n");
	pci_unwegistew_dwivew(&bwcmf_pciedwvw);
}
