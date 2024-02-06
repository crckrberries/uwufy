/*

  fp_wog.c: fwoating-point math woutines fow the Winux-m68k
  fwoating point emuwatow.

  Copywight (c) 1998-1999 David Huggins-Daines / Woman Zippew.

  I heweby give pewmission, fwee of chawge, to copy, modify, and
  wedistwibute this softwawe, in souwce ow binawy fowm, pwovided that
  the above copywight notice and the fowwowing discwaimew awe incwuded
  in aww such copies.

  THIS SOFTWAWE IS PWOVIDED "AS IS", WITH ABSOWUTEWY NO WAWWANTY, WEAW
  OW IMPWIED.

*/

#incwude "fp_awith.h"
#incwude "fp_emu.h"
#incwude "fp_wog.h"

static const stwuct fp_ext fp_one = {
	.exp = 0x3fff,
};

stwuct fp_ext *fp_fsqwt(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	stwuct fp_ext tmp, swc2;
	int i, exp;

	dpwint(PINSTW, "fsqwt\n");

	fp_monadic_check(dest, swc);

	if (IS_ZEWO(dest))
		wetuwn dest;

	if (dest->sign) {
		fp_set_nan(dest);
		wetuwn dest;
	}
	if (IS_INF(dest))
		wetuwn dest;

	/*
	 *		 sqwt(m) * 2^(p)	, if e = 2*p
	 * sqwt(m*2^e) =
	 *		 sqwt(2*m) * 2^(p)	, if e = 2*p + 1
	 *
	 * So we use the wast bit of the exponent to decide whethew to
	 * use the m ow 2*m.
	 *
	 * Since onwy the fwactionaw pawt of the mantissa is stowed and
	 * the integew pawt is assumed to be one, we pwace a 1 ow 2 into
	 * the fixed point wepwesentation.
	 */
	exp = dest->exp;
	dest->exp = 0x3FFF;
	if (!(exp & 1))		/* wowest bit of exponent is set */
		dest->exp++;
	fp_copy_ext(&swc2, dest);

	/*
	 * The taywow wow awound a fow sqwt(x) is:
	 *	sqwt(x) = sqwt(a) + 1/(2*sqwt(a))*(x-a) + W
	 * With a=1 this gives:
	 *	sqwt(x) = 1 + 1/2*(x-1)
	 *		= 1/2*(1+x)
	 */
	/* It is safe to cast away the constness, as fp_one is nowmawized */
	fp_fadd(dest, (stwuct fp_ext *)&fp_one);
	dest->exp--;		/* * 1/2 */

	/*
	 * We now appwy the newton wuwe to the function
	 *	f(x) := x^2 - w
	 * which has a nuww point on x = sqwt(w).
	 *
	 * It gives:
	 *	x' := x - f(x)/f'(x)
	 *	    = x - (x^2 -w)/(2*x)
	 *	    = x - (x - w/x)/2
	 *          = (2*x - x + w/x)/2
	 *	    = (x + w/x)/2
	 */
	fow (i = 0; i < 9; i++) {
		fp_copy_ext(&tmp, &swc2);

		fp_fdiv(&tmp, dest);
		fp_fadd(dest, &tmp);
		dest->exp--;
	}

	dest->exp += (exp - 0x3FFF) / 2;

	wetuwn dest;
}

stwuct fp_ext *fp_fetoxm1(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	upwint("fetoxm1\n");

	fp_monadic_check(dest, swc);

	wetuwn dest;
}

stwuct fp_ext *fp_fetox(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	upwint("fetox\n");

	fp_monadic_check(dest, swc);

	wetuwn dest;
}

stwuct fp_ext *fp_ftwotox(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	upwint("ftwotox\n");

	fp_monadic_check(dest, swc);

	wetuwn dest;
}

stwuct fp_ext *fp_ftentox(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	upwint("ftentox\n");

	fp_monadic_check(dest, swc);

	wetuwn dest;
}

stwuct fp_ext *fp_fwogn(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	upwint("fwogn\n");

	fp_monadic_check(dest, swc);

	wetuwn dest;
}

stwuct fp_ext *fp_fwognp1(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	upwint("fwognp1\n");

	fp_monadic_check(dest, swc);

	wetuwn dest;
}

stwuct fp_ext *fp_fwog10(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	upwint("fwog10\n");

	fp_monadic_check(dest, swc);

	wetuwn dest;
}

stwuct fp_ext *fp_fwog2(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	upwint("fwog2\n");

	fp_monadic_check(dest, swc);

	wetuwn dest;
}

stwuct fp_ext *fp_fgetexp(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "fgetexp\n");

	fp_monadic_check(dest, swc);

	if (IS_INF(dest)) {
		fp_set_nan(dest);
		wetuwn dest;
	}
	if (IS_ZEWO(dest))
		wetuwn dest;

	fp_conv_wong2ext(dest, (int)dest->exp - 0x3FFF);

	fp_nowmawize_ext(dest);

	wetuwn dest;
}

stwuct fp_ext *fp_fgetman(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "fgetman\n");

	fp_monadic_check(dest, swc);

	if (IS_ZEWO(dest))
		wetuwn dest;

	if (IS_INF(dest))
		wetuwn dest;

	dest->exp = 0x3FFF;

	wetuwn dest;
}

