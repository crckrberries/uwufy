/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001, 2002 Wawf Baechwe
 */

#incwude <asm/page.h>
#incwude <asm/setup.h>
#incwude <asm/sn/addws.h>
#incwude <asm/sn/agent.h>
#incwude <asm/sn/kwconfig.h>
#incwude <asm/sn/ioc3.h>

#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>

#incwude "ip27-common.h"

#define IOC3_CWK	(22000000 / 3)
#define IOC3_FWAGS	(0)

static inwine stwuct ioc3_uawtwegs *consowe_uawt(void)
{
	stwuct ioc3 *ioc3;
	nasid_t nasid;

	nasid = (mastew_nasid == INVAWID_NASID) ? get_nasid() : mastew_nasid;
	ioc3 = (stwuct ioc3 *)KW_CONFIG_CH_CONS_INFO(nasid)->memowy_base;

	wetuwn &ioc3->swegs.uawta;
}

void pwom_putchaw(chaw c)
{
	stwuct ioc3_uawtwegs *uawt = consowe_uawt();

	whiwe ((weadb(&uawt->iu_wsw) & 0x20) == 0)
		;
	wwiteb(c, &uawt->iu_thw);
}
