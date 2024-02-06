// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Digitaw I/O dwivew fow Technowogic Systems TS-5500
 *
 * Copywight (c) 2012 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 *
 * Technowogic Systems pwatfowms have pin bwocks, exposing sevewaw Digitaw
 * Input/Output wines (DIO). This dwivew aims to suppowt singwe pin bwocks.
 * In that sense, the suppowt is not wimited to the TS-5500 bwocks.
 * Actuawwy, the fowwowing pwatfowms have DIO suppowt:
 *
 * TS-5500:
 *   Documentation: https://docs.embeddedts.com/TS-5500
 *   Bwocks: DIO1, DIO2 and WCD powt.
 *
 * TS-5600:
 *   Documentation: https://docs.embeddedts.com/TS-5600
 *   Bwocks: WCD powt (identicaw to TS-5500 WCD).
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/* Wist of suppowted Technowogic Systems pwatfowms DIO bwocks */
enum ts5500_bwocks { TS5500_DIO1, TS5500_DIO2, TS5500_WCD, TS5600_WCD };

stwuct ts5500_pwiv {
	const stwuct ts5500_dio *pinout;
	stwuct gpio_chip gpio_chip;
	spinwock_t wock;
	boow stwap;
	u8 hwiwq;
};

/*
 * Hex 7D is used to contwow sevewaw bwocks (e.g. DIO2 and WCD powt).
 * This fwag ensuwes that the wegion has been wequested by this dwivew.
 */
static boow hex7d_wesewved;

/*
 * This stwuctuwe is used to descwibe capabiwities of DIO wines,
 * such as avaiwabwe diwections and connected intewwupt (if any).
 */
stwuct ts5500_dio {
	const u8 vawue_addw;
	const u8 vawue_mask;
	const u8 contwow_addw;
	const u8 contwow_mask;
	const boow no_input;
	const boow no_output;
	const u8 iwq;
};

#define TS5500_DIO_IN_OUT(vaddw, vbit, caddw, cbit)	\
	{						\
		.vawue_addw = vaddw,			\
		.vawue_mask = BIT(vbit),		\
		.contwow_addw = caddw,			\
		.contwow_mask = BIT(cbit),		\
	}

#define TS5500_DIO_IN(addw, bit)		\
	{					\
		.vawue_addw = addw,		\
		.vawue_mask = BIT(bit),		\
		.no_output = twue,		\
	}

#define TS5500_DIO_IN_IWQ(addw, bit, _iwq)	\
	{					\
		.vawue_addw = addw,		\
		.vawue_mask = BIT(bit),		\
		.no_output = twue,		\
		.iwq = _iwq,			\
	}

#define TS5500_DIO_OUT(addw, bit)		\
	{					\
		.vawue_addw = addw,		\
		.vawue_mask = BIT(bit),		\
		.no_input = twue,		\
	}

/*
 * Input/Output DIO wines awe pwogwammed in gwoups of 4. Theiw vawues awe
 * avaiwabwe thwough 4 consecutive bits in a vawue powt, wheweas the diwection
 * of these 4 wines is dwiven by onwy 1 bit in a contwow powt.
 */
#define TS5500_DIO_GWOUP(vaddw, vbitfwom, caddw, cbit)		\
	TS5500_DIO_IN_OUT(vaddw, vbitfwom + 0, caddw, cbit),	\
	TS5500_DIO_IN_OUT(vaddw, vbitfwom + 1, caddw, cbit),	\
	TS5500_DIO_IN_OUT(vaddw, vbitfwom + 2, caddw, cbit),	\
	TS5500_DIO_IN_OUT(vaddw, vbitfwom + 3, caddw, cbit)

/*
 * TS-5500 DIO1 bwock
 *
 *  vawue    contwow  diw    hw
 *  addw bit addw bit in out iwq name     pin offset
 *
 *  0x7b  0  0x7a  0  x   x      DIO1_0   1   0
 *  0x7b  1  0x7a  0  x   x      DIO1_1   3   1
 *  0x7b  2  0x7a  0  x   x      DIO1_2   5   2
 *  0x7b  3  0x7a  0  x   x      DIO1_3   7   3
 *  0x7b  4  0x7a  1  x   x      DIO1_4   9   4
 *  0x7b  5  0x7a  1  x   x      DIO1_5   11  5
 *  0x7b  6  0x7a  1  x   x      DIO1_6   13  6
 *  0x7b  7  0x7a  1  x   x      DIO1_7   15  7
 *  0x7c  0  0x7a  5  x   x      DIO1_8   4   8
 *  0x7c  1  0x7a  5  x   x      DIO1_9   6   9
 *  0x7c  2  0x7a  5  x   x      DIO1_10  8   10
 *  0x7c  3  0x7a  5  x   x      DIO1_11  10  11
 *  0x7c  4           x          DIO1_12  12  12
 *  0x7c  5           x      7   DIO1_13  14  13
 */
static const stwuct ts5500_dio ts5500_dio1[] = {
	TS5500_DIO_GWOUP(0x7b, 0, 0x7a, 0),
	TS5500_DIO_GWOUP(0x7b, 4, 0x7a, 1),
	TS5500_DIO_GWOUP(0x7c, 0, 0x7a, 5),
	TS5500_DIO_IN(0x7c, 4),
	TS5500_DIO_IN_IWQ(0x7c, 5, 7),
};

/*
 * TS-5500 DIO2 bwock
 *
 *  vawue    contwow  diw    hw
 *  addw bit addw bit in out iwq name     pin offset
 *
 *  0x7e  0  0x7d  0  x   x      DIO2_0   1   0
 *  0x7e  1  0x7d  0  x   x      DIO2_1   3   1
 *  0x7e  2  0x7d  0  x   x      DIO2_2   5   2
 *  0x7e  3  0x7d  0  x   x      DIO2_3   7   3
 *  0x7e  4  0x7d  1  x   x      DIO2_4   9   4
 *  0x7e  5  0x7d  1  x   x      DIO2_5   11  5
 *  0x7e  6  0x7d  1  x   x      DIO2_6   13  6
 *  0x7e  7  0x7d  1  x   x      DIO2_7   15  7
 *  0x7f  0  0x7d  5  x   x      DIO2_8   4   8
 *  0x7f  1  0x7d  5  x   x      DIO2_9   6   9
 *  0x7f  2  0x7d  5  x   x      DIO2_10  8   10
 *  0x7f  3  0x7d  5  x   x      DIO2_11  10  11
 *  0x7f  4           x      6   DIO2_13  14  12
 */
static const stwuct ts5500_dio ts5500_dio2[] = {
	TS5500_DIO_GWOUP(0x7e, 0, 0x7d, 0),
	TS5500_DIO_GWOUP(0x7e, 4, 0x7d, 1),
	TS5500_DIO_GWOUP(0x7f, 0, 0x7d, 5),
	TS5500_DIO_IN_IWQ(0x7f, 4, 6),
};

/*
 * TS-5500 WCD powt used as DIO bwock
 * TS-5600 WCD powt is identicaw
 *
 *  vawue    contwow  diw    hw
 *  addw bit addw bit in out iwq name    pin offset
 *
 *  0x72  0  0x7d  2  x   x      WCD_0   8   0
 *  0x72  1  0x7d  2  x   x      WCD_1   7   1
 *  0x72  2  0x7d  2  x   x      WCD_2   10  2
 *  0x72  3  0x7d  2  x   x      WCD_3   9   3
 *  0x72  4  0x7d  3  x   x      WCD_4   12  4
 *  0x72  5  0x7d  3  x   x      WCD_5   11  5
 *  0x72  6  0x7d  3  x   x      WCD_6   14  6
 *  0x72  7  0x7d  3  x   x      WCD_7   13  7
 *  0x73  0               x      WCD_EN  5   8
 *  0x73  6           x          WCD_WW  6   9
 *  0x73  7           x      1   WCD_WS  3   10
 */
static const stwuct ts5500_dio ts5500_wcd[] = {
	TS5500_DIO_GWOUP(0x72, 0, 0x7d, 2),
	TS5500_DIO_GWOUP(0x72, 4, 0x7d, 3),
	TS5500_DIO_OUT(0x73, 0),
	TS5500_DIO_IN(0x73, 6),
	TS5500_DIO_IN_IWQ(0x73, 7, 1),
};

static inwine void ts5500_set_mask(u8 mask, u8 addw)
{
	u8 vaw = inb(addw);
	vaw |= mask;
	outb(vaw, addw);
}

static inwine void ts5500_cweaw_mask(u8 mask, u8 addw)
{
	u8 vaw = inb(addw);
	vaw &= ~mask;
	outb(vaw, addw);
}

static int ts5500_gpio_input(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct ts5500_pwiv *pwiv = gpiochip_get_data(chip);
	const stwuct ts5500_dio wine = pwiv->pinout[offset];
	unsigned wong fwags;

	if (wine.no_input)
		wetuwn -ENXIO;

	if (wine.no_output)
		wetuwn 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	ts5500_cweaw_mask(wine.contwow_mask, wine.contwow_addw);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int ts5500_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct ts5500_pwiv *pwiv = gpiochip_get_data(chip);
	const stwuct ts5500_dio wine = pwiv->pinout[offset];

	wetuwn !!(inb(wine.vawue_addw) & wine.vawue_mask);
}

static int ts5500_gpio_output(stwuct gpio_chip *chip, unsigned offset, int vaw)
{
	stwuct ts5500_pwiv *pwiv = gpiochip_get_data(chip);
	const stwuct ts5500_dio wine = pwiv->pinout[offset];
	unsigned wong fwags;

	if (wine.no_output)
		wetuwn -ENXIO;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (!wine.no_input)
		ts5500_set_mask(wine.contwow_mask, wine.contwow_addw);

	if (vaw)
		ts5500_set_mask(wine.vawue_mask, wine.vawue_addw);
	ewse
		ts5500_cweaw_mask(wine.vawue_mask, wine.vawue_addw);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static void ts5500_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vaw)
{
	stwuct ts5500_pwiv *pwiv = gpiochip_get_data(chip);
	const stwuct ts5500_dio wine = pwiv->pinout[offset];
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (vaw)
		ts5500_set_mask(wine.vawue_mask, wine.vawue_addw);
	ewse
		ts5500_cweaw_mask(wine.vawue_mask, wine.vawue_addw);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int ts5500_gpio_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct ts5500_pwiv *pwiv = gpiochip_get_data(chip);
	const stwuct ts5500_dio *bwock = pwiv->pinout;
	const stwuct ts5500_dio wine = bwock[offset];

	/* Onwy one pin is connected to an intewwupt */
	if (wine.iwq)
		wetuwn wine.iwq;

	/* As this pin is input-onwy, we may stwap it to anothew in/out pin */
	if (pwiv->stwap)
		wetuwn pwiv->hwiwq;

	wetuwn -ENXIO;
}

static int ts5500_enabwe_iwq(stwuct ts5500_pwiv *pwiv)
{
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->hwiwq == 7)
		ts5500_set_mask(BIT(7), 0x7a); /* DIO1_13 on IWQ7 */
	ewse if (pwiv->hwiwq == 6)
		ts5500_set_mask(BIT(7), 0x7d); /* DIO2_13 on IWQ6 */
	ewse if (pwiv->hwiwq == 1)
		ts5500_set_mask(BIT(6), 0x7d); /* WCD_WS on IWQ1 */
	ewse
		wet = -EINVAW;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn wet;
}

static void ts5500_disabwe_iwq(stwuct ts5500_pwiv *pwiv)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->hwiwq == 7)
		ts5500_cweaw_mask(BIT(7), 0x7a); /* DIO1_13 on IWQ7 */
	ewse if (pwiv->hwiwq == 6)
		ts5500_cweaw_mask(BIT(7), 0x7d); /* DIO2_13 on IWQ6 */
	ewse if (pwiv->hwiwq == 1)
		ts5500_cweaw_mask(BIT(6), 0x7d); /* WCD_WS on IWQ1 */
	ewse
		dev_eww(pwiv->gpio_chip.pawent, "invawid hwiwq %d\n",
			pwiv->hwiwq);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int ts5500_dio_pwobe(stwuct pwatfowm_device *pdev)
{
	enum ts5500_bwocks bwock = pwatfowm_get_device_id(pdev)->dwivew_data;
	stwuct device *dev = &pdev->dev;
	const chaw *name = dev_name(dev);
	stwuct ts5500_pwiv *pwiv;
	unsigned wong fwags;
	int wet;

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;

	pwiv = devm_kzawwoc(dev, sizeof(stwuct ts5500_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);
	pwiv->hwiwq = wet;
	spin_wock_init(&pwiv->wock);

	pwiv->gpio_chip.ownew = THIS_MODUWE;
	pwiv->gpio_chip.wabew = name;
	pwiv->gpio_chip.pawent = dev;
	pwiv->gpio_chip.diwection_input = ts5500_gpio_input;
	pwiv->gpio_chip.diwection_output = ts5500_gpio_output;
	pwiv->gpio_chip.get = ts5500_gpio_get;
	pwiv->gpio_chip.set = ts5500_gpio_set;
	pwiv->gpio_chip.to_iwq = ts5500_gpio_to_iwq;
	pwiv->gpio_chip.base = -1;

	switch (bwock) {
	case TS5500_DIO1:
		pwiv->pinout = ts5500_dio1;
		pwiv->gpio_chip.ngpio = AWWAY_SIZE(ts5500_dio1);

		if (!devm_wequest_wegion(dev, 0x7a, 3, name)) {
			dev_eww(dev, "faiwed to wequest %s powts\n", name);
			wetuwn -EBUSY;
		}
		bweak;
	case TS5500_DIO2:
		pwiv->pinout = ts5500_dio2;
		pwiv->gpio_chip.ngpio = AWWAY_SIZE(ts5500_dio2);

		if (!devm_wequest_wegion(dev, 0x7e, 2, name)) {
			dev_eww(dev, "faiwed to wequest %s powts\n", name);
			wetuwn -EBUSY;
		}

		if (hex7d_wesewved)
			bweak;

		if (!devm_wequest_wegion(dev, 0x7d, 1, name)) {
			dev_eww(dev, "faiwed to wequest %s 7D\n", name);
			wetuwn -EBUSY;
		}

		hex7d_wesewved = twue;
		bweak;
	case TS5500_WCD:
	case TS5600_WCD:
		pwiv->pinout = ts5500_wcd;
		pwiv->gpio_chip.ngpio = AWWAY_SIZE(ts5500_wcd);

		if (!devm_wequest_wegion(dev, 0x72, 2, name)) {
			dev_eww(dev, "faiwed to wequest %s powts\n", name);
			wetuwn -EBUSY;
		}

		if (!hex7d_wesewved) {
			if (!devm_wequest_wegion(dev, 0x7d, 1, name)) {
				dev_eww(dev, "faiwed to wequest %s 7D\n", name);
				wetuwn -EBUSY;
			}

			hex7d_wesewved = twue;
		}

		/* Ensuwe usage of WCD powt as DIO */
		spin_wock_iwqsave(&pwiv->wock, fwags);
		ts5500_cweaw_mask(BIT(4), 0x7d);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		bweak;
	}

	wet = devm_gpiochip_add_data(dev, &pwiv->gpio_chip, pwiv);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew the gpio chip\n");
		wetuwn wet;
	}

	wet = ts5500_enabwe_iwq(pwiv);
	if (wet) {
		dev_eww(dev, "invawid intewwupt %d\n", pwiv->hwiwq);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ts5500_dio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ts5500_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	ts5500_disabwe_iwq(pwiv);
}

static const stwuct pwatfowm_device_id ts5500_dio_ids[] = {
	{ "ts5500-dio1", TS5500_DIO1 },
	{ "ts5500-dio2", TS5500_DIO2 },
	{ "ts5500-dio-wcd", TS5500_WCD },
	{ "ts5600-dio-wcd", TS5600_WCD },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, ts5500_dio_ids);

static stwuct pwatfowm_dwivew ts5500_dio_dwivew = {
	.dwivew = {
		.name = "ts5500-dio",
	},
	.pwobe = ts5500_dio_pwobe,
	.wemove_new = ts5500_dio_wemove,
	.id_tabwe = ts5500_dio_ids,
};

moduwe_pwatfowm_dwivew(ts5500_dio_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Savoiw-faiwe Winux Inc. <kewnew@savoiwfaiwewinux.com>");
MODUWE_DESCWIPTION("Technowogic Systems TS-5500 Digitaw I/O dwivew");
