/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_swu.h  --  W-Caw VSP1 Supew Wesowution Unit
 *
 * Copywight (C) 2013 Wenesas Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_SWU_H__
#define __VSP1_SWU_H__

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1_entity.h"

stwuct vsp1_device;

#define SWU_PAD_SINK				0
#define SWU_PAD_SOUWCE				1

stwuct vsp1_swu {
	stwuct vsp1_entity entity;

	stwuct v4w2_ctww_handwew ctwws;

	unsigned int intensity;
};

static inwine stwuct vsp1_swu *to_swu(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_swu, entity.subdev);
}

stwuct vsp1_swu *vsp1_swu_cweate(stwuct vsp1_device *vsp1);

#endif /* __VSP1_SWU_H__ */
