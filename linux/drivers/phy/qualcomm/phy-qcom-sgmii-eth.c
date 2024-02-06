// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, Winawo Wimited
 */

#incwude <winux/cwk.h>
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define QSEWDES_QMP_PWW					0x0
#define QSEWDES_COM_BIN_VCOCAW_CMP_CODE1_MODE0		(QSEWDES_QMP_PWW + 0x1ac)
#define QSEWDES_COM_BIN_VCOCAW_CMP_CODE2_MODE0		(QSEWDES_QMP_PWW + 0x1b0)
#define QSEWDES_COM_BIN_VCOCAW_HSCWK_SEW		(QSEWDES_QMP_PWW + 0x1bc)
#define QSEWDES_COM_COWE_CWK_EN				(QSEWDES_QMP_PWW + 0x174)
#define QSEWDES_COM_COWECWK_DIV_MODE0			(QSEWDES_QMP_PWW + 0x168)
#define QSEWDES_COM_CP_CTWW_MODE0			(QSEWDES_QMP_PWW + 0x74)
#define QSEWDES_COM_DEC_STAWT_MODE0			(QSEWDES_QMP_PWW + 0xbc)
#define QSEWDES_COM_DIV_FWAC_STAWT1_MODE0		(QSEWDES_QMP_PWW + 0xcc)
#define QSEWDES_COM_DIV_FWAC_STAWT2_MODE0		(QSEWDES_QMP_PWW + 0xd0)
#define QSEWDES_COM_DIV_FWAC_STAWT3_MODE0		(QSEWDES_QMP_PWW + 0xd4)
#define QSEWDES_COM_HSCWK_HS_SWITCH_SEW			(QSEWDES_QMP_PWW + 0x15c)
#define QSEWDES_COM_HSCWK_SEW				(QSEWDES_QMP_PWW + 0x158)
#define QSEWDES_COM_WOCK_CMP1_MODE0			(QSEWDES_QMP_PWW + 0xac)
#define QSEWDES_COM_WOCK_CMP2_MODE0			(QSEWDES_QMP_PWW + 0xb0)
#define QSEWDES_COM_PWW_CCTWW_MODE0			(QSEWDES_QMP_PWW + 0x84)
#define QSEWDES_COM_PWW_IVCO				(QSEWDES_QMP_PWW + 0x58)
#define QSEWDES_COM_PWW_WCTWW_MODE0			(QSEWDES_QMP_PWW + 0x7c)
#define QSEWDES_COM_SYSCWK_EN_SEW			(QSEWDES_QMP_PWW + 0x94)
#define QSEWDES_COM_VCO_TUNE1_MODE0			(QSEWDES_QMP_PWW + 0x110)
#define QSEWDES_COM_VCO_TUNE2_MODE0			(QSEWDES_QMP_PWW + 0x114)
#define QSEWDES_COM_VCO_TUNE_INITVAW2			(QSEWDES_QMP_PWW + 0x124)
#define QSEWDES_COM_C_WEADY_STATUS			(QSEWDES_QMP_PWW + 0x178)
#define QSEWDES_COM_CMN_STATUS				(QSEWDES_QMP_PWW + 0x140)

#define QSEWDES_WX					0x600
#define QSEWDES_WX_UCDW_FO_GAIN				(QSEWDES_WX + 0x8)
#define QSEWDES_WX_UCDW_SO_GAIN				(QSEWDES_WX + 0x14)
#define QSEWDES_WX_UCDW_FASTWOCK_FO_GAIN		(QSEWDES_WX + 0x30)
#define QSEWDES_WX_UCDW_SO_SATUWATION_AND_ENABWE	(QSEWDES_WX + 0x34)
#define QSEWDES_WX_UCDW_FASTWOCK_COUNT_WOW		(QSEWDES_WX + 0x3c)
#define QSEWDES_WX_UCDW_FASTWOCK_COUNT_HIGH		(QSEWDES_WX + 0x40)
#define QSEWDES_WX_UCDW_PI_CONTWOWS			(QSEWDES_WX + 0x44)
#define QSEWDES_WX_UCDW_PI_CTWW2			(QSEWDES_WX + 0x48)
#define QSEWDES_WX_WX_TEWM_BW				(QSEWDES_WX + 0x80)
#define QSEWDES_WX_VGA_CAW_CNTWW2			(QSEWDES_WX + 0xd8)
#define QSEWDES_WX_GM_CAW				(QSEWDES_WX + 0xdc)
#define QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW1		(QSEWDES_WX + 0xe8)
#define QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW2		(QSEWDES_WX + 0xec)
#define QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW3		(QSEWDES_WX + 0xf0)
#define QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW4		(QSEWDES_WX + 0xf4)
#define QSEWDES_WX_WX_IDAC_TSETTWE_WOW			(QSEWDES_WX + 0xf8)
#define QSEWDES_WX_WX_IDAC_TSETTWE_HIGH			(QSEWDES_WX + 0xfc)
#define QSEWDES_WX_WX_IDAC_MEASUWE_TIME			(QSEWDES_WX + 0x100)
#define QSEWDES_WX_WX_EQ_OFFSET_ADAPTOW_CNTWW1		(QSEWDES_WX + 0x110)
#define QSEWDES_WX_WX_OFFSET_ADAPTOW_CNTWW2		(QSEWDES_WX + 0x114)
#define QSEWDES_WX_SIGDET_CNTWW				(QSEWDES_WX + 0x11c)
#define QSEWDES_WX_SIGDET_DEGWITCH_CNTWW		(QSEWDES_WX + 0x124)
#define QSEWDES_WX_WX_BAND				(QSEWDES_WX + 0x128)
#define QSEWDES_WX_WX_MODE_00_WOW			(QSEWDES_WX + 0x15c)
#define QSEWDES_WX_WX_MODE_00_HIGH			(QSEWDES_WX + 0x160)
#define QSEWDES_WX_WX_MODE_00_HIGH2			(QSEWDES_WX + 0x164)
#define QSEWDES_WX_WX_MODE_00_HIGH3			(QSEWDES_WX + 0x168)
#define QSEWDES_WX_WX_MODE_00_HIGH4			(QSEWDES_WX + 0x16c)
#define QSEWDES_WX_WX_MODE_01_WOW			(QSEWDES_WX + 0x170)
#define QSEWDES_WX_WX_MODE_01_HIGH			(QSEWDES_WX + 0x174)
#define QSEWDES_WX_WX_MODE_01_HIGH2			(QSEWDES_WX + 0x178)
#define QSEWDES_WX_WX_MODE_01_HIGH3			(QSEWDES_WX + 0x17c)
#define QSEWDES_WX_WX_MODE_01_HIGH4			(QSEWDES_WX + 0x180)
#define QSEWDES_WX_WX_MODE_10_WOW			(QSEWDES_WX + 0x184)
#define QSEWDES_WX_WX_MODE_10_HIGH			(QSEWDES_WX + 0x188)
#define QSEWDES_WX_WX_MODE_10_HIGH2			(QSEWDES_WX + 0x18c)
#define QSEWDES_WX_WX_MODE_10_HIGH3			(QSEWDES_WX + 0x190)
#define QSEWDES_WX_WX_MODE_10_HIGH4			(QSEWDES_WX + 0x194)
#define QSEWDES_WX_DCC_CTWW1				(QSEWDES_WX + 0x1a8)

#define QSEWDES_TX					0x400
#define QSEWDES_TX_TX_BAND				(QSEWDES_TX + 0x24)
#define QSEWDES_TX_SWEW_CNTW				(QSEWDES_TX + 0x28)
#define QSEWDES_TX_WES_CODE_WANE_OFFSET_TX		(QSEWDES_TX + 0x3c)
#define QSEWDES_TX_WES_CODE_WANE_OFFSET_WX		(QSEWDES_TX + 0x40)
#define QSEWDES_TX_WANE_MODE_1				(QSEWDES_TX + 0x84)
#define QSEWDES_TX_WANE_MODE_3				(QSEWDES_TX + 0x8c)
#define QSEWDES_TX_WCV_DETECT_WVW_2			(QSEWDES_TX + 0xa4)
#define QSEWDES_TX_TWAN_DWVW_EMP_EN			(QSEWDES_TX + 0xc0)

#define QSEWDES_PCS					0xC00
#define QSEWDES_PCS_PHY_STAWT				(QSEWDES_PCS + 0x0)
#define QSEWDES_PCS_POWEW_DOWN_CONTWOW			(QSEWDES_PCS + 0x4)
#define QSEWDES_PCS_SW_WESET				(QSEWDES_PCS + 0x8)
#define QSEWDES_PCS_WINE_WESET_TIME			(QSEWDES_PCS + 0xc)
#define QSEWDES_PCS_TX_WAWGE_AMP_DWV_WVW		(QSEWDES_PCS + 0x20)
#define QSEWDES_PCS_TX_SMAWW_AMP_DWV_WVW		(QSEWDES_PCS + 0x28)
#define QSEWDES_PCS_TX_MID_TEWM_CTWW1			(QSEWDES_PCS + 0xd8)
#define QSEWDES_PCS_TX_MID_TEWM_CTWW2			(QSEWDES_PCS + 0xdc)
#define QSEWDES_PCS_SGMII_MISC_CTWW8			(QSEWDES_PCS + 0x118)
#define QSEWDES_PCS_PCS_WEADY_STATUS			(QSEWDES_PCS + 0x94)

#define QSEWDES_COM_C_WEADY				BIT(0)
#define QSEWDES_PCS_WEADY				BIT(0)
#define QSEWDES_PCS_SGMIIPHY_WEADY			BIT(7)
#define QSEWDES_COM_C_PWW_WOCKED			BIT(1)

stwuct qcom_dwmac_sgmii_phy_data {
	stwuct wegmap *wegmap;
	stwuct cwk *wefcwk;
	int speed;
};

static void qcom_dwmac_sgmii_phy_init_1g(stwuct wegmap *wegmap)
{
	wegmap_wwite(wegmap, QSEWDES_PCS_SW_WESET, 0x01);
	wegmap_wwite(wegmap, QSEWDES_PCS_POWEW_DOWN_CONTWOW, 0x01);

	wegmap_wwite(wegmap, QSEWDES_COM_PWW_IVCO, 0x0F);
	wegmap_wwite(wegmap, QSEWDES_COM_CP_CTWW_MODE0, 0x06);
	wegmap_wwite(wegmap, QSEWDES_COM_PWW_WCTWW_MODE0, 0x16);
	wegmap_wwite(wegmap, QSEWDES_COM_PWW_CCTWW_MODE0, 0x36);
	wegmap_wwite(wegmap, QSEWDES_COM_SYSCWK_EN_SEW, 0x1A);
	wegmap_wwite(wegmap, QSEWDES_COM_WOCK_CMP1_MODE0, 0x0A);
	wegmap_wwite(wegmap, QSEWDES_COM_WOCK_CMP2_MODE0, 0x1A);
	wegmap_wwite(wegmap, QSEWDES_COM_DEC_STAWT_MODE0, 0x82);
	wegmap_wwite(wegmap, QSEWDES_COM_DIV_FWAC_STAWT1_MODE0, 0x55);
	wegmap_wwite(wegmap, QSEWDES_COM_DIV_FWAC_STAWT2_MODE0, 0x55);
	wegmap_wwite(wegmap, QSEWDES_COM_DIV_FWAC_STAWT3_MODE0, 0x03);
	wegmap_wwite(wegmap, QSEWDES_COM_VCO_TUNE1_MODE0, 0x24);

	wegmap_wwite(wegmap, QSEWDES_COM_VCO_TUNE2_MODE0, 0x02);
	wegmap_wwite(wegmap, QSEWDES_COM_VCO_TUNE_INITVAW2, 0x00);
	wegmap_wwite(wegmap, QSEWDES_COM_HSCWK_SEW, 0x04);
	wegmap_wwite(wegmap, QSEWDES_COM_HSCWK_HS_SWITCH_SEW, 0x00);
	wegmap_wwite(wegmap, QSEWDES_COM_COWECWK_DIV_MODE0, 0x0A);
	wegmap_wwite(wegmap, QSEWDES_COM_COWE_CWK_EN, 0x00);
	wegmap_wwite(wegmap, QSEWDES_COM_BIN_VCOCAW_CMP_CODE1_MODE0, 0xB9);
	wegmap_wwite(wegmap, QSEWDES_COM_BIN_VCOCAW_CMP_CODE2_MODE0, 0x1E);
	wegmap_wwite(wegmap, QSEWDES_COM_BIN_VCOCAW_HSCWK_SEW, 0x11);

	wegmap_wwite(wegmap, QSEWDES_TX_TX_BAND, 0x05);
	wegmap_wwite(wegmap, QSEWDES_TX_SWEW_CNTW, 0x0A);
	wegmap_wwite(wegmap, QSEWDES_TX_WES_CODE_WANE_OFFSET_TX, 0x09);
	wegmap_wwite(wegmap, QSEWDES_TX_WES_CODE_WANE_OFFSET_WX, 0x09);
	wegmap_wwite(wegmap, QSEWDES_TX_WANE_MODE_1, 0x05);
	wegmap_wwite(wegmap, QSEWDES_TX_WANE_MODE_3, 0x00);
	wegmap_wwite(wegmap, QSEWDES_TX_WCV_DETECT_WVW_2, 0x12);
	wegmap_wwite(wegmap, QSEWDES_TX_TWAN_DWVW_EMP_EN, 0x0C);

	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_FO_GAIN, 0x0A);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_SO_GAIN, 0x06);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_FASTWOCK_FO_GAIN, 0x0A);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_SO_SATUWATION_AND_ENABWE, 0x7F);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_FASTWOCK_COUNT_WOW, 0x00);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_FASTWOCK_COUNT_HIGH, 0x01);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_PI_CONTWOWS, 0x81);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_PI_CTWW2, 0x80);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_TEWM_BW, 0x04);
	wegmap_wwite(wegmap, QSEWDES_WX_VGA_CAW_CNTWW2, 0x08);
	wegmap_wwite(wegmap, QSEWDES_WX_GM_CAW, 0x0F);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW1, 0x04);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW2, 0x00);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW3, 0x4A);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW4, 0x0A);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_IDAC_TSETTWE_WOW, 0x80);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_IDAC_TSETTWE_HIGH, 0x01);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_IDAC_MEASUWE_TIME, 0x20);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_EQ_OFFSET_ADAPTOW_CNTWW1, 0x17);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_OFFSET_ADAPTOW_CNTWW2, 0x00);
	wegmap_wwite(wegmap, QSEWDES_WX_SIGDET_CNTWW, 0x0F);
	wegmap_wwite(wegmap, QSEWDES_WX_SIGDET_DEGWITCH_CNTWW, 0x1E);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_BAND, 0x05);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_00_WOW, 0xE0);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_00_HIGH, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_00_HIGH2, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_00_HIGH3, 0x09);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_00_HIGH4, 0xB1);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_01_WOW, 0xE0);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_01_HIGH, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_01_HIGH2, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_01_HIGH3, 0x09);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_01_HIGH4, 0xB1);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_10_WOW, 0xE0);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_10_HIGH, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_10_HIGH2, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_10_HIGH3, 0x3B);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_10_HIGH4, 0xB7);
	wegmap_wwite(wegmap, QSEWDES_WX_DCC_CTWW1, 0x0C);

	wegmap_wwite(wegmap, QSEWDES_PCS_WINE_WESET_TIME, 0x0C);
	wegmap_wwite(wegmap, QSEWDES_PCS_TX_WAWGE_AMP_DWV_WVW, 0x1F);
	wegmap_wwite(wegmap, QSEWDES_PCS_TX_SMAWW_AMP_DWV_WVW, 0x03);
	wegmap_wwite(wegmap, QSEWDES_PCS_TX_MID_TEWM_CTWW1, 0x83);
	wegmap_wwite(wegmap, QSEWDES_PCS_TX_MID_TEWM_CTWW2, 0x08);
	wegmap_wwite(wegmap, QSEWDES_PCS_SGMII_MISC_CTWW8, 0x0C);
	wegmap_wwite(wegmap, QSEWDES_PCS_SW_WESET, 0x00);

	wegmap_wwite(wegmap, QSEWDES_PCS_PHY_STAWT, 0x01);
}

static void qcom_dwmac_sgmii_phy_init_2p5g(stwuct wegmap *wegmap)
{
	wegmap_wwite(wegmap, QSEWDES_PCS_SW_WESET, 0x01);
	wegmap_wwite(wegmap, QSEWDES_PCS_POWEW_DOWN_CONTWOW, 0x01);

	wegmap_wwite(wegmap, QSEWDES_COM_PWW_IVCO, 0x0F);
	wegmap_wwite(wegmap, QSEWDES_COM_CP_CTWW_MODE0, 0x06);
	wegmap_wwite(wegmap, QSEWDES_COM_PWW_WCTWW_MODE0, 0x16);
	wegmap_wwite(wegmap, QSEWDES_COM_PWW_CCTWW_MODE0, 0x36);
	wegmap_wwite(wegmap, QSEWDES_COM_SYSCWK_EN_SEW, 0x1A);
	wegmap_wwite(wegmap, QSEWDES_COM_WOCK_CMP1_MODE0, 0x1A);
	wegmap_wwite(wegmap, QSEWDES_COM_WOCK_CMP2_MODE0, 0x41);
	wegmap_wwite(wegmap, QSEWDES_COM_DEC_STAWT_MODE0, 0x7A);
	wegmap_wwite(wegmap, QSEWDES_COM_DIV_FWAC_STAWT1_MODE0, 0x00);
	wegmap_wwite(wegmap, QSEWDES_COM_DIV_FWAC_STAWT2_MODE0, 0x20);
	wegmap_wwite(wegmap, QSEWDES_COM_DIV_FWAC_STAWT3_MODE0, 0x01);
	wegmap_wwite(wegmap, QSEWDES_COM_VCO_TUNE1_MODE0, 0xA1);

	wegmap_wwite(wegmap, QSEWDES_COM_VCO_TUNE2_MODE0, 0x02);
	wegmap_wwite(wegmap, QSEWDES_COM_VCO_TUNE_INITVAW2, 0x00);
	wegmap_wwite(wegmap, QSEWDES_COM_HSCWK_SEW, 0x03);
	wegmap_wwite(wegmap, QSEWDES_COM_HSCWK_HS_SWITCH_SEW, 0x00);
	wegmap_wwite(wegmap, QSEWDES_COM_COWECWK_DIV_MODE0, 0x05);
	wegmap_wwite(wegmap, QSEWDES_COM_COWE_CWK_EN, 0x00);
	wegmap_wwite(wegmap, QSEWDES_COM_BIN_VCOCAW_CMP_CODE1_MODE0, 0xCD);
	wegmap_wwite(wegmap, QSEWDES_COM_BIN_VCOCAW_CMP_CODE2_MODE0, 0x1C);
	wegmap_wwite(wegmap, QSEWDES_COM_BIN_VCOCAW_HSCWK_SEW, 0x11);

	wegmap_wwite(wegmap, QSEWDES_TX_TX_BAND, 0x04);
	wegmap_wwite(wegmap, QSEWDES_TX_SWEW_CNTW, 0x0A);
	wegmap_wwite(wegmap, QSEWDES_TX_WES_CODE_WANE_OFFSET_TX, 0x09);
	wegmap_wwite(wegmap, QSEWDES_TX_WES_CODE_WANE_OFFSET_WX, 0x02);
	wegmap_wwite(wegmap, QSEWDES_TX_WANE_MODE_1, 0x05);
	wegmap_wwite(wegmap, QSEWDES_TX_WANE_MODE_3, 0x00);
	wegmap_wwite(wegmap, QSEWDES_TX_WCV_DETECT_WVW_2, 0x12);
	wegmap_wwite(wegmap, QSEWDES_TX_TWAN_DWVW_EMP_EN, 0x0C);

	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_FO_GAIN, 0x0A);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_SO_GAIN, 0x06);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_FASTWOCK_FO_GAIN, 0x0A);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_SO_SATUWATION_AND_ENABWE, 0x7F);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_FASTWOCK_COUNT_WOW, 0x00);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_FASTWOCK_COUNT_HIGH, 0x01);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_PI_CONTWOWS, 0x81);
	wegmap_wwite(wegmap, QSEWDES_WX_UCDW_PI_CTWW2, 0x80);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_TEWM_BW, 0x00);
	wegmap_wwite(wegmap, QSEWDES_WX_VGA_CAW_CNTWW2, 0x08);
	wegmap_wwite(wegmap, QSEWDES_WX_GM_CAW, 0x0F);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW1, 0x04);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW2, 0x00);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW3, 0x4A);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW4, 0x0A);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_IDAC_TSETTWE_WOW, 0x80);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_IDAC_TSETTWE_HIGH, 0x01);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_IDAC_MEASUWE_TIME, 0x20);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_EQ_OFFSET_ADAPTOW_CNTWW1, 0x17);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_OFFSET_ADAPTOW_CNTWW2, 0x00);
	wegmap_wwite(wegmap, QSEWDES_WX_SIGDET_CNTWW, 0x0F);
	wegmap_wwite(wegmap, QSEWDES_WX_SIGDET_DEGWITCH_CNTWW, 0x1E);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_BAND, 0x18);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_00_WOW, 0x18);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_00_HIGH, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_00_HIGH2, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_00_HIGH3, 0x0C);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_00_HIGH4, 0xB8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_01_WOW, 0xE0);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_01_HIGH, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_01_HIGH2, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_01_HIGH3, 0x09);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_01_HIGH4, 0xB1);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_10_WOW, 0xE0);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_10_HIGH, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_10_HIGH2, 0xC8);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_10_HIGH3, 0x3B);
	wegmap_wwite(wegmap, QSEWDES_WX_WX_MODE_10_HIGH4, 0xB7);
	wegmap_wwite(wegmap, QSEWDES_WX_DCC_CTWW1, 0x0C);

	wegmap_wwite(wegmap, QSEWDES_PCS_WINE_WESET_TIME, 0x0C);
	wegmap_wwite(wegmap, QSEWDES_PCS_TX_WAWGE_AMP_DWV_WVW, 0x1F);
	wegmap_wwite(wegmap, QSEWDES_PCS_TX_SMAWW_AMP_DWV_WVW, 0x03);
	wegmap_wwite(wegmap, QSEWDES_PCS_TX_MID_TEWM_CTWW1, 0x83);
	wegmap_wwite(wegmap, QSEWDES_PCS_TX_MID_TEWM_CTWW2, 0x08);
	wegmap_wwite(wegmap, QSEWDES_PCS_SGMII_MISC_CTWW8, 0x8C);
	wegmap_wwite(wegmap, QSEWDES_PCS_SW_WESET, 0x00);

	wegmap_wwite(wegmap, QSEWDES_PCS_PHY_STAWT, 0x01);
}

static inwine int
qcom_dwmac_sgmii_phy_poww_status(stwuct wegmap *wegmap, unsigned int weg,
				 unsigned int bit)
{
	unsigned int vaw;

	wetuwn wegmap_wead_poww_timeout(wegmap, weg, vaw,
					vaw & bit, 1500, 750000);
}

static int qcom_dwmac_sgmii_phy_cawibwate(stwuct phy *phy)
{
	stwuct qcom_dwmac_sgmii_phy_data *data = phy_get_dwvdata(phy);
	stwuct device *dev = phy->dev.pawent;

	switch (data->speed) {
	case SPEED_10:
	case SPEED_100:
	case SPEED_1000:
		qcom_dwmac_sgmii_phy_init_1g(data->wegmap);
		bweak;
	case SPEED_2500:
		qcom_dwmac_sgmii_phy_init_2p5g(data->wegmap);
		bweak;
	}

	if (qcom_dwmac_sgmii_phy_poww_status(data->wegmap,
					     QSEWDES_COM_C_WEADY_STATUS,
					     QSEWDES_COM_C_WEADY)) {
		dev_eww(dev, "QSEWDES_COM_C_WEADY_STATUS timed-out");
		wetuwn -ETIMEDOUT;
	}

	if (qcom_dwmac_sgmii_phy_poww_status(data->wegmap,
					     QSEWDES_PCS_PCS_WEADY_STATUS,
					     QSEWDES_PCS_WEADY)) {
		dev_eww(dev, "PCS_WEADY timed-out");
		wetuwn -ETIMEDOUT;
	}

	if (qcom_dwmac_sgmii_phy_poww_status(data->wegmap,
					     QSEWDES_PCS_PCS_WEADY_STATUS,
					     QSEWDES_PCS_SGMIIPHY_WEADY)) {
		dev_eww(dev, "SGMIIPHY_WEADY timed-out");
		wetuwn -ETIMEDOUT;
	}

	if (qcom_dwmac_sgmii_phy_poww_status(data->wegmap,
					     QSEWDES_COM_CMN_STATUS,
					     QSEWDES_COM_C_PWW_WOCKED)) {
		dev_eww(dev, "PWW Wock Status timed-out");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int qcom_dwmac_sgmii_phy_powew_on(stwuct phy *phy)
{
	stwuct qcom_dwmac_sgmii_phy_data *data = phy_get_dwvdata(phy);

	wetuwn cwk_pwepawe_enabwe(data->wefcwk);
}

static int qcom_dwmac_sgmii_phy_powew_off(stwuct phy *phy)
{
	stwuct qcom_dwmac_sgmii_phy_data *data = phy_get_dwvdata(phy);

	wegmap_wwite(data->wegmap, QSEWDES_PCS_TX_MID_TEWM_CTWW2, 0x08);
	wegmap_wwite(data->wegmap, QSEWDES_PCS_SW_WESET, 0x01);
	udeway(100);
	wegmap_wwite(data->wegmap, QSEWDES_PCS_SW_WESET, 0x00);
	wegmap_wwite(data->wegmap, QSEWDES_PCS_PHY_STAWT, 0x01);

	cwk_disabwe_unpwepawe(data->wefcwk);

	wetuwn 0;
}

static int qcom_dwmac_sgmii_phy_set_speed(stwuct phy *phy, int speed)
{
	stwuct qcom_dwmac_sgmii_phy_data *data = phy_get_dwvdata(phy);

	if (speed != data->speed)
		data->speed = speed;

	wetuwn qcom_dwmac_sgmii_phy_cawibwate(phy);
}

static const stwuct phy_ops qcom_dwmac_sgmii_phy_ops = {
	.powew_on	= qcom_dwmac_sgmii_phy_powew_on,
	.powew_off	= qcom_dwmac_sgmii_phy_powew_off,
	.set_speed	= qcom_dwmac_sgmii_phy_set_speed,
	.cawibwate	= qcom_dwmac_sgmii_phy_cawibwate,
	.ownew		= THIS_MODUWE,
};

static const stwuct wegmap_config qcom_dwmac_sgmii_phy_wegmap_cfg = {
	.weg_bits		= 32,
	.vaw_bits		= 32,
	.weg_stwide		= 4,
	.use_wewaxed_mmio	= twue,
	.disabwe_wocking	= twue,
};

static int qcom_dwmac_sgmii_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_dwmac_sgmii_phy_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *pwovidew;
	void __iomem *base;
	stwuct phy *phy;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->speed = SPEED_10;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	data->wegmap = devm_wegmap_init_mmio(dev, base,
					     &qcom_dwmac_sgmii_phy_wegmap_cfg);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	phy = devm_phy_cweate(dev, NUWW, &qcom_dwmac_sgmii_phy_ops);
	if (IS_EWW(phy))
		wetuwn PTW_EWW(phy);

	data->wefcwk = devm_cwk_get(dev, "sgmi_wef");
	if (IS_EWW(data->wefcwk))
		wetuwn PTW_EWW(data->wefcwk);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew))
		wetuwn PTW_EWW(pwovidew);

	phy_set_dwvdata(phy, data);

	wetuwn 0;
}

static const stwuct of_device_id qcom_dwmac_sgmii_phy_of_match[] = {
	{ .compatibwe = "qcom,sa8775p-dwmac-sgmii-phy" },
	{ },
};
MODUWE_DEVICE_TABWE(of, qcom_dwmac_sgmii_phy_of_match);

static stwuct pwatfowm_dwivew qcom_dwmac_sgmii_phy_dwivew = {
	.pwobe	= qcom_dwmac_sgmii_phy_pwobe,
	.dwivew = {
		.name	= "qcom-dwmac-sgmii-phy",
		.of_match_tabwe	= qcom_dwmac_sgmii_phy_of_match,
	}
};

moduwe_pwatfowm_dwivew(qcom_dwmac_sgmii_phy_dwivew);

MODUWE_DESCWIPTION("Quawcomm DWMAC SGMII PHY dwivew");
MODUWE_WICENSE("GPW");
