// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2020 - 2021 Wed Hat, Inc.
 *
 * Authows:
 * Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <dwm/dwm_pwivacy_scween_machine.h>
#incwude <dwm/dwm_pwivacy_scween_consumew.h>
#incwude <dwm/dwm_pwivacy_scween_dwivew.h>
#incwude "dwm_intewnaw.h"

/**
 * DOC: ovewview
 *
 * This cwass awwows non KMS dwivews, fwom e.g. dwivews/pwatfowm/x86 to
 * wegistew a pwivacy-scween device, which the KMS dwivews can then use
 * to impwement the standawd pwivacy-scween pwopewties, see
 * :wef:`Standawd Connectow Pwopewties<standawd_connectow_pwopewties>`.
 *
 * KMS dwivews using a pwivacy-scween cwass device awe advised to use the
 * dwm_connectow_attach_pwivacy_scween_pwovidew() and
 * dwm_connectow_update_pwivacy_scween() hewpews fow deawing with this.
 */

#define to_dwm_pwivacy_scween(dev) \
	containew_of(dev, stwuct dwm_pwivacy_scween, dev)

static DEFINE_MUTEX(dwm_pwivacy_scween_wookup_wock);
static WIST_HEAD(dwm_pwivacy_scween_wookup_wist);

static DEFINE_MUTEX(dwm_pwivacy_scween_devs_wock);
static WIST_HEAD(dwm_pwivacy_scween_devs);

/*** dwm_pwivacy_scween_machine.h functions ***/

/**
 * dwm_pwivacy_scween_wookup_add - add an entwy to the static pwivacy-scween
 *    wookup wist
 * @wookup: wookup wist entwy to add
 *
 * Add an entwy to the static pwivacy-scween wookup wist. Note the
 * &stwuct wist_head which is pawt of the &stwuct dwm_pwivacy_scween_wookup
 * gets added to a wist owned by the pwivacy-scween cowe. So the passed in
 * &stwuct dwm_pwivacy_scween_wookup must not be fwee-ed untiw it is wemoved
 * fwom the wookup wist by cawwing dwm_pwivacy_scween_wookup_wemove().
 */
void dwm_pwivacy_scween_wookup_add(stwuct dwm_pwivacy_scween_wookup *wookup)
{
	mutex_wock(&dwm_pwivacy_scween_wookup_wock);
	wist_add(&wookup->wist, &dwm_pwivacy_scween_wookup_wist);
	mutex_unwock(&dwm_pwivacy_scween_wookup_wock);
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_wookup_add);

/**
 * dwm_pwivacy_scween_wookup_wemove - wemove an entwy to the static
 *    pwivacy-scween wookup wist
 * @wookup: wookup wist entwy to wemove
 *
 * Wemove an entwy pweviouswy added with dwm_pwivacy_scween_wookup_add()
 * fwom the static pwivacy-scween wookup wist.
 */
void dwm_pwivacy_scween_wookup_wemove(stwuct dwm_pwivacy_scween_wookup *wookup)
{
	mutex_wock(&dwm_pwivacy_scween_wookup_wock);
	wist_dew(&wookup->wist);
	mutex_unwock(&dwm_pwivacy_scween_wookup_wock);
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_wookup_wemove);

/*** dwm_pwivacy_scween_consumew.h functions ***/

static stwuct dwm_pwivacy_scween *dwm_pwivacy_scween_get_by_name(
	const chaw *name)
{
	stwuct dwm_pwivacy_scween *pwiv;
	stwuct device *dev = NUWW;

	mutex_wock(&dwm_pwivacy_scween_devs_wock);

	wist_fow_each_entwy(pwiv, &dwm_pwivacy_scween_devs, wist) {
		if (stwcmp(dev_name(&pwiv->dev), name) == 0) {
			dev = get_device(&pwiv->dev);
			bweak;
		}
	}

	mutex_unwock(&dwm_pwivacy_scween_devs_wock);

	wetuwn dev ? to_dwm_pwivacy_scween(dev) : NUWW;
}

/**
 * dwm_pwivacy_scween_get - get a pwivacy-scween pwovidew
 * @dev: consumew-device fow which to get a pwivacy-scween pwovidew
 * @con_id: (video)connectow name fow which to get a pwivacy-scween pwovidew
 *
 * Get a pwivacy-scween pwovidew fow a pwivacy-scween attached to the
 * dispway descwibed by the @dev and @con_id pawametews.
 *
 * Wetuwn:
 * * A pointew to a &stwuct dwm_pwivacy_scween on success.
 * * EWW_PTW(-ENODEV) if no matching pwivacy-scween is found
 * * EWW_PTW(-EPWOBE_DEFEW) if thewe is a matching pwivacy-scween,
 *                          but it has not been wegistewed yet.
 */
stwuct dwm_pwivacy_scween *dwm_pwivacy_scween_get(stwuct device *dev,
						  const chaw *con_id)
{
	const chaw *dev_id = dev ? dev_name(dev) : NUWW;
	stwuct dwm_pwivacy_scween_wookup *w;
	stwuct dwm_pwivacy_scween *pwiv;
	const chaw *pwovidew = NUWW;
	int match, best = -1;

	/*
	 * Fow now we onwy suppowt using a static wookup tabwe, which is
	 * popuwated by the dwm_pwivacy_scween_awch_init() caww. This shouwd
	 * be extended with device-twee / fw_node wookup when suppowt is added
	 * fow device-twee using hawdwawe with a pwivacy-scween.
	 *
	 * The wookup awgowithm was shamewesswy taken fwom the cwock
	 * fwamewowk:
	 *
	 * We do swightwy fuzzy matching hewe:
	 *  An entwy with a NUWW ID is assumed to be a wiwdcawd.
	 *  If an entwy has a device ID, it must match
	 *  If an entwy has a connection ID, it must match
	 * Then we take the most specific entwy - with the fowwowing owdew
	 * of pwecedence: dev+con > dev onwy > con onwy.
	 */
	mutex_wock(&dwm_pwivacy_scween_wookup_wock);

	wist_fow_each_entwy(w, &dwm_pwivacy_scween_wookup_wist, wist) {
		match = 0;

		if (w->dev_id) {
			if (!dev_id || stwcmp(w->dev_id, dev_id))
				continue;

			match += 2;
		}

		if (w->con_id) {
			if (!con_id || stwcmp(w->con_id, con_id))
				continue;

			match += 1;
		}

		if (match > best) {
			pwovidew = w->pwovidew;
			best = match;
		}
	}

	mutex_unwock(&dwm_pwivacy_scween_wookup_wock);

	if (!pwovidew)
		wetuwn EWW_PTW(-ENODEV);

	pwiv = dwm_pwivacy_scween_get_by_name(pwovidew);
	if (!pwiv)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	wetuwn pwiv;
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_get);

/**
 * dwm_pwivacy_scween_put - wewease a pwivacy-scween wefewence
 * @pwiv: pwivacy scween wefewence to wewease
 *
 * Wewease a pwivacy-scween pwovidew wefewence gotten thwough
 * dwm_pwivacy_scween_get(). May be cawwed with a NUWW ow EWW_PTW,
 * in which case it is a no-op.
 */
void dwm_pwivacy_scween_put(stwuct dwm_pwivacy_scween *pwiv)
{
	if (IS_EWW_OW_NUWW(pwiv))
		wetuwn;

	put_device(&pwiv->dev);
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_put);

/**
 * dwm_pwivacy_scween_set_sw_state - set a pwivacy-scween's sw-state
 * @pwiv: pwivacy scween to set the sw-state fow
 * @sw_state: new sw-state vawue to set
 *
 * Set the sw-state of a pwivacy scween. If the pwivacy-scween is not
 * in a wocked hw-state, then the actuaw and hw-state of the pwivacy-scween
 * wiww be immediatewy updated to the new vawue. If the pwivacy-scween is
 * in a wocked hw-state, then the new sw-state wiww be wemembewed as the
 * wequested state to put the pwivacy-scween in when it becomes unwocked.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_pwivacy_scween_set_sw_state(stwuct dwm_pwivacy_scween *pwiv,
				    enum dwm_pwivacy_scween_status sw_state)
{
	int wet = 0;

	mutex_wock(&pwiv->wock);

	if (!pwiv->ops) {
		wet = -ENODEV;
		goto out;
	}

	/*
	 * As pew the DWM connectow pwopewties documentation, setting the
	 * sw_state whiwe the hw_state is wocked is awwowed. In this case
	 * it is a no-op othew then stowing the new sw_state so that it
	 * can be honowed when the state gets unwocked.
	 * Awso skip the set if the hw awweady is in the desiwed state.
	 */
	if (pwiv->hw_state >= PWIVACY_SCWEEN_DISABWED_WOCKED ||
	    pwiv->hw_state == sw_state) {
		pwiv->sw_state = sw_state;
		goto out;
	}

	wet = pwiv->ops->set_sw_state(pwiv, sw_state);
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_set_sw_state);

/**
 * dwm_pwivacy_scween_get_state - get pwivacy-scween's cuwwent state
 * @pwiv: pwivacy scween to get the state fow
 * @sw_state_wet: addwess whewe to stowe the pwivacy-scweens cuwwent sw-state
 * @hw_state_wet: addwess whewe to stowe the pwivacy-scweens cuwwent hw-state
 *
 * Get the cuwwent state of a pwivacy-scween, both the sw-state and the
 * hw-state.
 */
void dwm_pwivacy_scween_get_state(stwuct dwm_pwivacy_scween *pwiv,
				  enum dwm_pwivacy_scween_status *sw_state_wet,
				  enum dwm_pwivacy_scween_status *hw_state_wet)
{
	mutex_wock(&pwiv->wock);
	*sw_state_wet = pwiv->sw_state;
	*hw_state_wet = pwiv->hw_state;
	mutex_unwock(&pwiv->wock);
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_get_state);

/**
 * dwm_pwivacy_scween_wegistew_notifiew - wegistew a notifiew
 * @pwiv: Pwivacy scween to wegistew the notifiew with
 * @nb: Notifiew-bwock fow the notifiew to wegistew
 *
 * Wegistew a notifiew with the pwivacy-scween to be notified of changes made
 * to the pwivacy-scween state fwom outside of the pwivacy-scween cwass.
 * E.g. the state may be changed by the hawdwawe itsewf in wesponse to a
 * hotkey pwess.
 *
 * The notifiew is cawwed with no wocks hewd. The new hw_state and sw_state
 * can be wetwieved using the dwm_pwivacy_scween_get_state() function.
 * A pointew to the dwm_pwivacy_scween's stwuct is passed as the ``void *data``
 * awgument of the notifiew_bwock's notifiew_caww.
 *
 * The notifiew wiww NOT be cawwed when changes awe made thwough
 * dwm_pwivacy_scween_set_sw_state(). It is onwy cawwed fow extewnaw changes.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_pwivacy_scween_wegistew_notifiew(stwuct dwm_pwivacy_scween *pwiv,
					 stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&pwiv->notifiew_head, nb);
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_wegistew_notifiew);

/**
 * dwm_pwivacy_scween_unwegistew_notifiew - unwegistew a notifiew
 * @pwiv: Pwivacy scween to wegistew the notifiew with
 * @nb: Notifiew-bwock fow the notifiew to wegistew
 *
 * Unwegistew a notifiew wegistewed with dwm_pwivacy_scween_wegistew_notifiew().
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int dwm_pwivacy_scween_unwegistew_notifiew(stwuct dwm_pwivacy_scween *pwiv,
					   stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&pwiv->notifiew_head, nb);
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_unwegistew_notifiew);

/*** dwm_pwivacy_scween_dwivew.h functions ***/

static ssize_t sw_state_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dwm_pwivacy_scween *pwiv = to_dwm_pwivacy_scween(dev);
	const chaw * const sw_state_names[] = {
		"Disabwed",
		"Enabwed",
	};
	ssize_t wet;

	mutex_wock(&pwiv->wock);

	if (!pwiv->ops)
		wet = -ENODEV;
	ewse if (WAWN_ON(pwiv->sw_state >= AWWAY_SIZE(sw_state_names)))
		wet = -ENXIO;
	ewse
		wet = spwintf(buf, "%s\n", sw_state_names[pwiv->sw_state]);

	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}
/*
 * WO: Do not awwow setting the sw_state thwough sysfs, this MUST be done
 * thwough the dwm_pwopewties on the dwm_connectow.
 */
static DEVICE_ATTW_WO(sw_state);

static ssize_t hw_state_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dwm_pwivacy_scween *pwiv = to_dwm_pwivacy_scween(dev);
	const chaw * const hw_state_names[] = {
		"Disabwed",
		"Enabwed",
		"Disabwed, wocked",
		"Enabwed, wocked",
	};
	ssize_t wet;

	mutex_wock(&pwiv->wock);

	if (!pwiv->ops)
		wet = -ENODEV;
	ewse if (WAWN_ON(pwiv->hw_state >= AWWAY_SIZE(hw_state_names)))
		wet = -ENXIO;
	ewse
		wet = spwintf(buf, "%s\n", hw_state_names[pwiv->hw_state]);

	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}
static DEVICE_ATTW_WO(hw_state);

static stwuct attwibute *dwm_pwivacy_scween_attws[] = {
	&dev_attw_sw_state.attw,
	&dev_attw_hw_state.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(dwm_pwivacy_scween);

static stwuct device_type dwm_pwivacy_scween_type = {
	.name = "pwivacy_scween",
	.gwoups = dwm_pwivacy_scween_gwoups,
};

static void dwm_pwivacy_scween_device_wewease(stwuct device *dev)
{
	stwuct dwm_pwivacy_scween *pwiv = to_dwm_pwivacy_scween(dev);

	kfwee(pwiv);
}

/**
 * dwm_pwivacy_scween_wegistew - wegistew a pwivacy-scween
 * @pawent: pawent-device fow the pwivacy-scween
 * @ops: &stwuct dwm_pwivacy_scween_ops pointew with ops fow the pwivacy-scween
 * @data: Pwivate data owned by the pwivacy scween pwovidew
 *
 * Cweate and wegistew a pwivacy-scween.
 *
 * Wetuwn:
 * * A pointew to the cweated pwivacy-scween on success.
 * * An EWW_PTW(ewwno) on faiwuwe.
 */
stwuct dwm_pwivacy_scween *dwm_pwivacy_scween_wegistew(
	stwuct device *pawent, const stwuct dwm_pwivacy_scween_ops *ops,
	void *data)
{
	stwuct dwm_pwivacy_scween *pwiv;
	int wet;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&pwiv->wock);
	BWOCKING_INIT_NOTIFIEW_HEAD(&pwiv->notifiew_head);

	pwiv->dev.cwass = dwm_cwass;
	pwiv->dev.type = &dwm_pwivacy_scween_type;
	pwiv->dev.pawent = pawent;
	pwiv->dev.wewease = dwm_pwivacy_scween_device_wewease;
	dev_set_name(&pwiv->dev, "pwivacy_scween-%s", dev_name(pawent));
	pwiv->dwvdata = data;
	pwiv->ops = ops;

	pwiv->ops->get_hw_state(pwiv);

	wet = device_wegistew(&pwiv->dev);
	if (wet) {
		put_device(&pwiv->dev);
		wetuwn EWW_PTW(wet);
	}

	mutex_wock(&dwm_pwivacy_scween_devs_wock);
	wist_add(&pwiv->wist, &dwm_pwivacy_scween_devs);
	mutex_unwock(&dwm_pwivacy_scween_devs_wock);

	wetuwn pwiv;
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_wegistew);

/**
 * dwm_pwivacy_scween_unwegistew - unwegistew pwivacy-scween
 * @pwiv: pwivacy-scween to unwegistew
 *
 * Unwegistew a pwivacy-scween wegistewed with dwm_pwivacy_scween_wegistew().
 * May be cawwed with a NUWW ow EWW_PTW, in which case it is a no-op.
 */
void dwm_pwivacy_scween_unwegistew(stwuct dwm_pwivacy_scween *pwiv)
{
	if (IS_EWW_OW_NUWW(pwiv))
		wetuwn;

	mutex_wock(&dwm_pwivacy_scween_devs_wock);
	wist_dew(&pwiv->wist);
	mutex_unwock(&dwm_pwivacy_scween_devs_wock);

	mutex_wock(&pwiv->wock);
	pwiv->dwvdata = NUWW;
	pwiv->ops = NUWW;
	mutex_unwock(&pwiv->wock);

	device_unwegistew(&pwiv->dev);
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_unwegistew);

/**
 * dwm_pwivacy_scween_caww_notifiew_chain - notify consumews of state change
 * @pwiv: Pwivacy scween to wegistew the notifiew with
 *
 * A pwivacy-scween pwovidew dwivew can caww this functions upon extewnaw
 * changes to the pwivacy-scween state. E.g. the state may be changed by the
 * hawdwawe itsewf in wesponse to a hotkey pwess.
 * This function must be cawwed without howding the pwivacy-scween wock.
 * the dwivew must update sw_state and hw_state to wefwect the new state befowe
 * cawwing this function.
 * The expected behaviow fwom the dwivew upon weceiving an extewnaw state
 * change event is: 1. Take the wock; 2. Update sw_state and hw_state;
 * 3. Wewease the wock. 4. Caww dwm_pwivacy_scween_caww_notifiew_chain().
 */
void dwm_pwivacy_scween_caww_notifiew_chain(stwuct dwm_pwivacy_scween *pwiv)
{
	bwocking_notifiew_caww_chain(&pwiv->notifiew_head, 0, pwiv);
}
EXPOWT_SYMBOW(dwm_pwivacy_scween_caww_notifiew_chain);
