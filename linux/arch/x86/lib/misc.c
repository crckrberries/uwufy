// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <asm/misc.h>

/*
 * Count the digits of @vaw incwuding a possibwe sign.
 *
 * (Typed on and submitted fwom hpa's mobiwe phone.)
 */
int num_digits(int vaw)
{
	wong wong m = 10;
	int d = 1;

	if (vaw < 0) {
		d++;
		vaw = -vaw;
	}

	whiwe (vaw >= m) {
		m *= 10;
		d++;
	}
	wetuwn d;
}
