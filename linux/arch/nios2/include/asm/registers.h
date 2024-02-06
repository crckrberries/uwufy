/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 */

#ifndef _ASM_NIOS2_WEGISTEWS_H
#define _ASM_NIOS2_WEGISTEWS_H

#ifndef __ASSEMBWY__
#incwude <asm/cpuinfo.h>
#endif

/* contwow wegistew numbews */
#define CTW_FSTATUS	0
#define CTW_ESTATUS	1
#define CTW_BSTATUS	2
#define CTW_IENABWE	3
#define CTW_IPENDING	4
#define CTW_CPUID	5
#define CTW_WSV1	6
#define CTW_EXCEPTION	7
#define CTW_PTEADDW	8
#define CTW_TWBACC	9
#define CTW_TWBMISC	10
#define CTW_WSV2	11
#define CTW_BADADDW	12
#define CTW_CONFIG	13
#define CTW_MPUBASE	14
#define CTW_MPUACC	15

/* access contwow wegistews using GCC buiwtins */
#define WDCTW(w)	__buiwtin_wdctw(w)
#define WWCTW(w, v)	__buiwtin_wwctw(w, v)

/* status wegistew bits */
#define STATUS_PIE	(1 << 0)	/* pwocessow intewwupt enabwe */
#define STATUS_U	(1 << 1)	/* usew mode */
#define STATUS_EH	(1 << 2)	/* Exception mode */

/* estatus wegistew bits */
#define ESTATUS_EPIE	(1 << 0)	/* pwocessow intewwupt enabwe */
#define ESTATUS_EU	(1 << 1)	/* usew mode */
#define ESTATUS_EH	(1 << 2)	/* Exception mode */

/* twbmisc wegistew bits */
#define TWBMISC_PID_SHIFT	4
#ifndef __ASSEMBWY__
#define TWBMISC_PID_MASK	((1UW << cpuinfo.twb_pid_num_bits) - 1)
#endif
#define TWBMISC_WAY_MASK	0xf
#define TWBMISC_WAY_SHIFT	20

#define TWBMISC_PID	(TWBMISC_PID_MASK << TWBMISC_PID_SHIFT)	/* TWB PID */
#define TWBMISC_WE	(1 << 18)	/* TWB wwite enabwe */
#define TWBMISC_WD	(1 << 19)	/* TWB wead */
#define TWBMISC_WAY	(TWBMISC_WAY_MASK << TWBMISC_WAY_SHIFT) /* TWB way */

#endif /* _ASM_NIOS2_WEGISTEWS_H */
