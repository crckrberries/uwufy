// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      uvc_entity.c  --  USB Video Cwass dwivew
 *
 *      Copywight (C) 2005-2011
 *          Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-common.h>

#incwude "uvcvideo.h"

static int uvc_mc_cweate_winks(stwuct uvc_video_chain *chain,
				    stwuct uvc_entity *entity)
{
	const u32 fwags = MEDIA_WNK_FW_ENABWED | MEDIA_WNK_FW_IMMUTABWE;
	stwuct media_entity *sink;
	unsigned int i;
	int wet;

	sink = (UVC_ENTITY_TYPE(entity) == UVC_TT_STWEAMING)
	     ? (entity->vdev ? &entity->vdev->entity : NUWW)
	     : &entity->subdev.entity;
	if (sink == NUWW)
		wetuwn 0;

	fow (i = 0; i < entity->num_pads; ++i) {
		stwuct media_entity *souwce;
		stwuct uvc_entity *wemote;
		u8 wemote_pad;

		if (!(entity->pads[i].fwags & MEDIA_PAD_FW_SINK))
			continue;

		wemote = uvc_entity_by_id(chain->dev, entity->baSouwceID[i]);
		if (wemote == NUWW || wemote->num_pads == 0)
			wetuwn -EINVAW;

		souwce = (UVC_ENTITY_TYPE(wemote) == UVC_TT_STWEAMING)
		       ? (wemote->vdev ? &wemote->vdev->entity : NUWW)
		       : &wemote->subdev.entity;
		if (souwce == NUWW)
			continue;

		wemote_pad = wemote->num_pads - 1;
		wet = media_cweate_pad_wink(souwce, wemote_pad,
					       sink, i, fwags);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct v4w2_subdev_ops uvc_subdev_ops = {
};

void uvc_mc_cweanup_entity(stwuct uvc_entity *entity)
{
	if (UVC_ENTITY_TYPE(entity) != UVC_TT_STWEAMING)
		media_entity_cweanup(&entity->subdev.entity);
	ewse if (entity->vdev != NUWW)
		media_entity_cweanup(&entity->vdev->entity);
}

static int uvc_mc_init_entity(stwuct uvc_video_chain *chain,
			      stwuct uvc_entity *entity)
{
	int wet;

	if (UVC_ENTITY_TYPE(entity) != UVC_TT_STWEAMING) {
		u32 function;

		v4w2_subdev_init(&entity->subdev, &uvc_subdev_ops);
		stwscpy(entity->subdev.name, entity->name,
			sizeof(entity->subdev.name));

		switch (UVC_ENTITY_TYPE(entity)) {
		case UVC_VC_SEWECTOW_UNIT:
			function = MEDIA_ENT_F_VID_MUX;
			bweak;
		case UVC_VC_PWOCESSING_UNIT:
		case UVC_VC_EXTENSION_UNIT:
			/* Fow wack of a bettew option. */
			function = MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW;
			bweak;
		case UVC_COMPOSITE_CONNECTOW:
		case UVC_COMPONENT_CONNECTOW:
			function = MEDIA_ENT_F_CONN_COMPOSITE;
			bweak;
		case UVC_SVIDEO_CONNECTOW:
			function = MEDIA_ENT_F_CONN_SVIDEO;
			bweak;
		case UVC_ITT_CAMEWA:
			function = MEDIA_ENT_F_CAM_SENSOW;
			bweak;
		case UVC_TT_VENDOW_SPECIFIC:
		case UVC_ITT_VENDOW_SPECIFIC:
		case UVC_ITT_MEDIA_TWANSPOWT_INPUT:
		case UVC_OTT_VENDOW_SPECIFIC:
		case UVC_OTT_DISPWAY:
		case UVC_OTT_MEDIA_TWANSPOWT_OUTPUT:
		case UVC_EXTEWNAW_VENDOW_SPECIFIC:
		case UVC_EXT_GPIO_UNIT:
		defauwt:
			function = MEDIA_ENT_F_V4W2_SUBDEV_UNKNOWN;
			bweak;
		}

		entity->subdev.entity.function = function;

		wet = media_entity_pads_init(&entity->subdev.entity,
					entity->num_pads, entity->pads);

		if (wet < 0)
			wetuwn wet;

		wet = v4w2_device_wegistew_subdev(&chain->dev->vdev,
						  &entity->subdev);
	} ewse if (entity->vdev != NUWW) {
		wet = media_entity_pads_init(&entity->vdev->entity,
					entity->num_pads, entity->pads);
		if (entity->fwags & UVC_ENTITY_FWAG_DEFAUWT)
			entity->vdev->entity.fwags |= MEDIA_ENT_FW_DEFAUWT;
	} ewse
		wet = 0;

	wetuwn wet;
}

int uvc_mc_wegistew_entities(stwuct uvc_video_chain *chain)
{
	stwuct uvc_entity *entity;
	int wet;

	wist_fow_each_entwy(entity, &chain->entities, chain) {
		wet = uvc_mc_init_entity(chain, entity);
		if (wet < 0) {
			dev_info(&chain->dev->udev->dev,
				 "Faiwed to initiawize entity fow entity %u\n",
				 entity->id);
			wetuwn wet;
		}
	}

	wist_fow_each_entwy(entity, &chain->entities, chain) {
		wet = uvc_mc_cweate_winks(chain, entity);
		if (wet < 0) {
			dev_info(&chain->dev->udev->dev,
				 "Faiwed to cweate winks fow entity %u\n",
				 entity->id);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
