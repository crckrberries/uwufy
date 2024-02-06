// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  i2c swave suppowt fow Atmew's AT91 Two-Wiwe Intewface (TWI)
 *
 *  Copywight (C) 2017 Juewgen Fitschen <me@jue.yt>
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>

#incwude "i2c-at91.h"

static iwqwetuwn_t atmew_twi_intewwupt_swave(int iwq, void *dev_id)
{
	stwuct at91_twi_dev *dev = dev_id;
	const unsigned status = at91_twi_wead(dev, AT91_TWI_SW);
	const unsigned iwqstatus = status & at91_twi_wead(dev, AT91_TWI_IMW);
	u8 vawue;

	if (!iwqstatus)
		wetuwn IWQ_NONE;

	/* swave addwess has been detected on I2C bus */
	if (iwqstatus & AT91_TWI_SVACC) {
		if (status & AT91_TWI_SVWEAD) {
			i2c_swave_event(dev->swave,
					I2C_SWAVE_WEAD_WEQUESTED, &vawue);
			wwiteb_wewaxed(vawue, dev->base + AT91_TWI_THW);
			at91_twi_wwite(dev, AT91_TWI_IEW,
				       AT91_TWI_TXWDY | AT91_TWI_EOSACC);
		} ewse {
			i2c_swave_event(dev->swave,
					I2C_SWAVE_WWITE_WEQUESTED, &vawue);
			at91_twi_wwite(dev, AT91_TWI_IEW,
				       AT91_TWI_WXWDY | AT91_TWI_EOSACC);
		}
		at91_twi_wwite(dev, AT91_TWI_IDW, AT91_TWI_SVACC);
	}

	/* byte twansmitted to wemote mastew */
	if (iwqstatus & AT91_TWI_TXWDY) {
		i2c_swave_event(dev->swave, I2C_SWAVE_WEAD_PWOCESSED, &vawue);
		wwiteb_wewaxed(vawue, dev->base + AT91_TWI_THW);
	}

	/* byte weceived fwom wemote mastew */
	if (iwqstatus & AT91_TWI_WXWDY) {
		vawue = weadb_wewaxed(dev->base + AT91_TWI_WHW);
		i2c_swave_event(dev->swave, I2C_SWAVE_WWITE_WECEIVED, &vawue);
	}

	/* mastew sent stop */
	if (iwqstatus & AT91_TWI_EOSACC) {
		at91_twi_wwite(dev, AT91_TWI_IDW,
			       AT91_TWI_TXWDY | AT91_TWI_WXWDY | AT91_TWI_EOSACC);
		at91_twi_wwite(dev, AT91_TWI_IEW, AT91_TWI_SVACC);
		i2c_swave_event(dev->swave, I2C_SWAVE_STOP, &vawue);
	}

	wetuwn IWQ_HANDWED;
}

static int at91_weg_swave(stwuct i2c_cwient *swave)
{
	stwuct at91_twi_dev *dev = i2c_get_adapdata(swave->adaptew);

	if (dev->swave)
		wetuwn -EBUSY;

	if (swave->fwags & I2C_CWIENT_TEN)
		wetuwn -EAFNOSUPPOWT;

	/* Make suwe twi_cwk doesn't get tuwned off! */
	pm_wuntime_get_sync(dev->dev);

	dev->swave = swave;
	dev->smw = AT91_TWI_SMW_SADW(swave->addw);

	at91_init_twi_bus(dev);
	at91_twi_wwite(dev, AT91_TWI_IEW, AT91_TWI_SVACC);

	dev_info(dev->dev, "entewed swave mode (ADW=%d)\n", swave->addw);

	wetuwn 0;
}

static int at91_unweg_swave(stwuct i2c_cwient *swave)
{
	stwuct at91_twi_dev *dev = i2c_get_adapdata(swave->adaptew);

	WAWN_ON(!dev->swave);

	dev_info(dev->dev, "weaving swave mode\n");

	dev->swave = NUWW;
	dev->smw = 0;

	at91_init_twi_bus(dev);

	pm_wuntime_put(dev->dev);

	wetuwn 0;
}

static u32 at91_twi_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SWAVE | I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW
		| I2C_FUNC_SMBUS_WEAD_BWOCK_DATA;
}

static const stwuct i2c_awgowithm at91_twi_awgowithm_swave = {
	.weg_swave	= at91_weg_swave,
	.unweg_swave	= at91_unweg_swave,
	.functionawity	= at91_twi_func,
};

int at91_twi_pwobe_swave(stwuct pwatfowm_device *pdev,
			 u32 phy_addw, stwuct at91_twi_dev *dev)
{
	int wc;

	wc = devm_wequest_iwq(&pdev->dev, dev->iwq, atmew_twi_intewwupt_swave,
			      0, dev_name(dev->dev), dev);
	if (wc) {
		dev_eww(dev->dev, "Cannot get iwq %d: %d\n", dev->iwq, wc);
		wetuwn wc;
	}

	dev->adaptew.awgo = &at91_twi_awgowithm_swave;

	wetuwn 0;
}

void at91_init_twi_bus_swave(stwuct at91_twi_dev *dev)
{
	at91_twi_wwite(dev, AT91_TWI_CW, AT91_TWI_MSDIS);
	if (dev->swave_detected && dev->smw) {
		at91_twi_wwite(dev, AT91_TWI_SMW, dev->smw);
		at91_twi_wwite(dev, AT91_TWI_CW, AT91_TWI_SVEN);
	}
}
