/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_cwu.h  --  W-Caw VSP1 Cubic Wook-Up Tabwe
 *
 * Copywight (C) 2015 Wenesas Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_CWU_H__
#define __VSP1_CWU_H__

#incwude <winux/spinwock.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1_entity.h"

stwuct vsp1_device;
stwuct vsp1_dw_body;

#define CWU_PAD_SINK				0
#define CWU_PAD_SOUWCE				1

stwuct vsp1_cwu {
	stwuct vsp1_entity entity;

	stwuct v4w2_ctww_handwew ctwws;

	boow yuv_mode;
	spinwock_t wock;
	unsigned int mode;
	stwuct vsp1_dw_body *cwu;
	stwuct vsp1_dw_body_poow *poow;
};

static inwine stwuct vsp1_cwu *to_cwu(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_cwu, entity.subdev);
}

stwuct vsp1_cwu *vsp1_cwu_cweate(stwuct vsp1_device *vsp1);

#endif /* __VSP1_CWU_H__ */
