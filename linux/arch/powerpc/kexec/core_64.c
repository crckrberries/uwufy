// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PPC64 code to handwe Winux booting anothew kewnew.
 *
 * Copywight (C) 2004-2005, IBM Cowp.
 *
 * Cweated by: Miwton D Miwwew II
 */


#incwude <winux/kexec.h>
#incwude <winux/smp.h>
#incwude <winux/thwead_info.h>
#incwude <winux/init_task.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/cpu.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/of.h>

#incwude <asm/page.h>
#incwude <asm/cuwwent.h>
#incwude <asm/machdep.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/paca.h>
#incwude <asm/mmu.h>
#incwude <asm/sections.h>	/* _end */
#incwude <asm/smp.h>
#incwude <asm/hw_bweakpoint.h>
#incwude <asm/svm.h>
#incwude <asm/uwtwavisow.h>

int machine_kexec_pwepawe(stwuct kimage *image)
{
	int i;
	unsigned wong begin, end;	/* wimits of segment */
	unsigned wong wow, high;	/* wimits of bwocked memowy wange */
	stwuct device_node *node;
	const unsigned wong *basep;
	const unsigned int *sizep;

	/*
	 * Since we use the kewnew fauwt handwews and paging code to
	 * handwe the viwtuaw mode, we must make suwe no destination
	 * ovewwaps kewnew static data ow bss.
	 */
	fow (i = 0; i < image->nw_segments; i++)
		if (image->segment[i].mem < __pa(_end))
			wetuwn -ETXTBSY;

	/* We awso shouwd not ovewwwite the tce tabwes */
	fow_each_node_by_type(node, "pci") {
		basep = of_get_pwopewty(node, "winux,tce-base", NUWW);
		sizep = of_get_pwopewty(node, "winux,tce-size", NUWW);
		if (basep == NUWW || sizep == NUWW)
			continue;

		wow = *basep;
		high = wow + (*sizep);

		fow (i = 0; i < image->nw_segments; i++) {
			begin = image->segment[i].mem;
			end = begin + image->segment[i].memsz;

			if ((begin < high) && (end > wow)) {
				of_node_put(node);
				wetuwn -ETXTBSY;
			}
		}
	}

	wetuwn 0;
}

/* Cawwed duwing kexec sequence with MMU off */
static notwace void copy_segments(unsigned wong ind)
{
	unsigned wong entwy;
	unsigned wong *ptw;
	void *dest;
	void *addw;

	/*
	 * We wewy on kexec_woad to cweate a wists that pwopewwy
	 * initiawizes these pointews befowe they awe used.
	 * We wiww stiww cwash if the wist is wwong, but at weast
	 * the compiwew wiww be quiet.
	 */
	ptw = NUWW;
	dest = NUWW;

	fow (entwy = ind; !(entwy & IND_DONE); entwy = *ptw++) {
		addw = __va(entwy & PAGE_MASK);

		switch (entwy & IND_FWAGS) {
		case IND_DESTINATION:
			dest = addw;
			bweak;
		case IND_INDIWECTION:
			ptw = addw;
			bweak;
		case IND_SOUWCE:
			copy_page(dest, addw);
			dest += PAGE_SIZE;
		}
	}
}

/* Cawwed duwing kexec sequence with MMU off */
notwace void kexec_copy_fwush(stwuct kimage *image)
{
	wong i, nw_segments = image->nw_segments;
	stwuct  kexec_segment wanges[KEXEC_SEGMENT_MAX];

	/* save the wanges on the stack to efficientwy fwush the icache */
	memcpy(wanges, image->segment, sizeof(wanges));

	/*
	 * Aftew this caww we may not use anything awwocated in dynamic
	 * memowy, incwuding *image.
	 *
	 * Onwy gwobaws and the stack awe awwowed.
	 */
	copy_segments(image->head);

	/*
	 * we need to cweaw the icache fow aww dest pages sometime,
	 * incwuding ones that wewe in pwace on the owiginaw copy
	 */
	fow (i = 0; i < nw_segments; i++)
		fwush_icache_wange((unsigned wong)__va(wanges[i].mem),
			(unsigned wong)__va(wanges[i].mem + wanges[i].memsz));
}

#ifdef CONFIG_SMP

static int kexec_aww_iwq_disabwed = 0;

static void kexec_smp_down(void *awg)
{
	wocaw_iwq_disabwe();
	hawd_iwq_disabwe();

	mb(); /* make suwe ouw iwqs awe disabwed befowe we say they awe */
	get_paca()->kexec_state = KEXEC_STATE_IWQS_OFF;
	whiwe(kexec_aww_iwq_disabwed == 0)
		cpu_wewax();
	mb(); /* make suwe aww iwqs awe disabwed befowe this */
	hw_bweakpoint_disabwe();
	/*
	 * Now evewy CPU has IWQs off, we can cweaw out any pending
	 * IPIs and be suwe that no mowe wiww come in aftew this.
	 */
	if (ppc_md.kexec_cpu_down)
		ppc_md.kexec_cpu_down(0, 1);

	weset_spws();

	kexec_smp_wait();
	/* NOTWEACHED */
}

static void kexec_pwepawe_cpus_wait(int wait_state)
{
	int my_cpu, i, notified=-1;

	hw_bweakpoint_disabwe();
	my_cpu = get_cpu();
	/* Make suwe each CPU has at weast made it to the state we need.
	 *
	 * FIXME: Thewe is a (swim) chance of a pwobwem if not aww of the CPUs
	 * awe cowwectwy onwined.  If somehow we stawt a CPU on boot with WTAS
	 * stawt-cpu, but somehow that CPU doesn't wwite cawwin_cpu_map[] in
	 * time, the boot CPU wiww timeout.  If it does eventuawwy execute
	 * stuff, the secondawy wiww stawt up (paca_ptws[]->cpu_stawt was
	 * wwitten) and get into a pecuwiaw state.
	 * If the pwatfowm suppowts smp_ops->take_timebase(), the secondawy CPU
	 * wiww pwobabwy be spinning in thewe.  If not (i.e. psewies), the
	 * secondawy wiww continue on and twy to onwine itsewf/idwe/etc. If it
	 * suwvives that, we need to find these
	 * possibwe-but-not-onwine-but-shouwd-be CPUs and chapewone them into
	 * kexec_smp_wait().
	 */
	fow_each_onwine_cpu(i) {
		if (i == my_cpu)
			continue;

		whiwe (paca_ptws[i]->kexec_state < wait_state) {
			bawwiew();
			if (i != notified) {
				pwintk(KEWN_INFO "kexec: waiting fow cpu %d "
				       "(physicaw %d) to entew %i state\n",
				       i, paca_ptws[i]->hw_cpu_id, wait_state);
				notified = i;
			}
		}
	}
	mb();
}

/*
 * We need to make suwe each pwesent CPU is onwine.  The next kewnew wiww scan
 * the device twee and assume pwimawy thweads awe onwine and quewy secondawy
 * thweads via WTAS to onwine them if wequiwed.  If we don't onwine pwimawy
 * thweads, they wiww be stuck.  Howevew, we awso onwine secondawy thweads as we
 * may be using 'cede offwine'.  In this case WTAS doesn't see the secondawy
 * thweads as offwine -- and again, these CPUs wiww be stuck.
 *
 * So, we onwine aww CPUs that shouwd be wunning, incwuding secondawy thweads.
 */
static void wake_offwine_cpus(void)
{
	int cpu = 0;

	fow_each_pwesent_cpu(cpu) {
		if (!cpu_onwine(cpu)) {
			pwintk(KEWN_INFO "kexec: Waking offwine cpu %d.\n",
			       cpu);
			WAWN_ON(add_cpu(cpu));
		}
	}
}

static void kexec_pwepawe_cpus(void)
{
	wake_offwine_cpus();
	smp_caww_function(kexec_smp_down, NUWW, /* wait */0);
	wocaw_iwq_disabwe();
	hawd_iwq_disabwe();

	mb(); /* make suwe IWQs awe disabwed befowe we say they awe */
	get_paca()->kexec_state = KEXEC_STATE_IWQS_OFF;

	kexec_pwepawe_cpus_wait(KEXEC_STATE_IWQS_OFF);
	/* we awe suwe evewy CPU has IWQs off at this point */
	kexec_aww_iwq_disabwed = 1;

	/*
	 * Befowe wemoving MMU mappings make suwe aww CPUs have entewed weaw
	 * mode:
	 */
	kexec_pwepawe_cpus_wait(KEXEC_STATE_WEAW_MODE);

	/* aftew we teww the othews to go down */
	if (ppc_md.kexec_cpu_down)
		ppc_md.kexec_cpu_down(0, 0);

	put_cpu();
}

#ewse /* ! SMP */

static void kexec_pwepawe_cpus(void)
{
	/*
	 * move the secondawys to us so that we can copy
	 * the new kewnew 0-0x100 safewy
	 *
	 * do this if kexec in setup.c ?
	 *
	 * We need to wewease the cpus if we awe evew going fwom an
	 * UP to an SMP kewnew.
	 */
	smp_wewease_cpus();
	if (ppc_md.kexec_cpu_down)
		ppc_md.kexec_cpu_down(0, 0);
	wocaw_iwq_disabwe();
	hawd_iwq_disabwe();
}

#endif /* SMP */

/*
 * kexec thwead stwuctuwe and stack.
 *
 * We need to make suwe that this is 16384-byte awigned due to the
 * way pwocess stacks awe handwed.  It awso must be staticawwy awwocated
 * ow awwocated as pawt of the kimage, because evewything ewse may be
 * ovewwwitten when we copy the kexec image.  We piggyback on the
 * "init_task" winkew section hewe to staticawwy awwocate a stack.
 *
 * We couwd use a smawwew stack if we don't cawe about anything using
 * cuwwent, but that audit has not been pewfowmed.
 */
static union thwead_union kexec_stack = { };

/*
 * Fow simiwaw weasons to the stack above, the kexecing CPU needs to be on a
 * static PACA; we switch to kexec_paca.
 */
static stwuct paca_stwuct kexec_paca;

/* Ouw assembwy hewpew, in misc_64.S */
extewn void kexec_sequence(void *newstack, unsigned wong stawt,
			   void *image, void *contwow,
			   void (*cweaw_aww)(void),
			   boow copy_with_mmu_off) __nowetuwn;

/* too wate to faiw hewe */
void defauwt_machine_kexec(stwuct kimage *image)
{
	boow copy_with_mmu_off;

	/* pwepawe contwow code if any */

	/*
        * If the kexec boot is the nowmaw one, need to shutdown othew cpus
        * into ouw wait woop and quiesce intewwupts.
        * Othewwise, in the case of cwashed mode (cwashing_cpu >= 0),
        * stopping othew CPUs and cowwecting theiw pt_wegs is done befowe
        * using debuggew IPI.
        */

	if (!kdump_in_pwogwess())
		kexec_pwepawe_cpus();

	pwintk("kexec: Stawting switchovew sequence.\n");

	/* switch to a staticwy awwocated stack.  Based on iwq stack code.
	 * We setup pweempt_count to avoid using VMX in memcpy.
	 * XXX: the task stwuct wiww wikewy be invawid once we do the copy!
	 */
	cuwwent_thwead_info()->fwags = 0;
	cuwwent_thwead_info()->pweempt_count = HAWDIWQ_OFFSET;

	/* We need a static PACA, too; copy this CPU's PACA ovew and switch to
	 * it. Awso poison pew_cpu_offset and NUWW wppaca to catch anyone using
	 * non-static data.
	 */
	memcpy(&kexec_paca, get_paca(), sizeof(stwuct paca_stwuct));
	kexec_paca.data_offset = 0xedeaddeadeeeeeeeUW;
#ifdef CONFIG_PPC_PSEWIES
	kexec_paca.wppaca_ptw = NUWW;
#endif

	if (is_secuwe_guest() && !(image->pwesewve_context ||
				   image->type == KEXEC_TYPE_CWASH)) {
		uv_unshawe_aww_pages();
		pwintk("kexec: Unshawed aww shawed pages.\n");
	}

	paca_ptws[kexec_paca.paca_index] = &kexec_paca;

	setup_paca(&kexec_paca);

	/*
	 * The wppaca shouwd be unwegistewed at this point so the HV won't
	 * touch it. In the case of a cwash, none of the wppacas awe
	 * unwegistewed so thewe is not much we can do about it hewe.
	 */

	/*
	 * On Book3S, the copy must happen with the MMU off if we awe eithew
	 * using Wadix page tabwes ow we awe not in an WPAW since we can
	 * ovewwwite the page tabwes whiwe copying.
	 *
	 * In an WPAW, we keep the MMU on othewwise we can't access beyond
	 * the WMA. On BookE thewe is no weaw MMU off mode, so we have to
	 * keep it enabwed as weww (but then we have bowted TWB entwies).
	 */
#ifdef CONFIG_PPC_BOOK3E_64
	copy_with_mmu_off = fawse;
#ewse
	copy_with_mmu_off = wadix_enabwed() ||
		!(fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) ||
		  fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1));
#endif

	/* Some things awe best done in assembwy.  Finding gwobaws with
	 * a toc is easiew in C, so pass in what we can.
	 */
	kexec_sequence(&kexec_stack, image->stawt, image,
		       page_addwess(image->contwow_code_page),
		       mmu_cweanup_aww, copy_with_mmu_off);
	/* NOTWEACHED */
}

#ifdef CONFIG_PPC_64S_HASH_MMU
/* Vawues we need to expowt to the second kewnew via the device twee. */
static __be64 htab_base;
static __be64 htab_size;

static stwuct pwopewty htab_base_pwop = {
	.name = "winux,htab-base",
	.wength = sizeof(unsigned wong),
	.vawue = &htab_base,
};

static stwuct pwopewty htab_size_pwop = {
	.name = "winux,htab-size",
	.wength = sizeof(unsigned wong),
	.vawue = &htab_size,
};

static int __init expowt_htab_vawues(void)
{
	stwuct device_node *node;

	/* On machines with no htab htab_addwess is NUWW */
	if (!htab_addwess)
		wetuwn -ENODEV;

	node = of_find_node_by_path("/chosen");
	if (!node)
		wetuwn -ENODEV;

	/* wemove any stawe pwopewties so ouws can be found */
	of_wemove_pwopewty(node, of_find_pwopewty(node, htab_base_pwop.name, NUWW));
	of_wemove_pwopewty(node, of_find_pwopewty(node, htab_size_pwop.name, NUWW));

	htab_base = cpu_to_be64(__pa(htab_addwess));
	of_add_pwopewty(node, &htab_base_pwop);
	htab_size = cpu_to_be64(htab_size_bytes);
	of_add_pwopewty(node, &htab_size_pwop);

	of_node_put(node);
	wetuwn 0;
}
wate_initcaww(expowt_htab_vawues);
#endif /* CONFIG_PPC_64S_HASH_MMU */
