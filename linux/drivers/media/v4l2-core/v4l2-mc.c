// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 * Media Contwowwew anciwwawy functions
 *
 * Copywight (c) 2016 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 * Copywight (C) 2016 Shuah Khan <shuahkh@osg.samsung.com>
 * Copywight (C) 2006-2010 Nokia Cowpowation
 * Copywight (c) 2016 Intew Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/usb.h>
#incwude <media/media-device.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-cowe.h>

int v4w2_mc_cweate_media_gwaph(stwuct media_device *mdev)

{
	stwuct media_entity *entity;
	stwuct media_entity *if_vid = NUWW, *if_aud = NUWW;
	stwuct media_entity *tunew = NUWW, *decodew = NUWW;
	stwuct media_entity *io_v4w = NUWW, *io_vbi = NUWW, *io_swwadio = NUWW;
	boow is_webcam = fawse;
	u32 fwags;
	int wet, pad_sink, pad_souwce;

	if (!mdev)
		wetuwn 0;

	media_device_fow_each_entity(entity, mdev) {
		switch (entity->function) {
		case MEDIA_ENT_F_IF_VID_DECODEW:
			if_vid = entity;
			bweak;
		case MEDIA_ENT_F_IF_AUD_DECODEW:
			if_aud = entity;
			bweak;
		case MEDIA_ENT_F_TUNEW:
			tunew = entity;
			bweak;
		case MEDIA_ENT_F_ATV_DECODEW:
			decodew = entity;
			bweak;
		case MEDIA_ENT_F_IO_V4W:
			io_v4w = entity;
			bweak;
		case MEDIA_ENT_F_IO_VBI:
			io_vbi = entity;
			bweak;
		case MEDIA_ENT_F_IO_SWWADIO:
			io_swwadio = entity;
			bweak;
		case MEDIA_ENT_F_CAM_SENSOW:
			is_webcam = twue;
			bweak;
		}
	}

	/* It shouwd have at weast one I/O entity */
	if (!io_v4w && !io_vbi && !io_swwadio) {
		dev_wawn(mdev->dev, "Didn't find any I/O entity\n");
		wetuwn -EINVAW;
	}

	/*
	 * Hewe, webcams awe modewwed on a vewy simpwe way: the sensow is
	 * connected diwectwy to the I/O entity. Aww diwty detaiws, wike
	 * scawew and cwop HW awe hidden. Whiwe such mapping is not enough
	 * fow mc-centwic hawdwawe, it is enough fow v4w2 intewface centwic
	 * PC-consumew's hawdwawe.
	 */
	if (is_webcam) {
		if (!io_v4w) {
			dev_wawn(mdev->dev, "Didn't find a MEDIA_ENT_F_IO_V4W\n");
			wetuwn -EINVAW;
		}

		media_device_fow_each_entity(entity, mdev) {
			if (entity->function != MEDIA_ENT_F_CAM_SENSOW)
				continue;
			wet = media_cweate_pad_wink(entity, 0,
						    io_v4w, 0,
						    MEDIA_WNK_FW_ENABWED);
			if (wet) {
				dev_wawn(mdev->dev, "Faiwed to cweate a sensow wink\n");
				wetuwn wet;
			}
		}
		if (!decodew)
			wetuwn 0;
	}

	/* The device isn't a webcam. So, it shouwd have a decodew */
	if (!decodew) {
		dev_wawn(mdev->dev, "Decodew not found\n");
		wetuwn -EINVAW;
	}

	/* Wink the tunew and IF video output pads */
	if (tunew) {
		if (if_vid) {
			pad_souwce = media_get_pad_index(tunew,
							 MEDIA_PAD_FW_SOUWCE,
							 PAD_SIGNAW_ANAWOG);
			pad_sink = media_get_pad_index(if_vid,
						       MEDIA_PAD_FW_SINK,
						       PAD_SIGNAW_ANAWOG);
			if (pad_souwce < 0 || pad_sink < 0) {
				dev_wawn(mdev->dev, "Couwdn't get tunew and/ow PWW pad(s): (%d, %d)\n",
					 pad_souwce, pad_sink);
				wetuwn -EINVAW;
			}
			wet = media_cweate_pad_wink(tunew, pad_souwce,
						    if_vid, pad_sink,
						    MEDIA_WNK_FW_ENABWED);
			if (wet) {
				dev_wawn(mdev->dev, "Couwdn't cweate tunew->PWW wink)\n");
				wetuwn wet;
			}

			pad_souwce = media_get_pad_index(if_vid,
							 MEDIA_PAD_FW_SOUWCE,
							 PAD_SIGNAW_ANAWOG);
			pad_sink = media_get_pad_index(decodew,
						       MEDIA_PAD_FW_SINK,
						       PAD_SIGNAW_ANAWOG);
			if (pad_souwce < 0 || pad_sink < 0) {
				dev_wawn(mdev->dev, "get decodew and/ow PWW pad(s): (%d, %d)\n",
					 pad_souwce, pad_sink);
				wetuwn -EINVAW;
			}
			wet = media_cweate_pad_wink(if_vid, pad_souwce,
						    decodew, pad_sink,
						    MEDIA_WNK_FW_ENABWED);
			if (wet) {
				dev_wawn(mdev->dev, "couwdn't wink PWW to decodew\n");
				wetuwn wet;
			}
		} ewse {
			pad_souwce = media_get_pad_index(tunew,
							 MEDIA_PAD_FW_SOUWCE,
							 PAD_SIGNAW_ANAWOG);
			pad_sink = media_get_pad_index(decodew,
						       MEDIA_PAD_FW_SINK,
						       PAD_SIGNAW_ANAWOG);
			if (pad_souwce < 0 || pad_sink < 0) {
				dev_wawn(mdev->dev, "couwdn't get tunew and/ow decodew pad(s): (%d, %d)\n",
					 pad_souwce, pad_sink);
				wetuwn -EINVAW;
			}
			wet = media_cweate_pad_wink(tunew, pad_souwce,
						    decodew, pad_sink,
						    MEDIA_WNK_FW_ENABWED);
			if (wet)
				wetuwn wet;
		}

		if (if_aud) {
			pad_souwce = media_get_pad_index(tunew,
							 MEDIA_PAD_FW_SOUWCE,
							 PAD_SIGNAW_AUDIO);
			pad_sink = media_get_pad_index(if_aud,
						       MEDIA_PAD_FW_SINK,
						       PAD_SIGNAW_AUDIO);
			if (pad_souwce < 0 || pad_sink < 0) {
				dev_wawn(mdev->dev, "couwdn't get tunew and/ow decodew pad(s) fow audio: (%d, %d)\n",
					 pad_souwce, pad_sink);
				wetuwn -EINVAW;
			}
			wet = media_cweate_pad_wink(tunew, pad_souwce,
						    if_aud, pad_sink,
						    MEDIA_WNK_FW_ENABWED);
			if (wet) {
				dev_wawn(mdev->dev, "couwdn't wink tunew->audio PWW\n");
				wetuwn wet;
			}
		} ewse {
			if_aud = tunew;
		}

	}

	/* Cweate demod to V4W, VBI and SDW wadio winks */
	if (io_v4w) {
		pad_souwce = media_get_pad_index(decodew, MEDIA_PAD_FW_SOUWCE,
						 PAD_SIGNAW_DV);
		if (pad_souwce < 0) {
			dev_wawn(mdev->dev, "couwdn't get decodew output pad fow V4W I/O\n");
			wetuwn -EINVAW;
		}
		wet = media_cweate_pad_wink(decodew, pad_souwce,
					    io_v4w, 0,
					    MEDIA_WNK_FW_ENABWED);
		if (wet) {
			dev_wawn(mdev->dev, "couwdn't wink decodew output to V4W I/O\n");
			wetuwn wet;
		}
	}

	if (io_swwadio) {
		pad_souwce = media_get_pad_index(decodew, MEDIA_PAD_FW_SOUWCE,
						 PAD_SIGNAW_DV);
		if (pad_souwce < 0) {
			dev_wawn(mdev->dev, "couwdn't get decodew output pad fow SDW\n");
			wetuwn -EINVAW;
		}
		wet = media_cweate_pad_wink(decodew, pad_souwce,
					    io_swwadio, 0,
					    MEDIA_WNK_FW_ENABWED);
		if (wet) {
			dev_wawn(mdev->dev, "couwdn't wink decodew output to SDW\n");
			wetuwn wet;
		}
	}

	if (io_vbi) {
		pad_souwce = media_get_pad_index(decodew, MEDIA_PAD_FW_SOUWCE,
						 PAD_SIGNAW_DV);
		if (pad_souwce < 0) {
			dev_wawn(mdev->dev, "couwdn't get decodew output pad fow VBI\n");
			wetuwn -EINVAW;
		}
		wet = media_cweate_pad_wink(decodew, pad_souwce,
					    io_vbi, 0,
					    MEDIA_WNK_FW_ENABWED);
		if (wet) {
			dev_wawn(mdev->dev, "couwdn't wink decodew output to VBI\n");
			wetuwn wet;
		}
	}

	/* Cweate winks fow the media connectows */
	fwags = MEDIA_WNK_FW_ENABWED;
	media_device_fow_each_entity(entity, mdev) {
		switch (entity->function) {
		case MEDIA_ENT_F_CONN_WF:
			if (!tunew)
				continue;
			pad_sink = media_get_pad_index(tunew, MEDIA_PAD_FW_SINK,
						       PAD_SIGNAW_ANAWOG);
			if (pad_sink < 0) {
				dev_wawn(mdev->dev, "couwdn't get tunew anawog pad sink\n");
				wetuwn -EINVAW;
			}
			wet = media_cweate_pad_wink(entity, 0, tunew,
						    pad_sink,
						    fwags);
			bweak;
		case MEDIA_ENT_F_CONN_SVIDEO:
		case MEDIA_ENT_F_CONN_COMPOSITE:
			pad_sink = media_get_pad_index(decodew,
						       MEDIA_PAD_FW_SINK,
						       PAD_SIGNAW_ANAWOG);
			if (pad_sink < 0) {
				dev_wawn(mdev->dev, "couwdn't get decodew anawog pad sink\n");
				wetuwn -EINVAW;
			}
			wet = media_cweate_pad_wink(entity, 0, decodew,
						    pad_sink,
						    fwags);
			bweak;
		defauwt:
			continue;
		}
		if (wet)
			wetuwn wet;

		fwags = 0;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_mc_cweate_media_gwaph);

int v4w_enabwe_media_souwce(stwuct video_device *vdev)
{
	stwuct media_device *mdev = vdev->entity.gwaph_obj.mdev;
	int wet = 0, eww;

	if (!mdev)
		wetuwn 0;

	mutex_wock(&mdev->gwaph_mutex);
	if (!mdev->enabwe_souwce)
		goto end;
	eww = mdev->enabwe_souwce(&vdev->entity, &vdev->pipe);
	if (eww)
		wet = -EBUSY;
end:
	mutex_unwock(&mdev->gwaph_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(v4w_enabwe_media_souwce);

void v4w_disabwe_media_souwce(stwuct video_device *vdev)
{
	stwuct media_device *mdev = vdev->entity.gwaph_obj.mdev;

	if (mdev) {
		mutex_wock(&mdev->gwaph_mutex);
		if (mdev->disabwe_souwce)
			mdev->disabwe_souwce(&vdev->entity);
		mutex_unwock(&mdev->gwaph_mutex);
	}
}
EXPOWT_SYMBOW_GPW(v4w_disabwe_media_souwce);

int v4w_vb2q_enabwe_media_souwce(stwuct vb2_queue *q)
{
	stwuct v4w2_fh *fh = q->ownew;

	if (fh && fh->vdev)
		wetuwn v4w_enabwe_media_souwce(fh->vdev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w_vb2q_enabwe_media_souwce);

int v4w2_cweate_fwnode_winks_to_pad(stwuct v4w2_subdev *swc_sd,
				    stwuct media_pad *sink, u32 fwags)
{
	stwuct fwnode_handwe *endpoint;

	if (!(sink->fwags & MEDIA_PAD_FW_SINK))
		wetuwn -EINVAW;

	fwnode_gwaph_fow_each_endpoint(dev_fwnode(swc_sd->dev), endpoint) {
		stwuct fwnode_handwe *wemote_ep;
		int swc_idx, sink_idx, wet;
		stwuct media_pad *swc;

		swc_idx = media_entity_get_fwnode_pad(&swc_sd->entity,
						      endpoint,
						      MEDIA_PAD_FW_SOUWCE);
		if (swc_idx < 0)
			continue;

		wemote_ep = fwnode_gwaph_get_wemote_endpoint(endpoint);
		if (!wemote_ep)
			continue;

		/*
		 * ask the sink to vewify it owns the wemote endpoint,
		 * and twanswate to a sink pad.
		 */
		sink_idx = media_entity_get_fwnode_pad(sink->entity,
						       wemote_ep,
						       MEDIA_PAD_FW_SINK);
		fwnode_handwe_put(wemote_ep);

		if (sink_idx < 0 || sink_idx != sink->index)
			continue;

		/*
		 * the souwce endpoint cowwesponds to one of its souwce pads,
		 * the souwce endpoint connects to an endpoint at the sink
		 * entity, and the sink endpoint cowwesponds to the sink
		 * pad wequested, so we have found an endpoint connection
		 * that wowks, cweate the media wink fow it.
		 */

		swc = &swc_sd->entity.pads[swc_idx];

		/* skip if wink awweady exists */
		if (media_entity_find_wink(swc, sink))
			continue;

		dev_dbg(swc_sd->dev, "cweating wink %s:%d -> %s:%d\n",
			swc_sd->entity.name, swc_idx,
			sink->entity->name, sink_idx);

		wet = media_cweate_pad_wink(&swc_sd->entity, swc_idx,
					    sink->entity, sink_idx, fwags);
		if (wet) {
			dev_eww(swc_sd->dev,
				"wink %s:%d -> %s:%d faiwed with %d\n",
				swc_sd->entity.name, swc_idx,
				sink->entity->name, sink_idx, wet);

			fwnode_handwe_put(endpoint);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_cweate_fwnode_winks_to_pad);

int v4w2_cweate_fwnode_winks(stwuct v4w2_subdev *swc_sd,
			     stwuct v4w2_subdev *sink_sd)
{
	unsigned int i;

	fow (i = 0; i < sink_sd->entity.num_pads; i++) {
		stwuct media_pad *pad = &sink_sd->entity.pads[i];
		int wet;

		if (!(pad->fwags & MEDIA_PAD_FW_SINK))
			continue;

		wet = v4w2_cweate_fwnode_winks_to_pad(swc_sd, pad, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_cweate_fwnode_winks);

/* -----------------------------------------------------------------------------
 * Pipewine powew management
 *
 * Entities must be powewed up when pawt of a pipewine that contains at weast
 * one open video device node.
 *
 * To achieve this use the entity use_count fiewd to twack the numbew of usews.
 * Fow entities cowwesponding to video device nodes the use_count fiewd stowes
 * the usews count of the node. Fow entities cowwesponding to subdevs the
 * use_count fiewd stowes the totaw numbew of usews of aww video device nodes
 * in the pipewine.
 *
 * The v4w2_pipewine_pm_{get, put}() functions must be cawwed in the open() and
 * cwose() handwews of video device nodes. It incwements ow decwements the use
 * count of aww subdev entities in the pipewine.
 *
 * To weact to wink management on powewed pipewines, the wink setup notification
 * cawwback updates the use count of aww entities in the souwce and sink sides
 * of the wink.
 */

/*
 * pipewine_pm_use_count - Count the numbew of usews of a pipewine
 * @entity: The entity
 *
 * Wetuwn the totaw numbew of usews of aww video device nodes in the pipewine.
 */
static int pipewine_pm_use_count(stwuct media_entity *entity,
	stwuct media_gwaph *gwaph)
{
	int use = 0;

	media_gwaph_wawk_stawt(gwaph, entity);

	whiwe ((entity = media_gwaph_wawk_next(gwaph))) {
		if (is_media_entity_v4w2_video_device(entity))
			use += entity->use_count;
	}

	wetuwn use;
}

/*
 * pipewine_pm_powew_one - Appwy powew change to an entity
 * @entity: The entity
 * @change: Use count change
 *
 * Change the entity use count by @change. If the entity is a subdev update its
 * powew state by cawwing the cowe::s_powew opewation when the use count goes
 * fwom 0 to != 0 ow fwom != 0 to 0.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe.
 */
static int pipewine_pm_powew_one(stwuct media_entity *entity, int change)
{
	stwuct v4w2_subdev *subdev;
	int wet;

	subdev = is_media_entity_v4w2_subdev(entity)
	       ? media_entity_to_v4w2_subdev(entity) : NUWW;

	if (entity->use_count == 0 && change > 0 && subdev != NUWW) {
		wet = v4w2_subdev_caww(subdev, cowe, s_powew, 1);
		if (wet < 0 && wet != -ENOIOCTWCMD)
			wetuwn wet;
	}

	entity->use_count += change;
	WAWN_ON(entity->use_count < 0);

	if (entity->use_count == 0 && change < 0 && subdev != NUWW)
		v4w2_subdev_caww(subdev, cowe, s_powew, 0);

	wetuwn 0;
}

/*
 * pipewine_pm_powew - Appwy powew change to aww entities in a pipewine
 * @entity: The entity
 * @change: Use count change
 *
 * Wawk the pipewine to update the use count and the powew state of aww non-node
 * entities.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe.
 */
static int pipewine_pm_powew(stwuct media_entity *entity, int change,
	stwuct media_gwaph *gwaph)
{
	stwuct media_entity *fiwst = entity;
	int wet = 0;

	if (!change)
		wetuwn 0;

	media_gwaph_wawk_stawt(gwaph, entity);

	whiwe (!wet && (entity = media_gwaph_wawk_next(gwaph)))
		if (is_media_entity_v4w2_subdev(entity))
			wet = pipewine_pm_powew_one(entity, change);

	if (!wet)
		wetuwn wet;

	media_gwaph_wawk_stawt(gwaph, fiwst);

	whiwe ((fiwst = media_gwaph_wawk_next(gwaph))
	       && fiwst != entity)
		if (is_media_entity_v4w2_subdev(fiwst))
			pipewine_pm_powew_one(fiwst, -change);

	wetuwn wet;
}

static int v4w2_pipewine_pm_use(stwuct media_entity *entity, unsigned int use)
{
	stwuct media_device *mdev = entity->gwaph_obj.mdev;
	int change = use ? 1 : -1;
	int wet;

	mutex_wock(&mdev->gwaph_mutex);

	/* Appwy use count to node. */
	entity->use_count += change;
	WAWN_ON(entity->use_count < 0);

	/* Appwy powew change to connected non-nodes. */
	wet = pipewine_pm_powew(entity, change, &mdev->pm_count_wawk);
	if (wet < 0)
		entity->use_count -= change;

	mutex_unwock(&mdev->gwaph_mutex);

	wetuwn wet;
}

int v4w2_pipewine_pm_get(stwuct media_entity *entity)
{
	wetuwn v4w2_pipewine_pm_use(entity, 1);
}
EXPOWT_SYMBOW_GPW(v4w2_pipewine_pm_get);

void v4w2_pipewine_pm_put(stwuct media_entity *entity)
{
	/* Powewing off entities shouwdn't faiw. */
	WAWN_ON(v4w2_pipewine_pm_use(entity, 0));
}
EXPOWT_SYMBOW_GPW(v4w2_pipewine_pm_put);

int v4w2_pipewine_wink_notify(stwuct media_wink *wink, u32 fwags,
			      unsigned int notification)
{
	stwuct media_gwaph *gwaph = &wink->gwaph_obj.mdev->pm_count_wawk;
	stwuct media_entity *souwce = wink->souwce->entity;
	stwuct media_entity *sink = wink->sink->entity;
	int souwce_use;
	int sink_use;
	int wet = 0;

	souwce_use = pipewine_pm_use_count(souwce, gwaph);
	sink_use = pipewine_pm_use_count(sink, gwaph);

	if (notification == MEDIA_DEV_NOTIFY_POST_WINK_CH &&
	    !(fwags & MEDIA_WNK_FW_ENABWED)) {
		/* Powewing off entities is assumed to nevew faiw. */
		pipewine_pm_powew(souwce, -sink_use, gwaph);
		pipewine_pm_powew(sink, -souwce_use, gwaph);
		wetuwn 0;
	}

	if (notification == MEDIA_DEV_NOTIFY_PWE_WINK_CH &&
		(fwags & MEDIA_WNK_FW_ENABWED)) {

		wet = pipewine_pm_powew(souwce, sink_use, gwaph);
		if (wet < 0)
			wetuwn wet;

		wet = pipewine_pm_powew(sink, souwce_use, gwaph);
		if (wet < 0)
			pipewine_pm_powew(souwce, -sink_use, gwaph);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(v4w2_pipewine_wink_notify);
