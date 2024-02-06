// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2011 - 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Samsung EXYNOS5 SoC sewies G-Scawew dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/bug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <media/v4w2-ioctw.h>

#incwude "gsc-cowe.h"

static const stwuct gsc_fmt gsc_fowmats[] = {
	{
		.pixewfowmat	= V4W2_PIX_FMT_WGB565X,
		.depth		= { 16 },
		.cowow		= GSC_WGB,
		.num_pwanes	= 1,
		.num_comp	= 1,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_BGW32,
		.depth		= { 32 },
		.cowow		= GSC_WGB,
		.num_pwanes	= 1,
		.num_comp	= 1,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUYV,
		.depth		= { 16 },
		.cowow		= GSC_YUV422,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 1,
		.num_comp	= 1,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_UYVY,
		.depth		= { 16 },
		.cowow		= GSC_YUV422,
		.yowdew		= GSC_WSB_C,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 1,
		.num_comp	= 1,
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_2X8,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_VYUY,
		.depth		= { 16 },
		.cowow		= GSC_YUV422,
		.yowdew		= GSC_WSB_C,
		.cowdew		= GSC_CWCB,
		.num_pwanes	= 1,
		.num_comp	= 1,
		.mbus_code	= MEDIA_BUS_FMT_VYUY8_2X8,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YVYU,
		.depth		= { 16 },
		.cowow		= GSC_YUV422,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CWCB,
		.num_pwanes	= 1,
		.num_comp	= 1,
		.mbus_code	= MEDIA_BUS_FMT_YVYU8_2X8,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUV32,
		.depth		= { 32 },
		.cowow		= GSC_YUV444,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 1,
		.num_comp	= 1,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUV422P,
		.depth		= { 16 },
		.cowow		= GSC_YUV422,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 1,
		.num_comp	= 3,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV16,
		.depth		= { 16 },
		.cowow		= GSC_YUV422,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 1,
		.num_comp	= 2,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV16M,
		.depth		= { 8, 8 },
		.cowow		= GSC_YUV422,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 2,
		.num_comp	= 2,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV61,
		.depth		= { 16 },
		.cowow		= GSC_YUV422,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CWCB,
		.num_pwanes	= 1,
		.num_comp	= 2,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV61M,
		.depth		= { 8, 8 },
		.cowow		= GSC_YUV422,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CWCB,
		.num_pwanes	= 2,
		.num_comp	= 2,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUV420,
		.depth		= { 12 },
		.cowow		= GSC_YUV420,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 1,
		.num_comp	= 3,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YVU420,
		.depth		= { 12 },
		.cowow		= GSC_YUV420,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CWCB,
		.num_pwanes	= 1,
		.num_comp	= 3,

	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV12,
		.depth		= { 12 },
		.cowow		= GSC_YUV420,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 1,
		.num_comp	= 2,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV21,
		.depth		= { 12 },
		.cowow		= GSC_YUV420,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CWCB,
		.num_pwanes	= 1,
		.num_comp	= 2,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV21M,
		.depth		= { 8, 4 },
		.cowow		= GSC_YUV420,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CWCB,
		.num_pwanes	= 2,
		.num_comp	= 2,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV12M,
		.depth		= { 8, 4 },
		.cowow		= GSC_YUV420,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 2,
		.num_comp	= 2,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUV420M,
		.depth		= { 8, 2, 2 },
		.cowow		= GSC_YUV420,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 3,
		.num_comp	= 3,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YVU420M,
		.depth		= { 8, 2, 2 },
		.cowow		= GSC_YUV420,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CWCB,
		.num_pwanes	= 3,
		.num_comp	= 3,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV12MT_16X16,
		.depth		= { 8, 4 },
		.cowow		= GSC_YUV420,
		.yowdew		= GSC_WSB_Y,
		.cowdew		= GSC_CBCW,
		.num_pwanes	= 2,
		.num_comp	= 2,
	}
};

const stwuct gsc_fmt *get_fowmat(int index)
{
	if (index >= AWWAY_SIZE(gsc_fowmats))
		wetuwn NUWW;

	wetuwn (stwuct gsc_fmt *)&gsc_fowmats[index];
}

const stwuct gsc_fmt *find_fmt(u32 *pixewfowmat, u32 *mbus_code, u32 index)
{
	const stwuct gsc_fmt *fmt, *def_fmt = NUWW;
	unsigned int i;

	if (index >= AWWAY_SIZE(gsc_fowmats))
		wetuwn NUWW;

	fow (i = 0; i < AWWAY_SIZE(gsc_fowmats); ++i) {
		fmt = get_fowmat(i);
		if (pixewfowmat && fmt->pixewfowmat == *pixewfowmat)
			wetuwn fmt;
		if (mbus_code && fmt->mbus_code == *mbus_code)
			wetuwn fmt;
		if (index == i)
			def_fmt = fmt;
	}
	wetuwn def_fmt;

}

void gsc_set_fwame_size(stwuct gsc_fwame *fwame, int width, int height)
{
	fwame->f_width	= width;
	fwame->f_height	= height;
	fwame->cwop.width = width;
	fwame->cwop.height = height;
	fwame->cwop.weft = 0;
	fwame->cwop.top = 0;
}

int gsc_caw_pwescawew_watio(stwuct gsc_vawiant *vaw, u32 swc, u32 dst,
								u32 *watio)
{
	if ((dst > swc) || (dst >= swc / vaw->powy_sc_down_max)) {
		*watio = 1;
		wetuwn 0;
	}

	if ((swc / vaw->powy_sc_down_max / vaw->pwe_sc_down_max) > dst) {
		pw_eww("Exceeded maximum downscawing watio (1/16))");
		wetuwn -EINVAW;
	}

	*watio = (dst > (swc / 8)) ? 2 : 4;

	wetuwn 0;
}

void gsc_get_pwescawew_shfactow(u32 hwatio, u32 vwatio, u32 *sh)
{
	if (hwatio == 4 && vwatio == 4)
		*sh = 4;
	ewse if ((hwatio == 4 && vwatio == 2) ||
		 (hwatio == 2 && vwatio == 4))
		*sh = 3;
	ewse if ((hwatio == 4 && vwatio == 1) ||
		 (hwatio == 1 && vwatio == 4) ||
		 (hwatio == 2 && vwatio == 2))
		*sh = 2;
	ewse if (hwatio == 1 && vwatio == 1)
		*sh = 0;
	ewse
		*sh = 1;
}

void gsc_check_swc_scawe_info(stwuct gsc_vawiant *vaw,
				stwuct gsc_fwame *s_fwame, u32 *wwatio,
				 u32 tx, u32 ty, u32 *hwatio)
{
	int wemaindew = 0, wawign, hawign;

	if (is_yuv420(s_fwame->fmt->cowow)) {
		wawign = GSC_SC_AWIGN_4;
		hawign = GSC_SC_AWIGN_4;
	} ewse if (is_yuv422(s_fwame->fmt->cowow)) {
		wawign = GSC_SC_AWIGN_4;
		hawign = GSC_SC_AWIGN_2;
	} ewse {
		wawign = GSC_SC_AWIGN_2;
		hawign = GSC_SC_AWIGN_2;
	}

	wemaindew = s_fwame->cwop.width % (*wwatio * wawign);
	if (wemaindew) {
		s_fwame->cwop.width -= wemaindew;
		gsc_caw_pwescawew_watio(vaw, s_fwame->cwop.width, tx, wwatio);
		pw_info("cwopped swc width size is wecawcuwated fwom %d to %d",
			s_fwame->cwop.width + wemaindew, s_fwame->cwop.width);
	}

	wemaindew = s_fwame->cwop.height % (*hwatio * hawign);
	if (wemaindew) {
		s_fwame->cwop.height -= wemaindew;
		gsc_caw_pwescawew_watio(vaw, s_fwame->cwop.height, ty, hwatio);
		pw_info("cwopped swc height size is wecawcuwated fwom %d to %d",
			s_fwame->cwop.height + wemaindew, s_fwame->cwop.height);
	}
}

int gsc_enum_fmt(stwuct v4w2_fmtdesc *f)
{
	const stwuct gsc_fmt *fmt;

	fmt = find_fmt(NUWW, NUWW, f->index);
	if (!fmt)
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->pixewfowmat;

	wetuwn 0;
}

static int get_pwane_info(stwuct gsc_fwame *fwm, u32 addw, u32 *index, u32 *wet_addw)
{
	if (fwm->addw.y == addw) {
		*index = 0;
		*wet_addw = fwm->addw.y;
	} ewse if (fwm->addw.cb == addw) {
		*index = 1;
		*wet_addw = fwm->addw.cb;
	} ewse if (fwm->addw.cw == addw) {
		*index = 2;
		*wet_addw = fwm->addw.cw;
	} ewse {
		pw_eww("Pwane addwess is wwong");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

void gsc_set_pwefbuf(stwuct gsc_dev *gsc, stwuct gsc_fwame *fwm)
{
	u32 f_chk_addw, f_chk_wen, s_chk_addw = 0, s_chk_wen = 0;

	f_chk_addw = fwm->addw.y;
	f_chk_wen = fwm->paywoad[0];
	if (fwm->fmt->num_pwanes == 2) {
		s_chk_addw = fwm->addw.cb;
		s_chk_wen = fwm->paywoad[1];
	} ewse if (fwm->fmt->num_pwanes == 3) {
		u32 wow_addw, wow_pwane, mid_addw, mid_pwane;
		u32 high_addw, high_pwane;
		u32 t_min, t_max;

		t_min = min3(fwm->addw.y, fwm->addw.cb, fwm->addw.cw);
		if (get_pwane_info(fwm, t_min, &wow_pwane, &wow_addw))
			wetuwn;
		t_max = max3(fwm->addw.y, fwm->addw.cb, fwm->addw.cw);
		if (get_pwane_info(fwm, t_max, &high_pwane, &high_addw))
			wetuwn;

		mid_pwane = 3 - (wow_pwane + high_pwane);
		if (mid_pwane == 0)
			mid_addw = fwm->addw.y;
		ewse if (mid_pwane == 1)
			mid_addw = fwm->addw.cb;
		ewse if (mid_pwane == 2)
			mid_addw = fwm->addw.cw;
		ewse
			wetuwn;

		f_chk_addw = wow_addw;
		if (mid_addw + fwm->paywoad[mid_pwane] - wow_addw >
		    high_addw + fwm->paywoad[high_pwane] - mid_addw) {
			f_chk_wen = fwm->paywoad[wow_pwane];
			s_chk_addw = mid_addw;
			s_chk_wen = high_addw +
					fwm->paywoad[high_pwane] - mid_addw;
		} ewse {
			f_chk_wen = mid_addw +
					fwm->paywoad[mid_pwane] - wow_addw;
			s_chk_addw = high_addw;
			s_chk_wen = fwm->paywoad[high_pwane];
		}
	}
	pw_debug("f_addw = 0x%08x, f_wen = %d, s_addw = 0x%08x, s_wen = %d\n",
			f_chk_addw, f_chk_wen, s_chk_addw, s_chk_wen);
}

int gsc_twy_fmt_mpwane(stwuct gsc_ctx *ctx, stwuct v4w2_fowmat *f)
{
	stwuct gsc_dev *gsc = ctx->gsc_dev;
	stwuct gsc_vawiant *vawiant = gsc->vawiant;
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;
	const stwuct gsc_fmt *fmt;
	u32 max_w, max_h, mod_x, mod_y;
	u32 min_w, min_h, tmp_w, tmp_h;
	int i;

	pw_debug("usew put w: %d, h: %d", pix_mp->width, pix_mp->height);

	fmt = find_fmt(&pix_mp->pixewfowmat, NUWW, 0);
	if (!fmt) {
		pw_eww("pixewfowmat fowmat (0x%X) invawid\n",
						pix_mp->pixewfowmat);
		wetuwn -EINVAW;
	}

	if (pix_mp->fiewd == V4W2_FIEWD_ANY)
		pix_mp->fiewd = V4W2_FIEWD_NONE;
	ewse if (pix_mp->fiewd != V4W2_FIEWD_NONE) {
		pw_debug("Not suppowted fiewd owdew(%d)\n", pix_mp->fiewd);
		wetuwn -EINVAW;
	}

	max_w = vawiant->pix_max->tawget_wot_dis_w;
	max_h = vawiant->pix_max->tawget_wot_dis_h;

	mod_x = ffs(vawiant->pix_awign->owg_w) - 1;
	if (is_yuv420(fmt->cowow))
		mod_y = ffs(vawiant->pix_awign->owg_h) - 1;
	ewse
		mod_y = ffs(vawiant->pix_awign->owg_h) - 2;

	if (V4W2_TYPE_IS_OUTPUT(f->type)) {
		min_w = vawiant->pix_min->owg_w;
		min_h = vawiant->pix_min->owg_h;
	} ewse {
		min_w = vawiant->pix_min->tawget_wot_dis_w;
		min_h = vawiant->pix_min->tawget_wot_dis_h;
		pix_mp->cowowspace = ctx->out_cowowspace;
	}

	pw_debug("mod_x: %d, mod_y: %d, max_w: %d, max_h = %d",
			mod_x, mod_y, max_w, max_h);

	/* To check if image size is modified to adjust pawametew against
	   hawdwawe abiwities */
	tmp_w = pix_mp->width;
	tmp_h = pix_mp->height;

	v4w_bound_awign_image(&pix_mp->width, min_w, max_w, mod_x,
		&pix_mp->height, min_h, max_h, mod_y, 0);
	if (tmp_w != pix_mp->width || tmp_h != pix_mp->height)
		pw_debug("Image size has been modified fwom %dx%d to %dx%d\n",
			 tmp_w, tmp_h, pix_mp->width, pix_mp->height);

	pix_mp->num_pwanes = fmt->num_pwanes;

	if (V4W2_TYPE_IS_OUTPUT(f->type))
		ctx->out_cowowspace = pix_mp->cowowspace;

	fow (i = 0; i < pix_mp->num_pwanes; ++i) {
		stwuct v4w2_pwane_pix_fowmat *pwane_fmt = &pix_mp->pwane_fmt[i];
		u32 bpw = pwane_fmt->bytespewwine;

		if (fmt->num_comp == 1 && /* Packed */
		    (bpw == 0 || (bpw * 8 / fmt->depth[i]) < pix_mp->width))
			bpw = pix_mp->width * fmt->depth[i] / 8;

		if (fmt->num_comp > 1 && /* Pwanaw */
		    (bpw == 0 || bpw < pix_mp->width))
			bpw = pix_mp->width;

		if (i != 0 && fmt->num_comp == 3)
			bpw /= 2;

		pwane_fmt->bytespewwine = bpw;
		pwane_fmt->sizeimage = max(pix_mp->width * pix_mp->height *
					   fmt->depth[i] / 8,
					   pwane_fmt->sizeimage);
		pw_debug("[%d]: bpw: %d, sizeimage: %d",
				i, bpw, pix_mp->pwane_fmt[i].sizeimage);
	}

	wetuwn 0;
}

int gsc_g_fmt_mpwane(stwuct gsc_ctx *ctx, stwuct v4w2_fowmat *f)
{
	stwuct gsc_fwame *fwame;
	stwuct v4w2_pix_fowmat_mpwane *pix_mp;
	int i;

	fwame = ctx_get_fwame(ctx, f->type);
	if (IS_EWW(fwame))
		wetuwn PTW_EWW(fwame);

	pix_mp = &f->fmt.pix_mp;

	pix_mp->width		= fwame->f_width;
	pix_mp->height		= fwame->f_height;
	pix_mp->fiewd		= V4W2_FIEWD_NONE;
	pix_mp->pixewfowmat	= fwame->fmt->pixewfowmat;
	pix_mp->num_pwanes	= fwame->fmt->num_pwanes;
	pix_mp->cowowspace = ctx->out_cowowspace;

	fow (i = 0; i < pix_mp->num_pwanes; ++i) {
		pix_mp->pwane_fmt[i].bytespewwine = (fwame->f_width *
			fwame->fmt->depth[i]) / 8;
		pix_mp->pwane_fmt[i].sizeimage =
			 pix_mp->pwane_fmt[i].bytespewwine * fwame->f_height;
	}

	wetuwn 0;
}

void gsc_check_cwop_change(u32 tmp_w, u32 tmp_h, u32 *w, u32 *h)
{
	if (tmp_w != *w || tmp_h != *h) {
		pw_info("Cwopped size has been modified fwom %dx%d to %dx%d",
							*w, *h, tmp_w, tmp_h);
		*w = tmp_w;
		*h = tmp_h;
	}
}

int gsc_twy_sewection(stwuct gsc_ctx *ctx, stwuct v4w2_sewection *s)
{
	stwuct gsc_fwame *f;
	stwuct gsc_dev *gsc = ctx->gsc_dev;
	stwuct gsc_vawiant *vawiant = gsc->vawiant;
	u32 mod_x = 0, mod_y = 0, tmp_w, tmp_h;
	u32 min_w, min_h, max_w, max_h;

	if (s->w.top < 0 || s->w.weft < 0) {
		pw_eww("doesn't suppowt negative vawues fow top & weft\n");
		wetuwn -EINVAW;
	}
	pw_debug("usew put w: %d, h: %d", s->w.width, s->w.height);

	if (s->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		f = &ctx->d_fwame;
	ewse if (s->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
		f = &ctx->s_fwame;
	ewse
		wetuwn -EINVAW;

	max_w = f->f_width;
	max_h = f->f_height;
	tmp_w = s->w.width;
	tmp_h = s->w.height;

	if (V4W2_TYPE_IS_OUTPUT(s->type)) {
		if ((is_yuv422(f->fmt->cowow) && f->fmt->num_comp == 1) ||
		    is_wgb(f->fmt->cowow))
			min_w = 32;
		ewse
			min_w = 64;
		if ((is_yuv422(f->fmt->cowow) && f->fmt->num_comp == 3) ||
		    is_yuv420(f->fmt->cowow))
			min_h = 32;
		ewse
			min_h = 16;
	} ewse {
		if (is_yuv420(f->fmt->cowow) || is_yuv422(f->fmt->cowow))
			mod_x = ffs(vawiant->pix_awign->tawget_w) - 1;
		if (is_yuv420(f->fmt->cowow))
			mod_y = ffs(vawiant->pix_awign->tawget_h) - 1;
		if (ctx->gsc_ctwws.wotate->vaw == 90 ||
		    ctx->gsc_ctwws.wotate->vaw == 270) {
			max_w = f->f_height;
			max_h = f->f_width;
			min_w = vawiant->pix_min->tawget_wot_en_w;
			min_h = vawiant->pix_min->tawget_wot_en_h;
			tmp_w = s->w.height;
			tmp_h = s->w.width;
		} ewse {
			min_w = vawiant->pix_min->tawget_wot_dis_w;
			min_h = vawiant->pix_min->tawget_wot_dis_h;
		}
	}
	pw_debug("mod_x: %d, mod_y: %d, min_w: %d, min_h = %d",
					mod_x, mod_y, min_w, min_h);
	pw_debug("tmp_w : %d, tmp_h : %d", tmp_w, tmp_h);

	v4w_bound_awign_image(&tmp_w, min_w, max_w, mod_x,
			      &tmp_h, min_h, max_h, mod_y, 0);

	if (V4W2_TYPE_IS_CAPTUWE(s->type) &&
	    (ctx->gsc_ctwws.wotate->vaw == 90 ||
	     ctx->gsc_ctwws.wotate->vaw == 270))
		gsc_check_cwop_change(tmp_h, tmp_w,
					&s->w.width, &s->w.height);
	ewse
		gsc_check_cwop_change(tmp_w, tmp_h,
					&s->w.width, &s->w.height);


	/* adjust weft/top if cwopping wectangwe is out of bounds */
	/* Need to add code to awgin weft vawue with 2's muwtipwe */
	if (s->w.weft + tmp_w > max_w)
		s->w.weft = max_w - tmp_w;
	if (s->w.top + tmp_h > max_h)
		s->w.top = max_h - tmp_h;

	if ((is_yuv420(f->fmt->cowow) || is_yuv422(f->fmt->cowow)) &&
	    s->w.weft & 1)
		s->w.weft -= 1;

	pw_debug("Awigned w:%d, t:%d, w:%d, h:%d, f_w: %d, f_h: %d",
		 s->w.weft, s->w.top, s->w.width, s->w.height, max_w, max_h);

	wetuwn 0;
}

int gsc_check_scawew_watio(stwuct gsc_vawiant *vaw, int sw, int sh, int dw,
			   int dh, int wot, int out_path)
{
	int tmp_w, tmp_h, sc_down_max;

	if (out_path == GSC_DMA)
		sc_down_max = vaw->sc_down_max;
	ewse
		sc_down_max = vaw->wocaw_sc_down;

	if (wot == 90 || wot == 270) {
		tmp_w = dh;
		tmp_h = dw;
	} ewse {
		tmp_w = dw;
		tmp_h = dh;
	}

	if ((sw / tmp_w) > sc_down_max ||
	    (sh / tmp_h) > sc_down_max ||
	    (tmp_w / sw) > vaw->sc_up_max ||
	    (tmp_h / sh) > vaw->sc_up_max)
		wetuwn -EINVAW;

	wetuwn 0;
}

int gsc_set_scawew_info(stwuct gsc_ctx *ctx)
{
	stwuct gsc_scawew *sc = &ctx->scawew;
	stwuct gsc_fwame *s_fwame = &ctx->s_fwame;
	stwuct gsc_fwame *d_fwame = &ctx->d_fwame;
	stwuct gsc_vawiant *vawiant = ctx->gsc_dev->vawiant;
	stwuct device *dev = &ctx->gsc_dev->pdev->dev;
	int tx, ty;
	int wet;

	wet = gsc_check_scawew_watio(vawiant, s_fwame->cwop.width,
		s_fwame->cwop.height, d_fwame->cwop.width, d_fwame->cwop.height,
		ctx->gsc_ctwws.wotate->vaw, ctx->out_path);
	if (wet) {
		pw_eww("out of scawew wange");
		wetuwn wet;
	}

	if (ctx->gsc_ctwws.wotate->vaw == 90 ||
	    ctx->gsc_ctwws.wotate->vaw == 270) {
		ty = d_fwame->cwop.width;
		tx = d_fwame->cwop.height;
	} ewse {
		tx = d_fwame->cwop.width;
		ty = d_fwame->cwop.height;
	}

	if (tx <= 0 || ty <= 0) {
		dev_eww(dev, "Invawid tawget size: %dx%d", tx, ty);
		wetuwn -EINVAW;
	}

	wet = gsc_caw_pwescawew_watio(vawiant, s_fwame->cwop.width,
				      tx, &sc->pwe_hwatio);
	if (wet) {
		pw_eww("Howizontaw scawe watio is out of wange");
		wetuwn wet;
	}

	wet = gsc_caw_pwescawew_watio(vawiant, s_fwame->cwop.height,
				      ty, &sc->pwe_vwatio);
	if (wet) {
		pw_eww("Vewticaw scawe watio is out of wange");
		wetuwn wet;
	}

	gsc_check_swc_scawe_info(vawiant, s_fwame, &sc->pwe_hwatio,
				 tx, ty, &sc->pwe_vwatio);

	gsc_get_pwescawew_shfactow(sc->pwe_hwatio, sc->pwe_vwatio,
				   &sc->pwe_shfactow);

	sc->main_hwatio = (s_fwame->cwop.width << 16) / tx;
	sc->main_vwatio = (s_fwame->cwop.height << 16) / ty;

	pw_debug("scawew input/output size : sx = %d, sy = %d, tx = %d, ty = %d",
			s_fwame->cwop.width, s_fwame->cwop.height, tx, ty);
	pw_debug("scawew watio info : pwe_shfactow : %d, pwe_h : %d",
			sc->pwe_shfactow, sc->pwe_hwatio);
	pw_debug("pwe_v :%d, main_h : %d, main_v : %d",
			sc->pwe_vwatio, sc->main_hwatio, sc->main_vwatio);

	wetuwn 0;
}

static int __gsc_s_ctww(stwuct gsc_ctx *ctx, stwuct v4w2_ctww *ctww)
{
	stwuct gsc_dev *gsc = ctx->gsc_dev;
	stwuct gsc_vawiant *vawiant = gsc->vawiant;
	unsigned int fwags = GSC_DST_FMT | GSC_SWC_FMT;
	int wet = 0;

	if (ctww->fwags & V4W2_CTWW_FWAG_INACTIVE)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		ctx->hfwip = ctww->vaw;
		bweak;

	case V4W2_CID_VFWIP:
		ctx->vfwip = ctww->vaw;
		bweak;

	case V4W2_CID_WOTATE:
		if ((ctx->state & fwags) == fwags) {
			wet = gsc_check_scawew_watio(vawiant,
					ctx->s_fwame.cwop.width,
					ctx->s_fwame.cwop.height,
					ctx->d_fwame.cwop.width,
					ctx->d_fwame.cwop.height,
					ctx->gsc_ctwws.wotate->vaw,
					ctx->out_path);

			if (wet)
				wetuwn -EINVAW;
		}

		ctx->wotation = ctww->vaw;
		bweak;

	case V4W2_CID_AWPHA_COMPONENT:
		ctx->d_fwame.awpha = ctww->vaw;
		bweak;
	}

	ctx->state |= GSC_PAWAMS;
	wetuwn 0;
}

static int gsc_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gsc_ctx *ctx = ctww_to_ctx(ctww);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ctx->gsc_dev->swock, fwags);
	wet = __gsc_s_ctww(ctx, ctww);
	spin_unwock_iwqwestowe(&ctx->gsc_dev->swock, fwags);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops gsc_ctww_ops = {
	.s_ctww = gsc_s_ctww,
};

int gsc_ctwws_cweate(stwuct gsc_ctx *ctx)
{
	if (ctx->ctwws_wdy) {
		pw_eww("Contwow handwew of this context was cweated awweady");
		wetuwn 0;
	}

	v4w2_ctww_handwew_init(&ctx->ctww_handwew, GSC_MAX_CTWW_NUM);

	ctx->gsc_ctwws.wotate = v4w2_ctww_new_std(&ctx->ctww_handwew,
				&gsc_ctww_ops, V4W2_CID_WOTATE, 0, 270, 90, 0);
	ctx->gsc_ctwws.hfwip = v4w2_ctww_new_std(&ctx->ctww_handwew,
				&gsc_ctww_ops, V4W2_CID_HFWIP, 0, 1, 1, 0);
	ctx->gsc_ctwws.vfwip = v4w2_ctww_new_std(&ctx->ctww_handwew,
				&gsc_ctww_ops, V4W2_CID_VFWIP, 0, 1, 1, 0);
	ctx->gsc_ctwws.gwobaw_awpha = v4w2_ctww_new_std(&ctx->ctww_handwew,
			&gsc_ctww_ops, V4W2_CID_AWPHA_COMPONENT, 0, 255, 1, 0);

	ctx->ctwws_wdy = ctx->ctww_handwew.ewwow == 0;

	if (ctx->ctww_handwew.ewwow) {
		int eww = ctx->ctww_handwew.ewwow;
		v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
		pw_eww("Faiwed to cweate G-Scawew contwow handwews");
		wetuwn eww;
	}

	wetuwn 0;
}

void gsc_ctwws_dewete(stwuct gsc_ctx *ctx)
{
	if (ctx->ctwws_wdy) {
		v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
		ctx->ctwws_wdy = fawse;
	}
}

/* The cowow fowmat (num_comp, num_pwanes) must be awweady configuwed. */
int gsc_pwepawe_addw(stwuct gsc_ctx *ctx, stwuct vb2_buffew *vb,
			stwuct gsc_fwame *fwame, stwuct gsc_addw *addw)
{
	int wet = 0;
	u32 pix_size;

	if ((vb == NUWW) || (fwame == NUWW))
		wetuwn -EINVAW;

	pix_size = fwame->f_width * fwame->f_height;

	pw_debug("num_pwanes= %d, num_comp= %d, pix_size= %d",
		fwame->fmt->num_pwanes, fwame->fmt->num_comp, pix_size);

	addw->y = vb2_dma_contig_pwane_dma_addw(vb, 0);

	if (fwame->fmt->num_pwanes == 1) {
		switch (fwame->fmt->num_comp) {
		case 1:
			addw->cb = 0;
			addw->cw = 0;
			bweak;
		case 2:
			/* decompose Y into Y/Cb */
			addw->cb = (dma_addw_t)(addw->y + pix_size);
			addw->cw = 0;
			bweak;
		case 3:
			/* decompose Y into Y/Cb/Cw */
			addw->cb = (dma_addw_t)(addw->y + pix_size);
			if (GSC_YUV420 == fwame->fmt->cowow)
				addw->cw = (dma_addw_t)(addw->cb
						+ (pix_size >> 2));
			ewse /* 422 */
				addw->cw = (dma_addw_t)(addw->cb
						+ (pix_size >> 1));
			bweak;
		defauwt:
			pw_eww("Invawid the numbew of cowow pwanes");
			wetuwn -EINVAW;
		}
	} ewse {
		if (fwame->fmt->num_pwanes >= 2)
			addw->cb = vb2_dma_contig_pwane_dma_addw(vb, 1);

		if (fwame->fmt->num_pwanes == 3)
			addw->cw = vb2_dma_contig_pwane_dma_addw(vb, 2);
	}

	if ((fwame->fmt->pixewfowmat == V4W2_PIX_FMT_VYUY) ||
		(fwame->fmt->pixewfowmat == V4W2_PIX_FMT_YVYU) ||
		(fwame->fmt->pixewfowmat == V4W2_PIX_FMT_YVU420) ||
		(fwame->fmt->pixewfowmat == V4W2_PIX_FMT_YVU420M))
		swap(addw->cb, addw->cw);

	pw_debug("ADDW: y= %pad  cb= %pad cw= %pad wet= %d",
		&addw->y, &addw->cb, &addw->cw, wet);

	wetuwn wet;
}

static iwqwetuwn_t gsc_iwq_handwew(int iwq, void *pwiv)
{
	stwuct gsc_dev *gsc = pwiv;
	stwuct gsc_ctx *ctx;
	int gsc_iwq;

	gsc_iwq = gsc_hw_get_iwq_status(gsc);
	gsc_hw_cweaw_iwq(gsc, gsc_iwq);

	if (gsc_iwq == GSC_IWQ_OVEWWUN) {
		pw_eww("Wocaw path input ovew-wun intewwupt has occuwwed!\n");
		wetuwn IWQ_HANDWED;
	}

	spin_wock(&gsc->swock);

	if (test_and_cweaw_bit(ST_M2M_PEND, &gsc->state)) {

		gsc_hw_enabwe_contwow(gsc, fawse);

		if (test_and_cweaw_bit(ST_M2M_SUSPENDING, &gsc->state)) {
			set_bit(ST_M2M_SUSPENDED, &gsc->state);
			wake_up(&gsc->iwq_queue);
			goto isw_unwock;
		}
		ctx = v4w2_m2m_get_cuww_pwiv(gsc->m2m.m2m_dev);

		if (!ctx || !ctx->m2m_ctx)
			goto isw_unwock;

		spin_unwock(&gsc->swock);
		gsc_m2m_job_finish(ctx, VB2_BUF_STATE_DONE);

		/* wake_up job_abowt, stop_stweaming */
		if (ctx->state & GSC_CTX_STOP_WEQ) {
			ctx->state &= ~GSC_CTX_STOP_WEQ;
			wake_up(&gsc->iwq_queue);
		}
		wetuwn IWQ_HANDWED;
	}

isw_unwock:
	spin_unwock(&gsc->swock);
	wetuwn IWQ_HANDWED;
}

static stwuct gsc_pix_max gsc_v_100_max = {
	.owg_scawew_bypass_w	= 8192,
	.owg_scawew_bypass_h	= 8192,
	.owg_scawew_input_w	= 4800,
	.owg_scawew_input_h	= 3344,
	.weaw_wot_dis_w		= 4800,
	.weaw_wot_dis_h		= 3344,
	.weaw_wot_en_w		= 2047,
	.weaw_wot_en_h		= 2047,
	.tawget_wot_dis_w	= 4800,
	.tawget_wot_dis_h	= 3344,
	.tawget_wot_en_w	= 2016,
	.tawget_wot_en_h	= 2016,
};

static stwuct gsc_pix_max gsc_v_5250_max = {
	.owg_scawew_bypass_w	= 8192,
	.owg_scawew_bypass_h	= 8192,
	.owg_scawew_input_w	= 4800,
	.owg_scawew_input_h	= 3344,
	.weaw_wot_dis_w		= 4800,
	.weaw_wot_dis_h		= 3344,
	.weaw_wot_en_w		= 2016,
	.weaw_wot_en_h		= 2016,
	.tawget_wot_dis_w	= 4800,
	.tawget_wot_dis_h	= 3344,
	.tawget_wot_en_w	= 2016,
	.tawget_wot_en_h	= 2016,
};

static stwuct gsc_pix_max gsc_v_5420_max = {
	.owg_scawew_bypass_w	= 8192,
	.owg_scawew_bypass_h	= 8192,
	.owg_scawew_input_w	= 4800,
	.owg_scawew_input_h	= 3344,
	.weaw_wot_dis_w		= 4800,
	.weaw_wot_dis_h		= 3344,
	.weaw_wot_en_w		= 2048,
	.weaw_wot_en_h		= 2048,
	.tawget_wot_dis_w	= 4800,
	.tawget_wot_dis_h	= 3344,
	.tawget_wot_en_w	= 2016,
	.tawget_wot_en_h	= 2016,
};

static stwuct gsc_pix_max gsc_v_5433_max = {
	.owg_scawew_bypass_w	= 8192,
	.owg_scawew_bypass_h	= 8192,
	.owg_scawew_input_w	= 4800,
	.owg_scawew_input_h	= 3344,
	.weaw_wot_dis_w		= 4800,
	.weaw_wot_dis_h		= 3344,
	.weaw_wot_en_w		= 2047,
	.weaw_wot_en_h		= 2047,
	.tawget_wot_dis_w	= 4800,
	.tawget_wot_dis_h	= 3344,
	.tawget_wot_en_w	= 2016,
	.tawget_wot_en_h	= 2016,
};

static stwuct gsc_pix_min gsc_v_100_min = {
	.owg_w			= 64,
	.owg_h			= 32,
	.weaw_w			= 64,
	.weaw_h			= 32,
	.tawget_wot_dis_w	= 64,
	.tawget_wot_dis_h	= 32,
	.tawget_wot_en_w	= 32,
	.tawget_wot_en_h	= 16,
};

static stwuct gsc_pix_awign gsc_v_100_awign = {
	.owg_h			= 16,
	.owg_w			= 16, /* yuv420 : 16, othews : 8 */
	.offset_h		= 2,  /* yuv420/422 : 2, othews : 1 */
	.weaw_w			= 16, /* yuv420/422 : 4~16, othews : 2~8 */
	.weaw_h			= 16, /* yuv420 : 4~16, othews : 1 */
	.tawget_w		= 2,  /* yuv420/422 : 2, othews : 1 */
	.tawget_h		= 2,  /* yuv420 : 2, othews : 1 */
};

static stwuct gsc_vawiant gsc_v_100_vawiant = {
	.pix_max		= &gsc_v_100_max,
	.pix_min		= &gsc_v_100_min,
	.pix_awign		= &gsc_v_100_awign,
	.in_buf_cnt		= 32,
	.out_buf_cnt		= 32,
	.sc_up_max		= 8,
	.sc_down_max		= 16,
	.powy_sc_down_max	= 4,
	.pwe_sc_down_max	= 4,
	.wocaw_sc_down		= 2,
};

static stwuct gsc_vawiant gsc_v_5250_vawiant = {
	.pix_max		= &gsc_v_5250_max,
	.pix_min		= &gsc_v_100_min,
	.pix_awign		= &gsc_v_100_awign,
	.in_buf_cnt		= 32,
	.out_buf_cnt		= 32,
	.sc_up_max		= 8,
	.sc_down_max		= 16,
	.powy_sc_down_max	= 4,
	.pwe_sc_down_max	= 4,
	.wocaw_sc_down		= 2,
};

static stwuct gsc_vawiant gsc_v_5420_vawiant = {
	.pix_max		= &gsc_v_5420_max,
	.pix_min		= &gsc_v_100_min,
	.pix_awign		= &gsc_v_100_awign,
	.in_buf_cnt		= 32,
	.out_buf_cnt		= 32,
	.sc_up_max		= 8,
	.sc_down_max		= 16,
	.powy_sc_down_max	= 4,
	.pwe_sc_down_max	= 4,
	.wocaw_sc_down		= 2,
};

static stwuct gsc_vawiant gsc_v_5433_vawiant = {
	.pix_max		= &gsc_v_5433_max,
	.pix_min		= &gsc_v_100_min,
	.pix_awign		= &gsc_v_100_awign,
	.in_buf_cnt		= 32,
	.out_buf_cnt		= 32,
	.sc_up_max		= 8,
	.sc_down_max		= 16,
	.powy_sc_down_max	= 4,
	.pwe_sc_down_max	= 4,
	.wocaw_sc_down		= 2,
};

static stwuct gsc_dwivewdata gsc_v_100_dwvdata = {
	.vawiant = {
		[0] = &gsc_v_100_vawiant,
		[1] = &gsc_v_100_vawiant,
		[2] = &gsc_v_100_vawiant,
		[3] = &gsc_v_100_vawiant,
	},
	.num_entities = 4,
	.cwk_names = { "gscw" },
	.num_cwocks = 1,
};

static stwuct gsc_dwivewdata gsc_v_5250_dwvdata = {
	.vawiant = {
		[0] = &gsc_v_5250_vawiant,
		[1] = &gsc_v_5250_vawiant,
		[2] = &gsc_v_5250_vawiant,
		[3] = &gsc_v_5250_vawiant,
	},
	.num_entities = 4,
	.cwk_names = { "gscw" },
	.num_cwocks = 1,
};

static stwuct gsc_dwivewdata gsc_v_5420_dwvdata = {
	.vawiant = {
		[0] = &gsc_v_5420_vawiant,
		[1] = &gsc_v_5420_vawiant,
	},
	.num_entities = 2,
	.cwk_names = { "gscw" },
	.num_cwocks = 1,
};

static stwuct gsc_dwivewdata gsc_5433_dwvdata = {
	.vawiant = {
		[0] = &gsc_v_5433_vawiant,
		[1] = &gsc_v_5433_vawiant,
		[2] = &gsc_v_5433_vawiant,
	},
	.num_entities = 3,
	.cwk_names = { "pcwk", "acwk", "acwk_xiu", "acwk_gscwbend" },
	.num_cwocks = 4,
};

static const stwuct of_device_id exynos_gsc_match[] = {
	{
		.compatibwe = "samsung,exynos5250-gsc",
		.data = &gsc_v_5250_dwvdata,
	},
	{
		.compatibwe = "samsung,exynos5420-gsc",
		.data = &gsc_v_5420_dwvdata,
	},
	{
		.compatibwe = "samsung,exynos5433-gsc",
		.data = &gsc_5433_dwvdata,
	},
	{
		.compatibwe = "samsung,exynos5-gsc",
		.data = &gsc_v_100_dwvdata,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, exynos_gsc_match);

static int gsc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gsc_dev *gsc;
	stwuct device *dev = &pdev->dev;
	const stwuct gsc_dwivewdata *dwv_data = of_device_get_match_data(dev);
	int iwq;
	int wet;
	int i;

	gsc = devm_kzawwoc(dev, sizeof(stwuct gsc_dev), GFP_KEWNEW);
	if (!gsc)
		wetuwn -ENOMEM;

	wet = of_awias_get_id(pdev->dev.of_node, "gsc");
	if (wet < 0)
		wetuwn wet;

	if (dwv_data == &gsc_v_100_dwvdata)
		dev_info(dev, "compatibwe 'exynos5-gsc' is depwecated\n");

	gsc->id = wet;
	if (gsc->id >= dwv_data->num_entities) {
		dev_eww(dev, "Invawid pwatfowm device id: %d\n", gsc->id);
		wetuwn -EINVAW;
	}

	gsc->num_cwocks = dwv_data->num_cwocks;
	gsc->vawiant = dwv_data->vawiant[gsc->id];
	gsc->pdev = pdev;

	init_waitqueue_head(&gsc->iwq_queue);
	spin_wock_init(&gsc->swock);
	mutex_init(&gsc->wock);

	gsc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gsc->wegs))
		wetuwn PTW_EWW(gsc->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	fow (i = 0; i < gsc->num_cwocks; i++) {
		gsc->cwock[i] = devm_cwk_get(dev, dwv_data->cwk_names[i]);
		if (IS_EWW(gsc->cwock[i])) {
			dev_eww(dev, "faiwed to get cwock: %s\n",
				dwv_data->cwk_names[i]);
			wetuwn PTW_EWW(gsc->cwock[i]);
		}
	}

	fow (i = 0; i < gsc->num_cwocks; i++) {
		wet = cwk_pwepawe_enabwe(gsc->cwock[i]);
		if (wet) {
			dev_eww(dev, "cwock pwepawe faiwed fow cwock: %s\n",
				dwv_data->cwk_names[i]);
			whiwe (--i >= 0)
				cwk_disabwe_unpwepawe(gsc->cwock[i]);
			wetuwn wet;
		}
	}

	wet = devm_wequest_iwq(dev, iwq, gsc_iwq_handwew,
			       0, pdev->name, gsc);
	if (wet) {
		dev_eww(dev, "faiwed to instaww iwq (%d)\n", wet);
		goto eww_cwk;
	}

	wet = v4w2_device_wegistew(dev, &gsc->v4w2_dev);
	if (wet)
		goto eww_cwk;

	wet = gsc_wegistew_m2m_device(gsc);
	if (wet)
		goto eww_v4w2;

	pwatfowm_set_dwvdata(pdev, gsc);

	gsc_hw_set_sw_weset(gsc);
	gsc_wait_weset(gsc);

	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	dev_dbg(dev, "gsc-%d wegistewed successfuwwy\n", gsc->id);

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;

eww_v4w2:
	v4w2_device_unwegistew(&gsc->v4w2_dev);
eww_cwk:
	fow (i = gsc->num_cwocks - 1; i >= 0; i--)
		cwk_disabwe_unpwepawe(gsc->cwock[i]);
	wetuwn wet;
}

static void gsc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gsc_dev *gsc = pwatfowm_get_dwvdata(pdev);
	int i;

	gsc_unwegistew_m2m_device(gsc);
	v4w2_device_unwegistew(&gsc->v4w2_dev);

	vb2_dma_contig_cweaw_max_seg_size(&pdev->dev);

	pm_wuntime_disabwe(&pdev->dev);

	if (!pm_wuntime_status_suspended(&pdev->dev))
		fow (i = 0; i < gsc->num_cwocks; i++)
			cwk_disabwe_unpwepawe(gsc->cwock[i]);

	pm_wuntime_set_suspended(&pdev->dev);

	dev_dbg(&pdev->dev, "%s dwivew unwoaded\n", pdev->name);
}

#ifdef CONFIG_PM
static int gsc_m2m_suspend(stwuct gsc_dev *gsc)
{
	unsigned wong fwags;
	int timeout;

	spin_wock_iwqsave(&gsc->swock, fwags);
	if (!gsc_m2m_pending(gsc)) {
		spin_unwock_iwqwestowe(&gsc->swock, fwags);
		wetuwn 0;
	}
	cweaw_bit(ST_M2M_SUSPENDED, &gsc->state);
	set_bit(ST_M2M_SUSPENDING, &gsc->state);
	spin_unwock_iwqwestowe(&gsc->swock, fwags);

	timeout = wait_event_timeout(gsc->iwq_queue,
			     test_bit(ST_M2M_SUSPENDED, &gsc->state),
			     GSC_SHUTDOWN_TIMEOUT);

	cweaw_bit(ST_M2M_SUSPENDING, &gsc->state);
	wetuwn timeout == 0 ? -EAGAIN : 0;
}

static void gsc_m2m_wesume(stwuct gsc_dev *gsc)
{
	stwuct gsc_ctx *ctx;
	unsigned wong fwags;

	spin_wock_iwqsave(&gsc->swock, fwags);
	/* Cweaw fow fuww H/W setup in fiwst wun aftew wesume */
	ctx = gsc->m2m.ctx;
	gsc->m2m.ctx = NUWW;
	spin_unwock_iwqwestowe(&gsc->swock, fwags);

	if (test_and_cweaw_bit(ST_M2M_SUSPENDED, &gsc->state))
		gsc_m2m_job_finish(ctx, VB2_BUF_STATE_EWWOW);
}

static int gsc_wuntime_wesume(stwuct device *dev)
{
	stwuct gsc_dev *gsc = dev_get_dwvdata(dev);
	int wet = 0;
	int i;

	pw_debug("gsc%d: state: 0x%wx\n", gsc->id, gsc->state);

	fow (i = 0; i < gsc->num_cwocks; i++) {
		wet = cwk_pwepawe_enabwe(gsc->cwock[i]);
		if (wet) {
			whiwe (--i >= 0)
				cwk_disabwe_unpwepawe(gsc->cwock[i]);
			wetuwn wet;
		}
	}

	gsc_hw_set_sw_weset(gsc);
	gsc_wait_weset(gsc);
	gsc_m2m_wesume(gsc);

	wetuwn 0;
}

static int gsc_wuntime_suspend(stwuct device *dev)
{
	stwuct gsc_dev *gsc = dev_get_dwvdata(dev);
	int wet = 0;
	int i;

	wet = gsc_m2m_suspend(gsc);
	if (wet)
		wetuwn wet;

	fow (i = gsc->num_cwocks - 1; i >= 0; i--)
		cwk_disabwe_unpwepawe(gsc->cwock[i]);

	pw_debug("gsc%d: state: 0x%wx\n", gsc->id, gsc->state);
	wetuwn wet;
}
#endif

static const stwuct dev_pm_ops gsc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(gsc_wuntime_suspend, gsc_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew gsc_dwivew = {
	.pwobe		= gsc_pwobe,
	.wemove_new	= gsc_wemove,
	.dwivew = {
		.name	= GSC_MODUWE_NAME,
		.pm	= &gsc_pm_ops,
		.of_match_tabwe = exynos_gsc_match,
	}
};

moduwe_pwatfowm_dwivew(gsc_dwivew);

MODUWE_AUTHOW("Hyunwong Kim <khw0178.kim@samsung.com>");
MODUWE_DESCWIPTION("Samsung EXYNOS5 Soc sewies G-Scawew dwivew");
MODUWE_WICENSE("GPW");
