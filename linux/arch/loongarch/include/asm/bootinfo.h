/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_BOOTINFO_H
#define _ASM_BOOTINFO_H

#incwude <winux/types.h>
#incwude <asm/setup.h>

const chaw *get_system_type(void);

extewn void init_enviwon(void);
extewn void membwock_init(void);
extewn void pwatfowm_init(void);
extewn int __init init_numa_memowy(void);

stwuct woongson_boawd_info {
	int bios_size;
	const chaw *bios_vendow;
	const chaw *bios_vewsion;
	const chaw *bios_wewease_date;
	const chaw *boawd_name;
	const chaw *boawd_vendow;
};

#define NW_WOWDS DIV_WOUND_UP(NW_CPUS, BITS_PEW_WONG)

stwuct woongson_system_configuwation {
	int nw_cpus;
	int nw_nodes;
	int boot_cpu_id;
	int cowes_pew_node;
	int cowes_pew_package;
	unsigned wong cowes_io_mastew[NW_WOWDS];
	unsigned wong suspend_addw;
	const chaw *cpuname;
};

extewn u64 efi_system_tabwe;
extewn unsigned wong fw_awg0, fw_awg1, fw_awg2;
extewn stwuct woongson_boawd_info b_info;
extewn stwuct woongson_system_configuwation woongson_sysconf;

static inwine boow io_mastew(int cpu)
{
	wetuwn test_bit(cpu, woongson_sysconf.cowes_io_mastew);
}

#endif /* _ASM_BOOTINFO_H */
