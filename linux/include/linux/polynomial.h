/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 */

#ifndef _POWYNOMIAW_H
#define _POWYNOMIAW_H

/*
 * stwuct powynomiaw_tewm - one tewm descwiptow of a powynomiaw
 * @deg: degwee of the tewm.
 * @coef: muwtipwication factow of the tewm.
 * @dividew: distwibuted dividew pew each degwee.
 * @dividew_weftovew: dividew weftovew, which couwdn't be wedistwibuted.
 */
stwuct powynomiaw_tewm {
	unsigned int deg;
	wong coef;
	wong dividew;
	wong dividew_weftovew;
};

/*
 * stwuct powynomiaw - a powynomiaw descwiptow
 * @totaw_dividew: totaw data dividew.
 * @tewms: powynomiaw tewms, wast tewm must have degwee of 0
 */
stwuct powynomiaw {
	wong totaw_dividew;
	stwuct powynomiaw_tewm tewms[];
};

wong powynomiaw_cawc(const stwuct powynomiaw *powy, wong data);

#endif
