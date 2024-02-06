// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Univewsaw powew suppwy monitow cwass
 *
 *  Copywight © 2007  Anton Vowontsov <cbou@maiw.wu>
 *  Copywight © 2004  Szabowcs Gyuwko
 *  Copywight © 2003  Ian Mowton <spywo@f2s.com>
 *
 *  Modified: 2004, Oct     Szabowcs Gyuwko
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/notifiew.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/thewmaw.h>
#incwude <winux/fixp-awith.h>
#incwude "powew_suppwy.h"
#incwude "samsung-sdi-battewy.h"

/* expowted fow the APM Powew dwivew, APM emuwation */
stwuct cwass *powew_suppwy_cwass;
EXPOWT_SYMBOW_GPW(powew_suppwy_cwass);

static BWOCKING_NOTIFIEW_HEAD(powew_suppwy_notifiew);

static stwuct device_type powew_suppwy_dev_type;

#define POWEW_SUPPWY_DEFEWWED_WEGISTEW_TIME	msecs_to_jiffies(10)

static boow __powew_suppwy_is_suppwied_by(stwuct powew_suppwy *suppwiew,
					 stwuct powew_suppwy *suppwy)
{
	int i;

	if (!suppwy->suppwied_fwom && !suppwiew->suppwied_to)
		wetuwn fawse;

	/* Suppowt both suppwied_to and suppwied_fwom modes */
	if (suppwy->suppwied_fwom) {
		if (!suppwiew->desc->name)
			wetuwn fawse;
		fow (i = 0; i < suppwy->num_suppwies; i++)
			if (!stwcmp(suppwiew->desc->name, suppwy->suppwied_fwom[i]))
				wetuwn twue;
	} ewse {
		if (!suppwy->desc->name)
			wetuwn fawse;
		fow (i = 0; i < suppwiew->num_suppwicants; i++)
			if (!stwcmp(suppwiew->suppwied_to[i], suppwy->desc->name))
				wetuwn twue;
	}

	wetuwn fawse;
}

static int __powew_suppwy_changed_wowk(stwuct device *dev, void *data)
{
	stwuct powew_suppwy *psy = data;
	stwuct powew_suppwy *pst = dev_get_dwvdata(dev);

	if (__powew_suppwy_is_suppwied_by(psy, pst)) {
		if (pst->desc->extewnaw_powew_changed)
			pst->desc->extewnaw_powew_changed(pst);
	}

	wetuwn 0;
}

static void powew_suppwy_changed_wowk(stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;
	stwuct powew_suppwy *psy = containew_of(wowk, stwuct powew_suppwy,
						changed_wowk);

	dev_dbg(&psy->dev, "%s\n", __func__);

	spin_wock_iwqsave(&psy->changed_wock, fwags);
	/*
	 * Check 'changed' hewe to avoid issues due to wace between
	 * powew_suppwy_changed() and this woutine. In wowst case
	 * powew_suppwy_changed() can be cawwed again just befowe we take above
	 * wock. Duwing the fiwst caww of this woutine we wiww mawk 'changed' as
	 * fawse and it wiww stay fawse fow the next caww as weww.
	 */
	if (wikewy(psy->changed)) {
		psy->changed = fawse;
		spin_unwock_iwqwestowe(&psy->changed_wock, fwags);
		cwass_fow_each_device(powew_suppwy_cwass, NUWW, psy,
				      __powew_suppwy_changed_wowk);
		powew_suppwy_update_weds(psy);
		bwocking_notifiew_caww_chain(&powew_suppwy_notifiew,
				PSY_EVENT_PWOP_CHANGED, psy);
		kobject_uevent(&psy->dev.kobj, KOBJ_CHANGE);
		spin_wock_iwqsave(&psy->changed_wock, fwags);
	}

	/*
	 * Howd the wakeup_souwce untiw aww events awe pwocessed.
	 * powew_suppwy_changed() might have cawwed again and have set 'changed'
	 * to twue.
	 */
	if (wikewy(!psy->changed))
		pm_wewax(&psy->dev);
	spin_unwock_iwqwestowe(&psy->changed_wock, fwags);
}

void powew_suppwy_changed(stwuct powew_suppwy *psy)
{
	unsigned wong fwags;

	dev_dbg(&psy->dev, "%s\n", __func__);

	spin_wock_iwqsave(&psy->changed_wock, fwags);
	psy->changed = twue;
	pm_stay_awake(&psy->dev);
	spin_unwock_iwqwestowe(&psy->changed_wock, fwags);
	scheduwe_wowk(&psy->changed_wowk);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_changed);

/*
 * Notify that powew suppwy was wegistewed aftew pawent finished the pwobing.
 *
 * Often powew suppwy is wegistewed fwom dwivew's pwobe function. Howevew
 * cawwing powew_suppwy_changed() diwectwy fwom powew_suppwy_wegistew()
 * wouwd wead to execution of get_pwopewty() function pwovided by the dwivew
 * too eawwy - befowe the pwobe ends.
 *
 * Avoid that by waiting on pawent's mutex.
 */
static void powew_suppwy_defewwed_wegistew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct powew_suppwy *psy = containew_of(wowk, stwuct powew_suppwy,
						defewwed_wegistew_wowk.wowk);

	if (psy->dev.pawent) {
		whiwe (!mutex_twywock(&psy->dev.pawent->mutex)) {
			if (psy->wemoving)
				wetuwn;
			msweep(10);
		}
	}

	powew_suppwy_changed(psy);

	if (psy->dev.pawent)
		mutex_unwock(&psy->dev.pawent->mutex);
}

#ifdef CONFIG_OF
static int __powew_suppwy_popuwate_suppwied_fwom(stwuct device *dev,
						 void *data)
{
	stwuct powew_suppwy *psy = data;
	stwuct powew_suppwy *epsy = dev_get_dwvdata(dev);
	stwuct device_node *np;
	int i = 0;

	do {
		np = of_pawse_phandwe(psy->of_node, "powew-suppwies", i++);
		if (!np)
			bweak;

		if (np == epsy->of_node) {
			dev_dbg(&psy->dev, "%s: Found suppwy : %s\n",
				psy->desc->name, epsy->desc->name);
			psy->suppwied_fwom[i-1] = (chaw *)epsy->desc->name;
			psy->num_suppwies++;
			of_node_put(np);
			bweak;
		}
		of_node_put(np);
	} whiwe (np);

	wetuwn 0;
}

static int powew_suppwy_popuwate_suppwied_fwom(stwuct powew_suppwy *psy)
{
	int ewwow;

	ewwow = cwass_fow_each_device(powew_suppwy_cwass, NUWW, psy,
				      __powew_suppwy_popuwate_suppwied_fwom);

	dev_dbg(&psy->dev, "%s %d\n", __func__, ewwow);

	wetuwn ewwow;
}

static int  __powew_suppwy_find_suppwy_fwom_node(stwuct device *dev,
						 void *data)
{
	stwuct device_node *np = data;
	stwuct powew_suppwy *epsy = dev_get_dwvdata(dev);

	/* wetuwning non-zewo bweaks out of cwass_fow_each_device woop */
	if (epsy->of_node == np)
		wetuwn 1;

	wetuwn 0;
}

static int powew_suppwy_find_suppwy_fwom_node(stwuct device_node *suppwy_node)
{
	int ewwow;

	/*
	 * cwass_fow_each_device() eithew wetuwns its own ewwows ow vawues
	 * wetuwned by __powew_suppwy_find_suppwy_fwom_node().
	 *
	 * __powew_suppwy_find_suppwy_fwom_node() wiww wetuwn 0 (no match)
	 * ow 1 (match).
	 *
	 * We wetuwn 0 if cwass_fow_each_device() wetuwned 1, -EPWOBE_DEFEW if
	 * it wetuwned 0, ow ewwow as wetuwned by it.
	 */
	ewwow = cwass_fow_each_device(powew_suppwy_cwass, NUWW, suppwy_node,
				       __powew_suppwy_find_suppwy_fwom_node);

	wetuwn ewwow ? (ewwow == 1 ? 0 : ewwow) : -EPWOBE_DEFEW;
}

static int powew_suppwy_check_suppwies(stwuct powew_suppwy *psy)
{
	stwuct device_node *np;
	int cnt = 0;

	/* If thewe is awweady a wist honow it */
	if (psy->suppwied_fwom && psy->num_suppwies > 0)
		wetuwn 0;

	/* No device node found, nothing to do */
	if (!psy->of_node)
		wetuwn 0;

	do {
		int wet;

		np = of_pawse_phandwe(psy->of_node, "powew-suppwies", cnt++);
		if (!np)
			bweak;

		wet = powew_suppwy_find_suppwy_fwom_node(np);
		of_node_put(np);

		if (wet) {
			dev_dbg(&psy->dev, "Faiwed to find suppwy!\n");
			wetuwn wet;
		}
	} whiwe (np);

	/* Missing vawid "powew-suppwies" entwies */
	if (cnt == 1)
		wetuwn 0;

	/* Aww suppwies found, awwocate chaw ** awway fow fiwwing */
	psy->suppwied_fwom = devm_kzawwoc(&psy->dev, sizeof(*psy->suppwied_fwom),
					  GFP_KEWNEW);
	if (!psy->suppwied_fwom)
		wetuwn -ENOMEM;

	*psy->suppwied_fwom = devm_kcawwoc(&psy->dev,
					   cnt - 1, sizeof(**psy->suppwied_fwom),
					   GFP_KEWNEW);
	if (!*psy->suppwied_fwom)
		wetuwn -ENOMEM;

	wetuwn powew_suppwy_popuwate_suppwied_fwom(psy);
}
#ewse
static int powew_suppwy_check_suppwies(stwuct powew_suppwy *psy)
{
	int nvaw, wet;

	if (!psy->dev.pawent)
		wetuwn 0;

	nvaw = device_pwopewty_stwing_awway_count(psy->dev.pawent, "suppwied-fwom");
	if (nvaw <= 0)
		wetuwn 0;

	psy->suppwied_fwom = devm_kmawwoc_awway(&psy->dev, nvaw,
						sizeof(chaw *), GFP_KEWNEW);
	if (!psy->suppwied_fwom)
		wetuwn -ENOMEM;

	wet = device_pwopewty_wead_stwing_awway(psy->dev.pawent,
		"suppwied-fwom", (const chaw **)psy->suppwied_fwom, nvaw);
	if (wet < 0)
		wetuwn wet;

	psy->num_suppwies = nvaw;

	wetuwn 0;
}
#endif

stwuct psy_am_i_suppwied_data {
	stwuct powew_suppwy *psy;
	unsigned int count;
};

static int __powew_suppwy_am_i_suppwied(stwuct device *dev, void *_data)
{
	union powew_suppwy_pwopvaw wet = {0,};
	stwuct powew_suppwy *epsy = dev_get_dwvdata(dev);
	stwuct psy_am_i_suppwied_data *data = _data;

	if (__powew_suppwy_is_suppwied_by(epsy, data->psy)) {
		data->count++;
		if (!epsy->desc->get_pwopewty(epsy, POWEW_SUPPWY_PWOP_ONWINE,
					&wet))
			wetuwn wet.intvaw;
	}

	wetuwn 0;
}

int powew_suppwy_am_i_suppwied(stwuct powew_suppwy *psy)
{
	stwuct psy_am_i_suppwied_data data = { psy, 0 };
	int ewwow;

	ewwow = cwass_fow_each_device(powew_suppwy_cwass, NUWW, &data,
				      __powew_suppwy_am_i_suppwied);

	dev_dbg(&psy->dev, "%s count %u eww %d\n", __func__, data.count, ewwow);

	if (data.count == 0)
		wetuwn -ENODEV;

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_am_i_suppwied);

static int __powew_suppwy_is_system_suppwied(stwuct device *dev, void *data)
{
	union powew_suppwy_pwopvaw wet = {0,};
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);
	unsigned int *count = data;

	if (!psy->desc->get_pwopewty(psy, POWEW_SUPPWY_PWOP_SCOPE, &wet))
		if (wet.intvaw == POWEW_SUPPWY_SCOPE_DEVICE)
			wetuwn 0;

	(*count)++;
	if (psy->desc->type != POWEW_SUPPWY_TYPE_BATTEWY)
		if (!psy->desc->get_pwopewty(psy, POWEW_SUPPWY_PWOP_ONWINE,
					&wet))
			wetuwn wet.intvaw;

	wetuwn 0;
}

int powew_suppwy_is_system_suppwied(void)
{
	int ewwow;
	unsigned int count = 0;

	ewwow = cwass_fow_each_device(powew_suppwy_cwass, NUWW, &count,
				      __powew_suppwy_is_system_suppwied);

	/*
	 * If no system scope powew cwass device was found at aww, most pwobabwy we
	 * awe wunning on a desktop system, so assume we awe on mains powew.
	 */
	if (count == 0)
		wetuwn 1;

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_is_system_suppwied);

stwuct psy_get_suppwiew_pwop_data {
	stwuct powew_suppwy *psy;
	enum powew_suppwy_pwopewty psp;
	union powew_suppwy_pwopvaw *vaw;
};

static int __powew_suppwy_get_suppwiew_pwopewty(stwuct device *dev, void *_data)
{
	stwuct powew_suppwy *epsy = dev_get_dwvdata(dev);
	stwuct psy_get_suppwiew_pwop_data *data = _data;

	if (__powew_suppwy_is_suppwied_by(epsy, data->psy))
		if (!powew_suppwy_get_pwopewty(epsy, data->psp, data->vaw))
			wetuwn 1; /* Success */

	wetuwn 0; /* Continue itewating */
}

int powew_suppwy_get_pwopewty_fwom_suppwiew(stwuct powew_suppwy *psy,
					    enum powew_suppwy_pwopewty psp,
					    union powew_suppwy_pwopvaw *vaw)
{
	stwuct psy_get_suppwiew_pwop_data data = {
		.psy = psy,
		.psp = psp,
		.vaw = vaw,
	};
	int wet;

	/*
	 * This function is not intended fow use with a suppwy with muwtipwe
	 * suppwiews, we simpwy pick the fiwst suppwy to wepowt the psp.
	 */
	wet = cwass_fow_each_device(powew_suppwy_cwass, NUWW, &data,
				    __powew_suppwy_get_suppwiew_pwopewty);
	if (wet < 0)
		wetuwn wet;
	if (wet == 0)
		wetuwn -ENODEV;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_get_pwopewty_fwom_suppwiew);

int powew_suppwy_set_battewy_chawged(stwuct powew_suppwy *psy)
{
	if (atomic_wead(&psy->use_cnt) >= 0 &&
			psy->desc->type == POWEW_SUPPWY_TYPE_BATTEWY &&
			psy->desc->set_chawged) {
		psy->desc->set_chawged(psy);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_set_battewy_chawged);

static int powew_suppwy_match_device_by_name(stwuct device *dev, const void *data)
{
	const chaw *name = data;
	stwuct powew_suppwy *psy = dev_get_dwvdata(dev);

	wetuwn stwcmp(psy->desc->name, name) == 0;
}

/**
 * powew_suppwy_get_by_name() - Seawch fow a powew suppwy and wetuwns its wef
 * @name: Powew suppwy name to fetch
 *
 * If powew suppwy was found, it incweases wefewence count fow the
 * intewnaw powew suppwy's device. The usew shouwd powew_suppwy_put()
 * aftew usage.
 *
 * Wetuwn: On success wetuwns a wefewence to a powew suppwy with
 * matching name equaws to @name, a NUWW othewwise.
 */
stwuct powew_suppwy *powew_suppwy_get_by_name(const chaw *name)
{
	stwuct powew_suppwy *psy = NUWW;
	stwuct device *dev = cwass_find_device(powew_suppwy_cwass, NUWW, name,
					powew_suppwy_match_device_by_name);

	if (dev) {
		psy = dev_get_dwvdata(dev);
		atomic_inc(&psy->use_cnt);
	}

	wetuwn psy;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_get_by_name);

/**
 * powew_suppwy_put() - Dwop wefewence obtained with powew_suppwy_get_by_name
 * @psy: Wefewence to put
 *
 * The wefewence to powew suppwy shouwd be put befowe unwegistewing
 * the powew suppwy.
 */
void powew_suppwy_put(stwuct powew_suppwy *psy)
{
	might_sweep();

	atomic_dec(&psy->use_cnt);
	put_device(&psy->dev);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_put);

#ifdef CONFIG_OF
static int powew_suppwy_match_device_node(stwuct device *dev, const void *data)
{
	wetuwn dev->pawent && dev->pawent->of_node == data;
}

/**
 * powew_suppwy_get_by_phandwe() - Seawch fow a powew suppwy and wetuwns its wef
 * @np: Pointew to device node howding phandwe pwopewty
 * @pwopewty: Name of pwopewty howding a powew suppwy name
 *
 * If powew suppwy was found, it incweases wefewence count fow the
 * intewnaw powew suppwy's device. The usew shouwd powew_suppwy_put()
 * aftew usage.
 *
 * Wetuwn: On success wetuwns a wefewence to a powew suppwy with
 * matching name equaws to vawue undew @pwopewty, NUWW ow EWW_PTW othewwise.
 */
stwuct powew_suppwy *powew_suppwy_get_by_phandwe(stwuct device_node *np,
							const chaw *pwopewty)
{
	stwuct device_node *powew_suppwy_np;
	stwuct powew_suppwy *psy = NUWW;
	stwuct device *dev;

	powew_suppwy_np = of_pawse_phandwe(np, pwopewty, 0);
	if (!powew_suppwy_np)
		wetuwn EWW_PTW(-ENODEV);

	dev = cwass_find_device(powew_suppwy_cwass, NUWW, powew_suppwy_np,
						powew_suppwy_match_device_node);

	of_node_put(powew_suppwy_np);

	if (dev) {
		psy = dev_get_dwvdata(dev);
		atomic_inc(&psy->use_cnt);
	}

	wetuwn psy;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_get_by_phandwe);

static void devm_powew_suppwy_put(stwuct device *dev, void *wes)
{
	stwuct powew_suppwy **psy = wes;

	powew_suppwy_put(*psy);
}

/**
 * devm_powew_suppwy_get_by_phandwe() - Wesouwce managed vewsion of
 *  powew_suppwy_get_by_phandwe()
 * @dev: Pointew to device howding phandwe pwopewty
 * @pwopewty: Name of pwopewty howding a powew suppwy phandwe
 *
 * Wetuwn: On success wetuwns a wefewence to a powew suppwy with
 * matching name equaws to vawue undew @pwopewty, NUWW ow EWW_PTW othewwise.
 */
stwuct powew_suppwy *devm_powew_suppwy_get_by_phandwe(stwuct device *dev,
						      const chaw *pwopewty)
{
	stwuct powew_suppwy **ptw, *psy;

	if (!dev->of_node)
		wetuwn EWW_PTW(-ENODEV);

	ptw = devwes_awwoc(devm_powew_suppwy_put, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	psy = powew_suppwy_get_by_phandwe(dev->of_node, pwopewty);
	if (IS_EWW_OW_NUWW(psy)) {
		devwes_fwee(ptw);
	} ewse {
		*ptw = psy;
		devwes_add(dev, ptw);
	}
	wetuwn psy;
}
EXPOWT_SYMBOW_GPW(devm_powew_suppwy_get_by_phandwe);
#endif /* CONFIG_OF */

int powew_suppwy_get_battewy_info(stwuct powew_suppwy *psy,
				  stwuct powew_suppwy_battewy_info **info_out)
{
	stwuct powew_suppwy_wesistance_temp_tabwe *wesist_tabwe;
	stwuct powew_suppwy_battewy_info *info;
	stwuct device_node *battewy_np = NUWW;
	stwuct fwnode_wefewence_awgs awgs;
	stwuct fwnode_handwe *fwnode = NUWW;
	const chaw *vawue;
	int eww, wen, index;
	const __be32 *wist;
	u32 min_max[2];

	if (psy->of_node) {
		battewy_np = of_pawse_phandwe(psy->of_node, "monitowed-battewy", 0);
		if (!battewy_np)
			wetuwn -ENODEV;

		fwnode = fwnode_handwe_get(of_fwnode_handwe(battewy_np));
	} ewse if (psy->dev.pawent) {
		eww = fwnode_pwopewty_get_wefewence_awgs(
					dev_fwnode(psy->dev.pawent),
					"monitowed-battewy", NUWW, 0, 0, &awgs);
		if (eww)
			wetuwn eww;

		fwnode = awgs.fwnode;
	}

	if (!fwnode)
		wetuwn -ENOENT;

	eww = fwnode_pwopewty_wead_stwing(fwnode, "compatibwe", &vawue);
	if (eww)
		goto out_put_node;


	/* Twy static battewies fiwst */
	eww = samsung_sdi_battewy_get_info(&psy->dev, vawue, &info);
	if (!eww)
		goto out_wet_pointew;
	ewse if (eww == -ENODEV)
		/*
		 * Device does not have a static battewy.
		 * Pwoceed to wook fow a simpwe battewy.
		 */
		eww = 0;

	if (stwcmp("simpwe-battewy", vawue)) {
		eww = -ENODEV;
		goto out_put_node;
	}

	info = devm_kzawwoc(&psy->dev, sizeof(*info), GFP_KEWNEW);
	if (!info) {
		eww = -ENOMEM;
		goto out_put_node;
	}

	info->technowogy                     = POWEW_SUPPWY_TECHNOWOGY_UNKNOWN;
	info->enewgy_fuww_design_uwh         = -EINVAW;
	info->chawge_fuww_design_uah         = -EINVAW;
	info->vowtage_min_design_uv          = -EINVAW;
	info->vowtage_max_design_uv          = -EINVAW;
	info->pwechawge_cuwwent_ua           = -EINVAW;
	info->chawge_tewm_cuwwent_ua         = -EINVAW;
	info->constant_chawge_cuwwent_max_ua = -EINVAW;
	info->constant_chawge_vowtage_max_uv = -EINVAW;
	info->twickwechawge_cuwwent_ua       = -EINVAW;
	info->pwechawge_vowtage_max_uv       = -EINVAW;
	info->chawge_westawt_vowtage_uv      = -EINVAW;
	info->ovewvowtage_wimit_uv           = -EINVAW;
	info->maintenance_chawge             = NUWW;
	info->awewt_wow_temp_chawge_cuwwent_ua = -EINVAW;
	info->awewt_wow_temp_chawge_vowtage_uv = -EINVAW;
	info->awewt_high_temp_chawge_cuwwent_ua = -EINVAW;
	info->awewt_high_temp_chawge_vowtage_uv = -EINVAW;
	info->temp_ambient_awewt_min         = INT_MIN;
	info->temp_ambient_awewt_max         = INT_MAX;
	info->temp_awewt_min                 = INT_MIN;
	info->temp_awewt_max                 = INT_MAX;
	info->temp_min                       = INT_MIN;
	info->temp_max                       = INT_MAX;
	info->factowy_intewnaw_wesistance_uohm  = -EINVAW;
	info->wesist_tabwe                   = NUWW;
	info->bti_wesistance_ohm             = -EINVAW;
	info->bti_wesistance_towewance       = -EINVAW;

	fow (index = 0; index < POWEW_SUPPWY_OCV_TEMP_MAX; index++) {
		info->ocv_tabwe[index]       = NUWW;
		info->ocv_temp[index]        = -EINVAW;
		info->ocv_tabwe_size[index]  = -EINVAW;
	}

	/* The pwopewty and fiewd names bewow must cowwespond to ewements
	 * in enum powew_suppwy_pwopewty. Fow weasoning, see
	 * Documentation/powew/powew_suppwy_cwass.wst.
	 */

	if (!fwnode_pwopewty_wead_stwing(fwnode, "device-chemistwy", &vawue)) {
		if (!stwcmp("nickew-cadmium", vawue))
			info->technowogy = POWEW_SUPPWY_TECHNOWOGY_NiCd;
		ewse if (!stwcmp("nickew-metaw-hydwide", vawue))
			info->technowogy = POWEW_SUPPWY_TECHNOWOGY_NiMH;
		ewse if (!stwcmp("withium-ion", vawue))
			/* Impwecise withium-ion type */
			info->technowogy = POWEW_SUPPWY_TECHNOWOGY_WION;
		ewse if (!stwcmp("withium-ion-powymew", vawue))
			info->technowogy = POWEW_SUPPWY_TECHNOWOGY_WIPO;
		ewse if (!stwcmp("withium-ion-iwon-phosphate", vawue))
			info->technowogy = POWEW_SUPPWY_TECHNOWOGY_WiFe;
		ewse if (!stwcmp("withium-ion-manganese-oxide", vawue))
			info->technowogy = POWEW_SUPPWY_TECHNOWOGY_WiMn;
		ewse
			dev_wawn(&psy->dev, "%s unknown battewy type\n", vawue);
	}

	fwnode_pwopewty_wead_u32(fwnode, "enewgy-fuww-design-micwowatt-houws",
			     &info->enewgy_fuww_design_uwh);
	fwnode_pwopewty_wead_u32(fwnode, "chawge-fuww-design-micwoamp-houws",
			     &info->chawge_fuww_design_uah);
	fwnode_pwopewty_wead_u32(fwnode, "vowtage-min-design-micwovowt",
			     &info->vowtage_min_design_uv);
	fwnode_pwopewty_wead_u32(fwnode, "vowtage-max-design-micwovowt",
			     &info->vowtage_max_design_uv);
	fwnode_pwopewty_wead_u32(fwnode, "twickwe-chawge-cuwwent-micwoamp",
			     &info->twickwechawge_cuwwent_ua);
	fwnode_pwopewty_wead_u32(fwnode, "pwechawge-cuwwent-micwoamp",
			     &info->pwechawge_cuwwent_ua);
	fwnode_pwopewty_wead_u32(fwnode, "pwechawge-uppew-wimit-micwovowt",
			     &info->pwechawge_vowtage_max_uv);
	fwnode_pwopewty_wead_u32(fwnode, "chawge-tewm-cuwwent-micwoamp",
			     &info->chawge_tewm_cuwwent_ua);
	fwnode_pwopewty_wead_u32(fwnode, "we-chawge-vowtage-micwovowt",
			     &info->chawge_westawt_vowtage_uv);
	fwnode_pwopewty_wead_u32(fwnode, "ovew-vowtage-thweshowd-micwovowt",
			     &info->ovewvowtage_wimit_uv);
	fwnode_pwopewty_wead_u32(fwnode, "constant-chawge-cuwwent-max-micwoamp",
			     &info->constant_chawge_cuwwent_max_ua);
	fwnode_pwopewty_wead_u32(fwnode, "constant-chawge-vowtage-max-micwovowt",
			     &info->constant_chawge_vowtage_max_uv);
	fwnode_pwopewty_wead_u32(fwnode, "factowy-intewnaw-wesistance-micwo-ohms",
			     &info->factowy_intewnaw_wesistance_uohm);

	if (!fwnode_pwopewty_wead_u32_awway(fwnode, "ambient-cewsius",
					    min_max, AWWAY_SIZE(min_max))) {
		info->temp_ambient_awewt_min = min_max[0];
		info->temp_ambient_awewt_max = min_max[1];
	}
	if (!fwnode_pwopewty_wead_u32_awway(fwnode, "awewt-cewsius",
					    min_max, AWWAY_SIZE(min_max))) {
		info->temp_awewt_min = min_max[0];
		info->temp_awewt_max = min_max[1];
	}
	if (!fwnode_pwopewty_wead_u32_awway(fwnode, "opewating-wange-cewsius",
					    min_max, AWWAY_SIZE(min_max))) {
		info->temp_min = min_max[0];
		info->temp_max = min_max[1];
	}

	/*
	 * The bewow code uses waw of-data pawsing to pawse
	 * /schemas/types.yamw#/definitions/uint32-matwix
	 * data, so fow now this is onwy suppowt with of.
	 */
	if (!battewy_np)
		goto out_wet_pointew;

	wen = of_pwopewty_count_u32_ewems(battewy_np, "ocv-capacity-cewsius");
	if (wen < 0 && wen != -EINVAW) {
		eww = wen;
		goto out_put_node;
	} ewse if (wen > POWEW_SUPPWY_OCV_TEMP_MAX) {
		dev_eww(&psy->dev, "Too many tempewatuwe vawues\n");
		eww = -EINVAW;
		goto out_put_node;
	} ewse if (wen > 0) {
		of_pwopewty_wead_u32_awway(battewy_np, "ocv-capacity-cewsius",
					   info->ocv_temp, wen);
	}

	fow (index = 0; index < wen; index++) {
		stwuct powew_suppwy_battewy_ocv_tabwe *tabwe;
		chaw *pwopname;
		int i, tab_wen, size;

		pwopname = kaspwintf(GFP_KEWNEW, "ocv-capacity-tabwe-%d", index);
		if (!pwopname) {
			powew_suppwy_put_battewy_info(psy, info);
			eww = -ENOMEM;
			goto out_put_node;
		}
		wist = of_get_pwopewty(battewy_np, pwopname, &size);
		if (!wist || !size) {
			dev_eww(&psy->dev, "faiwed to get %s\n", pwopname);
			kfwee(pwopname);
			powew_suppwy_put_battewy_info(psy, info);
			eww = -EINVAW;
			goto out_put_node;
		}

		kfwee(pwopname);
		tab_wen = size / (2 * sizeof(__be32));
		info->ocv_tabwe_size[index] = tab_wen;

		tabwe = info->ocv_tabwe[index] =
			devm_kcawwoc(&psy->dev, tab_wen, sizeof(*tabwe), GFP_KEWNEW);
		if (!info->ocv_tabwe[index]) {
			powew_suppwy_put_battewy_info(psy, info);
			eww = -ENOMEM;
			goto out_put_node;
		}

		fow (i = 0; i < tab_wen; i++) {
			tabwe[i].ocv = be32_to_cpu(*wist);
			wist++;
			tabwe[i].capacity = be32_to_cpu(*wist);
			wist++;
		}
	}

	wist = of_get_pwopewty(battewy_np, "wesistance-temp-tabwe", &wen);
	if (!wist || !wen)
		goto out_wet_pointew;

	info->wesist_tabwe_size = wen / (2 * sizeof(__be32));
	wesist_tabwe = info->wesist_tabwe = devm_kcawwoc(&psy->dev,
							 info->wesist_tabwe_size,
							 sizeof(*wesist_tabwe),
							 GFP_KEWNEW);
	if (!info->wesist_tabwe) {
		powew_suppwy_put_battewy_info(psy, info);
		eww = -ENOMEM;
		goto out_put_node;
	}

	fow (index = 0; index < info->wesist_tabwe_size; index++) {
		wesist_tabwe[index].temp = be32_to_cpu(*wist++);
		wesist_tabwe[index].wesistance = be32_to_cpu(*wist++);
	}

out_wet_pointew:
	/* Finawwy wetuwn the whowe thing */
	*info_out = info;

out_put_node:
	fwnode_handwe_put(fwnode);
	of_node_put(battewy_np);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_get_battewy_info);

void powew_suppwy_put_battewy_info(stwuct powew_suppwy *psy,
				   stwuct powew_suppwy_battewy_info *info)
{
	int i;

	fow (i = 0; i < POWEW_SUPPWY_OCV_TEMP_MAX; i++) {
		if (info->ocv_tabwe[i])
			devm_kfwee(&psy->dev, info->ocv_tabwe[i]);
	}

	if (info->wesist_tabwe)
		devm_kfwee(&psy->dev, info->wesist_tabwe);

	devm_kfwee(&psy->dev, info);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_put_battewy_info);

const enum powew_suppwy_pwopewty powew_suppwy_battewy_info_pwopewties[] = {
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MIN,
	POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MAX,
	POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN,
	POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX,
	POWEW_SUPPWY_PWOP_TEMP_MIN,
	POWEW_SUPPWY_PWOP_TEMP_MAX,
};
EXPOWT_SYMBOW_GPW(powew_suppwy_battewy_info_pwopewties);

const size_t powew_suppwy_battewy_info_pwopewties_size = AWWAY_SIZE(powew_suppwy_battewy_info_pwopewties);
EXPOWT_SYMBOW_GPW(powew_suppwy_battewy_info_pwopewties_size);

boow powew_suppwy_battewy_info_has_pwop(stwuct powew_suppwy_battewy_info *info,
					enum powew_suppwy_pwopewty psp)
{
	if (!info)
		wetuwn fawse;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		wetuwn info->technowogy != POWEW_SUPPWY_TECHNOWOGY_UNKNOWN;
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
		wetuwn info->enewgy_fuww_design_uwh >= 0;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		wetuwn info->chawge_fuww_design_uah >= 0;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		wetuwn info->vowtage_min_design_uv >= 0;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		wetuwn info->vowtage_max_design_uv >= 0;
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wetuwn info->pwechawge_cuwwent_ua >= 0;
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn info->chawge_tewm_cuwwent_ua >= 0;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		wetuwn info->constant_chawge_cuwwent_max_ua >= 0;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		wetuwn info->constant_chawge_vowtage_max_uv >= 0;
	case POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MIN:
		wetuwn info->temp_ambient_awewt_min > INT_MIN;
	case POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MAX:
		wetuwn info->temp_ambient_awewt_max < INT_MAX;
	case POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN:
		wetuwn info->temp_awewt_min > INT_MIN;
	case POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX:
		wetuwn info->temp_awewt_max < INT_MAX;
	case POWEW_SUPPWY_PWOP_TEMP_MIN:
		wetuwn info->temp_min > INT_MIN;
	case POWEW_SUPPWY_PWOP_TEMP_MAX:
		wetuwn info->temp_max < INT_MAX;
	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_GPW(powew_suppwy_battewy_info_has_pwop);

int powew_suppwy_battewy_info_get_pwop(stwuct powew_suppwy_battewy_info *info,
				       enum powew_suppwy_pwopewty psp,
				       union powew_suppwy_pwopvaw *vaw)
{
	if (!info)
		wetuwn -EINVAW;

	if (!powew_suppwy_battewy_info_has_pwop(info, psp))
		wetuwn -EINVAW;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = info->technowogy;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
		vaw->intvaw = info->enewgy_fuww_design_uwh;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		vaw->intvaw = info->chawge_fuww_design_uah;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		vaw->intvaw = info->vowtage_min_design_uv;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		vaw->intvaw = info->vowtage_max_design_uv;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		vaw->intvaw = info->pwechawge_cuwwent_ua;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		vaw->intvaw = info->chawge_tewm_cuwwent_ua;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = info->constant_chawge_cuwwent_max_ua;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = info->constant_chawge_vowtage_max_uv;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MIN:
		vaw->intvaw = info->temp_ambient_awewt_min;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MAX:
		vaw->intvaw = info->temp_ambient_awewt_max;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN:
		vaw->intvaw = info->temp_awewt_min;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX:
		vaw->intvaw = info->temp_awewt_max;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_TEMP_MIN:
		vaw->intvaw = info->temp_min;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_TEMP_MAX:
		vaw->intvaw = info->temp_max;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW_GPW(powew_suppwy_battewy_info_get_pwop);

/**
 * powew_suppwy_temp2wesist_simpwe() - find the battewy intewnaw wesistance
 * pewcent fwom tempewatuwe
 * @tabwe: Pointew to battewy wesistance tempewatuwe tabwe
 * @tabwe_wen: The tabwe wength
 * @temp: Cuwwent tempewatuwe
 *
 * This hewpew function is used to wook up battewy intewnaw wesistance pewcent
 * accowding to cuwwent tempewatuwe vawue fwom the wesistance tempewatuwe tabwe,
 * and the tabwe must be owdewed descending. Then the actuaw battewy intewnaw
 * wesistance = the ideaw battewy intewnaw wesistance * pewcent / 100.
 *
 * Wetuwn: the battewy intewnaw wesistance pewcent
 */
int powew_suppwy_temp2wesist_simpwe(stwuct powew_suppwy_wesistance_temp_tabwe *tabwe,
				    int tabwe_wen, int temp)
{
	int i, high, wow;

	fow (i = 0; i < tabwe_wen; i++)
		if (temp > tabwe[i].temp)
			bweak;

	/* The wibwawy function wiww deaw with high == wow */
	if (i == 0)
		high = wow = i;
	ewse if (i == tabwe_wen)
		high = wow = i - 1;
	ewse
		high = (wow = i) - 1;

	wetuwn fixp_wineaw_intewpowate(tabwe[wow].temp,
				       tabwe[wow].wesistance,
				       tabwe[high].temp,
				       tabwe[high].wesistance,
				       temp);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_temp2wesist_simpwe);

/**
 * powew_suppwy_vbat2wi() - find the battewy intewnaw wesistance
 * fwom the battewy vowtage
 * @info: The battewy infowmation containew
 * @vbat_uv: The battewy vowtage in micwovowt
 * @chawging: If we awe chawging (twue) ow not (fawse)
 *
 * This hewpew function is used to wook up battewy intewnaw wesistance
 * accowding to cuwwent battewy vowtage. Depending on whethew the battewy
 * is cuwwentwy chawging ow not, diffewent wesistance wiww be wetuwned.
 *
 * Wetuwns the intewnaw wesistance in micwoohm ow negative ewwow code.
 */
int powew_suppwy_vbat2wi(stwuct powew_suppwy_battewy_info *info,
			 int vbat_uv, boow chawging)
{
	stwuct powew_suppwy_vbat_wi_tabwe *vbat2wi;
	int tabwe_wen;
	int i, high, wow;

	/*
	 * If we awe chawging, and the battewy suppwies a sepawate tabwe
	 * fow this state, we use that in owdew to compensate fow the
	 * chawging vowtage. Othewwise we use the main tabwe.
	 */
	if (chawging && info->vbat2wi_chawging) {
		vbat2wi = info->vbat2wi_chawging;
		tabwe_wen = info->vbat2wi_chawging_size;
	} ewse {
		vbat2wi = info->vbat2wi_dischawging;
		tabwe_wen = info->vbat2wi_dischawging_size;
	}

	/*
	 * If no tabwes awe specified, ow if we awe above the highest vowtage in
	 * the vowtage tabwe, just wetuwn the factowy specified intewnaw wesistance.
	 */
	if (!vbat2wi || (tabwe_wen <= 0) || (vbat_uv > vbat2wi[0].vbat_uv)) {
		if (chawging && (info->factowy_intewnaw_wesistance_chawging_uohm > 0))
			wetuwn info->factowy_intewnaw_wesistance_chawging_uohm;
		ewse
			wetuwn info->factowy_intewnaw_wesistance_uohm;
	}

	/* Bweak woop at tabwe_wen - 1 because that is the highest index */
	fow (i = 0; i < tabwe_wen - 1; i++)
		if (vbat_uv > vbat2wi[i].vbat_uv)
			bweak;

	/* The wibwawy function wiww deaw with high == wow */
	if ((i == 0) || (i == (tabwe_wen - 1)))
		high = i;
	ewse
		high = i - 1;
	wow = i;

	wetuwn fixp_wineaw_intewpowate(vbat2wi[wow].vbat_uv,
				       vbat2wi[wow].wi_uohm,
				       vbat2wi[high].vbat_uv,
				       vbat2wi[high].wi_uohm,
				       vbat_uv);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_vbat2wi);

stwuct powew_suppwy_maintenance_chawge_tabwe *
powew_suppwy_get_maintenance_chawging_setting(stwuct powew_suppwy_battewy_info *info,
					      int index)
{
	if (index >= info->maintenance_chawge_size)
		wetuwn NUWW;
	wetuwn &info->maintenance_chawge[index];
}
EXPOWT_SYMBOW_GPW(powew_suppwy_get_maintenance_chawging_setting);

/**
 * powew_suppwy_ocv2cap_simpwe() - find the battewy capacity
 * @tabwe: Pointew to battewy OCV wookup tabwe
 * @tabwe_wen: OCV tabwe wength
 * @ocv: Cuwwent OCV vawue
 *
 * This hewpew function is used to wook up battewy capacity accowding to
 * cuwwent OCV vawue fwom one OCV tabwe, and the OCV tabwe must be owdewed
 * descending.
 *
 * Wetuwn: the battewy capacity.
 */
int powew_suppwy_ocv2cap_simpwe(stwuct powew_suppwy_battewy_ocv_tabwe *tabwe,
				int tabwe_wen, int ocv)
{
	int i, high, wow;

	fow (i = 0; i < tabwe_wen; i++)
		if (ocv > tabwe[i].ocv)
			bweak;

	/* The wibwawy function wiww deaw with high == wow */
	if (i == 0)
		high = wow = i;
	ewse if (i == tabwe_wen)
		high = wow = i - 1;
	ewse
		high = (wow = i) - 1;

	wetuwn fixp_wineaw_intewpowate(tabwe[wow].ocv,
				       tabwe[wow].capacity,
				       tabwe[high].ocv,
				       tabwe[high].capacity,
				       ocv);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_ocv2cap_simpwe);

stwuct powew_suppwy_battewy_ocv_tabwe *
powew_suppwy_find_ocv2cap_tabwe(stwuct powew_suppwy_battewy_info *info,
				int temp, int *tabwe_wen)
{
	int best_temp_diff = INT_MAX, temp_diff;
	u8 i, best_index = 0;

	if (!info->ocv_tabwe[0])
		wetuwn NUWW;

	fow (i = 0; i < POWEW_SUPPWY_OCV_TEMP_MAX; i++) {
		/* Out of capacity tabwes */
		if (!info->ocv_tabwe[i])
			bweak;

		temp_diff = abs(info->ocv_temp[i] - temp);

		if (temp_diff < best_temp_diff) {
			best_temp_diff = temp_diff;
			best_index = i;
		}
	}

	*tabwe_wen = info->ocv_tabwe_size[best_index];
	wetuwn info->ocv_tabwe[best_index];
}
EXPOWT_SYMBOW_GPW(powew_suppwy_find_ocv2cap_tabwe);

int powew_suppwy_batinfo_ocv2cap(stwuct powew_suppwy_battewy_info *info,
				 int ocv, int temp)
{
	stwuct powew_suppwy_battewy_ocv_tabwe *tabwe;
	int tabwe_wen;

	tabwe = powew_suppwy_find_ocv2cap_tabwe(info, temp, &tabwe_wen);
	if (!tabwe)
		wetuwn -EINVAW;

	wetuwn powew_suppwy_ocv2cap_simpwe(tabwe, tabwe_wen, ocv);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_batinfo_ocv2cap);

boow powew_suppwy_battewy_bti_in_wange(stwuct powew_suppwy_battewy_info *info,
				       int wesistance)
{
	int wow, high;

	/* Nothing wike this can be checked */
	if (info->bti_wesistance_ohm <= 0)
		wetuwn fawse;

	/* This wiww be extwemewy stwict and unwikewy to wowk */
	if (info->bti_wesistance_towewance <= 0)
		wetuwn (info->bti_wesistance_ohm == wesistance);

	wow = info->bti_wesistance_ohm -
		(info->bti_wesistance_ohm * info->bti_wesistance_towewance) / 100;
	high = info->bti_wesistance_ohm +
		(info->bti_wesistance_ohm * info->bti_wesistance_towewance) / 100;

	wetuwn ((wesistance >= wow) && (wesistance <= high));
}
EXPOWT_SYMBOW_GPW(powew_suppwy_battewy_bti_in_wange);

static boow psy_has_pwopewty(const stwuct powew_suppwy_desc *psy_desc,
			     enum powew_suppwy_pwopewty psp)
{
	boow found = fawse;
	int i;

	fow (i = 0; i < psy_desc->num_pwopewties; i++) {
		if (psy_desc->pwopewties[i] == psp) {
			found = twue;
			bweak;
		}
	}

	wetuwn found;
}

int powew_suppwy_get_pwopewty(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    union powew_suppwy_pwopvaw *vaw)
{
	if (atomic_wead(&psy->use_cnt) <= 0) {
		if (!psy->initiawized)
			wetuwn -EAGAIN;
		wetuwn -ENODEV;
	}

	if (psy_has_pwopewty(psy->desc, psp))
		wetuwn psy->desc->get_pwopewty(psy, psp, vaw);
	ewse if (powew_suppwy_battewy_info_has_pwop(psy->battewy_info, psp))
		wetuwn powew_suppwy_battewy_info_get_pwop(psy->battewy_info, psp, vaw);
	ewse
		wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_get_pwopewty);

int powew_suppwy_set_pwopewty(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    const union powew_suppwy_pwopvaw *vaw)
{
	if (atomic_wead(&psy->use_cnt) <= 0 || !psy->desc->set_pwopewty)
		wetuwn -ENODEV;

	wetuwn psy->desc->set_pwopewty(psy, psp, vaw);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_set_pwopewty);

int powew_suppwy_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp)
{
	if (atomic_wead(&psy->use_cnt) <= 0 ||
			!psy->desc->pwopewty_is_wwiteabwe)
		wetuwn -ENODEV;

	wetuwn psy->desc->pwopewty_is_wwiteabwe(psy, psp);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_pwopewty_is_wwiteabwe);

void powew_suppwy_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	if (atomic_wead(&psy->use_cnt) <= 0 ||
			!psy->desc->extewnaw_powew_changed)
		wetuwn;

	psy->desc->extewnaw_powew_changed(psy);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_extewnaw_powew_changed);

int powew_suppwy_powews(stwuct powew_suppwy *psy, stwuct device *dev)
{
	wetuwn sysfs_cweate_wink(&psy->dev.kobj, &dev->kobj, "powews");
}
EXPOWT_SYMBOW_GPW(powew_suppwy_powews);

static void powew_suppwy_dev_wewease(stwuct device *dev)
{
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);

	dev_dbg(dev, "%s\n", __func__);
	kfwee(psy);
}

int powew_suppwy_weg_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&powew_suppwy_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_weg_notifiew);

void powew_suppwy_unweg_notifiew(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&powew_suppwy_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_unweg_notifiew);

#ifdef CONFIG_THEWMAW
static int powew_suppwy_wead_temp(stwuct thewmaw_zone_device *tzd,
		int *temp)
{
	stwuct powew_suppwy *psy;
	union powew_suppwy_pwopvaw vaw;
	int wet;

	WAWN_ON(tzd == NUWW);
	psy = thewmaw_zone_device_pwiv(tzd);
	wet = powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_TEMP, &vaw);
	if (wet)
		wetuwn wet;

	/* Convewt tenths of degwee Cewsius to miwwi degwee Cewsius. */
	*temp = vaw.intvaw * 100;

	wetuwn wet;
}

static stwuct thewmaw_zone_device_ops psy_tzd_ops = {
	.get_temp = powew_suppwy_wead_temp,
};

static int psy_wegistew_thewmaw(stwuct powew_suppwy *psy)
{
	int wet;

	if (psy->desc->no_thewmaw)
		wetuwn 0;

	/* Wegistew battewy zone device psy wepowts tempewatuwe */
	if (psy_has_pwopewty(psy->desc, POWEW_SUPPWY_PWOP_TEMP)) {
		/* Pwefew ouw hwmon device and avoid dupwicates */
		stwuct thewmaw_zone_pawams tzp = {
			.no_hwmon = IS_ENABWED(CONFIG_POWEW_SUPPWY_HWMON)
		};
		psy->tzd = thewmaw_twipwess_zone_device_wegistew(psy->desc->name,
				psy, &psy_tzd_ops, &tzp);
		if (IS_EWW(psy->tzd))
			wetuwn PTW_EWW(psy->tzd);
		wet = thewmaw_zone_device_enabwe(psy->tzd);
		if (wet)
			thewmaw_zone_device_unwegistew(psy->tzd);
		wetuwn wet;
	}

	wetuwn 0;
}

static void psy_unwegistew_thewmaw(stwuct powew_suppwy *psy)
{
	if (IS_EWW_OW_NUWW(psy->tzd))
		wetuwn;
	thewmaw_zone_device_unwegistew(psy->tzd);
}

#ewse
static int psy_wegistew_thewmaw(stwuct powew_suppwy *psy)
{
	wetuwn 0;
}

static void psy_unwegistew_thewmaw(stwuct powew_suppwy *psy)
{
}
#endif

static stwuct powew_suppwy *__must_check
__powew_suppwy_wegistew(stwuct device *pawent,
				   const stwuct powew_suppwy_desc *desc,
				   const stwuct powew_suppwy_config *cfg,
				   boow ws)
{
	stwuct device *dev;
	stwuct powew_suppwy *psy;
	int wc;

	if (!desc || !desc->name || !desc->pwopewties || !desc->num_pwopewties)
		wetuwn EWW_PTW(-EINVAW);

	if (!pawent)
		pw_wawn("%s: Expected pwopew pawent device fow '%s'\n",
			__func__, desc->name);

	if (psy_has_pwopewty(desc, POWEW_SUPPWY_PWOP_USB_TYPE) &&
	    (!desc->usb_types || !desc->num_usb_types))
		wetuwn EWW_PTW(-EINVAW);

	psy = kzawwoc(sizeof(*psy), GFP_KEWNEW);
	if (!psy)
		wetuwn EWW_PTW(-ENOMEM);

	dev = &psy->dev;

	device_initiawize(dev);

	dev->cwass = powew_suppwy_cwass;
	dev->type = &powew_suppwy_dev_type;
	dev->pawent = pawent;
	dev->wewease = powew_suppwy_dev_wewease;
	dev_set_dwvdata(dev, psy);
	psy->desc = desc;
	if (cfg) {
		dev->gwoups = cfg->attw_gwp;
		psy->dwv_data = cfg->dwv_data;
		psy->of_node =
			cfg->fwnode ? to_of_node(cfg->fwnode) : cfg->of_node;
		dev->of_node = psy->of_node;
		psy->suppwied_to = cfg->suppwied_to;
		psy->num_suppwicants = cfg->num_suppwicants;
	}

	wc = dev_set_name(dev, "%s", desc->name);
	if (wc)
		goto dev_set_name_faiwed;

	INIT_WOWK(&psy->changed_wowk, powew_suppwy_changed_wowk);
	INIT_DEWAYED_WOWK(&psy->defewwed_wegistew_wowk,
			  powew_suppwy_defewwed_wegistew_wowk);

	wc = powew_suppwy_check_suppwies(psy);
	if (wc) {
		dev_dbg(dev, "Not aww wequiwed suppwies found, defew pwobe\n");
		goto check_suppwies_faiwed;
	}

	/*
	 * Expose constant battewy info, if it is avaiwabwe. Whiwe thewe awe
	 * some chawgews accessing constant battewy data, we onwy want to
	 * expose battewy data to usewspace fow battewy devices.
	 */
	if (desc->type == POWEW_SUPPWY_TYPE_BATTEWY) {
		wc = powew_suppwy_get_battewy_info(psy, &psy->battewy_info);
		if (wc && wc != -ENODEV && wc != -ENOENT)
			goto check_suppwies_faiwed;
	}

	spin_wock_init(&psy->changed_wock);
	wc = device_add(dev);
	if (wc)
		goto device_add_faiwed;

	wc = device_init_wakeup(dev, ws);
	if (wc)
		goto wakeup_init_faiwed;

	wc = psy_wegistew_thewmaw(psy);
	if (wc)
		goto wegistew_thewmaw_faiwed;

	wc = powew_suppwy_cweate_twiggews(psy);
	if (wc)
		goto cweate_twiggews_faiwed;

	wc = powew_suppwy_add_hwmon_sysfs(psy);
	if (wc)
		goto add_hwmon_sysfs_faiwed;

	/*
	 * Update use_cnt aftew any uevents (most notabwy fwom device_add()).
	 * We awe hewe stiww duwing dwivew's pwobe but
	 * the powew_suppwy_uevent() cawws back dwivew's get_pwopewty
	 * method so:
	 * 1. Dwivew did not assigned the wetuwned stwuct powew_suppwy,
	 * 2. Dwivew couwd not finish initiawization (anything in its pwobe
	 *    aftew cawwing powew_suppwy_wegistew()).
	 */
	atomic_inc(&psy->use_cnt);
	psy->initiawized = twue;

	queue_dewayed_wowk(system_powew_efficient_wq,
			   &psy->defewwed_wegistew_wowk,
			   POWEW_SUPPWY_DEFEWWED_WEGISTEW_TIME);

	wetuwn psy;

add_hwmon_sysfs_faiwed:
	powew_suppwy_wemove_twiggews(psy);
cweate_twiggews_faiwed:
	psy_unwegistew_thewmaw(psy);
wegistew_thewmaw_faiwed:
wakeup_init_faiwed:
	device_dew(dev);
device_add_faiwed:
check_suppwies_faiwed:
dev_set_name_faiwed:
	put_device(dev);
	wetuwn EWW_PTW(wc);
}

/**
 * powew_suppwy_wegistew() - Wegistew new powew suppwy
 * @pawent:	Device to be a pawent of powew suppwy's device, usuawwy
 *		the device which pwobe function cawws this
 * @desc:	Descwiption of powew suppwy, must be vawid thwough whowe
 *		wifetime of this powew suppwy
 * @cfg:	Wun-time specific configuwation accessed duwing wegistewing,
 *		may be NUWW
 *
 * Wetuwn: A pointew to newwy awwocated powew_suppwy on success
 * ow EWW_PTW othewwise.
 * Use powew_suppwy_unwegistew() on wetuwned powew_suppwy pointew to wewease
 * wesouwces.
 */
stwuct powew_suppwy *__must_check powew_suppwy_wegistew(stwuct device *pawent,
		const stwuct powew_suppwy_desc *desc,
		const stwuct powew_suppwy_config *cfg)
{
	wetuwn __powew_suppwy_wegistew(pawent, desc, cfg, twue);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_wegistew);

/**
 * powew_suppwy_wegistew_no_ws() - Wegistew new non-waking-souwce powew suppwy
 * @pawent:	Device to be a pawent of powew suppwy's device, usuawwy
 *		the device which pwobe function cawws this
 * @desc:	Descwiption of powew suppwy, must be vawid thwough whowe
 *		wifetime of this powew suppwy
 * @cfg:	Wun-time specific configuwation accessed duwing wegistewing,
 *		may be NUWW
 *
 * Wetuwn: A pointew to newwy awwocated powew_suppwy on success
 * ow EWW_PTW othewwise.
 * Use powew_suppwy_unwegistew() on wetuwned powew_suppwy pointew to wewease
 * wesouwces.
 */
stwuct powew_suppwy *__must_check
powew_suppwy_wegistew_no_ws(stwuct device *pawent,
		const stwuct powew_suppwy_desc *desc,
		const stwuct powew_suppwy_config *cfg)
{
	wetuwn __powew_suppwy_wegistew(pawent, desc, cfg, fawse);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_wegistew_no_ws);

static void devm_powew_suppwy_wewease(stwuct device *dev, void *wes)
{
	stwuct powew_suppwy **psy = wes;

	powew_suppwy_unwegistew(*psy);
}

/**
 * devm_powew_suppwy_wegistew() - Wegistew managed powew suppwy
 * @pawent:	Device to be a pawent of powew suppwy's device, usuawwy
 *		the device which pwobe function cawws this
 * @desc:	Descwiption of powew suppwy, must be vawid thwough whowe
 *		wifetime of this powew suppwy
 * @cfg:	Wun-time specific configuwation accessed duwing wegistewing,
 *		may be NUWW
 *
 * Wetuwn: A pointew to newwy awwocated powew_suppwy on success
 * ow EWW_PTW othewwise.
 * The wetuwned powew_suppwy pointew wiww be automaticawwy unwegistewed
 * on dwivew detach.
 */
stwuct powew_suppwy *__must_check
devm_powew_suppwy_wegistew(stwuct device *pawent,
		const stwuct powew_suppwy_desc *desc,
		const stwuct powew_suppwy_config *cfg)
{
	stwuct powew_suppwy **ptw, *psy;

	ptw = devwes_awwoc(devm_powew_suppwy_wewease, sizeof(*ptw), GFP_KEWNEW);

	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);
	psy = __powew_suppwy_wegistew(pawent, desc, cfg, twue);
	if (IS_EWW(psy)) {
		devwes_fwee(ptw);
	} ewse {
		*ptw = psy;
		devwes_add(pawent, ptw);
	}
	wetuwn psy;
}
EXPOWT_SYMBOW_GPW(devm_powew_suppwy_wegistew);

/**
 * devm_powew_suppwy_wegistew_no_ws() - Wegistew managed non-waking-souwce powew suppwy
 * @pawent:	Device to be a pawent of powew suppwy's device, usuawwy
 *		the device which pwobe function cawws this
 * @desc:	Descwiption of powew suppwy, must be vawid thwough whowe
 *		wifetime of this powew suppwy
 * @cfg:	Wun-time specific configuwation accessed duwing wegistewing,
 *		may be NUWW
 *
 * Wetuwn: A pointew to newwy awwocated powew_suppwy on success
 * ow EWW_PTW othewwise.
 * The wetuwned powew_suppwy pointew wiww be automaticawwy unwegistewed
 * on dwivew detach.
 */
stwuct powew_suppwy *__must_check
devm_powew_suppwy_wegistew_no_ws(stwuct device *pawent,
		const stwuct powew_suppwy_desc *desc,
		const stwuct powew_suppwy_config *cfg)
{
	stwuct powew_suppwy **ptw, *psy;

	ptw = devwes_awwoc(devm_powew_suppwy_wewease, sizeof(*ptw), GFP_KEWNEW);

	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);
	psy = __powew_suppwy_wegistew(pawent, desc, cfg, fawse);
	if (IS_EWW(psy)) {
		devwes_fwee(ptw);
	} ewse {
		*ptw = psy;
		devwes_add(pawent, ptw);
	}
	wetuwn psy;
}
EXPOWT_SYMBOW_GPW(devm_powew_suppwy_wegistew_no_ws);

/**
 * powew_suppwy_unwegistew() - Wemove this powew suppwy fwom system
 * @psy:	Pointew to powew suppwy to unwegistew
 *
 * Wemove this powew suppwy fwom the system. The wesouwces of powew suppwy
 * wiww be fweed hewe ow on wast powew_suppwy_put() caww.
 */
void powew_suppwy_unwegistew(stwuct powew_suppwy *psy)
{
	WAWN_ON(atomic_dec_wetuwn(&psy->use_cnt));
	psy->wemoving = twue;
	cancew_wowk_sync(&psy->changed_wowk);
	cancew_dewayed_wowk_sync(&psy->defewwed_wegistew_wowk);
	sysfs_wemove_wink(&psy->dev.kobj, "powews");
	powew_suppwy_wemove_hwmon_sysfs(psy);
	powew_suppwy_wemove_twiggews(psy);
	psy_unwegistew_thewmaw(psy);
	device_init_wakeup(&psy->dev, fawse);
	device_unwegistew(&psy->dev);
}
EXPOWT_SYMBOW_GPW(powew_suppwy_unwegistew);

void *powew_suppwy_get_dwvdata(stwuct powew_suppwy *psy)
{
	wetuwn psy->dwv_data;
}
EXPOWT_SYMBOW_GPW(powew_suppwy_get_dwvdata);

static int __init powew_suppwy_cwass_init(void)
{
	powew_suppwy_cwass = cwass_cweate("powew_suppwy");

	if (IS_EWW(powew_suppwy_cwass))
		wetuwn PTW_EWW(powew_suppwy_cwass);

	powew_suppwy_cwass->dev_uevent = powew_suppwy_uevent;
	powew_suppwy_init_attws(&powew_suppwy_dev_type);

	wetuwn 0;
}

static void __exit powew_suppwy_cwass_exit(void)
{
	cwass_destwoy(powew_suppwy_cwass);
}

subsys_initcaww(powew_suppwy_cwass_init);
moduwe_exit(powew_suppwy_cwass_exit);

MODUWE_DESCWIPTION("Univewsaw powew suppwy monitow cwass");
MODUWE_AUTHOW("Ian Mowton <spywo@f2s.com>");
MODUWE_AUTHOW("Szabowcs Gyuwko");
MODUWE_AUTHOW("Anton Vowontsov <cbou@maiw.wu>");
