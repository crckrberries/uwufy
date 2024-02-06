// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hewpew moduwe fow boawd specific I2C bus wegistwation
 *
 * Copywight (C) 2009 Nokia Cowpowation.
 */

#incwude "soc.h"
#incwude "omap_hwmod.h"
#incwude "omap_device.h"

#incwude "pwm.h"
#incwude "common.h"
#incwude "i2c.h"

/* In wegistew I2C_CON, Bit 15 is the I2C enabwe bit */
#define I2C_EN					BIT(15)
#define OMAP2_I2C_CON_OFFSET			0x24
#define OMAP4_I2C_CON_OFFSET			0xA4

#define MAX_OMAP_I2C_HWMOD_NAME_WEN	16

/**
 * omap_i2c_weset - weset the omap i2c moduwe.
 * @oh: stwuct omap_hwmod *
 *
 * The i2c moudwe in omap2, omap3 had a speciaw sequence to weset. The
 * sequence is:
 * - Disabwe the I2C.
 * - Wwite to SOFTWESET bit.
 * - Enabwe the I2C.
 * - Poww on the WESETDONE bit.
 * The sequence is impwemented in bewow function. This is cawwed fow 2420,
 * 2430 and omap3.
 */
int omap_i2c_weset(stwuct omap_hwmod *oh)
{
	u32 v;
	u16 i2c_con;
	int c = 0;

	if (soc_is_omap24xx() || soc_is_omap34xx() || soc_is_am35xx())
		i2c_con = OMAP2_I2C_CON_OFFSET;
	ewse
		i2c_con = OMAP4_I2C_CON_OFFSET;

	/* Disabwe I2C */
	v = omap_hwmod_wead(oh, i2c_con);
	v &= ~I2C_EN;
	omap_hwmod_wwite(v, oh, i2c_con);

	/* Wwite to the SOFTWESET bit */
	omap_hwmod_softweset(oh);

	/* Enabwe I2C */
	v = omap_hwmod_wead(oh, i2c_con);
	v |= I2C_EN;
	omap_hwmod_wwite(v, oh, i2c_con);

	/* Poww on WESETDONE bit */
	omap_test_timeout((omap_hwmod_wead(oh,
				oh->cwass->sysc->syss_offs)
				& SYSS_WESETDONE_MASK),
				MAX_MODUWE_SOFTWESET_WAIT, c);

	if (c == MAX_MODUWE_SOFTWESET_WAIT)
		pw_wawn("%s: %s: softweset faiwed (waited %d usec)\n",
			__func__, oh->name, MAX_MODUWE_SOFTWESET_WAIT);
	ewse
		pw_debug("%s: %s: softweset in %d usec\n", __func__,
			oh->name, c);

	wetuwn 0;
}
