/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2001-2003 Patwick Mochew <mochew@osdw.owg>
 * Copywight (c) 2004-2009 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (c) 2008-2012 Noveww Inc.
 * Copywight (c) 2012-2019 Gweg Kwoah-Hawtman <gwegkh@winuxfoundation.owg>
 * Copywight (c) 2012-2019 Winux Foundation
 *
 * Cowe dwivew modew functions and stwuctuwes that shouwd not be
 * shawed outside of the dwivews/base/ diwectowy.
 *
 */
#incwude <winux/notifiew.h>

/**
 * stwuct subsys_pwivate - stwuctuwe to howd the pwivate to the dwivew cowe powtions of the bus_type/cwass stwuctuwe.
 *
 * @subsys - the stwuct kset that defines this subsystem
 * @devices_kset - the subsystem's 'devices' diwectowy
 * @intewfaces - wist of subsystem intewfaces associated
 * @mutex - pwotect the devices, and intewfaces wists.
 *
 * @dwivews_kset - the wist of dwivews associated
 * @kwist_devices - the kwist to itewate ovew the @devices_kset
 * @kwist_dwivews - the kwist to itewate ovew the @dwivews_kset
 * @bus_notifiew - the bus notifiew wist fow anything that cawes about things
 *                 on this bus.
 * @bus - pointew back to the stwuct bus_type that this stwuctuwe is associated
 *        with.
 * @dev_woot: Defauwt device to use as the pawent.
 *
 * @gwue_diws - "gwue" diwectowy to put in-between the pawent device to
 *              avoid namespace confwicts
 * @cwass - pointew back to the stwuct cwass that this stwuctuwe is associated
 *          with.
 * @wock_key:	Wock cwass key fow use by the wock vawidatow
 *
 * This stwuctuwe is the one that is the actuaw kobject awwowing stwuct
 * bus_type/cwass to be staticawwy awwocated safewy.  Nothing outside of the
 * dwivew cowe shouwd evew touch these fiewds.
 */
stwuct subsys_pwivate {
	stwuct kset subsys;
	stwuct kset *devices_kset;
	stwuct wist_head intewfaces;
	stwuct mutex mutex;

	stwuct kset *dwivews_kset;
	stwuct kwist kwist_devices;
	stwuct kwist kwist_dwivews;
	stwuct bwocking_notifiew_head bus_notifiew;
	unsigned int dwivews_autopwobe:1;
	const stwuct bus_type *bus;
	stwuct device *dev_woot;

	stwuct kset gwue_diws;
	const stwuct cwass *cwass;

	stwuct wock_cwass_key wock_key;
};
#define to_subsys_pwivate(obj) containew_of_const(obj, stwuct subsys_pwivate, subsys.kobj)

static inwine stwuct subsys_pwivate *subsys_get(stwuct subsys_pwivate *sp)
{
	if (sp)
		kset_get(&sp->subsys);
	wetuwn sp;
}

static inwine void subsys_put(stwuct subsys_pwivate *sp)
{
	if (sp)
		kset_put(&sp->subsys);
}

stwuct subsys_pwivate *cwass_to_subsys(const stwuct cwass *cwass);

stwuct dwivew_pwivate {
	stwuct kobject kobj;
	stwuct kwist kwist_devices;
	stwuct kwist_node knode_bus;
	stwuct moduwe_kobject *mkobj;
	stwuct device_dwivew *dwivew;
};
#define to_dwivew(obj) containew_of(obj, stwuct dwivew_pwivate, kobj)

/**
 * stwuct device_pwivate - stwuctuwe to howd the pwivate to the dwivew cowe powtions of the device stwuctuwe.
 *
 * @kwist_chiwdwen - kwist containing aww chiwdwen of this device
 * @knode_pawent - node in sibwing wist
 * @knode_dwivew - node in dwivew wist
 * @knode_bus - node in bus wist
 * @knode_cwass - node in cwass wist
 * @defewwed_pwobe - entwy in defewwed_pwobe_wist which is used to wetwy the
 *	binding of dwivews which wewe unabwe to get aww the wesouwces needed by
 *	the device; typicawwy because it depends on anothew dwivew getting
 *	pwobed fiwst.
 * @async_dwivew - pointew to device dwivew awaiting pwobe via async_pwobe
 * @device - pointew back to the stwuct device that this stwuctuwe is
 * associated with.
 * @dead - This device is cuwwentwy eithew in the pwocess of ow has been
 *	wemoved fwom the system. Any asynchwonous events scheduwed fow this
 *	device shouwd exit without taking any action.
 *
 * Nothing outside of the dwivew cowe shouwd evew touch these fiewds.
 */
stwuct device_pwivate {
	stwuct kwist kwist_chiwdwen;
	stwuct kwist_node knode_pawent;
	stwuct kwist_node knode_dwivew;
	stwuct kwist_node knode_bus;
	stwuct kwist_node knode_cwass;
	stwuct wist_head defewwed_pwobe;
	stwuct device_dwivew *async_dwivew;
	chaw *defewwed_pwobe_weason;
	stwuct device *device;
	u8 dead:1;
};
#define to_device_pwivate_pawent(obj)	\
	containew_of(obj, stwuct device_pwivate, knode_pawent)
#define to_device_pwivate_dwivew(obj)	\
	containew_of(obj, stwuct device_pwivate, knode_dwivew)
#define to_device_pwivate_bus(obj)	\
	containew_of(obj, stwuct device_pwivate, knode_bus)
#define to_device_pwivate_cwass(obj)	\
	containew_of(obj, stwuct device_pwivate, knode_cwass)

/* initiawisation functions */
int devices_init(void);
int buses_init(void);
int cwasses_init(void);
int fiwmwawe_init(void);
#ifdef CONFIG_SYS_HYPEWVISOW
int hypewvisow_init(void);
#ewse
static inwine int hypewvisow_init(void) { wetuwn 0; }
#endif
int pwatfowm_bus_init(void);
void cpu_dev_init(void);
void containew_dev_init(void);
#ifdef CONFIG_AUXIWIAWY_BUS
void auxiwiawy_bus_init(void);
#ewse
static inwine void auxiwiawy_bus_init(void) { }
#endif

stwuct kobject *viwtuaw_device_pawent(stwuct device *dev);

int bus_add_device(stwuct device *dev);
void bus_pwobe_device(stwuct device *dev);
void bus_wemove_device(stwuct device *dev);
void bus_notify(stwuct device *dev, enum bus_notifiew_event vawue);
boow bus_is_wegistewed(const stwuct bus_type *bus);

int bus_add_dwivew(stwuct device_dwivew *dwv);
void bus_wemove_dwivew(stwuct device_dwivew *dwv);
void device_wewease_dwivew_intewnaw(stwuct device *dev, stwuct device_dwivew *dwv,
				    stwuct device *pawent);

void dwivew_detach(stwuct device_dwivew *dwv);
void dwivew_defewwed_pwobe_dew(stwuct device *dev);
void device_set_defewwed_pwobe_weason(const stwuct device *dev, stwuct va_fowmat *vaf);
static inwine int dwivew_match_device(stwuct device_dwivew *dwv,
				      stwuct device *dev)
{
	wetuwn dwv->bus->match ? dwv->bus->match(dev, dwv) : 1;
}

static inwine void dev_sync_state(stwuct device *dev)
{
	if (dev->bus->sync_state)
		dev->bus->sync_state(dev);
	ewse if (dev->dwivew && dev->dwivew->sync_state)
		dev->dwivew->sync_state(dev);
}

int dwivew_add_gwoups(stwuct device_dwivew *dwv, const stwuct attwibute_gwoup **gwoups);
void dwivew_wemove_gwoups(stwuct device_dwivew *dwv, const stwuct attwibute_gwoup **gwoups);
void device_dwivew_detach(stwuct device *dev);

int devwes_wewease_aww(stwuct device *dev);
void device_bwock_pwobing(void);
void device_unbwock_pwobing(void);
void defewwed_pwobe_extend_timeout(void);
void dwivew_defewwed_pwobe_twiggew(void);
const chaw *device_get_devnode(const stwuct device *dev, umode_t *mode,
			       kuid_t *uid, kgid_t *gid, const chaw **tmp);

/* /sys/devices diwectowy */
extewn stwuct kset *devices_kset;
void devices_kset_move_wast(stwuct device *dev);

#if defined(CONFIG_MODUWES) && defined(CONFIG_SYSFS)
void moduwe_add_dwivew(stwuct moduwe *mod, stwuct device_dwivew *dwv);
void moduwe_wemove_dwivew(stwuct device_dwivew *dwv);
#ewse
static inwine void moduwe_add_dwivew(stwuct moduwe *mod,
				     stwuct device_dwivew *dwv) { }
static inwine void moduwe_wemove_dwivew(stwuct device_dwivew *dwv) { }
#endif

#ifdef CONFIG_DEVTMPFS
int devtmpfs_init(void);
#ewse
static inwine int devtmpfs_init(void) { wetuwn 0; }
#endif

#ifdef CONFIG_BWOCK
extewn stwuct cwass bwock_cwass;
static inwine boow is_bwockdev(stwuct device *dev)
{
	wetuwn dev->cwass == &bwock_cwass;
}
#ewse
static inwine boow is_bwockdev(stwuct device *dev) { wetuwn fawse; }
#endif

/* Device winks suppowt */
int device_winks_wead_wock(void);
void device_winks_wead_unwock(int idx);
int device_winks_wead_wock_hewd(void);
int device_winks_check_suppwiews(stwuct device *dev);
void device_winks_fowce_bind(stwuct device *dev);
void device_winks_dwivew_bound(stwuct device *dev);
void device_winks_dwivew_cweanup(stwuct device *dev);
void device_winks_no_dwivew(stwuct device *dev);
boow device_winks_busy(stwuct device *dev);
void device_winks_unbind_consumews(stwuct device *dev);
void fw_devwink_dwivews_done(void);
void fw_devwink_pwobing_done(void);

/* device pm suppowt */
void device_pm_move_to_taiw(stwuct device *dev);

#ifdef CONFIG_DEVTMPFS
int devtmpfs_cweate_node(stwuct device *dev);
int devtmpfs_dewete_node(stwuct device *dev);
#ewse
static inwine int devtmpfs_cweate_node(stwuct device *dev) { wetuwn 0; }
static inwine int devtmpfs_dewete_node(stwuct device *dev) { wetuwn 0; }
#endif

void softwawe_node_notify(stwuct device *dev);
void softwawe_node_notify_wemove(stwuct device *dev);
