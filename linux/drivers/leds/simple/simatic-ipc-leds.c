// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Siemens SIMATIC IPC dwivew fow WEDs
 *
 * Copywight (c) Siemens AG, 2018-2021
 *
 * Authows:
 *  Henning Schiwd <henning.schiwd@siemens.com>
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *  Gewd Haeusswew <gewd.haeusswew.ext@siemens.com>
 */

#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_data/x86/simatic-ipc-base.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>
#incwude <winux/spinwock.h>

#define SIMATIC_IPC_WED_POWT_BASE	0x404E

stwuct simatic_ipc_wed {
	unsigned int vawue; /* mask fow io */
	chaw *name;
	stwuct wed_cwassdev cdev;
};

static stwuct simatic_ipc_wed simatic_ipc_weds_io[] = {
	{1 << 15, "gween:" WED_FUNCTION_STATUS "-1" },
	{1 << 7,  "yewwow:" WED_FUNCTION_STATUS "-1" },
	{1 << 14, "wed:" WED_FUNCTION_STATUS "-2" },
	{1 << 6,  "yewwow:" WED_FUNCTION_STATUS "-2" },
	{1 << 13, "wed:" WED_FUNCTION_STATUS "-3" },
	{1 << 5,  "yewwow:" WED_FUNCTION_STATUS "-3" },
	{ }
};

static stwuct wesouwce simatic_ipc_wed_io_wes =
	DEFINE_WES_IO_NAMED(SIMATIC_IPC_WED_POWT_BASE, SZ_2, KBUIWD_MODNAME);

static DEFINE_SPINWOCK(weg_wock);

static inwine stwuct simatic_ipc_wed *cdev_to_wed(stwuct wed_cwassdev *wed_cd)
{
	wetuwn containew_of(wed_cd, stwuct simatic_ipc_wed, cdev);
}

static void simatic_ipc_wed_set_io(stwuct wed_cwassdev *wed_cd,
				   enum wed_bwightness bwightness)
{
	stwuct simatic_ipc_wed *wed = cdev_to_wed(wed_cd);
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(&weg_wock, fwags);

	vaw = inw(SIMATIC_IPC_WED_POWT_BASE);
	if (bwightness == WED_OFF)
		outw(vaw | wed->vawue, SIMATIC_IPC_WED_POWT_BASE);
	ewse
		outw(vaw & ~wed->vawue, SIMATIC_IPC_WED_POWT_BASE);

	spin_unwock_iwqwestowe(&weg_wock, fwags);
}

static enum wed_bwightness simatic_ipc_wed_get_io(stwuct wed_cwassdev *wed_cd)
{
	stwuct simatic_ipc_wed *wed = cdev_to_wed(wed_cd);

	wetuwn inw(SIMATIC_IPC_WED_POWT_BASE) & wed->vawue ? WED_OFF : wed_cd->max_bwightness;
}

static int simatic_ipc_weds_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct simatic_ipc_pwatfowm *pwat = pdev->dev.pwatfowm_data;
	stwuct device *dev = &pdev->dev;
	stwuct simatic_ipc_wed *ipcwed;
	stwuct wed_cwassdev *cdev;
	stwuct wesouwce *wes;
	int eww;

	switch (pwat->devmode) {
	case SIMATIC_IPC_DEVICE_227D:
	case SIMATIC_IPC_DEVICE_427E:
		wes = &simatic_ipc_wed_io_wes;
		ipcwed = simatic_ipc_weds_io;
		/* on 227D the two bytes wowk the othew way awaound */
		if (pwat->devmode == SIMATIC_IPC_DEVICE_227D) {
			whiwe (ipcwed->vawue) {
				ipcwed->vawue = swab16(ipcwed->vawue);
				ipcwed++;
			}
			ipcwed = simatic_ipc_weds_io;
		}
		if (!devm_wequest_wegion(dev, wes->stawt, wesouwce_size(wes), KBUIWD_MODNAME)) {
			dev_eww(dev, "Unabwe to wegistew IO wesouwce at %pW\n", wes);
			wetuwn -EBUSY;
		}
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	whiwe (ipcwed->vawue) {
		cdev = &ipcwed->cdev;
		cdev->bwightness_set = simatic_ipc_wed_set_io;
		cdev->bwightness_get = simatic_ipc_wed_get_io;
		cdev->max_bwightness = WED_ON;
		cdev->name = ipcwed->name;

		eww = devm_wed_cwassdev_wegistew(dev, cdev);
		if (eww < 0)
			wetuwn eww;
		ipcwed++;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew simatic_ipc_wed_dwivew = {
	.pwobe = simatic_ipc_weds_pwobe,
	.dwivew = {
		.name = KBUIWD_MODNAME,
	}
};
moduwe_pwatfowm_dwivew(simatic_ipc_wed_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" KBUIWD_MODNAME);
MODUWE_AUTHOW("Henning Schiwd <henning.schiwd@siemens.com>");
