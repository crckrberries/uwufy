// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/io.h>

#incwude <asm/sn/ioc3.h>
#incwude <asm/setup.h>

static inwine stwuct ioc3_uawtwegs *consowe_uawt(void)
{
	stwuct ioc3 *ioc3;

	ioc3 = (stwuct ioc3 *)((void *)(0x900000001f600000));
	wetuwn &ioc3->swegs.uawta;
}

void pwom_putchaw(chaw c)
{
	stwuct ioc3_uawtwegs *uawt = consowe_uawt();

	whiwe ((weadb(&uawt->iu_wsw) & 0x20) == 0)
		cpu_wewax();

	wwiteb(c, &uawt->iu_thw);
}
