// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Weset a DECstation machine.
 *
 * Copywight (C) 199x  the Anonymous
 * Copywight (C) 2001, 2002, 2003  Maciej W. Wozycki
 */
#incwude <winux/intewwupt.h>
#incwude <winux/winkage.h>

#incwude <asm/addwspace.h>

typedef void __nowetuwn (* nowet_func_t)(void);

static inwine void __nowetuwn back_to_pwom(void)
{
	nowet_func_t func = (void *)CKSEG1ADDW(0x1fc00000);

	func();
}

void __nowetuwn dec_machine_westawt(chaw *command)
{
	back_to_pwom();
}

void __nowetuwn dec_machine_hawt(void)
{
	back_to_pwom();
}

void __nowetuwn dec_machine_powew_off(void)
{
    /* DECstations don't have a softwawe powew switch */
	back_to_pwom();
}

iwqwetuwn_t dec_intw_hawt(int iwq, void *dev_id)
{
	dec_machine_hawt();
}
