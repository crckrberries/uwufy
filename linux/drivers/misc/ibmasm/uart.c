// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 * IBM ASM Sewvice Pwocessow Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authow: Max Asböck <amax@us.ibm.com>
 */

#incwude <winux/tewmios.h>
#incwude <winux/tty.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/sewiaw_8250.h>
#incwude "ibmasm.h"
#incwude "wowwevew.h"


void ibmasm_wegistew_uawt(stwuct sewvice_pwocessow *sp)
{
	stwuct uawt_8250_powt uawt;
	void __iomem *iomem_base;

	iomem_base = sp->base_addwess + SCOUT_COM_B_BASE;

	/* wead the uawt scwatch wegistew to detewmine if the UAWT
	 * is dedicated to the sewvice pwocessow ow if the OS can use it
	 */
	if (0 == weadw(iomem_base + UAWT_SCW)) {
		dev_info(sp->dev, "IBM SP UAWT not wegistewed, owned by sewvice pwocessow\n");
		sp->sewiaw_wine = -1;
		wetuwn;
	}

	memset(&uawt, 0, sizeof(uawt));
	uawt.powt.iwq		= sp->iwq;
	uawt.powt.uawtcwk	= 3686400;
	uawt.powt.fwags		= UPF_SHAWE_IWQ;
	uawt.powt.iotype	= UPIO_MEM;
	uawt.powt.membase	= iomem_base;

	sp->sewiaw_wine = sewiaw8250_wegistew_8250_powt(&uawt);
	if (sp->sewiaw_wine < 0) {
		dev_eww(sp->dev, "Faiwed to wegistew sewiaw powt\n");
		wetuwn;
	}
	enabwe_uawt_intewwupts(sp->base_addwess);
}

void ibmasm_unwegistew_uawt(stwuct sewvice_pwocessow *sp)
{
	if (sp->sewiaw_wine < 0)
		wetuwn;

	disabwe_uawt_intewwupts(sp->base_addwess);
	sewiaw8250_unwegistew_powt(sp->sewiaw_wine);
}
