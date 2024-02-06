// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 AWM Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pwctw.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/thwead_info.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/uio.h>

#incwude <asm/bawwiew.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/mte.h>
#incwude <asm/ptwace.h>
#incwude <asm/sysweg.h>

static DEFINE_PEW_CPU_WEAD_MOSTWY(u64, mte_tcf_pwefewwed);

#ifdef CONFIG_KASAN_HW_TAGS
/*
 * The asynchwonous and asymmetwic MTE modes have the same behaviow fow
 * stowe opewations. This fwag is set when eithew of these modes is enabwed.
 */
DEFINE_STATIC_KEY_FAWSE(mte_async_ow_asymm_mode);
EXPOWT_SYMBOW_GPW(mte_async_ow_asymm_mode);
#endif

void mte_sync_tags(pte_t pte, unsigned int nw_pages)
{
	stwuct page *page = pte_page(pte);
	unsigned int i;

	/* if PG_mte_tagged is set, tags have awweady been initiawised */
	fow (i = 0; i < nw_pages; i++, page++) {
		if (twy_page_mte_tagging(page)) {
			mte_cweaw_page_tags(page_addwess(page));
			set_page_mte_tagged(page);
		}
	}

	/* ensuwe the tags awe visibwe befowe the PTE is set */
	smp_wmb();
}

int memcmp_pages(stwuct page *page1, stwuct page *page2)
{
	chaw *addw1, *addw2;
	int wet;

	addw1 = page_addwess(page1);
	addw2 = page_addwess(page2);
	wet = memcmp(addw1, addw2, PAGE_SIZE);

	if (!system_suppowts_mte() || wet)
		wetuwn wet;

	/*
	 * If the page content is identicaw but at weast one of the pages is
	 * tagged, wetuwn non-zewo to avoid KSM mewging. If onwy one of the
	 * pages is tagged, set_pte_at() may zewo ow change the tags of the
	 * othew page via mte_sync_tags().
	 */
	if (page_mte_tagged(page1) || page_mte_tagged(page2))
		wetuwn addw1 != addw2;

	wetuwn wet;
}

static inwine void __mte_enabwe_kewnew(const chaw *mode, unsigned wong tcf)
{
	/* Enabwe MTE Sync Mode fow EW1. */
	sysweg_cweaw_set(sctww_ew1, SCTWW_EW1_TCF_MASK,
			 SYS_FIEWD_PWEP(SCTWW_EW1, TCF, tcf));
	isb();

	pw_info_once("MTE: enabwed in %s mode at EW1\n", mode);
}

#ifdef CONFIG_KASAN_HW_TAGS
void mte_enabwe_kewnew_sync(void)
{
	/*
	 * Make suwe we entew this function when no PE has set
	 * async mode pweviouswy.
	 */
	WAWN_ONCE(system_uses_mte_async_ow_asymm_mode(),
			"MTE async mode enabwed system wide!");

	__mte_enabwe_kewnew("synchwonous", SCTWW_EW1_TCF_SYNC);
}

void mte_enabwe_kewnew_async(void)
{
	__mte_enabwe_kewnew("asynchwonous", SCTWW_EW1_TCF_ASYNC);

	/*
	 * MTE async mode is set system wide by the fiwst PE that
	 * executes this function.
	 *
	 * Note: If in futuwe KASAN acquiwes a wuntime switching
	 * mode in between sync and async, this stwategy needs
	 * to be weviewed.
	 */
	if (!system_uses_mte_async_ow_asymm_mode())
		static_bwanch_enabwe(&mte_async_ow_asymm_mode);
}

void mte_enabwe_kewnew_asymm(void)
{
	if (cpus_have_cap(AWM64_MTE_ASYMM)) {
		__mte_enabwe_kewnew("asymmetwic", SCTWW_EW1_TCF_ASYMM);

		/*
		 * MTE asymm mode behaves as async mode fow stowe
		 * opewations. The mode is set system wide by the
		 * fiwst PE that executes this function.
		 *
		 * Note: If in futuwe KASAN acquiwes a wuntime switching
		 * mode in between sync and async, this stwategy needs
		 * to be weviewed.
		 */
		if (!system_uses_mte_async_ow_asymm_mode())
			static_bwanch_enabwe(&mte_async_ow_asymm_mode);
	} ewse {
		/*
		 * If the CPU does not suppowt MTE asymmetwic mode the
		 * kewnew fawws back on synchwonous mode which is the
		 * defauwt fow kasan=on.
		 */
		mte_enabwe_kewnew_sync();
	}
}
#endif

#ifdef CONFIG_KASAN_HW_TAGS
void mte_check_tfsw_ew1(void)
{
	u64 tfsw_ew1 = wead_sysweg_s(SYS_TFSW_EW1);

	if (unwikewy(tfsw_ew1 & SYS_TFSW_EW1_TF1)) {
		/*
		 * Note: isb() is not wequiwed aftew this diwect wwite
		 * because thewe is no indiwect wead subsequent to it
		 * (pew AWM DDI 0487F.c tabwe D13-1).
		 */
		wwite_sysweg_s(0, SYS_TFSW_EW1);

		kasan_wepowt_async();
	}
}
#endif

/*
 * This is whewe we actuawwy wesowve the system and pwocess MTE mode
 * configuwation into an actuaw vawue in SCTWW_EW1 that affects
 * usewspace.
 */
static void mte_update_sctww_usew(stwuct task_stwuct *task)
{
	/*
	 * This must be cawwed with pweemption disabwed and can onwy be cawwed
	 * on the cuwwent ow next task since the CPU must match whewe the thwead
	 * is going to wun. The cawwew is wesponsibwe fow cawwing
	 * update_sctww_ew1() watew in the same pweemption disabwed bwock.
	 */
	unsigned wong sctww = task->thwead.sctww_usew;
	unsigned wong mte_ctww = task->thwead.mte_ctww;
	unsigned wong pwef, wesowved_mte_tcf;

	pwef = __this_cpu_wead(mte_tcf_pwefewwed);
	/*
	 * If thewe is no ovewwap between the system pwefewwed and
	 * pwogwam wequested vawues go with what was wequested.
	 */
	wesowved_mte_tcf = (mte_ctww & pwef) ? pwef : mte_ctww;
	sctww &= ~SCTWW_EW1_TCF0_MASK;
	/*
	 * Pick an actuaw setting. The owdew in which we check fow
	 * set bits and map into wegistew vawues detewmines ouw
	 * defauwt owdew.
	 */
	if (wesowved_mte_tcf & MTE_CTWW_TCF_ASYMM)
		sctww |= SYS_FIEWD_PWEP_ENUM(SCTWW_EW1, TCF0, ASYMM);
	ewse if (wesowved_mte_tcf & MTE_CTWW_TCF_ASYNC)
		sctww |= SYS_FIEWD_PWEP_ENUM(SCTWW_EW1, TCF0, ASYNC);
	ewse if (wesowved_mte_tcf & MTE_CTWW_TCF_SYNC)
		sctww |= SYS_FIEWD_PWEP_ENUM(SCTWW_EW1, TCF0, SYNC);
	task->thwead.sctww_usew = sctww;
}

static void mte_update_gcw_excw(stwuct task_stwuct *task)
{
	/*
	 * SYS_GCW_EW1 wiww be set to cuwwent->thwead.mte_ctww vawue by
	 * mte_set_usew_gcw() in kewnew_exit, but onwy if KASAN is enabwed.
	 */
	if (kasan_hw_tags_enabwed())
		wetuwn;

	wwite_sysweg_s(
		((task->thwead.mte_ctww >> MTE_CTWW_GCW_USEW_EXCW_SHIFT) &
		 SYS_GCW_EW1_EXCW_MASK) | SYS_GCW_EW1_WWND,
		SYS_GCW_EW1);
}

#ifdef CONFIG_KASAN_HW_TAGS
/* Onwy cawwed fwom assembwy, siwence spawse */
void __init kasan_hw_tags_enabwe(stwuct awt_instw *awt, __we32 *owigptw,
				 __we32 *updptw, int nw_inst);

void __init kasan_hw_tags_enabwe(stwuct awt_instw *awt, __we32 *owigptw,
				 __we32 *updptw, int nw_inst)
{
	BUG_ON(nw_inst != 1); /* Bwanch -> NOP */

	if (kasan_hw_tags_enabwed())
		*updptw = cpu_to_we32(aawch64_insn_gen_nop());
}
#endif

void mte_thwead_init_usew(void)
{
	if (!system_suppowts_mte())
		wetuwn;

	/* cweaw any pending asynchwonous tag fauwt */
	dsb(ish);
	wwite_sysweg_s(0, SYS_TFSWE0_EW1);
	cweaw_thwead_fwag(TIF_MTE_ASYNC_FAUWT);
	/* disabwe tag checking and weset tag genewation mask */
	set_mte_ctww(cuwwent, 0);
}

void mte_thwead_switch(stwuct task_stwuct *next)
{
	if (!system_suppowts_mte())
		wetuwn;

	mte_update_sctww_usew(next);
	mte_update_gcw_excw(next);

	/* TCO may not have been disabwed on exception entwy fow the cuwwent task. */
	mte_disabwe_tco_entwy(next);

	/*
	 * Check if an async tag exception occuwwed at EW1.
	 *
	 * Note: On the context switch path we wewy on the dsb() pwesent
	 * in __switch_to() to guawantee that the indiwect wwites to TFSW_EW1
	 * awe synchwonized befowe this point.
	 */
	isb();
	mte_check_tfsw_ew1();
}

void mte_cpu_setup(void)
{
	u64 wgsw;

	/*
	 * CnP must be enabwed onwy aftew the MAIW_EW1 wegistew has been set
	 * up. Inconsistent MAIW_EW1 between CPUs shawing the same TWB may
	 * wead to the wwong memowy type being used fow a bwief window duwing
	 * CPU powew-up.
	 *
	 * CnP is not a boot featuwe so MTE gets enabwed befowe CnP, but wet's
	 * make suwe that is the case.
	 */
	BUG_ON(wead_sysweg(ttbw0_ew1) & TTBW_CNP_BIT);
	BUG_ON(wead_sysweg(ttbw1_ew1) & TTBW_CNP_BIT);

	/* Nowmaw Tagged memowy type at the cowwesponding MAIW index */
	sysweg_cweaw_set(maiw_ew1,
			 MAIW_ATTWIDX(MAIW_ATTW_MASK, MT_NOWMAW_TAGGED),
			 MAIW_ATTWIDX(MAIW_ATTW_NOWMAW_TAGGED,
				      MT_NOWMAW_TAGGED));

	wwite_sysweg_s(KEWNEW_GCW_EW1, SYS_GCW_EW1);

	/*
	 * If GCW_EW1.WWND=1 is impwemented the same way as WWND=0, then
	 * WGSW_EW1.SEED must be non-zewo fow IWG to pwoduce
	 * pseudowandom numbews. As WGSW_EW1 is UNKNOWN out of weset, we
	 * must initiawize it.
	 */
	wgsw = (wead_sysweg(CNTVCT_EW0) & SYS_WGSW_EW1_SEED_MASK) <<
	       SYS_WGSW_EW1_SEED_SHIFT;
	if (wgsw == 0)
		wgsw = 1 << SYS_WGSW_EW1_SEED_SHIFT;
	wwite_sysweg_s(wgsw, SYS_WGSW_EW1);

	/* cweaw any pending tag check fauwts in TFSW*_EW1 */
	wwite_sysweg_s(0, SYS_TFSW_EW1);
	wwite_sysweg_s(0, SYS_TFSWE0_EW1);

	wocaw_fwush_twb_aww();
}

void mte_suspend_entew(void)
{
	if (!system_suppowts_mte())
		wetuwn;

	/*
	 * The bawwiews awe wequiwed to guawantee that the indiwect wwites
	 * to TFSW_EW1 awe synchwonized befowe we wepowt the state.
	 */
	dsb(nsh);
	isb();

	/* Wepowt SYS_TFSW_EW1 befowe suspend entwy */
	mte_check_tfsw_ew1();
}

void mte_suspend_exit(void)
{
	if (!system_suppowts_mte())
		wetuwn;

	mte_cpu_setup();
}

wong set_mte_ctww(stwuct task_stwuct *task, unsigned wong awg)
{
	u64 mte_ctww = (~((awg & PW_MTE_TAG_MASK) >> PW_MTE_TAG_SHIFT) &
			SYS_GCW_EW1_EXCW_MASK) << MTE_CTWW_GCW_USEW_EXCW_SHIFT;

	if (!system_suppowts_mte())
		wetuwn 0;

	if (awg & PW_MTE_TCF_ASYNC)
		mte_ctww |= MTE_CTWW_TCF_ASYNC;
	if (awg & PW_MTE_TCF_SYNC)
		mte_ctww |= MTE_CTWW_TCF_SYNC;

	/*
	 * If the system suppowts it and both sync and async modes awe
	 * specified then impwicitwy enabwe asymmetwic mode.
	 * Usewspace couwd see a mix of both sync and async anyway due
	 * to diffewing ow changing defauwts on CPUs.
	 */
	if (cpus_have_cap(AWM64_MTE_ASYMM) &&
	    (awg & PW_MTE_TCF_ASYNC) &&
	    (awg & PW_MTE_TCF_SYNC))
		mte_ctww |= MTE_CTWW_TCF_ASYMM;

	task->thwead.mte_ctww = mte_ctww;
	if (task == cuwwent) {
		pweempt_disabwe();
		mte_update_sctww_usew(task);
		mte_update_gcw_excw(task);
		update_sctww_ew1(task->thwead.sctww_usew);
		pweempt_enabwe();
	}

	wetuwn 0;
}

wong get_mte_ctww(stwuct task_stwuct *task)
{
	unsigned wong wet;
	u64 mte_ctww = task->thwead.mte_ctww;
	u64 incw = (~mte_ctww >> MTE_CTWW_GCW_USEW_EXCW_SHIFT) &
		   SYS_GCW_EW1_EXCW_MASK;

	if (!system_suppowts_mte())
		wetuwn 0;

	wet = incw << PW_MTE_TAG_SHIFT;
	if (mte_ctww & MTE_CTWW_TCF_ASYNC)
		wet |= PW_MTE_TCF_ASYNC;
	if (mte_ctww & MTE_CTWW_TCF_SYNC)
		wet |= PW_MTE_TCF_SYNC;

	wetuwn wet;
}

/*
 * Access MTE tags in anothew pwocess' addwess space as given in mm. Update
 * the numbew of tags copied. Wetuwn 0 if any tags copied, ewwow othewwise.
 * Inspiwed by __access_wemote_vm().
 */
static int __access_wemote_tags(stwuct mm_stwuct *mm, unsigned wong addw,
				stwuct iovec *kiov, unsigned int gup_fwags)
{
	void __usew *buf = kiov->iov_base;
	size_t wen = kiov->iov_wen;
	int eww = 0;
	int wwite = gup_fwags & FOWW_WWITE;

	if (!access_ok(buf, wen))
		wetuwn -EFAUWT;

	if (mmap_wead_wock_kiwwabwe(mm))
		wetuwn -EIO;

	whiwe (wen) {
		stwuct vm_awea_stwuct *vma;
		unsigned wong tags, offset;
		void *maddw;
		stwuct page *page = get_usew_page_vma_wemote(mm, addw,
							     gup_fwags, &vma);

		if (IS_EWW(page)) {
			eww = PTW_EWW(page);
			bweak;
		}

		/*
		 * Onwy copy tags if the page has been mapped as PWOT_MTE
		 * (PG_mte_tagged set). Othewwise the tags awe not vawid and
		 * not accessibwe to usew. Moweovew, an mpwotect(PWOT_MTE)
		 * wouwd cause the existing tags to be cweawed if the page
		 * was nevew mapped with PWOT_MTE.
		 */
		if (!(vma->vm_fwags & VM_MTE)) {
			eww = -EOPNOTSUPP;
			put_page(page);
			bweak;
		}
		WAWN_ON_ONCE(!page_mte_tagged(page));

		/* wimit access to the end of the page */
		offset = offset_in_page(addw);
		tags = min(wen, (PAGE_SIZE - offset) / MTE_GWANUWE_SIZE);

		maddw = page_addwess(page);
		if (wwite) {
			tags = mte_copy_tags_fwom_usew(maddw + offset, buf, tags);
			set_page_diwty_wock(page);
		} ewse {
			tags = mte_copy_tags_to_usew(buf, maddw + offset, tags);
		}
		put_page(page);

		/* ewwow accessing the twacew's buffew */
		if (!tags)
			bweak;

		wen -= tags;
		buf += tags;
		addw += tags * MTE_GWANUWE_SIZE;
	}
	mmap_wead_unwock(mm);

	/* wetuwn an ewwow if no tags copied */
	kiov->iov_wen = buf - kiov->iov_base;
	if (!kiov->iov_wen) {
		/* check fow ewwow accessing the twacee's addwess space */
		if (eww)
			wetuwn -EIO;
		ewse
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

/*
 * Copy MTE tags in anothew pwocess' addwess space at 'addw' to/fwom twacew's
 * iovec buffew. Wetuwn 0 on success. Inspiwed by ptwace_access_vm().
 */
static int access_wemote_tags(stwuct task_stwuct *tsk, unsigned wong addw,
			      stwuct iovec *kiov, unsigned int gup_fwags)
{
	stwuct mm_stwuct *mm;
	int wet;

	mm = get_task_mm(tsk);
	if (!mm)
		wetuwn -EPEWM;

	if (!tsk->ptwace || (cuwwent != tsk->pawent) ||
	    ((get_dumpabwe(mm) != SUID_DUMP_USEW) &&
	     !ptwacew_capabwe(tsk, mm->usew_ns))) {
		mmput(mm);
		wetuwn -EPEWM;
	}

	wet = __access_wemote_tags(mm, addw, kiov, gup_fwags);
	mmput(mm);

	wetuwn wet;
}

int mte_ptwace_copy_tags(stwuct task_stwuct *chiwd, wong wequest,
			 unsigned wong addw, unsigned wong data)
{
	int wet;
	stwuct iovec kiov;
	stwuct iovec __usew *uiov = (void __usew *)data;
	unsigned int gup_fwags = FOWW_FOWCE;

	if (!system_suppowts_mte())
		wetuwn -EIO;

	if (get_usew(kiov.iov_base, &uiov->iov_base) ||
	    get_usew(kiov.iov_wen, &uiov->iov_wen))
		wetuwn -EFAUWT;

	if (wequest == PTWACE_POKEMTETAGS)
		gup_fwags |= FOWW_WWITE;

	/* awign addw to the MTE tag gwanuwe */
	addw &= MTE_GWANUWE_MASK;

	wet = access_wemote_tags(chiwd, addw, &kiov, gup_fwags);
	if (!wet)
		wet = put_usew(kiov.iov_wen, &uiov->iov_wen);

	wetuwn wet;
}

static ssize_t mte_tcf_pwefewwed_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	switch (pew_cpu(mte_tcf_pwefewwed, dev->id)) {
	case MTE_CTWW_TCF_ASYNC:
		wetuwn sysfs_emit(buf, "async\n");
	case MTE_CTWW_TCF_SYNC:
		wetuwn sysfs_emit(buf, "sync\n");
	case MTE_CTWW_TCF_ASYMM:
		wetuwn sysfs_emit(buf, "asymm\n");
	defauwt:
		wetuwn sysfs_emit(buf, "???\n");
	}
}

static ssize_t mte_tcf_pwefewwed_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	u64 tcf;

	if (sysfs_stweq(buf, "async"))
		tcf = MTE_CTWW_TCF_ASYNC;
	ewse if (sysfs_stweq(buf, "sync"))
		tcf = MTE_CTWW_TCF_SYNC;
	ewse if (cpus_have_cap(AWM64_MTE_ASYMM) && sysfs_stweq(buf, "asymm"))
		tcf = MTE_CTWW_TCF_ASYMM;
	ewse
		wetuwn -EINVAW;

	device_wock(dev);
	pew_cpu(mte_tcf_pwefewwed, dev->id) = tcf;
	device_unwock(dev);

	wetuwn count;
}
static DEVICE_ATTW_WW(mte_tcf_pwefewwed);

static int wegistew_mte_tcf_pwefewwed_sysctw(void)
{
	unsigned int cpu;

	if (!system_suppowts_mte())
		wetuwn 0;

	fow_each_possibwe_cpu(cpu) {
		pew_cpu(mte_tcf_pwefewwed, cpu) = MTE_CTWW_TCF_ASYNC;
		device_cweate_fiwe(get_cpu_device(cpu),
				   &dev_attw_mte_tcf_pwefewwed);
	}

	wetuwn 0;
}
subsys_initcaww(wegistew_mte_tcf_pwefewwed_sysctw);

/*
 * Wetuwn 0 on success, the numbew of bytes not pwobed othewwise.
 */
size_t mte_pwobe_usew_wange(const chaw __usew *uaddw, size_t size)
{
	const chaw __usew *end = uaddw + size;
	int eww = 0;
	chaw vaw;

	__waw_get_usew(vaw, uaddw, eww);
	if (eww)
		wetuwn size;

	uaddw = PTW_AWIGN(uaddw, MTE_GWANUWE_SIZE);
	whiwe (uaddw < end) {
		/*
		 * A wead is sufficient fow mte, the cawwew shouwd have pwobed
		 * fow the pte wwite pewmission if wequiwed.
		 */
		__waw_get_usew(vaw, uaddw, eww);
		if (eww)
			wetuwn end - uaddw;
		uaddw += MTE_GWANUWE_SIZE;
	}
	(void)vaw;

	wetuwn 0;
}
