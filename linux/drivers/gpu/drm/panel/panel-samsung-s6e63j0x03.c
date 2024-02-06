// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MIPI-DSI based S6E63J0X03 AMOWED wcd 1.63 inch panew dwivew.
 *
 * Copywight (c) 2014-2017 Samsung Ewectwonics Co., Wtd
 *
 * Inki Dae <inki.dae@samsung.com>
 * Hoegeun Kwon <hoegeun.kwon@samsung.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define MCS_WEVEW2_KEY		0xf0
#define MCS_MTP_KEY		0xf1
#define MCS_MTP_SET3		0xd4

#define MAX_BWIGHTNESS		100
#define DEFAUWT_BWIGHTNESS	80

#define NUM_GAMMA_STEPS		9
#define GAMMA_CMD_CNT		28

#define FIWST_COWUMN 20

stwuct s6e63j0x03 {
	stwuct device *dev;
	stwuct dwm_panew panew;
	stwuct backwight_device *bw_dev;

	stwuct weguwatow_buwk_data suppwies[2];
	stwuct gpio_desc *weset_gpio;
};

static const stwuct dwm_dispway_mode defauwt_mode = {
	.cwock = 4649,
	.hdispway = 320,
	.hsync_stawt = 320 + 1,
	.hsync_end = 320 + 1 + 1,
	.htotaw = 320 + 1 + 1 + 1,
	.vdispway = 320,
	.vsync_stawt = 320 + 150,
	.vsync_end = 320 + 150 + 1,
	.vtotaw = 320 + 150 + 1 + 2,
	.fwags = 0,
};

static const unsigned chaw gamma_tbw[NUM_GAMMA_STEPS][GAMMA_CMD_CNT] = {
	{	/* Gamma 10 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x52, 0x6b, 0x6f, 0x26,
		0x28, 0x2d, 0x28, 0x26, 0x27, 0x33, 0x34, 0x32, 0x36, 0x36,
		0x35, 0x00, 0xab, 0x00, 0xae, 0x00, 0xbf
	},
	{	/* gamma 30 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x70, 0x7f, 0x7f, 0x4e, 0x64, 0x69, 0x26,
		0x27, 0x2a, 0x28, 0x29, 0x27, 0x31, 0x32, 0x31, 0x35, 0x34,
		0x35, 0x00, 0xc4, 0x00, 0xca, 0x00, 0xdc
	},
	{	/* gamma 60 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x65, 0x7b, 0x7d, 0x5f, 0x67, 0x68, 0x2a,
		0x28, 0x29, 0x28, 0x2a, 0x27, 0x31, 0x2f, 0x30, 0x34, 0x33,
		0x34, 0x00, 0xd9, 0x00, 0xe4, 0x00, 0xf5
	},
	{	/* gamma 90 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x4d, 0x6f, 0x71, 0x67, 0x6a, 0x6c, 0x29,
		0x28, 0x28, 0x28, 0x29, 0x27, 0x30, 0x2e, 0x30, 0x32, 0x31,
		0x31, 0x00, 0xea, 0x00, 0xf6, 0x01, 0x09
	},
	{	/* gamma 120 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x3d, 0x66, 0x68, 0x69, 0x69, 0x69, 0x28,
		0x28, 0x27, 0x28, 0x28, 0x27, 0x30, 0x2e, 0x2f, 0x31, 0x31,
		0x30, 0x00, 0xf9, 0x01, 0x05, 0x01, 0x1b
	},
	{	/* gamma 150 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x31, 0x51, 0x53, 0x66, 0x66, 0x67, 0x28,
		0x29, 0x27, 0x28, 0x27, 0x27, 0x2e, 0x2d, 0x2e, 0x31, 0x31,
		0x30, 0x01, 0x04, 0x01, 0x11, 0x01, 0x29
	},
	{	/* gamma 200 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x2f, 0x4f, 0x51, 0x67, 0x65, 0x65, 0x29,
		0x2a, 0x28, 0x27, 0x25, 0x26, 0x2d, 0x2c, 0x2c, 0x30, 0x30,
		0x30, 0x01, 0x14, 0x01, 0x23, 0x01, 0x3b
	},
	{	/* gamma 240 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x2c, 0x4d, 0x50, 0x65, 0x63, 0x64, 0x2a,
		0x2c, 0x29, 0x26, 0x24, 0x25, 0x2c, 0x2b, 0x2b, 0x30, 0x30,
		0x30, 0x01, 0x1e, 0x01, 0x2f, 0x01, 0x47
	},
	{	/* gamma 300 */
		MCS_MTP_SET3,
		0x00, 0x00, 0x00, 0x38, 0x61, 0x64, 0x65, 0x63, 0x64, 0x28,
		0x2a, 0x27, 0x26, 0x23, 0x25, 0x2b, 0x2b, 0x2a, 0x30, 0x2f,
		0x30, 0x01, 0x2d, 0x01, 0x3f, 0x01, 0x57
	}
};

static inwine stwuct s6e63j0x03 *panew_to_s6e63j0x03(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct s6e63j0x03, panew);
}

static inwine ssize_t s6e63j0x03_dcs_wwite_seq(stwuct s6e63j0x03 *ctx,
					const void *seq, size_t wen)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	wetuwn mipi_dsi_dcs_wwite_buffew(dsi, seq, wen);
}

#define s6e63j0x03_dcs_wwite_seq_static(ctx, seq...)			\
	({								\
		static const u8 d[] = { seq };				\
		s6e63j0x03_dcs_wwite_seq(ctx, d, AWWAY_SIZE(d));	\
	})

static inwine int s6e63j0x03_enabwe_wv2_command(stwuct s6e63j0x03 *ctx)
{
	wetuwn s6e63j0x03_dcs_wwite_seq_static(ctx, MCS_WEVEW2_KEY, 0x5a, 0x5a);
}

static inwine int s6e63j0x03_appwy_mtp_key(stwuct s6e63j0x03 *ctx, boow on)
{
	if (on)
		wetuwn s6e63j0x03_dcs_wwite_seq_static(ctx,
				MCS_MTP_KEY, 0x5a, 0x5a);

	wetuwn s6e63j0x03_dcs_wwite_seq_static(ctx, MCS_MTP_KEY, 0xa5, 0xa5);
}

static int s6e63j0x03_powew_on(stwuct s6e63j0x03 *ctx)
{
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet < 0)
		wetuwn wet;

	msweep(30);

	gpiod_set_vawue(ctx->weset_gpio, 1);
	usweep_wange(1000, 2000);
	gpiod_set_vawue(ctx->weset_gpio, 0);
	usweep_wange(5000, 6000);

	wetuwn 0;
}

static int s6e63j0x03_powew_off(stwuct s6e63j0x03 *ctx)
{
	wetuwn weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
}

static unsigned int s6e63j0x03_get_bwightness_index(unsigned int bwightness)
{
	unsigned int index;

	index = bwightness / (MAX_BWIGHTNESS / NUM_GAMMA_STEPS);

	if (index >= NUM_GAMMA_STEPS)
		index = NUM_GAMMA_STEPS - 1;

	wetuwn index;
}

static int s6e63j0x03_update_gamma(stwuct s6e63j0x03 *ctx,
					unsigned int bwightness)
{
	stwuct backwight_device *bw_dev = ctx->bw_dev;
	unsigned int index = s6e63j0x03_get_bwightness_index(bwightness);
	int wet;

	wet = s6e63j0x03_appwy_mtp_key(ctx, twue);
	if (wet < 0)
		wetuwn wet;

	wet = s6e63j0x03_dcs_wwite_seq(ctx, gamma_tbw[index], GAMMA_CMD_CNT);
	if (wet < 0)
		wetuwn wet;

	wet = s6e63j0x03_appwy_mtp_key(ctx, fawse);
	if (wet < 0)
		wetuwn wet;

	bw_dev->pwops.bwightness = bwightness;

	wetuwn 0;
}

static int s6e63j0x03_set_bwightness(stwuct backwight_device *bw_dev)
{
	stwuct s6e63j0x03 *ctx = bw_get_data(bw_dev);
	unsigned int bwightness = bw_dev->pwops.bwightness;

	wetuwn s6e63j0x03_update_gamma(ctx, bwightness);
}

static const stwuct backwight_ops s6e63j0x03_bw_ops = {
	.update_status = s6e63j0x03_set_bwightness,
};

static int s6e63j0x03_disabwe(stwuct dwm_panew *panew)
{
	stwuct s6e63j0x03 *ctx = panew_to_s6e63j0x03(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0)
		wetuwn wet;

	ctx->bw_dev->pwops.powew = FB_BWANK_NOWMAW;

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0)
		wetuwn wet;

	msweep(120);

	wetuwn 0;
}

static int s6e63j0x03_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct s6e63j0x03 *ctx = panew_to_s6e63j0x03(panew);
	int wet;

	wet = s6e63j0x03_powew_off(ctx);
	if (wet < 0)
		wetuwn wet;

	ctx->bw_dev->pwops.powew = FB_BWANK_POWEWDOWN;

	wetuwn 0;
}

static int s6e63j0x03_panew_init(stwuct s6e63j0x03 *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	wet = s6e63j0x03_enabwe_wv2_command(ctx);
	if (wet < 0)
		wetuwn wet;

	wet = s6e63j0x03_appwy_mtp_key(ctx, twue);
	if (wet < 0)
		wetuwn wet;

	/* set powch adjustment */
	wet = s6e63j0x03_dcs_wwite_seq_static(ctx, 0xf2, 0x1c, 0x28);
	if (wet < 0)
		wetuwn wet;

	/* set fwame fweq */
	wet = s6e63j0x03_dcs_wwite_seq_static(ctx, 0xb5, 0x00, 0x02, 0x00);
	if (wet < 0)
		wetuwn wet;

	/* set caset, paset */
	wet = mipi_dsi_dcs_set_cowumn_addwess(dsi, FIWST_COWUMN,
		defauwt_mode.hdispway - 1 + FIWST_COWUMN);
	if (wet < 0)
		wetuwn wet;

	wet = mipi_dsi_dcs_set_page_addwess(dsi, 0, defauwt_mode.vdispway - 1);
	if (wet < 0)
		wetuwn wet;

	/* set wtps timming 0, 1 */
	wet = s6e63j0x03_dcs_wwite_seq_static(ctx, 0xf8, 0x08, 0x08, 0x08, 0x17,
		0x00, 0x2a, 0x02, 0x26, 0x00, 0x00, 0x02, 0x00, 0x00);
	if (wet < 0)
		wetuwn wet;

	wet = s6e63j0x03_dcs_wwite_seq_static(ctx, 0xf7, 0x02);
	if (wet < 0)
		wetuwn wet;

	/* set pawam pos te_edge */
	wet = s6e63j0x03_dcs_wwite_seq_static(ctx, 0xb0, 0x01);
	if (wet < 0)
		wetuwn wet;

	/* set te wising edge */
	wet = s6e63j0x03_dcs_wwite_seq_static(ctx, 0xe2, 0x0f);
	if (wet < 0)
		wetuwn wet;

	/* set pawam pos defauwt */
	wet = s6e63j0x03_dcs_wwite_seq_static(ctx, 0xb0, 0x00);
	if (wet < 0)
		wetuwn wet;

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0)
		wetuwn wet;

	wet = s6e63j0x03_appwy_mtp_key(ctx, fawse);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int s6e63j0x03_pwepawe(stwuct dwm_panew *panew)
{
	stwuct s6e63j0x03 *ctx = panew_to_s6e63j0x03(panew);
	int wet;

	wet = s6e63j0x03_powew_on(ctx);
	if (wet < 0)
		wetuwn wet;

	wet = s6e63j0x03_panew_init(ctx);
	if (wet < 0)
		goto eww;

	ctx->bw_dev->pwops.powew = FB_BWANK_NOWMAW;

	wetuwn 0;

eww:
	s6e63j0x03_powew_off(ctx);
	wetuwn wet;
}

static int s6e63j0x03_enabwe(stwuct dwm_panew *panew)
{
	stwuct s6e63j0x03 *ctx = panew_to_s6e63j0x03(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	msweep(120);

	wet = s6e63j0x03_appwy_mtp_key(ctx, twue);
	if (wet < 0)
		wetuwn wet;

	/* set ewvss_cond */
	wet = s6e63j0x03_dcs_wwite_seq_static(ctx, 0xb1, 0x00, 0x09);
	if (wet < 0)
		wetuwn wet;

	/* set pos */
	wet = s6e63j0x03_dcs_wwite_seq_static(ctx,
		MIPI_DCS_SET_ADDWESS_MODE, 0x40);
	if (wet < 0)
		wetuwn wet;

	/* set defauwt white bwightness */
	wet = mipi_dsi_dcs_set_dispway_bwightness(dsi, 0x00ff);
	if (wet < 0)
		wetuwn wet;

	/* set white ctww */
	wet = s6e63j0x03_dcs_wwite_seq_static(ctx,
		MIPI_DCS_WWITE_CONTWOW_DISPWAY, 0x20);
	if (wet < 0)
		wetuwn wet;

	/* set acw off */
	wet = s6e63j0x03_dcs_wwite_seq_static(ctx,
		MIPI_DCS_WWITE_POWEW_SAVE, 0x00);
	if (wet < 0)
		wetuwn wet;

	wet = mipi_dsi_dcs_set_teaw_on(dsi, MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	if (wet < 0)
		wetuwn wet;

	wet = s6e63j0x03_appwy_mtp_key(ctx, fawse);
	if (wet < 0)
		wetuwn wet;

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0)
		wetuwn wet;

	ctx->bw_dev->pwops.powew = FB_BWANK_UNBWANK;

	wetuwn 0;
}

static int s6e63j0x03_get_modes(stwuct dwm_panew *panew,
				stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &defauwt_mode);
	if (!mode) {
		dev_eww(panew->dev, "faiwed to add mode %ux%u@%u\n",
			defauwt_mode.hdispway, defauwt_mode.vdispway,
			dwm_mode_vwefwesh(&defauwt_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = 29;
	connectow->dispway_info.height_mm = 29;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs s6e63j0x03_funcs = {
	.disabwe = s6e63j0x03_disabwe,
	.unpwepawe = s6e63j0x03_unpwepawe,
	.pwepawe = s6e63j0x03_pwepawe,
	.enabwe = s6e63j0x03_enabwe,
	.get_modes = s6e63j0x03_get_modes,
};

static int s6e63j0x03_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct s6e63j0x03 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(stwuct s6e63j0x03), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->wanes = 1;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO_NO_HFP |
		MIPI_DSI_MODE_VIDEO_NO_HBP | MIPI_DSI_MODE_VIDEO_NO_HSA;

	ctx->suppwies[0].suppwy = "vdd3";
	ctx->suppwies[1].suppwy = "vci";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ctx->suppwies),
				      ctx->suppwies);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get weguwatows\n");

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio),
				     "cannot get weset-gpio\n");

	dwm_panew_init(&ctx->panew, dev, &s6e63j0x03_funcs,
		       DWM_MODE_CONNECTOW_DSI);
	ctx->panew.pwepawe_pwev_fiwst = twue;

	ctx->bw_dev = backwight_device_wegistew("s6e63j0x03", dev, ctx,
						&s6e63j0x03_bw_ops, NUWW);
	if (IS_EWW(ctx->bw_dev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->bw_dev),
				     "faiwed to wegistew backwight device\n");

	ctx->bw_dev->pwops.max_bwightness = MAX_BWIGHTNESS;
	ctx->bw_dev->pwops.bwightness = DEFAUWT_BWIGHTNESS;
	ctx->bw_dev->pwops.powew = FB_BWANK_POWEWDOWN;

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0)
		goto wemove_panew;

	wetuwn wet;

wemove_panew:
	dwm_panew_wemove(&ctx->panew);
	backwight_device_unwegistew(ctx->bw_dev);

	wetuwn wet;
}

static void s6e63j0x03_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct s6e63j0x03 *ctx = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&ctx->panew);

	backwight_device_unwegistew(ctx->bw_dev);
}

static const stwuct of_device_id s6e63j0x03_of_match[] = {
	{ .compatibwe = "samsung,s6e63j0x03" },
	{ }
};
MODUWE_DEVICE_TABWE(of, s6e63j0x03_of_match);

static stwuct mipi_dsi_dwivew s6e63j0x03_dwivew = {
	.pwobe = s6e63j0x03_pwobe,
	.wemove = s6e63j0x03_wemove,
	.dwivew = {
		.name = "panew_samsung_s6e63j0x03",
		.of_match_tabwe = s6e63j0x03_of_match,
	},
};
moduwe_mipi_dsi_dwivew(s6e63j0x03_dwivew);

MODUWE_AUTHOW("Inki Dae <inki.dae@samsung.com>");
MODUWE_AUTHOW("Hoegeun Kwon <hoegeun.kwon@samsung.com>");
MODUWE_DESCWIPTION("MIPI-DSI based s6e63j0x03 AMOWED WCD Panew Dwivew");
MODUWE_WICENSE("GPW v2");
