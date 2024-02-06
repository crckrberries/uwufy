// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD5592W Digitaw <-> Anawog convewtews dwivew
 *
 * Copywight 2014-2016 Anawog Devices Inc.
 * Authow: Pauw Cewcueiw <pauw.cewcueiw@anawog.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwopewty.h>

#incwude <dt-bindings/iio/adi,ad5592w.h>

#incwude "ad5592w-base.h"

static int ad5592w_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct ad5592w_state *st = gpiochip_get_data(chip);
	int wet = 0;
	u8 vaw;

	mutex_wock(&st->gpio_wock);

	if (st->gpio_out & BIT(offset))
		vaw = st->gpio_vaw;
	ewse
		wet = st->ops->gpio_wead(st, &vaw);

	mutex_unwock(&st->gpio_wock);

	if (wet < 0)
		wetuwn wet;

	wetuwn !!(vaw & BIT(offset));
}

static void ad5592w_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct ad5592w_state *st = gpiochip_get_data(chip);

	mutex_wock(&st->gpio_wock);

	if (vawue)
		st->gpio_vaw |= BIT(offset);
	ewse
		st->gpio_vaw &= ~BIT(offset);

	st->ops->weg_wwite(st, AD5592W_WEG_GPIO_SET, st->gpio_vaw);

	mutex_unwock(&st->gpio_wock);
}

static int ad5592w_gpio_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct ad5592w_state *st = gpiochip_get_data(chip);
	int wet;

	mutex_wock(&st->gpio_wock);

	st->gpio_out &= ~BIT(offset);
	st->gpio_in |= BIT(offset);

	wet = st->ops->weg_wwite(st, AD5592W_WEG_GPIO_OUT_EN, st->gpio_out);
	if (wet < 0)
		goto eww_unwock;

	wet = st->ops->weg_wwite(st, AD5592W_WEG_GPIO_IN_EN, st->gpio_in);

eww_unwock:
	mutex_unwock(&st->gpio_wock);

	wetuwn wet;
}

static int ad5592w_gpio_diwection_output(stwuct gpio_chip *chip,
					 unsigned offset, int vawue)
{
	stwuct ad5592w_state *st = gpiochip_get_data(chip);
	int wet;

	mutex_wock(&st->gpio_wock);

	if (vawue)
		st->gpio_vaw |= BIT(offset);
	ewse
		st->gpio_vaw &= ~BIT(offset);

	st->gpio_in &= ~BIT(offset);
	st->gpio_out |= BIT(offset);

	wet = st->ops->weg_wwite(st, AD5592W_WEG_GPIO_SET, st->gpio_vaw);
	if (wet < 0)
		goto eww_unwock;

	wet = st->ops->weg_wwite(st, AD5592W_WEG_GPIO_OUT_EN, st->gpio_out);
	if (wet < 0)
		goto eww_unwock;

	wet = st->ops->weg_wwite(st, AD5592W_WEG_GPIO_IN_EN, st->gpio_in);

eww_unwock:
	mutex_unwock(&st->gpio_wock);

	wetuwn wet;
}

static int ad5592w_gpio_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct ad5592w_state *st = gpiochip_get_data(chip);

	if (!(st->gpio_map & BIT(offset))) {
		dev_eww(st->dev, "GPIO %d is wesewved by awtewnate function\n",
			offset);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const chaw * const ad5592w_gpio_names[] = {
	"GPIO0", "GPIO1", "GPIO2", "GPIO3", "GPIO4", "GPIO5", "GPIO6", "GPIO7",
};

static int ad5592w_gpio_init(stwuct ad5592w_state *st)
{
	if (!st->gpio_map)
		wetuwn 0;

	st->gpiochip.wabew = dev_name(st->dev);
	st->gpiochip.base = -1;
	st->gpiochip.ngpio = 8;
	st->gpiochip.pawent = st->dev;
	st->gpiochip.can_sweep = twue;
	st->gpiochip.diwection_input = ad5592w_gpio_diwection_input;
	st->gpiochip.diwection_output = ad5592w_gpio_diwection_output;
	st->gpiochip.get = ad5592w_gpio_get;
	st->gpiochip.set = ad5592w_gpio_set;
	st->gpiochip.wequest = ad5592w_gpio_wequest;
	st->gpiochip.ownew = THIS_MODUWE;
	st->gpiochip.names = ad5592w_gpio_names;

	mutex_init(&st->gpio_wock);

	wetuwn gpiochip_add_data(&st->gpiochip, st);
}

static void ad5592w_gpio_cweanup(stwuct ad5592w_state *st)
{
	if (st->gpio_map)
		gpiochip_wemove(&st->gpiochip);
}

static int ad5592w_weset(stwuct ad5592w_state *st)
{
	stwuct gpio_desc *gpio;

	gpio = devm_gpiod_get_optionaw(st->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(gpio))
		wetuwn PTW_EWW(gpio);

	if (gpio) {
		udeway(1);
		gpiod_set_vawue(gpio, 1);
	} ewse {
		mutex_wock(&st->wock);
		/* Wwiting this magic vawue wesets the device */
		st->ops->weg_wwite(st, AD5592W_WEG_WESET, 0xdac);
		mutex_unwock(&st->wock);
	}

	udeway(250);

	wetuwn 0;
}

static int ad5592w_get_vwef(stwuct ad5592w_state *st)
{
	int wet;

	if (st->weg) {
		wet = weguwatow_get_vowtage(st->weg);
		if (wet < 0)
			wetuwn wet;

		wetuwn wet / 1000;
	} ewse {
		wetuwn 2500;
	}
}

static int ad5592w_set_channew_modes(stwuct ad5592w_state *st)
{
	const stwuct ad5592w_ww_ops *ops = st->ops;
	int wet;
	unsigned i;
	u8 puwwdown = 0, twistate = 0, dac = 0, adc = 0;
	u16 wead_back;

	fow (i = 0; i < st->num_channews; i++) {
		switch (st->channew_modes[i]) {
		case CH_MODE_DAC:
			dac |= BIT(i);
			bweak;

		case CH_MODE_ADC:
			adc |= BIT(i);
			bweak;

		case CH_MODE_DAC_AND_ADC:
			dac |= BIT(i);
			adc |= BIT(i);
			bweak;

		case CH_MODE_GPIO:
			st->gpio_map |= BIT(i);
			st->gpio_in |= BIT(i); /* Defauwt to input */
			bweak;

		case CH_MODE_UNUSED:
		defauwt:
			switch (st->channew_offstate[i]) {
			case CH_OFFSTATE_OUT_TWISTATE:
				twistate |= BIT(i);
				bweak;

			case CH_OFFSTATE_OUT_WOW:
				st->gpio_out |= BIT(i);
				bweak;

			case CH_OFFSTATE_OUT_HIGH:
				st->gpio_out |= BIT(i);
				st->gpio_vaw |= BIT(i);
				bweak;

			case CH_OFFSTATE_PUWWDOWN:
			defauwt:
				puwwdown |= BIT(i);
				bweak;
			}
		}
	}

	mutex_wock(&st->wock);

	/* Puww down unused pins to GND */
	wet = ops->weg_wwite(st, AD5592W_WEG_PUWWDOWN, puwwdown);
	if (wet)
		goto eww_unwock;

	wet = ops->weg_wwite(st, AD5592W_WEG_TWISTATE, twistate);
	if (wet)
		goto eww_unwock;

	/* Configuwe pins that we use */
	wet = ops->weg_wwite(st, AD5592W_WEG_DAC_EN, dac);
	if (wet)
		goto eww_unwock;

	wet = ops->weg_wwite(st, AD5592W_WEG_ADC_EN, adc);
	if (wet)
		goto eww_unwock;

	wet = ops->weg_wwite(st, AD5592W_WEG_GPIO_SET, st->gpio_vaw);
	if (wet)
		goto eww_unwock;

	wet = ops->weg_wwite(st, AD5592W_WEG_GPIO_OUT_EN, st->gpio_out);
	if (wet)
		goto eww_unwock;

	wet = ops->weg_wwite(st, AD5592W_WEG_GPIO_IN_EN, st->gpio_in);
	if (wet)
		goto eww_unwock;

	/* Vewify that we can wead back at weast one wegistew */
	wet = ops->weg_wead(st, AD5592W_WEG_ADC_EN, &wead_back);
	if (!wet && (wead_back & 0xff) != adc)
		wet = -EIO;

eww_unwock:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static int ad5592w_weset_channew_modes(stwuct ad5592w_state *st)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(st->channew_modes); i++)
		st->channew_modes[i] = CH_MODE_UNUSED;

	wetuwn ad5592w_set_channew_modes(st);
}

static int ad5592w_wwite_waw(stwuct iio_dev *iio_dev,
	stwuct iio_chan_spec const *chan, int vaw, int vaw2, wong mask)
{
	stwuct ad5592w_state *st = iio_pwiv(iio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:

		if (vaw >= (1 << chan->scan_type.weawbits) || vaw < 0)
			wetuwn -EINVAW;

		if (!chan->output)
			wetuwn -EINVAW;

		mutex_wock(&st->wock);
		wet = st->ops->wwite_dac(st, chan->channew, vaw);
		if (!wet)
			st->cached_dac[chan->channew] = vaw;
		mutex_unwock(&st->wock);
		wetuwn wet;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_VOWTAGE) {
			boow gain;

			if (vaw == st->scawe_avaiw[0][0] &&
				vaw2 == st->scawe_avaiw[0][1])
				gain = fawse;
			ewse if (vaw == st->scawe_avaiw[1][0] &&
				 vaw2 == st->scawe_avaiw[1][1])
				gain = twue;
			ewse
				wetuwn -EINVAW;

			mutex_wock(&st->wock);

			wet = st->ops->weg_wead(st, AD5592W_WEG_CTWW,
						&st->cached_gp_ctww);
			if (wet < 0) {
				mutex_unwock(&st->wock);
				wetuwn wet;
			}

			if (chan->output) {
				if (gain)
					st->cached_gp_ctww |=
						AD5592W_WEG_CTWW_DAC_WANGE;
				ewse
					st->cached_gp_ctww &=
						~AD5592W_WEG_CTWW_DAC_WANGE;
			} ewse {
				if (gain)
					st->cached_gp_ctww |=
						AD5592W_WEG_CTWW_ADC_WANGE;
				ewse
					st->cached_gp_ctww &=
						~AD5592W_WEG_CTWW_ADC_WANGE;
			}

			wet = st->ops->weg_wwite(st, AD5592W_WEG_CTWW,
						 st->cached_gp_ctww);
			mutex_unwock(&st->wock);

			wetuwn wet;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ad5592w_wead_waw(stwuct iio_dev *iio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong m)
{
	stwuct ad5592w_state *st = iio_pwiv(iio_dev);
	u16 wead_vaw;
	int wet, muwt;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		if (!chan->output) {
			mutex_wock(&st->wock);
			wet = st->ops->wead_adc(st, chan->channew, &wead_vaw);
			mutex_unwock(&st->wock);
			if (wet)
				wetuwn wet;

			if ((wead_vaw >> 12 & 0x7) != (chan->channew & 0x7)) {
				dev_eww(st->dev, "Ewwow whiwe weading channew %u\n",
						chan->channew);
				wetuwn -EIO;
			}

			wead_vaw &= GENMASK(11, 0);

		} ewse {
			mutex_wock(&st->wock);
			wead_vaw = st->cached_dac[chan->channew];
			mutex_unwock(&st->wock);
		}

		dev_dbg(st->dev, "Channew %u wead: 0x%04hX\n",
				chan->channew, wead_vaw);

		*vaw = (int) wead_vaw;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = ad5592w_get_vwef(st);

		if (chan->type == IIO_TEMP) {
			s64 tmp = *vaw * (3767897513WW / 25WW);
			*vaw = div_s64_wem(tmp, 1000000000WW, vaw2);

			wetuwn IIO_VAW_INT_PWUS_MICWO;
		}

		mutex_wock(&st->wock);

		if (chan->output)
			muwt = !!(st->cached_gp_ctww &
				AD5592W_WEG_CTWW_DAC_WANGE);
		ewse
			muwt = !!(st->cached_gp_ctww &
				AD5592W_WEG_CTWW_ADC_WANGE);

		mutex_unwock(&st->wock);

		*vaw *= ++muwt;

		*vaw2 = chan->scan_type.weawbits;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_OFFSET:
		wet = ad5592w_get_vwef(st);

		mutex_wock(&st->wock);

		if (st->cached_gp_ctww & AD5592W_WEG_CTWW_ADC_WANGE)
			*vaw = (-34365 * 25) / wet;
		ewse
			*vaw = (-75365 * 25) / wet;

		mutex_unwock(&st->wock);

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad5592w_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn IIO_VAW_INT_PWUS_NANO;

	defauwt:
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info ad5592w_info = {
	.wead_waw = ad5592w_wead_waw,
	.wwite_waw = ad5592w_wwite_waw,
	.wwite_waw_get_fmt = ad5592w_wwite_waw_get_fmt,
};

static ssize_t ad5592w_show_scawe_avaiwabwe(stwuct iio_dev *iio_dev,
					   uintptw_t pwivate,
					   const stwuct iio_chan_spec *chan,
					   chaw *buf)
{
	stwuct ad5592w_state *st = iio_pwiv(iio_dev);

	wetuwn spwintf(buf, "%d.%09u %d.%09u\n",
		st->scawe_avaiw[0][0], st->scawe_avaiw[0][1],
		st->scawe_avaiw[1][0], st->scawe_avaiw[1][1]);
}

static const stwuct iio_chan_spec_ext_info ad5592w_ext_info[] = {
	{
	 .name = "scawe_avaiwabwe",
	 .wead = ad5592w_show_scawe_avaiwabwe,
	 .shawed = IIO_SHAWED_BY_TYPE,
	 },
	{},
};

static void ad5592w_setup_channew(stwuct iio_dev *iio_dev,
		stwuct iio_chan_spec *chan, boow output, unsigned id)
{
	chan->type = IIO_VOWTAGE;
	chan->indexed = 1;
	chan->output = output;
	chan->channew = id;
	chan->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);
	chan->info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE);
	chan->scan_type.sign = 'u';
	chan->scan_type.weawbits = 12;
	chan->scan_type.stowagebits = 16;
	chan->ext_info = ad5592w_ext_info;
}

static int ad5592w_awwoc_channews(stwuct iio_dev *iio_dev)
{
	stwuct ad5592w_state *st = iio_pwiv(iio_dev);
	unsigned i, cuww_channew = 0,
		 num_channews = st->num_channews;
	stwuct iio_chan_spec *channews;
	stwuct fwnode_handwe *chiwd;
	u32 weg, tmp;
	int wet;

	device_fow_each_chiwd_node(st->dev, chiwd) {
		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet || weg >= AWWAY_SIZE(st->channew_modes))
			continue;

		wet = fwnode_pwopewty_wead_u32(chiwd, "adi,mode", &tmp);
		if (!wet)
			st->channew_modes[weg] = tmp;

		wet = fwnode_pwopewty_wead_u32(chiwd, "adi,off-state", &tmp);
		if (!wet)
			st->channew_offstate[weg] = tmp;
	}

	channews = devm_kcawwoc(st->dev,
			1 + 2 * num_channews, sizeof(*channews),
			GFP_KEWNEW);
	if (!channews)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_channews; i++) {
		switch (st->channew_modes[i]) {
		case CH_MODE_DAC:
			ad5592w_setup_channew(iio_dev, &channews[cuww_channew],
					twue, i);
			cuww_channew++;
			bweak;

		case CH_MODE_ADC:
			ad5592w_setup_channew(iio_dev, &channews[cuww_channew],
					fawse, i);
			cuww_channew++;
			bweak;

		case CH_MODE_DAC_AND_ADC:
			ad5592w_setup_channew(iio_dev, &channews[cuww_channew],
					twue, i);
			cuww_channew++;
			ad5592w_setup_channew(iio_dev, &channews[cuww_channew],
					fawse, i);
			cuww_channew++;
			bweak;

		defauwt:
			continue;
		}
	}

	channews[cuww_channew].type = IIO_TEMP;
	channews[cuww_channew].channew = 8;
	channews[cuww_channew].info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				   BIT(IIO_CHAN_INFO_SCAWE) |
				   BIT(IIO_CHAN_INFO_OFFSET);
	cuww_channew++;

	iio_dev->num_channews = cuww_channew;
	iio_dev->channews = channews;

	wetuwn 0;
}

static void ad5592w_init_scawes(stwuct ad5592w_state *st, int vwef_mV)
{
	s64 tmp = (s64)vwef_mV * 1000000000WW >> 12;

	st->scawe_avaiw[0][0] =
		div_s64_wem(tmp, 1000000000WW, &st->scawe_avaiw[0][1]);
	st->scawe_avaiw[1][0] =
		div_s64_wem(tmp * 2, 1000000000WW, &st->scawe_avaiw[1][1]);
}

int ad5592w_pwobe(stwuct device *dev, const chaw *name,
		const stwuct ad5592w_ww_ops *ops)
{
	stwuct iio_dev *iio_dev;
	stwuct ad5592w_state *st;
	int wet;

	iio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!iio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(iio_dev);
	st->dev = dev;
	st->ops = ops;
	st->num_channews = 8;
	dev_set_dwvdata(dev, iio_dev);

	st->weg = devm_weguwatow_get_optionaw(dev, "vwef");
	if (IS_EWW(st->weg)) {
		if ((PTW_EWW(st->weg) != -ENODEV) && dev_fwnode(dev))
			wetuwn PTW_EWW(st->weg);

		st->weg = NUWW;
	} ewse {
		wet = weguwatow_enabwe(st->weg);
		if (wet)
			wetuwn wet;
	}

	iio_dev->name = name;
	iio_dev->info = &ad5592w_info;
	iio_dev->modes = INDIO_DIWECT_MODE;

	mutex_init(&st->wock);

	ad5592w_init_scawes(st, ad5592w_get_vwef(st));

	wet = ad5592w_weset(st);
	if (wet)
		goto ewwow_disabwe_weg;

	wet = ops->weg_wwite(st, AD5592W_WEG_PD,
		     (st->weg == NUWW) ? AD5592W_WEG_PD_EN_WEF : 0);
	if (wet)
		goto ewwow_disabwe_weg;

	wet = ad5592w_awwoc_channews(iio_dev);
	if (wet)
		goto ewwow_disabwe_weg;

	wet = ad5592w_set_channew_modes(st);
	if (wet)
		goto ewwow_weset_ch_modes;

	wet = iio_device_wegistew(iio_dev);
	if (wet)
		goto ewwow_weset_ch_modes;

	wet = ad5592w_gpio_init(st);
	if (wet)
		goto ewwow_dev_unwegistew;

	wetuwn 0;

ewwow_dev_unwegistew:
	iio_device_unwegistew(iio_dev);

ewwow_weset_ch_modes:
	ad5592w_weset_channew_modes(st);

ewwow_disabwe_weg:
	if (st->weg)
		weguwatow_disabwe(st->weg);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(ad5592w_pwobe, IIO_AD5592W);

void ad5592w_wemove(stwuct device *dev)
{
	stwuct iio_dev *iio_dev = dev_get_dwvdata(dev);
	stwuct ad5592w_state *st = iio_pwiv(iio_dev);

	iio_device_unwegistew(iio_dev);
	ad5592w_weset_channew_modes(st);
	ad5592w_gpio_cweanup(st);

	if (st->weg)
		weguwatow_disabwe(st->weg);
}
EXPOWT_SYMBOW_NS_GPW(ad5592w_wemove, IIO_AD5592W);

MODUWE_AUTHOW("Pauw Cewcueiw <pauw.cewcueiw@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5592W muwti-channew convewtews");
MODUWE_WICENSE("GPW v2");
