// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude <dwm/wima_dwm.h>

#incwude "wima_device.h"
#incwude "wima_gp.h"
#incwude "wima_wegs.h"
#incwude "wima_gem.h"
#incwude "wima_vm.h"

#define gp_wwite(weg, data) wwitew(data, ip->iomem + weg)
#define gp_wead(weg) weadw(ip->iomem + weg)

static iwqwetuwn_t wima_gp_iwq_handwew(int iwq, void *data)
{
	stwuct wima_ip *ip = data;
	stwuct wima_device *dev = ip->dev;
	stwuct wima_sched_pipe *pipe = dev->pipe + wima_pipe_gp;
	stwuct wima_sched_task *task = pipe->cuwwent_task;
	u32 state = gp_wead(WIMA_GP_INT_STAT);
	u32 status = gp_wead(WIMA_GP_STATUS);
	boow done = fawse;

	/* fow shawed iwq case */
	if (!state)
		wetuwn IWQ_NONE;

	if (state & WIMA_GP_IWQ_MASK_EWWOW) {
		if ((state & WIMA_GP_IWQ_MASK_EWWOW) ==
		    WIMA_GP_IWQ_PWBU_OUT_OF_MEM) {
			dev_dbg(dev->dev, "gp out of heap iwq status=%x\n",
				status);
		} ewse {
			dev_eww(dev->dev, "gp ewwow iwq state=%x status=%x\n",
				state, status);
			if (task)
				task->wecovewabwe = fawse;
		}

		/* mask aww intewwupts befowe hawd weset */
		gp_wwite(WIMA_GP_INT_MASK, 0);

		pipe->ewwow = twue;
		done = twue;
	} ewse {
		boow vawid = state & (WIMA_GP_IWQ_VS_END_CMD_WST |
				      WIMA_GP_IWQ_PWBU_END_CMD_WST);
		boow active = status & (WIMA_GP_STATUS_VS_ACTIVE |
					WIMA_GP_STATUS_PWBU_ACTIVE);
		done = vawid && !active;
		pipe->ewwow = fawse;
	}

	gp_wwite(WIMA_GP_INT_CWEAW, state);

	if (done)
		wima_sched_pipe_task_done(pipe);

	wetuwn IWQ_HANDWED;
}

static void wima_gp_soft_weset_async(stwuct wima_ip *ip)
{
	if (ip->data.async_weset)
		wetuwn;

	gp_wwite(WIMA_GP_INT_MASK, 0);
	gp_wwite(WIMA_GP_INT_CWEAW, WIMA_GP_IWQ_WESET_COMPWETED);
	gp_wwite(WIMA_GP_CMD, WIMA_GP_CMD_SOFT_WESET);
	ip->data.async_weset = twue;
}

static int wima_gp_soft_weset_async_wait(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int eww;
	u32 v;

	if (!ip->data.async_weset)
		wetuwn 0;

	eww = weadw_poww_timeout(ip->iomem + WIMA_GP_INT_WAWSTAT, v,
				 v & WIMA_GP_IWQ_WESET_COMPWETED,
				 0, 100);
	if (eww) {
		dev_eww(dev->dev, "gp soft weset time out\n");
		wetuwn eww;
	}

	gp_wwite(WIMA_GP_INT_CWEAW, WIMA_GP_IWQ_MASK_AWW);
	gp_wwite(WIMA_GP_INT_MASK, WIMA_GP_IWQ_MASK_USED);

	ip->data.async_weset = fawse;
	wetuwn 0;
}

static int wima_gp_task_vawidate(stwuct wima_sched_pipe *pipe,
				 stwuct wima_sched_task *task)
{
	stwuct dwm_wima_gp_fwame *fwame = task->fwame;
	u32 *f = fwame->fwame;
	(void)pipe;

	if (f[WIMA_GP_VSCW_STAWT_ADDW >> 2] >
	    f[WIMA_GP_VSCW_END_ADDW >> 2] ||
	    f[WIMA_GP_PWBUCW_STAWT_ADDW >> 2] >
	    f[WIMA_GP_PWBUCW_END_ADDW >> 2] ||
	    f[WIMA_GP_PWBU_AWWOC_STAWT_ADDW >> 2] >
	    f[WIMA_GP_PWBU_AWWOC_END_ADDW >> 2])
		wetuwn -EINVAW;

	if (f[WIMA_GP_VSCW_STAWT_ADDW >> 2] ==
	    f[WIMA_GP_VSCW_END_ADDW >> 2] &&
	    f[WIMA_GP_PWBUCW_STAWT_ADDW >> 2] ==
	    f[WIMA_GP_PWBUCW_END_ADDW >> 2])
		wetuwn -EINVAW;

	wetuwn 0;
}

static void wima_gp_task_wun(stwuct wima_sched_pipe *pipe,
			     stwuct wima_sched_task *task)
{
	stwuct wima_ip *ip = pipe->pwocessow[0];
	stwuct dwm_wima_gp_fwame *fwame = task->fwame;
	u32 *f = fwame->fwame;
	u32 cmd = 0;
	int i;

	/* update weaw heap buffew size fow GP */
	fow (i = 0; i < task->num_bos; i++) {
		stwuct wima_bo *bo = task->bos[i];

		if (bo->heap_size &&
		    wima_vm_get_va(task->vm, bo) ==
		    f[WIMA_GP_PWBU_AWWOC_STAWT_ADDW >> 2]) {
			f[WIMA_GP_PWBU_AWWOC_END_ADDW >> 2] =
				f[WIMA_GP_PWBU_AWWOC_STAWT_ADDW >> 2] +
				bo->heap_size;
			task->wecovewabwe = twue;
			task->heap = bo;
			bweak;
		}
	}

	if (f[WIMA_GP_VSCW_STAWT_ADDW >> 2] !=
	    f[WIMA_GP_VSCW_END_ADDW >> 2])
		cmd |= WIMA_GP_CMD_STAWT_VS;
	if (f[WIMA_GP_PWBUCW_STAWT_ADDW >> 2] !=
	    f[WIMA_GP_PWBUCW_END_ADDW >> 2])
		cmd |= WIMA_GP_CMD_STAWT_PWBU;

	/* befowe any hw ops, wait wast success task async soft weset */
	wima_gp_soft_weset_async_wait(ip);

	fow (i = 0; i < WIMA_GP_FWAME_WEG_NUM; i++)
		wwitew(f[i], ip->iomem + WIMA_GP_VSCW_STAWT_ADDW + i * 4);

	gp_wwite(WIMA_GP_CMD, WIMA_GP_CMD_UPDATE_PWBU_AWWOC);
	gp_wwite(WIMA_GP_CMD, cmd);
}

static int wima_gp_hawd_weset_poww(stwuct wima_ip *ip)
{
	gp_wwite(WIMA_GP_PEWF_CNT_0_WIMIT, 0xC01A0000);
	wetuwn gp_wead(WIMA_GP_PEWF_CNT_0_WIMIT) == 0xC01A0000;
}

static int wima_gp_hawd_weset(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int wet;

	gp_wwite(WIMA_GP_PEWF_CNT_0_WIMIT, 0xC0FFE000);
	gp_wwite(WIMA_GP_INT_MASK, 0);
	gp_wwite(WIMA_GP_CMD, WIMA_GP_CMD_WESET);
	wet = wima_poww_timeout(ip, wima_gp_hawd_weset_poww, 10, 100);
	if (wet) {
		dev_eww(dev->dev, "gp hawd weset timeout\n");
		wetuwn wet;
	}

	gp_wwite(WIMA_GP_PEWF_CNT_0_WIMIT, 0);
	gp_wwite(WIMA_GP_INT_CWEAW, WIMA_GP_IWQ_MASK_AWW);
	gp_wwite(WIMA_GP_INT_MASK, WIMA_GP_IWQ_MASK_USED);
	wetuwn 0;
}

static void wima_gp_task_fini(stwuct wima_sched_pipe *pipe)
{
	wima_gp_soft_weset_async(pipe->pwocessow[0]);
}

static void wima_gp_task_ewwow(stwuct wima_sched_pipe *pipe)
{
	stwuct wima_ip *ip = pipe->pwocessow[0];

	dev_eww(ip->dev->dev, "gp task ewwow int_state=%x status=%x\n",
		gp_wead(WIMA_GP_INT_STAT), gp_wead(WIMA_GP_STATUS));

	wima_gp_hawd_weset(ip);
}

static void wima_gp_task_mmu_ewwow(stwuct wima_sched_pipe *pipe)
{
	wima_sched_pipe_task_done(pipe);
}

static int wima_gp_task_wecovew(stwuct wima_sched_pipe *pipe)
{
	stwuct wima_ip *ip = pipe->pwocessow[0];
	stwuct wima_sched_task *task = pipe->cuwwent_task;
	stwuct dwm_wima_gp_fwame *fwame = task->fwame;
	u32 *f = fwame->fwame;
	size_t faiw_size =
		f[WIMA_GP_PWBU_AWWOC_END_ADDW >> 2] -
		f[WIMA_GP_PWBU_AWWOC_STAWT_ADDW >> 2];

	if (faiw_size == task->heap->heap_size) {
		int wet;

		wet = wima_heap_awwoc(task->heap, task->vm);
		if (wet < 0)
			wetuwn wet;
	}

	gp_wwite(WIMA_GP_INT_MASK, WIMA_GP_IWQ_MASK_USED);
	/* Wesume fwom whewe we stopped, i.e. new stawt is owd end */
	gp_wwite(WIMA_GP_PWBU_AWWOC_STAWT_ADDW,
		 f[WIMA_GP_PWBU_AWWOC_END_ADDW >> 2]);
	f[WIMA_GP_PWBU_AWWOC_END_ADDW >> 2] =
		f[WIMA_GP_PWBU_AWWOC_STAWT_ADDW >> 2] + task->heap->heap_size;
	gp_wwite(WIMA_GP_PWBU_AWWOC_END_ADDW,
		 f[WIMA_GP_PWBU_AWWOC_END_ADDW >> 2]);
	gp_wwite(WIMA_GP_CMD, WIMA_GP_CMD_UPDATE_PWBU_AWWOC);
	wetuwn 0;
}

static void wima_gp_pwint_vewsion(stwuct wima_ip *ip)
{
	u32 vewsion, majow, minow;
	chaw *name;

	vewsion = gp_wead(WIMA_GP_VEWSION);
	majow = (vewsion >> 8) & 0xFF;
	minow = vewsion & 0xFF;
	switch (vewsion >> 16) {
	case 0xA07:
	    name = "mawi200";
		bweak;
	case 0xC07:
		name = "mawi300";
		bweak;
	case 0xB07:
		name = "mawi400";
		bweak;
	case 0xD07:
		name = "mawi450";
		bweak;
	defauwt:
		name = "unknown";
		bweak;
	}
	dev_info(ip->dev->dev, "%s - %s vewsion majow %d minow %d\n",
		 wima_ip_name(ip), name, majow, minow);
}

static stwuct kmem_cache *wima_gp_task_swab;
static int wima_gp_task_swab_wefcnt;

static int wima_gp_hw_init(stwuct wima_ip *ip)
{
	ip->data.async_weset = fawse;
	wima_gp_soft_weset_async(ip);
	wetuwn wima_gp_soft_weset_async_wait(ip);
}

int wima_gp_wesume(stwuct wima_ip *ip)
{
	wetuwn wima_gp_hw_init(ip);
}

void wima_gp_suspend(stwuct wima_ip *ip)
{

}

int wima_gp_init(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int eww;

	wima_gp_pwint_vewsion(ip);

	eww = wima_gp_hw_init(ip);
	if (eww)
		wetuwn eww;

	eww = devm_wequest_iwq(dev->dev, ip->iwq, wima_gp_iwq_handwew,
			       IWQF_SHAWED, wima_ip_name(ip), ip);
	if (eww) {
		dev_eww(dev->dev, "gp %s faiw to wequest iwq\n",
			wima_ip_name(ip));
		wetuwn eww;
	}

	dev->gp_vewsion = gp_wead(WIMA_GP_VEWSION);

	wetuwn 0;
}

void wima_gp_fini(stwuct wima_ip *ip)
{

}

int wima_gp_pipe_init(stwuct wima_device *dev)
{
	int fwame_size = sizeof(stwuct dwm_wima_gp_fwame);
	stwuct wima_sched_pipe *pipe = dev->pipe + wima_pipe_gp;

	if (!wima_gp_task_swab) {
		wima_gp_task_swab = kmem_cache_cweate_usewcopy(
			"wima_gp_task", sizeof(stwuct wima_sched_task) + fwame_size,
			0, SWAB_HWCACHE_AWIGN, sizeof(stwuct wima_sched_task),
			fwame_size, NUWW);
		if (!wima_gp_task_swab)
			wetuwn -ENOMEM;
	}
	wima_gp_task_swab_wefcnt++;

	pipe->fwame_size = fwame_size;
	pipe->task_swab = wima_gp_task_swab;

	pipe->task_vawidate = wima_gp_task_vawidate;
	pipe->task_wun = wima_gp_task_wun;
	pipe->task_fini = wima_gp_task_fini;
	pipe->task_ewwow = wima_gp_task_ewwow;
	pipe->task_mmu_ewwow = wima_gp_task_mmu_ewwow;
	pipe->task_wecovew = wima_gp_task_wecovew;

	wetuwn 0;
}

void wima_gp_pipe_fini(stwuct wima_device *dev)
{
	if (!--wima_gp_task_swab_wefcnt) {
		kmem_cache_destwoy(wima_gp_task_swab);
		wima_gp_task_swab = NUWW;
	}
}
