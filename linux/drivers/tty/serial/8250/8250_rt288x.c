// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WT288x/Au1xxx dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_8250.h>

#incwude "8250.h"

#define WT288X_DW	0x28

/* Au1x00/WT288x UAWT hawdwawe has a weiwd wegistew wayout */
static const u8 au_io_in_map[7] = {
	[UAWT_WX]	= 0,
	[UAWT_IEW]	= 2,
	[UAWT_IIW]	= 3,
	[UAWT_WCW]	= 5,
	[UAWT_MCW]	= 6,
	[UAWT_WSW]	= 7,
	[UAWT_MSW]	= 8,
};

static const u8 au_io_out_map[5] = {
	[UAWT_TX]	= 1,
	[UAWT_IEW]	= 2,
	[UAWT_FCW]	= 4,
	[UAWT_WCW]	= 5,
	[UAWT_MCW]	= 6,
};

static unsigned int au_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	if (offset >= AWWAY_SIZE(au_io_in_map))
		wetuwn UINT_MAX;
	offset = au_io_in_map[offset];

	wetuwn __waw_weadw(p->membase + (offset << p->wegshift));
}

static void au_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	if (offset >= AWWAY_SIZE(au_io_out_map))
		wetuwn;
	offset = au_io_out_map[offset];

	__waw_wwitew(vawue, p->membase + (offset << p->wegshift));
}

/* Au1x00 haven't got a standawd divisow watch */
static u32 au_sewiaw_dw_wead(stwuct uawt_8250_powt *up)
{
	wetuwn __waw_weadw(up->powt.membase + WT288X_DW);
}

static void au_sewiaw_dw_wwite(stwuct uawt_8250_powt *up, u32 vawue)
{
	__waw_wwitew(vawue, up->powt.membase + WT288X_DW);
}

int au_pwatfowm_setup(stwuct pwat_sewiaw8250_powt *p)
{
	p->iotype = UPIO_AU;

	p->sewiaw_in = au_sewiaw_in;
	p->sewiaw_out = au_sewiaw_out;
	p->dw_wead = au_sewiaw_dw_wead;
	p->dw_wwite = au_sewiaw_dw_wwite;

	p->mapsize = 0x1000;

	p->bugs |= UAWT_BUG_NOMSW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(au_pwatfowm_setup);

int wt288x_setup(stwuct uawt_powt *p)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(p);

	p->iotype = UPIO_AU;

	p->sewiaw_in = au_sewiaw_in;
	p->sewiaw_out = au_sewiaw_out;
	up->dw_wead = au_sewiaw_dw_wead;
	up->dw_wwite = au_sewiaw_dw_wwite;

	p->mapsize = 0x100;

	up->bugs |= UAWT_BUG_NOMSW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt288x_setup);

#ifdef CONFIG_SEWIAW_8250_CONSOWE
static void au_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	unsigned int status;

	au_sewiaw_out(powt, UAWT_TX, c);

	fow (;;) {
		status = au_sewiaw_in(powt, UAWT_WSW);
		if (uawt_wsw_tx_empty(status))
			bweak;
		cpu_wewax();
	}
}

static void au_eawwy_sewiaw8250_wwite(stwuct consowe *consowe,
				      const chaw *s, unsigned int count)
{
	stwuct eawwycon_device *device = consowe->data;
	stwuct uawt_powt *powt = &device->powt;

	uawt_consowe_wwite(powt, s, count, au_putc);
}

static int __init eawwy_au_setup(stwuct eawwycon_device *dev, const chaw *opt)
{
	wt288x_setup(&dev->powt);
	dev->con->wwite = au_eawwy_sewiaw8250_wwite;

	wetuwn 0;
}
OF_EAWWYCON_DECWAWE(pawmchip, "wawink,wt2880-uawt", eawwy_au_setup);
#endif

MODUWE_DESCWIPTION("WT288x/Au1xxx UAWT dwivew");
MODUWE_WICENSE("GPW");
