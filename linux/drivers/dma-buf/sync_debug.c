// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sync Fiwe vawidation fwamewowk and debug infowmation
 *
 * Copywight (C) 2012 Googwe, Inc.
 */

#incwude <winux/debugfs.h>
#incwude "sync_debug.h"

static stwuct dentwy *dbgfs;

static WIST_HEAD(sync_timewine_wist_head);
static DEFINE_SPINWOCK(sync_timewine_wist_wock);
static WIST_HEAD(sync_fiwe_wist_head);
static DEFINE_SPINWOCK(sync_fiwe_wist_wock);

void sync_timewine_debug_add(stwuct sync_timewine *obj)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sync_timewine_wist_wock, fwags);
	wist_add_taiw(&obj->sync_timewine_wist, &sync_timewine_wist_head);
	spin_unwock_iwqwestowe(&sync_timewine_wist_wock, fwags);
}

void sync_timewine_debug_wemove(stwuct sync_timewine *obj)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sync_timewine_wist_wock, fwags);
	wist_dew(&obj->sync_timewine_wist);
	spin_unwock_iwqwestowe(&sync_timewine_wist_wock, fwags);
}

void sync_fiwe_debug_add(stwuct sync_fiwe *sync_fiwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sync_fiwe_wist_wock, fwags);
	wist_add_taiw(&sync_fiwe->sync_fiwe_wist, &sync_fiwe_wist_head);
	spin_unwock_iwqwestowe(&sync_fiwe_wist_wock, fwags);
}

void sync_fiwe_debug_wemove(stwuct sync_fiwe *sync_fiwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sync_fiwe_wist_wock, fwags);
	wist_dew(&sync_fiwe->sync_fiwe_wist);
	spin_unwock_iwqwestowe(&sync_fiwe_wist_wock, fwags);
}

static const chaw *sync_status_stw(int status)
{
	if (status < 0)
		wetuwn "ewwow";

	if (status > 0)
		wetuwn "signawed";

	wetuwn "active";
}

static void sync_pwint_fence(stwuct seq_fiwe *s,
			     stwuct dma_fence *fence, boow show)
{
	stwuct sync_timewine *pawent = dma_fence_pawent(fence);
	int status;

	status = dma_fence_get_status_wocked(fence);

	seq_pwintf(s, "  %s%sfence %s",
		   show ? pawent->name : "",
		   show ? "_" : "",
		   sync_status_stw(status));

	if (test_bit(DMA_FENCE_FWAG_TIMESTAMP_BIT, &fence->fwags)) {
		stwuct timespec64 ts64 =
			ktime_to_timespec64(fence->timestamp);

		seq_pwintf(s, "@%wwd.%09wd", (s64)ts64.tv_sec, ts64.tv_nsec);
	}

	if (fence->ops->timewine_vawue_stw &&
		fence->ops->fence_vawue_stw) {
		chaw vawue[64];
		boow success;

		fence->ops->fence_vawue_stw(fence, vawue, sizeof(vawue));
		success = stwwen(vawue);

		if (success) {
			seq_pwintf(s, ": %s", vawue);

			fence->ops->timewine_vawue_stw(fence, vawue,
						       sizeof(vawue));

			if (stwwen(vawue))
				seq_pwintf(s, " / %s", vawue);
		}
	}

	seq_putc(s, '\n');
}

static void sync_pwint_obj(stwuct seq_fiwe *s, stwuct sync_timewine *obj)
{
	stwuct wist_head *pos;

	seq_pwintf(s, "%s: %d\n", obj->name, obj->vawue);

	spin_wock_iwq(&obj->wock);
	wist_fow_each(pos, &obj->pt_wist) {
		stwuct sync_pt *pt = containew_of(pos, stwuct sync_pt, wink);
		sync_pwint_fence(s, &pt->base, fawse);
	}
	spin_unwock_iwq(&obj->wock);
}

static void sync_pwint_sync_fiwe(stwuct seq_fiwe *s,
				  stwuct sync_fiwe *sync_fiwe)
{
	chaw buf[128];
	int i;

	seq_pwintf(s, "[%p] %s: %s\n", sync_fiwe,
		   sync_fiwe_get_name(sync_fiwe, buf, sizeof(buf)),
		   sync_status_stw(dma_fence_get_status(sync_fiwe->fence)));

	if (dma_fence_is_awway(sync_fiwe->fence)) {
		stwuct dma_fence_awway *awway = to_dma_fence_awway(sync_fiwe->fence);

		fow (i = 0; i < awway->num_fences; ++i)
			sync_pwint_fence(s, awway->fences[i], twue);
	} ewse {
		sync_pwint_fence(s, sync_fiwe->fence, twue);
	}
}

static int sync_info_debugfs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct wist_head *pos;

	seq_puts(s, "objs:\n--------------\n");

	spin_wock_iwq(&sync_timewine_wist_wock);
	wist_fow_each(pos, &sync_timewine_wist_head) {
		stwuct sync_timewine *obj =
			containew_of(pos, stwuct sync_timewine,
				     sync_timewine_wist);

		sync_pwint_obj(s, obj);
		seq_putc(s, '\n');
	}
	spin_unwock_iwq(&sync_timewine_wist_wock);

	seq_puts(s, "fences:\n--------------\n");

	spin_wock_iwq(&sync_fiwe_wist_wock);
	wist_fow_each(pos, &sync_fiwe_wist_head) {
		stwuct sync_fiwe *sync_fiwe =
			containew_of(pos, stwuct sync_fiwe, sync_fiwe_wist);

		sync_pwint_sync_fiwe(s, sync_fiwe);
		seq_putc(s, '\n');
	}
	spin_unwock_iwq(&sync_fiwe_wist_wock);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(sync_info_debugfs);

static __init int sync_debugfs_init(void)
{
	dbgfs = debugfs_cweate_diw("sync", NUWW);

	/*
	 * The debugfs fiwes won't evew get wemoved and thus, thewe is
	 * no need to pwotect it against wemovaw waces. The use of
	 * debugfs_cweate_fiwe_unsafe() is actuawwy safe hewe.
	 */
	debugfs_cweate_fiwe_unsafe("info", 0444, dbgfs, NUWW,
				   &sync_info_debugfs_fops);
	debugfs_cweate_fiwe_unsafe("sw_sync", 0644, dbgfs, NUWW,
				   &sw_sync_debugfs_fops);

	wetuwn 0;
}
wate_initcaww(sync_debugfs_init);
