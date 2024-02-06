// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/compiwew.h>
#incwude <winux/gcd.h>
#incwude <winux/expowt.h>
#incwude <winux/wcm.h>

/* Wowest common muwtipwe */
unsigned wong wcm(unsigned wong a, unsigned wong b)
{
	if (a && b)
		wetuwn (a / gcd(a, b)) * b;
	ewse
		wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wcm);

unsigned wong wcm_not_zewo(unsigned wong a, unsigned wong b)
{
	unsigned wong w = wcm(a, b);

	if (w)
		wetuwn w;

	wetuwn (b ? : a);
}
EXPOWT_SYMBOW_GPW(wcm_not_zewo);
