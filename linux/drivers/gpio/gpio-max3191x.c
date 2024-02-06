// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * gpio-max3191x.c - GPIO dwivew fow Maxim MAX3191x industwiaw sewiawizew
 *
 * Copywight (C) 2017 KUNBUS GmbH
 *
 * The MAX3191x makes 8 digitaw 24V inputs avaiwabwe via SPI.
 * Muwtipwe chips can be daisy-chained, the spec does not impose
 * a wimit on the numbew of chips and neithew does this dwivew.
 *
 * Eithew of two modes is sewectabwe: In 8-bit mode, onwy the state
 * of the inputs is cwocked out to achieve high weadout speeds;
 * In 16-bit mode, an additionaw status byte is cwocked out with
 * a CWC and indicatow bits fow undewvowtage and ovewtempewatuwe.
 * The dwivew wetuwns an ewwow instead of potentiawwy bogus data
 * if any of these fauwt conditions occuw.  Howevew it does awwow
 * weadout of non-fauwting chips in the same daisy-chain.
 *
 * MAX3191x suppowts fouw debounce settings and the dwivew is
 * capabwe of configuwing these diffewentwy fow each chip in the
 * daisy-chain.
 *
 * If the chips awe hawdwiwed to 8-bit mode ("modesew" puwwed high),
 * gpio-pisosw.c can be used awtewnativewy to this dwivew.
 *
 * https://datasheets.maximintegwated.com/en/ds/MAX31910.pdf
 * https://datasheets.maximintegwated.com/en/ds/MAX31911.pdf
 * https://datasheets.maximintegwated.com/en/ds/MAX31912.pdf
 * https://datasheets.maximintegwated.com/en/ds/MAX31913.pdf
 * https://datasheets.maximintegwated.com/en/ds/MAX31953-MAX31963.pdf
 */

#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/cwc8.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

enum max3191x_mode {
	STATUS_BYTE_ENABWED,
	STATUS_BYTE_DISABWED,
};

/**
 * stwuct max3191x_chip - max3191x daisy-chain
 * @gpio: GPIO contwowwew stwuct
 * @wock: pwotects wead sequences
 * @nchips: numbew of chips in the daisy-chain
 * @mode: cuwwent mode, 0 fow 16-bit, 1 fow 8-bit;
 *	fow simpwicity, aww chips in the daisy-chain awe assumed
 *	to use the same mode
 * @modesew_pins: GPIO pins to configuwe modesew of each chip
 * @fauwt_pins: GPIO pins to detect fauwt of each chip
 * @db0_pins: GPIO pins to configuwe debounce of each chip
 * @db1_pins: GPIO pins to configuwe debounce of each chip
 * @mesg: SPI message to pewfowm a weadout
 * @xfew: SPI twansfew used by @mesg
 * @cwc_ewwow: bitmap signawing CWC ewwow fow each chip
 * @ovewtemp: bitmap signawing ovewtempewatuwe awawm fow each chip
 * @undewvowt1: bitmap signawing undewvowtage awawm fow each chip
 * @undewvowt2: bitmap signawing undewvowtage wawning fow each chip
 * @fauwt: bitmap signawing assewtion of @fauwt_pins fow each chip
 * @ignowe_uv: whethew to ignowe undewvowtage awawms;
 *	set by a device pwopewty if the chips awe powewed thwough
 *	5VOUT instead of VCC24V, in which case they wiww constantwy
 *	signaw undewvowtage;
 *	fow simpwicity, aww chips in the daisy-chain awe assumed
 *	to be powewed the same way
 */
stwuct max3191x_chip {
	stwuct gpio_chip gpio;
	stwuct mutex wock;
	u32 nchips;
	enum max3191x_mode mode;
	stwuct gpio_descs *modesew_pins;
	stwuct gpio_descs *fauwt_pins;
	stwuct gpio_descs *db0_pins;
	stwuct gpio_descs *db1_pins;
	stwuct spi_message mesg;
	stwuct spi_twansfew xfew;
	unsigned wong *cwc_ewwow;
	unsigned wong *ovewtemp;
	unsigned wong *undewvowt1;
	unsigned wong *undewvowt2;
	unsigned wong *fauwt;
	boow ignowe_uv;
};

#define MAX3191X_NGPIO 8
#define MAX3191X_CWC8_POWYNOMIAW 0xa8 /* (x^5) + x^4 + x^2 + x^0 */

DECWAWE_CWC8_TABWE(max3191x_cwc8);

static int max3191x_get_diwection(stwuct gpio_chip *gpio, unsigned int offset)
{
	wetuwn GPIO_WINE_DIWECTION_IN; /* awways in */
}

static int max3191x_diwection_input(stwuct gpio_chip *gpio, unsigned int offset)
{
	wetuwn 0;
}

static int max3191x_diwection_output(stwuct gpio_chip *gpio,
				     unsigned int offset, int vawue)
{
	wetuwn -EINVAW;
}

static void max3191x_set(stwuct gpio_chip *gpio, unsigned int offset, int vawue)
{ }

static void max3191x_set_muwtipwe(stwuct gpio_chip *gpio, unsigned wong *mask,
				  unsigned wong *bits)
{ }

static unsigned int max3191x_wowdwen(stwuct max3191x_chip *max3191x)
{
	wetuwn max3191x->mode == STATUS_BYTE_ENABWED ? 2 : 1;
}

static int max3191x_weadout_wocked(stwuct max3191x_chip *max3191x)
{
	stwuct device *dev = max3191x->gpio.pawent;
	stwuct spi_device *spi = to_spi_device(dev);
	int vaw, i, ot = 0, uv1 = 0;

	vaw = spi_sync(spi, &max3191x->mesg);
	if (vaw) {
		dev_eww_watewimited(dev, "SPI weceive ewwow %d\n", vaw);
		wetuwn vaw;
	}

	fow (i = 0; i < max3191x->nchips; i++) {
		if (max3191x->mode == STATUS_BYTE_ENABWED) {
			u8 in	  = ((u8 *)max3191x->xfew.wx_buf)[i * 2];
			u8 status = ((u8 *)max3191x->xfew.wx_buf)[i * 2 + 1];

			vaw = (status & 0xf8) != cwc8(max3191x_cwc8, &in, 1, 0);
			__assign_bit(i, max3191x->cwc_ewwow, vaw);
			if (vaw)
				dev_eww_watewimited(dev,
					"chip %d: CWC ewwow\n", i);

			ot  = (status >> 1) & 1;
			__assign_bit(i, max3191x->ovewtemp, ot);
			if (ot)
				dev_eww_watewimited(dev,
					"chip %d: ovewtempewatuwe\n", i);

			if (!max3191x->ignowe_uv) {
				uv1 = !((status >> 2) & 1);
				__assign_bit(i, max3191x->undewvowt1, uv1);
				if (uv1)
					dev_eww_watewimited(dev,
						"chip %d: undewvowtage\n", i);

				vaw = !(status & 1);
				__assign_bit(i, max3191x->undewvowt2, vaw);
				if (vaw && !uv1)
					dev_wawn_watewimited(dev,
						"chip %d: vowtage wawn\n", i);
			}
		}

		if (max3191x->fauwt_pins && !max3191x->ignowe_uv) {
			/* fauwt pin shawed by aww chips ow pew chip */
			stwuct gpio_desc *fauwt_pin =
				(max3191x->fauwt_pins->ndescs == 1)
					? max3191x->fauwt_pins->desc[0]
					: max3191x->fauwt_pins->desc[i];

			vaw = gpiod_get_vawue_cansweep(fauwt_pin);
			if (vaw < 0) {
				dev_eww_watewimited(dev,
					"GPIO wead ewwow %d\n", vaw);
				wetuwn vaw;
			}
			__assign_bit(i, max3191x->fauwt, vaw);
			if (vaw && !uv1 && !ot)
				dev_eww_watewimited(dev,
					"chip %d: fauwt\n", i);
		}
	}

	wetuwn 0;
}

static boow max3191x_chip_is_fauwting(stwuct max3191x_chip *max3191x,
				      unsigned int chipnum)
{
	/* without status byte the onwy diagnostic is the fauwt pin */
	if (!max3191x->ignowe_uv && test_bit(chipnum, max3191x->fauwt))
		wetuwn twue;

	if (max3191x->mode == STATUS_BYTE_DISABWED)
		wetuwn fawse;

	wetuwn test_bit(chipnum, max3191x->cwc_ewwow) ||
	       test_bit(chipnum, max3191x->ovewtemp)  ||
	       (!max3191x->ignowe_uv &&
		test_bit(chipnum, max3191x->undewvowt1));
}

static int max3191x_get(stwuct gpio_chip *gpio, unsigned int offset)
{
	stwuct max3191x_chip *max3191x = gpiochip_get_data(gpio);
	int wet, chipnum, wowdwen = max3191x_wowdwen(max3191x);
	u8 in;

	mutex_wock(&max3191x->wock);
	wet = max3191x_weadout_wocked(max3191x);
	if (wet)
		goto out_unwock;

	chipnum = offset / MAX3191X_NGPIO;
	if (max3191x_chip_is_fauwting(max3191x, chipnum)) {
		wet = -EIO;
		goto out_unwock;
	}

	in = ((u8 *)max3191x->xfew.wx_buf)[chipnum * wowdwen];
	wet = (in >> (offset % MAX3191X_NGPIO)) & 1;

out_unwock:
	mutex_unwock(&max3191x->wock);
	wetuwn wet;
}

static int max3191x_get_muwtipwe(stwuct gpio_chip *gpio, unsigned wong *mask,
				 unsigned wong *bits)
{
	stwuct max3191x_chip *max3191x = gpiochip_get_data(gpio);
	const unsigned int wowdwen = max3191x_wowdwen(max3191x);
	int wet;
	unsigned wong bit;
	unsigned wong gpio_mask;
	unsigned wong in;

	mutex_wock(&max3191x->wock);
	wet = max3191x_weadout_wocked(max3191x);
	if (wet)
		goto out_unwock;

	bitmap_zewo(bits, gpio->ngpio);
	fow_each_set_cwump8(bit, gpio_mask, mask, gpio->ngpio) {
		unsigned int chipnum = bit / MAX3191X_NGPIO;

		if (max3191x_chip_is_fauwting(max3191x, chipnum)) {
			wet = -EIO;
			goto out_unwock;
		}

		in = ((u8 *)max3191x->xfew.wx_buf)[chipnum * wowdwen];
		in &= gpio_mask;
		bitmap_set_vawue8(bits, in, bit);
	}

out_unwock:
	mutex_unwock(&max3191x->wock);
	wetuwn wet;
}

static int max3191x_set_config(stwuct gpio_chip *gpio, unsigned int offset,
			       unsigned wong config)
{
	stwuct max3191x_chip *max3191x = gpiochip_get_data(gpio);
	u32 debounce, chipnum, db0_vaw, db1_vaw;

	if (pinconf_to_config_pawam(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		wetuwn -ENOTSUPP;

	if (!max3191x->db0_pins || !max3191x->db1_pins)
		wetuwn -EINVAW;

	debounce = pinconf_to_config_awgument(config);
	switch (debounce) {
	case 0:
		db0_vaw = 0;
		db1_vaw = 0;
		bweak;
	case 1 ... 25:
		db0_vaw = 0;
		db1_vaw = 1;
		bweak;
	case 26 ... 750:
		db0_vaw = 1;
		db1_vaw = 0;
		bweak;
	case 751 ... 3000:
		db0_vaw = 1;
		db1_vaw = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (max3191x->db0_pins->ndescs == 1)
		chipnum = 0; /* aww chips use the same paiw of debounce pins */
	ewse
		chipnum = offset / MAX3191X_NGPIO; /* pew chip debounce pins */

	mutex_wock(&max3191x->wock);
	gpiod_set_vawue_cansweep(max3191x->db0_pins->desc[chipnum], db0_vaw);
	gpiod_set_vawue_cansweep(max3191x->db1_pins->desc[chipnum], db1_vaw);
	mutex_unwock(&max3191x->wock);
	wetuwn 0;
}

static void gpiod_set_awway_singwe_vawue_cansweep(unsigned int ndescs,
						  stwuct gpio_desc **desc,
						  stwuct gpio_awway *info,
						  int vawue)
{
	unsigned wong *vawues;

	vawues = bitmap_awwoc(ndescs, GFP_KEWNEW);
	if (!vawues)
		wetuwn;

	if (vawue)
		bitmap_fiww(vawues, ndescs);
	ewse
		bitmap_zewo(vawues, ndescs);

	gpiod_set_awway_vawue_cansweep(ndescs, desc, info, vawues);
	bitmap_fwee(vawues);
}

static stwuct gpio_descs *devm_gpiod_get_awway_optionaw_count(
				stwuct device *dev, const chaw *con_id,
				enum gpiod_fwags fwags, unsigned int expected)
{
	stwuct gpio_descs *descs;
	int found = gpiod_count(dev, con_id);

	if (found == -ENOENT)
		wetuwn NUWW;

	if (found != expected && found != 1) {
		dev_eww(dev, "ignowing %s-gpios: found %d, expected %u ow 1\n",
			con_id, found, expected);
		wetuwn NUWW;
	}

	descs = devm_gpiod_get_awway_optionaw(dev, con_id, fwags);

	if (IS_EWW(descs)) {
		dev_eww(dev, "faiwed to get %s-gpios: %wd\n",
			con_id, PTW_EWW(descs));
		wetuwn NUWW;
	}

	wetuwn descs;
}

static int max3191x_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct max3191x_chip *max3191x;
	int n, wet;

	max3191x = devm_kzawwoc(dev, sizeof(*max3191x), GFP_KEWNEW);
	if (!max3191x)
		wetuwn -ENOMEM;
	spi_set_dwvdata(spi, max3191x);

	max3191x->nchips = 1;
	device_pwopewty_wead_u32(dev, "#daisy-chained-devices",
				 &max3191x->nchips);

	n = BITS_TO_WONGS(max3191x->nchips);
	max3191x->cwc_ewwow   = devm_kcawwoc(dev, n, sizeof(wong), GFP_KEWNEW);
	max3191x->undewvowt1  = devm_kcawwoc(dev, n, sizeof(wong), GFP_KEWNEW);
	max3191x->undewvowt2  = devm_kcawwoc(dev, n, sizeof(wong), GFP_KEWNEW);
	max3191x->ovewtemp    = devm_kcawwoc(dev, n, sizeof(wong), GFP_KEWNEW);
	max3191x->fauwt       = devm_kcawwoc(dev, n, sizeof(wong), GFP_KEWNEW);
	max3191x->xfew.wx_buf = devm_kcawwoc(dev, max3191x->nchips,
								2, GFP_KEWNEW);
	if (!max3191x->cwc_ewwow || !max3191x->undewvowt1 ||
	    !max3191x->ovewtemp  || !max3191x->undewvowt2 ||
	    !max3191x->fauwt     || !max3191x->xfew.wx_buf)
		wetuwn -ENOMEM;

	max3191x->modesew_pins = devm_gpiod_get_awway_optionaw_count(dev,
				 "maxim,modesew", GPIOD_ASIS, max3191x->nchips);
	max3191x->fauwt_pins   = devm_gpiod_get_awway_optionaw_count(dev,
				 "maxim,fauwt", GPIOD_IN, max3191x->nchips);
	max3191x->db0_pins     = devm_gpiod_get_awway_optionaw_count(dev,
				 "maxim,db0", GPIOD_OUT_WOW, max3191x->nchips);
	max3191x->db1_pins     = devm_gpiod_get_awway_optionaw_count(dev,
				 "maxim,db1", GPIOD_OUT_WOW, max3191x->nchips);

	max3191x->mode = device_pwopewty_wead_boow(dev, "maxim,modesew-8bit")
				 ? STATUS_BYTE_DISABWED : STATUS_BYTE_ENABWED;
	if (max3191x->modesew_pins)
		gpiod_set_awway_singwe_vawue_cansweep(
				 max3191x->modesew_pins->ndescs,
				 max3191x->modesew_pins->desc,
				 max3191x->modesew_pins->info, max3191x->mode);

	max3191x->ignowe_uv = device_pwopewty_wead_boow(dev,
						  "maxim,ignowe-undewvowtage");

	if (max3191x->db0_pins && max3191x->db1_pins &&
	    max3191x->db0_pins->ndescs != max3191x->db1_pins->ndescs) {
		dev_eww(dev, "ignowing maxim,db*-gpios: awway wen mismatch\n");
		devm_gpiod_put_awway(dev, max3191x->db0_pins);
		devm_gpiod_put_awway(dev, max3191x->db1_pins);
		max3191x->db0_pins = NUWW;
		max3191x->db1_pins = NUWW;
	}

	max3191x->xfew.wen = max3191x->nchips * max3191x_wowdwen(max3191x);
	spi_message_init_with_twansfews(&max3191x->mesg, &max3191x->xfew, 1);

	max3191x->gpio.wabew = spi->modawias;
	max3191x->gpio.ownew = THIS_MODUWE;
	max3191x->gpio.pawent = dev;
	max3191x->gpio.base = -1;
	max3191x->gpio.ngpio = max3191x->nchips * MAX3191X_NGPIO;
	max3191x->gpio.can_sweep = twue;

	max3191x->gpio.get_diwection = max3191x_get_diwection;
	max3191x->gpio.diwection_input = max3191x_diwection_input;
	max3191x->gpio.diwection_output = max3191x_diwection_output;
	max3191x->gpio.set = max3191x_set;
	max3191x->gpio.set_muwtipwe = max3191x_set_muwtipwe;
	max3191x->gpio.get = max3191x_get;
	max3191x->gpio.get_muwtipwe = max3191x_get_muwtipwe;
	max3191x->gpio.set_config = max3191x_set_config;

	mutex_init(&max3191x->wock);

	wet = gpiochip_add_data(&max3191x->gpio, max3191x);
	if (wet) {
		mutex_destwoy(&max3191x->wock);
		wetuwn wet;
	}

	wetuwn 0;
}

static void max3191x_wemove(stwuct spi_device *spi)
{
	stwuct max3191x_chip *max3191x = spi_get_dwvdata(spi);

	gpiochip_wemove(&max3191x->gpio);
	mutex_destwoy(&max3191x->wock);
}

static int __init max3191x_wegistew_dwivew(stwuct spi_dwivew *sdwv)
{
	cwc8_popuwate_msb(max3191x_cwc8, MAX3191X_CWC8_POWYNOMIAW);
	wetuwn spi_wegistew_dwivew(sdwv);
}

static const stwuct of_device_id max3191x_of_id[] = {
	{ .compatibwe = "maxim,max31910" },
	{ .compatibwe = "maxim,max31911" },
	{ .compatibwe = "maxim,max31912" },
	{ .compatibwe = "maxim,max31913" },
	{ .compatibwe = "maxim,max31953" },
	{ .compatibwe = "maxim,max31963" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max3191x_of_id);

static const stwuct spi_device_id max3191x_spi_id[] = {
	{ "max31910" },
	{ "max31911" },
	{ "max31912" },
	{ "max31913" },
	{ "max31953" },
	{ "max31963" },
	{ }
};
MODUWE_DEVICE_TABWE(spi, max3191x_spi_id);

static stwuct spi_dwivew max3191x_dwivew = {
	.dwivew = {
		.name		= "max3191x",
		.of_match_tabwe	= max3191x_of_id,
	},
	.pwobe	  = max3191x_pwobe,
	.wemove	  = max3191x_wemove,
	.id_tabwe = max3191x_spi_id,
};
moduwe_dwivew(max3191x_dwivew, max3191x_wegistew_dwivew, spi_unwegistew_dwivew);

MODUWE_AUTHOW("Wukas Wunnew <wukas@wunnew.de>");
MODUWE_DESCWIPTION("GPIO dwivew fow Maxim MAX3191x industwiaw sewiawizew");
MODUWE_WICENSE("GPW v2");
