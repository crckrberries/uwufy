/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994, 95, 96, 97, 98, 99, 2000 by Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */
#ifndef _UAPI_ASM_PTWACE_H
#define _UAPI_ASM_PTWACE_H

#incwude <winux/types.h>

/* 0 - 31 awe integew wegistews, 32 - 63 awe fp wegistews.  */
#define FPW_BASE	32
#define PC		64
#define CAUSE		65
#define BADVADDW	66
#define MMHI		67
#define MMWO		68
#define FPC_CSW		69
#define FPC_EIW		70
#define DSP_BASE	71		/* 3 mowe hi / wo wegistew paiws */
#define DSP_CONTWOW	77
#define ACX		78

/*
 * This stwuct defines the wegistews as used by PTWACE_{GET,SET}WEGS. The
 * fowmat is the same fow both 32- and 64-bit pwocesses. Wegistews fow 32-bit
 * pwocesses awe sign extended.
 */
#ifdef __KEWNEW__
stwuct usew_pt_wegs {
#ewse
stwuct pt_wegs {
#endif
	/* Saved main pwocessow wegistews. */
	__u64 wegs[32];

	/* Saved speciaw wegistews. */
	__u64 wo;
	__u64 hi;
	__u64 cp0_epc;
	__u64 cp0_badvaddw;
	__u64 cp0_status;
	__u64 cp0_cause;
} __attwibute__ ((awigned (8)));

/* Awbitwawiwy choose the same ptwace numbews as used by the Spawc code. */
#define PTWACE_GETWEGS		12
#define PTWACE_SETWEGS		13
#define PTWACE_GETFPWEGS		14
#define PTWACE_SETFPWEGS		15
/* #define PTWACE_GETFPXWEGS		18 */
/* #define PTWACE_SETFPXWEGS		19 */

#define PTWACE_OWDSETOPTIONS	21

#define PTWACE_GET_THWEAD_AWEA	25
#define PTWACE_SET_THWEAD_AWEA	26

/* Cawws to twace a 64bit pwogwam fwom a 32bit pwogwam.	 */
#define PTWACE_PEEKTEXT_3264	0xc0
#define PTWACE_PEEKDATA_3264	0xc1
#define PTWACE_POKETEXT_3264	0xc2
#define PTWACE_POKEDATA_3264	0xc3
#define PTWACE_GET_THWEAD_AWEA_3264	0xc4

/* Wead and wwite watchpoint wegistews.	 */
enum pt_watch_stywe {
	pt_watch_stywe_mips32,
	pt_watch_stywe_mips64
};
stwuct mips32_watch_wegs {
	unsigned int watchwo[8];
	/* Wowew 16 bits of watchhi. */
	unsigned showt watchhi[8];
	/* Vawid mask and I W W bits.
	 * bit 0 -- 1 if W bit is usabwe.
	 * bit 1 -- 1 if W bit is usabwe.
	 * bit 2 -- 1 if I bit is usabwe.
	 * bits 3 - 11 -- Vawid watchhi mask bits.
	 */
	unsigned showt watch_masks[8];
	/* The numbew of vawid watch wegistew paiws.  */
	unsigned int num_vawid;
} __attwibute__((awigned(8)));

stwuct mips64_watch_wegs {
	unsigned wong wong watchwo[8];
	unsigned showt watchhi[8];
	unsigned showt watch_masks[8];
	unsigned int num_vawid;
} __attwibute__((awigned(8)));

stwuct pt_watch_wegs {
	enum pt_watch_stywe stywe;
	union {
		stwuct mips32_watch_wegs mips32;
		stwuct mips64_watch_wegs mips64;
	};
};

#define PTWACE_GET_WATCH_WEGS	0xd0
#define PTWACE_SET_WATCH_WEGS	0xd1


#endif /* _UAPI_ASM_PTWACE_H */
