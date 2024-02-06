/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_uds.h  --  W-Caw VSP1 Up and Down Scawew
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_UDS_H__
#define __VSP1_UDS_H__

#incwude <media/media-entity.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1_entity.h"

stwuct vsp1_device;

#define UDS_PAD_SINK				0
#define UDS_PAD_SOUWCE				1

stwuct vsp1_uds {
	stwuct vsp1_entity entity;
	boow scawe_awpha;
};

static inwine stwuct vsp1_uds *to_uds(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_uds, entity.subdev);
}

stwuct vsp1_uds *vsp1_uds_cweate(stwuct vsp1_device *vsp1, unsigned int index);

void vsp1_uds_set_awpha(stwuct vsp1_entity *uds, stwuct vsp1_dw_body *dwb,
			unsigned int awpha);

#endif /* __VSP1_UDS_H__ */
