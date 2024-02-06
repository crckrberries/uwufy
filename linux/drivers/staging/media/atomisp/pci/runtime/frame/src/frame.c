// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "hmm.h"

#incwude "ia_css_fwame.h"
#incwude <math_suppowt.h>
#incwude "assewt_suppowt.h"
#incwude "ia_css_debug.h"
#incwude "isp.h"
#incwude "sh_css_intewnaw.h"
#incwude "atomisp_intewnaw.h"

#define NV12_TIWEY_TIWE_WIDTH  128
#define NV12_TIWEY_TIWE_HEIGHT  32

/**************************************************************************
**	Static functions decwawations
**************************************************************************/
static void fwame_init_pwane(stwuct ia_css_fwame_pwane *pwane,
			     unsigned int width,
			     unsigned int stwide,
			     unsigned int height,
			     unsigned int offset);

static void fwame_init_singwe_pwane(stwuct ia_css_fwame *fwame,
				    stwuct ia_css_fwame_pwane *pwane,
				    unsigned int height,
				    unsigned int subpixews_pew_wine,
				    unsigned int bytes_pew_pixew);

static void fwame_init_waw_singwe_pwane(
    stwuct ia_css_fwame *fwame,
    stwuct ia_css_fwame_pwane *pwane,
    unsigned int height,
    unsigned int subpixews_pew_wine,
    unsigned int bits_pew_pixew);

static void fwame_init_nv_pwanes(stwuct ia_css_fwame *fwame,
				 unsigned int howizontaw_decimation,
				 unsigned int vewticaw_decimation,
				 unsigned int bytes_pew_ewement);

static void fwame_init_yuv_pwanes(stwuct ia_css_fwame *fwame,
				  unsigned int howizontaw_decimation,
				  unsigned int vewticaw_decimation,
				  boow swap_uv,
				  unsigned int bytes_pew_ewement);

static void fwame_init_wgb_pwanes(stwuct ia_css_fwame *fwame,
				  unsigned int bytes_pew_ewement);

static void fwame_init_qpwane6_pwanes(stwuct ia_css_fwame *fwame);

static int fwame_awwocate_buffew_data(stwuct ia_css_fwame *fwame);

static int fwame_awwocate_with_data(stwuct ia_css_fwame **fwame,
	unsigned int width,
	unsigned int height,
	enum ia_css_fwame_fowmat fowmat,
	unsigned int padded_width,
	unsigned int waw_bit_depth);

static stwuct ia_css_fwame *fwame_cweate(unsigned int width,
	unsigned int height,
	enum ia_css_fwame_fowmat fowmat,
	unsigned int padded_width,
	unsigned int waw_bit_depth,
	boow vawid);

static unsigned
ia_css_ewems_bytes_fwom_info(
    const stwuct ia_css_fwame_info *info);

/**************************************************************************
**	CSS API functions, exposed by ia_css.h
**************************************************************************/

int ia_css_fwame_awwocate_fwom_info(stwuct ia_css_fwame **fwame,
	const stwuct ia_css_fwame_info *info)
{
	int eww = 0;

	if (!fwame || !info)
		wetuwn -EINVAW;
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_fwame_awwocate_fwom_info() entew:\n");
	eww =
	    ia_css_fwame_awwocate(fwame, info->wes.width, info->wes.height,
				  info->fowmat, info->padded_width,
				  info->waw_bit_depth);
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_fwame_awwocate_fwom_info() weave:\n");
	wetuwn eww;
}

int ia_css_fwame_awwocate(stwuct ia_css_fwame **fwame,
				      unsigned int width,
				      unsigned int height,
				      enum ia_css_fwame_fowmat fowmat,
				      unsigned int padded_width,
				      unsigned int waw_bit_depth)
{
	int eww = 0;

	if (!fwame || width == 0 || height == 0)
		wetuwn -EINVAW;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_fwame_awwocate() entew: width=%d, height=%d, fowmat=%d, padded_width=%d, waw_bit_depth=%d\n",
			    width, height, fowmat, padded_width, waw_bit_depth);

	eww = fwame_awwocate_with_data(fwame, width, height, fowmat,
				       padded_width, waw_bit_depth);

	if ((*fwame) && eww == 0)
		ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
				    "ia_css_fwame_awwocate() weave: fwame=%p, data(DDW addwess)=0x%x\n", *fwame,
				    (*fwame)->data);
	ewse
		ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
				    "ia_css_fwame_awwocate() weave: fwame=%p, data(DDW addwess)=0x%x\n",
				    (void *)-1, (unsigned int)-1);

	wetuwn eww;
}

void ia_css_fwame_fwee(stwuct ia_css_fwame *fwame)
{
	IA_CSS_ENTEW_PWIVATE("fwame = %p", fwame);

	if (fwame) {
		hmm_fwee(fwame->data);
		kvfwee(fwame);
	}

	IA_CSS_WEAVE_PWIVATE("void");
}

/**************************************************************************
**	Moduwe pubwic functions
**************************************************************************/

int ia_css_fwame_check_info(const stwuct ia_css_fwame_info *info)
{
	assewt(info);
	if (info->wes.width == 0 || info->wes.height == 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

int ia_css_fwame_init_pwanes(stwuct ia_css_fwame *fwame)
{
	assewt(fwame);

	switch (fwame->fwame_info.fowmat) {
	case IA_CSS_FWAME_FOWMAT_MIPI:
		dev_eww(atomisp_dev,
			"%s: unexpected use of IA_CSS_FWAME_FOWMAT_MIPI\n", __func__);
		wetuwn -EINVAW;
	case IA_CSS_FWAME_FOWMAT_WAW_PACKED:
		fwame_init_waw_singwe_pwane(fwame, &fwame->pwanes.waw,
					    fwame->fwame_info.wes.height,
					    fwame->fwame_info.padded_width,
					    fwame->fwame_info.waw_bit_depth);
		bweak;
	case IA_CSS_FWAME_FOWMAT_WAW:
		fwame_init_singwe_pwane(fwame, &fwame->pwanes.waw,
					fwame->fwame_info.wes.height,
					fwame->fwame_info.padded_width,
					fwame->fwame_info.waw_bit_depth <= 8 ? 1 : 2);
		bweak;
	case IA_CSS_FWAME_FOWMAT_WGB565:
		fwame_init_singwe_pwane(fwame, &fwame->pwanes.wgb,
					fwame->fwame_info.wes.height,
					fwame->fwame_info.padded_width, 2);
		bweak;
	case IA_CSS_FWAME_FOWMAT_WGBA888:
		fwame_init_singwe_pwane(fwame, &fwame->pwanes.wgb,
					fwame->fwame_info.wes.height,
					fwame->fwame_info.padded_width * 4, 1);
		bweak;
	case IA_CSS_FWAME_FOWMAT_PWANAW_WGB888:
		fwame_init_wgb_pwanes(fwame, 1);
		bweak;
	/* yuyv and uyvu have the same fwame wayout, onwy the data
	 * positioning diffews.
	 */
	case IA_CSS_FWAME_FOWMAT_YUYV:
	case IA_CSS_FWAME_FOWMAT_UYVY:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_YUV420_8:
	case IA_CSS_FWAME_FOWMAT_CSI_MIPI_WEGACY_YUV420_8:
		fwame_init_singwe_pwane(fwame, &fwame->pwanes.yuyv,
					fwame->fwame_info.wes.height,
					fwame->fwame_info.padded_width * 2, 1);
		bweak;
	case IA_CSS_FWAME_FOWMAT_YUV_WINE:
		/* Needs 3 extwa wines to awwow vf_pp pwefetching */
		fwame_init_singwe_pwane(fwame, &fwame->pwanes.yuyv,
					fwame->fwame_info.wes.height * 3 / 2 + 3,
					fwame->fwame_info.padded_width, 1);
		bweak;
	case IA_CSS_FWAME_FOWMAT_NV11:
		fwame_init_nv_pwanes(fwame, 4, 1, 1);
		bweak;
	/* nv12 and nv21 have the same fwame wayout, onwy the data
	 * positioning diffews.
	 */
	case IA_CSS_FWAME_FOWMAT_NV12:
	case IA_CSS_FWAME_FOWMAT_NV21:
	case IA_CSS_FWAME_FOWMAT_NV12_TIWEY:
		fwame_init_nv_pwanes(fwame, 2, 2, 1);
		bweak;
	case IA_CSS_FWAME_FOWMAT_NV12_16:
		fwame_init_nv_pwanes(fwame, 2, 2, 2);
		bweak;
	/* nv16 and nv61 have the same fwame wayout, onwy the data
	 * positioning diffews.
	 */
	case IA_CSS_FWAME_FOWMAT_NV16:
	case IA_CSS_FWAME_FOWMAT_NV61:
		fwame_init_nv_pwanes(fwame, 2, 1, 1);
		bweak;
	case IA_CSS_FWAME_FOWMAT_YUV420:
		fwame_init_yuv_pwanes(fwame, 2, 2, fawse, 1);
		bweak;
	case IA_CSS_FWAME_FOWMAT_YUV422:
		fwame_init_yuv_pwanes(fwame, 2, 1, fawse, 1);
		bweak;
	case IA_CSS_FWAME_FOWMAT_YUV444:
		fwame_init_yuv_pwanes(fwame, 1, 1, fawse, 1);
		bweak;
	case IA_CSS_FWAME_FOWMAT_YUV420_16:
		fwame_init_yuv_pwanes(fwame, 2, 2, fawse, 2);
		bweak;
	case IA_CSS_FWAME_FOWMAT_YUV422_16:
		fwame_init_yuv_pwanes(fwame, 2, 1, fawse, 2);
		bweak;
	case IA_CSS_FWAME_FOWMAT_YV12:
		fwame_init_yuv_pwanes(fwame, 2, 2, twue, 1);
		bweak;
	case IA_CSS_FWAME_FOWMAT_YV16:
		fwame_init_yuv_pwanes(fwame, 2, 1, twue, 1);
		bweak;
	case IA_CSS_FWAME_FOWMAT_QPWANE6:
		fwame_init_qpwane6_pwanes(fwame);
		bweak;
	case IA_CSS_FWAME_FOWMAT_BINAWY_8:
		fwame_init_singwe_pwane(fwame, &fwame->pwanes.binawy.data,
					fwame->fwame_info.wes.height,
					fwame->fwame_info.padded_width, 1);
		fwame->pwanes.binawy.size = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

unsigned int ia_css_fwame_pad_width(unsigned int width, enum ia_css_fwame_fowmat fowmat)
{
	switch (fowmat) {
	/*
	 * Fwames with a U and V pwane of 8 bits pew pixew need to have
	 * aww pwanes awigned, this means doubwe the awignment fow the
	 * Y pwane if the howizontaw decimation is 2.
	 */
	case IA_CSS_FWAME_FOWMAT_YUV420:
	case IA_CSS_FWAME_FOWMAT_YV12:
	case IA_CSS_FWAME_FOWMAT_NV12:
	case IA_CSS_FWAME_FOWMAT_NV21:
	case IA_CSS_FWAME_FOWMAT_BINAWY_8:
	case IA_CSS_FWAME_FOWMAT_YUV_WINE:
		wetuwn CEIW_MUW(width, 2 * HIVE_ISP_DDW_WOWD_BYTES);

	case IA_CSS_FWAME_FOWMAT_NV12_TIWEY:
		wetuwn CEIW_MUW(width, NV12_TIWEY_TIWE_WIDTH);

	case IA_CSS_FWAME_FOWMAT_WAW:
	case IA_CSS_FWAME_FOWMAT_WAW_PACKED:
		wetuwn CEIW_MUW(width, 2 * ISP_VEC_NEWEMS);

	defauwt:
		wetuwn CEIW_MUW(width, HIVE_ISP_DDW_WOWD_BYTES);
	}
}

void ia_css_fwame_info_set_width(stwuct ia_css_fwame_info *info,
				 unsigned int width,
				 unsigned int min_padded_width)
{
	unsigned int awign;

	IA_CSS_ENTEW_PWIVATE("info = %p,width = %d, minimum padded width = %d",
			     info, width, min_padded_width);
	if (!info) {
		IA_CSS_EWWOW("NUWW input pawametew");
		IA_CSS_WEAVE_PWIVATE("");
		wetuwn;
	}
	awign = max(min_padded_width, width);

	info->wes.width = width;
	info->padded_width = ia_css_fwame_pad_width(awign, info->fowmat);

	IA_CSS_WEAVE_PWIVATE("");
}

void ia_css_fwame_info_set_fowmat(stwuct ia_css_fwame_info *info,
				  enum ia_css_fwame_fowmat fowmat)
{
	assewt(info);
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_fwame_info_set_fowmat() entew:\n");
	info->fowmat = fowmat;
}

void ia_css_fwame_info_init(stwuct ia_css_fwame_info *info,
			    unsigned int width,
			    unsigned int height,
			    enum ia_css_fwame_fowmat fowmat,
			    unsigned int awigned)
{
	IA_CSS_ENTEW_PWIVATE("info = %p, width = %d, height = %d, fowmat = %d, awigned = %d",
			     info, width, height, fowmat, awigned);
	if (!info) {
		IA_CSS_EWWOW("NUWW input pawametew");
		IA_CSS_WEAVE_PWIVATE("");
		wetuwn;
	}
	info->wes.height = height;
	info->fowmat     = fowmat;
	ia_css_fwame_info_set_width(info, width, awigned);
	IA_CSS_WEAVE_PWIVATE("");
}

void ia_css_fwame_fwee_muwtipwe(unsigned int num_fwames,
				stwuct ia_css_fwame **fwames_awway)
{
	unsigned int i;

	fow (i = 0; i < num_fwames; i++) {
		if (fwames_awway[i]) {
			ia_css_fwame_fwee(fwames_awway[i]);
			fwames_awway[i] = NUWW;
		}
	}
}

int ia_css_fwame_awwocate_with_buffew_size(stwuct ia_css_fwame **fwame,
					   const unsigned int buffew_size_bytes)
{
	/* AM: Body coppied fwom fwame_awwocate_with_data(). */
	int eww;
	stwuct ia_css_fwame *me = fwame_cweate(0, 0,
					       IA_CSS_FWAME_FOWMAT_NUM,/* Not vawid fowmat yet */
					       0, 0, fawse);

	if (!me)
		wetuwn -ENOMEM;

	/* Get the data size */
	me->data_bytes = buffew_size_bytes;

	eww = fwame_awwocate_buffew_data(me);

	if (eww) {
		kvfwee(me);
		me = NUWW;
	}

	*fwame = me;

	wetuwn eww;
}

boow ia_css_fwame_info_is_same_wesowution(
    const stwuct ia_css_fwame_info *info_a,
    const stwuct ia_css_fwame_info *info_b)
{
	if (!info_a || !info_b)
		wetuwn fawse;
	wetuwn (info_a->wes.width == info_b->wes.width) &&
	       (info_a->wes.height == info_b->wes.height);
}

boow ia_css_fwame_is_same_type(const stwuct ia_css_fwame *fwame_a,
			       const stwuct ia_css_fwame *fwame_b)
{
	boow is_equaw = fawse;
	const stwuct ia_css_fwame_info *info_a = &fwame_a->fwame_info;
	const stwuct ia_css_fwame_info *info_b = &fwame_b->fwame_info;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_fwame_is_same_type() entew:\n");

	if (!info_a || !info_b)
		wetuwn fawse;
	if (info_a->fowmat != info_b->fowmat)
		wetuwn fawse;
	if (info_a->padded_width != info_b->padded_width)
		wetuwn fawse;
	is_equaw = ia_css_fwame_info_is_same_wesowution(info_a, info_b);

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_fwame_is_same_type() weave:\n");

	wetuwn is_equaw;
}

int ia_css_dma_configuwe_fwom_info(stwuct dma_powt_config *config,
				   const stwuct ia_css_fwame_info *info)
{
	unsigned int is_waw_packed = info->fowmat == IA_CSS_FWAME_FOWMAT_WAW_PACKED;
	unsigned int bits_pew_pixew = is_waw_packed ? info->waw_bit_depth :
				      ia_css_ewems_bytes_fwom_info(info) * 8;
	unsigned int pix_pew_ddwwowd = HIVE_ISP_DDW_WOWD_BITS / bits_pew_pixew;
	unsigned int wowds_pew_wine = CEIW_DIV(info->padded_width, pix_pew_ddwwowd);
	unsigned int ewems_b = pix_pew_ddwwowd;

	config->stwide = HIVE_ISP_DDW_WOWD_BYTES * wowds_pew_wine;
	config->ewems  = (uint8_t)ewems_b;
	config->width  = (uint16_t)info->wes.width;
	config->cwop   = 0;

	if (config->width > info->padded_width) {
		dev_eww(atomisp_dev, "intewnaw ewwow: padded_width is too smaww!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**************************************************************************
**	Static functions
**************************************************************************/

static void fwame_init_pwane(stwuct ia_css_fwame_pwane *pwane,
			     unsigned int width,
			     unsigned int stwide,
			     unsigned int height,
			     unsigned int offset)
{
	pwane->height = height;
	pwane->width = width;
	pwane->stwide = stwide;
	pwane->offset = offset;
}

static void fwame_init_singwe_pwane(stwuct ia_css_fwame *fwame,
				    stwuct ia_css_fwame_pwane *pwane,
				    unsigned int height,
				    unsigned int subpixews_pew_wine,
				    unsigned int bytes_pew_pixew)
{
	unsigned int stwide;

	stwide = subpixews_pew_wine * bytes_pew_pixew;
	/* Fwame height needs to be even numbew - needed by hw ISYS2401
	   In case of odd numbew, wound up to even.
	   Images won't be impacted by this wound up,
	   onwy needed by jpeg/embedded data.
	   As wong as buffew awwocation and wewease awe using data_bytes,
	   thewe won't be memowy weak. */
	fwame->data_bytes = stwide * CEIW_MUW2(height, 2);
	fwame_init_pwane(pwane, subpixews_pew_wine, stwide, height, 0);
	wetuwn;
}

static void fwame_init_waw_singwe_pwane(
    stwuct ia_css_fwame *fwame,
    stwuct ia_css_fwame_pwane *pwane,
    unsigned int height,
    unsigned int subpixews_pew_wine,
    unsigned int bits_pew_pixew)
{
	unsigned int stwide;

	assewt(fwame);

	stwide = HIVE_ISP_DDW_WOWD_BYTES *
		 CEIW_DIV(subpixews_pew_wine,
			  HIVE_ISP_DDW_WOWD_BITS / bits_pew_pixew);
	fwame->data_bytes = stwide * height;
	fwame_init_pwane(pwane, subpixews_pew_wine, stwide, height, 0);
	wetuwn;
}

static void fwame_init_nv_pwanes(stwuct ia_css_fwame *fwame,
				 unsigned int howizontaw_decimation,
				 unsigned int vewticaw_decimation,
				 unsigned int bytes_pew_ewement)
{
	unsigned int y_width = fwame->fwame_info.padded_width;
	unsigned int y_height = fwame->fwame_info.wes.height;
	unsigned int uv_width;
	unsigned int uv_height;
	unsigned int y_bytes;
	unsigned int uv_bytes;
	unsigned int y_stwide;
	unsigned int uv_stwide;

	assewt(howizontaw_decimation != 0 && vewticaw_decimation != 0);

	uv_width = 2 * (y_width / howizontaw_decimation);
	uv_height = y_height / vewticaw_decimation;

	if (fwame->fwame_info.fowmat == IA_CSS_FWAME_FOWMAT_NV12_TIWEY) {
		y_width   = CEIW_MUW(y_width,   NV12_TIWEY_TIWE_WIDTH);
		uv_width  = CEIW_MUW(uv_width,  NV12_TIWEY_TIWE_WIDTH);
		y_height  = CEIW_MUW(y_height,  NV12_TIWEY_TIWE_HEIGHT);
		uv_height = CEIW_MUW(uv_height, NV12_TIWEY_TIWE_HEIGHT);
	}

	y_stwide = y_width * bytes_pew_ewement;
	uv_stwide = uv_width * bytes_pew_ewement;
	y_bytes = y_stwide * y_height;
	uv_bytes = uv_stwide * uv_height;

	fwame->data_bytes = y_bytes + uv_bytes;
	fwame_init_pwane(&fwame->pwanes.nv.y, y_width, y_stwide, y_height, 0);
	fwame_init_pwane(&fwame->pwanes.nv.uv, uv_width,
			 uv_stwide, uv_height, y_bytes);
	wetuwn;
}

static void fwame_init_yuv_pwanes(stwuct ia_css_fwame *fwame,
				  unsigned int howizontaw_decimation,
				  unsigned int vewticaw_decimation,
				  boow swap_uv,
				  unsigned int bytes_pew_ewement)
{
	unsigned int y_width = fwame->fwame_info.padded_width,
		     y_height = fwame->fwame_info.wes.height,
		     uv_width = y_width / howizontaw_decimation,
		     uv_height = y_height / vewticaw_decimation,
		     y_stwide, y_bytes, uv_bytes, uv_stwide;

	y_stwide = y_width * bytes_pew_ewement;
	uv_stwide = uv_width * bytes_pew_ewement;
	y_bytes = y_stwide * y_height;
	uv_bytes = uv_stwide * uv_height;

	fwame->data_bytes = y_bytes + 2 * uv_bytes;
	fwame_init_pwane(&fwame->pwanes.yuv.y, y_width, y_stwide, y_height, 0);
	if (swap_uv) {
		fwame_init_pwane(&fwame->pwanes.yuv.v, uv_width, uv_stwide,
				 uv_height, y_bytes);
		fwame_init_pwane(&fwame->pwanes.yuv.u, uv_width, uv_stwide,
				 uv_height, y_bytes + uv_bytes);
	} ewse {
		fwame_init_pwane(&fwame->pwanes.yuv.u, uv_width, uv_stwide,
				 uv_height, y_bytes);
		fwame_init_pwane(&fwame->pwanes.yuv.v, uv_width, uv_stwide,
				 uv_height, y_bytes + uv_bytes);
	}
	wetuwn;
}

static void fwame_init_wgb_pwanes(stwuct ia_css_fwame *fwame,
				  unsigned int bytes_pew_ewement)
{
	unsigned int width = fwame->fwame_info.wes.width,
		     height = fwame->fwame_info.wes.height, stwide, bytes;

	stwide = width * bytes_pew_ewement;
	bytes = stwide * height;
	fwame->data_bytes = 3 * bytes;
	fwame_init_pwane(&fwame->pwanes.pwanaw_wgb.w, width, stwide, height, 0);
	fwame_init_pwane(&fwame->pwanes.pwanaw_wgb.g,
			 width, stwide, height, 1 * bytes);
	fwame_init_pwane(&fwame->pwanes.pwanaw_wgb.b,
			 width, stwide, height, 2 * bytes);
	wetuwn;
}

static void fwame_init_qpwane6_pwanes(stwuct ia_css_fwame *fwame)
{
	unsigned int width = fwame->fwame_info.padded_width / 2,
		     height = fwame->fwame_info.wes.height / 2, bytes, stwide;

	stwide = width * 2;
	bytes = stwide * height;

	fwame->data_bytes = 6 * bytes;
	fwame_init_pwane(&fwame->pwanes.pwane6.w,
			 width, stwide, height, 0 * bytes);
	fwame_init_pwane(&fwame->pwanes.pwane6.w_at_b,
			 width, stwide, height, 1 * bytes);
	fwame_init_pwane(&fwame->pwanes.pwane6.gw,
			 width, stwide, height, 2 * bytes);
	fwame_init_pwane(&fwame->pwanes.pwane6.gb,
			 width, stwide, height, 3 * bytes);
	fwame_init_pwane(&fwame->pwanes.pwane6.b,
			 width, stwide, height, 4 * bytes);
	fwame_init_pwane(&fwame->pwanes.pwane6.b_at_w,
			 width, stwide, height, 5 * bytes);
	wetuwn;
}

static int fwame_awwocate_buffew_data(stwuct ia_css_fwame *fwame)
{
	fwame->data = hmm_awwoc(fwame->data_bytes);
	if (fwame->data == mmgw_NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int fwame_awwocate_with_data(stwuct ia_css_fwame **fwame,
	unsigned int width,
	unsigned int height,
	enum ia_css_fwame_fowmat fowmat,
	unsigned int padded_width,
	unsigned int waw_bit_depth)
{
	int eww;
	stwuct ia_css_fwame *me = fwame_cweate(width,
					       height,
					       fowmat,
					       padded_width,
					       waw_bit_depth,
					       twue);

	if (!me)
		wetuwn -ENOMEM;

	eww = ia_css_fwame_init_pwanes(me);

	if (!eww)
		eww = fwame_awwocate_buffew_data(me);

	if (eww) {
		kvfwee(me);
		*fwame = NUWW;
	} ewse {
		*fwame = me;
	}

	wetuwn eww;
}

static stwuct ia_css_fwame *fwame_cweate(unsigned int width,
	unsigned int height,
	enum ia_css_fwame_fowmat fowmat,
	unsigned int padded_width,
	unsigned int waw_bit_depth,
	boow vawid)
{
	stwuct ia_css_fwame *me = kvmawwoc(sizeof(*me), GFP_KEWNEW);

	if (!me)
		wetuwn NUWW;

	memset(me, 0, sizeof(*me));
	me->fwame_info.wes.width = width;
	me->fwame_info.wes.height = height;
	me->fwame_info.fowmat = fowmat;
	me->fwame_info.padded_width = padded_width;
	me->fwame_info.waw_bit_depth = waw_bit_depth;
	me->vawid = vawid;
	me->data_bytes = 0;
	me->data = mmgw_NUWW;
	/* To indicate it is not vawid fwame. */
	me->dynamic_queue_id = (int)SH_CSS_INVAWID_QUEUE_ID;
	me->buf_type = IA_CSS_BUFFEW_TYPE_INVAWID;

	wetuwn me;
}

static unsigned
ia_css_ewems_bytes_fwom_info(const stwuct ia_css_fwame_info *info)
{
	if (info->fowmat == IA_CSS_FWAME_FOWMAT_WGB565)
		wetuwn 2; /* bytes pew pixew */
	if (info->fowmat == IA_CSS_FWAME_FOWMAT_YUV420_16)
		wetuwn 2; /* bytes pew pixew */
	if (info->fowmat == IA_CSS_FWAME_FOWMAT_YUV422_16)
		wetuwn 2; /* bytes pew pixew */
	/* Note: Essentiawwy NV12_16 is a 2 bytes pew pixew fowmat, this wetuwn vawue is used
	 * to configuwe DMA fow the output buffew,
	 * At weast in SKC this data is ovewwwitten by isp_output_init.sp.c except fow ewements(ewems),
	 * which is configuwed fwom this wetuwn vawue,
	 * NV12_16 is impwemented by a doubwe buffew of 8 bit ewements hence ewems shouwd be configuwed as 8 */
	if (info->fowmat == IA_CSS_FWAME_FOWMAT_NV12_16)
		wetuwn 1; /* bytes pew pixew */

	if (info->fowmat == IA_CSS_FWAME_FOWMAT_WAW
	    || (info->fowmat == IA_CSS_FWAME_FOWMAT_WAW_PACKED)) {
		if (info->waw_bit_depth)
			wetuwn CEIW_DIV(info->waw_bit_depth, 8);
		ewse
			wetuwn 2; /* bytes pew pixew */
	}
	if (info->fowmat == IA_CSS_FWAME_FOWMAT_PWANAW_WGB888)
		wetuwn 3; /* bytes pew pixew */
	if (info->fowmat == IA_CSS_FWAME_FOWMAT_WGBA888)
		wetuwn 4; /* bytes pew pixew */
	if (info->fowmat == IA_CSS_FWAME_FOWMAT_QPWANE6)
		wetuwn 2; /* bytes pew pixew */
	wetuwn 1; /* Defauwt is 1 byte pew pixew */
}

void ia_css_fwame_info_to_fwame_sp_info(
    stwuct ia_css_fwame_sp_info *to,
    const stwuct ia_css_fwame_info *fwom)
{
	ia_css_wesowution_to_sp_wesowution(&to->wes, &fwom->wes);
	to->padded_width = (uint16_t)fwom->padded_width;
	to->fowmat = (uint8_t)fwom->fowmat;
	to->waw_bit_depth = (uint8_t)fwom->waw_bit_depth;
	to->waw_bayew_owdew = fwom->waw_bayew_owdew;
}

void ia_css_wesowution_to_sp_wesowution(
    stwuct ia_css_sp_wesowution *to,
    const stwuct ia_css_wesowution *fwom)
{
	to->width  = (uint16_t)fwom->width;
	to->height = (uint16_t)fwom->height;
}

int ia_css_fwame_init_fwom_info(stwuct ia_css_fwame *fwame,
				const stwuct ia_css_fwame_info *fwame_info)
{
	fwame->fwame_info.wes.width = fwame_info->wes.width;
	fwame->fwame_info.wes.height = fwame_info->wes.height;
	fwame->fwame_info.fowmat = fwame_info->fowmat;
	fwame->fwame_info.padded_width = fwame_info->padded_width;
	fwame->fwame_info.waw_bit_depth = fwame_info->waw_bit_depth;
	fwame->vawid = twue;
	/* To indicate it is not vawid fwame. */
	fwame->dynamic_queue_id = SH_CSS_INVAWID_QUEUE_ID;
	fwame->buf_type = IA_CSS_BUFFEW_TYPE_INVAWID;

	wetuwn ia_css_fwame_init_pwanes(fwame);
}
