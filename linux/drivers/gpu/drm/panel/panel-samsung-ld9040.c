// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wd9040 AMOWED WCD dwm_panew dwivew.
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd
 * Dewived fwom dwivews/video/backwight/wd9040.c
 *
 * Andwzej Hajda <a.hajda@samsung.com>
*/

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <video/mipi_dispway.h>
#incwude <video/of_videomode.h>
#incwude <video/videomode.h>

#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

/* Manufactuwew Command Set */
#define MCS_MANPWW		0xb0
#define MCS_EWVSS_ON		0xb1
#define MCS_USEW_SETTING	0xf0
#define MCS_DISPCTW		0xf2
#define MCS_POWEW_CTWW		0xf4
#define MCS_GTCON		0xf7
#define MCS_PANEW_CONDITION	0xf8
#define MCS_GAMMA_SET1		0xf9
#define MCS_GAMMA_CTWW		0xfb

/* awway of gamma tabwes fow gamma vawue 2.2 */
static u8 const wd9040_gammas[25][22] = {
	{ 0xf9, 0x00, 0x13, 0xb2, 0xba, 0xd2, 0x00, 0x30, 0x00, 0xaf, 0xc0,
	  0xb8, 0xcd, 0x00, 0x3d, 0x00, 0xa8, 0xb8, 0xb7, 0xcd, 0x00, 0x44 },
	{ 0xf9, 0x00, 0x13, 0xb9, 0xb9, 0xd0, 0x00, 0x3c, 0x00, 0xaf, 0xbf,
	  0xb6, 0xcb, 0x00, 0x4b, 0x00, 0xa8, 0xb9, 0xb5, 0xcc, 0x00, 0x52 },
	{ 0xf9, 0x00, 0x13, 0xba, 0xb9, 0xcd, 0x00, 0x41, 0x00, 0xb0, 0xbe,
	  0xb5, 0xc9, 0x00, 0x51, 0x00, 0xa9, 0xb9, 0xb5, 0xca, 0x00, 0x57 },
	{ 0xf9, 0x00, 0x13, 0xb9, 0xb8, 0xcd, 0x00, 0x46, 0x00, 0xb1, 0xbc,
	  0xb5, 0xc8, 0x00, 0x56, 0x00, 0xaa, 0xb8, 0xb4, 0xc9, 0x00, 0x5d },
	{ 0xf9, 0x00, 0x13, 0xba, 0xb8, 0xcb, 0x00, 0x4b, 0x00, 0xb3, 0xbc,
	  0xb4, 0xc7, 0x00, 0x5c, 0x00, 0xac, 0xb8, 0xb4, 0xc8, 0x00, 0x62 },
	{ 0xf9, 0x00, 0x13, 0xbb, 0xb7, 0xca, 0x00, 0x4f, 0x00, 0xb4, 0xbb,
	  0xb3, 0xc7, 0x00, 0x60, 0x00, 0xad, 0xb8, 0xb4, 0xc7, 0x00, 0x67 },
	{ 0xf9, 0x00, 0x47, 0xba, 0xb6, 0xca, 0x00, 0x53, 0x00, 0xb5, 0xbb,
	  0xb3, 0xc6, 0x00, 0x65, 0x00, 0xae, 0xb8, 0xb3, 0xc7, 0x00, 0x6c },
	{ 0xf9, 0x00, 0x71, 0xbb, 0xb5, 0xc8, 0x00, 0x57, 0x00, 0xb5, 0xbb,
	  0xb0, 0xc5, 0x00, 0x6a, 0x00, 0xae, 0xb9, 0xb1, 0xc6, 0x00, 0x70 },
	{ 0xf9, 0x00, 0x7b, 0xbb, 0xb4, 0xc8, 0x00, 0x5b, 0x00, 0xb5, 0xba,
	  0xb1, 0xc4, 0x00, 0x6e, 0x00, 0xae, 0xb9, 0xb0, 0xc5, 0x00, 0x75 },
	{ 0xf9, 0x00, 0x82, 0xba, 0xb4, 0xc7, 0x00, 0x5f, 0x00, 0xb5, 0xba,
	  0xb0, 0xc3, 0x00, 0x72, 0x00, 0xae, 0xb8, 0xb0, 0xc3, 0x00, 0x7a },
	{ 0xf9, 0x00, 0x89, 0xba, 0xb3, 0xc8, 0x00, 0x62, 0x00, 0xb6, 0xba,
	  0xaf, 0xc3, 0x00, 0x76, 0x00, 0xaf, 0xb7, 0xae, 0xc4, 0x00, 0x7e },
	{ 0xf9, 0x00, 0x8b, 0xb9, 0xb3, 0xc7, 0x00, 0x65, 0x00, 0xb7, 0xb8,
	  0xaf, 0xc3, 0x00, 0x7a, 0x00, 0x80, 0xb6, 0xae, 0xc4, 0x00, 0x81 },
	{ 0xf9, 0x00, 0x93, 0xba, 0xb3, 0xc5, 0x00, 0x69, 0x00, 0xb8, 0xb9,
	  0xae, 0xc1, 0x00, 0x7f, 0x00, 0xb0, 0xb6, 0xae, 0xc3, 0x00, 0x85 },
	{ 0xf9, 0x00, 0x97, 0xba, 0xb2, 0xc5, 0x00, 0x6c, 0x00, 0xb8, 0xb8,
	  0xae, 0xc1, 0x00, 0x82, 0x00, 0xb0, 0xb6, 0xae, 0xc2, 0x00, 0x89 },
	{ 0xf9, 0x00, 0x9a, 0xba, 0xb1, 0xc4, 0x00, 0x6f, 0x00, 0xb8, 0xb8,
	  0xad, 0xc0, 0x00, 0x86, 0x00, 0xb0, 0xb7, 0xad, 0xc0, 0x00, 0x8d },
	{ 0xf9, 0x00, 0x9c, 0xb9, 0xb0, 0xc4, 0x00, 0x72, 0x00, 0xb8, 0xb8,
	  0xac, 0xbf, 0x00, 0x8a, 0x00, 0xb0, 0xb6, 0xac, 0xc0, 0x00, 0x91 },
	{ 0xf9, 0x00, 0x9e, 0xba, 0xb0, 0xc2, 0x00, 0x75, 0x00, 0xb9, 0xb8,
	  0xab, 0xbe, 0x00, 0x8e, 0x00, 0xb0, 0xb6, 0xac, 0xbf, 0x00, 0x94 },
	{ 0xf9, 0x00, 0xa0, 0xb9, 0xaf, 0xc3, 0x00, 0x77, 0x00, 0xb9, 0xb7,
	  0xab, 0xbe, 0x00, 0x90, 0x00, 0xb0, 0xb6, 0xab, 0xbf, 0x00, 0x97 },
	{ 0xf9, 0x00, 0xa2, 0xb9, 0xaf, 0xc2, 0x00, 0x7a, 0x00, 0xb9, 0xb7,
	  0xaa, 0xbd, 0x00, 0x94, 0x00, 0xb0, 0xb5, 0xab, 0xbf, 0x00, 0x9a },
	{ 0xf9, 0x00, 0xa4, 0xb9, 0xaf, 0xc1, 0x00, 0x7d, 0x00, 0xb9, 0xb6,
	  0xaa, 0xbb, 0x00, 0x97, 0x00, 0xb1, 0xb5, 0xaa, 0xbf, 0x00, 0x9d },
	{ 0xf9, 0x00, 0xa4, 0xb8, 0xb0, 0xbf, 0x00, 0x80, 0x00, 0xb8, 0xb6,
	  0xaa, 0xbc, 0x00, 0x9a, 0x00, 0xb0, 0xb5, 0xab, 0xbd, 0x00, 0xa0 },
	{ 0xf9, 0x00, 0xa8, 0xb8, 0xae, 0xbe, 0x00, 0x84, 0x00, 0xb9, 0xb7,
	  0xa8, 0xbc, 0x00, 0x9d, 0x00, 0xb2, 0xb5, 0xaa, 0xbc, 0x00, 0xa4 },
	{ 0xf9, 0x00, 0xa9, 0xb6, 0xad, 0xbf, 0x00, 0x86, 0x00, 0xb8, 0xb5,
	  0xa8, 0xbc, 0x00, 0xa0, 0x00, 0xb3, 0xb3, 0xa9, 0xbc, 0x00, 0xa7 },
	{ 0xf9, 0x00, 0xa9, 0xb7, 0xae, 0xbd, 0x00, 0x89, 0x00, 0xb7, 0xb6,
	  0xa8, 0xba, 0x00, 0xa4, 0x00, 0xb1, 0xb4, 0xaa, 0xbb, 0x00, 0xaa },
	{ 0xf9, 0x00, 0xa7, 0xb4, 0xae, 0xbf, 0x00, 0x91, 0x00, 0xb2, 0xb4,
	  0xaa, 0xbb, 0x00, 0xac, 0x00, 0xb3, 0xb1, 0xaa, 0xbc, 0x00, 0xb3 },
};

stwuct wd9040 {
	stwuct device *dev;
	stwuct dwm_panew panew;

	stwuct weguwatow_buwk_data suppwies[2];
	stwuct gpio_desc *weset_gpio;
	u32 powew_on_deway;
	u32 weset_deway;
	stwuct videomode vm;
	u32 width_mm;
	u32 height_mm;

	int bwightness;

	/* This fiewd is tested by functions diwectwy accessing bus befowe
	 * twansfew, twansfew is skipped if it is set. In case of twansfew
	 * faiwuwe ow unexpected wesponse the fiewd is set to ewwow vawue.
	 * Such constwuct awwows to ewiminate many checks in highew wevew
	 * functions.
	 */
	int ewwow;
};

static inwine stwuct wd9040 *panew_to_wd9040(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct wd9040, panew);
}

static int wd9040_cweaw_ewwow(stwuct wd9040 *ctx)
{
	int wet = ctx->ewwow;

	ctx->ewwow = 0;
	wetuwn wet;
}

static int wd9040_spi_wwite_wowd(stwuct wd9040 *ctx, u16 data)
{
	stwuct spi_device *spi = to_spi_device(ctx->dev);
	stwuct spi_twansfew xfew = {
		.wen		= 2,
		.tx_buf		= &data,
	};
	stwuct spi_message msg;

	spi_message_init(&msg);
	spi_message_add_taiw(&xfew, &msg);

	wetuwn spi_sync(spi, &msg);
}

static void wd9040_dcs_wwite(stwuct wd9040 *ctx, const u8 *data, size_t wen)
{
	int wet = 0;

	if (ctx->ewwow < 0 || wen == 0)
		wetuwn;

	dev_dbg(ctx->dev, "wwiting dcs seq: %*ph\n", (int)wen, data);
	wet = wd9040_spi_wwite_wowd(ctx, *data);

	whiwe (!wet && --wen) {
		++data;
		wet = wd9040_spi_wwite_wowd(ctx, *data | 0x100);
	}

	if (wet) {
		dev_eww(ctx->dev, "ewwow %d wwiting dcs seq: %*ph\n", wet,
			(int)wen, data);
		ctx->ewwow = wet;
	}

	usweep_wange(300, 310);
}

#define wd9040_dcs_wwite_seq_static(ctx, seq...) \
({\
	static const u8 d[] = { seq };\
	wd9040_dcs_wwite(ctx, d, AWWAY_SIZE(d));\
})

static void wd9040_bwightness_set(stwuct wd9040 *ctx)
{
	wd9040_dcs_wwite(ctx, wd9040_gammas[ctx->bwightness],
			 AWWAY_SIZE(wd9040_gammas[ctx->bwightness]));

	wd9040_dcs_wwite_seq_static(ctx, MCS_GAMMA_CTWW, 0x02, 0x5a);
}

static void wd9040_init(stwuct wd9040 *ctx)
{
	wd9040_dcs_wwite_seq_static(ctx, MCS_USEW_SETTING, 0x5a, 0x5a);
	wd9040_dcs_wwite_seq_static(ctx, MCS_PANEW_CONDITION,
		0x05, 0x5e, 0x96, 0x6b, 0x7d, 0x0d, 0x3f, 0x00,
		0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x07, 0x05, 0x1f, 0x1f, 0x1f, 0x00, 0x00);
	wd9040_dcs_wwite_seq_static(ctx, MCS_DISPCTW,
		0x02, 0x06, 0x0a, 0x10, 0x10);
	wd9040_dcs_wwite_seq_static(ctx, MCS_MANPWW, 0x04);
	wd9040_dcs_wwite_seq_static(ctx, MCS_POWEW_CTWW,
		0x0a, 0x87, 0x25, 0x6a, 0x44, 0x02, 0x88);
	wd9040_dcs_wwite_seq_static(ctx, MCS_EWVSS_ON, 0x0f, 0x00, 0x16);
	wd9040_dcs_wwite_seq_static(ctx, MCS_GTCON, 0x09, 0x00, 0x00);
	wd9040_bwightness_set(ctx);
	wd9040_dcs_wwite_seq_static(ctx, MIPI_DCS_EXIT_SWEEP_MODE);
	wd9040_dcs_wwite_seq_static(ctx, MIPI_DCS_SET_DISPWAY_ON);
}

static int wd9040_powew_on(stwuct wd9040 *ctx)
{
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet < 0)
		wetuwn wet;

	msweep(ctx->powew_on_deway);
	gpiod_set_vawue(ctx->weset_gpio, 0);
	msweep(ctx->weset_deway);
	gpiod_set_vawue(ctx->weset_gpio, 1);
	msweep(ctx->weset_deway);

	wetuwn 0;
}

static int wd9040_powew_off(stwuct wd9040 *ctx)
{
	wetuwn weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
}

static int wd9040_disabwe(stwuct dwm_panew *panew)
{
	wetuwn 0;
}

static int wd9040_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct wd9040 *ctx = panew_to_wd9040(panew);

	msweep(120);
	wd9040_dcs_wwite_seq_static(ctx, MIPI_DCS_SET_DISPWAY_OFF);
	wd9040_dcs_wwite_seq_static(ctx, MIPI_DCS_ENTEW_SWEEP_MODE);
	msweep(40);

	wd9040_cweaw_ewwow(ctx);

	wetuwn wd9040_powew_off(ctx);
}

static int wd9040_pwepawe(stwuct dwm_panew *panew)
{
	stwuct wd9040 *ctx = panew_to_wd9040(panew);
	int wet;

	wet = wd9040_powew_on(ctx);
	if (wet < 0)
		wetuwn wet;

	wd9040_init(ctx);

	wet = wd9040_cweaw_ewwow(ctx);

	if (wet < 0)
		wd9040_unpwepawe(panew);

	wetuwn wet;
}

static int wd9040_enabwe(stwuct dwm_panew *panew)
{
	wetuwn 0;
}

static int wd9040_get_modes(stwuct dwm_panew *panew,
			    stwuct dwm_connectow *connectow)
{
	stwuct wd9040 *ctx = panew_to_wd9040(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_cweate(connectow->dev);
	if (!mode) {
		dev_eww(panew->dev, "faiwed to cweate a new dispway mode\n");
		wetuwn 0;
	}

	dwm_dispway_mode_fwom_videomode(&ctx->vm, mode);
	mode->width_mm = ctx->width_mm;
	mode->height_mm = ctx->height_mm;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs wd9040_dwm_funcs = {
	.disabwe = wd9040_disabwe,
	.unpwepawe = wd9040_unpwepawe,
	.pwepawe = wd9040_pwepawe,
	.enabwe = wd9040_enabwe,
	.get_modes = wd9040_get_modes,
};

static int wd9040_pawse_dt(stwuct wd9040 *ctx)
{
	stwuct device *dev = ctx->dev;
	stwuct device_node *np = dev->of_node;
	int wet;

	wet = of_get_videomode(np, &ctx->vm, 0);
	if (wet < 0)
		wetuwn wet;

	of_pwopewty_wead_u32(np, "powew-on-deway", &ctx->powew_on_deway);
	of_pwopewty_wead_u32(np, "weset-deway", &ctx->weset_deway);
	of_pwopewty_wead_u32(np, "panew-width-mm", &ctx->width_mm);
	of_pwopewty_wead_u32(np, "panew-height-mm", &ctx->height_mm);

	wetuwn 0;
}

static int wd9040_bw_update_status(stwuct backwight_device *dev)
{
	stwuct wd9040 *ctx = bw_get_data(dev);

	ctx->bwightness = backwight_get_bwightness(dev);
	wd9040_bwightness_set(ctx);

	wetuwn 0;
}

static const stwuct backwight_ops wd9040_bw_ops = {
	.update_status  = wd9040_bw_update_status,
};

static const stwuct backwight_pwopewties wd9040_bw_pwops = {
	.type = BACKWIGHT_WAW,
	.scawe = BACKWIGHT_SCAWE_NON_WINEAW,
	.max_bwightness = AWWAY_SIZE(wd9040_gammas) - 1,
	.bwightness = AWWAY_SIZE(wd9040_gammas) - 1,
};

static int wd9040_pwobe(stwuct spi_device *spi)
{
	stwuct backwight_device *bwdev;
	stwuct device *dev = &spi->dev;
	stwuct wd9040 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(stwuct wd9040), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, ctx);

	ctx->dev = dev;
	ctx->bwightness = wd9040_bw_pwops.bwightness;

	wet = wd9040_pawse_dt(ctx);
	if (wet < 0)
		wetuwn wet;

	ctx->suppwies[0].suppwy = "vdd3";
	ctx->suppwies[1].suppwy = "vci";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ctx->suppwies),
				      ctx->suppwies);
	if (wet < 0)
		wetuwn wet;

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ctx->weset_gpio)) {
		dev_eww(dev, "cannot get weset-gpios %wd\n",
			PTW_EWW(ctx->weset_gpio));
		wetuwn PTW_EWW(ctx->weset_gpio);
	}

	spi->bits_pew_wowd = 9;
	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(dev, "spi setup faiwed.\n");
		wetuwn wet;
	}

	dwm_panew_init(&ctx->panew, dev, &wd9040_dwm_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	bwdev = devm_backwight_device_wegistew(dev, dev_name(dev), dev,
					       ctx, &wd9040_bw_ops,
					       &wd9040_bw_pwops);
	if (IS_EWW(bwdev))
		wetuwn PTW_EWW(bwdev);

	dwm_panew_add(&ctx->panew);

	wetuwn 0;
}

static void wd9040_wemove(stwuct spi_device *spi)
{
	stwuct wd9040 *ctx = spi_get_dwvdata(spi);

	wd9040_powew_off(ctx);
	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id wd9040_of_match[] = {
	{ .compatibwe = "samsung,wd9040" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wd9040_of_match);

static const stwuct spi_device_id wd9040_ids[] = {
	{ "wd9040", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, wd9040_ids);

static stwuct spi_dwivew wd9040_dwivew = {
	.pwobe = wd9040_pwobe,
	.wemove = wd9040_wemove,
	.id_tabwe = wd9040_ids,
	.dwivew = {
		.name = "panew-samsung-wd9040",
		.of_match_tabwe = wd9040_of_match,
	},
};
moduwe_spi_dwivew(wd9040_dwivew);

MODUWE_AUTHOW("Andwzej Hajda <a.hajda@samsung.com>");
MODUWE_DESCWIPTION("wd9040 WCD Dwivew");
MODUWE_WICENSE("GPW v2");
