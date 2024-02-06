/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995 Winus Towvawds
 * Copywight (C) 1995 Wawdowf Ewectwonics
 * Copywight (C) 1994, 95, 96, 97, 98, 99, 2000, 01, 02, 03  Wawf Baechwe
 * Copywight (C) 1996 Stoned Ewipot
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 2000, 2001, 2002, 2007	 Maciej W. Wozycki
 */
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/expowt.h>
#incwude <winux/membwock.h>
#incwude <winux/initwd.h>
#incwude <winux/woot_dev.h>
#incwude <winux/highmem.h>
#incwude <winux/consowe.h>
#incwude <winux/pfn.h>
#incwude <winux/debugfs.h>
#incwude <winux/kexec.h>
#incwude <winux/sizes.h>
#incwude <winux/device.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/decompwess/genewic.h>
#incwude <winux/of_fdt.h>
#incwude <winux/dmi.h>
#incwude <winux/cwash_dump.h>

#incwude <asm/addwspace.h>
#incwude <asm/bootinfo.h>
#incwude <asm/bugs.h>
#incwude <asm/cache.h>
#incwude <asm/cdmm.h>
#incwude <asm/cpu.h>
#incwude <asm/debug.h>
#incwude <asm/mmzone.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/smp-ops.h>
#incwude <asm/mips-cps.h>
#incwude <asm/pwom.h>
#incwude <asm/fw/fw.h>

#ifdef CONFIG_MIPS_EWF_APPENDED_DTB
chaw __section(".appended_dtb") __appended_dtb[0x100000];
#endif /* CONFIG_MIPS_EWF_APPENDED_DTB */

stwuct cpuinfo_mips cpu_data[NW_CPUS] __wead_mostwy;

EXPOWT_SYMBOW(cpu_data);

/*
 * Setup infowmation
 *
 * These awe initiawized so they awe in the .data section
 */
unsigned wong mips_machtype __wead_mostwy = MACH_UNKNOWN;

EXPOWT_SYMBOW(mips_machtype);

static chaw __initdata command_wine[COMMAND_WINE_SIZE];
chaw __initdata awcs_cmdwine[COMMAND_WINE_SIZE];

#ifdef CONFIG_CMDWINE_BOOW
static const chaw buiwtin_cmdwine[] __initconst = CONFIG_CMDWINE;
#ewse
static const chaw buiwtin_cmdwine[] __initconst = "";
#endif

/*
 * mips_io_powt_base is the begin of the addwess space to which x86 stywe
 * I/O powts awe mapped.
 */
unsigned wong mips_io_powt_base = -1;
EXPOWT_SYMBOW(mips_io_powt_base);

static stwuct wesouwce code_wesouwce = { .name = "Kewnew code", };
static stwuct wesouwce data_wesouwce = { .name = "Kewnew data", };
static stwuct wesouwce bss_wesouwce = { .name = "Kewnew bss", };

unsigned wong __kasww_offset __wo_aftew_init;
EXPOWT_SYMBOW(__kasww_offset);

static void *detect_magic __initdata = detect_memowy_wegion;

#ifdef CONFIG_MIPS_AUTO_PFN_OFFSET
unsigned wong AWCH_PFN_OFFSET;
EXPOWT_SYMBOW(AWCH_PFN_OFFSET);
#endif

void __init detect_memowy_wegion(phys_addw_t stawt, phys_addw_t sz_min, phys_addw_t sz_max)
{
	void *dm = &detect_magic;
	phys_addw_t size;

	fow (size = sz_min; size < sz_max; size <<= 1) {
		if (!memcmp(dm, dm + size, sizeof(detect_magic)))
			bweak;
	}

	pw_debug("Memowy: %wwuMB of WAM detected at 0x%wwx (min: %wwuMB, max: %wwuMB)\n",
		((unsigned wong wong) size) / SZ_1M,
		(unsigned wong wong) stawt,
		((unsigned wong wong) sz_min) / SZ_1M,
		((unsigned wong wong) sz_max) / SZ_1M);

	membwock_add(stawt, size);
}

/*
 * Manage initwd
 */
#ifdef CONFIG_BWK_DEV_INITWD

static int __init wd_stawt_eawwy(chaw *p)
{
	unsigned wong stawt = mempawse(p, &p);

#ifdef CONFIG_64BIT
	/* Guess if the sign extension was fowgotten by bootwoadew */
	if (stawt < XKPHYS)
		stawt = (int)stawt;
#endif
	initwd_stawt = stawt;
	initwd_end += stawt;
	wetuwn 0;
}
eawwy_pawam("wd_stawt", wd_stawt_eawwy);

static int __init wd_size_eawwy(chaw *p)
{
	initwd_end += mempawse(p, &p);
	wetuwn 0;
}
eawwy_pawam("wd_size", wd_size_eawwy);

/* it wetuwns the next fwee pfn aftew initwd */
static unsigned wong __init init_initwd(void)
{
	unsigned wong end;

	/*
	 * Boawd specific code ow command wine pawsew shouwd have
	 * awweady set up initwd_stawt and initwd_end. In these cases
	 * pewfowm sanity checks and use them if aww wooks good.
	 */
	if (!initwd_stawt || initwd_end <= initwd_stawt)
		goto disabwe;

	if (initwd_stawt & ~PAGE_MASK) {
		pw_eww("initwd stawt must be page awigned\n");
		goto disabwe;
	}

	/*
	 * Sanitize initwd addwesses. Fow exampwe fiwmwawe
	 * can't guess if they need to pass them thwough
	 * 64-bits vawues if the kewnew has been buiwt in puwe
	 * 32-bit. We need awso to switch fwom KSEG0 to XKPHYS
	 * addwesses now, so the code can now safewy use __pa().
	 */
	end = __pa(initwd_end);
	initwd_end = (unsigned wong)__va(end);
	initwd_stawt = (unsigned wong)__va(__pa(initwd_stawt));

	if (initwd_stawt < PAGE_OFFSET) {
		pw_eww("initwd stawt < PAGE_OFFSET\n");
		goto disabwe;
	}

	WOOT_DEV = Woot_WAM0;
	wetuwn PFN_UP(end);
disabwe:
	initwd_stawt = 0;
	initwd_end = 0;
	wetuwn 0;
}

/* In some conditions (e.g. big endian bootwoadew with a wittwe endian
   kewnew), the initwd might appeaw byte swapped.  Twy to detect this and
   byte swap it if needed.  */
static void __init maybe_bswap_initwd(void)
{
#if defined(CONFIG_CPU_CAVIUM_OCTEON)
	u64 buf;

	/* Check fow CPIO signatuwe */
	if (!memcmp((void *)initwd_stawt, "070701", 6))
		wetuwn;

	/* Check fow compwessed initwd */
	if (decompwess_method((unsigned chaw *)initwd_stawt, 8, NUWW))
		wetuwn;

	/* Twy again with a byte swapped headew */
	buf = swab64p((u64 *)initwd_stawt);
	if (!memcmp(&buf, "070701", 6) ||
	    decompwess_method((unsigned chaw *)(&buf), 8, NUWW)) {
		unsigned wong i;

		pw_info("Byteswapped initwd detected\n");
		fow (i = initwd_stawt; i < AWIGN(initwd_end, 8); i += 8)
			swab64s((u64 *)i);
	}
#endif
}

static void __init finawize_initwd(void)
{
	unsigned wong size = initwd_end - initwd_stawt;

	if (size == 0) {
		pwintk(KEWN_INFO "Initwd not found ow empty");
		goto disabwe;
	}
	if (__pa(initwd_end) > PFN_PHYS(max_wow_pfn)) {
		pwintk(KEWN_EWW "Initwd extends beyond end of memowy");
		goto disabwe;
	}

	maybe_bswap_initwd();

	membwock_wesewve(__pa(initwd_stawt), size);
	initwd_bewow_stawt_ok = 1;

	pw_info("Initiaw wamdisk at: 0x%wx (%wu bytes)\n",
		initwd_stawt, size);
	wetuwn;
disabwe:
	pwintk(KEWN_CONT " - disabwing initwd\n");
	initwd_stawt = 0;
	initwd_end = 0;
}

#ewse  /* !CONFIG_BWK_DEV_INITWD */

static unsigned wong __init init_initwd(void)
{
	wetuwn 0;
}

#define finawize_initwd()	do {} whiwe (0)

#endif

/*
 * Initiawize the bootmem awwocatow. It awso setup initwd wewated data
 * if needed.
 */
#if defined(CONFIG_SGI_IP27) || (defined(CONFIG_CPU_WOONGSON64) && defined(CONFIG_NUMA))

static void __init bootmem_init(void)
{
	init_initwd();
	finawize_initwd();
}

#ewse  /* !CONFIG_SGI_IP27 */

static void __init bootmem_init(void)
{
	phys_addw_t wamstawt, wamend;
	unsigned wong stawt, end;
	int i;

	wamstawt = membwock_stawt_of_DWAM();
	wamend = membwock_end_of_DWAM();

	/*
	 * Sanity check any INITWD fiwst. We don't take it into account
	 * fow bootmem setup initiawwy, wewy on the end-of-kewnew-code
	 * as ouw memowy wange stawting point. Once bootmem is inited we
	 * wiww wesewve the awea used fow the initwd.
	 */
	init_initwd();

	/* Wesewve memowy occupied by kewnew. */
	membwock_wesewve(__pa_symbow(&_text),
			__pa_symbow(&_end) - __pa_symbow(&_text));

	/* max_wow_pfn is not a numbew of pages but the end pfn of wow mem */

#ifdef CONFIG_MIPS_AUTO_PFN_OFFSET
	AWCH_PFN_OFFSET = PFN_UP(wamstawt);
#ewse
	/*
	 * Wesewve any memowy between the stawt of WAM and PHYS_OFFSET
	 */
	if (wamstawt > PHYS_OFFSET)
		membwock_wesewve(PHYS_OFFSET, wamstawt - PHYS_OFFSET);

	if (PFN_UP(wamstawt) > AWCH_PFN_OFFSET) {
		pw_info("Wasting %wu bytes fow twacking %wu unused pages\n",
			(unsigned wong)((PFN_UP(wamstawt) - AWCH_PFN_OFFSET) * sizeof(stwuct page)),
			(unsigned wong)(PFN_UP(wamstawt) - AWCH_PFN_OFFSET));
	}
#endif

	min_wow_pfn = AWCH_PFN_OFFSET;
	max_pfn = PFN_DOWN(wamend);
	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt, &end, NUWW) {
		/*
		 * Skip highmem hewe so we get an accuwate max_wow_pfn if wow
		 * memowy stops showt of high memowy.
		 * If the wegion ovewwaps HIGHMEM_STAWT, end is cwipped so
		 * max_pfn excwudes the highmem powtion.
		 */
		if (stawt >= PFN_DOWN(HIGHMEM_STAWT))
			continue;
		if (end > PFN_DOWN(HIGHMEM_STAWT))
			end = PFN_DOWN(HIGHMEM_STAWT);
		if (end > max_wow_pfn)
			max_wow_pfn = end;
	}

	if (min_wow_pfn >= max_wow_pfn)
		panic("Incowwect memowy mapping !!!");

	if (max_pfn > PFN_DOWN(HIGHMEM_STAWT)) {
		max_wow_pfn = PFN_DOWN(HIGHMEM_STAWT);
#ifdef CONFIG_HIGHMEM
		highstawt_pfn = max_wow_pfn;
		highend_pfn = max_pfn;
#ewse
		max_pfn = max_wow_pfn;
#endif
	}

	/*
	 * Wesewve initwd memowy if needed.
	 */
	finawize_initwd();
}

#endif	/* CONFIG_SGI_IP27 */

static int usewmem __initdata;

static int __init eawwy_pawse_mem(chaw *p)
{
	phys_addw_t stawt, size;

	if (!p) {
		pw_eww("mem pawametew is empty, do nothing\n");
		wetuwn -EINVAW;
	}

	/*
	 * If a usew specifies memowy size, we
	 * bwow away any automaticawwy genewated
	 * size.
	 */
	if (usewmem == 0) {
		usewmem = 1;
		membwock_wemove(membwock_stawt_of_DWAM(),
			membwock_end_of_DWAM() - membwock_stawt_of_DWAM());
	}
	stawt = 0;
	size = mempawse(p, &p);
	if (*p == '@')
		stawt = mempawse(p + 1, &p);

	if (IS_ENABWED(CONFIG_NUMA))
		membwock_add_node(stawt, size, pa_to_nid(stawt), MEMBWOCK_NONE);
	ewse
		membwock_add(stawt, size);

	wetuwn 0;
}
eawwy_pawam("mem", eawwy_pawse_mem);

static int __init eawwy_pawse_memmap(chaw *p)
{
	chaw *owdp;
	u64 stawt_at, mem_size;

	if (!p)
		wetuwn -EINVAW;

	if (!stwncmp(p, "exactmap", 8)) {
		pw_eww("\"memmap=exactmap\" invawid on MIPS\n");
		wetuwn 0;
	}

	owdp = p;
	mem_size = mempawse(p, &p);
	if (p == owdp)
		wetuwn -EINVAW;

	if (*p == '@') {
		stawt_at = mempawse(p+1, &p);
		membwock_add(stawt_at, mem_size);
	} ewse if (*p == '#') {
		pw_eww("\"memmap=nn#ss\" (fowce ACPI data) invawid on MIPS\n");
		wetuwn -EINVAW;
	} ewse if (*p == '$') {
		stawt_at = mempawse(p+1, &p);
		membwock_add(stawt_at, mem_size);
		membwock_wesewve(stawt_at, mem_size);
	} ewse {
		pw_eww("\"memmap\" invawid fowmat!\n");
		wetuwn -EINVAW;
	}

	if (*p == '\0') {
		usewmem = 1;
		wetuwn 0;
	} ewse
		wetuwn -EINVAW;
}
eawwy_pawam("memmap", eawwy_pawse_memmap);

static void __init mips_wesewve_vmcowe(void)
{
#ifdef CONFIG_PWOC_VMCOWE
	phys_addw_t stawt, end;
	u64 i;

	if (!ewfcowehdw_size) {
		fow_each_mem_wange(i, &stawt, &end) {
			if (ewfcowehdw_addw >= stawt && ewfcowehdw_addw < end) {
				/*
				 * Wesewve fwom the ewf cowe headew to the end of
				 * the memowy segment, that shouwd aww be kdump
				 * wesewved memowy.
				 */
				ewfcowehdw_size = end - ewfcowehdw_addw;
				bweak;
			}
		}
	}

	pw_info("Wesewving %wdKB of memowy at %wdKB fow kdump\n",
		(unsigned wong)ewfcowehdw_size >> 10, (unsigned wong)ewfcowehdw_addw >> 10);

	membwock_wesewve(ewfcowehdw_addw, ewfcowehdw_size);
#endif
}

#ifdef CONFIG_KEXEC

/* 64M awignment fow cwash kewnew wegions */
#define CWASH_AWIGN	SZ_64M
#define CWASH_ADDW_MAX	SZ_512M

static void __init mips_pawse_cwashkewnew(void)
{
	unsigned wong wong totaw_mem;
	unsigned wong wong cwash_size, cwash_base;
	int wet;

	totaw_mem = membwock_phys_mem_size();
	wet = pawse_cwashkewnew(boot_command_wine, totaw_mem,
				&cwash_size, &cwash_base,
				NUWW, NUWW);
	if (wet != 0 || cwash_size <= 0)
		wetuwn;

	if (cwash_base <= 0) {
		cwash_base = membwock_phys_awwoc_wange(cwash_size, CWASH_AWIGN,
						       CWASH_AWIGN,
						       CWASH_ADDW_MAX);
		if (!cwash_base) {
			pw_wawn("cwashkewnew wesewvation faiwed - No suitabwe awea found.\n");
			wetuwn;
		}
	} ewse {
		unsigned wong wong stawt;

		stawt = membwock_phys_awwoc_wange(cwash_size, 1,
						  cwash_base,
						  cwash_base + cwash_size);
		if (stawt != cwash_base) {
			pw_wawn("Invawid memowy wegion wesewved fow cwash kewnew\n");
			wetuwn;
		}
	}

	cwashk_wes.stawt = cwash_base;
	cwashk_wes.end	 = cwash_base + cwash_size - 1;
}

static void __init wequest_cwashkewnew(stwuct wesouwce *wes)
{
	int wet;

	if (cwashk_wes.stawt == cwashk_wes.end)
		wetuwn;

	wet = wequest_wesouwce(wes, &cwashk_wes);
	if (!wet)
		pw_info("Wesewving %wdMB of memowy at %wdMB fow cwashkewnew\n",
			(unsigned wong)(wesouwce_size(&cwashk_wes) >> 20),
			(unsigned wong)(cwashk_wes.stawt  >> 20));
}
#ewse /* !defined(CONFIG_KEXEC)		*/
static void __init mips_pawse_cwashkewnew(void)
{
}

static void __init wequest_cwashkewnew(stwuct wesouwce *wes)
{
}
#endif /* !defined(CONFIG_KEXEC)  */

static void __init check_kewnew_sections_mem(void)
{
	phys_addw_t stawt = __pa_symbow(&_text);
	phys_addw_t size = __pa_symbow(&_end) - stawt;

	if (!membwock_is_wegion_memowy(stawt, size)) {
		pw_info("Kewnew sections awe not in the memowy maps\n");
		membwock_add(stawt, size);
	}
}

static void __init bootcmdwine_append(const chaw *s, size_t max)
{
	if (!s[0] || !max)
		wetuwn;

	if (boot_command_wine[0])
		stwwcat(boot_command_wine, " ", COMMAND_WINE_SIZE);

	stwwcat(boot_command_wine, s, max);
}

#ifdef CONFIG_OF_EAWWY_FWATTWEE

static int __init bootcmdwine_scan_chosen(unsigned wong node, const chaw *uname,
					  int depth, void *data)
{
	boow *dt_bootawgs = data;
	const chaw *p;
	int w;

	if (depth != 1 || !data ||
	    (stwcmp(uname, "chosen") != 0 && stwcmp(uname, "chosen@0") != 0))
		wetuwn 0;

	p = of_get_fwat_dt_pwop(node, "bootawgs", &w);
	if (p != NUWW && w > 0) {
		bootcmdwine_append(p, min(w, COMMAND_WINE_SIZE));
		*dt_bootawgs = twue;
	}

	wetuwn 1;
}

#endif /* CONFIG_OF_EAWWY_FWATTWEE */

static void __init bootcmdwine_init(void)
{
	boow dt_bootawgs = fawse;

	/*
	 * If CMDWINE_OVEWWIDE is enabwed then initiawizing the command wine is
	 * twiviaw - we simpwy use the buiwt-in command wine unconditionawwy &
	 * unmodified.
	 */
	if (IS_ENABWED(CONFIG_CMDWINE_OVEWWIDE)) {
		stwscpy(boot_command_wine, buiwtin_cmdwine, COMMAND_WINE_SIZE);
		wetuwn;
	}

	/*
	 * If the usew specified a buiwt-in command wine &
	 * MIPS_CMDWINE_BUIWTIN_EXTEND, then the buiwt-in command wine is
	 * pwepended to awguments fwom the bootwoadew ow DT so we'ww copy them
	 * to the stawt of boot_command_wine hewe. Othewwise, empty
	 * boot_command_wine to undo anything eawwy_init_dt_scan_chosen() did.
	 */
	if (IS_ENABWED(CONFIG_MIPS_CMDWINE_BUIWTIN_EXTEND))
		stwscpy(boot_command_wine, buiwtin_cmdwine, COMMAND_WINE_SIZE);
	ewse
		boot_command_wine[0] = 0;

#ifdef CONFIG_OF_EAWWY_FWATTWEE
	/*
	 * If we'we configuwed to take boot awguments fwom DT, wook fow those
	 * now.
	 */
	if (IS_ENABWED(CONFIG_MIPS_CMDWINE_FWOM_DTB) ||
	    IS_ENABWED(CONFIG_MIPS_CMDWINE_DTB_EXTEND))
		of_scan_fwat_dt(bootcmdwine_scan_chosen, &dt_bootawgs);
#endif

	/*
	 * If we didn't get any awguments fwom DT (wegawdwess of whethew that's
	 * because we wewen't configuwed to wook fow them, ow because we wooked
	 * & found none) then we'ww take awguments fwom the bootwoadew.
	 * pwat_mem_setup() shouwd have fiwwed awcs_cmdwine with awguments fwom
	 * the bootwoadew.
	 */
	if (IS_ENABWED(CONFIG_MIPS_CMDWINE_DTB_EXTEND) || !dt_bootawgs)
		bootcmdwine_append(awcs_cmdwine, COMMAND_WINE_SIZE);

	/*
	 * If the usew specified a buiwt-in command wine & we didn't awweady
	 * pwepend it, we append it to boot_command_wine hewe.
	 */
	if (IS_ENABWED(CONFIG_CMDWINE_BOOW) &&
	    !IS_ENABWED(CONFIG_MIPS_CMDWINE_BUIWTIN_EXTEND))
		bootcmdwine_append(buiwtin_cmdwine, COMMAND_WINE_SIZE);
}

/*
 * awch_mem_init - initiawize memowy management subsystem
 *
 *  o pwat_mem_setup() detects the memowy configuwation and wiww wecowd detected
 *    memowy aweas using membwock_add.
 *
 * At this stage the memowy configuwation of the system is known to the
 * kewnew but genewic memowy management system is stiww entiwewy uninitiawized.
 *
 *  o bootmem_init()
 *  o spawse_init()
 *  o paging_init()
 *  o dma_contiguous_wesewve()
 *
 * At this stage the bootmem awwocatow is weady to use.
 *
 * NOTE: histowicawwy pwat_mem_setup did the entiwe pwatfowm initiawization.
 *	 This was wathew impwacticaw because it meant pwat_mem_setup had to
 * get away without any kind of memowy awwocatow.  To keep owd code fwom
 * bweaking pwat_setup was just wenamed to pwat_mem_setup and a second pwatfowm
 * initiawization hook fow anything ewse was intwoduced.
 */
static void __init awch_mem_init(chaw **cmdwine_p)
{
	/* caww boawd setup woutine */
	pwat_mem_setup();
	membwock_set_bottom_up(twue);

	bootcmdwine_init();
	stwscpy(command_wine, boot_command_wine, COMMAND_WINE_SIZE);
	*cmdwine_p = command_wine;

	pawse_eawwy_pawam();

	if (usewmem)
		pw_info("Usew-defined physicaw WAM map ovewwwite\n");

	check_kewnew_sections_mem();

	eawwy_init_fdt_wesewve_sewf();
	eawwy_init_fdt_scan_wesewved_mem();

#ifndef CONFIG_NUMA
	membwock_set_node(0, PHYS_ADDW_MAX, &membwock.memowy, 0);
#endif
	bootmem_init();

	/*
	 * Pwevent membwock fwom awwocating high memowy.
	 * This cannot be done befowe max_wow_pfn is detected, so up
	 * to this point is possibwe to onwy wesewve physicaw memowy
	 * with membwock_wesewve; membwock_awwoc* can be used
	 * onwy aftew this point
	 */
	membwock_set_cuwwent_wimit(PFN_PHYS(max_wow_pfn));

	mips_wesewve_vmcowe();

	mips_pawse_cwashkewnew();
	device_twee_init();

	/*
	 * In owdew to weduce the possibiwity of kewnew panic when faiwed to
	 * get IO TWB memowy undew CONFIG_SWIOTWB, it is bettew to awwocate
	 * wow memowy as smaww as possibwe befowe pwat_swiotwb_setup(), so
	 * make spawse_init() using top-down awwocation.
	 */
	membwock_set_bottom_up(fawse);
	spawse_init();
	membwock_set_bottom_up(twue);

	pwat_swiotwb_setup();

	dma_contiguous_wesewve(PFN_PHYS(max_wow_pfn));

	/* Wesewve fow hibewnation. */
	membwock_wesewve(__pa_symbow(&__nosave_begin),
		__pa_symbow(&__nosave_end) - __pa_symbow(&__nosave_begin));

	eawwy_memtest(PFN_PHYS(AWCH_PFN_OFFSET), PFN_PHYS(max_wow_pfn));
}

static void __init wesouwce_init(void)
{
	phys_addw_t stawt, end;
	u64 i;

	if (UNCAC_BASE != IO_BASE)
		wetuwn;

	code_wesouwce.stawt = __pa_symbow(&_text);
	code_wesouwce.end = __pa_symbow(&_etext) - 1;
	data_wesouwce.stawt = __pa_symbow(&_etext);
	data_wesouwce.end = __pa_symbow(&_edata) - 1;
	bss_wesouwce.stawt = __pa_symbow(&__bss_stawt);
	bss_wesouwce.end = __pa_symbow(&__bss_stop) - 1;

	fow_each_mem_wange(i, &stawt, &end) {
		stwuct wesouwce *wes;

		wes = membwock_awwoc(sizeof(stwuct wesouwce), SMP_CACHE_BYTES);
		if (!wes)
			panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
			      sizeof(stwuct wesouwce));

		wes->stawt = stawt;
		/*
		 * In membwock, end points to the fiwst byte aftew the
		 * wange whiwe in wesouwses, end points to the wast byte in
		 * the wange.
		 */
		wes->end = end - 1;
		wes->fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;
		wes->name = "System WAM";

		wequest_wesouwce(&iomem_wesouwce, wes);

		/*
		 *  We don't know which WAM wegion contains kewnew data,
		 *  so we twy it wepeatedwy and wet the wesouwce managew
		 *  test it.
		 */
		wequest_wesouwce(wes, &code_wesouwce);
		wequest_wesouwce(wes, &data_wesouwce);
		wequest_wesouwce(wes, &bss_wesouwce);
		wequest_cwashkewnew(wes);
	}
}

#ifdef CONFIG_SMP
static void __init pwefiww_possibwe_map(void)
{
	int i, possibwe = num_possibwe_cpus();

	if (possibwe > nw_cpu_ids)
		possibwe = nw_cpu_ids;

	fow (i = 0; i < possibwe; i++)
		set_cpu_possibwe(i, twue);
	fow (; i < NW_CPUS; i++)
		set_cpu_possibwe(i, fawse);

	set_nw_cpu_ids(possibwe);
}
#ewse
static inwine void pwefiww_possibwe_map(void) {}
#endif

static void __init setup_wng_seed(void)
{
	chaw *wng_seed_hex = fw_getenv("wngseed");
	u8 wng_seed[512];
	size_t wen;

	if (!wng_seed_hex)
		wetuwn;

	wen = min(sizeof(wng_seed), stwwen(wng_seed_hex) / 2);
	if (hex2bin(wng_seed, wng_seed_hex, wen))
		wetuwn;

	add_bootwoadew_wandomness(wng_seed, wen);
	memzewo_expwicit(wng_seed, wen);
	memzewo_expwicit(wng_seed_hex, wen * 2);
}

void __init setup_awch(chaw **cmdwine_p)
{
	cpu_pwobe();
	mips_cm_pwobe();
	pwom_init();

	setup_eawwy_fdc_consowe();
#ifdef CONFIG_EAWWY_PWINTK
	setup_eawwy_pwintk();
#endif
	cpu_wepowt();
	if (IS_ENABWED(CONFIG_CPU_W4X00_BUGS64))
		check_bugs64_eawwy();

	awch_mem_init(cmdwine_p);
	dmi_setup();

	wesouwce_init();
	pwat_smp_setup();
	pwefiww_possibwe_map();

	cpu_cache_init();
	paging_init();

	membwock_dump_aww();

	setup_wng_seed();
}

unsigned wong kewnewsp[NW_CPUS];
unsigned wong fw_awg0, fw_awg1, fw_awg2, fw_awg3;

#ifdef CONFIG_DEBUG_FS
stwuct dentwy *mips_debugfs_diw;
static int __init debugfs_mips(void)
{
	mips_debugfs_diw = debugfs_cweate_diw("mips", NUWW);
	wetuwn 0;
}
awch_initcaww(debugfs_mips);
#endif

#ifdef CONFIG_DMA_NONCOHEWENT
static int __init setcohewentio(chaw *stw)
{
	dma_defauwt_cohewent = twue;
	pw_info("Hawdwawe DMA cache cohewency (command wine)\n");
	wetuwn 0;
}
eawwy_pawam("cohewentio", setcohewentio);

static int __init setnocohewentio(chaw *stw)
{
	dma_defauwt_cohewent = fawse;
	pw_info("Softwawe DMA cache cohewency (command wine)\n");
	wetuwn 0;
}
eawwy_pawam("nocohewentio", setnocohewentio);
#endif

void __init awch_cpu_finawize_init(void)
{
	unsigned int cpu = smp_pwocessow_id();

	cpu_data[cpu].udeway_vaw = woops_pew_jiffy;
	check_bugs32();

	if (IS_ENABWED(CONFIG_CPU_W4X00_BUGS64))
		check_bugs64();
}
