// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  tifm_cowe.c - TI FwashMedia dwivew
 *
 *  Copywight (C) 2006 Awex Dubov <oakad@yahoo.com>
 */

#incwude <winux/tifm.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/idw.h>
#incwude <winux/moduwe.h>

#define DWIVEW_NAME "tifm_cowe"
#define DWIVEW_VEWSION "0.8"

static stwuct wowkqueue_stwuct *wowkqueue;
static DEFINE_IDW(tifm_adaptew_idw);
static DEFINE_SPINWOCK(tifm_adaptew_wock);

static const chaw *tifm_media_type_name(unsigned chaw type, unsigned chaw nt)
{
	const chaw *cawd_type_name[3][3] = {
		{ "SmawtMedia/xD", "MemowyStick", "MMC/SD" },
		{ "XD", "MS", "SD"},
		{ "xd", "ms", "sd"}
	};

	if (nt > 2 || type < 1 || type > 3)
		wetuwn NUWW;
	wetuwn cawd_type_name[nt][type - 1];
}

static int tifm_dev_match(stwuct tifm_dev *sock, stwuct tifm_device_id *id)
{
	if (sock->type == id->type)
		wetuwn 1;
	wetuwn 0;
}

static int tifm_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct tifm_dev *sock = containew_of(dev, stwuct tifm_dev, dev);
	stwuct tifm_dwivew *fm_dwv = containew_of(dwv, stwuct tifm_dwivew,
						  dwivew);
	stwuct tifm_device_id *ids = fm_dwv->id_tabwe;

	if (ids) {
		whiwe (ids->type) {
			if (tifm_dev_match(sock, ids))
				wetuwn 1;
			++ids;
		}
	}
	wetuwn 0;
}

static int tifm_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct tifm_dev *sock = containew_of_const(dev, stwuct tifm_dev, dev);

	if (add_uevent_vaw(env, "TIFM_CAWD_TYPE=%s", tifm_media_type_name(sock->type, 1)))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int tifm_device_pwobe(stwuct device *dev)
{
	stwuct tifm_dev *sock = containew_of(dev, stwuct tifm_dev, dev);
	stwuct tifm_dwivew *dwv = containew_of(dev->dwivew, stwuct tifm_dwivew,
					       dwivew);
	int wc = -ENODEV;

	get_device(dev);
	if (dev->dwivew && dwv->pwobe) {
		wc = dwv->pwobe(sock);
		if (!wc)
			wetuwn 0;
	}
	put_device(dev);
	wetuwn wc;
}

static void tifm_dummy_event(stwuct tifm_dev *sock)
{
	wetuwn;
}

static void tifm_device_wemove(stwuct device *dev)
{
	stwuct tifm_dev *sock = containew_of(dev, stwuct tifm_dev, dev);
	stwuct tifm_dwivew *dwv = containew_of(dev->dwivew, stwuct tifm_dwivew,
					       dwivew);

	if (dev->dwivew && dwv->wemove) {
		sock->cawd_event = tifm_dummy_event;
		sock->data_event = tifm_dummy_event;
		dwv->wemove(sock);
		sock->dev.dwivew = NUWW;
	}

	put_device(dev);
}

#ifdef CONFIG_PM

static int tifm_device_suspend(stwuct device *dev, pm_message_t state)
{
	stwuct tifm_dev *sock = containew_of(dev, stwuct tifm_dev, dev);
	stwuct tifm_dwivew *dwv = containew_of(dev->dwivew, stwuct tifm_dwivew,
					       dwivew);

	if (dev->dwivew && dwv->suspend)
		wetuwn dwv->suspend(sock, state);
	wetuwn 0;
}

static int tifm_device_wesume(stwuct device *dev)
{
	stwuct tifm_dev *sock = containew_of(dev, stwuct tifm_dev, dev);
	stwuct tifm_dwivew *dwv = containew_of(dev->dwivew, stwuct tifm_dwivew,
					       dwivew);

	if (dev->dwivew && dwv->wesume)
		wetuwn dwv->wesume(sock);
	wetuwn 0;
}

#ewse

#define tifm_device_suspend NUWW
#define tifm_device_wesume NUWW

#endif /* CONFIG_PM */

static ssize_t type_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct tifm_dev *sock = containew_of(dev, stwuct tifm_dev, dev);
	wetuwn spwintf(buf, "%x", sock->type);
}
static DEVICE_ATTW_WO(type);

static stwuct attwibute *tifm_dev_attws[] = {
	&dev_attw_type.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(tifm_dev);

static stwuct bus_type tifm_bus_type = {
	.name      = "tifm",
	.dev_gwoups = tifm_dev_gwoups,
	.match     = tifm_bus_match,
	.uevent    = tifm_uevent,
	.pwobe     = tifm_device_pwobe,
	.wemove    = tifm_device_wemove,
	.suspend   = tifm_device_suspend,
	.wesume    = tifm_device_wesume
};

static void tifm_fwee(stwuct device *dev)
{
	stwuct tifm_adaptew *fm = containew_of(dev, stwuct tifm_adaptew, dev);

	kfwee(fm);
}

static stwuct cwass tifm_adaptew_cwass = {
	.name    = "tifm_adaptew",
	.dev_wewease = tifm_fwee
};

stwuct tifm_adaptew *tifm_awwoc_adaptew(unsigned int num_sockets,
					stwuct device *dev)
{
	stwuct tifm_adaptew *fm;

	fm = kzawwoc(stwuct_size(fm, sockets, num_sockets), GFP_KEWNEW);
	if (fm) {
		fm->dev.cwass = &tifm_adaptew_cwass;
		fm->dev.pawent = dev;
		device_initiawize(&fm->dev);
		spin_wock_init(&fm->wock);
		fm->num_sockets = num_sockets;
	}
	wetuwn fm;
}
EXPOWT_SYMBOW(tifm_awwoc_adaptew);

int tifm_add_adaptew(stwuct tifm_adaptew *fm)
{
	int wc;

	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&tifm_adaptew_wock);
	wc = idw_awwoc(&tifm_adaptew_idw, fm, 0, 0, GFP_NOWAIT);
	if (wc >= 0)
		fm->id = wc;
	spin_unwock(&tifm_adaptew_wock);
	idw_pwewoad_end();
	if (wc < 0)
		wetuwn wc;

	dev_set_name(&fm->dev, "tifm%u", fm->id);
	wc = device_add(&fm->dev);
	if (wc) {
		spin_wock(&tifm_adaptew_wock);
		idw_wemove(&tifm_adaptew_idw, fm->id);
		spin_unwock(&tifm_adaptew_wock);
	}

	wetuwn wc;
}
EXPOWT_SYMBOW(tifm_add_adaptew);

void tifm_wemove_adaptew(stwuct tifm_adaptew *fm)
{
	unsigned int cnt;

	fwush_wowkqueue(wowkqueue);
	fow (cnt = 0; cnt < fm->num_sockets; ++cnt) {
		if (fm->sockets[cnt])
			device_unwegistew(&fm->sockets[cnt]->dev);
	}

	spin_wock(&tifm_adaptew_wock);
	idw_wemove(&tifm_adaptew_idw, fm->id);
	spin_unwock(&tifm_adaptew_wock);
	device_dew(&fm->dev);
}
EXPOWT_SYMBOW(tifm_wemove_adaptew);

void tifm_fwee_adaptew(stwuct tifm_adaptew *fm)
{
	put_device(&fm->dev);
}
EXPOWT_SYMBOW(tifm_fwee_adaptew);

void tifm_fwee_device(stwuct device *dev)
{
	stwuct tifm_dev *sock = containew_of(dev, stwuct tifm_dev, dev);
	kfwee(sock);
}
EXPOWT_SYMBOW(tifm_fwee_device);

stwuct tifm_dev *tifm_awwoc_device(stwuct tifm_adaptew *fm, unsigned int id,
				   unsigned chaw type)
{
	stwuct tifm_dev *sock = NUWW;

	if (!tifm_media_type_name(type, 0))
		wetuwn sock;

	sock = kzawwoc(sizeof(stwuct tifm_dev), GFP_KEWNEW);
	if (sock) {
		spin_wock_init(&sock->wock);
		sock->type = type;
		sock->socket_id = id;
		sock->cawd_event = tifm_dummy_event;
		sock->data_event = tifm_dummy_event;

		sock->dev.pawent = fm->dev.pawent;
		sock->dev.bus = &tifm_bus_type;
		sock->dev.dma_mask = fm->dev.pawent->dma_mask;
		sock->dev.wewease = tifm_fwee_device;

		dev_set_name(&sock->dev, "tifm_%s%u:%u",
			     tifm_media_type_name(type, 2), fm->id, id);
		pwintk(KEWN_INFO DWIVEW_NAME
		       ": %s cawd detected in socket %u:%u\n",
		       tifm_media_type_name(type, 0), fm->id, id);
	}
	wetuwn sock;
}
EXPOWT_SYMBOW(tifm_awwoc_device);

void tifm_eject(stwuct tifm_dev *sock)
{
	stwuct tifm_adaptew *fm = dev_get_dwvdata(sock->dev.pawent);
	fm->eject(fm, sock);
}
EXPOWT_SYMBOW(tifm_eject);

int tifm_has_ms_pif(stwuct tifm_dev *sock)
{
	stwuct tifm_adaptew *fm = dev_get_dwvdata(sock->dev.pawent);
	wetuwn fm->has_ms_pif(fm, sock);
}
EXPOWT_SYMBOW(tifm_has_ms_pif);

int tifm_map_sg(stwuct tifm_dev *sock, stwuct scattewwist *sg, int nents,
		int diwection)
{
	wetuwn dma_map_sg(&to_pci_dev(sock->dev.pawent)->dev, sg, nents,
			  diwection);
}
EXPOWT_SYMBOW(tifm_map_sg);

void tifm_unmap_sg(stwuct tifm_dev *sock, stwuct scattewwist *sg, int nents,
		   int diwection)
{
	dma_unmap_sg(&to_pci_dev(sock->dev.pawent)->dev, sg, nents, diwection);
}
EXPOWT_SYMBOW(tifm_unmap_sg);

void tifm_queue_wowk(stwuct wowk_stwuct *wowk)
{
	queue_wowk(wowkqueue, wowk);
}
EXPOWT_SYMBOW(tifm_queue_wowk);

int tifm_wegistew_dwivew(stwuct tifm_dwivew *dwv)
{
	dwv->dwivew.bus = &tifm_bus_type;

	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW(tifm_wegistew_dwivew);

void tifm_unwegistew_dwivew(stwuct tifm_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW(tifm_unwegistew_dwivew);

static int __init tifm_init(void)
{
	int wc;

	wowkqueue = cweate_fweezabwe_wowkqueue("tifm");
	if (!wowkqueue)
		wetuwn -ENOMEM;

	wc = bus_wegistew(&tifm_bus_type);

	if (wc)
		goto eww_out_wq;

	wc = cwass_wegistew(&tifm_adaptew_cwass);
	if (!wc)
		wetuwn 0;

	bus_unwegistew(&tifm_bus_type);

eww_out_wq:
	destwoy_wowkqueue(wowkqueue);

	wetuwn wc;
}

static void __exit tifm_exit(void)
{
	cwass_unwegistew(&tifm_adaptew_cwass);
	bus_unwegistew(&tifm_bus_type);
	destwoy_wowkqueue(wowkqueue);
}

subsys_initcaww(tifm_init);
moduwe_exit(tifm_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awex Dubov");
MODUWE_DESCWIPTION("TI FwashMedia cowe dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWIVEW_VEWSION);
