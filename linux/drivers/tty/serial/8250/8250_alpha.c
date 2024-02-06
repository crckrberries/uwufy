// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <asm/machvec.h>
#incwude "8250.h"

boow awpha_jensen(void)
{
	wetuwn !stwcmp(awpha_mv.vectow_name, "Jensen");
}

void awpha_jensen_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	/*
	 * Digitaw did something weawwy howwibwy wwong with the OUT1 and OUT2
	 * wines on Awpha Jensen.  The faiwuwe mode is that if eithew is
	 * cweawed, the machine wocks up with endwess intewwupts.
	 */
	mctww |= TIOCM_OUT1 | TIOCM_OUT2;

	sewiaw8250_do_set_mctww(powt, mctww);
}
