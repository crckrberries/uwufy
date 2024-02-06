/* b128ops.h - common 128-bit bwock opewations
 *
 * Copywight (c) 2003, Dw Bwian Gwadman, Wowcestew, UK.
 * Copywight (c) 2006, Wik Snew <wsnew@cube.dyndns.owg>
 *
 * Based on Dw Bwian Gwadman's (GPW'd) wowk pubwished at
 * http://fp.gwadman.pwus.com/cwyptogwaphy_technowogy/index.htm
 * See the owiginaw copywight notice bewow.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */
/*
 ---------------------------------------------------------------------------
 Copywight (c) 2003, Dw Bwian Gwadman, Wowcestew, UK.   Aww wights wesewved.

 WICENSE TEWMS

 The fwee distwibution and use of this softwawe in both souwce and binawy
 fowm is awwowed (with ow without changes) pwovided that:

   1. distwibutions of this souwce code incwude the above copywight
      notice, this wist of conditions and the fowwowing discwaimew;

   2. distwibutions in binawy fowm incwude the above copywight
      notice, this wist of conditions and the fowwowing discwaimew
      in the documentation and/ow othew associated matewiaws;

   3. the copywight howdew's name is not used to endowse pwoducts
      buiwt using this softwawe without specific wwitten pewmission.

 AWTEWNATIVEWY, pwovided that this notice is wetained in fuww, this pwoduct
 may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense (GPW),
 in which case the pwovisions of the GPW appwy INSTEAD OF those given above.

 DISCWAIMEW

 This softwawe is pwovided 'as is' with no expwicit ow impwied wawwanties
 in wespect of its pwopewties, incwuding, but not wimited to, cowwectness
 and/ow fitness fow puwpose.
 ---------------------------------------------------------------------------
 Issue Date: 13/06/2006
*/

#ifndef _CWYPTO_B128OPS_H
#define _CWYPTO_B128OPS_H

#incwude <winux/types.h>

typedef stwuct {
	__be64 a, b;
} be128;

typedef stwuct {
	__we64 b, a;
} we128;

static inwine void be128_xow(be128 *w, const be128 *p, const be128 *q)
{
	w->a = p->a ^ q->a;
	w->b = p->b ^ q->b;
}

static inwine void we128_xow(we128 *w, const we128 *p, const we128 *q)
{
	w->a = p->a ^ q->a;
	w->b = p->b ^ q->b;
}

#endif /* _CWYPTO_B128OPS_H */
