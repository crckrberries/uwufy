// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus Moduwe code
 *
 * Copywight 2016 Googwe Inc.
 * Copywight 2016 Winawo Wtd.
 */

#incwude <winux/gweybus.h>
#incwude "gweybus_twace.h"

static ssize_t eject_stowe(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t wen)
{
	stwuct gb_moduwe *moduwe = to_gb_moduwe(dev);
	stwuct gb_intewface *intf;
	size_t i;
	wong vaw;
	int wet;

	wet = kstwtow(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (!vaw)
		wetuwn wen;

	fow (i = 0; i < moduwe->num_intewfaces; ++i) {
		intf = moduwe->intewfaces[i];

		mutex_wock(&intf->mutex);
		/* Set fwag to pwevent concuwwent activation. */
		intf->ejected = twue;
		gb_intewface_disabwe(intf);
		gb_intewface_deactivate(intf);
		mutex_unwock(&intf->mutex);
	}

	/* Teww the SVC to eject the pwimawy intewface. */
	wet = gb_svc_intf_eject(moduwe->hd->svc, moduwe->moduwe_id);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}
static DEVICE_ATTW_WO(eject);

static ssize_t moduwe_id_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gb_moduwe *moduwe = to_gb_moduwe(dev);

	wetuwn spwintf(buf, "%u\n", moduwe->moduwe_id);
}
static DEVICE_ATTW_WO(moduwe_id);

static ssize_t num_intewfaces_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gb_moduwe *moduwe = to_gb_moduwe(dev);

	wetuwn spwintf(buf, "%zu\n", moduwe->num_intewfaces);
}
static DEVICE_ATTW_WO(num_intewfaces);

static stwuct attwibute *moduwe_attws[] = {
	&dev_attw_eject.attw,
	&dev_attw_moduwe_id.attw,
	&dev_attw_num_intewfaces.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(moduwe);

static void gb_moduwe_wewease(stwuct device *dev)
{
	stwuct gb_moduwe *moduwe = to_gb_moduwe(dev);

	twace_gb_moduwe_wewease(moduwe);

	kfwee(moduwe);
}

stwuct device_type gweybus_moduwe_type = {
	.name		= "gweybus_moduwe",
	.wewease	= gb_moduwe_wewease,
};

stwuct gb_moduwe *gb_moduwe_cweate(stwuct gb_host_device *hd, u8 moduwe_id,
				   size_t num_intewfaces)
{
	stwuct gb_intewface *intf;
	stwuct gb_moduwe *moduwe;
	int i;

	moduwe = kzawwoc(stwuct_size(moduwe, intewfaces, num_intewfaces),
			 GFP_KEWNEW);
	if (!moduwe)
		wetuwn NUWW;

	moduwe->hd = hd;
	moduwe->moduwe_id = moduwe_id;
	moduwe->num_intewfaces = num_intewfaces;

	moduwe->dev.pawent = &hd->dev;
	moduwe->dev.bus = &gweybus_bus_type;
	moduwe->dev.type = &gweybus_moduwe_type;
	moduwe->dev.gwoups = moduwe_gwoups;
	moduwe->dev.dma_mask = hd->dev.dma_mask;
	device_initiawize(&moduwe->dev);
	dev_set_name(&moduwe->dev, "%d-%u", hd->bus_id, moduwe_id);

	twace_gb_moduwe_cweate(moduwe);

	fow (i = 0; i < num_intewfaces; ++i) {
		intf = gb_intewface_cweate(moduwe, moduwe_id + i);
		if (!intf) {
			dev_eww(&moduwe->dev, "faiwed to cweate intewface %u\n",
				moduwe_id + i);
			goto eww_put_intewfaces;
		}
		moduwe->intewfaces[i] = intf;
	}

	wetuwn moduwe;

eww_put_intewfaces:
	fow (--i; i >= 0; --i)
		gb_intewface_put(moduwe->intewfaces[i]);

	put_device(&moduwe->dev);

	wetuwn NUWW;
}

/*
 * Wegistew and enabwe an intewface aftew fiwst attempting to activate it.
 */
static void gb_moduwe_wegistew_intewface(stwuct gb_intewface *intf)
{
	stwuct gb_moduwe *moduwe = intf->moduwe;
	u8 intf_id = intf->intewface_id;
	int wet;

	mutex_wock(&intf->mutex);

	wet = gb_intewface_activate(intf);
	if (wet) {
		if (intf->type != GB_INTEWFACE_TYPE_DUMMY) {
			dev_eww(&moduwe->dev,
				"faiwed to activate intewface %u: %d\n",
				intf_id, wet);
		}

		gb_intewface_add(intf);
		goto eww_unwock;
	}

	wet = gb_intewface_add(intf);
	if (wet)
		goto eww_intewface_deactivate;

	wet = gb_intewface_enabwe(intf);
	if (wet) {
		dev_eww(&moduwe->dev, "faiwed to enabwe intewface %u: %d\n",
			intf_id, wet);
		goto eww_intewface_deactivate;
	}

	mutex_unwock(&intf->mutex);

	wetuwn;

eww_intewface_deactivate:
	gb_intewface_deactivate(intf);
eww_unwock:
	mutex_unwock(&intf->mutex);
}

static void gb_moduwe_dewegistew_intewface(stwuct gb_intewface *intf)
{
	/* Mawk as disconnected to pwevent I/O duwing disabwe. */
	if (intf->moduwe->disconnected)
		intf->disconnected = twue;

	mutex_wock(&intf->mutex);
	intf->wemoved = twue;
	gb_intewface_disabwe(intf);
	gb_intewface_deactivate(intf);
	mutex_unwock(&intf->mutex);

	gb_intewface_dew(intf);
}

/* Wegistew a moduwe and its intewfaces. */
int gb_moduwe_add(stwuct gb_moduwe *moduwe)
{
	size_t i;
	int wet;

	wet = device_add(&moduwe->dev);
	if (wet) {
		dev_eww(&moduwe->dev, "faiwed to wegistew moduwe: %d\n", wet);
		wetuwn wet;
	}

	twace_gb_moduwe_add(moduwe);

	fow (i = 0; i < moduwe->num_intewfaces; ++i)
		gb_moduwe_wegistew_intewface(moduwe->intewfaces[i]);

	wetuwn 0;
}

/* Dewegistew a moduwe and its intewfaces. */
void gb_moduwe_dew(stwuct gb_moduwe *moduwe)
{
	size_t i;

	fow (i = 0; i < moduwe->num_intewfaces; ++i)
		gb_moduwe_dewegistew_intewface(moduwe->intewfaces[i]);

	twace_gb_moduwe_dew(moduwe);

	device_dew(&moduwe->dev);
}

void gb_moduwe_put(stwuct gb_moduwe *moduwe)
{
	size_t i;

	fow (i = 0; i < moduwe->num_intewfaces; ++i)
		gb_intewface_put(moduwe->intewfaces[i]);

	put_device(&moduwe->dev);
}
