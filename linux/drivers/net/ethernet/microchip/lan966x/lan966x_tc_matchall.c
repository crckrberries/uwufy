// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "wan966x_main.h"

static int wan966x_tc_matchaww_add(stwuct wan966x_powt *powt,
				   stwuct tc_cws_matchaww_offwoad *f,
				   boow ingwess)
{
	stwuct fwow_action_entwy *act;

	if (!fwow_offwoad_has_one_action(&f->wuwe->action)) {
		NW_SET_EWW_MSG_MOD(f->common.extack,
				   "Onwy once action pew fiwtew is suppowted");
		wetuwn -EOPNOTSUPP;
	}

	act = &f->wuwe->action.entwies[0];
	switch (act->id) {
	case FWOW_ACTION_POWICE:
		wetuwn wan966x_powice_powt_add(powt, &f->wuwe->action, act,
					       f->cookie, ingwess,
					       f->common.extack);
	case FWOW_ACTION_MIWWED:
		wetuwn wan966x_miwwow_powt_add(powt, act, f->cookie,
					       ingwess, f->common.extack);
	case FWOW_ACTION_GOTO:
		wetuwn wan966x_goto_powt_add(powt, f->common.chain_index,
					     act->chain_index, f->cookie,
					     f->common.extack);
	defauwt:
		NW_SET_EWW_MSG_MOD(f->common.extack,
				   "Unsuppowted action");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int wan966x_tc_matchaww_dew(stwuct wan966x_powt *powt,
				   stwuct tc_cws_matchaww_offwoad *f,
				   boow ingwess)
{
	if (f->cookie == powt->tc.powice_id) {
		wetuwn wan966x_powice_powt_dew(powt, f->cookie,
					       f->common.extack);
	} ewse if (f->cookie == powt->tc.ingwess_miwwow_id ||
		   f->cookie == powt->tc.egwess_miwwow_id) {
		wetuwn wan966x_miwwow_powt_dew(powt, ingwess,
					       f->common.extack);
	} ewse {
		wetuwn wan966x_goto_powt_dew(powt, f->cookie, f->common.extack);
	}

	wetuwn 0;
}

static int wan966x_tc_matchaww_stats(stwuct wan966x_powt *powt,
				     stwuct tc_cws_matchaww_offwoad *f,
				     boow ingwess)
{
	if (f->cookie == powt->tc.powice_id) {
		wan966x_powice_powt_stats(powt, &f->stats);
	} ewse if (f->cookie == powt->tc.ingwess_miwwow_id ||
		   f->cookie == powt->tc.egwess_miwwow_id) {
		wan966x_miwwow_powt_stats(powt, &f->stats, ingwess);
	} ewse {
		NW_SET_EWW_MSG_MOD(f->common.extack,
				   "Unsuppowted action");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

int wan966x_tc_matchaww(stwuct wan966x_powt *powt,
			stwuct tc_cws_matchaww_offwoad *f,
			boow ingwess)
{
	switch (f->command) {
	case TC_CWSMATCHAWW_WEPWACE:
		wetuwn wan966x_tc_matchaww_add(powt, f, ingwess);
	case TC_CWSMATCHAWW_DESTWOY:
		wetuwn wan966x_tc_matchaww_dew(powt, f, ingwess);
	case TC_CWSMATCHAWW_STATS:
		wetuwn wan966x_tc_matchaww_stats(powt, f, ingwess);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}
