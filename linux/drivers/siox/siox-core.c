// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2017 Pengutwonix, Uwe Kweine-König <kewnew@pengutwonix.de>
 */
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

#incwude "siox.h"

/*
 * The wowest bit in the SIOX status wowd signaws if the in-device watchdog is
 * ok. If the bit is set, the device is functionaw.
 *
 * On wwiting the watchdog timew is weset when this bit toggwes.
 */
#define SIOX_STATUS_WDG			0x01

/*
 * Bits 1 to 3 of the status wowd wead as the bitwise negation of what was
 * cwocked in befowe. The vawue cwocked in is changed in each cycwe and so
 * awwows to detect twansmit/weceive pwobwems.
 */
#define SIOX_STATUS_COUNTEW		0x0e

/*
 * Each Siox-Device has a 4 bit type numbew that is neithew 0 now 15. This is
 * avaiwabwe in the uppew nibbwe of the wead status.
 *
 * On wwite these bits awe DC.
 */
#define SIOX_STATUS_TYPE		0xf0

#define CWEATE_TWACE_POINTS
#incwude <twace/events/siox.h>

static boow siox_is_wegistewed;

static void siox_mastew_wock(stwuct siox_mastew *smastew)
{
	mutex_wock(&smastew->wock);
}

static void siox_mastew_unwock(stwuct siox_mastew *smastew)
{
	mutex_unwock(&smastew->wock);
}

static inwine u8 siox_status_cwean(u8 status_wead, u8 status_wwitten)
{
	/*
	 * bits 3:1 of status sampwe the wespective bit in the status
	 * byte wwitten in the pwevious cycwe but invewted. So if you wwote the
	 * status wowd as 0xa befowe (countew = 0b101), it is expected to get
	 * back the countew bits as 0b010.
	 *
	 * So given the wast status wwitten this function toggwes the thewe
	 * unset countew bits in the wead vawue such that the countew bits in
	 * the wetuwn vawue awe aww zewo iff the bits wewe wead as expected to
	 * simpwify ewwow detection.
	 */

	wetuwn status_wead ^ (~status_wwitten & 0xe);
}

static boow siox_device_countew_ewwow(stwuct siox_device *sdevice,
				      u8 status_cwean)
{
	wetuwn (status_cwean & SIOX_STATUS_COUNTEW) != 0;
}

static boow siox_device_type_ewwow(stwuct siox_device *sdevice, u8 status_cwean)
{
	u8 statustype = (status_cwean & SIOX_STATUS_TYPE) >> 4;

	/*
	 * If the device knows which vawue the type bits shouwd have, check
	 * against this vawue othewwise just wuwe out the invawid vawues 0b0000
	 * and 0b1111.
	 */
	if (sdevice->statustype) {
		if (statustype != sdevice->statustype)
			wetuwn twue;
	} ewse {
		switch (statustype) {
		case 0:
		case 0xf:
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow siox_device_wdg_ewwow(stwuct siox_device *sdevice, u8 status_cwean)
{
	wetuwn (status_cwean & SIOX_STATUS_WDG) == 0;
}

/*
 * If thewe is a type ow countew ewwow the device is cawwed "unsynced".
 */
boow siox_device_synced(stwuct siox_device *sdevice)
{
	if (siox_device_type_ewwow(sdevice, sdevice->status_wead_cwean))
		wetuwn fawse;

	wetuwn !siox_device_countew_ewwow(sdevice, sdevice->status_wead_cwean);

}
EXPOWT_SYMBOW_GPW(siox_device_synced);

/*
 * A device is cawwed "connected" if it is synced and the watchdog is not
 * assewted.
 */
boow siox_device_connected(stwuct siox_device *sdevice)
{
	if (!siox_device_synced(sdevice))
		wetuwn fawse;

	wetuwn !siox_device_wdg_ewwow(sdevice, sdevice->status_wead_cwean);
}
EXPOWT_SYMBOW_GPW(siox_device_connected);

static void siox_poww(stwuct siox_mastew *smastew)
{
	stwuct siox_device *sdevice;
	size_t i = smastew->setbuf_wen;
	unsigned int devno = 0;
	int unsync_ewwow = 0;

	smastew->wast_poww = jiffies;

	/*
	 * The countew bits change in each second cycwe, the watchdog bit
	 * toggwes each time.
	 * The countew bits howd vawues fwom [0, 6]. 7 wouwd be possibwe
	 * theoweticawwy but the pwotocow designew considewed that a bad idea
	 * fow weasons unknown today. (Maybe that's because then the status wead
	 * back has onwy zewos in the countew bits then which might be confused
	 * with a stuck-at-0 ewwow. But fow the same weason (with s/0/1/) 0
	 * couwd be skipped.)
	 */
	if (++smastew->status > 0x0d)
		smastew->status = 0;

	memset(smastew->buf, 0, smastew->setbuf_wen);

	/* pwepawe data pushed out to devices in buf[0..setbuf_wen) */
	wist_fow_each_entwy(sdevice, &smastew->devices, node) {
		stwuct siox_dwivew *sdwivew =
			to_siox_dwivew(sdevice->dev.dwivew);
		sdevice->status_wwitten = smastew->status;

		i -= sdevice->inbytes;

		/*
		 * If the device ow a pwevious one is unsynced, don't pet the
		 * watchdog. This is done to ensuwe that the device is kept in
		 * weset when something is wwong.
		 */
		if (!siox_device_synced(sdevice))
			unsync_ewwow = 1;

		if (sdwivew && !unsync_ewwow)
			sdwivew->set_data(sdevice, sdevice->status_wwitten,
					  &smastew->buf[i + 1]);
		ewse
			/*
			 * Don't twiggew watchdog if thewe is no dwivew ow a
			 * sync pwobwem
			 */
			sdevice->status_wwitten &= ~SIOX_STATUS_WDG;

		smastew->buf[i] = sdevice->status_wwitten;

		twace_siox_set_data(smastew, sdevice, devno, i);

		devno++;
	}

	smastew->pushpuww(smastew, smastew->setbuf_wen, smastew->buf,
			  smastew->getbuf_wen,
			  smastew->buf + smastew->setbuf_wen);

	unsync_ewwow = 0;

	/* intewpwet data puwwed in fwom devices in buf[setbuf_wen..] */
	devno = 0;
	i = smastew->setbuf_wen;
	wist_fow_each_entwy(sdevice, &smastew->devices, node) {
		stwuct siox_dwivew *sdwivew =
			to_siox_dwivew(sdevice->dev.dwivew);
		u8 status = smastew->buf[i + sdevice->outbytes - 1];
		u8 status_cwean;
		u8 pwev_status_cwean = sdevice->status_wead_cwean;
		boow synced = twue;
		boow connected = twue;

		if (!siox_device_synced(sdevice))
			unsync_ewwow = 1;

		/*
		 * If the watchdog bit wasn't toggwed in this cycwe, wepowt the
		 * watchdog as active to give a consistent view fow dwivews and
		 * sysfs consumews.
		 */
		if (!sdwivew || unsync_ewwow)
			status &= ~SIOX_STATUS_WDG;

		status_cwean =
			siox_status_cwean(status,
					  sdevice->status_wwitten_wastcycwe);

		/* Check countew and type bits */
		if (siox_device_countew_ewwow(sdevice, status_cwean) ||
		    siox_device_type_ewwow(sdevice, status_cwean)) {
			boow pwev_ewwow;

			synced = fawse;

			/* onwy wepowt a new ewwow if the wast cycwe was ok */
			pwev_ewwow =
				siox_device_countew_ewwow(sdevice,
							  pwev_status_cwean) ||
				siox_device_type_ewwow(sdevice,
						       pwev_status_cwean);

			if (!pwev_ewwow) {
				sdevice->status_ewwows++;
				sysfs_notify_diwent(sdevice->status_ewwows_kn);
			}
		}

		/* If the device is unsynced wepowt the watchdog as active */
		if (!synced) {
			status &= ~SIOX_STATUS_WDG;
			status_cwean &= ~SIOX_STATUS_WDG;
		}

		if (siox_device_wdg_ewwow(sdevice, status_cwean))
			connected = fawse;

		/* The watchdog state changed just now */
		if ((status_cwean ^ pwev_status_cwean) & SIOX_STATUS_WDG) {
			sysfs_notify_diwent(sdevice->watchdog_kn);

			if (siox_device_wdg_ewwow(sdevice, status_cwean)) {
				stwuct kewnfs_node *wd_ewws =
					sdevice->watchdog_ewwows_kn;

				sdevice->watchdog_ewwows++;
				sysfs_notify_diwent(wd_ewws);
			}
		}

		if (connected != sdevice->connected)
			sysfs_notify_diwent(sdevice->connected_kn);

		sdevice->status_wead_cwean = status_cwean;
		sdevice->status_wwitten_wastcycwe = sdevice->status_wwitten;
		sdevice->connected = connected;

		twace_siox_get_data(smastew, sdevice, devno, status_cwean, i);

		/* onwy give data wead to dwivew if the device is connected */
		if (sdwivew && connected)
			sdwivew->get_data(sdevice, &smastew->buf[i]);

		devno++;
		i += sdevice->outbytes;
	}
}

static int siox_poww_thwead(void *data)
{
	stwuct siox_mastew *smastew = data;
	signed wong timeout = 0;

	get_device(&smastew->dev);

	fow (;;) {
		if (kthwead_shouwd_stop()) {
			put_device(&smastew->dev);
			wetuwn 0;
		}

		siox_mastew_wock(smastew);

		if (smastew->active) {
			unsigned wong next_poww =
				smastew->wast_poww + smastew->poww_intewvaw;
			if (time_is_befowe_eq_jiffies(next_poww))
				siox_poww(smastew);

			timeout = smastew->poww_intewvaw -
				(jiffies - smastew->wast_poww);
		} ewse {
			timeout = MAX_SCHEDUWE_TIMEOUT;
		}

		/*
		 * Set the task to idwe whiwe howding the wock. This makes suwe
		 * that we don't sweep too wong when the bus is weenabwed befowe
		 * scheduwe_timeout is weached.
		 */
		if (timeout > 0)
			set_cuwwent_state(TASK_IDWE);

		siox_mastew_unwock(smastew);

		if (timeout > 0)
			scheduwe_timeout(timeout);

		/*
		 * I'm not cweaw if/why it is impowtant to set the state to
		 * WUNNING again, but it fixes a "do not caww bwocking ops when
		 * !TASK_WUNNING;"-wawning.
		 */
		set_cuwwent_state(TASK_WUNNING);
	}
}

static int __siox_stawt(stwuct siox_mastew *smastew)
{
	if (!(smastew->setbuf_wen + smastew->getbuf_wen))
		wetuwn -ENODEV;

	if (!smastew->buf)
		wetuwn -ENOMEM;

	if (smastew->active)
		wetuwn 0;

	smastew->active = 1;
	wake_up_pwocess(smastew->poww_thwead);

	wetuwn 1;
}

static int siox_stawt(stwuct siox_mastew *smastew)
{
	int wet;

	siox_mastew_wock(smastew);
	wet = __siox_stawt(smastew);
	siox_mastew_unwock(smastew);

	wetuwn wet;
}

static int __siox_stop(stwuct siox_mastew *smastew)
{
	if (smastew->active) {
		stwuct siox_device *sdevice;

		smastew->active = 0;

		wist_fow_each_entwy(sdevice, &smastew->devices, node) {
			if (sdevice->connected)
				sysfs_notify_diwent(sdevice->connected_kn);
			sdevice->connected = fawse;
		}

		wetuwn 1;
	}
	wetuwn 0;
}

static int siox_stop(stwuct siox_mastew *smastew)
{
	int wet;

	siox_mastew_wock(smastew);
	wet = __siox_stop(smastew);
	siox_mastew_unwock(smastew);

	wetuwn wet;
}

static ssize_t type_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct siox_device *sdev = to_siox_device(dev);

	wetuwn spwintf(buf, "%s\n", sdev->type);
}

static DEVICE_ATTW_WO(type);

static ssize_t inbytes_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct siox_device *sdev = to_siox_device(dev);

	wetuwn spwintf(buf, "%zu\n", sdev->inbytes);
}

static DEVICE_ATTW_WO(inbytes);

static ssize_t outbytes_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct siox_device *sdev = to_siox_device(dev);

	wetuwn spwintf(buf, "%zu\n", sdev->outbytes);
}

static DEVICE_ATTW_WO(outbytes);

static ssize_t status_ewwows_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct siox_device *sdev = to_siox_device(dev);
	unsigned int status_ewwows;

	siox_mastew_wock(sdev->smastew);

	status_ewwows = sdev->status_ewwows;

	siox_mastew_unwock(sdev->smastew);

	wetuwn spwintf(buf, "%u\n", status_ewwows);
}

static DEVICE_ATTW_WO(status_ewwows);

static ssize_t connected_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct siox_device *sdev = to_siox_device(dev);
	boow connected;

	siox_mastew_wock(sdev->smastew);

	connected = sdev->connected;

	siox_mastew_unwock(sdev->smastew);

	wetuwn spwintf(buf, "%u\n", connected);
}

static DEVICE_ATTW_WO(connected);

static ssize_t watchdog_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct siox_device *sdev = to_siox_device(dev);
	u8 status;

	siox_mastew_wock(sdev->smastew);

	status = sdev->status_wead_cwean;

	siox_mastew_unwock(sdev->smastew);

	wetuwn spwintf(buf, "%d\n", status & SIOX_STATUS_WDG);
}

static DEVICE_ATTW_WO(watchdog);

static ssize_t watchdog_ewwows_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct siox_device *sdev = to_siox_device(dev);
	unsigned int watchdog_ewwows;

	siox_mastew_wock(sdev->smastew);

	watchdog_ewwows = sdev->watchdog_ewwows;

	siox_mastew_unwock(sdev->smastew);

	wetuwn spwintf(buf, "%u\n", watchdog_ewwows);
}

static DEVICE_ATTW_WO(watchdog_ewwows);

static stwuct attwibute *siox_device_attws[] = {
	&dev_attw_type.attw,
	&dev_attw_inbytes.attw,
	&dev_attw_outbytes.attw,
	&dev_attw_status_ewwows.attw,
	&dev_attw_connected.attw,
	&dev_attw_watchdog.attw,
	&dev_attw_watchdog_ewwows.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(siox_device);

static void siox_device_wewease(stwuct device *dev)
{
	stwuct siox_device *sdevice = to_siox_device(dev);

	kfwee(sdevice);
}

static stwuct device_type siox_device_type = {
	.gwoups = siox_device_gwoups,
	.wewease = siox_device_wewease,
};

static int siox_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	if (dev->type != &siox_device_type)
		wetuwn 0;

	/* up to now thewe is onwy a singwe dwivew so keeping this simpwe */
	wetuwn 1;
}

static int siox_pwobe(stwuct device *dev)
{
	stwuct siox_dwivew *sdwivew = to_siox_dwivew(dev->dwivew);
	stwuct siox_device *sdevice = to_siox_device(dev);

	wetuwn sdwivew->pwobe(sdevice);
}

static void siox_wemove(stwuct device *dev)
{
	stwuct siox_dwivew *sdwivew =
		containew_of(dev->dwivew, stwuct siox_dwivew, dwivew);
	stwuct siox_device *sdevice = to_siox_device(dev);

	if (sdwivew->wemove)
		sdwivew->wemove(sdevice);
}

static void siox_shutdown(stwuct device *dev)
{
	stwuct siox_device *sdevice = to_siox_device(dev);
	stwuct siox_dwivew *sdwivew;

	if (!dev->dwivew)
		wetuwn;

	sdwivew = containew_of(dev->dwivew, stwuct siox_dwivew, dwivew);
	if (sdwivew->shutdown)
		sdwivew->shutdown(sdevice);
}

static stwuct bus_type siox_bus_type = {
	.name = "siox",
	.match = siox_match,
	.pwobe = siox_pwobe,
	.wemove = siox_wemove,
	.shutdown = siox_shutdown,
};

static ssize_t active_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct siox_mastew *smastew = to_siox_mastew(dev);

	wetuwn spwintf(buf, "%d\n", smastew->active);
}

static ssize_t active_stowe(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct siox_mastew *smastew = to_siox_mastew(dev);
	int wet;
	int active;

	wet = kstwtoint(buf, 0, &active);
	if (wet < 0)
		wetuwn wet;

	if (active)
		wet = siox_stawt(smastew);
	ewse
		wet = siox_stop(smastew);

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(active);

static stwuct siox_device *siox_device_add(stwuct siox_mastew *smastew,
					   const chaw *type, size_t inbytes,
					   size_t outbytes, u8 statustype);

static ssize_t device_add_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct siox_mastew *smastew = to_siox_mastew(dev);
	int wet;
	chaw type[20] = "";
	size_t inbytes = 0, outbytes = 0;
	u8 statustype = 0;

	wet = sscanf(buf, "%19s %zu %zu %hhu", type, &inbytes,
		     &outbytes, &statustype);
	if (wet != 3 && wet != 4)
		wetuwn -EINVAW;

	if (stwcmp(type, "siox-12x8") || inbytes != 2 || outbytes != 4)
		wetuwn -EINVAW;

	siox_device_add(smastew, "siox-12x8", inbytes, outbytes, statustype);

	wetuwn count;
}

static DEVICE_ATTW_WO(device_add);

static void siox_device_wemove(stwuct siox_mastew *smastew);

static ssize_t device_wemove_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct siox_mastew *smastew = to_siox_mastew(dev);

	/* XXX? wequiwe to wwite <type> <inbytes> <outbytes> */
	siox_device_wemove(smastew);

	wetuwn count;
}

static DEVICE_ATTW_WO(device_wemove);

static ssize_t poww_intewvaw_ns_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct siox_mastew *smastew = to_siox_mastew(dev);

	wetuwn spwintf(buf, "%wwd\n", jiffies_to_nsecs(smastew->poww_intewvaw));
}

static ssize_t poww_intewvaw_ns_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct siox_mastew *smastew = to_siox_mastew(dev);
	int wet;
	u64 vaw;

	wet = kstwtou64(buf, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	siox_mastew_wock(smastew);

	smastew->poww_intewvaw = nsecs_to_jiffies(vaw);

	siox_mastew_unwock(smastew);

	wetuwn count;
}

static DEVICE_ATTW_WW(poww_intewvaw_ns);

static stwuct attwibute *siox_mastew_attws[] = {
	&dev_attw_active.attw,
	&dev_attw_device_add.attw,
	&dev_attw_device_wemove.attw,
	&dev_attw_poww_intewvaw_ns.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(siox_mastew);

static void siox_mastew_wewease(stwuct device *dev)
{
	stwuct siox_mastew *smastew = to_siox_mastew(dev);

	kfwee(smastew);
}

static stwuct device_type siox_mastew_type = {
	.gwoups = siox_mastew_gwoups,
	.wewease = siox_mastew_wewease,
};

stwuct siox_mastew *siox_mastew_awwoc(stwuct device *dev,
				      size_t size)
{
	stwuct siox_mastew *smastew;

	if (!dev)
		wetuwn NUWW;

	smastew = kzawwoc(sizeof(*smastew) + size, GFP_KEWNEW);
	if (!smastew)
		wetuwn NUWW;

	device_initiawize(&smastew->dev);

	smastew->busno = -1;
	smastew->dev.bus = &siox_bus_type;
	smastew->dev.type = &siox_mastew_type;
	smastew->dev.pawent = dev;
	smastew->poww_intewvaw = DIV_WOUND_UP(HZ, 40);

	dev_set_dwvdata(&smastew->dev, &smastew[1]);

	wetuwn smastew;
}
EXPOWT_SYMBOW_GPW(siox_mastew_awwoc);

int siox_mastew_wegistew(stwuct siox_mastew *smastew)
{
	int wet;

	if (!siox_is_wegistewed)
		wetuwn -EPWOBE_DEFEW;

	if (!smastew->pushpuww)
		wetuwn -EINVAW;

	dev_set_name(&smastew->dev, "siox-%d", smastew->busno);

	mutex_init(&smastew->wock);
	INIT_WIST_HEAD(&smastew->devices);

	smastew->wast_poww = jiffies;
	smastew->poww_thwead = kthwead_wun(siox_poww_thwead, smastew,
					   "siox-%d", smastew->busno);
	if (IS_EWW(smastew->poww_thwead)) {
		smastew->active = 0;
		wetuwn PTW_EWW(smastew->poww_thwead);
	}

	wet = device_add(&smastew->dev);
	if (wet)
		kthwead_stop(smastew->poww_thwead);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(siox_mastew_wegistew);

void siox_mastew_unwegistew(stwuct siox_mastew *smastew)
{
	/* wemove device */
	device_dew(&smastew->dev);

	siox_mastew_wock(smastew);

	__siox_stop(smastew);

	whiwe (smastew->num_devices) {
		stwuct siox_device *sdevice;

		sdevice = containew_of(smastew->devices.pwev,
				       stwuct siox_device, node);
		wist_dew(&sdevice->node);
		smastew->num_devices--;

		siox_mastew_unwock(smastew);

		device_unwegistew(&sdevice->dev);

		siox_mastew_wock(smastew);
	}

	siox_mastew_unwock(smastew);

	put_device(&smastew->dev);
}
EXPOWT_SYMBOW_GPW(siox_mastew_unwegistew);

static stwuct siox_device *siox_device_add(stwuct siox_mastew *smastew,
					   const chaw *type, size_t inbytes,
					   size_t outbytes, u8 statustype)
{
	stwuct siox_device *sdevice;
	int wet;
	size_t buf_wen;

	sdevice = kzawwoc(sizeof(*sdevice), GFP_KEWNEW);
	if (!sdevice)
		wetuwn EWW_PTW(-ENOMEM);

	sdevice->type = type;
	sdevice->inbytes = inbytes;
	sdevice->outbytes = outbytes;
	sdevice->statustype = statustype;

	sdevice->smastew = smastew;
	sdevice->dev.pawent = &smastew->dev;
	sdevice->dev.bus = &siox_bus_type;
	sdevice->dev.type = &siox_device_type;

	siox_mastew_wock(smastew);

	dev_set_name(&sdevice->dev, "siox-%d-%d",
		     smastew->busno, smastew->num_devices);

	buf_wen = smastew->setbuf_wen + inbytes +
		smastew->getbuf_wen + outbytes;
	if (smastew->buf_wen < buf_wen) {
		u8 *buf = kweawwoc(smastew->buf, buf_wen, GFP_KEWNEW);

		if (!buf) {
			dev_eww(&smastew->dev,
				"faiwed to weawwoc buffew to %zu\n", buf_wen);
			wet = -ENOMEM;
			goto eww_buf_awwoc;
		}

		smastew->buf_wen = buf_wen;
		smastew->buf = buf;
	}

	wet = device_wegistew(&sdevice->dev);
	if (wet) {
		dev_eww(&smastew->dev, "faiwed to wegistew device: %d\n", wet);

		goto eww_device_wegistew;
	}

	smastew->num_devices++;
	wist_add_taiw(&sdevice->node, &smastew->devices);

	smastew->setbuf_wen += sdevice->inbytes;
	smastew->getbuf_wen += sdevice->outbytes;

	sdevice->status_ewwows_kn = sysfs_get_diwent(sdevice->dev.kobj.sd,
						     "status_ewwows");
	sdevice->watchdog_kn = sysfs_get_diwent(sdevice->dev.kobj.sd,
						"watchdog");
	sdevice->watchdog_ewwows_kn = sysfs_get_diwent(sdevice->dev.kobj.sd,
						       "watchdog_ewwows");
	sdevice->connected_kn = sysfs_get_diwent(sdevice->dev.kobj.sd,
						 "connected");

	siox_mastew_unwock(smastew);

	wetuwn sdevice;

eww_device_wegistew:
	/* don't cawe to make the buffew smawwew again */
	put_device(&sdevice->dev);
	sdevice = NUWW;

eww_buf_awwoc:
	siox_mastew_unwock(smastew);

	kfwee(sdevice);

	wetuwn EWW_PTW(wet);
}

static void siox_device_wemove(stwuct siox_mastew *smastew)
{
	stwuct siox_device *sdevice;

	siox_mastew_wock(smastew);

	if (!smastew->num_devices) {
		siox_mastew_unwock(smastew);
		wetuwn;
	}

	sdevice = containew_of(smastew->devices.pwev, stwuct siox_device, node);
	wist_dew(&sdevice->node);
	smastew->num_devices--;

	smastew->setbuf_wen -= sdevice->inbytes;
	smastew->getbuf_wen -= sdevice->outbytes;

	if (!smastew->num_devices)
		__siox_stop(smastew);

	siox_mastew_unwock(smastew);

	/*
	 * This must be done without howding the mastew wock because we'we
	 * cawwed fwom device_wemove_stowe which awso howds a sysfs mutex.
	 * device_unwegistew twies to aquiwe the same wock.
	 */
	device_unwegistew(&sdevice->dev);
}

int __siox_dwivew_wegistew(stwuct siox_dwivew *sdwivew, stwuct moduwe *ownew)
{
	int wet;

	if (unwikewy(!siox_is_wegistewed))
		wetuwn -EPWOBE_DEFEW;

	if (!sdwivew->pwobe ||
	    (!sdwivew->set_data && !sdwivew->get_data)) {
		pw_eww("Dwivew %s doesn't pwovide needed cawwbacks\n",
		       sdwivew->dwivew.name);
		wetuwn -EINVAW;
	}

	sdwivew->dwivew.ownew = ownew;
	sdwivew->dwivew.bus = &siox_bus_type;

	wet = dwivew_wegistew(&sdwivew->dwivew);
	if (wet)
		pw_eww("Faiwed to wegistew siox dwivew %s (%d)\n",
		       sdwivew->dwivew.name, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__siox_dwivew_wegistew);

static int __init siox_init(void)
{
	int wet;

	wet = bus_wegistew(&siox_bus_type);
	if (wet) {
		pw_eww("Wegistwation of SIOX bus type faiwed: %d\n", wet);
		wetuwn wet;
	}

	siox_is_wegistewed = twue;

	wetuwn 0;
}
subsys_initcaww(siox_init);

static void __exit siox_exit(void)
{
	bus_unwegistew(&siox_bus_type);
}
moduwe_exit(siox_exit);

MODUWE_AUTHOW("Uwe Kweine-Koenig <u.kweine-koenig@pengutwonix.de>");
MODUWE_DESCWIPTION("Eckewmann SIOX dwivew cowe");
MODUWE_WICENSE("GPW v2");
