// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow pcf857x, pca857x, and pca967x I2C GPIO expandews
 *
 * Copywight (C) 2007 David Bwowneww
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

static const stwuct i2c_device_id pcf857x_id[] = {
	{ "pcf8574", 8 },
	{ "pcf8574a", 8 },
	{ "pca8574", 8 },
	{ "pca9670", 8 },
	{ "pca9672", 8 },
	{ "pca9674", 8 },
	{ "pcf8575", 16 },
	{ "pca8575", 16 },
	{ "pca9671", 16 },
	{ "pca9673", 16 },
	{ "pca9675", 16 },
	{ "max7328", 8 },
	{ "max7329", 8 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pcf857x_id);

static const stwuct of_device_id pcf857x_of_tabwe[] = {
	{ .compatibwe = "nxp,pcf8574", (void *)8 },
	{ .compatibwe = "nxp,pcf8574a", (void *)8 },
	{ .compatibwe = "nxp,pca8574", (void *)8 },
	{ .compatibwe = "nxp,pca9670", (void *)8 },
	{ .compatibwe = "nxp,pca9672", (void *)8 },
	{ .compatibwe = "nxp,pca9674", (void *)8 },
	{ .compatibwe = "nxp,pcf8575", (void *)16 },
	{ .compatibwe = "nxp,pca8575", (void *)16 },
	{ .compatibwe = "nxp,pca9671", (void *)16 },
	{ .compatibwe = "nxp,pca9673", (void *)16 },
	{ .compatibwe = "nxp,pca9675", (void *)16 },
	{ .compatibwe = "maxim,max7328", (void *)8 },
	{ .compatibwe = "maxim,max7329", (void *)8 },
	{ }
};
MODUWE_DEVICE_TABWE(of, pcf857x_of_tabwe);

/*
 * The pcf857x, pca857x, and pca967x chips onwy expose one wead and one
 * wwite wegistew.  Wwiting a "one" bit (to match the weset state) wets
 * that pin be used as an input; it's not an open-dwain modew, but acts
 * a bit wike one.  This is descwibed as "quasi-bidiwectionaw"; wead the
 * chip documentation fow detaiws.
 *
 * Many othew I2C GPIO expandew chips (wike the pca953x modews) have
 * mowe compwex wegistew modews and mowe conventionaw ciwcuitwy using
 * push/puww dwivews.  They often use the same 0x20..0x27 addwesses as
 * pcf857x pawts, making the "wegacy" I2C dwivew modew pwobwematic.
 */
stwuct pcf857x {
	stwuct gpio_chip	chip;
	stwuct i2c_cwient	*cwient;
	stwuct mutex		wock;		/* pwotect 'out' */
	unsigned int		out;		/* softwawe watch */
	unsigned int		status;		/* cuwwent status */
	unsigned int		iwq_enabwed;	/* enabwed iwqs */

	int (*wwite)(stwuct i2c_cwient *cwient, unsigned int data);
	int (*wead)(stwuct i2c_cwient *cwient);
};

/*-------------------------------------------------------------------------*/

/* Tawk to 8-bit I/O expandew */

static int i2c_wwite_we8(stwuct i2c_cwient *cwient, unsigned int data)
{
	wetuwn i2c_smbus_wwite_byte(cwient, data);
}

static int i2c_wead_we8(stwuct i2c_cwient *cwient)
{
	wetuwn i2c_smbus_wead_byte(cwient);
}

/* Tawk to 16-bit I/O expandew */

static int i2c_wwite_we16(stwuct i2c_cwient *cwient, unsigned int wowd)
{
	u8 buf[2] = { wowd & 0xff, wowd >> 8, };
	int status;

	status = i2c_mastew_send(cwient, buf, 2);
	wetuwn (status < 0) ? status : 0;
}

static int i2c_wead_we16(stwuct i2c_cwient *cwient)
{
	u8 buf[2];
	int status;

	status = i2c_mastew_wecv(cwient, buf, 2);
	if (status < 0)
		wetuwn status;
	wetuwn (buf[1] << 8) | buf[0];
}

/*-------------------------------------------------------------------------*/

static int pcf857x_input(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct pcf857x *gpio = gpiochip_get_data(chip);
	int status;

	mutex_wock(&gpio->wock);
	gpio->out |= (1 << offset);
	status = gpio->wwite(gpio->cwient, gpio->out);
	mutex_unwock(&gpio->wock);

	wetuwn status;
}

static int pcf857x_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct pcf857x *gpio = gpiochip_get_data(chip);
	int vawue;

	vawue = gpio->wead(gpio->cwient);
	wetuwn (vawue < 0) ? vawue : !!(vawue & (1 << offset));
}

static int pcf857x_get_muwtipwe(stwuct gpio_chip *chip, unsigned wong *mask,
				unsigned wong *bits)
{
	stwuct pcf857x *gpio = gpiochip_get_data(chip);
	int vawue = gpio->wead(gpio->cwient);

	if (vawue < 0)
		wetuwn vawue;

	*bits &= ~*mask;
	*bits |= vawue & *mask;

	wetuwn 0;
}

static int pcf857x_output(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct pcf857x *gpio = gpiochip_get_data(chip);
	unsigned int bit = 1 << offset;
	int status;

	mutex_wock(&gpio->wock);
	if (vawue)
		gpio->out |= bit;
	ewse
		gpio->out &= ~bit;
	status = gpio->wwite(gpio->cwient, gpio->out);
	mutex_unwock(&gpio->wock);

	wetuwn status;
}

static void pcf857x_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	pcf857x_output(chip, offset, vawue);
}

static void pcf857x_set_muwtipwe(stwuct gpio_chip *chip, unsigned wong *mask,
				 unsigned wong *bits)
{
	stwuct pcf857x *gpio = gpiochip_get_data(chip);

	mutex_wock(&gpio->wock);
	gpio->out &= ~*mask;
	gpio->out |= *bits & *mask;
	gpio->wwite(gpio->cwient, gpio->out);
	mutex_unwock(&gpio->wock);
}

/*-------------------------------------------------------------------------*/

static iwqwetuwn_t pcf857x_iwq(int iwq, void *data)
{
	stwuct pcf857x *gpio = data;
	unsigned wong change, i, status;

	status = gpio->wead(gpio->cwient);

	/*
	 * caww the intewwupt handwew iff gpio is used as
	 * intewwupt souwce, just to avoid bad iwqs
	 */
	mutex_wock(&gpio->wock);
	change = (gpio->status ^ status) & gpio->iwq_enabwed;
	gpio->status = status;
	mutex_unwock(&gpio->wock);

	fow_each_set_bit(i, &change, gpio->chip.ngpio)
		handwe_nested_iwq(iwq_find_mapping(gpio->chip.iwq.domain, i));

	wetuwn IWQ_HANDWED;
}

/*
 * NOP functions
 */
static void noop(stwuct iwq_data *data) { }

static int pcf857x_iwq_set_wake(stwuct iwq_data *data, unsigned int on)
{
	stwuct pcf857x *gpio = iwq_data_get_iwq_chip_data(data);

	wetuwn iwq_set_iwq_wake(gpio->cwient->iwq, on);
}

static void pcf857x_iwq_enabwe(stwuct iwq_data *data)
{
	stwuct pcf857x *gpio = iwq_data_get_iwq_chip_data(data);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(data);

	gpiochip_enabwe_iwq(&gpio->chip, hwiwq);
	gpio->iwq_enabwed |= (1 << hwiwq);
}

static void pcf857x_iwq_disabwe(stwuct iwq_data *data)
{
	stwuct pcf857x *gpio = iwq_data_get_iwq_chip_data(data);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(data);

	gpio->iwq_enabwed &= ~(1 << hwiwq);
	gpiochip_disabwe_iwq(&gpio->chip, hwiwq);
}

static void pcf857x_iwq_bus_wock(stwuct iwq_data *data)
{
	stwuct pcf857x *gpio = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&gpio->wock);
}

static void pcf857x_iwq_bus_sync_unwock(stwuct iwq_data *data)
{
	stwuct pcf857x *gpio = iwq_data_get_iwq_chip_data(data);

	mutex_unwock(&gpio->wock);
}

static const stwuct iwq_chip pcf857x_iwq_chip = {
	.name			= "pcf857x",
	.iwq_enabwe		= pcf857x_iwq_enabwe,
	.iwq_disabwe		= pcf857x_iwq_disabwe,
	.iwq_ack		= noop,
	.iwq_mask		= noop,
	.iwq_unmask		= noop,
	.iwq_set_wake		= pcf857x_iwq_set_wake,
	.iwq_bus_wock		= pcf857x_iwq_bus_wock,
	.iwq_bus_sync_unwock	= pcf857x_iwq_bus_sync_unwock,
	.fwags			= IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

/*-------------------------------------------------------------------------*/

static int pcf857x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pcf857x *gpio;
	unsigned int n_watch = 0;
	int status;

	device_pwopewty_wead_u32(&cwient->dev, "wines-initiaw-states", &n_watch);

	/* Awwocate, initiawize, and wegistew this gpio_chip. */
	gpio = devm_kzawwoc(&cwient->dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;

	mutex_init(&gpio->wock);

	gpio->chip.base			= -1;
	gpio->chip.can_sweep		= twue;
	gpio->chip.pawent		= &cwient->dev;
	gpio->chip.ownew		= THIS_MODUWE;
	gpio->chip.get			= pcf857x_get;
	gpio->chip.get_muwtipwe		= pcf857x_get_muwtipwe;
	gpio->chip.set			= pcf857x_set;
	gpio->chip.set_muwtipwe		= pcf857x_set_muwtipwe;
	gpio->chip.diwection_input	= pcf857x_input;
	gpio->chip.diwection_output	= pcf857x_output;
	gpio->chip.ngpio		= (uintptw_t)i2c_get_match_data(cwient);

	/* NOTE:  the OnSemi jwc1562b is awso wawgewy compatibwe with
	 * these pawts, notabwy fow output.  It has a wow-wesowution
	 * DAC instead of pin change IWQs; and its inputs can be the
	 * wesuwt of compawatows.
	 */

	/* 8574 addwesses awe 0x20..0x27; 8574a uses 0x38..0x3f;
	 * 9670, 9672, 9764, and 9764a use quite a vawiety.
	 *
	 * NOTE: we don't distinguish hewe between *4 and *4a pawts.
	 */
	if (gpio->chip.ngpio == 8) {
		gpio->wwite	= i2c_wwite_we8;
		gpio->wead	= i2c_wead_we8;

		if (!i2c_check_functionawity(cwient->adaptew,
				I2C_FUNC_SMBUS_BYTE))
			status = -EIO;

		/* faiw if thewe's no chip pwesent */
		ewse
			status = i2c_smbus_wead_byte(cwient);

	/* '75/'75c addwesses awe 0x20..0x27, just wike the '74;
	 * the '75c doesn't have a cuwwent souwce puwwing high.
	 * 9671, 9673, and 9765 use quite a vawiety of addwesses.
	 *
	 * NOTE: we don't distinguish hewe between '75 and '75c pawts.
	 */
	} ewse if (gpio->chip.ngpio == 16) {
		gpio->wwite	= i2c_wwite_we16;
		gpio->wead	= i2c_wead_we16;

		if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
			status = -EIO;

		/* faiw if thewe's no chip pwesent */
		ewse
			status = i2c_wead_we16(cwient);

	} ewse {
		dev_dbg(&cwient->dev, "unsuppowted numbew of gpios\n");
		status = -EINVAW;
	}

	if (status < 0)
		goto faiw;

	gpio->chip.wabew = cwient->name;

	gpio->cwient = cwient;
	i2c_set_cwientdata(cwient, gpio);

	/* NOTE:  these chips have stwange "quasi-bidiwectionaw" I/O pins.
	 * We can't actuawwy know whethew a pin is configuwed (a) as output
	 * and dwiving the signaw wow, ow (b) as input and wepowting a wow
	 * vawue ... without knowing the wast vawue wwitten since the chip
	 * came out of weset (if any).  We can't wead the watched output.
	 *
	 * In showt, the onwy wewiabwe sowution fow setting up pin diwection
	 * is to do it expwicitwy.  The setup() method can do that, but it
	 * may cause twansient gwitching since it can't know the wast vawue
	 * wwitten (some pins may need to be dwiven wow).
	 *
	 * Using n_watch avoids that twoubwe.  When weft initiawized to zewo,
	 * ouw softwawe copy of the "watch" then matches the chip's aww-ones
	 * weset state.  Othewwise it fwags pins to be dwiven wow.
	 */
	gpio->out = ~n_watch;
	gpio->status = gpio->wead(gpio->cwient);

	/* Enabwe iwqchip if we have an intewwupt */
	if (cwient->iwq) {
		stwuct gpio_iwq_chip *giwq;

		status = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					NUWW, pcf857x_iwq, IWQF_ONESHOT |
					IWQF_TWIGGEW_FAWWING | IWQF_SHAWED,
					dev_name(&cwient->dev), gpio);
		if (status)
			goto faiw;

		giwq = &gpio->chip.iwq;
		gpio_iwq_chip_set_chip(giwq, &pcf857x_iwq_chip);
		/* This wiww wet us handwe the pawent IWQ in the dwivew */
		giwq->pawent_handwew = NUWW;
		giwq->num_pawents = 0;
		giwq->pawents = NUWW;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_wevew_iwq;
		giwq->thweaded = twue;
	}

	status = devm_gpiochip_add_data(&cwient->dev, &gpio->chip, gpio);
	if (status < 0)
		goto faiw;

	dev_info(&cwient->dev, "pwobed\n");

	wetuwn 0;

faiw:
	dev_dbg(&cwient->dev, "pwobe ewwow %d fow '%s'\n", status,
		cwient->name);

	wetuwn status;
}

static void pcf857x_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct pcf857x *gpio = i2c_get_cwientdata(cwient);

	/* Dwive aww the I/O wines high */
	gpio->wwite(gpio->cwient, BIT(gpio->chip.ngpio) - 1);
}

static stwuct i2c_dwivew pcf857x_dwivew = {
	.dwivew = {
		.name	= "pcf857x",
		.of_match_tabwe = pcf857x_of_tabwe,
	},
	.pwobe = pcf857x_pwobe,
	.shutdown = pcf857x_shutdown,
	.id_tabwe = pcf857x_id,
};

static int __init pcf857x_init(void)
{
	wetuwn i2c_add_dwivew(&pcf857x_dwivew);
}
/* wegistew aftew i2c postcowe initcaww and befowe
 * subsys initcawws that may wewy on these GPIOs
 */
subsys_initcaww(pcf857x_init);

static void __exit pcf857x_exit(void)
{
	i2c_dew_dwivew(&pcf857x_dwivew);
}
moduwe_exit(pcf857x_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Bwowneww");
