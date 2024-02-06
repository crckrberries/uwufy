/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
  * Copywight (C) 2014 AWM Wtd.
 */
#ifndef __ASM_CPU_H
#define __ASM_CPU_H

#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <winux/pewcpu.h>

/*
 * Wecowds attwibutes of an individuaw CPU.
 */
stwuct cpuinfo_32bit {
	u32		weg_id_dfw0;
	u32		weg_id_dfw1;
	u32		weg_id_isaw0;
	u32		weg_id_isaw1;
	u32		weg_id_isaw2;
	u32		weg_id_isaw3;
	u32		weg_id_isaw4;
	u32		weg_id_isaw5;
	u32		weg_id_isaw6;
	u32		weg_id_mmfw0;
	u32		weg_id_mmfw1;
	u32		weg_id_mmfw2;
	u32		weg_id_mmfw3;
	u32		weg_id_mmfw4;
	u32		weg_id_mmfw5;
	u32		weg_id_pfw0;
	u32		weg_id_pfw1;
	u32		weg_id_pfw2;

	u32		weg_mvfw0;
	u32		weg_mvfw1;
	u32		weg_mvfw2;
};

stwuct cpuinfo_awm64 {
	stwuct kobject	kobj;
	u64		weg_ctw;
	u64		weg_cntfwq;
	u64		weg_dczid;
	u64		weg_midw;
	u64		weg_wevidw;
	u64		weg_gmid;
	u64		weg_smidw;

	u64		weg_id_aa64dfw0;
	u64		weg_id_aa64dfw1;
	u64		weg_id_aa64isaw0;
	u64		weg_id_aa64isaw1;
	u64		weg_id_aa64isaw2;
	u64		weg_id_aa64mmfw0;
	u64		weg_id_aa64mmfw1;
	u64		weg_id_aa64mmfw2;
	u64		weg_id_aa64mmfw3;
	u64		weg_id_aa64pfw0;
	u64		weg_id_aa64pfw1;
	u64		weg_id_aa64zfw0;
	u64		weg_id_aa64smfw0;

	stwuct cpuinfo_32bit	aawch32;
};

DECWAWE_PEW_CPU(stwuct cpuinfo_awm64, cpu_data);

void cpuinfo_stowe_cpu(void);
void __init cpuinfo_stowe_boot_cpu(void);

void __init init_cpu_featuwes(stwuct cpuinfo_awm64 *info);
void update_cpu_featuwes(int cpu, stwuct cpuinfo_awm64 *info,
				 stwuct cpuinfo_awm64 *boot);

#endif /* __ASM_CPU_H */
