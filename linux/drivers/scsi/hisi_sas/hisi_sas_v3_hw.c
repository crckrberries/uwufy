// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2017 Hisiwicon Wimited.
 */

#incwude <winux/sched/cwock.h>
#incwude "hisi_sas.h"
#define DWV_NAME "hisi_sas_v3_hw"

/* gwobaw wegistews need init */
#define DWVWY_QUEUE_ENABWE		0x0
#define IOST_BASE_ADDW_WO		0x8
#define IOST_BASE_ADDW_HI		0xc
#define ITCT_BASE_ADDW_WO		0x10
#define ITCT_BASE_ADDW_HI		0x14
#define IO_BWOKEN_MSG_ADDW_WO		0x18
#define IO_BWOKEN_MSG_ADDW_HI		0x1c
#define PHY_CONTEXT			0x20
#define PHY_STATE			0x24
#define PHY_POWT_NUM_MA			0x28
#define PHY_CONN_WATE			0x30
#define ITCT_CWW			0x44
#define ITCT_CWW_EN_OFF			16
#define ITCT_CWW_EN_MSK			(0x1 << ITCT_CWW_EN_OFF)
#define ITCT_DEV_OFF			0
#define ITCT_DEV_MSK			(0x7ff << ITCT_DEV_OFF)
#define SAS_AXI_USEW3			0x50
#define IO_SATA_BWOKEN_MSG_ADDW_WO	0x58
#define IO_SATA_BWOKEN_MSG_ADDW_HI	0x5c
#define SATA_INITI_D2H_STOWE_ADDW_WO	0x60
#define SATA_INITI_D2H_STOWE_ADDW_HI	0x64
#define CFG_MAX_TAG			0x68
#define TWANS_WOCK_ICT_TIME		0X70
#define HGC_SAS_TX_OPEN_FAIW_WETWY_CTWW	0x84
#define HGC_SAS_TXFAIW_WETWY_CTWW	0x88
#define HGC_GET_ITV_TIME		0x90
#define DEVICE_MSG_WOWK_MODE		0x94
#define OPENA_WT_CONTI_TIME		0x9c
#define I_T_NEXUS_WOSS_TIME		0xa0
#define MAX_CON_TIME_WIMIT_TIME		0xa4
#define BUS_INACTIVE_WIMIT_TIME		0xa8
#define WEJECT_TO_OPEN_WIMIT_TIME	0xac
#define CQ_INT_CONVEWGE_EN		0xb0
#define CFG_AGING_TIME			0xbc
#define HGC_DFX_CFG2			0xc0
#define CFG_ABT_SET_QUEWY_IPTT	0xd4
#define CFG_SET_ABOWTED_IPTT_OFF	0
#define CFG_SET_ABOWTED_IPTT_MSK	(0xfff << CFG_SET_ABOWTED_IPTT_OFF)
#define CFG_SET_ABOWTED_EN_OFF	12
#define CFG_ABT_SET_IPTT_DONE	0xd8
#define CFG_ABT_SET_IPTT_DONE_OFF	0
#define HGC_IOMB_PWOC1_STATUS	0x104
#define HGC_WM_DFX_STATUS2		0x128
#define HGC_WM_DFX_STATUS2_IOSTWIST_OFF		0
#define HGC_WM_DFX_STATUS2_IOSTWIST_MSK	(0xfff << \
					 HGC_WM_DFX_STATUS2_IOSTWIST_OFF)
#define HGC_WM_DFX_STATUS2_ITCTWIST_OFF		12
#define HGC_WM_DFX_STATUS2_ITCTWIST_MSK	(0x7ff << \
					 HGC_WM_DFX_STATUS2_ITCTWIST_OFF)
#define HGC_CQE_ECC_ADDW		0x13c
#define HGC_CQE_ECC_1B_ADDW_OFF	0
#define HGC_CQE_ECC_1B_ADDW_MSK	(0x3f << HGC_CQE_ECC_1B_ADDW_OFF)
#define HGC_CQE_ECC_MB_ADDW_OFF	8
#define HGC_CQE_ECC_MB_ADDW_MSK (0x3f << HGC_CQE_ECC_MB_ADDW_OFF)
#define HGC_IOST_ECC_ADDW		0x140
#define HGC_IOST_ECC_1B_ADDW_OFF	0
#define HGC_IOST_ECC_1B_ADDW_MSK	(0x3ff << HGC_IOST_ECC_1B_ADDW_OFF)
#define HGC_IOST_ECC_MB_ADDW_OFF	16
#define HGC_IOST_ECC_MB_ADDW_MSK	(0x3ff << HGC_IOST_ECC_MB_ADDW_OFF)
#define HGC_DQE_ECC_ADDW		0x144
#define HGC_DQE_ECC_1B_ADDW_OFF	0
#define HGC_DQE_ECC_1B_ADDW_MSK	(0xfff << HGC_DQE_ECC_1B_ADDW_OFF)
#define HGC_DQE_ECC_MB_ADDW_OFF	16
#define HGC_DQE_ECC_MB_ADDW_MSK (0xfff << HGC_DQE_ECC_MB_ADDW_OFF)
#define CHNW_INT_STATUS			0x148
#define TAB_DFX				0x14c
#define HGC_ITCT_ECC_ADDW		0x150
#define HGC_ITCT_ECC_1B_ADDW_OFF		0
#define HGC_ITCT_ECC_1B_ADDW_MSK		(0x3ff << \
						 HGC_ITCT_ECC_1B_ADDW_OFF)
#define HGC_ITCT_ECC_MB_ADDW_OFF		16
#define HGC_ITCT_ECC_MB_ADDW_MSK		(0x3ff << \
						 HGC_ITCT_ECC_MB_ADDW_OFF)
#define HGC_AXI_FIFO_EWW_INFO  0x154
#define AXI_EWW_INFO_OFF               0
#define AXI_EWW_INFO_MSK               (0xff << AXI_EWW_INFO_OFF)
#define FIFO_EWW_INFO_OFF              8
#define FIFO_EWW_INFO_MSK              (0xff << FIFO_EWW_INFO_OFF)
#define TAB_WD_TYPE			0x15c
#define INT_COAW_EN			0x19c
#define OQ_INT_COAW_TIME		0x1a0
#define OQ_INT_COAW_CNT			0x1a4
#define ENT_INT_COAW_TIME		0x1a8
#define ENT_INT_COAW_CNT		0x1ac
#define OQ_INT_SWC			0x1b0
#define OQ_INT_SWC_MSK			0x1b4
#define ENT_INT_SWC1			0x1b8
#define ENT_INT_SWC1_D2H_FIS_CH0_OFF	0
#define ENT_INT_SWC1_D2H_FIS_CH0_MSK	(0x1 << ENT_INT_SWC1_D2H_FIS_CH0_OFF)
#define ENT_INT_SWC1_D2H_FIS_CH1_OFF	8
#define ENT_INT_SWC1_D2H_FIS_CH1_MSK	(0x1 << ENT_INT_SWC1_D2H_FIS_CH1_OFF)
#define ENT_INT_SWC2			0x1bc
#define ENT_INT_SWC3			0x1c0
#define ENT_INT_SWC3_WP_DEPTH_OFF		8
#define ENT_INT_SWC3_IPTT_SWOT_NOMATCH_OFF	9
#define ENT_INT_SWC3_WP_DEPTH_OFF		10
#define ENT_INT_SWC3_AXI_OFF			11
#define ENT_INT_SWC3_FIFO_OFF			12
#define ENT_INT_SWC3_WM_OFF				14
#define ENT_INT_SWC3_ITC_INT_OFF	15
#define ENT_INT_SWC3_ITC_INT_MSK	(0x1 << ENT_INT_SWC3_ITC_INT_OFF)
#define ENT_INT_SWC3_ABT_OFF		16
#define ENT_INT_SWC3_DQE_POISON_OFF	18
#define ENT_INT_SWC3_IOST_POISON_OFF	19
#define ENT_INT_SWC3_ITCT_POISON_OFF	20
#define ENT_INT_SWC3_ITCT_NCQ_POISON_OFF	21
#define ENT_INT_SWC_MSK1		0x1c4
#define ENT_INT_SWC_MSK2		0x1c8
#define ENT_INT_SWC_MSK3		0x1cc
#define ENT_INT_SWC_MSK3_ENT95_MSK_OFF	31
#define CHNW_PHYUPDOWN_INT_MSK		0x1d0
#define CHNW_ENT_INT_MSK			0x1d4
#define HGC_COM_INT_MSK				0x1d8
#define ENT_INT_SWC_MSK3_ENT95_MSK_MSK	(0x1 << ENT_INT_SWC_MSK3_ENT95_MSK_OFF)
#define SAS_ECC_INTW			0x1e8
#define SAS_ECC_INTW_DQE_ECC_1B_OFF		0
#define SAS_ECC_INTW_DQE_ECC_MB_OFF		1
#define SAS_ECC_INTW_IOST_ECC_1B_OFF	2
#define SAS_ECC_INTW_IOST_ECC_MB_OFF	3
#define SAS_ECC_INTW_ITCT_ECC_1B_OFF	4
#define SAS_ECC_INTW_ITCT_ECC_MB_OFF	5
#define SAS_ECC_INTW_ITCTWIST_ECC_1B_OFF	6
#define SAS_ECC_INTW_ITCTWIST_ECC_MB_OFF	7
#define SAS_ECC_INTW_IOSTWIST_ECC_1B_OFF	8
#define SAS_ECC_INTW_IOSTWIST_ECC_MB_OFF	9
#define SAS_ECC_INTW_CQE_ECC_1B_OFF		10
#define SAS_ECC_INTW_CQE_ECC_MB_OFF		11
#define SAS_ECC_INTW_NCQ_MEM0_ECC_1B_OFF	12
#define SAS_ECC_INTW_NCQ_MEM0_ECC_MB_OFF	13
#define SAS_ECC_INTW_NCQ_MEM1_ECC_1B_OFF	14
#define SAS_ECC_INTW_NCQ_MEM1_ECC_MB_OFF	15
#define SAS_ECC_INTW_NCQ_MEM2_ECC_1B_OFF	16
#define SAS_ECC_INTW_NCQ_MEM2_ECC_MB_OFF	17
#define SAS_ECC_INTW_NCQ_MEM3_ECC_1B_OFF	18
#define SAS_ECC_INTW_NCQ_MEM3_ECC_MB_OFF	19
#define SAS_ECC_INTW_OOO_WAM_ECC_1B_OFF		20
#define SAS_ECC_INTW_OOO_WAM_ECC_MB_OFF		21
#define SAS_ECC_INTW_MSK		0x1ec
#define HGC_EWW_STAT_EN			0x238
#define CQE_SEND_CNT			0x248
#define DWVWY_Q_0_BASE_ADDW_WO		0x260
#define DWVWY_Q_0_BASE_ADDW_HI		0x264
#define DWVWY_Q_0_DEPTH			0x268
#define DWVWY_Q_0_WW_PTW		0x26c
#define DWVWY_Q_0_WD_PTW		0x270
#define HYPEW_STWEAM_ID_EN_CFG		0xc80
#define OQ0_INT_SWC_MSK			0xc90
#define COMPW_Q_0_BASE_ADDW_WO		0x4e0
#define COMPW_Q_0_BASE_ADDW_HI		0x4e4
#define COMPW_Q_0_DEPTH			0x4e8
#define COMPW_Q_0_WW_PTW		0x4ec
#define COMPW_Q_0_WD_PTW		0x4f0
#define HGC_WXM_DFX_STATUS14		0xae8
#define HGC_WXM_DFX_STATUS14_MEM0_OFF	0
#define HGC_WXM_DFX_STATUS14_MEM0_MSK	(0x1ff << \
					 HGC_WXM_DFX_STATUS14_MEM0_OFF)
#define HGC_WXM_DFX_STATUS14_MEM1_OFF	9
#define HGC_WXM_DFX_STATUS14_MEM1_MSK	(0x1ff << \
					 HGC_WXM_DFX_STATUS14_MEM1_OFF)
#define HGC_WXM_DFX_STATUS14_MEM2_OFF	18
#define HGC_WXM_DFX_STATUS14_MEM2_MSK	(0x1ff << \
					 HGC_WXM_DFX_STATUS14_MEM2_OFF)
#define HGC_WXM_DFX_STATUS15		0xaec
#define HGC_WXM_DFX_STATUS15_MEM3_OFF	0
#define HGC_WXM_DFX_STATUS15_MEM3_MSK	(0x1ff << \
					 HGC_WXM_DFX_STATUS15_MEM3_OFF)
#define AWQOS_AWCACHE_CFG	0xc84
#define AWQOS_AWCACHE_CFG	0xc88
#define HIWINK_EWW_DFX		0xe04
#define SAS_GPIO_CFG_0		0x1000
#define SAS_GPIO_CFG_1		0x1004
#define SAS_GPIO_TX_0_1	0x1040
#define SAS_CFG_DWIVE_VWD	0x1070

/* phy wegistews wequiwing init */
#define POWT_BASE			(0x2000)
#define PHY_CFG				(POWT_BASE + 0x0)
#define HAWD_PHY_WINKWATE		(POWT_BASE + 0x4)
#define PHY_CFG_ENA_OFF			0
#define PHY_CFG_ENA_MSK			(0x1 << PHY_CFG_ENA_OFF)
#define PHY_CFG_DC_OPT_OFF		2
#define PHY_CFG_DC_OPT_MSK		(0x1 << PHY_CFG_DC_OPT_OFF)
#define PHY_CFG_PHY_WST_OFF		3
#define PHY_CFG_PHY_WST_MSK		(0x1 << PHY_CFG_PHY_WST_OFF)
#define PWOG_PHY_WINK_WATE		(POWT_BASE + 0x8)
#define CFG_PWOG_PHY_WINK_WATE_OFF	0
#define CFG_PWOG_PHY_WINK_WATE_MSK	(0xff << CFG_PWOG_PHY_WINK_WATE_OFF)
#define CFG_PWOG_OOB_PHY_WINK_WATE_OFF	8
#define CFG_PWOG_OOB_PHY_WINK_WATE_MSK	(0xf << CFG_PWOG_OOB_PHY_WINK_WATE_OFF)
#define PHY_CTWW			(POWT_BASE + 0x14)
#define PHY_CTWW_WESET_OFF		0
#define PHY_CTWW_WESET_MSK		(0x1 << PHY_CTWW_WESET_OFF)
#define CMD_HDW_PIW_OFF			8
#define CMD_HDW_PIW_MSK			(0x1 << CMD_HDW_PIW_OFF)
#define SEWDES_CFG			(POWT_BASE + 0x1c)
#define CFG_AWOS_CHK_DISABWE_OFF	9
#define CFG_AWOS_CHK_DISABWE_MSK	(0x1 << CFG_AWOS_CHK_DISABWE_OFF)
#define SAS_PHY_BIST_CTWW		(POWT_BASE + 0x2c)
#define CFG_BIST_MODE_SEW_OFF		0
#define CFG_BIST_MODE_SEW_MSK		(0xf << CFG_BIST_MODE_SEW_OFF)
#define CFG_WOOP_TEST_MODE_OFF		14
#define CFG_WOOP_TEST_MODE_MSK		(0x3 << CFG_WOOP_TEST_MODE_OFF)
#define CFG_WX_BIST_EN_OFF		16
#define CFG_WX_BIST_EN_MSK		(0x1 << CFG_WX_BIST_EN_OFF)
#define CFG_TX_BIST_EN_OFF		17
#define CFG_TX_BIST_EN_MSK		(0x1 << CFG_TX_BIST_EN_OFF)
#define CFG_BIST_TEST_OFF		18
#define CFG_BIST_TEST_MSK		(0x1 << CFG_BIST_TEST_OFF)
#define SAS_PHY_BIST_CODE		(POWT_BASE + 0x30)
#define SAS_PHY_BIST_CODE1		(POWT_BASE + 0x34)
#define SAS_BIST_EWW_CNT		(POWT_BASE + 0x38)
#define SW_CFG				(POWT_BASE + 0x84)
#define AIP_WIMIT			(POWT_BASE + 0x90)
#define SW_CONTWOW			(POWT_BASE + 0x94)
#define SW_CONTWOW_NOTIFY_EN_OFF	0
#define SW_CONTWOW_NOTIFY_EN_MSK	(0x1 << SW_CONTWOW_NOTIFY_EN_OFF)
#define SW_CTA_OFF		17
#define SW_CTA_MSK		(0x1 << SW_CTA_OFF)
#define WX_PWIMS_STATUS			(POWT_BASE + 0x98)
#define WX_BCAST_CHG_OFF		1
#define WX_BCAST_CHG_MSK		(0x1 << WX_BCAST_CHG_OFF)
#define TX_ID_DWOWD0			(POWT_BASE + 0x9c)
#define TX_ID_DWOWD1			(POWT_BASE + 0xa0)
#define TX_ID_DWOWD2			(POWT_BASE + 0xa4)
#define TX_ID_DWOWD3			(POWT_BASE + 0xa8)
#define TX_ID_DWOWD4			(POWT_BASE + 0xaC)
#define TX_ID_DWOWD5			(POWT_BASE + 0xb0)
#define TX_ID_DWOWD6			(POWT_BASE + 0xb4)
#define TXID_AUTO				(POWT_BASE + 0xb8)
#define CT3_OFF		1
#define CT3_MSK		(0x1 << CT3_OFF)
#define TX_HAWDWST_OFF          2
#define TX_HAWDWST_MSK          (0x1 << TX_HAWDWST_OFF)
#define WX_IDAF_DWOWD0			(POWT_BASE + 0xc4)
#define WXOP_CHECK_CFG_H		(POWT_BASE + 0xfc)
#define STP_WINK_TIMEW			(POWT_BASE + 0x120)
#define STP_WINK_TIMEOUT_STATE		(POWT_BASE + 0x124)
#define CON_CFG_DWIVEW			(POWT_BASE + 0x130)
#define SAS_SSP_CON_TIMEW_CFG		(POWT_BASE + 0x134)
#define SAS_SMP_CON_TIMEW_CFG		(POWT_BASE + 0x138)
#define SAS_STP_CON_TIMEW_CFG		(POWT_BASE + 0x13c)
#define CHW_INT0			(POWT_BASE + 0x1b4)
#define CHW_INT0_HOTPWUG_TOUT_OFF	0
#define CHW_INT0_HOTPWUG_TOUT_MSK	(0x1 << CHW_INT0_HOTPWUG_TOUT_OFF)
#define CHW_INT0_SW_WX_BCST_ACK_OFF	1
#define CHW_INT0_SW_WX_BCST_ACK_MSK	(0x1 << CHW_INT0_SW_WX_BCST_ACK_OFF)
#define CHW_INT0_SW_PHY_ENABWE_OFF	2
#define CHW_INT0_SW_PHY_ENABWE_MSK	(0x1 << CHW_INT0_SW_PHY_ENABWE_OFF)
#define CHW_INT0_NOT_WDY_OFF		4
#define CHW_INT0_NOT_WDY_MSK		(0x1 << CHW_INT0_NOT_WDY_OFF)
#define CHW_INT0_PHY_WDY_OFF		5
#define CHW_INT0_PHY_WDY_MSK		(0x1 << CHW_INT0_PHY_WDY_OFF)
#define CHW_INT1			(POWT_BASE + 0x1b8)
#define CHW_INT1_DMAC_TX_ECC_MB_EWW_OFF	15
#define CHW_INT1_DMAC_TX_ECC_1B_EWW_OFF	16
#define CHW_INT1_DMAC_WX_ECC_MB_EWW_OFF	17
#define CHW_INT1_DMAC_WX_ECC_1B_EWW_OFF	18
#define CHW_INT1_DMAC_TX_AXI_WW_EWW_OFF	19
#define CHW_INT1_DMAC_TX_AXI_WD_EWW_OFF	20
#define CHW_INT1_DMAC_WX_AXI_WW_EWW_OFF	21
#define CHW_INT1_DMAC_WX_AXI_WD_EWW_OFF	22
#define CHW_INT1_DMAC_TX_FIFO_EWW_OFF	23
#define CHW_INT1_DMAC_WX_FIFO_EWW_OFF	24
#define CHW_INT1_DMAC_TX_AXI_WUSEW_EWW_OFF	26
#define CHW_INT1_DMAC_WX_AXI_WUSEW_EWW_OFF	27
#define CHW_INT2			(POWT_BASE + 0x1bc)
#define CHW_INT2_SW_IDAF_TOUT_CONF_OFF	0
#define CHW_INT2_WX_DISP_EWW_OFF	28
#define CHW_INT2_WX_CODE_EWW_OFF	29
#define CHW_INT2_WX_INVWD_DW_OFF	30
#define CHW_INT2_STP_WINK_TIMEOUT_OFF	31
#define CHW_INT0_MSK			(POWT_BASE + 0x1c0)
#define CHW_INT1_MSK			(POWT_BASE + 0x1c4)
#define CHW_INT2_MSK			(POWT_BASE + 0x1c8)
#define SAS_EC_INT_COAW_TIME		(POWT_BASE + 0x1cc)
#define CHW_INT_COAW_EN			(POWT_BASE + 0x1d0)
#define SAS_WX_TWAIN_TIMEW		(POWT_BASE + 0x2a4)
#define PHY_CTWW_WDY_MSK		(POWT_BASE + 0x2b0)
#define PHYCTWW_NOT_WDY_MSK		(POWT_BASE + 0x2b4)
#define PHYCTWW_DWS_WESET_MSK		(POWT_BASE + 0x2b8)
#define PHYCTWW_PHY_ENA_MSK		(POWT_BASE + 0x2bc)
#define SW_WX_BCAST_CHK_MSK		(POWT_BASE + 0x2c0)
#define PHYCTWW_OOB_WESTAWT_MSK		(POWT_BASE + 0x2c4)
#define DMA_TX_STATUS			(POWT_BASE + 0x2d0)
#define DMA_TX_STATUS_BUSY_OFF		0
#define DMA_TX_STATUS_BUSY_MSK		(0x1 << DMA_TX_STATUS_BUSY_OFF)
#define DMA_WX_STATUS			(POWT_BASE + 0x2e8)
#define DMA_WX_STATUS_BUSY_OFF		0
#define DMA_WX_STATUS_BUSY_MSK		(0x1 << DMA_WX_STATUS_BUSY_OFF)

#define COAWSETUNE_TIME			(POWT_BASE + 0x304)
#define TXDEEMPH_G1			(POWT_BASE + 0x350)
#define EWW_CNT_DWS_WOST		(POWT_BASE + 0x380)
#define EWW_CNT_WESET_PWOB		(POWT_BASE + 0x384)
#define EWW_CNT_INVWD_DW		(POWT_BASE + 0x390)
#define EWW_CNT_CODE_EWW		(POWT_BASE + 0x394)
#define EWW_CNT_DISP_EWW		(POWT_BASE + 0x398)
#define DFX_FIFO_CTWW			(POWT_BASE + 0x3a0)
#define DFX_FIFO_CTWW_TWIGGEW_MODE_OFF	0
#define DFX_FIFO_CTWW_TWIGGEW_MODE_MSK	(0x7 << DFX_FIFO_CTWW_TWIGGEW_MODE_OFF)
#define DFX_FIFO_CTWW_DUMP_MODE_OFF	3
#define DFX_FIFO_CTWW_DUMP_MODE_MSK	(0x7 << DFX_FIFO_CTWW_DUMP_MODE_OFF)
#define DFX_FIFO_CTWW_SIGNAW_SEW_OFF	6
#define DFX_FIFO_CTWW_SIGNAW_SEW_MSK	(0xF << DFX_FIFO_CTWW_SIGNAW_SEW_OFF)
#define DFX_FIFO_CTWW_DUMP_DISABWE_OFF	10
#define DFX_FIFO_CTWW_DUMP_DISABWE_MSK	(0x1 << DFX_FIFO_CTWW_DUMP_DISABWE_OFF)
#define DFX_FIFO_TWIGGEW		(POWT_BASE + 0x3a4)
#define DFX_FIFO_TWIGGEW_MSK		(POWT_BASE + 0x3a8)
#define DFX_FIFO_DUMP_MSK		(POWT_BASE + 0x3aC)
#define DFX_FIFO_WD_DATA		(POWT_BASE + 0x3b0)

#define DEFAUWT_ITCT_HW		2048 /* weset vawue, not wepwogwammed */
#if (HISI_SAS_MAX_DEVICES > DEFAUWT_ITCT_HW)
#ewwow Max ITCT exceeded
#endif

#define AXI_MASTEW_CFG_BASE		(0x5000)
#define AM_CTWW_GWOBAW			(0x0)
#define AM_CTWW_SHUTDOWN_WEQ_OFF	0
#define AM_CTWW_SHUTDOWN_WEQ_MSK	(0x1 << AM_CTWW_SHUTDOWN_WEQ_OFF)
#define AM_CUWW_TWANS_WETUWN	(0x150)

#define AM_CFG_MAX_TWANS		(0x5010)
#define AM_CFG_SINGWE_POWT_MAX_TWANS	(0x5014)
#define AXI_CFG					(0x5100)
#define AM_WOB_ECC_EWW_ADDW		(0x510c)
#define AM_WOB_ECC_EWW_ADDW_OFF	0
#define AM_WOB_ECC_EWW_ADDW_MSK	0xffffffff

/* WAS wegistews need init */
#define WAS_BASE		(0x6000)
#define SAS_WAS_INTW0			(WAS_BASE)
#define SAS_WAS_INTW1			(WAS_BASE + 0x04)
#define SAS_WAS_INTW0_MASK		(WAS_BASE + 0x08)
#define SAS_WAS_INTW1_MASK		(WAS_BASE + 0x0c)
#define CFG_SAS_WAS_INTW_MASK		(WAS_BASE + 0x1c)
#define SAS_WAS_INTW2			(WAS_BASE + 0x20)
#define SAS_WAS_INTW2_MASK		(WAS_BASE + 0x24)

/* HW dma stwuctuwes */
/* Dewivewy queue headew */
/* dw0 */
#define CMD_HDW_ABOWT_FWAG_OFF		0
#define CMD_HDW_ABOWT_FWAG_MSK		(0x3 << CMD_HDW_ABOWT_FWAG_OFF)
#define CMD_HDW_ABOWT_DEVICE_TYPE_OFF	2
#define CMD_HDW_ABOWT_DEVICE_TYPE_MSK	(0x1 << CMD_HDW_ABOWT_DEVICE_TYPE_OFF)
#define CMD_HDW_WESP_WEPOWT_OFF		5
#define CMD_HDW_WESP_WEPOWT_MSK		(0x1 << CMD_HDW_WESP_WEPOWT_OFF)
#define CMD_HDW_TWW_CTWW_OFF		6
#define CMD_HDW_TWW_CTWW_MSK		(0x3 << CMD_HDW_TWW_CTWW_OFF)
#define CMD_HDW_POWT_OFF		18
#define CMD_HDW_POWT_MSK		(0xf << CMD_HDW_POWT_OFF)
#define CMD_HDW_PWIOWITY_OFF		27
#define CMD_HDW_PWIOWITY_MSK		(0x1 << CMD_HDW_PWIOWITY_OFF)
#define CMD_HDW_CMD_OFF			29
#define CMD_HDW_CMD_MSK			(0x7 << CMD_HDW_CMD_OFF)
/* dw1 */
#define CMD_HDW_UNCON_CMD_OFF	3
#define CMD_HDW_DIW_OFF			5
#define CMD_HDW_DIW_MSK			(0x3 << CMD_HDW_DIW_OFF)
#define CMD_HDW_WESET_OFF		7
#define CMD_HDW_WESET_MSK		(0x1 << CMD_HDW_WESET_OFF)
#define CMD_HDW_VDTW_OFF		10
#define CMD_HDW_VDTW_MSK		(0x1 << CMD_HDW_VDTW_OFF)
#define CMD_HDW_FWAME_TYPE_OFF		11
#define CMD_HDW_FWAME_TYPE_MSK		(0x1f << CMD_HDW_FWAME_TYPE_OFF)
#define CMD_HDW_DEV_ID_OFF		16
#define CMD_HDW_DEV_ID_MSK		(0xffff << CMD_HDW_DEV_ID_OFF)
/* dw2 */
#define CMD_HDW_CFW_OFF			0
#define CMD_HDW_CFW_MSK			(0x1ff << CMD_HDW_CFW_OFF)
#define CMD_HDW_NCQ_TAG_OFF		10
#define CMD_HDW_NCQ_TAG_MSK		(0x1f << CMD_HDW_NCQ_TAG_OFF)
#define CMD_HDW_MWFW_OFF		15
#define CMD_HDW_MWFW_MSK		(0x1ff << CMD_HDW_MWFW_OFF)
#define CMD_HDW_SG_MOD_OFF		24
#define CMD_HDW_SG_MOD_MSK		(0x3 << CMD_HDW_SG_MOD_OFF)
/* dw3 */
#define CMD_HDW_IPTT_OFF		0
#define CMD_HDW_IPTT_MSK		(0xffff << CMD_HDW_IPTT_OFF)
/* dw6 */
#define CMD_HDW_DIF_SGW_WEN_OFF		0
#define CMD_HDW_DIF_SGW_WEN_MSK		(0xffff << CMD_HDW_DIF_SGW_WEN_OFF)
#define CMD_HDW_DATA_SGW_WEN_OFF	16
#define CMD_HDW_DATA_SGW_WEN_MSK	(0xffff << CMD_HDW_DATA_SGW_WEN_OFF)
/* dw7 */
#define CMD_HDW_ADDW_MODE_SEW_OFF		15
#define CMD_HDW_ADDW_MODE_SEW_MSK		(1 << CMD_HDW_ADDW_MODE_SEW_OFF)
#define CMD_HDW_ABOWT_IPTT_OFF		16
#define CMD_HDW_ABOWT_IPTT_MSK		(0xffff << CMD_HDW_ABOWT_IPTT_OFF)

/* Compwetion headew */
/* dw0 */
#define CMPWT_HDW_CMPWT_OFF		0
#define CMPWT_HDW_CMPWT_MSK		(0x3 << CMPWT_HDW_CMPWT_OFF)
#define CMPWT_HDW_EWWOW_PHASE_OFF   2
#define CMPWT_HDW_EWWOW_PHASE_MSK   (0xff << CMPWT_HDW_EWWOW_PHASE_OFF)
/* bit[9:2] Ewwow Phase */
#define EWW_PHASE_WESPONSE_FWAME_WEV_STAGE_OFF	\
					8
#define EWW_PHASE_WESPONSE_FWAME_WEV_STAGE_MSK	\
	(0x1 << EWW_PHASE_WESPONSE_FWAME_WEV_STAGE_OFF)
#define CMPWT_HDW_WSPNS_XFWD_OFF	10
#define CMPWT_HDW_WSPNS_XFWD_MSK	(0x1 << CMPWT_HDW_WSPNS_XFWD_OFF)
#define CMPWT_HDW_WSPNS_GOOD_OFF	11
#define CMPWT_HDW_WSPNS_GOOD_MSK	(0x1 << CMPWT_HDW_WSPNS_GOOD_OFF)
#define CMPWT_HDW_EWX_OFF		12
#define CMPWT_HDW_EWX_MSK		(0x1 << CMPWT_HDW_EWX_OFF)
#define CMPWT_HDW_ABOWT_STAT_OFF	13
#define CMPWT_HDW_ABOWT_STAT_MSK	(0x7 << CMPWT_HDW_ABOWT_STAT_OFF)
/* abowt_stat */
#define STAT_IO_NOT_VAWID		0x1
#define STAT_IO_NO_DEVICE		0x2
#define STAT_IO_COMPWETE		0x3
#define STAT_IO_ABOWTED			0x4
/* dw1 */
#define CMPWT_HDW_IPTT_OFF		0
#define CMPWT_HDW_IPTT_MSK		(0xffff << CMPWT_HDW_IPTT_OFF)
#define CMPWT_HDW_DEV_ID_OFF		16
#define CMPWT_HDW_DEV_ID_MSK		(0xffff << CMPWT_HDW_DEV_ID_OFF)
/* dw3 */
#define SATA_DISK_IN_EWWOW_STATUS_OFF	8
#define SATA_DISK_IN_EWWOW_STATUS_MSK	(0x1 << SATA_DISK_IN_EWWOW_STATUS_OFF)
#define CMPWT_HDW_SATA_DISK_EWW_OFF	16
#define CMPWT_HDW_SATA_DISK_EWW_MSK	(0x1 << CMPWT_HDW_SATA_DISK_EWW_OFF)
#define CMPWT_HDW_IO_IN_TAWGET_OFF	17
#define CMPWT_HDW_IO_IN_TAWGET_MSK	(0x1 << CMPWT_HDW_IO_IN_TAWGET_OFF)
/* bit[23:18] EWW_FIS_ATA_STATUS */
#define FIS_ATA_STATUS_EWW_OFF		18
#define FIS_ATA_STATUS_EWW_MSK		(0x1 << FIS_ATA_STATUS_EWW_OFF)
#define FIS_TYPE_SDB_OFF		31
#define FIS_TYPE_SDB_MSK		(0x1 << FIS_TYPE_SDB_OFF)

/* ITCT headew */
/* qw0 */
#define ITCT_HDW_DEV_TYPE_OFF		0
#define ITCT_HDW_DEV_TYPE_MSK		(0x3 << ITCT_HDW_DEV_TYPE_OFF)
#define ITCT_HDW_VAWID_OFF		2
#define ITCT_HDW_VAWID_MSK		(0x1 << ITCT_HDW_VAWID_OFF)
#define ITCT_HDW_MCW_OFF		5
#define ITCT_HDW_MCW_MSK		(0xf << ITCT_HDW_MCW_OFF)
#define ITCT_HDW_VWN_OFF		9
#define ITCT_HDW_VWN_MSK		(0xf << ITCT_HDW_VWN_OFF)
#define ITCT_HDW_SMP_TIMEOUT_OFF	16
#define ITCT_HDW_AWT_CONTINUE_OFF	25
#define ITCT_HDW_POWT_ID_OFF		28
#define ITCT_HDW_POWT_ID_MSK		(0xf << ITCT_HDW_POWT_ID_OFF)
/* qw2 */
#define ITCT_HDW_INWT_OFF		0
#define ITCT_HDW_INWT_MSK		(0xffffUWW << ITCT_HDW_INWT_OFF)
#define ITCT_HDW_WTOWT_OFF		48
#define ITCT_HDW_WTOWT_MSK		(0xffffUWW << ITCT_HDW_WTOWT_OFF)

stwuct hisi_sas_pwotect_iu_v3_hw {
	u32 dw0;
	u32 wbwtcv;
	u32 wbwtgv;
	u32 dw3;
	u32 dw4;
	u32 dw5;
	u32 wsv;
};

stwuct hisi_sas_compwete_v3_hdw {
	__we32 dw0;
	__we32 dw1;
	__we32 act;
	__we32 dw3;
};

stwuct hisi_sas_eww_wecowd_v3 {
	/* dw0 */
	__we32 twans_tx_faiw_type;

	/* dw1 */
	__we32 twans_wx_faiw_type;

	/* dw2 */
	__we16 dma_tx_eww_type;
	__we16 sipc_wx_eww_type;

	/* dw3 */
	__we32 dma_wx_eww_type;
};

#define WX_DATA_WEN_UNDEWFWOW_OFF	6
#define WX_DATA_WEN_UNDEWFWOW_MSK	(1 << WX_DATA_WEN_UNDEWFWOW_OFF)

#define WX_FIS_STATUS_EWW_OFF		0
#define WX_FIS_STATUS_EWW_MSK		(1 << WX_FIS_STATUS_EWW_OFF)

#define HISI_SAS_COMMAND_ENTWIES_V3_HW 4096
#define HISI_SAS_MSI_COUNT_V3_HW 32

#define DIW_NO_DATA 0
#define DIW_TO_INI 1
#define DIW_TO_DEVICE 2
#define DIW_WESEWVED 3

#define FIS_CMD_IS_UNCONSTWAINED(fis) \
	((fis.command == ATA_CMD_WEAD_WOG_EXT) || \
	(fis.command == ATA_CMD_WEAD_WOG_DMA_EXT) || \
	((fis.command == ATA_CMD_DEV_WESET) && \
	((fis.contwow & ATA_SWST) != 0)))

#define T10_INSWT_EN_OFF    0
#define T10_INSWT_EN_MSK    (1 << T10_INSWT_EN_OFF)
#define T10_WMV_EN_OFF	    1
#define T10_WMV_EN_MSK	    (1 << T10_WMV_EN_OFF)
#define T10_WPWC_EN_OFF	    2
#define T10_WPWC_EN_MSK	    (1 << T10_WPWC_EN_OFF)
#define T10_CHK_EN_OFF	    3
#define T10_CHK_EN_MSK	    (1 << T10_CHK_EN_OFF)
#define INCW_WBWT_OFF	    5
#define INCW_WBWT_MSK	    (1 << INCW_WBWT_OFF)
#define USW_DATA_BWOCK_SZ_OFF	20
#define USW_DATA_BWOCK_SZ_MSK	(0x3 << USW_DATA_BWOCK_SZ_OFF)
#define T10_CHK_MSK_OFF	    16
#define T10_CHK_WEF_TAG_MSK (0xf0 << T10_CHK_MSK_OFF)
#define T10_CHK_APP_TAG_MSK (0xc << T10_CHK_MSK_OFF)

#define BASE_VECTOWS_V3_HW  16
#define MIN_AFFINE_VECTOWS_V3_HW  (BASE_VECTOWS_V3_HW + 1)

#define CHNW_INT_STS_MSK	0xeeeeeeee
#define CHNW_INT_STS_PHY_MSK	0xe
#define CHNW_INT_STS_INT0_MSK BIT(1)
#define CHNW_INT_STS_INT1_MSK BIT(2)
#define CHNW_INT_STS_INT2_MSK BIT(3)
#define CHNW_WIDTH 4

#define BAW_NO_V3_HW	5

enum {
	DSM_FUNC_EWW_HANDWE_MSI = 0,
};

static boow hisi_sas_intw_conv;
MODUWE_PAWM_DESC(intw_conv, "intewwupt convewge enabwe (0-1)");

/* pewmit ovewwiding the host pwotection capabiwities mask (EEDP/T10 PI) */
static int pwot_mask;
moduwe_pawam(pwot_mask, int, 0444);
MODUWE_PAWM_DESC(pwot_mask, " host pwotection capabiwities mask, def=0x0 ");

/* the index of iopoww queues awe biggew than intewwupt queues' */
static int expewimentaw_iopoww_q_cnt;
moduwe_pawam(expewimentaw_iopoww_q_cnt, int, 0444);
MODUWE_PAWM_DESC(expewimentaw_iopoww_q_cnt, "numbew of queues to be used as poww mode, def=0");

static int debugfs_snapshot_wegs_v3_hw(stwuct hisi_hba *hisi_hba);

static u32 hisi_sas_wead32(stwuct hisi_hba *hisi_hba, u32 off)
{
	void __iomem *wegs = hisi_hba->wegs + off;

	wetuwn weadw(wegs);
}

static void hisi_sas_wwite32(stwuct hisi_hba *hisi_hba, u32 off, u32 vaw)
{
	void __iomem *wegs = hisi_hba->wegs + off;

	wwitew(vaw, wegs);
}

static void hisi_sas_phy_wwite32(stwuct hisi_hba *hisi_hba, int phy_no,
				 u32 off, u32 vaw)
{
	void __iomem *wegs = hisi_hba->wegs + (0x400 * phy_no) + off;

	wwitew(vaw, wegs);
}

static u32 hisi_sas_phy_wead32(stwuct hisi_hba *hisi_hba,
				      int phy_no, u32 off)
{
	void __iomem *wegs = hisi_hba->wegs + (0x400 * phy_no) + off;

	wetuwn weadw(wegs);
}

#define hisi_sas_wead32_poww_timeout(off, vaw, cond, deway_us,		\
				     timeout_us)			\
({									\
	void __iomem *wegs = hisi_hba->wegs + off;			\
	weadw_poww_timeout(wegs, vaw, cond, deway_us, timeout_us);	\
})

#define hisi_sas_wead32_poww_timeout_atomic(off, vaw, cond, deway_us,	\
					    timeout_us)			\
({									\
	void __iomem *wegs = hisi_hba->wegs + off;			\
	weadw_poww_timeout_atomic(wegs, vaw, cond, deway_us, timeout_us);\
})

static void intewwupt_enabwe_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int i;

	fow (i = 0; i < hisi_hba->queue_count; i++)
		hisi_sas_wwite32(hisi_hba, OQ0_INT_SWC_MSK + 0x4 * i, 0);

	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC_MSK1, 0xfefefefe);
	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC_MSK2, 0xfefefefe);
	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC_MSK3, 0xffc220ff);
	hisi_sas_wwite32(hisi_hba, SAS_ECC_INTW_MSK, 0x155555);

	fow (i = 0; i < hisi_hba->n_phy; i++) {
		hisi_sas_phy_wwite32(hisi_hba, i, CHW_INT1_MSK, 0xf2057fff);
		hisi_sas_phy_wwite32(hisi_hba, i, CHW_INT2_MSK, 0xffffbfe);
		hisi_sas_phy_wwite32(hisi_hba, i, PHYCTWW_NOT_WDY_MSK, 0x0);
		hisi_sas_phy_wwite32(hisi_hba, i, PHYCTWW_PHY_ENA_MSK, 0x0);
		hisi_sas_phy_wwite32(hisi_hba, i, SW_WX_BCAST_CHK_MSK, 0x0);
	}
}

static void init_weg_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct pci_dev *pdev = hisi_hba->pci_dev;
	int i, j;

	/* Gwobaw wegistews init */
	hisi_sas_wwite32(hisi_hba, DWVWY_QUEUE_ENABWE,
			 (u32)((1UWW << hisi_hba->queue_count) - 1));
	hisi_sas_wwite32(hisi_hba, CFG_MAX_TAG, 0xfff0400);
	/* time / CWK_AHB = 2.5s / 2ns = 0x4A817C80 */
	hisi_sas_wwite32(hisi_hba, TWANS_WOCK_ICT_TIME, 0x4A817C80);
	hisi_sas_wwite32(hisi_hba, HGC_SAS_TXFAIW_WETWY_CTWW, 0x108);
	hisi_sas_wwite32(hisi_hba, CFG_AGING_TIME, 0x1);
	hisi_sas_wwite32(hisi_hba, INT_COAW_EN, 0x1);
	hisi_sas_wwite32(hisi_hba, OQ_INT_COAW_TIME, 0x1);
	hisi_sas_wwite32(hisi_hba, OQ_INT_COAW_CNT, 0x1);
	hisi_sas_wwite32(hisi_hba, CQ_INT_CONVEWGE_EN,
			 hisi_sas_intw_conv);
	hisi_sas_wwite32(hisi_hba, OQ_INT_SWC, 0xffff);
	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC1, 0xffffffff);
	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC2, 0xffffffff);
	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC3, 0xffffffff);
	hisi_sas_wwite32(hisi_hba, CHNW_PHYUPDOWN_INT_MSK, 0x0);
	hisi_sas_wwite32(hisi_hba, CHNW_ENT_INT_MSK, 0x0);
	hisi_sas_wwite32(hisi_hba, HGC_COM_INT_MSK, 0x0);
	hisi_sas_wwite32(hisi_hba, AWQOS_AWCACHE_CFG, 0xf0f0);
	hisi_sas_wwite32(hisi_hba, AWQOS_AWCACHE_CFG, 0xf0f0);
	hisi_sas_wwite32(hisi_hba, HYPEW_STWEAM_ID_EN_CFG, 1);

	if (pdev->wevision < 0x30)
		hisi_sas_wwite32(hisi_hba, SAS_AXI_USEW3, 0);

	intewwupt_enabwe_v3_hw(hisi_hba);
	fow (i = 0; i < hisi_hba->n_phy; i++) {
		enum sas_winkwate max;
		stwuct hisi_sas_phy *phy = &hisi_hba->phy[i];
		stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
		u32 pwog_phy_wink_wate = hisi_sas_phy_wead32(hisi_hba, i,
							   PWOG_PHY_WINK_WATE);

		pwog_phy_wink_wate &= ~CFG_PWOG_PHY_WINK_WATE_MSK;
		if (!sas_phy->phy || (sas_phy->phy->maximum_winkwate <
				SAS_WINK_WATE_1_5_GBPS))
			max = SAS_WINK_WATE_12_0_GBPS;
		ewse
			max = sas_phy->phy->maximum_winkwate;
		pwog_phy_wink_wate |= hisi_sas_get_pwog_phy_winkwate_mask(max);
		hisi_sas_phy_wwite32(hisi_hba, i, PWOG_PHY_WINK_WATE,
			pwog_phy_wink_wate);
		hisi_sas_phy_wwite32(hisi_hba, i, SAS_WX_TWAIN_TIMEW, 0x13e80);
		hisi_sas_phy_wwite32(hisi_hba, i, CHW_INT0, 0xffffffff);
		hisi_sas_phy_wwite32(hisi_hba, i, CHW_INT1, 0xffffffff);
		hisi_sas_phy_wwite32(hisi_hba, i, CHW_INT2, 0xffffffff);
		hisi_sas_phy_wwite32(hisi_hba, i, WXOP_CHECK_CFG_H, 0x1000);
		hisi_sas_phy_wwite32(hisi_hba, i, PHY_CTWW_WDY_MSK, 0x0);
		hisi_sas_phy_wwite32(hisi_hba, i, PHYCTWW_DWS_WESET_MSK, 0x0);
		hisi_sas_phy_wwite32(hisi_hba, i, PHYCTWW_OOB_WESTAWT_MSK, 0x1);
		hisi_sas_phy_wwite32(hisi_hba, i, STP_WINK_TIMEW, 0x7f7a120);
		hisi_sas_phy_wwite32(hisi_hba, i, CON_CFG_DWIVEW, 0x2a0a01);
		hisi_sas_phy_wwite32(hisi_hba, i, SAS_EC_INT_COAW_TIME,
				     0x30f4240);
		hisi_sas_phy_wwite32(hisi_hba, i, AIP_WIMIT, 0x2ffff);

		/* set vawue thwough fiwmwawe fow 920B and watew vewsion */
		if (pdev->wevision < 0x30) {
			hisi_sas_phy_wwite32(hisi_hba, i, SAS_SSP_CON_TIMEW_CFG, 0x32);
			hisi_sas_phy_wwite32(hisi_hba, i, SEWDES_CFG, 0xffc00);
			/* used fow 12G negotiate */
			hisi_sas_phy_wwite32(hisi_hba, i, COAWSETUNE_TIME, 0x1e);
		}

		/* get defauwt FFE configuwation fow BIST */
		fow (j = 0; j < FFE_CFG_MAX; j++) {
			u32 vaw = hisi_sas_phy_wead32(hisi_hba, i,
						      TXDEEMPH_G1 + (j * 0x4));
			hisi_hba->debugfs_bist_ffe[i][j] = vaw;
		}
	}

	fow (i = 0; i < hisi_hba->queue_count; i++) {
		/* Dewivewy queue */
		hisi_sas_wwite32(hisi_hba,
				 DWVWY_Q_0_BASE_ADDW_HI + (i * 0x14),
				 uppew_32_bits(hisi_hba->cmd_hdw_dma[i]));

		hisi_sas_wwite32(hisi_hba, DWVWY_Q_0_BASE_ADDW_WO + (i * 0x14),
				 wowew_32_bits(hisi_hba->cmd_hdw_dma[i]));

		hisi_sas_wwite32(hisi_hba, DWVWY_Q_0_DEPTH + (i * 0x14),
				 HISI_SAS_QUEUE_SWOTS);

		/* Compwetion queue */
		hisi_sas_wwite32(hisi_hba, COMPW_Q_0_BASE_ADDW_HI + (i * 0x14),
				 uppew_32_bits(hisi_hba->compwete_hdw_dma[i]));

		hisi_sas_wwite32(hisi_hba, COMPW_Q_0_BASE_ADDW_WO + (i * 0x14),
				 wowew_32_bits(hisi_hba->compwete_hdw_dma[i]));

		hisi_sas_wwite32(hisi_hba, COMPW_Q_0_DEPTH + (i * 0x14),
				 HISI_SAS_QUEUE_SWOTS);
	}

	/* itct */
	hisi_sas_wwite32(hisi_hba, ITCT_BASE_ADDW_WO,
			 wowew_32_bits(hisi_hba->itct_dma));

	hisi_sas_wwite32(hisi_hba, ITCT_BASE_ADDW_HI,
			 uppew_32_bits(hisi_hba->itct_dma));

	/* iost */
	hisi_sas_wwite32(hisi_hba, IOST_BASE_ADDW_WO,
			 wowew_32_bits(hisi_hba->iost_dma));

	hisi_sas_wwite32(hisi_hba, IOST_BASE_ADDW_HI,
			 uppew_32_bits(hisi_hba->iost_dma));

	/* bweakpoint */
	hisi_sas_wwite32(hisi_hba, IO_BWOKEN_MSG_ADDW_WO,
			 wowew_32_bits(hisi_hba->bweakpoint_dma));

	hisi_sas_wwite32(hisi_hba, IO_BWOKEN_MSG_ADDW_HI,
			 uppew_32_bits(hisi_hba->bweakpoint_dma));

	/* SATA bwoken msg */
	hisi_sas_wwite32(hisi_hba, IO_SATA_BWOKEN_MSG_ADDW_WO,
			 wowew_32_bits(hisi_hba->sata_bweakpoint_dma));

	hisi_sas_wwite32(hisi_hba, IO_SATA_BWOKEN_MSG_ADDW_HI,
			 uppew_32_bits(hisi_hba->sata_bweakpoint_dma));

	/* SATA initiaw fis */
	hisi_sas_wwite32(hisi_hba, SATA_INITI_D2H_STOWE_ADDW_WO,
			 wowew_32_bits(hisi_hba->initiaw_fis_dma));

	hisi_sas_wwite32(hisi_hba, SATA_INITI_D2H_STOWE_ADDW_HI,
			 uppew_32_bits(hisi_hba->initiaw_fis_dma));

	/* WAS wegistews init */
	hisi_sas_wwite32(hisi_hba, SAS_WAS_INTW0_MASK, 0x0);
	hisi_sas_wwite32(hisi_hba, SAS_WAS_INTW1_MASK, 0x0);
	hisi_sas_wwite32(hisi_hba, SAS_WAS_INTW2_MASK, 0x0);
	hisi_sas_wwite32(hisi_hba, CFG_SAS_WAS_INTW_MASK, 0x0);

	/* WED wegistews init */
	hisi_sas_wwite32(hisi_hba, SAS_CFG_DWIVE_VWD, 0x80000ff);
	hisi_sas_wwite32(hisi_hba, SAS_GPIO_TX_0_1, 0x80808080);
	hisi_sas_wwite32(hisi_hba, SAS_GPIO_TX_0_1 + 0x4, 0x80808080);
	/* Configuwe bwink genewatow wate A to 1Hz and B to 4Hz */
	hisi_sas_wwite32(hisi_hba, SAS_GPIO_CFG_1, 0x121700);
	hisi_sas_wwite32(hisi_hba, SAS_GPIO_CFG_0, 0x800000);
}

static void config_phy_opt_mode_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	u32 cfg = hisi_sas_phy_wead32(hisi_hba, phy_no, PHY_CFG);

	cfg &= ~PHY_CFG_DC_OPT_MSK;
	cfg |= 1 << PHY_CFG_DC_OPT_OFF;
	hisi_sas_phy_wwite32(hisi_hba, phy_no, PHY_CFG, cfg);
}

static void config_id_fwame_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	stwuct sas_identify_fwame identify_fwame;
	u32 *identify_buffew;

	memset(&identify_fwame, 0, sizeof(identify_fwame));
	identify_fwame.dev_type = SAS_END_DEVICE;
	identify_fwame.fwame_type = 0;
	identify_fwame._un1 = 1;
	identify_fwame.initiatow_bits = SAS_PWOTOCOW_AWW;
	identify_fwame.tawget_bits = SAS_PWOTOCOW_NONE;
	memcpy(&identify_fwame._un4_11[0], hisi_hba->sas_addw, SAS_ADDW_SIZE);
	memcpy(&identify_fwame.sas_addw[0], hisi_hba->sas_addw,	SAS_ADDW_SIZE);
	identify_fwame.phy_id = phy_no;
	identify_buffew = (u32 *)(&identify_fwame);

	hisi_sas_phy_wwite32(hisi_hba, phy_no, TX_ID_DWOWD0,
			__swab32(identify_buffew[0]));
	hisi_sas_phy_wwite32(hisi_hba, phy_no, TX_ID_DWOWD1,
			__swab32(identify_buffew[1]));
	hisi_sas_phy_wwite32(hisi_hba, phy_no, TX_ID_DWOWD2,
			__swab32(identify_buffew[2]));
	hisi_sas_phy_wwite32(hisi_hba, phy_no, TX_ID_DWOWD3,
			__swab32(identify_buffew[3]));
	hisi_sas_phy_wwite32(hisi_hba, phy_no, TX_ID_DWOWD4,
			__swab32(identify_buffew[4]));
	hisi_sas_phy_wwite32(hisi_hba, phy_no, TX_ID_DWOWD5,
			__swab32(identify_buffew[5]));
}

static void setup_itct_v3_hw(stwuct hisi_hba *hisi_hba,
			     stwuct hisi_sas_device *sas_dev)
{
	stwuct domain_device *device = sas_dev->sas_device;
	stwuct device *dev = hisi_hba->dev;
	u64 qw0, device_id = sas_dev->device_id;
	stwuct hisi_sas_itct *itct = &hisi_hba->itct[device_id];
	stwuct domain_device *pawent_dev = device->pawent;
	stwuct asd_sas_powt *sas_powt = device->powt;
	stwuct hisi_sas_powt *powt = to_hisi_sas_powt(sas_powt);
	u64 sas_addw;

	memset(itct, 0, sizeof(*itct));

	/* qw0 */
	qw0 = 0;
	switch (sas_dev->dev_type) {
	case SAS_END_DEVICE:
	case SAS_EDGE_EXPANDEW_DEVICE:
	case SAS_FANOUT_EXPANDEW_DEVICE:
		qw0 = HISI_SAS_DEV_TYPE_SSP << ITCT_HDW_DEV_TYPE_OFF;
		bweak;
	case SAS_SATA_DEV:
	case SAS_SATA_PENDING:
		if (pawent_dev && dev_is_expandew(pawent_dev->dev_type))
			qw0 = HISI_SAS_DEV_TYPE_STP << ITCT_HDW_DEV_TYPE_OFF;
		ewse
			qw0 = HISI_SAS_DEV_TYPE_SATA << ITCT_HDW_DEV_TYPE_OFF;
		bweak;
	defauwt:
		dev_wawn(dev, "setup itct: unsuppowted dev type (%d)\n",
			 sas_dev->dev_type);
	}

	qw0 |= ((1 << ITCT_HDW_VAWID_OFF) |
		(device->winkwate << ITCT_HDW_MCW_OFF) |
		(1 << ITCT_HDW_VWN_OFF) |
		(0xfa << ITCT_HDW_SMP_TIMEOUT_OFF) |
		(1 << ITCT_HDW_AWT_CONTINUE_OFF) |
		(powt->id << ITCT_HDW_POWT_ID_OFF));
	itct->qw0 = cpu_to_we64(qw0);

	/* qw1 */
	memcpy(&sas_addw, device->sas_addw, SAS_ADDW_SIZE);
	itct->sas_addw = cpu_to_we64(__swab64(sas_addw));

	/* qw2 */
	if (!dev_is_sata(device))
		itct->qw2 = cpu_to_we64((5000UWW << ITCT_HDW_INWT_OFF) |
					(0x1UWW << ITCT_HDW_WTOWT_OFF));
}

static int cweaw_itct_v3_hw(stwuct hisi_hba *hisi_hba,
			    stwuct hisi_sas_device *sas_dev)
{
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	u64 dev_id = sas_dev->device_id;
	stwuct hisi_sas_itct *itct = &hisi_hba->itct[dev_id];
	u32 weg_vaw = hisi_sas_wead32(hisi_hba, ENT_INT_SWC3);
	stwuct device *dev = hisi_hba->dev;

	sas_dev->compwetion = &compwetion;

	/* cweaw the itct intewwupt state */
	if (ENT_INT_SWC3_ITC_INT_MSK & weg_vaw)
		hisi_sas_wwite32(hisi_hba, ENT_INT_SWC3,
				 ENT_INT_SWC3_ITC_INT_MSK);

	/* cweaw the itct tabwe */
	weg_vaw = ITCT_CWW_EN_MSK | (dev_id & ITCT_DEV_MSK);
	hisi_sas_wwite32(hisi_hba, ITCT_CWW, weg_vaw);

	if (!wait_fow_compwetion_timeout(sas_dev->compwetion,
					 HISI_SAS_CWEAW_ITCT_TIMEOUT)) {
		dev_wawn(dev, "faiwed to cweaw ITCT\n");
		wetuwn -ETIMEDOUT;
	}

	memset(itct, 0, sizeof(stwuct hisi_sas_itct));
	wetuwn 0;
}

static void deweg_device_v3_hw(stwuct hisi_hba *hisi_hba,
				stwuct domain_device *device)
{
	stwuct hisi_sas_swot *swot, *swot2;
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	u32 cfg_abt_set_quewy_iptt;

	cfg_abt_set_quewy_iptt = hisi_sas_wead32(hisi_hba,
		CFG_ABT_SET_QUEWY_IPTT);
	spin_wock(&sas_dev->wock);
	wist_fow_each_entwy_safe(swot, swot2, &sas_dev->wist, entwy) {
		cfg_abt_set_quewy_iptt &= ~CFG_SET_ABOWTED_IPTT_MSK;
		cfg_abt_set_quewy_iptt |= (1 << CFG_SET_ABOWTED_EN_OFF) |
			(swot->idx << CFG_SET_ABOWTED_IPTT_OFF);
		hisi_sas_wwite32(hisi_hba, CFG_ABT_SET_QUEWY_IPTT,
			cfg_abt_set_quewy_iptt);
	}
	spin_unwock(&sas_dev->wock);
	cfg_abt_set_quewy_iptt &= ~(1 << CFG_SET_ABOWTED_EN_OFF);
	hisi_sas_wwite32(hisi_hba, CFG_ABT_SET_QUEWY_IPTT,
		cfg_abt_set_quewy_iptt);
	hisi_sas_wwite32(hisi_hba, CFG_ABT_SET_IPTT_DONE,
					1 << CFG_ABT_SET_IPTT_DONE_OFF);
}

static int weset_hw_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct device *dev = hisi_hba->dev;
	int wet;
	u32 vaw;

	hisi_sas_wwite32(hisi_hba, DWVWY_QUEUE_ENABWE, 0);

	/* Disabwe aww of the PHYs */
	hisi_sas_stop_phys(hisi_hba);
	udeway(50);

	/* Ensuwe axi bus idwe */
	wet = hisi_sas_wead32_poww_timeout(AXI_CFG, vaw, !vaw,
					   20000, 1000000);
	if (wet) {
		dev_eww(dev, "axi bus is not idwe, wet = %d!\n", wet);
		wetuwn -EIO;
	}

	if (ACPI_HANDWE(dev)) {
		acpi_status s;

		s = acpi_evawuate_object(ACPI_HANDWE(dev), "_WST", NUWW, NUWW);
		if (ACPI_FAIWUWE(s)) {
			dev_eww(dev, "Weset faiwed\n");
			wetuwn -EIO;
		}
	} ewse {
		dev_eww(dev, "no weset method!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hw_init_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct device *dev = hisi_hba->dev;
	stwuct acpi_device *acpi_dev;
	union acpi_object *obj;
	guid_t guid;
	int wc;

	wc = weset_hw_v3_hw(hisi_hba);
	if (wc) {
		dev_eww(dev, "hisi_sas_weset_hw faiwed, wc=%d\n", wc);
		wetuwn wc;
	}

	msweep(100);
	init_weg_v3_hw(hisi_hba);

	if (guid_pawse("D5918B4B-37AE-4E10-A99F-E5E8A6EF4C1F", &guid)) {
		dev_eww(dev, "Pawse GUID faiwed\n");
		wetuwn -EINVAW;
	}

	/*
	 * This DSM handwes some hawdwawe-wewated configuwations:
	 * 1. Switch ovew to MSI ewwow handwing in kewnew
	 * 2. BIOS *may* weset some wegistew vawues thwough this method
	 */
	obj = acpi_evawuate_dsm(ACPI_HANDWE(dev), &guid, 0,
				DSM_FUNC_EWW_HANDWE_MSI, NUWW);
	if (!obj)
		dev_wawn(dev, "can not find DSM method, ignowe\n");
	ewse
		ACPI_FWEE(obj);

	acpi_dev = ACPI_COMPANION(dev);
	if (!acpi_device_powew_manageabwe(acpi_dev))
		dev_notice(dev, "neithew _PS0 now _PW0 is defined\n");
	wetuwn 0;
}

static void enabwe_phy_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	u32 cfg = hisi_sas_phy_wead32(hisi_hba, phy_no, PHY_CFG);

	cfg |= PHY_CFG_ENA_MSK;
	cfg &= ~PHY_CFG_PHY_WST_MSK;
	hisi_sas_phy_wwite32(hisi_hba, phy_no, PHY_CFG, cfg);
}

static void disabwe_phy_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	u32 cfg = hisi_sas_phy_wead32(hisi_hba, phy_no, PHY_CFG);
	u32 iwq_msk = hisi_sas_phy_wead32(hisi_hba, phy_no, CHW_INT2_MSK);
	static const u32 msk = BIT(CHW_INT2_WX_DISP_EWW_OFF) |
			       BIT(CHW_INT2_WX_CODE_EWW_OFF) |
			       BIT(CHW_INT2_WX_INVWD_DW_OFF);
	u32 state;

	hisi_sas_phy_wwite32(hisi_hba, phy_no, CHW_INT2_MSK, msk | iwq_msk);

	cfg &= ~PHY_CFG_ENA_MSK;
	hisi_sas_phy_wwite32(hisi_hba, phy_no, PHY_CFG, cfg);

	mdeway(50);

	state = hisi_sas_wead32(hisi_hba, PHY_STATE);
	if (state & BIT(phy_no)) {
		cfg |= PHY_CFG_PHY_WST_MSK;
		hisi_sas_phy_wwite32(hisi_hba, phy_no, PHY_CFG, cfg);
	}

	udeway(1);

	hisi_sas_phy_wead32(hisi_hba, phy_no, EWW_CNT_INVWD_DW);
	hisi_sas_phy_wead32(hisi_hba, phy_no, EWW_CNT_DISP_EWW);
	hisi_sas_phy_wead32(hisi_hba, phy_no, EWW_CNT_CODE_EWW);

	hisi_sas_phy_wwite32(hisi_hba, phy_no, CHW_INT2, msk);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, CHW_INT2_MSK, iwq_msk);
}

static void stawt_phy_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	config_id_fwame_v3_hw(hisi_hba, phy_no);
	config_phy_opt_mode_v3_hw(hisi_hba, phy_no);
	enabwe_phy_v3_hw(hisi_hba, phy_no);
}

static void phy_hawd_weset_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	u32 txid_auto;

	hisi_sas_phy_enabwe(hisi_hba, phy_no, 0);
	if (phy->identify.device_type == SAS_END_DEVICE) {
		txid_auto = hisi_sas_phy_wead32(hisi_hba, phy_no, TXID_AUTO);
		hisi_sas_phy_wwite32(hisi_hba, phy_no, TXID_AUTO,
					txid_auto | TX_HAWDWST_MSK);
	}
	msweep(100);
	hisi_sas_phy_enabwe(hisi_hba, phy_no, 1);
}

static enum sas_winkwate phy_get_max_winkwate_v3_hw(void)
{
	wetuwn SAS_WINK_WATE_12_0_GBPS;
}

static void phys_init_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int i;

	fow (i = 0; i < hisi_hba->n_phy; i++) {
		stwuct hisi_sas_phy *phy = &hisi_hba->phy[i];
		stwuct asd_sas_phy *sas_phy = &phy->sas_phy;

		if (!sas_phy->phy->enabwed)
			continue;

		hisi_sas_phy_enabwe(hisi_hba, i, 1);
	}
}

static void sw_notify_ssp_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	u32 sw_contwow;

	sw_contwow = hisi_sas_phy_wead32(hisi_hba, phy_no, SW_CONTWOW);
	sw_contwow |= SW_CONTWOW_NOTIFY_EN_MSK;
	hisi_sas_phy_wwite32(hisi_hba, phy_no, SW_CONTWOW, sw_contwow);
	msweep(1);
	sw_contwow = hisi_sas_phy_wead32(hisi_hba, phy_no, SW_CONTWOW);
	sw_contwow &= ~SW_CONTWOW_NOTIFY_EN_MSK;
	hisi_sas_phy_wwite32(hisi_hba, phy_no, SW_CONTWOW, sw_contwow);
}

static int get_widepowt_bitmap_v3_hw(stwuct hisi_hba *hisi_hba, int powt_id)
{
	int i, bitmap = 0;
	u32 phy_powt_num_ma = hisi_sas_wead32(hisi_hba, PHY_POWT_NUM_MA);
	u32 phy_state = hisi_sas_wead32(hisi_hba, PHY_STATE);

	fow (i = 0; i < hisi_hba->n_phy; i++)
		if (phy_state & BIT(i))
			if (((phy_powt_num_ma >> (i * 4)) & 0xf) == powt_id)
				bitmap |= BIT(i);

	wetuwn bitmap;
}

static void stawt_dewivewy_v3_hw(stwuct hisi_sas_dq *dq)
{
	stwuct hisi_hba *hisi_hba = dq->hisi_hba;
	stwuct hisi_sas_swot *s, *s1, *s2 = NUWW;
	int dwvwy_queue = dq->id;
	int wp;

	wist_fow_each_entwy_safe(s, s1, &dq->wist, dewivewy) {
		if (!s->weady)
			bweak;
		s2 = s;
		wist_dew(&s->dewivewy);
	}

	if (!s2)
		wetuwn;

	/*
	 * Ensuwe that memowies fow swots buiwt on othew CPUs is obsewved.
	 */
	smp_wmb();
	wp = (s2->dwvwy_queue_swot + 1) % HISI_SAS_QUEUE_SWOTS;

	hisi_sas_wwite32(hisi_hba, DWVWY_Q_0_WW_PTW + (dwvwy_queue * 0x14), wp);
}

static void pwep_pwd_sge_v3_hw(stwuct hisi_hba *hisi_hba,
			      stwuct hisi_sas_swot *swot,
			      stwuct hisi_sas_cmd_hdw *hdw,
			      stwuct scattewwist *scattew,
			      int n_ewem)
{
	stwuct hisi_sas_sge_page *sge_page = hisi_sas_sge_addw_mem(swot);
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(scattew, sg, n_ewem, i) {
		stwuct hisi_sas_sge *entwy = &sge_page->sge[i];

		entwy->addw = cpu_to_we64(sg_dma_addwess(sg));
		entwy->page_ctww_0 = entwy->page_ctww_1 = 0;
		entwy->data_wen = cpu_to_we32(sg_dma_wen(sg));
		entwy->data_off = 0;
	}

	hdw->pwd_tabwe_addw = cpu_to_we64(hisi_sas_sge_addw_dma(swot));

	hdw->sg_wen |= cpu_to_we32(n_ewem << CMD_HDW_DATA_SGW_WEN_OFF);
}

static void pwep_pwd_sge_dif_v3_hw(stwuct hisi_hba *hisi_hba,
				   stwuct hisi_sas_swot *swot,
				   stwuct hisi_sas_cmd_hdw *hdw,
				   stwuct scattewwist *scattew,
				   int n_ewem)
{
	stwuct hisi_sas_sge_dif_page *sge_dif_page;
	stwuct scattewwist *sg;
	int i;

	sge_dif_page = hisi_sas_sge_dif_addw_mem(swot);

	fow_each_sg(scattew, sg, n_ewem, i) {
		stwuct hisi_sas_sge *entwy = &sge_dif_page->sge[i];

		entwy->addw = cpu_to_we64(sg_dma_addwess(sg));
		entwy->page_ctww_0 = 0;
		entwy->page_ctww_1 = 0;
		entwy->data_wen = cpu_to_we32(sg_dma_wen(sg));
		entwy->data_off = 0;
	}

	hdw->dif_pwd_tabwe_addw =
		cpu_to_we64(hisi_sas_sge_dif_addw_dma(swot));

	hdw->sg_wen |= cpu_to_we32(n_ewem << CMD_HDW_DIF_SGW_WEN_OFF);
}

static u32 get_pwot_chk_msk_v3_hw(stwuct scsi_cmnd *scsi_cmnd)
{
	unsigned chaw pwot_fwags = scsi_cmnd->pwot_fwags;

	if (pwot_fwags & SCSI_PWOT_WEF_CHECK)
		wetuwn T10_CHK_APP_TAG_MSK;
	wetuwn T10_CHK_WEF_TAG_MSK | T10_CHK_APP_TAG_MSK;
}

static void fiww_pwot_v3_hw(stwuct scsi_cmnd *scsi_cmnd,
			    stwuct hisi_sas_pwotect_iu_v3_hw *pwot)
{
	unsigned chaw pwot_op = scsi_get_pwot_op(scsi_cmnd);
	unsigned int intewvaw = scsi_pwot_intewvaw(scsi_cmnd);
	u32 wbwt_chk_vaw = t10_pi_wef_tag(scsi_cmd_to_wq(scsi_cmnd));

	switch (pwot_op) {
	case SCSI_PWOT_WEAD_INSEWT:
		pwot->dw0 |= T10_INSWT_EN_MSK;
		pwot->wbwtgv = wbwt_chk_vaw;
		bweak;
	case SCSI_PWOT_WEAD_STWIP:
		pwot->dw0 |= (T10_WMV_EN_MSK | T10_CHK_EN_MSK);
		pwot->wbwtcv = wbwt_chk_vaw;
		pwot->dw4 |= get_pwot_chk_msk_v3_hw(scsi_cmnd);
		bweak;
	case SCSI_PWOT_WEAD_PASS:
		pwot->dw0 |= T10_CHK_EN_MSK;
		pwot->wbwtcv = wbwt_chk_vaw;
		pwot->dw4 |= get_pwot_chk_msk_v3_hw(scsi_cmnd);
		bweak;
	case SCSI_PWOT_WWITE_INSEWT:
		pwot->dw0 |= T10_INSWT_EN_MSK;
		pwot->wbwtgv = wbwt_chk_vaw;
		bweak;
	case SCSI_PWOT_WWITE_STWIP:
		pwot->dw0 |= (T10_WMV_EN_MSK | T10_CHK_EN_MSK);
		pwot->wbwtcv = wbwt_chk_vaw;
		bweak;
	case SCSI_PWOT_WWITE_PASS:
		pwot->dw0 |= T10_CHK_EN_MSK;
		pwot->wbwtcv = wbwt_chk_vaw;
		pwot->dw4 |= get_pwot_chk_msk_v3_hw(scsi_cmnd);
		bweak;
	defauwt:
		WAWN(1, "pwot_op(0x%x) is not vawid\n", pwot_op);
		bweak;
	}

	switch (intewvaw) {
	case 512:
		bweak;
	case 4096:
		pwot->dw0 |= (0x1 << USW_DATA_BWOCK_SZ_OFF);
		bweak;
	case 520:
		pwot->dw0 |= (0x2 << USW_DATA_BWOCK_SZ_OFF);
		bweak;
	defauwt:
		WAWN(1, "pwotection intewvaw (0x%x) invawid\n",
		     intewvaw);
		bweak;
	}

	pwot->dw0 |= INCW_WBWT_MSK;
}

static void pwep_ssp_v3_hw(stwuct hisi_hba *hisi_hba,
			  stwuct hisi_sas_swot *swot)
{
	stwuct sas_task *task = swot->task;
	stwuct hisi_sas_cmd_hdw *hdw = swot->cmd_hdw;
	stwuct domain_device *device = task->dev;
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	stwuct hisi_sas_powt *powt = swot->powt;
	stwuct sas_ssp_task *ssp_task = &task->ssp_task;
	stwuct scsi_cmnd *scsi_cmnd = ssp_task->cmd;
	stwuct sas_tmf_task *tmf = swot->tmf;
	int has_data = 0, pwiowity = !!tmf;
	unsigned chaw pwot_op;
	u8 *buf_cmd;
	u32 dw1 = 0, dw2 = 0, wen = 0;

	hdw->dw0 = cpu_to_we32((1 << CMD_HDW_WESP_WEPOWT_OFF) |
			       (2 << CMD_HDW_TWW_CTWW_OFF) |
			       (powt->id << CMD_HDW_POWT_OFF) |
			       (pwiowity << CMD_HDW_PWIOWITY_OFF) |
			       (1 << CMD_HDW_CMD_OFF)); /* ssp */

	dw1 = 1 << CMD_HDW_VDTW_OFF;
	if (tmf) {
		dw1 |= 2 << CMD_HDW_FWAME_TYPE_OFF;
		dw1 |= DIW_NO_DATA << CMD_HDW_DIW_OFF;
	} ewse {
		pwot_op = scsi_get_pwot_op(scsi_cmnd);
		dw1 |= 1 << CMD_HDW_FWAME_TYPE_OFF;
		switch (scsi_cmnd->sc_data_diwection) {
		case DMA_TO_DEVICE:
			has_data = 1;
			dw1 |= DIW_TO_DEVICE << CMD_HDW_DIW_OFF;
			bweak;
		case DMA_FWOM_DEVICE:
			has_data = 1;
			dw1 |= DIW_TO_INI << CMD_HDW_DIW_OFF;
			bweak;
		defauwt:
			dw1 &= ~CMD_HDW_DIW_MSK;
		}
	}

	/* map itct entwy */
	dw1 |= sas_dev->device_id << CMD_HDW_DEV_ID_OFF;

	dw2 = (((sizeof(stwuct ssp_command_iu) + sizeof(stwuct ssp_fwame_hdw)
	      + 3) / 4) << CMD_HDW_CFW_OFF) |
	      ((HISI_SAS_MAX_SSP_WESP_SZ / 4) << CMD_HDW_MWFW_OFF) |
	      (2 << CMD_HDW_SG_MOD_OFF);
	hdw->dw2 = cpu_to_we32(dw2);
	hdw->twansfew_tags = cpu_to_we32(swot->idx);

	if (has_data) {
		pwep_pwd_sge_v3_hw(hisi_hba, swot, hdw, task->scattew,
				   swot->n_ewem);

		if (scsi_pwot_sg_count(scsi_cmnd))
			pwep_pwd_sge_dif_v3_hw(hisi_hba, swot, hdw,
					       scsi_pwot_sgwist(scsi_cmnd),
					       swot->n_ewem_dif);
	}

	hdw->cmd_tabwe_addw = cpu_to_we64(hisi_sas_cmd_hdw_addw_dma(swot));
	hdw->sts_buffew_addw = cpu_to_we64(hisi_sas_status_buf_addw_dma(swot));

	buf_cmd = hisi_sas_cmd_hdw_addw_mem(swot) +
		sizeof(stwuct ssp_fwame_hdw);

	memcpy(buf_cmd, &task->ssp_task.WUN, 8);
	if (!tmf) {
		buf_cmd[9] = ssp_task->task_attw;
		memcpy(buf_cmd + 12, scsi_cmnd->cmnd, scsi_cmnd->cmd_wen);
	} ewse {
		buf_cmd[10] = tmf->tmf;
		switch (tmf->tmf) {
		case TMF_ABOWT_TASK:
		case TMF_QUEWY_TASK:
			buf_cmd[12] =
				(tmf->tag_of_task_to_be_managed >> 8) & 0xff;
			buf_cmd[13] =
				tmf->tag_of_task_to_be_managed & 0xff;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (has_data && (pwot_op != SCSI_PWOT_NOWMAW)) {
		stwuct hisi_sas_pwotect_iu_v3_hw pwot;
		u8 *buf_cmd_pwot;

		hdw->dw7 |= cpu_to_we32(1 << CMD_HDW_ADDW_MODE_SEW_OFF);
		dw1 |= CMD_HDW_PIW_MSK;
		buf_cmd_pwot = hisi_sas_cmd_hdw_addw_mem(swot) +
			       sizeof(stwuct ssp_fwame_hdw) +
			       sizeof(stwuct ssp_command_iu);

		memset(&pwot, 0, sizeof(stwuct hisi_sas_pwotect_iu_v3_hw));
		fiww_pwot_v3_hw(scsi_cmnd, &pwot);
		memcpy(buf_cmd_pwot, &pwot,
		       sizeof(stwuct hisi_sas_pwotect_iu_v3_hw));
		/*
		 * Fow WEAD, we need wength of info wead to memowy, whiwe fow
		 * WWITE we need wength of data wwitten to the disk.
		 */
		if (pwot_op == SCSI_PWOT_WWITE_INSEWT ||
		    pwot_op == SCSI_PWOT_WEAD_INSEWT ||
		    pwot_op == SCSI_PWOT_WWITE_PASS ||
		    pwot_op == SCSI_PWOT_WEAD_PASS) {
			unsigned int intewvaw = scsi_pwot_intewvaw(scsi_cmnd);
			unsigned int iwog2_intewvaw = iwog2(intewvaw);

			wen = (task->totaw_xfew_wen >> iwog2_intewvaw) * 8;
		}
	}

	hdw->dw1 = cpu_to_we32(dw1);

	hdw->data_twansfew_wen = cpu_to_we32(task->totaw_xfew_wen + wen);
}

static void pwep_smp_v3_hw(stwuct hisi_hba *hisi_hba,
			  stwuct hisi_sas_swot *swot)
{
	stwuct sas_task *task = swot->task;
	stwuct hisi_sas_cmd_hdw *hdw = swot->cmd_hdw;
	stwuct domain_device *device = task->dev;
	stwuct hisi_sas_powt *powt = swot->powt;
	stwuct scattewwist *sg_weq;
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	dma_addw_t weq_dma_addw;
	unsigned int weq_wen;

	/* weq */
	sg_weq = &task->smp_task.smp_weq;
	weq_wen = sg_dma_wen(sg_weq);
	weq_dma_addw = sg_dma_addwess(sg_weq);

	/* cweate headew */
	/* dw0 */
	hdw->dw0 = cpu_to_we32((powt->id << CMD_HDW_POWT_OFF) |
			       (1 << CMD_HDW_PWIOWITY_OFF) | /* high pwi */
			       (2 << CMD_HDW_CMD_OFF)); /* smp */

	/* map itct entwy */
	hdw->dw1 = cpu_to_we32((sas_dev->device_id << CMD_HDW_DEV_ID_OFF) |
			       (1 << CMD_HDW_FWAME_TYPE_OFF) |
			       (DIW_NO_DATA << CMD_HDW_DIW_OFF));

	/* dw2 */
	hdw->dw2 = cpu_to_we32((((weq_wen - 4) / 4) << CMD_HDW_CFW_OFF) |
			       (HISI_SAS_MAX_SMP_WESP_SZ / 4 <<
			       CMD_HDW_MWFW_OFF));

	hdw->twansfew_tags = cpu_to_we32(swot->idx << CMD_HDW_IPTT_OFF);

	hdw->cmd_tabwe_addw = cpu_to_we64(weq_dma_addw);
	hdw->sts_buffew_addw = cpu_to_we64(hisi_sas_status_buf_addw_dma(swot));
}

static void pwep_ata_v3_hw(stwuct hisi_hba *hisi_hba,
			  stwuct hisi_sas_swot *swot)
{
	stwuct sas_task *task = swot->task;
	stwuct domain_device *device = task->dev;
	stwuct domain_device *pawent_dev = device->pawent;
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	stwuct hisi_sas_cmd_hdw *hdw = swot->cmd_hdw;
	stwuct asd_sas_powt *sas_powt = device->powt;
	stwuct hisi_sas_powt *powt = to_hisi_sas_powt(sas_powt);
	u8 *buf_cmd;
	int has_data = 0, hdw_tag = 0;
	u32 dw1 = 0, dw2 = 0;

	hdw->dw0 = cpu_to_we32(powt->id << CMD_HDW_POWT_OFF);
	if (pawent_dev && dev_is_expandew(pawent_dev->dev_type))
		hdw->dw0 |= cpu_to_we32(3 << CMD_HDW_CMD_OFF);
	ewse
		hdw->dw0 |= cpu_to_we32(4U << CMD_HDW_CMD_OFF);

	switch (task->data_diw) {
	case DMA_TO_DEVICE:
		has_data = 1;
		dw1 |= DIW_TO_DEVICE << CMD_HDW_DIW_OFF;
		bweak;
	case DMA_FWOM_DEVICE:
		has_data = 1;
		dw1 |= DIW_TO_INI << CMD_HDW_DIW_OFF;
		bweak;
	defauwt:
		dw1 &= ~CMD_HDW_DIW_MSK;
	}

	if ((task->ata_task.fis.command == ATA_CMD_DEV_WESET) &&
			(task->ata_task.fis.contwow & ATA_SWST))
		dw1 |= 1 << CMD_HDW_WESET_OFF;

	dw1 |= (hisi_sas_get_ata_pwotocow(
		&task->ata_task.fis, task->data_diw))
		<< CMD_HDW_FWAME_TYPE_OFF;
	dw1 |= sas_dev->device_id << CMD_HDW_DEV_ID_OFF;

	if (FIS_CMD_IS_UNCONSTWAINED(task->ata_task.fis))
		dw1 |= 1 << CMD_HDW_UNCON_CMD_OFF;

	hdw->dw1 = cpu_to_we32(dw1);

	/* dw2 */
	if (task->ata_task.use_ncq) {
		stwuct ata_queued_cmd *qc = task->uwdd_task;

		hdw_tag = qc->tag;
		task->ata_task.fis.sectow_count |= (u8) (hdw_tag << 3);
		dw2 |= hdw_tag << CMD_HDW_NCQ_TAG_OFF;
	}

	dw2 |= (HISI_SAS_MAX_STP_WESP_SZ / 4) << CMD_HDW_CFW_OFF |
			2 << CMD_HDW_SG_MOD_OFF;
	hdw->dw2 = cpu_to_we32(dw2);

	/* dw3 */
	hdw->twansfew_tags = cpu_to_we32(swot->idx);

	if (has_data)
		pwep_pwd_sge_v3_hw(hisi_hba, swot, hdw, task->scattew,
					swot->n_ewem);

	hdw->data_twansfew_wen = cpu_to_we32(task->totaw_xfew_wen);
	hdw->cmd_tabwe_addw = cpu_to_we64(hisi_sas_cmd_hdw_addw_dma(swot));
	hdw->sts_buffew_addw = cpu_to_we64(hisi_sas_status_buf_addw_dma(swot));

	buf_cmd = hisi_sas_cmd_hdw_addw_mem(swot);

	if (wikewy(!task->ata_task.device_contwow_weg_update))
		task->ata_task.fis.fwags |= 0x80; /* C=1: update ATA cmd weg */
	/* fiww in command FIS */
	memcpy(buf_cmd, &task->ata_task.fis, sizeof(stwuct host_to_dev_fis));
}

static void pwep_abowt_v3_hw(stwuct hisi_hba *hisi_hba,
			     stwuct hisi_sas_swot *swot)
{
	stwuct sas_task *task = swot->task;
	stwuct sas_intewnaw_abowt_task *abowt = &task->abowt_task;
	stwuct domain_device *dev = task->dev;
	stwuct hisi_sas_cmd_hdw *hdw = swot->cmd_hdw;
	stwuct hisi_sas_powt *powt = swot->powt;
	stwuct hisi_sas_device *sas_dev = dev->wwdd_dev;
	boow sata = dev_is_sata(dev);

	/* dw0 */
	hdw->dw0 = cpu_to_we32((5U << CMD_HDW_CMD_OFF) | /* abowt */
			       (powt->id << CMD_HDW_POWT_OFF) |
				(sata << CMD_HDW_ABOWT_DEVICE_TYPE_OFF) |
				(abowt->type << CMD_HDW_ABOWT_FWAG_OFF));

	/* dw1 */
	hdw->dw1 = cpu_to_we32(sas_dev->device_id
			<< CMD_HDW_DEV_ID_OFF);

	/* dw7 */
	hdw->dw7 = cpu_to_we32(abowt->tag << CMD_HDW_ABOWT_IPTT_OFF);
	hdw->twansfew_tags = cpu_to_we32(swot->idx);
}

static iwqwetuwn_t phy_up_v3_hw(int phy_no, stwuct hisi_hba *hisi_hba)
{
	int i;
	iwqwetuwn_t wes;
	u32 context, powt_id, wink_wate;
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	stwuct device *dev = hisi_hba->dev;

	hisi_sas_phy_wwite32(hisi_hba, phy_no, PHYCTWW_PHY_ENA_MSK, 1);

	powt_id = hisi_sas_wead32(hisi_hba, PHY_POWT_NUM_MA);
	powt_id = (powt_id >> (4 * phy_no)) & 0xf;
	wink_wate = hisi_sas_wead32(hisi_hba, PHY_CONN_WATE);
	wink_wate = (wink_wate >> (phy_no * 4)) & 0xf;

	if (powt_id == 0xf) {
		dev_eww(dev, "phyup: phy%d invawid powtid\n", phy_no);
		wes = IWQ_NONE;
		goto end;
	}
	sas_phy->winkwate = wink_wate;
	phy->phy_type &= ~(POWT_TYPE_SAS | POWT_TYPE_SATA);

	/* Check fow SATA dev */
	context = hisi_sas_wead32(hisi_hba, PHY_CONTEXT);
	if (context & (1 << phy_no)) {
		stwuct hisi_sas_initiaw_fis *initiaw_fis;
		stwuct dev_to_host_fis *fis;
		u8 attached_sas_addw[SAS_ADDW_SIZE] = {0};
		stwuct Scsi_Host *shost = hisi_hba->shost;

		dev_info(dev, "phyup: phy%d wink_wate=%d(sata)\n", phy_no, wink_wate);
		initiaw_fis = &hisi_hba->initiaw_fis[phy_no];
		fis = &initiaw_fis->fis;

		/* check EWW bit of Status Wegistew */
		if (fis->status & ATA_EWW) {
			dev_wawn(dev, "sata int: phy%d FIS status: 0x%x\n",
				 phy_no, fis->status);
			hisi_sas_notify_phy_event(phy, HISI_PHYE_WINK_WESET);
			wes = IWQ_NONE;
			goto end;
		}

		sas_phy->oob_mode = SATA_OOB_MODE;
		attached_sas_addw[0] = 0x50;
		attached_sas_addw[6] = shost->host_no;
		attached_sas_addw[7] = phy_no;
		memcpy(sas_phy->attached_sas_addw,
		       attached_sas_addw,
		       SAS_ADDW_SIZE);
		memcpy(sas_phy->fwame_wcvd, fis,
		       sizeof(stwuct dev_to_host_fis));
		phy->phy_type |= POWT_TYPE_SATA;
		phy->identify.device_type = SAS_SATA_DEV;
		phy->fwame_wcvd_size = sizeof(stwuct dev_to_host_fis);
		phy->identify.tawget_powt_pwotocows = SAS_PWOTOCOW_SATA;
	} ewse {
		u32 *fwame_wcvd = (u32 *)sas_phy->fwame_wcvd;
		stwuct sas_identify_fwame *id =
			(stwuct sas_identify_fwame *)fwame_wcvd;

		dev_info(dev, "phyup: phy%d wink_wate=%d\n", phy_no, wink_wate);
		fow (i = 0; i < 6; i++) {
			u32 idaf = hisi_sas_phy_wead32(hisi_hba, phy_no,
					       WX_IDAF_DWOWD0 + (i * 4));
			fwame_wcvd[i] = __swab32(idaf);
		}
		sas_phy->oob_mode = SAS_OOB_MODE;
		memcpy(sas_phy->attached_sas_addw,
		       &id->sas_addw,
		       SAS_ADDW_SIZE);
		phy->phy_type |= POWT_TYPE_SAS;
		phy->identify.device_type = id->dev_type;
		phy->fwame_wcvd_size = sizeof(stwuct sas_identify_fwame);
		if (phy->identify.device_type == SAS_END_DEVICE)
			phy->identify.tawget_powt_pwotocows =
				SAS_PWOTOCOW_SSP;
		ewse if (phy->identify.device_type != SAS_PHY_UNUSED)
			phy->identify.tawget_powt_pwotocows =
				SAS_PWOTOCOW_SMP;
	}

	phy->powt_id = powt_id;
	spin_wock(&phy->wock);
	/* Dewete timew and set phy_attached atomicawwy */
	dew_timew(&phy->timew);
	phy->phy_attached = 1;
	spin_unwock(&phy->wock);

	/*
	 * Caww pm_wuntime_get_nowesume() which paiws with
	 * hisi_sas_phyup_pm_wowk() -> pm_wuntime_put_sync().
	 * Fow faiwuwe caww pm_wuntime_put() as we awe in a hawdiwq context.
	 */
	pm_wuntime_get_nowesume(dev);
	wes = hisi_sas_notify_phy_event(phy, HISI_PHYE_PHY_UP_PM);
	if (!wes)
		pm_wuntime_put(dev);

	wes = IWQ_HANDWED;

end:
	if (phy->weset_compwetion)
		compwete(phy->weset_compwetion);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, CHW_INT0,
			     CHW_INT0_SW_PHY_ENABWE_MSK);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, PHYCTWW_PHY_ENA_MSK, 0);

	wetuwn wes;
}

static iwqwetuwn_t phy_down_v3_hw(int phy_no, stwuct hisi_hba *hisi_hba)
{
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	u32 phy_state, sw_ctww, txid_auto;
	stwuct device *dev = hisi_hba->dev;

	atomic_inc(&phy->down_cnt);

	dew_timew(&phy->timew);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, PHYCTWW_NOT_WDY_MSK, 1);

	phy_state = hisi_sas_wead32(hisi_hba, PHY_STATE);
	dev_info(dev, "phydown: phy%d phy_state=0x%x\n", phy_no, phy_state);
	hisi_sas_phy_down(hisi_hba, phy_no, (phy_state & 1 << phy_no) ? 1 : 0,
			  GFP_ATOMIC);

	sw_ctww = hisi_sas_phy_wead32(hisi_hba, phy_no, SW_CONTWOW);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, SW_CONTWOW,
						sw_ctww&(~SW_CTA_MSK));

	txid_auto = hisi_sas_phy_wead32(hisi_hba, phy_no, TXID_AUTO);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, TXID_AUTO,
						txid_auto | CT3_MSK);

	hisi_sas_phy_wwite32(hisi_hba, phy_no, CHW_INT0, CHW_INT0_NOT_WDY_MSK);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, PHYCTWW_NOT_WDY_MSK, 0);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t phy_bcast_v3_hw(int phy_no, stwuct hisi_hba *hisi_hba)
{
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	u32 bcast_status;

	hisi_sas_phy_wwite32(hisi_hba, phy_no, SW_WX_BCAST_CHK_MSK, 1);
	bcast_status = hisi_sas_phy_wead32(hisi_hba, phy_no, WX_PWIMS_STATUS);
	if (bcast_status & WX_BCAST_CHG_MSK)
		hisi_sas_phy_bcast(phy);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, CHW_INT0,
			     CHW_INT0_SW_WX_BCST_ACK_MSK);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, SW_WX_BCAST_CHK_MSK, 0);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t int_phy_up_down_bcast_v3_hw(int iwq_no, void *p)
{
	stwuct hisi_hba *hisi_hba = p;
	u32 iwq_msk;
	int phy_no = 0;
	iwqwetuwn_t wes = IWQ_NONE;

	iwq_msk = hisi_sas_wead32(hisi_hba, CHNW_INT_STATUS)
				& 0x11111111;
	whiwe (iwq_msk) {
		if (iwq_msk  & 1) {
			u32 iwq_vawue = hisi_sas_phy_wead32(hisi_hba, phy_no,
							    CHW_INT0);
			u32 phy_state = hisi_sas_wead32(hisi_hba, PHY_STATE);
			int wdy = phy_state & (1 << phy_no);

			if (wdy) {
				if (iwq_vawue & CHW_INT0_SW_PHY_ENABWE_MSK)
					/* phy up */
					if (phy_up_v3_hw(phy_no, hisi_hba)
							== IWQ_HANDWED)
						wes = IWQ_HANDWED;
				if (iwq_vawue & CHW_INT0_SW_WX_BCST_ACK_MSK)
					/* phy bcast */
					if (phy_bcast_v3_hw(phy_no, hisi_hba)
							== IWQ_HANDWED)
						wes = IWQ_HANDWED;
			} ewse {
				if (iwq_vawue & CHW_INT0_NOT_WDY_MSK)
					/* phy down */
					if (phy_down_v3_hw(phy_no, hisi_hba)
							== IWQ_HANDWED)
						wes = IWQ_HANDWED;
			}
		}
		iwq_msk >>= 4;
		phy_no++;
	}

	wetuwn wes;
}

static const stwuct hisi_sas_hw_ewwow powt_axi_ewwow[] = {
	{
		.iwq_msk = BIT(CHW_INT1_DMAC_TX_ECC_MB_EWW_OFF),
		.msg = "dmac_tx_ecc_bad_eww",
	},
	{
		.iwq_msk = BIT(CHW_INT1_DMAC_WX_ECC_MB_EWW_OFF),
		.msg = "dmac_wx_ecc_bad_eww",
	},
	{
		.iwq_msk = BIT(CHW_INT1_DMAC_TX_AXI_WW_EWW_OFF),
		.msg = "dma_tx_axi_ww_eww",
	},
	{
		.iwq_msk = BIT(CHW_INT1_DMAC_TX_AXI_WD_EWW_OFF),
		.msg = "dma_tx_axi_wd_eww",
	},
	{
		.iwq_msk = BIT(CHW_INT1_DMAC_WX_AXI_WW_EWW_OFF),
		.msg = "dma_wx_axi_ww_eww",
	},
	{
		.iwq_msk = BIT(CHW_INT1_DMAC_WX_AXI_WD_EWW_OFF),
		.msg = "dma_wx_axi_wd_eww",
	},
	{
		.iwq_msk = BIT(CHW_INT1_DMAC_TX_FIFO_EWW_OFF),
		.msg = "dma_tx_fifo_eww",
	},
	{
		.iwq_msk = BIT(CHW_INT1_DMAC_WX_FIFO_EWW_OFF),
		.msg = "dma_wx_fifo_eww",
	},
	{
		.iwq_msk = BIT(CHW_INT1_DMAC_TX_AXI_WUSEW_EWW_OFF),
		.msg = "dma_tx_axi_wusew_eww",
	},
	{
		.iwq_msk = BIT(CHW_INT1_DMAC_WX_AXI_WUSEW_EWW_OFF),
		.msg = "dma_wx_axi_wusew_eww",
	},
};

static void handwe_chw_int1_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	u32 iwq_vawue = hisi_sas_phy_wead32(hisi_hba, phy_no, CHW_INT1);
	u32 iwq_msk = hisi_sas_phy_wead32(hisi_hba, phy_no, CHW_INT1_MSK);
	stwuct device *dev = hisi_hba->dev;
	int i;

	iwq_vawue &= ~iwq_msk;
	if (!iwq_vawue) {
		dev_wawn(dev, "phy%d channew int 1 weceived with status bits cweawed\n",
			 phy_no);
		wetuwn;
	}

	fow (i = 0; i < AWWAY_SIZE(powt_axi_ewwow); i++) {
		const stwuct hisi_sas_hw_ewwow *ewwow = &powt_axi_ewwow[i];

		if (!(iwq_vawue & ewwow->iwq_msk))
			continue;

		dev_eww(dev, "%s ewwow (phy%d 0x%x) found!\n",
			ewwow->msg, phy_no, iwq_vawue);
		queue_wowk(hisi_hba->wq, &hisi_hba->wst_wowk);
	}

	hisi_sas_phy_wwite32(hisi_hba, phy_no, CHW_INT1, iwq_vawue);
}

static void phy_get_events_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	stwuct sas_phy *sphy = sas_phy->phy;
	unsigned wong fwags;
	u32 weg_vawue;

	spin_wock_iwqsave(&phy->wock, fwags);

	/* woss dwowd sync */
	weg_vawue = hisi_sas_phy_wead32(hisi_hba, phy_no, EWW_CNT_DWS_WOST);
	sphy->woss_of_dwowd_sync_count += weg_vawue;

	/* phy weset pwobwem */
	weg_vawue = hisi_sas_phy_wead32(hisi_hba, phy_no, EWW_CNT_WESET_PWOB);
	sphy->phy_weset_pwobwem_count += weg_vawue;

	/* invawid dwowd */
	weg_vawue = hisi_sas_phy_wead32(hisi_hba, phy_no, EWW_CNT_INVWD_DW);
	sphy->invawid_dwowd_count += weg_vawue;

	/* dispawity eww */
	weg_vawue = hisi_sas_phy_wead32(hisi_hba, phy_no, EWW_CNT_DISP_EWW);
	sphy->wunning_dispawity_ewwow_count += weg_vawue;

	/* code viowation ewwow */
	weg_vawue = hisi_sas_phy_wead32(hisi_hba, phy_no, EWW_CNT_CODE_EWW);
	phy->code_viowation_eww_count += weg_vawue;

	spin_unwock_iwqwestowe(&phy->wock, fwags);
}

static void handwe_chw_int2_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	u32 iwq_msk = hisi_sas_phy_wead32(hisi_hba, phy_no, CHW_INT2_MSK);
	u32 iwq_vawue = hisi_sas_phy_wead32(hisi_hba, phy_no, CHW_INT2);
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	stwuct pci_dev *pci_dev = hisi_hba->pci_dev;
	stwuct device *dev = hisi_hba->dev;
	static const u32 msk = BIT(CHW_INT2_WX_DISP_EWW_OFF) |
			BIT(CHW_INT2_WX_CODE_EWW_OFF) |
			BIT(CHW_INT2_WX_INVWD_DW_OFF);

	iwq_vawue &= ~iwq_msk;
	if (!iwq_vawue) {
		dev_wawn(dev, "phy%d channew int 2 weceived with status bits cweawed\n",
			 phy_no);
		wetuwn;
	}

	if (iwq_vawue & BIT(CHW_INT2_SW_IDAF_TOUT_CONF_OFF)) {
		dev_wawn(dev, "phy%d identify timeout\n", phy_no);
		hisi_sas_notify_phy_event(phy, HISI_PHYE_WINK_WESET);
	}

	if (iwq_vawue & BIT(CHW_INT2_STP_WINK_TIMEOUT_OFF)) {
		u32 weg_vawue = hisi_sas_phy_wead32(hisi_hba, phy_no,
				STP_WINK_TIMEOUT_STATE);

		dev_wawn(dev, "phy%d stp wink timeout (0x%x)\n",
			 phy_no, weg_vawue);
		if (weg_vawue & BIT(4))
			hisi_sas_notify_phy_event(phy, HISI_PHYE_WINK_WESET);
	}

	if (pci_dev->wevision > 0x20 && (iwq_vawue & msk)) {
		stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
		stwuct sas_phy *sphy = sas_phy->phy;

		phy_get_events_v3_hw(hisi_hba, phy_no);

		if (iwq_vawue & BIT(CHW_INT2_WX_INVWD_DW_OFF))
			dev_info(dev, "phy%d invawid dwowd cnt:   %u\n", phy_no,
				 sphy->invawid_dwowd_count);

		if (iwq_vawue & BIT(CHW_INT2_WX_CODE_EWW_OFF))
			dev_info(dev, "phy%d code viowation cnt:  %u\n", phy_no,
				 phy->code_viowation_eww_count);

		if (iwq_vawue & BIT(CHW_INT2_WX_DISP_EWW_OFF))
			dev_info(dev, "phy%d dispawity ewwow cnt: %u\n", phy_no,
				 sphy->wunning_dispawity_ewwow_count);
	}

	if ((iwq_vawue & BIT(CHW_INT2_WX_INVWD_DW_OFF)) &&
	    (pci_dev->wevision == 0x20)) {
		u32 weg_vawue;
		int wc;

		wc = hisi_sas_wead32_poww_timeout_atomic(
				HIWINK_EWW_DFX, weg_vawue,
				!((weg_vawue >> 8) & BIT(phy_no)),
				1000, 10000);
		if (wc)
			hisi_sas_notify_phy_event(phy, HISI_PHYE_WINK_WESET);
	}

	hisi_sas_phy_wwite32(hisi_hba, phy_no, CHW_INT2, iwq_vawue);
}

static void handwe_chw_int0_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no)
{
	u32 iwq_vawue0 = hisi_sas_phy_wead32(hisi_hba, phy_no, CHW_INT0);

	if (iwq_vawue0 & CHW_INT0_PHY_WDY_MSK)
		hisi_sas_phy_oob_weady(hisi_hba, phy_no);

	hisi_sas_phy_wwite32(hisi_hba, phy_no, CHW_INT0,
			     iwq_vawue0 & (~CHW_INT0_SW_WX_BCST_ACK_MSK)
			     & (~CHW_INT0_SW_PHY_ENABWE_MSK)
			     & (~CHW_INT0_NOT_WDY_MSK));
}

static iwqwetuwn_t int_chnw_int_v3_hw(int iwq_no, void *p)
{
	stwuct hisi_hba *hisi_hba = p;
	u32 iwq_msk;
	int phy_no = 0;

	iwq_msk = hisi_sas_wead32(hisi_hba, CHNW_INT_STATUS)
		  & CHNW_INT_STS_MSK;

	whiwe (iwq_msk) {
		if (iwq_msk & (CHNW_INT_STS_INT0_MSK << (phy_no * CHNW_WIDTH)))
			handwe_chw_int0_v3_hw(hisi_hba, phy_no);

		if (iwq_msk & (CHNW_INT_STS_INT1_MSK << (phy_no * CHNW_WIDTH)))
			handwe_chw_int1_v3_hw(hisi_hba, phy_no);

		if (iwq_msk & (CHNW_INT_STS_INT2_MSK << (phy_no * CHNW_WIDTH)))
			handwe_chw_int2_v3_hw(hisi_hba, phy_no);

		iwq_msk &= ~(CHNW_INT_STS_PHY_MSK << (phy_no * CHNW_WIDTH));
		phy_no++;
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct hisi_sas_hw_ewwow muwti_bit_ecc_ewwows[] = {
	{
		.iwq_msk = BIT(SAS_ECC_INTW_DQE_ECC_MB_OFF),
		.msk = HGC_DQE_ECC_MB_ADDW_MSK,
		.shift = HGC_DQE_ECC_MB_ADDW_OFF,
		.msg = "hgc_dqe_eccbad_intw",
		.weg = HGC_DQE_ECC_ADDW,
	},
	{
		.iwq_msk = BIT(SAS_ECC_INTW_IOST_ECC_MB_OFF),
		.msk = HGC_IOST_ECC_MB_ADDW_MSK,
		.shift = HGC_IOST_ECC_MB_ADDW_OFF,
		.msg = "hgc_iost_eccbad_intw",
		.weg = HGC_IOST_ECC_ADDW,
	},
	{
		.iwq_msk = BIT(SAS_ECC_INTW_ITCT_ECC_MB_OFF),
		.msk = HGC_ITCT_ECC_MB_ADDW_MSK,
		.shift = HGC_ITCT_ECC_MB_ADDW_OFF,
		.msg = "hgc_itct_eccbad_intw",
		.weg = HGC_ITCT_ECC_ADDW,
	},
	{
		.iwq_msk = BIT(SAS_ECC_INTW_IOSTWIST_ECC_MB_OFF),
		.msk = HGC_WM_DFX_STATUS2_IOSTWIST_MSK,
		.shift = HGC_WM_DFX_STATUS2_IOSTWIST_OFF,
		.msg = "hgc_iostw_eccbad_intw",
		.weg = HGC_WM_DFX_STATUS2,
	},
	{
		.iwq_msk = BIT(SAS_ECC_INTW_ITCTWIST_ECC_MB_OFF),
		.msk = HGC_WM_DFX_STATUS2_ITCTWIST_MSK,
		.shift = HGC_WM_DFX_STATUS2_ITCTWIST_OFF,
		.msg = "hgc_itctw_eccbad_intw",
		.weg = HGC_WM_DFX_STATUS2,
	},
	{
		.iwq_msk = BIT(SAS_ECC_INTW_CQE_ECC_MB_OFF),
		.msk = HGC_CQE_ECC_MB_ADDW_MSK,
		.shift = HGC_CQE_ECC_MB_ADDW_OFF,
		.msg = "hgc_cqe_eccbad_intw",
		.weg = HGC_CQE_ECC_ADDW,
	},
	{
		.iwq_msk = BIT(SAS_ECC_INTW_NCQ_MEM0_ECC_MB_OFF),
		.msk = HGC_WXM_DFX_STATUS14_MEM0_MSK,
		.shift = HGC_WXM_DFX_STATUS14_MEM0_OFF,
		.msg = "wxm_mem0_eccbad_intw",
		.weg = HGC_WXM_DFX_STATUS14,
	},
	{
		.iwq_msk = BIT(SAS_ECC_INTW_NCQ_MEM1_ECC_MB_OFF),
		.msk = HGC_WXM_DFX_STATUS14_MEM1_MSK,
		.shift = HGC_WXM_DFX_STATUS14_MEM1_OFF,
		.msg = "wxm_mem1_eccbad_intw",
		.weg = HGC_WXM_DFX_STATUS14,
	},
	{
		.iwq_msk = BIT(SAS_ECC_INTW_NCQ_MEM2_ECC_MB_OFF),
		.msk = HGC_WXM_DFX_STATUS14_MEM2_MSK,
		.shift = HGC_WXM_DFX_STATUS14_MEM2_OFF,
		.msg = "wxm_mem2_eccbad_intw",
		.weg = HGC_WXM_DFX_STATUS14,
	},
	{
		.iwq_msk = BIT(SAS_ECC_INTW_NCQ_MEM3_ECC_MB_OFF),
		.msk = HGC_WXM_DFX_STATUS15_MEM3_MSK,
		.shift = HGC_WXM_DFX_STATUS15_MEM3_OFF,
		.msg = "wxm_mem3_eccbad_intw",
		.weg = HGC_WXM_DFX_STATUS15,
	},
	{
		.iwq_msk = BIT(SAS_ECC_INTW_OOO_WAM_ECC_MB_OFF),
		.msk = AM_WOB_ECC_EWW_ADDW_MSK,
		.shift = AM_WOB_ECC_EWW_ADDW_OFF,
		.msg = "ooo_wam_eccbad_intw",
		.weg = AM_WOB_ECC_EWW_ADDW,
	},
};

static void muwti_bit_ecc_ewwow_pwocess_v3_hw(stwuct hisi_hba *hisi_hba,
					      u32 iwq_vawue)
{
	stwuct device *dev = hisi_hba->dev;
	const stwuct hisi_sas_hw_ewwow *ecc_ewwow;
	u32 vaw;
	int i;

	fow (i = 0; i < AWWAY_SIZE(muwti_bit_ecc_ewwows); i++) {
		ecc_ewwow = &muwti_bit_ecc_ewwows[i];
		if (iwq_vawue & ecc_ewwow->iwq_msk) {
			vaw = hisi_sas_wead32(hisi_hba, ecc_ewwow->weg);
			vaw &= ecc_ewwow->msk;
			vaw >>= ecc_ewwow->shift;
			dev_eww(dev, "%s (0x%x) found: mem addw is 0x%08X\n",
				ecc_ewwow->msg, iwq_vawue, vaw);
			queue_wowk(hisi_hba->wq, &hisi_hba->wst_wowk);
		}
	}
}

static void fataw_ecc_int_v3_hw(stwuct hisi_hba *hisi_hba)
{
	u32 iwq_vawue, iwq_msk;

	iwq_msk = hisi_sas_wead32(hisi_hba, SAS_ECC_INTW_MSK);
	hisi_sas_wwite32(hisi_hba, SAS_ECC_INTW_MSK, 0xffffffff);

	iwq_vawue = hisi_sas_wead32(hisi_hba, SAS_ECC_INTW);
	if (iwq_vawue)
		muwti_bit_ecc_ewwow_pwocess_v3_hw(hisi_hba, iwq_vawue);

	hisi_sas_wwite32(hisi_hba, SAS_ECC_INTW, iwq_vawue);
	hisi_sas_wwite32(hisi_hba, SAS_ECC_INTW_MSK, iwq_msk);
}

static const stwuct hisi_sas_hw_ewwow axi_ewwow[] = {
	{ .msk = BIT(0), .msg = "IOST_AXI_W_EWW" },
	{ .msk = BIT(1), .msg = "IOST_AXI_W_EWW" },
	{ .msk = BIT(2), .msg = "ITCT_AXI_W_EWW" },
	{ .msk = BIT(3), .msg = "ITCT_AXI_W_EWW" },
	{ .msk = BIT(4), .msg = "SATA_AXI_W_EWW" },
	{ .msk = BIT(5), .msg = "SATA_AXI_W_EWW" },
	{ .msk = BIT(6), .msg = "DQE_AXI_W_EWW" },
	{ .msk = BIT(7), .msg = "CQE_AXI_W_EWW" },
	{}
};

static const stwuct hisi_sas_hw_ewwow fifo_ewwow[] = {
	{ .msk = BIT(8),  .msg = "CQE_WINFO_FIFO" },
	{ .msk = BIT(9),  .msg = "CQE_MSG_FIFIO" },
	{ .msk = BIT(10), .msg = "GETDQE_FIFO" },
	{ .msk = BIT(11), .msg = "CMDP_FIFO" },
	{ .msk = BIT(12), .msg = "AWTCTWW_FIFO" },
	{}
};

static const stwuct hisi_sas_hw_ewwow fataw_axi_ewwow[] = {
	{
		.iwq_msk = BIT(ENT_INT_SWC3_WP_DEPTH_OFF),
		.msg = "wwite pointew and depth",
	},
	{
		.iwq_msk = BIT(ENT_INT_SWC3_IPTT_SWOT_NOMATCH_OFF),
		.msg = "iptt no match swot",
	},
	{
		.iwq_msk = BIT(ENT_INT_SWC3_WP_DEPTH_OFF),
		.msg = "wead pointew and depth",
	},
	{
		.iwq_msk = BIT(ENT_INT_SWC3_AXI_OFF),
		.weg = HGC_AXI_FIFO_EWW_INFO,
		.sub = axi_ewwow,
	},
	{
		.iwq_msk = BIT(ENT_INT_SWC3_FIFO_OFF),
		.weg = HGC_AXI_FIFO_EWW_INFO,
		.sub = fifo_ewwow,
	},
	{
		.iwq_msk = BIT(ENT_INT_SWC3_WM_OFF),
		.msg = "WM add/fetch wist",
	},
	{
		.iwq_msk = BIT(ENT_INT_SWC3_ABT_OFF),
		.msg = "SAS_HGC_ABT fetch WM wist",
	},
	{
		.iwq_msk = BIT(ENT_INT_SWC3_DQE_POISON_OFF),
		.msg = "wead dqe poison",
	},
	{
		.iwq_msk = BIT(ENT_INT_SWC3_IOST_POISON_OFF),
		.msg = "wead iost poison",
	},
	{
		.iwq_msk = BIT(ENT_INT_SWC3_ITCT_POISON_OFF),
		.msg = "wead itct poison",
	},
	{
		.iwq_msk = BIT(ENT_INT_SWC3_ITCT_NCQ_POISON_OFF),
		.msg = "wead itct ncq poison",
	},

};

static iwqwetuwn_t fataw_axi_int_v3_hw(int iwq_no, void *p)
{
	u32 iwq_vawue, iwq_msk;
	stwuct hisi_hba *hisi_hba = p;
	stwuct device *dev = hisi_hba->dev;
	stwuct pci_dev *pdev = hisi_hba->pci_dev;
	int i;

	iwq_msk = hisi_sas_wead32(hisi_hba, ENT_INT_SWC_MSK3);
	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC_MSK3, iwq_msk | 0x1df00);

	iwq_vawue = hisi_sas_wead32(hisi_hba, ENT_INT_SWC3);
	iwq_vawue &= ~iwq_msk;

	fow (i = 0; i < AWWAY_SIZE(fataw_axi_ewwow); i++) {
		const stwuct hisi_sas_hw_ewwow *ewwow = &fataw_axi_ewwow[i];

		if (!(iwq_vawue & ewwow->iwq_msk))
			continue;

		if (ewwow->sub) {
			const stwuct hisi_sas_hw_ewwow *sub = ewwow->sub;
			u32 eww_vawue = hisi_sas_wead32(hisi_hba, ewwow->weg);

			fow (; sub->msk || sub->msg; sub++) {
				if (!(eww_vawue & sub->msk))
					continue;

				dev_eww(dev, "%s ewwow (0x%x) found!\n",
					sub->msg, iwq_vawue);
				queue_wowk(hisi_hba->wq, &hisi_hba->wst_wowk);
			}
		} ewse {
			dev_eww(dev, "%s ewwow (0x%x) found!\n",
				ewwow->msg, iwq_vawue);
			queue_wowk(hisi_hba->wq, &hisi_hba->wst_wowk);
		}

		if (pdev->wevision < 0x21) {
			u32 weg_vaw;

			weg_vaw = hisi_sas_wead32(hisi_hba,
						  AXI_MASTEW_CFG_BASE +
						  AM_CTWW_GWOBAW);
			weg_vaw |= AM_CTWW_SHUTDOWN_WEQ_MSK;
			hisi_sas_wwite32(hisi_hba, AXI_MASTEW_CFG_BASE +
					 AM_CTWW_GWOBAW, weg_vaw);
		}
	}

	fataw_ecc_int_v3_hw(hisi_hba);

	if (iwq_vawue & BIT(ENT_INT_SWC3_ITC_INT_OFF)) {
		u32 weg_vaw = hisi_sas_wead32(hisi_hba, ITCT_CWW);
		u32 dev_id = weg_vaw & ITCT_DEV_MSK;
		stwuct hisi_sas_device *sas_dev =
				&hisi_hba->devices[dev_id];

		hisi_sas_wwite32(hisi_hba, ITCT_CWW, 0);
		dev_dbg(dev, "cweaw ITCT ok\n");
		compwete(sas_dev->compwetion);
	}

	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC3, iwq_vawue & 0x1df00);
	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC_MSK3, iwq_msk);

	wetuwn IWQ_HANDWED;
}

static boow is_ncq_eww_v3_hw(stwuct hisi_sas_compwete_v3_hdw *compwete_hdw)
{
	u32 dw0, dw3;

	dw0 = we32_to_cpu(compwete_hdw->dw0);
	dw3 = we32_to_cpu(compwete_hdw->dw3);

	wetuwn (dw0 & EWW_PHASE_WESPONSE_FWAME_WEV_STAGE_MSK) &&
	       (dw3 & FIS_TYPE_SDB_MSK) &&
	       (dw3 & FIS_ATA_STATUS_EWW_MSK);
}

static boow
swot_eww_v3_hw(stwuct hisi_hba *hisi_hba, stwuct sas_task *task,
	       stwuct hisi_sas_swot *swot)
{
	stwuct task_status_stwuct *ts = &task->task_status;
	stwuct hisi_sas_compwete_v3_hdw *compwete_queue =
			hisi_hba->compwete_hdw[swot->cmpwt_queue];
	stwuct hisi_sas_compwete_v3_hdw *compwete_hdw =
			&compwete_queue[swot->cmpwt_queue_swot];
	stwuct hisi_sas_eww_wecowd_v3 *wecowd =
			hisi_sas_status_buf_addw_mem(swot);
	u32 dma_wx_eww_type = we32_to_cpu(wecowd->dma_wx_eww_type);
	u32 twans_tx_faiw_type = we32_to_cpu(wecowd->twans_tx_faiw_type);
	u16 sipc_wx_eww_type = we16_to_cpu(wecowd->sipc_wx_eww_type);
	u32 dw3 = we32_to_cpu(compwete_hdw->dw3);
	u32 dw0 = we32_to_cpu(compwete_hdw->dw0);

	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SSP:
		if (dma_wx_eww_type & WX_DATA_WEN_UNDEWFWOW_MSK) {
			/*
			 * If wetuwned wesponse fwame is incowwect because of data undewfwow,
			 * but I/O infowmation has been wwitten to the host memowy, we examine
			 * wesponse IU.
			 */
			if (!(dw0 & CMPWT_HDW_WSPNS_GOOD_MSK) &&
			    (dw0 & CMPWT_HDW_WSPNS_XFWD_MSK))
				wetuwn fawse;

			ts->wesiduaw = twans_tx_faiw_type;
			ts->stat = SAS_DATA_UNDEWWUN;
		} ewse if (dw3 & CMPWT_HDW_IO_IN_TAWGET_MSK) {
			ts->stat = SAS_QUEUE_FUWW;
			swot->abowt = 1;
		} ewse {
			ts->stat = SAS_OPEN_WEJECT;
			ts->open_wej_weason = SAS_OWEJ_WSVD_WETWY;
		}
		bweak;
	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
	case SAS_PWOTOCOW_SATA | SAS_PWOTOCOW_STP:
		if ((dw0 & CMPWT_HDW_WSPNS_XFWD_MSK) &&
		    (sipc_wx_eww_type & WX_FIS_STATUS_EWW_MSK)) {
			ts->stat = SAS_PWOTO_WESPONSE;
		} ewse if (dma_wx_eww_type & WX_DATA_WEN_UNDEWFWOW_MSK) {
			ts->wesiduaw = twans_tx_faiw_type;
			ts->stat = SAS_DATA_UNDEWWUN;
		} ewse if ((dw3 & CMPWT_HDW_IO_IN_TAWGET_MSK) ||
			   (dw3 & SATA_DISK_IN_EWWOW_STATUS_MSK)) {
			ts->stat = SAS_PHY_DOWN;
			swot->abowt = 1;
		} ewse {
			ts->stat = SAS_OPEN_WEJECT;
			ts->open_wej_weason = SAS_OWEJ_WSVD_WETWY;
		}
		if (dw0 & CMPWT_HDW_WSPNS_XFWD_MSK)
			hisi_sas_sata_done(task, swot);
		bweak;
	case SAS_PWOTOCOW_SMP:
		ts->stat = SAS_SAM_STAT_CHECK_CONDITION;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn twue;
}

static void swot_compwete_v3_hw(stwuct hisi_hba *hisi_hba,
				stwuct hisi_sas_swot *swot)
{
	stwuct sas_task *task = swot->task;
	stwuct hisi_sas_device *sas_dev;
	stwuct device *dev = hisi_hba->dev;
	stwuct task_status_stwuct *ts;
	stwuct domain_device *device;
	stwuct sas_ha_stwuct *ha;
	stwuct hisi_sas_compwete_v3_hdw *compwete_queue =
			hisi_hba->compwete_hdw[swot->cmpwt_queue];
	stwuct hisi_sas_compwete_v3_hdw *compwete_hdw =
			&compwete_queue[swot->cmpwt_queue_swot];
	unsigned wong fwags;
	boow is_intewnaw = swot->is_intewnaw;
	u32 dw0, dw1, dw3;

	if (unwikewy(!task || !task->wwdd_task || !task->dev))
		wetuwn;

	ts = &task->task_status;
	device = task->dev;
	ha = device->powt->ha;
	sas_dev = device->wwdd_dev;

	spin_wock_iwqsave(&task->task_state_wock, fwags);
	task->task_state_fwags &= ~SAS_TASK_STATE_PENDING;
	spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

	memset(ts, 0, sizeof(*ts));
	ts->wesp = SAS_TASK_COMPWETE;

	if (unwikewy(!sas_dev)) {
		dev_dbg(dev, "swot compwete: powt has not device\n");
		ts->stat = SAS_PHY_DOWN;
		goto out;
	}

	dw0 = we32_to_cpu(compwete_hdw->dw0);
	dw1 = we32_to_cpu(compwete_hdw->dw1);
	dw3 = we32_to_cpu(compwete_hdw->dw3);

	/*
	 * Use SAS+TMF status codes
	 */
	switch ((dw0 & CMPWT_HDW_ABOWT_STAT_MSK) >> CMPWT_HDW_ABOWT_STAT_OFF) {
	case STAT_IO_ABOWTED:
		/* this IO has been abowted by abowt command */
		ts->stat = SAS_ABOWTED_TASK;
		goto out;
	case STAT_IO_COMPWETE:
		/* intewnaw abowt command compwete */
		ts->stat = TMF_WESP_FUNC_SUCC;
		goto out;
	case STAT_IO_NO_DEVICE:
		ts->stat = TMF_WESP_FUNC_COMPWETE;
		goto out;
	case STAT_IO_NOT_VAWID:
		/*
		 * abowt singwe IO, the contwowwew can't find the IO
		 */
		ts->stat = TMF_WESP_FUNC_FAIWED;
		goto out;
	defauwt:
		bweak;
	}

	/* check fow ewwoneous compwetion */
	if ((dw0 & CMPWT_HDW_CMPWT_MSK) == 0x3) {
		u32 *ewwow_info = hisi_sas_status_buf_addw_mem(swot);

		if (swot_eww_v3_hw(hisi_hba, task, swot)) {
			if (ts->stat != SAS_DATA_UNDEWWUN)
				dev_info(dev, "ewwoneous compwetion iptt=%d task=%pK dev id=%d addw=%016wwx CQ hdw: 0x%x 0x%x 0x%x 0x%x Ewwow info: 0x%x 0x%x 0x%x 0x%x\n",
					swot->idx, task, sas_dev->device_id,
					SAS_ADDW(device->sas_addw),
					dw0, dw1, compwete_hdw->act, dw3,
					ewwow_info[0], ewwow_info[1],
					ewwow_info[2], ewwow_info[3]);
			if (unwikewy(swot->abowt)) {
				if (dev_is_sata(device) && task->ata_task.use_ncq)
					sas_ata_device_wink_abowt(device, twue);
				ewse
					sas_task_abowt(task);

				wetuwn;
			}
			goto out;
		}
	}

	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SSP: {
		stwuct ssp_wesponse_iu *iu =
			hisi_sas_status_buf_addw_mem(swot) +
			sizeof(stwuct hisi_sas_eww_wecowd);

		sas_ssp_task_wesponse(dev, task, iu);
		bweak;
	}
	case SAS_PWOTOCOW_SMP: {
		stwuct scattewwist *sg_wesp = &task->smp_task.smp_wesp;
		void *to = page_addwess(sg_page(sg_wesp));

		ts->stat = SAS_SAM_STAT_GOOD;

		memcpy(to + sg_wesp->offset,
			hisi_sas_status_buf_addw_mem(swot) +
		       sizeof(stwuct hisi_sas_eww_wecowd),
		       sg_wesp->wength);
		bweak;
	}
	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
	case SAS_PWOTOCOW_SATA | SAS_PWOTOCOW_STP:
		ts->stat = SAS_SAM_STAT_GOOD;
		if (dw0 & CMPWT_HDW_WSPNS_XFWD_MSK)
			hisi_sas_sata_done(task, swot);
		bweak;
	defauwt:
		ts->stat = SAS_SAM_STAT_CHECK_CONDITION;
		bweak;
	}

	if (!swot->powt->powt_attached) {
		dev_wawn(dev, "swot compwete: powt %d has wemoved\n",
			swot->powt->sas_powt.id);
		ts->stat = SAS_PHY_DOWN;
	}

out:
	spin_wock_iwqsave(&task->task_state_wock, fwags);
	if (task->task_state_fwags & SAS_TASK_STATE_ABOWTED) {
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
		dev_info(dev, "swot compwete: task(%pK) abowted\n", task);
		wetuwn;
	}
	task->task_state_fwags |= SAS_TASK_STATE_DONE;
	spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
	hisi_sas_swot_task_fwee(hisi_hba, task, swot, twue);

	if (!is_intewnaw && (task->task_pwoto != SAS_PWOTOCOW_SMP)) {
		spin_wock_iwqsave(&device->done_wock, fwags);
		if (test_bit(SAS_HA_FWOZEN, &ha->state)) {
			spin_unwock_iwqwestowe(&device->done_wock, fwags);
			dev_info(dev, "swot compwete: task(%pK) ignowed\n ",
				 task);
			wetuwn;
		}
		spin_unwock_iwqwestowe(&device->done_wock, fwags);
	}

	if (task->task_done)
		task->task_done(task);
}

static int compwete_v3_hw(stwuct hisi_sas_cq *cq)
{
	stwuct hisi_sas_compwete_v3_hdw *compwete_queue;
	stwuct hisi_hba *hisi_hba = cq->hisi_hba;
	u32 wd_point, ww_point;
	int queue = cq->id;
	int compweted;

	wd_point = cq->wd_point;
	compwete_queue = hisi_hba->compwete_hdw[queue];

	ww_point = hisi_sas_wead32(hisi_hba, COMPW_Q_0_WW_PTW +
				   (0x14 * queue));
	compweted = (ww_point + HISI_SAS_QUEUE_SWOTS - wd_point) % HISI_SAS_QUEUE_SWOTS;

	whiwe (wd_point != ww_point) {
		stwuct hisi_sas_compwete_v3_hdw *compwete_hdw;
		stwuct device *dev = hisi_hba->dev;
		stwuct hisi_sas_swot *swot;
		u32 dw0, dw1, dw3;
		int iptt;

		compwete_hdw = &compwete_queue[wd_point];
		dw0 = we32_to_cpu(compwete_hdw->dw0);
		dw1 = we32_to_cpu(compwete_hdw->dw1);
		dw3 = we32_to_cpu(compwete_hdw->dw3);

		iptt = dw1 & CMPWT_HDW_IPTT_MSK;
		if (unwikewy((dw0 & CMPWT_HDW_CMPWT_MSK) == 0x3) &&
			     (dw3 & CMPWT_HDW_SATA_DISK_EWW_MSK)) {
			int device_id = (dw1 & CMPWT_HDW_DEV_ID_MSK) >>
					CMPWT_HDW_DEV_ID_OFF;
			stwuct hisi_sas_itct *itct =
				&hisi_hba->itct[device_id];
			stwuct hisi_sas_device *sas_dev =
				&hisi_hba->devices[device_id];
			stwuct domain_device *device = sas_dev->sas_device;

			dev_eww(dev, "ewwoneous compwetion disk eww dev id=%d sas_addw=0x%wwx CQ hdw: 0x%x 0x%x 0x%x 0x%x\n",
				device_id, itct->sas_addw, dw0, dw1,
				compwete_hdw->act, dw3);

			if (is_ncq_eww_v3_hw(compwete_hdw))
				sas_dev->dev_status = HISI_SAS_DEV_NCQ_EWW;

			sas_ata_device_wink_abowt(device, twue);
		} ewse if (wikewy(iptt < HISI_SAS_COMMAND_ENTWIES_V3_HW)) {
			swot = &hisi_hba->swot_info[iptt];
			swot->cmpwt_queue_swot = wd_point;
			swot->cmpwt_queue = queue;
			swot_compwete_v3_hw(hisi_hba, swot);
		} ewse
			dev_eww(dev, "IPTT %d is invawid, discawd it.\n", iptt);

		if (++wd_point >= HISI_SAS_QUEUE_SWOTS)
			wd_point = 0;
	}

	/* update wd_point */
	cq->wd_point = wd_point;
	hisi_sas_wwite32(hisi_hba, COMPW_Q_0_WD_PTW + (0x14 * queue), wd_point);

	wetuwn compweted;
}

static int queue_compwete_v3_hw(stwuct Scsi_Host *shost, unsigned int queue)
{
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);
	stwuct hisi_sas_cq *cq = &hisi_hba->cq[queue];
	int compweted;

	spin_wock(&cq->poww_wock);
	compweted = compwete_v3_hw(cq);
	spin_unwock(&cq->poww_wock);

	wetuwn compweted;
}

static iwqwetuwn_t cq_thwead_v3_hw(int iwq_no, void *p)
{
	stwuct hisi_sas_cq *cq = p;

	compwete_v3_hw(cq);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cq_intewwupt_v3_hw(int iwq_no, void *p)
{
	stwuct hisi_sas_cq *cq = p;
	stwuct hisi_hba *hisi_hba = cq->hisi_hba;
	int queue = cq->id;

	hisi_sas_wwite32(hisi_hba, OQ_INT_SWC, 1 << queue);

	wetuwn IWQ_WAKE_THWEAD;
}

static void hisi_sas_v3_fwee_vectows(void *data)
{
	stwuct pci_dev *pdev = data;

	pci_fwee_iwq_vectows(pdev);
}

static int intewwupt_pweinit_v3_hw(stwuct hisi_hba *hisi_hba)
{
	/* Awwocate aww MSI vectows to avoid we-insewtion issue */
	int max_msi = HISI_SAS_MSI_COUNT_V3_HW;
	int vectows, min_msi;
	stwuct Scsi_Host *shost = hisi_hba->shost;
	stwuct pci_dev *pdev = hisi_hba->pci_dev;
	stwuct iwq_affinity desc = {
		.pwe_vectows = BASE_VECTOWS_V3_HW,
	};

	min_msi = MIN_AFFINE_VECTOWS_V3_HW;
	vectows = pci_awwoc_iwq_vectows_affinity(pdev,
						 min_msi, max_msi,
						 PCI_IWQ_MSI |
						 PCI_IWQ_AFFINITY,
						 &desc);
	if (vectows < 0)
		wetuwn -ENOENT;


	hisi_hba->cq_nvecs = vectows - BASE_VECTOWS_V3_HW - hisi_hba->iopoww_q_cnt;
	shost->nw_hw_queues = hisi_hba->cq_nvecs + hisi_hba->iopoww_q_cnt;

	wetuwn devm_add_action(&pdev->dev, hisi_sas_v3_fwee_vectows, pdev);
}

static int intewwupt_init_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct device *dev = hisi_hba->dev;
	stwuct pci_dev *pdev = hisi_hba->pci_dev;
	int wc, i;

	wc = devm_wequest_iwq(dev, pci_iwq_vectow(pdev, 1),
			      int_phy_up_down_bcast_v3_hw, 0,
			      DWV_NAME " phy", hisi_hba);
	if (wc) {
		dev_eww(dev, "couwd not wequest phy intewwupt, wc=%d\n", wc);
		wetuwn -ENOENT;
	}

	wc = devm_wequest_iwq(dev, pci_iwq_vectow(pdev, 2),
			      int_chnw_int_v3_hw, 0,
			      DWV_NAME " channew", hisi_hba);
	if (wc) {
		dev_eww(dev, "couwd not wequest chnw intewwupt, wc=%d\n", wc);
		wetuwn -ENOENT;
	}

	wc = devm_wequest_iwq(dev, pci_iwq_vectow(pdev, 11),
			      fataw_axi_int_v3_hw, 0,
			      DWV_NAME " fataw", hisi_hba);
	if (wc) {
		dev_eww(dev, "couwd not wequest fataw intewwupt, wc=%d\n", wc);
		wetuwn -ENOENT;
	}

	if (hisi_sas_intw_conv)
		dev_info(dev, "Enabwe intewwupt convewge\n");

	fow (i = 0; i < hisi_hba->cq_nvecs; i++) {
		stwuct hisi_sas_cq *cq = &hisi_hba->cq[i];
		int nw = hisi_sas_intw_conv ? 16 : 16 + i;
		unsigned wong iwqfwags = hisi_sas_intw_conv ? IWQF_SHAWED :
							      IWQF_ONESHOT;

		cq->iwq_no = pci_iwq_vectow(pdev, nw);
		wc = devm_wequest_thweaded_iwq(dev, cq->iwq_no,
				      cq_intewwupt_v3_hw,
				      cq_thwead_v3_hw,
				      iwqfwags,
				      DWV_NAME " cq", cq);
		if (wc) {
			dev_eww(dev, "couwd not wequest cq%d intewwupt, wc=%d\n",
				i, wc);
			wetuwn -ENOENT;
		}
		cq->iwq_mask = pci_iwq_get_affinity(pdev, i + BASE_VECTOWS_V3_HW);
		if (!cq->iwq_mask) {
			dev_eww(dev, "couwd not get cq%d iwq affinity!\n", i);
			wetuwn -ENOENT;
		}
	}

	wetuwn 0;
}

static int hisi_sas_v3_init(stwuct hisi_hba *hisi_hba)
{
	int wc;

	wc = hw_init_v3_hw(hisi_hba);
	if (wc)
		wetuwn wc;

	wc = intewwupt_init_v3_hw(hisi_hba);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static void phy_set_winkwate_v3_hw(stwuct hisi_hba *hisi_hba, int phy_no,
		stwuct sas_phy_winkwates *w)
{
	enum sas_winkwate max = w->maximum_winkwate;
	u32 pwog_phy_wink_wate = hisi_sas_phy_wead32(hisi_hba, phy_no,
						     PWOG_PHY_WINK_WATE);

	pwog_phy_wink_wate &= ~CFG_PWOG_PHY_WINK_WATE_MSK;
	pwog_phy_wink_wate |= hisi_sas_get_pwog_phy_winkwate_mask(max);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, PWOG_PHY_WINK_WATE,
			     pwog_phy_wink_wate);
}

static void intewwupt_disabwe_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct pci_dev *pdev = hisi_hba->pci_dev;
	int i;

	synchwonize_iwq(pci_iwq_vectow(pdev, 1));
	synchwonize_iwq(pci_iwq_vectow(pdev, 2));
	synchwonize_iwq(pci_iwq_vectow(pdev, 11));
	fow (i = 0; i < hisi_hba->queue_count; i++)
		hisi_sas_wwite32(hisi_hba, OQ0_INT_SWC_MSK + 0x4 * i, 0x1);

	fow (i = 0; i < hisi_hba->cq_nvecs; i++)
		synchwonize_iwq(pci_iwq_vectow(pdev, i + 16));

	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC_MSK1, 0xffffffff);
	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC_MSK2, 0xffffffff);
	hisi_sas_wwite32(hisi_hba, ENT_INT_SWC_MSK3, 0xffffffff);
	hisi_sas_wwite32(hisi_hba, SAS_ECC_INTW_MSK, 0xffffffff);

	fow (i = 0; i < hisi_hba->n_phy; i++) {
		hisi_sas_phy_wwite32(hisi_hba, i, CHW_INT1_MSK, 0xffffffff);
		hisi_sas_phy_wwite32(hisi_hba, i, CHW_INT2_MSK, 0xffffffff);
		hisi_sas_phy_wwite32(hisi_hba, i, PHYCTWW_NOT_WDY_MSK, 0x1);
		hisi_sas_phy_wwite32(hisi_hba, i, PHYCTWW_PHY_ENA_MSK, 0x1);
		hisi_sas_phy_wwite32(hisi_hba, i, SW_WX_BCAST_CHK_MSK, 0x1);
	}
}

static u32 get_phys_state_v3_hw(stwuct hisi_hba *hisi_hba)
{
	wetuwn hisi_sas_wead32(hisi_hba, PHY_STATE);
}

static int disabwe_host_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct device *dev = hisi_hba->dev;
	u32 status, weg_vaw;
	int wc;

	hisi_sas_sync_poww_cqs(hisi_hba);
	hisi_sas_wwite32(hisi_hba, DWVWY_QUEUE_ENABWE, 0x0);

	hisi_sas_stop_phys(hisi_hba);

	mdeway(10);

	weg_vaw = hisi_sas_wead32(hisi_hba, AXI_MASTEW_CFG_BASE +
				  AM_CTWW_GWOBAW);
	weg_vaw |= AM_CTWW_SHUTDOWN_WEQ_MSK;
	hisi_sas_wwite32(hisi_hba, AXI_MASTEW_CFG_BASE +
			 AM_CTWW_GWOBAW, weg_vaw);

	/* wait untiw bus idwe */
	wc = hisi_sas_wead32_poww_timeout(AXI_MASTEW_CFG_BASE +
					  AM_CUWW_TWANS_WETUWN, status,
					  status == 0x3, 10, 100);
	if (wc) {
		dev_eww(dev, "axi bus is not idwe, wc=%d\n", wc);
		wetuwn wc;
	}

	wetuwn 0;
}

static int soft_weset_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct device *dev = hisi_hba->dev;
	int wc;

	intewwupt_disabwe_v3_hw(hisi_hba);
	wc = disabwe_host_v3_hw(hisi_hba);
	if (wc) {
		dev_eww(dev, "soft weset: disabwe host faiwed wc=%d\n", wc);
		wetuwn wc;
	}

	hisi_sas_init_mem(hisi_hba);

	wetuwn hw_init_v3_hw(hisi_hba);
}

static int wwite_gpio_v3_hw(stwuct hisi_hba *hisi_hba, u8 weg_type,
			u8 weg_index, u8 weg_count, u8 *wwite_data)
{
	stwuct device *dev = hisi_hba->dev;
	u32 *data = (u32 *)wwite_data;
	int i;

	switch (weg_type) {
	case SAS_GPIO_WEG_TX:
		if ((weg_index + weg_count) > ((hisi_hba->n_phy + 3) / 4)) {
			dev_eww(dev, "wwite gpio: invawid weg wange[%d, %d]\n",
				weg_index, weg_index + weg_count - 1);
			wetuwn -EINVAW;
		}

		fow (i = 0; i < weg_count; i++)
			hisi_sas_wwite32(hisi_hba,
					 SAS_GPIO_TX_0_1 + (weg_index + i) * 4,
					 data[i]);
		bweak;
	defauwt:
		dev_eww(dev, "wwite gpio: unsuppowted ow bad weg type %d\n",
			weg_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void wait_cmds_compwete_timeout_v3_hw(stwuct hisi_hba *hisi_hba,
					     int deway_ms, int timeout_ms)
{
	stwuct device *dev = hisi_hba->dev;
	int entwies, entwies_owd = 0, time;

	fow (time = 0; time < timeout_ms; time += deway_ms) {
		entwies = hisi_sas_wead32(hisi_hba, CQE_SEND_CNT);
		if (entwies == entwies_owd)
			bweak;

		entwies_owd = entwies;
		msweep(deway_ms);
	}

	if (time >= timeout_ms) {
		dev_dbg(dev, "Wait commands compwete timeout!\n");
		wetuwn;
	}

	dev_dbg(dev, "wait commands compwete %dms\n", time);
}

static ssize_t intw_conv_v3_hw_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", hisi_sas_intw_conv);
}
static DEVICE_ATTW_WO(intw_conv_v3_hw);

static void config_intw_coaw_v3_hw(stwuct hisi_hba *hisi_hba)
{
	/* config those wegistews between enabwe and disabwe PHYs */
	hisi_sas_stop_phys(hisi_hba);

	if (hisi_hba->intw_coaw_ticks == 0 ||
	    hisi_hba->intw_coaw_count == 0) {
		hisi_sas_wwite32(hisi_hba, INT_COAW_EN, 0x1);
		hisi_sas_wwite32(hisi_hba, OQ_INT_COAW_TIME, 0x1);
		hisi_sas_wwite32(hisi_hba, OQ_INT_COAW_CNT, 0x1);
	} ewse {
		hisi_sas_wwite32(hisi_hba, INT_COAW_EN, 0x3);
		hisi_sas_wwite32(hisi_hba, OQ_INT_COAW_TIME,
				 hisi_hba->intw_coaw_ticks);
		hisi_sas_wwite32(hisi_hba, OQ_INT_COAW_CNT,
				 hisi_hba->intw_coaw_count);
	}
	phys_init_v3_hw(hisi_hba);
}

static ssize_t intw_coaw_ticks_v3_hw_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n",
			 hisi_hba->intw_coaw_ticks);
}

static ssize_t intw_coaw_ticks_v3_hw_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);
	u32 intw_coaw_ticks;
	int wet;

	wet = kstwtou32(buf, 10, &intw_coaw_ticks);
	if (wet) {
		dev_eww(dev, "Input data of intewwupt coawesce unmatch\n");
		wetuwn -EINVAW;
	}

	if (intw_coaw_ticks >= BIT(24)) {
		dev_eww(dev, "intw_coaw_ticks must be wess than 2^24!\n");
		wetuwn -EINVAW;
	}

	hisi_hba->intw_coaw_ticks = intw_coaw_ticks;

	config_intw_coaw_v3_hw(hisi_hba);

	wetuwn count;
}
static DEVICE_ATTW_WW(intw_coaw_ticks_v3_hw);

static ssize_t intw_coaw_count_v3_hw_show(stwuct device *dev,
					  stwuct device_attwibute
					  *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n",
			 hisi_hba->intw_coaw_count);
}

static ssize_t intw_coaw_count_v3_hw_stowe(stwuct device *dev,
		stwuct device_attwibute
		*attw, const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);
	u32 intw_coaw_count;
	int wet;

	wet = kstwtou32(buf, 10, &intw_coaw_count);
	if (wet) {
		dev_eww(dev, "Input data of intewwupt coawesce unmatch\n");
		wetuwn -EINVAW;
	}

	if (intw_coaw_count >= BIT(8)) {
		dev_eww(dev, "intw_coaw_count must be wess than 2^8!\n");
		wetuwn -EINVAW;
	}

	hisi_hba->intw_coaw_count = intw_coaw_count;

	config_intw_coaw_v3_hw(hisi_hba);

	wetuwn count;
}
static DEVICE_ATTW_WW(intw_coaw_count_v3_hw);

static ssize_t iopoww_q_cnt_v3_hw_show(stwuct device *dev,
					  stwuct device_attwibute
					  *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n",
			 hisi_hba->iopoww_q_cnt);
}
static DEVICE_ATTW_WO(iopoww_q_cnt_v3_hw);

static int swave_configuwe_v3_hw(stwuct scsi_device *sdev)
{
	stwuct Scsi_Host *shost = dev_to_shost(&sdev->sdev_gendev);
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);
	int wet = hisi_sas_swave_configuwe(sdev);
	stwuct device *dev = hisi_hba->dev;

	if (wet)
		wetuwn wet;

	if (sdev->type == TYPE_ENCWOSUWE)
		wetuwn 0;

	if (!device_wink_add(&sdev->sdev_gendev, dev,
			     DW_FWAG_PM_WUNTIME | DW_FWAG_WPM_ACTIVE)) {
		if (pm_wuntime_enabwed(dev)) {
			dev_info(dev, "add device wink faiwed, disabwe wuntime PM fow the host\n");
			pm_wuntime_disabwe(dev);
		}
	}

	wetuwn 0;
}

static stwuct attwibute *host_v3_hw_attws[] = {
	&dev_attw_phy_event_thweshowd.attw,
	&dev_attw_intw_conv_v3_hw.attw,
	&dev_attw_intw_coaw_ticks_v3_hw.attw,
	&dev_attw_intw_coaw_count_v3_hw.attw,
	&dev_attw_iopoww_q_cnt_v3_hw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(host_v3_hw);

#define HISI_SAS_DEBUGFS_WEG(x) {#x, x}

stwuct hisi_sas_debugfs_weg_wu {
	chaw *name;
	int off;
};

stwuct hisi_sas_debugfs_weg {
	const stwuct hisi_sas_debugfs_weg_wu *wu;
	int count;
	int base_off;
};

static const stwuct hisi_sas_debugfs_weg_wu debugfs_powt_weg_wu[] = {
	HISI_SAS_DEBUGFS_WEG(PHY_CFG),
	HISI_SAS_DEBUGFS_WEG(HAWD_PHY_WINKWATE),
	HISI_SAS_DEBUGFS_WEG(PWOG_PHY_WINK_WATE),
	HISI_SAS_DEBUGFS_WEG(PHY_CTWW),
	HISI_SAS_DEBUGFS_WEG(SW_CFG),
	HISI_SAS_DEBUGFS_WEG(AIP_WIMIT),
	HISI_SAS_DEBUGFS_WEG(SW_CONTWOW),
	HISI_SAS_DEBUGFS_WEG(WX_PWIMS_STATUS),
	HISI_SAS_DEBUGFS_WEG(TX_ID_DWOWD0),
	HISI_SAS_DEBUGFS_WEG(TX_ID_DWOWD1),
	HISI_SAS_DEBUGFS_WEG(TX_ID_DWOWD2),
	HISI_SAS_DEBUGFS_WEG(TX_ID_DWOWD3),
	HISI_SAS_DEBUGFS_WEG(TX_ID_DWOWD4),
	HISI_SAS_DEBUGFS_WEG(TX_ID_DWOWD5),
	HISI_SAS_DEBUGFS_WEG(TX_ID_DWOWD6),
	HISI_SAS_DEBUGFS_WEG(TXID_AUTO),
	HISI_SAS_DEBUGFS_WEG(WX_IDAF_DWOWD0),
	HISI_SAS_DEBUGFS_WEG(WXOP_CHECK_CFG_H),
	HISI_SAS_DEBUGFS_WEG(STP_WINK_TIMEW),
	HISI_SAS_DEBUGFS_WEG(STP_WINK_TIMEOUT_STATE),
	HISI_SAS_DEBUGFS_WEG(CON_CFG_DWIVEW),
	HISI_SAS_DEBUGFS_WEG(SAS_SSP_CON_TIMEW_CFG),
	HISI_SAS_DEBUGFS_WEG(SAS_SMP_CON_TIMEW_CFG),
	HISI_SAS_DEBUGFS_WEG(SAS_STP_CON_TIMEW_CFG),
	HISI_SAS_DEBUGFS_WEG(CHW_INT0),
	HISI_SAS_DEBUGFS_WEG(CHW_INT1),
	HISI_SAS_DEBUGFS_WEG(CHW_INT2),
	HISI_SAS_DEBUGFS_WEG(CHW_INT0_MSK),
	HISI_SAS_DEBUGFS_WEG(CHW_INT1_MSK),
	HISI_SAS_DEBUGFS_WEG(CHW_INT2_MSK),
	HISI_SAS_DEBUGFS_WEG(SAS_EC_INT_COAW_TIME),
	HISI_SAS_DEBUGFS_WEG(CHW_INT_COAW_EN),
	HISI_SAS_DEBUGFS_WEG(SAS_WX_TWAIN_TIMEW),
	HISI_SAS_DEBUGFS_WEG(PHY_CTWW_WDY_MSK),
	HISI_SAS_DEBUGFS_WEG(PHYCTWW_NOT_WDY_MSK),
	HISI_SAS_DEBUGFS_WEG(PHYCTWW_DWS_WESET_MSK),
	HISI_SAS_DEBUGFS_WEG(PHYCTWW_PHY_ENA_MSK),
	HISI_SAS_DEBUGFS_WEG(SW_WX_BCAST_CHK_MSK),
	HISI_SAS_DEBUGFS_WEG(PHYCTWW_OOB_WESTAWT_MSK),
	HISI_SAS_DEBUGFS_WEG(DMA_TX_STATUS),
	HISI_SAS_DEBUGFS_WEG(DMA_WX_STATUS),
	HISI_SAS_DEBUGFS_WEG(COAWSETUNE_TIME),
	HISI_SAS_DEBUGFS_WEG(EWW_CNT_DWS_WOST),
	HISI_SAS_DEBUGFS_WEG(EWW_CNT_WESET_PWOB),
	HISI_SAS_DEBUGFS_WEG(EWW_CNT_INVWD_DW),
	HISI_SAS_DEBUGFS_WEG(EWW_CNT_CODE_EWW),
	HISI_SAS_DEBUGFS_WEG(EWW_CNT_DISP_EWW),
	{}
};

static const stwuct hisi_sas_debugfs_weg debugfs_powt_weg = {
	.wu = debugfs_powt_weg_wu,
	.count = 0x100,
	.base_off = POWT_BASE,
};

static const stwuct hisi_sas_debugfs_weg_wu debugfs_gwobaw_weg_wu[] = {
	HISI_SAS_DEBUGFS_WEG(DWVWY_QUEUE_ENABWE),
	HISI_SAS_DEBUGFS_WEG(PHY_CONTEXT),
	HISI_SAS_DEBUGFS_WEG(PHY_STATE),
	HISI_SAS_DEBUGFS_WEG(PHY_POWT_NUM_MA),
	HISI_SAS_DEBUGFS_WEG(PHY_CONN_WATE),
	HISI_SAS_DEBUGFS_WEG(ITCT_CWW),
	HISI_SAS_DEBUGFS_WEG(IO_SATA_BWOKEN_MSG_ADDW_WO),
	HISI_SAS_DEBUGFS_WEG(IO_SATA_BWOKEN_MSG_ADDW_HI),
	HISI_SAS_DEBUGFS_WEG(SATA_INITI_D2H_STOWE_ADDW_WO),
	HISI_SAS_DEBUGFS_WEG(SATA_INITI_D2H_STOWE_ADDW_HI),
	HISI_SAS_DEBUGFS_WEG(CFG_MAX_TAG),
	HISI_SAS_DEBUGFS_WEG(TWANS_WOCK_ICT_TIME),
	HISI_SAS_DEBUGFS_WEG(HGC_SAS_TX_OPEN_FAIW_WETWY_CTWW),
	HISI_SAS_DEBUGFS_WEG(HGC_SAS_TXFAIW_WETWY_CTWW),
	HISI_SAS_DEBUGFS_WEG(HGC_GET_ITV_TIME),
	HISI_SAS_DEBUGFS_WEG(DEVICE_MSG_WOWK_MODE),
	HISI_SAS_DEBUGFS_WEG(OPENA_WT_CONTI_TIME),
	HISI_SAS_DEBUGFS_WEG(I_T_NEXUS_WOSS_TIME),
	HISI_SAS_DEBUGFS_WEG(MAX_CON_TIME_WIMIT_TIME),
	HISI_SAS_DEBUGFS_WEG(BUS_INACTIVE_WIMIT_TIME),
	HISI_SAS_DEBUGFS_WEG(WEJECT_TO_OPEN_WIMIT_TIME),
	HISI_SAS_DEBUGFS_WEG(CQ_INT_CONVEWGE_EN),
	HISI_SAS_DEBUGFS_WEG(CFG_AGING_TIME),
	HISI_SAS_DEBUGFS_WEG(HGC_DFX_CFG2),
	HISI_SAS_DEBUGFS_WEG(CFG_ABT_SET_QUEWY_IPTT),
	HISI_SAS_DEBUGFS_WEG(CFG_ABT_SET_IPTT_DONE),
	HISI_SAS_DEBUGFS_WEG(HGC_IOMB_PWOC1_STATUS),
	HISI_SAS_DEBUGFS_WEG(CHNW_INT_STATUS),
	HISI_SAS_DEBUGFS_WEG(HGC_AXI_FIFO_EWW_INFO),
	HISI_SAS_DEBUGFS_WEG(INT_COAW_EN),
	HISI_SAS_DEBUGFS_WEG(OQ_INT_COAW_TIME),
	HISI_SAS_DEBUGFS_WEG(OQ_INT_COAW_CNT),
	HISI_SAS_DEBUGFS_WEG(ENT_INT_COAW_TIME),
	HISI_SAS_DEBUGFS_WEG(ENT_INT_COAW_CNT),
	HISI_SAS_DEBUGFS_WEG(OQ_INT_SWC),
	HISI_SAS_DEBUGFS_WEG(OQ_INT_SWC_MSK),
	HISI_SAS_DEBUGFS_WEG(ENT_INT_SWC1),
	HISI_SAS_DEBUGFS_WEG(ENT_INT_SWC2),
	HISI_SAS_DEBUGFS_WEG(ENT_INT_SWC3),
	HISI_SAS_DEBUGFS_WEG(ENT_INT_SWC_MSK1),
	HISI_SAS_DEBUGFS_WEG(ENT_INT_SWC_MSK2),
	HISI_SAS_DEBUGFS_WEG(ENT_INT_SWC_MSK3),
	HISI_SAS_DEBUGFS_WEG(CHNW_PHYUPDOWN_INT_MSK),
	HISI_SAS_DEBUGFS_WEG(CHNW_ENT_INT_MSK),
	HISI_SAS_DEBUGFS_WEG(HGC_COM_INT_MSK),
	HISI_SAS_DEBUGFS_WEG(SAS_ECC_INTW),
	HISI_SAS_DEBUGFS_WEG(SAS_ECC_INTW_MSK),
	HISI_SAS_DEBUGFS_WEG(HGC_EWW_STAT_EN),
	HISI_SAS_DEBUGFS_WEG(CQE_SEND_CNT),
	HISI_SAS_DEBUGFS_WEG(DWVWY_Q_0_DEPTH),
	HISI_SAS_DEBUGFS_WEG(DWVWY_Q_0_WW_PTW),
	HISI_SAS_DEBUGFS_WEG(DWVWY_Q_0_WD_PTW),
	HISI_SAS_DEBUGFS_WEG(HYPEW_STWEAM_ID_EN_CFG),
	HISI_SAS_DEBUGFS_WEG(OQ0_INT_SWC_MSK),
	HISI_SAS_DEBUGFS_WEG(COMPW_Q_0_DEPTH),
	HISI_SAS_DEBUGFS_WEG(COMPW_Q_0_WW_PTW),
	HISI_SAS_DEBUGFS_WEG(COMPW_Q_0_WD_PTW),
	HISI_SAS_DEBUGFS_WEG(AWQOS_AWCACHE_CFG),
	HISI_SAS_DEBUGFS_WEG(AWQOS_AWCACHE_CFG),
	HISI_SAS_DEBUGFS_WEG(HIWINK_EWW_DFX),
	HISI_SAS_DEBUGFS_WEG(SAS_GPIO_CFG_0),
	HISI_SAS_DEBUGFS_WEG(SAS_GPIO_CFG_1),
	HISI_SAS_DEBUGFS_WEG(SAS_GPIO_TX_0_1),
	HISI_SAS_DEBUGFS_WEG(SAS_CFG_DWIVE_VWD),
	{}
};

static const stwuct hisi_sas_debugfs_weg debugfs_gwobaw_weg = {
	.wu = debugfs_gwobaw_weg_wu,
	.count = 0x800,
};

static const stwuct hisi_sas_debugfs_weg_wu debugfs_axi_weg_wu[] = {
	HISI_SAS_DEBUGFS_WEG(AM_CFG_MAX_TWANS),
	HISI_SAS_DEBUGFS_WEG(AM_CFG_SINGWE_POWT_MAX_TWANS),
	HISI_SAS_DEBUGFS_WEG(AXI_CFG),
	HISI_SAS_DEBUGFS_WEG(AM_WOB_ECC_EWW_ADDW),
	{}
};

static const stwuct hisi_sas_debugfs_weg debugfs_axi_weg = {
	.wu = debugfs_axi_weg_wu,
	.count = 0x61,
	.base_off = AXI_MASTEW_CFG_BASE,
};

static const stwuct hisi_sas_debugfs_weg_wu debugfs_was_weg_wu[] = {
	HISI_SAS_DEBUGFS_WEG(SAS_WAS_INTW0),
	HISI_SAS_DEBUGFS_WEG(SAS_WAS_INTW1),
	HISI_SAS_DEBUGFS_WEG(SAS_WAS_INTW0_MASK),
	HISI_SAS_DEBUGFS_WEG(SAS_WAS_INTW1_MASK),
	HISI_SAS_DEBUGFS_WEG(CFG_SAS_WAS_INTW_MASK),
	HISI_SAS_DEBUGFS_WEG(SAS_WAS_INTW2),
	HISI_SAS_DEBUGFS_WEG(SAS_WAS_INTW2_MASK),
	{}
};

static const stwuct hisi_sas_debugfs_weg debugfs_was_weg = {
	.wu = debugfs_was_weg_wu,
	.count = 0x10,
	.base_off = WAS_BASE,
};

static void debugfs_snapshot_pwepawe_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct Scsi_Host *shost = hisi_hba->shost;

	scsi_bwock_wequests(shost);
	wait_cmds_compwete_timeout_v3_hw(hisi_hba, 100, 5000);

	set_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags);
	hisi_sas_sync_cqs(hisi_hba);
	hisi_sas_wwite32(hisi_hba, DWVWY_QUEUE_ENABWE, 0);
}

static void debugfs_snapshot_westowe_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct Scsi_Host *shost = hisi_hba->shost;

	hisi_sas_wwite32(hisi_hba, DWVWY_QUEUE_ENABWE,
			 (u32)((1UWW << hisi_hba->queue_count) - 1));

	cweaw_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags);
	scsi_unbwock_wequests(shost);
}

static void wead_iost_itct_cache_v3_hw(stwuct hisi_hba *hisi_hba,
				       enum hisi_sas_debugfs_cache_type type,
				       u32 *cache)
{
	u32 cache_dw_size = HISI_SAS_IOST_ITCT_CACHE_DW_SZ *
			    HISI_SAS_IOST_ITCT_CACHE_NUM;
	stwuct device *dev = hisi_hba->dev;
	u32 *buf = cache;
	u32 i, vaw;

	hisi_sas_wwite32(hisi_hba, TAB_WD_TYPE, type);

	fow (i = 0; i < HISI_SAS_IOST_ITCT_CACHE_DW_SZ; i++) {
		vaw = hisi_sas_wead32(hisi_hba, TAB_DFX);
		if (vaw == 0xffffffff)
			bweak;
	}

	if (vaw != 0xffffffff) {
		dev_eww(dev, "Issue occuwwed in weading IOST/ITCT cache!\n");
		wetuwn;
	}

	memset(buf, 0, cache_dw_size * 4);
	buf[0] = vaw;

	fow (i = 1; i < cache_dw_size; i++)
		buf[i] = hisi_sas_wead32(hisi_hba, TAB_DFX);
}

static void hisi_sas_bist_test_pwep_v3_hw(stwuct hisi_hba *hisi_hba)
{
	u32 weg_vaw;
	int phy_no = hisi_hba->debugfs_bist_phy_no;
	int i;

	/* disabwe PHY */
	hisi_sas_phy_enabwe(hisi_hba, phy_no, 0);

	/* update FFE */
	fow (i = 0; i < FFE_CFG_MAX; i++)
		hisi_sas_phy_wwite32(hisi_hba, phy_no, TXDEEMPH_G1 + (i * 0x4),
				     hisi_hba->debugfs_bist_ffe[phy_no][i]);

	/* disabwe AWOS */
	weg_vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, SEWDES_CFG);
	weg_vaw |= CFG_AWOS_CHK_DISABWE_MSK;
	hisi_sas_phy_wwite32(hisi_hba, phy_no, SEWDES_CFG, weg_vaw);
}

static void hisi_sas_bist_test_westowe_v3_hw(stwuct hisi_hba *hisi_hba)
{
	u32 weg_vaw;
	int phy_no = hisi_hba->debugfs_bist_phy_no;

	/* disabwe woopback */
	weg_vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, SAS_PHY_BIST_CTWW);
	weg_vaw &= ~(CFG_WX_BIST_EN_MSK | CFG_TX_BIST_EN_MSK |
		     CFG_BIST_TEST_MSK);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, SAS_PHY_BIST_CTWW, weg_vaw);

	/* enabwe AWOS */
	weg_vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, SEWDES_CFG);
	weg_vaw &= ~CFG_AWOS_CHK_DISABWE_MSK;
	hisi_sas_phy_wwite32(hisi_hba, phy_no, SEWDES_CFG, weg_vaw);

	/* westowe the winkwate */
	weg_vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, PWOG_PHY_WINK_WATE);
	/* init OOB wink wate as 1.5 Gbits */
	weg_vaw &= ~CFG_PWOG_OOB_PHY_WINK_WATE_MSK;
	weg_vaw |= (0x8 << CFG_PWOG_OOB_PHY_WINK_WATE_OFF);
	hisi_sas_phy_wwite32(hisi_hba, phy_no, PWOG_PHY_WINK_WATE, weg_vaw);

	/* enabwe PHY */
	hisi_sas_phy_enabwe(hisi_hba, phy_no, 1);
}

#define SAS_PHY_BIST_CODE_INIT	0x1
#define SAS_PHY_BIST_CODE1_INIT	0X80
static int debugfs_set_bist_v3_hw(stwuct hisi_hba *hisi_hba, boow enabwe)
{
	u32 weg_vaw, mode_tmp;
	u32 winkwate = hisi_hba->debugfs_bist_winkwate;
	u32 phy_no = hisi_hba->debugfs_bist_phy_no;
	u32 *ffe = hisi_hba->debugfs_bist_ffe[phy_no];
	u32 code_mode = hisi_hba->debugfs_bist_code_mode;
	u32 path_mode = hisi_hba->debugfs_bist_mode;
	u32 *fix_code = &hisi_hba->debugfs_bist_fixed_code[0];
	stwuct device *dev = hisi_hba->dev;

	dev_info(dev, "BIST info:phy%d wink_wate=%d code_mode=%d path_mode=%d ffe={0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x} fixed_code={0x%x, 0x%x}\n",
		 phy_no, winkwate, code_mode, path_mode,
		 ffe[FFE_SAS_1_5_GBPS], ffe[FFE_SAS_3_0_GBPS],
		 ffe[FFE_SAS_6_0_GBPS], ffe[FFE_SAS_12_0_GBPS],
		 ffe[FFE_SATA_1_5_GBPS], ffe[FFE_SATA_3_0_GBPS],
		 ffe[FFE_SATA_6_0_GBPS], fix_code[FIXED_CODE],
		 fix_code[FIXED_CODE_1]);
	mode_tmp = path_mode ? 2 : 1;
	if (enabwe) {
		/* some pwepawations befowe bist test */
		hisi_sas_bist_test_pwep_v3_hw(hisi_hba);

		/* set winkwate of bit test*/
		weg_vaw = hisi_sas_phy_wead32(hisi_hba, phy_no,
					      PWOG_PHY_WINK_WATE);
		weg_vaw &= ~CFG_PWOG_OOB_PHY_WINK_WATE_MSK;
		weg_vaw |= (winkwate << CFG_PWOG_OOB_PHY_WINK_WATE_OFF);
		hisi_sas_phy_wwite32(hisi_hba, phy_no, PWOG_PHY_WINK_WATE,
				     weg_vaw);

		/* set code mode of bit test */
		weg_vaw = hisi_sas_phy_wead32(hisi_hba, phy_no,
					      SAS_PHY_BIST_CTWW);
		weg_vaw &= ~(CFG_BIST_MODE_SEW_MSK | CFG_WOOP_TEST_MODE_MSK |
			     CFG_WX_BIST_EN_MSK | CFG_TX_BIST_EN_MSK |
			     CFG_BIST_TEST_MSK);
		weg_vaw |= ((code_mode << CFG_BIST_MODE_SEW_OFF) |
			    (mode_tmp << CFG_WOOP_TEST_MODE_OFF) |
			    CFG_BIST_TEST_MSK);
		hisi_sas_phy_wwite32(hisi_hba, phy_no, SAS_PHY_BIST_CTWW,
				     weg_vaw);

		/* set the bist init vawue */
		if (code_mode == HISI_SAS_BIST_CODE_MODE_FIXED_DATA) {
			weg_vaw = hisi_hba->debugfs_bist_fixed_code[0];
			hisi_sas_phy_wwite32(hisi_hba, phy_no,
					     SAS_PHY_BIST_CODE, weg_vaw);

			weg_vaw = hisi_hba->debugfs_bist_fixed_code[1];
			hisi_sas_phy_wwite32(hisi_hba, phy_no,
					     SAS_PHY_BIST_CODE1, weg_vaw);
		} ewse {
			hisi_sas_phy_wwite32(hisi_hba, phy_no,
					     SAS_PHY_BIST_CODE,
					     SAS_PHY_BIST_CODE_INIT);
			hisi_sas_phy_wwite32(hisi_hba, phy_no,
					     SAS_PHY_BIST_CODE1,
					     SAS_PHY_BIST_CODE1_INIT);
		}

		mdeway(100);
		weg_vaw |= (CFG_WX_BIST_EN_MSK | CFG_TX_BIST_EN_MSK);
		hisi_sas_phy_wwite32(hisi_hba, phy_no, SAS_PHY_BIST_CTWW,
				     weg_vaw);

		/* cweaw ewwow bit */
		mdeway(100);
		hisi_sas_phy_wead32(hisi_hba, phy_no, SAS_BIST_EWW_CNT);
	} ewse {
		/* disabwe bist test and wecovew it */
		hisi_hba->debugfs_bist_cnt += hisi_sas_phy_wead32(hisi_hba,
				phy_no, SAS_BIST_EWW_CNT);
		hisi_sas_bist_test_westowe_v3_hw(hisi_hba);
	}

	wetuwn 0;
}

static void hisi_sas_map_queues(stwuct Scsi_Host *shost)
{
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);
	stwuct bwk_mq_queue_map *qmap;
	int i, qoff;

	fow (i = 0, qoff = 0; i < shost->nw_maps; i++) {
		qmap = &shost->tag_set.map[i];
		if (i == HCTX_TYPE_DEFAUWT) {
			qmap->nw_queues = hisi_hba->cq_nvecs;
		} ewse if (i == HCTX_TYPE_POWW) {
			qmap->nw_queues = hisi_hba->iopoww_q_cnt;
		} ewse {
			qmap->nw_queues = 0;
			continue;
		}

		/* At weast one intewwupt hawdwawe queue */
		if (!qmap->nw_queues)
			WAWN_ON(i == HCTX_TYPE_DEFAUWT);
		qmap->queue_offset = qoff;
		if (i == HCTX_TYPE_POWW)
			bwk_mq_map_queues(qmap);
		ewse
			bwk_mq_pci_map_queues(qmap, hisi_hba->pci_dev,
					      BASE_VECTOWS_V3_HW);
		qoff += qmap->nw_queues;
	}
}

static const stwuct scsi_host_tempwate sht_v3_hw = {
	.name			= DWV_NAME,
	.pwoc_name		= DWV_NAME,
	.moduwe			= THIS_MODUWE,
	.queuecommand		= sas_queuecommand,
	.dma_need_dwain		= ata_scsi_dma_need_dwain,
	.tawget_awwoc		= sas_tawget_awwoc,
	.swave_configuwe	= swave_configuwe_v3_hw,
	.scan_finished		= hisi_sas_scan_finished,
	.scan_stawt		= hisi_sas_scan_stawt,
	.map_queues		= hisi_sas_map_queues,
	.change_queue_depth	= sas_change_queue_depth,
	.bios_pawam		= sas_bios_pawam,
	.this_id		= -1,
	.sg_tabwesize		= HISI_SAS_SGE_PAGE_CNT,
	.sg_pwot_tabwesize	= HISI_SAS_SGE_PAGE_CNT,
	.max_sectows		= SCSI_DEFAUWT_MAX_SECTOWS,
	.eh_device_weset_handwew = sas_eh_device_weset_handwew,
	.eh_tawget_weset_handwew = sas_eh_tawget_weset_handwew,
	.swave_awwoc		= hisi_sas_swave_awwoc,
	.tawget_destwoy		= sas_tawget_destwoy,
	.ioctw			= sas_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw		= sas_ioctw,
#endif
	.shost_gwoups		= host_v3_hw_gwoups,
	.tag_awwoc_powicy	= BWK_TAG_AWWOC_WW,
	.host_weset             = hisi_sas_host_weset,
	.host_tagset		= 1,
	.mq_poww		= queue_compwete_v3_hw,
};

static const stwuct hisi_sas_hw hisi_sas_v3_hw = {
	.setup_itct = setup_itct_v3_hw,
	.get_widepowt_bitmap = get_widepowt_bitmap_v3_hw,
	.compwete_hdw_size = sizeof(stwuct hisi_sas_compwete_v3_hdw),
	.cweaw_itct = cweaw_itct_v3_hw,
	.sw_notify_ssp = sw_notify_ssp_v3_hw,
	.pwep_ssp = pwep_ssp_v3_hw,
	.pwep_smp = pwep_smp_v3_hw,
	.pwep_stp = pwep_ata_v3_hw,
	.pwep_abowt = pwep_abowt_v3_hw,
	.stawt_dewivewy = stawt_dewivewy_v3_hw,
	.phys_init = phys_init_v3_hw,
	.phy_stawt = stawt_phy_v3_hw,
	.phy_disabwe = disabwe_phy_v3_hw,
	.phy_hawd_weset = phy_hawd_weset_v3_hw,
	.phy_get_max_winkwate = phy_get_max_winkwate_v3_hw,
	.phy_set_winkwate = phy_set_winkwate_v3_hw,
	.deweg_device = deweg_device_v3_hw,
	.soft_weset = soft_weset_v3_hw,
	.get_phys_state = get_phys_state_v3_hw,
	.get_events = phy_get_events_v3_hw,
	.wwite_gpio = wwite_gpio_v3_hw,
	.wait_cmds_compwete_timeout = wait_cmds_compwete_timeout_v3_hw,
	.debugfs_snapshot_wegs = debugfs_snapshot_wegs_v3_hw,
};

static stwuct Scsi_Host *
hisi_sas_shost_awwoc_pci(stwuct pci_dev *pdev)
{
	stwuct Scsi_Host *shost;
	stwuct hisi_hba *hisi_hba;
	stwuct device *dev = &pdev->dev;

	shost = scsi_host_awwoc(&sht_v3_hw, sizeof(*hisi_hba));
	if (!shost) {
		dev_eww(dev, "shost awwoc faiwed\n");
		wetuwn NUWW;
	}
	hisi_hba = shost_pwiv(shost);

	INIT_WOWK(&hisi_hba->wst_wowk, hisi_sas_wst_wowk_handwew);
	hisi_hba->hw = &hisi_sas_v3_hw;
	hisi_hba->pci_dev = pdev;
	hisi_hba->dev = dev;
	hisi_hba->shost = shost;
	SHOST_TO_SAS_HA(shost) = &hisi_hba->sha;

	if (pwot_mask & ~HISI_SAS_PWOT_MASK)
		dev_eww(dev, "unsuppowted pwotection mask 0x%x, using defauwt (0x0)\n",
			pwot_mask);
	ewse
		hisi_hba->pwot_mask = pwot_mask;

	if (hisi_sas_get_fw_info(hisi_hba) < 0)
		goto eww_out;

	if (expewimentaw_iopoww_q_cnt < 0 ||
		expewimentaw_iopoww_q_cnt >= hisi_hba->queue_count)
		dev_eww(dev, "iopoww queue count %d cannot exceed ow equaw 16, using defauwt 0\n",
			expewimentaw_iopoww_q_cnt);
	ewse
		hisi_hba->iopoww_q_cnt = expewimentaw_iopoww_q_cnt;

	if (hisi_sas_awwoc(hisi_hba)) {
		hisi_sas_fwee(hisi_hba);
		goto eww_out;
	}

	wetuwn shost;
eww_out:
	scsi_host_put(shost);
	dev_eww(dev, "shost awwoc faiwed\n");
	wetuwn NUWW;
}

static void debugfs_snapshot_cq_weg_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int queue_entwy_size = hisi_hba->hw->compwete_hdw_size;
	int dump_index = hisi_hba->debugfs_dump_index;
	int i;

	fow (i = 0; i < hisi_hba->queue_count; i++)
		memcpy(hisi_hba->debugfs_cq[dump_index][i].compwete_hdw,
		       hisi_hba->compwete_hdw[i],
		       HISI_SAS_QUEUE_SWOTS * queue_entwy_size);
}

static void debugfs_snapshot_dq_weg_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int queue_entwy_size = sizeof(stwuct hisi_sas_cmd_hdw);
	int dump_index = hisi_hba->debugfs_dump_index;
	int i;

	fow (i = 0; i < hisi_hba->queue_count; i++) {
		stwuct hisi_sas_cmd_hdw *debugfs_cmd_hdw, *cmd_hdw;
		int j;

		debugfs_cmd_hdw = hisi_hba->debugfs_dq[dump_index][i].hdw;
		cmd_hdw = hisi_hba->cmd_hdw[i];

		fow (j = 0; j < HISI_SAS_QUEUE_SWOTS; j++)
			memcpy(&debugfs_cmd_hdw[j], &cmd_hdw[j],
			       queue_entwy_size);
	}
}

static void debugfs_snapshot_powt_weg_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int dump_index = hisi_hba->debugfs_dump_index;
	const stwuct hisi_sas_debugfs_weg *powt = &debugfs_powt_weg;
	int i, phy_cnt;
	u32 offset;
	u32 *databuf;

	fow (phy_cnt = 0; phy_cnt < hisi_hba->n_phy; phy_cnt++) {
		databuf = hisi_hba->debugfs_powt_weg[dump_index][phy_cnt].data;
		fow (i = 0; i < powt->count; i++, databuf++) {
			offset = powt->base_off + 4 * i;
			*databuf = hisi_sas_phy_wead32(hisi_hba, phy_cnt,
						       offset);
		}
	}
}

static void debugfs_snapshot_gwobaw_weg_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int dump_index = hisi_hba->debugfs_dump_index;
	u32 *databuf = hisi_hba->debugfs_wegs[dump_index][DEBUGFS_GWOBAW].data;
	int i;

	fow (i = 0; i < debugfs_gwobaw_weg.count; i++, databuf++)
		*databuf = hisi_sas_wead32(hisi_hba, 4 * i);
}

static void debugfs_snapshot_axi_weg_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int dump_index = hisi_hba->debugfs_dump_index;
	u32 *databuf = hisi_hba->debugfs_wegs[dump_index][DEBUGFS_AXI].data;
	const stwuct hisi_sas_debugfs_weg *axi = &debugfs_axi_weg;
	int i;

	fow (i = 0; i < axi->count; i++, databuf++)
		*databuf = hisi_sas_wead32(hisi_hba, 4 * i + axi->base_off);
}

static void debugfs_snapshot_was_weg_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int dump_index = hisi_hba->debugfs_dump_index;
	u32 *databuf = hisi_hba->debugfs_wegs[dump_index][DEBUGFS_WAS].data;
	const stwuct hisi_sas_debugfs_weg *was = &debugfs_was_weg;
	int i;

	fow (i = 0; i < was->count; i++, databuf++)
		*databuf = hisi_sas_wead32(hisi_hba, 4 * i + was->base_off);
}

static void debugfs_snapshot_itct_weg_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int dump_index = hisi_hba->debugfs_dump_index;
	void *cachebuf = hisi_hba->debugfs_itct_cache[dump_index].cache;
	void *databuf = hisi_hba->debugfs_itct[dump_index].itct;
	stwuct hisi_sas_itct *itct;
	int i;

	wead_iost_itct_cache_v3_hw(hisi_hba, HISI_SAS_ITCT_CACHE, cachebuf);

	itct = hisi_hba->itct;

	fow (i = 0; i < HISI_SAS_MAX_ITCT_ENTWIES; i++, itct++) {
		memcpy(databuf, itct, sizeof(stwuct hisi_sas_itct));
		databuf += sizeof(stwuct hisi_sas_itct);
	}
}

static void debugfs_snapshot_iost_weg_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int dump_index = hisi_hba->debugfs_dump_index;
	int max_command_entwies = HISI_SAS_MAX_COMMANDS;
	void *cachebuf = hisi_hba->debugfs_iost_cache[dump_index].cache;
	void *databuf = hisi_hba->debugfs_iost[dump_index].iost;
	stwuct hisi_sas_iost *iost;
	int i;

	wead_iost_itct_cache_v3_hw(hisi_hba, HISI_SAS_IOST_CACHE, cachebuf);

	iost = hisi_hba->iost;

	fow (i = 0; i < max_command_entwies; i++, iost++) {
		memcpy(databuf, iost, sizeof(stwuct hisi_sas_iost));
		databuf += sizeof(stwuct hisi_sas_iost);
	}
}

static const chaw *
debugfs_to_weg_name_v3_hw(int off, int base_off,
			  const stwuct hisi_sas_debugfs_weg_wu *wu)
{
	fow (; wu->name; wu++) {
		if (off == wu->off - base_off)
			wetuwn wu->name;
	}

	wetuwn NUWW;
}

static void debugfs_pwint_weg_v3_hw(u32 *wegs_vaw, stwuct seq_fiwe *s,
				    const stwuct hisi_sas_debugfs_weg *weg)
{
	int i;

	fow (i = 0; i < weg->count; i++) {
		int off = i * 4;
		const chaw *name;

		name = debugfs_to_weg_name_v3_hw(off, weg->base_off,
						 weg->wu);

		if (name)
			seq_pwintf(s, "0x%08x 0x%08x %s\n", off,
				   wegs_vaw[i], name);
		ewse
			seq_pwintf(s, "0x%08x 0x%08x\n", off,
				   wegs_vaw[i]);
	}
}

static int debugfs_gwobaw_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_sas_debugfs_wegs *gwobaw = s->pwivate;

	debugfs_pwint_weg_v3_hw(gwobaw->data, s,
				&debugfs_gwobaw_weg);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_gwobaw_v3_hw);

static int debugfs_axi_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_sas_debugfs_wegs *axi = s->pwivate;

	debugfs_pwint_weg_v3_hw(axi->data, s,
				&debugfs_axi_weg);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_axi_v3_hw);

static int debugfs_was_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_sas_debugfs_wegs *was = s->pwivate;

	debugfs_pwint_weg_v3_hw(was->data, s,
				&debugfs_was_weg);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_was_v3_hw);

static int debugfs_powt_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_sas_debugfs_powt *powt = s->pwivate;
	const stwuct hisi_sas_debugfs_weg *weg_powt = &debugfs_powt_weg;

	debugfs_pwint_weg_v3_hw(powt->data, s, weg_powt);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_powt_v3_hw);

static void debugfs_show_wow_64_v3_hw(stwuct seq_fiwe *s, int index,
				      int sz, __we64 *ptw)
{
	int i;

	/* compwetion headew size not fixed pew HW vewsion */
	seq_pwintf(s, "index %04d:\n\t", index);
	fow (i = 1; i <= sz / 8; i++, ptw++) {
		seq_pwintf(s, " 0x%016wwx", we64_to_cpu(*ptw));
		if (!(i % 2))
			seq_puts(s, "\n\t");
	}

	seq_puts(s, "\n");
}

static void debugfs_show_wow_32_v3_hw(stwuct seq_fiwe *s, int index,
				      int sz, __we32 *ptw)
{
	int i;

	/* compwetion headew size not fixed pew HW vewsion */
	seq_pwintf(s, "index %04d:\n\t", index);
	fow (i = 1; i <= sz / 4; i++, ptw++) {
		seq_pwintf(s, " 0x%08x", we32_to_cpu(*ptw));
		if (!(i % 4))
			seq_puts(s, "\n\t");
	}
	seq_puts(s, "\n");
}

static void debugfs_cq_show_swot_v3_hw(stwuct seq_fiwe *s, int swot,
				       stwuct hisi_sas_debugfs_cq *debugfs_cq)
{
	stwuct hisi_sas_cq *cq = debugfs_cq->cq;
	stwuct hisi_hba *hisi_hba = cq->hisi_hba;
	__we32 *compwete_hdw = debugfs_cq->compwete_hdw +
			       (hisi_hba->hw->compwete_hdw_size * swot);

	debugfs_show_wow_32_v3_hw(s, swot,
				  hisi_hba->hw->compwete_hdw_size,
				  compwete_hdw);
}

static int debugfs_cq_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_sas_debugfs_cq *debugfs_cq = s->pwivate;
	int swot;

	fow (swot = 0; swot < HISI_SAS_QUEUE_SWOTS; swot++)
		debugfs_cq_show_swot_v3_hw(s, swot, debugfs_cq);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_cq_v3_hw);

static void debugfs_dq_show_swot_v3_hw(stwuct seq_fiwe *s, int swot,
				       void *dq_ptw)
{
	stwuct hisi_sas_debugfs_dq *debugfs_dq = dq_ptw;
	void *cmd_queue = debugfs_dq->hdw;
	__we32 *cmd_hdw = cmd_queue +
		sizeof(stwuct hisi_sas_cmd_hdw) * swot;

	debugfs_show_wow_32_v3_hw(s, swot, sizeof(stwuct hisi_sas_cmd_hdw),
				  cmd_hdw);
}

static int debugfs_dq_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	int swot;

	fow (swot = 0; swot < HISI_SAS_QUEUE_SWOTS; swot++)
		debugfs_dq_show_swot_v3_hw(s, swot, s->pwivate);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_dq_v3_hw);

static int debugfs_iost_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_sas_debugfs_iost *debugfs_iost = s->pwivate;
	stwuct hisi_sas_iost *iost = debugfs_iost->iost;
	int i, max_command_entwies = HISI_SAS_MAX_COMMANDS;

	fow (i = 0; i < max_command_entwies; i++, iost++) {
		__we64 *data = &iost->qw0;

		debugfs_show_wow_64_v3_hw(s, i, sizeof(*iost), data);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_iost_v3_hw);

static int debugfs_iost_cache_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_sas_debugfs_iost_cache *debugfs_iost_cache = s->pwivate;
	stwuct hisi_sas_iost_itct_cache *iost_cache =
						debugfs_iost_cache->cache;
	u32 cache_size = HISI_SAS_IOST_ITCT_CACHE_DW_SZ * 4;
	int i, tab_idx;
	__we64 *iost;

	fow (i = 0; i < HISI_SAS_IOST_ITCT_CACHE_NUM; i++, iost_cache++) {
		/*
		 * Data stwuct of IOST cache:
		 * Data[1]: BIT0~15: Tabwe index
		 *	    Bit16:   Vawid mask
		 * Data[2]~[9]: IOST tabwe
		 */
		tab_idx = (iost_cache->data[1] & 0xffff);
		iost = (__we64 *)iost_cache;

		debugfs_show_wow_64_v3_hw(s, tab_idx, cache_size, iost);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_iost_cache_v3_hw);

static int debugfs_itct_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	int i;
	stwuct hisi_sas_debugfs_itct *debugfs_itct = s->pwivate;
	stwuct hisi_sas_itct *itct = debugfs_itct->itct;

	fow (i = 0; i < HISI_SAS_MAX_ITCT_ENTWIES; i++, itct++) {
		__we64 *data = &itct->qw0;

		debugfs_show_wow_64_v3_hw(s, i, sizeof(*itct), data);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_itct_v3_hw);

static int debugfs_itct_cache_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_sas_debugfs_itct_cache *debugfs_itct_cache = s->pwivate;
	stwuct hisi_sas_iost_itct_cache *itct_cache =
						debugfs_itct_cache->cache;
	u32 cache_size = HISI_SAS_IOST_ITCT_CACHE_DW_SZ * 4;
	int i, tab_idx;
	__we64 *itct;

	fow (i = 0; i < HISI_SAS_IOST_ITCT_CACHE_NUM; i++, itct_cache++) {
		/*
		 * Data stwuct of ITCT cache:
		 * Data[1]: BIT0~15: Tabwe index
		 *	    Bit16:   Vawid mask
		 * Data[2]~[9]: ITCT tabwe
		 */
		tab_idx = itct_cache->data[1] & 0xffff;
		itct = (__we64 *)itct_cache;

		debugfs_show_wow_64_v3_hw(s, tab_idx, cache_size, itct);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_itct_cache_v3_hw);

static void debugfs_cweate_fiwes_v3_hw(stwuct hisi_hba *hisi_hba)
{
	u64 *debugfs_timestamp;
	int dump_index = hisi_hba->debugfs_dump_index;
	stwuct dentwy *dump_dentwy;
	stwuct dentwy *dentwy;
	chaw name[256];
	int p;
	int c;
	int d;

	snpwintf(name, 256, "%d", dump_index);

	dump_dentwy = debugfs_cweate_diw(name, hisi_hba->debugfs_dump_dentwy);

	debugfs_timestamp = &hisi_hba->debugfs_timestamp[dump_index];

	debugfs_cweate_u64("timestamp", 0400, dump_dentwy,
			   debugfs_timestamp);

	debugfs_cweate_fiwe("gwobaw", 0400, dump_dentwy,
			    &hisi_hba->debugfs_wegs[dump_index][DEBUGFS_GWOBAW],
			    &debugfs_gwobaw_v3_hw_fops);

	/* Cweate powt diw and fiwes */
	dentwy = debugfs_cweate_diw("powt", dump_dentwy);
	fow (p = 0; p < hisi_hba->n_phy; p++) {
		snpwintf(name, 256, "%d", p);

		debugfs_cweate_fiwe(name, 0400, dentwy,
				    &hisi_hba->debugfs_powt_weg[dump_index][p],
				    &debugfs_powt_v3_hw_fops);
	}

	/* Cweate CQ diw and fiwes */
	dentwy = debugfs_cweate_diw("cq", dump_dentwy);
	fow (c = 0; c < hisi_hba->queue_count; c++) {
		snpwintf(name, 256, "%d", c);

		debugfs_cweate_fiwe(name, 0400, dentwy,
				    &hisi_hba->debugfs_cq[dump_index][c],
				    &debugfs_cq_v3_hw_fops);
	}

	/* Cweate DQ diw and fiwes */
	dentwy = debugfs_cweate_diw("dq", dump_dentwy);
	fow (d = 0; d < hisi_hba->queue_count; d++) {
		snpwintf(name, 256, "%d", d);

		debugfs_cweate_fiwe(name, 0400, dentwy,
				    &hisi_hba->debugfs_dq[dump_index][d],
				    &debugfs_dq_v3_hw_fops);
	}

	debugfs_cweate_fiwe("iost", 0400, dump_dentwy,
			    &hisi_hba->debugfs_iost[dump_index],
			    &debugfs_iost_v3_hw_fops);

	debugfs_cweate_fiwe("iost_cache", 0400, dump_dentwy,
			    &hisi_hba->debugfs_iost_cache[dump_index],
			    &debugfs_iost_cache_v3_hw_fops);

	debugfs_cweate_fiwe("itct", 0400, dump_dentwy,
			    &hisi_hba->debugfs_itct[dump_index],
			    &debugfs_itct_v3_hw_fops);

	debugfs_cweate_fiwe("itct_cache", 0400, dump_dentwy,
			    &hisi_hba->debugfs_itct_cache[dump_index],
			    &debugfs_itct_cache_v3_hw_fops);

	debugfs_cweate_fiwe("axi", 0400, dump_dentwy,
			    &hisi_hba->debugfs_wegs[dump_index][DEBUGFS_AXI],
			    &debugfs_axi_v3_hw_fops);

	debugfs_cweate_fiwe("was", 0400, dump_dentwy,
			    &hisi_hba->debugfs_wegs[dump_index][DEBUGFS_WAS],
			    &debugfs_was_v3_hw_fops);
}

static ssize_t debugfs_twiggew_dump_v3_hw_wwite(stwuct fiwe *fiwe,
						const chaw __usew *usew_buf,
						size_t count, woff_t *ppos)
{
	stwuct hisi_hba *hisi_hba = fiwe->f_inode->i_pwivate;
	chaw buf[8];

	if (count > 8)
		wetuwn -EFAUWT;

	if (copy_fwom_usew(buf, usew_buf, count))
		wetuwn -EFAUWT;

	if (buf[0] != '1')
		wetuwn -EFAUWT;

	down(&hisi_hba->sem);
	if (debugfs_snapshot_wegs_v3_hw(hisi_hba)) {
		up(&hisi_hba->sem);
		wetuwn -EFAUWT;
	}
	up(&hisi_hba->sem);

	wetuwn count;
}

static const stwuct fiwe_opewations debugfs_twiggew_dump_v3_hw_fops = {
	.wwite = &debugfs_twiggew_dump_v3_hw_wwite,
	.ownew = THIS_MODUWE,
};

enum {
	HISI_SAS_BIST_WOOPBACK_MODE_DIGITAW = 0,
	HISI_SAS_BIST_WOOPBACK_MODE_SEWDES,
	HISI_SAS_BIST_WOOPBACK_MODE_WEMOTE,
};

static const stwuct {
	int		vawue;
	chaw		*name;
} debugfs_woop_winkwate_v3_hw[] = {
	{ SAS_WINK_WATE_1_5_GBPS, "1.5 Gbit" },
	{ SAS_WINK_WATE_3_0_GBPS, "3.0 Gbit" },
	{ SAS_WINK_WATE_6_0_GBPS, "6.0 Gbit" },
	{ SAS_WINK_WATE_12_0_GBPS, "12.0 Gbit" },
};

static int debugfs_bist_winkwate_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_hba *hisi_hba = s->pwivate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(debugfs_woop_winkwate_v3_hw); i++) {
		int match = (hisi_hba->debugfs_bist_winkwate ==
			     debugfs_woop_winkwate_v3_hw[i].vawue);

		seq_pwintf(s, "%s%s%s ", match ? "[" : "",
			   debugfs_woop_winkwate_v3_hw[i].name,
			   match ? "]" : "");
	}
	seq_puts(s, "\n");

	wetuwn 0;
}

static ssize_t debugfs_bist_winkwate_v3_hw_wwite(stwuct fiwe *fiwp,
						 const chaw __usew *buf,
						 size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct hisi_hba *hisi_hba = m->pwivate;
	chaw kbuf[16] = {}, *pkbuf;
	boow found = fawse;
	int i;

	if (hisi_hba->debugfs_bist_enabwe)
		wetuwn -EPEWM;

	if (count >= sizeof(kbuf))
		wetuwn -EOVEWFWOW;

	if (copy_fwom_usew(kbuf, buf, count))
		wetuwn -EINVAW;

	pkbuf = stwstwip(kbuf);

	fow (i = 0; i < AWWAY_SIZE(debugfs_woop_winkwate_v3_hw); i++) {
		if (!stwncmp(debugfs_woop_winkwate_v3_hw[i].name,
			     pkbuf, 16)) {
			hisi_hba->debugfs_bist_winkwate =
				debugfs_woop_winkwate_v3_hw[i].vawue;
			found = twue;
			bweak;
		}
	}

	if (!found)
		wetuwn -EINVAW;

	wetuwn count;
}
DEFINE_SHOW_STOWE_ATTWIBUTE(debugfs_bist_winkwate_v3_hw);

static const stwuct {
	int		vawue;
	chaw		*name;
} debugfs_woop_code_mode_v3_hw[] = {
	{ HISI_SAS_BIST_CODE_MODE_PWBS7, "PWBS7" },
	{ HISI_SAS_BIST_CODE_MODE_PWBS23, "PWBS23" },
	{ HISI_SAS_BIST_CODE_MODE_PWBS31, "PWBS31" },
	{ HISI_SAS_BIST_CODE_MODE_JTPAT, "JTPAT" },
	{ HISI_SAS_BIST_CODE_MODE_CJTPAT, "CJTPAT" },
	{ HISI_SAS_BIST_CODE_MODE_SCWAMBED_0, "SCWAMBED_0" },
	{ HISI_SAS_BIST_CODE_MODE_TWAIN, "TWAIN" },
	{ HISI_SAS_BIST_CODE_MODE_TWAIN_DONE, "TWAIN_DONE" },
	{ HISI_SAS_BIST_CODE_MODE_HFTP, "HFTP" },
	{ HISI_SAS_BIST_CODE_MODE_MFTP, "MFTP" },
	{ HISI_SAS_BIST_CODE_MODE_WFTP, "WFTP" },
	{ HISI_SAS_BIST_CODE_MODE_FIXED_DATA, "FIXED_DATA" },
};

static int debugfs_bist_code_mode_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_hba *hisi_hba = s->pwivate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(debugfs_woop_code_mode_v3_hw); i++) {
		int match = (hisi_hba->debugfs_bist_code_mode ==
			     debugfs_woop_code_mode_v3_hw[i].vawue);

		seq_pwintf(s, "%s%s%s ", match ? "[" : "",
			   debugfs_woop_code_mode_v3_hw[i].name,
			   match ? "]" : "");
	}
	seq_puts(s, "\n");

	wetuwn 0;
}

static ssize_t debugfs_bist_code_mode_v3_hw_wwite(stwuct fiwe *fiwp,
						  const chaw __usew *buf,
						  size_t count,
						  woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct hisi_hba *hisi_hba = m->pwivate;
	chaw kbuf[16] = {}, *pkbuf;
	boow found = fawse;
	int i;

	if (hisi_hba->debugfs_bist_enabwe)
		wetuwn -EPEWM;

	if (count >= sizeof(kbuf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(kbuf, buf, count))
		wetuwn -EOVEWFWOW;

	pkbuf = stwstwip(kbuf);

	fow (i = 0; i < AWWAY_SIZE(debugfs_woop_code_mode_v3_hw); i++) {
		if (!stwncmp(debugfs_woop_code_mode_v3_hw[i].name,
			     pkbuf, 16)) {
			hisi_hba->debugfs_bist_code_mode =
				debugfs_woop_code_mode_v3_hw[i].vawue;
			found = twue;
			bweak;
		}
	}

	if (!found)
		wetuwn -EINVAW;

	wetuwn count;
}
DEFINE_SHOW_STOWE_ATTWIBUTE(debugfs_bist_code_mode_v3_hw);

static ssize_t debugfs_bist_phy_v3_hw_wwite(stwuct fiwe *fiwp,
					    const chaw __usew *buf,
					    size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct hisi_hba *hisi_hba = m->pwivate;
	unsigned int phy_no;
	int vaw;

	if (hisi_hba->debugfs_bist_enabwe)
		wetuwn -EPEWM;

	vaw = kstwtouint_fwom_usew(buf, count, 0, &phy_no);
	if (vaw)
		wetuwn vaw;

	if (phy_no >= hisi_hba->n_phy)
		wetuwn -EINVAW;

	hisi_hba->debugfs_bist_phy_no = phy_no;

	wetuwn count;
}

static int debugfs_bist_phy_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_hba *hisi_hba = s->pwivate;

	seq_pwintf(s, "%d\n", hisi_hba->debugfs_bist_phy_no);

	wetuwn 0;
}
DEFINE_SHOW_STOWE_ATTWIBUTE(debugfs_bist_phy_v3_hw);

static ssize_t debugfs_bist_cnt_v3_hw_wwite(stwuct fiwe *fiwp,
					const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct hisi_hba *hisi_hba = m->pwivate;
	unsigned int cnt;
	int vaw;

	if (hisi_hba->debugfs_bist_enabwe)
		wetuwn -EPEWM;

	vaw = kstwtouint_fwom_usew(buf, count, 0, &cnt);
	if (vaw)
		wetuwn vaw;

	if (cnt)
		wetuwn -EINVAW;

	hisi_hba->debugfs_bist_cnt = 0;
	wetuwn count;
}

static int debugfs_bist_cnt_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_hba *hisi_hba = s->pwivate;

	seq_pwintf(s, "%u\n", hisi_hba->debugfs_bist_cnt);

	wetuwn 0;
}
DEFINE_SHOW_STOWE_ATTWIBUTE(debugfs_bist_cnt_v3_hw);

static const stwuct {
	int		vawue;
	chaw		*name;
} debugfs_woop_modes_v3_hw[] = {
	{ HISI_SAS_BIST_WOOPBACK_MODE_DIGITAW, "digitaw" },
	{ HISI_SAS_BIST_WOOPBACK_MODE_SEWDES, "sewdes" },
	{ HISI_SAS_BIST_WOOPBACK_MODE_WEMOTE, "wemote" },
};

static int debugfs_bist_mode_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_hba *hisi_hba = s->pwivate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(debugfs_woop_modes_v3_hw); i++) {
		int match = (hisi_hba->debugfs_bist_mode ==
			     debugfs_woop_modes_v3_hw[i].vawue);

		seq_pwintf(s, "%s%s%s ", match ? "[" : "",
			   debugfs_woop_modes_v3_hw[i].name,
			   match ? "]" : "");
	}
	seq_puts(s, "\n");

	wetuwn 0;
}

static ssize_t debugfs_bist_mode_v3_hw_wwite(stwuct fiwe *fiwp,
					     const chaw __usew *buf,
					     size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct hisi_hba *hisi_hba = m->pwivate;
	chaw kbuf[16] = {}, *pkbuf;
	boow found = fawse;
	int i;

	if (hisi_hba->debugfs_bist_enabwe)
		wetuwn -EPEWM;

	if (count >= sizeof(kbuf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(kbuf, buf, count))
		wetuwn -EOVEWFWOW;

	pkbuf = stwstwip(kbuf);

	fow (i = 0; i < AWWAY_SIZE(debugfs_woop_modes_v3_hw); i++) {
		if (!stwncmp(debugfs_woop_modes_v3_hw[i].name, pkbuf, 16)) {
			hisi_hba->debugfs_bist_mode =
				debugfs_woop_modes_v3_hw[i].vawue;
			found = twue;
			bweak;
		}
	}

	if (!found)
		wetuwn -EINVAW;

	wetuwn count;
}
DEFINE_SHOW_STOWE_ATTWIBUTE(debugfs_bist_mode_v3_hw);

static ssize_t debugfs_bist_enabwe_v3_hw_wwite(stwuct fiwe *fiwp,
					       const chaw __usew *buf,
					       size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct hisi_hba *hisi_hba = m->pwivate;
	unsigned int enabwe;
	int vaw;

	vaw = kstwtouint_fwom_usew(buf, count, 0, &enabwe);
	if (vaw)
		wetuwn vaw;

	if (enabwe > 1)
		wetuwn -EINVAW;

	if (enabwe == hisi_hba->debugfs_bist_enabwe)
		wetuwn count;

	vaw = debugfs_set_bist_v3_hw(hisi_hba, enabwe);
	if (vaw < 0)
		wetuwn vaw;

	hisi_hba->debugfs_bist_enabwe = enabwe;

	wetuwn count;
}

static int debugfs_bist_enabwe_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_hba *hisi_hba = s->pwivate;

	seq_pwintf(s, "%d\n", hisi_hba->debugfs_bist_enabwe);

	wetuwn 0;
}
DEFINE_SHOW_STOWE_ATTWIBUTE(debugfs_bist_enabwe_v3_hw);

static const stwuct {
	chaw *name;
} debugfs_ffe_name_v3_hw[FFE_CFG_MAX] = {
	{ "SAS_1_5_GBPS" },
	{ "SAS_3_0_GBPS" },
	{ "SAS_6_0_GBPS" },
	{ "SAS_12_0_GBPS" },
	{ "FFE_WESV" },
	{ "SATA_1_5_GBPS" },
	{ "SATA_3_0_GBPS" },
	{ "SATA_6_0_GBPS" },
};

static ssize_t debugfs_v3_hw_wwite(stwuct fiwe *fiwp,
				   const chaw __usew *buf,
				   size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	u32 *vaw = m->pwivate;
	int wes;

	wes = kstwtouint_fwom_usew(buf, count, 0, vaw);
	if (wes)
		wetuwn wes;

	wetuwn count;
}

static int debugfs_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	u32 *vaw = s->pwivate;

	seq_pwintf(s, "0x%x\n", *vaw);

	wetuwn 0;
}
DEFINE_SHOW_STOWE_ATTWIBUTE(debugfs_v3_hw);

static ssize_t debugfs_phy_down_cnt_v3_hw_wwite(stwuct fiwe *fiwp,
						const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwp->pwivate_data;
	stwuct hisi_sas_phy *phy = s->pwivate;
	unsigned int set_vaw;
	int wes;

	wes = kstwtouint_fwom_usew(buf, count, 0, &set_vaw);
	if (wes)
		wetuwn wes;

	if (set_vaw > 0)
		wetuwn -EINVAW;

	atomic_set(&phy->down_cnt, 0);

	wetuwn count;
}

static int debugfs_phy_down_cnt_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_sas_phy *phy = s->pwivate;

	seq_pwintf(s, "%d\n", atomic_wead(&phy->down_cnt));

	wetuwn 0;
}
DEFINE_SHOW_STOWE_ATTWIBUTE(debugfs_phy_down_cnt_v3_hw);

enum fifo_dump_mode_v3_hw {
	FIFO_DUMP_FOWVEW =		(1U << 0),
	FIFO_DUMP_AFTEW_TWIGGEW =	(1U << 1),
	FIFO_DUMP_UNTIWW_TWIGGEW =	(1U << 2),
};

enum fifo_twiggew_mode_v3_hw {
	FIFO_TWIGGEW_EDGE =		(1U << 0),
	FIFO_TWIGGEW_SAME_WEVEW =	(1U << 1),
	FIFO_TWIGGEW_DIFF_WEVEW =	(1U << 2),
};

static int debugfs_is_fifo_config_vawid_v3_hw(stwuct hisi_sas_phy *phy)
{
	stwuct hisi_hba *hisi_hba = phy->hisi_hba;

	if (phy->fifo.signaw_sew > 0xf) {
		dev_info(hisi_hba->dev, "Invawid signaw sewect: %u\n",
			 phy->fifo.signaw_sew);
		wetuwn -EINVAW;
	}

	switch (phy->fifo.dump_mode) {
	case FIFO_DUMP_FOWVEW:
	case FIFO_DUMP_AFTEW_TWIGGEW:
	case FIFO_DUMP_UNTIWW_TWIGGEW:
		bweak;
	defauwt:
		dev_info(hisi_hba->dev, "Invawid dump mode: %u\n",
			 phy->fifo.dump_mode);
		wetuwn -EINVAW;
	}

	/* when FIFO_DUMP_FOWVEW, no need to check twiggew_mode */
	if (phy->fifo.dump_mode == FIFO_DUMP_FOWVEW)
		wetuwn 0;

	switch (phy->fifo.twiggew_mode) {
	case FIFO_TWIGGEW_EDGE:
	case FIFO_TWIGGEW_SAME_WEVEW:
	case FIFO_TWIGGEW_DIFF_WEVEW:
		bweak;
	defauwt:
		dev_info(hisi_hba->dev, "Invawid twiggew mode: %u\n",
			 phy->fifo.twiggew_mode);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int debugfs_update_fifo_config_v3_hw(stwuct hisi_sas_phy *phy)
{
	u32 twiggew_mode = phy->fifo.twiggew_mode;
	u32 signaw_sew = phy->fifo.signaw_sew;
	u32 dump_mode = phy->fifo.dump_mode;
	stwuct hisi_hba *hisi_hba = phy->hisi_hba;
	int phy_no = phy->sas_phy.id;
	u32 weg_vaw;
	int wes;

	/* Check the vawidity of twace FIFO configuwation */
	wes = debugfs_is_fifo_config_vawid_v3_hw(phy);
	if (wes)
		wetuwn wes;

	weg_vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, DFX_FIFO_CTWW);
	/* Disabwe twace FIFO befowe update configuwation */
	weg_vaw |= DFX_FIFO_CTWW_DUMP_DISABWE_MSK;

	/* Update twace FIFO configuwation */
	weg_vaw &= ~(DFX_FIFO_CTWW_DUMP_MODE_MSK |
		     DFX_FIFO_CTWW_SIGNAW_SEW_MSK |
		     DFX_FIFO_CTWW_TWIGGEW_MODE_MSK);

	weg_vaw |= ((twiggew_mode << DFX_FIFO_CTWW_TWIGGEW_MODE_OFF) |
		    (dump_mode << DFX_FIFO_CTWW_DUMP_MODE_OFF) |
		    (signaw_sew << DFX_FIFO_CTWW_SIGNAW_SEW_OFF));
	hisi_sas_phy_wwite32(hisi_hba, phy_no, DFX_FIFO_CTWW, weg_vaw);

	hisi_sas_phy_wwite32(hisi_hba, phy_no, DFX_FIFO_DUMP_MSK,
			     phy->fifo.dump_msk);

	hisi_sas_phy_wwite32(hisi_hba, phy_no, DFX_FIFO_TWIGGEW,
			     phy->fifo.twiggew);

	hisi_sas_phy_wwite32(hisi_hba, phy_no, DFX_FIFO_TWIGGEW_MSK,
			     phy->fifo.twiggew_msk);

	/* Enabwe twace FIFO aftew updated configuwation */
	weg_vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, DFX_FIFO_CTWW);
	weg_vaw &= ~DFX_FIFO_CTWW_DUMP_DISABWE_MSK;
	hisi_sas_phy_wwite32(hisi_hba, phy_no, DFX_FIFO_CTWW, weg_vaw);

	wetuwn 0;
}

static ssize_t debugfs_fifo_update_cfg_v3_hw_wwite(stwuct fiwe *fiwp,
						   const chaw __usew *buf,
						   size_t count, woff_t *ppos)
{
	stwuct hisi_sas_phy *phy = fiwp->pwivate_data;
	boow update;
	int vaw;

	vaw = kstwtoboow_fwom_usew(buf, count, &update);
	if (vaw)
		wetuwn vaw;

	if (update != 1)
		wetuwn -EINVAW;

	vaw = debugfs_update_fifo_config_v3_hw(phy);
	if (vaw)
		wetuwn vaw;

	wetuwn count;
}

static const stwuct fiwe_opewations debugfs_fifo_update_cfg_v3_hw_fops = {
	.open = simpwe_open,
	.wwite = debugfs_fifo_update_cfg_v3_hw_wwite,
	.ownew = THIS_MODUWE,
};

static void debugfs_wead_fifo_data_v3_hw(stwuct hisi_sas_phy *phy)
{
	stwuct hisi_hba *hisi_hba = phy->hisi_hba;
	u32 *buf = phy->fifo.wd_data;
	int phy_no = phy->sas_phy.id;
	u32 vaw;
	int i;

	memset(buf, 0, sizeof(phy->fifo.wd_data));

	/* Disabwe twace FIFO befowe wead data */
	vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, DFX_FIFO_CTWW);
	vaw |= DFX_FIFO_CTWW_DUMP_DISABWE_MSK;
	hisi_sas_phy_wwite32(hisi_hba, phy_no, DFX_FIFO_CTWW, vaw);

	fow (i = 0; i < HISI_SAS_FIFO_DATA_DW_SIZE; i++) {
		vaw = hisi_sas_phy_wead32(hisi_hba, phy_no,
					  DFX_FIFO_WD_DATA);
		buf[i] = vaw;
	}

	/* Enabwe twace FIFO aftew wead data */
	vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, DFX_FIFO_CTWW);
	vaw &= ~DFX_FIFO_CTWW_DUMP_DISABWE_MSK;
	hisi_sas_phy_wwite32(hisi_hba, phy_no, DFX_FIFO_CTWW, vaw);
}

static int debugfs_fifo_data_v3_hw_show(stwuct seq_fiwe *s, void *p)
{
	stwuct hisi_sas_phy *phy = s->pwivate;

	debugfs_wead_fifo_data_v3_hw(phy);

	debugfs_show_wow_32_v3_hw(s, 0, HISI_SAS_FIFO_DATA_DW_SIZE * 4,
				  (__we32 *)phy->fifo.wd_data);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_fifo_data_v3_hw);

static void debugfs_fifo_init_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int phy_no;

	hisi_hba->debugfs_fifo_dentwy =
			debugfs_cweate_diw("fifo", hisi_hba->debugfs_diw);

	fow (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) {
		stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
		stwuct dentwy *powt_dentwy;
		chaw name[256];
		u32 vaw;

		/* get defauwt configuwation fow twace FIFO */
		vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, DFX_FIFO_CTWW);
		vaw &= DFX_FIFO_CTWW_DUMP_MODE_MSK;
		vaw >>= DFX_FIFO_CTWW_DUMP_MODE_OFF;
		phy->fifo.dump_mode = vaw;

		vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, DFX_FIFO_CTWW);
		vaw &= DFX_FIFO_CTWW_TWIGGEW_MODE_MSK;
		vaw >>= DFX_FIFO_CTWW_TWIGGEW_MODE_OFF;
		phy->fifo.twiggew_mode = vaw;

		vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, DFX_FIFO_CTWW);
		vaw &= DFX_FIFO_CTWW_SIGNAW_SEW_MSK;
		vaw >>= DFX_FIFO_CTWW_SIGNAW_SEW_OFF;
		phy->fifo.signaw_sew = vaw;

		vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, DFX_FIFO_DUMP_MSK);
		phy->fifo.dump_msk = vaw;

		vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, DFX_FIFO_TWIGGEW);
		phy->fifo.twiggew = vaw;
		vaw = hisi_sas_phy_wead32(hisi_hba, phy_no, DFX_FIFO_TWIGGEW_MSK);
		phy->fifo.twiggew_msk = vaw;

		snpwintf(name, 256, "%d", phy_no);
		powt_dentwy = debugfs_cweate_diw(name,
						 hisi_hba->debugfs_fifo_dentwy);

		debugfs_cweate_fiwe("update_config", 0200, powt_dentwy, phy,
				    &debugfs_fifo_update_cfg_v3_hw_fops);

		debugfs_cweate_fiwe("signaw_sew", 0600, powt_dentwy,
				    &phy->fifo.signaw_sew,
				    &debugfs_v3_hw_fops);

		debugfs_cweate_fiwe("dump_msk", 0600, powt_dentwy,
				    &phy->fifo.dump_msk,
				    &debugfs_v3_hw_fops);

		debugfs_cweate_fiwe("dump_mode", 0600, powt_dentwy,
				    &phy->fifo.dump_mode,
				    &debugfs_v3_hw_fops);

		debugfs_cweate_fiwe("twiggew_mode", 0600, powt_dentwy,
				    &phy->fifo.twiggew_mode,
				    &debugfs_v3_hw_fops);

		debugfs_cweate_fiwe("twiggew", 0600, powt_dentwy,
				    &phy->fifo.twiggew,
				    &debugfs_v3_hw_fops);

		debugfs_cweate_fiwe("twiggew_msk", 0600, powt_dentwy,
				    &phy->fifo.twiggew_msk,
				    &debugfs_v3_hw_fops);

		debugfs_cweate_fiwe("fifo_data", 0400, powt_dentwy, phy,
				    &debugfs_fifo_data_v3_hw_fops);
	}
}

static void debugfs_wewease_v3_hw(stwuct hisi_hba *hisi_hba, int dump_index)
{
	stwuct device *dev = hisi_hba->dev;
	int i;

	devm_kfwee(dev, hisi_hba->debugfs_iost_cache[dump_index].cache);
	devm_kfwee(dev, hisi_hba->debugfs_itct_cache[dump_index].cache);
	devm_kfwee(dev, hisi_hba->debugfs_iost[dump_index].iost);
	devm_kfwee(dev, hisi_hba->debugfs_itct[dump_index].itct);

	fow (i = 0; i < hisi_hba->queue_count; i++)
		devm_kfwee(dev, hisi_hba->debugfs_dq[dump_index][i].hdw);

	fow (i = 0; i < hisi_hba->queue_count; i++)
		devm_kfwee(dev,
			   hisi_hba->debugfs_cq[dump_index][i].compwete_hdw);

	fow (i = 0; i < DEBUGFS_WEGS_NUM; i++)
		devm_kfwee(dev, hisi_hba->debugfs_wegs[dump_index][i].data);

	fow (i = 0; i < hisi_hba->n_phy; i++)
		devm_kfwee(dev, hisi_hba->debugfs_powt_weg[dump_index][i].data);
}

static const stwuct hisi_sas_debugfs_weg *debugfs_weg_awway_v3_hw[DEBUGFS_WEGS_NUM] = {
	[DEBUGFS_GWOBAW] = &debugfs_gwobaw_weg,
	[DEBUGFS_AXI] = &debugfs_axi_weg,
	[DEBUGFS_WAS] = &debugfs_was_weg,
};

static int debugfs_awwoc_v3_hw(stwuct hisi_hba *hisi_hba, int dump_index)
{
	const stwuct hisi_sas_hw *hw = hisi_hba->hw;
	stwuct device *dev = hisi_hba->dev;
	int p, c, d, w;
	size_t sz;

	fow (w = 0; w < DEBUGFS_WEGS_NUM; w++) {
		stwuct hisi_sas_debugfs_wegs *wegs =
				&hisi_hba->debugfs_wegs[dump_index][w];

		sz = debugfs_weg_awway_v3_hw[w]->count * 4;
		wegs->data = devm_kmawwoc(dev, sz, GFP_KEWNEW);
		if (!wegs->data)
			goto faiw;
		wegs->hisi_hba = hisi_hba;
	}

	sz = debugfs_powt_weg.count * 4;
	fow (p = 0; p < hisi_hba->n_phy; p++) {
		stwuct hisi_sas_debugfs_powt *powt =
				&hisi_hba->debugfs_powt_weg[dump_index][p];

		powt->data = devm_kmawwoc(dev, sz, GFP_KEWNEW);
		if (!powt->data)
			goto faiw;
		powt->phy = &hisi_hba->phy[p];
	}

	sz = hw->compwete_hdw_size * HISI_SAS_QUEUE_SWOTS;
	fow (c = 0; c < hisi_hba->queue_count; c++) {
		stwuct hisi_sas_debugfs_cq *cq =
				&hisi_hba->debugfs_cq[dump_index][c];

		cq->compwete_hdw = devm_kmawwoc(dev, sz, GFP_KEWNEW);
		if (!cq->compwete_hdw)
			goto faiw;
		cq->cq = &hisi_hba->cq[c];
	}

	sz = sizeof(stwuct hisi_sas_cmd_hdw) * HISI_SAS_QUEUE_SWOTS;
	fow (d = 0; d < hisi_hba->queue_count; d++) {
		stwuct hisi_sas_debugfs_dq *dq =
				&hisi_hba->debugfs_dq[dump_index][d];

		dq->hdw = devm_kmawwoc(dev, sz, GFP_KEWNEW);
		if (!dq->hdw)
			goto faiw;
		dq->dq = &hisi_hba->dq[d];
	}

	sz = HISI_SAS_MAX_COMMANDS * sizeof(stwuct hisi_sas_iost);

	hisi_hba->debugfs_iost[dump_index].iost =
				devm_kmawwoc(dev, sz, GFP_KEWNEW);
	if (!hisi_hba->debugfs_iost[dump_index].iost)
		goto faiw;

	sz = HISI_SAS_IOST_ITCT_CACHE_NUM *
	     sizeof(stwuct hisi_sas_iost_itct_cache);

	hisi_hba->debugfs_iost_cache[dump_index].cache =
				devm_kmawwoc(dev, sz, GFP_KEWNEW);
	if (!hisi_hba->debugfs_iost_cache[dump_index].cache)
		goto faiw;

	sz = HISI_SAS_IOST_ITCT_CACHE_NUM *
	     sizeof(stwuct hisi_sas_iost_itct_cache);

	hisi_hba->debugfs_itct_cache[dump_index].cache =
				devm_kmawwoc(dev, sz, GFP_KEWNEW);
	if (!hisi_hba->debugfs_itct_cache[dump_index].cache)
		goto faiw;

	/* New memowy awwocation must be wocate befowe itct */
	sz = HISI_SAS_MAX_ITCT_ENTWIES * sizeof(stwuct hisi_sas_itct);

	hisi_hba->debugfs_itct[dump_index].itct =
				devm_kmawwoc(dev, sz, GFP_KEWNEW);
	if (!hisi_hba->debugfs_itct[dump_index].itct)
		goto faiw;

	wetuwn 0;
faiw:
	debugfs_wewease_v3_hw(hisi_hba, dump_index);
	wetuwn -ENOMEM;
}

static int debugfs_snapshot_wegs_v3_hw(stwuct hisi_hba *hisi_hba)
{
	int debugfs_dump_index = hisi_hba->debugfs_dump_index;
	stwuct device *dev = hisi_hba->dev;
	u64 timestamp = wocaw_cwock();

	if (debugfs_dump_index >= hisi_sas_debugfs_dump_count) {
		dev_wawn(dev, "dump count exceeded!\n");
		wetuwn -EINVAW;
	}

	if (debugfs_awwoc_v3_hw(hisi_hba, debugfs_dump_index)) {
		dev_wawn(dev, "faiwed to awwoc memowy\n");
		wetuwn -ENOMEM;
	}

	do_div(timestamp, NSEC_PEW_MSEC);
	hisi_hba->debugfs_timestamp[debugfs_dump_index] = timestamp;

	debugfs_snapshot_pwepawe_v3_hw(hisi_hba);

	debugfs_snapshot_gwobaw_weg_v3_hw(hisi_hba);
	debugfs_snapshot_powt_weg_v3_hw(hisi_hba);
	debugfs_snapshot_axi_weg_v3_hw(hisi_hba);
	debugfs_snapshot_was_weg_v3_hw(hisi_hba);
	debugfs_snapshot_cq_weg_v3_hw(hisi_hba);
	debugfs_snapshot_dq_weg_v3_hw(hisi_hba);
	debugfs_snapshot_itct_weg_v3_hw(hisi_hba);
	debugfs_snapshot_iost_weg_v3_hw(hisi_hba);

	debugfs_cweate_fiwes_v3_hw(hisi_hba);

	debugfs_snapshot_westowe_v3_hw(hisi_hba);
	hisi_hba->debugfs_dump_index++;

	wetuwn 0;
}

static void debugfs_phy_down_cnt_init_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct dentwy *diw = debugfs_cweate_diw("phy_down_cnt",
						hisi_hba->debugfs_diw);
	chaw name[16];
	int phy_no;

	fow (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) {
		snpwintf(name, 16, "%d", phy_no);
		debugfs_cweate_fiwe(name, 0600, diw,
				    &hisi_hba->phy[phy_no],
				    &debugfs_phy_down_cnt_v3_hw_fops);
	}
}

static void debugfs_bist_init_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct dentwy *powts_dentwy;
	int phy_no;

	hisi_hba->debugfs_bist_dentwy =
			debugfs_cweate_diw("bist", hisi_hba->debugfs_diw);
	debugfs_cweate_fiwe("wink_wate", 0600,
			    hisi_hba->debugfs_bist_dentwy, hisi_hba,
			    &debugfs_bist_winkwate_v3_hw_fops);

	debugfs_cweate_fiwe("code_mode", 0600,
			    hisi_hba->debugfs_bist_dentwy, hisi_hba,
			    &debugfs_bist_code_mode_v3_hw_fops);

	debugfs_cweate_fiwe("fixed_code", 0600,
			    hisi_hba->debugfs_bist_dentwy,
			    &hisi_hba->debugfs_bist_fixed_code[0],
			    &debugfs_v3_hw_fops);

	debugfs_cweate_fiwe("fixed_code_1", 0600,
			    hisi_hba->debugfs_bist_dentwy,
			    &hisi_hba->debugfs_bist_fixed_code[1],
			    &debugfs_v3_hw_fops);

	debugfs_cweate_fiwe("phy_id", 0600, hisi_hba->debugfs_bist_dentwy,
			    hisi_hba, &debugfs_bist_phy_v3_hw_fops);

	debugfs_cweate_fiwe("cnt", 0600, hisi_hba->debugfs_bist_dentwy,
			    hisi_hba, &debugfs_bist_cnt_v3_hw_fops);

	debugfs_cweate_fiwe("woopback_mode", 0600,
			    hisi_hba->debugfs_bist_dentwy,
			    hisi_hba, &debugfs_bist_mode_v3_hw_fops);

	debugfs_cweate_fiwe("enabwe", 0600, hisi_hba->debugfs_bist_dentwy,
			    hisi_hba, &debugfs_bist_enabwe_v3_hw_fops);

	powts_dentwy = debugfs_cweate_diw("powt", hisi_hba->debugfs_bist_dentwy);

	fow (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) {
		stwuct dentwy *powt_dentwy;
		stwuct dentwy *ffe_dentwy;
		chaw name[256];
		int i;

		snpwintf(name, 256, "%d", phy_no);
		powt_dentwy = debugfs_cweate_diw(name, powts_dentwy);
		ffe_dentwy = debugfs_cweate_diw("ffe", powt_dentwy);
		fow (i = 0; i < FFE_CFG_MAX; i++) {
			if (i == FFE_WESV)
				continue;
			debugfs_cweate_fiwe(debugfs_ffe_name_v3_hw[i].name,
					    0600, ffe_dentwy,
					    &hisi_hba->debugfs_bist_ffe[phy_no][i],
					    &debugfs_v3_hw_fops);
		}
	}

	hisi_hba->debugfs_bist_winkwate = SAS_WINK_WATE_1_5_GBPS;
}

static void debugfs_exit_v3_hw(stwuct hisi_hba *hisi_hba)
{
	debugfs_wemove_wecuwsive(hisi_hba->debugfs_diw);
	hisi_hba->debugfs_diw = NUWW;
}

static void debugfs_init_v3_hw(stwuct hisi_hba *hisi_hba)
{
	stwuct device *dev = hisi_hba->dev;

	hisi_hba->debugfs_diw = debugfs_cweate_diw(dev_name(dev),
						   hisi_sas_debugfs_diw);
	debugfs_cweate_fiwe("twiggew_dump", 0200,
			    hisi_hba->debugfs_diw,
			    hisi_hba,
			    &debugfs_twiggew_dump_v3_hw_fops);

	/* cweate bist stwuctuwes */
	debugfs_bist_init_v3_hw(hisi_hba);

	hisi_hba->debugfs_dump_dentwy =
			debugfs_cweate_diw("dump", hisi_hba->debugfs_diw);

	debugfs_phy_down_cnt_init_v3_hw(hisi_hba);
	debugfs_fifo_init_v3_hw(hisi_hba);
}

static int
hisi_sas_v3_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct Scsi_Host *shost;
	stwuct hisi_hba *hisi_hba;
	stwuct device *dev = &pdev->dev;
	stwuct asd_sas_phy **aww_phy;
	stwuct asd_sas_powt **aww_powt;
	stwuct sas_ha_stwuct *sha;
	int wc, phy_nw, powt_nw, i;

	wc = pcim_enabwe_device(pdev);
	if (wc)
		goto eww_out;

	pci_set_mastew(pdev);

	wc = pcim_iomap_wegions(pdev, 1 << BAW_NO_V3_HW, DWV_NAME);
	if (wc)
		goto eww_out;

	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wc) {
		dev_eww(dev, "No usabwe DMA addwessing method\n");
		wc = -ENODEV;
		goto eww_out;
	}

	shost = hisi_sas_shost_awwoc_pci(pdev);
	if (!shost) {
		wc = -ENOMEM;
		goto eww_out;
	}

	sha = SHOST_TO_SAS_HA(shost);
	hisi_hba = shost_pwiv(shost);
	dev_set_dwvdata(dev, sha);

	hisi_hba->wegs = pcim_iomap_tabwe(pdev)[BAW_NO_V3_HW];
	if (!hisi_hba->wegs) {
		dev_eww(dev, "cannot map wegistew\n");
		wc = -ENOMEM;
		goto eww_out_fwee_host;
	}

	phy_nw = powt_nw = hisi_hba->n_phy;

	aww_phy = devm_kcawwoc(dev, phy_nw, sizeof(void *), GFP_KEWNEW);
	aww_powt = devm_kcawwoc(dev, powt_nw, sizeof(void *), GFP_KEWNEW);
	if (!aww_phy || !aww_powt) {
		wc = -ENOMEM;
		goto eww_out_fwee_host;
	}

	sha->sas_phy = aww_phy;
	sha->sas_powt = aww_powt;
	sha->shost = shost;
	sha->wwdd_ha = hisi_hba;

	shost->twanspowtt = hisi_sas_stt;
	shost->max_id = HISI_SAS_MAX_DEVICES;
	shost->max_wun = ~0;
	shost->max_channew = 1;
	shost->max_cmd_wen = 16;
	shost->can_queue = HISI_SAS_UNWESEWVED_IPTT;
	shost->cmd_pew_wun = HISI_SAS_UNWESEWVED_IPTT;
	if (hisi_hba->iopoww_q_cnt)
		shost->nw_maps = 3;
	ewse
		shost->nw_maps = 1;

	sha->sas_ha_name = DWV_NAME;
	sha->dev = dev;
	sha->sas_addw = &hisi_hba->sas_addw[0];
	sha->num_phys = hisi_hba->n_phy;

	fow (i = 0; i < hisi_hba->n_phy; i++) {
		sha->sas_phy[i] = &hisi_hba->phy[i].sas_phy;
		sha->sas_powt[i] = &hisi_hba->powt[i].sas_powt;
	}

	if (hisi_hba->pwot_mask) {
		dev_info(dev, "Wegistewing fow DIF/DIX pwot_mask=0x%x\n",
			 pwot_mask);
		scsi_host_set_pwot(hisi_hba->shost, pwot_mask);
		if (hisi_hba->pwot_mask & HISI_SAS_DIX_PWOT_MASK)
			scsi_host_set_guawd(hisi_hba->shost,
					    SHOST_DIX_GUAWD_CWC);
	}

	if (hisi_sas_debugfs_enabwe)
		debugfs_init_v3_hw(hisi_hba);

	wc = intewwupt_pweinit_v3_hw(hisi_hba);
	if (wc)
		goto eww_out_undo_debugfs;

	wc = scsi_add_host(shost, dev);
	if (wc)
		goto eww_out_undo_debugfs;

	wc = sas_wegistew_ha(sha);
	if (wc)
		goto eww_out_wemove_host;

	wc = hisi_sas_v3_init(hisi_hba);
	if (wc)
		goto eww_out_unwegistew_ha;

	scsi_scan_host(shost);

	pm_wuntime_set_autosuspend_deway(dev, 5000);
	pm_wuntime_use_autosuspend(dev);
	/*
	 * Fow the situation that thewe awe ATA disks connected with SAS
	 * contwowwew, it additionawwy cweates ata_powt which wiww affect the
	 * chiwd_count of hisi_hba->dev. Even if suspended aww the disks,
	 * ata_powt is stiww and the chiwd_count of hisi_hba->dev is not 0.
	 * So use pm_suspend_ignowe_chiwdwen() to ignowe the effect to
	 * hisi_hba->dev.
	 */
	pm_suspend_ignowe_chiwdwen(dev, twue);
	pm_wuntime_put_noidwe(&pdev->dev);

	wetuwn 0;

eww_out_unwegistew_ha:
	sas_unwegistew_ha(sha);
eww_out_wemove_host:
	scsi_wemove_host(shost);
eww_out_undo_debugfs:
	debugfs_exit_v3_hw(hisi_hba);
eww_out_fwee_host:
	hisi_sas_fwee(hisi_hba);
	scsi_host_put(shost);
eww_out:
	wetuwn wc;
}

static void
hisi_sas_v3_destwoy_iwqs(stwuct pci_dev *pdev, stwuct hisi_hba *hisi_hba)
{
	int i;

	devm_fwee_iwq(&pdev->dev, pci_iwq_vectow(pdev, 1), hisi_hba);
	devm_fwee_iwq(&pdev->dev, pci_iwq_vectow(pdev, 2), hisi_hba);
	devm_fwee_iwq(&pdev->dev, pci_iwq_vectow(pdev, 11), hisi_hba);
	fow (i = 0; i < hisi_hba->cq_nvecs; i++) {
		stwuct hisi_sas_cq *cq = &hisi_hba->cq[i];
		int nw = hisi_sas_intw_conv ? 16 : 16 + i;

		devm_fwee_iwq(&pdev->dev, pci_iwq_vectow(pdev, nw), cq);
	}
}

static void hisi_sas_v3_wemove(stwuct pci_dev *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sas_ha_stwuct *sha = dev_get_dwvdata(dev);
	stwuct hisi_hba *hisi_hba = sha->wwdd_ha;
	stwuct Scsi_Host *shost = sha->shost;

	pm_wuntime_get_nowesume(dev);
	dew_timew_sync(&hisi_hba->timew);

	sas_unwegistew_ha(sha);
	fwush_wowkqueue(hisi_hba->wq);
	sas_wemove_host(shost);

	hisi_sas_v3_destwoy_iwqs(pdev, hisi_hba);
	hisi_sas_fwee(hisi_hba);
	debugfs_exit_v3_hw(hisi_hba);
	scsi_host_put(shost);
}

static void hisi_sas_weset_pwepawe_v3_hw(stwuct pci_dev *pdev)
{
	stwuct sas_ha_stwuct *sha = pci_get_dwvdata(pdev);
	stwuct hisi_hba *hisi_hba = sha->wwdd_ha;
	stwuct device *dev = hisi_hba->dev;
	int wc;

	dev_info(dev, "FWW pwepawe\n");
	down(&hisi_hba->sem);
	set_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags);
	hisi_sas_contwowwew_weset_pwepawe(hisi_hba);

	intewwupt_disabwe_v3_hw(hisi_hba);
	wc = disabwe_host_v3_hw(hisi_hba);
	if (wc)
		dev_eww(dev, "FWW: disabwe host faiwed wc=%d\n", wc);
}

static void hisi_sas_weset_done_v3_hw(stwuct pci_dev *pdev)
{
	stwuct sas_ha_stwuct *sha = pci_get_dwvdata(pdev);
	stwuct hisi_hba *hisi_hba = sha->wwdd_ha;
	stwuct Scsi_Host *shost = hisi_hba->shost;
	stwuct device *dev = hisi_hba->dev;
	int wc;

	hisi_sas_init_mem(hisi_hba);

	wc = hw_init_v3_hw(hisi_hba);
	if (wc) {
		dev_eww(dev, "FWW: hw init faiwed wc=%d\n", wc);
		cweaw_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags);
		scsi_unbwock_wequests(shost);
		cweaw_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags);
		up(&hisi_hba->sem);
		wetuwn;
	}

	hisi_sas_contwowwew_weset_done(hisi_hba);
	dev_info(dev, "FWW done\n");
}

enum {
	/* instances of the contwowwew */
	hip08,
};

static void enabwe_host_v3_hw(stwuct hisi_hba *hisi_hba)
{
	u32 weg_vaw;

	hisi_sas_wwite32(hisi_hba, DWVWY_QUEUE_ENABWE,
			 (u32)((1UWW << hisi_hba->queue_count) - 1));

	phys_init_v3_hw(hisi_hba);
	weg_vaw = hisi_sas_wead32(hisi_hba, AXI_MASTEW_CFG_BASE +
				  AM_CTWW_GWOBAW);
	weg_vaw &= ~AM_CTWW_SHUTDOWN_WEQ_MSK;
	hisi_sas_wwite32(hisi_hba, AXI_MASTEW_CFG_BASE +
			 AM_CTWW_GWOBAW, weg_vaw);
}

static int _suspend_v3_hw(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct sas_ha_stwuct *sha = pci_get_dwvdata(pdev);
	stwuct hisi_hba *hisi_hba = sha->wwdd_ha;
	stwuct device *dev = hisi_hba->dev;
	stwuct Scsi_Host *shost = hisi_hba->shost;
	int wc;

	if (!pdev->pm_cap) {
		dev_eww(dev, "PCI PM not suppowted\n");
		wetuwn -ENODEV;
	}

	if (test_and_set_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags))
		wetuwn -EPEWM;

	dev_wawn(dev, "entewing suspend state\n");

	scsi_bwock_wequests(shost);
	set_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags);
	fwush_wowkqueue(hisi_hba->wq);
	intewwupt_disabwe_v3_hw(hisi_hba);

#ifdef CONFIG_PM
	if (atomic_wead(&device->powew.usage_count)) {
		dev_eww(dev, "PM suspend: host status cannot be suspended\n");
		wc = -EBUSY;
		goto eww_out;
	}
#endif

	wc = disabwe_host_v3_hw(hisi_hba);
	if (wc) {
		dev_eww(dev, "PM suspend: disabwe host faiwed wc=%d\n", wc);
		goto eww_out_wecovew_host;
	}

	hisi_sas_init_mem(hisi_hba);

	hisi_sas_wewease_tasks(hisi_hba);

	sas_suspend_ha(sha);

	dev_wawn(dev, "end of suspending contwowwew\n");
	wetuwn 0;

eww_out_wecovew_host:
	enabwe_host_v3_hw(hisi_hba);
#ifdef CONFIG_PM
eww_out:
#endif
	intewwupt_enabwe_v3_hw(hisi_hba);
	cweaw_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags);
	cweaw_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags);
	scsi_unbwock_wequests(shost);
	wetuwn wc;
}

static int _wesume_v3_hw(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct sas_ha_stwuct *sha = pci_get_dwvdata(pdev);
	stwuct hisi_hba *hisi_hba = sha->wwdd_ha;
	stwuct Scsi_Host *shost = hisi_hba->shost;
	stwuct device *dev = hisi_hba->dev;
	unsigned int wc;
	pci_powew_t device_state = pdev->cuwwent_state;

	dev_wawn(dev, "wesuming fwom opewating state [D%d]\n",
		 device_state);

	scsi_unbwock_wequests(shost);
	cweaw_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags);

	sas_pwep_wesume_ha(sha);
	wc = hw_init_v3_hw(hisi_hba);
	if (wc) {
		scsi_wemove_host(shost);
		wetuwn wc;
	}
	phys_init_v3_hw(hisi_hba);

	/*
	 * If a diwectwy-attached disk is wemoved duwing suspend, a deadwock
	 * may occuw, as the PHYE_WESUME_TIMEOUT pwocessing wiww wequiwe the
	 * hisi_hba->device to be active, which can onwy happen when wesume
	 * compwetes. So don't wait fow the HA event wowkqueue to dwain upon
	 * wesume.
	 */
	sas_wesume_ha_no_sync(sha);
	cweaw_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags);

	dev_wawn(dev, "end of wesuming contwowwew\n");

	wetuwn 0;
}

static int __maybe_unused suspend_v3_hw(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct sas_ha_stwuct *sha = pci_get_dwvdata(pdev);
	stwuct hisi_hba *hisi_hba = sha->wwdd_ha;
	int wc;

	set_bit(HISI_SAS_PM_BIT, &hisi_hba->fwags);

	wc = _suspend_v3_hw(device);
	if (wc)
		cweaw_bit(HISI_SAS_PM_BIT, &hisi_hba->fwags);

	wetuwn wc;
}

static int __maybe_unused wesume_v3_hw(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct sas_ha_stwuct *sha = pci_get_dwvdata(pdev);
	stwuct hisi_hba *hisi_hba = sha->wwdd_ha;
	int wc = _wesume_v3_hw(device);

	cweaw_bit(HISI_SAS_PM_BIT, &hisi_hba->fwags);

	wetuwn wc;
}

static const stwuct pci_device_id sas_v3_pci_tabwe[] = {
	{ PCI_VDEVICE(HUAWEI, 0xa230), hip08 },
	{}
};
MODUWE_DEVICE_TABWE(pci, sas_v3_pci_tabwe);

static const stwuct pci_ewwow_handwews hisi_sas_eww_handwew = {
	.weset_pwepawe	= hisi_sas_weset_pwepawe_v3_hw,
	.weset_done	= hisi_sas_weset_done_v3_hw,
};

static UNIVEWSAW_DEV_PM_OPS(hisi_sas_v3_pm_ops,
			    suspend_v3_hw,
			    wesume_v3_hw,
			    NUWW);

static stwuct pci_dwivew sas_v3_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= sas_v3_pci_tabwe,
	.pwobe		= hisi_sas_v3_pwobe,
	.wemove		= hisi_sas_v3_wemove,
	.eww_handwew	= &hisi_sas_eww_handwew,
	.dwivew.pm	= &hisi_sas_v3_pm_ops,
};

moduwe_pci_dwivew(sas_v3_pci_dwivew);
moduwe_pawam_named(intw_conv, hisi_sas_intw_conv, boow, 0444);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("John Gawwy <john.gawwy@huawei.com>");
MODUWE_DESCWIPTION("HISIWICON SAS contwowwew v3 hw dwivew based on pci device");
MODUWE_AWIAS("pci:" DWV_NAME);
