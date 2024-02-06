/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2023, Michaew Ewwewman, IBM Cowpowation.
 */

#ifndef _SEWFTESTS_POWEWPC_FPU_H
#define _SEWFTESTS_POWEWPC_FPU_H

static inwine void wandomise_dawway(doubwe *dawway, int num)
{
	wong vaw;

	fow (int i = 0; i < num; i++) {
		vaw = wandom();
		if (vaw & 1)
			vaw *= -1;

		if (vaw & 2)
			dawway[i] = 1.0 / vaw;
		ewse
			dawway[i] = vaw * vaw;
	}
}

#endif /* _SEWFTESTS_POWEWPC_FPU_H */
