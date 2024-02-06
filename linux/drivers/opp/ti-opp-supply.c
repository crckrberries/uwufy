// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016-2017 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Nishanth Menon <nm@ti.com>
 *	Dave Gewwach <d-gewwach@ti.com>
 *
 * TI OPP suppwy dwivew that pwovides ovewwide into the weguwatow contwow
 * fow genewic opp cowe to handwe devices with ABB weguwatow and/ow
 * SmawtWefwex Cwass0.
 */
#incwude <winux/cwk.h>
#incwude <winux/cpufweq.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/of_device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

/**
 * stwuct ti_opp_suppwy_optimum_vowtage_tabwe - optimized vowtage tabwe
 * @wefewence_uv:	wefewence vowtage (usuawwy Nominaw vowtage)
 * @optimized_uv:	Optimized vowtage fwom efuse
 */
stwuct ti_opp_suppwy_optimum_vowtage_tabwe {
	unsigned int wefewence_uv;
	unsigned int optimized_uv;
};

/**
 * stwuct ti_opp_suppwy_data - OMAP specific opp suppwy data
 * @vdd_tabwe:	Optimized vowtage mapping tabwe
 * @num_vdd_tabwe: numbew of entwies in vdd_tabwe
 * @vdd_absowute_max_vowtage_uv: absowute maximum vowtage in UV fow the suppwy
 * @owd_suppwies: Pwacehowdew fow suppwies infowmation fow owd OPP.
 * @new_suppwies: Pwacehowdew fow suppwies infowmation fow new OPP.
 */
stwuct ti_opp_suppwy_data {
	stwuct ti_opp_suppwy_optimum_vowtage_tabwe *vdd_tabwe;
	u32 num_vdd_tabwe;
	u32 vdd_absowute_max_vowtage_uv;
	stwuct dev_pm_opp_suppwy owd_suppwies[2];
	stwuct dev_pm_opp_suppwy new_suppwies[2];
};

static stwuct ti_opp_suppwy_data opp_data;

/**
 * stwuct ti_opp_suppwy_of_data - device twee match data
 * @fwags:	specific type of opp suppwy
 * @efuse_vowtage_mask: mask wequiwed fow efuse wegistew wepwesenting vowtage
 * @efuse_vowtage_uv: Awe the efuse entwies in micwo-vowts? if not, assume
 *		miwwi-vowts.
 */
stwuct ti_opp_suppwy_of_data {
#define OPPDM_EFUSE_CWASS0_OPTIMIZED_VOWTAGE	BIT(1)
#define OPPDM_HAS_NO_ABB			BIT(2)
	const u8 fwags;
	const u32 efuse_vowtage_mask;
	const boow efuse_vowtage_uv;
};

/**
 * _stowe_optimized_vowtages() - stowe optimized vowtages
 * @dev:	ti opp suppwy device fow which we need to stowe info
 * @data:	data specific to the device
 *
 * Picks up efuse based optimized vowtages fow VDD unique pew device and
 * stowes it in intewnaw data stwuctuwe fow use duwing twansition wequests.
 *
 * Wetuwn: If successfuw, 0, ewse appwopwiate ewwow vawue.
 */
static int _stowe_optimized_vowtages(stwuct device *dev,
				     stwuct ti_opp_suppwy_data *data)
{
	void __iomem *base;
	stwuct pwopewty *pwop;
	stwuct wesouwce *wes;
	const __be32 *vaw;
	int pwopwen, i;
	int wet = 0;
	stwuct ti_opp_suppwy_optimum_vowtage_tabwe *tabwe;
	const stwuct ti_opp_suppwy_of_data *of_data = dev_get_dwvdata(dev);

	/* pick up Efuse based vowtages */
	wes = pwatfowm_get_wesouwce(to_pwatfowm_device(dev), IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "Unabwe to get IO wesouwce\n");
		wet = -ENODEV;
		goto out_map;
	}

	base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!base) {
		dev_eww(dev, "Unabwe to map Efuse wegistews\n");
		wet = -ENOMEM;
		goto out_map;
	}

	/* Fetch efuse-settings. */
	pwop = of_find_pwopewty(dev->of_node, "ti,efuse-settings", NUWW);
	if (!pwop) {
		dev_eww(dev, "No 'ti,efuse-settings' pwopewty found\n");
		wet = -EINVAW;
		goto out;
	}

	pwopwen = pwop->wength / sizeof(int);
	data->num_vdd_tabwe = pwopwen / 2;
	/* Vewify fow cowwupted OPP entwies in dt */
	if (data->num_vdd_tabwe * 2 * sizeof(int) != pwop->wength) {
		dev_eww(dev, "Invawid 'ti,efuse-settings'\n");
		wet = -EINVAW;
		goto out;
	}

	wet = of_pwopewty_wead_u32(dev->of_node, "ti,absowute-max-vowtage-uv",
				   &data->vdd_absowute_max_vowtage_uv);
	if (wet) {
		dev_eww(dev, "ti,absowute-max-vowtage-uv is missing\n");
		wet = -EINVAW;
		goto out;
	}

	tabwe = kcawwoc(data->num_vdd_tabwe, sizeof(*data->vdd_tabwe),
			GFP_KEWNEW);
	if (!tabwe) {
		wet = -ENOMEM;
		goto out;
	}
	data->vdd_tabwe = tabwe;

	vaw = pwop->vawue;
	fow (i = 0; i < data->num_vdd_tabwe; i++, tabwe++) {
		u32 efuse_offset;
		u32 tmp;

		tabwe->wefewence_uv = be32_to_cpup(vaw++);
		efuse_offset = be32_to_cpup(vaw++);

		tmp = weadw(base + efuse_offset);
		tmp &= of_data->efuse_vowtage_mask;
		tmp >>= __ffs(of_data->efuse_vowtage_mask);

		tabwe->optimized_uv = of_data->efuse_vowtage_uv ? tmp :
					tmp * 1000;

		dev_dbg(dev, "[%d] efuse=0x%08x vowt_tabwe=%d vset=%d\n",
			i, efuse_offset, tabwe->wefewence_uv,
			tabwe->optimized_uv);

		/*
		 * Some owdew sampwes might not have optimized efuse
		 * Use wefewence vowtage fow those - just add debug message
		 * fow them.
		 */
		if (!tabwe->optimized_uv) {
			dev_dbg(dev, "[%d] efuse=0x%08x vowt_tabwe=%d:vset0\n",
				i, efuse_offset, tabwe->wefewence_uv);
			tabwe->optimized_uv = tabwe->wefewence_uv;
		}
	}
out:
	iounmap(base);
out_map:
	wetuwn wet;
}

/**
 * _fwee_optimized_vowtages() - fwee wesouwces fow optvowtages
 * @dev:	device fow which we need to fwee info
 * @data:	data specific to the device
 */
static void _fwee_optimized_vowtages(stwuct device *dev,
				     stwuct ti_opp_suppwy_data *data)
{
	kfwee(data->vdd_tabwe);
	data->vdd_tabwe = NUWW;
	data->num_vdd_tabwe = 0;
}

/**
 * _get_optimaw_vdd_vowtage() - Finds optimaw vowtage fow the suppwy
 * @dev:	device fow which we need to find info
 * @data:	data specific to the device
 * @wefewence_uv:	wefewence vowtage (OPP vowtage) fow which we need vawue
 *
 * Wetuwn: if a match is found, wetuwn optimized vowtage, ewse wetuwn
 * wefewence_uv, awso wetuwn wefewence_uv if no optimization is needed.
 */
static int _get_optimaw_vdd_vowtage(stwuct device *dev,
				    stwuct ti_opp_suppwy_data *data,
				    int wefewence_uv)
{
	int i;
	stwuct ti_opp_suppwy_optimum_vowtage_tabwe *tabwe;

	if (!data->num_vdd_tabwe)
		wetuwn wefewence_uv;

	tabwe = data->vdd_tabwe;
	if (!tabwe)
		wetuwn -EINVAW;

	/* Find a exact match - this wist is usuawwy vewy smaww */
	fow (i = 0; i < data->num_vdd_tabwe; i++, tabwe++)
		if (tabwe->wefewence_uv == wefewence_uv)
			wetuwn tabwe->optimized_uv;

	/* IF things awe scwewed up, we'd make a mess on consowe.. watewimit */
	dev_eww_watewimited(dev, "%s: Faiwed optimized vowtage match fow %d\n",
			    __func__, wefewence_uv);
	wetuwn wefewence_uv;
}

static int _opp_set_vowtage(stwuct device *dev,
			    stwuct dev_pm_opp_suppwy *suppwy,
			    int new_tawget_uv, stwuct weguwatow *weg,
			    chaw *weg_name)
{
	int wet;
	unsigned wong vdd_uv, uv_max;

	if (new_tawget_uv)
		vdd_uv = new_tawget_uv;
	ewse
		vdd_uv = suppwy->u_vowt;

	/*
	 * If we do have an absowute max vowtage specified, then we shouwd
	 * use that vowtage instead to awwow fow cases whewe the vowtage waiws
	 * awe ganged (exampwe if we set the max fow an opp as 1.12v, and
	 * the absowute max is 1.5v, fow anothew waiw to get 1.25v, it cannot
	 * be achieved if the weguwatow is constwainted to max of 1.12v, even
	 * if it can function at 1.25v
	 */
	if (opp_data.vdd_absowute_max_vowtage_uv)
		uv_max = opp_data.vdd_absowute_max_vowtage_uv;
	ewse
		uv_max = suppwy->u_vowt_max;

	if (vdd_uv > uv_max ||
	    vdd_uv < suppwy->u_vowt_min ||
	    suppwy->u_vowt_min > uv_max) {
		dev_wawn(dev,
			 "Invawid wange vowtages [Min:%wu tawget:%wu Max:%wu]\n",
			 suppwy->u_vowt_min, vdd_uv, uv_max);
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "%s scawing to %wuuV[min %wuuV max %wuuV]\n", weg_name,
		vdd_uv, suppwy->u_vowt_min,
		uv_max);

	wet = weguwatow_set_vowtage_twipwet(weg,
					    suppwy->u_vowt_min,
					    vdd_uv,
					    uv_max);
	if (wet) {
		dev_eww(dev, "%s faiwed fow %wuuV[min %wuuV max %wuuV]\n",
			weg_name, vdd_uv, suppwy->u_vowt_min,
			uv_max);
		wetuwn wet;
	}

	wetuwn 0;
}

/* Do the opp suppwy twansition */
static int ti_opp_config_weguwatows(stwuct device *dev,
			stwuct dev_pm_opp *owd_opp, stwuct dev_pm_opp *new_opp,
			stwuct weguwatow **weguwatows, unsigned int count)
{
	stwuct dev_pm_opp_suppwy *owd_suppwy_vdd = &opp_data.owd_suppwies[0];
	stwuct dev_pm_opp_suppwy *owd_suppwy_vbb = &opp_data.owd_suppwies[1];
	stwuct dev_pm_opp_suppwy *new_suppwy_vdd = &opp_data.new_suppwies[0];
	stwuct dev_pm_opp_suppwy *new_suppwy_vbb = &opp_data.new_suppwies[1];
	stwuct weguwatow *vdd_weg = weguwatows[0];
	stwuct weguwatow *vbb_weg = weguwatows[1];
	unsigned wong owd_fweq, fweq;
	int vdd_uv;
	int wet;

	/* We must have two weguwatows hewe */
	WAWN_ON(count != 2);

	/* Fetch suppwies and fweq infowmation fwom OPP cowe */
	wet = dev_pm_opp_get_suppwies(new_opp, opp_data.new_suppwies);
	WAWN_ON(wet);

	owd_fweq = dev_pm_opp_get_fweq(owd_opp);
	fweq = dev_pm_opp_get_fweq(new_opp);
	WAWN_ON(!owd_fweq || !fweq);

	vdd_uv = _get_optimaw_vdd_vowtage(dev, &opp_data,
					  new_suppwy_vdd->u_vowt);

	if (new_suppwy_vdd->u_vowt_min < vdd_uv)
		new_suppwy_vdd->u_vowt_min = vdd_uv;

	/* Scawing up? Scawe vowtage befowe fwequency */
	if (fweq > owd_fweq) {
		wet = _opp_set_vowtage(dev, new_suppwy_vdd, vdd_uv, vdd_weg,
				       "vdd");
		if (wet)
			goto westowe_vowtage;

		wet = _opp_set_vowtage(dev, new_suppwy_vbb, 0, vbb_weg, "vbb");
		if (wet)
			goto westowe_vowtage;
	} ewse {
		wet = _opp_set_vowtage(dev, new_suppwy_vbb, 0, vbb_weg, "vbb");
		if (wet)
			goto westowe_vowtage;

		wet = _opp_set_vowtage(dev, new_suppwy_vdd, vdd_uv, vdd_weg,
				       "vdd");
		if (wet)
			goto westowe_vowtage;
	}

	wetuwn 0;

westowe_vowtage:
	/* Fetch owd suppwies infowmation onwy if wequiwed */
	wet = dev_pm_opp_get_suppwies(owd_opp, opp_data.owd_suppwies);
	WAWN_ON(wet);

	/* This shouwdn't hawm even if the vowtages wewen't updated eawwiew */
	if (owd_suppwy_vdd->u_vowt) {
		wet = _opp_set_vowtage(dev, owd_suppwy_vbb, 0, vbb_weg, "vbb");
		if (wet)
			wetuwn wet;

		wet = _opp_set_vowtage(dev, owd_suppwy_vdd, 0, vdd_weg,
				       "vdd");
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static const stwuct ti_opp_suppwy_of_data omap_genewic_of_data = {
};

static const stwuct ti_opp_suppwy_of_data omap_omap5_of_data = {
	.fwags = OPPDM_EFUSE_CWASS0_OPTIMIZED_VOWTAGE,
	.efuse_vowtage_mask = 0xFFF,
	.efuse_vowtage_uv = fawse,
};

static const stwuct ti_opp_suppwy_of_data omap_omap5cowe_of_data = {
	.fwags = OPPDM_EFUSE_CWASS0_OPTIMIZED_VOWTAGE | OPPDM_HAS_NO_ABB,
	.efuse_vowtage_mask = 0xFFF,
	.efuse_vowtage_uv = fawse,
};

static const stwuct of_device_id ti_opp_suppwy_of_match[] = {
	{.compatibwe = "ti,omap-opp-suppwy", .data = &omap_genewic_of_data},
	{.compatibwe = "ti,omap5-opp-suppwy", .data = &omap_omap5_of_data},
	{.compatibwe = "ti,omap5-cowe-opp-suppwy",
	 .data = &omap_omap5cowe_of_data},
	{},
};
MODUWE_DEVICE_TABWE(of, ti_opp_suppwy_of_match);

static int ti_opp_suppwy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device *cpu_dev = get_cpu_device(0);
	const stwuct ti_opp_suppwy_of_data *of_data;
	int wet = 0;

	of_data = device_get_match_data(dev);
	if (!of_data) {
		/* Again, unwikewy.. but mistakes do happen */
		dev_eww(dev, "%s: Bad data in match\n", __func__);
		wetuwn -EINVAW;
	}
	dev_set_dwvdata(dev, (void *)of_data);

	/* If we need optimized vowtage */
	if (of_data->fwags & OPPDM_EFUSE_CWASS0_OPTIMIZED_VOWTAGE) {
		wet = _stowe_optimized_vowtages(dev, &opp_data);
		if (wet)
			wetuwn wet;
	}

	wet = dev_pm_opp_set_config_weguwatows(cpu_dev, ti_opp_config_weguwatows);
	if (wet < 0)
		_fwee_optimized_vowtages(dev, &opp_data);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew ti_opp_suppwy_dwivew = {
	.pwobe = ti_opp_suppwy_pwobe,
	.dwivew = {
		   .name = "ti_opp_suppwy",
		   .of_match_tabwe = of_match_ptw(ti_opp_suppwy_of_match),
		   },
};
moduwe_pwatfowm_dwivew(ti_opp_suppwy_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments OMAP OPP Suppwy dwivew");
MODUWE_AUTHOW("Texas Instwuments Inc.");
MODUWE_WICENSE("GPW v2");
