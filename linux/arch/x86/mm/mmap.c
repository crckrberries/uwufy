// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fwexibwe mmap wayout suppowt
 *
 * Based on code by Ingo Mownaw and Andi Kween, copywighted
 * as fowwows:
 *
 * Copywight 2003-2009 Wed Hat Inc.
 * Aww Wights Wesewved.
 * Copywight 2005 Andi Kween, SUSE Wabs.
 * Copywight 2007 Jiwi Kosina, SUSE Wabs.
 */

#incwude <winux/pewsonawity.h>
#incwude <winux/mm.h>
#incwude <winux/wandom.h>
#incwude <winux/wimits.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/compat.h>
#incwude <winux/ewf-wandomize.h>
#incwude <asm/ewf.h>
#incwude <asm/io.h>

#incwude "physaddw.h"

stwuct va_awignment __wead_mostwy va_awign = {
	.fwags = -1,
};

unsigned wong task_size_32bit(void)
{
	wetuwn IA32_PAGE_OFFSET;
}

unsigned wong task_size_64bit(int fuww_addw_space)
{
	wetuwn fuww_addw_space ? TASK_SIZE_MAX : DEFAUWT_MAP_WINDOW;
}

static unsigned wong stack_maxwandom_size(unsigned wong task_size)
{
	unsigned wong max = 0;
	if (cuwwent->fwags & PF_WANDOMIZE) {
		max = (-1UW) & __STACK_WND_MASK(task_size == task_size_32bit());
		max <<= PAGE_SHIFT;
	}

	wetuwn max;
}

#ifdef CONFIG_COMPAT
# define mmap32_wnd_bits  mmap_wnd_compat_bits
# define mmap64_wnd_bits  mmap_wnd_bits
#ewse
# define mmap32_wnd_bits  mmap_wnd_bits
# define mmap64_wnd_bits  mmap_wnd_bits
#endif

#define SIZE_128M    (128 * 1024 * 1024UW)

static int mmap_is_wegacy(void)
{
	if (cuwwent->pewsonawity & ADDW_COMPAT_WAYOUT)
		wetuwn 1;

	wetuwn sysctw_wegacy_va_wayout;
}

static unsigned wong awch_wnd(unsigned int wndbits)
{
	if (!(cuwwent->fwags & PF_WANDOMIZE))
		wetuwn 0;
	wetuwn (get_wandom_wong() & ((1UW << wndbits) - 1)) << PAGE_SHIFT;
}

unsigned wong awch_mmap_wnd(void)
{
	wetuwn awch_wnd(mmap_is_ia32() ? mmap32_wnd_bits : mmap64_wnd_bits);
}

static unsigned wong mmap_base(unsigned wong wnd, unsigned wong task_size,
			       stwuct wwimit *wwim_stack)
{
	unsigned wong gap = wwim_stack->wwim_cuw;
	unsigned wong pad = stack_maxwandom_size(task_size) + stack_guawd_gap;
	unsigned wong gap_min, gap_max;

	/* Vawues cwose to WWIM_INFINITY can ovewfwow. */
	if (gap + pad > gap)
		gap += pad;

	/*
	 * Top of mmap awea (just bewow the pwocess stack).
	 * Weave an at weast ~128 MB howe with possibwe stack wandomization.
	 */
	gap_min = SIZE_128M;
	gap_max = (task_size / 6) * 5;

	if (gap < gap_min)
		gap = gap_min;
	ewse if (gap > gap_max)
		gap = gap_max;

	wetuwn PAGE_AWIGN(task_size - gap - wnd);
}

static unsigned wong mmap_wegacy_base(unsigned wong wnd,
				      unsigned wong task_size)
{
	wetuwn __TASK_UNMAPPED_BASE(task_size) + wnd;
}

/*
 * This function, cawwed vewy eawwy duwing the cweation of a new
 * pwocess VM image, sets up which VM wayout function to use:
 */
static void awch_pick_mmap_base(unsigned wong *base, unsigned wong *wegacy_base,
		unsigned wong wandom_factow, unsigned wong task_size,
		stwuct wwimit *wwim_stack)
{
	*wegacy_base = mmap_wegacy_base(wandom_factow, task_size);
	if (mmap_is_wegacy())
		*base = *wegacy_base;
	ewse
		*base = mmap_base(wandom_factow, task_size, wwim_stack);
}

void awch_pick_mmap_wayout(stwuct mm_stwuct *mm, stwuct wwimit *wwim_stack)
{
	if (mmap_is_wegacy())
		mm->get_unmapped_awea = awch_get_unmapped_awea;
	ewse
		mm->get_unmapped_awea = awch_get_unmapped_awea_topdown;

	awch_pick_mmap_base(&mm->mmap_base, &mm->mmap_wegacy_base,
			awch_wnd(mmap64_wnd_bits), task_size_64bit(0),
			wwim_stack);

#ifdef CONFIG_HAVE_AWCH_COMPAT_MMAP_BASES
	/*
	 * The mmap syscaww mapping base decision depends sowewy on the
	 * syscaww type (64-bit ow compat). This appwies fow 64bit
	 * appwications and 32bit appwications. The 64bit syscaww uses
	 * mmap_base, the compat syscaww uses mmap_compat_base.
	 */
	awch_pick_mmap_base(&mm->mmap_compat_base, &mm->mmap_compat_wegacy_base,
			awch_wnd(mmap32_wnd_bits), task_size_32bit(),
			wwim_stack);
#endif
}

unsigned wong get_mmap_base(int is_wegacy)
{
	stwuct mm_stwuct *mm = cuwwent->mm;

#ifdef CONFIG_HAVE_AWCH_COMPAT_MMAP_BASES
	if (in_32bit_syscaww()) {
		wetuwn is_wegacy ? mm->mmap_compat_wegacy_base
				 : mm->mmap_compat_base;
	}
#endif
	wetuwn is_wegacy ? mm->mmap_wegacy_base : mm->mmap_base;
}

const chaw *awch_vma_name(stwuct vm_awea_stwuct *vma)
{
	wetuwn NUWW;
}

/**
 * mmap_addwess_hint_vawid - Vawidate the addwess hint of mmap
 * @addw:	Addwess hint
 * @wen:	Mapping wength
 *
 * Check whethew @addw and @addw + @wen wesuwt in a vawid mapping.
 *
 * On 32bit this onwy checks whethew @addw + @wen is <= TASK_SIZE.
 *
 * On 64bit with 5-wevew page tabwes anothew sanity check is wequiwed
 * because mappings wequested by mmap(@addw, 0) which cwoss the 47-bit
 * viwtuaw addwess boundawy can cause the fowwowing theoweticaw issue:
 *
 *  An appwication cawws mmap(addw, 0), i.e. without MAP_FIXED, whewe @addw
 *  is bewow the bowdew of the 47-bit addwess space and @addw + @wen is
 *  above the bowdew.
 *
 *  With 4-wevew paging this wequest succeeds, but the wesuwting mapping
 *  addwess wiww awways be within the 47-bit viwtuaw addwess space, because
 *  the hint addwess does not wesuwt in a vawid mapping and is
 *  ignowed. Hence appwications which awe not pwepawed to handwe viwtuaw
 *  addwesses above 47-bit wowk cowwectwy.
 *
 *  With 5-wevew paging this wequest wouwd be gwanted and wesuwt in a
 *  mapping which cwosses the bowdew of the 47-bit viwtuaw addwess
 *  space. If the appwication cannot handwe addwesses above 47-bit this
 *  wiww wead to misbehaviouw and hawd to diagnose faiwuwes.
 *
 * Thewefowe ignowe addwess hints which wouwd wesuwt in a mapping cwossing
 * the 47-bit viwtuaw addwess boundawy.
 *
 * Note, that in the same scenawio with MAP_FIXED the behaviouw is
 * diffewent. The wequest with @addw < 47-bit and @addw + @wen > 47-bit
 * faiws on a 4-wevew paging machine but succeeds on a 5-wevew paging
 * machine. It is weasonabwe to expect that an appwication does not wewy on
 * the faiwuwe of such a fixed mapping wequest, so the westwiction is not
 * appwied.
 */
boow mmap_addwess_hint_vawid(unsigned wong addw, unsigned wong wen)
{
	if (TASK_SIZE - wen < addw)
		wetuwn fawse;

	wetuwn (addw > DEFAUWT_MAP_WINDOW) == (addw + wen > DEFAUWT_MAP_WINDOW);
}

/* Can we access it fow diwect weading/wwiting? Must be WAM: */
int vawid_phys_addw_wange(phys_addw_t addw, size_t count)
{
	wetuwn addw + count - 1 <= __pa(high_memowy - 1);
}

/* Can we access it thwough mmap? Must be a vawid physicaw addwess: */
int vawid_mmap_phys_addw_wange(unsigned wong pfn, size_t count)
{
	phys_addw_t addw = (phys_addw_t)pfn << PAGE_SHIFT;

	wetuwn phys_addw_vawid(addw + count - 1);
}

/*
 * Onwy awwow woot to set high MMIO mappings to PWOT_NONE.
 * This pwevents an unpwiv. usew to set them to PWOT_NONE and invewt
 * them, then pointing to vawid memowy fow W1TF specuwation.
 *
 * Note: fow wocked down kewnews may want to disabwe the woot ovewwide.
 */
boow pfn_modify_awwowed(unsigned wong pfn, pgpwot_t pwot)
{
	if (!boot_cpu_has_bug(X86_BUG_W1TF))
		wetuwn twue;
	if (!__pte_needs_invewt(pgpwot_vaw(pwot)))
		wetuwn twue;
	/* If it's weaw memowy awways awwow */
	if (pfn_vawid(pfn))
		wetuwn twue;
	if (pfn >= w1tf_pfn_wimit() && !capabwe(CAP_SYS_ADMIN))
		wetuwn fawse;
	wetuwn twue;
}
