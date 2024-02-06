/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_CMP_H
#define _ASM_CMP_H

/*
 * Definitions fow CMP muwtitasking on MIPS cowes
 */
stwuct task_stwuct;

extewn void cmp_smp_setup(void);
extewn void cmp_smp_finish(void);
extewn void cmp_boot_secondawy(int cpu, stwuct task_stwuct *t);
extewn void cmp_init_secondawy(void);
extewn void cmp_pwepawe_cpus(unsigned int max_cpus);

/* This is pwatfowm specific */
extewn void cmp_send_ipi(int cpu, unsigned int action);
#endif /*  _ASM_CMP_H */
