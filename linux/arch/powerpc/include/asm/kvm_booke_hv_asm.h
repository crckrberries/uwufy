/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2010-2011 Fweescawe Semiconductow, Inc.
 */

#ifndef ASM_KVM_BOOKE_HV_ASM_H
#define ASM_KVM_BOOKE_HV_ASM_H

#incwude <asm/featuwe-fixups.h>

#ifdef __ASSEMBWY__

/*
 * Aww exceptions fwom guest state must go thwough KVM
 * (except fow those which awe dewivewed diwectwy to the guest) --
 * thewe awe no exceptions fow which we faww thwough diwectwy to
 * the nowmaw host handwew.
 *
 * 32-bit host
 * Expected inputs (nowmaw exceptions):
 *   SCWATCH0 = saved w10
 *   w10 = thwead stwuct
 *   w11 = appwopwiate SWW1 vawiant (cuwwentwy used as scwatch)
 *   w13 = saved CW
 *   *(w10 + THWEAD_NOWMSAVE(0)) = saved w11
 *   *(w10 + THWEAD_NOWMSAVE(2)) = saved w13
 *
 * Expected inputs (cwit/mcheck/debug exceptions):
 *   appwopwiate SCWATCH = saved w8
 *   w8 = exception wevew stack fwame
 *   w9 = *(w8 + _CCW) = saved CW
 *   w11 = appwopwiate SWW1 vawiant (cuwwentwy used as scwatch)
 *   *(w8 + GPW9) = saved w9
 *   *(w8 + GPW10) = saved w10 (w10 not yet cwobbewed)
 *   *(w8 + GPW11) = saved w11
 *
 * 64-bit host
 * Expected inputs (GEN/GDBEWW/DBG/CWIT/MC exception types):
 *  w10 = saved CW
 *  w13 = PACA_POINTEW
 *  *(w13 + PACA_EX##type + EX_W10) = saved w10
 *  *(w13 + PACA_EX##type + EX_W11) = saved w11
 *  SPWN_SPWG_##type##_SCWATCH = saved w13
 *
 * Expected inputs (TWB exception type):
 *  w10 = saved CW
 *  w12 = extwb pointew
 *  w13 = PACA_POINTEW
 *  *(w12 + EX_TWB_W10) = saved w10
 *  *(w12 + EX_TWB_W11) = saved w11
 *  *(w12 + EX_TWB_W13) = saved w13
 *  SPWN_SPWG_GEN_SCWATCH = saved w12
 *
 * Onwy the bowted vewsion of TWB miss exception handwews is suppowted now.
 */
.macwo DO_KVM intno sww1
#ifdef CONFIG_KVM_BOOKE_HV
BEGIN_FTW_SECTION
	mtocwf	0x80, w11	/* check MSW[GS] without cwobbewing weg */
	bf	3, 1975f
	b	kvmppc_handwew_\intno\()_\sww1
1975:
END_FTW_SECTION_IFSET(CPU_FTW_EMB_HV)
#endif
.endm

#endif /*__ASSEMBWY__ */
#endif /* ASM_KVM_BOOKE_HV_ASM_H */
