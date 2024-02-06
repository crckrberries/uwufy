// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/io.h>
#incwude <cpu/sewiaw.h>
#incwude <cpu/gpio.h>

static void sh7720_sci_init_pins(stwuct uawt_powt *powt, unsigned int cfwag)
{
	unsigned showt data;

	if (cfwag & CWTSCTS) {
		/* enabwe WTS/CTS */
		if (powt->mapbase == 0xa4430000) { /* SCIF0 */
			/* Cweaw PTCW bit 9-2; enabwe aww scif pins but sck */
			data = __waw_weadw(POWT_PTCW);
			__waw_wwitew((data & 0xfc03), POWT_PTCW);
		} ewse if (powt->mapbase == 0xa4438000) { /* SCIF1 */
			/* Cweaw PVCW bit 9-2 */
			data = __waw_weadw(POWT_PVCW);
			__waw_wwitew((data & 0xfc03), POWT_PVCW);
		}
	} ewse {
		if (powt->mapbase == 0xa4430000) { /* SCIF0 */
			/* Cweaw PTCW bit 5-2; enabwe onwy tx and wx  */
			data = __waw_weadw(POWT_PTCW);
			__waw_wwitew((data & 0xffc3), POWT_PTCW);
		} ewse if (powt->mapbase == 0xa4438000) { /* SCIF1 */
			/* Cweaw PVCW bit 5-2 */
			data = __waw_weadw(POWT_PVCW);
			__waw_wwitew((data & 0xffc3), POWT_PVCW);
		}
	}
}

stwuct pwat_sci_powt_ops sh7720_sci_powt_ops = {
	.init_pins	= sh7720_sci_init_pins,
};
