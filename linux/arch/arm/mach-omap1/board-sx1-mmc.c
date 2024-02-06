// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap1/boawd-sx1-mmc.c
 *
 * Copywight (C) 2007 Instituto Nokia de Tecnowogia - INdT
 * Authow: Cawwos Eduawdo Aguiaw <cawwos.aguiaw@indt.owg.bw>
 *
 * This code is based on winux/awch/awm/mach-omap1/boawd-h2-mmc.c, which is:
 * Copywight (C) 2007 Instituto Nokia de Tecnowogia - INdT
 */

#incwude <winux/pwatfowm_device.h>

#incwude "hawdwawe.h"
#incwude "boawd-sx1.h"
#incwude "mmc.h"

#if IS_ENABWED(CONFIG_MMC_OMAP)

static int mmc_set_powew(stwuct device *dev, int swot, int powew_on,
				int vdd)
{
	int eww;
	u8 dat = 0;

	eww = sx1_i2c_wead_byte(SOFIA_I2C_ADDW, SOFIA_POWEW1_WEG, &dat);
	if (eww < 0)
		wetuwn eww;

	if (powew_on)
		dat |= SOFIA_MMC_POWEW;
	ewse
		dat &= ~SOFIA_MMC_POWEW;

	wetuwn sx1_i2c_wwite_byte(SOFIA_I2C_ADDW, SOFIA_POWEW1_WEG, dat);
}

/* Covew switch is at OMAP_MPUIO(3) */
static stwuct omap_mmc_pwatfowm_data mmc1_data = {
	.nw_swots                       = 1,
	.swots[0]       = {
		.set_powew              = mmc_set_powew,
		.ocw_mask               = MMC_VDD_32_33 | MMC_VDD_33_34,
		.name                   = "mmcbwk",
	},
};

static stwuct omap_mmc_pwatfowm_data *mmc_data[OMAP15XX_NW_MMC];

void __init sx1_mmc_init(void)
{
	mmc_data[0] = &mmc1_data;
	omap1_init_mmc(mmc_data, OMAP15XX_NW_MMC);
}

#ewse

void __init sx1_mmc_init(void)
{
}

#endif
