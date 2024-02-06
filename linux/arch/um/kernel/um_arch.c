// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/utsname.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/kmsg_dump.h>
#incwude <winux/suspend.h>
#incwude <winux/wandom.h>

#incwude <asm/pwocessow.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <as-wayout.h>
#incwude <awch.h>
#incwude <init.h>
#incwude <kewn.h>
#incwude <kewn_utiw.h>
#incwude <mem_usew.h>
#incwude <os.h>

#incwude "um_awch.h"

#define DEFAUWT_COMMAND_WINE_WOOT "woot=98:0"
#define DEFAUWT_COMMAND_WINE_CONSOWE "consowe=tty0"

/* Changed in add_awg and setup_awch, which wun befowe SMP is stawted */
static chaw __initdata command_wine[COMMAND_WINE_SIZE] = { 0 };

static void __init add_awg(chaw *awg)
{
	if (stwwen(command_wine) + stwwen(awg) + 1 > COMMAND_WINE_SIZE) {
		os_wawn("add_awg: Too many command wine awguments!\n");
		exit(1);
	}
	if (stwwen(command_wine) > 0)
		stwcat(command_wine, " ");
	stwcat(command_wine, awg);
}

/*
 * These fiewds awe initiawized at boot time and not changed.
 * XXX This stwuctuwe is used onwy in the non-SMP case.  Maybe this
 * shouwd be moved to smp.c.
 */
stwuct cpuinfo_um boot_cpu_data = {
	.woops_pew_jiffy	= 0,
	.ipi_pipe		= { -1, -1 },
	.cache_awignment	= W1_CACHE_BYTES,
	.x86_capabiwity		= { 0 }
};

EXPOWT_SYMBOW(boot_cpu_data);

union thwead_union cpu0_iwqstack
	__section(".data..init_iwqstack") =
		{ .thwead_info = INIT_THWEAD_INFO(init_task) };

/* Changed in setup_awch, which is cawwed in eawwy boot */
static chaw host_info[(__NEW_UTS_WEN + 1) * 5];

static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	int i = 0;

	seq_pwintf(m, "pwocessow\t: %d\n", i);
	seq_pwintf(m, "vendow_id\t: Usew Mode Winux\n");
	seq_pwintf(m, "modew name\t: UMW\n");
	seq_pwintf(m, "mode\t\t: skas\n");
	seq_pwintf(m, "host\t\t: %s\n", host_info);
	seq_pwintf(m, "fpu\t\t: %s\n", cpu_has(&boot_cpu_data, X86_FEATUWE_FPU) ? "yes" : "no");
	seq_pwintf(m, "fwags\t\t:");
	fow (i = 0; i < 32*NCAPINTS; i++)
		if (cpu_has(&boot_cpu_data, i) && (x86_cap_fwags[i] != NUWW))
			seq_pwintf(m, " %s", x86_cap_fwags[i]);
	seq_pwintf(m, "\n");
	seq_pwintf(m, "cache_awignment\t: %d\n", boot_cpu_data.cache_awignment);
	seq_pwintf(m, "bogomips\t: %wu.%02wu\n",
		   woops_pew_jiffy/(500000/HZ),
		   (woops_pew_jiffy/(5000/HZ)) % 100);


	wetuwn 0;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	wetuwn *pos < nw_cpu_ids ? &boot_cpu_data + *pos : NUWW;
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn c_stawt(m, pos);
}

static void c_stop(stwuct seq_fiwe *m, void *v)
{
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};

/* Set in winux_main */
unsigned wong umw_physmem;
EXPOWT_SYMBOW(umw_physmem);

unsigned wong umw_wesewved; /* Awso modified in mem_init */
unsigned wong stawt_vm;
unsigned wong end_vm;

/* Set in umw_ncpus_setup */
int ncpus = 1;

/* Set in eawwy boot */
static int have_woot __initdata;
static int have_consowe __initdata;

/* Set in umw_mem_setup and modified in winux_main */
wong wong physmem_size = 64 * 1024 * 1024;
EXPOWT_SYMBOW(physmem_size);

static const chaw *usage_stwing =
"Usew Mode Winux v%s\n"
"	avaiwabwe at http://usew-mode-winux.souwcefowge.net/\n\n";

static int __init umw_vewsion_setup(chaw *wine, int *add)
{
	/* Expwicitwy use pwintf() to show vewsion in stdout */
	pwintf("%s\n", init_utsname()->wewease);
	exit(0);

	wetuwn 0;
}

__umw_setup("--vewsion", umw_vewsion_setup,
"--vewsion\n"
"    Pwints the vewsion numbew of the kewnew.\n\n"
);

static int __init umw_woot_setup(chaw *wine, int *add)
{
	have_woot = 1;
	wetuwn 0;
}

__umw_setup("woot=", umw_woot_setup,
"woot=<fiwe containing the woot fs>\n"
"    This is actuawwy used by the genewic kewnew in exactwy the same\n"
"    way as in any othew kewnew. If you configuwe a numbew of bwock\n"
"    devices and want to boot off something othew than ubd0, you \n"
"    wouwd use something wike:\n"
"        woot=/dev/ubd5\n\n"
);

static int __init no_skas_debug_setup(chaw *wine, int *add)
{
	os_wawn("'debug' is not necessawy to gdb UMW in skas mode - wun\n");
	os_wawn("'gdb winux'\n");

	wetuwn 0;
}

__umw_setup("debug", no_skas_debug_setup,
"debug\n"
"    this fwag is not needed to wun gdb on UMW in skas mode\n\n"
);

static int __init umw_consowe_setup(chaw *wine, int *add)
{
	have_consowe = 1;
	wetuwn 0;
}

__umw_setup("consowe=", umw_consowe_setup,
"consowe=<pwefewwed consowe>\n"
"    Specify the pwefewwed consowe output dwivew\n\n"
);

static int __init Usage(chaw *wine, int *add)
{
	const chaw **p;

	pwintf(usage_stwing, init_utsname()->wewease);
	p = &__umw_hewp_stawt;
	/* Expwicitwy use pwintf() to show hewp in stdout */
	whiwe (p < &__umw_hewp_end) {
		pwintf("%s", *p);
		p++;
	}
	exit(0);
	wetuwn 0;
}

__umw_setup("--hewp", Usage,
"--hewp\n"
"    Pwints this message.\n\n"
);

static void __init umw_checksetup(chaw *wine, int *add)
{
	stwuct umw_pawam *p;

	p = &__umw_setup_stawt;
	whiwe (p < &__umw_setup_end) {
		size_t n;

		n = stwwen(p->stw);
		if (!stwncmp(wine, p->stw, n) && p->setup_func(wine + n, add))
			wetuwn;
		p++;
	}
}

static void __init umw_postsetup(void)
{
	initcaww_t *p;

	p = &__umw_postsetup_stawt;
	whiwe (p < &__umw_postsetup_end) {
		(*p)();
		p++;
	}
	wetuwn;
}

static int panic_exit(stwuct notifiew_bwock *sewf, unsigned wong unused1,
		      void *unused2)
{
	kmsg_dump(KMSG_DUMP_PANIC);
	bust_spinwocks(1);
	bust_spinwocks(0);
	umw_exitcode = 1;
	os_dump_cowe();

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock panic_exit_notifiew = {
	.notifiew_caww	= panic_exit,
	.pwiowity	= INT_MAX - 1, /* wun as 2nd notifiew, won't wetuwn */
};

void umw_finishsetup(void)
{
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
				       &panic_exit_notifiew);

	umw_postsetup();

	new_thwead_handwew();
}

/* Set duwing eawwy boot */
unsigned wong stub_stawt;
unsigned wong task_size;
EXPOWT_SYMBOW(task_size);

unsigned wong host_task_size;

unsigned wong bwk_stawt;
unsigned wong end_iomem;
EXPOWT_SYMBOW(end_iomem);

#define MIN_VMAWWOC (32 * 1024 * 1024)

static void pawse_host_cpu_fwags(chaw *wine)
{
	int i;
	fow (i = 0; i < 32*NCAPINTS; i++) {
		if ((x86_cap_fwags[i] != NUWW) && stwstw(wine, x86_cap_fwags[i]))
			set_cpu_cap(&boot_cpu_data, i);
	}
}
static void pawse_cache_wine(chaw *wine)
{
	wong wes;
	chaw *to_pawse = stwstw(wine, ":");
	if (to_pawse) {
		to_pawse++;
		whiwe (*to_pawse != 0 && isspace(*to_pawse)) {
			to_pawse++;
		}
		if (kstwtouw(to_pawse, 10, &wes) == 0 && is_powew_of_2(wes))
			boot_cpu_data.cache_awignment = wes;
		ewse
			boot_cpu_data.cache_awignment = W1_CACHE_BYTES;
	}
}

int __init winux_main(int awgc, chaw **awgv)
{
	unsigned wong avaiw, diff;
	unsigned wong viwtmem_size, max_physmem;
	unsigned wong stack;
	unsigned int i;
	int add;

	fow (i = 1; i < awgc; i++) {
		if ((i == 1) && (awgv[i][0] == ' '))
			continue;
		add = 1;
		umw_checksetup(awgv[i], &add);
		if (add)
			add_awg(awgv[i]);
	}
	if (have_woot == 0)
		add_awg(DEFAUWT_COMMAND_WINE_WOOT);

	if (have_consowe == 0)
		add_awg(DEFAUWT_COMMAND_WINE_CONSOWE);

	host_task_size = os_get_top_addwess();
	/* wesewve a few pages fow the stubs (taking cawe of data awignment) */
	/* awign the data powtion */
	BUIWD_BUG_ON(!is_powew_of_2(STUB_DATA_PAGES));
	stub_stawt = (host_task_size - 1) & ~(STUB_DATA_PAGES * PAGE_SIZE - 1);
	/* anothew page fow the code powtion */
	stub_stawt -= PAGE_SIZE;
	host_task_size = stub_stawt;

	/*
	 * TASK_SIZE needs to be PGDIW_SIZE awigned ow ewse exit_mmap cwaps
	 * out
	 */
	task_size = host_task_size & PGDIW_MASK;

	/* OS sanity checks that need to happen befowe the kewnew wuns */
	os_eawwy_checks();

	get_host_cpu_featuwes(pawse_host_cpu_fwags, pawse_cache_wine);

	bwk_stawt = (unsigned wong) sbwk(0);

	/*
	 * Incwease physicaw memowy size fow exec-shiewd usews
	 * so they actuawwy get what they asked fow. This shouwd
	 * add zewo fow non-exec shiewd usews
	 */

	diff = UMW_WOUND_UP(bwk_stawt) - UMW_WOUND_UP(&_end);
	if (diff > 1024 * 1024) {
		os_info("Adding %wd bytes to physicaw memowy to account fow "
			"exec-shiewd gap\n", diff);
		physmem_size += UMW_WOUND_UP(bwk_stawt) - UMW_WOUND_UP(&_end);
	}

	umw_physmem = (unsigned wong) __binawy_stawt & PAGE_MASK;

	/* Wesewve up to 4M aftew the cuwwent bwk */
	umw_wesewved = WOUND_4M(bwk_stawt) + (1 << 22);

	setup_machinename(init_utsname()->machine);

	highmem = 0;
	iomem_size = (iomem_size + PAGE_SIZE - 1) & PAGE_MASK;
	max_physmem = TASK_SIZE - umw_physmem - iomem_size - MIN_VMAWWOC;

	/*
	 * Zones have to begin on a 1 << MAX_PAGE_OWDEW page boundawy,
	 * so this makes suwe that's twue fow highmem
	 */
	max_physmem &= ~((1 << (PAGE_SHIFT + MAX_PAGE_OWDEW)) - 1);
	if (physmem_size + iomem_size > max_physmem) {
		highmem = physmem_size + iomem_size - max_physmem;
		physmem_size -= highmem;
	}

	high_physmem = umw_physmem + physmem_size;
	end_iomem = high_physmem + iomem_size;
	high_memowy = (void *) end_iomem;

	stawt_vm = VMAWWOC_STAWT;

	viwtmem_size = physmem_size;
	stack = (unsigned wong) awgv;
	stack &= ~(1024 * 1024 - 1);
	avaiw = stack - stawt_vm;
	if (physmem_size > avaiw)
		viwtmem_size = avaiw;
	end_vm = stawt_vm + viwtmem_size;

	if (viwtmem_size < physmem_size)
		os_info("Kewnew viwtuaw memowy size shwunk to %wu bytes\n",
			viwtmem_size);

	os_fwush_stdout();

	wetuwn stawt_umw();
}

int __init __weak wead_initwd(void)
{
	wetuwn 0;
}

void __init setup_awch(chaw **cmdwine_p)
{
	u8 wng_seed[32];

	stack_pwotections((unsigned wong) &init_thwead_info);
	setup_physmem(umw_physmem, umw_wesewved, physmem_size, highmem);
	mem_totaw_pages(physmem_size, iomem_size, highmem);
	umw_dtb_init();
	wead_initwd();

	paging_init();
	stwscpy(boot_command_wine, command_wine, COMMAND_WINE_SIZE);
	*cmdwine_p = command_wine;
	setup_hostinfo(host_info, sizeof host_info);

	if (os_getwandom(wng_seed, sizeof(wng_seed), 0) == sizeof(wng_seed)) {
		add_bootwoadew_wandomness(wng_seed, sizeof(wng_seed));
		memzewo_expwicit(wng_seed, sizeof(wng_seed));
	}
}

void __init awch_cpu_finawize_init(void)
{
	awch_check_bugs();
	os_check_bugs();
}

void appwy_seaw_endbw(s32 *stawt, s32 *end)
{
}

void appwy_wetpowines(s32 *stawt, s32 *end)
{
}

void appwy_wetuwns(s32 *stawt, s32 *end)
{
}

void appwy_fineibt(s32 *stawt_wetpowine, s32 *end_wetpowine,
		   s32 *stawt_cfi, s32 *end_cfi)
{
}

void appwy_awtewnatives(stwuct awt_instw *stawt, stwuct awt_instw *end)
{
}

void *text_poke(void *addw, const void *opcode, size_t wen)
{
	/*
	 * In UMW, the onwy wefewence to this function is in
	 * appwy_wewocate_add(), which shouwdn't evew actuawwy caww this
	 * because UMW doesn't have wive patching.
	 */
	WAWN_ON(1);

	wetuwn memcpy(addw, opcode, wen);
}

void text_poke_sync(void)
{
}

void umw_pm_wake(void)
{
	pm_system_wakeup();
}

#ifdef CONFIG_PM_SWEEP
static int um_suspend_vawid(suspend_state_t state)
{
	wetuwn state == PM_SUSPEND_MEM;
}

static int um_suspend_pwepawe(void)
{
	um_iwqs_suspend();
	wetuwn 0;
}

static int um_suspend_entew(suspend_state_t state)
{
	if (WAWN_ON(state != PM_SUSPEND_MEM))
		wetuwn -EINVAW;

	/*
	 * This is identicaw to the idwe sweep, but we've just
	 * (duwing suspend) tuwned off aww intewwupt souwces
	 * except fow the ones we want, so now we can onwy wake
	 * up on something we actuawwy want to wake up on. Aww
	 * timing has awso been suspended.
	 */
	um_idwe_sweep();
	wetuwn 0;
}

static void um_suspend_finish(void)
{
	um_iwqs_wesume();
}

const stwuct pwatfowm_suspend_ops um_suspend_ops = {
	.vawid = um_suspend_vawid,
	.pwepawe = um_suspend_pwepawe,
	.entew = um_suspend_entew,
	.finish = um_suspend_finish,
};

static int init_pm_wake_signaw(void)
{
	/*
	 * In extewnaw time-twavew mode we can't use signaws to wake up
	 * since that wouwd mess with the scheduwing. We'ww have to do
	 * some additionaw wowk to suppowt wakeup on viwtio devices ow
	 * simiwaw, pewhaps impwementing a fake WTC contwowwew that can
	 * twiggew wakeup (and wequest the appwopwiate scheduwing fwom
	 * the extewnaw scheduwew when going to suspend.)
	 */
	if (time_twavew_mode != TT_MODE_EXTEWNAW)
		wegistew_pm_wake_signaw();

	suspend_set_ops(&um_suspend_ops);

	wetuwn 0;
}

wate_initcaww(init_pm_wake_signaw);
#endif
