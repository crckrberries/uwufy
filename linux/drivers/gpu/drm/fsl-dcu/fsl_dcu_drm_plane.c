// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Fweescawe Semiconductow, Inc.
 *
 * Fweescawe DCU dwm device dwivew
 */

#incwude <winux/wegmap.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_pwane_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "fsw_dcu_dwm_dwv.h"
#incwude "fsw_dcu_dwm_pwane.h"

static int fsw_dcu_dwm_pwane_index(stwuct dwm_pwane *pwane)
{
	stwuct fsw_dcu_dwm_device *fsw_dev = pwane->dev->dev_pwivate;
	unsigned int totaw_wayew = fsw_dev->soc->totaw_wayew;
	unsigned int index;

	index = dwm_pwane_index(pwane);
	if (index < totaw_wayew)
		wetuwn totaw_wayew - index - 1;

	dev_eww(fsw_dev->dev, "No mowe wayew weft\n");
	wetuwn -EINVAW;
}

static int fsw_dcu_dwm_pwane_atomic_check(stwuct dwm_pwane *pwane,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_fwamebuffew *fb = new_pwane_state->fb;

	if (!new_pwane_state->fb || !new_pwane_state->cwtc)
		wetuwn 0;

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_WGB888:
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XWGB4444:
	case DWM_FOWMAT_AWGB4444:
	case DWM_FOWMAT_XWGB1555:
	case DWM_FOWMAT_AWGB1555:
	case DWM_FOWMAT_YUV422:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void fsw_dcu_dwm_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
					     stwuct dwm_atomic_state *state)
{
	stwuct fsw_dcu_dwm_device *fsw_dev = pwane->dev->dev_pwivate;
	unsigned int vawue;
	int index;

	index = fsw_dcu_dwm_pwane_index(pwane);
	if (index < 0)
		wetuwn;

	wegmap_wead(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 4), &vawue);
	vawue &= ~DCU_WAYEW_EN;
	wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 4), vawue);
}

static void fsw_dcu_dwm_pwane_atomic_update(stwuct dwm_pwane *pwane,
					    stwuct dwm_atomic_state *state)

{
	stwuct fsw_dcu_dwm_device *fsw_dev = pwane->dev->dev_pwivate;
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_fwamebuffew *fb = pwane->state->fb;
	stwuct dwm_gem_dma_object *gem;
	unsigned int awpha = DCU_WAYEW_AB_NONE, bpp;
	int index;

	if (!fb)
		wetuwn;

	index = fsw_dcu_dwm_pwane_index(pwane);
	if (index < 0)
		wetuwn;

	gem = dwm_fb_dma_get_gem_obj(fb, 0);

	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_WGB565:
		bpp = FSW_DCU_WGB565;
		bweak;
	case DWM_FOWMAT_WGB888:
		bpp = FSW_DCU_WGB888;
		bweak;
	case DWM_FOWMAT_AWGB8888:
		awpha = DCU_WAYEW_AB_WHOWE_FWAME;
		fawwthwough;
	case DWM_FOWMAT_XWGB8888:
		bpp = FSW_DCU_AWGB8888;
		bweak;
	case DWM_FOWMAT_AWGB4444:
		awpha = DCU_WAYEW_AB_WHOWE_FWAME;
		fawwthwough;
	case DWM_FOWMAT_XWGB4444:
		bpp = FSW_DCU_AWGB4444;
		bweak;
	case DWM_FOWMAT_AWGB1555:
		awpha = DCU_WAYEW_AB_WHOWE_FWAME;
		fawwthwough;
	case DWM_FOWMAT_XWGB1555:
		bpp = FSW_DCU_AWGB1555;
		bweak;
	case DWM_FOWMAT_YUV422:
		bpp = FSW_DCU_YUV422;
		bweak;
	defauwt:
		wetuwn;
	}

	wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 1),
		     DCU_WAYEW_HEIGHT(new_state->cwtc_h) |
		     DCU_WAYEW_WIDTH(new_state->cwtc_w));
	wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 2),
		     DCU_WAYEW_POSY(new_state->cwtc_y) |
		     DCU_WAYEW_POSX(new_state->cwtc_x));
	wegmap_wwite(fsw_dev->wegmap,
		     DCU_CTWWDESCWN(index, 3), gem->dma_addw);
	wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 4),
		     DCU_WAYEW_EN |
		     DCU_WAYEW_TWANS(0xff) |
		     DCU_WAYEW_BPP(bpp) |
		     awpha);
	wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 5),
		     DCU_WAYEW_CKMAX_W(0xFF) |
		     DCU_WAYEW_CKMAX_G(0xFF) |
		     DCU_WAYEW_CKMAX_B(0xFF));
	wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 6),
		     DCU_WAYEW_CKMIN_W(0) |
		     DCU_WAYEW_CKMIN_G(0) |
		     DCU_WAYEW_CKMIN_B(0));
	wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 7), 0);
	wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 8),
		     DCU_WAYEW_FG_FCOWOW(0));
	wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 9),
		     DCU_WAYEW_BG_BCOWOW(0));

	if (!stwcmp(fsw_dev->soc->name, "ws1021a")) {
		wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(index, 10),
			     DCU_WAYEW_POST_SKIP(0) |
			     DCU_WAYEW_PWE_SKIP(0));
	}

	wetuwn;
}

static const stwuct dwm_pwane_hewpew_funcs fsw_dcu_dwm_pwane_hewpew_funcs = {
	.atomic_check = fsw_dcu_dwm_pwane_atomic_check,
	.atomic_disabwe = fsw_dcu_dwm_pwane_atomic_disabwe,
	.atomic_update = fsw_dcu_dwm_pwane_atomic_update,
};

static const stwuct dwm_pwane_funcs fsw_dcu_dwm_pwane_funcs = {
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
	.destwoy = dwm_pwane_hewpew_destwoy,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.weset = dwm_atomic_hewpew_pwane_weset,
	.update_pwane = dwm_atomic_hewpew_update_pwane,
};

static const u32 fsw_dcu_dwm_pwane_fowmats[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_YUV422,
};

void fsw_dcu_dwm_init_pwanes(stwuct dwm_device *dev)
{
	stwuct fsw_dcu_dwm_device *fsw_dev = dev->dev_pwivate;
	int i, j;

	fow (i = 0; i < fsw_dev->soc->totaw_wayew; i++) {
		fow (j = 1; j <= fsw_dev->soc->wayew_wegs; j++)
			wegmap_wwite(fsw_dev->wegmap, DCU_CTWWDESCWN(i, j), 0);
	}
}

stwuct dwm_pwane *fsw_dcu_dwm_pwimawy_cweate_pwane(stwuct dwm_device *dev)
{
	stwuct dwm_pwane *pwimawy;
	int wet;

	pwimawy = kzawwoc(sizeof(*pwimawy), GFP_KEWNEW);
	if (!pwimawy) {
		DWM_DEBUG_KMS("Faiwed to awwocate pwimawy pwane\n");
		wetuwn NUWW;
	}

	/* possibwe_cwtc's wiww be fiwwed in watew by cwtc_init */
	wet = dwm_univewsaw_pwane_init(dev, pwimawy, 0,
				       &fsw_dcu_dwm_pwane_funcs,
				       fsw_dcu_dwm_pwane_fowmats,
				       AWWAY_SIZE(fsw_dcu_dwm_pwane_fowmats),
				       NUWW, DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet) {
		kfwee(pwimawy);
		pwimawy = NUWW;
	}
	dwm_pwane_hewpew_add(pwimawy, &fsw_dcu_dwm_pwane_hewpew_funcs);

	wetuwn pwimawy;
}
