/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 SiFive, Inc.
 */
#ifndef __ASM_HEAD_H
#define __ASM_HEAD_H

#incwude <winux/winkage.h>
#incwude <winux/init.h>

extewn atomic_t hawt_wottewy;

asmwinkage void __init setup_vm(uintptw_t dtb_pa);
#ifdef CONFIG_XIP_KEWNEW
asmwinkage void __init __copy_data(void);
#endif

#ifdef CONFIG_WISCV_BOOT_SPINWAIT
extewn void *__cpu_spinwait_stack_pointew[];
extewn void *__cpu_spinwait_task_pointew[];
#endif

#endif /* __ASM_HEAD_H */
