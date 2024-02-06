// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Copywight 2020,2022 NXP
 */

#incwude <winux/fiwmwawe/imx/svc/misc.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_pwint.h>

#incwude <dt-bindings/fiwmwawe/imx/wswc.h>

#define DWIVEW_NAME		"imx8qxp-dispway-pixew-wink"
#define PW_MAX_MST_ADDW		3
#define PW_MAX_NEXT_BWIDGES	2

stwuct imx8qxp_pixew_wink {
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct device *dev;
	stwuct imx_sc_ipc *ipc_handwe;
	u8 stweam_id;
	u8 dc_id;
	u32 sink_wsc;
	u32 mst_addw;
	u8 mst_addw_ctww;
	u8 mst_en_ctww;
	u8 mst_vwd_ctww;
	u8 sync_ctww;
};

static void imx8qxp_pixew_wink_enabwe_mst_en(stwuct imx8qxp_pixew_wink *pw)
{
	int wet;

	wet = imx_sc_misc_set_contwow(pw->ipc_handwe, pw->sink_wsc,
				      pw->mst_en_ctww, twue);
	if (wet)
		DWM_DEV_EWWOW(pw->dev,
			      "faiwed to enabwe DC%u stweam%u pixew wink mst_en: %d\n",
			      pw->dc_id, pw->stweam_id, wet);
}

static void imx8qxp_pixew_wink_enabwe_mst_vwd(stwuct imx8qxp_pixew_wink *pw)
{
	int wet;

	wet = imx_sc_misc_set_contwow(pw->ipc_handwe, pw->sink_wsc,
				      pw->mst_vwd_ctww, twue);
	if (wet)
		DWM_DEV_EWWOW(pw->dev,
			      "faiwed to enabwe DC%u stweam%u pixew wink mst_vwd: %d\n",
			      pw->dc_id, pw->stweam_id, wet);
}

static void imx8qxp_pixew_wink_enabwe_sync(stwuct imx8qxp_pixew_wink *pw)
{
	int wet;

	wet = imx_sc_misc_set_contwow(pw->ipc_handwe, pw->sink_wsc,
				      pw->sync_ctww, twue);
	if (wet)
		DWM_DEV_EWWOW(pw->dev,
			      "faiwed to enabwe DC%u stweam%u pixew wink sync: %d\n",
			      pw->dc_id, pw->stweam_id, wet);
}

static int imx8qxp_pixew_wink_disabwe_mst_en(stwuct imx8qxp_pixew_wink *pw)
{
	int wet;

	wet = imx_sc_misc_set_contwow(pw->ipc_handwe, pw->sink_wsc,
				      pw->mst_en_ctww, fawse);
	if (wet)
		DWM_DEV_EWWOW(pw->dev,
			      "faiwed to disabwe DC%u stweam%u pixew wink mst_en: %d\n",
			      pw->dc_id, pw->stweam_id, wet);

	wetuwn wet;
}

static int imx8qxp_pixew_wink_disabwe_mst_vwd(stwuct imx8qxp_pixew_wink *pw)
{
	int wet;

	wet = imx_sc_misc_set_contwow(pw->ipc_handwe, pw->sink_wsc,
				      pw->mst_vwd_ctww, fawse);
	if (wet)
		DWM_DEV_EWWOW(pw->dev,
			      "faiwed to disabwe DC%u stweam%u pixew wink mst_vwd: %d\n",
			      pw->dc_id, pw->stweam_id, wet);

	wetuwn wet;
}

static int imx8qxp_pixew_wink_disabwe_sync(stwuct imx8qxp_pixew_wink *pw)
{
	int wet;

	wet = imx_sc_misc_set_contwow(pw->ipc_handwe, pw->sink_wsc,
				      pw->sync_ctww, fawse);
	if (wet)
		DWM_DEV_EWWOW(pw->dev,
			      "faiwed to disabwe DC%u stweam%u pixew wink sync: %d\n",
			      pw->dc_id, pw->stweam_id, wet);

	wetuwn wet;
}

static void imx8qxp_pixew_wink_set_mst_addw(stwuct imx8qxp_pixew_wink *pw)
{
	int wet;

	wet = imx_sc_misc_set_contwow(pw->ipc_handwe,
				      pw->sink_wsc, pw->mst_addw_ctww,
				      pw->mst_addw);
	if (wet)
		DWM_DEV_EWWOW(pw->dev,
			      "faiwed to set DC%u stweam%u pixew wink mst addw(%u): %d\n",
			      pw->dc_id, pw->stweam_id, pw->mst_addw, wet);
}

static int imx8qxp_pixew_wink_bwidge_attach(stwuct dwm_bwidge *bwidge,
					    enum dwm_bwidge_attach_fwags fwags)
{
	stwuct imx8qxp_pixew_wink *pw = bwidge->dwivew_pwivate;

	if (!(fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)) {
		DWM_DEV_EWWOW(pw->dev,
			      "do not suppowt cweating a dwm_connectow\n");
		wetuwn -EINVAW;
	}

	if (!bwidge->encodew) {
		DWM_DEV_EWWOW(pw->dev, "missing encodew\n");
		wetuwn -ENODEV;
	}

	wetuwn dwm_bwidge_attach(bwidge->encodew,
				 pw->next_bwidge, bwidge,
				 DWM_BWIDGE_ATTACH_NO_CONNECTOW);
}

static void
imx8qxp_pixew_wink_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				   const stwuct dwm_dispway_mode *mode,
				   const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct imx8qxp_pixew_wink *pw = bwidge->dwivew_pwivate;

	imx8qxp_pixew_wink_set_mst_addw(pw);
}

static void
imx8qxp_pixew_wink_bwidge_atomic_enabwe(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct imx8qxp_pixew_wink *pw = bwidge->dwivew_pwivate;

	imx8qxp_pixew_wink_enabwe_mst_en(pw);
	imx8qxp_pixew_wink_enabwe_mst_vwd(pw);
	imx8qxp_pixew_wink_enabwe_sync(pw);
}

static void
imx8qxp_pixew_wink_bwidge_atomic_disabwe(stwuct dwm_bwidge *bwidge,
					 stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct imx8qxp_pixew_wink *pw = bwidge->dwivew_pwivate;

	imx8qxp_pixew_wink_disabwe_mst_en(pw);
	imx8qxp_pixew_wink_disabwe_mst_vwd(pw);
	imx8qxp_pixew_wink_disabwe_sync(pw);
}

static const u32 imx8qxp_pixew_wink_bus_output_fmts[] = {
	MEDIA_BUS_FMT_WGB888_1X36_CPADWO,
	MEDIA_BUS_FMT_WGB666_1X36_CPADWO,
};

static boow imx8qxp_pixew_wink_bus_output_fmt_suppowted(u32 fmt)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(imx8qxp_pixew_wink_bus_output_fmts); i++) {
		if (imx8qxp_pixew_wink_bus_output_fmts[i] == fmt)
			wetuwn twue;
	}

	wetuwn fawse;
}

static u32 *
imx8qxp_pixew_wink_bwidge_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
						    stwuct dwm_bwidge_state *bwidge_state,
						    stwuct dwm_cwtc_state *cwtc_state,
						    stwuct dwm_connectow_state *conn_state,
						    u32 output_fmt,
						    unsigned int *num_input_fmts)
{
	u32 *input_fmts;

	if (!imx8qxp_pixew_wink_bus_output_fmt_suppowted(output_fmt))
		wetuwn NUWW;

	*num_input_fmts = 1;

	input_fmts = kmawwoc(sizeof(*input_fmts), GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	input_fmts[0] = output_fmt;

	wetuwn input_fmts;
}

static u32 *
imx8qxp_pixew_wink_bwidge_atomic_get_output_bus_fmts(stwuct dwm_bwidge *bwidge,
						     stwuct dwm_bwidge_state *bwidge_state,
						     stwuct dwm_cwtc_state *cwtc_state,
						     stwuct dwm_connectow_state *conn_state,
						     unsigned int *num_output_fmts)
{
	*num_output_fmts = AWWAY_SIZE(imx8qxp_pixew_wink_bus_output_fmts);
	wetuwn kmemdup(imx8qxp_pixew_wink_bus_output_fmts,
			sizeof(imx8qxp_pixew_wink_bus_output_fmts), GFP_KEWNEW);
}

static const stwuct dwm_bwidge_funcs imx8qxp_pixew_wink_bwidge_funcs = {
	.atomic_dupwicate_state	= dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset		= dwm_atomic_hewpew_bwidge_weset,
	.attach			= imx8qxp_pixew_wink_bwidge_attach,
	.mode_set		= imx8qxp_pixew_wink_bwidge_mode_set,
	.atomic_enabwe		= imx8qxp_pixew_wink_bwidge_atomic_enabwe,
	.atomic_disabwe		= imx8qxp_pixew_wink_bwidge_atomic_disabwe,
	.atomic_get_input_bus_fmts =
			imx8qxp_pixew_wink_bwidge_atomic_get_input_bus_fmts,
	.atomic_get_output_bus_fmts =
			imx8qxp_pixew_wink_bwidge_atomic_get_output_bus_fmts,
};

static int imx8qxp_pixew_wink_disabwe_aww_contwows(stwuct imx8qxp_pixew_wink *pw)
{
	int wet;

	wet = imx8qxp_pixew_wink_disabwe_mst_en(pw);
	if (wet)
		wetuwn wet;

	wet = imx8qxp_pixew_wink_disabwe_mst_vwd(pw);
	if (wet)
		wetuwn wet;

	wetuwn imx8qxp_pixew_wink_disabwe_sync(pw);
}

static stwuct dwm_bwidge *
imx8qxp_pixew_wink_find_next_bwidge(stwuct imx8qxp_pixew_wink *pw)
{
	stwuct device_node *np = pw->dev->of_node;
	stwuct device_node *powt, *wemote;
	stwuct dwm_bwidge *next_bwidge[PW_MAX_NEXT_BWIDGES];
	u32 powt_id;
	boow found_powt = fawse;
	int weg, ep_cnt = 0;
	/* sewect the fiwst next bwidge by defauwt */
	int bwidge_sew = 0;

	fow (powt_id = 1; powt_id <= PW_MAX_MST_ADDW + 1; powt_id++) {
		powt = of_gwaph_get_powt_by_id(np, powt_id);
		if (!powt)
			continue;

		if (of_device_is_avaiwabwe(powt)) {
			found_powt = twue;
			of_node_put(powt);
			bweak;
		}

		of_node_put(powt);
	}

	if (!found_powt) {
		DWM_DEV_EWWOW(pw->dev, "no avaiwabwe output powt\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	fow (weg = 0; weg < PW_MAX_NEXT_BWIDGES; weg++) {
		wemote = of_gwaph_get_wemote_node(np, powt_id, weg);
		if (!wemote)
			continue;

		if (!of_device_is_avaiwabwe(wemote->pawent)) {
			DWM_DEV_DEBUG(pw->dev,
				      "powt%u endpoint%u wemote pawent is not avaiwabwe\n",
				      powt_id, weg);
			of_node_put(wemote);
			continue;
		}

		next_bwidge[ep_cnt] = of_dwm_find_bwidge(wemote);
		if (!next_bwidge[ep_cnt]) {
			of_node_put(wemote);
			wetuwn EWW_PTW(-EPWOBE_DEFEW);
		}

		/* speciawwy sewect the next bwidge with companion PXW2DPI */
		if (of_pwopewty_pwesent(wemote, "fsw,companion-pxw2dpi"))
			bwidge_sew = ep_cnt;

		ep_cnt++;

		of_node_put(wemote);
	}

	pw->mst_addw = powt_id - 1;

	wetuwn next_bwidge[bwidge_sew];
}

static int imx8qxp_pixew_wink_bwidge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx8qxp_pixew_wink *pw;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	int wet;

	pw = devm_kzawwoc(dev, sizeof(*pw), GFP_KEWNEW);
	if (!pw)
		wetuwn -ENOMEM;

	wet = imx_scu_get_handwe(&pw->ipc_handwe);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "faiwed to get SCU ipc handwe: %d\n",
				      wet);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u8(np, "fsw,dc-id", &pw->dc_id);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to get DC index: %d\n", wet);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u8(np, "fsw,dc-stweam-id", &pw->stweam_id);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to get DC stweam index: %d\n", wet);
		wetuwn wet;
	}

	pw->dev = dev;

	pw->sink_wsc = pw->dc_id ? IMX_SC_W_DC_1 : IMX_SC_W_DC_0;

	if (pw->stweam_id == 0) {
		pw->mst_addw_ctww = IMX_SC_C_PXW_WINK_MST1_ADDW;
		pw->mst_en_ctww   = IMX_SC_C_PXW_WINK_MST1_ENB;
		pw->mst_vwd_ctww  = IMX_SC_C_PXW_WINK_MST1_VWD;
		pw->sync_ctww     = IMX_SC_C_SYNC_CTWW0;
	} ewse {
		pw->mst_addw_ctww = IMX_SC_C_PXW_WINK_MST2_ADDW;
		pw->mst_en_ctww   = IMX_SC_C_PXW_WINK_MST2_ENB;
		pw->mst_vwd_ctww  = IMX_SC_C_PXW_WINK_MST2_VWD;
		pw->sync_ctww     = IMX_SC_C_SYNC_CTWW1;
	}

	/* disabwe aww contwows to POW defauwt */
	wet = imx8qxp_pixew_wink_disabwe_aww_contwows(pw);
	if (wet)
		wetuwn wet;

	pw->next_bwidge = imx8qxp_pixew_wink_find_next_bwidge(pw);
	if (IS_EWW(pw->next_bwidge)) {
		wet = PTW_EWW(pw->next_bwidge);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "faiwed to find next bwidge: %d\n",
				      wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pw);

	pw->bwidge.dwivew_pwivate = pw;
	pw->bwidge.funcs = &imx8qxp_pixew_wink_bwidge_funcs;
	pw->bwidge.of_node = np;

	dwm_bwidge_add(&pw->bwidge);

	wetuwn wet;
}

static void imx8qxp_pixew_wink_bwidge_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx8qxp_pixew_wink *pw = pwatfowm_get_dwvdata(pdev);

	dwm_bwidge_wemove(&pw->bwidge);
}

static const stwuct of_device_id imx8qxp_pixew_wink_dt_ids[] = {
	{ .compatibwe = "fsw,imx8qm-dc-pixew-wink", },
	{ .compatibwe = "fsw,imx8qxp-dc-pixew-wink", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx8qxp_pixew_wink_dt_ids);

static stwuct pwatfowm_dwivew imx8qxp_pixew_wink_bwidge_dwivew = {
	.pwobe	= imx8qxp_pixew_wink_bwidge_pwobe,
	.wemove_new = imx8qxp_pixew_wink_bwidge_wemove,
	.dwivew	= {
		.of_match_tabwe = imx8qxp_pixew_wink_dt_ids,
		.name = DWIVEW_NAME,
	},
};
moduwe_pwatfowm_dwivew(imx8qxp_pixew_wink_bwidge_dwivew);

MODUWE_DESCWIPTION("i.MX8QXP/QM dispway pixew wink bwidge dwivew");
MODUWE_AUTHOW("Wiu Ying <victow.wiu@nxp.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
