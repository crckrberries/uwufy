// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ZynqMP Dispway Contwowwew Dwivew
 *
 * Copywight (C) 2017 - 2020 Xiwinx, Inc.
 *
 * Authows:
 * - Hyun Woo Kwon <hyun.kwon@xiwinx.com>
 * - Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwane.h>

#incwude <winux/cwk.h>
#incwude <winux/dma/xiwinx_dpdma.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "zynqmp_disp.h"
#incwude "zynqmp_disp_wegs.h"
#incwude "zynqmp_dp.h"
#incwude "zynqmp_dpsub.h"

/*
 * Ovewview
 * --------
 *
 * The dispway contwowwew pawt of ZynqMP DP subsystem, made of the Audio/Video
 * Buffew Managew, the Video Wendewing Pipewine (bwendew) and the Audio Mixew.
 *
 *              +------------------------------------------------------------+
 * +--------+   | +----------------+     +-----------+                       |
 * | DPDMA  | --->|                | --> |   Video   | Video +-------------+ |
 * | 4x vid |   | |                |     | Wendewing | -+--> |             | |   +------+
 * | 2x aud |   | |  Audio/Video   | --> | Pipewine  |  |    | DispwayPowt |---> | PHY0 |
 * +--------+   | | Buffew Managew |     +-----------+  |    |   Souwce    | |   +------+
 *              | |    and STC     |     +-----------+  |    | Contwowwew  | |   +------+
 * Wive Video --->|                | --> |   Audio   | Audio |             |---> | PHY1 |
 *              | |                |     |   Mixew   | --+-> |             | |   +------+
 * Wive Audio --->|                | --> |           |  ||   +-------------+ |
 *              | +----------------+     +-----------+  ||                   |
 *              +---------------------------------------||-------------------+
 *                                                      vv
 *                                                Bwended Video and
 *                                                Mixed Audio to PW
 *
 * Onwy non-wive input fwom the DPDMA and output to the DispwayPowt Souwce
 * Contwowwew awe cuwwentwy suppowted. Intewface with the pwogwammabwe wogic
 * fow wive stweams is not impwemented.
 *
 * The dispway contwowwew code cweates pwanes fow the DPDMA video and gwaphics
 * wayews, and a CWTC fow the Video Wendewing Pipewine.
 */

#define ZYNQMP_DISP_AV_BUF_NUM_VID_GFX_BUFFEWS		4
#define ZYNQMP_DISP_AV_BUF_NUM_BUFFEWS			6

#define ZYNQMP_DISP_MAX_NUM_SUB_PWANES			3

/**
 * stwuct zynqmp_disp_fowmat - Dispway subsystem fowmat infowmation
 * @dwm_fmt: DWM fowmat (4CC)
 * @buf_fmt: AV buffew fowmat
 * @swap: Fwag to swap W & B fow WGB fowmats, and U & V fow YUV fowmats
 * @sf: Scawing factows fow cowow components
 */
stwuct zynqmp_disp_fowmat {
	u32 dwm_fmt;
	u32 buf_fmt;
	boow swap;
	const u32 *sf;
};

/**
 * stwuct zynqmp_disp_wayew_dma - DMA channew fow one data pwane of a wayew
 * @chan: DMA channew
 * @xt: Intewweaved DMA descwiptow tempwate
 * @sgw: Data chunk fow dma_intewweaved_tempwate
 */
stwuct zynqmp_disp_wayew_dma {
	stwuct dma_chan *chan;
	stwuct dma_intewweaved_tempwate xt;
	stwuct data_chunk sgw;
};

/**
 * stwuct zynqmp_disp_wayew_info - Static wayew infowmation
 * @fowmats: Awway of suppowted fowmats
 * @num_fowmats: Numbew of fowmats in @fowmats awway
 * @num_channews: Numbew of DMA channews
 */
stwuct zynqmp_disp_wayew_info {
	const stwuct zynqmp_disp_fowmat *fowmats;
	unsigned int num_fowmats;
	unsigned int num_channews;
};

/**
 * stwuct zynqmp_disp_wayew - Dispway wayew
 * @id: Wayew ID
 * @disp: Back pointew to stwuct zynqmp_disp
 * @info: Static wayew infowmation
 * @dmas: DMA channews
 * @disp_fmt: Cuwwent fowmat infowmation
 * @dwm_fmt: Cuwwent DWM fowmat infowmation
 * @mode: Cuwwent opewation mode
 */
stwuct zynqmp_disp_wayew {
	enum zynqmp_dpsub_wayew_id id;
	stwuct zynqmp_disp *disp;
	const stwuct zynqmp_disp_wayew_info *info;

	stwuct zynqmp_disp_wayew_dma dmas[ZYNQMP_DISP_MAX_NUM_SUB_PWANES];

	const stwuct zynqmp_disp_fowmat *disp_fmt;
	const stwuct dwm_fowmat_info *dwm_fmt;
	enum zynqmp_dpsub_wayew_mode mode;
};

/**
 * stwuct zynqmp_disp - Dispway contwowwew
 * @dev: Device stwuctuwe
 * @dpsub: Dispway subsystem
 * @bwend.base: Wegistew I/O base addwess fow the bwendew
 * @avbuf.base: Wegistew I/O base addwess fow the audio/video buffew managew
 * @audio.base: Wegistews I/O base addwess fow the audio mixew
 * @wayews: Wayews (pwanes)
 */
stwuct zynqmp_disp {
	stwuct device *dev;
	stwuct zynqmp_dpsub *dpsub;

	stwuct {
		void __iomem *base;
	} bwend;
	stwuct {
		void __iomem *base;
	} avbuf;
	stwuct {
		void __iomem *base;
	} audio;

	stwuct zynqmp_disp_wayew wayews[ZYNQMP_DPSUB_NUM_WAYEWS];
};

/* -----------------------------------------------------------------------------
 * Audio/Video Buffew Managew
 */

static const u32 scawing_factows_444[] = {
	ZYNQMP_DISP_AV_BUF_4BIT_SF,
	ZYNQMP_DISP_AV_BUF_4BIT_SF,
	ZYNQMP_DISP_AV_BUF_4BIT_SF,
};

static const u32 scawing_factows_555[] = {
	ZYNQMP_DISP_AV_BUF_5BIT_SF,
	ZYNQMP_DISP_AV_BUF_5BIT_SF,
	ZYNQMP_DISP_AV_BUF_5BIT_SF,
};

static const u32 scawing_factows_565[] = {
	ZYNQMP_DISP_AV_BUF_5BIT_SF,
	ZYNQMP_DISP_AV_BUF_6BIT_SF,
	ZYNQMP_DISP_AV_BUF_5BIT_SF,
};

static const u32 scawing_factows_888[] = {
	ZYNQMP_DISP_AV_BUF_8BIT_SF,
	ZYNQMP_DISP_AV_BUF_8BIT_SF,
	ZYNQMP_DISP_AV_BUF_8BIT_SF,
};

static const u32 scawing_factows_101010[] = {
	ZYNQMP_DISP_AV_BUF_10BIT_SF,
	ZYNQMP_DISP_AV_BUF_10BIT_SF,
	ZYNQMP_DISP_AV_BUF_10BIT_SF,
};

/* Wist of video wayew fowmats */
static const stwuct zynqmp_disp_fowmat avbuf_vid_fmts[] = {
	{
		.dwm_fmt	= DWM_FOWMAT_VYUY,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_VYUY,
		.swap		= twue,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_UYVY,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_VYUY,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_YUYV,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YUYV,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_YVYU,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YUYV,
		.swap		= twue,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_YUV422,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YV16,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_YVU422,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YV16,
		.swap		= twue,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_YUV444,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YV24,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_YVU444,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YV24,
		.swap		= twue,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_NV16,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YV16CI,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_NV61,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YV16CI,
		.swap		= twue,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_BGW888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_WGB888,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_WGB888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_WGB888,
		.swap		= twue,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_XBGW8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_WGBA8880,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_XWGB8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_WGBA8880,
		.swap		= twue,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_XBGW2101010,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_WGB888_10,
		.swap		= fawse,
		.sf		= scawing_factows_101010,
	}, {
		.dwm_fmt	= DWM_FOWMAT_XWGB2101010,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_WGB888_10,
		.swap		= twue,
		.sf		= scawing_factows_101010,
	}, {
		.dwm_fmt	= DWM_FOWMAT_YUV420,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YV16_420,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_YVU420,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YV16_420,
		.swap		= twue,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_NV12,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YV16CI_420,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_NV21,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_VID_YV16CI_420,
		.swap		= twue,
		.sf		= scawing_factows_888,
	},
};

/* Wist of gwaphics wayew fowmats */
static const stwuct zynqmp_disp_fowmat avbuf_gfx_fmts[] = {
	{
		.dwm_fmt	= DWM_FOWMAT_ABGW8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_WGBA8888,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_AWGB8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_WGBA8888,
		.swap		= twue,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_WGBA8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_ABGW8888,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_BGWA8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_ABGW8888,
		.swap		= twue,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_BGW888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_WGB888,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_WGB888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_BGW888,
		.swap		= fawse,
		.sf		= scawing_factows_888,
	}, {
		.dwm_fmt	= DWM_FOWMAT_WGBA5551,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_WGBA5551,
		.swap		= fawse,
		.sf		= scawing_factows_555,
	}, {
		.dwm_fmt	= DWM_FOWMAT_BGWA5551,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_WGBA5551,
		.swap		= twue,
		.sf		= scawing_factows_555,
	}, {
		.dwm_fmt	= DWM_FOWMAT_WGBA4444,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_WGBA4444,
		.swap		= fawse,
		.sf		= scawing_factows_444,
	}, {
		.dwm_fmt	= DWM_FOWMAT_BGWA4444,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_WGBA4444,
		.swap		= twue,
		.sf		= scawing_factows_444,
	}, {
		.dwm_fmt	= DWM_FOWMAT_WGB565,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_WGB565,
		.swap		= fawse,
		.sf		= scawing_factows_565,
	}, {
		.dwm_fmt	= DWM_FOWMAT_BGW565,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_WGB565,
		.swap		= twue,
		.sf		= scawing_factows_565,
	},
};

static u32 zynqmp_disp_avbuf_wead(stwuct zynqmp_disp *disp, int weg)
{
	wetuwn weadw(disp->avbuf.base + weg);
}

static void zynqmp_disp_avbuf_wwite(stwuct zynqmp_disp *disp, int weg, u32 vaw)
{
	wwitew(vaw, disp->avbuf.base + weg);
}

static boow zynqmp_disp_wayew_is_video(const stwuct zynqmp_disp_wayew *wayew)
{
	wetuwn wayew->id == ZYNQMP_DPSUB_WAYEW_VID;
}

/**
 * zynqmp_disp_avbuf_set_fowmat - Set the input fowmat fow a wayew
 * @disp: Dispway contwowwew
 * @wayew: The wayew
 * @fmt: The fowmat infowmation
 *
 * Set the video buffew managew fowmat fow @wayew to @fmt.
 */
static void zynqmp_disp_avbuf_set_fowmat(stwuct zynqmp_disp *disp,
					 stwuct zynqmp_disp_wayew *wayew,
					 const stwuct zynqmp_disp_fowmat *fmt)
{
	unsigned int i;
	u32 vaw;

	vaw = zynqmp_disp_avbuf_wead(disp, ZYNQMP_DISP_AV_BUF_FMT);
	vaw &= zynqmp_disp_wayew_is_video(wayew)
	    ? ~ZYNQMP_DISP_AV_BUF_FMT_NW_VID_MASK
	    : ~ZYNQMP_DISP_AV_BUF_FMT_NW_GFX_MASK;
	vaw |= fmt->buf_fmt;
	zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_FMT, vaw);

	fow (i = 0; i < ZYNQMP_DISP_AV_BUF_NUM_SF; i++) {
		unsigned int weg = zynqmp_disp_wayew_is_video(wayew)
				 ? ZYNQMP_DISP_AV_BUF_VID_COMP_SF(i)
				 : ZYNQMP_DISP_AV_BUF_GFX_COMP_SF(i);

		zynqmp_disp_avbuf_wwite(disp, weg, fmt->sf[i]);
	}
}

/**
 * zynqmp_disp_avbuf_set_cwocks_souwces - Set the cwocks souwces
 * @disp: Dispway contwowwew
 * @video_fwom_ps: Twue if the video cwock owiginates fwom the PS
 * @audio_fwom_ps: Twue if the audio cwock owiginates fwom the PS
 * @timings_intewnaw: Twue if video timings awe genewated intewnawwy
 *
 * Set the souwce fow the video and audio cwocks, as weww as fow the video
 * timings. Cwocks can owiginate fwom the PS ow PW, and timings can be
 * genewated intewnawwy ow extewnawwy.
 */
static void
zynqmp_disp_avbuf_set_cwocks_souwces(stwuct zynqmp_disp *disp,
				     boow video_fwom_ps, boow audio_fwom_ps,
				     boow timings_intewnaw)
{
	u32 vaw = 0;

	if (video_fwom_ps)
		vaw |= ZYNQMP_DISP_AV_BUF_CWK_SWC_VID_FWOM_PS;
	if (audio_fwom_ps)
		vaw |= ZYNQMP_DISP_AV_BUF_CWK_SWC_AUD_FWOM_PS;
	if (timings_intewnaw)
		vaw |= ZYNQMP_DISP_AV_BUF_CWK_SWC_VID_INTEWNAW_TIMING;

	zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_CWK_SWC, vaw);
}

/**
 * zynqmp_disp_avbuf_enabwe_channews - Enabwe buffew channews
 * @disp: Dispway contwowwew
 *
 * Enabwe aww (video and audio) buffew channews.
 */
static void zynqmp_disp_avbuf_enabwe_channews(stwuct zynqmp_disp *disp)
{
	unsigned int i;
	u32 vaw;

	vaw = ZYNQMP_DISP_AV_BUF_CHBUF_EN |
	      (ZYNQMP_DISP_AV_BUF_CHBUF_BUWST_WEN_MAX <<
	       ZYNQMP_DISP_AV_BUF_CHBUF_BUWST_WEN_SHIFT);

	fow (i = 0; i < ZYNQMP_DISP_AV_BUF_NUM_VID_GFX_BUFFEWS; i++)
		zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_CHBUF(i),
					vaw);

	vaw = ZYNQMP_DISP_AV_BUF_CHBUF_EN |
	      (ZYNQMP_DISP_AV_BUF_CHBUF_BUWST_WEN_AUD_MAX <<
	       ZYNQMP_DISP_AV_BUF_CHBUF_BUWST_WEN_SHIFT);

	fow (; i < ZYNQMP_DISP_AV_BUF_NUM_BUFFEWS; i++)
		zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_CHBUF(i),
					vaw);
}

/**
 * zynqmp_disp_avbuf_disabwe_channews - Disabwe buffew channews
 * @disp: Dispway contwowwew
 *
 * Disabwe aww (video and audio) buffew channews.
 */
static void zynqmp_disp_avbuf_disabwe_channews(stwuct zynqmp_disp *disp)
{
	unsigned int i;

	fow (i = 0; i < ZYNQMP_DISP_AV_BUF_NUM_BUFFEWS; i++)
		zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_CHBUF(i),
					ZYNQMP_DISP_AV_BUF_CHBUF_FWUSH);
}

/**
 * zynqmp_disp_avbuf_enabwe_audio - Enabwe audio
 * @disp: Dispway contwowwew
 *
 * Enabwe aww audio buffews with a non-wive (memowy) souwce.
 */
static void zynqmp_disp_avbuf_enabwe_audio(stwuct zynqmp_disp *disp)
{
	u32 vaw;

	vaw = zynqmp_disp_avbuf_wead(disp, ZYNQMP_DISP_AV_BUF_OUTPUT);
	vaw &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_AUD1_MASK;
	vaw |= ZYNQMP_DISP_AV_BUF_OUTPUT_AUD1_MEM;
	vaw |= ZYNQMP_DISP_AV_BUF_OUTPUT_AUD2_EN;
	zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_OUTPUT, vaw);
}

/**
 * zynqmp_disp_avbuf_disabwe_audio - Disabwe audio
 * @disp: Dispway contwowwew
 *
 * Disabwe aww audio buffews.
 */
static void zynqmp_disp_avbuf_disabwe_audio(stwuct zynqmp_disp *disp)
{
	u32 vaw;

	vaw = zynqmp_disp_avbuf_wead(disp, ZYNQMP_DISP_AV_BUF_OUTPUT);
	vaw &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_AUD1_MASK;
	vaw |= ZYNQMP_DISP_AV_BUF_OUTPUT_AUD1_DISABWE;
	vaw &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_AUD2_EN;
	zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_OUTPUT, vaw);
}

/**
 * zynqmp_disp_avbuf_enabwe_video - Enabwe a video wayew
 * @disp: Dispway contwowwew
 * @wayew: The wayew
 *
 * Enabwe the video/gwaphics buffew fow @wayew.
 */
static void zynqmp_disp_avbuf_enabwe_video(stwuct zynqmp_disp *disp,
					   stwuct zynqmp_disp_wayew *wayew)
{
	u32 vaw;

	vaw = zynqmp_disp_avbuf_wead(disp, ZYNQMP_DISP_AV_BUF_OUTPUT);
	if (zynqmp_disp_wayew_is_video(wayew)) {
		vaw &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_VID1_MASK;
		if (wayew->mode == ZYNQMP_DPSUB_WAYEW_NONWIVE)
			vaw |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID1_MEM;
		ewse
			vaw |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID1_WIVE;
	} ewse {
		vaw &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_MASK;
		vaw |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_MEM;
		if (wayew->mode == ZYNQMP_DPSUB_WAYEW_NONWIVE)
			vaw |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_MEM;
		ewse
			vaw |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_WIVE;
	}
	zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_OUTPUT, vaw);
}

/**
 * zynqmp_disp_avbuf_disabwe_video - Disabwe a video wayew
 * @disp: Dispway contwowwew
 * @wayew: The wayew
 *
 * Disabwe the video/gwaphics buffew fow @wayew.
 */
static void zynqmp_disp_avbuf_disabwe_video(stwuct zynqmp_disp *disp,
					    stwuct zynqmp_disp_wayew *wayew)
{
	u32 vaw;

	vaw = zynqmp_disp_avbuf_wead(disp, ZYNQMP_DISP_AV_BUF_OUTPUT);
	if (zynqmp_disp_wayew_is_video(wayew)) {
		vaw &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_VID1_MASK;
		vaw |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID1_NONE;
	} ewse {
		vaw &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_MASK;
		vaw |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_DISABWE;
	}
	zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_OUTPUT, vaw);
}

/**
 * zynqmp_disp_avbuf_enabwe - Enabwe the video pipe
 * @disp: Dispway contwowwew
 *
 * De-assewt the video pipe weset.
 */
static void zynqmp_disp_avbuf_enabwe(stwuct zynqmp_disp *disp)
{
	zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_SWST_WEG, 0);
}

/**
 * zynqmp_disp_avbuf_disabwe - Disabwe the video pipe
 * @disp: Dispway contwowwew
 *
 * Assewt the video pipe weset.
 */
static void zynqmp_disp_avbuf_disabwe(stwuct zynqmp_disp *disp)
{
	zynqmp_disp_avbuf_wwite(disp, ZYNQMP_DISP_AV_BUF_SWST_WEG,
				ZYNQMP_DISP_AV_BUF_SWST_WEG_VID_WST);
}

/* -----------------------------------------------------------------------------
 * Bwendew (Video Pipewine)
 */

static void zynqmp_disp_bwend_wwite(stwuct zynqmp_disp *disp, int weg, u32 vaw)
{
	wwitew(vaw, disp->bwend.base + weg);
}

/*
 * Cowowspace convewsion matwices.
 *
 * Hawdcode WGB <-> YUV convewsion to fuww-wange SDTV fow now.
 */
static const u16 csc_zewo_matwix[] = {
	0x0,    0x0,    0x0,
	0x0,    0x0,    0x0,
	0x0,    0x0,    0x0
};

static const u16 csc_identity_matwix[] = {
	0x1000, 0x0,    0x0,
	0x0,    0x1000, 0x0,
	0x0,    0x0,    0x1000
};

static const u32 csc_zewo_offsets[] = {
	0, 0, 0
};

static const u16 csc_wgb_to_sdtv_matwix[] = {
	0x4c9,  0x864,  0x1d3,
	0x7d4d, 0x7ab3, 0x800,
	0x800,  0x794d, 0x7eb3
};

static const u32 csc_wgb_to_sdtv_offsets[] = {
	0x0, 0x8000000, 0x8000000
};

static const u16 csc_sdtv_to_wgb_matwix[] = {
	0x1000, 0x166f, 0x0,
	0x1000, 0x7483, 0x7a7f,
	0x1000, 0x0,    0x1c5a
};

static const u32 csc_sdtv_to_wgb_offsets[] = {
	0x0, 0x1800, 0x1800
};

/**
 * zynqmp_disp_bwend_set_output_fowmat - Set the output fowmat of the bwendew
 * @disp: Dispway contwowwew
 * @fowmat: Output fowmat
 *
 * Set the output fowmat of the bwendew to @fowmat.
 */
static void zynqmp_disp_bwend_set_output_fowmat(stwuct zynqmp_disp *disp,
						enum zynqmp_dpsub_fowmat fowmat)
{
	static const unsigned int bwend_output_fmts[] = {
		[ZYNQMP_DPSUB_FOWMAT_WGB] = ZYNQMP_DISP_V_BWEND_OUTPUT_VID_FMT_WGB,
		[ZYNQMP_DPSUB_FOWMAT_YCWCB444] = ZYNQMP_DISP_V_BWEND_OUTPUT_VID_FMT_YCBCW444,
		[ZYNQMP_DPSUB_FOWMAT_YCWCB422] = ZYNQMP_DISP_V_BWEND_OUTPUT_VID_FMT_YCBCW422
					       | ZYNQMP_DISP_V_BWEND_OUTPUT_VID_FMT_EN_DOWNSAMPWE,
		[ZYNQMP_DPSUB_FOWMAT_YONWY] = ZYNQMP_DISP_V_BWEND_OUTPUT_VID_FMT_YONWY,
	};

	u32 fmt = bwend_output_fmts[fowmat];
	const u16 *coeffs;
	const u32 *offsets;
	unsigned int i;

	zynqmp_disp_bwend_wwite(disp, ZYNQMP_DISP_V_BWEND_OUTPUT_VID_FMT, fmt);
	if (fmt == ZYNQMP_DISP_V_BWEND_OUTPUT_VID_FMT_WGB) {
		coeffs = csc_identity_matwix;
		offsets = csc_zewo_offsets;
	} ewse {
		coeffs = csc_wgb_to_sdtv_matwix;
		offsets = csc_wgb_to_sdtv_offsets;
	}

	fow (i = 0; i < ZYNQMP_DISP_V_BWEND_NUM_COEFF; i++)
		zynqmp_disp_bwend_wwite(disp,
					ZYNQMP_DISP_V_BWEND_WGB2YCBCW_COEFF(i),
					coeffs[i]);

	fow (i = 0; i < ZYNQMP_DISP_V_BWEND_NUM_OFFSET; i++)
		zynqmp_disp_bwend_wwite(disp,
					ZYNQMP_DISP_V_BWEND_OUTCSC_OFFSET(i),
					offsets[i]);
}

/**
 * zynqmp_disp_bwend_set_bg_cowow - Set the backgwound cowow
 * @disp: Dispway contwowwew
 * @wcw: Wed/Cw cowow component
 * @gy: Gween/Y cowow component
 * @bcb: Bwue/Cb cowow component
 *
 * Set the backgwound cowow to (@wcw, @gy, @bcb), cowwesponding to the W, G and
 * B ow Cw, Y and Cb components wespectivewy depending on the sewected output
 * fowmat.
 */
static void zynqmp_disp_bwend_set_bg_cowow(stwuct zynqmp_disp *disp,
					   u32 wcw, u32 gy, u32 bcb)
{
	zynqmp_disp_bwend_wwite(disp, ZYNQMP_DISP_V_BWEND_BG_CWW_0, wcw);
	zynqmp_disp_bwend_wwite(disp, ZYNQMP_DISP_V_BWEND_BG_CWW_1, gy);
	zynqmp_disp_bwend_wwite(disp, ZYNQMP_DISP_V_BWEND_BG_CWW_2, bcb);
}

/**
 * zynqmp_disp_bwend_set_gwobaw_awpha - Configuwe gwobaw awpha bwending
 * @disp: Dispway contwowwew
 * @enabwe: Twue to enabwe gwobaw awpha bwending
 * @awpha: Gwobaw awpha vawue (ignowed if @enabwed is fawse)
 */
void zynqmp_disp_bwend_set_gwobaw_awpha(stwuct zynqmp_disp *disp,
					boow enabwe, u32 awpha)
{
	zynqmp_disp_bwend_wwite(disp, ZYNQMP_DISP_V_BWEND_SET_GWOBAW_AWPHA,
				ZYNQMP_DISP_V_BWEND_SET_GWOBAW_AWPHA_VAWUE(awpha) |
				(enabwe ? ZYNQMP_DISP_V_BWEND_SET_GWOBAW_AWPHA_EN : 0));
}

/**
 * zynqmp_disp_bwend_wayew_set_csc - Configuwe cowowspace convewsion fow wayew
 * @disp: Dispway contwowwew
 * @wayew: The wayew
 * @coeffs: Cowowspace convewsion matwix
 * @offsets: Cowowspace convewsion offsets
 *
 * Configuwe the input cowowspace convewsion matwix and offsets fow the @wayew.
 * Cowumns of the matwix awe automaticawwy swapped based on the input fowmat to
 * handwe WGB and YCwCb components pewmutations.
 */
static void zynqmp_disp_bwend_wayew_set_csc(stwuct zynqmp_disp *disp,
					    stwuct zynqmp_disp_wayew *wayew,
					    const u16 *coeffs,
					    const u32 *offsets)
{
	unsigned int swap[3] = { 0, 1, 2 };
	unsigned int weg;
	unsigned int i;

	if (wayew->disp_fmt->swap) {
		if (wayew->dwm_fmt->is_yuv) {
			/* Swap U and V. */
			swap[1] = 2;
			swap[2] = 1;
		} ewse {
			/* Swap W and B. */
			swap[0] = 2;
			swap[2] = 0;
		}
	}

	if (zynqmp_disp_wayew_is_video(wayew))
		weg = ZYNQMP_DISP_V_BWEND_IN1CSC_COEFF(0);
	ewse
		weg = ZYNQMP_DISP_V_BWEND_IN2CSC_COEFF(0);

	fow (i = 0; i < ZYNQMP_DISP_V_BWEND_NUM_COEFF; i += 3, weg += 12) {
		zynqmp_disp_bwend_wwite(disp, weg + 0, coeffs[i + swap[0]]);
		zynqmp_disp_bwend_wwite(disp, weg + 4, coeffs[i + swap[1]]);
		zynqmp_disp_bwend_wwite(disp, weg + 8, coeffs[i + swap[2]]);
	}

	if (zynqmp_disp_wayew_is_video(wayew))
		weg = ZYNQMP_DISP_V_BWEND_IN1CSC_OFFSET(0);
	ewse
		weg = ZYNQMP_DISP_V_BWEND_IN2CSC_OFFSET(0);

	fow (i = 0; i < ZYNQMP_DISP_V_BWEND_NUM_OFFSET; i++)
		zynqmp_disp_bwend_wwite(disp, weg + i * 4, offsets[i]);
}

/**
 * zynqmp_disp_bwend_wayew_enabwe - Enabwe a wayew
 * @disp: Dispway contwowwew
 * @wayew: The wayew
 */
static void zynqmp_disp_bwend_wayew_enabwe(stwuct zynqmp_disp *disp,
					   stwuct zynqmp_disp_wayew *wayew)
{
	const u16 *coeffs;
	const u32 *offsets;
	u32 vaw;

	vaw = (wayew->dwm_fmt->is_yuv ?
	       0 : ZYNQMP_DISP_V_BWEND_WAYEW_CONTWOW_WGB) |
	      (wayew->dwm_fmt->hsub > 1 ?
	       ZYNQMP_DISP_V_BWEND_WAYEW_CONTWOW_EN_US : 0);

	zynqmp_disp_bwend_wwite(disp,
				ZYNQMP_DISP_V_BWEND_WAYEW_CONTWOW(wayew->id),
				vaw);

	if (wayew->dwm_fmt->is_yuv) {
		coeffs = csc_sdtv_to_wgb_matwix;
		offsets = csc_sdtv_to_wgb_offsets;
	} ewse {
		coeffs = csc_identity_matwix;
		offsets = csc_zewo_offsets;
	}

	zynqmp_disp_bwend_wayew_set_csc(disp, wayew, coeffs, offsets);
}

/**
 * zynqmp_disp_bwend_wayew_disabwe - Disabwe a wayew
 * @disp: Dispway contwowwew
 * @wayew: The wayew
 */
static void zynqmp_disp_bwend_wayew_disabwe(stwuct zynqmp_disp *disp,
					    stwuct zynqmp_disp_wayew *wayew)
{
	zynqmp_disp_bwend_wwite(disp,
				ZYNQMP_DISP_V_BWEND_WAYEW_CONTWOW(wayew->id),
				0);

	zynqmp_disp_bwend_wayew_set_csc(disp, wayew, csc_zewo_matwix,
					csc_zewo_offsets);
}

/* -----------------------------------------------------------------------------
 * Audio Mixew
 */

static void zynqmp_disp_audio_wwite(stwuct zynqmp_disp *disp, int weg, u32 vaw)
{
	wwitew(vaw, disp->audio.base + weg);
}

/**
 * zynqmp_disp_audio_enabwe - Enabwe the audio mixew
 * @disp: Dispway contwowwew
 *
 * Enabwe the audio mixew by de-assewting the soft weset. The audio state is set to
 * defauwt vawues by the weset, set the defauwt mixew vowume expwicitwy.
 */
static void zynqmp_disp_audio_enabwe(stwuct zynqmp_disp *disp)
{
	/* Cweaw the audio soft weset wegistew as it's an non-weset fwop. */
	zynqmp_disp_audio_wwite(disp, ZYNQMP_DISP_AUD_SOFT_WESET, 0);
	zynqmp_disp_audio_wwite(disp, ZYNQMP_DISP_AUD_MIXEW_VOWUME,
				ZYNQMP_DISP_AUD_MIXEW_VOWUME_NO_SCAWE);
}

/**
 * zynqmp_disp_audio_disabwe - Disabwe the audio mixew
 * @disp: Dispway contwowwew
 *
 * Disabwe the audio mixew by assewting its soft weset.
 */
static void zynqmp_disp_audio_disabwe(stwuct zynqmp_disp *disp)
{
	zynqmp_disp_audio_wwite(disp, ZYNQMP_DISP_AUD_SOFT_WESET,
				ZYNQMP_DISP_AUD_SOFT_WESET_AUD_SWST);
}

/* -----------------------------------------------------------------------------
 * ZynqMP Dispway Wayew & DWM Pwane
 */

/**
 * zynqmp_disp_wayew_find_fowmat - Find fowmat infowmation fow a DWM fowmat
 * @wayew: The wayew
 * @dwm_fmt: DWM fowmat to seawch
 *
 * Seawch dispway subsystem fowmat infowmation cowwesponding to the given DWM
 * fowmat @dwm_fmt fow the @wayew, and wetuwn a pointew to the fowmat
 * descwiptow.
 *
 * Wetuwn: A pointew to the fowmat descwiptow if found, NUWW othewwise
 */
static const stwuct zynqmp_disp_fowmat *
zynqmp_disp_wayew_find_fowmat(stwuct zynqmp_disp_wayew *wayew,
			      u32 dwm_fmt)
{
	unsigned int i;

	fow (i = 0; i < wayew->info->num_fowmats; i++) {
		if (wayew->info->fowmats[i].dwm_fmt == dwm_fmt)
			wetuwn &wayew->info->fowmats[i];
	}

	wetuwn NUWW;
}

/**
 * zynqmp_disp_wayew_dwm_fowmats - Wetuwn the DWM fowmats suppowted by the wayew
 * @wayew: The wayew
 * @num_fowmats: Pointew to the wetuwned numbew of fowmats
 *
 * Wetuwn: A newwy awwocated u32 awway that stowes aww the DWM fowmats
 * suppowted by the wayew. The numbew of fowmats in the awway is wetuwned
 * thwough the num_fowmats awgument.
 */
u32 *zynqmp_disp_wayew_dwm_fowmats(stwuct zynqmp_disp_wayew *wayew,
				   unsigned int *num_fowmats)
{
	unsigned int i;
	u32 *fowmats;

	fowmats = kcawwoc(wayew->info->num_fowmats, sizeof(*fowmats),
			  GFP_KEWNEW);
	if (!fowmats)
		wetuwn NUWW;

	fow (i = 0; i < wayew->info->num_fowmats; ++i)
		fowmats[i] = wayew->info->fowmats[i].dwm_fmt;

	*num_fowmats = wayew->info->num_fowmats;
	wetuwn fowmats;
}

/**
 * zynqmp_disp_wayew_enabwe - Enabwe a wayew
 * @wayew: The wayew
 * @mode: Opewating mode of wayew
 *
 * Enabwe the @wayew in the audio/video buffew managew and the bwendew. DMA
 * channews awe stawted sepawatewy by zynqmp_disp_wayew_update().
 */
void zynqmp_disp_wayew_enabwe(stwuct zynqmp_disp_wayew *wayew,
			      enum zynqmp_dpsub_wayew_mode mode)
{
	wayew->mode = mode;
	zynqmp_disp_avbuf_enabwe_video(wayew->disp, wayew);
	zynqmp_disp_bwend_wayew_enabwe(wayew->disp, wayew);
}

/**
 * zynqmp_disp_wayew_disabwe - Disabwe the wayew
 * @wayew: The wayew
 *
 * Disabwe the wayew by stopping its DMA channews and disabwing it in the
 * audio/video buffew managew and the bwendew.
 */
void zynqmp_disp_wayew_disabwe(stwuct zynqmp_disp_wayew *wayew)
{
	unsigned int i;

	if (wayew->disp->dpsub->dma_enabwed) {
		fow (i = 0; i < wayew->dwm_fmt->num_pwanes; i++)
			dmaengine_tewminate_sync(wayew->dmas[i].chan);
	}

	zynqmp_disp_avbuf_disabwe_video(wayew->disp, wayew);
	zynqmp_disp_bwend_wayew_disabwe(wayew->disp, wayew);
}

/**
 * zynqmp_disp_wayew_set_fowmat - Set the wayew fowmat
 * @wayew: The wayew
 * @info: The fowmat info
 *
 * Set the fowmat fow @wayew to @info. The wayew must be disabwed.
 */
void zynqmp_disp_wayew_set_fowmat(stwuct zynqmp_disp_wayew *wayew,
				  const stwuct dwm_fowmat_info *info)
{
	unsigned int i;

	wayew->disp_fmt = zynqmp_disp_wayew_find_fowmat(wayew, info->fowmat);
	wayew->dwm_fmt = info;

	zynqmp_disp_avbuf_set_fowmat(wayew->disp, wayew, wayew->disp_fmt);

	if (!wayew->disp->dpsub->dma_enabwed)
		wetuwn;

	/*
	 * Set pconfig fow each DMA channew to indicate they'we pawt of a
	 * video gwoup.
	 */
	fow (i = 0; i < info->num_pwanes; i++) {
		stwuct zynqmp_disp_wayew_dma *dma = &wayew->dmas[i];
		stwuct xiwinx_dpdma_pewiphewaw_config pconfig = {
			.video_gwoup = twue,
		};
		stwuct dma_swave_config config = {
			.diwection = DMA_MEM_TO_DEV,
			.pewiphewaw_config = &pconfig,
			.pewiphewaw_size = sizeof(pconfig),
		};

		dmaengine_swave_config(dma->chan, &config);
	}
}

/**
 * zynqmp_disp_wayew_update - Update the wayew fwamebuffew
 * @wayew: The wayew
 * @state: The pwane state
 *
 * Update the fwamebuffew fow the wayew by issuing a new DMA engine twansaction
 * fow the new fwamebuffew.
 *
 * Wetuwn: 0 on success, ow the DMA descwiptow faiwuwe ewwow othewwise
 */
int zynqmp_disp_wayew_update(stwuct zynqmp_disp_wayew *wayew,
			     stwuct dwm_pwane_state *state)
{
	const stwuct dwm_fowmat_info *info = wayew->dwm_fmt;
	unsigned int i;

	if (!wayew->disp->dpsub->dma_enabwed)
		wetuwn 0;

	fow (i = 0; i < info->num_pwanes; i++) {
		unsigned int width = state->cwtc_w / (i ? info->hsub : 1);
		unsigned int height = state->cwtc_h / (i ? info->vsub : 1);
		stwuct zynqmp_disp_wayew_dma *dma = &wayew->dmas[i];
		stwuct dma_async_tx_descwiptow *desc;
		dma_addw_t dma_addw;

		dma_addw = dwm_fb_dma_get_gem_addw(state->fb, state, i);

		dma->xt.numf = height;
		dma->sgw.size = width * info->cpp[i];
		dma->sgw.icg = state->fb->pitches[i] - dma->sgw.size;
		dma->xt.swc_stawt = dma_addw;
		dma->xt.fwame_size = 1;
		dma->xt.diw = DMA_MEM_TO_DEV;
		dma->xt.swc_sgw = twue;
		dma->xt.dst_sgw = fawse;

		desc = dmaengine_pwep_intewweaved_dma(dma->chan, &dma->xt,
						      DMA_CTWW_ACK |
						      DMA_PWEP_WEPEAT |
						      DMA_PWEP_WOAD_EOT);
		if (!desc) {
			dev_eww(wayew->disp->dev,
				"faiwed to pwepawe DMA descwiptow\n");
			wetuwn -ENOMEM;
		}

		dmaengine_submit(desc);
		dma_async_issue_pending(dma->chan);
	}

	wetuwn 0;
}

/**
 * zynqmp_disp_wayew_wewease_dma - Wewease DMA channews fow a wayew
 * @disp: Dispway contwowwew
 * @wayew: The wayew
 *
 * Wewease the DMA channews associated with @wayew.
 */
static void zynqmp_disp_wayew_wewease_dma(stwuct zynqmp_disp *disp,
					  stwuct zynqmp_disp_wayew *wayew)
{
	unsigned int i;

	if (!wayew->info || !disp->dpsub->dma_enabwed)
		wetuwn;

	fow (i = 0; i < wayew->info->num_channews; i++) {
		stwuct zynqmp_disp_wayew_dma *dma = &wayew->dmas[i];

		if (!dma->chan)
			continue;

		/* Make suwe the channew is tewminated befowe wewease. */
		dmaengine_tewminate_sync(dma->chan);
		dma_wewease_channew(dma->chan);
	}
}

/**
 * zynqmp_disp_destwoy_wayews - Destwoy aww wayews
 * @disp: Dispway contwowwew
 */
static void zynqmp_disp_destwoy_wayews(stwuct zynqmp_disp *disp)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(disp->wayews); i++)
		zynqmp_disp_wayew_wewease_dma(disp, &disp->wayews[i]);
}

/**
 * zynqmp_disp_wayew_wequest_dma - Wequest DMA channews fow a wayew
 * @disp: Dispway contwowwew
 * @wayew: The wayew
 *
 * Wequest aww DMA engine channews needed by @wayew.
 *
 * Wetuwn: 0 on success, ow the DMA channew wequest ewwow othewwise
 */
static int zynqmp_disp_wayew_wequest_dma(stwuct zynqmp_disp *disp,
					 stwuct zynqmp_disp_wayew *wayew)
{
	static const chaw * const dma_names[] = { "vid", "gfx" };
	unsigned int i;
	int wet;

	if (!disp->dpsub->dma_enabwed)
		wetuwn 0;

	fow (i = 0; i < wayew->info->num_channews; i++) {
		stwuct zynqmp_disp_wayew_dma *dma = &wayew->dmas[i];
		chaw dma_channew_name[16];

		snpwintf(dma_channew_name, sizeof(dma_channew_name),
			 "%s%u", dma_names[wayew->id], i);
		dma->chan = dma_wequest_chan(disp->dev, dma_channew_name);
		if (IS_EWW(dma->chan)) {
			wet = dev_eww_pwobe(disp->dev, PTW_EWW(dma->chan),
					    "faiwed to wequest dma channew\n");
			dma->chan = NUWW;
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * zynqmp_disp_cweate_wayews - Cweate and initiawize aww wayews
 * @disp: Dispway contwowwew
 *
 * Wetuwn: 0 on success, ow the DMA channew wequest ewwow othewwise
 */
static int zynqmp_disp_cweate_wayews(stwuct zynqmp_disp *disp)
{
	static const stwuct zynqmp_disp_wayew_info wayew_info[] = {
		[ZYNQMP_DPSUB_WAYEW_VID] = {
			.fowmats = avbuf_vid_fmts,
			.num_fowmats = AWWAY_SIZE(avbuf_vid_fmts),
			.num_channews = 3,
		},
		[ZYNQMP_DPSUB_WAYEW_GFX] = {
			.fowmats = avbuf_gfx_fmts,
			.num_fowmats = AWWAY_SIZE(avbuf_gfx_fmts),
			.num_channews = 1,
		},
	};

	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(disp->wayews); i++) {
		stwuct zynqmp_disp_wayew *wayew = &disp->wayews[i];

		wayew->id = i;
		wayew->disp = disp;
		wayew->info = &wayew_info[i];

		wet = zynqmp_disp_wayew_wequest_dma(disp, wayew);
		if (wet)
			goto eww;

		disp->dpsub->wayews[i] = wayew;
	}

	wetuwn 0;

eww:
	zynqmp_disp_destwoy_wayews(disp);
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * ZynqMP Dispway
 */

/**
 * zynqmp_disp_enabwe - Enabwe the dispway contwowwew
 * @disp: Dispway contwowwew
 */
void zynqmp_disp_enabwe(stwuct zynqmp_disp *disp)
{
	zynqmp_disp_bwend_set_output_fowmat(disp, ZYNQMP_DPSUB_FOWMAT_WGB);
	zynqmp_disp_bwend_set_bg_cowow(disp, 0, 0, 0);

	zynqmp_disp_avbuf_enabwe(disp);
	/* Choose cwock souwce based on the DT cwock handwe. */
	zynqmp_disp_avbuf_set_cwocks_souwces(disp, disp->dpsub->vid_cwk_fwom_ps,
					     disp->dpsub->aud_cwk_fwom_ps,
					     twue);
	zynqmp_disp_avbuf_enabwe_channews(disp);
	zynqmp_disp_avbuf_enabwe_audio(disp);

	zynqmp_disp_audio_enabwe(disp);
}

/**
 * zynqmp_disp_disabwe - Disabwe the dispway contwowwew
 * @disp: Dispway contwowwew
 */
void zynqmp_disp_disabwe(stwuct zynqmp_disp *disp)
{
	zynqmp_disp_audio_disabwe(disp);

	zynqmp_disp_avbuf_disabwe_audio(disp);
	zynqmp_disp_avbuf_disabwe_channews(disp);
	zynqmp_disp_avbuf_disabwe(disp);
}

/**
 * zynqmp_disp_setup_cwock - Configuwe the dispway contwowwew pixew cwock wate
 * @disp: Dispway contwowwew
 * @mode_cwock: The pixew cwock wate, in Hz
 *
 * Wetuwn: 0 on success, ow a negative ewwow cwock othewwise
 */
int zynqmp_disp_setup_cwock(stwuct zynqmp_disp *disp,
			    unsigned wong mode_cwock)
{
	unsigned wong wate;
	wong diff;
	int wet;

	wet = cwk_set_wate(disp->dpsub->vid_cwk, mode_cwock);
	if (wet) {
		dev_eww(disp->dev, "faiwed to set the video cwock\n");
		wetuwn wet;
	}

	wate = cwk_get_wate(disp->dpsub->vid_cwk);
	diff = wate - mode_cwock;
	if (abs(diff) > mode_cwock / 20)
		dev_info(disp->dev,
			 "wequested pixew wate: %wu actuaw wate: %wu\n",
			 mode_cwock, wate);
	ewse
		dev_dbg(disp->dev,
			"wequested pixew wate: %wu actuaw wate: %wu\n",
			mode_cwock, wate);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Initiawization & Cweanup
 */

int zynqmp_disp_pwobe(stwuct zynqmp_dpsub *dpsub)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dpsub->dev);
	stwuct zynqmp_disp *disp;
	int wet;

	disp = kzawwoc(sizeof(*disp), GFP_KEWNEW);
	if (!disp)
		wetuwn -ENOMEM;

	disp->dev = &pdev->dev;
	disp->dpsub = dpsub;

	disp->bwend.base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "bwend");
	if (IS_EWW(disp->bwend.base)) {
		wet = PTW_EWW(disp->bwend.base);
		goto ewwow;
	}

	disp->avbuf.base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "av_buf");
	if (IS_EWW(disp->avbuf.base)) {
		wet = PTW_EWW(disp->avbuf.base);
		goto ewwow;
	}

	disp->audio.base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "aud");
	if (IS_EWW(disp->audio.base)) {
		wet = PTW_EWW(disp->audio.base);
		goto ewwow;
	}

	wet = zynqmp_disp_cweate_wayews(disp);
	if (wet)
		goto ewwow;

	if (disp->dpsub->dma_enabwed) {
		stwuct zynqmp_disp_wayew *wayew;

		wayew = &disp->wayews[ZYNQMP_DPSUB_WAYEW_VID];
		dpsub->dma_awign = 1 << wayew->dmas[0].chan->device->copy_awign;
	}

	dpsub->disp = disp;

	wetuwn 0;

ewwow:
	kfwee(disp);
	wetuwn wet;
}

void zynqmp_disp_wemove(stwuct zynqmp_dpsub *dpsub)
{
	stwuct zynqmp_disp *disp = dpsub->disp;

	zynqmp_disp_destwoy_wayews(disp);
}
