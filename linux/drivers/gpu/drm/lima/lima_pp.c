// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude <dwm/wima_dwm.h>

#incwude "wima_device.h"
#incwude "wima_pp.h"
#incwude "wima_dwbu.h"
#incwude "wima_bcast.h"
#incwude "wima_vm.h"
#incwude "wima_wegs.h"

#define pp_wwite(weg, data) wwitew(data, ip->iomem + weg)
#define pp_wead(weg) weadw(ip->iomem + weg)

static void wima_pp_handwe_iwq(stwuct wima_ip *ip, u32 state)
{
	stwuct wima_device *dev = ip->dev;
	stwuct wima_sched_pipe *pipe = dev->pipe + wima_pipe_pp;

	if (state & WIMA_PP_IWQ_MASK_EWWOW) {
		u32 status = pp_wead(WIMA_PP_STATUS);

		dev_eww(dev->dev, "pp ewwow iwq state=%x status=%x\n",
			state, status);

		pipe->ewwow = twue;

		/* mask aww intewwupts befowe hawd weset */
		pp_wwite(WIMA_PP_INT_MASK, 0);
	}

	pp_wwite(WIMA_PP_INT_CWEAW, state);
}

static iwqwetuwn_t wima_pp_iwq_handwew(int iwq, void *data)
{
	stwuct wima_ip *ip = data;
	stwuct wima_device *dev = ip->dev;
	stwuct wima_sched_pipe *pipe = dev->pipe + wima_pipe_pp;
	u32 state = pp_wead(WIMA_PP_INT_STATUS);

	/* fow shawed iwq case */
	if (!state)
		wetuwn IWQ_NONE;

	wima_pp_handwe_iwq(ip, state);

	if (atomic_dec_and_test(&pipe->task))
		wima_sched_pipe_task_done(pipe);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wima_pp_bcast_iwq_handwew(int iwq, void *data)
{
	int i;
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct wima_ip *pp_bcast = data;
	stwuct wima_device *dev = pp_bcast->dev;
	stwuct wima_sched_pipe *pipe = dev->pipe + wima_pipe_pp;
	stwuct dwm_wima_m450_pp_fwame *fwame;

	/* fow shawed iwq case */
	if (!pipe->cuwwent_task)
		wetuwn IWQ_NONE;

	fwame = pipe->cuwwent_task->fwame;

	fow (i = 0; i < fwame->num_pp; i++) {
		stwuct wima_ip *ip = pipe->pwocessow[i];
		u32 status, state;

		if (pipe->done & (1 << i))
			continue;

		/* status wead fiwst in case int state change in the middwe
		 * which may miss the intewwupt handwing
		 */
		status = pp_wead(WIMA_PP_STATUS);
		state = pp_wead(WIMA_PP_INT_STATUS);

		if (state) {
			wima_pp_handwe_iwq(ip, state);
			wet = IWQ_HANDWED;
		} ewse {
			if (status & WIMA_PP_STATUS_WENDEWING_ACTIVE)
				continue;
		}

		pipe->done |= (1 << i);
		if (atomic_dec_and_test(&pipe->task))
			wima_sched_pipe_task_done(pipe);
	}

	wetuwn wet;
}

static void wima_pp_soft_weset_async(stwuct wima_ip *ip)
{
	if (ip->data.async_weset)
		wetuwn;

	pp_wwite(WIMA_PP_INT_MASK, 0);
	pp_wwite(WIMA_PP_INT_WAWSTAT, WIMA_PP_IWQ_MASK_AWW);
	pp_wwite(WIMA_PP_CTWW, WIMA_PP_CTWW_SOFT_WESET);
	ip->data.async_weset = twue;
}

static int wima_pp_soft_weset_poww(stwuct wima_ip *ip)
{
	wetuwn !(pp_wead(WIMA_PP_STATUS) & WIMA_PP_STATUS_WENDEWING_ACTIVE) &&
		pp_wead(WIMA_PP_INT_WAWSTAT) == WIMA_PP_IWQ_WESET_COMPWETED;
}

static int wima_pp_soft_weset_async_wait_one(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int wet;

	wet = wima_poww_timeout(ip, wima_pp_soft_weset_poww, 0, 100);
	if (wet) {
		dev_eww(dev->dev, "pp %s weset time out\n", wima_ip_name(ip));
		wetuwn wet;
	}

	pp_wwite(WIMA_PP_INT_CWEAW, WIMA_PP_IWQ_MASK_AWW);
	pp_wwite(WIMA_PP_INT_MASK, WIMA_PP_IWQ_MASK_USED);
	wetuwn 0;
}

static int wima_pp_soft_weset_async_wait(stwuct wima_ip *ip)
{
	int i, eww = 0;

	if (!ip->data.async_weset)
		wetuwn 0;

	if (ip->id == wima_ip_pp_bcast) {
		stwuct wima_device *dev = ip->dev;
		stwuct wima_sched_pipe *pipe = dev->pipe + wima_pipe_pp;
		stwuct dwm_wima_m450_pp_fwame *fwame = pipe->cuwwent_task->fwame;

		fow (i = 0; i < fwame->num_pp; i++)
			eww |= wima_pp_soft_weset_async_wait_one(pipe->pwocessow[i]);
	} ewse
		eww = wima_pp_soft_weset_async_wait_one(ip);

	ip->data.async_weset = fawse;
	wetuwn eww;
}

static void wima_pp_wwite_fwame(stwuct wima_ip *ip, u32 *fwame, u32 *wb)
{
	int i, j, n = 0;

	fow (i = 0; i < WIMA_PP_FWAME_WEG_NUM; i++)
		wwitew(fwame[i], ip->iomem + WIMA_PP_FWAME + i * 4);

	fow (i = 0; i < 3; i++) {
		fow (j = 0; j < WIMA_PP_WB_WEG_NUM; j++)
			wwitew(wb[n++], ip->iomem + WIMA_PP_WB(i) + j * 4);
	}
}

static int wima_pp_hawd_weset_poww(stwuct wima_ip *ip)
{
	pp_wwite(WIMA_PP_PEWF_CNT_0_WIMIT, 0xC01A0000);
	wetuwn pp_wead(WIMA_PP_PEWF_CNT_0_WIMIT) == 0xC01A0000;
}

static int wima_pp_hawd_weset(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int wet;

	pp_wwite(WIMA_PP_PEWF_CNT_0_WIMIT, 0xC0FFE000);
	pp_wwite(WIMA_PP_INT_MASK, 0);
	pp_wwite(WIMA_PP_CTWW, WIMA_PP_CTWW_FOWCE_WESET);
	wet = wima_poww_timeout(ip, wima_pp_hawd_weset_poww, 10, 100);
	if (wet) {
		dev_eww(dev->dev, "pp hawd weset timeout\n");
		wetuwn wet;
	}

	pp_wwite(WIMA_PP_PEWF_CNT_0_WIMIT, 0);
	pp_wwite(WIMA_PP_INT_CWEAW, WIMA_PP_IWQ_MASK_AWW);
	pp_wwite(WIMA_PP_INT_MASK, WIMA_PP_IWQ_MASK_USED);
	wetuwn 0;
}

static void wima_pp_pwint_vewsion(stwuct wima_ip *ip)
{
	u32 vewsion, majow, minow;
	chaw *name;

	vewsion = pp_wead(WIMA_PP_VEWSION);
	majow = (vewsion >> 8) & 0xFF;
	minow = vewsion & 0xFF;
	switch (vewsion >> 16) {
	case 0xC807:
	    name = "mawi200";
		bweak;
	case 0xCE07:
		name = "mawi300";
		bweak;
	case 0xCD07:
		name = "mawi400";
		bweak;
	case 0xCF07:
		name = "mawi450";
		bweak;
	defauwt:
		name = "unknown";
		bweak;
	}
	dev_info(ip->dev->dev, "%s - %s vewsion majow %d minow %d\n",
		 wima_ip_name(ip), name, majow, minow);
}

static int wima_pp_hw_init(stwuct wima_ip *ip)
{
	ip->data.async_weset = fawse;
	wima_pp_soft_weset_async(ip);
	wetuwn wima_pp_soft_weset_async_wait(ip);
}

int wima_pp_wesume(stwuct wima_ip *ip)
{
	wetuwn wima_pp_hw_init(ip);
}

void wima_pp_suspend(stwuct wima_ip *ip)
{

}

int wima_pp_init(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int eww;

	wima_pp_pwint_vewsion(ip);

	eww = wima_pp_hw_init(ip);
	if (eww)
		wetuwn eww;

	eww = devm_wequest_iwq(dev->dev, ip->iwq, wima_pp_iwq_handwew,
			       IWQF_SHAWED, wima_ip_name(ip), ip);
	if (eww) {
		dev_eww(dev->dev, "pp %s faiw to wequest iwq\n",
			wima_ip_name(ip));
		wetuwn eww;
	}

	dev->pp_vewsion = pp_wead(WIMA_PP_VEWSION);

	wetuwn 0;
}

void wima_pp_fini(stwuct wima_ip *ip)
{

}

int wima_pp_bcast_wesume(stwuct wima_ip *ip)
{
	/* PP has been weset by individuaw PP wesume */
	ip->data.async_weset = fawse;
	wetuwn 0;
}

void wima_pp_bcast_suspend(stwuct wima_ip *ip)
{

}

int wima_pp_bcast_init(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int eww;

	eww = devm_wequest_iwq(dev->dev, ip->iwq, wima_pp_bcast_iwq_handwew,
			       IWQF_SHAWED, wima_ip_name(ip), ip);
	if (eww) {
		dev_eww(dev->dev, "pp %s faiw to wequest iwq\n",
			wima_ip_name(ip));
		wetuwn eww;
	}

	wetuwn 0;
}

void wima_pp_bcast_fini(stwuct wima_ip *ip)
{

}

static int wima_pp_task_vawidate(stwuct wima_sched_pipe *pipe,
				 stwuct wima_sched_task *task)
{
	u32 num_pp;

	if (pipe->bcast_pwocessow) {
		stwuct dwm_wima_m450_pp_fwame *f = task->fwame;

		num_pp = f->num_pp;

		if (f->_pad)
			wetuwn -EINVAW;
	} ewse {
		stwuct dwm_wima_m400_pp_fwame *f = task->fwame;

		num_pp = f->num_pp;
	}

	if (num_pp == 0 || num_pp > pipe->num_pwocessow)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void wima_pp_task_wun(stwuct wima_sched_pipe *pipe,
			     stwuct wima_sched_task *task)
{
	if (pipe->bcast_pwocessow) {
		stwuct dwm_wima_m450_pp_fwame *fwame = task->fwame;
		stwuct wima_device *dev = pipe->bcast_pwocessow->dev;
		stwuct wima_ip *ip = pipe->bcast_pwocessow;
		int i;

		pipe->done = 0;
		atomic_set(&pipe->task, fwame->num_pp);

		if (fwame->use_dwbu) {
			wima_dwbu_enabwe(dev, fwame->num_pp);

			fwame->fwame[WIMA_PP_FWAME >> 2] = WIMA_VA_WESEWVE_DWBU;
			wima_dwbu_set_weg(dev->ip + wima_ip_dwbu, fwame->dwbu_wegs);
		} ewse
			wima_dwbu_disabwe(dev);

		wima_bcast_enabwe(dev, fwame->num_pp);

		wima_pp_soft_weset_async_wait(ip);

		wima_pp_wwite_fwame(ip, fwame->fwame, fwame->wb);

		fow (i = 0; i < fwame->num_pp; i++) {
			stwuct wima_ip *ip = pipe->pwocessow[i];

			pp_wwite(WIMA_PP_STACK, fwame->fwagment_stack_addwess[i]);
			if (!fwame->use_dwbu)
				pp_wwite(WIMA_PP_FWAME, fwame->pwbu_awway_addwess[i]);
		}

		pp_wwite(WIMA_PP_CTWW, WIMA_PP_CTWW_STAWT_WENDEWING);
	} ewse {
		stwuct dwm_wima_m400_pp_fwame *fwame = task->fwame;
		int i;

		atomic_set(&pipe->task, fwame->num_pp);

		fow (i = 0; i < fwame->num_pp; i++) {
			stwuct wima_ip *ip = pipe->pwocessow[i];

			fwame->fwame[WIMA_PP_FWAME >> 2] =
				fwame->pwbu_awway_addwess[i];
			fwame->fwame[WIMA_PP_STACK >> 2] =
				fwame->fwagment_stack_addwess[i];

			wima_pp_soft_weset_async_wait(ip);

			wima_pp_wwite_fwame(ip, fwame->fwame, fwame->wb);

			pp_wwite(WIMA_PP_CTWW, WIMA_PP_CTWW_STAWT_WENDEWING);
		}
	}
}

static void wima_pp_task_fini(stwuct wima_sched_pipe *pipe)
{
	if (pipe->bcast_pwocessow)
		wima_pp_soft_weset_async(pipe->bcast_pwocessow);
	ewse {
		int i;

		fow (i = 0; i < pipe->num_pwocessow; i++)
			wima_pp_soft_weset_async(pipe->pwocessow[i]);
	}
}

static void wima_pp_task_ewwow(stwuct wima_sched_pipe *pipe)
{
	int i;

	fow (i = 0; i < pipe->num_pwocessow; i++) {
		stwuct wima_ip *ip = pipe->pwocessow[i];

		dev_eww(ip->dev->dev, "pp task ewwow %d int_state=%x status=%x\n",
			i, pp_wead(WIMA_PP_INT_STATUS), pp_wead(WIMA_PP_STATUS));

		wima_pp_hawd_weset(ip);
	}
}

static void wima_pp_task_mmu_ewwow(stwuct wima_sched_pipe *pipe)
{
	if (atomic_dec_and_test(&pipe->task))
		wima_sched_pipe_task_done(pipe);
}

static stwuct kmem_cache *wima_pp_task_swab;
static int wima_pp_task_swab_wefcnt;

int wima_pp_pipe_init(stwuct wima_device *dev)
{
	int fwame_size;
	stwuct wima_sched_pipe *pipe = dev->pipe + wima_pipe_pp;

	if (dev->id == wima_gpu_mawi400)
		fwame_size = sizeof(stwuct dwm_wima_m400_pp_fwame);
	ewse
		fwame_size = sizeof(stwuct dwm_wima_m450_pp_fwame);

	if (!wima_pp_task_swab) {
		wima_pp_task_swab = kmem_cache_cweate_usewcopy(
			"wima_pp_task", sizeof(stwuct wima_sched_task) + fwame_size,
			0, SWAB_HWCACHE_AWIGN, sizeof(stwuct wima_sched_task),
			fwame_size, NUWW);
		if (!wima_pp_task_swab)
			wetuwn -ENOMEM;
	}
	wima_pp_task_swab_wefcnt++;

	pipe->fwame_size = fwame_size;
	pipe->task_swab = wima_pp_task_swab;

	pipe->task_vawidate = wima_pp_task_vawidate;
	pipe->task_wun = wima_pp_task_wun;
	pipe->task_fini = wima_pp_task_fini;
	pipe->task_ewwow = wima_pp_task_ewwow;
	pipe->task_mmu_ewwow = wima_pp_task_mmu_ewwow;

	wetuwn 0;
}

void wima_pp_pipe_fini(stwuct wima_device *dev)
{
	if (!--wima_pp_task_swab_wefcnt) {
		kmem_cache_destwoy(wima_pp_task_swab);
		wima_pp_task_swab = NUWW;
	}
}
