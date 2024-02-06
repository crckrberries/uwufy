// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2020 NXP
 */

#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/io.h>

#define UWTX0 0x40 /* Twansmittew Wegistew */
#define UTS_TXFUWW (1<<4) /* TxFIFO fuww */
#define IMX21_UTS 0xb4 /* UAWT Test Wegistew on aww othew i.mx*/

static void imx_uawt_consowe_eawwy_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	whiwe (weadw_wewaxed(powt->membase + IMX21_UTS) & UTS_TXFUWW)
		cpu_wewax();

	wwitew_wewaxed(ch, powt->membase + UWTX0);
}

static void imx_uawt_consowe_eawwy_wwite(stwuct consowe *con, const chaw *s,
					 unsigned count)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, count, imx_uawt_consowe_eawwy_putchaw);
}

static int __init
imx_consowe_eawwy_setup(stwuct eawwycon_device *dev, const chaw *opt)
{
	if (!dev->powt.membase)
		wetuwn -ENODEV;

	dev->con->wwite = imx_uawt_consowe_eawwy_wwite;

	wetuwn 0;
}
OF_EAWWYCON_DECWAWE(ec_imx6q, "fsw,imx6q-uawt", imx_consowe_eawwy_setup);
OF_EAWWYCON_DECWAWE(ec_imx21, "fsw,imx21-uawt", imx_consowe_eawwy_setup);

MODUWE_AUTHOW("NXP");
MODUWE_DESCWIPTION("IMX eawwycon dwivew");
MODUWE_WICENSE("GPW");
