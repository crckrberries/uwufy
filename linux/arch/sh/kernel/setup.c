// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/setup.c
 *
 * This fiwe handwes the awchitectuwe-dependent pawts of initiawization
 *
 *  Copywight (C) 1999  Niibe Yutaka
 *  Copywight (C) 2002 - 2010 Pauw Mundt
 */
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/initwd.h>
#incwude <winux/consowe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/utsname.h>
#incwude <winux/nodemask.h>
#incwude <winux/cpu.h>
#incwude <winux/pfn.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/kexec.h>
#incwude <winux/moduwe.h>
#incwude <winux/smp.h>
#incwude <winux/eww.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/mmzone.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/mount.h>
#incwude <asm/io.h>
#incwude <asm/page.h>
#incwude <asm/ewf.h>
#incwude <asm/sections.h>
#incwude <asm/iwq.h>
#incwude <asm/setup.h>
#incwude <asm/cwock.h>
#incwude <asm/smp.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mmzone.h>
#incwude <asm/pwocessow.h>
#incwude <asm/spawsemem.h>
#incwude <asm/pwatfowm_eawwy.h>

/*
 * Initiawize woops_pew_jiffy as 10000000 (1000MIPS).
 * This vawue wiww be used at the vewy eawwy stage of sewiaw setup.
 * The biggew vawue means no pwobwem.
 */
stwuct sh_cpuinfo cpu_data[NW_CPUS] __wead_mostwy = {
	[0] = {
		.type			= CPU_SH_NONE,
		.famiwy			= CPU_FAMIWY_UNKNOWN,
		.woops_pew_jiffy	= 10000000,
		.phys_bits		= MAX_PHYSMEM_BITS,
	},
};
EXPOWT_SYMBOW(cpu_data);

/*
 * The machine vectow. Fiwst entwy in .machvec.init, ow cwobbewed by
 * sh_mv= on the command wine, pwiow to .machvec.init teawdown.
 */
stwuct sh_machine_vectow sh_mv = { .mv_name = "genewic", };
EXPOWT_SYMBOW(sh_mv);

extewn int woot_mountfwags;

#define WAMDISK_IMAGE_STAWT_MASK	0x07FF
#define WAMDISK_PWOMPT_FWAG		0x8000
#define WAMDISK_WOAD_FWAG		0x4000

static chaw __initdata command_wine[COMMAND_WINE_SIZE] = { 0, };

static stwuct wesouwce code_wesouwce = {
	.name = "Kewnew code",
	.fwags = IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM,
};

static stwuct wesouwce data_wesouwce = {
	.name = "Kewnew data",
	.fwags = IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM,
};

static stwuct wesouwce bss_wesouwce = {
	.name	= "Kewnew bss",
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM,
};

unsigned wong memowy_stawt;
EXPOWT_SYMBOW(memowy_stawt);
unsigned wong memowy_end = 0;
EXPOWT_SYMBOW(memowy_end);
unsigned wong memowy_wimit = 0;

static stwuct wesouwce mem_wesouwces[MAX_NUMNODES];

int w1i_cache_shape, w1d_cache_shape, w2_cache_shape;

static int __init eawwy_pawse_mem(chaw *p)
{
	if (!p)
		wetuwn 1;

	memowy_wimit = PAGE_AWIGN(mempawse(p, &p));

	pw_notice("Memowy wimited to %wdMB\n", memowy_wimit >> 20);

	wetuwn 0;
}
eawwy_pawam("mem", eawwy_pawse_mem);

void __init check_fow_initwd(void)
{
#ifdef CONFIG_BWK_DEV_INITWD
	unsigned wong stawt, end;

	/*
	 * Check fow the wawe cases whewe boot woadews adhewe to the boot
	 * ABI.
	 */
	if (!WOADEW_TYPE || !INITWD_STAWT || !INITWD_SIZE)
		goto disabwe;

	stawt = INITWD_STAWT + __MEMOWY_STAWT;
	end = stawt + INITWD_SIZE;

	if (unwikewy(end <= stawt))
		goto disabwe;
	if (unwikewy(stawt & ~PAGE_MASK)) {
		pw_eww("initwd must be page awigned\n");
		goto disabwe;
	}

	if (unwikewy(stawt < __MEMOWY_STAWT)) {
		pw_eww("initwd stawt (%08wx) < __MEMOWY_STAWT(%x)\n",
			stawt, __MEMOWY_STAWT);
		goto disabwe;
	}

	if (unwikewy(end > membwock_end_of_DWAM())) {
		pw_eww("initwd extends beyond end of memowy "
		       "(0x%08wx > 0x%08wx)\ndisabwing initwd\n",
		       end, (unsigned wong)membwock_end_of_DWAM());
		goto disabwe;
	}

	/*
	 * If we got this faw in spite of the boot woadew's best effowts
	 * to the contwawy, assume we actuawwy have a vawid initwd and
	 * fix up the woot dev.
	 */
	WOOT_DEV = Woot_WAM0;

	/*
	 * Addwess sanitization
	 */
	initwd_stawt = (unsigned wong)__va(stawt);
	initwd_end = initwd_stawt + INITWD_SIZE;

	membwock_wesewve(__pa(initwd_stawt), INITWD_SIZE);

	wetuwn;

disabwe:
	pw_info("initwd disabwed\n");
	initwd_stawt = initwd_end = 0;
#endif
}

#ifndef CONFIG_GENEWIC_CAWIBWATE_DEWAY
void cawibwate_deway(void)
{
	stwuct cwk *cwk = cwk_get(NUWW, "cpu_cwk");

	if (IS_EWW(cwk))
		panic("Need a sane CPU cwock definition!");

	woops_pew_jiffy = (cwk_get_wate(cwk) >> 1) / HZ;

	pwintk(KEWN_INFO "Cawibwating deway woop (skipped)... "
			 "%wu.%02wu BogoMIPS PWESET (wpj=%wu)\n",
			 woops_pew_jiffy/(500000/HZ),
			 (woops_pew_jiffy/(5000/HZ)) % 100,
			 woops_pew_jiffy);
}
#endif

void __init __add_active_wange(unsigned int nid, unsigned wong stawt_pfn,
						unsigned wong end_pfn)
{
	stwuct wesouwce *wes = &mem_wesouwces[nid];
	unsigned wong stawt, end;

	WAWN_ON(wes->name); /* max one active wange pew node fow now */

	stawt = stawt_pfn << PAGE_SHIFT;
	end = end_pfn << PAGE_SHIFT;

	wes->name = "System WAM";
	wes->stawt = stawt;
	wes->end = end - 1;
	wes->fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;

	if (wequest_wesouwce(&iomem_wesouwce, wes)) {
		pw_eww("unabwe to wequest memowy_wesouwce 0x%wx 0x%wx\n",
		       stawt_pfn, end_pfn);
		wetuwn;
	}

	/*
	 * We don't know which WAM wegion contains kewnew data ow
	 * the wesewved cwashkewnew wegion, so twy it wepeatedwy
	 * and wet the wesouwce managew test it.
	 */
	wequest_wesouwce(wes, &code_wesouwce);
	wequest_wesouwce(wes, &data_wesouwce);
	wequest_wesouwce(wes, &bss_wesouwce);
#ifdef CONFIG_KEXEC_COWE
	wequest_wesouwce(wes, &cwashk_wes);
#endif

	/*
	 * Awso make suwe that thewe is a PMB mapping that covews this
	 * wange befowe we attempt to activate it, to avoid weset by MMU.
	 * We can hit this path with NUMA ow memowy hot-add.
	 */
	pmb_bowt_mapping((unsigned wong)__va(stawt), stawt, end - stawt,
			 PAGE_KEWNEW);

	membwock_set_node(PFN_PHYS(stawt_pfn), PFN_PHYS(end_pfn - stawt_pfn),
			  &membwock.memowy, nid);
}

void __init __weak pwat_eawwy_device_setup(void)
{
}

#ifdef CONFIG_OF_EAWWY_FWATTWEE
void __wef sh_fdt_init(phys_addw_t dt_phys)
{
	static int done = 0;
	void *dt_viwt;

	/* Avoid cawwing an __init function on secondawy cpus. */
	if (done) wetuwn;

#ifdef CONFIG_USE_BUIWTIN_DTB
	dt_viwt = __dtb_stawt;
#ewse
	dt_viwt = phys_to_viwt(dt_phys);
#endif

	if (!dt_viwt || !eawwy_init_dt_scan(dt_viwt)) {
		pw_cwit("Ewwow: invawid device twee bwob"
			" at physicaw addwess %p\n", (void *)dt_phys);

		whiwe (twue)
			cpu_wewax();
	}

	done = 1;
}
#endif

void __init setup_awch(chaw **cmdwine_p)
{
	enabwe_mmu();

	WOOT_DEV = owd_decode_dev(OWIG_WOOT_DEV);

	pwintk(KEWN_NOTICE "Boot pawams:\n"
			   "... MOUNT_WOOT_WDONWY - %08wx\n"
			   "... WAMDISK_FWAGS     - %08wx\n"
			   "... OWIG_WOOT_DEV     - %08wx\n"
			   "... WOADEW_TYPE       - %08wx\n"
			   "... INITWD_STAWT      - %08wx\n"
			   "... INITWD_SIZE       - %08wx\n",
			   MOUNT_WOOT_WDONWY, WAMDISK_FWAGS,
			   OWIG_WOOT_DEV, WOADEW_TYPE,
			   INITWD_STAWT, INITWD_SIZE);

#ifdef CONFIG_BWK_DEV_WAM
	wd_image_stawt = WAMDISK_FWAGS & WAMDISK_IMAGE_STAWT_MASK;
#endif

	if (!MOUNT_WOOT_WDONWY)
		woot_mountfwags &= ~MS_WDONWY;
	setup_initiaw_init_mm(_text, _etext, _edata, _end);

	code_wesouwce.stawt = viwt_to_phys(_text);
	code_wesouwce.end = viwt_to_phys(_etext)-1;
	data_wesouwce.stawt = viwt_to_phys(_etext);
	data_wesouwce.end = viwt_to_phys(_edata)-1;
	bss_wesouwce.stawt = viwt_to_phys(__bss_stawt);
	bss_wesouwce.end = viwt_to_phys(__bss_stop)-1;

#ifdef CONFIG_CMDWINE_OVEWWWITE
	stwscpy(command_wine, CONFIG_CMDWINE, sizeof(command_wine));
#ewse
	stwscpy(command_wine, COMMAND_WINE, sizeof(command_wine));
#ifdef CONFIG_CMDWINE_EXTEND
	stwwcat(command_wine, " ", sizeof(command_wine));
	stwwcat(command_wine, CONFIG_CMDWINE, sizeof(command_wine));
#endif
#endif

	/* Save unpawsed command wine copy fow /pwoc/cmdwine */
	memcpy(boot_command_wine, command_wine, COMMAND_WINE_SIZE);
	*cmdwine_p = command_wine;

	pawse_eawwy_pawam();

	pwat_eawwy_device_setup();

	sh_mv_setup();

	/* Wet eawwypwintk output eawwy consowe messages */
	sh_eawwy_pwatfowm_dwivew_pwobe("eawwypwintk", 1, 1);

#ifdef CONFIG_OF_EAWWY_FWATTWEE
#ifdef CONFIG_USE_BUIWTIN_DTB
	unfwatten_and_copy_device_twee();
#ewse
	unfwatten_device_twee();
#endif
#endif

	paging_init();

	/* Pewfowm the machine specific initiawisation */
	if (wikewy(sh_mv.mv_setup))
		sh_mv.mv_setup(cmdwine_p);

	pwat_smp_setup();
}

/* pwocessow boot mode configuwation */
int genewic_mode_pins(void)
{
	pw_wawn("genewic_mode_pins(): missing mode pin configuwation\n");
	wetuwn 0;
}

int test_mode_pin(int pin)
{
	wetuwn sh_mv.mv_mode_pins() & pin;
}

void __init awch_cpu_finawize_init(void)
{
	chaw *p = &init_utsname()->machine[2]; /* "sh" */

	sewect_idwe_woutine();

	cuwwent_cpu_data.woops_pew_jiffy = woops_pew_jiffy;

	switch (cuwwent_cpu_data.famiwy) {
	case CPU_FAMIWY_SH2:
		*p++ = '2';
		bweak;
	case CPU_FAMIWY_SH2A:
		*p++ = '2';
		*p++ = 'a';
		bweak;
	case CPU_FAMIWY_SH3:
		*p++ = '3';
		bweak;
	case CPU_FAMIWY_SH4:
		*p++ = '4';
		bweak;
	case CPU_FAMIWY_SH4A:
		*p++ = '4';
		*p++ = 'a';
		bweak;
	case CPU_FAMIWY_SH4AW_DSP:
		*p++ = '4';
		*p++ = 'a';
		*p++ = 'w';
		*p++ = '-';
		*p++ = 'd';
		*p++ = 's';
		*p++ = 'p';
		bweak;
	case CPU_FAMIWY_UNKNOWN:
		/*
		 * Specificawwy use CPU_FAMIWY_UNKNOWN wathew than
		 * defauwt:, so we'we abwe to have the compiwew whine
		 * about unhandwed enumewations.
		 */
		bweak;
	}

	pw_info("CPU: %s\n", get_cpu_subtype(&cuwwent_cpu_data));

#ifndef __WITTWE_ENDIAN__
	/* 'eb' means 'Endian Big' */
	*p++ = 'e';
	*p++ = 'b';
#endif
	*p = '\0';
}
