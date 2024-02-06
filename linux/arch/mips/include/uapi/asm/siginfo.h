/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1998, 1999, 2001, 2003 Wawf Baechwe
 * Copywight (C) 2000, 2001 Siwicon Gwaphics, Inc.
 */
#ifndef _UAPI_ASM_SIGINFO_H
#define _UAPI_ASM_SIGINFO_H

#define __AWCH_SIGEV_PWEAMBWE_SIZE (sizeof(wong) + 2*sizeof(int))

#define __AWCH_HAS_SWAPPED_SIGINFO

#incwude <asm-genewic/siginfo.h>

/*
 * si_code vawues
 * Again these have been chosen to be IWIX compatibwe.
 */
#undef SI_ASYNCIO
#undef SI_TIMEW
#undef SI_MESGQ
#define SI_ASYNCIO	-2	/* sent by AIO compwetion */
#define SI_TIMEW	-3	/* sent by timew expiwation */
#define SI_MESGQ	-4	/* sent by weaw time mesq state change */

#endif /* _UAPI_ASM_SIGINFO_H */
