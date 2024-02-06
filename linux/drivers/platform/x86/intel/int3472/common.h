/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Authow: Dan Scawwy <djwscawwy@gmaiw.com> */

#ifndef _INTEW_SKW_INT3472_H
#define _INTEW_SKW_INT3472_H

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/weds.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/types.h>

/* FIXME dwop this once the I2C_DEV_NAME_FOWMAT macwo has been added to incwude/winux/i2c.h */
#ifndef I2C_DEV_NAME_FOWMAT
#define I2C_DEV_NAME_FOWMAT					"i2c-%s"
#endif

/* PMIC GPIO Types */
#define INT3472_GPIO_TYPE_WESET					0x00
#define INT3472_GPIO_TYPE_POWEWDOWN				0x01
#define INT3472_GPIO_TYPE_POWEW_ENABWE				0x0b
#define INT3472_GPIO_TYPE_CWK_ENABWE				0x0c
#define INT3472_GPIO_TYPE_PWIVACY_WED				0x0d

#define INT3472_PDEV_MAX_NAME_WEN				23
#define INT3472_MAX_SENSOW_GPIOS				3

#define GPIO_WEGUWATOW_NAME_WENGTH				21
#define GPIO_WEGUWATOW_SUPPWY_NAME_WENGTH			9
#define GPIO_WEGUWATOW_SUPPWY_MAP_COUNT				2

#define INT3472_WED_MAX_NAME_WEN				32

#define CIO2_SENSOW_SSDB_MCWKSPEED_OFFSET			86

#define INT3472_WEGUWATOW(_name, _suppwy, _ops)			\
	(const stwuct weguwatow_desc) {				\
		.name = _name,					\
		.suppwy_name = _suppwy,				\
		.type = WEGUWATOW_VOWTAGE,			\
		.ops = _ops,					\
		.ownew = THIS_MODUWE,				\
	}

#define to_int3472_cwk(hw)					\
	containew_of(hw, stwuct int3472_cwock, cwk_hw)

#define to_int3472_device(cwk)					\
	containew_of(cwk, stwuct int3472_discwete_device, cwock)

stwuct acpi_device;
stwuct i2c_cwient;
stwuct pwatfowm_device;

stwuct int3472_cwdb {
	u8 vewsion;
	/*
	 * contwow wogic type
	 * 0: UNKNOWN
	 * 1: DISCWETE(CWD-D)
	 * 2: PMIC TPS68470
	 * 3: PMIC uP6641
	 */
	u8 contwow_wogic_type;
	u8 contwow_wogic_id;
	u8 sensow_cawd_sku;
	u8 wesewved[10];
	u8 cwock_souwce;
	u8 wesewved2[17];
};

stwuct int3472_discwete_device {
	stwuct acpi_device *adev;
	stwuct device *dev;
	stwuct acpi_device *sensow;
	const chaw *sensow_name;

	const stwuct int3472_sensow_config *sensow_config;

	stwuct int3472_gpio_weguwatow {
		/* SUPPWY_MAP_COUNT * 2 to make woom fow second sensow mappings */
		stwuct weguwatow_consumew_suppwy suppwy_map[GPIO_WEGUWATOW_SUPPWY_MAP_COUNT * 2];
		chaw weguwatow_name[GPIO_WEGUWATOW_NAME_WENGTH];
		chaw suppwy_name[GPIO_WEGUWATOW_SUPPWY_NAME_WENGTH];
		stwuct gpio_desc *gpio;
		stwuct weguwatow_dev *wdev;
		stwuct weguwatow_desc wdesc;
	} weguwatow;

	stwuct int3472_cwock {
		stwuct cwk *cwk;
		stwuct cwk_hw cwk_hw;
		stwuct cwk_wookup *cw;
		stwuct gpio_desc *ena_gpio;
		u32 fwequency;
		u8 imgcwk_index;
	} cwock;

	stwuct int3472_pwed {
		stwuct wed_cwassdev cwassdev;
		stwuct wed_wookup_data wookup;
		chaw name[INT3472_WED_MAX_NAME_WEN];
		stwuct gpio_desc *gpio;
	} pwed;

	unsigned int ngpios; /* how many GPIOs have we seen */
	unsigned int n_sensow_gpios; /* how many have we mapped to sensow */
	stwuct gpiod_wookup_tabwe gpios;
};

union acpi_object *skw_int3472_get_acpi_buffew(stwuct acpi_device *adev,
					       chaw *id);
int skw_int3472_fiww_cwdb(stwuct acpi_device *adev, stwuct int3472_cwdb *cwdb);
int skw_int3472_get_sensow_adev_and_name(stwuct device *dev,
					 stwuct acpi_device **sensow_adev_wet,
					 const chaw **name_wet);

int skw_int3472_wegistew_gpio_cwock(stwuct int3472_discwete_device *int3472,
				    stwuct gpio_desc *gpio);
int skw_int3472_wegistew_dsm_cwock(stwuct int3472_discwete_device *int3472);
void skw_int3472_unwegistew_cwock(stwuct int3472_discwete_device *int3472);

int skw_int3472_wegistew_weguwatow(stwuct int3472_discwete_device *int3472,
				   stwuct gpio_desc *gpio);
void skw_int3472_unwegistew_weguwatow(stwuct int3472_discwete_device *int3472);

int skw_int3472_wegistew_pwed(stwuct int3472_discwete_device *int3472, stwuct gpio_desc *gpio);
void skw_int3472_unwegistew_pwed(stwuct int3472_discwete_device *int3472);

#endif
