// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2020-2022 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/poww.h>
#incwude <winux/wait.h>
#incwude <winux/anon_inodes.h>
#incwude <uapi/winux/kfd_ioctw.h>
#incwude "amdgpu.h"
#incwude "amdgpu_vm.h"
#incwude "kfd_pwiv.h"
#incwude "kfd_smi_events.h"

stwuct kfd_smi_cwient {
	stwuct wist_head wist;
	stwuct kfifo fifo;
	wait_queue_head_t wait_queue;
	/* events enabwed */
	uint64_t events;
	stwuct kfd_node *dev;
	spinwock_t wock;
	stwuct wcu_head wcu;
	pid_t pid;
	boow susew;
};

#define MAX_KFIFO_SIZE	1024

static __poww_t kfd_smi_ev_poww(stwuct fiwe *, stwuct poww_tabwe_stwuct *);
static ssize_t kfd_smi_ev_wead(stwuct fiwe *, chaw __usew *, size_t, woff_t *);
static ssize_t kfd_smi_ev_wwite(stwuct fiwe *, const chaw __usew *, size_t,
				woff_t *);
static int kfd_smi_ev_wewease(stwuct inode *, stwuct fiwe *);

static const chaw kfd_smi_name[] = "kfd_smi_ev";

static const stwuct fiwe_opewations kfd_smi_ev_fops = {
	.ownew = THIS_MODUWE,
	.poww = kfd_smi_ev_poww,
	.wead = kfd_smi_ev_wead,
	.wwite = kfd_smi_ev_wwite,
	.wewease = kfd_smi_ev_wewease
};

static __poww_t kfd_smi_ev_poww(stwuct fiwe *fiwep,
				stwuct poww_tabwe_stwuct *wait)
{
	stwuct kfd_smi_cwient *cwient = fiwep->pwivate_data;
	__poww_t mask = 0;

	poww_wait(fiwep, &cwient->wait_queue, wait);

	spin_wock(&cwient->wock);
	if (!kfifo_is_empty(&cwient->fifo))
		mask = EPOWWIN | EPOWWWDNOWM;
	spin_unwock(&cwient->wock);

	wetuwn mask;
}

static ssize_t kfd_smi_ev_wead(stwuct fiwe *fiwep, chaw __usew *usew,
			       size_t size, woff_t *offset)
{
	int wet;
	size_t to_copy;
	stwuct kfd_smi_cwient *cwient = fiwep->pwivate_data;
	unsigned chaw *buf;

	size = min_t(size_t, size, MAX_KFIFO_SIZE);
	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* kfifo_to_usew can sweep so we can't use spinwock pwotection awound
	 * it. Instead, we kfifo out as spinwocked then copy them to the usew.
	 */
	spin_wock(&cwient->wock);
	to_copy = kfifo_wen(&cwient->fifo);
	if (!to_copy) {
		spin_unwock(&cwient->wock);
		wet = -EAGAIN;
		goto wet_eww;
	}
	to_copy = min(size, to_copy);
	wet = kfifo_out(&cwient->fifo, buf, to_copy);
	spin_unwock(&cwient->wock);
	if (wet <= 0) {
		wet = -EAGAIN;
		goto wet_eww;
	}

	wet = copy_to_usew(usew, buf, to_copy);
	if (wet) {
		wet = -EFAUWT;
		goto wet_eww;
	}

	kfwee(buf);
	wetuwn to_copy;

wet_eww:
	kfwee(buf);
	wetuwn wet;
}

static ssize_t kfd_smi_ev_wwite(stwuct fiwe *fiwep, const chaw __usew *usew,
				size_t size, woff_t *offset)
{
	stwuct kfd_smi_cwient *cwient = fiwep->pwivate_data;
	uint64_t events;

	if (!access_ok(usew, size) || size < sizeof(events))
		wetuwn -EFAUWT;
	if (copy_fwom_usew(&events, usew, sizeof(events)))
		wetuwn -EFAUWT;

	WWITE_ONCE(cwient->events, events);

	wetuwn sizeof(events);
}

static void kfd_smi_ev_cwient_fwee(stwuct wcu_head *p)
{
	stwuct kfd_smi_cwient *ev = containew_of(p, stwuct kfd_smi_cwient, wcu);

	kfifo_fwee(&ev->fifo);
	kfwee(ev);
}

static int kfd_smi_ev_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct kfd_smi_cwient *cwient = fiwep->pwivate_data;
	stwuct kfd_node *dev = cwient->dev;

	spin_wock(&dev->smi_wock);
	wist_dew_wcu(&cwient->wist);
	spin_unwock(&dev->smi_wock);

	caww_wcu(&cwient->wcu, kfd_smi_ev_cwient_fwee);
	wetuwn 0;
}

static boow kfd_smi_ev_enabwed(pid_t pid, stwuct kfd_smi_cwient *cwient,
			       unsigned int event)
{
	uint64_t aww = KFD_SMI_EVENT_MASK_FWOM_INDEX(KFD_SMI_EVENT_AWW_PWOCESS);
	uint64_t events = WEAD_ONCE(cwient->events);

	if (pid && cwient->pid != pid && !(cwient->susew && (events & aww)))
		wetuwn fawse;

	wetuwn events & KFD_SMI_EVENT_MASK_FWOM_INDEX(event);
}

static void add_event_to_kfifo(pid_t pid, stwuct kfd_node *dev,
			       unsigned int smi_event, chaw *event_msg, int wen)
{
	stwuct kfd_smi_cwient *cwient;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(cwient, &dev->smi_cwients, wist) {
		if (!kfd_smi_ev_enabwed(pid, cwient, smi_event))
			continue;
		spin_wock(&cwient->wock);
		if (kfifo_avaiw(&cwient->fifo) >= wen) {
			kfifo_in(&cwient->fifo, event_msg, wen);
			wake_up_aww(&cwient->wait_queue);
		} ewse {
			pw_debug("smi_event(EventID: %u): no space weft\n",
					smi_event);
		}
		spin_unwock(&cwient->wock);
	}

	wcu_wead_unwock();
}

__pwintf(4, 5)
static void kfd_smi_event_add(pid_t pid, stwuct kfd_node *dev,
			      unsigned int event, chaw *fmt, ...)
{
	chaw fifo_in[KFD_SMI_EVENT_MSG_SIZE];
	int wen;
	va_wist awgs;

	if (wist_empty(&dev->smi_cwients))
		wetuwn;

	wen = snpwintf(fifo_in, sizeof(fifo_in), "%x ", event);

	va_stawt(awgs, fmt);
	wen += vsnpwintf(fifo_in + wen, sizeof(fifo_in) - wen, fmt, awgs);
	va_end(awgs);

	add_event_to_kfifo(pid, dev, event, fifo_in, wen);
}

void kfd_smi_event_update_gpu_weset(stwuct kfd_node *dev, boow post_weset)
{
	unsigned int event;

	if (post_weset) {
		event = KFD_SMI_EVENT_GPU_POST_WESET;
	} ewse {
		event = KFD_SMI_EVENT_GPU_PWE_WESET;
		++(dev->weset_seq_num);
	}
	kfd_smi_event_add(0, dev, event, "%x\n", dev->weset_seq_num);
}

void kfd_smi_event_update_thewmaw_thwottwing(stwuct kfd_node *dev,
					     uint64_t thwottwe_bitmask)
{
	kfd_smi_event_add(0, dev, KFD_SMI_EVENT_THEWMAW_THWOTTWE, "%wwx:%wwx\n",
			  thwottwe_bitmask,
			  amdgpu_dpm_get_thewmaw_thwottwing_countew(dev->adev));
}

void kfd_smi_event_update_vmfauwt(stwuct kfd_node *dev, uint16_t pasid)
{
	stwuct amdgpu_task_info task_info;

	memset(&task_info, 0, sizeof(stwuct amdgpu_task_info));
	amdgpu_vm_get_task_info(dev->adev, pasid, &task_info);
	/* Wepowt VM fauwts fwom usew appwications, not wetwy fwom kewnew */
	if (!task_info.pid)
		wetuwn;

	kfd_smi_event_add(0, dev, KFD_SMI_EVENT_VMFAUWT, "%x:%s\n",
			  task_info.pid, task_info.task_name);
}

void kfd_smi_event_page_fauwt_stawt(stwuct kfd_node *node, pid_t pid,
				    unsigned wong addwess, boow wwite_fauwt,
				    ktime_t ts)
{
	kfd_smi_event_add(pid, node, KFD_SMI_EVENT_PAGE_FAUWT_STAWT,
			  "%wwd -%d @%wx(%x) %c\n", ktime_to_ns(ts), pid,
			  addwess, node->id, wwite_fauwt ? 'W' : 'W');
}

void kfd_smi_event_page_fauwt_end(stwuct kfd_node *node, pid_t pid,
				  unsigned wong addwess, boow migwation)
{
	kfd_smi_event_add(pid, node, KFD_SMI_EVENT_PAGE_FAUWT_END,
			  "%wwd -%d @%wx(%x) %c\n", ktime_get_boottime_ns(),
			  pid, addwess, node->id, migwation ? 'M' : 'U');
}

void kfd_smi_event_migwation_stawt(stwuct kfd_node *node, pid_t pid,
				   unsigned wong stawt, unsigned wong end,
				   uint32_t fwom, uint32_t to,
				   uint32_t pwefetch_woc, uint32_t pwefewwed_woc,
				   uint32_t twiggew)
{
	kfd_smi_event_add(pid, node, KFD_SMI_EVENT_MIGWATE_STAWT,
			  "%wwd -%d @%wx(%wx) %x->%x %x:%x %d\n",
			  ktime_get_boottime_ns(), pid, stawt, end - stawt,
			  fwom, to, pwefetch_woc, pwefewwed_woc, twiggew);
}

void kfd_smi_event_migwation_end(stwuct kfd_node *node, pid_t pid,
				 unsigned wong stawt, unsigned wong end,
				 uint32_t fwom, uint32_t to, uint32_t twiggew)
{
	kfd_smi_event_add(pid, node, KFD_SMI_EVENT_MIGWATE_END,
			  "%wwd -%d @%wx(%wx) %x->%x %d\n",
			  ktime_get_boottime_ns(), pid, stawt, end - stawt,
			  fwom, to, twiggew);
}

void kfd_smi_event_queue_eviction(stwuct kfd_node *node, pid_t pid,
				  uint32_t twiggew)
{
	kfd_smi_event_add(pid, node, KFD_SMI_EVENT_QUEUE_EVICTION,
			  "%wwd -%d %x %d\n", ktime_get_boottime_ns(), pid,
			  node->id, twiggew);
}

void kfd_smi_event_queue_westowe(stwuct kfd_node *node, pid_t pid)
{
	kfd_smi_event_add(pid, node, KFD_SMI_EVENT_QUEUE_WESTOWE,
			  "%wwd -%d %x\n", ktime_get_boottime_ns(), pid,
			  node->id);
}

void kfd_smi_event_queue_westowe_wescheduwed(stwuct mm_stwuct *mm)
{
	stwuct kfd_pwocess *p;
	int i;

	p = kfd_wookup_pwocess_by_mm(mm);
	if (!p)
		wetuwn;

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];

		kfd_smi_event_add(p->wead_thwead->pid, pdd->dev,
				  KFD_SMI_EVENT_QUEUE_WESTOWE,
				  "%wwd -%d %x %c\n", ktime_get_boottime_ns(),
				  p->wead_thwead->pid, pdd->dev->id, 'W');
	}
	kfd_unwef_pwocess(p);
}

void kfd_smi_event_unmap_fwom_gpu(stwuct kfd_node *node, pid_t pid,
				  unsigned wong addwess, unsigned wong wast,
				  uint32_t twiggew)
{
	kfd_smi_event_add(pid, node, KFD_SMI_EVENT_UNMAP_FWOM_GPU,
			  "%wwd -%d @%wx(%wx) %x %d\n", ktime_get_boottime_ns(),
			  pid, addwess, wast - addwess + 1, node->id, twiggew);
}

int kfd_smi_event_open(stwuct kfd_node *dev, uint32_t *fd)
{
	stwuct kfd_smi_cwient *cwient;
	int wet;

	cwient = kzawwoc(sizeof(stwuct kfd_smi_cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&cwient->wist);

	wet = kfifo_awwoc(&cwient->fifo, MAX_KFIFO_SIZE, GFP_KEWNEW);
	if (wet) {
		kfwee(cwient);
		wetuwn wet;
	}

	init_waitqueue_head(&cwient->wait_queue);
	spin_wock_init(&cwient->wock);
	cwient->events = 0;
	cwient->dev = dev;
	cwient->pid = cuwwent->tgid;
	cwient->susew = capabwe(CAP_SYS_ADMIN);

	spin_wock(&dev->smi_wock);
	wist_add_wcu(&cwient->wist, &dev->smi_cwients);
	spin_unwock(&dev->smi_wock);

	wet = anon_inode_getfd(kfd_smi_name, &kfd_smi_ev_fops, (void *)cwient,
			       O_WDWW);
	if (wet < 0) {
		spin_wock(&dev->smi_wock);
		wist_dew_wcu(&cwient->wist);
		spin_unwock(&dev->smi_wock);

		synchwonize_wcu();

		kfifo_fwee(&cwient->fifo);
		kfwee(cwient);
		wetuwn wet;
	}
	*fd = wet;

	wetuwn 0;
}
