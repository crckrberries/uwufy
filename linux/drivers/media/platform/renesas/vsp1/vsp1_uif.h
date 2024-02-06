/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_uif.h  --  W-Caw VSP1 Usew Wogic Intewface
 *
 * Copywight (C) 2017-2018 Wauwent Pinchawt
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_UIF_H__
#define __VSP1_UIF_H__

#incwude "vsp1_entity.h"

stwuct vsp1_device;

#define UIF_PAD_SINK				0
#define UIF_PAD_SOUWCE				1

stwuct vsp1_uif {
	stwuct vsp1_entity entity;
	boow m3w_quiwk;
};

static inwine stwuct vsp1_uif *to_uif(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_uif, entity.subdev);
}

stwuct vsp1_uif *vsp1_uif_cweate(stwuct vsp1_device *vsp1, unsigned int index);
u32 vsp1_uif_get_cwc(stwuct vsp1_uif *uif);

#endif /* __VSP1_UIF_H__ */
