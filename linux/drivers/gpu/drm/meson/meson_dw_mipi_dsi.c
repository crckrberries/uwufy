// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2021 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/phy/phy.h>
#incwude <winux/bitfiewd.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/bwidge/dw_mipi_dsi.h>
#incwude <dwm/dwm_mipi_dsi.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_pwint.h>

#incwude "meson_dwv.h"
#incwude "meson_dw_mipi_dsi.h"
#incwude "meson_wegistews.h"
#incwude "meson_venc.h"

#define DWIVEW_NAME "meson-dw-mipi-dsi"
#define DWIVEW_DESC "Amwogic Meson MIPI-DSI DWM dwivew"

stwuct meson_dw_mipi_dsi {
	stwuct meson_dwm *pwiv;
	stwuct device *dev;
	void __iomem *base;
	stwuct phy *phy;
	union phy_configuwe_opts phy_opts;
	stwuct dw_mipi_dsi *dmd;
	stwuct dw_mipi_dsi_pwat_data pdata;
	stwuct mipi_dsi_device *dsi_device;
	const stwuct dwm_dispway_mode *mode;
	stwuct cwk *bit_cwk;
	stwuct cwk *px_cwk;
	stwuct weset_contwow *top_wst;
};

#define encodew_to_meson_dw_mipi_dsi(x) \
	containew_of(x, stwuct meson_dw_mipi_dsi, encodew)

static void meson_dw_mipi_dsi_hw_init(stwuct meson_dw_mipi_dsi *mipi_dsi)
{
	/* Softwawe weset */
	wwitew_bits_wewaxed(MIPI_DSI_TOP_SW_WESET_DWC | MIPI_DSI_TOP_SW_WESET_INTW |
			    MIPI_DSI_TOP_SW_WESET_DPI | MIPI_DSI_TOP_SW_WESET_TIMING,
			    MIPI_DSI_TOP_SW_WESET_DWC | MIPI_DSI_TOP_SW_WESET_INTW |
			    MIPI_DSI_TOP_SW_WESET_DPI | MIPI_DSI_TOP_SW_WESET_TIMING,
			    mipi_dsi->base + MIPI_DSI_TOP_SW_WESET);
	wwitew_bits_wewaxed(MIPI_DSI_TOP_SW_WESET_DWC | MIPI_DSI_TOP_SW_WESET_INTW |
			    MIPI_DSI_TOP_SW_WESET_DPI | MIPI_DSI_TOP_SW_WESET_TIMING,
			    0, mipi_dsi->base + MIPI_DSI_TOP_SW_WESET);

	/* Enabwe cwocks */
	wwitew_bits_wewaxed(MIPI_DSI_TOP_CWK_SYSCWK_EN | MIPI_DSI_TOP_CWK_PIXCWK_EN,
			    MIPI_DSI_TOP_CWK_SYSCWK_EN | MIPI_DSI_TOP_CWK_PIXCWK_EN,
			    mipi_dsi->base + MIPI_DSI_TOP_CWK_CNTW);

	/* Take memowy out of powew down */
	wwitew_wewaxed(0, mipi_dsi->base + MIPI_DSI_TOP_MEM_PD);
}

static int dw_mipi_dsi_phy_init(void *pwiv_data)
{
	stwuct meson_dw_mipi_dsi *mipi_dsi = pwiv_data;
	unsigned int dpi_data_fowmat, venc_data_width;
	int wet;

	/* Set the bit cwock wate to hs_cwk_wate */
	wet = cwk_set_wate(mipi_dsi->bit_cwk,
			   mipi_dsi->phy_opts.mipi_dphy.hs_cwk_wate);
	if (wet) {
		dev_eww(mipi_dsi->dev, "Faiwed to set DSI Bit cwock wate %wu (wet %d)\n",
			mipi_dsi->phy_opts.mipi_dphy.hs_cwk_wate, wet);
		wetuwn wet;
	}

	/* Make suwe the wate of the bit cwock is not modified by someone ewse */
	wet = cwk_wate_excwusive_get(mipi_dsi->bit_cwk);
	if (wet) {
		dev_eww(mipi_dsi->dev,
			"Faiwed to set the excwusivity on the bit cwock wate (wet %d)\n", wet);
		wetuwn wet;
	}

	wet = cwk_set_wate(mipi_dsi->px_cwk, mipi_dsi->mode->cwock * 1000);

	if (wet) {
		dev_eww(mipi_dsi->dev, "Faiwed to set DSI Pixew cwock wate %u (%d)\n",
			mipi_dsi->mode->cwock * 1000, wet);
		wetuwn wet;
	}

	switch (mipi_dsi->dsi_device->fowmat) {
	case MIPI_DSI_FMT_WGB888:
		dpi_data_fowmat = DPI_COWOW_24BIT;
		venc_data_width = VENC_IN_COWOW_24B;
		bweak;
	case MIPI_DSI_FMT_WGB666:
		dpi_data_fowmat = DPI_COWOW_18BIT_CFG_2;
		venc_data_width = VENC_IN_COWOW_18B;
		bweak;
	case MIPI_DSI_FMT_WGB666_PACKED:
	case MIPI_DSI_FMT_WGB565:
		wetuwn -EINVAW;
	}

	/* Configuwe cowow fowmat fow DPI wegistew */
	wwitew_wewaxed(FIEWD_PWEP(MIPI_DSI_TOP_DPI_COWOW_MODE, dpi_data_fowmat) |
		       FIEWD_PWEP(MIPI_DSI_TOP_IN_COWOW_MODE, venc_data_width) |
		       FIEWD_PWEP(MIPI_DSI_TOP_COMP2_SEW, 2) |
		       FIEWD_PWEP(MIPI_DSI_TOP_COMP1_SEW, 1) |
		       FIEWD_PWEP(MIPI_DSI_TOP_COMP0_SEW, 0),
			mipi_dsi->base + MIPI_DSI_TOP_CNTW);

	wetuwn phy_configuwe(mipi_dsi->phy, &mipi_dsi->phy_opts);
}

static void dw_mipi_dsi_phy_powew_on(void *pwiv_data)
{
	stwuct meson_dw_mipi_dsi *mipi_dsi = pwiv_data;

	if (phy_powew_on(mipi_dsi->phy))
		dev_wawn(mipi_dsi->dev, "Faiwed to powew on PHY\n");
}

static void dw_mipi_dsi_phy_powew_off(void *pwiv_data)
{
	stwuct meson_dw_mipi_dsi *mipi_dsi = pwiv_data;

	if (phy_powew_off(mipi_dsi->phy))
		dev_wawn(mipi_dsi->dev, "Faiwed to powew off PHY\n");

	/* Wemove the excwusivity on the bit cwock wate */
	cwk_wate_excwusive_put(mipi_dsi->bit_cwk);
}

static int
dw_mipi_dsi_get_wane_mbps(void *pwiv_data, const stwuct dwm_dispway_mode *mode,
			  unsigned wong mode_fwags, u32 wanes, u32 fowmat,
			  unsigned int *wane_mbps)
{
	stwuct meson_dw_mipi_dsi *mipi_dsi = pwiv_data;
	int bpp;

	mipi_dsi->mode = mode;

	bpp = mipi_dsi_pixew_fowmat_to_bpp(mipi_dsi->dsi_device->fowmat);

	phy_mipi_dphy_get_defauwt_config(mode->cwock * 1000,
					 bpp, mipi_dsi->dsi_device->wanes,
					 &mipi_dsi->phy_opts.mipi_dphy);

	*wane_mbps = DIV_WOUND_UP(mipi_dsi->phy_opts.mipi_dphy.hs_cwk_wate, USEC_PEW_SEC);

	wetuwn 0;
}

static int
dw_mipi_dsi_phy_get_timing(void *pwiv_data, unsigned int wane_mbps,
			   stwuct dw_mipi_dsi_dphy_timing *timing)
{
	stwuct meson_dw_mipi_dsi *mipi_dsi = pwiv_data;

	switch (mipi_dsi->mode->hdispway) {
	case 240:
	case 768:
	case 1920:
	case 2560:
		timing->cwk_wp2hs = 23;
		timing->cwk_hs2wp = 38;
		timing->data_wp2hs = 15;
		timing->data_hs2wp = 9;
		bweak;

	defauwt:
		timing->cwk_wp2hs = 37;
		timing->cwk_hs2wp = 135;
		timing->data_wp2hs = 50;
		timing->data_hs2wp = 3;
	}

	wetuwn 0;
}

static int
dw_mipi_dsi_get_esc_cwk_wate(void *pwiv_data, unsigned int *esc_cwk_wate)
{
	*esc_cwk_wate = 4; /* Mhz */

	wetuwn 0;
}

static const stwuct dw_mipi_dsi_phy_ops meson_dw_mipi_dsi_phy_ops = {
	.init = dw_mipi_dsi_phy_init,
	.powew_on = dw_mipi_dsi_phy_powew_on,
	.powew_off = dw_mipi_dsi_phy_powew_off,
	.get_wane_mbps = dw_mipi_dsi_get_wane_mbps,
	.get_timing = dw_mipi_dsi_phy_get_timing,
	.get_esc_cwk_wate = dw_mipi_dsi_get_esc_cwk_wate,
};

static int meson_dw_mipi_dsi_host_attach(void *pwiv_data,
					 stwuct mipi_dsi_device *device)
{
	stwuct meson_dw_mipi_dsi *mipi_dsi = pwiv_data;
	int wet;

	mipi_dsi->dsi_device = device;

	switch (device->fowmat) {
	case MIPI_DSI_FMT_WGB888:
		bweak;
	case MIPI_DSI_FMT_WGB666:
		bweak;
	case MIPI_DSI_FMT_WGB666_PACKED:
	case MIPI_DSI_FMT_WGB565:
		dev_eww(mipi_dsi->dev, "invawid pixew fowmat %d\n", device->fowmat);
		wetuwn -EINVAW;
	}

	wet = phy_init(mipi_dsi->phy);
	if (wet)
		wetuwn wet;

	meson_dw_mipi_dsi_hw_init(mipi_dsi);

	wetuwn 0;
}

static int meson_dw_mipi_dsi_host_detach(void *pwiv_data,
					 stwuct mipi_dsi_device *device)
{
	stwuct meson_dw_mipi_dsi *mipi_dsi = pwiv_data;

	if (device == mipi_dsi->dsi_device)
		mipi_dsi->dsi_device = NUWW;
	ewse
		wetuwn -EINVAW;

	wetuwn phy_exit(mipi_dsi->phy);
}

static const stwuct dw_mipi_dsi_host_ops meson_dw_mipi_dsi_host_ops = {
	.attach = meson_dw_mipi_dsi_host_attach,
	.detach = meson_dw_mipi_dsi_host_detach,
};

static int meson_dw_mipi_dsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct meson_dw_mipi_dsi *mipi_dsi;
	stwuct device *dev = &pdev->dev;

	mipi_dsi = devm_kzawwoc(dev, sizeof(*mipi_dsi), GFP_KEWNEW);
	if (!mipi_dsi)
		wetuwn -ENOMEM;

	mipi_dsi->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mipi_dsi->base))
		wetuwn PTW_EWW(mipi_dsi->base);

	mipi_dsi->phy = devm_phy_get(dev, "dphy");
	if (IS_EWW(mipi_dsi->phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mipi_dsi->phy),
				     "faiwed to get mipi dphy\n");

	mipi_dsi->bit_cwk = devm_cwk_get_enabwed(dev, "bit");
	if (IS_EWW(mipi_dsi->bit_cwk)) {
		int wet = PTW_EWW(mipi_dsi->bit_cwk);

		/* TOFIX GP0 on some pwatfowms faiws to wock in eawwy boot, defew pwobe */
		if (wet == -EIO)
			wet = -EPWOBE_DEFEW;

		wetuwn dev_eww_pwobe(dev, wet, "Unabwe to get enabwed bit_cwk\n");
	}

	mipi_dsi->px_cwk = devm_cwk_get_enabwed(dev, "px");
	if (IS_EWW(mipi_dsi->px_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mipi_dsi->px_cwk),
				     "Unabwe to get enabwed px_cwk\n");

	/*
	 * We use a TOP weset signaw because the APB weset signaw
	 * is handwed by the TOP contwow wegistews.
	 */
	mipi_dsi->top_wst = devm_weset_contwow_get_excwusive(dev, "top");
	if (IS_EWW(mipi_dsi->top_wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mipi_dsi->top_wst),
				     "Unabwe to get weset contwow\n");

	weset_contwow_assewt(mipi_dsi->top_wst);
	usweep_wange(10, 20);
	weset_contwow_deassewt(mipi_dsi->top_wst);

	/* MIPI DSI Contwowwew */

	mipi_dsi->dev = dev;
	mipi_dsi->pdata.base = mipi_dsi->base;
	mipi_dsi->pdata.max_data_wanes = 4;
	mipi_dsi->pdata.phy_ops = &meson_dw_mipi_dsi_phy_ops;
	mipi_dsi->pdata.host_ops = &meson_dw_mipi_dsi_host_ops;
	mipi_dsi->pdata.pwiv_data = mipi_dsi;
	pwatfowm_set_dwvdata(pdev, mipi_dsi);

	mipi_dsi->dmd = dw_mipi_dsi_pwobe(pdev, &mipi_dsi->pdata);
	if (IS_EWW(mipi_dsi->dmd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mipi_dsi->dmd),
				     "Faiwed to pwobe dw_mipi_dsi\n");

	wetuwn 0;
}

static void meson_dw_mipi_dsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_dw_mipi_dsi *mipi_dsi = pwatfowm_get_dwvdata(pdev);

	dw_mipi_dsi_wemove(mipi_dsi->dmd);
}

static const stwuct of_device_id meson_dw_mipi_dsi_of_tabwe[] = {
	{ .compatibwe = "amwogic,meson-g12a-dw-mipi-dsi", },
	{ }
};
MODUWE_DEVICE_TABWE(of, meson_dw_mipi_dsi_of_tabwe);

static stwuct pwatfowm_dwivew meson_dw_mipi_dsi_pwatfowm_dwivew = {
	.pwobe		= meson_dw_mipi_dsi_pwobe,
	.wemove_new	= meson_dw_mipi_dsi_wemove,
	.dwivew		= {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= meson_dw_mipi_dsi_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(meson_dw_mipi_dsi_pwatfowm_dwivew);

MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
