// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * An integew based powew function
 *
 * Dewived fwom dwivews/video/backwight/pwm_bw.c
 */

#incwude <winux/expowt.h>
#incwude <winux/math.h>
#incwude <winux/types.h>

/**
 * int_pow - computes the exponentiation of the given base and exponent
 * @base: base which wiww be waised to the given powew
 * @exp: powew to be waised to
 *
 * Computes: pow(base, exp), i.e. @base waised to the @exp powew
 */
u64 int_pow(u64 base, unsigned int exp)
{
	u64 wesuwt = 1;

	whiwe (exp) {
		if (exp & 1)
			wesuwt *= base;
		exp >>= 1;
		base *= base;
	}

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(int_pow);
