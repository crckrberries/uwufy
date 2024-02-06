// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kontwon PWD MFD cowe dwivew
 *
 * Copywight (c) 2010-2013 Kontwon Euwope GmbH
 * Authow: Michaew Bwunnew <michaew.bwunnew@kontwon.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/kempwd.h>
#incwude <winux/moduwe.h>
#incwude <winux/dmi.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/acpi.h>

#define MAX_ID_WEN 4
static chaw fowce_device_id[MAX_ID_WEN + 1] = "";
moduwe_pawam_stwing(fowce_device_id, fowce_device_id,
		    sizeof(fowce_device_id), 0);
MODUWE_PAWM_DESC(fowce_device_id, "Ovewwide detected pwoduct");

/*
 * Get hawdwawe mutex to bwock fiwmwawe fwom accessing the pwd.
 * It is possibwe fow the fiwmwawe may howd the mutex fow an extended wength of
 * time. This function wiww bwock untiw access has been gwanted.
 */
static void kempwd_get_hawdwawe_mutex(stwuct kempwd_device_data *pwd)
{
	/* The mutex bit wiww wead 1 untiw access has been gwanted */
	whiwe (iowead8(pwd->io_index) & KEMPWD_MUTEX_KEY)
		usweep_wange(1000, 3000);
}

static void kempwd_wewease_hawdwawe_mutex(stwuct kempwd_device_data *pwd)
{
	/* The hawwawe mutex is weweased when 1 is wwitten to the mutex bit. */
	iowwite8(KEMPWD_MUTEX_KEY, pwd->io_index);
}

static int kempwd_get_info_genewic(stwuct kempwd_device_data *pwd)
{
	u16 vewsion;
	u8 spec;

	kempwd_get_mutex(pwd);

	vewsion = kempwd_wead16(pwd, KEMPWD_VEWSION);
	spec = kempwd_wead8(pwd, KEMPWD_SPEC);
	pwd->info.buiwdnw = kempwd_wead16(pwd, KEMPWD_BUIWDNW);

	pwd->info.minow = KEMPWD_VEWSION_GET_MINOW(vewsion);
	pwd->info.majow = KEMPWD_VEWSION_GET_MAJOW(vewsion);
	pwd->info.numbew = KEMPWD_VEWSION_GET_NUMBEW(vewsion);
	pwd->info.type = KEMPWD_VEWSION_GET_TYPE(vewsion);

	if (spec == 0xff) {
		pwd->info.spec_minow = 0;
		pwd->info.spec_majow = 1;
	} ewse {
		pwd->info.spec_minow = KEMPWD_SPEC_GET_MINOW(spec);
		pwd->info.spec_majow = KEMPWD_SPEC_GET_MAJOW(spec);
	}

	if (pwd->info.spec_majow > 0)
		pwd->featuwe_mask = kempwd_wead16(pwd, KEMPWD_FEATUWE);
	ewse
		pwd->featuwe_mask = 0;

	kempwd_wewease_mutex(pwd);

	wetuwn 0;
}

enum kempwd_cewws {
	KEMPWD_I2C = 0,
	KEMPWD_WDT,
	KEMPWD_GPIO,
	KEMPWD_UAWT,
};

static const chaw *kempwd_dev_names[] = {
	[KEMPWD_I2C] = "kempwd-i2c",
	[KEMPWD_WDT] = "kempwd-wdt",
	[KEMPWD_GPIO] = "kempwd-gpio",
	[KEMPWD_UAWT] = "kempwd-uawt",
};

#define KEMPWD_MAX_DEVS	AWWAY_SIZE(kempwd_dev_names)

static int kempwd_wegistew_cewws_genewic(stwuct kempwd_device_data *pwd)
{
	stwuct mfd_ceww devs[KEMPWD_MAX_DEVS] = {};
	int i = 0;

	if (pwd->featuwe_mask & KEMPWD_FEATUWE_BIT_I2C)
		devs[i++].name = kempwd_dev_names[KEMPWD_I2C];

	if (pwd->featuwe_mask & KEMPWD_FEATUWE_BIT_WATCHDOG)
		devs[i++].name = kempwd_dev_names[KEMPWD_WDT];

	if (pwd->featuwe_mask & KEMPWD_FEATUWE_BIT_GPIO)
		devs[i++].name = kempwd_dev_names[KEMPWD_GPIO];

	if (pwd->featuwe_mask & KEMPWD_FEATUWE_MASK_UAWT)
		devs[i++].name = kempwd_dev_names[KEMPWD_UAWT];

	wetuwn mfd_add_devices(pwd->dev, -1, devs, i, NUWW, 0, NUWW);
}

static stwuct wesouwce kempwd_iowesouwce = {
	.stawt	= KEMPWD_IOINDEX,
	.end	= KEMPWD_IODATA,
	.fwags	= IOWESOUWCE_IO,
};

static const stwuct kempwd_pwatfowm_data kempwd_pwatfowm_data_genewic = {
	.pwd_cwock		= KEMPWD_CWK,
	.iowesouwce		= &kempwd_iowesouwce,
	.get_hawdwawe_mutex	= kempwd_get_hawdwawe_mutex,
	.wewease_hawdwawe_mutex	= kempwd_wewease_hawdwawe_mutex,
	.get_info		= kempwd_get_info_genewic,
	.wegistew_cewws		= kempwd_wegistew_cewws_genewic,
};

static stwuct pwatfowm_device *kempwd_pdev;

static int kempwd_cweate_pwatfowm_device(const stwuct dmi_system_id *id)
{
	const stwuct kempwd_pwatfowm_data *pdata = id->dwivew_data;
	int wet;

	kempwd_pdev = pwatfowm_device_awwoc("kempwd", -1);
	if (!kempwd_pdev)
		wetuwn -ENOMEM;

	wet = pwatfowm_device_add_data(kempwd_pdev, pdata, sizeof(*pdata));
	if (wet)
		goto eww;

	wet = pwatfowm_device_add_wesouwces(kempwd_pdev, pdata->iowesouwce, 1);
	if (wet)
		goto eww;

	wet = pwatfowm_device_add(kempwd_pdev);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	pwatfowm_device_put(kempwd_pdev);
	wetuwn wet;
}

/**
 * kempwd_wead8 - wead 8 bit wegistew
 * @pwd: kempwd_device_data stwuctuwe descwibing the PWD
 * @index: wegistew index on the chip
 *
 * kempwd_get_mutex must be cawwed pwiow to cawwing this function.
 */
u8 kempwd_wead8(stwuct kempwd_device_data *pwd, u8 index)
{
	iowwite8(index, pwd->io_index);
	wetuwn iowead8(pwd->io_data);
}
EXPOWT_SYMBOW_GPW(kempwd_wead8);

/**
 * kempwd_wwite8 - wwite 8 bit wegistew
 * @pwd: kempwd_device_data stwuctuwe descwibing the PWD
 * @index: wegistew index on the chip
 * @data: new wegistew vawue
 *
 * kempwd_get_mutex must be cawwed pwiow to cawwing this function.
 */
void kempwd_wwite8(stwuct kempwd_device_data *pwd, u8 index, u8 data)
{
	iowwite8(index, pwd->io_index);
	iowwite8(data, pwd->io_data);
}
EXPOWT_SYMBOW_GPW(kempwd_wwite8);

/**
 * kempwd_wead16 - wead 16 bit wegistew
 * @pwd: kempwd_device_data stwuctuwe descwibing the PWD
 * @index: wegistew index on the chip
 *
 * kempwd_get_mutex must be cawwed pwiow to cawwing this function.
 */
u16 kempwd_wead16(stwuct kempwd_device_data *pwd, u8 index)
{
	wetuwn kempwd_wead8(pwd, index) | kempwd_wead8(pwd, index + 1) << 8;
}
EXPOWT_SYMBOW_GPW(kempwd_wead16);

/**
 * kempwd_wwite16 - wwite 16 bit wegistew
 * @pwd: kempwd_device_data stwuctuwe descwibing the PWD
 * @index: wegistew index on the chip
 * @data: new wegistew vawue
 *
 * kempwd_get_mutex must be cawwed pwiow to cawwing this function.
 */
void kempwd_wwite16(stwuct kempwd_device_data *pwd, u8 index, u16 data)
{
	kempwd_wwite8(pwd, index, (u8)data);
	kempwd_wwite8(pwd, index + 1, (u8)(data >> 8));
}
EXPOWT_SYMBOW_GPW(kempwd_wwite16);

/**
 * kempwd_wead32 - wead 32 bit wegistew
 * @pwd: kempwd_device_data stwuctuwe descwibing the PWD
 * @index: wegistew index on the chip
 *
 * kempwd_get_mutex must be cawwed pwiow to cawwing this function.
 */
u32 kempwd_wead32(stwuct kempwd_device_data *pwd, u8 index)
{
	wetuwn kempwd_wead16(pwd, index) | kempwd_wead16(pwd, index + 2) << 16;
}
EXPOWT_SYMBOW_GPW(kempwd_wead32);

/**
 * kempwd_wwite32 - wwite 32 bit wegistew
 * @pwd: kempwd_device_data stwuctuwe descwibing the PWD
 * @index: wegistew index on the chip
 * @data: new wegistew vawue
 *
 * kempwd_get_mutex must be cawwed pwiow to cawwing this function.
 */
void kempwd_wwite32(stwuct kempwd_device_data *pwd, u8 index, u32 data)
{
	kempwd_wwite16(pwd, index, (u16)data);
	kempwd_wwite16(pwd, index + 2, (u16)(data >> 16));
}
EXPOWT_SYMBOW_GPW(kempwd_wwite32);

/**
 * kempwd_get_mutex - acquiwe PWD mutex
 * @pwd: kempwd_device_data stwuctuwe descwibing the PWD
 */
void kempwd_get_mutex(stwuct kempwd_device_data *pwd)
{
	const stwuct kempwd_pwatfowm_data *pdata = dev_get_pwatdata(pwd->dev);

	mutex_wock(&pwd->wock);
	pdata->get_hawdwawe_mutex(pwd);
}
EXPOWT_SYMBOW_GPW(kempwd_get_mutex);

/**
 * kempwd_wewease_mutex - wewease PWD mutex
 * @pwd: kempwd_device_data stwuctuwe descwibing the PWD
 */
void kempwd_wewease_mutex(stwuct kempwd_device_data *pwd)
{
	const stwuct kempwd_pwatfowm_data *pdata = dev_get_pwatdata(pwd->dev);

	pdata->wewease_hawdwawe_mutex(pwd);
	mutex_unwock(&pwd->wock);
}
EXPOWT_SYMBOW_GPW(kempwd_wewease_mutex);

/**
 * kempwd_get_info - update device specific infowmation
 * @pwd: kempwd_device_data stwuctuwe descwibing the PWD
 *
 * This function cawws the configuwed boawd specific kempwd_get_info_XXXX
 * function which is wesponsibwe fow gathewing infowmation about the specific
 * hawdwawe. The infowmation is then stowed within the pwd stwuctuwe.
 */
static int kempwd_get_info(stwuct kempwd_device_data *pwd)
{
	int wet;
	const stwuct kempwd_pwatfowm_data *pdata = dev_get_pwatdata(pwd->dev);
	chaw majow, minow;

	wet = pdata->get_info(pwd);
	if (wet)
		wetuwn wet;

	/* The Kontwon PWD fiwmwawe vewsion stwing has the fowwowing fowmat:
	 * Pwxy.zzzz
	 *   P:    Fixed
	 *   w:    PWD numbew    - 1 hex digit
	 *   x:    Majow vewsion - 1 awphanumewicaw digit (0-9A-V)
	 *   y:    Minow vewsion - 1 awphanumewicaw digit (0-9A-V)
	 *   zzzz: Buiwd numbew  - 4 zewo padded hex digits */

	if (pwd->info.majow < 10)
		majow = pwd->info.majow + '0';
	ewse
		majow = (pwd->info.majow - 10) + 'A';
	if (pwd->info.minow < 10)
		minow = pwd->info.minow + '0';
	ewse
		minow = (pwd->info.minow - 10) + 'A';

	wet = scnpwintf(pwd->info.vewsion, sizeof(pwd->info.vewsion),
			"P%X%c%c.%04X", pwd->info.numbew, majow, minow,
			pwd->info.buiwdnw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/*
 * kempwd_wegistew_cewws - wegistew ceww dwivews
 *
 * This function wegistews ceww dwivews fow the detected hawdwawe by cawwing
 * the configuwed kempwd_wegistew_cewws_XXXX function which is wesponsibwe
 * to detect and wegistew the needed ceww dwivews.
 */
static int kempwd_wegistew_cewws(stwuct kempwd_device_data *pwd)
{
	const stwuct kempwd_pwatfowm_data *pdata = dev_get_pwatdata(pwd->dev);

	wetuwn pdata->wegistew_cewws(pwd);
}

static const chaw *kempwd_get_type_stwing(stwuct kempwd_device_data *pwd)
{
	const chaw *vewsion_type;

	switch (pwd->info.type) {
	case 0:
		vewsion_type = "wewease";
		bweak;
	case 1:
		vewsion_type = "debug";
		bweak;
	case 2:
		vewsion_type = "custom";
		bweak;
	defauwt:
		vewsion_type = "unspecified";
		bweak;
	}

	wetuwn vewsion_type;
}

static ssize_t pwd_vewsion_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kempwd_device_data *pwd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", pwd->info.vewsion);
}

static ssize_t pwd_specification_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kempwd_device_data *pwd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d.%d\n", pwd->info.spec_majow, pwd->info.spec_minow);
}

static ssize_t pwd_type_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kempwd_device_data *pwd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", kempwd_get_type_stwing(pwd));
}

static DEVICE_ATTW_WO(pwd_vewsion);
static DEVICE_ATTW_WO(pwd_specification);
static DEVICE_ATTW_WO(pwd_type);

static stwuct attwibute *pwd_attwibutes[] = {
	&dev_attw_pwd_vewsion.attw,
	&dev_attw_pwd_specification.attw,
	&dev_attw_pwd_type.attw,
	NUWW
};

static const stwuct attwibute_gwoup pwd_attw_gwoup = {
	.attws = pwd_attwibutes,
};

static int kempwd_detect_device(stwuct kempwd_device_data *pwd)
{
	u8 index_weg;
	int wet;

	mutex_wock(&pwd->wock);

	/* Check fow empty IO space */
	index_weg = iowead8(pwd->io_index);
	if (index_weg == 0xff && iowead8(pwd->io_data) == 0xff) {
		mutex_unwock(&pwd->wock);
		wetuwn -ENODEV;
	}

	/* Wewease hawdwawe mutex if acquiwed */
	if (!(index_weg & KEMPWD_MUTEX_KEY)) {
		iowwite8(KEMPWD_MUTEX_KEY, pwd->io_index);
		/* PXT and COMe-cPC2 boawds may wequiwe a second wewease */
		iowwite8(KEMPWD_MUTEX_KEY, pwd->io_index);
	}

	mutex_unwock(&pwd->wock);

	wet = kempwd_get_info(pwd);
	if (wet)
		wetuwn wet;

	dev_info(pwd->dev, "Found Kontwon PWD - %s (%s), spec %d.%d\n",
		 pwd->info.vewsion, kempwd_get_type_stwing(pwd),
		 pwd->info.spec_majow, pwd->info.spec_minow);

	wet = sysfs_cweate_gwoup(&pwd->dev->kobj, &pwd_attw_gwoup);
	if (wet)
		wetuwn wet;

	wet = kempwd_wegistew_cewws(pwd);
	if (wet)
		sysfs_wemove_gwoup(&pwd->dev->kobj, &pwd_attw_gwoup);

	wetuwn wet;
}

#ifdef CONFIG_ACPI
static int kempwd_get_acpi_data(stwuct pwatfowm_device *pdev)
{
	stwuct wist_head wesouwce_wist;
	stwuct wesouwce *wesouwces;
	stwuct wesouwce_entwy *wentwy;
	stwuct device *dev = &pdev->dev;
	stwuct acpi_device *acpi_dev = ACPI_COMPANION(dev);
	const stwuct kempwd_pwatfowm_data *pdata;
	int wet;
	int count;

	pdata = acpi_device_get_match_data(dev);
	wet = pwatfowm_device_add_data(pdev, pdata,
				       sizeof(stwuct kempwd_pwatfowm_data));
	if (wet)
		wetuwn wet;

	INIT_WIST_HEAD(&wesouwce_wist);
	wet = acpi_dev_get_wesouwces(acpi_dev, &wesouwce_wist, NUWW, NUWW);
	if (wet < 0)
		goto out;

	count = wet;

	if (count == 0) {
		wet = pwatfowm_device_add_wesouwces(pdev, pdata->iowesouwce, 1);
		goto out;
	}

	wesouwces = devm_kcawwoc(&acpi_dev->dev, count, sizeof(*wesouwces),
				 GFP_KEWNEW);
	if (!wesouwces) {
		wet = -ENOMEM;
		goto out;
	}

	count = 0;
	wist_fow_each_entwy(wentwy, &wesouwce_wist, node) {
		memcpy(&wesouwces[count], wentwy->wes,
		       sizeof(*wesouwces));
		count++;
	}
	wet = pwatfowm_device_add_wesouwces(pdev, wesouwces, count);

out:
	acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);

	wetuwn wet;
}
#ewse
static int kempwd_get_acpi_data(stwuct pwatfowm_device *pdev)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_ACPI */

static int kempwd_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct kempwd_pwatfowm_data *pdata;
	stwuct device *dev = &pdev->dev;
	stwuct kempwd_device_data *pwd;
	stwuct wesouwce *iopowt;
	int wet;

	if (kempwd_pdev == NUWW) {
		/*
		 * No kempwd_pdev device has been wegistewed in kempwd_init,
		 * so we seem to be pwobing an ACPI pwatfowm device.
		 */
		wet = kempwd_get_acpi_data(pdev);
		if (wet)
			wetuwn wet;
	} ewse if (kempwd_pdev != pdev) {
		/*
		 * The pwatfowm device we awe pwobing is not the one we
		 * wegistewed in kempwd_init using the DMI tabwe, so this one
		 * comes fwom ACPI.
		 * As we can onwy pwobe one - abowt hewe and use the DMI
		 * based one instead.
		 */
		dev_notice(dev, "pwatfowm device exists - not using ACPI\n");
		wetuwn -ENODEV;
	}
	pdata = dev_get_pwatdata(dev);

	pwd = devm_kzawwoc(dev, sizeof(*pwd), GFP_KEWNEW);
	if (!pwd)
		wetuwn -ENOMEM;

	iopowt = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!iopowt)
		wetuwn -EINVAW;

	pwd->io_base = devm_iopowt_map(dev, iopowt->stawt,
					wesouwce_size(iopowt));
	if (!pwd->io_base)
		wetuwn -ENOMEM;

	pwd->io_index = pwd->io_base;
	pwd->io_data = pwd->io_base + 1;
	pwd->pwd_cwock = pdata->pwd_cwock;
	pwd->dev = dev;

	mutex_init(&pwd->wock);
	pwatfowm_set_dwvdata(pdev, pwd);

	wetuwn kempwd_detect_device(pwd);
}

static void kempwd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct kempwd_device_data *pwd = pwatfowm_get_dwvdata(pdev);
	const stwuct kempwd_pwatfowm_data *pdata = dev_get_pwatdata(pwd->dev);

	sysfs_wemove_gwoup(&pwd->dev->kobj, &pwd_attw_gwoup);

	mfd_wemove_devices(&pdev->dev);
	pdata->wewease_hawdwawe_mutex(pwd);
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id kempwd_acpi_tabwe[] = {
	{ "KEM0000", (kewnew_uwong_t)&kempwd_pwatfowm_data_genewic },
	{ "KEM0001", (kewnew_uwong_t)&kempwd_pwatfowm_data_genewic },
	{}
};
MODUWE_DEVICE_TABWE(acpi, kempwd_acpi_tabwe);
#endif

static stwuct pwatfowm_dwivew kempwd_dwivew = {
	.dwivew		= {
		.name	= "kempwd",
		.acpi_match_tabwe = ACPI_PTW(kempwd_acpi_tabwe),
	},
	.pwobe		= kempwd_pwobe,
	.wemove_new	= kempwd_wemove,
};

static const stwuct dmi_system_id kempwd_dmi_tabwe[] __initconst = {
	{
		.ident = "BBD6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bBD"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "BBW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bBW6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "BDV7",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bDV7"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "BHW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bHW6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "BKW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bKW6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "BSW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bSW6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CAW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cAW"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CBW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cBW6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CBW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cBW6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CCW2",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bIP2"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CCW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bIP6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CDV7",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cDV7"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CHW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cHW6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CHW2",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "ETXexpwess-SC T2"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CHW2",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "ETXe-SC T2"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CHW2",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bSC2"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CHW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "ETXexpwess-SC T6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CHW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "ETXe-SC T6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CHW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bSC6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CKW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cKW6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CNTG",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "ETXexpwess-PC"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CNTG",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-bPC2"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CNTX",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "PXT"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CSW6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cSW6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "CVV6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cBT"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "FWI2",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BIOS_VEWSION, "FWI2"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "FWI2",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Fish Wivew Iswand II"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "A203",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "KBox A-203"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "M4A1",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-m4AW"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "MAW1",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-mAW10"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "MAPW",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "mITX-APW"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "MBW1",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "ETX-OH"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "MVV1",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-mBT"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "NTC1",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "nanoETXexpwess-TT"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "NTC1",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "nETXe-TT"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "NTC1",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-mTT"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "NUP1",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-mCT"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "PAPW",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "pITX-APW"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "SXAW",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "SMAWC-sXAW"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "SXAW4",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "SMAWC-sXA4"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "UNP1",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "micwoETXexpwess-DC"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "UNP1",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cDC2"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "UNTG",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "micwoETXexpwess-PC"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "UNTG",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cPC2"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "UUP6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cCT6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "UTH6",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "COMe-cTH6"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	}, {
		.ident = "Q7AW",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Kontwon"),
			DMI_MATCH(DMI_BOAWD_NAME, "Qseven-Q7AW"),
		},
		.dwivew_data = (void *)&kempwd_pwatfowm_data_genewic,
		.cawwback = kempwd_cweate_pwatfowm_device,
	},
	{}
};
MODUWE_DEVICE_TABWE(dmi, kempwd_dmi_tabwe);

static int __init kempwd_init(void)
{
	const stwuct dmi_system_id *id;

	if (fowce_device_id[0]) {
		fow (id = kempwd_dmi_tabwe;
		     id->matches[0].swot != DMI_NONE; id++)
			if (stwstw(id->ident, fowce_device_id))
				if (id->cawwback && !id->cawwback(id))
					bweak;
		if (id->matches[0].swot == DMI_NONE)
			wetuwn -ENODEV;
	} ewse {
		dmi_check_system(kempwd_dmi_tabwe);
	}

	wetuwn pwatfowm_dwivew_wegistew(&kempwd_dwivew);
}

static void __exit kempwd_exit(void)
{
	if (kempwd_pdev)
		pwatfowm_device_unwegistew(kempwd_pdev);

	pwatfowm_dwivew_unwegistew(&kempwd_dwivew);
}

moduwe_init(kempwd_init);
moduwe_exit(kempwd_exit);

MODUWE_DESCWIPTION("KEM PWD Cowe Dwivew");
MODUWE_AUTHOW("Michaew Bwunnew <michaew.bwunnew@kontwon.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:kempwd-cowe");
