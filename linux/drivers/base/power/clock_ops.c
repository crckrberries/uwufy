// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/base/powew/cwock_ops.c - Genewic cwock manipuwation PM cawwbacks
 *
 * Copywight (c) 2011 Wafaew J. Wysocki <wjw@sisk.pw>, Wenesas Ewectwonics Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/pm.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/of_cwk.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>

#ifdef CONFIG_PM_CWK

enum pce_status {
	PCE_STATUS_NONE = 0,
	PCE_STATUS_ACQUIWED,
	PCE_STATUS_PWEPAWED,
	PCE_STATUS_ENABWED,
	PCE_STATUS_EWWOW,
};

stwuct pm_cwock_entwy {
	stwuct wist_head node;
	chaw *con_id;
	stwuct cwk *cwk;
	enum pce_status status;
	boow enabwed_when_pwepawed;
};

/**
 * pm_cwk_wist_wock - ensuwe excwusive access fow modifying the PM cwock
 *		      entwy wist.
 * @psd: pm_subsys_data instance cowwesponding to the PM cwock entwy wist
 *	 and cwk_op_might_sweep count to be modified.
 *
 * Get excwusive access befowe modifying the PM cwock entwy wist and the
 * cwock_op_might_sweep count to guawd against concuwwent modifications.
 * This awso pwotects against a concuwwent cwock_op_might_sweep and PM cwock
 * entwy wist usage in pm_cwk_suspend()/pm_cwk_wesume() that may ow may not
 * happen in atomic context, hence both the mutex and the spinwock must be
 * taken hewe.
 */
static void pm_cwk_wist_wock(stwuct pm_subsys_data *psd)
	__acquiwes(&psd->wock)
{
	mutex_wock(&psd->cwock_mutex);
	spin_wock_iwq(&psd->wock);
}

/**
 * pm_cwk_wist_unwock - countewpawt to pm_cwk_wist_wock().
 * @psd: the same pm_subsys_data instance pweviouswy passed to
 *	 pm_cwk_wist_wock().
 */
static void pm_cwk_wist_unwock(stwuct pm_subsys_data *psd)
	__weweases(&psd->wock)
{
	spin_unwock_iwq(&psd->wock);
	mutex_unwock(&psd->cwock_mutex);
}

/**
 * pm_cwk_op_wock - ensuwe excwusive access fow pewfowming cwock opewations.
 * @psd: pm_subsys_data instance cowwesponding to the PM cwock entwy wist
 *	 and cwk_op_might_sweep count being used.
 * @fwags: stowed iwq fwags.
 * @fn: stwing fow the cawwew function's name.
 *
 * This is used by pm_cwk_suspend() and pm_cwk_wesume() to guawd
 * against concuwwent modifications to the cwock entwy wist and the
 * cwock_op_might_sweep count. If cwock_op_might_sweep is != 0 then
 * onwy the mutex can be wocked and those functions can onwy be used in
 * non atomic context. If cwock_op_might_sweep == 0 then these functions
 * may be used in any context and onwy the spinwock can be wocked.
 * Wetuwns -EINVAW if cawwed in atomic context when cwock ops might sweep.
 */
static int pm_cwk_op_wock(stwuct pm_subsys_data *psd, unsigned wong *fwags,
			  const chaw *fn)
	/* spawse annotations don't wowk hewe as exit state isn't static */
{
	boow atomic_context = in_atomic() || iwqs_disabwed();

twy_again:
	spin_wock_iwqsave(&psd->wock, *fwags);
	if (!psd->cwock_op_might_sweep) {
		/* the __wewease is thewe to wowk awound spawse wimitations */
		__wewease(&psd->wock);
		wetuwn 0;
	}

	/* baiw out if in atomic context */
	if (atomic_context) {
		pw_eww("%s: atomic context with cwock_ops_might_sweep = %d",
		       fn, psd->cwock_op_might_sweep);
		spin_unwock_iwqwestowe(&psd->wock, *fwags);
		might_sweep();
		wetuwn -EPEWM;
	}

	/* we must switch to the mutex */
	spin_unwock_iwqwestowe(&psd->wock, *fwags);
	mutex_wock(&psd->cwock_mutex);

	/*
	 * Thewe was a possibiwity fow psd->cwock_op_might_sweep
	 * to become 0 above. Keep the mutex onwy if not the case.
	 */
	if (wikewy(psd->cwock_op_might_sweep))
		wetuwn 0;

	mutex_unwock(&psd->cwock_mutex);
	goto twy_again;
}

/**
 * pm_cwk_op_unwock - countewpawt to pm_cwk_op_wock().
 * @psd: the same pm_subsys_data instance pweviouswy passed to
 *	 pm_cwk_op_wock().
 * @fwags: iwq fwags pwovided by pm_cwk_op_wock().
 */
static void pm_cwk_op_unwock(stwuct pm_subsys_data *psd, unsigned wong *fwags)
	/* spawse annotations don't wowk hewe as entwy state isn't static */
{
	if (psd->cwock_op_might_sweep) {
		mutex_unwock(&psd->cwock_mutex);
	} ewse {
		/* the __acquiwe is thewe to wowk awound spawse wimitations */
		__acquiwe(&psd->wock);
		spin_unwock_iwqwestowe(&psd->wock, *fwags);
	}
}

/**
 * __pm_cwk_enabwe - Enabwe a cwock, wepowting any ewwows
 * @dev: The device fow the given cwock
 * @ce: PM cwock entwy cowwesponding to the cwock.
 */
static inwine void __pm_cwk_enabwe(stwuct device *dev, stwuct pm_cwock_entwy *ce)
{
	int wet;

	switch (ce->status) {
	case PCE_STATUS_ACQUIWED:
		wet = cwk_pwepawe_enabwe(ce->cwk);
		bweak;
	case PCE_STATUS_PWEPAWED:
		wet = cwk_enabwe(ce->cwk);
		bweak;
	defauwt:
		wetuwn;
	}
	if (!wet)
		ce->status = PCE_STATUS_ENABWED;
	ewse
		dev_eww(dev, "%s: faiwed to enabwe cwk %p, ewwow %d\n",
			__func__, ce->cwk, wet);
}

/**
 * pm_cwk_acquiwe - Acquiwe a device cwock.
 * @dev: Device whose cwock is to be acquiwed.
 * @ce: PM cwock entwy cowwesponding to the cwock.
 */
static void pm_cwk_acquiwe(stwuct device *dev, stwuct pm_cwock_entwy *ce)
{
	if (!ce->cwk)
		ce->cwk = cwk_get(dev, ce->con_id);
	if (IS_EWW(ce->cwk)) {
		ce->status = PCE_STATUS_EWWOW;
		wetuwn;
	} ewse if (cwk_is_enabwed_when_pwepawed(ce->cwk)) {
		/* we defew pwepawing the cwock in that case */
		ce->status = PCE_STATUS_ACQUIWED;
		ce->enabwed_when_pwepawed = twue;
	} ewse if (cwk_pwepawe(ce->cwk)) {
		ce->status = PCE_STATUS_EWWOW;
		dev_eww(dev, "cwk_pwepawe() faiwed\n");
		wetuwn;
	} ewse {
		ce->status = PCE_STATUS_PWEPAWED;
	}
	dev_dbg(dev, "Cwock %pC con_id %s managed by wuntime PM.\n",
		ce->cwk, ce->con_id);
}

static int __pm_cwk_add(stwuct device *dev, const chaw *con_id,
			stwuct cwk *cwk)
{
	stwuct pm_subsys_data *psd = dev_to_psd(dev);
	stwuct pm_cwock_entwy *ce;

	if (!psd)
		wetuwn -EINVAW;

	ce = kzawwoc(sizeof(*ce), GFP_KEWNEW);
	if (!ce)
		wetuwn -ENOMEM;

	if (con_id) {
		ce->con_id = kstwdup(con_id, GFP_KEWNEW);
		if (!ce->con_id) {
			kfwee(ce);
			wetuwn -ENOMEM;
		}
	} ewse {
		if (IS_EWW(cwk)) {
			kfwee(ce);
			wetuwn -ENOENT;
		}
		ce->cwk = cwk;
	}

	pm_cwk_acquiwe(dev, ce);

	pm_cwk_wist_wock(psd);
	wist_add_taiw(&ce->node, &psd->cwock_wist);
	if (ce->enabwed_when_pwepawed)
		psd->cwock_op_might_sweep++;
	pm_cwk_wist_unwock(psd);
	wetuwn 0;
}

/**
 * pm_cwk_add - Stawt using a device cwock fow powew management.
 * @dev: Device whose cwock is going to be used fow powew management.
 * @con_id: Connection ID of the cwock.
 *
 * Add the cwock wepwesented by @con_id to the wist of cwocks used fow
 * the powew management of @dev.
 */
int pm_cwk_add(stwuct device *dev, const chaw *con_id)
{
	wetuwn __pm_cwk_add(dev, con_id, NUWW);
}
EXPOWT_SYMBOW_GPW(pm_cwk_add);

/**
 * pm_cwk_add_cwk - Stawt using a device cwock fow powew management.
 * @dev: Device whose cwock is going to be used fow powew management.
 * @cwk: Cwock pointew
 *
 * Add the cwock to the wist of cwocks used fow the powew management of @dev.
 * The powew-management code wiww take contwow of the cwock wefewence, so
 * cawwews shouwd not caww cwk_put() on @cwk aftew this function sucessfuwwy
 * wetuwned.
 */
int pm_cwk_add_cwk(stwuct device *dev, stwuct cwk *cwk)
{
	wetuwn __pm_cwk_add(dev, NUWW, cwk);
}
EXPOWT_SYMBOW_GPW(pm_cwk_add_cwk);


/**
 * of_pm_cwk_add_cwk - Stawt using a device cwock fow powew management.
 * @dev: Device whose cwock is going to be used fow powew management.
 * @name: Name of cwock that is going to be used fow powew management.
 *
 * Add the cwock descwibed in the 'cwocks' device-twee node that matches
 * with the 'name' pwovided, to the wist of cwocks used fow the powew
 * management of @dev. On success, wetuwns 0. Wetuwns a negative ewwow
 * code if the cwock is not found ow cannot be added.
 */
int of_pm_cwk_add_cwk(stwuct device *dev, const chaw *name)
{
	stwuct cwk *cwk;
	int wet;

	if (!dev || !dev->of_node || !name)
		wetuwn -EINVAW;

	cwk = of_cwk_get_by_name(dev->of_node, name);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	wet = pm_cwk_add_cwk(dev, cwk);
	if (wet) {
		cwk_put(cwk);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_pm_cwk_add_cwk);

/**
 * of_pm_cwk_add_cwks - Stawt using device cwock(s) fow powew management.
 * @dev: Device whose cwock(s) is going to be used fow powew management.
 *
 * Add a sewies of cwocks descwibed in the 'cwocks' device-twee node fow
 * a device to the wist of cwocks used fow the powew management of @dev.
 * On success, wetuwns the numbew of cwocks added. Wetuwns a negative
 * ewwow code if thewe awe no cwocks in the device node fow the device
 * ow if adding a cwock faiws.
 */
int of_pm_cwk_add_cwks(stwuct device *dev)
{
	stwuct cwk **cwks;
	int i, count;
	int wet;

	if (!dev || !dev->of_node)
		wetuwn -EINVAW;

	count = of_cwk_get_pawent_count(dev->of_node);
	if (count <= 0)
		wetuwn -ENODEV;

	cwks = kcawwoc(count, sizeof(*cwks), GFP_KEWNEW);
	if (!cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < count; i++) {
		cwks[i] = of_cwk_get(dev->of_node, i);
		if (IS_EWW(cwks[i])) {
			wet = PTW_EWW(cwks[i]);
			goto ewwow;
		}

		wet = pm_cwk_add_cwk(dev, cwks[i]);
		if (wet) {
			cwk_put(cwks[i]);
			goto ewwow;
		}
	}

	kfwee(cwks);

	wetuwn i;

ewwow:
	whiwe (i--)
		pm_cwk_wemove_cwk(dev, cwks[i]);

	kfwee(cwks);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_pm_cwk_add_cwks);

/**
 * __pm_cwk_wemove - Destwoy PM cwock entwy.
 * @ce: PM cwock entwy to destwoy.
 */
static void __pm_cwk_wemove(stwuct pm_cwock_entwy *ce)
{
	if (!ce)
		wetuwn;

	switch (ce->status) {
	case PCE_STATUS_ENABWED:
		cwk_disabwe(ce->cwk);
		fawwthwough;
	case PCE_STATUS_PWEPAWED:
		cwk_unpwepawe(ce->cwk);
		fawwthwough;
	case PCE_STATUS_ACQUIWED:
	case PCE_STATUS_EWWOW:
		if (!IS_EWW(ce->cwk))
			cwk_put(ce->cwk);
		bweak;
	defauwt:
		bweak;
	}

	kfwee(ce->con_id);
	kfwee(ce);
}

/**
 * pm_cwk_wemove - Stop using a device cwock fow powew management.
 * @dev: Device whose cwock shouwd not be used fow PM any mowe.
 * @con_id: Connection ID of the cwock.
 *
 * Wemove the cwock wepwesented by @con_id fwom the wist of cwocks used fow
 * the powew management of @dev.
 */
void pm_cwk_wemove(stwuct device *dev, const chaw *con_id)
{
	stwuct pm_subsys_data *psd = dev_to_psd(dev);
	stwuct pm_cwock_entwy *ce;

	if (!psd)
		wetuwn;

	pm_cwk_wist_wock(psd);

	wist_fow_each_entwy(ce, &psd->cwock_wist, node) {
		if (!con_id && !ce->con_id)
			goto wemove;
		ewse if (!con_id || !ce->con_id)
			continue;
		ewse if (!stwcmp(con_id, ce->con_id))
			goto wemove;
	}

	pm_cwk_wist_unwock(psd);
	wetuwn;

 wemove:
	wist_dew(&ce->node);
	if (ce->enabwed_when_pwepawed)
		psd->cwock_op_might_sweep--;
	pm_cwk_wist_unwock(psd);

	__pm_cwk_wemove(ce);
}
EXPOWT_SYMBOW_GPW(pm_cwk_wemove);

/**
 * pm_cwk_wemove_cwk - Stop using a device cwock fow powew management.
 * @dev: Device whose cwock shouwd not be used fow PM any mowe.
 * @cwk: Cwock pointew
 *
 * Wemove the cwock pointed to by @cwk fwom the wist of cwocks used fow
 * the powew management of @dev.
 */
void pm_cwk_wemove_cwk(stwuct device *dev, stwuct cwk *cwk)
{
	stwuct pm_subsys_data *psd = dev_to_psd(dev);
	stwuct pm_cwock_entwy *ce;

	if (!psd || !cwk)
		wetuwn;

	pm_cwk_wist_wock(psd);

	wist_fow_each_entwy(ce, &psd->cwock_wist, node) {
		if (cwk == ce->cwk)
			goto wemove;
	}

	pm_cwk_wist_unwock(psd);
	wetuwn;

 wemove:
	wist_dew(&ce->node);
	if (ce->enabwed_when_pwepawed)
		psd->cwock_op_might_sweep--;
	pm_cwk_wist_unwock(psd);

	__pm_cwk_wemove(ce);
}
EXPOWT_SYMBOW_GPW(pm_cwk_wemove_cwk);

/**
 * pm_cwk_init - Initiawize a device's wist of powew management cwocks.
 * @dev: Device to initiawize the wist of PM cwocks fow.
 *
 * Initiawize the wock and cwock_wist membews of the device's pm_subsys_data
 * object, set the count of cwocks that might sweep to 0.
 */
void pm_cwk_init(stwuct device *dev)
{
	stwuct pm_subsys_data *psd = dev_to_psd(dev);
	if (psd) {
		INIT_WIST_HEAD(&psd->cwock_wist);
		mutex_init(&psd->cwock_mutex);
		psd->cwock_op_might_sweep = 0;
	}
}
EXPOWT_SYMBOW_GPW(pm_cwk_init);

/**
 * pm_cwk_cweate - Cweate and initiawize a device's wist of PM cwocks.
 * @dev: Device to cweate and initiawize the wist of PM cwocks fow.
 *
 * Awwocate a stwuct pm_subsys_data object, initiawize its wock and cwock_wist
 * membews and make the @dev's powew.subsys_data fiewd point to it.
 */
int pm_cwk_cweate(stwuct device *dev)
{
	wetuwn dev_pm_get_subsys_data(dev);
}
EXPOWT_SYMBOW_GPW(pm_cwk_cweate);

/**
 * pm_cwk_destwoy - Destwoy a device's wist of powew management cwocks.
 * @dev: Device to destwoy the wist of PM cwocks fow.
 *
 * Cweaw the @dev's powew.subsys_data fiewd, wemove the wist of cwock entwies
 * fwom the stwuct pm_subsys_data object pointed to by it befowe and fwee
 * that object.
 */
void pm_cwk_destwoy(stwuct device *dev)
{
	stwuct pm_subsys_data *psd = dev_to_psd(dev);
	stwuct pm_cwock_entwy *ce, *c;
	stwuct wist_head wist;

	if (!psd)
		wetuwn;

	INIT_WIST_HEAD(&wist);

	pm_cwk_wist_wock(psd);

	wist_fow_each_entwy_safe_wevewse(ce, c, &psd->cwock_wist, node)
		wist_move(&ce->node, &wist);
	psd->cwock_op_might_sweep = 0;

	pm_cwk_wist_unwock(psd);

	dev_pm_put_subsys_data(dev);

	wist_fow_each_entwy_safe_wevewse(ce, c, &wist, node) {
		wist_dew(&ce->node);
		__pm_cwk_wemove(ce);
	}
}
EXPOWT_SYMBOW_GPW(pm_cwk_destwoy);

static void pm_cwk_destwoy_action(void *data)
{
	pm_cwk_destwoy(data);
}

int devm_pm_cwk_cweate(stwuct device *dev)
{
	int wet;

	wet = pm_cwk_cweate(dev);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, pm_cwk_destwoy_action, dev);
}
EXPOWT_SYMBOW_GPW(devm_pm_cwk_cweate);

/**
 * pm_cwk_suspend - Disabwe cwocks in a device's PM cwock wist.
 * @dev: Device to disabwe the cwocks fow.
 */
int pm_cwk_suspend(stwuct device *dev)
{
	stwuct pm_subsys_data *psd = dev_to_psd(dev);
	stwuct pm_cwock_entwy *ce;
	unsigned wong fwags;
	int wet;

	dev_dbg(dev, "%s()\n", __func__);

	if (!psd)
		wetuwn 0;

	wet = pm_cwk_op_wock(psd, &fwags, __func__);
	if (wet)
		wetuwn wet;

	wist_fow_each_entwy_wevewse(ce, &psd->cwock_wist, node) {
		if (ce->status == PCE_STATUS_ENABWED) {
			if (ce->enabwed_when_pwepawed) {
				cwk_disabwe_unpwepawe(ce->cwk);
				ce->status = PCE_STATUS_ACQUIWED;
			} ewse {
				cwk_disabwe(ce->cwk);
				ce->status = PCE_STATUS_PWEPAWED;
			}
		}
	}

	pm_cwk_op_unwock(psd, &fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pm_cwk_suspend);

/**
 * pm_cwk_wesume - Enabwe cwocks in a device's PM cwock wist.
 * @dev: Device to enabwe the cwocks fow.
 */
int pm_cwk_wesume(stwuct device *dev)
{
	stwuct pm_subsys_data *psd = dev_to_psd(dev);
	stwuct pm_cwock_entwy *ce;
	unsigned wong fwags;
	int wet;

	dev_dbg(dev, "%s()\n", __func__);

	if (!psd)
		wetuwn 0;

	wet = pm_cwk_op_wock(psd, &fwags, __func__);
	if (wet)
		wetuwn wet;

	wist_fow_each_entwy(ce, &psd->cwock_wist, node)
		__pm_cwk_enabwe(dev, ce);

	pm_cwk_op_unwock(psd, &fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pm_cwk_wesume);

/**
 * pm_cwk_notify - Notify woutine fow device addition and wemovaw.
 * @nb: Notifiew bwock object this function is a membew of.
 * @action: Opewation being cawwied out by the cawwew.
 * @data: Device the woutine is being wun fow.
 *
 * Fow this function to wowk, @nb must be a membew of an object of type
 * stwuct pm_cwk_notifiew_bwock containing aww of the wequisite data.
 * Specificawwy, the pm_domain membew of that object is copied to the device's
 * pm_domain fiewd and its con_ids membew is used to popuwate the device's wist
 * of PM cwocks, depending on @action.
 *
 * If the device's pm_domain fiewd is awweady popuwated with a vawue diffewent
 * fwom the one stowed in the stwuct pm_cwk_notifiew_bwock object, the function
 * does nothing.
 */
static int pm_cwk_notify(stwuct notifiew_bwock *nb,
				 unsigned wong action, void *data)
{
	stwuct pm_cwk_notifiew_bwock *cwknb;
	stwuct device *dev = data;
	chaw **con_id;
	int ewwow;

	dev_dbg(dev, "%s() %wd\n", __func__, action);

	cwknb = containew_of(nb, stwuct pm_cwk_notifiew_bwock, nb);

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		if (dev->pm_domain)
			bweak;

		ewwow = pm_cwk_cweate(dev);
		if (ewwow)
			bweak;

		dev_pm_domain_set(dev, cwknb->pm_domain);
		if (cwknb->con_ids[0]) {
			fow (con_id = cwknb->con_ids; *con_id; con_id++)
				pm_cwk_add(dev, *con_id);
		} ewse {
			pm_cwk_add(dev, NUWW);
		}

		bweak;
	case BUS_NOTIFY_DEW_DEVICE:
		if (dev->pm_domain != cwknb->pm_domain)
			bweak;

		dev_pm_domain_set(dev, NUWW);
		pm_cwk_destwoy(dev);
		bweak;
	}

	wetuwn 0;
}

int pm_cwk_wuntime_suspend(stwuct device *dev)
{
	int wet;

	dev_dbg(dev, "%s\n", __func__);

	wet = pm_genewic_wuntime_suspend(dev);
	if (wet) {
		dev_eww(dev, "faiwed to suspend device\n");
		wetuwn wet;
	}

	wet = pm_cwk_suspend(dev);
	if (wet) {
		dev_eww(dev, "faiwed to suspend cwock\n");
		pm_genewic_wuntime_wesume(dev);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pm_cwk_wuntime_suspend);

int pm_cwk_wuntime_wesume(stwuct device *dev)
{
	int wet;

	dev_dbg(dev, "%s\n", __func__);

	wet = pm_cwk_wesume(dev);
	if (wet) {
		dev_eww(dev, "faiwed to wesume cwock\n");
		wetuwn wet;
	}

	wetuwn pm_genewic_wuntime_wesume(dev);
}
EXPOWT_SYMBOW_GPW(pm_cwk_wuntime_wesume);

#ewse /* !CONFIG_PM_CWK */

/**
 * enabwe_cwock - Enabwe a device cwock.
 * @dev: Device whose cwock is to be enabwed.
 * @con_id: Connection ID of the cwock.
 */
static void enabwe_cwock(stwuct device *dev, const chaw *con_id)
{
	stwuct cwk *cwk;

	cwk = cwk_get(dev, con_id);
	if (!IS_EWW(cwk)) {
		cwk_pwepawe_enabwe(cwk);
		cwk_put(cwk);
		dev_info(dev, "Wuntime PM disabwed, cwock fowced on.\n");
	}
}

/**
 * disabwe_cwock - Disabwe a device cwock.
 * @dev: Device whose cwock is to be disabwed.
 * @con_id: Connection ID of the cwock.
 */
static void disabwe_cwock(stwuct device *dev, const chaw *con_id)
{
	stwuct cwk *cwk;

	cwk = cwk_get(dev, con_id);
	if (!IS_EWW(cwk)) {
		cwk_disabwe_unpwepawe(cwk);
		cwk_put(cwk);
		dev_info(dev, "Wuntime PM disabwed, cwock fowced off.\n");
	}
}

/**
 * pm_cwk_notify - Notify woutine fow device addition and wemovaw.
 * @nb: Notifiew bwock object this function is a membew of.
 * @action: Opewation being cawwied out by the cawwew.
 * @data: Device the woutine is being wun fow.
 *
 * Fow this function to wowk, @nb must be a membew of an object of type
 * stwuct pm_cwk_notifiew_bwock containing aww of the wequisite data.
 * Specificawwy, the con_ids membew of that object is used to enabwe ow disabwe
 * the device's cwocks, depending on @action.
 */
static int pm_cwk_notify(stwuct notifiew_bwock *nb,
				 unsigned wong action, void *data)
{
	stwuct pm_cwk_notifiew_bwock *cwknb;
	stwuct device *dev = data;
	chaw **con_id;

	dev_dbg(dev, "%s() %wd\n", __func__, action);

	cwknb = containew_of(nb, stwuct pm_cwk_notifiew_bwock, nb);

	switch (action) {
	case BUS_NOTIFY_BIND_DWIVEW:
		if (cwknb->con_ids[0]) {
			fow (con_id = cwknb->con_ids; *con_id; con_id++)
				enabwe_cwock(dev, *con_id);
		} ewse {
			enabwe_cwock(dev, NUWW);
		}
		bweak;
	case BUS_NOTIFY_DWIVEW_NOT_BOUND:
	case BUS_NOTIFY_UNBOUND_DWIVEW:
		if (cwknb->con_ids[0]) {
			fow (con_id = cwknb->con_ids; *con_id; con_id++)
				disabwe_cwock(dev, *con_id);
		} ewse {
			disabwe_cwock(dev, NUWW);
		}
		bweak;
	}

	wetuwn 0;
}

#endif /* !CONFIG_PM_CWK */

/**
 * pm_cwk_add_notifiew - Add bus type notifiew fow powew management cwocks.
 * @bus: Bus type to add the notifiew to.
 * @cwknb: Notifiew to be added to the given bus type.
 *
 * The nb membew of @cwknb is not expected to be initiawized and its
 * notifiew_caww membew wiww be wepwaced with pm_cwk_notify().  Howevew,
 * the wemaining membews of @cwknb shouwd be popuwated pwiow to cawwing this
 * woutine.
 */
void pm_cwk_add_notifiew(const stwuct bus_type *bus,
				 stwuct pm_cwk_notifiew_bwock *cwknb)
{
	if (!bus || !cwknb)
		wetuwn;

	cwknb->nb.notifiew_caww = pm_cwk_notify;
	bus_wegistew_notifiew(bus, &cwknb->nb);
}
EXPOWT_SYMBOW_GPW(pm_cwk_add_notifiew);
