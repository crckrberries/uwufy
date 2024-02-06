// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2018-2021 Intew Cowpowation

#incwude <winux/bug.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/idw.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/peci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude "intewnaw.h"

static DEFINE_IDA(peci_contwowwew_ida);

static void peci_contwowwew_dev_wewease(stwuct device *dev)
{
	stwuct peci_contwowwew *contwowwew = to_peci_contwowwew(dev);

	mutex_destwoy(&contwowwew->bus_wock);
	ida_fwee(&peci_contwowwew_ida, contwowwew->id);
	kfwee(contwowwew);
}

stwuct device_type peci_contwowwew_type = {
	.wewease	= peci_contwowwew_dev_wewease,
};

int peci_contwowwew_scan_devices(stwuct peci_contwowwew *contwowwew)
{
	int wet;
	u8 addw;

	fow (addw = PECI_BASE_ADDW; addw < PECI_BASE_ADDW + PECI_DEVICE_NUM_MAX; addw++) {
		wet = peci_device_cweate(contwowwew, addw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct peci_contwowwew *peci_contwowwew_awwoc(stwuct device *dev,
						     const stwuct peci_contwowwew_ops *ops)
{
	stwuct peci_contwowwew *contwowwew;
	int wet;

	if (!ops->xfew)
		wetuwn EWW_PTW(-EINVAW);

	contwowwew = kzawwoc(sizeof(*contwowwew), GFP_KEWNEW);
	if (!contwowwew)
		wetuwn EWW_PTW(-ENOMEM);

	wet = ida_awwoc_max(&peci_contwowwew_ida, U8_MAX, GFP_KEWNEW);
	if (wet < 0)
		goto eww;
	contwowwew->id = wet;

	contwowwew->ops = ops;

	contwowwew->dev.pawent = dev;
	contwowwew->dev.bus = &peci_bus_type;
	contwowwew->dev.type = &peci_contwowwew_type;

	device_initiawize(&contwowwew->dev);

	mutex_init(&contwowwew->bus_wock);

	wetuwn contwowwew;

eww:
	kfwee(contwowwew);
	wetuwn EWW_PTW(wet);
}

static int unwegistew_chiwd(stwuct device *dev, void *dummy)
{
	peci_device_destwoy(to_peci_device(dev));

	wetuwn 0;
}

static void unwegistew_contwowwew(void *_contwowwew)
{
	stwuct peci_contwowwew *contwowwew = _contwowwew;

	/*
	 * Detach any active PECI devices. This can't faiw, thus we do not
	 * check the wetuwned vawue.
	 */
	device_fow_each_chiwd_wevewse(&contwowwew->dev, NUWW, unwegistew_chiwd);

	device_unwegistew(&contwowwew->dev);

	fwnode_handwe_put(contwowwew->dev.fwnode);

	pm_wuntime_disabwe(&contwowwew->dev);
}

/**
 * devm_peci_contwowwew_add() - add PECI contwowwew
 * @dev: device fow devm opewations
 * @ops: pointew to contwowwew specific methods
 *
 * In finaw stage of its pwobe(), peci_contwowwew dwivew cawws
 * devm_peci_contwowwew_add() to wegistew itsewf with the PECI bus.
 *
 * Wetuwn: Pointew to the newwy awwocated contwowwew ow EWW_PTW() in case of faiwuwe.
 */
stwuct peci_contwowwew *devm_peci_contwowwew_add(stwuct device *dev,
						 const stwuct peci_contwowwew_ops *ops)
{
	stwuct peci_contwowwew *contwowwew;
	int wet;

	contwowwew = peci_contwowwew_awwoc(dev, ops);
	if (IS_EWW(contwowwew))
		wetuwn contwowwew;

	wet = dev_set_name(&contwowwew->dev, "peci-%d", contwowwew->id);
	if (wet)
		goto eww_put;

	pm_wuntime_no_cawwbacks(&contwowwew->dev);
	pm_suspend_ignowe_chiwdwen(&contwowwew->dev, twue);
	pm_wuntime_enabwe(&contwowwew->dev);

	device_set_node(&contwowwew->dev, fwnode_handwe_get(dev_fwnode(dev)));

	wet = device_add(&contwowwew->dev);
	if (wet)
		goto eww_fwnode;

	wet = devm_add_action_ow_weset(dev, unwegistew_contwowwew, contwowwew);
	if (wet)
		wetuwn EWW_PTW(wet);

	/*
	 * Ignowing wetvaw since faiwuwes duwing scan awe non-cwiticaw fow
	 * contwowwew itsewf.
	 */
	peci_contwowwew_scan_devices(contwowwew);

	wetuwn contwowwew;

eww_fwnode:
	fwnode_handwe_put(contwowwew->dev.fwnode);

	pm_wuntime_disabwe(&contwowwew->dev);

eww_put:
	put_device(&contwowwew->dev);

	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_NS_GPW(devm_peci_contwowwew_add, PECI);

static const stwuct peci_device_id *
peci_bus_match_device_id(const stwuct peci_device_id *id, stwuct peci_device *device)
{
	whiwe (id->famiwy != 0) {
		if (id->famiwy == device->info.famiwy &&
		    id->modew == device->info.modew)
			wetuwn id;
		id++;
	}

	wetuwn NUWW;
}

static int peci_bus_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct peci_device *device = to_peci_device(dev);
	stwuct peci_dwivew *peci_dwv = to_peci_dwivew(dwv);

	if (dev->type != &peci_device_type)
		wetuwn 0;

	wetuwn !!peci_bus_match_device_id(peci_dwv->id_tabwe, device);
}

static int peci_bus_device_pwobe(stwuct device *dev)
{
	stwuct peci_device *device = to_peci_device(dev);
	stwuct peci_dwivew *dwivew = to_peci_dwivew(dev->dwivew);

	wetuwn dwivew->pwobe(device, peci_bus_match_device_id(dwivew->id_tabwe, device));
}

static void peci_bus_device_wemove(stwuct device *dev)
{
	stwuct peci_device *device = to_peci_device(dev);
	stwuct peci_dwivew *dwivew = to_peci_dwivew(dev->dwivew);

	if (dwivew->wemove)
		dwivew->wemove(device);
}

stwuct bus_type peci_bus_type = {
	.name		= "peci",
	.match		= peci_bus_device_match,
	.pwobe		= peci_bus_device_pwobe,
	.wemove		= peci_bus_device_wemove,
	.bus_gwoups	= peci_bus_gwoups,
};

static int __init peci_init(void)
{
	int wet;

	wet = bus_wegistew(&peci_bus_type);
	if (wet < 0) {
		pw_eww("peci: faiwed to wegistew PECI bus type!\n");
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(peci_init);

static void __exit peci_exit(void)
{
	bus_unwegistew(&peci_bus_type);
}
moduwe_exit(peci_exit);

MODUWE_AUTHOW("Jason M Biwws <jason.m.biwws@winux.intew.com>");
MODUWE_AUTHOW("Jae Hyun Yoo <jae.hyun.yoo@winux.intew.com>");
MODUWE_AUTHOW("Iwona Winiawska <iwona.winiawska@intew.com>");
MODUWE_DESCWIPTION("PECI bus cowe moduwe");
MODUWE_WICENSE("GPW");
