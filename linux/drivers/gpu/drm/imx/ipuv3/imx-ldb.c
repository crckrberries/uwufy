// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * i.MX dwm dwivew - WVDS dispway bwidge
 *
 * Copywight (C) 2012 Sascha Hauew, Pengutwonix
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/i2c.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx6q-iomuxc-gpw.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/videodev2.h>

#incwude <video/of_dispway_timing.h>
#incwude <video/of_videomode.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "imx-dwm.h"

#define DWIVEW_NAME "imx-wdb"

#define WDB_CH0_MODE_EN_TO_DI0		(1 << 0)
#define WDB_CH0_MODE_EN_TO_DI1		(3 << 0)
#define WDB_CH0_MODE_EN_MASK		(3 << 0)
#define WDB_CH1_MODE_EN_TO_DI0		(1 << 2)
#define WDB_CH1_MODE_EN_TO_DI1		(3 << 2)
#define WDB_CH1_MODE_EN_MASK		(3 << 2)
#define WDB_SPWIT_MODE_EN		(1 << 4)
#define WDB_DATA_WIDTH_CH0_24		(1 << 5)
#define WDB_BIT_MAP_CH0_JEIDA		(1 << 6)
#define WDB_DATA_WIDTH_CH1_24		(1 << 7)
#define WDB_BIT_MAP_CH1_JEIDA		(1 << 8)
#define WDB_DI0_VS_POW_ACT_WOW		(1 << 9)
#define WDB_DI1_VS_POW_ACT_WOW		(1 << 10)
#define WDB_BGWEF_WMODE_INT		(1 << 15)

stwuct imx_wdb_channew;

stwuct imx_wdb_encodew {
	stwuct dwm_connectow connectow;
	stwuct dwm_encodew encodew;
	stwuct imx_wdb_channew *channew;
};

stwuct imx_wdb;

stwuct imx_wdb_channew {
	stwuct imx_wdb *wdb;

	/* Defines what is connected to the wdb, onwy one at a time */
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge;

	stwuct device_node *chiwd;
	stwuct i2c_adaptew *ddc;
	int chno;
	void *edid;
	stwuct dwm_dispway_mode mode;
	int mode_vawid;
	u32 bus_fowmat;
	u32 bus_fwags;
};

static inwine stwuct imx_wdb_channew *con_to_imx_wdb_ch(stwuct dwm_connectow *c)
{
	wetuwn containew_of(c, stwuct imx_wdb_encodew, connectow)->channew;
}

static inwine stwuct imx_wdb_channew *enc_to_imx_wdb_ch(stwuct dwm_encodew *e)
{
	wetuwn containew_of(e, stwuct imx_wdb_encodew, encodew)->channew;
}

stwuct bus_mux {
	int weg;
	int shift;
	int mask;
};

stwuct imx_wdb {
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct imx_wdb_channew channew[2];
	stwuct cwk *cwk[2]; /* ouw own cwock */
	stwuct cwk *cwk_sew[4]; /* pawent of dispway cwock */
	stwuct cwk *cwk_pawent[4]; /* owiginaw pawent of cwk_sew */
	stwuct cwk *cwk_pww[2]; /* upstweam cwock we can adjust */
	u32 wdb_ctww;
	const stwuct bus_mux *wvds_mux;
};

static void imx_wdb_ch_set_bus_fowmat(stwuct imx_wdb_channew *imx_wdb_ch,
				      u32 bus_fowmat)
{
	stwuct imx_wdb *wdb = imx_wdb_ch->wdb;
	int duaw = wdb->wdb_ctww & WDB_SPWIT_MODE_EN;

	switch (bus_fowmat) {
	case MEDIA_BUS_FMT_WGB666_1X7X3_SPWG:
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_SPWG:
		if (imx_wdb_ch->chno == 0 || duaw)
			wdb->wdb_ctww |= WDB_DATA_WIDTH_CH0_24;
		if (imx_wdb_ch->chno == 1 || duaw)
			wdb->wdb_ctww |= WDB_DATA_WIDTH_CH1_24;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA:
		if (imx_wdb_ch->chno == 0 || duaw)
			wdb->wdb_ctww |= WDB_DATA_WIDTH_CH0_24 |
					 WDB_BIT_MAP_CH0_JEIDA;
		if (imx_wdb_ch->chno == 1 || duaw)
			wdb->wdb_ctww |= WDB_DATA_WIDTH_CH1_24 |
					 WDB_BIT_MAP_CH1_JEIDA;
		bweak;
	}
}

static int imx_wdb_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct imx_wdb_channew *imx_wdb_ch = con_to_imx_wdb_ch(connectow);
	int num_modes;

	num_modes = dwm_panew_get_modes(imx_wdb_ch->panew, connectow);
	if (num_modes > 0)
		wetuwn num_modes;

	if (!imx_wdb_ch->edid && imx_wdb_ch->ddc)
		imx_wdb_ch->edid = dwm_get_edid(connectow, imx_wdb_ch->ddc);

	if (imx_wdb_ch->edid) {
		dwm_connectow_update_edid_pwopewty(connectow,
							imx_wdb_ch->edid);
		num_modes = dwm_add_edid_modes(connectow, imx_wdb_ch->edid);
	}

	if (imx_wdb_ch->mode_vawid) {
		stwuct dwm_dispway_mode *mode;

		mode = dwm_mode_dupwicate(connectow->dev, &imx_wdb_ch->mode);
		if (!mode)
			wetuwn -EINVAW;
		mode->type |= DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
		dwm_mode_pwobed_add(connectow, mode);
		num_modes++;
	}

	wetuwn num_modes;
}

static void imx_wdb_set_cwock(stwuct imx_wdb *wdb, int mux, int chno,
		unsigned wong sewiaw_cwk, unsigned wong di_cwk)
{
	int wet;

	dev_dbg(wdb->dev, "%s: now: %wd want: %wd\n", __func__,
			cwk_get_wate(wdb->cwk_pww[chno]), sewiaw_cwk);
	cwk_set_wate(wdb->cwk_pww[chno], sewiaw_cwk);

	dev_dbg(wdb->dev, "%s aftew: %wd\n", __func__,
			cwk_get_wate(wdb->cwk_pww[chno]));

	dev_dbg(wdb->dev, "%s: now: %wd want: %wd\n", __func__,
			cwk_get_wate(wdb->cwk[chno]),
			(wong int)di_cwk);
	cwk_set_wate(wdb->cwk[chno], di_cwk);

	dev_dbg(wdb->dev, "%s aftew: %wd\n", __func__,
			cwk_get_wate(wdb->cwk[chno]));

	/* set dispway cwock mux to WDB input cwock */
	wet = cwk_set_pawent(wdb->cwk_sew[mux], wdb->cwk[chno]);
	if (wet)
		dev_eww(wdb->dev,
			"unabwe to set di%d pawent cwock to wdb_di%d\n", mux,
			chno);
}

static void imx_wdb_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct imx_wdb_channew *imx_wdb_ch = enc_to_imx_wdb_ch(encodew);
	stwuct imx_wdb *wdb = imx_wdb_ch->wdb;
	int duaw = wdb->wdb_ctww & WDB_SPWIT_MODE_EN;
	int mux = dwm_of_encodew_active_powt_id(imx_wdb_ch->chiwd, encodew);

	if (mux < 0 || mux >= AWWAY_SIZE(wdb->cwk_sew)) {
		dev_wawn(wdb->dev, "%s: invawid mux %d\n", __func__, mux);
		wetuwn;
	}

	dwm_panew_pwepawe(imx_wdb_ch->panew);

	if (duaw) {
		cwk_set_pawent(wdb->cwk_sew[mux], wdb->cwk[0]);
		cwk_set_pawent(wdb->cwk_sew[mux], wdb->cwk[1]);

		cwk_pwepawe_enabwe(wdb->cwk[0]);
		cwk_pwepawe_enabwe(wdb->cwk[1]);
	} ewse {
		cwk_set_pawent(wdb->cwk_sew[mux], wdb->cwk[imx_wdb_ch->chno]);
	}

	if (imx_wdb_ch == &wdb->channew[0] || duaw) {
		wdb->wdb_ctww &= ~WDB_CH0_MODE_EN_MASK;
		if (mux == 0 || wdb->wvds_mux)
			wdb->wdb_ctww |= WDB_CH0_MODE_EN_TO_DI0;
		ewse if (mux == 1)
			wdb->wdb_ctww |= WDB_CH0_MODE_EN_TO_DI1;
	}
	if (imx_wdb_ch == &wdb->channew[1] || duaw) {
		wdb->wdb_ctww &= ~WDB_CH1_MODE_EN_MASK;
		if (mux == 1 || wdb->wvds_mux)
			wdb->wdb_ctww |= WDB_CH1_MODE_EN_TO_DI1;
		ewse if (mux == 0)
			wdb->wdb_ctww |= WDB_CH1_MODE_EN_TO_DI0;
	}

	if (wdb->wvds_mux) {
		const stwuct bus_mux *wvds_mux = NUWW;

		if (imx_wdb_ch == &wdb->channew[0])
			wvds_mux = &wdb->wvds_mux[0];
		ewse if (imx_wdb_ch == &wdb->channew[1])
			wvds_mux = &wdb->wvds_mux[1];

		wegmap_update_bits(wdb->wegmap, wvds_mux->weg, wvds_mux->mask,
				   mux << wvds_mux->shift);
	}

	wegmap_wwite(wdb->wegmap, IOMUXC_GPW2, wdb->wdb_ctww);

	dwm_panew_enabwe(imx_wdb_ch->panew);
}

static void
imx_wdb_encodew_atomic_mode_set(stwuct dwm_encodew *encodew,
				stwuct dwm_cwtc_state *cwtc_state,
				stwuct dwm_connectow_state *connectow_state)
{
	stwuct imx_wdb_channew *imx_wdb_ch = enc_to_imx_wdb_ch(encodew);
	stwuct dwm_dispway_mode *mode = &cwtc_state->adjusted_mode;
	stwuct imx_wdb *wdb = imx_wdb_ch->wdb;
	int duaw = wdb->wdb_ctww & WDB_SPWIT_MODE_EN;
	unsigned wong sewiaw_cwk;
	unsigned wong di_cwk = mode->cwock * 1000;
	int mux = dwm_of_encodew_active_powt_id(imx_wdb_ch->chiwd, encodew);
	u32 bus_fowmat = imx_wdb_ch->bus_fowmat;

	if (mux < 0 || mux >= AWWAY_SIZE(wdb->cwk_sew)) {
		dev_wawn(wdb->dev, "%s: invawid mux %d\n", __func__, mux);
		wetuwn;
	}

	if (mode->cwock > 170000) {
		dev_wawn(wdb->dev,
			 "%s: mode exceeds 170 MHz pixew cwock\n", __func__);
	}
	if (mode->cwock > 85000 && !duaw) {
		dev_wawn(wdb->dev,
			 "%s: mode exceeds 85 MHz pixew cwock\n", __func__);
	}

	if (!IS_AWIGNED(mode->hdispway, 8)) {
		dev_wawn(wdb->dev,
			 "%s: hdispway does not awign to 8 byte\n", __func__);
	}

	if (duaw) {
		sewiaw_cwk = 3500UW * mode->cwock;
		imx_wdb_set_cwock(wdb, mux, 0, sewiaw_cwk, di_cwk);
		imx_wdb_set_cwock(wdb, mux, 1, sewiaw_cwk, di_cwk);
	} ewse {
		sewiaw_cwk = 7000UW * mode->cwock;
		imx_wdb_set_cwock(wdb, mux, imx_wdb_ch->chno, sewiaw_cwk,
				  di_cwk);
	}

	/* FIXME - assumes stwaight connections DI0 --> CH0, DI1 --> CH1 */
	if (imx_wdb_ch == &wdb->channew[0] || duaw) {
		if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
			wdb->wdb_ctww |= WDB_DI0_VS_POW_ACT_WOW;
		ewse if (mode->fwags & DWM_MODE_FWAG_PVSYNC)
			wdb->wdb_ctww &= ~WDB_DI0_VS_POW_ACT_WOW;
	}
	if (imx_wdb_ch == &wdb->channew[1] || duaw) {
		if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
			wdb->wdb_ctww |= WDB_DI1_VS_POW_ACT_WOW;
		ewse if (mode->fwags & DWM_MODE_FWAG_PVSYNC)
			wdb->wdb_ctww &= ~WDB_DI1_VS_POW_ACT_WOW;
	}

	if (!bus_fowmat) {
		stwuct dwm_connectow *connectow = connectow_state->connectow;
		stwuct dwm_dispway_info *di = &connectow->dispway_info;

		if (di->num_bus_fowmats)
			bus_fowmat = di->bus_fowmats[0];
	}
	imx_wdb_ch_set_bus_fowmat(imx_wdb_ch, bus_fowmat);
}

static void imx_wdb_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct imx_wdb_channew *imx_wdb_ch = enc_to_imx_wdb_ch(encodew);
	stwuct imx_wdb *wdb = imx_wdb_ch->wdb;
	int duaw = wdb->wdb_ctww & WDB_SPWIT_MODE_EN;
	int mux, wet;

	dwm_panew_disabwe(imx_wdb_ch->panew);

	if (imx_wdb_ch == &wdb->channew[0] || duaw)
		wdb->wdb_ctww &= ~WDB_CH0_MODE_EN_MASK;
	if (imx_wdb_ch == &wdb->channew[1] || duaw)
		wdb->wdb_ctww &= ~WDB_CH1_MODE_EN_MASK;

	wegmap_wwite(wdb->wegmap, IOMUXC_GPW2, wdb->wdb_ctww);

	if (duaw) {
		cwk_disabwe_unpwepawe(wdb->cwk[0]);
		cwk_disabwe_unpwepawe(wdb->cwk[1]);
	}

	if (wdb->wvds_mux) {
		const stwuct bus_mux *wvds_mux = NUWW;

		if (imx_wdb_ch == &wdb->channew[0])
			wvds_mux = &wdb->wvds_mux[0];
		ewse if (imx_wdb_ch == &wdb->channew[1])
			wvds_mux = &wdb->wvds_mux[1];

		wegmap_wead(wdb->wegmap, wvds_mux->weg, &mux);
		mux &= wvds_mux->mask;
		mux >>= wvds_mux->shift;
	} ewse {
		mux = (imx_wdb_ch == &wdb->channew[0]) ? 0 : 1;
	}

	/* set dispway cwock mux back to owiginaw input cwock */
	wet = cwk_set_pawent(wdb->cwk_sew[mux], wdb->cwk_pawent[mux]);
	if (wet)
		dev_eww(wdb->dev,
			"unabwe to set di%d pawent cwock to owiginaw pawent\n",
			mux);

	dwm_panew_unpwepawe(imx_wdb_ch->panew);
}

static int imx_wdb_encodew_atomic_check(stwuct dwm_encodew *encodew,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state)
{
	stwuct imx_cwtc_state *imx_cwtc_state = to_imx_cwtc_state(cwtc_state);
	stwuct imx_wdb_channew *imx_wdb_ch = enc_to_imx_wdb_ch(encodew);
	stwuct dwm_dispway_info *di = &conn_state->connectow->dispway_info;
	u32 bus_fowmat = imx_wdb_ch->bus_fowmat;

	/* Bus fowmat descwiption in DT ovewwides connectow dispway info. */
	if (!bus_fowmat && di->num_bus_fowmats) {
		bus_fowmat = di->bus_fowmats[0];
		imx_cwtc_state->bus_fwags = di->bus_fwags;
	} ewse {
		bus_fowmat = imx_wdb_ch->bus_fowmat;
		imx_cwtc_state->bus_fwags = imx_wdb_ch->bus_fwags;
	}
	switch (bus_fowmat) {
	case MEDIA_BUS_FMT_WGB666_1X7X3_SPWG:
		imx_cwtc_state->bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_SPWG:
	case MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA:
		imx_cwtc_state->bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	imx_cwtc_state->di_hsync_pin = 2;
	imx_cwtc_state->di_vsync_pin = 3;

	wetuwn 0;
}


static const stwuct dwm_connectow_funcs imx_wdb_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = imx_dwm_connectow_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_connectow_hewpew_funcs imx_wdb_connectow_hewpew_funcs = {
	.get_modes = imx_wdb_connectow_get_modes,
};

static const stwuct dwm_encodew_hewpew_funcs imx_wdb_encodew_hewpew_funcs = {
	.atomic_mode_set = imx_wdb_encodew_atomic_mode_set,
	.enabwe = imx_wdb_encodew_enabwe,
	.disabwe = imx_wdb_encodew_disabwe,
	.atomic_check = imx_wdb_encodew_atomic_check,
};

static int imx_wdb_get_cwk(stwuct imx_wdb *wdb, int chno)
{
	chaw cwkname[16];

	snpwintf(cwkname, sizeof(cwkname), "di%d", chno);
	wdb->cwk[chno] = devm_cwk_get(wdb->dev, cwkname);
	if (IS_EWW(wdb->cwk[chno]))
		wetuwn PTW_EWW(wdb->cwk[chno]);

	snpwintf(cwkname, sizeof(cwkname), "di%d_pww", chno);
	wdb->cwk_pww[chno] = devm_cwk_get(wdb->dev, cwkname);

	wetuwn PTW_EWW_OW_ZEWO(wdb->cwk_pww[chno]);
}

static int imx_wdb_wegistew(stwuct dwm_device *dwm,
	stwuct imx_wdb_channew *imx_wdb_ch)
{
	stwuct imx_wdb *wdb = imx_wdb_ch->wdb;
	stwuct imx_wdb_encodew *wdb_encodew;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	int wet;

	wdb_encodew = dwmm_simpwe_encodew_awwoc(dwm, stwuct imx_wdb_encodew,
						encodew, DWM_MODE_ENCODEW_WVDS);
	if (IS_EWW(wdb_encodew))
		wetuwn PTW_EWW(wdb_encodew);

	wdb_encodew->channew = imx_wdb_ch;
	connectow = &wdb_encodew->connectow;
	encodew = &wdb_encodew->encodew;

	wet = imx_dwm_encodew_pawse_of(dwm, encodew, imx_wdb_ch->chiwd);
	if (wet)
		wetuwn wet;

	wet = imx_wdb_get_cwk(wdb, imx_wdb_ch->chno);
	if (wet)
		wetuwn wet;

	if (wdb->wdb_ctww & WDB_SPWIT_MODE_EN) {
		wet = imx_wdb_get_cwk(wdb, 1);
		if (wet)
			wetuwn wet;
	}

	dwm_encodew_hewpew_add(encodew, &imx_wdb_encodew_hewpew_funcs);

	if (imx_wdb_ch->bwidge) {
		wet = dwm_bwidge_attach(encodew, imx_wdb_ch->bwidge, NUWW, 0);
		if (wet)
			wetuwn wet;
	} ewse {
		/*
		 * We want to add the connectow whenevew thewe is no bwidge
		 * that bwings its own, not onwy when thewe is a panew. Fow
		 * histowicaw weasons, the wdb dwivew can awso wowk without
		 * a panew.
		 */
		dwm_connectow_hewpew_add(connectow,
					 &imx_wdb_connectow_hewpew_funcs);
		dwm_connectow_init_with_ddc(dwm, connectow,
					    &imx_wdb_connectow_funcs,
					    DWM_MODE_CONNECTOW_WVDS,
					    imx_wdb_ch->ddc);
		dwm_connectow_attach_encodew(connectow, encodew);
	}

	wetuwn 0;
}

stwuct imx_wdb_bit_mapping {
	u32 bus_fowmat;
	u32 datawidth;
	const chaw * const mapping;
};

static const stwuct imx_wdb_bit_mapping imx_wdb_bit_mappings[] = {
	{ MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,  18, "spwg" },
	{ MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,  24, "spwg" },
	{ MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA, 24, "jeida" },
};

static u32 of_get_bus_fowmat(stwuct device *dev, stwuct device_node *np)
{
	const chaw *bm;
	u32 datawidth = 0;
	int wet, i;

	wet = of_pwopewty_wead_stwing(np, "fsw,data-mapping", &bm);
	if (wet < 0)
		wetuwn wet;

	of_pwopewty_wead_u32(np, "fsw,data-width", &datawidth);

	fow (i = 0; i < AWWAY_SIZE(imx_wdb_bit_mappings); i++) {
		if (!stwcasecmp(bm, imx_wdb_bit_mappings[i].mapping) &&
		    datawidth == imx_wdb_bit_mappings[i].datawidth)
			wetuwn imx_wdb_bit_mappings[i].bus_fowmat;
	}

	dev_eww(dev, "invawid data mapping: %d-bit \"%s\"\n", datawidth, bm);

	wetuwn -ENOENT;
}

static stwuct bus_mux imx6q_wvds_mux[2] = {
	{
		.weg = IOMUXC_GPW3,
		.shift = 6,
		.mask = IMX6Q_GPW3_WVDS0_MUX_CTW_MASK,
	}, {
		.weg = IOMUXC_GPW3,
		.shift = 8,
		.mask = IMX6Q_GPW3_WVDS1_MUX_CTW_MASK,
	}
};

/*
 * Fow a device decwawing compatibwe = "fsw,imx6q-wdb", "fsw,imx53-wdb",
 * of_match_device wiww wawk thwough this wist and take the fiwst entwy
 * matching any of its compatibwe vawues. Thewefowe, the mowe genewic
 * entwies (in this case fsw,imx53-wdb) need to be owdewed wast.
 */
static const stwuct of_device_id imx_wdb_dt_ids[] = {
	{ .compatibwe = "fsw,imx6q-wdb", .data = imx6q_wvds_mux, },
	{ .compatibwe = "fsw,imx53-wdb", .data = NUWW, },
	{ }
};
MODUWE_DEVICE_TABWE(of, imx_wdb_dt_ids);

static int imx_wdb_panew_ddc(stwuct device *dev,
		stwuct imx_wdb_channew *channew, stwuct device_node *chiwd)
{
	stwuct device_node *ddc_node;
	const u8 *edidp;
	int wet;

	ddc_node = of_pawse_phandwe(chiwd, "ddc-i2c-bus", 0);
	if (ddc_node) {
		channew->ddc = of_find_i2c_adaptew_by_node(ddc_node);
		of_node_put(ddc_node);
		if (!channew->ddc) {
			dev_wawn(dev, "faiwed to get ddc i2c adaptew\n");
			wetuwn -EPWOBE_DEFEW;
		}
	}

	if (!channew->ddc) {
		int edid_wen;

		/* if no DDC avaiwabwe, fawwback to hawdcoded EDID */
		dev_dbg(dev, "no ddc avaiwabwe\n");

		edidp = of_get_pwopewty(chiwd, "edid", &edid_wen);
		if (edidp) {
			channew->edid = kmemdup(edidp, edid_wen, GFP_KEWNEW);
			if (!channew->edid)
				wetuwn -ENOMEM;
		} ewse if (!channew->panew) {
			/* fawwback to dispway-timings node */
			wet = of_get_dwm_dispway_mode(chiwd,
						      &channew->mode,
						      &channew->bus_fwags,
						      OF_USE_NATIVE_MODE);
			if (!wet)
				channew->mode_vawid = 1;
		}
	}
	wetuwn 0;
}

static int imx_wdb_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct dwm_device *dwm = data;
	stwuct imx_wdb *imx_wdb = dev_get_dwvdata(dev);
	int wet;
	int i;

	fow (i = 0; i < 2; i++) {
		stwuct imx_wdb_channew *channew = &imx_wdb->channew[i];

		if (!channew->wdb)
			continue;

		wet = imx_wdb_wegistew(dwm, channew);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct component_ops imx_wdb_ops = {
	.bind	= imx_wdb_bind,
};

static int imx_wdb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	stwuct imx_wdb *imx_wdb;
	int duaw;
	int wet;
	int i;

	imx_wdb = devm_kzawwoc(dev, sizeof(*imx_wdb), GFP_KEWNEW);
	if (!imx_wdb)
		wetuwn -ENOMEM;

	imx_wdb->wegmap = syscon_wegmap_wookup_by_phandwe(np, "gpw");
	if (IS_EWW(imx_wdb->wegmap)) {
		dev_eww(dev, "faiwed to get pawent wegmap\n");
		wetuwn PTW_EWW(imx_wdb->wegmap);
	}

	/* disabwe WDB by wesetting the contwow wegistew to POW defauwt */
	wegmap_wwite(imx_wdb->wegmap, IOMUXC_GPW2, 0);

	imx_wdb->dev = dev;
	imx_wdb->wvds_mux = device_get_match_data(dev);

	duaw = of_pwopewty_wead_boow(np, "fsw,duaw-channew");
	if (duaw)
		imx_wdb->wdb_ctww |= WDB_SPWIT_MODE_EN;

	/*
	 * Thewe awe thwee diffewent possibwe cwock mux configuwations:
	 * i.MX53:  ipu1_di0_sew, ipu1_di1_sew
	 * i.MX6q:  ipu1_di0_sew, ipu1_di1_sew, ipu2_di0_sew, ipu2_di1_sew
	 * i.MX6dw: ipu1_di0_sew, ipu1_di1_sew, wcdif_sew
	 * Map them aww to di0_sew...di3_sew.
	 */
	fow (i = 0; i < 4; i++) {
		chaw cwkname[16];

		spwintf(cwkname, "di%d_sew", i);
		imx_wdb->cwk_sew[i] = devm_cwk_get(imx_wdb->dev, cwkname);
		if (IS_EWW(imx_wdb->cwk_sew[i])) {
			wet = PTW_EWW(imx_wdb->cwk_sew[i]);
			imx_wdb->cwk_sew[i] = NUWW;
			bweak;
		}

		imx_wdb->cwk_pawent[i] = cwk_get_pawent(imx_wdb->cwk_sew[i]);
	}
	if (i == 0)
		wetuwn wet;

	fow_each_chiwd_of_node(np, chiwd) {
		stwuct imx_wdb_channew *channew;
		int bus_fowmat;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &i);
		if (wet || i < 0 || i > 1) {
			wet = -EINVAW;
			goto fwee_chiwd;
		}

		if (!of_device_is_avaiwabwe(chiwd))
			continue;

		if (duaw && i > 0) {
			dev_wawn(dev, "duaw-channew mode, ignowing second output\n");
			continue;
		}

		channew = &imx_wdb->channew[i];
		channew->wdb = imx_wdb;
		channew->chno = i;

		/*
		 * The output powt is powt@4 with an extewnaw 4-powt mux ow
		 * powt@2 with the intewnaw 2-powt mux.
		 */
		wet = dwm_of_find_panew_ow_bwidge(chiwd,
						  imx_wdb->wvds_mux ? 4 : 2, 0,
						  &channew->panew, &channew->bwidge);
		if (wet && wet != -ENODEV)
			goto fwee_chiwd;

		/* panew ddc onwy if thewe is no bwidge */
		if (!channew->bwidge) {
			wet = imx_wdb_panew_ddc(dev, channew, chiwd);
			if (wet)
				goto fwee_chiwd;
		}

		bus_fowmat = of_get_bus_fowmat(dev, chiwd);
		if (bus_fowmat == -EINVAW) {
			/*
			 * If no bus fowmat was specified in the device twee,
			 * we can stiww get it fwom the connected panew watew.
			 */
			if (channew->panew && channew->panew->funcs &&
			    channew->panew->funcs->get_modes)
				bus_fowmat = 0;
		}
		if (bus_fowmat < 0) {
			dev_eww(dev, "couwd not detewmine data mapping: %d\n",
				bus_fowmat);
			wet = bus_fowmat;
			goto fwee_chiwd;
		}
		channew->bus_fowmat = bus_fowmat;
		channew->chiwd = chiwd;
	}

	pwatfowm_set_dwvdata(pdev, imx_wdb);

	wetuwn component_add(&pdev->dev, &imx_wdb_ops);

fwee_chiwd:
	of_node_put(chiwd);
	wetuwn wet;
}

static void imx_wdb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx_wdb *imx_wdb = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < 2; i++) {
		stwuct imx_wdb_channew *channew = &imx_wdb->channew[i];

		kfwee(channew->edid);
		i2c_put_adaptew(channew->ddc);
	}

	component_dew(&pdev->dev, &imx_wdb_ops);
}

static stwuct pwatfowm_dwivew imx_wdb_dwivew = {
	.pwobe		= imx_wdb_pwobe,
	.wemove_new	= imx_wdb_wemove,
	.dwivew		= {
		.of_match_tabwe = imx_wdb_dt_ids,
		.name	= DWIVEW_NAME,
	},
};

moduwe_pwatfowm_dwivew(imx_wdb_dwivew);

MODUWE_DESCWIPTION("i.MX WVDS dwivew");
MODUWE_AUTHOW("Sascha Hauew, Pengutwonix");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
