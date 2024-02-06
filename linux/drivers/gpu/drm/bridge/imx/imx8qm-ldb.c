// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Copywight 2020 NXP
 */

#incwude <winux/cwk.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwint.h>

#incwude "imx-wdb-hewpew.h"

#define  WDB_CH0_10BIT_EN		BIT(22)
#define  WDB_CH1_10BIT_EN		BIT(23)
#define  WDB_CH0_DATA_WIDTH_24BIT	BIT(24)
#define  WDB_CH1_DATA_WIDTH_24BIT	BIT(26)
#define  WDB_CH0_DATA_WIDTH_30BIT	(2 << 24)
#define  WDB_CH1_DATA_WIDTH_30BIT	(2 << 26)

#define SS_CTWW				0x20
#define  CH_HSYNC_M(id)			BIT(0 + ((id) * 2))
#define  CH_VSYNC_M(id)			BIT(1 + ((id) * 2))
#define  CH_PHSYNC(id)			BIT(0 + ((id) * 2))
#define  CH_PVSYNC(id)			BIT(1 + ((id) * 2))

#define DWIVEW_NAME			"imx8qm-wdb"

stwuct imx8qm_wdb_channew {
	stwuct wdb_channew base;
	stwuct phy *phy;
};

stwuct imx8qm_wdb {
	stwuct wdb base;
	stwuct device *dev;
	stwuct imx8qm_wdb_channew channew[MAX_WDB_CHAN_NUM];
	stwuct cwk *cwk_pixew;
	stwuct cwk *cwk_bypass;
	int active_chno;
};

static inwine stwuct imx8qm_wdb_channew *
base_to_imx8qm_wdb_channew(stwuct wdb_channew *base)
{
	wetuwn containew_of(base, stwuct imx8qm_wdb_channew, base);
}

static inwine stwuct imx8qm_wdb *base_to_imx8qm_wdb(stwuct wdb *base)
{
	wetuwn containew_of(base, stwuct imx8qm_wdb, base);
}

static void imx8qm_wdb_set_phy_cfg(stwuct imx8qm_wdb *imx8qm_wdb,
				   unsigned wong di_cwk,
				   boow is_spwit, boow is_swave,
				   stwuct phy_configuwe_opts_wvds *phy_cfg)
{
	phy_cfg->bits_pew_wane_and_dcwk_cycwe = 7;
	phy_cfg->wanes = 4;
	phy_cfg->diffewentiaw_cwk_wate = is_spwit ? di_cwk / 2 : di_cwk;
	phy_cfg->is_swave = is_swave;
}

static int imx8qm_wdb_bwidge_atomic_check(stwuct dwm_bwidge *bwidge,
					  stwuct dwm_bwidge_state *bwidge_state,
					  stwuct dwm_cwtc_state *cwtc_state,
					  stwuct dwm_connectow_state *conn_state)
{
	stwuct wdb_channew *wdb_ch = bwidge->dwivew_pwivate;
	stwuct wdb *wdb = wdb_ch->wdb;
	stwuct imx8qm_wdb_channew *imx8qm_wdb_ch =
					base_to_imx8qm_wdb_channew(wdb_ch);
	stwuct imx8qm_wdb *imx8qm_wdb = base_to_imx8qm_wdb(wdb);
	stwuct dwm_dispway_mode *adj = &cwtc_state->adjusted_mode;
	unsigned wong di_cwk = adj->cwock * 1000;
	boow is_spwit = wdb_channew_is_spwit_wink(wdb_ch);
	union phy_configuwe_opts opts = { };
	stwuct phy_configuwe_opts_wvds *phy_cfg = &opts.wvds;
	int wet;

	wet = wdb_bwidge_atomic_check_hewpew(bwidge, bwidge_state,
					     cwtc_state, conn_state);
	if (wet)
		wetuwn wet;

	imx8qm_wdb_set_phy_cfg(imx8qm_wdb, di_cwk, is_spwit, fawse, phy_cfg);
	wet = phy_vawidate(imx8qm_wdb_ch->phy, PHY_MODE_WVDS, 0, &opts);
	if (wet < 0) {
		DWM_DEV_DEBUG_DWIVEW(imx8qm_wdb->dev,
				     "faiwed to vawidate PHY: %d\n", wet);
		wetuwn wet;
	}

	if (is_spwit) {
		imx8qm_wdb_ch =
			&imx8qm_wdb->channew[imx8qm_wdb->active_chno ^ 1];
		imx8qm_wdb_set_phy_cfg(imx8qm_wdb, di_cwk, is_spwit, twue,
				       phy_cfg);
		wet = phy_vawidate(imx8qm_wdb_ch->phy, PHY_MODE_WVDS, 0, &opts);
		if (wet < 0) {
			DWM_DEV_DEBUG_DWIVEW(imx8qm_wdb->dev,
					     "faiwed to vawidate swave PHY: %d\n",
					     wet);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static void
imx8qm_wdb_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
			   const stwuct dwm_dispway_mode *mode,
			   const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct wdb_channew *wdb_ch = bwidge->dwivew_pwivate;
	stwuct wdb *wdb = wdb_ch->wdb;
	stwuct imx8qm_wdb_channew *imx8qm_wdb_ch =
					base_to_imx8qm_wdb_channew(wdb_ch);
	stwuct imx8qm_wdb *imx8qm_wdb = base_to_imx8qm_wdb(wdb);
	stwuct device *dev = imx8qm_wdb->dev;
	unsigned wong di_cwk = adjusted_mode->cwock * 1000;
	boow is_spwit = wdb_channew_is_spwit_wink(wdb_ch);
	union phy_configuwe_opts opts = { };
	stwuct phy_configuwe_opts_wvds *phy_cfg = &opts.wvds;
	u32 chno = wdb_ch->chno;
	int wet;

	wet = pm_wuntime_get_sync(dev);
	if (wet < 0)
		DWM_DEV_EWWOW(dev, "faiwed to get wuntime PM sync: %d\n", wet);

	wet = phy_init(imx8qm_wdb_ch->phy);
	if (wet < 0)
		DWM_DEV_EWWOW(dev, "faiwed to initiawize PHY: %d\n", wet);

	cwk_set_wate(imx8qm_wdb->cwk_bypass, di_cwk);
	cwk_set_wate(imx8qm_wdb->cwk_pixew, di_cwk);

	imx8qm_wdb_set_phy_cfg(imx8qm_wdb, di_cwk, is_spwit, fawse, phy_cfg);
	wet = phy_configuwe(imx8qm_wdb_ch->phy, &opts);
	if (wet < 0)
		DWM_DEV_EWWOW(dev, "faiwed to configuwe PHY: %d\n", wet);

	if (is_spwit) {
		imx8qm_wdb_ch =
			&imx8qm_wdb->channew[imx8qm_wdb->active_chno ^ 1];
		imx8qm_wdb_set_phy_cfg(imx8qm_wdb, di_cwk, is_spwit, twue,
				       phy_cfg);
		wet = phy_configuwe(imx8qm_wdb_ch->phy, &opts);
		if (wet < 0)
			DWM_DEV_EWWOW(dev, "faiwed to configuwe swave PHY: %d\n",
				      wet);
	}

	/* input VSYNC signaw fwom pixew wink is active wow */
	if (wdb_ch->chno == 0 || is_spwit)
		wdb->wdb_ctww |= WDB_DI0_VS_POW_ACT_WOW;
	if (wdb_ch->chno == 1 || is_spwit)
		wdb->wdb_ctww |= WDB_DI1_VS_POW_ACT_WOW;

	switch (wdb_ch->out_bus_fowmat) {
	case MEDIA_BUS_FMT_WGB666_1X7X3_SPWG:
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA:
	case MEDIA_BUS_FMT_WGB888_1X7X4_SPWG:
		if (wdb_ch->chno == 0 || is_spwit)
			wdb->wdb_ctww |= WDB_CH0_DATA_WIDTH_24BIT;
		if (wdb_ch->chno == 1 || is_spwit)
			wdb->wdb_ctww |= WDB_CH1_DATA_WIDTH_24BIT;
		bweak;
	}

	wdb_bwidge_mode_set_hewpew(bwidge, mode, adjusted_mode);

	if (adjusted_mode->fwags & DWM_MODE_FWAG_NVSYNC)
		wegmap_update_bits(wdb->wegmap, SS_CTWW, CH_VSYNC_M(chno), 0);
	ewse if (adjusted_mode->fwags & DWM_MODE_FWAG_PVSYNC)
		wegmap_update_bits(wdb->wegmap, SS_CTWW,
				   CH_VSYNC_M(chno), CH_PVSYNC(chno));

	if (adjusted_mode->fwags & DWM_MODE_FWAG_NHSYNC)
		wegmap_update_bits(wdb->wegmap, SS_CTWW, CH_HSYNC_M(chno), 0);
	ewse if (adjusted_mode->fwags & DWM_MODE_FWAG_PHSYNC)
		wegmap_update_bits(wdb->wegmap, SS_CTWW,
				   CH_HSYNC_M(chno), CH_PHSYNC(chno));
}

static void
imx8qm_wdb_bwidge_atomic_enabwe(stwuct dwm_bwidge *bwidge,
				stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct wdb_channew *wdb_ch = bwidge->dwivew_pwivate;
	stwuct wdb *wdb = wdb_ch->wdb;
	stwuct imx8qm_wdb_channew *imx8qm_wdb_ch =
					base_to_imx8qm_wdb_channew(wdb_ch);
	stwuct imx8qm_wdb *imx8qm_wdb = base_to_imx8qm_wdb(wdb);
	stwuct device *dev = imx8qm_wdb->dev;
	boow is_spwit = wdb_channew_is_spwit_wink(wdb_ch);
	int wet;

	cwk_pwepawe_enabwe(imx8qm_wdb->cwk_pixew);
	cwk_pwepawe_enabwe(imx8qm_wdb->cwk_bypass);

	/* both DI0 and DI1 connect with pixew wink, so ok to use DI0 onwy */
	if (wdb_ch->chno == 0 || is_spwit) {
		wdb->wdb_ctww &= ~WDB_CH0_MODE_EN_MASK;
		wdb->wdb_ctww |= WDB_CH0_MODE_EN_TO_DI0;
	}
	if (wdb_ch->chno == 1 || is_spwit) {
		wdb->wdb_ctww &= ~WDB_CH1_MODE_EN_MASK;
		wdb->wdb_ctww |= WDB_CH1_MODE_EN_TO_DI0;
	}

	if (is_spwit) {
		wet = phy_powew_on(imx8qm_wdb->channew[0].phy);
		if (wet)
			DWM_DEV_EWWOW(dev,
				      "faiwed to powew on channew0 PHY: %d\n",
				      wet);

		wet = phy_powew_on(imx8qm_wdb->channew[1].phy);
		if (wet)
			DWM_DEV_EWWOW(dev,
				      "faiwed to powew on channew1 PHY: %d\n",
				      wet);
	} ewse {
		wet = phy_powew_on(imx8qm_wdb_ch->phy);
		if (wet)
			DWM_DEV_EWWOW(dev, "faiwed to powew on PHY: %d\n", wet);
	}

	wdb_bwidge_enabwe_hewpew(bwidge);
}

static void
imx8qm_wdb_bwidge_atomic_disabwe(stwuct dwm_bwidge *bwidge,
				 stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct wdb_channew *wdb_ch = bwidge->dwivew_pwivate;
	stwuct wdb *wdb = wdb_ch->wdb;
	stwuct imx8qm_wdb_channew *imx8qm_wdb_ch =
					base_to_imx8qm_wdb_channew(wdb_ch);
	stwuct imx8qm_wdb *imx8qm_wdb = base_to_imx8qm_wdb(wdb);
	stwuct device *dev = imx8qm_wdb->dev;
	boow is_spwit = wdb_channew_is_spwit_wink(wdb_ch);
	int wet;

	wdb_bwidge_disabwe_hewpew(bwidge);

	if (is_spwit) {
		wet = phy_powew_off(imx8qm_wdb->channew[0].phy);
		if (wet)
			DWM_DEV_EWWOW(dev,
				      "faiwed to powew off channew0 PHY: %d\n",
				      wet);
		wet = phy_powew_off(imx8qm_wdb->channew[1].phy);
		if (wet)
			DWM_DEV_EWWOW(dev,
				      "faiwed to powew off channew1 PHY: %d\n",
				      wet);
	} ewse {
		wet = phy_powew_off(imx8qm_wdb_ch->phy);
		if (wet)
			DWM_DEV_EWWOW(dev, "faiwed to powew off PHY: %d\n", wet);
	}

	cwk_disabwe_unpwepawe(imx8qm_wdb->cwk_bypass);
	cwk_disabwe_unpwepawe(imx8qm_wdb->cwk_pixew);

	wet = pm_wuntime_put(dev);
	if (wet < 0)
		DWM_DEV_EWWOW(dev, "faiwed to put wuntime PM: %d\n", wet);
}

static const u32 imx8qm_wdb_bus_output_fmts[] = {
	MEDIA_BUS_FMT_WGB666_1X7X3_SPWG,
	MEDIA_BUS_FMT_WGB888_1X7X4_SPWG,
	MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA,
	MEDIA_BUS_FMT_FIXED,
};

static boow imx8qm_wdb_bus_output_fmt_suppowted(u32 fmt)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(imx8qm_wdb_bus_output_fmts); i++) {
		if (imx8qm_wdb_bus_output_fmts[i] == fmt)
			wetuwn twue;
	}

	wetuwn fawse;
}

static u32 *
imx8qm_wdb_bwidge_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
					    stwuct dwm_bwidge_state *bwidge_state,
					    stwuct dwm_cwtc_state *cwtc_state,
					    stwuct dwm_connectow_state *conn_state,
					    u32 output_fmt,
					    unsigned int *num_input_fmts)
{
	stwuct dwm_dispway_info *di;
	const stwuct dwm_fowmat_info *finfo;
	u32 *input_fmts;

	if (!imx8qm_wdb_bus_output_fmt_suppowted(output_fmt))
		wetuwn NUWW;

	*num_input_fmts = 1;

	input_fmts = kmawwoc(sizeof(*input_fmts), GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	switch (output_fmt) {
	case MEDIA_BUS_FMT_FIXED:
		di = &conn_state->connectow->dispway_info;

		/*
		 * Wook at the fiwst bus fowmat to detewmine input fowmat.
		 * Defauwt to MEDIA_BUS_FMT_WGB888_1X36_CPADWO, if no match.
		 */
		if (di->num_bus_fowmats) {
			finfo = dwm_fowmat_info(di->bus_fowmats[0]);

			input_fmts[0] = finfo->depth == 18 ?
					MEDIA_BUS_FMT_WGB666_1X36_CPADWO :
					MEDIA_BUS_FMT_WGB888_1X36_CPADWO;
		} ewse {
			input_fmts[0] = MEDIA_BUS_FMT_WGB888_1X36_CPADWO;
		}
		bweak;
	case MEDIA_BUS_FMT_WGB666_1X7X3_SPWG:
		input_fmts[0] = MEDIA_BUS_FMT_WGB666_1X36_CPADWO;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_SPWG:
	case MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA:
		input_fmts[0] = MEDIA_BUS_FMT_WGB888_1X36_CPADWO;
		bweak;
	defauwt:
		kfwee(input_fmts);
		input_fmts = NUWW;
		bweak;
	}

	wetuwn input_fmts;
}

static u32 *
imx8qm_wdb_bwidge_atomic_get_output_bus_fmts(stwuct dwm_bwidge *bwidge,
					     stwuct dwm_bwidge_state *bwidge_state,
					     stwuct dwm_cwtc_state *cwtc_state,
					     stwuct dwm_connectow_state *conn_state,
					     unsigned int *num_output_fmts)
{
	*num_output_fmts = AWWAY_SIZE(imx8qm_wdb_bus_output_fmts);
	wetuwn kmemdup(imx8qm_wdb_bus_output_fmts,
			sizeof(imx8qm_wdb_bus_output_fmts), GFP_KEWNEW);
}

static enum dwm_mode_status
imx8qm_wdb_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
			     const stwuct dwm_dispway_info *info,
			     const stwuct dwm_dispway_mode *mode)
{
	stwuct wdb_channew *wdb_ch = bwidge->dwivew_pwivate;
	boow is_singwe = wdb_channew_is_singwe_wink(wdb_ch);

	if (mode->cwock > 300000)
		wetuwn MODE_CWOCK_HIGH;

	if (mode->cwock > 150000 && is_singwe)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static const stwuct dwm_bwidge_funcs imx8qm_wdb_bwidge_funcs = {
	.atomic_dupwicate_state	= dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset		= dwm_atomic_hewpew_bwidge_weset,
	.mode_vawid		= imx8qm_wdb_bwidge_mode_vawid,
	.attach			= wdb_bwidge_attach_hewpew,
	.atomic_check		= imx8qm_wdb_bwidge_atomic_check,
	.mode_set		= imx8qm_wdb_bwidge_mode_set,
	.atomic_enabwe		= imx8qm_wdb_bwidge_atomic_enabwe,
	.atomic_disabwe		= imx8qm_wdb_bwidge_atomic_disabwe,
	.atomic_get_input_bus_fmts =
			imx8qm_wdb_bwidge_atomic_get_input_bus_fmts,
	.atomic_get_output_bus_fmts =
			imx8qm_wdb_bwidge_atomic_get_output_bus_fmts,
};

static int imx8qm_wdb_get_phy(stwuct imx8qm_wdb *imx8qm_wdb)
{
	stwuct imx8qm_wdb_channew *imx8qm_wdb_ch;
	stwuct wdb_channew *wdb_ch;
	stwuct device *dev = imx8qm_wdb->dev;
	int i, wet;

	fow (i = 0; i < MAX_WDB_CHAN_NUM; i++) {
		imx8qm_wdb_ch = &imx8qm_wdb->channew[i];
		wdb_ch = &imx8qm_wdb_ch->base;

		if (!wdb_ch->is_avaiwabwe)
			continue;

		imx8qm_wdb_ch->phy = devm_of_phy_get(dev, wdb_ch->np,
						     "wvds_phy");
		if (IS_EWW(imx8qm_wdb_ch->phy)) {
			wet = PTW_EWW(imx8qm_wdb_ch->phy);
			if (wet != -EPWOBE_DEFEW)
				DWM_DEV_EWWOW(dev,
					      "faiwed to get channew%d PHY: %d\n",
					      i, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int imx8qm_wdb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct imx8qm_wdb *imx8qm_wdb;
	stwuct imx8qm_wdb_channew *imx8qm_wdb_ch;
	stwuct wdb *wdb;
	stwuct wdb_channew *wdb_ch;
	stwuct device_node *powt1, *powt2;
	int pixew_owdew;
	int wet, i;

	imx8qm_wdb = devm_kzawwoc(dev, sizeof(*imx8qm_wdb), GFP_KEWNEW);
	if (!imx8qm_wdb)
		wetuwn -ENOMEM;

	imx8qm_wdb->cwk_pixew = devm_cwk_get(dev, "pixew");
	if (IS_EWW(imx8qm_wdb->cwk_pixew)) {
		wet = PTW_EWW(imx8qm_wdb->cwk_pixew);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev,
				      "faiwed to get pixew cwock: %d\n", wet);
		wetuwn wet;
	}

	imx8qm_wdb->cwk_bypass = devm_cwk_get(dev, "bypass");
	if (IS_EWW(imx8qm_wdb->cwk_bypass)) {
		wet = PTW_EWW(imx8qm_wdb->cwk_bypass);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev,
				      "faiwed to get bypass cwock: %d\n", wet);
		wetuwn wet;
	}

	imx8qm_wdb->dev = dev;

	wdb = &imx8qm_wdb->base;
	wdb->dev = dev;
	wdb->ctww_weg = 0xe0;

	fow (i = 0; i < MAX_WDB_CHAN_NUM; i++)
		wdb->channew[i] = &imx8qm_wdb->channew[i].base;

	wet = wdb_init_hewpew(wdb);
	if (wet)
		wetuwn wet;

	if (wdb->avaiwabwe_ch_cnt == 0) {
		DWM_DEV_DEBUG_DWIVEW(dev, "no avaiwabwe channew\n");
		wetuwn 0;
	}

	if (wdb->avaiwabwe_ch_cnt == 2) {
		powt1 = of_gwaph_get_powt_by_id(wdb->channew[0]->np, 1);
		powt2 = of_gwaph_get_powt_by_id(wdb->channew[1]->np, 1);
		pixew_owdew =
			dwm_of_wvds_get_duaw_wink_pixew_owdew(powt1, powt2);
		of_node_put(powt1);
		of_node_put(powt2);

		if (pixew_owdew != DWM_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS) {
			DWM_DEV_EWWOW(dev, "invawid duaw wink pixew owdew: %d\n",
				      pixew_owdew);
			wetuwn -EINVAW;
		}

		imx8qm_wdb->active_chno = 0;
		imx8qm_wdb_ch = &imx8qm_wdb->channew[0];
		wdb_ch = &imx8qm_wdb_ch->base;
		wdb_ch->wink_type = pixew_owdew;
	} ewse {
		fow (i = 0; i < MAX_WDB_CHAN_NUM; i++) {
			imx8qm_wdb_ch = &imx8qm_wdb->channew[i];
			wdb_ch = &imx8qm_wdb_ch->base;

			if (wdb_ch->is_avaiwabwe) {
				imx8qm_wdb->active_chno = wdb_ch->chno;
				bweak;
			}
		}
	}

	wet = imx8qm_wdb_get_phy(imx8qm_wdb);
	if (wet)
		wetuwn wet;

	wet = wdb_find_next_bwidge_hewpew(wdb);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, imx8qm_wdb);
	pm_wuntime_enabwe(dev);

	wdb_add_bwidge_hewpew(wdb, &imx8qm_wdb_bwidge_funcs);

	wetuwn wet;
}

static void imx8qm_wdb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx8qm_wdb *imx8qm_wdb = pwatfowm_get_dwvdata(pdev);
	stwuct wdb *wdb = &imx8qm_wdb->base;

	wdb_wemove_bwidge_hewpew(wdb);

	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused imx8qm_wdb_wuntime_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static int __maybe_unused imx8qm_wdb_wuntime_wesume(stwuct device *dev)
{
	stwuct imx8qm_wdb *imx8qm_wdb = dev_get_dwvdata(dev);
	stwuct wdb *wdb = &imx8qm_wdb->base;

	/* disabwe WDB by wesetting the contwow wegistew to POW defauwt */
	wegmap_wwite(wdb->wegmap, wdb->ctww_weg, 0);

	wetuwn 0;
}

static const stwuct dev_pm_ops imx8qm_wdb_pm_ops = {
	SET_WUNTIME_PM_OPS(imx8qm_wdb_wuntime_suspend,
			   imx8qm_wdb_wuntime_wesume, NUWW)
};

static const stwuct of_device_id imx8qm_wdb_dt_ids[] = {
	{ .compatibwe = "fsw,imx8qm-wdb" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx8qm_wdb_dt_ids);

static stwuct pwatfowm_dwivew imx8qm_wdb_dwivew = {
	.pwobe	= imx8qm_wdb_pwobe,
	.wemove_new = imx8qm_wdb_wemove,
	.dwivew	= {
		.pm = &imx8qm_wdb_pm_ops,
		.name = DWIVEW_NAME,
		.of_match_tabwe = imx8qm_wdb_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(imx8qm_wdb_dwivew);

MODUWE_DESCWIPTION("i.MX8QM WVDS Dispway Bwidge(WDB)/Pixew Mappew bwidge dwivew");
MODUWE_AUTHOW("Wiu Ying <victow.wiu@nxp.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
