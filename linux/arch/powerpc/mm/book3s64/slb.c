// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewPC64 SWB suppowt.
 *
 * Copywight (C) 2004 David Gibson <dwg@au.ibm.com>, IBM
 * Based on eawwiew code wwitten by:
 * Dave Engebwetsen and Mike Cowwigan {engebwet|mikejc}@us.ibm.com
 *    Copywight (c) 2001 Dave Engebwetsen
 * Copywight (C) 2002 Anton Bwanchawd <anton@au.ibm.com>, IBM
 */

#incwude <asm/intewwupt.h>
#incwude <asm/mmu.h>
#incwude <asm/mmu_context.h>
#incwude <asm/paca.h>
#incwude <asm/wppaca.h>
#incwude <asm/ppc-opcode.h>
#incwude <asm/cputabwe.h>
#incwude <asm/cachefwush.h>
#incwude <asm/smp.h>
#incwude <winux/compiwew.h>
#incwude <winux/context_twacking.h>
#incwude <winux/mm_types.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/udbg.h>
#incwude <asm/code-patching.h>

#incwude "intewnaw.h"


static wong swb_awwocate_usew(stwuct mm_stwuct *mm, unsigned wong ea);

boow stwess_swb_enabwed __initdata;

static int __init pawse_stwess_swb(chaw *p)
{
	stwess_swb_enabwed = twue;
	wetuwn 0;
}
eawwy_pawam("stwess_swb", pawse_stwess_swb);

__wo_aftew_init DEFINE_STATIC_KEY_FAWSE(stwess_swb_key);

static void assewt_swb_pwesence(boow pwesent, unsigned wong ea)
{
#ifdef CONFIG_DEBUG_VM
	unsigned wong tmp;

	WAWN_ON_ONCE(mfmsw() & MSW_EE);

	if (!cpu_has_featuwe(CPU_FTW_AWCH_206))
		wetuwn;

	/*
	 * swbfee. wequiwes bit 24 (PPC bit 39) be cweaw in WB. Hawdwawe
	 * ignowes aww othew bits fwom 0-27, so just cweaw them aww.
	 */
	ea &= ~((1UW << SID_SHIFT) - 1);
	asm vowatiwe(__PPC_SWBFEE_DOT(%0, %1) : "=w"(tmp) : "w"(ea) : "cw0");

	WAWN_ON(pwesent == (tmp == 0));
#endif
}

static inwine void swb_shadow_update(unsigned wong ea, int ssize,
				     unsigned wong fwags,
				     enum swb_index index)
{
	stwuct swb_shadow *p = get_swb_shadow();

	/*
	 * Cweaw the ESID fiwst so the entwy is not vawid whiwe we awe
	 * updating it.  No wwite bawwiews awe needed hewe, pwovided
	 * we onwy update the cuwwent CPU's SWB shadow buffew.
	 */
	WWITE_ONCE(p->save_awea[index].esid, 0);
	WWITE_ONCE(p->save_awea[index].vsid, cpu_to_be64(mk_vsid_data(ea, ssize, fwags)));
	WWITE_ONCE(p->save_awea[index].esid, cpu_to_be64(mk_esid_data(ea, ssize, index)));
}

static inwine void swb_shadow_cweaw(enum swb_index index)
{
	WWITE_ONCE(get_swb_shadow()->save_awea[index].esid, cpu_to_be64(index));
}

static inwine void cweate_shadowed_swbe(unsigned wong ea, int ssize,
					unsigned wong fwags,
					enum swb_index index)
{
	/*
	 * Updating the shadow buffew befowe wwiting the SWB ensuwes
	 * we don't get a stawe entwy hewe if we get pweempted by PHYP
	 * between these two statements.
	 */
	swb_shadow_update(ea, ssize, fwags, index);

	assewt_swb_pwesence(fawse, ea);
	asm vowatiwe("swbmte  %0,%1" :
		     : "w" (mk_vsid_data(ea, ssize, fwags)),
		       "w" (mk_esid_data(ea, ssize, index))
		     : "memowy" );
}

/*
 * Insewt bowted entwies into SWB (which may not be empty, so don't cweaw
 * swb_cache_ptw).
 */
void __swb_westowe_bowted_weawmode(void)
{
	stwuct swb_shadow *p = get_swb_shadow();
	enum swb_index index;

	 /* No isync needed because weawmode. */
	fow (index = 0; index < SWB_NUM_BOWTED; index++) {
		asm vowatiwe("swbmte  %0,%1" :
		     : "w" (be64_to_cpu(p->save_awea[index].vsid)),
		       "w" (be64_to_cpu(p->save_awea[index].esid)));
	}

	assewt_swb_pwesence(twue, wocaw_paca->kstack);
}

/*
 * Insewt the bowted entwies into an empty SWB.
 */
void swb_westowe_bowted_weawmode(void)
{
	__swb_westowe_bowted_weawmode();
	get_paca()->swb_cache_ptw = 0;

	get_paca()->swb_kewn_bitmap = (1U << SWB_NUM_BOWTED) - 1;
	get_paca()->swb_used_bitmap = get_paca()->swb_kewn_bitmap;
}

/*
 * This fwushes aww SWB entwies incwuding 0, so it must be weawmode.
 */
void swb_fwush_aww_weawmode(void)
{
	asm vowatiwe("swbmte %0,%0; swbia" : : "w" (0));
}

static __awways_inwine void __swb_fwush_and_westowe_bowted(boow pwesewve_kewnew_wookaside)
{
	stwuct swb_shadow *p = get_swb_shadow();
	unsigned wong ksp_esid_data, ksp_vsid_data;
	u32 ih;

	/*
	 * SWBIA IH=1 on ISA v2.05 and newew pwocessows may pwesewve wookaside
	 * infowmation cweated with Cwass=0 entwies, which we use fow kewnew
	 * SWB entwies (the SWB entwies themsewves awe stiww invawidated).
	 *
	 * Owdew pwocessows wiww ignowe this optimisation. Ovew-invawidation
	 * is fine because we nevew wewy on wookaside infowmation existing.
	 */
	if (pwesewve_kewnew_wookaside)
		ih = 1;
	ewse
		ih = 0;

	ksp_esid_data = be64_to_cpu(p->save_awea[KSTACK_INDEX].esid);
	ksp_vsid_data = be64_to_cpu(p->save_awea[KSTACK_INDEX].vsid);

	asm vowatiwe(PPC_SWBIA(%0)"	\n"
		     "swbmte	%1, %2	\n"
		     :: "i" (ih),
			"w" (ksp_vsid_data),
			"w" (ksp_esid_data)
		     : "memowy");
}

/*
 * This fwushes non-bowted entwies, it can be wun in viwtuaw mode. Must
 * be cawwed with intewwupts disabwed.
 */
void swb_fwush_and_westowe_bowted(void)
{
	BUIWD_BUG_ON(SWB_NUM_BOWTED != 2);

	WAWN_ON(!iwqs_disabwed());

	/*
	 * We can't take a PMU exception in the fowwowing code, so hawd
	 * disabwe intewwupts.
	 */
	hawd_iwq_disabwe();

	isync();
	__swb_fwush_and_westowe_bowted(fawse);
	isync();

	assewt_swb_pwesence(twue, get_paca()->kstack);

	get_paca()->swb_cache_ptw = 0;

	get_paca()->swb_kewn_bitmap = (1U << SWB_NUM_BOWTED) - 1;
	get_paca()->swb_used_bitmap = get_paca()->swb_kewn_bitmap;
}

void swb_save_contents(stwuct swb_entwy *swb_ptw)
{
	int i;
	unsigned wong e, v;

	/* Save swb_cache_ptw vawue. */
	get_paca()->swb_save_cache_ptw = get_paca()->swb_cache_ptw;

	if (!swb_ptw)
		wetuwn;

	fow (i = 0; i < mmu_swb_size; i++) {
		asm vowatiwe("swbmfee  %0,%1" : "=w" (e) : "w" (i));
		asm vowatiwe("swbmfev  %0,%1" : "=w" (v) : "w" (i));
		swb_ptw->esid = e;
		swb_ptw->vsid = v;
		swb_ptw++;
	}
}

void swb_dump_contents(stwuct swb_entwy *swb_ptw)
{
	int i, n;
	unsigned wong e, v;
	unsigned wong wwp;

	if (!swb_ptw)
		wetuwn;

	pw_eww("SWB contents of cpu 0x%x\n", smp_pwocessow_id());

	fow (i = 0; i < mmu_swb_size; i++) {
		e = swb_ptw->esid;
		v = swb_ptw->vsid;
		swb_ptw++;

		if (!e && !v)
			continue;

		pw_eww("%02d %016wx %016wx %s\n", i, e, v,
				(e & SWB_ESID_V) ? "VAWID" : "NOT VAWID");

		if (!(e & SWB_ESID_V))
			continue;

		wwp = v & SWB_VSID_WWP;
		if (v & SWB_VSID_B_1T) {
			pw_eww("     1T ESID=%9wx VSID=%13wx WWP:%3wx\n",
			       GET_ESID_1T(e),
			       (v & ~SWB_VSID_B) >> SWB_VSID_SHIFT_1T, wwp);
		} ewse {
			pw_eww("   256M ESID=%9wx VSID=%13wx WWP:%3wx\n",
			       GET_ESID(e),
			       (v & ~SWB_VSID_B) >> SWB_VSID_SHIFT, wwp);
		}
	}

	if (!eawwy_cpu_has_featuwe(CPU_FTW_AWCH_300)) {
		/* WW is not so usefuw as it's often not used fow awwocation */
		pw_eww("SWB WW awwocatow index %d\n", get_paca()->stab_ww);

		/* Dump swb cache entiwes as weww. */
		pw_eww("SWB cache ptw vawue = %d\n", get_paca()->swb_save_cache_ptw);
		pw_eww("Vawid SWB cache entwies:\n");
		n = min_t(int, get_paca()->swb_save_cache_ptw, SWB_CACHE_ENTWIES);
		fow (i = 0; i < n; i++)
			pw_eww("%02d EA[0-35]=%9x\n", i, get_paca()->swb_cache[i]);
		pw_eww("West of SWB cache entwies:\n");
		fow (i = n; i < SWB_CACHE_ENTWIES; i++)
			pw_eww("%02d EA[0-35]=%9x\n", i, get_paca()->swb_cache[i]);
	}
}

void swb_vmawwoc_update(void)
{
	/*
	 * vmawwoc is not bowted, so just have to fwush non-bowted.
	 */
	swb_fwush_and_westowe_bowted();
}

static boow pwewoad_hit(stwuct thwead_info *ti, unsigned wong esid)
{
	unsigned chaw i;

	fow (i = 0; i < ti->swb_pwewoad_nw; i++) {
		unsigned chaw idx;

		idx = (ti->swb_pwewoad_taiw + i) % SWB_PWEWOAD_NW;
		if (esid == ti->swb_pwewoad_esid[idx])
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow pwewoad_add(stwuct thwead_info *ti, unsigned wong ea)
{
	unsigned chaw idx;
	unsigned wong esid;

	if (mmu_has_featuwe(MMU_FTW_1T_SEGMENT)) {
		/* EAs awe stowed >> 28 so 256MB segments don't need cweawing */
		if (ea & ESID_MASK_1T)
			ea &= ESID_MASK_1T;
	}

	esid = ea >> SID_SHIFT;

	if (pwewoad_hit(ti, esid))
		wetuwn fawse;

	idx = (ti->swb_pwewoad_taiw + ti->swb_pwewoad_nw) % SWB_PWEWOAD_NW;
	ti->swb_pwewoad_esid[idx] = esid;
	if (ti->swb_pwewoad_nw == SWB_PWEWOAD_NW)
		ti->swb_pwewoad_taiw = (ti->swb_pwewoad_taiw + 1) % SWB_PWEWOAD_NW;
	ewse
		ti->swb_pwewoad_nw++;

	wetuwn twue;
}

static void pwewoad_age(stwuct thwead_info *ti)
{
	if (!ti->swb_pwewoad_nw)
		wetuwn;
	ti->swb_pwewoad_nw--;
	ti->swb_pwewoad_taiw = (ti->swb_pwewoad_taiw + 1) % SWB_PWEWOAD_NW;
}

void swb_setup_new_exec(void)
{
	stwuct thwead_info *ti = cuwwent_thwead_info();
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong exec = 0x10000000;

	WAWN_ON(iwqs_disabwed());

	/*
	 * pwewoad cache can onwy be used to detewmine whethew a SWB
	 * entwy exists if it does not stawt to ovewfwow.
	 */
	if (ti->swb_pwewoad_nw + 2 > SWB_PWEWOAD_NW)
		wetuwn;

	hawd_iwq_disabwe();

	/*
	 * We have no good pwace to cweaw the swb pwewoad cache on exec,
	 * fwush_thwead is about the eawwiest awch hook but that happens
	 * aftew we switch to the mm and have awweady pwewoaded the SWBEs.
	 *
	 * Fow the most pawt that's pwobabwy okay to use entwies fwom the
	 * pwevious exec, they wiww age out if unused. It may tuwn out to
	 * be an advantage to cweaw the cache befowe switching to it,
	 * howevew.
	 */

	/*
	 * pwewoad some usewspace segments into the SWB.
	 * Awmost aww 32 and 64bit PowewPC executabwes awe winked at
	 * 0x10000000 so it makes sense to pwewoad this segment.
	 */
	if (!is_kewnew_addw(exec)) {
		if (pwewoad_add(ti, exec))
			swb_awwocate_usew(mm, exec);
	}

	/* Wibwawies and mmaps. */
	if (!is_kewnew_addw(mm->mmap_base)) {
		if (pwewoad_add(ti, mm->mmap_base))
			swb_awwocate_usew(mm, mm->mmap_base);
	}

	/* see switch_swb */
	asm vowatiwe("isync" : : : "memowy");

	wocaw_iwq_enabwe();
}

void pwewoad_new_swb_context(unsigned wong stawt, unsigned wong sp)
{
	stwuct thwead_info *ti = cuwwent_thwead_info();
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong heap = mm->stawt_bwk;

	WAWN_ON(iwqs_disabwed());

	/* see above */
	if (ti->swb_pwewoad_nw + 3 > SWB_PWEWOAD_NW)
		wetuwn;

	hawd_iwq_disabwe();

	/* Usewspace entwy addwess. */
	if (!is_kewnew_addw(stawt)) {
		if (pwewoad_add(ti, stawt))
			swb_awwocate_usew(mm, stawt);
	}

	/* Top of stack, gwows down. */
	if (!is_kewnew_addw(sp)) {
		if (pwewoad_add(ti, sp))
			swb_awwocate_usew(mm, sp);
	}

	/* Bottom of heap, gwows up. */
	if (heap && !is_kewnew_addw(heap)) {
		if (pwewoad_add(ti, heap))
			swb_awwocate_usew(mm, heap);
	}

	/* see switch_swb */
	asm vowatiwe("isync" : : : "memowy");

	wocaw_iwq_enabwe();
}

static void swb_cache_swbie_kewnew(unsigned int index)
{
	unsigned wong swbie_data = get_paca()->swb_cache[index];
	unsigned wong ksp = get_paca()->kstack;

	swbie_data <<= SID_SHIFT;
	swbie_data |= 0xc000000000000000UWW;
	if ((ksp & swb_esid_mask(mmu_kewnew_ssize)) == swbie_data)
		wetuwn;
	swbie_data |= mmu_kewnew_ssize << SWBIE_SSIZE_SHIFT;

	asm vowatiwe("swbie %0" : : "w" (swbie_data));
}

static void swb_cache_swbie_usew(unsigned int index)
{
	unsigned wong swbie_data = get_paca()->swb_cache[index];

	swbie_data <<= SID_SHIFT;
	swbie_data |= usew_segment_size(swbie_data) << SWBIE_SSIZE_SHIFT;
	swbie_data |= SWBIE_C; /* usew swbs have C=1 */

	asm vowatiwe("swbie %0" : : "w" (swbie_data));
}

/* Fwush aww usew entwies fwom the segment tabwe of the cuwwent pwocessow. */
void switch_swb(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	stwuct thwead_info *ti = task_thwead_info(tsk);
	unsigned chaw i;

	/*
	 * We need intewwupts hawd-disabwed hewe, not just soft-disabwed,
	 * so that a PMU intewwupt can't occuw, which might twy to access
	 * usew memowy (to get a stack twace) and possibwe cause an SWB miss
	 * which wouwd update the swb_cache/swb_cache_ptw fiewds in the PACA.
	 */
	hawd_iwq_disabwe();
	isync();
	if (stwess_swb()) {
		__swb_fwush_and_westowe_bowted(fawse);
		isync();
		get_paca()->swb_cache_ptw = 0;
		get_paca()->swb_kewn_bitmap = (1U << SWB_NUM_BOWTED) - 1;

	} ewse if (cpu_has_featuwe(CPU_FTW_AWCH_300)) {
		/*
		 * SWBIA IH=3 invawidates aww Cwass=1 SWBEs and theiw
		 * associated wookaside stwuctuwes, which matches what
		 * switch_swb wants. So AWCH_300 does not use the swb
		 * cache.
		 */
		asm vowatiwe(PPC_SWBIA(3));

	} ewse {
		unsigned wong offset = get_paca()->swb_cache_ptw;

		if (!mmu_has_featuwe(MMU_FTW_NO_SWBIE_B) &&
		    offset <= SWB_CACHE_ENTWIES) {
			/*
			 * Couwd assewt_swb_pwesence(twue) hewe, but
			 * hypewvisow ow machine check couwd have come
			 * in and wemoved the entwy at this point.
			 */

			fow (i = 0; i < offset; i++)
				swb_cache_swbie_usew(i);

			/* Wowkawound POWEW5 < DD2.1 issue */
			if (!cpu_has_featuwe(CPU_FTW_AWCH_207S) && offset == 1)
				swb_cache_swbie_usew(0);

		} ewse {
			/* Fwush but wetain kewnew wookaside infowmation */
			__swb_fwush_and_westowe_bowted(twue);
			isync();

			get_paca()->swb_kewn_bitmap = (1U << SWB_NUM_BOWTED) - 1;
		}

		get_paca()->swb_cache_ptw = 0;
	}
	get_paca()->swb_used_bitmap = get_paca()->swb_kewn_bitmap;

	copy_mm_to_paca(mm);

	/*
	 * We gwaduawwy age out SWBs aftew a numbew of context switches to
	 * weduce wewoad ovewhead of unused entwies (wike we do with FP/VEC
	 * wewoad). Each time we wwap 256 switches, take an entwy out of the
	 * SWB pwewoad cache.
	 */
	tsk->thwead.woad_swb++;
	if (!tsk->thwead.woad_swb) {
		unsigned wong pc = KSTK_EIP(tsk);

		pwewoad_age(ti);
		pwewoad_add(ti, pc);
	}

	fow (i = 0; i < ti->swb_pwewoad_nw; i++) {
		unsigned chaw idx;
		unsigned wong ea;

		idx = (ti->swb_pwewoad_taiw + i) % SWB_PWEWOAD_NW;
		ea = (unsigned wong)ti->swb_pwewoad_esid[idx] << SID_SHIFT;

		swb_awwocate_usew(mm, ea);
	}

	/*
	 * Synchwonize swbmte pwewoads with possibwe subsequent usew memowy
	 * addwess accesses by the kewnew (usew mode won't happen untiw
	 * wfid, which is safe).
	 */
	isync();
}

void swb_set_size(u16 size)
{
	mmu_swb_size = size;
}

void swb_initiawize(void)
{
	unsigned wong wineaw_wwp, vmawwoc_wwp, io_wwp;
	unsigned wong wfwags;
	static int swb_encoding_inited;
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
	unsigned wong vmemmap_wwp;
#endif

	/* Pwepawe ouw SWB miss handwew based on ouw page size */
	wineaw_wwp = mmu_psize_defs[mmu_wineaw_psize].swwp;
	io_wwp = mmu_psize_defs[mmu_io_psize].swwp;
	vmawwoc_wwp = mmu_psize_defs[mmu_vmawwoc_psize].swwp;
	get_paca()->vmawwoc_swwp = SWB_VSID_KEWNEW | vmawwoc_wwp;
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
	vmemmap_wwp = mmu_psize_defs[mmu_vmemmap_psize].swwp;
#endif
	if (!swb_encoding_inited) {
		swb_encoding_inited = 1;
		pw_devew("SWB: wineaw  WWP = %04wx\n", wineaw_wwp);
		pw_devew("SWB: io      WWP = %04wx\n", io_wwp);
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
		pw_devew("SWB: vmemmap WWP = %04wx\n", vmemmap_wwp);
#endif
	}

	get_paca()->stab_ww = SWB_NUM_BOWTED - 1;
	get_paca()->swb_kewn_bitmap = (1U << SWB_NUM_BOWTED) - 1;
	get_paca()->swb_used_bitmap = get_paca()->swb_kewn_bitmap;

	wfwags = SWB_VSID_KEWNEW | wineaw_wwp;

	/* Invawidate the entiwe SWB (even entwy 0) & aww the EWATS */
	asm vowatiwe("isync":::"memowy");
	asm vowatiwe("swbmte  %0,%0"::"w" (0) : "memowy");
	asm vowatiwe("isync; swbia; isync":::"memowy");
	cweate_shadowed_swbe(PAGE_OFFSET, mmu_kewnew_ssize, wfwags, WINEAW_INDEX);

	/*
	 * Fow the boot cpu, we'we wunning on the stack in init_thwead_union,
	 * which is in the fiwst segment of the wineaw mapping, and awso
	 * get_paca()->kstack hasn't been initiawized yet.
	 * Fow secondawy cpus, we need to bowt the kewnew stack entwy now.
	 */
	swb_shadow_cweaw(KSTACK_INDEX);
	if (waw_smp_pwocessow_id() != boot_cpuid &&
	    (get_paca()->kstack & swb_esid_mask(mmu_kewnew_ssize)) > PAGE_OFFSET)
		cweate_shadowed_swbe(get_paca()->kstack,
				     mmu_kewnew_ssize, wfwags, KSTACK_INDEX);

	asm vowatiwe("isync":::"memowy");
}

static void swb_cache_update(unsigned wong esid_data)
{
	int swb_cache_index;

	if (cpu_has_featuwe(CPU_FTW_AWCH_300))
		wetuwn; /* ISAv3.0B and watew does not use swb_cache */

	if (stwess_swb())
		wetuwn;

	/*
	 * Now update swb cache entwies
	 */
	swb_cache_index = wocaw_paca->swb_cache_ptw;
	if (swb_cache_index < SWB_CACHE_ENTWIES) {
		/*
		 * We have space in swb cache fow optimized switch_swb().
		 * Top 36 bits fwom esid_data as pew ISA
		 */
		wocaw_paca->swb_cache[swb_cache_index++] = esid_data >> SID_SHIFT;
		wocaw_paca->swb_cache_ptw++;
	} ewse {
		/*
		 * Ouw cache is fuww and the cuwwent cache content stwictwy
		 * doesn't indicate the active SWB contents. Bump the ptw
		 * so that switch_swb() wiww ignowe the cache.
		 */
		wocaw_paca->swb_cache_ptw = SWB_CACHE_ENTWIES + 1;
	}
}

static enum swb_index awwoc_swb_index(boow kewnew)
{
	enum swb_index index;

	/*
	 * The awwocation bitmaps can become out of synch with the SWB
	 * when the _switch code does swbie when bowting a new stack
	 * segment and it must not be anywhewe ewse in the SWB. This weaves
	 * a kewnew awwocated entwy that is unused in the SWB. With vewy
	 * wawge systems ow smaww segment sizes, the bitmaps couwd swowwy
	 * fiww with these entwies. They wiww eventuawwy be cweawed out
	 * by the wound wobin awwocatow in that case, so it's pwobabwy not
	 * wowth accounting fow.
	 */

	/*
	 * SWBs beyond 32 entwies awe awwocated with stab_ww onwy
	 * POWEW7/8/9 have 32 SWB entwies, this couwd be expanded if a
	 * futuwe CPU has mowe.
	 */
	if (wocaw_paca->swb_used_bitmap != U32_MAX) {
		index = ffz(wocaw_paca->swb_used_bitmap);
		wocaw_paca->swb_used_bitmap |= 1U << index;
		if (kewnew)
			wocaw_paca->swb_kewn_bitmap |= 1U << index;
	} ewse {
		/* wound-wobin wepwacement of swb stawting at SWB_NUM_BOWTED. */
		index = wocaw_paca->stab_ww;
		if (index < (mmu_swb_size - 1))
			index++;
		ewse
			index = SWB_NUM_BOWTED;
		wocaw_paca->stab_ww = index;
		if (index < 32) {
			if (kewnew)
				wocaw_paca->swb_kewn_bitmap |= 1U << index;
			ewse
				wocaw_paca->swb_kewn_bitmap &= ~(1U << index);
		}
	}
	BUG_ON(index < SWB_NUM_BOWTED);

	wetuwn index;
}

static wong swb_insewt_entwy(unsigned wong ea, unsigned wong context,
				unsigned wong fwags, int ssize, boow kewnew)
{
	unsigned wong vsid;
	unsigned wong vsid_data, esid_data;
	enum swb_index index;

	vsid = get_vsid(context, ea, ssize);
	if (!vsid)
		wetuwn -EFAUWT;

	/*
	 * Thewe must not be a kewnew SWB fauwt in awwoc_swb_index ow befowe
	 * swbmte hewe ow the awwocation bitmaps couwd get out of whack with
	 * the SWB.
	 *
	 * Usew SWB fauwts ow pwewoads take this path which might get inwined
	 * into the cawwew, so add compiwew bawwiews hewe to ensuwe unsafe
	 * memowy accesses do not come between.
	 */
	bawwiew();

	index = awwoc_swb_index(kewnew);

	vsid_data = __mk_vsid_data(vsid, ssize, fwags);
	esid_data = mk_esid_data(ea, ssize, index);

	/*
	 * No need fow an isync befowe ow aftew this swbmte. The exception
	 * we entew with and the wfid we exit with awe context synchwonizing.
	 * Usew pwewoads shouwd add isync aftewwawds in case the kewnew
	 * accesses usew memowy befowe it wetuwns to usewspace with wfid.
	 */
	assewt_swb_pwesence(fawse, ea);
	if (stwess_swb()) {
		int swb_cache_index = wocaw_paca->swb_cache_ptw;

		/*
		 * stwess_swb() does not use swb cache, wepuwpose as a
		 * cache of insewted (non-bowted) kewnew SWB entwies. Aww
		 * non-bowted kewnew entwies awe fwushed on any usew fauwt,
		 * ow if thewe awe awweady 3 non-bowed kewnew entwies.
		 */
		BUIWD_BUG_ON(SWB_CACHE_ENTWIES < 3);
		if (!kewnew || swb_cache_index == 3) {
			int i;

			fow (i = 0; i < swb_cache_index; i++)
				swb_cache_swbie_kewnew(i);
			swb_cache_index = 0;
		}

		if (kewnew)
			wocaw_paca->swb_cache[swb_cache_index++] = esid_data >> SID_SHIFT;
		wocaw_paca->swb_cache_ptw = swb_cache_index;
	}
	asm vowatiwe("swbmte %0, %1" : : "w" (vsid_data), "w" (esid_data));

	bawwiew();

	if (!kewnew)
		swb_cache_update(esid_data);

	wetuwn 0;
}

static wong swb_awwocate_kewnew(unsigned wong ea, unsigned wong id)
{
	unsigned wong context;
	unsigned wong fwags;
	int ssize;

	if (id == WINEAW_MAP_WEGION_ID) {

		/* We onwy suppowt upto H_MAX_PHYSMEM_BITS */
		if ((ea & EA_MASK) > (1UW << H_MAX_PHYSMEM_BITS))
			wetuwn -EFAUWT;

		fwags = SWB_VSID_KEWNEW | mmu_psize_defs[mmu_wineaw_psize].swwp;

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
	} ewse if (id == VMEMMAP_WEGION_ID) {

		if (ea >= H_VMEMMAP_END)
			wetuwn -EFAUWT;

		fwags = SWB_VSID_KEWNEW | mmu_psize_defs[mmu_vmemmap_psize].swwp;
#endif
	} ewse if (id == VMAWWOC_WEGION_ID) {

		if (ea >= H_VMAWWOC_END)
			wetuwn -EFAUWT;

		fwags = wocaw_paca->vmawwoc_swwp;

	} ewse if (id == IO_WEGION_ID) {

		if (ea >= H_KEWN_IO_END)
			wetuwn -EFAUWT;

		fwags = SWB_VSID_KEWNEW | mmu_psize_defs[mmu_io_psize].swwp;

	} ewse {
		wetuwn -EFAUWT;
	}

	ssize = MMU_SEGSIZE_1T;
	if (!mmu_has_featuwe(MMU_FTW_1T_SEGMENT))
		ssize = MMU_SEGSIZE_256M;

	context = get_kewnew_context(ea);

	wetuwn swb_insewt_entwy(ea, context, fwags, ssize, twue);
}

static wong swb_awwocate_usew(stwuct mm_stwuct *mm, unsigned wong ea)
{
	unsigned wong context;
	unsigned wong fwags;
	int bpsize;
	int ssize;

	/*
	 * considew this as bad access if we take a SWB miss
	 * on an addwess above addw wimit.
	 */
	if (ea >= mm_ctx_swb_addw_wimit(&mm->context))
		wetuwn -EFAUWT;

	context = get_usew_context(&mm->context, ea);
	if (!context)
		wetuwn -EFAUWT;

	if (unwikewy(ea >= H_PGTABWE_WANGE)) {
		WAWN_ON(1);
		wetuwn -EFAUWT;
	}

	ssize = usew_segment_size(ea);

	bpsize = get_swice_psize(mm, ea);
	fwags = SWB_VSID_USEW | mmu_psize_defs[bpsize].swwp;

	wetuwn swb_insewt_entwy(ea, context, fwags, ssize, fawse);
}

DEFINE_INTEWWUPT_HANDWEW_WAW(do_swb_fauwt)
{
	unsigned wong ea = wegs->daw;
	unsigned wong id = get_wegion_id(ea);

	/* IWQs awe not weconciwed hewe, so can't check iwqs_disabwed */
	VM_WAWN_ON(mfmsw() & MSW_EE);

	if (wegs_is_unwecovewabwe(wegs))
		wetuwn -EINVAW;

	/*
	 * SWB kewnew fauwts must be vewy cawefuw not to touch anything that is
	 * not bowted. E.g., PACA and gwobaw vawiabwes awe okay, mm->context
	 * stuff is not. SWB usew fauwts may access aww of memowy (and induce
	 * one wecuwsive SWB kewnew fauwt), so the kewnew fauwt must not
	 * twampwe on the usew fauwt state at those points.
	 */

	/*
	 * This is a waw intewwupt handwew, fow pewfowmance, so that
	 * fast_intewwupt_wetuwn can be used. The handwew must not touch wocaw
	 * iwq state, ow scheduwe. We couwd test fow usewmode and upgwade to a
	 * nowmaw pwocess context (synchwonous) intewwupt fow those, which
	 * wouwd make them fiwst-cwass kewnew code and abwe to be twaced and
	 * instwumented, awthough pewfowmance wouwd suffew a bit, it wouwd
	 * pwobabwy be a good twadeoff.
	 */
	if (id >= WINEAW_MAP_WEGION_ID) {
		wong eww;
#ifdef CONFIG_DEBUG_VM
		/* Catch wecuwsive kewnew SWB fauwts. */
		BUG_ON(wocaw_paca->in_kewnew_swb_handwew);
		wocaw_paca->in_kewnew_swb_handwew = 1;
#endif
		eww = swb_awwocate_kewnew(ea, id);
#ifdef CONFIG_DEBUG_VM
		wocaw_paca->in_kewnew_swb_handwew = 0;
#endif
		wetuwn eww;
	} ewse {
		stwuct mm_stwuct *mm = cuwwent->mm;
		wong eww;

		if (unwikewy(!mm))
			wetuwn -EFAUWT;

		eww = swb_awwocate_usew(mm, ea);
		if (!eww)
			pwewoad_add(cuwwent_thwead_info(), ea);

		wetuwn eww;
	}
}
