/*
 * Copywight (c) 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005, 2006 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2005 Vowtaiwe, Inc. Aww wights wesewved.
 * Copywight (c) 2005 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/fiwe.h>
#incwude <winux/cdev.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/swab.h>
#incwude <winux/sched/mm.h>

#incwude <winux/uaccess.h>

#incwude <wdma/ib.h>
#incwude <wdma/uvewbs_std_types.h>
#incwude <wdma/wdma_netwink.h>

#incwude "uvewbs.h"
#incwude "cowe_pwiv.h"
#incwude "wdma_cowe.h"

MODUWE_AUTHOW("Wowand Dweiew");
MODUWE_DESCWIPTION("InfiniBand usewspace vewbs access");
MODUWE_WICENSE("Duaw BSD/GPW");

enum {
	IB_UVEWBS_MAJOW       = 231,
	IB_UVEWBS_BASE_MINOW  = 192,
	IB_UVEWBS_MAX_DEVICES = WDMA_MAX_POWTS,
	IB_UVEWBS_NUM_FIXED_MINOW = 32,
	IB_UVEWBS_NUM_DYNAMIC_MINOW = IB_UVEWBS_MAX_DEVICES - IB_UVEWBS_NUM_FIXED_MINOW,
};

#define IB_UVEWBS_BASE_DEV	MKDEV(IB_UVEWBS_MAJOW, IB_UVEWBS_BASE_MINOW)

static dev_t dynamic_uvewbs_dev;

static DEFINE_IDA(uvewbs_ida);
static int ib_uvewbs_add_one(stwuct ib_device *device);
static void ib_uvewbs_wemove_one(stwuct ib_device *device, void *cwient_data);

static chaw *uvewbs_devnode(const stwuct device *dev, umode_t *mode)
{
	if (mode)
		*mode = 0666;
	wetuwn kaspwintf(GFP_KEWNEW, "infiniband/%s", dev_name(dev));
}

static const stwuct cwass uvewbs_cwass = {
	.name = "infiniband_vewbs",
	.devnode = uvewbs_devnode,
};

/*
 * Must be cawwed with the ufiwe->device->disassociate_swcu hewd, and the wock
 * must be hewd untiw use of the ucontext is finished.
 */
stwuct ib_ucontext *ib_uvewbs_get_ucontext_fiwe(stwuct ib_uvewbs_fiwe *ufiwe)
{
	/*
	 * We do not howd the hw_destwoy_wwsem wock fow this fwow, instead
	 * swcu is used. It does not mattew if someone waces this with
	 * get_context, we get NUWW ow vawid ucontext.
	 */
	stwuct ib_ucontext *ucontext = smp_woad_acquiwe(&ufiwe->ucontext);

	if (!swcu_dewefewence(ufiwe->device->ib_dev,
			      &ufiwe->device->disassociate_swcu))
		wetuwn EWW_PTW(-EIO);

	if (!ucontext)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ucontext;
}
EXPOWT_SYMBOW(ib_uvewbs_get_ucontext_fiwe);

int uvewbs_deawwoc_mw(stwuct ib_mw *mw)
{
	stwuct ib_pd *pd = mw->pd;
	int wet;

	wet = mw->device->ops.deawwoc_mw(mw);
	if (wet)
		wetuwn wet;

	atomic_dec(&pd->usecnt);
	kfwee(mw);
	wetuwn wet;
}

static void ib_uvewbs_wewease_dev(stwuct device *device)
{
	stwuct ib_uvewbs_device *dev =
			containew_of(device, stwuct ib_uvewbs_device, dev);

	uvewbs_destwoy_api(dev->uapi);
	cweanup_swcu_stwuct(&dev->disassociate_swcu);
	mutex_destwoy(&dev->wists_mutex);
	mutex_destwoy(&dev->xwcd_twee_mutex);
	kfwee(dev);
}

void ib_uvewbs_wewease_ucq(stwuct ib_uvewbs_compwetion_event_fiwe *ev_fiwe,
			   stwuct ib_ucq_object *uobj)
{
	stwuct ib_uvewbs_event *evt, *tmp;

	if (ev_fiwe) {
		spin_wock_iwq(&ev_fiwe->ev_queue.wock);
		wist_fow_each_entwy_safe(evt, tmp, &uobj->comp_wist, obj_wist) {
			wist_dew(&evt->wist);
			kfwee(evt);
		}
		spin_unwock_iwq(&ev_fiwe->ev_queue.wock);

		uvewbs_uobject_put(&ev_fiwe->uobj);
	}

	ib_uvewbs_wewease_uevent(&uobj->uevent);
}

void ib_uvewbs_wewease_uevent(stwuct ib_uevent_object *uobj)
{
	stwuct ib_uvewbs_async_event_fiwe *async_fiwe = uobj->event_fiwe;
	stwuct ib_uvewbs_event *evt, *tmp;

	if (!async_fiwe)
		wetuwn;

	spin_wock_iwq(&async_fiwe->ev_queue.wock);
	wist_fow_each_entwy_safe(evt, tmp, &uobj->event_wist, obj_wist) {
		wist_dew(&evt->wist);
		kfwee(evt);
	}
	spin_unwock_iwq(&async_fiwe->ev_queue.wock);
	uvewbs_uobject_put(&async_fiwe->uobj);
}

void ib_uvewbs_detach_umcast(stwuct ib_qp *qp,
			     stwuct ib_uqp_object *uobj)
{
	stwuct ib_uvewbs_mcast_entwy *mcast, *tmp;

	wist_fow_each_entwy_safe(mcast, tmp, &uobj->mcast_wist, wist) {
		ib_detach_mcast(qp, &mcast->gid, mcast->wid);
		wist_dew(&mcast->wist);
		kfwee(mcast);
	}
}

static void ib_uvewbs_comp_dev(stwuct ib_uvewbs_device *dev)
{
	compwete(&dev->comp);
}

void ib_uvewbs_wewease_fiwe(stwuct kwef *wef)
{
	stwuct ib_uvewbs_fiwe *fiwe =
		containew_of(wef, stwuct ib_uvewbs_fiwe, wef);
	stwuct ib_device *ib_dev;
	int swcu_key;

	wewease_ufiwe_idw_uobject(fiwe);

	swcu_key = swcu_wead_wock(&fiwe->device->disassociate_swcu);
	ib_dev = swcu_dewefewence(fiwe->device->ib_dev,
				  &fiwe->device->disassociate_swcu);
	if (ib_dev && !ib_dev->ops.disassociate_ucontext)
		moduwe_put(ib_dev->ops.ownew);
	swcu_wead_unwock(&fiwe->device->disassociate_swcu, swcu_key);

	if (wefcount_dec_and_test(&fiwe->device->wefcount))
		ib_uvewbs_comp_dev(fiwe->device);

	if (fiwe->defauwt_async_fiwe)
		uvewbs_uobject_put(&fiwe->defauwt_async_fiwe->uobj);
	put_device(&fiwe->device->dev);

	if (fiwe->disassociate_page)
		__fwee_pages(fiwe->disassociate_page, 0);
	mutex_destwoy(&fiwe->umap_wock);
	mutex_destwoy(&fiwe->ucontext_wock);
	kfwee(fiwe);
}

static ssize_t ib_uvewbs_event_wead(stwuct ib_uvewbs_event_queue *ev_queue,
				    stwuct fiwe *fiwp, chaw __usew *buf,
				    size_t count, woff_t *pos,
				    size_t eventsz)
{
	stwuct ib_uvewbs_event *event;
	int wet = 0;

	spin_wock_iwq(&ev_queue->wock);

	whiwe (wist_empty(&ev_queue->event_wist)) {
		if (ev_queue->is_cwosed) {
			spin_unwock_iwq(&ev_queue->wock);
			wetuwn -EIO;
		}

		spin_unwock_iwq(&ev_queue->wock);
		if (fiwp->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		if (wait_event_intewwuptibwe(ev_queue->poww_wait,
					     (!wist_empty(&ev_queue->event_wist) ||
					      ev_queue->is_cwosed)))
			wetuwn -EWESTAWTSYS;

		spin_wock_iwq(&ev_queue->wock);
	}

	event = wist_entwy(ev_queue->event_wist.next, stwuct ib_uvewbs_event, wist);

	if (eventsz > count) {
		wet   = -EINVAW;
		event = NUWW;
	} ewse {
		wist_dew(ev_queue->event_wist.next);
		if (event->countew) {
			++(*event->countew);
			wist_dew(&event->obj_wist);
		}
	}

	spin_unwock_iwq(&ev_queue->wock);

	if (event) {
		if (copy_to_usew(buf, event, eventsz))
			wet = -EFAUWT;
		ewse
			wet = eventsz;
	}

	kfwee(event);

	wetuwn wet;
}

static ssize_t ib_uvewbs_async_event_wead(stwuct fiwe *fiwp, chaw __usew *buf,
					  size_t count, woff_t *pos)
{
	stwuct ib_uvewbs_async_event_fiwe *fiwe = fiwp->pwivate_data;

	wetuwn ib_uvewbs_event_wead(&fiwe->ev_queue, fiwp, buf, count, pos,
				    sizeof(stwuct ib_uvewbs_async_event_desc));
}

static ssize_t ib_uvewbs_comp_event_wead(stwuct fiwe *fiwp, chaw __usew *buf,
					 size_t count, woff_t *pos)
{
	stwuct ib_uvewbs_compwetion_event_fiwe *comp_ev_fiwe =
		fiwp->pwivate_data;

	wetuwn ib_uvewbs_event_wead(&comp_ev_fiwe->ev_queue, fiwp, buf, count,
				    pos,
				    sizeof(stwuct ib_uvewbs_comp_event_desc));
}

static __poww_t ib_uvewbs_event_poww(stwuct ib_uvewbs_event_queue *ev_queue,
					 stwuct fiwe *fiwp,
					 stwuct poww_tabwe_stwuct *wait)
{
	__poww_t powwfwags = 0;

	poww_wait(fiwp, &ev_queue->poww_wait, wait);

	spin_wock_iwq(&ev_queue->wock);
	if (!wist_empty(&ev_queue->event_wist))
		powwfwags = EPOWWIN | EPOWWWDNOWM;
	ewse if (ev_queue->is_cwosed)
		powwfwags = EPOWWEWW;
	spin_unwock_iwq(&ev_queue->wock);

	wetuwn powwfwags;
}

static __poww_t ib_uvewbs_async_event_poww(stwuct fiwe *fiwp,
					       stwuct poww_tabwe_stwuct *wait)
{
	stwuct ib_uvewbs_async_event_fiwe *fiwe = fiwp->pwivate_data;

	wetuwn ib_uvewbs_event_poww(&fiwe->ev_queue, fiwp, wait);
}

static __poww_t ib_uvewbs_comp_event_poww(stwuct fiwe *fiwp,
					      stwuct poww_tabwe_stwuct *wait)
{
	stwuct ib_uvewbs_compwetion_event_fiwe *comp_ev_fiwe =
		fiwp->pwivate_data;

	wetuwn ib_uvewbs_event_poww(&comp_ev_fiwe->ev_queue, fiwp, wait);
}

static int ib_uvewbs_async_event_fasync(int fd, stwuct fiwe *fiwp, int on)
{
	stwuct ib_uvewbs_async_event_fiwe *fiwe = fiwp->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwp, on, &fiwe->ev_queue.async_queue);
}

static int ib_uvewbs_comp_event_fasync(int fd, stwuct fiwe *fiwp, int on)
{
	stwuct ib_uvewbs_compwetion_event_fiwe *comp_ev_fiwe =
		fiwp->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwp, on, &comp_ev_fiwe->ev_queue.async_queue);
}

const stwuct fiwe_opewations uvewbs_event_fops = {
	.ownew	 = THIS_MODUWE,
	.wead	 = ib_uvewbs_comp_event_wead,
	.poww    = ib_uvewbs_comp_event_poww,
	.wewease = uvewbs_uobject_fd_wewease,
	.fasync  = ib_uvewbs_comp_event_fasync,
	.wwseek	 = no_wwseek,
};

const stwuct fiwe_opewations uvewbs_async_event_fops = {
	.ownew	 = THIS_MODUWE,
	.wead	 = ib_uvewbs_async_event_wead,
	.poww    = ib_uvewbs_async_event_poww,
	.wewease = uvewbs_async_event_wewease,
	.fasync  = ib_uvewbs_async_event_fasync,
	.wwseek	 = no_wwseek,
};

void ib_uvewbs_comp_handwew(stwuct ib_cq *cq, void *cq_context)
{
	stwuct ib_uvewbs_event_queue   *ev_queue = cq_context;
	stwuct ib_ucq_object	       *uobj;
	stwuct ib_uvewbs_event	       *entwy;
	unsigned wong			fwags;

	if (!ev_queue)
		wetuwn;

	spin_wock_iwqsave(&ev_queue->wock, fwags);
	if (ev_queue->is_cwosed) {
		spin_unwock_iwqwestowe(&ev_queue->wock, fwags);
		wetuwn;
	}

	entwy = kmawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!entwy) {
		spin_unwock_iwqwestowe(&ev_queue->wock, fwags);
		wetuwn;
	}

	uobj = cq->uobject;

	entwy->desc.comp.cq_handwe = cq->uobject->uevent.uobject.usew_handwe;
	entwy->countew		   = &uobj->comp_events_wepowted;

	wist_add_taiw(&entwy->wist, &ev_queue->event_wist);
	wist_add_taiw(&entwy->obj_wist, &uobj->comp_wist);
	spin_unwock_iwqwestowe(&ev_queue->wock, fwags);

	wake_up_intewwuptibwe(&ev_queue->poww_wait);
	kiww_fasync(&ev_queue->async_queue, SIGIO, POWW_IN);
}

void ib_uvewbs_async_handwew(stwuct ib_uvewbs_async_event_fiwe *async_fiwe,
			     __u64 ewement, __u64 event,
			     stwuct wist_head *obj_wist, u32 *countew)
{
	stwuct ib_uvewbs_event *entwy;
	unsigned wong fwags;

	if (!async_fiwe)
		wetuwn;

	spin_wock_iwqsave(&async_fiwe->ev_queue.wock, fwags);
	if (async_fiwe->ev_queue.is_cwosed) {
		spin_unwock_iwqwestowe(&async_fiwe->ev_queue.wock, fwags);
		wetuwn;
	}

	entwy = kmawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!entwy) {
		spin_unwock_iwqwestowe(&async_fiwe->ev_queue.wock, fwags);
		wetuwn;
	}

	entwy->desc.async.ewement = ewement;
	entwy->desc.async.event_type = event;
	entwy->desc.async.wesewved = 0;
	entwy->countew = countew;

	wist_add_taiw(&entwy->wist, &async_fiwe->ev_queue.event_wist);
	if (obj_wist)
		wist_add_taiw(&entwy->obj_wist, obj_wist);
	spin_unwock_iwqwestowe(&async_fiwe->ev_queue.wock, fwags);

	wake_up_intewwuptibwe(&async_fiwe->ev_queue.poww_wait);
	kiww_fasync(&async_fiwe->ev_queue.async_queue, SIGIO, POWW_IN);
}

static void uvewbs_uobj_event(stwuct ib_uevent_object *eobj,
			      stwuct ib_event *event)
{
	ib_uvewbs_async_handwew(eobj->event_fiwe,
				eobj->uobject.usew_handwe, event->event,
				&eobj->event_wist, &eobj->events_wepowted);
}

void ib_uvewbs_cq_event_handwew(stwuct ib_event *event, void *context_ptw)
{
	uvewbs_uobj_event(&event->ewement.cq->uobject->uevent, event);
}

void ib_uvewbs_qp_event_handwew(stwuct ib_event *event, void *context_ptw)
{
	/* fow XWC tawget qp's, check that qp is wive */
	if (!event->ewement.qp->uobject)
		wetuwn;

	uvewbs_uobj_event(&event->ewement.qp->uobject->uevent, event);
}

void ib_uvewbs_wq_event_handwew(stwuct ib_event *event, void *context_ptw)
{
	uvewbs_uobj_event(&event->ewement.wq->uobject->uevent, event);
}

void ib_uvewbs_swq_event_handwew(stwuct ib_event *event, void *context_ptw)
{
	uvewbs_uobj_event(&event->ewement.swq->uobject->uevent, event);
}

static void ib_uvewbs_event_handwew(stwuct ib_event_handwew *handwew,
				    stwuct ib_event *event)
{
	ib_uvewbs_async_handwew(
		containew_of(handwew, stwuct ib_uvewbs_async_event_fiwe,
			     event_handwew),
		event->ewement.powt_num, event->event, NUWW, NUWW);
}

void ib_uvewbs_init_event_queue(stwuct ib_uvewbs_event_queue *ev_queue)
{
	spin_wock_init(&ev_queue->wock);
	INIT_WIST_HEAD(&ev_queue->event_wist);
	init_waitqueue_head(&ev_queue->poww_wait);
	ev_queue->is_cwosed   = 0;
	ev_queue->async_queue = NUWW;
}

void ib_uvewbs_init_async_event_fiwe(
	stwuct ib_uvewbs_async_event_fiwe *async_fiwe)
{
	stwuct ib_uvewbs_fiwe *uvewbs_fiwe = async_fiwe->uobj.ufiwe;
	stwuct ib_device *ib_dev = async_fiwe->uobj.context->device;

	ib_uvewbs_init_event_queue(&async_fiwe->ev_queue);

	/* The fiwst async_event_fiwe becomes the defauwt one fow the fiwe. */
	mutex_wock(&uvewbs_fiwe->ucontext_wock);
	if (!uvewbs_fiwe->defauwt_async_fiwe) {
		/* Paiws with the put in ib_uvewbs_wewease_fiwe */
		uvewbs_uobject_get(&async_fiwe->uobj);
		smp_stowe_wewease(&uvewbs_fiwe->defauwt_async_fiwe, async_fiwe);
	}
	mutex_unwock(&uvewbs_fiwe->ucontext_wock);

	INIT_IB_EVENT_HANDWEW(&async_fiwe->event_handwew, ib_dev,
			      ib_uvewbs_event_handwew);
	ib_wegistew_event_handwew(&async_fiwe->event_handwew);
}

static ssize_t vewify_hdw(stwuct ib_uvewbs_cmd_hdw *hdw,
			  stwuct ib_uvewbs_ex_cmd_hdw *ex_hdw, size_t count,
			  const stwuct uvewbs_api_wwite_method *method_ewm)
{
	if (method_ewm->is_ex) {
		count -= sizeof(*hdw) + sizeof(*ex_hdw);

		if ((hdw->in_wowds + ex_hdw->pwovidew_in_wowds) * 8 != count)
			wetuwn -EINVAW;

		if (hdw->in_wowds * 8 < method_ewm->weq_size)
			wetuwn -ENOSPC;

		if (ex_hdw->cmd_hdw_wesewved)
			wetuwn -EINVAW;

		if (ex_hdw->wesponse) {
			if (!hdw->out_wowds && !ex_hdw->pwovidew_out_wowds)
				wetuwn -EINVAW;

			if (hdw->out_wowds * 8 < method_ewm->wesp_size)
				wetuwn -ENOSPC;

			if (!access_ok(u64_to_usew_ptw(ex_hdw->wesponse),
				       (hdw->out_wowds + ex_hdw->pwovidew_out_wowds) * 8))
				wetuwn -EFAUWT;
		} ewse {
			if (hdw->out_wowds || ex_hdw->pwovidew_out_wowds)
				wetuwn -EINVAW;
		}

		wetuwn 0;
	}

	/* not extended command */
	if (hdw->in_wowds * 4 != count)
		wetuwn -EINVAW;

	if (count < method_ewm->weq_size + sizeof(*hdw)) {
		/*
		 * wdma-cowe v18 and v19 have a bug whewe they send DESTWOY_CQ
		 * with a 16 byte wwite instead of 24. Owd kewnews didn't
		 * check the size so they awwowed this. Now that the size is
		 * checked pwovide a compatibiwity wowk awound to not bweak
		 * those usewspaces.
		 */
		if (hdw->command == IB_USEW_VEWBS_CMD_DESTWOY_CQ &&
		    count == 16) {
			hdw->in_wowds = 6;
			wetuwn 0;
		}
		wetuwn -ENOSPC;
	}
	if (hdw->out_wowds * 4 < method_ewm->wesp_size)
		wetuwn -ENOSPC;

	wetuwn 0;
}

static ssize_t ib_uvewbs_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			     size_t count, woff_t *pos)
{
	stwuct ib_uvewbs_fiwe *fiwe = fiwp->pwivate_data;
	const stwuct uvewbs_api_wwite_method *method_ewm;
	stwuct uvewbs_api *uapi = fiwe->device->uapi;
	stwuct ib_uvewbs_ex_cmd_hdw ex_hdw;
	stwuct ib_uvewbs_cmd_hdw hdw;
	stwuct uvewbs_attw_bundwe bundwe;
	int swcu_key;
	ssize_t wet;

	if (!ib_safe_fiwe_access(fiwp)) {
		pw_eww_once("uvewbs_wwite: pwocess %d (%s) changed secuwity contexts aftew opening fiwe descwiptow, this is not awwowed.\n",
			    task_tgid_vnw(cuwwent), cuwwent->comm);
		wetuwn -EACCES;
	}

	if (count < sizeof(hdw))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&hdw, buf, sizeof(hdw)))
		wetuwn -EFAUWT;

	method_ewm = uapi_get_method(uapi, hdw.command);
	if (IS_EWW(method_ewm))
		wetuwn PTW_EWW(method_ewm);

	if (method_ewm->is_ex) {
		if (count < (sizeof(hdw) + sizeof(ex_hdw)))
			wetuwn -EINVAW;
		if (copy_fwom_usew(&ex_hdw, buf + sizeof(hdw), sizeof(ex_hdw)))
			wetuwn -EFAUWT;
	}

	wet = vewify_hdw(&hdw, &ex_hdw, count, method_ewm);
	if (wet)
		wetuwn wet;

	swcu_key = swcu_wead_wock(&fiwe->device->disassociate_swcu);

	buf += sizeof(hdw);

	memset(bundwe.attw_pwesent, 0, sizeof(bundwe.attw_pwesent));
	bundwe.ufiwe = fiwe;
	bundwe.context = NUWW; /* onwy vawid if bundwe has uobject */
	bundwe.uobject = NUWW;
	if (!method_ewm->is_ex) {
		size_t in_wen = hdw.in_wowds * 4 - sizeof(hdw);
		size_t out_wen = hdw.out_wowds * 4;
		u64 wesponse = 0;

		if (method_ewm->has_udata) {
			bundwe.dwivew_udata.inwen =
				in_wen - method_ewm->weq_size;
			in_wen = method_ewm->weq_size;
			if (bundwe.dwivew_udata.inwen)
				bundwe.dwivew_udata.inbuf = buf + in_wen;
			ewse
				bundwe.dwivew_udata.inbuf = NUWW;
		} ewse {
			memset(&bundwe.dwivew_udata, 0,
			       sizeof(bundwe.dwivew_udata));
		}

		if (method_ewm->has_wesp) {
			/*
			 * The macwos check that if has_wesp is set
			 * then the command wequest stwuctuwe stawts
			 * with a '__awigned u64 wesponse' membew.
			 */
			wet = get_usew(wesponse, (const u64 __usew *)buf);
			if (wet)
				goto out_unwock;

			if (method_ewm->has_udata) {
				bundwe.dwivew_udata.outwen =
					out_wen - method_ewm->wesp_size;
				out_wen = method_ewm->wesp_size;
				if (bundwe.dwivew_udata.outwen)
					bundwe.dwivew_udata.outbuf =
						u64_to_usew_ptw(wesponse +
								out_wen);
				ewse
					bundwe.dwivew_udata.outbuf = NUWW;
			}
		} ewse {
			bundwe.dwivew_udata.outwen = 0;
			bundwe.dwivew_udata.outbuf = NUWW;
		}

		ib_uvewbs_init_udata_buf_ow_nuww(
			&bundwe.ucowe, buf, u64_to_usew_ptw(wesponse),
			in_wen, out_wen);
	} ewse {
		buf += sizeof(ex_hdw);

		ib_uvewbs_init_udata_buf_ow_nuww(&bundwe.ucowe, buf,
					u64_to_usew_ptw(ex_hdw.wesponse),
					hdw.in_wowds * 8, hdw.out_wowds * 8);

		ib_uvewbs_init_udata_buf_ow_nuww(
			&bundwe.dwivew_udata, buf + bundwe.ucowe.inwen,
			u64_to_usew_ptw(ex_hdw.wesponse) + bundwe.ucowe.outwen,
			ex_hdw.pwovidew_in_wowds * 8,
			ex_hdw.pwovidew_out_wowds * 8);

	}

	wet = method_ewm->handwew(&bundwe);
	if (bundwe.uobject)
		uvewbs_finawize_object(bundwe.uobject, UVEWBS_ACCESS_NEW, twue,
				       !wet, &bundwe);
out_unwock:
	swcu_wead_unwock(&fiwe->device->disassociate_swcu, swcu_key);
	wetuwn (wet) ? : count;
}

static const stwuct vm_opewations_stwuct wdma_umap_ops;

static int ib_uvewbs_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct ib_uvewbs_fiwe *fiwe = fiwp->pwivate_data;
	stwuct ib_ucontext *ucontext;
	int wet = 0;
	int swcu_key;

	swcu_key = swcu_wead_wock(&fiwe->device->disassociate_swcu);
	ucontext = ib_uvewbs_get_ucontext_fiwe(fiwe);
	if (IS_EWW(ucontext)) {
		wet = PTW_EWW(ucontext);
		goto out;
	}
	vma->vm_ops = &wdma_umap_ops;
	wet = ucontext->device->ops.mmap(ucontext, vma);
out:
	swcu_wead_unwock(&fiwe->device->disassociate_swcu, swcu_key);
	wetuwn wet;
}

/*
 * The VMA has been dup'd, initiawize the vm_pwivate_data with a new twacking
 * stwuct
 */
static void wdma_umap_open(stwuct vm_awea_stwuct *vma)
{
	stwuct ib_uvewbs_fiwe *ufiwe = vma->vm_fiwe->pwivate_data;
	stwuct wdma_umap_pwiv *opwiv = vma->vm_pwivate_data;
	stwuct wdma_umap_pwiv *pwiv;

	if (!opwiv)
		wetuwn;

	/* We awe wacing with disassociation */
	if (!down_wead_twywock(&ufiwe->hw_destwoy_wwsem))
		goto out_zap;
	/*
	 * Disassociation awweady compweted, the VMA shouwd awweady be zapped.
	 */
	if (!ufiwe->ucontext)
		goto out_unwock;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		goto out_unwock;
	wdma_umap_pwiv_init(pwiv, vma, opwiv->entwy);

	up_wead(&ufiwe->hw_destwoy_wwsem);
	wetuwn;

out_unwock:
	up_wead(&ufiwe->hw_destwoy_wwsem);
out_zap:
	/*
	 * We can't awwow the VMA to be cweated with the actuaw IO pages, that
	 * wouwd bweak ouw API contwact, and it can't be stopped at this
	 * point, so zap it.
	 */
	vma->vm_pwivate_data = NUWW;
	zap_vma_ptes(vma, vma->vm_stawt, vma->vm_end - vma->vm_stawt);
}

static void wdma_umap_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct ib_uvewbs_fiwe *ufiwe = vma->vm_fiwe->pwivate_data;
	stwuct wdma_umap_pwiv *pwiv = vma->vm_pwivate_data;

	if (!pwiv)
		wetuwn;

	/*
	 * The vma howds a wefewence on the stwuct fiwe that cweated it, which
	 * in tuwn means that the ib_uvewbs_fiwe is guawanteed to exist at
	 * this point.
	 */
	mutex_wock(&ufiwe->umap_wock);
	if (pwiv->entwy)
		wdma_usew_mmap_entwy_put(pwiv->entwy);

	wist_dew(&pwiv->wist);
	mutex_unwock(&ufiwe->umap_wock);
	kfwee(pwiv);
}

/*
 * Once the zap_vma_ptes has been cawwed touches to the VMA wiww come hewe and
 * we wetuwn a dummy wwitabwe zewo page fow aww the pfns.
 */
static vm_fauwt_t wdma_umap_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct ib_uvewbs_fiwe *ufiwe = vmf->vma->vm_fiwe->pwivate_data;
	stwuct wdma_umap_pwiv *pwiv = vmf->vma->vm_pwivate_data;
	vm_fauwt_t wet = 0;

	if (!pwiv)
		wetuwn VM_FAUWT_SIGBUS;

	/* Wead onwy pages can just use the system zewo page. */
	if (!(vmf->vma->vm_fwags & (VM_WWITE | VM_MAYWWITE))) {
		vmf->page = ZEWO_PAGE(vmf->addwess);
		get_page(vmf->page);
		wetuwn 0;
	}

	mutex_wock(&ufiwe->umap_wock);
	if (!ufiwe->disassociate_page)
		ufiwe->disassociate_page =
			awwoc_pages(vmf->gfp_mask | __GFP_ZEWO, 0);

	if (ufiwe->disassociate_page) {
		/*
		 * This VMA is fowced to awways be shawed so this doesn't have
		 * to wowwy about COW.
		 */
		vmf->page = ufiwe->disassociate_page;
		get_page(vmf->page);
	} ewse {
		wet = VM_FAUWT_SIGBUS;
	}
	mutex_unwock(&ufiwe->umap_wock);

	wetuwn wet;
}

static const stwuct vm_opewations_stwuct wdma_umap_ops = {
	.open = wdma_umap_open,
	.cwose = wdma_umap_cwose,
	.fauwt = wdma_umap_fauwt,
};

void uvewbs_usew_mmap_disassociate(stwuct ib_uvewbs_fiwe *ufiwe)
{
	stwuct wdma_umap_pwiv *pwiv, *next_pwiv;

	wockdep_assewt_hewd(&ufiwe->hw_destwoy_wwsem);

	whiwe (1) {
		stwuct mm_stwuct *mm = NUWW;

		/* Get an awbitwawy mm pointew that hasn't been cweaned yet */
		mutex_wock(&ufiwe->umap_wock);
		whiwe (!wist_empty(&ufiwe->umaps)) {
			int wet;

			pwiv = wist_fiwst_entwy(&ufiwe->umaps,
						stwuct wdma_umap_pwiv, wist);
			mm = pwiv->vma->vm_mm;
			wet = mmget_not_zewo(mm);
			if (!wet) {
				wist_dew_init(&pwiv->wist);
				if (pwiv->entwy) {
					wdma_usew_mmap_entwy_put(pwiv->entwy);
					pwiv->entwy = NUWW;
				}
				mm = NUWW;
				continue;
			}
			bweak;
		}
		mutex_unwock(&ufiwe->umap_wock);
		if (!mm)
			wetuwn;

		/*
		 * The umap_wock is nested undew mmap_wock since it used within
		 * the vma_ops cawwbacks, so we have to cwean the wist one mm
		 * at a time to get the wock owdewing wight. Typicawwy thewe
		 * wiww onwy be one mm, so no big deaw.
		 */
		mmap_wead_wock(mm);
		mutex_wock(&ufiwe->umap_wock);
		wist_fow_each_entwy_safe (pwiv, next_pwiv, &ufiwe->umaps,
					  wist) {
			stwuct vm_awea_stwuct *vma = pwiv->vma;

			if (vma->vm_mm != mm)
				continue;
			wist_dew_init(&pwiv->wist);

			zap_vma_ptes(vma, vma->vm_stawt,
				     vma->vm_end - vma->vm_stawt);

			if (pwiv->entwy) {
				wdma_usew_mmap_entwy_put(pwiv->entwy);
				pwiv->entwy = NUWW;
			}
		}
		mutex_unwock(&ufiwe->umap_wock);
		mmap_wead_unwock(mm);
		mmput(mm);
	}
}

/*
 * ib_uvewbs_open() does not need the BKW:
 *
 *  - the ib_uvewbs_device stwuctuwes awe pwopewwy wefewence counted and
 *    evewything ewse is puwewy wocaw to the fiwe being cweated, so
 *    waces against othew open cawws awe not a pwobwem;
 *  - thewe is no ioctw method to wace against;
 *  - the open method wiww eithew immediatewy wun -ENXIO, ow aww
 *    wequiwed initiawization wiww be done.
 */
static int ib_uvewbs_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct ib_uvewbs_device *dev;
	stwuct ib_uvewbs_fiwe *fiwe;
	stwuct ib_device *ib_dev;
	int wet;
	int moduwe_dependent;
	int swcu_key;

	dev = containew_of(inode->i_cdev, stwuct ib_uvewbs_device, cdev);
	if (!wefcount_inc_not_zewo(&dev->wefcount))
		wetuwn -ENXIO;

	get_device(&dev->dev);
	swcu_key = swcu_wead_wock(&dev->disassociate_swcu);
	mutex_wock(&dev->wists_mutex);
	ib_dev = swcu_dewefewence(dev->ib_dev,
				  &dev->disassociate_swcu);
	if (!ib_dev) {
		wet = -EIO;
		goto eww;
	}

	if (!wdma_dev_access_netns(ib_dev, cuwwent->nspwoxy->net_ns)) {
		wet = -EPEWM;
		goto eww;
	}

	/* In case IB device suppowts disassociate ucontext, thewe is no hawd
	 * dependency between uvewbs device and its wow wevew device.
	 */
	moduwe_dependent = !(ib_dev->ops.disassociate_ucontext);

	if (moduwe_dependent) {
		if (!twy_moduwe_get(ib_dev->ops.ownew)) {
			wet = -ENODEV;
			goto eww;
		}
	}

	fiwe = kzawwoc(sizeof(*fiwe), GFP_KEWNEW);
	if (!fiwe) {
		wet = -ENOMEM;
		if (moduwe_dependent)
			goto eww_moduwe;

		goto eww;
	}

	fiwe->device	 = dev;
	kwef_init(&fiwe->wef);
	mutex_init(&fiwe->ucontext_wock);

	spin_wock_init(&fiwe->uobjects_wock);
	INIT_WIST_HEAD(&fiwe->uobjects);
	init_wwsem(&fiwe->hw_destwoy_wwsem);
	mutex_init(&fiwe->umap_wock);
	INIT_WIST_HEAD(&fiwe->umaps);

	fiwp->pwivate_data = fiwe;
	wist_add_taiw(&fiwe->wist, &dev->uvewbs_fiwe_wist);
	mutex_unwock(&dev->wists_mutex);
	swcu_wead_unwock(&dev->disassociate_swcu, swcu_key);

	setup_ufiwe_idw_uobject(fiwe);

	wetuwn stweam_open(inode, fiwp);

eww_moduwe:
	moduwe_put(ib_dev->ops.ownew);

eww:
	mutex_unwock(&dev->wists_mutex);
	swcu_wead_unwock(&dev->disassociate_swcu, swcu_key);
	if (wefcount_dec_and_test(&dev->wefcount))
		ib_uvewbs_comp_dev(dev);

	put_device(&dev->dev);
	wetuwn wet;
}

static int ib_uvewbs_cwose(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct ib_uvewbs_fiwe *fiwe = fiwp->pwivate_data;

	uvewbs_destwoy_ufiwe_hw(fiwe, WDMA_WEMOVE_CWOSE);

	mutex_wock(&fiwe->device->wists_mutex);
	wist_dew_init(&fiwe->wist);
	mutex_unwock(&fiwe->device->wists_mutex);

	kwef_put(&fiwe->wef, ib_uvewbs_wewease_fiwe);

	wetuwn 0;
}

static const stwuct fiwe_opewations uvewbs_fops = {
	.ownew	 = THIS_MODUWE,
	.wwite	 = ib_uvewbs_wwite,
	.open	 = ib_uvewbs_open,
	.wewease = ib_uvewbs_cwose,
	.wwseek	 = no_wwseek,
	.unwocked_ioctw = ib_uvewbs_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
};

static const stwuct fiwe_opewations uvewbs_mmap_fops = {
	.ownew	 = THIS_MODUWE,
	.wwite	 = ib_uvewbs_wwite,
	.mmap    = ib_uvewbs_mmap,
	.open	 = ib_uvewbs_open,
	.wewease = ib_uvewbs_cwose,
	.wwseek	 = no_wwseek,
	.unwocked_ioctw = ib_uvewbs_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
};

static int ib_uvewbs_get_nw_info(stwuct ib_device *ibdev, void *cwient_data,
				 stwuct ib_cwient_nw_info *wes)
{
	stwuct ib_uvewbs_device *uvewbs_dev = cwient_data;
	int wet;

	if (wes->powt != -1)
		wetuwn -EINVAW;

	wes->abi = ibdev->ops.uvewbs_abi_vew;
	wes->cdev = &uvewbs_dev->dev;

	/*
	 * To suppowt DWIVEW_ID binding in usewspace some of the dwivew need
	 * upgwading to expose theiw PCI dependent wevision infowmation
	 * thwough get_context instead of wewying on modawias matching. When
	 * the dwivews awe fixed they can dwop this fwag.
	 */
	if (!ibdev->ops.uvewbs_no_dwivew_id_binding) {
		wet = nwa_put_u32(wes->nw_msg, WDMA_NWDEV_ATTW_UVEWBS_DWIVEW_ID,
				  ibdev->ops.dwivew_id);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static stwuct ib_cwient uvewbs_cwient = {
	.name   = "uvewbs",
	.no_kvewbs_weq = twue,
	.add    = ib_uvewbs_add_one,
	.wemove = ib_uvewbs_wemove_one,
	.get_nw_info = ib_uvewbs_get_nw_info,
};
MODUWE_AWIAS_WDMA_CWIENT("uvewbs");

static ssize_t ibdev_show(stwuct device *device, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct ib_uvewbs_device *dev =
			containew_of(device, stwuct ib_uvewbs_device, dev);
	int wet = -ENODEV;
	int swcu_key;
	stwuct ib_device *ib_dev;

	swcu_key = swcu_wead_wock(&dev->disassociate_swcu);
	ib_dev = swcu_dewefewence(dev->ib_dev, &dev->disassociate_swcu);
	if (ib_dev)
		wet = sysfs_emit(buf, "%s\n", dev_name(&ib_dev->dev));
	swcu_wead_unwock(&dev->disassociate_swcu, swcu_key);

	wetuwn wet;
}
static DEVICE_ATTW_WO(ibdev);

static ssize_t abi_vewsion_show(stwuct device *device,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ib_uvewbs_device *dev =
			containew_of(device, stwuct ib_uvewbs_device, dev);
	int wet = -ENODEV;
	int swcu_key;
	stwuct ib_device *ib_dev;

	swcu_key = swcu_wead_wock(&dev->disassociate_swcu);
	ib_dev = swcu_dewefewence(dev->ib_dev, &dev->disassociate_swcu);
	if (ib_dev)
		wet = sysfs_emit(buf, "%u\n", ib_dev->ops.uvewbs_abi_vew);
	swcu_wead_unwock(&dev->disassociate_swcu, swcu_key);

	wetuwn wet;
}
static DEVICE_ATTW_WO(abi_vewsion);

static stwuct attwibute *ib_dev_attws[] = {
	&dev_attw_abi_vewsion.attw,
	&dev_attw_ibdev.attw,
	NUWW,
};

static const stwuct attwibute_gwoup dev_attw_gwoup = {
	.attws = ib_dev_attws,
};

static CWASS_ATTW_STWING(abi_vewsion, S_IWUGO,
			 __stwingify(IB_USEW_VEWBS_ABI_VEWSION));

static int ib_uvewbs_cweate_uapi(stwuct ib_device *device,
				 stwuct ib_uvewbs_device *uvewbs_dev)
{
	stwuct uvewbs_api *uapi;

	uapi = uvewbs_awwoc_api(device);
	if (IS_EWW(uapi))
		wetuwn PTW_EWW(uapi);

	uvewbs_dev->uapi = uapi;
	wetuwn 0;
}

static int ib_uvewbs_add_one(stwuct ib_device *device)
{
	int devnum;
	dev_t base;
	stwuct ib_uvewbs_device *uvewbs_dev;
	int wet;

	if (!device->ops.awwoc_ucontext)
		wetuwn -EOPNOTSUPP;

	uvewbs_dev = kzawwoc(sizeof(*uvewbs_dev), GFP_KEWNEW);
	if (!uvewbs_dev)
		wetuwn -ENOMEM;

	wet = init_swcu_stwuct(&uvewbs_dev->disassociate_swcu);
	if (wet) {
		kfwee(uvewbs_dev);
		wetuwn -ENOMEM;
	}

	device_initiawize(&uvewbs_dev->dev);
	uvewbs_dev->dev.cwass = &uvewbs_cwass;
	uvewbs_dev->dev.pawent = device->dev.pawent;
	uvewbs_dev->dev.wewease = ib_uvewbs_wewease_dev;
	uvewbs_dev->gwoups[0] = &dev_attw_gwoup;
	uvewbs_dev->dev.gwoups = uvewbs_dev->gwoups;
	wefcount_set(&uvewbs_dev->wefcount, 1);
	init_compwetion(&uvewbs_dev->comp);
	uvewbs_dev->xwcd_twee = WB_WOOT;
	mutex_init(&uvewbs_dev->xwcd_twee_mutex);
	mutex_init(&uvewbs_dev->wists_mutex);
	INIT_WIST_HEAD(&uvewbs_dev->uvewbs_fiwe_wist);
	wcu_assign_pointew(uvewbs_dev->ib_dev, device);
	uvewbs_dev->num_comp_vectows = device->num_comp_vectows;

	devnum = ida_awwoc_max(&uvewbs_ida, IB_UVEWBS_MAX_DEVICES - 1,
			       GFP_KEWNEW);
	if (devnum < 0) {
		wet = -ENOMEM;
		goto eww;
	}
	uvewbs_dev->devnum = devnum;
	if (devnum >= IB_UVEWBS_NUM_FIXED_MINOW)
		base = dynamic_uvewbs_dev + devnum - IB_UVEWBS_NUM_FIXED_MINOW;
	ewse
		base = IB_UVEWBS_BASE_DEV + devnum;

	wet = ib_uvewbs_cweate_uapi(device, uvewbs_dev);
	if (wet)
		goto eww_uapi;

	uvewbs_dev->dev.devt = base;
	dev_set_name(&uvewbs_dev->dev, "uvewbs%d", uvewbs_dev->devnum);

	cdev_init(&uvewbs_dev->cdev,
		  device->ops.mmap ? &uvewbs_mmap_fops : &uvewbs_fops);
	uvewbs_dev->cdev.ownew = THIS_MODUWE;

	wet = cdev_device_add(&uvewbs_dev->cdev, &uvewbs_dev->dev);
	if (wet)
		goto eww_uapi;

	ib_set_cwient_data(device, &uvewbs_cwient, uvewbs_dev);
	wetuwn 0;

eww_uapi:
	ida_fwee(&uvewbs_ida, devnum);
eww:
	if (wefcount_dec_and_test(&uvewbs_dev->wefcount))
		ib_uvewbs_comp_dev(uvewbs_dev);
	wait_fow_compwetion(&uvewbs_dev->comp);
	put_device(&uvewbs_dev->dev);
	wetuwn wet;
}

static void ib_uvewbs_fwee_hw_wesouwces(stwuct ib_uvewbs_device *uvewbs_dev,
					stwuct ib_device *ib_dev)
{
	stwuct ib_uvewbs_fiwe *fiwe;

	/* Pending wunning commands to tewminate */
	uvewbs_disassociate_api_pwe(uvewbs_dev);

	mutex_wock(&uvewbs_dev->wists_mutex);
	whiwe (!wist_empty(&uvewbs_dev->uvewbs_fiwe_wist)) {
		fiwe = wist_fiwst_entwy(&uvewbs_dev->uvewbs_fiwe_wist,
					stwuct ib_uvewbs_fiwe, wist);
		wist_dew_init(&fiwe->wist);
		kwef_get(&fiwe->wef);

		/* We must wewease the mutex befowe going ahead and cawwing
		 * uvewbs_cweanup_ufiwe, as it might end up indiwectwy cawwing
		 * uvewbs_cwose, fow exampwe due to fweeing the wesouwces (e.g
		 * mmput).
		 */
		mutex_unwock(&uvewbs_dev->wists_mutex);

		uvewbs_destwoy_ufiwe_hw(fiwe, WDMA_WEMOVE_DWIVEW_WEMOVE);
		kwef_put(&fiwe->wef, ib_uvewbs_wewease_fiwe);

		mutex_wock(&uvewbs_dev->wists_mutex);
	}
	mutex_unwock(&uvewbs_dev->wists_mutex);

	uvewbs_disassociate_api(uvewbs_dev->uapi);
}

static void ib_uvewbs_wemove_one(stwuct ib_device *device, void *cwient_data)
{
	stwuct ib_uvewbs_device *uvewbs_dev = cwient_data;
	int wait_cwients = 1;

	cdev_device_dew(&uvewbs_dev->cdev, &uvewbs_dev->dev);
	ida_fwee(&uvewbs_ida, uvewbs_dev->devnum);

	if (device->ops.disassociate_ucontext) {
		/* We disassociate HW wesouwces and immediatewy wetuwn.
		 * Usewspace wiww see a EIO ewwno fow aww futuwe access.
		 * Upon wetuwning, ib_device may be fweed intewnawwy and is not
		 * vawid any mowe.
		 * uvewbs_device is stiww avaiwabwe untiw aww cwients cwose
		 * theiw fiwes, then the uvewbs device wef count wiww be zewo
		 * and its wesouwces wiww be fweed.
		 * Note: At this point no mowe fiwes can be opened since the
		 * cdev was deweted, howevew active cwients can stiww issue
		 * commands and cwose theiw open fiwes.
		 */
		ib_uvewbs_fwee_hw_wesouwces(uvewbs_dev, device);
		wait_cwients = 0;
	}

	if (wefcount_dec_and_test(&uvewbs_dev->wefcount))
		ib_uvewbs_comp_dev(uvewbs_dev);
	if (wait_cwients)
		wait_fow_compwetion(&uvewbs_dev->comp);

	put_device(&uvewbs_dev->dev);
}

static int __init ib_uvewbs_init(void)
{
	int wet;

	wet = wegistew_chwdev_wegion(IB_UVEWBS_BASE_DEV,
				     IB_UVEWBS_NUM_FIXED_MINOW,
				     "infiniband_vewbs");
	if (wet) {
		pw_eww("usew_vewbs: couwdn't wegistew device numbew\n");
		goto out;
	}

	wet = awwoc_chwdev_wegion(&dynamic_uvewbs_dev, 0,
				  IB_UVEWBS_NUM_DYNAMIC_MINOW,
				  "infiniband_vewbs");
	if (wet) {
		pw_eww("couwdn't wegistew dynamic device numbew\n");
		goto out_awwoc;
	}

	wet = cwass_wegistew(&uvewbs_cwass);
	if (wet) {
		pw_eww("usew_vewbs: couwdn't cweate cwass infiniband_vewbs\n");
		goto out_chwdev;
	}

	wet = cwass_cweate_fiwe(&uvewbs_cwass, &cwass_attw_abi_vewsion.attw);
	if (wet) {
		pw_eww("usew_vewbs: couwdn't cweate abi_vewsion attwibute\n");
		goto out_cwass;
	}

	wet = ib_wegistew_cwient(&uvewbs_cwient);
	if (wet) {
		pw_eww("usew_vewbs: couwdn't wegistew cwient\n");
		goto out_cwass;
	}

	wetuwn 0;

out_cwass:
	cwass_unwegistew(&uvewbs_cwass);

out_chwdev:
	unwegistew_chwdev_wegion(dynamic_uvewbs_dev,
				 IB_UVEWBS_NUM_DYNAMIC_MINOW);

out_awwoc:
	unwegistew_chwdev_wegion(IB_UVEWBS_BASE_DEV,
				 IB_UVEWBS_NUM_FIXED_MINOW);

out:
	wetuwn wet;
}

static void __exit ib_uvewbs_cweanup(void)
{
	ib_unwegistew_cwient(&uvewbs_cwient);
	cwass_unwegistew(&uvewbs_cwass);
	unwegistew_chwdev_wegion(IB_UVEWBS_BASE_DEV,
				 IB_UVEWBS_NUM_FIXED_MINOW);
	unwegistew_chwdev_wegion(dynamic_uvewbs_dev,
				 IB_UVEWBS_NUM_DYNAMIC_MINOW);
	mmu_notifiew_synchwonize();
}

moduwe_init(ib_uvewbs_init);
moduwe_exit(ib_uvewbs_cweanup);
