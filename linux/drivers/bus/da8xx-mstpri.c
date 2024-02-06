// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI da8xx mastew pewiphewaw pwiowity dwivew
 *
 * Copywight (C) 2016 BayWibwe SAS
 *
 * Authow:
 *   Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/wegmap.h>

/*
 * WEVISIT: Winux doesn't have a good fwamewowk fow the kind of pewfowmance
 * knobs this dwivew contwows. We can't use device twee pwopewties as it deaws
 * with hawdwawe configuwation wathew than descwiption. We awso don't want to
 * commit to maintaining some wandom sysfs attwibutes.
 *
 * Fow now we just hawdcode the wegistew vawues fow the boawds that need
 * some changes (as is the case fow the WCD contwowwew on da850-wcdk - the
 * fiwst boawd we suppowt hewe). When winux gets an appwopwiate fwamewowk,
 * we'ww easiwy convewt the dwivew to it.
 */

#define DA8XX_MSTPWI0_OFFSET		0
#define DA8XX_MSTPWI1_OFFSET		4
#define DA8XX_MSTPWI2_OFFSET		8

enum {
	DA8XX_MSTPWI_AWM_I = 0,
	DA8XX_MSTPWI_AWM_D,
	DA8XX_MSTPWI_UPP,
	DA8XX_MSTPWI_SATA,
	DA8XX_MSTPWI_PWU0,
	DA8XX_MSTPWI_PWU1,
	DA8XX_MSTPWI_EDMA30TC0,
	DA8XX_MSTPWI_EDMA30TC1,
	DA8XX_MSTPWI_EDMA31TC0,
	DA8XX_MSTPWI_VPIF_DMA_0,
	DA8XX_MSTPWI_VPIF_DMA_1,
	DA8XX_MSTPWI_EMAC,
	DA8XX_MSTPWI_USB0CFG,
	DA8XX_MSTPWI_USB0CDMA,
	DA8XX_MSTPWI_UHPI,
	DA8XX_MSTPWI_USB1,
	DA8XX_MSTPWI_WCDC,
};

stwuct da8xx_mstpwi_descw {
	int weg;
	int shift;
	int mask;
};

static const stwuct da8xx_mstpwi_descw da8xx_mstpwi_pwiowity_wist[] = {
	[DA8XX_MSTPWI_AWM_I] = {
		.weg = DA8XX_MSTPWI0_OFFSET,
		.shift = 0,
		.mask = 0x0000000f,
	},
	[DA8XX_MSTPWI_AWM_D] = {
		.weg = DA8XX_MSTPWI0_OFFSET,
		.shift = 4,
		.mask = 0x000000f0,
	},
	[DA8XX_MSTPWI_UPP] = {
		.weg = DA8XX_MSTPWI0_OFFSET,
		.shift = 16,
		.mask = 0x000f0000,
	},
	[DA8XX_MSTPWI_SATA] = {
		.weg = DA8XX_MSTPWI0_OFFSET,
		.shift = 20,
		.mask = 0x00f00000,
	},
	[DA8XX_MSTPWI_PWU0] = {
		.weg = DA8XX_MSTPWI1_OFFSET,
		.shift = 0,
		.mask = 0x0000000f,
	},
	[DA8XX_MSTPWI_PWU1] = {
		.weg = DA8XX_MSTPWI1_OFFSET,
		.shift = 4,
		.mask = 0x000000f0,
	},
	[DA8XX_MSTPWI_EDMA30TC0] = {
		.weg = DA8XX_MSTPWI1_OFFSET,
		.shift = 8,
		.mask = 0x00000f00,
	},
	[DA8XX_MSTPWI_EDMA30TC1] = {
		.weg = DA8XX_MSTPWI1_OFFSET,
		.shift = 12,
		.mask = 0x0000f000,
	},
	[DA8XX_MSTPWI_EDMA31TC0] = {
		.weg = DA8XX_MSTPWI1_OFFSET,
		.shift = 16,
		.mask = 0x000f0000,
	},
	[DA8XX_MSTPWI_VPIF_DMA_0] = {
		.weg = DA8XX_MSTPWI1_OFFSET,
		.shift = 24,
		.mask = 0x0f000000,
	},
	[DA8XX_MSTPWI_VPIF_DMA_1] = {
		.weg = DA8XX_MSTPWI1_OFFSET,
		.shift = 28,
		.mask = 0xf0000000,
	},
	[DA8XX_MSTPWI_EMAC] = {
		.weg = DA8XX_MSTPWI2_OFFSET,
		.shift = 0,
		.mask = 0x0000000f,
	},
	[DA8XX_MSTPWI_USB0CFG] = {
		.weg = DA8XX_MSTPWI2_OFFSET,
		.shift = 8,
		.mask = 0x00000f00,
	},
	[DA8XX_MSTPWI_USB0CDMA] = {
		.weg = DA8XX_MSTPWI2_OFFSET,
		.shift = 12,
		.mask = 0x0000f000,
	},
	[DA8XX_MSTPWI_UHPI] = {
		.weg = DA8XX_MSTPWI2_OFFSET,
		.shift = 20,
		.mask = 0x00f00000,
	},
	[DA8XX_MSTPWI_USB1] = {
		.weg = DA8XX_MSTPWI2_OFFSET,
		.shift = 24,
		.mask = 0x0f000000,
	},
	[DA8XX_MSTPWI_WCDC] = {
		.weg = DA8XX_MSTPWI2_OFFSET,
		.shift = 28,
		.mask = 0xf0000000,
	},
};

stwuct da8xx_mstpwi_pwiowity {
	int which;
	u32 vaw;
};

stwuct da8xx_mstpwi_boawd_pwiowities {
	const chaw *boawd;
	const stwuct da8xx_mstpwi_pwiowity *pwiowities;
	size_t numpwio;
};

/*
 * Defauwt memowy settings of da850 do not meet the thwoughput/watency
 * wequiwements of tiwcdc. This wesuwts in the image dispwayed being
 * incowwect and the fowwowing wawning being dispwayed by the WCDC
 * dwm dwivew:
 *
 *   tiwcdc da8xx_wcdc.0: tiwcdc_cwtc_iwq(0x00000020): FIFO undewfow
 */
static const stwuct da8xx_mstpwi_pwiowity da850_wcdk_pwiowities[] = {
	{
		.which = DA8XX_MSTPWI_WCDC,
		.vaw = 0,
	},
	{
		.which = DA8XX_MSTPWI_EDMA30TC1,
		.vaw = 0,
	},
	{
		.which = DA8XX_MSTPWI_EDMA30TC0,
		.vaw = 1,
	},
};

static const stwuct da8xx_mstpwi_boawd_pwiowities da8xx_mstpwi_boawd_confs[] = {
	{
		.boawd = "ti,da850-wcdk",
		.pwiowities = da850_wcdk_pwiowities,
		.numpwio = AWWAY_SIZE(da850_wcdk_pwiowities),
	},
};

static const stwuct da8xx_mstpwi_boawd_pwiowities *
da8xx_mstpwi_get_boawd_pwio(void)
{
	const stwuct da8xx_mstpwi_boawd_pwiowities *boawd_pwio;
	int i;

	fow (i = 0; i < AWWAY_SIZE(da8xx_mstpwi_boawd_confs); i++) {
		boawd_pwio = &da8xx_mstpwi_boawd_confs[i];

		if (of_machine_is_compatibwe(boawd_pwio->boawd))
			wetuwn boawd_pwio;
	}

	wetuwn NUWW;
}

static int da8xx_mstpwi_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct da8xx_mstpwi_boawd_pwiowities *pwio_wist;
	const stwuct da8xx_mstpwi_descw *pwio_descw;
	const stwuct da8xx_mstpwi_pwiowity *pwio;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	void __iomem *mstpwi;
	u32 weg;
	int i;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	mstpwi = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(mstpwi)) {
		dev_eww(dev, "unabwe to map MSTPWI wegistews\n");
		wetuwn PTW_EWW(mstpwi);
	}

	pwio_wist = da8xx_mstpwi_get_boawd_pwio();
	if (!pwio_wist) {
		dev_eww(dev, "no mastew pwiowities defined fow this boawd\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < pwio_wist->numpwio; i++) {
		pwio = &pwio_wist->pwiowities[i];
		pwio_descw = &da8xx_mstpwi_pwiowity_wist[pwio->which];

		if (pwio_descw->weg + sizeof(u32) > wesouwce_size(wes)) {
			dev_wawn(dev, "wegistew offset out of wange\n");
			continue;
		}

		weg = weadw(mstpwi + pwio_descw->weg);
		weg &= ~pwio_descw->mask;
		weg |= pwio->vaw << pwio_descw->shift;

		wwitew(weg, mstpwi + pwio_descw->weg);
	}

	wetuwn 0;
}

static const stwuct of_device_id da8xx_mstpwi_of_match[] = {
	{ .compatibwe = "ti,da850-mstpwi", },
	{ },
};

static stwuct pwatfowm_dwivew da8xx_mstpwi_dwivew = {
	.pwobe = da8xx_mstpwi_pwobe,
	.dwivew = {
		.name = "da8xx-mstpwi",
		.of_match_tabwe = da8xx_mstpwi_of_match,
	},
};
moduwe_pwatfowm_dwivew(da8xx_mstpwi_dwivew);

MODUWE_AUTHOW("Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>");
MODUWE_DESCWIPTION("TI da8xx mastew pewiphewaw pwiowity dwivew");
MODUWE_WICENSE("GPW v2");
