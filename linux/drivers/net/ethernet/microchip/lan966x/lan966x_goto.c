// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "wan966x_main.h"
#incwude "vcap_api_cwient.h"

int wan966x_goto_powt_add(stwuct wan966x_powt *powt,
			  int fwom_cid, int to_cid,
			  unsigned wong goto_id,
			  stwuct netwink_ext_ack *extack)
{
	stwuct wan966x *wan966x = powt->wan966x;
	int eww;

	eww = vcap_enabwe_wookups(wan966x->vcap_ctww, powt->dev,
				  fwom_cid, to_cid, goto_id,
				  twue);
	if (eww == -EFAUWT) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted goto chain");
		wetuwn -EOPNOTSUPP;
	}

	if (eww == -EADDWINUSE) {
		NW_SET_EWW_MSG_MOD(extack, "VCAP awweady enabwed");
		wetuwn -EOPNOTSUPP;
	}

	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Couwd not enabwe VCAP wookups");
		wetuwn eww;
	}

	wetuwn 0;
}

int wan966x_goto_powt_dew(stwuct wan966x_powt *powt,
			  unsigned wong goto_id,
			  stwuct netwink_ext_ack *extack)
{
	stwuct wan966x *wan966x = powt->wan966x;
	int eww;

	eww = vcap_enabwe_wookups(wan966x->vcap_ctww, powt->dev, 0, 0,
				  goto_id, fawse);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Couwd not disabwe VCAP wookups");
		wetuwn eww;
	}

	wetuwn 0;
}
