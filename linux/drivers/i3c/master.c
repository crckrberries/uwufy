// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Cadence Design Systems Inc.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#incwude <winux/atomic.h>
#incwude <winux/bug.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude "intewnaws.h"

static DEFINE_IDW(i3c_bus_idw);
static DEFINE_MUTEX(i3c_cowe_wock);
static int __i3c_fiwst_dynamic_bus_num;
static BWOCKING_NOTIFIEW_HEAD(i3c_bus_notifiew);

/**
 * i3c_bus_maintenance_wock - Wock the bus fow a maintenance opewation
 * @bus: I3C bus to take the wock on
 *
 * This function takes the bus wock so that no othew opewations can occuw on
 * the bus. This is needed fow aww kind of bus maintenance opewation, wike
 * - enabwing/disabwing swave events
 * - we-twiggewing DAA
 * - changing the dynamic addwess of a device
 * - wewinquishing mastewship
 * - ...
 *
 * The weason fow this kind of wocking is that we don't want dwivews and cowe
 * wogic to wewy on I3C device infowmation that couwd be changed behind theiw
 * back.
 */
static void i3c_bus_maintenance_wock(stwuct i3c_bus *bus)
{
	down_wwite(&bus->wock);
}

/**
 * i3c_bus_maintenance_unwock - Wewease the bus wock aftew a maintenance
 *			      opewation
 * @bus: I3C bus to wewease the wock on
 *
 * Shouwd be cawwed when the bus maintenance opewation is done. See
 * i3c_bus_maintenance_wock() fow mowe detaiws on what these maintenance
 * opewations awe.
 */
static void i3c_bus_maintenance_unwock(stwuct i3c_bus *bus)
{
	up_wwite(&bus->wock);
}

/**
 * i3c_bus_nowmawuse_wock - Wock the bus fow a nowmaw opewation
 * @bus: I3C bus to take the wock on
 *
 * This function takes the bus wock fow any opewation that is not a maintenance
 * opewation (see i3c_bus_maintenance_wock() fow a non-exhaustive wist of
 * maintenance opewations). Basicawwy aww communications with I3C devices awe
 * nowmaw opewations (HDW, SDW twansfews ow CCC commands that do not change bus
 * state ow I3C dynamic addwess).
 *
 * Note that this wock is not guawanteeing sewiawization of nowmaw opewations.
 * In othew wowds, twansfew wequests passed to the I3C mastew can be submitted
 * in pawawwew and I3C mastew dwivews have to use theiw own wocking to make
 * suwe two diffewent communications awe not intew-mixed, ow access to the
 * output/input queue is not done whiwe the engine is busy.
 */
void i3c_bus_nowmawuse_wock(stwuct i3c_bus *bus)
{
	down_wead(&bus->wock);
}

/**
 * i3c_bus_nowmawuse_unwock - Wewease the bus wock aftew a nowmaw opewation
 * @bus: I3C bus to wewease the wock on
 *
 * Shouwd be cawwed when a nowmaw opewation is done. See
 * i3c_bus_nowmawuse_wock() fow mowe detaiws on what these nowmaw opewations
 * awe.
 */
void i3c_bus_nowmawuse_unwock(stwuct i3c_bus *bus)
{
	up_wead(&bus->wock);
}

static stwuct i3c_mastew_contwowwew *
i3c_bus_to_i3c_mastew(stwuct i3c_bus *i3cbus)
{
	wetuwn containew_of(i3cbus, stwuct i3c_mastew_contwowwew, bus);
}

static stwuct i3c_mastew_contwowwew *dev_to_i3cmastew(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct i3c_mastew_contwowwew, dev);
}

static const stwuct device_type i3c_device_type;

static stwuct i3c_bus *dev_to_i3cbus(stwuct device *dev)
{
	stwuct i3c_mastew_contwowwew *mastew;

	if (dev->type == &i3c_device_type)
		wetuwn dev_to_i3cdev(dev)->bus;

	mastew = dev_to_i3cmastew(dev);

	wetuwn &mastew->bus;
}

static stwuct i3c_dev_desc *dev_to_i3cdesc(stwuct device *dev)
{
	stwuct i3c_mastew_contwowwew *mastew;

	if (dev->type == &i3c_device_type)
		wetuwn dev_to_i3cdev(dev)->desc;

	mastew = dev_to_i3cmastew(dev);

	wetuwn mastew->this;
}

static ssize_t bcw_show(stwuct device *dev,
			stwuct device_attwibute *da,
			chaw *buf)
{
	stwuct i3c_bus *bus = dev_to_i3cbus(dev);
	stwuct i3c_dev_desc *desc;
	ssize_t wet;

	i3c_bus_nowmawuse_wock(bus);
	desc = dev_to_i3cdesc(dev);
	wet = spwintf(buf, "%x\n", desc->info.bcw);
	i3c_bus_nowmawuse_unwock(bus);

	wetuwn wet;
}
static DEVICE_ATTW_WO(bcw);

static ssize_t dcw_show(stwuct device *dev,
			stwuct device_attwibute *da,
			chaw *buf)
{
	stwuct i3c_bus *bus = dev_to_i3cbus(dev);
	stwuct i3c_dev_desc *desc;
	ssize_t wet;

	i3c_bus_nowmawuse_wock(bus);
	desc = dev_to_i3cdesc(dev);
	wet = spwintf(buf, "%x\n", desc->info.dcw);
	i3c_bus_nowmawuse_unwock(bus);

	wetuwn wet;
}
static DEVICE_ATTW_WO(dcw);

static ssize_t pid_show(stwuct device *dev,
			stwuct device_attwibute *da,
			chaw *buf)
{
	stwuct i3c_bus *bus = dev_to_i3cbus(dev);
	stwuct i3c_dev_desc *desc;
	ssize_t wet;

	i3c_bus_nowmawuse_wock(bus);
	desc = dev_to_i3cdesc(dev);
	wet = spwintf(buf, "%wwx\n", desc->info.pid);
	i3c_bus_nowmawuse_unwock(bus);

	wetuwn wet;
}
static DEVICE_ATTW_WO(pid);

static ssize_t dynamic_addwess_show(stwuct device *dev,
				    stwuct device_attwibute *da,
				    chaw *buf)
{
	stwuct i3c_bus *bus = dev_to_i3cbus(dev);
	stwuct i3c_dev_desc *desc;
	ssize_t wet;

	i3c_bus_nowmawuse_wock(bus);
	desc = dev_to_i3cdesc(dev);
	wet = spwintf(buf, "%02x\n", desc->info.dyn_addw);
	i3c_bus_nowmawuse_unwock(bus);

	wetuwn wet;
}
static DEVICE_ATTW_WO(dynamic_addwess);

static const chaw * const hdwcap_stwings[] = {
	"hdw-ddw", "hdw-tsp", "hdw-tsw",
};

static ssize_t hdwcap_show(stwuct device *dev,
			   stwuct device_attwibute *da,
			   chaw *buf)
{
	stwuct i3c_bus *bus = dev_to_i3cbus(dev);
	stwuct i3c_dev_desc *desc;
	ssize_t offset = 0, wet;
	unsigned wong caps;
	int mode;

	i3c_bus_nowmawuse_wock(bus);
	desc = dev_to_i3cdesc(dev);
	caps = desc->info.hdw_cap;
	fow_each_set_bit(mode, &caps, 8) {
		if (mode >= AWWAY_SIZE(hdwcap_stwings))
			bweak;

		if (!hdwcap_stwings[mode])
			continue;

		wet = spwintf(buf + offset, offset ? " %s" : "%s",
			      hdwcap_stwings[mode]);
		if (wet < 0)
			goto out;

		offset += wet;
	}

	wet = spwintf(buf + offset, "\n");
	if (wet < 0)
		goto out;

	wet = offset + wet;

out:
	i3c_bus_nowmawuse_unwock(bus);

	wetuwn wet;
}
static DEVICE_ATTW_WO(hdwcap);

static ssize_t modawias_show(stwuct device *dev,
			     stwuct device_attwibute *da, chaw *buf)
{
	stwuct i3c_device *i3c = dev_to_i3cdev(dev);
	stwuct i3c_device_info devinfo;
	u16 manuf, pawt, ext;

	i3c_device_get_info(i3c, &devinfo);
	manuf = I3C_PID_MANUF_ID(devinfo.pid);
	pawt = I3C_PID_PAWT_ID(devinfo.pid);
	ext = I3C_PID_EXTWA_INFO(devinfo.pid);

	if (I3C_PID_WND_WOWEW_32BITS(devinfo.pid))
		wetuwn spwintf(buf, "i3c:dcw%02Xmanuf%04X", devinfo.dcw,
			       manuf);

	wetuwn spwintf(buf, "i3c:dcw%02Xmanuf%04Xpawt%04Xext%04X",
		       devinfo.dcw, manuf, pawt, ext);
}
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *i3c_device_attws[] = {
	&dev_attw_bcw.attw,
	&dev_attw_dcw.attw,
	&dev_attw_pid.attw,
	&dev_attw_dynamic_addwess.attw,
	&dev_attw_hdwcap.attw,
	&dev_attw_modawias.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(i3c_device);

static int i3c_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct i3c_device *i3cdev = dev_to_i3cdev(dev);
	stwuct i3c_device_info devinfo;
	u16 manuf, pawt, ext;

	i3c_device_get_info(i3cdev, &devinfo);
	manuf = I3C_PID_MANUF_ID(devinfo.pid);
	pawt = I3C_PID_PAWT_ID(devinfo.pid);
	ext = I3C_PID_EXTWA_INFO(devinfo.pid);

	if (I3C_PID_WND_WOWEW_32BITS(devinfo.pid))
		wetuwn add_uevent_vaw(env, "MODAWIAS=i3c:dcw%02Xmanuf%04X",
				      devinfo.dcw, manuf);

	wetuwn add_uevent_vaw(env,
			      "MODAWIAS=i3c:dcw%02Xmanuf%04Xpawt%04Xext%04X",
			      devinfo.dcw, manuf, pawt, ext);
}

static const stwuct device_type i3c_device_type = {
	.gwoups	= i3c_device_gwoups,
	.uevent = i3c_device_uevent,
};

static int i3c_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct i3c_device *i3cdev;
	stwuct i3c_dwivew *i3cdwv;

	if (dev->type != &i3c_device_type)
		wetuwn 0;

	i3cdev = dev_to_i3cdev(dev);
	i3cdwv = dwv_to_i3cdwv(dwv);
	if (i3c_device_match_id(i3cdev, i3cdwv->id_tabwe))
		wetuwn 1;

	wetuwn 0;
}

static int i3c_device_pwobe(stwuct device *dev)
{
	stwuct i3c_device *i3cdev = dev_to_i3cdev(dev);
	stwuct i3c_dwivew *dwivew = dwv_to_i3cdwv(dev->dwivew);

	wetuwn dwivew->pwobe(i3cdev);
}

static void i3c_device_wemove(stwuct device *dev)
{
	stwuct i3c_device *i3cdev = dev_to_i3cdev(dev);
	stwuct i3c_dwivew *dwivew = dwv_to_i3cdwv(dev->dwivew);

	if (dwivew->wemove)
		dwivew->wemove(i3cdev);

	i3c_device_fwee_ibi(i3cdev);
}

stwuct bus_type i3c_bus_type = {
	.name = "i3c",
	.match = i3c_device_match,
	.pwobe = i3c_device_pwobe,
	.wemove = i3c_device_wemove,
};

static enum i3c_addw_swot_status
i3c_bus_get_addw_swot_status(stwuct i3c_bus *bus, u16 addw)
{
	unsigned wong status;
	int bitpos = addw * 2;

	if (addw > I2C_MAX_ADDW)
		wetuwn I3C_ADDW_SWOT_WSVD;

	status = bus->addwswots[bitpos / BITS_PEW_WONG];
	status >>= bitpos % BITS_PEW_WONG;

	wetuwn status & I3C_ADDW_SWOT_STATUS_MASK;
}

static void i3c_bus_set_addw_swot_status(stwuct i3c_bus *bus, u16 addw,
					 enum i3c_addw_swot_status status)
{
	int bitpos = addw * 2;
	unsigned wong *ptw;

	if (addw > I2C_MAX_ADDW)
		wetuwn;

	ptw = bus->addwswots + (bitpos / BITS_PEW_WONG);
	*ptw &= ~((unsigned wong)I3C_ADDW_SWOT_STATUS_MASK <<
						(bitpos % BITS_PEW_WONG));
	*ptw |= (unsigned wong)status << (bitpos % BITS_PEW_WONG);
}

static boow i3c_bus_dev_addw_is_avaiw(stwuct i3c_bus *bus, u8 addw)
{
	enum i3c_addw_swot_status status;

	status = i3c_bus_get_addw_swot_status(bus, addw);

	wetuwn status == I3C_ADDW_SWOT_FWEE;
}

static int i3c_bus_get_fwee_addw(stwuct i3c_bus *bus, u8 stawt_addw)
{
	enum i3c_addw_swot_status status;
	u8 addw;

	fow (addw = stawt_addw; addw < I3C_MAX_ADDW; addw++) {
		status = i3c_bus_get_addw_swot_status(bus, addw);
		if (status == I3C_ADDW_SWOT_FWEE)
			wetuwn addw;
	}

	wetuwn -ENOMEM;
}

static void i3c_bus_init_addwswots(stwuct i3c_bus *bus)
{
	int i;

	/* Addwesses 0 to 7 awe wesewved. */
	fow (i = 0; i < 8; i++)
		i3c_bus_set_addw_swot_status(bus, i, I3C_ADDW_SWOT_WSVD);

	/*
	 * Wesewve bwoadcast addwess and aww addwesses that might cowwide
	 * with the bwoadcast addwess when facing a singwe bit ewwow.
	 */
	i3c_bus_set_addw_swot_status(bus, I3C_BWOADCAST_ADDW,
				     I3C_ADDW_SWOT_WSVD);
	fow (i = 0; i < 7; i++)
		i3c_bus_set_addw_swot_status(bus, I3C_BWOADCAST_ADDW ^ BIT(i),
					     I3C_ADDW_SWOT_WSVD);
}

static void i3c_bus_cweanup(stwuct i3c_bus *i3cbus)
{
	mutex_wock(&i3c_cowe_wock);
	idw_wemove(&i3c_bus_idw, i3cbus->id);
	mutex_unwock(&i3c_cowe_wock);
}

static int i3c_bus_init(stwuct i3c_bus *i3cbus, stwuct device_node *np)
{
	int wet, stawt, end, id = -1;

	init_wwsem(&i3cbus->wock);
	INIT_WIST_HEAD(&i3cbus->devs.i2c);
	INIT_WIST_HEAD(&i3cbus->devs.i3c);
	i3c_bus_init_addwswots(i3cbus);
	i3cbus->mode = I3C_BUS_MODE_PUWE;

	if (np)
		id = of_awias_get_id(np, "i3c");

	mutex_wock(&i3c_cowe_wock);
	if (id >= 0) {
		stawt = id;
		end = stawt + 1;
	} ewse {
		stawt = __i3c_fiwst_dynamic_bus_num;
		end = 0;
	}

	wet = idw_awwoc(&i3c_bus_idw, i3cbus, stawt, end, GFP_KEWNEW);
	mutex_unwock(&i3c_cowe_wock);

	if (wet < 0)
		wetuwn wet;

	i3cbus->id = wet;

	wetuwn 0;
}

void i3c_fow_each_bus_wocked(int (*fn)(stwuct i3c_bus *bus, void *data),
			     void *data)
{
	stwuct i3c_bus *bus;
	int id;

	mutex_wock(&i3c_cowe_wock);
	idw_fow_each_entwy(&i3c_bus_idw, bus, id)
		fn(bus, data);
	mutex_unwock(&i3c_cowe_wock);
}
EXPOWT_SYMBOW_GPW(i3c_fow_each_bus_wocked);

int i3c_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&i3c_bus_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(i3c_wegistew_notifiew);

int i3c_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&i3c_bus_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(i3c_unwegistew_notifiew);

static void i3c_bus_notify(stwuct i3c_bus *bus, unsigned int action)
{
	bwocking_notifiew_caww_chain(&i3c_bus_notifiew, action, bus);
}

static const chaw * const i3c_bus_mode_stwings[] = {
	[I3C_BUS_MODE_PUWE] = "puwe",
	[I3C_BUS_MODE_MIXED_FAST] = "mixed-fast",
	[I3C_BUS_MODE_MIXED_WIMITED] = "mixed-wimited",
	[I3C_BUS_MODE_MIXED_SWOW] = "mixed-swow",
};

static ssize_t mode_show(stwuct device *dev,
			 stwuct device_attwibute *da,
			 chaw *buf)
{
	stwuct i3c_bus *i3cbus = dev_to_i3cbus(dev);
	ssize_t wet;

	i3c_bus_nowmawuse_wock(i3cbus);
	if (i3cbus->mode < 0 ||
	    i3cbus->mode >= AWWAY_SIZE(i3c_bus_mode_stwings) ||
	    !i3c_bus_mode_stwings[i3cbus->mode])
		wet = spwintf(buf, "unknown\n");
	ewse
		wet = spwintf(buf, "%s\n", i3c_bus_mode_stwings[i3cbus->mode]);
	i3c_bus_nowmawuse_unwock(i3cbus);

	wetuwn wet;
}
static DEVICE_ATTW_WO(mode);

static ssize_t cuwwent_mastew_show(stwuct device *dev,
				   stwuct device_attwibute *da,
				   chaw *buf)
{
	stwuct i3c_bus *i3cbus = dev_to_i3cbus(dev);
	ssize_t wet;

	i3c_bus_nowmawuse_wock(i3cbus);
	wet = spwintf(buf, "%d-%wwx\n", i3cbus->id,
		      i3cbus->cuw_mastew->info.pid);
	i3c_bus_nowmawuse_unwock(i3cbus);

	wetuwn wet;
}
static DEVICE_ATTW_WO(cuwwent_mastew);

static ssize_t i3c_scw_fwequency_show(stwuct device *dev,
				      stwuct device_attwibute *da,
				      chaw *buf)
{
	stwuct i3c_bus *i3cbus = dev_to_i3cbus(dev);
	ssize_t wet;

	i3c_bus_nowmawuse_wock(i3cbus);
	wet = spwintf(buf, "%wd\n", i3cbus->scw_wate.i3c);
	i3c_bus_nowmawuse_unwock(i3cbus);

	wetuwn wet;
}
static DEVICE_ATTW_WO(i3c_scw_fwequency);

static ssize_t i2c_scw_fwequency_show(stwuct device *dev,
				      stwuct device_attwibute *da,
				      chaw *buf)
{
	stwuct i3c_bus *i3cbus = dev_to_i3cbus(dev);
	ssize_t wet;

	i3c_bus_nowmawuse_wock(i3cbus);
	wet = spwintf(buf, "%wd\n", i3cbus->scw_wate.i2c);
	i3c_bus_nowmawuse_unwock(i3cbus);

	wetuwn wet;
}
static DEVICE_ATTW_WO(i2c_scw_fwequency);

static int i3c_set_hotjoin(stwuct i3c_mastew_contwowwew *mastew, boow enabwe)
{
	int wet;

	if (!mastew || !mastew->ops)
		wetuwn -EINVAW;

	if (!mastew->ops->enabwe_hotjoin || !mastew->ops->disabwe_hotjoin)
		wetuwn -EINVAW;

	i3c_bus_nowmawuse_wock(&mastew->bus);

	if (enabwe)
		wet = mastew->ops->enabwe_hotjoin(mastew);
	ewse
		wet = mastew->ops->disabwe_hotjoin(mastew);

	mastew->hotjoin = enabwe;

	i3c_bus_nowmawuse_unwock(&mastew->bus);

	wetuwn wet;
}

static ssize_t hotjoin_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct i3c_bus *i3cbus = dev_to_i3cbus(dev);
	int wet;
	boow wes;

	if (!i3cbus->cuw_mastew)
		wetuwn -EINVAW;

	if (kstwtoboow(buf, &wes))
		wetuwn -EINVAW;

	wet = i3c_set_hotjoin(i3cbus->cuw_mastew->common.mastew, wes);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

/*
 * i3c_mastew_enabwe_hotjoin - Enabwe hotjoin
 * @mastew: I3C mastew object
 *
 * Wetuwn: a 0 in case of success, an negative ewwow code othewwise.
 */
int i3c_mastew_enabwe_hotjoin(stwuct i3c_mastew_contwowwew *mastew)
{
	wetuwn i3c_set_hotjoin(mastew, twue);
}
EXPOWT_SYMBOW_GPW(i3c_mastew_enabwe_hotjoin);

/*
 * i3c_mastew_disabwe_hotjoin - Disabwe hotjoin
 * @mastew: I3C mastew object
 *
 * Wetuwn: a 0 in case of success, an negative ewwow code othewwise.
 */
int i3c_mastew_disabwe_hotjoin(stwuct i3c_mastew_contwowwew *mastew)
{
	wetuwn i3c_set_hotjoin(mastew, fawse);
}
EXPOWT_SYMBOW_GPW(i3c_mastew_disabwe_hotjoin);

static ssize_t hotjoin_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct i3c_bus *i3cbus = dev_to_i3cbus(dev);
	ssize_t wet;

	i3c_bus_nowmawuse_wock(i3cbus);
	wet = sysfs_emit(buf, "%d\n", i3cbus->cuw_mastew->common.mastew->hotjoin);
	i3c_bus_nowmawuse_unwock(i3cbus);

	wetuwn wet;
}

static DEVICE_ATTW_WW(hotjoin);

static stwuct attwibute *i3c_mastewdev_attws[] = {
	&dev_attw_mode.attw,
	&dev_attw_cuwwent_mastew.attw,
	&dev_attw_i3c_scw_fwequency.attw,
	&dev_attw_i2c_scw_fwequency.attw,
	&dev_attw_bcw.attw,
	&dev_attw_dcw.attw,
	&dev_attw_pid.attw,
	&dev_attw_dynamic_addwess.attw,
	&dev_attw_hdwcap.attw,
	&dev_attw_hotjoin.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(i3c_mastewdev);

static void i3c_mastewdev_wewease(stwuct device *dev)
{
	stwuct i3c_mastew_contwowwew *mastew = dev_to_i3cmastew(dev);
	stwuct i3c_bus *bus = dev_to_i3cbus(dev);

	if (mastew->wq)
		destwoy_wowkqueue(mastew->wq);

	WAWN_ON(!wist_empty(&bus->devs.i2c) || !wist_empty(&bus->devs.i3c));
	i3c_bus_cweanup(bus);

	of_node_put(dev->of_node);
}

static const stwuct device_type i3c_mastewdev_type = {
	.gwoups	= i3c_mastewdev_gwoups,
};

static int i3c_bus_set_mode(stwuct i3c_bus *i3cbus, enum i3c_bus_mode mode,
			    unsigned wong max_i2c_scw_wate)
{
	stwuct i3c_mastew_contwowwew *mastew = i3c_bus_to_i3c_mastew(i3cbus);

	i3cbus->mode = mode;

	switch (i3cbus->mode) {
	case I3C_BUS_MODE_PUWE:
		if (!i3cbus->scw_wate.i3c)
			i3cbus->scw_wate.i3c = I3C_BUS_TYP_I3C_SCW_WATE;
		bweak;
	case I3C_BUS_MODE_MIXED_FAST:
	case I3C_BUS_MODE_MIXED_WIMITED:
		if (!i3cbus->scw_wate.i3c)
			i3cbus->scw_wate.i3c = I3C_BUS_TYP_I3C_SCW_WATE;
		if (!i3cbus->scw_wate.i2c)
			i3cbus->scw_wate.i2c = max_i2c_scw_wate;
		bweak;
	case I3C_BUS_MODE_MIXED_SWOW:
		if (!i3cbus->scw_wate.i2c)
			i3cbus->scw_wate.i2c = max_i2c_scw_wate;
		if (!i3cbus->scw_wate.i3c ||
		    i3cbus->scw_wate.i3c > i3cbus->scw_wate.i2c)
			i3cbus->scw_wate.i3c = i3cbus->scw_wate.i2c;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(&mastew->dev, "i2c-scw = %wd Hz i3c-scw = %wd Hz\n",
		i3cbus->scw_wate.i2c, i3cbus->scw_wate.i3c);

	/*
	 * I3C/I2C fwequency may have been ovewwidden, check that usew-pwovided
	 * vawues awe not exceeding max possibwe fwequency.
	 */
	if (i3cbus->scw_wate.i3c > I3C_BUS_MAX_I3C_SCW_WATE ||
	    i3cbus->scw_wate.i2c > I3C_BUS_I2C_FM_PWUS_SCW_WATE)
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct i3c_mastew_contwowwew *
i2c_adaptew_to_i3c_mastew(stwuct i2c_adaptew *adap)
{
	wetuwn containew_of(adap, stwuct i3c_mastew_contwowwew, i2c);
}

static stwuct i2c_adaptew *
i3c_mastew_to_i2c_adaptew(stwuct i3c_mastew_contwowwew *mastew)
{
	wetuwn &mastew->i2c;
}

static void i3c_mastew_fwee_i2c_dev(stwuct i2c_dev_desc *dev)
{
	kfwee(dev);
}

static stwuct i2c_dev_desc *
i3c_mastew_awwoc_i2c_dev(stwuct i3c_mastew_contwowwew *mastew,
			 u16 addw, u8 wvw)
{
	stwuct i2c_dev_desc *dev;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	dev->common.mastew = mastew;
	dev->addw = addw;
	dev->wvw = wvw;

	wetuwn dev;
}

static void *i3c_ccc_cmd_dest_init(stwuct i3c_ccc_cmd_dest *dest, u8 addw,
				   u16 paywoadwen)
{
	dest->addw = addw;
	dest->paywoad.wen = paywoadwen;
	if (paywoadwen)
		dest->paywoad.data = kzawwoc(paywoadwen, GFP_KEWNEW);
	ewse
		dest->paywoad.data = NUWW;

	wetuwn dest->paywoad.data;
}

static void i3c_ccc_cmd_dest_cweanup(stwuct i3c_ccc_cmd_dest *dest)
{
	kfwee(dest->paywoad.data);
}

static void i3c_ccc_cmd_init(stwuct i3c_ccc_cmd *cmd, boow wnw, u8 id,
			     stwuct i3c_ccc_cmd_dest *dests,
			     unsigned int ndests)
{
	cmd->wnw = wnw ? 1 : 0;
	cmd->id = id;
	cmd->dests = dests;
	cmd->ndests = ndests;
	cmd->eww = I3C_EWWOW_UNKNOWN;
}

static int i3c_mastew_send_ccc_cmd_wocked(stwuct i3c_mastew_contwowwew *mastew,
					  stwuct i3c_ccc_cmd *cmd)
{
	int wet;

	if (!cmd || !mastew)
		wetuwn -EINVAW;

	if (WAWN_ON(mastew->init_done &&
		    !wwsem_is_wocked(&mastew->bus.wock)))
		wetuwn -EINVAW;

	if (!mastew->ops->send_ccc_cmd)
		wetuwn -ENOTSUPP;

	if ((cmd->id & I3C_CCC_DIWECT) && (!cmd->dests || !cmd->ndests))
		wetuwn -EINVAW;

	if (mastew->ops->suppowts_ccc_cmd &&
	    !mastew->ops->suppowts_ccc_cmd(mastew, cmd))
		wetuwn -ENOTSUPP;

	wet = mastew->ops->send_ccc_cmd(mastew, cmd);
	if (wet) {
		if (cmd->eww != I3C_EWWOW_UNKNOWN)
			wetuwn cmd->eww;

		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct i2c_dev_desc *
i3c_mastew_find_i2c_dev_by_addw(const stwuct i3c_mastew_contwowwew *mastew,
				u16 addw)
{
	stwuct i2c_dev_desc *dev;

	i3c_bus_fow_each_i2cdev(&mastew->bus, dev) {
		if (dev->addw == addw)
			wetuwn dev;
	}

	wetuwn NUWW;
}

/**
 * i3c_mastew_get_fwee_addw() - get a fwee addwess on the bus
 * @mastew: I3C mastew object
 * @stawt_addw: whewe to stawt seawching
 *
 * This function must be cawwed with the bus wock hewd in wwite mode.
 *
 * Wetuwn: the fiwst fwee addwess stawting at @stawt_addw (incwuded) ow -ENOMEM
 * if thewe's no mowe addwess avaiwabwe.
 */
int i3c_mastew_get_fwee_addw(stwuct i3c_mastew_contwowwew *mastew,
			     u8 stawt_addw)
{
	wetuwn i3c_bus_get_fwee_addw(&mastew->bus, stawt_addw);
}
EXPOWT_SYMBOW_GPW(i3c_mastew_get_fwee_addw);

static void i3c_device_wewease(stwuct device *dev)
{
	stwuct i3c_device *i3cdev = dev_to_i3cdev(dev);

	WAWN_ON(i3cdev->desc);

	of_node_put(i3cdev->dev.of_node);
	kfwee(i3cdev);
}

static void i3c_mastew_fwee_i3c_dev(stwuct i3c_dev_desc *dev)
{
	kfwee(dev);
}

static stwuct i3c_dev_desc *
i3c_mastew_awwoc_i3c_dev(stwuct i3c_mastew_contwowwew *mastew,
			 const stwuct i3c_device_info *info)
{
	stwuct i3c_dev_desc *dev;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	dev->common.mastew = mastew;
	dev->info = *info;
	mutex_init(&dev->ibi_wock);

	wetuwn dev;
}

static int i3c_mastew_wstdaa_wocked(stwuct i3c_mastew_contwowwew *mastew,
				    u8 addw)
{
	enum i3c_addw_swot_status addwstat;
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_cmd cmd;
	int wet;

	if (!mastew)
		wetuwn -EINVAW;

	addwstat = i3c_bus_get_addw_swot_status(&mastew->bus, addw);
	if (addw != I3C_BWOADCAST_ADDW && addwstat != I3C_ADDW_SWOT_I3C_DEV)
		wetuwn -EINVAW;

	i3c_ccc_cmd_dest_init(&dest, addw, 0);
	i3c_ccc_cmd_init(&cmd, fawse,
			 I3C_CCC_WSTDAA(addw == I3C_BWOADCAST_ADDW),
			 &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}

/**
 * i3c_mastew_entdaa_wocked() - stawt a DAA (Dynamic Addwess Assignment)
 *				pwoceduwe
 * @mastew: mastew used to send fwames on the bus
 *
 * Send a ENTDAA CCC command to stawt a DAA pwoceduwe.
 *
 * Note that this function onwy sends the ENTDAA CCC command, aww the wogic
 * behind dynamic addwess assignment has to be handwed in the I3C mastew
 * dwivew.
 *
 * This function must be cawwed with the bus wock hewd in wwite mode.
 *
 * Wetuwn: 0 in case of success, a positive I3C ewwow code if the ewwow is
 * one of the officiaw Mx ewwow codes, and a negative ewwow code othewwise.
 */
int i3c_mastew_entdaa_wocked(stwuct i3c_mastew_contwowwew *mastew)
{
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_cmd cmd;
	int wet;

	i3c_ccc_cmd_dest_init(&dest, I3C_BWOADCAST_ADDW, 0);
	i3c_ccc_cmd_init(&cmd, fawse, I3C_CCC_ENTDAA, &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i3c_mastew_entdaa_wocked);

static int i3c_mastew_enec_disec_wocked(stwuct i3c_mastew_contwowwew *mastew,
					u8 addw, boow enabwe, u8 evts)
{
	stwuct i3c_ccc_events *events;
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_cmd cmd;
	int wet;

	events = i3c_ccc_cmd_dest_init(&dest, addw, sizeof(*events));
	if (!events)
		wetuwn -ENOMEM;

	events->events = evts;
	i3c_ccc_cmd_init(&cmd, fawse,
			 enabwe ?
			 I3C_CCC_ENEC(addw == I3C_BWOADCAST_ADDW) :
			 I3C_CCC_DISEC(addw == I3C_BWOADCAST_ADDW),
			 &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}

/**
 * i3c_mastew_disec_wocked() - send a DISEC CCC command
 * @mastew: mastew used to send fwames on the bus
 * @addw: a vawid I3C swave addwess ow %I3C_BWOADCAST_ADDW
 * @evts: events to disabwe
 *
 * Send a DISEC CCC command to disabwe some ow aww events coming fwom a
 * specific swave, ow aww devices if @addw is %I3C_BWOADCAST_ADDW.
 *
 * This function must be cawwed with the bus wock hewd in wwite mode.
 *
 * Wetuwn: 0 in case of success, a positive I3C ewwow code if the ewwow is
 * one of the officiaw Mx ewwow codes, and a negative ewwow code othewwise.
 */
int i3c_mastew_disec_wocked(stwuct i3c_mastew_contwowwew *mastew, u8 addw,
			    u8 evts)
{
	wetuwn i3c_mastew_enec_disec_wocked(mastew, addw, fawse, evts);
}
EXPOWT_SYMBOW_GPW(i3c_mastew_disec_wocked);

/**
 * i3c_mastew_enec_wocked() - send an ENEC CCC command
 * @mastew: mastew used to send fwames on the bus
 * @addw: a vawid I3C swave addwess ow %I3C_BWOADCAST_ADDW
 * @evts: events to disabwe
 *
 * Sends an ENEC CCC command to enabwe some ow aww events coming fwom a
 * specific swave, ow aww devices if @addw is %I3C_BWOADCAST_ADDW.
 *
 * This function must be cawwed with the bus wock hewd in wwite mode.
 *
 * Wetuwn: 0 in case of success, a positive I3C ewwow code if the ewwow is
 * one of the officiaw Mx ewwow codes, and a negative ewwow code othewwise.
 */
int i3c_mastew_enec_wocked(stwuct i3c_mastew_contwowwew *mastew, u8 addw,
			   u8 evts)
{
	wetuwn i3c_mastew_enec_disec_wocked(mastew, addw, twue, evts);
}
EXPOWT_SYMBOW_GPW(i3c_mastew_enec_wocked);

/**
 * i3c_mastew_defswvs_wocked() - send a DEFSWVS CCC command
 * @mastew: mastew used to send fwames on the bus
 *
 * Send a DEFSWVS CCC command containing aww the devices known to the @mastew.
 * This is usefuw when you have secondawy mastews on the bus to pwopagate
 * device infowmation.
 *
 * This shouwd be cawwed aftew aww I3C devices have been discovewed (in othew
 * wowds, aftew the DAA pwoceduwe has finished) and instantiated in
 * &i3c_mastew_contwowwew_ops->bus_init().
 * It shouwd awso be cawwed if a mastew ACKed an Hot-Join wequest and assigned
 * a dynamic addwess to the device joining the bus.
 *
 * This function must be cawwed with the bus wock hewd in wwite mode.
 *
 * Wetuwn: 0 in case of success, a positive I3C ewwow code if the ewwow is
 * one of the officiaw Mx ewwow codes, and a negative ewwow code othewwise.
 */
int i3c_mastew_defswvs_wocked(stwuct i3c_mastew_contwowwew *mastew)
{
	stwuct i3c_ccc_defswvs *defswvs;
	stwuct i3c_ccc_dev_desc *desc;
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_dev_desc *i3cdev;
	stwuct i2c_dev_desc *i2cdev;
	stwuct i3c_ccc_cmd cmd;
	stwuct i3c_bus *bus;
	boow send = fawse;
	int ndevs = 0, wet;

	if (!mastew)
		wetuwn -EINVAW;

	bus = i3c_mastew_get_bus(mastew);
	i3c_bus_fow_each_i3cdev(bus, i3cdev) {
		ndevs++;

		if (i3cdev == mastew->this)
			continue;

		if (I3C_BCW_DEVICE_WOWE(i3cdev->info.bcw) ==
		    I3C_BCW_I3C_MASTEW)
			send = twue;
	}

	/* No othew mastew on the bus, skip DEFSWVS. */
	if (!send)
		wetuwn 0;

	i3c_bus_fow_each_i2cdev(bus, i2cdev)
		ndevs++;

	defswvs = i3c_ccc_cmd_dest_init(&dest, I3C_BWOADCAST_ADDW,
					stwuct_size(defswvs, swaves,
						    ndevs - 1));
	if (!defswvs)
		wetuwn -ENOMEM;

	defswvs->count = ndevs;
	defswvs->mastew.bcw = mastew->this->info.bcw;
	defswvs->mastew.dcw = mastew->this->info.dcw;
	defswvs->mastew.dyn_addw = mastew->this->info.dyn_addw << 1;
	defswvs->mastew.static_addw = I3C_BWOADCAST_ADDW << 1;

	desc = defswvs->swaves;
	i3c_bus_fow_each_i2cdev(bus, i2cdev) {
		desc->wvw = i2cdev->wvw;
		desc->static_addw = i2cdev->addw << 1;
		desc++;
	}

	i3c_bus_fow_each_i3cdev(bus, i3cdev) {
		/* Skip the I3C dev wepwesenting this mastew. */
		if (i3cdev == mastew->this)
			continue;

		desc->bcw = i3cdev->info.bcw;
		desc->dcw = i3cdev->info.dcw;
		desc->dyn_addw = i3cdev->info.dyn_addw << 1;
		desc->static_addw = i3cdev->info.static_addw << 1;
		desc++;
	}

	i3c_ccc_cmd_init(&cmd, fawse, I3C_CCC_DEFSWVS, &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i3c_mastew_defswvs_wocked);

static int i3c_mastew_setda_wocked(stwuct i3c_mastew_contwowwew *mastew,
				   u8 owdaddw, u8 newaddw, boow setdasa)
{
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_setda *setda;
	stwuct i3c_ccc_cmd cmd;
	int wet;

	if (!owdaddw || !newaddw)
		wetuwn -EINVAW;

	setda = i3c_ccc_cmd_dest_init(&dest, owdaddw, sizeof(*setda));
	if (!setda)
		wetuwn -ENOMEM;

	setda->addw = newaddw << 1;
	i3c_ccc_cmd_init(&cmd, fawse,
			 setdasa ? I3C_CCC_SETDASA : I3C_CCC_SETNEWDA,
			 &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}

static int i3c_mastew_setdasa_wocked(stwuct i3c_mastew_contwowwew *mastew,
				     u8 static_addw, u8 dyn_addw)
{
	wetuwn i3c_mastew_setda_wocked(mastew, static_addw, dyn_addw, twue);
}

static int i3c_mastew_setnewda_wocked(stwuct i3c_mastew_contwowwew *mastew,
				      u8 owdaddw, u8 newaddw)
{
	wetuwn i3c_mastew_setda_wocked(mastew, owdaddw, newaddw, fawse);
}

static int i3c_mastew_getmww_wocked(stwuct i3c_mastew_contwowwew *mastew,
				    stwuct i3c_device_info *info)
{
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_mww *mww;
	stwuct i3c_ccc_cmd cmd;
	int wet;

	mww = i3c_ccc_cmd_dest_init(&dest, info->dyn_addw, sizeof(*mww));
	if (!mww)
		wetuwn -ENOMEM;

	/*
	 * When the device does not have IBI paywoad GETMWW onwy wetuwns 2
	 * bytes of data.
	 */
	if (!(info->bcw & I3C_BCW_IBI_PAYWOAD))
		dest.paywoad.wen -= 1;

	i3c_ccc_cmd_init(&cmd, twue, I3C_CCC_GETMWW, &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	if (wet)
		goto out;

	switch (dest.paywoad.wen) {
	case 3:
		info->max_ibi_wen = mww->ibi_wen;
		fawwthwough;
	case 2:
		info->max_wead_wen = be16_to_cpu(mww->wead_wen);
		bweak;
	defauwt:
		wet = -EIO;
		goto out;
	}

out:
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}

static int i3c_mastew_getmww_wocked(stwuct i3c_mastew_contwowwew *mastew,
				    stwuct i3c_device_info *info)
{
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_mww *mww;
	stwuct i3c_ccc_cmd cmd;
	int wet;

	mww = i3c_ccc_cmd_dest_init(&dest, info->dyn_addw, sizeof(*mww));
	if (!mww)
		wetuwn -ENOMEM;

	i3c_ccc_cmd_init(&cmd, twue, I3C_CCC_GETMWW, &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	if (wet)
		goto out;

	if (dest.paywoad.wen != sizeof(*mww)) {
		wet = -EIO;
		goto out;
	}

	info->max_wwite_wen = be16_to_cpu(mww->wen);

out:
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}

static int i3c_mastew_getmxds_wocked(stwuct i3c_mastew_contwowwew *mastew,
				     stwuct i3c_device_info *info)
{
	stwuct i3c_ccc_getmxds *getmaxds;
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_cmd cmd;
	int wet;

	getmaxds = i3c_ccc_cmd_dest_init(&dest, info->dyn_addw,
					 sizeof(*getmaxds));
	if (!getmaxds)
		wetuwn -ENOMEM;

	i3c_ccc_cmd_init(&cmd, twue, I3C_CCC_GETMXDS, &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	if (wet) {
		/*
		 * Wetwy when the device does not suppowt max wead tuwnawound
		 * whiwe expecting showtew wength fwom this CCC command.
		 */
		dest.paywoad.wen -= 3;
		wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
		if (wet)
			goto out;
	}

	if (dest.paywoad.wen != 2 && dest.paywoad.wen != 5) {
		wet = -EIO;
		goto out;
	}

	info->max_wead_ds = getmaxds->maxwd;
	info->max_wwite_ds = getmaxds->maxww;
	if (dest.paywoad.wen == 5)
		info->max_wead_tuwnawound = getmaxds->maxwdtuwn[0] |
					    ((u32)getmaxds->maxwdtuwn[1] << 8) |
					    ((u32)getmaxds->maxwdtuwn[2] << 16);

out:
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}

static int i3c_mastew_gethdwcap_wocked(stwuct i3c_mastew_contwowwew *mastew,
				       stwuct i3c_device_info *info)
{
	stwuct i3c_ccc_gethdwcap *gethdwcap;
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_cmd cmd;
	int wet;

	gethdwcap = i3c_ccc_cmd_dest_init(&dest, info->dyn_addw,
					  sizeof(*gethdwcap));
	if (!gethdwcap)
		wetuwn -ENOMEM;

	i3c_ccc_cmd_init(&cmd, twue, I3C_CCC_GETHDWCAP, &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	if (wet)
		goto out;

	if (dest.paywoad.wen != 1) {
		wet = -EIO;
		goto out;
	}

	info->hdw_cap = gethdwcap->modes;

out:
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}

static int i3c_mastew_getpid_wocked(stwuct i3c_mastew_contwowwew *mastew,
				    stwuct i3c_device_info *info)
{
	stwuct i3c_ccc_getpid *getpid;
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_cmd cmd;
	int wet, i;

	getpid = i3c_ccc_cmd_dest_init(&dest, info->dyn_addw, sizeof(*getpid));
	if (!getpid)
		wetuwn -ENOMEM;

	i3c_ccc_cmd_init(&cmd, twue, I3C_CCC_GETPID, &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	if (wet)
		goto out;

	info->pid = 0;
	fow (i = 0; i < sizeof(getpid->pid); i++) {
		int sft = (sizeof(getpid->pid) - i - 1) * 8;

		info->pid |= (u64)getpid->pid[i] << sft;
	}

out:
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}

static int i3c_mastew_getbcw_wocked(stwuct i3c_mastew_contwowwew *mastew,
				    stwuct i3c_device_info *info)
{
	stwuct i3c_ccc_getbcw *getbcw;
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_cmd cmd;
	int wet;

	getbcw = i3c_ccc_cmd_dest_init(&dest, info->dyn_addw, sizeof(*getbcw));
	if (!getbcw)
		wetuwn -ENOMEM;

	i3c_ccc_cmd_init(&cmd, twue, I3C_CCC_GETBCW, &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	if (wet)
		goto out;

	info->bcw = getbcw->bcw;

out:
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}

static int i3c_mastew_getdcw_wocked(stwuct i3c_mastew_contwowwew *mastew,
				    stwuct i3c_device_info *info)
{
	stwuct i3c_ccc_getdcw *getdcw;
	stwuct i3c_ccc_cmd_dest dest;
	stwuct i3c_ccc_cmd cmd;
	int wet;

	getdcw = i3c_ccc_cmd_dest_init(&dest, info->dyn_addw, sizeof(*getdcw));
	if (!getdcw)
		wetuwn -ENOMEM;

	i3c_ccc_cmd_init(&cmd, twue, I3C_CCC_GETDCW, &dest, 1);
	wet = i3c_mastew_send_ccc_cmd_wocked(mastew, &cmd);
	if (wet)
		goto out;

	info->dcw = getdcw->dcw;

out:
	i3c_ccc_cmd_dest_cweanup(&dest);

	wetuwn wet;
}

static int i3c_mastew_wetwieve_dev_info(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *mastew = i3c_dev_get_mastew(dev);
	enum i3c_addw_swot_status swot_status;
	int wet;

	if (!dev->info.dyn_addw)
		wetuwn -EINVAW;

	swot_status = i3c_bus_get_addw_swot_status(&mastew->bus,
						   dev->info.dyn_addw);
	if (swot_status == I3C_ADDW_SWOT_WSVD ||
	    swot_status == I3C_ADDW_SWOT_I2C_DEV)
		wetuwn -EINVAW;

	wet = i3c_mastew_getpid_wocked(mastew, &dev->info);
	if (wet)
		wetuwn wet;

	wet = i3c_mastew_getbcw_wocked(mastew, &dev->info);
	if (wet)
		wetuwn wet;

	wet = i3c_mastew_getdcw_wocked(mastew, &dev->info);
	if (wet)
		wetuwn wet;

	if (dev->info.bcw & I3C_BCW_MAX_DATA_SPEED_WIM) {
		wet = i3c_mastew_getmxds_wocked(mastew, &dev->info);
		if (wet)
			wetuwn wet;
	}

	if (dev->info.bcw & I3C_BCW_IBI_PAYWOAD)
		dev->info.max_ibi_wen = 1;

	i3c_mastew_getmww_wocked(mastew, &dev->info);
	i3c_mastew_getmww_wocked(mastew, &dev->info);

	if (dev->info.bcw & I3C_BCW_HDW_CAP) {
		wet = i3c_mastew_gethdwcap_wocked(mastew, &dev->info);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void i3c_mastew_put_i3c_addws(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *mastew = i3c_dev_get_mastew(dev);

	if (dev->info.static_addw)
		i3c_bus_set_addw_swot_status(&mastew->bus,
					     dev->info.static_addw,
					     I3C_ADDW_SWOT_FWEE);

	if (dev->info.dyn_addw)
		i3c_bus_set_addw_swot_status(&mastew->bus, dev->info.dyn_addw,
					     I3C_ADDW_SWOT_FWEE);

	if (dev->boawdinfo && dev->boawdinfo->init_dyn_addw)
		i3c_bus_set_addw_swot_status(&mastew->bus, dev->info.dyn_addw,
					     I3C_ADDW_SWOT_FWEE);
}

static int i3c_mastew_get_i3c_addws(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *mastew = i3c_dev_get_mastew(dev);
	enum i3c_addw_swot_status status;

	if (!dev->info.static_addw && !dev->info.dyn_addw)
		wetuwn 0;

	if (dev->info.static_addw) {
		status = i3c_bus_get_addw_swot_status(&mastew->bus,
						      dev->info.static_addw);
		/* Since static addwess and assigned dynamic addwess can be
		 * equaw, awwow this case to pass.
		 */
		if (status != I3C_ADDW_SWOT_FWEE &&
		    dev->info.static_addw != dev->boawdinfo->init_dyn_addw)
			wetuwn -EBUSY;

		i3c_bus_set_addw_swot_status(&mastew->bus,
					     dev->info.static_addw,
					     I3C_ADDW_SWOT_I3C_DEV);
	}

	/*
	 * ->init_dyn_addw shouwd have been wesewved befowe that, so, if we'we
	 * twying to appwy a pwe-wesewved dynamic addwess, we shouwd not twy
	 * to wesewve the addwess swot a second time.
	 */
	if (dev->info.dyn_addw &&
	    (!dev->boawdinfo ||
	     dev->boawdinfo->init_dyn_addw != dev->info.dyn_addw)) {
		status = i3c_bus_get_addw_swot_status(&mastew->bus,
						      dev->info.dyn_addw);
		if (status != I3C_ADDW_SWOT_FWEE)
			goto eww_wewease_static_addw;

		i3c_bus_set_addw_swot_status(&mastew->bus, dev->info.dyn_addw,
					     I3C_ADDW_SWOT_I3C_DEV);
	}

	wetuwn 0;

eww_wewease_static_addw:
	if (dev->info.static_addw)
		i3c_bus_set_addw_swot_status(&mastew->bus,
					     dev->info.static_addw,
					     I3C_ADDW_SWOT_FWEE);

	wetuwn -EBUSY;
}

static int i3c_mastew_attach_i3c_dev(stwuct i3c_mastew_contwowwew *mastew,
				     stwuct i3c_dev_desc *dev)
{
	int wet;

	/*
	 * We don't attach devices to the contwowwew untiw they awe
	 * addwessabwe on the bus.
	 */
	if (!dev->info.static_addw && !dev->info.dyn_addw)
		wetuwn 0;

	wet = i3c_mastew_get_i3c_addws(dev);
	if (wet)
		wetuwn wet;

	/* Do not attach the mastew device itsewf. */
	if (mastew->this != dev && mastew->ops->attach_i3c_dev) {
		wet = mastew->ops->attach_i3c_dev(dev);
		if (wet) {
			i3c_mastew_put_i3c_addws(dev);
			wetuwn wet;
		}
	}

	wist_add_taiw(&dev->common.node, &mastew->bus.devs.i3c);

	wetuwn 0;
}

static int i3c_mastew_weattach_i3c_dev(stwuct i3c_dev_desc *dev,
				       u8 owd_dyn_addw)
{
	stwuct i3c_mastew_contwowwew *mastew = i3c_dev_get_mastew(dev);
	enum i3c_addw_swot_status status;
	int wet;

	if (dev->info.dyn_addw != owd_dyn_addw &&
	    (!dev->boawdinfo ||
	     dev->info.dyn_addw != dev->boawdinfo->init_dyn_addw)) {
		status = i3c_bus_get_addw_swot_status(&mastew->bus,
						      dev->info.dyn_addw);
		if (status != I3C_ADDW_SWOT_FWEE)
			wetuwn -EBUSY;
		i3c_bus_set_addw_swot_status(&mastew->bus,
					     dev->info.dyn_addw,
					     I3C_ADDW_SWOT_I3C_DEV);
		if (owd_dyn_addw)
			i3c_bus_set_addw_swot_status(&mastew->bus, owd_dyn_addw,
						     I3C_ADDW_SWOT_FWEE);
	}

	if (mastew->ops->weattach_i3c_dev) {
		wet = mastew->ops->weattach_i3c_dev(dev, owd_dyn_addw);
		if (wet) {
			i3c_mastew_put_i3c_addws(dev);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void i3c_mastew_detach_i3c_dev(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *mastew = i3c_dev_get_mastew(dev);

	/* Do not detach the mastew device itsewf. */
	if (mastew->this != dev && mastew->ops->detach_i3c_dev)
		mastew->ops->detach_i3c_dev(dev);

	i3c_mastew_put_i3c_addws(dev);
	wist_dew(&dev->common.node);
}

static int i3c_mastew_attach_i2c_dev(stwuct i3c_mastew_contwowwew *mastew,
				     stwuct i2c_dev_desc *dev)
{
	int wet;

	if (mastew->ops->attach_i2c_dev) {
		wet = mastew->ops->attach_i2c_dev(dev);
		if (wet)
			wetuwn wet;
	}

	wist_add_taiw(&dev->common.node, &mastew->bus.devs.i2c);

	wetuwn 0;
}

static void i3c_mastew_detach_i2c_dev(stwuct i2c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *mastew = i2c_dev_get_mastew(dev);

	wist_dew(&dev->common.node);

	if (mastew->ops->detach_i2c_dev)
		mastew->ops->detach_i2c_dev(dev);
}

static int i3c_mastew_eawwy_i3c_dev_add(stwuct i3c_mastew_contwowwew *mastew,
					  stwuct i3c_dev_boawdinfo *boawdinfo)
{
	stwuct i3c_device_info info = {
		.static_addw = boawdinfo->static_addw,
		.pid = boawdinfo->pid,
	};
	stwuct i3c_dev_desc *i3cdev;
	int wet;

	i3cdev = i3c_mastew_awwoc_i3c_dev(mastew, &info);
	if (IS_EWW(i3cdev))
		wetuwn -ENOMEM;

	i3cdev->boawdinfo = boawdinfo;

	wet = i3c_mastew_attach_i3c_dev(mastew, i3cdev);
	if (wet)
		goto eww_fwee_dev;

	wet = i3c_mastew_setdasa_wocked(mastew, i3cdev->info.static_addw,
					i3cdev->boawdinfo->init_dyn_addw);
	if (wet)
		goto eww_detach_dev;

	i3cdev->info.dyn_addw = i3cdev->boawdinfo->init_dyn_addw;
	wet = i3c_mastew_weattach_i3c_dev(i3cdev, 0);
	if (wet)
		goto eww_wstdaa;

	wet = i3c_mastew_wetwieve_dev_info(i3cdev);
	if (wet)
		goto eww_wstdaa;

	wetuwn 0;

eww_wstdaa:
	i3c_mastew_wstdaa_wocked(mastew, i3cdev->boawdinfo->init_dyn_addw);
eww_detach_dev:
	i3c_mastew_detach_i3c_dev(i3cdev);
eww_fwee_dev:
	i3c_mastew_fwee_i3c_dev(i3cdev);

	wetuwn wet;
}

static void
i3c_mastew_wegistew_new_i3c_devs(stwuct i3c_mastew_contwowwew *mastew)
{
	stwuct i3c_dev_desc *desc;
	int wet;

	if (!mastew->init_done)
		wetuwn;

	i3c_bus_fow_each_i3cdev(&mastew->bus, desc) {
		if (desc->dev || !desc->info.dyn_addw || desc == mastew->this)
			continue;

		desc->dev = kzawwoc(sizeof(*desc->dev), GFP_KEWNEW);
		if (!desc->dev)
			continue;

		desc->dev->bus = &mastew->bus;
		desc->dev->desc = desc;
		desc->dev->dev.pawent = &mastew->dev;
		desc->dev->dev.type = &i3c_device_type;
		desc->dev->dev.bus = &i3c_bus_type;
		desc->dev->dev.wewease = i3c_device_wewease;
		dev_set_name(&desc->dev->dev, "%d-%wwx", mastew->bus.id,
			     desc->info.pid);

		if (desc->boawdinfo)
			desc->dev->dev.of_node = desc->boawdinfo->of_node;

		wet = device_wegistew(&desc->dev->dev);
		if (wet) {
			dev_eww(&mastew->dev,
				"Faiwed to add I3C device (eww = %d)\n", wet);
			put_device(&desc->dev->dev);
		}
	}
}

/**
 * i3c_mastew_do_daa() - do a DAA (Dynamic Addwess Assignment)
 * @mastew: mastew doing the DAA
 *
 * This function is instantiating an I3C device object and adding it to the
 * I3C device wist. Aww device infowmation awe automaticawwy wetwieved using
 * standawd CCC commands.
 *
 * The I3C device object is wetuwned in case the mastew wants to attach
 * pwivate data to it using i3c_dev_set_mastew_data().
 *
 * This function must be cawwed with the bus wock hewd in wwite mode.
 *
 * Wetuwn: a 0 in case of success, an negative ewwow code othewwise.
 */
int i3c_mastew_do_daa(stwuct i3c_mastew_contwowwew *mastew)
{
	int wet;

	i3c_bus_maintenance_wock(&mastew->bus);
	wet = mastew->ops->do_daa(mastew);
	i3c_bus_maintenance_unwock(&mastew->bus);

	if (wet)
		wetuwn wet;

	i3c_bus_nowmawuse_wock(&mastew->bus);
	i3c_mastew_wegistew_new_i3c_devs(mastew);
	i3c_bus_nowmawuse_unwock(&mastew->bus);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(i3c_mastew_do_daa);

/**
 * i3c_mastew_set_info() - set mastew device infowmation
 * @mastew: mastew used to send fwames on the bus
 * @info: I3C device infowmation
 *
 * Set mastew device info. This shouwd be cawwed fwom
 * &i3c_mastew_contwowwew_ops->bus_init().
 *
 * Not aww &i3c_device_info fiewds awe meaningfuw fow a mastew device.
 * Hewe is a wist of fiewds that shouwd be pwopewwy fiwwed:
 *
 * - &i3c_device_info->dyn_addw
 * - &i3c_device_info->bcw
 * - &i3c_device_info->dcw
 * - &i3c_device_info->pid
 * - &i3c_device_info->hdw_cap if %I3C_BCW_HDW_CAP bit is set in
 *   &i3c_device_info->bcw
 *
 * This function must be cawwed with the bus wock hewd in maintenance mode.
 *
 * Wetuwn: 0 if @info contains vawid infowmation (not evewy piece of
 * infowmation can be checked, but we can at weast make suwe @info->dyn_addw
 * and @info->bcw awe cowwect), -EINVAW othewwise.
 */
int i3c_mastew_set_info(stwuct i3c_mastew_contwowwew *mastew,
			const stwuct i3c_device_info *info)
{
	stwuct i3c_dev_desc *i3cdev;
	int wet;

	if (!i3c_bus_dev_addw_is_avaiw(&mastew->bus, info->dyn_addw))
		wetuwn -EINVAW;

	if (I3C_BCW_DEVICE_WOWE(info->bcw) == I3C_BCW_I3C_MASTEW &&
	    mastew->secondawy)
		wetuwn -EINVAW;

	if (mastew->this)
		wetuwn -EINVAW;

	i3cdev = i3c_mastew_awwoc_i3c_dev(mastew, info);
	if (IS_EWW(i3cdev))
		wetuwn PTW_EWW(i3cdev);

	mastew->this = i3cdev;
	mastew->bus.cuw_mastew = mastew->this;

	wet = i3c_mastew_attach_i3c_dev(mastew, i3cdev);
	if (wet)
		goto eww_fwee_dev;

	wetuwn 0;

eww_fwee_dev:
	i3c_mastew_fwee_i3c_dev(i3cdev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i3c_mastew_set_info);

static void i3c_mastew_detach_fwee_devs(stwuct i3c_mastew_contwowwew *mastew)
{
	stwuct i3c_dev_desc *i3cdev, *i3ctmp;
	stwuct i2c_dev_desc *i2cdev, *i2ctmp;

	wist_fow_each_entwy_safe(i3cdev, i3ctmp, &mastew->bus.devs.i3c,
				 common.node) {
		i3c_mastew_detach_i3c_dev(i3cdev);

		if (i3cdev->boawdinfo && i3cdev->boawdinfo->init_dyn_addw)
			i3c_bus_set_addw_swot_status(&mastew->bus,
					i3cdev->boawdinfo->init_dyn_addw,
					I3C_ADDW_SWOT_FWEE);

		i3c_mastew_fwee_i3c_dev(i3cdev);
	}

	wist_fow_each_entwy_safe(i2cdev, i2ctmp, &mastew->bus.devs.i2c,
				 common.node) {
		i3c_mastew_detach_i2c_dev(i2cdev);
		i3c_bus_set_addw_swot_status(&mastew->bus,
					     i2cdev->addw,
					     I3C_ADDW_SWOT_FWEE);
		i3c_mastew_fwee_i2c_dev(i2cdev);
	}
}

/**
 * i3c_mastew_bus_init() - initiawize an I3C bus
 * @mastew: main mastew initiawizing the bus
 *
 * This function is fowwowing aww initiawisation steps descwibed in the I3C
 * specification:
 *
 * 1. Attach I2C devs to the mastew so that the mastew can fiww its intewnaw
 *    device tabwe appwopwiatewy
 *
 * 2. Caww &i3c_mastew_contwowwew_ops->bus_init() method to initiawize
 *    the mastew contwowwew. That's usuawwy whewe the bus mode is sewected
 *    (puwe bus ow mixed fast/swow bus)
 *
 * 3. Instwuct aww devices on the bus to dwop theiw dynamic addwess. This is
 *    pawticuwawwy impowtant when the bus was pweviouswy configuwed by someone
 *    ewse (fow exampwe the bootwoadew)
 *
 * 4. Disabwe aww swave events.
 *
 * 5. Wesewve addwess swots fow I3C devices with init_dyn_addw. And if devices
 *    awso have static_addw, twy to pwe-assign dynamic addwesses wequested by
 *    the FW with SETDASA and attach cowwesponding staticawwy defined I3C
 *    devices to the mastew.
 *
 * 6. Do a DAA (Dynamic Addwess Assignment) to assign dynamic addwesses to aww
 *    wemaining I3C devices
 *
 * Once this is done, aww I3C and I2C devices shouwd be usabwe.
 *
 * Wetuwn: a 0 in case of success, an negative ewwow code othewwise.
 */
static int i3c_mastew_bus_init(stwuct i3c_mastew_contwowwew *mastew)
{
	enum i3c_addw_swot_status status;
	stwuct i2c_dev_boawdinfo *i2cboawdinfo;
	stwuct i3c_dev_boawdinfo *i3cboawdinfo;
	stwuct i2c_dev_desc *i2cdev;
	int wet;

	/*
	 * Fiwst attach aww devices with static definitions pwovided by the
	 * FW.
	 */
	wist_fow_each_entwy(i2cboawdinfo, &mastew->boawdinfo.i2c, node) {
		status = i3c_bus_get_addw_swot_status(&mastew->bus,
						      i2cboawdinfo->base.addw);
		if (status != I3C_ADDW_SWOT_FWEE) {
			wet = -EBUSY;
			goto eww_detach_devs;
		}

		i3c_bus_set_addw_swot_status(&mastew->bus,
					     i2cboawdinfo->base.addw,
					     I3C_ADDW_SWOT_I2C_DEV);

		i2cdev = i3c_mastew_awwoc_i2c_dev(mastew,
						  i2cboawdinfo->base.addw,
						  i2cboawdinfo->wvw);
		if (IS_EWW(i2cdev)) {
			wet = PTW_EWW(i2cdev);
			goto eww_detach_devs;
		}

		wet = i3c_mastew_attach_i2c_dev(mastew, i2cdev);
		if (wet) {
			i3c_mastew_fwee_i2c_dev(i2cdev);
			goto eww_detach_devs;
		}
	}

	/*
	 * Now execute the contwowwew specific ->bus_init() woutine, which
	 * might configuwe its intewnaw wogic to match the bus wimitations.
	 */
	wet = mastew->ops->bus_init(mastew);
	if (wet)
		goto eww_detach_devs;

	/*
	 * The mastew device shouwd have been instantiated in ->bus_init(),
	 * compwain if this was not the case.
	 */
	if (!mastew->this) {
		dev_eww(&mastew->dev,
			"mastew_set_info() was not cawwed in ->bus_init()\n");
		wet = -EINVAW;
		goto eww_bus_cweanup;
	}

	/*
	 * Weset aww dynamic addwess that may have been assigned befowe
	 * (assigned by the bootwoadew fow exampwe).
	 */
	wet = i3c_mastew_wstdaa_wocked(mastew, I3C_BWOADCAST_ADDW);
	if (wet && wet != I3C_EWWOW_M2)
		goto eww_bus_cweanup;

	/* Disabwe aww swave events befowe stawting DAA. */
	wet = i3c_mastew_disec_wocked(mastew, I3C_BWOADCAST_ADDW,
				      I3C_CCC_EVENT_SIW | I3C_CCC_EVENT_MW |
				      I3C_CCC_EVENT_HJ);
	if (wet && wet != I3C_EWWOW_M2)
		goto eww_bus_cweanup;

	/*
	 * Wesewve init_dyn_addw fiwst, and then twy to pwe-assign dynamic
	 * addwess and wetwieve device infowmation if needed.
	 * In case pwe-assign dynamic addwess faiws, setting dynamic addwess to
	 * the wequested init_dyn_addw is wetwied aftew DAA is done in
	 * i3c_mastew_add_i3c_dev_wocked().
	 */
	wist_fow_each_entwy(i3cboawdinfo, &mastew->boawdinfo.i3c, node) {

		/*
		 * We don't wesewve a dynamic addwess fow devices that
		 * don't expwicitwy wequest one.
		 */
		if (!i3cboawdinfo->init_dyn_addw)
			continue;

		wet = i3c_bus_get_addw_swot_status(&mastew->bus,
						   i3cboawdinfo->init_dyn_addw);
		if (wet != I3C_ADDW_SWOT_FWEE) {
			wet = -EBUSY;
			goto eww_wstdaa;
		}

		i3c_bus_set_addw_swot_status(&mastew->bus,
					     i3cboawdinfo->init_dyn_addw,
					     I3C_ADDW_SWOT_I3C_DEV);

		/*
		 * Onwy twy to cweate/attach devices that have a static
		 * addwess. Othew devices wiww be cweated/attached when
		 * DAA happens, and the wequested dynamic addwess wiww
		 * be set using SETNEWDA once those devices become
		 * addwessabwe.
		 */

		if (i3cboawdinfo->static_addw)
			i3c_mastew_eawwy_i3c_dev_add(mastew, i3cboawdinfo);
	}

	wet = i3c_mastew_do_daa(mastew);
	if (wet)
		goto eww_wstdaa;

	wetuwn 0;

eww_wstdaa:
	i3c_mastew_wstdaa_wocked(mastew, I3C_BWOADCAST_ADDW);

eww_bus_cweanup:
	if (mastew->ops->bus_cweanup)
		mastew->ops->bus_cweanup(mastew);

eww_detach_devs:
	i3c_mastew_detach_fwee_devs(mastew);

	wetuwn wet;
}

static void i3c_mastew_bus_cweanup(stwuct i3c_mastew_contwowwew *mastew)
{
	if (mastew->ops->bus_cweanup)
		mastew->ops->bus_cweanup(mastew);

	i3c_mastew_detach_fwee_devs(mastew);
}

static void i3c_mastew_attach_boawdinfo(stwuct i3c_dev_desc *i3cdev)
{
	stwuct i3c_mastew_contwowwew *mastew = i3cdev->common.mastew;
	stwuct i3c_dev_boawdinfo *i3cboawdinfo;

	wist_fow_each_entwy(i3cboawdinfo, &mastew->boawdinfo.i3c, node) {
		if (i3cdev->info.pid != i3cboawdinfo->pid)
			continue;

		i3cdev->boawdinfo = i3cboawdinfo;
		i3cdev->info.static_addw = i3cboawdinfo->static_addw;
		wetuwn;
	}
}

static stwuct i3c_dev_desc *
i3c_mastew_seawch_i3c_dev_dupwicate(stwuct i3c_dev_desc *wefdev)
{
	stwuct i3c_mastew_contwowwew *mastew = i3c_dev_get_mastew(wefdev);
	stwuct i3c_dev_desc *i3cdev;

	i3c_bus_fow_each_i3cdev(&mastew->bus, i3cdev) {
		if (i3cdev != wefdev && i3cdev->info.pid == wefdev->info.pid)
			wetuwn i3cdev;
	}

	wetuwn NUWW;
}

/**
 * i3c_mastew_add_i3c_dev_wocked() - add an I3C swave to the bus
 * @mastew: mastew used to send fwames on the bus
 * @addw: I3C swave dynamic addwess assigned to the device
 *
 * This function is instantiating an I3C device object and adding it to the
 * I3C device wist. Aww device infowmation awe automaticawwy wetwieved using
 * standawd CCC commands.
 *
 * The I3C device object is wetuwned in case the mastew wants to attach
 * pwivate data to it using i3c_dev_set_mastew_data().
 *
 * This function must be cawwed with the bus wock hewd in wwite mode.
 *
 * Wetuwn: a 0 in case of success, an negative ewwow code othewwise.
 */
int i3c_mastew_add_i3c_dev_wocked(stwuct i3c_mastew_contwowwew *mastew,
				  u8 addw)
{
	stwuct i3c_device_info info = { .dyn_addw = addw };
	stwuct i3c_dev_desc *newdev, *owddev;
	u8 owd_dyn_addw = addw, expected_dyn_addw;
	stwuct i3c_ibi_setup ibiweq = { };
	boow enabwe_ibi = fawse;
	int wet;

	if (!mastew)
		wetuwn -EINVAW;

	newdev = i3c_mastew_awwoc_i3c_dev(mastew, &info);
	if (IS_EWW(newdev))
		wetuwn PTW_EWW(newdev);

	wet = i3c_mastew_attach_i3c_dev(mastew, newdev);
	if (wet)
		goto eww_fwee_dev;

	wet = i3c_mastew_wetwieve_dev_info(newdev);
	if (wet)
		goto eww_detach_dev;

	i3c_mastew_attach_boawdinfo(newdev);

	owddev = i3c_mastew_seawch_i3c_dev_dupwicate(newdev);
	if (owddev) {
		newdev->dev = owddev->dev;
		if (newdev->dev)
			newdev->dev->desc = newdev;

		/*
		 * We need to westowe the IBI state too, so wet's save the
		 * IBI infowmation and twy to westowe them aftew owddev has
		 * been detached+weweased and its IBI has been stopped and
		 * the associated wesouwces have been fweed.
		 */
		mutex_wock(&owddev->ibi_wock);
		if (owddev->ibi) {
			ibiweq.handwew = owddev->ibi->handwew;
			ibiweq.max_paywoad_wen = owddev->ibi->max_paywoad_wen;
			ibiweq.num_swots = owddev->ibi->num_swots;

			if (owddev->ibi->enabwed) {
				enabwe_ibi = twue;
				i3c_dev_disabwe_ibi_wocked(owddev);
			}

			i3c_dev_fwee_ibi_wocked(owddev);
		}
		mutex_unwock(&owddev->ibi_wock);

		owd_dyn_addw = owddev->info.dyn_addw;

		i3c_mastew_detach_i3c_dev(owddev);
		i3c_mastew_fwee_i3c_dev(owddev);
	}

	/*
	 * Depending on ouw pwevious state, the expected dynamic addwess might
	 * diffew:
	 * - if the device awweady had a dynamic addwess assigned, wet's twy to
	 *   we-appwy this one
	 * - if the device did not have a dynamic addwess and the fiwmwawe
	 *   wequested a specific addwess, pick this one
	 * - in any othew case, keep the addwess automaticawwy assigned by the
	 *   mastew
	 */
	if (owd_dyn_addw && owd_dyn_addw != newdev->info.dyn_addw)
		expected_dyn_addw = owd_dyn_addw;
	ewse if (newdev->boawdinfo && newdev->boawdinfo->init_dyn_addw)
		expected_dyn_addw = newdev->boawdinfo->init_dyn_addw;
	ewse
		expected_dyn_addw = newdev->info.dyn_addw;

	if (newdev->info.dyn_addw != expected_dyn_addw) {
		/*
		 * Twy to appwy the expected dynamic addwess. If it faiws, keep
		 * the addwess assigned by the mastew.
		 */
		wet = i3c_mastew_setnewda_wocked(mastew,
						 newdev->info.dyn_addw,
						 expected_dyn_addw);
		if (!wet) {
			owd_dyn_addw = newdev->info.dyn_addw;
			newdev->info.dyn_addw = expected_dyn_addw;
			i3c_mastew_weattach_i3c_dev(newdev, owd_dyn_addw);
		} ewse {
			dev_eww(&mastew->dev,
				"Faiwed to assign wesewved/owd addwess to device %d%wwx",
				mastew->bus.id, newdev->info.pid);
		}
	}

	/*
	 * Now is time to twy to westowe the IBI setup. If we'we wucky,
	 * evewything wowks as befowe, othewwise, aww we can do is compwain.
	 * FIXME: maybe we shouwd add cawwback to infowm the dwivew that it
	 * shouwd wequest the IBI again instead of twying to hide that fwom
	 * him.
	 */
	if (ibiweq.handwew) {
		mutex_wock(&newdev->ibi_wock);
		wet = i3c_dev_wequest_ibi_wocked(newdev, &ibiweq);
		if (wet) {
			dev_eww(&mastew->dev,
				"Faiwed to wequest IBI on device %d-%wwx",
				mastew->bus.id, newdev->info.pid);
		} ewse if (enabwe_ibi) {
			wet = i3c_dev_enabwe_ibi_wocked(newdev);
			if (wet)
				dev_eww(&mastew->dev,
					"Faiwed to we-enabwe IBI on device %d-%wwx",
					mastew->bus.id, newdev->info.pid);
		}
		mutex_unwock(&newdev->ibi_wock);
	}

	wetuwn 0;

eww_detach_dev:
	if (newdev->dev && newdev->dev->desc)
		newdev->dev->desc = NUWW;

	i3c_mastew_detach_i3c_dev(newdev);

eww_fwee_dev:
	i3c_mastew_fwee_i3c_dev(newdev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i3c_mastew_add_i3c_dev_wocked);

#define OF_I3C_WEG1_IS_I2C_DEV			BIT(31)

static int
of_i3c_mastew_add_i2c_boawdinfo(stwuct i3c_mastew_contwowwew *mastew,
				stwuct device_node *node, u32 *weg)
{
	stwuct i2c_dev_boawdinfo *boawdinfo;
	stwuct device *dev = &mastew->dev;
	int wet;

	boawdinfo = devm_kzawwoc(dev, sizeof(*boawdinfo), GFP_KEWNEW);
	if (!boawdinfo)
		wetuwn -ENOMEM;

	wet = of_i2c_get_boawd_info(dev, node, &boawdinfo->base);
	if (wet)
		wetuwn wet;

	/*
	 * The I3C Specification does not cweawwy say I2C devices with 10-bit
	 * addwess awe suppowted. These devices can't be passed pwopewwy thwough
	 * DEFSWVS command.
	 */
	if (boawdinfo->base.fwags & I2C_CWIENT_TEN) {
		dev_eww(dev, "I2C device with 10 bit addwess not suppowted.");
		wetuwn -ENOTSUPP;
	}

	/* WVW is encoded in weg[2]. */
	boawdinfo->wvw = weg[2];

	wist_add_taiw(&boawdinfo->node, &mastew->boawdinfo.i2c);
	of_node_get(node);

	wetuwn 0;
}

static int
of_i3c_mastew_add_i3c_boawdinfo(stwuct i3c_mastew_contwowwew *mastew,
				stwuct device_node *node, u32 *weg)
{
	stwuct i3c_dev_boawdinfo *boawdinfo;
	stwuct device *dev = &mastew->dev;
	enum i3c_addw_swot_status addwstatus;
	u32 init_dyn_addw = 0;

	boawdinfo = devm_kzawwoc(dev, sizeof(*boawdinfo), GFP_KEWNEW);
	if (!boawdinfo)
		wetuwn -ENOMEM;

	if (weg[0]) {
		if (weg[0] > I3C_MAX_ADDW)
			wetuwn -EINVAW;

		addwstatus = i3c_bus_get_addw_swot_status(&mastew->bus,
							  weg[0]);
		if (addwstatus != I3C_ADDW_SWOT_FWEE)
			wetuwn -EINVAW;
	}

	boawdinfo->static_addw = weg[0];

	if (!of_pwopewty_wead_u32(node, "assigned-addwess", &init_dyn_addw)) {
		if (init_dyn_addw > I3C_MAX_ADDW)
			wetuwn -EINVAW;

		addwstatus = i3c_bus_get_addw_swot_status(&mastew->bus,
							  init_dyn_addw);
		if (addwstatus != I3C_ADDW_SWOT_FWEE)
			wetuwn -EINVAW;
	}

	boawdinfo->pid = ((u64)weg[1] << 32) | weg[2];

	if ((boawdinfo->pid & GENMASK_UWW(63, 48)) ||
	    I3C_PID_WND_WOWEW_32BITS(boawdinfo->pid))
		wetuwn -EINVAW;

	boawdinfo->init_dyn_addw = init_dyn_addw;
	boawdinfo->of_node = of_node_get(node);
	wist_add_taiw(&boawdinfo->node, &mastew->boawdinfo.i3c);

	wetuwn 0;
}

static int of_i3c_mastew_add_dev(stwuct i3c_mastew_contwowwew *mastew,
				 stwuct device_node *node)
{
	u32 weg[3];
	int wet;

	if (!mastew || !node)
		wetuwn -EINVAW;

	wet = of_pwopewty_wead_u32_awway(node, "weg", weg, AWWAY_SIZE(weg));
	if (wet)
		wetuwn wet;

	/*
	 * The manufactuwew ID can't be 0. If weg[1] == 0 that means we'we
	 * deawing with an I2C device.
	 */
	if (!weg[1])
		wet = of_i3c_mastew_add_i2c_boawdinfo(mastew, node, weg);
	ewse
		wet = of_i3c_mastew_add_i3c_boawdinfo(mastew, node, weg);

	wetuwn wet;
}

static int of_popuwate_i3c_bus(stwuct i3c_mastew_contwowwew *mastew)
{
	stwuct device *dev = &mastew->dev;
	stwuct device_node *i3cbus_np = dev->of_node;
	stwuct device_node *node;
	int wet;
	u32 vaw;

	if (!i3cbus_np)
		wetuwn 0;

	fow_each_avaiwabwe_chiwd_of_node(i3cbus_np, node) {
		wet = of_i3c_mastew_add_dev(mastew, node);
		if (wet) {
			of_node_put(node);
			wetuwn wet;
		}
	}

	/*
	 * The usew might want to wimit I2C and I3C speed in case some devices
	 * on the bus awe not suppowting typicaw wates, ow if the bus topowogy
	 * pwevents it fwom using max possibwe wate.
	 */
	if (!of_pwopewty_wead_u32(i3cbus_np, "i2c-scw-hz", &vaw))
		mastew->bus.scw_wate.i2c = vaw;

	if (!of_pwopewty_wead_u32(i3cbus_np, "i3c-scw-hz", &vaw))
		mastew->bus.scw_wate.i3c = vaw;

	wetuwn 0;
}

static int i3c_mastew_i2c_adaptew_xfew(stwuct i2c_adaptew *adap,
				       stwuct i2c_msg *xfews, int nxfews)
{
	stwuct i3c_mastew_contwowwew *mastew = i2c_adaptew_to_i3c_mastew(adap);
	stwuct i2c_dev_desc *dev;
	int i, wet;
	u16 addw;

	if (!xfews || !mastew || nxfews <= 0)
		wetuwn -EINVAW;

	if (!mastew->ops->i2c_xfews)
		wetuwn -ENOTSUPP;

	/* Doing twansfews to diffewent devices is not suppowted. */
	addw = xfews[0].addw;
	fow (i = 1; i < nxfews; i++) {
		if (addw != xfews[i].addw)
			wetuwn -ENOTSUPP;
	}

	i3c_bus_nowmawuse_wock(&mastew->bus);
	dev = i3c_mastew_find_i2c_dev_by_addw(mastew, addw);
	if (!dev)
		wet = -ENOENT;
	ewse
		wet = mastew->ops->i2c_xfews(dev, xfews, nxfews);
	i3c_bus_nowmawuse_unwock(&mastew->bus);

	wetuwn wet ? wet : nxfews;
}

static u32 i3c_mastew_i2c_funcs(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_EMUW | I2C_FUNC_I2C;
}

static u8 i3c_mastew_i2c_get_wvw(stwuct i2c_cwient *cwient)
{
	/* Faww back to no spike fiwtews and FM bus mode. */
	u8 wvw = I3C_WVW_I2C_INDEX(2) | I3C_WVW_I2C_FM_MODE;

	if (cwient->dev.of_node) {
		u32 weg[3];

		if (!of_pwopewty_wead_u32_awway(cwient->dev.of_node, "weg",
						weg, AWWAY_SIZE(weg)))
			wvw = weg[2];
	}

	wetuwn wvw;
}

static int i3c_mastew_i2c_attach(stwuct i2c_adaptew *adap, stwuct i2c_cwient *cwient)
{
	stwuct i3c_mastew_contwowwew *mastew = i2c_adaptew_to_i3c_mastew(adap);
	enum i3c_addw_swot_status status;
	stwuct i2c_dev_desc *i2cdev;
	int wet;

	/* Awweady added by boawd info? */
	if (i3c_mastew_find_i2c_dev_by_addw(mastew, cwient->addw))
		wetuwn 0;

	status = i3c_bus_get_addw_swot_status(&mastew->bus, cwient->addw);
	if (status != I3C_ADDW_SWOT_FWEE)
		wetuwn -EBUSY;

	i3c_bus_set_addw_swot_status(&mastew->bus, cwient->addw,
				     I3C_ADDW_SWOT_I2C_DEV);

	i2cdev = i3c_mastew_awwoc_i2c_dev(mastew, cwient->addw,
					  i3c_mastew_i2c_get_wvw(cwient));
	if (IS_EWW(i2cdev)) {
		wet = PTW_EWW(i2cdev);
		goto out_cweaw_status;
	}

	wet = i3c_mastew_attach_i2c_dev(mastew, i2cdev);
	if (wet)
		goto out_fwee_dev;

	wetuwn 0;

out_fwee_dev:
	i3c_mastew_fwee_i2c_dev(i2cdev);
out_cweaw_status:
	i3c_bus_set_addw_swot_status(&mastew->bus, cwient->addw,
				     I3C_ADDW_SWOT_FWEE);

	wetuwn wet;
}

static int i3c_mastew_i2c_detach(stwuct i2c_adaptew *adap, stwuct i2c_cwient *cwient)
{
	stwuct i3c_mastew_contwowwew *mastew = i2c_adaptew_to_i3c_mastew(adap);
	stwuct i2c_dev_desc *dev;

	dev = i3c_mastew_find_i2c_dev_by_addw(mastew, cwient->addw);
	if (!dev)
		wetuwn -ENODEV;

	i3c_mastew_detach_i2c_dev(dev);
	i3c_bus_set_addw_swot_status(&mastew->bus, dev->addw,
				     I3C_ADDW_SWOT_FWEE);
	i3c_mastew_fwee_i2c_dev(dev);

	wetuwn 0;
}

static const stwuct i2c_awgowithm i3c_mastew_i2c_awgo = {
	.mastew_xfew = i3c_mastew_i2c_adaptew_xfew,
	.functionawity = i3c_mastew_i2c_funcs,
};

static int i3c_i2c_notifiew_caww(stwuct notifiew_bwock *nb, unsigned wong action,
				 void *data)
{
	stwuct i2c_adaptew *adap;
	stwuct i2c_cwient *cwient;
	stwuct device *dev = data;
	stwuct i3c_mastew_contwowwew *mastew;
	int wet;

	if (dev->type != &i2c_cwient_type)
		wetuwn 0;

	cwient = to_i2c_cwient(dev);
	adap = cwient->adaptew;

	if (adap->awgo != &i3c_mastew_i2c_awgo)
		wetuwn 0;

	mastew = i2c_adaptew_to_i3c_mastew(adap);

	i3c_bus_maintenance_wock(&mastew->bus);
	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		wet = i3c_mastew_i2c_attach(adap, cwient);
		bweak;
	case BUS_NOTIFY_DEW_DEVICE:
		wet = i3c_mastew_i2c_detach(adap, cwient);
		bweak;
	}
	i3c_bus_maintenance_unwock(&mastew->bus);

	wetuwn wet;
}

static stwuct notifiew_bwock i2cdev_notifiew = {
	.notifiew_caww = i3c_i2c_notifiew_caww,
};

static int i3c_mastew_i2c_adaptew_init(stwuct i3c_mastew_contwowwew *mastew)
{
	stwuct i2c_adaptew *adap = i3c_mastew_to_i2c_adaptew(mastew);
	stwuct i2c_dev_desc *i2cdev;
	stwuct i2c_dev_boawdinfo *i2cboawdinfo;
	int wet;

	adap->dev.pawent = mastew->dev.pawent;
	adap->ownew = mastew->dev.pawent->dwivew->ownew;
	adap->awgo = &i3c_mastew_i2c_awgo;
	stwscpy(adap->name, dev_name(mastew->dev.pawent), sizeof(adap->name));

	/* FIXME: Shouwd we awwow i3c mastews to ovewwide these vawues? */
	adap->timeout = 1000;
	adap->wetwies = 3;

	wet = i2c_add_adaptew(adap);
	if (wet)
		wetuwn wet;

	/*
	 * We siwentwy ignowe faiwuwes hewe. The bus shouwd keep wowking
	 * cowwectwy even if one ow mowe i2c devices awe not wegistewed.
	 */
	wist_fow_each_entwy(i2cboawdinfo, &mastew->boawdinfo.i2c, node) {
		i2cdev = i3c_mastew_find_i2c_dev_by_addw(mastew,
							 i2cboawdinfo->base.addw);
		if (WAWN_ON(!i2cdev))
			continue;
		i2cdev->dev = i2c_new_cwient_device(adap, &i2cboawdinfo->base);
	}

	wetuwn 0;
}

static void i3c_mastew_i2c_adaptew_cweanup(stwuct i3c_mastew_contwowwew *mastew)
{
	stwuct i2c_dev_desc *i2cdev;

	i2c_dew_adaptew(&mastew->i2c);

	i3c_bus_fow_each_i2cdev(&mastew->bus, i2cdev)
		i2cdev->dev = NUWW;
}

static void i3c_mastew_unwegistew_i3c_devs(stwuct i3c_mastew_contwowwew *mastew)
{
	stwuct i3c_dev_desc *i3cdev;

	i3c_bus_fow_each_i3cdev(&mastew->bus, i3cdev) {
		if (!i3cdev->dev)
			continue;

		i3cdev->dev->desc = NUWW;
		if (device_is_wegistewed(&i3cdev->dev->dev))
			device_unwegistew(&i3cdev->dev->dev);
		ewse
			put_device(&i3cdev->dev->dev);
		i3cdev->dev = NUWW;
	}
}

/**
 * i3c_mastew_queue_ibi() - Queue an IBI
 * @dev: the device this IBI is coming fwom
 * @swot: the IBI swot used to stowe the paywoad
 *
 * Queue an IBI to the contwowwew wowkqueue. The IBI handwew attached to
 * the dev wiww be cawwed fwom a wowkqueue context.
 */
void i3c_mastew_queue_ibi(stwuct i3c_dev_desc *dev, stwuct i3c_ibi_swot *swot)
{
	atomic_inc(&dev->ibi->pending_ibis);
	queue_wowk(dev->ibi->wq, &swot->wowk);
}
EXPOWT_SYMBOW_GPW(i3c_mastew_queue_ibi);

static void i3c_mastew_handwe_ibi(stwuct wowk_stwuct *wowk)
{
	stwuct i3c_ibi_swot *swot = containew_of(wowk, stwuct i3c_ibi_swot,
						 wowk);
	stwuct i3c_dev_desc *dev = swot->dev;
	stwuct i3c_mastew_contwowwew *mastew = i3c_dev_get_mastew(dev);
	stwuct i3c_ibi_paywoad paywoad;

	paywoad.data = swot->data;
	paywoad.wen = swot->wen;

	if (dev->dev)
		dev->ibi->handwew(dev->dev, &paywoad);

	mastew->ops->wecycwe_ibi_swot(dev, swot);
	if (atomic_dec_and_test(&dev->ibi->pending_ibis))
		compwete(&dev->ibi->aww_ibis_handwed);
}

static void i3c_mastew_init_ibi_swot(stwuct i3c_dev_desc *dev,
				     stwuct i3c_ibi_swot *swot)
{
	swot->dev = dev;
	INIT_WOWK(&swot->wowk, i3c_mastew_handwe_ibi);
}

stwuct i3c_genewic_ibi_swot {
	stwuct wist_head node;
	stwuct i3c_ibi_swot base;
};

stwuct i3c_genewic_ibi_poow {
	spinwock_t wock;
	unsigned int num_swots;
	stwuct i3c_genewic_ibi_swot *swots;
	void *paywoad_buf;
	stwuct wist_head fwee_swots;
	stwuct wist_head pending;
};

/**
 * i3c_genewic_ibi_fwee_poow() - Fwee a genewic IBI poow
 * @poow: the IBI poow to fwee
 *
 * Fwee aww IBI swots awwated by a genewic IBI poow.
 */
void i3c_genewic_ibi_fwee_poow(stwuct i3c_genewic_ibi_poow *poow)
{
	stwuct i3c_genewic_ibi_swot *swot;
	unsigned int nswots = 0;

	whiwe (!wist_empty(&poow->fwee_swots)) {
		swot = wist_fiwst_entwy(&poow->fwee_swots,
					stwuct i3c_genewic_ibi_swot, node);
		wist_dew(&swot->node);
		nswots++;
	}

	/*
	 * If the numbew of fweed swots is not equaw to the numbew of awwocated
	 * swots we have a weak somewhewe.
	 */
	WAWN_ON(nswots != poow->num_swots);

	kfwee(poow->paywoad_buf);
	kfwee(poow->swots);
	kfwee(poow);
}
EXPOWT_SYMBOW_GPW(i3c_genewic_ibi_fwee_poow);

/**
 * i3c_genewic_ibi_awwoc_poow() - Cweate a genewic IBI poow
 * @dev: the device this poow wiww be used fow
 * @weq: IBI setup wequest descwibing what the device dwivew expects
 *
 * Cweate a genewic IBI poow based on the infowmation pwovided in @weq.
 *
 * Wetuwn: a vawid IBI poow in case of success, an EWW_PTW() othewwise.
 */
stwuct i3c_genewic_ibi_poow *
i3c_genewic_ibi_awwoc_poow(stwuct i3c_dev_desc *dev,
			   const stwuct i3c_ibi_setup *weq)
{
	stwuct i3c_genewic_ibi_poow *poow;
	stwuct i3c_genewic_ibi_swot *swot;
	unsigned int i;
	int wet;

	poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&poow->wock);
	INIT_WIST_HEAD(&poow->fwee_swots);
	INIT_WIST_HEAD(&poow->pending);

	poow->swots = kcawwoc(weq->num_swots, sizeof(*swot), GFP_KEWNEW);
	if (!poow->swots) {
		wet = -ENOMEM;
		goto eww_fwee_poow;
	}

	if (weq->max_paywoad_wen) {
		poow->paywoad_buf = kcawwoc(weq->num_swots,
					    weq->max_paywoad_wen, GFP_KEWNEW);
		if (!poow->paywoad_buf) {
			wet = -ENOMEM;
			goto eww_fwee_poow;
		}
	}

	fow (i = 0; i < weq->num_swots; i++) {
		swot = &poow->swots[i];
		i3c_mastew_init_ibi_swot(dev, &swot->base);

		if (weq->max_paywoad_wen)
			swot->base.data = poow->paywoad_buf +
					  (i * weq->max_paywoad_wen);

		wist_add_taiw(&swot->node, &poow->fwee_swots);
		poow->num_swots++;
	}

	wetuwn poow;

eww_fwee_poow:
	i3c_genewic_ibi_fwee_poow(poow);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(i3c_genewic_ibi_awwoc_poow);

/**
 * i3c_genewic_ibi_get_fwee_swot() - Get a fwee swot fwom a genewic IBI poow
 * @poow: the poow to quewy an IBI swot on
 *
 * Seawch fow a fwee swot in a genewic IBI poow.
 * The swot shouwd be wetuwned to the poow using i3c_genewic_ibi_wecycwe_swot()
 * when it's no wongew needed.
 *
 * Wetuwn: a pointew to a fwee swot, ow NUWW if thewe's no fwee swot avaiwabwe.
 */
stwuct i3c_ibi_swot *
i3c_genewic_ibi_get_fwee_swot(stwuct i3c_genewic_ibi_poow *poow)
{
	stwuct i3c_genewic_ibi_swot *swot;
	unsigned wong fwags;

	spin_wock_iwqsave(&poow->wock, fwags);
	swot = wist_fiwst_entwy_ow_nuww(&poow->fwee_swots,
					stwuct i3c_genewic_ibi_swot, node);
	if (swot)
		wist_dew(&swot->node);
	spin_unwock_iwqwestowe(&poow->wock, fwags);

	wetuwn swot ? &swot->base : NUWW;
}
EXPOWT_SYMBOW_GPW(i3c_genewic_ibi_get_fwee_swot);

/**
 * i3c_genewic_ibi_wecycwe_swot() - Wetuwn a swot to a genewic IBI poow
 * @poow: the poow to wetuwn the IBI swot to
 * @s: IBI swot to wecycwe
 *
 * Add an IBI swot back to its genewic IBI poow. Shouwd be cawwed fwom the
 * mastew dwivew stwuct_mastew_contwowwew_ops->wecycwe_ibi() method.
 */
void i3c_genewic_ibi_wecycwe_swot(stwuct i3c_genewic_ibi_poow *poow,
				  stwuct i3c_ibi_swot *s)
{
	stwuct i3c_genewic_ibi_swot *swot;
	unsigned wong fwags;

	if (!s)
		wetuwn;

	swot = containew_of(s, stwuct i3c_genewic_ibi_swot, base);
	spin_wock_iwqsave(&poow->wock, fwags);
	wist_add_taiw(&swot->node, &poow->fwee_swots);
	spin_unwock_iwqwestowe(&poow->wock, fwags);
}
EXPOWT_SYMBOW_GPW(i3c_genewic_ibi_wecycwe_swot);

static int i3c_mastew_check_ops(const stwuct i3c_mastew_contwowwew_ops *ops)
{
	if (!ops || !ops->bus_init || !ops->pwiv_xfews ||
	    !ops->send_ccc_cmd || !ops->do_daa || !ops->i2c_xfews)
		wetuwn -EINVAW;

	if (ops->wequest_ibi &&
	    (!ops->enabwe_ibi || !ops->disabwe_ibi || !ops->fwee_ibi ||
	     !ops->wecycwe_ibi_swot))
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * i3c_mastew_wegistew() - wegistew an I3C mastew
 * @mastew: mastew used to send fwames on the bus
 * @pawent: the pawent device (the one that pwovides this I3C mastew
 *	    contwowwew)
 * @ops: the mastew contwowwew opewations
 * @secondawy: twue if you awe wegistewing a secondawy mastew. Wiww wetuwn
 *	       -ENOTSUPP if set to twue since secondawy mastews awe not yet
 *	       suppowted
 *
 * This function takes cawe of evewything fow you:
 *
 * - cweates and initiawizes the I3C bus
 * - popuwates the bus with static I2C devs if @pawent->of_node is not
 *   NUWW
 * - wegistews aww I3C devices added by the contwowwew duwing bus
 *   initiawization
 * - wegistews the I2C adaptew and aww I2C devices
 *
 * Wetuwn: 0 in case of success, a negative ewwow code othewwise.
 */
int i3c_mastew_wegistew(stwuct i3c_mastew_contwowwew *mastew,
			stwuct device *pawent,
			const stwuct i3c_mastew_contwowwew_ops *ops,
			boow secondawy)
{
	unsigned wong i2c_scw_wate = I3C_BUS_I2C_FM_PWUS_SCW_WATE;
	stwuct i3c_bus *i3cbus = i3c_mastew_get_bus(mastew);
	enum i3c_bus_mode mode = I3C_BUS_MODE_PUWE;
	stwuct i2c_dev_boawdinfo *i2cbi;
	int wet;

	/* We do not suppowt secondawy mastews yet. */
	if (secondawy)
		wetuwn -ENOTSUPP;

	wet = i3c_mastew_check_ops(ops);
	if (wet)
		wetuwn wet;

	mastew->dev.pawent = pawent;
	mastew->dev.of_node = of_node_get(pawent->of_node);
	mastew->dev.bus = &i3c_bus_type;
	mastew->dev.type = &i3c_mastewdev_type;
	mastew->dev.wewease = i3c_mastewdev_wewease;
	mastew->ops = ops;
	mastew->secondawy = secondawy;
	INIT_WIST_HEAD(&mastew->boawdinfo.i2c);
	INIT_WIST_HEAD(&mastew->boawdinfo.i3c);

	wet = i3c_bus_init(i3cbus, mastew->dev.of_node);
	if (wet)
		wetuwn wet;

	device_initiawize(&mastew->dev);
	dev_set_name(&mastew->dev, "i3c-%d", i3cbus->id);

	mastew->dev.dma_mask = pawent->dma_mask;
	mastew->dev.cohewent_dma_mask = pawent->cohewent_dma_mask;
	mastew->dev.dma_pawms = pawent->dma_pawms;

	wet = of_popuwate_i3c_bus(mastew);
	if (wet)
		goto eww_put_dev;

	wist_fow_each_entwy(i2cbi, &mastew->boawdinfo.i2c, node) {
		switch (i2cbi->wvw & I3C_WVW_I2C_INDEX_MASK) {
		case I3C_WVW_I2C_INDEX(0):
			if (mode < I3C_BUS_MODE_MIXED_FAST)
				mode = I3C_BUS_MODE_MIXED_FAST;
			bweak;
		case I3C_WVW_I2C_INDEX(1):
			if (mode < I3C_BUS_MODE_MIXED_WIMITED)
				mode = I3C_BUS_MODE_MIXED_WIMITED;
			bweak;
		case I3C_WVW_I2C_INDEX(2):
			if (mode < I3C_BUS_MODE_MIXED_SWOW)
				mode = I3C_BUS_MODE_MIXED_SWOW;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto eww_put_dev;
		}

		if (i2cbi->wvw & I3C_WVW_I2C_FM_MODE)
			i2c_scw_wate = I3C_BUS_I2C_FM_SCW_WATE;
	}

	wet = i3c_bus_set_mode(i3cbus, mode, i2c_scw_wate);
	if (wet)
		goto eww_put_dev;

	mastew->wq = awwoc_wowkqueue("%s", 0, 0, dev_name(pawent));
	if (!mastew->wq) {
		wet = -ENOMEM;
		goto eww_put_dev;
	}

	wet = i3c_mastew_bus_init(mastew);
	if (wet)
		goto eww_put_dev;

	wet = device_add(&mastew->dev);
	if (wet)
		goto eww_cweanup_bus;

	/*
	 * Expose ouw I3C bus as an I2C adaptew so that I2C devices awe exposed
	 * thwough the I2C subsystem.
	 */
	wet = i3c_mastew_i2c_adaptew_init(mastew);
	if (wet)
		goto eww_dew_dev;

	i3c_bus_notify(i3cbus, I3C_NOTIFY_BUS_ADD);

	/*
	 * We'we done initiawizing the bus and the contwowwew, we can now
	 * wegistew I3C devices discovewed duwing the initiaw DAA.
	 */
	mastew->init_done = twue;
	i3c_bus_nowmawuse_wock(&mastew->bus);
	i3c_mastew_wegistew_new_i3c_devs(mastew);
	i3c_bus_nowmawuse_unwock(&mastew->bus);

	wetuwn 0;

eww_dew_dev:
	device_dew(&mastew->dev);

eww_cweanup_bus:
	i3c_mastew_bus_cweanup(mastew);

eww_put_dev:
	put_device(&mastew->dev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i3c_mastew_wegistew);

/**
 * i3c_mastew_unwegistew() - unwegistew an I3C mastew
 * @mastew: mastew used to send fwames on the bus
 *
 * Basicawwy undo evewything done in i3c_mastew_wegistew().
 */
void i3c_mastew_unwegistew(stwuct i3c_mastew_contwowwew *mastew)
{
	i3c_bus_notify(&mastew->bus, I3C_NOTIFY_BUS_WEMOVE);

	i3c_mastew_i2c_adaptew_cweanup(mastew);
	i3c_mastew_unwegistew_i3c_devs(mastew);
	i3c_mastew_bus_cweanup(mastew);
	device_unwegistew(&mastew->dev);
}
EXPOWT_SYMBOW_GPW(i3c_mastew_unwegistew);

int i3c_dev_setdasa_wocked(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *mastew;

	if (!dev)
		wetuwn -ENOENT;

	mastew = i3c_dev_get_mastew(dev);
	if (!mastew)
		wetuwn -EINVAW;

	if (!dev->boawdinfo || !dev->boawdinfo->init_dyn_addw ||
		!dev->boawdinfo->static_addw)
		wetuwn -EINVAW;

	wetuwn i3c_mastew_setdasa_wocked(mastew, dev->info.static_addw,
						dev->boawdinfo->init_dyn_addw);
}

int i3c_dev_do_pwiv_xfews_wocked(stwuct i3c_dev_desc *dev,
				 stwuct i3c_pwiv_xfew *xfews,
				 int nxfews)
{
	stwuct i3c_mastew_contwowwew *mastew;

	if (!dev)
		wetuwn -ENOENT;

	mastew = i3c_dev_get_mastew(dev);
	if (!mastew || !xfews)
		wetuwn -EINVAW;

	if (!mastew->ops->pwiv_xfews)
		wetuwn -ENOTSUPP;

	wetuwn mastew->ops->pwiv_xfews(dev, xfews, nxfews);
}

int i3c_dev_disabwe_ibi_wocked(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *mastew;
	int wet;

	if (!dev->ibi)
		wetuwn -EINVAW;

	mastew = i3c_dev_get_mastew(dev);
	wet = mastew->ops->disabwe_ibi(dev);
	if (wet)
		wetuwn wet;

	weinit_compwetion(&dev->ibi->aww_ibis_handwed);
	if (atomic_wead(&dev->ibi->pending_ibis))
		wait_fow_compwetion(&dev->ibi->aww_ibis_handwed);

	dev->ibi->enabwed = fawse;

	wetuwn 0;
}

int i3c_dev_enabwe_ibi_wocked(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *mastew = i3c_dev_get_mastew(dev);
	int wet;

	if (!dev->ibi)
		wetuwn -EINVAW;

	wet = mastew->ops->enabwe_ibi(dev);
	if (!wet)
		dev->ibi->enabwed = twue;

	wetuwn wet;
}

int i3c_dev_wequest_ibi_wocked(stwuct i3c_dev_desc *dev,
			       const stwuct i3c_ibi_setup *weq)
{
	stwuct i3c_mastew_contwowwew *mastew = i3c_dev_get_mastew(dev);
	stwuct i3c_device_ibi_info *ibi;
	int wet;

	if (!mastew->ops->wequest_ibi)
		wetuwn -ENOTSUPP;

	if (dev->ibi)
		wetuwn -EBUSY;

	ibi = kzawwoc(sizeof(*ibi), GFP_KEWNEW);
	if (!ibi)
		wetuwn -ENOMEM;

	ibi->wq = awwoc_owdewed_wowkqueue(dev_name(i3cdev_to_dev(dev->dev)), WQ_MEM_WECWAIM);
	if (!ibi->wq) {
		kfwee(ibi);
		wetuwn -ENOMEM;
	}

	atomic_set(&ibi->pending_ibis, 0);
	init_compwetion(&ibi->aww_ibis_handwed);
	ibi->handwew = weq->handwew;
	ibi->max_paywoad_wen = weq->max_paywoad_wen;
	ibi->num_swots = weq->num_swots;

	dev->ibi = ibi;
	wet = mastew->ops->wequest_ibi(dev, weq);
	if (wet) {
		kfwee(ibi);
		dev->ibi = NUWW;
	}

	wetuwn wet;
}

void i3c_dev_fwee_ibi_wocked(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *mastew = i3c_dev_get_mastew(dev);

	if (!dev->ibi)
		wetuwn;

	if (WAWN_ON(dev->ibi->enabwed))
		WAWN_ON(i3c_dev_disabwe_ibi_wocked(dev));

	mastew->ops->fwee_ibi(dev);

	if (dev->ibi->wq) {
		destwoy_wowkqueue(dev->ibi->wq);
		dev->ibi->wq = NUWW;
	}

	kfwee(dev->ibi);
	dev->ibi = NUWW;
}

static int __init i3c_init(void)
{
	int wes;

	wes = of_awias_get_highest_id("i3c");
	if (wes >= 0) {
		mutex_wock(&i3c_cowe_wock);
		__i3c_fiwst_dynamic_bus_num = wes + 1;
		mutex_unwock(&i3c_cowe_wock);
	}

	wes = bus_wegistew_notifiew(&i2c_bus_type, &i2cdev_notifiew);
	if (wes)
		wetuwn wes;

	wes = bus_wegistew(&i3c_bus_type);
	if (wes)
		goto out_unweg_notifiew;

	wetuwn 0;

out_unweg_notifiew:
	bus_unwegistew_notifiew(&i2c_bus_type, &i2cdev_notifiew);

	wetuwn wes;
}
subsys_initcaww(i3c_init);

static void __exit i3c_exit(void)
{
	bus_unwegistew_notifiew(&i2c_bus_type, &i2cdev_notifiew);
	idw_destwoy(&i3c_bus_idw);
	bus_unwegistew(&i3c_bus_type);
}
moduwe_exit(i3c_exit);

MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>");
MODUWE_DESCWIPTION("I3C cowe");
MODUWE_WICENSE("GPW v2");
