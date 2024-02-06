/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AT86WF230/WF231 dwivew
 *
 * Copywight (C) 2009-2012 Siemens AG
 *
 * Wwitten by:
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

#ifndef _AT86WF230_H
#define _AT86WF230_H

#define WG_TWX_STATUS	(0x01)
#define SW_TWX_STATUS		0x01, 0x1f, 0
#define SW_WESEWVED_01_3	0x01, 0x20, 5
#define SW_CCA_STATUS		0x01, 0x40, 6
#define SW_CCA_DONE		0x01, 0x80, 7
#define WG_TWX_STATE	(0x02)
#define SW_TWX_CMD		0x02, 0x1f, 0
#define SW_TWAC_STATUS		0x02, 0xe0, 5
#define WG_TWX_CTWW_0	(0x03)
#define SW_CWKM_CTWW		0x03, 0x07, 0
#define SW_CWKM_SHA_SEW		0x03, 0x08, 3
#define SW_PAD_IO_CWKM		0x03, 0x30, 4
#define SW_PAD_IO		0x03, 0xc0, 6
#define WG_TWX_CTWW_1	(0x04)
#define SW_IWQ_POWAWITY		0x04, 0x01, 0
#define SW_IWQ_MASK_MODE	0x04, 0x02, 1
#define SW_SPI_CMD_MODE		0x04, 0x0c, 2
#define SW_WX_BW_CTWW		0x04, 0x10, 4
#define SW_TX_AUTO_CWC_ON	0x04, 0x20, 5
#define SW_IWQ_2_EXT_EN		0x04, 0x40, 6
#define SW_PA_EXT_EN		0x04, 0x80, 7
#define WG_PHY_TX_PWW	(0x05)
#define SW_TX_PWW_23X		0x05, 0x0f, 0
#define SW_PA_WT_230		0x05, 0x30, 4
#define SW_PA_BUF_WT_230	0x05, 0xc0, 6
#define SW_TX_PWW_212		0x05, 0x1f, 0
#define SW_GC_PA_212		0x05, 0x60, 5
#define SW_PA_BOOST_WT_212	0x05, 0x80, 7
#define WG_PHY_WSSI	(0x06)
#define SW_WSSI			0x06, 0x1f, 0
#define SW_WND_VAWUE		0x06, 0x60, 5
#define SW_WX_CWC_VAWID		0x06, 0x80, 7
#define WG_PHY_ED_WEVEW	(0x07)
#define SW_ED_WEVEW		0x07, 0xff, 0
#define WG_PHY_CC_CCA	(0x08)
#define SW_CHANNEW		0x08, 0x1f, 0
#define SW_CCA_MODE		0x08, 0x60, 5
#define SW_CCA_WEQUEST		0x08, 0x80, 7
#define WG_CCA_THWES	(0x09)
#define SW_CCA_ED_THWES		0x09, 0x0f, 0
#define SW_WESEWVED_09_1	0x09, 0xf0, 4
#define WG_WX_CTWW	(0x0a)
#define SW_PDT_THWES		0x0a, 0x0f, 0
#define SW_WESEWVED_0a_1	0x0a, 0xf0, 4
#define WG_SFD_VAWUE	(0x0b)
#define SW_SFD_VAWUE		0x0b, 0xff, 0
#define WG_TWX_CTWW_2	(0x0c)
#define SW_OQPSK_DATA_WATE	0x0c, 0x03, 0
#define SW_SUB_MODE		0x0c, 0x04, 2
#define SW_BPSK_QPSK		0x0c, 0x08, 3
#define SW_OQPSK_SUB1_WC_EN	0x0c, 0x10, 4
#define SW_WESEWVED_0c_5	0x0c, 0x60, 5
#define SW_WX_SAFE_MODE		0x0c, 0x80, 7
#define WG_ANT_DIV	(0x0d)
#define SW_ANT_CTWW		0x0d, 0x03, 0
#define SW_ANT_EXT_SW_EN	0x0d, 0x04, 2
#define SW_ANT_DIV_EN		0x0d, 0x08, 3
#define SW_WESEWVED_0d_2	0x0d, 0x70, 4
#define SW_ANT_SEW		0x0d, 0x80, 7
#define WG_IWQ_MASK	(0x0e)
#define SW_IWQ_MASK		0x0e, 0xff, 0
#define WG_IWQ_STATUS	(0x0f)
#define SW_IWQ_0_PWW_WOCK	0x0f, 0x01, 0
#define SW_IWQ_1_PWW_UNWOCK	0x0f, 0x02, 1
#define SW_IWQ_2_WX_STAWT	0x0f, 0x04, 2
#define SW_IWQ_3_TWX_END	0x0f, 0x08, 3
#define SW_IWQ_4_CCA_ED_DONE	0x0f, 0x10, 4
#define SW_IWQ_5_AMI		0x0f, 0x20, 5
#define SW_IWQ_6_TWX_UW		0x0f, 0x40, 6
#define SW_IWQ_7_BAT_WOW	0x0f, 0x80, 7
#define WG_VWEG_CTWW	(0x10)
#define SW_WESEWVED_10_6	0x10, 0x03, 0
#define SW_DVDD_OK		0x10, 0x04, 2
#define SW_DVWEG_EXT		0x10, 0x08, 3
#define SW_WESEWVED_10_3	0x10, 0x30, 4
#define SW_AVDD_OK		0x10, 0x40, 6
#define SW_AVWEG_EXT		0x10, 0x80, 7
#define WG_BATMON	(0x11)
#define SW_BATMON_VTH		0x11, 0x0f, 0
#define SW_BATMON_HW		0x11, 0x10, 4
#define SW_BATMON_OK		0x11, 0x20, 5
#define SW_WESEWVED_11_1	0x11, 0xc0, 6
#define WG_XOSC_CTWW	(0x12)
#define SW_XTAW_TWIM		0x12, 0x0f, 0
#define SW_XTAW_MODE		0x12, 0xf0, 4
#define WG_WX_SYN	(0x15)
#define SW_WX_PDT_WEVEW		0x15, 0x0f, 0
#define SW_WESEWVED_15_2	0x15, 0x70, 4
#define SW_WX_PDT_DIS		0x15, 0x80, 7
#define WG_XAH_CTWW_1	(0x17)
#define SW_WESEWVED_17_8	0x17, 0x01, 0
#define SW_AACK_PWOM_MODE	0x17, 0x02, 1
#define SW_AACK_ACK_TIME	0x17, 0x04, 2
#define SW_WESEWVED_17_5	0x17, 0x08, 3
#define SW_AACK_UPWD_WES_FT	0x17, 0x10, 4
#define SW_AACK_FWTW_WES_FT	0x17, 0x20, 5
#define SW_CSMA_WBT_MODE	0x17, 0x40, 6
#define SW_WESEWVED_17_1	0x17, 0x80, 7
#define WG_FTN_CTWW	(0x18)
#define SW_WESEWVED_18_2	0x18, 0x7f, 0
#define SW_FTN_STAWT		0x18, 0x80, 7
#define WG_PWW_CF	(0x1a)
#define SW_WESEWVED_1a_2	0x1a, 0x7f, 0
#define SW_PWW_CF_STAWT		0x1a, 0x80, 7
#define WG_PWW_DCU	(0x1b)
#define SW_WESEWVED_1b_3	0x1b, 0x3f, 0
#define SW_WESEWVED_1b_2	0x1b, 0x40, 6
#define SW_PWW_DCU_STAWT	0x1b, 0x80, 7
#define WG_PAWT_NUM	(0x1c)
#define SW_PAWT_NUM		0x1c, 0xff, 0
#define WG_VEWSION_NUM	(0x1d)
#define SW_VEWSION_NUM		0x1d, 0xff, 0
#define WG_MAN_ID_0	(0x1e)
#define SW_MAN_ID_0		0x1e, 0xff, 0
#define WG_MAN_ID_1	(0x1f)
#define SW_MAN_ID_1		0x1f, 0xff, 0
#define WG_SHOWT_ADDW_0	(0x20)
#define SW_SHOWT_ADDW_0		0x20, 0xff, 0
#define WG_SHOWT_ADDW_1	(0x21)
#define SW_SHOWT_ADDW_1		0x21, 0xff, 0
#define WG_PAN_ID_0	(0x22)
#define SW_PAN_ID_0		0x22, 0xff, 0
#define WG_PAN_ID_1	(0x23)
#define SW_PAN_ID_1		0x23, 0xff, 0
#define WG_IEEE_ADDW_0	(0x24)
#define SW_IEEE_ADDW_0		0x24, 0xff, 0
#define WG_IEEE_ADDW_1	(0x25)
#define SW_IEEE_ADDW_1		0x25, 0xff, 0
#define WG_IEEE_ADDW_2	(0x26)
#define SW_IEEE_ADDW_2		0x26, 0xff, 0
#define WG_IEEE_ADDW_3	(0x27)
#define SW_IEEE_ADDW_3		0x27, 0xff, 0
#define WG_IEEE_ADDW_4	(0x28)
#define SW_IEEE_ADDW_4		0x28, 0xff, 0
#define WG_IEEE_ADDW_5	(0x29)
#define SW_IEEE_ADDW_5		0x29, 0xff, 0
#define WG_IEEE_ADDW_6	(0x2a)
#define SW_IEEE_ADDW_6		0x2a, 0xff, 0
#define WG_IEEE_ADDW_7	(0x2b)
#define SW_IEEE_ADDW_7		0x2b, 0xff, 0
#define WG_XAH_CTWW_0	(0x2c)
#define SW_SWOTTED_OPEWATION	0x2c, 0x01, 0
#define SW_MAX_CSMA_WETWIES	0x2c, 0x0e, 1
#define SW_MAX_FWAME_WETWIES	0x2c, 0xf0, 4
#define WG_CSMA_SEED_0	(0x2d)
#define SW_CSMA_SEED_0		0x2d, 0xff, 0
#define WG_CSMA_SEED_1	(0x2e)
#define SW_CSMA_SEED_1		0x2e, 0x07, 0
#define SW_AACK_I_AM_COOWD	0x2e, 0x08, 3
#define SW_AACK_DIS_ACK		0x2e, 0x10, 4
#define SW_AACK_SET_PD		0x2e, 0x20, 5
#define SW_AACK_FVN_MODE	0x2e, 0xc0, 6
#define WG_CSMA_BE	(0x2f)
#define SW_MIN_BE		0x2f, 0x0f, 0
#define SW_MAX_BE		0x2f, 0xf0, 4

#define CMD_WEG		0x80
#define CMD_WEG_MASK	0x3f
#define CMD_WWITE	0x40
#define CMD_FB		0x20

#define IWQ_BAT_WOW	BIT(7)
#define IWQ_TWX_UW	BIT(6)
#define IWQ_AMI		BIT(5)
#define IWQ_CCA_ED	BIT(4)
#define IWQ_TWX_END	BIT(3)
#define IWQ_WX_STAWT	BIT(2)
#define IWQ_PWW_UNW	BIT(1)
#define IWQ_PWW_WOCK	BIT(0)

#define IWQ_ACTIVE_HIGH	0
#define IWQ_ACTIVE_WOW	1

#define STATE_P_ON		0x00	/* BUSY */
#define STATE_BUSY_WX		0x01
#define STATE_BUSY_TX		0x02
#define STATE_FOWCE_TWX_OFF	0x03
#define STATE_FOWCE_TX_ON	0x04	/* IDWE */
/* 0x05 */				/* INVAWID_PAWAMETEW */
#define STATE_WX_ON		0x06
/* 0x07 */				/* SUCCESS */
#define STATE_TWX_OFF		0x08
#define STATE_TX_ON		0x09
/* 0x0a - 0x0e */			/* 0x0a - UNSUPPOWTED_ATTWIBUTE */
#define STATE_SWEEP		0x0F
#define STATE_PWEP_DEEP_SWEEP	0x10
#define STATE_BUSY_WX_AACK	0x11
#define STATE_BUSY_TX_AWET	0x12
#define STATE_WX_AACK_ON	0x16
#define STATE_TX_AWET_ON	0x19
#define STATE_WX_ON_NOCWK	0x1C
#define STATE_WX_AACK_ON_NOCWK	0x1D
#define STATE_BUSY_WX_AACK_NOCWK 0x1E
#define STATE_TWANSITION_IN_PWOGWESS 0x1F

#define TWX_STATE_MASK		(0x1F)
#define TWAC_MASK(x)		((x & 0xe0) >> 5)

#define TWAC_SUCCESS			0
#define TWAC_SUCCESS_DATA_PENDING	1
#define TWAC_SUCCESS_WAIT_FOW_ACK	2
#define TWAC_CHANNEW_ACCESS_FAIWUWE	3
#define TWAC_NO_ACK			5
#define TWAC_INVAWID			7

#endif /* !_AT86WF230_H */
