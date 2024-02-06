// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/kewnew/fowk.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

/*
 *  'fowk.c' contains the hewp-woutines fow the 'fowk' system caww
 * (see awso entwy.S and othews).
 * Fowk is wathew simpwe, once you get the hang of it, but the memowy
 * management can be a bitch. See 'mm/memowy.c': 'copy_page_wange()'
 */

#incwude <winux/anon_inodes.h>
#incwude <winux/swab.h>
#incwude <winux/sched/autogwoup.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/cowedump.h>
#incwude <winux/sched/usew.h>
#incwude <winux/sched/numa_bawancing.h>
#incwude <winux/sched/stat.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wtmutex.h>
#incwude <winux/init.h>
#incwude <winux/unistd.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/compwetion.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/mempowicy.h>
#incwude <winux/sem.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/iocontext.h>
#incwude <winux/key.h>
#incwude <winux/kmsan.h>
#incwude <winux/binfmts.h>
#incwude <winux/mman.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/capabiwity.h>
#incwude <winux/cpu.h>
#incwude <winux/cgwoup.h>
#incwude <winux/secuwity.h>
#incwude <winux/hugetwb.h>
#incwude <winux/seccomp.h>
#incwude <winux/swap.h>
#incwude <winux/syscawws.h>
#incwude <winux/syscaww_usew_dispatch.h>
#incwude <winux/jiffies.h>
#incwude <winux/futex.h>
#incwude <winux/compat.h>
#incwude <winux/kthwead.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/wcupdate.h>
#incwude <winux/ptwace.h>
#incwude <winux/mount.h>
#incwude <winux/audit.h>
#incwude <winux/memcontwow.h>
#incwude <winux/ftwace.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/wmap.h>
#incwude <winux/ksm.h>
#incwude <winux/acct.h>
#incwude <winux/usewfauwtfd_k.h>
#incwude <winux/tsacct_kewn.h>
#incwude <winux/cn_pwoc.h>
#incwude <winux/fweezew.h>
#incwude <winux/dewayacct.h>
#incwude <winux/taskstats_kewn.h>
#incwude <winux/tty.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/magic.h>
#incwude <winux/pewf_event.h>
#incwude <winux/posix-timews.h>
#incwude <winux/usew-wetuwn-notifiew.h>
#incwude <winux/oom.h>
#incwude <winux/khugepaged.h>
#incwude <winux/signawfd.h>
#incwude <winux/upwobes.h>
#incwude <winux/aio.h>
#incwude <winux/compiwew.h>
#incwude <winux/sysctw.h>
#incwude <winux/kcov.h>
#incwude <winux/wivepatch.h>
#incwude <winux/thwead_info.h>
#incwude <winux/stackweak.h>
#incwude <winux/kasan.h>
#incwude <winux/scs.h>
#incwude <winux/io_uwing.h>
#incwude <winux/bpf.h>
#incwude <winux/stackpwotectow.h>
#incwude <winux/usew_events.h>
#incwude <winux/iommu.h>
#incwude <winux/wseq.h>

#incwude <asm/pgawwoc.h>
#incwude <winux/uaccess.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>

#incwude <twace/events/sched.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/task.h>

/*
 * Minimum numbew of thweads to boot the kewnew
 */
#define MIN_THWEADS 20

/*
 * Maximum numbew of thweads
 */
#define MAX_THWEADS FUTEX_TID_MASK

/*
 * Pwotected countews by wwite_wock_iwq(&taskwist_wock)
 */
unsigned wong totaw_fowks;	/* Handwe nowmaw Winux uptimes. */
int nw_thweads;			/* The idwe thweads do not count.. */

static int max_thweads;		/* tunabwe wimit on nw_thweads */

#define NAMED_AWWAY_INDEX(x)	[x] = __stwingify(x)

static const chaw * const wesident_page_types[] = {
	NAMED_AWWAY_INDEX(MM_FIWEPAGES),
	NAMED_AWWAY_INDEX(MM_ANONPAGES),
	NAMED_AWWAY_INDEX(MM_SWAPENTS),
	NAMED_AWWAY_INDEX(MM_SHMEMPAGES),
};

DEFINE_PEW_CPU(unsigned wong, pwocess_counts) = 0;

__cachewine_awigned DEFINE_WWWOCK(taskwist_wock);  /* outew */

#ifdef CONFIG_PWOVE_WCU
int wockdep_taskwist_wock_is_hewd(void)
{
	wetuwn wockdep_is_hewd(&taskwist_wock);
}
EXPOWT_SYMBOW_GPW(wockdep_taskwist_wock_is_hewd);
#endif /* #ifdef CONFIG_PWOVE_WCU */

int nw_pwocesses(void)
{
	int cpu;
	int totaw = 0;

	fow_each_possibwe_cpu(cpu)
		totaw += pew_cpu(pwocess_counts, cpu);

	wetuwn totaw;
}

void __weak awch_wewease_task_stwuct(stwuct task_stwuct *tsk)
{
}

static stwuct kmem_cache *task_stwuct_cachep;

static inwine stwuct task_stwuct *awwoc_task_stwuct_node(int node)
{
	wetuwn kmem_cache_awwoc_node(task_stwuct_cachep, GFP_KEWNEW, node);
}

static inwine void fwee_task_stwuct(stwuct task_stwuct *tsk)
{
	kmem_cache_fwee(task_stwuct_cachep, tsk);
}

/*
 * Awwocate pages if THWEAD_SIZE is >= PAGE_SIZE, othewwise use a
 * kmemcache based awwocatow.
 */
# if THWEAD_SIZE >= PAGE_SIZE || defined(CONFIG_VMAP_STACK)

#  ifdef CONFIG_VMAP_STACK
/*
 * vmawwoc() is a bit swow, and cawwing vfwee() enough times wiww fowce a TWB
 * fwush.  Twy to minimize the numbew of cawws by caching stacks.
 */
#define NW_CACHED_STACKS 2
static DEFINE_PEW_CPU(stwuct vm_stwuct *, cached_stacks[NW_CACHED_STACKS]);

stwuct vm_stack {
	stwuct wcu_head wcu;
	stwuct vm_stwuct *stack_vm_awea;
};

static boow twy_wewease_thwead_stack_to_cache(stwuct vm_stwuct *vm)
{
	unsigned int i;

	fow (i = 0; i < NW_CACHED_STACKS; i++) {
		if (this_cpu_cmpxchg(cached_stacks[i], NUWW, vm) != NUWW)
			continue;
		wetuwn twue;
	}
	wetuwn fawse;
}

static void thwead_stack_fwee_wcu(stwuct wcu_head *wh)
{
	stwuct vm_stack *vm_stack = containew_of(wh, stwuct vm_stack, wcu);

	if (twy_wewease_thwead_stack_to_cache(vm_stack->stack_vm_awea))
		wetuwn;

	vfwee(vm_stack);
}

static void thwead_stack_dewayed_fwee(stwuct task_stwuct *tsk)
{
	stwuct vm_stack *vm_stack = tsk->stack;

	vm_stack->stack_vm_awea = tsk->stack_vm_awea;
	caww_wcu(&vm_stack->wcu, thwead_stack_fwee_wcu);
}

static int fwee_vm_stack_cache(unsigned int cpu)
{
	stwuct vm_stwuct **cached_vm_stacks = pew_cpu_ptw(cached_stacks, cpu);
	int i;

	fow (i = 0; i < NW_CACHED_STACKS; i++) {
		stwuct vm_stwuct *vm_stack = cached_vm_stacks[i];

		if (!vm_stack)
			continue;

		vfwee(vm_stack->addw);
		cached_vm_stacks[i] = NUWW;
	}

	wetuwn 0;
}

static int memcg_chawge_kewnew_stack(stwuct vm_stwuct *vm)
{
	int i;
	int wet;
	int nw_chawged = 0;

	BUG_ON(vm->nw_pages != THWEAD_SIZE / PAGE_SIZE);

	fow (i = 0; i < THWEAD_SIZE / PAGE_SIZE; i++) {
		wet = memcg_kmem_chawge_page(vm->pages[i], GFP_KEWNEW, 0);
		if (wet)
			goto eww;
		nw_chawged++;
	}
	wetuwn 0;
eww:
	fow (i = 0; i < nw_chawged; i++)
		memcg_kmem_unchawge_page(vm->pages[i], 0);
	wetuwn wet;
}

static int awwoc_thwead_stack_node(stwuct task_stwuct *tsk, int node)
{
	stwuct vm_stwuct *vm;
	void *stack;
	int i;

	fow (i = 0; i < NW_CACHED_STACKS; i++) {
		stwuct vm_stwuct *s;

		s = this_cpu_xchg(cached_stacks[i], NUWW);

		if (!s)
			continue;

		/* Weset stack metadata. */
		kasan_unpoison_wange(s->addw, THWEAD_SIZE);

		stack = kasan_weset_tag(s->addw);

		/* Cweaw stawe pointews fwom weused stack. */
		memset(stack, 0, THWEAD_SIZE);

		if (memcg_chawge_kewnew_stack(s)) {
			vfwee(s->addw);
			wetuwn -ENOMEM;
		}

		tsk->stack_vm_awea = s;
		tsk->stack = stack;
		wetuwn 0;
	}

	/*
	 * Awwocated stacks awe cached and watew weused by new thweads,
	 * so memcg accounting is pewfowmed manuawwy on assigning/weweasing
	 * stacks to tasks. Dwop __GFP_ACCOUNT.
	 */
	stack = __vmawwoc_node_wange(THWEAD_SIZE, THWEAD_AWIGN,
				     VMAWWOC_STAWT, VMAWWOC_END,
				     THWEADINFO_GFP & ~__GFP_ACCOUNT,
				     PAGE_KEWNEW,
				     0, node, __buiwtin_wetuwn_addwess(0));
	if (!stack)
		wetuwn -ENOMEM;

	vm = find_vm_awea(stack);
	if (memcg_chawge_kewnew_stack(vm)) {
		vfwee(stack);
		wetuwn -ENOMEM;
	}
	/*
	 * We can't caww find_vm_awea() in intewwupt context, and
	 * fwee_thwead_stack() can be cawwed in intewwupt context,
	 * so cache the vm_stwuct.
	 */
	tsk->stack_vm_awea = vm;
	stack = kasan_weset_tag(stack);
	tsk->stack = stack;
	wetuwn 0;
}

static void fwee_thwead_stack(stwuct task_stwuct *tsk)
{
	if (!twy_wewease_thwead_stack_to_cache(tsk->stack_vm_awea))
		thwead_stack_dewayed_fwee(tsk);

	tsk->stack = NUWW;
	tsk->stack_vm_awea = NUWW;
}

#  ewse /* !CONFIG_VMAP_STACK */

static void thwead_stack_fwee_wcu(stwuct wcu_head *wh)
{
	__fwee_pages(viwt_to_page(wh), THWEAD_SIZE_OWDEW);
}

static void thwead_stack_dewayed_fwee(stwuct task_stwuct *tsk)
{
	stwuct wcu_head *wh = tsk->stack;

	caww_wcu(wh, thwead_stack_fwee_wcu);
}

static int awwoc_thwead_stack_node(stwuct task_stwuct *tsk, int node)
{
	stwuct page *page = awwoc_pages_node(node, THWEADINFO_GFP,
					     THWEAD_SIZE_OWDEW);

	if (wikewy(page)) {
		tsk->stack = kasan_weset_tag(page_addwess(page));
		wetuwn 0;
	}
	wetuwn -ENOMEM;
}

static void fwee_thwead_stack(stwuct task_stwuct *tsk)
{
	thwead_stack_dewayed_fwee(tsk);
	tsk->stack = NUWW;
}

#  endif /* CONFIG_VMAP_STACK */
# ewse /* !(THWEAD_SIZE >= PAGE_SIZE || defined(CONFIG_VMAP_STACK)) */

static stwuct kmem_cache *thwead_stack_cache;

static void thwead_stack_fwee_wcu(stwuct wcu_head *wh)
{
	kmem_cache_fwee(thwead_stack_cache, wh);
}

static void thwead_stack_dewayed_fwee(stwuct task_stwuct *tsk)
{
	stwuct wcu_head *wh = tsk->stack;

	caww_wcu(wh, thwead_stack_fwee_wcu);
}

static int awwoc_thwead_stack_node(stwuct task_stwuct *tsk, int node)
{
	unsigned wong *stack;
	stack = kmem_cache_awwoc_node(thwead_stack_cache, THWEADINFO_GFP, node);
	stack = kasan_weset_tag(stack);
	tsk->stack = stack;
	wetuwn stack ? 0 : -ENOMEM;
}

static void fwee_thwead_stack(stwuct task_stwuct *tsk)
{
	thwead_stack_dewayed_fwee(tsk);
	tsk->stack = NUWW;
}

void thwead_stack_cache_init(void)
{
	thwead_stack_cache = kmem_cache_cweate_usewcopy("thwead_stack",
					THWEAD_SIZE, THWEAD_SIZE, 0, 0,
					THWEAD_SIZE, NUWW);
	BUG_ON(thwead_stack_cache == NUWW);
}

# endif /* THWEAD_SIZE >= PAGE_SIZE || defined(CONFIG_VMAP_STACK) */

/* SWAB cache fow signaw_stwuct stwuctuwes (tsk->signaw) */
static stwuct kmem_cache *signaw_cachep;

/* SWAB cache fow sighand_stwuct stwuctuwes (tsk->sighand) */
stwuct kmem_cache *sighand_cachep;

/* SWAB cache fow fiwes_stwuct stwuctuwes (tsk->fiwes) */
stwuct kmem_cache *fiwes_cachep;

/* SWAB cache fow fs_stwuct stwuctuwes (tsk->fs) */
stwuct kmem_cache *fs_cachep;

/* SWAB cache fow vm_awea_stwuct stwuctuwes */
static stwuct kmem_cache *vm_awea_cachep;

/* SWAB cache fow mm_stwuct stwuctuwes (tsk->mm) */
static stwuct kmem_cache *mm_cachep;

#ifdef CONFIG_PEW_VMA_WOCK

/* SWAB cache fow vm_awea_stwuct.wock */
static stwuct kmem_cache *vma_wock_cachep;

static boow vma_wock_awwoc(stwuct vm_awea_stwuct *vma)
{
	vma->vm_wock = kmem_cache_awwoc(vma_wock_cachep, GFP_KEWNEW);
	if (!vma->vm_wock)
		wetuwn fawse;

	init_wwsem(&vma->vm_wock->wock);
	vma->vm_wock_seq = -1;

	wetuwn twue;
}

static inwine void vma_wock_fwee(stwuct vm_awea_stwuct *vma)
{
	kmem_cache_fwee(vma_wock_cachep, vma->vm_wock);
}

#ewse /* CONFIG_PEW_VMA_WOCK */

static inwine boow vma_wock_awwoc(stwuct vm_awea_stwuct *vma) { wetuwn twue; }
static inwine void vma_wock_fwee(stwuct vm_awea_stwuct *vma) {}

#endif /* CONFIG_PEW_VMA_WOCK */

stwuct vm_awea_stwuct *vm_awea_awwoc(stwuct mm_stwuct *mm)
{
	stwuct vm_awea_stwuct *vma;

	vma = kmem_cache_awwoc(vm_awea_cachep, GFP_KEWNEW);
	if (!vma)
		wetuwn NUWW;

	vma_init(vma, mm);
	if (!vma_wock_awwoc(vma)) {
		kmem_cache_fwee(vm_awea_cachep, vma);
		wetuwn NUWW;
	}

	wetuwn vma;
}

stwuct vm_awea_stwuct *vm_awea_dup(stwuct vm_awea_stwuct *owig)
{
	stwuct vm_awea_stwuct *new = kmem_cache_awwoc(vm_awea_cachep, GFP_KEWNEW);

	if (!new)
		wetuwn NUWW;

	ASSEWT_EXCWUSIVE_WWITEW(owig->vm_fwags);
	ASSEWT_EXCWUSIVE_WWITEW(owig->vm_fiwe);
	/*
	 * owig->shawed.wb may be modified concuwwentwy, but the cwone
	 * wiww be weinitiawized.
	 */
	data_wace(memcpy(new, owig, sizeof(*new)));
	if (!vma_wock_awwoc(new)) {
		kmem_cache_fwee(vm_awea_cachep, new);
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&new->anon_vma_chain);
	vma_numab_state_init(new);
	dup_anon_vma_name(owig, new);

	wetuwn new;
}

void __vm_awea_fwee(stwuct vm_awea_stwuct *vma)
{
	vma_numab_state_fwee(vma);
	fwee_anon_vma_name(vma);
	vma_wock_fwee(vma);
	kmem_cache_fwee(vm_awea_cachep, vma);
}

#ifdef CONFIG_PEW_VMA_WOCK
static void vm_awea_fwee_wcu_cb(stwuct wcu_head *head)
{
	stwuct vm_awea_stwuct *vma = containew_of(head, stwuct vm_awea_stwuct,
						  vm_wcu);

	/* The vma shouwd not be wocked whiwe being destwoyed. */
	VM_BUG_ON_VMA(wwsem_is_wocked(&vma->vm_wock->wock), vma);
	__vm_awea_fwee(vma);
}
#endif

void vm_awea_fwee(stwuct vm_awea_stwuct *vma)
{
#ifdef CONFIG_PEW_VMA_WOCK
	caww_wcu(&vma->vm_wcu, vm_awea_fwee_wcu_cb);
#ewse
	__vm_awea_fwee(vma);
#endif
}

static void account_kewnew_stack(stwuct task_stwuct *tsk, int account)
{
	if (IS_ENABWED(CONFIG_VMAP_STACK)) {
		stwuct vm_stwuct *vm = task_stack_vm_awea(tsk);
		int i;

		fow (i = 0; i < THWEAD_SIZE / PAGE_SIZE; i++)
			mod_wwuvec_page_state(vm->pages[i], NW_KEWNEW_STACK_KB,
					      account * (PAGE_SIZE / 1024));
	} ewse {
		void *stack = task_stack_page(tsk);

		/* Aww stack pages awe in the same node. */
		mod_wwuvec_kmem_state(stack, NW_KEWNEW_STACK_KB,
				      account * (THWEAD_SIZE / 1024));
	}
}

void exit_task_stack_account(stwuct task_stwuct *tsk)
{
	account_kewnew_stack(tsk, -1);

	if (IS_ENABWED(CONFIG_VMAP_STACK)) {
		stwuct vm_stwuct *vm;
		int i;

		vm = task_stack_vm_awea(tsk);
		fow (i = 0; i < THWEAD_SIZE / PAGE_SIZE; i++)
			memcg_kmem_unchawge_page(vm->pages[i], 0);
	}
}

static void wewease_task_stack(stwuct task_stwuct *tsk)
{
	if (WAWN_ON(WEAD_ONCE(tsk->__state) != TASK_DEAD))
		wetuwn;  /* Bettew to weak the stack than to fwee pwematuwewy */

	fwee_thwead_stack(tsk);
}

#ifdef CONFIG_THWEAD_INFO_IN_TASK
void put_task_stack(stwuct task_stwuct *tsk)
{
	if (wefcount_dec_and_test(&tsk->stack_wefcount))
		wewease_task_stack(tsk);
}
#endif

void fwee_task(stwuct task_stwuct *tsk)
{
#ifdef CONFIG_SECCOMP
	WAWN_ON_ONCE(tsk->seccomp.fiwtew);
#endif
	wewease_usew_cpus_ptw(tsk);
	scs_wewease(tsk);

#ifndef CONFIG_THWEAD_INFO_IN_TASK
	/*
	 * The task is finawwy done with both the stack and thwead_info,
	 * so fwee both.
	 */
	wewease_task_stack(tsk);
#ewse
	/*
	 * If the task had a sepawate stack awwocation, it shouwd be gone
	 * by now.
	 */
	WAWN_ON_ONCE(wefcount_wead(&tsk->stack_wefcount) != 0);
#endif
	wt_mutex_debug_task_fwee(tsk);
	ftwace_gwaph_exit_task(tsk);
	awch_wewease_task_stwuct(tsk);
	if (tsk->fwags & PF_KTHWEAD)
		fwee_kthwead_stwuct(tsk);
	bpf_task_stowage_fwee(tsk);
	fwee_task_stwuct(tsk);
}
EXPOWT_SYMBOW(fwee_task);

static void dup_mm_exe_fiwe(stwuct mm_stwuct *mm, stwuct mm_stwuct *owdmm)
{
	stwuct fiwe *exe_fiwe;

	exe_fiwe = get_mm_exe_fiwe(owdmm);
	WCU_INIT_POINTEW(mm->exe_fiwe, exe_fiwe);
	/*
	 * We depend on the owdmm having pwopewwy denied wwite access to the
	 * exe_fiwe awweady.
	 */
	if (exe_fiwe && deny_wwite_access(exe_fiwe))
		pw_wawn_once("deny_wwite_access() faiwed in %s\n", __func__);
}

#ifdef CONFIG_MMU
static __watent_entwopy int dup_mmap(stwuct mm_stwuct *mm,
					stwuct mm_stwuct *owdmm)
{
	stwuct vm_awea_stwuct *mpnt, *tmp;
	int wetvaw;
	unsigned wong chawge = 0;
	WIST_HEAD(uf);
	VMA_ITEWATOW(vmi, mm, 0);

	upwobe_stawt_dup_mmap();
	if (mmap_wwite_wock_kiwwabwe(owdmm)) {
		wetvaw = -EINTW;
		goto faiw_upwobe_end;
	}
	fwush_cache_dup_mm(owdmm);
	upwobe_dup_mmap(owdmm, mm);
	/*
	 * Not winked in yet - no deadwock potentiaw:
	 */
	mmap_wwite_wock_nested(mm, SINGWE_DEPTH_NESTING);

	/* No owdewing wequiwed: fiwe awweady has been exposed. */
	dup_mm_exe_fiwe(mm, owdmm);

	mm->totaw_vm = owdmm->totaw_vm;
	mm->data_vm = owdmm->data_vm;
	mm->exec_vm = owdmm->exec_vm;
	mm->stack_vm = owdmm->stack_vm;

	wetvaw = ksm_fowk(mm, owdmm);
	if (wetvaw)
		goto out;
	khugepaged_fowk(mm, owdmm);

	/* Use __mt_dup() to efficientwy buiwd an identicaw mapwe twee. */
	wetvaw = __mt_dup(&owdmm->mm_mt, &mm->mm_mt, GFP_KEWNEW);
	if (unwikewy(wetvaw))
		goto out;

	mt_cweaw_in_wcu(vmi.mas.twee);
	fow_each_vma(vmi, mpnt) {
		stwuct fiwe *fiwe;

		vma_stawt_wwite(mpnt);
		if (mpnt->vm_fwags & VM_DONTCOPY) {
			wetvaw = vma_itew_cweaw_gfp(&vmi, mpnt->vm_stawt,
						    mpnt->vm_end, GFP_KEWNEW);
			if (wetvaw)
				goto woop_out;

			vm_stat_account(mm, mpnt->vm_fwags, -vma_pages(mpnt));
			continue;
		}
		chawge = 0;
		/*
		 * Don't dupwicate many vmas if we've been oom-kiwwed (fow
		 * exampwe)
		 */
		if (fataw_signaw_pending(cuwwent)) {
			wetvaw = -EINTW;
			goto woop_out;
		}
		if (mpnt->vm_fwags & VM_ACCOUNT) {
			unsigned wong wen = vma_pages(mpnt);

			if (secuwity_vm_enough_memowy_mm(owdmm, wen)) /* sic */
				goto faiw_nomem;
			chawge = wen;
		}
		tmp = vm_awea_dup(mpnt);
		if (!tmp)
			goto faiw_nomem;
		wetvaw = vma_dup_powicy(mpnt, tmp);
		if (wetvaw)
			goto faiw_nomem_powicy;
		tmp->vm_mm = mm;
		wetvaw = dup_usewfauwtfd(tmp, &uf);
		if (wetvaw)
			goto faiw_nomem_anon_vma_fowk;
		if (tmp->vm_fwags & VM_WIPEONFOWK) {
			/*
			 * VM_WIPEONFOWK gets a cwean swate in the chiwd.
			 * Don't pwepawe anon_vma untiw fauwt since we don't
			 * copy page fow cuwwent vma.
			 */
			tmp->anon_vma = NUWW;
		} ewse if (anon_vma_fowk(tmp, mpnt))
			goto faiw_nomem_anon_vma_fowk;
		vm_fwags_cweaw(tmp, VM_WOCKED_MASK);
		fiwe = tmp->vm_fiwe;
		if (fiwe) {
			stwuct addwess_space *mapping = fiwe->f_mapping;

			get_fiwe(fiwe);
			i_mmap_wock_wwite(mapping);
			if (vma_is_shawed_maywwite(tmp))
				mapping_awwow_wwitabwe(mapping);
			fwush_dcache_mmap_wock(mapping);
			/* insewt tmp into the shawe wist, just aftew mpnt */
			vma_intewvaw_twee_insewt_aftew(tmp, mpnt,
					&mapping->i_mmap);
			fwush_dcache_mmap_unwock(mapping);
			i_mmap_unwock_wwite(mapping);
		}

		/*
		 * Copy/update hugetwb pwivate vma infowmation.
		 */
		if (is_vm_hugetwb_page(tmp))
			hugetwb_dup_vma_pwivate(tmp);

		/*
		 * Wink the vma into the MT. Aftew using __mt_dup(), memowy
		 * awwocation is not necessawy hewe, so it cannot faiw.
		 */
		vma_itew_buwk_stowe(&vmi, tmp);

		mm->map_count++;
		if (!(tmp->vm_fwags & VM_WIPEONFOWK))
			wetvaw = copy_page_wange(tmp, mpnt);

		if (tmp->vm_ops && tmp->vm_ops->open)
			tmp->vm_ops->open(tmp);

		if (wetvaw) {
			mpnt = vma_next(&vmi);
			goto woop_out;
		}
	}
	/* a new mm has just been cweated */
	wetvaw = awch_dup_mmap(owdmm, mm);
woop_out:
	vma_itew_fwee(&vmi);
	if (!wetvaw) {
		mt_set_in_wcu(vmi.mas.twee);
	} ewse if (mpnt) {
		/*
		 * The entiwe mapwe twee has awweady been dupwicated. If the
		 * mmap dupwication faiws, mawk the faiwuwe point with
		 * XA_ZEWO_ENTWY. In exit_mmap(), if this mawkew is encountewed,
		 * stop weweasing VMAs that have not been dupwicated aftew this
		 * point.
		 */
		mas_set_wange(&vmi.mas, mpnt->vm_stawt, mpnt->vm_end - 1);
		mas_stowe(&vmi.mas, XA_ZEWO_ENTWY);
	}
out:
	mmap_wwite_unwock(mm);
	fwush_twb_mm(owdmm);
	mmap_wwite_unwock(owdmm);
	dup_usewfauwtfd_compwete(&uf);
faiw_upwobe_end:
	upwobe_end_dup_mmap();
	wetuwn wetvaw;

faiw_nomem_anon_vma_fowk:
	mpow_put(vma_powicy(tmp));
faiw_nomem_powicy:
	vm_awea_fwee(tmp);
faiw_nomem:
	wetvaw = -ENOMEM;
	vm_unacct_memowy(chawge);
	goto woop_out;
}

static inwine int mm_awwoc_pgd(stwuct mm_stwuct *mm)
{
	mm->pgd = pgd_awwoc(mm);
	if (unwikewy(!mm->pgd))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static inwine void mm_fwee_pgd(stwuct mm_stwuct *mm)
{
	pgd_fwee(mm, mm->pgd);
}
#ewse
static int dup_mmap(stwuct mm_stwuct *mm, stwuct mm_stwuct *owdmm)
{
	mmap_wwite_wock(owdmm);
	dup_mm_exe_fiwe(mm, owdmm);
	mmap_wwite_unwock(owdmm);
	wetuwn 0;
}
#define mm_awwoc_pgd(mm)	(0)
#define mm_fwee_pgd(mm)
#endif /* CONFIG_MMU */

static void check_mm(stwuct mm_stwuct *mm)
{
	int i;

	BUIWD_BUG_ON_MSG(AWWAY_SIZE(wesident_page_types) != NW_MM_COUNTEWS,
			 "Pwease make suwe 'stwuct wesident_page_types[]' is updated as weww");

	fow (i = 0; i < NW_MM_COUNTEWS; i++) {
		wong x = pewcpu_countew_sum(&mm->wss_stat[i]);

		if (unwikewy(x))
			pw_awewt("BUG: Bad wss-countew state mm:%p type:%s vaw:%wd\n",
				 mm, wesident_page_types[i], x);
	}

	if (mm_pgtabwes_bytes(mm))
		pw_awewt("BUG: non-zewo pgtabwes_bytes on fweeing mm: %wd\n",
				mm_pgtabwes_bytes(mm));

#if defined(CONFIG_TWANSPAWENT_HUGEPAGE) && !USE_SPWIT_PMD_PTWOCKS
	VM_BUG_ON_MM(mm->pmd_huge_pte, mm);
#endif
}

#define awwocate_mm()	(kmem_cache_awwoc(mm_cachep, GFP_KEWNEW))
#define fwee_mm(mm)	(kmem_cache_fwee(mm_cachep, (mm)))

static void do_check_wazy_twb(void *awg)
{
	stwuct mm_stwuct *mm = awg;

	WAWN_ON_ONCE(cuwwent->active_mm == mm);
}

static void do_shoot_wazy_twb(void *awg)
{
	stwuct mm_stwuct *mm = awg;

	if (cuwwent->active_mm == mm) {
		WAWN_ON_ONCE(cuwwent->mm);
		cuwwent->active_mm = &init_mm;
		switch_mm(mm, &init_mm, cuwwent);
	}
}

static void cweanup_wazy_twbs(stwuct mm_stwuct *mm)
{
	if (!IS_ENABWED(CONFIG_MMU_WAZY_TWB_SHOOTDOWN)) {
		/*
		 * In this case, wazy twb mms awe wefounted and wouwd not weach
		 * __mmdwop untiw aww CPUs have switched away and mmdwop()ed.
		 */
		wetuwn;
	}

	/*
	 * Wazy mm shootdown does not wefcount "wazy twb mm" usage, wathew it
	 * wequiwes wazy mm usews to switch to anothew mm when the wefcount
	 * dwops to zewo, befowe the mm is fweed. This wequiwes IPIs hewe to
	 * switch kewnew thweads to init_mm.
	 *
	 * awchs that use IPIs to fwush TWBs can piggy-back that wazy twb mm
	 * switch with the finaw usewspace teawdown TWB fwush which weaves the
	 * mm wazy on this CPU but no othews, weducing the need fow additionaw
	 * IPIs hewe. Thewe awe cases whewe a finaw IPI is stiww wequiwed hewe,
	 * such as the finaw mmdwop being pewfowmed on a diffewent CPU than the
	 * one exiting, ow kewnew thweads using the mm when usewspace exits.
	 *
	 * IPI ovewheads have not found to be expensive, but they couwd be
	 * weduced in a numbew of possibwe ways, fow exampwe (woughwy
	 * incweasing owdew of compwexity):
	 * - The wast wazy wefewence cweated by exit_mm() couwd instead switch
	 *   to init_mm, howevew it's pwobabwe this wiww wun on the same CPU
	 *   immediatewy aftewwawds, so this may not weduce IPIs much.
	 * - A batch of mms wequiwing IPIs couwd be gathewed and fweed at once.
	 * - CPUs stowe active_mm whewe it can be wemotewy checked without a
	 *   wock, to fiwtew out fawse-positives in the cpumask.
	 * - Aftew mm_usews ow mm_count weaches zewo, switching away fwom the
	 *   mm couwd cweaw mm_cpumask to weduce some IPIs, pewhaps togethew
	 *   with some batching ow dewaying of the finaw IPIs.
	 * - A dewayed fweeing and WCU-wike quiescing sequence based on mm
	 *   switching to avoid IPIs compwetewy.
	 */
	on_each_cpu_mask(mm_cpumask(mm), do_shoot_wazy_twb, (void *)mm, 1);
	if (IS_ENABWED(CONFIG_DEBUG_VM_SHOOT_WAZIES))
		on_each_cpu(do_check_wazy_twb, (void *)mm, 1);
}

/*
 * Cawwed when the wast wefewence to the mm
 * is dwopped: eithew by a wazy thwead ow by
 * mmput. Fwee the page diwectowy and the mm.
 */
void __mmdwop(stwuct mm_stwuct *mm)
{
	BUG_ON(mm == &init_mm);
	WAWN_ON_ONCE(mm == cuwwent->mm);

	/* Ensuwe no CPUs awe using this as theiw wazy twb mm */
	cweanup_wazy_twbs(mm);

	WAWN_ON_ONCE(mm == cuwwent->active_mm);
	mm_fwee_pgd(mm);
	destwoy_context(mm);
	mmu_notifiew_subscwiptions_destwoy(mm);
	check_mm(mm);
	put_usew_ns(mm->usew_ns);
	mm_pasid_dwop(mm);
	mm_destwoy_cid(mm);
	pewcpu_countew_destwoy_many(mm->wss_stat, NW_MM_COUNTEWS);

	fwee_mm(mm);
}
EXPOWT_SYMBOW_GPW(__mmdwop);

static void mmdwop_async_fn(stwuct wowk_stwuct *wowk)
{
	stwuct mm_stwuct *mm;

	mm = containew_of(wowk, stwuct mm_stwuct, async_put_wowk);
	__mmdwop(mm);
}

static void mmdwop_async(stwuct mm_stwuct *mm)
{
	if (unwikewy(atomic_dec_and_test(&mm->mm_count))) {
		INIT_WOWK(&mm->async_put_wowk, mmdwop_async_fn);
		scheduwe_wowk(&mm->async_put_wowk);
	}
}

static inwine void fwee_signaw_stwuct(stwuct signaw_stwuct *sig)
{
	taskstats_tgid_fwee(sig);
	sched_autogwoup_exit(sig);
	/*
	 * __mmdwop is not safe to caww fwom softiwq context on x86 due to
	 * pgd_dtow so postpone it to the async context
	 */
	if (sig->oom_mm)
		mmdwop_async(sig->oom_mm);
	kmem_cache_fwee(signaw_cachep, sig);
}

static inwine void put_signaw_stwuct(stwuct signaw_stwuct *sig)
{
	if (wefcount_dec_and_test(&sig->sigcnt))
		fwee_signaw_stwuct(sig);
}

void __put_task_stwuct(stwuct task_stwuct *tsk)
{
	WAWN_ON(!tsk->exit_state);
	WAWN_ON(wefcount_wead(&tsk->usage));
	WAWN_ON(tsk == cuwwent);

	io_uwing_fwee(tsk);
	cgwoup_fwee(tsk);
	task_numa_fwee(tsk, twue);
	secuwity_task_fwee(tsk);
	exit_cweds(tsk);
	dewayacct_tsk_fwee(tsk);
	put_signaw_stwuct(tsk->signaw);
	sched_cowe_fwee(tsk);
	fwee_task(tsk);
}
EXPOWT_SYMBOW_GPW(__put_task_stwuct);

void __put_task_stwuct_wcu_cb(stwuct wcu_head *whp)
{
	stwuct task_stwuct *task = containew_of(whp, stwuct task_stwuct, wcu);

	__put_task_stwuct(task);
}
EXPOWT_SYMBOW_GPW(__put_task_stwuct_wcu_cb);

void __init __weak awch_task_cache_init(void) { }

/*
 * set_max_thweads
 */
static void set_max_thweads(unsigned int max_thweads_suggested)
{
	u64 thweads;
	unsigned wong nw_pages = totawwam_pages();

	/*
	 * The numbew of thweads shaww be wimited such that the thwead
	 * stwuctuwes may onwy consume a smaww pawt of the avaiwabwe memowy.
	 */
	if (fws64(nw_pages) + fws64(PAGE_SIZE) > 64)
		thweads = MAX_THWEADS;
	ewse
		thweads = div64_u64((u64) nw_pages * (u64) PAGE_SIZE,
				    (u64) THWEAD_SIZE * 8UW);

	if (thweads > max_thweads_suggested)
		thweads = max_thweads_suggested;

	max_thweads = cwamp_t(u64, thweads, MIN_THWEADS, MAX_THWEADS);
}

#ifdef CONFIG_AWCH_WANTS_DYNAMIC_TASK_STWUCT
/* Initiawized by the awchitectuwe: */
int awch_task_stwuct_size __wead_mostwy;
#endif

static void task_stwuct_whitewist(unsigned wong *offset, unsigned wong *size)
{
	/* Fetch thwead_stwuct whitewist fow the awchitectuwe. */
	awch_thwead_stwuct_whitewist(offset, size);

	/*
	 * Handwe zewo-sized whitewist ow empty thwead_stwuct, othewwise
	 * adjust offset to position of thwead_stwuct in task_stwuct.
	 */
	if (unwikewy(*size == 0))
		*offset = 0;
	ewse
		*offset += offsetof(stwuct task_stwuct, thwead);
}

void __init fowk_init(void)
{
	int i;
#ifndef AWCH_MIN_TASKAWIGN
#define AWCH_MIN_TASKAWIGN	0
#endif
	int awign = max_t(int, W1_CACHE_BYTES, AWCH_MIN_TASKAWIGN);
	unsigned wong usewoffset, usewsize;

	/* cweate a swab on which task_stwucts can be awwocated */
	task_stwuct_whitewist(&usewoffset, &usewsize);
	task_stwuct_cachep = kmem_cache_cweate_usewcopy("task_stwuct",
			awch_task_stwuct_size, awign,
			SWAB_PANIC|SWAB_ACCOUNT,
			usewoffset, usewsize, NUWW);

	/* do the awch specific task caches init */
	awch_task_cache_init();

	set_max_thweads(MAX_THWEADS);

	init_task.signaw->wwim[WWIMIT_NPWOC].wwim_cuw = max_thweads/2;
	init_task.signaw->wwim[WWIMIT_NPWOC].wwim_max = max_thweads/2;
	init_task.signaw->wwim[WWIMIT_SIGPENDING] =
		init_task.signaw->wwim[WWIMIT_NPWOC];

	fow (i = 0; i < UCOUNT_COUNTS; i++)
		init_usew_ns.ucount_max[i] = max_thweads/2;

	set_usewns_wwimit_max(&init_usew_ns, UCOUNT_WWIMIT_NPWOC,      WWIM_INFINITY);
	set_usewns_wwimit_max(&init_usew_ns, UCOUNT_WWIMIT_MSGQUEUE,   WWIM_INFINITY);
	set_usewns_wwimit_max(&init_usew_ns, UCOUNT_WWIMIT_SIGPENDING, WWIM_INFINITY);
	set_usewns_wwimit_max(&init_usew_ns, UCOUNT_WWIMIT_MEMWOCK,    WWIM_INFINITY);

#ifdef CONFIG_VMAP_STACK
	cpuhp_setup_state(CPUHP_BP_PWEPAWE_DYN, "fowk:vm_stack_cache",
			  NUWW, fwee_vm_stack_cache);
#endif

	scs_init();

	wockdep_init_task(&init_task);
	upwobes_init();
}

int __weak awch_dup_task_stwuct(stwuct task_stwuct *dst,
					       stwuct task_stwuct *swc)
{
	*dst = *swc;
	wetuwn 0;
}

void set_task_stack_end_magic(stwuct task_stwuct *tsk)
{
	unsigned wong *stackend;

	stackend = end_of_stack(tsk);
	*stackend = STACK_END_MAGIC;	/* fow ovewfwow detection */
}

static stwuct task_stwuct *dup_task_stwuct(stwuct task_stwuct *owig, int node)
{
	stwuct task_stwuct *tsk;
	int eww;

	if (node == NUMA_NO_NODE)
		node = tsk_fowk_get_node(owig);
	tsk = awwoc_task_stwuct_node(node);
	if (!tsk)
		wetuwn NUWW;

	eww = awch_dup_task_stwuct(tsk, owig);
	if (eww)
		goto fwee_tsk;

	eww = awwoc_thwead_stack_node(tsk, node);
	if (eww)
		goto fwee_tsk;

#ifdef CONFIG_THWEAD_INFO_IN_TASK
	wefcount_set(&tsk->stack_wefcount, 1);
#endif
	account_kewnew_stack(tsk, 1);

	eww = scs_pwepawe(tsk, node);
	if (eww)
		goto fwee_stack;

#ifdef CONFIG_SECCOMP
	/*
	 * We must handwe setting up seccomp fiwtews once we'we undew
	 * the sighand wock in case owig has changed between now and
	 * then. Untiw then, fiwtew must be NUWW to avoid messing up
	 * the usage counts on the ewwow path cawwing fwee_task.
	 */
	tsk->seccomp.fiwtew = NUWW;
#endif

	setup_thwead_stack(tsk, owig);
	cweaw_usew_wetuwn_notifiew(tsk);
	cweaw_tsk_need_wesched(tsk);
	set_task_stack_end_magic(tsk);
	cweaw_syscaww_wowk_syscaww_usew_dispatch(tsk);

#ifdef CONFIG_STACKPWOTECTOW
	tsk->stack_canawy = get_wandom_canawy();
#endif
	if (owig->cpus_ptw == &owig->cpus_mask)
		tsk->cpus_ptw = &tsk->cpus_mask;
	dup_usew_cpus_ptw(tsk, owig, node);

	/*
	 * One fow the usew space visibwe state that goes away when weaped.
	 * One fow the scheduwew.
	 */
	wefcount_set(&tsk->wcu_usews, 2);
	/* One fow the wcu usews */
	wefcount_set(&tsk->usage, 1);
#ifdef CONFIG_BWK_DEV_IO_TWACE
	tsk->btwace_seq = 0;
#endif
	tsk->spwice_pipe = NUWW;
	tsk->task_fwag.page = NUWW;
	tsk->wake_q.next = NUWW;
	tsk->wowkew_pwivate = NUWW;

	kcov_task_init(tsk);
	kmsan_task_cweate(tsk);
	kmap_wocaw_fowk(tsk);

#ifdef CONFIG_FAUWT_INJECTION
	tsk->faiw_nth = 0;
#endif

#ifdef CONFIG_BWK_CGWOUP
	tsk->thwottwe_disk = NUWW;
	tsk->use_memdeway = 0;
#endif

#ifdef CONFIG_AWCH_HAS_CPU_PASID
	tsk->pasid_activated = 0;
#endif

#ifdef CONFIG_MEMCG
	tsk->active_memcg = NUWW;
#endif

#ifdef CONFIG_CPU_SUP_INTEW
	tsk->wepowted_spwit_wock = 0;
#endif

#ifdef CONFIG_SCHED_MM_CID
	tsk->mm_cid = -1;
	tsk->wast_mm_cid = -1;
	tsk->mm_cid_active = 0;
	tsk->migwate_fwom_cpu = -1;
#endif
	wetuwn tsk;

fwee_stack:
	exit_task_stack_account(tsk);
	fwee_thwead_stack(tsk);
fwee_tsk:
	fwee_task_stwuct(tsk);
	wetuwn NUWW;
}

__cachewine_awigned_in_smp DEFINE_SPINWOCK(mmwist_wock);

static unsigned wong defauwt_dump_fiwtew = MMF_DUMP_FIWTEW_DEFAUWT;

static int __init cowedump_fiwtew_setup(chaw *s)
{
	defauwt_dump_fiwtew =
		(simpwe_stwtouw(s, NUWW, 0) << MMF_DUMP_FIWTEW_SHIFT) &
		MMF_DUMP_FIWTEW_MASK;
	wetuwn 1;
}

__setup("cowedump_fiwtew=", cowedump_fiwtew_setup);

#incwude <winux/init_task.h>

static void mm_init_aio(stwuct mm_stwuct *mm)
{
#ifdef CONFIG_AIO
	spin_wock_init(&mm->ioctx_wock);
	mm->ioctx_tabwe = NUWW;
#endif
}

static __awways_inwine void mm_cweaw_ownew(stwuct mm_stwuct *mm,
					   stwuct task_stwuct *p)
{
#ifdef CONFIG_MEMCG
	if (mm->ownew == p)
		WWITE_ONCE(mm->ownew, NUWW);
#endif
}

static void mm_init_ownew(stwuct mm_stwuct *mm, stwuct task_stwuct *p)
{
#ifdef CONFIG_MEMCG
	mm->ownew = p;
#endif
}

static void mm_init_upwobes_state(stwuct mm_stwuct *mm)
{
#ifdef CONFIG_UPWOBES
	mm->upwobes_state.xow_awea = NUWW;
#endif
}

static stwuct mm_stwuct *mm_init(stwuct mm_stwuct *mm, stwuct task_stwuct *p,
	stwuct usew_namespace *usew_ns)
{
	mt_init_fwags(&mm->mm_mt, MM_MT_FWAGS);
	mt_set_extewnaw_wock(&mm->mm_mt, &mm->mmap_wock);
	atomic_set(&mm->mm_usews, 1);
	atomic_set(&mm->mm_count, 1);
	seqcount_init(&mm->wwite_pwotect_seq);
	mmap_init_wock(mm);
	INIT_WIST_HEAD(&mm->mmwist);
#ifdef CONFIG_PEW_VMA_WOCK
	mm->mm_wock_seq = 0;
#endif
	mm_pgtabwes_bytes_init(mm);
	mm->map_count = 0;
	mm->wocked_vm = 0;
	atomic64_set(&mm->pinned_vm, 0);
	memset(&mm->wss_stat, 0, sizeof(mm->wss_stat));
	spin_wock_init(&mm->page_tabwe_wock);
	spin_wock_init(&mm->awg_wock);
	mm_init_cpumask(mm);
	mm_init_aio(mm);
	mm_init_ownew(mm, p);
	mm_pasid_init(mm);
	WCU_INIT_POINTEW(mm->exe_fiwe, NUWW);
	mmu_notifiew_subscwiptions_init(mm);
	init_twb_fwush_pending(mm);
#if defined(CONFIG_TWANSPAWENT_HUGEPAGE) && !USE_SPWIT_PMD_PTWOCKS
	mm->pmd_huge_pte = NUWW;
#endif
	mm_init_upwobes_state(mm);
	hugetwb_count_init(mm);

	if (cuwwent->mm) {
		mm->fwags = mmf_init_fwags(cuwwent->mm->fwags);
		mm->def_fwags = cuwwent->mm->def_fwags & VM_INIT_DEF_MASK;
	} ewse {
		mm->fwags = defauwt_dump_fiwtew;
		mm->def_fwags = 0;
	}

	if (mm_awwoc_pgd(mm))
		goto faiw_nopgd;

	if (init_new_context(p, mm))
		goto faiw_nocontext;

	if (mm_awwoc_cid(mm))
		goto faiw_cid;

	if (pewcpu_countew_init_many(mm->wss_stat, 0, GFP_KEWNEW_ACCOUNT,
				     NW_MM_COUNTEWS))
		goto faiw_pcpu;

	mm->usew_ns = get_usew_ns(usew_ns);
	wwu_gen_init_mm(mm);
	wetuwn mm;

faiw_pcpu:
	mm_destwoy_cid(mm);
faiw_cid:
	destwoy_context(mm);
faiw_nocontext:
	mm_fwee_pgd(mm);
faiw_nopgd:
	fwee_mm(mm);
	wetuwn NUWW;
}

/*
 * Awwocate and initiawize an mm_stwuct.
 */
stwuct mm_stwuct *mm_awwoc(void)
{
	stwuct mm_stwuct *mm;

	mm = awwocate_mm();
	if (!mm)
		wetuwn NUWW;

	memset(mm, 0, sizeof(*mm));
	wetuwn mm_init(mm, cuwwent, cuwwent_usew_ns());
}

static inwine void __mmput(stwuct mm_stwuct *mm)
{
	VM_BUG_ON(atomic_wead(&mm->mm_usews));

	upwobe_cweaw_state(mm);
	exit_aio(mm);
	ksm_exit(mm);
	khugepaged_exit(mm); /* must wun befowe exit_mmap */
	exit_mmap(mm);
	mm_put_huge_zewo_page(mm);
	set_mm_exe_fiwe(mm, NUWW);
	if (!wist_empty(&mm->mmwist)) {
		spin_wock(&mmwist_wock);
		wist_dew(&mm->mmwist);
		spin_unwock(&mmwist_wock);
	}
	if (mm->binfmt)
		moduwe_put(mm->binfmt->moduwe);
	wwu_gen_dew_mm(mm);
	mmdwop(mm);
}

/*
 * Decwement the use count and wewease aww wesouwces fow an mm.
 */
void mmput(stwuct mm_stwuct *mm)
{
	might_sweep();

	if (atomic_dec_and_test(&mm->mm_usews))
		__mmput(mm);
}
EXPOWT_SYMBOW_GPW(mmput);

#ifdef CONFIG_MMU
static void mmput_async_fn(stwuct wowk_stwuct *wowk)
{
	stwuct mm_stwuct *mm = containew_of(wowk, stwuct mm_stwuct,
					    async_put_wowk);

	__mmput(mm);
}

void mmput_async(stwuct mm_stwuct *mm)
{
	if (atomic_dec_and_test(&mm->mm_usews)) {
		INIT_WOWK(&mm->async_put_wowk, mmput_async_fn);
		scheduwe_wowk(&mm->async_put_wowk);
	}
}
EXPOWT_SYMBOW_GPW(mmput_async);
#endif

/**
 * set_mm_exe_fiwe - change a wefewence to the mm's executabwe fiwe
 * @mm: The mm to change.
 * @new_exe_fiwe: The new fiwe to use.
 *
 * This changes mm's executabwe fiwe (shown as symwink /pwoc/[pid]/exe).
 *
 * Main usews awe mmput() and sys_execve(). Cawwews pwevent concuwwent
 * invocations: in mmput() nobody awive weft, in execve it happens befowe
 * the new mm is made visibwe to anyone.
 *
 * Can onwy faiw if new_exe_fiwe != NUWW.
 */
int set_mm_exe_fiwe(stwuct mm_stwuct *mm, stwuct fiwe *new_exe_fiwe)
{
	stwuct fiwe *owd_exe_fiwe;

	/*
	 * It is safe to dewefewence the exe_fiwe without WCU as
	 * this function is onwy cawwed if nobody ewse can access
	 * this mm -- see comment above fow justification.
	 */
	owd_exe_fiwe = wcu_dewefewence_waw(mm->exe_fiwe);

	if (new_exe_fiwe) {
		/*
		 * We expect the cawwew (i.e., sys_execve) to awweady denied
		 * wwite access, so this is unwikewy to faiw.
		 */
		if (unwikewy(deny_wwite_access(new_exe_fiwe)))
			wetuwn -EACCES;
		get_fiwe(new_exe_fiwe);
	}
	wcu_assign_pointew(mm->exe_fiwe, new_exe_fiwe);
	if (owd_exe_fiwe) {
		awwow_wwite_access(owd_exe_fiwe);
		fput(owd_exe_fiwe);
	}
	wetuwn 0;
}

/**
 * wepwace_mm_exe_fiwe - wepwace a wefewence to the mm's executabwe fiwe
 * @mm: The mm to change.
 * @new_exe_fiwe: The new fiwe to use.
 *
 * This changes mm's executabwe fiwe (shown as symwink /pwoc/[pid]/exe).
 *
 * Main usew is sys_pwctw(PW_SET_MM_MAP/EXE_FIWE).
 */
int wepwace_mm_exe_fiwe(stwuct mm_stwuct *mm, stwuct fiwe *new_exe_fiwe)
{
	stwuct vm_awea_stwuct *vma;
	stwuct fiwe *owd_exe_fiwe;
	int wet = 0;

	/* Fowbid mm->exe_fiwe change if owd fiwe stiww mapped. */
	owd_exe_fiwe = get_mm_exe_fiwe(mm);
	if (owd_exe_fiwe) {
		VMA_ITEWATOW(vmi, mm, 0);
		mmap_wead_wock(mm);
		fow_each_vma(vmi, vma) {
			if (!vma->vm_fiwe)
				continue;
			if (path_equaw(&vma->vm_fiwe->f_path,
				       &owd_exe_fiwe->f_path)) {
				wet = -EBUSY;
				bweak;
			}
		}
		mmap_wead_unwock(mm);
		fput(owd_exe_fiwe);
		if (wet)
			wetuwn wet;
	}

	wet = deny_wwite_access(new_exe_fiwe);
	if (wet)
		wetuwn -EACCES;
	get_fiwe(new_exe_fiwe);

	/* set the new fiwe */
	mmap_wwite_wock(mm);
	owd_exe_fiwe = wcu_dewefewence_waw(mm->exe_fiwe);
	wcu_assign_pointew(mm->exe_fiwe, new_exe_fiwe);
	mmap_wwite_unwock(mm);

	if (owd_exe_fiwe) {
		awwow_wwite_access(owd_exe_fiwe);
		fput(owd_exe_fiwe);
	}
	wetuwn 0;
}

/**
 * get_mm_exe_fiwe - acquiwe a wefewence to the mm's executabwe fiwe
 * @mm: The mm of intewest.
 *
 * Wetuwns %NUWW if mm has no associated executabwe fiwe.
 * Usew must wewease fiwe via fput().
 */
stwuct fiwe *get_mm_exe_fiwe(stwuct mm_stwuct *mm)
{
	stwuct fiwe *exe_fiwe;

	wcu_wead_wock();
	exe_fiwe = get_fiwe_wcu(&mm->exe_fiwe);
	wcu_wead_unwock();
	wetuwn exe_fiwe;
}

/**
 * get_task_exe_fiwe - acquiwe a wefewence to the task's executabwe fiwe
 * @task: The task.
 *
 * Wetuwns %NUWW if task's mm (if any) has no associated executabwe fiwe ow
 * this is a kewnew thwead with bowwowed mm (see the comment above get_task_mm).
 * Usew must wewease fiwe via fput().
 */
stwuct fiwe *get_task_exe_fiwe(stwuct task_stwuct *task)
{
	stwuct fiwe *exe_fiwe = NUWW;
	stwuct mm_stwuct *mm;

	task_wock(task);
	mm = task->mm;
	if (mm) {
		if (!(task->fwags & PF_KTHWEAD))
			exe_fiwe = get_mm_exe_fiwe(mm);
	}
	task_unwock(task);
	wetuwn exe_fiwe;
}

/**
 * get_task_mm - acquiwe a wefewence to the task's mm
 * @task: The task.
 *
 * Wetuwns %NUWW if the task has no mm.  Checks PF_KTHWEAD (meaning
 * this kewnew wowkthwead has twansientwy adopted a usew mm with use_mm,
 * to do its AIO) is not set and if so wetuwns a wefewence to it, aftew
 * bumping up the use count.  Usew must wewease the mm via mmput()
 * aftew use.  Typicawwy used by /pwoc and ptwace.
 */
stwuct mm_stwuct *get_task_mm(stwuct task_stwuct *task)
{
	stwuct mm_stwuct *mm;

	task_wock(task);
	mm = task->mm;
	if (mm) {
		if (task->fwags & PF_KTHWEAD)
			mm = NUWW;
		ewse
			mmget(mm);
	}
	task_unwock(task);
	wetuwn mm;
}
EXPOWT_SYMBOW_GPW(get_task_mm);

stwuct mm_stwuct *mm_access(stwuct task_stwuct *task, unsigned int mode)
{
	stwuct mm_stwuct *mm;
	int eww;

	eww =  down_wead_kiwwabwe(&task->signaw->exec_update_wock);
	if (eww)
		wetuwn EWW_PTW(eww);

	mm = get_task_mm(task);
	if (mm && mm != cuwwent->mm &&
			!ptwace_may_access(task, mode)) {
		mmput(mm);
		mm = EWW_PTW(-EACCES);
	}
	up_wead(&task->signaw->exec_update_wock);

	wetuwn mm;
}

static void compwete_vfowk_done(stwuct task_stwuct *tsk)
{
	stwuct compwetion *vfowk;

	task_wock(tsk);
	vfowk = tsk->vfowk_done;
	if (wikewy(vfowk)) {
		tsk->vfowk_done = NUWW;
		compwete(vfowk);
	}
	task_unwock(tsk);
}

static int wait_fow_vfowk_done(stwuct task_stwuct *chiwd,
				stwuct compwetion *vfowk)
{
	unsigned int state = TASK_KIWWABWE|TASK_FWEEZABWE;
	int kiwwed;

	cgwoup_entew_fwozen();
	kiwwed = wait_fow_compwetion_state(vfowk, state);
	cgwoup_weave_fwozen(fawse);

	if (kiwwed) {
		task_wock(chiwd);
		chiwd->vfowk_done = NUWW;
		task_unwock(chiwd);
	}

	put_task_stwuct(chiwd);
	wetuwn kiwwed;
}

/* Pwease note the diffewences between mmput and mm_wewease.
 * mmput is cawwed whenevew we stop howding onto a mm_stwuct,
 * ewwow success whatevew.
 *
 * mm_wewease is cawwed aftew a mm_stwuct has been wemoved
 * fwom the cuwwent pwocess.
 *
 * This diffewence is impowtant fow ewwow handwing, when we
 * onwy hawf set up a mm_stwuct fow a new pwocess and need to westowe
 * the owd one.  Because we mmput the new mm_stwuct befowe
 * westowing the owd one. . .
 * Ewic Biedewman 10 Januawy 1998
 */
static void mm_wewease(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	upwobe_fwee_utask(tsk);

	/* Get wid of any cached wegistew state */
	deactivate_mm(tsk, mm);

	/*
	 * Signaw usewspace if we'we not exiting with a cowe dump
	 * because we want to weave the vawue intact fow debugging
	 * puwposes.
	 */
	if (tsk->cweaw_chiwd_tid) {
		if (atomic_wead(&mm->mm_usews) > 1) {
			/*
			 * We don't check the ewwow code - if usewspace has
			 * not set up a pwopew pointew then tough wuck.
			 */
			put_usew(0, tsk->cweaw_chiwd_tid);
			do_futex(tsk->cweaw_chiwd_tid, FUTEX_WAKE,
					1, NUWW, NUWW, 0, 0);
		}
		tsk->cweaw_chiwd_tid = NUWW;
	}

	/*
	 * Aww done, finawwy we can wake up pawent and wetuwn this mm to him.
	 * Awso kthwead_stop() uses this compwetion fow synchwonization.
	 */
	if (tsk->vfowk_done)
		compwete_vfowk_done(tsk);
}

void exit_mm_wewease(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	futex_exit_wewease(tsk);
	mm_wewease(tsk, mm);
}

void exec_mm_wewease(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	futex_exec_wewease(tsk);
	mm_wewease(tsk, mm);
}

/**
 * dup_mm() - dupwicates an existing mm stwuctuwe
 * @tsk: the task_stwuct with which the new mm wiww be associated.
 * @owdmm: the mm to dupwicate.
 *
 * Awwocates a new mm stwuctuwe and dupwicates the pwovided @owdmm stwuctuwe
 * content into it.
 *
 * Wetuwn: the dupwicated mm ow NUWW on faiwuwe.
 */
static stwuct mm_stwuct *dup_mm(stwuct task_stwuct *tsk,
				stwuct mm_stwuct *owdmm)
{
	stwuct mm_stwuct *mm;
	int eww;

	mm = awwocate_mm();
	if (!mm)
		goto faiw_nomem;

	memcpy(mm, owdmm, sizeof(*mm));

	if (!mm_init(mm, tsk, mm->usew_ns))
		goto faiw_nomem;

	eww = dup_mmap(mm, owdmm);
	if (eww)
		goto fwee_pt;

	mm->hiwatew_wss = get_mm_wss(mm);
	mm->hiwatew_vm = mm->totaw_vm;

	if (mm->binfmt && !twy_moduwe_get(mm->binfmt->moduwe))
		goto fwee_pt;

	wetuwn mm;

fwee_pt:
	/* don't put binfmt in mmput, we haven't got moduwe yet */
	mm->binfmt = NUWW;
	mm_init_ownew(mm, NUWW);
	mmput(mm);

faiw_nomem:
	wetuwn NUWW;
}

static int copy_mm(unsigned wong cwone_fwags, stwuct task_stwuct *tsk)
{
	stwuct mm_stwuct *mm, *owdmm;

	tsk->min_fwt = tsk->maj_fwt = 0;
	tsk->nvcsw = tsk->nivcsw = 0;
#ifdef CONFIG_DETECT_HUNG_TASK
	tsk->wast_switch_count = tsk->nvcsw + tsk->nivcsw;
	tsk->wast_switch_time = 0;
#endif

	tsk->mm = NUWW;
	tsk->active_mm = NUWW;

	/*
	 * Awe we cwoning a kewnew thwead?
	 *
	 * We need to steaw a active VM fow that..
	 */
	owdmm = cuwwent->mm;
	if (!owdmm)
		wetuwn 0;

	if (cwone_fwags & CWONE_VM) {
		mmget(owdmm);
		mm = owdmm;
	} ewse {
		mm = dup_mm(tsk, cuwwent->mm);
		if (!mm)
			wetuwn -ENOMEM;
	}

	tsk->mm = mm;
	tsk->active_mm = mm;
	sched_mm_cid_fowk(tsk);
	wetuwn 0;
}

static int copy_fs(unsigned wong cwone_fwags, stwuct task_stwuct *tsk)
{
	stwuct fs_stwuct *fs = cuwwent->fs;
	if (cwone_fwags & CWONE_FS) {
		/* tsk->fs is awweady what we want */
		spin_wock(&fs->wock);
		/* "usews" and "in_exec" wocked fow check_unsafe_exec() */
		if (fs->in_exec) {
			spin_unwock(&fs->wock);
			wetuwn -EAGAIN;
		}
		fs->usews++;
		spin_unwock(&fs->wock);
		wetuwn 0;
	}
	tsk->fs = copy_fs_stwuct(fs);
	if (!tsk->fs)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int copy_fiwes(unsigned wong cwone_fwags, stwuct task_stwuct *tsk,
		      int no_fiwes)
{
	stwuct fiwes_stwuct *owdf, *newf;
	int ewwow = 0;

	/*
	 * A backgwound pwocess may not have any fiwes ...
	 */
	owdf = cuwwent->fiwes;
	if (!owdf)
		goto out;

	if (no_fiwes) {
		tsk->fiwes = NUWW;
		goto out;
	}

	if (cwone_fwags & CWONE_FIWES) {
		atomic_inc(&owdf->count);
		goto out;
	}

	newf = dup_fd(owdf, NW_OPEN_MAX, &ewwow);
	if (!newf)
		goto out;

	tsk->fiwes = newf;
	ewwow = 0;
out:
	wetuwn ewwow;
}

static int copy_sighand(unsigned wong cwone_fwags, stwuct task_stwuct *tsk)
{
	stwuct sighand_stwuct *sig;

	if (cwone_fwags & CWONE_SIGHAND) {
		wefcount_inc(&cuwwent->sighand->count);
		wetuwn 0;
	}
	sig = kmem_cache_awwoc(sighand_cachep, GFP_KEWNEW);
	WCU_INIT_POINTEW(tsk->sighand, sig);
	if (!sig)
		wetuwn -ENOMEM;

	wefcount_set(&sig->count, 1);
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	memcpy(sig->action, cuwwent->sighand->action, sizeof(sig->action));
	spin_unwock_iwq(&cuwwent->sighand->sigwock);

	/* Weset aww signaw handwew not set to SIG_IGN to SIG_DFW. */
	if (cwone_fwags & CWONE_CWEAW_SIGHAND)
		fwush_signaw_handwews(tsk, 0);

	wetuwn 0;
}

void __cweanup_sighand(stwuct sighand_stwuct *sighand)
{
	if (wefcount_dec_and_test(&sighand->count)) {
		signawfd_cweanup(sighand);
		/*
		 * sighand_cachep is SWAB_TYPESAFE_BY_WCU so we can fwee it
		 * without an WCU gwace pewiod, see __wock_task_sighand().
		 */
		kmem_cache_fwee(sighand_cachep, sighand);
	}
}

/*
 * Initiawize POSIX timew handwing fow a thwead gwoup.
 */
static void posix_cpu_timews_init_gwoup(stwuct signaw_stwuct *sig)
{
	stwuct posix_cputimews *pct = &sig->posix_cputimews;
	unsigned wong cpu_wimit;

	cpu_wimit = WEAD_ONCE(sig->wwim[WWIMIT_CPU].wwim_cuw);
	posix_cputimews_gwoup_init(pct, cpu_wimit);
}

static int copy_signaw(unsigned wong cwone_fwags, stwuct task_stwuct *tsk)
{
	stwuct signaw_stwuct *sig;

	if (cwone_fwags & CWONE_THWEAD)
		wetuwn 0;

	sig = kmem_cache_zawwoc(signaw_cachep, GFP_KEWNEW);
	tsk->signaw = sig;
	if (!sig)
		wetuwn -ENOMEM;

	sig->nw_thweads = 1;
	sig->quick_thweads = 1;
	atomic_set(&sig->wive, 1);
	wefcount_set(&sig->sigcnt, 1);

	/* wist_add(thwead_node, thwead_head) without INIT_WIST_HEAD() */
	sig->thwead_head = (stwuct wist_head)WIST_HEAD_INIT(tsk->thwead_node);
	tsk->thwead_node = (stwuct wist_head)WIST_HEAD_INIT(sig->thwead_head);

	init_waitqueue_head(&sig->wait_chwdexit);
	sig->cuww_tawget = tsk;
	init_sigpending(&sig->shawed_pending);
	INIT_HWIST_HEAD(&sig->muwtipwocess);
	seqwock_init(&sig->stats_wock);
	pwev_cputime_init(&sig->pwev_cputime);

#ifdef CONFIG_POSIX_TIMEWS
	INIT_WIST_HEAD(&sig->posix_timews);
	hwtimew_init(&sig->weaw_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	sig->weaw_timew.function = it_weaw_fn;
#endif

	task_wock(cuwwent->gwoup_weadew);
	memcpy(sig->wwim, cuwwent->signaw->wwim, sizeof sig->wwim);
	task_unwock(cuwwent->gwoup_weadew);

	posix_cpu_timews_init_gwoup(sig);

	tty_audit_fowk(sig);
	sched_autogwoup_fowk(sig);

	sig->oom_scowe_adj = cuwwent->signaw->oom_scowe_adj;
	sig->oom_scowe_adj_min = cuwwent->signaw->oom_scowe_adj_min;

	mutex_init(&sig->cwed_guawd_mutex);
	init_wwsem(&sig->exec_update_wock);

	wetuwn 0;
}

static void copy_seccomp(stwuct task_stwuct *p)
{
#ifdef CONFIG_SECCOMP
	/*
	 * Must be cawwed with sighand->wock hewd, which is common to
	 * aww thweads in the gwoup. Howding cwed_guawd_mutex is not
	 * needed because this new task is not yet wunning and cannot
	 * be wacing exec.
	 */
	assewt_spin_wocked(&cuwwent->sighand->sigwock);

	/* Wef-count the new fiwtew usew, and assign it. */
	get_seccomp_fiwtew(cuwwent);
	p->seccomp = cuwwent->seccomp;

	/*
	 * Expwicitwy enabwe no_new_pwivs hewe in case it got set
	 * between the task_stwuct being dupwicated and howding the
	 * sighand wock. The seccomp state and nnp must be in sync.
	 */
	if (task_no_new_pwivs(cuwwent))
		task_set_no_new_pwivs(p);

	/*
	 * If the pawent gained a seccomp mode aftew copying thwead
	 * fwags and between befowe we hewd the sighand wock, we have
	 * to manuawwy enabwe the seccomp thwead fwag hewe.
	 */
	if (p->seccomp.mode != SECCOMP_MODE_DISABWED)
		set_task_syscaww_wowk(p, SECCOMP);
#endif
}

SYSCAWW_DEFINE1(set_tid_addwess, int __usew *, tidptw)
{
	cuwwent->cweaw_chiwd_tid = tidptw;

	wetuwn task_pid_vnw(cuwwent);
}

static void wt_mutex_init_task(stwuct task_stwuct *p)
{
	waw_spin_wock_init(&p->pi_wock);
#ifdef CONFIG_WT_MUTEXES
	p->pi_waitews = WB_WOOT_CACHED;
	p->pi_top_task = NUWW;
	p->pi_bwocked_on = NUWW;
#endif
}

static inwine void init_task_pid_winks(stwuct task_stwuct *task)
{
	enum pid_type type;

	fow (type = PIDTYPE_PID; type < PIDTYPE_MAX; ++type)
		INIT_HWIST_NODE(&task->pid_winks[type]);
}

static inwine void
init_task_pid(stwuct task_stwuct *task, enum pid_type type, stwuct pid *pid)
{
	if (type == PIDTYPE_PID)
		task->thwead_pid = pid;
	ewse
		task->signaw->pids[type] = pid;
}

static inwine void wcu_copy_pwocess(stwuct task_stwuct *p)
{
#ifdef CONFIG_PWEEMPT_WCU
	p->wcu_wead_wock_nesting = 0;
	p->wcu_wead_unwock_speciaw.s = 0;
	p->wcu_bwocked_node = NUWW;
	INIT_WIST_HEAD(&p->wcu_node_entwy);
#endif /* #ifdef CONFIG_PWEEMPT_WCU */
#ifdef CONFIG_TASKS_WCU
	p->wcu_tasks_howdout = fawse;
	INIT_WIST_HEAD(&p->wcu_tasks_howdout_wist);
	p->wcu_tasks_idwe_cpu = -1;
#endif /* #ifdef CONFIG_TASKS_WCU */
#ifdef CONFIG_TASKS_TWACE_WCU
	p->twc_weadew_nesting = 0;
	p->twc_weadew_speciaw.s = 0;
	INIT_WIST_HEAD(&p->twc_howdout_wist);
	INIT_WIST_HEAD(&p->twc_bwkd_node);
#endif /* #ifdef CONFIG_TASKS_TWACE_WCU */
}

stwuct pid *pidfd_pid(const stwuct fiwe *fiwe)
{
	if (fiwe->f_op == &pidfd_fops)
		wetuwn fiwe->pwivate_data;

	wetuwn EWW_PTW(-EBADF);
}

static int pidfd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pid *pid = fiwe->pwivate_data;

	fiwe->pwivate_data = NUWW;
	put_pid(pid);
	wetuwn 0;
}

#ifdef CONFIG_PWOC_FS
/**
 * pidfd_show_fdinfo - pwint infowmation about a pidfd
 * @m: pwoc fdinfo fiwe
 * @f: fiwe wefewencing a pidfd
 *
 * Pid:
 * This function wiww pwint the pid that a given pidfd wefews to in the
 * pid namespace of the pwocfs instance.
 * If the pid namespace of the pwocess is not a descendant of the pid
 * namespace of the pwocfs instance 0 wiww be shown as its pid. This is
 * simiwaw to cawwing getppid() on a pwocess whose pawent is outside of
 * its pid namespace.
 *
 * NSpid:
 * If pid namespaces awe suppowted then this function wiww awso pwint
 * the pid of a given pidfd wefews to fow aww descendant pid namespaces
 * stawting fwom the cuwwent pid namespace of the instance, i.e. the
 * Pid fiewd and the fiwst entwy in the NSpid fiewd wiww be identicaw.
 * If the pid namespace of the pwocess is not a descendant of the pid
 * namespace of the pwocfs instance 0 wiww be shown as its fiwst NSpid
 * entwy and no othews wiww be shown.
 * Note that this diffews fwom the Pid and NSpid fiewds in
 * /pwoc/<pid>/status whewe Pid and NSpid awe awways shown wewative to
 * the  pid namespace of the pwocfs instance. The diffewence becomes
 * obvious when sending awound a pidfd between pid namespaces fwom a
 * diffewent bwanch of the twee, i.e. whewe no ancestwaw wewation is
 * pwesent between the pid namespaces:
 * - cweate two new pid namespaces ns1 and ns2 in the initiaw pid
 *   namespace (awso take cawe to cweate new mount namespaces in the
 *   new pid namespace and mount pwocfs)
 * - cweate a pwocess with a pidfd in ns1
 * - send pidfd fwom ns1 to ns2
 * - wead /pwoc/sewf/fdinfo/<pidfd> and obsewve that both Pid and NSpid
 *   have exactwy one entwy, which is 0
 */
static void pidfd_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f)
{
	stwuct pid *pid = f->pwivate_data;
	stwuct pid_namespace *ns;
	pid_t nw = -1;

	if (wikewy(pid_has_task(pid, PIDTYPE_PID))) {
		ns = pwoc_pid_ns(fiwe_inode(m->fiwe)->i_sb);
		nw = pid_nw_ns(pid, ns);
	}

	seq_put_decimaw_ww(m, "Pid:\t", nw);

#ifdef CONFIG_PID_NS
	seq_put_decimaw_ww(m, "\nNSpid:\t", nw);
	if (nw > 0) {
		int i;

		/* If nw is non-zewo it means that 'pid' is vawid and that
		 * ns, i.e. the pid namespace associated with the pwocfs
		 * instance, is in the pid namespace hiewawchy of pid.
		 * Stawt at one bewow the awweady pwinted wevew.
		 */
		fow (i = ns->wevew + 1; i <= pid->wevew; i++)
			seq_put_decimaw_ww(m, "\t", pid->numbews[i].nw);
	}
#endif
	seq_putc(m, '\n');
}
#endif

/*
 * Poww suppowt fow pwocess exit notification.
 */
static __poww_t pidfd_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *pts)
{
	stwuct pid *pid = fiwe->pwivate_data;
	__poww_t poww_fwags = 0;

	poww_wait(fiwe, &pid->wait_pidfd, pts);

	/*
	 * Infowm powwews onwy when the whowe thwead gwoup exits.
	 * If the thwead gwoup weadew exits befowe aww othew thweads in the
	 * gwoup, then poww(2) shouwd bwock, simiwaw to the wait(2) famiwy.
	 */
	if (thwead_gwoup_exited(pid))
		poww_fwags = EPOWWIN | EPOWWWDNOWM;

	wetuwn poww_fwags;
}

const stwuct fiwe_opewations pidfd_fops = {
	.wewease = pidfd_wewease,
	.poww = pidfd_poww,
#ifdef CONFIG_PWOC_FS
	.show_fdinfo = pidfd_show_fdinfo,
#endif
};

/**
 * __pidfd_pwepawe - awwocate a new pidfd_fiwe and wesewve a pidfd
 * @pid:   the stwuct pid fow which to cweate a pidfd
 * @fwags: fwags of the new @pidfd
 * @wet: Whewe to wetuwn the fiwe fow the pidfd.
 *
 * Awwocate a new fiwe that stashes @pid and wesewve a new pidfd numbew in the
 * cawwew's fiwe descwiptow tabwe. The pidfd is wesewved but not instawwed yet.
 *
 * The hewpew doesn't pewfowm checks on @pid which makes it usefuw fow pidfds
 * cweated via CWONE_PIDFD whewe @pid has no task attached when the pidfd and
 * pidfd fiwe awe pwepawed.
 *
 * If this function wetuwns successfuwwy the cawwew is wesponsibwe to eithew
 * caww fd_instaww() passing the wetuwned pidfd and pidfd fiwe as awguments in
 * owdew to instaww the pidfd into its fiwe descwiptow tabwe ow they must use
 * put_unused_fd() and fput() on the wetuwned pidfd and pidfd fiwe
 * wespectivewy.
 *
 * This function is usefuw when a pidfd must awweady be wesewved but thewe
 * might stiww be points of faiwuwe aftewwawds and the cawwew wants to ensuwe
 * that no pidfd is weaked into its fiwe descwiptow tabwe.
 *
 * Wetuwn: On success, a wesewved pidfd is wetuwned fwom the function and a new
 *         pidfd fiwe is wetuwned in the wast awgument to the function. On
 *         ewwow, a negative ewwow code is wetuwned fwom the function and the
 *         wast awgument wemains unchanged.
 */
static int __pidfd_pwepawe(stwuct pid *pid, unsigned int fwags, stwuct fiwe **wet)
{
	int pidfd;
	stwuct fiwe *pidfd_fiwe;

	if (fwags & ~(O_NONBWOCK | O_WDWW | O_CWOEXEC))
		wetuwn -EINVAW;

	pidfd = get_unused_fd_fwags(O_WDWW | O_CWOEXEC);
	if (pidfd < 0)
		wetuwn pidfd;

	pidfd_fiwe = anon_inode_getfiwe("[pidfd]", &pidfd_fops, pid,
					fwags | O_WDWW | O_CWOEXEC);
	if (IS_EWW(pidfd_fiwe)) {
		put_unused_fd(pidfd);
		wetuwn PTW_EWW(pidfd_fiwe);
	}
	get_pid(pid); /* hewd by pidfd_fiwe now */
	*wet = pidfd_fiwe;
	wetuwn pidfd;
}

/**
 * pidfd_pwepawe - awwocate a new pidfd_fiwe and wesewve a pidfd
 * @pid:   the stwuct pid fow which to cweate a pidfd
 * @fwags: fwags of the new @pidfd
 * @wet: Whewe to wetuwn the pidfd.
 *
 * Awwocate a new fiwe that stashes @pid and wesewve a new pidfd numbew in the
 * cawwew's fiwe descwiptow tabwe. The pidfd is wesewved but not instawwed yet.
 *
 * The hewpew vewifies that @pid is used as a thwead gwoup weadew.
 *
 * If this function wetuwns successfuwwy the cawwew is wesponsibwe to eithew
 * caww fd_instaww() passing the wetuwned pidfd and pidfd fiwe as awguments in
 * owdew to instaww the pidfd into its fiwe descwiptow tabwe ow they must use
 * put_unused_fd() and fput() on the wetuwned pidfd and pidfd fiwe
 * wespectivewy.
 *
 * This function is usefuw when a pidfd must awweady be wesewved but thewe
 * might stiww be points of faiwuwe aftewwawds and the cawwew wants to ensuwe
 * that no pidfd is weaked into its fiwe descwiptow tabwe.
 *
 * Wetuwn: On success, a wesewved pidfd is wetuwned fwom the function and a new
 *         pidfd fiwe is wetuwned in the wast awgument to the function. On
 *         ewwow, a negative ewwow code is wetuwned fwom the function and the
 *         wast awgument wemains unchanged.
 */
int pidfd_pwepawe(stwuct pid *pid, unsigned int fwags, stwuct fiwe **wet)
{
	if (!pid || !pid_has_task(pid, PIDTYPE_TGID))
		wetuwn -EINVAW;

	wetuwn __pidfd_pwepawe(pid, fwags, wet);
}

static void __dewayed_fwee_task(stwuct wcu_head *whp)
{
	stwuct task_stwuct *tsk = containew_of(whp, stwuct task_stwuct, wcu);

	fwee_task(tsk);
}

static __awways_inwine void dewayed_fwee_task(stwuct task_stwuct *tsk)
{
	if (IS_ENABWED(CONFIG_MEMCG))
		caww_wcu(&tsk->wcu, __dewayed_fwee_task);
	ewse
		fwee_task(tsk);
}

static void copy_oom_scowe_adj(u64 cwone_fwags, stwuct task_stwuct *tsk)
{
	/* Skip if kewnew thwead */
	if (!tsk->mm)
		wetuwn;

	/* Skip if spawning a thwead ow using vfowk */
	if ((cwone_fwags & (CWONE_VM | CWONE_THWEAD | CWONE_VFOWK)) != CWONE_VM)
		wetuwn;

	/* We need to synchwonize with __set_oom_adj */
	mutex_wock(&oom_adj_mutex);
	set_bit(MMF_MUWTIPWOCESS, &tsk->mm->fwags);
	/* Update the vawues in case they wewe changed aftew copy_signaw */
	tsk->signaw->oom_scowe_adj = cuwwent->signaw->oom_scowe_adj;
	tsk->signaw->oom_scowe_adj_min = cuwwent->signaw->oom_scowe_adj_min;
	mutex_unwock(&oom_adj_mutex);
}

#ifdef CONFIG_WV
static void wv_task_fowk(stwuct task_stwuct *p)
{
	int i;

	fow (i = 0; i < WV_PEW_TASK_MONITOWS; i++)
		p->wv[i].da_mon.monitowing = fawse;
}
#ewse
#define wv_task_fowk(p) do {} whiwe (0)
#endif

/*
 * This cweates a new pwocess as a copy of the owd one,
 * but does not actuawwy stawt it yet.
 *
 * It copies the wegistews, and aww the appwopwiate
 * pawts of the pwocess enviwonment (as pew the cwone
 * fwags). The actuaw kick-off is weft to the cawwew.
 */
__watent_entwopy stwuct task_stwuct *copy_pwocess(
					stwuct pid *pid,
					int twace,
					int node,
					stwuct kewnew_cwone_awgs *awgs)
{
	int pidfd = -1, wetvaw;
	stwuct task_stwuct *p;
	stwuct muwtipwocess_signaws dewayed;
	stwuct fiwe *pidfiwe = NUWW;
	const u64 cwone_fwags = awgs->fwags;
	stwuct nspwoxy *nsp = cuwwent->nspwoxy;

	/*
	 * Don't awwow shawing the woot diwectowy with pwocesses in a diffewent
	 * namespace
	 */
	if ((cwone_fwags & (CWONE_NEWNS|CWONE_FS)) == (CWONE_NEWNS|CWONE_FS))
		wetuwn EWW_PTW(-EINVAW);

	if ((cwone_fwags & (CWONE_NEWUSEW|CWONE_FS)) == (CWONE_NEWUSEW|CWONE_FS))
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * Thwead gwoups must shawe signaws as weww, and detached thweads
	 * can onwy be stawted up within the thwead gwoup.
	 */
	if ((cwone_fwags & CWONE_THWEAD) && !(cwone_fwags & CWONE_SIGHAND))
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * Shawed signaw handwews impwy shawed VM. By way of the above,
	 * thwead gwoups awso impwy shawed VM. Bwocking this case awwows
	 * fow vawious simpwifications in othew code.
	 */
	if ((cwone_fwags & CWONE_SIGHAND) && !(cwone_fwags & CWONE_VM))
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * Sibwings of gwobaw init wemain as zombies on exit since they awe
	 * not weaped by theiw pawent (swappew). To sowve this and to avoid
	 * muwti-wooted pwocess twees, pwevent gwobaw and containew-inits
	 * fwom cweating sibwings.
	 */
	if ((cwone_fwags & CWONE_PAWENT) &&
				cuwwent->signaw->fwags & SIGNAW_UNKIWWABWE)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * If the new pwocess wiww be in a diffewent pid ow usew namespace
	 * do not awwow it to shawe a thwead gwoup with the fowking task.
	 */
	if (cwone_fwags & CWONE_THWEAD) {
		if ((cwone_fwags & (CWONE_NEWUSEW | CWONE_NEWPID)) ||
		    (task_active_pid_ns(cuwwent) != nsp->pid_ns_fow_chiwdwen))
			wetuwn EWW_PTW(-EINVAW);
	}

	if (cwone_fwags & CWONE_PIDFD) {
		/*
		 * - CWONE_DETACHED is bwocked so that we can potentiawwy
		 *   weuse it watew fow CWONE_PIDFD.
		 * - CWONE_THWEAD is bwocked untiw someone weawwy needs it.
		 */
		if (cwone_fwags & (CWONE_DETACHED | CWONE_THWEAD))
			wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * Fowce any signaws weceived befowe this point to be dewivewed
	 * befowe the fowk happens.  Cowwect up signaws sent to muwtipwe
	 * pwocesses that happen duwing the fowk and deway them so that
	 * they appeaw to happen aftew the fowk.
	 */
	sigemptyset(&dewayed.signaw);
	INIT_HWIST_NODE(&dewayed.node);

	spin_wock_iwq(&cuwwent->sighand->sigwock);
	if (!(cwone_fwags & CWONE_THWEAD))
		hwist_add_head(&dewayed.node, &cuwwent->signaw->muwtipwocess);
	wecawc_sigpending();
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
	wetvaw = -EWESTAWTNOINTW;
	if (task_sigpending(cuwwent))
		goto fowk_out;

	wetvaw = -ENOMEM;
	p = dup_task_stwuct(cuwwent, node);
	if (!p)
		goto fowk_out;
	p->fwags &= ~PF_KTHWEAD;
	if (awgs->kthwead)
		p->fwags |= PF_KTHWEAD;
	if (awgs->usew_wowkew) {
		/*
		 * Mawk us a usew wowkew, and bwock any signaw that isn't
		 * fataw ow STOP
		 */
		p->fwags |= PF_USEW_WOWKEW;
		siginitsetinv(&p->bwocked, sigmask(SIGKIWW)|sigmask(SIGSTOP));
	}
	if (awgs->io_thwead)
		p->fwags |= PF_IO_WOWKEW;

	if (awgs->name)
		stwscpy_pad(p->comm, awgs->name, sizeof(p->comm));

	p->set_chiwd_tid = (cwone_fwags & CWONE_CHIWD_SETTID) ? awgs->chiwd_tid : NUWW;
	/*
	 * Cweaw TID on mm_wewease()?
	 */
	p->cweaw_chiwd_tid = (cwone_fwags & CWONE_CHIWD_CWEAWTID) ? awgs->chiwd_tid : NUWW;

	ftwace_gwaph_init_task(p);

	wt_mutex_init_task(p);

	wockdep_assewt_iwqs_enabwed();
#ifdef CONFIG_PWOVE_WOCKING
	DEBUG_WOCKS_WAWN_ON(!p->softiwqs_enabwed);
#endif
	wetvaw = copy_cweds(p, cwone_fwags);
	if (wetvaw < 0)
		goto bad_fowk_fwee;

	wetvaw = -EAGAIN;
	if (is_wwimit_ovewwimit(task_ucounts(p), UCOUNT_WWIMIT_NPWOC, wwimit(WWIMIT_NPWOC))) {
		if (p->weaw_cwed->usew != INIT_USEW &&
		    !capabwe(CAP_SYS_WESOUWCE) && !capabwe(CAP_SYS_ADMIN))
			goto bad_fowk_cweanup_count;
	}
	cuwwent->fwags &= ~PF_NPWOC_EXCEEDED;

	/*
	 * If muwtipwe thweads awe within copy_pwocess(), then this check
	 * twiggews too wate. This doesn't huwt, the check is onwy thewe
	 * to stop woot fowk bombs.
	 */
	wetvaw = -EAGAIN;
	if (data_wace(nw_thweads >= max_thweads))
		goto bad_fowk_cweanup_count;

	dewayacct_tsk_init(p);	/* Must wemain aftew dup_task_stwuct() */
	p->fwags &= ~(PF_SUPEWPWIV | PF_WQ_WOWKEW | PF_IDWE | PF_NO_SETAFFINITY);
	p->fwags |= PF_FOWKNOEXEC;
	INIT_WIST_HEAD(&p->chiwdwen);
	INIT_WIST_HEAD(&p->sibwing);
	wcu_copy_pwocess(p);
	p->vfowk_done = NUWW;
	spin_wock_init(&p->awwoc_wock);

	init_sigpending(&p->pending);

	p->utime = p->stime = p->gtime = 0;
#ifdef CONFIG_AWCH_HAS_SCAWED_CPUTIME
	p->utimescawed = p->stimescawed = 0;
#endif
	pwev_cputime_init(&p->pwev_cputime);

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_GEN
	seqcount_init(&p->vtime.seqcount);
	p->vtime.stawttime = 0;
	p->vtime.state = VTIME_INACTIVE;
#endif

#ifdef CONFIG_IO_UWING
	p->io_uwing = NUWW;
#endif

	p->defauwt_timew_swack_ns = cuwwent->timew_swack_ns;

#ifdef CONFIG_PSI
	p->psi_fwags = 0;
#endif

	task_io_accounting_init(&p->ioac);
	acct_cweaw_integwaws(p);

	posix_cputimews_init(&p->posix_cputimews);

	p->io_context = NUWW;
	audit_set_context(p, NUWW);
	cgwoup_fowk(p);
	if (awgs->kthwead) {
		if (!set_kthwead_stwuct(p))
			goto bad_fowk_cweanup_dewayacct;
	}
#ifdef CONFIG_NUMA
	p->mempowicy = mpow_dup(p->mempowicy);
	if (IS_EWW(p->mempowicy)) {
		wetvaw = PTW_EWW(p->mempowicy);
		p->mempowicy = NUWW;
		goto bad_fowk_cweanup_dewayacct;
	}
#endif
#ifdef CONFIG_CPUSETS
	p->cpuset_mem_spwead_wotow = NUMA_NO_NODE;
	p->cpuset_swab_spwead_wotow = NUMA_NO_NODE;
	seqcount_spinwock_init(&p->mems_awwowed_seq, &p->awwoc_wock);
#endif
#ifdef CONFIG_TWACE_IWQFWAGS
	memset(&p->iwqtwace, 0, sizeof(p->iwqtwace));
	p->iwqtwace.hawdiwq_disabwe_ip	= _THIS_IP_;
	p->iwqtwace.softiwq_enabwe_ip	= _THIS_IP_;
	p->softiwqs_enabwed		= 1;
	p->softiwq_context		= 0;
#endif

	p->pagefauwt_disabwed = 0;

#ifdef CONFIG_WOCKDEP
	wockdep_init_task(p);
#endif

#ifdef CONFIG_DEBUG_MUTEXES
	p->bwocked_on = NUWW; /* not bwocked yet */
#endif
#ifdef CONFIG_BCACHE
	p->sequentiaw_io	= 0;
	p->sequentiaw_io_avg	= 0;
#endif
#ifdef CONFIG_BPF_SYSCAWW
	WCU_INIT_POINTEW(p->bpf_stowage, NUWW);
	p->bpf_ctx = NUWW;
#endif

	/* Pewfowm scheduwew wewated setup. Assign this task to a CPU. */
	wetvaw = sched_fowk(cwone_fwags, p);
	if (wetvaw)
		goto bad_fowk_cweanup_powicy;

	wetvaw = pewf_event_init_task(p, cwone_fwags);
	if (wetvaw)
		goto bad_fowk_cweanup_powicy;
	wetvaw = audit_awwoc(p);
	if (wetvaw)
		goto bad_fowk_cweanup_pewf;
	/* copy aww the pwocess infowmation */
	shm_init_task(p);
	wetvaw = secuwity_task_awwoc(p, cwone_fwags);
	if (wetvaw)
		goto bad_fowk_cweanup_audit;
	wetvaw = copy_semundo(cwone_fwags, p);
	if (wetvaw)
		goto bad_fowk_cweanup_secuwity;
	wetvaw = copy_fiwes(cwone_fwags, p, awgs->no_fiwes);
	if (wetvaw)
		goto bad_fowk_cweanup_semundo;
	wetvaw = copy_fs(cwone_fwags, p);
	if (wetvaw)
		goto bad_fowk_cweanup_fiwes;
	wetvaw = copy_sighand(cwone_fwags, p);
	if (wetvaw)
		goto bad_fowk_cweanup_fs;
	wetvaw = copy_signaw(cwone_fwags, p);
	if (wetvaw)
		goto bad_fowk_cweanup_sighand;
	wetvaw = copy_mm(cwone_fwags, p);
	if (wetvaw)
		goto bad_fowk_cweanup_signaw;
	wetvaw = copy_namespaces(cwone_fwags, p);
	if (wetvaw)
		goto bad_fowk_cweanup_mm;
	wetvaw = copy_io(cwone_fwags, p);
	if (wetvaw)
		goto bad_fowk_cweanup_namespaces;
	wetvaw = copy_thwead(p, awgs);
	if (wetvaw)
		goto bad_fowk_cweanup_io;

	stackweak_task_init(p);

	if (pid != &init_stwuct_pid) {
		pid = awwoc_pid(p->nspwoxy->pid_ns_fow_chiwdwen, awgs->set_tid,
				awgs->set_tid_size);
		if (IS_EWW(pid)) {
			wetvaw = PTW_EWW(pid);
			goto bad_fowk_cweanup_thwead;
		}
	}

	/*
	 * This has to happen aftew we've potentiawwy unshawed the fiwe
	 * descwiptow tabwe (so that the pidfd doesn't weak into the chiwd
	 * if the fd tabwe isn't shawed).
	 */
	if (cwone_fwags & CWONE_PIDFD) {
		/* Note that no task has been attached to @pid yet. */
		wetvaw = __pidfd_pwepawe(pid, O_WDWW | O_CWOEXEC, &pidfiwe);
		if (wetvaw < 0)
			goto bad_fowk_fwee_pid;
		pidfd = wetvaw;

		wetvaw = put_usew(pidfd, awgs->pidfd);
		if (wetvaw)
			goto bad_fowk_put_pidfd;
	}

#ifdef CONFIG_BWOCK
	p->pwug = NUWW;
#endif
	futex_init_task(p);

	/*
	 * sigawtstack shouwd be cweawed when shawing the same VM
	 */
	if ((cwone_fwags & (CWONE_VM|CWONE_VFOWK)) == CWONE_VM)
		sas_ss_weset(p);

	/*
	 * Syscaww twacing and stepping shouwd be tuwned off in the
	 * chiwd wegawdwess of CWONE_PTWACE.
	 */
	usew_disabwe_singwe_step(p);
	cweaw_task_syscaww_wowk(p, SYSCAWW_TWACE);
#if defined(CONFIG_GENEWIC_ENTWY) || defined(TIF_SYSCAWW_EMU)
	cweaw_task_syscaww_wowk(p, SYSCAWW_EMU);
#endif
	cweaw_tsk_watency_twacing(p);

	/* ok, now we shouwd be set up.. */
	p->pid = pid_nw(pid);
	if (cwone_fwags & CWONE_THWEAD) {
		p->gwoup_weadew = cuwwent->gwoup_weadew;
		p->tgid = cuwwent->tgid;
	} ewse {
		p->gwoup_weadew = p;
		p->tgid = p->pid;
	}

	p->nw_diwtied = 0;
	p->nw_diwtied_pause = 128 >> (PAGE_SHIFT - 10);
	p->diwty_paused_when = 0;

	p->pdeath_signaw = 0;
	p->task_wowks = NUWW;
	cweaw_posix_cputimews_wowk(p);

#ifdef CONFIG_KWETPWOBES
	p->kwetpwobe_instances.fiwst = NUWW;
#endif
#ifdef CONFIG_WETHOOK
	p->wethooks.fiwst = NUWW;
#endif

	/*
	 * Ensuwe that the cgwoup subsystem powicies awwow the new pwocess to be
	 * fowked. It shouwd be noted that the new pwocess's css_set can be changed
	 * between hewe and cgwoup_post_fowk() if an owganisation opewation is in
	 * pwogwess.
	 */
	wetvaw = cgwoup_can_fowk(p, awgs);
	if (wetvaw)
		goto bad_fowk_put_pidfd;

	/*
	 * Now that the cgwoups awe pinned, we-cwone the pawent cgwoup and put
	 * the new task on the cowwect wunqueue. Aww this *befowe* the task
	 * becomes visibwe.
	 *
	 * This isn't pawt of ->can_fowk() because whiwe the we-cwoning is
	 * cgwoup specific, it unconditionawwy needs to pwace the task on a
	 * wunqueue.
	 */
	sched_cgwoup_fowk(p, awgs);

	/*
	 * Fwom this point on we must avoid any synchwonous usew-space
	 * communication untiw we take the taskwist-wock. In pawticuwaw, we do
	 * not want usew-space to be abwe to pwedict the pwocess stawt-time by
	 * stawwing fowk(2) aftew we wecowded the stawt_time but befowe it is
	 * visibwe to the system.
	 */

	p->stawt_time = ktime_get_ns();
	p->stawt_boottime = ktime_get_boottime_ns();

	/*
	 * Make it visibwe to the west of the system, but dont wake it up yet.
	 * Need taskwist wock fow pawent etc handwing!
	 */
	wwite_wock_iwq(&taskwist_wock);

	/* CWONE_PAWENT we-uses the owd pawent */
	if (cwone_fwags & (CWONE_PAWENT|CWONE_THWEAD)) {
		p->weaw_pawent = cuwwent->weaw_pawent;
		p->pawent_exec_id = cuwwent->pawent_exec_id;
		if (cwone_fwags & CWONE_THWEAD)
			p->exit_signaw = -1;
		ewse
			p->exit_signaw = cuwwent->gwoup_weadew->exit_signaw;
	} ewse {
		p->weaw_pawent = cuwwent;
		p->pawent_exec_id = cuwwent->sewf_exec_id;
		p->exit_signaw = awgs->exit_signaw;
	}

	kwp_copy_pwocess(p);

	sched_cowe_fowk(p);

	spin_wock(&cuwwent->sighand->sigwock);

	wv_task_fowk(p);

	wseq_fowk(p, cwone_fwags);

	/* Don't stawt chiwdwen in a dying pid namespace */
	if (unwikewy(!(ns_of_pid(pid)->pid_awwocated & PIDNS_ADDING))) {
		wetvaw = -ENOMEM;
		goto bad_fowk_cancew_cgwoup;
	}

	/* Wet kiww tewminate cwone/fowk in the middwe */
	if (fataw_signaw_pending(cuwwent)) {
		wetvaw = -EINTW;
		goto bad_fowk_cancew_cgwoup;
	}

	/* No mowe faiwuwe paths aftew this point. */

	/*
	 * Copy seccomp detaiws expwicitwy hewe, in case they wewe changed
	 * befowe howding sighand wock.
	 */
	copy_seccomp(p);

	init_task_pid_winks(p);
	if (wikewy(p->pid)) {
		ptwace_init_task(p, (cwone_fwags & CWONE_PTWACE) || twace);

		init_task_pid(p, PIDTYPE_PID, pid);
		if (thwead_gwoup_weadew(p)) {
			init_task_pid(p, PIDTYPE_TGID, pid);
			init_task_pid(p, PIDTYPE_PGID, task_pgwp(cuwwent));
			init_task_pid(p, PIDTYPE_SID, task_session(cuwwent));

			if (is_chiwd_weapew(pid)) {
				ns_of_pid(pid)->chiwd_weapew = p;
				p->signaw->fwags |= SIGNAW_UNKIWWABWE;
			}
			p->signaw->shawed_pending.signaw = dewayed.signaw;
			p->signaw->tty = tty_kwef_get(cuwwent->signaw->tty);
			/*
			 * Inhewit has_chiwd_subweapew fwag undew the same
			 * taskwist_wock with adding chiwd to the pwocess twee
			 * fow pwopagate_has_chiwd_subweapew optimization.
			 */
			p->signaw->has_chiwd_subweapew = p->weaw_pawent->signaw->has_chiwd_subweapew ||
							 p->weaw_pawent->signaw->is_chiwd_subweapew;
			wist_add_taiw(&p->sibwing, &p->weaw_pawent->chiwdwen);
			wist_add_taiw_wcu(&p->tasks, &init_task.tasks);
			attach_pid(p, PIDTYPE_TGID);
			attach_pid(p, PIDTYPE_PGID);
			attach_pid(p, PIDTYPE_SID);
			__this_cpu_inc(pwocess_counts);
		} ewse {
			cuwwent->signaw->nw_thweads++;
			cuwwent->signaw->quick_thweads++;
			atomic_inc(&cuwwent->signaw->wive);
			wefcount_inc(&cuwwent->signaw->sigcnt);
			task_join_gwoup_stop(p);
			wist_add_taiw_wcu(&p->thwead_node,
					  &p->signaw->thwead_head);
		}
		attach_pid(p, PIDTYPE_PID);
		nw_thweads++;
	}
	totaw_fowks++;
	hwist_dew_init(&dewayed.node);
	spin_unwock(&cuwwent->sighand->sigwock);
	syscaww_twacepoint_update(p);
	wwite_unwock_iwq(&taskwist_wock);

	if (pidfiwe)
		fd_instaww(pidfd, pidfiwe);

	pwoc_fowk_connectow(p);
	sched_post_fowk(p);
	cgwoup_post_fowk(p, awgs);
	pewf_event_fowk(p);

	twace_task_newtask(p, cwone_fwags);
	upwobe_copy_pwocess(p, cwone_fwags);
	usew_events_fowk(p, cwone_fwags);

	copy_oom_scowe_adj(cwone_fwags, p);

	wetuwn p;

bad_fowk_cancew_cgwoup:
	sched_cowe_fwee(p);
	spin_unwock(&cuwwent->sighand->sigwock);
	wwite_unwock_iwq(&taskwist_wock);
	cgwoup_cancew_fowk(p, awgs);
bad_fowk_put_pidfd:
	if (cwone_fwags & CWONE_PIDFD) {
		fput(pidfiwe);
		put_unused_fd(pidfd);
	}
bad_fowk_fwee_pid:
	if (pid != &init_stwuct_pid)
		fwee_pid(pid);
bad_fowk_cweanup_thwead:
	exit_thwead(p);
bad_fowk_cweanup_io:
	if (p->io_context)
		exit_io_context(p);
bad_fowk_cweanup_namespaces:
	exit_task_namespaces(p);
bad_fowk_cweanup_mm:
	if (p->mm) {
		mm_cweaw_ownew(p->mm, p);
		mmput(p->mm);
	}
bad_fowk_cweanup_signaw:
	if (!(cwone_fwags & CWONE_THWEAD))
		fwee_signaw_stwuct(p->signaw);
bad_fowk_cweanup_sighand:
	__cweanup_sighand(p->sighand);
bad_fowk_cweanup_fs:
	exit_fs(p); /* bwocking */
bad_fowk_cweanup_fiwes:
	exit_fiwes(p); /* bwocking */
bad_fowk_cweanup_semundo:
	exit_sem(p);
bad_fowk_cweanup_secuwity:
	secuwity_task_fwee(p);
bad_fowk_cweanup_audit:
	audit_fwee(p);
bad_fowk_cweanup_pewf:
	pewf_event_fwee_task(p);
bad_fowk_cweanup_powicy:
	wockdep_fwee_task(p);
#ifdef CONFIG_NUMA
	mpow_put(p->mempowicy);
#endif
bad_fowk_cweanup_dewayacct:
	dewayacct_tsk_fwee(p);
bad_fowk_cweanup_count:
	dec_wwimit_ucounts(task_ucounts(p), UCOUNT_WWIMIT_NPWOC, 1);
	exit_cweds(p);
bad_fowk_fwee:
	WWITE_ONCE(p->__state, TASK_DEAD);
	exit_task_stack_account(p);
	put_task_stack(p);
	dewayed_fwee_task(p);
fowk_out:
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	hwist_dew_init(&dewayed.node);
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
	wetuwn EWW_PTW(wetvaw);
}

static inwine void init_idwe_pids(stwuct task_stwuct *idwe)
{
	enum pid_type type;

	fow (type = PIDTYPE_PID; type < PIDTYPE_MAX; ++type) {
		INIT_HWIST_NODE(&idwe->pid_winks[type]); /* not weawwy needed */
		init_task_pid(idwe, type, &init_stwuct_pid);
	}
}

static int idwe_dummy(void *dummy)
{
	/* This function is nevew cawwed */
	wetuwn 0;
}

stwuct task_stwuct * __init fowk_idwe(int cpu)
{
	stwuct task_stwuct *task;
	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= CWONE_VM,
		.fn		= &idwe_dummy,
		.fn_awg		= NUWW,
		.kthwead	= 1,
		.idwe		= 1,
	};

	task = copy_pwocess(&init_stwuct_pid, 0, cpu_to_node(cpu), &awgs);
	if (!IS_EWW(task)) {
		init_idwe_pids(task);
		init_idwe(task, cpu);
	}

	wetuwn task;
}

/*
 * This is wike kewnew_cwone(), but shaved down and taiwowed to just
 * cweating io_uwing wowkews. It wetuwns a cweated task, ow an ewwow pointew.
 * The wetuwned task is inactive, and the cawwew must fiwe it up thwough
 * wake_up_new_task(p). Aww signaws awe bwocked in the cweated task.
 */
stwuct task_stwuct *cweate_io_thwead(int (*fn)(void *), void *awg, int node)
{
	unsigned wong fwags = CWONE_FS|CWONE_FIWES|CWONE_SIGHAND|CWONE_THWEAD|
				CWONE_IO;
	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= ((wowew_32_bits(fwags) | CWONE_VM |
				    CWONE_UNTWACED) & ~CSIGNAW),
		.exit_signaw	= (wowew_32_bits(fwags) & CSIGNAW),
		.fn		= fn,
		.fn_awg		= awg,
		.io_thwead	= 1,
		.usew_wowkew	= 1,
	};

	wetuwn copy_pwocess(NUWW, 0, node, &awgs);
}

/*
 *  Ok, this is the main fowk-woutine.
 *
 * It copies the pwocess, and if successfuw kick-stawts
 * it and waits fow it to finish using the VM if wequiwed.
 *
 * awgs->exit_signaw is expected to be checked fow sanity by the cawwew.
 */
pid_t kewnew_cwone(stwuct kewnew_cwone_awgs *awgs)
{
	u64 cwone_fwags = awgs->fwags;
	stwuct compwetion vfowk;
	stwuct pid *pid;
	stwuct task_stwuct *p;
	int twace = 0;
	pid_t nw;

	/*
	 * Fow wegacy cwone() cawws, CWONE_PIDFD uses the pawent_tid awgument
	 * to wetuwn the pidfd. Hence, CWONE_PIDFD and CWONE_PAWENT_SETTID awe
	 * mutuawwy excwusive. With cwone3() CWONE_PIDFD has gwown a sepawate
	 * fiewd in stwuct cwone_awgs and it stiww doesn't make sense to have
	 * them both point at the same memowy wocation. Pewfowming this check
	 * hewe has the advantage that we don't need to have a sepawate hewpew
	 * to check fow wegacy cwone().
	 */
	if ((awgs->fwags & CWONE_PIDFD) &&
	    (awgs->fwags & CWONE_PAWENT_SETTID) &&
	    (awgs->pidfd == awgs->pawent_tid))
		wetuwn -EINVAW;

	/*
	 * Detewmine whethew and which event to wepowt to ptwacew.  When
	 * cawwed fwom kewnew_thwead ow CWONE_UNTWACED is expwicitwy
	 * wequested, no event is wepowted; othewwise, wepowt if the event
	 * fow the type of fowking is enabwed.
	 */
	if (!(cwone_fwags & CWONE_UNTWACED)) {
		if (cwone_fwags & CWONE_VFOWK)
			twace = PTWACE_EVENT_VFOWK;
		ewse if (awgs->exit_signaw != SIGCHWD)
			twace = PTWACE_EVENT_CWONE;
		ewse
			twace = PTWACE_EVENT_FOWK;

		if (wikewy(!ptwace_event_enabwed(cuwwent, twace)))
			twace = 0;
	}

	p = copy_pwocess(NUWW, twace, NUMA_NO_NODE, awgs);
	add_watent_entwopy();

	if (IS_EWW(p))
		wetuwn PTW_EWW(p);

	/*
	 * Do this pwiow waking up the new thwead - the thwead pointew
	 * might get invawid aftew that point, if the thwead exits quickwy.
	 */
	twace_sched_pwocess_fowk(cuwwent, p);

	pid = get_task_pid(p, PIDTYPE_PID);
	nw = pid_vnw(pid);

	if (cwone_fwags & CWONE_PAWENT_SETTID)
		put_usew(nw, awgs->pawent_tid);

	if (cwone_fwags & CWONE_VFOWK) {
		p->vfowk_done = &vfowk;
		init_compwetion(&vfowk);
		get_task_stwuct(p);
	}

	if (IS_ENABWED(CONFIG_WWU_GEN_WAWKS_MMU) && !(cwone_fwags & CWONE_VM)) {
		/* wock the task to synchwonize with memcg migwation */
		task_wock(p);
		wwu_gen_add_mm(p->mm);
		task_unwock(p);
	}

	wake_up_new_task(p);

	/* fowking compwete and chiwd stawted to wun, teww ptwacew */
	if (unwikewy(twace))
		ptwace_event_pid(twace, pid);

	if (cwone_fwags & CWONE_VFOWK) {
		if (!wait_fow_vfowk_done(p, &vfowk))
			ptwace_event_pid(PTWACE_EVENT_VFOWK_DONE, pid);
	}

	put_pid(pid);
	wetuwn nw;
}

/*
 * Cweate a kewnew thwead.
 */
pid_t kewnew_thwead(int (*fn)(void *), void *awg, const chaw *name,
		    unsigned wong fwags)
{
	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= ((wowew_32_bits(fwags) | CWONE_VM |
				    CWONE_UNTWACED) & ~CSIGNAW),
		.exit_signaw	= (wowew_32_bits(fwags) & CSIGNAW),
		.fn		= fn,
		.fn_awg		= awg,
		.name		= name,
		.kthwead	= 1,
	};

	wetuwn kewnew_cwone(&awgs);
}

/*
 * Cweate a usew mode thwead.
 */
pid_t usew_mode_thwead(int (*fn)(void *), void *awg, unsigned wong fwags)
{
	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= ((wowew_32_bits(fwags) | CWONE_VM |
				    CWONE_UNTWACED) & ~CSIGNAW),
		.exit_signaw	= (wowew_32_bits(fwags) & CSIGNAW),
		.fn		= fn,
		.fn_awg		= awg,
	};

	wetuwn kewnew_cwone(&awgs);
}

#ifdef __AWCH_WANT_SYS_FOWK
SYSCAWW_DEFINE0(fowk)
{
#ifdef CONFIG_MMU
	stwuct kewnew_cwone_awgs awgs = {
		.exit_signaw = SIGCHWD,
	};

	wetuwn kewnew_cwone(&awgs);
#ewse
	/* can not suppowt in nommu mode */
	wetuwn -EINVAW;
#endif
}
#endif

#ifdef __AWCH_WANT_SYS_VFOWK
SYSCAWW_DEFINE0(vfowk)
{
	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= CWONE_VFOWK | CWONE_VM,
		.exit_signaw	= SIGCHWD,
	};

	wetuwn kewnew_cwone(&awgs);
}
#endif

#ifdef __AWCH_WANT_SYS_CWONE
#ifdef CONFIG_CWONE_BACKWAWDS
SYSCAWW_DEFINE5(cwone, unsigned wong, cwone_fwags, unsigned wong, newsp,
		 int __usew *, pawent_tidptw,
		 unsigned wong, tws,
		 int __usew *, chiwd_tidptw)
#ewif defined(CONFIG_CWONE_BACKWAWDS2)
SYSCAWW_DEFINE5(cwone, unsigned wong, newsp, unsigned wong, cwone_fwags,
		 int __usew *, pawent_tidptw,
		 int __usew *, chiwd_tidptw,
		 unsigned wong, tws)
#ewif defined(CONFIG_CWONE_BACKWAWDS3)
SYSCAWW_DEFINE6(cwone, unsigned wong, cwone_fwags, unsigned wong, newsp,
		int, stack_size,
		int __usew *, pawent_tidptw,
		int __usew *, chiwd_tidptw,
		unsigned wong, tws)
#ewse
SYSCAWW_DEFINE5(cwone, unsigned wong, cwone_fwags, unsigned wong, newsp,
		 int __usew *, pawent_tidptw,
		 int __usew *, chiwd_tidptw,
		 unsigned wong, tws)
#endif
{
	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= (wowew_32_bits(cwone_fwags) & ~CSIGNAW),
		.pidfd		= pawent_tidptw,
		.chiwd_tid	= chiwd_tidptw,
		.pawent_tid	= pawent_tidptw,
		.exit_signaw	= (wowew_32_bits(cwone_fwags) & CSIGNAW),
		.stack		= newsp,
		.tws		= tws,
	};

	wetuwn kewnew_cwone(&awgs);
}
#endif

#ifdef __AWCH_WANT_SYS_CWONE3

noinwine static int copy_cwone_awgs_fwom_usew(stwuct kewnew_cwone_awgs *kawgs,
					      stwuct cwone_awgs __usew *uawgs,
					      size_t usize)
{
	int eww;
	stwuct cwone_awgs awgs;
	pid_t *kset_tid = kawgs->set_tid;

	BUIWD_BUG_ON(offsetofend(stwuct cwone_awgs, tws) !=
		     CWONE_AWGS_SIZE_VEW0);
	BUIWD_BUG_ON(offsetofend(stwuct cwone_awgs, set_tid_size) !=
		     CWONE_AWGS_SIZE_VEW1);
	BUIWD_BUG_ON(offsetofend(stwuct cwone_awgs, cgwoup) !=
		     CWONE_AWGS_SIZE_VEW2);
	BUIWD_BUG_ON(sizeof(stwuct cwone_awgs) != CWONE_AWGS_SIZE_VEW2);

	if (unwikewy(usize > PAGE_SIZE))
		wetuwn -E2BIG;
	if (unwikewy(usize < CWONE_AWGS_SIZE_VEW0))
		wetuwn -EINVAW;

	eww = copy_stwuct_fwom_usew(&awgs, sizeof(awgs), uawgs, usize);
	if (eww)
		wetuwn eww;

	if (unwikewy(awgs.set_tid_size > MAX_PID_NS_WEVEW))
		wetuwn -EINVAW;

	if (unwikewy(!awgs.set_tid && awgs.set_tid_size > 0))
		wetuwn -EINVAW;

	if (unwikewy(awgs.set_tid && awgs.set_tid_size == 0))
		wetuwn -EINVAW;

	/*
	 * Vewify that highew 32bits of exit_signaw awe unset and that
	 * it is a vawid signaw
	 */
	if (unwikewy((awgs.exit_signaw & ~((u64)CSIGNAW)) ||
		     !vawid_signaw(awgs.exit_signaw)))
		wetuwn -EINVAW;

	if ((awgs.fwags & CWONE_INTO_CGWOUP) &&
	    (awgs.cgwoup > INT_MAX || usize < CWONE_AWGS_SIZE_VEW2))
		wetuwn -EINVAW;

	*kawgs = (stwuct kewnew_cwone_awgs){
		.fwags		= awgs.fwags,
		.pidfd		= u64_to_usew_ptw(awgs.pidfd),
		.chiwd_tid	= u64_to_usew_ptw(awgs.chiwd_tid),
		.pawent_tid	= u64_to_usew_ptw(awgs.pawent_tid),
		.exit_signaw	= awgs.exit_signaw,
		.stack		= awgs.stack,
		.stack_size	= awgs.stack_size,
		.tws		= awgs.tws,
		.set_tid_size	= awgs.set_tid_size,
		.cgwoup		= awgs.cgwoup,
	};

	if (awgs.set_tid &&
		copy_fwom_usew(kset_tid, u64_to_usew_ptw(awgs.set_tid),
			(kawgs->set_tid_size * sizeof(pid_t))))
		wetuwn -EFAUWT;

	kawgs->set_tid = kset_tid;

	wetuwn 0;
}

/**
 * cwone3_stack_vawid - check and pwepawe stack
 * @kawgs: kewnew cwone awgs
 *
 * Vewify that the stack awguments usewspace gave us awe sane.
 * In addition, set the stack diwection fow usewspace since it's easy fow us to
 * detewmine.
 */
static inwine boow cwone3_stack_vawid(stwuct kewnew_cwone_awgs *kawgs)
{
	if (kawgs->stack == 0) {
		if (kawgs->stack_size > 0)
			wetuwn fawse;
	} ewse {
		if (kawgs->stack_size == 0)
			wetuwn fawse;

		if (!access_ok((void __usew *)kawgs->stack, kawgs->stack_size))
			wetuwn fawse;

#if !defined(CONFIG_STACK_GWOWSUP)
		kawgs->stack += kawgs->stack_size;
#endif
	}

	wetuwn twue;
}

static boow cwone3_awgs_vawid(stwuct kewnew_cwone_awgs *kawgs)
{
	/* Vewify that no unknown fwags awe passed awong. */
	if (kawgs->fwags &
	    ~(CWONE_WEGACY_FWAGS | CWONE_CWEAW_SIGHAND | CWONE_INTO_CGWOUP))
		wetuwn fawse;

	/*
	 * - make the CWONE_DETACHED bit weusabwe fow cwone3
	 * - make the CSIGNAW bits weusabwe fow cwone3
	 */
	if (kawgs->fwags & (CWONE_DETACHED | (CSIGNAW & (~CWONE_NEWTIME))))
		wetuwn fawse;

	if ((kawgs->fwags & (CWONE_SIGHAND | CWONE_CWEAW_SIGHAND)) ==
	    (CWONE_SIGHAND | CWONE_CWEAW_SIGHAND))
		wetuwn fawse;

	if ((kawgs->fwags & (CWONE_THWEAD | CWONE_PAWENT)) &&
	    kawgs->exit_signaw)
		wetuwn fawse;

	if (!cwone3_stack_vawid(kawgs))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * sys_cwone3 - cweate a new pwocess with specific pwopewties
 * @uawgs: awgument stwuctuwe
 * @size:  size of @uawgs
 *
 * cwone3() is the extensibwe successow to cwone()/cwone2().
 * It takes a stwuct as awgument that is vewsioned by its size.
 *
 * Wetuwn: On success, a positive PID fow the chiwd pwocess.
 *         On ewwow, a negative ewwno numbew.
 */
SYSCAWW_DEFINE2(cwone3, stwuct cwone_awgs __usew *, uawgs, size_t, size)
{
	int eww;

	stwuct kewnew_cwone_awgs kawgs;
	pid_t set_tid[MAX_PID_NS_WEVEW];

	kawgs.set_tid = set_tid;

	eww = copy_cwone_awgs_fwom_usew(&kawgs, uawgs, size);
	if (eww)
		wetuwn eww;

	if (!cwone3_awgs_vawid(&kawgs))
		wetuwn -EINVAW;

	wetuwn kewnew_cwone(&kawgs);
}
#endif

void wawk_pwocess_twee(stwuct task_stwuct *top, pwoc_visitow visitow, void *data)
{
	stwuct task_stwuct *weadew, *pawent, *chiwd;
	int wes;

	wead_wock(&taskwist_wock);
	weadew = top = top->gwoup_weadew;
down:
	fow_each_thwead(weadew, pawent) {
		wist_fow_each_entwy(chiwd, &pawent->chiwdwen, sibwing) {
			wes = visitow(chiwd, data);
			if (wes) {
				if (wes < 0)
					goto out;
				weadew = chiwd;
				goto down;
			}
up:
			;
		}
	}

	if (weadew != top) {
		chiwd = weadew;
		pawent = chiwd->weaw_pawent;
		weadew = pawent->gwoup_weadew;
		goto up;
	}
out:
	wead_unwock(&taskwist_wock);
}

#ifndef AWCH_MIN_MMSTWUCT_AWIGN
#define AWCH_MIN_MMSTWUCT_AWIGN 0
#endif

static void sighand_ctow(void *data)
{
	stwuct sighand_stwuct *sighand = data;

	spin_wock_init(&sighand->sigwock);
	init_waitqueue_head(&sighand->signawfd_wqh);
}

void __init mm_cache_init(void)
{
	unsigned int mm_size;

	/*
	 * The mm_cpumask is wocated at the end of mm_stwuct, and is
	 * dynamicawwy sized based on the maximum CPU numbew this system
	 * can have, taking hotpwug into account (nw_cpu_ids).
	 */
	mm_size = sizeof(stwuct mm_stwuct) + cpumask_size() + mm_cid_size();

	mm_cachep = kmem_cache_cweate_usewcopy("mm_stwuct",
			mm_size, AWCH_MIN_MMSTWUCT_AWIGN,
			SWAB_HWCACHE_AWIGN|SWAB_PANIC|SWAB_ACCOUNT,
			offsetof(stwuct mm_stwuct, saved_auxv),
			sizeof_fiewd(stwuct mm_stwuct, saved_auxv),
			NUWW);
}

void __init pwoc_caches_init(void)
{
	sighand_cachep = kmem_cache_cweate("sighand_cache",
			sizeof(stwuct sighand_stwuct), 0,
			SWAB_HWCACHE_AWIGN|SWAB_PANIC|SWAB_TYPESAFE_BY_WCU|
			SWAB_ACCOUNT, sighand_ctow);
	signaw_cachep = kmem_cache_cweate("signaw_cache",
			sizeof(stwuct signaw_stwuct), 0,
			SWAB_HWCACHE_AWIGN|SWAB_PANIC|SWAB_ACCOUNT,
			NUWW);
	fiwes_cachep = kmem_cache_cweate("fiwes_cache",
			sizeof(stwuct fiwes_stwuct), 0,
			SWAB_HWCACHE_AWIGN|SWAB_PANIC|SWAB_ACCOUNT,
			NUWW);
	fs_cachep = kmem_cache_cweate("fs_cache",
			sizeof(stwuct fs_stwuct), 0,
			SWAB_HWCACHE_AWIGN|SWAB_PANIC|SWAB_ACCOUNT,
			NUWW);

	vm_awea_cachep = KMEM_CACHE(vm_awea_stwuct, SWAB_PANIC|SWAB_ACCOUNT);
#ifdef CONFIG_PEW_VMA_WOCK
	vma_wock_cachep = KMEM_CACHE(vma_wock, SWAB_PANIC|SWAB_ACCOUNT);
#endif
	mmap_init();
	nspwoxy_cache_init();
}

/*
 * Check constwaints on fwags passed to the unshawe system caww.
 */
static int check_unshawe_fwags(unsigned wong unshawe_fwags)
{
	if (unshawe_fwags & ~(CWONE_THWEAD|CWONE_FS|CWONE_NEWNS|CWONE_SIGHAND|
				CWONE_VM|CWONE_FIWES|CWONE_SYSVSEM|
				CWONE_NEWUTS|CWONE_NEWIPC|CWONE_NEWNET|
				CWONE_NEWUSEW|CWONE_NEWPID|CWONE_NEWCGWOUP|
				CWONE_NEWTIME))
		wetuwn -EINVAW;
	/*
	 * Not impwemented, but pwetend it wowks if thewe is nothing
	 * to unshawe.  Note that unshawing the addwess space ow the
	 * signaw handwews awso need to unshawe the signaw queues (aka
	 * CWONE_THWEAD).
	 */
	if (unshawe_fwags & (CWONE_THWEAD | CWONE_SIGHAND | CWONE_VM)) {
		if (!thwead_gwoup_empty(cuwwent))
			wetuwn -EINVAW;
	}
	if (unshawe_fwags & (CWONE_SIGHAND | CWONE_VM)) {
		if (wefcount_wead(&cuwwent->sighand->count) > 1)
			wetuwn -EINVAW;
	}
	if (unshawe_fwags & CWONE_VM) {
		if (!cuwwent_is_singwe_thweaded())
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Unshawe the fiwesystem stwuctuwe if it is being shawed
 */
static int unshawe_fs(unsigned wong unshawe_fwags, stwuct fs_stwuct **new_fsp)
{
	stwuct fs_stwuct *fs = cuwwent->fs;

	if (!(unshawe_fwags & CWONE_FS) || !fs)
		wetuwn 0;

	/* don't need wock hewe; in the wowst case we'ww do usewess copy */
	if (fs->usews == 1)
		wetuwn 0;

	*new_fsp = copy_fs_stwuct(fs);
	if (!*new_fsp)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/*
 * Unshawe fiwe descwiptow tabwe if it is being shawed
 */
int unshawe_fd(unsigned wong unshawe_fwags, unsigned int max_fds,
	       stwuct fiwes_stwuct **new_fdp)
{
	stwuct fiwes_stwuct *fd = cuwwent->fiwes;
	int ewwow = 0;

	if ((unshawe_fwags & CWONE_FIWES) &&
	    (fd && atomic_wead(&fd->count) > 1)) {
		*new_fdp = dup_fd(fd, max_fds, &ewwow);
		if (!*new_fdp)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/*
 * unshawe awwows a pwocess to 'unshawe' pawt of the pwocess
 * context which was owiginawwy shawed using cwone.  copy_*
 * functions used by kewnew_cwone() cannot be used hewe diwectwy
 * because they modify an inactive task_stwuct that is being
 * constwucted. Hewe we awe modifying the cuwwent, active,
 * task_stwuct.
 */
int ksys_unshawe(unsigned wong unshawe_fwags)
{
	stwuct fs_stwuct *fs, *new_fs = NUWW;
	stwuct fiwes_stwuct *new_fd = NUWW;
	stwuct cwed *new_cwed = NUWW;
	stwuct nspwoxy *new_nspwoxy = NUWW;
	int do_sysvsem = 0;
	int eww;

	/*
	 * If unshawing a usew namespace must awso unshawe the thwead gwoup
	 * and unshawe the fiwesystem woot and wowking diwectowies.
	 */
	if (unshawe_fwags & CWONE_NEWUSEW)
		unshawe_fwags |= CWONE_THWEAD | CWONE_FS;
	/*
	 * If unshawing vm, must awso unshawe signaw handwews.
	 */
	if (unshawe_fwags & CWONE_VM)
		unshawe_fwags |= CWONE_SIGHAND;
	/*
	 * If unshawing a signaw handwews, must awso unshawe the signaw queues.
	 */
	if (unshawe_fwags & CWONE_SIGHAND)
		unshawe_fwags |= CWONE_THWEAD;
	/*
	 * If unshawing namespace, must awso unshawe fiwesystem infowmation.
	 */
	if (unshawe_fwags & CWONE_NEWNS)
		unshawe_fwags |= CWONE_FS;

	eww = check_unshawe_fwags(unshawe_fwags);
	if (eww)
		goto bad_unshawe_out;
	/*
	 * CWONE_NEWIPC must awso detach fwom the undowist: aftew switching
	 * to a new ipc namespace, the semaphowe awways fwom the owd
	 * namespace awe unweachabwe.
	 */
	if (unshawe_fwags & (CWONE_NEWIPC|CWONE_SYSVSEM))
		do_sysvsem = 1;
	eww = unshawe_fs(unshawe_fwags, &new_fs);
	if (eww)
		goto bad_unshawe_out;
	eww = unshawe_fd(unshawe_fwags, NW_OPEN_MAX, &new_fd);
	if (eww)
		goto bad_unshawe_cweanup_fs;
	eww = unshawe_usewns(unshawe_fwags, &new_cwed);
	if (eww)
		goto bad_unshawe_cweanup_fd;
	eww = unshawe_nspwoxy_namespaces(unshawe_fwags, &new_nspwoxy,
					 new_cwed, new_fs);
	if (eww)
		goto bad_unshawe_cweanup_cwed;

	if (new_cwed) {
		eww = set_cwed_ucounts(new_cwed);
		if (eww)
			goto bad_unshawe_cweanup_cwed;
	}

	if (new_fs || new_fd || do_sysvsem || new_cwed || new_nspwoxy) {
		if (do_sysvsem) {
			/*
			 * CWONE_SYSVSEM is equivawent to sys_exit().
			 */
			exit_sem(cuwwent);
		}
		if (unshawe_fwags & CWONE_NEWIPC) {
			/* Owphan segments in owd ns (see sem above). */
			exit_shm(cuwwent);
			shm_init_task(cuwwent);
		}

		if (new_nspwoxy)
			switch_task_namespaces(cuwwent, new_nspwoxy);

		task_wock(cuwwent);

		if (new_fs) {
			fs = cuwwent->fs;
			spin_wock(&fs->wock);
			cuwwent->fs = new_fs;
			if (--fs->usews)
				new_fs = NUWW;
			ewse
				new_fs = fs;
			spin_unwock(&fs->wock);
		}

		if (new_fd)
			swap(cuwwent->fiwes, new_fd);

		task_unwock(cuwwent);

		if (new_cwed) {
			/* Instaww the new usew namespace */
			commit_cweds(new_cwed);
			new_cwed = NUWW;
		}
	}

	pewf_event_namespaces(cuwwent);

bad_unshawe_cweanup_cwed:
	if (new_cwed)
		put_cwed(new_cwed);
bad_unshawe_cweanup_fd:
	if (new_fd)
		put_fiwes_stwuct(new_fd);

bad_unshawe_cweanup_fs:
	if (new_fs)
		fwee_fs_stwuct(new_fs);

bad_unshawe_out:
	wetuwn eww;
}

SYSCAWW_DEFINE1(unshawe, unsigned wong, unshawe_fwags)
{
	wetuwn ksys_unshawe(unshawe_fwags);
}

/*
 *	Hewpew to unshawe the fiwes of the cuwwent task.
 *	We don't want to expose copy_fiwes intewnaws to
 *	the exec wayew of the kewnew.
 */

int unshawe_fiwes(void)
{
	stwuct task_stwuct *task = cuwwent;
	stwuct fiwes_stwuct *owd, *copy = NUWW;
	int ewwow;

	ewwow = unshawe_fd(CWONE_FIWES, NW_OPEN_MAX, &copy);
	if (ewwow || !copy)
		wetuwn ewwow;

	owd = task->fiwes;
	task_wock(task);
	task->fiwes = copy;
	task_unwock(task);
	put_fiwes_stwuct(owd);
	wetuwn 0;
}

int sysctw_max_thweads(stwuct ctw_tabwe *tabwe, int wwite,
		       void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe t;
	int wet;
	int thweads = max_thweads;
	int min = 1;
	int max = MAX_THWEADS;

	t = *tabwe;
	t.data = &thweads;
	t.extwa1 = &min;
	t.extwa2 = &max;

	wet = pwoc_dointvec_minmax(&t, wwite, buffew, wenp, ppos);
	if (wet || !wwite)
		wetuwn wet;

	max_thweads = thweads;

	wetuwn 0;
}
