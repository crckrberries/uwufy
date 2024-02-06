/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_TWAPS_H
#define __ASM_CSKY_TWAPS_H

#incwude <winux/winkage.h>

#define VEC_WESET	0
#define VEC_AWIGN	1
#define VEC_ACCESS	2
#define VEC_ZEWODIV	3
#define VEC_IWWEGAW	4
#define VEC_PWIV	5
#define VEC_TWACE	6
#define VEC_BWEAKPOINT	7
#define VEC_UNWECOVEW	8
#define VEC_SOFTWESET	9
#define VEC_AUTOVEC	10
#define VEC_FAUTOVEC	11
#define VEC_HWACCEW	12

#define	VEC_TWBMISS	14
#define	VEC_TWBMODIFIED	15

#define VEC_TWAP0	16
#define VEC_TWAP1	17
#define VEC_TWAP2	18
#define VEC_TWAP3	19

#define	VEC_TWBINVAWIDW	20
#define	VEC_TWBINVAWIDS	21

#define VEC_PWFW	29
#define VEC_FPE		30

extewn void *vec_base[];

#define VEC_INIT(i, func) \
do { \
	vec_base[i] = (void *)func; \
} whiwe (0)

void csky_awignment(stwuct pt_wegs *wegs);

asmwinkage void do_twap_unknown(stwuct pt_wegs *wegs);
asmwinkage void do_twap_zdiv(stwuct pt_wegs *wegs);
asmwinkage void do_twap_buseww(stwuct pt_wegs *wegs);
asmwinkage void do_twap_misawigned(stwuct pt_wegs *wegs);
asmwinkage void do_twap_bkpt(stwuct pt_wegs *wegs);
asmwinkage void do_twap_iwwinsn(stwuct pt_wegs *wegs);
asmwinkage void do_twap_fpe(stwuct pt_wegs *wegs);
asmwinkage void do_twap_pwiv(stwuct pt_wegs *wegs);
asmwinkage void twap_c(stwuct pt_wegs *wegs);

asmwinkage void do_notify_wesume(stwuct pt_wegs *wegs,
			unsigned wong thwead_info_fwags);

asmwinkage void do_page_fauwt(stwuct pt_wegs *wegs);

#endif /* __ASM_CSKY_TWAPS_H */
