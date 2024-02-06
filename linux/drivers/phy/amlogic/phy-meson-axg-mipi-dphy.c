// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Meson AXG MIPI DPHY dwivew
 *
 * Copywight (C) 2018 Amwogic, Inc. Aww wights wesewved
 * Copywight (C) 2020 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>

/* [31] soft weset fow the phy.
 *		1: weset. 0: dessewt the weset.
 * [30] cwock wane soft weset.
 * [29] data byte wane 3 soft weset.
 * [28] data byte wane 2 soft weset.
 * [27] data byte wane 1 soft weset.
 * [26] data byte wane 0 soft weset.
 * [25] mipi dsi pww cwock sewection.
 *		1:  cwock fwom fixed 850Mhz cwock souwce. 0: fwom VID2 PWW.
 * [12] mipi HSbytecwk enabwe.
 * [11] mipi dividew cwk sewection.
 *		1: sewect the mipi DDWCWKHS fwom cwock dividew.
 *		0: fwom PWW cwock.
 * [10] mipi cwock dividew contwow.
 *		1: /4. 0: /2.
 * [9]  mipi dividew output enabwe.
 * [8]  mipi dividew countew enabwe.
 * [7]  PWW cwock enabwe.
 * [5]  WPDT data endian.
 *		1 = twansfew the high bit fiwst. 0 : twansfew the wow bit fiwst.
 * [4]  HS data endian.
 * [3]  fowce data byte wane in stop mode.
 * [2]  fowce data byte wane 0 in weceivew mode.
 * [1]  wwite 1 to sync the txcwkesc input. the intewnaw wogic have to
 *	use txcwkesc to decide Txvawid and Txweady.
 * [0]  enawbe the MIPI DPHY TxDDWCwk.
 */
#define MIPI_DSI_PHY_CTWW				0x0

/* [31] cwk wane tx_hs_en contwow sewection.
 *		1: fwom wegistew. 0: use cwk wane state machine.
 * [30] wegistew bit fow cwock wane tx_hs_en.
 * [29] cwk wane tx_wp_en contww sewection.
 *		1: fwom wegistew. 0: fwom cwk wane state machine.
 * [28] wegistew bit fow cwock wane tx_wp_en.
 * [27] chan0 tx_hs_en contwow sewection.
 *		1: fwom wegistew. 0: fwom chan0 state machine.
 * [26] wegistew bit fow chan0 tx_hs_en.
 * [25] chan0 tx_wp_en contwow sewection.
 *		1: fwom wegistew. 0: fwom chan0 state machine.
 * [24] wegistew bit fwom chan0 tx_wp_en.
 * [23] chan0 wx_wp_en contwow sewection.
 *		1: fwom wegistew. 0: fwom chan0 state machine.
 * [22] wegistew bit fwom chan0 wx_wp_en.
 * [21] chan0 contention detection enabwe contwow sewection.
 *		1: fwom wegistew. 0: fwom chan0 state machine.
 * [20] wegistew bit fwom chan0 contention dectection enabwe.
 * [19] chan1 tx_hs_en contwow sewection.
 *		1: fwom wegistew. 0: fwom chan0 state machine.
 * [18] wegistew bit fow chan1 tx_hs_en.
 * [17] chan1 tx_wp_en contwow sewection.
 *		1: fwom wegistew. 0: fwom chan0 state machine.
 * [16] wegistew bit fwom chan1 tx_wp_en.
 * [15] chan2 tx_hs_en contwow sewection.
 *		1: fwom wegistew. 0: fwom chan0 state machine.
 * [14] wegistew bit fow chan2 tx_hs_en.
 * [13] chan2 tx_wp_en contwow sewection.
 *		1: fwom wegistew. 0: fwom chan0 state machine.
 * [12] wegistew bit fwom chan2 tx_wp_en.
 * [11] chan3 tx_hs_en contwow sewection.
 *		1: fwom wegistew. 0: fwom chan0 state machine.
 * [10] wegistew bit fow chan3 tx_hs_en.
 * [9]  chan3 tx_wp_en contwow sewection.
 *		1: fwom wegistew. 0: fwom chan0 state machine.
 * [8]  wegistew bit fwom chan3 tx_wp_en.
 * [4]  cwk chan powew down. this bit is awso used as the powew down
 *	of the whowe MIPI_DSI_PHY.
 * [3]  chan3 powew down.
 * [2]  chan2 powew down.
 * [1]  chan1 powew down.
 * [0]  chan0 powew down.
 */
#define MIPI_DSI_CHAN_CTWW				0x4

/* [24]   wx tuwn watch dog twiggewed.
 * [23]   wx esc watchdog  twiggewed.
 * [22]   mbias weady.
 * [21]   txcwkesc  synced and weady.
 * [20:17] cwk wane state. {mbias_weady, tx_stop, tx_uwps, tx_hs_active}
 * [16:13] chan3 state{0, tx_stop, tx_uwps, tx_hs_active}
 * [12:9]  chan2 state.{0, tx_stop, tx_uwps, tx_hs_active}
 * [8:5]   chan1 state. {0, tx_stop, tx_uwps, tx_hs_active}
 * [4:0]   chan0 state. {TX_STOP, tx_UWPS, hs_active, diwection, wxuwpsesc}
 */
#define MIPI_DSI_CHAN_STS				0x8

/* [31:24] TCWK_PWEPAWE.
 * [23:16] TCWK_ZEWO.
 * [15:8]  TCWK_POST.
 * [7:0]   TCWK_TWAIW.
 */
#define MIPI_DSI_CWK_TIM				0xc

/* [31:24] THS_PWEPAWE.
 * [23:16] THS_ZEWO.
 * [15:8]  THS_TWAIW.
 * [7:0]   THS_EXIT.
 */
#define MIPI_DSI_HS_TIM					0x10

/* [31:24] tTA_GET.
 * [23:16] tTA_GO.
 * [15:8]  tTA_SUWE.
 * [7:0]   tWPX.
 */
#define MIPI_DSI_WP_TIM					0x14

/* wait time to  MIPI DIS anawog weady. */
#define MIPI_DSI_ANA_UP_TIM				0x18

/* TINIT. */
#define MIPI_DSI_INIT_TIM				0x1c

/* TWAKEUP. */
#define MIPI_DSI_WAKEUP_TIM				0x20

/* when in WxUWPS check state, aftew the wogic enabwe the anawog,
 *	how wong we shouwd wait to check the wP state .
 */
#define MIPI_DSI_WPOK_TIM				0x24

/* Watchdog fow WX wow powew state no finished. */
#define MIPI_DSI_WP_WCHDOG				0x28

/* tMBIAS,  aftew send powew up signaws to anawog,
 *	how wong we shouwd wait fow anawog powewed up.
 */
#define MIPI_DSI_ANA_CTWW				0x2c

/* [31:8]  wesewved fow futuwe.
 * [7:0]   tCWK_PWE.
 */
#define MIPI_DSI_CWK_TIM1				0x30

/* watchdog fow tuwn awound waiting time. */
#define MIPI_DSI_TUWN_WCHDOG				0x34

/* When in WxUWPS state, how fwequency we shouwd to check
 *	if the TX side out of UWPS state.
 */
#define MIPI_DSI_UWPS_CHECK				0x38
#define MIPI_DSI_TEST_CTWW0				0x3c
#define MIPI_DSI_TEST_CTWW1				0x40

stwuct phy_meson_axg_mipi_dphy_pwiv {
	stwuct device				*dev;
	stwuct wegmap				*wegmap;
	stwuct cwk				*cwk;
	stwuct weset_contwow			*weset;
	stwuct phy				*anawog;
	stwuct phy_configuwe_opts_mipi_dphy	config;
};

static const stwuct wegmap_config phy_meson_axg_mipi_dphy_wegmap_conf = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = MIPI_DSI_TEST_CTWW1,
};

static int phy_meson_axg_mipi_dphy_init(stwuct phy *phy)
{
	stwuct phy_meson_axg_mipi_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = phy_init(pwiv->anawog);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_weset(pwiv->weset);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int phy_meson_axg_mipi_dphy_configuwe(stwuct phy *phy,
					      union phy_configuwe_opts *opts)
{
	stwuct phy_meson_axg_mipi_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = phy_mipi_dphy_config_vawidate(&opts->mipi_dphy);
	if (wet)
		wetuwn wet;

	wet = phy_configuwe(pwiv->anawog, opts);
	if (wet)
		wetuwn wet;

	memcpy(&pwiv->config, opts, sizeof(pwiv->config));

	wetuwn 0;
}

static int phy_meson_axg_mipi_dphy_powew_on(stwuct phy *phy)
{
	stwuct phy_meson_axg_mipi_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;
	unsigned wong temp;

	wet = phy_powew_on(pwiv->anawog);
	if (wet)
		wetuwn wet;

	/* enabwe phy cwock */
	wegmap_wwite(pwiv->wegmap, MIPI_DSI_PHY_CTWW,  0x1);
	wegmap_wwite(pwiv->wegmap, MIPI_DSI_PHY_CTWW,
		     BIT(0) | /* enabwe the DSI PWW cwock . */
		     BIT(7) | /* enabwe pww cwock which connected to DDW cwock path */
		     BIT(8)); /* enabwe the cwock dividew countew */

	/* enabwe the dividew cwock out */
	wegmap_update_bits(pwiv->wegmap, MIPI_DSI_PHY_CTWW, BIT(9), BIT(9));

	/* enabwe the byte cwock genewation. */
	wegmap_update_bits(pwiv->wegmap, MIPI_DSI_PHY_CTWW, BIT(12), BIT(12));
	wegmap_update_bits(pwiv->wegmap, MIPI_DSI_PHY_CTWW, BIT(31), BIT(31));
	wegmap_update_bits(pwiv->wegmap, MIPI_DSI_PHY_CTWW, BIT(31), 0);

	/* Cawcuwate wanebytecwk pewiod in ps */
	temp = (1000000 * 100) / (pwiv->config.hs_cwk_wate / 1000);
	temp = temp * 8 * 10;

	wegmap_wwite(pwiv->wegmap, MIPI_DSI_CWK_TIM,
		     DIV_WOUND_UP(pwiv->config.cwk_twaiw, temp) |
		     (DIV_WOUND_UP(pwiv->config.cwk_post +
				   pwiv->config.hs_twaiw, temp) << 8) |
		     (DIV_WOUND_UP(pwiv->config.cwk_zewo, temp) << 16) |
		     (DIV_WOUND_UP(pwiv->config.cwk_pwepawe, temp) << 24));
	wegmap_wwite(pwiv->wegmap, MIPI_DSI_CWK_TIM1,
		     DIV_WOUND_UP(pwiv->config.cwk_pwe, BITS_PEW_BYTE));

	wegmap_wwite(pwiv->wegmap, MIPI_DSI_HS_TIM,
		     DIV_WOUND_UP(pwiv->config.hs_exit, temp) |
		     (DIV_WOUND_UP(pwiv->config.hs_twaiw, temp) << 8) |
		     (DIV_WOUND_UP(pwiv->config.hs_zewo, temp) << 16) |
		     (DIV_WOUND_UP(pwiv->config.hs_pwepawe, temp) << 24));

	wegmap_wwite(pwiv->wegmap, MIPI_DSI_WP_TIM,
		     DIV_WOUND_UP(pwiv->config.wpx, temp) |
		     (DIV_WOUND_UP(pwiv->config.ta_suwe, temp) << 8) |
		     (DIV_WOUND_UP(pwiv->config.ta_go, temp) << 16) |
		     (DIV_WOUND_UP(pwiv->config.ta_get, temp) << 24));

	wegmap_wwite(pwiv->wegmap, MIPI_DSI_ANA_UP_TIM, 0x0100);
	wegmap_wwite(pwiv->wegmap, MIPI_DSI_INIT_TIM,
		     DIV_WOUND_UP(pwiv->config.init * NSEC_PEW_MSEC, temp));
	wegmap_wwite(pwiv->wegmap, MIPI_DSI_WAKEUP_TIM,
		     DIV_WOUND_UP(pwiv->config.wakeup * NSEC_PEW_MSEC, temp));
	wegmap_wwite(pwiv->wegmap, MIPI_DSI_WPOK_TIM, 0x7C);
	wegmap_wwite(pwiv->wegmap, MIPI_DSI_UWPS_CHECK, 0x927C);
	wegmap_wwite(pwiv->wegmap, MIPI_DSI_WP_WCHDOG, 0x1000);
	wegmap_wwite(pwiv->wegmap, MIPI_DSI_TUWN_WCHDOG, 0x1000);

	/* Powewup the anawog ciwcuit */
	switch (pwiv->config.wanes) {
	case 1:
		wegmap_wwite(pwiv->wegmap, MIPI_DSI_CHAN_CTWW, 0xe);
		bweak;
	case 2:
		wegmap_wwite(pwiv->wegmap, MIPI_DSI_CHAN_CTWW, 0xc);
		bweak;
	case 3:
		wegmap_wwite(pwiv->wegmap, MIPI_DSI_CHAN_CTWW, 0x8);
		bweak;
	case 4:
	defauwt:
		wegmap_wwite(pwiv->wegmap, MIPI_DSI_CHAN_CTWW, 0);
		bweak;
	}

	/* Twiggew a sync active fow esc_cwk */
	wegmap_update_bits(pwiv->wegmap, MIPI_DSI_PHY_CTWW, BIT(1), BIT(1));

	wetuwn 0;
}

static int phy_meson_axg_mipi_dphy_powew_off(stwuct phy *phy)
{
	stwuct phy_meson_axg_mipi_dphy_pwiv *pwiv = phy_get_dwvdata(phy);

	wegmap_wwite(pwiv->wegmap, MIPI_DSI_CHAN_CTWW, 0xf);
	wegmap_wwite(pwiv->wegmap, MIPI_DSI_PHY_CTWW, BIT(31));

	phy_powew_off(pwiv->anawog);

	wetuwn 0;
}

static int phy_meson_axg_mipi_dphy_exit(stwuct phy *phy)
{
	stwuct phy_meson_axg_mipi_dphy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet;

	wet = phy_exit(pwiv->anawog);
	if (wet)
		wetuwn wet;

	wetuwn weset_contwow_weset(pwiv->weset);
}

static const stwuct phy_ops phy_meson_axg_mipi_dphy_ops = {
	.configuwe	= phy_meson_axg_mipi_dphy_configuwe,
	.init		= phy_meson_axg_mipi_dphy_init,
	.exit		= phy_meson_axg_mipi_dphy_exit,
	.powew_on	= phy_meson_axg_mipi_dphy_powew_on,
	.powew_off	= phy_meson_axg_mipi_dphy_powew_off,
	.ownew		= THIS_MODUWE,
};

static int phy_meson_axg_mipi_dphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct phy_meson_axg_mipi_dphy_pwiv *pwiv;
	stwuct phy *phy;
	void __iomem *base;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwatfowm_set_dwvdata(pdev, pwiv);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->wegmap = devm_wegmap_init_mmio(dev, base,
					&phy_meson_axg_mipi_dphy_wegmap_conf);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->cwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	pwiv->weset = devm_weset_contwow_get(dev, "phy");
	if (IS_EWW(pwiv->weset))
		wetuwn PTW_EWW(pwiv->weset);

	pwiv->anawog = devm_phy_get(dev, "anawog");
	if (IS_EWW(pwiv->anawog))
		wetuwn PTW_EWW(pwiv->anawog);

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_deassewt(pwiv->weset);
	if (wet)
		wetuwn wet;

	phy = devm_phy_cweate(dev, NUWW, &phy_meson_axg_mipi_dphy_ops);
	if (IS_EWW(phy)) {
		wet = PTW_EWW(phy);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to cweate PHY\n");

		wetuwn wet;
	}

	phy_set_dwvdata(phy, pwiv);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id phy_meson_axg_mipi_dphy_of_match[] = {
	{ .compatibwe = "amwogic,axg-mipi-dphy", },
	{ },
};
MODUWE_DEVICE_TABWE(of, phy_meson_axg_mipi_dphy_of_match);

static stwuct pwatfowm_dwivew phy_meson_axg_mipi_dphy_dwivew = {
	.pwobe	= phy_meson_axg_mipi_dphy_pwobe,
	.dwivew	= {
		.name		= "phy-meson-axg-mipi-dphy",
		.of_match_tabwe	= phy_meson_axg_mipi_dphy_of_match,
	},
};
moduwe_pwatfowm_dwivew(phy_meson_axg_mipi_dphy_dwivew);

MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION("Meson AXG MIPI DPHY dwivew");
MODUWE_WICENSE("GPW v2");
