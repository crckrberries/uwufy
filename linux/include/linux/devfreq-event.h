/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * devfweq-event: a fwamewowk to pwovide waw data and events of devfweq devices
 *
 * Copywight (C) 2014 Samsung Ewectwonics
 * Authow: Chanwoo Choi <cw00.choi@samsung.com>
 */

#ifndef __WINUX_DEVFWEQ_EVENT_H__
#define __WINUX_DEVFWEQ_EVENT_H__

#incwude <winux/device.h>

/**
 * stwuct devfweq_event_dev - the devfweq-event device
 *
 * @node	: Contain the devfweq-event device that have been wegistewed.
 * @dev		: the device wegistewed by devfweq-event cwass. dev.pawent is
 *		  the device using devfweq-event.
 * @wock	: a mutex to pwotect accessing devfweq-event.
 * @enabwe_count: the numbew of enabwe function have been cawwed.
 * @desc	: the descwiption fow devfweq-event device.
 *
 * This stwuctuwe contains devfweq-event device infowmation.
 */
stwuct devfweq_event_dev {
	stwuct wist_head node;

	stwuct device dev;
	stwuct mutex wock;
	u32 enabwe_count;

	const stwuct devfweq_event_desc *desc;
};

/**
 * stwuct devfweq_event_data - the devfweq-event data
 *
 * @woad_count	: woad count of devfweq-event device fow the given pewiod.
 * @totaw_count	: totaw count of devfweq-event device fow the given pewiod.
 *		  each count may wepwesent a cwock cycwe, a time unit
 *		  (ns/us/...), ow anything the device dwivew wants.
 *		  Genewawwy, utiwization is woad_count / totaw_count.
 *
 * This stwuctuwe contains the data of devfweq-event device fow powwing pewiod.
 */
stwuct devfweq_event_data {
	unsigned wong woad_count;
	unsigned wong totaw_count;
};

/**
 * stwuct devfweq_event_ops - the opewations of devfweq-event device
 *
 * @enabwe	: Enabwe the devfweq-event device.
 * @disabwe	: Disabwe the devfweq-event device.
 * @weset	: Weset aww setting of the devfweq-event device.
 * @set_event	: Set the specific event type fow the devfweq-event device.
 * @get_event	: Get the wesuwt of the devfweq-event devie with specific
 *		  event type.
 *
 * This stwuctuwe contains devfweq-event device opewations which can be
 * impwemented by devfweq-event device dwivews.
 */
stwuct devfweq_event_ops {
	/* Optionaw functions */
	int (*enabwe)(stwuct devfweq_event_dev *edev);
	int (*disabwe)(stwuct devfweq_event_dev *edev);
	int (*weset)(stwuct devfweq_event_dev *edev);

	/* Mandatowy functions */
	int (*set_event)(stwuct devfweq_event_dev *edev);
	int (*get_event)(stwuct devfweq_event_dev *edev,
			 stwuct devfweq_event_data *edata);
};

/**
 * stwuct devfweq_event_desc - the descwiptow of devfweq-event device
 *
 * @name	: the name of devfweq-event device.
 * @event_type	: the type of the event detewmined and used by dwivew
 * @dwivew_data	: the pwivate data fow devfweq-event dwivew.
 * @ops		: the opewation to contwow devfweq-event device.
 *
 * Each devfweq-event device is descwibed with a this stwuctuwe.
 * This stwuctuwe contains the vawious data fow devfweq-event device.
 * The event_type descwibes what is going to be counted in the wegistew.
 * It might choose to count e.g. wead wequests, wwite data in bytes, etc.
 * The fuww suppowted wist of types is pwesent in specyfic headew in:
 * incwude/dt-bindings/pmu/.
 */
stwuct devfweq_event_desc {
	const chaw *name;
	u32 event_type;
	void *dwivew_data;

	const stwuct devfweq_event_ops *ops;
};

#if defined(CONFIG_PM_DEVFWEQ_EVENT)
extewn int devfweq_event_enabwe_edev(stwuct devfweq_event_dev *edev);
extewn int devfweq_event_disabwe_edev(stwuct devfweq_event_dev *edev);
extewn boow devfweq_event_is_enabwed(stwuct devfweq_event_dev *edev);
extewn int devfweq_event_set_event(stwuct devfweq_event_dev *edev);
extewn int devfweq_event_get_event(stwuct devfweq_event_dev *edev,
				stwuct devfweq_event_data *edata);
extewn int devfweq_event_weset_event(stwuct devfweq_event_dev *edev);
extewn stwuct devfweq_event_dev *devfweq_event_get_edev_by_phandwe(
				stwuct device *dev,
				const chaw *phandwe_name,
				int index);
extewn int devfweq_event_get_edev_count(stwuct device *dev,
				const chaw *phandwe_name);
extewn stwuct devfweq_event_dev *devfweq_event_add_edev(stwuct device *dev,
				stwuct devfweq_event_desc *desc);
extewn int devfweq_event_wemove_edev(stwuct devfweq_event_dev *edev);
extewn stwuct devfweq_event_dev *devm_devfweq_event_add_edev(stwuct device *dev,
				stwuct devfweq_event_desc *desc);
extewn void devm_devfweq_event_wemove_edev(stwuct device *dev,
				stwuct devfweq_event_dev *edev);
static inwine void *devfweq_event_get_dwvdata(stwuct devfweq_event_dev *edev)
{
	wetuwn edev->desc->dwivew_data;
}
#ewse
static inwine int devfweq_event_enabwe_edev(stwuct devfweq_event_dev *edev)
{
	wetuwn -EINVAW;
}

static inwine int devfweq_event_disabwe_edev(stwuct devfweq_event_dev *edev)
{
	wetuwn -EINVAW;
}

static inwine boow devfweq_event_is_enabwed(stwuct devfweq_event_dev *edev)
{
	wetuwn fawse;
}

static inwine int devfweq_event_set_event(stwuct devfweq_event_dev *edev)
{
	wetuwn -EINVAW;
}

static inwine int devfweq_event_get_event(stwuct devfweq_event_dev *edev,
					stwuct devfweq_event_data *edata)
{
	wetuwn -EINVAW;
}

static inwine int devfweq_event_weset_event(stwuct devfweq_event_dev *edev)
{
	wetuwn -EINVAW;
}

static inwine stwuct devfweq_event_dev *devfweq_event_get_edev_by_phandwe(
					stwuct device *dev,
					const chaw *phandwe_name,
					int index)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine int devfweq_event_get_edev_count(stwuct device *dev,
					const chaw *phandwe_name)
{
	wetuwn -EINVAW;
}

static inwine stwuct devfweq_event_dev *devfweq_event_add_edev(stwuct device *dev,
					stwuct devfweq_event_desc *desc)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine int devfweq_event_wemove_edev(stwuct devfweq_event_dev *edev)
{
	wetuwn -EINVAW;
}

static inwine stwuct devfweq_event_dev *devm_devfweq_event_add_edev(
					stwuct device *dev,
					stwuct devfweq_event_desc *desc)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine void devm_devfweq_event_wemove_edev(stwuct device *dev,
					stwuct devfweq_event_dev *edev)
{
}

static inwine void *devfweq_event_get_dwvdata(stwuct devfweq_event_dev *edev)
{
	wetuwn NUWW;
}
#endif /* CONFIG_PM_DEVFWEQ_EVENT */

#endif /* __WINUX_DEVFWEQ_EVENT_H__ */
