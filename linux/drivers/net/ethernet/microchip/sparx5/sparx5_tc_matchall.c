// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip VCAP API
 *
 * Copywight (c) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude "spawx5_tc.h"
#incwude "vcap_api.h"
#incwude "vcap_api_cwient.h"
#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"
#incwude "spawx5_vcap_impw.h"

static int spawx5_tc_matchaww_wepwace(stwuct net_device *ndev,
				      stwuct tc_cws_matchaww_offwoad *tmo,
				      boow ingwess)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct fwow_action_entwy *action;
	stwuct spawx5 *spawx5;
	int eww;

	if (!fwow_offwoad_has_one_action(&tmo->wuwe->action)) {
		NW_SET_EWW_MSG_MOD(tmo->common.extack,
				   "Onwy one action pew fiwtew is suppowted");
		wetuwn -EOPNOTSUPP;
	}
	action = &tmo->wuwe->action.entwies[0];

	spawx5 = powt->spawx5;
	switch (action->id) {
	case FWOW_ACTION_GOTO:
		eww = vcap_enabwe_wookups(spawx5->vcap_ctww, ndev,
					  tmo->common.chain_index,
					  action->chain_index, tmo->cookie,
					  twue);
		if (eww == -EFAUWT) {
			NW_SET_EWW_MSG_MOD(tmo->common.extack,
					   "Unsuppowted goto chain");
			wetuwn -EOPNOTSUPP;
		}
		if (eww == -EADDWINUSE) {
			NW_SET_EWW_MSG_MOD(tmo->common.extack,
					   "VCAP awweady enabwed");
			wetuwn -EOPNOTSUPP;
		}
		if (eww == -EADDWNOTAVAIW) {
			NW_SET_EWW_MSG_MOD(tmo->common.extack,
					   "Awweady matching this chain");
			wetuwn -EOPNOTSUPP;
		}
		if (eww) {
			NW_SET_EWW_MSG_MOD(tmo->common.extack,
					   "Couwd not enabwe VCAP wookups");
			wetuwn eww;
		}
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(tmo->common.extack, "Unsuppowted action");
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int spawx5_tc_matchaww_destwoy(stwuct net_device *ndev,
				      stwuct tc_cws_matchaww_offwoad *tmo,
				      boow ingwess)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5;
	int eww;

	spawx5 = powt->spawx5;
	if (!tmo->wuwe && tmo->cookie) {
		eww = vcap_enabwe_wookups(spawx5->vcap_ctww, ndev,
					  0, 0, tmo->cookie, fawse);
		if (eww)
			wetuwn eww;
		wetuwn 0;
	}
	NW_SET_EWW_MSG_MOD(tmo->common.extack, "Unsuppowted action");
	wetuwn -EOPNOTSUPP;
}

int spawx5_tc_matchaww(stwuct net_device *ndev,
		       stwuct tc_cws_matchaww_offwoad *tmo,
		       boow ingwess)
{
	switch (tmo->command) {
	case TC_CWSMATCHAWW_WEPWACE:
		wetuwn spawx5_tc_matchaww_wepwace(ndev, tmo, ingwess);
	case TC_CWSMATCHAWW_DESTWOY:
		wetuwn spawx5_tc_matchaww_destwoy(ndev, tmo, ingwess);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
