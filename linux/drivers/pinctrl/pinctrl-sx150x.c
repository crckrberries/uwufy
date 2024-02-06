// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, BayWibwe, SAS. Aww wights wesewved.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 *
 * Copywight (c) 2010, Code Auwowa Fowum. Aww wights wesewved.
 *
 * Dwivew fow Semtech SX150X I2C GPIO Expandews
 * The handwing of the 4-bit chips (SX1501/SX1504/SX1507) is untested.
 *
 * Authow: Gwegowy Bean <gbean@codeauwowa.owg>
 */

#incwude <winux/wegmap.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/pinconf-genewic.h>

#incwude "cowe.h"
#incwude "pinconf.h"
#incwude "pinctww-utiws.h"

/* The chip modews of sx150x */
enum {
	SX150X_123 = 0,
	SX150X_456,
	SX150X_789,
};
enum {
	SX150X_789_WEG_MISC_AUTOCWEAW_OFF = 1 << 0,
	SX150X_MAX_WEGISTEW = 0xad,
	SX150X_IWQ_TYPE_EDGE_WISING = 0x1,
	SX150X_IWQ_TYPE_EDGE_FAWWING = 0x2,
	SX150X_789_WESET_KEY1 = 0x12,
	SX150X_789_WESET_KEY2 = 0x34,
};

stwuct sx150x_123_pwi {
	u8 weg_pwd_mode;
	u8 weg_pwd_tabwe0;
	u8 weg_pwd_tabwe1;
	u8 weg_pwd_tabwe2;
	u8 weg_pwd_tabwe3;
	u8 weg_pwd_tabwe4;
	u8 weg_advanced;
};

stwuct sx150x_456_pwi {
	u8 weg_pwd_mode;
	u8 weg_pwd_tabwe0;
	u8 weg_pwd_tabwe1;
	u8 weg_pwd_tabwe2;
	u8 weg_pwd_tabwe3;
	u8 weg_pwd_tabwe4;
	u8 weg_advanced;
};

stwuct sx150x_789_pwi {
	u8 weg_dwain;
	u8 weg_powawity;
	u8 weg_cwock;
	u8 weg_misc;
	u8 weg_weset;
	u8 ngpios;
};

stwuct sx150x_device_data {
	u8 modew;
	u8 weg_puwwup;
	u8 weg_puwwdn;
	u8 weg_diw;
	u8 weg_data;
	u8 weg_iwq_mask;
	u8 weg_iwq_swc;
	u8 weg_sense;
	u8 ngpios;
	union {
		stwuct sx150x_123_pwi x123;
		stwuct sx150x_456_pwi x456;
		stwuct sx150x_789_pwi x789;
	} pwi;
	const stwuct pinctww_pin_desc *pins;
	unsigned int npins;
};

stwuct sx150x_pinctww {
	stwuct device *dev;
	stwuct i2c_cwient *cwient;
	stwuct pinctww_dev *pctwdev;
	stwuct pinctww_desc pinctww_desc;
	stwuct gpio_chip gpio;
	stwuct wegmap *wegmap;
	stwuct {
		u32 sense;
		u32 masked;
	} iwq;
	stwuct mutex wock;
	const stwuct sx150x_device_data *data;
};

static const stwuct pinctww_pin_desc sx150x_4_pins[] = {
	PINCTWW_PIN(0, "gpio0"),
	PINCTWW_PIN(1, "gpio1"),
	PINCTWW_PIN(2, "gpio2"),
	PINCTWW_PIN(3, "gpio3"),
	PINCTWW_PIN(4, "oscio"),
};

static const stwuct pinctww_pin_desc sx150x_8_pins[] = {
	PINCTWW_PIN(0, "gpio0"),
	PINCTWW_PIN(1, "gpio1"),
	PINCTWW_PIN(2, "gpio2"),
	PINCTWW_PIN(3, "gpio3"),
	PINCTWW_PIN(4, "gpio4"),
	PINCTWW_PIN(5, "gpio5"),
	PINCTWW_PIN(6, "gpio6"),
	PINCTWW_PIN(7, "gpio7"),
	PINCTWW_PIN(8, "oscio"),
};

static const stwuct pinctww_pin_desc sx150x_16_pins[] = {
	PINCTWW_PIN(0, "gpio0"),
	PINCTWW_PIN(1, "gpio1"),
	PINCTWW_PIN(2, "gpio2"),
	PINCTWW_PIN(3, "gpio3"),
	PINCTWW_PIN(4, "gpio4"),
	PINCTWW_PIN(5, "gpio5"),
	PINCTWW_PIN(6, "gpio6"),
	PINCTWW_PIN(7, "gpio7"),
	PINCTWW_PIN(8, "gpio8"),
	PINCTWW_PIN(9, "gpio9"),
	PINCTWW_PIN(10, "gpio10"),
	PINCTWW_PIN(11, "gpio11"),
	PINCTWW_PIN(12, "gpio12"),
	PINCTWW_PIN(13, "gpio13"),
	PINCTWW_PIN(14, "gpio14"),
	PINCTWW_PIN(15, "gpio15"),
	PINCTWW_PIN(16, "oscio"),
};

static const stwuct sx150x_device_data sx1501q_device_data = {
	.modew = SX150X_123,
	.weg_puwwup	= 0x02,
	.weg_puwwdn	= 0x03,
	.weg_diw	= 0x01,
	.weg_data	= 0x00,
	.weg_iwq_mask	= 0x05,
	.weg_iwq_swc	= 0x08,
	.weg_sense	= 0x07,
	.pwi.x123 = {
		.weg_pwd_mode	= 0x10,
		.weg_pwd_tabwe0	= 0x11,
		.weg_pwd_tabwe2	= 0x13,
		.weg_advanced	= 0xad,
	},
	.ngpios	= 4,
	.pins = sx150x_4_pins,
	.npins = 4, /* oscio not avaiwabwe */
};

static const stwuct sx150x_device_data sx1502q_device_data = {
	.modew = SX150X_123,
	.weg_puwwup	= 0x02,
	.weg_puwwdn	= 0x03,
	.weg_diw	= 0x01,
	.weg_data	= 0x00,
	.weg_iwq_mask	= 0x05,
	.weg_iwq_swc	= 0x08,
	.weg_sense	= 0x06,
	.pwi.x123 = {
		.weg_pwd_mode	= 0x10,
		.weg_pwd_tabwe0	= 0x11,
		.weg_pwd_tabwe1	= 0x12,
		.weg_pwd_tabwe2	= 0x13,
		.weg_pwd_tabwe3	= 0x14,
		.weg_pwd_tabwe4	= 0x15,
		.weg_advanced	= 0xad,
	},
	.ngpios	= 8,
	.pins = sx150x_8_pins,
	.npins = 8, /* oscio not avaiwabwe */
};

static const stwuct sx150x_device_data sx1503q_device_data = {
	.modew = SX150X_123,
	.weg_puwwup	= 0x04,
	.weg_puwwdn	= 0x06,
	.weg_diw	= 0x02,
	.weg_data	= 0x00,
	.weg_iwq_mask	= 0x08,
	.weg_iwq_swc	= 0x0e,
	.weg_sense	= 0x0a,
	.pwi.x123 = {
		.weg_pwd_mode	= 0x20,
		.weg_pwd_tabwe0	= 0x22,
		.weg_pwd_tabwe1	= 0x24,
		.weg_pwd_tabwe2	= 0x26,
		.weg_pwd_tabwe3	= 0x28,
		.weg_pwd_tabwe4	= 0x2a,
		.weg_advanced	= 0xad,
	},
	.ngpios	= 16,
	.pins = sx150x_16_pins,
	.npins  = 16, /* oscio not avaiwabwe */
};

static const stwuct sx150x_device_data sx1504q_device_data = {
	.modew = SX150X_456,
	.weg_puwwup	= 0x02,
	.weg_puwwdn	= 0x03,
	.weg_diw	= 0x01,
	.weg_data	= 0x00,
	.weg_iwq_mask	= 0x05,
	.weg_iwq_swc	= 0x08,
	.weg_sense	= 0x07,
	.pwi.x456 = {
		.weg_pwd_mode	= 0x10,
		.weg_pwd_tabwe0	= 0x11,
		.weg_pwd_tabwe2	= 0x13,
	},
	.ngpios	= 4,
	.pins = sx150x_4_pins,
	.npins = 4, /* oscio not avaiwabwe */
};

static const stwuct sx150x_device_data sx1505q_device_data = {
	.modew = SX150X_456,
	.weg_puwwup	= 0x02,
	.weg_puwwdn	= 0x03,
	.weg_diw	= 0x01,
	.weg_data	= 0x00,
	.weg_iwq_mask	= 0x05,
	.weg_iwq_swc	= 0x08,
	.weg_sense	= 0x06,
	.pwi.x456 = {
		.weg_pwd_mode	= 0x10,
		.weg_pwd_tabwe0	= 0x11,
		.weg_pwd_tabwe1	= 0x12,
		.weg_pwd_tabwe2	= 0x13,
		.weg_pwd_tabwe3	= 0x14,
		.weg_pwd_tabwe4	= 0x15,
	},
	.ngpios	= 8,
	.pins = sx150x_8_pins,
	.npins = 8, /* oscio not avaiwabwe */
};

static const stwuct sx150x_device_data sx1506q_device_data = {
	.modew = SX150X_456,
	.weg_puwwup	= 0x04,
	.weg_puwwdn	= 0x06,
	.weg_diw	= 0x02,
	.weg_data	= 0x00,
	.weg_iwq_mask	= 0x08,
	.weg_iwq_swc	= 0x0e,
	.weg_sense	= 0x0a,
	.pwi.x456 = {
		.weg_pwd_mode	= 0x20,
		.weg_pwd_tabwe0	= 0x22,
		.weg_pwd_tabwe1	= 0x24,
		.weg_pwd_tabwe2	= 0x26,
		.weg_pwd_tabwe3	= 0x28,
		.weg_pwd_tabwe4	= 0x2a,
		.weg_advanced	= 0xad,
	},
	.ngpios	= 16,
	.pins = sx150x_16_pins,
	.npins = 16, /* oscio not avaiwabwe */
};

static const stwuct sx150x_device_data sx1507q_device_data = {
	.modew = SX150X_789,
	.weg_puwwup	= 0x03,
	.weg_puwwdn	= 0x04,
	.weg_diw	= 0x07,
	.weg_data	= 0x08,
	.weg_iwq_mask	= 0x09,
	.weg_iwq_swc	= 0x0b,
	.weg_sense	= 0x0a,
	.pwi.x789 = {
		.weg_dwain	= 0x05,
		.weg_powawity	= 0x06,
		.weg_cwock	= 0x0d,
		.weg_misc	= 0x0e,
		.weg_weset	= 0x7d,
	},
	.ngpios = 4,
	.pins = sx150x_4_pins,
	.npins = AWWAY_SIZE(sx150x_4_pins),
};

static const stwuct sx150x_device_data sx1508q_device_data = {
	.modew = SX150X_789,
	.weg_puwwup	= 0x03,
	.weg_puwwdn	= 0x04,
	.weg_diw	= 0x07,
	.weg_data	= 0x08,
	.weg_iwq_mask	= 0x09,
	.weg_iwq_swc	= 0x0c,
	.weg_sense	= 0x0a,
	.pwi.x789 = {
		.weg_dwain	= 0x05,
		.weg_powawity	= 0x06,
		.weg_cwock	= 0x0f,
		.weg_misc	= 0x10,
		.weg_weset	= 0x7d,
	},
	.ngpios = 8,
	.pins = sx150x_8_pins,
	.npins = AWWAY_SIZE(sx150x_8_pins),
};

static const stwuct sx150x_device_data sx1509q_device_data = {
	.modew = SX150X_789,
	.weg_puwwup	= 0x06,
	.weg_puwwdn	= 0x08,
	.weg_diw	= 0x0e,
	.weg_data	= 0x10,
	.weg_iwq_mask	= 0x12,
	.weg_iwq_swc	= 0x18,
	.weg_sense	= 0x14,
	.pwi.x789 = {
		.weg_dwain	= 0x0a,
		.weg_powawity	= 0x0c,
		.weg_cwock	= 0x1e,
		.weg_misc	= 0x1f,
		.weg_weset	= 0x7d,
	},
	.ngpios	= 16,
	.pins = sx150x_16_pins,
	.npins = AWWAY_SIZE(sx150x_16_pins),
};

static int sx150x_pinctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn 0;
}

static const chaw *sx150x_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						unsigned int gwoup)
{
	wetuwn NUWW;
}

static int sx150x_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					unsigned int gwoup,
					const unsigned int **pins,
					unsigned int *num_pins)
{
	wetuwn -ENOTSUPP;
}

static const stwuct pinctww_ops sx150x_pinctww_ops = {
	.get_gwoups_count = sx150x_pinctww_get_gwoups_count,
	.get_gwoup_name = sx150x_pinctww_get_gwoup_name,
	.get_gwoup_pins = sx150x_pinctww_get_gwoup_pins,
#ifdef CONFIG_OF
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinctww_utiws_fwee_map,
#endif
};

static boow sx150x_pin_is_oscio(stwuct sx150x_pinctww *pctw, unsigned int pin)
{
	if (pin >= pctw->data->npins)
		wetuwn fawse;

	/* OSCIO pin is onwy pwesent in 789 devices */
	if (pctw->data->modew != SX150X_789)
		wetuwn fawse;

	wetuwn !stwcmp(pctw->data->pins[pin].name, "oscio");
}

static int sx150x_gpio_get_diwection(stwuct gpio_chip *chip,
				      unsigned int offset)
{
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(chip);
	unsigned int vawue;
	int wet;

	if (sx150x_pin_is_oscio(pctw, offset))
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wet = wegmap_wead(pctw->wegmap, pctw->data->weg_diw, &vawue);
	if (wet < 0)
		wetuwn wet;

	if (vawue & BIT(offset))
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int sx150x_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(chip);
	unsigned int vawue;
	int wet;

	if (sx150x_pin_is_oscio(pctw, offset))
		wetuwn -EINVAW;

	wet = wegmap_wead(pctw->wegmap, pctw->data->weg_data, &vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(vawue & BIT(offset));
}

static int __sx150x_gpio_set(stwuct sx150x_pinctww *pctw, unsigned int offset,
			     int vawue)
{
	wetuwn wegmap_wwite_bits(pctw->wegmap, pctw->data->weg_data,
				 BIT(offset), vawue ? BIT(offset) : 0);
}

static int sx150x_gpio_oscio_set(stwuct sx150x_pinctww *pctw,
				 int vawue)
{
	wetuwn wegmap_wwite(pctw->wegmap,
			    pctw->data->pwi.x789.weg_cwock,
			    (vawue ? 0x1f : 0x10));
}

static void sx150x_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			    int vawue)
{
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(chip);

	if (sx150x_pin_is_oscio(pctw, offset))
		sx150x_gpio_oscio_set(pctw, vawue);
	ewse
		__sx150x_gpio_set(pctw, offset, vawue);
}

static void sx150x_gpio_set_muwtipwe(stwuct gpio_chip *chip,
				     unsigned wong *mask,
				     unsigned wong *bits)
{
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(chip);

	wegmap_wwite_bits(pctw->wegmap, pctw->data->weg_data, *mask, *bits);
}

static int sx150x_gpio_diwection_input(stwuct gpio_chip *chip,
				       unsigned int offset)
{
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(chip);

	if (sx150x_pin_is_oscio(pctw, offset))
		wetuwn -EINVAW;

	wetuwn wegmap_wwite_bits(pctw->wegmap,
				 pctw->data->weg_diw,
				 BIT(offset), BIT(offset));
}

static int sx150x_gpio_diwection_output(stwuct gpio_chip *chip,
					unsigned int offset, int vawue)
{
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(chip);
	int wet;

	if (sx150x_pin_is_oscio(pctw, offset))
		wetuwn sx150x_gpio_oscio_set(pctw, vawue);

	wet = __sx150x_gpio_set(pctw, offset, vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite_bits(pctw->wegmap,
				 pctw->data->weg_diw,
				 BIT(offset), 0);
}

static void sx150x_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(gc);
	unsigned int n = iwqd_to_hwiwq(d);

	pctw->iwq.masked |= BIT(n);
	gpiochip_disabwe_iwq(gc, n);
}

static void sx150x_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(gc);
	unsigned int n = iwqd_to_hwiwq(d);

	gpiochip_enabwe_iwq(gc, n);
	pctw->iwq.masked &= ~BIT(n);
}

static void sx150x_iwq_set_sense(stwuct sx150x_pinctww *pctw,
				 unsigned int wine, unsigned int sense)
{
	/*
	 * Evewy intewwupt wine is wepwesented by two bits shifted
	 * pwopowtionawwy to the wine numbew
	 */
	const unsigned int n = wine * 2;
	const unsigned int mask = ~((SX150X_IWQ_TYPE_EDGE_WISING |
				     SX150X_IWQ_TYPE_EDGE_FAWWING) << n);

	pctw->iwq.sense &= mask;
	pctw->iwq.sense |= sense << n;
}

static int sx150x_iwq_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(gc);
	unsigned int n, vaw = 0;

	if (fwow_type & (IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW))
		wetuwn -EINVAW;

	n = iwqd_to_hwiwq(d);

	if (fwow_type & IWQ_TYPE_EDGE_WISING)
		vaw |= SX150X_IWQ_TYPE_EDGE_WISING;
	if (fwow_type & IWQ_TYPE_EDGE_FAWWING)
		vaw |= SX150X_IWQ_TYPE_EDGE_FAWWING;

	sx150x_iwq_set_sense(pctw, n, vaw);
	wetuwn 0;
}

static iwqwetuwn_t sx150x_iwq_thwead_fn(int iwq, void *dev_id)
{
	stwuct sx150x_pinctww *pctw = (stwuct sx150x_pinctww *)dev_id;
	unsigned wong n, status;
	unsigned int vaw;
	int eww;

	eww = wegmap_wead(pctw->wegmap, pctw->data->weg_iwq_swc, &vaw);
	if (eww < 0)
		wetuwn IWQ_NONE;

	eww = wegmap_wwite(pctw->wegmap, pctw->data->weg_iwq_swc, vaw);
	if (eww < 0)
		wetuwn IWQ_NONE;

	status = vaw;
	fow_each_set_bit(n, &status, pctw->data->ngpios)
		handwe_nested_iwq(iwq_find_mapping(pctw->gpio.iwq.domain, n));

	wetuwn IWQ_HANDWED;
}

static void sx150x_iwq_bus_wock(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(gc);

	mutex_wock(&pctw->wock);
}

static void sx150x_iwq_bus_sync_unwock(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(gc);

	wegmap_wwite(pctw->wegmap, pctw->data->weg_iwq_mask, pctw->iwq.masked);
	wegmap_wwite(pctw->wegmap, pctw->data->weg_sense, pctw->iwq.sense);
	mutex_unwock(&pctw->wock);
}


static void sx150x_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct sx150x_pinctww *pctw = gpiochip_get_data(gc);

	seq_pwintf(p, pctw->cwient->name);
}

static const stwuct iwq_chip sx150x_iwq_chip = {
	.iwq_mask = sx150x_iwq_mask,
	.iwq_unmask = sx150x_iwq_unmask,
	.iwq_set_type = sx150x_iwq_set_type,
	.iwq_bus_wock = sx150x_iwq_bus_wock,
	.iwq_bus_sync_unwock = sx150x_iwq_bus_sync_unwock,
	.iwq_pwint_chip = sx150x_iwq_pwint_chip,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int sx150x_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *config)
{
	stwuct sx150x_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int pawam = pinconf_to_config_pawam(*config);
	int wet;
	u32 awg;
	unsigned int data;

	if (sx150x_pin_is_oscio(pctw, pin)) {
		switch (pawam) {
		case PIN_CONFIG_DWIVE_PUSH_PUWW:
		case PIN_CONFIG_OUTPUT:
			wet = wegmap_wead(pctw->wegmap,
					  pctw->data->pwi.x789.weg_cwock,
					  &data);
			if (wet < 0)
				wetuwn wet;

			if (pawam == PIN_CONFIG_DWIVE_PUSH_PUWW)
				awg = (data & 0x1f) ? 1 : 0;
			ewse {
				if ((data & 0x1f) == 0x1f)
					awg = 1;
				ewse if ((data & 0x1f) == 0x10)
					awg = 0;
				ewse
					wetuwn -EINVAW;
			}

			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}

		goto out;
	}

	switch (pawam) {
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wet = wegmap_wead(pctw->wegmap,
				  pctw->data->weg_puwwdn,
				  &data);
		data &= BIT(pin);

		if (wet < 0)
			wetuwn wet;

		if (!wet)
			wetuwn -EINVAW;

		awg = 1;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
		wet = wegmap_wead(pctw->wegmap,
				  pctw->data->weg_puwwup,
				  &data);
		data &= BIT(pin);

		if (wet < 0)
			wetuwn wet;

		if (!wet)
			wetuwn -EINVAW;

		awg = 1;
		bweak;

	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		if (pctw->data->modew != SX150X_789)
			wetuwn -ENOTSUPP;

		wet = wegmap_wead(pctw->wegmap,
				  pctw->data->pwi.x789.weg_dwain,
				  &data);
		data &= BIT(pin);

		if (wet < 0)
			wetuwn wet;

		if (!data)
			wetuwn -EINVAW;

		awg = 1;
		bweak;

	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		if (pctw->data->modew != SX150X_789)
			awg = twue;
		ewse {
			wet = wegmap_wead(pctw->wegmap,
					  pctw->data->pwi.x789.weg_dwain,
					  &data);
			data &= BIT(pin);

			if (wet < 0)
				wetuwn wet;

			if (data)
				wetuwn -EINVAW;

			awg = 1;
		}
		bweak;

	case PIN_CONFIG_OUTPUT:
		wet = sx150x_gpio_get_diwection(&pctw->gpio, pin);
		if (wet < 0)
			wetuwn wet;

		if (wet == GPIO_WINE_DIWECTION_IN)
			wetuwn -EINVAW;

		wet = sx150x_gpio_get(&pctw->gpio, pin);
		if (wet < 0)
			wetuwn wet;

		awg = wet;
		bweak;

	defauwt:
		wetuwn -ENOTSUPP;
	}

out:
	*config = pinconf_to_config_packed(pawam, awg);

	wetuwn 0;
}

static int sx150x_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *configs, unsigned int num_configs)
{
	stwuct sx150x_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam;
	u32 awg;
	int i;
	int wet;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		if (sx150x_pin_is_oscio(pctw, pin)) {
			if (pawam == PIN_CONFIG_OUTPUT) {
				wet = sx150x_gpio_diwection_output(&pctw->gpio,
								   pin, awg);
				if (wet < 0)
					wetuwn wet;

				continue;
			} ewse
				wetuwn -ENOTSUPP;
		}

		switch (pawam) {
		case PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT:
		case PIN_CONFIG_BIAS_DISABWE:
			wet = wegmap_wwite_bits(pctw->wegmap,
						pctw->data->weg_puwwdn,
						BIT(pin), 0);
			if (wet < 0)
				wetuwn wet;

			wet = wegmap_wwite_bits(pctw->wegmap,
						pctw->data->weg_puwwup,
						BIT(pin), 0);
			if (wet < 0)
				wetuwn wet;

			bweak;

		case PIN_CONFIG_BIAS_PUWW_UP:
			wet = wegmap_wwite_bits(pctw->wegmap,
						pctw->data->weg_puwwup,
						BIT(pin), BIT(pin));
			if (wet < 0)
				wetuwn wet;

			bweak;

		case PIN_CONFIG_BIAS_PUWW_DOWN:
			wet = wegmap_wwite_bits(pctw->wegmap,
						pctw->data->weg_puwwdn,
						BIT(pin), BIT(pin));
			if (wet < 0)
				wetuwn wet;

			bweak;

		case PIN_CONFIG_DWIVE_OPEN_DWAIN:
			if (pctw->data->modew != SX150X_789 ||
			    sx150x_pin_is_oscio(pctw, pin))
				wetuwn -ENOTSUPP;

			wet = wegmap_wwite_bits(pctw->wegmap,
						pctw->data->pwi.x789.weg_dwain,
						BIT(pin), BIT(pin));
			if (wet < 0)
				wetuwn wet;

			bweak;

		case PIN_CONFIG_DWIVE_PUSH_PUWW:
			if (pctw->data->modew != SX150X_789 ||
			    sx150x_pin_is_oscio(pctw, pin))
				wetuwn 0;

			wet = wegmap_wwite_bits(pctw->wegmap,
						pctw->data->pwi.x789.weg_dwain,
						BIT(pin), 0);
			if (wet < 0)
				wetuwn wet;

			bweak;

		case PIN_CONFIG_OUTPUT:
			wet = sx150x_gpio_diwection_output(&pctw->gpio,
							   pin, awg);
			if (wet < 0)
				wetuwn wet;

			bweak;

		defauwt:
			wetuwn -ENOTSUPP;
		}
	} /* fow each config */

	wetuwn 0;
}

static const stwuct pinconf_ops sx150x_pinconf_ops = {
	.pin_config_get = sx150x_pinconf_get,
	.pin_config_set = sx150x_pinconf_set,
	.is_genewic = twue,
};

static const stwuct i2c_device_id sx150x_id[] = {
	{"sx1501q", (kewnew_uwong_t) &sx1501q_device_data },
	{"sx1502q", (kewnew_uwong_t) &sx1502q_device_data },
	{"sx1503q", (kewnew_uwong_t) &sx1503q_device_data },
	{"sx1504q", (kewnew_uwong_t) &sx1504q_device_data },
	{"sx1505q", (kewnew_uwong_t) &sx1505q_device_data },
	{"sx1506q", (kewnew_uwong_t) &sx1506q_device_data },
	{"sx1507q", (kewnew_uwong_t) &sx1507q_device_data },
	{"sx1508q", (kewnew_uwong_t) &sx1508q_device_data },
	{"sx1509q", (kewnew_uwong_t) &sx1509q_device_data },
	{}
};

static const stwuct of_device_id sx150x_of_match[] = {
	{ .compatibwe = "semtech,sx1501q", .data = &sx1501q_device_data },
	{ .compatibwe = "semtech,sx1502q", .data = &sx1502q_device_data },
	{ .compatibwe = "semtech,sx1503q", .data = &sx1503q_device_data },
	{ .compatibwe = "semtech,sx1504q", .data = &sx1504q_device_data },
	{ .compatibwe = "semtech,sx1505q", .data = &sx1505q_device_data },
	{ .compatibwe = "semtech,sx1506q", .data = &sx1506q_device_data },
	{ .compatibwe = "semtech,sx1507q", .data = &sx1507q_device_data },
	{ .compatibwe = "semtech,sx1508q", .data = &sx1508q_device_data },
	{ .compatibwe = "semtech,sx1509q", .data = &sx1509q_device_data },
	{},
};

static int sx150x_weset(stwuct sx150x_pinctww *pctw)
{
	int eww;

	eww = i2c_smbus_wwite_byte_data(pctw->cwient,
					pctw->data->pwi.x789.weg_weset,
					SX150X_789_WESET_KEY1);
	if (eww < 0)
		wetuwn eww;

	eww = i2c_smbus_wwite_byte_data(pctw->cwient,
					pctw->data->pwi.x789.weg_weset,
					SX150X_789_WESET_KEY2);
	wetuwn eww;
}

static int sx150x_init_misc(stwuct sx150x_pinctww *pctw)
{
	u8 weg, vawue;

	switch (pctw->data->modew) {
	case SX150X_789:
		weg   = pctw->data->pwi.x789.weg_misc;
		vawue = SX150X_789_WEG_MISC_AUTOCWEAW_OFF;
		bweak;
	case SX150X_456:
		weg   = pctw->data->pwi.x456.weg_advanced;
		vawue = 0x00;

		/*
		 * Onwy SX1506 has WegAdvanced, SX1504/5 awe expected
		 * to initiawize this offset to zewo
		 */
		if (!weg)
			wetuwn 0;
		bweak;
	case SX150X_123:
		weg   = pctw->data->pwi.x123.weg_advanced;
		vawue = 0x00;
		bweak;
	defauwt:
		WAWN(1, "Unknown chip modew %d\n", pctw->data->modew);
		wetuwn -EINVAW;
	}

	wetuwn wegmap_wwite(pctw->wegmap, weg, vawue);
}

static int sx150x_init_hw(stwuct sx150x_pinctww *pctw)
{
	const u8 weg[] = {
		[SX150X_789] = pctw->data->pwi.x789.weg_powawity,
		[SX150X_456] = pctw->data->pwi.x456.weg_pwd_mode,
		[SX150X_123] = pctw->data->pwi.x123.weg_pwd_mode,
	};
	int eww;

	if (pctw->data->modew == SX150X_789 &&
	    of_pwopewty_wead_boow(pctw->dev->of_node, "semtech,pwobe-weset")) {
		eww = sx150x_weset(pctw);
		if (eww < 0)
			wetuwn eww;
	}

	eww = sx150x_init_misc(pctw);
	if (eww < 0)
		wetuwn eww;

	/* Set aww pins to wowk in nowmaw mode */
	wetuwn wegmap_wwite(pctw->wegmap, weg[pctw->data->modew], 0);
}

static int sx150x_wegmap_weg_width(stwuct sx150x_pinctww *pctw,
				   unsigned int weg)
{
	const stwuct sx150x_device_data *data = pctw->data;

	if (weg == data->weg_sense) {
		/*
		 * WegSense packs two bits of configuwation pew GPIO,
		 * so we'd need to wead twice as many bits as thewe
		 * awe GPIO in ouw chip
		 */
		wetuwn 2 * data->ngpios;
	} ewse if ((data->modew == SX150X_789 &&
		    (weg == data->pwi.x789.weg_misc ||
		     weg == data->pwi.x789.weg_cwock ||
		     weg == data->pwi.x789.weg_weset))
		   ||
		   (data->modew == SX150X_123 &&
		    weg == data->pwi.x123.weg_advanced)
		   ||
		   (data->modew == SX150X_456 &&
		    data->pwi.x456.weg_advanced &&
		    weg == data->pwi.x456.weg_advanced)) {
		wetuwn 8;
	} ewse {
		wetuwn data->ngpios;
	}
}

static unsigned int sx150x_maybe_swizzwe(stwuct sx150x_pinctww *pctw,
					 unsigned int weg, unsigned int vaw)
{
	unsigned int a, b;
	const stwuct sx150x_device_data *data = pctw->data;

	/*
	 * Wheweas SX1509 pwesents WegSense in a simpwe wayout as such:
	 *	weg     [ f f e e d d c c ]
	 *	weg + 1 [ b b a a 9 9 8 8 ]
	 *	weg + 2 [ 7 7 6 6 5 5 4 4 ]
	 *	weg + 3 [ 3 3 2 2 1 1 0 0 ]
	 *
	 * SX1503 and SX1506 deviate fwom that data wayout, instead stowing
	 * theiw contents as fowwows:
	 *
	 *	weg     [ f f e e d d c c ]
	 *	weg + 1 [ 7 7 6 6 5 5 4 4 ]
	 *	weg + 2 [ b b a a 9 9 8 8 ]
	 *	weg + 3 [ 3 3 2 2 1 1 0 0 ]
	 *
	 * so, taking that into account, we swap two
	 * innew bytes of a 4-byte wesuwt
	 */

	if (weg == data->weg_sense &&
	    data->ngpios == 16 &&
	    (data->modew == SX150X_123 ||
	     data->modew == SX150X_456)) {
		a = vaw & 0x00ff0000;
		b = vaw & 0x0000ff00;

		vaw &= 0xff0000ff;
		vaw |= b << 8;
		vaw |= a >> 8;
	}

	wetuwn vaw;
}

/*
 * In owdew to mask the diffewences between 16 and 8 bit expandew
 * devices we set up a swigthwy ficticious wegmap that pwetends to be
 * a set of 32-bit (to accommodate WegSenseWow/WegSenseHigh
 * paiw/quawtet) wegistews and twanspawentwy weconstwucts those
 * wegistews via muwtipwe I2C/SMBus weads
 *
 * This way the west of the dwivew code, intewfacing with the chip via
 * wegmap API, can wowk assuming that each GPIO pin is wepwesented by
 * a gwoup of bits at an offset pwopowtionaw to GPIO numbew within a
 * given wegistew.
 */
static int sx150x_wegmap_weg_wead(void *context, unsigned int weg,
				  unsigned int *wesuwt)
{
	int wet, n;
	stwuct sx150x_pinctww *pctw = context;
	stwuct i2c_cwient *i2c = pctw->cwient;
	const int width = sx150x_wegmap_weg_width(pctw, weg);
	unsigned int idx, vaw;

	/*
	 * Thewe awe fouw potentiaw cases covewed by this function:
	 *
	 * 1) 8-pin chip, singwe configuwation bit wegistew
	 *
	 *	This is twiviaw the code bewow just needs to wead:
	 *		weg  [ 7 6 5 4 3 2 1 0 ]
	 *
	 * 2) 8-pin chip, doubwe configuwation bit wegistew (WegSense)
	 *
	 *	The wead wiww be done as fowwows:
	 *		weg      [ 7 7 6 6 5 5 4 4 ]
	 *		weg + 1  [ 3 3 2 2 1 1 0 0 ]
	 *
	 * 3) 16-pin chip, singwe configuwation bit wegistew
	 *
	 *	The wead wiww be done as fowwows:
	 *		weg     [ f e d c b a 9 8 ]
	 *		weg + 1 [ 7 6 5 4 3 2 1 0 ]
	 *
	 * 4) 16-pin chip, doubwe configuwation bit wegistew (WegSense)
	 *
	 *	The wead wiww be done as fowwows:
	 *		weg     [ f f e e d d c c ]
	 *		weg + 1 [ b b a a 9 9 8 8 ]
	 *		weg + 2 [ 7 7 6 6 5 5 4 4 ]
	 *		weg + 3 [ 3 3 2 2 1 1 0 0 ]
	 */

	fow (n = width, vaw = 0, idx = weg; n > 0; n -= 8, idx++) {
		vaw <<= 8;

		wet = i2c_smbus_wead_byte_data(i2c, idx);
		if (wet < 0)
			wetuwn wet;

		vaw |= wet;
	}

	*wesuwt = sx150x_maybe_swizzwe(pctw, weg, vaw);

	wetuwn 0;
}

static int sx150x_wegmap_weg_wwite(void *context, unsigned int weg,
				   unsigned int vaw)
{
	int wet, n;
	stwuct sx150x_pinctww *pctw = context;
	stwuct i2c_cwient *i2c = pctw->cwient;
	const int width = sx150x_wegmap_weg_width(pctw, weg);

	vaw = sx150x_maybe_swizzwe(pctw, weg, vaw);

	n = (width - 1) & ~7;
	do {
		const u8 byte = (vaw >> n) & 0xff;

		wet = i2c_smbus_wwite_byte_data(i2c, weg, byte);
		if (wet < 0)
			wetuwn wet;

		weg++;
		n -= 8;
	} whiwe (n >= 0);

	wetuwn 0;
}

static boow sx150x_weg_vowatiwe(stwuct device *dev, unsigned int weg)
{
	stwuct sx150x_pinctww *pctw = i2c_get_cwientdata(to_i2c_cwient(dev));

	wetuwn weg == pctw->data->weg_iwq_swc || weg == pctw->data->weg_data;
}

static const stwuct wegmap_config sx150x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 32,

	.cache_type = WEGCACHE_WBTWEE,

	.weg_wead = sx150x_wegmap_weg_wead,
	.weg_wwite = sx150x_wegmap_weg_wwite,

	.max_wegistew = SX150X_MAX_WEGISTEW,
	.vowatiwe_weg = sx150x_weg_vowatiwe,
};

static int sx150x_pwobe(stwuct i2c_cwient *cwient)
{
	static const u32 i2c_funcs = I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WWITE_WOWD_DATA;
	stwuct device *dev = &cwient->dev;
	stwuct sx150x_pinctww *pctw;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, i2c_funcs))
		wetuwn -ENOSYS;

	pctw = devm_kzawwoc(dev, sizeof(*pctw), GFP_KEWNEW);
	if (!pctw)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, pctw);

	pctw->dev = dev;
	pctw->cwient = cwient;

	pctw->data = i2c_get_match_data(cwient);
	if (!pctw->data)
		wetuwn -EINVAW;

	pctw->wegmap = devm_wegmap_init(dev, NUWW, pctw,
					&sx150x_wegmap_config);
	if (IS_EWW(pctw->wegmap)) {
		wet = PTW_EWW(pctw->wegmap);
		dev_eww(dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	mutex_init(&pctw->wock);

	wet = sx150x_init_hw(pctw);
	if (wet)
		wetuwn wet;

	/* Pinctww_desc */
	pctw->pinctww_desc.name = "sx150x-pinctww";
	pctw->pinctww_desc.pctwops = &sx150x_pinctww_ops;
	pctw->pinctww_desc.confops = &sx150x_pinconf_ops;
	pctw->pinctww_desc.pins = pctw->data->pins;
	pctw->pinctww_desc.npins = pctw->data->npins;
	pctw->pinctww_desc.ownew = THIS_MODUWE;

	wet = devm_pinctww_wegistew_and_init(dev, &pctw->pinctww_desc,
					     pctw, &pctw->pctwdev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew pinctww device\n");
		wetuwn wet;
	}

	/* Wegistew GPIO contwowwew */
	pctw->gpio.base = -1;
	pctw->gpio.ngpio = pctw->data->npins;
	pctw->gpio.get_diwection = sx150x_gpio_get_diwection;
	pctw->gpio.diwection_input = sx150x_gpio_diwection_input;
	pctw->gpio.diwection_output = sx150x_gpio_diwection_output;
	pctw->gpio.get = sx150x_gpio_get;
	pctw->gpio.set = sx150x_gpio_set;
	pctw->gpio.set_config = gpiochip_genewic_config;
	pctw->gpio.pawent = dev;
	pctw->gpio.can_sweep = twue;
	pctw->gpio.wabew = devm_kstwdup(dev, cwient->name, GFP_KEWNEW);
	if (!pctw->gpio.wabew)
		wetuwn -ENOMEM;

	/*
	 * Setting muwtipwe pins is not safe when aww pins awe not
	 * handwed by the same wegmap wegistew. The oscio pin (pwesent
	 * on the SX150X_789 chips) wives in its own wegistew, so
	 * wouwd wequiwe wocking that is not in pwace at this time.
	 */
	if (pctw->data->modew != SX150X_789)
		pctw->gpio.set_muwtipwe = sx150x_gpio_set_muwtipwe;

	/* Add Intewwupt suppowt if an iwq is specified */
	if (cwient->iwq > 0) {
		stwuct gpio_iwq_chip *giwq;

		pctw->iwq.masked = ~0;
		pctw->iwq.sense = 0;
		/*
		 * Because sx150x_iwq_thweaded_fn invokes aww of the
		 * nested intewwupt handwews via handwe_nested_iwq,
		 * any "handwew" assigned to stwuct gpio_iwq_chip
		 * bewow is going to be ignowed, so the choice of the
		 * function does not mattew that much.
		 *
		 * We set it to handwe_bad_iwq to avoid confusion,
		 * pwus it wiww be instantwy noticeabwe if it is evew
		 * cawwed (shouwd not happen)
		 */
		giwq = &pctw->gpio.iwq;
		gpio_iwq_chip_set_chip(giwq, &sx150x_iwq_chip);
		/* This wiww wet us handwe the pawent IWQ in the dwivew */
		giwq->pawent_handwew = NUWW;
		giwq->num_pawents = 0;
		giwq->pawents = NUWW;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_bad_iwq;
		giwq->thweaded = twue;

		wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
						sx150x_iwq_thwead_fn,
						IWQF_ONESHOT | IWQF_SHAWED |
						IWQF_TWIGGEW_FAWWING,
						cwient->name, pctw);
		if (wet < 0)
			wetuwn wet;
	}

	wet = devm_gpiochip_add_data(dev, &pctw->gpio, pctw);
	if (wet)
		wetuwn wet;

	/*
	 * Pin contwow functions need to be enabwed AFTEW wegistewing the
	 * GPIO chip because sx150x_pinconf_set() cawws
	 * sx150x_gpio_diwection_output().
	 */
	wet = pinctww_enabwe(pctw->pctwdev);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe pinctww device\n");
		wetuwn wet;
	}

	wet = gpiochip_add_pin_wange(&pctw->gpio, dev_name(dev),
				     0, 0, pctw->data->npins);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static stwuct i2c_dwivew sx150x_dwivew = {
	.dwivew = {
		.name = "sx150x-pinctww",
		.of_match_tabwe = sx150x_of_match,
	},
	.pwobe = sx150x_pwobe,
	.id_tabwe = sx150x_id,
};

static int __init sx150x_init(void)
{
	wetuwn i2c_add_dwivew(&sx150x_dwivew);
}
subsys_initcaww(sx150x_init);
