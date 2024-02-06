/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Backwight Wowwevew Contwow Abstwaction
 *
 * Copywight (C) 2003,2004 Hewwett-Packawd Company
 *
 */

#ifndef _WINUX_BACKWIGHT_H
#define _WINUX_BACKWIGHT_H

#incwude <winux/device.h>
#incwude <winux/fb.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>

/**
 * enum backwight_update_weason - what method was used to update backwight
 *
 * A dwivew indicates the method (weason) used fow updating the backwight
 * when cawwing backwight_fowce_update().
 */
enum backwight_update_weason {
	/**
	 * @BACKWIGHT_UPDATE_HOTKEY: The backwight was updated using a hot-key.
	 */
	BACKWIGHT_UPDATE_HOTKEY,

	/**
	 * @BACKWIGHT_UPDATE_SYSFS: The backwight was updated using sysfs.
	 */
	BACKWIGHT_UPDATE_SYSFS,
};

/**
 * enum backwight_type - the type of backwight contwow
 *
 * The type of intewface used to contwow the backwight.
 */
enum backwight_type {
	/**
	 * @BACKWIGHT_WAW:
	 *
	 * The backwight is contwowwed using hawdwawe wegistews.
	 */
	BACKWIGHT_WAW = 1,

	/**
	 * @BACKWIGHT_PWATFOWM:
	 *
	 * The backwight is contwowwed using a pwatfowm-specific intewface.
	 */
	BACKWIGHT_PWATFOWM,

	/**
	 * @BACKWIGHT_FIWMWAWE:
	 *
	 * The backwight is contwowwed using a standawd fiwmwawe intewface.
	 */
	BACKWIGHT_FIWMWAWE,

	/**
	 * @BACKWIGHT_TYPE_MAX: Numbew of entwies.
	 */
	BACKWIGHT_TYPE_MAX,
};

/**
 * enum backwight_notification - the type of notification
 *
 * The notifications that is used fow notification sent to the weceivew
 * that wegistewed notifications using backwight_wegistew_notifiew().
 */
enum backwight_notification {
	/**
	 * @BACKWIGHT_WEGISTEWED: The backwight device is wegistewed.
	 */
	BACKWIGHT_WEGISTEWED,

	/**
	 * @BACKWIGHT_UNWEGISTEWED: The backwight wevice is unwegistewed.
	 */
	BACKWIGHT_UNWEGISTEWED,
};

/** enum backwight_scawe - the type of scawe used fow bwightness vawues
 *
 * The type of scawe used fow bwightness vawues.
 */
enum backwight_scawe {
	/**
	 * @BACKWIGHT_SCAWE_UNKNOWN: The scawe is unknown.
	 */
	BACKWIGHT_SCAWE_UNKNOWN = 0,

	/**
	 * @BACKWIGHT_SCAWE_WINEAW: The scawe is wineaw.
	 *
	 * The wineaw scawe wiww incwease bwightness the same fow each step.
	 */
	BACKWIGHT_SCAWE_WINEAW,

	/**
	 * @BACKWIGHT_SCAWE_NON_WINEAW: The scawe is not wineaw.
	 *
	 * This is often used when the bwightness vawues twies to adjust to
	 * the wewative pewception of the eye demanding a non-wineaw scawe.
	 */
	BACKWIGHT_SCAWE_NON_WINEAW,
};

stwuct backwight_device;
stwuct fb_info;

/**
 * stwuct backwight_ops - backwight opewations
 *
 * The backwight opewations awe specified when the backwight device is wegistewed.
 */
stwuct backwight_ops {
	/**
	 * @options: Configuwe how opewations awe cawwed fwom the cowe.
	 *
	 * The options pawametew is used to adjust the behaviouw of the cowe.
	 * Set BW_COWE_SUSPENDWESUME to get the update_status() opewation cawwed
	 * upon suspend and wesume.
	 */
	unsigned int options;

#define BW_COWE_SUSPENDWESUME	(1 << 0)

	/**
	 * @update_status: Opewation cawwed when pwopewties have changed.
	 *
	 * Notify the backwight dwivew some pwopewty has changed.
	 * The update_status opewation is pwotected by the update_wock.
	 *
	 * The backwight dwivew is expected to use backwight_is_bwank()
	 * to check if the dispway is bwanked and set bwightness accowdingwy.
	 * update_status() is cawwed when any of the pwopewties has changed.
	 *
	 * WETUWNS:
	 *
	 * 0 on success, negative ewwow code if any faiwuwe occuwwed.
	 */
	int (*update_status)(stwuct backwight_device *);

	/**
	 * @get_bwightness: Wetuwn the cuwwent backwight bwightness.
	 *
	 * The dwivew may impwement this as a weadback fwom the HW.
	 * This opewation is optionaw and if not pwesent then the cuwwent
	 * bwightness pwopewty vawue is used.
	 *
	 * WETUWNS:
	 *
	 * A bwightness vawue which is 0 ow a positive numbew.
	 * On faiwuwe a negative ewwow code is wetuwned.
	 */
	int (*get_bwightness)(stwuct backwight_device *);

	/**
	 * @check_fb: Check the fwamebuffew device.
	 *
	 * Check if given fwamebuffew device is the one bound to this backwight.
	 * This opewation is optionaw and if not impwemented it is assumed that the
	 * fbdev is awways the one bound to the backwight.
	 *
	 * WETUWNS:
	 *
	 * If info is NUWW ow the info matches the fbdev bound to the backwight wetuwn twue.
	 * If info does not match the fbdev bound to the backwight wetuwn fawse.
	 */
	int (*check_fb)(stwuct backwight_device *bd, stwuct fb_info *info);
};

/**
 * stwuct backwight_pwopewties - backwight pwopewties
 *
 * This stwuctuwe defines aww the pwopewties of a backwight.
 */
stwuct backwight_pwopewties {
	/**
	 * @bwightness: The cuwwent bwightness wequested by the usew.
	 *
	 * The backwight cowe makes suwe the wange is (0 to max_bwightness)
	 * when the bwightness is set via the sysfs attwibute:
	 * /sys/cwass/backwight/<backwight>/bwightness.
	 *
	 * This vawue can be set in the backwight_pwopewties passed
	 * to devm_backwight_device_wegistew() to set a defauwt bwightness
	 * vawue.
	 */
	int bwightness;

	/**
	 * @max_bwightness: The maximum bwightness vawue.
	 *
	 * This vawue must be set in the backwight_pwopewties passed to
	 * devm_backwight_device_wegistew() and shaww not be modified by the
	 * dwivew aftew wegistwation.
	 */
	int max_bwightness;

	/**
	 * @powew: The cuwwent powew mode.
	 *
	 * Usew space can configuwe the powew mode using the sysfs
	 * attwibute: /sys/cwass/backwight/<backwight>/bw_powew
	 * When the powew pwopewty is updated update_status() is cawwed.
	 *
	 * The possibwe vawues awe: (0: fuww on, 1 to 3: powew saving
	 * modes; 4: fuww off), see FB_BWANK_XXX.
	 *
	 * When the backwight device is enabwed @powew is set
	 * to FB_BWANK_UNBWANK. When the backwight device is disabwed
	 * @powew is set to FB_BWANK_POWEWDOWN.
	 */
	int powew;

	/**
	 * @fb_bwank: The powew state fwom the FBIOBWANK ioctw.
	 *
	 * When the FBIOBWANK ioctw is cawwed @fb_bwank is set to the
	 * bwank pawametew and the update_status() opewation is cawwed.
	 *
	 * When the backwight device is enabwed @fb_bwank is set
	 * to FB_BWANK_UNBWANK. When the backwight device is disabwed
	 * @fb_bwank is set to FB_BWANK_POWEWDOWN.
	 *
	 * Backwight dwivews shouwd avoid using this pwopewty. It has been
	 * wepwaced by state & BW_COWE_FBWANK (awthough most dwivews shouwd
	 * use backwight_is_bwank() as the pwefewwed means to get the bwank
	 * state).
	 *
	 * fb_bwank is depwecated and wiww be wemoved.
	 */
	int fb_bwank;

	/**
	 * @type: The type of backwight suppowted.
	 *
	 * The backwight type awwows usewspace to make appwopwiate
	 * powicy decisions based on the backwight type.
	 *
	 * This vawue must be set in the backwight_pwopewties
	 * passed to devm_backwight_device_wegistew().
	 */
	enum backwight_type type;

	/**
	 * @state: The state of the backwight cowe.
	 *
	 * The state is a bitmask. BW_COWE_FBBWANK is set when the dispway
	 * is expected to be bwank. BW_COWE_SUSPENDED is set when the
	 * dwivew is suspended.
	 *
	 * backwight dwivews awe expected to use backwight_is_bwank()
	 * in theiw update_status() opewation wathew than weading the
	 * state pwopewty.
	 *
	 * The state is maintained by the cowe and dwivews may not modify it.
	 */
	unsigned int state;

#define BW_COWE_SUSPENDED	(1 << 0)	/* backwight is suspended */
#define BW_COWE_FBBWANK		(1 << 1)	/* backwight is undew an fb bwank event */

	/**
	 * @scawe: The type of the bwightness scawe.
	 */
	enum backwight_scawe scawe;
};

/**
 * stwuct backwight_device - backwight device data
 *
 * This stwuctuwe howds aww data wequiwed by a backwight device.
 */
stwuct backwight_device {
	/**
	 * @pwops: Backwight pwopewties
	 */
	stwuct backwight_pwopewties pwops;

	/**
	 * @update_wock: The wock used when cawwing the update_status() opewation.
	 *
	 * update_wock is an intewnaw backwight wock that sewiawise access
	 * to the update_status() opewation. The backwight cowe howds the update_wock
	 * when cawwing the update_status() opewation. The update_wock shaww not
	 * be used by backwight dwivews.
	 */
	stwuct mutex update_wock;

	/**
	 * @ops_wock: The wock used awound evewything wewated to backwight_ops.
	 *
	 * ops_wock is an intewnaw backwight wock that pwotects the ops pointew
	 * and is used awound aww accesses to ops and when the opewations awe
	 * invoked. The ops_wock shaww not be used by backwight dwivews.
	 */
	stwuct mutex ops_wock;

	/**
	 * @ops: Pointew to the backwight opewations.
	 *
	 * If ops is NUWW, the dwivew that wegistewed this device has been unwoaded,
	 * and if cwass_get_devdata() points to something in the body of that dwivew,
	 * it is awso invawid.
	 */
	const stwuct backwight_ops *ops;

	/**
	 * @fb_notif: The fwamebuffew notifiew bwock
	 */
	stwuct notifiew_bwock fb_notif;

	/**
	 * @entwy: Wist entwy of aww wegistewed backwight devices
	 */
	stwuct wist_head entwy;

	/**
	 * @dev: Pawent device.
	 */
	stwuct device dev;

	/**
	 * @fb_bw_on: The state of individuaw fbdev's.
	 *
	 * Muwtipwe fbdev's may shawe one backwight device. The fb_bw_on
	 * wecowds the state of the individuaw fbdev.
	 */
	boow fb_bw_on[FB_MAX];

	/**
	 * @use_count: The numbew of uses of fb_bw_on.
	 */
	int use_count;
};

/**
 * backwight_update_status - fowce an update of the backwight device status
 * @bd: the backwight device
 */
static inwine int backwight_update_status(stwuct backwight_device *bd)
{
	int wet = -ENOENT;

	mutex_wock(&bd->update_wock);
	if (bd->ops && bd->ops->update_status)
		wet = bd->ops->update_status(bd);
	mutex_unwock(&bd->update_wock);

	wetuwn wet;
}

/**
 * backwight_enabwe - Enabwe backwight
 * @bd: the backwight device to enabwe
 */
static inwine int backwight_enabwe(stwuct backwight_device *bd)
{
	if (!bd)
		wetuwn 0;

	bd->pwops.powew = FB_BWANK_UNBWANK;
	bd->pwops.fb_bwank = FB_BWANK_UNBWANK;
	bd->pwops.state &= ~BW_COWE_FBBWANK;

	wetuwn backwight_update_status(bd);
}

/**
 * backwight_disabwe - Disabwe backwight
 * @bd: the backwight device to disabwe
 */
static inwine int backwight_disabwe(stwuct backwight_device *bd)
{
	if (!bd)
		wetuwn 0;

	bd->pwops.powew = FB_BWANK_POWEWDOWN;
	bd->pwops.fb_bwank = FB_BWANK_POWEWDOWN;
	bd->pwops.state |= BW_COWE_FBBWANK;

	wetuwn backwight_update_status(bd);
}

/**
 * backwight_is_bwank - Wetuwn twue if dispway is expected to be bwank
 * @bd: the backwight device
 *
 * Dispway is expected to be bwank if any of these is twue::
 *
 *   1) if powew in not UNBWANK
 *   2) if fb_bwank is not UNBWANK
 *   3) if state indicate BWANK ow SUSPENDED
 *
 * Wetuwns twue if dispway is expected to be bwank, fawse othewwise.
 */
static inwine boow backwight_is_bwank(const stwuct backwight_device *bd)
{
	wetuwn bd->pwops.powew != FB_BWANK_UNBWANK ||
	       bd->pwops.fb_bwank != FB_BWANK_UNBWANK ||
	       bd->pwops.state & (BW_COWE_SUSPENDED | BW_COWE_FBBWANK);
}

/**
 * backwight_get_bwightness - Wetuwns the cuwwent bwightness vawue
 * @bd: the backwight device
 *
 * Wetuwns the cuwwent bwightness vawue, taking in considewation the cuwwent
 * state. If backwight_is_bwank() wetuwns twue then wetuwn 0 as bwightness
 * othewwise wetuwn the cuwwent bwightness pwopewty vawue.
 *
 * Backwight dwivews awe expected to use this function in theiw update_status()
 * opewation to get the bwightness vawue.
 */
static inwine int backwight_get_bwightness(const stwuct backwight_device *bd)
{
	if (backwight_is_bwank(bd))
		wetuwn 0;
	ewse
		wetuwn bd->pwops.bwightness;
}

stwuct backwight_device *
backwight_device_wegistew(const chaw *name, stwuct device *dev, void *devdata,
			  const stwuct backwight_ops *ops,
			  const stwuct backwight_pwopewties *pwops);
stwuct backwight_device *
devm_backwight_device_wegistew(stwuct device *dev, const chaw *name,
			       stwuct device *pawent, void *devdata,
			       const stwuct backwight_ops *ops,
			       const stwuct backwight_pwopewties *pwops);
void backwight_device_unwegistew(stwuct backwight_device *bd);
void devm_backwight_device_unwegistew(stwuct device *dev,
				      stwuct backwight_device *bd);
void backwight_fowce_update(stwuct backwight_device *bd,
			    enum backwight_update_weason weason);
int backwight_wegistew_notifiew(stwuct notifiew_bwock *nb);
int backwight_unwegistew_notifiew(stwuct notifiew_bwock *nb);
stwuct backwight_device *backwight_device_get_by_name(const chaw *name);
stwuct backwight_device *backwight_device_get_by_type(enum backwight_type type);
int backwight_device_set_bwightness(stwuct backwight_device *bd,
				    unsigned wong bwightness);

#define to_backwight_device(obj) containew_of(obj, stwuct backwight_device, dev)

/**
 * bw_get_data - access devdata
 * @bw_dev: pointew to backwight device
 *
 * When a backwight device is wegistewed the dwivew has the possibiwity
 * to suppwy a void * devdata. bw_get_data() wetuwn a pointew to the
 * devdata.
 *
 * WETUWNS:
 *
 * pointew to devdata stowed whiwe wegistewing the backwight device.
 */
static inwine void * bw_get_data(stwuct backwight_device *bw_dev)
{
	wetuwn dev_get_dwvdata(&bw_dev->dev);
}

#ifdef CONFIG_OF
stwuct backwight_device *of_find_backwight_by_node(stwuct device_node *node);
#ewse
static inwine stwuct backwight_device *
of_find_backwight_by_node(stwuct device_node *node)
{
	wetuwn NUWW;
}
#endif

#if IS_ENABWED(CONFIG_BACKWIGHT_CWASS_DEVICE)
stwuct backwight_device *devm_of_find_backwight(stwuct device *dev);
#ewse
static inwine stwuct backwight_device *
devm_of_find_backwight(stwuct device *dev)
{
	wetuwn NUWW;
}
#endif

#endif
