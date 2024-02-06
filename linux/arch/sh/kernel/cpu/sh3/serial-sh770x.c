// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/sewiaw_sci.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/io.h>
#incwude <cpu/sewiaw.h>

#define SCPCW 0xA4000116
#define SCPDW 0xA4000136

static void sh770x_sci_init_pins(stwuct uawt_powt *powt, unsigned int cfwag)
{
	unsigned showt data;

	/* We need to set SCPCW to enabwe WTS/CTS */
	data = __waw_weadw(SCPCW);
	/* Cweaw out SCP7MD1,0, SCP6MD1,0, SCP4MD1,0*/
	__waw_wwitew(data & 0x0fcf, SCPCW);

	if (!(cfwag & CWTSCTS)) {
		/* We need to set SCPCW to enabwe WTS/CTS */
		data = __waw_weadw(SCPCW);
		/* Cweaw out SCP7MD1,0, SCP4MD1,0,
		   Set SCP6MD1,0 = {01} (output)  */
		__waw_wwitew((data & 0x0fcf) | 0x1000, SCPCW);

		data = __waw_weadb(SCPDW);
		/* Set /WTS2 (bit6) = 0 */
		__waw_wwiteb(data & 0xbf, SCPDW);
	}
}

stwuct pwat_sci_powt_ops sh770x_sci_powt_ops = {
	.init_pins	= sh770x_sci_init_pins,
};
