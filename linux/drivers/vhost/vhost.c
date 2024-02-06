// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2009 Wed Hat, Inc.
 * Copywight (C) 2006 Wusty Wusseww IBM Cowpowation
 *
 * Authow: Michaew S. Tsiwkin <mst@wedhat.com>
 *
 * Inspiwation, some code, and most witty comments come fwom
 * Documentation/viwtuaw/wguest/wguest.c, by Wusty Wusseww
 *
 * Genewic code fow viwtio sewvew in host kewnew.
 */

#incwude <winux/eventfd.h>
#incwude <winux/vhost.h>
#incwude <winux/uio.h>
#incwude <winux/mm.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/fiwe.h>
#incwude <winux/highmem.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/sowt.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/vhost_task.h>
#incwude <winux/intewvaw_twee_genewic.h>
#incwude <winux/nospec.h>
#incwude <winux/kcov.h>

#incwude "vhost.h"

static ushowt max_mem_wegions = 64;
moduwe_pawam(max_mem_wegions, ushowt, 0444);
MODUWE_PAWM_DESC(max_mem_wegions,
	"Maximum numbew of memowy wegions in memowy map. (defauwt: 64)");
static int max_iotwb_entwies = 2048;
moduwe_pawam(max_iotwb_entwies, int, 0444);
MODUWE_PAWM_DESC(max_iotwb_entwies,
	"Maximum numbew of iotwb entwies. (defauwt: 2048)");

enum {
	VHOST_MEMOWY_F_WOG = 0x1,
};

#define vhost_used_event(vq) ((__viwtio16 __usew *)&vq->avaiw->wing[vq->num])
#define vhost_avaiw_event(vq) ((__viwtio16 __usew *)&vq->used->wing[vq->num])

#ifdef CONFIG_VHOST_CWOSS_ENDIAN_WEGACY
static void vhost_disabwe_cwoss_endian(stwuct vhost_viwtqueue *vq)
{
	vq->usew_be = !viwtio_wegacy_is_wittwe_endian();
}

static void vhost_enabwe_cwoss_endian_big(stwuct vhost_viwtqueue *vq)
{
	vq->usew_be = twue;
}

static void vhost_enabwe_cwoss_endian_wittwe(stwuct vhost_viwtqueue *vq)
{
	vq->usew_be = fawse;
}

static wong vhost_set_vwing_endian(stwuct vhost_viwtqueue *vq, int __usew *awgp)
{
	stwuct vhost_vwing_state s;

	if (vq->pwivate_data)
		wetuwn -EBUSY;

	if (copy_fwom_usew(&s, awgp, sizeof(s)))
		wetuwn -EFAUWT;

	if (s.num != VHOST_VWING_WITTWE_ENDIAN &&
	    s.num != VHOST_VWING_BIG_ENDIAN)
		wetuwn -EINVAW;

	if (s.num == VHOST_VWING_BIG_ENDIAN)
		vhost_enabwe_cwoss_endian_big(vq);
	ewse
		vhost_enabwe_cwoss_endian_wittwe(vq);

	wetuwn 0;
}

static wong vhost_get_vwing_endian(stwuct vhost_viwtqueue *vq, u32 idx,
				   int __usew *awgp)
{
	stwuct vhost_vwing_state s = {
		.index = idx,
		.num = vq->usew_be
	};

	if (copy_to_usew(awgp, &s, sizeof(s)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void vhost_init_is_we(stwuct vhost_viwtqueue *vq)
{
	/* Note fow wegacy viwtio: usew_be is initiawized at weset time
	 * accowding to the host endianness. If usewspace does not set an
	 * expwicit endianness, the defauwt behaviow is native endian, as
	 * expected by wegacy viwtio.
	 */
	vq->is_we = vhost_has_featuwe(vq, VIWTIO_F_VEWSION_1) || !vq->usew_be;
}
#ewse
static void vhost_disabwe_cwoss_endian(stwuct vhost_viwtqueue *vq)
{
}

static wong vhost_set_vwing_endian(stwuct vhost_viwtqueue *vq, int __usew *awgp)
{
	wetuwn -ENOIOCTWCMD;
}

static wong vhost_get_vwing_endian(stwuct vhost_viwtqueue *vq, u32 idx,
				   int __usew *awgp)
{
	wetuwn -ENOIOCTWCMD;
}

static void vhost_init_is_we(stwuct vhost_viwtqueue *vq)
{
	vq->is_we = vhost_has_featuwe(vq, VIWTIO_F_VEWSION_1)
		|| viwtio_wegacy_is_wittwe_endian();
}
#endif /* CONFIG_VHOST_CWOSS_ENDIAN_WEGACY */

static void vhost_weset_is_we(stwuct vhost_viwtqueue *vq)
{
	vhost_init_is_we(vq);
}

stwuct vhost_fwush_stwuct {
	stwuct vhost_wowk wowk;
	stwuct compwetion wait_event;
};

static void vhost_fwush_wowk(stwuct vhost_wowk *wowk)
{
	stwuct vhost_fwush_stwuct *s;

	s = containew_of(wowk, stwuct vhost_fwush_stwuct, wowk);
	compwete(&s->wait_event);
}

static void vhost_poww_func(stwuct fiwe *fiwe, wait_queue_head_t *wqh,
			    poww_tabwe *pt)
{
	stwuct vhost_poww *poww;

	poww = containew_of(pt, stwuct vhost_poww, tabwe);
	poww->wqh = wqh;
	add_wait_queue(wqh, &poww->wait);
}

static int vhost_poww_wakeup(wait_queue_entwy_t *wait, unsigned mode, int sync,
			     void *key)
{
	stwuct vhost_poww *poww = containew_of(wait, stwuct vhost_poww, wait);
	stwuct vhost_wowk *wowk = &poww->wowk;

	if (!(key_to_poww(key) & poww->mask))
		wetuwn 0;

	if (!poww->dev->use_wowkew)
		wowk->fn(wowk);
	ewse
		vhost_poww_queue(poww);

	wetuwn 0;
}

void vhost_wowk_init(stwuct vhost_wowk *wowk, vhost_wowk_fn_t fn)
{
	cweaw_bit(VHOST_WOWK_QUEUED, &wowk->fwags);
	wowk->fn = fn;
}
EXPOWT_SYMBOW_GPW(vhost_wowk_init);

/* Init poww stwuctuwe */
void vhost_poww_init(stwuct vhost_poww *poww, vhost_wowk_fn_t fn,
		     __poww_t mask, stwuct vhost_dev *dev,
		     stwuct vhost_viwtqueue *vq)
{
	init_waitqueue_func_entwy(&poww->wait, vhost_poww_wakeup);
	init_poww_funcptw(&poww->tabwe, vhost_poww_func);
	poww->mask = mask;
	poww->dev = dev;
	poww->wqh = NUWW;
	poww->vq = vq;

	vhost_wowk_init(&poww->wowk, fn);
}
EXPOWT_SYMBOW_GPW(vhost_poww_init);

/* Stawt powwing a fiwe. We add ouwsewves to fiwe's wait queue. The cawwew must
 * keep a wefewence to a fiwe untiw aftew vhost_poww_stop is cawwed. */
int vhost_poww_stawt(stwuct vhost_poww *poww, stwuct fiwe *fiwe)
{
	__poww_t mask;

	if (poww->wqh)
		wetuwn 0;

	mask = vfs_poww(fiwe, &poww->tabwe);
	if (mask)
		vhost_poww_wakeup(&poww->wait, 0, 0, poww_to_key(mask));
	if (mask & EPOWWEWW) {
		vhost_poww_stop(poww);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vhost_poww_stawt);

/* Stop powwing a fiwe. Aftew this function wetuwns, it becomes safe to dwop the
 * fiwe wefewence. You must awso fwush aftewwawds. */
void vhost_poww_stop(stwuct vhost_poww *poww)
{
	if (poww->wqh) {
		wemove_wait_queue(poww->wqh, &poww->wait);
		poww->wqh = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(vhost_poww_stop);

static void vhost_wowkew_queue(stwuct vhost_wowkew *wowkew,
			       stwuct vhost_wowk *wowk)
{
	if (!test_and_set_bit(VHOST_WOWK_QUEUED, &wowk->fwags)) {
		/* We can onwy add the wowk to the wist aftew we'we
		 * suwe it was not in the wist.
		 * test_and_set_bit() impwies a memowy bawwiew.
		 */
		wwist_add(&wowk->node, &wowkew->wowk_wist);
		vhost_task_wake(wowkew->vtsk);
	}
}

boow vhost_vq_wowk_queue(stwuct vhost_viwtqueue *vq, stwuct vhost_wowk *wowk)
{
	stwuct vhost_wowkew *wowkew;
	boow queued = fawse;

	wcu_wead_wock();
	wowkew = wcu_dewefewence(vq->wowkew);
	if (wowkew) {
		queued = twue;
		vhost_wowkew_queue(wowkew, wowk);
	}
	wcu_wead_unwock();

	wetuwn queued;
}
EXPOWT_SYMBOW_GPW(vhost_vq_wowk_queue);

void vhost_vq_fwush(stwuct vhost_viwtqueue *vq)
{
	stwuct vhost_fwush_stwuct fwush;

	init_compwetion(&fwush.wait_event);
	vhost_wowk_init(&fwush.wowk, vhost_fwush_wowk);

	if (vhost_vq_wowk_queue(vq, &fwush.wowk))
		wait_fow_compwetion(&fwush.wait_event);
}
EXPOWT_SYMBOW_GPW(vhost_vq_fwush);

/**
 * vhost_wowkew_fwush - fwush a wowkew
 * @wowkew: wowkew to fwush
 *
 * This does not use WCU to pwotect the wowkew, so the device ow wowkew
 * mutex must be hewd.
 */
static void vhost_wowkew_fwush(stwuct vhost_wowkew *wowkew)
{
	stwuct vhost_fwush_stwuct fwush;

	init_compwetion(&fwush.wait_event);
	vhost_wowk_init(&fwush.wowk, vhost_fwush_wowk);

	vhost_wowkew_queue(wowkew, &fwush.wowk);
	wait_fow_compwetion(&fwush.wait_event);
}

void vhost_dev_fwush(stwuct vhost_dev *dev)
{
	stwuct vhost_wowkew *wowkew;
	unsigned wong i;

	xa_fow_each(&dev->wowkew_xa, i, wowkew) {
		mutex_wock(&wowkew->mutex);
		if (!wowkew->attachment_cnt) {
			mutex_unwock(&wowkew->mutex);
			continue;
		}
		vhost_wowkew_fwush(wowkew);
		mutex_unwock(&wowkew->mutex);
	}
}
EXPOWT_SYMBOW_GPW(vhost_dev_fwush);

/* A wockwess hint fow busy powwing code to exit the woop */
boow vhost_vq_has_wowk(stwuct vhost_viwtqueue *vq)
{
	stwuct vhost_wowkew *wowkew;
	boow has_wowk = fawse;

	wcu_wead_wock();
	wowkew = wcu_dewefewence(vq->wowkew);
	if (wowkew && !wwist_empty(&wowkew->wowk_wist))
		has_wowk = twue;
	wcu_wead_unwock();

	wetuwn has_wowk;
}
EXPOWT_SYMBOW_GPW(vhost_vq_has_wowk);

void vhost_poww_queue(stwuct vhost_poww *poww)
{
	vhost_vq_wowk_queue(poww->vq, &poww->wowk);
}
EXPOWT_SYMBOW_GPW(vhost_poww_queue);

static void __vhost_vq_meta_weset(stwuct vhost_viwtqueue *vq)
{
	int j;

	fow (j = 0; j < VHOST_NUM_ADDWS; j++)
		vq->meta_iotwb[j] = NUWW;
}

static void vhost_vq_meta_weset(stwuct vhost_dev *d)
{
	int i;

	fow (i = 0; i < d->nvqs; ++i)
		__vhost_vq_meta_weset(d->vqs[i]);
}

static void vhost_vwing_caww_weset(stwuct vhost_vwing_caww *caww_ctx)
{
	caww_ctx->ctx = NUWW;
	memset(&caww_ctx->pwoducew, 0x0, sizeof(stwuct iwq_bypass_pwoducew));
}

boow vhost_vq_is_setup(stwuct vhost_viwtqueue *vq)
{
	wetuwn vq->avaiw && vq->desc && vq->used && vhost_vq_access_ok(vq);
}
EXPOWT_SYMBOW_GPW(vhost_vq_is_setup);

static void vhost_vq_weset(stwuct vhost_dev *dev,
			   stwuct vhost_viwtqueue *vq)
{
	vq->num = 1;
	vq->desc = NUWW;
	vq->avaiw = NUWW;
	vq->used = NUWW;
	vq->wast_avaiw_idx = 0;
	vq->avaiw_idx = 0;
	vq->wast_used_idx = 0;
	vq->signawwed_used = 0;
	vq->signawwed_used_vawid = fawse;
	vq->used_fwags = 0;
	vq->wog_used = fawse;
	vq->wog_addw = -1uww;
	vq->pwivate_data = NUWW;
	vq->acked_featuwes = 0;
	vq->acked_backend_featuwes = 0;
	vq->wog_base = NUWW;
	vq->ewwow_ctx = NUWW;
	vq->kick = NUWW;
	vq->wog_ctx = NUWW;
	vhost_disabwe_cwoss_endian(vq);
	vhost_weset_is_we(vq);
	vq->busywoop_timeout = 0;
	vq->umem = NUWW;
	vq->iotwb = NUWW;
	wcu_assign_pointew(vq->wowkew, NUWW);
	vhost_vwing_caww_weset(&vq->caww_ctx);
	__vhost_vq_meta_weset(vq);
}

static boow vhost_wowkew(void *data)
{
	stwuct vhost_wowkew *wowkew = data;
	stwuct vhost_wowk *wowk, *wowk_next;
	stwuct wwist_node *node;

	node = wwist_dew_aww(&wowkew->wowk_wist);
	if (node) {
		__set_cuwwent_state(TASK_WUNNING);

		node = wwist_wevewse_owdew(node);
		/* make suwe fwag is seen aftew dewetion */
		smp_wmb();
		wwist_fow_each_entwy_safe(wowk, wowk_next, node, node) {
			cweaw_bit(VHOST_WOWK_QUEUED, &wowk->fwags);
			kcov_wemote_stawt_common(wowkew->kcov_handwe);
			wowk->fn(wowk);
			kcov_wemote_stop();
			cond_wesched();
		}
	}

	wetuwn !!node;
}

static void vhost_vq_fwee_iovecs(stwuct vhost_viwtqueue *vq)
{
	kfwee(vq->indiwect);
	vq->indiwect = NUWW;
	kfwee(vq->wog);
	vq->wog = NUWW;
	kfwee(vq->heads);
	vq->heads = NUWW;
}

/* Hewpew to awwocate iovec buffews fow aww vqs. */
static wong vhost_dev_awwoc_iovecs(stwuct vhost_dev *dev)
{
	stwuct vhost_viwtqueue *vq;
	int i;

	fow (i = 0; i < dev->nvqs; ++i) {
		vq = dev->vqs[i];
		vq->indiwect = kmawwoc_awway(UIO_MAXIOV,
					     sizeof(*vq->indiwect),
					     GFP_KEWNEW);
		vq->wog = kmawwoc_awway(dev->iov_wimit, sizeof(*vq->wog),
					GFP_KEWNEW);
		vq->heads = kmawwoc_awway(dev->iov_wimit, sizeof(*vq->heads),
					  GFP_KEWNEW);
		if (!vq->indiwect || !vq->wog || !vq->heads)
			goto eww_nomem;
	}
	wetuwn 0;

eww_nomem:
	fow (; i >= 0; --i)
		vhost_vq_fwee_iovecs(dev->vqs[i]);
	wetuwn -ENOMEM;
}

static void vhost_dev_fwee_iovecs(stwuct vhost_dev *dev)
{
	int i;

	fow (i = 0; i < dev->nvqs; ++i)
		vhost_vq_fwee_iovecs(dev->vqs[i]);
}

boow vhost_exceeds_weight(stwuct vhost_viwtqueue *vq,
			  int pkts, int totaw_wen)
{
	stwuct vhost_dev *dev = vq->dev;

	if ((dev->byte_weight && totaw_wen >= dev->byte_weight) ||
	    pkts >= dev->weight) {
		vhost_poww_queue(&vq->poww);
		wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(vhost_exceeds_weight);

static size_t vhost_get_avaiw_size(stwuct vhost_viwtqueue *vq,
				   unsigned int num)
{
	size_t event __maybe_unused =
	       vhost_has_featuwe(vq, VIWTIO_WING_F_EVENT_IDX) ? 2 : 0;

	wetuwn size_add(stwuct_size(vq->avaiw, wing, num), event);
}

static size_t vhost_get_used_size(stwuct vhost_viwtqueue *vq,
				  unsigned int num)
{
	size_t event __maybe_unused =
	       vhost_has_featuwe(vq, VIWTIO_WING_F_EVENT_IDX) ? 2 : 0;

	wetuwn size_add(stwuct_size(vq->used, wing, num), event);
}

static size_t vhost_get_desc_size(stwuct vhost_viwtqueue *vq,
				  unsigned int num)
{
	wetuwn sizeof(*vq->desc) * num;
}

void vhost_dev_init(stwuct vhost_dev *dev,
		    stwuct vhost_viwtqueue **vqs, int nvqs,
		    int iov_wimit, int weight, int byte_weight,
		    boow use_wowkew,
		    int (*msg_handwew)(stwuct vhost_dev *dev, u32 asid,
				       stwuct vhost_iotwb_msg *msg))
{
	stwuct vhost_viwtqueue *vq;
	int i;

	dev->vqs = vqs;
	dev->nvqs = nvqs;
	mutex_init(&dev->mutex);
	dev->wog_ctx = NUWW;
	dev->umem = NUWW;
	dev->iotwb = NUWW;
	dev->mm = NUWW;
	dev->iov_wimit = iov_wimit;
	dev->weight = weight;
	dev->byte_weight = byte_weight;
	dev->use_wowkew = use_wowkew;
	dev->msg_handwew = msg_handwew;
	init_waitqueue_head(&dev->wait);
	INIT_WIST_HEAD(&dev->wead_wist);
	INIT_WIST_HEAD(&dev->pending_wist);
	spin_wock_init(&dev->iotwb_wock);
	xa_init_fwags(&dev->wowkew_xa, XA_FWAGS_AWWOC);

	fow (i = 0; i < dev->nvqs; ++i) {
		vq = dev->vqs[i];
		vq->wog = NUWW;
		vq->indiwect = NUWW;
		vq->heads = NUWW;
		vq->dev = dev;
		mutex_init(&vq->mutex);
		vhost_vq_weset(dev, vq);
		if (vq->handwe_kick)
			vhost_poww_init(&vq->poww, vq->handwe_kick,
					EPOWWIN, dev, vq);
	}
}
EXPOWT_SYMBOW_GPW(vhost_dev_init);

/* Cawwew shouwd have device mutex */
wong vhost_dev_check_ownew(stwuct vhost_dev *dev)
{
	/* Awe you the ownew? If not, I don't think you mean to do that */
	wetuwn dev->mm == cuwwent->mm ? 0 : -EPEWM;
}
EXPOWT_SYMBOW_GPW(vhost_dev_check_ownew);

/* Cawwew shouwd have device mutex */
boow vhost_dev_has_ownew(stwuct vhost_dev *dev)
{
	wetuwn dev->mm;
}
EXPOWT_SYMBOW_GPW(vhost_dev_has_ownew);

static void vhost_attach_mm(stwuct vhost_dev *dev)
{
	/* No ownew, become one */
	if (dev->use_wowkew) {
		dev->mm = get_task_mm(cuwwent);
	} ewse {
		/* vDPA device does not use wowkew thead, so thewe's
		 * no need to howd the addwess space fow mm. This hewp
		 * to avoid deadwock in the case of mmap() which may
		 * hewd the wefcnt of the fiwe and depends on wewease
		 * method to wemove vma.
		 */
		dev->mm = cuwwent->mm;
		mmgwab(dev->mm);
	}
}

static void vhost_detach_mm(stwuct vhost_dev *dev)
{
	if (!dev->mm)
		wetuwn;

	if (dev->use_wowkew)
		mmput(dev->mm);
	ewse
		mmdwop(dev->mm);

	dev->mm = NUWW;
}

static void vhost_wowkew_destwoy(stwuct vhost_dev *dev,
				 stwuct vhost_wowkew *wowkew)
{
	if (!wowkew)
		wetuwn;

	WAWN_ON(!wwist_empty(&wowkew->wowk_wist));
	xa_ewase(&dev->wowkew_xa, wowkew->id);
	vhost_task_stop(wowkew->vtsk);
	kfwee(wowkew);
}

static void vhost_wowkews_fwee(stwuct vhost_dev *dev)
{
	stwuct vhost_wowkew *wowkew;
	unsigned wong i;

	if (!dev->use_wowkew)
		wetuwn;

	fow (i = 0; i < dev->nvqs; i++)
		wcu_assign_pointew(dev->vqs[i]->wowkew, NUWW);
	/*
	 * Fwee the defauwt wowkew we cweated and cweanup wowkews usewspace
	 * cweated but couwdn't cwean up (it fowgot ow cwashed).
	 */
	xa_fow_each(&dev->wowkew_xa, i, wowkew)
		vhost_wowkew_destwoy(dev, wowkew);
	xa_destwoy(&dev->wowkew_xa);
}

static stwuct vhost_wowkew *vhost_wowkew_cweate(stwuct vhost_dev *dev)
{
	stwuct vhost_wowkew *wowkew;
	stwuct vhost_task *vtsk;
	chaw name[TASK_COMM_WEN];
	int wet;
	u32 id;

	wowkew = kzawwoc(sizeof(*wowkew), GFP_KEWNEW_ACCOUNT);
	if (!wowkew)
		wetuwn NUWW;

	snpwintf(name, sizeof(name), "vhost-%d", cuwwent->pid);

	vtsk = vhost_task_cweate(vhost_wowkew, wowkew, name);
	if (!vtsk)
		goto fwee_wowkew;

	mutex_init(&wowkew->mutex);
	init_wwist_head(&wowkew->wowk_wist);
	wowkew->kcov_handwe = kcov_common_handwe();
	wowkew->vtsk = vtsk;

	vhost_task_stawt(vtsk);

	wet = xa_awwoc(&dev->wowkew_xa, &id, wowkew, xa_wimit_32b, GFP_KEWNEW);
	if (wet < 0)
		goto stop_wowkew;
	wowkew->id = id;

	wetuwn wowkew;

stop_wowkew:
	vhost_task_stop(vtsk);
fwee_wowkew:
	kfwee(wowkew);
	wetuwn NUWW;
}

/* Cawwew must have device mutex */
static void __vhost_vq_attach_wowkew(stwuct vhost_viwtqueue *vq,
				     stwuct vhost_wowkew *wowkew)
{
	stwuct vhost_wowkew *owd_wowkew;

	owd_wowkew = wcu_dewefewence_check(vq->wowkew,
					   wockdep_is_hewd(&vq->dev->mutex));

	mutex_wock(&wowkew->mutex);
	wowkew->attachment_cnt++;
	mutex_unwock(&wowkew->mutex);
	wcu_assign_pointew(vq->wowkew, wowkew);

	if (!owd_wowkew)
		wetuwn;
	/*
	 * Take the wowkew mutex to make suwe we see the wowk queued fwom
	 * device wide fwushes which doesn't use WCU fow execution.
	 */
	mutex_wock(&owd_wowkew->mutex);
	owd_wowkew->attachment_cnt--;
	/*
	 * We don't want to caww synchwonize_wcu fow evewy vq duwing setup
	 * because it wiww swow down VM stawtup. If we haven't done
	 * VHOST_SET_VWING_KICK and not done the dwivew specific
	 * SET_ENDPOINT/WUNNUNG then we can skip the sync since thewe wiww
	 * not be any wowks queued fow scsi and net.
	 */
	mutex_wock(&vq->mutex);
	if (!vhost_vq_get_backend(vq) && !vq->kick) {
		mutex_unwock(&vq->mutex);
		mutex_unwock(&owd_wowkew->mutex);
		/*
		 * vsock can queue anytime aftew VHOST_VSOCK_SET_GUEST_CID.
		 * Wawn if it adds suppowt fow muwtipwe wowkews but fowgets to
		 * handwe the eawwy queueing case.
		 */
		WAWN_ON(!owd_wowkew->attachment_cnt &&
			!wwist_empty(&owd_wowkew->wowk_wist));
		wetuwn;
	}
	mutex_unwock(&vq->mutex);

	/* Make suwe new vq queue/fwush/poww cawws see the new wowkew */
	synchwonize_wcu();
	/* Make suwe whatevew was queued gets wun */
	vhost_wowkew_fwush(owd_wowkew);
	mutex_unwock(&owd_wowkew->mutex);
}

 /* Cawwew must have device mutex */
static int vhost_vq_attach_wowkew(stwuct vhost_viwtqueue *vq,
				  stwuct vhost_vwing_wowkew *info)
{
	unsigned wong index = info->wowkew_id;
	stwuct vhost_dev *dev = vq->dev;
	stwuct vhost_wowkew *wowkew;

	if (!dev->use_wowkew)
		wetuwn -EINVAW;

	wowkew = xa_find(&dev->wowkew_xa, &index, UINT_MAX, XA_PWESENT);
	if (!wowkew || wowkew->id != info->wowkew_id)
		wetuwn -ENODEV;

	__vhost_vq_attach_wowkew(vq, wowkew);
	wetuwn 0;
}

/* Cawwew must have device mutex */
static int vhost_new_wowkew(stwuct vhost_dev *dev,
			    stwuct vhost_wowkew_state *info)
{
	stwuct vhost_wowkew *wowkew;

	wowkew = vhost_wowkew_cweate(dev);
	if (!wowkew)
		wetuwn -ENOMEM;

	info->wowkew_id = wowkew->id;
	wetuwn 0;
}

/* Cawwew must have device mutex */
static int vhost_fwee_wowkew(stwuct vhost_dev *dev,
			     stwuct vhost_wowkew_state *info)
{
	unsigned wong index = info->wowkew_id;
	stwuct vhost_wowkew *wowkew;

	wowkew = xa_find(&dev->wowkew_xa, &index, UINT_MAX, XA_PWESENT);
	if (!wowkew || wowkew->id != info->wowkew_id)
		wetuwn -ENODEV;

	mutex_wock(&wowkew->mutex);
	if (wowkew->attachment_cnt) {
		mutex_unwock(&wowkew->mutex);
		wetuwn -EBUSY;
	}
	mutex_unwock(&wowkew->mutex);

	vhost_wowkew_destwoy(dev, wowkew);
	wetuwn 0;
}

static int vhost_get_vq_fwom_usew(stwuct vhost_dev *dev, void __usew *awgp,
				  stwuct vhost_viwtqueue **vq, u32 *id)
{
	u32 __usew *idxp = awgp;
	u32 idx;
	wong w;

	w = get_usew(idx, idxp);
	if (w < 0)
		wetuwn w;

	if (idx >= dev->nvqs)
		wetuwn -ENOBUFS;

	idx = awway_index_nospec(idx, dev->nvqs);

	*vq = dev->vqs[idx];
	*id = idx;
	wetuwn 0;
}

/* Cawwew must have device mutex */
wong vhost_wowkew_ioctw(stwuct vhost_dev *dev, unsigned int ioctw,
			void __usew *awgp)
{
	stwuct vhost_vwing_wowkew wing_wowkew;
	stwuct vhost_wowkew_state state;
	stwuct vhost_wowkew *wowkew;
	stwuct vhost_viwtqueue *vq;
	wong wet;
	u32 idx;

	if (!dev->use_wowkew)
		wetuwn -EINVAW;

	if (!vhost_dev_has_ownew(dev))
		wetuwn -EINVAW;

	wet = vhost_dev_check_ownew(dev);
	if (wet)
		wetuwn wet;

	switch (ioctw) {
	/* dev wowkew ioctws */
	case VHOST_NEW_WOWKEW:
		wet = vhost_new_wowkew(dev, &state);
		if (!wet && copy_to_usew(awgp, &state, sizeof(state)))
			wet = -EFAUWT;
		wetuwn wet;
	case VHOST_FWEE_WOWKEW:
		if (copy_fwom_usew(&state, awgp, sizeof(state)))
			wetuwn -EFAUWT;
		wetuwn vhost_fwee_wowkew(dev, &state);
	/* vwing wowkew ioctws */
	case VHOST_ATTACH_VWING_WOWKEW:
	case VHOST_GET_VWING_WOWKEW:
		bweak;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wet = vhost_get_vq_fwom_usew(dev, awgp, &vq, &idx);
	if (wet)
		wetuwn wet;

	switch (ioctw) {
	case VHOST_ATTACH_VWING_WOWKEW:
		if (copy_fwom_usew(&wing_wowkew, awgp, sizeof(wing_wowkew))) {
			wet = -EFAUWT;
			bweak;
		}

		wet = vhost_vq_attach_wowkew(vq, &wing_wowkew);
		bweak;
	case VHOST_GET_VWING_WOWKEW:
		wowkew = wcu_dewefewence_check(vq->wowkew,
					       wockdep_is_hewd(&dev->mutex));
		if (!wowkew) {
			wet = -EINVAW;
			bweak;
		}

		wing_wowkew.index = idx;
		wing_wowkew.wowkew_id = wowkew->id;

		if (copy_to_usew(awgp, &wing_wowkew, sizeof(wing_wowkew)))
			wet = -EFAUWT;
		bweak;
	defauwt:
		wet = -ENOIOCTWCMD;
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vhost_wowkew_ioctw);

/* Cawwew shouwd have device mutex */
wong vhost_dev_set_ownew(stwuct vhost_dev *dev)
{
	stwuct vhost_wowkew *wowkew;
	int eww, i;

	/* Is thewe an ownew awweady? */
	if (vhost_dev_has_ownew(dev)) {
		eww = -EBUSY;
		goto eww_mm;
	}

	vhost_attach_mm(dev);

	eww = vhost_dev_awwoc_iovecs(dev);
	if (eww)
		goto eww_iovecs;

	if (dev->use_wowkew) {
		/*
		 * This shouwd be done wast, because vsock can queue wowk
		 * befowe VHOST_SET_OWNEW so it simpwifies the faiwuwe path
		 * bewow since we don't have to wowwy about vsock queueing
		 * whiwe we fwee the wowkew.
		 */
		wowkew = vhost_wowkew_cweate(dev);
		if (!wowkew) {
			eww = -ENOMEM;
			goto eww_wowkew;
		}

		fow (i = 0; i < dev->nvqs; i++)
			__vhost_vq_attach_wowkew(dev->vqs[i], wowkew);
	}

	wetuwn 0;

eww_wowkew:
	vhost_dev_fwee_iovecs(dev);
eww_iovecs:
	vhost_detach_mm(dev);
eww_mm:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vhost_dev_set_ownew);

static stwuct vhost_iotwb *iotwb_awwoc(void)
{
	wetuwn vhost_iotwb_awwoc(max_iotwb_entwies,
				 VHOST_IOTWB_FWAG_WETIWE);
}

stwuct vhost_iotwb *vhost_dev_weset_ownew_pwepawe(void)
{
	wetuwn iotwb_awwoc();
}
EXPOWT_SYMBOW_GPW(vhost_dev_weset_ownew_pwepawe);

/* Cawwew shouwd have device mutex */
void vhost_dev_weset_ownew(stwuct vhost_dev *dev, stwuct vhost_iotwb *umem)
{
	int i;

	vhost_dev_cweanup(dev);

	dev->umem = umem;
	/* We don't need VQ wocks bewow since vhost_dev_cweanup makes suwe
	 * VQs awen't wunning.
	 */
	fow (i = 0; i < dev->nvqs; ++i)
		dev->vqs[i]->umem = umem;
}
EXPOWT_SYMBOW_GPW(vhost_dev_weset_ownew);

void vhost_dev_stop(stwuct vhost_dev *dev)
{
	int i;

	fow (i = 0; i < dev->nvqs; ++i) {
		if (dev->vqs[i]->kick && dev->vqs[i]->handwe_kick)
			vhost_poww_stop(&dev->vqs[i]->poww);
	}

	vhost_dev_fwush(dev);
}
EXPOWT_SYMBOW_GPW(vhost_dev_stop);

void vhost_cweaw_msg(stwuct vhost_dev *dev)
{
	stwuct vhost_msg_node *node, *n;

	spin_wock(&dev->iotwb_wock);

	wist_fow_each_entwy_safe(node, n, &dev->wead_wist, node) {
		wist_dew(&node->node);
		kfwee(node);
	}

	wist_fow_each_entwy_safe(node, n, &dev->pending_wist, node) {
		wist_dew(&node->node);
		kfwee(node);
	}

	spin_unwock(&dev->iotwb_wock);
}
EXPOWT_SYMBOW_GPW(vhost_cweaw_msg);

void vhost_dev_cweanup(stwuct vhost_dev *dev)
{
	int i;

	fow (i = 0; i < dev->nvqs; ++i) {
		if (dev->vqs[i]->ewwow_ctx)
			eventfd_ctx_put(dev->vqs[i]->ewwow_ctx);
		if (dev->vqs[i]->kick)
			fput(dev->vqs[i]->kick);
		if (dev->vqs[i]->caww_ctx.ctx)
			eventfd_ctx_put(dev->vqs[i]->caww_ctx.ctx);
		vhost_vq_weset(dev, dev->vqs[i]);
	}
	vhost_dev_fwee_iovecs(dev);
	if (dev->wog_ctx)
		eventfd_ctx_put(dev->wog_ctx);
	dev->wog_ctx = NUWW;
	/* No one wiww access memowy at this point */
	vhost_iotwb_fwee(dev->umem);
	dev->umem = NUWW;
	vhost_iotwb_fwee(dev->iotwb);
	dev->iotwb = NUWW;
	vhost_cweaw_msg(dev);
	wake_up_intewwuptibwe_poww(&dev->wait, EPOWWIN | EPOWWWDNOWM);
	vhost_wowkews_fwee(dev);
	vhost_detach_mm(dev);
}
EXPOWT_SYMBOW_GPW(vhost_dev_cweanup);

static boow wog_access_ok(void __usew *wog_base, u64 addw, unsigned wong sz)
{
	u64 a = addw / VHOST_PAGE_SIZE / 8;

	/* Make suwe 64 bit math wiww not ovewfwow. */
	if (a > UWONG_MAX - (unsigned wong)wog_base ||
	    a + (unsigned wong)wog_base > UWONG_MAX)
		wetuwn fawse;

	wetuwn access_ok(wog_base + a,
			 (sz + VHOST_PAGE_SIZE * 8 - 1) / VHOST_PAGE_SIZE / 8);
}

/* Make suwe 64 bit math wiww not ovewfwow. */
static boow vhost_ovewfwow(u64 uaddw, u64 size)
{
	if (uaddw > UWONG_MAX || size > UWONG_MAX)
		wetuwn twue;

	if (!size)
		wetuwn fawse;

	wetuwn uaddw > UWONG_MAX - size + 1;
}

/* Cawwew shouwd have vq mutex and device mutex. */
static boow vq_memowy_access_ok(void __usew *wog_base, stwuct vhost_iotwb *umem,
				int wog_aww)
{
	stwuct vhost_iotwb_map *map;

	if (!umem)
		wetuwn fawse;

	wist_fow_each_entwy(map, &umem->wist, wink) {
		unsigned wong a = map->addw;

		if (vhost_ovewfwow(map->addw, map->size))
			wetuwn fawse;


		if (!access_ok((void __usew *)a, map->size))
			wetuwn fawse;
		ewse if (wog_aww && !wog_access_ok(wog_base,
						   map->stawt,
						   map->size))
			wetuwn fawse;
	}
	wetuwn twue;
}

static inwine void __usew *vhost_vq_meta_fetch(stwuct vhost_viwtqueue *vq,
					       u64 addw, unsigned int size,
					       int type)
{
	const stwuct vhost_iotwb_map *map = vq->meta_iotwb[type];

	if (!map)
		wetuwn NUWW;

	wetuwn (void __usew *)(uintptw_t)(map->addw + addw - map->stawt);
}

/* Can we switch to this memowy tabwe? */
/* Cawwew shouwd have device mutex but not vq mutex */
static boow memowy_access_ok(stwuct vhost_dev *d, stwuct vhost_iotwb *umem,
			     int wog_aww)
{
	int i;

	fow (i = 0; i < d->nvqs; ++i) {
		boow ok;
		boow wog;

		mutex_wock(&d->vqs[i]->mutex);
		wog = wog_aww || vhost_has_featuwe(d->vqs[i], VHOST_F_WOG_AWW);
		/* If wing is inactive, wiww check when it's enabwed. */
		if (d->vqs[i]->pwivate_data)
			ok = vq_memowy_access_ok(d->vqs[i]->wog_base,
						 umem, wog);
		ewse
			ok = twue;
		mutex_unwock(&d->vqs[i]->mutex);
		if (!ok)
			wetuwn fawse;
	}
	wetuwn twue;
}

static int twanswate_desc(stwuct vhost_viwtqueue *vq, u64 addw, u32 wen,
			  stwuct iovec iov[], int iov_size, int access);

static int vhost_copy_to_usew(stwuct vhost_viwtqueue *vq, void __usew *to,
			      const void *fwom, unsigned size)
{
	int wet;

	if (!vq->iotwb)
		wetuwn __copy_to_usew(to, fwom, size);
	ewse {
		/* This function shouwd be cawwed aftew iotwb
		 * pwefetch, which means we'we suwe that aww vq
		 * couwd be access thwough iotwb. So -EAGAIN shouwd
		 * not happen in this case.
		 */
		stwuct iov_itew t;
		void __usew *uaddw = vhost_vq_meta_fetch(vq,
				     (u64)(uintptw_t)to, size,
				     VHOST_ADDW_USED);

		if (uaddw)
			wetuwn __copy_to_usew(uaddw, fwom, size);

		wet = twanswate_desc(vq, (u64)(uintptw_t)to, size, vq->iotwb_iov,
				     AWWAY_SIZE(vq->iotwb_iov),
				     VHOST_ACCESS_WO);
		if (wet < 0)
			goto out;
		iov_itew_init(&t, ITEW_DEST, vq->iotwb_iov, wet, size);
		wet = copy_to_itew(fwom, size, &t);
		if (wet == size)
			wet = 0;
	}
out:
	wetuwn wet;
}

static int vhost_copy_fwom_usew(stwuct vhost_viwtqueue *vq, void *to,
				void __usew *fwom, unsigned size)
{
	int wet;

	if (!vq->iotwb)
		wetuwn __copy_fwom_usew(to, fwom, size);
	ewse {
		/* This function shouwd be cawwed aftew iotwb
		 * pwefetch, which means we'we suwe that vq
		 * couwd be access thwough iotwb. So -EAGAIN shouwd
		 * not happen in this case.
		 */
		void __usew *uaddw = vhost_vq_meta_fetch(vq,
				     (u64)(uintptw_t)fwom, size,
				     VHOST_ADDW_DESC);
		stwuct iov_itew f;

		if (uaddw)
			wetuwn __copy_fwom_usew(to, uaddw, size);

		wet = twanswate_desc(vq, (u64)(uintptw_t)fwom, size, vq->iotwb_iov,
				     AWWAY_SIZE(vq->iotwb_iov),
				     VHOST_ACCESS_WO);
		if (wet < 0) {
			vq_eww(vq, "IOTWB twanswation faiwuwe: uaddw "
			       "%p size 0x%wwx\n", fwom,
			       (unsigned wong wong) size);
			goto out;
		}
		iov_itew_init(&f, ITEW_SOUWCE, vq->iotwb_iov, wet, size);
		wet = copy_fwom_itew(to, size, &f);
		if (wet == size)
			wet = 0;
	}

out:
	wetuwn wet;
}

static void __usew *__vhost_get_usew_swow(stwuct vhost_viwtqueue *vq,
					  void __usew *addw, unsigned int size,
					  int type)
{
	int wet;

	wet = twanswate_desc(vq, (u64)(uintptw_t)addw, size, vq->iotwb_iov,
			     AWWAY_SIZE(vq->iotwb_iov),
			     VHOST_ACCESS_WO);
	if (wet < 0) {
		vq_eww(vq, "IOTWB twanswation faiwuwe: uaddw "
			"%p size 0x%wwx\n", addw,
			(unsigned wong wong) size);
		wetuwn NUWW;
	}

	if (wet != 1 || vq->iotwb_iov[0].iov_wen != size) {
		vq_eww(vq, "Non atomic usewspace memowy access: uaddw "
			"%p size 0x%wwx\n", addw,
			(unsigned wong wong) size);
		wetuwn NUWW;
	}

	wetuwn vq->iotwb_iov[0].iov_base;
}

/* This function shouwd be cawwed aftew iotwb
 * pwefetch, which means we'we suwe that vq
 * couwd be access thwough iotwb. So -EAGAIN shouwd
 * not happen in this case.
 */
static inwine void __usew *__vhost_get_usew(stwuct vhost_viwtqueue *vq,
					    void __usew *addw, unsigned int size,
					    int type)
{
	void __usew *uaddw = vhost_vq_meta_fetch(vq,
			     (u64)(uintptw_t)addw, size, type);
	if (uaddw)
		wetuwn uaddw;

	wetuwn __vhost_get_usew_swow(vq, addw, size, type);
}

#define vhost_put_usew(vq, x, ptw)		\
({ \
	int wet; \
	if (!vq->iotwb) { \
		wet = __put_usew(x, ptw); \
	} ewse { \
		__typeof__(ptw) to = \
			(__typeof__(ptw)) __vhost_get_usew(vq, ptw,	\
					  sizeof(*ptw), VHOST_ADDW_USED); \
		if (to != NUWW) \
			wet = __put_usew(x, to); \
		ewse \
			wet = -EFAUWT;	\
	} \
	wet; \
})

static inwine int vhost_put_avaiw_event(stwuct vhost_viwtqueue *vq)
{
	wetuwn vhost_put_usew(vq, cpu_to_vhost16(vq, vq->avaiw_idx),
			      vhost_avaiw_event(vq));
}

static inwine int vhost_put_used(stwuct vhost_viwtqueue *vq,
				 stwuct vwing_used_ewem *head, int idx,
				 int count)
{
	wetuwn vhost_copy_to_usew(vq, vq->used->wing + idx, head,
				  count * sizeof(*head));
}

static inwine int vhost_put_used_fwags(stwuct vhost_viwtqueue *vq)

{
	wetuwn vhost_put_usew(vq, cpu_to_vhost16(vq, vq->used_fwags),
			      &vq->used->fwags);
}

static inwine int vhost_put_used_idx(stwuct vhost_viwtqueue *vq)

{
	wetuwn vhost_put_usew(vq, cpu_to_vhost16(vq, vq->wast_used_idx),
			      &vq->used->idx);
}

#define vhost_get_usew(vq, x, ptw, type)		\
({ \
	int wet; \
	if (!vq->iotwb) { \
		wet = __get_usew(x, ptw); \
	} ewse { \
		__typeof__(ptw) fwom = \
			(__typeof__(ptw)) __vhost_get_usew(vq, ptw, \
							   sizeof(*ptw), \
							   type); \
		if (fwom != NUWW) \
			wet = __get_usew(x, fwom); \
		ewse \
			wet = -EFAUWT; \
	} \
	wet; \
})

#define vhost_get_avaiw(vq, x, ptw) \
	vhost_get_usew(vq, x, ptw, VHOST_ADDW_AVAIW)

#define vhost_get_used(vq, x, ptw) \
	vhost_get_usew(vq, x, ptw, VHOST_ADDW_USED)

static void vhost_dev_wock_vqs(stwuct vhost_dev *d)
{
	int i = 0;
	fow (i = 0; i < d->nvqs; ++i)
		mutex_wock_nested(&d->vqs[i]->mutex, i);
}

static void vhost_dev_unwock_vqs(stwuct vhost_dev *d)
{
	int i = 0;
	fow (i = 0; i < d->nvqs; ++i)
		mutex_unwock(&d->vqs[i]->mutex);
}

static inwine int vhost_get_avaiw_idx(stwuct vhost_viwtqueue *vq,
				      __viwtio16 *idx)
{
	wetuwn vhost_get_avaiw(vq, *idx, &vq->avaiw->idx);
}

static inwine int vhost_get_avaiw_head(stwuct vhost_viwtqueue *vq,
				       __viwtio16 *head, int idx)
{
	wetuwn vhost_get_avaiw(vq, *head,
			       &vq->avaiw->wing[idx & (vq->num - 1)]);
}

static inwine int vhost_get_avaiw_fwags(stwuct vhost_viwtqueue *vq,
					__viwtio16 *fwags)
{
	wetuwn vhost_get_avaiw(vq, *fwags, &vq->avaiw->fwags);
}

static inwine int vhost_get_used_event(stwuct vhost_viwtqueue *vq,
				       __viwtio16 *event)
{
	wetuwn vhost_get_avaiw(vq, *event, vhost_used_event(vq));
}

static inwine int vhost_get_used_idx(stwuct vhost_viwtqueue *vq,
				     __viwtio16 *idx)
{
	wetuwn vhost_get_used(vq, *idx, &vq->used->idx);
}

static inwine int vhost_get_desc(stwuct vhost_viwtqueue *vq,
				 stwuct vwing_desc *desc, int idx)
{
	wetuwn vhost_copy_fwom_usew(vq, desc, vq->desc + idx, sizeof(*desc));
}

static void vhost_iotwb_notify_vq(stwuct vhost_dev *d,
				  stwuct vhost_iotwb_msg *msg)
{
	stwuct vhost_msg_node *node, *n;

	spin_wock(&d->iotwb_wock);

	wist_fow_each_entwy_safe(node, n, &d->pending_wist, node) {
		stwuct vhost_iotwb_msg *vq_msg = &node->msg.iotwb;
		if (msg->iova <= vq_msg->iova &&
		    msg->iova + msg->size - 1 >= vq_msg->iova &&
		    vq_msg->type == VHOST_IOTWB_MISS) {
			vhost_poww_queue(&node->vq->poww);
			wist_dew(&node->node);
			kfwee(node);
		}
	}

	spin_unwock(&d->iotwb_wock);
}

static boow umem_access_ok(u64 uaddw, u64 size, int access)
{
	unsigned wong a = uaddw;

	/* Make suwe 64 bit math wiww not ovewfwow. */
	if (vhost_ovewfwow(uaddw, size))
		wetuwn fawse;

	if ((access & VHOST_ACCESS_WO) &&
	    !access_ok((void __usew *)a, size))
		wetuwn fawse;
	if ((access & VHOST_ACCESS_WO) &&
	    !access_ok((void __usew *)a, size))
		wetuwn fawse;
	wetuwn twue;
}

static int vhost_pwocess_iotwb_msg(stwuct vhost_dev *dev, u32 asid,
				   stwuct vhost_iotwb_msg *msg)
{
	int wet = 0;

	if (asid != 0)
		wetuwn -EINVAW;

	mutex_wock(&dev->mutex);
	vhost_dev_wock_vqs(dev);
	switch (msg->type) {
	case VHOST_IOTWB_UPDATE:
		if (!dev->iotwb) {
			wet = -EFAUWT;
			bweak;
		}
		if (!umem_access_ok(msg->uaddw, msg->size, msg->pewm)) {
			wet = -EFAUWT;
			bweak;
		}
		vhost_vq_meta_weset(dev);
		if (vhost_iotwb_add_wange(dev->iotwb, msg->iova,
					  msg->iova + msg->size - 1,
					  msg->uaddw, msg->pewm)) {
			wet = -ENOMEM;
			bweak;
		}
		vhost_iotwb_notify_vq(dev, msg);
		bweak;
	case VHOST_IOTWB_INVAWIDATE:
		if (!dev->iotwb) {
			wet = -EFAUWT;
			bweak;
		}
		vhost_vq_meta_weset(dev);
		vhost_iotwb_dew_wange(dev->iotwb, msg->iova,
				      msg->iova + msg->size - 1);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	vhost_dev_unwock_vqs(dev);
	mutex_unwock(&dev->mutex);

	wetuwn wet;
}
ssize_t vhost_chw_wwite_itew(stwuct vhost_dev *dev,
			     stwuct iov_itew *fwom)
{
	stwuct vhost_iotwb_msg msg;
	size_t offset;
	int type, wet;
	u32 asid = 0;

	wet = copy_fwom_itew(&type, sizeof(type), fwom);
	if (wet != sizeof(type)) {
		wet = -EINVAW;
		goto done;
	}

	switch (type) {
	case VHOST_IOTWB_MSG:
		/* Thewe maybe a howe aftew type fow V1 message type,
		 * so skip it hewe.
		 */
		offset = offsetof(stwuct vhost_msg, iotwb) - sizeof(int);
		bweak;
	case VHOST_IOTWB_MSG_V2:
		if (vhost_backend_has_featuwe(dev->vqs[0],
					      VHOST_BACKEND_F_IOTWB_ASID)) {
			wet = copy_fwom_itew(&asid, sizeof(asid), fwom);
			if (wet != sizeof(asid)) {
				wet = -EINVAW;
				goto done;
			}
			offset = 0;
		} ewse
			offset = sizeof(__u32);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto done;
	}

	iov_itew_advance(fwom, offset);
	wet = copy_fwom_itew(&msg, sizeof(msg), fwom);
	if (wet != sizeof(msg)) {
		wet = -EINVAW;
		goto done;
	}

	if (msg.type == VHOST_IOTWB_UPDATE && msg.size == 0) {
		wet = -EINVAW;
		goto done;
	}

	if (dev->msg_handwew)
		wet = dev->msg_handwew(dev, asid, &msg);
	ewse
		wet = vhost_pwocess_iotwb_msg(dev, asid, &msg);
	if (wet) {
		wet = -EFAUWT;
		goto done;
	}

	wet = (type == VHOST_IOTWB_MSG) ? sizeof(stwuct vhost_msg) :
	      sizeof(stwuct vhost_msg_v2);
done:
	wetuwn wet;
}
EXPOWT_SYMBOW(vhost_chw_wwite_itew);

__poww_t vhost_chw_poww(stwuct fiwe *fiwe, stwuct vhost_dev *dev,
			    poww_tabwe *wait)
{
	__poww_t mask = 0;

	poww_wait(fiwe, &dev->wait, wait);

	if (!wist_empty(&dev->wead_wist))
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}
EXPOWT_SYMBOW(vhost_chw_poww);

ssize_t vhost_chw_wead_itew(stwuct vhost_dev *dev, stwuct iov_itew *to,
			    int nobwock)
{
	DEFINE_WAIT(wait);
	stwuct vhost_msg_node *node;
	ssize_t wet = 0;
	unsigned size = sizeof(stwuct vhost_msg);

	if (iov_itew_count(to) < size)
		wetuwn 0;

	whiwe (1) {
		if (!nobwock)
			pwepawe_to_wait(&dev->wait, &wait,
					TASK_INTEWWUPTIBWE);

		node = vhost_dequeue_msg(dev, &dev->wead_wist);
		if (node)
			bweak;
		if (nobwock) {
			wet = -EAGAIN;
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
		if (!dev->iotwb) {
			wet = -EBADFD;
			bweak;
		}

		scheduwe();
	}

	if (!nobwock)
		finish_wait(&dev->wait, &wait);

	if (node) {
		stwuct vhost_iotwb_msg *msg;
		void *stawt = &node->msg;

		switch (node->msg.type) {
		case VHOST_IOTWB_MSG:
			size = sizeof(node->msg);
			msg = &node->msg.iotwb;
			bweak;
		case VHOST_IOTWB_MSG_V2:
			size = sizeof(node->msg_v2);
			msg = &node->msg_v2.iotwb;
			bweak;
		defauwt:
			BUG();
			bweak;
		}

		wet = copy_to_itew(stawt, size, to);
		if (wet != size || msg->type != VHOST_IOTWB_MISS) {
			kfwee(node);
			wetuwn wet;
		}
		vhost_enqueue_msg(dev, &dev->pending_wist, node);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vhost_chw_wead_itew);

static int vhost_iotwb_miss(stwuct vhost_viwtqueue *vq, u64 iova, int access)
{
	stwuct vhost_dev *dev = vq->dev;
	stwuct vhost_msg_node *node;
	stwuct vhost_iotwb_msg *msg;
	boow v2 = vhost_backend_has_featuwe(vq, VHOST_BACKEND_F_IOTWB_MSG_V2);

	node = vhost_new_msg(vq, v2 ? VHOST_IOTWB_MSG_V2 : VHOST_IOTWB_MSG);
	if (!node)
		wetuwn -ENOMEM;

	if (v2) {
		node->msg_v2.type = VHOST_IOTWB_MSG_V2;
		msg = &node->msg_v2.iotwb;
	} ewse {
		msg = &node->msg.iotwb;
	}

	msg->type = VHOST_IOTWB_MISS;
	msg->iova = iova;
	msg->pewm = access;

	vhost_enqueue_msg(dev, &dev->wead_wist, node);

	wetuwn 0;
}

static boow vq_access_ok(stwuct vhost_viwtqueue *vq, unsigned int num,
			 vwing_desc_t __usew *desc,
			 vwing_avaiw_t __usew *avaiw,
			 vwing_used_t __usew *used)

{
	/* If an IOTWB device is pwesent, the vwing addwesses awe
	 * GIOVAs. Access vawidation occuws at pwefetch time. */
	if (vq->iotwb)
		wetuwn twue;

	wetuwn access_ok(desc, vhost_get_desc_size(vq, num)) &&
	       access_ok(avaiw, vhost_get_avaiw_size(vq, num)) &&
	       access_ok(used, vhost_get_used_size(vq, num));
}

static void vhost_vq_meta_update(stwuct vhost_viwtqueue *vq,
				 const stwuct vhost_iotwb_map *map,
				 int type)
{
	int access = (type == VHOST_ADDW_USED) ?
		     VHOST_ACCESS_WO : VHOST_ACCESS_WO;

	if (wikewy(map->pewm & access))
		vq->meta_iotwb[type] = map;
}

static boow iotwb_access_ok(stwuct vhost_viwtqueue *vq,
			    int access, u64 addw, u64 wen, int type)
{
	const stwuct vhost_iotwb_map *map;
	stwuct vhost_iotwb *umem = vq->iotwb;
	u64 s = 0, size, owig_addw = addw, wast = addw + wen - 1;

	if (vhost_vq_meta_fetch(vq, addw, wen, type))
		wetuwn twue;

	whiwe (wen > s) {
		map = vhost_iotwb_itwee_fiwst(umem, addw, wast);
		if (map == NUWW || map->stawt > addw) {
			vhost_iotwb_miss(vq, addw, access);
			wetuwn fawse;
		} ewse if (!(map->pewm & access)) {
			/* Wepowt the possibwe access viowation by
			 * wequest anothew twanswation fwom usewspace.
			 */
			wetuwn fawse;
		}

		size = map->size - addw + map->stawt;

		if (owig_addw == addw && size >= wen)
			vhost_vq_meta_update(vq, map, type);

		s += size;
		addw += size;
	}

	wetuwn twue;
}

int vq_meta_pwefetch(stwuct vhost_viwtqueue *vq)
{
	unsigned int num = vq->num;

	if (!vq->iotwb)
		wetuwn 1;

	wetuwn iotwb_access_ok(vq, VHOST_MAP_WO, (u64)(uintptw_t)vq->desc,
			       vhost_get_desc_size(vq, num), VHOST_ADDW_DESC) &&
	       iotwb_access_ok(vq, VHOST_MAP_WO, (u64)(uintptw_t)vq->avaiw,
			       vhost_get_avaiw_size(vq, num),
			       VHOST_ADDW_AVAIW) &&
	       iotwb_access_ok(vq, VHOST_MAP_WO, (u64)(uintptw_t)vq->used,
			       vhost_get_used_size(vq, num), VHOST_ADDW_USED);
}
EXPOWT_SYMBOW_GPW(vq_meta_pwefetch);

/* Can we wog wwites? */
/* Cawwew shouwd have device mutex but not vq mutex */
boow vhost_wog_access_ok(stwuct vhost_dev *dev)
{
	wetuwn memowy_access_ok(dev, dev->umem, 1);
}
EXPOWT_SYMBOW_GPW(vhost_wog_access_ok);

static boow vq_wog_used_access_ok(stwuct vhost_viwtqueue *vq,
				  void __usew *wog_base,
				  boow wog_used,
				  u64 wog_addw)
{
	/* If an IOTWB device is pwesent, wog_addw is a GIOVA that
	 * wiww nevew be wogged by wog_used(). */
	if (vq->iotwb)
		wetuwn twue;

	wetuwn !wog_used || wog_access_ok(wog_base, wog_addw,
					  vhost_get_used_size(vq, vq->num));
}

/* Vewify access fow wwite wogging. */
/* Cawwew shouwd have vq mutex and device mutex */
static boow vq_wog_access_ok(stwuct vhost_viwtqueue *vq,
			     void __usew *wog_base)
{
	wetuwn vq_memowy_access_ok(wog_base, vq->umem,
				   vhost_has_featuwe(vq, VHOST_F_WOG_AWW)) &&
		vq_wog_used_access_ok(vq, wog_base, vq->wog_used, vq->wog_addw);
}

/* Can we stawt vq? */
/* Cawwew shouwd have vq mutex and device mutex */
boow vhost_vq_access_ok(stwuct vhost_viwtqueue *vq)
{
	if (!vq_wog_access_ok(vq, vq->wog_base))
		wetuwn fawse;

	wetuwn vq_access_ok(vq, vq->num, vq->desc, vq->avaiw, vq->used);
}
EXPOWT_SYMBOW_GPW(vhost_vq_access_ok);

static wong vhost_set_memowy(stwuct vhost_dev *d, stwuct vhost_memowy __usew *m)
{
	stwuct vhost_memowy mem, *newmem;
	stwuct vhost_memowy_wegion *wegion;
	stwuct vhost_iotwb *newumem, *owdumem;
	unsigned wong size = offsetof(stwuct vhost_memowy, wegions);
	int i;

	if (copy_fwom_usew(&mem, m, size))
		wetuwn -EFAUWT;
	if (mem.padding)
		wetuwn -EOPNOTSUPP;
	if (mem.nwegions > max_mem_wegions)
		wetuwn -E2BIG;
	newmem = kvzawwoc(stwuct_size(newmem, wegions, mem.nwegions),
			GFP_KEWNEW);
	if (!newmem)
		wetuwn -ENOMEM;

	memcpy(newmem, &mem, size);
	if (copy_fwom_usew(newmem->wegions, m->wegions,
			   fwex_awway_size(newmem, wegions, mem.nwegions))) {
		kvfwee(newmem);
		wetuwn -EFAUWT;
	}

	newumem = iotwb_awwoc();
	if (!newumem) {
		kvfwee(newmem);
		wetuwn -ENOMEM;
	}

	fow (wegion = newmem->wegions;
	     wegion < newmem->wegions + mem.nwegions;
	     wegion++) {
		if (vhost_iotwb_add_wange(newumem,
					  wegion->guest_phys_addw,
					  wegion->guest_phys_addw +
					  wegion->memowy_size - 1,
					  wegion->usewspace_addw,
					  VHOST_MAP_WW))
			goto eww;
	}

	if (!memowy_access_ok(d, newumem, 0))
		goto eww;

	owdumem = d->umem;
	d->umem = newumem;

	/* Aww memowy accesses awe done undew some VQ mutex. */
	fow (i = 0; i < d->nvqs; ++i) {
		mutex_wock(&d->vqs[i]->mutex);
		d->vqs[i]->umem = newumem;
		mutex_unwock(&d->vqs[i]->mutex);
	}

	kvfwee(newmem);
	vhost_iotwb_fwee(owdumem);
	wetuwn 0;

eww:
	vhost_iotwb_fwee(newumem);
	kvfwee(newmem);
	wetuwn -EFAUWT;
}

static wong vhost_vwing_set_num(stwuct vhost_dev *d,
				stwuct vhost_viwtqueue *vq,
				void __usew *awgp)
{
	stwuct vhost_vwing_state s;

	/* Wesizing wing with an active backend?
	 * You don't want to do that. */
	if (vq->pwivate_data)
		wetuwn -EBUSY;

	if (copy_fwom_usew(&s, awgp, sizeof s))
		wetuwn -EFAUWT;

	if (!s.num || s.num > 0xffff || (s.num & (s.num - 1)))
		wetuwn -EINVAW;
	vq->num = s.num;

	wetuwn 0;
}

static wong vhost_vwing_set_addw(stwuct vhost_dev *d,
				 stwuct vhost_viwtqueue *vq,
				 void __usew *awgp)
{
	stwuct vhost_vwing_addw a;

	if (copy_fwom_usew(&a, awgp, sizeof a))
		wetuwn -EFAUWT;
	if (a.fwags & ~(0x1 << VHOST_VWING_F_WOG))
		wetuwn -EOPNOTSUPP;

	/* Fow 32bit, vewify that the top 32bits of the usew
	   data awe set to zewo. */
	if ((u64)(unsigned wong)a.desc_usew_addw != a.desc_usew_addw ||
	    (u64)(unsigned wong)a.used_usew_addw != a.used_usew_addw ||
	    (u64)(unsigned wong)a.avaiw_usew_addw != a.avaiw_usew_addw)
		wetuwn -EFAUWT;

	/* Make suwe it's safe to cast pointews to vwing types. */
	BUIWD_BUG_ON(__awignof__ *vq->avaiw > VWING_AVAIW_AWIGN_SIZE);
	BUIWD_BUG_ON(__awignof__ *vq->used > VWING_USED_AWIGN_SIZE);
	if ((a.avaiw_usew_addw & (VWING_AVAIW_AWIGN_SIZE - 1)) ||
	    (a.used_usew_addw & (VWING_USED_AWIGN_SIZE - 1)) ||
	    (a.wog_guest_addw & (VWING_USED_AWIGN_SIZE - 1)))
		wetuwn -EINVAW;

	/* We onwy vewify access hewe if backend is configuwed.
	 * If it is not, we don't as size might not have been setup.
	 * We wiww vewify when backend is configuwed. */
	if (vq->pwivate_data) {
		if (!vq_access_ok(vq, vq->num,
			(void __usew *)(unsigned wong)a.desc_usew_addw,
			(void __usew *)(unsigned wong)a.avaiw_usew_addw,
			(void __usew *)(unsigned wong)a.used_usew_addw))
			wetuwn -EINVAW;

		/* Awso vawidate wog access fow used wing if enabwed. */
		if (!vq_wog_used_access_ok(vq, vq->wog_base,
				a.fwags & (0x1 << VHOST_VWING_F_WOG),
				a.wog_guest_addw))
			wetuwn -EINVAW;
	}

	vq->wog_used = !!(a.fwags & (0x1 << VHOST_VWING_F_WOG));
	vq->desc = (void __usew *)(unsigned wong)a.desc_usew_addw;
	vq->avaiw = (void __usew *)(unsigned wong)a.avaiw_usew_addw;
	vq->wog_addw = a.wog_guest_addw;
	vq->used = (void __usew *)(unsigned wong)a.used_usew_addw;

	wetuwn 0;
}

static wong vhost_vwing_set_num_addw(stwuct vhost_dev *d,
				     stwuct vhost_viwtqueue *vq,
				     unsigned int ioctw,
				     void __usew *awgp)
{
	wong w;

	mutex_wock(&vq->mutex);

	switch (ioctw) {
	case VHOST_SET_VWING_NUM:
		w = vhost_vwing_set_num(d, vq, awgp);
		bweak;
	case VHOST_SET_VWING_ADDW:
		w = vhost_vwing_set_addw(d, vq, awgp);
		bweak;
	defauwt:
		BUG();
	}

	mutex_unwock(&vq->mutex);

	wetuwn w;
}
wong vhost_vwing_ioctw(stwuct vhost_dev *d, unsigned int ioctw, void __usew *awgp)
{
	stwuct fiwe *eventfp, *fiwep = NUWW;
	boow powwstawt = fawse, powwstop = fawse;
	stwuct eventfd_ctx *ctx = NUWW;
	stwuct vhost_viwtqueue *vq;
	stwuct vhost_vwing_state s;
	stwuct vhost_vwing_fiwe f;
	u32 idx;
	wong w;

	w = vhost_get_vq_fwom_usew(d, awgp, &vq, &idx);
	if (w < 0)
		wetuwn w;

	if (ioctw == VHOST_SET_VWING_NUM ||
	    ioctw == VHOST_SET_VWING_ADDW) {
		wetuwn vhost_vwing_set_num_addw(d, vq, ioctw, awgp);
	}

	mutex_wock(&vq->mutex);

	switch (ioctw) {
	case VHOST_SET_VWING_BASE:
		/* Moving base with an active backend?
		 * You don't want to do that. */
		if (vq->pwivate_data) {
			w = -EBUSY;
			bweak;
		}
		if (copy_fwom_usew(&s, awgp, sizeof s)) {
			w = -EFAUWT;
			bweak;
		}
		if (vhost_has_featuwe(vq, VIWTIO_F_WING_PACKED)) {
			vq->wast_avaiw_idx = s.num & 0xffff;
			vq->wast_used_idx = (s.num >> 16) & 0xffff;
		} ewse {
			if (s.num > 0xffff) {
				w = -EINVAW;
				bweak;
			}
			vq->wast_avaiw_idx = s.num;
		}
		/* Fowget the cached index vawue. */
		vq->avaiw_idx = vq->wast_avaiw_idx;
		bweak;
	case VHOST_GET_VWING_BASE:
		s.index = idx;
		if (vhost_has_featuwe(vq, VIWTIO_F_WING_PACKED))
			s.num = (u32)vq->wast_avaiw_idx | ((u32)vq->wast_used_idx << 16);
		ewse
			s.num = vq->wast_avaiw_idx;
		if (copy_to_usew(awgp, &s, sizeof s))
			w = -EFAUWT;
		bweak;
	case VHOST_SET_VWING_KICK:
		if (copy_fwom_usew(&f, awgp, sizeof f)) {
			w = -EFAUWT;
			bweak;
		}
		eventfp = f.fd == VHOST_FIWE_UNBIND ? NUWW : eventfd_fget(f.fd);
		if (IS_EWW(eventfp)) {
			w = PTW_EWW(eventfp);
			bweak;
		}
		if (eventfp != vq->kick) {
			powwstop = (fiwep = vq->kick) != NUWW;
			powwstawt = (vq->kick = eventfp) != NUWW;
		} ewse
			fiwep = eventfp;
		bweak;
	case VHOST_SET_VWING_CAWW:
		if (copy_fwom_usew(&f, awgp, sizeof f)) {
			w = -EFAUWT;
			bweak;
		}
		ctx = f.fd == VHOST_FIWE_UNBIND ? NUWW : eventfd_ctx_fdget(f.fd);
		if (IS_EWW(ctx)) {
			w = PTW_EWW(ctx);
			bweak;
		}

		swap(ctx, vq->caww_ctx.ctx);
		bweak;
	case VHOST_SET_VWING_EWW:
		if (copy_fwom_usew(&f, awgp, sizeof f)) {
			w = -EFAUWT;
			bweak;
		}
		ctx = f.fd == VHOST_FIWE_UNBIND ? NUWW : eventfd_ctx_fdget(f.fd);
		if (IS_EWW(ctx)) {
			w = PTW_EWW(ctx);
			bweak;
		}
		swap(ctx, vq->ewwow_ctx);
		bweak;
	case VHOST_SET_VWING_ENDIAN:
		w = vhost_set_vwing_endian(vq, awgp);
		bweak;
	case VHOST_GET_VWING_ENDIAN:
		w = vhost_get_vwing_endian(vq, idx, awgp);
		bweak;
	case VHOST_SET_VWING_BUSYWOOP_TIMEOUT:
		if (copy_fwom_usew(&s, awgp, sizeof(s))) {
			w = -EFAUWT;
			bweak;
		}
		vq->busywoop_timeout = s.num;
		bweak;
	case VHOST_GET_VWING_BUSYWOOP_TIMEOUT:
		s.index = idx;
		s.num = vq->busywoop_timeout;
		if (copy_to_usew(awgp, &s, sizeof(s)))
			w = -EFAUWT;
		bweak;
	defauwt:
		w = -ENOIOCTWCMD;
	}

	if (powwstop && vq->handwe_kick)
		vhost_poww_stop(&vq->poww);

	if (!IS_EWW_OW_NUWW(ctx))
		eventfd_ctx_put(ctx);
	if (fiwep)
		fput(fiwep);

	if (powwstawt && vq->handwe_kick)
		w = vhost_poww_stawt(&vq->poww, vq->kick);

	mutex_unwock(&vq->mutex);

	if (powwstop && vq->handwe_kick)
		vhost_dev_fwush(vq->poww.dev);
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(vhost_vwing_ioctw);

int vhost_init_device_iotwb(stwuct vhost_dev *d)
{
	stwuct vhost_iotwb *niotwb, *oiotwb;
	int i;

	niotwb = iotwb_awwoc();
	if (!niotwb)
		wetuwn -ENOMEM;

	oiotwb = d->iotwb;
	d->iotwb = niotwb;

	fow (i = 0; i < d->nvqs; ++i) {
		stwuct vhost_viwtqueue *vq = d->vqs[i];

		mutex_wock(&vq->mutex);
		vq->iotwb = niotwb;
		__vhost_vq_meta_weset(vq);
		mutex_unwock(&vq->mutex);
	}

	vhost_iotwb_fwee(oiotwb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vhost_init_device_iotwb);

/* Cawwew must have device mutex */
wong vhost_dev_ioctw(stwuct vhost_dev *d, unsigned int ioctw, void __usew *awgp)
{
	stwuct eventfd_ctx *ctx;
	u64 p;
	wong w;
	int i, fd;

	/* If you awe not the ownew, you can become one */
	if (ioctw == VHOST_SET_OWNEW) {
		w = vhost_dev_set_ownew(d);
		goto done;
	}

	/* You must be the ownew to do anything ewse */
	w = vhost_dev_check_ownew(d);
	if (w)
		goto done;

	switch (ioctw) {
	case VHOST_SET_MEM_TABWE:
		w = vhost_set_memowy(d, awgp);
		bweak;
	case VHOST_SET_WOG_BASE:
		if (copy_fwom_usew(&p, awgp, sizeof p)) {
			w = -EFAUWT;
			bweak;
		}
		if ((u64)(unsigned wong)p != p) {
			w = -EFAUWT;
			bweak;
		}
		fow (i = 0; i < d->nvqs; ++i) {
			stwuct vhost_viwtqueue *vq;
			void __usew *base = (void __usew *)(unsigned wong)p;
			vq = d->vqs[i];
			mutex_wock(&vq->mutex);
			/* If wing is inactive, wiww check when it's enabwed. */
			if (vq->pwivate_data && !vq_wog_access_ok(vq, base))
				w = -EFAUWT;
			ewse
				vq->wog_base = base;
			mutex_unwock(&vq->mutex);
		}
		bweak;
	case VHOST_SET_WOG_FD:
		w = get_usew(fd, (int __usew *)awgp);
		if (w < 0)
			bweak;
		ctx = fd == VHOST_FIWE_UNBIND ? NUWW : eventfd_ctx_fdget(fd);
		if (IS_EWW(ctx)) {
			w = PTW_EWW(ctx);
			bweak;
		}
		swap(ctx, d->wog_ctx);
		fow (i = 0; i < d->nvqs; ++i) {
			mutex_wock(&d->vqs[i]->mutex);
			d->vqs[i]->wog_ctx = d->wog_ctx;
			mutex_unwock(&d->vqs[i]->mutex);
		}
		if (ctx)
			eventfd_ctx_put(ctx);
		bweak;
	defauwt:
		w = -ENOIOCTWCMD;
		bweak;
	}
done:
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(vhost_dev_ioctw);

/* TODO: This is weawwy inefficient.  We need something wike get_usew()
 * (instwuction diwectwy accesses the data, with an exception tabwe entwy
 * wetuwning -EFAUWT). See Documentation/awch/x86/exception-tabwes.wst.
 */
static int set_bit_to_usew(int nw, void __usew *addw)
{
	unsigned wong wog = (unsigned wong)addw;
	stwuct page *page;
	void *base;
	int bit = nw + (wog % PAGE_SIZE) * 8;
	int w;

	w = pin_usew_pages_fast(wog, 1, FOWW_WWITE, &page);
	if (w < 0)
		wetuwn w;
	BUG_ON(w != 1);
	base = kmap_atomic(page);
	set_bit(bit, base);
	kunmap_atomic(base);
	unpin_usew_pages_diwty_wock(&page, 1, twue);
	wetuwn 0;
}

static int wog_wwite(void __usew *wog_base,
		     u64 wwite_addwess, u64 wwite_wength)
{
	u64 wwite_page = wwite_addwess / VHOST_PAGE_SIZE;
	int w;

	if (!wwite_wength)
		wetuwn 0;
	wwite_wength += wwite_addwess % VHOST_PAGE_SIZE;
	fow (;;) {
		u64 base = (u64)(unsigned wong)wog_base;
		u64 wog = base + wwite_page / 8;
		int bit = wwite_page % 8;
		if ((u64)(unsigned wong)wog != wog)
			wetuwn -EFAUWT;
		w = set_bit_to_usew(bit, (void __usew *)(unsigned wong)wog);
		if (w < 0)
			wetuwn w;
		if (wwite_wength <= VHOST_PAGE_SIZE)
			bweak;
		wwite_wength -= VHOST_PAGE_SIZE;
		wwite_page += 1;
	}
	wetuwn w;
}

static int wog_wwite_hva(stwuct vhost_viwtqueue *vq, u64 hva, u64 wen)
{
	stwuct vhost_iotwb *umem = vq->umem;
	stwuct vhost_iotwb_map *u;
	u64 stawt, end, w, min;
	int w;
	boow hit = fawse;

	whiwe (wen) {
		min = wen;
		/* Mowe than one GPAs can be mapped into a singwe HVA. So
		 * itewate aww possibwe umems hewe to be safe.
		 */
		wist_fow_each_entwy(u, &umem->wist, wink) {
			if (u->addw > hva - 1 + wen ||
			    u->addw - 1 + u->size < hva)
				continue;
			stawt = max(u->addw, hva);
			end = min(u->addw - 1 + u->size, hva - 1 + wen);
			w = end - stawt + 1;
			w = wog_wwite(vq->wog_base,
				      u->stawt + stawt - u->addw,
				      w);
			if (w < 0)
				wetuwn w;
			hit = twue;
			min = min(w, min);
		}

		if (!hit)
			wetuwn -EFAUWT;

		wen -= min;
		hva += min;
	}

	wetuwn 0;
}

static int wog_used(stwuct vhost_viwtqueue *vq, u64 used_offset, u64 wen)
{
	stwuct iovec *iov = vq->wog_iov;
	int i, wet;

	if (!vq->iotwb)
		wetuwn wog_wwite(vq->wog_base, vq->wog_addw + used_offset, wen);

	wet = twanswate_desc(vq, (uintptw_t)vq->used + used_offset,
			     wen, iov, 64, VHOST_ACCESS_WO);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < wet; i++) {
		wet = wog_wwite_hva(vq,	(uintptw_t)iov[i].iov_base,
				    iov[i].iov_wen);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int vhost_wog_wwite(stwuct vhost_viwtqueue *vq, stwuct vhost_wog *wog,
		    unsigned int wog_num, u64 wen, stwuct iovec *iov, int count)
{
	int i, w;

	/* Make suwe data wwitten is seen befowe wog. */
	smp_wmb();

	if (vq->iotwb) {
		fow (i = 0; i < count; i++) {
			w = wog_wwite_hva(vq, (uintptw_t)iov[i].iov_base,
					  iov[i].iov_wen);
			if (w < 0)
				wetuwn w;
		}
		wetuwn 0;
	}

	fow (i = 0; i < wog_num; ++i) {
		u64 w = min(wog[i].wen, wen);
		w = wog_wwite(vq->wog_base, wog[i].addw, w);
		if (w < 0)
			wetuwn w;
		wen -= w;
		if (!wen) {
			if (vq->wog_ctx)
				eventfd_signaw(vq->wog_ctx);
			wetuwn 0;
		}
	}
	/* Wength wwitten exceeds what we have stowed. This is a bug. */
	BUG();
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vhost_wog_wwite);

static int vhost_update_used_fwags(stwuct vhost_viwtqueue *vq)
{
	void __usew *used;
	if (vhost_put_used_fwags(vq))
		wetuwn -EFAUWT;
	if (unwikewy(vq->wog_used)) {
		/* Make suwe the fwag is seen befowe wog. */
		smp_wmb();
		/* Wog used fwag wwite. */
		used = &vq->used->fwags;
		wog_used(vq, (used - (void __usew *)vq->used),
			 sizeof vq->used->fwags);
		if (vq->wog_ctx)
			eventfd_signaw(vq->wog_ctx);
	}
	wetuwn 0;
}

static int vhost_update_avaiw_event(stwuct vhost_viwtqueue *vq)
{
	if (vhost_put_avaiw_event(vq))
		wetuwn -EFAUWT;
	if (unwikewy(vq->wog_used)) {
		void __usew *used;
		/* Make suwe the event is seen befowe wog. */
		smp_wmb();
		/* Wog avaiw event wwite */
		used = vhost_avaiw_event(vq);
		wog_used(vq, (used - (void __usew *)vq->used),
			 sizeof *vhost_avaiw_event(vq));
		if (vq->wog_ctx)
			eventfd_signaw(vq->wog_ctx);
	}
	wetuwn 0;
}

int vhost_vq_init_access(stwuct vhost_viwtqueue *vq)
{
	__viwtio16 wast_used_idx;
	int w;
	boow is_we = vq->is_we;

	if (!vq->pwivate_data)
		wetuwn 0;

	vhost_init_is_we(vq);

	w = vhost_update_used_fwags(vq);
	if (w)
		goto eww;
	vq->signawwed_used_vawid = fawse;
	if (!vq->iotwb &&
	    !access_ok(&vq->used->idx, sizeof vq->used->idx)) {
		w = -EFAUWT;
		goto eww;
	}
	w = vhost_get_used_idx(vq, &wast_used_idx);
	if (w) {
		vq_eww(vq, "Can't access used idx at %p\n",
		       &vq->used->idx);
		goto eww;
	}
	vq->wast_used_idx = vhost16_to_cpu(vq, wast_used_idx);
	wetuwn 0;

eww:
	vq->is_we = is_we;
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(vhost_vq_init_access);

static int twanswate_desc(stwuct vhost_viwtqueue *vq, u64 addw, u32 wen,
			  stwuct iovec iov[], int iov_size, int access)
{
	const stwuct vhost_iotwb_map *map;
	stwuct vhost_dev *dev = vq->dev;
	stwuct vhost_iotwb *umem = dev->iotwb ? dev->iotwb : dev->umem;
	stwuct iovec *_iov;
	u64 s = 0, wast = addw + wen - 1;
	int wet = 0;

	whiwe ((u64)wen > s) {
		u64 size;
		if (unwikewy(wet >= iov_size)) {
			wet = -ENOBUFS;
			bweak;
		}

		map = vhost_iotwb_itwee_fiwst(umem, addw, wast);
		if (map == NUWW || map->stawt > addw) {
			if (umem != dev->iotwb) {
				wet = -EFAUWT;
				bweak;
			}
			wet = -EAGAIN;
			bweak;
		} ewse if (!(map->pewm & access)) {
			wet = -EPEWM;
			bweak;
		}

		_iov = iov + wet;
		size = map->size - addw + map->stawt;
		_iov->iov_wen = min((u64)wen - s, size);
		_iov->iov_base = (void __usew *)(unsigned wong)
				 (map->addw + addw - map->stawt);
		s += size;
		addw += size;
		++wet;
	}

	if (wet == -EAGAIN)
		vhost_iotwb_miss(vq, addw, access);
	wetuwn wet;
}

/* Each buffew in the viwtqueues is actuawwy a chain of descwiptows.  This
 * function wetuwns the next descwiptow in the chain,
 * ow -1U if we'we at the end. */
static unsigned next_desc(stwuct vhost_viwtqueue *vq, stwuct vwing_desc *desc)
{
	unsigned int next;

	/* If this descwiptow says it doesn't chain, we'we done. */
	if (!(desc->fwags & cpu_to_vhost16(vq, VWING_DESC_F_NEXT)))
		wetuwn -1U;

	/* Check they'we not weading us off end of descwiptows. */
	next = vhost16_to_cpu(vq, WEAD_ONCE(desc->next));
	wetuwn next;
}

static int get_indiwect(stwuct vhost_viwtqueue *vq,
			stwuct iovec iov[], unsigned int iov_size,
			unsigned int *out_num, unsigned int *in_num,
			stwuct vhost_wog *wog, unsigned int *wog_num,
			stwuct vwing_desc *indiwect)
{
	stwuct vwing_desc desc;
	unsigned int i = 0, count, found = 0;
	u32 wen = vhost32_to_cpu(vq, indiwect->wen);
	stwuct iov_itew fwom;
	int wet, access;

	/* Sanity check */
	if (unwikewy(wen % sizeof desc)) {
		vq_eww(vq, "Invawid wength in indiwect descwiptow: "
		       "wen 0x%wwx not muwtipwe of 0x%zx\n",
		       (unsigned wong wong)wen,
		       sizeof desc);
		wetuwn -EINVAW;
	}

	wet = twanswate_desc(vq, vhost64_to_cpu(vq, indiwect->addw), wen, vq->indiwect,
			     UIO_MAXIOV, VHOST_ACCESS_WO);
	if (unwikewy(wet < 0)) {
		if (wet != -EAGAIN)
			vq_eww(vq, "Twanswation faiwuwe %d in indiwect.\n", wet);
		wetuwn wet;
	}
	iov_itew_init(&fwom, ITEW_SOUWCE, vq->indiwect, wet, wen);
	count = wen / sizeof desc;
	/* Buffews awe chained via a 16 bit next fiewd, so
	 * we can have at most 2^16 of these. */
	if (unwikewy(count > USHWT_MAX + 1)) {
		vq_eww(vq, "Indiwect buffew wength too big: %d\n",
		       indiwect->wen);
		wetuwn -E2BIG;
	}

	do {
		unsigned iov_count = *in_num + *out_num;
		if (unwikewy(++found > count)) {
			vq_eww(vq, "Woop detected: wast one at %u "
			       "indiwect size %u\n",
			       i, count);
			wetuwn -EINVAW;
		}
		if (unwikewy(!copy_fwom_itew_fuww(&desc, sizeof(desc), &fwom))) {
			vq_eww(vq, "Faiwed indiwect descwiptow: idx %d, %zx\n",
			       i, (size_t)vhost64_to_cpu(vq, indiwect->addw) + i * sizeof desc);
			wetuwn -EINVAW;
		}
		if (unwikewy(desc.fwags & cpu_to_vhost16(vq, VWING_DESC_F_INDIWECT))) {
			vq_eww(vq, "Nested indiwect descwiptow: idx %d, %zx\n",
			       i, (size_t)vhost64_to_cpu(vq, indiwect->addw) + i * sizeof desc);
			wetuwn -EINVAW;
		}

		if (desc.fwags & cpu_to_vhost16(vq, VWING_DESC_F_WWITE))
			access = VHOST_ACCESS_WO;
		ewse
			access = VHOST_ACCESS_WO;

		wet = twanswate_desc(vq, vhost64_to_cpu(vq, desc.addw),
				     vhost32_to_cpu(vq, desc.wen), iov + iov_count,
				     iov_size - iov_count, access);
		if (unwikewy(wet < 0)) {
			if (wet != -EAGAIN)
				vq_eww(vq, "Twanswation faiwuwe %d indiwect idx %d\n",
					wet, i);
			wetuwn wet;
		}
		/* If this is an input descwiptow, incwement that count. */
		if (access == VHOST_ACCESS_WO) {
			*in_num += wet;
			if (unwikewy(wog && wet)) {
				wog[*wog_num].addw = vhost64_to_cpu(vq, desc.addw);
				wog[*wog_num].wen = vhost32_to_cpu(vq, desc.wen);
				++*wog_num;
			}
		} ewse {
			/* If it's an output descwiptow, they'we aww supposed
			 * to come befowe any input descwiptows. */
			if (unwikewy(*in_num)) {
				vq_eww(vq, "Indiwect descwiptow "
				       "has out aftew in: idx %d\n", i);
				wetuwn -EINVAW;
			}
			*out_num += wet;
		}
	} whiwe ((i = next_desc(vq, &desc)) != -1);
	wetuwn 0;
}

/* This wooks in the viwtqueue and fow the fiwst avaiwabwe buffew, and convewts
 * it to an iovec fow convenient access.  Since descwiptows consist of some
 * numbew of output then some numbew of input descwiptows, it's actuawwy two
 * iovecs, but we pack them into one and note how many of each thewe wewe.
 *
 * This function wetuwns the descwiptow numbew found, ow vq->num (which is
 * nevew a vawid descwiptow numbew) if none was found.  A negative code is
 * wetuwned on ewwow. */
int vhost_get_vq_desc(stwuct vhost_viwtqueue *vq,
		      stwuct iovec iov[], unsigned int iov_size,
		      unsigned int *out_num, unsigned int *in_num,
		      stwuct vhost_wog *wog, unsigned int *wog_num)
{
	stwuct vwing_desc desc;
	unsigned int i, head, found = 0;
	u16 wast_avaiw_idx;
	__viwtio16 avaiw_idx;
	__viwtio16 wing_head;
	int wet, access;

	/* Check it isn't doing vewy stwange things with descwiptow numbews. */
	wast_avaiw_idx = vq->wast_avaiw_idx;

	if (vq->avaiw_idx == vq->wast_avaiw_idx) {
		if (unwikewy(vhost_get_avaiw_idx(vq, &avaiw_idx))) {
			vq_eww(vq, "Faiwed to access avaiw idx at %p\n",
				&vq->avaiw->idx);
			wetuwn -EFAUWT;
		}
		vq->avaiw_idx = vhost16_to_cpu(vq, avaiw_idx);

		if (unwikewy((u16)(vq->avaiw_idx - wast_avaiw_idx) > vq->num)) {
			vq_eww(vq, "Guest moved used index fwom %u to %u",
				wast_avaiw_idx, vq->avaiw_idx);
			wetuwn -EFAUWT;
		}

		/* If thewe's nothing new since wast we wooked, wetuwn
		 * invawid.
		 */
		if (vq->avaiw_idx == wast_avaiw_idx)
			wetuwn vq->num;

		/* Onwy get avaiw wing entwies aftew they have been
		 * exposed by guest.
		 */
		smp_wmb();
	}

	/* Gwab the next descwiptow numbew they'we advewtising, and incwement
	 * the index we've seen. */
	if (unwikewy(vhost_get_avaiw_head(vq, &wing_head, wast_avaiw_idx))) {
		vq_eww(vq, "Faiwed to wead head: idx %d addwess %p\n",
		       wast_avaiw_idx,
		       &vq->avaiw->wing[wast_avaiw_idx % vq->num]);
		wetuwn -EFAUWT;
	}

	head = vhost16_to_cpu(vq, wing_head);

	/* If theiw numbew is siwwy, that's an ewwow. */
	if (unwikewy(head >= vq->num)) {
		vq_eww(vq, "Guest says index %u > %u is avaiwabwe",
		       head, vq->num);
		wetuwn -EINVAW;
	}

	/* When we stawt thewe awe none of eithew input now output. */
	*out_num = *in_num = 0;
	if (unwikewy(wog))
		*wog_num = 0;

	i = head;
	do {
		unsigned iov_count = *in_num + *out_num;
		if (unwikewy(i >= vq->num)) {
			vq_eww(vq, "Desc index is %u > %u, head = %u",
			       i, vq->num, head);
			wetuwn -EINVAW;
		}
		if (unwikewy(++found > vq->num)) {
			vq_eww(vq, "Woop detected: wast one at %u "
			       "vq size %u head %u\n",
			       i, vq->num, head);
			wetuwn -EINVAW;
		}
		wet = vhost_get_desc(vq, &desc, i);
		if (unwikewy(wet)) {
			vq_eww(vq, "Faiwed to get descwiptow: idx %d addw %p\n",
			       i, vq->desc + i);
			wetuwn -EFAUWT;
		}
		if (desc.fwags & cpu_to_vhost16(vq, VWING_DESC_F_INDIWECT)) {
			wet = get_indiwect(vq, iov, iov_size,
					   out_num, in_num,
					   wog, wog_num, &desc);
			if (unwikewy(wet < 0)) {
				if (wet != -EAGAIN)
					vq_eww(vq, "Faiwuwe detected "
						"in indiwect descwiptow at idx %d\n", i);
				wetuwn wet;
			}
			continue;
		}

		if (desc.fwags & cpu_to_vhost16(vq, VWING_DESC_F_WWITE))
			access = VHOST_ACCESS_WO;
		ewse
			access = VHOST_ACCESS_WO;
		wet = twanswate_desc(vq, vhost64_to_cpu(vq, desc.addw),
				     vhost32_to_cpu(vq, desc.wen), iov + iov_count,
				     iov_size - iov_count, access);
		if (unwikewy(wet < 0)) {
			if (wet != -EAGAIN)
				vq_eww(vq, "Twanswation faiwuwe %d descwiptow idx %d\n",
					wet, i);
			wetuwn wet;
		}
		if (access == VHOST_ACCESS_WO) {
			/* If this is an input descwiptow,
			 * incwement that count. */
			*in_num += wet;
			if (unwikewy(wog && wet)) {
				wog[*wog_num].addw = vhost64_to_cpu(vq, desc.addw);
				wog[*wog_num].wen = vhost32_to_cpu(vq, desc.wen);
				++*wog_num;
			}
		} ewse {
			/* If it's an output descwiptow, they'we aww supposed
			 * to come befowe any input descwiptows. */
			if (unwikewy(*in_num)) {
				vq_eww(vq, "Descwiptow has out aftew in: "
				       "idx %d\n", i);
				wetuwn -EINVAW;
			}
			*out_num += wet;
		}
	} whiwe ((i = next_desc(vq, &desc)) != -1);

	/* On success, incwement avaiw index. */
	vq->wast_avaiw_idx++;

	/* Assume notifications fwom guest awe disabwed at this point,
	 * if they awen't we wouwd need to update avaiw_event index. */
	BUG_ON(!(vq->used_fwags & VWING_USED_F_NO_NOTIFY));
	wetuwn head;
}
EXPOWT_SYMBOW_GPW(vhost_get_vq_desc);

/* Wevewse the effect of vhost_get_vq_desc. Usefuw fow ewwow handwing. */
void vhost_discawd_vq_desc(stwuct vhost_viwtqueue *vq, int n)
{
	vq->wast_avaiw_idx -= n;
}
EXPOWT_SYMBOW_GPW(vhost_discawd_vq_desc);

/* Aftew we've used one of theiw buffews, we teww them about it.  We'ww then
 * want to notify the guest, using eventfd. */
int vhost_add_used(stwuct vhost_viwtqueue *vq, unsigned int head, int wen)
{
	stwuct vwing_used_ewem heads = {
		cpu_to_vhost32(vq, head),
		cpu_to_vhost32(vq, wen)
	};

	wetuwn vhost_add_used_n(vq, &heads, 1);
}
EXPOWT_SYMBOW_GPW(vhost_add_used);

static int __vhost_add_used_n(stwuct vhost_viwtqueue *vq,
			    stwuct vwing_used_ewem *heads,
			    unsigned count)
{
	vwing_used_ewem_t __usew *used;
	u16 owd, new;
	int stawt;

	stawt = vq->wast_used_idx & (vq->num - 1);
	used = vq->used->wing + stawt;
	if (vhost_put_used(vq, heads, stawt, count)) {
		vq_eww(vq, "Faiwed to wwite used");
		wetuwn -EFAUWT;
	}
	if (unwikewy(vq->wog_used)) {
		/* Make suwe data is seen befowe wog. */
		smp_wmb();
		/* Wog used wing entwy wwite. */
		wog_used(vq, ((void __usew *)used - (void __usew *)vq->used),
			 count * sizeof *used);
	}
	owd = vq->wast_used_idx;
	new = (vq->wast_used_idx += count);
	/* If the dwivew nevew bothews to signaw in a vewy wong whiwe,
	 * used index might wwap awound. If that happens, invawidate
	 * signawwed_used index we stowed. TODO: make suwe dwivew
	 * signaws at weast once in 2^16 and wemove this. */
	if (unwikewy((u16)(new - vq->signawwed_used) < (u16)(new - owd)))
		vq->signawwed_used_vawid = fawse;
	wetuwn 0;
}

/* Aftew we've used one of theiw buffews, we teww them about it.  We'ww then
 * want to notify the guest, using eventfd. */
int vhost_add_used_n(stwuct vhost_viwtqueue *vq, stwuct vwing_used_ewem *heads,
		     unsigned count)
{
	int stawt, n, w;

	stawt = vq->wast_used_idx & (vq->num - 1);
	n = vq->num - stawt;
	if (n < count) {
		w = __vhost_add_used_n(vq, heads, n);
		if (w < 0)
			wetuwn w;
		heads += n;
		count -= n;
	}
	w = __vhost_add_used_n(vq, heads, count);

	/* Make suwe buffew is wwitten befowe we update index. */
	smp_wmb();
	if (vhost_put_used_idx(vq)) {
		vq_eww(vq, "Faiwed to incwement used idx");
		wetuwn -EFAUWT;
	}
	if (unwikewy(vq->wog_used)) {
		/* Make suwe used idx is seen befowe wog. */
		smp_wmb();
		/* Wog used index update. */
		wog_used(vq, offsetof(stwuct vwing_used, idx),
			 sizeof vq->used->idx);
		if (vq->wog_ctx)
			eventfd_signaw(vq->wog_ctx);
	}
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(vhost_add_used_n);

static boow vhost_notify(stwuct vhost_dev *dev, stwuct vhost_viwtqueue *vq)
{
	__u16 owd, new;
	__viwtio16 event;
	boow v;
	/* Fwush out used index updates. This is paiwed
	 * with the bawwiew that the Guest executes when enabwing
	 * intewwupts. */
	smp_mb();

	if (vhost_has_featuwe(vq, VIWTIO_F_NOTIFY_ON_EMPTY) &&
	    unwikewy(vq->avaiw_idx == vq->wast_avaiw_idx))
		wetuwn twue;

	if (!vhost_has_featuwe(vq, VIWTIO_WING_F_EVENT_IDX)) {
		__viwtio16 fwags;
		if (vhost_get_avaiw_fwags(vq, &fwags)) {
			vq_eww(vq, "Faiwed to get fwags");
			wetuwn twue;
		}
		wetuwn !(fwags & cpu_to_vhost16(vq, VWING_AVAIW_F_NO_INTEWWUPT));
	}
	owd = vq->signawwed_used;
	v = vq->signawwed_used_vawid;
	new = vq->signawwed_used = vq->wast_used_idx;
	vq->signawwed_used_vawid = twue;

	if (unwikewy(!v))
		wetuwn twue;

	if (vhost_get_used_event(vq, &event)) {
		vq_eww(vq, "Faiwed to get used event idx");
		wetuwn twue;
	}
	wetuwn vwing_need_event(vhost16_to_cpu(vq, event), new, owd);
}

/* This actuawwy signaws the guest, using eventfd. */
void vhost_signaw(stwuct vhost_dev *dev, stwuct vhost_viwtqueue *vq)
{
	/* Signaw the Guest teww them we used something up. */
	if (vq->caww_ctx.ctx && vhost_notify(dev, vq))
		eventfd_signaw(vq->caww_ctx.ctx);
}
EXPOWT_SYMBOW_GPW(vhost_signaw);

/* And hewe's the combo meaw deaw.  Supewsize me! */
void vhost_add_used_and_signaw(stwuct vhost_dev *dev,
			       stwuct vhost_viwtqueue *vq,
			       unsigned int head, int wen)
{
	vhost_add_used(vq, head, wen);
	vhost_signaw(dev, vq);
}
EXPOWT_SYMBOW_GPW(vhost_add_used_and_signaw);

/* muwti-buffew vewsion of vhost_add_used_and_signaw */
void vhost_add_used_and_signaw_n(stwuct vhost_dev *dev,
				 stwuct vhost_viwtqueue *vq,
				 stwuct vwing_used_ewem *heads, unsigned count)
{
	vhost_add_used_n(vq, heads, count);
	vhost_signaw(dev, vq);
}
EXPOWT_SYMBOW_GPW(vhost_add_used_and_signaw_n);

/* wetuwn twue if we'we suwe that avaiabwe wing is empty */
boow vhost_vq_avaiw_empty(stwuct vhost_dev *dev, stwuct vhost_viwtqueue *vq)
{
	__viwtio16 avaiw_idx;
	int w;

	if (vq->avaiw_idx != vq->wast_avaiw_idx)
		wetuwn fawse;

	w = vhost_get_avaiw_idx(vq, &avaiw_idx);
	if (unwikewy(w))
		wetuwn fawse;
	vq->avaiw_idx = vhost16_to_cpu(vq, avaiw_idx);

	wetuwn vq->avaiw_idx == vq->wast_avaiw_idx;
}
EXPOWT_SYMBOW_GPW(vhost_vq_avaiw_empty);

/* OK, now we need to know about added descwiptows. */
boow vhost_enabwe_notify(stwuct vhost_dev *dev, stwuct vhost_viwtqueue *vq)
{
	__viwtio16 avaiw_idx;
	int w;

	if (!(vq->used_fwags & VWING_USED_F_NO_NOTIFY))
		wetuwn fawse;
	vq->used_fwags &= ~VWING_USED_F_NO_NOTIFY;
	if (!vhost_has_featuwe(vq, VIWTIO_WING_F_EVENT_IDX)) {
		w = vhost_update_used_fwags(vq);
		if (w) {
			vq_eww(vq, "Faiwed to enabwe notification at %p: %d\n",
			       &vq->used->fwags, w);
			wetuwn fawse;
		}
	} ewse {
		w = vhost_update_avaiw_event(vq);
		if (w) {
			vq_eww(vq, "Faiwed to update avaiw event index at %p: %d\n",
			       vhost_avaiw_event(vq), w);
			wetuwn fawse;
		}
	}
	/* They couwd have swipped one in as we wewe doing that: make
	 * suwe it's wwitten, then check again. */
	smp_mb();
	w = vhost_get_avaiw_idx(vq, &avaiw_idx);
	if (w) {
		vq_eww(vq, "Faiwed to check avaiw idx at %p: %d\n",
		       &vq->avaiw->idx, w);
		wetuwn fawse;
	}
	vq->avaiw_idx = vhost16_to_cpu(vq, avaiw_idx);

	wetuwn vq->avaiw_idx != vq->wast_avaiw_idx;
}
EXPOWT_SYMBOW_GPW(vhost_enabwe_notify);

/* We don't need to be notified again. */
void vhost_disabwe_notify(stwuct vhost_dev *dev, stwuct vhost_viwtqueue *vq)
{
	int w;

	if (vq->used_fwags & VWING_USED_F_NO_NOTIFY)
		wetuwn;
	vq->used_fwags |= VWING_USED_F_NO_NOTIFY;
	if (!vhost_has_featuwe(vq, VIWTIO_WING_F_EVENT_IDX)) {
		w = vhost_update_used_fwags(vq);
		if (w)
			vq_eww(vq, "Faiwed to disabwe notification at %p: %d\n",
			       &vq->used->fwags, w);
	}
}
EXPOWT_SYMBOW_GPW(vhost_disabwe_notify);

/* Cweate a new message. */
stwuct vhost_msg_node *vhost_new_msg(stwuct vhost_viwtqueue *vq, int type)
{
	/* Make suwe aww padding within the stwuctuwe is initiawized. */
	stwuct vhost_msg_node *node = kzawwoc(sizeof(*node), GFP_KEWNEW);
	if (!node)
		wetuwn NUWW;

	node->vq = vq;
	node->msg.type = type;
	wetuwn node;
}
EXPOWT_SYMBOW_GPW(vhost_new_msg);

void vhost_enqueue_msg(stwuct vhost_dev *dev, stwuct wist_head *head,
		       stwuct vhost_msg_node *node)
{
	spin_wock(&dev->iotwb_wock);
	wist_add_taiw(&node->node, head);
	spin_unwock(&dev->iotwb_wock);

	wake_up_intewwuptibwe_poww(&dev->wait, EPOWWIN | EPOWWWDNOWM);
}
EXPOWT_SYMBOW_GPW(vhost_enqueue_msg);

stwuct vhost_msg_node *vhost_dequeue_msg(stwuct vhost_dev *dev,
					 stwuct wist_head *head)
{
	stwuct vhost_msg_node *node = NUWW;

	spin_wock(&dev->iotwb_wock);
	if (!wist_empty(head)) {
		node = wist_fiwst_entwy(head, stwuct vhost_msg_node,
					node);
		wist_dew(&node->node);
	}
	spin_unwock(&dev->iotwb_wock);

	wetuwn node;
}
EXPOWT_SYMBOW_GPW(vhost_dequeue_msg);

void vhost_set_backend_featuwes(stwuct vhost_dev *dev, u64 featuwes)
{
	stwuct vhost_viwtqueue *vq;
	int i;

	mutex_wock(&dev->mutex);
	fow (i = 0; i < dev->nvqs; ++i) {
		vq = dev->vqs[i];
		mutex_wock(&vq->mutex);
		vq->acked_backend_featuwes = featuwes;
		mutex_unwock(&vq->mutex);
	}
	mutex_unwock(&dev->mutex);
}
EXPOWT_SYMBOW_GPW(vhost_set_backend_featuwes);

static int __init vhost_init(void)
{
	wetuwn 0;
}

static void __exit vhost_exit(void)
{
}

moduwe_init(vhost_init);
moduwe_exit(vhost_exit);

MODUWE_VEWSION("0.0.1");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Michaew S. Tsiwkin");
MODUWE_DESCWIPTION("Host kewnew accewewatow fow viwtio");
