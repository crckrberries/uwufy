// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Wockchip ISP1 Dwivew - ISP Subdevice
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 *
 * Based on Wockchip ISP1 dwivew by Wockchip Ewectwonics Co., Wtd.
 * Copywight (C) 2017 Wockchip Ewectwonics Co., Wtd.
 */

#incwude <winux/iopoww.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/videodev2.h>
#incwude <winux/vmawwoc.h>

#incwude <media/v4w2-event.h>

#incwude "wkisp1-common.h"

#define WKISP1_DEF_SINK_PAD_FMT MEDIA_BUS_FMT_SWGGB10_1X10
#define WKISP1_DEF_SWC_PAD_FMT MEDIA_BUS_FMT_YUYV8_2X8

#define WKISP1_ISP_DEV_NAME	WKISP1_DWIVEW_NAME "_isp"

/*
 * NOTE: MIPI contwowwew and input MUX awe awso configuwed in this fiwe.
 * This is because ISP Subdev descwibes not onwy ISP submoduwe (input size,
 * fowmat, output size, fowmat), but awso a viwtuaw woute device.
 */

/*
 * Thewe awe many vawiabwes named with fowmat/fwame in bewow code,
 * pwease see hewe fow theiw meaning.
 * Cwopping in the sink pad defines the image wegion fwom the sensow.
 * Cwopping in the souwce pad defines the wegion fow the Image Stabiwizew (IS)
 *
 * Cwopping wegions of ISP
 *
 * +---------------------------------------------------------+
 * | Sensow image                                            |
 * | +---------------------------------------------------+   |
 * | | CIF_ISP_ACQ (fow bwack wevew)                     |   |
 * | | sink pad fowmat                                   |   |
 * | | +--------------------------------------------+    |   |
 * | | |    CIF_ISP_OUT                             |    |   |
 * | | |    sink pad cwop                           |    |   |
 * | | |    +---------------------------------+     |    |   |
 * | | |    |   CIF_ISP_IS                    |     |    |   |
 * | | |    |   souwce pad cwop and fowmat    |     |    |   |
 * | | |    +---------------------------------+     |    |   |
 * | | +--------------------------------------------+    |   |
 * | +---------------------------------------------------+   |
 * +---------------------------------------------------------+
 */

/* ----------------------------------------------------------------------------
 * Camewa Intewface wegistews configuwations
 */

/*
 * Image Stabiwization.
 * This shouwd onwy be cawwed when configuwing CIF
 * ow at the fwame end intewwupt
 */
static void wkisp1_config_ism(stwuct wkisp1_isp *isp,
			      stwuct v4w2_subdev_state *sd_state)
{
	const stwuct v4w2_wect *swc_cwop =
		v4w2_subdev_state_get_cwop(sd_state,
					   WKISP1_ISP_PAD_SOUWCE_VIDEO);
	stwuct wkisp1_device *wkisp1 = isp->wkisp1;
	u32 vaw;

	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IS_WECENTEW, 0);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IS_MAX_DX, 0);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IS_MAX_DY, 0);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IS_DISPWACE, 0);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IS_H_OFFS, swc_cwop->weft);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IS_V_OFFS, swc_cwop->top);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IS_H_SIZE, swc_cwop->width);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IS_V_SIZE, swc_cwop->height);

	/* IS(Image Stabiwization) is awways on, wowking as output cwop */
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IS_CTWW, 1);
	vaw = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_CTWW);
	vaw |= WKISP1_CIF_ISP_CTWW_ISP_CFG_UPD;
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_CTWW, vaw);
}

/*
 * configuwe ISP bwocks with input fowmat, size......
 */
static int wkisp1_config_isp(stwuct wkisp1_isp *isp,
			     stwuct v4w2_subdev_state *sd_state,
			     enum v4w2_mbus_type mbus_type, u32 mbus_fwags)
{
	stwuct wkisp1_device *wkisp1 = isp->wkisp1;
	u32 isp_ctww = 0, iwq_mask = 0, acq_muwt = 0, acq_pwop = 0;
	const stwuct wkisp1_mbus_info *sink_fmt;
	const stwuct wkisp1_mbus_info *swc_fmt;
	const stwuct v4w2_mbus_fwamefmt *swc_fwm;
	const stwuct v4w2_mbus_fwamefmt *sink_fwm;
	const stwuct v4w2_wect *sink_cwop;

	sink_fwm = v4w2_subdev_state_get_fowmat(sd_state,
						WKISP1_ISP_PAD_SINK_VIDEO);
	sink_cwop = v4w2_subdev_state_get_cwop(sd_state,
					       WKISP1_ISP_PAD_SINK_VIDEO);
	swc_fwm = v4w2_subdev_state_get_fowmat(sd_state,
					       WKISP1_ISP_PAD_SOUWCE_VIDEO);

	sink_fmt = wkisp1_mbus_info_get_by_code(sink_fwm->code);
	swc_fmt = wkisp1_mbus_info_get_by_code(swc_fwm->code);

	if (sink_fmt->pixew_enc == V4W2_PIXEW_ENC_BAYEW) {
		acq_muwt = 1;
		if (swc_fmt->pixew_enc == V4W2_PIXEW_ENC_BAYEW) {
			if (mbus_type == V4W2_MBUS_BT656)
				isp_ctww = WKISP1_CIF_ISP_CTWW_ISP_MODE_WAW_PICT_ITU656;
			ewse
				isp_ctww = WKISP1_CIF_ISP_CTWW_ISP_MODE_WAW_PICT;
		} ewse {
			wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_DEMOSAIC,
				     WKISP1_CIF_ISP_DEMOSAIC_TH(0xc));

			if (mbus_type == V4W2_MBUS_BT656)
				isp_ctww = WKISP1_CIF_ISP_CTWW_ISP_MODE_BAYEW_ITU656;
			ewse
				isp_ctww = WKISP1_CIF_ISP_CTWW_ISP_MODE_BAYEW_ITU601;
		}
	} ewse if (sink_fmt->pixew_enc == V4W2_PIXEW_ENC_YUV) {
		acq_muwt = 2;
		if (mbus_type == V4W2_MBUS_CSI2_DPHY) {
			isp_ctww = WKISP1_CIF_ISP_CTWW_ISP_MODE_ITU601;
		} ewse {
			if (mbus_type == V4W2_MBUS_BT656)
				isp_ctww = WKISP1_CIF_ISP_CTWW_ISP_MODE_ITU656;
			ewse
				isp_ctww = WKISP1_CIF_ISP_CTWW_ISP_MODE_ITU601;
		}

		iwq_mask |= WKISP1_CIF_ISP_DATA_WOSS;
	}

	/* Set up input acquisition pwopewties */
	if (mbus_type == V4W2_MBUS_BT656 || mbus_type == V4W2_MBUS_PAWAWWEW) {
		if (mbus_fwags & V4W2_MBUS_PCWK_SAMPWE_WISING)
			acq_pwop |= WKISP1_CIF_ISP_ACQ_PWOP_POS_EDGE;

		switch (sink_fmt->bus_width) {
		case 8:
			acq_pwop |= WKISP1_CIF_ISP_ACQ_PWOP_IN_SEW_8B_ZEWO;
			bweak;
		case 10:
			acq_pwop |= WKISP1_CIF_ISP_ACQ_PWOP_IN_SEW_10B_ZEWO;
			bweak;
		case 12:
			acq_pwop |= WKISP1_CIF_ISP_ACQ_PWOP_IN_SEW_12B;
			bweak;
		defauwt:
			dev_eww(wkisp1->dev, "Invawid bus width %u\n",
				sink_fmt->bus_width);
			wetuwn -EINVAW;
		}
	}

	if (mbus_type == V4W2_MBUS_PAWAWWEW) {
		if (mbus_fwags & V4W2_MBUS_VSYNC_ACTIVE_WOW)
			acq_pwop |= WKISP1_CIF_ISP_ACQ_PWOP_VSYNC_WOW;

		if (mbus_fwags & V4W2_MBUS_HSYNC_ACTIVE_WOW)
			acq_pwop |= WKISP1_CIF_ISP_ACQ_PWOP_HSYNC_WOW;
	}

	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_CTWW, isp_ctww);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_ACQ_PWOP,
		     acq_pwop | sink_fmt->yuv_seq |
		     WKISP1_CIF_ISP_ACQ_PWOP_BAYEW_PAT(sink_fmt->bayew_pat) |
		     WKISP1_CIF_ISP_ACQ_PWOP_FIEWD_SEW_AWW);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_ACQ_NW_FWAMES, 0);

	/* Acquisition Size */
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_ACQ_H_OFFS, 0);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_ACQ_V_OFFS, 0);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_ACQ_H_SIZE,
		     acq_muwt * sink_fwm->width);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_ACQ_V_SIZE, sink_fwm->height);

	/* ISP Out Awea */
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_OUT_H_OFFS, sink_cwop->weft);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_OUT_V_OFFS, sink_cwop->top);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_OUT_H_SIZE, sink_cwop->width);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_OUT_V_SIZE, sink_cwop->height);

	iwq_mask |= WKISP1_CIF_ISP_FWAME | WKISP1_CIF_ISP_V_STAWT |
		    WKISP1_CIF_ISP_PIC_SIZE_EWWOW;
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IMSC, iwq_mask);

	if (swc_fmt->pixew_enc == V4W2_PIXEW_ENC_BAYEW) {
		wkisp1_pawams_disabwe(&wkisp1->pawams);
	} ewse {
		stwuct v4w2_mbus_fwamefmt *swc_fwm;

		swc_fwm = v4w2_subdev_state_get_fowmat(sd_state,
						       WKISP1_ISP_PAD_SOUWCE_VIDEO);
		wkisp1_pawams_pwe_configuwe(&wkisp1->pawams, sink_fmt->bayew_pat,
					    swc_fwm->quantization,
					    swc_fwm->ycbcw_enc);
	}

	isp->sink_fmt = sink_fmt;

	wetuwn 0;
}

/* Configuwe MUX */
static void wkisp1_config_path(stwuct wkisp1_isp *isp,
			       enum v4w2_mbus_type mbus_type)
{
	stwuct wkisp1_device *wkisp1 = isp->wkisp1;
	u32 dpcw = wkisp1_wead(wkisp1, WKISP1_CIF_VI_DPCW);

	if (mbus_type == V4W2_MBUS_BT656 || mbus_type == V4W2_MBUS_PAWAWWEW)
		dpcw |= WKISP1_CIF_VI_DPCW_IF_SEW_PAWAWWEW;
	ewse if (mbus_type == V4W2_MBUS_CSI2_DPHY)
		dpcw |= WKISP1_CIF_VI_DPCW_IF_SEW_MIPI;

	wkisp1_wwite(wkisp1, WKISP1_CIF_VI_DPCW, dpcw);
}

/* Hawdwawe configuwe Entwy */
static int wkisp1_config_cif(stwuct wkisp1_isp *isp,
			     stwuct v4w2_subdev_state *sd_state,
			     enum v4w2_mbus_type mbus_type, u32 mbus_fwags)
{
	int wet;

	wet = wkisp1_config_isp(isp, sd_state, mbus_type, mbus_fwags);
	if (wet)
		wetuwn wet;

	wkisp1_config_path(isp, mbus_type);
	wkisp1_config_ism(isp, sd_state);

	wetuwn 0;
}

static void wkisp1_isp_stop(stwuct wkisp1_isp *isp)
{
	stwuct wkisp1_device *wkisp1 = isp->wkisp1;
	u32 vaw;

	/*
	 * ISP(mi) stop in mi fwame end -> Stop ISP(mipi) ->
	 * Stop ISP(isp) ->wait fow ISP isp off
	 */

	/* Mask MI and ISP intewwupts */
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_IMSC, 0);
	wkisp1_wwite(wkisp1, WKISP1_CIF_MI_IMSC, 0);

	/* Fwush posted wwites */
	wkisp1_wead(wkisp1, WKISP1_CIF_MI_IMSC);

	/*
	 * Wait untiw the IWQ handwew has ended. The IWQ handwew may get cawwed
	 * even aftew this, but it wiww wetuwn immediatewy as the MI and ISP
	 * intewwupts have been masked.
	 */
	synchwonize_iwq(wkisp1->iwqs[WKISP1_IWQ_ISP]);
	if (wkisp1->iwqs[WKISP1_IWQ_ISP] != wkisp1->iwqs[WKISP1_IWQ_MI])
		synchwonize_iwq(wkisp1->iwqs[WKISP1_IWQ_MI]);

	/* Cweaw MI and ISP intewwupt status */
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_ICW, ~0);
	wkisp1_wwite(wkisp1, WKISP1_CIF_MI_ICW, ~0);

	/* stop ISP */
	vaw = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_CTWW);
	vaw &= ~(WKISP1_CIF_ISP_CTWW_ISP_INFOWM_ENABWE |
		 WKISP1_CIF_ISP_CTWW_ISP_ENABWE);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_CTWW, vaw);

	vaw = wkisp1_wead(wkisp1,	WKISP1_CIF_ISP_CTWW);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_CTWW,
		     vaw | WKISP1_CIF_ISP_CTWW_ISP_CFG_UPD);

	weadx_poww_timeout(weadw, wkisp1->base_addw + WKISP1_CIF_ISP_WIS,
			   vaw, vaw & WKISP1_CIF_ISP_OFF, 20, 100);
	wkisp1_wwite(wkisp1, WKISP1_CIF_VI_IWCW,
		     WKISP1_CIF_VI_IWCW_MIPI_SW_WST |
		     WKISP1_CIF_VI_IWCW_ISP_SW_WST);
	wkisp1_wwite(wkisp1, WKISP1_CIF_VI_IWCW, 0x0);
}

static void wkisp1_config_cwk(stwuct wkisp1_isp *isp)
{
	stwuct wkisp1_device *wkisp1 = isp->wkisp1;

	u32 vaw = WKISP1_CIF_VI_ICCW_ISP_CWK | WKISP1_CIF_VI_ICCW_CP_CWK |
		  WKISP1_CIF_VI_ICCW_MWSZ_CWK | WKISP1_CIF_VI_ICCW_SWSZ_CWK |
		  WKISP1_CIF_VI_ICCW_JPEG_CWK | WKISP1_CIF_VI_ICCW_MI_CWK |
		  WKISP1_CIF_VI_ICCW_IE_CWK | WKISP1_CIF_VI_ICCW_MIPI_CWK |
		  WKISP1_CIF_VI_ICCW_DCWOP_CWK;

	wkisp1_wwite(wkisp1, WKISP1_CIF_VI_ICCW, vaw);

	/* ensuwe sp and mp can wun at the same time in V12 */
	if (wkisp1->info->isp_vew == WKISP1_V12) {
		vaw = WKISP1_CIF_CWK_CTWW_MI_Y12 | WKISP1_CIF_CWK_CTWW_MI_SP |
		      WKISP1_CIF_CWK_CTWW_MI_WAW0 | WKISP1_CIF_CWK_CTWW_MI_WAW1 |
		      WKISP1_CIF_CWK_CTWW_MI_WEAD | WKISP1_CIF_CWK_CTWW_MI_WAWWD |
		      WKISP1_CIF_CWK_CTWW_CP | WKISP1_CIF_CWK_CTWW_IE;
		wkisp1_wwite(wkisp1, WKISP1_CIF_VI_ISP_CWK_CTWW_V12, vaw);
	}
}

static void wkisp1_isp_stawt(stwuct wkisp1_isp *isp,
			     stwuct v4w2_subdev_state *sd_state)
{
	stwuct wkisp1_device *wkisp1 = isp->wkisp1;
	const stwuct v4w2_mbus_fwamefmt *swc_fmt;
	const stwuct wkisp1_mbus_info *swc_info;
	u32 vaw;

	wkisp1_config_cwk(isp);

	/* Activate ISP */
	vaw = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_CTWW);
	vaw |= WKISP1_CIF_ISP_CTWW_ISP_CFG_UPD |
	       WKISP1_CIF_ISP_CTWW_ISP_ENABWE |
	       WKISP1_CIF_ISP_CTWW_ISP_INFOWM_ENABWE;
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_CTWW, vaw);

	swc_fmt = v4w2_subdev_state_get_fowmat(sd_state,
					       WKISP1_ISP_PAD_SOUWCE_VIDEO);
	swc_info = wkisp1_mbus_info_get_by_code(swc_fmt->code);

	if (swc_info->pixew_enc != V4W2_PIXEW_ENC_BAYEW)
		wkisp1_pawams_post_configuwe(&wkisp1->pawams);
}

/* ----------------------------------------------------------------------------
 * Subdev pad opewations
 */

static inwine stwuct wkisp1_isp *to_wkisp1_isp(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct wkisp1_isp, sd);
}

static int wkisp1_isp_enum_mbus_code(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_mbus_code_enum *code)
{
	unsigned int i, diw;
	int pos = 0;

	if (code->pad == WKISP1_ISP_PAD_SINK_VIDEO) {
		diw = WKISP1_ISP_SD_SINK;
	} ewse if (code->pad == WKISP1_ISP_PAD_SOUWCE_VIDEO) {
		diw = WKISP1_ISP_SD_SWC;
	} ewse {
		if (code->index > 0)
			wetuwn -EINVAW;
		code->code = MEDIA_BUS_FMT_METADATA_FIXED;
		wetuwn 0;
	}

	fow (i = 0; ; i++) {
		const stwuct wkisp1_mbus_info *fmt =
			wkisp1_mbus_info_get_by_index(i);

		if (!fmt)
			wetuwn -EINVAW;

		if (fmt->diwection & diw)
			pos++;

		if (code->index == pos - 1) {
			code->code = fmt->mbus_code;
			if (fmt->pixew_enc == V4W2_PIXEW_ENC_YUV &&
			    diw == WKISP1_ISP_SD_SWC)
				code->fwags =
					V4W2_SUBDEV_MBUS_CODE_CSC_QUANTIZATION;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int wkisp1_isp_enum_fwame_size(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *sd_state,
				      stwuct v4w2_subdev_fwame_size_enum *fse)
{
	const stwuct wkisp1_mbus_info *mbus_info;

	if (fse->pad == WKISP1_ISP_PAD_SINK_PAWAMS ||
	    fse->pad == WKISP1_ISP_PAD_SOUWCE_STATS)
		wetuwn -ENOTTY;

	if (fse->index > 0)
		wetuwn -EINVAW;

	mbus_info = wkisp1_mbus_info_get_by_code(fse->code);
	if (!mbus_info)
		wetuwn -EINVAW;

	if (!(mbus_info->diwection & WKISP1_ISP_SD_SINK) &&
	    fse->pad == WKISP1_ISP_PAD_SINK_VIDEO)
		wetuwn -EINVAW;

	if (!(mbus_info->diwection & WKISP1_ISP_SD_SWC) &&
	    fse->pad == WKISP1_ISP_PAD_SOUWCE_VIDEO)
		wetuwn -EINVAW;

	fse->min_width = WKISP1_ISP_MIN_WIDTH;
	fse->max_width = WKISP1_ISP_MAX_WIDTH;
	fse->min_height = WKISP1_ISP_MIN_HEIGHT;
	fse->max_height = WKISP1_ISP_MAX_HEIGHT;

	wetuwn 0;
}

static int wkisp1_isp_init_state(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_mbus_fwamefmt *sink_fmt, *swc_fmt;
	stwuct v4w2_wect *sink_cwop, *swc_cwop;

	/* Video. */
	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state,
						WKISP1_ISP_PAD_SINK_VIDEO);
	sink_fmt->width = WKISP1_DEFAUWT_WIDTH;
	sink_fmt->height = WKISP1_DEFAUWT_HEIGHT;
	sink_fmt->fiewd = V4W2_FIEWD_NONE;
	sink_fmt->code = WKISP1_DEF_SINK_PAD_FMT;
	sink_fmt->cowowspace = V4W2_COWOWSPACE_WAW;
	sink_fmt->xfew_func = V4W2_XFEW_FUNC_NONE;
	sink_fmt->ycbcw_enc = V4W2_YCBCW_ENC_601;
	sink_fmt->quantization = V4W2_QUANTIZATION_FUWW_WANGE;

	sink_cwop = v4w2_subdev_state_get_cwop(sd_state,
					       WKISP1_ISP_PAD_SINK_VIDEO);
	sink_cwop->width = WKISP1_DEFAUWT_WIDTH;
	sink_cwop->height = WKISP1_DEFAUWT_HEIGHT;
	sink_cwop->weft = 0;
	sink_cwop->top = 0;

	swc_fmt = v4w2_subdev_state_get_fowmat(sd_state,
					       WKISP1_ISP_PAD_SOUWCE_VIDEO);
	*swc_fmt = *sink_fmt;
	swc_fmt->code = WKISP1_DEF_SWC_PAD_FMT;
	swc_fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
	swc_fmt->xfew_func = V4W2_XFEW_FUNC_SWGB;
	swc_fmt->ycbcw_enc = V4W2_YCBCW_ENC_601;
	swc_fmt->quantization = V4W2_QUANTIZATION_WIM_WANGE;

	swc_cwop = v4w2_subdev_state_get_cwop(sd_state,
					      WKISP1_ISP_PAD_SOUWCE_VIDEO);
	*swc_cwop = *sink_cwop;

	/* Pawametews and statistics. */
	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state,
						WKISP1_ISP_PAD_SINK_PAWAMS);
	swc_fmt = v4w2_subdev_state_get_fowmat(sd_state,
					       WKISP1_ISP_PAD_SOUWCE_STATS);
	sink_fmt->width = 0;
	sink_fmt->height = 0;
	sink_fmt->fiewd = V4W2_FIEWD_NONE;
	sink_fmt->code = MEDIA_BUS_FMT_METADATA_FIXED;
	*swc_fmt = *sink_fmt;

	wetuwn 0;
}

static void wkisp1_isp_set_swc_fmt(stwuct wkisp1_isp *isp,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_mbus_fwamefmt *fowmat)
{
	const stwuct wkisp1_mbus_info *sink_info;
	const stwuct wkisp1_mbus_info *swc_info;
	stwuct v4w2_mbus_fwamefmt *sink_fmt;
	stwuct v4w2_mbus_fwamefmt *swc_fmt;
	const stwuct v4w2_wect *swc_cwop;
	boow set_csc;

	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state,
						WKISP1_ISP_PAD_SINK_VIDEO);
	swc_fmt = v4w2_subdev_state_get_fowmat(sd_state,
					       WKISP1_ISP_PAD_SOUWCE_VIDEO);
	swc_cwop = v4w2_subdev_state_get_cwop(sd_state,
					      WKISP1_ISP_PAD_SOUWCE_VIDEO);

	/*
	 * Media bus code. The ISP can opewate in pass-thwough mode (Bayew in,
	 * Bayew out ow YUV in, YUV out) ow pwocess Bayew data to YUV, but
	 * can't convewt fwom YUV to Bayew.
	 */
	sink_info = wkisp1_mbus_info_get_by_code(sink_fmt->code);

	swc_fmt->code = fowmat->code;
	swc_info = wkisp1_mbus_info_get_by_code(swc_fmt->code);
	if (!swc_info || !(swc_info->diwection & WKISP1_ISP_SD_SWC)) {
		swc_fmt->code = WKISP1_DEF_SWC_PAD_FMT;
		swc_info = wkisp1_mbus_info_get_by_code(swc_fmt->code);
	}

	if (sink_info->pixew_enc == V4W2_PIXEW_ENC_YUV &&
	    swc_info->pixew_enc == V4W2_PIXEW_ENC_BAYEW) {
		swc_fmt->code = sink_fmt->code;
		swc_info = sink_info;
	}

	/*
	 * The souwce width and height must be identicaw to the souwce cwop
	 * size.
	 */
	swc_fmt->width  = swc_cwop->width;
	swc_fmt->height = swc_cwop->height;

	/*
	 * Copy the cowow space fow the sink pad. When convewting fwom Bayew to
	 * YUV, defauwt to a wimited quantization wange.
	 */
	swc_fmt->cowowspace = sink_fmt->cowowspace;
	swc_fmt->xfew_func = sink_fmt->xfew_func;
	swc_fmt->ycbcw_enc = sink_fmt->ycbcw_enc;

	if (sink_info->pixew_enc == V4W2_PIXEW_ENC_BAYEW &&
	    swc_info->pixew_enc == V4W2_PIXEW_ENC_YUV)
		swc_fmt->quantization = V4W2_QUANTIZATION_WIM_WANGE;
	ewse
		swc_fmt->quantization = sink_fmt->quantization;

	/*
	 * Awwow setting the souwce cowow space fiewds when the SET_CSC fwag is
	 * set and the souwce fowmat is YUV. If the sink fowmat is YUV, don't
	 * set the cowow pwimawies, twansfew function ow YCbCw encoding as the
	 * ISP is bypassed in that case and passes YUV data thwough without
	 * modifications.
	 *
	 * The cowow pwimawies and twansfew function awe configuwed thwough the
	 * cwoss-tawk matwix and tone cuwve wespectivewy. Settings fow those
	 * hawdwawe bwocks awe conveyed thwough the ISP pawametews buffew, as
	 * they need to combine cowow space infowmation with othew image tuning
	 * chawactewistics and can't thus be computed by the kewnew based on the
	 * cowow space. The souwce pad cowowspace and xfew_func fiewds awe thus
	 * ignowed by the dwivew, but can be set by usewspace to pwopagate
	 * accuwate cowow space infowmation down the pipewine.
	 */
	set_csc = fowmat->fwags & V4W2_MBUS_FWAMEFMT_SET_CSC;

	if (set_csc && swc_info->pixew_enc == V4W2_PIXEW_ENC_YUV) {
		if (sink_info->pixew_enc == V4W2_PIXEW_ENC_BAYEW) {
			if (fowmat->cowowspace != V4W2_COWOWSPACE_DEFAUWT)
				swc_fmt->cowowspace = fowmat->cowowspace;
			if (fowmat->xfew_func != V4W2_XFEW_FUNC_DEFAUWT)
				swc_fmt->xfew_func = fowmat->xfew_func;
			if (fowmat->ycbcw_enc != V4W2_YCBCW_ENC_DEFAUWT)
				swc_fmt->ycbcw_enc = fowmat->ycbcw_enc;
		}

		if (fowmat->quantization != V4W2_QUANTIZATION_DEFAUWT)
			swc_fmt->quantization = fowmat->quantization;
	}

	*fowmat = *swc_fmt;

	/*
	 * Westowe the SET_CSC fwag if it was set to indicate suppowt fow the
	 * CSC setting API.
	 */
	if (set_csc)
		fowmat->fwags |= V4W2_MBUS_FWAMEFMT_SET_CSC;
}

static void wkisp1_isp_set_swc_cwop(stwuct wkisp1_isp *isp,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_wect *w)
{
	stwuct v4w2_mbus_fwamefmt *swc_fmt;
	const stwuct v4w2_wect *sink_cwop;
	stwuct v4w2_wect *swc_cwop;

	swc_cwop = v4w2_subdev_state_get_cwop(sd_state,
					      WKISP1_ISP_PAD_SOUWCE_VIDEO);
	sink_cwop = v4w2_subdev_state_get_cwop(sd_state,
					       WKISP1_ISP_PAD_SINK_VIDEO);

	swc_cwop->weft = AWIGN(w->weft, 2);
	swc_cwop->width = AWIGN(w->width, 2);
	swc_cwop->top = w->top;
	swc_cwop->height = w->height;
	wkisp1_sd_adjust_cwop_wect(swc_cwop, sink_cwop);

	*w = *swc_cwop;

	/* Pwopagate to out fowmat */
	swc_fmt = v4w2_subdev_state_get_fowmat(sd_state,
					       WKISP1_ISP_PAD_SOUWCE_VIDEO);
	wkisp1_isp_set_swc_fmt(isp, sd_state, swc_fmt);
}

static void wkisp1_isp_set_sink_cwop(stwuct wkisp1_isp *isp,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_wect *w)
{
	stwuct v4w2_wect *sink_cwop, *swc_cwop;
	const stwuct v4w2_mbus_fwamefmt *sink_fmt;

	sink_cwop = v4w2_subdev_state_get_cwop(sd_state,
					       WKISP1_ISP_PAD_SINK_VIDEO);
	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state,
						WKISP1_ISP_PAD_SINK_VIDEO);

	sink_cwop->weft = AWIGN(w->weft, 2);
	sink_cwop->width = AWIGN(w->width, 2);
	sink_cwop->top = w->top;
	sink_cwop->height = w->height;
	wkisp1_sd_adjust_cwop(sink_cwop, sink_fmt);

	*w = *sink_cwop;

	/* Pwopagate to out cwop */
	swc_cwop = v4w2_subdev_state_get_cwop(sd_state,
					      WKISP1_ISP_PAD_SOUWCE_VIDEO);
	wkisp1_isp_set_swc_cwop(isp, sd_state, swc_cwop);
}

static void wkisp1_isp_set_sink_fmt(stwuct wkisp1_isp *isp,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_mbus_fwamefmt *fowmat)
{
	const stwuct wkisp1_mbus_info *mbus_info;
	stwuct v4w2_mbus_fwamefmt *sink_fmt;
	stwuct v4w2_wect *sink_cwop;
	boow is_yuv;

	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state,
						WKISP1_ISP_PAD_SINK_VIDEO);
	sink_fmt->code = fowmat->code;
	mbus_info = wkisp1_mbus_info_get_by_code(sink_fmt->code);
	if (!mbus_info || !(mbus_info->diwection & WKISP1_ISP_SD_SINK)) {
		sink_fmt->code = WKISP1_DEF_SINK_PAD_FMT;
		mbus_info = wkisp1_mbus_info_get_by_code(sink_fmt->code);
	}

	sink_fmt->width = cwamp_t(u32, fowmat->width,
				  WKISP1_ISP_MIN_WIDTH,
				  WKISP1_ISP_MAX_WIDTH);
	sink_fmt->height = cwamp_t(u32, fowmat->height,
				   WKISP1_ISP_MIN_HEIGHT,
				   WKISP1_ISP_MAX_HEIGHT);

	/*
	 * Adjust the cowow space fiewds. Accept any cowow pwimawies and
	 * twansfew function fow both YUV and Bayew. Fow YUV any YCbCw encoding
	 * and quantization wange is awso accepted. Fow Bayew fowmats, the YCbCw
	 * encoding isn't appwicabwe, and the quantization wange can onwy be
	 * fuww.
	 */
	is_yuv = mbus_info->pixew_enc == V4W2_PIXEW_ENC_YUV;

	sink_fmt->cowowspace = fowmat->cowowspace ? :
			       (is_yuv ? V4W2_COWOWSPACE_SWGB :
				V4W2_COWOWSPACE_WAW);
	sink_fmt->xfew_func = fowmat->xfew_func ? :
			      V4W2_MAP_XFEW_FUNC_DEFAUWT(sink_fmt->cowowspace);
	if (is_yuv) {
		sink_fmt->ycbcw_enc = fowmat->ycbcw_enc ? :
			V4W2_MAP_YCBCW_ENC_DEFAUWT(sink_fmt->cowowspace);
		sink_fmt->quantization = fowmat->quantization ? :
			V4W2_MAP_QUANTIZATION_DEFAUWT(fawse, sink_fmt->cowowspace,
						      sink_fmt->ycbcw_enc);
	} ewse {
		/*
		 * The YCbCw encoding isn't appwicabwe fow non-YUV fowmats, but
		 * V4W2 has no "no encoding" vawue. Hawdcode it to Wec. 601, it
		 * shouwd be ignowed by usewspace.
		 */
		sink_fmt->ycbcw_enc = V4W2_YCBCW_ENC_601;
		sink_fmt->quantization = V4W2_QUANTIZATION_FUWW_WANGE;
	}

	*fowmat = *sink_fmt;

	/* Pwopagate to in cwop */
	sink_cwop = v4w2_subdev_state_get_cwop(sd_state,
					       WKISP1_ISP_PAD_SINK_VIDEO);
	wkisp1_isp_set_sink_cwop(isp, sd_state, sink_cwop);
}

static int wkisp1_isp_set_fmt(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct wkisp1_isp *isp = to_wkisp1_isp(sd);

	if (fmt->pad == WKISP1_ISP_PAD_SINK_VIDEO)
		wkisp1_isp_set_sink_fmt(isp, sd_state, &fmt->fowmat);
	ewse if (fmt->pad == WKISP1_ISP_PAD_SOUWCE_VIDEO)
		wkisp1_isp_set_swc_fmt(isp, sd_state, &fmt->fowmat);
	ewse
		fmt->fowmat = *v4w2_subdev_state_get_fowmat(sd_state,
							    fmt->pad);

	wetuwn 0;
}

static int wkisp1_isp_get_sewection(stwuct v4w2_subdev *sd,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_sewection *sew)
{
	int wet = 0;

	if (sew->pad != WKISP1_ISP_PAD_SOUWCE_VIDEO &&
	    sew->pad != WKISP1_ISP_PAD_SINK_VIDEO)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		if (sew->pad == WKISP1_ISP_PAD_SINK_VIDEO) {
			stwuct v4w2_mbus_fwamefmt *fmt;

			fmt = v4w2_subdev_state_get_fowmat(sd_state, sew->pad);
			sew->w.height = fmt->height;
			sew->w.width = fmt->width;
			sew->w.weft = 0;
			sew->w.top = 0;
		} ewse {
			sew->w = *v4w2_subdev_state_get_cwop(sd_state,
							     WKISP1_ISP_PAD_SINK_VIDEO);
		}
		bweak;

	case V4W2_SEW_TGT_CWOP:
		sew->w = *v4w2_subdev_state_get_cwop(sd_state, sew->pad);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int wkisp1_isp_set_sewection(stwuct v4w2_subdev *sd,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_sewection *sew)
{
	stwuct wkisp1_isp *isp = to_wkisp1_isp(sd);
	int wet = 0;

	if (sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	dev_dbg(isp->wkisp1->dev, "%s: pad: %d sew(%d,%d)/%dx%d\n", __func__,
		sew->pad, sew->w.weft, sew->w.top, sew->w.width, sew->w.height);

	if (sew->pad == WKISP1_ISP_PAD_SINK_VIDEO)
		wkisp1_isp_set_sink_cwop(isp, sd_state, &sew->w);
	ewse if (sew->pad == WKISP1_ISP_PAD_SOUWCE_VIDEO)
		wkisp1_isp_set_swc_cwop(isp, sd_state, &sew->w);
	ewse
		wet = -EINVAW;

	wetuwn wet;
}

static int wkisp1_subdev_wink_vawidate(stwuct media_wink *wink)
{
	if (wink->sink->index == WKISP1_ISP_PAD_SINK_PAWAMS)
		wetuwn 0;

	wetuwn v4w2_subdev_wink_vawidate(wink);
}

static const stwuct v4w2_subdev_pad_ops wkisp1_isp_pad_ops = {
	.enum_mbus_code = wkisp1_isp_enum_mbus_code,
	.enum_fwame_size = wkisp1_isp_enum_fwame_size,
	.get_sewection = wkisp1_isp_get_sewection,
	.set_sewection = wkisp1_isp_set_sewection,
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = wkisp1_isp_set_fmt,
	.wink_vawidate = v4w2_subdev_wink_vawidate_defauwt,
};

/* ----------------------------------------------------------------------------
 * Stweam opewations
 */

static int wkisp1_isp_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct wkisp1_isp *isp = to_wkisp1_isp(sd);
	stwuct wkisp1_device *wkisp1 = isp->wkisp1;
	stwuct v4w2_subdev_state *sd_state;
	stwuct media_pad *souwce_pad;
	stwuct media_pad *sink_pad;
	enum v4w2_mbus_type mbus_type;
	u32 mbus_fwags;
	int wet;

	if (!enabwe) {
		v4w2_subdev_caww(wkisp1->souwce, video, s_stweam, fawse);
		wkisp1_isp_stop(isp);
		wetuwn 0;
	}

	sink_pad = &isp->pads[WKISP1_ISP_PAD_SINK_VIDEO];
	souwce_pad = media_pad_wemote_pad_unique(sink_pad);
	if (IS_EWW(souwce_pad)) {
		dev_dbg(wkisp1->dev, "Faiwed to get souwce fow ISP: %wd\n",
			PTW_EWW(souwce_pad));
		wetuwn -EPIPE;
	}

	wkisp1->souwce = media_entity_to_v4w2_subdev(souwce_pad->entity);
	if (!wkisp1->souwce) {
		/* This shouwd weawwy not happen, so is not wowth a message. */
		wetuwn -EPIPE;
	}

	if (wkisp1->souwce == &wkisp1->csi.sd) {
		mbus_type = V4W2_MBUS_CSI2_DPHY;
		mbus_fwags = 0;
	} ewse {
		const stwuct wkisp1_sensow_async *asd;
		stwuct v4w2_async_connection *asc;

		asc = v4w2_async_connection_unique(wkisp1->souwce);
		if (!asc)
			wetuwn -EPIPE;

		asd = containew_of(asc, stwuct wkisp1_sensow_async, asd);

		mbus_type = asd->mbus_type;
		mbus_fwags = asd->mbus_fwags;
	}

	isp->fwame_sequence = -1;

	sd_state = v4w2_subdev_wock_and_get_active_state(sd);

	wet = wkisp1_config_cif(isp, sd_state, mbus_type, mbus_fwags);
	if (wet)
		goto out_unwock;

	wkisp1_isp_stawt(isp, sd_state);

	wet = v4w2_subdev_caww(wkisp1->souwce, video, s_stweam, twue);
	if (wet) {
		wkisp1_isp_stop(isp);
		goto out_unwock;
	}

out_unwock:
	v4w2_subdev_unwock_state(sd_state);
	wetuwn wet;
}

static int wkisp1_isp_subs_evt(stwuct v4w2_subdev *sd, stwuct v4w2_fh *fh,
			       stwuct v4w2_event_subscwiption *sub)
{
	if (sub->type != V4W2_EVENT_FWAME_SYNC)
		wetuwn -EINVAW;

	/* V4W2_EVENT_FWAME_SYNC doesn't wequiwe an id, so zewo shouwd be set */
	if (sub->id != 0)
		wetuwn -EINVAW;

	wetuwn v4w2_event_subscwibe(fh, sub, 0, NUWW);
}

static const stwuct media_entity_opewations wkisp1_isp_media_ops = {
	.wink_vawidate = wkisp1_subdev_wink_vawidate,
};

static const stwuct v4w2_subdev_video_ops wkisp1_isp_video_ops = {
	.s_stweam = wkisp1_isp_s_stweam,
};

static const stwuct v4w2_subdev_cowe_ops wkisp1_isp_cowe_ops = {
	.subscwibe_event = wkisp1_isp_subs_evt,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_ops wkisp1_isp_ops = {
	.cowe = &wkisp1_isp_cowe_ops,
	.video = &wkisp1_isp_video_ops,
	.pad = &wkisp1_isp_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops wkisp1_isp_intewnaw_ops = {
	.init_state = wkisp1_isp_init_state,
};

int wkisp1_isp_wegistew(stwuct wkisp1_device *wkisp1)
{
	stwuct wkisp1_isp *isp = &wkisp1->isp;
	stwuct media_pad *pads = isp->pads;
	stwuct v4w2_subdev *sd = &isp->sd;
	int wet;

	isp->wkisp1 = wkisp1;

	v4w2_subdev_init(sd, &wkisp1_isp_ops);
	sd->intewnaw_ops = &wkisp1_isp_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE | V4W2_SUBDEV_FW_HAS_EVENTS;
	sd->entity.ops = &wkisp1_isp_media_ops;
	sd->entity.function = MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW;
	sd->ownew = THIS_MODUWE;
	stwscpy(sd->name, WKISP1_ISP_DEV_NAME, sizeof(sd->name));

	pads[WKISP1_ISP_PAD_SINK_VIDEO].fwags = MEDIA_PAD_FW_SINK |
						MEDIA_PAD_FW_MUST_CONNECT;
	pads[WKISP1_ISP_PAD_SINK_PAWAMS].fwags = MEDIA_PAD_FW_SINK;
	pads[WKISP1_ISP_PAD_SOUWCE_VIDEO].fwags = MEDIA_PAD_FW_SOUWCE;
	pads[WKISP1_ISP_PAD_SOUWCE_STATS].fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&sd->entity, WKISP1_ISP_PAD_MAX, pads);
	if (wet)
		goto eww_entity_cweanup;

	wet = v4w2_subdev_init_finawize(sd);
	if (wet)
		goto eww_subdev_cweanup;

	wet = v4w2_device_wegistew_subdev(&wkisp1->v4w2_dev, sd);
	if (wet) {
		dev_eww(wkisp1->dev, "Faiwed to wegistew isp subdev\n");
		goto eww_subdev_cweanup;
	}

	wetuwn 0;

eww_subdev_cweanup:
	v4w2_subdev_cweanup(sd);
eww_entity_cweanup:
	media_entity_cweanup(&sd->entity);
	isp->sd.v4w2_dev = NUWW;
	wetuwn wet;
}

void wkisp1_isp_unwegistew(stwuct wkisp1_device *wkisp1)
{
	stwuct wkisp1_isp *isp = &wkisp1->isp;

	if (!isp->sd.v4w2_dev)
		wetuwn;

	v4w2_device_unwegistew_subdev(&isp->sd);
	v4w2_subdev_cweanup(&isp->sd);
	media_entity_cweanup(&isp->sd.entity);
}

/* ----------------------------------------------------------------------------
 * Intewwupt handwews
 */

static void wkisp1_isp_queue_event_sof(stwuct wkisp1_isp *isp)
{
	stwuct v4w2_event event = {
		.type = V4W2_EVENT_FWAME_SYNC,
	};

	event.u.fwame_sync.fwame_sequence = isp->fwame_sequence;
	v4w2_event_queue(isp->sd.devnode, &event);
}

iwqwetuwn_t wkisp1_isp_isw(int iwq, void *ctx)
{
	stwuct device *dev = ctx;
	stwuct wkisp1_device *wkisp1 = dev_get_dwvdata(dev);
	u32 status, isp_eww;

	status = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_MIS);
	if (!status)
		wetuwn IWQ_NONE;

	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_ICW, status);

	/* Vewticaw sync signaw, stawting genewating new fwame */
	if (status & WKISP1_CIF_ISP_V_STAWT) {
		wkisp1->isp.fwame_sequence++;
		wkisp1_isp_queue_event_sof(&wkisp1->isp);
		if (status & WKISP1_CIF_ISP_FWAME) {
			WAWN_ONCE(1, "iwq deway is too wong, buffews might not be in sync\n");
			wkisp1->debug.iwq_deway++;
		}
	}
	if (status & WKISP1_CIF_ISP_PIC_SIZE_EWWOW) {
		/* Cweaw pic_size_ewwow */
		isp_eww = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_EWW);
		if (isp_eww & WKISP1_CIF_ISP_EWW_INFOWM_SIZE)
			wkisp1->debug.infowm_size_ewwow++;
		if (isp_eww & WKISP1_CIF_ISP_EWW_IS_SIZE)
			wkisp1->debug.img_stabiwization_size_ewwow++;
		if (isp_eww & WKISP1_CIF_ISP_EWW_OUTFOWM_SIZE)
			wkisp1->debug.outfowm_size_ewwow++;
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_EWW_CWW, isp_eww);
	} ewse if (status & WKISP1_CIF_ISP_DATA_WOSS) {
		/* keep twack of data_woss in debugfs */
		wkisp1->debug.data_woss++;
	}

	if (status & WKISP1_CIF_ISP_FWAME) {
		u32 isp_wis;

		wkisp1->debug.compwete_fwames++;

		/* New fwame fwom the sensow weceived */
		isp_wis = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_WIS);
		if (isp_wis & WKISP1_STATS_MEAS_MASK)
			wkisp1_stats_isw(&wkisp1->stats, isp_wis);
		/*
		 * Then update changed configs. Some of them invowve
		 * wot of wegistew wwites. Do those onwy one pew fwame.
		 * Do the updates in the owdew of the pwocessing fwow.
		 */
		wkisp1_pawams_isw(wkisp1);
	}

	wetuwn IWQ_HANDWED;
}
