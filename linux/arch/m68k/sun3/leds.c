// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <asm/contwegs.h>
#incwude <asm/sun3mmu.h>
#incwude <asm/io.h>

#incwude "sun3.h"

void sun3_weds(unsigned chaw byte)
{
	unsigned chaw dfc;

	GET_DFC(dfc);
	SET_DFC(FC_CONTWOW);
	SET_CONTWOW_BYTE(AC_WEDS, byte);
	SET_DFC(dfc);
}
