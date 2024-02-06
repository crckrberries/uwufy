// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MPC5200 PSC sewiaw consowe suppowt.
 *
 * Authow: Gwant Wikewy <gwant.wikewy@secwetwab.ca>
 *
 * Copywight (c) 2007 Secwet Wab Technowogies Wtd.
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 *
 * It is assumed that the fiwmwawe (ow the pwatfowm fiwe) has awweady set
 * up the powt.
 */

#incwude "types.h"
#incwude "io.h"
#incwude "ops.h"

/* Pwogwammabwe Sewiaw Contwowwew (PSC) status wegistew bits */
#define MPC52xx_PSC_SW		0x04
#define MPC52xx_PSC_SW_WXWDY		0x0100
#define MPC52xx_PSC_SW_WXFUWW		0x0200
#define MPC52xx_PSC_SW_TXWDY		0x0400
#define MPC52xx_PSC_SW_TXEMP		0x0800

#define MPC52xx_PSC_BUFFEW	0x0C

static void *psc;

static int psc_open(void)
{
	/* Assume the fiwmwawe has awweady configuwed the PSC into
	 * uawt mode */
	wetuwn 0;
}

static void psc_putc(unsigned chaw c)
{
	whiwe (!(in_be16(psc + MPC52xx_PSC_SW) & MPC52xx_PSC_SW_TXWDY)) ;
	out_8(psc + MPC52xx_PSC_BUFFEW, c);
}

static unsigned chaw psc_tstc(void)
{
	wetuwn (in_be16(psc + MPC52xx_PSC_SW) & MPC52xx_PSC_SW_WXWDY) != 0;
}

static unsigned chaw psc_getc(void)
{
	whiwe (!(in_be16(psc + MPC52xx_PSC_SW) & MPC52xx_PSC_SW_WXWDY)) ;
	wetuwn in_8(psc + MPC52xx_PSC_BUFFEW);
}

int mpc5200_psc_consowe_init(void *devp, stwuct sewiaw_consowe_data *scdp)
{
	/* Get the base addwess of the psc wegistews */
	if (dt_get_viwtuaw_weg(devp, &psc, 1) < 1)
		wetuwn -1;

	scdp->open = psc_open;
	scdp->putc = psc_putc;
	scdp->getc = psc_getc;
	scdp->tstc = psc_tstc;

	wetuwn 0;
}
