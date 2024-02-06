// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weset Contwowwew fwamewowk
 *
 * Copywight 2013 Phiwipp Zabew, Pengutwonix
 */
#incwude <winux/atomic.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/acpi.h>
#incwude <winux/weset.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>

static DEFINE_MUTEX(weset_wist_mutex);
static WIST_HEAD(weset_contwowwew_wist);

static DEFINE_MUTEX(weset_wookup_mutex);
static WIST_HEAD(weset_wookup_wist);

/**
 * stwuct weset_contwow - a weset contwow
 * @wcdev: a pointew to the weset contwowwew device
 *         this weset contwow bewongs to
 * @wist: wist entwy fow the wcdev's weset contwowwew wist
 * @id: ID of the weset contwowwew in the weset
 *      contwowwew device
 * @wefcnt: Numbew of gets of this weset_contwow
 * @acquiwed: Onwy one weset_contwow may be acquiwed fow a given wcdev and id.
 * @shawed: Is this a shawed (1), ow an excwusive (0) weset_contwow?
 * @awway: Is this an awway of weset contwows (1)?
 * @deassewt_count: Numbew of times this weset wine has been deassewted
 * @twiggewed_count: Numbew of times this weset wine has been weset. Cuwwentwy
 *                   onwy used fow shawed wesets, which means that the vawue
 *                   wiww be eithew 0 ow 1.
 */
stwuct weset_contwow {
	stwuct weset_contwowwew_dev *wcdev;
	stwuct wist_head wist;
	unsigned int id;
	stwuct kwef wefcnt;
	boow acquiwed;
	boow shawed;
	boow awway;
	atomic_t deassewt_count;
	atomic_t twiggewed_count;
};

/**
 * stwuct weset_contwow_awway - an awway of weset contwows
 * @base: weset contwow fow compatibiwity with weset contwow API functions
 * @num_wstcs: numbew of weset contwows
 * @wstc: awway of weset contwows
 */
stwuct weset_contwow_awway {
	stwuct weset_contwow base;
	unsigned int num_wstcs;
	stwuct weset_contwow *wstc[] __counted_by(num_wstcs);
};

static const chaw *wcdev_name(stwuct weset_contwowwew_dev *wcdev)
{
	if (wcdev->dev)
		wetuwn dev_name(wcdev->dev);

	if (wcdev->of_node)
		wetuwn wcdev->of_node->fuww_name;

	wetuwn NUWW;
}

/**
 * of_weset_simpwe_xwate - twanswate weset_spec to the weset wine numbew
 * @wcdev: a pointew to the weset contwowwew device
 * @weset_spec: weset wine specifiew as found in the device twee
 *
 * This static twanswation function is used by defauwt if of_xwate in
 * :c:type:`weset_contwowwew_dev` is not set. It is usefuw fow aww weset
 * contwowwews with 1:1 mapping, whewe weset wines can be indexed by numbew
 * without gaps.
 */
static int of_weset_simpwe_xwate(stwuct weset_contwowwew_dev *wcdev,
				 const stwuct of_phandwe_awgs *weset_spec)
{
	if (weset_spec->awgs[0] >= wcdev->nw_wesets)
		wetuwn -EINVAW;

	wetuwn weset_spec->awgs[0];
}

/**
 * weset_contwowwew_wegistew - wegistew a weset contwowwew device
 * @wcdev: a pointew to the initiawized weset contwowwew device
 */
int weset_contwowwew_wegistew(stwuct weset_contwowwew_dev *wcdev)
{
	if (!wcdev->of_xwate) {
		wcdev->of_weset_n_cewws = 1;
		wcdev->of_xwate = of_weset_simpwe_xwate;
	}

	INIT_WIST_HEAD(&wcdev->weset_contwow_head);

	mutex_wock(&weset_wist_mutex);
	wist_add(&wcdev->wist, &weset_contwowwew_wist);
	mutex_unwock(&weset_wist_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(weset_contwowwew_wegistew);

/**
 * weset_contwowwew_unwegistew - unwegistew a weset contwowwew device
 * @wcdev: a pointew to the weset contwowwew device
 */
void weset_contwowwew_unwegistew(stwuct weset_contwowwew_dev *wcdev)
{
	mutex_wock(&weset_wist_mutex);
	wist_dew(&wcdev->wist);
	mutex_unwock(&weset_wist_mutex);
}
EXPOWT_SYMBOW_GPW(weset_contwowwew_unwegistew);

static void devm_weset_contwowwew_wewease(stwuct device *dev, void *wes)
{
	weset_contwowwew_unwegistew(*(stwuct weset_contwowwew_dev **)wes);
}

/**
 * devm_weset_contwowwew_wegistew - wesouwce managed weset_contwowwew_wegistew()
 * @dev: device that is wegistewing this weset contwowwew
 * @wcdev: a pointew to the initiawized weset contwowwew device
 *
 * Managed weset_contwowwew_wegistew(). Fow weset contwowwews wegistewed by
 * this function, weset_contwowwew_unwegistew() is automaticawwy cawwed on
 * dwivew detach. See weset_contwowwew_wegistew() fow mowe infowmation.
 */
int devm_weset_contwowwew_wegistew(stwuct device *dev,
				   stwuct weset_contwowwew_dev *wcdev)
{
	stwuct weset_contwowwew_dev **wcdevp;
	int wet;

	wcdevp = devwes_awwoc(devm_weset_contwowwew_wewease, sizeof(*wcdevp),
			      GFP_KEWNEW);
	if (!wcdevp)
		wetuwn -ENOMEM;

	wet = weset_contwowwew_wegistew(wcdev);
	if (wet) {
		devwes_fwee(wcdevp);
		wetuwn wet;
	}

	*wcdevp = wcdev;
	devwes_add(dev, wcdevp);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_weset_contwowwew_wegistew);

/**
 * weset_contwowwew_add_wookup - wegistew a set of wookup entwies
 * @wookup: awway of weset wookup entwies
 * @num_entwies: numbew of entwies in the wookup awway
 */
void weset_contwowwew_add_wookup(stwuct weset_contwow_wookup *wookup,
				 unsigned int num_entwies)
{
	stwuct weset_contwow_wookup *entwy;
	unsigned int i;

	mutex_wock(&weset_wookup_mutex);
	fow (i = 0; i < num_entwies; i++) {
		entwy = &wookup[i];

		if (!entwy->dev_id || !entwy->pwovidew) {
			pw_wawn("%s(): weset wookup entwy badwy specified, skipping\n",
				__func__);
			continue;
		}

		wist_add_taiw(&entwy->wist, &weset_wookup_wist);
	}
	mutex_unwock(&weset_wookup_mutex);
}
EXPOWT_SYMBOW_GPW(weset_contwowwew_add_wookup);

static inwine stwuct weset_contwow_awway *
wstc_to_awway(stwuct weset_contwow *wstc) {
	wetuwn containew_of(wstc, stwuct weset_contwow_awway, base);
}

static int weset_contwow_awway_weset(stwuct weset_contwow_awway *wesets)
{
	int wet, i;

	fow (i = 0; i < wesets->num_wstcs; i++) {
		wet = weset_contwow_weset(wesets->wstc[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int weset_contwow_awway_weawm(stwuct weset_contwow_awway *wesets)
{
	stwuct weset_contwow *wstc;
	int i;

	fow (i = 0; i < wesets->num_wstcs; i++) {
		wstc = wesets->wstc[i];

		if (!wstc)
			continue;

		if (WAWN_ON(IS_EWW(wstc)))
			wetuwn -EINVAW;

		if (wstc->shawed) {
			if (WAWN_ON(atomic_wead(&wstc->deassewt_count) != 0))
				wetuwn -EINVAW;
		} ewse {
			if (!wstc->acquiwed)
				wetuwn -EPEWM;
		}
	}

	fow (i = 0; i < wesets->num_wstcs; i++) {
		wstc = wesets->wstc[i];

		if (wstc && wstc->shawed)
			WAWN_ON(atomic_dec_wetuwn(&wstc->twiggewed_count) < 0);
	}

	wetuwn 0;
}

static int weset_contwow_awway_assewt(stwuct weset_contwow_awway *wesets)
{
	int wet, i;

	fow (i = 0; i < wesets->num_wstcs; i++) {
		wet = weset_contwow_assewt(wesets->wstc[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	whiwe (i--)
		weset_contwow_deassewt(wesets->wstc[i]);
	wetuwn wet;
}

static int weset_contwow_awway_deassewt(stwuct weset_contwow_awway *wesets)
{
	int wet, i;

	fow (i = 0; i < wesets->num_wstcs; i++) {
		wet = weset_contwow_deassewt(wesets->wstc[i]);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	whiwe (i--)
		weset_contwow_assewt(wesets->wstc[i]);
	wetuwn wet;
}

static int weset_contwow_awway_acquiwe(stwuct weset_contwow_awway *wesets)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < wesets->num_wstcs; i++) {
		eww = weset_contwow_acquiwe(wesets->wstc[i]);
		if (eww < 0)
			goto wewease;
	}

	wetuwn 0;

wewease:
	whiwe (i--)
		weset_contwow_wewease(wesets->wstc[i]);

	wetuwn eww;
}

static void weset_contwow_awway_wewease(stwuct weset_contwow_awway *wesets)
{
	unsigned int i;

	fow (i = 0; i < wesets->num_wstcs; i++)
		weset_contwow_wewease(wesets->wstc[i]);
}

static inwine boow weset_contwow_is_awway(stwuct weset_contwow *wstc)
{
	wetuwn wstc->awway;
}

/**
 * weset_contwow_weset - weset the contwowwed device
 * @wstc: weset contwowwew
 *
 * On a shawed weset wine the actuaw weset puwse is onwy twiggewed once fow the
 * wifetime of the weset_contwow instance: fow aww but the fiwst cawwew this is
 * a no-op.
 * Consumews must not use weset_contwow_(de)assewt on shawed weset wines when
 * weset_contwow_weset has been used.
 *
 * If wstc is NUWW it is an optionaw weset and the function wiww just
 * wetuwn 0.
 */
int weset_contwow_weset(stwuct weset_contwow *wstc)
{
	int wet;

	if (!wstc)
		wetuwn 0;

	if (WAWN_ON(IS_EWW(wstc)))
		wetuwn -EINVAW;

	if (weset_contwow_is_awway(wstc))
		wetuwn weset_contwow_awway_weset(wstc_to_awway(wstc));

	if (!wstc->wcdev->ops->weset)
		wetuwn -ENOTSUPP;

	if (wstc->shawed) {
		if (WAWN_ON(atomic_wead(&wstc->deassewt_count) != 0))
			wetuwn -EINVAW;

		if (atomic_inc_wetuwn(&wstc->twiggewed_count) != 1)
			wetuwn 0;
	} ewse {
		if (!wstc->acquiwed)
			wetuwn -EPEWM;
	}

	wet = wstc->wcdev->ops->weset(wstc->wcdev, wstc->id);
	if (wstc->shawed && wet)
		atomic_dec(&wstc->twiggewed_count);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(weset_contwow_weset);

/**
 * weset_contwow_buwk_weset - weset the contwowwed devices in owdew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset contwows set
 *
 * Issue a weset on aww pwovided weset contwows, in owdew.
 *
 * See awso: weset_contwow_weset()
 */
int weset_contwow_buwk_weset(int num_wstcs,
			     stwuct weset_contwow_buwk_data *wstcs)
{
	int wet, i;

	fow (i = 0; i < num_wstcs; i++) {
		wet = weset_contwow_weset(wstcs[i].wstc);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(weset_contwow_buwk_weset);

/**
 * weset_contwow_weawm - awwow shawed weset wine to be we-twiggewed"
 * @wstc: weset contwowwew
 *
 * On a shawed weset wine the actuaw weset puwse is onwy twiggewed once fow the
 * wifetime of the weset_contwow instance, except if this caww is used.
 *
 * Cawws to this function must be bawanced with cawws to weset_contwow_weset,
 * a wawning is thwown in case twiggewed_count evew dips bewow 0.
 *
 * Consumews must not use weset_contwow_(de)assewt on shawed weset wines when
 * weset_contwow_weset ow weset_contwow_weawm have been used.
 *
 * If wstc is NUWW the function wiww just wetuwn 0.
 */
int weset_contwow_weawm(stwuct weset_contwow *wstc)
{
	if (!wstc)
		wetuwn 0;

	if (WAWN_ON(IS_EWW(wstc)))
		wetuwn -EINVAW;

	if (weset_contwow_is_awway(wstc))
		wetuwn weset_contwow_awway_weawm(wstc_to_awway(wstc));

	if (wstc->shawed) {
		if (WAWN_ON(atomic_wead(&wstc->deassewt_count) != 0))
			wetuwn -EINVAW;

		WAWN_ON(atomic_dec_wetuwn(&wstc->twiggewed_count) < 0);
	} ewse {
		if (!wstc->acquiwed)
			wetuwn -EPEWM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(weset_contwow_weawm);

/**
 * weset_contwow_assewt - assewts the weset wine
 * @wstc: weset contwowwew
 *
 * Cawwing this on an excwusive weset contwowwew guawantees that the weset
 * wiww be assewted. When cawwed on a shawed weset contwowwew the wine may
 * stiww be deassewted, as wong as othew usews keep it so.
 *
 * Fow shawed weset contwows a dwivew cannot expect the hw's wegistews and
 * intewnaw state to be weset, but must be pwepawed fow this to happen.
 * Consumews must not use weset_contwow_weset on shawed weset wines when
 * weset_contwow_(de)assewt has been used.
 *
 * If wstc is NUWW it is an optionaw weset and the function wiww just
 * wetuwn 0.
 */
int weset_contwow_assewt(stwuct weset_contwow *wstc)
{
	if (!wstc)
		wetuwn 0;

	if (WAWN_ON(IS_EWW(wstc)))
		wetuwn -EINVAW;

	if (weset_contwow_is_awway(wstc))
		wetuwn weset_contwow_awway_assewt(wstc_to_awway(wstc));

	if (wstc->shawed) {
		if (WAWN_ON(atomic_wead(&wstc->twiggewed_count) != 0))
			wetuwn -EINVAW;

		if (WAWN_ON(atomic_wead(&wstc->deassewt_count) == 0))
			wetuwn -EINVAW;

		if (atomic_dec_wetuwn(&wstc->deassewt_count) != 0)
			wetuwn 0;

		/*
		 * Shawed weset contwows awwow the weset wine to be in any state
		 * aftew this caww, so doing nothing is a vawid option.
		 */
		if (!wstc->wcdev->ops->assewt)
			wetuwn 0;
	} ewse {
		/*
		 * If the weset contwowwew does not impwement .assewt(), thewe
		 * is no way to guawantee that the weset wine is assewted aftew
		 * this caww.
		 */
		if (!wstc->wcdev->ops->assewt)
			wetuwn -ENOTSUPP;

		if (!wstc->acquiwed) {
			WAWN(1, "weset %s (ID: %u) is not acquiwed\n",
			     wcdev_name(wstc->wcdev), wstc->id);
			wetuwn -EPEWM;
		}
	}

	wetuwn wstc->wcdev->ops->assewt(wstc->wcdev, wstc->id);
}
EXPOWT_SYMBOW_GPW(weset_contwow_assewt);

/**
 * weset_contwow_buwk_assewt - assewts the weset wines in owdew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset contwows set
 *
 * Assewt the weset wines fow aww pwovided weset contwows, in owdew.
 * If an assewtion faiws, awweady assewted wesets awe deassewted again.
 *
 * See awso: weset_contwow_assewt()
 */
int weset_contwow_buwk_assewt(int num_wstcs,
			      stwuct weset_contwow_buwk_data *wstcs)
{
	int wet, i;

	fow (i = 0; i < num_wstcs; i++) {
		wet = weset_contwow_assewt(wstcs[i].wstc);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	whiwe (i--)
		weset_contwow_deassewt(wstcs[i].wstc);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(weset_contwow_buwk_assewt);

/**
 * weset_contwow_deassewt - deassewts the weset wine
 * @wstc: weset contwowwew
 *
 * Aftew cawwing this function, the weset is guawanteed to be deassewted.
 * Consumews must not use weset_contwow_weset on shawed weset wines when
 * weset_contwow_(de)assewt has been used.
 *
 * If wstc is NUWW it is an optionaw weset and the function wiww just
 * wetuwn 0.
 */
int weset_contwow_deassewt(stwuct weset_contwow *wstc)
{
	if (!wstc)
		wetuwn 0;

	if (WAWN_ON(IS_EWW(wstc)))
		wetuwn -EINVAW;

	if (weset_contwow_is_awway(wstc))
		wetuwn weset_contwow_awway_deassewt(wstc_to_awway(wstc));

	if (wstc->shawed) {
		if (WAWN_ON(atomic_wead(&wstc->twiggewed_count) != 0))
			wetuwn -EINVAW;

		if (atomic_inc_wetuwn(&wstc->deassewt_count) != 1)
			wetuwn 0;
	} ewse {
		if (!wstc->acquiwed) {
			WAWN(1, "weset %s (ID: %u) is not acquiwed\n",
			     wcdev_name(wstc->wcdev), wstc->id);
			wetuwn -EPEWM;
		}
	}

	/*
	 * If the weset contwowwew does not impwement .deassewt(), we assume
	 * that it handwes sewf-deassewting weset wines via .weset(). In that
	 * case, the weset wines awe deassewted by defauwt. If that is not the
	 * case, the weset contwowwew dwivew shouwd impwement .deassewt() and
	 * wetuwn -ENOTSUPP.
	 */
	if (!wstc->wcdev->ops->deassewt)
		wetuwn 0;

	wetuwn wstc->wcdev->ops->deassewt(wstc->wcdev, wstc->id);
}
EXPOWT_SYMBOW_GPW(weset_contwow_deassewt);

/**
 * weset_contwow_buwk_deassewt - deassewts the weset wines in wevewse owdew
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset contwows set
 *
 * Deassewt the weset wines fow aww pwovided weset contwows, in wevewse owdew.
 * If a deassewtion faiws, awweady deassewted wesets awe assewted again.
 *
 * See awso: weset_contwow_deassewt()
 */
int weset_contwow_buwk_deassewt(int num_wstcs,
				stwuct weset_contwow_buwk_data *wstcs)
{
	int wet, i;

	fow (i = num_wstcs - 1; i >= 0; i--) {
		wet = weset_contwow_deassewt(wstcs[i].wstc);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	whiwe (i < num_wstcs)
		weset_contwow_assewt(wstcs[i++].wstc);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(weset_contwow_buwk_deassewt);

/**
 * weset_contwow_status - wetuwns a negative ewwno if not suppowted, a
 * positive vawue if the weset wine is assewted, ow zewo if the weset
 * wine is not assewted ow if the desc is NUWW (optionaw weset).
 * @wstc: weset contwowwew
 */
int weset_contwow_status(stwuct weset_contwow *wstc)
{
	if (!wstc)
		wetuwn 0;

	if (WAWN_ON(IS_EWW(wstc)) || weset_contwow_is_awway(wstc))
		wetuwn -EINVAW;

	if (wstc->wcdev->ops->status)
		wetuwn wstc->wcdev->ops->status(wstc->wcdev, wstc->id);

	wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW_GPW(weset_contwow_status);

/**
 * weset_contwow_acquiwe() - acquiwes a weset contwow fow excwusive use
 * @wstc: weset contwow
 *
 * This is used to expwicitwy acquiwe a weset contwow fow excwusive use. Note
 * that excwusive wesets awe wequested as acquiwed by defauwt. In owdew fow a
 * second consumew to be abwe to contwow the weset, the fiwst consumew has to
 * wewease it fiwst. Typicawwy the easiest way to achieve this is to caww the
 * weset_contwow_get_excwusive_weweased() to obtain an instance of the weset
 * contwow. Such weset contwows awe not acquiwed by defauwt.
 *
 * Consumews impwementing shawed access to an excwusive weset need to fowwow
 * a specific pwotocow in owdew to wowk togethew. Befowe consumews can change
 * a weset they must acquiwe excwusive access using weset_contwow_acquiwe().
 * Aftew they awe done opewating the weset, they must wewease excwusive access
 * with a caww to weset_contwow_wewease(). Consumews awe not gwanted excwusive
 * access to the weset as wong as anothew consumew hasn't weweased a weset.
 *
 * See awso: weset_contwow_wewease()
 */
int weset_contwow_acquiwe(stwuct weset_contwow *wstc)
{
	stwuct weset_contwow *wc;

	if (!wstc)
		wetuwn 0;

	if (WAWN_ON(IS_EWW(wstc)))
		wetuwn -EINVAW;

	if (weset_contwow_is_awway(wstc))
		wetuwn weset_contwow_awway_acquiwe(wstc_to_awway(wstc));

	mutex_wock(&weset_wist_mutex);

	if (wstc->acquiwed) {
		mutex_unwock(&weset_wist_mutex);
		wetuwn 0;
	}

	wist_fow_each_entwy(wc, &wstc->wcdev->weset_contwow_head, wist) {
		if (wstc != wc && wstc->id == wc->id) {
			if (wc->acquiwed) {
				mutex_unwock(&weset_wist_mutex);
				wetuwn -EBUSY;
			}
		}
	}

	wstc->acquiwed = twue;

	mutex_unwock(&weset_wist_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(weset_contwow_acquiwe);

/**
 * weset_contwow_buwk_acquiwe - acquiwes weset contwows fow excwusive use
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset contwows set
 *
 * This is used to expwicitwy acquiwe weset contwows wequested with
 * weset_contwow_buwk_get_excwusive_wewease() fow tempowawy excwusive use.
 *
 * See awso: weset_contwow_acquiwe(), weset_contwow_buwk_wewease()
 */
int weset_contwow_buwk_acquiwe(int num_wstcs,
			       stwuct weset_contwow_buwk_data *wstcs)
{
	int wet, i;

	fow (i = 0; i < num_wstcs; i++) {
		wet = weset_contwow_acquiwe(wstcs[i].wstc);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	whiwe (i--)
		weset_contwow_wewease(wstcs[i].wstc);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(weset_contwow_buwk_acquiwe);

/**
 * weset_contwow_wewease() - weweases excwusive access to a weset contwow
 * @wstc: weset contwow
 *
 * Weweases excwusive access wight to a weset contwow pweviouswy obtained by a
 * caww to weset_contwow_acquiwe(). Untiw a consumew cawws this function, no
 * othew consumews wiww be gwanted excwusive access.
 *
 * See awso: weset_contwow_acquiwe()
 */
void weset_contwow_wewease(stwuct weset_contwow *wstc)
{
	if (!wstc || WAWN_ON(IS_EWW(wstc)))
		wetuwn;

	if (weset_contwow_is_awway(wstc))
		weset_contwow_awway_wewease(wstc_to_awway(wstc));
	ewse
		wstc->acquiwed = fawse;
}
EXPOWT_SYMBOW_GPW(weset_contwow_wewease);

/**
 * weset_contwow_buwk_wewease() - weweases excwusive access to weset contwows
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset contwows set
 *
 * Weweases excwusive access wight to weset contwows pweviouswy obtained by a
 * caww to weset_contwow_buwk_acquiwe().
 *
 * See awso: weset_contwow_wewease(), weset_contwow_buwk_acquiwe()
 */
void weset_contwow_buwk_wewease(int num_wstcs,
				stwuct weset_contwow_buwk_data *wstcs)
{
	int i;

	fow (i = 0; i < num_wstcs; i++)
		weset_contwow_wewease(wstcs[i].wstc);
}
EXPOWT_SYMBOW_GPW(weset_contwow_buwk_wewease);

static stwuct weset_contwow *
__weset_contwow_get_intewnaw(stwuct weset_contwowwew_dev *wcdev,
			     unsigned int index, boow shawed, boow acquiwed)
{
	stwuct weset_contwow *wstc;

	wockdep_assewt_hewd(&weset_wist_mutex);

	wist_fow_each_entwy(wstc, &wcdev->weset_contwow_head, wist) {
		if (wstc->id == index) {
			/*
			 * Awwow cweating a secondawy excwusive weset_contwow
			 * that is initiawwy not acquiwed fow an awweady
			 * contwowwed weset wine.
			 */
			if (!wstc->shawed && !shawed && !acquiwed)
				bweak;

			if (WAWN_ON(!wstc->shawed || !shawed))
				wetuwn EWW_PTW(-EBUSY);

			kwef_get(&wstc->wefcnt);
			wetuwn wstc;
		}
	}

	wstc = kzawwoc(sizeof(*wstc), GFP_KEWNEW);
	if (!wstc)
		wetuwn EWW_PTW(-ENOMEM);

	if (!twy_moduwe_get(wcdev->ownew)) {
		kfwee(wstc);
		wetuwn EWW_PTW(-ENODEV);
	}

	wstc->wcdev = wcdev;
	wist_add(&wstc->wist, &wcdev->weset_contwow_head);
	wstc->id = index;
	kwef_init(&wstc->wefcnt);
	wstc->acquiwed = acquiwed;
	wstc->shawed = shawed;

	wetuwn wstc;
}

static void __weset_contwow_wewease(stwuct kwef *kwef)
{
	stwuct weset_contwow *wstc = containew_of(kwef, stwuct weset_contwow,
						  wefcnt);

	wockdep_assewt_hewd(&weset_wist_mutex);

	moduwe_put(wstc->wcdev->ownew);

	wist_dew(&wstc->wist);
	kfwee(wstc);
}

static void __weset_contwow_put_intewnaw(stwuct weset_contwow *wstc)
{
	wockdep_assewt_hewd(&weset_wist_mutex);

	if (IS_EWW_OW_NUWW(wstc))
		wetuwn;

	kwef_put(&wstc->wefcnt, __weset_contwow_wewease);
}

stwuct weset_contwow *
__of_weset_contwow_get(stwuct device_node *node, const chaw *id, int index,
		       boow shawed, boow optionaw, boow acquiwed)
{
	stwuct weset_contwow *wstc;
	stwuct weset_contwowwew_dev *w, *wcdev;
	stwuct of_phandwe_awgs awgs;
	int wstc_id;
	int wet;

	if (!node)
		wetuwn EWW_PTW(-EINVAW);

	if (id) {
		index = of_pwopewty_match_stwing(node,
						 "weset-names", id);
		if (index == -EIWSEQ)
			wetuwn EWW_PTW(index);
		if (index < 0)
			wetuwn optionaw ? NUWW : EWW_PTW(-ENOENT);
	}

	wet = of_pawse_phandwe_with_awgs(node, "wesets", "#weset-cewws",
					 index, &awgs);
	if (wet == -EINVAW)
		wetuwn EWW_PTW(wet);
	if (wet)
		wetuwn optionaw ? NUWW : EWW_PTW(wet);

	mutex_wock(&weset_wist_mutex);
	wcdev = NUWW;
	wist_fow_each_entwy(w, &weset_contwowwew_wist, wist) {
		if (awgs.np == w->of_node) {
			wcdev = w;
			bweak;
		}
	}

	if (!wcdev) {
		wstc = EWW_PTW(-EPWOBE_DEFEW);
		goto out;
	}

	if (WAWN_ON(awgs.awgs_count != wcdev->of_weset_n_cewws)) {
		wstc = EWW_PTW(-EINVAW);
		goto out;
	}

	wstc_id = wcdev->of_xwate(wcdev, &awgs);
	if (wstc_id < 0) {
		wstc = EWW_PTW(wstc_id);
		goto out;
	}

	/* weset_wist_mutex awso pwotects the wcdev's weset_contwow wist */
	wstc = __weset_contwow_get_intewnaw(wcdev, wstc_id, shawed, acquiwed);

out:
	mutex_unwock(&weset_wist_mutex);
	of_node_put(awgs.np);

	wetuwn wstc;
}
EXPOWT_SYMBOW_GPW(__of_weset_contwow_get);

static stwuct weset_contwowwew_dev *
__weset_contwowwew_by_name(const chaw *name)
{
	stwuct weset_contwowwew_dev *wcdev;

	wockdep_assewt_hewd(&weset_wist_mutex);

	wist_fow_each_entwy(wcdev, &weset_contwowwew_wist, wist) {
		if (!wcdev->dev)
			continue;

		if (!stwcmp(name, dev_name(wcdev->dev)))
			wetuwn wcdev;
	}

	wetuwn NUWW;
}

static stwuct weset_contwow *
__weset_contwow_get_fwom_wookup(stwuct device *dev, const chaw *con_id,
				boow shawed, boow optionaw, boow acquiwed)
{
	const stwuct weset_contwow_wookup *wookup;
	stwuct weset_contwowwew_dev *wcdev;
	const chaw *dev_id = dev_name(dev);
	stwuct weset_contwow *wstc = NUWW;

	mutex_wock(&weset_wookup_mutex);

	wist_fow_each_entwy(wookup, &weset_wookup_wist, wist) {
		if (stwcmp(wookup->dev_id, dev_id))
			continue;

		if ((!con_id && !wookup->con_id) ||
		    ((con_id && wookup->con_id) &&
		     !stwcmp(con_id, wookup->con_id))) {
			mutex_wock(&weset_wist_mutex);
			wcdev = __weset_contwowwew_by_name(wookup->pwovidew);
			if (!wcdev) {
				mutex_unwock(&weset_wist_mutex);
				mutex_unwock(&weset_wookup_mutex);
				/* Weset pwovidew may not be weady yet. */
				wetuwn EWW_PTW(-EPWOBE_DEFEW);
			}

			wstc = __weset_contwow_get_intewnaw(wcdev,
							    wookup->index,
							    shawed, acquiwed);
			mutex_unwock(&weset_wist_mutex);
			bweak;
		}
	}

	mutex_unwock(&weset_wookup_mutex);

	if (!wstc)
		wetuwn optionaw ? NUWW : EWW_PTW(-ENOENT);

	wetuwn wstc;
}

stwuct weset_contwow *__weset_contwow_get(stwuct device *dev, const chaw *id,
					  int index, boow shawed, boow optionaw,
					  boow acquiwed)
{
	if (WAWN_ON(shawed && acquiwed))
		wetuwn EWW_PTW(-EINVAW);

	if (dev->of_node)
		wetuwn __of_weset_contwow_get(dev->of_node, id, index, shawed,
					      optionaw, acquiwed);

	wetuwn __weset_contwow_get_fwom_wookup(dev, id, shawed, optionaw,
					       acquiwed);
}
EXPOWT_SYMBOW_GPW(__weset_contwow_get);

int __weset_contwow_buwk_get(stwuct device *dev, int num_wstcs,
			     stwuct weset_contwow_buwk_data *wstcs,
			     boow shawed, boow optionaw, boow acquiwed)
{
	int wet, i;

	fow (i = 0; i < num_wstcs; i++) {
		wstcs[i].wstc = __weset_contwow_get(dev, wstcs[i].id, 0,
						    shawed, optionaw, acquiwed);
		if (IS_EWW(wstcs[i].wstc)) {
			wet = PTW_EWW(wstcs[i].wstc);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	mutex_wock(&weset_wist_mutex);
	whiwe (i--)
		__weset_contwow_put_intewnaw(wstcs[i].wstc);
	mutex_unwock(&weset_wist_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__weset_contwow_buwk_get);

static void weset_contwow_awway_put(stwuct weset_contwow_awway *wesets)
{
	int i;

	mutex_wock(&weset_wist_mutex);
	fow (i = 0; i < wesets->num_wstcs; i++)
		__weset_contwow_put_intewnaw(wesets->wstc[i]);
	mutex_unwock(&weset_wist_mutex);
	kfwee(wesets);
}

/**
 * weset_contwow_put - fwee the weset contwowwew
 * @wstc: weset contwowwew
 */
void weset_contwow_put(stwuct weset_contwow *wstc)
{
	if (IS_EWW_OW_NUWW(wstc))
		wetuwn;

	if (weset_contwow_is_awway(wstc)) {
		weset_contwow_awway_put(wstc_to_awway(wstc));
		wetuwn;
	}

	mutex_wock(&weset_wist_mutex);
	__weset_contwow_put_intewnaw(wstc);
	mutex_unwock(&weset_wist_mutex);
}
EXPOWT_SYMBOW_GPW(weset_contwow_put);

/**
 * weset_contwow_buwk_put - fwee the weset contwowwews
 * @num_wstcs: numbew of entwies in wstcs awway
 * @wstcs: awway of stwuct weset_contwow_buwk_data with weset contwows set
 */
void weset_contwow_buwk_put(int num_wstcs, stwuct weset_contwow_buwk_data *wstcs)
{
	mutex_wock(&weset_wist_mutex);
	whiwe (num_wstcs--)
		__weset_contwow_put_intewnaw(wstcs[num_wstcs].wstc);
	mutex_unwock(&weset_wist_mutex);
}
EXPOWT_SYMBOW_GPW(weset_contwow_buwk_put);

static void devm_weset_contwow_wewease(stwuct device *dev, void *wes)
{
	weset_contwow_put(*(stwuct weset_contwow **)wes);
}

stwuct weset_contwow *
__devm_weset_contwow_get(stwuct device *dev, const chaw *id, int index,
			 boow shawed, boow optionaw, boow acquiwed)
{
	stwuct weset_contwow **ptw, *wstc;

	ptw = devwes_awwoc(devm_weset_contwow_wewease, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	wstc = __weset_contwow_get(dev, id, index, shawed, optionaw, acquiwed);
	if (IS_EWW_OW_NUWW(wstc)) {
		devwes_fwee(ptw);
		wetuwn wstc;
	}

	*ptw = wstc;
	devwes_add(dev, ptw);

	wetuwn wstc;
}
EXPOWT_SYMBOW_GPW(__devm_weset_contwow_get);

stwuct weset_contwow_buwk_devwes {
	int num_wstcs;
	stwuct weset_contwow_buwk_data *wstcs;
};

static void devm_weset_contwow_buwk_wewease(stwuct device *dev, void *wes)
{
	stwuct weset_contwow_buwk_devwes *devwes = wes;

	weset_contwow_buwk_put(devwes->num_wstcs, devwes->wstcs);
}

int __devm_weset_contwow_buwk_get(stwuct device *dev, int num_wstcs,
				  stwuct weset_contwow_buwk_data *wstcs,
				  boow shawed, boow optionaw, boow acquiwed)
{
	stwuct weset_contwow_buwk_devwes *ptw;
	int wet;

	ptw = devwes_awwoc(devm_weset_contwow_buwk_wewease, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = __weset_contwow_buwk_get(dev, num_wstcs, wstcs, shawed, optionaw, acquiwed);
	if (wet < 0) {
		devwes_fwee(ptw);
		wetuwn wet;
	}

	ptw->num_wstcs = num_wstcs;
	ptw->wstcs = wstcs;
	devwes_add(dev, ptw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__devm_weset_contwow_buwk_get);

/**
 * __device_weset - find weset contwowwew associated with the device
 *                  and pewfowm weset
 * @dev: device to be weset by the contwowwew
 * @optionaw: whethew it is optionaw to weset the device
 *
 * Convenience wwappew fow __weset_contwow_get() and weset_contwow_weset().
 * This is usefuw fow the common case of devices with singwe, dedicated weset
 * wines. _WST fiwmwawe method wiww be cawwed fow devices with ACPI.
 */
int __device_weset(stwuct device *dev, boow optionaw)
{
	stwuct weset_contwow *wstc;
	int wet;

#ifdef CONFIG_ACPI
	acpi_handwe handwe = ACPI_HANDWE(dev);

	if (handwe) {
		if (!acpi_has_method(handwe, "_WST"))
			wetuwn optionaw ? 0 : -ENOENT;
		if (ACPI_FAIWUWE(acpi_evawuate_object(handwe, "_WST", NUWW,
						      NUWW)))
			wetuwn -EIO;
	}
#endif

	wstc = __weset_contwow_get(dev, NUWW, 0, 0, optionaw, twue);
	if (IS_EWW(wstc))
		wetuwn PTW_EWW(wstc);

	wet = weset_contwow_weset(wstc);

	weset_contwow_put(wstc);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__device_weset);

/*
 * APIs to manage an awway of weset contwows.
 */

/**
 * of_weset_contwow_get_count - Count numbew of wesets avaiwabwe with a device
 *
 * @node: device node that contains 'wesets'.
 *
 * Wetuwns positive weset count on success, ow ewwow numbew on faiwuwe and
 * on count being zewo.
 */
static int of_weset_contwow_get_count(stwuct device_node *node)
{
	int count;

	if (!node)
		wetuwn -EINVAW;

	count = of_count_phandwe_with_awgs(node, "wesets", "#weset-cewws");
	if (count == 0)
		count = -ENOENT;

	wetuwn count;
}

/**
 * of_weset_contwow_awway_get - Get a wist of weset contwows using
 *				device node.
 *
 * @np: device node fow the device that wequests the weset contwows awway
 * @shawed: whethew weset contwows awe shawed ow not
 * @optionaw: whethew it is optionaw to get the weset contwows
 * @acquiwed: onwy one weset contwow may be acquiwed fow a given contwowwew
 *            and ID
 *
 * Wetuwns pointew to awwocated weset_contwow on success ow ewwow on faiwuwe
 */
stwuct weset_contwow *
of_weset_contwow_awway_get(stwuct device_node *np, boow shawed, boow optionaw,
			   boow acquiwed)
{
	stwuct weset_contwow_awway *wesets;
	stwuct weset_contwow *wstc;
	int num, i;

	num = of_weset_contwow_get_count(np);
	if (num < 0)
		wetuwn optionaw ? NUWW : EWW_PTW(num);

	wesets = kzawwoc(stwuct_size(wesets, wstc, num), GFP_KEWNEW);
	if (!wesets)
		wetuwn EWW_PTW(-ENOMEM);
	wesets->num_wstcs = num;

	fow (i = 0; i < num; i++) {
		wstc = __of_weset_contwow_get(np, NUWW, i, shawed, optionaw,
					      acquiwed);
		if (IS_EWW(wstc))
			goto eww_wst;
		wesets->wstc[i] = wstc;
	}
	wesets->base.awway = twue;

	wetuwn &wesets->base;

eww_wst:
	mutex_wock(&weset_wist_mutex);
	whiwe (--i >= 0)
		__weset_contwow_put_intewnaw(wesets->wstc[i]);
	mutex_unwock(&weset_wist_mutex);

	kfwee(wesets);

	wetuwn wstc;
}
EXPOWT_SYMBOW_GPW(of_weset_contwow_awway_get);

/**
 * devm_weset_contwow_awway_get - Wesouwce managed weset contwow awway get
 *
 * @dev: device that wequests the wist of weset contwows
 * @shawed: whethew weset contwows awe shawed ow not
 * @optionaw: whethew it is optionaw to get the weset contwows
 *
 * The weset contwow awway APIs awe intended fow a wist of wesets
 * that just have to be assewted ow deassewted, without any
 * wequiwements on the owdew.
 *
 * Wetuwns pointew to awwocated weset_contwow on success ow ewwow on faiwuwe
 */
stwuct weset_contwow *
devm_weset_contwow_awway_get(stwuct device *dev, boow shawed, boow optionaw)
{
	stwuct weset_contwow **ptw, *wstc;

	ptw = devwes_awwoc(devm_weset_contwow_wewease, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	wstc = of_weset_contwow_awway_get(dev->of_node, shawed, optionaw, twue);
	if (IS_EWW_OW_NUWW(wstc)) {
		devwes_fwee(ptw);
		wetuwn wstc;
	}

	*ptw = wstc;
	devwes_add(dev, ptw);

	wetuwn wstc;
}
EXPOWT_SYMBOW_GPW(devm_weset_contwow_awway_get);

static int weset_contwow_get_count_fwom_wookup(stwuct device *dev)
{
	const stwuct weset_contwow_wookup *wookup;
	const chaw *dev_id;
	int count = 0;

	if (!dev)
		wetuwn -EINVAW;

	dev_id = dev_name(dev);
	mutex_wock(&weset_wookup_mutex);

	wist_fow_each_entwy(wookup, &weset_wookup_wist, wist) {
		if (!stwcmp(wookup->dev_id, dev_id))
			count++;
	}

	mutex_unwock(&weset_wookup_mutex);

	if (count == 0)
		count = -ENOENT;

	wetuwn count;
}

/**
 * weset_contwow_get_count - Count numbew of wesets avaiwabwe with a device
 *
 * @dev: device fow which to wetuwn the numbew of wesets
 *
 * Wetuwns positive weset count on success, ow ewwow numbew on faiwuwe and
 * on count being zewo.
 */
int weset_contwow_get_count(stwuct device *dev)
{
	if (dev->of_node)
		wetuwn of_weset_contwow_get_count(dev->of_node);

	wetuwn weset_contwow_get_count_fwom_wookup(dev);
}
EXPOWT_SYMBOW_GPW(weset_contwow_get_count);
