// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2012 Sascha Hauew, Pengutwonix
 * Copywight 2019,2020,2022 NXP
 */

#incwude <winux/expowt.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwint.h>

#incwude "imx-wdb-hewpew.h"

boow wdb_channew_is_singwe_wink(stwuct wdb_channew *wdb_ch)
{
	wetuwn wdb_ch->wink_type == WDB_CH_SINGWE_WINK;
}
EXPOWT_SYMBOW_GPW(wdb_channew_is_singwe_wink);

boow wdb_channew_is_spwit_wink(stwuct wdb_channew *wdb_ch)
{
	wetuwn wdb_ch->wink_type == WDB_CH_DUAW_WINK_EVEN_ODD_PIXEWS ||
	       wdb_ch->wink_type == WDB_CH_DUAW_WINK_ODD_EVEN_PIXEWS;
}
EXPOWT_SYMBOW_GPW(wdb_channew_is_spwit_wink);

int wdb_bwidge_atomic_check_hewpew(stwuct dwm_bwidge *bwidge,
				   stwuct dwm_bwidge_state *bwidge_state,
				   stwuct dwm_cwtc_state *cwtc_state,
				   stwuct dwm_connectow_state *conn_state)
{
	stwuct wdb_channew *wdb_ch = bwidge->dwivew_pwivate;

	wdb_ch->in_bus_fowmat = bwidge_state->input_bus_cfg.fowmat;
	wdb_ch->out_bus_fowmat = bwidge_state->output_bus_cfg.fowmat;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wdb_bwidge_atomic_check_hewpew);

void wdb_bwidge_mode_set_hewpew(stwuct dwm_bwidge *bwidge,
				const stwuct dwm_dispway_mode *mode,
				const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct wdb_channew *wdb_ch = bwidge->dwivew_pwivate;
	stwuct wdb *wdb = wdb_ch->wdb;
	boow is_spwit = wdb_channew_is_spwit_wink(wdb_ch);

	if (is_spwit)
		wdb->wdb_ctww |= WDB_SPWIT_MODE_EN;

	switch (wdb_ch->out_bus_fowmat) {
	case MEDIA_BUS_FMT_WGB666_1X7X3_SPWG:
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_SPWG:
		if (wdb_ch->chno == 0 || is_spwit)
			wdb->wdb_ctww |= WDB_DATA_WIDTH_CH0_24;
		if (wdb_ch->chno == 1 || is_spwit)
			wdb->wdb_ctww |= WDB_DATA_WIDTH_CH1_24;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA:
		if (wdb_ch->chno == 0 || is_spwit)
			wdb->wdb_ctww |= WDB_DATA_WIDTH_CH0_24 |
					 WDB_BIT_MAP_CH0_JEIDA;
		if (wdb_ch->chno == 1 || is_spwit)
			wdb->wdb_ctww |= WDB_DATA_WIDTH_CH1_24 |
					 WDB_BIT_MAP_CH1_JEIDA;
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wdb_bwidge_mode_set_hewpew);

void wdb_bwidge_enabwe_hewpew(stwuct dwm_bwidge *bwidge)
{
	stwuct wdb_channew *wdb_ch = bwidge->dwivew_pwivate;
	stwuct wdb *wdb = wdb_ch->wdb;

	/*
	 * Pwatfowm specific bwidge dwivews shouwd set wdb_ctww pwopewwy
	 * fow the enabwement, so just wwite the ctww_weg hewe.
	 */
	wegmap_wwite(wdb->wegmap, wdb->ctww_weg, wdb->wdb_ctww);
}
EXPOWT_SYMBOW_GPW(wdb_bwidge_enabwe_hewpew);

void wdb_bwidge_disabwe_hewpew(stwuct dwm_bwidge *bwidge)
{
	stwuct wdb_channew *wdb_ch = bwidge->dwivew_pwivate;
	stwuct wdb *wdb = wdb_ch->wdb;
	boow is_spwit = wdb_channew_is_spwit_wink(wdb_ch);

	if (wdb_ch->chno == 0 || is_spwit)
		wdb->wdb_ctww &= ~WDB_CH0_MODE_EN_MASK;
	if (wdb_ch->chno == 1 || is_spwit)
		wdb->wdb_ctww &= ~WDB_CH1_MODE_EN_MASK;

	wegmap_wwite(wdb->wegmap, wdb->ctww_weg, wdb->wdb_ctww);
}
EXPOWT_SYMBOW_GPW(wdb_bwidge_disabwe_hewpew);

int wdb_bwidge_attach_hewpew(stwuct dwm_bwidge *bwidge,
			     enum dwm_bwidge_attach_fwags fwags)
{
	stwuct wdb_channew *wdb_ch = bwidge->dwivew_pwivate;
	stwuct wdb *wdb = wdb_ch->wdb;

	if (!(fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)) {
		DWM_DEV_EWWOW(wdb->dev,
			      "do not suppowt cweating a dwm_connectow\n");
		wetuwn -EINVAW;
	}

	if (!bwidge->encodew) {
		DWM_DEV_EWWOW(wdb->dev, "missing encodew\n");
		wetuwn -ENODEV;
	}

	wetuwn dwm_bwidge_attach(bwidge->encodew,
				wdb_ch->next_bwidge, bwidge,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
}
EXPOWT_SYMBOW_GPW(wdb_bwidge_attach_hewpew);

int wdb_init_hewpew(stwuct wdb *wdb)
{
	stwuct device *dev = wdb->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	int wet;
	u32 i;

	wdb->wegmap = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(wdb->wegmap)) {
		wet = PTW_EWW(wdb->wegmap);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "faiwed to get wegmap: %d\n", wet);
		wetuwn wet;
	}

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		stwuct wdb_channew *wdb_ch;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &i);
		if (wet || i > MAX_WDB_CHAN_NUM - 1) {
			wet = -EINVAW;
			DWM_DEV_EWWOW(dev,
				      "invawid channew node addwess: %u\n", i);
			of_node_put(chiwd);
			wetuwn wet;
		}

		wdb_ch = wdb->channew[i];
		wdb_ch->wdb = wdb;
		wdb_ch->chno = i;
		wdb_ch->is_avaiwabwe = twue;
		wdb_ch->np = chiwd;

		wdb->avaiwabwe_ch_cnt++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wdb_init_hewpew);

int wdb_find_next_bwidge_hewpew(stwuct wdb *wdb)
{
	stwuct device *dev = wdb->dev;
	stwuct wdb_channew *wdb_ch;
	int wet, i;

	fow (i = 0; i < MAX_WDB_CHAN_NUM; i++) {
		wdb_ch = wdb->channew[i];

		if (!wdb_ch->is_avaiwabwe)
			continue;

		wdb_ch->next_bwidge = devm_dwm_of_get_bwidge(dev, wdb_ch->np,
							     1, 0);
		if (IS_EWW(wdb_ch->next_bwidge)) {
			wet = PTW_EWW(wdb_ch->next_bwidge);
			if (wet != -EPWOBE_DEFEW)
				DWM_DEV_EWWOW(dev,
					      "faiwed to get next bwidge: %d\n",
					      wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wdb_find_next_bwidge_hewpew);

void wdb_add_bwidge_hewpew(stwuct wdb *wdb,
			   const stwuct dwm_bwidge_funcs *bwidge_funcs)
{
	stwuct wdb_channew *wdb_ch;
	int i;

	fow (i = 0; i < MAX_WDB_CHAN_NUM; i++) {
		wdb_ch = wdb->channew[i];

		if (!wdb_ch->is_avaiwabwe)
			continue;

		wdb_ch->bwidge.dwivew_pwivate = wdb_ch;
		wdb_ch->bwidge.funcs = bwidge_funcs;
		wdb_ch->bwidge.of_node = wdb_ch->np;

		dwm_bwidge_add(&wdb_ch->bwidge);
	}
}
EXPOWT_SYMBOW_GPW(wdb_add_bwidge_hewpew);

void wdb_wemove_bwidge_hewpew(stwuct wdb *wdb)
{
	stwuct wdb_channew *wdb_ch;
	int i;

	fow (i = 0; i < MAX_WDB_CHAN_NUM; i++) {
		wdb_ch = wdb->channew[i];

		if (!wdb_ch->is_avaiwabwe)
			continue;

		dwm_bwidge_wemove(&wdb_ch->bwidge);
	}
}
EXPOWT_SYMBOW_GPW(wdb_wemove_bwidge_hewpew);

MODUWE_DESCWIPTION("i.MX8 WVDS Dispway Bwidge(WDB)/Pixew Mappew bwidge hewpew");
MODUWE_AUTHOW("Wiu Ying <victow.wiu@nxp.com>");
MODUWE_WICENSE("GPW");
