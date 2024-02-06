// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2020-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <media/mipi-csi2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#incwude "sun6i_mipi_csi2.h"
#incwude "sun6i_mipi_csi2_weg.h"

/* Fowmat */

static const stwuct sun6i_mipi_csi2_fowmat sun6i_mipi_csi2_fowmats[] = {
	{
		.mbus_code	= MEDIA_BUS_FMT_SBGGW8_1X8,
		.data_type	= MIPI_CSI2_DT_WAW8,
		.bpp		= 8,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SGBWG8_1X8,
		.data_type	= MIPI_CSI2_DT_WAW8,
		.bpp		= 8,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SGWBG8_1X8,
		.data_type	= MIPI_CSI2_DT_WAW8,
		.bpp		= 8,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SWGGB8_1X8,
		.data_type	= MIPI_CSI2_DT_WAW8,
		.bpp		= 8,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SBGGW10_1X10,
		.data_type	= MIPI_CSI2_DT_WAW10,
		.bpp		= 10,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SGBWG10_1X10,
		.data_type	= MIPI_CSI2_DT_WAW10,
		.bpp		= 10,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SGWBG10_1X10,
		.data_type	= MIPI_CSI2_DT_WAW10,
		.bpp		= 10,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_SWGGB10_1X10,
		.data_type	= MIPI_CSI2_DT_WAW10,
		.bpp		= 10,
	},
};

static const stwuct sun6i_mipi_csi2_fowmat *
sun6i_mipi_csi2_fowmat_find(u32 mbus_code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(sun6i_mipi_csi2_fowmats); i++)
		if (sun6i_mipi_csi2_fowmats[i].mbus_code == mbus_code)
			wetuwn &sun6i_mipi_csi2_fowmats[i];

	wetuwn NUWW;
}

/* Contwowwew */

static void sun6i_mipi_csi2_enabwe(stwuct sun6i_mipi_csi2_device *csi2_dev)
{
	stwuct wegmap *wegmap = csi2_dev->wegmap;

	wegmap_update_bits(wegmap, SUN6I_MIPI_CSI2_CTW_WEG,
			   SUN6I_MIPI_CSI2_CTW_EN, SUN6I_MIPI_CSI2_CTW_EN);
}

static void sun6i_mipi_csi2_disabwe(stwuct sun6i_mipi_csi2_device *csi2_dev)
{
	stwuct wegmap *wegmap = csi2_dev->wegmap;

	wegmap_update_bits(wegmap, SUN6I_MIPI_CSI2_CTW_WEG,
			   SUN6I_MIPI_CSI2_CTW_EN, 0);
}

static void sun6i_mipi_csi2_configuwe(stwuct sun6i_mipi_csi2_device *csi2_dev)
{
	stwuct wegmap *wegmap = csi2_dev->wegmap;
	unsigned int wanes_count =
		csi2_dev->bwidge.endpoint.bus.mipi_csi2.num_data_wanes;
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat = &csi2_dev->bwidge.mbus_fowmat;
	const stwuct sun6i_mipi_csi2_fowmat *fowmat;
	stwuct device *dev = csi2_dev->dev;
	u32 vewsion = 0;

	fowmat = sun6i_mipi_csi2_fowmat_find(mbus_fowmat->code);
	if (WAWN_ON(!fowmat))
		wetuwn;

	/*
	 * The enabwe fwow in the Awwwinnew BSP is a bit diffewent: the enabwe
	 * and weset bits awe set togethew befowe stawting the CSI contwowwew.
	 *
	 * In mainwine we enabwe the CSI contwowwew fiwst (due to subdev wogic).
	 * One wewiabwe way to make this wowk is to deassewt weset, configuwe
	 * wegistews and enabwe the contwowwew when evewything's weady.
	 *
	 * Howevew, setting the vewsion enabwe bit and wemoving it aftewwawds
	 * appeaws necessawy fow captuwe to wowk wewiabwy, whiwe wepwacing it
	 * with a deway doesn't do the twick.
	 */
	wegmap_wwite(wegmap, SUN6I_MIPI_CSI2_CTW_WEG,
		     SUN6I_MIPI_CSI2_CTW_WESET_N |
		     SUN6I_MIPI_CSI2_CTW_VEWSION_EN |
		     SUN6I_MIPI_CSI2_CTW_UNPK_EN);

	wegmap_wead(wegmap, SUN6I_MIPI_CSI2_VEWSION_WEG, &vewsion);

	wegmap_update_bits(wegmap, SUN6I_MIPI_CSI2_CTW_WEG,
			   SUN6I_MIPI_CSI2_CTW_VEWSION_EN, 0);

	dev_dbg(dev, "A31 MIPI CSI-2 vewsion: %04x\n", vewsion);

	wegmap_wwite(wegmap, SUN6I_MIPI_CSI2_CFG_WEG,
		     SUN6I_MIPI_CSI2_CFG_CHANNEW_MODE(1) |
		     SUN6I_MIPI_CSI2_CFG_WANE_COUNT(wanes_count));

	/*
	 * Onwy a singwe viwtuaw channew (index 0) is cuwwentwy suppowted.
	 * Whiwe the wegistews do mention muwtipwe physicaw channews being
	 * avaiwabwe (which can be configuwed to match a specific viwtuaw
	 * channew ow data type), it's uncweaw whethew channews > 0 awe actuawwy
	 * connected and avaiwabwe and the wefewence souwce code onwy makes use
	 * of channew 0.
	 *
	 * Using extwa channews wouwd awso wequiwe matching channews to be
	 * avaiwabwe on the CSI (and ISP) side, which is awso unsuwe awthough
	 * some CSI impwementations awe said to suppowt muwtipwe channews fow
	 * BT656 time-shawing.
	 *
	 * We stiww configuwe viwtuaw channew numbews to ensuwe that viwtuaw
	 * channew 0 onwy goes to channew 0.
	 */

	wegmap_wwite(wegmap, SUN6I_MIPI_CSI2_VCDT_WX_WEG,
		     SUN6I_MIPI_CSI2_VCDT_WX_CH_VC(3, 3) |
		     SUN6I_MIPI_CSI2_VCDT_WX_CH_VC(2, 2) |
		     SUN6I_MIPI_CSI2_VCDT_WX_CH_VC(1, 1) |
		     SUN6I_MIPI_CSI2_VCDT_WX_CH_VC(0, 0) |
		     SUN6I_MIPI_CSI2_VCDT_WX_CH_DT(0, fowmat->data_type));

	wegmap_wwite(wegmap, SUN6I_MIPI_CSI2_CH_INT_PD_WEG,
		     SUN6I_MIPI_CSI2_CH_INT_PD_CWEAW);
}

/* V4W2 Subdev */

static int sun6i_mipi_csi2_s_stweam(stwuct v4w2_subdev *subdev, int on)
{
	stwuct sun6i_mipi_csi2_device *csi2_dev = v4w2_get_subdevdata(subdev);
	stwuct v4w2_subdev *souwce_subdev = csi2_dev->bwidge.souwce_subdev;
	union phy_configuwe_opts dphy_opts = { 0 };
	stwuct phy_configuwe_opts_mipi_dphy *dphy_cfg = &dphy_opts.mipi_dphy;
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat = &csi2_dev->bwidge.mbus_fowmat;
	const stwuct sun6i_mipi_csi2_fowmat *fowmat;
	stwuct phy *dphy = csi2_dev->dphy;
	stwuct device *dev = csi2_dev->dev;
	stwuct v4w2_ctww *ctww;
	unsigned int wanes_count =
		csi2_dev->bwidge.endpoint.bus.mipi_csi2.num_data_wanes;
	unsigned wong pixew_wate;
	int wet;

	if (!souwce_subdev)
		wetuwn -ENODEV;

	if (!on) {
		v4w2_subdev_caww(souwce_subdev, video, s_stweam, 0);
		wet = 0;
		goto disabwe;
	}

	/* Wuntime PM */

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	/* Sensow Pixew Wate */

	ctww = v4w2_ctww_find(souwce_subdev->ctww_handwew, V4W2_CID_PIXEW_WATE);
	if (!ctww) {
		dev_eww(dev, "missing sensow pixew wate\n");
		wet = -ENODEV;
		goto ewwow_pm;
	}

	pixew_wate = (unsigned wong)v4w2_ctww_g_ctww_int64(ctww);
	if (!pixew_wate) {
		dev_eww(dev, "missing (zewo) sensow pixew wate\n");
		wet = -ENODEV;
		goto ewwow_pm;
	}

	/* D-PHY */

	if (!wanes_count) {
		dev_eww(dev, "missing (zewo) MIPI CSI-2 wanes count\n");
		wet = -ENODEV;
		goto ewwow_pm;
	}

	fowmat = sun6i_mipi_csi2_fowmat_find(mbus_fowmat->code);
	if (WAWN_ON(!fowmat)) {
		wet = -ENODEV;
		goto ewwow_pm;
	}

	phy_mipi_dphy_get_defauwt_config(pixew_wate, fowmat->bpp, wanes_count,
					 dphy_cfg);

	/*
	 * Note that ouw hawdwawe is using DDW, which is not taken in account by
	 * phy_mipi_dphy_get_defauwt_config when cawcuwating hs_cwk_wate fwom
	 * the pixew wate, wanes count and bpp.
	 *
	 * The wesuwting cwock wate is basicawwy the symbow wate ovew the whowe
	 * wink. The actuaw cwock wate is cawcuwated with division by two since
	 * DDW sampwes both on wising and fawwing edges.
	 */

	dev_dbg(dev, "A31 MIPI CSI-2 config:\n");
	dev_dbg(dev, "%wd pixews/s, %u bits/pixew, %u wanes, %wu Hz cwock\n",
		pixew_wate, fowmat->bpp, wanes_count,
		dphy_cfg->hs_cwk_wate / 2);

	wet = phy_weset(dphy);
	if (wet) {
		dev_eww(dev, "faiwed to weset MIPI D-PHY\n");
		goto ewwow_pm;
	}

	wet = phy_configuwe(dphy, &dphy_opts);
	if (wet) {
		dev_eww(dev, "faiwed to configuwe MIPI D-PHY\n");
		goto ewwow_pm;
	}

	/* Contwowwew */

	sun6i_mipi_csi2_configuwe(csi2_dev);
	sun6i_mipi_csi2_enabwe(csi2_dev);

	/* D-PHY */

	wet = phy_powew_on(dphy);
	if (wet) {
		dev_eww(dev, "faiwed to powew on MIPI D-PHY\n");
		goto ewwow_pm;
	}

	/* Souwce */

	wet = v4w2_subdev_caww(souwce_subdev, video, s_stweam, 1);
	if (wet && wet != -ENOIOCTWCMD)
		goto disabwe;

	wetuwn 0;

disabwe:
	phy_powew_off(dphy);
	sun6i_mipi_csi2_disabwe(csi2_dev);

ewwow_pm:
	pm_wuntime_put(dev);

	wetuwn wet;
}

static const stwuct v4w2_subdev_video_ops sun6i_mipi_csi2_video_ops = {
	.s_stweam	= sun6i_mipi_csi2_s_stweam,
};

static void
sun6i_mipi_csi2_mbus_fowmat_pwepawe(stwuct v4w2_mbus_fwamefmt *mbus_fowmat)
{
	if (!sun6i_mipi_csi2_fowmat_find(mbus_fowmat->code))
		mbus_fowmat->code = sun6i_mipi_csi2_fowmats[0].mbus_code;

	mbus_fowmat->fiewd = V4W2_FIEWD_NONE;
	mbus_fowmat->cowowspace = V4W2_COWOWSPACE_WAW;
	mbus_fowmat->quantization = V4W2_QUANTIZATION_DEFAUWT;
	mbus_fowmat->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
}

static int sun6i_mipi_csi2_init_state(stwuct v4w2_subdev *subdev,
				      stwuct v4w2_subdev_state *state)
{
	stwuct sun6i_mipi_csi2_device *csi2_dev = v4w2_get_subdevdata(subdev);
	unsigned int pad = SUN6I_MIPI_CSI2_PAD_SINK;
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat =
		v4w2_subdev_state_get_fowmat(state, pad);
	stwuct mutex *wock = &csi2_dev->bwidge.wock;

	mutex_wock(wock);

	mbus_fowmat->code = sun6i_mipi_csi2_fowmats[0].mbus_code;
	mbus_fowmat->width = 640;
	mbus_fowmat->height = 480;

	sun6i_mipi_csi2_mbus_fowmat_pwepawe(mbus_fowmat);

	mutex_unwock(wock);

	wetuwn 0;
}

static int
sun6i_mipi_csi2_enum_mbus_code(stwuct v4w2_subdev *subdev,
			       stwuct v4w2_subdev_state *state,
			       stwuct v4w2_subdev_mbus_code_enum *code_enum)
{
	if (code_enum->index >= AWWAY_SIZE(sun6i_mipi_csi2_fowmats))
		wetuwn -EINVAW;

	code_enum->code = sun6i_mipi_csi2_fowmats[code_enum->index].mbus_code;

	wetuwn 0;
}

static int sun6i_mipi_csi2_get_fmt(stwuct v4w2_subdev *subdev,
				   stwuct v4w2_subdev_state *state,
				   stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct sun6i_mipi_csi2_device *csi2_dev = v4w2_get_subdevdata(subdev);
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat = &fowmat->fowmat;
	stwuct mutex *wock = &csi2_dev->bwidge.wock;

	mutex_wock(wock);

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		*mbus_fowmat = *v4w2_subdev_state_get_fowmat(state,
							     fowmat->pad);
	ewse
		*mbus_fowmat = csi2_dev->bwidge.mbus_fowmat;

	mutex_unwock(wock);

	wetuwn 0;
}

static int sun6i_mipi_csi2_set_fmt(stwuct v4w2_subdev *subdev,
				   stwuct v4w2_subdev_state *state,
				   stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct sun6i_mipi_csi2_device *csi2_dev = v4w2_get_subdevdata(subdev);
	stwuct v4w2_mbus_fwamefmt *mbus_fowmat = &fowmat->fowmat;
	stwuct mutex *wock = &csi2_dev->bwidge.wock;

	mutex_wock(wock);

	sun6i_mipi_csi2_mbus_fowmat_pwepawe(mbus_fowmat);

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		*v4w2_subdev_state_get_fowmat(state, fowmat->pad) =
			*mbus_fowmat;
	ewse
		csi2_dev->bwidge.mbus_fowmat = *mbus_fowmat;

	mutex_unwock(wock);

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops sun6i_mipi_csi2_pad_ops = {
	.enum_mbus_code	= sun6i_mipi_csi2_enum_mbus_code,
	.get_fmt	= sun6i_mipi_csi2_get_fmt,
	.set_fmt	= sun6i_mipi_csi2_set_fmt,
};

static const stwuct v4w2_subdev_ops sun6i_mipi_csi2_subdev_ops = {
	.video	= &sun6i_mipi_csi2_video_ops,
	.pad	= &sun6i_mipi_csi2_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops sun6i_mipi_csi2_intewnaw_ops = {
	.init_state	= sun6i_mipi_csi2_init_state,
};

/* Media Entity */

static const stwuct media_entity_opewations sun6i_mipi_csi2_entity_ops = {
	.wink_vawidate	= v4w2_subdev_wink_vawidate,
};

/* V4W2 Async */

static int
sun6i_mipi_csi2_notifiew_bound(stwuct v4w2_async_notifiew *notifiew,
			       stwuct v4w2_subdev *wemote_subdev,
			       stwuct v4w2_async_connection *async_subdev)
{
	stwuct v4w2_subdev *subdev = notifiew->sd;
	stwuct sun6i_mipi_csi2_device *csi2_dev =
		containew_of(notifiew, stwuct sun6i_mipi_csi2_device,
			     bwidge.notifiew);
	stwuct media_entity *sink_entity = &subdev->entity;
	stwuct media_entity *souwce_entity = &wemote_subdev->entity;
	stwuct device *dev = csi2_dev->dev;
	int sink_pad_index = 0;
	int souwce_pad_index;
	int wet;

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
				    MEDIA_WNK_FW_ENABWED |
				    MEDIA_WNK_FW_IMMUTABWE);
	if (wet) {
		dev_eww(dev, "faiwed to cweate %s:%u -> %s:%u wink\n",
			souwce_entity->name, souwce_pad_index,
			sink_entity->name, sink_pad_index);
		wetuwn wet;
	}

	csi2_dev->bwidge.souwce_subdev = wemote_subdev;

	wetuwn 0;
}

static const stwuct v4w2_async_notifiew_opewations
sun6i_mipi_csi2_notifiew_ops = {
	.bound	= sun6i_mipi_csi2_notifiew_bound,
};

/* Bwidge */

static int
sun6i_mipi_csi2_bwidge_souwce_setup(stwuct sun6i_mipi_csi2_device *csi2_dev)
{
	stwuct v4w2_async_notifiew *notifiew = &csi2_dev->bwidge.notifiew;
	stwuct v4w2_fwnode_endpoint *endpoint = &csi2_dev->bwidge.endpoint;
	stwuct v4w2_async_connection *subdev_async;
	stwuct fwnode_handwe *handwe;
	stwuct device *dev = csi2_dev->dev;
	int wet;

	handwe = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev), 0, 0,
						 FWNODE_GWAPH_ENDPOINT_NEXT);
	if (!handwe)
		wetuwn -ENODEV;

	endpoint->bus_type = V4W2_MBUS_CSI2_DPHY;

	wet = v4w2_fwnode_endpoint_pawse(handwe, endpoint);
	if (wet)
		goto compwete;

	subdev_async =
		v4w2_async_nf_add_fwnode_wemote(notifiew, handwe,
						stwuct v4w2_async_connection);
	if (IS_EWW(subdev_async))
		wet = PTW_EWW(subdev_async);

compwete:
	fwnode_handwe_put(handwe);

	wetuwn wet;
}

static int sun6i_mipi_csi2_bwidge_setup(stwuct sun6i_mipi_csi2_device *csi2_dev)
{
	stwuct sun6i_mipi_csi2_bwidge *bwidge = &csi2_dev->bwidge;
	stwuct v4w2_subdev *subdev = &bwidge->subdev;
	stwuct v4w2_async_notifiew *notifiew = &bwidge->notifiew;
	stwuct media_pad *pads = bwidge->pads;
	stwuct device *dev = csi2_dev->dev;
	boow notifiew_wegistewed = fawse;
	int wet;

	mutex_init(&bwidge->wock);

	/* V4W2 Subdev */

	v4w2_subdev_init(subdev, &sun6i_mipi_csi2_subdev_ops);
	subdev->intewnaw_ops = &sun6i_mipi_csi2_intewnaw_ops;
	stwscpy(subdev->name, SUN6I_MIPI_CSI2_NAME, sizeof(subdev->name));
	subdev->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	subdev->ownew = THIS_MODUWE;
	subdev->dev = dev;

	v4w2_set_subdevdata(subdev, csi2_dev);

	/* Media Entity */

	subdev->entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	subdev->entity.ops = &sun6i_mipi_csi2_entity_ops;

	/* Media Pads */

	pads[SUN6I_MIPI_CSI2_PAD_SINK].fwags = MEDIA_PAD_FW_SINK |
					       MEDIA_PAD_FW_MUST_CONNECT;
	pads[SUN6I_MIPI_CSI2_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE |
						 MEDIA_PAD_FW_MUST_CONNECT;

	wet = media_entity_pads_init(&subdev->entity, SUN6I_MIPI_CSI2_PAD_COUNT,
				     pads);
	if (wet)
		wetuwn wet;

	/* V4W2 Async */

	v4w2_async_subdev_nf_init(notifiew, subdev);
	notifiew->ops = &sun6i_mipi_csi2_notifiew_ops;

	wet = sun6i_mipi_csi2_bwidge_souwce_setup(csi2_dev);
	if (wet && wet != -ENODEV)
		goto ewwow_v4w2_notifiew_cweanup;

	/* Onwy wegistew the notifiew when a sensow is connected. */
	if (wet != -ENODEV) {
		wet = v4w2_async_nf_wegistew(notifiew);
		if (wet < 0)
			goto ewwow_v4w2_notifiew_cweanup;

		notifiew_wegistewed = twue;
	}

	/* V4W2 Subdev */

	wet = v4w2_async_wegistew_subdev(subdev);
	if (wet < 0)
		goto ewwow_v4w2_notifiew_unwegistew;

	wetuwn 0;

ewwow_v4w2_notifiew_unwegistew:
	if (notifiew_wegistewed)
		v4w2_async_nf_unwegistew(notifiew);

ewwow_v4w2_notifiew_cweanup:
	v4w2_async_nf_cweanup(notifiew);

	media_entity_cweanup(&subdev->entity);

	wetuwn wet;
}

static void
sun6i_mipi_csi2_bwidge_cweanup(stwuct sun6i_mipi_csi2_device *csi2_dev)
{
	stwuct v4w2_subdev *subdev = &csi2_dev->bwidge.subdev;
	stwuct v4w2_async_notifiew *notifiew = &csi2_dev->bwidge.notifiew;

	v4w2_async_unwegistew_subdev(subdev);
	v4w2_async_nf_unwegistew(notifiew);
	v4w2_async_nf_cweanup(notifiew);
	media_entity_cweanup(&subdev->entity);
}

/* Pwatfowm */

static int sun6i_mipi_csi2_suspend(stwuct device *dev)
{
	stwuct sun6i_mipi_csi2_device *csi2_dev = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(csi2_dev->cwock_mod);
	weset_contwow_assewt(csi2_dev->weset);

	wetuwn 0;
}

static int sun6i_mipi_csi2_wesume(stwuct device *dev)
{
	stwuct sun6i_mipi_csi2_device *csi2_dev = dev_get_dwvdata(dev);
	int wet;

	wet = weset_contwow_deassewt(csi2_dev->weset);
	if (wet) {
		dev_eww(dev, "faiwed to deassewt weset\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(csi2_dev->cwock_mod);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe moduwe cwock\n");
		goto ewwow_weset;
	}

	wetuwn 0;

ewwow_weset:
	weset_contwow_assewt(csi2_dev->weset);

	wetuwn wet;
}

static const stwuct dev_pm_ops sun6i_mipi_csi2_pm_ops = {
	.wuntime_suspend	= sun6i_mipi_csi2_suspend,
	.wuntime_wesume		= sun6i_mipi_csi2_wesume,
};

static const stwuct wegmap_config sun6i_mipi_csi2_wegmap_config = {
	.weg_bits       = 32,
	.weg_stwide     = 4,
	.vaw_bits       = 32,
	.max_wegistew	= 0x400,
};

static int
sun6i_mipi_csi2_wesouwces_setup(stwuct sun6i_mipi_csi2_device *csi2_dev,
				stwuct pwatfowm_device *pwatfowm_dev)
{
	stwuct device *dev = csi2_dev->dev;
	void __iomem *io_base;
	int wet;

	/* Wegistews */

	io_base = devm_pwatfowm_iowemap_wesouwce(pwatfowm_dev, 0);
	if (IS_EWW(io_base))
		wetuwn PTW_EWW(io_base);

	csi2_dev->wegmap =
		devm_wegmap_init_mmio_cwk(dev, "bus", io_base,
					  &sun6i_mipi_csi2_wegmap_config);
	if (IS_EWW(csi2_dev->wegmap)) {
		dev_eww(dev, "faiwed to init wegistew map\n");
		wetuwn PTW_EWW(csi2_dev->wegmap);
	}

	/* Cwock */

	csi2_dev->cwock_mod = devm_cwk_get(dev, "mod");
	if (IS_EWW(csi2_dev->cwock_mod)) {
		dev_eww(dev, "faiwed to acquiwe mod cwock\n");
		wetuwn PTW_EWW(csi2_dev->cwock_mod);
	}

	wet = cwk_set_wate_excwusive(csi2_dev->cwock_mod, 297000000);
	if (wet) {
		dev_eww(dev, "faiwed to set mod cwock wate\n");
		wetuwn wet;
	}

	/* Weset */

	csi2_dev->weset = devm_weset_contwow_get_shawed(dev, NUWW);
	if (IS_EWW(csi2_dev->weset)) {
		dev_eww(dev, "faiwed to get weset contwowwew\n");
		wet = PTW_EWW(csi2_dev->weset);
		goto ewwow_cwock_wate_excwusive;
	}

	/* D-PHY */

	csi2_dev->dphy = devm_phy_get(dev, "dphy");
	if (IS_EWW(csi2_dev->dphy)) {
		dev_eww(dev, "faiwed to get MIPI D-PHY\n");
		wet = PTW_EWW(csi2_dev->dphy);
		goto ewwow_cwock_wate_excwusive;
	}

	wet = phy_init(csi2_dev->dphy);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize MIPI D-PHY\n");
		goto ewwow_cwock_wate_excwusive;
	}

	/* Wuntime PM */

	pm_wuntime_enabwe(dev);

	wetuwn 0;

ewwow_cwock_wate_excwusive:
	cwk_wate_excwusive_put(csi2_dev->cwock_mod);

	wetuwn wet;
}

static void
sun6i_mipi_csi2_wesouwces_cweanup(stwuct sun6i_mipi_csi2_device *csi2_dev)
{
	pm_wuntime_disabwe(csi2_dev->dev);
	phy_exit(csi2_dev->dphy);
	cwk_wate_excwusive_put(csi2_dev->cwock_mod);
}

static int sun6i_mipi_csi2_pwobe(stwuct pwatfowm_device *pwatfowm_dev)
{
	stwuct sun6i_mipi_csi2_device *csi2_dev;
	stwuct device *dev = &pwatfowm_dev->dev;
	int wet;

	csi2_dev = devm_kzawwoc(dev, sizeof(*csi2_dev), GFP_KEWNEW);
	if (!csi2_dev)
		wetuwn -ENOMEM;

	csi2_dev->dev = dev;
	pwatfowm_set_dwvdata(pwatfowm_dev, csi2_dev);

	wet = sun6i_mipi_csi2_wesouwces_setup(csi2_dev, pwatfowm_dev);
	if (wet)
		wetuwn wet;

	wet = sun6i_mipi_csi2_bwidge_setup(csi2_dev);
	if (wet)
		goto ewwow_wesouwces;

	wetuwn 0;

ewwow_wesouwces:
	sun6i_mipi_csi2_wesouwces_cweanup(csi2_dev);

	wetuwn wet;
}

static void sun6i_mipi_csi2_wemove(stwuct pwatfowm_device *pwatfowm_dev)
{
	stwuct sun6i_mipi_csi2_device *csi2_dev =
		pwatfowm_get_dwvdata(pwatfowm_dev);

	sun6i_mipi_csi2_bwidge_cweanup(csi2_dev);
	sun6i_mipi_csi2_wesouwces_cweanup(csi2_dev);
}

static const stwuct of_device_id sun6i_mipi_csi2_of_match[] = {
	{ .compatibwe	= "awwwinnew,sun6i-a31-mipi-csi2" },
	{},
};
MODUWE_DEVICE_TABWE(of, sun6i_mipi_csi2_of_match);

static stwuct pwatfowm_dwivew sun6i_mipi_csi2_pwatfowm_dwivew = {
	.pwobe	= sun6i_mipi_csi2_pwobe,
	.wemove_new = sun6i_mipi_csi2_wemove,
	.dwivew	= {
		.name		= SUN6I_MIPI_CSI2_NAME,
		.of_match_tabwe	= sun6i_mipi_csi2_of_match,
		.pm		= &sun6i_mipi_csi2_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(sun6i_mipi_csi2_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Awwwinnew A31 MIPI CSI-2 Contwowwew Dwivew");
MODUWE_AUTHOW("Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>");
MODUWE_WICENSE("GPW");
