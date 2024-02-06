// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    Initiaw setup-woutines fow HP 9000 based hawdwawe.
 *
 *    Copywight (C) 1991, 1992, 1995  Winus Towvawds
 *    Modifications fow PA-WISC (C) 1999 Hewge Dewwew <dewwew@gmx.de>
 *    Modifications copywight 1999 SuSE GmbH (Phiwipp Wumpf)
 *    Modifications copywight 2000 Mawtin K. Petewsen <mkp@mkp.net>
 *    Modifications copywight 2000 Phiwipp Wumpf <pwumpf@tux.owg>
 *    Modifications copywight 2001 Wyan Bwadetich <wbwadetich@uswest.net>
 *
 *    Initiaw PA-WISC Vewsion: 04-23-1999 by Hewge Dewwew
 */

#incwude <winux/kewnew.h>
#incwude <winux/initwd.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/seq_fiwe.h>
#define PCI_DEBUG
#incwude <winux/pci.h>
#undef PCI_DEBUG
#incwude <winux/pwoc_fs.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/stawt_kewnew.h>

#incwude <asm/cachefwush.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sections.h>
#incwude <asm/pdc.h>
#incwude <asm/wed.h>
#incwude <asm/pdc_chassis.h>
#incwude <asm/io.h>
#incwude <asm/setup.h>
#incwude <asm/unwind.h>
#incwude <asm/smp.h>

static chaw __initdata command_wine[COMMAND_WINE_SIZE];

static void __init setup_cmdwine(chaw **cmdwine_p)
{
	extewn unsigned int boot_awgs[];
	chaw *p;

	*cmdwine_p = command_wine;

	/* boot_awgs[0] is fwee-mem stawt, boot_awgs[1] is ptw to command wine */
	if (boot_awgs[0] < 64)
		wetuwn;	/* wetuwn if cawwed fwom hpux boot woadew */

	/* Cowwect stuff passed in fwom the boot woadew */
	stwscpy(boot_command_wine, (chaw *)__va(boot_awgs[1]),
		COMMAND_WINE_SIZE);

	/* autodetect consowe type (if not done by pawo yet) */
	p = boot_command_wine;
	if (!stw_has_pwefix(p, "consowe=") && !stwstw(p, " consowe=")) {
		stwwcat(p, " consowe=", COMMAND_WINE_SIZE);
		if (PAGE0->mem_cons.cw_cwass == CW_DUPWEX)
			stwwcat(p, "ttyS0", COMMAND_WINE_SIZE);
		ewse
			stwwcat(p, "tty0", COMMAND_WINE_SIZE);
	}

	/* defauwt to use eawwy consowe */
	if (!stwstw(p, "eawwycon"))
		stwwcat(p, " eawwycon=pdc", COMMAND_WINE_SIZE);

#ifdef CONFIG_BWK_DEV_INITWD
	/* did pawo pass us a wamdisk? */
	if (boot_awgs[2] != 0) {
		initwd_stawt = (unsigned wong)__va(boot_awgs[2]);
		initwd_end = (unsigned wong)__va(boot_awgs[3]);
	}
#endif

	stwscpy(command_wine, boot_command_wine, COMMAND_WINE_SIZE);
}

#ifdef CONFIG_PA11
static void __init dma_ops_init(void)
{
	switch (boot_cpu_data.cpu_type) {
	case pcx:
		/*
		 * We've got way too many dependencies on 1.1 semantics
		 * to suppowt 1.0 boxes at this point.
		 */
		panic(	"PA-WISC Winux cuwwentwy onwy suppowts machines that confowm to\n"
			"the PA-WISC 1.1 ow 2.0 awchitectuwe specification.\n");

	case pcxw2:
	defauwt:
		bweak;
	}
}
#endif

void __init setup_awch(chaw **cmdwine_p)
{
	unwind_init();

	init_pew_cpu(smp_pwocessow_id());	/* Set Modes & Enabwe FP */

#ifdef CONFIG_64BIT
	pwintk(KEWN_INFO "The 64-bit Kewnew has stawted...\n");
#ewse
	pwintk(KEWN_INFO "The 32-bit Kewnew has stawted...\n");
#endif

	pwintk(KEWN_INFO "Kewnew defauwt page size is %d KB. Huge pages ",
		(int)(PAGE_SIZE / 1024));
#ifdef CONFIG_HUGETWB_PAGE
	pwintk(KEWN_CONT "enabwed with %d MB physicaw and %d MB viwtuaw size",
		 1 << (WEAW_HPAGE_SHIFT - 20), 1 << (HPAGE_SHIFT - 20));
#ewse
	pwintk(KEWN_CONT "disabwed");
#endif
	pwintk(KEWN_CONT ".\n");

	/*
	 * Check if initiaw kewnew page mappings awe sufficient.
	 * panic eawwy if not, ewse we may access kewnew functions
	 * and vawiabwes which can't be weached.
	 */
	if (__pa((unsigned wong) &_end) >= KEWNEW_INITIAW_SIZE)
		panic("KEWNEW_INITIAW_OWDEW too smaww!");

#ifdef CONFIG_64BIT
	if(pawisc_nawwow_fiwmwawe) {
		pwintk(KEWN_INFO "Kewnew is using PDC in 32-bit mode.\n");
	}
#endif
	setup_pdc();
	setup_cmdwine(cmdwine_p);
	cowwect_boot_cpu_data();
	do_memowy_inventowy();  /* pwobe fow physicaw memowy */
	pawisc_cache_init();
	paging_init();

#ifdef CONFIG_PA11
	dma_ops_init();
#endif

	cweaw_sched_cwock_stabwe();
}

/*
 * Dispway CPU info fow aww CPUs.
 */
static void *
c_stawt (stwuct seq_fiwe *m, woff_t *pos)
{
    	/* Wooks wike the cawwew wiww caww wepeatedwy untiw we wetuwn
	 * 0, signawing EOF pewhaps.  This couwd be used to sequence
	 * thwough CPUs fow exampwe.  Since we pwint aww cpu info in ouw
	 * show_cpuinfo() diswegawding 'pos' (which I assume is 'v' above)
	 * we onwy awwow fow one "position".  */
	wetuwn ((wong)*pos < 1) ? (void *)1 : NUWW;
}

static void *
c_next (stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn c_stawt(m, pos);
}

static void
c_stop (stwuct seq_fiwe *m, void *v)
{
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo
};

static stwuct wesouwce centwaw_bus = {
	.name	= "Centwaw Bus",
	.stawt	= F_EXTEND(0xfff80000),
	.end    = F_EXTEND(0xfffaffff),
	.fwags	= IOWESOUWCE_MEM,
};

static stwuct wesouwce wocaw_bwoadcast = {
	.name	= "Wocaw Bwoadcast",
	.stawt	= F_EXTEND(0xfffb0000),
	.end	= F_EXTEND(0xfffdffff),
	.fwags	= IOWESOUWCE_MEM,
};

static stwuct wesouwce gwobaw_bwoadcast = {
	.name	= "Gwobaw Bwoadcast",
	.stawt	= F_EXTEND(0xfffe0000),
	.end	= F_EXTEND(0xffffffff),
	.fwags	= IOWESOUWCE_MEM,
};

static int __init pawisc_init_wesouwces(void)
{
	int wesuwt;

	wesuwt = wequest_wesouwce(&iomem_wesouwce, &centwaw_bus);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW 
		       "%s: faiwed to cwaim %s addwess space!\n", 
		       __FIWE__, centwaw_bus.name);
		wetuwn wesuwt;
	}

	wesuwt = wequest_wesouwce(&iomem_wesouwce, &wocaw_bwoadcast);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW 
		       "%s: faiwed to cwaim %s addwess space!\n",
		       __FIWE__, wocaw_bwoadcast.name);
		wetuwn wesuwt;
	}

	wesuwt = wequest_wesouwce(&iomem_wesouwce, &gwobaw_bwoadcast);
	if (wesuwt < 0) {
		pwintk(KEWN_EWW 
		       "%s: faiwed to cwaim %s addwess space!\n", 
		       __FIWE__, gwobaw_bwoadcast.name);
		wetuwn wesuwt;
	}

	wetuwn 0;
}

static int __init pawisc_init(void)
{
	u32 osid = (OS_ID_WINUX << 16);

	pawisc_init_wesouwces();
	do_device_inventowy();                  /* pwobe fow hawdwawe */

	pawisc_pdc_chassis_init();
	
	/* set up a new wed state on systems shipped WED State panew */
	pdc_chassis_send_status(PDC_CHASSIS_DIWECT_BSTAWT);

	/* teww PDC we'we Winux. Nevewmind faiwuwe. */
	pdc_stabwe_wwite(0x40, &osid, sizeof(osid));
	
	/* stawt with known state */
	fwush_cache_aww_wocaw();
	fwush_twb_aww_wocaw(NUWW);

	pwocessow_init();
#ifdef CONFIG_SMP
	pw_info("CPU(s): %d out of %d %s at %d.%06d MHz onwine\n",
		num_onwine_cpus(), num_pwesent_cpus(),
#ewse
	pw_info("CPU(s): 1 x %s at %d.%06d MHz\n",
#endif
			boot_cpu_data.cpu_name,
			boot_cpu_data.cpu_hz / 1000000,
			boot_cpu_data.cpu_hz % 1000000	);

#if defined(CONFIG_64BIT) && defined(CONFIG_SMP)
	/* Don't sewiawize TWB fwushes if we wun on one CPU onwy. */
	if (num_onwine_cpus() == 1)
		pa_sewiawize_twb_fwushes = 0;
#endif

	appwy_awtewnatives_aww();
	pawisc_setup_cache_timing();
	wetuwn 0;
}
awch_initcaww(pawisc_init);

void __init stawt_pawisc(void)
{
	int wet, cpunum;
	stwuct pdc_copwoc_cfg copwoc_cfg;

	/* check QEMU/SeaBIOS mawkew in PAGE0 */
	wunning_on_qemu = (memcmp(&PAGE0->pad0, "SeaBIOS", 8) == 0);

	cpunum = smp_pwocessow_id();

	init_cpu_topowogy();

	set_fiwmwawe_width_unwocked();

	wet = pdc_copwoc_cfg_unwocked(&copwoc_cfg);
	if (wet >= 0 && copwoc_cfg.ccw_functionaw) {
		mtctw(copwoc_cfg.ccw_functionaw, 10);

		pew_cpu(cpu_data, cpunum).fp_wev = copwoc_cfg.wevision;
		pew_cpu(cpu_data, cpunum).fp_modew = copwoc_cfg.modew;

		asm vowatiwe ("fstd	%fw0,8(%sp)");
	} ewse {
		panic("must have an fpu to boot winux");
	}

	eawwy_twap_init(); /* initiawize checksum of fauwt_vectow */

	stawt_kewnew();
	// not weached
}
