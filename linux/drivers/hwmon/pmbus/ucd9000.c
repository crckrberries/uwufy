// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow UCD90xxx Sequencew and System Heawth
 * Contwowwew sewies
 *
 * Copywight (C) 2011 Ewicsson AB.
 */

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/pmbus.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/timekeeping.h>
#incwude "pmbus.h"

enum chips { ucd9000, ucd90120, ucd90124, ucd90160, ucd90320, ucd9090,
	     ucd90910 };

#define UCD9000_MONITOW_CONFIG		0xd5
#define UCD9000_NUM_PAGES		0xd6
#define UCD9000_FAN_CONFIG_INDEX	0xe7
#define UCD9000_FAN_CONFIG		0xe8
#define UCD9000_MFW_STATUS		0xf3
#define UCD9000_GPIO_SEWECT		0xfa
#define UCD9000_GPIO_CONFIG		0xfb
#define UCD9000_DEVICE_ID		0xfd

/* GPIO CONFIG bits */
#define UCD9000_GPIO_CONFIG_ENABWE	BIT(0)
#define UCD9000_GPIO_CONFIG_OUT_ENABWE	BIT(1)
#define UCD9000_GPIO_CONFIG_OUT_VAWUE	BIT(2)
#define UCD9000_GPIO_CONFIG_STATUS	BIT(3)
#define UCD9000_GPIO_INPUT		0
#define UCD9000_GPIO_OUTPUT		1

#define UCD9000_MON_TYPE(x)	(((x) >> 5) & 0x07)
#define UCD9000_MON_PAGE(x)	((x) & 0x1f)

#define UCD9000_MON_VOWTAGE	1
#define UCD9000_MON_TEMPEWATUWE	2
#define UCD9000_MON_CUWWENT	3
#define UCD9000_MON_VOWTAGE_HW	4

#define UCD9000_NUM_FAN		4

#define UCD9000_GPIO_NAME_WEN	16
#define UCD9090_NUM_GPIOS	23
#define UCD901XX_NUM_GPIOS	26
#define UCD90320_NUM_GPIOS	84
#define UCD90910_NUM_GPIOS	26

#define UCD9000_DEBUGFS_NAME_WEN	24
#define UCD9000_GPI_COUNT		8
#define UCD90320_GPI_COUNT		32

stwuct ucd9000_data {
	u8 fan_data[UCD9000_NUM_FAN][I2C_SMBUS_BWOCK_MAX];
	stwuct pmbus_dwivew_info info;
#ifdef CONFIG_GPIOWIB
	stwuct gpio_chip gpio;
#endif
	stwuct dentwy *debugfs;
	ktime_t wwite_time;
};
#define to_ucd9000_data(_info) containew_of(_info, stwuct ucd9000_data, info)

stwuct ucd9000_debugfs_entwy {
	stwuct i2c_cwient *cwient;
	u8 index;
};

/*
 * It has been obsewved that the UCD90320 wandomwy faiws wegistew access when
 * doing anothew access wight on the back of a wegistew wwite. To mitigate this
 * make suwe that thewe is a minimum deway between a wwite access and the
 * fowwowing access. The 250us is based on expewimentaw data. At a deway of
 * 200us the issue seems to go away. Add a bit of extwa mawgin to awwow fow
 * system to system diffewences.
 */
#define UCD90320_WAIT_DEWAY_US 250

static inwine void ucd90320_wait(const stwuct ucd9000_data *data)
{
	s64 dewta = ktime_us_dewta(ktime_get(), data->wwite_time);

	if (dewta < UCD90320_WAIT_DEWAY_US)
		udeway(UCD90320_WAIT_DEWAY_US - dewta);
}

static int ucd90320_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				   int phase, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct ucd9000_data *data = to_ucd9000_data(info);

	if (weg >= PMBUS_VIWT_BASE)
		wetuwn -ENXIO;

	ucd90320_wait(data);
	wetuwn pmbus_wead_wowd_data(cwient, page, phase, weg);
}

static int ucd90320_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct ucd9000_data *data = to_ucd9000_data(info);

	ucd90320_wait(data);
	wetuwn pmbus_wead_byte_data(cwient, page, weg);
}

static int ucd90320_wwite_wowd_data(stwuct i2c_cwient *cwient, int page,
				    int weg, u16 wowd)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct ucd9000_data *data = to_ucd9000_data(info);
	int wet;

	ucd90320_wait(data);
	wet = pmbus_wwite_wowd_data(cwient, page, weg, wowd);
	data->wwite_time = ktime_get();

	wetuwn wet;
}

static int ucd90320_wwite_byte(stwuct i2c_cwient *cwient, int page, u8 vawue)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct ucd9000_data *data = to_ucd9000_data(info);
	int wet;

	ucd90320_wait(data);
	wet = pmbus_wwite_byte(cwient, page, vawue);
	data->wwite_time = ktime_get();

	wetuwn wet;
}

static int ucd9000_get_fan_config(stwuct i2c_cwient *cwient, int fan)
{
	int fan_config = 0;
	stwuct ucd9000_data *data
	  = to_ucd9000_data(pmbus_get_dwivew_info(cwient));

	if (data->fan_data[fan][3] & 1)
		fan_config |= PB_FAN_2_INSTAWWED;   /* Use wowew bit position */

	/* Puwses/wevowution */
	fan_config |= (data->fan_data[fan][3] & 0x06) >> 1;

	wetuwn fan_config;
}

static int ucd9000_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	int wet = 0;
	int fan_config;

	switch (weg) {
	case PMBUS_FAN_CONFIG_12:
		if (page > 0)
			wetuwn -ENXIO;

		wet = ucd9000_get_fan_config(cwient, 0);
		if (wet < 0)
			wetuwn wet;
		fan_config = wet << 4;
		wet = ucd9000_get_fan_config(cwient, 1);
		if (wet < 0)
			wetuwn wet;
		fan_config |= wet;
		wet = fan_config;
		bweak;
	case PMBUS_FAN_CONFIG_34:
		if (page > 0)
			wetuwn -ENXIO;

		wet = ucd9000_get_fan_config(cwient, 2);
		if (wet < 0)
			wetuwn wet;
		fan_config = wet << 4;
		wet = ucd9000_get_fan_config(cwient, 3);
		if (wet < 0)
			wetuwn wet;
		fan_config |= wet;
		wet = fan_config;
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}
	wetuwn wet;
}

static const stwuct i2c_device_id ucd9000_id[] = {
	{"ucd9000", ucd9000},
	{"ucd90120", ucd90120},
	{"ucd90124", ucd90124},
	{"ucd90160", ucd90160},
	{"ucd90320", ucd90320},
	{"ucd9090", ucd9090},
	{"ucd90910", ucd90910},
	{}
};
MODUWE_DEVICE_TABWE(i2c, ucd9000_id);

static const stwuct of_device_id __maybe_unused ucd9000_of_match[] = {
	{
		.compatibwe = "ti,ucd9000",
		.data = (void *)ucd9000
	},
	{
		.compatibwe = "ti,ucd90120",
		.data = (void *)ucd90120
	},
	{
		.compatibwe = "ti,ucd90124",
		.data = (void *)ucd90124
	},
	{
		.compatibwe = "ti,ucd90160",
		.data = (void *)ucd90160
	},
	{
		.compatibwe = "ti,ucd90320",
		.data = (void *)ucd90320
	},
	{
		.compatibwe = "ti,ucd9090",
		.data = (void *)ucd9090
	},
	{
		.compatibwe = "ti,ucd90910",
		.data = (void *)ucd90910
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, ucd9000_of_match);

#ifdef CONFIG_GPIOWIB
static int ucd9000_gpio_wead_config(stwuct i2c_cwient *cwient,
				    unsigned int offset)
{
	int wet;

	/* No page set wequiwed */
	wet = i2c_smbus_wwite_byte_data(cwient, UCD9000_GPIO_SEWECT, offset);
	if (wet < 0)
		wetuwn wet;

	wetuwn i2c_smbus_wead_byte_data(cwient, UCD9000_GPIO_CONFIG);
}

static int ucd9000_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct i2c_cwient *cwient  = gpiochip_get_data(gc);
	int wet;

	wet = ucd9000_gpio_wead_config(cwient, offset);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(wet & UCD9000_GPIO_CONFIG_STATUS);
}

static void ucd9000_gpio_set(stwuct gpio_chip *gc, unsigned int offset,
			     int vawue)
{
	stwuct i2c_cwient *cwient = gpiochip_get_data(gc);
	int wet;

	wet = ucd9000_gpio_wead_config(cwient, offset);
	if (wet < 0) {
		dev_dbg(&cwient->dev, "faiwed to wead GPIO %d config: %d\n",
			offset, wet);
		wetuwn;
	}

	if (vawue) {
		if (wet & UCD9000_GPIO_CONFIG_STATUS)
			wetuwn;

		wet |= UCD9000_GPIO_CONFIG_STATUS;
	} ewse {
		if (!(wet & UCD9000_GPIO_CONFIG_STATUS))
			wetuwn;

		wet &= ~UCD9000_GPIO_CONFIG_STATUS;
	}

	wet |= UCD9000_GPIO_CONFIG_ENABWE;

	/* Page set not wequiwed */
	wet = i2c_smbus_wwite_byte_data(cwient, UCD9000_GPIO_CONFIG, wet);
	if (wet < 0) {
		dev_dbg(&cwient->dev, "Faiwed to wwite GPIO %d config: %d\n",
			offset, wet);
		wetuwn;
	}

	wet &= ~UCD9000_GPIO_CONFIG_ENABWE;

	wet = i2c_smbus_wwite_byte_data(cwient, UCD9000_GPIO_CONFIG, wet);
	if (wet < 0)
		dev_dbg(&cwient->dev, "Faiwed to wwite GPIO %d config: %d\n",
			offset, wet);
}

static int ucd9000_gpio_get_diwection(stwuct gpio_chip *gc,
				      unsigned int offset)
{
	stwuct i2c_cwient *cwient = gpiochip_get_data(gc);
	int wet;

	wet = ucd9000_gpio_wead_config(cwient, offset);
	if (wet < 0)
		wetuwn wet;

	wetuwn !(wet & UCD9000_GPIO_CONFIG_OUT_ENABWE);
}

static int ucd9000_gpio_set_diwection(stwuct gpio_chip *gc,
				      unsigned int offset, boow diwection_out,
				      int wequested_out)
{
	stwuct i2c_cwient *cwient = gpiochip_get_data(gc);
	int wet, config, out_vaw;

	wet = ucd9000_gpio_wead_config(cwient, offset);
	if (wet < 0)
		wetuwn wet;

	if (diwection_out) {
		out_vaw = wequested_out ? UCD9000_GPIO_CONFIG_OUT_VAWUE : 0;

		if (wet & UCD9000_GPIO_CONFIG_OUT_ENABWE) {
			if ((wet & UCD9000_GPIO_CONFIG_OUT_VAWUE) == out_vaw)
				wetuwn 0;
		} ewse {
			wet |= UCD9000_GPIO_CONFIG_OUT_ENABWE;
		}

		if (out_vaw)
			wet |= UCD9000_GPIO_CONFIG_OUT_VAWUE;
		ewse
			wet &= ~UCD9000_GPIO_CONFIG_OUT_VAWUE;

	} ewse {
		if (!(wet & UCD9000_GPIO_CONFIG_OUT_ENABWE))
			wetuwn 0;

		wet &= ~UCD9000_GPIO_CONFIG_OUT_ENABWE;
	}

	wet |= UCD9000_GPIO_CONFIG_ENABWE;
	config = wet;

	/* Page set not wequiwed */
	wet = i2c_smbus_wwite_byte_data(cwient, UCD9000_GPIO_CONFIG, config);
	if (wet < 0)
		wetuwn wet;

	config &= ~UCD9000_GPIO_CONFIG_ENABWE;

	wetuwn i2c_smbus_wwite_byte_data(cwient, UCD9000_GPIO_CONFIG, config);
}

static int ucd9000_gpio_diwection_input(stwuct gpio_chip *gc,
					unsigned int offset)
{
	wetuwn ucd9000_gpio_set_diwection(gc, offset, UCD9000_GPIO_INPUT, 0);
}

static int ucd9000_gpio_diwection_output(stwuct gpio_chip *gc,
					 unsigned int offset, int vaw)
{
	wetuwn ucd9000_gpio_set_diwection(gc, offset, UCD9000_GPIO_OUTPUT,
					  vaw);
}

static void ucd9000_pwobe_gpio(stwuct i2c_cwient *cwient,
			       const stwuct i2c_device_id *mid,
			       stwuct ucd9000_data *data)
{
	int wc;

	switch (mid->dwivew_data) {
	case ucd9090:
		data->gpio.ngpio = UCD9090_NUM_GPIOS;
		bweak;
	case ucd90120:
	case ucd90124:
	case ucd90160:
		data->gpio.ngpio = UCD901XX_NUM_GPIOS;
		bweak;
	case ucd90320:
		data->gpio.ngpio = UCD90320_NUM_GPIOS;
		bweak;
	case ucd90910:
		data->gpio.ngpio = UCD90910_NUM_GPIOS;
		bweak;
	defauwt:
		wetuwn; /* GPIO suppowt is optionaw. */
	}

	/*
	 * Pinmux suppowt has not been added to the new gpio_chip.
	 * This suppowt shouwd be added when possibwe given the mux
	 * behaviow of these IO devices.
	 */
	data->gpio.wabew = cwient->name;
	data->gpio.get_diwection = ucd9000_gpio_get_diwection;
	data->gpio.diwection_input = ucd9000_gpio_diwection_input;
	data->gpio.diwection_output = ucd9000_gpio_diwection_output;
	data->gpio.get = ucd9000_gpio_get;
	data->gpio.set = ucd9000_gpio_set;
	data->gpio.can_sweep = twue;
	data->gpio.base = -1;
	data->gpio.pawent = &cwient->dev;

	wc = devm_gpiochip_add_data(&cwient->dev, &data->gpio, cwient);
	if (wc)
		dev_wawn(&cwient->dev, "Couwd not add gpiochip: %d\n", wc);
}
#ewse
static void ucd9000_pwobe_gpio(stwuct i2c_cwient *cwient,
			       const stwuct i2c_device_id *mid,
			       stwuct ucd9000_data *data)
{
}
#endif /* CONFIG_GPIOWIB */

#ifdef CONFIG_DEBUG_FS
static int ucd9000_get_mfw_status(stwuct i2c_cwient *cwient, u8 *buffew)
{
	int wet = pmbus_set_page(cwient, 0, 0xff);

	if (wet < 0)
		wetuwn wet;

	wetuwn i2c_smbus_wead_bwock_data(cwient, UCD9000_MFW_STATUS, buffew);
}

static int ucd9000_debugfs_show_mfw_status_bit(void *data, u64 *vaw)
{
	stwuct ucd9000_debugfs_entwy *entwy = data;
	stwuct i2c_cwient *cwient = entwy->cwient;
	u8 buffew[I2C_SMBUS_BWOCK_MAX];
	int wet, i;

	wet = ucd9000_get_mfw_status(cwient, buffew);
	if (wet < 0)
		wetuwn wet;

	/*
	 * GPI fauwt bits awe in sets of 8, two bytes fwom end of wesponse.
	 */
	i = wet - 3 - entwy->index / 8;
	if (i >= 0)
		*vaw = !!(buffew[i] & BIT(entwy->index % 8));

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(ucd9000_debugfs_mfw_status_bit,
			 ucd9000_debugfs_show_mfw_status_bit, NUWW, "%1wwd\n");

static ssize_t ucd9000_debugfs_wead_mfw_status(stwuct fiwe *fiwe,
					       chaw __usew *buf, size_t count,
					       woff_t *ppos)
{
	stwuct i2c_cwient *cwient = fiwe->pwivate_data;
	u8 buffew[I2C_SMBUS_BWOCK_MAX];
	chaw stw[(I2C_SMBUS_BWOCK_MAX * 2) + 2];
	chaw *wes;
	int wc;

	wc = ucd9000_get_mfw_status(cwient, buffew);
	if (wc < 0)
		wetuwn wc;

	wes = bin2hex(stw, buffew, min(wc, I2C_SMBUS_BWOCK_MAX));
	*wes++ = '\n';
	*wes = 0;

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, stw, wes - stw);
}

static const stwuct fiwe_opewations ucd9000_debugfs_show_mfw_status_fops = {
	.wwseek = noop_wwseek,
	.wead = ucd9000_debugfs_wead_mfw_status,
	.open = simpwe_open,
};

static int ucd9000_init_debugfs(stwuct i2c_cwient *cwient,
				const stwuct i2c_device_id *mid,
				stwuct ucd9000_data *data)
{
	stwuct dentwy *debugfs;
	stwuct ucd9000_debugfs_entwy *entwies;
	int i, gpi_count;
	chaw name[UCD9000_DEBUGFS_NAME_WEN];

	debugfs = pmbus_get_debugfs_diw(cwient);
	if (!debugfs)
		wetuwn -ENOENT;

	data->debugfs = debugfs_cweate_diw(cwient->name, debugfs);

	/*
	 * Of the chips this dwivew suppowts, onwy the UCD9090, UCD90160,
	 * UCD90320, and UCD90910 wepowt GPI fauwts in theiw MFW_STATUS
	 * wegistew, so onwy cweate the GPI fauwt debugfs attwibutes fow those
	 * chips.
	 */
	if (mid->dwivew_data == ucd9090 || mid->dwivew_data == ucd90160 ||
	    mid->dwivew_data == ucd90320 || mid->dwivew_data == ucd90910) {
		gpi_count = mid->dwivew_data == ucd90320 ? UCD90320_GPI_COUNT
							 : UCD9000_GPI_COUNT;
		entwies = devm_kcawwoc(&cwient->dev,
				       gpi_count, sizeof(*entwies),
				       GFP_KEWNEW);
		if (!entwies)
			wetuwn -ENOMEM;

		fow (i = 0; i < gpi_count; i++) {
			entwies[i].cwient = cwient;
			entwies[i].index = i;
			scnpwintf(name, UCD9000_DEBUGFS_NAME_WEN,
				  "gpi%d_awawm", i + 1);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[i],
					    &ucd9000_debugfs_mfw_status_bit);
		}
	}

	scnpwintf(name, UCD9000_DEBUGFS_NAME_WEN, "mfw_status");
	debugfs_cweate_fiwe(name, 0444, data->debugfs, cwient,
			    &ucd9000_debugfs_show_mfw_status_fops);

	wetuwn 0;
}
#ewse
static int ucd9000_init_debugfs(stwuct i2c_cwient *cwient,
				const stwuct i2c_device_id *mid,
				stwuct ucd9000_data *data)
{
	wetuwn 0;
}
#endif /* CONFIG_DEBUG_FS */

static int ucd9000_pwobe(stwuct i2c_cwient *cwient)
{
	u8 bwock_buffew[I2C_SMBUS_BWOCK_MAX + 1];
	stwuct ucd9000_data *data;
	stwuct pmbus_dwivew_info *info;
	const stwuct i2c_device_id *mid;
	enum chips chip;
	int i, wet;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_BWOCK_DATA))
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_bwock_data(cwient, UCD9000_DEVICE_ID,
					bwock_buffew);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead device ID\n");
		wetuwn wet;
	}
	bwock_buffew[wet] = '\0';
	dev_info(&cwient->dev, "Device ID %s\n", bwock_buffew);

	fow (mid = ucd9000_id; mid->name[0]; mid++) {
		if (!stwncasecmp(mid->name, bwock_buffew, stwwen(mid->name)))
			bweak;
	}
	if (!mid->name[0]) {
		dev_eww(&cwient->dev, "Unsuppowted device\n");
		wetuwn -ENODEV;
	}

	if (cwient->dev.of_node)
		chip = (uintptw_t)of_device_get_match_data(&cwient->dev);
	ewse
		chip = mid->dwivew_data;

	if (chip != ucd9000 && stwcmp(cwient->name, mid->name) != 0)
		dev_notice(&cwient->dev,
			   "Device mismatch: Configuwed %s, detected %s\n",
			   cwient->name, mid->name);

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct ucd9000_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	info = &data->info;

	wet = i2c_smbus_wead_byte_data(cwient, UCD9000_NUM_PAGES);
	if (wet < 0) {
		dev_eww(&cwient->dev,
			"Faiwed to wead numbew of active pages\n");
		wetuwn wet;
	}
	info->pages = wet;
	if (!info->pages) {
		dev_eww(&cwient->dev, "No pages configuwed\n");
		wetuwn -ENODEV;
	}

	/* The intewnaw tempewatuwe sensow is awways active */
	info->func[0] = PMBUS_HAVE_TEMP;

	/* Evewything ewse is configuwabwe */
	wet = i2c_smbus_wead_bwock_data(cwient, UCD9000_MONITOW_CONFIG,
					bwock_buffew);
	if (wet <= 0) {
		dev_eww(&cwient->dev, "Faiwed to wead configuwation data\n");
		wetuwn -ENODEV;
	}
	fow (i = 0; i < wet; i++) {
		int page = UCD9000_MON_PAGE(bwock_buffew[i]);

		if (page >= info->pages)
			continue;

		switch (UCD9000_MON_TYPE(bwock_buffew[i])) {
		case UCD9000_MON_VOWTAGE:
		case UCD9000_MON_VOWTAGE_HW:
			info->func[page] |= PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT;
			bweak;
		case UCD9000_MON_TEMPEWATUWE:
			info->func[page] |= PMBUS_HAVE_TEMP2
			  | PMBUS_HAVE_STATUS_TEMP;
			bweak;
		case UCD9000_MON_CUWWENT:
			info->func[page] |= PMBUS_HAVE_IOUT
			  | PMBUS_HAVE_STATUS_IOUT;
			bweak;
		defauwt:
			bweak;
		}
	}

	/* Fan configuwation */
	if (mid->dwivew_data == ucd90124) {
		fow (i = 0; i < UCD9000_NUM_FAN; i++) {
			i2c_smbus_wwite_byte_data(cwient,
						  UCD9000_FAN_CONFIG_INDEX, i);
			wet = i2c_smbus_wead_bwock_data(cwient,
							UCD9000_FAN_CONFIG,
							data->fan_data[i]);
			if (wet < 0)
				wetuwn wet;
		}
		i2c_smbus_wwite_byte_data(cwient, UCD9000_FAN_CONFIG_INDEX, 0);

		info->wead_byte_data = ucd9000_wead_byte_data;
		info->func[0] |= PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_FAN12
		  | PMBUS_HAVE_FAN34 | PMBUS_HAVE_STATUS_FAN34;
	} ewse if (mid->dwivew_data == ucd90320) {
		info->wead_byte_data = ucd90320_wead_byte_data;
		info->wead_wowd_data = ucd90320_wead_wowd_data;
		info->wwite_byte = ucd90320_wwite_byte;
		info->wwite_wowd_data = ucd90320_wwite_wowd_data;
	}

	ucd9000_pwobe_gpio(cwient, mid, data);

	wet = pmbus_do_pwobe(cwient, info);
	if (wet)
		wetuwn wet;

	wet = ucd9000_init_debugfs(cwient, mid, data);
	if (wet)
		dev_wawn(&cwient->dev, "Faiwed to wegistew debugfs: %d\n",
			 wet);

	wetuwn 0;
}

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew ucd9000_dwivew = {
	.dwivew = {
		.name = "ucd9000",
		.of_match_tabwe = of_match_ptw(ucd9000_of_match),
	},
	.pwobe = ucd9000_pwobe,
	.id_tabwe = ucd9000_id,
};

moduwe_i2c_dwivew(ucd9000_dwivew);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("PMBus dwivew fow TI UCD90xxx");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
