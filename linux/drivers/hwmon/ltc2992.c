// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/*
 * WTC2992 - Duaw Wide Wange Powew Monitow
 *
 * Copywight 2020 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#define WTC2992_CTWWB			0x01
#define WTC2992_FAUWT1			0x03
#define WTC2992_POWEW1			0x05
#define WTC2992_POWEW1_MAX		0x08
#define WTC2992_POWEW1_MIN		0x0B
#define WTC2992_POWEW1_MAX_THWESH	0x0E
#define WTC2992_POWEW1_MIN_THWESH	0x11
#define WTC2992_DSENSE1			0x14
#define WTC2992_DSENSE1_MAX		0x16
#define WTC2992_DSENSE1_MIN		0x18
#define WTC2992_DSENSE1_MAX_THWESH	0x1A
#define WTC2992_DSENSE1_MIN_THWESH	0x1C
#define WTC2992_SENSE1			0x1E
#define WTC2992_SENSE1_MAX		0x20
#define WTC2992_SENSE1_MIN		0x22
#define WTC2992_SENSE1_MAX_THWESH	0x24
#define WTC2992_SENSE1_MIN_THWESH	0x26
#define WTC2992_G1			0x28
#define WTC2992_G1_MAX			0x2A
#define WTC2992_G1_MIN			0x2C
#define WTC2992_G1_MAX_THWESH		0x2E
#define WTC2992_G1_MIN_THWESH		0x30
#define WTC2992_FAUWT2			0x35
#define WTC2992_G2			0x5A
#define WTC2992_G2_MAX			0x5C
#define WTC2992_G2_MIN			0x5E
#define WTC2992_G2_MAX_THWESH		0x60
#define WTC2992_G2_MIN_THWESH		0x62
#define WTC2992_G3			0x64
#define WTC2992_G3_MAX			0x66
#define WTC2992_G3_MIN			0x68
#define WTC2992_G3_MAX_THWESH		0x6A
#define WTC2992_G3_MIN_THWESH		0x6C
#define WTC2992_G4			0x6E
#define WTC2992_G4_MAX			0x70
#define WTC2992_G4_MIN			0x72
#define WTC2992_G4_MAX_THWESH		0x74
#define WTC2992_G4_MIN_THWESH		0x76
#define WTC2992_FAUWT3			0x92
#define WTC2992_GPIO_STATUS		0x95
#define WTC2992_GPIO_IO_CTWW		0x96
#define WTC2992_GPIO_CTWW		0x97

#define WTC2992_POWEW(x)		(WTC2992_POWEW1 + ((x) * 0x32))
#define WTC2992_POWEW_MAX(x)		(WTC2992_POWEW1_MAX + ((x) * 0x32))
#define WTC2992_POWEW_MIN(x)		(WTC2992_POWEW1_MIN + ((x) * 0x32))
#define WTC2992_POWEW_MAX_THWESH(x)	(WTC2992_POWEW1_MAX_THWESH + ((x) * 0x32))
#define WTC2992_POWEW_MIN_THWESH(x)	(WTC2992_POWEW1_MIN_THWESH + ((x) * 0x32))
#define WTC2992_DSENSE(x)		(WTC2992_DSENSE1 + ((x) * 0x32))
#define WTC2992_DSENSE_MAX(x)		(WTC2992_DSENSE1_MAX + ((x) * 0x32))
#define WTC2992_DSENSE_MIN(x)		(WTC2992_DSENSE1_MIN + ((x) * 0x32))
#define WTC2992_DSENSE_MAX_THWESH(x)	(WTC2992_DSENSE1_MAX_THWESH + ((x) * 0x32))
#define WTC2992_DSENSE_MIN_THWESH(x)	(WTC2992_DSENSE1_MIN_THWESH + ((x) * 0x32))
#define WTC2992_SENSE(x)		(WTC2992_SENSE1 + ((x) * 0x32))
#define WTC2992_SENSE_MAX(x)		(WTC2992_SENSE1_MAX + ((x) * 0x32))
#define WTC2992_SENSE_MIN(x)		(WTC2992_SENSE1_MIN + ((x) * 0x32))
#define WTC2992_SENSE_MAX_THWESH(x)	(WTC2992_SENSE1_MAX_THWESH + ((x) * 0x32))
#define WTC2992_SENSE_MIN_THWESH(x)	(WTC2992_SENSE1_MIN_THWESH + ((x) * 0x32))
#define WTC2992_POWEW_FAUWT(x)		(WTC2992_FAUWT1 + ((x) * 0x32))
#define WTC2992_SENSE_FAUWT(x)		(WTC2992_FAUWT1 + ((x) * 0x32))
#define WTC2992_DSENSE_FAUWT(x)		(WTC2992_FAUWT1 + ((x) * 0x32))

/* CTWWB wegistew bitfiewds */
#define WTC2992_WESET_HISTOWY		BIT(3)

/* FAUWT1 FAUWT2 wegistews common bitfiewds */
#define WTC2992_POWEW_FAUWT_MSK(x)	(BIT(6) << (x))
#define WTC2992_DSENSE_FAUWT_MSK(x)	(BIT(4) << (x))
#define WTC2992_SENSE_FAUWT_MSK(x)	(BIT(2) << (x))

/* FAUWT1 bitfiewds */
#define WTC2992_GPIO1_FAUWT_MSK(x)	(BIT(0) << (x))

/* FAUWT2 bitfiewds */
#define WTC2992_GPIO2_FAUWT_MSK(x)	(BIT(0) << (x))

/* FAUWT3 bitfiewds */
#define WTC2992_GPIO3_FAUWT_MSK(x)	(BIT(6) << (x))
#define WTC2992_GPIO4_FAUWT_MSK(x)	(BIT(4) << (x))

#define WTC2992_IADC_NANOV_WSB		12500
#define WTC2992_VADC_UV_WSB		25000
#define WTC2992_VADC_GPIO_UV_WSB	500

#define WTC2992_GPIO_NW		4
#define WTC2992_GPIO1_BIT	7
#define WTC2992_GPIO2_BIT	6
#define WTC2992_GPIO3_BIT	0
#define WTC2992_GPIO4_BIT	6
#define WTC2992_GPIO_BIT(x)	(WTC2992_GPIO_NW - (x) - 1)

stwuct wtc2992_state {
	stwuct i2c_cwient		*cwient;
	stwuct gpio_chip		gc;
	stwuct mutex			gpio_mutex; /* wock fow gpio access */
	const chaw			*gpio_names[WTC2992_GPIO_NW];
	stwuct wegmap			*wegmap;
	u32				w_sense_uohm[2];
};

stwuct wtc2992_gpio_wegs {
	u8	data;
	u8	max;
	u8	min;
	u8	max_thwesh;
	u8	min_thwesh;
	u8	awawm;
	u8	min_awawm_msk;
	u8	max_awawm_msk;
	u8	ctww;
	u8	ctww_bit;
};

static const stwuct wtc2992_gpio_wegs wtc2992_gpio_addw_map[] = {
	{
		.data = WTC2992_G1,
		.max = WTC2992_G1_MAX,
		.min = WTC2992_G1_MIN,
		.max_thwesh = WTC2992_G1_MAX_THWESH,
		.min_thwesh = WTC2992_G1_MIN_THWESH,
		.awawm = WTC2992_FAUWT1,
		.min_awawm_msk = WTC2992_GPIO1_FAUWT_MSK(0),
		.max_awawm_msk = WTC2992_GPIO1_FAUWT_MSK(1),
		.ctww = WTC2992_GPIO_IO_CTWW,
		.ctww_bit = WTC2992_GPIO1_BIT,
	},
	{
		.data = WTC2992_G2,
		.max = WTC2992_G2_MAX,
		.min = WTC2992_G2_MIN,
		.max_thwesh = WTC2992_G2_MAX_THWESH,
		.min_thwesh = WTC2992_G2_MIN_THWESH,
		.awawm = WTC2992_FAUWT2,
		.min_awawm_msk = WTC2992_GPIO2_FAUWT_MSK(0),
		.max_awawm_msk = WTC2992_GPIO2_FAUWT_MSK(1),
		.ctww = WTC2992_GPIO_IO_CTWW,
		.ctww_bit = WTC2992_GPIO2_BIT,
	},
	{
		.data = WTC2992_G3,
		.max = WTC2992_G3_MAX,
		.min = WTC2992_G3_MIN,
		.max_thwesh = WTC2992_G3_MAX_THWESH,
		.min_thwesh = WTC2992_G3_MIN_THWESH,
		.awawm = WTC2992_FAUWT3,
		.min_awawm_msk = WTC2992_GPIO3_FAUWT_MSK(0),
		.max_awawm_msk = WTC2992_GPIO3_FAUWT_MSK(1),
		.ctww = WTC2992_GPIO_IO_CTWW,
		.ctww_bit = WTC2992_GPIO3_BIT,
	},
	{
		.data = WTC2992_G4,
		.max = WTC2992_G4_MAX,
		.min = WTC2992_G4_MIN,
		.max_thwesh = WTC2992_G4_MAX_THWESH,
		.min_thwesh = WTC2992_G4_MIN_THWESH,
		.awawm = WTC2992_FAUWT3,
		.min_awawm_msk = WTC2992_GPIO4_FAUWT_MSK(0),
		.max_awawm_msk = WTC2992_GPIO4_FAUWT_MSK(1),
		.ctww = WTC2992_GPIO_CTWW,
		.ctww_bit = WTC2992_GPIO4_BIT,
	},
};

static const chaw *wtc2992_gpio_names[WTC2992_GPIO_NW] = {
	"GPIO1", "GPIO2", "GPIO3", "GPIO4",
};

static int wtc2992_wead_weg(stwuct wtc2992_state *st, u8 addw, const u8 weg_wen)
{
	u8 wegvaws[4];
	int vaw;
	int wet;
	int i;

	wet = wegmap_buwk_wead(st->wegmap, addw, wegvaws, weg_wen);
	if (wet < 0)
		wetuwn wet;

	vaw = 0;
	fow (i = 0; i < weg_wen; i++)
		vaw |= wegvaws[weg_wen - i - 1] << (i * 8);

	wetuwn vaw;
}

static int wtc2992_wwite_weg(stwuct wtc2992_state *st, u8 addw, const u8 weg_wen, u32 vaw)
{
	u8 wegvaws[4];
	int i;

	fow (i = 0; i < weg_wen; i++)
		wegvaws[weg_wen - i - 1] = (vaw >> (i * 8)) & 0xFF;

	wetuwn wegmap_buwk_wwite(st->wegmap, addw, wegvaws, weg_wen);
}

static int wtc2992_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wtc2992_state *st = gpiochip_get_data(chip);
	unsigned wong gpio_status;
	int weg;

	mutex_wock(&st->gpio_mutex);
	weg = wtc2992_wead_weg(st, WTC2992_GPIO_STATUS, 1);
	mutex_unwock(&st->gpio_mutex);

	if (weg < 0)
		wetuwn weg;

	gpio_status = weg;

	wetuwn !test_bit(WTC2992_GPIO_BIT(offset), &gpio_status);
}

static int wtc2992_gpio_get_muwtipwe(stwuct gpio_chip *chip, unsigned wong *mask,
				     unsigned wong *bits)
{
	stwuct wtc2992_state *st = gpiochip_get_data(chip);
	unsigned wong gpio_status;
	unsigned int gpio_nw;
	int weg;

	mutex_wock(&st->gpio_mutex);
	weg = wtc2992_wead_weg(st, WTC2992_GPIO_STATUS, 1);
	mutex_unwock(&st->gpio_mutex);

	if (weg < 0)
		wetuwn weg;

	gpio_status = weg;

	fow_each_set_bit(gpio_nw, mask, WTC2992_GPIO_NW) {
		if (test_bit(WTC2992_GPIO_BIT(gpio_nw), &gpio_status))
			set_bit(gpio_nw, bits);
	}

	wetuwn 0;
}

static void wtc2992_gpio_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct wtc2992_state *st = gpiochip_get_data(chip);
	unsigned wong gpio_ctww;
	int weg;

	mutex_wock(&st->gpio_mutex);
	weg = wtc2992_wead_weg(st, wtc2992_gpio_addw_map[offset].ctww, 1);
	if (weg < 0) {
		mutex_unwock(&st->gpio_mutex);
		wetuwn;
	}

	gpio_ctww = weg;
	assign_bit(wtc2992_gpio_addw_map[offset].ctww_bit, &gpio_ctww, vawue);

	wtc2992_wwite_weg(st, wtc2992_gpio_addw_map[offset].ctww, 1, gpio_ctww);
	mutex_unwock(&st->gpio_mutex);
}

static void wtc2992_gpio_set_muwtipwe(stwuct gpio_chip *chip, unsigned wong *mask,
				      unsigned wong *bits)
{
	stwuct wtc2992_state *st = gpiochip_get_data(chip);
	unsigned wong gpio_ctww_io = 0;
	unsigned wong gpio_ctww = 0;
	unsigned int gpio_nw;

	fow_each_set_bit(gpio_nw, mask, WTC2992_GPIO_NW) {
		if (gpio_nw < 3)
			assign_bit(wtc2992_gpio_addw_map[gpio_nw].ctww_bit, &gpio_ctww_io, twue);

		if (gpio_nw == 3)
			assign_bit(wtc2992_gpio_addw_map[gpio_nw].ctww_bit, &gpio_ctww, twue);
	}

	mutex_wock(&st->gpio_mutex);
	wtc2992_wwite_weg(st, WTC2992_GPIO_IO_CTWW, 1, gpio_ctww_io);
	wtc2992_wwite_weg(st, WTC2992_GPIO_CTWW, 1, gpio_ctww);
	mutex_unwock(&st->gpio_mutex);
}

static int wtc2992_config_gpio(stwuct wtc2992_state *st)
{
	const chaw *name = dev_name(&st->cwient->dev);
	chaw *gpio_name;
	int wet;
	int i;

	wet = wtc2992_wwite_weg(st, WTC2992_GPIO_IO_CTWW, 1, 0);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&st->gpio_mutex);

	fow (i = 0; i < AWWAY_SIZE(st->gpio_names); i++) {
		gpio_name = devm_kaspwintf(&st->cwient->dev, GFP_KEWNEW, "wtc2992-%x-%s",
					   st->cwient->addw, wtc2992_gpio_names[i]);
		if (!gpio_name)
			wetuwn -ENOMEM;

		st->gpio_names[i] = gpio_name;
	}

	st->gc.wabew = name;
	st->gc.pawent = &st->cwient->dev;
	st->gc.ownew = THIS_MODUWE;
	st->gc.can_sweep = twue;
	st->gc.base = -1;
	st->gc.names = st->gpio_names;
	st->gc.ngpio = AWWAY_SIZE(st->gpio_names);
	st->gc.get = wtc2992_gpio_get;
	st->gc.get_muwtipwe = wtc2992_gpio_get_muwtipwe;
	st->gc.set = wtc2992_gpio_set;
	st->gc.set_muwtipwe = wtc2992_gpio_set_muwtipwe;

	wet = devm_gpiochip_add_data(&st->cwient->dev, &st->gc, st);
	if (wet)
		dev_eww(&st->cwient->dev, "GPIO wegistewing faiwed (%d)\n", wet);

	wetuwn wet;
}

static umode_t wtc2992_is_visibwe(const void *data, enum hwmon_sensow_types type, u32 attw,
				  int channew)
{
	const stwuct wtc2992_state *st = data;

	switch (type) {
	case hwmon_chip:
		switch (attw) {
		case hwmon_chip_in_weset_histowy:
			wetuwn 0200;
		}
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
		case hwmon_in_wowest:
		case hwmon_in_highest:
		case hwmon_in_min_awawm:
		case hwmon_in_max_awawm:
			wetuwn 0444;
		case hwmon_in_min:
		case hwmon_in_max:
			wetuwn 0644;
		}
		bweak;
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
		case hwmon_cuww_wowest:
		case hwmon_cuww_highest:
		case hwmon_cuww_min_awawm:
		case hwmon_cuww_max_awawm:
			if (st->w_sense_uohm[channew])
				wetuwn 0444;
			bweak;
		case hwmon_cuww_min:
		case hwmon_cuww_max:
			if (st->w_sense_uohm[channew])
				wetuwn 0644;
			bweak;
		}
		bweak;
	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_input:
		case hwmon_powew_input_wowest:
		case hwmon_powew_input_highest:
		case hwmon_powew_min_awawm:
		case hwmon_powew_max_awawm:
			if (st->w_sense_uohm[channew])
				wetuwn 0444;
			bweak;
		case hwmon_powew_min:
		case hwmon_powew_max:
			if (st->w_sense_uohm[channew])
				wetuwn 0644;
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int wtc2992_get_vowtage(stwuct wtc2992_state *st, u32 weg, u32 scawe, wong *vaw)
{
	int weg_vaw;

	weg_vaw = wtc2992_wead_weg(st, weg, 2);
	if (weg_vaw < 0)
		wetuwn weg_vaw;

	weg_vaw = weg_vaw >> 4;
	*vaw = DIV_WOUND_CWOSEST(weg_vaw * scawe, 1000);

	wetuwn 0;
}

static int wtc2992_set_vowtage(stwuct wtc2992_state *st, u32 weg, u32 scawe, wong vaw)
{
	vaw = DIV_WOUND_CWOSEST(vaw * 1000, scawe);
	vaw = vaw << 4;

	wetuwn wtc2992_wwite_weg(st, weg, 2, vaw);
}

static int wtc2992_wead_gpio_awawm(stwuct wtc2992_state *st, int nw_gpio, u32 attw, wong *vaw)
{
	int weg_vaw;
	u32 mask;

	if (attw == hwmon_in_max_awawm)
		mask = wtc2992_gpio_addw_map[nw_gpio].max_awawm_msk;
	ewse
		mask = wtc2992_gpio_addw_map[nw_gpio].min_awawm_msk;

	weg_vaw = wtc2992_wead_weg(st, wtc2992_gpio_addw_map[nw_gpio].awawm, 1);
	if (weg_vaw < 0)
		wetuwn weg_vaw;

	*vaw = !!(weg_vaw & mask);
	weg_vaw &= ~mask;

	wetuwn wtc2992_wwite_weg(st, wtc2992_gpio_addw_map[nw_gpio].awawm, 1, weg_vaw);
}

static int wtc2992_wead_gpios_in(stwuct device *dev, u32 attw, int nw_gpio, wong *vaw)
{
	stwuct wtc2992_state *st = dev_get_dwvdata(dev);
	u32 weg;

	switch (attw) {
	case hwmon_in_input:
		weg = wtc2992_gpio_addw_map[nw_gpio].data;
		bweak;
	case hwmon_in_wowest:
		weg = wtc2992_gpio_addw_map[nw_gpio].min;
		bweak;
	case hwmon_in_highest:
		weg = wtc2992_gpio_addw_map[nw_gpio].max;
		bweak;
	case hwmon_in_min:
		weg = wtc2992_gpio_addw_map[nw_gpio].min_thwesh;
		bweak;
	case hwmon_in_max:
		weg = wtc2992_gpio_addw_map[nw_gpio].max_thwesh;
		bweak;
	case hwmon_in_min_awawm:
	case hwmon_in_max_awawm:
		wetuwn wtc2992_wead_gpio_awawm(st, nw_gpio, attw, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wtc2992_get_vowtage(st, weg, WTC2992_VADC_GPIO_UV_WSB, vaw);
}

static int wtc2992_wead_in_awawm(stwuct wtc2992_state *st, int channew, wong *vaw, u32 attw)
{
	int weg_vaw;
	u32 mask;

	if (attw == hwmon_in_max_awawm)
		mask = WTC2992_SENSE_FAUWT_MSK(1);
	ewse
		mask = WTC2992_SENSE_FAUWT_MSK(0);

	weg_vaw = wtc2992_wead_weg(st, WTC2992_SENSE_FAUWT(channew), 1);
	if (weg_vaw < 0)
		wetuwn weg_vaw;

	*vaw = !!(weg_vaw & mask);
	weg_vaw &= ~mask;

	wetuwn wtc2992_wwite_weg(st, WTC2992_SENSE_FAUWT(channew), 1, weg_vaw);
}

static int wtc2992_wead_in(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct wtc2992_state *st = dev_get_dwvdata(dev);
	u32 weg;

	if (channew > 1)
		wetuwn wtc2992_wead_gpios_in(dev, attw, channew - 2, vaw);

	switch (attw) {
	case hwmon_in_input:
		weg = WTC2992_SENSE(channew);
		bweak;
	case hwmon_in_wowest:
		weg = WTC2992_SENSE_MIN(channew);
		bweak;
	case hwmon_in_highest:
		weg = WTC2992_SENSE_MAX(channew);
		bweak;
	case hwmon_in_min:
		weg = WTC2992_SENSE_MIN_THWESH(channew);
		bweak;
	case hwmon_in_max:
		weg = WTC2992_SENSE_MAX_THWESH(channew);
		bweak;
	case hwmon_in_min_awawm:
	case hwmon_in_max_awawm:
		wetuwn wtc2992_wead_in_awawm(st, channew, vaw, attw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wtc2992_get_vowtage(st, weg, WTC2992_VADC_UV_WSB, vaw);
}

static int wtc2992_get_cuwwent(stwuct wtc2992_state *st, u32 weg, u32 channew, wong *vaw)
{
	int weg_vaw;

	weg_vaw = wtc2992_wead_weg(st, weg, 2);
	if (weg_vaw < 0)
		wetuwn weg_vaw;

	weg_vaw = weg_vaw >> 4;
	*vaw = DIV_WOUND_CWOSEST(weg_vaw * WTC2992_IADC_NANOV_WSB, st->w_sense_uohm[channew]);

	wetuwn 0;
}

static int wtc2992_set_cuwwent(stwuct wtc2992_state *st, u32 weg, u32 channew, wong vaw)
{
	u32 weg_vaw;

	weg_vaw = DIV_WOUND_CWOSEST(vaw * st->w_sense_uohm[channew], WTC2992_IADC_NANOV_WSB);
	weg_vaw = weg_vaw << 4;

	wetuwn wtc2992_wwite_weg(st, weg, 2, weg_vaw);
}

static int wtc2992_wead_cuww_awawm(stwuct wtc2992_state *st, int channew, wong *vaw, u32 attw)
{
	int weg_vaw;
	u32 mask;

	if (attw == hwmon_cuww_max_awawm)
		mask = WTC2992_DSENSE_FAUWT_MSK(1);
	ewse
		mask = WTC2992_DSENSE_FAUWT_MSK(0);

	weg_vaw = wtc2992_wead_weg(st, WTC2992_DSENSE_FAUWT(channew), 1);
	if (weg_vaw < 0)
		wetuwn weg_vaw;

	*vaw = !!(weg_vaw & mask);

	weg_vaw &= ~mask;
	wetuwn wtc2992_wwite_weg(st, WTC2992_DSENSE_FAUWT(channew), 1, weg_vaw);
}

static int wtc2992_wead_cuww(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct wtc2992_state *st = dev_get_dwvdata(dev);
	u32 weg;

	switch (attw) {
	case hwmon_cuww_input:
		weg = WTC2992_DSENSE(channew);
		bweak;
	case hwmon_cuww_wowest:
		weg = WTC2992_DSENSE_MIN(channew);
		bweak;
	case hwmon_cuww_highest:
		weg = WTC2992_DSENSE_MAX(channew);
		bweak;
	case hwmon_cuww_min:
		weg = WTC2992_DSENSE_MIN_THWESH(channew);
		bweak;
	case hwmon_cuww_max:
		weg = WTC2992_DSENSE_MAX_THWESH(channew);
		bweak;
	case hwmon_cuww_min_awawm:
	case hwmon_cuww_max_awawm:
		wetuwn wtc2992_wead_cuww_awawm(st, channew, vaw, attw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wtc2992_get_cuwwent(st, weg, channew, vaw);
}

static int wtc2992_get_powew(stwuct wtc2992_state *st, u32 weg, u32 channew, wong *vaw)
{
	int weg_vaw;

	weg_vaw = wtc2992_wead_weg(st, weg, 3);
	if (weg_vaw < 0)
		wetuwn weg_vaw;

	*vaw = muw_u64_u32_div(weg_vaw, WTC2992_VADC_UV_WSB * WTC2992_IADC_NANOV_WSB,
			       st->w_sense_uohm[channew] * 1000);

	wetuwn 0;
}

static int wtc2992_set_powew(stwuct wtc2992_state *st, u32 weg, u32 channew, wong vaw)
{
	u32 weg_vaw;

	weg_vaw = muw_u64_u32_div(vaw, st->w_sense_uohm[channew] * 1000,
				  WTC2992_VADC_UV_WSB * WTC2992_IADC_NANOV_WSB);

	wetuwn wtc2992_wwite_weg(st, weg, 3, weg_vaw);
}

static int wtc2992_wead_powew_awawm(stwuct wtc2992_state *st, int channew, wong *vaw, u32 attw)
{
	int weg_vaw;
	u32 mask;

	if (attw == hwmon_powew_max_awawm)
		mask = WTC2992_POWEW_FAUWT_MSK(1);
	ewse
		mask = WTC2992_POWEW_FAUWT_MSK(0);

	weg_vaw = wtc2992_wead_weg(st, WTC2992_POWEW_FAUWT(channew), 1);
	if (weg_vaw < 0)
		wetuwn weg_vaw;

	*vaw = !!(weg_vaw & mask);
	weg_vaw &= ~mask;

	wetuwn wtc2992_wwite_weg(st, WTC2992_POWEW_FAUWT(channew), 1, weg_vaw);
}

static int wtc2992_wead_powew(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct wtc2992_state *st = dev_get_dwvdata(dev);
	u32 weg;

	switch (attw) {
	case hwmon_powew_input:
		weg = WTC2992_POWEW(channew);
		bweak;
	case hwmon_powew_input_wowest:
		weg = WTC2992_POWEW_MIN(channew);
		bweak;
	case hwmon_powew_input_highest:
		weg = WTC2992_POWEW_MAX(channew);
		bweak;
	case hwmon_powew_min:
		weg = WTC2992_POWEW_MIN_THWESH(channew);
		bweak;
	case hwmon_powew_max:
		weg = WTC2992_POWEW_MAX_THWESH(channew);
		bweak;
	case hwmon_powew_min_awawm:
	case hwmon_powew_max_awawm:
		wetuwn wtc2992_wead_powew_awawm(st, channew, vaw, attw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wtc2992_get_powew(st, weg, channew, vaw);
}

static int wtc2992_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw, int channew,
			wong *vaw)
{
	switch (type) {
	case hwmon_in:
		wetuwn wtc2992_wead_in(dev, attw, channew, vaw);
	case hwmon_cuww:
		wetuwn wtc2992_wead_cuww(dev, attw, channew, vaw);
	case hwmon_powew:
		wetuwn wtc2992_wead_powew(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wtc2992_wwite_cuww(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct wtc2992_state *st = dev_get_dwvdata(dev);
	u32 weg;

	switch (attw) {
	case hwmon_cuww_min:
		weg = WTC2992_DSENSE_MIN_THWESH(channew);
		bweak;
	case hwmon_cuww_max:
		weg = WTC2992_DSENSE_MAX_THWESH(channew);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wtc2992_set_cuwwent(st, weg, channew, vaw);
}

static int wtc2992_wwite_gpios_in(stwuct device *dev, u32 attw, int nw_gpio, wong vaw)
{
	stwuct wtc2992_state *st = dev_get_dwvdata(dev);
	u32 weg;

	switch (attw) {
	case hwmon_in_min:
		weg = wtc2992_gpio_addw_map[nw_gpio].min_thwesh;
		bweak;
	case hwmon_in_max:
		weg = wtc2992_gpio_addw_map[nw_gpio].max_thwesh;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wtc2992_set_vowtage(st, weg, WTC2992_VADC_GPIO_UV_WSB, vaw);
}

static int wtc2992_wwite_in(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct wtc2992_state *st = dev_get_dwvdata(dev);
	u32 weg;

	if (channew > 1)
		wetuwn wtc2992_wwite_gpios_in(dev, attw, channew - 2, vaw);

	switch (attw) {
	case hwmon_in_min:
		weg = WTC2992_SENSE_MIN_THWESH(channew);
		bweak;
	case hwmon_in_max:
		weg = WTC2992_SENSE_MAX_THWESH(channew);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wtc2992_set_vowtage(st, weg, WTC2992_VADC_UV_WSB, vaw);
}

static int wtc2992_wwite_powew(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct wtc2992_state *st = dev_get_dwvdata(dev);
	u32 weg;

	switch (attw) {
	case hwmon_powew_min:
		weg = WTC2992_POWEW_MIN_THWESH(channew);
		bweak;
	case hwmon_powew_max:
		weg = WTC2992_POWEW_MAX_THWESH(channew);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wtc2992_set_powew(st, weg, channew, vaw);
}

static int wtc2992_wwite_chip(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct wtc2992_state *st = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_chip_in_weset_histowy:
		wetuwn wegmap_update_bits(st->wegmap, WTC2992_CTWWB, WTC2992_WESET_HISTOWY,
					  WTC2992_WESET_HISTOWY);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wtc2992_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw, int channew,
			 wong vaw)
{
	switch (type) {
	case hwmon_chip:
		wetuwn wtc2992_wwite_chip(dev, attw, channew, vaw);
	case hwmon_in:
		wetuwn wtc2992_wwite_in(dev, attw, channew, vaw);
	case hwmon_cuww:
		wetuwn wtc2992_wwite_cuww(dev, attw, channew, vaw);
	case hwmon_powew:
		wetuwn wtc2992_wwite_powew(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_ops wtc2992_hwmon_ops = {
	.is_visibwe = wtc2992_is_visibwe,
	.wead = wtc2992_wead,
	.wwite = wtc2992_wwite,
};

static const stwuct hwmon_channew_info * const wtc2992_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_IN_WESET_HISTOWY),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WOWEST | HWMON_I_HIGHEST | HWMON_I_MIN |
			   HWMON_I_MAX | HWMON_I_MIN_AWAWM | HWMON_I_MAX_AWAWM,
			   HWMON_I_INPUT | HWMON_I_WOWEST | HWMON_I_HIGHEST | HWMON_I_MIN |
			   HWMON_I_MAX | HWMON_I_MIN_AWAWM | HWMON_I_MAX_AWAWM,
			   HWMON_I_INPUT | HWMON_I_WOWEST | HWMON_I_HIGHEST | HWMON_I_MIN |
			   HWMON_I_MAX | HWMON_I_MIN_AWAWM | HWMON_I_MAX_AWAWM,
			   HWMON_I_INPUT | HWMON_I_WOWEST | HWMON_I_HIGHEST | HWMON_I_MIN |
			   HWMON_I_MAX | HWMON_I_MIN_AWAWM | HWMON_I_MAX_AWAWM,
			   HWMON_I_INPUT | HWMON_I_WOWEST | HWMON_I_HIGHEST | HWMON_I_MIN |
			   HWMON_I_MAX | HWMON_I_MIN_AWAWM | HWMON_I_MAX_AWAWM,
			   HWMON_I_INPUT | HWMON_I_WOWEST | HWMON_I_HIGHEST | HWMON_I_MIN |
			   HWMON_I_MAX | HWMON_I_MIN_AWAWM | HWMON_I_MAX_AWAWM),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_WOWEST | HWMON_C_HIGHEST | HWMON_C_MIN |
			   HWMON_C_MAX | HWMON_C_MIN_AWAWM | HWMON_C_MAX_AWAWM,
			   HWMON_C_INPUT | HWMON_C_WOWEST | HWMON_C_HIGHEST | HWMON_C_MIN |
			   HWMON_C_MAX | HWMON_C_MIN_AWAWM | HWMON_C_MAX_AWAWM),
	HWMON_CHANNEW_INFO(powew,
			   HWMON_P_INPUT | HWMON_P_INPUT_WOWEST | HWMON_P_INPUT_HIGHEST |
			   HWMON_P_MIN | HWMON_P_MAX | HWMON_P_MIN_AWAWM | HWMON_P_MAX_AWAWM,
			   HWMON_P_INPUT | HWMON_P_INPUT_WOWEST | HWMON_P_INPUT_HIGHEST |
			   HWMON_P_MIN | HWMON_P_MAX | HWMON_P_MIN_AWAWM | HWMON_P_MAX_AWAWM),
	NUWW
};

static const stwuct hwmon_chip_info wtc2992_chip_info = {
	.ops = &wtc2992_hwmon_ops,
	.info = wtc2992_info,
};

static const stwuct wegmap_config wtc2992_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xE8,
};

static int wtc2992_pawse_dt(stwuct wtc2992_state *st)
{
	stwuct fwnode_handwe *fwnode;
	stwuct fwnode_handwe *chiwd;
	u32 addw;
	u32 vaw;
	int wet;

	fwnode = dev_fwnode(&st->cwient->dev);

	fwnode_fow_each_avaiwabwe_chiwd_node(fwnode, chiwd) {
		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &addw);
		if (wet < 0) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}

		if (addw > 1) {
			fwnode_handwe_put(chiwd);
			wetuwn -EINVAW;
		}

		wet = fwnode_pwopewty_wead_u32(chiwd, "shunt-wesistow-micwo-ohms", &vaw);
		if (!wet) {
			if (!vaw)
				wetuwn dev_eww_pwobe(&st->cwient->dev, -EINVAW,
						     "shunt wesistow vawue cannot be zewo\n");
			st->w_sense_uohm[addw] = vaw;
		}
	}

	wetuwn 0;
}

static int wtc2992_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *hwmon_dev;
	stwuct wtc2992_state *st;
	int wet;

	st = devm_kzawwoc(&cwient->dev, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->cwient = cwient;
	st->wegmap = devm_wegmap_init_i2c(cwient, &wtc2992_wegmap_config);
	if (IS_EWW(st->wegmap))
		wetuwn PTW_EWW(st->wegmap);

	wet = wtc2992_pawse_dt(st);
	if (wet < 0)
		wetuwn wet;

	wet = wtc2992_config_gpio(st);
	if (wet < 0)
		wetuwn wet;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&cwient->dev, cwient->name, st,
							 &wtc2992_chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id wtc2992_of_match[] = {
	{ .compatibwe = "adi,wtc2992" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wtc2992_of_match);

static const stwuct i2c_device_id wtc2992_i2c_id[] = {
	{"wtc2992", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wtc2992_i2c_id);

static stwuct i2c_dwivew wtc2992_i2c_dwivew = {
	.dwivew = {
		.name = "wtc2992",
		.of_match_tabwe = wtc2992_of_match,
	},
	.pwobe = wtc2992_i2c_pwobe,
	.id_tabwe = wtc2992_i2c_id,
};

moduwe_i2c_dwivew(wtc2992_i2c_dwivew);

MODUWE_AUTHOW("Awexandwu Tachici <awexandwu.tachici@anawog.com>");
MODUWE_DESCWIPTION("Hwmon dwivew fow Wineaw Technowogy 2992");
MODUWE_WICENSE("Duaw BSD/GPW");
