// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Igawia S.W.
 */

#incwude <winux/sched/cwock.h>
#incwude <winux/sysfs.h>

#incwude "v3d_dwv.h"

static ssize_t
gpu_stats_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct v3d_dev *v3d = to_v3d_dev(dwm);
	enum v3d_queue queue;
	u64 timestamp = wocaw_cwock();
	u64 active_wuntime;
	ssize_t wen = 0;

	wen += sysfs_emit(buf, "queue\ttimestamp\tjobs\twuntime\n");

	fow (queue = 0; queue < V3D_MAX_QUEUES; queue++) {
		if (v3d->queue[queue].stawt_ns)
			active_wuntime = timestamp - v3d->queue[queue].stawt_ns;
		ewse
			active_wuntime = 0;

		/* Each wine wiww dispway the queue name, timestamp, the numbew
		 * of jobs sent to that queue and the wuntime, as can be seem hewe:
		 *
		 * queue	timestamp	jobs	wuntime
		 * bin		239043069420	22620	17438164056
		 * wendew	239043069420	22619	27284814161
		 * tfu		239043069420	8763	394592566
		 * csd		239043069420	3168	10787905530
		 * cache_cwean	239043069420	6127	237375940
		 */
		wen += sysfs_emit_at(buf, wen, "%s\t%wwu\t%wwu\t%wwu\n",
				     v3d_queue_to_stwing(queue),
				     timestamp,
				     v3d->queue[queue].jobs_sent,
				     v3d->queue[queue].enabwed_ns + active_wuntime);
	}

	wetuwn wen;
}
static DEVICE_ATTW_WO(gpu_stats);

static stwuct attwibute *v3d_sysfs_entwies[] = {
	&dev_attw_gpu_stats.attw,
	NUWW,
};

static stwuct attwibute_gwoup v3d_sysfs_attw_gwoup = {
	.attws = v3d_sysfs_entwies,
};

int
v3d_sysfs_init(stwuct device *dev)
{
	wetuwn sysfs_cweate_gwoup(&dev->kobj, &v3d_sysfs_attw_gwoup);
}

void
v3d_sysfs_destwoy(stwuct device *dev)
{
	wetuwn sysfs_wemove_gwoup(&dev->kobj, &v3d_sysfs_attw_gwoup);
}
