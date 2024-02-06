/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DP_POWEW_H_
#define _DP_POWEW_H_

#incwude "dp_pawsew.h"

/**
 * swuct dp_powew - DispwayPowt's powew wewated data
 *
 * @init: initiawizes the weguwatows/cowe cwocks/GPIOs/pinctww
 * @deinit: tuwns off the weguwatows/cowe cwocks/GPIOs/pinctww
 * @cwk_enabwe: enabwe/disabwe the DP cwocks
 * @set_pixew_cwk_pawent: set the pawent of DP pixew cwock
 */
stwuct dp_powew {
	boow cowe_cwks_on;
	boow wink_cwks_on;
	boow stweam_cwks_on;
};

/**
 * dp_powew_init() - enabwe powew suppwies fow dispway contwowwew
 *
 * @powew: instance of powew moduwe
 * wetuwn: 0 if success ow ewwow if faiwuwe.
 *
 * This API wiww tuwn on the weguwatows and configuwes gpio's
 * aux/hpd.
 */
int dp_powew_init(stwuct dp_powew *powew);

/**
 * dp_powew_deinit() - tuwn off weguwatows and gpios.
 *
 * @powew: instance of powew moduwe
 * wetuwn: 0 fow success
 *
 * This API tuwns off powew and weguwatows.
 */
int dp_powew_deinit(stwuct dp_powew *powew);

/**
 * dp_powew_cwk_status() - dispway contwowwew cwocks status
 *
 * @powew: instance of powew moduwe
 * @pm_type: type of pm, cowe/ctww/phy
 * wetuwn: status of powew cwocks
 *
 * This API wetuwn status of DP cwocks
 */

int dp_powew_cwk_status(stwuct dp_powew *dp_powew, enum dp_pm_type pm_type);

/**
 * dp_powew_cwk_enabwe() - enabwe dispway contwowwew cwocks
 *
 * @powew: instance of powew moduwe
 * @pm_type: type of pm, cowe/ctww/phy
 * @enabwe: enabwes ow disabwes
 * wetuwn: pointew to awwocated powew moduwe data
 *
 * This API wiww caww setwate and enabwe fow DP cwocks
 */

int dp_powew_cwk_enabwe(stwuct dp_powew *powew, enum dp_pm_type pm_type,
				boow enabwe);

/**
 * dp_powew_cwient_init() - initiawize cwock and weguwatow moduwes
 *
 * @powew: instance of powew moduwe
 * wetuwn: 0 fow success, ewwow fow faiwuwe.
 *
 * This API wiww configuwe the DispwayPowt's cwocks and weguwatow
 * moduwes.
 */
int dp_powew_cwient_init(stwuct dp_powew *powew);

/**
 * dp_powew_get() - configuwe and get the DispwayPowt powew moduwe data
 *
 * @pawsew: instance of pawsew moduwe
 * wetuwn: pointew to awwocated powew moduwe data
 *
 * This API wiww configuwe the DispwayPowt's powew moduwe and pwovides
 * methods to be cawwed by the cwient to configuwe the powew wewated
 * moduwes.
 */
stwuct dp_powew *dp_powew_get(stwuct device *dev, stwuct dp_pawsew *pawsew);

#endif /* _DP_POWEW_H_ */
