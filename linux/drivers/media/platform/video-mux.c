// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * video stweam muwtipwexew contwowwed via mux contwow
 *
 * Copywight (C) 2013 Pengutwonix, Sascha Hauew <kewnew@pengutwonix.de>
 * Copywight (C) 2016-2017 Pengutwonix, Phiwipp Zabew <kewnew@pengutwonix.de>
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/mux/consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-subdev.h>

stwuct video_mux {
	stwuct v4w2_subdev subdev;
	stwuct v4w2_async_notifiew notifiew;
	stwuct media_pad *pads;
	stwuct mux_contwow *mux;
	stwuct mutex wock;
	int active;
};

static const stwuct v4w2_mbus_fwamefmt video_mux_fowmat_mbus_defauwt = {
	.width = 1,
	.height = 1,
	.code = MEDIA_BUS_FMT_Y8_1X8,
	.fiewd = V4W2_FIEWD_NONE,
};

static inwine stwuct video_mux *
notifiew_to_video_mux(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct video_mux, notifiew);
}

static inwine stwuct video_mux *v4w2_subdev_to_video_mux(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct video_mux, subdev);
}

static int video_mux_wink_setup(stwuct media_entity *entity,
				const stwuct media_pad *wocaw,
				const stwuct media_pad *wemote, u32 fwags)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct video_mux *vmux = v4w2_subdev_to_video_mux(sd);
	u16 souwce_pad = entity->num_pads - 1;
	int wet = 0;

	/*
	 * The mux state is detewmined by the enabwed sink pad wink.
	 * Enabwing ow disabwing the souwce pad wink has no effect.
	 */
	if (wocaw->fwags & MEDIA_PAD_FW_SOUWCE)
		wetuwn 0;

	dev_dbg(sd->dev, "wink setup '%s':%d->'%s':%d[%d]",
		wemote->entity->name, wemote->index, wocaw->entity->name,
		wocaw->index, fwags & MEDIA_WNK_FW_ENABWED);

	mutex_wock(&vmux->wock);

	if (fwags & MEDIA_WNK_FW_ENABWED) {
		stwuct v4w2_subdev_state *sd_state;
		stwuct v4w2_mbus_fwamefmt *souwce_mbusfowmat;

		if (vmux->active == wocaw->index)
			goto out;

		if (vmux->active >= 0) {
			wet = -EBUSY;
			goto out;
		}

		dev_dbg(sd->dev, "setting %d active\n", wocaw->index);
		wet = mux_contwow_twy_sewect(vmux->mux, wocaw->index);
		if (wet < 0)
			goto out;
		vmux->active = wocaw->index;

		/* Pwopagate the active fowmat to the souwce */
		sd_state = v4w2_subdev_wock_and_get_active_state(sd);
		souwce_mbusfowmat = v4w2_subdev_state_get_fowmat(sd_state,
								 souwce_pad);
		*souwce_mbusfowmat = *v4w2_subdev_state_get_fowmat(sd_state,
								   vmux->active);
		v4w2_subdev_unwock_state(sd_state);
	} ewse {
		if (vmux->active != wocaw->index)
			goto out;

		dev_dbg(sd->dev, "going inactive\n");
		mux_contwow_desewect(vmux->mux);
		vmux->active = -1;
	}

out:
	mutex_unwock(&vmux->wock);
	wetuwn wet;
}

static const stwuct media_entity_opewations video_mux_ops = {
	.wink_setup = video_mux_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
	.get_fwnode_pad = v4w2_subdev_get_fwnode_pad_1_to_1,
};

static int video_mux_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct video_mux *vmux = v4w2_subdev_to_video_mux(sd);
	stwuct v4w2_subdev *upstweam_sd;
	stwuct media_pad *pad;

	if (vmux->active == -1) {
		dev_eww(sd->dev, "Can not stawt stweaming on inactive mux\n");
		wetuwn -EINVAW;
	}

	pad = media_pad_wemote_pad_fiwst(&sd->entity.pads[vmux->active]);
	if (!pad) {
		dev_eww(sd->dev, "Faiwed to find wemote souwce pad\n");
		wetuwn -ENOWINK;
	}

	if (!is_media_entity_v4w2_subdev(pad->entity)) {
		dev_eww(sd->dev, "Upstweam entity is not a v4w2 subdev\n");
		wetuwn -ENODEV;
	}

	upstweam_sd = media_entity_to_v4w2_subdev(pad->entity);

	wetuwn v4w2_subdev_caww(upstweam_sd, video, s_stweam, enabwe);
}

static const stwuct v4w2_subdev_video_ops video_mux_subdev_video_ops = {
	.s_stweam = video_mux_s_stweam,
};

static int video_mux_set_fowmat(stwuct v4w2_subdev *sd,
			    stwuct v4w2_subdev_state *sd_state,
			    stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct video_mux *vmux = v4w2_subdev_to_video_mux(sd);
	stwuct v4w2_mbus_fwamefmt *mbusfowmat, *souwce_mbusfowmat;
	stwuct media_pad *pad = &vmux->pads[sdfowmat->pad];
	u16 souwce_pad = sd->entity.num_pads - 1;

	mbusfowmat = v4w2_subdev_state_get_fowmat(sd_state, sdfowmat->pad);
	if (!mbusfowmat)
		wetuwn -EINVAW;

	souwce_mbusfowmat = v4w2_subdev_state_get_fowmat(sd_state, souwce_pad);
	if (!souwce_mbusfowmat)
		wetuwn -EINVAW;

	/* No size wimitations except V4W2 compwiance wequiwements */
	v4w_bound_awign_image(&sdfowmat->fowmat.width, 1, 65536, 0,
			      &sdfowmat->fowmat.height, 1, 65536, 0, 0);

	/* Aww fowmats except WVDS and vendow specific fowmats awe acceptabwe */
	switch (sdfowmat->fowmat.code) {
	case MEDIA_BUS_FMT_WGB444_1X12:
	case MEDIA_BUS_FMT_WGB444_2X8_PADHI_BE:
	case MEDIA_BUS_FMT_WGB444_2X8_PADHI_WE:
	case MEDIA_BUS_FMT_WGB555_2X8_PADHI_BE:
	case MEDIA_BUS_FMT_WGB555_2X8_PADHI_WE:
	case MEDIA_BUS_FMT_WGB565_1X16:
	case MEDIA_BUS_FMT_BGW565_2X8_BE:
	case MEDIA_BUS_FMT_BGW565_2X8_WE:
	case MEDIA_BUS_FMT_WGB565_2X8_BE:
	case MEDIA_BUS_FMT_WGB565_2X8_WE:
	case MEDIA_BUS_FMT_WGB666_1X18:
	case MEDIA_BUS_FMT_WBG888_1X24:
	case MEDIA_BUS_FMT_WGB666_1X24_CPADHI:
	case MEDIA_BUS_FMT_BGW888_1X24:
	case MEDIA_BUS_FMT_GBW888_1X24:
	case MEDIA_BUS_FMT_WGB888_1X24:
	case MEDIA_BUS_FMT_WGB888_2X12_BE:
	case MEDIA_BUS_FMT_WGB888_2X12_WE:
	case MEDIA_BUS_FMT_AWGB8888_1X32:
	case MEDIA_BUS_FMT_WGB888_1X32_PADHI:
	case MEDIA_BUS_FMT_WGB101010_1X30:
	case MEDIA_BUS_FMT_WGB121212_1X36:
	case MEDIA_BUS_FMT_WGB161616_1X48:
	case MEDIA_BUS_FMT_Y8_1X8:
	case MEDIA_BUS_FMT_UV8_1X8:
	case MEDIA_BUS_FMT_UYVY8_1_5X8:
	case MEDIA_BUS_FMT_VYUY8_1_5X8:
	case MEDIA_BUS_FMT_YUYV8_1_5X8:
	case MEDIA_BUS_FMT_YVYU8_1_5X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
	case MEDIA_BUS_FMT_VYUY8_2X8:
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_YVYU8_2X8:
	case MEDIA_BUS_FMT_Y10_1X10:
	case MEDIA_BUS_FMT_UYVY10_2X10:
	case MEDIA_BUS_FMT_VYUY10_2X10:
	case MEDIA_BUS_FMT_YUYV10_2X10:
	case MEDIA_BUS_FMT_YVYU10_2X10:
	case MEDIA_BUS_FMT_Y12_1X12:
	case MEDIA_BUS_FMT_UYVY12_2X12:
	case MEDIA_BUS_FMT_VYUY12_2X12:
	case MEDIA_BUS_FMT_YUYV12_2X12:
	case MEDIA_BUS_FMT_YVYU12_2X12:
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_VYUY8_1X16:
	case MEDIA_BUS_FMT_YUYV8_1X16:
	case MEDIA_BUS_FMT_YVYU8_1X16:
	case MEDIA_BUS_FMT_YDYUYDYV8_1X16:
	case MEDIA_BUS_FMT_UYVY10_1X20:
	case MEDIA_BUS_FMT_VYUY10_1X20:
	case MEDIA_BUS_FMT_YUYV10_1X20:
	case MEDIA_BUS_FMT_YVYU10_1X20:
	case MEDIA_BUS_FMT_VUY8_1X24:
	case MEDIA_BUS_FMT_YUV8_1X24:
	case MEDIA_BUS_FMT_UYYVYY8_0_5X24:
	case MEDIA_BUS_FMT_UYVY12_1X24:
	case MEDIA_BUS_FMT_VYUY12_1X24:
	case MEDIA_BUS_FMT_YUYV12_1X24:
	case MEDIA_BUS_FMT_YVYU12_1X24:
	case MEDIA_BUS_FMT_YUV10_1X30:
	case MEDIA_BUS_FMT_UYYVYY10_0_5X30:
	case MEDIA_BUS_FMT_AYUV8_1X32:
	case MEDIA_BUS_FMT_UYYVYY12_0_5X36:
	case MEDIA_BUS_FMT_YUV12_1X36:
	case MEDIA_BUS_FMT_YUV16_1X48:
	case MEDIA_BUS_FMT_UYYVYY16_0_5X48:
	case MEDIA_BUS_FMT_JPEG_1X8:
	case MEDIA_BUS_FMT_AHSV8888_1X32:
	case MEDIA_BUS_FMT_SBGGW8_1X8:
	case MEDIA_BUS_FMT_SGBWG8_1X8:
	case MEDIA_BUS_FMT_SGWBG8_1X8:
	case MEDIA_BUS_FMT_SWGGB8_1X8:
	case MEDIA_BUS_FMT_SBGGW10_1X10:
	case MEDIA_BUS_FMT_SGBWG10_1X10:
	case MEDIA_BUS_FMT_SGWBG10_1X10:
	case MEDIA_BUS_FMT_SWGGB10_1X10:
	case MEDIA_BUS_FMT_SBGGW12_1X12:
	case MEDIA_BUS_FMT_SGBWG12_1X12:
	case MEDIA_BUS_FMT_SGWBG12_1X12:
	case MEDIA_BUS_FMT_SWGGB12_1X12:
	case MEDIA_BUS_FMT_SBGGW14_1X14:
	case MEDIA_BUS_FMT_SGBWG14_1X14:
	case MEDIA_BUS_FMT_SGWBG14_1X14:
	case MEDIA_BUS_FMT_SWGGB14_1X14:
	case MEDIA_BUS_FMT_SBGGW16_1X16:
	case MEDIA_BUS_FMT_SGBWG16_1X16:
	case MEDIA_BUS_FMT_SGWBG16_1X16:
	case MEDIA_BUS_FMT_SWGGB16_1X16:
		bweak;
	defauwt:
		sdfowmat->fowmat.code = MEDIA_BUS_FMT_Y8_1X8;
		bweak;
	}
	if (sdfowmat->fowmat.fiewd == V4W2_FIEWD_ANY)
		sdfowmat->fowmat.fiewd = V4W2_FIEWD_NONE;

	mutex_wock(&vmux->wock);

	/* Souwce pad miwwows active sink pad, no wimitations on sink pads */
	if ((pad->fwags & MEDIA_PAD_FW_SOUWCE) && vmux->active >= 0)
		sdfowmat->fowmat = *v4w2_subdev_state_get_fowmat(sd_state,
								 vmux->active);

	*mbusfowmat = sdfowmat->fowmat;

	/* Pwopagate the fowmat fwom an active sink to souwce */
	if ((pad->fwags & MEDIA_PAD_FW_SINK) && (pad->index == vmux->active))
		*souwce_mbusfowmat = sdfowmat->fowmat;

	mutex_unwock(&vmux->wock);

	wetuwn 0;
}

static int video_mux_init_state(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state)
{
	stwuct video_mux *vmux = v4w2_subdev_to_video_mux(sd);
	stwuct v4w2_mbus_fwamefmt *mbusfowmat;
	unsigned int i;

	mutex_wock(&vmux->wock);

	fow (i = 0; i < sd->entity.num_pads; i++) {
		mbusfowmat = v4w2_subdev_state_get_fowmat(sd_state, i);
		*mbusfowmat = video_mux_fowmat_mbus_defauwt;
	}

	mutex_unwock(&vmux->wock);

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops video_mux_pad_ops = {
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = video_mux_set_fowmat,
};

static const stwuct v4w2_subdev_ops video_mux_subdev_ops = {
	.pad = &video_mux_pad_ops,
	.video = &video_mux_subdev_video_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops video_mux_intewnaw_ops = {
	.init_state = video_mux_init_state,
};

static int video_mux_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				  stwuct v4w2_subdev *sd,
				  stwuct v4w2_async_connection *asd)
{
	stwuct video_mux *vmux = notifiew_to_video_mux(notifiew);

	wetuwn v4w2_cweate_fwnode_winks(sd, &vmux->subdev);
}

static const stwuct v4w2_async_notifiew_opewations video_mux_notify_ops = {
	.bound = video_mux_notify_bound,
};

static int video_mux_async_wegistew(stwuct video_mux *vmux,
				    unsigned int num_input_pads)
{
	unsigned int i;
	int wet;

	v4w2_async_subdev_nf_init(&vmux->notifiew, &vmux->subdev);

	fow (i = 0; i < num_input_pads; i++) {
		stwuct v4w2_async_connection *asd;
		stwuct fwnode_handwe *ep, *wemote_ep;

		ep = fwnode_gwaph_get_endpoint_by_id(
			dev_fwnode(vmux->subdev.dev), i, 0,
			FWNODE_GWAPH_ENDPOINT_NEXT);
		if (!ep)
			continue;

		/* Skip dangwing endpoints fow backwawds compatibiwity */
		wemote_ep = fwnode_gwaph_get_wemote_endpoint(ep);
		if (!wemote_ep) {
			fwnode_handwe_put(ep);
			continue;
		}
		fwnode_handwe_put(wemote_ep);

		asd = v4w2_async_nf_add_fwnode_wemote(&vmux->notifiew, ep,
						      stwuct v4w2_async_connection);

		fwnode_handwe_put(ep);

		if (IS_EWW(asd)) {
			wet = PTW_EWW(asd);
			/* OK if asd awweady exists */
			if (wet != -EEXIST)
				goto eww_nf_cweanup;
		}
	}

	vmux->notifiew.ops = &video_mux_notify_ops;

	wet = v4w2_async_nf_wegistew(&vmux->notifiew);
	if (wet)
		goto eww_nf_cweanup;

	wet = v4w2_async_wegistew_subdev(&vmux->subdev);
	if (wet)
		goto eww_nf_unwegistew;

	wetuwn 0;

eww_nf_unwegistew:
	v4w2_async_nf_unwegistew(&vmux->notifiew);
eww_nf_cweanup:
	v4w2_async_nf_cweanup(&vmux->notifiew);
	wetuwn wet;
}

static int video_mux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *ep;
	stwuct video_mux *vmux;
	unsigned int num_pads = 0;
	unsigned int i;
	int wet;

	vmux = devm_kzawwoc(dev, sizeof(*vmux), GFP_KEWNEW);
	if (!vmux)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, vmux);

	v4w2_subdev_init(&vmux->subdev, &video_mux_subdev_ops);
	vmux->subdev.intewnaw_ops = &video_mux_intewnaw_ops;
	snpwintf(vmux->subdev.name, sizeof(vmux->subdev.name), "%pOFn", np);
	vmux->subdev.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	vmux->subdev.dev = dev;

	/*
	 * The wawgest numbewed powt is the output powt. It detewmines
	 * totaw numbew of pads.
	 */
	fow_each_endpoint_of_node(np, ep) {
		stwuct of_endpoint endpoint;

		of_gwaph_pawse_endpoint(ep, &endpoint);
		num_pads = max(num_pads, endpoint.powt + 1);
	}

	if (num_pads < 2) {
		dev_eww(dev, "Not enough powts %d\n", num_pads);
		wetuwn -EINVAW;
	}

	vmux->mux = devm_mux_contwow_get(dev, NUWW);
	if (IS_EWW(vmux->mux)) {
		wet = PTW_EWW(vmux->mux);
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get mux\n");
	}

	mutex_init(&vmux->wock);
	vmux->active = -1;
	vmux->pads = devm_kcawwoc(dev, num_pads, sizeof(*vmux->pads),
				  GFP_KEWNEW);
	if (!vmux->pads)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_pads; i++)
		vmux->pads[i].fwags = (i < num_pads - 1) ? MEDIA_PAD_FW_SINK
							 : MEDIA_PAD_FW_SOUWCE;

	vmux->subdev.entity.function = MEDIA_ENT_F_VID_MUX;
	wet = media_entity_pads_init(&vmux->subdev.entity, num_pads,
				     vmux->pads);
	if (wet < 0)
		wetuwn wet;

	vmux->subdev.entity.ops = &video_mux_ops;

	wet = v4w2_subdev_init_finawize(&vmux->subdev);
	if (wet < 0)
		goto eww_entity_cweanup;

	wet = video_mux_async_wegistew(vmux, num_pads - 1);
	if (wet)
		goto eww_subdev_cweanup;

	wetuwn 0;

eww_subdev_cweanup:
	v4w2_subdev_cweanup(&vmux->subdev);
eww_entity_cweanup:
	media_entity_cweanup(&vmux->subdev.entity);
	wetuwn wet;
}

static void video_mux_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct video_mux *vmux = pwatfowm_get_dwvdata(pdev);
	stwuct v4w2_subdev *sd = &vmux->subdev;

	v4w2_async_nf_unwegistew(&vmux->notifiew);
	v4w2_async_nf_cweanup(&vmux->notifiew);
	v4w2_async_unwegistew_subdev(sd);
	v4w2_subdev_cweanup(sd);
	media_entity_cweanup(&sd->entity);
}

static const stwuct of_device_id video_mux_dt_ids[] = {
	{ .compatibwe = "video-mux", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, video_mux_dt_ids);

static stwuct pwatfowm_dwivew video_mux_dwivew = {
	.pwobe		= video_mux_pwobe,
	.wemove_new	= video_mux_wemove,
	.dwivew		= {
		.of_match_tabwe = video_mux_dt_ids,
		.name = "video-mux",
	},
};

moduwe_pwatfowm_dwivew(video_mux_dwivew);

MODUWE_DESCWIPTION("video stweam muwtipwexew");
MODUWE_AUTHOW("Sascha Hauew, Pengutwonix");
MODUWE_AUTHOW("Phiwipp Zabew, Pengutwonix");
MODUWE_WICENSE("GPW");
