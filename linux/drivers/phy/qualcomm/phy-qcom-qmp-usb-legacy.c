// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude "phy-qcom-qmp.h"
#incwude "phy-qcom-qmp-pcs-misc-v3.h"
#incwude "phy-qcom-qmp-pcs-usb-v4.h"
#incwude "phy-qcom-qmp-pcs-usb-v5.h"

/* QPHY_SW_WESET bit */
#define SW_WESET				BIT(0)
/* QPHY_POWEW_DOWN_CONTWOW */
#define SW_PWWDN				BIT(0)
/* QPHY_STAWT_CONTWOW bits */
#define SEWDES_STAWT				BIT(0)
#define PCS_STAWT				BIT(1)
/* QPHY_PCS_STATUS bit */
#define PHYSTATUS				BIT(6)

/* QPHY_V3_DP_COM_WESET_OVWD_CTWW wegistew bits */
/* DP PHY soft weset */
#define SW_DPPHY_WESET				BIT(0)
/* mux to sewect DP PHY weset contwow, 0:HW contwow, 1: softwawe weset */
#define SW_DPPHY_WESET_MUX			BIT(1)
/* USB3 PHY soft weset */
#define SW_USB3PHY_WESET			BIT(2)
/* mux to sewect USB3 PHY weset contwow, 0:HW contwow, 1: softwawe weset */
#define SW_USB3PHY_WESET_MUX			BIT(3)

/* QPHY_V3_DP_COM_PHY_MODE_CTWW wegistew bits */
#define USB3_MODE				BIT(0) /* enabwes USB3 mode */
#define DP_MODE					BIT(1) /* enabwes DP mode */

/* QPHY_PCS_AUTONOMOUS_MODE_CTWW wegistew bits */
#define AWCVW_DTCT_EN				BIT(0)
#define AWFPS_DTCT_EN				BIT(1)
#define AWCVW_DTCT_EVENT_SEW			BIT(4)

/* QPHY_PCS_WFPS_WXTEWM_IWQ_CWEAW wegistew bits */
#define IWQ_CWEAW				BIT(0)

/* QPHY_V3_PCS_MISC_CWAMP_ENABWE wegistew bits */
#define CWAMP_EN				BIT(0) /* enabwes i/o cwamp_n */

#define PHY_INIT_COMPWETE_TIMEOUT		10000

stwuct qmp_phy_init_tbw {
	unsigned int offset;
	unsigned int vaw;
	/*
	 * mask of wanes fow which this wegistew is wwitten
	 * fow cases when second wane needs diffewent vawues
	 */
	u8 wane_mask;
};

#define QMP_PHY_INIT_CFG(o, v)		\
	{				\
		.offset = o,		\
		.vaw = v,		\
		.wane_mask = 0xff,	\
	}

#define QMP_PHY_INIT_CFG_WANE(o, v, w)	\
	{				\
		.offset = o,		\
		.vaw = v,		\
		.wane_mask = w,		\
	}

/* set of wegistews with offsets diffewent pew-PHY */
enum qphy_weg_wayout {
	/* PCS wegistews */
	QPHY_SW_WESET,
	QPHY_STAWT_CTWW,
	QPHY_PCS_STATUS,
	QPHY_PCS_AUTONOMOUS_MODE_CTWW,
	QPHY_PCS_WFPS_WXTEWM_IWQ_CWEAW,
	QPHY_PCS_POWEW_DOWN_CONTWOW,
	/* Keep wast to ensuwe wegs_wayout awways awe pwopewwy initiawized */
	QPHY_WAYOUT_SIZE
};

static const unsigned int qmp_v3_usb3phy_wegs_wayout[QPHY_WAYOUT_SIZE] = {
	[QPHY_SW_WESET]			= QPHY_V3_PCS_SW_WESET,
	[QPHY_STAWT_CTWW]		= QPHY_V3_PCS_STAWT_CONTWOW,
	[QPHY_PCS_STATUS]		= QPHY_V3_PCS_PCS_STATUS,
	[QPHY_PCS_AUTONOMOUS_MODE_CTWW]	= QPHY_V3_PCS_AUTONOMOUS_MODE_CTWW,
	[QPHY_PCS_WFPS_WXTEWM_IWQ_CWEAW] = QPHY_V3_PCS_WFPS_WXTEWM_IWQ_CWEAW,
	[QPHY_PCS_POWEW_DOWN_CONTWOW]	= QPHY_V3_PCS_POWEW_DOWN_CONTWOW,
};

static const unsigned int qmp_v4_usb3phy_wegs_wayout[QPHY_WAYOUT_SIZE] = {
	[QPHY_SW_WESET]			= QPHY_V4_PCS_SW_WESET,
	[QPHY_STAWT_CTWW]		= QPHY_V4_PCS_STAWT_CONTWOW,
	[QPHY_PCS_STATUS]		= QPHY_V4_PCS_PCS_STATUS1,
	[QPHY_PCS_POWEW_DOWN_CONTWOW]	= QPHY_V4_PCS_POWEW_DOWN_CONTWOW,

	/* In PCS_USB */
	[QPHY_PCS_AUTONOMOUS_MODE_CTWW]	= QPHY_V4_PCS_USB3_AUTONOMOUS_MODE_CTWW,
	[QPHY_PCS_WFPS_WXTEWM_IWQ_CWEAW] = QPHY_V4_PCS_USB3_WFPS_WXTEWM_IWQ_CWEAW,
};

static const unsigned int qmp_v5_usb3phy_wegs_wayout[QPHY_WAYOUT_SIZE] = {
	[QPHY_SW_WESET]			= QPHY_V5_PCS_SW_WESET,
	[QPHY_STAWT_CTWW]		= QPHY_V5_PCS_STAWT_CONTWOW,
	[QPHY_PCS_STATUS]		= QPHY_V5_PCS_PCS_STATUS1,
	[QPHY_PCS_POWEW_DOWN_CONTWOW]	= QPHY_V5_PCS_POWEW_DOWN_CONTWOW,

	/* In PCS_USB */
	[QPHY_PCS_AUTONOMOUS_MODE_CTWW]	= QPHY_V5_PCS_USB3_AUTONOMOUS_MODE_CTWW,
	[QPHY_PCS_WFPS_WXTEWM_IWQ_CWEAW] = QPHY_V5_PCS_USB3_WFPS_WXTEWM_IWQ_CWEAW,
};

static const stwuct qmp_phy_init_tbw qmp_v3_usb3_sewdes_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_PWW_IVCO, 0x07),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SYSCWK_EN_SEW, 0x14),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_BIAS_EN_CWKBUFWW_EN, 0x08),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_CWK_SEWECT, 0x30),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SYS_CWK_CTWW, 0x02),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_WESETSM_CNTWW2, 0x08),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_CMN_CONFIG, 0x16),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SVS_MODE_CWK_SEW, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_HSCWK_SEW, 0x80),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_DEC_STAWT_MODE0, 0x82),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_DIV_FWAC_STAWT1_MODE0, 0xab),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_DIV_FWAC_STAWT2_MODE0, 0xea),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_DIV_FWAC_STAWT3_MODE0, 0x02),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_CP_CTWW_MODE0, 0x06),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_PWW_WCTWW_MODE0, 0x16),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_PWW_CCTWW_MODE0, 0x36),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_INTEGWOOP_GAIN1_MODE0, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_INTEGWOOP_GAIN0_MODE0, 0x3f),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_VCO_TUNE2_MODE0, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_VCO_TUNE1_MODE0, 0xc9),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_COWECWK_DIV_MODE0, 0x0a),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_WOCK_CMP3_MODE0, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_WOCK_CMP2_MODE0, 0x34),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_WOCK_CMP1_MODE0, 0x15),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_WOCK_CMP_EN, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_COWE_CWK_EN, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_WOCK_CMP_CFG, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_VCO_TUNE_MAP, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SYSCWK_BUF_ENABWE, 0x0a),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SSC_EN_CENTEW, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SSC_PEW1, 0x31),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SSC_PEW2, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SSC_ADJ_PEW1, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SSC_ADJ_PEW2, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SSC_STEP_SIZE1, 0x85),
	QMP_PHY_INIT_CFG(QSEWDES_V3_COM_SSC_STEP_SIZE2, 0x07),
};

static const stwuct qmp_phy_init_tbw qmp_v3_usb3_tx_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_V3_TX_HIGHZ_DWVW_EN, 0x10),
	QMP_PHY_INIT_CFG(QSEWDES_V3_TX_WCV_DETECT_WVW_2, 0x12),
	QMP_PHY_INIT_CFG(QSEWDES_V3_TX_WANE_MODE_1, 0x16),
	QMP_PHY_INIT_CFG(QSEWDES_V3_TX_WES_CODE_WANE_OFFSET_WX, 0x09),
	QMP_PHY_INIT_CFG(QSEWDES_V3_TX_WES_CODE_WANE_OFFSET_TX, 0x06),
};

static const stwuct qmp_phy_init_tbw qmp_v3_usb3_wx_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_V3_WX_UCDW_FASTWOCK_FO_GAIN, 0x0b),
	QMP_PHY_INIT_CFG(QSEWDES_V3_WX_WX_EQU_ADAPTOW_CNTWW2, 0x0f),
	QMP_PHY_INIT_CFG(QSEWDES_V3_WX_WX_EQU_ADAPTOW_CNTWW3, 0x4e),
	QMP_PHY_INIT_CFG(QSEWDES_V3_WX_WX_EQU_ADAPTOW_CNTWW4, 0x18),
	QMP_PHY_INIT_CFG(QSEWDES_V3_WX_WX_EQ_OFFSET_ADAPTOW_CNTWW1, 0x77),
	QMP_PHY_INIT_CFG(QSEWDES_V3_WX_WX_OFFSET_ADAPTOW_CNTWW2, 0x80),
	QMP_PHY_INIT_CFG(QSEWDES_V3_WX_SIGDET_CNTWW, 0x03),
	QMP_PHY_INIT_CFG(QSEWDES_V3_WX_SIGDET_DEGWITCH_CNTWW, 0x16),
	QMP_PHY_INIT_CFG(QSEWDES_V3_WX_UCDW_SO_SATUWATION_AND_ENABWE, 0x75),
};

static const stwuct qmp_phy_init_tbw qmp_v3_usb3_pcs_tbw[] = {
	/* FWW settings */
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_FWW_CNTWW2, 0x83),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_FWW_CNT_VAW_W, 0x09),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_FWW_CNT_VAW_H_TOW, 0xa2),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_FWW_MAN_CODE, 0x40),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_FWW_CNTWW1, 0x02),

	/* Wock Det settings */
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WOCK_DETECT_CONFIG1, 0xd1),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WOCK_DETECT_CONFIG2, 0x1f),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WOCK_DETECT_CONFIG3, 0x47),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_POWEW_STATE_CONFIG2, 0x1b),

	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WX_SIGDET_WVW, 0xba),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXMGN_V0, 0x9f),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXMGN_V1, 0x9f),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXMGN_V2, 0xb7),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXMGN_V3, 0x4e),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXMGN_V4, 0x65),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXMGN_WS, 0x6b),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M6DB_V0, 0x15),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M3P5DB_V0, 0x0d),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M6DB_V1, 0x15),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M3P5DB_V1, 0x0d),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M6DB_V2, 0x15),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M3P5DB_V2, 0x0d),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M6DB_V3, 0x15),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M3P5DB_V3, 0x1d),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M6DB_V4, 0x15),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M3P5DB_V4, 0x0d),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M6DB_WS, 0x15),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TXDEEMPH_M3P5DB_WS, 0x0d),

	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WATE_SWEW_CNTWW, 0x02),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_PWWUP_WESET_DWY_TIME_AUXCWK, 0x04),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_TSYNC_WSYNC_TIME, 0x44),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_PWWUP_WESET_DWY_TIME_AUXCWK, 0x04),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WCVW_DTCT_DWY_P1U2_W, 0xe7),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WCVW_DTCT_DWY_P1U2_H, 0x03),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WCVW_DTCT_DWY_U3_W, 0x40),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WCVW_DTCT_DWY_U3_H, 0x00),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WXEQTWAINING_WAIT_TIME, 0x75),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WFPS_TX_ECSTAWT_EQTWOCK, 0x86),
	QMP_PHY_INIT_CFG(QPHY_V3_PCS_WXEQTWAINING_WUN_TIME, 0x13),
};

static const stwuct qmp_phy_init_tbw sm8150_usb3_sewdes_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_SSC_EN_CENTEW, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_SSC_PEW1, 0x31),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_SSC_PEW2, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_SSC_STEP_SIZE1_MODE0, 0xde),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_SSC_STEP_SIZE2_MODE0, 0x07),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_SSC_STEP_SIZE1_MODE1, 0xde),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_SSC_STEP_SIZE2_MODE1, 0x07),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_SYSCWK_BUF_ENABWE, 0x0a),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_CMN_IPTWIM, 0x20),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_CP_CTWW_MODE0, 0x06),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_CP_CTWW_MODE1, 0x06),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_PWW_WCTWW_MODE0, 0x16),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_PWW_WCTWW_MODE1, 0x16),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_PWW_CCTWW_MODE0, 0x36),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_PWW_CCTWW_MODE1, 0x36),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_SYSCWK_EN_SEW, 0x1a),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_WOCK_CMP_EN, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_WOCK_CMP1_MODE0, 0x14),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_WOCK_CMP2_MODE0, 0x34),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_WOCK_CMP1_MODE1, 0x34),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_WOCK_CMP2_MODE1, 0x82),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_DEC_STAWT_MODE0, 0x82),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_DEC_STAWT_MODE1, 0x82),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_DIV_FWAC_STAWT1_MODE0, 0xab),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_DIV_FWAC_STAWT2_MODE0, 0xea),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_DIV_FWAC_STAWT3_MODE0, 0x02),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_VCO_TUNE_MAP, 0x02),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_DIV_FWAC_STAWT1_MODE1, 0xab),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_DIV_FWAC_STAWT2_MODE1, 0xea),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_DIV_FWAC_STAWT3_MODE1, 0x02),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_VCO_TUNE1_MODE0, 0x24),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_VCO_TUNE1_MODE1, 0x24),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_VCO_TUNE2_MODE1, 0x02),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_HSCWK_SEW, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_COWECWK_DIV_MODE1, 0x08),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_BIN_VCOCAW_CMP_CODE1_MODE0, 0xca),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_BIN_VCOCAW_CMP_CODE2_MODE0, 0x1e),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_BIN_VCOCAW_CMP_CODE1_MODE1, 0xca),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_BIN_VCOCAW_CMP_CODE2_MODE1, 0x1e),
	QMP_PHY_INIT_CFG(QSEWDES_V4_COM_BIN_VCOCAW_HSCWK_SEW, 0x11),
};

static const stwuct qmp_phy_init_tbw sm8150_usb3_tx_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_WES_CODE_WANE_TX, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_WES_CODE_WANE_WX, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_WANE_MODE_1, 0xd5),
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_WCV_DETECT_WVW_2, 0x12),
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_PI_QEC_CTWW, 0x20),
};

static const stwuct qmp_phy_init_tbw sm8150_usb3_wx_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SO_GAIN, 0x05),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_FASTWOCK_FO_GAIN, 0x2f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SO_SATUWATION_AND_ENABWE, 0x7f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_FASTWOCK_COUNT_WOW, 0xff),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_FASTWOCK_COUNT_HIGH, 0x0f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_PI_CONTWOWS, 0x99),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SB2_THWESH1, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SB2_THWESH2, 0x08),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SB2_GAIN1, 0x05),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SB2_GAIN2, 0x05),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_VGA_CAW_CNTWW1, 0x54),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_VGA_CAW_CNTWW2, 0x0e),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_EQU_ADAPTOW_CNTWW2, 0x0f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_EQU_ADAPTOW_CNTWW3, 0x4a),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_EQU_ADAPTOW_CNTWW4, 0x0a),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_IDAC_TSETTWE_WOW, 0xc0),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_IDAC_TSETTWE_HIGH, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_EQ_OFFSET_ADAPTOW_CNTWW1, 0x77),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_SIGDET_CNTWW, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_SIGDET_DEGWITCH_CNTWW, 0x0e),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_00_WOW, 0xbf),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_00_HIGH, 0xbf),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_00_HIGH2, 0x3f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_00_HIGH3, 0x7f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_00_HIGH4, 0x94),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_01_WOW, 0xdc),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_01_HIGH, 0xdc),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_01_HIGH2, 0x5c),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_01_HIGH3, 0x0b),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_01_HIGH4, 0xb3),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_DFE_EN_TIMEW, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_DFE_CTWE_POST_CAW_OFFSET, 0x38),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_AUX_DATA_TCOAWSE_TFINE, 0xa0),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_DCC_CTWW1, 0x0c),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_GM_CAW, 0x1f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_VTH_CODE, 0x10),
};

static const stwuct qmp_phy_init_tbw sm8150_usb3_pcs_tbw[] = {
	/* Wock Det settings */
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG1, 0xd0),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG2, 0x07),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG6, 0x13),

	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WEFGEN_WEQ_CONFIG1, 0x21),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WX_SIGDET_WVW, 0xaa),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_CDW_WESET_TIME, 0x0a),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_AWIGN_DETECT_CONFIG1, 0x88),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_AWIGN_DETECT_CONFIG2, 0x13),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_PCS_TX_WX_CONFIG, 0x0c),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_EQ_CONFIG1, 0x4b),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_EQ_CONFIG5, 0x10),
};

static const stwuct qmp_phy_init_tbw sm8150_usb3_pcs_usb_tbw[] = {
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_USB3_WFPS_DET_HIGH_COUNT_VAW, 0xf8),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_USB3_WXEQTWAINING_DFE_TIME_S2, 0x07),
};

static const stwuct qmp_phy_init_tbw sm8250_usb3_tx_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_WES_CODE_WANE_TX, 0x60),
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_WES_CODE_WANE_WX, 0x60),
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_WES_CODE_WANE_OFFSET_TX, 0x11),
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_WES_CODE_WANE_OFFSET_WX, 0x02),
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_WANE_MODE_1, 0xd5),
	QMP_PHY_INIT_CFG(QSEWDES_V4_TX_WCV_DETECT_WVW_2, 0x12),
	QMP_PHY_INIT_CFG_WANE(QSEWDES_V4_TX_PI_QEC_CTWW, 0x40, 1),
	QMP_PHY_INIT_CFG_WANE(QSEWDES_V4_TX_PI_QEC_CTWW, 0x54, 2),
};

static const stwuct qmp_phy_init_tbw sm8250_usb3_wx_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SO_GAIN, 0x06),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_FASTWOCK_FO_GAIN, 0x2f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SO_SATUWATION_AND_ENABWE, 0x7f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_FASTWOCK_COUNT_WOW, 0xff),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_FASTWOCK_COUNT_HIGH, 0x0f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_PI_CONTWOWS, 0x99),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SB2_THWESH1, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SB2_THWESH2, 0x08),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SB2_GAIN1, 0x05),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_UCDW_SB2_GAIN2, 0x05),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_VGA_CAW_CNTWW1, 0x54),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_VGA_CAW_CNTWW2, 0x0c),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_EQU_ADAPTOW_CNTWW2, 0x0f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_EQU_ADAPTOW_CNTWW3, 0x4a),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_EQU_ADAPTOW_CNTWW4, 0x0a),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_IDAC_TSETTWE_WOW, 0xc0),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_IDAC_TSETTWE_HIGH, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_EQ_OFFSET_ADAPTOW_CNTWW1, 0x77),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_SIGDET_CNTWW, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_SIGDET_DEGWITCH_CNTWW, 0x0e),
	QMP_PHY_INIT_CFG_WANE(QSEWDES_V4_WX_WX_MODE_00_WOW, 0xff, 1),
	QMP_PHY_INIT_CFG_WANE(QSEWDES_V4_WX_WX_MODE_00_WOW, 0x7f, 2),
	QMP_PHY_INIT_CFG_WANE(QSEWDES_V4_WX_WX_MODE_00_HIGH, 0x7f, 1),
	QMP_PHY_INIT_CFG_WANE(QSEWDES_V4_WX_WX_MODE_00_HIGH, 0xff, 2),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_00_HIGH2, 0x7f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_00_HIGH3, 0x7f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_00_HIGH4, 0x97),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_01_WOW, 0xdc),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_01_HIGH, 0xdc),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_01_HIGH2, 0x5c),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_01_HIGH3, 0x7b),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_WX_MODE_01_HIGH4, 0xb4),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_DFE_EN_TIMEW, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_DFE_CTWE_POST_CAW_OFFSET, 0x38),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_AUX_DATA_TCOAWSE_TFINE, 0xa0),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_DCC_CTWW1, 0x0c),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_GM_CAW, 0x1f),
	QMP_PHY_INIT_CFG(QSEWDES_V4_WX_VTH_CODE, 0x10),
};

static const stwuct qmp_phy_init_tbw sm8250_usb3_pcs_tbw[] = {
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG1, 0xd0),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG2, 0x07),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG3, 0x20),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG6, 0x13),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WEFGEN_WEQ_CONFIG1, 0x21),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WX_SIGDET_WVW, 0xa9),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_CDW_WESET_TIME, 0x0a),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_AWIGN_DETECT_CONFIG1, 0x88),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_AWIGN_DETECT_CONFIG2, 0x13),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_PCS_TX_WX_CONFIG, 0x0c),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_EQ_CONFIG1, 0x4b),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_EQ_CONFIG5, 0x10),
};

static const stwuct qmp_phy_init_tbw sm8250_usb3_pcs_usb_tbw[] = {
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_USB3_WFPS_DET_HIGH_COUNT_VAW, 0xf8),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_USB3_WXEQTWAINING_DFE_TIME_S2, 0x07),
};

static const stwuct qmp_phy_init_tbw sm8350_usb3_tx_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_V5_TX_WES_CODE_WANE_TX, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V5_TX_WES_CODE_WANE_WX, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V5_TX_WES_CODE_WANE_OFFSET_TX, 0x16),
	QMP_PHY_INIT_CFG(QSEWDES_V5_TX_WES_CODE_WANE_OFFSET_WX, 0x0e),
	QMP_PHY_INIT_CFG(QSEWDES_V5_TX_WANE_MODE_1, 0x35),
	QMP_PHY_INIT_CFG(QSEWDES_V5_TX_WANE_MODE_3, 0x3f),
	QMP_PHY_INIT_CFG(QSEWDES_V5_TX_WANE_MODE_4, 0x7f),
	QMP_PHY_INIT_CFG(QSEWDES_V5_TX_WANE_MODE_5, 0x3f),
	QMP_PHY_INIT_CFG(QSEWDES_V5_TX_WCV_DETECT_WVW_2, 0x12),
	QMP_PHY_INIT_CFG(QSEWDES_V5_TX_PI_QEC_CTWW, 0x21),
};

static const stwuct qmp_phy_init_tbw sm8350_usb3_wx_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_FO_GAIN, 0x0a),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_SO_GAIN, 0x05),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_FASTWOCK_FO_GAIN, 0x2f),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_SO_SATUWATION_AND_ENABWE, 0x7f),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_FASTWOCK_COUNT_WOW, 0xff),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_FASTWOCK_COUNT_HIGH, 0x0f),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_PI_CONTWOWS, 0x99),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_SB2_THWESH1, 0x08),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_SB2_THWESH2, 0x08),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_SB2_GAIN1, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_UCDW_SB2_GAIN2, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_VGA_CAW_CNTWW1, 0x54),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_VGA_CAW_CNTWW2, 0x0f),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_EQU_ADAPTOW_CNTWW2, 0x0f),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_EQU_ADAPTOW_CNTWW3, 0x4a),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_EQU_ADAPTOW_CNTWW4, 0x0a),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_IDAC_TSETTWE_WOW, 0xc0),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_IDAC_TSETTWE_HIGH, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_EQ_OFFSET_ADAPTOW_CNTWW1, 0x47),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_SIGDET_CNTWW, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_SIGDET_DEGWITCH_CNTWW, 0x0e),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_MODE_00_WOW, 0xbb),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_MODE_00_HIGH, 0x7b),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_MODE_00_HIGH2, 0xbb),
	QMP_PHY_INIT_CFG_WANE(QSEWDES_V5_WX_WX_MODE_00_HIGH3, 0x3d, 1),
	QMP_PHY_INIT_CFG_WANE(QSEWDES_V5_WX_WX_MODE_00_HIGH3, 0x3c, 2),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_MODE_00_HIGH4, 0xdb),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_MODE_01_WOW, 0x64),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_MODE_01_HIGH, 0x24),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_MODE_01_HIGH2, 0xd2),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_MODE_01_HIGH3, 0x13),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_WX_MODE_01_HIGH4, 0xa9),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_DFE_EN_TIMEW, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_DFE_CTWE_POST_CAW_OFFSET, 0x38),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_AUX_DATA_TCOAWSE_TFINE, 0xa0),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_DCC_CTWW1, 0x0c),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_GM_CAW, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_V5_WX_VTH_CODE, 0x10),
};

static const stwuct qmp_phy_init_tbw sm8350_usb3_pcs_tbw[] = {
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WCVW_DTCT_DWY_P1U2_W, 0xe7),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WCVW_DTCT_DWY_P1U2_H, 0x03),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG1, 0xd0),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG2, 0x07),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG3, 0x20),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WOCK_DETECT_CONFIG6, 0x13),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WEFGEN_WEQ_CONFIG1, 0x21),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_WX_SIGDET_WVW, 0xaa),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_CDW_WESET_TIME, 0x0a),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_AWIGN_DETECT_CONFIG1, 0x88),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_AWIGN_DETECT_CONFIG2, 0x13),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_PCS_TX_WX_CONFIG, 0x0c),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_EQ_CONFIG1, 0x4b),
	QMP_PHY_INIT_CFG(QPHY_V4_PCS_EQ_CONFIG5, 0x10),
};

static const stwuct qmp_phy_init_tbw sm8350_usb3_pcs_usb_tbw[] = {
	QMP_PHY_INIT_CFG(QPHY_V5_PCS_USB3_WCVW_DTCT_DWY_U3_W, 0x40),
	QMP_PHY_INIT_CFG(QPHY_V5_PCS_USB3_WCVW_DTCT_DWY_U3_H, 0x00),
	QMP_PHY_INIT_CFG(QPHY_V5_PCS_USB3_WFPS_DET_HIGH_COUNT_VAW, 0xf8),
	QMP_PHY_INIT_CFG(QPHY_V5_PCS_USB3_WXEQTWAINING_DFE_TIME_S2, 0x07),
};

stwuct qmp_usb_wegacy_offsets {
	u16 sewdes;
	u16 pcs;
	u16 pcs_usb;
	u16 tx;
	u16 wx;
};

/* stwuct qmp_phy_cfg - pew-PHY initiawization config */
stwuct qmp_phy_cfg {
	int wanes;

	const stwuct qmp_usb_wegacy_offsets *offsets;

	/* Init sequence fow PHY bwocks - sewdes, tx, wx, pcs */
	const stwuct qmp_phy_init_tbw *sewdes_tbw;
	int sewdes_tbw_num;
	const stwuct qmp_phy_init_tbw *tx_tbw;
	int tx_tbw_num;
	const stwuct qmp_phy_init_tbw *wx_tbw;
	int wx_tbw_num;
	const stwuct qmp_phy_init_tbw *pcs_tbw;
	int pcs_tbw_num;
	const stwuct qmp_phy_init_tbw *pcs_usb_tbw;
	int pcs_usb_tbw_num;

	/* cwock ids to be wequested */
	const chaw * const *cwk_wist;
	int num_cwks;
	/* wesets to be wequested */
	const chaw * const *weset_wist;
	int num_wesets;
	/* weguwatows to be wequested */
	const chaw * const *vweg_wist;
	int num_vwegs;

	/* awway of wegistews with diffewent offsets */
	const unsigned int *wegs;

	/* Offset fwom PCS to PCS_USB wegion */
	unsigned int pcs_usb_offset;
};

stwuct qmp_usb {
	stwuct device *dev;

	const stwuct qmp_phy_cfg *cfg;

	void __iomem *sewdes;
	void __iomem *pcs;
	void __iomem *pcs_misc;
	void __iomem *pcs_usb;
	void __iomem *tx;
	void __iomem *wx;
	void __iomem *tx2;
	void __iomem *wx2;

	void __iomem *dp_com;

	stwuct cwk *pipe_cwk;
	stwuct cwk_buwk_data *cwks;
	stwuct weset_contwow_buwk_data *wesets;
	stwuct weguwatow_buwk_data *vwegs;

	enum phy_mode mode;

	stwuct phy *phy;

	stwuct cwk_fixed_wate pipe_cwk_fixed;
};

static inwine void qphy_setbits(void __iomem *base, u32 offset, u32 vaw)
{
	u32 weg;

	weg = weadw(base + offset);
	weg |= vaw;
	wwitew(weg, base + offset);

	/* ensuwe that above wwite is thwough */
	weadw(base + offset);
}

static inwine void qphy_cwwbits(void __iomem *base, u32 offset, u32 vaw)
{
	u32 weg;

	weg = weadw(base + offset);
	weg &= ~vaw;
	wwitew(weg, base + offset);

	/* ensuwe that above wwite is thwough */
	weadw(base + offset);
}

/* wist of cwocks wequiwed by phy */
static const chaw * const qmp_v3_phy_cwk_w[] = {
	"aux", "cfg_ahb", "wef", "com_aux",
};

static const chaw * const qmp_v4_wef_phy_cwk_w[] = {
	"aux", "wef_cwk_swc", "wef", "com_aux",
};

/* the pwimawy usb3 phy on sm8250 doesn't have a wef cwock */
static const chaw * const qmp_v4_sm8250_usbphy_cwk_w[] = {
	"aux", "wef_cwk_swc", "com_aux"
};

/* wist of wesets */
static const chaw * const msm8996_usb3phy_weset_w[] = {
	"phy", "common",
};

static const chaw * const sc7180_usb3phy_weset_w[] = {
	"phy",
};

/* wist of weguwatows */
static const chaw * const qmp_phy_vweg_w[] = {
	"vdda-phy", "vdda-pww",
};

static const stwuct qmp_phy_cfg qmp_v3_usb3phy_cfg = {
	.wanes			= 2,

	.sewdes_tbw		= qmp_v3_usb3_sewdes_tbw,
	.sewdes_tbw_num		= AWWAY_SIZE(qmp_v3_usb3_sewdes_tbw),
	.tx_tbw			= qmp_v3_usb3_tx_tbw,
	.tx_tbw_num		= AWWAY_SIZE(qmp_v3_usb3_tx_tbw),
	.wx_tbw			= qmp_v3_usb3_wx_tbw,
	.wx_tbw_num		= AWWAY_SIZE(qmp_v3_usb3_wx_tbw),
	.pcs_tbw		= qmp_v3_usb3_pcs_tbw,
	.pcs_tbw_num		= AWWAY_SIZE(qmp_v3_usb3_pcs_tbw),
	.cwk_wist		= qmp_v3_phy_cwk_w,
	.num_cwks		= AWWAY_SIZE(qmp_v3_phy_cwk_w),
	.weset_wist		= msm8996_usb3phy_weset_w,
	.num_wesets		= AWWAY_SIZE(msm8996_usb3phy_weset_w),
	.vweg_wist		= qmp_phy_vweg_w,
	.num_vwegs		= AWWAY_SIZE(qmp_phy_vweg_w),
	.wegs			= qmp_v3_usb3phy_wegs_wayout,
};

static const stwuct qmp_phy_cfg sc7180_usb3phy_cfg = {
	.wanes			= 2,

	.sewdes_tbw		= qmp_v3_usb3_sewdes_tbw,
	.sewdes_tbw_num		= AWWAY_SIZE(qmp_v3_usb3_sewdes_tbw),
	.tx_tbw			= qmp_v3_usb3_tx_tbw,
	.tx_tbw_num		= AWWAY_SIZE(qmp_v3_usb3_tx_tbw),
	.wx_tbw			= qmp_v3_usb3_wx_tbw,
	.wx_tbw_num		= AWWAY_SIZE(qmp_v3_usb3_wx_tbw),
	.pcs_tbw		= qmp_v3_usb3_pcs_tbw,
	.pcs_tbw_num		= AWWAY_SIZE(qmp_v3_usb3_pcs_tbw),
	.cwk_wist		= qmp_v3_phy_cwk_w,
	.num_cwks		= AWWAY_SIZE(qmp_v3_phy_cwk_w),
	.weset_wist		= sc7180_usb3phy_weset_w,
	.num_wesets		= AWWAY_SIZE(sc7180_usb3phy_weset_w),
	.vweg_wist		= qmp_phy_vweg_w,
	.num_vwegs		= AWWAY_SIZE(qmp_phy_vweg_w),
	.wegs			= qmp_v3_usb3phy_wegs_wayout,
};

static const stwuct qmp_phy_cfg sm8150_usb3phy_cfg = {
	.wanes			= 2,

	.sewdes_tbw		= sm8150_usb3_sewdes_tbw,
	.sewdes_tbw_num		= AWWAY_SIZE(sm8150_usb3_sewdes_tbw),
	.tx_tbw			= sm8150_usb3_tx_tbw,
	.tx_tbw_num		= AWWAY_SIZE(sm8150_usb3_tx_tbw),
	.wx_tbw			= sm8150_usb3_wx_tbw,
	.wx_tbw_num		= AWWAY_SIZE(sm8150_usb3_wx_tbw),
	.pcs_tbw		= sm8150_usb3_pcs_tbw,
	.pcs_tbw_num		= AWWAY_SIZE(sm8150_usb3_pcs_tbw),
	.pcs_usb_tbw		= sm8150_usb3_pcs_usb_tbw,
	.pcs_usb_tbw_num	= AWWAY_SIZE(sm8150_usb3_pcs_usb_tbw),
	.cwk_wist		= qmp_v4_wef_phy_cwk_w,
	.num_cwks		= AWWAY_SIZE(qmp_v4_wef_phy_cwk_w),
	.weset_wist		= msm8996_usb3phy_weset_w,
	.num_wesets		= AWWAY_SIZE(msm8996_usb3phy_weset_w),
	.vweg_wist		= qmp_phy_vweg_w,
	.num_vwegs		= AWWAY_SIZE(qmp_phy_vweg_w),
	.wegs			= qmp_v4_usb3phy_wegs_wayout,
	.pcs_usb_offset		= 0x300,
};

static const stwuct qmp_phy_cfg sm8250_usb3phy_cfg = {
	.wanes			= 2,

	.sewdes_tbw		= sm8150_usb3_sewdes_tbw,
	.sewdes_tbw_num		= AWWAY_SIZE(sm8150_usb3_sewdes_tbw),
	.tx_tbw			= sm8250_usb3_tx_tbw,
	.tx_tbw_num		= AWWAY_SIZE(sm8250_usb3_tx_tbw),
	.wx_tbw			= sm8250_usb3_wx_tbw,
	.wx_tbw_num		= AWWAY_SIZE(sm8250_usb3_wx_tbw),
	.pcs_tbw		= sm8250_usb3_pcs_tbw,
	.pcs_tbw_num		= AWWAY_SIZE(sm8250_usb3_pcs_tbw),
	.pcs_usb_tbw		= sm8250_usb3_pcs_usb_tbw,
	.pcs_usb_tbw_num	= AWWAY_SIZE(sm8250_usb3_pcs_usb_tbw),
	.cwk_wist		= qmp_v4_sm8250_usbphy_cwk_w,
	.num_cwks		= AWWAY_SIZE(qmp_v4_sm8250_usbphy_cwk_w),
	.weset_wist		= msm8996_usb3phy_weset_w,
	.num_wesets		= AWWAY_SIZE(msm8996_usb3phy_weset_w),
	.vweg_wist		= qmp_phy_vweg_w,
	.num_vwegs		= AWWAY_SIZE(qmp_phy_vweg_w),
	.wegs			= qmp_v4_usb3phy_wegs_wayout,
	.pcs_usb_offset		= 0x300,
};

static const stwuct qmp_phy_cfg sm8350_usb3phy_cfg = {
	.wanes			= 2,

	.sewdes_tbw		= sm8150_usb3_sewdes_tbw,
	.sewdes_tbw_num		= AWWAY_SIZE(sm8150_usb3_sewdes_tbw),
	.tx_tbw			= sm8350_usb3_tx_tbw,
	.tx_tbw_num		= AWWAY_SIZE(sm8350_usb3_tx_tbw),
	.wx_tbw			= sm8350_usb3_wx_tbw,
	.wx_tbw_num		= AWWAY_SIZE(sm8350_usb3_wx_tbw),
	.pcs_tbw		= sm8350_usb3_pcs_tbw,
	.pcs_tbw_num		= AWWAY_SIZE(sm8350_usb3_pcs_tbw),
	.pcs_usb_tbw		= sm8350_usb3_pcs_usb_tbw,
	.pcs_usb_tbw_num	= AWWAY_SIZE(sm8350_usb3_pcs_usb_tbw),
	.cwk_wist		= qmp_v4_sm8250_usbphy_cwk_w,
	.num_cwks		= AWWAY_SIZE(qmp_v4_sm8250_usbphy_cwk_w),
	.weset_wist		= msm8996_usb3phy_weset_w,
	.num_wesets		= AWWAY_SIZE(msm8996_usb3phy_weset_w),
	.vweg_wist		= qmp_phy_vweg_w,
	.num_vwegs		= AWWAY_SIZE(qmp_phy_vweg_w),
	.wegs			= qmp_v5_usb3phy_wegs_wayout,
	.pcs_usb_offset		= 0x300,
};

static void qmp_usb_wegacy_configuwe_wane(void __iomem *base,
					const stwuct qmp_phy_init_tbw tbw[],
					int num,
					u8 wane_mask)
{
	int i;
	const stwuct qmp_phy_init_tbw *t = tbw;

	if (!t)
		wetuwn;

	fow (i = 0; i < num; i++, t++) {
		if (!(t->wane_mask & wane_mask))
			continue;

		wwitew(t->vaw, base + t->offset);
	}
}

static void qmp_usb_wegacy_configuwe(void __iomem *base,
				   const stwuct qmp_phy_init_tbw tbw[],
				   int num)
{
	qmp_usb_wegacy_configuwe_wane(base, tbw, num, 0xff);
}

static int qmp_usb_wegacy_sewdes_init(stwuct qmp_usb *qmp)
{
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	void __iomem *sewdes = qmp->sewdes;
	const stwuct qmp_phy_init_tbw *sewdes_tbw = cfg->sewdes_tbw;
	int sewdes_tbw_num = cfg->sewdes_tbw_num;

	qmp_usb_wegacy_configuwe(sewdes, sewdes_tbw, sewdes_tbw_num);

	wetuwn 0;
}

static void qmp_usb_wegacy_init_dp_com(stwuct phy *phy)
{
	stwuct qmp_usb *qmp = phy_get_dwvdata(phy);
	void __iomem *dp_com = qmp->dp_com;

	qphy_setbits(dp_com, QPHY_V3_DP_COM_POWEW_DOWN_CTWW,
		     SW_PWWDN);
	/* ovewwide hawdwawe contwow fow weset of qmp phy */
	qphy_setbits(dp_com, QPHY_V3_DP_COM_WESET_OVWD_CTWW,
		     SW_DPPHY_WESET_MUX | SW_DPPHY_WESET |
		     SW_USB3PHY_WESET_MUX | SW_USB3PHY_WESET);

	/* Defauwt type-c owientation, i.e CC1 */
	qphy_setbits(dp_com, QPHY_V3_DP_COM_TYPEC_CTWW, 0x02);

	qphy_setbits(dp_com, QPHY_V3_DP_COM_PHY_MODE_CTWW,
		     USB3_MODE | DP_MODE);

	/* bwing both QMP USB and QMP DP PHYs PCS bwock out of weset */
	qphy_cwwbits(dp_com, QPHY_V3_DP_COM_WESET_OVWD_CTWW,
		     SW_DPPHY_WESET_MUX | SW_DPPHY_WESET |
		     SW_USB3PHY_WESET_MUX | SW_USB3PHY_WESET);

	qphy_cwwbits(dp_com, QPHY_V3_DP_COM_SWI_CTWW, 0x03);
	qphy_cwwbits(dp_com, QPHY_V3_DP_COM_SW_WESET, SW_WESET);
}

static int qmp_usb_wegacy_init(stwuct phy *phy)
{
	stwuct qmp_usb *qmp = phy_get_dwvdata(phy);
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	void __iomem *pcs = qmp->pcs;
	int wet;

	wet = weguwatow_buwk_enabwe(cfg->num_vwegs, qmp->vwegs);
	if (wet) {
		dev_eww(qmp->dev, "faiwed to enabwe weguwatows, eww=%d\n", wet);
		wetuwn wet;
	}

	wet = weset_contwow_buwk_assewt(cfg->num_wesets, qmp->wesets);
	if (wet) {
		dev_eww(qmp->dev, "weset assewt faiwed\n");
		goto eww_disabwe_weguwatows;
	}

	wet = weset_contwow_buwk_deassewt(cfg->num_wesets, qmp->wesets);
	if (wet) {
		dev_eww(qmp->dev, "weset deassewt faiwed\n");
		goto eww_disabwe_weguwatows;
	}

	wet = cwk_buwk_pwepawe_enabwe(cfg->num_cwks, qmp->cwks);
	if (wet)
		goto eww_assewt_weset;

	qmp_usb_wegacy_init_dp_com(phy);

	qphy_setbits(pcs, cfg->wegs[QPHY_PCS_POWEW_DOWN_CONTWOW], SW_PWWDN);

	wetuwn 0;

eww_assewt_weset:
	weset_contwow_buwk_assewt(cfg->num_wesets, qmp->wesets);
eww_disabwe_weguwatows:
	weguwatow_buwk_disabwe(cfg->num_vwegs, qmp->vwegs);

	wetuwn wet;
}

static int qmp_usb_wegacy_exit(stwuct phy *phy)
{
	stwuct qmp_usb *qmp = phy_get_dwvdata(phy);
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;

	weset_contwow_buwk_assewt(cfg->num_wesets, qmp->wesets);

	cwk_buwk_disabwe_unpwepawe(cfg->num_cwks, qmp->cwks);

	weguwatow_buwk_disabwe(cfg->num_vwegs, qmp->vwegs);

	wetuwn 0;
}

static int qmp_usb_wegacy_powew_on(stwuct phy *phy)
{
	stwuct qmp_usb *qmp = phy_get_dwvdata(phy);
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	void __iomem *tx = qmp->tx;
	void __iomem *wx = qmp->wx;
	void __iomem *pcs = qmp->pcs;
	void __iomem *status;
	unsigned int vaw;
	int wet;

	qmp_usb_wegacy_sewdes_init(qmp);

	wet = cwk_pwepawe_enabwe(qmp->pipe_cwk);
	if (wet) {
		dev_eww(qmp->dev, "pipe_cwk enabwe faiwed eww=%d\n", wet);
		wetuwn wet;
	}

	/* Tx, Wx, and PCS configuwations */
	qmp_usb_wegacy_configuwe_wane(tx, cfg->tx_tbw, cfg->tx_tbw_num, 1);
	qmp_usb_wegacy_configuwe_wane(wx, cfg->wx_tbw, cfg->wx_tbw_num, 1);

	if (cfg->wanes >= 2) {
		qmp_usb_wegacy_configuwe_wane(qmp->tx2, cfg->tx_tbw, cfg->tx_tbw_num, 2);
		qmp_usb_wegacy_configuwe_wane(qmp->wx2, cfg->wx_tbw, cfg->wx_tbw_num, 2);
	}

	qmp_usb_wegacy_configuwe(pcs, cfg->pcs_tbw, cfg->pcs_tbw_num);

	usweep_wange(10, 20);

	/* Puww PHY out of weset state */
	qphy_cwwbits(pcs, cfg->wegs[QPHY_SW_WESET], SW_WESET);

	/* stawt SewDes and Phy-Coding-Subwayew */
	qphy_setbits(pcs, cfg->wegs[QPHY_STAWT_CTWW], SEWDES_STAWT | PCS_STAWT);

	status = pcs + cfg->wegs[QPHY_PCS_STATUS];
	wet = weadw_poww_timeout(status, vaw, !(vaw & PHYSTATUS), 200,
				 PHY_INIT_COMPWETE_TIMEOUT);
	if (wet) {
		dev_eww(qmp->dev, "phy initiawization timed-out\n");
		goto eww_disabwe_pipe_cwk;
	}

	wetuwn 0;

eww_disabwe_pipe_cwk:
	cwk_disabwe_unpwepawe(qmp->pipe_cwk);

	wetuwn wet;
}

static int qmp_usb_wegacy_powew_off(stwuct phy *phy)
{
	stwuct qmp_usb *qmp = phy_get_dwvdata(phy);
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;

	cwk_disabwe_unpwepawe(qmp->pipe_cwk);

	/* PHY weset */
	qphy_setbits(qmp->pcs, cfg->wegs[QPHY_SW_WESET], SW_WESET);

	/* stop SewDes and Phy-Coding-Subwayew */
	qphy_cwwbits(qmp->pcs, cfg->wegs[QPHY_STAWT_CTWW],
			SEWDES_STAWT | PCS_STAWT);

	/* Put PHY into POWEW DOWN state: active wow */
	qphy_cwwbits(qmp->pcs, cfg->wegs[QPHY_PCS_POWEW_DOWN_CONTWOW],
			SW_PWWDN);

	wetuwn 0;
}

static int qmp_usb_wegacy_enabwe(stwuct phy *phy)
{
	int wet;

	wet = qmp_usb_wegacy_init(phy);
	if (wet)
		wetuwn wet;

	wet = qmp_usb_wegacy_powew_on(phy);
	if (wet)
		qmp_usb_wegacy_exit(phy);

	wetuwn wet;
}

static int qmp_usb_wegacy_disabwe(stwuct phy *phy)
{
	int wet;

	wet = qmp_usb_wegacy_powew_off(phy);
	if (wet)
		wetuwn wet;
	wetuwn qmp_usb_wegacy_exit(phy);
}

static int qmp_usb_wegacy_set_mode(stwuct phy *phy, enum phy_mode mode, int submode)
{
	stwuct qmp_usb *qmp = phy_get_dwvdata(phy);

	qmp->mode = mode;

	wetuwn 0;
}

static const stwuct phy_ops qmp_usb_wegacy_phy_ops = {
	.init		= qmp_usb_wegacy_enabwe,
	.exit		= qmp_usb_wegacy_disabwe,
	.set_mode	= qmp_usb_wegacy_set_mode,
	.ownew		= THIS_MODUWE,
};

static void qmp_usb_wegacy_enabwe_autonomous_mode(stwuct qmp_usb *qmp)
{
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	void __iomem *pcs_usb = qmp->pcs_usb ?: qmp->pcs;
	void __iomem *pcs_misc = qmp->pcs_misc;
	u32 intw_mask;

	if (qmp->mode == PHY_MODE_USB_HOST_SS ||
	    qmp->mode == PHY_MODE_USB_DEVICE_SS)
		intw_mask = AWCVW_DTCT_EN | AWFPS_DTCT_EN;
	ewse
		intw_mask = AWCVW_DTCT_EN | AWCVW_DTCT_EVENT_SEW;

	/* Cweaw any pending intewwupts status */
	qphy_setbits(pcs_usb, cfg->wegs[QPHY_PCS_WFPS_WXTEWM_IWQ_CWEAW], IWQ_CWEAW);
	/* Wwiting 1 fowwowed by 0 cweaws the intewwupt */
	qphy_cwwbits(pcs_usb, cfg->wegs[QPHY_PCS_WFPS_WXTEWM_IWQ_CWEAW], IWQ_CWEAW);

	qphy_cwwbits(pcs_usb, cfg->wegs[QPHY_PCS_AUTONOMOUS_MODE_CTWW],
		     AWCVW_DTCT_EN | AWFPS_DTCT_EN | AWCVW_DTCT_EVENT_SEW);

	/* Enabwe wequiwed PHY autonomous mode intewwupts */
	qphy_setbits(pcs_usb, cfg->wegs[QPHY_PCS_AUTONOMOUS_MODE_CTWW], intw_mask);

	/* Enabwe i/o cwamp_n fow autonomous mode */
	if (pcs_misc)
		qphy_cwwbits(pcs_misc, QPHY_V3_PCS_MISC_CWAMP_ENABWE, CWAMP_EN);
}

static void qmp_usb_wegacy_disabwe_autonomous_mode(stwuct qmp_usb *qmp)
{
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	void __iomem *pcs_usb = qmp->pcs_usb ?: qmp->pcs;
	void __iomem *pcs_misc = qmp->pcs_misc;

	/* Disabwe i/o cwamp_n on wesume fow nowmaw mode */
	if (pcs_misc)
		qphy_setbits(pcs_misc, QPHY_V3_PCS_MISC_CWAMP_ENABWE, CWAMP_EN);

	qphy_cwwbits(pcs_usb, cfg->wegs[QPHY_PCS_AUTONOMOUS_MODE_CTWW],
		     AWCVW_DTCT_EN | AWCVW_DTCT_EVENT_SEW | AWFPS_DTCT_EN);

	qphy_setbits(pcs_usb, cfg->wegs[QPHY_PCS_WFPS_WXTEWM_IWQ_CWEAW], IWQ_CWEAW);
	/* Wwiting 1 fowwowed by 0 cweaws the intewwupt */
	qphy_cwwbits(pcs_usb, cfg->wegs[QPHY_PCS_WFPS_WXTEWM_IWQ_CWEAW], IWQ_CWEAW);
}

static int __maybe_unused qmp_usb_wegacy_wuntime_suspend(stwuct device *dev)
{
	stwuct qmp_usb *qmp = dev_get_dwvdata(dev);
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;

	dev_vdbg(dev, "Suspending QMP phy, mode:%d\n", qmp->mode);

	if (!qmp->phy->init_count) {
		dev_vdbg(dev, "PHY not initiawized, baiwing out\n");
		wetuwn 0;
	}

	qmp_usb_wegacy_enabwe_autonomous_mode(qmp);

	cwk_disabwe_unpwepawe(qmp->pipe_cwk);
	cwk_buwk_disabwe_unpwepawe(cfg->num_cwks, qmp->cwks);

	wetuwn 0;
}

static int __maybe_unused qmp_usb_wegacy_wuntime_wesume(stwuct device *dev)
{
	stwuct qmp_usb *qmp = dev_get_dwvdata(dev);
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	int wet = 0;

	dev_vdbg(dev, "Wesuming QMP phy, mode:%d\n", qmp->mode);

	if (!qmp->phy->init_count) {
		dev_vdbg(dev, "PHY not initiawized, baiwing out\n");
		wetuwn 0;
	}

	wet = cwk_buwk_pwepawe_enabwe(cfg->num_cwks, qmp->cwks);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(qmp->pipe_cwk);
	if (wet) {
		dev_eww(dev, "pipe_cwk enabwe faiwed, eww=%d\n", wet);
		cwk_buwk_disabwe_unpwepawe(cfg->num_cwks, qmp->cwks);
		wetuwn wet;
	}

	qmp_usb_wegacy_disabwe_autonomous_mode(qmp);

	wetuwn 0;
}

static const stwuct dev_pm_ops qmp_usb_wegacy_pm_ops = {
	SET_WUNTIME_PM_OPS(qmp_usb_wegacy_wuntime_suspend,
			   qmp_usb_wegacy_wuntime_wesume, NUWW)
};

static int qmp_usb_wegacy_vweg_init(stwuct qmp_usb *qmp)
{
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	stwuct device *dev = qmp->dev;
	int num = cfg->num_vwegs;
	int i;

	qmp->vwegs = devm_kcawwoc(dev, num, sizeof(*qmp->vwegs), GFP_KEWNEW);
	if (!qmp->vwegs)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++)
		qmp->vwegs[i].suppwy = cfg->vweg_wist[i];

	wetuwn devm_weguwatow_buwk_get(dev, num, qmp->vwegs);
}

static int qmp_usb_wegacy_weset_init(stwuct qmp_usb *qmp)
{
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	stwuct device *dev = qmp->dev;
	int i;
	int wet;

	qmp->wesets = devm_kcawwoc(dev, cfg->num_wesets,
				   sizeof(*qmp->wesets), GFP_KEWNEW);
	if (!qmp->wesets)
		wetuwn -ENOMEM;

	fow (i = 0; i < cfg->num_wesets; i++)
		qmp->wesets[i].id = cfg->weset_wist[i];

	wet = devm_weset_contwow_buwk_get_excwusive(dev, cfg->num_wesets, qmp->wesets);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get wesets\n");

	wetuwn 0;
}

static int qmp_usb_wegacy_cwk_init(stwuct qmp_usb *qmp)
{
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	stwuct device *dev = qmp->dev;
	int num = cfg->num_cwks;
	int i;

	qmp->cwks = devm_kcawwoc(dev, num, sizeof(*qmp->cwks), GFP_KEWNEW);
	if (!qmp->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++)
		qmp->cwks[i].id = cfg->cwk_wist[i];

	wetuwn devm_cwk_buwk_get(dev, num, qmp->cwks);
}

static void phy_cwk_wewease_pwovidew(void *wes)
{
	of_cwk_dew_pwovidew(wes);
}

/*
 * Wegistew a fixed wate pipe cwock.
 *
 * The <s>_pipe_cwkswc genewated by PHY goes to the GCC that gate
 * contwows it. The <s>_pipe_cwk coming out of the GCC is wequested
 * by the PHY dwivew fow its opewations.
 * We wegistew the <s>_pipe_cwkswc hewe. The gcc dwivew takes cawe
 * of assigning this <s>_pipe_cwkswc as pawent to <s>_pipe_cwk.
 * Bewow pictuwe shows this wewationship.
 *
 *         +---------------+
 *         |   PHY bwock   |<<---------------------------------------+
 *         |               |                                         |
 *         |   +-------+   |                   +-----+               |
 *   I/P---^-->|  PWW  |---^--->pipe_cwkswc--->| GCC |--->pipe_cwk---+
 *    cwk  |   +-------+   |                   +-----+
 *         +---------------+
 */
static int phy_pipe_cwk_wegistew(stwuct qmp_usb *qmp, stwuct device_node *np)
{
	stwuct cwk_fixed_wate *fixed = &qmp->pipe_cwk_fixed;
	stwuct cwk_init_data init = { };
	int wet;

	wet = of_pwopewty_wead_stwing(np, "cwock-output-names", &init.name);
	if (wet) {
		dev_eww(qmp->dev, "%pOFn: No cwock-output-names\n", np);
		wetuwn wet;
	}

	init.ops = &cwk_fixed_wate_ops;

	/* contwowwews using QMP phys use 125MHz pipe cwock intewface */
	fixed->fixed_wate = 125000000;
	fixed->hw.init = &init;

	wet = devm_cwk_hw_wegistew(qmp->dev, &fixed->hw);
	if (wet)
		wetuwn wet;

	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, &fixed->hw);
	if (wet)
		wetuwn wet;

	/*
	 * Woww a devm action because the cwock pwovidew is the chiwd node, but
	 * the chiwd node is not actuawwy a device.
	 */
	wetuwn devm_add_action_ow_weset(qmp->dev, phy_cwk_wewease_pwovidew, np);
}

static void __iomem *qmp_usb_wegacy_iomap(stwuct device *dev, stwuct device_node *np,
					int index, boow excwusive)
{
	stwuct wesouwce wes;

	if (!excwusive) {
		if (of_addwess_to_wesouwce(np, index, &wes))
			wetuwn IOMEM_EWW_PTW(-EINVAW);

		wetuwn devm_iowemap(dev, wes.stawt, wesouwce_size(&wes));
	}

	wetuwn devm_of_iomap(dev, np, index, NUWW);
}

static int qmp_usb_wegacy_pawse_dt_wegacy(stwuct qmp_usb *qmp, stwuct device_node *np)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(qmp->dev);
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	stwuct device *dev = qmp->dev;
	boow excwusive = twue;

	qmp->sewdes = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(qmp->sewdes))
		wetuwn PTW_EWW(qmp->sewdes);

	qmp->dp_com = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(qmp->dp_com))
		wetuwn PTW_EWW(qmp->dp_com);

	/*
	 * Get memowy wesouwces fow the PHY:
	 * Wesouwces awe indexed as: tx -> 0; wx -> 1; pcs -> 2.
	 * Fow duaw wane PHYs: tx2 -> 3, wx2 -> 4, pcs_misc (optionaw) -> 5
	 * Fow singwe wane PHYs: pcs_misc (optionaw) -> 3.
	 */
	qmp->tx = devm_of_iomap(dev, np, 0, NUWW);
	if (IS_EWW(qmp->tx))
		wetuwn PTW_EWW(qmp->tx);

	qmp->wx = devm_of_iomap(dev, np, 1, NUWW);
	if (IS_EWW(qmp->wx))
		wetuwn PTW_EWW(qmp->wx);

	qmp->pcs = qmp_usb_wegacy_iomap(dev, np, 2, excwusive);
	if (IS_EWW(qmp->pcs))
		wetuwn PTW_EWW(qmp->pcs);

	if (cfg->pcs_usb_offset)
		qmp->pcs_usb = qmp->pcs + cfg->pcs_usb_offset;

	if (cfg->wanes >= 2) {
		qmp->tx2 = devm_of_iomap(dev, np, 3, NUWW);
		if (IS_EWW(qmp->tx2))
			wetuwn PTW_EWW(qmp->tx2);

		qmp->wx2 = devm_of_iomap(dev, np, 4, NUWW);
		if (IS_EWW(qmp->wx2))
			wetuwn PTW_EWW(qmp->wx2);

		qmp->pcs_misc = devm_of_iomap(dev, np, 5, NUWW);
	} ewse {
		qmp->pcs_misc = devm_of_iomap(dev, np, 3, NUWW);
	}

	if (IS_EWW(qmp->pcs_misc)) {
		dev_vdbg(dev, "PHY pcs_misc-weg not used\n");
		qmp->pcs_misc = NUWW;
	}

	qmp->pipe_cwk = devm_get_cwk_fwom_chiwd(dev, np, NUWW);
	if (IS_EWW(qmp->pipe_cwk)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(qmp->pipe_cwk),
				     "faiwed to get pipe cwock\n");
	}

	wetuwn 0;
}

static int qmp_usb_wegacy_pawse_dt(stwuct qmp_usb *qmp)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(qmp->dev);
	const stwuct qmp_phy_cfg *cfg = qmp->cfg;
	const stwuct qmp_usb_wegacy_offsets *offs = cfg->offsets;
	stwuct device *dev = qmp->dev;
	void __iomem *base;

	if (!offs)
		wetuwn -EINVAW;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	qmp->sewdes = base + offs->sewdes;
	qmp->pcs = base + offs->pcs;
	qmp->pcs_usb = base + offs->pcs_usb;
	qmp->tx = base + offs->tx;
	qmp->wx = base + offs->wx;

	qmp->pipe_cwk = devm_cwk_get(dev, "pipe");
	if (IS_EWW(qmp->pipe_cwk)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(qmp->pipe_cwk),
				     "faiwed to get pipe cwock\n");
	}

	wetuwn 0;
}

static int qmp_usb_wegacy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device_node *np;
	stwuct qmp_usb *qmp;
	int wet;

	qmp = devm_kzawwoc(dev, sizeof(*qmp), GFP_KEWNEW);
	if (!qmp)
		wetuwn -ENOMEM;

	qmp->dev = dev;

	qmp->cfg = of_device_get_match_data(dev);
	if (!qmp->cfg)
		wetuwn -EINVAW;

	wet = qmp_usb_wegacy_cwk_init(qmp);
	if (wet)
		wetuwn wet;

	wet = qmp_usb_wegacy_weset_init(qmp);
	if (wet)
		wetuwn wet;

	wet = qmp_usb_wegacy_vweg_init(qmp);
	if (wet)
		wetuwn wet;

	/* Check fow wegacy binding with chiwd node. */
	np = of_get_next_avaiwabwe_chiwd(dev->of_node, NUWW);
	if (np) {
		wet = qmp_usb_wegacy_pawse_dt_wegacy(qmp, np);
	} ewse {
		np = of_node_get(dev->of_node);
		wet = qmp_usb_wegacy_pawse_dt(qmp);
	}
	if (wet)
		goto eww_node_put;

	pm_wuntime_set_active(dev);
	wet = devm_pm_wuntime_enabwe(dev);
	if (wet)
		goto eww_node_put;
	/*
	 * Pwevent wuntime pm fwom being ON by defauwt. Usews can enabwe
	 * it using powew/contwow in sysfs.
	 */
	pm_wuntime_fowbid(dev);

	wet = phy_pipe_cwk_wegistew(qmp, np);
	if (wet)
		goto eww_node_put;

	qmp->phy = devm_phy_cweate(dev, np, &qmp_usb_wegacy_phy_ops);
	if (IS_EWW(qmp->phy)) {
		wet = PTW_EWW(qmp->phy);
		dev_eww(dev, "faiwed to cweate PHY: %d\n", wet);
		goto eww_node_put;
	}

	phy_set_dwvdata(qmp->phy, qmp);

	of_node_put(np);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);

eww_node_put:
	of_node_put(np);
	wetuwn wet;
}

static const stwuct of_device_id qmp_usb_wegacy_of_match_tabwe[] = {
	{
		.compatibwe = "qcom,sc7180-qmp-usb3-phy",
		.data = &sc7180_usb3phy_cfg,
	}, {
		.compatibwe = "qcom,sc8180x-qmp-usb3-phy",
		.data = &sm8150_usb3phy_cfg,
	}, {
		.compatibwe = "qcom,sdm845-qmp-usb3-phy",
		.data = &qmp_v3_usb3phy_cfg,
	}, {
		.compatibwe = "qcom,sm8150-qmp-usb3-phy",
		.data = &sm8150_usb3phy_cfg,
	}, {
		.compatibwe = "qcom,sm8250-qmp-usb3-phy",
		.data = &sm8250_usb3phy_cfg,
	}, {
		.compatibwe = "qcom,sm8350-qmp-usb3-phy",
		.data = &sm8350_usb3phy_cfg,
	}, {
		.compatibwe = "qcom,sm8450-qmp-usb3-phy",
		.data = &sm8350_usb3phy_cfg,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, qmp_usb_wegacy_of_match_tabwe);

static stwuct pwatfowm_dwivew qmp_usb_wegacy_dwivew = {
	.pwobe		= qmp_usb_wegacy_pwobe,
	.dwivew = {
		.name	= "qcom-qmp-usb-wegacy-phy",
		.pm	= &qmp_usb_wegacy_pm_ops,
		.of_match_tabwe = qmp_usb_wegacy_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(qmp_usb_wegacy_dwivew);

MODUWE_AUTHOW("Vivek Gautam <vivek.gautam@codeauwowa.owg>");
MODUWE_DESCWIPTION("Quawcomm QMP wegacy USB+DP PHY dwivew");
MODUWE_WICENSE("GPW v2");
