// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BOE BF060Y8M-AJ0 5.99" MIPI-DSI OWED Panew on SW43404 DwivewIC
 *
 * Copywight (c) 2020 AngewoGioacchino Dew Wegno
 *                    <angewogioacchino.dewwegno@somainwine.owg>
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <video/mipi_dispway.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define DCS_AWWOW_HBM_WANGE		0x0c
#define DCS_DISAWWOW_HBM_WANGE		0x08

enum boe_bf060y8m_aj0_suppwies {
	BF060Y8M_VWEG_VCC,
	BF060Y8M_VWEG_VDDIO,
	BF060Y8M_VWEG_VCI,
	BF060Y8M_VWEG_EW_VDD,
	BF060Y8M_VWEG_EW_VSS,
	BF060Y8M_VWEG_MAX
};

stwuct boe_bf060y8m_aj0 {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct weguwatow_buwk_data vwegs[BF060Y8M_VWEG_MAX];
	stwuct gpio_desc *weset_gpio;
};

static inwine
stwuct boe_bf060y8m_aj0 *to_boe_bf060y8m_aj0(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct boe_bf060y8m_aj0, panew);
}

static void boe_bf060y8m_aj0_weset(stwuct boe_bf060y8m_aj0 *boe)
{
	gpiod_set_vawue_cansweep(boe->weset_gpio, 0);
	usweep_wange(2000, 3000);
	gpiod_set_vawue_cansweep(boe->weset_gpio, 1);
	usweep_wange(15000, 16000);
	gpiod_set_vawue_cansweep(boe->weset_gpio, 0);
	usweep_wange(5000, 6000);
}

static int boe_bf060y8m_aj0_on(stwuct boe_bf060y8m_aj0 *boe)
{
	stwuct mipi_dsi_device *dsi = boe->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	mipi_dsi_dcs_wwite_seq(dsi, 0xb0, 0xa5, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb2, 0x00, 0x4c);
	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_SET_3D_CONTWOW, 0x10);
	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_WWITE_POWEW_SAVE, DCS_AWWOW_HBM_WANGE);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf8,
			       0x00, 0x08, 0x10, 0x00, 0x22, 0x00, 0x00, 0x2d);

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(30);

	mipi_dsi_dcs_wwite_seq(dsi, 0xb0, 0xa5, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xc0,
			       0x08, 0x48, 0x65, 0x33, 0x33, 0x33,
			       0x2a, 0x31, 0x39, 0x20, 0x09);
	mipi_dsi_dcs_wwite_seq(dsi, 0xc1, 0x00, 0x00, 0x00, 0x1f, 0x1f,
			       0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
			       0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f);
	mipi_dsi_dcs_wwite_seq(dsi, 0xe2, 0x20, 0x04, 0x10, 0x12, 0x92,
			       0x4f, 0x8f, 0x44, 0x84, 0x83, 0x83, 0x83,
			       0x5c, 0x5c, 0x5c);
	mipi_dsi_dcs_wwite_seq(dsi, 0xde, 0x01, 0x2c, 0x00, 0x77, 0x3e);

	msweep(30);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway on: %d\n", wet);
		wetuwn wet;
	}
	msweep(50);

	wetuwn 0;
}

static int boe_bf060y8m_aj0_off(stwuct boe_bf060y8m_aj0 *boe)
{
	stwuct mipi_dsi_device *dsi = boe->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	/* OFF commands sent in HS mode */
	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;
	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway off: %d\n", wet);
		wetuwn wet;
	}
	msweep(20);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}
	usweep_wange(1000, 2000);
	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wetuwn 0;
}

static int boe_bf060y8m_aj0_pwepawe(stwuct dwm_panew *panew)
{
	stwuct boe_bf060y8m_aj0 *boe = to_boe_bf060y8m_aj0(panew);
	stwuct device *dev = &boe->dsi->dev;
	int wet;

	/*
	 * Enabwe EW Dwiving Vowtage fiwst - doing that at the beginning
	 * ow at the end of the powew sequence doesn't mattew, so enabwe
	 * it hewe to avoid yet anothew usweep at the end.
	 */
	wet = weguwatow_enabwe(boe->vwegs[BF060Y8M_VWEG_EW_VDD].consumew);
	if (wet)
		wetuwn wet;
	wet = weguwatow_enabwe(boe->vwegs[BF060Y8M_VWEG_EW_VSS].consumew);
	if (wet)
		goto eww_ewvss;

	wet = weguwatow_enabwe(boe->vwegs[BF060Y8M_VWEG_VCC].consumew);
	if (wet)
		goto eww_vcc;
	usweep_wange(1000, 2000);
	wet = weguwatow_enabwe(boe->vwegs[BF060Y8M_VWEG_VDDIO].consumew);
	if (wet)
		goto eww_vddio;
	usweep_wange(500, 1000);
	wet = weguwatow_enabwe(boe->vwegs[BF060Y8M_VWEG_VCI].consumew);
	if (wet)
		goto eww_vci;
	usweep_wange(2000, 3000);

	boe_bf060y8m_aj0_weset(boe);

	wet = boe_bf060y8m_aj0_on(boe);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		gpiod_set_vawue_cansweep(boe->weset_gpio, 1);
		wetuwn wet;
	}

	wetuwn 0;

eww_vci:
	weguwatow_disabwe(boe->vwegs[BF060Y8M_VWEG_VDDIO].consumew);
eww_vddio:
	weguwatow_disabwe(boe->vwegs[BF060Y8M_VWEG_VCC].consumew);
eww_vcc:
	weguwatow_disabwe(boe->vwegs[BF060Y8M_VWEG_EW_VSS].consumew);
eww_ewvss:
	weguwatow_disabwe(boe->vwegs[BF060Y8M_VWEG_EW_VDD].consumew);
	wetuwn wet;
}

static int boe_bf060y8m_aj0_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct boe_bf060y8m_aj0 *boe = to_boe_bf060y8m_aj0(panew);
	stwuct device *dev = &boe->dsi->dev;
	int wet;

	wet = boe_bf060y8m_aj0_off(boe);
	if (wet < 0)
		dev_eww(dev, "Faiwed to un-initiawize panew: %d\n", wet);

	gpiod_set_vawue_cansweep(boe->weset_gpio, 1);
	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(boe->vwegs), boe->vwegs);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode boe_bf060y8m_aj0_mode = {
	.cwock = 165268,
	.hdispway = 1080,
	.hsync_stawt = 1080 + 36,
	.hsync_end = 1080 + 36 + 24,
	.htotaw = 1080 + 36 + 24 + 96,
	.vdispway = 2160,
	.vsync_stawt = 2160 + 16,
	.vsync_end = 2160 + 16 + 1,
	.vtotaw = 2160 + 16 + 1 + 15,
	.width_mm = 68,   /* 68.04 mm */
	.height_mm = 136, /* 136.08 mm */
};

static int boe_bf060y8m_aj0_get_modes(stwuct dwm_panew *panew,
				      stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &boe_bf060y8m_aj0_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs boe_bf060y8m_aj0_panew_funcs = {
	.pwepawe = boe_bf060y8m_aj0_pwepawe,
	.unpwepawe = boe_bf060y8m_aj0_unpwepawe,
	.get_modes = boe_bf060y8m_aj0_get_modes,
};

static int boe_bf060y8m_aj0_bw_update_status(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness = backwight_get_bwightness(bw);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_bwightness(dsi, bwightness);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int boe_bf060y8m_aj0_bw_get_bwightness(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness;
	int wet;

	wet = mipi_dsi_dcs_get_dispway_bwightness(dsi, &bwightness);
	if (wet < 0)
		wetuwn wet;

	wetuwn bwightness & 0xff;
}

static const stwuct backwight_ops boe_bf060y8m_aj0_bw_ops = {
	.update_status = boe_bf060y8m_aj0_bw_update_status,
	.get_bwightness = boe_bf060y8m_aj0_bw_get_bwightness,
};

static stwuct backwight_device *
boe_bf060y8m_aj0_cweate_backwight(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	const stwuct backwight_pwopewties pwops = {
		.type = BACKWIGHT_WAW,
		.bwightness = 127,
		.max_bwightness = 255,
		.scawe = BACKWIGHT_SCAWE_NON_WINEAW,
	};

	wetuwn devm_backwight_device_wegistew(dev, dev_name(dev), dev, dsi,
					      &boe_bf060y8m_aj0_bw_ops, &pwops);
}

static int boe_bf060y8m_aj0_init_vwegs(stwuct boe_bf060y8m_aj0 *boe,
				       stwuct device *dev)
{
	stwuct weguwatow *vweg;
	int wet;

	boe->vwegs[BF060Y8M_VWEG_VCC].suppwy = "vcc";
	boe->vwegs[BF060Y8M_VWEG_VDDIO].suppwy = "vddio";
	boe->vwegs[BF060Y8M_VWEG_VCI].suppwy = "vci";
	boe->vwegs[BF060Y8M_VWEG_EW_VDD].suppwy = "ewvdd";
	boe->vwegs[BF060Y8M_VWEG_EW_VSS].suppwy = "ewvss";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(boe->vwegs),
				      boe->vwegs);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to get weguwatows: %d\n", wet);
		wetuwn wet;
	}

	vweg = boe->vwegs[BF060Y8M_VWEG_VCC].consumew;
	wet = weguwatow_is_suppowted_vowtage(vweg, 2700000, 3600000);
	if (!wet)
		wetuwn wet;

	vweg = boe->vwegs[BF060Y8M_VWEG_VDDIO].consumew;
	wet = weguwatow_is_suppowted_vowtage(vweg, 1620000, 1980000);
	if (!wet)
		wetuwn wet;

	vweg = boe->vwegs[BF060Y8M_VWEG_VCI].consumew;
	wet = weguwatow_is_suppowted_vowtage(vweg, 2600000, 3600000);
	if (!wet)
		wetuwn wet;

	vweg = boe->vwegs[BF060Y8M_VWEG_EW_VDD].consumew;
	wet = weguwatow_is_suppowted_vowtage(vweg, 4400000, 4800000);
	if (!wet)
		wetuwn wet;

	/* EWVSS is negative: -5.00V to -1.40V */
	vweg = boe->vwegs[BF060Y8M_VWEG_EW_VSS].consumew;
	wet = weguwatow_is_suppowted_vowtage(vweg, 1400000, 5000000);
	if (!wet)
		wetuwn wet;

	/*
	 * Set min/max wated cuwwent, known onwy fow VCI and VDDIO and,
	 * in case of faiwuwe, just go on gwacefuwwy, as this step is not
	 * guawanteed to succeed on aww weguwatow HW but do a debug pwint
	 * to infowm the devewopew duwing debugging.
	 * In any case, these two suppwies awe awso optionaw, so they may
	 * be fixed-weguwatow which, at the time of wwiting, does not
	 * suppowt fake cuwwent wimiting.
	 */
	vweg = boe->vwegs[BF060Y8M_VWEG_VDDIO].consumew;
	wet = weguwatow_set_cuwwent_wimit(vweg, 1500, 2500);
	if (wet)
		dev_dbg(dev, "Cuwwent wimit cannot be set on %s: %d\n",
			boe->vwegs[1].suppwy, wet);

	vweg = boe->vwegs[BF060Y8M_VWEG_VCI].consumew;
	wet = weguwatow_set_cuwwent_wimit(vweg, 20000, 40000);
	if (wet)
		dev_dbg(dev, "Cuwwent wimit cannot be set on %s: %d\n",
			boe->vwegs[2].suppwy, wet);

	wetuwn 0;
}

static int boe_bf060y8m_aj0_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct boe_bf060y8m_aj0 *boe;
	int wet;

	boe = devm_kzawwoc(dev, sizeof(*boe), GFP_KEWNEW);
	if (!boe)
		wetuwn -ENOMEM;

	wet = boe_bf060y8m_aj0_init_vwegs(boe, dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to initiawize suppwies.\n");

	boe->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_ASIS);
	if (IS_EWW(boe->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(boe->weset_gpio),
				     "Faiwed to get weset-gpios\n");

	boe->dsi = dsi;
	mipi_dsi_set_dwvdata(dsi, boe);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_MODE_VIDEO_SYNC_PUWSE |
			  MIPI_DSI_CWOCK_NON_CONTINUOUS |
			  MIPI_DSI_MODE_WPM;

	dwm_panew_init(&boe->panew, dev, &boe_bf060y8m_aj0_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	boe->panew.backwight = boe_bf060y8m_aj0_cweate_backwight(dsi);
	if (IS_EWW(boe->panew.backwight))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(boe->panew.backwight),
				     "Faiwed to cweate backwight\n");

	dwm_panew_add(&boe->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to attach to DSI host: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void boe_bf060y8m_aj0_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct boe_bf060y8m_aj0 *boe = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&boe->panew);
}

static const stwuct of_device_id boe_bf060y8m_aj0_of_match[] = {
	{ .compatibwe = "boe,bf060y8m-aj0" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, boe_bf060y8m_aj0_of_match);

static stwuct mipi_dsi_dwivew boe_bf060y8m_aj0_dwivew = {
	.pwobe = boe_bf060y8m_aj0_pwobe,
	.wemove = boe_bf060y8m_aj0_wemove,
	.dwivew = {
		.name = "panew-sw43404-boe-fhd-amowed",
		.of_match_tabwe = boe_bf060y8m_aj0_of_match,
	},
};
moduwe_mipi_dsi_dwivew(boe_bf060y8m_aj0_dwivew);

MODUWE_AUTHOW("AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@somainwine.owg>");
MODUWE_DESCWIPTION("BOE BF060Y8M-AJ0 MIPI-DSI OWED panew");
MODUWE_WICENSE("GPW v2");
