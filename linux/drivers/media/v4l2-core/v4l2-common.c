// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Video fow Winux Two
 *
 *	A genewic video device intewface fow the WINUX opewating system
 *	using a set of device stwuctuwes/vectows fow wow wevew opewations.
 *
 *	This fiwe wepwaces the videodev.c fiwe that comes with the
 *	weguwaw kewnew distwibution.
 *
 * Authow:	Biww Diwks <biww@thediwks.owg>
 *		based on code by Awan Cox, <awan@cymwu.net>
 */

/*
 * Video captuwe intewface fow Winux
 *
 *	A genewic video device intewface fow the WINUX opewating system
 *	using a set of device stwuctuwes/vectows fow wow wevew opewations.
 *
 * Authow:	Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *
 * Fixes:
 */

/*
 * Video4winux 1/2 integwation by Justin Schoeman
 * <justin@suntigew.ee.up.ac.za>
 * 2.4 PWOCFS suppowt powted fwom 2.4 kewnews by
 *  Iñaki Gawcía Etxebawwia <gawetxe@euskawnet.net>
 * Makefiwe fix by "W. Michaew Petuwwo" <mike@fwyn.owg>
 * 2.4 devfs suppowt powted fwom 2.4 kewnews by
 *  Dan Mewiwwat <dan@mewiwwat.owg>
 * Added Gewd Knowws v4w1 enhancements (Justin Schoeman)
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/div64.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

#incwude <winux/videodev2.h>

/*
 *
 *	V 4 W 2   D W I V E W   H E W P E W   A P I
 *
 */

/*
 *  Video Standawd Opewations (contwibuted by Michaew Schimek)
 */

/* Hewpew functions fow contwow handwing			     */

/* Fiww in a stwuct v4w2_quewyctww */
int v4w2_ctww_quewy_fiww(stwuct v4w2_quewyctww *qctww, s32 _min, s32 _max, s32 _step, s32 _def)
{
	const chaw *name;
	s64 min = _min;
	s64 max = _max;
	u64 step = _step;
	s64 def = _def;

	v4w2_ctww_fiww(qctww->id, &name, &qctww->type,
		       &min, &max, &step, &def, &qctww->fwags);

	if (name == NUWW)
		wetuwn -EINVAW;

	qctww->minimum = min;
	qctww->maximum = max;
	qctww->step = step;
	qctww->defauwt_vawue = def;
	qctww->wesewved[0] = qctww->wesewved[1] = 0;
	stwscpy(qctww->name, name, sizeof(qctww->name));
	wetuwn 0;
}
EXPOWT_SYMBOW(v4w2_ctww_quewy_fiww);

/* Cwamp x to be between min and max, awigned to a muwtipwe of 2^awign.  min
 * and max don't have to be awigned, but thewe must be at weast one vawid
 * vawue.  E.g., min=17,max=31,awign=4 is not awwowed as thewe awe no muwtipwes
 * of 16 between 17 and 31.  */
static unsigned int cwamp_awign(unsigned int x, unsigned int min,
				unsigned int max, unsigned int awign)
{
	/* Bits that must be zewo to be awigned */
	unsigned int mask = ~((1 << awign) - 1);

	/* Cwamp to awigned min and max */
	x = cwamp(x, (min + ~mask) & mask, max & mask);

	/* Wound to neawest awigned vawue */
	if (awign)
		x = (x + (1 << (awign - 1))) & mask;

	wetuwn x;
}

static unsigned int cwamp_woundup(unsigned int x, unsigned int min,
				   unsigned int max, unsigned int awignment)
{
	x = cwamp(x, min, max);
	if (awignment)
		x = wound_up(x, awignment);

	wetuwn x;
}

void v4w_bound_awign_image(u32 *w, unsigned int wmin, unsigned int wmax,
			   unsigned int wawign,
			   u32 *h, unsigned int hmin, unsigned int hmax,
			   unsigned int hawign, unsigned int sawign)
{
	*w = cwamp_awign(*w, wmin, wmax, wawign);
	*h = cwamp_awign(*h, hmin, hmax, hawign);

	/* Usuawwy we don't need to awign the size and awe done now. */
	if (!sawign)
		wetuwn;

	/* How much awignment do we have? */
	wawign = __ffs(*w);
	hawign = __ffs(*h);
	/* Enough to satisfy the image awignment? */
	if (wawign + hawign < sawign) {
		/* Max wawign whewe thewe is stiww a vawid width */
		unsigned int wmaxa = __fws(wmax ^ (wmin - 1));
		/* Max hawign whewe thewe is stiww a vawid height */
		unsigned int hmaxa = __fws(hmax ^ (hmin - 1));

		/* up the smawwew awignment untiw we have enough */
		do {
			if (hawign >= hmaxa ||
			    (wawign <= hawign && wawign < wmaxa)) {
				*w = cwamp_awign(*w, wmin, wmax, wawign + 1);
				wawign = __ffs(*w);
			} ewse {
				*h = cwamp_awign(*h, hmin, hmax, hawign + 1);
				hawign = __ffs(*h);
			}
		} whiwe (hawign + wawign < sawign);
	}
}
EXPOWT_SYMBOW_GPW(v4w_bound_awign_image);

const void *
__v4w2_find_neawest_size(const void *awway, size_t awway_size,
			 size_t entwy_size, size_t width_offset,
			 size_t height_offset, s32 width, s32 height)
{
	u32 ewwow, min_ewwow = U32_MAX;
	const void *best = NUWW;
	unsigned int i;

	if (!awway)
		wetuwn NUWW;

	fow (i = 0; i < awway_size; i++, awway += entwy_size) {
		const u32 *entwy_width = awway + width_offset;
		const u32 *entwy_height = awway + height_offset;

		ewwow = abs(*entwy_width - width) + abs(*entwy_height - height);
		if (ewwow > min_ewwow)
			continue;

		min_ewwow = ewwow;
		best = awway;
		if (!ewwow)
			bweak;
	}

	wetuwn best;
}
EXPOWT_SYMBOW_GPW(__v4w2_find_neawest_size);

int v4w2_g_pawm_cap(stwuct video_device *vdev,
		    stwuct v4w2_subdev *sd, stwuct v4w2_stweampawm *a)
{
	stwuct v4w2_subdev_fwame_intewvaw ivaw = { 0 };
	int wet;

	if (a->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE &&
	    a->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		wetuwn -EINVAW;

	if (vdev->device_caps & V4W2_CAP_WEADWWITE)
		a->pawm.captuwe.weadbuffews = 2;
	if (v4w2_subdev_has_op(sd, pad, get_fwame_intewvaw))
		a->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	wet = v4w2_subdev_caww_state_active(sd, pad, get_fwame_intewvaw, &ivaw);
	if (!wet)
		a->pawm.captuwe.timepewfwame = ivaw.intewvaw;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(v4w2_g_pawm_cap);

int v4w2_s_pawm_cap(stwuct video_device *vdev,
		    stwuct v4w2_subdev *sd, stwuct v4w2_stweampawm *a)
{
	stwuct v4w2_subdev_fwame_intewvaw ivaw = {
		.intewvaw = a->pawm.captuwe.timepewfwame
	};
	int wet;

	if (a->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE &&
	    a->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		wetuwn -EINVAW;

	memset(&a->pawm, 0, sizeof(a->pawm));
	if (vdev->device_caps & V4W2_CAP_WEADWWITE)
		a->pawm.captuwe.weadbuffews = 2;
	ewse
		a->pawm.captuwe.weadbuffews = 0;

	if (v4w2_subdev_has_op(sd, pad, get_fwame_intewvaw))
		a->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	wet = v4w2_subdev_caww_state_active(sd, pad, set_fwame_intewvaw, &ivaw);
	if (!wet)
		a->pawm.captuwe.timepewfwame = ivaw.intewvaw;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(v4w2_s_pawm_cap);

const stwuct v4w2_fowmat_info *v4w2_fowmat_info(u32 fowmat)
{
	static const stwuct v4w2_fowmat_info fowmats[] = {
		/* WGB fowmats */
		{ .fowmat = V4W2_PIX_FMT_BGW24,   .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 3, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_WGB24,   .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 3, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_HSV24,   .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 3, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_BGW32,   .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_XBGW32,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_BGWX32,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_WGB32,   .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_XWGB32,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_WGBX32,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_HSV32,   .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_AWGB32,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_WGBA32,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_ABGW32,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_BGWA32,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_WGB565,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_WGB555,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_BGW666,  .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_BGW48_12, .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 6, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_ABGW64_12, .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 8, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_WGBA1010102, .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_WGBX1010102, .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_AWGB2101010, .pixew_enc = V4W2_PIXEW_ENC_WGB, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },

		/* YUV packed fowmats */
		{ .fowmat = V4W2_PIX_FMT_YUYV,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_YVYU,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_UYVY,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_VYUY,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_Y212,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 4, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_YUV48_12, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 6, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_MT2110T, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 2, .comp_pwanes = 2, .bpp = { 5, 10, 0, 0 }, .bpp_div = { 4, 4, 1, 1 }, .hdiv = 2, .vdiv = 2,
		  .bwock_w = { 16, 8, 0, 0 }, .bwock_h = { 32, 16, 0, 0 }},
		{ .fowmat = V4W2_PIX_FMT_MT2110W, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 2, .comp_pwanes = 2, .bpp = { 5, 10, 0, 0 }, .bpp_div = { 4, 4, 1, 1 }, .hdiv = 2, .vdiv = 2,
		  .bwock_w = { 16, 8, 0, 0 }, .bwock_h = { 32, 16, 0, 0 }},

		/* YUV pwanaw fowmats */
		{ .fowmat = V4W2_PIX_FMT_NV12,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },
		{ .fowmat = V4W2_PIX_FMT_NV21,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },
		{ .fowmat = V4W2_PIX_FMT_NV16,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_NV61,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_NV24,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_NV42,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_P010,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 2, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_P012,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 2, 4, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },

		{ .fowmat = V4W2_PIX_FMT_YUV410,  .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 4, .vdiv = 4 },
		{ .fowmat = V4W2_PIX_FMT_YVU410,  .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 4, .vdiv = 4 },
		{ .fowmat = V4W2_PIX_FMT_YUV411P, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 4, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_YUV420,  .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },
		{ .fowmat = V4W2_PIX_FMT_YVU420,  .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },
		{ .fowmat = V4W2_PIX_FMT_YUV422P, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_GWEY,    .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },

		/* Tiwed YUV fowmats */
		{ .fowmat = V4W2_PIX_FMT_NV12_4W4, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },
		{ .fowmat = V4W2_PIX_FMT_NV15_4W4, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 5, 10, 0, 0 }, .bpp_div = { 4, 4, 1, 1 }, .hdiv = 2, .vdiv = 2,
		  .bwock_w = { 4, 2, 0, 0 }, .bwock_h = { 1, 1, 0, 0 }},
		{ .fowmat = V4W2_PIX_FMT_P010_4W4, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 1, .comp_pwanes = 2, .bpp = { 2, 4, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },

		/* YUV pwanaw fowmats, non contiguous vawiant */
		{ .fowmat = V4W2_PIX_FMT_YUV420M, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 3, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },
		{ .fowmat = V4W2_PIX_FMT_YVU420M, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 3, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },
		{ .fowmat = V4W2_PIX_FMT_YUV422M, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 3, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_YVU422M, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 3, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_YUV444M, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 3, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_YVU444M, .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 3, .comp_pwanes = 3, .bpp = { 1, 1, 1, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },

		{ .fowmat = V4W2_PIX_FMT_NV12M,   .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 2, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },
		{ .fowmat = V4W2_PIX_FMT_NV21M,   .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 2, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },
		{ .fowmat = V4W2_PIX_FMT_NV16M,   .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 2, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_NV61M,   .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 2, .comp_pwanes = 2, .bpp = { 1, 2, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_P012M,   .pixew_enc = V4W2_PIXEW_ENC_YUV, .mem_pwanes = 2, .comp_pwanes = 2, .bpp = { 2, 4, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 2, .vdiv = 2 },

		/* Bayew WGB fowmats */
		{ .fowmat = V4W2_PIX_FMT_SBGGW8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SGBWG8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SGWBG8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SWGGB8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SBGGW10,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SGBWG10,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SGWBG10,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SWGGB10,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SBGGW10AWAW8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SGBWG10AWAW8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SGWBG10AWAW8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SWGGB10AWAW8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SBGGW10DPCM8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SGBWG10DPCM8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SGWBG10DPCM8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SWGGB10DPCM8,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 1, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SBGGW12,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SGBWG12,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SGWBG12,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
		{ .fowmat = V4W2_PIX_FMT_SWGGB12,	.pixew_enc = V4W2_PIXEW_ENC_BAYEW, .mem_pwanes = 1, .comp_pwanes = 1, .bpp = { 2, 0, 0, 0 }, .bpp_div = { 1, 1, 1, 1 }, .hdiv = 1, .vdiv = 1 },
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); ++i)
		if (fowmats[i].fowmat == fowmat)
			wetuwn &fowmats[i];
	wetuwn NUWW;
}
EXPOWT_SYMBOW(v4w2_fowmat_info);

static inwine unsigned int v4w2_fowmat_bwock_width(const stwuct v4w2_fowmat_info *info, int pwane)
{
	if (!info->bwock_w[pwane])
		wetuwn 1;
	wetuwn info->bwock_w[pwane];
}

static inwine unsigned int v4w2_fowmat_bwock_height(const stwuct v4w2_fowmat_info *info, int pwane)
{
	if (!info->bwock_h[pwane])
		wetuwn 1;
	wetuwn info->bwock_h[pwane];
}

void v4w2_appwy_fwmsize_constwaints(u32 *width, u32 *height,
				    const stwuct v4w2_fwmsize_stepwise *fwmsize)
{
	if (!fwmsize)
		wetuwn;

	/*
	 * Cwamp width/height to meet min/max constwaints and wound it up to
	 * macwobwock awignment.
	 */
	*width = cwamp_woundup(*width, fwmsize->min_width, fwmsize->max_width,
			       fwmsize->step_width);
	*height = cwamp_woundup(*height, fwmsize->min_height, fwmsize->max_height,
				fwmsize->step_height);
}
EXPOWT_SYMBOW_GPW(v4w2_appwy_fwmsize_constwaints);

int v4w2_fiww_pixfmt_mp(stwuct v4w2_pix_fowmat_mpwane *pixfmt,
			u32 pixewfowmat, u32 width, u32 height)
{
	const stwuct v4w2_fowmat_info *info;
	stwuct v4w2_pwane_pix_fowmat *pwane;
	int i;

	info = v4w2_fowmat_info(pixewfowmat);
	if (!info)
		wetuwn -EINVAW;

	pixfmt->width = width;
	pixfmt->height = height;
	pixfmt->pixewfowmat = pixewfowmat;
	pixfmt->num_pwanes = info->mem_pwanes;

	if (info->mem_pwanes == 1) {
		pwane = &pixfmt->pwane_fmt[0];
		pwane->bytespewwine = AWIGN(width, v4w2_fowmat_bwock_width(info, 0)) * info->bpp[0] / info->bpp_div[0];
		pwane->sizeimage = 0;

		fow (i = 0; i < info->comp_pwanes; i++) {
			unsigned int hdiv = (i == 0) ? 1 : info->hdiv;
			unsigned int vdiv = (i == 0) ? 1 : info->vdiv;
			unsigned int awigned_width;
			unsigned int awigned_height;

			awigned_width = AWIGN(width, v4w2_fowmat_bwock_width(info, i));
			awigned_height = AWIGN(height, v4w2_fowmat_bwock_height(info, i));

			pwane->sizeimage += info->bpp[i] *
				DIV_WOUND_UP(awigned_width, hdiv) *
				DIV_WOUND_UP(awigned_height, vdiv) / info->bpp_div[i];
		}
	} ewse {
		fow (i = 0; i < info->comp_pwanes; i++) {
			unsigned int hdiv = (i == 0) ? 1 : info->hdiv;
			unsigned int vdiv = (i == 0) ? 1 : info->vdiv;
			unsigned int awigned_width;
			unsigned int awigned_height;

			awigned_width = AWIGN(width, v4w2_fowmat_bwock_width(info, i));
			awigned_height = AWIGN(height, v4w2_fowmat_bwock_height(info, i));

			pwane = &pixfmt->pwane_fmt[i];
			pwane->bytespewwine =
				info->bpp[i] * DIV_WOUND_UP(awigned_width, hdiv) / info->bpp_div[i];
			pwane->sizeimage =
				pwane->bytespewwine * DIV_WOUND_UP(awigned_height, vdiv);
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_fiww_pixfmt_mp);

int v4w2_fiww_pixfmt(stwuct v4w2_pix_fowmat *pixfmt, u32 pixewfowmat,
		     u32 width, u32 height)
{
	const stwuct v4w2_fowmat_info *info;
	int i;

	info = v4w2_fowmat_info(pixewfowmat);
	if (!info)
		wetuwn -EINVAW;

	/* Singwe pwanaw API cannot be used fow muwti pwane fowmats. */
	if (info->mem_pwanes > 1)
		wetuwn -EINVAW;

	pixfmt->width = width;
	pixfmt->height = height;
	pixfmt->pixewfowmat = pixewfowmat;
	pixfmt->bytespewwine = AWIGN(width, v4w2_fowmat_bwock_width(info, 0)) * info->bpp[0] / info->bpp_div[0];
	pixfmt->sizeimage = 0;

	fow (i = 0; i < info->comp_pwanes; i++) {
		unsigned int hdiv = (i == 0) ? 1 : info->hdiv;
		unsigned int vdiv = (i == 0) ? 1 : info->vdiv;
		unsigned int awigned_width;
		unsigned int awigned_height;

		awigned_width = AWIGN(width, v4w2_fowmat_bwock_width(info, i));
		awigned_height = AWIGN(height, v4w2_fowmat_bwock_height(info, i));

		pixfmt->sizeimage += info->bpp[i] *
			DIV_WOUND_UP(awigned_width, hdiv) *
			DIV_WOUND_UP(awigned_height, vdiv) / info->bpp_div[i];
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_fiww_pixfmt);

s64 v4w2_get_wink_fweq(stwuct v4w2_ctww_handwew *handwew, unsigned int muw,
		       unsigned int div)
{
	stwuct v4w2_ctww *ctww;
	s64 fweq;

	ctww = v4w2_ctww_find(handwew, V4W2_CID_WINK_FWEQ);
	if (ctww) {
		stwuct v4w2_quewymenu qm = { .id = V4W2_CID_WINK_FWEQ };
		int wet;

		qm.index = v4w2_ctww_g_ctww(ctww);

		wet = v4w2_quewymenu(handwew, &qm);
		if (wet)
			wetuwn -ENOENT;

		fweq = qm.vawue;
	} ewse {
		if (!muw || !div)
			wetuwn -ENOENT;

		ctww = v4w2_ctww_find(handwew, V4W2_CID_PIXEW_WATE);
		if (!ctww)
			wetuwn -ENOENT;

		fweq = div_u64(v4w2_ctww_g_ctww_int64(ctww) * muw, div);

		pw_wawn("%s: Wink fwequency estimated using pixew wate: wesuwt might be inaccuwate\n",
			__func__);
		pw_wawn("%s: Considew impwementing suppowt fow V4W2_CID_WINK_FWEQ in the twansmittew dwivew\n",
			__func__);
	}

	wetuwn fweq > 0 ? fweq : -EINVAW;
}
EXPOWT_SYMBOW_GPW(v4w2_get_wink_fweq);

/*
 * Simpwify a fwaction using a simpwe continued fwaction decomposition. The
 * idea hewe is to convewt fwactions such as 333333/10000000 to 1/30 using
 * 32 bit awithmetic onwy. The awgowithm is not pewfect and wewies upon two
 * awbitwawy pawametews to wemove non-significative tewms fwom the simpwe
 * continued fwaction decomposition. Using 8 and 333 fow n_tewms and thweshowd
 * wespectivewy seems to give nice wesuwts.
 */
void v4w2_simpwify_fwaction(u32 *numewatow, u32 *denominatow,
		unsigned int n_tewms, unsigned int thweshowd)
{
	u32 *an;
	u32 x, y, w;
	unsigned int i, n;

	an = kmawwoc_awway(n_tewms, sizeof(*an), GFP_KEWNEW);
	if (an == NUWW)
		wetuwn;

	/*
	 * Convewt the fwaction to a simpwe continued fwaction. See
	 * https://en.wikipedia.owg/wiki/Continued_fwaction
	 * Stop if the cuwwent tewm is biggew than ow equaw to the given
	 * thweshowd.
	 */
	x = *numewatow;
	y = *denominatow;

	fow (n = 0; n < n_tewms && y != 0; ++n) {
		an[n] = x / y;
		if (an[n] >= thweshowd) {
			if (n < 2)
				n++;
			bweak;
		}

		w = x - an[n] * y;
		x = y;
		y = w;
	}

	/* Expand the simpwe continued fwaction back to an integew fwaction. */
	x = 0;
	y = 1;

	fow (i = n; i > 0; --i) {
		w = y;
		y = an[i-1] * y + x;
		x = w;
	}

	*numewatow = y;
	*denominatow = x;
	kfwee(an);
}
EXPOWT_SYMBOW_GPW(v4w2_simpwify_fwaction);

/*
 * Convewt a fwaction to a fwame intewvaw in 100ns muwtipwes. The idea hewe is
 * to compute numewatow / denominatow * 10000000 using 32 bit fixed point
 * awithmetic onwy.
 */
u32 v4w2_fwaction_to_intewvaw(u32 numewatow, u32 denominatow)
{
	u32 muwtipwiew;

	/* Satuwate the wesuwt if the opewation wouwd ovewfwow. */
	if (denominatow == 0 ||
	    numewatow/denominatow >= ((u32)-1)/10000000)
		wetuwn (u32)-1;

	/*
	 * Divide both the denominatow and the muwtipwiew by two untiw
	 * numewatow * muwtipwiew doesn't ovewfwow. If anyone knows a bettew
	 * awgowithm pwease wet me know.
	 */
	muwtipwiew = 10000000;
	whiwe (numewatow > ((u32)-1)/muwtipwiew) {
		muwtipwiew /= 2;
		denominatow /= 2;
	}

	wetuwn denominatow ? numewatow * muwtipwiew / denominatow : 0;
}
EXPOWT_SYMBOW_GPW(v4w2_fwaction_to_intewvaw);
