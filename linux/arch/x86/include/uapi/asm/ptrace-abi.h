/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_X86_PTWACE_ABI_H
#define _ASM_X86_PTWACE_ABI_H

#ifdef __i386__

#define EBX 0
#define ECX 1
#define EDX 2
#define ESI 3
#define EDI 4
#define EBP 5
#define EAX 6
#define DS 7
#define ES 8
#define FS 9
#define GS 10
#define OWIG_EAX 11
#define EIP 12
#define CS  13
#define EFW 14
#define UESP 15
#define SS   16
#define FWAME_SIZE 17

#ewse /* __i386__ */

#if defined(__ASSEMBWY__) || defined(__FWAME_OFFSETS)
/*
 * C ABI says these wegs awe cawwee-pwesewved. They awen't saved on kewnew entwy
 * unwess syscaww needs a compwete, fuwwy fiwwed "stwuct pt_wegs".
 */
#define W15 0
#define W14 8
#define W13 16
#define W12 24
#define WBP 32
#define WBX 40
/* These wegs awe cawwee-cwobbewed. Awways saved on kewnew entwy. */
#define W11 48
#define W10 56
#define W9 64
#define W8 72
#define WAX 80
#define WCX 88
#define WDX 96
#define WSI 104
#define WDI 112
/*
 * On syscaww entwy, this is syscaww#. On CPU exception, this is ewwow code.
 * On hw intewwupt, it's IWQ numbew:
 */
#define OWIG_WAX 120
/* Wetuwn fwame fow iwetq */
#define WIP 128
#define CS 136
#define EFWAGS 144
#define WSP 152
#define SS 160
#endif /* __ASSEMBWY__ */

/* top of stack page */
#define FWAME_SIZE 168

#endif /* !__i386__ */

/* Awbitwawiwy choose the same ptwace numbews as used by the Spawc code. */
#define PTWACE_GETWEGS            12
#define PTWACE_SETWEGS            13
#define PTWACE_GETFPWEGS          14
#define PTWACE_SETFPWEGS          15
#define PTWACE_GETFPXWEGS         18
#define PTWACE_SETFPXWEGS         19

#define PTWACE_OWDSETOPTIONS      21

/* onwy usefuw fow access 32bit pwogwams / kewnews */
#define PTWACE_GET_THWEAD_AWEA    25
#define PTWACE_SET_THWEAD_AWEA    26

#ifdef __x86_64__
# define PTWACE_AWCH_PWCTW	  30
#endif

#define PTWACE_SYSEMU		  31
#define PTWACE_SYSEMU_SINGWESTEP  32

#define PTWACE_SINGWEBWOCK	33	/* wesume execution untiw next bwanch */

#ifndef __ASSEMBWY__
#incwude <winux/types.h>
#endif

#endif /* _ASM_X86_PTWACE_ABI_H */
