// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mantix MWAF057WE51 5.7" MIPI-DSI panew dwivew
 *
 * Copywight (C) Puwism SPC 2020
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define DWV_NAME "panew-mantix-mwaf057we51"

/* Manufactuwew specific Commands send via DSI */
#define MANTIX_CMD_OTP_STOP_WEWOAD_MIPI 0x41
#define MANTIX_CMD_INT_CANCEW           0x4C
#define MANTIX_CMD_SPI_FINISH           0x90

stwuct mantix {
	stwuct device *dev;
	stwuct dwm_panew panew;

	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *tp_wstn_gpio;

	stwuct weguwatow *avdd;
	stwuct weguwatow *avee;
	stwuct weguwatow *vddi;

	const stwuct dwm_dispway_mode *defauwt_mode;
};

static inwine stwuct mantix *panew_to_mantix(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct mantix, panew);
}

static int mantix_init_sequence(stwuct mantix *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	stwuct device *dev = ctx->dev;

	/*
	 * Init sequence was suppwied by the panew vendow.
	 */
	mipi_dsi_genewic_wwite_seq(dsi, MANTIX_CMD_OTP_STOP_WEWOAD_MIPI, 0x5A);

	mipi_dsi_genewic_wwite_seq(dsi, MANTIX_CMD_INT_CANCEW, 0x03);
	mipi_dsi_genewic_wwite_seq(dsi, MANTIX_CMD_OTP_STOP_WEWOAD_MIPI, 0x5A, 0x03);
	mipi_dsi_genewic_wwite_seq(dsi, 0x80, 0xA9, 0x00);

	mipi_dsi_genewic_wwite_seq(dsi, MANTIX_CMD_OTP_STOP_WEWOAD_MIPI, 0x5A, 0x09);
	mipi_dsi_genewic_wwite_seq(dsi, 0x80, 0x64, 0x00, 0x64, 0x00, 0x00);
	msweep(20);

	mipi_dsi_genewic_wwite_seq(dsi, MANTIX_CMD_SPI_FINISH, 0xA5);
	mipi_dsi_genewic_wwite_seq(dsi, MANTIX_CMD_OTP_STOP_WEWOAD_MIPI, 0x00, 0x2F);
	msweep(20);

	dev_dbg(dev, "Panew init sequence done\n");
	wetuwn 0;
}

static int mantix_enabwe(stwuct dwm_panew *panew)
{
	stwuct mantix *ctx = panew_to_mantix(panew);
	stwuct device *dev = ctx->dev;
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);
	int wet;

	wet = mantix_init_sequence(ctx);
	if (wet < 0) {
		dev_eww(ctx->dev, "Panew init sequence faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode\n");
		wetuwn wet;
	}
	msweep(20);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet)
		wetuwn wet;
	usweep_wange(10000, 12000);

	wet = mipi_dsi_tuwn_on_pewiphewaw(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to tuwn on pewiphewaw\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int mantix_disabwe(stwuct dwm_panew *panew)
{
	stwuct mantix *ctx = panew_to_mantix(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0)
		dev_eww(ctx->dev, "Faiwed to tuwn off the dispway: %d\n", wet);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0)
		dev_eww(ctx->dev, "Faiwed to entew sweep mode: %d\n", wet);


	wetuwn 0;
}

static int mantix_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct mantix *ctx = panew_to_mantix(panew);

	gpiod_set_vawue_cansweep(ctx->tp_wstn_gpio, 1);
	usweep_wange(5000, 6000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);

	weguwatow_disabwe(ctx->avee);
	weguwatow_disabwe(ctx->avdd);
	/* T11 */
	usweep_wange(5000, 6000);
	weguwatow_disabwe(ctx->vddi);
	/* T14 */
	msweep(50);

	wetuwn 0;
}

static int mantix_pwepawe(stwuct dwm_panew *panew)
{
	stwuct mantix *ctx = panew_to_mantix(panew);
	int wet;

	/* Focawtech FT8006P, section 7.3.1 and 7.3.4 */
	dev_dbg(ctx->dev, "Wesetting the panew\n");
	wet = weguwatow_enabwe(ctx->vddi);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to enabwe vddi suppwy: %d\n", wet);
		wetuwn wet;
	}

	/* T1 + T2 */
	usweep_wange(8000, 10000);

	wet = weguwatow_enabwe(ctx->avdd);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to enabwe avdd suppwy: %d\n", wet);
		wetuwn wet;
	}

	/* T2d */
	usweep_wange(3500, 4000);
	wet = weguwatow_enabwe(ctx->avee);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to enabwe avee suppwy: %d\n", wet);
		wetuwn wet;
	}

	/* T3 + T4 + time fow vowtage to become stabwe: */
	usweep_wange(6000, 7000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	gpiod_set_vawue_cansweep(ctx->tp_wstn_gpio, 0);

	/* T6 */
	msweep(50);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode defauwt_mode_mantix = {
	.hdispway    = 720,
	.hsync_stawt = 720 + 45,
	.hsync_end   = 720 + 45 + 14,
	.htotaw	     = 720 + 45 + 14 + 25,
	.vdispway    = 1440,
	.vsync_stawt = 1440 + 130,
	.vsync_end   = 1440 + 130 + 8,
	.vtotaw	     = 1440 + 130 + 8 + 106,
	.cwock	     = 85298,
	.fwags	     = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm    = 65,
	.height_mm   = 130,
};

static const stwuct dwm_dispway_mode defauwt_mode_ys = {
	.hdispway    = 720,
	.hsync_stawt = 720 + 45,
	.hsync_end   = 720 + 45 + 14,
	.htotaw	     = 720 + 45 + 14 + 25,
	.vdispway    = 1440,
	.vsync_stawt = 1440 + 175,
	.vsync_end   = 1440 + 175 + 8,
	.vtotaw	     = 1440 + 175 + 8 + 50,
	.cwock	     = 85298,
	.fwags	     = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm    = 65,
	.height_mm   = 130,
};

static const u32 mantix_bus_fowmats[] = {
	MEDIA_BUS_FMT_WGB888_1X24,
};

static int mantix_get_modes(stwuct dwm_panew *panew,
			    stwuct dwm_connectow *connectow)
{
	stwuct mantix *ctx = panew_to_mantix(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, ctx->defauwt_mode);
	if (!mode) {
		dev_eww(ctx->dev, "Faiwed to add mode %ux%u@%u\n",
			ctx->defauwt_mode->hdispway, ctx->defauwt_mode->vdispway,
			dwm_mode_vwefwesh(ctx->defauwt_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	dwm_dispway_info_set_bus_fowmats(&connectow->dispway_info,
					 mantix_bus_fowmats,
					 AWWAY_SIZE(mantix_bus_fowmats));

	wetuwn 1;
}

static const stwuct dwm_panew_funcs mantix_dwm_funcs = {
	.disabwe   = mantix_disabwe,
	.unpwepawe = mantix_unpwepawe,
	.pwepawe   = mantix_pwepawe,
	.enabwe	   = mantix_enabwe,
	.get_modes = mantix_get_modes,
};

static int mantix_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct mantix *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->defauwt_mode = of_device_get_match_data(dev);

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ctx->weset_gpio)) {
		dev_eww(dev, "cannot get weset gpio\n");
		wetuwn PTW_EWW(ctx->weset_gpio);
	}

	ctx->tp_wstn_gpio = devm_gpiod_get(dev, "mantix,tp-wstn", GPIOD_OUT_HIGH);
	if (IS_EWW(ctx->tp_wstn_gpio)) {
		dev_eww(dev, "cannot get tp-wstn gpio\n");
		wetuwn PTW_EWW(ctx->tp_wstn_gpio);
	}

	mipi_dsi_set_dwvdata(dsi, ctx);
	ctx->dev = dev;

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO |
		MIPI_DSI_MODE_VIDEO_BUWST | MIPI_DSI_MODE_VIDEO_SYNC_PUWSE;

	ctx->avdd = devm_weguwatow_get(dev, "avdd");
	if (IS_EWW(ctx->avdd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->avdd), "Faiwed to wequest avdd weguwatow\n");

	ctx->avee = devm_weguwatow_get(dev, "avee");
	if (IS_EWW(ctx->avee))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->avee), "Faiwed to wequest avee weguwatow\n");

	ctx->vddi = devm_weguwatow_get(dev, "vddi");
	if (IS_EWW(ctx->vddi))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->vddi), "Faiwed to wequest vddi weguwatow\n");

	dwm_panew_init(&ctx->panew, dev, &mantix_dwm_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "mipi_dsi_attach faiwed (%d). Is host weady?\n", wet);
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	dev_info(dev, "%ux%u@%u %ubpp dsi %udw - weady\n",
		 ctx->defauwt_mode->hdispway, ctx->defauwt_mode->vdispway,
		 dwm_mode_vwefwesh(ctx->defauwt_mode),
		 mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat), dsi->wanes);

	wetuwn 0;
}

static void mantix_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct mantix *ctx = mipi_dsi_get_dwvdata(dsi);

	dwm_panew_unpwepawe(&ctx->panew);
	dwm_panew_disabwe(&ctx->panew);
}

static void mantix_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct mantix *ctx = mipi_dsi_get_dwvdata(dsi);

	mantix_shutdown(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id mantix_of_match[] = {
	{ .compatibwe = "mantix,mwaf057we51-x", .data = &defauwt_mode_mantix },
	{ .compatibwe = "ys,ys57pss36bh5gq", .data = &defauwt_mode_ys },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mantix_of_match);

static stwuct mipi_dsi_dwivew mantix_dwivew = {
	.pwobe	= mantix_pwobe,
	.wemove = mantix_wemove,
	.shutdown = mantix_shutdown,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = mantix_of_match,
	},
};
moduwe_mipi_dsi_dwivew(mantix_dwivew);

MODUWE_AUTHOW("Guido Günthew <agx@sigxcpu.owg>");
MODUWE_DESCWIPTION("DWM dwivew fow Mantix MWAF057WE51-X MIPI DSI panew");
MODUWE_WICENSE("GPW v2");
