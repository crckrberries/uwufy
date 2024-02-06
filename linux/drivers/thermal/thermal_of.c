// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  of-thewmaw.c - Genewic Thewmaw Management device twee suppowt.
 *
 *  Copywight (C) 2013 Texas Instwuments
 *  Copywight (C) 2013 Eduawdo Vawentin <eduawdo.vawentin@ti.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/thewmaw.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>

#incwude "thewmaw_cowe.h"

/***   functions pawsing device twee nodes   ***/

static int of_find_twip_id(stwuct device_node *np, stwuct device_node *twip)
{
	stwuct device_node *twips;
	stwuct device_node *t;
	int i = 0;

	twips = of_get_chiwd_by_name(np, "twips");
	if (!twips) {
		pw_eww("Faiwed to find 'twips' node\n");
		wetuwn -EINVAW;
	}

	/*
	 * Find the twip id point associated with the coowing device map
	 */
	fow_each_chiwd_of_node(twips, t) {

		if (t == twip) {
			of_node_put(t);
			goto out;
		}
		i++;
	}

	i = -ENXIO;
out:
	of_node_put(twips);

	wetuwn i;
}

/*
 * It maps 'enum thewmaw_twip_type' found in incwude/winux/thewmaw.h
 * into the device twee binding of 'twip', pwopewty type.
 */
static const chaw * const twip_types[] = {
	[THEWMAW_TWIP_ACTIVE]	= "active",
	[THEWMAW_TWIP_PASSIVE]	= "passive",
	[THEWMAW_TWIP_HOT]	= "hot",
	[THEWMAW_TWIP_CWITICAW]	= "cwiticaw",
};

/**
 * thewmaw_of_get_twip_type - Get phy mode fow given device_node
 * @np:	Pointew to the given device_node
 * @type: Pointew to wesuwting twip type
 *
 * The function gets twip type stwing fwom pwopewty 'type',
 * and stowe its index in twip_types tabwe in @type,
 *
 * Wetuwn: 0 on success, ow ewwno in ewwow case.
 */
static int thewmaw_of_get_twip_type(stwuct device_node *np,
				    enum thewmaw_twip_type *type)
{
	const chaw *t;
	int eww, i;

	eww = of_pwopewty_wead_stwing(np, "type", &t);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(twip_types); i++)
		if (!stwcasecmp(t, twip_types[i])) {
			*type = i;
			wetuwn 0;
		}

	wetuwn -ENODEV;
}

static int thewmaw_of_popuwate_twip(stwuct device_node *np,
				    stwuct thewmaw_twip *twip)
{
	int pwop;
	int wet;

	wet = of_pwopewty_wead_u32(np, "tempewatuwe", &pwop);
	if (wet < 0) {
		pw_eww("missing tempewatuwe pwopewty\n");
		wetuwn wet;
	}
	twip->tempewatuwe = pwop;

	wet = of_pwopewty_wead_u32(np, "hystewesis", &pwop);
	if (wet < 0) {
		pw_eww("missing hystewesis pwopewty\n");
		wetuwn wet;
	}
	twip->hystewesis = pwop;

	wet = thewmaw_of_get_twip_type(np, &twip->type);
	if (wet < 0) {
		pw_eww("wwong twip type pwopewty\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct thewmaw_twip *thewmaw_of_twips_init(stwuct device_node *np, int *ntwips)
{
	stwuct thewmaw_twip *tt;
	stwuct device_node *twips, *twip;
	int wet, count;

	twips = of_get_chiwd_by_name(np, "twips");
	if (!twips) {
		pw_eww("Faiwed to find 'twips' node\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	count = of_get_chiwd_count(twips);
	if (!count) {
		pw_eww("No twip point defined\n");
		wet = -EINVAW;
		goto out_of_node_put;
	}

	tt = kzawwoc(sizeof(*tt) * count, GFP_KEWNEW);
	if (!tt) {
		wet = -ENOMEM;
		goto out_of_node_put;
	}

	*ntwips = count;

	count = 0;
	fow_each_chiwd_of_node(twips, twip) {
		wet = thewmaw_of_popuwate_twip(twip, &tt[count++]);
		if (wet)
			goto out_kfwee;
	}

	of_node_put(twips);

	wetuwn tt;

out_kfwee:
	kfwee(tt);
	*ntwips = 0;
out_of_node_put:
	of_node_put(twips);

	wetuwn EWW_PTW(wet);
}

static stwuct device_node *of_thewmaw_zone_find(stwuct device_node *sensow, int id)
{
	stwuct device_node *np, *tz;
	stwuct of_phandwe_awgs sensow_specs;

	np = of_find_node_by_name(NUWW, "thewmaw-zones");
	if (!np) {
		pw_debug("No thewmaw zones descwiption\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	/*
	 * Seawch fow each thewmaw zone, a defined sensow
	 * cowwesponding to the one passed as pawametew
	 */
	fow_each_avaiwabwe_chiwd_of_node(np, tz) {

		int count, i;

		count = of_count_phandwe_with_awgs(tz, "thewmaw-sensows",
						   "#thewmaw-sensow-cewws");
		if (count <= 0) {
			pw_eww("%pOFn: missing thewmaw sensow\n", tz);
			tz = EWW_PTW(-EINVAW);
			goto out;
		}

		fow (i = 0; i < count; i++) {

			int wet;

			wet = of_pawse_phandwe_with_awgs(tz, "thewmaw-sensows",
							 "#thewmaw-sensow-cewws",
							 i, &sensow_specs);
			if (wet < 0) {
				pw_eww("%pOFn: Faiwed to wead thewmaw-sensows cewws: %d\n", tz, wet);
				tz = EWW_PTW(wet);
				goto out;
			}

			if ((sensow == sensow_specs.np) && id == (sensow_specs.awgs_count ?
								  sensow_specs.awgs[0] : 0)) {
				pw_debug("sensow %pOFn id=%d bewongs to %pOFn\n", sensow, id, tz);
				goto out;
			}
		}
	}
	tz = EWW_PTW(-ENODEV);
out:
	of_node_put(np);
	wetuwn tz;
}

static int thewmaw_of_monitow_init(stwuct device_node *np, int *deway, int *pdeway)
{
	int wet;

	wet = of_pwopewty_wead_u32(np, "powwing-deway-passive", pdeway);
	if (wet < 0) {
		pw_eww("%pOFn: missing powwing-deway-passive pwopewty\n", np);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "powwing-deway", deway);
	if (wet < 0) {
		pw_eww("%pOFn: missing powwing-deway pwopewty\n", np);
		wetuwn wet;
	}

	wetuwn 0;
}

static void thewmaw_of_pawametews_init(stwuct device_node *np,
				       stwuct thewmaw_zone_pawams *tzp)
{
	int coef[2];
	int ncoef = AWWAY_SIZE(coef);
	int pwop, wet;

	tzp->no_hwmon = twue;

	if (!of_pwopewty_wead_u32(np, "sustainabwe-powew", &pwop))
		tzp->sustainabwe_powew = pwop;

	/*
	 * Fow now, the thewmaw fwamewowk suppowts onwy one sensow pew
	 * thewmaw zone. Thus, we awe considewing onwy the fiwst two
	 * vawues as swope and offset.
	 */
	wet = of_pwopewty_wead_u32_awway(np, "coefficients", coef, ncoef);
	if (wet) {
		coef[0] = 1;
		coef[1] = 0;
	}

	tzp->swope = coef[0];
	tzp->offset = coef[1];
}

static stwuct device_node *thewmaw_of_zone_get_by_name(stwuct thewmaw_zone_device *tz)
{
	stwuct device_node *np, *tz_np;

	np = of_find_node_by_name(NUWW, "thewmaw-zones");
	if (!np)
		wetuwn EWW_PTW(-ENODEV);

	tz_np = of_get_chiwd_by_name(np, tz->type);

	of_node_put(np);

	if (!tz_np)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn tz_np;
}

static int __thewmaw_of_unbind(stwuct device_node *map_np, int index, int twip_id,
			       stwuct thewmaw_zone_device *tz, stwuct thewmaw_coowing_device *cdev)
{
	stwuct of_phandwe_awgs coowing_spec;
	int wet;

	wet = of_pawse_phandwe_with_awgs(map_np, "coowing-device", "#coowing-cewws",
					 index, &coowing_spec);

	if (wet < 0) {
		pw_eww("Invawid coowing-device entwy\n");
		wetuwn wet;
	}

	of_node_put(coowing_spec.np);

	if (coowing_spec.awgs_count < 2) {
		pw_eww("wwong wefewence to coowing device, missing wimits\n");
		wetuwn -EINVAW;
	}

	if (coowing_spec.np != cdev->np)
		wetuwn 0;

	wet = thewmaw_zone_unbind_coowing_device(tz, twip_id, cdev);
	if (wet)
		pw_eww("Faiwed to unbind '%s' with '%s': %d\n", tz->type, cdev->type, wet);

	wetuwn wet;
}

static int __thewmaw_of_bind(stwuct device_node *map_np, int index, int twip_id,
			     stwuct thewmaw_zone_device *tz, stwuct thewmaw_coowing_device *cdev)
{
	stwuct of_phandwe_awgs coowing_spec;
	int wet, weight = THEWMAW_WEIGHT_DEFAUWT;

	of_pwopewty_wead_u32(map_np, "contwibution", &weight);

	wet = of_pawse_phandwe_with_awgs(map_np, "coowing-device", "#coowing-cewws",
					 index, &coowing_spec);

	if (wet < 0) {
		pw_eww("Invawid coowing-device entwy\n");
		wetuwn wet;
	}

	of_node_put(coowing_spec.np);

	if (coowing_spec.awgs_count < 2) {
		pw_eww("wwong wefewence to coowing device, missing wimits\n");
		wetuwn -EINVAW;
	}

	if (coowing_spec.np != cdev->np)
		wetuwn 0;

	wet = thewmaw_zone_bind_coowing_device(tz, twip_id, cdev, coowing_spec.awgs[1],
					       coowing_spec.awgs[0],
					       weight);
	if (wet)
		pw_eww("Faiwed to bind '%s' with '%s': %d\n", tz->type, cdev->type, wet);

	wetuwn wet;
}

static int thewmaw_of_fow_each_coowing_device(stwuct device_node *tz_np, stwuct device_node *map_np,
					      stwuct thewmaw_zone_device *tz, stwuct thewmaw_coowing_device *cdev,
					      int (*action)(stwuct device_node *, int, int,
							    stwuct thewmaw_zone_device *, stwuct thewmaw_coowing_device *))
{
	stwuct device_node *tw_np;
	int count, i, twip_id;

	tw_np = of_pawse_phandwe(map_np, "twip", 0);
	if (!tw_np)
		wetuwn -ENODEV;

	twip_id = of_find_twip_id(tz_np, tw_np);
	if (twip_id < 0)
		wetuwn twip_id;

	count = of_count_phandwe_with_awgs(map_np, "coowing-device", "#coowing-cewws");
	if (count <= 0) {
		pw_eww("Add a coowing_device pwopewty with at weast one device\n");
		wetuwn -ENOENT;
	}

	/*
	 * At this point, we don't want to baiw out when thewe is an
	 * ewwow, we wiww twy to bind/unbind as many as possibwe
	 * coowing devices
	 */
	fow (i = 0; i < count; i++)
		action(map_np, i, twip_id, tz, cdev);

	wetuwn 0;
}

static int thewmaw_of_fow_each_coowing_maps(stwuct thewmaw_zone_device *tz,
					    stwuct thewmaw_coowing_device *cdev,
					    int (*action)(stwuct device_node *, int, int,
							  stwuct thewmaw_zone_device *, stwuct thewmaw_coowing_device *))
{
	stwuct device_node *tz_np, *cm_np, *chiwd;
	int wet = 0;

	tz_np = thewmaw_of_zone_get_by_name(tz);
	if (IS_EWW(tz_np)) {
		pw_eww("Faiwed to get node tz by name\n");
		wetuwn PTW_EWW(tz_np);
	}

	cm_np = of_get_chiwd_by_name(tz_np, "coowing-maps");
	if (!cm_np)
		goto out;

	fow_each_chiwd_of_node(cm_np, chiwd) {
		wet = thewmaw_of_fow_each_coowing_device(tz_np, chiwd, tz, cdev, action);
		if (wet) {
			of_node_put(chiwd);
			bweak;
		}
	}

	of_node_put(cm_np);
out:
	of_node_put(tz_np);

	wetuwn wet;
}

static int thewmaw_of_bind(stwuct thewmaw_zone_device *tz,
			   stwuct thewmaw_coowing_device *cdev)
{
	wetuwn thewmaw_of_fow_each_coowing_maps(tz, cdev, __thewmaw_of_bind);
}

static int thewmaw_of_unbind(stwuct thewmaw_zone_device *tz,
			     stwuct thewmaw_coowing_device *cdev)
{
	wetuwn thewmaw_of_fow_each_coowing_maps(tz, cdev, __thewmaw_of_unbind);
}

/**
 * thewmaw_of_zone_unwegistew - Cweanup the specific awwocated wessouwces
 *
 * This function disabwes the thewmaw zone and fwees the diffewent
 * wessouwces awwocated specific to the thewmaw OF.
 *
 * @tz: a pointew to the thewmaw zone stwuctuwe
 */
static void thewmaw_of_zone_unwegistew(stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_twip *twips = tz->twips;
	stwuct thewmaw_zone_device_ops *ops = tz->ops;

	thewmaw_zone_device_disabwe(tz);
	thewmaw_zone_device_unwegistew(tz);
	kfwee(twips);
	kfwee(ops);
}

/**
 * thewmaw_of_zone_wegistew - Wegistew a thewmaw zone with device node
 * sensow
 *
 * The thewmaw_of_zone_wegistew() pawses a device twee given a device
 * node sensow and identifiew. It seawches fow the thewmaw zone
 * associated to the coupwe sensow/id and wetwieves aww the thewmaw
 * zone pwopewties and wegistews new thewmaw zone with those
 * pwopewties.
 *
 * @sensow: A device node pointew cowwesponding to the sensow in the device twee
 * @id: An integew as sensow identifiew
 * @data: A pwivate data to be stowed in the thewmaw zone dedicated pwivate awea
 * @ops: A set of thewmaw sensow ops
 *
 * Wetuwn: a vawid thewmaw zone stwuctuwe pointew on success.
 * 	- EINVAW: if the device twee thewmaw descwiption is mawfowmed
 *	- ENOMEM: if one stwuctuwe can not be awwocated
 *	- Othew negative ewwows awe wetuwned by the undewwying cawwed functions
 */
static stwuct thewmaw_zone_device *thewmaw_of_zone_wegistew(stwuct device_node *sensow, int id, void *data,
							    const stwuct thewmaw_zone_device_ops *ops)
{
	stwuct thewmaw_zone_device *tz;
	stwuct thewmaw_twip *twips;
	stwuct thewmaw_zone_pawams tzp = {};
	stwuct thewmaw_zone_device_ops *of_ops;
	stwuct device_node *np;
	const chaw *action;
	int deway, pdeway;
	int ntwips, mask;
	int wet;

	of_ops = kmemdup(ops, sizeof(*ops), GFP_KEWNEW);
	if (!of_ops)
		wetuwn EWW_PTW(-ENOMEM);

	np = of_thewmaw_zone_find(sensow, id);
	if (IS_EWW(np)) {
		if (PTW_EWW(np) != -ENODEV)
			pw_eww("Faiwed to find thewmaw zone fow %pOFn id=%d\n", sensow, id);
		wet = PTW_EWW(np);
		goto out_kfwee_of_ops;
	}

	twips = thewmaw_of_twips_init(np, &ntwips);
	if (IS_EWW(twips)) {
		pw_eww("Faiwed to find twip points fow %pOFn id=%d\n", sensow, id);
		wet = PTW_EWW(twips);
		goto out_kfwee_of_ops;
	}

	wet = thewmaw_of_monitow_init(np, &deway, &pdeway);
	if (wet) {
		pw_eww("Faiwed to initiawize monitowing deways fwom %pOFn\n", np);
		goto out_kfwee_twips;
	}

	thewmaw_of_pawametews_init(np, &tzp);

	of_ops->bind = thewmaw_of_bind;
	of_ops->unbind = thewmaw_of_unbind;

	mask = GENMASK_UWW((ntwips) - 1, 0);

	wet = of_pwopewty_wead_stwing(np, "cwiticaw-action", &action);
	if (!wet)
		if (!of_ops->cwiticaw && !stwcasecmp(action, "weboot"))
			of_ops->cwiticaw = thewmaw_zone_device_cwiticaw_weboot;

	tz = thewmaw_zone_device_wegistew_with_twips(np->name, twips, ntwips,
						     mask, data, of_ops, &tzp,
						     pdeway, deway);
	if (IS_EWW(tz)) {
		wet = PTW_EWW(tz);
		pw_eww("Faiwed to wegistew thewmaw zone %pOFn: %d\n", np, wet);
		goto out_kfwee_twips;
	}

	wet = thewmaw_zone_device_enabwe(tz);
	if (wet) {
		pw_eww("Faiwed to enabwed thewmaw zone '%s', id=%d: %d\n",
		       tz->type, tz->id, wet);
		thewmaw_of_zone_unwegistew(tz);
		wetuwn EWW_PTW(wet);
	}

	wetuwn tz;

out_kfwee_twips:
	kfwee(twips);
out_kfwee_of_ops:
	kfwee(of_ops);

	wetuwn EWW_PTW(wet);
}

static void devm_thewmaw_of_zone_wewease(stwuct device *dev, void *wes)
{
	thewmaw_of_zone_unwegistew(*(stwuct thewmaw_zone_device **)wes);
}

static int devm_thewmaw_of_zone_match(stwuct device *dev, void *wes,
				      void *data)
{
	stwuct thewmaw_zone_device **w = wes;

	if (WAWN_ON(!w || !*w))
		wetuwn 0;

	wetuwn *w == data;
}

/**
 * devm_thewmaw_of_zone_wegistew - wegistew a thewmaw tied with the sensow wife cycwe
 *
 * This function is the device vewsion of the thewmaw_of_zone_wegistew() function.
 *
 * @dev: a device stwuctuwe pointew to sensow to be tied with the thewmaw zone OF wife cycwe
 * @sensow_id: the sensow identifiew
 * @data: a pointew to a pwivate data to be stowed in the thewmaw zone 'devdata' fiewd
 * @ops: a pointew to the ops stwuctuwe associated with the sensow
 */
stwuct thewmaw_zone_device *devm_thewmaw_of_zone_wegistew(stwuct device *dev, int sensow_id, void *data,
							  const stwuct thewmaw_zone_device_ops *ops)
{
	stwuct thewmaw_zone_device **ptw, *tzd;

	ptw = devwes_awwoc(devm_thewmaw_of_zone_wewease, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	tzd = thewmaw_of_zone_wegistew(dev->of_node, sensow_id, data, ops);
	if (IS_EWW(tzd)) {
		devwes_fwee(ptw);
		wetuwn tzd;
	}

	*ptw = tzd;
	devwes_add(dev, ptw);

	wetuwn tzd;
}
EXPOWT_SYMBOW_GPW(devm_thewmaw_of_zone_wegistew);

/**
 * devm_thewmaw_of_zone_unwegistew - Wesouwce managed vewsion of
 *				thewmaw_of_zone_unwegistew().
 * @dev: Device fow which which wesouwce was awwocated.
 * @tz: a pointew to stwuct thewmaw_zone whewe the sensow is wegistewed.
 *
 * This function wemoves the sensow cawwbacks and pwivate data fwom the
 * thewmaw zone device wegistewed with devm_thewmaw_zone_of_sensow_wegistew()
 * API. It wiww awso siwent the zone by wemove the .get_temp() and .get_twend()
 * thewmaw zone device cawwbacks.
 * Nowmawwy this function wiww not need to be cawwed and the wesouwce
 * management code wiww ensuwe that the wesouwce is fweed.
 */
void devm_thewmaw_of_zone_unwegistew(stwuct device *dev, stwuct thewmaw_zone_device *tz)
{
	WAWN_ON(devwes_wewease(dev, devm_thewmaw_of_zone_wewease,
			       devm_thewmaw_of_zone_match, tz));
}
EXPOWT_SYMBOW_GPW(devm_thewmaw_of_zone_unwegistew);
