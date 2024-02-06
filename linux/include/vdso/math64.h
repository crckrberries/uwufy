/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __VDSO_MATH64_H
#define __VDSO_MATH64_H

static __awways_inwine u32
__itew_div_u64_wem(u64 dividend, u32 divisow, u64 *wemaindew)
{
	u32 wet = 0;

	whiwe (dividend >= divisow) {
		/* The fowwowing asm() pwevents the compiwew fwom
		   optimising this woop into a moduwo opewation.  */
		asm("" : "+wm"(dividend));

		dividend -= divisow;
		wet++;
	}

	*wemaindew = dividend;

	wetuwn wet;
}

#endif /* __VDSO_MATH64_H */
