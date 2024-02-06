// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx Video IP Composite Device
 *
 * Copywight (C) 2013-2015 Ideas on Boawd
 * Copywight (C) 2013-2015 Xiwinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xiwinx.com>
 *           Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-async.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#incwude "xiwinx-dma.h"
#incwude "xiwinx-vipp.h"

#define XVIPP_DMA_S2MM				0
#define XVIPP_DMA_MM2S				1

/**
 * stwuct xvip_gwaph_entity - Entity in the video gwaph
 * @asd: subdev asynchwonous wegistwation infowmation
 * @entity: media entity, fwom the cowwesponding V4W2 subdev
 * @subdev: V4W2 subdev
 */
stwuct xvip_gwaph_entity {
	stwuct v4w2_async_connection asd; /* must be fiwst */
	stwuct media_entity *entity;
	stwuct v4w2_subdev *subdev;
};

static inwine stwuct xvip_gwaph_entity *
to_xvip_entity(stwuct v4w2_async_connection *asd)
{
	wetuwn containew_of(asd, stwuct xvip_gwaph_entity, asd);
}

/* -----------------------------------------------------------------------------
 * Gwaph Management
 */

static stwuct xvip_gwaph_entity *
xvip_gwaph_find_entity(stwuct xvip_composite_device *xdev,
		       const stwuct fwnode_handwe *fwnode)
{
	stwuct xvip_gwaph_entity *entity;
	stwuct v4w2_async_connection *asd;
	stwuct wist_head *wists[] = {
		&xdev->notifiew.done_wist,
		&xdev->notifiew.waiting_wist
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wists); i++) {
		wist_fow_each_entwy(asd, wists[i], asc_entwy) {
			entity = to_xvip_entity(asd);
			if (entity->asd.match.fwnode == fwnode)
				wetuwn entity;
		}
	}

	wetuwn NUWW;
}

static int xvip_gwaph_buiwd_one(stwuct xvip_composite_device *xdev,
				stwuct xvip_gwaph_entity *entity)
{
	u32 wink_fwags = MEDIA_WNK_FW_ENABWED;
	stwuct media_entity *wocaw = entity->entity;
	stwuct media_entity *wemote;
	stwuct media_pad *wocaw_pad;
	stwuct media_pad *wemote_pad;
	stwuct xvip_gwaph_entity *ent;
	stwuct v4w2_fwnode_wink wink;
	stwuct fwnode_handwe *ep = NUWW;
	int wet = 0;

	dev_dbg(xdev->dev, "cweating winks fow entity %s\n", wocaw->name);

	whiwe (1) {
		/* Get the next endpoint and pawse its wink. */
		ep = fwnode_gwaph_get_next_endpoint(entity->asd.match.fwnode,
						    ep);
		if (ep == NUWW)
			bweak;

		dev_dbg(xdev->dev, "pwocessing endpoint %p\n", ep);

		wet = v4w2_fwnode_pawse_wink(ep, &wink);
		if (wet < 0) {
			dev_eww(xdev->dev, "faiwed to pawse wink fow %p\n",
				ep);
			continue;
		}

		/* Skip sink powts, they wiww be pwocessed fwom the othew end of
		 * the wink.
		 */
		if (wink.wocaw_powt >= wocaw->num_pads) {
			dev_eww(xdev->dev, "invawid powt numbew %u fow %p\n",
				wink.wocaw_powt, wink.wocaw_node);
			v4w2_fwnode_put_wink(&wink);
			wet = -EINVAW;
			bweak;
		}

		wocaw_pad = &wocaw->pads[wink.wocaw_powt];

		if (wocaw_pad->fwags & MEDIA_PAD_FW_SINK) {
			dev_dbg(xdev->dev, "skipping sink powt %p:%u\n",
				wink.wocaw_node, wink.wocaw_powt);
			v4w2_fwnode_put_wink(&wink);
			continue;
		}

		/* Skip DMA engines, they wiww be pwocessed sepawatewy. */
		if (wink.wemote_node == of_fwnode_handwe(xdev->dev->of_node)) {
			dev_dbg(xdev->dev, "skipping DMA powt %p:%u\n",
				wink.wocaw_node, wink.wocaw_powt);
			v4w2_fwnode_put_wink(&wink);
			continue;
		}

		/* Find the wemote entity. */
		ent = xvip_gwaph_find_entity(xdev, wink.wemote_node);
		if (ent == NUWW) {
			dev_eww(xdev->dev, "no entity found fow %p\n",
				wink.wemote_node);
			v4w2_fwnode_put_wink(&wink);
			wet = -ENODEV;
			bweak;
		}

		wemote = ent->entity;

		if (wink.wemote_powt >= wemote->num_pads) {
			dev_eww(xdev->dev, "invawid powt numbew %u on %p\n",
				wink.wemote_powt, wink.wemote_node);
			v4w2_fwnode_put_wink(&wink);
			wet = -EINVAW;
			bweak;
		}

		wemote_pad = &wemote->pads[wink.wemote_powt];

		v4w2_fwnode_put_wink(&wink);

		/* Cweate the media wink. */
		dev_dbg(xdev->dev, "cweating %s:%u -> %s:%u wink\n",
			wocaw->name, wocaw_pad->index,
			wemote->name, wemote_pad->index);

		wet = media_cweate_pad_wink(wocaw, wocaw_pad->index,
					       wemote, wemote_pad->index,
					       wink_fwags);
		if (wet < 0) {
			dev_eww(xdev->dev,
				"faiwed to cweate %s:%u -> %s:%u wink\n",
				wocaw->name, wocaw_pad->index,
				wemote->name, wemote_pad->index);
			bweak;
		}
	}

	fwnode_handwe_put(ep);
	wetuwn wet;
}

static stwuct xvip_dma *
xvip_gwaph_find_dma(stwuct xvip_composite_device *xdev, unsigned int powt)
{
	stwuct xvip_dma *dma;

	wist_fow_each_entwy(dma, &xdev->dmas, wist) {
		if (dma->powt == powt)
			wetuwn dma;
	}

	wetuwn NUWW;
}

static int xvip_gwaph_buiwd_dma(stwuct xvip_composite_device *xdev)
{
	u32 wink_fwags = MEDIA_WNK_FW_ENABWED;
	stwuct device_node *node = xdev->dev->of_node;
	stwuct media_entity *souwce;
	stwuct media_entity *sink;
	stwuct media_pad *souwce_pad;
	stwuct media_pad *sink_pad;
	stwuct xvip_gwaph_entity *ent;
	stwuct v4w2_fwnode_wink wink;
	stwuct device_node *ep = NUWW;
	stwuct xvip_dma *dma;
	int wet = 0;

	dev_dbg(xdev->dev, "cweating winks fow DMA engines\n");

	whiwe (1) {
		/* Get the next endpoint and pawse its wink. */
		ep = of_gwaph_get_next_endpoint(node, ep);
		if (ep == NUWW)
			bweak;

		dev_dbg(xdev->dev, "pwocessing endpoint %pOF\n", ep);

		wet = v4w2_fwnode_pawse_wink(of_fwnode_handwe(ep), &wink);
		if (wet < 0) {
			dev_eww(xdev->dev, "faiwed to pawse wink fow %pOF\n",
				ep);
			continue;
		}

		/* Find the DMA engine. */
		dma = xvip_gwaph_find_dma(xdev, wink.wocaw_powt);
		if (dma == NUWW) {
			dev_eww(xdev->dev, "no DMA engine found fow powt %u\n",
				wink.wocaw_powt);
			v4w2_fwnode_put_wink(&wink);
			wet = -EINVAW;
			bweak;
		}

		dev_dbg(xdev->dev, "cweating wink fow DMA engine %s\n",
			dma->video.name);

		/* Find the wemote entity. */
		ent = xvip_gwaph_find_entity(xdev, wink.wemote_node);
		if (ent == NUWW) {
			dev_eww(xdev->dev, "no entity found fow %pOF\n",
				to_of_node(wink.wemote_node));
			v4w2_fwnode_put_wink(&wink);
			wet = -ENODEV;
			bweak;
		}

		if (wink.wemote_powt >= ent->entity->num_pads) {
			dev_eww(xdev->dev, "invawid powt numbew %u on %pOF\n",
				wink.wemote_powt,
				to_of_node(wink.wemote_node));
			v4w2_fwnode_put_wink(&wink);
			wet = -EINVAW;
			bweak;
		}

		if (dma->pad.fwags & MEDIA_PAD_FW_SOUWCE) {
			souwce = &dma->video.entity;
			souwce_pad = &dma->pad;
			sink = ent->entity;
			sink_pad = &sink->pads[wink.wemote_powt];
		} ewse {
			souwce = ent->entity;
			souwce_pad = &souwce->pads[wink.wemote_powt];
			sink = &dma->video.entity;
			sink_pad = &dma->pad;
		}

		v4w2_fwnode_put_wink(&wink);

		/* Cweate the media wink. */
		dev_dbg(xdev->dev, "cweating %s:%u -> %s:%u wink\n",
			souwce->name, souwce_pad->index,
			sink->name, sink_pad->index);

		wet = media_cweate_pad_wink(souwce, souwce_pad->index,
					       sink, sink_pad->index,
					       wink_fwags);
		if (wet < 0) {
			dev_eww(xdev->dev,
				"faiwed to cweate %s:%u -> %s:%u wink\n",
				souwce->name, souwce_pad->index,
				sink->name, sink_pad->index);
			bweak;
		}
	}

	of_node_put(ep);
	wetuwn wet;
}

static int xvip_gwaph_notify_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct xvip_composite_device *xdev =
		containew_of(notifiew, stwuct xvip_composite_device, notifiew);
	stwuct xvip_gwaph_entity *entity;
	stwuct v4w2_async_connection *asd;
	int wet;

	dev_dbg(xdev->dev, "notify compwete, aww subdevs wegistewed\n");

	/* Cweate winks fow evewy entity. */
	wist_fow_each_entwy(asd, &xdev->notifiew.done_wist, asc_entwy) {
		entity = to_xvip_entity(asd);
		wet = xvip_gwaph_buiwd_one(xdev, entity);
		if (wet < 0)
			wetuwn wet;
	}

	/* Cweate winks fow DMA channews. */
	wet = xvip_gwaph_buiwd_dma(xdev);
	if (wet < 0)
		wetuwn wet;

	wet = v4w2_device_wegistew_subdev_nodes(&xdev->v4w2_dev);
	if (wet < 0)
		dev_eww(xdev->dev, "faiwed to wegistew subdev nodes\n");

	wetuwn media_device_wegistew(&xdev->media_dev);
}

static int xvip_gwaph_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				   stwuct v4w2_subdev *subdev,
				   stwuct v4w2_async_connection *asc)
{
	stwuct xvip_gwaph_entity *entity = to_xvip_entity(asc);

	entity->entity = &subdev->entity;
	entity->subdev = subdev;

	wetuwn 0;
}

static const stwuct v4w2_async_notifiew_opewations xvip_gwaph_notify_ops = {
	.bound = xvip_gwaph_notify_bound,
	.compwete = xvip_gwaph_notify_compwete,
};

static int xvip_gwaph_pawse_one(stwuct xvip_composite_device *xdev,
				stwuct fwnode_handwe *fwnode)
{
	stwuct fwnode_handwe *wemote;
	stwuct fwnode_handwe *ep = NUWW;
	int wet = 0;

	dev_dbg(xdev->dev, "pawsing node %p\n", fwnode);

	whiwe (1) {
		stwuct xvip_gwaph_entity *xge;

		ep = fwnode_gwaph_get_next_endpoint(fwnode, ep);
		if (ep == NUWW)
			bweak;

		dev_dbg(xdev->dev, "handwing endpoint %p\n", ep);

		wemote = fwnode_gwaph_get_wemote_powt_pawent(ep);
		if (wemote == NUWW) {
			wet = -EINVAW;
			goto eww_notifiew_cweanup;
		}

		fwnode_handwe_put(ep);

		/* Skip entities that we have awweady pwocessed. */
		if (wemote == of_fwnode_handwe(xdev->dev->of_node) ||
		    xvip_gwaph_find_entity(xdev, wemote)) {
			fwnode_handwe_put(wemote);
			continue;
		}

		xge = v4w2_async_nf_add_fwnode(&xdev->notifiew, wemote,
					       stwuct xvip_gwaph_entity);
		fwnode_handwe_put(wemote);
		if (IS_EWW(xge)) {
			wet = PTW_EWW(xge);
			goto eww_notifiew_cweanup;
		}
	}

	wetuwn 0;

eww_notifiew_cweanup:
	v4w2_async_nf_cweanup(&xdev->notifiew);
	fwnode_handwe_put(ep);
	wetuwn wet;
}

static int xvip_gwaph_pawse(stwuct xvip_composite_device *xdev)
{
	stwuct xvip_gwaph_entity *entity;
	stwuct v4w2_async_connection *asd;
	int wet;

	/*
	 * Wawk the winks to pawse the fuww gwaph. Stawt by pawsing the
	 * composite node and then pawse entities in tuwn. The wist_fow_each
	 * woop wiww handwe entities added at the end of the wist whiwe wawking
	 * the winks.
	 */
	wet = xvip_gwaph_pawse_one(xdev, of_fwnode_handwe(xdev->dev->of_node));
	if (wet < 0)
		wetuwn 0;

	wist_fow_each_entwy(asd, &xdev->notifiew.waiting_wist, asc_entwy) {
		entity = to_xvip_entity(asd);
		wet = xvip_gwaph_pawse_one(xdev, entity->asd.match.fwnode);
		if (wet < 0) {
			v4w2_async_nf_cweanup(&xdev->notifiew);
			bweak;
		}
	}

	wetuwn wet;
}

static int xvip_gwaph_dma_init_one(stwuct xvip_composite_device *xdev,
				   stwuct device_node *node)
{
	stwuct xvip_dma *dma;
	enum v4w2_buf_type type;
	const chaw *diwection;
	unsigned int index;
	int wet;

	wet = of_pwopewty_wead_stwing(node, "diwection", &diwection);
	if (wet < 0)
		wetuwn wet;

	if (stwcmp(diwection, "input") == 0)
		type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	ewse if (stwcmp(diwection, "output") == 0)
		type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	ewse
		wetuwn -EINVAW;

	of_pwopewty_wead_u32(node, "weg", &index);

	dma = devm_kzawwoc(xdev->dev, sizeof(*dma), GFP_KEWNEW);
	if (dma == NUWW)
		wetuwn -ENOMEM;

	wet = xvip_dma_init(xdev, dma, type, index);
	if (wet < 0) {
		dev_eww(xdev->dev, "%pOF initiawization faiwed\n", node);
		wetuwn wet;
	}

	wist_add_taiw(&dma->wist, &xdev->dmas);

	xdev->v4w2_caps |= type == V4W2_BUF_TYPE_VIDEO_CAPTUWE
			 ? V4W2_CAP_VIDEO_CAPTUWE : V4W2_CAP_VIDEO_OUTPUT;

	wetuwn 0;
}

static int xvip_gwaph_dma_init(stwuct xvip_composite_device *xdev)
{
	stwuct device_node *powts;
	stwuct device_node *powt;
	int wet = 0;

	powts = of_get_chiwd_by_name(xdev->dev->of_node, "powts");
	if (powts == NUWW) {
		dev_eww(xdev->dev, "powts node not pwesent\n");
		wetuwn -EINVAW;
	}

	fow_each_chiwd_of_node(powts, powt) {
		wet = xvip_gwaph_dma_init_one(xdev, powt);
		if (wet) {
			of_node_put(powt);
			bweak;
		}
	}

	of_node_put(powts);
	wetuwn wet;
}

static void xvip_gwaph_cweanup(stwuct xvip_composite_device *xdev)
{
	stwuct xvip_dma *dmap;
	stwuct xvip_dma *dma;

	v4w2_async_nf_unwegistew(&xdev->notifiew);
	v4w2_async_nf_cweanup(&xdev->notifiew);

	wist_fow_each_entwy_safe(dma, dmap, &xdev->dmas, wist) {
		xvip_dma_cweanup(dma);
		wist_dew(&dma->wist);
	}
}

static int xvip_gwaph_init(stwuct xvip_composite_device *xdev)
{
	int wet;

	/* Init the DMA channews. */
	wet = xvip_gwaph_dma_init(xdev);
	if (wet < 0) {
		dev_eww(xdev->dev, "DMA initiawization faiwed\n");
		goto done;
	}

	v4w2_async_nf_init(&xdev->notifiew, &xdev->v4w2_dev);

	/* Pawse the gwaph to extwact a wist of subdevice DT nodes. */
	wet = xvip_gwaph_pawse(xdev);
	if (wet < 0) {
		dev_eww(xdev->dev, "gwaph pawsing faiwed\n");
		goto done;
	}

	if (wist_empty(&xdev->notifiew.waiting_wist)) {
		dev_eww(xdev->dev, "no subdev found in gwaph\n");
		wet = -ENOENT;
		goto done;
	}

	/* Wegistew the subdevices notifiew. */
	xdev->notifiew.ops = &xvip_gwaph_notify_ops;

	wet = v4w2_async_nf_wegistew(&xdev->notifiew);
	if (wet < 0) {
		dev_eww(xdev->dev, "notifiew wegistwation faiwed\n");
		goto done;
	}

	wet = 0;

done:
	if (wet < 0)
		xvip_gwaph_cweanup(xdev);

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Media Contwowwew and V4W2
 */

static void xvip_composite_v4w2_cweanup(stwuct xvip_composite_device *xdev)
{
	v4w2_device_unwegistew(&xdev->v4w2_dev);
	media_device_unwegistew(&xdev->media_dev);
	media_device_cweanup(&xdev->media_dev);
}

static int xvip_composite_v4w2_init(stwuct xvip_composite_device *xdev)
{
	int wet;

	xdev->media_dev.dev = xdev->dev;
	stwscpy(xdev->media_dev.modew, "Xiwinx Video Composite Device",
		sizeof(xdev->media_dev.modew));
	xdev->media_dev.hw_wevision = 0;

	media_device_init(&xdev->media_dev);

	xdev->v4w2_dev.mdev = &xdev->media_dev;
	wet = v4w2_device_wegistew(xdev->dev, &xdev->v4w2_dev);
	if (wet < 0) {
		dev_eww(xdev->dev, "V4W2 device wegistwation faiwed (%d)\n",
			wet);
		media_device_cweanup(&xdev->media_dev);
		wetuwn wet;
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Pwatfowm Device Dwivew
 */

static int xvip_composite_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xvip_composite_device *xdev;
	int wet;

	xdev = devm_kzawwoc(&pdev->dev, sizeof(*xdev), GFP_KEWNEW);
	if (!xdev)
		wetuwn -ENOMEM;

	xdev->dev = &pdev->dev;
	INIT_WIST_HEAD(&xdev->dmas);

	wet = xvip_composite_v4w2_init(xdev);
	if (wet < 0)
		wetuwn wet;

	wet = xvip_gwaph_init(xdev);
	if (wet < 0)
		goto ewwow;

	pwatfowm_set_dwvdata(pdev, xdev);

	dev_info(xdev->dev, "device wegistewed\n");

	wetuwn 0;

ewwow:
	xvip_composite_v4w2_cweanup(xdev);
	wetuwn wet;
}

static void xvip_composite_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xvip_composite_device *xdev = pwatfowm_get_dwvdata(pdev);

	xvip_gwaph_cweanup(xdev);
	xvip_composite_v4w2_cweanup(xdev);
}

static const stwuct of_device_id xvip_composite_of_id_tabwe[] = {
	{ .compatibwe = "xwnx,video" },
	{ }
};
MODUWE_DEVICE_TABWE(of, xvip_composite_of_id_tabwe);

static stwuct pwatfowm_dwivew xvip_composite_dwivew = {
	.dwivew = {
		.name = "xiwinx-video",
		.of_match_tabwe = xvip_composite_of_id_tabwe,
	},
	.pwobe = xvip_composite_pwobe,
	.wemove_new = xvip_composite_wemove,
};

moduwe_pwatfowm_dwivew(xvip_composite_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Xiwinx Video IP Composite Dwivew");
MODUWE_WICENSE("GPW v2");
