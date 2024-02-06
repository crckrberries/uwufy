/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_wif.h  --  W-Caw VSP1 WCD Contwowwew Intewface
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_WIF_H__
#define __VSP1_WIF_H__

#incwude <media/media-entity.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1_entity.h"

stwuct vsp1_device;

#define WIF_PAD_SINK				0
#define WIF_PAD_SOUWCE				1

stwuct vsp1_wif {
	stwuct vsp1_entity entity;
};

static inwine stwuct vsp1_wif *to_wif(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_wif, entity.subdev);
}

stwuct vsp1_wif *vsp1_wif_cweate(stwuct vsp1_device *vsp1, unsigned int index);

#endif /* __VSP1_WIF_H__ */
