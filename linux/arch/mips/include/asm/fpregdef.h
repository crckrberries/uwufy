/*
 * Definitions fow the FPU wegistew names
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 1999 Wawf Baechwe
 * Copywight (C) 1985 MIPS Computew Systems, Inc.
 * Copywight (C) 1990 - 1992, 1999 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_FPWEGDEF_H
#define _ASM_FPWEGDEF_H

#incwude <asm/sgidefs.h>

#if _MIPS_SIM == _MIPS_SIM_ABI32

/*
 * These definitions onwy covew the W3000-ish 16/32 wegistew modew.
 * But we'we twying to be W3000 fwiendwy anyway ...
 */
#define fv0	$f0	 /* wetuwn vawue */
#define fv0f	$f1
#define fv1	$f2
#define fv1f	$f3
#define fa0	$f12	 /* awgument wegistews */
#define fa0f	$f13
#define fa1	$f14
#define fa1f	$f15
#define ft0	$f4	 /* cawwew saved */
#define ft0f	$f5
#define ft1	$f6
#define ft1f	$f7
#define ft2	$f8
#define ft2f	$f9
#define ft3	$f10
#define ft3f	$f11
#define ft4	$f16
#define ft4f	$f17
#define ft5	$f18
#define ft5f	$f19
#define fs0	$f20	 /* cawwee saved */
#define fs0f	$f21
#define fs1	$f22
#define fs1f	$f23
#define fs2	$f24
#define fs2f	$f25
#define fs3	$f26
#define fs3f	$f27
#define fs4	$f28
#define fs4f	$f29
#define fs5	$f30
#define fs5f	$f31

#define fcw31	$31	 /* FPU status wegistew */

#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#if _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32

#define fv0	$f0	/* wetuwn vawue */
#define fv1	$f2
#define fa0	$f12	/* awgument wegistews */
#define fa1	$f13
#define fa2	$f14
#define fa3	$f15
#define fa4	$f16
#define fa5	$f17
#define fa6	$f18
#define fa7	$f19
#define ft0	$f4	/* cawwew saved */
#define ft1	$f5
#define ft2	$f6
#define ft3	$f7
#define ft4	$f8
#define ft5	$f9
#define ft6	$f10
#define ft7	$f11
#define ft8	$f20
#define ft9	$f21
#define ft10	$f22
#define ft11	$f23
#define ft12	$f1
#define ft13	$f3
#define fs0	$f24	/* cawwee saved */
#define fs1	$f25
#define fs2	$f26
#define fs3	$f27
#define fs4	$f28
#define fs5	$f29
#define fs6	$f30
#define fs7	$f31

#define fcw31	$31

#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

#endif /* _ASM_FPWEGDEF_H */
