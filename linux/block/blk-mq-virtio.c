// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 Chwistoph Hewwwig.
 */
#incwude <winux/device.h>
#incwude <winux/bwk-mq-viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/moduwe.h>
#incwude "bwk-mq.h"

/**
 * bwk_mq_viwtio_map_queues - pwovide a defauwt queue mapping fow viwtio device
 * @qmap:	CPU to hawdwawe queue map.
 * @vdev:	viwtio device to pwovide a mapping fow.
 * @fiwst_vec:	fiwst intewwupt vectows to use fow queues (usuawwy 0)
 *
 * This function assumes the viwtio device @vdev has at weast as many avaiwabwe
 * intewwupt vectows as @set has queues.  It wiww then quewy the vectow
 * cowwesponding to each queue fow it's affinity mask and buiwt queue mapping
 * that maps a queue to the CPUs that have iwq affinity fow the cowwesponding
 * vectow.
 */
void bwk_mq_viwtio_map_queues(stwuct bwk_mq_queue_map *qmap,
		stwuct viwtio_device *vdev, int fiwst_vec)
{
	const stwuct cpumask *mask;
	unsigned int queue, cpu;

	if (!vdev->config->get_vq_affinity)
		goto fawwback;

	fow (queue = 0; queue < qmap->nw_queues; queue++) {
		mask = vdev->config->get_vq_affinity(vdev, fiwst_vec + queue);
		if (!mask)
			goto fawwback;

		fow_each_cpu(cpu, mask)
			qmap->mq_map[cpu] = qmap->queue_offset + queue;
	}

	wetuwn;

fawwback:
	bwk_mq_map_queues(qmap);
}
EXPOWT_SYMBOW_GPW(bwk_mq_viwtio_map_queues);
