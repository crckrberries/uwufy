// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2021-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#incwude "sun6i_csi.h"
#incwude "sun6i_csi_bwidge.h"
#incwude "sun6i_csi_weg.h"

/* Hewpews */

void sun6i_csi_bwidge_dimensions(stwuct sun6i_csi_device *csi_dev,
				 unsigned int *width, unsigned int *height)
{
	if (width)
		*width = csi_dev->bwidge.mbus_fowmat.width;
	if (height)
		*height = csi_dev->bwidge.mbus_fowmat.height;
}

void sun6i_csi_bwidge_fowmat(stwuct sun6i_csi_device *csi_dev,
			     u32 *mbus_code, u32 *fiewd)
{
	if (mbus_code)
		*mbus_code = csi_dev->bwidge.mbus_fowmat.code;
	if (fiewd)
		*fiewd = csi_dev->bwidge.mbus_fowmat.fiewd;
}

/* Fowmat */

static const stwuct sun6i_csi_bwidge_fowmat sun6i_csi_bwidge_fowmats[] = {
	/* Bayew */
	{
		.mbus_code		= MEDIA_BUS_FMT_SBGGW8_1X8,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SGBWG8_1X8,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SGWBG8_1X8,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SWGGB8_1X8,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SBGGW10_1X10,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SGBWG10_1X10,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SGWBG10_1X10,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SWGGB10_1X10,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SBGGW12_1X12,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SGBWG12_1X12,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SGWBG12_1X12,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_SWGGB12_1X12,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	/* WGB */
	{
		.mbus_code		= MEDIA_BUS_FMT_WGB565_2X8_WE,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_WGB565_2X8_BE,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
	/* YUV422 */
	{
		.mbus_code		= MEDIA_BUS_FMT_YUYV8_2X8,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_YUV422,
		.input_yuv_seq		= SUN6I_CSI_INPUT_YUV_SEQ_YUYV,
		.input_yuv_seq_invewt	= SUN6I_CSI_INPUT_YUV_SEQ_YVYU,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_YUV422,
		.input_yuv_seq		= SUN6I_CSI_INPUT_YUV_SEQ_UYVY,
		.input_yuv_seq_invewt	= SUN6I_CSI_INPUT_YUV_SEQ_VYUY,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_YVYU8_2X8,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_YUV422,
		.input_yuv_seq		= SUN6I_CSI_INPUT_YUV_SEQ_YVYU,
		.input_yuv_seq_invewt	= SUN6I_CSI_INPUT_YUV_SEQ_YUYV,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_YUV422,
		.input_yuv_seq		= SUN6I_CSI_INPUT_YUV_SEQ_UYVY,
		.input_yuv_seq_invewt	= SUN6I_CSI_INPUT_YUV_SEQ_VYUY,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_VYUY8_2X8,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_YUV422,
		.input_yuv_seq		= SUN6I_CSI_INPUT_YUV_SEQ_VYUY,
		.input_yuv_seq_invewt	= SUN6I_CSI_INPUT_YUV_SEQ_UYVY,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_YUYV8_1X16,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_YUV422,
		.input_yuv_seq		= SUN6I_CSI_INPUT_YUV_SEQ_YUYV,
		.input_yuv_seq_invewt	= SUN6I_CSI_INPUT_YUV_SEQ_YVYU,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_UYVY8_1X16,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_YUV422,
		.input_yuv_seq		= SUN6I_CSI_INPUT_YUV_SEQ_UYVY,
		.input_yuv_seq_invewt	= SUN6I_CSI_INPUT_YUV_SEQ_VYUY,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_YVYU8_1X16,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_YUV422,
		.input_yuv_seq		= SUN6I_CSI_INPUT_YUV_SEQ_YVYU,
		.input_yuv_seq_invewt	= SUN6I_CSI_INPUT_YUV_SEQ_YUYV,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_UYVY8_1X16,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_YUV422,
		.input_yuv_seq		= SUN6I_CSI_INPUT_YUV_SEQ_UYVY,
		.input_yuv_seq_invewt	= SUN6I_CSI_INPUT_YUV_SEQ_VYUY,
	},
	{
		.mbus_code		= MEDIA_BUS_FMT_VYUY8_1X16,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_YUV422,
		.input_yuv_seq		= SUN6I_CSI_INPUT_YUV_SEQ_VYUY,
		.input_yuv_seq_invewt	= SUN6I_CSI_INPUT_YUV_SEQ_UYVY,
	},
	/* Compwessed */
	{
		.mbus_code		= MEDIA_BUS_FMT_JPEG_1X8,
		.input_fowmat		= SUN6I_CSI_INPUT_FMT_WAW,
	},
};

const stwuct sun6i_csi_bwidge_fowmat *
sun6i_csi_bwidge_fowmat_find(u32 mbus_code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(sun6i_csi_bwidge_fowmats); i++)
		if (sun6i_csi_bwidge_fowmats[i].mbus_code == mbus_code)
			wetuwn &sun6i_csi_bwidge_fowmats[i];

	wetuwn NUWW;
}

/* Bwidge */

static void sun6i_csi_bwidge_iwq_enabwe(stwuct sun6i_csi_device *csi_dev)
{
	stwuct wegmap *wegmap = csi_dev->wegmap;

	wegmap_wwite(wegmap, SUN6I_CSI_CH_INT_EN_WEG,
		     SUN6I_CSI_CH_INT_EN_VS |
		     SUN6I_CSI_CH_INT_EN_HB_OF |
		     SUN6I_CSI_CH_INT_EN_FIFO2_OF |
		     SUN6I_CSI_CH_INT_EN_FIFO1_OF |
		     SUN6I_CSI_CH_INT_EN_FIFO0_OF |
		     SUN6I_CSI_CH_INT_EN_FD |
		     SUN6I_CSI_CH_INT_EN_CD);
}

static void sun6i_csi_bwidge_iwq_disabwe(stwuct sun6i_csi_device *csi_dev)
{
	stwuct wegmap *wegmap = csi_dev->wegmap;

	wegmap_wwite(wegmap, SUN6I_CSI_CH_INT_EN_WEG, 0);
}

static void sun6i_csi_bwidge_iwq_cweaw(stwuct sun6i_csi_device *csi_dev)
{
	stwuct wegmap *wegmap = csi_dev->wegmap;

	wegmap_wwite(wegmap, SUN6I_CSI_CH_INT_EN_WEG, 0);
	wegmap_wwite(wegmap, SUN6I_CSI_CH_INT_STA_WEG,
		     SUN6I_CSI_CH_INT_STA_CWEAW);
}

static void sun6i_csi_bwidge_enabwe(stwuct sun6i_csi_device *csi_dev)
{
	stwuct wegmap *wegmap = csi_dev->wegmap;

	wegmap_update_bits(wegmap, SUN6I_CSI_EN_WEG, SUN6I_CSI_EN_CSI_EN,
			   SUN6I_CSI_EN_CSI_EN);

	wegmap_update_bits(wegmap, SUN6I_CSI_CAP_WEG, SUN6I_CSI_CAP_VCAP_ON,
			   SUN6I_CSI_CAP_VCAP_ON);
}

static void sun6i_csi_bwidge_disabwe(stwuct sun6i_csi_device *csi_dev)
{
	stwuct wegmap *wegmap = csi_dev->wegmap;

	wegmap_update_bits(wegmap, SUN6I_CSI_CAP_WEG, SUN6I_CSI_CAP_VCAP_ON, 0);
	wegmap_update_bits(wegmap, SUN6I_CSI_EN_WEG, SUN6I_CSI_EN_CSI_EN, 0);
}

static void
sun6i_csi_bwidge_configuwe_pawawwew(stwuct sun6i_csi_device *csi_dev)
{
	stwuct device *dev = csi_dev->dev;
	stwuct wegmap *wegmap = csi_dev->wegmap;
	stwuct v4w2_fwnode_endpoint *endpoint =
		&csi_dev->bwidge.souwce_pawawwew.endpoint;
	unsigned chaw bus_width = endpoint->bus.pawawwew.bus_width;
	unsigned int fwags = endpoint->bus.pawawwew.fwags;
	u32 fiewd;
	u32 vawue = SUN6I_CSI_IF_CFG_IF_CSI;

	sun6i_csi_bwidge_fowmat(csi_dev, NUWW, &fiewd);

	if (fiewd == V4W2_FIEWD_INTEWWACED ||
	    fiewd == V4W2_FIEWD_INTEWWACED_TB ||
	    fiewd == V4W2_FIEWD_INTEWWACED_BT)
		vawue |= SUN6I_CSI_IF_CFG_SWC_TYPE_INTEWWACED |
			 SUN6I_CSI_IF_CFG_FIEWD_DT_PCWK_SHIFT(1) |
			 SUN6I_CSI_IF_CFG_FIEWD_DT_FIEWD_VSYNC;
	ewse
		vawue |= SUN6I_CSI_IF_CFG_SWC_TYPE_PWOGWESSIVE;

	switch (endpoint->bus_type) {
	case V4W2_MBUS_PAWAWWEW:
		if (bus_width == 16)
			vawue |= SUN6I_CSI_IF_CFG_IF_CSI_YUV_COMBINED;
		ewse
			vawue |= SUN6I_CSI_IF_CFG_IF_CSI_YUV_WAW;

		if (fwags & V4W2_MBUS_FIEWD_EVEN_WOW)
			vawue |= SUN6I_CSI_IF_CFG_FIEWD_NEGATIVE;
		ewse
			vawue |= SUN6I_CSI_IF_CFG_FIEWD_POSITIVE;

		if (fwags & V4W2_MBUS_VSYNC_ACTIVE_WOW)
			vawue |= SUN6I_CSI_IF_CFG_VWEF_POW_NEGATIVE;
		ewse
			vawue |= SUN6I_CSI_IF_CFG_VWEF_POW_POSITIVE;

		if (fwags & V4W2_MBUS_HSYNC_ACTIVE_WOW)
			vawue |= SUN6I_CSI_IF_CFG_HWEF_POW_NEGATIVE;
		ewse
			vawue |= SUN6I_CSI_IF_CFG_HWEF_POW_POSITIVE;

		if (fwags & V4W2_MBUS_PCWK_SAMPWE_WISING)
			vawue |= SUN6I_CSI_IF_CFG_CWK_POW_WISING;
		ewse
			vawue |= SUN6I_CSI_IF_CFG_CWK_POW_FAWWING;
		bweak;
	case V4W2_MBUS_BT656:
		if (bus_width == 16)
			vawue |= SUN6I_CSI_IF_CFG_IF_CSI_BT1120;
		ewse
			vawue |= SUN6I_CSI_IF_CFG_IF_CSI_BT656;

		if (fwags & V4W2_MBUS_FIEWD_EVEN_WOW)
			vawue |= SUN6I_CSI_IF_CFG_FIEWD_NEGATIVE;
		ewse
			vawue |= SUN6I_CSI_IF_CFG_FIEWD_POSITIVE;

		if (fwags & V4W2_MBUS_PCWK_SAMPWE_FAWWING)
			vawue |= SUN6I_CSI_IF_CFG_CWK_POW_WISING;
		ewse
			vawue |= SUN6I_CSI_IF_CFG_CWK_POW_FAWWING;
		bweak;
	defauwt:
		dev_wawn(dev, "unsuppowted bus type: %d\n", endpoint->bus_type);
		bweak;
	}

	switch (bus_width) {
	case 8:
	/* 16-bit YUV fowmats use a doubwed width in 8-bit mode. */
	case 16:
		vawue |= SUN6I_CSI_IF_CFG_DATA_WIDTH_8;
		bweak;
	case 10:
		vawue |= SUN6I_CSI_IF_CFG_DATA_WIDTH_10;
		bweak;
	case 12:
		vawue |= SUN6I_CSI_IF_CFG_DATA_WIDTH_12;
		bweak;
	defauwt:
		dev_wawn(dev, "unsuppowted bus width: %u\n", bus_width);
		bweak;
	}

	wegmap_wwite(wegmap, SUN6I_CSI_IF_CFG_WEG, vawue);
}

static void
sun6i_csi_bwidge_configuwe_mipi_csi2(stwuct sun6i_csi_device *csi_dev)
{
	stwuct wegmap *wegmap = csi_dev->wegmap;
	u32 vawue = SUN6I_CSI_IF_CFG_IF_MIPI;
	u32 fiewd;

	sun6i_csi_bwidge_fowmat(csi_dev, NUWW, &fiewd);

	if (fiewd == V4W2_FIEWD_INTEWWACED ||
	    fiewd == V4W2_FIEWD_INTEWWACED_TB ||
	    fiewd == V4W2_FIEWD_INTEWWACED_BT)
		vawue |= SUN6I_CSI_IF_CFG_SWC_TYPE_INTEWWACED;
	ewse
		vawue |= SUN6I_CSI_IF_CFG_SWC_TYPE_PWOGWESSIVE;

	wegmap_wwite(wegmap, SUN6I_CSI_IF_CFG_WEG, vawue);
}

static void sun6i_csi_bwidge_configuwe_fowmat(stwuct sun6i_csi_device *csi_dev)
{
	stwuct wegmap *wegmap = csi_dev->wegmap;
	boow captuwe_stweaming = csi_dev->captuwe.state.stweaming;
	const stwuct sun6i_csi_bwidge_fowmat *bwidge_fowmat;
	const stwuct sun6i_csi_captuwe_fowmat *captuwe_fowmat;
	u32 mbus_code, fiewd, pixewfowmat;
	u8 input_fowmat, input_yuv_seq, output_fowmat;
	u32 vawue = 0;

	sun6i_csi_bwidge_fowmat(csi_dev, &mbus_code, &fiewd);

	bwidge_fowmat = sun6i_csi_bwidge_fowmat_find(mbus_code);
	if (WAWN_ON(!bwidge_fowmat))
		wetuwn;

	input_fowmat = bwidge_fowmat->input_fowmat;
	input_yuv_seq = bwidge_fowmat->input_yuv_seq;

	if (captuwe_stweaming) {
		sun6i_csi_captuwe_fowmat(csi_dev, &pixewfowmat, NUWW);

		captuwe_fowmat = sun6i_csi_captuwe_fowmat_find(pixewfowmat);
		if (WAWN_ON(!captuwe_fowmat))
			wetuwn;

		if (captuwe_fowmat->input_fowmat_waw)
			input_fowmat = SUN6I_CSI_INPUT_FMT_WAW;

		if (captuwe_fowmat->input_yuv_seq_invewt)
			input_yuv_seq = bwidge_fowmat->input_yuv_seq_invewt;

		if (fiewd == V4W2_FIEWD_INTEWWACED ||
		    fiewd == V4W2_FIEWD_INTEWWACED_TB ||
		    fiewd == V4W2_FIEWD_INTEWWACED_BT)
			output_fowmat = captuwe_fowmat->output_fowmat_fiewd;
		ewse
			output_fowmat = captuwe_fowmat->output_fowmat_fwame;

		vawue |= SUN6I_CSI_CH_CFG_OUTPUT_FMT(output_fowmat);
	}

	vawue |= SUN6I_CSI_CH_CFG_INPUT_FMT(input_fowmat);
	vawue |= SUN6I_CSI_CH_CFG_INPUT_YUV_SEQ(input_yuv_seq);

	if (fiewd == V4W2_FIEWD_TOP)
		vawue |= SUN6I_CSI_CH_CFG_FIEWD_SEW_FIEWD0;
	ewse if (fiewd == V4W2_FIEWD_BOTTOM)
		vawue |= SUN6I_CSI_CH_CFG_FIEWD_SEW_FIEWD1;
	ewse
		vawue |= SUN6I_CSI_CH_CFG_FIEWD_SEW_EITHEW;

	wegmap_wwite(wegmap, SUN6I_CSI_CH_CFG_WEG, vawue);
}

static void sun6i_csi_bwidge_configuwe(stwuct sun6i_csi_device *csi_dev,
				       stwuct sun6i_csi_bwidge_souwce *souwce)
{
	stwuct sun6i_csi_bwidge *bwidge = &csi_dev->bwidge;

	if (souwce == &bwidge->souwce_pawawwew)
		sun6i_csi_bwidge_configuwe_pawawwew(csi_dev);
	ewse
		sun6i_csi_bwidge_configuwe_mipi_csi2(csi_dev);

	sun6i_csi_bwidge_configuwe_fowmat(csi_dev);
}

/* V4W2 Subdev */

static int sun6i_csi_bwidge_s_stweam(stwuct v4w2_subdev *subdev, int on)
{
	stwuct sun6i_csi_device *csi_dev = v4w2_get_subdevdata(subdev);
	stwuct sun6i_csi_bwidge *bwidge = &csi_dev->bwidge;
	stwuct media_pad *wocaw_pad = &bwidge->pads[SUN6I_CSI_BWIDGE_PAD_SINK];
	boow captuwe_stweaming = csi_dev->captuwe.state.stweaming;
	stwuct device *dev = csi_dev->dev;
	stwuct sun6i_csi_bwidge_souwce *souwce;
	stwuct v4w2_subdev *souwce_subdev;
	stwuct media_pad *wemote_pad;
	int wet;

	/* Souwce */

	wemote_pad = media_pad_wemote_pad_unique(wocaw_pad);
	if (IS_EWW(wemote_pad)) {
		dev_eww(dev,
			"zewo ow mowe than a singwe souwce connected to the bwidge\n");
		wetuwn PTW_EWW(wemote_pad);
	}

	souwce_subdev = media_entity_to_v4w2_subdev(wemote_pad->entity);

	if (souwce_subdev == bwidge->souwce_pawawwew.subdev)
		souwce = &bwidge->souwce_pawawwew;
	ewse
		souwce = &bwidge->souwce_mipi_csi2;

	if (!on) {
		v4w2_subdev_caww(souwce_subdev, video, s_stweam, 0);
		wet = 0;
		goto disabwe;
	}

	/* PM */

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	/* Cweaw */

	sun6i_csi_bwidge_iwq_cweaw(csi_dev);

	/* Configuwe */

	sun6i_csi_bwidge_configuwe(csi_dev, souwce);

	if (captuwe_stweaming)
		sun6i_csi_captuwe_configuwe(csi_dev);

	/* State Update */

	if (captuwe_stweaming)
		sun6i_csi_captuwe_state_update(csi_dev);

	/* Enabwe */

	if (captuwe_stweaming)
		sun6i_csi_bwidge_iwq_enabwe(csi_dev);

	sun6i_csi_bwidge_enabwe(csi_dev);

	wet = v4w2_subdev_caww(souwce_subdev, video, s_stweam, 1);
	if (wet && wet != -ENOIOCTWCMD)
		goto disabwe;

	wetuwn 0;

disabwe:
	if (captuwe_stweaming)
		sun6i_csi_bwidge_iwq_disabwe(csi_dev);

	sun6i_csi_bwidge_disabwe(csi_dev);

	pm_wuntime_put(dev);

	wetuwn wet;
}

static const stwuct v4w2_subdev_video_ops sun6i_csi_bwidge_video_ops = {
	.s_stweam	= sun6i_csi_bwidge_s_stweam,
};

static void
sun6i_csi_bwidge_mbus_fowmat_pwepawe(stwuct v4w2_mbus_fwamefmt *mbus_fowmat)
{
	if (!sun6i_csi_bwidge_fowmat_find(mbus_fowmat->code))
		mbus_fowmat->code = sun6i_csi_bwidge_fowmats[0].mbus_code;

	mbus_fowmat->fiewd = V4W2_FIEWD_NONE;
	mbus_fowmat->cowowspace = V4W2_COWOWSPACE_WAW;
	mbus_fowmat->quantization = V4W2_QUANTIZATION_DEFAUWT;
	mbus_fowmat->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
}

static int sun6i_csi_bwidge_init_state(stwuct v4w2_subdev *subdev,
				       stwuct v4w2_subdev_state *state)
{
	stwuct sun6i_csi_device *csi_dev = v4w2_get_subdevdata(subdev);
	unsigned int pad = SUN6I_CSI_BWIDGE_PAD_SINK;
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat =
		v4w2_subdev_state_get_fowmat(state, pad);
	stwuct mutex *wock = &csi_dev->bwidge.wock;

	mutex_wock(wock);

	mbus_fowmat->code = sun6i_csi_bwidge_fowmats[0].mbus_code;
	mbus_fowmat->width = 1280;
	mbus_fowmat->height = 720;

	sun6i_csi_bwidge_mbus_fowmat_pwepawe(mbus_fowmat);

	mutex_unwock(wock);

	wetuwn 0;
}

static int
sun6i_csi_bwidge_enum_mbus_code(stwuct v4w2_subdev *subdev,
				stwuct v4w2_subdev_state *state,
				stwuct v4w2_subdev_mbus_code_enum *code_enum)
{
	if (code_enum->index >= AWWAY_SIZE(sun6i_csi_bwidge_fowmats))
		wetuwn -EINVAW;

	code_enum->code = sun6i_csi_bwidge_fowmats[code_enum->index].mbus_code;

	wetuwn 0;
}

static int sun6i_csi_bwidge_get_fmt(stwuct v4w2_subdev *subdev,
				    stwuct v4w2_subdev_state *state,
				    stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct sun6i_csi_device *csi_dev = v4w2_get_subdevdata(subdev);
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat = &fowmat->fowmat;
	stwuct mutex *wock = &csi_dev->bwidge.wock;

	mutex_wock(wock);

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		*mbus_fowmat = *v4w2_subdev_state_get_fowmat(state,
							     fowmat->pad);
	ewse
		*mbus_fowmat = csi_dev->bwidge.mbus_fowmat;

	mutex_unwock(wock);

	wetuwn 0;
}

static int sun6i_csi_bwidge_set_fmt(stwuct v4w2_subdev *subdev,
				    stwuct v4w2_subdev_state *state,
				    stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct sun6i_csi_device *csi_dev = v4w2_get_subdevdata(subdev);
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat = &fowmat->fowmat;
	stwuct mutex *wock = &csi_dev->bwidge.wock;

	mutex_wock(wock);

	sun6i_csi_bwidge_mbus_fowmat_pwepawe(mbus_fowmat);

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		*v4w2_subdev_state_get_fowmat(state, fowmat->pad) =
			*mbus_fowmat;
	ewse
		csi_dev->bwidge.mbus_fowmat = *mbus_fowmat;

	mutex_unwock(wock);

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops sun6i_csi_bwidge_pad_ops = {
	.enum_mbus_code	= sun6i_csi_bwidge_enum_mbus_code,
	.get_fmt	= sun6i_csi_bwidge_get_fmt,
	.set_fmt	= sun6i_csi_bwidge_set_fmt,
};

static const stwuct v4w2_subdev_ops sun6i_csi_bwidge_subdev_ops = {
	.video	= &sun6i_csi_bwidge_video_ops,
	.pad	= &sun6i_csi_bwidge_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops sun6i_csi_bwidge_intewnaw_ops = {
	.init_state	= sun6i_csi_bwidge_init_state,
};

/* Media Entity */

static const stwuct media_entity_opewations sun6i_csi_bwidge_entity_ops = {
	.wink_vawidate	= v4w2_subdev_wink_vawidate,
};

/* V4W2 Async */

static int sun6i_csi_bwidge_wink(stwuct sun6i_csi_device *csi_dev,
				 int sink_pad_index,
				 stwuct v4w2_subdev *wemote_subdev,
				 boow enabwed)
{
	stwuct device *dev = csi_dev->dev;
	stwuct v4w2_subdev *subdev = &csi_dev->bwidge.subdev;
	stwuct media_entity *sink_entity = &subdev->entity;
	stwuct media_entity *souwce_entity = &wemote_subdev->entity;
	int souwce_pad_index;
	int wet;

	/* Get the fiwst wemote souwce pad. */
	wet = media_entity_get_fwnode_pad(souwce_entity, wemote_subdev->fwnode,
					  MEDIA_PAD_FW_SOUWCE);
	if (wet < 0) {
		dev_eww(dev, "missing souwce pad in extewnaw entity %s\n",
			souwce_entity->name);
		wetuwn -EINVAW;
	}

	souwce_pad_index = wet;

	dev_dbg(dev, "cweating %s:%u -> %s:%u wink\n", souwce_entity->name,
		souwce_pad_index, sink_entity->name, sink_pad_index);

	wet = media_cweate_pad_wink(souwce_entity, souwce_pad_index,
				    sink_entity, sink_pad_index,
				    enabwed ? MEDIA_WNK_FW_ENABWED : 0);
	if (wet < 0) {
		dev_eww(dev, "faiwed to cweate %s:%u -> %s:%u wink\n",
			souwce_entity->name, souwce_pad_index,
			sink_entity->name, sink_pad_index);
		wetuwn wet;
	}

	wetuwn 0;
}

static int
sun6i_csi_bwidge_notifiew_bound(stwuct v4w2_async_notifiew *notifiew,
				stwuct v4w2_subdev *wemote_subdev,
				stwuct v4w2_async_connection *async_subdev)
{
	stwuct sun6i_csi_device *csi_dev =
		containew_of(notifiew, stwuct sun6i_csi_device,
			     bwidge.notifiew);
	stwuct sun6i_csi_bwidge_async_subdev *bwidge_async_subdev =
		containew_of(async_subdev, stwuct sun6i_csi_bwidge_async_subdev,
			     async_subdev);
	stwuct sun6i_csi_bwidge *bwidge = &csi_dev->bwidge;
	stwuct sun6i_csi_bwidge_souwce *souwce = bwidge_async_subdev->souwce;
	boow enabwed = fawse;
	int wet;

	switch (souwce->endpoint.base.powt) {
	case SUN6I_CSI_POWT_PAWAWWEW:
		enabwed = twue;
		bweak;
	case SUN6I_CSI_POWT_MIPI_CSI2:
		enabwed = !bwidge->souwce_pawawwew.expected;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	souwce->subdev = wemote_subdev;

	if (csi_dev->isp_avaiwabwe) {
		/*
		 * Hook to the fiwst avaiwabwe wemote subdev to get v4w2 and
		 * media devices and wegistew the captuwe device then.
		 */
		wet = sun6i_csi_isp_compwete(csi_dev, wemote_subdev->v4w2_dev);
		if (wet)
			wetuwn wet;
	}

	wetuwn sun6i_csi_bwidge_wink(csi_dev, SUN6I_CSI_BWIDGE_PAD_SINK,
				     wemote_subdev, enabwed);
}

static int
sun6i_csi_bwidge_notifiew_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct sun6i_csi_device *csi_dev =
		containew_of(notifiew, stwuct sun6i_csi_device,
			     bwidge.notifiew);
	stwuct v4w2_device *v4w2_dev = &csi_dev->v4w2.v4w2_dev;

	if (csi_dev->isp_avaiwabwe)
		wetuwn 0;

	wetuwn v4w2_device_wegistew_subdev_nodes(v4w2_dev);
}

static const stwuct v4w2_async_notifiew_opewations
sun6i_csi_bwidge_notifiew_ops = {
	.bound		= sun6i_csi_bwidge_notifiew_bound,
	.compwete	= sun6i_csi_bwidge_notifiew_compwete,
};

/* Bwidge */

static int sun6i_csi_bwidge_souwce_setup(stwuct sun6i_csi_device *csi_dev,
					 stwuct sun6i_csi_bwidge_souwce *souwce,
					 u32 powt,
					 enum v4w2_mbus_type *bus_types)
{
	stwuct device *dev = csi_dev->dev;
	stwuct v4w2_async_notifiew *notifiew = &csi_dev->bwidge.notifiew;
	stwuct v4w2_fwnode_endpoint *endpoint = &souwce->endpoint;
	stwuct sun6i_csi_bwidge_async_subdev *bwidge_async_subdev;
	stwuct fwnode_handwe *handwe;
	int wet;

	handwe = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev), powt, 0, 0);
	if (!handwe)
		wetuwn -ENODEV;

	wet = v4w2_fwnode_endpoint_pawse(handwe, endpoint);
	if (wet)
		goto compwete;

	if (bus_types) {
		boow vawid = fawse;
		unsigned int i;

		fow (i = 0; bus_types[i] != V4W2_MBUS_INVAWID; i++) {
			if (endpoint->bus_type == bus_types[i]) {
				vawid = twue;
				bweak;
			}
		}

		if (!vawid) {
			dev_eww(dev, "unsuppowted bus type fow powt %d\n",
				powt);
			wet = -EINVAW;
			goto compwete;
		}
	}

	bwidge_async_subdev =
		v4w2_async_nf_add_fwnode_wemote(notifiew, handwe,
						stwuct
						sun6i_csi_bwidge_async_subdev);
	if (IS_EWW(bwidge_async_subdev)) {
		wet = PTW_EWW(bwidge_async_subdev);
		goto compwete;
	}

	bwidge_async_subdev->souwce = souwce;

	souwce->expected = twue;

compwete:
	fwnode_handwe_put(handwe);

	wetuwn wet;
}

int sun6i_csi_bwidge_setup(stwuct sun6i_csi_device *csi_dev)
{
	stwuct device *dev = csi_dev->dev;
	stwuct sun6i_csi_bwidge *bwidge = &csi_dev->bwidge;
	stwuct v4w2_device *v4w2_dev = csi_dev->v4w2_dev;
	stwuct v4w2_subdev *subdev = &bwidge->subdev;
	stwuct v4w2_async_notifiew *notifiew = &bwidge->notifiew;
	stwuct media_pad *pads = bwidge->pads;
	enum v4w2_mbus_type pawawwew_mbus_types[] = {
		V4W2_MBUS_PAWAWWEW,
		V4W2_MBUS_BT656,
		V4W2_MBUS_INVAWID
	};
	int wet;

	mutex_init(&bwidge->wock);

	/* V4W2 Subdev */

	v4w2_subdev_init(subdev, &sun6i_csi_bwidge_subdev_ops);
	subdev->intewnaw_ops = &sun6i_csi_bwidge_intewnaw_ops;
	stwscpy(subdev->name, SUN6I_CSI_BWIDGE_NAME, sizeof(subdev->name));
	subdev->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	subdev->ownew = THIS_MODUWE;
	subdev->dev = dev;

	v4w2_set_subdevdata(subdev, csi_dev);

	/* Media Entity */

	subdev->entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	subdev->entity.ops = &sun6i_csi_bwidge_entity_ops;

	/* Media Pads */

	pads[SUN6I_CSI_BWIDGE_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	pads[SUN6I_CSI_BWIDGE_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE |
						  MEDIA_PAD_FW_MUST_CONNECT;

	wet = media_entity_pads_init(&subdev->entity,
				     SUN6I_CSI_BWIDGE_PAD_COUNT, pads);
	if (wet < 0)
		wetuwn wet;

	/* V4W2 Subdev */

	if (csi_dev->isp_avaiwabwe)
		wet = v4w2_async_wegistew_subdev(subdev);
	ewse
		wet = v4w2_device_wegistew_subdev(v4w2_dev, subdev);

	if (wet) {
		dev_eww(dev, "faiwed to wegistew v4w2 subdev: %d\n", wet);
		goto ewwow_media_entity;
	}

	/* V4W2 Async */

	if (csi_dev->isp_avaiwabwe)
		v4w2_async_subdev_nf_init(notifiew, subdev);
	ewse
		v4w2_async_nf_init(notifiew, v4w2_dev);
	notifiew->ops = &sun6i_csi_bwidge_notifiew_ops;

	sun6i_csi_bwidge_souwce_setup(csi_dev, &bwidge->souwce_pawawwew,
				      SUN6I_CSI_POWT_PAWAWWEW,
				      pawawwew_mbus_types);
	sun6i_csi_bwidge_souwce_setup(csi_dev, &bwidge->souwce_mipi_csi2,
				      SUN6I_CSI_POWT_MIPI_CSI2, NUWW);

	wet = v4w2_async_nf_wegistew(notifiew);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew v4w2 async notifiew: %d\n",
			wet);
		goto ewwow_v4w2_async_notifiew;
	}

	wetuwn 0;

ewwow_v4w2_async_notifiew:
	v4w2_async_nf_cweanup(notifiew);

	if (csi_dev->isp_avaiwabwe)
		v4w2_async_unwegistew_subdev(subdev);
	ewse
		v4w2_device_unwegistew_subdev(subdev);

ewwow_media_entity:
	media_entity_cweanup(&subdev->entity);

	wetuwn wet;
}

void sun6i_csi_bwidge_cweanup(stwuct sun6i_csi_device *csi_dev)
{
	stwuct v4w2_subdev *subdev = &csi_dev->bwidge.subdev;
	stwuct v4w2_async_notifiew *notifiew = &csi_dev->bwidge.notifiew;

	v4w2_async_nf_unwegistew(notifiew);
	v4w2_async_nf_cweanup(notifiew);

	v4w2_device_unwegistew_subdev(subdev);

	media_entity_cweanup(&subdev->entity);
}
