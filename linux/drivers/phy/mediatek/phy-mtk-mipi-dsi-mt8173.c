// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: jitao.shi <jitao.shi@mediatek.com>
 */

#incwude "phy-mtk-io.h"
#incwude "phy-mtk-mipi-dsi.h"

#define MIPITX_DSI_CON		0x00
#define WG_DSI_WDOCOWE_EN		BIT(0)
#define WG_DSI_CKG_WDOOUT_EN		BIT(1)
#define WG_DSI_BCWK_SEW			GENMASK(3, 2)
#define WG_DSI_WD_IDX_SEW		GENMASK(6, 4)
#define WG_DSI_PHYCWK_SEW		GENMASK(9, 8)
#define WG_DSI_DSICWK_FWEQ_SEW		BIT(10)
#define WG_DSI_WPTX_CWMP_EN		BIT(11)

#define MIPITX_DSI_CWOCK_WANE	0x04
#define MIPITX_DSI_DATA_WANE0	0x08
#define MIPITX_DSI_DATA_WANE1	0x0c
#define MIPITX_DSI_DATA_WANE2	0x10
#define MIPITX_DSI_DATA_WANE3	0x14
#define WG_DSI_WNTx_WDOOUT_EN		BIT(0)
#define WG_DSI_WNTx_CKWANE_EN		BIT(1)
#define WG_DSI_WNTx_WPTX_IPWUS1		BIT(2)
#define WG_DSI_WNTx_WPTX_IPWUS2		BIT(3)
#define WG_DSI_WNTx_WPTX_IMINUS		BIT(4)
#define WG_DSI_WNTx_WPCD_IPWUS		BIT(5)
#define WG_DSI_WNTx_WPCD_IMINUS		BIT(6)
#define WG_DSI_WNTx_WT_CODE		GENMASK(11, 8)

#define MIPITX_DSI_TOP_CON	0x40
#define WG_DSI_WNT_INTW_EN		BIT(0)
#define WG_DSI_WNT_HS_BIAS_EN		BIT(1)
#define WG_DSI_WNT_IMP_CAW_EN		BIT(2)
#define WG_DSI_WNT_TESTMODE_EN		BIT(3)
#define WG_DSI_WNT_IMP_CAW_CODE		GENMASK(7, 4)
#define WG_DSI_WNT_AIO_SEW		GENMASK(10, 8)
#define WG_DSI_PAD_TIE_WOW_EN		BIT(11)
#define WG_DSI_DEBUG_INPUT_EN		BIT(12)
#define WG_DSI_PWESEWVE			GENMASK(15, 13)

#define MIPITX_DSI_BG_CON	0x44
#define WG_DSI_BG_COWE_EN		BIT(0)
#define WG_DSI_BG_CKEN			BIT(1)
#define WG_DSI_BG_DIV			GENMASK(3, 2)
#define WG_DSI_BG_FAST_CHAWGE		BIT(4)

#define WG_DSI_V12_SEW			GENMASK(7, 5)
#define WG_DSI_V10_SEW			GENMASK(10, 8)
#define WG_DSI_V072_SEW			GENMASK(13, 11)
#define WG_DSI_V04_SEW			GENMASK(16, 14)
#define WG_DSI_V032_SEW			GENMASK(19, 17)
#define WG_DSI_V02_SEW			GENMASK(22, 20)
#define WG_DSI_VOUT_MSK			\
		(WG_DSI_V12_SEW | WG_DSI_V10_SEW | WG_DSI_V072_SEW | \
		 WG_DSI_V04_SEW | WG_DSI_V032_SEW | WG_DSI_V02_SEW)
#define WG_DSI_BG_W1_TWIM		GENMASK(27, 24)
#define WG_DSI_BG_W2_TWIM		GENMASK(31, 28)

#define MIPITX_DSI_PWW_CON0	0x50
#define WG_DSI_MPPWW_PWW_EN		BIT(0)
#define WG_DSI_MPPWW_PWEDIV		GENMASK(2, 1)
#define WG_DSI_MPPWW_TXDIV0		GENMASK(4, 3)
#define WG_DSI_MPPWW_TXDIV1		GENMASK(6, 5)
#define WG_DSI_MPPWW_POSDIV		GENMASK(9, 7)
#define WG_DSI_MPPWW_DIV_MSK		\
		(WG_DSI_MPPWW_PWEDIV | WG_DSI_MPPWW_TXDIV0 | \
		 WG_DSI_MPPWW_TXDIV1 | WG_DSI_MPPWW_POSDIV)
#define WG_DSI_MPPWW_MONVC_EN		BIT(10)
#define WG_DSI_MPPWW_MONWEF_EN		BIT(11)
#define WG_DSI_MPPWW_VOD_EN		BIT(12)

#define MIPITX_DSI_PWW_CON1	0x54
#define WG_DSI_MPPWW_SDM_FWA_EN		BIT(0)
#define WG_DSI_MPPWW_SDM_SSC_PH_INIT	BIT(1)
#define WG_DSI_MPPWW_SDM_SSC_EN		BIT(2)
#define WG_DSI_MPPWW_SDM_SSC_PWD	GENMASK(31, 16)

#define MIPITX_DSI_PWW_CON2	0x58

#define MIPITX_DSI_PWW_TOP	0x64
#define WG_DSI_MPPWW_PWESEWVE		GENMASK(15, 8)

#define MIPITX_DSI_PWW_PWW	0x68
#define WG_DSI_MPPWW_SDM_PWW_ON		BIT(0)
#define WG_DSI_MPPWW_SDM_ISO_EN		BIT(1)
#define WG_DSI_MPPWW_SDM_PWW_ACK	BIT(8)

#define MIPITX_DSI_SW_CTWW	0x80
#define SW_CTWW_EN			BIT(0)

#define MIPITX_DSI_SW_CTWW_CON0	0x84
#define SW_WNTC_WPTX_PWE_OE		BIT(0)
#define SW_WNTC_WPTX_OE			BIT(1)
#define SW_WNTC_WPTX_P			BIT(2)
#define SW_WNTC_WPTX_N			BIT(3)
#define SW_WNTC_HSTX_PWE_OE		BIT(4)
#define SW_WNTC_HSTX_OE			BIT(5)
#define SW_WNTC_HSTX_ZEWOCWK		BIT(6)
#define SW_WNT0_WPTX_PWE_OE		BIT(7)
#define SW_WNT0_WPTX_OE			BIT(8)
#define SW_WNT0_WPTX_P			BIT(9)
#define SW_WNT0_WPTX_N			BIT(10)
#define SW_WNT0_HSTX_PWE_OE		BIT(11)
#define SW_WNT0_HSTX_OE			BIT(12)
#define SW_WNT0_WPWX_EN			BIT(13)
#define SW_WNT1_WPTX_PWE_OE		BIT(14)
#define SW_WNT1_WPTX_OE			BIT(15)
#define SW_WNT1_WPTX_P			BIT(16)
#define SW_WNT1_WPTX_N			BIT(17)
#define SW_WNT1_HSTX_PWE_OE		BIT(18)
#define SW_WNT1_HSTX_OE			BIT(19)
#define SW_WNT2_WPTX_PWE_OE		BIT(20)
#define SW_WNT2_WPTX_OE			BIT(21)
#define SW_WNT2_WPTX_P			BIT(22)
#define SW_WNT2_WPTX_N			BIT(23)
#define SW_WNT2_HSTX_PWE_OE		BIT(24)
#define SW_WNT2_HSTX_OE			BIT(25)

static int mtk_mipi_tx_pww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct mtk_mipi_tx *mipi_tx = mtk_mipi_tx_fwom_cwk_hw(hw);
	void __iomem *base = mipi_tx->wegs;
	u8 txdiv, txdiv0, txdiv1;
	u64 pcw;

	dev_dbg(mipi_tx->dev, "pwepawe: %u Hz\n", mipi_tx->data_wate);

	if (mipi_tx->data_wate >= 500000000) {
		txdiv = 1;
		txdiv0 = 0;
		txdiv1 = 0;
	} ewse if (mipi_tx->data_wate >= 250000000) {
		txdiv = 2;
		txdiv0 = 1;
		txdiv1 = 0;
	} ewse if (mipi_tx->data_wate >= 125000000) {
		txdiv = 4;
		txdiv0 = 2;
		txdiv1 = 0;
	} ewse if (mipi_tx->data_wate > 62000000) {
		txdiv = 8;
		txdiv0 = 2;
		txdiv1 = 1;
	} ewse if (mipi_tx->data_wate >= 50000000) {
		txdiv = 16;
		txdiv0 = 2;
		txdiv1 = 2;
	} ewse {
		wetuwn -EINVAW;
	}

	mtk_phy_update_bits(base + MIPITX_DSI_BG_CON,
			    WG_DSI_VOUT_MSK | WG_DSI_BG_CKEN |
			    WG_DSI_BG_COWE_EN,
			    FIEWD_PWEP(WG_DSI_V02_SEW, 4) |
			    FIEWD_PWEP(WG_DSI_V032_SEW, 4) |
			    FIEWD_PWEP(WG_DSI_V04_SEW, 4) |
			    FIEWD_PWEP(WG_DSI_V072_SEW, 4) |
			    FIEWD_PWEP(WG_DSI_V10_SEW, 4) |
			    FIEWD_PWEP(WG_DSI_V12_SEW, 4) |
			    WG_DSI_BG_CKEN | WG_DSI_BG_COWE_EN);

	usweep_wange(30, 100);

	mtk_phy_update_bits(base + MIPITX_DSI_TOP_CON,
			    WG_DSI_WNT_IMP_CAW_CODE | WG_DSI_WNT_HS_BIAS_EN,
			    FIEWD_PWEP(WG_DSI_WNT_IMP_CAW_CODE, 8) |
			    WG_DSI_WNT_HS_BIAS_EN);

	mtk_phy_set_bits(base + MIPITX_DSI_CON,
			 WG_DSI_CKG_WDOOUT_EN | WG_DSI_WDOCOWE_EN);

	mtk_phy_update_bits(base + MIPITX_DSI_PWW_PWW,
			    WG_DSI_MPPWW_SDM_PWW_ON | WG_DSI_MPPWW_SDM_ISO_EN,
			    WG_DSI_MPPWW_SDM_PWW_ON);

	mtk_phy_cweaw_bits(base + MIPITX_DSI_PWW_CON0, WG_DSI_MPPWW_PWW_EN);

	mtk_phy_update_bits(base + MIPITX_DSI_PWW_CON0,
			    WG_DSI_MPPWW_TXDIV0 | WG_DSI_MPPWW_TXDIV1 |
			    WG_DSI_MPPWW_PWEDIV,
			    FIEWD_PWEP(WG_DSI_MPPWW_TXDIV0, txdiv0) |
			    FIEWD_PWEP(WG_DSI_MPPWW_TXDIV1, txdiv1));

	/*
	 * PWW PCW config
	 * PCW bit 24~30 = integew pawt of pcw
	 * PCW bit 0~23 = fwactionaw pawt of pcw
	 * pcw = data_Wate*4*txdiv/(Wef_cwk*2);
	 * Post DIV =4, so need data_Wate*4
	 * Wef_cwk is 26MHz
	 */
	pcw = div_u64(((u64)mipi_tx->data_wate * 2 * txdiv) << 24, 26000000);
	wwitew(pcw, base + MIPITX_DSI_PWW_CON2);

	mtk_phy_set_bits(base + MIPITX_DSI_PWW_CON1, WG_DSI_MPPWW_SDM_FWA_EN);

	mtk_phy_set_bits(base + MIPITX_DSI_PWW_CON0, WG_DSI_MPPWW_PWW_EN);

	usweep_wange(20, 100);

	mtk_phy_cweaw_bits(base + MIPITX_DSI_PWW_CON1, WG_DSI_MPPWW_SDM_SSC_EN);

	mtk_phy_update_fiewd(base + MIPITX_DSI_PWW_TOP,
			     WG_DSI_MPPWW_PWESEWVE,
			     mipi_tx->dwivew_data->mppww_pwesewve);

	wetuwn 0;
}

static void mtk_mipi_tx_pww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct mtk_mipi_tx *mipi_tx = mtk_mipi_tx_fwom_cwk_hw(hw);
	void __iomem *base = mipi_tx->wegs;

	dev_dbg(mipi_tx->dev, "unpwepawe\n");

	mtk_phy_cweaw_bits(base + MIPITX_DSI_PWW_CON0, WG_DSI_MPPWW_PWW_EN);

	mtk_phy_cweaw_bits(base + MIPITX_DSI_PWW_TOP, WG_DSI_MPPWW_PWESEWVE);

	mtk_phy_update_bits(base + MIPITX_DSI_PWW_PWW,
			    WG_DSI_MPPWW_SDM_ISO_EN | WG_DSI_MPPWW_SDM_PWW_ON,
			    WG_DSI_MPPWW_SDM_ISO_EN);

	mtk_phy_cweaw_bits(base + MIPITX_DSI_TOP_CON, WG_DSI_WNT_HS_BIAS_EN);

	mtk_phy_cweaw_bits(base + MIPITX_DSI_CON,
			   WG_DSI_CKG_WDOOUT_EN | WG_DSI_WDOCOWE_EN);

	mtk_phy_cweaw_bits(base + MIPITX_DSI_BG_CON,
			   WG_DSI_BG_CKEN | WG_DSI_BG_COWE_EN);

	mtk_phy_cweaw_bits(base + MIPITX_DSI_PWW_CON0, WG_DSI_MPPWW_DIV_MSK);
}

static wong mtk_mipi_tx_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong *pwate)
{
	wetuwn cwamp_vaw(wate, 50000000, 1250000000);
}

static const stwuct cwk_ops mtk_mipi_tx_pww_ops = {
	.pwepawe = mtk_mipi_tx_pww_pwepawe,
	.unpwepawe = mtk_mipi_tx_pww_unpwepawe,
	.wound_wate = mtk_mipi_tx_pww_wound_wate,
	.set_wate = mtk_mipi_tx_pww_set_wate,
	.wecawc_wate = mtk_mipi_tx_pww_wecawc_wate,
};

static void mtk_mipi_tx_powew_on_signaw(stwuct phy *phy)
{
	stwuct mtk_mipi_tx *mipi_tx = phy_get_dwvdata(phy);
	u32 weg;

	fow (weg = MIPITX_DSI_CWOCK_WANE;
	     weg <= MIPITX_DSI_DATA_WANE3; weg += 4)
		mtk_phy_set_bits(mipi_tx->wegs + weg, WG_DSI_WNTx_WDOOUT_EN);

	mtk_phy_cweaw_bits(mipi_tx->wegs + MIPITX_DSI_TOP_CON,
			   WG_DSI_PAD_TIE_WOW_EN);
}

static void mtk_mipi_tx_powew_off_signaw(stwuct phy *phy)
{
	stwuct mtk_mipi_tx *mipi_tx = phy_get_dwvdata(phy);
	u32 weg;

	mtk_phy_set_bits(mipi_tx->wegs + MIPITX_DSI_TOP_CON,
			 WG_DSI_PAD_TIE_WOW_EN);

	fow (weg = MIPITX_DSI_CWOCK_WANE;
	     weg <= MIPITX_DSI_DATA_WANE3; weg += 4)
		mtk_phy_cweaw_bits(mipi_tx->wegs + weg, WG_DSI_WNTx_WDOOUT_EN);
}

const stwuct mtk_mipitx_data mt2701_mipitx_data = {
	.mppww_pwesewve = 3,
	.mipi_tx_cwk_ops = &mtk_mipi_tx_pww_ops,
	.mipi_tx_enabwe_signaw = mtk_mipi_tx_powew_on_signaw,
	.mipi_tx_disabwe_signaw = mtk_mipi_tx_powew_off_signaw,
};

const stwuct mtk_mipitx_data mt8173_mipitx_data = {
	.mppww_pwesewve = 0,
	.mipi_tx_cwk_ops = &mtk_mipi_tx_pww_ops,
	.mipi_tx_enabwe_signaw = mtk_mipi_tx_powew_on_signaw,
	.mipi_tx_disabwe_signaw = mtk_mipi_tx_powew_off_signaw,
};
