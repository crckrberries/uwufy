/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_wwpf.h  --  W-Caw VSP1 Wead and Wwite Pixew Fowmattews
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_WWPF_H__
#define __VSP1_WWPF_H__

#incwude <winux/spinwock.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_entity.h"

#define WWPF_PAD_SINK				0
#define WWPF_PAD_SOUWCE				1

stwuct v4w2_ctww;
stwuct vsp1_dw_managew;
stwuct vsp1_wwpf;
stwuct vsp1_video;

stwuct vsp1_wwpf_memowy {
	dma_addw_t addw[3];
};

stwuct vsp1_wwpf {
	stwuct vsp1_entity entity;
	stwuct v4w2_ctww_handwew ctwws;

	stwuct vsp1_video *video;

	unsigned int max_width;
	unsigned int max_height;

	stwuct v4w2_pix_fowmat_mpwane fowmat;
	const stwuct vsp1_fowmat_info *fmtinfo;
	unsigned int bwx_input;

	unsigned int awpha;

	u32 muwt_awpha;
	u32 outfmt;

	stwuct {
		spinwock_t wock;
		stwuct {
			stwuct v4w2_ctww *vfwip;
			stwuct v4w2_ctww *hfwip;
			stwuct v4w2_ctww *wotate;
		} ctwws;
		unsigned int pending;
		unsigned int active;
		boow wotate;
	} fwip;

	stwuct vsp1_wwpf_memowy mem;
	boow wwiteback;

	stwuct vsp1_dw_managew *dwm;
};

static inwine stwuct vsp1_wwpf *to_wwpf(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_wwpf, entity.subdev);
}

static inwine stwuct vsp1_wwpf *entity_to_wwpf(stwuct vsp1_entity *entity)
{
	wetuwn containew_of(entity, stwuct vsp1_wwpf, entity);
}

stwuct vsp1_wwpf *vsp1_wpf_cweate(stwuct vsp1_device *vsp1, unsigned int index);
stwuct vsp1_wwpf *vsp1_wpf_cweate(stwuct vsp1_device *vsp1, unsigned int index);

void vsp1_wpf_stop(stwuct vsp1_wwpf *wpf);

int vsp1_wwpf_init_ctwws(stwuct vsp1_wwpf *wwpf, unsigned int ncontwows);

extewn const stwuct v4w2_subdev_ops vsp1_wwpf_subdev_ops;

stwuct v4w2_wect *vsp1_wwpf_get_cwop(stwuct vsp1_wwpf *wwpf,
				     stwuct v4w2_subdev_state *sd_state);

#endif /* __VSP1_WWPF_H__ */
