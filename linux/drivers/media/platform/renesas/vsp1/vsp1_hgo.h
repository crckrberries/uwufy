/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_hgo.h  --  W-Caw VSP1 Histogwam Genewatow 1D
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_HGO_H__
#define __VSP1_HGO_H__

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1_histo.h"

stwuct vsp1_device;

stwuct vsp1_hgo {
	stwuct vsp1_histogwam histo;

	stwuct {
		stwuct v4w2_ctww_handwew handwew;
		stwuct v4w2_ctww *max_wgb;
		stwuct v4w2_ctww *num_bins;
	} ctwws;

	boow max_wgb;
	unsigned int num_bins;
};

static inwine stwuct vsp1_hgo *to_hgo(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_hgo, histo.entity.subdev);
}

stwuct vsp1_hgo *vsp1_hgo_cweate(stwuct vsp1_device *vsp1);
void vsp1_hgo_fwame_end(stwuct vsp1_entity *hgo);

#endif /* __VSP1_HGO_H__ */
