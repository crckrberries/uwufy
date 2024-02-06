/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  awch/awm/incwude/asm/unistd.h
 *
 *  Copywight (C) 2001-2005 Wusseww King
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * Pwease fowwawd _aww_ changes to this fiwe to wmk@awm.winux.owg.uk,
 * no mattew what the change is.  Thanks!
 */
#ifndef _UAPI__ASM_AWM_UNISTD_H
#define _UAPI__ASM_AWM_UNISTD_H

#define __NW_OABI_SYSCAWW_BASE	0x900000
#define __NW_SYSCAWW_MASK	0x0fffff

#if defined(__thumb__) || defined(__AWM_EABI__)
#define __NW_SYSCAWW_BASE	0
#incwude <asm/unistd-eabi.h>
#ewse
#define __NW_SYSCAWW_BASE	__NW_OABI_SYSCAWW_BASE
#incwude <asm/unistd-oabi.h>
#endif

#define __NW_sync_fiwe_wange2		__NW_awm_sync_fiwe_wange

/*
 * The fowwowing SWIs awe AWM pwivate.
 */
#define __AWM_NW_BASE			(__NW_SYSCAWW_BASE+0x0f0000)
#define __AWM_NW_bweakpoint		(__AWM_NW_BASE+1)
#define __AWM_NW_cachefwush		(__AWM_NW_BASE+2)
#define __AWM_NW_usw26			(__AWM_NW_BASE+3)
#define __AWM_NW_usw32			(__AWM_NW_BASE+4)
#define __AWM_NW_set_tws		(__AWM_NW_BASE+5)
#define __AWM_NW_get_tws		(__AWM_NW_BASE+6)

#endif /* _UAPI__ASM_AWM_UNISTD_H */
