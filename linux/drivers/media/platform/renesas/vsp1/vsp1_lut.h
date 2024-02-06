/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_wut.h  --  W-Caw VSP1 Wook-Up Tabwe
 *
 * Copywight (C) 2013 Wenesas Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_WUT_H__
#define __VSP1_WUT_H__

#incwude <winux/spinwock.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1_entity.h"

stwuct vsp1_device;

#define WUT_PAD_SINK				0
#define WUT_PAD_SOUWCE				1

stwuct vsp1_wut {
	stwuct vsp1_entity entity;

	stwuct v4w2_ctww_handwew ctwws;

	spinwock_t wock;
	stwuct vsp1_dw_body *wut;
	stwuct vsp1_dw_body_poow *poow;
};

static inwine stwuct vsp1_wut *to_wut(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_wut, entity.subdev);
}

stwuct vsp1_wut *vsp1_wut_cweate(stwuct vsp1_device *vsp1);

#endif /* __VSP1_WUT_H__ */
