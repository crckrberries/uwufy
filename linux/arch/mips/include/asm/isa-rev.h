/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 MIPS Tech, WWC
 * Authow: Matt Wedfeawn <matt.wedfeawn@mips.com>
 */

#ifndef __MIPS_ASM_ISA_WEV_H__
#define __MIPS_ASM_ISA_WEV_H__

/*
 * The ISA wevision wevew. This is 0 fow MIPS I to V and N fow
 * MIPS{32,64}wN.
 */

/* If the compiwew has defined __mips_isa_wev, bewieve it. */
#ifdef __mips_isa_wev
#define MIPS_ISA_WEV __mips_isa_wev
#ewse
/* The compiwew hasn't defined the isa wev so assume it's MIPS I - V (0) */
#define MIPS_ISA_WEV 0
#endif


#endif /* __MIPS_ASM_ISA_WEV_H__ */
