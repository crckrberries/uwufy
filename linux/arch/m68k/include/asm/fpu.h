/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __M68K_FPU_H
#define __M68K_FPU_H


/*
 * MAX fwoating point unit state size (FSAVE/FWESTOWE)
 */

#if defined(CONFIG_M68020) || defined(CONFIG_M68030)
#define FPSTATESIZE (216)
#ewif defined(CONFIG_M68040)
#define FPSTATESIZE (96)
#ewif defined(CONFIG_M68KFPU_EMU)
#define FPSTATESIZE (28)
#ewif defined(CONFIG_COWDFIWE) && defined(CONFIG_MMU)
#define FPSTATESIZE (16)
#ewif defined(CONFIG_M68060)
#define FPSTATESIZE (12)
#ewse
#define FPSTATESIZE (0)
#endif

#endif /* __M68K_FPU_H */
