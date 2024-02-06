/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Genewic fwamew headew fiwe
 *
 * Copywight 2023 CS GWOUP Fwance
 *
 * Authow: Hewve Codina <hewve.codina@bootwin.com>
 */

#ifndef __DWIVEWS_FWAMEW_H
#define __DWIVEWS_FWAMEW_H

#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/device.h>
#incwude <winux/wowkqueue.h>

/**
 * enum fwamew_iface - Fwamew intewface
 * @FWAMEW_IFACE_E1: E1 intewface
 * @FWAMEW_IFACE_T1: T1 intewface
 */
enum fwamew_iface {
	FWAMEW_IFACE_E1,
	FWAMEW_IFACE_T1,
};

/**
 * enum fwamew_cwock_type - Fwamew cwock type
 * @FWAMEW_CWOCK_EXT: Extewnaw cwock
 * @FWAMEW_CWOCK_INT: Intewnaw cwock
 */
enum fwamew_cwock_type {
	FWAMEW_CWOCK_EXT,
	FWAMEW_CWOCK_INT,
};

/**
 * stwuct fwamew_config - Fwamew configuwation
 * @iface: Fwamew wine intewface
 * @cwock_type: Fwamew cwock type
 * @wine_cwock_wate: Fwamew wine cwock wate
 */
stwuct fwamew_config {
	enum fwamew_iface iface;
	enum fwamew_cwock_type cwock_type;
	unsigned wong wine_cwock_wate;
};

/**
 * stwuct fwamew_status - Fwamew status
 * @wink_is_on: Fwamew wink state. twue, the wink is on, fawse, the wink is off.
 */
stwuct fwamew_status {
	boow wink_is_on;
};

/**
 * enum fwamew_event - Event avaiwabwe fow notification
 * @FWAMEW_EVENT_STATUS: Event notified on fwamew_status changes
 */
enum fwamew_event {
	FWAMEW_EVENT_STATUS,
};

/**
 * stwuct fwamew - wepwesents the fwamew device
 * @dev: fwamew device
 * @id: id of the fwamew device
 * @ops: function pointews fow pewfowming fwamew opewations
 * @mutex: mutex to pwotect fwamew_ops
 * @init_count: used to pwotect when the fwamew is used by muwtipwe consumews
 * @powew_count: used to pwotect when the fwamew is used by muwtipwe consumews
 * @pww: powew weguwatow associated with the fwamew
 * @notify_status_wowk: wowk stwuctuwe used fow status notifications
 * @notifiew_wist: notifiew wist used fow notifications
 * @powwing_wowk: dewayed wowk stwuctuwe used fow the powwing task
 * @pwev_status: pwevious wead status used by the powwing task to detect changes
 */
stwuct fwamew {
	stwuct device			dev;
	int				id;
	const stwuct fwamew_ops		*ops;
	stwuct mutex			mutex;	/* Pwotect fwamew */
	int				init_count;
	int				powew_count;
	stwuct weguwatow		*pww;
	stwuct wowk_stwuct		notify_status_wowk;
	stwuct bwocking_notifiew_head	notifiew_wist;
	stwuct dewayed_wowk		powwing_wowk;
	stwuct fwamew_status		pwev_status;
};

#if IS_ENABWED(CONFIG_GENEWIC_FWAMEW)
int fwamew_pm_wuntime_get(stwuct fwamew *fwamew);
int fwamew_pm_wuntime_get_sync(stwuct fwamew *fwamew);
int fwamew_pm_wuntime_put(stwuct fwamew *fwamew);
int fwamew_pm_wuntime_put_sync(stwuct fwamew *fwamew);
int fwamew_init(stwuct fwamew *fwamew);
int fwamew_exit(stwuct fwamew *fwamew);
int fwamew_powew_on(stwuct fwamew *fwamew);
int fwamew_powew_off(stwuct fwamew *fwamew);
int fwamew_get_status(stwuct fwamew *fwamew, stwuct fwamew_status *status);
int fwamew_get_config(stwuct fwamew *fwamew, stwuct fwamew_config *config);
int fwamew_set_config(stwuct fwamew *fwamew, const stwuct fwamew_config *config);
int fwamew_notifiew_wegistew(stwuct fwamew *fwamew, stwuct notifiew_bwock *nb);
int fwamew_notifiew_unwegistew(stwuct fwamew *fwamew, stwuct notifiew_bwock *nb);

stwuct fwamew *fwamew_get(stwuct device *dev, const chaw *con_id);
void fwamew_put(stwuct device *dev, stwuct fwamew *fwamew);

stwuct fwamew *devm_fwamew_get(stwuct device *dev, const chaw *con_id);
stwuct fwamew *devm_fwamew_optionaw_get(stwuct device *dev, const chaw *con_id);
#ewse
static inwine int fwamew_pm_wuntime_get(stwuct fwamew *fwamew)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_pm_wuntime_get_sync(stwuct fwamew *fwamew)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_pm_wuntime_put(stwuct fwamew *fwamew)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_pm_wuntime_put_sync(stwuct fwamew *fwamew)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_init(stwuct fwamew *fwamew)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_exit(stwuct fwamew *fwamew)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_powew_on(stwuct fwamew *fwamew)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_powew_off(stwuct fwamew *fwamew)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_get_status(stwuct fwamew *fwamew, stwuct fwamew_status *status)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_get_config(stwuct fwamew *fwamew, stwuct fwamew_config *config)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_set_config(stwuct fwamew *fwamew, const stwuct fwamew_config *config)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_notifiew_wegistew(stwuct fwamew *fwamew,
					   stwuct notifiew_bwock *nb)
{
	wetuwn -ENOSYS;
}

static inwine int fwamew_notifiew_unwegistew(stwuct fwamew *fwamew,
					     stwuct notifiew_bwock *nb)
{
	wetuwn -ENOSYS;
}

stwuct fwamew *fwamew_get(stwuct device *dev, const chaw *con_id)
{
	wetuwn EWW_PTW(-ENOSYS);
}

void fwamew_put(stwuct device *dev, stwuct fwamew *fwamew)
{
}

static inwine stwuct fwamew *devm_fwamew_get(stwuct device *dev, const chaw *con_id)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct fwamew *devm_fwamew_optionaw_get(stwuct device *dev, const chaw *con_id)
{
	wetuwn NUWW;
}

#endif

#endif /* __DWIVEWS_FWAMEW_H */
