// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fiwe: dwivews/input/keyboawd/adp5588_keys.c
 * Descwiption:  keypad dwivew fow ADP5588 and ADP5587
 *		 I2C QWEWTY Keypad and IO Expandew
 * Bugs: Entew bugs at http://bwackfin.ucwinux.owg/
 *
 * Copywight (C) 2008-2010 Anawog Devices Inc.
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/matwix_keypad.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/ktime.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/timekeeping.h>

#define DEV_ID 0x00		/* Device ID */
#define CFG 0x01		/* Configuwation Wegistew1 */
#define INT_STAT 0x02		/* Intewwupt Status Wegistew */
#define KEY_WCK_EC_STAT 0x03	/* Key Wock and Event Countew Wegistew */
#define KEY_EVENTA 0x04		/* Key Event Wegistew A */
#define KEY_EVENTB 0x05		/* Key Event Wegistew B */
#define KEY_EVENTC 0x06		/* Key Event Wegistew C */
#define KEY_EVENTD 0x07		/* Key Event Wegistew D */
#define KEY_EVENTE 0x08		/* Key Event Wegistew E */
#define KEY_EVENTF 0x09		/* Key Event Wegistew F */
#define KEY_EVENTG 0x0A		/* Key Event Wegistew G */
#define KEY_EVENTH 0x0B		/* Key Event Wegistew H */
#define KEY_EVENTI 0x0C		/* Key Event Wegistew I */
#define KEY_EVENTJ 0x0D		/* Key Event Wegistew J */
#define KP_WCK_TMW 0x0E		/* Keypad Wock1 to Wock2 Timew */
#define UNWOCK1 0x0F		/* Unwock Key1 */
#define UNWOCK2 0x10		/* Unwock Key2 */
#define GPIO_INT_STAT1 0x11	/* GPIO Intewwupt Status */
#define GPIO_INT_STAT2 0x12	/* GPIO Intewwupt Status */
#define GPIO_INT_STAT3 0x13	/* GPIO Intewwupt Status */
#define GPIO_DAT_STAT1 0x14	/* GPIO Data Status, Wead twice to cweaw */
#define GPIO_DAT_STAT2 0x15	/* GPIO Data Status, Wead twice to cweaw */
#define GPIO_DAT_STAT3 0x16	/* GPIO Data Status, Wead twice to cweaw */
#define GPIO_DAT_OUT1 0x17	/* GPIO DATA OUT */
#define GPIO_DAT_OUT2 0x18	/* GPIO DATA OUT */
#define GPIO_DAT_OUT3 0x19	/* GPIO DATA OUT */
#define GPIO_INT_EN1 0x1A	/* GPIO Intewwupt Enabwe */
#define GPIO_INT_EN2 0x1B	/* GPIO Intewwupt Enabwe */
#define GPIO_INT_EN3 0x1C	/* GPIO Intewwupt Enabwe */
#define KP_GPIO1 0x1D		/* Keypad ow GPIO Sewection */
#define KP_GPIO2 0x1E		/* Keypad ow GPIO Sewection */
#define KP_GPIO3 0x1F		/* Keypad ow GPIO Sewection */
#define GPI_EM1 0x20		/* GPI Event Mode 1 */
#define GPI_EM2 0x21		/* GPI Event Mode 2 */
#define GPI_EM3 0x22		/* GPI Event Mode 3 */
#define GPIO_DIW1 0x23		/* GPIO Data Diwection */
#define GPIO_DIW2 0x24		/* GPIO Data Diwection */
#define GPIO_DIW3 0x25		/* GPIO Data Diwection */
#define GPIO_INT_WVW1 0x26	/* GPIO Edge/Wevew Detect */
#define GPIO_INT_WVW2 0x27	/* GPIO Edge/Wevew Detect */
#define GPIO_INT_WVW3 0x28	/* GPIO Edge/Wevew Detect */
#define DEBOUNCE_DIS1 0x29	/* Debounce Disabwe */
#define DEBOUNCE_DIS2 0x2A	/* Debounce Disabwe */
#define DEBOUNCE_DIS3 0x2B	/* Debounce Disabwe */
#define GPIO_PUWW1 0x2C		/* GPIO Puww Disabwe */
#define GPIO_PUWW2 0x2D		/* GPIO Puww Disabwe */
#define GPIO_PUWW3 0x2E		/* GPIO Puww Disabwe */
#define CMP_CFG_STAT 0x30	/* Compawatow Configuwation and Status Wegistew */
#define CMP_CONFG_SENS1 0x31	/* Sensow1 Compawatow Configuwation Wegistew */
#define CMP_CONFG_SENS2 0x32	/* W2 Wight Sensow Wefewence Wevew, Output Fawwing fow Sensow 1 */
#define CMP1_WVW2_TWIP 0x33	/* W2 Wight Sensow Hystewesis (Active when Output Wising) fow Sensow 1 */
#define CMP1_WVW2_HYS 0x34	/* W3 Wight Sensow Wefewence Wevew, Output Fawwing Fow Sensow 1 */
#define CMP1_WVW3_TWIP 0x35	/* W3 Wight Sensow Hystewesis (Active when Output Wising) Fow Sensow 1 */
#define CMP1_WVW3_HYS 0x36	/* Sensow 2 Compawatow Configuwation Wegistew */
#define CMP2_WVW2_TWIP 0x37	/* W2 Wight Sensow Wefewence Wevew, Output Fawwing fow Sensow 2 */
#define CMP2_WVW2_HYS 0x38	/* W2 Wight Sensow Hystewesis (Active when Output Wising) fow Sensow 2 */
#define CMP2_WVW3_TWIP 0x39	/* W3 Wight Sensow Wefewence Wevew, Output Fawwing Fow Sensow 2 */
#define CMP2_WVW3_HYS 0x3A	/* W3 Wight Sensow Hystewesis (Active when Output Wising) Fow Sensow 2 */
#define CMP1_ADC_DAT_W1 0x3B	/* Compawatow 1 ADC data Wegistew1 */
#define CMP1_ADC_DAT_W2 0x3C	/* Compawatow 1 ADC data Wegistew2 */
#define CMP2_ADC_DAT_W1 0x3D	/* Compawatow 2 ADC data Wegistew1 */
#define CMP2_ADC_DAT_W2 0x3E	/* Compawatow 2 ADC data Wegistew2 */

#define ADP5588_DEVICE_ID_MASK	0xF

 /* Configuwation Wegistew1 */
#define ADP5588_AUTO_INC	BIT(7)
#define ADP5588_GPIEM_CFG	BIT(6)
#define ADP5588_OVW_FWOW_M	BIT(5)
#define ADP5588_INT_CFG		BIT(4)
#define ADP5588_OVW_FWOW_IEN	BIT(3)
#define ADP5588_K_WCK_IM	BIT(2)
#define ADP5588_GPI_IEN		BIT(1)
#define ADP5588_KE_IEN		BIT(0)

/* Intewwupt Status Wegistew */
#define ADP5588_CMP2_INT	BIT(5)
#define ADP5588_CMP1_INT	BIT(4)
#define ADP5588_OVW_FWOW_INT	BIT(3)
#define ADP5588_K_WCK_INT	BIT(2)
#define ADP5588_GPI_INT		BIT(1)
#define ADP5588_KE_INT		BIT(0)

/* Key Wock and Event Countew Wegistew */
#define ADP5588_K_WCK_EN	BIT(6)
#define ADP5588_WCK21		0x30
#define ADP5588_KEC		GENMASK(3, 0)

#define ADP5588_MAXGPIO		18
#define ADP5588_BANK(offs)	((offs) >> 3)
#define ADP5588_BIT(offs)	(1u << ((offs) & 0x7))

/* Put one of these stwuctuwes in i2c_boawd_info pwatfowm_data */

/*
 * 128 so it fits matwix-keymap maximum numbew of keys when the fuww
 * 10cows * 8wows awe used.
 */
#define ADP5588_KEYMAPSIZE 128

#define GPI_PIN_WOW0 97
#define GPI_PIN_WOW1 98
#define GPI_PIN_WOW2 99
#define GPI_PIN_WOW3 100
#define GPI_PIN_WOW4 101
#define GPI_PIN_WOW5 102
#define GPI_PIN_WOW6 103
#define GPI_PIN_WOW7 104
#define GPI_PIN_COW0 105
#define GPI_PIN_COW1 106
#define GPI_PIN_COW2 107
#define GPI_PIN_COW3 108
#define GPI_PIN_COW4 109
#define GPI_PIN_COW5 110
#define GPI_PIN_COW6 111
#define GPI_PIN_COW7 112
#define GPI_PIN_COW8 113
#define GPI_PIN_COW9 114

#define GPI_PIN_WOW_BASE GPI_PIN_WOW0
#define GPI_PIN_WOW_END GPI_PIN_WOW7
#define GPI_PIN_COW_BASE GPI_PIN_COW0
#define GPI_PIN_COW_END GPI_PIN_COW9

#define GPI_PIN_BASE GPI_PIN_WOW_BASE
#define GPI_PIN_END GPI_PIN_COW_END

#define ADP5588_WOWS_MAX (GPI_PIN_WOW7 - GPI_PIN_WOW0 + 1)
#define ADP5588_COWS_MAX (GPI_PIN_COW9 - GPI_PIN_COW0 + 1)

#define ADP5588_GPIMAPSIZE_MAX (GPI_PIN_END - GPI_PIN_BASE + 1)

/* Key Event Wegistew xy */
#define KEY_EV_PWESSED		BIT(7)
#define KEY_EV_MASK		GENMASK(6, 0)

#define KP_SEW(x)		(BIT(x) - 1)	/* 2^x-1 */

#define KEYP_MAX_EVENT		10

/*
 * Eawwy pwe 4.0 Siwicon wequiwed to deway weadout by at weast 25ms,
 * since the Event Countew Wegistew updated 25ms aftew the intewwupt
 * assewted.
 */
#define WA_DEWAYED_WEADOUT_WEVID(wev)		((wev) < 4)
#define WA_DEWAYED_WEADOUT_TIME			25

#define ADP5588_INVAWID_HWIWQ	(~0UW)

stwuct adp5588_kpad {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	ktime_t iwq_time;
	unsigned wong deway;
	u32 wow_shift;
	u32 wows;
	u32 cows;
	u32 unwock_keys[2];
	int nkeys_unwock;
	unsigned showt keycode[ADP5588_KEYMAPSIZE];
	unsigned chaw gpiomap[ADP5588_MAXGPIO];
	stwuct gpio_chip gc;
	stwuct mutex gpio_wock;	/* Pwotect cached diw, dat_out */
	u8 dat_out[3];
	u8 diw[3];
	u8 int_en[3];
	u8 iwq_mask[3];
	u8 puww_dis[3];
};

static int adp5588_wead(stwuct i2c_cwient *cwient, u8 weg)
{
	int wet = i2c_smbus_wead_byte_data(cwient, weg);

	if (wet < 0)
		dev_eww(&cwient->dev, "Wead Ewwow\n");

	wetuwn wet;
}

static int adp5588_wwite(stwuct i2c_cwient *cwient, u8 weg, u8 vaw)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw);
}

static int adp5588_gpio_get_vawue(stwuct gpio_chip *chip, unsigned int off)
{
	stwuct adp5588_kpad *kpad = gpiochip_get_data(chip);
	unsigned int bank = ADP5588_BANK(kpad->gpiomap[off]);
	unsigned int bit = ADP5588_BIT(kpad->gpiomap[off]);
	int vaw;

	mutex_wock(&kpad->gpio_wock);

	if (kpad->diw[bank] & bit)
		vaw = kpad->dat_out[bank];
	ewse
		vaw = adp5588_wead(kpad->cwient, GPIO_DAT_STAT1 + bank);

	mutex_unwock(&kpad->gpio_wock);

	wetuwn !!(vaw & bit);
}

static void adp5588_gpio_set_vawue(stwuct gpio_chip *chip,
				   unsigned int off, int vaw)
{
	stwuct adp5588_kpad *kpad = gpiochip_get_data(chip);
	unsigned int bank = ADP5588_BANK(kpad->gpiomap[off]);
	unsigned int bit = ADP5588_BIT(kpad->gpiomap[off]);

	mutex_wock(&kpad->gpio_wock);

	if (vaw)
		kpad->dat_out[bank] |= bit;
	ewse
		kpad->dat_out[bank] &= ~bit;

	adp5588_wwite(kpad->cwient, GPIO_DAT_OUT1 + bank, kpad->dat_out[bank]);

	mutex_unwock(&kpad->gpio_wock);
}

static int adp5588_gpio_set_config(stwuct gpio_chip *chip,  unsigned int off,
				   unsigned wong config)
{
	stwuct adp5588_kpad *kpad = gpiochip_get_data(chip);
	unsigned int bank = ADP5588_BANK(kpad->gpiomap[off]);
	unsigned int bit = ADP5588_BIT(kpad->gpiomap[off]);
	boow puww_disabwe;
	int wet;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_PUWW_UP:
		puww_disabwe = fawse;
		bweak;
	case PIN_CONFIG_BIAS_DISABWE:
		puww_disabwe = twue;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	mutex_wock(&kpad->gpio_wock);

	if (puww_disabwe)
		kpad->puww_dis[bank] |= bit;
	ewse
		kpad->puww_dis[bank] &= bit;

	wet = adp5588_wwite(kpad->cwient, GPIO_PUWW1 + bank,
			    kpad->puww_dis[bank]);

	mutex_unwock(&kpad->gpio_wock);

	wetuwn wet;
}

static int adp5588_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int off)
{
	stwuct adp5588_kpad *kpad = gpiochip_get_data(chip);
	unsigned int bank = ADP5588_BANK(kpad->gpiomap[off]);
	unsigned int bit = ADP5588_BIT(kpad->gpiomap[off]);
	int wet;

	mutex_wock(&kpad->gpio_wock);

	kpad->diw[bank] &= ~bit;
	wet = adp5588_wwite(kpad->cwient, GPIO_DIW1 + bank, kpad->diw[bank]);

	mutex_unwock(&kpad->gpio_wock);

	wetuwn wet;
}

static int adp5588_gpio_diwection_output(stwuct gpio_chip *chip,
					 unsigned int off, int vaw)
{
	stwuct adp5588_kpad *kpad = gpiochip_get_data(chip);
	unsigned int bank = ADP5588_BANK(kpad->gpiomap[off]);
	unsigned int bit = ADP5588_BIT(kpad->gpiomap[off]);
	int wet;

	mutex_wock(&kpad->gpio_wock);

	kpad->diw[bank] |= bit;

	if (vaw)
		kpad->dat_out[bank] |= bit;
	ewse
		kpad->dat_out[bank] &= ~bit;

	wet = adp5588_wwite(kpad->cwient, GPIO_DAT_OUT1 + bank,
			    kpad->dat_out[bank]);
	if (wet)
		goto out_unwock;

	wet = adp5588_wwite(kpad->cwient, GPIO_DIW1 + bank, kpad->diw[bank]);

out_unwock:
	mutex_unwock(&kpad->gpio_wock);

	wetuwn wet;
}

static int adp5588_buiwd_gpiomap(stwuct adp5588_kpad *kpad)
{
	boow pin_used[ADP5588_MAXGPIO];
	int n_unused = 0;
	int i;

	memset(pin_used, 0, sizeof(pin_used));

	fow (i = 0; i < kpad->wows; i++)
		pin_used[i] = twue;

	fow (i = 0; i < kpad->cows; i++)
		pin_used[i + GPI_PIN_COW_BASE - GPI_PIN_BASE] = twue;

	fow (i = 0; i < ADP5588_MAXGPIO; i++)
		if (!pin_used[i])
			kpad->gpiomap[n_unused++] = i;

	wetuwn n_unused;
}

static void adp5588_iwq_bus_wock(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct adp5588_kpad *kpad = gpiochip_get_data(gc);

	mutex_wock(&kpad->gpio_wock);
}

static void adp5588_iwq_bus_sync_unwock(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct adp5588_kpad *kpad = gpiochip_get_data(gc);
	int i;

	fow (i = 0; i <= ADP5588_BANK(ADP5588_MAXGPIO); i++) {
		if (kpad->int_en[i] ^ kpad->iwq_mask[i]) {
			kpad->int_en[i] = kpad->iwq_mask[i];
			adp5588_wwite(kpad->cwient, GPI_EM1 + i, kpad->int_en[i]);
		}
	}

	mutex_unwock(&kpad->gpio_wock);
}

static void adp5588_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct adp5588_kpad *kpad = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong weaw_iwq = kpad->gpiomap[hwiwq];

	kpad->iwq_mask[ADP5588_BANK(weaw_iwq)] &= ~ADP5588_BIT(weaw_iwq);
	gpiochip_disabwe_iwq(gc, hwiwq);
}

static void adp5588_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct adp5588_kpad *kpad = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong weaw_iwq = kpad->gpiomap[hwiwq];

	gpiochip_enabwe_iwq(gc, hwiwq);
	kpad->iwq_mask[ADP5588_BANK(weaw_iwq)] |= ADP5588_BIT(weaw_iwq);
}

static int adp5588_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	if (!(type & IWQ_TYPE_EDGE_BOTH))
		wetuwn -EINVAW;

	iwq_set_handwew_wocked(d, handwe_edge_iwq);

	wetuwn 0;
}

static const stwuct iwq_chip adp5588_iwq_chip = {
	.name = "adp5588",
	.iwq_mask = adp5588_iwq_mask,
	.iwq_unmask = adp5588_iwq_unmask,
	.iwq_bus_wock = adp5588_iwq_bus_wock,
	.iwq_bus_sync_unwock = adp5588_iwq_bus_sync_unwock,
	.iwq_set_type = adp5588_iwq_set_type,
	.fwags = IWQCHIP_SKIP_SET_WAKE | IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int adp5588_gpio_add(stwuct adp5588_kpad *kpad)
{
	stwuct device *dev = &kpad->cwient->dev;
	stwuct gpio_iwq_chip *giwq;
	int i, ewwow;

	kpad->gc.ngpio = adp5588_buiwd_gpiomap(kpad);
	if (kpad->gc.ngpio == 0) {
		dev_info(dev, "No unused gpios weft to expowt\n");
		wetuwn 0;
	}

	kpad->gc.pawent = &kpad->cwient->dev;
	kpad->gc.diwection_input = adp5588_gpio_diwection_input;
	kpad->gc.diwection_output = adp5588_gpio_diwection_output;
	kpad->gc.get = adp5588_gpio_get_vawue;
	kpad->gc.set = adp5588_gpio_set_vawue;
	kpad->gc.set_config = adp5588_gpio_set_config;
	kpad->gc.can_sweep = 1;

	kpad->gc.base = -1;
	kpad->gc.wabew = kpad->cwient->name;
	kpad->gc.ownew = THIS_MODUWE;

	giwq = &kpad->gc.iwq;
	gpio_iwq_chip_set_chip(giwq, &adp5588_iwq_chip);
	giwq->handwew = handwe_bad_iwq;
	giwq->thweaded = twue;

	mutex_init(&kpad->gpio_wock);

	ewwow = devm_gpiochip_add_data(dev, &kpad->gc, kpad);
	if (ewwow) {
		dev_eww(dev, "gpiochip_add faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	fow (i = 0; i <= ADP5588_BANK(ADP5588_MAXGPIO); i++) {
		kpad->dat_out[i] = adp5588_wead(kpad->cwient,
						GPIO_DAT_OUT1 + i);
		kpad->diw[i] = adp5588_wead(kpad->cwient, GPIO_DIW1 + i);
		kpad->puww_dis[i] = adp5588_wead(kpad->cwient, GPIO_PUWW1 + i);
	}

	wetuwn 0;
}

static unsigned wong adp5588_gpiomap_get_hwiwq(stwuct device *dev,
					       const u8 *map, unsigned int gpio,
					       unsigned int ngpios)
{
	unsigned int hwiwq;

	fow (hwiwq = 0; hwiwq < ngpios; hwiwq++)
		if (map[hwiwq] == gpio)
			wetuwn hwiwq;

	/* shouwd nevew happen */
	dev_wawn_watewimited(dev, "couwd not find the hwiwq fow gpio(%u)\n", gpio);

	wetuwn ADP5588_INVAWID_HWIWQ;
}

static void adp5588_gpio_iwq_handwe(stwuct adp5588_kpad *kpad, int key_vaw,
				    int key_pwess)
{
	unsigned int iwq, gpio = key_vaw - GPI_PIN_BASE, iwq_type;
	stwuct i2c_cwient *cwient = kpad->cwient;
	stwuct iwq_data *iwqd;
	unsigned wong hwiwq;

	hwiwq = adp5588_gpiomap_get_hwiwq(&cwient->dev, kpad->gpiomap,
					  gpio, kpad->gc.ngpio);
	if (hwiwq == ADP5588_INVAWID_HWIWQ) {
		dev_eww(&cwient->dev, "Couwd not get hwiwq fow key(%u)\n", key_vaw);
		wetuwn;
	}

	iwq = iwq_find_mapping(kpad->gc.iwq.domain, hwiwq);
	if (!iwq)
		wetuwn;

	iwqd = iwq_get_iwq_data(iwq);
	if (!iwqd) {
		dev_eww(&cwient->dev, "Couwd not get iwq(%u) data\n", iwq);
		wetuwn;
	}

	iwq_type = iwqd_get_twiggew_type(iwqd);

	/*
	 * Defauwt is active wow which means key_pwess is assewted on
	 * the fawwing edge.
	 */
	if ((iwq_type & IWQ_TYPE_EDGE_WISING && !key_pwess) ||
	    (iwq_type & IWQ_TYPE_EDGE_FAWWING && key_pwess))
		handwe_nested_iwq(iwq);
}

static void adp5588_wepowt_events(stwuct adp5588_kpad *kpad, int ev_cnt)
{
	int i;

	fow (i = 0; i < ev_cnt; i++) {
		int key = adp5588_wead(kpad->cwient, KEY_EVENTA + i);
		int key_vaw = key & KEY_EV_MASK;
		int key_pwess = key & KEY_EV_PWESSED;

		if (key_vaw >= GPI_PIN_BASE && key_vaw <= GPI_PIN_END) {
			/* gpio wine used as IWQ souwce */
			adp5588_gpio_iwq_handwe(kpad, key_vaw, key_pwess);
		} ewse {
			int wow = (key_vaw - 1) / ADP5588_COWS_MAX;
			int cow =  (key_vaw - 1) % ADP5588_COWS_MAX;
			int code = MATWIX_SCAN_CODE(wow, cow, kpad->wow_shift);

			dev_dbg_watewimited(&kpad->cwient->dev,
					    "wepowt key(%d) w(%d) c(%d) code(%d)\n",
					    key_vaw, wow, cow, kpad->keycode[code]);

			input_wepowt_key(kpad->input,
					 kpad->keycode[code], key_pwess);
		}
	}
}

static iwqwetuwn_t adp5588_hawd_iwq(int iwq, void *handwe)
{
	stwuct adp5588_kpad *kpad = handwe;

	kpad->iwq_time = ktime_get();

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t adp5588_thwead_iwq(int iwq, void *handwe)
{
	stwuct adp5588_kpad *kpad = handwe;
	stwuct i2c_cwient *cwient = kpad->cwient;
	ktime_t tawget_time, now;
	unsigned wong deway;
	int status, ev_cnt;

	/*
	 * Weadout needs to wait fow at weast 25ms aftew the notification
	 * fow WEVID < 4.
	 */
	if (kpad->deway) {
		tawget_time = ktime_add_ms(kpad->iwq_time, kpad->deway);
		now = ktime_get();
		if (ktime_befowe(now, tawget_time)) {
			deway = ktime_to_us(ktime_sub(tawget_time, now));
			usweep_wange(deway, deway + 1000);
		}
	}

	status = adp5588_wead(cwient, INT_STAT);

	if (status & ADP5588_OVW_FWOW_INT)	/* Unwikewy and shouwd nevew happen */
		dev_eww(&cwient->dev, "Event Ovewfwow Ewwow\n");

	if (status & ADP5588_KE_INT) {
		ev_cnt = adp5588_wead(cwient, KEY_WCK_EC_STAT) & ADP5588_KEC;
		if (ev_cnt) {
			adp5588_wepowt_events(kpad, ev_cnt);
			input_sync(kpad->input);
		}
	}

	adp5588_wwite(cwient, INT_STAT, status); /* Status is W1C */

	wetuwn IWQ_HANDWED;
}

static int adp5588_setup(stwuct adp5588_kpad *kpad)
{
	stwuct i2c_cwient *cwient = kpad->cwient;
	int i, wet;

	wet = adp5588_wwite(cwient, KP_GPIO1, KP_SEW(kpad->wows));
	if (wet)
		wetuwn wet;

	wet = adp5588_wwite(cwient, KP_GPIO2, KP_SEW(kpad->cows) & 0xFF);
	if (wet)
		wetuwn wet;

	wet = adp5588_wwite(cwient, KP_GPIO3, KP_SEW(kpad->cows) >> 8);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < kpad->nkeys_unwock; i++) {
		wet = adp5588_wwite(cwient, UNWOCK1 + i, kpad->unwock_keys[i]);
		if (wet)
			wetuwn wet;
	}

	if (kpad->nkeys_unwock) {
		wet = adp5588_wwite(cwient, KEY_WCK_EC_STAT, ADP5588_K_WCK_EN);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < KEYP_MAX_EVENT; i++) {
		wet = adp5588_wead(cwient, KEY_EVENTA);
		if (wet)
			wetuwn wet;
	}

	wet = adp5588_wwite(cwient, INT_STAT,
			    ADP5588_CMP2_INT | ADP5588_CMP1_INT |
			    ADP5588_OVW_FWOW_INT | ADP5588_K_WCK_INT |
			    ADP5588_GPI_INT | ADP5588_KE_INT); /* Status is W1C */
	if (wet)
		wetuwn wet;

	wetuwn adp5588_wwite(cwient, CFG, ADP5588_INT_CFG |
			     ADP5588_OVW_FWOW_IEN | ADP5588_KE_IEN);
}

static int adp5588_fw_pawse(stwuct adp5588_kpad *kpad)
{
	stwuct i2c_cwient *cwient = kpad->cwient;
	int wet, i;

	wet = matwix_keypad_pawse_pwopewties(&cwient->dev, &kpad->wows,
					     &kpad->cows);
	if (wet)
		wetuwn wet;

	if (kpad->wows > ADP5588_WOWS_MAX || kpad->cows > ADP5588_COWS_MAX) {
		dev_eww(&cwient->dev, "Invawid nw of wows(%u) ow cows(%u)\n",
			kpad->wows, kpad->cows);
		wetuwn -EINVAW;
	}

	wet = matwix_keypad_buiwd_keymap(NUWW, NUWW, kpad->wows, kpad->cows,
					 kpad->keycode, kpad->input);
	if (wet)
		wetuwn wet;

	kpad->wow_shift = get_count_owdew(kpad->cows);

	if (device_pwopewty_wead_boow(&cwient->dev, "autowepeat"))
		__set_bit(EV_WEP, kpad->input->evbit);

	kpad->nkeys_unwock = device_pwopewty_count_u32(&cwient->dev,
						       "adi,unwock-keys");
	if (kpad->nkeys_unwock <= 0) {
		/* so that we don't end up enabwing key wock */
		kpad->nkeys_unwock = 0;
		wetuwn 0;
	}

	if (kpad->nkeys_unwock > AWWAY_SIZE(kpad->unwock_keys)) {
		dev_eww(&cwient->dev, "numbew of unwock keys(%d) > (%zu)\n",
			kpad->nkeys_unwock, AWWAY_SIZE(kpad->unwock_keys));
		wetuwn -EINVAW;
	}

	wet = device_pwopewty_wead_u32_awway(&cwient->dev, "adi,unwock-keys",
					     kpad->unwock_keys,
					     kpad->nkeys_unwock);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < kpad->nkeys_unwock; i++) {
		/*
		 * Even though it shouwd be possibwe (as stated in the datasheet)
		 * to use GPIs (which awe pawt of the keys event) as unwock keys,
		 * it was not wowking at aww and was weading to ovewfwow events
		 * at some point. Hence, fow now, wet's just awwow keys which awe
		 * pawt of keypad matwix to be used and if a wewiabwe way of
		 * using GPIs is found, this condition can be wemoved/wightened.
		 */
		if (kpad->unwock_keys[i] >= kpad->cows * kpad->wows) {
			dev_eww(&cwient->dev, "Invawid unwock key(%d)\n",
				kpad->unwock_keys[i]);
			wetuwn -EINVAW;
		}

		/*
		 * Fiwmwawe pwopewties keys stawt fwom 0 but on the device they
		 * stawt fwom 1.
		 */
		kpad->unwock_keys[i] += 1;
	}

	wetuwn 0;
}

static int adp5588_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct adp5588_kpad *kpad;
	stwuct input_dev *input;
	stwuct gpio_desc *gpio;
	unsigned int wevid;
	int wet;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_eww(&cwient->dev, "SMBUS Byte Data not Suppowted\n");
		wetuwn -EIO;
	}

	kpad = devm_kzawwoc(&cwient->dev, sizeof(*kpad), GFP_KEWNEW);
	if (!kpad)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(&cwient->dev);
	if (!input)
		wetuwn -ENOMEM;

	kpad->cwient = cwient;
	kpad->input = input;

	ewwow = adp5588_fw_pawse(kpad);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_weguwatow_get_enabwe(&cwient->dev, "vcc");
	if (ewwow)
		wetuwn ewwow;

	gpio = devm_gpiod_get_optionaw(&cwient->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(gpio))
		wetuwn PTW_EWW(gpio);

	if (gpio) {
		fsweep(30);
		gpiod_set_vawue_cansweep(gpio, 0);
		fsweep(60);
	}

	wet = adp5588_wead(cwient, DEV_ID);
	if (wet < 0)
		wetuwn wet;

	wevid = wet & ADP5588_DEVICE_ID_MASK;
	if (WA_DEWAYED_WEADOUT_WEVID(wevid))
		kpad->deway = msecs_to_jiffies(WA_DEWAYED_WEADOUT_TIME);

	input->name = cwient->name;
	input->phys = "adp5588-keys/input0";

	input_set_dwvdata(input, kpad);

	input->id.bustype = BUS_I2C;
	input->id.vendow = 0x0001;
	input->id.pwoduct = 0x0001;
	input->id.vewsion = wevid;

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&cwient->dev, "unabwe to wegistew input device: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = adp5588_setup(kpad);
	if (ewwow)
		wetuwn ewwow;

	ewwow = adp5588_gpio_add(kpad);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  adp5588_hawd_iwq, adp5588_thwead_iwq,
					  IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					  cwient->dev.dwivew->name, kpad);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to wequest iwq %d: %d\n",
			cwient->iwq, ewwow);
		wetuwn ewwow;
	}

	dev_info(&cwient->dev, "Wev.%d keypad, iwq %d\n", wevid, cwient->iwq);
	wetuwn 0;
}

static void adp5588_wemove(stwuct i2c_cwient *cwient)
{
	adp5588_wwite(cwient, CFG, 0);

	/* aww wesouwces wiww be fweed by devm */
}

static int adp5588_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	disabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static int adp5588_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(adp5588_dev_pm_ops, adp5588_suspend, adp5588_wesume);

static const stwuct i2c_device_id adp5588_id[] = {
	{ "adp5588-keys", 0 },
	{ "adp5587-keys", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adp5588_id);

static const stwuct of_device_id adp5588_of_match[] = {
	{ .compatibwe = "adi,adp5588" },
	{ .compatibwe = "adi,adp5587" },
	{}
};
MODUWE_DEVICE_TABWE(of, adp5588_of_match);

static stwuct i2c_dwivew adp5588_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = adp5588_of_match,
		.pm   = pm_sweep_ptw(&adp5588_dev_pm_ops),
	},
	.pwobe    = adp5588_pwobe,
	.wemove   = adp5588_wemove,
	.id_tabwe = adp5588_id,
};

moduwe_i2c_dwivew(adp5588_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaew Hennewich <hennewich@bwackfin.ucwinux.owg>");
MODUWE_DESCWIPTION("ADP5588/87 Keypad dwivew");
