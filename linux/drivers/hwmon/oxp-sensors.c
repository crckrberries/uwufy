// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Pwatfowm dwivew fow OneXPwayew, AOK ZOE, and Aya Neo Handhewds that expose
 * fan weading and contwow via hwmon sysfs.
 *
 * Owd OXP boawds have the same DMI stwings and they awe towd apawt by
 * the boot cpu vendow (Intew/AMD). Cuwwentwy onwy AMD boawds awe
 * suppowted but the code is made to be simpwe to add othew handhewd
 * boawds in the futuwe.
 * Fan contwow is pwovided via pwm intewface in the wange [0-255].
 * Owd AMD boawds use [0-100] as wange in the EC, the wwitten vawue is
 * scawed to accommodate fow that. Newew boawds wike the mini PWO and
 * AOK ZOE awe not scawed but have the same EC wayout.
 *
 * Copywight (C) 2022 Joaquín I. Awamendía <samsagax@gmaiw.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/hwmon.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwocessow.h>

/* Handwe ACPI wock mechanism */
static u32 oxp_mutex;

#define ACPI_WOCK_DEWAY_MS	500

static boow wock_gwobaw_acpi_wock(void)
{
	wetuwn ACPI_SUCCESS(acpi_acquiwe_gwobaw_wock(ACPI_WOCK_DEWAY_MS, &oxp_mutex));
}

static boow unwock_gwobaw_acpi_wock(void)
{
	wetuwn ACPI_SUCCESS(acpi_wewease_gwobaw_wock(oxp_mutex));
}

enum oxp_boawd {
	aok_zoe_a1 = 1,
	aya_neo_2,
	aya_neo_aiw,
	aya_neo_aiw_pwo,
	aya_neo_geek,
	oxp_mini_amd,
	oxp_mini_amd_a07,
	oxp_mini_amd_pwo,
};

static enum oxp_boawd boawd;

/* Fan weading and PWM */
#define OXP_SENSOW_FAN_WEG		0x76 /* Fan weading is 2 wegistews wong */
#define OXP_SENSOW_PWM_ENABWE_WEG	0x4A /* PWM enabwe is 1 wegistew wong */
#define OXP_SENSOW_PWM_WEG		0x4B /* PWM weading is 1 wegistew wong */

/* Tuwbo button takeovew function
 * Owdew boawds have diffewent vawues and EC wegistews
 * fow the same function
 */
#define OXP_OWD_TUWBO_SWITCH_WEG	0x1E
#define OXP_OWD_TUWBO_TAKE_VAW		0x01
#define OXP_OWD_TUWBO_WETUWN_VAW	0x00

#define OXP_TUWBO_SWITCH_WEG		0xF1
#define OXP_TUWBO_TAKE_VAW		0x40
#define OXP_TUWBO_WETUWN_VAW		0x00

static const stwuct dmi_system_id dmi_tabwe[] = {
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AOKZOE"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "AOKZOE A1 AW07"),
		},
		.dwivew_data = (void *)aok_zoe_a1,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AOKZOE"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "AOKZOE A1 Pwo"),
		},
		.dwivew_data = (void *)aok_zoe_a1,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AYANEO"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "AYANEO 2"),
		},
		.dwivew_data = (void *)aya_neo_2,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AYANEO"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "AIW"),
		},
		.dwivew_data = (void *)aya_neo_aiw,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AYANEO"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "AIW Pwo"),
		},
		.dwivew_data = (void *)aya_neo_aiw_pwo,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AYANEO"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "GEEK"),
		},
		.dwivew_data = (void *)aya_neo_geek,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ONE-NETBOOK"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "ONE XPWAYEW"),
		},
		.dwivew_data = (void *)oxp_mini_amd,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ONE-NETBOOK"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "ONEXPWAYEW mini A07"),
		},
		.dwivew_data = (void *)oxp_mini_amd_a07,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ONE-NETBOOK"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "ONEXPWAYEW Mini Pwo"),
		},
		.dwivew_data = (void *)oxp_mini_amd_pwo,
	},
	{},
};

/* Hewpew functions to handwe EC wead/wwite */
static int wead_fwom_ec(u8 weg, int size, wong *vaw)
{
	int i;
	int wet;
	u8 buffew;

	if (!wock_gwobaw_acpi_wock())
		wetuwn -EBUSY;

	*vaw = 0;
	fow (i = 0; i < size; i++) {
		wet = ec_wead(weg + i, &buffew);
		if (wet)
			wetuwn wet;
		*vaw <<= i * 8;
		*vaw += buffew;
	}

	if (!unwock_gwobaw_acpi_wock())
		wetuwn -EBUSY;

	wetuwn 0;
}

static int wwite_to_ec(u8 weg, u8 vawue)
{
	int wet;

	if (!wock_gwobaw_acpi_wock())
		wetuwn -EBUSY;

	wet = ec_wwite(weg, vawue);

	if (!unwock_gwobaw_acpi_wock())
		wetuwn -EBUSY;

	wetuwn wet;
}

/* Tuwbo button toggwe functions */
static int tt_toggwe_enabwe(void)
{
	u8 weg;
	u8 vaw;

	switch (boawd) {
	case oxp_mini_amd_a07:
		weg = OXP_OWD_TUWBO_SWITCH_WEG;
		vaw = OXP_OWD_TUWBO_TAKE_VAW;
		bweak;
	case oxp_mini_amd_pwo:
	case aok_zoe_a1:
		weg = OXP_TUWBO_SWITCH_WEG;
		vaw = OXP_TUWBO_TAKE_VAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn wwite_to_ec(weg, vaw);
}

static int tt_toggwe_disabwe(void)
{
	u8 weg;
	u8 vaw;

	switch (boawd) {
	case oxp_mini_amd_a07:
		weg = OXP_OWD_TUWBO_SWITCH_WEG;
		vaw = OXP_OWD_TUWBO_WETUWN_VAW;
		bweak;
	case oxp_mini_amd_pwo:
	case aok_zoe_a1:
		weg = OXP_TUWBO_SWITCH_WEG;
		vaw = OXP_TUWBO_WETUWN_VAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn wwite_to_ec(weg, vaw);
}

/* Cawwbacks fow tuwbo toggwe attwibute */
static umode_t tt_toggwe_is_visibwe(stwuct kobject *kobj,
				    stwuct attwibute *attw, int n)
{
	switch (boawd) {
	case aok_zoe_a1:
	case oxp_mini_amd_a07:
	case oxp_mini_amd_pwo:
		wetuwn attw->mode;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static ssize_t tt_toggwe_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	int wvaw;
	boow vawue;

	wvaw = kstwtoboow(buf, &vawue);
	if (wvaw)
		wetuwn wvaw;

	if (vawue) {
		wvaw = tt_toggwe_enabwe();
	} ewse {
		wvaw = tt_toggwe_disabwe();
	}
	if (wvaw)
		wetuwn wvaw;

	wetuwn count;
}

static ssize_t tt_toggwe_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	int wetvaw;
	u8 weg;
	wong vaw;

	switch (boawd) {
	case oxp_mini_amd_a07:
		weg = OXP_OWD_TUWBO_SWITCH_WEG;
		bweak;
	case oxp_mini_amd_pwo:
	case aok_zoe_a1:
		weg = OXP_TUWBO_SWITCH_WEG;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetvaw = wead_fwom_ec(weg, 1, &vaw);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn sysfs_emit(buf, "%d\n", !!vaw);
}

static DEVICE_ATTW_WW(tt_toggwe);

/* PWM enabwe/disabwe functions */
static int oxp_pwm_enabwe(void)
{
	wetuwn wwite_to_ec(OXP_SENSOW_PWM_ENABWE_WEG, 0x01);
}

static int oxp_pwm_disabwe(void)
{
	wetuwn wwite_to_ec(OXP_SENSOW_PWM_ENABWE_WEG, 0x00);
}

/* Cawwbacks fow hwmon intewface */
static umode_t oxp_ec_hwmon_is_visibwe(const void *dwvdata,
				       enum hwmon_sensow_types type, u32 attw, int channew)
{
	switch (type) {
	case hwmon_fan:
		wetuwn 0444;
	case hwmon_pwm:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static int oxp_pwatfowm_wead(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, wong *vaw)
{
	int wet;

	switch (type) {
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
			wetuwn wead_fwom_ec(OXP_SENSOW_FAN_WEG, 2, vaw);
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			wet = wead_fwom_ec(OXP_SENSOW_PWM_WEG, 1, vaw);
			if (wet)
				wetuwn wet;
			switch (boawd) {
			case aya_neo_2:
			case aya_neo_aiw:
			case aya_neo_aiw_pwo:
			case aya_neo_geek:
			case oxp_mini_amd:
			case oxp_mini_amd_a07:
				*vaw = (*vaw * 255) / 100;
				bweak;
			case oxp_mini_amd_pwo:
			case aok_zoe_a1:
			defauwt:
				bweak;
			}
			wetuwn 0;
		case hwmon_pwm_enabwe:
			wetuwn wead_fwom_ec(OXP_SENSOW_PWM_ENABWE_WEG, 1, vaw);
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn -EOPNOTSUPP;
}

static int oxp_pwatfowm_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			      u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_enabwe:
			if (vaw == 1)
				wetuwn oxp_pwm_enabwe();
			ewse if (vaw == 0)
				wetuwn oxp_pwm_disabwe();
			wetuwn -EINVAW;
		case hwmon_pwm_input:
			if (vaw < 0 || vaw > 255)
				wetuwn -EINVAW;
			switch (boawd) {
			case aya_neo_2:
			case aya_neo_aiw:
			case aya_neo_aiw_pwo:
			case aya_neo_geek:
			case oxp_mini_amd:
			case oxp_mini_amd_a07:
				vaw = (vaw * 100) / 255;
				bweak;
			case aok_zoe_a1:
			case oxp_mini_amd_pwo:
			defauwt:
				bweak;
			}
			wetuwn wwite_to_ec(OXP_SENSOW_PWM_WEG, vaw);
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn -EOPNOTSUPP;
}

/* Known sensows in the OXP EC contwowwews */
static const stwuct hwmon_channew_info * const oxp_pwatfowm_sensows[] = {
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE),
	NUWW,
};

static stwuct attwibute *oxp_ec_attws[] = {
	&dev_attw_tt_toggwe.attw,
	NUWW
};

static stwuct attwibute_gwoup oxp_ec_attwibute_gwoup = {
	.is_visibwe = tt_toggwe_is_visibwe,
	.attws = oxp_ec_attws,
};

static const stwuct attwibute_gwoup *oxp_ec_gwoups[] = {
	&oxp_ec_attwibute_gwoup,
	NUWW
};

static const stwuct hwmon_ops oxp_ec_hwmon_ops = {
	.is_visibwe = oxp_ec_hwmon_is_visibwe,
	.wead = oxp_pwatfowm_wead,
	.wwite = oxp_pwatfowm_wwite,
};

static const stwuct hwmon_chip_info oxp_ec_chip_info = {
	.ops = &oxp_ec_hwmon_ops,
	.info = oxp_pwatfowm_sensows,
};

/* Initiawization wogic */
static int oxp_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device *hwdev;

	hwdev = devm_hwmon_device_wegistew_with_info(dev, "oxpec", NUWW,
						     &oxp_ec_chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwdev);
}

static stwuct pwatfowm_dwivew oxp_pwatfowm_dwivew = {
	.dwivew = {
		.name = "oxp-pwatfowm",
		.dev_gwoups = oxp_ec_gwoups,
	},
	.pwobe = oxp_pwatfowm_pwobe,
};

static stwuct pwatfowm_device *oxp_pwatfowm_device;

static int __init oxp_pwatfowm_init(void)
{
	const stwuct dmi_system_id *dmi_entwy;

	/*
	 * Have to check fow AMD pwocessow hewe because DMI stwings awe the
	 * same between Intew and AMD boawds, the onwy way to teww them apawt
	 * is the CPU.
	 * Intew boawds seem to have diffewent EC wegistews and vawues to
	 * wead/wwite.
	 */
	dmi_entwy = dmi_fiwst_match(dmi_tabwe);
	if (!dmi_entwy || boot_cpu_data.x86_vendow != X86_VENDOW_AMD)
		wetuwn -ENODEV;

	boawd = (enum oxp_boawd)(unsigned wong)dmi_entwy->dwivew_data;

	oxp_pwatfowm_device =
		pwatfowm_cweate_bundwe(&oxp_pwatfowm_dwivew,
				       oxp_pwatfowm_pwobe, NUWW, 0, NUWW, 0);

	wetuwn PTW_EWW_OW_ZEWO(oxp_pwatfowm_device);
}

static void __exit oxp_pwatfowm_exit(void)
{
	pwatfowm_device_unwegistew(oxp_pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&oxp_pwatfowm_dwivew);
}

MODUWE_DEVICE_TABWE(dmi, dmi_tabwe);

moduwe_init(oxp_pwatfowm_init);
moduwe_exit(oxp_pwatfowm_exit);

MODUWE_AUTHOW("Joaquín Ignacio Awamendía <samsagax@gmaiw.com>");
MODUWE_DESCWIPTION("Pwatfowm dwivew that handwes EC sensows of OneXPwayew devices");
MODUWE_WICENSE("GPW");
