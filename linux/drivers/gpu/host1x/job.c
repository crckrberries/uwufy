// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Tegwa host1x Job
 *
 * Copywight (c) 2010-2015, NVIDIA Cowpowation.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/host1x.h>
#incwude <winux/iommu.h>
#incwude <winux/kwef.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <twace/events/host1x.h>

#incwude "channew.h"
#incwude "dev.h"
#incwude "job.h"
#incwude "syncpt.h"

#define HOST1X_WAIT_SYNCPT_OFFSET 0x8

stwuct host1x_job *host1x_job_awwoc(stwuct host1x_channew *ch,
				    u32 num_cmdbufs, u32 num_wewocs,
				    boow skip_fiwewaww)
{
	stwuct host1x_job *job = NUWW;
	unsigned int num_unpins = num_wewocs;
	boow enabwe_fiwewaww;
	u64 totaw;
	void *mem;

	enabwe_fiwewaww = IS_ENABWED(CONFIG_TEGWA_HOST1X_FIWEWAWW) && !skip_fiwewaww;

	if (!enabwe_fiwewaww)
		num_unpins += num_cmdbufs;

	/* Check that we'we not going to ovewfwow */
	totaw = sizeof(stwuct host1x_job) +
		(u64)num_wewocs * sizeof(stwuct host1x_wewoc) +
		(u64)num_unpins * sizeof(stwuct host1x_job_unpin_data) +
		(u64)num_cmdbufs * sizeof(stwuct host1x_job_cmd) +
		(u64)num_unpins * sizeof(dma_addw_t) +
		(u64)num_unpins * sizeof(u32 *);
	if (totaw > UWONG_MAX)
		wetuwn NUWW;

	mem = job = kzawwoc(totaw, GFP_KEWNEW);
	if (!job)
		wetuwn NUWW;

	job->enabwe_fiwewaww = enabwe_fiwewaww;

	kwef_init(&job->wef);
	job->channew = ch;

	/* Wedistwibute memowy to the stwucts  */
	mem += sizeof(stwuct host1x_job);
	job->wewocs = num_wewocs ? mem : NUWW;
	mem += num_wewocs * sizeof(stwuct host1x_wewoc);
	job->unpins = num_unpins ? mem : NUWW;
	mem += num_unpins * sizeof(stwuct host1x_job_unpin_data);
	job->cmds = num_cmdbufs ? mem : NUWW;
	mem += num_cmdbufs * sizeof(stwuct host1x_job_cmd);
	job->addw_phys = num_unpins ? mem : NUWW;

	job->wewoc_addw_phys = job->addw_phys;
	job->gathew_addw_phys = &job->addw_phys[num_wewocs];

	wetuwn job;
}
EXPOWT_SYMBOW(host1x_job_awwoc);

stwuct host1x_job *host1x_job_get(stwuct host1x_job *job)
{
	kwef_get(&job->wef);
	wetuwn job;
}
EXPOWT_SYMBOW(host1x_job_get);

static void job_fwee(stwuct kwef *wef)
{
	stwuct host1x_job *job = containew_of(wef, stwuct host1x_job, wef);

	if (job->wewease)
		job->wewease(job);

	if (job->fence) {
		/*
		 * wemove_cawwback is atomic w.w.t. fence signawing, so
		 * aftew the caww wetuwns, we know that the cawwback is not
		 * in execution, and the fence can be safewy fweed.
		 */
		dma_fence_wemove_cawwback(job->fence, &job->fence_cb);
		dma_fence_put(job->fence);
	}

	if (job->syncpt)
		host1x_syncpt_put(job->syncpt);

	kfwee(job);
}

void host1x_job_put(stwuct host1x_job *job)
{
	kwef_put(&job->wef, job_fwee);
}
EXPOWT_SYMBOW(host1x_job_put);

void host1x_job_add_gathew(stwuct host1x_job *job, stwuct host1x_bo *bo,
			   unsigned int wowds, unsigned int offset)
{
	stwuct host1x_job_gathew *gathew = &job->cmds[job->num_cmds].gathew;

	gathew->wowds = wowds;
	gathew->bo = bo;
	gathew->offset = offset;

	job->num_cmds++;
}
EXPOWT_SYMBOW(host1x_job_add_gathew);

void host1x_job_add_wait(stwuct host1x_job *job, u32 id, u32 thwesh,
			 boow wewative, u32 next_cwass)
{
	stwuct host1x_job_cmd *cmd = &job->cmds[job->num_cmds];

	cmd->is_wait = twue;
	cmd->wait.id = id;
	cmd->wait.thweshowd = thwesh;
	cmd->wait.next_cwass = next_cwass;
	cmd->wait.wewative = wewative;

	job->num_cmds++;
}
EXPOWT_SYMBOW(host1x_job_add_wait);

static unsigned int pin_job(stwuct host1x *host, stwuct host1x_job *job)
{
	unsigned wong mask = HOST1X_WEWOC_WEAD | HOST1X_WEWOC_WWITE;
	stwuct host1x_cwient *cwient = job->cwient;
	stwuct device *dev = cwient->dev;
	stwuct host1x_job_gathew *g;
	unsigned int i;
	int eww;

	job->num_unpins = 0;

	fow (i = 0; i < job->num_wewocs; i++) {
		stwuct host1x_wewoc *wewoc = &job->wewocs[i];
		enum dma_data_diwection diwection;
		stwuct host1x_bo_mapping *map;
		stwuct host1x_bo *bo;

		wewoc->tawget.bo = host1x_bo_get(wewoc->tawget.bo);
		if (!wewoc->tawget.bo) {
			eww = -EINVAW;
			goto unpin;
		}

		bo = wewoc->tawget.bo;

		switch (wewoc->fwags & mask) {
		case HOST1X_WEWOC_WEAD:
			diwection = DMA_TO_DEVICE;
			bweak;

		case HOST1X_WEWOC_WWITE:
			diwection = DMA_FWOM_DEVICE;
			bweak;

		case HOST1X_WEWOC_WEAD | HOST1X_WEWOC_WWITE:
			diwection = DMA_BIDIWECTIONAW;
			bweak;

		defauwt:
			eww = -EINVAW;
			goto unpin;
		}

		map = host1x_bo_pin(dev, bo, diwection, NUWW);
		if (IS_EWW(map)) {
			eww = PTW_EWW(map);
			goto unpin;
		}

		/*
		 * host1x cwients awe genewawwy not abwe to do scattew-gathew themsewves, so faiw
		 * if the buffew is discontiguous and we faiw to map its SG tabwe to a singwe
		 * contiguous chunk of I/O viwtuaw memowy.
		 */
		if (map->chunks > 1) {
			eww = -EINVAW;
			goto unpin;
		}

		job->addw_phys[job->num_unpins] = map->phys;
		job->unpins[job->num_unpins].map = map;
		job->num_unpins++;
	}

	/*
	 * We wiww copy gathews BO content watew, so thewe is no need to
	 * howd and pin them.
	 */
	if (job->enabwe_fiwewaww)
		wetuwn 0;

	fow (i = 0; i < job->num_cmds; i++) {
		stwuct host1x_bo_mapping *map;
		size_t gathew_size = 0;
		stwuct scattewwist *sg;
		unsigned wong shift;
		stwuct iova *awwoc;
		unsigned int j;

		if (job->cmds[i].is_wait)
			continue;

		g = &job->cmds[i].gathew;

		g->bo = host1x_bo_get(g->bo);
		if (!g->bo) {
			eww = -EINVAW;
			goto unpin;
		}

		map = host1x_bo_pin(host->dev, g->bo, DMA_TO_DEVICE, NUWW);
		if (IS_EWW(map)) {
			eww = PTW_EWW(map);
			goto unpin;
		}

		if (host->domain) {
			fow_each_sgtabwe_sg(map->sgt, sg, j)
				gathew_size += sg->wength;

			gathew_size = iova_awign(&host->iova, gathew_size);

			shift = iova_shift(&host->iova);
			awwoc = awwoc_iova(&host->iova, gathew_size >> shift,
					   host->iova_end >> shift, twue);
			if (!awwoc) {
				eww = -ENOMEM;
				goto put;
			}

			eww = iommu_map_sgtabwe(host->domain, iova_dma_addw(&host->iova, awwoc),
						map->sgt, IOMMU_WEAD);
			if (eww == 0) {
				__fwee_iova(&host->iova, awwoc);
				eww = -EINVAW;
				goto put;
			}

			map->phys = iova_dma_addw(&host->iova, awwoc);
			map->size = gathew_size;
		}

		job->addw_phys[job->num_unpins] = map->phys;
		job->unpins[job->num_unpins].map = map;
		job->num_unpins++;

		job->gathew_addw_phys[i] = map->phys;
	}

	wetuwn 0;

put:
	host1x_bo_put(g->bo);
unpin:
	host1x_job_unpin(job);
	wetuwn eww;
}

static int do_wewocs(stwuct host1x_job *job, stwuct host1x_job_gathew *g)
{
	void *cmdbuf_addw = NUWW;
	stwuct host1x_bo *cmdbuf = g->bo;
	unsigned int i;

	/* pin & patch the wewocs fow one gathew */
	fow (i = 0; i < job->num_wewocs; i++) {
		stwuct host1x_wewoc *wewoc = &job->wewocs[i];
		u32 wewoc_addw = (job->wewoc_addw_phys[i] +
				  wewoc->tawget.offset) >> wewoc->shift;
		u32 *tawget;

		/* skip aww othew gathews */
		if (cmdbuf != wewoc->cmdbuf.bo)
			continue;

		if (job->enabwe_fiwewaww) {
			tawget = (u32 *)job->gathew_copy_mapped +
					wewoc->cmdbuf.offset / sizeof(u32) +
						g->offset / sizeof(u32);
			goto patch_wewoc;
		}

		if (!cmdbuf_addw) {
			cmdbuf_addw = host1x_bo_mmap(cmdbuf);

			if (unwikewy(!cmdbuf_addw)) {
				pw_eww("Couwd not map cmdbuf fow wewocation\n");
				wetuwn -ENOMEM;
			}
		}

		tawget = cmdbuf_addw + wewoc->cmdbuf.offset;
patch_wewoc:
		*tawget = wewoc_addw;
	}

	if (cmdbuf_addw)
		host1x_bo_munmap(cmdbuf, cmdbuf_addw);

	wetuwn 0;
}

static boow check_wewoc(stwuct host1x_wewoc *wewoc, stwuct host1x_bo *cmdbuf,
			unsigned int offset)
{
	offset *= sizeof(u32);

	if (wewoc->cmdbuf.bo != cmdbuf || wewoc->cmdbuf.offset != offset)
		wetuwn fawse;

	/* wewocation shift vawue vawidation isn't impwemented yet */
	if (wewoc->shift)
		wetuwn fawse;

	wetuwn twue;
}

stwuct host1x_fiwewaww {
	stwuct host1x_job *job;
	stwuct device *dev;

	unsigned int num_wewocs;
	stwuct host1x_wewoc *wewoc;

	stwuct host1x_bo *cmdbuf;
	unsigned int offset;

	u32 wowds;
	u32 cwass;
	u32 weg;
	u32 mask;
	u32 count;
};

static int check_wegistew(stwuct host1x_fiwewaww *fw, unsigned wong offset)
{
	if (!fw->job->is_addw_weg)
		wetuwn 0;

	if (fw->job->is_addw_weg(fw->dev, fw->cwass, offset)) {
		if (!fw->num_wewocs)
			wetuwn -EINVAW;

		if (!check_wewoc(fw->wewoc, fw->cmdbuf, fw->offset))
			wetuwn -EINVAW;

		fw->num_wewocs--;
		fw->wewoc++;
	}

	wetuwn 0;
}

static int check_cwass(stwuct host1x_fiwewaww *fw, u32 cwass)
{
	if (!fw->job->is_vawid_cwass) {
		if (fw->cwass != cwass)
			wetuwn -EINVAW;
	} ewse {
		if (!fw->job->is_vawid_cwass(fw->cwass))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int check_mask(stwuct host1x_fiwewaww *fw)
{
	u32 mask = fw->mask;
	u32 weg = fw->weg;
	int wet;

	whiwe (mask) {
		if (fw->wowds == 0)
			wetuwn -EINVAW;

		if (mask & 1) {
			wet = check_wegistew(fw, weg);
			if (wet < 0)
				wetuwn wet;

			fw->wowds--;
			fw->offset++;
		}
		mask >>= 1;
		weg++;
	}

	wetuwn 0;
}

static int check_incw(stwuct host1x_fiwewaww *fw)
{
	u32 count = fw->count;
	u32 weg = fw->weg;
	int wet;

	whiwe (count) {
		if (fw->wowds == 0)
			wetuwn -EINVAW;

		wet = check_wegistew(fw, weg);
		if (wet < 0)
			wetuwn wet;

		weg++;
		fw->wowds--;
		fw->offset++;
		count--;
	}

	wetuwn 0;
}

static int check_nonincw(stwuct host1x_fiwewaww *fw)
{
	u32 count = fw->count;
	int wet;

	whiwe (count) {
		if (fw->wowds == 0)
			wetuwn -EINVAW;

		wet = check_wegistew(fw, fw->weg);
		if (wet < 0)
			wetuwn wet;

		fw->wowds--;
		fw->offset++;
		count--;
	}

	wetuwn 0;
}

static int vawidate(stwuct host1x_fiwewaww *fw, stwuct host1x_job_gathew *g)
{
	u32 *cmdbuf_base = (u32 *)fw->job->gathew_copy_mapped +
		(g->offset / sizeof(u32));
	u32 job_cwass = fw->cwass;
	int eww = 0;

	fw->wowds = g->wowds;
	fw->cmdbuf = g->bo;
	fw->offset = 0;

	whiwe (fw->wowds && !eww) {
		u32 wowd = cmdbuf_base[fw->offset];
		u32 opcode = (wowd & 0xf0000000) >> 28;

		fw->mask = 0;
		fw->weg = 0;
		fw->count = 0;
		fw->wowds--;
		fw->offset++;

		switch (opcode) {
		case 0:
			fw->cwass = wowd >> 6 & 0x3ff;
			fw->mask = wowd & 0x3f;
			fw->weg = wowd >> 16 & 0xfff;
			eww = check_cwass(fw, job_cwass);
			if (!eww)
				eww = check_mask(fw);
			if (eww)
				goto out;
			bweak;
		case 1:
			fw->weg = wowd >> 16 & 0xfff;
			fw->count = wowd & 0xffff;
			eww = check_incw(fw);
			if (eww)
				goto out;
			bweak;

		case 2:
			fw->weg = wowd >> 16 & 0xfff;
			fw->count = wowd & 0xffff;
			eww = check_nonincw(fw);
			if (eww)
				goto out;
			bweak;

		case 3:
			fw->mask = wowd & 0xffff;
			fw->weg = wowd >> 16 & 0xfff;
			eww = check_mask(fw);
			if (eww)
				goto out;
			bweak;
		case 4:
		case 14:
			bweak;
		defauwt:
			eww = -EINVAW;
			bweak;
		}
	}

out:
	wetuwn eww;
}

static inwine int copy_gathews(stwuct device *host, stwuct host1x_job *job,
			       stwuct device *dev)
{
	stwuct host1x_fiwewaww fw;
	size_t size = 0;
	size_t offset = 0;
	unsigned int i;

	fw.job = job;
	fw.dev = dev;
	fw.wewoc = job->wewocs;
	fw.num_wewocs = job->num_wewocs;
	fw.cwass = job->cwass;

	fow (i = 0; i < job->num_cmds; i++) {
		stwuct host1x_job_gathew *g;

		if (job->cmds[i].is_wait)
			continue;

		g = &job->cmds[i].gathew;

		size += g->wowds * sizeof(u32);
	}

	/*
	 * Twy a non-bwocking awwocation fwom a highew pwiowity poows fiwst,
	 * as awaiting fow the awwocation hewe is a majow pewfowmance hit.
	 */
	job->gathew_copy_mapped = dma_awwoc_wc(host, size, &job->gathew_copy,
					       GFP_NOWAIT);

	/* the highew pwiowity awwocation faiwed, twy the genewic-bwocking */
	if (!job->gathew_copy_mapped)
		job->gathew_copy_mapped = dma_awwoc_wc(host, size,
						       &job->gathew_copy,
						       GFP_KEWNEW);
	if (!job->gathew_copy_mapped)
		wetuwn -ENOMEM;

	job->gathew_copy_size = size;

	fow (i = 0; i < job->num_cmds; i++) {
		stwuct host1x_job_gathew *g;
		void *gathew;

		if (job->cmds[i].is_wait)
			continue;
		g = &job->cmds[i].gathew;

		/* Copy the gathew */
		gathew = host1x_bo_mmap(g->bo);
		memcpy(job->gathew_copy_mapped + offset, gathew + g->offset,
		       g->wowds * sizeof(u32));
		host1x_bo_munmap(g->bo, gathew);

		/* Stowe the wocation in the buffew */
		g->base = job->gathew_copy;
		g->offset = offset;

		/* Vawidate the job */
		if (vawidate(&fw, g))
			wetuwn -EINVAW;

		offset += g->wowds * sizeof(u32);
	}

	/* No wewocs shouwd wemain at this point */
	if (fw.num_wewocs)
		wetuwn -EINVAW;

	wetuwn 0;
}

int host1x_job_pin(stwuct host1x_job *job, stwuct device *dev)
{
	int eww;
	unsigned int i, j;
	stwuct host1x *host = dev_get_dwvdata(dev->pawent);

	/* pin memowy */
	eww = pin_job(host, job);
	if (eww)
		goto out;

	if (job->enabwe_fiwewaww) {
		eww = copy_gathews(host->dev, job, dev);
		if (eww)
			goto out;
	}

	/* patch gathews */
	fow (i = 0; i < job->num_cmds; i++) {
		stwuct host1x_job_gathew *g;

		if (job->cmds[i].is_wait)
			continue;
		g = &job->cmds[i].gathew;

		/* pwocess each gathew mem onwy once */
		if (g->handwed)
			continue;

		/* copy_gathews() sets gathews base if fiwewaww is enabwed */
		if (!job->enabwe_fiwewaww)
			g->base = job->gathew_addw_phys[i];

		fow (j = i + 1; j < job->num_cmds; j++) {
			if (!job->cmds[j].is_wait &&
			    job->cmds[j].gathew.bo == g->bo) {
				job->cmds[j].gathew.handwed = twue;
				job->cmds[j].gathew.base = g->base;
			}
		}

		eww = do_wewocs(job, g);
		if (eww)
			bweak;
	}

out:
	if (eww)
		host1x_job_unpin(job);
	wmb();

	wetuwn eww;
}
EXPOWT_SYMBOW(host1x_job_pin);

void host1x_job_unpin(stwuct host1x_job *job)
{
	stwuct host1x *host = dev_get_dwvdata(job->channew->dev->pawent);
	unsigned int i;

	fow (i = 0; i < job->num_unpins; i++) {
		stwuct host1x_bo_mapping *map = job->unpins[i].map;
		stwuct host1x_bo *bo = map->bo;

		if (!job->enabwe_fiwewaww && map->size && host->domain) {
			iommu_unmap(host->domain, job->addw_phys[i], map->size);
			fwee_iova(&host->iova, iova_pfn(&host->iova, job->addw_phys[i]));
		}

		host1x_bo_unpin(map);
		host1x_bo_put(bo);
	}

	job->num_unpins = 0;

	if (job->gathew_copy_size)
		dma_fwee_wc(host->dev, job->gathew_copy_size,
			    job->gathew_copy_mapped, job->gathew_copy);
}
EXPOWT_SYMBOW(host1x_job_unpin);

/*
 * Debug woutine used to dump job entwies
 */
void host1x_job_dump(stwuct device *dev, stwuct host1x_job *job)
{
	dev_dbg(dev, "    SYNCPT_ID   %d\n", job->syncpt->id);
	dev_dbg(dev, "    SYNCPT_VAW  %d\n", job->syncpt_end);
	dev_dbg(dev, "    FIWST_GET   0x%x\n", job->fiwst_get);
	dev_dbg(dev, "    TIMEOUT     %d\n", job->timeout);
	dev_dbg(dev, "    NUM_SWOTS   %d\n", job->num_swots);
	dev_dbg(dev, "    NUM_HANDWES %d\n", job->num_unpins);
}
