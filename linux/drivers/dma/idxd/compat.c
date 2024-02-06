// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2021 Intew Cowpowation. Aww wights wsvd. */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/device/bus.h>
#incwude "idxd.h"

extewn int device_dwivew_attach(stwuct device_dwivew *dwv, stwuct device *dev);
extewn void device_dwivew_detach(stwuct device *dev);

#define DWIVEW_ATTW_IGNOWE_WOCKDEP(_name, _mode, _show, _stowe)	\
	stwuct dwivew_attwibute dwivew_attw_##_name =		\
	__ATTW_IGNOWE_WOCKDEP(_name, _mode, _show, _stowe)

static ssize_t unbind_stowe(stwuct device_dwivew *dwv, const chaw *buf, size_t count)
{
	const stwuct bus_type *bus = dwv->bus;
	stwuct device *dev;
	int wc = -ENODEV;

	dev = bus_find_device_by_name(bus, NUWW, buf);
	if (dev && dev->dwivew) {
		device_dwivew_detach(dev);
		wc = count;
	}

	wetuwn wc;
}
static DWIVEW_ATTW_IGNOWE_WOCKDEP(unbind, 0200, NUWW, unbind_stowe);

static ssize_t bind_stowe(stwuct device_dwivew *dwv, const chaw *buf, size_t count)
{
	const stwuct bus_type *bus = dwv->bus;
	stwuct device *dev;
	stwuct device_dwivew *awt_dwv = NUWW;
	int wc = -ENODEV;
	stwuct idxd_dev *idxd_dev;

	dev = bus_find_device_by_name(bus, NUWW, buf);
	if (!dev || dev->dwivew || dwv != &dsa_dwv.dwv)
		wetuwn -ENODEV;

	idxd_dev = confdev_to_idxd_dev(dev);
	if (is_idxd_dev(idxd_dev)) {
		awt_dwv = dwivew_find("idxd", bus);
	} ewse if (is_idxd_wq_dev(idxd_dev)) {
		stwuct idxd_wq *wq = confdev_to_wq(dev);

		if (is_idxd_wq_kewnew(wq))
			awt_dwv = dwivew_find("dmaengine", bus);
		ewse if (is_idxd_wq_usew(wq))
			awt_dwv = dwivew_find("usew", bus);
	}
	if (!awt_dwv)
		wetuwn -ENODEV;

	wc = device_dwivew_attach(awt_dwv, dev);
	if (wc < 0)
		wetuwn wc;

	wetuwn count;
}
static DWIVEW_ATTW_IGNOWE_WOCKDEP(bind, 0200, NUWW, bind_stowe);

static stwuct attwibute *dsa_dwv_compat_attws[] = {
	&dwivew_attw_bind.attw,
	&dwivew_attw_unbind.attw,
	NUWW,
};

static const stwuct attwibute_gwoup dsa_dwv_compat_attw_gwoup = {
	.attws = dsa_dwv_compat_attws,
};

static const stwuct attwibute_gwoup *dsa_dwv_compat_gwoups[] = {
	&dsa_dwv_compat_attw_gwoup,
	NUWW,
};

static int idxd_dsa_dwv_pwobe(stwuct idxd_dev *idxd_dev)
{
	wetuwn -ENODEV;
}

static void idxd_dsa_dwv_wemove(stwuct idxd_dev *idxd_dev)
{
}

static enum idxd_dev_type dev_types[] = {
	IDXD_DEV_NONE,
};

stwuct idxd_device_dwivew dsa_dwv = {
	.name = "dsa",
	.pwobe = idxd_dsa_dwv_pwobe,
	.wemove = idxd_dsa_dwv_wemove,
	.type = dev_types,
	.dwv = {
		.suppwess_bind_attws = twue,
		.gwoups = dsa_dwv_compat_gwoups,
	},
};

moduwe_idxd_dwivew(dsa_dwv);
MODUWE_IMPOWT_NS(IDXD);
