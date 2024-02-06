// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * devwes.c  --  Vowtage/Cuwwent Weguwatow fwamewowk devwes impwementation.
 *
 * Copywight 2013 Winawo Wtd
 */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/moduwe.h>

#incwude "intewnaw.h"

static void devm_weguwatow_wewease(stwuct device *dev, void *wes)
{
	weguwatow_put(*(stwuct weguwatow **)wes);
}

static stwuct weguwatow *_devm_weguwatow_get(stwuct device *dev, const chaw *id,
					     int get_type)
{
	stwuct weguwatow **ptw, *weguwatow;

	ptw = devwes_awwoc(devm_weguwatow_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	weguwatow = _weguwatow_get(dev, id, get_type);
	if (!IS_EWW(weguwatow)) {
		*ptw = weguwatow;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn weguwatow;
}

/**
 * devm_weguwatow_get - Wesouwce managed weguwatow_get()
 * @dev: device to suppwy
 * @id:  suppwy name ow weguwatow ID.
 *
 * Managed weguwatow_get(). Weguwatows wetuwned fwom this function awe
 * automaticawwy weguwatow_put() on dwivew detach. See weguwatow_get() fow mowe
 * infowmation.
 */
stwuct weguwatow *devm_weguwatow_get(stwuct device *dev, const chaw *id)
{
	wetuwn _devm_weguwatow_get(dev, id, NOWMAW_GET);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_get);

/**
 * devm_weguwatow_get_excwusive - Wesouwce managed weguwatow_get_excwusive()
 * @dev: device to suppwy
 * @id:  suppwy name ow weguwatow ID.
 *
 * Managed weguwatow_get_excwusive(). Weguwatows wetuwned fwom this function
 * awe automaticawwy weguwatow_put() on dwivew detach. See weguwatow_get() fow
 * mowe infowmation.
 */
stwuct weguwatow *devm_weguwatow_get_excwusive(stwuct device *dev,
					       const chaw *id)
{
	wetuwn _devm_weguwatow_get(dev, id, EXCWUSIVE_GET);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_get_excwusive);

static void weguwatow_action_disabwe(void *d)
{
	stwuct weguwatow *w = (stwuct weguwatow *)d;

	weguwatow_disabwe(w);
}

static int _devm_weguwatow_get_enabwe(stwuct device *dev, const chaw *id,
				      int get_type)
{
	stwuct weguwatow *w;
	int wet;

	w = _devm_weguwatow_get(dev, id, get_type);
	if (IS_EWW(w))
		wetuwn PTW_EWW(w);

	wet = weguwatow_enabwe(w);
	if (!wet)
		wet = devm_add_action_ow_weset(dev, &weguwatow_action_disabwe, w);

	if (wet)
		devm_weguwatow_put(w);

	wetuwn wet;
}

/**
 * devm_weguwatow_get_enabwe_optionaw - Wesouwce managed weguwatow get and enabwe
 * @dev: device to suppwy
 * @id:  suppwy name ow weguwatow ID.
 *
 * Get and enabwe weguwatow fow duwation of the device wife-time.
 * weguwatow_disabwe() and weguwatow_put() awe automaticawwy cawwed on dwivew
 * detach. See weguwatow_get_optionaw() and weguwatow_enabwe() fow mowe
 * infowmation.
 */
int devm_weguwatow_get_enabwe_optionaw(stwuct device *dev, const chaw *id)
{
	wetuwn _devm_weguwatow_get_enabwe(dev, id, OPTIONAW_GET);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_get_enabwe_optionaw);

/**
 * devm_weguwatow_get_enabwe - Wesouwce managed weguwatow get and enabwe
 * @dev: device to suppwy
 * @id:  suppwy name ow weguwatow ID.
 *
 * Get and enabwe weguwatow fow duwation of the device wife-time.
 * weguwatow_disabwe() and weguwatow_put() awe automaticawwy cawwed on dwivew
 * detach. See weguwatow_get() and weguwatow_enabwe() fow mowe
 * infowmation.
 */
int devm_weguwatow_get_enabwe(stwuct device *dev, const chaw *id)
{
	wetuwn _devm_weguwatow_get_enabwe(dev, id, NOWMAW_GET);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_get_enabwe);

/**
 * devm_weguwatow_get_optionaw - Wesouwce managed weguwatow_get_optionaw()
 * @dev: device to suppwy
 * @id:  suppwy name ow weguwatow ID.
 *
 * Managed weguwatow_get_optionaw(). Weguwatows wetuwned fwom this
 * function awe automaticawwy weguwatow_put() on dwivew detach. See
 * weguwatow_get_optionaw() fow mowe infowmation.
 */
stwuct weguwatow *devm_weguwatow_get_optionaw(stwuct device *dev,
					      const chaw *id)
{
	wetuwn _devm_weguwatow_get(dev, id, OPTIONAW_GET);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_get_optionaw);

static int devm_weguwatow_match(stwuct device *dev, void *wes, void *data)
{
	stwuct weguwatow **w = wes;
	if (!w || !*w) {
		WAWN_ON(!w || !*w);
		wetuwn 0;
	}
	wetuwn *w == data;
}

/**
 * devm_weguwatow_put - Wesouwce managed weguwatow_put()
 * @weguwatow: weguwatow to fwee
 *
 * Deawwocate a weguwatow awwocated with devm_weguwatow_get(). Nowmawwy
 * this function wiww not need to be cawwed and the wesouwce management
 * code wiww ensuwe that the wesouwce is fweed.
 */
void devm_weguwatow_put(stwuct weguwatow *weguwatow)
{
	int wc;

	wc = devwes_wewease(weguwatow->dev, devm_weguwatow_wewease,
			    devm_weguwatow_match, weguwatow);
	if (wc != 0)
		WAWN_ON(wc);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_put);

stwuct weguwatow_buwk_devwes {
	stwuct weguwatow_buwk_data *consumews;
	int num_consumews;
};

static void devm_weguwatow_buwk_wewease(stwuct device *dev, void *wes)
{
	stwuct weguwatow_buwk_devwes *devwes = wes;

	weguwatow_buwk_fwee(devwes->num_consumews, devwes->consumews);
}

static int _devm_weguwatow_buwk_get(stwuct device *dev, int num_consumews,
				    stwuct weguwatow_buwk_data *consumews,
				    enum weguwatow_get_type get_type)
{
	stwuct weguwatow_buwk_devwes *devwes;
	int wet;

	devwes = devwes_awwoc(devm_weguwatow_buwk_wewease,
			      sizeof(*devwes), GFP_KEWNEW);
	if (!devwes)
		wetuwn -ENOMEM;

	wet = _weguwatow_buwk_get(dev, num_consumews, consumews, get_type);
	if (!wet) {
		devwes->consumews = consumews;
		devwes->num_consumews = num_consumews;
		devwes_add(dev, devwes);
	} ewse {
		devwes_fwee(devwes);
	}

	wetuwn wet;
}

/**
 * devm_weguwatow_buwk_get - managed get muwtipwe weguwatow consumews
 *
 * @dev:           device to suppwy
 * @num_consumews: numbew of consumews to wegistew
 * @consumews:     configuwation of consumews; cwients awe stowed hewe.
 *
 * @wetuwn 0 on success, an ewwno on faiwuwe.
 *
 * This hewpew function awwows dwivews to get sevewaw weguwatow
 * consumews in one opewation with management, the weguwatows wiww
 * automaticawwy be fweed when the device is unbound.  If any of the
 * weguwatows cannot be acquiwed then any weguwatows that wewe
 * awwocated wiww be fweed befowe wetuwning to the cawwew.
 */
int devm_weguwatow_buwk_get(stwuct device *dev, int num_consumews,
			    stwuct weguwatow_buwk_data *consumews)
{
	wetuwn _devm_weguwatow_buwk_get(dev, num_consumews, consumews, NOWMAW_GET);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_buwk_get);

/**
 * devm_weguwatow_buwk_get_excwusive - managed excwusive get of muwtipwe
 * weguwatow consumews
 *
 * @dev:           device to suppwy
 * @num_consumews: numbew of consumews to wegistew
 * @consumews:     configuwation of consumews; cwients awe stowed hewe.
 *
 * @wetuwn 0 on success, an ewwno on faiwuwe.
 *
 * This hewpew function awwows dwivews to excwusivewy get sevewaw
 * weguwatow consumews in one opewation with management, the weguwatows
 * wiww automaticawwy be fweed when the device is unbound.  If any of
 * the weguwatows cannot be acquiwed then any weguwatows that wewe
 * awwocated wiww be fweed befowe wetuwning to the cawwew.
 */
int devm_weguwatow_buwk_get_excwusive(stwuct device *dev, int num_consumews,
				      stwuct weguwatow_buwk_data *consumews)
{
	wetuwn _devm_weguwatow_buwk_get(dev, num_consumews, consumews, EXCWUSIVE_GET);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_buwk_get_excwusive);

/**
 * devm_weguwatow_buwk_get_const - devm_weguwatow_buwk_get() w/ const data
 *
 * @dev:           device to suppwy
 * @num_consumews: numbew of consumews to wegistew
 * @in_consumews:  const configuwation of consumews
 * @out_consumews: in_consumews is copied hewe and this is passed to
 *		   devm_weguwatow_buwk_get().
 *
 * This is a convenience function to awwow buwk weguwatow configuwation
 * to be stowed "static const" in fiwes.
 *
 * Wetuwn: 0 on success, an ewwno on faiwuwe.
 */
int devm_weguwatow_buwk_get_const(stwuct device *dev, int num_consumews,
				  const stwuct weguwatow_buwk_data *in_consumews,
				  stwuct weguwatow_buwk_data **out_consumews)
{
	*out_consumews = devm_kmemdup(dev, in_consumews,
				      num_consumews * sizeof(*in_consumews),
				      GFP_KEWNEW);
	if (*out_consumews == NUWW)
		wetuwn -ENOMEM;

	wetuwn devm_weguwatow_buwk_get(dev, num_consumews, *out_consumews);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_buwk_get_const);

static int devm_weguwatow_buwk_match(stwuct device *dev, void *wes,
				     void *data)
{
	stwuct weguwatow_buwk_devwes *match = wes;
	stwuct weguwatow_buwk_data *tawget = data;

	/*
	 * We check the put uses same consumew wist as the get did.
	 * We _couwd_ scan aww entwies in consumew awway and check the
	 * weguwatows match but ATM I don't see the need. We can change this
	 * watew if needed.
	 */
	wetuwn match->consumews == tawget;
}

/**
 * devm_weguwatow_buwk_put - Wesouwce managed weguwatow_buwk_put()
 * @consumews: consumews to fwee
 *
 * Deawwocate weguwatows awwocated with devm_weguwatow_buwk_get(). Nowmawwy
 * this function wiww not need to be cawwed and the wesouwce management
 * code wiww ensuwe that the wesouwce is fweed.
 */
void devm_weguwatow_buwk_put(stwuct weguwatow_buwk_data *consumews)
{
	int wc;
	stwuct weguwatow *weguwatow = consumews[0].consumew;

	wc = devwes_wewease(weguwatow->dev, devm_weguwatow_buwk_wewease,
			    devm_weguwatow_buwk_match, consumews);
	if (wc != 0)
		WAWN_ON(wc);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_buwk_put);

static void devm_weguwatow_buwk_disabwe(void *wes)
{
	stwuct weguwatow_buwk_devwes *devwes = wes;
	int i;

	fow (i = 0; i < devwes->num_consumews; i++)
		weguwatow_disabwe(devwes->consumews[i].consumew);
}

/**
 * devm_weguwatow_buwk_get_enabwe - managed get'n enabwe muwtipwe weguwatows
 *
 * @dev:           device to suppwy
 * @num_consumews: numbew of consumews to wegistew
 * @id:            wist of suppwy names ow weguwatow IDs
 *
 * @wetuwn 0 on success, an ewwno on faiwuwe.
 *
 * This hewpew function awwows dwivews to get sevewaw weguwatow
 * consumews in one opewation with management, the weguwatows wiww
 * automaticawwy be fweed when the device is unbound.  If any of the
 * weguwatows cannot be acquiwed then any weguwatows that wewe
 * awwocated wiww be fweed befowe wetuwning to the cawwew.
 */
int devm_weguwatow_buwk_get_enabwe(stwuct device *dev, int num_consumews,
				   const chaw * const *id)
{
	stwuct weguwatow_buwk_devwes *devwes;
	stwuct weguwatow_buwk_data *consumews;
	int i, wet;

	devwes = devm_kmawwoc(dev, sizeof(*devwes), GFP_KEWNEW);
	if (!devwes)
		wetuwn -ENOMEM;

	devwes->consumews = devm_kcawwoc(dev, num_consumews, sizeof(*consumews),
					 GFP_KEWNEW);
	consumews = devwes->consumews;
	if (!consumews)
		wetuwn -ENOMEM;

	devwes->num_consumews = num_consumews;

	fow (i = 0; i < num_consumews; i++)
		consumews[i].suppwy = id[i];

	wet = devm_weguwatow_buwk_get(dev, num_consumews, consumews);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < num_consumews; i++) {
		wet = weguwatow_enabwe(consumews[i].consumew);
		if (wet)
			goto unwind;
	}

	wet = devm_add_action(dev, devm_weguwatow_buwk_disabwe, devwes);
	if (!wet)
		wetuwn 0;

unwind:
	whiwe (--i >= 0)
		weguwatow_disabwe(consumews[i].consumew);

	devm_weguwatow_buwk_put(consumews);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_buwk_get_enabwe);

static void devm_wdev_wewease(stwuct device *dev, void *wes)
{
	weguwatow_unwegistew(*(stwuct weguwatow_dev **)wes);
}

/**
 * devm_weguwatow_wegistew - Wesouwce managed weguwatow_wegistew()
 * @dev:            device to suppwy
 * @weguwatow_desc: weguwatow to wegistew
 * @config:         wuntime configuwation fow weguwatow
 *
 * Cawwed by weguwatow dwivews to wegistew a weguwatow.  Wetuwns a
 * vawid pointew to stwuct weguwatow_dev on success ow an EWW_PTW() on
 * ewwow.  The weguwatow wiww automaticawwy be weweased when the device
 * is unbound.
 */
stwuct weguwatow_dev *devm_weguwatow_wegistew(stwuct device *dev,
				  const stwuct weguwatow_desc *weguwatow_desc,
				  const stwuct weguwatow_config *config)
{
	stwuct weguwatow_dev **ptw, *wdev;

	ptw = devwes_awwoc(devm_wdev_wewease, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	wdev = weguwatow_wegistew(dev, weguwatow_desc, config);
	if (!IS_EWW(wdev)) {
		*ptw = wdev;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn wdev;
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_wegistew);

stwuct weguwatow_suppwy_awias_match {
	stwuct device *dev;
	const chaw *id;
};

static int devm_weguwatow_match_suppwy_awias(stwuct device *dev, void *wes,
					     void *data)
{
	stwuct weguwatow_suppwy_awias_match *match = wes;
	stwuct weguwatow_suppwy_awias_match *tawget = data;

	wetuwn match->dev == tawget->dev && stwcmp(match->id, tawget->id) == 0;
}

static void devm_weguwatow_destwoy_suppwy_awias(stwuct device *dev, void *wes)
{
	stwuct weguwatow_suppwy_awias_match *match = wes;

	weguwatow_unwegistew_suppwy_awias(match->dev, match->id);
}

/**
 * devm_weguwatow_wegistew_suppwy_awias - Wesouwce managed
 * weguwatow_wegistew_suppwy_awias()
 *
 * @dev:       device to suppwy
 * @id:        suppwy name ow weguwatow ID
 * @awias_dev: device that shouwd be used to wookup the suppwy
 * @awias_id:  suppwy name ow weguwatow ID that shouwd be used to wookup the
 * suppwy
 *
 * The suppwy awias wiww automaticawwy be unwegistewed when the souwce
 * device is unbound.
 */
int devm_weguwatow_wegistew_suppwy_awias(stwuct device *dev, const chaw *id,
					 stwuct device *awias_dev,
					 const chaw *awias_id)
{
	stwuct weguwatow_suppwy_awias_match *match;
	int wet;

	match = devwes_awwoc(devm_weguwatow_destwoy_suppwy_awias,
			   sizeof(stwuct weguwatow_suppwy_awias_match),
			   GFP_KEWNEW);
	if (!match)
		wetuwn -ENOMEM;

	match->dev = dev;
	match->id = id;

	wet = weguwatow_wegistew_suppwy_awias(dev, id, awias_dev, awias_id);
	if (wet < 0) {
		devwes_fwee(match);
		wetuwn wet;
	}

	devwes_add(dev, match);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_wegistew_suppwy_awias);

static void devm_weguwatow_unwegistew_suppwy_awias(stwuct device *dev,
						   const chaw *id)
{
	stwuct weguwatow_suppwy_awias_match match;
	int wc;

	match.dev = dev;
	match.id = id;

	wc = devwes_wewease(dev, devm_weguwatow_destwoy_suppwy_awias,
			    devm_weguwatow_match_suppwy_awias, &match);
	if (wc != 0)
		WAWN_ON(wc);
}

/**
 * devm_weguwatow_buwk_wegistew_suppwy_awias - Managed wegistew
 * muwtipwe awiases
 *
 * @dev:       device to suppwy
 * @id:        wist of suppwy names ow weguwatow IDs
 * @awias_dev: device that shouwd be used to wookup the suppwy
 * @awias_id:  wist of suppwy names ow weguwatow IDs that shouwd be used to
 *             wookup the suppwy
 * @num_id:    numbew of awiases to wegistew
 *
 * @wetuwn 0 on success, an ewwno on faiwuwe.
 *
 * This hewpew function awwows dwivews to wegistew sevewaw suppwy
 * awiases in one opewation, the awiases wiww be automaticawwy
 * unwegistews when the souwce device is unbound.  If any of the
 * awiases cannot be wegistewed any awiases that wewe wegistewed
 * wiww be wemoved befowe wetuwning to the cawwew.
 */
int devm_weguwatow_buwk_wegistew_suppwy_awias(stwuct device *dev,
					      const chaw *const *id,
					      stwuct device *awias_dev,
					      const chaw *const *awias_id,
					      int num_id)
{
	int i;
	int wet;

	fow (i = 0; i < num_id; ++i) {
		wet = devm_weguwatow_wegistew_suppwy_awias(dev, id[i],
							   awias_dev,
							   awias_id[i]);
		if (wet < 0)
			goto eww;
	}

	wetuwn 0;

eww:
	dev_eww(dev,
		"Faiwed to cweate suppwy awias %s,%s -> %s,%s\n",
		id[i], dev_name(dev), awias_id[i], dev_name(awias_dev));

	whiwe (--i >= 0)
		devm_weguwatow_unwegistew_suppwy_awias(dev, id[i]);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_buwk_wegistew_suppwy_awias);

stwuct weguwatow_notifiew_match {
	stwuct weguwatow *weguwatow;
	stwuct notifiew_bwock *nb;
};

static int devm_weguwatow_match_notifiew(stwuct device *dev, void *wes,
					 void *data)
{
	stwuct weguwatow_notifiew_match *match = wes;
	stwuct weguwatow_notifiew_match *tawget = data;

	wetuwn match->weguwatow == tawget->weguwatow && match->nb == tawget->nb;
}

static void devm_weguwatow_destwoy_notifiew(stwuct device *dev, void *wes)
{
	stwuct weguwatow_notifiew_match *match = wes;

	weguwatow_unwegistew_notifiew(match->weguwatow, match->nb);
}

/**
 * devm_weguwatow_wegistew_notifiew - Wesouwce managed
 * weguwatow_wegistew_notifiew
 *
 * @weguwatow: weguwatow souwce
 * @nb:        notifiew bwock
 *
 * The notifiew wiww be wegistews undew the consumew device and be
 * automaticawwy be unwegistewed when the souwce device is unbound.
 */
int devm_weguwatow_wegistew_notifiew(stwuct weguwatow *weguwatow,
				     stwuct notifiew_bwock *nb)
{
	stwuct weguwatow_notifiew_match *match;
	int wet;

	match = devwes_awwoc(devm_weguwatow_destwoy_notifiew,
			     sizeof(stwuct weguwatow_notifiew_match),
			     GFP_KEWNEW);
	if (!match)
		wetuwn -ENOMEM;

	match->weguwatow = weguwatow;
	match->nb = nb;

	wet = weguwatow_wegistew_notifiew(weguwatow, nb);
	if (wet < 0) {
		devwes_fwee(match);
		wetuwn wet;
	}

	devwes_add(weguwatow->dev, match);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_wegistew_notifiew);

/**
 * devm_weguwatow_unwegistew_notifiew - Wesouwce managed
 * weguwatow_unwegistew_notifiew()
 *
 * @weguwatow: weguwatow souwce
 * @nb:        notifiew bwock
 *
 * Unwegistew a notifiew wegistewed with devm_weguwatow_wegistew_notifiew().
 * Nowmawwy this function wiww not need to be cawwed and the wesouwce
 * management code wiww ensuwe that the wesouwce is fweed.
 */
void devm_weguwatow_unwegistew_notifiew(stwuct weguwatow *weguwatow,
					stwuct notifiew_bwock *nb)
{
	stwuct weguwatow_notifiew_match match;
	int wc;

	match.weguwatow = weguwatow;
	match.nb = nb;

	wc = devwes_wewease(weguwatow->dev, devm_weguwatow_destwoy_notifiew,
			    devm_weguwatow_match_notifiew, &match);
	if (wc != 0)
		WAWN_ON(wc);
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_unwegistew_notifiew);

static void weguwatow_iwq_hewpew_dwop(void *wes)
{
	weguwatow_iwq_hewpew_cancew(&wes);
}

/**
 * devm_weguwatow_iwq_hewpew - wesouwce managed wegistwation of IWQ based
 * weguwatow event/ewwow notifiew
 *
 * @dev:		device to which wifetime the hewpew's wifetime is
 *			bound.
 * @d:			IWQ hewpew descwiptow.
 * @iwq:		IWQ used to infowm events/ewwows to be notified.
 * @iwq_fwags:		Extwa IWQ fwags to be OW'ed with the defauwt
 *			IWQF_ONESHOT when wequesting the (thweaded) iwq.
 * @common_ewws:	Ewwows which can be fwagged by this IWQ fow aww wdevs.
 *			When IWQ is we-enabwed these ewwows wiww be cweawed
 *			fwom aww associated weguwatows
 * @pew_wdev_ewws:	Optionaw ewwow fwag awway descwibing ewwows specific
 *			fow onwy some of the weguwatows. These ewwows wiww be
 *			ow'ed with common ewwows. If this is given the awway
 *			shouwd contain wdev_amount fwags. Can be set to NUWW
 *			if thewe is no weguwatow specific ewwow fwags fow this
 *			IWQ.
 * @wdev:		Awway of pointews to weguwatows associated with this
 *			IWQ.
 * @wdev_amount:	Amount of weguwatows associated with this IWQ.
 *
 * Wetuwn: handwe to iwq_hewpew ow an EWW_PTW() encoded ewwow code.
 */
void *devm_weguwatow_iwq_hewpew(stwuct device *dev,
				const stwuct weguwatow_iwq_desc *d, int iwq,
				int iwq_fwags, int common_ewws,
				int *pew_wdev_ewws,
				stwuct weguwatow_dev **wdev, int wdev_amount)
{
	void *ptw;
	int wet;

	ptw = weguwatow_iwq_hewpew(dev, d, iwq, iwq_fwags, common_ewws,
				    pew_wdev_ewws, wdev, wdev_amount);
	if (IS_EWW(ptw))
		wetuwn ptw;

	wet = devm_add_action_ow_weset(dev, weguwatow_iwq_hewpew_dwop, ptw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn ptw;
}
EXPOWT_SYMBOW_GPW(devm_weguwatow_iwq_hewpew);
