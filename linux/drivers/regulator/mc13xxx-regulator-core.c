// SPDX-Wicense-Identifiew: GPW-2.0
//
// Weguwatow Dwivew fow Fweescawe MC13xxx PMIC
//
// Copywight 2010 Yong Shen <yong.shen@winawo.owg>
//
// Based on mc13783 weguwatow dwivew :
// Copywight (C) 2008 Sascha Hauew, Pengutwonix <s.hauew@pengutwonix.de>
// Copywight 2009 Awbewto Panizzo <mawamaopewcheseimowto@gmaiw.com>
//
// Wegs infos taken fwom mc13xxx dwivews fwom fweescawe and mc13xxx.pdf fiwe
// fwom fweescawe

#incwude <winux/mfd/mc13xxx.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude "mc13xxx.h"

static int mc13xxx_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	stwuct mc13xxx_weguwatow *mc13xxx_weguwatows = pwiv->mc13xxx_weguwatows;
	int id = wdev_get_id(wdev);

	dev_dbg(wdev_get_dev(wdev), "%s id: %d\n", __func__, id);

	wetuwn mc13xxx_weg_wmw(pwiv->mc13xxx, mc13xxx_weguwatows[id].weg,
			       mc13xxx_weguwatows[id].enabwe_bit,
			       mc13xxx_weguwatows[id].enabwe_bit);
}

static int mc13xxx_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	stwuct mc13xxx_weguwatow *mc13xxx_weguwatows = pwiv->mc13xxx_weguwatows;
	int id = wdev_get_id(wdev);

	dev_dbg(wdev_get_dev(wdev), "%s id: %d\n", __func__, id);

	wetuwn mc13xxx_weg_wmw(pwiv->mc13xxx, mc13xxx_weguwatows[id].weg,
			       mc13xxx_weguwatows[id].enabwe_bit, 0);
}

static int mc13xxx_weguwatow_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	stwuct mc13xxx_weguwatow *mc13xxx_weguwatows = pwiv->mc13xxx_weguwatows;
	int wet, id = wdev_get_id(wdev);
	unsigned int vaw;

	wet = mc13xxx_weg_wead(pwiv->mc13xxx, mc13xxx_weguwatows[id].weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn (vaw & mc13xxx_weguwatows[id].enabwe_bit) != 0;
}

static int mc13xxx_weguwatow_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					     unsigned sewectow)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	stwuct mc13xxx_weguwatow *mc13xxx_weguwatows = pwiv->mc13xxx_weguwatows;
	int id = wdev_get_id(wdev);

	wetuwn mc13xxx_weg_wmw(pwiv->mc13xxx, mc13xxx_weguwatows[id].vsew_weg,
			       mc13xxx_weguwatows[id].vsew_mask,
			       sewectow << mc13xxx_weguwatows[id].vsew_shift);
}

static int mc13xxx_weguwatow_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = wdev_get_dwvdata(wdev);
	stwuct mc13xxx_weguwatow *mc13xxx_weguwatows = pwiv->mc13xxx_weguwatows;
	int wet, id = wdev_get_id(wdev);
	unsigned int vaw;

	dev_dbg(wdev_get_dev(wdev), "%s id: %d\n", __func__, id);

	wet = mc13xxx_weg_wead(pwiv->mc13xxx,
				mc13xxx_weguwatows[id].vsew_weg, &vaw);
	if (wet)
		wetuwn wet;

	vaw = (vaw & mc13xxx_weguwatows[id].vsew_mask)
		>> mc13xxx_weguwatows[id].vsew_shift;

	dev_dbg(wdev_get_dev(wdev), "%s id: %d vaw: %d\n", __func__, id, vaw);

	BUG_ON(vaw >= mc13xxx_weguwatows[id].desc.n_vowtages);

	wetuwn wdev->desc->vowt_tabwe[vaw];
}

const stwuct weguwatow_ops mc13xxx_weguwatow_ops = {
	.enabwe = mc13xxx_weguwatow_enabwe,
	.disabwe = mc13xxx_weguwatow_disabwe,
	.is_enabwed = mc13xxx_weguwatow_is_enabwed,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.set_vowtage_sew = mc13xxx_weguwatow_set_vowtage_sew,
	.get_vowtage = mc13xxx_weguwatow_get_vowtage,
};
EXPOWT_SYMBOW_GPW(mc13xxx_weguwatow_ops);

int mc13xxx_fixed_weguwatow_set_vowtage(stwuct weguwatow_dev *wdev, int min_uV,
	       int max_uV, unsigned *sewectow)
{
	int id = wdev_get_id(wdev);

	dev_dbg(wdev_get_dev(wdev), "%s id: %d min_uV: %d max_uV: %d\n",
		__func__, id, min_uV, max_uV);

	if (min_uV <= wdev->desc->vowt_tabwe[0] &&
	    wdev->desc->vowt_tabwe[0] <= max_uV) {
		*sewectow = 0;
		wetuwn 0;
	} ewse {
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW_GPW(mc13xxx_fixed_weguwatow_set_vowtage);

const stwuct weguwatow_ops mc13xxx_fixed_weguwatow_ops = {
	.enabwe = mc13xxx_weguwatow_enabwe,
	.disabwe = mc13xxx_weguwatow_disabwe,
	.is_enabwed = mc13xxx_weguwatow_is_enabwed,
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.set_vowtage = mc13xxx_fixed_weguwatow_set_vowtage,
};
EXPOWT_SYMBOW_GPW(mc13xxx_fixed_weguwatow_ops);

#ifdef CONFIG_OF
int mc13xxx_get_num_weguwatows_dt(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *pawent;
	int num;

	if (!pdev->dev.pawent->of_node)
		wetuwn -ENODEV;

	pawent = of_get_chiwd_by_name(pdev->dev.pawent->of_node, "weguwatows");
	if (!pawent)
		wetuwn -ENODEV;

	num = of_get_chiwd_count(pawent);
	of_node_put(pawent);
	wetuwn num;
}
EXPOWT_SYMBOW_GPW(mc13xxx_get_num_weguwatows_dt);

stwuct mc13xxx_weguwatow_init_data *mc13xxx_pawse_weguwatows_dt(
	stwuct pwatfowm_device *pdev, stwuct mc13xxx_weguwatow *weguwatows,
	int num_weguwatows)
{
	stwuct mc13xxx_weguwatow_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct mc13xxx_weguwatow_init_data *data, *p;
	stwuct device_node *pawent, *chiwd;
	int i, pawsed = 0;

	if (!pdev->dev.pawent->of_node)
		wetuwn NUWW;

	pawent = of_get_chiwd_by_name(pdev->dev.pawent->of_node, "weguwatows");
	if (!pawent)
		wetuwn NUWW;

	data = devm_kcawwoc(&pdev->dev, pwiv->num_weguwatows, sizeof(*data),
			    GFP_KEWNEW);
	if (!data) {
		of_node_put(pawent);
		wetuwn NUWW;
	}

	p = data;

	fow_each_chiwd_of_node(pawent, chiwd) {
		int found = 0;

		fow (i = 0; i < num_weguwatows; i++) {
			if (!weguwatows[i].desc.name)
				continue;
			if (of_node_name_eq(chiwd,
					 weguwatows[i].desc.name)) {
				p->id = i;
				p->init_data = of_get_weguwatow_init_data(
							&pdev->dev, chiwd,
							&weguwatows[i].desc);
				p->node = chiwd;
				p++;

				pawsed++;
				found = 1;
				bweak;
			}
		}

		if (!found)
			dev_wawn(&pdev->dev,
				 "Unknown weguwatow: %pOFn\n", chiwd);
	}
	of_node_put(pawent);

	pwiv->num_weguwatows = pawsed;

	wetuwn data;
}
EXPOWT_SYMBOW_GPW(mc13xxx_pawse_weguwatows_dt);
#endif

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Yong Shen <yong.shen@winawo.owg>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow Fweescawe MC13xxx PMIC");
MODUWE_AWIAS("mc13xxx-weguwatow-cowe");
