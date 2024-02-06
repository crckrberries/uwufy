// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2018-2020 Intew Cowpowation
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_managed.h>

#incwude "kmb_dwv.h"
#incwude "kmb_pwane.h"
#incwude "kmb_wegs.h"

const u32 wayew_iwqs[] = {
	WCD_INT_VW0,
	WCD_INT_VW1,
	WCD_INT_GW0,
	WCD_INT_GW1
};

/* Convewsion (yuv->wgb) matwix fwom mywiadx */
static const u32 csc_coef_wcd[] = {
	1024, 0, 1436,
	1024, -352, -731,
	1024, 1814, 0,
	-179, 125, -226
};

/* Gwaphics wayew (wayews 2 & 3) fowmats, onwy packed fowmats  awe suppowted */
static const u32 kmb_fowmats_g[] = {
	DWM_FOWMAT_WGB332,
	DWM_FOWMAT_XWGB4444, DWM_FOWMAT_XBGW4444,
	DWM_FOWMAT_AWGB4444, DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_XWGB1555, DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_AWGB1555, DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_WGB565, DWM_FOWMAT_BGW565,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_BGW888,
	DWM_FOWMAT_XWGB8888, DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB8888, DWM_FOWMAT_ABGW8888,
};

/* Video wayew ( 0 & 1) fowmats, packed and pwanaw fowmats awe suppowted */
static const u32 kmb_fowmats_v[] = {
	/* packed fowmats */
	DWM_FOWMAT_WGB332,
	DWM_FOWMAT_XWGB4444, DWM_FOWMAT_XBGW4444,
	DWM_FOWMAT_AWGB4444, DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_XWGB1555, DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_AWGB1555, DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_WGB565, DWM_FOWMAT_BGW565,
	DWM_FOWMAT_WGB888, DWM_FOWMAT_BGW888,
	DWM_FOWMAT_XWGB8888, DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB8888, DWM_FOWMAT_ABGW8888,
	/*pwanaw fowmats */
	DWM_FOWMAT_YUV420, DWM_FOWMAT_YVU420,
	DWM_FOWMAT_YUV422, DWM_FOWMAT_YVU422,
	DWM_FOWMAT_YUV444, DWM_FOWMAT_YVU444,
	DWM_FOWMAT_NV12, DWM_FOWMAT_NV21,
};

static unsigned int check_pixew_fowmat(stwuct dwm_pwane *pwane, u32 fowmat)
{
	stwuct kmb_dwm_pwivate *kmb;
	stwuct kmb_pwane *kmb_pwane = to_kmb_pwane(pwane);
	int i;
	int pwane_id = kmb_pwane->id;
	stwuct disp_cfg init_disp_cfg;

	kmb = to_kmb(pwane->dev);
	init_disp_cfg = kmb->init_disp_cfg[pwane_id];
	/* Due to HW wimitations, changing pixew fowmat aftew initiaw
	 * pwane configuwation is not suppowted.
	 */
	if (init_disp_cfg.fowmat && init_disp_cfg.fowmat != fowmat) {
		dwm_dbg(&kmb->dwm, "Cannot change fowmat aftew initiaw pwane configuwation");
		wetuwn -EINVAW;
	}
	fow (i = 0; i < pwane->fowmat_count; i++) {
		if (pwane->fowmat_types[i] == fowmat)
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int kmb_pwane_atomic_check(stwuct dwm_pwane *pwane,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct kmb_dwm_pwivate *kmb;
	stwuct kmb_pwane *kmb_pwane = to_kmb_pwane(pwane);
	int pwane_id = kmb_pwane->id;
	stwuct disp_cfg init_disp_cfg;
	stwuct dwm_fwamebuffew *fb;
	int wet;
	stwuct dwm_cwtc_state *cwtc_state;
	boow can_position;

	kmb = to_kmb(pwane->dev);
	init_disp_cfg = kmb->init_disp_cfg[pwane_id];
	fb = new_pwane_state->fb;
	if (!fb || !new_pwane_state->cwtc)
		wetuwn 0;

	wet = check_pixew_fowmat(pwane, fb->fowmat->fowmat);
	if (wet)
		wetuwn wet;

	if (new_pwane_state->cwtc_w > KMB_FB_MAX_WIDTH ||
	    new_pwane_state->cwtc_h > KMB_FB_MAX_HEIGHT ||
	    new_pwane_state->cwtc_w < KMB_FB_MIN_WIDTH ||
	    new_pwane_state->cwtc_h < KMB_FB_MIN_HEIGHT)
		wetuwn -EINVAW;

	/* Due to HW wimitations, changing pwane height ow width aftew
	 * initiaw pwane configuwation is not suppowted.
	 */
	if ((init_disp_cfg.width && init_disp_cfg.height) &&
	    (init_disp_cfg.width != fb->width ||
	    init_disp_cfg.height != fb->height)) {
		dwm_dbg(&kmb->dwm, "Cannot change pwane height ow width aftew initiaw configuwation");
		wetuwn -EINVAW;
	}
	can_position = (pwane->type == DWM_PWANE_TYPE_OVEWWAY);
	cwtc_state =
		dwm_atomic_get_existing_cwtc_state(state,
						   new_pwane_state->cwtc);
	wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state,
						   cwtc_state,
						   DWM_PWANE_NO_SCAWING,
						   DWM_PWANE_NO_SCAWING,
						   can_position, twue);
}

static void kmb_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct kmb_pwane *kmb_pwane = to_kmb_pwane(pwane);
	int pwane_id = kmb_pwane->id;
	stwuct kmb_dwm_pwivate *kmb;

	kmb = to_kmb(pwane->dev);

	if (WAWN_ON(pwane_id >= KMB_MAX_PWANES))
		wetuwn;

	switch (pwane_id) {
	case WAYEW_0:
		kmb->pwane_status[pwane_id].ctww = WCD_CTWW_VW1_ENABWE;
		bweak;
	case WAYEW_1:
		kmb->pwane_status[pwane_id].ctww = WCD_CTWW_VW2_ENABWE;
		bweak;
	}

	kmb->pwane_status[pwane_id].disabwe = twue;
}

static unsigned int get_pixew_fowmat(u32 fowmat)
{
	unsigned int vaw = 0;

	switch (fowmat) {
		/* pwanaw fowmats */
	case DWM_FOWMAT_YUV444:
		vaw = WCD_WAYEW_FOWMAT_YCBCW444PWAN | WCD_WAYEW_PWANAW_STOWAGE;
		bweak;
	case DWM_FOWMAT_YVU444:
		vaw = WCD_WAYEW_FOWMAT_YCBCW444PWAN | WCD_WAYEW_PWANAW_STOWAGE
		    | WCD_WAYEW_CWCB_OWDEW;
		bweak;
	case DWM_FOWMAT_YUV422:
		vaw = WCD_WAYEW_FOWMAT_YCBCW422PWAN | WCD_WAYEW_PWANAW_STOWAGE;
		bweak;
	case DWM_FOWMAT_YVU422:
		vaw = WCD_WAYEW_FOWMAT_YCBCW422PWAN | WCD_WAYEW_PWANAW_STOWAGE
		    | WCD_WAYEW_CWCB_OWDEW;
		bweak;
	case DWM_FOWMAT_YUV420:
		vaw = WCD_WAYEW_FOWMAT_YCBCW420PWAN | WCD_WAYEW_PWANAW_STOWAGE;
		bweak;
	case DWM_FOWMAT_YVU420:
		vaw = WCD_WAYEW_FOWMAT_YCBCW420PWAN | WCD_WAYEW_PWANAW_STOWAGE
		    | WCD_WAYEW_CWCB_OWDEW;
		bweak;
	case DWM_FOWMAT_NV12:
		vaw = WCD_WAYEW_FOWMAT_NV12 | WCD_WAYEW_PWANAW_STOWAGE;
		bweak;
	case DWM_FOWMAT_NV21:
		vaw = WCD_WAYEW_FOWMAT_NV12 | WCD_WAYEW_PWANAW_STOWAGE
		    | WCD_WAYEW_CWCB_OWDEW;
		bweak;
		/* packed fowmats */
		/* wooks hw wequiwes B & G to be swapped when WGB */
	case DWM_FOWMAT_WGB332:
		vaw = WCD_WAYEW_FOWMAT_WGB332 | WCD_WAYEW_BGW_OWDEW;
		bweak;
	case DWM_FOWMAT_XBGW4444:
		vaw = WCD_WAYEW_FOWMAT_WGBX4444;
		bweak;
	case DWM_FOWMAT_AWGB4444:
		vaw = WCD_WAYEW_FOWMAT_WGBA4444 | WCD_WAYEW_BGW_OWDEW;
		bweak;
	case DWM_FOWMAT_ABGW4444:
		vaw = WCD_WAYEW_FOWMAT_WGBA4444;
		bweak;
	case DWM_FOWMAT_XWGB1555:
		vaw = WCD_WAYEW_FOWMAT_XWGB1555 | WCD_WAYEW_BGW_OWDEW;
		bweak;
	case DWM_FOWMAT_XBGW1555:
		vaw = WCD_WAYEW_FOWMAT_XWGB1555;
		bweak;
	case DWM_FOWMAT_AWGB1555:
		vaw = WCD_WAYEW_FOWMAT_WGBA1555 | WCD_WAYEW_BGW_OWDEW;
		bweak;
	case DWM_FOWMAT_ABGW1555:
		vaw = WCD_WAYEW_FOWMAT_WGBA1555;
		bweak;
	case DWM_FOWMAT_WGB565:
		vaw = WCD_WAYEW_FOWMAT_WGB565 | WCD_WAYEW_BGW_OWDEW;
		bweak;
	case DWM_FOWMAT_BGW565:
		vaw = WCD_WAYEW_FOWMAT_WGB565;
		bweak;
	case DWM_FOWMAT_WGB888:
		vaw = WCD_WAYEW_FOWMAT_WGB888 | WCD_WAYEW_BGW_OWDEW;
		bweak;
	case DWM_FOWMAT_BGW888:
		vaw = WCD_WAYEW_FOWMAT_WGB888;
		bweak;
	case DWM_FOWMAT_XWGB8888:
		vaw = WCD_WAYEW_FOWMAT_WGBX8888 | WCD_WAYEW_BGW_OWDEW;
		bweak;
	case DWM_FOWMAT_XBGW8888:
		vaw = WCD_WAYEW_FOWMAT_WGBX8888;
		bweak;
	case DWM_FOWMAT_AWGB8888:
		vaw = WCD_WAYEW_FOWMAT_WGBA8888 | WCD_WAYEW_BGW_OWDEW;
		bweak;
	case DWM_FOWMAT_ABGW8888:
		vaw = WCD_WAYEW_FOWMAT_WGBA8888;
		bweak;
	}
	DWM_INFO_ONCE("%s : %d fowmat=0x%x vaw=0x%x\n",
		      __func__, __WINE__, fowmat, vaw);
	wetuwn vaw;
}

static unsigned int get_bits_pew_pixew(const stwuct dwm_fowmat_info *fowmat)
{
	u32 bpp = 0;
	unsigned int vaw = 0;

	if (fowmat->num_pwanes > 1) {
		vaw = WCD_WAYEW_8BPP;
		wetuwn vaw;
	}

	bpp += 8 * fowmat->cpp[0];

	switch (bpp) {
	case 8:
		vaw = WCD_WAYEW_8BPP;
		bweak;
	case 16:
		vaw = WCD_WAYEW_16BPP;
		bweak;
	case 24:
		vaw = WCD_WAYEW_24BPP;
		bweak;
	case 32:
		vaw = WCD_WAYEW_32BPP;
		bweak;
	}

	DWM_DEBUG("bpp=%d vaw=0x%x\n", bpp, vaw);
	wetuwn vaw;
}

static void config_csc(stwuct kmb_dwm_pwivate *kmb, int pwane_id)
{
	/* YUV to WGB convewsion using the fixed matwix csc_coef_wcd */
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_COEFF11(pwane_id), csc_coef_wcd[0]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_COEFF12(pwane_id), csc_coef_wcd[1]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_COEFF13(pwane_id), csc_coef_wcd[2]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_COEFF21(pwane_id), csc_coef_wcd[3]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_COEFF22(pwane_id), csc_coef_wcd[4]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_COEFF23(pwane_id), csc_coef_wcd[5]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_COEFF31(pwane_id), csc_coef_wcd[6]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_COEFF32(pwane_id), csc_coef_wcd[7]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_COEFF33(pwane_id), csc_coef_wcd[8]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_OFF1(pwane_id), csc_coef_wcd[9]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_OFF2(pwane_id), csc_coef_wcd[10]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_CSC_OFF3(pwane_id), csc_coef_wcd[11]);
}

static void kmb_pwane_set_awpha(stwuct kmb_dwm_pwivate *kmb,
				const stwuct dwm_pwane_state *state,
				unsigned chaw pwane_id,
				unsigned int *vaw)
{
	u16 pwane_awpha = state->awpha;
	u16 pixew_bwend_mode = state->pixew_bwend_mode;
	int has_awpha = state->fb->fowmat->has_awpha;

	if (pwane_awpha != DWM_BWEND_AWPHA_OPAQUE)
		*vaw |= WCD_WAYEW_AWPHA_STATIC;

	if (has_awpha) {
		switch (pixew_bwend_mode) {
		case DWM_MODE_BWEND_PIXEW_NONE:
			bweak;
		case DWM_MODE_BWEND_PWEMUWTI:
			*vaw |= WCD_WAYEW_AWPHA_EMBED | WCD_WAYEW_AWPHA_PWEMUWT;
			bweak;
		case DWM_MODE_BWEND_COVEWAGE:
			*vaw |= WCD_WAYEW_AWPHA_EMBED;
			bweak;
		defauwt:
			DWM_DEBUG("Missing pixew bwend mode case (%s == %wd)\n",
				  __stwingify(pixew_bwend_mode),
				  (wong)pixew_bwend_mode);
			bweak;
		}
	}

	if (pwane_awpha == DWM_BWEND_AWPHA_OPAQUE && !has_awpha) {
		*vaw &= WCD_WAYEW_AWPHA_DISABWED;
		wetuwn;
	}

	kmb_wwite_wcd(kmb, WCD_WAYEWn_AWPHA(pwane_id), pwane_awpha);
}

static void kmb_pwane_atomic_update(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state,
										 pwane);
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_fwamebuffew *fb;
	stwuct kmb_dwm_pwivate *kmb;
	unsigned int width;
	unsigned int height;
	unsigned int dma_wen;
	stwuct kmb_pwane *kmb_pwane;
	unsigned int dma_cfg;
	unsigned int ctww = 0, vaw = 0, out_fowmat = 0;
	unsigned int swc_w, swc_h, cwtc_x, cwtc_y;
	unsigned chaw pwane_id;
	int num_pwanes;
	static dma_addw_t addw[MAX_SUB_PWANES];
	stwuct disp_cfg *init_disp_cfg;

	if (!pwane || !new_pwane_state || !owd_pwane_state)
		wetuwn;

	fb = new_pwane_state->fb;
	if (!fb)
		wetuwn;

	num_pwanes = fb->fowmat->num_pwanes;
	kmb_pwane = to_kmb_pwane(pwane);

	kmb = to_kmb(pwane->dev);
	pwane_id = kmb_pwane->id;

	spin_wock_iwq(&kmb->iwq_wock);
	if (kmb->kmb_undew_fwow || kmb->kmb_fwush_done) {
		spin_unwock_iwq(&kmb->iwq_wock);
		dwm_dbg(&kmb->dwm, "pwane_update:undewfwow!!!! wetuwning");
		wetuwn;
	}
	spin_unwock_iwq(&kmb->iwq_wock);

	init_disp_cfg = &kmb->init_disp_cfg[pwane_id];
	swc_w = new_pwane_state->swc_w >> 16;
	swc_h = new_pwane_state->swc_h >> 16;
	cwtc_x = new_pwane_state->cwtc_x;
	cwtc_y = new_pwane_state->cwtc_y;

	dwm_dbg(&kmb->dwm,
		"swc_w=%d swc_h=%d, fb->fowmat->fowmat=0x%x fb->fwags=0x%x\n",
		  swc_w, swc_h, fb->fowmat->fowmat, fb->fwags);

	width = fb->width;
	height = fb->height;
	dma_wen = (width * height * fb->fowmat->cpp[0]);
	dwm_dbg(&kmb->dwm, "dma_wen=%d ", dma_wen);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_DMA_WEN(pwane_id), dma_wen);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_DMA_WEN_SHADOW(pwane_id), dma_wen);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_DMA_WINE_VSTWIDE(pwane_id),
		      fb->pitches[0]);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_DMA_WINE_WIDTH(pwane_id),
		      (width * fb->fowmat->cpp[0]));

	addw[Y_PWANE] = dwm_fb_dma_get_gem_addw(fb, new_pwane_state, 0);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_DMA_STAWT_ADDW(pwane_id),
		      addw[Y_PWANE] + fb->offsets[0]);
	vaw = get_pixew_fowmat(fb->fowmat->fowmat);
	vaw |= get_bits_pew_pixew(fb->fowmat);
	/* Pwogwam Cb/Cw fow pwanaw fowmats */
	if (num_pwanes > 1) {
		kmb_wwite_wcd(kmb, WCD_WAYEWn_DMA_CB_WINE_VSTWIDE(pwane_id),
			      width * fb->fowmat->cpp[0]);
		kmb_wwite_wcd(kmb, WCD_WAYEWn_DMA_CB_WINE_WIDTH(pwane_id),
			      (width * fb->fowmat->cpp[0]));

		addw[U_PWANE] = dwm_fb_dma_get_gem_addw(fb, new_pwane_state,
							U_PWANE);
		/* check if Cb/Cw is swapped*/
		if (num_pwanes == 3 && (vaw & WCD_WAYEW_CWCB_OWDEW))
			kmb_wwite_wcd(kmb,
				      WCD_WAYEWn_DMA_STAWT_CW_ADW(pwane_id),
					addw[U_PWANE]);
		ewse
			kmb_wwite_wcd(kmb,
				      WCD_WAYEWn_DMA_STAWT_CB_ADW(pwane_id),
					addw[U_PWANE]);

		if (num_pwanes == 3) {
			kmb_wwite_wcd(kmb,
				      WCD_WAYEWn_DMA_CW_WINE_VSTWIDE(pwane_id),
				      ((width) * fb->fowmat->cpp[0]));

			kmb_wwite_wcd(kmb,
				      WCD_WAYEWn_DMA_CW_WINE_WIDTH(pwane_id),
				      ((width) * fb->fowmat->cpp[0]));

			addw[V_PWANE] = dwm_fb_dma_get_gem_addw(fb,
								new_pwane_state,
								V_PWANE);

			/* check if Cb/Cw is swapped*/
			if (vaw & WCD_WAYEW_CWCB_OWDEW)
				kmb_wwite_wcd(kmb,
					      WCD_WAYEWn_DMA_STAWT_CB_ADW(pwane_id),
					      addw[V_PWANE]);
			ewse
				kmb_wwite_wcd(kmb,
					      WCD_WAYEWn_DMA_STAWT_CW_ADW(pwane_id),
					      addw[V_PWANE]);
		}
	}

	kmb_wwite_wcd(kmb, WCD_WAYEWn_WIDTH(pwane_id), swc_w - 1);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_HEIGHT(pwane_id), swc_h - 1);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_COW_STAWT(pwane_id), cwtc_x);
	kmb_wwite_wcd(kmb, WCD_WAYEWn_WOW_STAWT(pwane_id), cwtc_y);

	vaw |= WCD_WAYEW_FIFO_100;

	if (vaw & WCD_WAYEW_PWANAW_STOWAGE) {
		vaw |= WCD_WAYEW_CSC_EN;

		/* Enabwe CSC if input is pwanaw and output is WGB */
		config_csc(kmb, pwane_id);
	}

	kmb_pwane_set_awpha(kmb, pwane->state, pwane_id, &vaw);

	kmb_wwite_wcd(kmb, WCD_WAYEWn_CFG(pwane_id), vaw);

	/* Configuwe WCD_CONTWOW */
	ctww = kmb_wead_wcd(kmb, WCD_CONTWOW);

	/* Set wayew bwending config */
	ctww &= ~WCD_CTWW_AWPHA_AWW;
	ctww |= WCD_CTWW_AWPHA_BOTTOM_VW1 |
		WCD_CTWW_AWPHA_BWEND_VW2;

	ctww &= ~WCD_CTWW_AWPHA_BWEND_BKGND_DISABWE;

	switch (pwane_id) {
	case WAYEW_0:
		ctww |= WCD_CTWW_VW1_ENABWE;
		bweak;
	case WAYEW_1:
		ctww |= WCD_CTWW_VW2_ENABWE;
		bweak;
	case WAYEW_2:
		ctww |= WCD_CTWW_GW1_ENABWE;
		bweak;
	case WAYEW_3:
		ctww |= WCD_CTWW_GW2_ENABWE;
		bweak;
	}

	ctww |= WCD_CTWW_PWOGWESSIVE | WCD_CTWW_TIM_GEN_ENABWE
	    | WCD_CTWW_CONTINUOUS | WCD_CTWW_OUTPUT_ENABWED;

	/* WCD is connected to MIPI on kmb
	 * Thewefowe this bit is wequiwed fow DSI Tx
	 */
	ctww |= WCD_CTWW_VHSYNC_IDWE_WVW;

	kmb_wwite_wcd(kmb, WCD_CONTWOW, ctww);

	/* Enabwe pipewine AXI wead twansactions fow the DMA
	 * aftew setting gwaphics wayews. This must be done
	 * in a sepawate wwite cycwe.
	 */
	kmb_set_bitmask_wcd(kmb, WCD_CONTWOW, WCD_CTWW_PIPEWINE_DMA);

	/* FIXME no doc on how to set output fowmat, these vawues awe taken
	 * fwom the Mywiadx tests
	 */
	out_fowmat |= WCD_OUTF_FOWMAT_WGB888;

	/* Weave WGB owdew,convewsion mode and cwip mode to defauwt */
	/* do not intewweave WGB channews fow mipi Tx compatibiwity */
	out_fowmat |= WCD_OUTF_MIPI_WGB_MODE;
	kmb_wwite_wcd(kmb, WCD_OUT_FOWMAT_CFG, out_fowmat);

	dma_cfg = WCD_DMA_WAYEW_ENABWE | WCD_DMA_WAYEW_VSTWIDE_EN |
	    WCD_DMA_WAYEW_CONT_UPDATE | WCD_DMA_WAYEW_AXI_BUWST_16;

	/* Enabwe DMA */
	kmb_wwite_wcd(kmb, WCD_WAYEWn_DMA_CFG(pwane_id), dma_cfg);

	/* Save initiaw dispway config */
	if (!init_disp_cfg->width ||
	    !init_disp_cfg->height ||
	    !init_disp_cfg->fowmat) {
		init_disp_cfg->width = width;
		init_disp_cfg->height = height;
		init_disp_cfg->fowmat = fb->fowmat->fowmat;
	}

	dwm_dbg(&kmb->dwm, "dma_cfg=0x%x WCD_DMA_CFG=0x%x\n", dma_cfg,
		kmb_wead_wcd(kmb, WCD_WAYEWn_DMA_CFG(pwane_id)));

	kmb_set_bitmask_wcd(kmb, WCD_INT_CWEAW, WCD_INT_EOF |
			WCD_INT_DMA_EWW);
	kmb_set_bitmask_wcd(kmb, WCD_INT_ENABWE, WCD_INT_EOF |
			WCD_INT_DMA_EWW);
}

static const stwuct dwm_pwane_hewpew_funcs kmb_pwane_hewpew_funcs = {
	.atomic_check = kmb_pwane_atomic_check,
	.atomic_update = kmb_pwane_atomic_update,
	.atomic_disabwe = kmb_pwane_atomic_disabwe
};

void kmb_pwane_destwoy(stwuct dwm_pwane *pwane)
{
	stwuct kmb_pwane *kmb_pwane = to_kmb_pwane(pwane);

	dwm_pwane_cweanup(pwane);
	kfwee(kmb_pwane);
}

static const stwuct dwm_pwane_funcs kmb_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = kmb_pwane_destwoy,
	.weset = dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
};

stwuct kmb_pwane *kmb_pwane_init(stwuct dwm_device *dwm)
{
	stwuct kmb_dwm_pwivate *kmb = to_kmb(dwm);
	stwuct kmb_pwane *pwane = NUWW;
	stwuct kmb_pwane *pwimawy = NUWW;
	int i = 0;
	int wet = 0;
	enum dwm_pwane_type pwane_type;
	const u32 *pwane_fowmats;
	int num_pwane_fowmats;
	unsigned int bwend_caps = BIT(DWM_MODE_BWEND_PIXEW_NONE) |
				  BIT(DWM_MODE_BWEND_PWEMUWTI)   |
				  BIT(DWM_MODE_BWEND_COVEWAGE);

	fow (i = 0; i < KMB_MAX_PWANES; i++) {
		pwane = dwmm_kzawwoc(dwm, sizeof(*pwane), GFP_KEWNEW);

		if (!pwane) {
			dwm_eww(dwm, "Faiwed to awwocate pwane\n");
			wetuwn EWW_PTW(-ENOMEM);
		}

		pwane_type = (i == 0) ? DWM_PWANE_TYPE_PWIMAWY :
		    DWM_PWANE_TYPE_OVEWWAY;
		if (i < 2) {
			pwane_fowmats = kmb_fowmats_v;
			num_pwane_fowmats = AWWAY_SIZE(kmb_fowmats_v);
		} ewse {
			pwane_fowmats = kmb_fowmats_g;
			num_pwane_fowmats = AWWAY_SIZE(kmb_fowmats_g);
		}

		wet = dwm_univewsaw_pwane_init(dwm, &pwane->base_pwane,
					       POSSIBWE_CWTCS, &kmb_pwane_funcs,
					       pwane_fowmats, num_pwane_fowmats,
					       NUWW, pwane_type, "pwane %d", i);
		if (wet < 0) {
			dwm_eww(dwm, "dwm_univewsaw_pwane_init faiwed (wet=%d)",
				wet);
			goto cweanup;
		}
		dwm_dbg(dwm, "%s : %d i=%d type=%d",
			__func__, __WINE__,
			  i, pwane_type);
		dwm_pwane_cweate_awpha_pwopewty(&pwane->base_pwane);

		dwm_pwane_cweate_bwend_mode_pwopewty(&pwane->base_pwane,
						     bwend_caps);

		dwm_pwane_cweate_zpos_immutabwe_pwopewty(&pwane->base_pwane, i);

		dwm_pwane_hewpew_add(&pwane->base_pwane,
				     &kmb_pwane_hewpew_funcs);

		if (pwane_type == DWM_PWANE_TYPE_PWIMAWY) {
			pwimawy = pwane;
			kmb->pwane = pwane;
		}
		dwm_dbg(dwm, "%s : %d pwimawy=%p\n", __func__, __WINE__,
			&pwimawy->base_pwane);
		pwane->id = i;
	}

	/* Disabwe pipewine AXI wead twansactions fow the DMA
	 * pwiow to setting gwaphics wayews
	 */
	kmb_cww_bitmask_wcd(kmb, WCD_CONTWOW, WCD_CTWW_PIPEWINE_DMA);

	wetuwn pwimawy;
cweanup:
	dwmm_kfwee(dwm, pwane);
	wetuwn EWW_PTW(wet);
}
