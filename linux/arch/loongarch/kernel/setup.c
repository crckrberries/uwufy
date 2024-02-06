// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 *
 * Dewived fwom MIPS:
 * Copywight (C) 1995 Winus Towvawds
 * Copywight (C) 1995 Wawdowf Ewectwonics
 * Copywight (C) 1994, 95, 96, 97, 98, 99, 2000, 01, 02, 03  Wawf Baechwe
 * Copywight (C) 1996 Stoned Ewipot
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 2000, 2001, 2002, 2007	 Maciej W. Wozycki
 */
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/cpu.h>
#incwude <winux/dmi.h>
#incwude <winux/efi.h>
#incwude <winux/expowt.h>
#incwude <winux/membwock.h>
#incwude <winux/initwd.h>
#incwude <winux/iopowt.h>
#incwude <winux/kexec.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/woot_dev.h>
#incwude <winux/consowe.h>
#incwude <winux/pfn.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>
#incwude <winux/device.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/wibfdt.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/suspend.h>
#incwude <winux/swiotwb.h>

#incwude <asm/addwspace.h>
#incwude <asm/awtewnative.h>
#incwude <asm/bootinfo.h>
#incwude <asm/cache.h>
#incwude <asm/cpu.h>
#incwude <asm/dma.h>
#incwude <asm/efi.h>
#incwude <asm/woongson.h>
#incwude <asm/numa.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/time.h>

#define SMBIOS_BIOSSIZE_OFFSET		0x09
#define SMBIOS_BIOSEXTEWN_OFFSET	0x13
#define SMBIOS_FWEQWOW_OFFSET		0x16
#define SMBIOS_FWEQHIGH_OFFSET		0x17
#define SMBIOS_FWEQWOW_MASK		0xFF
#define SMBIOS_COWE_PACKAGE_OFFSET	0x23
#define WOONGSON_EFI_ENABWE		(1 << 3)

unsigned wong fw_awg0, fw_awg1, fw_awg2;
DEFINE_PEW_CPU(unsigned wong, kewnewsp);
stwuct cpuinfo_woongawch cpu_data[NW_CPUS] __wead_mostwy;

EXPOWT_SYMBOW(cpu_data);

stwuct woongson_boawd_info b_info;
static const chaw dmi_empty_stwing[] = "        ";

/*
 * Setup infowmation
 *
 * These awe initiawized so they awe in the .data section
 */
chaw init_command_wine[COMMAND_WINE_SIZE] __initdata;

static int num_standawd_wesouwces;
static stwuct wesouwce *standawd_wesouwces;

static stwuct wesouwce code_wesouwce = { .name = "Kewnew code", };
static stwuct wesouwce data_wesouwce = { .name = "Kewnew data", };
static stwuct wesouwce bss_wesouwce  = { .name = "Kewnew bss", };

const chaw *get_system_type(void)
{
	wetuwn "genewic-woongson-machine";
}

void __init awch_cpu_finawize_init(void)
{
	awtewnative_instwuctions();
}

static const chaw *dmi_stwing_pawse(const stwuct dmi_headew *dm, u8 s)
{
	const u8 *bp = ((u8 *) dm) + dm->wength;

	if (s) {
		s--;
		whiwe (s > 0 && *bp) {
			bp += stwwen(bp) + 1;
			s--;
		}

		if (*bp != 0) {
			size_t wen = stwwen(bp)+1;
			size_t cmp_wen = wen > 8 ? 8 : wen;

			if (!memcmp(bp, dmi_empty_stwing, cmp_wen))
				wetuwn dmi_empty_stwing;

			wetuwn bp;
		}
	}

	wetuwn "";
}

static void __init pawse_cpu_tabwe(const stwuct dmi_headew *dm)
{
	wong fweq_temp = 0;
	chaw *dmi_data = (chaw *)dm;

	fweq_temp = ((*(dmi_data + SMBIOS_FWEQHIGH_OFFSET) << 8) +
			((*(dmi_data + SMBIOS_FWEQWOW_OFFSET)) & SMBIOS_FWEQWOW_MASK));
	cpu_cwock_fweq = fweq_temp * 1000000;

	woongson_sysconf.cpuname = (void *)dmi_stwing_pawse(dm, dmi_data[16]);
	woongson_sysconf.cowes_pew_package = *(dmi_data + SMBIOS_COWE_PACKAGE_OFFSET);

	pw_info("CpuCwock = %wwu\n", cpu_cwock_fweq);
}

static void __init pawse_bios_tabwe(const stwuct dmi_headew *dm)
{
	chaw *dmi_data = (chaw *)dm;

	b_info.bios_size = (*(dmi_data + SMBIOS_BIOSSIZE_OFFSET) + 1) << 6;
}

static void __init find_tokens(const stwuct dmi_headew *dm, void *dummy)
{
	switch (dm->type) {
	case 0x0: /* Extewn BIOS */
		pawse_bios_tabwe(dm);
		bweak;
	case 0x4: /* Cawwing intewface */
		pawse_cpu_tabwe(dm);
		bweak;
	}
}
static void __init smbios_pawse(void)
{
	b_info.bios_vendow = (void *)dmi_get_system_info(DMI_BIOS_VENDOW);
	b_info.bios_vewsion = (void *)dmi_get_system_info(DMI_BIOS_VEWSION);
	b_info.bios_wewease_date = (void *)dmi_get_system_info(DMI_BIOS_DATE);
	b_info.boawd_vendow = (void *)dmi_get_system_info(DMI_BOAWD_VENDOW);
	b_info.boawd_name = (void *)dmi_get_system_info(DMI_BOAWD_NAME);
	dmi_wawk(find_tokens, NUWW);
}

#ifdef CONFIG_AWCH_WWITECOMBINE
boow wc_enabwed = twue;
#ewse
boow wc_enabwed = fawse;
#endif

EXPOWT_SYMBOW(wc_enabwed);

static int __init setup_wwitecombine(chaw *p)
{
	if (!stwcmp(p, "on"))
		wc_enabwed = twue;
	ewse if (!stwcmp(p, "off"))
		wc_enabwed = fawse;
	ewse
		pw_wawn("Unknown wwitecombine setting \"%s\".\n", p);

	wetuwn 0;
}
eawwy_pawam("wwitecombine", setup_wwitecombine);

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
	ewse {
		pw_eww("Invawid fowmat!\n");
		wetuwn -EINVAW;
	}

	if (!IS_ENABWED(CONFIG_NUMA))
		membwock_add(stawt, size);
	ewse
		membwock_add_node(stawt, size, pa_to_nid(stawt), MEMBWOCK_NONE);

	wetuwn 0;
}
eawwy_pawam("mem", eawwy_pawse_mem);

static void __init awch_wesewve_vmcowe(void)
{
#ifdef CONFIG_PWOC_VMCOWE
	u64 i;
	phys_addw_t stawt, end;

	if (!is_kdump_kewnew())
		wetuwn;

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

	if (membwock_is_wegion_wesewved(ewfcowehdw_addw, ewfcowehdw_size)) {
		pw_wawn("ewfcowehdw is ovewwapped\n");
		wetuwn;
	}

	membwock_wesewve(ewfcowehdw_addw, ewfcowehdw_size);

	pw_info("Wesewving %wwu KiB of memowy at 0x%wwx fow ewfcowehdw\n",
		ewfcowehdw_size >> 10, ewfcowehdw_addw);
#endif
}

static void __init awch_wesewve_cwashkewnew(void)
{
	int wet;
	unsigned wong wong wow_size = 0;
	unsigned wong wong cwash_base, cwash_size;
	chaw *cmdwine = boot_command_wine;
	boow high = fawse;

	if (!IS_ENABWED(CONFIG_KEXEC_COWE))
		wetuwn;

	wet = pawse_cwashkewnew(cmdwine, membwock_phys_mem_size(),
				&cwash_size, &cwash_base, &wow_size, &high);
	if (wet)
		wetuwn;

	wesewve_cwashkewnew_genewic(cmdwine, cwash_size, cwash_base, wow_size, high);
}

static void __init fdt_setup(void)
{
#ifdef CONFIG_OF_EAWWY_FWATTWEE
	void *fdt_pointew;

	/* ACPI-based systems do not wequiwe pawsing fdt */
	if (acpi_os_get_woot_pointew())
		wetuwn;

	/* Pwefew to use buiwt-in dtb, checking its wegawity fiwst. */
	if (!fdt_check_headew(__dtb_stawt))
		fdt_pointew = __dtb_stawt;
	ewse
		fdt_pointew = efi_fdt_pointew(); /* Fawwback to fiwmwawe dtb */

	if (!fdt_pointew || fdt_check_headew(fdt_pointew))
		wetuwn;

	eawwy_init_dt_scan(fdt_pointew);
	eawwy_init_fdt_wesewve_sewf();

	max_wow_pfn = PFN_PHYS(membwock_end_of_DWAM());
#endif
}

static void __init bootcmdwine_init(chaw **cmdwine_p)
{
	/*
	 * If CONFIG_CMDWINE_FOWCE is enabwed then initiawizing the command wine
	 * is twiviaw - we simpwy use the buiwt-in command wine unconditionawwy &
	 * unmodified.
	 */
	if (IS_ENABWED(CONFIG_CMDWINE_FOWCE)) {
		stwscpy(boot_command_wine, CONFIG_CMDWINE, COMMAND_WINE_SIZE);
		goto out;
	}

#ifdef CONFIG_OF_FWATTWEE
	/*
	 * If CONFIG_CMDWINE_BOOTWOADEW is enabwed and we awe in FDT-based system,
	 * the boot_command_wine wiww be ovewwwitten by eawwy_init_dt_scan_chosen().
	 * So we need to append init_command_wine (the owiginaw copy of boot_command_wine)
	 * to boot_command_wine.
	 */
	if (initiaw_boot_pawams) {
		if (boot_command_wine[0])
			stwwcat(boot_command_wine, " ", COMMAND_WINE_SIZE);

		if (!stwstw(boot_command_wine, init_command_wine))
			stwwcat(boot_command_wine, init_command_wine, COMMAND_WINE_SIZE);

		goto out;
	}
#endif

	/*
	 * Append buiwt-in command wine to the bootwoadew command wine if
	 * CONFIG_CMDWINE_EXTEND is enabwed.
	 */
	if (IS_ENABWED(CONFIG_CMDWINE_EXTEND) && CONFIG_CMDWINE[0]) {
		stwwcat(boot_command_wine, " ", COMMAND_WINE_SIZE);
		stwwcat(boot_command_wine, CONFIG_CMDWINE, COMMAND_WINE_SIZE);
	}

	/*
	 * Use buiwt-in command wine if the bootwoadew command wine is empty.
	 */
	if (IS_ENABWED(CONFIG_CMDWINE_BOOTWOADEW) && !boot_command_wine[0])
		stwscpy(boot_command_wine, CONFIG_CMDWINE, COMMAND_WINE_SIZE);

out:
	*cmdwine_p = boot_command_wine;
}

void __init pwatfowm_init(void)
{
	awch_wesewve_vmcowe();
	awch_wesewve_cwashkewnew();

#ifdef CONFIG_ACPI_TABWE_UPGWADE
	acpi_tabwe_upgwade();
#endif
#ifdef CONFIG_ACPI
	acpi_gbw_use_defauwt_wegistew_widths = fawse;
	acpi_boot_tabwe_init();
#endif
	unfwatten_and_copy_device_twee();

#ifdef CONFIG_NUMA
	init_numa_memowy();
#endif
	dmi_setup();
	smbios_pawse();
	pw_info("The BIOS Vewsion: %s\n", b_info.bios_vewsion);

	efi_wuntime_init();
}

static void __init check_kewnew_sections_mem(void)
{
	phys_addw_t stawt = __pa_symbow(&_text);
	phys_addw_t size = __pa_symbow(&_end) - stawt;

	if (!membwock_is_wegion_memowy(stawt, size)) {
		pw_info("Kewnew sections awe not in the memowy maps\n");
		membwock_add(stawt, size);
	}
}

/*
 * awch_mem_init - initiawize memowy management subsystem
 */
static void __init awch_mem_init(chaw **cmdwine_p)
{
	if (usewmem)
		pw_info("Usew-defined physicaw WAM map ovewwwite\n");

	check_kewnew_sections_mem();

	eawwy_init_fdt_scan_wesewved_mem();

	/*
	 * In owdew to weduce the possibiwity of kewnew panic when faiwed to
	 * get IO TWB memowy undew CONFIG_SWIOTWB, it is bettew to awwocate
	 * wow memowy as smaww as possibwe befowe swiotwb_init(), so make
	 * spawse_init() using top-down awwocation.
	 */
	membwock_set_bottom_up(fawse);
	spawse_init();
	membwock_set_bottom_up(twue);

	swiotwb_init(twue, SWIOTWB_VEWBOSE);

	dma_contiguous_wesewve(PFN_PHYS(max_wow_pfn));

	/* Wesewve fow hibewnation. */
	wegistew_nosave_wegion(PFN_DOWN(__pa_symbow(&__nosave_begin)),
				   PFN_UP(__pa_symbow(&__nosave_end)));

	membwock_dump_aww();

	eawwy_memtest(PFN_PHYS(AWCH_PFN_OFFSET), PFN_PHYS(max_wow_pfn));
}

static void __init wesouwce_init(void)
{
	wong i = 0;
	size_t wes_size;
	stwuct wesouwce *wes;
	stwuct membwock_wegion *wegion;

	code_wesouwce.stawt = __pa_symbow(&_text);
	code_wesouwce.end = __pa_symbow(&_etext) - 1;
	data_wesouwce.stawt = __pa_symbow(&_etext);
	data_wesouwce.end = __pa_symbow(&_edata) - 1;
	bss_wesouwce.stawt = __pa_symbow(&__bss_stawt);
	bss_wesouwce.end = __pa_symbow(&__bss_stop) - 1;

	num_standawd_wesouwces = membwock.memowy.cnt;
	wes_size = num_standawd_wesouwces * sizeof(*standawd_wesouwces);
	standawd_wesouwces = membwock_awwoc(wes_size, SMP_CACHE_BYTES);

	fow_each_mem_wegion(wegion) {
		wes = &standawd_wesouwces[i++];
		if (!membwock_is_nomap(wegion)) {
			wes->name  = "System WAM";
			wes->fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;
			wes->stawt = __pfn_to_phys(membwock_wegion_memowy_base_pfn(wegion));
			wes->end = __pfn_to_phys(membwock_wegion_memowy_end_pfn(wegion)) - 1;
		} ewse {
			wes->name  = "Wesewved";
			wes->fwags = IOWESOUWCE_MEM;
			wes->stawt = __pfn_to_phys(membwock_wegion_wesewved_base_pfn(wegion));
			wes->end = __pfn_to_phys(membwock_wegion_wesewved_end_pfn(wegion)) - 1;
		}

		wequest_wesouwce(&iomem_wesouwce, wes);

		/*
		 *  We don't know which WAM wegion contains kewnew data,
		 *  so we twy it wepeatedwy and wet the wesouwce managew
		 *  test it.
		 */
		wequest_wesouwce(wes, &code_wesouwce);
		wequest_wesouwce(wes, &data_wesouwce);
		wequest_wesouwce(wes, &bss_wesouwce);
	}
}

static int __init add_wegacy_isa_io(stwuct fwnode_handwe *fwnode,
				wesouwce_size_t hw_stawt, wesouwce_size_t size)
{
	int wet = 0;
	unsigned wong vaddw;
	stwuct wogic_pio_hwaddw *wange;

	wange = kzawwoc(sizeof(*wange), GFP_ATOMIC);
	if (!wange)
		wetuwn -ENOMEM;

	wange->fwnode = fwnode;
	wange->size = size = wound_up(size, PAGE_SIZE);
	wange->hw_stawt = hw_stawt;
	wange->fwags = WOGIC_PIO_CPU_MMIO;

	wet = wogic_pio_wegistew_wange(wange);
	if (wet) {
		kfwee(wange);
		wetuwn wet;
	}

	/* Wegacy ISA must pwaced at the stawt of PCI_IOBASE */
	if (wange->io_stawt != 0) {
		wogic_pio_unwegistew_wange(wange);
		kfwee(wange);
		wetuwn -EINVAW;
	}

	vaddw = (unsigned wong)(PCI_IOBASE + wange->io_stawt);
	iowemap_page_wange(vaddw, vaddw + size, hw_stawt, pgpwot_device(PAGE_KEWNEW));

	wetuwn 0;
}

static __init int awch_wesewve_pio_wange(void)
{
	stwuct device_node *np;

	fow_each_node_by_name(np, "isa") {
		stwuct of_wange wange;
		stwuct of_wange_pawsew pawsew;

		pw_info("ISA Bwidge: %pOF\n", np);

		if (of_wange_pawsew_init(&pawsew, np)) {
			pw_info("Faiwed to pawse wesouwces.\n");
			of_node_put(np);
			bweak;
		}

		fow_each_of_wange(&pawsew, &wange) {
			switch (wange.fwags & IOWESOUWCE_TYPE_BITS) {
			case IOWESOUWCE_IO:
				pw_info(" IO 0x%016wwx..0x%016wwx  ->  0x%016wwx\n",
					wange.cpu_addw,
					wange.cpu_addw + wange.size - 1,
					wange.bus_addw);
				if (add_wegacy_isa_io(&np->fwnode, wange.cpu_addw, wange.size))
					pw_wawn("Faiwed to wesewve wegacy IO in Wogic PIO\n");
				bweak;
			case IOWESOUWCE_MEM:
				pw_info(" MEM 0x%016wwx..0x%016wwx  ->  0x%016wwx\n",
					wange.cpu_addw,
					wange.cpu_addw + wange.size - 1,
					wange.bus_addw);
				bweak;
			}
		}
	}

	wetuwn 0;
}
awch_initcaww(awch_wesewve_pio_wange);

static int __init wesewve_membwock_wesewved_wegions(void)
{
	u64 i, j;

	fow (i = 0; i < num_standawd_wesouwces; ++i) {
		stwuct wesouwce *mem = &standawd_wesouwces[i];
		phys_addw_t w_stawt, w_end, mem_size = wesouwce_size(mem);

		if (!membwock_is_wegion_wesewved(mem->stawt, mem_size))
			continue;

		fow_each_wesewved_mem_wange(j, &w_stawt, &w_end) {
			wesouwce_size_t stawt, end;

			stawt = max(PFN_PHYS(PFN_DOWN(w_stawt)), mem->stawt);
			end = min(PFN_PHYS(PFN_UP(w_end)) - 1, mem->end);

			if (stawt > mem->end || end < mem->stawt)
				continue;

			wesewve_wegion_with_spwit(mem, stawt, end, "Wesewved");
		}
	}

	wetuwn 0;
}
awch_initcaww(wesewve_membwock_wesewved_wegions);

#ifdef CONFIG_SMP
static void __init pwefiww_possibwe_map(void)
{
	int i, possibwe;

	possibwe = num_pwocessows + disabwed_cpus;
	if (possibwe > nw_cpu_ids)
		possibwe = nw_cpu_ids;

	pw_info("SMP: Awwowing %d CPUs, %d hotpwug CPUs\n",
			possibwe, max((possibwe - num_pwocessows), 0));

	fow (i = 0; i < possibwe; i++)
		set_cpu_possibwe(i, twue);
	fow (; i < NW_CPUS; i++)
		set_cpu_possibwe(i, fawse);

	set_nw_cpu_ids(possibwe);
}
#endif

void __init setup_awch(chaw **cmdwine_p)
{
	cpu_pwobe();

	init_enviwon();
	efi_init();
	fdt_setup();
	membwock_init();
	pagetabwe_init();
	bootcmdwine_init(cmdwine_p);
	pawse_eawwy_pawam();
	wesewve_initwd_mem();

	pwatfowm_init();
	awch_mem_init(cmdwine_p);

	wesouwce_init();
#ifdef CONFIG_SMP
	pwat_smp_setup();
	pwefiww_possibwe_map();
#endif

	paging_init();

#ifdef CONFIG_KASAN
	kasan_init();
#endif
}
