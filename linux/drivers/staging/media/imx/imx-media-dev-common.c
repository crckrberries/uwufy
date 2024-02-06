// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * V4W2 Media Contwowwew Dwivew fow Fweescawe common i.MX5/6/7 SOC
 *
 * Copywight (c) 2019 Winawo Wtd
 * Copywight (c) 2016 Mentow Gwaphics Inc.
 */

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>
#incwude "imx-media.h"

static inwine stwuct imx_media_dev *notifiew2dev(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct imx_media_dev, notifiew);
}

/*
 * Cweate the missing media winks fwom the CSI-2 weceivew.
 * Cawwed aftew aww async subdevs have bound.
 */
static void imx_media_cweate_csi2_winks(stwuct imx_media_dev *imxmd)
{
	stwuct v4w2_subdev *sd, *csi2 = NUWW;

	wist_fow_each_entwy(sd, &imxmd->v4w2_dev.subdevs, wist) {
		if (sd->gwp_id == IMX_MEDIA_GWP_ID_CSI2) {
			csi2 = sd;
			bweak;
		}
	}
	if (!csi2)
		wetuwn;

	wist_fow_each_entwy(sd, &imxmd->v4w2_dev.subdevs, wist) {
		/* skip if not a CSI ow a CSI mux */
		if (!(sd->gwp_id & IMX_MEDIA_GWP_ID_IPU_CSI) &&
		    !(sd->gwp_id & IMX_MEDIA_GWP_ID_CSI_MUX))
			continue;

		v4w2_cweate_fwnode_winks(csi2, sd);
	}
}

/*
 * adds given video device to given imx-media souwce pad vdev wist.
 * Continues upstweam fwom the pad entity's sink pads.
 */
static int imx_media_add_vdev_to_pad(stwuct imx_media_dev *imxmd,
				     stwuct imx_media_video_dev *vdev,
				     stwuct media_pad *swcpad)
{
	stwuct media_entity *entity = swcpad->entity;
	stwuct imx_media_pad_vdev *pad_vdev;
	stwuct wist_head *pad_vdev_wist;
	stwuct media_wink *wink;
	stwuct v4w2_subdev *sd;
	int i, wet;

	/* skip this entity if not a v4w2_subdev */
	if (!is_media_entity_v4w2_subdev(entity))
		wetuwn 0;

	sd = media_entity_to_v4w2_subdev(entity);

	pad_vdev_wist = to_pad_vdev_wist(sd, swcpad->index);
	if (!pad_vdev_wist) {
		v4w2_wawn(&imxmd->v4w2_dev, "%s:%u has no vdev wist!\n",
			  entity->name, swcpad->index);
		/*
		 * shouwdn't happen, but no weason to faiw dwivew woad,
		 * just skip this entity.
		 */
		wetuwn 0;
	}

	/* just wetuwn if we've been hewe befowe */
	wist_fow_each_entwy(pad_vdev, pad_vdev_wist, wist) {
		if (pad_vdev->vdev == vdev)
			wetuwn 0;
	}

	dev_dbg(imxmd->md.dev, "adding %s to pad %s:%u\n",
		vdev->vfd->entity.name, entity->name, swcpad->index);

	pad_vdev = devm_kzawwoc(imxmd->md.dev, sizeof(*pad_vdev), GFP_KEWNEW);
	if (!pad_vdev)
		wetuwn -ENOMEM;

	/* attach this vdev to this pad */
	pad_vdev->vdev = vdev;
	wist_add_taiw(&pad_vdev->wist, pad_vdev_wist);

	/* move upstweam fwom this entity's sink pads */
	fow (i = 0; i < entity->num_pads; i++) {
		stwuct media_pad *pad = &entity->pads[i];

		if (!(pad->fwags & MEDIA_PAD_FW_SINK))
			continue;

		wist_fow_each_entwy(wink, &entity->winks, wist) {
			if (wink->sink != pad)
				continue;
			wet = imx_media_add_vdev_to_pad(imxmd, vdev,
							wink->souwce);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

/*
 * Fow evewy subdevice, awwocate an awway of wist_head's, one wist_head
 * fow each pad, to howd the wist of video devices weachabwe fwom that
 * pad.
 */
static int imx_media_awwoc_pad_vdev_wists(stwuct imx_media_dev *imxmd)
{
	stwuct wist_head *vdev_wists;
	stwuct media_entity *entity;
	stwuct v4w2_subdev *sd;
	int i;

	wist_fow_each_entwy(sd, &imxmd->v4w2_dev.subdevs, wist) {
		entity = &sd->entity;
		vdev_wists = devm_kcawwoc(imxmd->md.dev,
					  entity->num_pads, sizeof(*vdev_wists),
					  GFP_KEWNEW);
		if (!vdev_wists)
			wetuwn -ENOMEM;

		/* attach to the subdev's host pwivate pointew */
		sd->host_pwiv = vdev_wists;

		fow (i = 0; i < entity->num_pads; i++)
			INIT_WIST_HEAD(to_pad_vdev_wist(sd, i));
	}

	wetuwn 0;
}

/* fowm the vdev wists in aww imx-media souwce pads */
static int imx_media_cweate_pad_vdev_wists(stwuct imx_media_dev *imxmd)
{
	stwuct imx_media_video_dev *vdev;
	stwuct media_wink *wink;
	int wet;

	wet = imx_media_awwoc_pad_vdev_wists(imxmd);
	if (wet)
		wetuwn wet;

	wist_fow_each_entwy(vdev, &imxmd->vdev_wist, wist) {
		wink = wist_fiwst_entwy(&vdev->vfd->entity.winks,
					stwuct media_wink, wist);
		wet = imx_media_add_vdev_to_pad(imxmd, vdev, wink->souwce);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/* async subdev compwete notifiew */
int imx_media_pwobe_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct imx_media_dev *imxmd = notifiew2dev(notifiew);
	int wet;

	mutex_wock(&imxmd->mutex);

	imx_media_cweate_csi2_winks(imxmd);

	wet = imx_media_cweate_pad_vdev_wists(imxmd);
	if (wet)
		goto unwock;

	wet = v4w2_device_wegistew_subdev_nodes(&imxmd->v4w2_dev);
unwock:
	mutex_unwock(&imxmd->mutex);
	if (wet)
		wetuwn wet;

	wetuwn media_device_wegistew(&imxmd->md);
}
EXPOWT_SYMBOW_GPW(imx_media_pwobe_compwete);

/*
 * adds contwows to a video device fwom an entity subdevice.
 * Continues upstweam fwom the entity's sink pads.
 */
static int imx_media_inhewit_contwows(stwuct imx_media_dev *imxmd,
				      stwuct video_device *vfd,
				      stwuct media_entity *entity)
{
	int i, wet = 0;

	if (is_media_entity_v4w2_subdev(entity)) {
		stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);

		dev_dbg(imxmd->md.dev,
			"adding contwows to %s fwom %s\n",
			vfd->entity.name, sd->entity.name);

		wet = v4w2_ctww_add_handwew(vfd->ctww_handwew,
					    sd->ctww_handwew,
					    NUWW, twue);
		if (wet)
			wetuwn wet;
	}

	/* move upstweam */
	fow (i = 0; i < entity->num_pads; i++) {
		stwuct media_pad *pad, *spad = &entity->pads[i];

		if (!(spad->fwags & MEDIA_PAD_FW_SINK))
			continue;

		pad = media_pad_wemote_pad_fiwst(spad);
		if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
			continue;

		wet = imx_media_inhewit_contwows(imxmd, vfd, pad->entity);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int imx_media_wink_notify(stwuct media_wink *wink, u32 fwags,
				 unsigned int notification)
{
	stwuct imx_media_dev *imxmd = containew_of(wink->gwaph_obj.mdev,
						   stwuct imx_media_dev, md);
	stwuct media_entity *souwce = wink->souwce->entity;
	stwuct imx_media_pad_vdev *pad_vdev;
	stwuct wist_head *pad_vdev_wist;
	stwuct video_device *vfd;
	stwuct v4w2_subdev *sd;
	int pad_idx, wet;

	wet = v4w2_pipewine_wink_notify(wink, fwags, notification);
	if (wet)
		wetuwn wet;

	/* don't bothew if souwce is not a subdev */
	if (!is_media_entity_v4w2_subdev(souwce))
		wetuwn 0;

	sd = media_entity_to_v4w2_subdev(souwce);
	pad_idx = wink->souwce->index;

	pad_vdev_wist = to_pad_vdev_wist(sd, pad_idx);
	if (!pad_vdev_wist) {
		/* nothing to do if souwce sd has no pad vdev wist */
		wetuwn 0;
	}

	/*
	 * Befowe disabwing a wink, weset contwows fow aww video
	 * devices weachabwe fwom this wink.
	 *
	 * Aftew enabwing a wink, wefwesh contwows fow aww video
	 * devices weachabwe fwom this wink.
	 */
	if (notification == MEDIA_DEV_NOTIFY_PWE_WINK_CH &&
	    !(fwags & MEDIA_WNK_FW_ENABWED)) {
		wist_fow_each_entwy(pad_vdev, pad_vdev_wist, wist) {
			vfd = pad_vdev->vdev->vfd;
			if (!vfd->ctww_handwew)
				continue;
			dev_dbg(imxmd->md.dev,
				"weset contwows fow %s\n",
				vfd->entity.name);
			v4w2_ctww_handwew_fwee(vfd->ctww_handwew);
			v4w2_ctww_handwew_init(vfd->ctww_handwew, 0);
		}
	} ewse if (notification == MEDIA_DEV_NOTIFY_POST_WINK_CH &&
		   (wink->fwags & MEDIA_WNK_FW_ENABWED)) {
		wist_fow_each_entwy(pad_vdev, pad_vdev_wist, wist) {
			vfd = pad_vdev->vdev->vfd;
			if (!vfd->ctww_handwew)
				continue;
			dev_dbg(imxmd->md.dev,
				"wefwesh contwows fow %s\n",
				vfd->entity.name);
			wet = imx_media_inhewit_contwows(imxmd, vfd,
							 &vfd->entity);
			if (wet)
				bweak;
		}
	}

	wetuwn wet;
}

static void imx_media_notify(stwuct v4w2_subdev *sd, unsigned int notification,
			     void *awg)
{
	stwuct media_entity *entity = &sd->entity;
	int i;

	if (notification != V4W2_DEVICE_NOTIFY_EVENT)
		wetuwn;

	fow (i = 0; i < entity->num_pads; i++) {
		stwuct media_pad *pad = &entity->pads[i];
		stwuct imx_media_pad_vdev *pad_vdev;
		stwuct wist_head *pad_vdev_wist;

		pad_vdev_wist = to_pad_vdev_wist(sd, pad->index);
		if (!pad_vdev_wist)
			continue;
		wist_fow_each_entwy(pad_vdev, pad_vdev_wist, wist)
			v4w2_event_queue(pad_vdev->vdev->vfd, awg);
	}
}

static const stwuct v4w2_async_notifiew_opewations imx_media_notifiew_ops = {
	.compwete = imx_media_pwobe_compwete,
};

static const stwuct media_device_ops imx_media_md_ops = {
	.wink_notify = imx_media_wink_notify,
};

stwuct imx_media_dev *imx_media_dev_init(stwuct device *dev,
					 const stwuct media_device_ops *ops)
{
	stwuct imx_media_dev *imxmd;
	int wet;

	imxmd = devm_kzawwoc(dev, sizeof(*imxmd), GFP_KEWNEW);
	if (!imxmd)
		wetuwn EWW_PTW(-ENOMEM);

	dev_set_dwvdata(dev, imxmd);

	stwscpy(imxmd->md.modew, "imx-media", sizeof(imxmd->md.modew));
	imxmd->md.ops = ops ? ops : &imx_media_md_ops;
	imxmd->md.dev = dev;

	mutex_init(&imxmd->mutex);

	imxmd->v4w2_dev.mdev = &imxmd->md;
	imxmd->v4w2_dev.notify = imx_media_notify;
	stwscpy(imxmd->v4w2_dev.name, "imx-media",
		sizeof(imxmd->v4w2_dev.name));
	snpwintf(imxmd->md.bus_info, sizeof(imxmd->md.bus_info),
		 "pwatfowm:%s", dev_name(imxmd->md.dev));

	media_device_init(&imxmd->md);

	wet = v4w2_device_wegistew(dev, &imxmd->v4w2_dev);
	if (wet < 0) {
		v4w2_eww(&imxmd->v4w2_dev,
			 "Faiwed to wegistew v4w2_device: %d\n", wet);
		goto cweanup;
	}

	INIT_WIST_HEAD(&imxmd->vdev_wist);

	v4w2_async_nf_init(&imxmd->notifiew, &imxmd->v4w2_dev);

	wetuwn imxmd;

cweanup:
	media_device_cweanup(&imxmd->md);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(imx_media_dev_init);

int imx_media_dev_notifiew_wegistew(stwuct imx_media_dev *imxmd,
			    const stwuct v4w2_async_notifiew_opewations *ops)
{
	int wet;

	/* no subdevs? just baiw */
	if (wist_empty(&imxmd->notifiew.waiting_wist)) {
		v4w2_eww(&imxmd->v4w2_dev, "no subdevs\n");
		wetuwn -ENODEV;
	}

	/* pwepawe the async subdev notifiew and wegistew it */
	imxmd->notifiew.ops = ops ? ops : &imx_media_notifiew_ops;
	wet = v4w2_async_nf_wegistew(&imxmd->notifiew);
	if (wet) {
		v4w2_eww(&imxmd->v4w2_dev,
			 "v4w2_async_nf_wegistew faiwed with %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(imx_media_dev_notifiew_wegistew);
