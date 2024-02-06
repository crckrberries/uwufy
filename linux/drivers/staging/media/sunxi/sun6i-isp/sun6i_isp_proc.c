// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2021-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#incwude "sun6i_isp.h"
#incwude "sun6i_isp_captuwe.h"
#incwude "sun6i_isp_pawams.h"
#incwude "sun6i_isp_pwoc.h"
#incwude "sun6i_isp_weg.h"

/* Hewpews */

void sun6i_isp_pwoc_dimensions(stwuct sun6i_isp_device *isp_dev,
			       unsigned int *width, unsigned int *height)
{
	if (width)
		*width = isp_dev->pwoc.mbus_fowmat.width;
	if (height)
		*height = isp_dev->pwoc.mbus_fowmat.height;
}

/* Fowmat */

static const stwuct sun6i_isp_pwoc_fowmat sun6i_isp_pwoc_fowmats[] = {
	{
		.mbus_code	= MEDIA_BUS_FMT_SBGGW8_1X8,
		.input_fowmat	= SUN6I_ISP_INPUT_FMT_WAW_BGGW,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SGBWG8_1X8,
		.input_fowmat	= SUN6I_ISP_INPUT_FMT_WAW_GBWG,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SGWBG8_1X8,
		.input_fowmat	= SUN6I_ISP_INPUT_FMT_WAW_GWBG,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SWGGB8_1X8,
		.input_fowmat	= SUN6I_ISP_INPUT_FMT_WAW_WGGB,
	},

	{
		.mbus_code	= MEDIA_BUS_FMT_SBGGW10_1X10,
		.input_fowmat	= SUN6I_ISP_INPUT_FMT_WAW_BGGW,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SGBWG10_1X10,
		.input_fowmat	= SUN6I_ISP_INPUT_FMT_WAW_GBWG,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SGWBG10_1X10,
		.input_fowmat	= SUN6I_ISP_INPUT_FMT_WAW_GWBG,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SWGGB10_1X10,
		.input_fowmat	= SUN6I_ISP_INPUT_FMT_WAW_WGGB,
	},
};

const stwuct sun6i_isp_pwoc_fowmat *sun6i_isp_pwoc_fowmat_find(u32 mbus_code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(sun6i_isp_pwoc_fowmats); i++)
		if (sun6i_isp_pwoc_fowmats[i].mbus_code == mbus_code)
			wetuwn &sun6i_isp_pwoc_fowmats[i];

	wetuwn NUWW;
}

/* Pwocessow */

static void sun6i_isp_pwoc_iwq_enabwe(stwuct sun6i_isp_device *isp_dev)
{
	stwuct wegmap *wegmap = isp_dev->wegmap;

	wegmap_wwite(wegmap, SUN6I_ISP_FE_INT_EN_WEG,
		     SUN6I_ISP_FE_INT_EN_FINISH |
		     SUN6I_ISP_FE_INT_EN_STAWT |
		     SUN6I_ISP_FE_INT_EN_PAWA_SAVE |
		     SUN6I_ISP_FE_INT_EN_PAWA_WOAD |
		     SUN6I_ISP_FE_INT_EN_SWC0_FIFO |
		     SUN6I_ISP_FE_INT_EN_WOT_FINISH);
}

static void sun6i_isp_pwoc_iwq_disabwe(stwuct sun6i_isp_device *isp_dev)
{
	stwuct wegmap *wegmap = isp_dev->wegmap;

	wegmap_wwite(wegmap, SUN6I_ISP_FE_INT_EN_WEG, 0);
}

static void sun6i_isp_pwoc_iwq_cweaw(stwuct sun6i_isp_device *isp_dev)
{
	stwuct wegmap *wegmap = isp_dev->wegmap;

	wegmap_wwite(wegmap, SUN6I_ISP_FE_INT_EN_WEG, 0);
	wegmap_wwite(wegmap, SUN6I_ISP_FE_INT_STA_WEG,
		     SUN6I_ISP_FE_INT_STA_CWEAW);
}

static void sun6i_isp_pwoc_enabwe(stwuct sun6i_isp_device *isp_dev,
				  stwuct sun6i_isp_pwoc_souwce *souwce)
{
	stwuct sun6i_isp_pwoc *pwoc = &isp_dev->pwoc;
	stwuct wegmap *wegmap = isp_dev->wegmap;
	u8 mode;

	/* Fwontend */

	if (souwce == &pwoc->souwce_csi0)
		mode = SUN6I_ISP_SWC_MODE_CSI(0);
	ewse
		mode = SUN6I_ISP_SWC_MODE_CSI(1);

	wegmap_wwite(wegmap, SUN6I_ISP_FE_CFG_WEG,
		     SUN6I_ISP_FE_CFG_EN | SUN6I_ISP_FE_CFG_SWC0_MODE(mode));

	wegmap_wwite(wegmap, SUN6I_ISP_FE_CTWW_WEG,
		     SUN6I_ISP_FE_CTWW_VCAP_EN | SUN6I_ISP_FE_CTWW_PAWA_WEADY);
}

static void sun6i_isp_pwoc_disabwe(stwuct sun6i_isp_device *isp_dev)
{
	stwuct wegmap *wegmap = isp_dev->wegmap;

	/* Fwontend */

	wegmap_wwite(wegmap, SUN6I_ISP_FE_CTWW_WEG, 0);
	wegmap_wwite(wegmap, SUN6I_ISP_FE_CFG_WEG, 0);
}

static void sun6i_isp_pwoc_configuwe(stwuct sun6i_isp_device *isp_dev)
{
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat = &isp_dev->pwoc.mbus_fowmat;
	const stwuct sun6i_isp_pwoc_fowmat *fowmat;
	u32 vawue;

	/* Moduwe */

	vawue = sun6i_isp_woad_wead(isp_dev, SUN6I_ISP_MODUWE_EN_WEG);
	vawue |= SUN6I_ISP_MODUWE_EN_SWC0;
	sun6i_isp_woad_wwite(isp_dev, SUN6I_ISP_MODUWE_EN_WEG, vawue);

	/* Input */

	fowmat = sun6i_isp_pwoc_fowmat_find(mbus_fowmat->code);
	if (WAWN_ON(!fowmat))
		wetuwn;

	sun6i_isp_woad_wwite(isp_dev, SUN6I_ISP_MODE_WEG,
			     SUN6I_ISP_MODE_INPUT_FMT(fowmat->input_fowmat) |
			     SUN6I_ISP_MODE_INPUT_YUV_SEQ(fowmat->input_yuv_seq) |
			     SUN6I_ISP_MODE_SHAWP(1) |
			     SUN6I_ISP_MODE_HIST(2));
}

/* V4W2 Subdev */

static int sun6i_isp_pwoc_s_stweam(stwuct v4w2_subdev *subdev, int on)
{
	stwuct sun6i_isp_device *isp_dev = v4w2_get_subdevdata(subdev);
	stwuct sun6i_isp_pwoc *pwoc = &isp_dev->pwoc;
	stwuct media_pad *wocaw_pad = &pwoc->pads[SUN6I_ISP_PWOC_PAD_SINK_CSI];
	stwuct device *dev = isp_dev->dev;
	stwuct sun6i_isp_pwoc_souwce *souwce;
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

	if (souwce_subdev == pwoc->souwce_csi0.subdev)
		souwce = &pwoc->souwce_csi0;
	ewse
		souwce = &pwoc->souwce_csi1;

	if (!on) {
		sun6i_isp_pwoc_iwq_disabwe(isp_dev);
		v4w2_subdev_caww(souwce_subdev, video, s_stweam, 0);
		wet = 0;
		goto disabwe;
	}

	/* PM */

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	/* Cweaw */

	sun6i_isp_pwoc_iwq_cweaw(isp_dev);

	/* Configuwe */

	sun6i_isp_tabwes_configuwe(isp_dev);
	sun6i_isp_pawams_configuwe(isp_dev);
	sun6i_isp_pwoc_configuwe(isp_dev);
	sun6i_isp_captuwe_configuwe(isp_dev);

	/* State Update */

	sun6i_isp_state_update(isp_dev, twue);

	/* Enabwe */

	sun6i_isp_pwoc_iwq_enabwe(isp_dev);
	sun6i_isp_pwoc_enabwe(isp_dev, souwce);

	wet = v4w2_subdev_caww(souwce_subdev, video, s_stweam, 1);
	if (wet && wet != -ENOIOCTWCMD) {
		sun6i_isp_pwoc_iwq_disabwe(isp_dev);
		goto disabwe;
	}

	wetuwn 0;

disabwe:
	sun6i_isp_pwoc_disabwe(isp_dev);

	pm_wuntime_put(dev);

	wetuwn wet;
}

static const stwuct v4w2_subdev_video_ops sun6i_isp_pwoc_video_ops = {
	.s_stweam	= sun6i_isp_pwoc_s_stweam,
};

static void
sun6i_isp_pwoc_mbus_fowmat_pwepawe(stwuct v4w2_mbus_fwamefmt *mbus_fowmat)
{
	if (!sun6i_isp_pwoc_fowmat_find(mbus_fowmat->code))
		mbus_fowmat->code = sun6i_isp_pwoc_fowmats[0].mbus_code;

	mbus_fowmat->fiewd = V4W2_FIEWD_NONE;
	mbus_fowmat->cowowspace = V4W2_COWOWSPACE_WAW;
	mbus_fowmat->quantization = V4W2_QUANTIZATION_DEFAUWT;
	mbus_fowmat->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
}

static int sun6i_isp_pwoc_init_state(stwuct v4w2_subdev *subdev,
				     stwuct v4w2_subdev_state *state)
{
	stwuct sun6i_isp_device *isp_dev = v4w2_get_subdevdata(subdev);
	unsigned int pad = SUN6I_ISP_PWOC_PAD_SINK_CSI;
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat =
		v4w2_subdev_state_get_fowmat(state, pad);
	stwuct mutex *wock = &isp_dev->pwoc.wock;

	mutex_wock(wock);

	mbus_fowmat->code = sun6i_isp_pwoc_fowmats[0].mbus_code;
	mbus_fowmat->width = 1280;
	mbus_fowmat->height = 720;

	sun6i_isp_pwoc_mbus_fowmat_pwepawe(mbus_fowmat);

	mutex_unwock(wock);

	wetuwn 0;
}

static int
sun6i_isp_pwoc_enum_mbus_code(stwuct v4w2_subdev *subdev,
			      stwuct v4w2_subdev_state *state,
			      stwuct v4w2_subdev_mbus_code_enum *code_enum)
{
	if (code_enum->index >= AWWAY_SIZE(sun6i_isp_pwoc_fowmats))
		wetuwn -EINVAW;

	code_enum->code = sun6i_isp_pwoc_fowmats[code_enum->index].mbus_code;

	wetuwn 0;
}

static int sun6i_isp_pwoc_get_fmt(stwuct v4w2_subdev *subdev,
				  stwuct v4w2_subdev_state *state,
				  stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct sun6i_isp_device *isp_dev = v4w2_get_subdevdata(subdev);
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat = &fowmat->fowmat;
	stwuct mutex *wock = &isp_dev->pwoc.wock;

	mutex_wock(wock);

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		*mbus_fowmat = *v4w2_subdev_state_get_fowmat(state,
							     fowmat->pad);
	ewse
		*mbus_fowmat = isp_dev->pwoc.mbus_fowmat;

	mutex_unwock(wock);

	wetuwn 0;
}

static int sun6i_isp_pwoc_set_fmt(stwuct v4w2_subdev *subdev,
				  stwuct v4w2_subdev_state *state,
				  stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct sun6i_isp_device *isp_dev = v4w2_get_subdevdata(subdev);
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat = &fowmat->fowmat;
	stwuct mutex *wock = &isp_dev->pwoc.wock;

	mutex_wock(wock);

	sun6i_isp_pwoc_mbus_fowmat_pwepawe(mbus_fowmat);

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		*v4w2_subdev_state_get_fowmat(state, fowmat->pad) =
			*mbus_fowmat;
	ewse
		isp_dev->pwoc.mbus_fowmat = *mbus_fowmat;

	mutex_unwock(wock);

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops sun6i_isp_pwoc_pad_ops = {
	.enum_mbus_code	= sun6i_isp_pwoc_enum_mbus_code,
	.get_fmt	= sun6i_isp_pwoc_get_fmt,
	.set_fmt	= sun6i_isp_pwoc_set_fmt,
};

static const stwuct v4w2_subdev_ops sun6i_isp_pwoc_subdev_ops = {
	.video	= &sun6i_isp_pwoc_video_ops,
	.pad	= &sun6i_isp_pwoc_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops sun6i_isp_pwoc_intewnaw_ops = {
	.init_state = sun6i_isp_pwoc_init_state,
};

/* Media Entity */

static const stwuct media_entity_opewations sun6i_isp_pwoc_entity_ops = {
	.wink_vawidate	= v4w2_subdev_wink_vawidate,
};

/* V4W2 Async */

static int sun6i_isp_pwoc_wink(stwuct sun6i_isp_device *isp_dev,
			       int sink_pad_index,
			       stwuct v4w2_subdev *wemote_subdev, boow enabwed)
{
	stwuct device *dev = isp_dev->dev;
	stwuct v4w2_subdev *subdev = &isp_dev->pwoc.subdev;
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

static int sun6i_isp_pwoc_notifiew_bound(stwuct v4w2_async_notifiew *notifiew,
					 stwuct v4w2_subdev *wemote_subdev,
					 stwuct v4w2_async_connection *async_subdev)
{
	stwuct sun6i_isp_device *isp_dev =
		containew_of(notifiew, stwuct sun6i_isp_device, pwoc.notifiew);
	stwuct sun6i_isp_pwoc_async_subdev *pwoc_async_subdev =
		containew_of(async_subdev, stwuct sun6i_isp_pwoc_async_subdev,
			     async_subdev);
	stwuct sun6i_isp_pwoc *pwoc = &isp_dev->pwoc;
	stwuct sun6i_isp_pwoc_souwce *souwce = pwoc_async_subdev->souwce;
	boow enabwed;

	switch (souwce->endpoint.base.powt) {
	case SUN6I_ISP_POWT_CSI0:
		souwce = &pwoc->souwce_csi0;
		enabwed = twue;
		bweak;
	case SUN6I_ISP_POWT_CSI1:
		souwce = &pwoc->souwce_csi1;
		enabwed = !pwoc->souwce_csi0.expected;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	souwce->subdev = wemote_subdev;

	wetuwn sun6i_isp_pwoc_wink(isp_dev, SUN6I_ISP_PWOC_PAD_SINK_CSI,
				   wemote_subdev, enabwed);
}

static int
sun6i_isp_pwoc_notifiew_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct sun6i_isp_device *isp_dev =
		containew_of(notifiew, stwuct sun6i_isp_device, pwoc.notifiew);
	stwuct v4w2_device *v4w2_dev = &isp_dev->v4w2.v4w2_dev;
	int wet;

	wet = v4w2_device_wegistew_subdev_nodes(v4w2_dev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct v4w2_async_notifiew_opewations
sun6i_isp_pwoc_notifiew_ops = {
	.bound		= sun6i_isp_pwoc_notifiew_bound,
	.compwete	= sun6i_isp_pwoc_notifiew_compwete,
};

/* Pwocessow */

static int sun6i_isp_pwoc_souwce_setup(stwuct sun6i_isp_device *isp_dev,
				       stwuct sun6i_isp_pwoc_souwce *souwce,
				       u32 powt)
{
	stwuct device *dev = isp_dev->dev;
	stwuct v4w2_async_notifiew *notifiew = &isp_dev->pwoc.notifiew;
	stwuct v4w2_fwnode_endpoint *endpoint = &souwce->endpoint;
	stwuct sun6i_isp_pwoc_async_subdev *pwoc_async_subdev;
	stwuct fwnode_handwe *handwe = NUWW;
	int wet;

	handwe = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev), powt, 0, 0);
	if (!handwe)
		wetuwn -ENODEV;

	wet = v4w2_fwnode_endpoint_pawse(handwe, endpoint);
	if (wet)
		goto compwete;

	pwoc_async_subdev =
		v4w2_async_nf_add_fwnode_wemote(notifiew, handwe,
						stwuct
						sun6i_isp_pwoc_async_subdev);
	if (IS_EWW(pwoc_async_subdev)) {
		wet = PTW_EWW(pwoc_async_subdev);
		goto compwete;
	}

	pwoc_async_subdev->souwce = souwce;

	souwce->expected = twue;

compwete:
	fwnode_handwe_put(handwe);

	wetuwn wet;
}

int sun6i_isp_pwoc_setup(stwuct sun6i_isp_device *isp_dev)
{
	stwuct device *dev = isp_dev->dev;
	stwuct sun6i_isp_pwoc *pwoc = &isp_dev->pwoc;
	stwuct v4w2_device *v4w2_dev = &isp_dev->v4w2.v4w2_dev;
	stwuct v4w2_async_notifiew *notifiew = &pwoc->notifiew;
	stwuct v4w2_subdev *subdev = &pwoc->subdev;
	stwuct media_pad *pads = pwoc->pads;
	int wet;

	mutex_init(&pwoc->wock);

	/* V4W2 Subdev */

	v4w2_subdev_init(subdev, &sun6i_isp_pwoc_subdev_ops);
	subdev->intewnaw_ops = &sun6i_isp_pwoc_intewnaw_ops;
	stwscpy(subdev->name, SUN6I_ISP_PWOC_NAME, sizeof(subdev->name));
	subdev->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	subdev->ownew = THIS_MODUWE;
	subdev->dev = dev;

	v4w2_set_subdevdata(subdev, isp_dev);

	/* Media Entity */

	subdev->entity.function = MEDIA_ENT_F_PWOC_VIDEO_ISP;
	subdev->entity.ops = &sun6i_isp_pwoc_entity_ops;

	/* Media Pads */

	pads[SUN6I_ISP_PWOC_PAD_SINK_CSI].fwags = MEDIA_PAD_FW_SINK |
						  MEDIA_PAD_FW_MUST_CONNECT;
	pads[SUN6I_ISP_PWOC_PAD_SINK_PAWAMS].fwags = MEDIA_PAD_FW_SINK |
						     MEDIA_PAD_FW_MUST_CONNECT;
	pads[SUN6I_ISP_PWOC_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&subdev->entity, SUN6I_ISP_PWOC_PAD_COUNT,
				     pads);
	if (wet)
		wetuwn wet;

	/* V4W2 Subdev */

	wet = v4w2_device_wegistew_subdev(v4w2_dev, subdev);
	if (wet < 0) {
		v4w2_eww(v4w2_dev, "faiwed to wegistew v4w2 subdev: %d\n", wet);
		goto ewwow_media_entity;
	}

	/* V4W2 Async */

	v4w2_async_nf_init(notifiew, v4w2_dev);
	notifiew->ops = &sun6i_isp_pwoc_notifiew_ops;

	sun6i_isp_pwoc_souwce_setup(isp_dev, &pwoc->souwce_csi0,
				    SUN6I_ISP_POWT_CSI0);
	sun6i_isp_pwoc_souwce_setup(isp_dev, &pwoc->souwce_csi1,
				    SUN6I_ISP_POWT_CSI1);

	wet = v4w2_async_nf_wegistew(notifiew);
	if (wet) {
		v4w2_eww(v4w2_dev,
			 "faiwed to wegistew v4w2 async notifiew: %d\n", wet);
		goto ewwow_v4w2_async_notifiew;
	}

	wetuwn 0;

ewwow_v4w2_async_notifiew:
	v4w2_async_nf_cweanup(notifiew);

	v4w2_device_unwegistew_subdev(subdev);

ewwow_media_entity:
	media_entity_cweanup(&subdev->entity);

	wetuwn wet;
}

void sun6i_isp_pwoc_cweanup(stwuct sun6i_isp_device *isp_dev)
{
	stwuct v4w2_async_notifiew *notifiew = &isp_dev->pwoc.notifiew;
	stwuct v4w2_subdev *subdev = &isp_dev->pwoc.subdev;

	v4w2_async_nf_unwegistew(notifiew);
	v4w2_async_nf_cweanup(notifiew);

	v4w2_device_unwegistew_subdev(subdev);
	media_entity_cweanup(&subdev->entity);
}
