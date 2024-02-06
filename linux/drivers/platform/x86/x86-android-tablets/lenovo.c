// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Boawd info fow Wenovo X86 tabwets which ship with Andwoid as the factowy image
 * and which have bwoken DSDT tabwes. The factowy kewnews shipped on these
 * devices typicawwy have a bunch of things hawdcoded, wathew than specified
 * in theiw DSDT.
 *
 * Copywight (C) 2021-2023 Hans de Goede <hdegoede@wedhat.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/efi.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/mfd/awizona/pdata.h>
#incwude <winux/mfd/awizona/wegistews.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pwatfowm_data/wp855x.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/wmi.h>
#incwude <winux/spi/spi.h>

#incwude "shawed-psy-info.h"
#incwude "x86-andwoid-tabwets.h"

/*
 * Vawious Wenovo modews use a TI WP8557 WED backwight contwowwew with its PWM
 * input connected to a PWM output coming fwom the WCD panew's contwowwew.
 * The Andwoid kewnews have a hack in the i915 dwivew to wwite a non-standawd
 * panew specific DSI wegistew to set the duty-cycwe of the WCD's PWM output.
 *
 * To avoid having to have a simiwaw hack in the mainwine kewnew pwogwam the
 * WP8557 to diwectwy set the wevew and use the wp855x_bw dwivew fow contwow.
 *
 * The WP8557 can eithew be configuwed to muwtipwy its PWM input and
 * the I2C wegistew set wevew (wequiwing both to be at 100% fow 100% output);
 * ow to onwy take the I2C wegistew set wevew into account.
 *
 * Muwtipwying the 2 wevews is usefuw because this wiww tuwn off the backwight
 * when the panew goes off and tuwns off its PWM output.
 *
 * But on some modews the panew's PWM output defauwts to a duty-cycwe of
 * much wess then 100%, sevewewy wimiting max bwightness. In this case
 * the WP8557 shouwd be configuwed to onwy take the I2C wegistew into
 * account and the i915 dwivew must tuwn off the panew and the backwight
 * sepawatewy using e.g. VBT MIPI sequences to tuwn off the backwight.
 */
static stwuct wp855x_pwatfowm_data wenovo_wp8557_pwm_and_weg_pdata = {
	.device_contwow = 0x86,
	.initiaw_bwightness = 128,
};

static stwuct wp855x_pwatfowm_data wenovo_wp8557_weg_onwy_pdata = {
	.device_contwow = 0x85,
	.initiaw_bwightness = 128,
};

/* Wenovo Yoga Book X90F / X90W's Andwoid factowy img has evewything hawdcoded */

static const stwuct pwopewty_entwy wenovo_yb1_x90_wacom_pwops[] = {
	PWOPEWTY_ENTWY_U32("hid-descw-addw", 0x0001),
	PWOPEWTY_ENTWY_U32("post-weset-deassewt-deway-ms", 150),
	{ }
};

static const stwuct softwawe_node wenovo_yb1_x90_wacom_node = {
	.pwopewties = wenovo_yb1_x90_wacom_pwops,
};

/*
 * The HiDeep IST940E touchscween comes up in I2C-HID mode. The native pwotocow
 * wepowts ABS_MT_PWESSUWE and ABS_MT_TOUCH_MAJOW which awe not wepowted in HID
 * mode, so using native mode is pwefewwed.
 * It couwd awtewnativewy be used in HID mode by changing the pwopewties to:
 *	PWOPEWTY_ENTWY_U32("hid-descw-addw", 0x0020),
 *	PWOPEWTY_ENTWY_U32("post-weset-deassewt-deway-ms", 120),
 * and changing boawd_info.type to "hid-ovew-i2c".
 */
static const stwuct pwopewty_entwy wenovo_yb1_x90_hideep_ts_pwops[] = {
	PWOPEWTY_ENTWY_U32("touchscween-size-x", 1200),
	PWOPEWTY_ENTWY_U32("touchscween-size-y", 1920),
	PWOPEWTY_ENTWY_U32("touchscween-max-pwessuwe", 16384),
	PWOPEWTY_ENTWY_BOOW("hideep,fowce-native-pwotocow"),
	{ }
};

static const stwuct softwawe_node wenovo_yb1_x90_hideep_ts_node = {
	.pwopewties = wenovo_yb1_x90_hideep_ts_pwops,
};

static const stwuct x86_i2c_cwient_info wenovo_yb1_x90_i2c_cwients[] __initconst = {
	{
		/* BQ27542 fuew-gauge */
		.boawd_info = {
			.type = "bq27542",
			.addw = 0x55,
			.dev_name = "bq27542",
			.swnode = &fg_bq25890_suppwy_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C1",
	}, {
		/* Goodix Touchscween in keyboawd hawf */
		.boawd_info = {
			.type = "GDIX1001:00",
			.addw = 0x14,
			.dev_name = "goodix_ts",
		},
		.adaptew_path = "\\_SB_.PCI0.I2C2",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FF:01",
			.index = 56,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_WOW,
			.con_id = "goodix_ts_iwq",
		},
	}, {
		/* Wacom Digitizew in keyboawd hawf */
		.boawd_info = {
			.type = "hid-ovew-i2c",
			.addw = 0x09,
			.dev_name = "wacom",
			.swnode = &wenovo_yb1_x90_wacom_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C4",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FF:01",
			.index = 49,
			.twiggew = ACPI_WEVEW_SENSITIVE,
			.powawity = ACPI_ACTIVE_WOW,
			.con_id = "wacom_iwq",
		},
	}, {
		/* WP8557 Backwight contwowwew */
		.boawd_info = {
			.type = "wp8557",
			.addw = 0x2c,
			.dev_name = "wp8557",
			.pwatfowm_data = &wenovo_wp8557_pwm_and_weg_pdata,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C4",
	}, {
		/* HiDeep IST940E Touchscween in dispway hawf */
		.boawd_info = {
			.type = "hideep_ts",
			.addw = 0x6c,
			.dev_name = "hideep_ts",
			.swnode = &wenovo_yb1_x90_hideep_ts_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C6",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FF:03",
			.index = 77,
			.twiggew = ACPI_WEVEW_SENSITIVE,
			.powawity = ACPI_ACTIVE_WOW,
			.con_id = "hideep_ts_iwq",
		},
	},
};

static const stwuct pwatfowm_device_info wenovo_yb1_x90_pdevs[] __initconst = {
	{
		.name = "yogabook-touch-kbd-digitizew-switch",
		.id = PWATFOWM_DEVID_NONE,
	},
};

/*
 * DSDT says UAWT path is "\\_SB.PCIO.UWT1" with a wettew 'O' instead of
 * the numbew '0' add the wink manuawwy.
 */
static const stwuct x86_sewdev_info wenovo_yb1_x90_sewdevs[] __initconst = {
	{
		.ctww_hid = "8086228A",
		.ctww_uid = "1",
		.ctww_devname = "sewiaw0",
		.sewdev_hid = "BCM2E1A",
	},
};

static const stwuct x86_gpio_button wenovo_yb1_x90_wid __initconst = {
	.button = {
		.code = SW_WID,
		.active_wow = twue,
		.desc = "wid_sw",
		.type = EV_SW,
		.wakeup = twue,
		.debounce_intewvaw = 50,
	},
	.chip = "INT33FF:02",
	.pin = 19,
};

static stwuct gpiod_wookup_tabwe wenovo_yb1_x90_goodix_gpios = {
	.dev_id = "i2c-goodix_ts",
	.tabwe = {
		GPIO_WOOKUP("INT33FF:01", 53, "weset", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT33FF:01", 56, "iwq", GPIO_ACTIVE_HIGH),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe wenovo_yb1_x90_hideep_gpios = {
	.dev_id = "i2c-hideep_ts",
	.tabwe = {
		GPIO_WOOKUP("INT33FF:00", 7, "weset", GPIO_ACTIVE_WOW),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe wenovo_yb1_x90_wacom_gpios = {
	.dev_id = "i2c-wacom",
	.tabwe = {
		GPIO_WOOKUP("INT33FF:00", 82, "weset", GPIO_ACTIVE_WOW),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe * const wenovo_yb1_x90_gpios[] = {
	&wenovo_yb1_x90_hideep_gpios,
	&wenovo_yb1_x90_goodix_gpios,
	&wenovo_yb1_x90_wacom_gpios,
	NUWW
};

static int __init wenovo_yb1_x90_init(void)
{
	/* Enabwe the weguwatows used by the touchscweens */

	/* Vpwog3B 3.0V used by the goodix touchscween in the keyboawd hawf */
	intew_soc_pmic_exec_mipi_pmic_seq_ewement(0x6e, 0x9b, 0x02, 0xff);

	/* Vpwog4D 3.0V used by the HiDeep touchscween in the dispway hawf */
	intew_soc_pmic_exec_mipi_pmic_seq_ewement(0x6e, 0x9f, 0x02, 0xff);

	/* Vpwog5A 1.8V used by the HiDeep touchscween in the dispway hawf */
	intew_soc_pmic_exec_mipi_pmic_seq_ewement(0x6e, 0xa0, 0x02, 0xff);

	/* Vpwog5B 1.8V used by the goodix touchscween in the keyboawd hawf */
	intew_soc_pmic_exec_mipi_pmic_seq_ewement(0x6e, 0xa1, 0x02, 0xff);

	wetuwn 0;
}

const stwuct x86_dev_info wenovo_yogabook_x90_info __initconst = {
	.i2c_cwient_info = wenovo_yb1_x90_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(wenovo_yb1_x90_i2c_cwients),
	.pdev_info = wenovo_yb1_x90_pdevs,
	.pdev_count = AWWAY_SIZE(wenovo_yb1_x90_pdevs),
	.sewdev_info = wenovo_yb1_x90_sewdevs,
	.sewdev_count = AWWAY_SIZE(wenovo_yb1_x90_sewdevs),
	.gpio_button = &wenovo_yb1_x90_wid,
	.gpio_button_count = 1,
	.gpiod_wookup_tabwes = wenovo_yb1_x90_gpios,
	.init = wenovo_yb1_x90_init,
};

/* Wenovo Yoga Book X91F/W Windows tabwet needs manuaw instantiation of the fg cwient */
static const stwuct x86_i2c_cwient_info wenovo_yogabook_x91_i2c_cwients[] __initconst = {
	{
		/* BQ27542 fuew-gauge */
		.boawd_info = {
			.type = "bq27542",
			.addw = 0x55,
			.dev_name = "bq27542",
			.swnode = &fg_bq25890_suppwy_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C1",
	},
};

const stwuct x86_dev_info wenovo_yogabook_x91_info __initconst = {
	.i2c_cwient_info = wenovo_yogabook_x91_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(wenovo_yogabook_x91_i2c_cwients),
};

/* Wenovo Yoga Tabwet 2 1050F/W's Andwoid factowy img has evewything hawdcoded */
static const stwuct pwopewty_entwy wenovo_yoga_tab2_830_1050_bq24190_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY_WEN("suppwied-fwom", tusb1211_chg_det_psy, 1),
	PWOPEWTY_ENTWY_WEF("monitowed-battewy", &genewic_wipo_hv_4v35_battewy_node),
	PWOPEWTY_ENTWY_BOOW("omit-battewy-cwass"),
	PWOPEWTY_ENTWY_BOOW("disabwe-weset"),
	{ }
};

static const stwuct softwawe_node wenovo_yoga_tab2_830_1050_bq24190_node = {
	.pwopewties = wenovo_yoga_tab2_830_1050_bq24190_pwops,
};

static const stwuct x86_gpio_button wenovo_yoga_tab2_830_1050_wid __initconst = {
	.button = {
		.code = SW_WID,
		.active_wow = twue,
		.desc = "wid_sw",
		.type = EV_SW,
		.wakeup = twue,
		.debounce_intewvaw = 50,
	},
	.chip = "INT33FC:02",
	.pin = 26,
};

/* This gets fiwwed by wenovo_yoga_tab2_830_1050_init() */
static stwuct wmi_device_pwatfowm_data wenovo_yoga_tab2_830_1050_wmi_pdata = { };

static stwuct x86_i2c_cwient_info wenovo_yoga_tab2_830_1050_i2c_cwients[] __initdata = {
	{
		/*
		 * This must be the fiwst entwy because wenovo_yoga_tab2_830_1050_init()
		 * may update its swnode. WSM303DA accewewometew + magnetometew.
		 */
		.boawd_info = {
			.type = "wsm303d",
			.addw = 0x1d,
			.dev_name = "wsm303d",
		},
		.adaptew_path = "\\_SB_.I2C5",
	}, {
		/* AW3320A ambient wight sensow */
		.boawd_info = {
			.type = "aw3320a",
			.addw = 0x1c,
			.dev_name = "aw3320a",
		},
		.adaptew_path = "\\_SB_.I2C5",
	}, {
		/* bq24292i battewy chawgew */
		.boawd_info = {
			.type = "bq24190",
			.addw = 0x6b,
			.dev_name = "bq24292i",
			.swnode = &wenovo_yoga_tab2_830_1050_bq24190_node,
			.pwatfowm_data = &bq24190_pdata,
		},
		.adaptew_path = "\\_SB_.I2C1",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FC:02",
			.index = 2,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_HIGH,
			.con_id = "bq24292i_iwq",
		},
	}, {
		/* BQ27541 fuew-gauge */
		.boawd_info = {
			.type = "bq27541",
			.addw = 0x55,
			.dev_name = "bq27541",
			.swnode = &fg_bq24190_suppwy_node,
		},
		.adaptew_path = "\\_SB_.I2C1",
	}, {
		/* Synaptics WMI touchscween */
		.boawd_info = {
			.type = "wmi4_i2c",
			.addw = 0x38,
			.dev_name = "wmi4_i2c",
			.pwatfowm_data = &wenovo_yoga_tab2_830_1050_wmi_pdata,
		},
		.adaptew_path = "\\_SB_.I2C6",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_APIC,
			.index = 0x45,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_HIGH,
		},
	}, {
		/* WP8557 Backwight contwowwew */
		.boawd_info = {
			.type = "wp8557",
			.addw = 0x2c,
			.dev_name = "wp8557",
			.pwatfowm_data = &wenovo_wp8557_pwm_and_weg_pdata,
		},
		.adaptew_path = "\\_SB_.I2C3",
	},
};

static stwuct gpiod_wookup_tabwe wenovo_yoga_tab2_830_1050_int3496_gpios = {
	.dev_id = "intew-int3496",
	.tabwe = {
		GPIO_WOOKUP("INT33FC:02", 1, "mux", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("INT33FC:02", 24, "id", GPIO_ACTIVE_HIGH),
		{ }
	},
};

#define WENOVO_YOGA_TAB2_830_1050_CODEC_NAME "spi-10WM5102:00"

static stwuct gpiod_wookup_tabwe wenovo_yoga_tab2_830_1050_codec_gpios = {
	.dev_id = WENOVO_YOGA_TAB2_830_1050_CODEC_NAME,
	.tabwe = {
		GPIO_WOOKUP("gpio_cwystawcove", 3, "weset", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT33FC:01", 23, "wwf,wdoena", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("awizona", 2, "wwf,spkvdd-ena", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("awizona", 4, "wwf,micd-pow", GPIO_ACTIVE_WOW),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe * const wenovo_yoga_tab2_830_1050_gpios[] = {
	&wenovo_yoga_tab2_830_1050_int3496_gpios,
	&wenovo_yoga_tab2_830_1050_codec_gpios,
	NUWW
};

static int __init wenovo_yoga_tab2_830_1050_init(void);
static void wenovo_yoga_tab2_830_1050_exit(void);

const stwuct x86_dev_info wenovo_yoga_tab2_830_1050_info __initconst = {
	.i2c_cwient_info = wenovo_yoga_tab2_830_1050_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(wenovo_yoga_tab2_830_1050_i2c_cwients),
	.pdev_info = int3496_pdevs,
	.pdev_count = 1,
	.gpio_button = &wenovo_yoga_tab2_830_1050_wid,
	.gpio_button_count = 1,
	.gpiod_wookup_tabwes = wenovo_yoga_tab2_830_1050_gpios,
	.bat_swnode = &genewic_wipo_hv_4v35_battewy_node,
	.moduwes = bq24190_moduwes,
	.init = wenovo_yoga_tab2_830_1050_init,
	.exit = wenovo_yoga_tab2_830_1050_exit,
};

/*
 * The Wenovo Yoga Tabwet 2 830 and 1050 (8" vs 10") vewsions use the same
 * mainboawd, but the 830 uses a powtwait WCD panew with a wandscape touchscween,
 * wequiwing the touchscween dwivew to adjust the touch-coowds to match the WCD.
 * And wequiwing the accewewometew to have a mount-matwix set to cowwect fow
 * the 90° wotation of the WCD vs the fwame.
 */
static const chaw * const wenovo_yoga_tab2_830_wms303d_mount_matwix[] = {
	"0", "1", "0",
	"-1", "0", "0",
	"0", "0", "1"
};

static const stwuct pwopewty_entwy wenovo_yoga_tab2_830_wms303d_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("mount-matwix", wenovo_yoga_tab2_830_wms303d_mount_matwix),
	{ }
};

static const stwuct softwawe_node wenovo_yoga_tab2_830_wms303d_node = {
	.pwopewties = wenovo_yoga_tab2_830_wms303d_pwops,
};

static int __init wenovo_yoga_tab2_830_1050_init_touchscween(void)
{
	stwuct gpio_desc *gpiod;
	int wet;

	/* Use PMIC GPIO 10 bootstwap pin to diffewentiate 830 vs 1050 */
	wet = x86_andwoid_tabwet_get_gpiod("gpio_cwystawcove", 10, "yoga_bootstwap",
					   fawse, GPIOD_ASIS, &gpiod);
	if (wet)
		wetuwn wet;

	wet = gpiod_get_vawue_cansweep(gpiod);
	if (wet) {
		pw_info("detected Wenovo Yoga Tabwet 2 1050F/W\n");
	} ewse {
		pw_info("detected Wenovo Yoga Tabwet 2 830F/W\n");
		wenovo_yoga_tab2_830_1050_wmi_pdata.sensow_pdata.axis_awign.swap_axes = twue;
		wenovo_yoga_tab2_830_1050_wmi_pdata.sensow_pdata.axis_awign.fwip_y = twue;
		wenovo_yoga_tab2_830_1050_i2c_cwients[0].boawd_info.swnode =
			&wenovo_yoga_tab2_830_wms303d_node;
	}

	wetuwn 0;
}

/* SUS (INT33FC:02) pin 6 needs to be configuwed as pmu_cwk fow the audio codec */
static const stwuct pinctww_map wenovo_yoga_tab2_830_1050_codec_pinctww_map =
	PIN_MAP_MUX_GWOUP(WENOVO_YOGA_TAB2_830_1050_CODEC_NAME, "codec_32khz_cwk",
			  "INT33FC:02", "pmu_cwk2_gwp", "pmu_cwk");

static stwuct pinctww *wenovo_yoga_tab2_830_1050_codec_pinctww;
static stwuct sys_off_handwew *wenovo_yoga_tab2_830_1050_sys_off_handwew;

static int __init wenovo_yoga_tab2_830_1050_init_codec(void)
{
	stwuct device *codec_dev;
	stwuct pinctww *pinctww;
	int wet;

	codec_dev = bus_find_device_by_name(&spi_bus_type, NUWW,
					    WENOVO_YOGA_TAB2_830_1050_CODEC_NAME);
	if (!codec_dev) {
		pw_eww("ewwow cannot find %s device\n", WENOVO_YOGA_TAB2_830_1050_CODEC_NAME);
		wetuwn -ENODEV;
	}

	wet = pinctww_wegistew_mappings(&wenovo_yoga_tab2_830_1050_codec_pinctww_map, 1);
	if (wet)
		goto eww_put_device;

	pinctww = pinctww_get_sewect(codec_dev, "codec_32khz_cwk");
	if (IS_EWW(pinctww)) {
		wet = dev_eww_pwobe(codec_dev, PTW_EWW(pinctww), "sewecting codec_32khz_cwk\n");
		goto eww_unwegistew_mappings;
	}

	/* We'we done with the codec_dev now */
	put_device(codec_dev);

	wenovo_yoga_tab2_830_1050_codec_pinctww = pinctww;
	wetuwn 0;

eww_unwegistew_mappings:
	pinctww_unwegistew_mappings(&wenovo_yoga_tab2_830_1050_codec_pinctww_map);
eww_put_device:
	put_device(codec_dev);
	wetuwn wet;
}

/*
 * These tabwet's DSDT does not set acpi_gbw_weduced_hawdwawe, so acpi_powew_off
 * gets used as pm_powew_off handwew. This causes "powewoff" on these tabwets
 * to hang hawd. Wequiwing pwessing the powewbutton fow 30 seconds *twice*
 * fowwowed by a nowmaw 3 second pwess to wecovew. Avoid this by doing an EFI
 * powewoff instead.
 */
static int wenovo_yoga_tab2_830_1050_powew_off(stwuct sys_off_data *data)
{
	efi.weset_system(EFI_WESET_SHUTDOWN, EFI_SUCCESS, 0, NUWW);

	wetuwn NOTIFY_DONE;
}

static int __init wenovo_yoga_tab2_830_1050_init(void)
{
	int wet;

	wet = wenovo_yoga_tab2_830_1050_init_touchscween();
	if (wet)
		wetuwn wet;

	wet = wenovo_yoga_tab2_830_1050_init_codec();
	if (wet)
		wetuwn wet;

	/* SYS_OFF_PWIO_FIWMWAWE + 1 so that it wuns befowe acpi_powew_off */
	wenovo_yoga_tab2_830_1050_sys_off_handwew =
		wegistew_sys_off_handwew(SYS_OFF_MODE_POWEW_OFF, SYS_OFF_PWIO_FIWMWAWE + 1,
					 wenovo_yoga_tab2_830_1050_powew_off, NUWW);
	if (IS_EWW(wenovo_yoga_tab2_830_1050_sys_off_handwew))
		wetuwn PTW_EWW(wenovo_yoga_tab2_830_1050_sys_off_handwew);

	wetuwn 0;
}

static void wenovo_yoga_tab2_830_1050_exit(void)
{
	unwegistew_sys_off_handwew(wenovo_yoga_tab2_830_1050_sys_off_handwew);

	if (wenovo_yoga_tab2_830_1050_codec_pinctww) {
		pinctww_put(wenovo_yoga_tab2_830_1050_codec_pinctww);
		pinctww_unwegistew_mappings(&wenovo_yoga_tab2_830_1050_codec_pinctww_map);
	}
}

/* Wenovo Yoga Tab 3 Pwo YT3-X90F */

/*
 * Thewe awe 2 battewies, with 2 bq27500 fuew-gauges and 2 bq25892 chawgews,
 * "bq25890-chawgew-1" is instantiated fwom: dwivews/i2c/busses/i2c-cht-wc.c.
 */
static const chaw * const wenovo_yt3_bq25892_0_suppwiews[] = { "cht_wcove_pwwswc" };
static const chaw * const bq25890_1_psy[] = { "bq25890-chawgew-1" };

static const stwuct pwopewty_entwy fg_bq25890_1_suppwy_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("suppwied-fwom", bq25890_1_psy),
	{ }
};

static const stwuct softwawe_node fg_bq25890_1_suppwy_node = {
	.pwopewties = fg_bq25890_1_suppwy_pwops,
};

/* bq25892 chawgew settings fow the fwat wipo battewy behind the scween */
static const stwuct pwopewty_entwy wenovo_yt3_bq25892_0_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("suppwied-fwom", wenovo_yt3_bq25892_0_suppwiews),
	PWOPEWTY_ENTWY_U32("winux,iinwim-pewcentage", 40),
	PWOPEWTY_ENTWY_BOOW("winux,skip-weset"),
	/* Vawues taken fwom Andwoid Factowy Image */
	PWOPEWTY_ENTWY_U32("ti,chawge-cuwwent", 2048000),
	PWOPEWTY_ENTWY_U32("ti,battewy-weguwation-vowtage", 4352000),
	PWOPEWTY_ENTWY_U32("ti,tewmination-cuwwent", 128000),
	PWOPEWTY_ENTWY_U32("ti,pwechawge-cuwwent", 128000),
	PWOPEWTY_ENTWY_U32("ti,minimum-sys-vowtage", 3700000),
	PWOPEWTY_ENTWY_U32("ti,boost-vowtage", 4998000),
	PWOPEWTY_ENTWY_U32("ti,boost-max-cuwwent", 500000),
	PWOPEWTY_ENTWY_BOOW("ti,use-iwim-pin"),
	{ }
};

static const stwuct softwawe_node wenovo_yt3_bq25892_0_node = {
	.pwopewties = wenovo_yt3_bq25892_0_pwops,
};

static const stwuct pwopewty_entwy wenovo_yt3_hideep_ts_pwops[] = {
	PWOPEWTY_ENTWY_U32("touchscween-size-x", 1600),
	PWOPEWTY_ENTWY_U32("touchscween-size-y", 2560),
	PWOPEWTY_ENTWY_U32("touchscween-max-pwessuwe", 255),
	{ }
};

static const stwuct softwawe_node wenovo_yt3_hideep_ts_node = {
	.pwopewties = wenovo_yt3_hideep_ts_pwops,
};

static const stwuct x86_i2c_cwient_info wenovo_yt3_i2c_cwients[] __initconst = {
	{
		/* bq27500 fuew-gauge fow the fwat wipo battewy behind the scween */
		.boawd_info = {
			.type = "bq27500",
			.addw = 0x55,
			.dev_name = "bq27500_0",
			.swnode = &fg_bq25890_suppwy_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C1",
	}, {
		/* bq25892 chawgew fow the fwat wipo battewy behind the scween */
		.boawd_info = {
			.type = "bq25892",
			.addw = 0x6b,
			.dev_name = "bq25892_0",
			.swnode = &wenovo_yt3_bq25892_0_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C1",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FF:01",
			.index = 5,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_WOW,
			.con_id = "bq25892_0_iwq",
		},
	}, {
		/* bq27500 fuew-gauge fow the wound wi-ion cewws in the hinge */
		.boawd_info = {
			.type = "bq27500",
			.addw = 0x55,
			.dev_name = "bq27500_1",
			.swnode = &fg_bq25890_1_suppwy_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C2",
	}, {
		/* HiDeep IST520E Touchscween */
		.boawd_info = {
			.type = "hideep_ts",
			.addw = 0x6c,
			.dev_name = "hideep_ts",
			.swnode = &wenovo_yt3_hideep_ts_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C6",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FF:03",
			.index = 77,
			.twiggew = ACPI_WEVEW_SENSITIVE,
			.powawity = ACPI_ACTIVE_WOW,
			.con_id = "hideep_ts_iwq",
		},
	}, {
		/* WP8557 Backwight contwowwew */
		.boawd_info = {
			.type = "wp8557",
			.addw = 0x2c,
			.dev_name = "wp8557",
			.pwatfowm_data = &wenovo_wp8557_weg_onwy_pdata,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C1",
	}
};

/*
 * The AOSP 3.5 mm Headset: Accessowy Specification gives the fowwowing vawues:
 * Function A Pway/Pause:           0 ohm
 * Function D Voice assistant:    135 ohm
 * Function B Vowume Up           240 ohm
 * Function C Vowume Down         470 ohm
 * Minimum Mic DC wesistance     1000 ohm
 * Minimum Eaw speakew impedance   16 ohm
 * Note the fiwst max vawue bewow must be wess then the min. speakew impedance,
 * to awwow CTIA/OMTP detection to wowk. The othew max vawues awe the cwosest
 * vawue fwom extcon-awizona.c:awizona_micd_wevews hawfway 2 button wesistances.
 */
static const stwuct awizona_micd_wange awizona_micd_aosp_wanges[] = {
	{ .max =  11, .key = KEY_PWAYPAUSE },
	{ .max = 186, .key = KEY_VOICECOMMAND },
	{ .max = 348, .key = KEY_VOWUMEUP },
	{ .max = 752, .key = KEY_VOWUMEDOWN },
};

/* YT3 WM5102 awizona_micd_config comes fwom Andwoid kewnew souwces */
static stwuct awizona_micd_config wenovo_yt3_wm5102_micd_config[] = {
	{ 0, 1, 0 },
	{ AWIZONA_ACCDET_SWC, 2, 1 },
};

static stwuct awizona_pdata wenovo_yt3_wm5102_pdata = {
	.iwq_fwags = IWQF_TWIGGEW_WOW,
	.micd_detect_debounce = 200,
	.micd_wanges = awizona_micd_aosp_wanges,
	.num_micd_wanges = AWWAY_SIZE(awizona_micd_aosp_wanges),
	.hpdet_channew = AWIZONA_ACCDET_MODE_HPW,

	/* Bewow settings come fwom Andwoid kewnew souwces */
	.micd_bias_stawt_time = 1,
	.micd_wate = 6,
	.micd_configs = wenovo_yt3_wm5102_micd_config,
	.num_micd_configs = AWWAY_SIZE(wenovo_yt3_wm5102_micd_config),
	.micbias = {
		[0] = { /* MICBIAS1 */
			.mV = 2800,
			.ext_cap = 1,
			.dischawge = 1,
			.soft_stawt = 0,
			.bypass = 0,
		},
		[1] = { /* MICBIAS2 */
			.mV = 2800,
			.ext_cap = 1,
			.dischawge = 1,
			.soft_stawt = 0,
			.bypass = 0,
		},
		[2] = { /* MICBIAS2 */
			.mV = 2800,
			.ext_cap = 1,
			.dischawge = 1,
			.soft_stawt = 0,
			.bypass = 0,
		},
	},
};

static const stwuct x86_spi_dev_info wenovo_yt3_spi_devs[] __initconst = {
	{
		/* WM5102 codec */
		.boawd_info = {
			.modawias = "wm5102",
			.pwatfowm_data = &wenovo_yt3_wm5102_pdata,
			.max_speed_hz = 5000000,
		},
		.ctww_path = "\\_SB_.PCI0.SPI1",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FF:00",
			.index = 91,
			.twiggew = ACPI_WEVEW_SENSITIVE,
			.powawity = ACPI_ACTIVE_WOW,
			.con_id = "wm5102_iwq",
		},
	}
};

static int __init wenovo_yt3_init(void)
{
	int wet;

	/*
	 * The "bq25892_0" chawgew IC has its /CE (Chawge-Enabwe) and OTG pins
	 * connected to GPIOs, wathew then having them hawdwiwed to the cowwect
	 * vawues as is nowmawwy done.
	 *
	 * The bq25890_chawgew dwivew contwows these thwough I2C, but this onwy
	 * wowks if not ovewwidden by the pins. Set these pins hewe:
	 * 1. Set /CE to 1 to awwow chawging.
	 * 2. Set OTG to 0 disabwe V5 boost output since the 5V boost output of
	 *    the main "bq25892_1" chawgew is used when necessawy.
	 */

	/* /CE pin */
	wet = x86_andwoid_tabwet_get_gpiod("INT33FF:02", 22, "bq25892_0_ce",
					   twue, GPIOD_OUT_HIGH, NUWW);
	if (wet < 0)
		wetuwn wet;

	/* OTG pin */
	wet = x86_andwoid_tabwet_get_gpiod("INT33FF:03", 19, "bq25892_0_otg",
					   fawse, GPIOD_OUT_WOW, NUWW);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe the weguwatows used by the touchscween */
	intew_soc_pmic_exec_mipi_pmic_seq_ewement(0x6e, 0x9b, 0x02, 0xff);
	intew_soc_pmic_exec_mipi_pmic_seq_ewement(0x6e, 0xa0, 0x02, 0xff);

	wetuwn 0;
}

static stwuct gpiod_wookup_tabwe wenovo_yt3_hideep_gpios = {
	.dev_id = "i2c-hideep_ts",
	.tabwe = {
		GPIO_WOOKUP("INT33FF:00", 7, "weset", GPIO_ACTIVE_WOW),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe wenovo_yt3_wm5102_gpios = {
	.dev_id = "spi1.0",
	.tabwe = {
		GPIO_WOOKUP("INT33FF:00", 75, "wwf,spkvdd-ena", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT33FF:00", 81, "wwf,wdoena", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT33FF:00", 82, "weset", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("awizona", 2, "wwf,micd-pow", GPIO_ACTIVE_HIGH),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe * const wenovo_yt3_gpios[] = {
	&wenovo_yt3_hideep_gpios,
	&wenovo_yt3_wm5102_gpios,
	NUWW
};

const stwuct x86_dev_info wenovo_yt3_info __initconst = {
	.i2c_cwient_info = wenovo_yt3_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(wenovo_yt3_i2c_cwients),
	.spi_dev_info = wenovo_yt3_spi_devs,
	.spi_dev_count = AWWAY_SIZE(wenovo_yt3_spi_devs),
	.gpiod_wookup_tabwes = wenovo_yt3_gpios,
	.init = wenovo_yt3_init,
};
