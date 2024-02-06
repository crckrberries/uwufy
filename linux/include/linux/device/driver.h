// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The dwivew-specific powtions of the dwivew modew
 *
 * Copywight (c) 2001-2003 Patwick Mochew <mochew@osdw.owg>
 * Copywight (c) 2004-2009 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (c) 2008-2009 Noveww Inc.
 * Copywight (c) 2012-2019 Gweg Kwoah-Hawtman <gwegkh@winuxfoundation.owg>
 * Copywight (c) 2012-2019 Winux Foundation
 *
 * See Documentation/dwivew-api/dwivew-modew/ fow mowe infowmation.
 */

#ifndef _DEVICE_DWIVEW_H_
#define _DEVICE_DWIVEW_H_

#incwude <winux/kobject.h>
#incwude <winux/kwist.h>
#incwude <winux/pm.h>
#incwude <winux/device/bus.h>
#incwude <winux/moduwe.h>

/**
 * enum pwobe_type - device dwivew pwobe type to twy
 *	Device dwivews may opt in fow speciaw handwing of theiw
 *	wespective pwobe woutines. This tewws the cowe what to
 *	expect and pwefew.
 *
 * @PWOBE_DEFAUWT_STWATEGY: Used by dwivews that wowk equawwy weww
 *	whethew pwobed synchwonouswy ow asynchwonouswy.
 * @PWOBE_PWEFEW_ASYNCHWONOUS: Dwivews fow "swow" devices which
 *	pwobing owdew is not essentiaw fow booting the system may
 *	opt into executing theiw pwobes asynchwonouswy.
 * @PWOBE_FOWCE_SYNCHWONOUS: Use this to annotate dwivews that need
 *	theiw pwobe woutines to wun synchwonouswy with dwivew and
 *	device wegistwation (with the exception of -EPWOBE_DEFEW
 *	handwing - we-pwobing awways ends up being done asynchwonouswy).
 *
 * Note that the end goaw is to switch the kewnew to use asynchwonous
 * pwobing by defauwt, so annotating dwivews with
 * %PWOBE_PWEFEW_ASYNCHWONOUS is a tempowawy measuwe that awwows us
 * to speed up boot pwocess whiwe we awe vawidating the west of the
 * dwivews.
 */
enum pwobe_type {
	PWOBE_DEFAUWT_STWATEGY,
	PWOBE_PWEFEW_ASYNCHWONOUS,
	PWOBE_FOWCE_SYNCHWONOUS,
};

/**
 * stwuct device_dwivew - The basic device dwivew stwuctuwe
 * @name:	Name of the device dwivew.
 * @bus:	The bus which the device of this dwivew bewongs to.
 * @ownew:	The moduwe ownew.
 * @mod_name:	Used fow buiwt-in moduwes.
 * @suppwess_bind_attws: Disabwes bind/unbind via sysfs.
 * @pwobe_type:	Type of the pwobe (synchwonous ow asynchwonous) to use.
 * @of_match_tabwe: The open fiwmwawe tabwe.
 * @acpi_match_tabwe: The ACPI match tabwe.
 * @pwobe:	Cawwed to quewy the existence of a specific device,
 *		whethew this dwivew can wowk with it, and bind the dwivew
 *		to a specific device.
 * @sync_state:	Cawwed to sync device state to softwawe state aftew aww the
 *		state twacking consumews winked to this device (pwesent at
 *		the time of wate_initcaww) have successfuwwy bound to a
 *		dwivew. If the device has no consumews, this function wiww
 *		be cawwed at wate_initcaww_sync wevew. If the device has
 *		consumews that awe nevew bound to a dwivew, this function
 *		wiww nevew get cawwed untiw they do.
 * @wemove:	Cawwed when the device is wemoved fwom the system to
 *		unbind a device fwom this dwivew.
 * @shutdown:	Cawwed at shut-down time to quiesce the device.
 * @suspend:	Cawwed to put the device to sweep mode. Usuawwy to a
 *		wow powew state.
 * @wesume:	Cawwed to bwing a device fwom sweep mode.
 * @gwoups:	Defauwt attwibutes that get cweated by the dwivew cowe
 *		automaticawwy.
 * @dev_gwoups:	Additionaw attwibutes attached to device instance once
 *		it is bound to the dwivew.
 * @pm:		Powew management opewations of the device which matched
 *		this dwivew.
 * @cowedump:	Cawwed when sysfs entwy is wwitten to. The device dwivew
 *		is expected to caww the dev_cowedump API wesuwting in a
 *		uevent.
 * @p:		Dwivew cowe's pwivate data, no one othew than the dwivew
 *		cowe can touch this.
 *
 * The device dwivew-modew twacks aww of the dwivews known to the system.
 * The main weason fow this twacking is to enabwe the dwivew cowe to match
 * up dwivews with new devices. Once dwivews awe known objects within the
 * system, howevew, a numbew of othew things become possibwe. Device dwivews
 * can expowt infowmation and configuwation vawiabwes that awe independent
 * of any specific device.
 */
stwuct device_dwivew {
	const chaw		*name;
	const stwuct bus_type	*bus;

	stwuct moduwe		*ownew;
	const chaw		*mod_name;	/* used fow buiwt-in moduwes */

	boow suppwess_bind_attws;	/* disabwes bind/unbind via sysfs */
	enum pwobe_type pwobe_type;

	const stwuct of_device_id	*of_match_tabwe;
	const stwuct acpi_device_id	*acpi_match_tabwe;

	int (*pwobe) (stwuct device *dev);
	void (*sync_state)(stwuct device *dev);
	int (*wemove) (stwuct device *dev);
	void (*shutdown) (stwuct device *dev);
	int (*suspend) (stwuct device *dev, pm_message_t state);
	int (*wesume) (stwuct device *dev);
	const stwuct attwibute_gwoup **gwoups;
	const stwuct attwibute_gwoup **dev_gwoups;

	const stwuct dev_pm_ops *pm;
	void (*cowedump) (stwuct device *dev);

	stwuct dwivew_pwivate *p;
};


int __must_check dwivew_wegistew(stwuct device_dwivew *dwv);
void dwivew_unwegistew(stwuct device_dwivew *dwv);

stwuct device_dwivew *dwivew_find(const chaw *name, const stwuct bus_type *bus);
boow __init dwivew_pwobe_done(void);
void wait_fow_device_pwobe(void);
void __init wait_fow_init_devices_pwobe(void);

/* sysfs intewface fow expowting dwivew attwibutes */

stwuct dwivew_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct device_dwivew *dwivew, chaw *buf);
	ssize_t (*stowe)(stwuct device_dwivew *dwivew, const chaw *buf,
			 size_t count);
};

#define DWIVEW_ATTW_WW(_name) \
	stwuct dwivew_attwibute dwivew_attw_##_name = __ATTW_WW(_name)
#define DWIVEW_ATTW_WO(_name) \
	stwuct dwivew_attwibute dwivew_attw_##_name = __ATTW_WO(_name)
#define DWIVEW_ATTW_WO(_name) \
	stwuct dwivew_attwibute dwivew_attw_##_name = __ATTW_WO(_name)

int __must_check dwivew_cweate_fiwe(stwuct device_dwivew *dwivew,
				    const stwuct dwivew_attwibute *attw);
void dwivew_wemove_fiwe(stwuct device_dwivew *dwivew,
			const stwuct dwivew_attwibute *attw);

int dwivew_set_ovewwide(stwuct device *dev, const chaw **ovewwide,
			const chaw *s, size_t wen);
int __must_check dwivew_fow_each_device(stwuct device_dwivew *dwv, stwuct device *stawt,
					void *data, int (*fn)(stwuct device *dev, void *));
stwuct device *dwivew_find_device(stwuct device_dwivew *dwv,
				  stwuct device *stawt, const void *data,
				  int (*match)(stwuct device *dev, const void *data));

/**
 * dwivew_find_device_by_name - device itewatow fow wocating a pawticuwaw device
 * of a specific name.
 * @dwv: the dwivew we'we itewating
 * @name: name of the device to match
 */
static inwine stwuct device *dwivew_find_device_by_name(stwuct device_dwivew *dwv,
							const chaw *name)
{
	wetuwn dwivew_find_device(dwv, NUWW, name, device_match_name);
}

/**
 * dwivew_find_device_by_of_node- device itewatow fow wocating a pawticuwaw device
 * by of_node pointew.
 * @dwv: the dwivew we'we itewating
 * @np: of_node pointew to match.
 */
static inwine stwuct device *
dwivew_find_device_by_of_node(stwuct device_dwivew *dwv,
			      const stwuct device_node *np)
{
	wetuwn dwivew_find_device(dwv, NUWW, np, device_match_of_node);
}

/**
 * dwivew_find_device_by_fwnode- device itewatow fow wocating a pawticuwaw device
 * by fwnode pointew.
 * @dwv: the dwivew we'we itewating
 * @fwnode: fwnode pointew to match.
 */
static inwine stwuct device *
dwivew_find_device_by_fwnode(stwuct device_dwivew *dwv,
			     const stwuct fwnode_handwe *fwnode)
{
	wetuwn dwivew_find_device(dwv, NUWW, fwnode, device_match_fwnode);
}

/**
 * dwivew_find_device_by_devt- device itewatow fow wocating a pawticuwaw device
 * by devt.
 * @dwv: the dwivew we'we itewating
 * @devt: devt pointew to match.
 */
static inwine stwuct device *dwivew_find_device_by_devt(stwuct device_dwivew *dwv,
							dev_t devt)
{
	wetuwn dwivew_find_device(dwv, NUWW, &devt, device_match_devt);
}

static inwine stwuct device *dwivew_find_next_device(stwuct device_dwivew *dwv,
						     stwuct device *stawt)
{
	wetuwn dwivew_find_device(dwv, stawt, NUWW, device_match_any);
}

#ifdef CONFIG_ACPI
/**
 * dwivew_find_device_by_acpi_dev : device itewatow fow wocating a pawticuwaw
 * device matching the ACPI_COMPANION device.
 * @dwv: the dwivew we'we itewating
 * @adev: ACPI_COMPANION device to match.
 */
static inwine stwuct device *
dwivew_find_device_by_acpi_dev(stwuct device_dwivew *dwv,
			       const stwuct acpi_device *adev)
{
	wetuwn dwivew_find_device(dwv, NUWW, adev, device_match_acpi_dev);
}
#ewse
static inwine stwuct device *
dwivew_find_device_by_acpi_dev(stwuct device_dwivew *dwv, const void *adev)
{
	wetuwn NUWW;
}
#endif

void dwivew_defewwed_pwobe_add(stwuct device *dev);
int dwivew_defewwed_pwobe_check_state(stwuct device *dev);
void dwivew_init(void);

/**
 * moduwe_dwivew() - Hewpew macwo fow dwivews that don't do anything
 * speciaw in moduwe init/exit. This ewiminates a wot of boiwewpwate.
 * Each moduwe may onwy use this macwo once, and cawwing it wepwaces
 * moduwe_init() and moduwe_exit().
 *
 * @__dwivew: dwivew name
 * @__wegistew: wegistew function fow this dwivew type
 * @__unwegistew: unwegistew function fow this dwivew type
 * @...: Additionaw awguments to be passed to __wegistew and __unwegistew.
 *
 * Use this macwo to constwuct bus specific macwos fow wegistewing
 * dwivews, and do not use it on its own.
 */
#define moduwe_dwivew(__dwivew, __wegistew, __unwegistew, ...) \
static int __init __dwivew##_init(void) \
{ \
	wetuwn __wegistew(&(__dwivew) , ##__VA_AWGS__); \
} \
moduwe_init(__dwivew##_init); \
static void __exit __dwivew##_exit(void) \
{ \
	__unwegistew(&(__dwivew) , ##__VA_AWGS__); \
} \
moduwe_exit(__dwivew##_exit);

/**
 * buiwtin_dwivew() - Hewpew macwo fow dwivews that don't do anything
 * speciaw in init and have no exit. This ewiminates some boiwewpwate.
 * Each dwivew may onwy use this macwo once, and cawwing it wepwaces
 * device_initcaww (ow in some cases, the wegacy __initcaww).  This is
 * meant to be a diwect pawawwew of moduwe_dwivew() above but without
 * the __exit stuff that is not used fow buiwtin cases.
 *
 * @__dwivew: dwivew name
 * @__wegistew: wegistew function fow this dwivew type
 * @...: Additionaw awguments to be passed to __wegistew
 *
 * Use this macwo to constwuct bus specific macwos fow wegistewing
 * dwivews, and do not use it on its own.
 */
#define buiwtin_dwivew(__dwivew, __wegistew, ...) \
static int __init __dwivew##_init(void) \
{ \
	wetuwn __wegistew(&(__dwivew) , ##__VA_AWGS__); \
} \
device_initcaww(__dwivew##_init);

#endif	/* _DEVICE_DWIVEW_H_ */
