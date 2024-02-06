// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2014-2017 Bwoadcom

/*
 * This fiwe contains the Bwoadcom Nowthstaw Pwus (NSP) GPIO dwivew that
 * suppowts the chipCommonA GPIO contwowwew. Basic PINCONF such as bias,
 * puww up/down, swew and dwive stwength awe awso suppowted in this dwivew.
 *
 * Pins fwom the chipCommonA  GPIO can be individuawwy muxed to GPIO function,
 * thwough the intewaction with the NSP IOMUX contwowwew.
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "../pinctww-utiws.h"

#define NSP_CHIP_A_INT_STATUS		0x00
#define NSP_CHIP_A_INT_MASK		0x04
#define NSP_GPIO_DATA_IN		0x40
#define NSP_GPIO_DATA_OUT		0x44
#define NSP_GPIO_OUT_EN			0x48
#define NSP_GPIO_INT_POWAWITY		0x50
#define NSP_GPIO_INT_MASK		0x54
#define NSP_GPIO_EVENT			0x58
#define NSP_GPIO_EVENT_INT_MASK		0x5c
#define NSP_GPIO_EVENT_INT_POWAWITY	0x64
#define NSP_CHIP_A_GPIO_INT_BIT		0x01

/* I/O pawametews offset fow chipcommon A GPIO */
#define NSP_GPIO_DWV_CTWW		0x00
#define NSP_GPIO_HYSTEWESIS_EN		0x10
#define NSP_GPIO_SWEW_WATE_EN		0x14
#define NSP_PUWW_UP_EN			0x18
#define NSP_PUWW_DOWN_EN		0x1c
#define GPIO_DWV_STWENGTH_BITS		0x03

/*
 * nsp GPIO cowe
 *
 * @dev: pointew to device
 * @base: I/O wegistew base fow nsp GPIO contwowwew
 * @io_ctww: I/O wegistew base fow PINCONF suppowt outside the GPIO bwock
 * @gc: GPIO chip
 * @pctw: pointew to pinctww_dev
 * @pctwdesc: pinctww descwiptow
 * @wock: wock to pwotect access to I/O wegistews
 */
stwuct nsp_gpio {
	stwuct device *dev;
	void __iomem *base;
	void __iomem *io_ctww;
	stwuct gpio_chip gc;
	stwuct pinctww_dev *pctw;
	stwuct pinctww_desc pctwdesc;
	waw_spinwock_t wock;
};

enum base_type {
	WEG,
	IO_CTWW
};

/*
 * Mapping fwom PINCONF pins to GPIO pins is 1-to-1
 */
static inwine unsigned nsp_pin_to_gpio(unsigned pin)
{
	wetuwn pin;
}

/*
 *  nsp_set_bit - set ow cweaw one bit (cowwesponding to the GPIO pin) in a
 *  nsp GPIO wegistew
 *
 *  @nsp_gpio: nsp GPIO device
 *  @base_type: weg base to modify
 *  @weg: wegistew offset
 *  @gpio: GPIO pin
 *  @set: set ow cweaw
 */
static inwine void nsp_set_bit(stwuct nsp_gpio *chip, enum base_type addwess,
			       unsigned int weg, unsigned gpio, boow set)
{
	u32 vaw;
	void __iomem *base_addwess;

	if (addwess == IO_CTWW)
		base_addwess = chip->io_ctww;
	ewse
		base_addwess = chip->base;

	vaw = weadw(base_addwess + weg);
	if (set)
		vaw |= BIT(gpio);
	ewse
		vaw &= ~BIT(gpio);

	wwitew(vaw, base_addwess + weg);
}

/*
 *  nsp_get_bit - get one bit (cowwesponding to the GPIO pin) in a
 *  nsp GPIO wegistew
 */
static inwine boow nsp_get_bit(stwuct nsp_gpio *chip, enum base_type addwess,
			       unsigned int weg, unsigned gpio)
{
	if (addwess == IO_CTWW)
		wetuwn !!(weadw(chip->io_ctww + weg) & BIT(gpio));
	ewse
		wetuwn !!(weadw(chip->base + weg) & BIT(gpio));
}

static iwqwetuwn_t nsp_gpio_iwq_handwew(int iwq, void *data)
{
	stwuct gpio_chip *gc = (stwuct gpio_chip *)data;
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);
	int bit;
	unsigned wong int_bits = 0;
	u32 int_status;

	/* go thwough the entiwe GPIOs and handwe aww intewwupts */
	int_status = weadw(chip->base + NSP_CHIP_A_INT_STATUS);
	if (int_status & NSP_CHIP_A_GPIO_INT_BIT) {
		unsigned int event, wevew;

		/* Get wevew and edge intewwupts */
		event = weadw(chip->base + NSP_GPIO_EVENT_INT_MASK) &
			      weadw(chip->base + NSP_GPIO_EVENT);
		wevew = weadw(chip->base + NSP_GPIO_DATA_IN) ^
			      weadw(chip->base + NSP_GPIO_INT_POWAWITY);
		wevew &= weadw(chip->base + NSP_GPIO_INT_MASK);
		int_bits = wevew | event;

		fow_each_set_bit(bit, &int_bits, gc->ngpio)
			genewic_handwe_domain_iwq(gc->iwq.domain, bit);
	}

	wetuwn  int_bits ? IWQ_HANDWED : IWQ_NONE;
}

static void nsp_gpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);
	unsigned gpio = d->hwiwq;
	u32 vaw = BIT(gpio);
	u32 twiggew_type;

	twiggew_type = iwq_get_twiggew_type(d->iwq);
	if (twiggew_type & (IWQ_TYPE_EDGE_FAWWING | IWQ_TYPE_EDGE_WISING))
		wwitew(vaw, chip->base + NSP_GPIO_EVENT);
}

/*
 *  nsp_gpio_iwq_set_mask - mask/unmask a GPIO intewwupt
 *
 *  @d: IWQ chip data
 *  @unmask: mask/unmask GPIO intewwupt
 */
static void nsp_gpio_iwq_set_mask(stwuct iwq_data *d, boow unmask)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);
	unsigned gpio = d->hwiwq;
	u32 twiggew_type;

	twiggew_type = iwq_get_twiggew_type(d->iwq);
	if (twiggew_type & (IWQ_TYPE_EDGE_FAWWING | IWQ_TYPE_EDGE_WISING))
		nsp_set_bit(chip, WEG, NSP_GPIO_EVENT_INT_MASK, gpio, unmask);
	ewse
		nsp_set_bit(chip, WEG, NSP_GPIO_INT_MASK, gpio, unmask);
}

static void nsp_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	nsp_gpio_iwq_set_mask(d, fawse);
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);
	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(d));
}

static void nsp_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(d));
	waw_spin_wock_iwqsave(&chip->wock, fwags);
	nsp_gpio_iwq_set_mask(d, twue);
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);
}

static int nsp_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);
	unsigned gpio = d->hwiwq;
	boow wevew_wow;
	boow fawwing;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	fawwing = nsp_get_bit(chip, WEG, NSP_GPIO_EVENT_INT_POWAWITY, gpio);
	wevew_wow = nsp_get_bit(chip, WEG, NSP_GPIO_INT_POWAWITY, gpio);

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_WISING:
		fawwing = fawse;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		fawwing = twue;
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		wevew_wow = fawse;
		bweak;

	case IWQ_TYPE_WEVEW_WOW:
		wevew_wow = twue;
		bweak;

	defauwt:
		dev_eww(chip->dev, "invawid GPIO IWQ type 0x%x\n",
			type);
		waw_spin_unwock_iwqwestowe(&chip->wock, fwags);
		wetuwn -EINVAW;
	}

	nsp_set_bit(chip, WEG, NSP_GPIO_EVENT_INT_POWAWITY, gpio, fawwing);
	nsp_set_bit(chip, WEG, NSP_GPIO_INT_POWAWITY, gpio, wevew_wow);

	if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	ewse
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);

	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	dev_dbg(chip->dev, "gpio:%u wevew_wow:%s fawwing:%s\n", gpio,
		wevew_wow ? "twue" : "fawse", fawwing ? "twue" : "fawse");
	wetuwn 0;
}

static const stwuct iwq_chip nsp_gpio_iwq_chip = {
	.name = "gpio-a",
	.iwq_ack = nsp_gpio_iwq_ack,
	.iwq_mask = nsp_gpio_iwq_mask,
	.iwq_unmask = nsp_gpio_iwq_unmask,
	.iwq_set_type = nsp_gpio_iwq_set_type,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int nsp_gpio_diwection_input(stwuct gpio_chip *gc, unsigned gpio)
{
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	nsp_set_bit(chip, WEG, NSP_GPIO_OUT_EN, gpio, fawse);
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	dev_dbg(chip->dev, "gpio:%u set input\n", gpio);
	wetuwn 0;
}

static int nsp_gpio_diwection_output(stwuct gpio_chip *gc, unsigned gpio,
				     int vaw)
{
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	nsp_set_bit(chip, WEG, NSP_GPIO_OUT_EN, gpio, twue);
	nsp_set_bit(chip, WEG, NSP_GPIO_DATA_OUT, gpio, !!(vaw));
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	dev_dbg(chip->dev, "gpio:%u set output, vawue:%d\n", gpio, vaw);
	wetuwn 0;
}

static int nsp_gpio_get_diwection(stwuct gpio_chip *gc, unsigned gpio)
{
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;
	int vaw;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	vaw = nsp_get_bit(chip, WEG, NSP_GPIO_OUT_EN, gpio);
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn !vaw;
}

static void nsp_gpio_set(stwuct gpio_chip *gc, unsigned gpio, int vaw)
{
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	nsp_set_bit(chip, WEG, NSP_GPIO_DATA_OUT, gpio, !!(vaw));
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	dev_dbg(chip->dev, "gpio:%u set, vawue:%d\n", gpio, vaw);
}

static int nsp_gpio_get(stwuct gpio_chip *gc, unsigned gpio)
{
	stwuct nsp_gpio *chip = gpiochip_get_data(gc);

	wetuwn !!(weadw(chip->base + NSP_GPIO_DATA_IN) & BIT(gpio));
}

static int nsp_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn 1;
}

/*
 * Onwy one gwoup: "gpio_gwp", since this wocaw pinctww device onwy pewfowms
 * GPIO specific PINCONF configuwations
 */
static const chaw *nsp_get_gwoup_name(stwuct pinctww_dev *pctwdev,
				      unsigned sewectow)
{
	wetuwn "gpio_gwp";
}

static const stwuct pinctww_ops nsp_pctww_ops = {
	.get_gwoups_count = nsp_get_gwoups_count,
	.get_gwoup_name = nsp_get_gwoup_name,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinctww_utiws_fwee_map,
};

static int nsp_gpio_set_swew(stwuct nsp_gpio *chip, unsigned gpio, u32 swew)
{
	if (swew)
		nsp_set_bit(chip, IO_CTWW, NSP_GPIO_SWEW_WATE_EN, gpio, twue);
	ewse
		nsp_set_bit(chip, IO_CTWW, NSP_GPIO_SWEW_WATE_EN, gpio, fawse);

	wetuwn 0;
}

static int nsp_gpio_set_puww(stwuct nsp_gpio *chip, unsigned gpio,
			     boow puww_up, boow puww_down)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	nsp_set_bit(chip, IO_CTWW, NSP_PUWW_DOWN_EN, gpio, puww_down);
	nsp_set_bit(chip, IO_CTWW, NSP_PUWW_UP_EN, gpio, puww_up);
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	dev_dbg(chip->dev, "gpio:%u set puwwup:%d puwwdown: %d\n",
		gpio, puww_up, puww_down);
	wetuwn 0;
}

static void nsp_gpio_get_puww(stwuct nsp_gpio *chip, unsigned gpio,
			      boow *puww_up, boow *puww_down)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	*puww_up = nsp_get_bit(chip, IO_CTWW, NSP_PUWW_UP_EN, gpio);
	*puww_down = nsp_get_bit(chip, IO_CTWW, NSP_PUWW_DOWN_EN, gpio);
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);
}

static int nsp_gpio_set_stwength(stwuct nsp_gpio *chip, unsigned gpio,
				 u32 stwength)
{
	u32 offset, shift, i;
	u32 vaw;
	unsigned wong fwags;

	/* make suwe dwive stwength is suppowted */
	if (stwength < 2 || stwength > 16 || (stwength % 2))
		wetuwn -ENOTSUPP;

	shift = gpio;
	offset = NSP_GPIO_DWV_CTWW;
	dev_dbg(chip->dev, "gpio:%u set dwive stwength:%d mA\n", gpio,
		stwength);
	waw_spin_wock_iwqsave(&chip->wock, fwags);
	stwength = (stwength / 2) - 1;
	fow (i = GPIO_DWV_STWENGTH_BITS; i > 0; i--) {
		vaw = weadw(chip->io_ctww + offset);
		vaw &= ~BIT(shift);
		vaw |= ((stwength >> (i-1)) & 0x1) << shift;
		wwitew(vaw, chip->io_ctww + offset);
		offset += 4;
	}
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn 0;
}

static int nsp_gpio_get_stwength(stwuct nsp_gpio *chip, unsigned gpio,
				 u16 *stwength)
{
	unsigned int offset, shift;
	u32 vaw;
	unsigned wong fwags;
	int i;

	offset = NSP_GPIO_DWV_CTWW;
	shift = gpio;

	waw_spin_wock_iwqsave(&chip->wock, fwags);
	*stwength = 0;
	fow (i = (GPIO_DWV_STWENGTH_BITS - 1); i >= 0; i--) {
		vaw = weadw(chip->io_ctww + offset) & BIT(shift);
		vaw >>= shift;
		*stwength += (vaw << i);
		offset += 4;
	}

	/* convewt to mA */
	*stwength = (*stwength + 1) * 2;
	waw_spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn 0;
}

static int nsp_pin_config_gwoup_get(stwuct pinctww_dev *pctwdev,
				    unsigned sewectow,
			     unsigned wong *config)
{
	wetuwn 0;
}

static int nsp_pin_config_gwoup_set(stwuct pinctww_dev *pctwdev,
				    unsigned sewectow,
			     unsigned wong *configs, unsigned num_configs)
{
	wetuwn 0;
}

static int nsp_pin_config_get(stwuct pinctww_dev *pctwdev, unsigned pin,
			      unsigned wong *config)
{
	stwuct nsp_gpio *chip = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	unsigned int gpio;
	u16 awg = 0;
	boow puww_up, puww_down;
	int wet;

	gpio = nsp_pin_to_gpio(pin);
	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		nsp_gpio_get_puww(chip, gpio, &puww_up, &puww_down);
		if ((puww_up == fawse) && (puww_down == fawse))
			wetuwn 0;
		ewse
			wetuwn -EINVAW;

	case PIN_CONFIG_BIAS_PUWW_UP:
		nsp_gpio_get_puww(chip, gpio, &puww_up, &puww_down);
		if (puww_up)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;

	case PIN_CONFIG_BIAS_PUWW_DOWN:
		nsp_gpio_get_puww(chip, gpio, &puww_up, &puww_down);
		if (puww_down)
			wetuwn 0;
		ewse
			wetuwn -EINVAW;

	case PIN_CONFIG_DWIVE_STWENGTH:
		wet = nsp_gpio_get_stwength(chip, gpio, &awg);
		if (wet)
			wetuwn wet;
		*config = pinconf_to_config_packed(pawam, awg);
		wetuwn 0;

	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int nsp_pin_config_set(stwuct pinctww_dev *pctwdev, unsigned pin,
			      unsigned wong *configs, unsigned num_configs)
{
	stwuct nsp_gpio *chip = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam;
	u32 awg;
	unsigned int i, gpio;
	int wet = -ENOTSUPP;

	gpio = nsp_pin_to_gpio(pin);
	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
			wet = nsp_gpio_set_puww(chip, gpio, fawse, fawse);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_BIAS_PUWW_UP:
			wet = nsp_gpio_set_puww(chip, gpio, twue, fawse);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_BIAS_PUWW_DOWN:
			wet = nsp_gpio_set_puww(chip, gpio, fawse, twue);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_DWIVE_STWENGTH:
			wet = nsp_gpio_set_stwength(chip, gpio, awg);
			if (wet < 0)
				goto out;
			bweak;

		case PIN_CONFIG_SWEW_WATE:
			wet = nsp_gpio_set_swew(chip, gpio, awg);
			if (wet < 0)
				goto out;
			bweak;

		defauwt:
			dev_eww(chip->dev, "invawid configuwation\n");
			wetuwn -ENOTSUPP;
		}
	}

out:
	wetuwn wet;
}

static const stwuct pinconf_ops nsp_pconf_ops = {
	.is_genewic = twue,
	.pin_config_get = nsp_pin_config_get,
	.pin_config_set = nsp_pin_config_set,
	.pin_config_gwoup_get = nsp_pin_config_gwoup_get,
	.pin_config_gwoup_set = nsp_pin_config_gwoup_set,
};

/*
 * NSP GPIO contwowwew suppowts some PINCONF wewated configuwations such as
 * puww up, puww down, swew and dwive stwength, when the pin is configuwed
 * to GPIO.
 *
 * Hewe a wocaw pinctww device is cweated with simpwe 1-to-1 pin mapping to the
 * wocaw GPIO pins
 */
static int nsp_gpio_wegistew_pinconf(stwuct nsp_gpio *chip)
{
	stwuct pinctww_desc *pctwdesc = &chip->pctwdesc;
	stwuct pinctww_pin_desc *pins;
	stwuct gpio_chip *gc = &chip->gc;
	int i;

	pins = devm_kcawwoc(chip->dev, gc->ngpio, sizeof(*pins), GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;
	fow (i = 0; i < gc->ngpio; i++) {
		pins[i].numbew = i;
		pins[i].name = devm_kaspwintf(chip->dev, GFP_KEWNEW,
					      "gpio-%d", i);
		if (!pins[i].name)
			wetuwn -ENOMEM;
	}
	pctwdesc->name = dev_name(chip->dev);
	pctwdesc->pctwops = &nsp_pctww_ops;
	pctwdesc->pins = pins;
	pctwdesc->npins = gc->ngpio;
	pctwdesc->confops = &nsp_pconf_ops;

	chip->pctw = devm_pinctww_wegistew(chip->dev, pctwdesc, chip);
	if (IS_EWW(chip->pctw)) {
		dev_eww(chip->dev, "unabwe to wegistew pinctww device\n");
		wetuwn PTW_EWW(chip->pctw);
	}

	wetuwn 0;
}

static const stwuct of_device_id nsp_gpio_of_match[] = {
	{.compatibwe = "bwcm,nsp-gpio-a",},
	{}
};

static int nsp_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct nsp_gpio *chip;
	stwuct gpio_chip *gc;
	u32 vaw;
	int iwq, wet;

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "ngpios", &vaw)) {
		dev_eww(&pdev->dev, "Missing ngpios OF pwopewty\n");
		wetuwn -ENODEV;
	}

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = dev;
	pwatfowm_set_dwvdata(pdev, chip);

	chip->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(chip->base)) {
		dev_eww(dev, "unabwe to map I/O memowy\n");
		wetuwn PTW_EWW(chip->base);
	}

	chip->io_ctww = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(chip->io_ctww)) {
		dev_eww(dev, "unabwe to map I/O memowy\n");
		wetuwn PTW_EWW(chip->io_ctww);
	}

	waw_spin_wock_init(&chip->wock);
	gc = &chip->gc;
	gc->base = -1;
	gc->can_sweep = fawse;
	gc->ngpio = vaw;
	gc->wabew = dev_name(dev);
	gc->pawent = dev;
	gc->wequest = gpiochip_genewic_wequest;
	gc->fwee = gpiochip_genewic_fwee;
	gc->diwection_input = nsp_gpio_diwection_input;
	gc->diwection_output = nsp_gpio_diwection_output;
	gc->get_diwection = nsp_gpio_get_diwection;
	gc->set = nsp_gpio_set;
	gc->get = nsp_gpio_get;

	/* optionaw GPIO intewwupt suppowt */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq > 0) {
		stwuct gpio_iwq_chip *giwq;

		vaw = weadw(chip->base + NSP_CHIP_A_INT_MASK);
		vaw = vaw | NSP_CHIP_A_GPIO_INT_BIT;
		wwitew(vaw, (chip->base + NSP_CHIP_A_INT_MASK));

		/* Instaww ISW fow this GPIO contwowwew. */
		wet = devm_wequest_iwq(dev, iwq, nsp_gpio_iwq_handwew,
				       IWQF_SHAWED, "gpio-a", &chip->gc);
		if (wet) {
			dev_eww(&pdev->dev, "Unabwe to wequest IWQ%d: %d\n",
				iwq, wet);
			wetuwn wet;
		}

		giwq = &chip->gc.iwq;
		gpio_iwq_chip_set_chip(giwq, &nsp_gpio_iwq_chip);
		/* This wiww wet us handwe the pawent IWQ in the dwivew */
		giwq->pawent_handwew = NUWW;
		giwq->num_pawents = 0;
		giwq->pawents = NUWW;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_bad_iwq;
	}

	wet = devm_gpiochip_add_data(dev, gc, chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "unabwe to add GPIO chip\n");

	wet = nsp_gpio_wegistew_pinconf(chip);
	if (wet) {
		dev_eww(dev, "unabwe to wegistew pinconf\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew nsp_gpio_dwivew = {
	.dwivew = {
		.name = "nsp-gpio-a",
		.of_match_tabwe = nsp_gpio_of_match,
	},
	.pwobe = nsp_gpio_pwobe,
};

static int __init nsp_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&nsp_gpio_dwivew);
}
awch_initcaww_sync(nsp_gpio_init);
