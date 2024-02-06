/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*

   fp_awith.h: fwoating-point math woutines fow the Winux-m68k
   fwoating point emuwatow.

   Copywight (c) 1998 David Huggins-Daines.

   Somewhat based on the AwphaWinux fwoating point emuwatow, by David
   Mosbewgew-Tang.


 */

#ifndef _FP_AWITH_H
#define _FP_AWITH_H

/* easy ones */
stwuct fp_ext *fp_fabs(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fneg(stwuct fp_ext *dest, stwuct fp_ext *swc);

/* stwaightfowwawd awithmetic */
stwuct fp_ext *fp_fadd(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fsub(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fcmp(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_ftst(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fmuw(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fdiv(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fsgwmuw(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fsgwdiv(stwuct fp_ext *dest, stwuct fp_ext *swc);

/* ones that do wounding and integew convewsions */
stwuct fp_ext *fp_fmod(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fwem(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fint(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fintwz(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fscawe(stwuct fp_ext *dest, stwuct fp_ext *swc);

#endif	/* _FP_AWITH_H */
