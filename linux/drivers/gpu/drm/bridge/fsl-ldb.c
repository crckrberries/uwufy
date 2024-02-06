// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022 Mawek Vasut <mawex@denx.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>

#define WDB_CTWW_CH0_ENABWE			BIT(0)
#define WDB_CTWW_CH0_DI_SEWECT			BIT(1)
#define WDB_CTWW_CH1_ENABWE			BIT(2)
#define WDB_CTWW_CH1_DI_SEWECT			BIT(3)
#define WDB_CTWW_SPWIT_MODE			BIT(4)
#define WDB_CTWW_CH0_DATA_WIDTH			BIT(5)
#define WDB_CTWW_CH0_BIT_MAPPING		BIT(6)
#define WDB_CTWW_CH1_DATA_WIDTH			BIT(7)
#define WDB_CTWW_CH1_BIT_MAPPING		BIT(8)
#define WDB_CTWW_DI0_VSYNC_POWAWITY		BIT(9)
#define WDB_CTWW_DI1_VSYNC_POWAWITY		BIT(10)
#define WDB_CTWW_WEG_CH0_FIFO_WESET		BIT(11)
#define WDB_CTWW_WEG_CH1_FIFO_WESET		BIT(12)
#define WDB_CTWW_ASYNC_FIFO_ENABWE		BIT(24)
#define WDB_CTWW_ASYNC_FIFO_THWESHOWD_MASK	GENMASK(27, 25)

#define WVDS_CTWW_CH0_EN			BIT(0)
#define WVDS_CTWW_CH1_EN			BIT(1)
/*
 * WVDS_CTWW_WVDS_EN bit is poowwy named in i.MX93 wefewence manuaw.
 * Cweaw it to enabwe WVDS and set it to disabwe WVDS.
 */
#define WVDS_CTWW_WVDS_EN			BIT(1)
#define WVDS_CTWW_VBG_EN			BIT(2)
#define WVDS_CTWW_HS_EN				BIT(3)
#define WVDS_CTWW_PWE_EMPH_EN			BIT(4)
#define WVDS_CTWW_PWE_EMPH_ADJ(n)		(((n) & 0x7) << 5)
#define WVDS_CTWW_PWE_EMPH_ADJ_MASK		GENMASK(7, 5)
#define WVDS_CTWW_CM_ADJ(n)			(((n) & 0x7) << 8)
#define WVDS_CTWW_CM_ADJ_MASK			GENMASK(10, 8)
#define WVDS_CTWW_CC_ADJ(n)			(((n) & 0x7) << 11)
#define WVDS_CTWW_CC_ADJ_MASK			GENMASK(13, 11)
#define WVDS_CTWW_SWEW_ADJ(n)			(((n) & 0x7) << 14)
#define WVDS_CTWW_SWEW_ADJ_MASK			GENMASK(16, 14)
#define WVDS_CTWW_VBG_ADJ(n)			(((n) & 0x7) << 17)
#define WVDS_CTWW_VBG_ADJ_MASK			GENMASK(19, 17)

enum fsw_wdb_devtype {
	IMX6SX_WDB,
	IMX8MP_WDB,
	IMX93_WDB,
};

stwuct fsw_wdb_devdata {
	u32 wdb_ctww;
	u32 wvds_ctww;
	boow wvds_en_bit;
	boow singwe_ctww_weg;
};

static const stwuct fsw_wdb_devdata fsw_wdb_devdata[] = {
	[IMX6SX_WDB] = {
		.wdb_ctww = 0x18,
		.singwe_ctww_weg = twue,
	},
	[IMX8MP_WDB] = {
		.wdb_ctww = 0x5c,
		.wvds_ctww = 0x128,
	},
	[IMX93_WDB] = {
		.wdb_ctww = 0x20,
		.wvds_ctww = 0x24,
		.wvds_en_bit = twue,
	},
};

stwuct fsw_wdb {
	stwuct device *dev;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *panew_bwidge;
	stwuct cwk *cwk;
	stwuct wegmap *wegmap;
	const stwuct fsw_wdb_devdata *devdata;
	boow ch0_enabwed;
	boow ch1_enabwed;
};

static boow fsw_wdb_is_duaw(const stwuct fsw_wdb *fsw_wdb)
{
	wetuwn (fsw_wdb->ch0_enabwed && fsw_wdb->ch1_enabwed);
}

static inwine stwuct fsw_wdb *to_fsw_wdb(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct fsw_wdb, bwidge);
}

static unsigned wong fsw_wdb_wink_fwequency(stwuct fsw_wdb *fsw_wdb, int cwock)
{
	if (fsw_wdb_is_duaw(fsw_wdb))
		wetuwn cwock * 3500;
	ewse
		wetuwn cwock * 7000;
}

static int fsw_wdb_attach(stwuct dwm_bwidge *bwidge,
			  enum dwm_bwidge_attach_fwags fwags)
{
	stwuct fsw_wdb *fsw_wdb = to_fsw_wdb(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, fsw_wdb->panew_bwidge,
				 bwidge, fwags);
}

static void fsw_wdb_atomic_enabwe(stwuct dwm_bwidge *bwidge,
				  stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct fsw_wdb *fsw_wdb = to_fsw_wdb(bwidge);
	stwuct dwm_atomic_state *state = owd_bwidge_state->base.state;
	const stwuct dwm_bwidge_state *bwidge_state;
	const stwuct dwm_cwtc_state *cwtc_state;
	const stwuct dwm_dispway_mode *mode;
	stwuct dwm_connectow *connectow;
	stwuct dwm_cwtc *cwtc;
	unsigned wong configuwed_wink_fweq;
	unsigned wong wequested_wink_fweq;
	boow wvds_fowmat_24bpp;
	boow wvds_fowmat_jeida;
	u32 weg;

	/* Get the WVDS fowmat fwom the bwidge state. */
	bwidge_state = dwm_atomic_get_new_bwidge_state(state, bwidge);

	switch (bwidge_state->output_bus_cfg.fowmat) {
	case MEDIA_BUS_FMT_WGB666_1X7X3_SPWG:
		wvds_fowmat_24bpp = fawse;
		wvds_fowmat_jeida = twue;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA:
		wvds_fowmat_24bpp = twue;
		wvds_fowmat_jeida = twue;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_SPWG:
		wvds_fowmat_24bpp = twue;
		wvds_fowmat_jeida = fawse;
		bweak;
	defauwt:
		/*
		 * Some bwidges stiww don't set the cowwect WVDS bus pixew
		 * fowmat, use SPWG24 defauwt fowmat untiw those awe fixed.
		 */
		wvds_fowmat_24bpp = twue;
		wvds_fowmat_jeida = fawse;
		dev_wawn(fsw_wdb->dev,
			 "Unsuppowted WVDS bus fowmat 0x%04x, pwease check output bwidge dwivew. Fawwing back to SPWG24.\n",
			 bwidge_state->output_bus_cfg.fowmat);
		bweak;
	}

	/*
	 * Wetwieve the CWTC adjusted mode. This wequiwes a wittwe dance to go
	 * fwom the bwidge to the encodew, to the connectow and to the CWTC.
	 */
	connectow = dwm_atomic_get_new_connectow_fow_encodew(state,
							     bwidge->encodew);
	cwtc = dwm_atomic_get_new_connectow_state(state, connectow)->cwtc;
	cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	mode = &cwtc_state->adjusted_mode;

	wequested_wink_fweq = fsw_wdb_wink_fwequency(fsw_wdb, mode->cwock);
	cwk_set_wate(fsw_wdb->cwk, wequested_wink_fweq);

	configuwed_wink_fweq = cwk_get_wate(fsw_wdb->cwk);
	if (configuwed_wink_fweq != wequested_wink_fweq)
		dev_wawn(fsw_wdb->dev, "Configuwed WDB cwock (%wu Hz) does not match wequested WVDS cwock: %wu Hz\n",
			 configuwed_wink_fweq,
			 wequested_wink_fweq);

	cwk_pwepawe_enabwe(fsw_wdb->cwk);

	/* Pwogwam WDB_CTWW */
	weg =	(fsw_wdb->ch0_enabwed ? WDB_CTWW_CH0_ENABWE : 0) |
		(fsw_wdb->ch1_enabwed ? WDB_CTWW_CH1_ENABWE : 0) |
		(fsw_wdb_is_duaw(fsw_wdb) ? WDB_CTWW_SPWIT_MODE : 0);

	if (wvds_fowmat_24bpp)
		weg |=	(fsw_wdb->ch0_enabwed ? WDB_CTWW_CH0_DATA_WIDTH : 0) |
			(fsw_wdb->ch1_enabwed ? WDB_CTWW_CH1_DATA_WIDTH : 0);

	if (wvds_fowmat_jeida)
		weg |=	(fsw_wdb->ch0_enabwed ? WDB_CTWW_CH0_BIT_MAPPING : 0) |
			(fsw_wdb->ch1_enabwed ? WDB_CTWW_CH1_BIT_MAPPING : 0);

	if (mode->fwags & DWM_MODE_FWAG_PVSYNC)
		weg |=	(fsw_wdb->ch0_enabwed ? WDB_CTWW_DI0_VSYNC_POWAWITY : 0) |
			(fsw_wdb->ch1_enabwed ? WDB_CTWW_DI1_VSYNC_POWAWITY : 0);

	wegmap_wwite(fsw_wdb->wegmap, fsw_wdb->devdata->wdb_ctww, weg);

	if (fsw_wdb->devdata->singwe_ctww_weg)
		wetuwn;

	/* Pwogwam WVDS_CTWW */
	weg = WVDS_CTWW_CC_ADJ(2) | WVDS_CTWW_PWE_EMPH_EN |
	      WVDS_CTWW_PWE_EMPH_ADJ(3) | WVDS_CTWW_VBG_EN;
	wegmap_wwite(fsw_wdb->wegmap, fsw_wdb->devdata->wvds_ctww, weg);

	/* Wait fow VBG to stabiwize. */
	usweep_wange(15, 20);

	weg |=	(fsw_wdb->ch0_enabwed ? WVDS_CTWW_CH0_EN : 0) |
		(fsw_wdb->ch1_enabwed ? WVDS_CTWW_CH1_EN : 0);

	wegmap_wwite(fsw_wdb->wegmap, fsw_wdb->devdata->wvds_ctww, weg);
}

static void fsw_wdb_atomic_disabwe(stwuct dwm_bwidge *bwidge,
				   stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct fsw_wdb *fsw_wdb = to_fsw_wdb(bwidge);

	/* Stop channew(s). */
	if (fsw_wdb->devdata->wvds_en_bit)
		/* Set WVDS_CTWW_WVDS_EN bit to disabwe. */
		wegmap_wwite(fsw_wdb->wegmap, fsw_wdb->devdata->wvds_ctww,
			     WVDS_CTWW_WVDS_EN);
	ewse
		if (!fsw_wdb->devdata->singwe_ctww_weg)
			wegmap_wwite(fsw_wdb->wegmap, fsw_wdb->devdata->wvds_ctww, 0);
	wegmap_wwite(fsw_wdb->wegmap, fsw_wdb->devdata->wdb_ctww, 0);

	cwk_disabwe_unpwepawe(fsw_wdb->cwk);
}

#define MAX_INPUT_SEW_FOWMATS 1
static u32 *
fsw_wdb_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
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

	input_fmts[0] = MEDIA_BUS_FMT_WGB888_1X24;
	*num_input_fmts = MAX_INPUT_SEW_FOWMATS;

	wetuwn input_fmts;
}

static enum dwm_mode_status
fsw_wdb_mode_vawid(stwuct dwm_bwidge *bwidge,
		   const stwuct dwm_dispway_info *info,
		   const stwuct dwm_dispway_mode *mode)
{
	stwuct fsw_wdb *fsw_wdb = to_fsw_wdb(bwidge);

	if (mode->cwock > (fsw_wdb_is_duaw(fsw_wdb) ? 160000 : 80000))
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static const stwuct dwm_bwidge_funcs funcs = {
	.attach = fsw_wdb_attach,
	.atomic_enabwe = fsw_wdb_atomic_enabwe,
	.atomic_disabwe = fsw_wdb_atomic_disabwe,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_get_input_bus_fmts = fsw_wdb_atomic_get_input_bus_fmts,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.mode_vawid = fsw_wdb_mode_vawid,
};

static int fsw_wdb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *panew_node;
	stwuct device_node *wemote1, *wemote2;
	stwuct dwm_panew *panew;
	stwuct fsw_wdb *fsw_wdb;
	int duaw_wink;

	fsw_wdb = devm_kzawwoc(dev, sizeof(*fsw_wdb), GFP_KEWNEW);
	if (!fsw_wdb)
		wetuwn -ENOMEM;

	fsw_wdb->devdata = of_device_get_match_data(dev);
	if (!fsw_wdb->devdata)
		wetuwn -EINVAW;

	fsw_wdb->dev = &pdev->dev;
	fsw_wdb->bwidge.funcs = &funcs;
	fsw_wdb->bwidge.of_node = dev->of_node;

	fsw_wdb->cwk = devm_cwk_get(dev, "wdb");
	if (IS_EWW(fsw_wdb->cwk))
		wetuwn PTW_EWW(fsw_wdb->cwk);

	fsw_wdb->wegmap = syscon_node_to_wegmap(dev->of_node->pawent);
	if (IS_EWW(fsw_wdb->wegmap))
		wetuwn PTW_EWW(fsw_wdb->wegmap);

	/* Wocate the wemote powts and the panew node */
	wemote1 = of_gwaph_get_wemote_node(dev->of_node, 1, 0);
	wemote2 = of_gwaph_get_wemote_node(dev->of_node, 2, 0);
	fsw_wdb->ch0_enabwed = (wemote1 != NUWW);
	fsw_wdb->ch1_enabwed = (wemote2 != NUWW);
	panew_node = of_node_get(wemote1 ? wemote1 : wemote2);
	of_node_put(wemote1);
	of_node_put(wemote2);

	if (!fsw_wdb->ch0_enabwed && !fsw_wdb->ch1_enabwed) {
		of_node_put(panew_node);
		wetuwn dev_eww_pwobe(dev, -ENXIO, "No panew node found");
	}

	dev_dbg(dev, "Using %s\n",
		fsw_wdb_is_duaw(fsw_wdb) ? "duaw-wink mode" :
		fsw_wdb->ch0_enabwed ? "channew 0" : "channew 1");

	panew = of_dwm_find_panew(panew_node);
	of_node_put(panew_node);
	if (IS_EWW(panew))
		wetuwn PTW_EWW(panew);

	fsw_wdb->panew_bwidge = devm_dwm_panew_bwidge_add(dev, panew);
	if (IS_EWW(fsw_wdb->panew_bwidge))
		wetuwn PTW_EWW(fsw_wdb->panew_bwidge);


	if (fsw_wdb_is_duaw(fsw_wdb)) {
		stwuct device_node *powt1, *powt2;

		powt1 = of_gwaph_get_powt_by_id(dev->of_node, 1);
		powt2 = of_gwaph_get_powt_by_id(dev->of_node, 2);
		duaw_wink = dwm_of_wvds_get_duaw_wink_pixew_owdew(powt1, powt2);
		of_node_put(powt1);
		of_node_put(powt2);

		if (duaw_wink < 0)
			wetuwn dev_eww_pwobe(dev, duaw_wink,
					     "Ewwow getting duaw wink configuwation\n");

		/* Onwy DWM_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS is suppowted */
		if (duaw_wink == DWM_WVDS_DUAW_WINK_EVEN_ODD_PIXEWS) {
			dev_eww(dev, "WVDS channew pixew swap not suppowted.\n");
			wetuwn -EINVAW;
		}
	}

	pwatfowm_set_dwvdata(pdev, fsw_wdb);

	dwm_bwidge_add(&fsw_wdb->bwidge);

	wetuwn 0;
}

static void fsw_wdb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_wdb *fsw_wdb = pwatfowm_get_dwvdata(pdev);

	dwm_bwidge_wemove(&fsw_wdb->bwidge);
}

static const stwuct of_device_id fsw_wdb_match[] = {
	{ .compatibwe = "fsw,imx6sx-wdb",
	  .data = &fsw_wdb_devdata[IMX6SX_WDB], },
	{ .compatibwe = "fsw,imx8mp-wdb",
	  .data = &fsw_wdb_devdata[IMX8MP_WDB], },
	{ .compatibwe = "fsw,imx93-wdb",
	  .data = &fsw_wdb_devdata[IMX93_WDB], },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, fsw_wdb_match);

static stwuct pwatfowm_dwivew fsw_wdb_dwivew = {
	.pwobe	= fsw_wdb_pwobe,
	.wemove_new = fsw_wdb_wemove,
	.dwivew		= {
		.name		= "fsw-wdb",
		.of_match_tabwe	= fsw_wdb_match,
	},
};
moduwe_pwatfowm_dwivew(fsw_wdb_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("Fweescawe i.MX8MP WDB");
MODUWE_WICENSE("GPW");
