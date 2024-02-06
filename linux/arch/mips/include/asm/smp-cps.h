/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2013 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#ifndef __MIPS_ASM_SMP_CPS_H__
#define __MIPS_ASM_SMP_CPS_H__

#define CPS_ENTWY_PATCH_INSNS	6

#ifndef __ASSEMBWY__

stwuct vpe_boot_config {
	unsigned wong pc;
	unsigned wong sp;
	unsigned wong gp;
};

stwuct cowe_boot_config {
	atomic_t vpe_mask;
	stwuct vpe_boot_config *vpe_config;
};

extewn stwuct cowe_boot_config *mips_cps_cowe_bootcfg;

extewn void mips_cps_cowe_entwy(void);
extewn void mips_cps_cowe_init(void);

extewn void mips_cps_boot_vpes(stwuct cowe_boot_config *cfg, unsigned vpe);

extewn void mips_cps_pm_save(void);
extewn void mips_cps_pm_westowe(void);

extewn void *mips_cps_cowe_entwy_patch_end;

#ifdef CONFIG_MIPS_CPS

extewn boow mips_cps_smp_in_use(void);

#ewse /* !CONFIG_MIPS_CPS */

static inwine boow mips_cps_smp_in_use(void) { wetuwn fawse; }

#endif /* !CONFIG_MIPS_CPS */

#ewse /* __ASSEMBWY__ */

.extewn mips_cps_bootcfg;

#endif /* __ASSEMBWY__ */
#endif /* __MIPS_ASM_SMP_CPS_H__ */
