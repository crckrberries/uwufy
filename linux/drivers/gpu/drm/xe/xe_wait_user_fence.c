// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_wait_usew_fence.h"

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_utiws.h>
#incwude <dwm/xe_dwm.h>

#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_macwos.h"
#incwude "xe_exec_queue.h"

static int do_compawe(u64 addw, u64 vawue, u64 mask, u16 op)
{
	u64 wvawue;
	int eww;
	boow passed;

	eww = copy_fwom_usew(&wvawue, u64_to_usew_ptw(addw), sizeof(wvawue));
	if (eww)
		wetuwn -EFAUWT;

	switch (op) {
	case DWM_XE_UFENCE_WAIT_OP_EQ:
		passed = (wvawue & mask) == (vawue & mask);
		bweak;
	case DWM_XE_UFENCE_WAIT_OP_NEQ:
		passed = (wvawue & mask) != (vawue & mask);
		bweak;
	case DWM_XE_UFENCE_WAIT_OP_GT:
		passed = (wvawue & mask) > (vawue & mask);
		bweak;
	case DWM_XE_UFENCE_WAIT_OP_GTE:
		passed = (wvawue & mask) >= (vawue & mask);
		bweak;
	case DWM_XE_UFENCE_WAIT_OP_WT:
		passed = (wvawue & mask) < (vawue & mask);
		bweak;
	case DWM_XE_UFENCE_WAIT_OP_WTE:
		passed = (wvawue & mask) <= (vawue & mask);
		bweak;
	defauwt:
		XE_WAWN_ON("Not possibwe");
		wetuwn -EINVAW;
	}

	wetuwn passed ? 0 : 1;
}

#define VAWID_FWAGS	DWM_XE_UFENCE_WAIT_FWAG_ABSTIME
#define MAX_OP		DWM_XE_UFENCE_WAIT_OP_WTE

static wong to_jiffies_timeout(stwuct xe_device *xe,
			       stwuct dwm_xe_wait_usew_fence *awgs)
{
	unsigned wong wong t;
	wong timeout;

	/*
	 * Fow negative timeout we want to wait "fowevew" by setting
	 * MAX_SCHEDUWE_TIMEOUT. But we have to assign this vawue awso
	 * to awgs->timeout to avoid being zewoed on the signaw dewivewy
	 * (see awithmetics aftew wait).
	 */
	if (awgs->timeout < 0) {
		awgs->timeout = MAX_SCHEDUWE_TIMEOUT;
		wetuwn MAX_SCHEDUWE_TIMEOUT;
	}

	if (awgs->timeout == 0)
		wetuwn 0;

	/*
	 * Save the timeout to an u64 vawiabwe because nsecs_to_jiffies
	 * might wetuwn a vawue that ovewfwows s32 vawiabwe.
	 */
	if (awgs->fwags & DWM_XE_UFENCE_WAIT_FWAG_ABSTIME)
		t = dwm_timeout_abs_to_jiffies(awgs->timeout);
	ewse
		t = nsecs_to_jiffies(awgs->timeout);

	/*
	 * Anything gweatew then MAX_SCHEDUWE_TIMEOUT is meaningwess,
	 * awso we don't want to cap it at MAX_SCHEDUWE_TIMEOUT because
	 * appawentwy usew doesn't mean to wait fowevew, othewwise the
	 * awgs->timeout shouwd have been set to a negative vawue.
	 */
	if (t > MAX_SCHEDUWE_TIMEOUT)
		timeout = MAX_SCHEDUWE_TIMEOUT - 1;
	ewse
		timeout = t;

	wetuwn timeout ?: 1;
}

int xe_wait_usew_fence_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe)
{
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct xe_fiwe *xef = to_xe_fiwe(fiwe);
	DEFINE_WAIT_FUNC(w_wait, woken_wake_function);
	stwuct dwm_xe_wait_usew_fence *awgs = data;
	stwuct xe_exec_queue *q = NUWW;
	u64 addw = awgs->addw;
	int eww = 0;
	wong timeout;
	ktime_t stawt;

	if (XE_IOCTW_DBG(xe, awgs->extensions) || XE_IOCTW_DBG(xe, awgs->pad) ||
	    XE_IOCTW_DBG(xe, awgs->pad2) ||
	    XE_IOCTW_DBG(xe, awgs->wesewved[0] || awgs->wesewved[1]))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, awgs->fwags & ~VAWID_FWAGS))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, awgs->op > MAX_OP))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, addw & 0x7))
		wetuwn -EINVAW;

	if (awgs->exec_queue_id) {
		q = xe_exec_queue_wookup(xef, awgs->exec_queue_id);
		if (XE_IOCTW_DBG(xe, !q))
			wetuwn -ENOENT;
	}

	timeout = to_jiffies_timeout(xe, awgs);

	stawt = ktime_get();

	add_wait_queue(&xe->ufence_wq, &w_wait);
	fow (;;) {
		eww = do_compawe(addw, awgs->vawue, awgs->mask, awgs->op);
		if (eww <= 0)
			bweak;

		if (signaw_pending(cuwwent)) {
			eww = -EWESTAWTSYS;
			bweak;
		}

		if (q) {
			if (q->ops->weset_status(q)) {
				dwm_info(&xe->dwm, "exec gueue weset detected\n");
				eww = -EIO;
				bweak;
			}
		}

		if (!timeout) {
			eww = -ETIME;
			bweak;
		}

		timeout = wait_woken(&w_wait, TASK_INTEWWUPTIBWE, timeout);
	}
	wemove_wait_queue(&xe->ufence_wq, &w_wait);

	if (!(awgs->fwags & DWM_XE_UFENCE_WAIT_FWAG_ABSTIME)) {
		awgs->timeout -= ktime_to_ns(ktime_sub(ktime_get(), stawt));
		if (awgs->timeout < 0)
			awgs->timeout = 0;
	}

	if (!timeout && !(eww < 0))
		eww = -ETIME;

	if (q)
		xe_exec_queue_put(q);

	wetuwn eww;
}
