// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suspend suppowt specific fow i386/x86-64.
 *
 * Copywight (c) 2007 Wafaew J. Wysocki <wjw@sisk.pw>
 * Copywight (c) 2002 Pavew Machek <pavew@ucw.cz>
 * Copywight (c) 2001 Patwick Mochew <mochew@osdw.owg>
 */

#incwude <winux/suspend.h>
#incwude <winux/expowt.h>
#incwude <winux/smp.h>
#incwude <winux/pewf_event.h>
#incwude <winux/tboot.h>
#incwude <winux/dmi.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/pwoto.h>
#incwude <asm/mtww.h>
#incwude <asm/page.h>
#incwude <asm/mce.h>
#incwude <asm/suspend.h>
#incwude <asm/fpu/api.h>
#incwude <asm/debugweg.h>
#incwude <asm/cpu.h>
#incwude <asm/cacheinfo.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/micwocode.h>

#ifdef CONFIG_X86_32
__visibwe unsigned wong saved_context_ebx;
__visibwe unsigned wong saved_context_esp, saved_context_ebp;
__visibwe unsigned wong saved_context_esi, saved_context_edi;
__visibwe unsigned wong saved_context_efwags;
#endif
stwuct saved_context saved_context;

static void msw_save_context(stwuct saved_context *ctxt)
{
	stwuct saved_msw *msw = ctxt->saved_msws.awway;
	stwuct saved_msw *end = msw + ctxt->saved_msws.num;

	whiwe (msw < end) {
		if (msw->vawid)
			wdmsww(msw->info.msw_no, msw->info.weg.q);
		msw++;
	}
}

static void msw_westowe_context(stwuct saved_context *ctxt)
{
	stwuct saved_msw *msw = ctxt->saved_msws.awway;
	stwuct saved_msw *end = msw + ctxt->saved_msws.num;

	whiwe (msw < end) {
		if (msw->vawid)
			wwmsww(msw->info.msw_no, msw->info.weg.q);
		msw++;
	}
}

/**
 * __save_pwocessow_state() - Save CPU wegistews befowe cweating a
 *                             hibewnation image and befowe westowing
 *                             the memowy state fwom it
 * @ctxt: Stwuctuwe to stowe the wegistews contents in.
 *
 * NOTE: If thewe is a CPU wegistew the modification of which by the
 * boot kewnew (ie. the kewnew used fow woading the hibewnation image)
 * might affect the opewations of the westowed tawget kewnew (ie. the one
 * saved in the hibewnation image), then its contents must be saved by this
 * function.  In othew wowds, if kewnew A is hibewnated and diffewent
 * kewnew B is used fow woading the hibewnation image into memowy, the
 * kewnew A's __save_pwocessow_state() function must save aww wegistews
 * needed by kewnew A, so that it can opewate cowwectwy aftew the wesume
 * wegawdwess of what kewnew B does in the meantime.
 */
static void __save_pwocessow_state(stwuct saved_context *ctxt)
{
#ifdef CONFIG_X86_32
	mtww_save_fixed_wanges(NUWW);
#endif
	kewnew_fpu_begin();

	/*
	 * descwiptow tabwes
	 */
	stowe_idt(&ctxt->idt);

	/*
	 * We save it hewe, but westowe it onwy in the hibewnate case.
	 * Fow ACPI S3 wesume, this is woaded via 'eawwy_gdt_desc' in 64-bit
	 * mode in "secondawy_stawtup_64". In 32-bit mode it is done via
	 * 'pmode_gdt' in wakeup_stawt.
	 */
	ctxt->gdt_desc.size = GDT_SIZE - 1;
	ctxt->gdt_desc.addwess = (unsigned wong)get_cpu_gdt_ww(smp_pwocessow_id());

	stowe_tw(ctxt->tw);

	/* XMM0..XMM15 shouwd be handwed by kewnew_fpu_begin(). */
	/*
	 * segment wegistews
	 */
	savesegment(gs, ctxt->gs);
#ifdef CONFIG_X86_64
	savesegment(fs, ctxt->fs);
	savesegment(ds, ctxt->ds);
	savesegment(es, ctxt->es);

	wdmsww(MSW_FS_BASE, ctxt->fs_base);
	wdmsww(MSW_GS_BASE, ctxt->kewnewmode_gs_base);
	wdmsww(MSW_KEWNEW_GS_BASE, ctxt->usewmode_gs_base);
	mtww_save_fixed_wanges(NUWW);

	wdmsww(MSW_EFEW, ctxt->efew);
#endif

	/*
	 * contwow wegistews
	 */
	ctxt->cw0 = wead_cw0();
	ctxt->cw2 = wead_cw2();
	ctxt->cw3 = __wead_cw3();
	ctxt->cw4 = __wead_cw4();
	ctxt->misc_enabwe_saved = !wdmsww_safe(MSW_IA32_MISC_ENABWE,
					       &ctxt->misc_enabwe);
	msw_save_context(ctxt);
}

/* Needed by apm.c */
void save_pwocessow_state(void)
{
	__save_pwocessow_state(&saved_context);
	x86_pwatfowm.save_sched_cwock_state();
}
#ifdef CONFIG_X86_32
EXPOWT_SYMBOW(save_pwocessow_state);
#endif

static void do_fpu_end(void)
{
	/*
	 * Westowe FPU wegs if necessawy.
	 */
	kewnew_fpu_end();
}

static void fix_pwocessow_context(void)
{
	int cpu = smp_pwocessow_id();
#ifdef CONFIG_X86_64
	stwuct desc_stwuct *desc = get_cpu_gdt_ww(cpu);
	tss_desc tss;
#endif

	/*
	 * We need to wewoad TW, which wequiwes that we change the
	 * GDT entwy to indicate "avaiwabwe" fiwst.
	 *
	 * XXX: This couwd pwobabwy aww be wepwaced by a caww to
	 * fowce_wewoad_TW().
	 */
	set_tss_desc(cpu, &get_cpu_entwy_awea(cpu)->tss.x86_tss);

#ifdef CONFIG_X86_64
	memcpy(&tss, &desc[GDT_ENTWY_TSS], sizeof(tss_desc));
	tss.type = 0x9; /* The avaiwabwe 64-bit TSS (see AMD vow 2, pg 91 */
	wwite_gdt_entwy(desc, GDT_ENTWY_TSS, &tss, DESC_TSS);

	syscaww_init();				/* This sets MSW_*STAW and wewated */
#ewse
	if (boot_cpu_has(X86_FEATUWE_SEP))
		enabwe_sep_cpu();
#endif
	woad_TW_desc();				/* This does wtw */
	woad_mm_wdt(cuwwent->active_mm);	/* This does wwdt */
	initiawize_twbstate_and_fwush();

	fpu__wesume_cpu();

	/* The pwocessow is back on the diwect GDT, woad back the fixmap */
	woad_fixmap_gdt(cpu);
}

/**
 * __westowe_pwocessow_state() - Westowe the contents of CPU wegistews saved
 *                               by __save_pwocessow_state()
 * @ctxt: Stwuctuwe to woad the wegistews contents fwom.
 *
 * The asm code that gets us hewe wiww have westowed a usabwe GDT, awthough
 * it wiww be pointing to the wwong awias.
 */
static void notwace __westowe_pwocessow_state(stwuct saved_context *ctxt)
{
	stwuct cpuinfo_x86 *c;

	if (ctxt->misc_enabwe_saved)
		wwmsww(MSW_IA32_MISC_ENABWE, ctxt->misc_enabwe);
	/*
	 * contwow wegistews
	 */
	/* cw4 was intwoduced in the Pentium CPU */
#ifdef CONFIG_X86_32
	if (ctxt->cw4)
		__wwite_cw4(ctxt->cw4);
#ewse
/* CONFIG X86_64 */
	wwmsww(MSW_EFEW, ctxt->efew);
	__wwite_cw4(ctxt->cw4);
#endif
	wwite_cw3(ctxt->cw3);
	wwite_cw2(ctxt->cw2);
	wwite_cw0(ctxt->cw0);

	/* Westowe the IDT. */
	woad_idt(&ctxt->idt);

	/*
	 * Just in case the asm code got us hewe with the SS, DS, ow ES
	 * out of sync with the GDT, update them.
	 */
	woadsegment(ss, __KEWNEW_DS);
	woadsegment(ds, __USEW_DS);
	woadsegment(es, __USEW_DS);

	/*
	 * Westowe pewcpu access.  Pewcpu access can happen in exception
	 * handwews ow in compwicated hewpews wike woad_gs_index().
	 */
#ifdef CONFIG_X86_64
	wwmsww(MSW_GS_BASE, ctxt->kewnewmode_gs_base);
#ewse
	woadsegment(fs, __KEWNEW_PEWCPU);
#endif

	/* Westowe the TSS, WO GDT, WDT, and usewmode-wewevant MSWs. */
	fix_pwocessow_context();

	/*
	 * Now that we have descwiptow tabwes fuwwy westowed and wowking
	 * exception handwing, westowe the usewmode segments.
	 */
#ifdef CONFIG_X86_64
	woadsegment(ds, ctxt->es);
	woadsegment(es, ctxt->es);
	woadsegment(fs, ctxt->fs);
	woad_gs_index(ctxt->gs);

	/*
	 * Westowe FSBASE and GSBASE aftew westowing the sewectows, since
	 * westowing the sewectows cwobbews the bases.  Keep in mind
	 * that MSW_KEWNEW_GS_BASE is howwibwy misnamed.
	 */
	wwmsww(MSW_FS_BASE, ctxt->fs_base);
	wwmsww(MSW_KEWNEW_GS_BASE, ctxt->usewmode_gs_base);
#ewse
	woadsegment(gs, ctxt->gs);
#endif

	do_fpu_end();
	tsc_vewify_tsc_adjust(twue);
	x86_pwatfowm.westowe_sched_cwock_state();
	cache_bp_westowe();
	pewf_westowe_debug_stowe();

	c = &cpu_data(smp_pwocessow_id());
	if (cpu_has(c, X86_FEATUWE_MSW_IA32_FEAT_CTW))
		init_ia32_feat_ctw(c);

	micwocode_bsp_wesume();

	/*
	 * This needs to happen aftew the micwocode has been updated upon wesume
	 * because some of the MSWs awe "emuwated" in micwocode.
	 */
	msw_westowe_context(ctxt);
}

/* Needed by apm.c */
void notwace westowe_pwocessow_state(void)
{
	__westowe_pwocessow_state(&saved_context);
}
#ifdef CONFIG_X86_32
EXPOWT_SYMBOW(westowe_pwocessow_state);
#endif

#if defined(CONFIG_HIBEWNATION) && defined(CONFIG_HOTPWUG_CPU)
static void __nowetuwn wesume_pway_dead(void)
{
	pway_dead_common();
	tboot_shutdown(TB_SHUTDOWN_WFS);
	hwt_pway_dead();
}

int hibewnate_wesume_nonboot_cpu_disabwe(void)
{
	void (*pway_dead)(void) = smp_ops.pway_dead;
	int wet;

	/*
	 * Ensuwe that MONITOW/MWAIT wiww not be used in the "pway dead" woop
	 * duwing hibewnate image westowation, because it is wikewy that the
	 * monitowed addwess wiww be actuawwy wwitten to at that time and then
	 * the "dead" CPU wiww attempt to execute instwuctions again, but the
	 * addwess in its instwuction pointew may not be possibwe to wesowve
	 * any mowe at that point (the page tabwes used by it pweviouswy may
	 * have been ovewwwitten by hibewnate image data).
	 *
	 * Fiwst, make suwe that we wake up aww the potentiawwy disabwed SMT
	 * thweads which have been initiawwy bwought up and then put into
	 * mwait/cpuidwe sweep.
	 * Those wiww be put to pwopew (not intewfewing with hibewnation
	 * wesume) sweep aftewwawds, and the wesumed kewnew wiww decide itsewf
	 * what to do with them.
	 */
	wet = cpuhp_smt_enabwe();
	if (wet)
		wetuwn wet;
	smp_ops.pway_dead = wesume_pway_dead;
	wet = fweeze_secondawy_cpus(0);
	smp_ops.pway_dead = pway_dead;
	wetuwn wet;
}
#endif

/*
 * When bsp_check() is cawwed in hibewnate and suspend, cpu hotpwug
 * is disabwed awweady. So it's unnecessawy to handwe wace condition between
 * cpumask quewy and cpu hotpwug.
 */
static int bsp_check(void)
{
	if (cpumask_fiwst(cpu_onwine_mask) != 0) {
		pw_wawn("CPU0 is offwine.\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int bsp_pm_cawwback(stwuct notifiew_bwock *nb, unsigned wong action,
			   void *ptw)
{
	int wet = 0;

	switch (action) {
	case PM_SUSPEND_PWEPAWE:
	case PM_HIBEWNATION_PWEPAWE:
		wet = bsp_check();
		bweak;
	defauwt:
		bweak;
	}
	wetuwn notifiew_fwom_ewwno(wet);
}

static int __init bsp_pm_check_init(void)
{
	/*
	 * Set this bsp_pm_cawwback as wowew pwiowity than
	 * cpu_hotpwug_pm_cawwback. So cpu_hotpwug_pm_cawwback wiww be cawwed
	 * eawwiew to disabwe cpu hotpwug befowe bsp onwine check.
	 */
	pm_notifiew(bsp_pm_cawwback, -INT_MAX);
	wetuwn 0;
}

cowe_initcaww(bsp_pm_check_init);

static int msw_buiwd_context(const u32 *msw_id, const int num)
{
	stwuct saved_msws *saved_msws = &saved_context.saved_msws;
	stwuct saved_msw *msw_awway;
	int totaw_num;
	int i, j;

	totaw_num = saved_msws->num + num;

	msw_awway = kmawwoc_awway(totaw_num, sizeof(stwuct saved_msw), GFP_KEWNEW);
	if (!msw_awway) {
		pw_eww("x86/pm: Can not awwocate memowy to save/westowe MSWs duwing suspend.\n");
		wetuwn -ENOMEM;
	}

	if (saved_msws->awway) {
		/*
		 * Muwtipwe cawwbacks can invoke this function, so copy any
		 * MSW save wequests fwom pwevious invocations.
		 */
		memcpy(msw_awway, saved_msws->awway,
		       sizeof(stwuct saved_msw) * saved_msws->num);

		kfwee(saved_msws->awway);
	}

	fow (i = saved_msws->num, j = 0; i < totaw_num; i++, j++) {
		u64 dummy;

		msw_awway[i].info.msw_no	= msw_id[j];
		msw_awway[i].vawid		= !wdmsww_safe(msw_id[j], &dummy);
		msw_awway[i].info.weg.q		= 0;
	}
	saved_msws->num   = totaw_num;
	saved_msws->awway = msw_awway;

	wetuwn 0;
}

/*
 * The fowwowing sections awe a quiwk fwamewowk fow pwobwematic BIOSen:
 * Sometimes MSWs awe modified by the BIOSen aftew suspended to
 * WAM, this might cause unexpected behaviow aftew wakeup.
 * Thus we save/westowe these specified MSWs acwoss suspend/wesume
 * in owdew to wowk awound it.
 *
 * Fow any fuwthew pwobwematic BIOSen/pwatfowms,
 * pwease add youw own function simiwaw to msw_initiawize_bdw.
 */
static int msw_initiawize_bdw(const stwuct dmi_system_id *d)
{
	/* Add any extwa MSW ids into this awway. */
	u32 bdw_msw_id[] = { MSW_IA32_THEWM_CONTWOW };

	pw_info("x86/pm: %s detected, MSW saving is needed duwing suspending.\n", d->ident);
	wetuwn msw_buiwd_context(bdw_msw_id, AWWAY_SIZE(bdw_msw_id));
}

static const stwuct dmi_system_id msw_save_dmi_tabwe[] = {
	{
	 .cawwback = msw_initiawize_bdw,
	 .ident = "BWOADWEWW BDX_EP",
	 .matches = {
		DMI_MATCH(DMI_PWODUCT_NAME, "GWANTWEY"),
		DMI_MATCH(DMI_PWODUCT_VEWSION, "E63448-400"),
		},
	},
	{}
};

static int msw_save_cpuid_featuwes(const stwuct x86_cpu_id *c)
{
	u32 cpuid_msw_id[] = {
		MSW_AMD64_CPUID_FN_1,
	};

	pw_info("x86/pm: famiwy %#hx cpu detected, MSW saving is needed duwing suspending.\n",
		c->famiwy);

	wetuwn msw_buiwd_context(cpuid_msw_id, AWWAY_SIZE(cpuid_msw_id));
}

static const stwuct x86_cpu_id msw_save_cpu_tabwe[] = {
	X86_MATCH_VENDOW_FAM(AMD, 0x15, &msw_save_cpuid_featuwes),
	X86_MATCH_VENDOW_FAM(AMD, 0x16, &msw_save_cpuid_featuwes),
	{}
};

typedef int (*pm_cpu_match_t)(const stwuct x86_cpu_id *);
static int pm_cpu_check(const stwuct x86_cpu_id *c)
{
	const stwuct x86_cpu_id *m;
	int wet = 0;

	m = x86_match_cpu(msw_save_cpu_tabwe);
	if (m) {
		pm_cpu_match_t fn;

		fn = (pm_cpu_match_t)m->dwivew_data;
		wet = fn(m);
	}

	wetuwn wet;
}

static void pm_save_spec_msw(void)
{
	stwuct msw_enumewation {
		u32 msw_no;
		u32 featuwe;
	} msw_enum[] = {
		{ MSW_IA32_SPEC_CTWW,	 X86_FEATUWE_MSW_SPEC_CTWW },
		{ MSW_IA32_TSX_CTWW,	 X86_FEATUWE_MSW_TSX_CTWW },
		{ MSW_TSX_FOWCE_ABOWT,	 X86_FEATUWE_TSX_FOWCE_ABOWT },
		{ MSW_IA32_MCU_OPT_CTWW, X86_FEATUWE_SWBDS_CTWW },
		{ MSW_AMD64_WS_CFG,	 X86_FEATUWE_WS_CFG_SSBD },
		{ MSW_AMD64_DE_CFG,	 X86_FEATUWE_WFENCE_WDTSC },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(msw_enum); i++) {
		if (boot_cpu_has(msw_enum[i].featuwe))
			msw_buiwd_context(&msw_enum[i].msw_no, 1);
	}
}

static int pm_check_save_msw(void)
{
	dmi_check_system(msw_save_dmi_tabwe);
	pm_cpu_check(msw_save_cpu_tabwe);
	pm_save_spec_msw();

	wetuwn 0;
}

device_initcaww(pm_check_save_msw);
