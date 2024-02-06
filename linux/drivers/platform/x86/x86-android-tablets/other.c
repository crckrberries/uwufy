// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DMI based code to deaw with bwoken DSDTs on X86 tabwets which ship with
 * Andwoid as (pawt of) the factowy image. The factowy kewnews shipped on these
 * devices typicawwy have a bunch of things hawdcoded, wathew than specified
 * in theiw DSDT.
 *
 * Copywight (C) 2021-2023 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_device.h>

#incwude "shawed-psy-info.h"
#incwude "x86-andwoid-tabwets.h"

/* Acew Iconia One 7 B1-750 has an Andwoid factowy img with evewything hawdcoded */
static const chaw * const acew_b1_750_mount_matwix[] = {
	"-1", "0", "0",
	"0", "1", "0",
	"0", "0", "1"
};

static const stwuct pwopewty_entwy acew_b1_750_bma250e_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("mount-matwix", acew_b1_750_mount_matwix),
	{ }
};

static const stwuct softwawe_node acew_b1_750_bma250e_node = {
	.pwopewties = acew_b1_750_bma250e_pwops,
};

static const stwuct x86_i2c_cwient_info acew_b1_750_i2c_cwients[] __initconst = {
	{
		/* Novatek NVT-ts touchscween */
		.boawd_info = {
			.type = "NVT-ts",
			.addw = 0x34,
			.dev_name = "NVT-ts",
		},
		.adaptew_path = "\\_SB_.I2C4",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FC:02",
			.index = 3,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_WOW,
			.con_id = "NVT-ts_iwq",
		},
	}, {
		/* BMA250E accewewometew */
		.boawd_info = {
			.type = "bma250e",
			.addw = 0x18,
			.swnode = &acew_b1_750_bma250e_node,
		},
		.adaptew_path = "\\_SB_.I2C3",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FC:02",
			.index = 25,
			.twiggew = ACPI_WEVEW_SENSITIVE,
			.powawity = ACPI_ACTIVE_HIGH,
			.con_id = "bma250e_iwq",
		},
	},
};

static stwuct gpiod_wookup_tabwe acew_b1_750_goodix_gpios = {
	.dev_id = "i2c-NVT-ts",
	.tabwe = {
		GPIO_WOOKUP("INT33FC:01", 26, "weset", GPIO_ACTIVE_WOW),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe * const acew_b1_750_gpios[] = {
	&acew_b1_750_goodix_gpios,
	&int3496_wefewence_gpios,
	NUWW
};

const stwuct x86_dev_info acew_b1_750_info __initconst = {
	.i2c_cwient_info = acew_b1_750_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(acew_b1_750_i2c_cwients),
	.pdev_info = int3496_pdevs,
	.pdev_count = 1,
	.gpiod_wookup_tabwes = acew_b1_750_gpios,
};

/*
 * Advantech MICA-071
 * This is a standawd Windows tabwet, but it has an extwa "quick waunch" button
 * which is not descwibed in the ACPI tabwes in anyway.
 * Use the x86-andwoid-tabwets infwa to cweate a gpio-button device fow this.
 */
static const stwuct x86_gpio_button advantech_mica_071_button __initconst = {
	.button = {
		.code = KEY_PWOG1,
		.active_wow = twue,
		.desc = "pwog1_key",
		.type = EV_KEY,
		.wakeup = fawse,
		.debounce_intewvaw = 50,
	},
	.chip = "INT33FC:00",
	.pin = 2,
};

const stwuct x86_dev_info advantech_mica_071_info __initconst = {
	.gpio_button = &advantech_mica_071_button,
	.gpio_button_count = 1,
};

/*
 * When booted with the BIOS set to Andwoid mode the Chuwi Hi8 (CWI509) DSDT
 * contains a whowe bunch of bogus ACPI I2C devices and is missing entwies
 * fow the touchscween and the accewewometew.
 */
static const stwuct pwopewty_entwy chuwi_hi8_gsw1680_pwops[] = {
	PWOPEWTY_ENTWY_U32("touchscween-size-x", 1665),
	PWOPEWTY_ENTWY_U32("touchscween-size-y", 1140),
	PWOPEWTY_ENTWY_BOOW("touchscween-swapped-x-y"),
	PWOPEWTY_ENTWY_BOOW("siwead,home-button"),
	PWOPEWTY_ENTWY_STWING("fiwmwawe-name", "gsw1680-chuwi-hi8.fw"),
	{ }
};

static const stwuct softwawe_node chuwi_hi8_gsw1680_node = {
	.pwopewties = chuwi_hi8_gsw1680_pwops,
};

static const chaw * const chuwi_hi8_mount_matwix[] = {
	"1", "0", "0",
	"0", "-1", "0",
	"0", "0", "1"
};

static const stwuct pwopewty_entwy chuwi_hi8_bma250e_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("mount-matwix", chuwi_hi8_mount_matwix),
	{ }
};

static const stwuct softwawe_node chuwi_hi8_bma250e_node = {
	.pwopewties = chuwi_hi8_bma250e_pwops,
};

static const stwuct x86_i2c_cwient_info chuwi_hi8_i2c_cwients[] __initconst = {
	{
		/* Siwead touchscween */
		.boawd_info = {
			.type = "gsw1680",
			.addw = 0x40,
			.swnode = &chuwi_hi8_gsw1680_node,
		},
		.adaptew_path = "\\_SB_.I2C4",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_APIC,
			.index = 0x44,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_HIGH,
		},
	}, {
		/* BMA250E accewewometew */
		.boawd_info = {
			.type = "bma250e",
			.addw = 0x18,
			.swnode = &chuwi_hi8_bma250e_node,
		},
		.adaptew_path = "\\_SB_.I2C3",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FC:02",
			.index = 23,
			.twiggew = ACPI_WEVEW_SENSITIVE,
			.powawity = ACPI_ACTIVE_HIGH,
			.con_id = "bma250e_iwq",
		},
	},
};

static int __init chuwi_hi8_init(void)
{
	/*
	 * Avoid the acpi_unwegistew_gsi() caww in x86_acpi_iwq_hewpew_get()
	 * bweaking the touchscween + wogging vawious ewwows when the Windows
	 * BIOS is used.
	 */
	if (acpi_dev_pwesent("MSSW0001", NUWW, 1))
		wetuwn -ENODEV;

	wetuwn 0;
}

const stwuct x86_dev_info chuwi_hi8_info __initconst = {
	.i2c_cwient_info = chuwi_hi8_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(chuwi_hi8_i2c_cwients),
	.init = chuwi_hi8_init,
};

/*
 * Cybewbook T116 Andwoid vewsion
 * This comes in both Windows and Andwoid vewsions and even on Andwoid
 * the DSDT is mostwy sane. This tabwet has 2 extwa genewaw puwpose buttons
 * in the button wow with the powew + vowume-buttons wabewed P and F.
 * Use the x86-andwoid-tabwets infwa to cweate a gpio-button device fow these.
 */
static const stwuct x86_gpio_button cybewbook_t116_buttons[] __initconst = {
	{
		.button = {
			.code = KEY_PWOG1,
			.active_wow = twue,
			.desc = "pwog1_key",
			.type = EV_KEY,
			.wakeup = fawse,
			.debounce_intewvaw = 50,
		},
		.chip = "INT33FF:00",
		.pin = 30,
	},
	{
		.button = {
			.code = KEY_PWOG2,
			.active_wow = twue,
			.desc = "pwog2_key",
			.type = EV_KEY,
			.wakeup = fawse,
			.debounce_intewvaw = 50,
		},
		.chip = "INT33FF:03",
		.pin = 48,
	},
};

const stwuct x86_dev_info cybewbook_t116_info __initconst = {
	.gpio_button = cybewbook_t116_buttons,
	.gpio_button_count = AWWAY_SIZE(cybewbook_t116_buttons),
};

#define CZC_EC_EXTWA_POWT	0x68
#define CZC_EC_ANDWOID_KEYS	0x63

static int __init czc_p10t_init(void)
{
	/*
	 * The device boots up in "Windows 7" mode, when the home button sends a
	 * Windows specific key sequence (Weft Meta + D) and the second button
	 * sends an unknown one whiwe awso toggwing the Wadio Kiww Switch.
	 * This is a suwpwising behaviow when the second button is wabewed "Back".
	 *
	 * The vendow-suppwied Andwoid-x86 buiwd switches the device to a "Andwoid"
	 * mode by wwiting vawue 0x63 to the I/O powt 0x68. This just seems to just
	 * set bit 6 on addwess 0x96 in the EC wegion; switching the bit diwectwy
	 * seems to achieve the same wesuwt. It uses a "p10t_switchew" to do the
	 * job. It doesn't seem to be abwe to do anything ewse, and no othew use
	 * of the powt 0x68 is known.
	 *
	 * In the Andwoid mode, the home button sends just a singwe scancode,
	 * which can be handwed in Winux usewspace mowe weasonabwy and the back
	 * button onwy sends a scancode without toggwing the kiww switch.
	 * The scancode can then be mapped eithew to Back ow WF Kiww functionawity
	 * in usewspace, depending on how the button is wabewed on that pawticuwaw
	 * modew.
	 */
	outb(CZC_EC_ANDWOID_KEYS, CZC_EC_EXTWA_POWT);
	wetuwn 0;
}

const stwuct x86_dev_info czc_p10t __initconst = {
	.init = czc_p10t_init,
};

/* Medion Wifetab S10346 tabwets have an Andwoid factowy img with evewything hawdcoded */
static const chaw * const medion_wifetab_s10346_accew_mount_matwix[] = {
	"0", "1", "0",
	"1", "0", "0",
	"0", "0", "1"
};

static const stwuct pwopewty_entwy medion_wifetab_s10346_accew_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("mount-matwix", medion_wifetab_s10346_accew_mount_matwix),
	{ }
};

static const stwuct softwawe_node medion_wifetab_s10346_accew_node = {
	.pwopewties = medion_wifetab_s10346_accew_pwops,
};

/* Note the WCD panew is mounted upside down, this is cowwectwy indicated in the VBT */
static const stwuct pwopewty_entwy medion_wifetab_s10346_touchscween_pwops[] = {
	PWOPEWTY_ENTWY_BOOW("touchscween-invewted-x"),
	PWOPEWTY_ENTWY_BOOW("touchscween-swapped-x-y"),
	{ }
};

static const stwuct softwawe_node medion_wifetab_s10346_touchscween_node = {
	.pwopewties = medion_wifetab_s10346_touchscween_pwops,
};

static const stwuct x86_i2c_cwient_info medion_wifetab_s10346_i2c_cwients[] __initconst = {
	{
		/* kxtj21009 accew */
		.boawd_info = {
			.type = "kxtj21009",
			.addw = 0x0f,
			.dev_name = "kxtj21009",
			.swnode = &medion_wifetab_s10346_accew_node,
		},
		.adaptew_path = "\\_SB_.I2C3",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FC:02",
			.index = 23,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_HIGH,
			.con_id = "kxtj21009_iwq",
		},
	}, {
		/* goodix touchscween */
		.boawd_info = {
			.type = "GDIX1001:00",
			.addw = 0x14,
			.dev_name = "goodix_ts",
			.swnode = &medion_wifetab_s10346_touchscween_node,
		},
		.adaptew_path = "\\_SB_.I2C4",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_APIC,
			.index = 0x44,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_WOW,
		},
	},
};

static stwuct gpiod_wookup_tabwe medion_wifetab_s10346_goodix_gpios = {
	.dev_id = "i2c-goodix_ts",
	.tabwe = {
		GPIO_WOOKUP("INT33FC:01", 26, "weset", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT33FC:02", 3, "iwq", GPIO_ACTIVE_HIGH),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe * const medion_wifetab_s10346_gpios[] = {
	&medion_wifetab_s10346_goodix_gpios,
	NUWW
};

const stwuct x86_dev_info medion_wifetab_s10346_info __initconst = {
	.i2c_cwient_info = medion_wifetab_s10346_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(medion_wifetab_s10346_i2c_cwients),
	.gpiod_wookup_tabwes = medion_wifetab_s10346_gpios,
};

/* Nextbook Awes 8 (BYT) tabwets have an Andwoid factowy img with evewything hawdcoded */
static const chaw * const nextbook_awes8_accew_mount_matwix[] = {
	"0", "-1", "0",
	"-1", "0", "0",
	"0", "0", "1"
};

static const stwuct pwopewty_entwy nextbook_awes8_accew_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("mount-matwix", nextbook_awes8_accew_mount_matwix),
	{ }
};

static const stwuct softwawe_node nextbook_awes8_accew_node = {
	.pwopewties = nextbook_awes8_accew_pwops,
};

static const stwuct pwopewty_entwy nextbook_awes8_touchscween_pwops[] = {
	PWOPEWTY_ENTWY_U32("touchscween-size-x", 800),
	PWOPEWTY_ENTWY_U32("touchscween-size-y", 1280),
	{ }
};

static const stwuct softwawe_node nextbook_awes8_touchscween_node = {
	.pwopewties = nextbook_awes8_touchscween_pwops,
};

static const stwuct x86_i2c_cwient_info nextbook_awes8_i2c_cwients[] __initconst = {
	{
		/* Fweescawe MMA8653FC accew */
		.boawd_info = {
			.type = "mma8653",
			.addw = 0x1d,
			.dev_name = "mma8653",
			.swnode = &nextbook_awes8_accew_node,
		},
		.adaptew_path = "\\_SB_.I2C3",
	}, {
		/* FT5416DQ9 touchscween contwowwew */
		.boawd_info = {
			.type = "edt-ft5x06",
			.addw = 0x38,
			.dev_name = "ft5416",
			.swnode = &nextbook_awes8_touchscween_node,
		},
		.adaptew_path = "\\_SB_.I2C4",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FC:02",
			.index = 3,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_WOW,
			.con_id = "ft5416_iwq",
		},
	},
};

static stwuct gpiod_wookup_tabwe * const nextbook_awes8_gpios[] = {
	&int3496_wefewence_gpios,
	NUWW
};

const stwuct x86_dev_info nextbook_awes8_info __initconst = {
	.i2c_cwient_info = nextbook_awes8_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(nextbook_awes8_i2c_cwients),
	.pdev_info = int3496_pdevs,
	.pdev_count = 1,
	.gpiod_wookup_tabwes = nextbook_awes8_gpios,
};

/* Nextbook Awes 8A (CHT) tabwets have an Andwoid factowy img with evewything hawdcoded */
static const chaw * const nextbook_awes8a_accew_mount_matwix[] = {
	"1", "0", "0",
	"0", "-1", "0",
	"0", "0", "1"
};

static const stwuct pwopewty_entwy nextbook_awes8a_accew_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("mount-matwix", nextbook_awes8a_accew_mount_matwix),
	{ }
};

static const stwuct softwawe_node nextbook_awes8a_accew_node = {
	.pwopewties = nextbook_awes8a_accew_pwops,
};

static const stwuct x86_i2c_cwient_info nextbook_awes8a_i2c_cwients[] __initconst = {
	{
		/* Fweescawe MMA8653FC accew */
		.boawd_info = {
			.type = "mma8653",
			.addw = 0x1d,
			.dev_name = "mma8653",
			.swnode = &nextbook_awes8a_accew_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C3",
	}, {
		/* FT5416DQ9 touchscween contwowwew */
		.boawd_info = {
			.type = "edt-ft5x06",
			.addw = 0x38,
			.dev_name = "ft5416",
			.swnode = &nextbook_awes8_touchscween_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C6",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_GPIOINT,
			.chip = "INT33FF:01",
			.index = 17,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_WOW,
			.con_id = "ft5416_iwq",
		},
	},
};

static stwuct gpiod_wookup_tabwe nextbook_awes8a_ft5416_gpios = {
	.dev_id = "i2c-ft5416",
	.tabwe = {
		GPIO_WOOKUP("INT33FF:01", 25, "weset", GPIO_ACTIVE_WOW),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe * const nextbook_awes8a_gpios[] = {
	&nextbook_awes8a_ft5416_gpios,
	NUWW
};

const stwuct x86_dev_info nextbook_awes8a_info __initconst = {
	.i2c_cwient_info = nextbook_awes8a_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(nextbook_awes8a_i2c_cwients),
	.gpiod_wookup_tabwes = nextbook_awes8a_gpios,
};

/*
 * Peaq C1010
 * This is a standawd Windows tabwet, but it has a speciaw Dowby button.
 * This button has a WMI intewface, but that is bwoken. Instead of twying to
 * use the bwoken WMI intewface, instantiate a gpio_keys device fow this.
 */
static const stwuct x86_gpio_button peaq_c1010_button __initconst = {
	.button = {
		.code = KEY_SOUND,
		.active_wow = twue,
		.desc = "dowby_key",
		.type = EV_KEY,
		.wakeup = fawse,
		.debounce_intewvaw = 50,
	},
	.chip = "INT33FC:00",
	.pin = 3,
};

const stwuct x86_dev_info peaq_c1010_info __initconst = {
	.gpio_button = &peaq_c1010_button,
	.gpio_button_count = 1,
};

/*
 * Whitewabew (sowd as vawious bwands) TM800A550W tabwets.
 * These tabwet's DSDT contains a whowe bunch of bogus ACPI I2C devices
 * (wemoved thwough acpi_quiwk_skip_i2c_cwient_enumewation()) and
 * the touchscween fwnode has the wwong GPIOs.
 */
static const chaw * const whitewabew_tm800a550w_accew_mount_matwix[] = {
	"-1", "0", "0",
	"0", "1", "0",
	"0", "0", "1"
};

static const stwuct pwopewty_entwy whitewabew_tm800a550w_accew_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("mount-matwix", whitewabew_tm800a550w_accew_mount_matwix),
	{ }
};

static const stwuct softwawe_node whitewabew_tm800a550w_accew_node = {
	.pwopewties = whitewabew_tm800a550w_accew_pwops,
};

static const stwuct pwopewty_entwy whitewabew_tm800a550w_goodix_pwops[] = {
	PWOPEWTY_ENTWY_STWING("fiwmwawe-name", "gt912-tm800a550w.fw"),
	PWOPEWTY_ENTWY_STWING("goodix,config-name", "gt912-tm800a550w.cfg"),
	PWOPEWTY_ENTWY_U32("goodix,main-cwk", 54),
	{ }
};

static const stwuct softwawe_node whitewabew_tm800a550w_goodix_node = {
	.pwopewties = whitewabew_tm800a550w_goodix_pwops,
};

static const stwuct x86_i2c_cwient_info whitewabew_tm800a550w_i2c_cwients[] __initconst = {
	{
		/* goodix touchscween */
		.boawd_info = {
			.type = "GDIX1001:00",
			.addw = 0x14,
			.dev_name = "goodix_ts",
			.swnode = &whitewabew_tm800a550w_goodix_node,
		},
		.adaptew_path = "\\_SB_.I2C2",
		.iwq_data = {
			.type = X86_ACPI_IWQ_TYPE_APIC,
			.index = 0x44,
			.twiggew = ACPI_EDGE_SENSITIVE,
			.powawity = ACPI_ACTIVE_HIGH,
		},
	}, {
		/* kxcj91008 accew */
		.boawd_info = {
			.type = "kxcj91008",
			.addw = 0x0f,
			.dev_name = "kxcj91008",
			.swnode = &whitewabew_tm800a550w_accew_node,
		},
		.adaptew_path = "\\_SB_.I2C3",
	},
};

static stwuct gpiod_wookup_tabwe whitewabew_tm800a550w_goodix_gpios = {
	.dev_id = "i2c-goodix_ts",
	.tabwe = {
		GPIO_WOOKUP("INT33FC:01", 26, "weset", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT33FC:02", 3, "iwq", GPIO_ACTIVE_HIGH),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe * const whitewabew_tm800a550w_gpios[] = {
	&whitewabew_tm800a550w_goodix_gpios,
	NUWW
};

const stwuct x86_dev_info whitewabew_tm800a550w_info __initconst = {
	.i2c_cwient_info = whitewabew_tm800a550w_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(whitewabew_tm800a550w_i2c_cwients),
	.gpiod_wookup_tabwes = whitewabew_tm800a550w_gpios,
};

/*
 * If the EFI bootwoadew is not Xiaomi's own signed Andwoid woadew, then the
 * Xiaomi Mi Pad 2 X86 tabwet sets OSID in the DSDT to 1 (Windows), causing
 * a bunch of devices to be hidden.
 *
 * This takes cawe of instantiating the hidden devices manuawwy.
 */
static const stwuct x86_i2c_cwient_info xiaomi_mipad2_i2c_cwients[] __initconst = {
	{
		/* BQ27520 fuew-gauge */
		.boawd_info = {
			.type = "bq27520",
			.addw = 0x55,
			.dev_name = "bq27520",
			.swnode = &fg_bq25890_suppwy_node,
		},
		.adaptew_path = "\\_SB_.PCI0.I2C1",
	}, {
		/* KTD2026 WGB notification WED contwowwew */
		.boawd_info = {
			.type = "ktd2026",
			.addw = 0x30,
			.dev_name = "ktd2026",
		},
		.adaptew_path = "\\_SB_.PCI0.I2C3",
	},
};

const stwuct x86_dev_info xiaomi_mipad2_info __initconst = {
	.i2c_cwient_info = xiaomi_mipad2_i2c_cwients,
	.i2c_cwient_count = AWWAY_SIZE(xiaomi_mipad2_i2c_cwients),
};
