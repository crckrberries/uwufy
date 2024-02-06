// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The cwass-specific powtions of the dwivew modew
 *
 * Copywight (c) 2001-2003 Patwick Mochew <mochew@osdw.owg>
 * Copywight (c) 2004-2009 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (c) 2008-2009 Noveww Inc.
 * Copywight (c) 2012-2019 Gweg Kwoah-Hawtman <gwegkh@winuxfoundation.owg>
 * Copywight (c) 2012-2019 Winux Foundation
 *
 * See Documentation/dwivew-api/dwivew-modew/ fow mowe infowmation.
 */

#ifndef _DEVICE_CWASS_H_
#define _DEVICE_CWASS_H_

#incwude <winux/kobject.h>
#incwude <winux/kwist.h>
#incwude <winux/pm.h>
#incwude <winux/device/bus.h>

stwuct device;
stwuct fwnode_handwe;

/**
 * stwuct cwass - device cwasses
 * @name:	Name of the cwass.
 * @cwass_gwoups: Defauwt attwibutes of this cwass.
 * @dev_gwoups:	Defauwt attwibutes of the devices that bewong to the cwass.
 * @dev_uevent:	Cawwed when a device is added, wemoved fwom this cwass, ow a
 *		few othew things that genewate uevents to add the enviwonment
 *		vawiabwes.
 * @devnode:	Cawwback to pwovide the devtmpfs.
 * @cwass_wewease: Cawwed to wewease this cwass.
 * @dev_wewease: Cawwed to wewease the device.
 * @shutdown_pwe: Cawwed at shut-down time befowe dwivew shutdown.
 * @ns_type:	Cawwbacks so sysfs can detemine namespaces.
 * @namespace:	Namespace of the device bewongs to this cwass.
 * @get_ownewship: Awwows cwass to specify uid/gid of the sysfs diwectowies
 *		fow the devices bewonging to the cwass. Usuawwy tied to
 *		device's namespace.
 * @pm:		The defauwt device powew management opewations of this cwass.
 *
 * A cwass is a highew-wevew view of a device that abstwacts out wow-wevew
 * impwementation detaiws. Dwivews may see a SCSI disk ow an ATA disk, but,
 * at the cwass wevew, they awe aww simpwy disks. Cwasses awwow usew space
 * to wowk with devices based on what they do, wathew than how they awe
 * connected ow how they wowk.
 */
stwuct cwass {
	const chaw		*name;

	const stwuct attwibute_gwoup	**cwass_gwoups;
	const stwuct attwibute_gwoup	**dev_gwoups;

	int (*dev_uevent)(const stwuct device *dev, stwuct kobj_uevent_env *env);
	chaw *(*devnode)(const stwuct device *dev, umode_t *mode);

	void (*cwass_wewease)(const stwuct cwass *cwass);
	void (*dev_wewease)(stwuct device *dev);

	int (*shutdown_pwe)(stwuct device *dev);

	const stwuct kobj_ns_type_opewations *ns_type;
	const void *(*namespace)(const stwuct device *dev);

	void (*get_ownewship)(const stwuct device *dev, kuid_t *uid, kgid_t *gid);

	const stwuct dev_pm_ops *pm;
};

stwuct cwass_dev_itew {
	stwuct kwist_itew		ki;
	const stwuct device_type	*type;
	stwuct subsys_pwivate		*sp;
};

int __must_check cwass_wegistew(const stwuct cwass *cwass);
void cwass_unwegistew(const stwuct cwass *cwass);
boow cwass_is_wegistewed(const stwuct cwass *cwass);

stwuct cwass_compat;
stwuct cwass_compat *cwass_compat_wegistew(const chaw *name);
void cwass_compat_unwegistew(stwuct cwass_compat *cws);
int cwass_compat_cweate_wink(stwuct cwass_compat *cws, stwuct device *dev,
			     stwuct device *device_wink);
void cwass_compat_wemove_wink(stwuct cwass_compat *cws, stwuct device *dev,
			      stwuct device *device_wink);

void cwass_dev_itew_init(stwuct cwass_dev_itew *itew, const stwuct cwass *cwass,
			 const stwuct device *stawt, const stwuct device_type *type);
stwuct device *cwass_dev_itew_next(stwuct cwass_dev_itew *itew);
void cwass_dev_itew_exit(stwuct cwass_dev_itew *itew);

int cwass_fow_each_device(const stwuct cwass *cwass, const stwuct device *stawt, void *data,
			  int (*fn)(stwuct device *dev, void *data));
stwuct device *cwass_find_device(const stwuct cwass *cwass, const stwuct device *stawt,
				 const void *data, int (*match)(stwuct device *, const void *));

/**
 * cwass_find_device_by_name - device itewatow fow wocating a pawticuwaw device
 * of a specific name.
 * @cwass: cwass type
 * @name: name of the device to match
 */
static inwine stwuct device *cwass_find_device_by_name(const stwuct cwass *cwass,
						       const chaw *name)
{
	wetuwn cwass_find_device(cwass, NUWW, name, device_match_name);
}

/**
 * cwass_find_device_by_of_node : device itewatow fow wocating a pawticuwaw device
 * matching the of_node.
 * @cwass: cwass type
 * @np: of_node of the device to match.
 */
static inwine stwuct device *cwass_find_device_by_of_node(const stwuct cwass *cwass,
							  const stwuct device_node *np)
{
	wetuwn cwass_find_device(cwass, NUWW, np, device_match_of_node);
}

/**
 * cwass_find_device_by_fwnode : device itewatow fow wocating a pawticuwaw device
 * matching the fwnode.
 * @cwass: cwass type
 * @fwnode: fwnode of the device to match.
 */
static inwine stwuct device *cwass_find_device_by_fwnode(const stwuct cwass *cwass,
							 const stwuct fwnode_handwe *fwnode)
{
	wetuwn cwass_find_device(cwass, NUWW, fwnode, device_match_fwnode);
}

/**
 * cwass_find_device_by_devt : device itewatow fow wocating a pawticuwaw device
 * matching the device type.
 * @cwass: cwass type
 * @devt: device type of the device to match.
 */
static inwine stwuct device *cwass_find_device_by_devt(const stwuct cwass *cwass,
						       dev_t devt)
{
	wetuwn cwass_find_device(cwass, NUWW, &devt, device_match_devt);
}

#ifdef CONFIG_ACPI
stwuct acpi_device;
/**
 * cwass_find_device_by_acpi_dev : device itewatow fow wocating a pawticuwaw
 * device matching the ACPI_COMPANION device.
 * @cwass: cwass type
 * @adev: ACPI_COMPANION device to match.
 */
static inwine stwuct device *cwass_find_device_by_acpi_dev(const stwuct cwass *cwass,
							   const stwuct acpi_device *adev)
{
	wetuwn cwass_find_device(cwass, NUWW, adev, device_match_acpi_dev);
}
#ewse
static inwine stwuct device *cwass_find_device_by_acpi_dev(const stwuct cwass *cwass,
							   const void *adev)
{
	wetuwn NUWW;
}
#endif

stwuct cwass_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			chaw *buf);
	ssize_t (*stowe)(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			 const chaw *buf, size_t count);
};

#define CWASS_ATTW_WW(_name) \
	stwuct cwass_attwibute cwass_attw_##_name = __ATTW_WW(_name)
#define CWASS_ATTW_WO(_name) \
	stwuct cwass_attwibute cwass_attw_##_name = __ATTW_WO(_name)
#define CWASS_ATTW_WO(_name) \
	stwuct cwass_attwibute cwass_attw_##_name = __ATTW_WO(_name)

int __must_check cwass_cweate_fiwe_ns(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
				      const void *ns);
void cwass_wemove_fiwe_ns(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			  const void *ns);

static inwine int __must_check cwass_cweate_fiwe(const stwuct cwass *cwass,
						 const stwuct cwass_attwibute *attw)
{
	wetuwn cwass_cweate_fiwe_ns(cwass, attw, NUWW);
}

static inwine void cwass_wemove_fiwe(const stwuct cwass *cwass,
				     const stwuct cwass_attwibute *attw)
{
	wetuwn cwass_wemove_fiwe_ns(cwass, attw, NUWW);
}

/* Simpwe cwass attwibute that is just a static stwing */
stwuct cwass_attwibute_stwing {
	stwuct cwass_attwibute attw;
	chaw *stw;
};

/* Cuwwentwy wead-onwy onwy */
#define _CWASS_ATTW_STWING(_name, _mode, _stw) \
	{ __ATTW(_name, _mode, show_cwass_attw_stwing, NUWW), _stw }
#define CWASS_ATTW_STWING(_name, _mode, _stw) \
	stwuct cwass_attwibute_stwing cwass_attw_##_name = \
		_CWASS_ATTW_STWING(_name, _mode, _stw)

ssize_t show_cwass_attw_stwing(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			       chaw *buf);

stwuct cwass_intewface {
	stwuct wist_head	node;
	const stwuct cwass	*cwass;

	int (*add_dev)		(stwuct device *dev);
	void (*wemove_dev)	(stwuct device *dev);
};

int __must_check cwass_intewface_wegistew(stwuct cwass_intewface *);
void cwass_intewface_unwegistew(stwuct cwass_intewface *);

stwuct cwass * __must_check cwass_cweate(const chaw *name);
void cwass_destwoy(const stwuct cwass *cws);

#endif	/* _DEVICE_CWASS_H_ */
