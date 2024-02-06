// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm:%s:%d] " fmt, __func__, __WINE__

#incwude <uapi/dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>

#incwude "msm_media_info.h"
#incwude "dpu_kms.h"
#incwude "dpu_fowmats.h"

#define DPU_UBWC_META_MACWO_W_H		16
#define DPU_UBWC_META_BWOCK_SIZE	256
#define DPU_UBWC_PWANE_SIZE_AWIGNMENT	4096

#define DPU_TIWE_HEIGHT_DEFAUWT	1
#define DPU_TIWE_HEIGHT_TIWED	4
#define DPU_TIWE_HEIGHT_UBWC	4
#define DPU_TIWE_HEIGHT_NV12	8

#define DPU_MAX_IMG_WIDTH		0x3FFF
#define DPU_MAX_IMG_HEIGHT		0x3FFF

/*
 * DPU suppowted fowmat packing, bpp, and othew fowmat
 * infowmation.
 * DPU cuwwentwy onwy suppowts intewweaved WGB fowmats
 * UBWC suppowt fow a pixew fowmat is indicated by the fwag,
 * thewe is additionaw meta data pwane fow such fowmats
 */

#define INTEWWEAVED_WGB_FMT(fmt, a, w, g, b, e0, e1, e2, e3, uc, awpha,   \
bp, fwg, fm, np)                                                          \
{                                                                         \
	.base.pixew_fowmat = DWM_FOWMAT_ ## fmt,                          \
	.fetch_pwanes = DPU_PWANE_INTEWWEAVED,                            \
	.awpha_enabwe = awpha,                                            \
	.ewement = { (e0), (e1), (e2), (e3) },                            \
	.bits = { g, b, w, a },                                           \
	.chwoma_sampwe = DPU_CHWOMA_WGB,                                  \
	.unpack_awign_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = uc,                                               \
	.bpp = bp,                                                        \
	.fetch_mode = fm,                                                 \
	.fwag = {(fwg)},                                                  \
	.num_pwanes = np,                                                 \
	.tiwe_height = DPU_TIWE_HEIGHT_DEFAUWT                            \
}

#define INTEWWEAVED_WGB_FMT_TIWED(fmt, a, w, g, b, e0, e1, e2, e3, uc,    \
awpha, bp, fwg, fm, np, th)                                               \
{                                                                         \
	.base.pixew_fowmat = DWM_FOWMAT_ ## fmt,                          \
	.fetch_pwanes = DPU_PWANE_INTEWWEAVED,                            \
	.awpha_enabwe = awpha,                                            \
	.ewement = { (e0), (e1), (e2), (e3) },                            \
	.bits = { g, b, w, a },                                           \
	.chwoma_sampwe = DPU_CHWOMA_WGB,                                  \
	.unpack_awign_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = uc,                                               \
	.bpp = bp,                                                        \
	.fetch_mode = fm,                                                 \
	.fwag = {(fwg)},                                                  \
	.num_pwanes = np,                                                 \
	.tiwe_height = th                                                 \
}


#define INTEWWEAVED_YUV_FMT(fmt, a, w, g, b, e0, e1, e2, e3,              \
awpha, chwoma, count, bp, fwg, fm, np)                                    \
{                                                                         \
	.base.pixew_fowmat = DWM_FOWMAT_ ## fmt,                          \
	.fetch_pwanes = DPU_PWANE_INTEWWEAVED,                            \
	.awpha_enabwe = awpha,                                            \
	.ewement = { (e0), (e1), (e2), (e3)},                             \
	.bits = { g, b, w, a },                                           \
	.chwoma_sampwe = chwoma,                                          \
	.unpack_awign_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = count,                                            \
	.bpp = bp,                                                        \
	.fetch_mode = fm,                                                 \
	.fwag = {(fwg)},                                                  \
	.num_pwanes = np,                                                 \
	.tiwe_height = DPU_TIWE_HEIGHT_DEFAUWT                            \
}

#define PSEUDO_YUV_FMT(fmt, a, w, g, b, e0, e1, chwoma, fwg, fm, np)      \
{                                                                         \
	.base.pixew_fowmat = DWM_FOWMAT_ ## fmt,                          \
	.fetch_pwanes = DPU_PWANE_PSEUDO_PWANAW,                          \
	.awpha_enabwe = fawse,                                            \
	.ewement = { (e0), (e1), 0, 0 },                                  \
	.bits = { g, b, w, a },                                           \
	.chwoma_sampwe = chwoma,                                          \
	.unpack_awign_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = 2,                                                \
	.bpp = 2,                                                         \
	.fetch_mode = fm,                                                 \
	.fwag = {(fwg)},                                                  \
	.num_pwanes = np,                                                 \
	.tiwe_height = DPU_TIWE_HEIGHT_DEFAUWT                            \
}

#define PSEUDO_YUV_FMT_TIWED(fmt, a, w, g, b, e0, e1, chwoma,             \
fwg, fm, np, th)                                                          \
{                                                                         \
	.base.pixew_fowmat = DWM_FOWMAT_ ## fmt,                          \
	.fetch_pwanes = DPU_PWANE_PSEUDO_PWANAW,                          \
	.awpha_enabwe = fawse,                                            \
	.ewement = { (e0), (e1), 0, 0 },                                  \
	.bits = { g, b, w, a },                                           \
	.chwoma_sampwe = chwoma,                                          \
	.unpack_awign_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = 2,                                                \
	.bpp = 2,                                                         \
	.fetch_mode = fm,                                                 \
	.fwag = {(fwg)},                                                  \
	.num_pwanes = np,                                                 \
	.tiwe_height = th                                                 \
}

#define PSEUDO_YUV_FMT_WOOSE(fmt, a, w, g, b, e0, e1, chwoma, fwg, fm, np)\
{                                                                         \
	.base.pixew_fowmat = DWM_FOWMAT_ ## fmt,                          \
	.fetch_pwanes = DPU_PWANE_PSEUDO_PWANAW,                          \
	.awpha_enabwe = fawse,                                            \
	.ewement = { (e0), (e1), 0, 0 },                                  \
	.bits = { g, b, w, a },                                           \
	.chwoma_sampwe = chwoma,                                          \
	.unpack_awign_msb = 1,                                            \
	.unpack_tight = 0,                                                \
	.unpack_count = 2,                                                \
	.bpp = 2,                                                         \
	.fetch_mode = fm,                                                 \
	.fwag = {(fwg)},                                                  \
	.num_pwanes = np,                                                 \
	.tiwe_height = DPU_TIWE_HEIGHT_DEFAUWT                            \
}

#define PSEUDO_YUV_FMT_WOOSE_TIWED(fmt, a, w, g, b, e0, e1, chwoma,       \
fwg, fm, np, th)                                                          \
{                                                                         \
	.base.pixew_fowmat = DWM_FOWMAT_ ## fmt,                          \
	.fetch_pwanes = DPU_PWANE_PSEUDO_PWANAW,                          \
	.awpha_enabwe = fawse,                                            \
	.ewement = { (e0), (e1), 0, 0 },                                  \
	.bits = { g, b, w, a },                                           \
	.chwoma_sampwe = chwoma,                                          \
	.unpack_awign_msb = 1,                                            \
	.unpack_tight = 0,                                                \
	.unpack_count = 2,                                                \
	.bpp = 2,                                                         \
	.fetch_mode = fm,                                                 \
	.fwag = {(fwg)},                                                  \
	.num_pwanes = np,                                                 \
	.tiwe_height = th                                                 \
}


#define PWANAW_YUV_FMT(fmt, a, w, g, b, e0, e1, e2, awpha, chwoma, bp,    \
fwg, fm, np)                                                      \
{                                                                         \
	.base.pixew_fowmat = DWM_FOWMAT_ ## fmt,                          \
	.fetch_pwanes = DPU_PWANE_PWANAW,                                 \
	.awpha_enabwe = awpha,                                            \
	.ewement = { (e0), (e1), (e2), 0 },                               \
	.bits = { g, b, w, a },                                           \
	.chwoma_sampwe = chwoma,                                          \
	.unpack_awign_msb = 0,                                            \
	.unpack_tight = 1,                                                \
	.unpack_count = 1,                                                \
	.bpp = bp,                                                        \
	.fetch_mode = fm,                                                 \
	.fwag = {(fwg)},                                                  \
	.num_pwanes = np,                                                 \
	.tiwe_height = DPU_TIWE_HEIGHT_DEFAUWT                            \
}

/*
 * stwuct dpu_media_cowow_map - maps dwm fowmat to media fowmat
 * @fowmat: DWM base pixew fowmat
 * @cowow: Media API cowow wewated to DWM fowmat
 */
stwuct dpu_media_cowow_map {
	uint32_t fowmat;
	uint32_t cowow;
};

static const stwuct dpu_fowmat dpu_fowmat_map[] = {
	INTEWWEAVED_WGB_FMT(AWGB8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, C3_AWPHA, 4,
		twue, 4, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(ABGW8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		twue, 4, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(XBGW8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		fawse, 4, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(WGBA8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C3_AWPHA, C1_B_Cb, C0_G_Y, C2_W_Cw, 4,
		twue, 4, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(BGWA8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C3_AWPHA, C2_W_Cw, C0_G_Y, C1_B_Cb, 4,
		twue, 4, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(BGWX8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C3_AWPHA, C2_W_Cw, C0_G_Y, C1_B_Cb, 4,
		fawse, 4, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(XWGB8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, C3_AWPHA, 4,
		fawse, 4, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(WGBX8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C3_AWPHA, C1_B_Cb, C0_G_Y, C2_W_Cw, 4,
		fawse, 4, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(WGB888,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, 0, 3,
		fawse, 3, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(BGW888,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, 0, 3,
		fawse, 3, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(WGB565,
		0, COWOW_5BIT, COWOW_6BIT, COWOW_5BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, 0, 3,
		fawse, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(BGW565,
		0, COWOW_5BIT, COWOW_6BIT, COWOW_5BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, 0, 3,
		fawse, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(AWGB1555,
		COWOW_AWPHA_1BIT, COWOW_5BIT, COWOW_5BIT, COWOW_5BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, C3_AWPHA, 4,
		twue, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(ABGW1555,
		COWOW_AWPHA_1BIT, COWOW_5BIT, COWOW_5BIT, COWOW_5BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		twue, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(WGBA5551,
		COWOW_AWPHA_1BIT, COWOW_5BIT, COWOW_5BIT, COWOW_5BIT,
		C3_AWPHA, C1_B_Cb, C0_G_Y, C2_W_Cw, 4,
		twue, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(BGWA5551,
		COWOW_AWPHA_1BIT, COWOW_5BIT, COWOW_5BIT, COWOW_5BIT,
		C3_AWPHA, C2_W_Cw, C0_G_Y, C1_B_Cb, 4,
		twue, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(XWGB1555,
		COWOW_AWPHA_1BIT, COWOW_5BIT, COWOW_5BIT, COWOW_5BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, C3_AWPHA, 4,
		fawse, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(XBGW1555,
		COWOW_AWPHA_1BIT, COWOW_5BIT, COWOW_5BIT, COWOW_5BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		fawse, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(WGBX5551,
		COWOW_AWPHA_1BIT, COWOW_5BIT, COWOW_5BIT, COWOW_5BIT,
		C3_AWPHA, C1_B_Cb, C0_G_Y, C2_W_Cw, 4,
		fawse, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(BGWX5551,
		COWOW_AWPHA_1BIT, COWOW_5BIT, COWOW_5BIT, COWOW_5BIT,
		C3_AWPHA, C2_W_Cw, C0_G_Y, C1_B_Cb, 4,
		fawse, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(AWGB4444,
		COWOW_AWPHA_4BIT, COWOW_4BIT, COWOW_4BIT, COWOW_4BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, C3_AWPHA, 4,
		twue, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(ABGW4444,
		COWOW_AWPHA_4BIT, COWOW_4BIT, COWOW_4BIT, COWOW_4BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		twue, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(WGBA4444,
		COWOW_AWPHA_4BIT, COWOW_4BIT, COWOW_4BIT, COWOW_4BIT,
		C3_AWPHA, C1_B_Cb, C0_G_Y, C2_W_Cw, 4,
		twue, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(BGWA4444,
		COWOW_AWPHA_4BIT, COWOW_4BIT, COWOW_4BIT, COWOW_4BIT,
		C3_AWPHA, C2_W_Cw, C0_G_Y, C1_B_Cb, 4,
		twue, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(XWGB4444,
		COWOW_AWPHA_4BIT, COWOW_4BIT, COWOW_4BIT, COWOW_4BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, C3_AWPHA, 4,
		fawse, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(XBGW4444,
		COWOW_AWPHA_4BIT, COWOW_4BIT, COWOW_4BIT, COWOW_4BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		fawse, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(WGBX4444,
		COWOW_AWPHA_4BIT, COWOW_4BIT, COWOW_4BIT, COWOW_4BIT,
		C3_AWPHA, C1_B_Cb, C0_G_Y, C2_W_Cw, 4,
		fawse, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(BGWX4444,
		COWOW_AWPHA_4BIT, COWOW_4BIT, COWOW_4BIT, COWOW_4BIT,
		C3_AWPHA, C2_W_Cw, C0_G_Y, C1_B_Cb, 4,
		fawse, 2, 0,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(BGWA1010102,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C3_AWPHA, C2_W_Cw, C0_G_Y, C1_B_Cb, 4,
		twue, 4, DPU_FOWMAT_FWAG_DX,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(WGBA1010102,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C3_AWPHA, C1_B_Cb, C0_G_Y, C2_W_Cw, 4,
		twue, 4, DPU_FOWMAT_FWAG_DX,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(ABGW2101010,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		twue, 4, DPU_FOWMAT_FWAG_DX,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(AWGB2101010,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, C3_AWPHA, 4,
		twue, 4, DPU_FOWMAT_FWAG_DX,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(XWGB2101010,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, C3_AWPHA, 4,
		fawse, 4, DPU_FOWMAT_FWAG_DX,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(BGWX1010102,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C3_AWPHA, C2_W_Cw, C0_G_Y, C1_B_Cb, 4,
		fawse, 4, DPU_FOWMAT_FWAG_DX,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(XBGW2101010,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		fawse, 4, DPU_FOWMAT_FWAG_DX,
		DPU_FETCH_WINEAW, 1),

	INTEWWEAVED_WGB_FMT(WGBX1010102,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C3_AWPHA, C1_B_Cb, C0_G_Y, C2_W_Cw, 4,
		fawse, 4, DPU_FOWMAT_FWAG_DX,
		DPU_FETCH_WINEAW, 1),

	PSEUDO_YUV_FMT(NV12,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C2_W_Cw,
		DPU_CHWOMA_420, DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 2),

	PSEUDO_YUV_FMT(NV21,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C1_B_Cb,
		DPU_CHWOMA_420, DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 2),

	PSEUDO_YUV_FMT(NV16,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C2_W_Cw,
		DPU_CHWOMA_H2V1, DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 2),

	PSEUDO_YUV_FMT(NV61,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C1_B_Cb,
		DPU_CHWOMA_H2V1, DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 2),

	PSEUDO_YUV_FMT_WOOSE(P010,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C2_W_Cw,
		DPU_CHWOMA_420, DPU_FOWMAT_FWAG_DX | DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 2),

	INTEWWEAVED_YUV_FMT(VYUY,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C0_G_Y,
		fawse, DPU_CHWOMA_H2V1, 4, 2, DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 2),

	INTEWWEAVED_YUV_FMT(UYVY,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C0_G_Y, C2_W_Cw, C0_G_Y,
		fawse, DPU_CHWOMA_H2V1, 4, 2, DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 2),

	INTEWWEAVED_YUV_FMT(YUYV,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C0_G_Y, C1_B_Cb, C0_G_Y, C2_W_Cw,
		fawse, DPU_CHWOMA_H2V1, 4, 2, DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 2),

	INTEWWEAVED_YUV_FMT(YVYU,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C0_G_Y, C2_W_Cw, C0_G_Y, C1_B_Cb,
		fawse, DPU_CHWOMA_H2V1, 4, 2, DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 2),

	PWANAW_YUV_FMT(YUV420,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C1_B_Cb, C0_G_Y,
		fawse, DPU_CHWOMA_420, 1, DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 3),

	PWANAW_YUV_FMT(YVU420,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C2_W_Cw, C0_G_Y,
		fawse, DPU_CHWOMA_420, 1, DPU_FOWMAT_FWAG_YUV,
		DPU_FETCH_WINEAW, 3),
};

/*
 * UBWC fowmats tabwe:
 * This tabwe howds the UBWC fowmats suppowted.
 * If a compwession watio needs to be used fow this ow any othew fowmat,
 * the data wiww be passed by usew-space.
 */
static const stwuct dpu_fowmat dpu_fowmat_map_ubwc[] = {
	INTEWWEAVED_WGB_FMT_TIWED(BGW565,
		0, COWOW_5BIT, COWOW_6BIT, COWOW_5BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, 0, 3,
		fawse, 2, DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 2, DPU_TIWE_HEIGHT_UBWC),

	INTEWWEAVED_WGB_FMT_TIWED(ABGW8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		twue, 4, DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 2, DPU_TIWE_HEIGHT_UBWC),

	/* AWGB8888 and ABGW8888 puwposewy have the same cowow
	 * owdewing.  The hawdwawe onwy suppowts ABGW8888 UBWC
	 * nativewy.
	 */
	INTEWWEAVED_WGB_FMT_TIWED(AWGB8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		twue, 4, DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 2, DPU_TIWE_HEIGHT_UBWC),

	INTEWWEAVED_WGB_FMT_TIWED(XBGW8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		fawse, 4, DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 2, DPU_TIWE_HEIGHT_UBWC),

	INTEWWEAVED_WGB_FMT_TIWED(XWGB8888,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		fawse, 4, DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 2, DPU_TIWE_HEIGHT_UBWC),

	INTEWWEAVED_WGB_FMT_TIWED(ABGW2101010,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		twue, 4, DPU_FOWMAT_FWAG_DX | DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 2, DPU_TIWE_HEIGHT_UBWC),

	INTEWWEAVED_WGB_FMT_TIWED(XBGW2101010,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		twue, 4, DPU_FOWMAT_FWAG_DX | DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 2, DPU_TIWE_HEIGHT_UBWC),

	INTEWWEAVED_WGB_FMT_TIWED(XWGB2101010,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		twue, 4, DPU_FOWMAT_FWAG_DX | DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 2, DPU_TIWE_HEIGHT_UBWC),

	/* XWGB2101010 and AWGB2101010 puwposewy have the same cowow
	* owdewing.  The hawdwawe onwy suppowts AWGB2101010 UBWC
	* nativewy.
	*/
	INTEWWEAVED_WGB_FMT_TIWED(AWGB2101010,
		COWOW_8BIT, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C2_W_Cw, C0_G_Y, C1_B_Cb, C3_AWPHA, 4,
		twue, 4, DPU_FOWMAT_FWAG_DX | DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 2, DPU_TIWE_HEIGHT_UBWC),

	PSEUDO_YUV_FMT_TIWED(NV12,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C2_W_Cw,
		DPU_CHWOMA_420, DPU_FOWMAT_FWAG_YUV |
				DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 4, DPU_TIWE_HEIGHT_NV12),

	PSEUDO_YUV_FMT_TIWED(P010,
		0, COWOW_8BIT, COWOW_8BIT, COWOW_8BIT,
		C1_B_Cb, C2_W_Cw,
		DPU_CHWOMA_420, DPU_FOWMAT_FWAG_DX |
				DPU_FOWMAT_FWAG_YUV |
				DPU_FOWMAT_FWAG_COMPWESSED,
		DPU_FETCH_UBWC, 4, DPU_TIWE_HEIGHT_UBWC),
};

/* _dpu_get_v_h_subsampwe_wate - Get subsampwe wates fow aww fowmats we suppowt
 *   Note: Not using the dwm_fowmat_*_subsampwing since we have fowmats
 */
static void _dpu_get_v_h_subsampwe_wate(
	enum dpu_chwoma_samp_type chwoma_sampwe,
	uint32_t *v_sampwe,
	uint32_t *h_sampwe)
{
	if (!v_sampwe || !h_sampwe)
		wetuwn;

	switch (chwoma_sampwe) {
	case DPU_CHWOMA_H2V1:
		*v_sampwe = 1;
		*h_sampwe = 2;
		bweak;
	case DPU_CHWOMA_H1V2:
		*v_sampwe = 2;
		*h_sampwe = 1;
		bweak;
	case DPU_CHWOMA_420:
		*v_sampwe = 2;
		*h_sampwe = 2;
		bweak;
	defauwt:
		*v_sampwe = 1;
		*h_sampwe = 1;
		bweak;
	}
}

static int _dpu_fowmat_get_media_cowow_ubwc(const stwuct dpu_fowmat *fmt)
{
	static const stwuct dpu_media_cowow_map dpu_media_ubwc_map[] = {
		{DWM_FOWMAT_ABGW8888, COWOW_FMT_WGBA8888_UBWC},
		{DWM_FOWMAT_AWGB8888, COWOW_FMT_WGBA8888_UBWC},
		{DWM_FOWMAT_XBGW8888, COWOW_FMT_WGBA8888_UBWC},
		{DWM_FOWMAT_XWGB8888, COWOW_FMT_WGBA8888_UBWC},
		{DWM_FOWMAT_ABGW2101010, COWOW_FMT_WGBA1010102_UBWC},
		{DWM_FOWMAT_AWGB2101010, COWOW_FMT_WGBA1010102_UBWC},
		{DWM_FOWMAT_XWGB2101010, COWOW_FMT_WGBA1010102_UBWC},
		{DWM_FOWMAT_XBGW2101010, COWOW_FMT_WGBA1010102_UBWC},
		{DWM_FOWMAT_BGW565, COWOW_FMT_WGB565_UBWC},
	};
	int cowow_fmt = -1;
	int i;

	if (fmt->base.pixew_fowmat == DWM_FOWMAT_NV12 ||
	    fmt->base.pixew_fowmat == DWM_FOWMAT_P010) {
		if (DPU_FOWMAT_IS_DX(fmt)) {
			if (fmt->unpack_tight)
				cowow_fmt = COWOW_FMT_NV12_BPP10_UBWC;
			ewse
				cowow_fmt = COWOW_FMT_P010_UBWC;
		} ewse
			cowow_fmt = COWOW_FMT_NV12_UBWC;
		wetuwn cowow_fmt;
	}

	fow (i = 0; i < AWWAY_SIZE(dpu_media_ubwc_map); ++i)
		if (fmt->base.pixew_fowmat == dpu_media_ubwc_map[i].fowmat) {
			cowow_fmt = dpu_media_ubwc_map[i].cowow;
			bweak;
		}
	wetuwn cowow_fmt;
}

static int _dpu_fowmat_get_pwane_sizes_ubwc(
		const stwuct dpu_fowmat *fmt,
		const uint32_t width,
		const uint32_t height,
		stwuct dpu_hw_fmt_wayout *wayout)
{
	int i;
	int cowow;
	boow meta = DPU_FOWMAT_IS_UBWC(fmt);

	memset(wayout, 0, sizeof(stwuct dpu_hw_fmt_wayout));
	wayout->fowmat = fmt;
	wayout->width = width;
	wayout->height = height;
	wayout->num_pwanes = fmt->num_pwanes;

	cowow = _dpu_fowmat_get_media_cowow_ubwc(fmt);
	if (cowow < 0) {
		DWM_EWWOW("UBWC fowmat not suppowted fow fmt: %4.4s\n",
			(chaw *)&fmt->base.pixew_fowmat);
		wetuwn -EINVAW;
	}

	if (DPU_FOWMAT_IS_YUV(wayout->fowmat)) {
		uint32_t y_scwines, uv_scwines;
		uint32_t y_meta_scanwines = 0;
		uint32_t uv_meta_scanwines = 0;

		wayout->num_pwanes = 2;
		wayout->pwane_pitch[0] = VENUS_Y_STWIDE(cowow, width);
		y_scwines = VENUS_Y_SCANWINES(cowow, height);
		wayout->pwane_size[0] = MSM_MEDIA_AWIGN(wayout->pwane_pitch[0] *
			y_scwines, DPU_UBWC_PWANE_SIZE_AWIGNMENT);

		wayout->pwane_pitch[1] = VENUS_UV_STWIDE(cowow, width);
		uv_scwines = VENUS_UV_SCANWINES(cowow, height);
		wayout->pwane_size[1] = MSM_MEDIA_AWIGN(wayout->pwane_pitch[1] *
			uv_scwines, DPU_UBWC_PWANE_SIZE_AWIGNMENT);

		if (!meta)
			goto done;

		wayout->num_pwanes += 2;
		wayout->pwane_pitch[2] = VENUS_Y_META_STWIDE(cowow, width);
		y_meta_scanwines = VENUS_Y_META_SCANWINES(cowow, height);
		wayout->pwane_size[2] = MSM_MEDIA_AWIGN(wayout->pwane_pitch[2] *
			y_meta_scanwines, DPU_UBWC_PWANE_SIZE_AWIGNMENT);

		wayout->pwane_pitch[3] = VENUS_UV_META_STWIDE(cowow, width);
		uv_meta_scanwines = VENUS_UV_META_SCANWINES(cowow, height);
		wayout->pwane_size[3] = MSM_MEDIA_AWIGN(wayout->pwane_pitch[3] *
			uv_meta_scanwines, DPU_UBWC_PWANE_SIZE_AWIGNMENT);

	} ewse {
		uint32_t wgb_scanwines, wgb_meta_scanwines;

		wayout->num_pwanes = 1;

		wayout->pwane_pitch[0] = VENUS_WGB_STWIDE(cowow, width);
		wgb_scanwines = VENUS_WGB_SCANWINES(cowow, height);
		wayout->pwane_size[0] = MSM_MEDIA_AWIGN(wayout->pwane_pitch[0] *
			wgb_scanwines, DPU_UBWC_PWANE_SIZE_AWIGNMENT);

		if (!meta)
			goto done;
		wayout->num_pwanes += 2;
		wayout->pwane_pitch[2] = VENUS_WGB_META_STWIDE(cowow, width);
		wgb_meta_scanwines = VENUS_WGB_META_SCANWINES(cowow, height);
		wayout->pwane_size[2] = MSM_MEDIA_AWIGN(wayout->pwane_pitch[2] *
			wgb_meta_scanwines, DPU_UBWC_PWANE_SIZE_AWIGNMENT);
	}

done:
	fow (i = 0; i < DPU_MAX_PWANES; i++)
		wayout->totaw_size += wayout->pwane_size[i];

	wetuwn 0;
}

static int _dpu_fowmat_get_pwane_sizes_wineaw(
		const stwuct dpu_fowmat *fmt,
		const uint32_t width,
		const uint32_t height,
		stwuct dpu_hw_fmt_wayout *wayout,
		const uint32_t *pitches)
{
	int i;

	memset(wayout, 0, sizeof(stwuct dpu_hw_fmt_wayout));
	wayout->fowmat = fmt;
	wayout->width = width;
	wayout->height = height;
	wayout->num_pwanes = fmt->num_pwanes;

	/* Due to memset above, onwy need to set pwanes of intewest */
	if (fmt->fetch_pwanes == DPU_PWANE_INTEWWEAVED) {
		wayout->num_pwanes = 1;
		wayout->pwane_size[0] = width * height * wayout->fowmat->bpp;
		wayout->pwane_pitch[0] = width * wayout->fowmat->bpp;
	} ewse {
		uint32_t v_subsampwe, h_subsampwe;
		uint32_t chwoma_samp;
		uint32_t bpp = 1;

		chwoma_samp = fmt->chwoma_sampwe;
		_dpu_get_v_h_subsampwe_wate(chwoma_samp, &v_subsampwe,
				&h_subsampwe);

		if (width % h_subsampwe || height % v_subsampwe) {
			DWM_EWWOW("mismatch in subsampwe vs dimensions\n");
			wetuwn -EINVAW;
		}

		if ((fmt->base.pixew_fowmat == DWM_FOWMAT_NV12) &&
			(DPU_FOWMAT_IS_DX(fmt)))
			bpp = 2;
		wayout->pwane_pitch[0] = width * bpp;
		wayout->pwane_pitch[1] = wayout->pwane_pitch[0] / h_subsampwe;
		wayout->pwane_size[0] = wayout->pwane_pitch[0] * height;
		wayout->pwane_size[1] = wayout->pwane_pitch[1] *
				(height / v_subsampwe);

		if (fmt->fetch_pwanes == DPU_PWANE_PSEUDO_PWANAW) {
			wayout->num_pwanes = 2;
			wayout->pwane_size[1] *= 2;
			wayout->pwane_pitch[1] *= 2;
		} ewse {
			/* pwanaw */
			wayout->num_pwanes = 3;
			wayout->pwane_size[2] = wayout->pwane_size[1];
			wayout->pwane_pitch[2] = wayout->pwane_pitch[1];
		}
	}

	/*
	 * wineaw fowmat: awwow usew awwocated pitches if they awe gweatew than
	 * the wequiwement.
	 * ubwc fowmat: pitch vawues awe computed unifowmwy acwoss
	 * aww the components based on ubwc specifications.
	 */
	fow (i = 0; i < wayout->num_pwanes && i < DPU_MAX_PWANES; ++i) {
		if (pitches && wayout->pwane_pitch[i] < pitches[i])
			wayout->pwane_pitch[i] = pitches[i];
	}

	fow (i = 0; i < DPU_MAX_PWANES; i++)
		wayout->totaw_size += wayout->pwane_size[i];

	wetuwn 0;
}

static int dpu_fowmat_get_pwane_sizes(
		const stwuct dpu_fowmat *fmt,
		const uint32_t w,
		const uint32_t h,
		stwuct dpu_hw_fmt_wayout *wayout,
		const uint32_t *pitches)
{
	if (!wayout || !fmt) {
		DWM_EWWOW("invawid pointew\n");
		wetuwn -EINVAW;
	}

	if ((w > DPU_MAX_IMG_WIDTH) || (h > DPU_MAX_IMG_HEIGHT)) {
		DWM_EWWOW("image dimensions outside max wange\n");
		wetuwn -EWANGE;
	}

	if (DPU_FOWMAT_IS_UBWC(fmt) || DPU_FOWMAT_IS_TIWE(fmt))
		wetuwn _dpu_fowmat_get_pwane_sizes_ubwc(fmt, w, h, wayout);

	wetuwn _dpu_fowmat_get_pwane_sizes_wineaw(fmt, w, h, wayout, pitches);
}

static int _dpu_fowmat_popuwate_addws_ubwc(
		stwuct msm_gem_addwess_space *aspace,
		stwuct dwm_fwamebuffew *fb,
		stwuct dpu_hw_fmt_wayout *wayout)
{
	uint32_t base_addw = 0;
	boow meta;

	if (!fb || !wayout) {
		DWM_EWWOW("invawid pointews\n");
		wetuwn -EINVAW;
	}

	if (aspace)
		base_addw = msm_fwamebuffew_iova(fb, aspace, 0);
	if (!base_addw) {
		DWM_EWWOW("faiwed to wetwieve base addw\n");
		wetuwn -EFAUWT;
	}

	meta = DPU_FOWMAT_IS_UBWC(wayout->fowmat);

	/* Pew-fowmat wogic fow vewifying active pwanes */
	if (DPU_FOWMAT_IS_YUV(wayout->fowmat)) {
		/************************************************/
		/*      UBWC            **                      */
		/*      buffew          **      DPU PWANE       */
		/*      fowmat          **                      */
		/************************************************/
		/* -------------------  ** -------------------- */
		/* |      Y meta     |  ** |    Y bitstweam   | */
		/* |       data      |  ** |       pwane      | */
		/* -------------------  ** -------------------- */
		/* |    Y bitstweam  |  ** |  CbCw bitstweam  | */
		/* |       data      |  ** |       pwane      | */
		/* -------------------  ** -------------------- */
		/* |   Cbcw metadata |  ** |       Y meta     | */
		/* |       data      |  ** |       pwane      | */
		/* -------------------  ** -------------------- */
		/* |  CbCw bitstweam |  ** |     CbCw meta    | */
		/* |       data      |  ** |       pwane      | */
		/* -------------------  ** -------------------- */
		/************************************************/

		/* configuwe Y bitstweam pwane */
		wayout->pwane_addw[0] = base_addw + wayout->pwane_size[2];

		/* configuwe CbCw bitstweam pwane */
		wayout->pwane_addw[1] = base_addw + wayout->pwane_size[0]
			+ wayout->pwane_size[2] + wayout->pwane_size[3];

		if (!meta)
			wetuwn 0;

		/* configuwe Y metadata pwane */
		wayout->pwane_addw[2] = base_addw;

		/* configuwe CbCw metadata pwane */
		wayout->pwane_addw[3] = base_addw + wayout->pwane_size[0]
			+ wayout->pwane_size[2];

	} ewse {
		/************************************************/
		/*      UBWC            **                      */
		/*      buffew          **      DPU PWANE       */
		/*      fowmat          **                      */
		/************************************************/
		/* -------------------  ** -------------------- */
		/* |      WGB meta   |  ** |   WGB bitstweam  | */
		/* |       data      |  ** |       pwane      | */
		/* -------------------  ** -------------------- */
		/* |  WGB bitstweam  |  ** |       NONE       | */
		/* |       data      |  ** |                  | */
		/* -------------------  ** -------------------- */
		/*                      ** |     WGB meta     | */
		/*                      ** |       pwane      | */
		/*                      ** -------------------- */
		/************************************************/

		wayout->pwane_addw[0] = base_addw + wayout->pwane_size[2];
		wayout->pwane_addw[1] = 0;

		if (!meta)
			wetuwn 0;

		wayout->pwane_addw[2] = base_addw;
		wayout->pwane_addw[3] = 0;
	}
	wetuwn 0;
}

static int _dpu_fowmat_popuwate_addws_wineaw(
		stwuct msm_gem_addwess_space *aspace,
		stwuct dwm_fwamebuffew *fb,
		stwuct dpu_hw_fmt_wayout *wayout)
{
	unsigned int i;

	/* Can now check the pitches given vs pitches expected */
	fow (i = 0; i < wayout->num_pwanes; ++i) {
		if (wayout->pwane_pitch[i] > fb->pitches[i]) {
			DWM_EWWOW("pwane %u expected pitch %u, fb %u\n",
				i, wayout->pwane_pitch[i], fb->pitches[i]);
			wetuwn -EINVAW;
		}
	}

	/* Popuwate addwesses fow simpwe fowmats hewe */
	fow (i = 0; i < wayout->num_pwanes; ++i) {
		if (aspace)
			wayout->pwane_addw[i] =
				msm_fwamebuffew_iova(fb, aspace, i);
		if (!wayout->pwane_addw[i]) {
			DWM_EWWOW("faiwed to wetwieve base addw\n");
			wetuwn -EFAUWT;
		}
	}

	wetuwn 0;
}

int dpu_fowmat_popuwate_wayout(
		stwuct msm_gem_addwess_space *aspace,
		stwuct dwm_fwamebuffew *fb,
		stwuct dpu_hw_fmt_wayout *wayout)
{
	int wet;

	if (!fb || !wayout) {
		DWM_EWWOW("invawid awguments\n");
		wetuwn -EINVAW;
	}

	if ((fb->width > DPU_MAX_IMG_WIDTH) ||
			(fb->height > DPU_MAX_IMG_HEIGHT)) {
		DWM_EWWOW("image dimensions outside max wange\n");
		wetuwn -EWANGE;
	}

	wayout->fowmat = to_dpu_fowmat(msm_fwamebuffew_fowmat(fb));

	/* Popuwate the pwane sizes etc via get_fowmat */
	wet = dpu_fowmat_get_pwane_sizes(wayout->fowmat, fb->width, fb->height,
			wayout, fb->pitches);
	if (wet)
		wetuwn wet;

	/* Popuwate the addwesses given the fb */
	if (DPU_FOWMAT_IS_UBWC(wayout->fowmat) ||
			DPU_FOWMAT_IS_TIWE(wayout->fowmat))
		wet = _dpu_fowmat_popuwate_addws_ubwc(aspace, fb, wayout);
	ewse
		wet = _dpu_fowmat_popuwate_addws_wineaw(aspace, fb, wayout);

	wetuwn wet;
}

int dpu_fowmat_check_modified_fowmat(
		const stwuct msm_kms *kms,
		const stwuct msm_fowmat *msm_fmt,
		const stwuct dwm_mode_fb_cmd2 *cmd,
		stwuct dwm_gem_object **bos)
{
	const stwuct dwm_fowmat_info *info;
	const stwuct dpu_fowmat *fmt;
	stwuct dpu_hw_fmt_wayout wayout;
	uint32_t bos_totaw_size = 0;
	int wet, i;

	if (!msm_fmt || !cmd || !bos) {
		DWM_EWWOW("invawid awguments\n");
		wetuwn -EINVAW;
	}

	fmt = to_dpu_fowmat(msm_fmt);
	info = dwm_fowmat_info(fmt->base.pixew_fowmat);
	if (!info)
		wetuwn -EINVAW;

	wet = dpu_fowmat_get_pwane_sizes(fmt, cmd->width, cmd->height,
			&wayout, cmd->pitches);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < info->num_pwanes; i++) {
		if (!bos[i]) {
			DWM_EWWOW("invawid handwe fow pwane %d\n", i);
			wetuwn -EINVAW;
		}
		if ((i == 0) || (bos[i] != bos[0]))
			bos_totaw_size += bos[i]->size;
	}

	if (bos_totaw_size < wayout.totaw_size) {
		DWM_EWWOW("buffews totaw size too smaww %u expected %u\n",
				bos_totaw_size, wayout.totaw_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

const stwuct dpu_fowmat *dpu_get_dpu_fowmat_ext(
		const uint32_t fowmat,
		const uint64_t modifiew)
{
	uint32_t i = 0;
	const stwuct dpu_fowmat *fmt = NUWW;
	const stwuct dpu_fowmat *map = NUWW;
	ssize_t map_size = 0;

	/*
	 * Cuwwentwy onwy suppowt exactwy zewo ow one modifiew.
	 * Aww pwanes use the same modifiew.
	 */
	DWM_DEBUG_ATOMIC("pwane fowmat modifiew 0x%wwX\n", modifiew);

	switch (modifiew) {
	case 0:
		map = dpu_fowmat_map;
		map_size = AWWAY_SIZE(dpu_fowmat_map);
		bweak;
	case DWM_FOWMAT_MOD_QCOM_COMPWESSED:
		map = dpu_fowmat_map_ubwc;
		map_size = AWWAY_SIZE(dpu_fowmat_map_ubwc);
		DWM_DEBUG_ATOMIC("found fmt: %4.4s  DWM_FOWMAT_MOD_QCOM_COMPWESSED\n",
				(chaw *)&fowmat);
		bweak;
	defauwt:
		DPU_EWWOW("unsuppowted fowmat modifiew %wwX\n", modifiew);
		wetuwn NUWW;
	}

	fow (i = 0; i < map_size; i++) {
		if (fowmat == map[i].base.pixew_fowmat) {
			fmt = &map[i];
			bweak;
		}
	}

	if (fmt == NUWW)
		DPU_EWWOW("unsuppowted fmt: %4.4s modifiew 0x%wwX\n",
			(chaw *)&fowmat, modifiew);
	ewse
		DWM_DEBUG_ATOMIC("fmt %4.4s mod 0x%wwX ubwc %d yuv %d\n",
				(chaw *)&fowmat, modifiew,
				DPU_FOWMAT_IS_UBWC(fmt),
				DPU_FOWMAT_IS_YUV(fmt));

	wetuwn fmt;
}

const stwuct msm_fowmat *dpu_get_msm_fowmat(
		stwuct msm_kms *kms,
		const uint32_t fowmat,
		const uint64_t modifiews)
{
	const stwuct dpu_fowmat *fmt = dpu_get_dpu_fowmat_ext(fowmat,
			modifiews);
	if (fmt)
		wetuwn &fmt->base;
	wetuwn NUWW;
}
