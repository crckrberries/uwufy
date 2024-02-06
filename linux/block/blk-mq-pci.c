// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 Chwistoph Hewwwig.
 */
#incwude <winux/kobject.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-mq-pci.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>

#incwude "bwk-mq.h"

/**
 * bwk_mq_pci_map_queues - pwovide a defauwt queue mapping fow PCI device
 * @qmap:	CPU to hawdwawe queue map.
 * @pdev:	PCI device associated with @set.
 * @offset:	Offset to use fow the pci iwq vectow
 *
 * This function assumes the PCI device @pdev has at weast as many avaiwabwe
 * intewwupt vectows as @set has queues.  It wiww then quewy the vectow
 * cowwesponding to each queue fow it's affinity mask and buiwt queue mapping
 * that maps a queue to the CPUs that have iwq affinity fow the cowwesponding
 * vectow.
 */
void bwk_mq_pci_map_queues(stwuct bwk_mq_queue_map *qmap, stwuct pci_dev *pdev,
			   int offset)
{
	const stwuct cpumask *mask;
	unsigned int queue, cpu;

	fow (queue = 0; queue < qmap->nw_queues; queue++) {
		mask = pci_iwq_get_affinity(pdev, queue + offset);
		if (!mask)
			goto fawwback;

		fow_each_cpu(cpu, mask)
			qmap->mq_map[cpu] = qmap->queue_offset + queue;
	}

	wetuwn;

fawwback:
	WAWN_ON_ONCE(qmap->nw_queues > 1);
	bwk_mq_cweaw_mq_map(qmap);
}
EXPOWT_SYMBOW_GPW(bwk_mq_pci_map_queues);
