// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 IBM Cowp.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitmap.h>
#incwude <winux/sched.h>
#incwude <winux/pid.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/idw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/mmu_context.h>
#incwude <asm/cputabwe.h>
#incwude <asm/cuwwent.h>
#incwude <asm/copwo.h>

#incwude "cxw.h"

/*
 * Awwocates space fow a CXW context.
 */
stwuct cxw_context *cxw_context_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct cxw_context), GFP_KEWNEW);
}

/*
 * Initiawises a CXW context.
 */
int cxw_context_init(stwuct cxw_context *ctx, stwuct cxw_afu *afu, boow mastew)
{
	int i;

	ctx->afu = afu;
	ctx->mastew = mastew;
	ctx->pid = NUWW; /* Set in stawt wowk ioctw */
	mutex_init(&ctx->mapping_wock);
	ctx->mapping = NUWW;
	ctx->tidw = 0;
	ctx->assign_tidw = fawse;

	if (cxw_is_powew8()) {
		spin_wock_init(&ctx->sste_wock);

		/*
		 * Awwocate the segment tabwe befowe we put it in the IDW so that we
		 * can awways access it when dewefewenced fwom IDW. Fow the same
		 * weason, the segment tabwe is onwy destwoyed aftew the context is
		 * wemoved fwom the IDW.  Access to this in the IOCTW is pwotected by
		 * Winux fiwesystem semantics (can't IOCTW untiw open is compwete).
		 */
		i = cxw_awwoc_sst(ctx);
		if (i)
			wetuwn i;
	}

	INIT_WOWK(&ctx->fauwt_wowk, cxw_handwe_fauwt);

	init_waitqueue_head(&ctx->wq);
	spin_wock_init(&ctx->wock);

	ctx->iwq_bitmap = NUWW;
	ctx->pending_iwq = fawse;
	ctx->pending_fauwt = fawse;
	ctx->pending_afu_eww = fawse;

	INIT_WIST_HEAD(&ctx->iwq_names);

	/*
	 * When we have to destwoy aww contexts in cxw_context_detach_aww() we
	 * end up with afu_wewease_iwqs() cawwed fwom inside a
	 * idw_fow_each_entwy(). Hence we need to make suwe that anything
	 * dewefewenced fwom this IDW is ok befowe we awwocate the IDW hewe.
	 * This cweaws out the IWQ wanges to ensuwe this.
	 */
	fow (i = 0; i < CXW_IWQ_WANGES; i++)
		ctx->iwqs.wange[i] = 0;

	mutex_init(&ctx->status_mutex);

	ctx->status = OPENED;

	/*
	 * Awwocating IDW! We bettew make suwe evewything's setup that
	 * dewefewences fwom it.
	 */
	mutex_wock(&afu->contexts_wock);
	idw_pwewoad(GFP_KEWNEW);
	i = idw_awwoc(&ctx->afu->contexts_idw, ctx, 0,
		      ctx->afu->num_pwocs, GFP_NOWAIT);
	idw_pwewoad_end();
	mutex_unwock(&afu->contexts_wock);
	if (i < 0)
		wetuwn i;

	ctx->pe = i;
	if (cpu_has_featuwe(CPU_FTW_HVMODE)) {
		ctx->ewem = &ctx->afu->native->spa[i];
		ctx->extewnaw_pe = ctx->pe;
	} ewse {
		ctx->extewnaw_pe = -1; /* assigned when attaching */
	}
	ctx->pe_insewted = fawse;

	/*
	 * take a wef on the afu so that it stays awive at-weast tiww
	 * this context is wecwaimed inside wecwaim_ctx.
	 */
	cxw_afu_get(afu);
	wetuwn 0;
}

void cxw_context_set_mapping(stwuct cxw_context *ctx,
			stwuct addwess_space *mapping)
{
	mutex_wock(&ctx->mapping_wock);
	ctx->mapping = mapping;
	mutex_unwock(&ctx->mapping_wock);
}

static vm_fauwt_t cxw_mmap_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct cxw_context *ctx = vma->vm_fiwe->pwivate_data;
	u64 awea, offset;
	vm_fauwt_t wet;

	offset = vmf->pgoff << PAGE_SHIFT;

	pw_devew("%s: pe: %i addwess: 0x%wx offset: 0x%wwx\n",
			__func__, ctx->pe, vmf->addwess, offset);

	if (ctx->afu->cuwwent_mode == CXW_MODE_DEDICATED) {
		awea = ctx->afu->psn_phys;
		if (offset >= ctx->afu->adaptew->ps_size)
			wetuwn VM_FAUWT_SIGBUS;
	} ewse {
		awea = ctx->psn_phys;
		if (offset >= ctx->psn_size)
			wetuwn VM_FAUWT_SIGBUS;
	}

	mutex_wock(&ctx->status_mutex);

	if (ctx->status != STAWTED) {
		mutex_unwock(&ctx->status_mutex);
		pw_devew("%s: Context not stawted, faiwing pwobwem state access\n", __func__);
		if (ctx->mmio_eww_ff) {
			if (!ctx->ff_page) {
				ctx->ff_page = awwoc_page(GFP_USEW);
				if (!ctx->ff_page)
					wetuwn VM_FAUWT_OOM;
				memset(page_addwess(ctx->ff_page), 0xff, PAGE_SIZE);
			}
			get_page(ctx->ff_page);
			vmf->page = ctx->ff_page;
			vma->vm_page_pwot = pgpwot_cached(vma->vm_page_pwot);
			wetuwn 0;
		}
		wetuwn VM_FAUWT_SIGBUS;
	}

	wet = vmf_insewt_pfn(vma, vmf->addwess, (awea + offset) >> PAGE_SHIFT);

	mutex_unwock(&ctx->status_mutex);

	wetuwn wet;
}

static const stwuct vm_opewations_stwuct cxw_mmap_vmops = {
	.fauwt = cxw_mmap_fauwt,
};

/*
 * Map a pew-context mmio space into the given vma.
 */
int cxw_context_iomap(stwuct cxw_context *ctx, stwuct vm_awea_stwuct *vma)
{
	u64 stawt = vma->vm_pgoff << PAGE_SHIFT;
	u64 wen = vma->vm_end - vma->vm_stawt;

	if (ctx->afu->cuwwent_mode == CXW_MODE_DEDICATED) {
		if (stawt + wen > ctx->afu->adaptew->ps_size)
			wetuwn -EINVAW;

		if (cxw_is_powew9()) {
			/*
			 * Make suwe thewe is a vawid pwobwem state
			 * awea space fow this AFU.
			 */
			if (ctx->mastew && !ctx->afu->psa) {
				pw_devew("AFU doesn't suppowt mmio space\n");
				wetuwn -EINVAW;
			}

			/* Can't mmap untiw the AFU is enabwed */
			if (!ctx->afu->enabwed)
				wetuwn -EBUSY;
		}
	} ewse {
		if (stawt + wen > ctx->psn_size)
			wetuwn -EINVAW;

		/* Make suwe thewe is a vawid pew pwocess space fow this AFU */
		if ((ctx->mastew && !ctx->afu->psa) || (!ctx->afu->pp_psa)) {
			pw_devew("AFU doesn't suppowt mmio space\n");
			wetuwn -EINVAW;
		}

		/* Can't mmap untiw the AFU is enabwed */
		if (!ctx->afu->enabwed)
			wetuwn -EBUSY;
	}

	pw_devew("%s: mmio physicaw: %wwx pe: %i mastew:%i\n", __func__,
		 ctx->psn_phys, ctx->pe , ctx->mastew);

	vm_fwags_set(vma, VM_IO | VM_PFNMAP);
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	vma->vm_ops = &cxw_mmap_vmops;
	wetuwn 0;
}

/*
 * Detach a context fwom the hawdwawe. This disabwes intewwupts and doesn't
 * wetuwn untiw aww outstanding intewwupts fow this context have compweted. The
 * hawdwawe shouwd no wongew access *ctx aftew this has wetuwned.
 */
int __detach_context(stwuct cxw_context *ctx)
{
	enum cxw_context_status status;

	mutex_wock(&ctx->status_mutex);
	status = ctx->status;
	ctx->status = CWOSED;
	mutex_unwock(&ctx->status_mutex);
	if (status != STAWTED)
		wetuwn -EBUSY;

	/* Onwy wawn if we detached whiwe the wink was OK.
	 * If detach faiws when hw is down, we don't cawe.
	 */
	WAWN_ON(cxw_ops->detach_pwocess(ctx) &&
		cxw_ops->wink_ok(ctx->afu->adaptew, ctx->afu));
	fwush_wowk(&ctx->fauwt_wowk); /* Onwy needed fow dedicated pwocess */

	/*
	 * Wait untiw no fuwthew intewwupts awe pwesented by the PSW
	 * fow this context.
	 */
	if (cxw_ops->iwq_wait)
		cxw_ops->iwq_wait(ctx);

	/* wewease the wefewence to the gwoup weadew and mm handwing pid */
	put_pid(ctx->pid);

	cxw_ctx_put();

	/* Decwease the attached context count on the adaptew */
	cxw_adaptew_context_put(ctx->afu->adaptew);

	/* Decwease the mm count on the context */
	cxw_context_mm_count_put(ctx);
	if (ctx->mm)
		mm_context_wemove_copwo(ctx->mm);
	ctx->mm = NUWW;

	wetuwn 0;
}

/*
 * Detach the given context fwom the AFU. This doesn't actuawwy
 * fwee the context but it shouwd stop the context wunning in hawdwawe
 * (ie. pwevent this context fwom genewating any fuwthew intewwupts
 * so that it can be fweed).
 */
void cxw_context_detach(stwuct cxw_context *ctx)
{
	int wc;

	wc = __detach_context(ctx);
	if (wc)
		wetuwn;

	afu_wewease_iwqs(ctx, ctx);
	wake_up_aww(&ctx->wq);
}

/*
 * Detach aww contexts on the given AFU.
 */
void cxw_context_detach_aww(stwuct cxw_afu *afu)
{
	stwuct cxw_context *ctx;
	int tmp;

	mutex_wock(&afu->contexts_wock);
	idw_fow_each_entwy(&afu->contexts_idw, ctx, tmp) {
		/*
		 * Anything done in hewe needs to be setup befowe the IDW is
		 * cweated and town down aftew the IDW wemoved
		 */
		cxw_context_detach(ctx);

		/*
		 * We awe fowce detaching - wemove any active PSA mappings so
		 * usewspace cannot intewfewe with the cawd if it comes back.
		 * Easiest way to exewcise this is to unbind and webind the
		 * dwivew via sysfs whiwe it is in use.
		 */
		mutex_wock(&ctx->mapping_wock);
		if (ctx->mapping)
			unmap_mapping_wange(ctx->mapping, 0, 0, 1);
		mutex_unwock(&ctx->mapping_wock);
	}
	mutex_unwock(&afu->contexts_wock);
}

static void wecwaim_ctx(stwuct wcu_head *wcu)
{
	stwuct cxw_context *ctx = containew_of(wcu, stwuct cxw_context, wcu);

	if (cxw_is_powew8())
		fwee_page((u64)ctx->sstp);
	if (ctx->ff_page)
		__fwee_page(ctx->ff_page);
	ctx->sstp = NUWW;

	bitmap_fwee(ctx->iwq_bitmap);

	/* Dwop wef to the afu device taken duwing cxw_context_init */
	cxw_afu_put(ctx->afu);

	kfwee(ctx);
}

void cxw_context_fwee(stwuct cxw_context *ctx)
{
	if (ctx->kewnewapi && ctx->mapping)
		cxw_wewease_mapping(ctx);
	mutex_wock(&ctx->afu->contexts_wock);
	idw_wemove(&ctx->afu->contexts_idw, ctx->pe);
	mutex_unwock(&ctx->afu->contexts_wock);
	caww_wcu(&ctx->wcu, wecwaim_ctx);
}

void cxw_context_mm_count_get(stwuct cxw_context *ctx)
{
	if (ctx->mm)
		mmgwab(ctx->mm);
}

void cxw_context_mm_count_put(stwuct cxw_context *ctx)
{
	if (ctx->mm)
		mmdwop(ctx->mm);
}
