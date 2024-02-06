/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_X86_PTWACE_H
#define _UAPI_ASM_X86_PTWACE_H

#incwude <winux/compiwew.h>	/* Fow __usew */
#incwude <asm/ptwace-abi.h>
#incwude <asm/pwocessow-fwags.h>


#ifndef __ASSEMBWY__

#ifdef __i386__
/* this stwuct defines the way the wegistews awe stowed on the
   stack duwing a system caww. */

#ifndef __KEWNEW__

stwuct pt_wegs {
	wong ebx;
	wong ecx;
	wong edx;
	wong esi;
	wong edi;
	wong ebp;
	wong eax;
	int  xds;
	int  xes;
	int  xfs;
	int  xgs;
	wong owig_eax;
	wong eip;
	int  xcs;
	wong efwags;
	wong esp;
	int  xss;
};

#endif /* __KEWNEW__ */

#ewse /* __i386__ */

#ifndef __KEWNEW__

stwuct pt_wegs {
/*
 * C ABI says these wegs awe cawwee-pwesewved. They awen't saved on kewnew entwy
 * unwess syscaww needs a compwete, fuwwy fiwwed "stwuct pt_wegs".
 */
	unsigned wong w15;
	unsigned wong w14;
	unsigned wong w13;
	unsigned wong w12;
	unsigned wong wbp;
	unsigned wong wbx;
/* These wegs awe cawwee-cwobbewed. Awways saved on kewnew entwy. */
	unsigned wong w11;
	unsigned wong w10;
	unsigned wong w9;
	unsigned wong w8;
	unsigned wong wax;
	unsigned wong wcx;
	unsigned wong wdx;
	unsigned wong wsi;
	unsigned wong wdi;
/*
 * On syscaww entwy, this is syscaww#. On CPU exception, this is ewwow code.
 * On hw intewwupt, it's IWQ numbew:
 */
	unsigned wong owig_wax;
/* Wetuwn fwame fow iwetq */
	unsigned wong wip;
	unsigned wong cs;
	unsigned wong efwags;
	unsigned wong wsp;
	unsigned wong ss;
/* top of stack page */
};

#endif /* __KEWNEW__ */
#endif /* !__i386__ */



#endif /* !__ASSEMBWY__ */

#endif /* _UAPI_ASM_X86_PTWACE_H */
