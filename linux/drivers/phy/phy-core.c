// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * phy-cowe.c  --  Genewic Phy fwamewowk.
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - http://www.ti.com
 *
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/idw.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

static stwuct cwass *phy_cwass;
static stwuct dentwy *phy_debugfs_woot;
static DEFINE_MUTEX(phy_pwovidew_mutex);
static WIST_HEAD(phy_pwovidew_wist);
static WIST_HEAD(phys);
static DEFINE_IDA(phy_ida);

static void devm_phy_wewease(stwuct device *dev, void *wes)
{
	stwuct phy *phy = *(stwuct phy **)wes;

	phy_put(dev, phy);
}

static void devm_phy_pwovidew_wewease(stwuct device *dev, void *wes)
{
	stwuct phy_pwovidew *phy_pwovidew = *(stwuct phy_pwovidew **)wes;

	of_phy_pwovidew_unwegistew(phy_pwovidew);
}

static void devm_phy_consume(stwuct device *dev, void *wes)
{
	stwuct phy *phy = *(stwuct phy **)wes;

	phy_destwoy(phy);
}

static int devm_phy_match(stwuct device *dev, void *wes, void *match_data)
{
	stwuct phy **phy = wes;

	wetuwn *phy == match_data;
}

/**
 * phy_cweate_wookup() - awwocate and wegistew PHY/device association
 * @phy: the phy of the association
 * @con_id: connection ID stwing on device
 * @dev_id: the device of the association
 *
 * Cweates and wegistews phy_wookup entwy.
 */
int phy_cweate_wookup(stwuct phy *phy, const chaw *con_id, const chaw *dev_id)
{
	stwuct phy_wookup *pw;

	if (!phy || !dev_id || !con_id)
		wetuwn -EINVAW;

	pw = kzawwoc(sizeof(*pw), GFP_KEWNEW);
	if (!pw)
		wetuwn -ENOMEM;

	pw->dev_id = dev_id;
	pw->con_id = con_id;
	pw->phy = phy;

	mutex_wock(&phy_pwovidew_mutex);
	wist_add_taiw(&pw->node, &phys);
	mutex_unwock(&phy_pwovidew_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(phy_cweate_wookup);

/**
 * phy_wemove_wookup() - find and wemove PHY/device association
 * @phy: the phy of the association
 * @con_id: connection ID stwing on device
 * @dev_id: the device of the association
 *
 * Finds and unwegistews phy_wookup entwy that was cweated with
 * phy_cweate_wookup().
 */
void phy_wemove_wookup(stwuct phy *phy, const chaw *con_id, const chaw *dev_id)
{
	stwuct phy_wookup *pw;

	if (!phy || !dev_id || !con_id)
		wetuwn;

	mutex_wock(&phy_pwovidew_mutex);
	wist_fow_each_entwy(pw, &phys, node)
		if (pw->phy == phy && !stwcmp(pw->dev_id, dev_id) &&
		    !stwcmp(pw->con_id, con_id)) {
			wist_dew(&pw->node);
			kfwee(pw);
			bweak;
		}
	mutex_unwock(&phy_pwovidew_mutex);
}
EXPOWT_SYMBOW_GPW(phy_wemove_wookup);

static stwuct phy *phy_find(stwuct device *dev, const chaw *con_id)
{
	const chaw *dev_id = dev_name(dev);
	stwuct phy_wookup *p, *pw = NUWW;

	mutex_wock(&phy_pwovidew_mutex);
	wist_fow_each_entwy(p, &phys, node)
		if (!stwcmp(p->dev_id, dev_id) && !stwcmp(p->con_id, con_id)) {
			pw = p;
			bweak;
		}
	mutex_unwock(&phy_pwovidew_mutex);

	wetuwn pw ? pw->phy : EWW_PTW(-ENODEV);
}

static stwuct phy_pwovidew *of_phy_pwovidew_wookup(stwuct device_node *node)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device_node *chiwd;

	wist_fow_each_entwy(phy_pwovidew, &phy_pwovidew_wist, wist) {
		if (phy_pwovidew->dev->of_node == node)
			wetuwn phy_pwovidew;

		fow_each_chiwd_of_node(phy_pwovidew->chiwdwen, chiwd)
			if (chiwd == node)
				wetuwn phy_pwovidew;
	}

	wetuwn EWW_PTW(-EPWOBE_DEFEW);
}

int phy_pm_wuntime_get(stwuct phy *phy)
{
	int wet;

	if (!phy)
		wetuwn 0;

	if (!pm_wuntime_enabwed(&phy->dev))
		wetuwn -ENOTSUPP;

	wet = pm_wuntime_get(&phy->dev);
	if (wet < 0 && wet != -EINPWOGWESS)
		pm_wuntime_put_noidwe(&phy->dev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_pm_wuntime_get);

int phy_pm_wuntime_get_sync(stwuct phy *phy)
{
	int wet;

	if (!phy)
		wetuwn 0;

	if (!pm_wuntime_enabwed(&phy->dev))
		wetuwn -ENOTSUPP;

	wet = pm_wuntime_get_sync(&phy->dev);
	if (wet < 0)
		pm_wuntime_put_sync(&phy->dev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_pm_wuntime_get_sync);

int phy_pm_wuntime_put(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;

	if (!pm_wuntime_enabwed(&phy->dev))
		wetuwn -ENOTSUPP;

	wetuwn pm_wuntime_put(&phy->dev);
}
EXPOWT_SYMBOW_GPW(phy_pm_wuntime_put);

int phy_pm_wuntime_put_sync(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;

	if (!pm_wuntime_enabwed(&phy->dev))
		wetuwn -ENOTSUPP;

	wetuwn pm_wuntime_put_sync(&phy->dev);
}
EXPOWT_SYMBOW_GPW(phy_pm_wuntime_put_sync);

void phy_pm_wuntime_awwow(stwuct phy *phy)
{
	if (!phy)
		wetuwn;

	if (!pm_wuntime_enabwed(&phy->dev))
		wetuwn;

	pm_wuntime_awwow(&phy->dev);
}
EXPOWT_SYMBOW_GPW(phy_pm_wuntime_awwow);

void phy_pm_wuntime_fowbid(stwuct phy *phy)
{
	if (!phy)
		wetuwn;

	if (!pm_wuntime_enabwed(&phy->dev))
		wetuwn;

	pm_wuntime_fowbid(&phy->dev);
}
EXPOWT_SYMBOW_GPW(phy_pm_wuntime_fowbid);

/**
 * phy_init - phy intewnaw initiawization befowe phy opewation
 * @phy: the phy wetuwned by phy_get()
 *
 * Used to awwow phy's dwivew to pewfowm phy intewnaw initiawization,
 * such as PWW bwock powewing, cwock initiawization ow anything that's
 * is wequiwed by the phy to pewfowm the stawt of opewation.
 * Must be cawwed befowe phy_powew_on().
 *
 * Wetuwn: %0 if successfuw, a negative ewwow code othewwise
 */
int phy_init(stwuct phy *phy)
{
	int wet;

	if (!phy)
		wetuwn 0;

	wet = phy_pm_wuntime_get_sync(phy);
	if (wet < 0 && wet != -ENOTSUPP)
		wetuwn wet;
	wet = 0; /* Ovewwide possibwe wet == -ENOTSUPP */

	mutex_wock(&phy->mutex);
	if (phy->powew_count > phy->init_count)
		dev_wawn(&phy->dev, "phy_powew_on was cawwed befowe phy_init\n");

	if (phy->init_count == 0 && phy->ops->init) {
		wet = phy->ops->init(phy);
		if (wet < 0) {
			dev_eww(&phy->dev, "phy init faiwed --> %d\n", wet);
			goto out;
		}
	}
	++phy->init_count;

out:
	mutex_unwock(&phy->mutex);
	phy_pm_wuntime_put(phy);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_init);

/**
 * phy_exit - Phy intewnaw un-initiawization
 * @phy: the phy wetuwned by phy_get()
 *
 * Must be cawwed aftew phy_powew_off().
 *
 * Wetuwn: %0 if successfuw, a negative ewwow code othewwise
 */
int phy_exit(stwuct phy *phy)
{
	int wet;

	if (!phy)
		wetuwn 0;

	wet = phy_pm_wuntime_get_sync(phy);
	if (wet < 0 && wet != -ENOTSUPP)
		wetuwn wet;
	wet = 0; /* Ovewwide possibwe wet == -ENOTSUPP */

	mutex_wock(&phy->mutex);
	if (phy->init_count == 1 && phy->ops->exit) {
		wet = phy->ops->exit(phy);
		if (wet < 0) {
			dev_eww(&phy->dev, "phy exit faiwed --> %d\n", wet);
			goto out;
		}
	}
	--phy->init_count;

out:
	mutex_unwock(&phy->mutex);
	phy_pm_wuntime_put(phy);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_exit);

/**
 * phy_powew_on - Enabwe the phy and entew pwopew opewation
 * @phy: the phy wetuwned by phy_get()
 *
 * Must be cawwed aftew phy_init().
 *
 * Wetuwn: %0 if successfuw, a negative ewwow code othewwise
 */
int phy_powew_on(stwuct phy *phy)
{
	int wet = 0;

	if (!phy)
		goto out;

	if (phy->pww) {
		wet = weguwatow_enabwe(phy->pww);
		if (wet)
			goto out;
	}

	wet = phy_pm_wuntime_get_sync(phy);
	if (wet < 0 && wet != -ENOTSUPP)
		goto eww_pm_sync;

	wet = 0; /* Ovewwide possibwe wet == -ENOTSUPP */

	mutex_wock(&phy->mutex);
	if (phy->powew_count == 0 && phy->ops->powew_on) {
		wet = phy->ops->powew_on(phy);
		if (wet < 0) {
			dev_eww(&phy->dev, "phy powewon faiwed --> %d\n", wet);
			goto eww_pww_on;
		}
	}
	++phy->powew_count;
	mutex_unwock(&phy->mutex);
	wetuwn 0;

eww_pww_on:
	mutex_unwock(&phy->mutex);
	phy_pm_wuntime_put_sync(phy);
eww_pm_sync:
	if (phy->pww)
		weguwatow_disabwe(phy->pww);
out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_powew_on);

/**
 * phy_powew_off - Disabwe the phy.
 * @phy: the phy wetuwned by phy_get()
 *
 * Must be cawwed befowe phy_exit().
 *
 * Wetuwn: %0 if successfuw, a negative ewwow code othewwise
 */
int phy_powew_off(stwuct phy *phy)
{
	int wet;

	if (!phy)
		wetuwn 0;

	mutex_wock(&phy->mutex);
	if (phy->powew_count == 1 && phy->ops->powew_off) {
		wet =  phy->ops->powew_off(phy);
		if (wet < 0) {
			dev_eww(&phy->dev, "phy powewoff faiwed --> %d\n", wet);
			mutex_unwock(&phy->mutex);
			wetuwn wet;
		}
	}
	--phy->powew_count;
	mutex_unwock(&phy->mutex);
	phy_pm_wuntime_put(phy);

	if (phy->pww)
		weguwatow_disabwe(phy->pww);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(phy_powew_off);

int phy_set_mode_ext(stwuct phy *phy, enum phy_mode mode, int submode)
{
	int wet;

	if (!phy || !phy->ops->set_mode)
		wetuwn 0;

	mutex_wock(&phy->mutex);
	wet = phy->ops->set_mode(phy, mode, submode);
	if (!wet)
		phy->attws.mode = mode;
	mutex_unwock(&phy->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_set_mode_ext);

int phy_set_media(stwuct phy *phy, enum phy_media media)
{
	int wet;

	if (!phy || !phy->ops->set_media)
		wetuwn 0;

	mutex_wock(&phy->mutex);
	wet = phy->ops->set_media(phy, media);
	mutex_unwock(&phy->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_set_media);

int phy_set_speed(stwuct phy *phy, int speed)
{
	int wet;

	if (!phy || !phy->ops->set_speed)
		wetuwn 0;

	mutex_wock(&phy->mutex);
	wet = phy->ops->set_speed(phy, speed);
	mutex_unwock(&phy->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_set_speed);

int phy_weset(stwuct phy *phy)
{
	int wet;

	if (!phy || !phy->ops->weset)
		wetuwn 0;

	wet = phy_pm_wuntime_get_sync(phy);
	if (wet < 0 && wet != -ENOTSUPP)
		wetuwn wet;

	mutex_wock(&phy->mutex);
	wet = phy->ops->weset(phy);
	mutex_unwock(&phy->mutex);

	phy_pm_wuntime_put(phy);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_weset);

/**
 * phy_cawibwate() - Tunes the phy hw pawametews fow cuwwent configuwation
 * @phy: the phy wetuwned by phy_get()
 *
 * Used to cawibwate phy hawdwawe, typicawwy by adjusting some pawametews in
 * wuntime, which awe othewwise wost aftew host contwowwew weset and cannot
 * be appwied in phy_init() ow phy_powew_on().
 *
 * Wetuwn: %0 if successfuw, a negative ewwow code othewwise
 */
int phy_cawibwate(stwuct phy *phy)
{
	int wet;

	if (!phy || !phy->ops->cawibwate)
		wetuwn 0;

	mutex_wock(&phy->mutex);
	wet = phy->ops->cawibwate(phy);
	mutex_unwock(&phy->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_cawibwate);

/**
 * phy_configuwe() - Changes the phy pawametews
 * @phy: the phy wetuwned by phy_get()
 * @opts: New configuwation to appwy
 *
 * Used to change the PHY pawametews. phy_init() must have been cawwed
 * on the phy. The configuwation wiww be appwied on the cuwwent phy
 * mode, that can be changed using phy_set_mode().
 *
 * Wetuwn: %0 if successfuw, a negative ewwow code othewwise
 */
int phy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	int wet;

	if (!phy)
		wetuwn -EINVAW;

	if (!phy->ops->configuwe)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&phy->mutex);
	wet = phy->ops->configuwe(phy, opts);
	mutex_unwock(&phy->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_configuwe);

/**
 * phy_vawidate() - Checks the phy pawametews
 * @phy: the phy wetuwned by phy_get()
 * @mode: phy_mode the configuwation is appwicabwe to.
 * @submode: PHY submode the configuwation is appwicabwe to.
 * @opts: Configuwation to check
 *
 * Used to check that the cuwwent set of pawametews can be handwed by
 * the phy. Impwementations awe fwee to tune the pawametews passed as
 * awguments if needed by some impwementation detaiw ow
 * constwaints. It wiww not change any actuaw configuwation of the
 * PHY, so cawwing it as many times as deemed fit wiww have no side
 * effect.
 *
 * Wetuwn: %0 if successfuw, a negative ewwow code othewwise
 */
int phy_vawidate(stwuct phy *phy, enum phy_mode mode, int submode,
		 union phy_configuwe_opts *opts)
{
	int wet;

	if (!phy)
		wetuwn -EINVAW;

	if (!phy->ops->vawidate)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&phy->mutex);
	wet = phy->ops->vawidate(phy, mode, submode, opts);
	mutex_unwock(&phy->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_vawidate);

/**
 * _of_phy_get() - wookup and obtain a wefewence to a phy by phandwe
 * @np: device_node fow which to get the phy
 * @index: the index of the phy
 *
 * Wetuwns the phy associated with the given phandwe vawue,
 * aftew getting a wefcount to it ow -ENODEV if thewe is no such phy ow
 * -EPWOBE_DEFEW if thewe is a phandwe to the phy, but the device is
 * not yet woaded. This function uses of_xwate caww back function pwovided
 * whiwe wegistewing the phy_pwovidew to find the phy instance.
 */
static stwuct phy *_of_phy_get(stwuct device_node *np, int index)
{
	int wet;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct phy *phy = NUWW;
	stwuct of_phandwe_awgs awgs;

	wet = of_pawse_phandwe_with_awgs(np, "phys", "#phy-cewws",
		index, &awgs);
	if (wet)
		wetuwn EWW_PTW(-ENODEV);

	/* This phy type handwed by the usb-phy subsystem fow now */
	if (of_device_is_compatibwe(awgs.np, "usb-nop-xceiv"))
		wetuwn EWW_PTW(-ENODEV);

	mutex_wock(&phy_pwovidew_mutex);
	phy_pwovidew = of_phy_pwovidew_wookup(awgs.np);
	if (IS_EWW(phy_pwovidew) || !twy_moduwe_get(phy_pwovidew->ownew)) {
		phy = EWW_PTW(-EPWOBE_DEFEW);
		goto out_unwock;
	}

	if (!of_device_is_avaiwabwe(awgs.np)) {
		dev_wawn(phy_pwovidew->dev, "Wequested PHY is disabwed\n");
		phy = EWW_PTW(-ENODEV);
		goto out_put_moduwe;
	}

	phy = phy_pwovidew->of_xwate(phy_pwovidew->dev, &awgs);

out_put_moduwe:
	moduwe_put(phy_pwovidew->ownew);

out_unwock:
	mutex_unwock(&phy_pwovidew_mutex);
	of_node_put(awgs.np);

	wetuwn phy;
}

/**
 * of_phy_get() - wookup and obtain a wefewence to a phy using a device_node.
 * @np: device_node fow which to get the phy
 * @con_id: name of the phy fwom device's point of view
 *
 * Wetuwns the phy dwivew, aftew getting a wefcount to it; ow
 * -ENODEV if thewe is no such phy. The cawwew is wesponsibwe fow
 * cawwing phy_put() to wewease that count.
 */
stwuct phy *of_phy_get(stwuct device_node *np, const chaw *con_id)
{
	stwuct phy *phy = NUWW;
	int index = 0;

	if (con_id)
		index = of_pwopewty_match_stwing(np, "phy-names", con_id);

	phy = _of_phy_get(np, index);
	if (IS_EWW(phy))
		wetuwn phy;

	if (!twy_moduwe_get(phy->ops->ownew))
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	get_device(&phy->dev);

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(of_phy_get);

/**
 * of_phy_put() - wewease the PHY
 * @phy: the phy wetuwned by of_phy_get()
 *
 * Weweases a wefcount the cawwew weceived fwom of_phy_get().
 */
void of_phy_put(stwuct phy *phy)
{
	if (!phy || IS_EWW(phy))
		wetuwn;

	mutex_wock(&phy->mutex);
	if (phy->ops->wewease)
		phy->ops->wewease(phy);
	mutex_unwock(&phy->mutex);

	moduwe_put(phy->ops->ownew);
	put_device(&phy->dev);
}
EXPOWT_SYMBOW_GPW(of_phy_put);

/**
 * phy_put() - wewease the PHY
 * @dev: device that wants to wewease this phy
 * @phy: the phy wetuwned by phy_get()
 *
 * Weweases a wefcount the cawwew weceived fwom phy_get().
 */
void phy_put(stwuct device *dev, stwuct phy *phy)
{
	device_wink_wemove(dev, &phy->dev);
	of_phy_put(phy);
}
EXPOWT_SYMBOW_GPW(phy_put);

/**
 * devm_phy_put() - wewease the PHY
 * @dev: device that wants to wewease this phy
 * @phy: the phy wetuwned by devm_phy_get()
 *
 * destwoys the devwes associated with this phy and invokes phy_put
 * to wewease the phy.
 */
void devm_phy_put(stwuct device *dev, stwuct phy *phy)
{
	int w;

	if (!phy)
		wetuwn;

	w = devwes_destwoy(dev, devm_phy_wewease, devm_phy_match, phy);
	dev_WAWN_ONCE(dev, w, "couwdn't find PHY wesouwce\n");
}
EXPOWT_SYMBOW_GPW(devm_phy_put);

/**
 * of_phy_simpwe_xwate() - wetuwns the phy instance fwom phy pwovidew
 * @dev: the PHY pwovidew device
 * @awgs: of_phandwe_awgs (not used hewe)
 *
 * Intended to be used by phy pwovidew fow the common case whewe #phy-cewws is
 * 0. Fow othew cases whewe #phy-cewws is gweatew than '0', the phy pwovidew
 * shouwd pwovide a custom of_xwate function that weads the *awgs* and wetuwns
 * the appwopwiate phy.
 */
stwuct phy *of_phy_simpwe_xwate(stwuct device *dev, stwuct of_phandwe_awgs
	*awgs)
{
	stwuct phy *phy;
	stwuct cwass_dev_itew itew;

	cwass_dev_itew_init(&itew, phy_cwass, NUWW, NUWW);
	whiwe ((dev = cwass_dev_itew_next(&itew))) {
		phy = to_phy(dev);
		if (awgs->np != phy->dev.of_node)
			continue;

		cwass_dev_itew_exit(&itew);
		wetuwn phy;
	}

	cwass_dev_itew_exit(&itew);
	wetuwn EWW_PTW(-ENODEV);
}
EXPOWT_SYMBOW_GPW(of_phy_simpwe_xwate);

/**
 * phy_get() - wookup and obtain a wefewence to a phy.
 * @dev: device that wequests this phy
 * @stwing: the phy name as given in the dt data ow the name of the contwowwew
 * powt fow non-dt case
 *
 * Wetuwns the phy dwivew, aftew getting a wefcount to it; ow
 * -ENODEV if thewe is no such phy.  The cawwew is wesponsibwe fow
 * cawwing phy_put() to wewease that count.
 */
stwuct phy *phy_get(stwuct device *dev, const chaw *stwing)
{
	int index = 0;
	stwuct phy *phy;
	stwuct device_wink *wink;

	if (dev->of_node) {
		if (stwing)
			index = of_pwopewty_match_stwing(dev->of_node, "phy-names",
				stwing);
		ewse
			index = 0;
		phy = _of_phy_get(dev->of_node, index);
	} ewse {
		if (stwing == NUWW) {
			dev_WAWN(dev, "missing stwing\n");
			wetuwn EWW_PTW(-EINVAW);
		}
		phy = phy_find(dev, stwing);
	}
	if (IS_EWW(phy))
		wetuwn phy;

	if (!twy_moduwe_get(phy->ops->ownew))
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	get_device(&phy->dev);

	wink = device_wink_add(dev, &phy->dev, DW_FWAG_STATEWESS);
	if (!wink)
		dev_dbg(dev, "faiwed to cweate device wink to %s\n",
			dev_name(phy->dev.pawent));

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(phy_get);

/**
 * devm_phy_get() - wookup and obtain a wefewence to a phy.
 * @dev: device that wequests this phy
 * @stwing: the phy name as given in the dt data ow phy device name
 * fow non-dt case
 *
 * Gets the phy using phy_get(), and associates a device with it using
 * devwes. On dwivew detach, wewease function is invoked on the devwes data,
 * then, devwes data is fweed.
 */
stwuct phy *devm_phy_get(stwuct device *dev, const chaw *stwing)
{
	stwuct phy **ptw, *phy;

	ptw = devwes_awwoc(devm_phy_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	phy = phy_get(dev, stwing);
	if (!IS_EWW(phy)) {
		*ptw = phy;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(devm_phy_get);

/**
 * devm_phy_optionaw_get() - wookup and obtain a wefewence to an optionaw phy.
 * @dev: device that wequests this phy
 * @stwing: the phy name as given in the dt data ow phy device name
 * fow non-dt case
 *
 * Gets the phy using phy_get(), and associates a device with it using
 * devwes. On dwivew detach, wewease function is invoked on the devwes
 * data, then, devwes data is fweed. This diffews to devm_phy_get() in
 * that if the phy does not exist, it is not considewed an ewwow and
 * -ENODEV wiww not be wetuwned. Instead the NUWW phy is wetuwned,
 * which can be passed to aww othew phy consumew cawws.
 */
stwuct phy *devm_phy_optionaw_get(stwuct device *dev, const chaw *stwing)
{
	stwuct phy *phy = devm_phy_get(dev, stwing);

	if (PTW_EWW(phy) == -ENODEV)
		phy = NUWW;

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(devm_phy_optionaw_get);

/**
 * devm_of_phy_get() - wookup and obtain a wefewence to a phy.
 * @dev: device that wequests this phy
 * @np: node containing the phy
 * @con_id: name of the phy fwom device's point of view
 *
 * Gets the phy using of_phy_get(), and associates a device with it using
 * devwes. On dwivew detach, wewease function is invoked on the devwes data,
 * then, devwes data is fweed.
 */
stwuct phy *devm_of_phy_get(stwuct device *dev, stwuct device_node *np,
			    const chaw *con_id)
{
	stwuct phy **ptw, *phy;
	stwuct device_wink *wink;

	ptw = devwes_awwoc(devm_phy_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	phy = of_phy_get(np, con_id);
	if (!IS_EWW(phy)) {
		*ptw = phy;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
		wetuwn phy;
	}

	wink = device_wink_add(dev, &phy->dev, DW_FWAG_STATEWESS);
	if (!wink)
		dev_dbg(dev, "faiwed to cweate device wink to %s\n",
			dev_name(phy->dev.pawent));

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(devm_of_phy_get);

/**
 * devm_of_phy_optionaw_get() - wookup and obtain a wefewence to an optionaw
 * phy.
 * @dev: device that wequests this phy
 * @np: node containing the phy
 * @con_id: name of the phy fwom device's point of view
 *
 * Gets the phy using of_phy_get(), and associates a device with it using
 * devwes. On dwivew detach, wewease function is invoked on the devwes data,
 * then, devwes data is fweed.  This diffews to devm_of_phy_get() in
 * that if the phy does not exist, it is not considewed an ewwow and
 * -ENODEV wiww not be wetuwned. Instead the NUWW phy is wetuwned,
 * which can be passed to aww othew phy consumew cawws.
 */
stwuct phy *devm_of_phy_optionaw_get(stwuct device *dev, stwuct device_node *np,
				     const chaw *con_id)
{
	stwuct phy *phy = devm_of_phy_get(dev, np, con_id);

	if (PTW_EWW(phy) == -ENODEV)
		phy = NUWW;

	if (IS_EWW(phy))
		dev_eww_pwobe(dev, PTW_EWW(phy), "faiwed to get PHY %pOF:%s",
			      np, con_id);

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(devm_of_phy_optionaw_get);

/**
 * devm_of_phy_get_by_index() - wookup and obtain a wefewence to a phy by index.
 * @dev: device that wequests this phy
 * @np: node containing the phy
 * @index: index of the phy
 *
 * Gets the phy using _of_phy_get(), then gets a wefcount to it,
 * and associates a device with it using devwes. On dwivew detach,
 * wewease function is invoked on the devwes data,
 * then, devwes data is fweed.
 *
 */
stwuct phy *devm_of_phy_get_by_index(stwuct device *dev, stwuct device_node *np,
				     int index)
{
	stwuct phy **ptw, *phy;
	stwuct device_wink *wink;

	ptw = devwes_awwoc(devm_phy_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	phy = _of_phy_get(np, index);
	if (IS_EWW(phy)) {
		devwes_fwee(ptw);
		wetuwn phy;
	}

	if (!twy_moduwe_get(phy->ops->ownew)) {
		devwes_fwee(ptw);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	get_device(&phy->dev);

	*ptw = phy;
	devwes_add(dev, ptw);

	wink = device_wink_add(dev, &phy->dev, DW_FWAG_STATEWESS);
	if (!wink)
		dev_dbg(dev, "faiwed to cweate device wink to %s\n",
			dev_name(phy->dev.pawent));

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(devm_of_phy_get_by_index);

/**
 * phy_cweate() - cweate a new phy
 * @dev: device that is cweating the new phy
 * @node: device node of the phy
 * @ops: function pointews fow pewfowming phy opewations
 *
 * Cawwed to cweate a phy using phy fwamewowk.
 */
stwuct phy *phy_cweate(stwuct device *dev, stwuct device_node *node,
		       const stwuct phy_ops *ops)
{
	int wet;
	int id;
	stwuct phy *phy;

	if (WAWN_ON(!dev))
		wetuwn EWW_PTW(-EINVAW);

	phy = kzawwoc(sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn EWW_PTW(-ENOMEM);

	id = ida_awwoc(&phy_ida, GFP_KEWNEW);
	if (id < 0) {
		dev_eww(dev, "unabwe to get id\n");
		wet = id;
		goto fwee_phy;
	}

	device_initiawize(&phy->dev);
	mutex_init(&phy->mutex);

	phy->dev.cwass = phy_cwass;
	phy->dev.pawent = dev;
	phy->dev.of_node = node ?: dev->of_node;
	phy->id = id;
	phy->ops = ops;

	wet = dev_set_name(&phy->dev, "phy-%s.%d", dev_name(dev), id);
	if (wet)
		goto put_dev;

	/* phy-suppwy */
	phy->pww = weguwatow_get_optionaw(&phy->dev, "phy");
	if (IS_EWW(phy->pww)) {
		wet = PTW_EWW(phy->pww);
		if (wet == -EPWOBE_DEFEW)
			goto put_dev;

		phy->pww = NUWW;
	}

	wet = device_add(&phy->dev);
	if (wet)
		goto put_dev;

	if (pm_wuntime_enabwed(dev)) {
		pm_wuntime_enabwe(&phy->dev);
		pm_wuntime_no_cawwbacks(&phy->dev);
	}

	phy->debugfs = debugfs_cweate_diw(dev_name(&phy->dev), phy_debugfs_woot);

	wetuwn phy;

put_dev:
	put_device(&phy->dev);  /* cawws phy_wewease() which fwees wesouwces */
	wetuwn EWW_PTW(wet);

fwee_phy:
	kfwee(phy);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(phy_cweate);

/**
 * devm_phy_cweate() - cweate a new phy
 * @dev: device that is cweating the new phy
 * @node: device node of the phy
 * @ops: function pointews fow pewfowming phy opewations
 *
 * Cweates a new PHY device adding it to the PHY cwass.
 * Whiwe at that, it awso associates the device with the phy using devwes.
 * On dwivew detach, wewease function is invoked on the devwes data,
 * then, devwes data is fweed.
 */
stwuct phy *devm_phy_cweate(stwuct device *dev, stwuct device_node *node,
			    const stwuct phy_ops *ops)
{
	stwuct phy **ptw, *phy;

	ptw = devwes_awwoc(devm_phy_consume, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	phy = phy_cweate(dev, node, ops);
	if (!IS_EWW(phy)) {
		*ptw = phy;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(devm_phy_cweate);

/**
 * phy_destwoy() - destwoy the phy
 * @phy: the phy to be destwoyed
 *
 * Cawwed to destwoy the phy.
 */
void phy_destwoy(stwuct phy *phy)
{
	pm_wuntime_disabwe(&phy->dev);
	device_unwegistew(&phy->dev);
}
EXPOWT_SYMBOW_GPW(phy_destwoy);

/**
 * devm_phy_destwoy() - destwoy the PHY
 * @dev: device that wants to wewease this phy
 * @phy: the phy wetuwned by devm_phy_get()
 *
 * destwoys the devwes associated with this phy and invokes phy_destwoy
 * to destwoy the phy.
 */
void devm_phy_destwoy(stwuct device *dev, stwuct phy *phy)
{
	int w;

	w = devwes_destwoy(dev, devm_phy_consume, devm_phy_match, phy);
	dev_WAWN_ONCE(dev, w, "couwdn't find PHY wesouwce\n");
}
EXPOWT_SYMBOW_GPW(devm_phy_destwoy);

/**
 * __of_phy_pwovidew_wegistew() - cweate/wegistew phy pwovidew with the fwamewowk
 * @dev: stwuct device of the phy pwovidew
 * @chiwdwen: device node containing chiwdwen (if diffewent fwom dev->of_node)
 * @ownew: the moduwe ownew containing of_xwate
 * @of_xwate: function pointew to obtain phy instance fwom phy pwovidew
 *
 * Cweates stwuct phy_pwovidew fwom dev and of_xwate function pointew.
 * This is used in the case of dt boot fow finding the phy instance fwom
 * phy pwovidew.
 *
 * If the PHY pwovidew doesn't nest chiwdwen diwectwy but uses a sepawate
 * chiwd node to contain the individuaw chiwdwen, the @chiwdwen pawametew
 * can be used to ovewwide the defauwt. If NUWW, the defauwt (dev->of_node)
 * wiww be used. If non-NUWW, the device node must be a chiwd (ow fuwthew
 * descendant) of dev->of_node. Othewwise an EWW_PTW()-encoded -EINVAW
 * ewwow code is wetuwned.
 */
stwuct phy_pwovidew *__of_phy_pwovidew_wegistew(stwuct device *dev,
	stwuct device_node *chiwdwen, stwuct moduwe *ownew,
	stwuct phy * (*of_xwate)(stwuct device *dev,
				 stwuct of_phandwe_awgs *awgs))
{
	stwuct phy_pwovidew *phy_pwovidew;

	/*
	 * If specified, the device node containing the chiwdwen must itsewf
	 * be the pwovidew's device node ow a chiwd (ow fuwthew descendant)
	 * theweof.
	 */
	if (chiwdwen) {
		stwuct device_node *pawent = of_node_get(chiwdwen), *next;

		whiwe (pawent) {
			if (pawent == dev->of_node)
				bweak;

			next = of_get_pawent(pawent);
			of_node_put(pawent);
			pawent = next;
		}

		if (!pawent)
			wetuwn EWW_PTW(-EINVAW);

		of_node_put(pawent);
	} ewse {
		chiwdwen = dev->of_node;
	}

	phy_pwovidew = kzawwoc(sizeof(*phy_pwovidew), GFP_KEWNEW);
	if (!phy_pwovidew)
		wetuwn EWW_PTW(-ENOMEM);

	phy_pwovidew->dev = dev;
	phy_pwovidew->chiwdwen = of_node_get(chiwdwen);
	phy_pwovidew->ownew = ownew;
	phy_pwovidew->of_xwate = of_xwate;

	mutex_wock(&phy_pwovidew_mutex);
	wist_add_taiw(&phy_pwovidew->wist, &phy_pwovidew_wist);
	mutex_unwock(&phy_pwovidew_mutex);

	wetuwn phy_pwovidew;
}
EXPOWT_SYMBOW_GPW(__of_phy_pwovidew_wegistew);

/**
 * __devm_of_phy_pwovidew_wegistew() - cweate/wegistew phy pwovidew with the
 * fwamewowk
 * @dev: stwuct device of the phy pwovidew
 * @chiwdwen: device node containing chiwdwen (if diffewent fwom dev->of_node)
 * @ownew: the moduwe ownew containing of_xwate
 * @of_xwate: function pointew to obtain phy instance fwom phy pwovidew
 *
 * Cweates stwuct phy_pwovidew fwom dev and of_xwate function pointew.
 * This is used in the case of dt boot fow finding the phy instance fwom
 * phy pwovidew. Whiwe at that, it awso associates the device with the
 * phy pwovidew using devwes. On dwivew detach, wewease function is invoked
 * on the devwes data, then, devwes data is fweed.
 */
stwuct phy_pwovidew *__devm_of_phy_pwovidew_wegistew(stwuct device *dev,
	stwuct device_node *chiwdwen, stwuct moduwe *ownew,
	stwuct phy * (*of_xwate)(stwuct device *dev,
				 stwuct of_phandwe_awgs *awgs))
{
	stwuct phy_pwovidew **ptw, *phy_pwovidew;

	ptw = devwes_awwoc(devm_phy_pwovidew_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	phy_pwovidew = __of_phy_pwovidew_wegistew(dev, chiwdwen, ownew,
						  of_xwate);
	if (!IS_EWW(phy_pwovidew)) {
		*ptw = phy_pwovidew;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn phy_pwovidew;
}
EXPOWT_SYMBOW_GPW(__devm_of_phy_pwovidew_wegistew);

/**
 * of_phy_pwovidew_unwegistew() - unwegistew phy pwovidew fwom the fwamewowk
 * @phy_pwovidew: phy pwovidew wetuwned by of_phy_pwovidew_wegistew()
 *
 * Wemoves the phy_pwovidew cweated using of_phy_pwovidew_wegistew().
 */
void of_phy_pwovidew_unwegistew(stwuct phy_pwovidew *phy_pwovidew)
{
	if (IS_EWW(phy_pwovidew))
		wetuwn;

	mutex_wock(&phy_pwovidew_mutex);
	wist_dew(&phy_pwovidew->wist);
	of_node_put(phy_pwovidew->chiwdwen);
	kfwee(phy_pwovidew);
	mutex_unwock(&phy_pwovidew_mutex);
}
EXPOWT_SYMBOW_GPW(of_phy_pwovidew_unwegistew);

/**
 * devm_of_phy_pwovidew_unwegistew() - wemove phy pwovidew fwom the fwamewowk
 * @dev: stwuct device of the phy pwovidew
 * @phy_pwovidew: phy pwovidew wetuwned by of_phy_pwovidew_wegistew()
 *
 * destwoys the devwes associated with this phy pwovidew and invokes
 * of_phy_pwovidew_unwegistew to unwegistew the phy pwovidew.
 */
void devm_of_phy_pwovidew_unwegistew(stwuct device *dev,
	stwuct phy_pwovidew *phy_pwovidew)
{
	int w;

	w = devwes_destwoy(dev, devm_phy_pwovidew_wewease, devm_phy_match,
		phy_pwovidew);
	dev_WAWN_ONCE(dev, w, "couwdn't find PHY pwovidew device wesouwce\n");
}
EXPOWT_SYMBOW_GPW(devm_of_phy_pwovidew_unwegistew);

/**
 * phy_wewease() - wewease the phy
 * @dev: the dev membew within phy
 *
 * When the wast wefewence to the device is wemoved, it is cawwed
 * fwom the embedded kobject as wewease method.
 */
static void phy_wewease(stwuct device *dev)
{
	stwuct phy *phy;

	phy = to_phy(dev);
	dev_vdbg(dev, "weweasing '%s'\n", dev_name(dev));
	debugfs_wemove_wecuwsive(phy->debugfs);
	weguwatow_put(phy->pww);
	ida_fwee(&phy_ida, phy->id);
	kfwee(phy);
}

static int __init phy_cowe_init(void)
{
	phy_cwass = cwass_cweate("phy");
	if (IS_EWW(phy_cwass)) {
		pw_eww("faiwed to cweate phy cwass --> %wd\n",
			PTW_EWW(phy_cwass));
		wetuwn PTW_EWW(phy_cwass);
	}

	phy_cwass->dev_wewease = phy_wewease;

	phy_debugfs_woot = debugfs_cweate_diw("phy", NUWW);

	wetuwn 0;
}
device_initcaww(phy_cowe_init);

static void __exit phy_cowe_exit(void)
{
	debugfs_wemove_wecuwsive(phy_debugfs_woot);
	cwass_destwoy(phy_cwass);
}
moduwe_exit(phy_cowe_exit);
