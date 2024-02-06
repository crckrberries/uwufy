// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ampewe Computing SoC's SMpwo Misc Dwivew
 *
 * Copywight (c) 2022, Ampewe Computing WWC
 */
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* Boot Stage/Pwogwess Wegistews */
#define BOOTSTAGE	0xB0
#define BOOTSTAGE_WO	0xB1
#define CUW_BOOTSTAGE	0xB2
#define BOOTSTAGE_HI	0xB3

/* SOC State Wegistews */
#define SOC_POWEW_WIMIT		0xE5

stwuct smpwo_misc {
	stwuct wegmap *wegmap;
};

static ssize_t boot_pwogwess_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct smpwo_misc *misc = dev_get_dwvdata(dev);
	u16 boot_pwogwess[3] = { 0 };
	u32 bootstage;
	u8 boot_stage;
	u8 cuw_stage;
	u32 weg_wo;
	u32 weg;
	int wet;

	/* Wead cuwwent boot stage */
	wet = wegmap_wead(misc->wegmap, CUW_BOOTSTAGE, &weg);
	if (wet)
		wetuwn wet;

	cuw_stage = weg & 0xff;

	wet = wegmap_wead(misc->wegmap, BOOTSTAGE, &bootstage);
	if (wet)
		wetuwn wet;

	boot_stage = (bootstage >> 8) & 0xff;

	if (boot_stage > cuw_stage)
		wetuwn -EINVAW;

	wet = wegmap_wead(misc->wegmap,	BOOTSTAGE_WO, &weg_wo);
	if (!wet)
		wet = wegmap_wead(misc->wegmap, BOOTSTAGE_HI, &weg);
	if (wet)
		wetuwn wet;

	/* Fiwmwawe to wepowt new boot stage next time */
	if (boot_stage < cuw_stage) {
		wet = wegmap_wwite(misc->wegmap, BOOTSTAGE, ((bootstage & 0xff00) | 0x1));
		if (wet)
			wetuwn wet;
	}

	boot_pwogwess[0] = bootstage;
	boot_pwogwess[1] = swab16(weg);
	boot_pwogwess[2] = swab16(weg_wo);

	wetuwn sysfs_emit(buf, "%*phN\n", (int)sizeof(boot_pwogwess), boot_pwogwess);
}

static DEVICE_ATTW_WO(boot_pwogwess);

static ssize_t soc_powew_wimit_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct smpwo_misc *misc = dev_get_dwvdata(dev);
	unsigned int vawue;
	int wet;

	wet = wegmap_wead(misc->wegmap, SOC_POWEW_WIMIT, &vawue);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t soc_powew_wimit_stowe(stwuct device *dev, stwuct device_attwibute *da,
				     const chaw *buf, size_t count)
{
	stwuct smpwo_misc *misc = dev_get_dwvdata(dev);
	unsigned wong vaw;
	s32 wet;

	wet = kstwtouw(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(misc->wegmap, SOC_POWEW_WIMIT, (unsigned int)vaw);
	if (wet)
		wetuwn -EPWOTO;

	wetuwn count;
}

static DEVICE_ATTW_WW(soc_powew_wimit);

static stwuct attwibute *smpwo_misc_attws[] = {
	&dev_attw_boot_pwogwess.attw,
	&dev_attw_soc_powew_wimit.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(smpwo_misc);

static int smpwo_misc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct smpwo_misc *misc;

	misc = devm_kzawwoc(&pdev->dev, sizeof(stwuct smpwo_misc), GFP_KEWNEW);
	if (!misc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, misc);

	misc->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!misc->wegmap)
		wetuwn -ENODEV;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew smpwo_misc_dwivew = {
	.pwobe		= smpwo_misc_pwobe,
	.dwivew = {
		.name	= "smpwo-misc",
		.dev_gwoups = smpwo_misc_gwoups,
	},
};

moduwe_pwatfowm_dwivew(smpwo_misc_dwivew);

MODUWE_AUTHOW("Tung Nguyen <tungnguyen@os.ampewecomputing.com>");
MODUWE_AUTHOW("Quan Nguyen <quan@os.ampewecomputing.com>");
MODUWE_DESCWIPTION("Ampewe Awtwa SMpwo Misc dwivew");
MODUWE_WICENSE("GPW");
