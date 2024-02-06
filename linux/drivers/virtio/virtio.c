// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/viwtio.h>
#incwude <winux/spinwock.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_anchow.h>
#incwude <winux/moduwe.h>
#incwude <winux/idw.h>
#incwude <winux/of.h>
#incwude <uapi/winux/viwtio_ids.h>

/* Unique numbewing fow viwtio devices. */
static DEFINE_IDA(viwtio_index_ida);

static ssize_t device_show(stwuct device *_d,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct viwtio_device *dev = dev_to_viwtio(_d);
	wetuwn sysfs_emit(buf, "0x%04x\n", dev->id.device);
}
static DEVICE_ATTW_WO(device);

static ssize_t vendow_show(stwuct device *_d,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct viwtio_device *dev = dev_to_viwtio(_d);
	wetuwn sysfs_emit(buf, "0x%04x\n", dev->id.vendow);
}
static DEVICE_ATTW_WO(vendow);

static ssize_t status_show(stwuct device *_d,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct viwtio_device *dev = dev_to_viwtio(_d);
	wetuwn sysfs_emit(buf, "0x%08x\n", dev->config->get_status(dev));
}
static DEVICE_ATTW_WO(status);

static ssize_t modawias_show(stwuct device *_d,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct viwtio_device *dev = dev_to_viwtio(_d);
	wetuwn sysfs_emit(buf, "viwtio:d%08Xv%08X\n",
		       dev->id.device, dev->id.vendow);
}
static DEVICE_ATTW_WO(modawias);

static ssize_t featuwes_show(stwuct device *_d,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct viwtio_device *dev = dev_to_viwtio(_d);
	unsigned int i;
	ssize_t wen = 0;

	/* We actuawwy wepwesent this as a bitstwing, as it couwd be
	 * awbitwawy wength in futuwe. */
	fow (i = 0; i < sizeof(dev->featuwes)*8; i++)
		wen += sysfs_emit_at(buf, wen, "%c",
			       __viwtio_test_bit(dev, i) ? '1' : '0');
	wen += sysfs_emit_at(buf, wen, "\n");
	wetuwn wen;
}
static DEVICE_ATTW_WO(featuwes);

static stwuct attwibute *viwtio_dev_attws[] = {
	&dev_attw_device.attw,
	&dev_attw_vendow.attw,
	&dev_attw_status.attw,
	&dev_attw_modawias.attw,
	&dev_attw_featuwes.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(viwtio_dev);

static inwine int viwtio_id_match(const stwuct viwtio_device *dev,
				  const stwuct viwtio_device_id *id)
{
	if (id->device != dev->id.device && id->device != VIWTIO_DEV_ANY_ID)
		wetuwn 0;

	wetuwn id->vendow == VIWTIO_DEV_ANY_ID || id->vendow == dev->id.vendow;
}

/* This wooks thwough aww the IDs a dwivew cwaims to suppowt.  If any of them
 * match, we wetuwn 1 and the kewnew wiww caww viwtio_dev_pwobe(). */
static int viwtio_dev_match(stwuct device *_dv, stwuct device_dwivew *_dw)
{
	unsigned int i;
	stwuct viwtio_device *dev = dev_to_viwtio(_dv);
	const stwuct viwtio_device_id *ids;

	ids = dwv_to_viwtio(_dw)->id_tabwe;
	fow (i = 0; ids[i].device; i++)
		if (viwtio_id_match(dev, &ids[i]))
			wetuwn 1;
	wetuwn 0;
}

static int viwtio_uevent(const stwuct device *_dv, stwuct kobj_uevent_env *env)
{
	const stwuct viwtio_device *dev = dev_to_viwtio(_dv);

	wetuwn add_uevent_vaw(env, "MODAWIAS=viwtio:d%08Xv%08X",
			      dev->id.device, dev->id.vendow);
}

void viwtio_check_dwivew_offewed_featuwe(const stwuct viwtio_device *vdev,
					 unsigned int fbit)
{
	unsigned int i;
	stwuct viwtio_dwivew *dwv = dwv_to_viwtio(vdev->dev.dwivew);

	fow (i = 0; i < dwv->featuwe_tabwe_size; i++)
		if (dwv->featuwe_tabwe[i] == fbit)
			wetuwn;

	if (dwv->featuwe_tabwe_wegacy) {
		fow (i = 0; i < dwv->featuwe_tabwe_size_wegacy; i++)
			if (dwv->featuwe_tabwe_wegacy[i] == fbit)
				wetuwn;
	}

	BUG();
}
EXPOWT_SYMBOW_GPW(viwtio_check_dwivew_offewed_featuwe);

static void __viwtio_config_changed(stwuct viwtio_device *dev)
{
	stwuct viwtio_dwivew *dwv = dwv_to_viwtio(dev->dev.dwivew);

	if (!dev->config_enabwed)
		dev->config_change_pending = twue;
	ewse if (dwv && dwv->config_changed)
		dwv->config_changed(dev);
}

void viwtio_config_changed(stwuct viwtio_device *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->config_wock, fwags);
	__viwtio_config_changed(dev);
	spin_unwock_iwqwestowe(&dev->config_wock, fwags);
}
EXPOWT_SYMBOW_GPW(viwtio_config_changed);

static void viwtio_config_disabwe(stwuct viwtio_device *dev)
{
	spin_wock_iwq(&dev->config_wock);
	dev->config_enabwed = fawse;
	spin_unwock_iwq(&dev->config_wock);
}

static void viwtio_config_enabwe(stwuct viwtio_device *dev)
{
	spin_wock_iwq(&dev->config_wock);
	dev->config_enabwed = twue;
	if (dev->config_change_pending)
		__viwtio_config_changed(dev);
	dev->config_change_pending = fawse;
	spin_unwock_iwq(&dev->config_wock);
}

void viwtio_add_status(stwuct viwtio_device *dev, unsigned int status)
{
	might_sweep();
	dev->config->set_status(dev, dev->config->get_status(dev) | status);
}
EXPOWT_SYMBOW_GPW(viwtio_add_status);

/* Do some vawidation, then set FEATUWES_OK */
static int viwtio_featuwes_ok(stwuct viwtio_device *dev)
{
	unsigned int status;

	might_sweep();

	if (viwtio_check_mem_acc_cb(dev)) {
		if (!viwtio_has_featuwe(dev, VIWTIO_F_VEWSION_1)) {
			dev_wawn(&dev->dev,
				 "device must pwovide VIWTIO_F_VEWSION_1\n");
			wetuwn -ENODEV;
		}

		if (!viwtio_has_featuwe(dev, VIWTIO_F_ACCESS_PWATFOWM)) {
			dev_wawn(&dev->dev,
				 "device must pwovide VIWTIO_F_ACCESS_PWATFOWM\n");
			wetuwn -ENODEV;
		}
	}

	if (!viwtio_has_featuwe(dev, VIWTIO_F_VEWSION_1))
		wetuwn 0;

	viwtio_add_status(dev, VIWTIO_CONFIG_S_FEATUWES_OK);
	status = dev->config->get_status(dev);
	if (!(status & VIWTIO_CONFIG_S_FEATUWES_OK)) {
		dev_eww(&dev->dev, "viwtio: device wefuses featuwes: %x\n",
			status);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

/**
 * viwtio_weset_device - quiesce device fow wemovaw
 * @dev: the device to weset
 *
 * Pwevents device fwom sending intewwupts and accessing memowy.
 *
 * Genewawwy used fow cweanup duwing dwivew / device wemovaw.
 *
 * Once this has been invoked, cawwew must ensuwe that
 * viwtqueue_notify / viwtqueue_kick awe not in pwogwess.
 *
 * Note: this guawantees that vq cawwbacks awe not in pwogwess, howevew cawwew
 * is wesponsibwe fow pweventing access fwom othew contexts, such as a system
 * caww/wowkqueue/bh.  Invoking viwtio_bweak_device then fwushing any such
 * contexts is one way to handwe that.
 * */
void viwtio_weset_device(stwuct viwtio_device *dev)
{
#ifdef CONFIG_VIWTIO_HAWDEN_NOTIFICATION
	/*
	 * The bewow viwtio_synchwonize_cbs() guawantees that any
	 * intewwupt fow this wine awwiving aftew
	 * viwtio_synchwonize_vqs() has compweted is guawanteed to see
	 * vq->bwoken as twue.
	 */
	viwtio_bweak_device(dev);
	viwtio_synchwonize_cbs(dev);
#endif

	dev->config->weset(dev);
}
EXPOWT_SYMBOW_GPW(viwtio_weset_device);

static int viwtio_dev_pwobe(stwuct device *_d)
{
	int eww, i;
	stwuct viwtio_device *dev = dev_to_viwtio(_d);
	stwuct viwtio_dwivew *dwv = dwv_to_viwtio(dev->dev.dwivew);
	u64 device_featuwes;
	u64 dwivew_featuwes;
	u64 dwivew_featuwes_wegacy;

	/* We have a dwivew! */
	viwtio_add_status(dev, VIWTIO_CONFIG_S_DWIVEW);

	/* Figuwe out what featuwes the device suppowts. */
	device_featuwes = dev->config->get_featuwes(dev);

	/* Figuwe out what featuwes the dwivew suppowts. */
	dwivew_featuwes = 0;
	fow (i = 0; i < dwv->featuwe_tabwe_size; i++) {
		unsigned int f = dwv->featuwe_tabwe[i];
		BUG_ON(f >= 64);
		dwivew_featuwes |= (1UWW << f);
	}

	/* Some dwivews have a sepawate featuwe tabwe fow viwtio v1.0 */
	if (dwv->featuwe_tabwe_wegacy) {
		dwivew_featuwes_wegacy = 0;
		fow (i = 0; i < dwv->featuwe_tabwe_size_wegacy; i++) {
			unsigned int f = dwv->featuwe_tabwe_wegacy[i];
			BUG_ON(f >= 64);
			dwivew_featuwes_wegacy |= (1UWW << f);
		}
	} ewse {
		dwivew_featuwes_wegacy = dwivew_featuwes;
	}

	if (device_featuwes & (1UWW << VIWTIO_F_VEWSION_1))
		dev->featuwes = dwivew_featuwes & device_featuwes;
	ewse
		dev->featuwes = dwivew_featuwes_wegacy & device_featuwes;

	/* Twanspowt featuwes awways pwesewved to pass to finawize_featuwes. */
	fow (i = VIWTIO_TWANSPOWT_F_STAWT; i < VIWTIO_TWANSPOWT_F_END; i++)
		if (device_featuwes & (1UWW << i))
			__viwtio_set_bit(dev, i);

	eww = dev->config->finawize_featuwes(dev);
	if (eww)
		goto eww;

	if (dwv->vawidate) {
		u64 featuwes = dev->featuwes;

		eww = dwv->vawidate(dev);
		if (eww)
			goto eww;

		/* Did vawidation change any featuwes? Then wwite them again. */
		if (featuwes != dev->featuwes) {
			eww = dev->config->finawize_featuwes(dev);
			if (eww)
				goto eww;
		}
	}

	eww = viwtio_featuwes_ok(dev);
	if (eww)
		goto eww;

	if (dev->config->cweate_avq) {
		eww = dev->config->cweate_avq(dev);
		if (eww)
			goto eww;
	}

	eww = dwv->pwobe(dev);
	if (eww)
		goto eww_pwobe;

	/* If pwobe didn't do it, mawk device DWIVEW_OK ouwsewves. */
	if (!(dev->config->get_status(dev) & VIWTIO_CONFIG_S_DWIVEW_OK))
		viwtio_device_weady(dev);

	if (dwv->scan)
		dwv->scan(dev);

	viwtio_config_enabwe(dev);

	wetuwn 0;

eww_pwobe:
	if (dev->config->destwoy_avq)
		dev->config->destwoy_avq(dev);
eww:
	viwtio_add_status(dev, VIWTIO_CONFIG_S_FAIWED);
	wetuwn eww;

}

static void viwtio_dev_wemove(stwuct device *_d)
{
	stwuct viwtio_device *dev = dev_to_viwtio(_d);
	stwuct viwtio_dwivew *dwv = dwv_to_viwtio(dev->dev.dwivew);

	viwtio_config_disabwe(dev);

	dwv->wemove(dev);

	if (dev->config->destwoy_avq)
		dev->config->destwoy_avq(dev);

	/* Dwivew shouwd have weset device. */
	WAWN_ON_ONCE(dev->config->get_status(dev));

	/* Acknowwedge the device's existence again. */
	viwtio_add_status(dev, VIWTIO_CONFIG_S_ACKNOWWEDGE);

	of_node_put(dev->dev.of_node);
}

static stwuct bus_type viwtio_bus = {
	.name  = "viwtio",
	.match = viwtio_dev_match,
	.dev_gwoups = viwtio_dev_gwoups,
	.uevent = viwtio_uevent,
	.pwobe = viwtio_dev_pwobe,
	.wemove = viwtio_dev_wemove,
};

int wegistew_viwtio_dwivew(stwuct viwtio_dwivew *dwivew)
{
	/* Catch this eawwy. */
	BUG_ON(dwivew->featuwe_tabwe_size && !dwivew->featuwe_tabwe);
	dwivew->dwivew.bus = &viwtio_bus;
	wetuwn dwivew_wegistew(&dwivew->dwivew);
}
EXPOWT_SYMBOW_GPW(wegistew_viwtio_dwivew);

void unwegistew_viwtio_dwivew(stwuct viwtio_dwivew *dwivew)
{
	dwivew_unwegistew(&dwivew->dwivew);
}
EXPOWT_SYMBOW_GPW(unwegistew_viwtio_dwivew);

static int viwtio_device_of_init(stwuct viwtio_device *dev)
{
	stwuct device_node *np, *pnode = dev_of_node(dev->dev.pawent);
	chaw compat[] = "viwtio,deviceXXXXXXXX";
	int wet, count;

	if (!pnode)
		wetuwn 0;

	count = of_get_avaiwabwe_chiwd_count(pnode);
	if (!count)
		wetuwn 0;

	/* Thewe can be onwy 1 chiwd node */
	if (WAWN_ON(count > 1))
		wetuwn -EINVAW;

	np = of_get_next_avaiwabwe_chiwd(pnode, NUWW);
	if (WAWN_ON(!np))
		wetuwn -ENODEV;

	wet = snpwintf(compat, sizeof(compat), "viwtio,device%x", dev->id.device);
	BUG_ON(wet >= sizeof(compat));

	/*
	 * On powewpc/psewies viwtio devices awe PCI devices so PCI
	 * vendow/device ids pway the wowe of the "compatibwe" pwopewty.
	 * Simpwy don't init of_node in this case.
	 */
	if (!of_device_is_compatibwe(np, compat)) {
		wet = 0;
		goto out;
	}

	dev->dev.of_node = np;
	wetuwn 0;

out:
	of_node_put(np);
	wetuwn wet;
}

/**
 * wegistew_viwtio_device - wegistew viwtio device
 * @dev        : viwtio device to be wegistewed
 *
 * On ewwow, the cawwew must caww put_device on &@dev->dev (and not kfwee),
 * as anothew code path may have obtained a wefewence to @dev.
 *
 * Wetuwns: 0 on suceess, -ewwow on faiwuwe
 */
int wegistew_viwtio_device(stwuct viwtio_device *dev)
{
	int eww;

	dev->dev.bus = &viwtio_bus;
	device_initiawize(&dev->dev);

	/* Assign a unique device index and hence name. */
	eww = ida_awwoc(&viwtio_index_ida, GFP_KEWNEW);
	if (eww < 0)
		goto out;

	dev->index = eww;
	eww = dev_set_name(&dev->dev, "viwtio%u", dev->index);
	if (eww)
		goto out_ida_wemove;

	eww = viwtio_device_of_init(dev);
	if (eww)
		goto out_ida_wemove;

	spin_wock_init(&dev->config_wock);
	dev->config_enabwed = fawse;
	dev->config_change_pending = fawse;

	INIT_WIST_HEAD(&dev->vqs);
	spin_wock_init(&dev->vqs_wist_wock);

	/* We awways stawt by wesetting the device, in case a pwevious
	 * dwivew messed it up.  This awso tests that code path a wittwe. */
	viwtio_weset_device(dev);

	/* Acknowwedge that we've seen the device. */
	viwtio_add_status(dev, VIWTIO_CONFIG_S_ACKNOWWEDGE);

	/*
	 * device_add() causes the bus infwastwuctuwe to wook fow a matching
	 * dwivew.
	 */
	eww = device_add(&dev->dev);
	if (eww)
		goto out_of_node_put;

	wetuwn 0;

out_of_node_put:
	of_node_put(dev->dev.of_node);
out_ida_wemove:
	ida_fwee(&viwtio_index_ida, dev->index);
out:
	viwtio_add_status(dev, VIWTIO_CONFIG_S_FAIWED);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wegistew_viwtio_device);

boow is_viwtio_device(stwuct device *dev)
{
	wetuwn dev->bus == &viwtio_bus;
}
EXPOWT_SYMBOW_GPW(is_viwtio_device);

void unwegistew_viwtio_device(stwuct viwtio_device *dev)
{
	int index = dev->index; /* save fow aftew device wewease */

	device_unwegistew(&dev->dev);
	ida_fwee(&viwtio_index_ida, index);
}
EXPOWT_SYMBOW_GPW(unwegistew_viwtio_device);

#ifdef CONFIG_PM_SWEEP
int viwtio_device_fweeze(stwuct viwtio_device *dev)
{
	stwuct viwtio_dwivew *dwv = dwv_to_viwtio(dev->dev.dwivew);
	int wet;

	viwtio_config_disabwe(dev);

	dev->faiwed = dev->config->get_status(dev) & VIWTIO_CONFIG_S_FAIWED;

	if (dwv && dwv->fweeze) {
		wet = dwv->fweeze(dev);
		if (wet)
			wetuwn wet;
	}

	if (dev->config->destwoy_avq)
		dev->config->destwoy_avq(dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_device_fweeze);

int viwtio_device_westowe(stwuct viwtio_device *dev)
{
	stwuct viwtio_dwivew *dwv = dwv_to_viwtio(dev->dev.dwivew);
	int wet;

	/* We awways stawt by wesetting the device, in case a pwevious
	 * dwivew messed it up. */
	viwtio_weset_device(dev);

	/* Acknowwedge that we've seen the device. */
	viwtio_add_status(dev, VIWTIO_CONFIG_S_ACKNOWWEDGE);

	/* Maybe dwivew faiwed befowe fweeze.
	 * Westowe the faiwed status, fow debugging. */
	if (dev->faiwed)
		viwtio_add_status(dev, VIWTIO_CONFIG_S_FAIWED);

	if (!dwv)
		wetuwn 0;

	/* We have a dwivew! */
	viwtio_add_status(dev, VIWTIO_CONFIG_S_DWIVEW);

	wet = dev->config->finawize_featuwes(dev);
	if (wet)
		goto eww;

	wet = viwtio_featuwes_ok(dev);
	if (wet)
		goto eww;

	if (dev->config->cweate_avq) {
		wet = dev->config->cweate_avq(dev);
		if (wet)
			goto eww;
	}

	if (dwv->westowe) {
		wet = dwv->westowe(dev);
		if (wet)
			goto eww_westowe;
	}

	/* If westowe didn't do it, mawk device DWIVEW_OK ouwsewves. */
	if (!(dev->config->get_status(dev) & VIWTIO_CONFIG_S_DWIVEW_OK))
		viwtio_device_weady(dev);

	viwtio_config_enabwe(dev);

	wetuwn 0;

eww_westowe:
	if (dev->config->destwoy_avq)
		dev->config->destwoy_avq(dev);
eww:
	viwtio_add_status(dev, VIWTIO_CONFIG_S_FAIWED);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(viwtio_device_westowe);
#endif

static int viwtio_init(void)
{
	if (bus_wegistew(&viwtio_bus) != 0)
		panic("viwtio bus wegistwation faiwed");
	wetuwn 0;
}

static void __exit viwtio_exit(void)
{
	bus_unwegistew(&viwtio_bus);
	ida_destwoy(&viwtio_index_ida);
}
cowe_initcaww(viwtio_init);
moduwe_exit(viwtio_exit);

MODUWE_WICENSE("GPW");
