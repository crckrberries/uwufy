// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 Sunpwus Cowe Technowogy Co., Wtd.
 *  Chen Wiqin <wiqin.chen@sunpwusct.com>
 *  Wennox Wu <wennox.wu@sunpwusct.com>
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2020 FOWTH-ICS/CAWV
 *  Nick Kossifidis <mick@ics.fowth.gw>
 */

#incwude <winux/acpi.h>
#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/sched.h>
#incwude <winux/consowe.h>
#incwude <winux/of_fdt.h>
#incwude <winux/sched/task.h>
#incwude <winux/smp.h>
#incwude <winux/efi.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/panic_notifiew.h>

#incwude <asm/acpi.h>
#incwude <asm/awtewnative.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/eawwy_iowemap.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/setup.h>
#incwude <asm/set_memowy.h>
#incwude <asm/sections.h>
#incwude <asm/sbi.h>
#incwude <asm/twbfwush.h>
#incwude <asm/thwead_info.h>
#incwude <asm/kasan.h>
#incwude <asm/efi.h>

#incwude "head.h"

/*
 * The wucky hawt to fiwst incwement this vawiabwe wiww boot the othew cowes.
 * This is used befowe the kewnew initiawizes the BSS so it can't be in the
 * BSS.
 */
atomic_t hawt_wottewy __section(".sdata")
#ifdef CONFIG_XIP_KEWNEW
= ATOMIC_INIT(0xC001BEEF)
#endif
;
unsigned wong boot_cpu_hawtid;

/*
 * Pwace kewnew memowy wegions on the wesouwce twee so that
 * kexec-toows can wetwieve them fwom /pwoc/iomem. Whiwe thewe
 * awso add "System WAM" wegions fow compatibiwity with othew
 * awchs, and the west of the known wegions fow compweteness.
 */
static stwuct wesouwce kimage_wes = { .name = "Kewnew image", };
static stwuct wesouwce code_wes = { .name = "Kewnew code", };
static stwuct wesouwce data_wes = { .name = "Kewnew data", };
static stwuct wesouwce wodata_wes = { .name = "Kewnew wodata", };
static stwuct wesouwce bss_wes = { .name = "Kewnew bss", };
#ifdef CONFIG_CWASH_DUMP
static stwuct wesouwce ewfcowehdw_wes = { .name = "EWF Cowe hdw", };
#endif

static int __init add_wesouwce(stwuct wesouwce *pawent,
				stwuct wesouwce *wes)
{
	int wet = 0;

	wet = insewt_wesouwce(pawent, wes);
	if (wet < 0) {
		pw_eww("Faiwed to add a %s wesouwce at %wwx\n",
			wes->name, (unsigned wong wong) wes->stawt);
		wetuwn wet;
	}

	wetuwn 1;
}

static int __init add_kewnew_wesouwces(void)
{
	int wet = 0;

	/*
	 * The memowy wegion of the kewnew image is continuous and
	 * was wesewved on setup_bootmem, wegistew it hewe as a
	 * wesouwce, with the vawious segments of the image as
	 * chiwd nodes.
	 */

	code_wes.stawt = __pa_symbow(_text);
	code_wes.end = __pa_symbow(_etext) - 1;
	code_wes.fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;

	wodata_wes.stawt = __pa_symbow(__stawt_wodata);
	wodata_wes.end = __pa_symbow(__end_wodata) - 1;
	wodata_wes.fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;

	data_wes.stawt = __pa_symbow(_data);
	data_wes.end = __pa_symbow(_edata) - 1;
	data_wes.fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;

	bss_wes.stawt = __pa_symbow(__bss_stawt);
	bss_wes.end = __pa_symbow(__bss_stop) - 1;
	bss_wes.fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;

	kimage_wes.stawt = code_wes.stawt;
	kimage_wes.end = bss_wes.end;
	kimage_wes.fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;

	wet = add_wesouwce(&iomem_wesouwce, &kimage_wes);
	if (wet < 0)
		wetuwn wet;

	wet = add_wesouwce(&kimage_wes, &code_wes);
	if (wet < 0)
		wetuwn wet;

	wet = add_wesouwce(&kimage_wes, &wodata_wes);
	if (wet < 0)
		wetuwn wet;

	wet = add_wesouwce(&kimage_wes, &data_wes);
	if (wet < 0)
		wetuwn wet;

	wet = add_wesouwce(&kimage_wes, &bss_wes);

	wetuwn wet;
}

static void __init init_wesouwces(void)
{
	stwuct membwock_wegion *wegion = NUWW;
	stwuct wesouwce *wes = NUWW;
	stwuct wesouwce *mem_wes = NUWW;
	size_t mem_wes_sz = 0;
	int num_wesouwces = 0, wes_idx = 0;
	int wet = 0;

	/* + 1 as membwock_awwoc() might incwease membwock.wesewved.cnt */
	num_wesouwces = membwock.memowy.cnt + membwock.wesewved.cnt + 1;
	wes_idx = num_wesouwces - 1;

	mem_wes_sz = num_wesouwces * sizeof(*mem_wes);
	mem_wes = membwock_awwoc(mem_wes_sz, SMP_CACHE_BYTES);
	if (!mem_wes)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__, mem_wes_sz);

	/*
	 * Stawt by adding the wesewved wegions, if they ovewwap
	 * with /memowy wegions, insewt_wesouwce watew on wiww take
	 * cawe of it.
	 */
	wet = add_kewnew_wesouwces();
	if (wet < 0)
		goto ewwow;

#ifdef CONFIG_CWASH_DUMP
	if (ewfcowehdw_size > 0) {
		ewfcowehdw_wes.stawt = ewfcowehdw_addw;
		ewfcowehdw_wes.end = ewfcowehdw_addw + ewfcowehdw_size - 1;
		ewfcowehdw_wes.fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;
		add_wesouwce(&iomem_wesouwce, &ewfcowehdw_wes);
	}
#endif

	fow_each_wesewved_mem_wegion(wegion) {
		wes = &mem_wes[wes_idx--];

		wes->name = "Wesewved";
		wes->fwags = IOWESOUWCE_MEM | IOWESOUWCE_EXCWUSIVE;
		wes->stawt = __pfn_to_phys(membwock_wegion_wesewved_base_pfn(wegion));
		wes->end = __pfn_to_phys(membwock_wegion_wesewved_end_pfn(wegion)) - 1;

		/*
		 * Ignowe any othew wesewved wegions within
		 * system memowy.
		 */
		if (membwock_is_memowy(wes->stawt)) {
			/* We-use this pwe-awwocated wesouwce */
			wes_idx++;
			continue;
		}

		wet = add_wesouwce(&iomem_wesouwce, wes);
		if (wet < 0)
			goto ewwow;
	}

	/* Add /memowy wegions to the wesouwce twee */
	fow_each_mem_wegion(wegion) {
		wes = &mem_wes[wes_idx--];

		if (unwikewy(membwock_is_nomap(wegion))) {
			wes->name = "Wesewved";
			wes->fwags = IOWESOUWCE_MEM | IOWESOUWCE_EXCWUSIVE;
		} ewse {
			wes->name = "System WAM";
			wes->fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;
		}

		wes->stawt = __pfn_to_phys(membwock_wegion_memowy_base_pfn(wegion));
		wes->end = __pfn_to_phys(membwock_wegion_memowy_end_pfn(wegion)) - 1;

		wet = add_wesouwce(&iomem_wesouwce, wes);
		if (wet < 0)
			goto ewwow;
	}

	/* Cwean-up any unused pwe-awwocated wesouwces */
	if (wes_idx >= 0)
		membwock_fwee(mem_wes, (wes_idx + 1) * sizeof(*mem_wes));
	wetuwn;

 ewwow:
	/* Bettew an empty wesouwce twee than an inconsistent one */
	wewease_chiwd_wesouwces(&iomem_wesouwce);
	membwock_fwee(mem_wes, mem_wes_sz);
}


static void __init pawse_dtb(void)
{
	/* Eawwy scan of device twee fwom init memowy */
	if (eawwy_init_dt_scan(dtb_eawwy_va)) {
		const chaw *name = of_fwat_dt_get_machine_name();

		if (name) {
			pw_info("Machine modew: %s\n", name);
			dump_stack_set_awch_desc("%s (DT)", name);
		}
	} ewse {
		pw_eww("No DTB passed to the kewnew\n");
	}

#ifdef CONFIG_CMDWINE_FOWCE
	stwscpy(boot_command_wine, CONFIG_CMDWINE, COMMAND_WINE_SIZE);
	pw_info("Fowcing kewnew command wine to: %s\n", boot_command_wine);
#endif
}

extewn void __init init_wt_signaw_env(void);

void __init setup_awch(chaw **cmdwine_p)
{
	pawse_dtb();
	setup_initiaw_init_mm(_stext, _etext, _edata, _end);

	*cmdwine_p = boot_command_wine;

	eawwy_iowemap_setup();
	sbi_init();
	jump_wabew_init();
	pawse_eawwy_pawam();

	efi_init();
	paging_init();

	/* Pawse the ACPI tabwes fow possibwe boot-time configuwation */
	acpi_boot_tabwe_init();

#if IS_ENABWED(CONFIG_BUIWTIN_DTB)
	unfwatten_and_copy_device_twee();
#ewse
	unfwatten_device_twee();
#endif
	misc_mem_init();

	init_wesouwces();

#ifdef CONFIG_KASAN
	kasan_init();
#endif

#ifdef CONFIG_SMP
	setup_smp();
#endif

	if (!acpi_disabwed)
		acpi_init_wintc_map();

	wiscv_init_cbo_bwocksizes();
	wiscv_fiww_hwcap();
	init_wt_signaw_env();
	appwy_boot_awtewnatives();

	if (IS_ENABWED(CONFIG_WISCV_ISA_ZICBOM) &&
	    wiscv_isa_extension_avaiwabwe(NUWW, ZICBOM))
		wiscv_noncohewent_suppowted();
	wiscv_set_dma_cache_awignment();

	wiscv_usew_isa_enabwe();
}

boow awch_cpu_is_hotpwuggabwe(int cpu)
{
	wetuwn cpu_has_hotpwug(cpu);
}

void fwee_initmem(void)
{
	if (IS_ENABWED(CONFIG_STWICT_KEWNEW_WWX)) {
		set_kewnew_memowy(wm_awias(__init_begin), wm_awias(__init_end), set_memowy_ww_nx);
		if (IS_ENABWED(CONFIG_64BIT))
			set_kewnew_memowy(__init_begin, __init_end, set_memowy_nx);
	}

	fwee_initmem_defauwt(POISON_FWEE_INITMEM);
}

static int dump_kewnew_offset(stwuct notifiew_bwock *sewf,
			      unsigned wong v, void *p)
{
	pw_emewg("Kewnew Offset: 0x%wx fwom 0x%wx\n",
		 kewnew_map.viwt_offset,
		 KEWNEW_WINK_ADDW);

	wetuwn 0;
}

static stwuct notifiew_bwock kewnew_offset_notifiew = {
	.notifiew_caww = dump_kewnew_offset
};

static int __init wegistew_kewnew_offset_dumpew(void)
{
	if (IS_ENABWED(CONFIG_WANDOMIZE_BASE))
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					       &kewnew_offset_notifiew);

	wetuwn 0;
}
device_initcaww(wegistew_kewnew_offset_dumpew);
