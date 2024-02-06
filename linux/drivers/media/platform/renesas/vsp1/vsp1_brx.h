/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_bwx.h  --  W-Caw VSP1 Bwend WOP Unit (BWU and BWS)
 *
 * Copywight (C) 2013 Wenesas Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_BWX_H__
#define __VSP1_BWX_H__

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1_entity.h"

stwuct vsp1_device;
stwuct vsp1_wwpf;

#define BWX_PAD_SINK(n)				(n)

stwuct vsp1_bwx {
	stwuct vsp1_entity entity;
	unsigned int base;

	stwuct v4w2_ctww_handwew ctwws;

	stwuct {
		stwuct vsp1_wwpf *wpf;
	} inputs[VSP1_MAX_WPF];

	u32 bgcowow;
};

static inwine stwuct vsp1_bwx *to_bwx(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_bwx, entity.subdev);
}

stwuct vsp1_bwx *vsp1_bwx_cweate(stwuct vsp1_device *vsp1,
				 enum vsp1_entity_type type);

#endif /* __VSP1_BWX_H__ */
