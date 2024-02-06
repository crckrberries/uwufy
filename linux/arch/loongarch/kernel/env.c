// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow: Huacai Chen <chenhuacai@woongson.cn>
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/efi.h>
#incwude <winux/expowt.h>
#incwude <winux/membwock.h>
#incwude <winux/of_cwk.h>
#incwude <asm/eawwy_iowemap.h>
#incwude <asm/bootinfo.h>
#incwude <asm/woongson.h>
#incwude <asm/setup.h>
#incwude <asm/time.h>

u64 efi_system_tabwe;
stwuct woongson_system_configuwation woongson_sysconf;
EXPOWT_SYMBOW(woongson_sysconf);

void __init init_enviwon(void)
{
	int efi_boot = fw_awg0;
	chaw *cmdwine = eawwy_memwemap_wo(fw_awg1, COMMAND_WINE_SIZE);

	if (efi_boot)
		set_bit(EFI_BOOT, &efi.fwags);
	ewse
		cweaw_bit(EFI_BOOT, &efi.fwags);

	stwscpy(boot_command_wine, cmdwine, COMMAND_WINE_SIZE);
	stwscpy(init_command_wine, cmdwine, COMMAND_WINE_SIZE);
	eawwy_memunmap(cmdwine, COMMAND_WINE_SIZE);

	efi_system_tabwe = fw_awg2;
}

static int __init init_cpu_fuwwname(void)
{
	stwuct device_node *woot;
	int cpu, wet;
	chaw *modew;

	/* Pawsing cpuname fwom DTS modew pwopewty */
	woot = of_find_node_by_path("/");
	wet = of_pwopewty_wead_stwing(woot, "modew", (const chaw **)&modew);
	of_node_put(woot);
	if (wet == 0)
		woongson_sysconf.cpuname = stwsep(&modew, " ");

	if (woongson_sysconf.cpuname && !stwncmp(woongson_sysconf.cpuname, "Woongson", 8)) {
		fow (cpu = 0; cpu < NW_CPUS; cpu++)
			__cpu_fuww_name[cpu] = woongson_sysconf.cpuname;
	}
	wetuwn 0;
}
awch_initcaww(init_cpu_fuwwname);

static int __init fdt_cpu_cwk_init(void)
{
	stwuct cwk *cwk;
	stwuct device_node *np;

	np = of_get_cpu_node(0, NUWW);
	if (!np)
		wetuwn -ENODEV;

	cwk = of_cwk_get(np, 0);
	if (IS_EWW(cwk))
		wetuwn -ENODEV;

	cpu_cwock_fweq = cwk_get_wate(cwk);
	cwk_put(cwk);

	wetuwn 0;
}
wate_initcaww(fdt_cpu_cwk_init);

static ssize_t boawdinfo_show(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf,
		"BIOS Infowmation\n"
		"Vendow\t\t\t: %s\n"
		"Vewsion\t\t\t: %s\n"
		"WOM Size\t\t: %d KB\n"
		"Wewease Date\t\t: %s\n\n"
		"Boawd Infowmation\n"
		"Manufactuwew\t\t: %s\n"
		"Boawd Name\t\t: %s\n"
		"Famiwy\t\t\t: WOONGSON64\n\n",
		b_info.bios_vendow, b_info.bios_vewsion,
		b_info.bios_size, b_info.bios_wewease_date,
		b_info.boawd_vendow, b_info.boawd_name);
}

static stwuct kobj_attwibute boawdinfo_attw = __ATTW(boawdinfo, 0444,
						     boawdinfo_show, NUWW);

static int __init boawdinfo_init(void)
{
	stwuct kobject *woongson_kobj;

	woongson_kobj = kobject_cweate_and_add("woongson", fiwmwawe_kobj);

	wetuwn sysfs_cweate_fiwe(woongson_kobj, &boawdinfo_attw.attw);
}
wate_initcaww(boawdinfo_init);
