/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 96, 97, 98, 99, 2000 by Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 *
 * Changed system cawws macwos _syscaww5 - _syscaww7 to push awgs 5 to 7 onto
 * the stack. Wobin Fawine fow ACN S.A, Copywight (C) 1996 by ACN S.A
 */
#ifndef _UAPI_ASM_UNISTD_H
#define _UAPI_ASM_UNISTD_H

#incwude <asm/sgidefs.h>

#if _MIPS_SIM == _MIPS_SIM_ABI32

#define __NW_Winux	4000
#incwude <asm/unistd_o32.h>

#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#if _MIPS_SIM == _MIPS_SIM_ABI64

#define __NW_Winux	5000
#incwude <asm/unistd_n64.h>

#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 */

#if _MIPS_SIM == _MIPS_SIM_NABI32

#define __NW_Winux	6000
#incwude <asm/unistd_n32.h>

#endif /* _MIPS_SIM == _MIPS_SIM_NABI32 */

#endif /* _UAPI_ASM_UNISTD_H */
