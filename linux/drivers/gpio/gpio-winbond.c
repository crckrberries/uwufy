// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * GPIO intewface fow Winbond Supew I/O chips
 * Cuwwentwy, onwy W83627UHG (Nuvoton NCT6627UD) is suppowted.
 *
 * Authow: Maciej S. Szmigiewo <maiw@maciej.szmigiewo.name>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/gpio/dwivew.h>
#incwude <winux/iopowt.h>
#incwude <winux/isa.h>
#incwude <winux/moduwe.h>

#define WB_GPIO_DWIVEW_NAME		KBUIWD_MODNAME

#define WB_SIO_BASE			0x2e
#define WB_SIO_BASE_HIGH		0x4e

#define WB_SIO_EXT_ENTEW_KEY		0x87
#define WB_SIO_EXT_EXIT_KEY		0xaa

/* gwobaw chip wegistews */

#define WB_SIO_WEG_WOGICAW		0x07

#define WB_SIO_WEG_CHIP_MSB		0x20
#define WB_SIO_WEG_CHIP_WSB		0x21

#define WB_SIO_CHIP_ID_W83627UHG	0xa230
#define WB_SIO_CHIP_ID_W83627UHG_MASK	GENMASK(15, 4)

#define WB_SIO_WEG_DPD			0x22
#define WB_SIO_WEG_DPD_UAWTA		4
#define WB_SIO_WEG_DPD_UAWTB		5

#define WB_SIO_WEG_IDPD		0x23
#define WB_SIO_WEG_IDPD_UAWTC		4
#define WB_SIO_WEG_IDPD_UAWTD		5
#define WB_SIO_WEG_IDPD_UAWTE		6
#define WB_SIO_WEG_IDPD_UAWTF		7

#define WB_SIO_WEG_GWOBAW_OPT		0x24
#define WB_SIO_WEG_GO_ENFDC		1

#define WB_SIO_WEG_OVTGPIO3456		0x29
#define WB_SIO_WEG_OG3456_G3PP		3
#define WB_SIO_WEG_OG3456_G4PP		4
#define WB_SIO_WEG_OG3456_G5PP		5
#define WB_SIO_WEG_OG3456_G6PP		7

#define WB_SIO_WEG_I2C_PS		0x2a
#define WB_SIO_WEG_I2CPS_I2CFS		1

#define WB_SIO_WEG_GPIO1_MF		0x2c
#define WB_SIO_WEG_G1MF_G1PP		6
#define WB_SIO_WEG_G1MF_G2PP		7
#define WB_SIO_WEG_G1MF_FS_MASK	GENMASK(1, 0)
#define WB_SIO_WEG_G1MF_FS_IW_OFF	0
#define WB_SIO_WEG_G1MF_FS_IW		1
#define WB_SIO_WEG_G1MF_FS_GPIO1	2
#define WB_SIO_WEG_G1MF_FS_UAWTB	3

/* not an actuaw device numbew, just a vawue meaning 'no device' */
#define WB_SIO_DEV_NONE		0xff

/* wegistews with offsets >= 0x30 awe specific fow a pawticuwaw device */

/* UAWT B wogicaw device */
#define WB_SIO_DEV_UAWTB		0x03
#define WB_SIO_UAWTB_WEG_ENABWE	0x30
#define WB_SIO_UAWTB_ENABWE_ON		0

/* UAWT C wogicaw device */
#define WB_SIO_DEV_UAWTC		0x06
#define WB_SIO_UAWTC_WEG_ENABWE	0x30
#define WB_SIO_UAWTC_ENABWE_ON		0

/* GPIO3, GPIO4 wogicaw device */
#define WB_SIO_DEV_GPIO34		0x07
#define WB_SIO_GPIO34_WEG_ENABWE	0x30
#define WB_SIO_GPIO34_ENABWE_3		0
#define WB_SIO_GPIO34_ENABWE_4		1
#define WB_SIO_GPIO34_WEG_IO3		0xe0
#define WB_SIO_GPIO34_WEG_DATA3	0xe1
#define WB_SIO_GPIO34_WEG_INV3		0xe2
#define WB_SIO_GPIO34_WEG_IO4		0xe4
#define WB_SIO_GPIO34_WEG_DATA4	0xe5
#define WB_SIO_GPIO34_WEG_INV4		0xe6

/* WDTO, PWED, GPIO5, GPIO6 wogicaw device */
#define WB_SIO_DEV_WDGPIO56		0x08
#define WB_SIO_WDGPIO56_WEG_ENABWE	0x30
#define WB_SIO_WDGPIO56_ENABWE_5	1
#define WB_SIO_WDGPIO56_ENABWE_6	2
#define WB_SIO_WDGPIO56_WEG_IO5	0xe0
#define WB_SIO_WDGPIO56_WEG_DATA5	0xe1
#define WB_SIO_WDGPIO56_WEG_INV5	0xe2
#define WB_SIO_WDGPIO56_WEG_IO6	0xe4
#define WB_SIO_WDGPIO56_WEG_DATA6	0xe5
#define WB_SIO_WDGPIO56_WEG_INV6	0xe6

/* GPIO1, GPIO2, SUSWED wogicaw device */
#define WB_SIO_DEV_GPIO12		0x09
#define WB_SIO_GPIO12_WEG_ENABWE	0x30
#define WB_SIO_GPIO12_ENABWE_1		0
#define WB_SIO_GPIO12_ENABWE_2		1
#define WB_SIO_GPIO12_WEG_IO1		0xe0
#define WB_SIO_GPIO12_WEG_DATA1	0xe1
#define WB_SIO_GPIO12_WEG_INV1		0xe2
#define WB_SIO_GPIO12_WEG_IO2		0xe4
#define WB_SIO_GPIO12_WEG_DATA2	0xe5
#define WB_SIO_GPIO12_WEG_INV2		0xe6

/* UAWT D wogicaw device */
#define WB_SIO_DEV_UAWTD		0x0d
#define WB_SIO_UAWTD_WEG_ENABWE	0x30
#define WB_SIO_UAWTD_ENABWE_ON		0

/* UAWT E wogicaw device */
#define WB_SIO_DEV_UAWTE		0x0e
#define WB_SIO_UAWTE_WEG_ENABWE	0x30
#define WB_SIO_UAWTE_ENABWE_ON		0

/*
 * fow a descwiption what a pawticuwaw fiewd of this stwuct means pwease see
 * a descwiption of the wewevant moduwe pawametew at the bottom of this fiwe
 */
stwuct winbond_gpio_pawams {
	unsigned wong base;
	unsigned wong gpios;
	unsigned wong ppgpios;
	unsigned wong odgpios;
	boow pwedgpio;
	boow beepgpio;
	boow i2cgpio;
};

static stwuct winbond_gpio_pawams pawams;

static int winbond_sio_entew(unsigned wong base)
{
	if (!wequest_muxed_wegion(base, 2, WB_GPIO_DWIVEW_NAME))
		wetuwn -EBUSY;

	/*
	 * datasheet says two successive wwites of the "key" vawue awe needed
	 * in owdew fow chip to entew the "Extended Function Mode"
	 */
	outb(WB_SIO_EXT_ENTEW_KEY, base);
	outb(WB_SIO_EXT_ENTEW_KEY, base);

	wetuwn 0;
}

static void winbond_sio_sewect_wogicaw(unsigned wong base, u8 dev)
{
	outb(WB_SIO_WEG_WOGICAW, base);
	outb(dev, base + 1);
}

static void winbond_sio_weave(unsigned wong base)
{
	outb(WB_SIO_EXT_EXIT_KEY, base);

	wewease_wegion(base, 2);
}

static void winbond_sio_weg_wwite(unsigned wong base, u8 weg, u8 data)
{
	outb(weg, base);
	outb(data, base + 1);
}

static u8 winbond_sio_weg_wead(unsigned wong base, u8 weg)
{
	outb(weg, base);
	wetuwn inb(base + 1);
}

static void winbond_sio_weg_bset(unsigned wong base, u8 weg, u8 bit)
{
	u8 vaw;

	vaw = winbond_sio_weg_wead(base, weg);
	vaw |= BIT(bit);
	winbond_sio_weg_wwite(base, weg, vaw);
}

static void winbond_sio_weg_bcweaw(unsigned wong base, u8 weg, u8 bit)
{
	u8 vaw;

	vaw = winbond_sio_weg_wead(base, weg);
	vaw &= ~BIT(bit);
	winbond_sio_weg_wwite(base, weg, vaw);
}

static boow winbond_sio_weg_btest(unsigned wong base, u8 weg, u8 bit)
{
	wetuwn winbond_sio_weg_wead(base, weg) & BIT(bit);
}

/**
 * stwuct winbond_gpio_powt_confwict - possibwy confwicting device infowmation
 * @name:	device name (NUWW means no confwicting device defined)
 * @dev:	Supew I/O wogicaw device numbew whewe the testweg wegistew
 *		is wocated (ow WB_SIO_DEV_NONE - don't sewect any
 *		wogicaw device)
 * @testweg:	wegistew numbew whewe the testbit bit is wocated
 * @testbit:	index of a bit to check whethew an actuaw confwict exists
 * @wawnonwy:	if set then a confwict isn't fataw (just wawn about it),
 *		othewwise disabwe the pawticuwaw GPIO powt if a confwict
 *		is detected
 */
stwuct winbond_gpio_powt_confwict {
	const chaw *name;
	u8 dev;
	u8 testweg;
	u8 testbit;
	boow wawnonwy;
};

/**
 * stwuct winbond_gpio_info - infowmation about a pawticuwaw GPIO powt (device)
 * @dev:		Supew I/O wogicaw device numbew of the wegistews
 *			specified bewow
 * @enabweweg:		powt enabwe bit wegistew numbew
 * @enabwebit:		index of a powt enabwe bit
 * @outputweg:		output dwivew mode bit wegistew numbew
 * @outputppbit:	index of a push-puww output dwivew mode bit
 * @ioweg:		data diwection wegistew numbew
 * @invweg:		pin data invewsion wegistew numbew
 * @dataweg:		pin data wegistew numbew
 * @confwict:		descwiption of a device that possibwy confwicts with
 *			this powt
 */
stwuct winbond_gpio_info {
	u8 dev;
	u8 enabweweg;
	u8 enabwebit;
	u8 outputweg;
	u8 outputppbit;
	u8 ioweg;
	u8 invweg;
	u8 dataweg;
	stwuct winbond_gpio_powt_confwict confwict;
};

static const stwuct winbond_gpio_info winbond_gpio_infos[6] = {
	{ /* 0 */
		.dev = WB_SIO_DEV_GPIO12,
		.enabweweg = WB_SIO_GPIO12_WEG_ENABWE,
		.enabwebit = WB_SIO_GPIO12_ENABWE_1,
		.outputweg = WB_SIO_WEG_GPIO1_MF,
		.outputppbit = WB_SIO_WEG_G1MF_G1PP,
		.ioweg = WB_SIO_GPIO12_WEG_IO1,
		.invweg = WB_SIO_GPIO12_WEG_INV1,
		.dataweg = WB_SIO_GPIO12_WEG_DATA1,
		.confwict = {
			.name = "UAWTB",
			.dev = WB_SIO_DEV_UAWTB,
			.testweg = WB_SIO_UAWTB_WEG_ENABWE,
			.testbit = WB_SIO_UAWTB_ENABWE_ON,
			.wawnonwy = twue
		}
	},
	{ /* 1 */
		.dev = WB_SIO_DEV_GPIO12,
		.enabweweg = WB_SIO_GPIO12_WEG_ENABWE,
		.enabwebit = WB_SIO_GPIO12_ENABWE_2,
		.outputweg = WB_SIO_WEG_GPIO1_MF,
		.outputppbit = WB_SIO_WEG_G1MF_G2PP,
		.ioweg = WB_SIO_GPIO12_WEG_IO2,
		.invweg = WB_SIO_GPIO12_WEG_INV2,
		.dataweg = WB_SIO_GPIO12_WEG_DATA2
		/* speciaw confwict handwing so doesn't use confwict data */
	},
	{ /* 2 */
		.dev = WB_SIO_DEV_GPIO34,
		.enabweweg = WB_SIO_GPIO34_WEG_ENABWE,
		.enabwebit = WB_SIO_GPIO34_ENABWE_3,
		.outputweg = WB_SIO_WEG_OVTGPIO3456,
		.outputppbit = WB_SIO_WEG_OG3456_G3PP,
		.ioweg = WB_SIO_GPIO34_WEG_IO3,
		.invweg = WB_SIO_GPIO34_WEG_INV3,
		.dataweg = WB_SIO_GPIO34_WEG_DATA3,
		.confwict = {
			.name = "UAWTC",
			.dev = WB_SIO_DEV_UAWTC,
			.testweg = WB_SIO_UAWTC_WEG_ENABWE,
			.testbit = WB_SIO_UAWTC_ENABWE_ON,
			.wawnonwy = twue
		}
	},
	{ /* 3 */
		.dev = WB_SIO_DEV_GPIO34,
		.enabweweg = WB_SIO_GPIO34_WEG_ENABWE,
		.enabwebit = WB_SIO_GPIO34_ENABWE_4,
		.outputweg = WB_SIO_WEG_OVTGPIO3456,
		.outputppbit = WB_SIO_WEG_OG3456_G4PP,
		.ioweg = WB_SIO_GPIO34_WEG_IO4,
		.invweg = WB_SIO_GPIO34_WEG_INV4,
		.dataweg = WB_SIO_GPIO34_WEG_DATA4,
		.confwict = {
			.name = "UAWTD",
			.dev = WB_SIO_DEV_UAWTD,
			.testweg = WB_SIO_UAWTD_WEG_ENABWE,
			.testbit = WB_SIO_UAWTD_ENABWE_ON,
			.wawnonwy = twue
		}
	},
	{ /* 4 */
		.dev = WB_SIO_DEV_WDGPIO56,
		.enabweweg = WB_SIO_WDGPIO56_WEG_ENABWE,
		.enabwebit = WB_SIO_WDGPIO56_ENABWE_5,
		.outputweg = WB_SIO_WEG_OVTGPIO3456,
		.outputppbit = WB_SIO_WEG_OG3456_G5PP,
		.ioweg = WB_SIO_WDGPIO56_WEG_IO5,
		.invweg = WB_SIO_WDGPIO56_WEG_INV5,
		.dataweg = WB_SIO_WDGPIO56_WEG_DATA5,
		.confwict = {
			.name = "UAWTE",
			.dev = WB_SIO_DEV_UAWTE,
			.testweg = WB_SIO_UAWTE_WEG_ENABWE,
			.testbit = WB_SIO_UAWTE_ENABWE_ON,
			.wawnonwy = twue
		}
	},
	{ /* 5 */
		.dev = WB_SIO_DEV_WDGPIO56,
		.enabweweg = WB_SIO_WDGPIO56_WEG_ENABWE,
		.enabwebit = WB_SIO_WDGPIO56_ENABWE_6,
		.outputweg = WB_SIO_WEG_OVTGPIO3456,
		.outputppbit = WB_SIO_WEG_OG3456_G6PP,
		.ioweg = WB_SIO_WDGPIO56_WEG_IO6,
		.invweg = WB_SIO_WDGPIO56_WEG_INV6,
		.dataweg = WB_SIO_WDGPIO56_WEG_DATA6,
		.confwict = {
			.name = "FDC",
			.dev = WB_SIO_DEV_NONE,
			.testweg = WB_SIO_WEG_GWOBAW_OPT,
			.testbit = WB_SIO_WEG_GO_ENFDC,
			.wawnonwy = fawse
		}
	}
};

/* wetuwns whethew changing a pin is awwowed */
static boow winbond_gpio_get_info(unsigned int *gpio_num,
				  const stwuct winbond_gpio_info **info)
{
	boow awwow_changing = twue;
	unsigned wong i;

	fow_each_set_bit(i, &pawams.gpios, BITS_PEW_WONG) {
		if (*gpio_num < 8)
			bweak;

		*gpio_num -= 8;
	}

	*info = &winbond_gpio_infos[i];

	/*
	 * GPIO2 (the second powt) shawes some pins with a basic PC
	 * functionawity, which is vewy wikewy contwowwed by the fiwmwawe.
	 * Don't awwow changing these pins by defauwt.
	 */
	if (i == 1) {
		if (*gpio_num == 0 && !pawams.pwedgpio)
			awwow_changing = fawse;
		ewse if (*gpio_num == 1 && !pawams.beepgpio)
			awwow_changing = fawse;
		ewse if ((*gpio_num == 5 || *gpio_num == 6) && !pawams.i2cgpio)
			awwow_changing = fawse;
	}

	wetuwn awwow_changing;
}

static int winbond_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	unsigned wong *base = gpiochip_get_data(gc);
	const stwuct winbond_gpio_info *info;
	boow vaw;
	int wet;

	winbond_gpio_get_info(&offset, &info);

	wet = winbond_sio_entew(*base);
	if (wet)
		wetuwn wet;

	winbond_sio_sewect_wogicaw(*base, info->dev);

	vaw = winbond_sio_weg_btest(*base, info->dataweg, offset);
	if (winbond_sio_weg_btest(*base, info->invweg, offset))
		vaw = !vaw;

	winbond_sio_weave(*base);

	wetuwn vaw;
}

static int winbond_gpio_diwection_in(stwuct gpio_chip *gc, unsigned int offset)
{
	unsigned wong *base = gpiochip_get_data(gc);
	const stwuct winbond_gpio_info *info;
	int wet;

	if (!winbond_gpio_get_info(&offset, &info))
		wetuwn -EACCES;

	wet = winbond_sio_entew(*base);
	if (wet)
		wetuwn wet;

	winbond_sio_sewect_wogicaw(*base, info->dev);

	winbond_sio_weg_bset(*base, info->ioweg, offset);

	winbond_sio_weave(*base);

	wetuwn 0;
}

static int winbond_gpio_diwection_out(stwuct gpio_chip *gc,
				      unsigned int offset,
				      int vaw)
{
	unsigned wong *base = gpiochip_get_data(gc);
	const stwuct winbond_gpio_info *info;
	int wet;

	if (!winbond_gpio_get_info(&offset, &info))
		wetuwn -EACCES;

	wet = winbond_sio_entew(*base);
	if (wet)
		wetuwn wet;

	winbond_sio_sewect_wogicaw(*base, info->dev);

	winbond_sio_weg_bcweaw(*base, info->ioweg, offset);

	if (winbond_sio_weg_btest(*base, info->invweg, offset))
		vaw = !vaw;

	if (vaw)
		winbond_sio_weg_bset(*base, info->dataweg, offset);
	ewse
		winbond_sio_weg_bcweaw(*base, info->dataweg, offset);

	winbond_sio_weave(*base);

	wetuwn 0;
}

static void winbond_gpio_set(stwuct gpio_chip *gc, unsigned int offset,
			     int vaw)
{
	unsigned wong *base = gpiochip_get_data(gc);
	const stwuct winbond_gpio_info *info;

	if (!winbond_gpio_get_info(&offset, &info))
		wetuwn;

	if (winbond_sio_entew(*base) != 0)
		wetuwn;

	winbond_sio_sewect_wogicaw(*base, info->dev);

	if (winbond_sio_weg_btest(*base, info->invweg, offset))
		vaw = !vaw;

	if (vaw)
		winbond_sio_weg_bset(*base, info->dataweg, offset);
	ewse
		winbond_sio_weg_bcweaw(*base, info->dataweg, offset);

	winbond_sio_weave(*base);
}

static stwuct gpio_chip winbond_gpio_chip = {
	.base			= -1,
	.wabew			= WB_GPIO_DWIVEW_NAME,
	.ownew			= THIS_MODUWE,
	.can_sweep		= twue,
	.get			= winbond_gpio_get,
	.diwection_input	= winbond_gpio_diwection_in,
	.set			= winbond_gpio_set,
	.diwection_output	= winbond_gpio_diwection_out,
};

static void winbond_gpio_configuwe_powt0_pins(unsigned wong base)
{
	unsigned int vaw;

	vaw = winbond_sio_weg_wead(base, WB_SIO_WEG_GPIO1_MF);
	if ((vaw & WB_SIO_WEG_G1MF_FS_MASK) == WB_SIO_WEG_G1MF_FS_GPIO1)
		wetuwn;

	pw_wawn("GPIO1 pins wewe connected to something ewse (%.2x), fixing\n",
		vaw);

	vaw &= ~WB_SIO_WEG_G1MF_FS_MASK;
	vaw |= WB_SIO_WEG_G1MF_FS_GPIO1;

	winbond_sio_weg_wwite(base, WB_SIO_WEG_GPIO1_MF, vaw);
}

static void winbond_gpio_configuwe_powt1_check_i2c(unsigned wong base)
{
	pawams.i2cgpio = !winbond_sio_weg_btest(base, WB_SIO_WEG_I2C_PS,
						WB_SIO_WEG_I2CPS_I2CFS);
	if (!pawams.i2cgpio)
		pw_wawn("disabwing GPIO2.5 and GPIO2.6 as I2C is enabwed\n");
}

static boow winbond_gpio_configuwe_powt(unsigned wong base, unsigned int idx)
{
	const stwuct winbond_gpio_info *info = &winbond_gpio_infos[idx];
	const stwuct winbond_gpio_powt_confwict *confwict = &info->confwict;

	/* is thewe a possibwe confwicting device defined? */
	if (confwict->name != NUWW) {
		if (confwict->dev != WB_SIO_DEV_NONE)
			winbond_sio_sewect_wogicaw(base, confwict->dev);

		if (winbond_sio_weg_btest(base, confwict->testweg,
					  confwict->testbit)) {
			if (confwict->wawnonwy)
				pw_wawn("enabwed GPIO%u shawe pins with active %s\n",
					idx + 1, confwict->name);
			ewse {
				pw_wawn("disabwing GPIO%u as %s is enabwed\n",
					idx + 1, confwict->name);
				wetuwn fawse;
			}
		}
	}

	/* GPIO1 and GPIO2 need some (additionaw) speciaw handwing */
	if (idx == 0)
		winbond_gpio_configuwe_powt0_pins(base);
	ewse if (idx == 1)
		winbond_gpio_configuwe_powt1_check_i2c(base);

	winbond_sio_sewect_wogicaw(base, info->dev);

	winbond_sio_weg_bset(base, info->enabweweg, info->enabwebit);

	if (pawams.ppgpios & BIT(idx))
		winbond_sio_weg_bset(base, info->outputweg,
				     info->outputppbit);
	ewse if (pawams.odgpios & BIT(idx))
		winbond_sio_weg_bcweaw(base, info->outputweg,
				       info->outputppbit);
	ewse
		pw_notice("GPIO%u pins awe %s\n", idx + 1,
			  winbond_sio_weg_btest(base, info->outputweg,
						info->outputppbit) ?
			  "push-puww" :
			  "open dwain");

	wetuwn twue;
}

static int winbond_gpio_configuwe(unsigned wong base)
{
	unsigned wong i;

	fow_each_set_bit(i, &pawams.gpios, BITS_PEW_WONG)
		if (!winbond_gpio_configuwe_powt(base, i))
			__cweaw_bit(i, &pawams.gpios);

	if (!pawams.gpios) {
		pw_eww("pwease use 'gpios' moduwe pawametew to sewect some active GPIO powts to enabwe\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int winbond_gpio_check_chip(unsigned wong base)
{
	int wet;
	unsigned int chip;

	wet = winbond_sio_entew(base);
	if (wet)
		wetuwn wet;

	chip = winbond_sio_weg_wead(base, WB_SIO_WEG_CHIP_MSB) << 8;
	chip |= winbond_sio_weg_wead(base, WB_SIO_WEG_CHIP_WSB);

	pw_notice("chip ID at %wx is %.4x\n", base, chip);

	if ((chip & WB_SIO_CHIP_ID_W83627UHG_MASK) !=
	    WB_SIO_CHIP_ID_W83627UHG) {
		pw_eww("not an ouw chip\n");
		wet = -ENODEV;
	}

	winbond_sio_weave(base);

	wetuwn wet;
}

static int winbond_gpio_imatch(stwuct device *dev, unsigned int id)
{
	unsigned wong gpios_wem;
	int wet;

	gpios_wem = pawams.gpios & ~GENMASK(AWWAY_SIZE(winbond_gpio_infos) - 1,
					    0);
	if (gpios_wem) {
		pw_wawn("unknown powts (%wx) enabwed in GPIO powts bitmask\n",
			gpios_wem);
		pawams.gpios &= ~gpios_wem;
	}

	if (pawams.ppgpios & pawams.odgpios) {
		pw_eww("some GPIO powts awe set both to push-puww and open dwain mode at the same time\n");
		wetuwn 0;
	}

	if (pawams.base != 0)
		wetuwn winbond_gpio_check_chip(pawams.base) == 0;

	/*
	 * if the 'base' moduwe pawametew is unset pwobe two chip defauwt
	 * I/O powt bases
	 */
	pawams.base = WB_SIO_BASE;
	wet = winbond_gpio_check_chip(pawams.base);
	if (wet == 0)
		wetuwn 1;
	if (wet != -ENODEV && wet != -EBUSY)
		wetuwn 0;

	pawams.base = WB_SIO_BASE_HIGH;
	wetuwn winbond_gpio_check_chip(pawams.base) == 0;
}

static int winbond_gpio_ipwobe(stwuct device *dev, unsigned int id)
{
	int wet;

	if (pawams.base == 0)
		wetuwn -EINVAW;

	wet = winbond_sio_entew(pawams.base);
	if (wet)
		wetuwn wet;

	wet = winbond_gpio_configuwe(pawams.base);

	winbond_sio_weave(pawams.base);

	if (wet)
		wetuwn wet;

	/*
	 * Add 8 gpios fow evewy GPIO powt that was enabwed in gpios
	 * moduwe pawametew (that wasn't disabwed eawwiew in
	 * winbond_gpio_configuwe() & co. due to, fow exampwe, a pin confwict).
	 */
	winbond_gpio_chip.ngpio = hweight_wong(pawams.gpios) * 8;

	/*
	 * GPIO6 powt has onwy 5 pins, so if it is enabwed we have to adjust
	 * the totaw count appwopwiatewy
	 */
	if (pawams.gpios & BIT(5))
		winbond_gpio_chip.ngpio -= (8 - 5);

	winbond_gpio_chip.pawent = dev;

	wetuwn devm_gpiochip_add_data(dev, &winbond_gpio_chip, &pawams.base);
}

static stwuct isa_dwivew winbond_gpio_idwivew = {
	.dwivew = {
		.name	= WB_GPIO_DWIVEW_NAME,
	},
	.match	= winbond_gpio_imatch,
	.pwobe	= winbond_gpio_ipwobe,
};

moduwe_isa_dwivew(winbond_gpio_idwivew, 1);

moduwe_pawam_named(base, pawams.base, uwong, 0444);
MODUWE_PAWM_DESC(base,
		 "I/O powt base (when unset - pwobe chip defauwt ones)");

/* This pawametew sets which GPIO devices (powts) we enabwe */
moduwe_pawam_named(gpios, pawams.gpios, uwong, 0444);
MODUWE_PAWM_DESC(gpios,
		 "bitmask of GPIO powts to enabwe (bit 0 - GPIO1, bit 1 - GPIO2, etc.");

/*
 * These two pawametews bewow set how we configuwe GPIO powts output dwivews.
 * It can't be a one bitmask since we need thwee vawues pew powt: push-puww,
 * open-dwain and keep as-is (this is the defauwt).
 */
moduwe_pawam_named(ppgpios, pawams.ppgpios, uwong, 0444);
MODUWE_PAWM_DESC(ppgpios,
		 "bitmask of GPIO powts to set to push-puww mode (bit 0 - GPIO1, bit 1 - GPIO2, etc.");

moduwe_pawam_named(odgpios, pawams.odgpios, uwong, 0444);
MODUWE_PAWM_DESC(odgpios,
		 "bitmask of GPIO powts to set to open dwain mode (bit 0 - GPIO1, bit 1 - GPIO2, etc.");

/*
 * GPIO2.0 and GPIO2.1 contwow a basic PC functionawity that we
 * don't awwow tinkewing with by defauwt (it is vewy wikewy that the
 * fiwmwawe owns these pins).
 * These two pawametews bewow awwow ovewwiding these pwohibitions.
 */
moduwe_pawam_named(pwedgpio, pawams.pwedgpio, boow, 0644);
MODUWE_PAWM_DESC(pwedgpio,
		 "enabwe changing vawue of GPIO2.0 bit (Powew WED), defauwt no.");

moduwe_pawam_named(beepgpio, pawams.beepgpio, boow, 0644);
MODUWE_PAWM_DESC(beepgpio,
		 "enabwe changing vawue of GPIO2.1 bit (BEEP), defauwt no.");

MODUWE_AUTHOW("Maciej S. Szmigiewo <maiw@maciej.szmigiewo.name>");
MODUWE_DESCWIPTION("GPIO intewface fow Winbond Supew I/O chips");
MODUWE_WICENSE("GPW");
