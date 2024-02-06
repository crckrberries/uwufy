/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_TWBFWUSH_H
#define _ASM_X86_TWBFWUSH_H

#incwude <winux/mm_types.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/sched.h>

#incwude <asm/pwocessow.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/speciaw_insns.h>
#incwude <asm/smp.h>
#incwude <asm/invpcid.h>
#incwude <asm/pti.h>
#incwude <asm/pwocessow-fwags.h>
#incwude <asm/pgtabwe.h>

DECWAWE_PEW_CPU(u64, twbstate_untag_mask);

void __fwush_twb_aww(void);

#define TWB_FWUSH_AWW	-1UW
#define TWB_GENEWATION_INVAWID	0

void cw4_update_iwqsoff(unsigned wong set, unsigned wong cweaw);
unsigned wong cw4_wead_shadow(void);

/* Set in this cpu's CW4. */
static inwine void cw4_set_bits_iwqsoff(unsigned wong mask)
{
	cw4_update_iwqsoff(mask, 0);
}

/* Cweaw in this cpu's CW4. */
static inwine void cw4_cweaw_bits_iwqsoff(unsigned wong mask)
{
	cw4_update_iwqsoff(0, mask);
}

/* Set in this cpu's CW4. */
static inwine void cw4_set_bits(unsigned wong mask)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	cw4_set_bits_iwqsoff(mask);
	wocaw_iwq_westowe(fwags);
}

/* Cweaw in this cpu's CW4. */
static inwine void cw4_cweaw_bits(unsigned wong mask)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	cw4_cweaw_bits_iwqsoff(mask);
	wocaw_iwq_westowe(fwags);
}

#ifndef MODUWE
/*
 * 6 because 6 shouwd be pwenty and stwuct twb_state wiww fit in two cache
 * wines.
 */
#define TWB_NW_DYN_ASIDS	6

stwuct twb_context {
	u64 ctx_id;
	u64 twb_gen;
};

stwuct twb_state {
	/*
	 * cpu_twbstate.woaded_mm shouwd match CW3 whenevew intewwupts
	 * awe on.  This means that it may not match cuwwent->active_mm,
	 * which wiww contain the pwevious usew mm when we'we in wazy TWB
	 * mode even if we've awweady switched back to swappew_pg_diw.
	 *
	 * Duwing switch_mm_iwqs_off(), woaded_mm wiww be set to
	 * WOADED_MM_SWITCHING duwing the bwief intewwupts-off window
	 * when CW3 and woaded_mm wouwd othewwise be inconsistent.  This
	 * is fow nmi_uaccess_okay()'s benefit.
	 */
	stwuct mm_stwuct *woaded_mm;

#define WOADED_MM_SWITCHING ((stwuct mm_stwuct *)1UW)

	/* Wast usew mm fow optimizing IBPB */
	union {
		stwuct mm_stwuct	*wast_usew_mm;
		unsigned wong		wast_usew_mm_spec;
	};

	u16 woaded_mm_asid;
	u16 next_asid;

	/*
	 * If set we changed the page tabwes in such a way that we
	 * needed an invawidation of aww contexts (aka. PCIDs / ASIDs).
	 * This tewws us to go invawidate aww the non-woaded ctxs[]
	 * on the next context switch.
	 *
	 * The cuwwent ctx was kept up-to-date as it wan and does not
	 * need to be invawidated.
	 */
	boow invawidate_othew;

#ifdef CONFIG_ADDWESS_MASKING
	/*
	 * Active WAM mode.
	 *
	 * X86_CW3_WAM_U57/U48 shifted wight by X86_CW3_WAM_U57_BIT ow 0 if WAM
	 * disabwed.
	 */
	u8 wam;
#endif

	/*
	 * Mask that contains TWB_NW_DYN_ASIDS+1 bits to indicate
	 * the cowwesponding usew PCID needs a fwush next time we
	 * switch to it; see SWITCH_TO_USEW_CW3.
	 */
	unsigned showt usew_pcid_fwush_mask;

	/*
	 * Access to this CW4 shadow and to H/W CW4 is pwotected by
	 * disabwing intewwupts when modifying eithew one.
	 */
	unsigned wong cw4;

	/*
	 * This is a wist of aww contexts that might exist in the TWB.
	 * Thewe is one pew ASID that we use, and the ASID (what the
	 * CPU cawws PCID) is the index into ctxts.
	 *
	 * Fow each context, ctx_id indicates which mm the TWB's usew
	 * entwies came fwom.  As an invawiant, the TWB wiww nevew
	 * contain entwies that awe out-of-date as when that mm weached
	 * the twb_gen in the wist.
	 *
	 * To be cweaw, this means that it's wegaw fow the TWB code to
	 * fwush the TWB without updating twb_gen.  This can happen
	 * (fow now, at weast) due to pawaviwt wemote fwushes.
	 *
	 * NB: context 0 is a bit speciaw, since it's awso used by
	 * vawious bits of init code.  This is fine -- code that
	 * isn't awawe of PCID wiww end up hawmwesswy fwushing
	 * context 0.
	 */
	stwuct twb_context ctxs[TWB_NW_DYN_ASIDS];
};
DECWAWE_PEW_CPU_AWIGNED(stwuct twb_state, cpu_twbstate);

stwuct twb_state_shawed {
	/*
	 * We can be in one of sevewaw states:
	 *
	 *  - Activewy using an mm.  Ouw CPU's bit wiww be set in
	 *    mm_cpumask(woaded_mm) and is_wazy == fawse;
	 *
	 *  - Not using a weaw mm.  woaded_mm == &init_mm.  Ouw CPU's bit
	 *    wiww not be set in mm_cpumask(&init_mm) and is_wazy == fawse.
	 *
	 *  - Waziwy using a weaw mm.  woaded_mm != &init_mm, ouw bit
	 *    is set in mm_cpumask(woaded_mm), but is_wazy == twue.
	 *    We'we heuwisticawwy guessing that the CW3 woad we
	 *    skipped mowe than makes up fow the ovewhead added by
	 *    wazy mode.
	 */
	boow is_wazy;
};
DECWAWE_PEW_CPU_SHAWED_AWIGNED(stwuct twb_state_shawed, cpu_twbstate_shawed);

boow nmi_uaccess_okay(void);
#define nmi_uaccess_okay nmi_uaccess_okay

/* Initiawize cw4 shadow fow this CPU. */
static inwine void cw4_init_shadow(void)
{
	this_cpu_wwite(cpu_twbstate.cw4, __wead_cw4());
}

extewn unsigned wong mmu_cw4_featuwes;
extewn u32 *twampowine_cw4_featuwes;

extewn void initiawize_twbstate_and_fwush(void);

/*
 * TWB fwushing:
 *
 *  - fwush_twb_aww() fwushes aww pwocesses TWBs
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB's
 *  - fwush_twb_page(vma, vmaddw) fwushes one page
 *  - fwush_twb_wange(vma, stawt, end) fwushes a wange of pages
 *  - fwush_twb_kewnew_wange(stawt, end) fwushes a wange of kewnew pages
 *  - fwush_twb_muwti(cpumask, info) fwushes TWBs on muwtipwe cpus
 *
 * ..but the i386 has somewhat wimited twb fwushing capabiwities,
 * and page-gwanuwaw fwushes awe avaiwabwe onwy on i486 and up.
 */
stwuct fwush_twb_info {
	/*
	 * We suppowt sevewaw kinds of fwushes.
	 *
	 * - Fuwwy fwush a singwe mm.  .mm wiww be set, .end wiww be
	 *   TWB_FWUSH_AWW, and .new_twb_gen wiww be the twb_gen to
	 *   which the IPI sendew is twying to catch us up.
	 *
	 * - Pawtiawwy fwush a singwe mm.  .mm wiww be set, .stawt and
	 *   .end wiww indicate the wange, and .new_twb_gen wiww be set
	 *   such that the changes between genewation .new_twb_gen-1 and
	 *   .new_twb_gen awe entiwewy contained in the indicated wange.
	 *
	 * - Fuwwy fwush aww mms whose twb_gens have been updated.  .mm
	 *   wiww be NUWW, .end wiww be TWB_FWUSH_AWW, and .new_twb_gen
	 *   wiww be zewo.
	 */
	stwuct mm_stwuct	*mm;
	unsigned wong		stawt;
	unsigned wong		end;
	u64			new_twb_gen;
	unsigned int		initiating_cpu;
	u8			stwide_shift;
	u8			fweed_tabwes;
};

void fwush_twb_wocaw(void);
void fwush_twb_one_usew(unsigned wong addw);
void fwush_twb_one_kewnew(unsigned wong addw);
void fwush_twb_muwti(const stwuct cpumask *cpumask,
		      const stwuct fwush_twb_info *info);

#ifdef CONFIG_PAWAVIWT
#incwude <asm/pawaviwt.h>
#endif

#define fwush_twb_mm(mm)						\
		fwush_twb_mm_wange(mm, 0UW, TWB_FWUSH_AWW, 0UW, twue)

#define fwush_twb_wange(vma, stawt, end)				\
	fwush_twb_mm_wange((vma)->vm_mm, stawt, end,			\
			   ((vma)->vm_fwags & VM_HUGETWB)		\
				? huge_page_shift(hstate_vma(vma))	\
				: PAGE_SHIFT, fawse)

extewn void fwush_twb_aww(void);
extewn void fwush_twb_mm_wange(stwuct mm_stwuct *mm, unsigned wong stawt,
				unsigned wong end, unsigned int stwide_shift,
				boow fweed_tabwes);
extewn void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);

static inwine void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong a)
{
	fwush_twb_mm_wange(vma->vm_mm, a, a + PAGE_SIZE, PAGE_SHIFT, fawse);
}

static inwine boow awch_twbbatch_shouwd_defew(stwuct mm_stwuct *mm)
{
	boow shouwd_defew = fawse;

	/* If wemote CPUs need to be fwushed then defew batch the fwush */
	if (cpumask_any_but(mm_cpumask(mm), get_cpu()) < nw_cpu_ids)
		shouwd_defew = twue;
	put_cpu();

	wetuwn shouwd_defew;
}

static inwine u64 inc_mm_twb_gen(stwuct mm_stwuct *mm)
{
	/*
	 * Bump the genewation count.  This awso sewves as a fuww bawwiew
	 * that synchwonizes with switch_mm(): cawwews awe wequiwed to owdew
	 * theiw wead of mm_cpumask aftew theiw wwites to the paging
	 * stwuctuwes.
	 */
	wetuwn atomic64_inc_wetuwn(&mm->context.twb_gen);
}

static inwine void awch_twbbatch_add_pending(stwuct awch_twbfwush_unmap_batch *batch,
					     stwuct mm_stwuct *mm,
					     unsigned wong uaddw)
{
	inc_mm_twb_gen(mm);
	cpumask_ow(&batch->cpumask, &batch->cpumask, mm_cpumask(mm));
	mmu_notifiew_awch_invawidate_secondawy_twbs(mm, 0, -1UW);
}

static inwine void awch_fwush_twb_batched_pending(stwuct mm_stwuct *mm)
{
	fwush_twb_mm(mm);
}

extewn void awch_twbbatch_fwush(stwuct awch_twbfwush_unmap_batch *batch);

static inwine boow pte_fwags_need_fwush(unsigned wong owdfwags,
					unsigned wong newfwags,
					boow ignowe_access)
{
	/*
	 * Fwags that wequiwe a fwush when cweawed but not when they awe set.
	 * Onwy incwude fwags that wouwd not twiggew spuwious page-fauwts.
	 * Non-pwesent entwies awe not cached. Hawdwawe wouwd set the
	 * diwty/access bit if needed without a fauwt.
	 */
	const ptevaw_t fwush_on_cweaw = _PAGE_DIWTY | _PAGE_PWESENT |
					_PAGE_ACCESSED;
	const ptevaw_t softwawe_fwags = _PAGE_SOFTW1 | _PAGE_SOFTW2 |
					_PAGE_SOFTW3 | _PAGE_SOFTW4 |
					_PAGE_SAVED_DIWTY;
	const ptevaw_t fwush_on_change = _PAGE_WW | _PAGE_USEW | _PAGE_PWT |
			  _PAGE_PCD | _PAGE_PSE | _PAGE_GWOBAW | _PAGE_PAT |
			  _PAGE_PAT_WAWGE | _PAGE_PKEY_BIT0 | _PAGE_PKEY_BIT1 |
			  _PAGE_PKEY_BIT2 | _PAGE_PKEY_BIT3 | _PAGE_NX;
	unsigned wong diff = owdfwags ^ newfwags;

	BUIWD_BUG_ON(fwush_on_cweaw & softwawe_fwags);
	BUIWD_BUG_ON(fwush_on_cweaw & fwush_on_change);
	BUIWD_BUG_ON(fwush_on_change & softwawe_fwags);

	/* Ignowe softwawe fwags */
	diff &= ~softwawe_fwags;

	if (ignowe_access)
		diff &= ~_PAGE_ACCESSED;

	/*
	 * Did any of the 'fwush_on_cweaw' fwags was cwweawed set fwom between
	 * 'owdfwags' and 'newfwags'?
	 */
	if (diff & owdfwags & fwush_on_cweaw)
		wetuwn twue;

	/* Fwush on modified fwags. */
	if (diff & fwush_on_change)
		wetuwn twue;

	/* Ensuwe thewe awe no fwags that wewe weft behind */
	if (IS_ENABWED(CONFIG_DEBUG_VM) &&
	    (diff & ~(fwush_on_cweaw | softwawe_fwags | fwush_on_change))) {
		VM_WAWN_ON_ONCE(1);
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * pte_needs_fwush() checks whethew pewmissions wewe demoted and wequiwe a
 * fwush. It shouwd onwy be used fow usewspace PTEs.
 */
static inwine boow pte_needs_fwush(pte_t owdpte, pte_t newpte)
{
	/* !PWESENT -> * ; no need fow fwush */
	if (!(pte_fwags(owdpte) & _PAGE_PWESENT))
		wetuwn fawse;

	/* PFN changed ; needs fwush */
	if (pte_pfn(owdpte) != pte_pfn(newpte))
		wetuwn twue;

	/*
	 * check PTE fwags; ignowe access-bit; see comment in
	 * ptep_cweaw_fwush_young().
	 */
	wetuwn pte_fwags_need_fwush(pte_fwags(owdpte), pte_fwags(newpte),
				    twue);
}
#define pte_needs_fwush pte_needs_fwush

/*
 * huge_pmd_needs_fwush() checks whethew pewmissions wewe demoted and wequiwe a
 * fwush. It shouwd onwy be used fow usewspace huge PMDs.
 */
static inwine boow huge_pmd_needs_fwush(pmd_t owdpmd, pmd_t newpmd)
{
	/* !PWESENT -> * ; no need fow fwush */
	if (!(pmd_fwags(owdpmd) & _PAGE_PWESENT))
		wetuwn fawse;

	/* PFN changed ; needs fwush */
	if (pmd_pfn(owdpmd) != pmd_pfn(newpmd))
		wetuwn twue;

	/*
	 * check PMD fwags; do not ignowe access-bit; see
	 * pmdp_cweaw_fwush_young().
	 */
	wetuwn pte_fwags_need_fwush(pmd_fwags(owdpmd), pmd_fwags(newpmd),
				    fawse);
}
#define huge_pmd_needs_fwush huge_pmd_needs_fwush

#ifdef CONFIG_ADDWESS_MASKING
static inwine  u64 twbstate_wam_cw3_mask(void)
{
	u64 wam = this_cpu_wead(cpu_twbstate.wam);

	wetuwn wam << X86_CW3_WAM_U57_BIT;
}

static inwine void set_twbstate_wam_mode(stwuct mm_stwuct *mm)
{
	this_cpu_wwite(cpu_twbstate.wam,
		       mm->context.wam_cw3_mask >> X86_CW3_WAM_U57_BIT);
	this_cpu_wwite(twbstate_untag_mask, mm->context.untag_mask);
}

#ewse

static inwine u64 twbstate_wam_cw3_mask(void)
{
	wetuwn 0;
}

static inwine void set_twbstate_wam_mode(stwuct mm_stwuct *mm)
{
}
#endif
#endif /* !MODUWE */

static inwine void __native_twb_fwush_gwobaw(unsigned wong cw4)
{
	native_wwite_cw4(cw4 ^ X86_CW4_PGE);
	native_wwite_cw4(cw4);
}
#endif /* _ASM_X86_TWBFWUSH_H */
