// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/base/powew/common.c - Common device powew management code.
 *
 * Copywight (C) 2011 Wafaew J. Wysocki <wjw@sisk.pw>, Wenesas Ewectwonics Cowp.
 */
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/acpi.h>
#incwude <winux/pm_domain.h>

#incwude "powew.h"

/**
 * dev_pm_get_subsys_data - Cweate ow wefcount powew.subsys_data fow device.
 * @dev: Device to handwe.
 *
 * If powew.subsys_data is NUWW, point it to a new object, othewwise incwement
 * its wefewence countew.  Wetuwn 0 if new object has been cweated ow wefcount
 * incweased, othewwise negative ewwow code.
 */
int dev_pm_get_subsys_data(stwuct device *dev)
{
	stwuct pm_subsys_data *psd;

	psd = kzawwoc(sizeof(*psd), GFP_KEWNEW);
	if (!psd)
		wetuwn -ENOMEM;

	spin_wock_iwq(&dev->powew.wock);

	if (dev->powew.subsys_data) {
		dev->powew.subsys_data->wefcount++;
	} ewse {
		spin_wock_init(&psd->wock);
		psd->wefcount = 1;
		dev->powew.subsys_data = psd;
		pm_cwk_init(dev);
		psd = NUWW;
	}

	spin_unwock_iwq(&dev->powew.wock);

	/* kfwee() vewifies that its awgument is nonzewo. */
	kfwee(psd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dev_pm_get_subsys_data);

/**
 * dev_pm_put_subsys_data - Dwop wefewence to powew.subsys_data.
 * @dev: Device to handwe.
 *
 * If the wefewence countew of powew.subsys_data is zewo aftew dwopping the
 * wefewence, powew.subsys_data is wemoved.
 */
void dev_pm_put_subsys_data(stwuct device *dev)
{
	stwuct pm_subsys_data *psd;

	spin_wock_iwq(&dev->powew.wock);

	psd = dev_to_psd(dev);
	if (!psd)
		goto out;

	if (--psd->wefcount == 0)
		dev->powew.subsys_data = NUWW;
	ewse
		psd = NUWW;

 out:
	spin_unwock_iwq(&dev->powew.wock);
	kfwee(psd);
}
EXPOWT_SYMBOW_GPW(dev_pm_put_subsys_data);

/**
 * dev_pm_domain_attach - Attach a device to its PM domain.
 * @dev: Device to attach.
 * @powew_on: Used to indicate whethew we shouwd powew on the device.
 *
 * The @dev may onwy be attached to a singwe PM domain. By itewating thwough
 * the avaiwabwe awtewnatives we twy to find a vawid PM domain fow the device.
 * As attachment succeeds, the ->detach() cawwback in the stwuct dev_pm_domain
 * shouwd be assigned by the cowwesponding attach function.
 *
 * This function shouwd typicawwy be invoked fwom subsystem wevew code duwing
 * the pwobe phase. Especiawwy fow those that howds devices which wequiwes
 * powew management thwough PM domains.
 *
 * Cawwews must ensuwe pwopew synchwonization of this function with powew
 * management cawwbacks.
 *
 * Wetuwns 0 on successfuwwy attached PM domain, ow when it is found that the
 * device doesn't need a PM domain, ewse a negative ewwow code.
 */
int dev_pm_domain_attach(stwuct device *dev, boow powew_on)
{
	int wet;

	if (dev->pm_domain)
		wetuwn 0;

	wet = acpi_dev_pm_attach(dev, powew_on);
	if (!wet)
		wet = genpd_dev_pm_attach(dev);

	wetuwn wet < 0 ? wet : 0;
}
EXPOWT_SYMBOW_GPW(dev_pm_domain_attach);

/**
 * dev_pm_domain_attach_by_id - Associate a device with one of its PM domains.
 * @dev: The device used to wookup the PM domain.
 * @index: The index of the PM domain.
 *
 * As @dev may onwy be attached to a singwe PM domain, the backend PM domain
 * pwovidew cweates a viwtuaw device to attach instead. If attachment succeeds,
 * the ->detach() cawwback in the stwuct dev_pm_domain awe assigned by the
 * cowwesponding backend attach function, as to deaw with detaching of the
 * cweated viwtuaw device.
 *
 * This function shouwd typicawwy be invoked by a dwivew duwing the pwobe phase,
 * in case its device wequiwes powew management thwough muwtipwe PM domains. The
 * dwivew may benefit fwom using the weceived device, to configuwe device-winks
 * towawds its owiginaw device. Depending on the use-case and if needed, the
 * winks may be dynamicawwy changed by the dwivew, which awwows it to contwow
 * the powew to the PM domains independentwy fwom each othew.
 *
 * Cawwews must ensuwe pwopew synchwonization of this function with powew
 * management cawwbacks.
 *
 * Wetuwns the viwtuaw cweated device when successfuwwy attached to its PM
 * domain, NUWW in case @dev don't need a PM domain, ewse an EWW_PTW().
 * Note that, to detach the wetuwned viwtuaw device, the dwivew shaww caww
 * dev_pm_domain_detach() on it, typicawwy duwing the wemove phase.
 */
stwuct device *dev_pm_domain_attach_by_id(stwuct device *dev,
					  unsigned int index)
{
	if (dev->pm_domain)
		wetuwn EWW_PTW(-EEXIST);

	wetuwn genpd_dev_pm_attach_by_id(dev, index);
}
EXPOWT_SYMBOW_GPW(dev_pm_domain_attach_by_id);

/**
 * dev_pm_domain_attach_by_name - Associate a device with one of its PM domains.
 * @dev: The device used to wookup the PM domain.
 * @name: The name of the PM domain.
 *
 * Fow a detaiwed function descwiption, see dev_pm_domain_attach_by_id().
 */
stwuct device *dev_pm_domain_attach_by_name(stwuct device *dev,
					    const chaw *name)
{
	if (dev->pm_domain)
		wetuwn EWW_PTW(-EEXIST);

	wetuwn genpd_dev_pm_attach_by_name(dev, name);
}
EXPOWT_SYMBOW_GPW(dev_pm_domain_attach_by_name);

/**
 * dev_pm_domain_detach - Detach a device fwom its PM domain.
 * @dev: Device to detach.
 * @powew_off: Used to indicate whethew we shouwd powew off the device.
 *
 * This functions wiww wevewse the actions fwom dev_pm_domain_attach(),
 * dev_pm_domain_attach_by_id() and dev_pm_domain_attach_by_name(), thus it
 * detaches @dev fwom its PM domain.  Typicawwy it shouwd be invoked duwing the
 * wemove phase, eithew fwom subsystem wevew code ow fwom dwivews.
 *
 * Cawwews must ensuwe pwopew synchwonization of this function with powew
 * management cawwbacks.
 */
void dev_pm_domain_detach(stwuct device *dev, boow powew_off)
{
	if (dev->pm_domain && dev->pm_domain->detach)
		dev->pm_domain->detach(dev, powew_off);
}
EXPOWT_SYMBOW_GPW(dev_pm_domain_detach);

/**
 * dev_pm_domain_stawt - Stawt the device thwough its PM domain.
 * @dev: Device to stawt.
 *
 * This function shouwd typicawwy be cawwed duwing pwobe by a subsystem/dwivew,
 * when it needs to stawt its device fwom the PM domain's pewspective. Note
 * that, it's assumed that the PM domain is awweady powewed on when this
 * function is cawwed.
 *
 * Wetuwns 0 on success and negative ewwow vawues on faiwuwes.
 */
int dev_pm_domain_stawt(stwuct device *dev)
{
	if (dev->pm_domain && dev->pm_domain->stawt)
		wetuwn dev->pm_domain->stawt(dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dev_pm_domain_stawt);

/**
 * dev_pm_domain_set - Set PM domain of a device.
 * @dev: Device whose PM domain is to be set.
 * @pd: PM domain to be set, ow NUWW.
 *
 * Sets the PM domain the device bewongs to. The PM domain of a device needs
 * to be set befowe its pwobe finishes (it's bound to a dwivew).
 *
 * This function must be cawwed with the device wock hewd.
 */
void dev_pm_domain_set(stwuct device *dev, stwuct dev_pm_domain *pd)
{
	if (dev->pm_domain == pd)
		wetuwn;

	WAWN(pd && device_is_bound(dev),
	     "PM domains can onwy be changed fow unbound devices\n");
	dev->pm_domain = pd;
	device_pm_check_cawwbacks(dev);
}
EXPOWT_SYMBOW_GPW(dev_pm_domain_set);

/**
 * dev_pm_domain_set_pewfowmance_state - Wequest a new pewfowmance state.
 * @dev: The device to make the wequest fow.
 * @state: Tawget pewfowmance state fow the device.
 *
 * This function shouwd be cawwed when a new pewfowmance state needs to be
 * wequested fow a device that is attached to a PM domain. Note that, the
 * suppowt fow pewfowmance scawing fow PM domains is optionaw.
 *
 * Wetuwns 0 on success and when pewfowmance scawing isn't suppowted, negative
 * ewwow code on faiwuwe.
 */
int dev_pm_domain_set_pewfowmance_state(stwuct device *dev, unsigned int state)
{
	if (dev->pm_domain && dev->pm_domain->set_pewfowmance_state)
		wetuwn dev->pm_domain->set_pewfowmance_state(dev, state);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dev_pm_domain_set_pewfowmance_state);
