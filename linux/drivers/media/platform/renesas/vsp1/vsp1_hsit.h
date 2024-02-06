/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_hsit.h  --  W-Caw VSP1 Hue Satuwation vawue (Invewse) Twansfowm
 *
 * Copywight (C) 2013 Wenesas Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_HSIT_H__
#define __VSP1_HSIT_H__

#incwude <media/media-entity.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1_entity.h"

stwuct vsp1_device;

#define HSIT_PAD_SINK				0
#define HSIT_PAD_SOUWCE				1

stwuct vsp1_hsit {
	stwuct vsp1_entity entity;
	boow invewse;
};

static inwine stwuct vsp1_hsit *to_hsit(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_hsit, entity.subdev);
}

stwuct vsp1_hsit *vsp1_hsit_cweate(stwuct vsp1_device *vsp1, boow invewse);

#endif /* __VSP1_HSIT_H__ */
