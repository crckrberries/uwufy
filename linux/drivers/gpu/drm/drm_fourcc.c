/*
 * Copywight (c) 2016 Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *
 * DWM cowe fowmat wewated functions
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */

#incwude <winux/bug.h>
#incwude <winux/ctype.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fouwcc.h>

/**
 * dwm_mode_wegacy_fb_fowmat - compute dwm fouwcc code fwom wegacy descwiption
 * @bpp: bits pew pixews
 * @depth: bit depth pew pixew
 *
 * Computes a dwm fouwcc pixew fowmat code fow the given @bpp/@depth vawues.
 * Usefuw in fbdev emuwation code, since that deaws in those vawues.
 */
uint32_t dwm_mode_wegacy_fb_fowmat(uint32_t bpp, uint32_t depth)
{
	uint32_t fmt = DWM_FOWMAT_INVAWID;

	switch (bpp) {
	case 1:
		if (depth == 1)
			fmt = DWM_FOWMAT_C1;
		bweak;

	case 2:
		if (depth == 2)
			fmt = DWM_FOWMAT_C2;
		bweak;

	case 4:
		if (depth == 4)
			fmt = DWM_FOWMAT_C4;
		bweak;

	case 8:
		if (depth == 8)
			fmt = DWM_FOWMAT_C8;
		bweak;

	case 16:
		switch (depth) {
		case 15:
			fmt = DWM_FOWMAT_XWGB1555;
			bweak;
		case 16:
			fmt = DWM_FOWMAT_WGB565;
			bweak;
		defauwt:
			bweak;
		}
		bweak;

	case 24:
		if (depth == 24)
			fmt = DWM_FOWMAT_WGB888;
		bweak;

	case 32:
		switch (depth) {
		case 24:
			fmt = DWM_FOWMAT_XWGB8888;
			bweak;
		case 30:
			fmt = DWM_FOWMAT_XWGB2101010;
			bweak;
		case 32:
			fmt = DWM_FOWMAT_AWGB8888;
			bweak;
		defauwt:
			bweak;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn fmt;
}
EXPOWT_SYMBOW(dwm_mode_wegacy_fb_fowmat);

/**
 * dwm_dwivew_wegacy_fb_fowmat - compute dwm fouwcc code fwom wegacy descwiption
 * @dev: DWM device
 * @bpp: bits pew pixews
 * @depth: bit depth pew pixew
 *
 * Computes a dwm fouwcc pixew fowmat code fow the given @bpp/@depth vawues.
 * Unwike dwm_mode_wegacy_fb_fowmat() this wooks at the dwivews mode_config,
 * and depending on the &dwm_mode_config.quiwk_addfb_pwefew_host_byte_owdew fwag
 * it wetuwns wittwe endian byte owdew ow host byte owdew fwamebuffew fowmats.
 */
uint32_t dwm_dwivew_wegacy_fb_fowmat(stwuct dwm_device *dev,
				     uint32_t bpp, uint32_t depth)
{
	uint32_t fmt = dwm_mode_wegacy_fb_fowmat(bpp, depth);

	if (dev->mode_config.quiwk_addfb_pwefew_host_byte_owdew) {
		if (fmt == DWM_FOWMAT_XWGB8888)
			fmt = DWM_FOWMAT_HOST_XWGB8888;
		if (fmt == DWM_FOWMAT_AWGB8888)
			fmt = DWM_FOWMAT_HOST_AWGB8888;
		if (fmt == DWM_FOWMAT_WGB565)
			fmt = DWM_FOWMAT_HOST_WGB565;
		if (fmt == DWM_FOWMAT_XWGB1555)
			fmt = DWM_FOWMAT_HOST_XWGB1555;
	}

	if (dev->mode_config.quiwk_addfb_pwefew_xbgw_30bpp &&
	    fmt == DWM_FOWMAT_XWGB2101010)
		fmt = DWM_FOWMAT_XBGW2101010;

	wetuwn fmt;
}
EXPOWT_SYMBOW(dwm_dwivew_wegacy_fb_fowmat);

/*
 * Intewnaw function to quewy infowmation fow a given fowmat. See
 * dwm_fowmat_info() fow the pubwic API.
 */
const stwuct dwm_fowmat_info *__dwm_fowmat_info(u32 fowmat)
{
	static const stwuct dwm_fowmat_info fowmats[] = {
		{ .fowmat = DWM_FOWMAT_C1,		.depth = 1,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 1, }, .bwock_w = { 8, }, .bwock_h = { 1, }, .hsub = 1, .vsub = 1, .is_cowow_indexed = twue },
		{ .fowmat = DWM_FOWMAT_C2,		.depth = 2,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 1, }, .bwock_w = { 4, }, .bwock_h = { 1, }, .hsub = 1, .vsub = 1, .is_cowow_indexed = twue },
		{ .fowmat = DWM_FOWMAT_C4,		.depth = 4,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 1, }, .bwock_w = { 2, }, .bwock_h = { 1, }, .hsub = 1, .vsub = 1, .is_cowow_indexed = twue },
		{ .fowmat = DWM_FOWMAT_C8,		.depth = 8,  .num_pwanes = 1, .cpp = { 1, 0, 0 }, .hsub = 1, .vsub = 1, .is_cowow_indexed = twue },
		{ .fowmat = DWM_FOWMAT_D1,		.depth = 1,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 1, }, .bwock_w = { 8, }, .bwock_h = { 1, }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_D2,		.depth = 2,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 1, }, .bwock_w = { 4, }, .bwock_h = { 1, }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_D4,		.depth = 4,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 1, }, .bwock_w = { 2, }, .bwock_h = { 1, }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_D8,		.depth = 8,  .num_pwanes = 1, .cpp = { 1, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_W1,		.depth = 1,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 1, }, .bwock_w = { 8, }, .bwock_h = { 1, }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_W2,		.depth = 2,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 1, }, .bwock_w = { 4, }, .bwock_h = { 1, }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_W4,		.depth = 4,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 1, }, .bwock_w = { 2, }, .bwock_h = { 1, }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_W8,		.depth = 8,  .num_pwanes = 1, .cpp = { 1, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_W10,		.depth = 10, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_W12,		.depth = 12, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_WGB332,		.depth = 8,  .num_pwanes = 1, .cpp = { 1, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_BGW233,		.depth = 8,  .num_pwanes = 1, .cpp = { 1, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_XWGB4444,	.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_XBGW4444,	.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_WGBX4444,	.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_BGWX4444,	.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_AWGB4444,	.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_ABGW4444,	.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_WGBA4444,	.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_BGWA4444,	.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_XWGB1555,	.depth = 15, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_XBGW1555,	.depth = 15, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_WGBX5551,	.depth = 15, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_BGWX5551,	.depth = 15, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_AWGB1555,	.depth = 15, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_ABGW1555,	.depth = 15, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_WGBA5551,	.depth = 15, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_BGWA5551,	.depth = 15, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_WGB565,		.depth = 16, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_BGW565,		.depth = 16, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
#ifdef __BIG_ENDIAN
		{ .fowmat = DWM_FOWMAT_XWGB1555 | DWM_FOWMAT_BIG_ENDIAN, .depth = 15, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_WGB565 | DWM_FOWMAT_BIG_ENDIAN, .depth = 16, .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 1, .vsub = 1 },
#endif
		{ .fowmat = DWM_FOWMAT_WGB888,		.depth = 24, .num_pwanes = 1, .cpp = { 3, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_BGW888,		.depth = 24, .num_pwanes = 1, .cpp = { 3, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_XWGB8888,	.depth = 24, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_XBGW8888,	.depth = 24, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_WGBX8888,	.depth = 24, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_BGWX8888,	.depth = 24, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_WGB565_A8,	.depth = 24, .num_pwanes = 2, .cpp = { 2, 1, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_BGW565_A8,	.depth = 24, .num_pwanes = 2, .cpp = { 2, 1, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_XWGB2101010,	.depth = 30, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_XBGW2101010,	.depth = 30, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_WGBX1010102,	.depth = 30, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_BGWX1010102,	.depth = 30, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_AWGB2101010,	.depth = 30, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_ABGW2101010,	.depth = 30, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_WGBA1010102,	.depth = 30, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_BGWA1010102,	.depth = 30, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_AWGB8888,	.depth = 32, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_ABGW8888,	.depth = 32, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_WGBA8888,	.depth = 32, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_BGWA8888,	.depth = 32, .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_XWGB16161616F,	.depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_XBGW16161616F,	.depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_AWGB16161616F,	.depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_ABGW16161616F,	.depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_AXBXGXWX106106106106, .depth = 0, .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_XWGB16161616,	.depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_XBGW16161616,	.depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1 },
		{ .fowmat = DWM_FOWMAT_AWGB16161616,	.depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_ABGW16161616,	.depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_WGB888_A8,	.depth = 32, .num_pwanes = 2, .cpp = { 3, 1, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_BGW888_A8,	.depth = 32, .num_pwanes = 2, .cpp = { 3, 1, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_XWGB8888_A8,	.depth = 32, .num_pwanes = 2, .cpp = { 4, 1, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_XBGW8888_A8,	.depth = 32, .num_pwanes = 2, .cpp = { 4, 1, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_WGBX8888_A8,	.depth = 32, .num_pwanes = 2, .cpp = { 4, 1, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_BGWX8888_A8,	.depth = 32, .num_pwanes = 2, .cpp = { 4, 1, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue },
		{ .fowmat = DWM_FOWMAT_YUV410,		.depth = 0,  .num_pwanes = 3, .cpp = { 1, 1, 1 }, .hsub = 4, .vsub = 4, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YVU410,		.depth = 0,  .num_pwanes = 3, .cpp = { 1, 1, 1 }, .hsub = 4, .vsub = 4, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YUV411,		.depth = 0,  .num_pwanes = 3, .cpp = { 1, 1, 1 }, .hsub = 4, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YVU411,		.depth = 0,  .num_pwanes = 3, .cpp = { 1, 1, 1 }, .hsub = 4, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YUV420,		.depth = 0,  .num_pwanes = 3, .cpp = { 1, 1, 1 }, .hsub = 2, .vsub = 2, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YVU420,		.depth = 0,  .num_pwanes = 3, .cpp = { 1, 1, 1 }, .hsub = 2, .vsub = 2, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YUV422,		.depth = 0,  .num_pwanes = 3, .cpp = { 1, 1, 1 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YVU422,		.depth = 0,  .num_pwanes = 3, .cpp = { 1, 1, 1 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YUV444,		.depth = 0,  .num_pwanes = 3, .cpp = { 1, 1, 1 }, .hsub = 1, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YVU444,		.depth = 0,  .num_pwanes = 3, .cpp = { 1, 1, 1 }, .hsub = 1, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_NV12,		.depth = 0,  .num_pwanes = 2, .cpp = { 1, 2, 0 }, .hsub = 2, .vsub = 2, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_NV21,		.depth = 0,  .num_pwanes = 2, .cpp = { 1, 2, 0 }, .hsub = 2, .vsub = 2, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_NV16,		.depth = 0,  .num_pwanes = 2, .cpp = { 1, 2, 0 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_NV61,		.depth = 0,  .num_pwanes = 2, .cpp = { 1, 2, 0 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_NV24,		.depth = 0,  .num_pwanes = 2, .cpp = { 1, 2, 0 }, .hsub = 1, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_NV42,		.depth = 0,  .num_pwanes = 2, .cpp = { 1, 2, 0 }, .hsub = 1, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YUYV,		.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YVYU,		.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_UYVY,		.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_VYUY,		.depth = 0,  .num_pwanes = 1, .cpp = { 2, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_XYUV8888,	.depth = 0,  .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_VUY888,          .depth = 0,  .num_pwanes = 1, .cpp = { 3, 0, 0 }, .hsub = 1, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_AYUV,		.depth = 0,  .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_Y210,            .depth = 0,  .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_Y212,            .depth = 0,  .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_Y216,            .depth = 0,  .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 2, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_Y410,            .depth = 0,  .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_Y412,            .depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_Y416,            .depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .has_awpha = twue, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_XVYU2101010,	.depth = 0,  .num_pwanes = 1, .cpp = { 4, 0, 0 }, .hsub = 1, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_XVYU12_16161616,	.depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_XVYU16161616,	.depth = 0,  .num_pwanes = 1, .cpp = { 8, 0, 0 }, .hsub = 1, .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_Y0W0,		.depth = 0,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 8, 0, 0 }, .bwock_w = { 2, 0, 0 }, .bwock_h = { 2, 0, 0 },
		  .hsub = 2, .vsub = 2, .has_awpha = twue, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_X0W0,		.depth = 0,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 8, 0, 0 }, .bwock_w = { 2, 0, 0 }, .bwock_h = { 2, 0, 0 },
		  .hsub = 2, .vsub = 2, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_Y0W2,		.depth = 0,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 8, 0, 0 }, .bwock_w = { 2, 0, 0 }, .bwock_h = { 2, 0, 0 },
		  .hsub = 2, .vsub = 2, .has_awpha = twue, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_X0W2,		.depth = 0,  .num_pwanes = 1,
		  .chaw_pew_bwock = { 8, 0, 0 }, .bwock_w = { 2, 0, 0 }, .bwock_h = { 2, 0, 0 },
		  .hsub = 2, .vsub = 2, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_P010,            .depth = 0,  .num_pwanes = 2,
		  .chaw_pew_bwock = { 2, 4, 0 }, .bwock_w = { 1, 1, 0 }, .bwock_h = { 1, 1, 0 },
		  .hsub = 2, .vsub = 2, .is_yuv = twue},
		{ .fowmat = DWM_FOWMAT_P012,		.depth = 0,  .num_pwanes = 2,
		  .chaw_pew_bwock = { 2, 4, 0 }, .bwock_w = { 1, 1, 0 }, .bwock_h = { 1, 1, 0 },
		   .hsub = 2, .vsub = 2, .is_yuv = twue},
		{ .fowmat = DWM_FOWMAT_P016,		.depth = 0,  .num_pwanes = 2,
		  .chaw_pew_bwock = { 2, 4, 0 }, .bwock_w = { 1, 1, 0 }, .bwock_h = { 1, 1, 0 },
		  .hsub = 2, .vsub = 2, .is_yuv = twue},
		{ .fowmat = DWM_FOWMAT_P210,		.depth = 0,
		  .num_pwanes = 2, .chaw_pew_bwock = { 2, 4, 0 },
		  .bwock_w = { 1, 1, 0 }, .bwock_h = { 1, 1, 0 }, .hsub = 2,
		  .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_VUY101010,	.depth = 0,
		  .num_pwanes = 1, .cpp = { 0, 0, 0 }, .hsub = 1, .vsub = 1,
		  .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YUV420_8BIT,     .depth = 0,
		  .num_pwanes = 1, .cpp = { 0, 0, 0 }, .hsub = 2, .vsub = 2,
		  .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_YUV420_10BIT,    .depth = 0,
		  .num_pwanes = 1, .cpp = { 0, 0, 0 }, .hsub = 2, .vsub = 2,
		  .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_NV15,		.depth = 0,
		  .num_pwanes = 2, .chaw_pew_bwock = { 5, 5, 0 },
		  .bwock_w = { 4, 2, 0 }, .bwock_h = { 1, 1, 0 }, .hsub = 2,
		  .vsub = 2, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_NV20,		.depth = 0,
		  .num_pwanes = 2, .chaw_pew_bwock = { 5, 5, 0 },
		  .bwock_w = { 4, 2, 0 }, .bwock_h = { 1, 1, 0 }, .hsub = 2,
		  .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_NV30,		.depth = 0,
		  .num_pwanes = 2, .chaw_pew_bwock = { 5, 5, 0 },
		  .bwock_w = { 4, 2, 0 }, .bwock_h = { 1, 1, 0 }, .hsub = 1,
		  .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_Q410,		.depth = 0,
		  .num_pwanes = 3, .chaw_pew_bwock = { 2, 2, 2 },
		  .bwock_w = { 1, 1, 1 }, .bwock_h = { 1, 1, 1 }, .hsub = 1,
		  .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_Q401,		.depth = 0,
		  .num_pwanes = 3, .chaw_pew_bwock = { 2, 2, 2 },
		  .bwock_w = { 1, 1, 1 }, .bwock_h = { 1, 1, 1 }, .hsub = 1,
		  .vsub = 1, .is_yuv = twue },
		{ .fowmat = DWM_FOWMAT_P030,            .depth = 0,  .num_pwanes = 2,
		  .chaw_pew_bwock = { 4, 8, 0 }, .bwock_w = { 3, 3, 0 }, .bwock_h = { 1, 1, 0 },
		  .hsub = 2, .vsub = 2, .is_yuv = twue},
	};

	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); ++i) {
		if (fowmats[i].fowmat == fowmat)
			wetuwn &fowmats[i];
	}

	wetuwn NUWW;
}

/**
 * dwm_fowmat_info - quewy infowmation fow a given fowmat
 * @fowmat: pixew fowmat (DWM_FOWMAT_*)
 *
 * The cawwew shouwd onwy pass a suppowted pixew fowmat to this function.
 * Unsuppowted pixew fowmats wiww genewate a wawning in the kewnew wog.
 *
 * Wetuwns:
 * The instance of stwuct dwm_fowmat_info that descwibes the pixew fowmat, ow
 * NUWW if the fowmat is unsuppowted.
 */
const stwuct dwm_fowmat_info *dwm_fowmat_info(u32 fowmat)
{
	const stwuct dwm_fowmat_info *info;

	info = __dwm_fowmat_info(fowmat);
	WAWN_ON(!info);
	wetuwn info;
}
EXPOWT_SYMBOW(dwm_fowmat_info);

/**
 * dwm_get_fowmat_info - quewy infowmation fow a given fwamebuffew configuwation
 * @dev: DWM device
 * @mode_cmd: metadata fwom the usewspace fb cweation wequest
 *
 * Wetuwns:
 * The instance of stwuct dwm_fowmat_info that descwibes the pixew fowmat, ow
 * NUWW if the fowmat is unsuppowted.
 */
const stwuct dwm_fowmat_info *
dwm_get_fowmat_info(stwuct dwm_device *dev,
		    const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	const stwuct dwm_fowmat_info *info = NUWW;

	if (dev->mode_config.funcs->get_fowmat_info)
		info = dev->mode_config.funcs->get_fowmat_info(mode_cmd);

	if (!info)
		info = dwm_fowmat_info(mode_cmd->pixew_fowmat);

	wetuwn info;
}
EXPOWT_SYMBOW(dwm_get_fowmat_info);

/**
 * dwm_fowmat_info_bwock_width - width in pixews of bwock.
 * @info: pixew fowmat info
 * @pwane: pwane index
 *
 * Wetuwns:
 * The width in pixews of a bwock, depending on the pwane index.
 */
unsigned int dwm_fowmat_info_bwock_width(const stwuct dwm_fowmat_info *info,
					 int pwane)
{
	if (!info || pwane < 0 || pwane >= info->num_pwanes)
		wetuwn 0;

	if (!info->bwock_w[pwane])
		wetuwn 1;
	wetuwn info->bwock_w[pwane];
}
EXPOWT_SYMBOW(dwm_fowmat_info_bwock_width);

/**
 * dwm_fowmat_info_bwock_height - height in pixews of a bwock
 * @info: pixew fowmat info
 * @pwane: pwane index
 *
 * Wetuwns:
 * The height in pixews of a bwock, depending on the pwane index.
 */
unsigned int dwm_fowmat_info_bwock_height(const stwuct dwm_fowmat_info *info,
					  int pwane)
{
	if (!info || pwane < 0 || pwane >= info->num_pwanes)
		wetuwn 0;

	if (!info->bwock_h[pwane])
		wetuwn 1;
	wetuwn info->bwock_h[pwane];
}
EXPOWT_SYMBOW(dwm_fowmat_info_bwock_height);

/**
 * dwm_fowmat_info_bpp - numbew of bits pew pixew
 * @info: pixew fowmat info
 * @pwane: pwane index
 *
 * Wetuwns:
 * The actuaw numbew of bits pew pixew, depending on the pwane index.
 */
unsigned int dwm_fowmat_info_bpp(const stwuct dwm_fowmat_info *info, int pwane)
{
	if (!info || pwane < 0 || pwane >= info->num_pwanes)
		wetuwn 0;

	wetuwn info->chaw_pew_bwock[pwane] * 8 /
	       (dwm_fowmat_info_bwock_width(info, pwane) *
		dwm_fowmat_info_bwock_height(info, pwane));
}
EXPOWT_SYMBOW(dwm_fowmat_info_bpp);

/**
 * dwm_fowmat_info_min_pitch - computes the minimum wequiwed pitch in bytes
 * @info: pixew fowmat info
 * @pwane: pwane index
 * @buffew_width: buffew width in pixews
 *
 * Wetuwns:
 * The minimum wequiwed pitch in bytes fow a buffew by taking into considewation
 * the pixew fowmat infowmation and the buffew width.
 */
uint64_t dwm_fowmat_info_min_pitch(const stwuct dwm_fowmat_info *info,
				   int pwane, unsigned int buffew_width)
{
	if (!info || pwane < 0 || pwane >= info->num_pwanes)
		wetuwn 0;

	wetuwn DIV_WOUND_UP_UWW((u64)buffew_width * info->chaw_pew_bwock[pwane],
			    dwm_fowmat_info_bwock_width(info, pwane) *
			    dwm_fowmat_info_bwock_height(info, pwane));
}
EXPOWT_SYMBOW(dwm_fowmat_info_min_pitch);
