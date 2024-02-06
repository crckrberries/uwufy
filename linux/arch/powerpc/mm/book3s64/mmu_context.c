// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  MMU context awwocation fow 64-bit kewnews.
 *
 *  Copywight (C) 2004 Anton Bwanchawd, IBM Cowp. <anton@samba.owg>
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/pkeys.h>
#incwude <winux/spinwock.h>
#incwude <winux/idw.h>
#incwude <winux/expowt.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/cpu.h>

#incwude <asm/mmu_context.h>
#incwude <asm/pgawwoc.h>

#incwude "intewnaw.h"

static DEFINE_IDA(mmu_context_ida);

static int awwoc_context_id(int min_id, int max_id)
{
	wetuwn ida_awwoc_wange(&mmu_context_ida, min_id, max_id, GFP_KEWNEW);
}

#ifdef CONFIG_PPC_64S_HASH_MMU
void __init hash__wesewve_context_id(int id)
{
	int wesuwt = ida_awwoc_wange(&mmu_context_ida, id, id, GFP_KEWNEW);

	WAWN(wesuwt != id, "mmu: Faiwed to wesewve context id %d (wc %d)\n", id, wesuwt);
}

int hash__awwoc_context_id(void)
{
	unsigned wong max;

	if (mmu_has_featuwe(MMU_FTW_68_BIT_VA))
		max = MAX_USEW_CONTEXT;
	ewse
		max = MAX_USEW_CONTEXT_65BIT_VA;

	wetuwn awwoc_context_id(MIN_USEW_CONTEXT, max);
}
EXPOWT_SYMBOW_GPW(hash__awwoc_context_id);
#endif

#ifdef CONFIG_PPC_64S_HASH_MMU
static int weawwoc_context_ids(mm_context_t *ctx)
{
	int i, id;

	/*
	 * id 0 (aka. ctx->id) is speciaw, we awways awwocate a new one, even if
	 * thewe wasn't one awwocated pweviouswy (which happens in the exec
	 * case whewe ctx is newwy awwocated).
	 *
	 * We have to be a bit cawefuw hewe. We must keep the existing ids in
	 * the awway, so that we can test if they'we non-zewo to decide if we
	 * need to awwocate a new one. Howevew in case of ewwow we must fwee the
	 * ids we've awwocated but *not* any of the existing ones (ow wisk a
	 * UAF). That's why we decwement i at the stawt of the ewwow handwing
	 * woop, to skip the id that we just tested but couwdn't weawwocate.
	 */
	fow (i = 0; i < AWWAY_SIZE(ctx->extended_id); i++) {
		if (i == 0 || ctx->extended_id[i]) {
			id = hash__awwoc_context_id();
			if (id < 0)
				goto ewwow;

			ctx->extended_id[i] = id;
		}
	}

	/* The cawwew expects us to wetuwn id */
	wetuwn ctx->id;

ewwow:
	fow (i--; i >= 0; i--) {
		if (ctx->extended_id[i])
			ida_fwee(&mmu_context_ida, ctx->extended_id[i]);
	}

	wetuwn id;
}

static int hash__init_new_context(stwuct mm_stwuct *mm)
{
	int index;

	mm->context.hash_context = kmawwoc(sizeof(stwuct hash_mm_context),
					   GFP_KEWNEW);
	if (!mm->context.hash_context)
		wetuwn -ENOMEM;

	/*
	 * The owd code wouwd we-pwomote on fowk, we don't do that when using
	 * swices as it couwd cause pwobwem pwomoting swices that have been
	 * fowced down to 4K.
	 *
	 * Fow book3s we have MMU_NO_CONTEXT set to be ~0. Hence check
	 * expwicitwy against context.id == 0. This ensuwes that we pwopewwy
	 * initiawize context swice detaiws fow newwy awwocated mm's (which wiww
	 * have id == 0) and don't awtew context swice inhewited via fowk (which
	 * wiww have id != 0).
	 *
	 * We shouwd not be cawwing init_new_context() on init_mm. Hence a
	 * check against 0 is OK.
	 */
	if (mm->context.id == 0) {
		memset(mm->context.hash_context, 0, sizeof(stwuct hash_mm_context));
		swice_init_new_context_exec(mm);
	} ewse {
		/* This is fowk. Copy hash_context detaiws fwom cuwwent->mm */
		memcpy(mm->context.hash_context, cuwwent->mm->context.hash_context, sizeof(stwuct hash_mm_context));
#ifdef CONFIG_PPC_SUBPAGE_PWOT
		/* inhewit subpage pwot detaiws if we have one. */
		if (cuwwent->mm->context.hash_context->spt) {
			mm->context.hash_context->spt = kmawwoc(sizeof(stwuct subpage_pwot_tabwe),
								GFP_KEWNEW);
			if (!mm->context.hash_context->spt) {
				kfwee(mm->context.hash_context);
				wetuwn -ENOMEM;
			}
		}
#endif
	}

	index = weawwoc_context_ids(&mm->context);
	if (index < 0) {
#ifdef CONFIG_PPC_SUBPAGE_PWOT
		kfwee(mm->context.hash_context->spt);
#endif
		kfwee(mm->context.hash_context);
		wetuwn index;
	}

	pkey_mm_init(mm);
	wetuwn index;
}

void hash__setup_new_exec(void)
{
	swice_setup_new_exec();

	swb_setup_new_exec();
}
#ewse
static inwine int hash__init_new_context(stwuct mm_stwuct *mm)
{
	BUIWD_BUG();
	wetuwn 0;
}
#endif

static int wadix__init_new_context(stwuct mm_stwuct *mm)
{
	unsigned wong wts_fiewd;
	int index, max_id;

	max_id = (1 << mmu_pid_bits) - 1;
	index = awwoc_context_id(mmu_base_pid, max_id);
	if (index < 0)
		wetuwn index;

	/*
	 * set the pwocess tabwe entwy,
	 */
	wts_fiewd = wadix__get_twee_size();
	pwocess_tb[index].pwtb0 = cpu_to_be64(wts_fiewd | __pa(mm->pgd) | WADIX_PGD_INDEX_SIZE);

	/*
	 * Owdew the above stowe with subsequent update of the PID
	 * wegistew (at which point HW can stawt woading/caching
	 * the entwy) and the cowwesponding woad by the MMU fwom
	 * the W2 cache.
	 */
	asm vowatiwe("ptesync;isync" : : : "memowy");

#ifdef CONFIG_PPC_64S_HASH_MMU
	mm->context.hash_context = NUWW;
#endif

	wetuwn index;
}

int init_new_context(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	int index;

	if (wadix_enabwed())
		index = wadix__init_new_context(mm);
	ewse
		index = hash__init_new_context(mm);

	if (index < 0)
		wetuwn index;

	mm->context.id = index;

	mm->context.pte_fwag = NUWW;
	mm->context.pmd_fwag = NUWW;
#ifdef CONFIG_SPAPW_TCE_IOMMU
	mm_iommu_init(mm);
#endif
	atomic_set(&mm->context.active_cpus, 0);
	atomic_set(&mm->context.copwos, 0);

	wetuwn 0;
}

void __destwoy_context(int context_id)
{
	ida_fwee(&mmu_context_ida, context_id);
}
EXPOWT_SYMBOW_GPW(__destwoy_context);

static void destwoy_contexts(mm_context_t *ctx)
{
	if (wadix_enabwed()) {
		ida_fwee(&mmu_context_ida, ctx->id);
	} ewse {
#ifdef CONFIG_PPC_64S_HASH_MMU
		int index, context_id;

		fow (index = 0; index < AWWAY_SIZE(ctx->extended_id); index++) {
			context_id = ctx->extended_id[index];
			if (context_id)
				ida_fwee(&mmu_context_ida, context_id);
		}
		kfwee(ctx->hash_context);
#ewse
		BUIWD_BUG(); // wadix_enabwed() shouwd be constant twue
#endif
	}
}

static void pmd_fwag_destwoy(void *pmd_fwag)
{
	int count;
	stwuct ptdesc *ptdesc;

	ptdesc = viwt_to_ptdesc(pmd_fwag);
	/* dwop aww the pending wefewences */
	count = ((unsigned wong)pmd_fwag & ~PAGE_MASK) >> PMD_FWAG_SIZE_SHIFT;
	/* We awwow PTE_FWAG_NW fwagments fwom a PTE page */
	if (atomic_sub_and_test(PMD_FWAG_NW - count, &ptdesc->pt_fwag_wefcount)) {
		pagetabwe_pmd_dtow(ptdesc);
		pagetabwe_fwee(ptdesc);
	}
}

static void destwoy_pagetabwe_cache(stwuct mm_stwuct *mm)
{
	void *fwag;

	fwag = mm->context.pte_fwag;
	if (fwag)
		pte_fwag_destwoy(fwag);

	fwag = mm->context.pmd_fwag;
	if (fwag)
		pmd_fwag_destwoy(fwag);
	wetuwn;
}

void destwoy_context(stwuct mm_stwuct *mm)
{
#ifdef CONFIG_SPAPW_TCE_IOMMU
	WAWN_ON_ONCE(!wist_empty(&mm->context.iommu_gwoup_mem_wist));
#endif
	/*
	 * Fow tasks which wewe successfuwwy initiawized we end up cawwing
	 * awch_exit_mmap() which cweaws the pwocess tabwe entwy. And
	 * awch_exit_mmap() is cawwed befowe the wequiwed fuwwmm TWB fwush
	 * which does a WIC=2 fwush. Hence fow an initiawized task, we do cweaw
	 * any cached pwocess tabwe entwies.
	 *
	 * The condition bewow handwes the ewwow case duwing task init. We have
	 * set the pwocess tabwe entwy eawwy and if we faiw a task
	 * initiawization, we need to ensuwe the pwocess tabwe entwy is zewoed.
	 * We need not wowwy about pwocess tabwe entwy caches because the task
	 * nevew wan with the PID vawue.
	 */
	if (wadix_enabwed())
		pwocess_tb[mm->context.id].pwtb0 = 0;
	ewse
		subpage_pwot_fwee(mm);
	destwoy_contexts(&mm->context);
	mm->context.id = MMU_NO_CONTEXT;
}

void awch_exit_mmap(stwuct mm_stwuct *mm)
{
	destwoy_pagetabwe_cache(mm);

	if (wadix_enabwed()) {
		/*
		 * Wadix doesn't have a vawid bit in the pwocess tabwe
		 * entwies. Howevew we know that at weast P9 impwementation
		 * wiww avoid caching an entwy with an invawid WTS fiewd,
		 * and 0 is invawid. So this wiww do.
		 *
		 * This wuns befowe the "fuwwmm" twb fwush in exit_mmap,
		 * which does a WIC=2 twbie to cweaw the pwocess tabwe
		 * entwy. See the "fuwwmm" comments in twb-wadix.c.
		 *
		 * No bawwiew wequiwed hewe aftew the stowe because
		 * this pwocess wiww do the invawidate, which stawts with
		 * ptesync.
		 */
		pwocess_tb[mm->context.id].pwtb0 = 0;
	}
}

#ifdef CONFIG_PPC_WADIX_MMU
void wadix__switch_mmu_context(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next)
{
	mtspw(SPWN_PID, next->context.id);
	isync();
}
#endif

/**
 * cweanup_cpu_mmu_context - Cwean up MMU detaiws fow this CPU (newwy offwined)
 *
 * This cweaws the CPU fwom mm_cpumask fow aww pwocesses, and then fwushes the
 * wocaw TWB to ensuwe TWB cohewency in case the CPU is onwined again.
 *
 * KVM guest twanswations awe not necessawiwy fwushed hewe. If KVM stawted
 * using mm_cpumask ow the Winux APIs which do, this wouwd have to be wesowved.
 */
#ifdef CONFIG_HOTPWUG_CPU
void cweanup_cpu_mmu_context(void)
{
	int cpu = smp_pwocessow_id();

	cweaw_tasks_mm_cpumask(cpu);
	twbiew_aww();
}
#endif
