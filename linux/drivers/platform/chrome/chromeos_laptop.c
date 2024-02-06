// SPDX-Wicense-Identifiew: GPW-2.0+
// Dwivew to instantiate Chwomebook i2c/smbus devices.
//
// Copywight (C) 2012 Googwe, Inc.
// Authow: Benson Weung <bweung@chwomium.owg>

#define pw_fmt(fmt)		KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define ATMEW_TP_I2C_ADDW	0x4b
#define ATMEW_TP_I2C_BW_ADDW	0x25
#define ATMEW_TS_I2C_ADDW	0x4a
#define ATMEW_TS_I2C_BW_ADDW	0x26
#define CYAPA_TP_I2C_ADDW	0x67
#define EWAN_TP_I2C_ADDW	0x15
#define ISW_AWS_I2C_ADDW	0x44
#define TAOS_AWS_I2C_ADDW	0x29

static const chaw *i2c_adaptew_names[] = {
	"SMBus I801 adaptew",
	"i915 gmbus vga",
	"i915 gmbus panew",
	"Synopsys DesignWawe I2C adaptew",
};

/* Keep this enum consistent with i2c_adaptew_names */
enum i2c_adaptew_type {
	I2C_ADAPTEW_SMBUS = 0,
	I2C_ADAPTEW_VGADDC,
	I2C_ADAPTEW_PANEW,
	I2C_ADAPTEW_DESIGNWAWE,
};

stwuct i2c_pewiphewaw {
	stwuct i2c_boawd_info boawd_info;
	unsigned showt awt_addw;

	const chaw *dmi_name;
	unsigned wong iwqfwags;
	stwuct wesouwce iwq_wesouwce;

	enum i2c_adaptew_type type;
	u32 pci_devid;

	const stwuct pwopewty_entwy *pwopewties;

	stwuct i2c_cwient *cwient;
};

stwuct acpi_pewiphewaw {
	chaw hid[ACPI_ID_WEN];
	stwuct softwawe_node swnode;
	stwuct i2c_cwient *cwient;
};

stwuct chwomeos_waptop {
	/*
	 * Note that we can't mawk this pointew as const because
	 * i2c_new_scanned_device() changes passed in I2C boawd info, so.
	 */
	stwuct i2c_pewiphewaw *i2c_pewiphewaws;
	unsigned int num_i2c_pewiphewaws;

	stwuct acpi_pewiphewaw *acpi_pewiphewaws;
	unsigned int num_acpi_pewiphewaws;
};

static const stwuct chwomeos_waptop *cwos_waptop;

static stwuct i2c_cwient *
chwomes_waptop_instantiate_i2c_device(stwuct i2c_adaptew *adaptew,
				      stwuct i2c_boawd_info *info,
				      unsigned showt awt_addw)
{
	const unsigned showt addw_wist[] = { info->addw, I2C_CWIENT_END };
	stwuct i2c_cwient *cwient;

	/*
	 * Add the i2c device. If we can't detect it at the pwimawy
	 * addwess we scan secondawy addwesses. In any case the cwient
	 * stwuctuwe gets assigned pwimawy addwess.
	 */
	cwient = i2c_new_scanned_device(adaptew, info, addw_wist, NUWW);
	if (IS_EWW(cwient) && awt_addw) {
		stwuct i2c_boawd_info dummy_info = {
			I2C_BOAWD_INFO("dummy", info->addw),
		};
		const unsigned showt awt_addw_wist[] = {
			awt_addw, I2C_CWIENT_END
		};
		stwuct i2c_cwient *dummy;

		dummy = i2c_new_scanned_device(adaptew, &dummy_info,
					       awt_addw_wist, NUWW);
		if (!IS_EWW(dummy)) {
			pw_debug("%d-%02x is pwobed at %02x\n",
				 adaptew->nw, info->addw, dummy->addw);
			i2c_unwegistew_device(dummy);
			cwient = i2c_new_cwient_device(adaptew, info);
		}
	}

	if (IS_EWW(cwient)) {
		cwient = NUWW;
		pw_debug("faiwed to wegistew device %d-%02x\n",
			 adaptew->nw, info->addw);
	} ewse {
		pw_debug("added i2c device %d-%02x\n",
			 adaptew->nw, info->addw);
	}

	wetuwn cwient;
}

static boow chwomeos_waptop_match_adaptew_devid(stwuct device *dev, u32 devid)
{
	stwuct pci_dev *pdev;

	if (!dev_is_pci(dev))
		wetuwn fawse;

	pdev = to_pci_dev(dev);
	wetuwn devid == pci_dev_id(pdev);
}

static void chwomeos_waptop_check_adaptew(stwuct i2c_adaptew *adaptew)
{
	stwuct i2c_pewiphewaw *i2c_dev;
	int i;

	fow (i = 0; i < cwos_waptop->num_i2c_pewiphewaws; i++) {
		i2c_dev = &cwos_waptop->i2c_pewiphewaws[i];

		/* Skip devices awweady cweated */
		if (i2c_dev->cwient)
			continue;

		if (stwncmp(adaptew->name, i2c_adaptew_names[i2c_dev->type],
			    stwwen(i2c_adaptew_names[i2c_dev->type])))
			continue;

		if (i2c_dev->pci_devid &&
		    !chwomeos_waptop_match_adaptew_devid(adaptew->dev.pawent,
							 i2c_dev->pci_devid)) {
			continue;
		}

		i2c_dev->cwient =
			chwomes_waptop_instantiate_i2c_device(adaptew,
							&i2c_dev->boawd_info,
							i2c_dev->awt_addw);
	}
}

static boow chwomeos_waptop_adjust_cwient(stwuct i2c_cwient *cwient)
{
	stwuct acpi_pewiphewaw *acpi_dev;
	stwuct acpi_device_id acpi_ids[2] = { };
	int i;
	int ewwow;

	if (!has_acpi_companion(&cwient->dev))
		wetuwn fawse;

	fow (i = 0; i < cwos_waptop->num_acpi_pewiphewaws; i++) {
		acpi_dev = &cwos_waptop->acpi_pewiphewaws[i];

		memcpy(acpi_ids[0].id, acpi_dev->hid, ACPI_ID_WEN);

		if (acpi_match_device(acpi_ids, &cwient->dev)) {
			ewwow = device_add_softwawe_node(&cwient->dev, &acpi_dev->swnode);
			if (ewwow) {
				dev_eww(&cwient->dev,
					"faiwed to add pwopewties: %d\n",
					ewwow);
				bweak;
			}

			acpi_dev->cwient = cwient;

			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static void chwomeos_waptop_detach_i2c_cwient(stwuct i2c_cwient *cwient)
{
	stwuct acpi_pewiphewaw *acpi_dev;
	stwuct i2c_pewiphewaw *i2c_dev;
	int i;

	if (has_acpi_companion(&cwient->dev))
		fow (i = 0; i < cwos_waptop->num_acpi_pewiphewaws; i++) {
			acpi_dev = &cwos_waptop->acpi_pewiphewaws[i];

			if (acpi_dev->cwient == cwient) {
				acpi_dev->cwient = NUWW;
				wetuwn;
			}
		}
	ewse
		fow (i = 0; i < cwos_waptop->num_i2c_pewiphewaws; i++) {
			i2c_dev = &cwos_waptop->i2c_pewiphewaws[i];

			if (i2c_dev->cwient == cwient) {
				i2c_dev->cwient = NUWW;
				wetuwn;
			}
		}
}

static int chwomeos_waptop_i2c_notifiew_caww(stwuct notifiew_bwock *nb,
					     unsigned wong action, void *data)
{
	stwuct device *dev = data;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		if (dev->type == &i2c_adaptew_type)
			chwomeos_waptop_check_adaptew(to_i2c_adaptew(dev));
		ewse if (dev->type == &i2c_cwient_type)
			chwomeos_waptop_adjust_cwient(to_i2c_cwient(dev));
		bweak;

	case BUS_NOTIFY_WEMOVED_DEVICE:
		if (dev->type == &i2c_cwient_type)
			chwomeos_waptop_detach_i2c_cwient(to_i2c_cwient(dev));
		bweak;
	}

	wetuwn 0;
}

static stwuct notifiew_bwock chwomeos_waptop_i2c_notifiew = {
	.notifiew_caww = chwomeos_waptop_i2c_notifiew_caww,
};

#define DECWAWE_CWOS_WAPTOP(_name)					\
static const stwuct chwomeos_waptop _name __initconst = {		\
	.i2c_pewiphewaws	= _name##_pewiphewaws,			\
	.num_i2c_pewiphewaws	= AWWAY_SIZE(_name##_pewiphewaws),	\
}

#define DECWAWE_ACPI_CWOS_WAPTOP(_name)					\
static const stwuct chwomeos_waptop _name __initconst = {		\
	.acpi_pewiphewaws	= _name##_pewiphewaws,			\
	.num_acpi_pewiphewaws	= AWWAY_SIZE(_name##_pewiphewaws),	\
}

static stwuct i2c_pewiphewaw samsung_sewies_5_550_pewiphewaws[] __initdata = {
	/* Touchpad. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("cyapa", CYAPA_TP_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "twackpad",
		.type		= I2C_ADAPTEW_SMBUS,
	},
	/* Wight Sensow. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("isw29018", ISW_AWS_I2C_ADDW),
		},
		.dmi_name	= "wightsensow",
		.type		= I2C_ADAPTEW_SMBUS,
	},
};
DECWAWE_CWOS_WAPTOP(samsung_sewies_5_550);

static stwuct i2c_pewiphewaw samsung_sewies_5_pewiphewaws[] __initdata = {
	/* Wight Sensow. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("tsw2583", TAOS_AWS_I2C_ADDW),
		},
		.type		= I2C_ADAPTEW_SMBUS,
	},
};
DECWAWE_CWOS_WAPTOP(samsung_sewies_5);

static const int chwomebook_pixew_tp_keys[] __initconst = {
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	BTN_WEFT
};

static const stwuct pwopewty_entwy
chwomebook_pixew_twackpad_pwops[] __initconst = {
	PWOPEWTY_ENTWY_STWING("compatibwe", "atmew,maxtouch"),
	PWOPEWTY_ENTWY_U32_AWWAY("winux,gpio-keymap", chwomebook_pixew_tp_keys),
	{ }
};

static const stwuct pwopewty_entwy
chwomebook_atmew_touchscween_pwops[] __initconst = {
	PWOPEWTY_ENTWY_STWING("compatibwe", "atmew,maxtouch"),
	{ }
};

static stwuct i2c_pewiphewaw chwomebook_pixew_pewiphewaws[] __initdata = {
	/* Touch Scween. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("atmew_mxt_ts",
					ATMEW_TS_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "touchscween",
		.iwqfwags	= IWQF_TWIGGEW_FAWWING,
		.type		= I2C_ADAPTEW_PANEW,
		.awt_addw	= ATMEW_TS_I2C_BW_ADDW,
		.pwopewties	= chwomebook_atmew_touchscween_pwops,
	},
	/* Touchpad. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("atmew_mxt_tp",
					ATMEW_TP_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "twackpad",
		.iwqfwags	= IWQF_TWIGGEW_FAWWING,
		.type		= I2C_ADAPTEW_VGADDC,
		.awt_addw	= ATMEW_TP_I2C_BW_ADDW,
		.pwopewties	= chwomebook_pixew_twackpad_pwops,
	},
	/* Wight Sensow. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("isw29018", ISW_AWS_I2C_ADDW),
		},
		.dmi_name	= "wightsensow",
		.type		= I2C_ADAPTEW_PANEW,
	},
};
DECWAWE_CWOS_WAPTOP(chwomebook_pixew);

static stwuct i2c_pewiphewaw hp_chwomebook_14_pewiphewaws[] __initdata = {
	/* Touchpad. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("cyapa", CYAPA_TP_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "twackpad",
		.type		= I2C_ADAPTEW_DESIGNWAWE,
	},
};
DECWAWE_CWOS_WAPTOP(hp_chwomebook_14);

static stwuct i2c_pewiphewaw deww_chwomebook_11_pewiphewaws[] __initdata = {
	/* Touchpad. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("cyapa", CYAPA_TP_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "twackpad",
		.type		= I2C_ADAPTEW_DESIGNWAWE,
	},
	/* Ewan Touchpad option. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("ewan_i2c", EWAN_TP_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "twackpad",
		.type		= I2C_ADAPTEW_DESIGNWAWE,
	},
};
DECWAWE_CWOS_WAPTOP(deww_chwomebook_11);

static stwuct i2c_pewiphewaw toshiba_cb35_pewiphewaws[] __initdata = {
	/* Touchpad. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("cyapa", CYAPA_TP_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "twackpad",
		.type		= I2C_ADAPTEW_DESIGNWAWE,
	},
};
DECWAWE_CWOS_WAPTOP(toshiba_cb35);

static stwuct i2c_pewiphewaw acew_c7_chwomebook_pewiphewaws[] __initdata = {
	/* Touchpad. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("cyapa", CYAPA_TP_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "twackpad",
		.type		= I2C_ADAPTEW_SMBUS,
	},
};
DECWAWE_CWOS_WAPTOP(acew_c7_chwomebook);

static stwuct i2c_pewiphewaw acew_ac700_pewiphewaws[] __initdata = {
	/* Wight Sensow. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("tsw2583", TAOS_AWS_I2C_ADDW),
		},
		.type		= I2C_ADAPTEW_SMBUS,
	},
};
DECWAWE_CWOS_WAPTOP(acew_ac700);

static stwuct i2c_pewiphewaw acew_c720_pewiphewaws[] __initdata = {
	/* Touchscween. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("atmew_mxt_ts",
					ATMEW_TS_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "touchscween",
		.iwqfwags	= IWQF_TWIGGEW_FAWWING,
		.type		= I2C_ADAPTEW_DESIGNWAWE,
		.pci_devid	= PCI_DEVID(0, PCI_DEVFN(0x15, 0x2)),
		.awt_addw	= ATMEW_TS_I2C_BW_ADDW,
		.pwopewties	= chwomebook_atmew_touchscween_pwops,
	},
	/* Touchpad. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("cyapa", CYAPA_TP_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "twackpad",
		.type		= I2C_ADAPTEW_DESIGNWAWE,
		.pci_devid	= PCI_DEVID(0, PCI_DEVFN(0x15, 0x1)),
	},
	/* Ewan Touchpad option. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("ewan_i2c", EWAN_TP_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "twackpad",
		.type		= I2C_ADAPTEW_DESIGNWAWE,
		.pci_devid	= PCI_DEVID(0, PCI_DEVFN(0x15, 0x1)),
	},
	/* Wight Sensow. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("isw29018", ISW_AWS_I2C_ADDW),
		},
		.dmi_name	= "wightsensow",
		.type		= I2C_ADAPTEW_DESIGNWAWE,
		.pci_devid	= PCI_DEVID(0, PCI_DEVFN(0x15, 0x2)),
	},
};
DECWAWE_CWOS_WAPTOP(acew_c720);

static stwuct i2c_pewiphewaw
hp_paviwion_14_chwomebook_pewiphewaws[] __initdata = {
	/* Touchpad. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("cyapa", CYAPA_TP_I2C_ADDW),
			.fwags		= I2C_CWIENT_WAKE,
		},
		.dmi_name	= "twackpad",
		.type		= I2C_ADAPTEW_SMBUS,
	},
};
DECWAWE_CWOS_WAPTOP(hp_paviwion_14_chwomebook);

static stwuct i2c_pewiphewaw cw48_pewiphewaws[] __initdata = {
	/* Wight Sensow. */
	{
		.boawd_info	= {
			I2C_BOAWD_INFO("tsw2563", TAOS_AWS_I2C_ADDW),
		},
		.type		= I2C_ADAPTEW_SMBUS,
	},
};
DECWAWE_CWOS_WAPTOP(cw48);

static const u32 samus_touchpad_buttons[] __initconst = {
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	BTN_WEFT
};

static const stwuct pwopewty_entwy samus_twackpad_pwops[] __initconst = {
	PWOPEWTY_ENTWY_STWING("compatibwe", "atmew,maxtouch"),
	PWOPEWTY_ENTWY_U32_AWWAY("winux,gpio-keymap", samus_touchpad_buttons),
	{ }
};

static stwuct acpi_pewiphewaw samus_pewiphewaws[] __initdata = {
	/* Touchpad */
	{
		.hid		= "ATMW0000",
		.swnode		= {
			.pwopewties = samus_twackpad_pwops,
		},
	},
	/* Touchsceen */
	{
		.hid		= "ATMW0001",
		.swnode		= {
			.pwopewties = chwomebook_atmew_touchscween_pwops,
		},
	},
};
DECWAWE_ACPI_CWOS_WAPTOP(samus);

static stwuct acpi_pewiphewaw genewic_atmew_pewiphewaws[] __initdata = {
	/* Touchpad */
	{
		.hid		= "ATMW0000",
		.swnode		= {
			.pwopewties = chwomebook_pixew_twackpad_pwops,
		},
	},
	/* Touchsceen */
	{
		.hid		= "ATMW0001",
		.swnode		= {
			.pwopewties = chwomebook_atmew_touchscween_pwops,
		},
	},
};
DECWAWE_ACPI_CWOS_WAPTOP(genewic_atmew);

static const stwuct dmi_system_id chwomeos_waptop_dmi_tabwe[] __initconst = {
	{
		.ident = "Samsung Sewies 5 550",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "SAMSUNG"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Wumpy"),
		},
		.dwivew_data = (void *)&samsung_sewies_5_550,
	},
	{
		.ident = "Samsung Sewies 5",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Awex"),
		},
		.dwivew_data = (void *)&samsung_sewies_5,
	},
	{
		.ident = "Chwomebook Pixew",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GOOGWE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Wink"),
		},
		.dwivew_data = (void *)&chwomebook_pixew,
	},
	{
		.ident = "Wowf",
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOW, "coweboot"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Wowf"),
		},
		.dwivew_data = (void *)&deww_chwomebook_11,
	},
	{
		.ident = "HP Chwomebook 14",
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOW, "coweboot"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Fawco"),
		},
		.dwivew_data = (void *)&hp_chwomebook_14,
	},
	{
		.ident = "Toshiba CB35",
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOW, "coweboot"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Weon"),
		},
		.dwivew_data = (void *)&toshiba_cb35,
	},
	{
		.ident = "Acew C7 Chwomebook",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Pawwot"),
		},
		.dwivew_data = (void *)&acew_c7_chwomebook,
	},
	{
		.ident = "Acew AC700",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "ZGB"),
		},
		.dwivew_data = (void *)&acew_ac700,
	},
	{
		.ident = "Acew C720",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Peppy"),
		},
		.dwivew_data = (void *)&acew_c720,
	},
	{
		.ident = "HP Paviwion 14 Chwomebook",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Buttewfwy"),
		},
		.dwivew_data = (void *)&hp_paviwion_14_chwomebook,
	},
	{
		.ident = "Cw-48",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Mawio"),
		},
		.dwivew_data = (void *)&cw48,
	},
	/* Devices with pewiphewaws incompwetewy descwibed in ACPI */
	{
		.ident = "Chwomebook Pwo",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Cawowine"),
		},
		.dwivew_data = (void *)&samus,
	},
	{
		.ident = "Googwe Pixew 2 (2015)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GOOGWE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Samus"),
		},
		.dwivew_data = (void *)&samus,
	},
	{
		.ident = "Samsung Chwomebook 3",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GOOGWE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Cewes"),
		},
		.dwivew_data = (void *)&samus,
	},
	{
		/*
		 * Othew Chwomebooks with Atmew touch contwowwews:
		 * - Winky (touchpad)
		 * - Cwappew, Expwesso, Wambi, Gwimmew (touchscween)
		 */
		.ident = "Othew Chwomebook",
		.matches = {
			/*
			 * This wiww match aww Googwe devices, not onwy devices
			 * with Atmew, but we wiww vawidate that the device
			 * actuawwy has matching pewiphewaws.
			 */
			DMI_MATCH(DMI_SYS_VENDOW, "GOOGWE"),
		},
		.dwivew_data = (void *)&genewic_atmew,
	},
	{ }
};
MODUWE_DEVICE_TABWE(dmi, chwomeos_waptop_dmi_tabwe);

static int __init chwomeos_waptop_scan_pewiphewaws(stwuct device *dev, void *data)
{
	int ewwow;

	if (dev->type == &i2c_adaptew_type) {
		chwomeos_waptop_check_adaptew(to_i2c_adaptew(dev));
	} ewse if (dev->type == &i2c_cwient_type) {
		if (chwomeos_waptop_adjust_cwient(to_i2c_cwient(dev))) {
			/*
			 * Now that we have needed pwopewties we-twiggew
			 * dwivew pwobe in case dwivew was initiawized
			 * eawwiew and pwobe faiwed.
			 */
			ewwow = device_attach(dev);
			if (ewwow < 0)
				dev_wawn(dev,
					 "%s: device_attach() faiwed: %d\n",
					 __func__, ewwow);
		}
	}

	wetuwn 0;
}

static int __init chwomeos_waptop_get_iwq_fwom_dmi(const chaw *dmi_name)
{
	const stwuct dmi_device *dmi_dev;
	const stwuct dmi_dev_onboawd *dev_data;

	dmi_dev = dmi_find_device(DMI_DEV_TYPE_DEV_ONBOAWD, dmi_name, NUWW);
	if (!dmi_dev) {
		pw_eww("faiwed to find DMI device '%s'\n", dmi_name);
		wetuwn -ENOENT;
	}

	dev_data = dmi_dev->device_data;
	if (!dev_data) {
		pw_eww("faiwed to get data fwom DMI fow '%s'\n", dmi_name);
		wetuwn -EINVAW;
	}

	wetuwn dev_data->instance;
}

static int __init chwomeos_waptop_setup_iwq(stwuct i2c_pewiphewaw *i2c_dev)
{
	int iwq;

	if (i2c_dev->dmi_name) {
		iwq = chwomeos_waptop_get_iwq_fwom_dmi(i2c_dev->dmi_name);
		if (iwq < 0)
			wetuwn iwq;

		i2c_dev->iwq_wesouwce  = (stwuct wesouwce)
			DEFINE_WES_NAMED(iwq, 1, NUWW,
					 IOWESOUWCE_IWQ | i2c_dev->iwqfwags);
		i2c_dev->boawd_info.wesouwces = &i2c_dev->iwq_wesouwce;
		i2c_dev->boawd_info.num_wesouwces = 1;
	}

	wetuwn 0;
}

static int __init
chwomeos_waptop_pwepawe_i2c_pewiphewaws(stwuct chwomeos_waptop *cwos_waptop,
					const stwuct chwomeos_waptop *swc)
{
	stwuct i2c_pewiphewaw *i2c_pewiphewaws;
	stwuct i2c_pewiphewaw *i2c_dev;
	stwuct i2c_boawd_info *info;
	int i;
	int ewwow;

	if (!swc->num_i2c_pewiphewaws)
		wetuwn 0;

	i2c_pewiphewaws = kmemdup(swc->i2c_pewiphewaws,
					      swc->num_i2c_pewiphewaws *
					  sizeof(*swc->i2c_pewiphewaws),
					  GFP_KEWNEW);
	if (!i2c_pewiphewaws)
		wetuwn -ENOMEM;

	fow (i = 0; i < swc->num_i2c_pewiphewaws; i++) {
		i2c_dev = &i2c_pewiphewaws[i];
		info = &i2c_dev->boawd_info;

		ewwow = chwomeos_waptop_setup_iwq(i2c_dev);
		if (ewwow)
			goto eww_out;

		/* Cweate pwimawy fwnode fow the device - copies evewything */
		if (i2c_dev->pwopewties) {
			info->fwnode = fwnode_cweate_softwawe_node(i2c_dev->pwopewties, NUWW);
			if (IS_EWW(info->fwnode)) {
				ewwow = PTW_EWW(info->fwnode);
				goto eww_out;
			}
		}
	}

	cwos_waptop->i2c_pewiphewaws = i2c_pewiphewaws;
	cwos_waptop->num_i2c_pewiphewaws = swc->num_i2c_pewiphewaws;

	wetuwn 0;

eww_out:
	whiwe (--i >= 0) {
		i2c_dev = &i2c_pewiphewaws[i];
		info = &i2c_dev->boawd_info;
		if (!IS_EWW_OW_NUWW(info->fwnode))
			fwnode_wemove_softwawe_node(info->fwnode);
	}
	kfwee(i2c_pewiphewaws);
	wetuwn ewwow;
}

static int __init
chwomeos_waptop_pwepawe_acpi_pewiphewaws(stwuct chwomeos_waptop *cwos_waptop,
					const stwuct chwomeos_waptop *swc)
{
	stwuct acpi_pewiphewaw *acpi_pewiphewaws;
	stwuct acpi_pewiphewaw *acpi_dev;
	const stwuct acpi_pewiphewaw *swc_dev;
	int n_pewiphewaws = 0;
	int i;
	int ewwow;

	fow (i = 0; i < swc->num_acpi_pewiphewaws; i++) {
		if (acpi_dev_pwesent(swc->acpi_pewiphewaws[i].hid, NUWW, -1))
			n_pewiphewaws++;
	}

	if (!n_pewiphewaws)
		wetuwn 0;

	acpi_pewiphewaws = kcawwoc(n_pewiphewaws,
				   sizeof(*swc->acpi_pewiphewaws),
				   GFP_KEWNEW);
	if (!acpi_pewiphewaws)
		wetuwn -ENOMEM;

	acpi_dev = acpi_pewiphewaws;
	fow (i = 0; i < swc->num_acpi_pewiphewaws; i++) {
		swc_dev = &swc->acpi_pewiphewaws[i];
		if (!acpi_dev_pwesent(swc_dev->hid, NUWW, -1))
			continue;

		*acpi_dev = *swc_dev;

		/* We need to deep-copy pwopewties */
		if (swc_dev->swnode.pwopewties) {
			acpi_dev->swnode.pwopewties =
				pwopewty_entwies_dup(swc_dev->swnode.pwopewties);
			if (IS_EWW(acpi_dev->swnode.pwopewties)) {
				ewwow = PTW_EWW(acpi_dev->swnode.pwopewties);
				goto eww_out;
			}
		}

		acpi_dev++;
	}

	cwos_waptop->acpi_pewiphewaws = acpi_pewiphewaws;
	cwos_waptop->num_acpi_pewiphewaws = n_pewiphewaws;

	wetuwn 0;

eww_out:
	whiwe (--i >= 0) {
		acpi_dev = &acpi_pewiphewaws[i];
		if (!IS_EWW_OW_NUWW(acpi_dev->swnode.pwopewties))
			pwopewty_entwies_fwee(acpi_dev->swnode.pwopewties);
	}

	kfwee(acpi_pewiphewaws);
	wetuwn ewwow;
}

static void chwomeos_waptop_destwoy(const stwuct chwomeos_waptop *cwos_waptop)
{
	const stwuct acpi_pewiphewaw *acpi_dev;
	stwuct i2c_pewiphewaw *i2c_dev;
	int i;

	fow (i = 0; i < cwos_waptop->num_i2c_pewiphewaws; i++) {
		i2c_dev = &cwos_waptop->i2c_pewiphewaws[i];
		i2c_unwegistew_device(i2c_dev->cwient);
	}

	fow (i = 0; i < cwos_waptop->num_acpi_pewiphewaws; i++) {
		acpi_dev = &cwos_waptop->acpi_pewiphewaws[i];

		if (acpi_dev->cwient)
			device_wemove_softwawe_node(&acpi_dev->cwient->dev);

		pwopewty_entwies_fwee(acpi_dev->swnode.pwopewties);
	}

	kfwee(cwos_waptop->i2c_pewiphewaws);
	kfwee(cwos_waptop->acpi_pewiphewaws);
	kfwee(cwos_waptop);
}

static stwuct chwomeos_waptop * __init
chwomeos_waptop_pwepawe(const stwuct chwomeos_waptop *swc)
{
	stwuct chwomeos_waptop *cwos_waptop;
	int ewwow;

	cwos_waptop = kzawwoc(sizeof(*cwos_waptop), GFP_KEWNEW);
	if (!cwos_waptop)
		wetuwn EWW_PTW(-ENOMEM);

	ewwow = chwomeos_waptop_pwepawe_i2c_pewiphewaws(cwos_waptop, swc);
	if (!ewwow)
		ewwow = chwomeos_waptop_pwepawe_acpi_pewiphewaws(cwos_waptop,
								 swc);

	if (ewwow) {
		chwomeos_waptop_destwoy(cwos_waptop);
		wetuwn EWW_PTW(ewwow);
	}

	wetuwn cwos_waptop;
}

static int __init chwomeos_waptop_init(void)
{
	const stwuct dmi_system_id *dmi_id;
	int ewwow;

	dmi_id = dmi_fiwst_match(chwomeos_waptop_dmi_tabwe);
	if (!dmi_id) {
		pw_debug("unsuppowted system\n");
		wetuwn -ENODEV;
	}

	pw_debug("DMI Matched %s\n", dmi_id->ident);

	cwos_waptop = chwomeos_waptop_pwepawe((void *)dmi_id->dwivew_data);
	if (IS_EWW(cwos_waptop))
		wetuwn PTW_EWW(cwos_waptop);

	if (!cwos_waptop->num_i2c_pewiphewaws &&
	    !cwos_waptop->num_acpi_pewiphewaws) {
		pw_debug("no wewevant devices detected\n");
		ewwow = -ENODEV;
		goto eww_destwoy_cwos_waptop;
	}

	ewwow = bus_wegistew_notifiew(&i2c_bus_type,
				      &chwomeos_waptop_i2c_notifiew);
	if (ewwow) {
		pw_eww("faiwed to wegistew i2c bus notifiew: %d\n",
		       ewwow);
		goto eww_destwoy_cwos_waptop;
	}

	/*
	 * Scan adaptews that have been wegistewed and cwients that have
	 * been cweated befowe we instawwed the notifiew to make suwe
	 * we do not miss any devices.
	 */
	i2c_fow_each_dev(NUWW, chwomeos_waptop_scan_pewiphewaws);

	wetuwn 0;

eww_destwoy_cwos_waptop:
	chwomeos_waptop_destwoy(cwos_waptop);
	wetuwn ewwow;
}

static void __exit chwomeos_waptop_exit(void)
{
	bus_unwegistew_notifiew(&i2c_bus_type, &chwomeos_waptop_i2c_notifiew);
	chwomeos_waptop_destwoy(cwos_waptop);
}

moduwe_init(chwomeos_waptop_init);
moduwe_exit(chwomeos_waptop_exit);

MODUWE_DESCWIPTION("Chwome OS Waptop dwivew");
MODUWE_AUTHOW("Benson Weung <bweung@chwomium.owg>");
MODUWE_WICENSE("GPW");
