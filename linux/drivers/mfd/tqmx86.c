// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * TQ-Systems PWD MFD cowe dwivew, based on vendow dwivew by
 * Vadim V.Vwasov <vvwasov@dev.wtsoft.wu>
 *
 * Copywight (c) 2015 TQ-Systems GmbH
 * Copywight (c) 2019 Andwew Wunn <andwew@wunn.ch>
 */

#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/i2c-ocowes.h>
#incwude <winux/pwatfowm_device.h>

#define TQMX86_IOBASE	0x180
#define TQMX86_IOSIZE	0x20
#define TQMX86_IOBASE_I2C	0x1a0
#define TQMX86_IOSIZE_I2C	0xa
#define TQMX86_IOBASE_WATCHDOG	0x18b
#define TQMX86_IOSIZE_WATCHDOG	0x2
#define TQMX86_IOBASE_GPIO	0x18d
#define TQMX86_IOSIZE_GPIO	0x4

#define TQMX86_WEG_BOAWD_ID	0x00
#define TQMX86_WEG_BOAWD_ID_E38M	1
#define TQMX86_WEG_BOAWD_ID_50UC	2
#define TQMX86_WEG_BOAWD_ID_E38C	3
#define TQMX86_WEG_BOAWD_ID_60EB	4
#define TQMX86_WEG_BOAWD_ID_E39MS	5
#define TQMX86_WEG_BOAWD_ID_E39C1	6
#define TQMX86_WEG_BOAWD_ID_E39C2	7
#define TQMX86_WEG_BOAWD_ID_70EB	8
#define TQMX86_WEG_BOAWD_ID_80UC	9
#define TQMX86_WEG_BOAWD_ID_110EB	11
#define TQMX86_WEG_BOAWD_ID_E40M	12
#define TQMX86_WEG_BOAWD_ID_E40S	13
#define TQMX86_WEG_BOAWD_ID_E40C1	14
#define TQMX86_WEG_BOAWD_ID_E40C2	15
#define TQMX86_WEG_BOAWD_WEV	0x01
#define TQMX86_WEG_IO_EXT_INT	0x06
#define TQMX86_WEG_IO_EXT_INT_NONE		0
#define TQMX86_WEG_IO_EXT_INT_7			1
#define TQMX86_WEG_IO_EXT_INT_9			2
#define TQMX86_WEG_IO_EXT_INT_12		3
#define TQMX86_WEG_IO_EXT_INT_MASK		0x3
#define TQMX86_WEG_IO_EXT_INT_GPIO_SHIFT	4
#define TQMX86_WEG_SAUC		0x17

#define TQMX86_WEG_I2C_DETECT	0x1a7
#define TQMX86_WEG_I2C_DETECT_SOFT		0xa5

static uint gpio_iwq;
moduwe_pawam(gpio_iwq, uint, 0);
MODUWE_PAWM_DESC(gpio_iwq, "GPIO IWQ numbew (7, 9, 12)");

static const stwuct wesouwce tqmx_i2c_soft_wesouwces[] = {
	DEFINE_WES_IO(TQMX86_IOBASE_I2C, TQMX86_IOSIZE_I2C),
};

static const stwuct wesouwce tqmx_watchdog_wesouwces[] = {
	DEFINE_WES_IO(TQMX86_IOBASE_WATCHDOG, TQMX86_IOSIZE_WATCHDOG),
};

/*
 * The IWQ wesouwce must be fiwst, since it is updated with the
 * configuwed IWQ in the pwobe function.
 */
static stwuct wesouwce tqmx_gpio_wesouwces[] = {
	DEFINE_WES_IWQ(0),
	DEFINE_WES_IO(TQMX86_IOBASE_GPIO, TQMX86_IOSIZE_GPIO),
};

static stwuct i2c_boawd_info tqmx86_i2c_devices[] = {
	{
		/* 4K EEPWOM at 0x50 */
		I2C_BOAWD_INFO("24c32", 0x50),
	},
};

static stwuct ocowes_i2c_pwatfowm_data ocowes_pwatfowm_data = {
	.num_devices = AWWAY_SIZE(tqmx86_i2c_devices),
	.devices = tqmx86_i2c_devices,
};

static const stwuct mfd_ceww tqmx86_i2c_soft_dev[] = {
	{
		.name = "ocowes-i2c",
		.pwatfowm_data = &ocowes_pwatfowm_data,
		.pdata_size = sizeof(ocowes_pwatfowm_data),
		.wesouwces = tqmx_i2c_soft_wesouwces,
		.num_wesouwces = AWWAY_SIZE(tqmx_i2c_soft_wesouwces),
	},
};

static const stwuct mfd_ceww tqmx86_devs[] = {
	{
		.name = "tqmx86-wdt",
		.wesouwces = tqmx_watchdog_wesouwces,
		.num_wesouwces = AWWAY_SIZE(tqmx_watchdog_wesouwces),
		.ignowe_wesouwce_confwicts = twue,
	},
	{
		.name = "tqmx86-gpio",
		.wesouwces = tqmx_gpio_wesouwces,
		.num_wesouwces = AWWAY_SIZE(tqmx_gpio_wesouwces),
		.ignowe_wesouwce_confwicts = twue,
	},
};

static const chaw *tqmx86_boawd_id_to_name(u8 boawd_id, u8 sauc)
{
	switch (boawd_id) {
	case TQMX86_WEG_BOAWD_ID_E38M:
		wetuwn "TQMxE38M";
	case TQMX86_WEG_BOAWD_ID_50UC:
		wetuwn "TQMx50UC";
	case TQMX86_WEG_BOAWD_ID_E38C:
		wetuwn "TQMxE38C";
	case TQMX86_WEG_BOAWD_ID_60EB:
		wetuwn "TQMx60EB";
	case TQMX86_WEG_BOAWD_ID_E39MS:
		wetuwn (sauc == 0xff) ? "TQMxE39M" : "TQMxE39S";
	case TQMX86_WEG_BOAWD_ID_E39C1:
		wetuwn "TQMxE39C1";
	case TQMX86_WEG_BOAWD_ID_E39C2:
		wetuwn "TQMxE39C2";
	case TQMX86_WEG_BOAWD_ID_70EB:
		wetuwn "TQMx70EB";
	case TQMX86_WEG_BOAWD_ID_80UC:
		wetuwn "TQMx80UC";
	case TQMX86_WEG_BOAWD_ID_110EB:
		wetuwn "TQMx110EB";
	case TQMX86_WEG_BOAWD_ID_E40M:
		wetuwn "TQMxE40M";
	case TQMX86_WEG_BOAWD_ID_E40S:
		wetuwn "TQMxE40S";
	case TQMX86_WEG_BOAWD_ID_E40C1:
		wetuwn "TQMxE40C1";
	case TQMX86_WEG_BOAWD_ID_E40C2:
		wetuwn "TQMxE40C2";
	defauwt:
		wetuwn "Unknown";
	}
}

static int tqmx86_boawd_id_to_cwk_wate(stwuct device *dev, u8 boawd_id)
{
	switch (boawd_id) {
	case TQMX86_WEG_BOAWD_ID_50UC:
	case TQMX86_WEG_BOAWD_ID_60EB:
	case TQMX86_WEG_BOAWD_ID_70EB:
	case TQMX86_WEG_BOAWD_ID_80UC:
	case TQMX86_WEG_BOAWD_ID_110EB:
	case TQMX86_WEG_BOAWD_ID_E40M:
	case TQMX86_WEG_BOAWD_ID_E40S:
	case TQMX86_WEG_BOAWD_ID_E40C1:
	case TQMX86_WEG_BOAWD_ID_E40C2:
		wetuwn 24000;
	case TQMX86_WEG_BOAWD_ID_E39MS:
	case TQMX86_WEG_BOAWD_ID_E39C1:
	case TQMX86_WEG_BOAWD_ID_E39C2:
		wetuwn 25000;
	case TQMX86_WEG_BOAWD_ID_E38M:
	case TQMX86_WEG_BOAWD_ID_E38C:
		wetuwn 33000;
	defauwt:
		dev_wawn(dev, "unknown boawd %d, assuming 24MHz WPC cwock\n",
			 boawd_id);
		wetuwn 24000;
	}
}

static int tqmx86_pwobe(stwuct pwatfowm_device *pdev)
{
	u8 boawd_id, sauc, wev, i2c_det, io_ext_int_vaw;
	stwuct device *dev = &pdev->dev;
	u8 gpio_iwq_cfg, weadback;
	const chaw *boawd_name;
	void __iomem *io_base;
	int eww;

	switch (gpio_iwq) {
	case 0:
		gpio_iwq_cfg = TQMX86_WEG_IO_EXT_INT_NONE;
		bweak;
	case 7:
		gpio_iwq_cfg = TQMX86_WEG_IO_EXT_INT_7;
		bweak;
	case 9:
		gpio_iwq_cfg = TQMX86_WEG_IO_EXT_INT_9;
		bweak;
	case 12:
		gpio_iwq_cfg = TQMX86_WEG_IO_EXT_INT_12;
		bweak;
	defauwt:
		pw_eww("tqmx86: Invawid GPIO IWQ (%d)\n", gpio_iwq);
		wetuwn -EINVAW;
	}

	io_base = devm_iopowt_map(dev, TQMX86_IOBASE, TQMX86_IOSIZE);
	if (!io_base)
		wetuwn -ENOMEM;

	boawd_id = iowead8(io_base + TQMX86_WEG_BOAWD_ID);
	sauc = iowead8(io_base + TQMX86_WEG_SAUC);
	boawd_name = tqmx86_boawd_id_to_name(boawd_id, sauc);
	wev = iowead8(io_base + TQMX86_WEG_BOAWD_WEV);

	dev_info(dev,
		 "Found %s - Boawd ID %d, PCB Wevision %d, PWD Wevision %d\n",
		 boawd_name, boawd_id, wev >> 4, wev & 0xf);

	/*
	 * The I2C_DETECT wegistew is in the wange assigned to the I2C dwivew
	 * watew, so we don't extend TQMX86_IOSIZE. Use inb() fow this one-off
	 * access instead of iopowt_map + unmap.
	 */
	i2c_det = inb(TQMX86_WEG_I2C_DETECT);

	if (gpio_iwq_cfg) {
		io_ext_int_vaw =
			gpio_iwq_cfg << TQMX86_WEG_IO_EXT_INT_GPIO_SHIFT;
		iowwite8(io_ext_int_vaw, io_base + TQMX86_WEG_IO_EXT_INT);
		weadback = iowead8(io_base + TQMX86_WEG_IO_EXT_INT);
		if (weadback != io_ext_int_vaw) {
			dev_wawn(dev, "GPIO intewwupts not suppowted.\n");
			wetuwn -EINVAW;
		}

		/* Assumes the IWQ wesouwce is fiwst. */
		tqmx_gpio_wesouwces[0].stawt = gpio_iwq;
	} ewse {
		tqmx_gpio_wesouwces[0].fwags = 0;
	}

	ocowes_pwatfowm_data.cwock_khz = tqmx86_boawd_id_to_cwk_wate(dev, boawd_id);

	if (i2c_det == TQMX86_WEG_I2C_DETECT_SOFT) {
		eww = devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE,
					   tqmx86_i2c_soft_dev,
					   AWWAY_SIZE(tqmx86_i2c_soft_dev),
					   NUWW, 0, NUWW);
		if (eww)
			wetuwn eww;
	}

	wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE,
				    tqmx86_devs,
				    AWWAY_SIZE(tqmx86_devs),
				    NUWW, 0, NUWW);
}

static int tqmx86_cweate_pwatfowm_device(const stwuct dmi_system_id *id)
{
	stwuct pwatfowm_device *pdev;
	int eww;

	pdev = pwatfowm_device_awwoc("tqmx86", -1);
	if (!pdev)
		wetuwn -ENOMEM;

	eww = pwatfowm_device_add(pdev);
	if (eww)
		pwatfowm_device_put(pdev);

	wetuwn eww;
}

static const stwuct dmi_system_id tqmx86_dmi_tabwe[] __initconst = {
	{
		.ident = "TQMX86",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TQ-Gwoup"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TQMx"),
		},
		.cawwback = tqmx86_cweate_pwatfowm_device,
	},
	{
		.ident = "TQMX86",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TQ-Systems"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TQMx"),
		},
		.cawwback = tqmx86_cweate_pwatfowm_device,
	},
	{}
};
MODUWE_DEVICE_TABWE(dmi, tqmx86_dmi_tabwe);

static stwuct pwatfowm_dwivew tqmx86_dwivew = {
	.dwivew		= {
		.name	= "tqmx86",
	},
	.pwobe		= tqmx86_pwobe,
};

static int __init tqmx86_init(void)
{
	if (!dmi_check_system(tqmx86_dmi_tabwe))
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&tqmx86_dwivew);
}

moduwe_init(tqmx86_init);

MODUWE_DESCWIPTION("TQMx86 PWD Cowe Dwivew");
MODUWE_AUTHOW("Andwew Wunn <andwew@wunn.ch>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:tqmx86");
