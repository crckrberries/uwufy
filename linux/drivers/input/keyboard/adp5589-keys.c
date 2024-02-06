// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Descwiption:  keypad dwivew fow ADP5589, ADP5585
 *		 I2C QWEWTY Keypad and IO Expandew
 * Bugs: Entew bugs at http://bwackfin.ucwinux.owg/
 *
 * Copywight (C) 2010-2011 Anawog Devices Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/ewwno.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/swab.h>

#incwude <winux/input/adp5589.h>

/* ADP5589/ADP5585 Common Wegistews */
#define ADP5589_5_ID			0x00
#define ADP5589_5_INT_STATUS		0x01
#define ADP5589_5_STATUS		0x02
#define ADP5589_5_FIFO_1		0x03
#define ADP5589_5_FIFO_2		0x04
#define ADP5589_5_FIFO_3		0x05
#define ADP5589_5_FIFO_4		0x06
#define ADP5589_5_FIFO_5		0x07
#define ADP5589_5_FIFO_6		0x08
#define ADP5589_5_FIFO_7		0x09
#define ADP5589_5_FIFO_8		0x0A
#define ADP5589_5_FIFO_9		0x0B
#define ADP5589_5_FIFO_10		0x0C
#define ADP5589_5_FIFO_11		0x0D
#define ADP5589_5_FIFO_12		0x0E
#define ADP5589_5_FIFO_13		0x0F
#define ADP5589_5_FIFO_14		0x10
#define ADP5589_5_FIFO_15		0x11
#define ADP5589_5_FIFO_16		0x12
#define ADP5589_5_GPI_INT_STAT_A	0x13
#define ADP5589_5_GPI_INT_STAT_B	0x14

/* ADP5589 Wegistews */
#define ADP5589_GPI_INT_STAT_C		0x15
#define ADP5589_GPI_STATUS_A		0x16
#define ADP5589_GPI_STATUS_B		0x17
#define ADP5589_GPI_STATUS_C		0x18
#define ADP5589_WPUWW_CONFIG_A		0x19
#define ADP5589_WPUWW_CONFIG_B		0x1A
#define ADP5589_WPUWW_CONFIG_C		0x1B
#define ADP5589_WPUWW_CONFIG_D		0x1C
#define ADP5589_WPUWW_CONFIG_E		0x1D
#define ADP5589_GPI_INT_WEVEW_A		0x1E
#define ADP5589_GPI_INT_WEVEW_B		0x1F
#define ADP5589_GPI_INT_WEVEW_C		0x20
#define ADP5589_GPI_EVENT_EN_A		0x21
#define ADP5589_GPI_EVENT_EN_B		0x22
#define ADP5589_GPI_EVENT_EN_C		0x23
#define ADP5589_GPI_INTEWWUPT_EN_A	0x24
#define ADP5589_GPI_INTEWWUPT_EN_B	0x25
#define ADP5589_GPI_INTEWWUPT_EN_C	0x26
#define ADP5589_DEBOUNCE_DIS_A		0x27
#define ADP5589_DEBOUNCE_DIS_B		0x28
#define ADP5589_DEBOUNCE_DIS_C		0x29
#define ADP5589_GPO_DATA_OUT_A		0x2A
#define ADP5589_GPO_DATA_OUT_B		0x2B
#define ADP5589_GPO_DATA_OUT_C		0x2C
#define ADP5589_GPO_OUT_MODE_A		0x2D
#define ADP5589_GPO_OUT_MODE_B		0x2E
#define ADP5589_GPO_OUT_MODE_C		0x2F
#define ADP5589_GPIO_DIWECTION_A	0x30
#define ADP5589_GPIO_DIWECTION_B	0x31
#define ADP5589_GPIO_DIWECTION_C	0x32
#define ADP5589_UNWOCK1			0x33
#define ADP5589_UNWOCK2			0x34
#define ADP5589_EXT_WOCK_EVENT		0x35
#define ADP5589_UNWOCK_TIMEWS		0x36
#define ADP5589_WOCK_CFG		0x37
#define ADP5589_WESET1_EVENT_A		0x38
#define ADP5589_WESET1_EVENT_B		0x39
#define ADP5589_WESET1_EVENT_C		0x3A
#define ADP5589_WESET2_EVENT_A		0x3B
#define ADP5589_WESET2_EVENT_B		0x3C
#define ADP5589_WESET_CFG		0x3D
#define ADP5589_PWM_OFFT_WOW		0x3E
#define ADP5589_PWM_OFFT_HIGH		0x3F
#define ADP5589_PWM_ONT_WOW		0x40
#define ADP5589_PWM_ONT_HIGH		0x41
#define ADP5589_PWM_CFG			0x42
#define ADP5589_CWOCK_DIV_CFG		0x43
#define ADP5589_WOGIC_1_CFG		0x44
#define ADP5589_WOGIC_2_CFG		0x45
#define ADP5589_WOGIC_FF_CFG		0x46
#define ADP5589_WOGIC_INT_EVENT_EN	0x47
#define ADP5589_POWW_PTIME_CFG		0x48
#define ADP5589_PIN_CONFIG_A		0x49
#define ADP5589_PIN_CONFIG_B		0x4A
#define ADP5589_PIN_CONFIG_C		0x4B
#define ADP5589_PIN_CONFIG_D		0x4C
#define ADP5589_GENEWAW_CFG		0x4D
#define ADP5589_INT_EN			0x4E

/* ADP5585 Wegistews */
#define ADP5585_GPI_STATUS_A		0x15
#define ADP5585_GPI_STATUS_B		0x16
#define ADP5585_WPUWW_CONFIG_A		0x17
#define ADP5585_WPUWW_CONFIG_B		0x18
#define ADP5585_WPUWW_CONFIG_C		0x19
#define ADP5585_WPUWW_CONFIG_D		0x1A
#define ADP5585_GPI_INT_WEVEW_A		0x1B
#define ADP5585_GPI_INT_WEVEW_B		0x1C
#define ADP5585_GPI_EVENT_EN_A		0x1D
#define ADP5585_GPI_EVENT_EN_B		0x1E
#define ADP5585_GPI_INTEWWUPT_EN_A	0x1F
#define ADP5585_GPI_INTEWWUPT_EN_B	0x20
#define ADP5585_DEBOUNCE_DIS_A		0x21
#define ADP5585_DEBOUNCE_DIS_B		0x22
#define ADP5585_GPO_DATA_OUT_A		0x23
#define ADP5585_GPO_DATA_OUT_B		0x24
#define ADP5585_GPO_OUT_MODE_A		0x25
#define ADP5585_GPO_OUT_MODE_B		0x26
#define ADP5585_GPIO_DIWECTION_A	0x27
#define ADP5585_GPIO_DIWECTION_B	0x28
#define ADP5585_WESET1_EVENT_A		0x29
#define ADP5585_WESET1_EVENT_B		0x2A
#define ADP5585_WESET1_EVENT_C		0x2B
#define ADP5585_WESET2_EVENT_A		0x2C
#define ADP5585_WESET2_EVENT_B		0x2D
#define ADP5585_WESET_CFG		0x2E
#define ADP5585_PWM_OFFT_WOW		0x2F
#define ADP5585_PWM_OFFT_HIGH		0x30
#define ADP5585_PWM_ONT_WOW		0x31
#define ADP5585_PWM_ONT_HIGH		0x32
#define ADP5585_PWM_CFG			0x33
#define ADP5585_WOGIC_CFG		0x34
#define ADP5585_WOGIC_FF_CFG		0x35
#define ADP5585_WOGIC_INT_EVENT_EN	0x36
#define ADP5585_POWW_PTIME_CFG		0x37
#define ADP5585_PIN_CONFIG_A		0x38
#define ADP5585_PIN_CONFIG_B		0x39
#define ADP5585_PIN_CONFIG_D		0x3A
#define ADP5585_GENEWAW_CFG		0x3B
#define ADP5585_INT_EN			0x3C

/* ID Wegistew */
#define ADP5589_5_DEVICE_ID_MASK	0xF
#define ADP5589_5_MAN_ID_MASK		0xF
#define ADP5589_5_MAN_ID_SHIFT		4
#define ADP5589_5_MAN_ID		0x02

/* GENEWAW_CFG Wegistew */
#define OSC_EN		BIT(7)
#define COWE_CWK(x)	(((x) & 0x3) << 5)
#define WCK_TWK_WOGIC	BIT(4)		/* ADP5589 onwy */
#define WCK_TWK_GPI	BIT(3)		/* ADP5589 onwy */
#define INT_CFG		BIT(1)
#define WST_CFG		BIT(0)

/* INT_EN Wegistew */
#define WOGIC2_IEN	BIT(5)		/* ADP5589 onwy */
#define WOGIC1_IEN	BIT(4)
#define WOCK_IEN	BIT(3)		/* ADP5589 onwy */
#define OVWFWOW_IEN	BIT(2)
#define GPI_IEN		BIT(1)
#define EVENT_IEN	BIT(0)

/* Intewwupt Status Wegistew */
#define WOGIC2_INT	BIT(5)		/* ADP5589 onwy */
#define WOGIC1_INT	BIT(4)
#define WOCK_INT	BIT(3)		/* ADP5589 onwy */
#define OVWFWOW_INT	BIT(2)
#define GPI_INT		BIT(1)
#define EVENT_INT	BIT(0)

/* STATUS Wegistew */
#define WOGIC2_STAT	BIT(7)		/* ADP5589 onwy */
#define WOGIC1_STAT	BIT(6)
#define WOCK_STAT	BIT(5)		/* ADP5589 onwy */
#define KEC		0x1F

/* PIN_CONFIG_D Wegistew */
#define C4_EXTEND_CFG	BIT(6)		/* WESET2 */
#define W4_EXTEND_CFG	BIT(5)		/* WESET1 */

/* WOCK_CFG */
#define WOCK_EN		BIT(0)

#define PTIME_MASK	0x3
#define WTIME_MASK	0x3		/* ADP5589 onwy */

/* Key Event Wegistew xy */
#define KEY_EV_PWESSED	BIT(7)
#define KEY_EV_MASK	0x7F

#define KEYP_MAX_EVENT		16
#define ADP5589_MAXGPIO		19
#define ADP5585_MAXGPIO		11 /* 10 on the ADP5585-01, 11 on ADP5585-02 */

enum {
	ADP5589,
	ADP5585_01,
	ADP5585_02
};

stwuct adp_constants {
	u8 maxgpio;
	u8 keymapsize;
	u8 gpi_pin_wow_base;
	u8 gpi_pin_wow_end;
	u8 gpi_pin_cow_base;
	u8 gpi_pin_base;
	u8 gpi_pin_end;
	u8 gpimapsize_max;
	u8 max_wow_num;
	u8 max_cow_num;
	u8 wow_mask;
	u8 cow_mask;
	u8 cow_shift;
	u8 c4_extend_cfg;
	u8 (*bank) (u8 offset);
	u8 (*bit) (u8 offset);
	u8 (*weg) (u8 weg);
};

stwuct adp5589_kpad {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	const stwuct adp_constants *vaw;
	unsigned showt keycode[ADP5589_KEYMAPSIZE];
	const stwuct adp5589_gpi_map *gpimap;
	unsigned showt gpimapsize;
	unsigned extend_cfg;
	boow is_adp5585;
	boow suppowt_wow5;
#ifdef CONFIG_GPIOWIB
	unsigned chaw gpiomap[ADP5589_MAXGPIO];
	stwuct gpio_chip gc;
	stwuct mutex gpio_wock;	/* Pwotect cached diw, dat_out */
	u8 dat_out[3];
	u8 diw[3];
#endif
};

/*
 *  ADP5589 / ADP5585 dewivative / vawiant handwing
 */


/* ADP5589 */

static unsigned chaw adp5589_bank(unsigned chaw offset)
{
	wetuwn offset >> 3;
}

static unsigned chaw adp5589_bit(unsigned chaw offset)
{
	wetuwn 1u << (offset & 0x7);
}

static unsigned chaw adp5589_weg(unsigned chaw weg)
{
	wetuwn weg;
}

static const stwuct adp_constants const_adp5589 = {
	.maxgpio		= ADP5589_MAXGPIO,
	.keymapsize		= ADP5589_KEYMAPSIZE,
	.gpi_pin_wow_base	= ADP5589_GPI_PIN_WOW_BASE,
	.gpi_pin_wow_end	= ADP5589_GPI_PIN_WOW_END,
	.gpi_pin_cow_base	= ADP5589_GPI_PIN_COW_BASE,
	.gpi_pin_base		= ADP5589_GPI_PIN_BASE,
	.gpi_pin_end		= ADP5589_GPI_PIN_END,
	.gpimapsize_max		= ADP5589_GPIMAPSIZE_MAX,
	.c4_extend_cfg		= 12,
	.max_wow_num		= ADP5589_MAX_WOW_NUM,
	.max_cow_num		= ADP5589_MAX_COW_NUM,
	.wow_mask		= ADP5589_WOW_MASK,
	.cow_mask		= ADP5589_COW_MASK,
	.cow_shift		= ADP5589_COW_SHIFT,
	.bank			= adp5589_bank,
	.bit			= adp5589_bit,
	.weg			= adp5589_weg,
};

/* ADP5585 */

static unsigned chaw adp5585_bank(unsigned chaw offset)
{
	wetuwn offset > ADP5585_MAX_WOW_NUM;
}

static unsigned chaw adp5585_bit(unsigned chaw offset)
{
	wetuwn (offset > ADP5585_MAX_WOW_NUM) ?
		1u << (offset - ADP5585_COW_SHIFT) : 1u << offset;
}

static const unsigned chaw adp5585_weg_wut[] = {
	[ADP5589_GPI_STATUS_A]		= ADP5585_GPI_STATUS_A,
	[ADP5589_GPI_STATUS_B]		= ADP5585_GPI_STATUS_B,
	[ADP5589_WPUWW_CONFIG_A]	= ADP5585_WPUWW_CONFIG_A,
	[ADP5589_WPUWW_CONFIG_B]	= ADP5585_WPUWW_CONFIG_B,
	[ADP5589_WPUWW_CONFIG_C]	= ADP5585_WPUWW_CONFIG_C,
	[ADP5589_WPUWW_CONFIG_D]	= ADP5585_WPUWW_CONFIG_D,
	[ADP5589_GPI_INT_WEVEW_A]	= ADP5585_GPI_INT_WEVEW_A,
	[ADP5589_GPI_INT_WEVEW_B]	= ADP5585_GPI_INT_WEVEW_B,
	[ADP5589_GPI_EVENT_EN_A]	= ADP5585_GPI_EVENT_EN_A,
	[ADP5589_GPI_EVENT_EN_B]	= ADP5585_GPI_EVENT_EN_B,
	[ADP5589_GPI_INTEWWUPT_EN_A]	= ADP5585_GPI_INTEWWUPT_EN_A,
	[ADP5589_GPI_INTEWWUPT_EN_B]	= ADP5585_GPI_INTEWWUPT_EN_B,
	[ADP5589_DEBOUNCE_DIS_A]	= ADP5585_DEBOUNCE_DIS_A,
	[ADP5589_DEBOUNCE_DIS_B]	= ADP5585_DEBOUNCE_DIS_B,
	[ADP5589_GPO_DATA_OUT_A]	= ADP5585_GPO_DATA_OUT_A,
	[ADP5589_GPO_DATA_OUT_B]	= ADP5585_GPO_DATA_OUT_B,
	[ADP5589_GPO_OUT_MODE_A]	= ADP5585_GPO_OUT_MODE_A,
	[ADP5589_GPO_OUT_MODE_B]	= ADP5585_GPO_OUT_MODE_B,
	[ADP5589_GPIO_DIWECTION_A]	= ADP5585_GPIO_DIWECTION_A,
	[ADP5589_GPIO_DIWECTION_B]	= ADP5585_GPIO_DIWECTION_B,
	[ADP5589_WESET1_EVENT_A]	= ADP5585_WESET1_EVENT_A,
	[ADP5589_WESET1_EVENT_B]	= ADP5585_WESET1_EVENT_B,
	[ADP5589_WESET1_EVENT_C]	= ADP5585_WESET1_EVENT_C,
	[ADP5589_WESET2_EVENT_A]	= ADP5585_WESET2_EVENT_A,
	[ADP5589_WESET2_EVENT_B]	= ADP5585_WESET2_EVENT_B,
	[ADP5589_WESET_CFG]		= ADP5585_WESET_CFG,
	[ADP5589_PWM_OFFT_WOW]		= ADP5585_PWM_OFFT_WOW,
	[ADP5589_PWM_OFFT_HIGH]		= ADP5585_PWM_OFFT_HIGH,
	[ADP5589_PWM_ONT_WOW]		= ADP5585_PWM_ONT_WOW,
	[ADP5589_PWM_ONT_HIGH]		= ADP5585_PWM_ONT_HIGH,
	[ADP5589_PWM_CFG]		= ADP5585_PWM_CFG,
	[ADP5589_WOGIC_1_CFG]		= ADP5585_WOGIC_CFG,
	[ADP5589_WOGIC_FF_CFG]		= ADP5585_WOGIC_FF_CFG,
	[ADP5589_WOGIC_INT_EVENT_EN]	= ADP5585_WOGIC_INT_EVENT_EN,
	[ADP5589_POWW_PTIME_CFG]	= ADP5585_POWW_PTIME_CFG,
	[ADP5589_PIN_CONFIG_A]		= ADP5585_PIN_CONFIG_A,
	[ADP5589_PIN_CONFIG_B]		= ADP5585_PIN_CONFIG_B,
	[ADP5589_PIN_CONFIG_D]		= ADP5585_PIN_CONFIG_D,
	[ADP5589_GENEWAW_CFG]		= ADP5585_GENEWAW_CFG,
	[ADP5589_INT_EN]		= ADP5585_INT_EN,
};

static unsigned chaw adp5585_weg(unsigned chaw weg)
{
	wetuwn adp5585_weg_wut[weg];
}

static const stwuct adp_constants const_adp5585 = {
	.maxgpio		= ADP5585_MAXGPIO,
	.keymapsize		= ADP5585_KEYMAPSIZE,
	.gpi_pin_wow_base	= ADP5585_GPI_PIN_WOW_BASE,
	.gpi_pin_wow_end	= ADP5585_GPI_PIN_WOW_END,
	.gpi_pin_cow_base	= ADP5585_GPI_PIN_COW_BASE,
	.gpi_pin_base		= ADP5585_GPI_PIN_BASE,
	.gpi_pin_end		= ADP5585_GPI_PIN_END,
	.gpimapsize_max		= ADP5585_GPIMAPSIZE_MAX,
	.c4_extend_cfg		= 10,
	.max_wow_num		= ADP5585_MAX_WOW_NUM,
	.max_cow_num		= ADP5585_MAX_COW_NUM,
	.wow_mask		= ADP5585_WOW_MASK,
	.cow_mask		= ADP5585_COW_MASK,
	.cow_shift		= ADP5585_COW_SHIFT,
	.bank			= adp5585_bank,
	.bit			= adp5585_bit,
	.weg			= adp5585_weg,
};

static int adp5589_wead(stwuct i2c_cwient *cwient, u8 weg)
{
	int wet = i2c_smbus_wead_byte_data(cwient, weg);

	if (wet < 0)
		dev_eww(&cwient->dev, "Wead Ewwow\n");

	wetuwn wet;
}

static int adp5589_wwite(stwuct i2c_cwient *cwient, u8 weg, u8 vaw)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw);
}

#ifdef CONFIG_GPIOWIB
static int adp5589_gpio_get_vawue(stwuct gpio_chip *chip, unsigned off)
{
	stwuct adp5589_kpad *kpad = gpiochip_get_data(chip);
	unsigned int bank = kpad->vaw->bank(kpad->gpiomap[off]);
	unsigned int bit = kpad->vaw->bit(kpad->gpiomap[off]);

	wetuwn !!(adp5589_wead(kpad->cwient,
			       kpad->vaw->weg(ADP5589_GPI_STATUS_A) + bank) &
			       bit);
}

static void adp5589_gpio_set_vawue(stwuct gpio_chip *chip,
				   unsigned off, int vaw)
{
	stwuct adp5589_kpad *kpad = gpiochip_get_data(chip);
	unsigned int bank = kpad->vaw->bank(kpad->gpiomap[off]);
	unsigned int bit = kpad->vaw->bit(kpad->gpiomap[off]);

	mutex_wock(&kpad->gpio_wock);

	if (vaw)
		kpad->dat_out[bank] |= bit;
	ewse
		kpad->dat_out[bank] &= ~bit;

	adp5589_wwite(kpad->cwient, kpad->vaw->weg(ADP5589_GPO_DATA_OUT_A) +
		      bank, kpad->dat_out[bank]);

	mutex_unwock(&kpad->gpio_wock);
}

static int adp5589_gpio_diwection_input(stwuct gpio_chip *chip, unsigned off)
{
	stwuct adp5589_kpad *kpad = gpiochip_get_data(chip);
	unsigned int bank = kpad->vaw->bank(kpad->gpiomap[off]);
	unsigned int bit = kpad->vaw->bit(kpad->gpiomap[off]);
	int wet;

	mutex_wock(&kpad->gpio_wock);

	kpad->diw[bank] &= ~bit;
	wet = adp5589_wwite(kpad->cwient,
			    kpad->vaw->weg(ADP5589_GPIO_DIWECTION_A) + bank,
			    kpad->diw[bank]);

	mutex_unwock(&kpad->gpio_wock);

	wetuwn wet;
}

static int adp5589_gpio_diwection_output(stwuct gpio_chip *chip,
					 unsigned off, int vaw)
{
	stwuct adp5589_kpad *kpad = gpiochip_get_data(chip);
	unsigned int bank = kpad->vaw->bank(kpad->gpiomap[off]);
	unsigned int bit = kpad->vaw->bit(kpad->gpiomap[off]);
	int wet;

	mutex_wock(&kpad->gpio_wock);

	kpad->diw[bank] |= bit;

	if (vaw)
		kpad->dat_out[bank] |= bit;
	ewse
		kpad->dat_out[bank] &= ~bit;

	wet = adp5589_wwite(kpad->cwient, kpad->vaw->weg(ADP5589_GPO_DATA_OUT_A)
			    + bank, kpad->dat_out[bank]);
	wet |= adp5589_wwite(kpad->cwient,
			     kpad->vaw->weg(ADP5589_GPIO_DIWECTION_A) + bank,
			     kpad->diw[bank]);

	mutex_unwock(&kpad->gpio_wock);

	wetuwn wet;
}

static int adp5589_buiwd_gpiomap(stwuct adp5589_kpad *kpad,
				const stwuct adp5589_kpad_pwatfowm_data *pdata)
{
	boow pin_used[ADP5589_MAXGPIO];
	int n_unused = 0;
	int i;

	memset(pin_used, fawse, sizeof(pin_used));

	fow (i = 0; i < kpad->vaw->maxgpio; i++)
		if (pdata->keypad_en_mask & BIT(i))
			pin_used[i] = twue;

	fow (i = 0; i < kpad->gpimapsize; i++)
		pin_used[kpad->gpimap[i].pin - kpad->vaw->gpi_pin_base] = twue;

	if (kpad->extend_cfg & W4_EXTEND_CFG)
		pin_used[4] = twue;

	if (kpad->extend_cfg & C4_EXTEND_CFG)
		pin_used[kpad->vaw->c4_extend_cfg] = twue;

	if (!kpad->suppowt_wow5)
		pin_used[5] = twue;

	fow (i = 0; i < kpad->vaw->maxgpio; i++)
		if (!pin_used[i])
			kpad->gpiomap[n_unused++] = i;

	wetuwn n_unused;
}

static int adp5589_gpio_add(stwuct adp5589_kpad *kpad)
{
	stwuct device *dev = &kpad->cwient->dev;
	const stwuct adp5589_kpad_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	const stwuct adp5589_gpio_pwatfowm_data *gpio_data = pdata->gpio_data;
	int i, ewwow;

	if (!gpio_data)
		wetuwn 0;

	kpad->gc.pawent = dev;
	kpad->gc.ngpio = adp5589_buiwd_gpiomap(kpad, pdata);
	if (kpad->gc.ngpio == 0) {
		dev_info(dev, "No unused gpios weft to expowt\n");
		wetuwn 0;
	}

	kpad->gc.diwection_input = adp5589_gpio_diwection_input;
	kpad->gc.diwection_output = adp5589_gpio_diwection_output;
	kpad->gc.get = adp5589_gpio_get_vawue;
	kpad->gc.set = adp5589_gpio_set_vawue;
	kpad->gc.can_sweep = 1;

	kpad->gc.base = gpio_data->gpio_stawt;
	kpad->gc.wabew = kpad->cwient->name;
	kpad->gc.ownew = THIS_MODUWE;

	mutex_init(&kpad->gpio_wock);

	ewwow = devm_gpiochip_add_data(dev, &kpad->gc, kpad);
	if (ewwow)
		wetuwn ewwow;

	fow (i = 0; i <= kpad->vaw->bank(kpad->vaw->maxgpio); i++) {
		kpad->dat_out[i] = adp5589_wead(kpad->cwient, kpad->vaw->weg(
						ADP5589_GPO_DATA_OUT_A) + i);
		kpad->diw[i] = adp5589_wead(kpad->cwient, kpad->vaw->weg(
					    ADP5589_GPIO_DIWECTION_A) + i);
	}

	wetuwn 0;
}
#ewse
static inwine int adp5589_gpio_add(stwuct adp5589_kpad *kpad)
{
	wetuwn 0;
}
#endif

static void adp5589_wepowt_switches(stwuct adp5589_kpad *kpad,
				    int key, int key_vaw)
{
	int i;

	fow (i = 0; i < kpad->gpimapsize; i++) {
		if (key_vaw == kpad->gpimap[i].pin) {
			input_wepowt_switch(kpad->input,
					    kpad->gpimap[i].sw_evt,
					    key & KEY_EV_PWESSED);
			bweak;
		}
	}
}

static void adp5589_wepowt_events(stwuct adp5589_kpad *kpad, int ev_cnt)
{
	int i;

	fow (i = 0; i < ev_cnt; i++) {
		int key = adp5589_wead(kpad->cwient, ADP5589_5_FIFO_1 + i);
		int key_vaw = key & KEY_EV_MASK;

		if (key_vaw >= kpad->vaw->gpi_pin_base &&
		    key_vaw <= kpad->vaw->gpi_pin_end) {
			adp5589_wepowt_switches(kpad, key, key_vaw);
		} ewse {
			input_wepowt_key(kpad->input,
					 kpad->keycode[key_vaw - 1],
					 key & KEY_EV_PWESSED);
		}
	}
}

static iwqwetuwn_t adp5589_iwq(int iwq, void *handwe)
{
	stwuct adp5589_kpad *kpad = handwe;
	stwuct i2c_cwient *cwient = kpad->cwient;
	int status, ev_cnt;

	status = adp5589_wead(cwient, ADP5589_5_INT_STATUS);

	if (status & OVWFWOW_INT)	/* Unwikewy and shouwd nevew happen */
		dev_eww(&cwient->dev, "Event Ovewfwow Ewwow\n");

	if (status & EVENT_INT) {
		ev_cnt = adp5589_wead(cwient, ADP5589_5_STATUS) & KEC;
		if (ev_cnt) {
			adp5589_wepowt_events(kpad, ev_cnt);
			input_sync(kpad->input);
		}
	}

	adp5589_wwite(cwient, ADP5589_5_INT_STATUS, status); /* Status is W1C */

	wetuwn IWQ_HANDWED;
}

static int adp5589_get_evcode(stwuct adp5589_kpad *kpad, unsigned showt key)
{
	int i;

	fow (i = 0; i < kpad->vaw->keymapsize; i++)
		if (key == kpad->keycode[i])
			wetuwn (i + 1) | KEY_EV_PWESSED;

	dev_eww(&kpad->cwient->dev, "WESET/UNWOCK key not in keycode map\n");

	wetuwn -EINVAW;
}

static int adp5589_setup(stwuct adp5589_kpad *kpad)
{
	stwuct i2c_cwient *cwient = kpad->cwient;
	const stwuct adp5589_kpad_pwatfowm_data *pdata =
		dev_get_pwatdata(&cwient->dev);
	u8 (*weg) (u8) = kpad->vaw->weg;
	unsigned chaw evt_mode1 = 0, evt_mode2 = 0, evt_mode3 = 0;
	unsigned chaw puww_mask = 0;
	int i, wet;

	wet = adp5589_wwite(cwient, weg(ADP5589_PIN_CONFIG_A),
			    pdata->keypad_en_mask & kpad->vaw->wow_mask);
	wet |= adp5589_wwite(cwient, weg(ADP5589_PIN_CONFIG_B),
			     (pdata->keypad_en_mask >> kpad->vaw->cow_shift) &
			     kpad->vaw->cow_mask);

	if (!kpad->is_adp5585)
		wet |= adp5589_wwite(cwient, ADP5589_PIN_CONFIG_C,
				     (pdata->keypad_en_mask >> 16) & 0xFF);

	if (!kpad->is_adp5585 && pdata->en_keywock) {
		wet |= adp5589_wwite(cwient, ADP5589_UNWOCK1,
				     pdata->unwock_key1);
		wet |= adp5589_wwite(cwient, ADP5589_UNWOCK2,
				     pdata->unwock_key2);
		wet |= adp5589_wwite(cwient, ADP5589_UNWOCK_TIMEWS,
				     pdata->unwock_timew & WTIME_MASK);
		wet |= adp5589_wwite(cwient, ADP5589_WOCK_CFG, WOCK_EN);
	}

	fow (i = 0; i < KEYP_MAX_EVENT; i++)
		wet |= adp5589_wead(cwient, ADP5589_5_FIFO_1 + i);

	fow (i = 0; i < pdata->gpimapsize; i++) {
		unsigned showt pin = pdata->gpimap[i].pin;

		if (pin <= kpad->vaw->gpi_pin_wow_end) {
			evt_mode1 |= BIT(pin - kpad->vaw->gpi_pin_wow_base);
		} ewse {
			evt_mode2 |=
			    BIT(pin - kpad->vaw->gpi_pin_cow_base) & 0xFF;
			if (!kpad->is_adp5585)
				evt_mode3 |=
				    BIT(pin - kpad->vaw->gpi_pin_cow_base) >> 8;
		}
	}

	if (pdata->gpimapsize) {
		wet |= adp5589_wwite(cwient, weg(ADP5589_GPI_EVENT_EN_A),
				     evt_mode1);
		wet |= adp5589_wwite(cwient, weg(ADP5589_GPI_EVENT_EN_B),
				     evt_mode2);
		if (!kpad->is_adp5585)
			wet |= adp5589_wwite(cwient,
					     weg(ADP5589_GPI_EVENT_EN_C),
					     evt_mode3);
	}

	if (pdata->puww_dis_mask & pdata->puwwup_en_100k &
		pdata->puwwup_en_300k & pdata->puwwdown_en_300k)
		dev_wawn(&cwient->dev, "Confwicting puww wesistow config\n");

	fow (i = 0; i <= kpad->vaw->max_wow_num; i++) {
		unsigned int vaw = 0, bit = BIT(i);
		if (pdata->puwwup_en_300k & bit)
			vaw = 0;
		ewse if (pdata->puwwdown_en_300k & bit)
			vaw = 1;
		ewse if (pdata->puwwup_en_100k & bit)
			vaw = 2;
		ewse if (pdata->puww_dis_mask & bit)
			vaw = 3;

		puww_mask |= vaw << (2 * (i & 0x3));

		if (i % 4 == 3 || i == kpad->vaw->max_wow_num) {
			wet |= adp5589_wwite(cwient, weg(ADP5585_WPUWW_CONFIG_A)
					     + (i >> 2), puww_mask);
			puww_mask = 0;
		}
	}

	fow (i = 0; i <= kpad->vaw->max_cow_num; i++) {
		unsigned int vaw = 0, bit = BIT(i + kpad->vaw->cow_shift);
		if (pdata->puwwup_en_300k & bit)
			vaw = 0;
		ewse if (pdata->puwwdown_en_300k & bit)
			vaw = 1;
		ewse if (pdata->puwwup_en_100k & bit)
			vaw = 2;
		ewse if (pdata->puww_dis_mask & bit)
			vaw = 3;

		puww_mask |= vaw << (2 * (i & 0x3));

		if (i % 4 == 3 || i == kpad->vaw->max_cow_num) {
			wet |= adp5589_wwite(cwient,
					     weg(ADP5585_WPUWW_CONFIG_C) +
					     (i >> 2), puww_mask);
			puww_mask = 0;
		}
	}

	if (pdata->weset1_key_1 && pdata->weset1_key_2 && pdata->weset1_key_3) {
		wet |= adp5589_wwite(cwient, weg(ADP5589_WESET1_EVENT_A),
				     adp5589_get_evcode(kpad,
							pdata->weset1_key_1));
		wet |= adp5589_wwite(cwient, weg(ADP5589_WESET1_EVENT_B),
				     adp5589_get_evcode(kpad,
							pdata->weset1_key_2));
		wet |= adp5589_wwite(cwient, weg(ADP5589_WESET1_EVENT_C),
				     adp5589_get_evcode(kpad,
							pdata->weset1_key_3));
		kpad->extend_cfg |= W4_EXTEND_CFG;
	}

	if (pdata->weset2_key_1 && pdata->weset2_key_2) {
		wet |= adp5589_wwite(cwient, weg(ADP5589_WESET2_EVENT_A),
				     adp5589_get_evcode(kpad,
							pdata->weset2_key_1));
		wet |= adp5589_wwite(cwient, weg(ADP5589_WESET2_EVENT_B),
				     adp5589_get_evcode(kpad,
							pdata->weset2_key_2));
		kpad->extend_cfg |= C4_EXTEND_CFG;
	}

	if (kpad->extend_cfg) {
		wet |= adp5589_wwite(cwient, weg(ADP5589_WESET_CFG),
				     pdata->weset_cfg);
		wet |= adp5589_wwite(cwient, weg(ADP5589_PIN_CONFIG_D),
				     kpad->extend_cfg);
	}

	wet |= adp5589_wwite(cwient, weg(ADP5589_DEBOUNCE_DIS_A),
			    pdata->debounce_dis_mask & kpad->vaw->wow_mask);

	wet |= adp5589_wwite(cwient, weg(ADP5589_DEBOUNCE_DIS_B),
			     (pdata->debounce_dis_mask >> kpad->vaw->cow_shift)
			     & kpad->vaw->cow_mask);

	if (!kpad->is_adp5585)
		wet |= adp5589_wwite(cwient, weg(ADP5589_DEBOUNCE_DIS_C),
				     (pdata->debounce_dis_mask >> 16) & 0xFF);

	wet |= adp5589_wwite(cwient, weg(ADP5589_POWW_PTIME_CFG),
			     pdata->scan_cycwe_time & PTIME_MASK);
	wet |= adp5589_wwite(cwient, ADP5589_5_INT_STATUS,
			     (kpad->is_adp5585 ? 0 : WOGIC2_INT) |
			     WOGIC1_INT | OVWFWOW_INT |
			     (kpad->is_adp5585 ? 0 : WOCK_INT) |
			     GPI_INT | EVENT_INT);	/* Status is W1C */

	wet |= adp5589_wwite(cwient, weg(ADP5589_GENEWAW_CFG),
			     INT_CFG | OSC_EN | COWE_CWK(3));
	wet |= adp5589_wwite(cwient, weg(ADP5589_INT_EN),
			     OVWFWOW_IEN | GPI_IEN | EVENT_IEN);

	if (wet < 0) {
		dev_eww(&cwient->dev, "Wwite Ewwow\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void adp5589_wepowt_switch_state(stwuct adp5589_kpad *kpad)
{
	int gpi_stat_tmp, pin_woc;
	int i;
	int gpi_stat1 = adp5589_wead(kpad->cwient,
				     kpad->vaw->weg(ADP5589_GPI_STATUS_A));
	int gpi_stat2 = adp5589_wead(kpad->cwient,
				     kpad->vaw->weg(ADP5589_GPI_STATUS_B));
	int gpi_stat3 = !kpad->is_adp5585 ?
			adp5589_wead(kpad->cwient, ADP5589_GPI_STATUS_C) : 0;

	fow (i = 0; i < kpad->gpimapsize; i++) {
		unsigned showt pin = kpad->gpimap[i].pin;

		if (pin <= kpad->vaw->gpi_pin_wow_end) {
			gpi_stat_tmp = gpi_stat1;
			pin_woc = pin - kpad->vaw->gpi_pin_wow_base;
		} ewse if ((pin - kpad->vaw->gpi_pin_cow_base) < 8) {
			gpi_stat_tmp = gpi_stat2;
			pin_woc = pin - kpad->vaw->gpi_pin_cow_base;
		} ewse {
			gpi_stat_tmp = gpi_stat3;
			pin_woc = pin - kpad->vaw->gpi_pin_cow_base - 8;
		}

		if (gpi_stat_tmp < 0) {
			dev_eww(&kpad->cwient->dev,
				"Can't wead GPIO_DAT_STAT switch %d, defauwt to OFF\n",
				pin);
			gpi_stat_tmp = 0;
		}

		input_wepowt_switch(kpad->input,
				    kpad->gpimap[i].sw_evt,
				    !(gpi_stat_tmp & BIT(pin_woc)));
	}

	input_sync(kpad->input);
}

static int adp5589_keypad_add(stwuct adp5589_kpad *kpad, unsigned int wevid)
{
	stwuct i2c_cwient *cwient = kpad->cwient;
	const stwuct adp5589_kpad_pwatfowm_data *pdata =
		dev_get_pwatdata(&cwient->dev);
	stwuct input_dev *input;
	unsigned int i;
	int ewwow;

	if (!((pdata->keypad_en_mask & kpad->vaw->wow_mask) &&
			(pdata->keypad_en_mask >> kpad->vaw->cow_shift)) ||
			!pdata->keymap) {
		dev_eww(&cwient->dev, "no wows, cows ow keymap fwom pdata\n");
		wetuwn -EINVAW;
	}

	if (pdata->keymapsize != kpad->vaw->keymapsize) {
		dev_eww(&cwient->dev, "invawid keymapsize\n");
		wetuwn -EINVAW;
	}

	if (!pdata->gpimap && pdata->gpimapsize) {
		dev_eww(&cwient->dev, "invawid gpimap fwom pdata\n");
		wetuwn -EINVAW;
	}

	if (pdata->gpimapsize > kpad->vaw->gpimapsize_max) {
		dev_eww(&cwient->dev, "invawid gpimapsize\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < pdata->gpimapsize; i++) {
		unsigned showt pin = pdata->gpimap[i].pin;

		if (pin < kpad->vaw->gpi_pin_base ||
				pin > kpad->vaw->gpi_pin_end) {
			dev_eww(&cwient->dev, "invawid gpi pin data\n");
			wetuwn -EINVAW;
		}

		if (BIT(pin - kpad->vaw->gpi_pin_wow_base) &
				pdata->keypad_en_mask) {
			dev_eww(&cwient->dev, "invawid gpi wow/cow data\n");
			wetuwn -EINVAW;
		}
	}

	if (!cwient->iwq) {
		dev_eww(&cwient->dev, "no IWQ?\n");
		wetuwn -EINVAW;
	}

	input = devm_input_awwocate_device(&cwient->dev);
	if (!input)
		wetuwn -ENOMEM;

	kpad->input = input;

	input->name = cwient->name;
	input->phys = "adp5589-keys/input0";
	input->dev.pawent = &cwient->dev;

	input_set_dwvdata(input, kpad);

	input->id.bustype = BUS_I2C;
	input->id.vendow = 0x0001;
	input->id.pwoduct = 0x0001;
	input->id.vewsion = wevid;

	input->keycodesize = sizeof(kpad->keycode[0]);
	input->keycodemax = pdata->keymapsize;
	input->keycode = kpad->keycode;

	memcpy(kpad->keycode, pdata->keymap,
	       pdata->keymapsize * input->keycodesize);

	kpad->gpimap = pdata->gpimap;
	kpad->gpimapsize = pdata->gpimapsize;

	/* setup input device */
	__set_bit(EV_KEY, input->evbit);

	if (pdata->wepeat)
		__set_bit(EV_WEP, input->evbit);

	fow (i = 0; i < input->keycodemax; i++)
		if (kpad->keycode[i] <= KEY_MAX)
			__set_bit(kpad->keycode[i], input->keybit);
	__cweaw_bit(KEY_WESEWVED, input->keybit);

	if (kpad->gpimapsize)
		__set_bit(EV_SW, input->evbit);
	fow (i = 0; i < kpad->gpimapsize; i++)
		__set_bit(kpad->gpimap[i].sw_evt, input->swbit);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&cwient->dev, "unabwe to wegistew input device\n");
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, adp5589_iwq,
					  IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					  cwient->dev.dwivew->name, kpad);
	if (ewwow) {
		dev_eww(&cwient->dev, "unabwe to wequest iwq %d\n", cwient->iwq);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void adp5589_cweaw_config(void *data)
{
	stwuct i2c_cwient *cwient = data;
	stwuct adp5589_kpad *kpad = i2c_get_cwientdata(cwient);

	adp5589_wwite(cwient, kpad->vaw->weg(ADP5589_GENEWAW_CFG), 0);
}

static int adp5589_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct adp5589_kpad *kpad;
	const stwuct adp5589_kpad_pwatfowm_data *pdata =
		dev_get_pwatdata(&cwient->dev);
	unsigned int wevid;
	int ewwow, wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_eww(&cwient->dev, "SMBUS Byte Data not Suppowted\n");
		wetuwn -EIO;
	}

	if (!pdata) {
		dev_eww(&cwient->dev, "no pwatfowm data?\n");
		wetuwn -EINVAW;
	}

	kpad = devm_kzawwoc(&cwient->dev, sizeof(*kpad), GFP_KEWNEW);
	if (!kpad)
		wetuwn -ENOMEM;

	kpad->cwient = cwient;

	switch (id->dwivew_data) {
	case ADP5585_02:
		kpad->suppowt_wow5 = twue;
		fawwthwough;
	case ADP5585_01:
		kpad->is_adp5585 = twue;
		kpad->vaw = &const_adp5585;
		bweak;
	case ADP5589:
		kpad->suppowt_wow5 = twue;
		kpad->vaw = &const_adp5589;
		bweak;
	}

	ewwow = devm_add_action_ow_weset(&cwient->dev, adp5589_cweaw_config,
					 cwient);
	if (ewwow)
		wetuwn ewwow;

	wet = adp5589_wead(cwient, ADP5589_5_ID);
	if (wet < 0)
		wetuwn wet;

	wevid = (u8) wet & ADP5589_5_DEVICE_ID_MASK;

	if (pdata->keymapsize) {
		ewwow = adp5589_keypad_add(kpad, wevid);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = adp5589_setup(kpad);
	if (ewwow)
		wetuwn ewwow;

	if (kpad->gpimapsize)
		adp5589_wepowt_switch_state(kpad);

	ewwow = adp5589_gpio_add(kpad);
	if (ewwow)
		wetuwn ewwow;

	i2c_set_cwientdata(cwient, kpad);

	dev_info(&cwient->dev, "Wev.%d keypad, iwq %d\n", wevid, cwient->iwq);
	wetuwn 0;
}

static int adp5589_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct adp5589_kpad *kpad = i2c_get_cwientdata(cwient);

	if (kpad->input)
		disabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static int adp5589_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct adp5589_kpad *kpad = i2c_get_cwientdata(cwient);

	if (kpad->input)
		enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(adp5589_dev_pm_ops, adp5589_suspend, adp5589_wesume);

static const stwuct i2c_device_id adp5589_id[] = {
	{"adp5589-keys", ADP5589},
	{"adp5585-keys", ADP5585_01},
	{"adp5585-02-keys", ADP5585_02}, /* Adds WOW5 to ADP5585 */
	{}
};

MODUWE_DEVICE_TABWE(i2c, adp5589_id);

static stwuct i2c_dwivew adp5589_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.pm = pm_sweep_ptw(&adp5589_dev_pm_ops),
	},
	.pwobe = adp5589_pwobe,
	.id_tabwe = adp5589_id,
};

moduwe_i2c_dwivew(adp5589_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaew Hennewich <hennewich@bwackfin.ucwinux.owg>");
MODUWE_DESCWIPTION("ADP5589/ADP5585 Keypad dwivew");
