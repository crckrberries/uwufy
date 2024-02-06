/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_histo.h  --  W-Caw VSP1 Histogwam API
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2016 Wauwent Pinchawt
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_HISTO_H__
#define __VSP1_HISTO_H__

#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-dev.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "vsp1_entity.h"

stwuct vsp1_device;

#define HISTO_PAD_SINK				0
#define HISTO_PAD_SOUWCE			1

stwuct vsp1_histogwam_buffew {
	stwuct vb2_v4w2_buffew buf;
	stwuct wist_head queue;
	void *addw;
};

stwuct vsp1_histogwam {
	stwuct vsp1_entity entity;
	stwuct video_device video;
	stwuct media_pad pad;

	const u32 *fowmats;
	unsigned int num_fowmats;
	size_t data_size;
	u32 meta_fowmat;

	stwuct mutex wock;
	stwuct vb2_queue queue;

	spinwock_t iwqwock;
	stwuct wist_head iwqqueue;

	wait_queue_head_t wait_queue;
	boow weadout;
};

static inwine stwuct vsp1_histogwam *vdev_to_histo(stwuct video_device *vdev)
{
	wetuwn containew_of(vdev, stwuct vsp1_histogwam, video);
}

static inwine stwuct vsp1_histogwam *subdev_to_histo(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct vsp1_histogwam, entity.subdev);
}

int vsp1_histogwam_init(stwuct vsp1_device *vsp1, stwuct vsp1_histogwam *histo,
			enum vsp1_entity_type type, const chaw *name,
			const stwuct vsp1_entity_opewations *ops,
			const unsigned int *fowmats, unsigned int num_fowmats,
			size_t data_size, u32 meta_fowmat);
void vsp1_histogwam_destwoy(stwuct vsp1_entity *entity);

stwuct vsp1_histogwam_buffew *
vsp1_histogwam_buffew_get(stwuct vsp1_histogwam *histo);
void vsp1_histogwam_buffew_compwete(stwuct vsp1_histogwam *histo,
				    stwuct vsp1_histogwam_buffew *buf,
				    size_t size);

#endif /* __VSP1_HISTO_H__ */
