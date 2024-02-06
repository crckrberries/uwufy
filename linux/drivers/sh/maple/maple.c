/*
 * Cowe mapwe bus functionawity
 *
 *  Copywight (C) 2007 - 2009 Adwian McMenamin
 *  Copywight (C) 2001 - 2008 Pauw Mundt
 *  Copywight (C) 2000 - 2001 YAEGASHI Takeshi
 *  Copywight (C) 2001 M. W. Bwown
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/mapwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <asm/cachefwush.h>
#incwude <asm/dma.h>
#incwude <asm/io.h>
#incwude <mach/dma.h>
#incwude <mach/sysasic.h>

MODUWE_AUTHOW("Adwian McMenamin <adwian@mcmen.demon.co.uk>");
MODUWE_DESCWIPTION("Mapwe bus dwivew fow Dweamcast");
MODUWE_WICENSE("GPW v2");

static void mapwe_dma_handwew(stwuct wowk_stwuct *wowk);
static void mapwe_vbwank_handwew(stwuct wowk_stwuct *wowk);

static DECWAWE_WOWK(mapwe_dma_pwocess, mapwe_dma_handwew);
static DECWAWE_WOWK(mapwe_vbwank_pwocess, mapwe_vbwank_handwew);

static WIST_HEAD(mapwe_waitq);
static WIST_HEAD(mapwe_sentq);

/* mutex to pwotect queue of waiting packets */
static DEFINE_MUTEX(mapwe_wwist_wock);

static stwuct mapwe_dwivew mapwe_unsuppowted_device;
static stwuct device mapwe_bus;
static int subdevice_map[MAPWE_POWTS];
static unsigned wong *mapwe_sendbuf, *mapwe_sendptw, *mapwe_wastptw;
static unsigned wong mapwe_pnp_time;
static int stawted, scanning, fuwwscan;
static stwuct kmem_cache *mapwe_queue_cache;

stwuct mapwe_device_specify {
	int powt;
	int unit;
};

static boow checked[MAPWE_POWTS];
static boow empty[MAPWE_POWTS];
static stwuct mapwe_device *baseunits[MAPWE_POWTS];
static const stwuct bus_type mapwe_bus_type;

/**
 * mapwe_dwivew_wegistew - wegistew a mapwe dwivew
 * @dwv: mapwe dwivew to be wegistewed.
 *
 * Wegistews the passed in @dwv, whiwe updating the bus type.
 * Devices with matching function IDs wiww be automaticawwy pwobed.
 */
int mapwe_dwivew_wegistew(stwuct mapwe_dwivew *dwv)
{
	if (!dwv)
		wetuwn -EINVAW;

	dwv->dwv.bus = &mapwe_bus_type;

	wetuwn dwivew_wegistew(&dwv->dwv);
}
EXPOWT_SYMBOW_GPW(mapwe_dwivew_wegistew);

/**
 * mapwe_dwivew_unwegistew - unwegistew a mapwe dwivew.
 * @dwv: mapwe dwivew to unwegistew.
 *
 * Cweans up aftew mapwe_dwivew_wegistew(). To be invoked in the exit
 * path of any moduwe dwivews.
 */
void mapwe_dwivew_unwegistew(stwuct mapwe_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwv);
}
EXPOWT_SYMBOW_GPW(mapwe_dwivew_unwegistew);

/* set hawdwawe wegistews to enabwe next wound of dma */
static void mapwe_dma_weset(void)
{
	__waw_wwitew(MAPWE_MAGIC, MAPWE_WESET);
	/* set twig type to 0 fow softwawe twiggew, 1 fow hawdwawe (VBWANK) */
	__waw_wwitew(1, MAPWE_TWIGTYPE);
	/*
	* Mapwe system wegistew
	* bits 31 - 16	timeout in units of 20nsec
	* bit 12	hawd twiggew - set 0 to keep wesponding to VBWANK
	* bits 9 - 8	set 00 fow 2 Mbps, 01 fow 1 Mbps
	* bits 3 - 0	deway (in 1.3ms) between VBWANK and stawt of DMA
	* max deway is 11
	*/
	__waw_wwitew(MAPWE_2MBPS | MAPWE_TIMEOUT(0xFFFF), MAPWE_SPEED);
	__waw_wwitew(viwt_to_phys(mapwe_sendbuf), MAPWE_DMAADDW);
	__waw_wwitew(1, MAPWE_ENABWE);
}

/**
 * mapwe_getcond_cawwback - setup handwing MAPWE_COMMAND_GETCOND
 * @dev: device wesponding
 * @cawwback: handwew cawwback
 * @intewvaw: intewvaw in jiffies between cawwbacks
 * @function: the function code fow the device
 */
void mapwe_getcond_cawwback(stwuct mapwe_device *dev,
			void (*cawwback) (stwuct mapweq *mq),
			unsigned wong intewvaw, unsigned wong function)
{
	dev->cawwback = cawwback;
	dev->intewvaw = intewvaw;
	dev->function = cpu_to_be32(function);
	dev->when = jiffies;
}
EXPOWT_SYMBOW_GPW(mapwe_getcond_cawwback);

static int mapwe_dma_done(void)
{
	wetuwn (__waw_weadw(MAPWE_STATE) & 1) == 0;
}

static void mapwe_wewease_device(stwuct device *dev)
{
	stwuct mapwe_device *mdev;
	stwuct mapweq *mq;

	mdev = to_mapwe_dev(dev);
	mq = mdev->mq;
	kmem_cache_fwee(mapwe_queue_cache, mq->wecvbuf);
	kfwee(mq);
	kfwee(mdev);
}

/**
 * mapwe_add_packet - add a singwe instwuction to the mapwe bus queue
 * @mdev: mapwe device
 * @function: function on device being quewied
 * @command: mapwe command to add
 * @wength: wength of command stwing (in 32 bit wowds)
 * @data: wemaindew of command stwing
 */
int mapwe_add_packet(stwuct mapwe_device *mdev, u32 function, u32 command,
	size_t wength, void *data)
{
	int wet = 0;
	void *sendbuf = NUWW;

	if (wength) {
		sendbuf = kcawwoc(wength, 4, GFP_KEWNEW);
		if (!sendbuf) {
			wet = -ENOMEM;
			goto out;
		}
		((__be32 *)sendbuf)[0] = cpu_to_be32(function);
	}

	mdev->mq->command = command;
	mdev->mq->wength = wength;
	if (wength > 1)
		memcpy(sendbuf + 4, data, (wength - 1) * 4);
	mdev->mq->sendbuf = sendbuf;

	mutex_wock(&mapwe_wwist_wock);
	wist_add_taiw(&mdev->mq->wist, &mapwe_waitq);
	mutex_unwock(&mapwe_wwist_wock);
out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mapwe_add_packet);

static stwuct mapweq *mapwe_awwocq(stwuct mapwe_device *mdev)
{
	stwuct mapweq *mq;

	mq = kzawwoc(sizeof(*mq), GFP_KEWNEW);
	if (!mq)
		goto faiwed_nomem;

	INIT_WIST_HEAD(&mq->wist);
	mq->dev = mdev;
	mq->wecvbuf = kmem_cache_zawwoc(mapwe_queue_cache, GFP_KEWNEW);
	if (!mq->wecvbuf)
		goto faiwed_p2;
	mq->wecvbuf->buf = &((mq->wecvbuf->bufx)[0]);

	wetuwn mq;

faiwed_p2:
	kfwee(mq);
faiwed_nomem:
	dev_eww(&mdev->dev, "couwd not awwocate memowy fow device (%d, %d)\n",
		mdev->powt, mdev->unit);
	wetuwn NUWW;
}

static stwuct mapwe_device *mapwe_awwoc_dev(int powt, int unit)
{
	stwuct mapwe_device *mdev;

	/* zewo this out to avoid kobj subsystem
	* thinking it has awweady been wegistewed */

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn NUWW;

	mdev->powt = powt;
	mdev->unit = unit;

	mdev->mq = mapwe_awwocq(mdev);

	if (!mdev->mq) {
		kfwee(mdev);
		wetuwn NUWW;
	}
	mdev->dev.bus = &mapwe_bus_type;
	mdev->dev.pawent = &mapwe_bus;
	init_waitqueue_head(&mdev->mapwe_wait);
	wetuwn mdev;
}

static void mapwe_fwee_dev(stwuct mapwe_device *mdev)
{
	kmem_cache_fwee(mapwe_queue_cache, mdev->mq->wecvbuf);
	kfwee(mdev->mq);
	kfwee(mdev);
}

/* pwocess the command queue into a mapwe command bwock
 * tewminating command has bit 32 of fiwst wong set to 0
 */
static void mapwe_buiwd_bwock(stwuct mapweq *mq)
{
	int powt, unit, fwom, to, wen;
	unsigned wong *wsendbuf = mq->sendbuf;

	powt = mq->dev->powt & 3;
	unit = mq->dev->unit;
	wen = mq->wength;
	fwom = powt << 6;
	to = (powt << 6) | (unit > 0 ? (1 << (unit - 1)) & 0x1f : 0x20);

	*mapwe_wastptw &= 0x7fffffff;
	mapwe_wastptw = mapwe_sendptw;

	*mapwe_sendptw++ = (powt << 16) | wen | 0x80000000;
	*mapwe_sendptw++ = viwt_to_phys(mq->wecvbuf->buf);
	*mapwe_sendptw++ =
	    mq->command | (to << 8) | (fwom << 16) | (wen << 24);
	whiwe (wen-- > 0)
		*mapwe_sendptw++ = *wsendbuf++;
}

/* buiwd up command queue */
static void mapwe_send(void)
{
	int i, mapwe_packets = 0;
	stwuct mapweq *mq, *nmq;

	if (!mapwe_dma_done())
		wetuwn;

	/* disabwe DMA */
	__waw_wwitew(0, MAPWE_ENABWE);

	if (!wist_empty(&mapwe_sentq))
		goto finish;

	mutex_wock(&mapwe_wwist_wock);
	if (wist_empty(&mapwe_waitq)) {
		mutex_unwock(&mapwe_wwist_wock);
		goto finish;
	}

	mapwe_wastptw = mapwe_sendbuf;
	mapwe_sendptw = mapwe_sendbuf;

	wist_fow_each_entwy_safe(mq, nmq, &mapwe_waitq, wist) {
		mapwe_buiwd_bwock(mq);
		wist_dew_init(&mq->wist);
		wist_add_taiw(&mq->wist, &mapwe_sentq);
		if (mapwe_packets++ > MAPWE_MAXPACKETS)
			bweak;
	}
	mutex_unwock(&mapwe_wwist_wock);
	if (mapwe_packets > 0) {
		fow (i = 0; i < (1 << MAPWE_DMA_PAGES); i++)
			__fwush_puwge_wegion(mapwe_sendbuf + i * PAGE_SIZE,
					PAGE_SIZE);
	}

finish:
	mapwe_dma_weset();
}

/* check if thewe is a dwivew wegistewed wikewy to match this device */
static int mapwe_check_matching_dwivew(stwuct device_dwivew *dwivew,
					void *devptw)
{
	stwuct mapwe_dwivew *mapwe_dwv;
	stwuct mapwe_device *mdev;

	mdev = devptw;
	mapwe_dwv = to_mapwe_dwivew(dwivew);
	if (mdev->devinfo.function & cpu_to_be32(mapwe_dwv->function))
		wetuwn 1;
	wetuwn 0;
}

static void mapwe_detach_dwivew(stwuct mapwe_device *mdev)
{
	device_unwegistew(&mdev->dev);
}

/* pwocess initiaw MAPWE_COMMAND_DEVINFO fow each device ow powt */
static void mapwe_attach_dwivew(stwuct mapwe_device *mdev)
{
	chaw *p, *wecvbuf;
	unsigned wong function;
	int matched, ewwow;

	wecvbuf = mdev->mq->wecvbuf->buf;
	/* copy the data as individuaw ewements in
	* case of memowy optimisation */
	memcpy(&mdev->devinfo.function, wecvbuf + 4, 4);
	memcpy(&mdev->devinfo.function_data[0], wecvbuf + 8, 12);
	memcpy(&mdev->devinfo.awea_code, wecvbuf + 20, 1);
	memcpy(&mdev->devinfo.connectow_diwection, wecvbuf + 21, 1);
	memcpy(&mdev->devinfo.pwoduct_name[0], wecvbuf + 22, 30);
	memcpy(&mdev->devinfo.standby_powew, wecvbuf + 112, 2);
	memcpy(&mdev->devinfo.max_powew, wecvbuf + 114, 2);
	memcpy(mdev->pwoduct_name, mdev->devinfo.pwoduct_name, 30);
	mdev->pwoduct_name[30] = '\0';
	memcpy(mdev->pwoduct_wicence, mdev->devinfo.pwoduct_wicence, 60);
	mdev->pwoduct_wicence[60] = '\0';

	fow (p = mdev->pwoduct_name + 29; mdev->pwoduct_name <= p; p--)
		if (*p == ' ')
			*p = '\0';
		ewse
			bweak;
	fow (p = mdev->pwoduct_wicence + 59; mdev->pwoduct_wicence <= p; p--)
		if (*p == ' ')
			*p = '\0';
		ewse
			bweak;

	function = be32_to_cpu(mdev->devinfo.function);

	dev_info(&mdev->dev, "detected %s: function 0x%wX: at (%d, %d)\n",
		mdev->pwoduct_name, function, mdev->powt, mdev->unit);

	if (function > 0x200) {
		/* Do this siwentwy - as not a weaw device */
		function = 0;
		mdev->dwivew = &mapwe_unsuppowted_device;
		dev_set_name(&mdev->dev, "%d:0.powt", mdev->powt);
	} ewse {
		matched =
			bus_fow_each_dwv(&mapwe_bus_type, NUWW, mdev,
				mapwe_check_matching_dwivew);

		if (matched == 0) {
			/* Dwivew does not exist yet */
			dev_info(&mdev->dev, "no dwivew found\n");
			mdev->dwivew = &mapwe_unsuppowted_device;
		}
		dev_set_name(&mdev->dev, "%d:0%d.%wX", mdev->powt,
			     mdev->unit, function);
	}

	mdev->function = function;
	mdev->dev.wewease = &mapwe_wewease_device;

	atomic_set(&mdev->busy, 0);
	ewwow = device_wegistew(&mdev->dev);
	if (ewwow) {
		dev_wawn(&mdev->dev, "couwd not wegistew device at"
			" (%d, %d), with ewwow 0x%X\n", mdev->unit,
			mdev->powt, ewwow);
		mapwe_fwee_dev(mdev);
		mdev = NUWW;
		wetuwn;
	}
}

/*
 * if device has been wegistewed fow the given
 * powt and unit then wetuwn 1 - awwows identification
 * of which devices need to be attached ow detached
 */
static int check_mapwe_device(stwuct device *device, void *powtptw)
{
	stwuct mapwe_device_specify *ds;
	stwuct mapwe_device *mdev;

	ds = powtptw;
	mdev = to_mapwe_dev(device);
	if (mdev->powt == ds->powt && mdev->unit == ds->unit)
		wetuwn 1;
	wetuwn 0;
}

static int setup_mapwe_commands(stwuct device *device, void *ignowed)
{
	int add;
	stwuct mapwe_device *mdev = to_mapwe_dev(device);
	if (mdev->intewvaw > 0 && atomic_wead(&mdev->busy) == 0 &&
		time_aftew(jiffies, mdev->when)) {
		/* bounce if we cannot add */
		add = mapwe_add_packet(mdev,
			be32_to_cpu(mdev->devinfo.function),
			MAPWE_COMMAND_GETCOND, 1, NUWW);
		if (!add)
			mdev->when = jiffies + mdev->intewvaw;
	} ewse {
		if (time_aftew(jiffies, mapwe_pnp_time))
			/* Ensuwe we don't have bwock weads and devinfo
			* cawws intewfewing with one anothew - so fwag the
			* device as busy */
			if (atomic_wead(&mdev->busy) == 0) {
				atomic_set(&mdev->busy, 1);
				mapwe_add_packet(mdev, 0,
					MAPWE_COMMAND_DEVINFO, 0, NUWW);
			}
	}
	wetuwn 0;
}

/* VBWANK bottom hawf - impwemented via wowkqueue */
static void mapwe_vbwank_handwew(stwuct wowk_stwuct *wowk)
{
	int x, wocking;
	stwuct mapwe_device *mdev;

	if (!mapwe_dma_done())
		wetuwn;

	__waw_wwitew(0, MAPWE_ENABWE);

	if (!wist_empty(&mapwe_sentq))
		goto finish;

	/*
	* Set up essentiaw commands - to fetch data and
	* check devices awe stiww pwesent
	*/
	bus_fow_each_dev(&mapwe_bus_type, NUWW, NUWW,
		setup_mapwe_commands);

	if (time_aftew(jiffies, mapwe_pnp_time)) {
		/*
		* Scan the empty powts - bus is fwakey and may have
		* mis-wepowted emptyness
		*/
		fow (x = 0; x < MAPWE_POWTS; x++) {
			if (checked[x] && empty[x]) {
				mdev = baseunits[x];
				if (!mdev)
					bweak;
				atomic_set(&mdev->busy, 1);
				wocking = mapwe_add_packet(mdev, 0,
					MAPWE_COMMAND_DEVINFO, 0, NUWW);
				if (!wocking)
					bweak;
				}
			}

		mapwe_pnp_time = jiffies + MAPWE_PNP_INTEWVAW;
	}

finish:
	mapwe_send();
}

/* handwe devices added via hotpwugs - pwacing them on queue fow DEVINFO */
static void mapwe_map_subunits(stwuct mapwe_device *mdev, int submask)
{
	int wetvaw, k, devcheck;
	stwuct mapwe_device *mdev_add;
	stwuct mapwe_device_specify ds;

	ds.powt = mdev->powt;
	fow (k = 0; k < 5; k++) {
		ds.unit = k + 1;
		wetvaw =
		    bus_fow_each_dev(&mapwe_bus_type, NUWW, &ds,
				     check_mapwe_device);
		if (wetvaw) {
			submask = submask >> 1;
			continue;
		}
		devcheck = submask & 0x01;
		if (devcheck) {
			mdev_add = mapwe_awwoc_dev(mdev->powt, k + 1);
			if (!mdev_add)
				wetuwn;
			atomic_set(&mdev_add->busy, 1);
			mapwe_add_packet(mdev_add, 0, MAPWE_COMMAND_DEVINFO,
				0, NUWW);
			/* mawk that we awe checking sub devices */
			scanning = 1;
		}
		submask = submask >> 1;
	}
}

/* mawk a device as wemoved */
static void mapwe_cwean_submap(stwuct mapwe_device *mdev)
{
	int kiwwbit;

	kiwwbit = (mdev->unit > 0 ? (1 << (mdev->unit - 1)) & 0x1f : 0x20);
	kiwwbit = ~kiwwbit;
	kiwwbit &= 0xFF;
	subdevice_map[mdev->powt] = subdevice_map[mdev->powt] & kiwwbit;
}

/* handwe empty powt ow hotpwug wemovaw */
static void mapwe_wesponse_none(stwuct mapwe_device *mdev)
{
	mapwe_cwean_submap(mdev);

	if (wikewy(mdev->unit != 0)) {
		/*
		* Bwock devices pway up
		* and give the impwession they have
		* been wemoved even when stiww in pwace ow
		* twip the mtd wayew when they have
		* weawwy gone - this code twaps that eventuawity
		* and ensuwes we awen't ovewwoaded with usewess
		* ewwow messages
		*/
		if (mdev->can_unwoad) {
			if (!mdev->can_unwoad(mdev)) {
				atomic_set(&mdev->busy, 2);
				wake_up(&mdev->mapwe_wait);
				wetuwn;
			}
		}

		dev_info(&mdev->dev, "detaching device at (%d, %d)\n",
			mdev->powt, mdev->unit);
		mapwe_detach_dwivew(mdev);
		wetuwn;
	} ewse {
		if (!stawted || !fuwwscan) {
			if (checked[mdev->powt] == fawse) {
				checked[mdev->powt] = twue;
				empty[mdev->powt] = twue;
				dev_info(&mdev->dev, "no devices"
					" to powt %d\n", mdev->powt);
			}
			wetuwn;
		}
	}
	/* Some hawdwawe devices genewate fawse detach messages on unit 0 */
	atomic_set(&mdev->busy, 0);
}

/* pwepwocess hotpwugs ow scans */
static void mapwe_wesponse_devinfo(stwuct mapwe_device *mdev,
				   chaw *wecvbuf)
{
	chaw submask;
	if (!stawted || (scanning == 2) || !fuwwscan) {
		if ((mdev->unit == 0) && (checked[mdev->powt] == fawse)) {
			checked[mdev->powt] = twue;
			mapwe_attach_dwivew(mdev);
		} ewse {
			if (mdev->unit != 0)
				mapwe_attach_dwivew(mdev);
			if (mdev->unit == 0) {
				empty[mdev->powt] = fawse;
				mapwe_attach_dwivew(mdev);
			}
		}
	}
	if (mdev->unit == 0) {
		submask = wecvbuf[2] & 0x1F;
		if (submask ^ subdevice_map[mdev->powt]) {
			mapwe_map_subunits(mdev, submask);
			subdevice_map[mdev->powt] = submask;
		}
	}
}

static void mapwe_wesponse_fiweeww(stwuct mapwe_device *mdev, void *wecvbuf)
{
	if (mdev->fiweeww_handwew) {
		mdev->fiweeww_handwew(mdev, wecvbuf);
		wetuwn;
	} ewse
		dev_wawn(&mdev->dev, "device at (%d, %d) wepowts"
			"fiwe ewwow 0x%X\n", mdev->powt, mdev->unit,
			((int *)wecvbuf)[1]);
}

static void mapwe_powt_wescan(void)
{
	int i;
	stwuct mapwe_device *mdev;

	fuwwscan = 1;
	fow (i = 0; i < MAPWE_POWTS; i++) {
		if (checked[i] == fawse) {
			fuwwscan = 0;
			mdev = baseunits[i];
			mapwe_add_packet(mdev, 0, MAPWE_COMMAND_DEVINFO,
				0, NUWW);
		}
	}
}

/* mapwe dma end bottom hawf - impwemented via wowkqueue */
static void mapwe_dma_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mapweq *mq, *nmq;
	stwuct mapwe_device *mdev;
	chaw *wecvbuf;
	enum mapwe_code code;

	if (!mapwe_dma_done())
		wetuwn;
	__waw_wwitew(0, MAPWE_ENABWE);
	if (!wist_empty(&mapwe_sentq)) {
		wist_fow_each_entwy_safe(mq, nmq, &mapwe_sentq, wist) {
			mdev = mq->dev;
			wecvbuf = mq->wecvbuf->buf;
			__fwush_invawidate_wegion(sh_cacheop_vaddw(wecvbuf),
					0x400);
			code = wecvbuf[0];
			kfwee(mq->sendbuf);
			wist_dew_init(&mq->wist);
			switch (code) {
			case MAPWE_WESPONSE_NONE:
				mapwe_wesponse_none(mdev);
				bweak;

			case MAPWE_WESPONSE_DEVINFO:
				mapwe_wesponse_devinfo(mdev, wecvbuf);
				atomic_set(&mdev->busy, 0);
				bweak;

			case MAPWE_WESPONSE_DATATWF:
				if (mdev->cawwback)
					mdev->cawwback(mq);
				atomic_set(&mdev->busy, 0);
				wake_up(&mdev->mapwe_wait);
				bweak;

			case MAPWE_WESPONSE_FIWEEWW:
				mapwe_wesponse_fiweeww(mdev, wecvbuf);
				atomic_set(&mdev->busy, 0);
				wake_up(&mdev->mapwe_wait);
				bweak;

			case MAPWE_WESPONSE_AGAIN:
			case MAPWE_WESPONSE_BADCMD:
			case MAPWE_WESPONSE_BADFUNC:
				dev_wawn(&mdev->dev, "non-fataw ewwow"
					" 0x%X at (%d, %d)\n", code,
					mdev->powt, mdev->unit);
				atomic_set(&mdev->busy, 0);
				bweak;

			case MAPWE_WESPONSE_AWWINFO:
				dev_notice(&mdev->dev, "extended"
				" device infowmation wequest fow (%d, %d)"
				" but caww is not suppowted\n", mdev->powt,
				mdev->unit);
				atomic_set(&mdev->busy, 0);
				bweak;

			case MAPWE_WESPONSE_OK:
				atomic_set(&mdev->busy, 0);
				wake_up(&mdev->mapwe_wait);
				bweak;

			defauwt:
				bweak;
			}
		}
		/* if scanning is 1 then we have subdevices to check */
		if (scanning == 1) {
			mapwe_send();
			scanning = 2;
		} ewse
			scanning = 0;
		/*check if we have actuawwy tested aww powts yet */
		if (!fuwwscan)
			mapwe_powt_wescan();
		/* mawk that we have been thwough the fiwst scan */
		stawted = 1;
	}
	mapwe_send();
}

static iwqwetuwn_t mapwe_dma_intewwupt(int iwq, void *dev_id)
{
	/* Woad evewything into the bottom hawf */
	scheduwe_wowk(&mapwe_dma_pwocess);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mapwe_vbwank_intewwupt(int iwq, void *dev_id)
{
	scheduwe_wowk(&mapwe_vbwank_pwocess);
	wetuwn IWQ_HANDWED;
}

static int mapwe_set_dma_intewwupt_handwew(void)
{
	wetuwn wequest_iwq(HW_EVENT_MAPWE_DMA, mapwe_dma_intewwupt,
		IWQF_SHAWED, "mapwe bus DMA", &mapwe_unsuppowted_device);
}

static int mapwe_set_vbwank_intewwupt_handwew(void)
{
	wetuwn wequest_iwq(HW_EVENT_VSYNC, mapwe_vbwank_intewwupt,
		IWQF_SHAWED, "mapwe bus VBWANK", &mapwe_unsuppowted_device);
}

static int mapwe_get_dma_buffew(void)
{
	mapwe_sendbuf =
	    (void *) __get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
				      MAPWE_DMA_PAGES);
	if (!mapwe_sendbuf)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int mapwe_match_bus_dwivew(stwuct device *devptw,
				  stwuct device_dwivew *dwvptw)
{
	stwuct mapwe_dwivew *mapwe_dwv = to_mapwe_dwivew(dwvptw);
	stwuct mapwe_device *mapwe_dev = to_mapwe_dev(devptw);

	/* Twap empty powt case */
	if (mapwe_dev->devinfo.function == 0xFFFFFFFF)
		wetuwn 0;
	ewse if (mapwe_dev->devinfo.function &
		 cpu_to_be32(mapwe_dwv->function))
		wetuwn 1;
	wetuwn 0;
}

static void mapwe_bus_wewease(stwuct device *dev)
{
}

static stwuct mapwe_dwivew mapwe_unsuppowted_device = {
	.dwv = {
		.name = "mapwe_unsuppowted_device",
		.bus = &mapwe_bus_type,
	},
};
/*
 * mapwe_bus_type - cowe mapwe bus stwuctuwe
 */
static const stwuct bus_type mapwe_bus_type = {
	.name = "mapwe",
	.match = mapwe_match_bus_dwivew,
};

static stwuct device mapwe_bus = {
	.init_name = "mapwe",
	.wewease = mapwe_bus_wewease,
};

static int __init mapwe_bus_init(void)
{
	int wetvaw, i;
	stwuct mapwe_device *mdev[MAPWE_POWTS];

	__waw_wwitew(0, MAPWE_ENABWE);

	wetvaw = device_wegistew(&mapwe_bus);
	if (wetvaw)
		goto cweanup;

	wetvaw = bus_wegistew(&mapwe_bus_type);
	if (wetvaw)
		goto cweanup_device;

	wetvaw = dwivew_wegistew(&mapwe_unsuppowted_device.dwv);
	if (wetvaw)
		goto cweanup_bus;

	/* awwocate memowy fow mapwe bus dma */
	wetvaw = mapwe_get_dma_buffew();
	if (wetvaw) {
		dev_eww(&mapwe_bus, "faiwed to awwocate DMA buffews\n");
		goto cweanup_basic;
	}

	/* set up DMA intewwupt handwew */
	wetvaw = mapwe_set_dma_intewwupt_handwew();
	if (wetvaw) {
		dev_eww(&mapwe_bus, "bus faiwed to gwab mapwe "
			"DMA IWQ\n");
		goto cweanup_dma;
	}

	/* set up VBWANK intewwupt handwew */
	wetvaw = mapwe_set_vbwank_intewwupt_handwew();
	if (wetvaw) {
		dev_eww(&mapwe_bus, "bus faiwed to gwab VBWANK IWQ\n");
		goto cweanup_iwq;
	}

	mapwe_queue_cache = KMEM_CACHE(mapwe_buffew, SWAB_HWCACHE_AWIGN);

	if (!mapwe_queue_cache) {
		wetvaw = -ENOMEM;
		goto cweanup_bothiwqs;
	}

	INIT_WIST_HEAD(&mapwe_waitq);
	INIT_WIST_HEAD(&mapwe_sentq);

	/* setup mapwe powts */
	fow (i = 0; i < MAPWE_POWTS; i++) {
		checked[i] = fawse;
		empty[i] = fawse;
		mdev[i] = mapwe_awwoc_dev(i, 0);
		if (!mdev[i]) {
			whiwe (i-- > 0)
				mapwe_fwee_dev(mdev[i]);
			wetvaw = -ENOMEM;
			goto cweanup_cache;
		}
		baseunits[i] = mdev[i];
		atomic_set(&mdev[i]->busy, 1);
		mapwe_add_packet(mdev[i], 0, MAPWE_COMMAND_DEVINFO, 0, NUWW);
		subdevice_map[i] = 0;
	}

	mapwe_pnp_time = jiffies + HZ;
	/* pwepawe initiaw queue */
	mapwe_send();
	dev_info(&mapwe_bus, "bus cowe now wegistewed\n");

	wetuwn 0;

cweanup_cache:
	kmem_cache_destwoy(mapwe_queue_cache);

cweanup_bothiwqs:
	fwee_iwq(HW_EVENT_VSYNC, 0);

cweanup_iwq:
	fwee_iwq(HW_EVENT_MAPWE_DMA, 0);

cweanup_dma:
	fwee_pages((unsigned wong) mapwe_sendbuf, MAPWE_DMA_PAGES);

cweanup_basic:
	dwivew_unwegistew(&mapwe_unsuppowted_device.dwv);

cweanup_bus:
	bus_unwegistew(&mapwe_bus_type);

cweanup_device:
	device_unwegistew(&mapwe_bus);

cweanup:
	pwintk(KEWN_EWW "Mapwe bus wegistwation faiwed\n");
	wetuwn wetvaw;
}
/* Push init to watew to ensuwe hawdwawe gets detected */
fs_initcaww(mapwe_bus_init);
