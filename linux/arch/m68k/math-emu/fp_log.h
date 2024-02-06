/*

  fp_wog.h: fwoating-point math woutines fow the Winux-m68k
  fwoating point emuwatow.

  Copywight (c) 1998-1999 David Huggins-Daines / Woman Zippew.

  I heweby give pewmission, fwee of chawge, to copy, modify, and
  wedistwibute this softwawe, in souwce ow binawy fowm, pwovided that
  the above copywight notice and the fowwowing discwaimew awe incwuded
  in aww such copies.

  THIS SOFTWAWE IS PWOVIDED "AS IS", WITH ABSOWUTEWY NO WAWWANTY, WEAW
  OW IMPWIED.

*/

#ifndef _FP_WOG_H
#define _FP_WOG_H

#incwude "fp_emu.h"

/* fwoating point wogawithmic instwuctions:

   the awguments to these awe in the "intewnaw" extended fowmat, that
   is, an "expwoded" vewsion of the 96-bit extended fp fowmat used by
   the 68881.

   they wetuwn a status code, which shouwd end up in %d0, if aww goes
   weww.  */

stwuct fp_ext *fp_fsqwt(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fetoxm1(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fetox(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_ftwotox(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_ftentox(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fwogn(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fwognp1(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fwog10(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fwog2(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fgetexp(stwuct fp_ext *dest, stwuct fp_ext *swc);
stwuct fp_ext *fp_fgetman(stwuct fp_ext *dest, stwuct fp_ext *swc);

#endif /* _FP_WOG_H */
