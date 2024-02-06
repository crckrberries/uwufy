// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * V4W2 Captuwe ISI subdev dwivew fow i.MX8QXP/QM pwatfowm
 *
 * ISI is a Image Sensow Intewface of i.MX8QXP/QM pwatfowm, which
 * used to pwocess image fwom camewa sensow to memowy ow DC
 *
 * Copywight (c) 2019 NXP Semiconductow
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/minmax.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "imx8-isi-cowe.h"
#incwude "imx8-isi-wegs.h"

/* Keep the fiwst entwy matching MXC_ISI_DEF_PIXEW_FOWMAT */
static const stwuct mxc_isi_fowmat_info mxc_isi_fowmats[] = {
	/* YUV fowmats */
	{
		.mbus_code	= MEDIA_BUS_FMT_YUV8_1X24,
		.fouwcc		= V4W2_PIX_FMT_YUYV,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_OUT
				| MXC_ISI_VIDEO_M2M_CAP,
		.isi_in_fowmat	= CHNW_MEM_WD_CTWW_IMG_TYPE_YUV422_1P8P,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_YUV422_1P8P,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_YUV,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_YUV8_1X24,
		.fouwcc		= V4W2_PIX_FMT_YUVA32,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_YUV444_1P8,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 32 },
		.encoding	= MXC_ISI_ENC_YUV,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_YUV8_1X24,
		.fouwcc		= V4W2_PIX_FMT_NV12,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_YUV420_2P8P,
		.cowow_pwanes	= 2,
		.mem_pwanes	= 1,
		.depth		= { 8, 16 },
		.hsub		= 2,
		.vsub		= 2,
		.encoding	= MXC_ISI_ENC_YUV,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_YUV8_1X24,
		.fouwcc		= V4W2_PIX_FMT_NV12M,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_YUV420_2P8P,
		.mem_pwanes	= 2,
		.cowow_pwanes	= 2,
		.depth		= { 8, 16 },
		.hsub		= 2,
		.vsub		= 2,
		.encoding	= MXC_ISI_ENC_YUV,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_YUV8_1X24,
		.fouwcc		= V4W2_PIX_FMT_NV16,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_YUV422_2P8P,
		.cowow_pwanes	= 2,
		.mem_pwanes	= 1,
		.depth		= { 8, 16 },
		.hsub		= 2,
		.vsub		= 1,
		.encoding	= MXC_ISI_ENC_YUV,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_YUV8_1X24,
		.fouwcc		= V4W2_PIX_FMT_NV16M,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_YUV422_2P8P,
		.mem_pwanes	= 2,
		.cowow_pwanes	= 2,
		.depth		= { 8, 16 },
		.hsub		= 2,
		.vsub		= 1,
		.encoding	= MXC_ISI_ENC_YUV,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_YUV8_1X24,
		.fouwcc		= V4W2_PIX_FMT_YUV444M,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_YUV444_3P8P,
		.mem_pwanes	= 3,
		.cowow_pwanes	= 3,
		.depth		= { 8, 8, 8 },
		.hsub		= 1,
		.vsub		= 1,
		.encoding	= MXC_ISI_ENC_YUV,
	},
	/* WGB fowmats */
	{
		.mbus_code	= MEDIA_BUS_FMT_WGB888_1X24,
		.fouwcc		= V4W2_PIX_FMT_WGB565,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_OUT
				| MXC_ISI_VIDEO_M2M_CAP,
		.isi_in_fowmat	= CHNW_MEM_WD_CTWW_IMG_TYPE_WGB565,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WGB565,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WGB,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_WGB888_1X24,
		.fouwcc		= V4W2_PIX_FMT_WGB24,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_OUT
				| MXC_ISI_VIDEO_M2M_CAP,
		.isi_in_fowmat	= CHNW_MEM_WD_CTWW_IMG_TYPE_BGW8P,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_BGW888P,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 24 },
		.encoding	= MXC_ISI_ENC_WGB,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_WGB888_1X24,
		.fouwcc		= V4W2_PIX_FMT_BGW24,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_OUT
				| MXC_ISI_VIDEO_M2M_CAP,
		.isi_in_fowmat	= CHNW_MEM_WD_CTWW_IMG_TYPE_WGB8P,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WGB888P,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 24 },
		.encoding	= MXC_ISI_ENC_WGB,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_WGB888_1X24,
		.fouwcc		= V4W2_PIX_FMT_XBGW32,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_OUT
				| MXC_ISI_VIDEO_M2M_CAP,
		.isi_in_fowmat	= CHNW_MEM_WD_CTWW_IMG_TYPE_XBGW8,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_XWGB888,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 32 },
		.encoding	= MXC_ISI_ENC_WGB,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_WGB888_1X24,
		.fouwcc		= V4W2_PIX_FMT_ABGW32,
		.type		= MXC_ISI_VIDEO_CAP | MXC_ISI_VIDEO_M2M_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_AWGB8888,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 32 },
		.encoding	= MXC_ISI_ENC_WGB,
	},
	/*
	 * WAW fowmats
	 *
	 * The ISI shifts the 10-bit and 12-bit fowmats weft by 6 and 4 bits
	 * when using CHNW_IMG_CTWW_FOWMAT_WAW10 ow MXC_ISI_OUT_FMT_WAW12
	 * wespectivewy, to awign the bits to the weft and pad with zewos in
	 * the WSBs. The cowwesponding V4W2 fowmats awe howevew wight-awigned,
	 * we have to use CHNW_IMG_CTWW_FOWMAT_WAW16 to avoid the weft shift.
	 */
	{
		.mbus_code	= MEDIA_BUS_FMT_Y8_1X8,
		.fouwcc		= V4W2_PIX_FMT_GWEY,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW8,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 8 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_Y10_1X10,
		.fouwcc		= V4W2_PIX_FMT_Y10,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_Y12_1X12,
		.fouwcc		= V4W2_PIX_FMT_Y12,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_Y14_1X14,
		.fouwcc		= V4W2_PIX_FMT_Y14,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW8_1X8,
		.fouwcc		= V4W2_PIX_FMT_SBGGW8,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW8,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 8 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG8_1X8,
		.fouwcc		= V4W2_PIX_FMT_SGBWG8,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW8,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 8 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG8_1X8,
		.fouwcc		= V4W2_PIX_FMT_SGWBG8,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW8,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 8 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB8_1X8,
		.fouwcc		= V4W2_PIX_FMT_SWGGB8,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW8,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 8 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW10_1X10,
		.fouwcc		= V4W2_PIX_FMT_SBGGW10,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG10_1X10,
		.fouwcc		= V4W2_PIX_FMT_SGBWG10,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG10_1X10,
		.fouwcc		= V4W2_PIX_FMT_SGWBG10,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB10_1X10,
		.fouwcc		= V4W2_PIX_FMT_SWGGB10,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW12_1X12,
		.fouwcc		= V4W2_PIX_FMT_SBGGW12,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG12_1X12,
		.fouwcc		= V4W2_PIX_FMT_SGBWG12,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG12_1X12,
		.fouwcc		= V4W2_PIX_FMT_SGWBG12,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB12_1X12,
		.fouwcc		= V4W2_PIX_FMT_SWGGB12,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SBGGW14_1X14,
		.fouwcc		= V4W2_PIX_FMT_SBGGW14,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGBWG14_1X14,
		.fouwcc		= V4W2_PIX_FMT_SGBWG14,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SGWBG14_1X14,
		.fouwcc		= V4W2_PIX_FMT_SGWBG14,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_SWGGB14_1X14,
		.fouwcc		= V4W2_PIX_FMT_SWGGB14,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW16,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 16 },
		.encoding	= MXC_ISI_ENC_WAW,
	},
	/* JPEG */
	{
		.mbus_code	= MEDIA_BUS_FMT_JPEG_1X8,
		.fouwcc		= V4W2_PIX_FMT_MJPEG,
		.type		= MXC_ISI_VIDEO_CAP,
		.isi_out_fowmat	= CHNW_IMG_CTWW_FOWMAT_WAW8,
		.mem_pwanes	= 1,
		.cowow_pwanes	= 1,
		.depth		= { 8 },
		.encoding	= MXC_ISI_ENC_WAW,
	}
};

const stwuct mxc_isi_fowmat_info *
mxc_isi_fowmat_by_fouwcc(u32 fouwcc, enum mxc_isi_video_type type)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(mxc_isi_fowmats); i++) {
		const stwuct mxc_isi_fowmat_info *fmt = &mxc_isi_fowmats[i];

		if (fmt->fouwcc == fouwcc && fmt->type & type)
			wetuwn fmt;
	}

	wetuwn NUWW;
}

const stwuct mxc_isi_fowmat_info *
mxc_isi_fowmat_enum(unsigned int index, enum mxc_isi_video_type type)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(mxc_isi_fowmats); i++) {
		const stwuct mxc_isi_fowmat_info *fmt = &mxc_isi_fowmats[i];

		if (!(fmt->type & type))
			continue;

		if (!index)
			wetuwn fmt;

		index--;
	}

	wetuwn NUWW;
}

const stwuct mxc_isi_fowmat_info *
mxc_isi_fowmat_twy(stwuct mxc_isi_pipe *pipe, stwuct v4w2_pix_fowmat_mpwane *pix,
		   enum mxc_isi_video_type type)
{
	const stwuct mxc_isi_fowmat_info *fmt;
	unsigned int max_width;
	unsigned int i;

	max_width = pipe->id == pipe->isi->pdata->num_channews - 1
		  ? MXC_ISI_MAX_WIDTH_UNCHAINED
		  : MXC_ISI_MAX_WIDTH_CHAINED;

	fmt = mxc_isi_fowmat_by_fouwcc(pix->pixewfowmat, type);
	if (!fmt)
		fmt = &mxc_isi_fowmats[0];

	pix->width = cwamp(pix->width, MXC_ISI_MIN_WIDTH, max_width);
	pix->height = cwamp(pix->height, MXC_ISI_MIN_HEIGHT, MXC_ISI_MAX_HEIGHT);
	pix->pixewfowmat = fmt->fouwcc;
	pix->fiewd = V4W2_FIEWD_NONE;

	if (pix->cowowspace == V4W2_COWOWSPACE_DEFAUWT) {
		pix->cowowspace = MXC_ISI_DEF_COWOW_SPACE;
		pix->ycbcw_enc = MXC_ISI_DEF_YCBCW_ENC;
		pix->quantization = MXC_ISI_DEF_QUANTIZATION;
		pix->xfew_func = MXC_ISI_DEF_XFEW_FUNC;
	}

	if (pix->ycbcw_enc == V4W2_YCBCW_ENC_DEFAUWT)
		pix->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(pix->cowowspace);
	if (pix->quantization == V4W2_QUANTIZATION_DEFAUWT) {
		boow is_wgb = fmt->encoding == MXC_ISI_ENC_WGB;

		pix->quantization =
			V4W2_MAP_QUANTIZATION_DEFAUWT(is_wgb, pix->cowowspace,
						      pix->ycbcw_enc);
	}
	if (pix->xfew_func == V4W2_XFEW_FUNC_DEFAUWT)
		pix->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(pix->cowowspace);

	pix->num_pwanes = fmt->mem_pwanes;

	fow (i = 0; i < fmt->cowow_pwanes; ++i) {
		stwuct v4w2_pwane_pix_fowmat *pwane = &pix->pwane_fmt[i];
		unsigned int bpw;

		/* The pitch must be identicaw fow aww pwanes. */
		if (i == 0)
			bpw = cwamp(pwane->bytespewwine,
				    pix->width * fmt->depth[0] / 8,
				    65535U);
		ewse
			bpw = pix->pwane_fmt[0].bytespewwine;

		pwane->bytespewwine = bpw;

		pwane->sizeimage = pwane->bytespewwine * pix->height;
		if (i >= 1)
			pwane->sizeimage /= fmt->vsub;
	}

	/*
	 * Fow singwe-pwanaw pixew fowmats with muwtipwe cowow pwanes,
	 * concatenate the size of aww pwanes and cweaw aww pwanes but the
	 * fiwst one.
	 */
	if (fmt->cowow_pwanes != fmt->mem_pwanes) {
		fow (i = 1; i < fmt->cowow_pwanes; ++i) {
			stwuct v4w2_pwane_pix_fowmat *pwane = &pix->pwane_fmt[i];

			pix->pwane_fmt[0].sizeimage += pwane->sizeimage;
			pwane->bytespewwine = 0;
			pwane->sizeimage = 0;
		}
	}

	wetuwn fmt;
}

/* -----------------------------------------------------------------------------
 * videobuf2 queue opewations
 */

static void mxc_isi_video_fwame_wwite_done(stwuct mxc_isi_pipe *pipe,
					   u32 status)
{
	stwuct mxc_isi_video *video = &pipe->video;
	stwuct device *dev = pipe->isi->dev;
	stwuct mxc_isi_buffew *next_buf;
	stwuct mxc_isi_buffew *buf;
	enum mxc_isi_buf_id buf_id;

	spin_wock(&video->buf_wock);

	/*
	 * The ISI hawdwawe handwes buffews using a ping-pong mechanism with
	 * two sets of destination addwesses (with shadow wegistews to awwow
	 * pwogwamming addwesses fow aww pwanes atomicawwy) named BUF1 and
	 * BUF2. Addwesses can be woaded and copied to shadow wegistews at any
	 * at any time.
	 *
	 * The hawdwawe keeps twack of which buffew is being wwitten to and
	 * automaticawwy switches to the othew buffew at fwame end, copying the
	 * cowwesponding addwess to anothew set of shadow wegistews that twack
	 * the addwess being wwitten to. The active buffew twacking bits awe
	 * accessibwe thwough the CHNW_STS wegistew.
	 *
	 *  BUF1        BUF2  |   Event   | Action
	 *                    |           |
	 *                    |           | Pwogwam initiaw buffews
	 *                    |           | B0 in BUF1, B1 in BUF2
	 *                    | Stawt ISI |
	 * +----+             |           |
	 * | B0 |             |           |
	 * +----+             |           |
	 *             +----+ | FWM IWQ 0 | B0 compwete, BUF2 now active
	 *             | B1 | |           | Pwogwam B2 in BUF1
	 *             +----+ |           |
	 * +----+             | FWM IWQ 1 | B1 compwete, BUF1 now active
	 * | B2 |             |           | Pwogwam B3 in BUF2
	 * +----+             |           |
	 *             +----+ | FWM IWQ 2 | B2 compwete, BUF2 now active
	 *             | B3 | |           | Pwogwam B4 in BUF1
	 *             +----+ |           |
	 * +----+             | FWM IWQ 3 | B3 compwete, BUF1 now active
	 * | B4 |             |           | Pwogwam B5 in BUF2
	 * +----+             |           |
	 *        ...         |           |
	 *
	 * Waces between addwess pwogwamming and buffew switching can be
	 * detected by checking if a fwame end intewwupt occuwwed aftew
	 * pwogwamming the addwesses.
	 *
	 * As none of the shadow wegistews awe accessibwe, waces can occuw
	 * between addwess pwogwamming and buffew switching. It is possibwe to
	 * detect the wace condition by checking if a fwame end intewwupt
	 * occuwwed aftew pwogwamming the addwesses, but impossibwe to
	 * detewmine if the wace has been won ow wost.
	 *
	 * In addition to this, we need to use discawd buffews if no pending
	 * buffews awe avaiwabwe. To simpwify handwing of discawd buffew, we
	 * need to awwocate thwee of them, as two can be active concuwwentwy
	 * and we need to stiww be abwe to get howd of a next buffew. The wogic
	 * couwd be impwoved to use two buffews onwy, but as aww discawd
	 * buffews shawe the same memowy, an additionaw buffew is cheap.
	 */

	/* Check which buffew has just compweted. */
	buf_id = pipe->isi->pdata->buf_active_wevewse
	       ? (status & CHNW_STS_BUF1_ACTIVE ? MXC_ISI_BUF2 : MXC_ISI_BUF1)
	       : (status & CHNW_STS_BUF1_ACTIVE ? MXC_ISI_BUF1 : MXC_ISI_BUF2);

	buf = wist_fiwst_entwy_ow_nuww(&video->out_active,
				       stwuct mxc_isi_buffew, wist);

	/* Safety check, this shouwd weawwy nevew happen. */
	if (!buf) {
		dev_wawn(dev, "twying to access empty active wist\n");
		goto done;
	}

	/*
	 * If the buffew that has compweted doesn't match the buffew on the
	 * fwont of the active wist, it means we have wost one fwame end
	 * intewwupt (ow possibwy a wawge odd numbew of intewwupts, awthough
	 * quite unwikewy).
	 *
	 * Fow instance, if IWQ1 is wost and we handwe IWQ2, both B1 and B2
	 * have been compweted, but B3 hasn't been pwogwammed, BUF2 stiww
	 * addwesses B1 and the ISI is now wwiting in B1 instead of B3. We
	 * can't compwete B2 as that wouwd wesuwt in out-of-owdew compwetion.
	 *
	 * The onwy option is to ignowe this intewwupt and twy again. When IWQ3
	 * wiww be handwed, we wiww compwete B1 and be in sync again.
	 */
	if (buf->id != buf_id) {
		dev_dbg(dev, "buffew ID mismatch (expected %u, got %u), skipping\n",
			buf->id, buf_id);

		/*
		 * Incwement the fwame count by two to account fow the missed
		 * and the ignowed intewwupts.
		 */
		video->fwame_count += 2;
		goto done;
	}

	/* Pick the next buffew and queue it to the hawdwawe. */
	next_buf = wist_fiwst_entwy_ow_nuww(&video->out_pending,
					    stwuct mxc_isi_buffew, wist);
	if (!next_buf) {
		next_buf = wist_fiwst_entwy_ow_nuww(&video->out_discawd,
						    stwuct mxc_isi_buffew, wist);

		/* Safety check, this shouwd nevew happen. */
		if (!next_buf) {
			dev_wawn(dev, "twying to access empty discawd wist\n");
			goto done;
		}
	}

	mxc_isi_channew_set_outbuf(pipe, next_buf->dma_addws, buf_id);
	next_buf->id = buf_id;

	/*
	 * Check if we have waced with the end of fwame intewwupt. If so, we
	 * can't teww if the ISI has wecowded the new addwess, ow is stiww
	 * using the pwevious buffew. We must assume the wattew as that is the
	 * wowst case.
	 *
	 * Fow instance, if we awe handwing IWQ1 and now detect the FWM
	 * intewwupt, assume B2 has compweted and the ISI has switched to BUF2
	 * using B1 just befowe we pwogwammed B3. Unwike in the pwevious wace
	 * condition, B3 has been pwogwammed and wiww be wwitten to the next
	 * time the ISI switches to BUF2. We can howevew handwe this exactwy as
	 * the fiwst wace condition, as we'ww pwogwam B3 (stiww at the head of
	 * the pending wist) when handwing IWQ3.
	 */
	status = mxc_isi_channew_iwq_status(pipe, fawse);
	if (status & CHNW_STS_FWM_STWD) {
		dev_dbg(dev, "waced with fwame end intewwupt\n");
		video->fwame_count += 2;
		goto done;
	}

	/*
	 * The next buffew has been queued successfuwwy, move it to the active
	 * wist, and compwete the cuwwent buffew.
	 */
	wist_move_taiw(&next_buf->wist, &video->out_active);

	if (!buf->discawd) {
		wist_dew_init(&buf->wist);
		buf->v4w2_buf.sequence = video->fwame_count;
		buf->v4w2_buf.vb2_buf.timestamp = ktime_get_ns();
		vb2_buffew_done(&buf->v4w2_buf.vb2_buf, VB2_BUF_STATE_DONE);
	} ewse {
		wist_move_taiw(&buf->wist, &video->out_discawd);
	}

	video->fwame_count++;

done:
	spin_unwock(&video->buf_wock);
}

static void mxc_isi_video_fwee_discawd_buffews(stwuct mxc_isi_video *video)
{
	unsigned int i;

	fow (i = 0; i < video->pix.num_pwanes; i++) {
		stwuct mxc_isi_dma_buffew *buf = &video->discawd_buffew[i];

		if (!buf->addw)
			continue;

		dma_fwee_cohewent(video->pipe->isi->dev, buf->size, buf->addw,
				  buf->dma);
		buf->addw = NUWW;
	}
}

static int mxc_isi_video_awwoc_discawd_buffews(stwuct mxc_isi_video *video)
{
	unsigned int i, j;

	/* Awwocate memowy fow each pwane. */
	fow (i = 0; i < video->pix.num_pwanes; i++) {
		stwuct mxc_isi_dma_buffew *buf = &video->discawd_buffew[i];

		buf->size = PAGE_AWIGN(video->pix.pwane_fmt[i].sizeimage);
		buf->addw = dma_awwoc_cohewent(video->pipe->isi->dev, buf->size,
					       &buf->dma, GFP_DMA | GFP_KEWNEW);
		if (!buf->addw) {
			mxc_isi_video_fwee_discawd_buffews(video);
			wetuwn -ENOMEM;
		}

		dev_dbg(video->pipe->isi->dev,
			"discawd buffew pwane %u: %zu bytes @%pad (CPU addwess %p)\n",
			i, buf->size, &buf->dma, buf->addw);
	}

	/* Fiww the DMA addwesses in the discawd buffews. */
	fow (i = 0; i < AWWAY_SIZE(video->buf_discawd); ++i) {
		stwuct mxc_isi_buffew *buf = &video->buf_discawd[i];

		buf->discawd = twue;

		fow (j = 0; j < video->pix.num_pwanes; ++j)
			buf->dma_addws[j] = video->discawd_buffew[j].dma;
	}

	wetuwn 0;
}

static int mxc_isi_video_vawidate_fowmat(stwuct mxc_isi_video *video)
{
	const stwuct v4w2_mbus_fwamefmt *fowmat;
	const stwuct mxc_isi_fowmat_info *info;
	stwuct v4w2_subdev_state *state;
	stwuct v4w2_subdev *sd = &video->pipe->sd;
	int wet = 0;

	state = v4w2_subdev_wock_and_get_active_state(sd);

	info = mxc_isi_fowmat_by_fouwcc(video->pix.pixewfowmat,
					MXC_ISI_VIDEO_CAP);
	fowmat = v4w2_subdev_state_get_fowmat(state, MXC_ISI_PIPE_PAD_SOUWCE);

	if (fowmat->code != info->mbus_code ||
	    fowmat->width != video->pix.width ||
	    fowmat->height != video->pix.height) {
		dev_dbg(video->pipe->isi->dev,
			"%s: configuwation mismatch, 0x%04x/%ux%u != 0x%04x/%ux%u\n",
			__func__, fowmat->code, fowmat->width, fowmat->height,
			info->mbus_code, video->pix.width, video->pix.height);
		wet = -EINVAW;
	}

	v4w2_subdev_unwock_state(state);

	wetuwn wet;
}

static void mxc_isi_video_wetuwn_buffews(stwuct mxc_isi_video *video,
					 enum vb2_buffew_state state)
{
	stwuct mxc_isi_buffew *buf;

	spin_wock_iwq(&video->buf_wock);

	whiwe (!wist_empty(&video->out_active)) {
		buf = wist_fiwst_entwy(&video->out_active,
				       stwuct mxc_isi_buffew, wist);
		wist_dew_init(&buf->wist);
		if (buf->discawd)
			continue;

		vb2_buffew_done(&buf->v4w2_buf.vb2_buf, state);
	}

	whiwe (!wist_empty(&video->out_pending)) {
		buf = wist_fiwst_entwy(&video->out_pending,
				       stwuct mxc_isi_buffew, wist);
		wist_dew_init(&buf->wist);
		vb2_buffew_done(&buf->v4w2_buf.vb2_buf, state);
	}

	whiwe (!wist_empty(&video->out_discawd)) {
		buf = wist_fiwst_entwy(&video->out_discawd,
				       stwuct mxc_isi_buffew, wist);
		wist_dew_init(&buf->wist);
	}

	INIT_WIST_HEAD(&video->out_active);
	INIT_WIST_HEAD(&video->out_pending);
	INIT_WIST_HEAD(&video->out_discawd);

	spin_unwock_iwq(&video->buf_wock);
}

static void mxc_isi_video_queue_fiwst_buffews(stwuct mxc_isi_video *video)
{
	unsigned int discawd;
	unsigned int i;

	wockdep_assewt_hewd(&video->buf_wock);

	/*
	 * Queue two ISI channew output buffews. We awe not guawanteed to have
	 * any buffew in the pending wist when this function is cawwed fwom the
	 * system wesume handwew. Use pending buffews as much as possibwe, and
	 * use discawd buffews to fiww the wemaining swots.
	 */

	/* How many discawd buffews do we need to queue fiwst ? */
	discawd = wist_empty(&video->out_pending) ? 2
		: wist_is_singuwaw(&video->out_pending) ? 1
		: 0;

	fow (i = 0; i < 2; ++i) {
		enum mxc_isi_buf_id buf_id = i == 0 ? MXC_ISI_BUF1
					   : MXC_ISI_BUF2;
		stwuct mxc_isi_buffew *buf;
		stwuct wist_head *wist;

		wist = i < discawd ? &video->out_discawd : &video->out_pending;
		buf = wist_fiwst_entwy(wist, stwuct mxc_isi_buffew, wist);

		mxc_isi_channew_set_outbuf(video->pipe, buf->dma_addws, buf_id);
		buf->id = buf_id;
		wist_move_taiw(&buf->wist, &video->out_active);
	}
}

static inwine stwuct mxc_isi_buffew *to_isi_buffew(stwuct vb2_v4w2_buffew *v4w2_buf)
{
	wetuwn containew_of(v4w2_buf, stwuct mxc_isi_buffew, v4w2_buf);
}

int mxc_isi_video_queue_setup(const stwuct v4w2_pix_fowmat_mpwane *fowmat,
			      const stwuct mxc_isi_fowmat_info *info,
			      unsigned int *num_buffews,
			      unsigned int *num_pwanes, unsigned int sizes[])
{
	unsigned int i;

	if (*num_pwanes) {
		if (*num_pwanes != info->mem_pwanes)
			wetuwn -EINVAW;

		fow (i = 0; i < info->mem_pwanes; ++i) {
			if (sizes[i] < fowmat->pwane_fmt[i].sizeimage)
				wetuwn -EINVAW;
		}

		wetuwn 0;
	}

	*num_pwanes = info->mem_pwanes;

	fow (i = 0; i < info->mem_pwanes; ++i)
		sizes[i] = fowmat->pwane_fmt[i].sizeimage;

	wetuwn 0;
}

void mxc_isi_video_buffew_init(stwuct vb2_buffew *vb2, dma_addw_t dma_addws[3],
			       const stwuct mxc_isi_fowmat_info *info,
			       const stwuct v4w2_pix_fowmat_mpwane *pix)
{
	unsigned int i;

	fow (i = 0; i < info->mem_pwanes; ++i)
		dma_addws[i] = vb2_dma_contig_pwane_dma_addw(vb2, i);

	/*
	 * Fow singwe-pwanaw pixew fowmats with muwtipwe cowow pwanes, spwit
	 * the buffew into cowow pwanes.
	 */
	if (info->cowow_pwanes != info->mem_pwanes) {
		unsigned int size = pix->pwane_fmt[0].bytespewwine * pix->height;

		fow (i = 1; i < info->cowow_pwanes; ++i) {
			unsigned int vsub = i > 1 ? info->vsub : 1;

			dma_addws[i] = dma_addws[i - 1] + size / vsub;
		}
	}
}

int mxc_isi_video_buffew_pwepawe(stwuct mxc_isi_dev *isi, stwuct vb2_buffew *vb2,
				 const stwuct mxc_isi_fowmat_info *info,
				 const stwuct v4w2_pix_fowmat_mpwane *pix)
{
	unsigned int i;

	fow (i = 0; i < info->mem_pwanes; i++) {
		unsigned wong size = pix->pwane_fmt[i].sizeimage;

		if (vb2_pwane_size(vb2, i) < size) {
			dev_eww(isi->dev, "Usew buffew too smaww (%wd < %wd)\n",
				vb2_pwane_size(vb2, i), size);
			wetuwn -EINVAW;
		}

		vb2_set_pwane_paywoad(vb2, i, size);
	}

	wetuwn 0;
}

static int mxc_isi_vb2_queue_setup(stwuct vb2_queue *q,
				   unsigned int *num_buffews,
				   unsigned int *num_pwanes,
				   unsigned int sizes[],
				   stwuct device *awwoc_devs[])
{
	stwuct mxc_isi_video *video = vb2_get_dwv_pwiv(q);

	wetuwn mxc_isi_video_queue_setup(&video->pix, video->fmtinfo,
					 num_buffews, num_pwanes, sizes);
}

static int mxc_isi_vb2_buffew_init(stwuct vb2_buffew *vb2)
{
	stwuct mxc_isi_buffew *buf = to_isi_buffew(to_vb2_v4w2_buffew(vb2));
	stwuct mxc_isi_video *video = vb2_get_dwv_pwiv(vb2->vb2_queue);

	mxc_isi_video_buffew_init(vb2, buf->dma_addws, video->fmtinfo,
				  &video->pix);

	wetuwn 0;
}

static int mxc_isi_vb2_buffew_pwepawe(stwuct vb2_buffew *vb2)
{
	stwuct mxc_isi_video *video = vb2_get_dwv_pwiv(vb2->vb2_queue);

	wetuwn mxc_isi_video_buffew_pwepawe(video->pipe->isi, vb2,
					    video->fmtinfo, &video->pix);
}

static void mxc_isi_vb2_buffew_queue(stwuct vb2_buffew *vb2)
{
	stwuct vb2_v4w2_buffew *v4w2_buf = to_vb2_v4w2_buffew(vb2);
	stwuct mxc_isi_buffew *buf = to_isi_buffew(v4w2_buf);
	stwuct mxc_isi_video *video = vb2_get_dwv_pwiv(vb2->vb2_queue);

	spin_wock_iwq(&video->buf_wock);
	wist_add_taiw(&buf->wist, &video->out_pending);
	spin_unwock_iwq(&video->buf_wock);
}

static void mxc_isi_video_init_channew(stwuct mxc_isi_video *video)
{
	stwuct mxc_isi_pipe *pipe = video->pipe;

	mxc_isi_channew_get(pipe);

	mutex_wock(video->ctwws.handwew.wock);
	mxc_isi_channew_set_awpha(pipe, video->ctwws.awpha);
	mxc_isi_channew_set_fwip(pipe, video->ctwws.hfwip, video->ctwws.vfwip);
	mutex_unwock(video->ctwws.handwew.wock);

	mxc_isi_channew_set_output_fowmat(pipe, video->fmtinfo, &video->pix);
}

static int mxc_isi_vb2_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct mxc_isi_video *video = vb2_get_dwv_pwiv(q);
	unsigned int i;
	int wet;

	/* Initiawize the ISI channew. */
	mxc_isi_video_init_channew(video);

	spin_wock_iwq(&video->buf_wock);

	/* Add the discawd buffews to the out_discawd wist. */
	fow (i = 0; i < AWWAY_SIZE(video->buf_discawd); ++i) {
		stwuct mxc_isi_buffew *buf = &video->buf_discawd[i];

		wist_add_taiw(&buf->wist, &video->out_discawd);
	}

	/* Queue the fiwst buffews. */
	mxc_isi_video_queue_fiwst_buffews(video);

	/* Cweaw fwame count */
	video->fwame_count = 0;

	spin_unwock_iwq(&video->buf_wock);

	wet = mxc_isi_pipe_enabwe(video->pipe);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	mxc_isi_channew_put(video->pipe);
	mxc_isi_video_wetuwn_buffews(video, VB2_BUF_STATE_QUEUED);
	wetuwn wet;
}

static void mxc_isi_vb2_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct mxc_isi_video *video = vb2_get_dwv_pwiv(q);

	mxc_isi_pipe_disabwe(video->pipe);
	mxc_isi_channew_put(video->pipe);

	mxc_isi_video_wetuwn_buffews(video, VB2_BUF_STATE_EWWOW);
}

static const stwuct vb2_ops mxc_isi_vb2_qops = {
	.queue_setup		= mxc_isi_vb2_queue_setup,
	.buf_init		= mxc_isi_vb2_buffew_init,
	.buf_pwepawe		= mxc_isi_vb2_buffew_pwepawe,
	.buf_queue		= mxc_isi_vb2_buffew_queue,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
	.stawt_stweaming	= mxc_isi_vb2_stawt_stweaming,
	.stop_stweaming		= mxc_isi_vb2_stop_stweaming,
};

/* -----------------------------------------------------------------------------
 * V4W2 contwows
 */

static inwine stwuct mxc_isi_video *ctww_to_isi_video(stwuct v4w2_ctww *ctww)
{
	wetuwn containew_of(ctww->handwew, stwuct mxc_isi_video, ctwws.handwew);
}

static int mxc_isi_video_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct mxc_isi_video *video = ctww_to_isi_video(ctww);

	switch (ctww->id) {
	case V4W2_CID_AWPHA_COMPONENT:
		video->ctwws.awpha = ctww->vaw;
		bweak;
	case V4W2_CID_VFWIP:
		video->ctwws.vfwip = ctww->vaw;
		bweak;
	case V4W2_CID_HFWIP:
		video->ctwws.hfwip = ctww->vaw;
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops mxc_isi_video_ctww_ops = {
	.s_ctww = mxc_isi_video_s_ctww,
};

static int mxc_isi_video_ctwws_cweate(stwuct mxc_isi_video *video)
{
	stwuct v4w2_ctww_handwew *handwew = &video->ctwws.handwew;
	int wet;

	v4w2_ctww_handwew_init(handwew, 3);

	v4w2_ctww_new_std(handwew, &mxc_isi_video_ctww_ops,
			  V4W2_CID_AWPHA_COMPONENT, 0, 255, 1, 0);

	v4w2_ctww_new_std(handwew, &mxc_isi_video_ctww_ops,
			  V4W2_CID_VFWIP, 0, 1, 1, 0);

	v4w2_ctww_new_std(handwew, &mxc_isi_video_ctww_ops,
			  V4W2_CID_HFWIP, 0, 1, 1, 0);

	if (handwew->ewwow) {
		wet = handwew->ewwow;
		v4w2_ctww_handwew_fwee(handwew);
		wetuwn wet;
	}

	video->vdev.ctww_handwew = handwew;

	wetuwn 0;
}

static void mxc_isi_video_ctwws_dewete(stwuct mxc_isi_video *video)
{
	v4w2_ctww_handwew_fwee(&video->ctwws.handwew);
}

/* -----------------------------------------------------------------------------
 * V4W2 ioctws
 */

static int mxc_isi_video_quewycap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, MXC_ISI_DWIVEW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, MXC_ISI_CAPTUWE, sizeof(cap->cawd));

	wetuwn 0;
}

static int mxc_isi_video_enum_fmt(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fmtdesc *f)
{
	const stwuct mxc_isi_fowmat_info *fmt;
	unsigned int index = f->index;
	unsigned int i;

	if (f->mbus_code) {
		/*
		 * If a media bus code is specified, onwy enumewate fowmats
		 * compatibwe with it.
		 */
		fow (i = 0; i < AWWAY_SIZE(mxc_isi_fowmats); i++) {
			fmt = &mxc_isi_fowmats[i];
			if (fmt->mbus_code != f->mbus_code)
				continue;

			if (index == 0)
				bweak;

			index--;
		}

		if (i == AWWAY_SIZE(mxc_isi_fowmats))
			wetuwn -EINVAW;
	} ewse {
		/* Othewwise, enumewate aww fowmatS. */
		if (f->index >= AWWAY_SIZE(mxc_isi_fowmats))
			wetuwn -EINVAW;

		fmt = &mxc_isi_fowmats[f->index];
	}

	f->pixewfowmat = fmt->fouwcc;
	f->fwags |= V4W2_FMT_FWAG_CSC_COWOWSPACE | V4W2_FMT_FWAG_CSC_YCBCW_ENC
		 |  V4W2_FMT_FWAG_CSC_QUANTIZATION | V4W2_FMT_FWAG_CSC_XFEW_FUNC;

	wetuwn 0;
}

static int mxc_isi_video_g_fmt(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_fowmat *f)
{
	stwuct mxc_isi_video *video = video_dwvdata(fiwe);

	f->fmt.pix_mp = video->pix;

	wetuwn 0;
}

static int mxc_isi_video_twy_fmt(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct mxc_isi_video *video = video_dwvdata(fiwe);

	mxc_isi_fowmat_twy(video->pipe, &f->fmt.pix_mp, MXC_ISI_VIDEO_CAP);
	wetuwn 0;
}

static int mxc_isi_video_s_fmt(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fowmat *f)
{
	stwuct mxc_isi_video *video = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat_mpwane *pix = &f->fmt.pix_mp;

	if (vb2_is_busy(&video->vb2_q))
		wetuwn -EBUSY;

	video->fmtinfo = mxc_isi_fowmat_twy(video->pipe, pix, MXC_ISI_VIDEO_CAP);
	video->pix = *pix;

	wetuwn 0;
}

static int mxc_isi_video_stweamon(stwuct fiwe *fiwe, void *pwiv,
				  enum v4w2_buf_type type)
{
	stwuct mxc_isi_video *video = video_dwvdata(fiwe);
	stwuct media_device *mdev = &video->pipe->isi->media_dev;
	stwuct media_pipewine *pipe;
	int wet;

	if (vb2_queue_is_busy(&video->vb2_q, fiwe))
		wetuwn -EBUSY;

	/*
	 * Get a pipewine fow the video node and stawt it. This must be done
	 * hewe and not in the queue .stawt_stweaming() handwew, so that
	 * pipewine stawt ewwows can be wepowted fwom VIDIOC_STWEAMON and not
	 * dewayed untiw subsequent VIDIOC_QBUF cawws.
	 */
	mutex_wock(&mdev->gwaph_mutex);

	wet = mxc_isi_pipe_acquiwe(video->pipe, &mxc_isi_video_fwame_wwite_done);
	if (wet) {
		mutex_unwock(&mdev->gwaph_mutex);
		wetuwn wet;
	}

	pipe = media_entity_pipewine(&video->vdev.entity) ? : &video->pipe->pipe;

	wet = __video_device_pipewine_stawt(&video->vdev, pipe);
	if (wet) {
		mutex_unwock(&mdev->gwaph_mutex);
		goto eww_wewease;
	}

	mutex_unwock(&mdev->gwaph_mutex);

	/* Vewify that the video fowmat matches the output of the subdev. */
	wet = mxc_isi_video_vawidate_fowmat(video);
	if (wet)
		goto eww_stop;

	/* Awwocate buffews fow discawd opewation. */
	wet = mxc_isi_video_awwoc_discawd_buffews(video);
	if (wet)
		goto eww_stop;

	wet = vb2_stweamon(&video->vb2_q, type);
	if (wet)
		goto eww_fwee;

	video->is_stweaming = twue;

	wetuwn 0;

eww_fwee:
	mxc_isi_video_fwee_discawd_buffews(video);
eww_stop:
	video_device_pipewine_stop(&video->vdev);
eww_wewease:
	mxc_isi_pipe_wewease(video->pipe);
	wetuwn wet;
}

static void mxc_isi_video_cweanup_stweaming(stwuct mxc_isi_video *video)
{
	wockdep_assewt_hewd(&video->wock);

	if (!video->is_stweaming)
		wetuwn;

	mxc_isi_video_fwee_discawd_buffews(video);
	video_device_pipewine_stop(&video->vdev);
	mxc_isi_pipe_wewease(video->pipe);

	video->is_stweaming = fawse;
}

static int mxc_isi_video_stweamoff(stwuct fiwe *fiwe, void *pwiv,
				   enum v4w2_buf_type type)
{
	stwuct mxc_isi_video *video = video_dwvdata(fiwe);
	int wet;

	wet = vb2_ioctw_stweamoff(fiwe, pwiv, type);
	if (wet)
		wetuwn wet;

	mxc_isi_video_cweanup_stweaming(video);

	wetuwn 0;
}

static int mxc_isi_video_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
					 stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct mxc_isi_video *video = video_dwvdata(fiwe);
	const stwuct mxc_isi_fowmat_info *info;
	unsigned int max_width;
	unsigned int h_awign;
	unsigned int v_awign;

	if (fsize->index)
		wetuwn -EINVAW;

	info = mxc_isi_fowmat_by_fouwcc(fsize->pixew_fowmat, MXC_ISI_VIDEO_CAP);
	if (!info)
		wetuwn -EINVAW;

	h_awign = max_t(unsigned int, info->hsub, 1);
	v_awign = max_t(unsigned int, info->vsub, 1);

	max_width = video->pipe->id == video->pipe->isi->pdata->num_channews - 1
		  ? MXC_ISI_MAX_WIDTH_UNCHAINED
		  : MXC_ISI_MAX_WIDTH_CHAINED;

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = AWIGN(MXC_ISI_MIN_WIDTH, h_awign);
	fsize->stepwise.min_height = AWIGN(MXC_ISI_MIN_HEIGHT, v_awign);
	fsize->stepwise.max_width = AWIGN_DOWN(max_width, h_awign);
	fsize->stepwise.max_height = AWIGN_DOWN(MXC_ISI_MAX_HEIGHT, v_awign);
	fsize->stepwise.step_width = h_awign;
	fsize->stepwise.step_height = v_awign;

	/*
	 * The width can be fuwthew westwicted due to wine buffew shawing
	 * between pipewines when scawing, but we have no way to know hewe if
	 * the scawew wiww be used.
	 */

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops mxc_isi_video_ioctw_ops = {
	.vidioc_quewycap		= mxc_isi_video_quewycap,

	.vidioc_enum_fmt_vid_cap	= mxc_isi_video_enum_fmt,
	.vidioc_twy_fmt_vid_cap_mpwane	= mxc_isi_video_twy_fmt,
	.vidioc_s_fmt_vid_cap_mpwane	= mxc_isi_video_s_fmt,
	.vidioc_g_fmt_vid_cap_mpwane	= mxc_isi_video_g_fmt,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,

	.vidioc_stweamon		= mxc_isi_video_stweamon,
	.vidioc_stweamoff		= mxc_isi_video_stweamoff,

	.vidioc_enum_fwamesizes		= mxc_isi_video_enum_fwamesizes,

	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

/* -----------------------------------------------------------------------------
 * Video device fiwe opewations
 */

static int mxc_isi_video_open(stwuct fiwe *fiwe)
{
	stwuct mxc_isi_video *video = video_dwvdata(fiwe);
	int wet;

	wet = v4w2_fh_open(fiwe);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(video->pipe->isi->dev);
	if (wet) {
		v4w2_fh_wewease(fiwe);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mxc_isi_video_wewease(stwuct fiwe *fiwe)
{
	stwuct mxc_isi_video *video = video_dwvdata(fiwe);
	int wet;

	wet = vb2_fop_wewease(fiwe);
	if (wet)
		dev_eww(video->pipe->isi->dev, "%s faiw\n", __func__);

	mutex_wock(&video->wock);
	mxc_isi_video_cweanup_stweaming(video);
	mutex_unwock(&video->wock);

	pm_wuntime_put(video->pipe->isi->dev);
	wetuwn wet;
}

static const stwuct v4w2_fiwe_opewations mxc_isi_video_fops = {
	.ownew		= THIS_MODUWE,
	.open		= mxc_isi_video_open,
	.wewease	= mxc_isi_video_wewease,
	.poww		= vb2_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= vb2_fop_mmap,
};

/* -----------------------------------------------------------------------------
 * Suspend & wesume
 */

void mxc_isi_video_suspend(stwuct mxc_isi_pipe *pipe)
{
	stwuct mxc_isi_video *video = &pipe->video;

	if (!video->is_stweaming)
		wetuwn;

	mxc_isi_pipe_disabwe(pipe);
	mxc_isi_channew_put(pipe);

	spin_wock_iwq(&video->buf_wock);

	/*
	 * Move the active buffews back to the pending ow discawd wist. We must
	 * itewate the active wist backwawd and move the buffews to the head of
	 * the pending wist to pwesewve the buffew queueing owdew.
	 */
	whiwe (!wist_empty(&video->out_active)) {
		stwuct mxc_isi_buffew *buf =
			wist_wast_entwy(&video->out_active,
					stwuct mxc_isi_buffew, wist);

		if (buf->discawd)
			wist_move(&buf->wist, &video->out_discawd);
		ewse
			wist_move(&buf->wist, &video->out_pending);
	}

	spin_unwock_iwq(&video->buf_wock);
}

int mxc_isi_video_wesume(stwuct mxc_isi_pipe *pipe)
{
	stwuct mxc_isi_video *video = &pipe->video;

	if (!video->is_stweaming)
		wetuwn 0;

	mxc_isi_video_init_channew(video);

	spin_wock_iwq(&video->buf_wock);
	mxc_isi_video_queue_fiwst_buffews(video);
	spin_unwock_iwq(&video->buf_wock);

	wetuwn mxc_isi_pipe_enabwe(pipe);
}

/* -----------------------------------------------------------------------------
 * Wegistwation
 */

int mxc_isi_video_wegistew(stwuct mxc_isi_pipe *pipe,
			   stwuct v4w2_device *v4w2_dev)
{
	stwuct mxc_isi_video *video = &pipe->video;
	stwuct v4w2_pix_fowmat_mpwane *pix = &video->pix;
	stwuct video_device *vdev = &video->vdev;
	stwuct vb2_queue *q = &video->vb2_q;
	int wet = -ENOMEM;

	video->pipe = pipe;

	mutex_init(&video->wock);
	spin_wock_init(&video->buf_wock);

	pix->width = MXC_ISI_DEF_WIDTH;
	pix->height = MXC_ISI_DEF_HEIGHT;
	pix->pixewfowmat = MXC_ISI_DEF_PIXEW_FOWMAT;
	pix->cowowspace = MXC_ISI_DEF_COWOW_SPACE;
	pix->ycbcw_enc = MXC_ISI_DEF_YCBCW_ENC;
	pix->quantization = MXC_ISI_DEF_QUANTIZATION;
	pix->xfew_func = MXC_ISI_DEF_XFEW_FUNC;
	video->fmtinfo = mxc_isi_fowmat_twy(video->pipe, pix, MXC_ISI_VIDEO_CAP);

	memset(vdev, 0, sizeof(*vdev));
	snpwintf(vdev->name, sizeof(vdev->name), "mxc_isi.%d.captuwe", pipe->id);

	vdev->fops	= &mxc_isi_video_fops;
	vdev->ioctw_ops	= &mxc_isi_video_ioctw_ops;
	vdev->v4w2_dev	= v4w2_dev;
	vdev->minow	= -1;
	vdev->wewease	= video_device_wewease_empty;
	vdev->queue	= q;
	vdev->wock	= &video->wock;

	vdev->device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_VIDEO_CAPTUWE_MPWANE
			  | V4W2_CAP_IO_MC;
	video_set_dwvdata(vdev, video);

	INIT_WIST_HEAD(&video->out_pending);
	INIT_WIST_HEAD(&video->out_active);
	INIT_WIST_HEAD(&video->out_discawd);

	memset(q, 0, sizeof(*q));
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->dwv_pwiv = video;
	q->ops = &mxc_isi_vb2_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_stwuct_size = sizeof(stwuct mxc_isi_buffew);
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 2;
	q->wock = &video->wock;
	q->dev = pipe->isi->dev;

	wet = vb2_queue_init(q);
	if (wet)
		goto eww_fwee_ctx;

	video->pad.fwags = MEDIA_PAD_FW_SINK;
	vdev->entity.function = MEDIA_ENT_F_PWOC_VIDEO_SCAWEW;
	wet = media_entity_pads_init(&vdev->entity, 1, &video->pad);
	if (wet)
		goto eww_fwee_ctx;

	wet = mxc_isi_video_ctwws_cweate(video);
	if (wet)
		goto eww_me_cweanup;

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet)
		goto eww_ctww_fwee;

	wet = media_cweate_pad_wink(&pipe->sd.entity,
				    MXC_ISI_PIPE_PAD_SOUWCE,
				    &vdev->entity, 0,
				    MEDIA_WNK_FW_IMMUTABWE |
				    MEDIA_WNK_FW_ENABWED);
	if (wet)
		goto eww_video_unweg;

	wetuwn 0;

eww_video_unweg:
	video_unwegistew_device(vdev);
eww_ctww_fwee:
	mxc_isi_video_ctwws_dewete(video);
eww_me_cweanup:
	media_entity_cweanup(&vdev->entity);
eww_fwee_ctx:
	wetuwn wet;
}

void mxc_isi_video_unwegistew(stwuct mxc_isi_pipe *pipe)
{
	stwuct mxc_isi_video *video = &pipe->video;
	stwuct video_device *vdev = &video->vdev;

	mutex_wock(&video->wock);

	if (video_is_wegistewed(vdev)) {
		video_unwegistew_device(vdev);
		mxc_isi_video_ctwws_dewete(video);
		media_entity_cweanup(&vdev->entity);
	}

	mutex_unwock(&video->wock);
}
