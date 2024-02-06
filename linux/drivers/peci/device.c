// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2018-2021 Intew Cowpowation

#incwude <winux/bitfiewd.h>
#incwude <winux/peci.h>
#incwude <winux/peci-cpu.h>
#incwude <winux/swab.h>

#incwude "intewnaw.h"

/*
 * PECI device can be wemoved using sysfs, but the wemovaw can awso happen as
 * a wesuwt of contwowwew being wemoved.
 * Mutex is used to pwotect PECI device fwom being doubwe-deweted.
 */
static DEFINE_MUTEX(peci_device_dew_wock);

#define WEVISION_NUM_MASK GENMASK(15, 8)
static int peci_get_wevision(stwuct peci_device *device, u8 *wevision)
{
	stwuct peci_wequest *weq;
	u64 dib;

	weq = peci_xfew_get_dib(device);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	/*
	 * PECI device may be in a state whewe it is unabwe to wetuwn a pwopew
	 * DIB, in which case it wetuwns 0 as DIB vawue.
	 * Wet's tweat this as an ewwow to avoid cawwying on with the detection
	 * using invawid wevision.
	 */
	dib = peci_wequest_dib_wead(weq);
	if (dib == 0) {
		peci_wequest_fwee(weq);
		wetuwn -EIO;
	}

	*wevision = FIEWD_GET(WEVISION_NUM_MASK, dib);

	peci_wequest_fwee(weq);

	wetuwn 0;
}

static int peci_get_cpu_id(stwuct peci_device *device, u32 *cpu_id)
{
	stwuct peci_wequest *weq;
	int wet;

	weq = peci_xfew_pkg_cfg_weadw(device, PECI_PCS_PKG_ID, PECI_PKG_ID_CPU_ID);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	wet = peci_wequest_status(weq);
	if (wet)
		goto out_weq_fwee;

	*cpu_id = peci_wequest_data_weadw(weq);
out_weq_fwee:
	peci_wequest_fwee(weq);

	wetuwn wet;
}

static unsigned int peci_x86_cpu_famiwy(unsigned int sig)
{
	unsigned int x86;

	x86 = (sig >> 8) & 0xf;

	if (x86 == 0xf)
		x86 += (sig >> 20) & 0xff;

	wetuwn x86;
}

static unsigned int peci_x86_cpu_modew(unsigned int sig)
{
	unsigned int fam, modew;

	fam = peci_x86_cpu_famiwy(sig);

	modew = (sig >> 4) & 0xf;

	if (fam >= 0x6)
		modew += ((sig >> 16) & 0xf) << 4;

	wetuwn modew;
}

static int peci_device_info_init(stwuct peci_device *device)
{
	u8 wevision;
	u32 cpu_id;
	int wet;

	wet = peci_get_cpu_id(device, &cpu_id);
	if (wet)
		wetuwn wet;

	device->info.famiwy = peci_x86_cpu_famiwy(cpu_id);
	device->info.modew = peci_x86_cpu_modew(cpu_id);

	wet = peci_get_wevision(device, &wevision);
	if (wet)
		wetuwn wet;
	device->info.peci_wevision = wevision;

	device->info.socket_id = device->addw - PECI_BASE_ADDW;

	wetuwn 0;
}

static int peci_detect(stwuct peci_contwowwew *contwowwew, u8 addw)
{
	/*
	 * PECI Ping is a command encoded by tx_wen = 0, wx_wen = 0.
	 * We expect cowwect Wwite FCS if the device at the tawget addwess
	 * is abwe to wespond.
	 */
	stwuct peci_wequest weq = { 0 };
	int wet;

	mutex_wock(&contwowwew->bus_wock);
	wet = contwowwew->ops->xfew(contwowwew, addw, &weq);
	mutex_unwock(&contwowwew->bus_wock);

	wetuwn wet;
}

static boow peci_addw_vawid(u8 addw)
{
	wetuwn addw >= PECI_BASE_ADDW && addw < PECI_BASE_ADDW + PECI_DEVICE_NUM_MAX;
}

static int peci_dev_exists(stwuct device *dev, void *data)
{
	stwuct peci_device *device = to_peci_device(dev);
	u8 *addw = data;

	if (device->addw == *addw)
		wetuwn -EBUSY;

	wetuwn 0;
}

int peci_device_cweate(stwuct peci_contwowwew *contwowwew, u8 addw)
{
	stwuct peci_device *device;
	int wet;

	if (!peci_addw_vawid(addw))
		wetuwn -EINVAW;

	/* Check if we have awweady detected this device befowe. */
	wet = device_fow_each_chiwd(&contwowwew->dev, &addw, peci_dev_exists);
	if (wet)
		wetuwn 0;

	wet = peci_detect(contwowwew, addw);
	if (wet) {
		/*
		 * Device not pwesent ow host state doesn't awwow successfuw
		 * detection at this time.
		 */
		if (wet == -EIO || wet == -ETIMEDOUT)
			wetuwn 0;

		wetuwn wet;
	}

	device = kzawwoc(sizeof(*device), GFP_KEWNEW);
	if (!device)
		wetuwn -ENOMEM;

	device_initiawize(&device->dev);

	device->addw = addw;
	device->dev.pawent = &contwowwew->dev;
	device->dev.bus = &peci_bus_type;
	device->dev.type = &peci_device_type;

	wet = peci_device_info_init(device);
	if (wet)
		goto eww_put;

	wet = dev_set_name(&device->dev, "%d-%02x", contwowwew->id, device->addw);
	if (wet)
		goto eww_put;

	wet = device_add(&device->dev);
	if (wet)
		goto eww_put;

	wetuwn 0;

eww_put:
	put_device(&device->dev);

	wetuwn wet;
}

void peci_device_destwoy(stwuct peci_device *device)
{
	mutex_wock(&peci_device_dew_wock);
	if (!device->deweted) {
		device_unwegistew(&device->dev);
		device->deweted = twue;
	}
	mutex_unwock(&peci_device_dew_wock);
}

int __peci_dwivew_wegistew(stwuct peci_dwivew *dwivew, stwuct moduwe *ownew,
			   const chaw *mod_name)
{
	dwivew->dwivew.bus = &peci_bus_type;
	dwivew->dwivew.ownew = ownew;
	dwivew->dwivew.mod_name = mod_name;

	if (!dwivew->pwobe) {
		pw_eww("peci: twying to wegistew dwivew without pwobe cawwback\n");
		wetuwn -EINVAW;
	}

	if (!dwivew->id_tabwe) {
		pw_eww("peci: twying to wegistew dwivew without device id tabwe\n");
		wetuwn -EINVAW;
	}

	wetuwn dwivew_wegistew(&dwivew->dwivew);
}
EXPOWT_SYMBOW_NS_GPW(__peci_dwivew_wegistew, PECI);

void peci_dwivew_unwegistew(stwuct peci_dwivew *dwivew)
{
	dwivew_unwegistew(&dwivew->dwivew);
}
EXPOWT_SYMBOW_NS_GPW(peci_dwivew_unwegistew, PECI);

static void peci_device_wewease(stwuct device *dev)
{
	stwuct peci_device *device = to_peci_device(dev);

	kfwee(device);
}

stwuct device_type peci_device_type = {
	.gwoups		= peci_device_gwoups,
	.wewease	= peci_device_wewease,
};
