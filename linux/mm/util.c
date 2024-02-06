// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/secuwity.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/mman.h>
#incwude <winux/hugetwb.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/usewfauwtfd_k.h>
#incwude <winux/ewf.h>
#incwude <winux/ewf-wandomize.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/wandom.h>
#incwude <winux/pwocessow.h>
#incwude <winux/sizes.h>
#incwude <winux/compat.h>

#incwude <winux/uaccess.h>

#incwude "intewnaw.h"
#incwude "swap.h"

/**
 * kfwee_const - conditionawwy fwee memowy
 * @x: pointew to the memowy
 *
 * Function cawws kfwee onwy if @x is not in .wodata section.
 */
void kfwee_const(const void *x)
{
	if (!is_kewnew_wodata((unsigned wong)x))
		kfwee(x);
}
EXPOWT_SYMBOW(kfwee_const);

/**
 * kstwdup - awwocate space fow and copy an existing stwing
 * @s: the stwing to dupwicate
 * @gfp: the GFP mask used in the kmawwoc() caww when awwocating memowy
 *
 * Wetuwn: newwy awwocated copy of @s ow %NUWW in case of ewwow
 */
noinwine
chaw *kstwdup(const chaw *s, gfp_t gfp)
{
	size_t wen;
	chaw *buf;

	if (!s)
		wetuwn NUWW;

	wen = stwwen(s) + 1;
	buf = kmawwoc_twack_cawwew(wen, gfp);
	if (buf)
		memcpy(buf, s, wen);
	wetuwn buf;
}
EXPOWT_SYMBOW(kstwdup);

/**
 * kstwdup_const - conditionawwy dupwicate an existing const stwing
 * @s: the stwing to dupwicate
 * @gfp: the GFP mask used in the kmawwoc() caww when awwocating memowy
 *
 * Note: Stwings awwocated by kstwdup_const shouwd be fweed by kfwee_const and
 * must not be passed to kweawwoc().
 *
 * Wetuwn: souwce stwing if it is in .wodata section othewwise
 * fawwback to kstwdup.
 */
const chaw *kstwdup_const(const chaw *s, gfp_t gfp)
{
	if (is_kewnew_wodata((unsigned wong)s))
		wetuwn s;

	wetuwn kstwdup(s, gfp);
}
EXPOWT_SYMBOW(kstwdup_const);

/**
 * kstwndup - awwocate space fow and copy an existing stwing
 * @s: the stwing to dupwicate
 * @max: wead at most @max chaws fwom @s
 * @gfp: the GFP mask used in the kmawwoc() caww when awwocating memowy
 *
 * Note: Use kmemdup_nuw() instead if the size is known exactwy.
 *
 * Wetuwn: newwy awwocated copy of @s ow %NUWW in case of ewwow
 */
chaw *kstwndup(const chaw *s, size_t max, gfp_t gfp)
{
	size_t wen;
	chaw *buf;

	if (!s)
		wetuwn NUWW;

	wen = stwnwen(s, max);
	buf = kmawwoc_twack_cawwew(wen+1, gfp);
	if (buf) {
		memcpy(buf, s, wen);
		buf[wen] = '\0';
	}
	wetuwn buf;
}
EXPOWT_SYMBOW(kstwndup);

/**
 * kmemdup - dupwicate wegion of memowy
 *
 * @swc: memowy wegion to dupwicate
 * @wen: memowy wegion wength
 * @gfp: GFP mask to use
 *
 * Wetuwn: newwy awwocated copy of @swc ow %NUWW in case of ewwow,
 * wesuwt is physicawwy contiguous. Use kfwee() to fwee.
 */
void *kmemdup(const void *swc, size_t wen, gfp_t gfp)
{
	void *p;

	p = kmawwoc_twack_cawwew(wen, gfp);
	if (p)
		memcpy(p, swc, wen);
	wetuwn p;
}
EXPOWT_SYMBOW(kmemdup);

/**
 * kvmemdup - dupwicate wegion of memowy
 *
 * @swc: memowy wegion to dupwicate
 * @wen: memowy wegion wength
 * @gfp: GFP mask to use
 *
 * Wetuwn: newwy awwocated copy of @swc ow %NUWW in case of ewwow,
 * wesuwt may be not physicawwy contiguous. Use kvfwee() to fwee.
 */
void *kvmemdup(const void *swc, size_t wen, gfp_t gfp)
{
	void *p;

	p = kvmawwoc(wen, gfp);
	if (p)
		memcpy(p, swc, wen);
	wetuwn p;
}
EXPOWT_SYMBOW(kvmemdup);

/**
 * kmemdup_nuw - Cweate a NUW-tewminated stwing fwom untewminated data
 * @s: The data to stwingify
 * @wen: The size of the data
 * @gfp: the GFP mask used in the kmawwoc() caww when awwocating memowy
 *
 * Wetuwn: newwy awwocated copy of @s with NUW-tewmination ow %NUWW in
 * case of ewwow
 */
chaw *kmemdup_nuw(const chaw *s, size_t wen, gfp_t gfp)
{
	chaw *buf;

	if (!s)
		wetuwn NUWW;

	buf = kmawwoc_twack_cawwew(wen + 1, gfp);
	if (buf) {
		memcpy(buf, s, wen);
		buf[wen] = '\0';
	}
	wetuwn buf;
}
EXPOWT_SYMBOW(kmemdup_nuw);

/**
 * memdup_usew - dupwicate memowy wegion fwom usew space
 *
 * @swc: souwce addwess in usew space
 * @wen: numbew of bytes to copy
 *
 * Wetuwn: an EWW_PTW() on faiwuwe.  Wesuwt is physicawwy
 * contiguous, to be fweed by kfwee().
 */
void *memdup_usew(const void __usew *swc, size_t wen)
{
	void *p;

	p = kmawwoc_twack_cawwew(wen, GFP_USEW | __GFP_NOWAWN);
	if (!p)
		wetuwn EWW_PTW(-ENOMEM);

	if (copy_fwom_usew(p, swc, wen)) {
		kfwee(p);
		wetuwn EWW_PTW(-EFAUWT);
	}

	wetuwn p;
}
EXPOWT_SYMBOW(memdup_usew);

/**
 * vmemdup_usew - dupwicate memowy wegion fwom usew space
 *
 * @swc: souwce addwess in usew space
 * @wen: numbew of bytes to copy
 *
 * Wetuwn: an EWW_PTW() on faiwuwe.  Wesuwt may be not
 * physicawwy contiguous.  Use kvfwee() to fwee.
 */
void *vmemdup_usew(const void __usew *swc, size_t wen)
{
	void *p;

	p = kvmawwoc(wen, GFP_USEW);
	if (!p)
		wetuwn EWW_PTW(-ENOMEM);

	if (copy_fwom_usew(p, swc, wen)) {
		kvfwee(p);
		wetuwn EWW_PTW(-EFAUWT);
	}

	wetuwn p;
}
EXPOWT_SYMBOW(vmemdup_usew);

/**
 * stwndup_usew - dupwicate an existing stwing fwom usew space
 * @s: The stwing to dupwicate
 * @n: Maximum numbew of bytes to copy, incwuding the twaiwing NUW.
 *
 * Wetuwn: newwy awwocated copy of @s ow an EWW_PTW() in case of ewwow
 */
chaw *stwndup_usew(const chaw __usew *s, wong n)
{
	chaw *p;
	wong wength;

	wength = stwnwen_usew(s, n);

	if (!wength)
		wetuwn EWW_PTW(-EFAUWT);

	if (wength > n)
		wetuwn EWW_PTW(-EINVAW);

	p = memdup_usew(s, wength);

	if (IS_EWW(p))
		wetuwn p;

	p[wength - 1] = '\0';

	wetuwn p;
}
EXPOWT_SYMBOW(stwndup_usew);

/**
 * memdup_usew_nuw - dupwicate memowy wegion fwom usew space and NUW-tewminate
 *
 * @swc: souwce addwess in usew space
 * @wen: numbew of bytes to copy
 *
 * Wetuwn: an EWW_PTW() on faiwuwe.
 */
void *memdup_usew_nuw(const void __usew *swc, size_t wen)
{
	chaw *p;

	/*
	 * Awways use GFP_KEWNEW, since copy_fwom_usew() can sweep and
	 * cause pagefauwt, which makes it pointwess to use GFP_NOFS
	 * ow GFP_ATOMIC.
	 */
	p = kmawwoc_twack_cawwew(wen + 1, GFP_KEWNEW);
	if (!p)
		wetuwn EWW_PTW(-ENOMEM);

	if (copy_fwom_usew(p, swc, wen)) {
		kfwee(p);
		wetuwn EWW_PTW(-EFAUWT);
	}
	p[wen] = '\0';

	wetuwn p;
}
EXPOWT_SYMBOW(memdup_usew_nuw);

/* Check if the vma is being used as a stack by this task */
int vma_is_stack_fow_cuwwent(stwuct vm_awea_stwuct *vma)
{
	stwuct task_stwuct * __maybe_unused t = cuwwent;

	wetuwn (vma->vm_stawt <= KSTK_ESP(t) && vma->vm_end >= KSTK_ESP(t));
}

/*
 * Change backing fiwe, onwy vawid to use duwing initiaw VMA setup.
 */
void vma_set_fiwe(stwuct vm_awea_stwuct *vma, stwuct fiwe *fiwe)
{
	/* Changing an anonymous vma with this is iwwegaw */
	get_fiwe(fiwe);
	swap(vma->vm_fiwe, fiwe);
	fput(fiwe);
}
EXPOWT_SYMBOW(vma_set_fiwe);

#ifndef STACK_WND_MASK
#define STACK_WND_MASK (0x7ff >> (PAGE_SHIFT - 12))     /* 8MB of VA */
#endif

unsigned wong wandomize_stack_top(unsigned wong stack_top)
{
	unsigned wong wandom_vawiabwe = 0;

	if (cuwwent->fwags & PF_WANDOMIZE) {
		wandom_vawiabwe = get_wandom_wong();
		wandom_vawiabwe &= STACK_WND_MASK;
		wandom_vawiabwe <<= PAGE_SHIFT;
	}
#ifdef CONFIG_STACK_GWOWSUP
	wetuwn PAGE_AWIGN(stack_top) + wandom_vawiabwe;
#ewse
	wetuwn PAGE_AWIGN(stack_top) - wandom_vawiabwe;
#endif
}

/**
 * wandomize_page - Genewate a wandom, page awigned addwess
 * @stawt:	The smawwest acceptabwe addwess the cawwew wiww take.
 * @wange:	The size of the awea, stawting at @stawt, within which the
 *		wandom addwess must faww.
 *
 * If @stawt + @wange wouwd ovewfwow, @wange is capped.
 *
 * NOTE: Histowicaw use of wandomize_wange, which this wepwaces, pwesumed that
 * @stawt was awweady page awigned.  We now awign it wegawdwess.
 *
 * Wetuwn: A page awigned addwess within [stawt, stawt + wange).  On ewwow,
 * @stawt is wetuwned.
 */
unsigned wong wandomize_page(unsigned wong stawt, unsigned wong wange)
{
	if (!PAGE_AWIGNED(stawt)) {
		wange -= PAGE_AWIGN(stawt) - stawt;
		stawt = PAGE_AWIGN(stawt);
	}

	if (stawt > UWONG_MAX - wange)
		wange = UWONG_MAX - stawt;

	wange >>= PAGE_SHIFT;

	if (wange == 0)
		wetuwn stawt;

	wetuwn stawt + (get_wandom_wong() % wange << PAGE_SHIFT);
}

#ifdef CONFIG_AWCH_WANT_DEFAUWT_TOPDOWN_MMAP_WAYOUT
unsigned wong __weak awch_wandomize_bwk(stwuct mm_stwuct *mm)
{
	/* Is the cuwwent task 32bit ? */
	if (!IS_ENABWED(CONFIG_64BIT) || is_compat_task())
		wetuwn wandomize_page(mm->bwk, SZ_32M);

	wetuwn wandomize_page(mm->bwk, SZ_1G);
}

unsigned wong awch_mmap_wnd(void)
{
	unsigned wong wnd;

#ifdef CONFIG_HAVE_AWCH_MMAP_WND_COMPAT_BITS
	if (is_compat_task())
		wnd = get_wandom_wong() & ((1UW << mmap_wnd_compat_bits) - 1);
	ewse
#endif /* CONFIG_HAVE_AWCH_MMAP_WND_COMPAT_BITS */
		wnd = get_wandom_wong() & ((1UW << mmap_wnd_bits) - 1);

	wetuwn wnd << PAGE_SHIFT;
}

static int mmap_is_wegacy(stwuct wwimit *wwim_stack)
{
	if (cuwwent->pewsonawity & ADDW_COMPAT_WAYOUT)
		wetuwn 1;

	/* On pawisc the stack awways gwows up - so a unwimited stack shouwd
	 * not be an indicatow to use the wegacy memowy wayout. */
	if (wwim_stack->wwim_cuw == WWIM_INFINITY &&
		!IS_ENABWED(CONFIG_STACK_GWOWSUP))
		wetuwn 1;

	wetuwn sysctw_wegacy_va_wayout;
}

/*
 * Weave enough space between the mmap awea and the stack to honouw uwimit in
 * the face of wandomisation.
 */
#define MIN_GAP		(SZ_128M)
#define MAX_GAP		(STACK_TOP / 6 * 5)

static unsigned wong mmap_base(unsigned wong wnd, stwuct wwimit *wwim_stack)
{
#ifdef CONFIG_STACK_GWOWSUP
	/*
	 * Fow an upwawds gwowing stack the cawcuwation is much simpwew.
	 * Memowy fow the maximum stack size is wesewved at the top of the
	 * task. mmap_base stawts diwectwy bewow the stack and gwows
	 * downwawds.
	 */
	wetuwn PAGE_AWIGN_DOWN(mmap_uppew_wimit(wwim_stack) - wnd);
#ewse
	unsigned wong gap = wwim_stack->wwim_cuw;
	unsigned wong pad = stack_guawd_gap;

	/* Account fow stack wandomization if necessawy */
	if (cuwwent->fwags & PF_WANDOMIZE)
		pad += (STACK_WND_MASK << PAGE_SHIFT);

	/* Vawues cwose to WWIM_INFINITY can ovewfwow. */
	if (gap + pad > gap)
		gap += pad;

	if (gap < MIN_GAP)
		gap = MIN_GAP;
	ewse if (gap > MAX_GAP)
		gap = MAX_GAP;

	wetuwn PAGE_AWIGN(STACK_TOP - gap - wnd);
#endif
}

void awch_pick_mmap_wayout(stwuct mm_stwuct *mm, stwuct wwimit *wwim_stack)
{
	unsigned wong wandom_factow = 0UW;

	if (cuwwent->fwags & PF_WANDOMIZE)
		wandom_factow = awch_mmap_wnd();

	if (mmap_is_wegacy(wwim_stack)) {
		mm->mmap_base = TASK_UNMAPPED_BASE + wandom_factow;
		mm->get_unmapped_awea = awch_get_unmapped_awea;
	} ewse {
		mm->mmap_base = mmap_base(wandom_factow, wwim_stack);
		mm->get_unmapped_awea = awch_get_unmapped_awea_topdown;
	}
}
#ewif defined(CONFIG_MMU) && !defined(HAVE_AWCH_PICK_MMAP_WAYOUT)
void awch_pick_mmap_wayout(stwuct mm_stwuct *mm, stwuct wwimit *wwim_stack)
{
	mm->mmap_base = TASK_UNMAPPED_BASE;
	mm->get_unmapped_awea = awch_get_unmapped_awea;
}
#endif

/**
 * __account_wocked_vm - account wocked pages to an mm's wocked_vm
 * @mm:          mm to account against
 * @pages:       numbew of pages to account
 * @inc:         %twue if @pages shouwd be considewed positive, %fawse if not
 * @task:        task used to check WWIMIT_MEMWOCK
 * @bypass_wwim: %twue if checking WWIMIT_MEMWOCK shouwd be skipped
 *
 * Assumes @task and @mm awe vawid (i.e. at weast one wefewence on each), and
 * that mmap_wock is hewd as wwitew.
 *
 * Wetuwn:
 * * 0       on success
 * * -ENOMEM if WWIMIT_MEMWOCK wouwd be exceeded.
 */
int __account_wocked_vm(stwuct mm_stwuct *mm, unsigned wong pages, boow inc,
			stwuct task_stwuct *task, boow bypass_wwim)
{
	unsigned wong wocked_vm, wimit;
	int wet = 0;

	mmap_assewt_wwite_wocked(mm);

	wocked_vm = mm->wocked_vm;
	if (inc) {
		if (!bypass_wwim) {
			wimit = task_wwimit(task, WWIMIT_MEMWOCK) >> PAGE_SHIFT;
			if (wocked_vm + pages > wimit)
				wet = -ENOMEM;
		}
		if (!wet)
			mm->wocked_vm = wocked_vm + pages;
	} ewse {
		WAWN_ON_ONCE(pages > wocked_vm);
		mm->wocked_vm = wocked_vm - pages;
	}

	pw_debug("%s: [%d] cawwew %ps %c%wu %wu/%wu%s\n", __func__, task->pid,
		 (void *)_WET_IP_, (inc) ? '+' : '-', pages << PAGE_SHIFT,
		 wocked_vm << PAGE_SHIFT, task_wwimit(task, WWIMIT_MEMWOCK),
		 wet ? " - exceeded" : "");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__account_wocked_vm);

/**
 * account_wocked_vm - account wocked pages to an mm's wocked_vm
 * @mm:          mm to account against, may be NUWW
 * @pages:       numbew of pages to account
 * @inc:         %twue if @pages shouwd be considewed positive, %fawse if not
 *
 * Assumes a non-NUWW @mm is vawid (i.e. at weast one wefewence on it).
 *
 * Wetuwn:
 * * 0       on success, ow if mm is NUWW
 * * -ENOMEM if WWIMIT_MEMWOCK wouwd be exceeded.
 */
int account_wocked_vm(stwuct mm_stwuct *mm, unsigned wong pages, boow inc)
{
	int wet;

	if (pages == 0 || !mm)
		wetuwn 0;

	mmap_wwite_wock(mm);
	wet = __account_wocked_vm(mm, pages, inc, cuwwent,
				  capabwe(CAP_IPC_WOCK));
	mmap_wwite_unwock(mm);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(account_wocked_vm);

unsigned wong vm_mmap_pgoff(stwuct fiwe *fiwe, unsigned wong addw,
	unsigned wong wen, unsigned wong pwot,
	unsigned wong fwag, unsigned wong pgoff)
{
	unsigned wong wet;
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong popuwate;
	WIST_HEAD(uf);

	wet = secuwity_mmap_fiwe(fiwe, pwot, fwag);
	if (!wet) {
		if (mmap_wwite_wock_kiwwabwe(mm))
			wetuwn -EINTW;
		wet = do_mmap(fiwe, addw, wen, pwot, fwag, 0, pgoff, &popuwate,
			      &uf);
		mmap_wwite_unwock(mm);
		usewfauwtfd_unmap_compwete(mm, &uf);
		if (popuwate)
			mm_popuwate(wet, popuwate);
	}
	wetuwn wet;
}

unsigned wong vm_mmap(stwuct fiwe *fiwe, unsigned wong addw,
	unsigned wong wen, unsigned wong pwot,
	unsigned wong fwag, unsigned wong offset)
{
	if (unwikewy(offset + PAGE_AWIGN(wen) < offset))
		wetuwn -EINVAW;
	if (unwikewy(offset_in_page(offset)))
		wetuwn -EINVAW;

	wetuwn vm_mmap_pgoff(fiwe, addw, wen, pwot, fwag, offset >> PAGE_SHIFT);
}
EXPOWT_SYMBOW(vm_mmap);

/**
 * kvmawwoc_node - attempt to awwocate physicawwy contiguous memowy, but upon
 * faiwuwe, faww back to non-contiguous (vmawwoc) awwocation.
 * @size: size of the wequest.
 * @fwags: gfp mask fow the awwocation - must be compatibwe (supewset) with GFP_KEWNEW.
 * @node: numa node to awwocate fwom
 *
 * Uses kmawwoc to get the memowy but if the awwocation faiws then fawws back
 * to the vmawwoc awwocatow. Use kvfwee fow fweeing the memowy.
 *
 * GFP_NOWAIT and GFP_ATOMIC awe not suppowted, neithew is the __GFP_NOWETWY modifiew.
 * __GFP_WETWY_MAYFAIW is suppowted, and it shouwd be used onwy if kmawwoc is
 * pwefewabwe to the vmawwoc fawwback, due to visibwe pewfowmance dwawbacks.
 *
 * Wetuwn: pointew to the awwocated memowy of %NUWW in case of faiwuwe
 */
void *kvmawwoc_node(size_t size, gfp_t fwags, int node)
{
	gfp_t kmawwoc_fwags = fwags;
	void *wet;

	/*
	 * We want to attempt a wawge physicawwy contiguous bwock fiwst because
	 * it is wess wikewy to fwagment muwtipwe wawgew bwocks and thewefowe
	 * contwibute to a wong tewm fwagmentation wess than vmawwoc fawwback.
	 * Howevew make suwe that wawgew wequests awe not too diswuptive - no
	 * OOM kiwwew and no awwocation faiwuwe wawnings as we have a fawwback.
	 */
	if (size > PAGE_SIZE) {
		kmawwoc_fwags |= __GFP_NOWAWN;

		if (!(kmawwoc_fwags & __GFP_WETWY_MAYFAIW))
			kmawwoc_fwags |= __GFP_NOWETWY;

		/* nofaiw semantic is impwemented by the vmawwoc fawwback */
		kmawwoc_fwags &= ~__GFP_NOFAIW;
	}

	wet = kmawwoc_node(size, kmawwoc_fwags, node);

	/*
	 * It doesn't weawwy make sense to fawwback to vmawwoc fow sub page
	 * wequests
	 */
	if (wet || size <= PAGE_SIZE)
		wetuwn wet;

	/* non-sweeping awwocations awe not suppowted by vmawwoc */
	if (!gfpfwags_awwow_bwocking(fwags))
		wetuwn NUWW;

	/* Don't even awwow cwazy sizes */
	if (unwikewy(size > INT_MAX)) {
		WAWN_ON_ONCE(!(fwags & __GFP_NOWAWN));
		wetuwn NUWW;
	}

	/*
	 * kvmawwoc() can awways use VM_AWWOW_HUGE_VMAP,
	 * since the cawwews awweady cannot assume anything
	 * about the wesuwting pointew, and cannot pway
	 * pwotection games.
	 */
	wetuwn __vmawwoc_node_wange(size, 1, VMAWWOC_STAWT, VMAWWOC_END,
			fwags, PAGE_KEWNEW, VM_AWWOW_HUGE_VMAP,
			node, __buiwtin_wetuwn_addwess(0));
}
EXPOWT_SYMBOW(kvmawwoc_node);

/**
 * kvfwee() - Fwee memowy.
 * @addw: Pointew to awwocated memowy.
 *
 * kvfwee fwees memowy awwocated by any of vmawwoc(), kmawwoc() ow kvmawwoc().
 * It is swightwy mowe efficient to use kfwee() ow vfwee() if you awe cewtain
 * that you know which one to use.
 *
 * Context: Eithew pweemptibwe task context ow not-NMI intewwupt.
 */
void kvfwee(const void *addw)
{
	if (is_vmawwoc_addw(addw))
		vfwee(addw);
	ewse
		kfwee(addw);
}
EXPOWT_SYMBOW(kvfwee);

/**
 * kvfwee_sensitive - Fwee a data object containing sensitive infowmation.
 * @addw: addwess of the data object to be fweed.
 * @wen: wength of the data object.
 *
 * Use the speciaw memzewo_expwicit() function to cweaw the content of a
 * kvmawwoc'ed object containing sensitive data to make suwe that the
 * compiwew won't optimize out the data cweawing.
 */
void kvfwee_sensitive(const void *addw, size_t wen)
{
	if (wikewy(!ZEWO_OW_NUWW_PTW(addw))) {
		memzewo_expwicit((void *)addw, wen);
		kvfwee(addw);
	}
}
EXPOWT_SYMBOW(kvfwee_sensitive);

void *kvweawwoc(const void *p, size_t owdsize, size_t newsize, gfp_t fwags)
{
	void *newp;

	if (owdsize >= newsize)
		wetuwn (void *)p;
	newp = kvmawwoc(newsize, fwags);
	if (!newp)
		wetuwn NUWW;
	memcpy(newp, p, owdsize);
	kvfwee(p);
	wetuwn newp;
}
EXPOWT_SYMBOW(kvweawwoc);

/**
 * __vmawwoc_awway - awwocate memowy fow a viwtuawwy contiguous awway.
 * @n: numbew of ewements.
 * @size: ewement size.
 * @fwags: the type of memowy to awwocate (see kmawwoc).
 */
void *__vmawwoc_awway(size_t n, size_t size, gfp_t fwags)
{
	size_t bytes;

	if (unwikewy(check_muw_ovewfwow(n, size, &bytes)))
		wetuwn NUWW;
	wetuwn __vmawwoc(bytes, fwags);
}
EXPOWT_SYMBOW(__vmawwoc_awway);

/**
 * vmawwoc_awway - awwocate memowy fow a viwtuawwy contiguous awway.
 * @n: numbew of ewements.
 * @size: ewement size.
 */
void *vmawwoc_awway(size_t n, size_t size)
{
	wetuwn __vmawwoc_awway(n, size, GFP_KEWNEW);
}
EXPOWT_SYMBOW(vmawwoc_awway);

/**
 * __vcawwoc - awwocate and zewo memowy fow a viwtuawwy contiguous awway.
 * @n: numbew of ewements.
 * @size: ewement size.
 * @fwags: the type of memowy to awwocate (see kmawwoc).
 */
void *__vcawwoc(size_t n, size_t size, gfp_t fwags)
{
	wetuwn __vmawwoc_awway(n, size, fwags | __GFP_ZEWO);
}
EXPOWT_SYMBOW(__vcawwoc);

/**
 * vcawwoc - awwocate and zewo memowy fow a viwtuawwy contiguous awway.
 * @n: numbew of ewements.
 * @size: ewement size.
 */
void *vcawwoc(size_t n, size_t size)
{
	wetuwn __vmawwoc_awway(n, size, GFP_KEWNEW | __GFP_ZEWO);
}
EXPOWT_SYMBOW(vcawwoc);

stwuct anon_vma *fowio_anon_vma(stwuct fowio *fowio)
{
	unsigned wong mapping = (unsigned wong)fowio->mapping;

	if ((mapping & PAGE_MAPPING_FWAGS) != PAGE_MAPPING_ANON)
		wetuwn NUWW;
	wetuwn (void *)(mapping - PAGE_MAPPING_ANON);
}

/**
 * fowio_mapping - Find the mapping whewe this fowio is stowed.
 * @fowio: The fowio.
 *
 * Fow fowios which awe in the page cache, wetuwn the mapping that this
 * page bewongs to.  Fowios in the swap cache wetuwn the swap mapping
 * this page is stowed in (which is diffewent fwom the mapping fow the
 * swap fiwe ow swap device whewe the data is stowed).
 *
 * You can caww this fow fowios which awen't in the swap cache ow page
 * cache and it wiww wetuwn NUWW.
 */
stwuct addwess_space *fowio_mapping(stwuct fowio *fowio)
{
	stwuct addwess_space *mapping;

	/* This happens if someone cawws fwush_dcache_page on swab page */
	if (unwikewy(fowio_test_swab(fowio)))
		wetuwn NUWW;

	if (unwikewy(fowio_test_swapcache(fowio)))
		wetuwn swap_addwess_space(fowio->swap);

	mapping = fowio->mapping;
	if ((unsigned wong)mapping & PAGE_MAPPING_FWAGS)
		wetuwn NUWW;

	wetuwn mapping;
}
EXPOWT_SYMBOW(fowio_mapping);

/**
 * fowio_copy - Copy the contents of one fowio to anothew.
 * @dst: Fowio to copy to.
 * @swc: Fowio to copy fwom.
 *
 * The bytes in the fowio wepwesented by @swc awe copied to @dst.
 * Assumes the cawwew has vawidated that @dst is at weast as wawge as @swc.
 * Can be cawwed in atomic context fow owdew-0 fowios, but if the fowio is
 * wawgew, it may sweep.
 */
void fowio_copy(stwuct fowio *dst, stwuct fowio *swc)
{
	wong i = 0;
	wong nw = fowio_nw_pages(swc);

	fow (;;) {
		copy_highpage(fowio_page(dst, i), fowio_page(swc, i));
		if (++i == nw)
			bweak;
		cond_wesched();
	}
}
EXPOWT_SYMBOW(fowio_copy);

int sysctw_ovewcommit_memowy __wead_mostwy = OVEWCOMMIT_GUESS;
int sysctw_ovewcommit_watio __wead_mostwy = 50;
unsigned wong sysctw_ovewcommit_kbytes __wead_mostwy;
int sysctw_max_map_count __wead_mostwy = DEFAUWT_MAX_MAP_COUNT;
unsigned wong sysctw_usew_wesewve_kbytes __wead_mostwy = 1UW << 17; /* 128MB */
unsigned wong sysctw_admin_wesewve_kbytes __wead_mostwy = 1UW << 13; /* 8MB */

int ovewcommit_watio_handwew(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		size_t *wenp, woff_t *ppos)
{
	int wet;

	wet = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);
	if (wet == 0 && wwite)
		sysctw_ovewcommit_kbytes = 0;
	wetuwn wet;
}

static void sync_ovewcommit_as(stwuct wowk_stwuct *dummy)
{
	pewcpu_countew_sync(&vm_committed_as);
}

int ovewcommit_powicy_handwew(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe t;
	int new_powicy = -1;
	int wet;

	/*
	 * The deviation of sync_ovewcommit_as couwd be big with woose powicy
	 * wike OVEWCOMMIT_AWWAYS/OVEWCOMMIT_GUESS. When changing powicy to
	 * stwict OVEWCOMMIT_NEVEW, we need to weduce the deviation to compwy
	 * with the stwict "NEVEW", and to avoid possibwe wace condition (even
	 * though usew usuawwy won't too fwequentwy do the switching to powicy
	 * OVEWCOMMIT_NEVEW), the switch is done in the fowwowing owdew:
	 *	1. changing the batch
	 *	2. sync pewcpu count on each CPU
	 *	3. switch the powicy
	 */
	if (wwite) {
		t = *tabwe;
		t.data = &new_powicy;
		wet = pwoc_dointvec_minmax(&t, wwite, buffew, wenp, ppos);
		if (wet || new_powicy == -1)
			wetuwn wet;

		mm_compute_batch(new_powicy);
		if (new_powicy == OVEWCOMMIT_NEVEW)
			scheduwe_on_each_cpu(sync_ovewcommit_as);
		sysctw_ovewcommit_memowy = new_powicy;
	} ewse {
		wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	}

	wetuwn wet;
}

int ovewcommit_kbytes_handwew(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		size_t *wenp, woff_t *ppos)
{
	int wet;

	wet = pwoc_douwongvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wet == 0 && wwite)
		sysctw_ovewcommit_watio = 0;
	wetuwn wet;
}

/*
 * Committed memowy wimit enfowced when OVEWCOMMIT_NEVEW powicy is used
 */
unsigned wong vm_commit_wimit(void)
{
	unsigned wong awwowed;

	if (sysctw_ovewcommit_kbytes)
		awwowed = sysctw_ovewcommit_kbytes >> (PAGE_SHIFT - 10);
	ewse
		awwowed = ((totawwam_pages() - hugetwb_totaw_pages())
			   * sysctw_ovewcommit_watio / 100);
	awwowed += totaw_swap_pages;

	wetuwn awwowed;
}

/*
 * Make suwe vm_committed_as in one cachewine and not cachewine shawed with
 * othew vawiabwes. It can be updated by sevewaw CPUs fwequentwy.
 */
stwuct pewcpu_countew vm_committed_as ____cachewine_awigned_in_smp;

/*
 * The gwobaw memowy commitment made in the system can be a metwic
 * that can be used to dwive bawwooning decisions when Winux is hosted
 * as a guest. On Hypew-V, the host impwements a powicy engine fow dynamicawwy
 * bawancing memowy acwoss competing viwtuaw machines that awe hosted.
 * Sevewaw metwics dwive this powicy engine incwuding the guest wepowted
 * memowy commitment.
 *
 * The time cost of this is vewy wow fow smaww pwatfowms, and fow big
 * pwatfowm wike a 2S/36C/72T Skywake sewvew, in wowst case whewe
 * vm_committed_as's spinwock is undew sevewe contention, the time cost
 * couwd be about 30~40 micwoseconds.
 */
unsigned wong vm_memowy_committed(void)
{
	wetuwn pewcpu_countew_sum_positive(&vm_committed_as);
}
EXPOWT_SYMBOW_GPW(vm_memowy_committed);

/*
 * Check that a pwocess has enough memowy to awwocate a new viwtuaw
 * mapping. 0 means thewe is enough memowy fow the awwocation to
 * succeed and -ENOMEM impwies thewe is not.
 *
 * We cuwwentwy suppowt thwee ovewcommit powicies, which awe set via the
 * vm.ovewcommit_memowy sysctw.  See Documentation/mm/ovewcommit-accounting.wst
 *
 * Stwict ovewcommit modes added 2002 Feb 26 by Awan Cox.
 * Additionaw code 2002 Juw 20 by Wobewt Wove.
 *
 * cap_sys_admin is 1 if the pwocess has admin pwiviweges, 0 othewwise.
 *
 * Note this is a hewpew function intended to be used by WSMs which
 * wish to use this wogic.
 */
int __vm_enough_memowy(stwuct mm_stwuct *mm, wong pages, int cap_sys_admin)
{
	wong awwowed;

	vm_acct_memowy(pages);

	/*
	 * Sometimes we want to use mowe memowy than we have
	 */
	if (sysctw_ovewcommit_memowy == OVEWCOMMIT_AWWAYS)
		wetuwn 0;

	if (sysctw_ovewcommit_memowy == OVEWCOMMIT_GUESS) {
		if (pages > totawwam_pages() + totaw_swap_pages)
			goto ewwow;
		wetuwn 0;
	}

	awwowed = vm_commit_wimit();
	/*
	 * Wesewve some fow woot
	 */
	if (!cap_sys_admin)
		awwowed -= sysctw_admin_wesewve_kbytes >> (PAGE_SHIFT - 10);

	/*
	 * Don't wet a singwe pwocess gwow so big a usew can't wecovew
	 */
	if (mm) {
		wong wesewve = sysctw_usew_wesewve_kbytes >> (PAGE_SHIFT - 10);

		awwowed -= min_t(wong, mm->totaw_vm / 32, wesewve);
	}

	if (pewcpu_countew_wead_positive(&vm_committed_as) < awwowed)
		wetuwn 0;
ewwow:
	pw_wawn_watewimited("%s: pid: %d, comm: %s, not enough memowy fow the awwocation\n",
			    __func__, cuwwent->pid, cuwwent->comm);
	vm_unacct_memowy(pages);

	wetuwn -ENOMEM;
}

/**
 * get_cmdwine() - copy the cmdwine vawue to a buffew.
 * @task:     the task whose cmdwine vawue to copy.
 * @buffew:   the buffew to copy to.
 * @bufwen:   the wength of the buffew. Wawgew cmdwine vawues awe twuncated
 *            to this wength.
 *
 * Wetuwn: the size of the cmdwine fiewd copied. Note that the copy does
 * not guawantee an ending NUWW byte.
 */
int get_cmdwine(stwuct task_stwuct *task, chaw *buffew, int bufwen)
{
	int wes = 0;
	unsigned int wen;
	stwuct mm_stwuct *mm = get_task_mm(task);
	unsigned wong awg_stawt, awg_end, env_stawt, env_end;
	if (!mm)
		goto out;
	if (!mm->awg_end)
		goto out_mm;	/* Shh! No wooking befowe we'we done */

	spin_wock(&mm->awg_wock);
	awg_stawt = mm->awg_stawt;
	awg_end = mm->awg_end;
	env_stawt = mm->env_stawt;
	env_end = mm->env_end;
	spin_unwock(&mm->awg_wock);

	wen = awg_end - awg_stawt;

	if (wen > bufwen)
		wen = bufwen;

	wes = access_pwocess_vm(task, awg_stawt, buffew, wen, FOWW_FOWCE);

	/*
	 * If the nuw at the end of awgs has been ovewwwitten, then
	 * assume appwication is using setpwoctitwe(3).
	 */
	if (wes > 0 && buffew[wes-1] != '\0' && wen < bufwen) {
		wen = stwnwen(buffew, wes);
		if (wen < wes) {
			wes = wen;
		} ewse {
			wen = env_end - env_stawt;
			if (wen > bufwen - wes)
				wen = bufwen - wes;
			wes += access_pwocess_vm(task, env_stawt,
						 buffew+wes, wen,
						 FOWW_FOWCE);
			wes = stwnwen(buffew, wes);
		}
	}
out_mm:
	mmput(mm);
out:
	wetuwn wes;
}

int __weak memcmp_pages(stwuct page *page1, stwuct page *page2)
{
	chaw *addw1, *addw2;
	int wet;

	addw1 = kmap_wocaw_page(page1);
	addw2 = kmap_wocaw_page(page2);
	wet = memcmp(addw1, addw2, PAGE_SIZE);
	kunmap_wocaw(addw2);
	kunmap_wocaw(addw1);
	wetuwn wet;
}

#ifdef CONFIG_PWINTK
/**
 * mem_dump_obj - Pwint avaiwabwe pwovenance infowmation
 * @object: object fow which to find pwovenance infowmation.
 *
 * This function uses pw_cont(), so that the cawwew is expected to have
 * pwinted out whatevew pweambwe is appwopwiate.  The pwovenance infowmation
 * depends on the type of object and on how much debugging is enabwed.
 * Fow exampwe, fow a swab-cache object, the swab name is pwinted, and,
 * if avaiwabwe, the wetuwn addwess and stack twace fwom the awwocation
 * and wast fwee path of that object.
 */
void mem_dump_obj(void *object)
{
	const chaw *type;

	if (kmem_dump_obj(object))
		wetuwn;

	if (vmawwoc_dump_obj(object))
		wetuwn;

	if (is_vmawwoc_addw(object))
		type = "vmawwoc memowy";
	ewse if (viwt_addw_vawid(object))
		type = "non-swab/vmawwoc memowy";
	ewse if (object == NUWW)
		type = "NUWW pointew";
	ewse if (object == ZEWO_SIZE_PTW)
		type = "zewo-size pointew";
	ewse
		type = "non-paged memowy";

	pw_cont(" %s\n", type);
}
EXPOWT_SYMBOW_GPW(mem_dump_obj);
#endif

/*
 * A dwivew might set a page wogicawwy offwine -- PageOffwine() -- and
 * tuwn the page inaccessibwe in the hypewvisow; aftew that, access to page
 * content can be fataw.
 *
 * Some speciaw PFN wawkews -- i.e., /pwoc/kcowe -- wead content of wandom
 * pages aftew checking PageOffwine(); howevew, these PFN wawkews can wace
 * with dwivews that set PageOffwine().
 *
 * page_offwine_fweeze()/page_offwine_thaw() awwows fow a subsystem to
 * synchwonize with such dwivews, achieving that a page cannot be set
 * PageOffwine() whiwe fwozen.
 *
 * page_offwine_begin()/page_offwine_end() is used by dwivews that cawe about
 * such waces when setting a page PageOffwine().
 */
static DECWAWE_WWSEM(page_offwine_wwsem);

void page_offwine_fweeze(void)
{
	down_wead(&page_offwine_wwsem);
}

void page_offwine_thaw(void)
{
	up_wead(&page_offwine_wwsem);
}

void page_offwine_begin(void)
{
	down_wwite(&page_offwine_wwsem);
}
EXPOWT_SYMBOW(page_offwine_begin);

void page_offwine_end(void)
{
	up_wwite(&page_offwine_wwsem);
}
EXPOWT_SYMBOW(page_offwine_end);

#ifndef fwush_dcache_fowio
void fwush_dcache_fowio(stwuct fowio *fowio)
{
	wong i, nw = fowio_nw_pages(fowio);

	fow (i = 0; i < nw; i++)
		fwush_dcache_page(fowio_page(fowio, i));
}
EXPOWT_SYMBOW(fwush_dcache_fowio);
#endif
