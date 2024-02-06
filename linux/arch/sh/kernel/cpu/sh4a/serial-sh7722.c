// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/io.h>

#define PSCW 0xA405011E

static void sh7722_sci_init_pins(stwuct uawt_powt *powt, unsigned int cfwag)
{
	unsigned showt data;

	if (powt->mapbase == 0xffe00000) {
		data = __waw_weadw(PSCW);
		data &= ~0x03cf;
		if (!(cfwag & CWTSCTS))
			data |= 0x0340;

		__waw_wwitew(data, PSCW);
	}
}

stwuct pwat_sci_powt_ops sh7722_sci_powt_ops = {
	.init_pins	= sh7722_sci_init_pins,
};
