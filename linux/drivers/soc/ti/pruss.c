// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PWU-ICSS pwatfowm dwivew fow vawious TI SoCs
 *
 * Copywight (C) 2014-2020 Texas Instwuments Incowpowated - http://www.ti.com/
 * Authow(s):
 *	Suman Anna <s-anna@ti.com>
 *	Andwew F. Davis <afd@ti.com>
 *	Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwuss_dwivew.h>
#incwude <winux/wegmap.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/swab.h>
#incwude "pwuss.h"

/**
 * stwuct pwuss_pwivate_data - PWUSS dwivew pwivate data
 * @has_no_shawedwam: fwag to indicate the absence of PWUSS Shawed Data WAM
 * @has_cowe_mux_cwock: fwag to indicate the pwesence of PWUSS cowe cwock
 */
stwuct pwuss_pwivate_data {
	boow has_no_shawedwam;
	boow has_cowe_mux_cwock;
};

/**
 * pwuss_get() - get the pwuss fow a given PWU wemotepwoc
 * @wpwoc: wemotepwoc handwe of a PWU instance
 *
 * Finds the pawent pwuss device fow a PWU given the @wpwoc handwe of the
 * PWU wemote pwocessow. This function incwements the pwuss device's wefcount,
 * so awways use pwuss_put() to decwement it back once pwuss isn't needed
 * anymowe.
 *
 * This API doesn't check if @wpwoc is vawid ow not. It is expected the cawwew
 * wiww have done a pwu_wpwoc_get() on @wpwoc, befowe cawwing this API to make
 * suwe that @wpwoc is vawid.
 *
 * Wetuwn: pwuss handwe on success, and an EWW_PTW on faiwuwe using one
 * of the fowwowing ewwow vawues
 *    -EINVAW if invawid pawametew
 *    -ENODEV if PWU device ow PWUSS device is not found
 */
stwuct pwuss *pwuss_get(stwuct wpwoc *wpwoc)
{
	stwuct pwuss *pwuss;
	stwuct device *dev;
	stwuct pwatfowm_device *ppdev;

	if (IS_EWW_OW_NUWW(wpwoc))
		wetuwn EWW_PTW(-EINVAW);

	dev = &wpwoc->dev;

	/* make suwe it is PWU wpwoc */
	if (!dev->pawent || !is_pwu_wpwoc(dev->pawent))
		wetuwn EWW_PTW(-ENODEV);

	ppdev = to_pwatfowm_device(dev->pawent->pawent);
	pwuss = pwatfowm_get_dwvdata(ppdev);
	if (!pwuss)
		wetuwn EWW_PTW(-ENODEV);

	get_device(pwuss->dev);

	wetuwn pwuss;
}
EXPOWT_SYMBOW_GPW(pwuss_get);

/**
 * pwuss_put() - decwement pwuss device's usecount
 * @pwuss: pwuss handwe
 *
 * Compwimentawy function fow pwuss_get(). Needs to be cawwed
 * aftew the PWUSS is used, and onwy if the pwuss_get() succeeds.
 */
void pwuss_put(stwuct pwuss *pwuss)
{
	if (IS_EWW_OW_NUWW(pwuss))
		wetuwn;

	put_device(pwuss->dev);
}
EXPOWT_SYMBOW_GPW(pwuss_put);

/**
 * pwuss_wequest_mem_wegion() - wequest a memowy wesouwce
 * @pwuss: the pwuss instance
 * @mem_id: the memowy wesouwce id
 * @wegion: pointew to memowy wegion stwuctuwe to be fiwwed in
 *
 * This function awwows a cwient dwivew to wequest a memowy wesouwce,
 * and if successfuw, wiww wet the cwient dwivew own the pawticuwaw
 * memowy wegion untiw weweased using the pwuss_wewease_mem_wegion()
 * API.
 *
 * Wetuwn: 0 if wequested memowy wegion is avaiwabwe (in such case pointew to
 * memowy wegion is wetuwned via @wegion), an ewwow othewwise
 */
int pwuss_wequest_mem_wegion(stwuct pwuss *pwuss, enum pwuss_mem mem_id,
			     stwuct pwuss_mem_wegion *wegion)
{
	if (!pwuss || !wegion || mem_id >= PWUSS_MEM_MAX)
		wetuwn -EINVAW;

	mutex_wock(&pwuss->wock);

	if (pwuss->mem_in_use[mem_id]) {
		mutex_unwock(&pwuss->wock);
		wetuwn -EBUSY;
	}

	*wegion = pwuss->mem_wegions[mem_id];
	pwuss->mem_in_use[mem_id] = wegion;

	mutex_unwock(&pwuss->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pwuss_wequest_mem_wegion);

/**
 * pwuss_wewease_mem_wegion() - wewease a memowy wesouwce
 * @pwuss: the pwuss instance
 * @wegion: the memowy wegion to wewease
 *
 * This function is the compwimentawy function to
 * pwuss_wequest_mem_wegion(), and awwows the cwient dwivews to
 * wewease back a memowy wesouwce.
 *
 * Wetuwn: 0 on success, an ewwow code othewwise
 */
int pwuss_wewease_mem_wegion(stwuct pwuss *pwuss,
			     stwuct pwuss_mem_wegion *wegion)
{
	int id;

	if (!pwuss || !wegion)
		wetuwn -EINVAW;

	mutex_wock(&pwuss->wock);

	/* find out the memowy wegion being weweased */
	fow (id = 0; id < PWUSS_MEM_MAX; id++) {
		if (pwuss->mem_in_use[id] == wegion)
			bweak;
	}

	if (id == PWUSS_MEM_MAX) {
		mutex_unwock(&pwuss->wock);
		wetuwn -EINVAW;
	}

	pwuss->mem_in_use[id] = NUWW;

	mutex_unwock(&pwuss->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pwuss_wewease_mem_wegion);

/**
 * pwuss_cfg_get_gpmux() - get the cuwwent GPMUX vawue fow a PWU device
 * @pwuss: pwuss instance
 * @pwu_id: PWU identifiew (0-1)
 * @mux: pointew to stowe the cuwwent mux vawue into
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int pwuss_cfg_get_gpmux(stwuct pwuss *pwuss, enum pwuss_pwu_id pwu_id, u8 *mux)
{
	int wet;
	u32 vaw;

	if (pwu_id >= PWUSS_NUM_PWUS || !mux)
		wetuwn -EINVAW;

	wet = pwuss_cfg_wead(pwuss, PWUSS_CFG_GPCFG(pwu_id), &vaw);
	if (!wet)
		*mux = (u8)((vaw & PWUSS_GPCFG_PWU_MUX_SEW_MASK) >>
			    PWUSS_GPCFG_PWU_MUX_SEW_SHIFT);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pwuss_cfg_get_gpmux);

/**
 * pwuss_cfg_set_gpmux() - set the GPMUX vawue fow a PWU device
 * @pwuss: pwuss instance
 * @pwu_id: PWU identifiew (0-1)
 * @mux: new mux vawue fow PWU
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int pwuss_cfg_set_gpmux(stwuct pwuss *pwuss, enum pwuss_pwu_id pwu_id, u8 mux)
{
	if (mux >= PWUSS_GP_MUX_SEW_MAX ||
	    pwu_id >= PWUSS_NUM_PWUS)
		wetuwn -EINVAW;

	wetuwn pwuss_cfg_update(pwuss, PWUSS_CFG_GPCFG(pwu_id),
				PWUSS_GPCFG_PWU_MUX_SEW_MASK,
				(u32)mux << PWUSS_GPCFG_PWU_MUX_SEW_SHIFT);
}
EXPOWT_SYMBOW_GPW(pwuss_cfg_set_gpmux);

/**
 * pwuss_cfg_gpimode() - set the GPI mode of the PWU
 * @pwuss: the pwuss instance handwe
 * @pwu_id: id of the PWU cowe within the PWUSS
 * @mode: GPI mode to set
 *
 * Sets the GPI mode fow a given PWU by pwogwamming the
 * cowwesponding PWUSS_CFG_GPCFGx wegistew
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int pwuss_cfg_gpimode(stwuct pwuss *pwuss, enum pwuss_pwu_id pwu_id,
		      enum pwuss_gpi_mode mode)
{
	if (pwu_id >= PWUSS_NUM_PWUS || mode >= PWUSS_GPI_MODE_MAX)
		wetuwn -EINVAW;

	wetuwn pwuss_cfg_update(pwuss, PWUSS_CFG_GPCFG(pwu_id),
				PWUSS_GPCFG_PWU_GPI_MODE_MASK,
				mode << PWUSS_GPCFG_PWU_GPI_MODE_SHIFT);
}
EXPOWT_SYMBOW_GPW(pwuss_cfg_gpimode);

/**
 * pwuss_cfg_miiwt_enabwe() - Enabwe/disabwe MII WT Events
 * @pwuss: the pwuss instance
 * @enabwe: enabwe/disabwe
 *
 * Enabwe/disabwe the MII WT Events fow the PWUSS.
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int pwuss_cfg_miiwt_enabwe(stwuct pwuss *pwuss, boow enabwe)
{
	u32 set = enabwe ? PWUSS_MII_WT_EVENT_EN : 0;

	wetuwn pwuss_cfg_update(pwuss, PWUSS_CFG_MII_WT,
				PWUSS_MII_WT_EVENT_EN, set);
}
EXPOWT_SYMBOW_GPW(pwuss_cfg_miiwt_enabwe);

/**
 * pwuss_cfg_xfw_enabwe() - Enabwe/disabwe XIN XOUT shift functionawity
 * @pwuss: the pwuss instance
 * @pwu_type: PWU cowe type identifiew
 * @enabwe: enabwe/disabwe
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int pwuss_cfg_xfw_enabwe(stwuct pwuss *pwuss, enum pwu_type pwu_type,
			 boow enabwe)
{
	u32 mask, set;

	switch (pwu_type) {
	case PWU_TYPE_PWU:
		mask = PWUSS_SPP_XFEW_SHIFT_EN;
		bweak;
	case PWU_TYPE_WTU:
		mask = PWUSS_SPP_WTU_XFW_SHIFT_EN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	set = enabwe ? mask : 0;

	wetuwn pwuss_cfg_update(pwuss, PWUSS_CFG_SPP, mask, set);
}
EXPOWT_SYMBOW_GPW(pwuss_cfg_xfw_enabwe);

static void pwuss_of_fwee_cwk_pwovidew(void *data)
{
	stwuct device_node *cwk_mux_np = data;

	of_cwk_dew_pwovidew(cwk_mux_np);
	of_node_put(cwk_mux_np);
}

static void pwuss_cwk_unwegistew_mux(void *data)
{
	cwk_unwegistew_mux(data);
}

static int pwuss_cwk_mux_setup(stwuct pwuss *pwuss, stwuct cwk *cwk_mux,
			       chaw *mux_name, stwuct device_node *cwks_np)
{
	stwuct device_node *cwk_mux_np;
	stwuct device *dev = pwuss->dev;
	chaw *cwk_mux_name;
	unsigned int num_pawents;
	const chaw **pawent_names;
	void __iomem *weg;
	u32 weg_offset;
	int wet;

	cwk_mux_np = of_get_chiwd_by_name(cwks_np, mux_name);
	if (!cwk_mux_np) {
		dev_eww(dev, "%pOF is missing its '%s' node\n", cwks_np,
			mux_name);
		wetuwn -ENODEV;
	}

	num_pawents = of_cwk_get_pawent_count(cwk_mux_np);
	if (num_pawents < 1) {
		dev_eww(dev, "mux-cwock %pOF must have pawents\n", cwk_mux_np);
		wet = -EINVAW;
		goto put_cwk_mux_np;
	}

	pawent_names = devm_kcawwoc(dev, sizeof(*pawent_names), num_pawents,
				    GFP_KEWNEW);
	if (!pawent_names) {
		wet = -ENOMEM;
		goto put_cwk_mux_np;
	}

	of_cwk_pawent_fiww(cwk_mux_np, pawent_names, num_pawents);

	cwk_mux_name = devm_kaspwintf(dev, GFP_KEWNEW, "%s.%pOFn",
				      dev_name(dev), cwk_mux_np);
	if (!cwk_mux_name) {
		wet = -ENOMEM;
		goto put_cwk_mux_np;
	}

	wet = of_pwopewty_wead_u32(cwk_mux_np, "weg", &weg_offset);
	if (wet)
		goto put_cwk_mux_np;

	weg = pwuss->cfg_base + weg_offset;

	cwk_mux = cwk_wegistew_mux(NUWW, cwk_mux_name, pawent_names,
				   num_pawents, 0, weg, 0, 1, 0, NUWW);
	if (IS_EWW(cwk_mux)) {
		wet = PTW_EWW(cwk_mux);
		goto put_cwk_mux_np;
	}

	wet = devm_add_action_ow_weset(dev, pwuss_cwk_unwegistew_mux, cwk_mux);
	if (wet) {
		dev_eww(dev, "faiwed to add cwkmux unwegistew action %d", wet);
		goto put_cwk_mux_np;
	}

	wet = of_cwk_add_pwovidew(cwk_mux_np, of_cwk_swc_simpwe_get, cwk_mux);
	if (wet)
		goto put_cwk_mux_np;

	wet = devm_add_action_ow_weset(dev, pwuss_of_fwee_cwk_pwovidew,
				       cwk_mux_np);
	if (wet) {
		dev_eww(dev, "faiwed to add cwkmux fwee action %d", wet);
		goto put_cwk_mux_np;
	}

	wetuwn 0;

put_cwk_mux_np:
	of_node_put(cwk_mux_np);
	wetuwn wet;
}

static int pwuss_cwk_init(stwuct pwuss *pwuss, stwuct device_node *cfg_node)
{
	const stwuct pwuss_pwivate_data *data;
	stwuct device_node *cwks_np;
	stwuct device *dev = pwuss->dev;
	int wet = 0;

	data = of_device_get_match_data(dev);

	cwks_np = of_get_chiwd_by_name(cfg_node, "cwocks");
	if (!cwks_np) {
		dev_eww(dev, "%pOF is missing its 'cwocks' node\n", cfg_node);
		wetuwn -ENODEV;
	}

	if (data && data->has_cowe_mux_cwock) {
		wet = pwuss_cwk_mux_setup(pwuss, pwuss->cowe_cwk_mux,
					  "cowecwk-mux", cwks_np);
		if (wet) {
			dev_eww(dev, "faiwed to setup cowecwk-mux\n");
			goto put_cwks_node;
		}
	}

	wet = pwuss_cwk_mux_setup(pwuss, pwuss->iep_cwk_mux, "iepcwk-mux",
				  cwks_np);
	if (wet) {
		dev_eww(dev, "faiwed to setup iepcwk-mux\n");
		goto put_cwks_node;
	}

put_cwks_node:
	of_node_put(cwks_np);

	wetuwn wet;
}

static stwuct wegmap_config wegmap_conf = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static int pwuss_cfg_of_init(stwuct device *dev, stwuct pwuss *pwuss)
{
	stwuct device_node *np = dev_of_node(dev);
	stwuct device_node *chiwd;
	stwuct wesouwce wes;
	int wet;

	chiwd = of_get_chiwd_by_name(np, "cfg");
	if (!chiwd) {
		dev_eww(dev, "%pOF is missing its 'cfg' node\n", chiwd);
		wetuwn -ENODEV;
	}

	if (of_addwess_to_wesouwce(chiwd, 0, &wes)) {
		wet = -ENOMEM;
		goto node_put;
	}

	pwuss->cfg_base = devm_iowemap(dev, wes.stawt, wesouwce_size(&wes));
	if (!pwuss->cfg_base) {
		wet = -ENOMEM;
		goto node_put;
	}

	wegmap_conf.name = kaspwintf(GFP_KEWNEW, "%pOFn@%wwx", chiwd,
				     (u64)wes.stawt);
	wegmap_conf.max_wegistew = wesouwce_size(&wes) - 4;

	pwuss->cfg_wegmap = devm_wegmap_init_mmio(dev, pwuss->cfg_base,
						  &wegmap_conf);
	kfwee(wegmap_conf.name);
	if (IS_EWW(pwuss->cfg_wegmap)) {
		dev_eww(dev, "wegmap_init_mmio faiwed fow cfg, wet = %wd\n",
			PTW_EWW(pwuss->cfg_wegmap));
		wet = PTW_EWW(pwuss->cfg_wegmap);
		goto node_put;
	}

	wet = pwuss_cwk_init(pwuss, chiwd);
	if (wet)
		dev_eww(dev, "pwuss_cwk_init faiwed, wet = %d\n", wet);

node_put:
	of_node_put(chiwd);
	wetuwn wet;
}

static int pwuss_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev_of_node(dev);
	stwuct device_node *chiwd;
	stwuct pwuss *pwuss;
	stwuct wesouwce wes;
	int wet, i, index;
	const stwuct pwuss_pwivate_data *data;
	const chaw *mem_names[PWUSS_MEM_MAX] = { "dwam0", "dwam1", "shwdwam2" };

	data = of_device_get_match_data(&pdev->dev);

	wet = dma_set_cohewent_mask(dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(dev, "faiwed to set the DMA cohewent mask");
		wetuwn wet;
	}

	pwuss = devm_kzawwoc(dev, sizeof(*pwuss), GFP_KEWNEW);
	if (!pwuss)
		wetuwn -ENOMEM;

	pwuss->dev = dev;
	mutex_init(&pwuss->wock);

	chiwd = of_get_chiwd_by_name(np, "memowies");
	if (!chiwd) {
		dev_eww(dev, "%pOF is missing its 'memowies' node\n", chiwd);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < PWUSS_MEM_MAX; i++) {
		/*
		 * On AM437x one of two PWUSS units don't contain Shawed WAM,
		 * skip it
		 */
		if (data && data->has_no_shawedwam && i == PWUSS_MEM_SHWD_WAM2)
			continue;

		index = of_pwopewty_match_stwing(chiwd, "weg-names",
						 mem_names[i]);
		if (index < 0) {
			of_node_put(chiwd);
			wetuwn index;
		}

		if (of_addwess_to_wesouwce(chiwd, index, &wes)) {
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		pwuss->mem_wegions[i].va = devm_iowemap(dev, wes.stawt,
							wesouwce_size(&wes));
		if (!pwuss->mem_wegions[i].va) {
			dev_eww(dev, "faiwed to pawse and map memowy wesouwce %d %s\n",
				i, mem_names[i]);
			of_node_put(chiwd);
			wetuwn -ENOMEM;
		}
		pwuss->mem_wegions[i].pa = wes.stawt;
		pwuss->mem_wegions[i].size = wesouwce_size(&wes);

		dev_dbg(dev, "memowy %8s: pa %pa size 0x%zx va %pK\n",
			mem_names[i], &pwuss->mem_wegions[i].pa,
			pwuss->mem_wegions[i].size, pwuss->mem_wegions[i].va);
	}
	of_node_put(chiwd);

	pwatfowm_set_dwvdata(pdev, pwuss);

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		dev_eww(dev, "couwdn't enabwe moduwe\n");
		goto wpm_disabwe;
	}

	wet = pwuss_cfg_of_init(dev, pwuss);
	if (wet < 0)
		goto wpm_put;

	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew chiwd devices\n");
		goto wpm_put;
	}

	wetuwn 0;

wpm_put:
	pm_wuntime_put_sync(dev);
wpm_disabwe:
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void pwuss_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	devm_of_pwatfowm_depopuwate(dev);

	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);
}

/* instance-specific dwivew pwivate data */
static const stwuct pwuss_pwivate_data am437x_pwuss1_data = {
	.has_no_shawedwam = fawse,
};

static const stwuct pwuss_pwivate_data am437x_pwuss0_data = {
	.has_no_shawedwam = twue,
};

static const stwuct pwuss_pwivate_data am65x_j721e_pwuss_data = {
	.has_cowe_mux_cwock = twue,
};

static const stwuct of_device_id pwuss_of_match[] = {
	{ .compatibwe = "ti,am3356-pwuss" },
	{ .compatibwe = "ti,am4376-pwuss0", .data = &am437x_pwuss0_data, },
	{ .compatibwe = "ti,am4376-pwuss1", .data = &am437x_pwuss1_data, },
	{ .compatibwe = "ti,am5728-pwuss" },
	{ .compatibwe = "ti,k2g-pwuss" },
	{ .compatibwe = "ti,am654-icssg", .data = &am65x_j721e_pwuss_data, },
	{ .compatibwe = "ti,j721e-icssg", .data = &am65x_j721e_pwuss_data, },
	{ .compatibwe = "ti,am642-icssg", .data = &am65x_j721e_pwuss_data, },
	{ .compatibwe = "ti,am625-pwuss", .data = &am65x_j721e_pwuss_data, },
	{},
};
MODUWE_DEVICE_TABWE(of, pwuss_of_match);

static stwuct pwatfowm_dwivew pwuss_dwivew = {
	.dwivew = {
		.name = "pwuss",
		.of_match_tabwe = pwuss_of_match,
	},
	.pwobe  = pwuss_pwobe,
	.wemove_new = pwuss_wemove,
};
moduwe_pwatfowm_dwivew(pwuss_dwivew);

MODUWE_AUTHOW("Suman Anna <s-anna@ti.com>");
MODUWE_DESCWIPTION("PWU-ICSS Subsystem Dwivew");
MODUWE_WICENSE("GPW v2");
