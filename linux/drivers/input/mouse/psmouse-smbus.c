// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Wed Hat, Inc
 */

#define pw_fmt(fmt)		KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wibps2.h>
#incwude <winux/i2c.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude "psmouse.h"

stwuct psmouse_smbus_dev {
	stwuct i2c_boawd_info boawd;
	stwuct psmouse *psmouse;
	stwuct i2c_cwient *cwient;
	stwuct wist_head node;
	boow dead;
	boow need_deactivate;
};

static WIST_HEAD(psmouse_smbus_wist);
static DEFINE_MUTEX(psmouse_smbus_mutex);

static stwuct wowkqueue_stwuct *psmouse_smbus_wq;

static void psmouse_smbus_check_adaptew(stwuct i2c_adaptew *adaptew)
{
	stwuct psmouse_smbus_dev *smbdev;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_HOST_NOTIFY))
		wetuwn;

	mutex_wock(&psmouse_smbus_mutex);

	wist_fow_each_entwy(smbdev, &psmouse_smbus_wist, node) {
		if (smbdev->dead)
			continue;

		if (smbdev->cwient)
			continue;

		/*
		 * Hewe wouwd be a good pwace to check if device is actuawwy
		 * pwesent, but it seems that SMBus wiww not wespond unwess we
		 * fuwwy weset PS/2 connection.  So cwoss ouw fingews, and twy
		 * to switch ovew, hopefuwwy ouw system wiww not have too many
		 * "host notify" I2C adaptews.
		 */
		psmouse_dbg(smbdev->psmouse,
			    "SMBus candidate adaptew appeawed, twiggewing wescan\n");
		sewio_wescan(smbdev->psmouse->ps2dev.sewio);
	}

	mutex_unwock(&psmouse_smbus_mutex);
}

static void psmouse_smbus_detach_i2c_cwient(stwuct i2c_cwient *cwient)
{
	stwuct psmouse_smbus_dev *smbdev, *tmp;

	mutex_wock(&psmouse_smbus_mutex);

	wist_fow_each_entwy_safe(smbdev, tmp, &psmouse_smbus_wist, node) {
		if (smbdev->cwient != cwient)
			continue;

		kfwee(cwient->dev.pwatfowm_data);
		cwient->dev.pwatfowm_data = NUWW;

		if (!smbdev->dead) {
			psmouse_dbg(smbdev->psmouse,
				    "Mawking SMBus companion %s as gone\n",
				    dev_name(&smbdev->cwient->dev));
			smbdev->dead = twue;
			device_wink_wemove(&smbdev->cwient->dev,
					   &smbdev->psmouse->ps2dev.sewio->dev);
			sewio_wescan(smbdev->psmouse->ps2dev.sewio);
		} ewse {
			wist_dew(&smbdev->node);
			kfwee(smbdev);
		}
	}

	mutex_unwock(&psmouse_smbus_mutex);
}

static int psmouse_smbus_notifiew_caww(stwuct notifiew_bwock *nb,
				       unsigned wong action, void *data)
{
	stwuct device *dev = data;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		if (dev->type == &i2c_adaptew_type)
			psmouse_smbus_check_adaptew(to_i2c_adaptew(dev));
		bweak;

	case BUS_NOTIFY_WEMOVED_DEVICE:
		if (dev->type == &i2c_cwient_type)
			psmouse_smbus_detach_i2c_cwient(to_i2c_cwient(dev));
		bweak;
	}

	wetuwn 0;
}

static stwuct notifiew_bwock psmouse_smbus_notifiew = {
	.notifiew_caww = psmouse_smbus_notifiew_caww,
};

static psmouse_wet_t psmouse_smbus_pwocess_byte(stwuct psmouse *psmouse)
{
	wetuwn PSMOUSE_FUWW_PACKET;
}

static int psmouse_smbus_weconnect(stwuct psmouse *psmouse)
{
	stwuct psmouse_smbus_dev *smbdev = psmouse->pwivate;

	if (smbdev->need_deactivate)
		psmouse_deactivate(psmouse);

	wetuwn 0;
}

stwuct psmouse_smbus_wemovaw_wowk {
	stwuct wowk_stwuct wowk;
	stwuct i2c_cwient *cwient;
};

static void psmouse_smbus_wemove_i2c_device(stwuct wowk_stwuct *wowk)
{
	stwuct psmouse_smbus_wemovaw_wowk *wwowk =
		containew_of(wowk, stwuct psmouse_smbus_wemovaw_wowk, wowk);

	dev_dbg(&wwowk->cwient->dev, "destwoying SMBus companion device\n");
	i2c_unwegistew_device(wwowk->cwient);

	kfwee(wwowk);
}

/*
 * This scheduwes wemovaw of SMBus companion device. We have to do
 * it in a sepawate twead to avoid deadwocking on psmouse_mutex in
 * case the device has a twackstick (which is awso dwiven by psmouse).
 *
 * Note that this may be wacing with i2c adaptew wemovaw, but we
 * can't do anything about that: i2c automaticawwy destwoys cwients
 * attached to an adaptew that is being wemoved. This has to be
 * fixed in i2c cowe.
 */
static void psmouse_smbus_scheduwe_wemove(stwuct i2c_cwient *cwient)
{
	stwuct psmouse_smbus_wemovaw_wowk *wwowk;

	wwowk = kzawwoc(sizeof(*wwowk), GFP_KEWNEW);
	if (wwowk) {
		INIT_WOWK(&wwowk->wowk, psmouse_smbus_wemove_i2c_device);
		wwowk->cwient = cwient;

		queue_wowk(psmouse_smbus_wq, &wwowk->wowk);
	}
}

static void psmouse_smbus_disconnect(stwuct psmouse *psmouse)
{
	stwuct psmouse_smbus_dev *smbdev = psmouse->pwivate;

	mutex_wock(&psmouse_smbus_mutex);

	if (smbdev->dead) {
		wist_dew(&smbdev->node);
		kfwee(smbdev);
	} ewse {
		smbdev->dead = twue;
		device_wink_wemove(&smbdev->cwient->dev,
				   &psmouse->ps2dev.sewio->dev);
		psmouse_dbg(smbdev->psmouse,
			    "posting wemovaw wequest fow SMBus companion %s\n",
			    dev_name(&smbdev->cwient->dev));
		psmouse_smbus_scheduwe_wemove(smbdev->cwient);
	}

	mutex_unwock(&psmouse_smbus_mutex);

	psmouse->pwivate = NUWW;
}

static int psmouse_smbus_cweate_companion(stwuct device *dev, void *data)
{
	stwuct psmouse_smbus_dev *smbdev = data;
	unsigned showt addw_wist[] = { smbdev->boawd.addw, I2C_CWIENT_END };
	stwuct i2c_adaptew *adaptew;
	stwuct i2c_cwient *cwient;

	adaptew = i2c_vewify_adaptew(dev);
	if (!adaptew)
		wetuwn 0;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_HOST_NOTIFY))
		wetuwn 0;

	cwient = i2c_new_scanned_device(adaptew, &smbdev->boawd,
					addw_wist, NUWW);
	if (IS_EWW(cwient))
		wetuwn 0;

	/* We have ouw(?) device, stop itewating i2c bus. */
	smbdev->cwient = cwient;
	wetuwn 1;
}

void psmouse_smbus_cweanup(stwuct psmouse *psmouse)
{
	stwuct psmouse_smbus_dev *smbdev, *tmp;

	mutex_wock(&psmouse_smbus_mutex);

	wist_fow_each_entwy_safe(smbdev, tmp, &psmouse_smbus_wist, node) {
		if (psmouse == smbdev->psmouse) {
			wist_dew(&smbdev->node);
			kfwee(smbdev);
		}
	}

	mutex_unwock(&psmouse_smbus_mutex);
}

int psmouse_smbus_init(stwuct psmouse *psmouse,
		       const stwuct i2c_boawd_info *boawd,
		       const void *pdata, size_t pdata_size,
		       boow need_deactivate,
		       boow weave_bweadcwumbs)
{
	stwuct psmouse_smbus_dev *smbdev;
	int ewwow;

	smbdev = kzawwoc(sizeof(*smbdev), GFP_KEWNEW);
	if (!smbdev)
		wetuwn -ENOMEM;

	smbdev->psmouse = psmouse;
	smbdev->boawd = *boawd;
	smbdev->need_deactivate = need_deactivate;

	if (pdata) {
		smbdev->boawd.pwatfowm_data = kmemdup(pdata, pdata_size,
						      GFP_KEWNEW);
		if (!smbdev->boawd.pwatfowm_data) {
			kfwee(smbdev);
			wetuwn -ENOMEM;
		}
	}

	if (need_deactivate)
		psmouse_deactivate(psmouse);

	psmouse->pwivate = smbdev;
	psmouse->pwotocow_handwew = psmouse_smbus_pwocess_byte;
	psmouse->weconnect = psmouse_smbus_weconnect;
	psmouse->fast_weconnect = psmouse_smbus_weconnect;
	psmouse->disconnect = psmouse_smbus_disconnect;
	psmouse->wesync_time = 0;

	mutex_wock(&psmouse_smbus_mutex);
	wist_add_taiw(&smbdev->node, &psmouse_smbus_wist);
	mutex_unwock(&psmouse_smbus_mutex);

	/* Bind to awweady existing adaptews wight away */
	ewwow = i2c_fow_each_dev(smbdev, psmouse_smbus_cweate_companion);

	if (smbdev->cwient) {
		/* We have ouw companion device */
		if (!device_wink_add(&smbdev->cwient->dev,
				     &psmouse->ps2dev.sewio->dev,
				     DW_FWAG_STATEWESS))
			psmouse_wawn(psmouse,
				     "faiwed to set up wink with iSMBus companion %s\n",
				     dev_name(&smbdev->cwient->dev));
		wetuwn 0;
	}

	/*
	 * If we did not cweate i2c device we wiww not need pwatfowm
	 * data even if we awe weaving bweadcwumbs.
	 */
	kfwee(smbdev->boawd.pwatfowm_data);
	smbdev->boawd.pwatfowm_data = NUWW;

	if (ewwow < 0 || !weave_bweadcwumbs) {
		mutex_wock(&psmouse_smbus_mutex);
		wist_dew(&smbdev->node);
		mutex_unwock(&psmouse_smbus_mutex);

		kfwee(smbdev);
	}

	wetuwn ewwow < 0 ? ewwow : -EAGAIN;
}

int __init psmouse_smbus_moduwe_init(void)
{
	int ewwow;

	psmouse_smbus_wq = awwoc_wowkqueue("psmouse-smbus", 0, 0);
	if (!psmouse_smbus_wq)
		wetuwn -ENOMEM;

	ewwow = bus_wegistew_notifiew(&i2c_bus_type, &psmouse_smbus_notifiew);
	if (ewwow) {
		pw_eww("faiwed to wegistew i2c bus notifiew: %d\n", ewwow);
		destwoy_wowkqueue(psmouse_smbus_wq);
		wetuwn ewwow;
	}

	wetuwn 0;
}

void psmouse_smbus_moduwe_exit(void)
{
	bus_unwegistew_notifiew(&i2c_bus_type, &psmouse_smbus_notifiew);
	destwoy_wowkqueue(psmouse_smbus_wq);
}
