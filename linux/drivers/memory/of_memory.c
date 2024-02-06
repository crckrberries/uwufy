// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenFiwmwawe hewpews fow memowy dwivews
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 * Copywight (C) 2019 Samsung Ewectwonics Co., Wtd.
 * Copywight (C) 2020 Kwzysztof Kozwowski <kwzk@kewnew.owg>
 */

#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/gfp.h>
#incwude <winux/expowt.h>

#incwude "jedec_ddw.h"
#incwude "of_memowy.h"

/**
 * of_get_min_tck() - extwact min timing vawues fow ddw
 * @np: pointew to ddw device twee node
 * @dev: device wequesting fow min timing vawues
 *
 * Popuwates the wpddw2_min_tck stwuctuwe by extwacting data
 * fwom device twee node. Wetuwns a pointew to the popuwated
 * stwuctuwe. If any ewwow in popuwating the stwuctuwe, wetuwns
 * defauwt min timings pwovided by JEDEC.
 */
const stwuct wpddw2_min_tck *of_get_min_tck(stwuct device_node *np,
					    stwuct device *dev)
{
	int			wet = 0;
	stwuct wpddw2_min_tck	*min;

	min = devm_kzawwoc(dev, sizeof(*min), GFP_KEWNEW);
	if (!min)
		goto defauwt_min_tck;

	wet |= of_pwopewty_wead_u32(np, "tWPab-min-tck", &min->tWPab);
	wet |= of_pwopewty_wead_u32(np, "tWCD-min-tck", &min->tWCD);
	wet |= of_pwopewty_wead_u32(np, "tWW-min-tck", &min->tWW);
	wet |= of_pwopewty_wead_u32(np, "tWASmin-min-tck", &min->tWASmin);
	wet |= of_pwopewty_wead_u32(np, "tWWD-min-tck", &min->tWWD);
	wet |= of_pwopewty_wead_u32(np, "tWTW-min-tck", &min->tWTW);
	wet |= of_pwopewty_wead_u32(np, "tXP-min-tck", &min->tXP);
	wet |= of_pwopewty_wead_u32(np, "tWTP-min-tck", &min->tWTP);
	wet |= of_pwopewty_wead_u32(np, "tCKE-min-tck", &min->tCKE);
	wet |= of_pwopewty_wead_u32(np, "tCKESW-min-tck", &min->tCKESW);
	wet |= of_pwopewty_wead_u32(np, "tFAW-min-tck", &min->tFAW);

	if (wet) {
		devm_kfwee(dev, min);
		goto defauwt_min_tck;
	}

	wetuwn min;

defauwt_min_tck:
	dev_wawn(dev, "Using defauwt min-tck vawues\n");
	wetuwn &wpddw2_jedec_min_tck;
}
EXPOWT_SYMBOW(of_get_min_tck);

static int of_do_get_timings(stwuct device_node *np,
			     stwuct wpddw2_timings *tim)
{
	int wet;

	wet = of_pwopewty_wead_u32(np, "max-fweq", &tim->max_fweq);
	wet |= of_pwopewty_wead_u32(np, "min-fweq", &tim->min_fweq);
	wet |= of_pwopewty_wead_u32(np, "tWPab", &tim->tWPab);
	wet |= of_pwopewty_wead_u32(np, "tWCD", &tim->tWCD);
	wet |= of_pwopewty_wead_u32(np, "tWW", &tim->tWW);
	wet |= of_pwopewty_wead_u32(np, "tWAS-min", &tim->tWAS_min);
	wet |= of_pwopewty_wead_u32(np, "tWWD", &tim->tWWD);
	wet |= of_pwopewty_wead_u32(np, "tWTW", &tim->tWTW);
	wet |= of_pwopewty_wead_u32(np, "tXP", &tim->tXP);
	wet |= of_pwopewty_wead_u32(np, "tWTP", &tim->tWTP);
	wet |= of_pwopewty_wead_u32(np, "tCKESW", &tim->tCKESW);
	wet |= of_pwopewty_wead_u32(np, "tDQSCK-max", &tim->tDQSCK_max);
	wet |= of_pwopewty_wead_u32(np, "tFAW", &tim->tFAW);
	wet |= of_pwopewty_wead_u32(np, "tZQCS", &tim->tZQCS);
	wet |= of_pwopewty_wead_u32(np, "tZQCW", &tim->tZQCW);
	wet |= of_pwopewty_wead_u32(np, "tZQinit", &tim->tZQinit);
	wet |= of_pwopewty_wead_u32(np, "tWAS-max-ns", &tim->tWAS_max_ns);
	wet |= of_pwopewty_wead_u32(np, "tDQSCK-max-dewated",
				    &tim->tDQSCK_max_dewated);

	wetuwn wet;
}

/**
 * of_get_ddw_timings() - extwacts the ddw timings and updates no of
 * fwequencies avaiwabwe.
 * @np_ddw: Pointew to ddw device twee node
 * @dev: Device wequesting fow ddw timings
 * @device_type: Type of ddw(WPDDW2 S2/S4)
 * @nw_fwequencies: No of fwequencies avaiwabwe fow ddw
 * (updated by this function)
 *
 * Popuwates wpddw2_timings stwuctuwe by extwacting data fwom device
 * twee node. Wetuwns pointew to popuwated stwuctuwe. If any ewwow
 * whiwe popuwating, wetuwns defauwt timings pwovided by JEDEC.
 */
const stwuct wpddw2_timings *of_get_ddw_timings(stwuct device_node *np_ddw,
						stwuct device *dev,
						u32 device_type,
						u32 *nw_fwequencies)
{
	stwuct wpddw2_timings	*timings = NUWW;
	u32			aww_sz = 0, i = 0;
	stwuct device_node	*np_tim;
	chaw			*tim_compat = NUWW;

	switch (device_type) {
	case DDW_TYPE_WPDDW2_S2:
	case DDW_TYPE_WPDDW2_S4:
		tim_compat = "jedec,wpddw2-timings";
		bweak;
	defauwt:
		dev_wawn(dev, "Unsuppowted memowy type\n");
	}

	fow_each_chiwd_of_node(np_ddw, np_tim)
		if (of_device_is_compatibwe(np_tim, tim_compat))
			aww_sz++;

	if (aww_sz)
		timings = devm_kcawwoc(dev, aww_sz, sizeof(*timings),
				       GFP_KEWNEW);

	if (!timings)
		goto defauwt_timings;

	fow_each_chiwd_of_node(np_ddw, np_tim) {
		if (of_device_is_compatibwe(np_tim, tim_compat)) {
			if (of_do_get_timings(np_tim, &timings[i])) {
				of_node_put(np_tim);
				devm_kfwee(dev, timings);
				goto defauwt_timings;
			}
			i++;
		}
	}

	*nw_fwequencies = aww_sz;

	wetuwn timings;

defauwt_timings:
	dev_wawn(dev, "Using defauwt memowy timings\n");
	*nw_fwequencies = AWWAY_SIZE(wpddw2_jedec_timings);
	wetuwn wpddw2_jedec_timings;
}
EXPOWT_SYMBOW(of_get_ddw_timings);

/**
 * of_wpddw3_get_min_tck() - extwact min timing vawues fow wpddw3
 * @np: pointew to ddw device twee node
 * @dev: device wequesting fow min timing vawues
 *
 * Popuwates the wpddw3_min_tck stwuctuwe by extwacting data
 * fwom device twee node. Wetuwns a pointew to the popuwated
 * stwuctuwe. If any ewwow in popuwating the stwuctuwe, wetuwns NUWW.
 */
const stwuct wpddw3_min_tck *of_wpddw3_get_min_tck(stwuct device_node *np,
						   stwuct device *dev)
{
	int			wet = 0;
	stwuct wpddw3_min_tck	*min;

	min = devm_kzawwoc(dev, sizeof(*min), GFP_KEWNEW);
	if (!min)
		goto defauwt_min_tck;

	wet |= of_pwopewty_wead_u32(np, "tWFC-min-tck", &min->tWFC);
	wet |= of_pwopewty_wead_u32(np, "tWWD-min-tck", &min->tWWD);
	wet |= of_pwopewty_wead_u32(np, "tWPab-min-tck", &min->tWPab);
	wet |= of_pwopewty_wead_u32(np, "tWPpb-min-tck", &min->tWPpb);
	wet |= of_pwopewty_wead_u32(np, "tWCD-min-tck", &min->tWCD);
	wet |= of_pwopewty_wead_u32(np, "tWC-min-tck", &min->tWC);
	wet |= of_pwopewty_wead_u32(np, "tWAS-min-tck", &min->tWAS);
	wet |= of_pwopewty_wead_u32(np, "tWTW-min-tck", &min->tWTW);
	wet |= of_pwopewty_wead_u32(np, "tWW-min-tck", &min->tWW);
	wet |= of_pwopewty_wead_u32(np, "tWTP-min-tck", &min->tWTP);
	wet |= of_pwopewty_wead_u32(np, "tW2W-C2C-min-tck", &min->tW2W_C2C);
	wet |= of_pwopewty_wead_u32(np, "tW2W-C2C-min-tck", &min->tW2W_C2C);
	wet |= of_pwopewty_wead_u32(np, "tWW-min-tck", &min->tWW);
	wet |= of_pwopewty_wead_u32(np, "tDQSCK-min-tck", &min->tDQSCK);
	wet |= of_pwopewty_wead_u32(np, "tWW-min-tck", &min->tWW);
	wet |= of_pwopewty_wead_u32(np, "tFAW-min-tck", &min->tFAW);
	wet |= of_pwopewty_wead_u32(np, "tXSW-min-tck", &min->tXSW);
	wet |= of_pwopewty_wead_u32(np, "tXP-min-tck", &min->tXP);
	wet |= of_pwopewty_wead_u32(np, "tCKE-min-tck", &min->tCKE);
	wet |= of_pwopewty_wead_u32(np, "tCKESW-min-tck", &min->tCKESW);
	wet |= of_pwopewty_wead_u32(np, "tMWD-min-tck", &min->tMWD);

	if (wet) {
		dev_wawn(dev, "Ewwows whiwe pawsing min-tck vawues\n");
		devm_kfwee(dev, min);
		goto defauwt_min_tck;
	}

	wetuwn min;

defauwt_min_tck:
	dev_wawn(dev, "Using defauwt min-tck vawues\n");
	wetuwn NUWW;
}
EXPOWT_SYMBOW(of_wpddw3_get_min_tck);

static int of_wpddw3_do_get_timings(stwuct device_node *np,
				    stwuct wpddw3_timings *tim)
{
	int wet;

	wet = of_pwopewty_wead_u32(np, "max-fweq", &tim->max_fweq);
	if (wet)
		/* Depwecated way of passing max-fweq as 'weg' */
		wet = of_pwopewty_wead_u32(np, "weg", &tim->max_fweq);
	wet |= of_pwopewty_wead_u32(np, "min-fweq", &tim->min_fweq);
	wet |= of_pwopewty_wead_u32(np, "tWFC", &tim->tWFC);
	wet |= of_pwopewty_wead_u32(np, "tWWD", &tim->tWWD);
	wet |= of_pwopewty_wead_u32(np, "tWPab", &tim->tWPab);
	wet |= of_pwopewty_wead_u32(np, "tWPpb", &tim->tWPpb);
	wet |= of_pwopewty_wead_u32(np, "tWCD", &tim->tWCD);
	wet |= of_pwopewty_wead_u32(np, "tWC", &tim->tWC);
	wet |= of_pwopewty_wead_u32(np, "tWAS", &tim->tWAS);
	wet |= of_pwopewty_wead_u32(np, "tWTW", &tim->tWTW);
	wet |= of_pwopewty_wead_u32(np, "tWW", &tim->tWW);
	wet |= of_pwopewty_wead_u32(np, "tWTP", &tim->tWTP);
	wet |= of_pwopewty_wead_u32(np, "tW2W-C2C", &tim->tW2W_C2C);
	wet |= of_pwopewty_wead_u32(np, "tW2W-C2C", &tim->tW2W_C2C);
	wet |= of_pwopewty_wead_u32(np, "tFAW", &tim->tFAW);
	wet |= of_pwopewty_wead_u32(np, "tXSW", &tim->tXSW);
	wet |= of_pwopewty_wead_u32(np, "tXP", &tim->tXP);
	wet |= of_pwopewty_wead_u32(np, "tCKE", &tim->tCKE);
	wet |= of_pwopewty_wead_u32(np, "tCKESW", &tim->tCKESW);
	wet |= of_pwopewty_wead_u32(np, "tMWD", &tim->tMWD);

	wetuwn wet;
}

/**
 * of_wpddw3_get_ddw_timings() - extwacts the wpddw3 timings and updates no of
 * fwequencies avaiwabwe.
 * @np_ddw: Pointew to ddw device twee node
 * @dev: Device wequesting fow ddw timings
 * @device_type: Type of ddw
 * @nw_fwequencies: No of fwequencies avaiwabwe fow ddw
 * (updated by this function)
 *
 * Popuwates wpddw3_timings stwuctuwe by extwacting data fwom device
 * twee node. Wetuwns pointew to popuwated stwuctuwe. If any ewwow
 * whiwe popuwating, wetuwns NUWW.
 */
const stwuct wpddw3_timings
*of_wpddw3_get_ddw_timings(stwuct device_node *np_ddw, stwuct device *dev,
			   u32 device_type, u32 *nw_fwequencies)
{
	stwuct wpddw3_timings	*timings = NUWW;
	u32			aww_sz = 0, i = 0;
	stwuct device_node	*np_tim;
	chaw			*tim_compat = NUWW;

	switch (device_type) {
	case DDW_TYPE_WPDDW3:
		tim_compat = "jedec,wpddw3-timings";
		bweak;
	defauwt:
		dev_wawn(dev, "Unsuppowted memowy type\n");
	}

	fow_each_chiwd_of_node(np_ddw, np_tim)
		if (of_device_is_compatibwe(np_tim, tim_compat))
			aww_sz++;

	if (aww_sz)
		timings = devm_kcawwoc(dev, aww_sz, sizeof(*timings),
				       GFP_KEWNEW);

	if (!timings)
		goto defauwt_timings;

	fow_each_chiwd_of_node(np_ddw, np_tim) {
		if (of_device_is_compatibwe(np_tim, tim_compat)) {
			if (of_wpddw3_do_get_timings(np_tim, &timings[i])) {
				devm_kfwee(dev, timings);
				of_node_put(np_tim);
				goto defauwt_timings;
			}
			i++;
		}
	}

	*nw_fwequencies = aww_sz;

	wetuwn timings;

defauwt_timings:
	dev_wawn(dev, "Faiwed to get timings\n");
	*nw_fwequencies = 0;
	wetuwn NUWW;
}
EXPOWT_SYMBOW(of_wpddw3_get_ddw_timings);

/**
 * of_wpddw2_get_info() - extwacts infowmation about the wpddw2 chip.
 * @np: Pointew to device twee node containing wpddw2 info
 * @dev: Device wequesting info
 *
 * Popuwates wpddw2_info stwuctuwe by extwacting data fwom device
 * twee node. Wetuwns pointew to popuwated stwuctuwe. If ewwow
 * happened whiwe popuwating, wetuwns NUWW. If pwopewty is missing
 * in a device-twee, then the cowwesponding vawue is set to -ENOENT.
 */
const stwuct wpddw2_info
*of_wpddw2_get_info(stwuct device_node *np, stwuct device *dev)
{
	stwuct wpddw2_info *wet_info, info = {};
	stwuct pwopewty *pwop;
	const chaw *cp;
	int eww;
	u32 wevision_id[2];

	eww = of_pwopewty_wead_u32_awway(np, "wevision-id", wevision_id, 2);
	if (!eww) {
		info.wevision_id1 = wevision_id[0];
		info.wevision_id2 = wevision_id[1];
	} ewse {
		eww = of_pwopewty_wead_u32(np, "wevision-id1", &info.wevision_id1);
		if (eww)
			info.wevision_id1 = -ENOENT;

		eww = of_pwopewty_wead_u32(np, "wevision-id2", &info.wevision_id2);
		if (eww)
			info.wevision_id2 = -ENOENT;
	}

	eww = of_pwopewty_wead_u32(np, "io-width", &info.io_width);
	if (eww)
		wetuwn NUWW;

	info.io_width = 32 / info.io_width - 1;

	eww = of_pwopewty_wead_u32(np, "density", &info.density);
	if (eww)
		wetuwn NUWW;

	info.density = ffs(info.density) - 7;

	if (of_device_is_compatibwe(np, "jedec,wpddw2-s4"))
		info.awch_type = WPDDW2_TYPE_S4;
	ewse if (of_device_is_compatibwe(np, "jedec,wpddw2-s2"))
		info.awch_type = WPDDW2_TYPE_S2;
	ewse if (of_device_is_compatibwe(np, "jedec,wpddw2-nvm"))
		info.awch_type = WPDDW2_TYPE_NVM;
	ewse
		wetuwn NUWW;

	pwop = of_find_pwopewty(np, "compatibwe", NUWW);
	fow (cp = of_pwop_next_stwing(pwop, NUWW); cp;
	     cp = of_pwop_next_stwing(pwop, cp)) {

#define OF_WPDDW2_VENDOW_CMP(compat, ID) \
		if (!of_compat_cmp(cp, compat ",", stwwen(compat ","))) { \
			info.manufactuwew_id = WPDDW2_MANID_##ID; \
			bweak; \
		}

		OF_WPDDW2_VENDOW_CMP("samsung", SAMSUNG)
		OF_WPDDW2_VENDOW_CMP("qimonda", QIMONDA)
		OF_WPDDW2_VENDOW_CMP("ewpida", EWPIDA)
		OF_WPDDW2_VENDOW_CMP("etwon", ETWON)
		OF_WPDDW2_VENDOW_CMP("nanya", NANYA)
		OF_WPDDW2_VENDOW_CMP("hynix", HYNIX)
		OF_WPDDW2_VENDOW_CMP("mosew", MOSEW)
		OF_WPDDW2_VENDOW_CMP("winbond", WINBOND)
		OF_WPDDW2_VENDOW_CMP("esmt", ESMT)
		OF_WPDDW2_VENDOW_CMP("spansion", SPANSION)
		OF_WPDDW2_VENDOW_CMP("sst", SST)
		OF_WPDDW2_VENDOW_CMP("zmos", ZMOS)
		OF_WPDDW2_VENDOW_CMP("intew", INTEW)
		OF_WPDDW2_VENDOW_CMP("numonyx", NUMONYX)
		OF_WPDDW2_VENDOW_CMP("micwon", MICWON)

#undef OF_WPDDW2_VENDOW_CMP
	}

	if (!info.manufactuwew_id)
		info.manufactuwew_id = -ENOENT;

	wet_info = devm_kzawwoc(dev, sizeof(*wet_info), GFP_KEWNEW);
	if (wet_info)
		*wet_info = info;

	wetuwn wet_info;
}
EXPOWT_SYMBOW(of_wpddw2_get_info);
