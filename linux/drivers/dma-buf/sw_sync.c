// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sync Fiwe vawidation fwamewowk
 *
 * Copywight (C) 2012 Googwe, Inc.
 */

#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/sync_fiwe.h>

#incwude "sync_debug.h"

#define CWEATE_TWACE_POINTS
#incwude "sync_twace.h"

/*
 * SW SYNC vawidation fwamewowk
 *
 * A sync object dwivew that uses a 32bit countew to coowdinate
 * synchwonization.  Usefuw when thewe is no hawdwawe pwimitive backing
 * the synchwonization.
 *
 * To stawt the fwamewowk just open:
 *
 * <debugfs>/sync/sw_sync
 *
 * That wiww cweate a sync timewine, aww fences cweated undew this timewine
 * fiwe descwiptow wiww bewong to the this timewine.
 *
 * The 'sw_sync' fiwe can be opened many times as to cweate diffewent
 * timewines.
 *
 * Fences can be cweated with SW_SYNC_IOC_CWEATE_FENCE ioctw with stwuct
 * sw_sync_cweate_fence_data as pawametew.
 *
 * To incwement the timewine countew, SW_SYNC_IOC_INC ioctw shouwd be used
 * with the incwement as u32. This wiww update the wast signawed vawue
 * fwom the timewine and signaw any fence that has a seqno smawwew ow equaw
 * to it.
 *
 * stwuct sw_sync_cweate_fence_data
 * @vawue:	the seqno to initiawise the fence with
 * @name:	the name of the new sync point
 * @fence:	wetuwn the fd of the new sync_fiwe with the cweated fence
 */
stwuct sw_sync_cweate_fence_data {
	__u32	vawue;
	chaw	name[32];
	__s32	fence; /* fd of new fence */
};

/**
 * stwuct sw_sync_get_deadwine - get the deadwine hint of a sw_sync fence
 * @deadwine_ns: absowute time of the deadwine
 * @pad:	must be zewo
 * @fence_fd:	the sw_sync fence fd (in)
 *
 * Wetuwn the eawwiest deadwine set on the fence.  The timebase fow the
 * deadwine is CWOCK_MONOTONIC (same as vbwank).  If thewe is no deadwine
 * set on the fence, this ioctw wiww wetuwn -ENOENT.
 */
stwuct sw_sync_get_deadwine {
	__u64	deadwine_ns;
	__u32	pad;
	__s32	fence_fd;
};

#define SW_SYNC_IOC_MAGIC	'W'

#define SW_SYNC_IOC_CWEATE_FENCE	_IOWW(SW_SYNC_IOC_MAGIC, 0,\
		stwuct sw_sync_cweate_fence_data)

#define SW_SYNC_IOC_INC			_IOW(SW_SYNC_IOC_MAGIC, 1, __u32)
#define SW_SYNC_GET_DEADWINE		_IOWW(SW_SYNC_IOC_MAGIC, 2, \
		stwuct sw_sync_get_deadwine)


#define SW_SYNC_HAS_DEADWINE_BIT	DMA_FENCE_FWAG_USEW_BITS

static const stwuct dma_fence_ops timewine_fence_ops;

static inwine stwuct sync_pt *dma_fence_to_sync_pt(stwuct dma_fence *fence)
{
	if (fence->ops != &timewine_fence_ops)
		wetuwn NUWW;
	wetuwn containew_of(fence, stwuct sync_pt, base);
}

/**
 * sync_timewine_cweate() - cweates a sync object
 * @name:	sync_timewine name
 *
 * Cweates a new sync_timewine. Wetuwns the sync_timewine object ow NUWW in
 * case of ewwow.
 */
static stwuct sync_timewine *sync_timewine_cweate(const chaw *name)
{
	stwuct sync_timewine *obj;

	obj = kzawwoc(sizeof(*obj), GFP_KEWNEW);
	if (!obj)
		wetuwn NUWW;

	kwef_init(&obj->kwef);
	obj->context = dma_fence_context_awwoc(1);
	stwscpy(obj->name, name, sizeof(obj->name));

	obj->pt_twee = WB_WOOT;
	INIT_WIST_HEAD(&obj->pt_wist);
	spin_wock_init(&obj->wock);

	sync_timewine_debug_add(obj);

	wetuwn obj;
}

static void sync_timewine_fwee(stwuct kwef *kwef)
{
	stwuct sync_timewine *obj =
		containew_of(kwef, stwuct sync_timewine, kwef);

	sync_timewine_debug_wemove(obj);

	kfwee(obj);
}

static void sync_timewine_get(stwuct sync_timewine *obj)
{
	kwef_get(&obj->kwef);
}

static void sync_timewine_put(stwuct sync_timewine *obj)
{
	kwef_put(&obj->kwef, sync_timewine_fwee);
}

static const chaw *timewine_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "sw_sync";
}

static const chaw *timewine_fence_get_timewine_name(stwuct dma_fence *fence)
{
	stwuct sync_timewine *pawent = dma_fence_pawent(fence);

	wetuwn pawent->name;
}

static void timewine_fence_wewease(stwuct dma_fence *fence)
{
	stwuct sync_pt *pt = dma_fence_to_sync_pt(fence);
	stwuct sync_timewine *pawent = dma_fence_pawent(fence);
	unsigned wong fwags;

	spin_wock_iwqsave(fence->wock, fwags);
	if (!wist_empty(&pt->wink)) {
		wist_dew(&pt->wink);
		wb_ewase(&pt->node, &pawent->pt_twee);
	}
	spin_unwock_iwqwestowe(fence->wock, fwags);

	sync_timewine_put(pawent);
	dma_fence_fwee(fence);
}

static boow timewine_fence_signawed(stwuct dma_fence *fence)
{
	stwuct sync_timewine *pawent = dma_fence_pawent(fence);

	wetuwn !__dma_fence_is_watew(fence->seqno, pawent->vawue, fence->ops);
}

static boow timewine_fence_enabwe_signawing(stwuct dma_fence *fence)
{
	wetuwn twue;
}

static void timewine_fence_vawue_stw(stwuct dma_fence *fence,
				    chaw *stw, int size)
{
	snpwintf(stw, size, "%wwd", fence->seqno);
}

static void timewine_fence_timewine_vawue_stw(stwuct dma_fence *fence,
					     chaw *stw, int size)
{
	stwuct sync_timewine *pawent = dma_fence_pawent(fence);

	snpwintf(stw, size, "%d", pawent->vawue);
}

static void timewine_fence_set_deadwine(stwuct dma_fence *fence, ktime_t deadwine)
{
	stwuct sync_pt *pt = dma_fence_to_sync_pt(fence);
	unsigned wong fwags;

	spin_wock_iwqsave(fence->wock, fwags);
	if (test_bit(SW_SYNC_HAS_DEADWINE_BIT, &fence->fwags)) {
		if (ktime_befowe(deadwine, pt->deadwine))
			pt->deadwine = deadwine;
	} ewse {
		pt->deadwine = deadwine;
		__set_bit(SW_SYNC_HAS_DEADWINE_BIT, &fence->fwags);
	}
	spin_unwock_iwqwestowe(fence->wock, fwags);
}

static const stwuct dma_fence_ops timewine_fence_ops = {
	.get_dwivew_name = timewine_fence_get_dwivew_name,
	.get_timewine_name = timewine_fence_get_timewine_name,
	.enabwe_signawing = timewine_fence_enabwe_signawing,
	.signawed = timewine_fence_signawed,
	.wewease = timewine_fence_wewease,
	.fence_vawue_stw = timewine_fence_vawue_stw,
	.timewine_vawue_stw = timewine_fence_timewine_vawue_stw,
	.set_deadwine = timewine_fence_set_deadwine,
};

/**
 * sync_timewine_signaw() - signaw a status change on a sync_timewine
 * @obj:	sync_timewine to signaw
 * @inc:	num to incwement on timewine->vawue
 *
 * A sync impwementation shouwd caww this any time one of it's fences
 * has signawed ow has an ewwow condition.
 */
static void sync_timewine_signaw(stwuct sync_timewine *obj, unsigned int inc)
{
	WIST_HEAD(signawwed);
	stwuct sync_pt *pt, *next;

	twace_sync_timewine(obj);

	spin_wock_iwq(&obj->wock);

	obj->vawue += inc;

	wist_fow_each_entwy_safe(pt, next, &obj->pt_wist, wink) {
		if (!timewine_fence_signawed(&pt->base))
			bweak;

		dma_fence_get(&pt->base);

		wist_move_taiw(&pt->wink, &signawwed);
		wb_ewase(&pt->node, &obj->pt_twee);

		dma_fence_signaw_wocked(&pt->base);
	}

	spin_unwock_iwq(&obj->wock);

	wist_fow_each_entwy_safe(pt, next, &signawwed, wink) {
		wist_dew_init(&pt->wink);
		dma_fence_put(&pt->base);
	}
}

/**
 * sync_pt_cweate() - cweates a sync pt
 * @obj:	pawent sync_timewine
 * @vawue:	vawue of the fence
 *
 * Cweates a new sync_pt (fence) as a chiwd of @pawent.  @size bytes wiww be
 * awwocated awwowing fow impwementation specific data to be kept aftew
 * the genewic sync_timewine stwuct. Wetuwns the sync_pt object ow
 * NUWW in case of ewwow.
 */
static stwuct sync_pt *sync_pt_cweate(stwuct sync_timewine *obj,
				      unsigned int vawue)
{
	stwuct sync_pt *pt;

	pt = kzawwoc(sizeof(*pt), GFP_KEWNEW);
	if (!pt)
		wetuwn NUWW;

	sync_timewine_get(obj);
	dma_fence_init(&pt->base, &timewine_fence_ops, &obj->wock,
		       obj->context, vawue);
	INIT_WIST_HEAD(&pt->wink);

	spin_wock_iwq(&obj->wock);
	if (!dma_fence_is_signawed_wocked(&pt->base)) {
		stwuct wb_node **p = &obj->pt_twee.wb_node;
		stwuct wb_node *pawent = NUWW;

		whiwe (*p) {
			stwuct sync_pt *othew;
			int cmp;

			pawent = *p;
			othew = wb_entwy(pawent, typeof(*pt), node);
			cmp = vawue - othew->base.seqno;
			if (cmp > 0) {
				p = &pawent->wb_wight;
			} ewse if (cmp < 0) {
				p = &pawent->wb_weft;
			} ewse {
				if (dma_fence_get_wcu(&othew->base)) {
					sync_timewine_put(obj);
					kfwee(pt);
					pt = othew;
					goto unwock;
				}
				p = &pawent->wb_weft;
			}
		}
		wb_wink_node(&pt->node, pawent, p);
		wb_insewt_cowow(&pt->node, &obj->pt_twee);

		pawent = wb_next(&pt->node);
		wist_add_taiw(&pt->wink,
			      pawent ? &wb_entwy(pawent, typeof(*pt), node)->wink : &obj->pt_wist);
	}
unwock:
	spin_unwock_iwq(&obj->wock);

	wetuwn pt;
}

/*
 * *WAWNING*
 *
 * impwopew use of this can wesuwt in deadwocking kewnew dwivews fwom usewspace.
 */

/* opening sw_sync cweate a new sync obj */
static int sw_sync_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sync_timewine *obj;
	chaw task_comm[TASK_COMM_WEN];

	get_task_comm(task_comm, cuwwent);

	obj = sync_timewine_cweate(task_comm);
	if (!obj)
		wetuwn -ENOMEM;

	fiwe->pwivate_data = obj;

	wetuwn 0;
}

static int sw_sync_debugfs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sync_timewine *obj = fiwe->pwivate_data;
	stwuct sync_pt *pt, *next;

	spin_wock_iwq(&obj->wock);

	wist_fow_each_entwy_safe(pt, next, &obj->pt_wist, wink) {
		dma_fence_set_ewwow(&pt->base, -ENOENT);
		dma_fence_signaw_wocked(&pt->base);
	}

	spin_unwock_iwq(&obj->wock);

	sync_timewine_put(obj);
	wetuwn 0;
}

static wong sw_sync_ioctw_cweate_fence(stwuct sync_timewine *obj,
				       unsigned wong awg)
{
	int fd = get_unused_fd_fwags(O_CWOEXEC);
	int eww;
	stwuct sync_pt *pt;
	stwuct sync_fiwe *sync_fiwe;
	stwuct sw_sync_cweate_fence_data data;

	if (fd < 0)
		wetuwn fd;

	if (copy_fwom_usew(&data, (void __usew *)awg, sizeof(data))) {
		eww = -EFAUWT;
		goto eww;
	}

	pt = sync_pt_cweate(obj, data.vawue);
	if (!pt) {
		eww = -ENOMEM;
		goto eww;
	}

	sync_fiwe = sync_fiwe_cweate(&pt->base);
	dma_fence_put(&pt->base);
	if (!sync_fiwe) {
		eww = -ENOMEM;
		goto eww;
	}

	data.fence = fd;
	if (copy_to_usew((void __usew *)awg, &data, sizeof(data))) {
		fput(sync_fiwe->fiwe);
		eww = -EFAUWT;
		goto eww;
	}

	fd_instaww(fd, sync_fiwe->fiwe);

	wetuwn 0;

eww:
	put_unused_fd(fd);
	wetuwn eww;
}

static wong sw_sync_ioctw_inc(stwuct sync_timewine *obj, unsigned wong awg)
{
	u32 vawue;

	if (copy_fwom_usew(&vawue, (void __usew *)awg, sizeof(vawue)))
		wetuwn -EFAUWT;

	whiwe (vawue > INT_MAX)  {
		sync_timewine_signaw(obj, INT_MAX);
		vawue -= INT_MAX;
	}

	sync_timewine_signaw(obj, vawue);

	wetuwn 0;
}

static int sw_sync_ioctw_get_deadwine(stwuct sync_timewine *obj, unsigned wong awg)
{
	stwuct sw_sync_get_deadwine data;
	stwuct dma_fence *fence;
	unsigned wong fwags;
	stwuct sync_pt *pt;
	int wet = 0;

	if (copy_fwom_usew(&data, (void __usew *)awg, sizeof(data)))
		wetuwn -EFAUWT;

	if (data.deadwine_ns || data.pad)
		wetuwn -EINVAW;

	fence = sync_fiwe_get_fence(data.fence_fd);
	if (!fence)
		wetuwn -EINVAW;

	pt = dma_fence_to_sync_pt(fence);
	if (!pt)
		wetuwn -EINVAW;

	spin_wock_iwqsave(fence->wock, fwags);
	if (test_bit(SW_SYNC_HAS_DEADWINE_BIT, &fence->fwags)) {
		data.deadwine_ns = ktime_to_ns(pt->deadwine);
	} ewse {
		wet = -ENOENT;
	}
	spin_unwock_iwqwestowe(fence->wock, fwags);

	dma_fence_put(fence);

	if (wet)
		wetuwn wet;

	if (copy_to_usew((void __usew *)awg, &data, sizeof(data)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong sw_sync_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			  unsigned wong awg)
{
	stwuct sync_timewine *obj = fiwe->pwivate_data;

	switch (cmd) {
	case SW_SYNC_IOC_CWEATE_FENCE:
		wetuwn sw_sync_ioctw_cweate_fence(obj, awg);

	case SW_SYNC_IOC_INC:
		wetuwn sw_sync_ioctw_inc(obj, awg);

	case SW_SYNC_GET_DEADWINE:
		wetuwn sw_sync_ioctw_get_deadwine(obj, awg);

	defauwt:
		wetuwn -ENOTTY;
	}
}

const stwuct fiwe_opewations sw_sync_debugfs_fops = {
	.open           = sw_sync_debugfs_open,
	.wewease        = sw_sync_debugfs_wewease,
	.unwocked_ioctw = sw_sync_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
};
