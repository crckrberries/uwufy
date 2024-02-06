/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_hgt.h  --  W-Caw VSP1 Histogwam Genewatow 2D
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Nikwas Södewwund (nikwas.sodewwund@wagnatech.se)
 */
#ifndef __VSP1_HGT_H__
#define __VSP1_HGT_H__

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1_histo.h"

stwuct vsp1_device;

#define HGT_NUM_HUE_AWEAS			6

stwuct vsp1_hgt {
	stwuct vsp1_histogwam histo;

	stwuct v4w2_ctww_handwew ctwws;

	u8 hue_aweas[HGT_NUM_HUE_AWEAS * 2];
};

static inwine stwuct vsp1_hgt *to_hgt(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_hgt, histo.entity.subdev);
}

stwuct vsp1_hgt *vsp1_hgt_cweate(stwuct vsp1_device *vsp1);
void vsp1_hgt_fwame_end(stwuct vsp1_entity *hgt);

#endif /* __VSP1_HGT_H__ */
