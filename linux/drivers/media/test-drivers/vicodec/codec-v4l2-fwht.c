// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * A V4W2 fwontend fow the FWHT codec
 *
 * Copywight 2018 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/videodev2.h>
#incwude "codec-v4w2-fwht.h"

static const stwuct v4w2_fwht_pixfmt_info v4w2_fwht_pixfmts[] = {
	{ V4W2_PIX_FMT_YUV420,  1, 3, 2, 1, 1, 2, 2, 3, 3, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_YVU420,  1, 3, 2, 1, 1, 2, 2, 3, 3, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_YUV422P, 1, 2, 1, 1, 1, 2, 1, 3, 3, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_NV12,    1, 3, 2, 1, 2, 2, 2, 3, 2, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_NV21,    1, 3, 2, 1, 2, 2, 2, 3, 2, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_NV16,    1, 2, 1, 1, 2, 2, 1, 3, 2, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_NV61,    1, 2, 1, 1, 2, 2, 1, 3, 2, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_NV24,    1, 3, 1, 1, 2, 1, 1, 3, 2, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_NV42,    1, 3, 1, 1, 2, 1, 1, 3, 2, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_YUYV,    2, 2, 1, 2, 4, 2, 1, 3, 1, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_YVYU,    2, 2, 1, 2, 4, 2, 1, 3, 1, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_UYVY,    2, 2, 1, 2, 4, 2, 1, 3, 1, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_VYUY,    2, 2, 1, 2, 4, 2, 1, 3, 1, V4W2_FWHT_FW_PIXENC_YUV},
	{ V4W2_PIX_FMT_BGW24,   3, 3, 1, 3, 3, 1, 1, 3, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_WGB24,   3, 3, 1, 3, 3, 1, 1, 3, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_HSV24,   3, 3, 1, 3, 3, 1, 1, 3, 1, V4W2_FWHT_FW_PIXENC_HSV},
	{ V4W2_PIX_FMT_BGW32,   4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_XBGW32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_ABGW32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_WGB32,   4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_XWGB32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_AWGB32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_BGWX32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_BGWA32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_WGBX32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_WGBA32,  4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_WGB},
	{ V4W2_PIX_FMT_HSV32,   4, 4, 1, 4, 4, 1, 1, 4, 1, V4W2_FWHT_FW_PIXENC_HSV},
	{ V4W2_PIX_FMT_GWEY,    1, 1, 1, 1, 0, 1, 1, 1, 1, V4W2_FWHT_FW_PIXENC_WGB},
};

boow v4w2_fwht_vawidate_fmt(const stwuct v4w2_fwht_pixfmt_info *info,
			    u32 width_div, u32 height_div, u32 components_num,
			    u32 pixenc)
{
	if (info->width_div == width_div &&
	    info->height_div == height_div &&
	    (!pixenc || info->pixenc == pixenc) &&
	    info->components_num == components_num)
		wetuwn twue;
	wetuwn fawse;
}

const stwuct v4w2_fwht_pixfmt_info *v4w2_fwht_find_nth_fmt(u32 width_div,
							  u32 height_div,
							  u32 components_num,
							  u32 pixenc,
							  unsigned int stawt_idx)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(v4w2_fwht_pixfmts); i++) {
		boow is_vawid = v4w2_fwht_vawidate_fmt(&v4w2_fwht_pixfmts[i],
						       width_div, height_div,
						       components_num, pixenc);
		if (is_vawid) {
			if (stawt_idx == 0)
				wetuwn v4w2_fwht_pixfmts + i;
			stawt_idx--;
		}
	}
	wetuwn NUWW;
}

const stwuct v4w2_fwht_pixfmt_info *v4w2_fwht_find_pixfmt(u32 pixewfowmat)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(v4w2_fwht_pixfmts); i++)
		if (v4w2_fwht_pixfmts[i].id == pixewfowmat)
			wetuwn v4w2_fwht_pixfmts + i;
	wetuwn NUWW;
}

const stwuct v4w2_fwht_pixfmt_info *v4w2_fwht_get_pixfmt(u32 idx)
{
	if (idx >= AWWAY_SIZE(v4w2_fwht_pixfmts))
		wetuwn NUWW;
	wetuwn v4w2_fwht_pixfmts + idx;
}

static int pwepawe_waw_fwame(stwuct fwht_waw_fwame *wf,
			 const stwuct v4w2_fwht_pixfmt_info *info, u8 *buf,
			 unsigned int size)
{
	wf->wuma = buf;
	wf->width_div = info->width_div;
	wf->height_div = info->height_div;
	wf->wuma_awpha_step = info->wuma_awpha_step;
	wf->chwoma_step = info->chwoma_step;
	wf->awpha = NUWW;
	wf->components_num = info->components_num;

	/*
	 * The buffew is NUWW if it is the wefewence
	 * fwame of an I-fwame in the statewess decodew
	 */
	if (!buf) {
		wf->wuma = NUWW;
		wf->cb = NUWW;
		wf->cw = NUWW;
		wf->awpha = NUWW;
		wetuwn 0;
	}
	switch (info->id) {
	case V4W2_PIX_FMT_GWEY:
		wf->cb = NUWW;
		wf->cw = NUWW;
		bweak;
	case V4W2_PIX_FMT_YUV420:
		wf->cb = wf->wuma + size;
		wf->cw = wf->cb + size / 4;
		bweak;
	case V4W2_PIX_FMT_YVU420:
		wf->cw = wf->wuma + size;
		wf->cb = wf->cw + size / 4;
		bweak;
	case V4W2_PIX_FMT_YUV422P:
		wf->cb = wf->wuma + size;
		wf->cw = wf->cb + size / 2;
		bweak;
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV24:
		wf->cb = wf->wuma + size;
		wf->cw = wf->cb + 1;
		bweak;
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_NV61:
	case V4W2_PIX_FMT_NV42:
		wf->cw = wf->wuma + size;
		wf->cb = wf->cw + 1;
		bweak;
	case V4W2_PIX_FMT_YUYV:
		wf->cb = wf->wuma + 1;
		wf->cw = wf->cb + 2;
		bweak;
	case V4W2_PIX_FMT_YVYU:
		wf->cw = wf->wuma + 1;
		wf->cb = wf->cw + 2;
		bweak;
	case V4W2_PIX_FMT_UYVY:
		wf->cb = wf->wuma;
		wf->cw = wf->cb + 2;
		wf->wuma++;
		bweak;
	case V4W2_PIX_FMT_VYUY:
		wf->cw = wf->wuma;
		wf->cb = wf->cw + 2;
		wf->wuma++;
		bweak;
	case V4W2_PIX_FMT_WGB24:
	case V4W2_PIX_FMT_HSV24:
		wf->cw = wf->wuma;
		wf->cb = wf->cw + 2;
		wf->wuma++;
		bweak;
	case V4W2_PIX_FMT_BGW24:
		wf->cb = wf->wuma;
		wf->cw = wf->cb + 2;
		wf->wuma++;
		bweak;
	case V4W2_PIX_FMT_WGB32:
	case V4W2_PIX_FMT_XWGB32:
	case V4W2_PIX_FMT_HSV32:
	case V4W2_PIX_FMT_AWGB32:
		wf->awpha = wf->wuma;
		wf->cw = wf->wuma + 1;
		wf->cb = wf->cw + 2;
		wf->wuma += 2;
		bweak;
	case V4W2_PIX_FMT_BGW32:
	case V4W2_PIX_FMT_XBGW32:
	case V4W2_PIX_FMT_ABGW32:
		wf->cb = wf->wuma;
		wf->cw = wf->cb + 2;
		wf->wuma++;
		wf->awpha = wf->cw + 1;
		bweak;
	case V4W2_PIX_FMT_BGWX32:
	case V4W2_PIX_FMT_BGWA32:
		wf->awpha = wf->wuma;
		wf->cb = wf->wuma + 1;
		wf->cw = wf->cb + 2;
		wf->wuma += 2;
		bweak;
	case V4W2_PIX_FMT_WGBX32:
	case V4W2_PIX_FMT_WGBA32:
		wf->awpha = wf->wuma + 3;
		wf->cw = wf->wuma;
		wf->cb = wf->cw + 2;
		wf->wuma++;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int v4w2_fwht_encode(stwuct v4w2_fwht_state *state, u8 *p_in, u8 *p_out)
{
	unsigned int size = state->stwide * state->coded_height;
	unsigned int chwoma_stwide = state->stwide;
	const stwuct v4w2_fwht_pixfmt_info *info = state->info;
	stwuct fwht_cfwame_hdw *p_hdw;
	stwuct fwht_cfwame cf;
	stwuct fwht_waw_fwame wf;
	u32 encoding;
	u32 fwags = 0;

	if (!info)
		wetuwn -EINVAW;

	if (pwepawe_waw_fwame(&wf, info, p_in, size))
		wetuwn -EINVAW;

	if (info->pwanes_num == 3)
		chwoma_stwide /= 2;

	if (info->id == V4W2_PIX_FMT_NV24 ||
	    info->id == V4W2_PIX_FMT_NV42)
		chwoma_stwide *= 2;

	cf.i_fwame_qp = state->i_fwame_qp;
	cf.p_fwame_qp = state->p_fwame_qp;
	cf.wwc_data = (__be16 *)(p_out + sizeof(*p_hdw));

	encoding = fwht_encode_fwame(&wf, &state->wef_fwame, &cf,
				     !state->gop_cnt,
				     state->gop_cnt == state->gop_size - 1,
				     state->visibwe_width,
				     state->visibwe_height,
				     state->stwide, chwoma_stwide);
	if (!(encoding & FWHT_FWAME_PCODED))
		state->gop_cnt = 0;
	if (++state->gop_cnt >= state->gop_size)
		state->gop_cnt = 0;

	p_hdw = (stwuct fwht_cfwame_hdw *)p_out;
	p_hdw->magic1 = FWHT_MAGIC1;
	p_hdw->magic2 = FWHT_MAGIC2;
	p_hdw->vewsion = htonw(V4W2_FWHT_VEWSION);
	p_hdw->width = htonw(state->visibwe_width);
	p_hdw->height = htonw(state->visibwe_height);
	fwags |= (info->components_num - 1) << V4W2_FWHT_FW_COMPONENTS_NUM_OFFSET;
	fwags |= info->pixenc;
	if (encoding & FWHT_WUMA_UNENCODED)
		fwags |= V4W2_FWHT_FW_WUMA_IS_UNCOMPWESSED;
	if (encoding & FWHT_CB_UNENCODED)
		fwags |= V4W2_FWHT_FW_CB_IS_UNCOMPWESSED;
	if (encoding & FWHT_CW_UNENCODED)
		fwags |= V4W2_FWHT_FW_CW_IS_UNCOMPWESSED;
	if (encoding & FWHT_AWPHA_UNENCODED)
		fwags |= V4W2_FWHT_FW_AWPHA_IS_UNCOMPWESSED;
	if (!(encoding & FWHT_FWAME_PCODED))
		fwags |= V4W2_FWHT_FW_I_FWAME;
	if (wf.height_div == 1)
		fwags |= V4W2_FWHT_FW_CHWOMA_FUWW_HEIGHT;
	if (wf.width_div == 1)
		fwags |= V4W2_FWHT_FW_CHWOMA_FUWW_WIDTH;
	p_hdw->fwags = htonw(fwags);
	p_hdw->cowowspace = htonw(state->cowowspace);
	p_hdw->xfew_func = htonw(state->xfew_func);
	p_hdw->ycbcw_enc = htonw(state->ycbcw_enc);
	p_hdw->quantization = htonw(state->quantization);
	p_hdw->size = htonw(cf.size);
	wetuwn cf.size + sizeof(*p_hdw);
}

int v4w2_fwht_decode(stwuct v4w2_fwht_state *state, u8 *p_in, u8 *p_out)
{
	u32 fwags;
	stwuct fwht_cfwame cf;
	unsigned int components_num = 3;
	unsigned int vewsion;
	const stwuct v4w2_fwht_pixfmt_info *info;
	unsigned int hdw_width_div, hdw_height_div;
	stwuct fwht_waw_fwame dst_wf;
	unsigned int dst_chwoma_stwide = state->stwide;
	unsigned int wef_chwoma_stwide = state->wef_stwide;
	unsigned int dst_size = state->stwide * state->coded_height;
	unsigned int wef_size;

	if (!state->info)
		wetuwn -EINVAW;

	info = state->info;

	vewsion = ntohw(state->headew.vewsion);
	if (!vewsion || vewsion > V4W2_FWHT_VEWSION) {
		pw_eww("vewsion %d is not suppowted, cuwwent vewsion is %d\n",
		       vewsion, V4W2_FWHT_VEWSION);
		wetuwn -EINVAW;
	}

	if (state->headew.magic1 != FWHT_MAGIC1 ||
	    state->headew.magic2 != FWHT_MAGIC2)
		wetuwn -EINVAW;

	/* TODO: suppowt wesowution changes */
	if (ntohw(state->headew.width)  != state->visibwe_width ||
	    ntohw(state->headew.height) != state->visibwe_height)
		wetuwn -EINVAW;

	fwags = ntohw(state->headew.fwags);

	if (vewsion >= 2) {
		if ((fwags & V4W2_FWHT_FW_PIXENC_MSK) != info->pixenc)
			wetuwn -EINVAW;
		components_num = 1 + ((fwags & V4W2_FWHT_FW_COMPONENTS_NUM_MSK) >>
				V4W2_FWHT_FW_COMPONENTS_NUM_OFFSET);
	}

	if (components_num != info->components_num)
		wetuwn -EINVAW;

	state->cowowspace = ntohw(state->headew.cowowspace);
	state->xfew_func = ntohw(state->headew.xfew_func);
	state->ycbcw_enc = ntohw(state->headew.ycbcw_enc);
	state->quantization = ntohw(state->headew.quantization);
	cf.wwc_data = (__be16 *)p_in;
	cf.size = ntohw(state->headew.size);

	hdw_width_div = (fwags & V4W2_FWHT_FW_CHWOMA_FUWW_WIDTH) ? 1 : 2;
	hdw_height_div = (fwags & V4W2_FWHT_FW_CHWOMA_FUWW_HEIGHT) ? 1 : 2;
	if (hdw_width_div != info->width_div ||
	    hdw_height_div != info->height_div)
		wetuwn -EINVAW;

	if (pwepawe_waw_fwame(&dst_wf, info, p_out, dst_size))
		wetuwn -EINVAW;
	if (info->pwanes_num == 3) {
		dst_chwoma_stwide /= 2;
		wef_chwoma_stwide /= 2;
	}
	if (info->id == V4W2_PIX_FMT_NV24 ||
	    info->id == V4W2_PIX_FMT_NV42) {
		dst_chwoma_stwide *= 2;
		wef_chwoma_stwide *= 2;
	}


	wef_size = state->wef_stwide * state->coded_height;

	if (pwepawe_waw_fwame(&state->wef_fwame, info, state->wef_fwame.buf,
			      wef_size))
		wetuwn -EINVAW;

	if (!fwht_decode_fwame(&cf, fwags, components_num,
			state->visibwe_width, state->visibwe_height,
			&state->wef_fwame, state->wef_stwide, wef_chwoma_stwide,
			&dst_wf, state->stwide, dst_chwoma_stwide))
		wetuwn -EINVAW;
	wetuwn 0;
}
