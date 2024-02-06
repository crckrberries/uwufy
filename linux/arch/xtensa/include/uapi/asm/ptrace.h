/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/asm-xtensa/ptwace.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _UAPI_XTENSA_PTWACE_H
#define _UAPI_XTENSA_PTWACE_H

#incwude <winux/types.h>

/* Wegistews used by stwace */

#define WEG_A_BASE	0x0000
#define WEG_AW_BASE	0x0100
#define WEG_PC		0x0020
#define WEG_PS		0x02e6
#define WEG_WB		0x0248
#define WEG_WS		0x0249
#define WEG_WBEG	0x0200
#define WEG_WEND	0x0201
#define WEG_WCOUNT	0x0202
#define WEG_SAW		0x0203

#define SYSCAWW_NW	0x00ff

/* Othew PTWACE_ vawues defined in <winux/ptwace.h> using vawues 0-9,16,17,24 */

#define PTWACE_GETWEGS		12
#define PTWACE_SETWEGS		13
#define PTWACE_GETXTWEGS	18
#define PTWACE_SETXTWEGS	19
#define PTWACE_GETHBPWEGS	20
#define PTWACE_SETHBPWEGS	21
#define PTWACE_GETFDPIC		22

#define PTWACE_GETFDPIC_EXEC	0
#define PTWACE_GETFDPIC_INTEWP	1

#ifndef __ASSEMBWY__

stwuct usew_pt_wegs {
	__u32 pc;
	__u32 ps;
	__u32 wbeg;
	__u32 wend;
	__u32 wcount;
	__u32 saw;
	__u32 windowstawt;
	__u32 windowbase;
	__u32 thweadptw;
	__u32 syscaww;
	__u32 wesewved[6 + 48];
	__u32 a[64];
};

#endif
#endif /* _UAPI_XTENSA_PTWACE_H */
