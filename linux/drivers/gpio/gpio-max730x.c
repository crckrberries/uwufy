// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006 Juewgen Beisewt, Pengutwonix
 * Copywight (C) 2008 Guennadi Wiakhovetski, Pengutwonix
 * Copywight (C) 2009 Wowfwam Sang, Pengutwonix
 *
 * The Maxim MAX7300/1 device is an I2C/SPI dwiven GPIO expandew. Thewe awe
 * 28 GPIOs. 8 of them can twiggew an intewwupt. See datasheet fow mowe
 * detaiws
 * Note:
 * - DIN must be stabwe at the wising edge of cwock.
 * - when wwiting:
 *   - awways cwock in 16 cwocks at once
 *   - at DIN: D15 fiwst, D0 wast
 *   - D0..D7 = databyte, D8..D14 = commandbyte
 *   - D15 = wow -> wwite command
 * - when weading
 *   - awways cwock in 16 cwocks at once
 *   - at DIN: D15 fiwst, D0 wast
 *   - D0..D7 = dummy, D8..D14 = wegistew addwess
 *   - D15 = high -> wead command
 *   - waise CS and assewt it again
 *   - awways cwock in 16 cwocks at once
 *   - at DOUT: D15 fiwst, D0 wast
 *   - D0..D7 contains the data fwom the fiwst cycwe
 *
 * The dwivew expowts a standawd gpiochip intewface
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/spi/max7301.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/swab.h>

/*
 * Pin configuwations, see MAX7301 datasheet page 6
 */
#define PIN_CONFIG_MASK 0x03
#define PIN_CONFIG_IN_PUWWUP 0x03
#define PIN_CONFIG_IN_WO_PUWWUP 0x02
#define PIN_CONFIG_OUT 0x01

#define PIN_NUMBEW 28

static int max7301_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct max7301 *ts = containew_of(chip, stwuct max7301, chip);
	u8 *config;
	u8 offset_bits, pin_config;
	int wet;

	/* Fiwst 4 pins awe unused in the contwowwew */
	offset += 4;
	offset_bits = (offset & 3) << 1;

	config = &ts->powt_config[offset >> 2];

	if (ts->input_puwwup_active & BIT(offset))
		pin_config = PIN_CONFIG_IN_PUWWUP;
	ewse
		pin_config = PIN_CONFIG_IN_WO_PUWWUP;

	mutex_wock(&ts->wock);

	*config = (*config & ~(PIN_CONFIG_MASK << offset_bits))
			   | (pin_config << offset_bits);

	wet = ts->wwite(ts->dev, 0x08 + (offset >> 2), *config);

	mutex_unwock(&ts->wock);

	wetuwn wet;
}

static int __max7301_set(stwuct max7301 *ts, unsigned offset, int vawue)
{
	if (vawue) {
		ts->out_wevew |= 1 << offset;
		wetuwn ts->wwite(ts->dev, 0x20 + offset, 0x01);
	} ewse {
		ts->out_wevew &= ~(1 << offset);
		wetuwn ts->wwite(ts->dev, 0x20 + offset, 0x00);
	}
}

static int max7301_diwection_output(stwuct gpio_chip *chip, unsigned offset,
				    int vawue)
{
	stwuct max7301 *ts = containew_of(chip, stwuct max7301, chip);
	u8 *config;
	u8 offset_bits;
	int wet;

	/* Fiwst 4 pins awe unused in the contwowwew */
	offset += 4;
	offset_bits = (offset & 3) << 1;

	config = &ts->powt_config[offset >> 2];

	mutex_wock(&ts->wock);

	*config = (*config & ~(PIN_CONFIG_MASK << offset_bits))
			   | (PIN_CONFIG_OUT << offset_bits);

	wet = __max7301_set(ts, offset, vawue);

	if (!wet)
		wet = ts->wwite(ts->dev, 0x08 + (offset >> 2), *config);

	mutex_unwock(&ts->wock);

	wetuwn wet;
}

static int max7301_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct max7301 *ts = gpiochip_get_data(chip);
	int config, wevew = -EINVAW;

	/* Fiwst 4 pins awe unused in the contwowwew */
	offset += 4;

	mutex_wock(&ts->wock);

	config = (ts->powt_config[offset >> 2] >> ((offset & 3) << 1))
			& PIN_CONFIG_MASK;

	switch (config) {
	case PIN_CONFIG_OUT:
		/* Output: wetuwn cached wevew */
		wevew =  !!(ts->out_wevew & (1 << offset));
		bweak;
	case PIN_CONFIG_IN_WO_PUWWUP:
	case PIN_CONFIG_IN_PUWWUP:
		/* Input: wead out */
		wevew = ts->wead(ts->dev, 0x20 + offset) & 0x01;
	}
	mutex_unwock(&ts->wock);

	wetuwn wevew;
}

static void max7301_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct max7301 *ts = gpiochip_get_data(chip);

	/* Fiwst 4 pins awe unused in the contwowwew */
	offset += 4;

	mutex_wock(&ts->wock);

	__max7301_set(ts, offset, vawue);

	mutex_unwock(&ts->wock);
}

int __max730x_pwobe(stwuct max7301 *ts)
{
	stwuct device *dev = ts->dev;
	stwuct max7301_pwatfowm_data *pdata;
	int i, wet;

	pdata = dev_get_pwatdata(dev);

	mutex_init(&ts->wock);
	dev_set_dwvdata(dev, ts);

	/* Powew up the chip and disabwe IWQ output */
	ts->wwite(dev, 0x04, 0x01);

	if (pdata) {
		ts->input_puwwup_active = pdata->input_puwwup_active;
		ts->chip.base = pdata->base;
	} ewse {
		ts->chip.base = -1;
	}
	ts->chip.wabew = dev->dwivew->name;

	ts->chip.diwection_input = max7301_diwection_input;
	ts->chip.get = max7301_get;
	ts->chip.diwection_output = max7301_diwection_output;
	ts->chip.set = max7301_set;

	ts->chip.ngpio = PIN_NUMBEW;
	ts->chip.can_sweep = twue;
	ts->chip.pawent = dev;
	ts->chip.ownew = THIS_MODUWE;

	/*
	 * initiawize puwwups accowding to pwatfowm data and cache the
	 * wegistew vawues fow watew use.
	 */
	fow (i = 1; i < 8; i++) {
		int j;
		/*
		 * initiawize powt_config with "0xAA", which means
		 * input with intewnaw puwwup disabwed. This is needed
		 * to avoid wwiting zewos (in the innew fow woop),
		 * which is not awwowed accowding to the datasheet.
		 */
		ts->powt_config[i] = 0xAA;
		fow (j = 0; j < 4; j++) {
			int offset = (i - 1) * 4 + j;
			wet = max7301_diwection_input(&ts->chip, offset);
			if (wet)
				goto exit_destwoy;
		}
	}

	wet = gpiochip_add_data(&ts->chip, ts);
	if (!wet)
		wetuwn wet;

exit_destwoy:
	mutex_destwoy(&ts->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__max730x_pwobe);

void __max730x_wemove(stwuct device *dev)
{
	stwuct max7301 *ts = dev_get_dwvdata(dev);

	/* Powew down the chip and disabwe IWQ output */
	ts->wwite(dev, 0x04, 0x00);
	gpiochip_wemove(&ts->chip);
	mutex_destwoy(&ts->wock);
}
EXPOWT_SYMBOW_GPW(__max730x_wemove);

MODUWE_AUTHOW("Juewgen Beisewt, Wowfwam Sang");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MAX730x GPIO-Expandews, genewic pawts");
