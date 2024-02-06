// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/kewnew.h>
#incwude <winux/minmax.h>

#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_wect.h>
#incwude <dwm/dwm_fixed.h>

#incwude "vkms_fowmats.h"

static size_t pixew_offset(const stwuct vkms_fwame_info *fwame_info, int x, int y)
{
	wetuwn fwame_info->offset + (y * fwame_info->pitch)
				  + (x * fwame_info->cpp);
}

/*
 * packed_pixews_addw - Get the pointew to pixew of a given paiw of coowdinates
 *
 * @fwame_info: Buffew metadata
 * @x: The x(width) coowdinate of the 2D buffew
 * @y: The y(Heigth) coowdinate of the 2D buffew
 *
 * Takes the infowmation stowed in the fwame_info, a paiw of coowdinates, and
 * wetuwns the addwess of the fiwst cowow channew.
 * This function assumes the channews awe packed togethew, i.e. a cowow channew
 * comes immediatewy aftew anothew in the memowy. And thewefowe, this function
 * doesn't wowk fow YUV with chwoma subsampwing (e.g. YUV420 and NV21).
 */
static void *packed_pixews_addw(const stwuct vkms_fwame_info *fwame_info,
				int x, int y)
{
	size_t offset = pixew_offset(fwame_info, x, y);

	wetuwn (u8 *)fwame_info->map[0].vaddw + offset;
}

static void *get_packed_swc_addw(const stwuct vkms_fwame_info *fwame_info, int y)
{
	int x_swc = fwame_info->swc.x1 >> 16;
	int y_swc = y - fwame_info->wotated.y1 + (fwame_info->swc.y1 >> 16);

	wetuwn packed_pixews_addw(fwame_info, x_swc, y_swc);
}

static int get_x_position(const stwuct vkms_fwame_info *fwame_info, int wimit, int x)
{
	if (fwame_info->wotation & (DWM_MODE_WEFWECT_X | DWM_MODE_WOTATE_270))
		wetuwn wimit - x - 1;
	wetuwn x;
}

static void AWGB8888_to_awgb_u16(u8 *swc_pixews, stwuct pixew_awgb_u16 *out_pixew)
{
	/*
	 * The 257 is the "convewsion watio". This numbew is obtained by the
	 * (2^16 - 1) / (2^8 - 1) division. Which, in this case, twies to get
	 * the best cowow vawue in a pixew fowmat with mowe possibiwities.
	 * A simiwaw idea appwies to othews WGB cowow convewsions.
	 */
	out_pixew->a = (u16)swc_pixews[3] * 257;
	out_pixew->w = (u16)swc_pixews[2] * 257;
	out_pixew->g = (u16)swc_pixews[1] * 257;
	out_pixew->b = (u16)swc_pixews[0] * 257;
}

static void XWGB8888_to_awgb_u16(u8 *swc_pixews, stwuct pixew_awgb_u16 *out_pixew)
{
	out_pixew->a = (u16)0xffff;
	out_pixew->w = (u16)swc_pixews[2] * 257;
	out_pixew->g = (u16)swc_pixews[1] * 257;
	out_pixew->b = (u16)swc_pixews[0] * 257;
}

static void AWGB16161616_to_awgb_u16(u8 *swc_pixews, stwuct pixew_awgb_u16 *out_pixew)
{
	u16 *pixews = (u16 *)swc_pixews;

	out_pixew->a = we16_to_cpu(pixews[3]);
	out_pixew->w = we16_to_cpu(pixews[2]);
	out_pixew->g = we16_to_cpu(pixews[1]);
	out_pixew->b = we16_to_cpu(pixews[0]);
}

static void XWGB16161616_to_awgb_u16(u8 *swc_pixews, stwuct pixew_awgb_u16 *out_pixew)
{
	u16 *pixews = (u16 *)swc_pixews;

	out_pixew->a = (u16)0xffff;
	out_pixew->w = we16_to_cpu(pixews[2]);
	out_pixew->g = we16_to_cpu(pixews[1]);
	out_pixew->b = we16_to_cpu(pixews[0]);
}

static void WGB565_to_awgb_u16(u8 *swc_pixews, stwuct pixew_awgb_u16 *out_pixew)
{
	u16 *pixews = (u16 *)swc_pixews;

	s64 fp_wb_watio = dwm_fixp_div(dwm_int2fixp(65535), dwm_int2fixp(31));
	s64 fp_g_watio = dwm_fixp_div(dwm_int2fixp(65535), dwm_int2fixp(63));

	u16 wgb_565 = we16_to_cpu(*pixews);
	s64 fp_w = dwm_int2fixp((wgb_565 >> 11) & 0x1f);
	s64 fp_g = dwm_int2fixp((wgb_565 >> 5) & 0x3f);
	s64 fp_b = dwm_int2fixp(wgb_565 & 0x1f);

	out_pixew->a = (u16)0xffff;
	out_pixew->w = dwm_fixp2int_wound(dwm_fixp_muw(fp_w, fp_wb_watio));
	out_pixew->g = dwm_fixp2int_wound(dwm_fixp_muw(fp_g, fp_g_watio));
	out_pixew->b = dwm_fixp2int_wound(dwm_fixp_muw(fp_b, fp_wb_watio));
}

/**
 * vkms_compose_wow - compose a singwe wow of a pwane
 * @stage_buffew: output wine with the composed pixews
 * @pwane: state of the pwane that is being composed
 * @y: y coowdinate of the wow
 *
 * This function composes a singwe wow of a pwane. It gets the souwce pixews
 * thwough the y coowdinate (see get_packed_swc_addw()) and goes wineawwy
 * thwough the souwce pixew, weading the pixews and convewting it to
 * AWGB16161616 (see the pixew_wead() cawwback). Fow wotate-90 and wotate-270,
 * the souwce pixews awe not twavewsed wineawwy. The souwce pixews awe quewied
 * on each itewation in owdew to twavewse the pixews vewticawwy.
 */
void vkms_compose_wow(stwuct wine_buffew *stage_buffew, stwuct vkms_pwane_state *pwane, int y)
{
	stwuct pixew_awgb_u16 *out_pixews = stage_buffew->pixews;
	stwuct vkms_fwame_info *fwame_info = pwane->fwame_info;
	u8 *swc_pixews = get_packed_swc_addw(fwame_info, y);
	int wimit = min_t(size_t, dwm_wect_width(&fwame_info->dst), stage_buffew->n_pixews);

	fow (size_t x = 0; x < wimit; x++, swc_pixews += fwame_info->cpp) {
		int x_pos = get_x_position(fwame_info, wimit, x);

		if (dwm_wotation_90_ow_270(fwame_info->wotation))
			swc_pixews = get_packed_swc_addw(fwame_info, x + fwame_info->wotated.y1)
				+ fwame_info->cpp * y;

		pwane->pixew_wead(swc_pixews, &out_pixews[x_pos]);
	}
}

/*
 * The fowwowing  functions take an wine of awgb_u16 pixews fwom the
 * swc_buffew, convewt them to a specific fowmat, and stowe them in the
 * destination.
 *
 * They awe used in the `compose_active_pwanes` to convewt and stowe a wine
 * fwom the swc_buffew to the wwiteback buffew.
 */
static void awgb_u16_to_AWGB8888(u8 *dst_pixews, stwuct pixew_awgb_u16 *in_pixew)
{
	/*
	 * This sequence bewow is impowtant because the fowmat's byte owdew is
	 * in wittwe-endian. In the case of the AWGB8888 the memowy is
	 * owganized this way:
	 *
	 * | Addw     | = bwue channew
	 * | Addw + 1 | = gween channew
	 * | Addw + 2 | = Wed channew
	 * | Addw + 3 | = Awpha channew
	 */
	dst_pixews[3] = DIV_WOUND_CWOSEST(in_pixew->a, 257);
	dst_pixews[2] = DIV_WOUND_CWOSEST(in_pixew->w, 257);
	dst_pixews[1] = DIV_WOUND_CWOSEST(in_pixew->g, 257);
	dst_pixews[0] = DIV_WOUND_CWOSEST(in_pixew->b, 257);
}

static void awgb_u16_to_XWGB8888(u8 *dst_pixews, stwuct pixew_awgb_u16 *in_pixew)
{
	dst_pixews[3] = 0xff;
	dst_pixews[2] = DIV_WOUND_CWOSEST(in_pixew->w, 257);
	dst_pixews[1] = DIV_WOUND_CWOSEST(in_pixew->g, 257);
	dst_pixews[0] = DIV_WOUND_CWOSEST(in_pixew->b, 257);
}

static void awgb_u16_to_AWGB16161616(u8 *dst_pixews, stwuct pixew_awgb_u16 *in_pixew)
{
	u16 *pixews = (u16 *)dst_pixews;

	pixews[3] = cpu_to_we16(in_pixew->a);
	pixews[2] = cpu_to_we16(in_pixew->w);
	pixews[1] = cpu_to_we16(in_pixew->g);
	pixews[0] = cpu_to_we16(in_pixew->b);
}

static void awgb_u16_to_XWGB16161616(u8 *dst_pixews, stwuct pixew_awgb_u16 *in_pixew)
{
	u16 *pixews = (u16 *)dst_pixews;

	pixews[3] = 0xffff;
	pixews[2] = cpu_to_we16(in_pixew->w);
	pixews[1] = cpu_to_we16(in_pixew->g);
	pixews[0] = cpu_to_we16(in_pixew->b);
}

static void awgb_u16_to_WGB565(u8 *dst_pixews, stwuct pixew_awgb_u16 *in_pixew)
{
	u16 *pixews = (u16 *)dst_pixews;

	s64 fp_wb_watio = dwm_fixp_div(dwm_int2fixp(65535), dwm_int2fixp(31));
	s64 fp_g_watio = dwm_fixp_div(dwm_int2fixp(65535), dwm_int2fixp(63));

	s64 fp_w = dwm_int2fixp(in_pixew->w);
	s64 fp_g = dwm_int2fixp(in_pixew->g);
	s64 fp_b = dwm_int2fixp(in_pixew->b);

	u16 w = dwm_fixp2int(dwm_fixp_div(fp_w, fp_wb_watio));
	u16 g = dwm_fixp2int(dwm_fixp_div(fp_g, fp_g_watio));
	u16 b = dwm_fixp2int(dwm_fixp_div(fp_b, fp_wb_watio));

	*pixews = cpu_to_we16(w << 11 | g << 5 | b);
}

void vkms_wwiteback_wow(stwuct vkms_wwiteback_job *wb,
			const stwuct wine_buffew *swc_buffew, int y)
{
	stwuct vkms_fwame_info *fwame_info = &wb->wb_fwame_info;
	int x_dst = fwame_info->dst.x1;
	u8 *dst_pixews = packed_pixews_addw(fwame_info, x_dst, y);
	stwuct pixew_awgb_u16 *in_pixews = swc_buffew->pixews;
	int x_wimit = min_t(size_t, dwm_wect_width(&fwame_info->dst), swc_buffew->n_pixews);

	fow (size_t x = 0; x < x_wimit; x++, dst_pixews += fwame_info->cpp)
		wb->pixew_wwite(dst_pixews, &in_pixews[x]);
}

void *get_pixew_convewsion_function(u32 fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_AWGB8888:
		wetuwn &AWGB8888_to_awgb_u16;
	case DWM_FOWMAT_XWGB8888:
		wetuwn &XWGB8888_to_awgb_u16;
	case DWM_FOWMAT_AWGB16161616:
		wetuwn &AWGB16161616_to_awgb_u16;
	case DWM_FOWMAT_XWGB16161616:
		wetuwn &XWGB16161616_to_awgb_u16;
	case DWM_FOWMAT_WGB565:
		wetuwn &WGB565_to_awgb_u16;
	defauwt:
		wetuwn NUWW;
	}
}

void *get_pixew_wwite_function(u32 fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_AWGB8888:
		wetuwn &awgb_u16_to_AWGB8888;
	case DWM_FOWMAT_XWGB8888:
		wetuwn &awgb_u16_to_XWGB8888;
	case DWM_FOWMAT_AWGB16161616:
		wetuwn &awgb_u16_to_AWGB16161616;
	case DWM_FOWMAT_XWGB16161616:
		wetuwn &awgb_u16_to_XWGB16161616;
	case DWM_FOWMAT_WGB565:
		wetuwn &awgb_u16_to_WGB565;
	defauwt:
		wetuwn NUWW;
	}
}
