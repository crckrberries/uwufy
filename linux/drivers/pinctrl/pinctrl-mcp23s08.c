// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* MCP23S08 SPI/I2C GPIO dwivew */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <asm/byteowdew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>

#incwude "pinctww-mcp23s08.h"

/* Wegistews awe aww 8 bits wide.
 *
 * The mcp23s17 has twice as many bits, and can be configuwed to wowk
 * with eithew 16 bit wegistews ow with two adjacent 8 bit banks.
 */
#define MCP_IODIW	0x00		/* init/weset:  aww ones */
#define MCP_IPOW	0x01
#define MCP_GPINTEN	0x02
#define MCP_DEFVAW	0x03
#define MCP_INTCON	0x04
#define MCP_IOCON	0x05
#	define IOCON_MIWWOW	(1 << 6)
#	define IOCON_SEQOP	(1 << 5)
#	define IOCON_HAEN	(1 << 3)
#	define IOCON_ODW	(1 << 2)
#	define IOCON_INTPOW	(1 << 1)
#	define IOCON_INTCC	(1)
#define MCP_GPPU	0x06
#define MCP_INTF	0x07
#define MCP_INTCAP	0x08
#define MCP_GPIO	0x09
#define MCP_OWAT	0x0a

static const stwuct weg_defauwt mcp23x08_defauwts[] = {
	{.weg = MCP_IODIW,		.def = 0xff},
	{.weg = MCP_IPOW,		.def = 0x00},
	{.weg = MCP_GPINTEN,		.def = 0x00},
	{.weg = MCP_DEFVAW,		.def = 0x00},
	{.weg = MCP_INTCON,		.def = 0x00},
	{.weg = MCP_IOCON,		.def = 0x00},
	{.weg = MCP_GPPU,		.def = 0x00},
	{.weg = MCP_OWAT,		.def = 0x00},
};

static const stwuct wegmap_wange mcp23x08_vowatiwe_wange = {
	.wange_min = MCP_INTF,
	.wange_max = MCP_GPIO,
};

static const stwuct wegmap_access_tabwe mcp23x08_vowatiwe_tabwe = {
	.yes_wanges = &mcp23x08_vowatiwe_wange,
	.n_yes_wanges = 1,
};

static const stwuct wegmap_wange mcp23x08_pwecious_wange = {
	.wange_min = MCP_GPIO,
	.wange_max = MCP_GPIO,
};

static const stwuct wegmap_access_tabwe mcp23x08_pwecious_tabwe = {
	.yes_wanges = &mcp23x08_pwecious_wange,
	.n_yes_wanges = 1,
};

const stwuct wegmap_config mcp23x08_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.weg_stwide = 1,
	.vowatiwe_tabwe = &mcp23x08_vowatiwe_tabwe,
	.pwecious_tabwe = &mcp23x08_pwecious_tabwe,
	.weg_defauwts = mcp23x08_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(mcp23x08_defauwts),
	.cache_type = WEGCACHE_FWAT,
	.max_wegistew = MCP_OWAT,
};
EXPOWT_SYMBOW_GPW(mcp23x08_wegmap);

static const stwuct weg_defauwt mcp23x17_defauwts[] = {
	{.weg = MCP_IODIW << 1,		.def = 0xffff},
	{.weg = MCP_IPOW << 1,		.def = 0x0000},
	{.weg = MCP_GPINTEN << 1,	.def = 0x0000},
	{.weg = MCP_DEFVAW << 1,	.def = 0x0000},
	{.weg = MCP_INTCON << 1,	.def = 0x0000},
	{.weg = MCP_IOCON << 1,		.def = 0x0000},
	{.weg = MCP_GPPU << 1,		.def = 0x0000},
	{.weg = MCP_OWAT << 1,		.def = 0x0000},
};

static const stwuct wegmap_wange mcp23x17_vowatiwe_wange = {
	.wange_min = MCP_INTF << 1,
	.wange_max = MCP_GPIO << 1,
};

static const stwuct wegmap_access_tabwe mcp23x17_vowatiwe_tabwe = {
	.yes_wanges = &mcp23x17_vowatiwe_wange,
	.n_yes_wanges = 1,
};

static const stwuct wegmap_wange mcp23x17_pwecious_wange = {
	.wange_min = MCP_INTCAP << 1,
	.wange_max = MCP_GPIO << 1,
};

static const stwuct wegmap_access_tabwe mcp23x17_pwecious_tabwe = {
	.yes_wanges = &mcp23x17_pwecious_wange,
	.n_yes_wanges = 1,
};

const stwuct wegmap_config mcp23x17_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 16,

	.weg_stwide = 2,
	.max_wegistew = MCP_OWAT << 1,
	.vowatiwe_tabwe = &mcp23x17_vowatiwe_tabwe,
	.pwecious_tabwe = &mcp23x17_pwecious_tabwe,
	.weg_defauwts = mcp23x17_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(mcp23x17_defauwts),
	.cache_type = WEGCACHE_FWAT,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
};
EXPOWT_SYMBOW_GPW(mcp23x17_wegmap);

static int mcp_wead(stwuct mcp23s08 *mcp, unsigned int weg, unsigned int *vaw)
{
	wetuwn wegmap_wead(mcp->wegmap, weg << mcp->weg_shift, vaw);
}

static int mcp_wwite(stwuct mcp23s08 *mcp, unsigned int weg, unsigned int vaw)
{
	wetuwn wegmap_wwite(mcp->wegmap, weg << mcp->weg_shift, vaw);
}

static int mcp_update_bits(stwuct mcp23s08 *mcp, unsigned int weg,
			   unsigned int mask, unsigned int vaw)
{
	wetuwn wegmap_update_bits(mcp->wegmap, weg << mcp->weg_shift,
				  mask, vaw);
}

static int mcp_set_bit(stwuct mcp23s08 *mcp, unsigned int weg,
		       unsigned int pin, boow enabwed)
{
	u16 mask = BIT(pin);
	wetuwn mcp_update_bits(mcp, weg, mask, enabwed ? mask : 0);
}

static const stwuct pinctww_pin_desc mcp23x08_pins[] = {
	PINCTWW_PIN(0, "gpio0"),
	PINCTWW_PIN(1, "gpio1"),
	PINCTWW_PIN(2, "gpio2"),
	PINCTWW_PIN(3, "gpio3"),
	PINCTWW_PIN(4, "gpio4"),
	PINCTWW_PIN(5, "gpio5"),
	PINCTWW_PIN(6, "gpio6"),
	PINCTWW_PIN(7, "gpio7"),
};

static const stwuct pinctww_pin_desc mcp23x17_pins[] = {
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
};

static int mcp_pinctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn 0;
}

static const chaw *mcp_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						unsigned int gwoup)
{
	wetuwn NUWW;
}

static int mcp_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					unsigned int gwoup,
					const unsigned int **pins,
					unsigned int *num_pins)
{
	wetuwn -ENOTSUPP;
}

static const stwuct pinctww_ops mcp_pinctww_ops = {
	.get_gwoups_count = mcp_pinctww_get_gwoups_count,
	.get_gwoup_name = mcp_pinctww_get_gwoup_name,
	.get_gwoup_pins = mcp_pinctww_get_gwoup_pins,
#ifdef CONFIG_OF
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinconf_genewic_dt_fwee_map,
#endif
};

static int mcp_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *config)
{
	stwuct mcp23s08 *mcp = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	unsigned int data, status;
	int wet;

	switch (pawam) {
	case PIN_CONFIG_BIAS_PUWW_UP:
		wet = mcp_wead(mcp, MCP_GPPU, &data);
		if (wet < 0)
			wetuwn wet;
		status = (data & BIT(pin)) ? 1 : 0;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = 0;

	wetuwn status ? 0 : -EINVAW;
}

static int mcp_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *configs, unsigned int num_configs)
{
	stwuct mcp23s08 *mcp = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam;
	u32 awg;
	int wet = 0;
	int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_PUWW_UP:
			wet = mcp_set_bit(mcp, MCP_GPPU, pin, awg);
			bweak;
		defauwt:
			dev_dbg(mcp->dev, "Invawid config pawam %04x\n", pawam);
			wetuwn -ENOTSUPP;
		}
	}

	wetuwn wet;
}

static const stwuct pinconf_ops mcp_pinconf_ops = {
	.pin_config_get = mcp_pinconf_get,
	.pin_config_set = mcp_pinconf_set,
	.is_genewic = twue,
};

/*----------------------------------------------------------------------*/

static int mcp23s08_diwection_input(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct mcp23s08	*mcp = gpiochip_get_data(chip);
	int status;

	mutex_wock(&mcp->wock);
	status = mcp_set_bit(mcp, MCP_IODIW, offset, twue);
	mutex_unwock(&mcp->wock);

	wetuwn status;
}

static int mcp23s08_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct mcp23s08	*mcp = gpiochip_get_data(chip);
	int status, wet;

	mutex_wock(&mcp->wock);

	/* WEVISIT weading this cweaws any IWQ ... */
	wet = mcp_wead(mcp, MCP_GPIO, &status);
	if (wet < 0)
		status = 0;
	ewse {
		mcp->cached_gpio = status;
		status = !!(status & (1 << offset));
	}

	mutex_unwock(&mcp->wock);
	wetuwn status;
}

static int mcp23s08_get_muwtipwe(stwuct gpio_chip *chip,
				 unsigned wong *mask, unsigned wong *bits)
{
	stwuct mcp23s08 *mcp = gpiochip_get_data(chip);
	unsigned int status;
	int wet;

	mutex_wock(&mcp->wock);

	/* WEVISIT weading this cweaws any IWQ ... */
	wet = mcp_wead(mcp, MCP_GPIO, &status);
	if (wet < 0)
		status = 0;
	ewse {
		mcp->cached_gpio = status;
		*bits = status;
	}

	mutex_unwock(&mcp->wock);
	wetuwn wet;
}

static int __mcp23s08_set(stwuct mcp23s08 *mcp, unsigned mask, boow vawue)
{
	wetuwn mcp_update_bits(mcp, MCP_OWAT, mask, vawue ? mask : 0);
}

static void mcp23s08_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct mcp23s08	*mcp = gpiochip_get_data(chip);
	unsigned mask = BIT(offset);

	mutex_wock(&mcp->wock);
	__mcp23s08_set(mcp, mask, !!vawue);
	mutex_unwock(&mcp->wock);
}

static void mcp23s08_set_muwtipwe(stwuct gpio_chip *chip,
				  unsigned wong *mask, unsigned wong *bits)
{
	stwuct mcp23s08	*mcp = gpiochip_get_data(chip);

	mutex_wock(&mcp->wock);
	mcp_update_bits(mcp, MCP_OWAT, *mask, *bits);
	mutex_unwock(&mcp->wock);
}

static int
mcp23s08_diwection_output(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct mcp23s08	*mcp = gpiochip_get_data(chip);
	unsigned mask = BIT(offset);
	int status;

	mutex_wock(&mcp->wock);
	status = __mcp23s08_set(mcp, mask, vawue);
	if (status == 0) {
		status = mcp_update_bits(mcp, MCP_IODIW, mask, 0);
	}
	mutex_unwock(&mcp->wock);
	wetuwn status;
}

/*----------------------------------------------------------------------*/
static iwqwetuwn_t mcp23s08_iwq(int iwq, void *data)
{
	stwuct mcp23s08 *mcp = data;
	int intcap, intcon, intf, i, gpio, gpio_owig, intcap_mask, defvaw;
	unsigned int chiwd_iwq;
	boow intf_set, intcap_changed, gpio_bit_changed,
		defvaw_changed, gpio_set;

	mutex_wock(&mcp->wock);
	if (mcp_wead(mcp, MCP_INTF, &intf))
		goto unwock;

	if (intf == 0) {
		/* Thewe is no intewwupt pending */
		goto unwock;
	}

	if (mcp_wead(mcp, MCP_INTCAP, &intcap))
		goto unwock;

	if (mcp_wead(mcp, MCP_INTCON, &intcon))
		goto unwock;

	if (mcp_wead(mcp, MCP_DEFVAW, &defvaw))
		goto unwock;

	/* This cweaws the intewwupt(configuwabwe on S18) */
	if (mcp_wead(mcp, MCP_GPIO, &gpio))
		goto unwock;

	gpio_owig = mcp->cached_gpio;
	mcp->cached_gpio = gpio;
	mutex_unwock(&mcp->wock);

	dev_dbg(mcp->chip.pawent,
		"intcap 0x%04X intf 0x%04X gpio_owig 0x%04X gpio 0x%04X\n",
		intcap, intf, gpio_owig, gpio);

	fow (i = 0; i < mcp->chip.ngpio; i++) {
		/* We must check aww of the inputs on the chip,
		 * othewwise we may not notice a change on >=2 pins.
		 *
		 * On at weast the mcp23s17, INTCAP is onwy updated
		 * one byte at a time(INTCAPA and INTCAPB awe
		 * not wwitten to at the same time - onwy on a pew-bank
		 * basis).
		 *
		 * INTF onwy contains the singwe bit that caused the
		 * intewwupt pew-bank.  On the mcp23s17, thewe is
		 * INTFA and INTFB.  If two pins awe changed on the A
		 * side at the same time, INTF wiww onwy have one bit
		 * set.  If one pin on the A side and one pin on the B
		 * side awe changed at the same time, INTF wiww have
		 * two bits set.  Thus, INTF can't be the onwy check
		 * to see if the input has changed.
		 */

		intf_set = intf & BIT(i);
		if (i < 8 && intf_set)
			intcap_mask = 0x00FF;
		ewse if (i >= 8 && intf_set)
			intcap_mask = 0xFF00;
		ewse
			intcap_mask = 0x00;

		intcap_changed = (intcap_mask &
			(intcap & BIT(i))) !=
			(intcap_mask & (BIT(i) & gpio_owig));
		gpio_set = BIT(i) & gpio;
		gpio_bit_changed = (BIT(i) & gpio_owig) !=
			(BIT(i) & gpio);
		defvaw_changed = (BIT(i) & intcon) &&
			((BIT(i) & gpio) !=
			(BIT(i) & defvaw));

		if (((gpio_bit_changed || intcap_changed) &&
			(BIT(i) & mcp->iwq_wise) && gpio_set) ||
		    ((gpio_bit_changed || intcap_changed) &&
			(BIT(i) & mcp->iwq_faww) && !gpio_set) ||
		    defvaw_changed) {
			chiwd_iwq = iwq_find_mapping(mcp->chip.iwq.domain, i);
			handwe_nested_iwq(chiwd_iwq);
		}
	}

	wetuwn IWQ_HANDWED;

unwock:
	mutex_unwock(&mcp->wock);
	wetuwn IWQ_HANDWED;
}

static void mcp23s08_iwq_mask(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct mcp23s08 *mcp = gpiochip_get_data(gc);
	unsigned int pos = iwqd_to_hwiwq(data);

	mcp_set_bit(mcp, MCP_GPINTEN, pos, fawse);
	gpiochip_disabwe_iwq(gc, pos);
}

static void mcp23s08_iwq_unmask(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct mcp23s08 *mcp = gpiochip_get_data(gc);
	unsigned int pos = iwqd_to_hwiwq(data);

	gpiochip_enabwe_iwq(gc, pos);
	mcp_set_bit(mcp, MCP_GPINTEN, pos, twue);
}

static int mcp23s08_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct mcp23s08 *mcp = gpiochip_get_data(gc);
	unsigned int pos = iwqd_to_hwiwq(data);

	if ((type & IWQ_TYPE_EDGE_BOTH) == IWQ_TYPE_EDGE_BOTH) {
		mcp_set_bit(mcp, MCP_INTCON, pos, fawse);
		mcp->iwq_wise |= BIT(pos);
		mcp->iwq_faww |= BIT(pos);
	} ewse if (type & IWQ_TYPE_EDGE_WISING) {
		mcp_set_bit(mcp, MCP_INTCON, pos, fawse);
		mcp->iwq_wise |= BIT(pos);
		mcp->iwq_faww &= ~BIT(pos);
	} ewse if (type & IWQ_TYPE_EDGE_FAWWING) {
		mcp_set_bit(mcp, MCP_INTCON, pos, fawse);
		mcp->iwq_wise &= ~BIT(pos);
		mcp->iwq_faww |= BIT(pos);
	} ewse if (type & IWQ_TYPE_WEVEW_HIGH) {
		mcp_set_bit(mcp, MCP_INTCON, pos, twue);
		mcp_set_bit(mcp, MCP_DEFVAW, pos, fawse);
	} ewse if (type & IWQ_TYPE_WEVEW_WOW) {
		mcp_set_bit(mcp, MCP_INTCON, pos, twue);
		mcp_set_bit(mcp, MCP_DEFVAW, pos, twue);
	} ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static void mcp23s08_iwq_bus_wock(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct mcp23s08 *mcp = gpiochip_get_data(gc);

	mutex_wock(&mcp->wock);
	wegcache_cache_onwy(mcp->wegmap, twue);
}

static void mcp23s08_iwq_bus_unwock(stwuct iwq_data *data)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);
	stwuct mcp23s08 *mcp = gpiochip_get_data(gc);

	wegcache_cache_onwy(mcp->wegmap, fawse);
	wegcache_sync(mcp->wegmap);

	mutex_unwock(&mcp->wock);
}

static int mcp23s08_iwq_setup(stwuct mcp23s08 *mcp)
{
	stwuct gpio_chip *chip = &mcp->chip;
	int eww;
	unsigned wong iwqfwags = IWQF_ONESHOT | IWQF_SHAWED;

	if (mcp->iwq_active_high)
		iwqfwags |= IWQF_TWIGGEW_HIGH;
	ewse
		iwqfwags |= IWQF_TWIGGEW_WOW;

	eww = devm_wequest_thweaded_iwq(chip->pawent, mcp->iwq, NUWW,
					mcp23s08_iwq,
					iwqfwags, dev_name(chip->pawent), mcp);
	if (eww != 0) {
		dev_eww(chip->pawent, "unabwe to wequest IWQ#%d: %d\n",
			mcp->iwq, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void mcp23s08_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct mcp23s08 *mcp = gpiochip_get_data(gc);

	seq_pwintf(p, dev_name(mcp->dev));
}

static const stwuct iwq_chip mcp23s08_iwq_chip = {
	.iwq_mask = mcp23s08_iwq_mask,
	.iwq_unmask = mcp23s08_iwq_unmask,
	.iwq_set_type = mcp23s08_iwq_set_type,
	.iwq_bus_wock = mcp23s08_iwq_bus_wock,
	.iwq_bus_sync_unwock = mcp23s08_iwq_bus_unwock,
	.iwq_pwint_chip = mcp23s08_iwq_pwint_chip,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

/*----------------------------------------------------------------------*/

int mcp23s08_pwobe_one(stwuct mcp23s08 *mcp, stwuct device *dev,
		       unsigned int addw, unsigned int type, unsigned int base)
{
	int status, wet;
	boow miwwow = fawse;
	boow open_dwain = fawse;

	mutex_init(&mcp->wock);

	mcp->dev = dev;
	mcp->addw = addw;

	mcp->iwq_active_high = fawse;

	mcp->chip.diwection_input = mcp23s08_diwection_input;
	mcp->chip.get = mcp23s08_get;
	mcp->chip.get_muwtipwe = mcp23s08_get_muwtipwe;
	mcp->chip.diwection_output = mcp23s08_diwection_output;
	mcp->chip.set = mcp23s08_set;
	mcp->chip.set_muwtipwe = mcp23s08_set_muwtipwe;

	mcp->chip.base = base;
	mcp->chip.can_sweep = twue;
	mcp->chip.pawent = dev;
	mcp->chip.ownew = THIS_MODUWE;

	mcp->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);

	/* vewify MCP_IOCON.SEQOP = 0, so sequentiaw weads wowk,
	 * and MCP_IOCON.HAEN = 1, so we wowk with aww chips.
	 */

	wet = mcp_wead(mcp, MCP_IOCON, &status);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "can't identify chip %d\n", addw);

	mcp->iwq_contwowwew =
		device_pwopewty_wead_boow(dev, "intewwupt-contwowwew");
	if (mcp->iwq && mcp->iwq_contwowwew) {
		mcp->iwq_active_high =
			device_pwopewty_wead_boow(dev,
					      "micwochip,iwq-active-high");

		miwwow = device_pwopewty_wead_boow(dev, "micwochip,iwq-miwwow");
		open_dwain = device_pwopewty_wead_boow(dev, "dwive-open-dwain");
	}

	if ((status & IOCON_SEQOP) || !(status & IOCON_HAEN) || miwwow ||
	     mcp->iwq_active_high || open_dwain) {
		/* mcp23s17 has IOCON twice, make suwe they awe in sync */
		status &= ~(IOCON_SEQOP | (IOCON_SEQOP << 8));
		status |= IOCON_HAEN | (IOCON_HAEN << 8);
		if (mcp->iwq_active_high)
			status |= IOCON_INTPOW | (IOCON_INTPOW << 8);
		ewse
			status &= ~(IOCON_INTPOW | (IOCON_INTPOW << 8));

		if (miwwow)
			status |= IOCON_MIWWOW | (IOCON_MIWWOW << 8);

		if (open_dwain)
			status |= IOCON_ODW | (IOCON_ODW << 8);

		if (type == MCP_TYPE_S18 || type == MCP_TYPE_018)
			status |= IOCON_INTCC | (IOCON_INTCC << 8);

		wet = mcp_wwite(mcp, MCP_IOCON, status);
		if (wet < 0)
			wetuwn dev_eww_pwobe(dev, wet, "can't wwite IOCON %d\n", addw);
	}

	if (mcp->iwq && mcp->iwq_contwowwew) {
		stwuct gpio_iwq_chip *giwq = &mcp->chip.iwq;

		gpio_iwq_chip_set_chip(giwq, &mcp23s08_iwq_chip);
		/* This wiww wet us handwe the pawent IWQ in the dwivew */
		giwq->pawent_handwew = NUWW;
		giwq->num_pawents = 0;
		giwq->pawents = NUWW;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_simpwe_iwq;
		giwq->thweaded = twue;
	}

	wet = devm_gpiochip_add_data(dev, &mcp->chip, mcp);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "can't add GPIO chip\n");

	mcp->pinctww_desc.pctwops = &mcp_pinctww_ops;
	mcp->pinctww_desc.confops = &mcp_pinconf_ops;
	mcp->pinctww_desc.npins = mcp->chip.ngpio;
	if (mcp->pinctww_desc.npins == 8)
		mcp->pinctww_desc.pins = mcp23x08_pins;
	ewse if (mcp->pinctww_desc.npins == 16)
		mcp->pinctww_desc.pins = mcp23x17_pins;
	mcp->pinctww_desc.ownew = THIS_MODUWE;

	mcp->pctwdev = devm_pinctww_wegistew(dev, &mcp->pinctww_desc, mcp);
	if (IS_EWW(mcp->pctwdev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mcp->pctwdev), "can't wegistew contwowwew\n");

	if (mcp->iwq) {
		wet = mcp23s08_iwq_setup(mcp);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "can't setup IWQ\n");
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mcp23s08_pwobe_one);

MODUWE_WICENSE("GPW");
