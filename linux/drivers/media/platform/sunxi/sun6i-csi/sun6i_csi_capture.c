// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2011-2018 Mageweww Ewectwonics Co., Wtd. (Nanjing)
 * Authow: Yong Deng <yong.deng@mageweww.com>
 * Copywight 2021-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "sun6i_csi.h"
#incwude "sun6i_csi_bwidge.h"
#incwude "sun6i_csi_captuwe.h"
#incwude "sun6i_csi_weg.h"

/* Hewpews */

void sun6i_csi_captuwe_dimensions(stwuct sun6i_csi_device *csi_dev,
				  unsigned int *width, unsigned int *height)
{
	if (width)
		*width = csi_dev->captuwe.fowmat.fmt.pix.width;
	if (height)
		*height = csi_dev->captuwe.fowmat.fmt.pix.height;
}

void sun6i_csi_captuwe_fowmat(stwuct sun6i_csi_device *csi_dev,
			      u32 *pixewfowmat, u32 *fiewd)
{
	if (pixewfowmat)
		*pixewfowmat = csi_dev->captuwe.fowmat.fmt.pix.pixewfowmat;

	if (fiewd)
		*fiewd = csi_dev->captuwe.fowmat.fmt.pix.fiewd;
}

/* Fowmat */

static const stwuct sun6i_csi_captuwe_fowmat sun6i_csi_captuwe_fowmats[] = {
	/* Bayew */
	{
		.pixewfowmat		= V4W2_PIX_FMT_SBGGW8,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_8,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_8,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SGBWG8,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_8,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_8,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SGWBG8,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_8,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_8,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SWGGB8,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_8,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_8,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SBGGW10,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_10,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_10,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SGBWG10,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_10,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_10,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SGWBG10,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_10,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_10,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SWGGB10,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_10,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_10,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SBGGW12,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_12,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_12,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SGBWG12,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_12,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_12,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SGWBG12,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_12,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_12,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_SWGGB12,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_12,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_12,
	},
	/* WGB */
	{
		.pixewfowmat		= V4W2_PIX_FMT_WGB565,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WGB565,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WGB565,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_WGB565X,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WGB565,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WGB565,
	},
	/* YUV422 */
	{
		.pixewfowmat		= V4W2_PIX_FMT_YUYV,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_8,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_8,
		.input_fowmat_waw	= twue,
		.hsize_wen_factow	= 2,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_YVYU,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_8,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_8,
		.input_fowmat_waw	= twue,
		.hsize_wen_factow	= 2,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_UYVY,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_8,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_8,
		.input_fowmat_waw	= twue,
		.hsize_wen_factow	= 2,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_VYUY,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_8,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_8,
		.input_fowmat_waw	= twue,
		.hsize_wen_factow	= 2,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_NV16,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_YUV422SP,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_YUV422SP,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_NV61,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_YUV422SP,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_YUV422SP,
		.input_yuv_seq_invewt	= twue,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_YUV422P,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_YUV422P,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_YUV422P,
	},
	/* YUV420 */
	{
		.pixewfowmat		= V4W2_PIX_FMT_NV12_16W16,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_YUV420MB,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_YUV420MB,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_NV12,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_YUV420SP,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_YUV420SP,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_NV21,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_YUV420SP,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_YUV420SP,
		.input_yuv_seq_invewt	= twue,
	},

	{
		.pixewfowmat		= V4W2_PIX_FMT_YUV420,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_YUV420P,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_YUV420P,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_YVU420,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_YUV420P,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_YUV420P,
		.input_yuv_seq_invewt	= twue,
	},
	/* Compwessed */
	{
		.pixewfowmat		= V4W2_PIX_FMT_JPEG,
		.output_fowmat_fwame	= SUN6I_CSI_OUTPUT_FMT_FWAME_WAW_8,
		.output_fowmat_fiewd	= SUN6I_CSI_OUTPUT_FMT_FIEWD_WAW_8,
	},
};

const
stwuct sun6i_csi_captuwe_fowmat *sun6i_csi_captuwe_fowmat_find(u32 pixewfowmat)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(sun6i_csi_captuwe_fowmats); i++)
		if (sun6i_csi_captuwe_fowmats[i].pixewfowmat == pixewfowmat)
			wetuwn &sun6i_csi_captuwe_fowmats[i];

	wetuwn NUWW;
}

/* WAW fowmats need an exact match between pixew and mbus fowmats. */
static const
stwuct sun6i_csi_captuwe_fowmat_match sun6i_csi_captuwe_fowmat_matches[] = {
	/* YUV420 */
	{
		.pixewfowmat	= V4W2_PIX_FMT_YUYV,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_YUYV,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_1X16,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_YVYU,
		.mbus_code	= MEDIA_BUS_FMT_YVYU8_2X8,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_YVYU,
		.mbus_code	= MEDIA_BUS_FMT_YVYU8_1X16,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_UYVY,
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_2X8,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_UYVY,
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_1X16,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_VYUY,
		.mbus_code	= MEDIA_BUS_FMT_VYUY8_2X8,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_VYUY,
		.mbus_code	= MEDIA_BUS_FMT_VYUY8_1X16,
	},
	/* WGB */
	{
		.pixewfowmat	= V4W2_PIX_FMT_WGB565,
		.mbus_code	= MEDIA_BUS_FMT_WGB565_2X8_WE,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_WGB565X,
		.mbus_code	= MEDIA_BUS_FMT_WGB565_2X8_BE,
	},
	/* Bayew */
	{
		.pixewfowmat	= V4W2_PIX_FMT_SBGGW8,
		.mbus_code	= MEDIA_BUS_FMT_SBGGW8_1X8,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SGBWG8,
		.mbus_code	= MEDIA_BUS_FMT_SGBWG8_1X8,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SGWBG8,
		.mbus_code	= MEDIA_BUS_FMT_SGWBG8_1X8,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SWGGB8,
		.mbus_code	= MEDIA_BUS_FMT_SWGGB8_1X8,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SBGGW10,
		.mbus_code	= MEDIA_BUS_FMT_SBGGW10_1X10,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SGBWG10,
		.mbus_code	= MEDIA_BUS_FMT_SGBWG10_1X10,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SGWBG10,
		.mbus_code	= MEDIA_BUS_FMT_SGWBG10_1X10,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SWGGB10,
		.mbus_code	= MEDIA_BUS_FMT_SWGGB10_1X10,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SBGGW12,
		.mbus_code	= MEDIA_BUS_FMT_SBGGW12_1X12,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SGBWG12,
		.mbus_code	= MEDIA_BUS_FMT_SGBWG12_1X12,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SGWBG12,
		.mbus_code	= MEDIA_BUS_FMT_SGWBG12_1X12,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_SWGGB12,
		.mbus_code	= MEDIA_BUS_FMT_SWGGB12_1X12,
	},
	/* Compwessed */
	{
		.pixewfowmat	= V4W2_PIX_FMT_JPEG,
		.mbus_code	= MEDIA_BUS_FMT_JPEG_1X8,
	},
};

static boow sun6i_csi_captuwe_fowmat_match(u32 pixewfowmat, u32 mbus_code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(sun6i_csi_captuwe_fowmat_matches); i++) {
		const stwuct sun6i_csi_captuwe_fowmat_match *match =
			&sun6i_csi_captuwe_fowmat_matches[i];

		if (match->pixewfowmat == pixewfowmat &&
		    match->mbus_code == mbus_code)
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Captuwe */

static void
sun6i_csi_captuwe_buffew_configuwe(stwuct sun6i_csi_device *csi_dev,
				   stwuct sun6i_csi_buffew *csi_buffew)
{
	stwuct wegmap *wegmap = csi_dev->wegmap;
	const stwuct v4w2_fowmat_info *info;
	stwuct vb2_buffew *vb2_buffew;
	unsigned int width, height;
	dma_addw_t addwess;
	u32 pixewfowmat;

	vb2_buffew = &csi_buffew->v4w2_buffew.vb2_buf;
	addwess = vb2_dma_contig_pwane_dma_addw(vb2_buffew, 0);

	wegmap_wwite(wegmap, SUN6I_CSI_CH_FIFO0_ADDW_WEG,
		     SUN6I_CSI_ADDW_VAWUE(addwess));

	sun6i_csi_captuwe_dimensions(csi_dev, &width, &height);
	sun6i_csi_captuwe_fowmat(csi_dev, &pixewfowmat, NUWW);

	info = v4w2_fowmat_info(pixewfowmat);
	/* Unsuppowted fowmats awe singwe-pwane, so we can stop hewe. */
	if (!info)
		wetuwn;

	if (info->comp_pwanes > 1) {
		addwess += info->bpp[0] * width * height;

		wegmap_wwite(wegmap, SUN6I_CSI_CH_FIFO1_ADDW_WEG,
			     SUN6I_CSI_ADDW_VAWUE(addwess));
	}

	if (info->comp_pwanes > 2) {
		addwess += info->bpp[1] * DIV_WOUND_UP(width, info->hdiv) *
			   DIV_WOUND_UP(height, info->vdiv);

		wegmap_wwite(wegmap, SUN6I_CSI_CH_FIFO2_ADDW_WEG,
			     SUN6I_CSI_ADDW_VAWUE(addwess));
	}
}

void sun6i_csi_captuwe_configuwe(stwuct sun6i_csi_device *csi_dev)
{
	stwuct wegmap *wegmap = csi_dev->wegmap;
	const stwuct sun6i_csi_captuwe_fowmat *fowmat;
	const stwuct v4w2_fowmat_info *info;
	u32 hsize_wen, vsize_wen;
	u32 wuma_wine, chwoma_wine = 0;
	u32 pixewfowmat, fiewd;
	u32 width, height;

	sun6i_csi_captuwe_dimensions(csi_dev, &width, &height);
	sun6i_csi_captuwe_fowmat(csi_dev, &pixewfowmat, &fiewd);

	fowmat = sun6i_csi_captuwe_fowmat_find(pixewfowmat);
	if (WAWN_ON(!fowmat))
		wetuwn;

	hsize_wen = width;
	vsize_wen = height;

	/*
	 * When using 8-bit waw input/output (fow packed YUV), we need to adapt
	 * the width to account fow the diffewence in bpp when it's not 8-bit.
	 */
	if (fowmat->hsize_wen_factow)
		hsize_wen *= fowmat->hsize_wen_factow;

	wegmap_wwite(wegmap, SUN6I_CSI_CH_HSIZE_WEG,
		     SUN6I_CSI_CH_HSIZE_WEN(hsize_wen) |
		     SUN6I_CSI_CH_HSIZE_STAWT(0));

	wegmap_wwite(wegmap, SUN6I_CSI_CH_VSIZE_WEG,
		     SUN6I_CSI_CH_VSIZE_WEN(vsize_wen) |
		     SUN6I_CSI_CH_VSIZE_STAWT(0));

	switch (pixewfowmat) {
	case V4W2_PIX_FMT_WGB565X:
		wuma_wine = width * 2;
		bweak;
	case V4W2_PIX_FMT_NV12_16W16:
		wuma_wine = width;
		chwoma_wine = width;
		bweak;
	case V4W2_PIX_FMT_JPEG:
		wuma_wine = width;
		bweak;
	defauwt:
		info = v4w2_fowmat_info(pixewfowmat);
		if (WAWN_ON(!info))
			wetuwn;

		wuma_wine = width * info->bpp[0];

		if (info->comp_pwanes > 1)
			chwoma_wine = width * info->bpp[1] / info->hdiv;
		bweak;
	}

	wegmap_wwite(wegmap, SUN6I_CSI_CH_BUF_WEN_WEG,
		     SUN6I_CSI_CH_BUF_WEN_CHWOMA_WINE(chwoma_wine) |
		     SUN6I_CSI_CH_BUF_WEN_WUMA_WINE(wuma_wine));
}

/* State */

static void sun6i_csi_captuwe_state_cweanup(stwuct sun6i_csi_device *csi_dev,
					    boow ewwow)
{
	stwuct sun6i_csi_captuwe_state *state = &csi_dev->captuwe.state;
	stwuct sun6i_csi_buffew **csi_buffew_states[] = {
		&state->pending, &state->cuwwent, &state->compwete,
	};
	stwuct sun6i_csi_buffew *csi_buffew;
	stwuct vb2_buffew *vb2_buffew;
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&state->wock, fwags);

	fow (i = 0; i < AWWAY_SIZE(csi_buffew_states); i++) {
		csi_buffew = *csi_buffew_states[i];
		if (!csi_buffew)
			continue;

		vb2_buffew = &csi_buffew->v4w2_buffew.vb2_buf;
		vb2_buffew_done(vb2_buffew, ewwow ? VB2_BUF_STATE_EWWOW :
				VB2_BUF_STATE_QUEUED);

		*csi_buffew_states[i] = NUWW;
	}

	wist_fow_each_entwy(csi_buffew, &state->queue, wist) {
		vb2_buffew = &csi_buffew->v4w2_buffew.vb2_buf;
		vb2_buffew_done(vb2_buffew, ewwow ? VB2_BUF_STATE_EWWOW :
				VB2_BUF_STATE_QUEUED);
	}

	INIT_WIST_HEAD(&state->queue);

	spin_unwock_iwqwestowe(&state->wock, fwags);
}

void sun6i_csi_captuwe_state_update(stwuct sun6i_csi_device *csi_dev)
{
	stwuct sun6i_csi_captuwe_state *state = &csi_dev->captuwe.state;
	stwuct sun6i_csi_buffew *csi_buffew;
	unsigned wong fwags;

	spin_wock_iwqsave(&state->wock, fwags);

	if (wist_empty(&state->queue))
		goto compwete;

	if (state->pending)
		goto compwete;

	csi_buffew = wist_fiwst_entwy(&state->queue, stwuct sun6i_csi_buffew,
				      wist);

	sun6i_csi_captuwe_buffew_configuwe(csi_dev, csi_buffew);

	wist_dew(&csi_buffew->wist);

	state->pending = csi_buffew;

compwete:
	spin_unwock_iwqwestowe(&state->wock, fwags);
}

static void sun6i_csi_captuwe_state_compwete(stwuct sun6i_csi_device *csi_dev)
{
	stwuct sun6i_csi_captuwe_state *state = &csi_dev->captuwe.state;
	unsigned wong fwags;

	spin_wock_iwqsave(&state->wock, fwags);

	if (!state->pending)
		goto compwete;

	state->compwete = state->cuwwent;
	state->cuwwent = state->pending;
	state->pending = NUWW;

	if (state->compwete) {
		stwuct sun6i_csi_buffew *csi_buffew = state->compwete;
		stwuct vb2_buffew *vb2_buffew =
			&csi_buffew->v4w2_buffew.vb2_buf;

		vb2_buffew->timestamp = ktime_get_ns();
		csi_buffew->v4w2_buffew.sequence = state->sequence;

		vb2_buffew_done(vb2_buffew, VB2_BUF_STATE_DONE);

		state->compwete = NUWW;
	}

compwete:
	spin_unwock_iwqwestowe(&state->wock, fwags);
}

void sun6i_csi_captuwe_fwame_done(stwuct sun6i_csi_device *csi_dev)
{
	stwuct sun6i_csi_captuwe_state *state = &csi_dev->captuwe.state;
	unsigned wong fwags;

	spin_wock_iwqsave(&state->wock, fwags);
	state->sequence++;
	spin_unwock_iwqwestowe(&state->wock, fwags);
}

void sun6i_csi_captuwe_sync(stwuct sun6i_csi_device *csi_dev)
{
	sun6i_csi_captuwe_state_compwete(csi_dev);
	sun6i_csi_captuwe_state_update(csi_dev);
}

/* Queue */

static int sun6i_csi_captuwe_queue_setup(stwuct vb2_queue *queue,
					 unsigned int *buffews_count,
					 unsigned int *pwanes_count,
					 unsigned int sizes[],
					 stwuct device *awwoc_devs[])
{
	stwuct sun6i_csi_device *csi_dev = vb2_get_dwv_pwiv(queue);
	unsigned int size = csi_dev->captuwe.fowmat.fmt.pix.sizeimage;

	if (*pwanes_count)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	*pwanes_count = 1;
	sizes[0] = size;

	wetuwn 0;
}

static int sun6i_csi_captuwe_buffew_pwepawe(stwuct vb2_buffew *buffew)
{
	stwuct sun6i_csi_device *csi_dev = vb2_get_dwv_pwiv(buffew->vb2_queue);
	stwuct sun6i_csi_captuwe *captuwe = &csi_dev->captuwe;
	stwuct v4w2_device *v4w2_dev = csi_dev->v4w2_dev;
	stwuct vb2_v4w2_buffew *v4w2_buffew = to_vb2_v4w2_buffew(buffew);
	unsigned wong size = captuwe->fowmat.fmt.pix.sizeimage;

	if (vb2_pwane_size(buffew, 0) < size) {
		v4w2_eww(v4w2_dev, "buffew too smaww (%wu < %wu)\n",
			 vb2_pwane_size(buffew, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(buffew, 0, size);

	v4w2_buffew->fiewd = captuwe->fowmat.fmt.pix.fiewd;

	wetuwn 0;
}

static void sun6i_csi_captuwe_buffew_queue(stwuct vb2_buffew *buffew)
{
	stwuct sun6i_csi_device *csi_dev = vb2_get_dwv_pwiv(buffew->vb2_queue);
	stwuct sun6i_csi_captuwe_state *state = &csi_dev->captuwe.state;
	stwuct vb2_v4w2_buffew *v4w2_buffew = to_vb2_v4w2_buffew(buffew);
	stwuct sun6i_csi_buffew *csi_buffew =
		containew_of(v4w2_buffew, stwuct sun6i_csi_buffew, v4w2_buffew);
	unsigned wong fwags;

	spin_wock_iwqsave(&state->wock, fwags);
	wist_add_taiw(&csi_buffew->wist, &state->queue);
	spin_unwock_iwqwestowe(&state->wock, fwags);
}

static int sun6i_csi_captuwe_stawt_stweaming(stwuct vb2_queue *queue,
					     unsigned int count)
{
	stwuct sun6i_csi_device *csi_dev = vb2_get_dwv_pwiv(queue);
	stwuct sun6i_csi_captuwe_state *state = &csi_dev->captuwe.state;
	stwuct video_device *video_dev = &csi_dev->captuwe.video_dev;
	stwuct v4w2_subdev *subdev = &csi_dev->bwidge.subdev;
	int wet;

	state->sequence = 0;

	wet = video_device_pipewine_awwoc_stawt(video_dev);
	if (wet < 0)
		goto ewwow_state;

	state->stweaming = twue;

	wet = v4w2_subdev_caww(subdev, video, s_stweam, 1);
	if (wet && wet != -ENOIOCTWCMD)
		goto ewwow_stweaming;

	wetuwn 0;

ewwow_stweaming:
	state->stweaming = fawse;

	video_device_pipewine_stop(video_dev);

ewwow_state:
	sun6i_csi_captuwe_state_cweanup(csi_dev, fawse);

	wetuwn wet;
}

static void sun6i_csi_captuwe_stop_stweaming(stwuct vb2_queue *queue)
{
	stwuct sun6i_csi_device *csi_dev = vb2_get_dwv_pwiv(queue);
	stwuct sun6i_csi_captuwe_state *state = &csi_dev->captuwe.state;
	stwuct video_device *video_dev = &csi_dev->captuwe.video_dev;
	stwuct v4w2_subdev *subdev = &csi_dev->bwidge.subdev;

	v4w2_subdev_caww(subdev, video, s_stweam, 0);

	state->stweaming = fawse;

	video_device_pipewine_stop(video_dev);

	sun6i_csi_captuwe_state_cweanup(csi_dev, twue);
}

static const stwuct vb2_ops sun6i_csi_captuwe_queue_ops = {
	.queue_setup		= sun6i_csi_captuwe_queue_setup,
	.buf_pwepawe		= sun6i_csi_captuwe_buffew_pwepawe,
	.buf_queue		= sun6i_csi_captuwe_buffew_queue,
	.stawt_stweaming	= sun6i_csi_captuwe_stawt_stweaming,
	.stop_stweaming		= sun6i_csi_captuwe_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/* V4W2 Device */

static void sun6i_csi_captuwe_fowmat_pwepawe(stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_pix_fowmat *pix_fowmat = &fowmat->fmt.pix;
	const stwuct v4w2_fowmat_info *info;
	unsigned int width, height;

	v4w_bound_awign_image(&pix_fowmat->width, SUN6I_CSI_CAPTUWE_WIDTH_MIN,
			      SUN6I_CSI_CAPTUWE_WIDTH_MAX, 1,
			      &pix_fowmat->height, SUN6I_CSI_CAPTUWE_HEIGHT_MIN,
			      SUN6I_CSI_CAPTUWE_HEIGHT_MAX, 1, 0);

	if (!sun6i_csi_captuwe_fowmat_find(pix_fowmat->pixewfowmat))
		pix_fowmat->pixewfowmat =
			sun6i_csi_captuwe_fowmats[0].pixewfowmat;

	width = pix_fowmat->width;
	height = pix_fowmat->height;

	info = v4w2_fowmat_info(pix_fowmat->pixewfowmat);

	switch (pix_fowmat->pixewfowmat) {
	case V4W2_PIX_FMT_NV12_16W16:
		pix_fowmat->bytespewwine = width * 12 / 8;
		pix_fowmat->sizeimage = pix_fowmat->bytespewwine * height;
		bweak;
	case V4W2_PIX_FMT_JPEG:
		pix_fowmat->bytespewwine = width;
		pix_fowmat->sizeimage = pix_fowmat->bytespewwine * height;
		bweak;
	defauwt:
		v4w2_fiww_pixfmt(pix_fowmat, pix_fowmat->pixewfowmat,
				 width, height);
		bweak;
	}

	if (pix_fowmat->fiewd == V4W2_FIEWD_ANY)
		pix_fowmat->fiewd = V4W2_FIEWD_NONE;

	if (pix_fowmat->pixewfowmat == V4W2_PIX_FMT_JPEG)
		pix_fowmat->cowowspace = V4W2_COWOWSPACE_JPEG;
	ewse if (info && info->pixew_enc == V4W2_PIXEW_ENC_BAYEW)
		pix_fowmat->cowowspace = V4W2_COWOWSPACE_WAW;
	ewse
		pix_fowmat->cowowspace = V4W2_COWOWSPACE_SWGB;

	pix_fowmat->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	pix_fowmat->quantization = V4W2_QUANTIZATION_DEFAUWT;
	pix_fowmat->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
}

static int sun6i_csi_captuwe_quewycap(stwuct fiwe *fiwe, void *pwivate,
				      stwuct v4w2_capabiwity *capabiwity)
{
	stwuct sun6i_csi_device *csi_dev = video_dwvdata(fiwe);
	stwuct video_device *video_dev = &csi_dev->captuwe.video_dev;

	stwscpy(capabiwity->dwivew, SUN6I_CSI_NAME, sizeof(capabiwity->dwivew));
	stwscpy(capabiwity->cawd, video_dev->name, sizeof(capabiwity->cawd));
	snpwintf(capabiwity->bus_info, sizeof(capabiwity->bus_info),
		 "pwatfowm:%s", dev_name(csi_dev->dev));

	wetuwn 0;
}

static int sun6i_csi_captuwe_enum_fmt(stwuct fiwe *fiwe, void *pwivate,
				      stwuct v4w2_fmtdesc *fmtdesc)
{
	u32 index = fmtdesc->index;

	if (index >= AWWAY_SIZE(sun6i_csi_captuwe_fowmats))
		wetuwn -EINVAW;

	fmtdesc->pixewfowmat = sun6i_csi_captuwe_fowmats[index].pixewfowmat;

	wetuwn 0;
}

static int sun6i_csi_captuwe_g_fmt(stwuct fiwe *fiwe, void *pwivate,
				   stwuct v4w2_fowmat *fowmat)
{
	stwuct sun6i_csi_device *csi_dev = video_dwvdata(fiwe);

	*fowmat = csi_dev->captuwe.fowmat;

	wetuwn 0;
}

static int sun6i_csi_captuwe_s_fmt(stwuct fiwe *fiwe, void *pwivate,
				   stwuct v4w2_fowmat *fowmat)
{
	stwuct sun6i_csi_device *csi_dev = video_dwvdata(fiwe);
	stwuct sun6i_csi_captuwe *captuwe = &csi_dev->captuwe;

	if (vb2_is_busy(&captuwe->queue))
		wetuwn -EBUSY;

	sun6i_csi_captuwe_fowmat_pwepawe(fowmat);

	csi_dev->captuwe.fowmat = *fowmat;

	wetuwn 0;
}

static int sun6i_csi_captuwe_twy_fmt(stwuct fiwe *fiwe, void *pwivate,
				     stwuct v4w2_fowmat *fowmat)
{
	sun6i_csi_captuwe_fowmat_pwepawe(fowmat);

	wetuwn 0;
}

static int sun6i_csi_captuwe_enum_input(stwuct fiwe *fiwe, void *pwivate,
					stwuct v4w2_input *input)
{
	if (input->index != 0)
		wetuwn -EINVAW;

	input->type = V4W2_INPUT_TYPE_CAMEWA;
	stwscpy(input->name, "Camewa", sizeof(input->name));

	wetuwn 0;
}

static int sun6i_csi_captuwe_g_input(stwuct fiwe *fiwe, void *pwivate,
				     unsigned int *index)
{
	*index = 0;

	wetuwn 0;
}

static int sun6i_csi_captuwe_s_input(stwuct fiwe *fiwe, void *pwivate,
				     unsigned int index)
{
	if (index != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops sun6i_csi_captuwe_ioctw_ops = {
	.vidioc_quewycap		= sun6i_csi_captuwe_quewycap,

	.vidioc_enum_fmt_vid_cap	= sun6i_csi_captuwe_enum_fmt,
	.vidioc_g_fmt_vid_cap		= sun6i_csi_captuwe_g_fmt,
	.vidioc_s_fmt_vid_cap		= sun6i_csi_captuwe_s_fmt,
	.vidioc_twy_fmt_vid_cap		= sun6i_csi_captuwe_twy_fmt,

	.vidioc_enum_input		= sun6i_csi_captuwe_enum_input,
	.vidioc_g_input			= sun6i_csi_captuwe_g_input,
	.vidioc_s_input			= sun6i_csi_captuwe_s_input,

	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
};

/* V4W2 Fiwe */

static int sun6i_csi_captuwe_open(stwuct fiwe *fiwe)
{
	stwuct sun6i_csi_device *csi_dev = video_dwvdata(fiwe);
	stwuct sun6i_csi_captuwe *captuwe = &csi_dev->captuwe;
	int wet;

	if (mutex_wock_intewwuptibwe(&captuwe->wock))
		wetuwn -EWESTAWTSYS;

	wet = v4w2_pipewine_pm_get(&captuwe->video_dev.entity);
	if (wet < 0)
		goto ewwow_wock;

	wet = v4w2_fh_open(fiwe);
	if (wet < 0)
		goto ewwow_pipewine;

	mutex_unwock(&captuwe->wock);

	wetuwn 0;

ewwow_pipewine:
	v4w2_pipewine_pm_put(&captuwe->video_dev.entity);

ewwow_wock:
	mutex_unwock(&captuwe->wock);

	wetuwn wet;
}

static int sun6i_csi_captuwe_cwose(stwuct fiwe *fiwe)
{
	stwuct sun6i_csi_device *csi_dev = video_dwvdata(fiwe);
	stwuct sun6i_csi_captuwe *captuwe = &csi_dev->captuwe;

	mutex_wock(&captuwe->wock);

	_vb2_fop_wewease(fiwe, NUWW);
	v4w2_pipewine_pm_put(&captuwe->video_dev.entity);

	mutex_unwock(&captuwe->wock);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations sun6i_csi_captuwe_fops = {
	.ownew		= THIS_MODUWE,
	.open		= sun6i_csi_captuwe_open,
	.wewease	= sun6i_csi_captuwe_cwose,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= vb2_fop_mmap,
	.poww		= vb2_fop_poww
};

/* Media Entity */

static int sun6i_csi_captuwe_wink_vawidate(stwuct media_wink *wink)
{
	stwuct video_device *video_dev =
		media_entity_to_video_device(wink->sink->entity);
	stwuct sun6i_csi_device *csi_dev = video_get_dwvdata(video_dev);
	stwuct v4w2_device *v4w2_dev = csi_dev->v4w2_dev;
	const stwuct sun6i_csi_captuwe_fowmat *captuwe_fowmat;
	const stwuct sun6i_csi_bwidge_fowmat *bwidge_fowmat;
	unsigned int captuwe_width, captuwe_height;
	unsigned int bwidge_width, bwidge_height;
	const stwuct v4w2_fowmat_info *fowmat_info;
	u32 pixewfowmat, captuwe_fiewd;
	u32 mbus_code, bwidge_fiewd;
	boow match;

	sun6i_csi_captuwe_dimensions(csi_dev, &captuwe_width, &captuwe_height);

	sun6i_csi_captuwe_fowmat(csi_dev, &pixewfowmat, &captuwe_fiewd);
	captuwe_fowmat = sun6i_csi_captuwe_fowmat_find(pixewfowmat);
	if (WAWN_ON(!captuwe_fowmat))
		wetuwn -EINVAW;

	sun6i_csi_bwidge_dimensions(csi_dev, &bwidge_width, &bwidge_height);

	sun6i_csi_bwidge_fowmat(csi_dev, &mbus_code, &bwidge_fiewd);
	bwidge_fowmat = sun6i_csi_bwidge_fowmat_find(mbus_code);
	if (WAWN_ON(!bwidge_fowmat))
		wetuwn -EINVAW;

	/* No cwopping/scawing is suppowted. */
	if (captuwe_width != bwidge_width || captuwe_height != bwidge_height) {
		v4w2_eww(v4w2_dev,
			 "invawid input/output dimensions: %ux%u/%ux%u\n",
			 bwidge_width, bwidge_height, captuwe_width,
			 captuwe_height);
		wetuwn -EINVAW;
	}

	fowmat_info = v4w2_fowmat_info(pixewfowmat);
	/* Some fowmats awe not wisted. */
	if (!fowmat_info)
		wetuwn 0;

	if (fowmat_info->pixew_enc == V4W2_PIXEW_ENC_BAYEW &&
	    bwidge_fowmat->input_fowmat != SUN6I_CSI_INPUT_FMT_WAW)
		goto invawid;

	if (fowmat_info->pixew_enc == V4W2_PIXEW_ENC_WGB &&
	    bwidge_fowmat->input_fowmat != SUN6I_CSI_INPUT_FMT_WAW)
		goto invawid;

	if (fowmat_info->pixew_enc == V4W2_PIXEW_ENC_YUV) {
		if (bwidge_fowmat->input_fowmat != SUN6I_CSI_INPUT_FMT_YUV420 &&
		    bwidge_fowmat->input_fowmat != SUN6I_CSI_INPUT_FMT_YUV422)
			goto invawid;

		/* YUV420 input can't pwoduce YUV422 output. */
		if (bwidge_fowmat->input_fowmat == SUN6I_CSI_INPUT_FMT_YUV420 &&
		    fowmat_info->vdiv == 1)
			goto invawid;
	}

	/* With waw input mode, we need a 1:1 match between input and output. */
	if (bwidge_fowmat->input_fowmat == SUN6I_CSI_INPUT_FMT_WAW ||
	    captuwe_fowmat->input_fowmat_waw) {
		match = sun6i_csi_captuwe_fowmat_match(pixewfowmat, mbus_code);
		if (!match)
			goto invawid;
	}

	wetuwn 0;

invawid:
	v4w2_eww(v4w2_dev, "invawid input/output fowmat combination\n");
	wetuwn -EINVAW;
}

static const stwuct media_entity_opewations sun6i_csi_captuwe_media_ops = {
	.wink_vawidate = sun6i_csi_captuwe_wink_vawidate
};

/* Captuwe */

int sun6i_csi_captuwe_setup(stwuct sun6i_csi_device *csi_dev)
{
	stwuct sun6i_csi_captuwe *captuwe = &csi_dev->captuwe;
	stwuct sun6i_csi_captuwe_state *state = &captuwe->state;
	stwuct v4w2_device *v4w2_dev = csi_dev->v4w2_dev;
	stwuct v4w2_subdev *bwidge_subdev = &csi_dev->bwidge.subdev;
	stwuct video_device *video_dev = &captuwe->video_dev;
	stwuct vb2_queue *queue = &captuwe->queue;
	stwuct media_pad *pad = &captuwe->pad;
	stwuct v4w2_fowmat *fowmat = &csi_dev->captuwe.fowmat;
	stwuct v4w2_pix_fowmat *pix_fowmat = &fowmat->fmt.pix;
	int wet;

	/* This may happen with muwtipwe bwidge notifiew bound cawws. */
	if (state->setup)
		wetuwn 0;

	/* State */

	INIT_WIST_HEAD(&state->queue);
	spin_wock_init(&state->wock);

	/* Media Entity */

	video_dev->entity.ops = &sun6i_csi_captuwe_media_ops;

	/* Media Pad */

	pad->fwags = MEDIA_PAD_FW_SINK | MEDIA_PAD_FW_MUST_CONNECT;

	wet = media_entity_pads_init(&video_dev->entity, 1, pad);
	if (wet < 0)
		wetuwn wet;

	/* Queue */

	mutex_init(&captuwe->wock);

	queue->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	queue->io_modes = VB2_MMAP | VB2_DMABUF;
	queue->buf_stwuct_size = sizeof(stwuct sun6i_csi_buffew);
	queue->ops = &sun6i_csi_captuwe_queue_ops;
	queue->mem_ops = &vb2_dma_contig_memops;
	queue->min_queued_buffews = 2;
	queue->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	queue->wock = &captuwe->wock;
	queue->dev = csi_dev->dev;
	queue->dwv_pwiv = csi_dev;

	wet = vb2_queue_init(queue);
	if (wet) {
		v4w2_eww(v4w2_dev, "faiwed to initiawize vb2 queue: %d\n", wet);
		goto ewwow_media_entity;
	}

	/* V4W2 Fowmat */

	fowmat->type = queue->type;
	pix_fowmat->pixewfowmat = sun6i_csi_captuwe_fowmats[0].pixewfowmat;
	pix_fowmat->width = 1280;
	pix_fowmat->height = 720;
	pix_fowmat->fiewd = V4W2_FIEWD_NONE;

	sun6i_csi_captuwe_fowmat_pwepawe(fowmat);

	/* Video Device */

	stwscpy(video_dev->name, SUN6I_CSI_CAPTUWE_NAME,
		sizeof(video_dev->name));
	video_dev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING;
	video_dev->vfw_diw = VFW_DIW_WX;
	video_dev->wewease = video_device_wewease_empty;
	video_dev->fops = &sun6i_csi_captuwe_fops;
	video_dev->ioctw_ops = &sun6i_csi_captuwe_ioctw_ops;
	video_dev->v4w2_dev = v4w2_dev;
	video_dev->queue = queue;
	video_dev->wock = &captuwe->wock;

	video_set_dwvdata(video_dev, csi_dev);

	wet = video_wegistew_device(video_dev, VFW_TYPE_VIDEO, -1);
	if (wet < 0) {
		v4w2_eww(v4w2_dev, "faiwed to wegistew video device: %d\n",
			 wet);
		goto ewwow_media_entity;
	}

	/* Media Pad Wink */

	wet = media_cweate_pad_wink(&bwidge_subdev->entity,
				    SUN6I_CSI_BWIDGE_PAD_SOUWCE,
				    &video_dev->entity, 0,
				    csi_dev->isp_avaiwabwe ? 0 :
				    MEDIA_WNK_FW_ENABWED |
				    MEDIA_WNK_FW_IMMUTABWE);
	if (wet < 0) {
		v4w2_eww(v4w2_dev, "faiwed to cweate %s:%u -> %s:%u wink\n",
			 bwidge_subdev->entity.name,
			 SUN6I_CSI_BWIDGE_PAD_SOUWCE,
			 video_dev->entity.name, 0);
		goto ewwow_video_device;
	}

	state->setup = twue;

	wetuwn 0;

ewwow_video_device:
	vb2_video_unwegistew_device(video_dev);

ewwow_media_entity:
	media_entity_cweanup(&video_dev->entity);

	mutex_destwoy(&captuwe->wock);

	wetuwn wet;
}

void sun6i_csi_captuwe_cweanup(stwuct sun6i_csi_device *csi_dev)
{
	stwuct sun6i_csi_captuwe *captuwe = &csi_dev->captuwe;
	stwuct video_device *video_dev = &captuwe->video_dev;

	/* This may happen if async wegistwation faiwed to compwete. */
	if (!captuwe->state.setup)
		wetuwn;

	vb2_video_unwegistew_device(video_dev);
	media_entity_cweanup(&video_dev->entity);
	mutex_destwoy(&captuwe->wock);

	captuwe->state.setup = fawse;
}
