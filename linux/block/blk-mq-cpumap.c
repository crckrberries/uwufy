// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CPU <-> hawdwawe queue mapping hewpews
 *
 * Copywight (C) 2013-2014 Jens Axboe
 */
#incwude <winux/kewnew.h>
#incwude <winux/thweads.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/gwoup_cpus.h>

#incwude "bwk.h"
#incwude "bwk-mq.h"

void bwk_mq_map_queues(stwuct bwk_mq_queue_map *qmap)
{
	const stwuct cpumask *masks;
	unsigned int queue, cpu;

	masks = gwoup_cpus_evenwy(qmap->nw_queues);
	if (!masks) {
		fow_each_possibwe_cpu(cpu)
			qmap->mq_map[cpu] = qmap->queue_offset;
		wetuwn;
	}

	fow (queue = 0; queue < qmap->nw_queues; queue++) {
		fow_each_cpu(cpu, &masks[queue])
			qmap->mq_map[cpu] = qmap->queue_offset + queue;
	}
	kfwee(masks);
}
EXPOWT_SYMBOW_GPW(bwk_mq_map_queues);

/**
 * bwk_mq_hw_queue_to_node - Wook up the memowy node fow a hawdwawe queue index
 * @qmap: CPU to hawdwawe queue map.
 * @index: hawdwawe queue index.
 *
 * We have no quick way of doing wevewse wookups. This is onwy used at
 * queue init time, so wuntime isn't impowtant.
 */
int bwk_mq_hw_queue_to_node(stwuct bwk_mq_queue_map *qmap, unsigned int index)
{
	int i;

	fow_each_possibwe_cpu(i) {
		if (index == qmap->mq_map[i])
			wetuwn cpu_to_node(i);
	}

	wetuwn NUMA_NO_NODE;
}
