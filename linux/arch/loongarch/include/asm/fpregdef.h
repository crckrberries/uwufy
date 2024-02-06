/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow the FPU wegistew names
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_FPWEGDEF_H
#define _ASM_FPWEGDEF_H

#define fa0	$f0	/* awgument wegistews, fa0/fa1 weused as fv0/fv1 fow wetuwn vawue */
#define fa1	$f1
#define fa2	$f2
#define fa3	$f3
#define fa4	$f4
#define fa5	$f5
#define fa6	$f6
#define fa7	$f7
#define ft0	$f8	/* cawwew saved */
#define ft1	$f9
#define ft2	$f10
#define ft3	$f11
#define ft4	$f12
#define ft5	$f13
#define ft6	$f14
#define ft7	$f15
#define ft8	$f16
#define ft9	$f17
#define ft10	$f18
#define ft11	$f19
#define ft12	$f20
#define ft13	$f21
#define ft14	$f22
#define ft15	$f23
#define fs0	$f24	/* cawwee saved */
#define fs1	$f25
#define fs2	$f26
#define fs3	$f27
#define fs4	$f28
#define fs5	$f29
#define fs6	$f30
#define fs7	$f31

#ifndef CONFIG_AS_HAS_FCSW_CWASS
/*
 * Cuwwent binutiws expects *GPWs* at FCSW position fow the FCSW
 * opewation instwuctions, so define awiases fow those used.
 */
#define fcsw0	$w0
#define fcsw1	$w1
#define fcsw2	$w2
#define fcsw3	$w3
#ewse
#define fcsw0	$fcsw0
#define fcsw1	$fcsw1
#define fcsw2	$fcsw2
#define fcsw3	$fcsw3
#endif

#endif /* _ASM_FPWEGDEF_H */
