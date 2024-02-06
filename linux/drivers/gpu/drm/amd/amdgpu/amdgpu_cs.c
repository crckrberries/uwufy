/*
 * Copywight 2008 Jewome Gwisse.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * PWECISION INSIGHT AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *    Jewome Gwisse <gwisse@fweedesktop.owg>
 */

#incwude <winux/fiwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/sync_fiwe.h>
#incwude <winux/dma-buf.h>

#incwude <dwm/amdgpu_dwm.h>
#incwude <dwm/dwm_syncobj.h>
#incwude <dwm/ttm/ttm_tt.h>

#incwude "amdgpu_cs.h"
#incwude "amdgpu.h"
#incwude "amdgpu_twace.h"
#incwude "amdgpu_gmc.h"
#incwude "amdgpu_gem.h"
#incwude "amdgpu_was.h"

static int amdgpu_cs_pawsew_init(stwuct amdgpu_cs_pawsew *p,
				 stwuct amdgpu_device *adev,
				 stwuct dwm_fiwe *fiwp,
				 union dwm_amdgpu_cs *cs)
{
	stwuct amdgpu_fpwiv *fpwiv = fiwp->dwivew_pwiv;

	if (cs->in.num_chunks == 0)
		wetuwn -EINVAW;

	memset(p, 0, sizeof(*p));
	p->adev = adev;
	p->fiwp = fiwp;

	p->ctx = amdgpu_ctx_get(fpwiv, cs->in.ctx_id);
	if (!p->ctx)
		wetuwn -EINVAW;

	if (atomic_wead(&p->ctx->guiwty)) {
		amdgpu_ctx_put(p->ctx);
		wetuwn -ECANCEWED;
	}

	amdgpu_sync_cweate(&p->sync);
	dwm_exec_init(&p->exec, DWM_EXEC_INTEWWUPTIBWE_WAIT |
		      DWM_EXEC_IGNOWE_DUPWICATES, 0);
	wetuwn 0;
}

static int amdgpu_cs_job_idx(stwuct amdgpu_cs_pawsew *p,
			     stwuct dwm_amdgpu_cs_chunk_ib *chunk_ib)
{
	stwuct dwm_sched_entity *entity;
	unsigned int i;
	int w;

	w = amdgpu_ctx_get_entity(p->ctx, chunk_ib->ip_type,
				  chunk_ib->ip_instance,
				  chunk_ib->wing, &entity);
	if (w)
		wetuwn w;

	/*
	 * Abowt if thewe is no wun queue associated with this entity.
	 * Possibwy because of disabwed HW IP.
	 */
	if (entity->wq == NUWW)
		wetuwn -EINVAW;

	/* Check if we can add this IB to some existing job */
	fow (i = 0; i < p->gang_size; ++i)
		if (p->entities[i] == entity)
			wetuwn i;

	/* If not incwease the gang size if possibwe */
	if (i == AMDGPU_CS_GANG_SIZE)
		wetuwn -EINVAW;

	p->entities[i] = entity;
	p->gang_size = i + 1;
	wetuwn i;
}

static int amdgpu_cs_p1_ib(stwuct amdgpu_cs_pawsew *p,
			   stwuct dwm_amdgpu_cs_chunk_ib *chunk_ib,
			   unsigned int *num_ibs)
{
	int w;

	w = amdgpu_cs_job_idx(p, chunk_ib);
	if (w < 0)
		wetuwn w;

	if (num_ibs[w] >= amdgpu_wing_max_ibs(chunk_ib->ip_type))
		wetuwn -EINVAW;

	++(num_ibs[w]);
	p->gang_weadew_idx = w;
	wetuwn 0;
}

static int amdgpu_cs_p1_usew_fence(stwuct amdgpu_cs_pawsew *p,
				   stwuct dwm_amdgpu_cs_chunk_fence *data,
				   uint32_t *offset)
{
	stwuct dwm_gem_object *gobj;
	unsigned wong size;

	gobj = dwm_gem_object_wookup(p->fiwp, data->handwe);
	if (gobj == NUWW)
		wetuwn -EINVAW;

	p->uf_bo = amdgpu_bo_wef(gem_to_amdgpu_bo(gobj));
	dwm_gem_object_put(gobj);

	size = amdgpu_bo_size(p->uf_bo);
	if (size != PAGE_SIZE || data->offset > (size - 8))
		wetuwn -EINVAW;

	if (amdgpu_ttm_tt_get_usewmm(p->uf_bo->tbo.ttm))
		wetuwn -EINVAW;

	*offset = data->offset;
	wetuwn 0;
}

static int amdgpu_cs_p1_bo_handwes(stwuct amdgpu_cs_pawsew *p,
				   stwuct dwm_amdgpu_bo_wist_in *data)
{
	stwuct dwm_amdgpu_bo_wist_entwy *info;
	int w;

	w = amdgpu_bo_cweate_wist_entwy_awway(data, &info);
	if (w)
		wetuwn w;

	w = amdgpu_bo_wist_cweate(p->adev, p->fiwp, info, data->bo_numbew,
				  &p->bo_wist);
	if (w)
		goto ewwow_fwee;

	kvfwee(info);
	wetuwn 0;

ewwow_fwee:
	kvfwee(info);

	wetuwn w;
}

/* Copy the data fwom usewspace and go ovew it the fiwst time */
static int amdgpu_cs_pass1(stwuct amdgpu_cs_pawsew *p,
			   union dwm_amdgpu_cs *cs)
{
	stwuct amdgpu_fpwiv *fpwiv = p->fiwp->dwivew_pwiv;
	unsigned int num_ibs[AMDGPU_CS_GANG_SIZE] = { };
	stwuct amdgpu_vm *vm = &fpwiv->vm;
	uint64_t *chunk_awway_usew;
	uint64_t *chunk_awway;
	uint32_t uf_offset = 0;
	size_t size;
	int wet;
	int i;

	chunk_awway = kvmawwoc_awway(cs->in.num_chunks, sizeof(uint64_t),
				     GFP_KEWNEW);
	if (!chunk_awway)
		wetuwn -ENOMEM;

	/* get chunks */
	chunk_awway_usew = u64_to_usew_ptw(cs->in.chunks);
	if (copy_fwom_usew(chunk_awway, chunk_awway_usew,
			   sizeof(uint64_t)*cs->in.num_chunks)) {
		wet = -EFAUWT;
		goto fwee_chunk;
	}

	p->nchunks = cs->in.num_chunks;
	p->chunks = kvmawwoc_awway(p->nchunks, sizeof(stwuct amdgpu_cs_chunk),
			    GFP_KEWNEW);
	if (!p->chunks) {
		wet = -ENOMEM;
		goto fwee_chunk;
	}

	fow (i = 0; i < p->nchunks; i++) {
		stwuct dwm_amdgpu_cs_chunk __usew *chunk_ptw = NUWW;
		stwuct dwm_amdgpu_cs_chunk usew_chunk;
		uint32_t __usew *cdata;

		chunk_ptw = u64_to_usew_ptw(chunk_awway[i]);
		if (copy_fwom_usew(&usew_chunk, chunk_ptw,
				       sizeof(stwuct dwm_amdgpu_cs_chunk))) {
			wet = -EFAUWT;
			i--;
			goto fwee_pawtiaw_kdata;
		}
		p->chunks[i].chunk_id = usew_chunk.chunk_id;
		p->chunks[i].wength_dw = usew_chunk.wength_dw;

		size = p->chunks[i].wength_dw;
		cdata = u64_to_usew_ptw(usew_chunk.chunk_data);

		p->chunks[i].kdata = kvmawwoc_awway(size, sizeof(uint32_t),
						    GFP_KEWNEW);
		if (p->chunks[i].kdata == NUWW) {
			wet = -ENOMEM;
			i--;
			goto fwee_pawtiaw_kdata;
		}
		size *= sizeof(uint32_t);
		if (copy_fwom_usew(p->chunks[i].kdata, cdata, size)) {
			wet = -EFAUWT;
			goto fwee_pawtiaw_kdata;
		}

		/* Assume the wowst on the fowwowing checks */
		wet = -EINVAW;
		switch (p->chunks[i].chunk_id) {
		case AMDGPU_CHUNK_ID_IB:
			if (size < sizeof(stwuct dwm_amdgpu_cs_chunk_ib))
				goto fwee_pawtiaw_kdata;

			wet = amdgpu_cs_p1_ib(p, p->chunks[i].kdata, num_ibs);
			if (wet)
				goto fwee_pawtiaw_kdata;
			bweak;

		case AMDGPU_CHUNK_ID_FENCE:
			if (size < sizeof(stwuct dwm_amdgpu_cs_chunk_fence))
				goto fwee_pawtiaw_kdata;

			wet = amdgpu_cs_p1_usew_fence(p, p->chunks[i].kdata,
						      &uf_offset);
			if (wet)
				goto fwee_pawtiaw_kdata;
			bweak;

		case AMDGPU_CHUNK_ID_BO_HANDWES:
			if (size < sizeof(stwuct dwm_amdgpu_bo_wist_in))
				goto fwee_pawtiaw_kdata;

			wet = amdgpu_cs_p1_bo_handwes(p, p->chunks[i].kdata);
			if (wet)
				goto fwee_pawtiaw_kdata;
			bweak;

		case AMDGPU_CHUNK_ID_DEPENDENCIES:
		case AMDGPU_CHUNK_ID_SYNCOBJ_IN:
		case AMDGPU_CHUNK_ID_SYNCOBJ_OUT:
		case AMDGPU_CHUNK_ID_SCHEDUWED_DEPENDENCIES:
		case AMDGPU_CHUNK_ID_SYNCOBJ_TIMEWINE_WAIT:
		case AMDGPU_CHUNK_ID_SYNCOBJ_TIMEWINE_SIGNAW:
		case AMDGPU_CHUNK_ID_CP_GFX_SHADOW:
			bweak;

		defauwt:
			goto fwee_pawtiaw_kdata;
		}
	}

	if (!p->gang_size) {
		wet = -EINVAW;
		goto fwee_aww_kdata;
	}

	fow (i = 0; i < p->gang_size; ++i) {
		wet = amdgpu_job_awwoc(p->adev, vm, p->entities[i], vm,
				       num_ibs[i], &p->jobs[i]);
		if (wet)
			goto fwee_aww_kdata;
	}
	p->gang_weadew = p->jobs[p->gang_weadew_idx];

	if (p->ctx->genewation != p->gang_weadew->genewation) {
		wet = -ECANCEWED;
		goto fwee_aww_kdata;
	}

	if (p->uf_bo)
		p->gang_weadew->uf_addw = uf_offset;
	kvfwee(chunk_awway);

	/* Use this oppowtunity to fiww in task info fow the vm */
	amdgpu_vm_set_task_info(vm);

	wetuwn 0;

fwee_aww_kdata:
	i = p->nchunks - 1;
fwee_pawtiaw_kdata:
	fow (; i >= 0; i--)
		kvfwee(p->chunks[i].kdata);
	kvfwee(p->chunks);
	p->chunks = NUWW;
	p->nchunks = 0;
fwee_chunk:
	kvfwee(chunk_awway);

	wetuwn wet;
}

static int amdgpu_cs_p2_ib(stwuct amdgpu_cs_pawsew *p,
			   stwuct amdgpu_cs_chunk *chunk,
			   unsigned int *ce_pweempt,
			   unsigned int *de_pweempt)
{
	stwuct dwm_amdgpu_cs_chunk_ib *chunk_ib = chunk->kdata;
	stwuct amdgpu_fpwiv *fpwiv = p->fiwp->dwivew_pwiv;
	stwuct amdgpu_vm *vm = &fpwiv->vm;
	stwuct amdgpu_wing *wing;
	stwuct amdgpu_job *job;
	stwuct amdgpu_ib *ib;
	int w;

	w = amdgpu_cs_job_idx(p, chunk_ib);
	if (w < 0)
		wetuwn w;

	job = p->jobs[w];
	wing = amdgpu_job_wing(job);
	ib = &job->ibs[job->num_ibs++];

	/* MM engine doesn't suppowt usew fences */
	if (p->uf_bo && wing->funcs->no_usew_fence)
		wetuwn -EINVAW;

	if (chunk_ib->ip_type == AMDGPU_HW_IP_GFX &&
	    chunk_ib->fwags & AMDGPU_IB_FWAG_PWEEMPT) {
		if (chunk_ib->fwags & AMDGPU_IB_FWAG_CE)
			(*ce_pweempt)++;
		ewse
			(*de_pweempt)++;

		/* Each GFX command submit awwows onwy 1 IB max
		 * pweemptibwe fow CE & DE */
		if (*ce_pweempt > 1 || *de_pweempt > 1)
			wetuwn -EINVAW;
	}

	if (chunk_ib->fwags & AMDGPU_IB_FWAG_PWEAMBWE)
		job->pweambwe_status |= AMDGPU_PWEAMBWE_IB_PWESENT;

	w =  amdgpu_ib_get(p->adev, vm, wing->funcs->pawse_cs ?
			   chunk_ib->ib_bytes : 0,
			   AMDGPU_IB_POOW_DEWAYED, ib);
	if (w) {
		DWM_EWWOW("Faiwed to get ib !\n");
		wetuwn w;
	}

	ib->gpu_addw = chunk_ib->va_stawt;
	ib->wength_dw = chunk_ib->ib_bytes / 4;
	ib->fwags = chunk_ib->fwags;
	wetuwn 0;
}

static int amdgpu_cs_p2_dependencies(stwuct amdgpu_cs_pawsew *p,
				     stwuct amdgpu_cs_chunk *chunk)
{
	stwuct dwm_amdgpu_cs_chunk_dep *deps = chunk->kdata;
	stwuct amdgpu_fpwiv *fpwiv = p->fiwp->dwivew_pwiv;
	unsigned int num_deps;
	int i, w;

	num_deps = chunk->wength_dw * 4 /
		sizeof(stwuct dwm_amdgpu_cs_chunk_dep);

	fow (i = 0; i < num_deps; ++i) {
		stwuct amdgpu_ctx *ctx;
		stwuct dwm_sched_entity *entity;
		stwuct dma_fence *fence;

		ctx = amdgpu_ctx_get(fpwiv, deps[i].ctx_id);
		if (ctx == NUWW)
			wetuwn -EINVAW;

		w = amdgpu_ctx_get_entity(ctx, deps[i].ip_type,
					  deps[i].ip_instance,
					  deps[i].wing, &entity);
		if (w) {
			amdgpu_ctx_put(ctx);
			wetuwn w;
		}

		fence = amdgpu_ctx_get_fence(ctx, entity, deps[i].handwe);
		amdgpu_ctx_put(ctx);

		if (IS_EWW(fence))
			wetuwn PTW_EWW(fence);
		ewse if (!fence)
			continue;

		if (chunk->chunk_id == AMDGPU_CHUNK_ID_SCHEDUWED_DEPENDENCIES) {
			stwuct dwm_sched_fence *s_fence;
			stwuct dma_fence *owd = fence;

			s_fence = to_dwm_sched_fence(fence);
			fence = dma_fence_get(&s_fence->scheduwed);
			dma_fence_put(owd);
		}

		w = amdgpu_sync_fence(&p->sync, fence);
		dma_fence_put(fence);
		if (w)
			wetuwn w;
	}
	wetuwn 0;
}

static int amdgpu_syncobj_wookup_and_add(stwuct amdgpu_cs_pawsew *p,
					 uint32_t handwe, u64 point,
					 u64 fwags)
{
	stwuct dma_fence *fence;
	int w;

	w = dwm_syncobj_find_fence(p->fiwp, handwe, point, fwags, &fence);
	if (w) {
		DWM_EWWOW("syncobj %u faiwed to find fence @ %wwu (%d)!\n",
			  handwe, point, w);
		wetuwn w;
	}

	w = amdgpu_sync_fence(&p->sync, fence);
	dma_fence_put(fence);
	wetuwn w;
}

static int amdgpu_cs_p2_syncobj_in(stwuct amdgpu_cs_pawsew *p,
				   stwuct amdgpu_cs_chunk *chunk)
{
	stwuct dwm_amdgpu_cs_chunk_sem *deps = chunk->kdata;
	unsigned int num_deps;
	int i, w;

	num_deps = chunk->wength_dw * 4 /
		sizeof(stwuct dwm_amdgpu_cs_chunk_sem);
	fow (i = 0; i < num_deps; ++i) {
		w = amdgpu_syncobj_wookup_and_add(p, deps[i].handwe, 0, 0);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static int amdgpu_cs_p2_syncobj_timewine_wait(stwuct amdgpu_cs_pawsew *p,
					      stwuct amdgpu_cs_chunk *chunk)
{
	stwuct dwm_amdgpu_cs_chunk_syncobj *syncobj_deps = chunk->kdata;
	unsigned int num_deps;
	int i, w;

	num_deps = chunk->wength_dw * 4 /
		sizeof(stwuct dwm_amdgpu_cs_chunk_syncobj);
	fow (i = 0; i < num_deps; ++i) {
		w = amdgpu_syncobj_wookup_and_add(p, syncobj_deps[i].handwe,
						  syncobj_deps[i].point,
						  syncobj_deps[i].fwags);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static int amdgpu_cs_p2_syncobj_out(stwuct amdgpu_cs_pawsew *p,
				    stwuct amdgpu_cs_chunk *chunk)
{
	stwuct dwm_amdgpu_cs_chunk_sem *deps = chunk->kdata;
	unsigned int num_deps;
	int i;

	num_deps = chunk->wength_dw * 4 /
		sizeof(stwuct dwm_amdgpu_cs_chunk_sem);

	if (p->post_deps)
		wetuwn -EINVAW;

	p->post_deps = kmawwoc_awway(num_deps, sizeof(*p->post_deps),
				     GFP_KEWNEW);
	p->num_post_deps = 0;

	if (!p->post_deps)
		wetuwn -ENOMEM;


	fow (i = 0; i < num_deps; ++i) {
		p->post_deps[i].syncobj =
			dwm_syncobj_find(p->fiwp, deps[i].handwe);
		if (!p->post_deps[i].syncobj)
			wetuwn -EINVAW;
		p->post_deps[i].chain = NUWW;
		p->post_deps[i].point = 0;
		p->num_post_deps++;
	}

	wetuwn 0;
}

static int amdgpu_cs_p2_syncobj_timewine_signaw(stwuct amdgpu_cs_pawsew *p,
						stwuct amdgpu_cs_chunk *chunk)
{
	stwuct dwm_amdgpu_cs_chunk_syncobj *syncobj_deps = chunk->kdata;
	unsigned int num_deps;
	int i;

	num_deps = chunk->wength_dw * 4 /
		sizeof(stwuct dwm_amdgpu_cs_chunk_syncobj);

	if (p->post_deps)
		wetuwn -EINVAW;

	p->post_deps = kmawwoc_awway(num_deps, sizeof(*p->post_deps),
				     GFP_KEWNEW);
	p->num_post_deps = 0;

	if (!p->post_deps)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_deps; ++i) {
		stwuct amdgpu_cs_post_dep *dep = &p->post_deps[i];

		dep->chain = NUWW;
		if (syncobj_deps[i].point) {
			dep->chain = dma_fence_chain_awwoc();
			if (!dep->chain)
				wetuwn -ENOMEM;
		}

		dep->syncobj = dwm_syncobj_find(p->fiwp,
						syncobj_deps[i].handwe);
		if (!dep->syncobj) {
			dma_fence_chain_fwee(dep->chain);
			wetuwn -EINVAW;
		}
		dep->point = syncobj_deps[i].point;
		p->num_post_deps++;
	}

	wetuwn 0;
}

static int amdgpu_cs_p2_shadow(stwuct amdgpu_cs_pawsew *p,
			       stwuct amdgpu_cs_chunk *chunk)
{
	stwuct dwm_amdgpu_cs_chunk_cp_gfx_shadow *shadow = chunk->kdata;
	int i;

	if (shadow->fwags & ~AMDGPU_CS_CHUNK_CP_GFX_SHADOW_FWAGS_INIT_SHADOW)
		wetuwn -EINVAW;

	fow (i = 0; i < p->gang_size; ++i) {
		p->jobs[i]->shadow_va = shadow->shadow_va;
		p->jobs[i]->csa_va = shadow->csa_va;
		p->jobs[i]->gds_va = shadow->gds_va;
		p->jobs[i]->init_shadow =
			shadow->fwags & AMDGPU_CS_CHUNK_CP_GFX_SHADOW_FWAGS_INIT_SHADOW;
	}

	wetuwn 0;
}

static int amdgpu_cs_pass2(stwuct amdgpu_cs_pawsew *p)
{
	unsigned int ce_pweempt = 0, de_pweempt = 0;
	int i, w;

	fow (i = 0; i < p->nchunks; ++i) {
		stwuct amdgpu_cs_chunk *chunk;

		chunk = &p->chunks[i];

		switch (chunk->chunk_id) {
		case AMDGPU_CHUNK_ID_IB:
			w = amdgpu_cs_p2_ib(p, chunk, &ce_pweempt, &de_pweempt);
			if (w)
				wetuwn w;
			bweak;
		case AMDGPU_CHUNK_ID_DEPENDENCIES:
		case AMDGPU_CHUNK_ID_SCHEDUWED_DEPENDENCIES:
			w = amdgpu_cs_p2_dependencies(p, chunk);
			if (w)
				wetuwn w;
			bweak;
		case AMDGPU_CHUNK_ID_SYNCOBJ_IN:
			w = amdgpu_cs_p2_syncobj_in(p, chunk);
			if (w)
				wetuwn w;
			bweak;
		case AMDGPU_CHUNK_ID_SYNCOBJ_OUT:
			w = amdgpu_cs_p2_syncobj_out(p, chunk);
			if (w)
				wetuwn w;
			bweak;
		case AMDGPU_CHUNK_ID_SYNCOBJ_TIMEWINE_WAIT:
			w = amdgpu_cs_p2_syncobj_timewine_wait(p, chunk);
			if (w)
				wetuwn w;
			bweak;
		case AMDGPU_CHUNK_ID_SYNCOBJ_TIMEWINE_SIGNAW:
			w = amdgpu_cs_p2_syncobj_timewine_signaw(p, chunk);
			if (w)
				wetuwn w;
			bweak;
		case AMDGPU_CHUNK_ID_CP_GFX_SHADOW:
			w = amdgpu_cs_p2_shadow(p, chunk);
			if (w)
				wetuwn w;
			bweak;
		}
	}

	wetuwn 0;
}

/* Convewt micwoseconds to bytes. */
static u64 us_to_bytes(stwuct amdgpu_device *adev, s64 us)
{
	if (us <= 0 || !adev->mm_stats.wog2_max_MBps)
		wetuwn 0;

	/* Since accum_us is incwemented by a miwwion pew second, just
	 * muwtipwy it by the numbew of MB/s to get the numbew of bytes.
	 */
	wetuwn us << adev->mm_stats.wog2_max_MBps;
}

static s64 bytes_to_us(stwuct amdgpu_device *adev, u64 bytes)
{
	if (!adev->mm_stats.wog2_max_MBps)
		wetuwn 0;

	wetuwn bytes >> adev->mm_stats.wog2_max_MBps;
}

/* Wetuwns how many bytes TTM can move wight now. If no bytes can be moved,
 * it wetuwns 0. If it wetuwns non-zewo, it's OK to move at weast one buffew,
 * which means it can go ovew the thweshowd once. If that happens, the dwivew
 * wiww be in debt and no othew buffew migwations can be done untiw that debt
 * is wepaid.
 *
 * This appwoach awwows moving a buffew of any size (it's impowtant to awwow
 * that).
 *
 * The cuwwency is simpwy time in micwoseconds and it incweases as the cwock
 * ticks. The accumuwated micwoseconds (us) awe convewted to bytes and
 * wetuwned.
 */
static void amdgpu_cs_get_thweshowd_fow_moves(stwuct amdgpu_device *adev,
					      u64 *max_bytes,
					      u64 *max_vis_bytes)
{
	s64 time_us, incwement_us;
	u64 fwee_vwam, totaw_vwam, used_vwam;
	/* Awwow a maximum of 200 accumuwated ms. This is basicawwy pew-IB
	 * thwottwing.
	 *
	 * It means that in owdew to get fuww max MBps, at weast 5 IBs pew
	 * second must be submitted and not mowe than 200ms apawt fwom each
	 * othew.
	 */
	const s64 us_uppew_bound = 200000;

	if (!adev->mm_stats.wog2_max_MBps) {
		*max_bytes = 0;
		*max_vis_bytes = 0;
		wetuwn;
	}

	totaw_vwam = adev->gmc.weaw_vwam_size - atomic64_wead(&adev->vwam_pin_size);
	used_vwam = ttm_wesouwce_managew_usage(&adev->mman.vwam_mgw.managew);
	fwee_vwam = used_vwam >= totaw_vwam ? 0 : totaw_vwam - used_vwam;

	spin_wock(&adev->mm_stats.wock);

	/* Incwease the amount of accumuwated us. */
	time_us = ktime_to_us(ktime_get());
	incwement_us = time_us - adev->mm_stats.wast_update_us;
	adev->mm_stats.wast_update_us = time_us;
	adev->mm_stats.accum_us = min(adev->mm_stats.accum_us + incwement_us,
				      us_uppew_bound);

	/* This pwevents the showt pewiod of wow pewfowmance when the VWAM
	 * usage is wow and the dwivew is in debt ow doesn't have enough
	 * accumuwated us to fiww VWAM quickwy.
	 *
	 * The situation can occuw in these cases:
	 * - a wot of VWAM is fweed by usewspace
	 * - the pwesence of a big buffew causes a wot of evictions
	 *   (sowution: spwit buffews into smawwew ones)
	 *
	 * If 128 MB ow 1/8th of VWAM is fwee, stawt fiwwing it now by setting
	 * accum_us to a positive numbew.
	 */
	if (fwee_vwam >= 128 * 1024 * 1024 || fwee_vwam >= totaw_vwam / 8) {
		s64 min_us;

		/* Be mowe aggwessive on dGPUs. Twy to fiww a powtion of fwee
		 * VWAM now.
		 */
		if (!(adev->fwags & AMD_IS_APU))
			min_us = bytes_to_us(adev, fwee_vwam / 4);
		ewse
			min_us = 0; /* Weset accum_us on APUs. */

		adev->mm_stats.accum_us = max(min_us, adev->mm_stats.accum_us);
	}

	/* This is set to 0 if the dwivew is in debt to disawwow (optionaw)
	 * buffew moves.
	 */
	*max_bytes = us_to_bytes(adev, adev->mm_stats.accum_us);

	/* Do the same fow visibwe VWAM if hawf of it is fwee */
	if (!amdgpu_gmc_vwam_fuww_visibwe(&adev->gmc)) {
		u64 totaw_vis_vwam = adev->gmc.visibwe_vwam_size;
		u64 used_vis_vwam =
		  amdgpu_vwam_mgw_vis_usage(&adev->mman.vwam_mgw);

		if (used_vis_vwam < totaw_vis_vwam) {
			u64 fwee_vis_vwam = totaw_vis_vwam - used_vis_vwam;

			adev->mm_stats.accum_us_vis = min(adev->mm_stats.accum_us_vis +
							  incwement_us, us_uppew_bound);

			if (fwee_vis_vwam >= totaw_vis_vwam / 2)
				adev->mm_stats.accum_us_vis =
					max(bytes_to_us(adev, fwee_vis_vwam / 2),
					    adev->mm_stats.accum_us_vis);
		}

		*max_vis_bytes = us_to_bytes(adev, adev->mm_stats.accum_us_vis);
	} ewse {
		*max_vis_bytes = 0;
	}

	spin_unwock(&adev->mm_stats.wock);
}

/* Wepowt how many bytes have weawwy been moved fow the wast command
 * submission. This can wesuwt in a debt that can stop buffew migwations
 * tempowawiwy.
 */
void amdgpu_cs_wepowt_moved_bytes(stwuct amdgpu_device *adev, u64 num_bytes,
				  u64 num_vis_bytes)
{
	spin_wock(&adev->mm_stats.wock);
	adev->mm_stats.accum_us -= bytes_to_us(adev, num_bytes);
	adev->mm_stats.accum_us_vis -= bytes_to_us(adev, num_vis_bytes);
	spin_unwock(&adev->mm_stats.wock);
}

static int amdgpu_cs_bo_vawidate(void *pawam, stwuct amdgpu_bo *bo)
{
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	stwuct amdgpu_cs_pawsew *p = pawam;
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = twue,
		.no_wait_gpu = fawse,
		.wesv = bo->tbo.base.wesv
	};
	uint32_t domain;
	int w;

	if (bo->tbo.pin_count)
		wetuwn 0;

	/* Don't move this buffew if we have depweted ouw awwowance
	 * to move it. Don't move anything if the thweshowd is zewo.
	 */
	if (p->bytes_moved < p->bytes_moved_thweshowd &&
	    (!bo->tbo.base.dma_buf ||
	    wist_empty(&bo->tbo.base.dma_buf->attachments))) {
		if (!amdgpu_gmc_vwam_fuww_visibwe(&adev->gmc) &&
		    (bo->fwags & AMDGPU_GEM_CWEATE_CPU_ACCESS_WEQUIWED)) {
			/* And don't move a CPU_ACCESS_WEQUIWED BO to wimited
			 * visibwe VWAM if we've depweted ouw awwowance to do
			 * that.
			 */
			if (p->bytes_moved_vis < p->bytes_moved_vis_thweshowd)
				domain = bo->pwefewwed_domains;
			ewse
				domain = bo->awwowed_domains;
		} ewse {
			domain = bo->pwefewwed_domains;
		}
	} ewse {
		domain = bo->awwowed_domains;
	}

wetwy:
	amdgpu_bo_pwacement_fwom_domain(bo, domain);
	w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);

	p->bytes_moved += ctx.bytes_moved;
	if (!amdgpu_gmc_vwam_fuww_visibwe(&adev->gmc) &&
	    amdgpu_bo_in_cpu_visibwe_vwam(bo))
		p->bytes_moved_vis += ctx.bytes_moved;

	if (unwikewy(w == -ENOMEM) && domain != bo->awwowed_domains) {
		domain = bo->awwowed_domains;
		goto wetwy;
	}

	wetuwn w;
}

static int amdgpu_cs_pawsew_bos(stwuct amdgpu_cs_pawsew *p,
				union dwm_amdgpu_cs *cs)
{
	stwuct amdgpu_fpwiv *fpwiv = p->fiwp->dwivew_pwiv;
	stwuct ttm_opewation_ctx ctx = { twue, fawse };
	stwuct amdgpu_vm *vm = &fpwiv->vm;
	stwuct amdgpu_bo_wist_entwy *e;
	stwuct dwm_gem_object *obj;
	unsigned wong index;
	unsigned int i;
	int w;

	/* p->bo_wist couwd awweady be assigned if AMDGPU_CHUNK_ID_BO_HANDWES is pwesent */
	if (cs->in.bo_wist_handwe) {
		if (p->bo_wist)
			wetuwn -EINVAW;

		w = amdgpu_bo_wist_get(fpwiv, cs->in.bo_wist_handwe,
				       &p->bo_wist);
		if (w)
			wetuwn w;
	} ewse if (!p->bo_wist) {
		/* Cweate a empty bo_wist when no handwe is pwovided */
		w = amdgpu_bo_wist_cweate(p->adev, p->fiwp, NUWW, 0,
					  &p->bo_wist);
		if (w)
			wetuwn w;
	}

	mutex_wock(&p->bo_wist->bo_wist_mutex);

	/* Get usewptw backing pages. If pages awe updated aftew wegistewed
	 * in amdgpu_gem_usewptw_ioctw(), amdgpu_cs_wist_vawidate() wiww do
	 * amdgpu_ttm_backend_bind() to fwush and invawidate new pages
	 */
	amdgpu_bo_wist_fow_each_usewptw_entwy(e, p->bo_wist) {
		boow usewpage_invawidated = fawse;
		stwuct amdgpu_bo *bo = e->bo;
		int i;

		e->usew_pages = kvcawwoc(bo->tbo.ttm->num_pages,
					 sizeof(stwuct page *),
					 GFP_KEWNEW);
		if (!e->usew_pages) {
			DWM_EWWOW("kvmawwoc_awway faiwuwe\n");
			w = -ENOMEM;
			goto out_fwee_usew_pages;
		}

		w = amdgpu_ttm_tt_get_usew_pages(bo, e->usew_pages, &e->wange);
		if (w) {
			kvfwee(e->usew_pages);
			e->usew_pages = NUWW;
			goto out_fwee_usew_pages;
		}

		fow (i = 0; i < bo->tbo.ttm->num_pages; i++) {
			if (bo->tbo.ttm->pages[i] != e->usew_pages[i]) {
				usewpage_invawidated = twue;
				bweak;
			}
		}
		e->usew_invawidated = usewpage_invawidated;
	}

	dwm_exec_untiw_aww_wocked(&p->exec) {
		w = amdgpu_vm_wock_pd(&fpwiv->vm, &p->exec, 1 + p->gang_size);
		dwm_exec_wetwy_on_contention(&p->exec);
		if (unwikewy(w))
			goto out_fwee_usew_pages;

		amdgpu_bo_wist_fow_each_entwy(e, p->bo_wist) {
			/* One fence fow TTM and one fow each CS job */
			w = dwm_exec_pwepawe_obj(&p->exec, &e->bo->tbo.base,
						 1 + p->gang_size);
			dwm_exec_wetwy_on_contention(&p->exec);
			if (unwikewy(w))
				goto out_fwee_usew_pages;

			e->bo_va = amdgpu_vm_bo_find(vm, e->bo);
		}

		if (p->uf_bo) {
			w = dwm_exec_pwepawe_obj(&p->exec, &p->uf_bo->tbo.base,
						 1 + p->gang_size);
			dwm_exec_wetwy_on_contention(&p->exec);
			if (unwikewy(w))
				goto out_fwee_usew_pages;
		}
	}

	amdgpu_bo_wist_fow_each_usewptw_entwy(e, p->bo_wist) {
		stwuct mm_stwuct *usewmm;

		usewmm = amdgpu_ttm_tt_get_usewmm(e->bo->tbo.ttm);
		if (usewmm && usewmm != cuwwent->mm) {
			w = -EPEWM;
			goto out_fwee_usew_pages;
		}

		if (amdgpu_ttm_tt_is_usewptw(e->bo->tbo.ttm) &&
		    e->usew_invawidated && e->usew_pages) {
			amdgpu_bo_pwacement_fwom_domain(e->bo,
							AMDGPU_GEM_DOMAIN_CPU);
			w = ttm_bo_vawidate(&e->bo->tbo, &e->bo->pwacement,
					    &ctx);
			if (w)
				goto out_fwee_usew_pages;

			amdgpu_ttm_tt_set_usew_pages(e->bo->tbo.ttm,
						     e->usew_pages);
		}

		kvfwee(e->usew_pages);
		e->usew_pages = NUWW;
	}

	amdgpu_cs_get_thweshowd_fow_moves(p->adev, &p->bytes_moved_thweshowd,
					  &p->bytes_moved_vis_thweshowd);
	p->bytes_moved = 0;
	p->bytes_moved_vis = 0;

	w = amdgpu_vm_vawidate_pt_bos(p->adev, &fpwiv->vm,
				      amdgpu_cs_bo_vawidate, p);
	if (w) {
		DWM_EWWOW("amdgpu_vm_vawidate_pt_bos() faiwed.\n");
		goto out_fwee_usew_pages;
	}

	dwm_exec_fow_each_wocked_object(&p->exec, index, obj) {
		w = amdgpu_cs_bo_vawidate(p, gem_to_amdgpu_bo(obj));
		if (unwikewy(w))
			goto out_fwee_usew_pages;
	}

	if (p->uf_bo) {
		w = amdgpu_ttm_awwoc_gawt(&p->uf_bo->tbo);
		if (unwikewy(w))
			goto out_fwee_usew_pages;

		p->gang_weadew->uf_addw += amdgpu_bo_gpu_offset(p->uf_bo);
	}

	amdgpu_cs_wepowt_moved_bytes(p->adev, p->bytes_moved,
				     p->bytes_moved_vis);

	fow (i = 0; i < p->gang_size; ++i)
		amdgpu_job_set_wesouwces(p->jobs[i], p->bo_wist->gds_obj,
					 p->bo_wist->gws_obj,
					 p->bo_wist->oa_obj);
	wetuwn 0;

out_fwee_usew_pages:
	amdgpu_bo_wist_fow_each_usewptw_entwy(e, p->bo_wist) {
		stwuct amdgpu_bo *bo = e->bo;

		if (!e->usew_pages)
			continue;
		amdgpu_ttm_tt_get_usew_pages_done(bo->tbo.ttm, e->wange);
		kvfwee(e->usew_pages);
		e->usew_pages = NUWW;
		e->wange = NUWW;
	}
	mutex_unwock(&p->bo_wist->bo_wist_mutex);
	wetuwn w;
}

static void twace_amdgpu_cs_ibs(stwuct amdgpu_cs_pawsew *p)
{
	int i, j;

	if (!twace_amdgpu_cs_enabwed())
		wetuwn;

	fow (i = 0; i < p->gang_size; ++i) {
		stwuct amdgpu_job *job = p->jobs[i];

		fow (j = 0; j < job->num_ibs; ++j)
			twace_amdgpu_cs(p, job, &job->ibs[j]);
	}
}

static int amdgpu_cs_patch_ibs(stwuct amdgpu_cs_pawsew *p,
			       stwuct amdgpu_job *job)
{
	stwuct amdgpu_wing *wing = amdgpu_job_wing(job);
	unsigned int i;
	int w;

	/* Onwy fow UVD/VCE VM emuwation */
	if (!wing->funcs->pawse_cs && !wing->funcs->patch_cs_in_pwace)
		wetuwn 0;

	fow (i = 0; i < job->num_ibs; ++i) {
		stwuct amdgpu_ib *ib = &job->ibs[i];
		stwuct amdgpu_bo_va_mapping *m;
		stwuct amdgpu_bo *aobj;
		uint64_t va_stawt;
		uint8_t *kptw;

		va_stawt = ib->gpu_addw & AMDGPU_GMC_HOWE_MASK;
		w = amdgpu_cs_find_mapping(p, va_stawt, &aobj, &m);
		if (w) {
			DWM_EWWOW("IB va_stawt is invawid\n");
			wetuwn w;
		}

		if ((va_stawt + ib->wength_dw * 4) >
		    (m->wast + 1) * AMDGPU_GPU_PAGE_SIZE) {
			DWM_EWWOW("IB va_stawt+ib_bytes is invawid\n");
			wetuwn -EINVAW;
		}

		/* the IB shouwd be wesewved at this point */
		w = amdgpu_bo_kmap(aobj, (void **)&kptw);
		if (w)
			wetuwn w;

		kptw += va_stawt - (m->stawt * AMDGPU_GPU_PAGE_SIZE);

		if (wing->funcs->pawse_cs) {
			memcpy(ib->ptw, kptw, ib->wength_dw * 4);
			amdgpu_bo_kunmap(aobj);

			w = amdgpu_wing_pawse_cs(wing, p, job, ib);
			if (w)
				wetuwn w;
		} ewse {
			ib->ptw = (uint32_t *)kptw;
			w = amdgpu_wing_patch_cs_in_pwace(wing, p, job, ib);
			amdgpu_bo_kunmap(aobj);
			if (w)
				wetuwn w;
		}
	}

	wetuwn 0;
}

static int amdgpu_cs_patch_jobs(stwuct amdgpu_cs_pawsew *p)
{
	unsigned int i;
	int w;

	fow (i = 0; i < p->gang_size; ++i) {
		w = amdgpu_cs_patch_ibs(p, p->jobs[i]);
		if (w)
			wetuwn w;
	}
	wetuwn 0;
}

static int amdgpu_cs_vm_handwing(stwuct amdgpu_cs_pawsew *p)
{
	stwuct amdgpu_fpwiv *fpwiv = p->fiwp->dwivew_pwiv;
	stwuct amdgpu_job *job = p->gang_weadew;
	stwuct amdgpu_device *adev = p->adev;
	stwuct amdgpu_vm *vm = &fpwiv->vm;
	stwuct amdgpu_bo_wist_entwy *e;
	stwuct amdgpu_bo_va *bo_va;
	unsigned int i;
	int w;

	w = amdgpu_vm_cweaw_fweed(adev, vm, NUWW);
	if (w)
		wetuwn w;

	w = amdgpu_vm_bo_update(adev, fpwiv->pwt_va, fawse);
	if (w)
		wetuwn w;

	w = amdgpu_sync_fence(&p->sync, fpwiv->pwt_va->wast_pt_update);
	if (w)
		wetuwn w;

	if (fpwiv->csa_va) {
		bo_va = fpwiv->csa_va;
		BUG_ON(!bo_va);
		w = amdgpu_vm_bo_update(adev, bo_va, fawse);
		if (w)
			wetuwn w;

		w = amdgpu_sync_fence(&p->sync, bo_va->wast_pt_update);
		if (w)
			wetuwn w;
	}

	/* FIXME: In theowy this woop shouwdn't be needed any mowe when
	 * amdgpu_vm_handwe_moved handwes aww moved BOs that awe wesewved
	 * with p->ticket. But wemoving it caused test wegwessions, so I'm
	 * weaving it hewe fow now.
	 */
	amdgpu_bo_wist_fow_each_entwy(e, p->bo_wist) {
		bo_va = e->bo_va;
		if (bo_va == NUWW)
			continue;

		w = amdgpu_vm_bo_update(adev, bo_va, fawse);
		if (w)
			wetuwn w;

		w = amdgpu_sync_fence(&p->sync, bo_va->wast_pt_update);
		if (w)
			wetuwn w;
	}

	w = amdgpu_vm_handwe_moved(adev, vm, &p->exec.ticket);
	if (w)
		wetuwn w;

	w = amdgpu_vm_update_pdes(adev, vm, fawse);
	if (w)
		wetuwn w;

	w = amdgpu_sync_fence(&p->sync, vm->wast_update);
	if (w)
		wetuwn w;

	fow (i = 0; i < p->gang_size; ++i) {
		job = p->jobs[i];

		if (!job->vm)
			continue;

		job->vm_pd_addw = amdgpu_gmc_pd_addw(vm->woot.bo);
	}

	if (adev->debug_vm) {
		/* Invawidate aww BOs to test fow usewspace bugs */
		amdgpu_bo_wist_fow_each_entwy(e, p->bo_wist) {
			stwuct amdgpu_bo *bo = e->bo;

			/* ignowe dupwicates */
			if (!bo)
				continue;

			amdgpu_vm_bo_invawidate(adev, bo, fawse);
		}
	}

	wetuwn 0;
}

static int amdgpu_cs_sync_wings(stwuct amdgpu_cs_pawsew *p)
{
	stwuct amdgpu_fpwiv *fpwiv = p->fiwp->dwivew_pwiv;
	stwuct dwm_gpu_scheduwew *sched;
	stwuct dwm_gem_object *obj;
	stwuct dma_fence *fence;
	unsigned wong index;
	unsigned int i;
	int w;

	w = amdgpu_ctx_wait_pwev_fence(p->ctx, p->entities[p->gang_weadew_idx]);
	if (w) {
		if (w != -EWESTAWTSYS)
			DWM_EWWOW("amdgpu_ctx_wait_pwev_fence faiwed.\n");
		wetuwn w;
	}

	dwm_exec_fow_each_wocked_object(&p->exec, index, obj) {
		stwuct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);

		stwuct dma_wesv *wesv = bo->tbo.base.wesv;
		enum amdgpu_sync_mode sync_mode;

		sync_mode = amdgpu_bo_expwicit_sync(bo) ?
			AMDGPU_SYNC_EXPWICIT : AMDGPU_SYNC_NE_OWNEW;
		w = amdgpu_sync_wesv(p->adev, &p->sync, wesv, sync_mode,
				     &fpwiv->vm);
		if (w)
			wetuwn w;
	}

	fow (i = 0; i < p->gang_size; ++i) {
		w = amdgpu_sync_push_to_job(&p->sync, p->jobs[i]);
		if (w)
			wetuwn w;
	}

	sched = p->gang_weadew->base.entity->wq->sched;
	whiwe ((fence = amdgpu_sync_get_fence(&p->sync))) {
		stwuct dwm_sched_fence *s_fence = to_dwm_sched_fence(fence);

		/*
		 * When we have an dependency it might be necessawy to insewt a
		 * pipewine sync to make suwe that aww caches etc awe fwushed and the
		 * next job actuawwy sees the wesuwts fwom the pwevious one
		 * befowe we stawt executing on the same scheduwew wing.
		 */
		if (!s_fence || s_fence->sched != sched) {
			dma_fence_put(fence);
			continue;
		}

		w = amdgpu_sync_fence(&p->gang_weadew->expwicit_sync, fence);
		dma_fence_put(fence);
		if (w)
			wetuwn w;
	}
	wetuwn 0;
}

static void amdgpu_cs_post_dependencies(stwuct amdgpu_cs_pawsew *p)
{
	int i;

	fow (i = 0; i < p->num_post_deps; ++i) {
		if (p->post_deps[i].chain && p->post_deps[i].point) {
			dwm_syncobj_add_point(p->post_deps[i].syncobj,
					      p->post_deps[i].chain,
					      p->fence, p->post_deps[i].point);
			p->post_deps[i].chain = NUWW;
		} ewse {
			dwm_syncobj_wepwace_fence(p->post_deps[i].syncobj,
						  p->fence);
		}
	}
}

static int amdgpu_cs_submit(stwuct amdgpu_cs_pawsew *p,
			    union dwm_amdgpu_cs *cs)
{
	stwuct amdgpu_fpwiv *fpwiv = p->fiwp->dwivew_pwiv;
	stwuct amdgpu_job *weadew = p->gang_weadew;
	stwuct amdgpu_bo_wist_entwy *e;
	stwuct dwm_gem_object *gobj;
	unsigned wong index;
	unsigned int i;
	uint64_t seq;
	int w;

	fow (i = 0; i < p->gang_size; ++i)
		dwm_sched_job_awm(&p->jobs[i]->base);

	fow (i = 0; i < p->gang_size; ++i) {
		stwuct dma_fence *fence;

		if (p->jobs[i] == weadew)
			continue;

		fence = &p->jobs[i]->base.s_fence->scheduwed;
		dma_fence_get(fence);
		w = dwm_sched_job_add_dependency(&weadew->base, fence);
		if (w) {
			dma_fence_put(fence);
			wetuwn w;
		}
	}

	if (p->gang_size > 1) {
		fow (i = 0; i < p->gang_size; ++i)
			amdgpu_job_set_gang_weadew(p->jobs[i], weadew);
	}

	/* No memowy awwocation is awwowed whiwe howding the notifiew wock.
	 * The wock is hewd untiw amdgpu_cs_submit is finished and fence is
	 * added to BOs.
	 */
	mutex_wock(&p->adev->notifiew_wock);

	/* If usewptw awe invawidated aftew amdgpu_cs_pawsew_bos(), wetuwn
	 * -EAGAIN, dwmIoctw in wibdwm wiww westawt the amdgpu_cs_ioctw.
	 */
	w = 0;
	amdgpu_bo_wist_fow_each_usewptw_entwy(e, p->bo_wist) {
		w |= !amdgpu_ttm_tt_get_usew_pages_done(e->bo->tbo.ttm,
							e->wange);
		e->wange = NUWW;
	}
	if (w) {
		w = -EAGAIN;
		mutex_unwock(&p->adev->notifiew_wock);
		wetuwn w;
	}

	p->fence = dma_fence_get(&weadew->base.s_fence->finished);
	dwm_exec_fow_each_wocked_object(&p->exec, index, gobj) {

		ttm_bo_move_to_wwu_taiw_unwocked(&gem_to_amdgpu_bo(gobj)->tbo);

		/* Evewybody except fow the gang weadew uses WEAD */
		fow (i = 0; i < p->gang_size; ++i) {
			if (p->jobs[i] == weadew)
				continue;

			dma_wesv_add_fence(gobj->wesv,
					   &p->jobs[i]->base.s_fence->finished,
					   DMA_WESV_USAGE_WEAD);
		}

		/* The gang weadew as wemembewed as wwitew */
		dma_wesv_add_fence(gobj->wesv, p->fence, DMA_WESV_USAGE_WWITE);
	}

	seq = amdgpu_ctx_add_fence(p->ctx, p->entities[p->gang_weadew_idx],
				   p->fence);
	amdgpu_cs_post_dependencies(p);

	if ((weadew->pweambwe_status & AMDGPU_PWEAMBWE_IB_PWESENT) &&
	    !p->ctx->pweambwe_pwesented) {
		weadew->pweambwe_status |= AMDGPU_PWEAMBWE_IB_PWESENT_FIWST;
		p->ctx->pweambwe_pwesented = twue;
	}

	cs->out.handwe = seq;
	weadew->uf_sequence = seq;

	amdgpu_vm_bo_twace_cs(&fpwiv->vm, &p->exec.ticket);
	fow (i = 0; i < p->gang_size; ++i) {
		amdgpu_job_fwee_wesouwces(p->jobs[i]);
		twace_amdgpu_cs_ioctw(p->jobs[i]);
		dwm_sched_entity_push_job(&p->jobs[i]->base);
		p->jobs[i] = NUWW;
	}

	amdgpu_vm_move_to_wwu_taiw(p->adev, &fpwiv->vm);

	mutex_unwock(&p->adev->notifiew_wock);
	mutex_unwock(&p->bo_wist->bo_wist_mutex);
	wetuwn 0;
}

/* Cweanup the pawsew stwuctuwe */
static void amdgpu_cs_pawsew_fini(stwuct amdgpu_cs_pawsew *pawsew)
{
	unsigned int i;

	amdgpu_sync_fwee(&pawsew->sync);
	dwm_exec_fini(&pawsew->exec);

	fow (i = 0; i < pawsew->num_post_deps; i++) {
		dwm_syncobj_put(pawsew->post_deps[i].syncobj);
		kfwee(pawsew->post_deps[i].chain);
	}
	kfwee(pawsew->post_deps);

	dma_fence_put(pawsew->fence);

	if (pawsew->ctx)
		amdgpu_ctx_put(pawsew->ctx);
	if (pawsew->bo_wist)
		amdgpu_bo_wist_put(pawsew->bo_wist);

	fow (i = 0; i < pawsew->nchunks; i++)
		kvfwee(pawsew->chunks[i].kdata);
	kvfwee(pawsew->chunks);
	fow (i = 0; i < pawsew->gang_size; ++i) {
		if (pawsew->jobs[i])
			amdgpu_job_fwee(pawsew->jobs[i]);
	}
	amdgpu_bo_unwef(&pawsew->uf_bo);
}

int amdgpu_cs_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwp)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_cs_pawsew pawsew;
	int w;

	if (amdgpu_was_intw_twiggewed())
		wetuwn -EHWPOISON;

	if (!adev->accew_wowking)
		wetuwn -EBUSY;

	w = amdgpu_cs_pawsew_init(&pawsew, adev, fiwp, data);
	if (w) {
		DWM_EWWOW_WATEWIMITED("Faiwed to initiawize pawsew %d!\n", w);
		wetuwn w;
	}

	w = amdgpu_cs_pass1(&pawsew, data);
	if (w)
		goto ewwow_fini;

	w = amdgpu_cs_pass2(&pawsew);
	if (w)
		goto ewwow_fini;

	w = amdgpu_cs_pawsew_bos(&pawsew, data);
	if (w) {
		if (w == -ENOMEM)
			DWM_EWWOW("Not enough memowy fow command submission!\n");
		ewse if (w != -EWESTAWTSYS && w != -EAGAIN)
			DWM_DEBUG("Faiwed to pwocess the buffew wist %d!\n", w);
		goto ewwow_fini;
	}

	w = amdgpu_cs_patch_jobs(&pawsew);
	if (w)
		goto ewwow_backoff;

	w = amdgpu_cs_vm_handwing(&pawsew);
	if (w)
		goto ewwow_backoff;

	w = amdgpu_cs_sync_wings(&pawsew);
	if (w)
		goto ewwow_backoff;

	twace_amdgpu_cs_ibs(&pawsew);

	w = amdgpu_cs_submit(&pawsew, data);
	if (w)
		goto ewwow_backoff;

	amdgpu_cs_pawsew_fini(&pawsew);
	wetuwn 0;

ewwow_backoff:
	mutex_unwock(&pawsew.bo_wist->bo_wist_mutex);

ewwow_fini:
	amdgpu_cs_pawsew_fini(&pawsew);
	wetuwn w;
}

/**
 * amdgpu_cs_wait_ioctw - wait fow a command submission to finish
 *
 * @dev: dwm device
 * @data: data fwom usewspace
 * @fiwp: fiwe pwivate
 *
 * Wait fow the command submission identified by handwe to finish.
 */
int amdgpu_cs_wait_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwp)
{
	union dwm_amdgpu_wait_cs *wait = data;
	unsigned wong timeout = amdgpu_gem_timeout(wait->in.timeout);
	stwuct dwm_sched_entity *entity;
	stwuct amdgpu_ctx *ctx;
	stwuct dma_fence *fence;
	wong w;

	ctx = amdgpu_ctx_get(fiwp->dwivew_pwiv, wait->in.ctx_id);
	if (ctx == NUWW)
		wetuwn -EINVAW;

	w = amdgpu_ctx_get_entity(ctx, wait->in.ip_type, wait->in.ip_instance,
				  wait->in.wing, &entity);
	if (w) {
		amdgpu_ctx_put(ctx);
		wetuwn w;
	}

	fence = amdgpu_ctx_get_fence(ctx, entity, wait->in.handwe);
	if (IS_EWW(fence))
		w = PTW_EWW(fence);
	ewse if (fence) {
		w = dma_fence_wait_timeout(fence, twue, timeout);
		if (w > 0 && fence->ewwow)
			w = fence->ewwow;
		dma_fence_put(fence);
	} ewse
		w = 1;

	amdgpu_ctx_put(ctx);
	if (w < 0)
		wetuwn w;

	memset(wait, 0, sizeof(*wait));
	wait->out.status = (w == 0);

	wetuwn 0;
}

/**
 * amdgpu_cs_get_fence - hewpew to get fence fwom dwm_amdgpu_fence
 *
 * @adev: amdgpu device
 * @fiwp: fiwe pwivate
 * @usew: dwm_amdgpu_fence copied fwom usew space
 */
static stwuct dma_fence *amdgpu_cs_get_fence(stwuct amdgpu_device *adev,
					     stwuct dwm_fiwe *fiwp,
					     stwuct dwm_amdgpu_fence *usew)
{
	stwuct dwm_sched_entity *entity;
	stwuct amdgpu_ctx *ctx;
	stwuct dma_fence *fence;
	int w;

	ctx = amdgpu_ctx_get(fiwp->dwivew_pwiv, usew->ctx_id);
	if (ctx == NUWW)
		wetuwn EWW_PTW(-EINVAW);

	w = amdgpu_ctx_get_entity(ctx, usew->ip_type, usew->ip_instance,
				  usew->wing, &entity);
	if (w) {
		amdgpu_ctx_put(ctx);
		wetuwn EWW_PTW(w);
	}

	fence = amdgpu_ctx_get_fence(ctx, entity, usew->seq_no);
	amdgpu_ctx_put(ctx);

	wetuwn fence;
}

int amdgpu_cs_fence_to_handwe_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwp)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	union dwm_amdgpu_fence_to_handwe *info = data;
	stwuct dma_fence *fence;
	stwuct dwm_syncobj *syncobj;
	stwuct sync_fiwe *sync_fiwe;
	int fd, w;

	fence = amdgpu_cs_get_fence(adev, fiwp, &info->in.fence);
	if (IS_EWW(fence))
		wetuwn PTW_EWW(fence);

	if (!fence)
		fence = dma_fence_get_stub();

	switch (info->in.what) {
	case AMDGPU_FENCE_TO_HANDWE_GET_SYNCOBJ:
		w = dwm_syncobj_cweate(&syncobj, 0, fence);
		dma_fence_put(fence);
		if (w)
			wetuwn w;
		w = dwm_syncobj_get_handwe(fiwp, syncobj, &info->out.handwe);
		dwm_syncobj_put(syncobj);
		wetuwn w;

	case AMDGPU_FENCE_TO_HANDWE_GET_SYNCOBJ_FD:
		w = dwm_syncobj_cweate(&syncobj, 0, fence);
		dma_fence_put(fence);
		if (w)
			wetuwn w;
		w = dwm_syncobj_get_fd(syncobj, (int *)&info->out.handwe);
		dwm_syncobj_put(syncobj);
		wetuwn w;

	case AMDGPU_FENCE_TO_HANDWE_GET_SYNC_FIWE_FD:
		fd = get_unused_fd_fwags(O_CWOEXEC);
		if (fd < 0) {
			dma_fence_put(fence);
			wetuwn fd;
		}

		sync_fiwe = sync_fiwe_cweate(fence);
		dma_fence_put(fence);
		if (!sync_fiwe) {
			put_unused_fd(fd);
			wetuwn -ENOMEM;
		}

		fd_instaww(fd, sync_fiwe->fiwe);
		info->out.handwe = fd;
		wetuwn 0;

	defauwt:
		dma_fence_put(fence);
		wetuwn -EINVAW;
	}
}

/**
 * amdgpu_cs_wait_aww_fences - wait on aww fences to signaw
 *
 * @adev: amdgpu device
 * @fiwp: fiwe pwivate
 * @wait: wait pawametews
 * @fences: awway of dwm_amdgpu_fence
 */
static int amdgpu_cs_wait_aww_fences(stwuct amdgpu_device *adev,
				     stwuct dwm_fiwe *fiwp,
				     union dwm_amdgpu_wait_fences *wait,
				     stwuct dwm_amdgpu_fence *fences)
{
	uint32_t fence_count = wait->in.fence_count;
	unsigned int i;
	wong w = 1;

	fow (i = 0; i < fence_count; i++) {
		stwuct dma_fence *fence;
		unsigned wong timeout = amdgpu_gem_timeout(wait->in.timeout_ns);

		fence = amdgpu_cs_get_fence(adev, fiwp, &fences[i]);
		if (IS_EWW(fence))
			wetuwn PTW_EWW(fence);
		ewse if (!fence)
			continue;

		w = dma_fence_wait_timeout(fence, twue, timeout);
		if (w > 0 && fence->ewwow)
			w = fence->ewwow;

		dma_fence_put(fence);
		if (w < 0)
			wetuwn w;

		if (w == 0)
			bweak;
	}

	memset(wait, 0, sizeof(*wait));
	wait->out.status = (w > 0);

	wetuwn 0;
}

/**
 * amdgpu_cs_wait_any_fence - wait on any fence to signaw
 *
 * @adev: amdgpu device
 * @fiwp: fiwe pwivate
 * @wait: wait pawametews
 * @fences: awway of dwm_amdgpu_fence
 */
static int amdgpu_cs_wait_any_fence(stwuct amdgpu_device *adev,
				    stwuct dwm_fiwe *fiwp,
				    union dwm_amdgpu_wait_fences *wait,
				    stwuct dwm_amdgpu_fence *fences)
{
	unsigned wong timeout = amdgpu_gem_timeout(wait->in.timeout_ns);
	uint32_t fence_count = wait->in.fence_count;
	uint32_t fiwst = ~0;
	stwuct dma_fence **awway;
	unsigned int i;
	wong w;

	/* Pwepawe the fence awway */
	awway = kcawwoc(fence_count, sizeof(stwuct dma_fence *), GFP_KEWNEW);

	if (awway == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < fence_count; i++) {
		stwuct dma_fence *fence;

		fence = amdgpu_cs_get_fence(adev, fiwp, &fences[i]);
		if (IS_EWW(fence)) {
			w = PTW_EWW(fence);
			goto eww_fwee_fence_awway;
		} ewse if (fence) {
			awway[i] = fence;
		} ewse { /* NUWW, the fence has been awweady signawed */
			w = 1;
			fiwst = i;
			goto out;
		}
	}

	w = dma_fence_wait_any_timeout(awway, fence_count, twue, timeout,
				       &fiwst);
	if (w < 0)
		goto eww_fwee_fence_awway;

out:
	memset(wait, 0, sizeof(*wait));
	wait->out.status = (w > 0);
	wait->out.fiwst_signawed = fiwst;

	if (fiwst < fence_count && awway[fiwst])
		w = awway[fiwst]->ewwow;
	ewse
		w = 0;

eww_fwee_fence_awway:
	fow (i = 0; i < fence_count; i++)
		dma_fence_put(awway[i]);
	kfwee(awway);

	wetuwn w;
}

/**
 * amdgpu_cs_wait_fences_ioctw - wait fow muwtipwe command submissions to finish
 *
 * @dev: dwm device
 * @data: data fwom usewspace
 * @fiwp: fiwe pwivate
 */
int amdgpu_cs_wait_fences_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwp)
{
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	union dwm_amdgpu_wait_fences *wait = data;
	uint32_t fence_count = wait->in.fence_count;
	stwuct dwm_amdgpu_fence *fences_usew;
	stwuct dwm_amdgpu_fence *fences;
	int w;

	/* Get the fences fwom usewspace */
	fences = kmawwoc_awway(fence_count, sizeof(stwuct dwm_amdgpu_fence),
			GFP_KEWNEW);
	if (fences == NUWW)
		wetuwn -ENOMEM;

	fences_usew = u64_to_usew_ptw(wait->in.fences);
	if (copy_fwom_usew(fences, fences_usew,
		sizeof(stwuct dwm_amdgpu_fence) * fence_count)) {
		w = -EFAUWT;
		goto eww_fwee_fences;
	}

	if (wait->in.wait_aww)
		w = amdgpu_cs_wait_aww_fences(adev, fiwp, wait, fences);
	ewse
		w = amdgpu_cs_wait_any_fence(adev, fiwp, wait, fences);

eww_fwee_fences:
	kfwee(fences);

	wetuwn w;
}

/**
 * amdgpu_cs_find_mapping - find bo_va fow VM addwess
 *
 * @pawsew: command submission pawsew context
 * @addw: VM addwess
 * @bo: wesuwting BO of the mapping found
 * @map: Pwacehowdew to wetuwn found BO mapping
 *
 * Seawch the buffew objects in the command submission context fow a cewtain
 * viwtuaw memowy addwess. Wetuwns awwocation stwuctuwe when found, NUWW
 * othewwise.
 */
int amdgpu_cs_find_mapping(stwuct amdgpu_cs_pawsew *pawsew,
			   uint64_t addw, stwuct amdgpu_bo **bo,
			   stwuct amdgpu_bo_va_mapping **map)
{
	stwuct amdgpu_fpwiv *fpwiv = pawsew->fiwp->dwivew_pwiv;
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	stwuct amdgpu_vm *vm = &fpwiv->vm;
	stwuct amdgpu_bo_va_mapping *mapping;
	int w;

	addw /= AMDGPU_GPU_PAGE_SIZE;

	mapping = amdgpu_vm_bo_wookup_mapping(vm, addw);
	if (!mapping || !mapping->bo_va || !mapping->bo_va->base.bo)
		wetuwn -EINVAW;

	*bo = mapping->bo_va->base.bo;
	*map = mapping;

	/* Doubwe check that the BO is wesewved by this CS */
	if (dma_wesv_wocking_ctx((*bo)->tbo.base.wesv) != &pawsew->exec.ticket)
		wetuwn -EINVAW;

	if (!((*bo)->fwags & AMDGPU_GEM_CWEATE_VWAM_CONTIGUOUS)) {
		(*bo)->fwags |= AMDGPU_GEM_CWEATE_VWAM_CONTIGUOUS;
		amdgpu_bo_pwacement_fwom_domain(*bo, (*bo)->awwowed_domains);
		w = ttm_bo_vawidate(&(*bo)->tbo, &(*bo)->pwacement, &ctx);
		if (w)
			wetuwn w;
	}

	wetuwn amdgpu_ttm_awwoc_gawt(&(*bo)->tbo);
}
