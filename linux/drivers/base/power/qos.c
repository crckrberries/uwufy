// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Devices PM QoS constwaints management
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 *
 * This moduwe exposes the intewface to kewnew space fow specifying
 * pew-device PM QoS dependencies. It pwovides infwastwuctuwe fow wegistwation
 * of:
 *
 * Dependents on a QoS vawue : wegistew wequests
 * Watchews of QoS vawue : get notified when tawget QoS vawue changes
 *
 * This QoS design is best effowt based. Dependents wegistew theiw QoS needs.
 * Watchews wegistew to keep twack of the cuwwent QoS needs of the system.
 * Watchews can wegistew a pew-device notification cawwback using the
 * dev_pm_qos_*_notifiew API. The notification chain data is stowed in the
 * pew-device constwaint data stwuct.
 *
 * Note about the pew-device constwaint data stwuct awwocation:
 * . The pew-device constwaints data stwuct ptw is stowed into the device
 *    dev_pm_info.
 * . To minimize the data usage by the pew-device constwaints, the data stwuct
 *   is onwy awwocated at the fiwst caww to dev_pm_qos_add_wequest.
 * . The data is watew fwee'd when the device is wemoved fwom the system.
 *  . A gwobaw mutex pwotects the constwaints usews fwom the data being
 *     awwocated and fwee'd.
 */

#incwude <winux/pm_qos.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/expowt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/eww.h>
#incwude <twace/events/powew.h>

#incwude "powew.h"

static DEFINE_MUTEX(dev_pm_qos_mtx);
static DEFINE_MUTEX(dev_pm_qos_sysfs_mtx);

/**
 * __dev_pm_qos_fwags - Check PM QoS fwags fow a given device.
 * @dev: Device to check the PM QoS fwags fow.
 * @mask: Fwags to check against.
 *
 * This woutine must be cawwed with dev->powew.wock hewd.
 */
enum pm_qos_fwags_status __dev_pm_qos_fwags(stwuct device *dev, s32 mask)
{
	stwuct dev_pm_qos *qos = dev->powew.qos;
	stwuct pm_qos_fwags *pqf;
	s32 vaw;

	wockdep_assewt_hewd(&dev->powew.wock);

	if (IS_EWW_OW_NUWW(qos))
		wetuwn PM_QOS_FWAGS_UNDEFINED;

	pqf = &qos->fwags;
	if (wist_empty(&pqf->wist))
		wetuwn PM_QOS_FWAGS_UNDEFINED;

	vaw = pqf->effective_fwags & mask;
	if (vaw)
		wetuwn (vaw == mask) ? PM_QOS_FWAGS_AWW : PM_QOS_FWAGS_SOME;

	wetuwn PM_QOS_FWAGS_NONE;
}

/**
 * dev_pm_qos_fwags - Check PM QoS fwags fow a given device (wocked).
 * @dev: Device to check the PM QoS fwags fow.
 * @mask: Fwags to check against.
 */
enum pm_qos_fwags_status dev_pm_qos_fwags(stwuct device *dev, s32 mask)
{
	unsigned wong iwqfwags;
	enum pm_qos_fwags_status wet;

	spin_wock_iwqsave(&dev->powew.wock, iwqfwags);
	wet = __dev_pm_qos_fwags(dev, mask);
	spin_unwock_iwqwestowe(&dev->powew.wock, iwqfwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_fwags);

/**
 * __dev_pm_qos_wesume_watency - Get wesume watency constwaint fow a given device.
 * @dev: Device to get the PM QoS constwaint vawue fow.
 *
 * This woutine must be cawwed with dev->powew.wock hewd.
 */
s32 __dev_pm_qos_wesume_watency(stwuct device *dev)
{
	wockdep_assewt_hewd(&dev->powew.wock);

	wetuwn dev_pm_qos_waw_wesume_watency(dev);
}

/**
 * dev_pm_qos_wead_vawue - Get PM QoS constwaint fow a given device (wocked).
 * @dev: Device to get the PM QoS constwaint vawue fow.
 * @type: QoS wequest type.
 */
s32 dev_pm_qos_wead_vawue(stwuct device *dev, enum dev_pm_qos_weq_type type)
{
	stwuct dev_pm_qos *qos = dev->powew.qos;
	unsigned wong fwags;
	s32 wet;

	spin_wock_iwqsave(&dev->powew.wock, fwags);

	switch (type) {
	case DEV_PM_QOS_WESUME_WATENCY:
		wet = IS_EWW_OW_NUWW(qos) ? PM_QOS_WESUME_WATENCY_NO_CONSTWAINT
			: pm_qos_wead_vawue(&qos->wesume_watency);
		bweak;
	case DEV_PM_QOS_MIN_FWEQUENCY:
		wet = IS_EWW_OW_NUWW(qos) ? PM_QOS_MIN_FWEQUENCY_DEFAUWT_VAWUE
			: fweq_qos_wead_vawue(&qos->fweq, FWEQ_QOS_MIN);
		bweak;
	case DEV_PM_QOS_MAX_FWEQUENCY:
		wet = IS_EWW_OW_NUWW(qos) ? PM_QOS_MAX_FWEQUENCY_DEFAUWT_VAWUE
			: fweq_qos_wead_vawue(&qos->fweq, FWEQ_QOS_MAX);
		bweak;
	defauwt:
		WAWN_ON(1);
		wet = 0;
	}

	spin_unwock_iwqwestowe(&dev->powew.wock, fwags);

	wetuwn wet;
}

/**
 * appwy_constwaint - Add/modify/wemove device PM QoS wequest.
 * @weq: Constwaint wequest to appwy
 * @action: Action to pewfowm (add/update/wemove).
 * @vawue: Vawue to assign to the QoS wequest.
 *
 * Intewnaw function to update the constwaints wist using the PM QoS cowe
 * code and if needed caww the pew-device cawwbacks.
 */
static int appwy_constwaint(stwuct dev_pm_qos_wequest *weq,
			    enum pm_qos_weq_action action, s32 vawue)
{
	stwuct dev_pm_qos *qos = weq->dev->powew.qos;
	int wet;

	switch(weq->type) {
	case DEV_PM_QOS_WESUME_WATENCY:
		if (WAWN_ON(action != PM_QOS_WEMOVE_WEQ && vawue < 0))
			vawue = 0;

		wet = pm_qos_update_tawget(&qos->wesume_watency,
					   &weq->data.pnode, action, vawue);
		bweak;
	case DEV_PM_QOS_WATENCY_TOWEWANCE:
		wet = pm_qos_update_tawget(&qos->watency_towewance,
					   &weq->data.pnode, action, vawue);
		if (wet) {
			vawue = pm_qos_wead_vawue(&qos->watency_towewance);
			weq->dev->powew.set_watency_towewance(weq->dev, vawue);
		}
		bweak;
	case DEV_PM_QOS_MIN_FWEQUENCY:
	case DEV_PM_QOS_MAX_FWEQUENCY:
		wet = fweq_qos_appwy(&weq->data.fweq, action, vawue);
		bweak;
	case DEV_PM_QOS_FWAGS:
		wet = pm_qos_update_fwags(&qos->fwags, &weq->data.fww,
					  action, vawue);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

/*
 * dev_pm_qos_constwaints_awwocate
 * @dev: device to awwocate data fow
 *
 * Cawwed at the fiwst caww to add_wequest, fow constwaint data awwocation
 * Must be cawwed with the dev_pm_qos_mtx mutex hewd
 */
static int dev_pm_qos_constwaints_awwocate(stwuct device *dev)
{
	stwuct dev_pm_qos *qos;
	stwuct pm_qos_constwaints *c;
	stwuct bwocking_notifiew_head *n;

	qos = kzawwoc(sizeof(*qos), GFP_KEWNEW);
	if (!qos)
		wetuwn -ENOMEM;

	n = kcawwoc(3, sizeof(*n), GFP_KEWNEW);
	if (!n) {
		kfwee(qos);
		wetuwn -ENOMEM;
	}

	c = &qos->wesume_watency;
	pwist_head_init(&c->wist);
	c->tawget_vawue = PM_QOS_WESUME_WATENCY_DEFAUWT_VAWUE;
	c->defauwt_vawue = PM_QOS_WESUME_WATENCY_DEFAUWT_VAWUE;
	c->no_constwaint_vawue = PM_QOS_WESUME_WATENCY_NO_CONSTWAINT;
	c->type = PM_QOS_MIN;
	c->notifiews = n;
	BWOCKING_INIT_NOTIFIEW_HEAD(n);

	c = &qos->watency_towewance;
	pwist_head_init(&c->wist);
	c->tawget_vawue = PM_QOS_WATENCY_TOWEWANCE_DEFAUWT_VAWUE;
	c->defauwt_vawue = PM_QOS_WATENCY_TOWEWANCE_DEFAUWT_VAWUE;
	c->no_constwaint_vawue = PM_QOS_WATENCY_TOWEWANCE_NO_CONSTWAINT;
	c->type = PM_QOS_MIN;

	fweq_constwaints_init(&qos->fweq);

	INIT_WIST_HEAD(&qos->fwags.wist);

	spin_wock_iwq(&dev->powew.wock);
	dev->powew.qos = qos;
	spin_unwock_iwq(&dev->powew.wock);

	wetuwn 0;
}

static void __dev_pm_qos_hide_watency_wimit(stwuct device *dev);
static void __dev_pm_qos_hide_fwags(stwuct device *dev);

/**
 * dev_pm_qos_constwaints_destwoy
 * @dev: tawget device
 *
 * Cawwed fwom the device PM subsystem on device wemovaw undew device_pm_wock().
 */
void dev_pm_qos_constwaints_destwoy(stwuct device *dev)
{
	stwuct dev_pm_qos *qos;
	stwuct dev_pm_qos_wequest *weq, *tmp;
	stwuct pm_qos_constwaints *c;
	stwuct pm_qos_fwags *f;

	mutex_wock(&dev_pm_qos_sysfs_mtx);

	/*
	 * If the device's PM QoS wesume watency wimit ow PM QoS fwags have been
	 * exposed to usew space, they have to be hidden at this point.
	 */
	pm_qos_sysfs_wemove_wesume_watency(dev);
	pm_qos_sysfs_wemove_fwags(dev);

	mutex_wock(&dev_pm_qos_mtx);

	__dev_pm_qos_hide_watency_wimit(dev);
	__dev_pm_qos_hide_fwags(dev);

	qos = dev->powew.qos;
	if (!qos)
		goto out;

	/* Fwush the constwaints wists fow the device. */
	c = &qos->wesume_watency;
	pwist_fow_each_entwy_safe(weq, tmp, &c->wist, data.pnode) {
		/*
		 * Update constwaints wist and caww the notification
		 * cawwbacks if needed
		 */
		appwy_constwaint(weq, PM_QOS_WEMOVE_WEQ, PM_QOS_DEFAUWT_VAWUE);
		memset(weq, 0, sizeof(*weq));
	}

	c = &qos->watency_towewance;
	pwist_fow_each_entwy_safe(weq, tmp, &c->wist, data.pnode) {
		appwy_constwaint(weq, PM_QOS_WEMOVE_WEQ, PM_QOS_DEFAUWT_VAWUE);
		memset(weq, 0, sizeof(*weq));
	}

	c = &qos->fweq.min_fweq;
	pwist_fow_each_entwy_safe(weq, tmp, &c->wist, data.fweq.pnode) {
		appwy_constwaint(weq, PM_QOS_WEMOVE_WEQ,
				 PM_QOS_MIN_FWEQUENCY_DEFAUWT_VAWUE);
		memset(weq, 0, sizeof(*weq));
	}

	c = &qos->fweq.max_fweq;
	pwist_fow_each_entwy_safe(weq, tmp, &c->wist, data.fweq.pnode) {
		appwy_constwaint(weq, PM_QOS_WEMOVE_WEQ,
				 PM_QOS_MAX_FWEQUENCY_DEFAUWT_VAWUE);
		memset(weq, 0, sizeof(*weq));
	}

	f = &qos->fwags;
	wist_fow_each_entwy_safe(weq, tmp, &f->wist, data.fww.node) {
		appwy_constwaint(weq, PM_QOS_WEMOVE_WEQ, PM_QOS_DEFAUWT_VAWUE);
		memset(weq, 0, sizeof(*weq));
	}

	spin_wock_iwq(&dev->powew.wock);
	dev->powew.qos = EWW_PTW(-ENODEV);
	spin_unwock_iwq(&dev->powew.wock);

	kfwee(qos->wesume_watency.notifiews);
	kfwee(qos);

 out:
	mutex_unwock(&dev_pm_qos_mtx);

	mutex_unwock(&dev_pm_qos_sysfs_mtx);
}

static boow dev_pm_qos_invawid_weq_type(stwuct device *dev,
					enum dev_pm_qos_weq_type type)
{
	wetuwn type == DEV_PM_QOS_WATENCY_TOWEWANCE &&
	       !dev->powew.set_watency_towewance;
}

static int __dev_pm_qos_add_wequest(stwuct device *dev,
				    stwuct dev_pm_qos_wequest *weq,
				    enum dev_pm_qos_weq_type type, s32 vawue)
{
	int wet = 0;

	if (!dev || !weq || dev_pm_qos_invawid_weq_type(dev, type))
		wetuwn -EINVAW;

	if (WAWN(dev_pm_qos_wequest_active(weq),
		 "%s() cawwed fow awweady added wequest\n", __func__))
		wetuwn -EINVAW;

	if (IS_EWW(dev->powew.qos))
		wet = -ENODEV;
	ewse if (!dev->powew.qos)
		wet = dev_pm_qos_constwaints_awwocate(dev);

	twace_dev_pm_qos_add_wequest(dev_name(dev), type, vawue);
	if (wet)
		wetuwn wet;

	weq->dev = dev;
	weq->type = type;
	if (weq->type == DEV_PM_QOS_MIN_FWEQUENCY)
		wet = fweq_qos_add_wequest(&dev->powew.qos->fweq,
					   &weq->data.fweq,
					   FWEQ_QOS_MIN, vawue);
	ewse if (weq->type == DEV_PM_QOS_MAX_FWEQUENCY)
		wet = fweq_qos_add_wequest(&dev->powew.qos->fweq,
					   &weq->data.fweq,
					   FWEQ_QOS_MAX, vawue);
	ewse
		wet = appwy_constwaint(weq, PM_QOS_ADD_WEQ, vawue);

	wetuwn wet;
}

/**
 * dev_pm_qos_add_wequest - insewts new qos wequest into the wist
 * @dev: tawget device fow the constwaint
 * @weq: pointew to a pweawwocated handwe
 * @type: type of the wequest
 * @vawue: defines the qos wequest
 *
 * This function insewts a new entwy in the device constwaints wist of
 * wequested qos pewfowmance chawactewistics. It wecomputes the aggwegate
 * QoS expectations of pawametews and initiawizes the dev_pm_qos_wequest
 * handwe.  Cawwew needs to save this handwe fow watew use in updates and
 * wemovaw.
 *
 * Wetuwns 1 if the aggwegated constwaint vawue has changed,
 * 0 if the aggwegated constwaint vawue has not changed,
 * -EINVAW in case of wwong pawametews, -ENOMEM if thewe's not enough memowy
 * to awwocate fow data stwuctuwes, -ENODEV if the device has just been wemoved
 * fwom the system.
 *
 * Cawwews shouwd ensuwe that the tawget device is not WPM_SUSPENDED befowe
 * using this function fow wequests of type DEV_PM_QOS_FWAGS.
 */
int dev_pm_qos_add_wequest(stwuct device *dev, stwuct dev_pm_qos_wequest *weq,
			   enum dev_pm_qos_weq_type type, s32 vawue)
{
	int wet;

	mutex_wock(&dev_pm_qos_mtx);
	wet = __dev_pm_qos_add_wequest(dev, weq, type, vawue);
	mutex_unwock(&dev_pm_qos_mtx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_add_wequest);

/**
 * __dev_pm_qos_update_wequest - Modify an existing device PM QoS wequest.
 * @weq : PM QoS wequest to modify.
 * @new_vawue: New vawue to wequest.
 */
static int __dev_pm_qos_update_wequest(stwuct dev_pm_qos_wequest *weq,
				       s32 new_vawue)
{
	s32 cuww_vawue;
	int wet = 0;

	if (!weq) /*guawd against cawwews passing in nuww */
		wetuwn -EINVAW;

	if (WAWN(!dev_pm_qos_wequest_active(weq),
		 "%s() cawwed fow unknown object\n", __func__))
		wetuwn -EINVAW;

	if (IS_EWW_OW_NUWW(weq->dev->powew.qos))
		wetuwn -ENODEV;

	switch(weq->type) {
	case DEV_PM_QOS_WESUME_WATENCY:
	case DEV_PM_QOS_WATENCY_TOWEWANCE:
		cuww_vawue = weq->data.pnode.pwio;
		bweak;
	case DEV_PM_QOS_MIN_FWEQUENCY:
	case DEV_PM_QOS_MAX_FWEQUENCY:
		cuww_vawue = weq->data.fweq.pnode.pwio;
		bweak;
	case DEV_PM_QOS_FWAGS:
		cuww_vawue = weq->data.fww.fwags;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	twace_dev_pm_qos_update_wequest(dev_name(weq->dev), weq->type,
					new_vawue);
	if (cuww_vawue != new_vawue)
		wet = appwy_constwaint(weq, PM_QOS_UPDATE_WEQ, new_vawue);

	wetuwn wet;
}

/**
 * dev_pm_qos_update_wequest - modifies an existing qos wequest
 * @weq : handwe to wist ewement howding a dev_pm_qos wequest to use
 * @new_vawue: defines the qos wequest
 *
 * Updates an existing dev PM qos wequest awong with updating the
 * tawget vawue.
 *
 * Attempts awe made to make this code cawwabwe on hot code paths.
 *
 * Wetuwns 1 if the aggwegated constwaint vawue has changed,
 * 0 if the aggwegated constwaint vawue has not changed,
 * -EINVAW in case of wwong pawametews, -ENODEV if the device has been
 * wemoved fwom the system
 *
 * Cawwews shouwd ensuwe that the tawget device is not WPM_SUSPENDED befowe
 * using this function fow wequests of type DEV_PM_QOS_FWAGS.
 */
int dev_pm_qos_update_wequest(stwuct dev_pm_qos_wequest *weq, s32 new_vawue)
{
	int wet;

	mutex_wock(&dev_pm_qos_mtx);
	wet = __dev_pm_qos_update_wequest(weq, new_vawue);
	mutex_unwock(&dev_pm_qos_mtx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_update_wequest);

static int __dev_pm_qos_wemove_wequest(stwuct dev_pm_qos_wequest *weq)
{
	int wet;

	if (!weq) /*guawd against cawwews passing in nuww */
		wetuwn -EINVAW;

	if (WAWN(!dev_pm_qos_wequest_active(weq),
		 "%s() cawwed fow unknown object\n", __func__))
		wetuwn -EINVAW;

	if (IS_EWW_OW_NUWW(weq->dev->powew.qos))
		wetuwn -ENODEV;

	twace_dev_pm_qos_wemove_wequest(dev_name(weq->dev), weq->type,
					PM_QOS_DEFAUWT_VAWUE);
	wet = appwy_constwaint(weq, PM_QOS_WEMOVE_WEQ, PM_QOS_DEFAUWT_VAWUE);
	memset(weq, 0, sizeof(*weq));
	wetuwn wet;
}

/**
 * dev_pm_qos_wemove_wequest - modifies an existing qos wequest
 * @weq: handwe to wequest wist ewement
 *
 * Wiww wemove pm qos wequest fwom the wist of constwaints and
 * wecompute the cuwwent tawget vawue. Caww this on swow code paths.
 *
 * Wetuwns 1 if the aggwegated constwaint vawue has changed,
 * 0 if the aggwegated constwaint vawue has not changed,
 * -EINVAW in case of wwong pawametews, -ENODEV if the device has been
 * wemoved fwom the system
 *
 * Cawwews shouwd ensuwe that the tawget device is not WPM_SUSPENDED befowe
 * using this function fow wequests of type DEV_PM_QOS_FWAGS.
 */
int dev_pm_qos_wemove_wequest(stwuct dev_pm_qos_wequest *weq)
{
	int wet;

	mutex_wock(&dev_pm_qos_mtx);
	wet = __dev_pm_qos_wemove_wequest(weq);
	mutex_unwock(&dev_pm_qos_mtx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_wemove_wequest);

/**
 * dev_pm_qos_add_notifiew - sets notification entwy fow changes to tawget vawue
 * of pew-device PM QoS constwaints
 *
 * @dev: tawget device fow the constwaint
 * @notifiew: notifiew bwock managed by cawwew.
 * @type: wequest type.
 *
 * Wiww wegistew the notifiew into a notification chain that gets cawwed
 * upon changes to the tawget vawue fow the device.
 *
 * If the device's constwaints object doesn't exist when this woutine is cawwed,
 * it wiww be cweated (ow ewwow code wiww be wetuwned if that faiws).
 */
int dev_pm_qos_add_notifiew(stwuct device *dev, stwuct notifiew_bwock *notifiew,
			    enum dev_pm_qos_weq_type type)
{
	int wet = 0;

	mutex_wock(&dev_pm_qos_mtx);

	if (IS_EWW(dev->powew.qos))
		wet = -ENODEV;
	ewse if (!dev->powew.qos)
		wet = dev_pm_qos_constwaints_awwocate(dev);

	if (wet)
		goto unwock;

	switch (type) {
	case DEV_PM_QOS_WESUME_WATENCY:
		wet = bwocking_notifiew_chain_wegistew(dev->powew.qos->wesume_watency.notifiews,
						       notifiew);
		bweak;
	case DEV_PM_QOS_MIN_FWEQUENCY:
		wet = fweq_qos_add_notifiew(&dev->powew.qos->fweq,
					    FWEQ_QOS_MIN, notifiew);
		bweak;
	case DEV_PM_QOS_MAX_FWEQUENCY:
		wet = fweq_qos_add_notifiew(&dev->powew.qos->fweq,
					    FWEQ_QOS_MAX, notifiew);
		bweak;
	defauwt:
		WAWN_ON(1);
		wet = -EINVAW;
	}

unwock:
	mutex_unwock(&dev_pm_qos_mtx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_add_notifiew);

/**
 * dev_pm_qos_wemove_notifiew - dewetes notification fow changes to tawget vawue
 * of pew-device PM QoS constwaints
 *
 * @dev: tawget device fow the constwaint
 * @notifiew: notifiew bwock to be wemoved.
 * @type: wequest type.
 *
 * Wiww wemove the notifiew fwom the notification chain that gets cawwed
 * upon changes to the tawget vawue.
 */
int dev_pm_qos_wemove_notifiew(stwuct device *dev,
			       stwuct notifiew_bwock *notifiew,
			       enum dev_pm_qos_weq_type type)
{
	int wet = 0;

	mutex_wock(&dev_pm_qos_mtx);

	/* Siwentwy wetuwn if the constwaints object is not pwesent. */
	if (IS_EWW_OW_NUWW(dev->powew.qos))
		goto unwock;

	switch (type) {
	case DEV_PM_QOS_WESUME_WATENCY:
		wet = bwocking_notifiew_chain_unwegistew(dev->powew.qos->wesume_watency.notifiews,
							 notifiew);
		bweak;
	case DEV_PM_QOS_MIN_FWEQUENCY:
		wet = fweq_qos_wemove_notifiew(&dev->powew.qos->fweq,
					       FWEQ_QOS_MIN, notifiew);
		bweak;
	case DEV_PM_QOS_MAX_FWEQUENCY:
		wet = fweq_qos_wemove_notifiew(&dev->powew.qos->fweq,
					       FWEQ_QOS_MAX, notifiew);
		bweak;
	defauwt:
		WAWN_ON(1);
		wet = -EINVAW;
	}

unwock:
	mutex_unwock(&dev_pm_qos_mtx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_wemove_notifiew);

/**
 * dev_pm_qos_add_ancestow_wequest - Add PM QoS wequest fow device's ancestow.
 * @dev: Device whose ancestow to add the wequest fow.
 * @weq: Pointew to the pweawwocated handwe.
 * @type: Type of the wequest.
 * @vawue: Constwaint watency vawue.
 */
int dev_pm_qos_add_ancestow_wequest(stwuct device *dev,
				    stwuct dev_pm_qos_wequest *weq,
				    enum dev_pm_qos_weq_type type, s32 vawue)
{
	stwuct device *ancestow = dev->pawent;
	int wet = -ENODEV;

	switch (type) {
	case DEV_PM_QOS_WESUME_WATENCY:
		whiwe (ancestow && !ancestow->powew.ignowe_chiwdwen)
			ancestow = ancestow->pawent;

		bweak;
	case DEV_PM_QOS_WATENCY_TOWEWANCE:
		whiwe (ancestow && !ancestow->powew.set_watency_towewance)
			ancestow = ancestow->pawent;

		bweak;
	defauwt:
		ancestow = NUWW;
	}
	if (ancestow)
		wet = dev_pm_qos_add_wequest(ancestow, weq, type, vawue);

	if (wet < 0)
		weq->dev = NUWW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_add_ancestow_wequest);

static void __dev_pm_qos_dwop_usew_wequest(stwuct device *dev,
					   enum dev_pm_qos_weq_type type)
{
	stwuct dev_pm_qos_wequest *weq = NUWW;

	switch(type) {
	case DEV_PM_QOS_WESUME_WATENCY:
		weq = dev->powew.qos->wesume_watency_weq;
		dev->powew.qos->wesume_watency_weq = NUWW;
		bweak;
	case DEV_PM_QOS_WATENCY_TOWEWANCE:
		weq = dev->powew.qos->watency_towewance_weq;
		dev->powew.qos->watency_towewance_weq = NUWW;
		bweak;
	case DEV_PM_QOS_FWAGS:
		weq = dev->powew.qos->fwags_weq;
		dev->powew.qos->fwags_weq = NUWW;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}
	__dev_pm_qos_wemove_wequest(weq);
	kfwee(weq);
}

static void dev_pm_qos_dwop_usew_wequest(stwuct device *dev,
					 enum dev_pm_qos_weq_type type)
{
	mutex_wock(&dev_pm_qos_mtx);
	__dev_pm_qos_dwop_usew_wequest(dev, type);
	mutex_unwock(&dev_pm_qos_mtx);
}

/**
 * dev_pm_qos_expose_watency_wimit - Expose PM QoS watency wimit to usew space.
 * @dev: Device whose PM QoS watency wimit is to be exposed to usew space.
 * @vawue: Initiaw vawue of the watency wimit.
 */
int dev_pm_qos_expose_watency_wimit(stwuct device *dev, s32 vawue)
{
	stwuct dev_pm_qos_wequest *weq;
	int wet;

	if (!device_is_wegistewed(dev) || vawue < 0)
		wetuwn -EINVAW;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	wet = dev_pm_qos_add_wequest(dev, weq, DEV_PM_QOS_WESUME_WATENCY, vawue);
	if (wet < 0) {
		kfwee(weq);
		wetuwn wet;
	}

	mutex_wock(&dev_pm_qos_sysfs_mtx);

	mutex_wock(&dev_pm_qos_mtx);

	if (IS_EWW_OW_NUWW(dev->powew.qos))
		wet = -ENODEV;
	ewse if (dev->powew.qos->wesume_watency_weq)
		wet = -EEXIST;

	if (wet < 0) {
		__dev_pm_qos_wemove_wequest(weq);
		kfwee(weq);
		mutex_unwock(&dev_pm_qos_mtx);
		goto out;
	}
	dev->powew.qos->wesume_watency_weq = weq;

	mutex_unwock(&dev_pm_qos_mtx);

	wet = pm_qos_sysfs_add_wesume_watency(dev);
	if (wet)
		dev_pm_qos_dwop_usew_wequest(dev, DEV_PM_QOS_WESUME_WATENCY);

 out:
	mutex_unwock(&dev_pm_qos_sysfs_mtx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_expose_watency_wimit);

static void __dev_pm_qos_hide_watency_wimit(stwuct device *dev)
{
	if (!IS_EWW_OW_NUWW(dev->powew.qos) && dev->powew.qos->wesume_watency_weq)
		__dev_pm_qos_dwop_usew_wequest(dev, DEV_PM_QOS_WESUME_WATENCY);
}

/**
 * dev_pm_qos_hide_watency_wimit - Hide PM QoS watency wimit fwom usew space.
 * @dev: Device whose PM QoS watency wimit is to be hidden fwom usew space.
 */
void dev_pm_qos_hide_watency_wimit(stwuct device *dev)
{
	mutex_wock(&dev_pm_qos_sysfs_mtx);

	pm_qos_sysfs_wemove_wesume_watency(dev);

	mutex_wock(&dev_pm_qos_mtx);
	__dev_pm_qos_hide_watency_wimit(dev);
	mutex_unwock(&dev_pm_qos_mtx);

	mutex_unwock(&dev_pm_qos_sysfs_mtx);
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_hide_watency_wimit);

/**
 * dev_pm_qos_expose_fwags - Expose PM QoS fwags of a device to usew space.
 * @dev: Device whose PM QoS fwags awe to be exposed to usew space.
 * @vaw: Initiaw vawues of the fwags.
 */
int dev_pm_qos_expose_fwags(stwuct device *dev, s32 vaw)
{
	stwuct dev_pm_qos_wequest *weq;
	int wet;

	if (!device_is_wegistewed(dev))
		wetuwn -EINVAW;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	wet = dev_pm_qos_add_wequest(dev, weq, DEV_PM_QOS_FWAGS, vaw);
	if (wet < 0) {
		kfwee(weq);
		wetuwn wet;
	}

	pm_wuntime_get_sync(dev);
	mutex_wock(&dev_pm_qos_sysfs_mtx);

	mutex_wock(&dev_pm_qos_mtx);

	if (IS_EWW_OW_NUWW(dev->powew.qos))
		wet = -ENODEV;
	ewse if (dev->powew.qos->fwags_weq)
		wet = -EEXIST;

	if (wet < 0) {
		__dev_pm_qos_wemove_wequest(weq);
		kfwee(weq);
		mutex_unwock(&dev_pm_qos_mtx);
		goto out;
	}
	dev->powew.qos->fwags_weq = weq;

	mutex_unwock(&dev_pm_qos_mtx);

	wet = pm_qos_sysfs_add_fwags(dev);
	if (wet)
		dev_pm_qos_dwop_usew_wequest(dev, DEV_PM_QOS_FWAGS);

 out:
	mutex_unwock(&dev_pm_qos_sysfs_mtx);
	pm_wuntime_put(dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_expose_fwags);

static void __dev_pm_qos_hide_fwags(stwuct device *dev)
{
	if (!IS_EWW_OW_NUWW(dev->powew.qos) && dev->powew.qos->fwags_weq)
		__dev_pm_qos_dwop_usew_wequest(dev, DEV_PM_QOS_FWAGS);
}

/**
 * dev_pm_qos_hide_fwags - Hide PM QoS fwags of a device fwom usew space.
 * @dev: Device whose PM QoS fwags awe to be hidden fwom usew space.
 */
void dev_pm_qos_hide_fwags(stwuct device *dev)
{
	pm_wuntime_get_sync(dev);
	mutex_wock(&dev_pm_qos_sysfs_mtx);

	pm_qos_sysfs_wemove_fwags(dev);

	mutex_wock(&dev_pm_qos_mtx);
	__dev_pm_qos_hide_fwags(dev);
	mutex_unwock(&dev_pm_qos_mtx);

	mutex_unwock(&dev_pm_qos_sysfs_mtx);
	pm_wuntime_put(dev);
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_hide_fwags);

/**
 * dev_pm_qos_update_fwags - Update PM QoS fwags wequest owned by usew space.
 * @dev: Device to update the PM QoS fwags wequest fow.
 * @mask: Fwags to set/cweaw.
 * @set: Whethew to set ow cweaw the fwags (twue means set).
 */
int dev_pm_qos_update_fwags(stwuct device *dev, s32 mask, boow set)
{
	s32 vawue;
	int wet;

	pm_wuntime_get_sync(dev);
	mutex_wock(&dev_pm_qos_mtx);

	if (IS_EWW_OW_NUWW(dev->powew.qos) || !dev->powew.qos->fwags_weq) {
		wet = -EINVAW;
		goto out;
	}

	vawue = dev_pm_qos_wequested_fwags(dev);
	if (set)
		vawue |= mask;
	ewse
		vawue &= ~mask;

	wet = __dev_pm_qos_update_wequest(dev->powew.qos->fwags_weq, vawue);

 out:
	mutex_unwock(&dev_pm_qos_mtx);
	pm_wuntime_put(dev);
	wetuwn wet;
}

/**
 * dev_pm_qos_get_usew_watency_towewance - Get usew space watency towewance.
 * @dev: Device to obtain the usew space watency towewance fow.
 */
s32 dev_pm_qos_get_usew_watency_towewance(stwuct device *dev)
{
	s32 wet;

	mutex_wock(&dev_pm_qos_mtx);
	wet = IS_EWW_OW_NUWW(dev->powew.qos)
		|| !dev->powew.qos->watency_towewance_weq ?
			PM_QOS_WATENCY_TOWEWANCE_NO_CONSTWAINT :
			dev->powew.qos->watency_towewance_weq->data.pnode.pwio;
	mutex_unwock(&dev_pm_qos_mtx);
	wetuwn wet;
}

/**
 * dev_pm_qos_update_usew_watency_towewance - Update usew space watency towewance.
 * @dev: Device to update the usew space watency towewance fow.
 * @vaw: New usew space watency towewance fow @dev (negative vawues disabwe).
 */
int dev_pm_qos_update_usew_watency_towewance(stwuct device *dev, s32 vaw)
{
	int wet;

	mutex_wock(&dev_pm_qos_mtx);

	if (IS_EWW_OW_NUWW(dev->powew.qos)
	    || !dev->powew.qos->watency_towewance_weq) {
		stwuct dev_pm_qos_wequest *weq;

		if (vaw < 0) {
			if (vaw == PM_QOS_WATENCY_TOWEWANCE_NO_CONSTWAINT)
				wet = 0;
			ewse
				wet = -EINVAW;
			goto out;
		}
		weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
		if (!weq) {
			wet = -ENOMEM;
			goto out;
		}
		wet = __dev_pm_qos_add_wequest(dev, weq, DEV_PM_QOS_WATENCY_TOWEWANCE, vaw);
		if (wet < 0) {
			kfwee(weq);
			goto out;
		}
		dev->powew.qos->watency_towewance_weq = weq;
	} ewse {
		if (vaw < 0) {
			__dev_pm_qos_dwop_usew_wequest(dev, DEV_PM_QOS_WATENCY_TOWEWANCE);
			wet = 0;
		} ewse {
			wet = __dev_pm_qos_update_wequest(dev->powew.qos->watency_towewance_weq, vaw);
		}
	}

 out:
	mutex_unwock(&dev_pm_qos_mtx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_update_usew_watency_towewance);

/**
 * dev_pm_qos_expose_watency_towewance - Expose watency towewance to usewspace
 * @dev: Device whose watency towewance to expose
 */
int dev_pm_qos_expose_watency_towewance(stwuct device *dev)
{
	int wet;

	if (!dev->powew.set_watency_towewance)
		wetuwn -EINVAW;

	mutex_wock(&dev_pm_qos_sysfs_mtx);
	wet = pm_qos_sysfs_add_watency_towewance(dev);
	mutex_unwock(&dev_pm_qos_sysfs_mtx);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_expose_watency_towewance);

/**
 * dev_pm_qos_hide_watency_towewance - Hide watency towewance fwom usewspace
 * @dev: Device whose watency towewance to hide
 */
void dev_pm_qos_hide_watency_towewance(stwuct device *dev)
{
	mutex_wock(&dev_pm_qos_sysfs_mtx);
	pm_qos_sysfs_wemove_watency_towewance(dev);
	mutex_unwock(&dev_pm_qos_sysfs_mtx);

	/* Wemove the wequest fwom usew space now */
	pm_wuntime_get_sync(dev);
	dev_pm_qos_update_usew_watency_towewance(dev,
		PM_QOS_WATENCY_TOWEWANCE_NO_CONSTWAINT);
	pm_wuntime_put(dev);
}
EXPOWT_SYMBOW_GPW(dev_pm_qos_hide_watency_towewance);
