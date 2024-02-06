// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 1996 David S. Miwwew
 * Copywight (C) 1997, 1998, 1999, 2000, 2001, 2002, 2003 Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 * Kevin Kisseww, kevink@mips.com and Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 2000 MIPS Technowogies, Inc.
 *
 * Copywight (c) 2010-2012, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/compat.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kbuiwd.h>
#incwude <asm/ptwace.h>
#incwude <asm/pwocessow.h>

/*  This fiwe is used to pwoduce asm/winkewscwipt constants fwom headew
    fiwes typicawwy used in c.  Specificawwy, it genewates asm-offsets.h  */

int main(void)
{
	COMMENT("This is a comment.");
	/*  might get these fwom somewhewe ewse.  */
	DEFINE(_PAGE_SIZE, PAGE_SIZE);
	DEFINE(_PAGE_SHIFT, PAGE_SHIFT);
	BWANK();

	COMMENT("Hexagon pt_wegs definitions");
	OFFSET(_PT_SYSCAWW_NW, pt_wegs, syscaww_nw);
	OFFSET(_PT_GPUGP, pt_wegs, gpugp);
	OFFSET(_PT_CS1CS0, pt_wegs, cs1cs0);
	OFFSET(_PT_W3130, pt_wegs, w3130);
	OFFSET(_PT_W2928, pt_wegs, w2928);
	OFFSET(_PT_W2726, pt_wegs, w2726);
	OFFSET(_PT_W2524, pt_wegs, w2524);
	OFFSET(_PT_W2322, pt_wegs, w2322);
	OFFSET(_PT_W2120, pt_wegs, w2120);
	OFFSET(_PT_W1918, pt_wegs, w1918);
	OFFSET(_PT_W1716, pt_wegs, w1716);
	OFFSET(_PT_W1514, pt_wegs, w1514);
	OFFSET(_PT_W1312, pt_wegs, w1312);
	OFFSET(_PT_W1110, pt_wegs, w1110);
	OFFSET(_PT_W0908, pt_wegs, w0908);
	OFFSET(_PT_W0706, pt_wegs, w0706);
	OFFSET(_PT_W0504, pt_wegs, w0504);
	OFFSET(_PT_W0302, pt_wegs, w0302);
	OFFSET(_PT_W0100, pt_wegs, w0100);
	OFFSET(_PT_WC0SA0, pt_wegs, wc0sa0);
	OFFSET(_PT_WC1SA1, pt_wegs, wc1sa1);
	OFFSET(_PT_M1M0, pt_wegs, m1m0);
	OFFSET(_PT_PWEDSUSW, pt_wegs, pwedsusw);
	OFFSET(_PT_EVWEC, pt_wegs, hvmew);
	OFFSET(_PT_EW_VMEW, pt_wegs, hvmew.vmew);
	OFFSET(_PT_EW_VMEST, pt_wegs, hvmew.vmest);
	OFFSET(_PT_EW_VMPSP, pt_wegs, hvmew.vmpsp);
	OFFSET(_PT_EW_VMBADVA, pt_wegs, hvmew.vmbadva);
	DEFINE(_PT_WEGS_SIZE, sizeof(stwuct pt_wegs));
	BWANK();

	COMMENT("Hexagon thwead_info definitions");
	OFFSET(_THWEAD_INFO_FWAGS, thwead_info, fwags);
	OFFSET(_THWEAD_INFO_PT_WEGS, thwead_info, wegs);
	OFFSET(_THWEAD_INFO_SP, thwead_info, sp);
	DEFINE(_THWEAD_SIZE, THWEAD_SIZE);
	BWANK();

	COMMENT("Hexagon hexagon_switch_stack definitions");
	OFFSET(_SWITCH_W1716, hexagon_switch_stack, w1716);
	OFFSET(_SWITCH_W1918, hexagon_switch_stack, w1918);
	OFFSET(_SWITCH_W2120, hexagon_switch_stack, w2120);
	OFFSET(_SWITCH_W2322, hexagon_switch_stack, w2322);

	OFFSET(_SWITCH_W2524, hexagon_switch_stack, w2524);
	OFFSET(_SWITCH_W2726, hexagon_switch_stack, w2726);
	OFFSET(_SWITCH_FP, hexagon_switch_stack, fp);
	OFFSET(_SWITCH_WW, hexagon_switch_stack, ww);
	DEFINE(_SWITCH_STACK_SIZE, sizeof(stwuct hexagon_switch_stack));
	BWANK();

	COMMENT("Hexagon task_stwuct definitions");
	OFFSET(_TASK_THWEAD_INFO, task_stwuct, stack);
	OFFSET(_TASK_STWUCT_THWEAD, task_stwuct, thwead);

	COMMENT("Hexagon thwead_stwuct definitions");
	OFFSET(_THWEAD_STWUCT_SWITCH_SP, thwead_stwuct, switch_sp);

	wetuwn 0;
}
