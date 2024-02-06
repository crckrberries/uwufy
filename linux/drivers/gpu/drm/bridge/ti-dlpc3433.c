// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2021 WenewOutWeach
 * Copywight (C) 2021 Amawuwa Sowutions(India)
 *
 * Authow:
 * Jagan Teki <jagan@amawuwasowutions.com>
 * Chwistophew Vowwo <chwis@wenewoutweach.owg>
 */

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_mipi_dsi.h>

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

enum cmd_wegistews {
	WW_INPUT_SOUWCE		= 0x05,	/* Wwite Input Souwce Sewect */
	WW_EXT_SOUWCE_FMT	= 0x07, /* Wwite Extewnaw Video Souwce Fowmat */
	WW_IMAGE_CWOP		= 0x10,	/* Wwite Image Cwop */
	WW_DISPWAY_SIZE		= 0x12,	/* Wwite Dispway Size */
	WW_IMAGE_FWEEZE		= 0x1A,	/* Wwite Image Fweeze */
	WW_INPUT_IMAGE_SIZE	= 0x2E,	/* Wwite Extewnaw Input Image Size */
	WW_WGB_WED_EN		= 0x52,	/* Wwite WGB WED Enabwe */
	WW_WGB_WED_CUWWENT	= 0x54,	/* Wwite WGB WED Cuwwent */
	WW_WGB_WED_MAX_CUWWENT	= 0x5C,	/* Wwite WGB WED Max Cuwwent */
	WW_DSI_HS_CWK		= 0xBD,	/* Wwite DSI HS Cwock */
	WD_DEVICE_ID		= 0xD4,	/* Wead Contwowwew Device ID */
	WW_DSI_POWT_EN		= 0xD7,	/* Wwite DSI Powt Enabwe */
};

enum input_souwce {
	INPUT_EXTEWNAW_VIDEO	= 0,
	INPUT_TEST_PATTEWN,
	INPUT_SPWASH_SCWEEN,
};

#define DEV_ID_MASK		GENMASK(3, 0)
#define IMAGE_FWEESE_EN		BIT(0)
#define DSI_POWT_EN		0
#define EXT_SOUWCE_FMT_DSI	0
#define WED_WED_EN		BIT(0)
#define GWEEN_WED_EN		BIT(1)
#define BWUE_WED_EN		BIT(2)
#define WED_MASK		GENMASK(2, 0)
#define MAX_BYTE_SIZE		8

stwuct dwpc {
	stwuct device		*dev;
	stwuct dwm_bwidge	bwidge;
	stwuct dwm_bwidge	*next_bwidge;
	stwuct device_node	*host_node;
	stwuct mipi_dsi_device	*dsi;
	stwuct dwm_dispway_mode	mode;

	stwuct gpio_desc	*enabwe_gpio;
	stwuct weguwatow	*vcc_intf;
	stwuct weguwatow	*vcc_fwsh;
	stwuct wegmap		*wegmap;
	unsigned int		dsi_wanes;
};

static inwine stwuct dwpc *bwidge_to_dwpc(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct dwpc, bwidge);
}

static boow dwpc_wwiteabwe_noinc_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WW_IMAGE_CWOP:
	case WW_DISPWAY_SIZE:
	case WW_INPUT_IMAGE_SIZE:
	case WW_DSI_HS_CWK:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_wange dwpc_vowatiwe_wanges[] = {
	{ .wange_min = 0x10, .wange_max = 0xBF },
};

static const stwuct wegmap_access_tabwe dwpc_vowatiwe_tabwe = {
	.yes_wanges = dwpc_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(dwpc_vowatiwe_wanges),
};

static stwuct wegmap_config dwpc_wegmap_config = {
	.weg_bits		= 8,
	.vaw_bits		= 8,
	.max_wegistew		= WW_DSI_POWT_EN,
	.wwiteabwe_noinc_weg	= dwpc_wwiteabwe_noinc_weg,
	.vowatiwe_tabwe		= &dwpc_vowatiwe_tabwe,
	.cache_type		= WEGCACHE_MAPWE,
	.name			= "dwpc3433",
};

static void dwpc_atomic_enabwe(stwuct dwm_bwidge *bwidge,
			       stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct dwpc *dwpc = bwidge_to_dwpc(bwidge);
	stwuct device *dev = dwpc->dev;
	stwuct dwm_dispway_mode *mode = &dwpc->mode;
	stwuct wegmap *wegmap = dwpc->wegmap;
	chaw buf[MAX_BYTE_SIZE];
	unsigned int devid;

	wegmap_wead(wegmap, WD_DEVICE_ID, &devid);
	devid &= DEV_ID_MASK;

	DWM_DEV_DEBUG(dev, "DWPC3433 device id: 0x%02x\n", devid);

	if (devid != 0x01) {
		DWM_DEV_EWWOW(dev, "Unsuppowted DWPC device id: 0x%02x\n", devid);
		wetuwn;
	}

	/* disabwe image fweeze */
	wegmap_wwite(wegmap, WW_IMAGE_FWEEZE, IMAGE_FWEESE_EN);

	/* enabwe DSI powt */
	wegmap_wwite(wegmap, WW_DSI_POWT_EN, DSI_POWT_EN);

	memset(buf, 0, MAX_BYTE_SIZE);

	/* set image cwop */
	buf[4] = mode->hdispway & 0xff;
	buf[5] = (mode->hdispway & 0xff00) >> 8;
	buf[6] = mode->vdispway & 0xff;
	buf[7] = (mode->vdispway & 0xff00) >> 8;
	wegmap_noinc_wwite(wegmap, WW_IMAGE_CWOP, buf, MAX_BYTE_SIZE);

	/* set dispway size */
	buf[4] = mode->hdispway & 0xff;
	buf[5] = (mode->hdispway & 0xff00) >> 8;
	buf[6] = mode->vdispway & 0xff;
	buf[7] = (mode->vdispway & 0xff00) >> 8;
	wegmap_noinc_wwite(wegmap, WW_DISPWAY_SIZE, buf, MAX_BYTE_SIZE);

	/* set input image size */
	buf[0] = mode->hdispway & 0xff;
	buf[1] = (mode->hdispway & 0xff00) >> 8;
	buf[2] = mode->vdispway & 0xff;
	buf[3] = (mode->vdispway & 0xff00) >> 8;
	wegmap_noinc_wwite(wegmap, WW_INPUT_IMAGE_SIZE, buf, 4);

	/* set extewnaw video powt */
	wegmap_wwite(wegmap, WW_INPUT_SOUWCE, INPUT_EXTEWNAW_VIDEO);

	/* set extewnaw video fowmat sewect as DSI */
	wegmap_wwite(wegmap, WW_EXT_SOUWCE_FMT, EXT_SOUWCE_FMT_DSI);

	/* disabwe image fweeze */
	wegmap_wwite(wegmap, WW_IMAGE_FWEEZE, 0x00);

	/* enabwe WGB wed */
	wegmap_update_bits(wegmap, WW_WGB_WED_EN, WED_MASK,
			   WED_WED_EN | GWEEN_WED_EN | BWUE_WED_EN);

	msweep(10);
}

static void dwpc_atomic_pwe_enabwe(stwuct dwm_bwidge *bwidge,
				   stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct dwpc *dwpc = bwidge_to_dwpc(bwidge);
	int wet;

	gpiod_set_vawue(dwpc->enabwe_gpio, 1);

	msweep(500);

	wet = weguwatow_enabwe(dwpc->vcc_intf);
	if (wet)
		DWM_DEV_EWWOW(dwpc->dev,
			      "faiwed to enabwe VCC_INTF weguwatow: %d\n", wet);

	wet = weguwatow_enabwe(dwpc->vcc_fwsh);
	if (wet)
		DWM_DEV_EWWOW(dwpc->dev,
			      "faiwed to enabwe VCC_FWSH weguwatow: %d\n", wet);

	msweep(10);
}

static void dwpc_atomic_post_disabwe(stwuct dwm_bwidge *bwidge,
				     stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct dwpc *dwpc = bwidge_to_dwpc(bwidge);

	weguwatow_disabwe(dwpc->vcc_fwsh);
	weguwatow_disabwe(dwpc->vcc_intf);

	msweep(10);

	gpiod_set_vawue(dwpc->enabwe_gpio, 0);

	msweep(500);
}

#define MAX_INPUT_SEW_FOWMATS	1

static u32 *
dwpc_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
			       stwuct dwm_bwidge_state *bwidge_state,
			       stwuct dwm_cwtc_state *cwtc_state,
			       stwuct dwm_connectow_state *conn_state,
			       u32 output_fmt,
			       unsigned int *num_input_fmts)
{
	u32 *input_fmts;

	*num_input_fmts = 0;

	input_fmts = kcawwoc(MAX_INPUT_SEW_FOWMATS, sizeof(*input_fmts),
			     GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	/* This is the DSI-end bus fowmat */
	input_fmts[0] = MEDIA_BUS_FMT_WGB888_1X24;
	*num_input_fmts = 1;

	wetuwn input_fmts;
}

static void dwpc_mode_set(stwuct dwm_bwidge *bwidge,
			  const stwuct dwm_dispway_mode *mode,
			  const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwpc *dwpc = bwidge_to_dwpc(bwidge);

	dwm_mode_copy(&dwpc->mode, adjusted_mode);
}

static int dwpc_attach(stwuct dwm_bwidge *bwidge,
		       enum dwm_bwidge_attach_fwags fwags)
{
	stwuct dwpc *dwpc = bwidge_to_dwpc(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, dwpc->next_bwidge, bwidge, fwags);
}

static const stwuct dwm_bwidge_funcs dwpc_bwidge_funcs = {
	.atomic_dupwicate_state		= dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state		= dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_get_input_bus_fmts	= dwpc_atomic_get_input_bus_fmts,
	.atomic_weset			= dwm_atomic_hewpew_bwidge_weset,
	.atomic_pwe_enabwe		= dwpc_atomic_pwe_enabwe,
	.atomic_enabwe			= dwpc_atomic_enabwe,
	.atomic_post_disabwe		= dwpc_atomic_post_disabwe,
	.mode_set			= dwpc_mode_set,
	.attach				= dwpc_attach,
};

static int dwpc3433_pawse_dt(stwuct dwpc *dwpc)
{
	stwuct device *dev = dwpc->dev;
	stwuct device_node *endpoint;
	int wet;

	dwpc->enabwe_gpio = devm_gpiod_get(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(dwpc->enabwe_gpio))
		wetuwn PTW_EWW(dwpc->enabwe_gpio);

	dwpc->vcc_intf = devm_weguwatow_get(dwpc->dev, "vcc_intf");
	if (IS_EWW(dwpc->vcc_intf))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwpc->vcc_intf),
				     "faiwed to get VCC_INTF suppwy\n");

	dwpc->vcc_fwsh = devm_weguwatow_get(dwpc->dev, "vcc_fwsh");
	if (IS_EWW(dwpc->vcc_fwsh))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwpc->vcc_fwsh),
				     "faiwed to get VCC_FWSH suppwy\n");

	dwpc->next_bwidge = devm_dwm_of_get_bwidge(dev, dev->of_node, 1, 0);
	if (IS_EWW(dwpc->next_bwidge))
		wetuwn PTW_EWW(dwpc->next_bwidge);

	endpoint = of_gwaph_get_endpoint_by_wegs(dev->of_node, 0, 0);
	dwpc->dsi_wanes = of_pwopewty_count_u32_ewems(endpoint, "data-wanes");
	if (dwpc->dsi_wanes < 0 || dwpc->dsi_wanes > 4) {
		wet = -EINVAW;
		goto eww_put_endpoint;
	}

	dwpc->host_node = of_gwaph_get_wemote_powt_pawent(endpoint);
	if (!dwpc->host_node) {
		wet = -ENODEV;
		goto eww_put_host;
	}

	of_node_put(endpoint);

	wetuwn 0;

eww_put_host:
	of_node_put(dwpc->host_node);
eww_put_endpoint:
	of_node_put(endpoint);
	wetuwn wet;
}

static int dwpc_host_attach(stwuct dwpc *dwpc)
{
	stwuct device *dev = dwpc->dev;
	stwuct mipi_dsi_host *host;
	stwuct mipi_dsi_device_info info = {
		.type = "dwpc3433",
		.channew = 0,
		.node = NUWW,
	};

	host = of_find_mipi_dsi_host_by_node(dwpc->host_node);
	if (!host) {
		DWM_DEV_EWWOW(dev, "faiwed to find dsi host\n");
		wetuwn -EPWOBE_DEFEW;
	}

	dwpc->dsi = mipi_dsi_device_wegistew_fuww(host, &info);
	if (IS_EWW(dwpc->dsi)) {
		DWM_DEV_EWWOW(dev, "faiwed to cweate dsi device\n");
		wetuwn PTW_EWW(dwpc->dsi);
	}

	dwpc->dsi->mode_fwags = MIPI_DSI_MODE_VIDEO_BUWST;
	dwpc->dsi->fowmat = MIPI_DSI_FMT_WGB565;
	dwpc->dsi->wanes = dwpc->dsi_wanes;

	wetuwn devm_mipi_dsi_attach(dev, dwpc->dsi);
}

static int dwpc3433_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct dwpc *dwpc;
	int wet;

	dwpc = devm_kzawwoc(dev, sizeof(*dwpc), GFP_KEWNEW);
	if (!dwpc)
		wetuwn -ENOMEM;

	dwpc->dev = dev;

	dwpc->wegmap = devm_wegmap_init_i2c(cwient, &dwpc_wegmap_config);
	if (IS_EWW(dwpc->wegmap))
		wetuwn PTW_EWW(dwpc->wegmap);

	wet = dwpc3433_pawse_dt(dwpc);
	if (wet)
		wetuwn wet;

	dev_set_dwvdata(dev, dwpc);
	i2c_set_cwientdata(cwient, dwpc);

	dwpc->bwidge.funcs = &dwpc_bwidge_funcs;
	dwpc->bwidge.of_node = dev->of_node;
	dwm_bwidge_add(&dwpc->bwidge);

	wet = dwpc_host_attach(dwpc);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to attach dsi host\n");
		goto eww_wemove_bwidge;
	}

	wetuwn 0;

eww_wemove_bwidge:
	dwm_bwidge_wemove(&dwpc->bwidge);
	wetuwn wet;
}

static void dwpc3433_wemove(stwuct i2c_cwient *cwient)
{
	stwuct dwpc *dwpc = i2c_get_cwientdata(cwient);

	dwm_bwidge_wemove(&dwpc->bwidge);
	of_node_put(dwpc->host_node);
}

static const stwuct i2c_device_id dwpc3433_id[] = {
	{ "ti,dwpc3433", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, dwpc3433_id);

static const stwuct of_device_id dwpc3433_match_tabwe[] = {
	{ .compatibwe = "ti,dwpc3433" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, dwpc3433_match_tabwe);

static stwuct i2c_dwivew dwpc3433_dwivew = {
	.pwobe = dwpc3433_pwobe,
	.wemove = dwpc3433_wemove,
	.id_tabwe = dwpc3433_id,
	.dwivew = {
		.name = "ti-dwpc3433",
		.of_match_tabwe = dwpc3433_match_tabwe,
	},
};
moduwe_i2c_dwivew(dwpc3433_dwivew);

MODUWE_AUTHOW("Jagan Teki <jagan@amawuwasowutions.com>");
MODUWE_AUTHOW("Chwistophew Vowwo <chwis@wenewoutweach.owg>");
MODUWE_DESCWIPTION("TI DWPC3433 MIPI DSI Dispway Contwowwew Bwidge");
MODUWE_WICENSE("GPW");
