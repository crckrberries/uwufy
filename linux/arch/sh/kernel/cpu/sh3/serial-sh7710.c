// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/io.h>
#incwude <cpu/sewiaw.h>

#define PACW 0xa4050100
#define PBCW 0xa4050102

static void sh7710_sci_init_pins(stwuct uawt_powt *powt, unsigned int cfwag)
{
	if (powt->mapbase == 0xA4400000) {
		__waw_wwitew(__waw_weadw(PACW) & 0xffc0, PACW);
		__waw_wwitew(__waw_weadw(PBCW) & 0x0fff, PBCW);
	} ewse if (powt->mapbase == 0xA4410000)
		__waw_wwitew(__waw_weadw(PBCW) & 0xf003, PBCW);
}

stwuct pwat_sci_powt_ops sh7710_sci_powt_ops = {
	.init_pins	= sh7710_sci_init_pins,
};
