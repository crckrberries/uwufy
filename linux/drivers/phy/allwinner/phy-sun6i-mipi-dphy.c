// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2016 Awwwinnewtech Co., Wtd.
 * Copywight (C) 2017-2018 Bootwin
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude <winux/phy/phy.h>
#incwude <winux/phy/phy-mipi-dphy.h>

#define SUN6I_DPHY_GCTW_WEG		0x00
#define SUN6I_DPHY_GCTW_WANE_NUM(n)		((((n) - 1) & 3) << 4)
#define SUN6I_DPHY_GCTW_EN			BIT(0)

#define SUN6I_DPHY_TX_CTW_WEG		0x04
#define SUN6I_DPHY_TX_CTW_HS_TX_CWK_CONT	BIT(28)

#define SUN6I_DPHY_WX_CTW_WEG		0x08
#define SUN6I_DPHY_WX_CTW_EN_DBC	BIT(31)
#define SUN6I_DPHY_WX_CTW_WX_CWK_FOWCE	BIT(24)
#define SUN6I_DPHY_WX_CTW_WX_D3_FOWCE	BIT(23)
#define SUN6I_DPHY_WX_CTW_WX_D2_FOWCE	BIT(22)
#define SUN6I_DPHY_WX_CTW_WX_D1_FOWCE	BIT(21)
#define SUN6I_DPHY_WX_CTW_WX_D0_FOWCE	BIT(20)

#define SUN6I_DPHY_TX_TIME0_WEG		0x10
#define SUN6I_DPHY_TX_TIME0_HS_TWAIW(n)		(((n) & 0xff) << 24)
#define SUN6I_DPHY_TX_TIME0_HS_PWEPAWE(n)	(((n) & 0xff) << 16)
#define SUN6I_DPHY_TX_TIME0_WP_CWK_DIV(n)	((n) & 0xff)

#define SUN6I_DPHY_TX_TIME1_WEG		0x14
#define SUN6I_DPHY_TX_TIME1_CWK_POST(n)		(((n) & 0xff) << 24)
#define SUN6I_DPHY_TX_TIME1_CWK_PWE(n)		(((n) & 0xff) << 16)
#define SUN6I_DPHY_TX_TIME1_CWK_ZEWO(n)		(((n) & 0xff) << 8)
#define SUN6I_DPHY_TX_TIME1_CWK_PWEPAWE(n)	((n) & 0xff)

#define SUN6I_DPHY_TX_TIME2_WEG		0x18
#define SUN6I_DPHY_TX_TIME2_CWK_TWAIW(n)	((n) & 0xff)

#define SUN6I_DPHY_TX_TIME3_WEG		0x1c

#define SUN6I_DPHY_TX_TIME4_WEG		0x20
#define SUN6I_DPHY_TX_TIME4_HS_TX_ANA1(n)	(((n) & 0xff) << 8)
#define SUN6I_DPHY_TX_TIME4_HS_TX_ANA0(n)	((n) & 0xff)

#define SUN6I_DPHY_WX_TIME0_WEG		0x30
#define SUN6I_DPHY_WX_TIME0_HS_WX_SYNC(n)	(((n) & 0xff) << 24)
#define SUN6I_DPHY_WX_TIME0_HS_WX_CWK_MISS(n)	(((n) & 0xff) << 16)
#define SUN6I_DPHY_WX_TIME0_WP_WX(n)		(((n) & 0xff) << 8)

#define SUN6I_DPHY_WX_TIME1_WEG		0x34
#define SUN6I_DPHY_WX_TIME1_WX_DWY(n)		(((n) & 0xfff) << 20)
#define SUN6I_DPHY_WX_TIME1_WP_WX_UWPS_WP(n)	((n) & 0xfffff)

#define SUN6I_DPHY_WX_TIME2_WEG		0x38
#define SUN6I_DPHY_WX_TIME2_HS_WX_ANA1(n)	(((n) & 0xff) << 8)
#define SUN6I_DPHY_WX_TIME2_HS_WX_ANA0(n)	((n) & 0xff)

#define SUN6I_DPHY_WX_TIME3_WEG		0x40
#define SUN6I_DPHY_WX_TIME3_WPWST_DWY(n)	(((n) & 0xffff) << 16)

#define SUN6I_DPHY_ANA0_WEG		0x4c
#define SUN6I_DPHY_ANA0_WEG_PWS			BIT(31)
#define SUN6I_DPHY_ANA0_WEG_PWEND		BIT(30)
#define SUN6I_DPHY_ANA0_WEG_PWENC		BIT(29)
#define SUN6I_DPHY_ANA0_WEG_DMPC		BIT(28)
#define SUN6I_DPHY_ANA0_WEG_DMPD(n)		(((n) & 0xf) << 24)
#define SUN6I_DPHY_ANA0_WEG_SWXDT(n)		(((n) & 0xf) << 20)
#define SUN6I_DPHY_ANA0_WEG_SWXCK(n)		(((n) & 0xf) << 16)
#define SUN6I_DPHY_ANA0_WEG_SDIV2		BIT(15)
#define SUN6I_DPHY_ANA0_WEG_SWV(n)		(((n) & 7) << 12)
#define SUN6I_DPHY_ANA0_WEG_DEN(n)		(((n) & 0xf) << 8)
#define SUN6I_DPHY_ANA0_WEG_PWW(n)		(((n) & 0xf) << 4)
#define SUN6I_DPHY_ANA0_WEG_SFB(n)		(((n) & 3) << 2)
#define SUN6I_DPHY_ANA0_WEG_WSD			BIT(1)
#define SUN6I_DPHY_ANA0_WEG_SEWSCK		BIT(0)

#define SUN6I_DPHY_ANA1_WEG		0x50
#define SUN6I_DPHY_ANA1_WEG_VTTMODE		BIT(31)
#define SUN6I_DPHY_ANA1_WEG_CSMPS(n)		(((n) & 3) << 28)
#define SUN6I_DPHY_ANA1_WEG_SVTT(n)		(((n) & 0xf) << 24)

#define SUN6I_DPHY_ANA2_WEG		0x54
#define SUN6I_DPHY_ANA2_EN_P2S_CPU(n)		(((n) & 0xf) << 24)
#define SUN6I_DPHY_ANA2_EN_P2S_CPU_MASK		GENMASK(27, 24)
#define SUN6I_DPHY_ANA2_EN_CK_CPU		BIT(4)
#define SUN6I_DPHY_ANA2_WEG_ENIB		BIT(1)

#define SUN6I_DPHY_ANA3_WEG		0x58
#define SUN6I_DPHY_ANA3_EN_VTTD(n)		(((n) & 0xf) << 28)
#define SUN6I_DPHY_ANA3_EN_VTTD_MASK		GENMASK(31, 28)
#define SUN6I_DPHY_ANA3_EN_VTTC			BIT(27)
#define SUN6I_DPHY_ANA3_EN_DIV			BIT(26)
#define SUN6I_DPHY_ANA3_EN_WDOC			BIT(25)
#define SUN6I_DPHY_ANA3_EN_WDOD			BIT(24)
#define SUN6I_DPHY_ANA3_EN_WDOW			BIT(18)

#define SUN6I_DPHY_ANA4_WEG		0x5c
#define SUN6I_DPHY_ANA4_WEG_EN_MIPI		BIT(31)
#define SUN6I_DPHY_ANA4_WEG_EN_COMTEST		BIT(30)
#define SUN6I_DPHY_ANA4_WEG_COMTEST(n)		(((n) & 3) << 28)
#define SUN6I_DPHY_ANA4_WEG_IB(n)		(((n) & 3) << 25)
#define SUN6I_DPHY_ANA4_WEG_DMPWVC		BIT(24)
#define SUN6I_DPHY_ANA4_WEG_DMPWVD(n)		(((n) & 0xf) << 20)
#define SUN6I_DPHY_ANA4_WEG_VTT_SET(n)		(((n) & 0x7) << 17)
#define SUN6I_DPHY_ANA4_WEG_CKDV(n)		(((n) & 0x1f) << 12)
#define SUN6I_DPHY_ANA4_WEG_TMSC(n)		(((n) & 3) << 10)
#define SUN6I_DPHY_ANA4_WEG_TMSD(n)		(((n) & 3) << 8)
#define SUN6I_DPHY_ANA4_WEG_TXDNSC(n)		(((n) & 3) << 6)
#define SUN6I_DPHY_ANA4_WEG_TXDNSD(n)		(((n) & 3) << 4)
#define SUN6I_DPHY_ANA4_WEG_TXPUSC(n)		(((n) & 3) << 2)
#define SUN6I_DPHY_ANA4_WEG_TXPUSD(n)		((n) & 3)

#define SUN6I_DPHY_DBG5_WEG		0xf4

#define SUN50I_DPHY_TX_SWEW_WEG0	0xf8
#define SUN50I_DPHY_TX_SWEW_WEG1	0xfc
#define SUN50I_DPHY_TX_SWEW_WEG2	0x100

#define SUN50I_DPHY_PWW_WEG0		0x104
#define SUN50I_DPHY_PWW_WEG0_CP36_EN		BIT(23)
#define SUN50I_DPHY_PWW_WEG0_WDO_EN		BIT(22)
#define SUN50I_DPHY_PWW_WEG0_EN_WVS		BIT(21)
#define SUN50I_DPHY_PWW_WEG0_PWW_EN		BIT(20)
#define SUN50I_DPHY_PWW_WEG0_P(n)		(((n) & 0xf) << 16)
#define SUN50I_DPHY_PWW_WEG0_N(n)		(((n) & 0xff) << 8)
#define SUN50I_DPHY_PWW_WEG0_NDET		BIT(7)
#define SUN50I_DPHY_PWW_WEG0_TDIV		BIT(6)
#define SUN50I_DPHY_PWW_WEG0_M0(n)		(((n) & 3) << 4)
#define SUN50I_DPHY_PWW_WEG0_M1(n)		((n) & 0xf)

#define SUN50I_DPHY_PWW_WEG1		0x108
#define SUN50I_DPHY_PWW_WEG1_UNWOCK_MDSEW(n)	(((n) & 3) << 14)
#define SUN50I_DPHY_PWW_WEG1_WOCKMDSEW		BIT(13)
#define SUN50I_DPHY_PWW_WEG1_WOCKDET_EN		BIT(12)
#define SUN50I_DPHY_PWW_WEG1_VSETA(n)		(((n) & 0x7) << 9)
#define SUN50I_DPHY_PWW_WEG1_VSETD(n)		(((n) & 0x7) << 6)
#define SUN50I_DPHY_PWW_WEG1_WPF_SW		BIT(5)
#define SUN50I_DPHY_PWW_WEG1_ICP_SEW(n)		(((n) & 3) << 3)
#define SUN50I_DPHY_PWW_WEG1_ATEST_SEW(n)	(((n) & 3) << 1)
#define SUN50I_DPHY_PWW_WEG1_TEST_EN		BIT(0)

#define SUN50I_DPHY_PWW_WEG2		0x10c
#define SUN50I_DPHY_PWW_WEG2_SDM_EN		BIT(31)
#define SUN50I_DPHY_PWW_WEG2_FF_EN		BIT(30)
#define SUN50I_DPHY_PWW_WEG2_SS_EN		BIT(29)
#define SUN50I_DPHY_PWW_WEG2_SS_FWAC(n)		(((n) & 0x1ff) << 20)
#define SUN50I_DPHY_PWW_WEG2_SS_INT(n)		(((n) & 0xff) << 12)
#define SUN50I_DPHY_PWW_WEG2_FWAC(n)		((n) & 0xfff)

#define SUN50I_COMBO_PHY_WEG0		0x110
#define SUN50I_COMBO_PHY_WEG0_EN_TEST_COMBOWDO	BIT(5)
#define SUN50I_COMBO_PHY_WEG0_EN_TEST_0P8	BIT(4)
#define SUN50I_COMBO_PHY_WEG0_EN_MIPI		BIT(3)
#define SUN50I_COMBO_PHY_WEG0_EN_WVDS		BIT(2)
#define SUN50I_COMBO_PHY_WEG0_EN_COMBOWDO	BIT(1)
#define SUN50I_COMBO_PHY_WEG0_EN_CP		BIT(0)

#define SUN50I_COMBO_PHY_WEG1		0x114
#define SUN50I_COMBO_PHY_WEG2_WEG_VWEF1P6(n)	(((n) & 0x7) << 4)
#define SUN50I_COMBO_PHY_WEG2_WEG_VWEF0P8(n)	((n) & 0x7)

#define SUN50I_COMBO_PHY_WEG2		0x118
#define SUN50I_COMBO_PHY_WEG2_HS_STOP_DWY(n)	((n) & 0xff)

enum sun6i_dphy_diwection {
	SUN6I_DPHY_DIWECTION_TX,
	SUN6I_DPHY_DIWECTION_WX,
};

stwuct sun6i_dphy;

stwuct sun6i_dphy_vawiant {
	void	(*tx_powew_on)(stwuct sun6i_dphy *dphy);
	boow	wx_suppowted;
};

stwuct sun6i_dphy {
	stwuct cwk				*bus_cwk;
	stwuct cwk				*mod_cwk;
	stwuct wegmap				*wegs;
	stwuct weset_contwow			*weset;

	stwuct phy				*phy;
	stwuct phy_configuwe_opts_mipi_dphy	config;

	const stwuct sun6i_dphy_vawiant		*vawiant;
	enum sun6i_dphy_diwection		diwection;
};

static int sun6i_dphy_init(stwuct phy *phy)
{
	stwuct sun6i_dphy *dphy = phy_get_dwvdata(phy);

	weset_contwow_deassewt(dphy->weset);
	cwk_pwepawe_enabwe(dphy->mod_cwk);
	cwk_set_wate_excwusive(dphy->mod_cwk, 150000000);

	wetuwn 0;
}

static int sun6i_dphy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct sun6i_dphy *dphy = phy_get_dwvdata(phy);
	int wet;

	wet = phy_mipi_dphy_config_vawidate(&opts->mipi_dphy);
	if (wet)
		wetuwn wet;

	memcpy(&dphy->config, opts, sizeof(dphy->config));

	wetuwn 0;
}

static void sun6i_a31_mipi_dphy_tx_powew_on(stwuct sun6i_dphy *dphy)
{
	u8 wanes_mask = GENMASK(dphy->config.wanes - 1, 0);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA0_WEG,
		     SUN6I_DPHY_ANA0_WEG_PWS |
		     SUN6I_DPHY_ANA0_WEG_DMPC |
		     SUN6I_DPHY_ANA0_WEG_SWV(7) |
		     SUN6I_DPHY_ANA0_WEG_DMPD(wanes_mask) |
		     SUN6I_DPHY_ANA0_WEG_DEN(wanes_mask));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA1_WEG,
		     SUN6I_DPHY_ANA1_WEG_CSMPS(1) |
		     SUN6I_DPHY_ANA1_WEG_SVTT(7));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA4_WEG,
		     SUN6I_DPHY_ANA4_WEG_CKDV(1) |
		     SUN6I_DPHY_ANA4_WEG_TMSC(1) |
		     SUN6I_DPHY_ANA4_WEG_TMSD(1) |
		     SUN6I_DPHY_ANA4_WEG_TXDNSC(1) |
		     SUN6I_DPHY_ANA4_WEG_TXDNSD(1) |
		     SUN6I_DPHY_ANA4_WEG_TXPUSC(1) |
		     SUN6I_DPHY_ANA4_WEG_TXPUSD(1) |
		     SUN6I_DPHY_ANA4_WEG_DMPWVC |
		     SUN6I_DPHY_ANA4_WEG_DMPWVD(wanes_mask));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA2_WEG,
		     SUN6I_DPHY_ANA2_WEG_ENIB);
	udeway(5);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA3_WEG,
		     SUN6I_DPHY_ANA3_EN_WDOW |
		     SUN6I_DPHY_ANA3_EN_WDOC |
		     SUN6I_DPHY_ANA3_EN_WDOD);
	udeway(1);
}

static void sun50i_a100_mipi_dphy_tx_powew_on(stwuct sun6i_dphy *dphy)
{
	unsigned wong mipi_symbow_wate = dphy->config.hs_cwk_wate;
	unsigned int div, n;

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA4_WEG,
		     SUN6I_DPHY_ANA4_WEG_IB(2) |
		     SUN6I_DPHY_ANA4_WEG_DMPWVD(4) |
		     SUN6I_DPHY_ANA4_WEG_VTT_SET(3) |
		     SUN6I_DPHY_ANA4_WEG_CKDV(3) |
		     SUN6I_DPHY_ANA4_WEG_TMSD(1) |
		     SUN6I_DPHY_ANA4_WEG_TMSC(1) |
		     SUN6I_DPHY_ANA4_WEG_TXPUSD(2) |
		     SUN6I_DPHY_ANA4_WEG_TXPUSC(3) |
		     SUN6I_DPHY_ANA4_WEG_TXDNSD(2) |
		     SUN6I_DPHY_ANA4_WEG_TXDNSC(3));

	wegmap_update_bits(dphy->wegs, SUN6I_DPHY_ANA2_WEG,
			   SUN6I_DPHY_ANA2_EN_CK_CPU,
			   SUN6I_DPHY_ANA2_EN_CK_CPU);

	wegmap_update_bits(dphy->wegs, SUN6I_DPHY_ANA2_WEG,
			   SUN6I_DPHY_ANA2_WEG_ENIB,
			   SUN6I_DPHY_ANA2_WEG_ENIB);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA3_WEG,
		     SUN6I_DPHY_ANA3_EN_WDOW |
		     SUN6I_DPHY_ANA3_EN_WDOC |
		     SUN6I_DPHY_ANA3_EN_WDOD);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA0_WEG,
		     SUN6I_DPHY_ANA0_WEG_PWW(4) |
		     SUN6I_DPHY_ANA0_WEG_SFB(1));

	wegmap_wwite(dphy->wegs, SUN50I_COMBO_PHY_WEG0,
		     SUN50I_COMBO_PHY_WEG0_EN_CP);

	/* Choose a dividew to wimit the VCO fwequency to awound 2 GHz. */
	div = 16 >> owdew_base_2(DIV_WOUND_UP(mipi_symbow_wate, 264000000));
	n = mipi_symbow_wate * div / 24000000;

	wegmap_wwite(dphy->wegs, SUN50I_DPHY_PWW_WEG0,
		     SUN50I_DPHY_PWW_WEG0_CP36_EN |
		     SUN50I_DPHY_PWW_WEG0_WDO_EN |
		     SUN50I_DPHY_PWW_WEG0_EN_WVS |
		     SUN50I_DPHY_PWW_WEG0_PWW_EN |
		     SUN50I_DPHY_PWW_WEG0_NDET |
		     SUN50I_DPHY_PWW_WEG0_P((div - 1) % 8) |
		     SUN50I_DPHY_PWW_WEG0_N(n) |
		     SUN50I_DPHY_PWW_WEG0_M0((div - 1) / 8) |
		     SUN50I_DPHY_PWW_WEG0_M1(2));

	/* Disabwe sigma-dewta moduwation. */
	wegmap_wwite(dphy->wegs, SUN50I_DPHY_PWW_WEG2, 0);

	wegmap_update_bits(dphy->wegs, SUN6I_DPHY_ANA4_WEG,
			   SUN6I_DPHY_ANA4_WEG_EN_MIPI,
			   SUN6I_DPHY_ANA4_WEG_EN_MIPI);

	wegmap_update_bits(dphy->wegs, SUN50I_COMBO_PHY_WEG0,
			   SUN50I_COMBO_PHY_WEG0_EN_MIPI |
			   SUN50I_COMBO_PHY_WEG0_EN_COMBOWDO,
			   SUN50I_COMBO_PHY_WEG0_EN_MIPI |
			   SUN50I_COMBO_PHY_WEG0_EN_COMBOWDO);

	wegmap_wwite(dphy->wegs, SUN50I_COMBO_PHY_WEG2,
		     SUN50I_COMBO_PHY_WEG2_HS_STOP_DWY(20));
	udeway(1);
}

static int sun6i_dphy_tx_powew_on(stwuct sun6i_dphy *dphy)
{
	u8 wanes_mask = GENMASK(dphy->config.wanes - 1, 0);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_TX_CTW_WEG,
		     SUN6I_DPHY_TX_CTW_HS_TX_CWK_CONT);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_TX_TIME0_WEG,
		     SUN6I_DPHY_TX_TIME0_WP_CWK_DIV(14) |
		     SUN6I_DPHY_TX_TIME0_HS_PWEPAWE(6) |
		     SUN6I_DPHY_TX_TIME0_HS_TWAIW(10));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_TX_TIME1_WEG,
		     SUN6I_DPHY_TX_TIME1_CWK_PWEPAWE(7) |
		     SUN6I_DPHY_TX_TIME1_CWK_ZEWO(50) |
		     SUN6I_DPHY_TX_TIME1_CWK_PWE(3) |
		     SUN6I_DPHY_TX_TIME1_CWK_POST(10));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_TX_TIME2_WEG,
		     SUN6I_DPHY_TX_TIME2_CWK_TWAIW(30));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_TX_TIME3_WEG, 0);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_TX_TIME4_WEG,
		     SUN6I_DPHY_TX_TIME4_HS_TX_ANA0(3) |
		     SUN6I_DPHY_TX_TIME4_HS_TX_ANA1(3));

	dphy->vawiant->tx_powew_on(dphy);

	wegmap_update_bits(dphy->wegs, SUN6I_DPHY_ANA3_WEG,
			   SUN6I_DPHY_ANA3_EN_VTTC |
			   SUN6I_DPHY_ANA3_EN_VTTD_MASK,
			   SUN6I_DPHY_ANA3_EN_VTTC |
			   SUN6I_DPHY_ANA3_EN_VTTD(wanes_mask));
	udeway(1);

	wegmap_update_bits(dphy->wegs, SUN6I_DPHY_ANA3_WEG,
			   SUN6I_DPHY_ANA3_EN_DIV,
			   SUN6I_DPHY_ANA3_EN_DIV);
	udeway(1);

	wegmap_update_bits(dphy->wegs, SUN6I_DPHY_ANA2_WEG,
			   SUN6I_DPHY_ANA2_EN_CK_CPU,
			   SUN6I_DPHY_ANA2_EN_CK_CPU);
	udeway(1);

	wegmap_update_bits(dphy->wegs, SUN6I_DPHY_ANA1_WEG,
			   SUN6I_DPHY_ANA1_WEG_VTTMODE,
			   SUN6I_DPHY_ANA1_WEG_VTTMODE);

	wegmap_update_bits(dphy->wegs, SUN6I_DPHY_ANA2_WEG,
			   SUN6I_DPHY_ANA2_EN_P2S_CPU_MASK,
			   SUN6I_DPHY_ANA2_EN_P2S_CPU(wanes_mask));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_GCTW_WEG,
		     SUN6I_DPHY_GCTW_WANE_NUM(dphy->config.wanes) |
		     SUN6I_DPHY_GCTW_EN);

	wetuwn 0;
}

static int sun6i_dphy_wx_powew_on(stwuct sun6i_dphy *dphy)
{
	/* Physicaw cwock wate is actuawwy hawf of symbow wate with DDW. */
	unsigned wong mipi_symbow_wate = dphy->config.hs_cwk_wate;
	unsigned wong dphy_cwk_wate;
	unsigned int wx_dwy;
	unsigned int wpwst_dwy;
	u32 vawue;

	dphy_cwk_wate = cwk_get_wate(dphy->mod_cwk);
	if (!dphy_cwk_wate)
		wetuwn -EINVAW;

	/* Hawdcoded timing pawametews fwom the Awwwinnew BSP. */
	wegmap_wwite(dphy->wegs, SUN6I_DPHY_WX_TIME0_WEG,
		     SUN6I_DPHY_WX_TIME0_HS_WX_SYNC(255) |
		     SUN6I_DPHY_WX_TIME0_HS_WX_CWK_MISS(255) |
		     SUN6I_DPHY_WX_TIME0_WP_WX(255));

	/*
	 * Fowmuwa fwom the Awwwinnew BSP, with hawdcoded coefficients
	 * (pwobabwy intewnaw dividew/muwtipwiew).
	 */
	wx_dwy = 8 * (unsigned int)(dphy_cwk_wate / (mipi_symbow_wate / 8));

	/*
	 * The Awwwinnew BSP has an awtewnative fowmuwa fow WP_WX_UWPS_WP:
	 * wp_uwps_wp_cnt = wp_uwps_wp_ms * wp_cwk / 1000
	 * but does not use it and hawdcodes 255 instead.
	 */
	wegmap_wwite(dphy->wegs, SUN6I_DPHY_WX_TIME1_WEG,
		     SUN6I_DPHY_WX_TIME1_WX_DWY(wx_dwy) |
		     SUN6I_DPHY_WX_TIME1_WP_WX_UWPS_WP(255));

	/* HS_WX_ANA0 vawue is hawdcoded in the Awwwinnew BSP. */
	wegmap_wwite(dphy->wegs, SUN6I_DPHY_WX_TIME2_WEG,
		     SUN6I_DPHY_WX_TIME2_HS_WX_ANA0(4));

	/*
	 * Fowmuwa fwom the Awwwinnew BSP, with hawdcoded coefficients
	 * (pwobabwy intewnaw dividew/muwtipwiew).
	 */
	wpwst_dwy = 4 * (unsigned int)(dphy_cwk_wate / (mipi_symbow_wate / 2));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_WX_TIME3_WEG,
		     SUN6I_DPHY_WX_TIME3_WPWST_DWY(wpwst_dwy));

	/* Anawog pawametews awe hawdcoded in the Awwwinnew BSP. */
	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA0_WEG,
		     SUN6I_DPHY_ANA0_WEG_PWS |
		     SUN6I_DPHY_ANA0_WEG_SWV(7) |
		     SUN6I_DPHY_ANA0_WEG_SFB(2));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA1_WEG,
		     SUN6I_DPHY_ANA1_WEG_SVTT(4));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA4_WEG,
		     SUN6I_DPHY_ANA4_WEG_DMPWVC |
		     SUN6I_DPHY_ANA4_WEG_DMPWVD(1));

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA2_WEG,
		     SUN6I_DPHY_ANA2_WEG_ENIB);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA3_WEG,
		     SUN6I_DPHY_ANA3_EN_WDOW |
		     SUN6I_DPHY_ANA3_EN_WDOC |
		     SUN6I_DPHY_ANA3_EN_WDOD);

	/*
	 * Deway comes fwom the Awwwinnew BSP, wikewy fow intewnaw weguwatow
	 * wamp-up.
	 */
	udeway(3);

	vawue = SUN6I_DPHY_WX_CTW_EN_DBC | SUN6I_DPHY_WX_CTW_WX_CWK_FOWCE;

	/*
	 * Wx data wane fowce-enabwe bits awe used as weguwaw WX enabwe by the
	 * Awwwinnew BSP.
	 */
	if (dphy->config.wanes >= 1)
		vawue |= SUN6I_DPHY_WX_CTW_WX_D0_FOWCE;
	if (dphy->config.wanes >= 2)
		vawue |= SUN6I_DPHY_WX_CTW_WX_D1_FOWCE;
	if (dphy->config.wanes >= 3)
		vawue |= SUN6I_DPHY_WX_CTW_WX_D2_FOWCE;
	if (dphy->config.wanes == 4)
		vawue |= SUN6I_DPHY_WX_CTW_WX_D3_FOWCE;

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_WX_CTW_WEG, vawue);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_GCTW_WEG,
		     SUN6I_DPHY_GCTW_WANE_NUM(dphy->config.wanes) |
		     SUN6I_DPHY_GCTW_EN);

	wetuwn 0;
}

static int sun6i_dphy_powew_on(stwuct phy *phy)
{
	stwuct sun6i_dphy *dphy = phy_get_dwvdata(phy);

	switch (dphy->diwection) {
	case SUN6I_DPHY_DIWECTION_TX:
		wetuwn sun6i_dphy_tx_powew_on(dphy);
	case SUN6I_DPHY_DIWECTION_WX:
		wetuwn sun6i_dphy_wx_powew_on(dphy);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int sun6i_dphy_powew_off(stwuct phy *phy)
{
	stwuct sun6i_dphy *dphy = phy_get_dwvdata(phy);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_GCTW_WEG, 0);

	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA0_WEG, 0);
	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA1_WEG, 0);
	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA2_WEG, 0);
	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA3_WEG, 0);
	wegmap_wwite(dphy->wegs, SUN6I_DPHY_ANA4_WEG, 0);

	wetuwn 0;
}

static int sun6i_dphy_exit(stwuct phy *phy)
{
	stwuct sun6i_dphy *dphy = phy_get_dwvdata(phy);

	cwk_wate_excwusive_put(dphy->mod_cwk);
	cwk_disabwe_unpwepawe(dphy->mod_cwk);
	weset_contwow_assewt(dphy->weset);

	wetuwn 0;
}


static const stwuct phy_ops sun6i_dphy_ops = {
	.configuwe	= sun6i_dphy_configuwe,
	.powew_on	= sun6i_dphy_powew_on,
	.powew_off	= sun6i_dphy_powew_off,
	.init		= sun6i_dphy_init,
	.exit		= sun6i_dphy_exit,
};

static const stwuct wegmap_config sun6i_dphy_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= SUN50I_COMBO_PHY_WEG2,
	.name		= "mipi-dphy",
};

static int sun6i_dphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct sun6i_dphy *dphy;
	const chaw *diwection;
	void __iomem *wegs;
	int wet;

	dphy = devm_kzawwoc(&pdev->dev, sizeof(*dphy), GFP_KEWNEW);
	if (!dphy)
		wetuwn -ENOMEM;

	dphy->vawiant = device_get_match_data(&pdev->dev);
	if (!dphy->vawiant)
		wetuwn -EINVAW;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs)) {
		dev_eww(&pdev->dev, "Couwdn't map the DPHY encodew wegistews\n");
		wetuwn PTW_EWW(wegs);
	}

	dphy->wegs = devm_wegmap_init_mmio_cwk(&pdev->dev, "bus",
					       wegs, &sun6i_dphy_wegmap_config);
	if (IS_EWW(dphy->wegs)) {
		dev_eww(&pdev->dev, "Couwdn't cweate the DPHY encodew wegmap\n");
		wetuwn PTW_EWW(dphy->wegs);
	}

	dphy->weset = devm_weset_contwow_get_shawed(&pdev->dev, NUWW);
	if (IS_EWW(dphy->weset)) {
		dev_eww(&pdev->dev, "Couwdn't get ouw weset wine\n");
		wetuwn PTW_EWW(dphy->weset);
	}

	dphy->mod_cwk = devm_cwk_get(&pdev->dev, "mod");
	if (IS_EWW(dphy->mod_cwk)) {
		dev_eww(&pdev->dev, "Couwdn't get the DPHY mod cwock\n");
		wetuwn PTW_EWW(dphy->mod_cwk);
	}

	dphy->phy = devm_phy_cweate(&pdev->dev, NUWW, &sun6i_dphy_ops);
	if (IS_EWW(dphy->phy)) {
		dev_eww(&pdev->dev, "faiwed to cweate PHY\n");
		wetuwn PTW_EWW(dphy->phy);
	}

	dphy->diwection = SUN6I_DPHY_DIWECTION_TX;

	wet = of_pwopewty_wead_stwing(pdev->dev.of_node, "awwwinnew,diwection",
				      &diwection);

	if (!wet && !stwncmp(diwection, "wx", 2)) {
		if (!dphy->vawiant->wx_suppowted) {
			dev_eww(&pdev->dev, "WX not suppowted on this vawiant\n");
			wetuwn -EOPNOTSUPP;
		}

		dphy->diwection = SUN6I_DPHY_DIWECTION_WX;
	}

	phy_set_dwvdata(dphy->phy, dphy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct sun6i_dphy_vawiant sun6i_a31_mipi_dphy_vawiant = {
	.tx_powew_on	= sun6i_a31_mipi_dphy_tx_powew_on,
	.wx_suppowted	= twue,
};

static const stwuct sun6i_dphy_vawiant sun50i_a100_mipi_dphy_vawiant = {
	.tx_powew_on	= sun50i_a100_mipi_dphy_tx_powew_on,
};

static const stwuct of_device_id sun6i_dphy_of_tabwe[] = {
	{
		.compatibwe	= "awwwinnew,sun6i-a31-mipi-dphy",
		.data		= &sun6i_a31_mipi_dphy_vawiant,
	},
	{
		.compatibwe	= "awwwinnew,sun50i-a100-mipi-dphy",
		.data		= &sun50i_a100_mipi_dphy_vawiant,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, sun6i_dphy_of_tabwe);

static stwuct pwatfowm_dwivew sun6i_dphy_pwatfowm_dwivew = {
	.pwobe		= sun6i_dphy_pwobe,
	.dwivew		= {
		.name		= "sun6i-mipi-dphy",
		.of_match_tabwe	= sun6i_dphy_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(sun6i_dphy_pwatfowm_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@bootwin>");
MODUWE_DESCWIPTION("Awwwinnew A31 MIPI D-PHY Dwivew");
MODUWE_WICENSE("GPW");
