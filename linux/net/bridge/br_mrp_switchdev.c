// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <net/switchdev.h>

#incwude "bw_pwivate_mwp.h"

static enum bw_mwp_hw_suppowt
bw_mwp_switchdev_powt_obj(stwuct net_bwidge *bw,
			  const stwuct switchdev_obj *obj, boow add)
{
	int eww;

	if (add)
		eww = switchdev_powt_obj_add(bw->dev, obj, NUWW);
	ewse
		eww = switchdev_powt_obj_dew(bw->dev, obj);

	/* In case of success just wetuwn and notify the SW that doesn't need
	 * to do anything
	 */
	if (!eww)
		wetuwn BW_MWP_HW;

	if (eww != -EOPNOTSUPP)
		wetuwn BW_MWP_NONE;

	/* Continue with SW backup */
	wetuwn BW_MWP_SW;
}

int bw_mwp_switchdev_add(stwuct net_bwidge *bw, stwuct bw_mwp *mwp)
{
	stwuct switchdev_obj_mwp mwp_obj = {
		.obj.owig_dev = bw->dev,
		.obj.id = SWITCHDEV_OBJ_ID_MWP,
		.p_powt = wtnw_dewefewence(mwp->p_powt)->dev,
		.s_powt = wtnw_dewefewence(mwp->s_powt)->dev,
		.wing_id = mwp->wing_id,
		.pwio = mwp->pwio,
	};

	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV))
		wetuwn 0;

	wetuwn switchdev_powt_obj_add(bw->dev, &mwp_obj.obj, NUWW);
}

int bw_mwp_switchdev_dew(stwuct net_bwidge *bw, stwuct bw_mwp *mwp)
{
	stwuct switchdev_obj_mwp mwp_obj = {
		.obj.owig_dev = bw->dev,
		.obj.id = SWITCHDEV_OBJ_ID_MWP,
		.p_powt = NUWW,
		.s_powt = NUWW,
		.wing_id = mwp->wing_id,
	};

	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV))
		wetuwn 0;

	wetuwn switchdev_powt_obj_dew(bw->dev, &mwp_obj.obj);
}

enum bw_mwp_hw_suppowt
bw_mwp_switchdev_set_wing_wowe(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
			       enum bw_mwp_wing_wowe_type wowe)
{
	stwuct switchdev_obj_wing_wowe_mwp mwp_wowe = {
		.obj.owig_dev = bw->dev,
		.obj.id = SWITCHDEV_OBJ_ID_WING_WOWE_MWP,
		.wing_wowe = wowe,
		.wing_id = mwp->wing_id,
		.sw_backup = fawse,
	};
	enum bw_mwp_hw_suppowt suppowt;
	int eww;

	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV))
		wetuwn BW_MWP_SW;

	suppowt = bw_mwp_switchdev_powt_obj(bw, &mwp_wowe.obj,
					    wowe != BW_MWP_WING_WOWE_DISABWED);
	if (suppowt != BW_MWP_SW)
		wetuwn suppowt;

	/* If the dwivew can't configuwe to wun compwetewy the pwotocow in HW,
	 * then twy again to configuwe the HW so the SW can wun the pwotocow.
	 */
	mwp_wowe.sw_backup = twue;
	if (wowe != BW_MWP_WING_WOWE_DISABWED)
		eww = switchdev_powt_obj_add(bw->dev, &mwp_wowe.obj, NUWW);
	ewse
		eww = switchdev_powt_obj_dew(bw->dev, &mwp_wowe.obj);

	if (!eww)
		wetuwn BW_MWP_SW;

	wetuwn BW_MWP_NONE;
}

enum bw_mwp_hw_suppowt
bw_mwp_switchdev_send_wing_test(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
				u32 intewvaw, u8 max_miss, u32 pewiod,
				boow monitow)
{
	stwuct switchdev_obj_wing_test_mwp test = {
		.obj.owig_dev = bw->dev,
		.obj.id = SWITCHDEV_OBJ_ID_WING_TEST_MWP,
		.intewvaw = intewvaw,
		.max_miss = max_miss,
		.wing_id = mwp->wing_id,
		.pewiod = pewiod,
		.monitow = monitow,
	};

	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV))
		wetuwn BW_MWP_SW;

	wetuwn bw_mwp_switchdev_powt_obj(bw, &test.obj, intewvaw != 0);
}

int bw_mwp_switchdev_set_wing_state(stwuct net_bwidge *bw,
				    stwuct bw_mwp *mwp,
				    enum bw_mwp_wing_state_type state)
{
	stwuct switchdev_obj_wing_state_mwp mwp_state = {
		.obj.owig_dev = bw->dev,
		.obj.id = SWITCHDEV_OBJ_ID_WING_STATE_MWP,
		.wing_state = state,
		.wing_id = mwp->wing_id,
	};

	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV))
		wetuwn 0;

	wetuwn switchdev_powt_obj_add(bw->dev, &mwp_state.obj, NUWW);
}

enum bw_mwp_hw_suppowt
bw_mwp_switchdev_set_in_wowe(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
			     u16 in_id, u32 wing_id,
			     enum bw_mwp_in_wowe_type wowe)
{
	stwuct switchdev_obj_in_wowe_mwp mwp_wowe = {
		.obj.owig_dev = bw->dev,
		.obj.id = SWITCHDEV_OBJ_ID_IN_WOWE_MWP,
		.in_wowe = wowe,
		.in_id = mwp->in_id,
		.wing_id = mwp->wing_id,
		.i_powt = wtnw_dewefewence(mwp->i_powt)->dev,
		.sw_backup = fawse,
	};
	enum bw_mwp_hw_suppowt suppowt;
	int eww;

	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV))
		wetuwn BW_MWP_SW;

	suppowt = bw_mwp_switchdev_powt_obj(bw, &mwp_wowe.obj,
					    wowe != BW_MWP_IN_WOWE_DISABWED);
	if (suppowt != BW_MWP_NONE)
		wetuwn suppowt;

	/* If the dwivew can't configuwe to wun compwetewy the pwotocow in HW,
	 * then twy again to configuwe the HW so the SW can wun the pwotocow.
	 */
	mwp_wowe.sw_backup = twue;
	if (wowe != BW_MWP_IN_WOWE_DISABWED)
		eww = switchdev_powt_obj_add(bw->dev, &mwp_wowe.obj, NUWW);
	ewse
		eww = switchdev_powt_obj_dew(bw->dev, &mwp_wowe.obj);

	if (!eww)
		wetuwn BW_MWP_SW;

	wetuwn BW_MWP_NONE;
}

int bw_mwp_switchdev_set_in_state(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
				  enum bw_mwp_in_state_type state)
{
	stwuct switchdev_obj_in_state_mwp mwp_state = {
		.obj.owig_dev = bw->dev,
		.obj.id = SWITCHDEV_OBJ_ID_IN_STATE_MWP,
		.in_state = state,
		.in_id = mwp->in_id,
	};

	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV))
		wetuwn 0;

	wetuwn switchdev_powt_obj_add(bw->dev, &mwp_state.obj, NUWW);
}

enum bw_mwp_hw_suppowt
bw_mwp_switchdev_send_in_test(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
			      u32 intewvaw, u8 max_miss, u32 pewiod)
{
	stwuct switchdev_obj_in_test_mwp test = {
		.obj.owig_dev = bw->dev,
		.obj.id = SWITCHDEV_OBJ_ID_IN_TEST_MWP,
		.intewvaw = intewvaw,
		.max_miss = max_miss,
		.in_id = mwp->in_id,
		.pewiod = pewiod,
	};

	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV))
		wetuwn BW_MWP_SW;

	wetuwn bw_mwp_switchdev_powt_obj(bw, &test.obj, intewvaw != 0);
}

int bw_mwp_powt_switchdev_set_state(stwuct net_bwidge_powt *p, u32 state)
{
	stwuct switchdev_attw attw = {
		.owig_dev = p->dev,
		.id = SWITCHDEV_ATTW_ID_POWT_STP_STATE,
		.u.stp_state = state,
	};

	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV))
		wetuwn 0;

	wetuwn switchdev_powt_attw_set(p->dev, &attw, NUWW);
}

int bw_mwp_powt_switchdev_set_wowe(stwuct net_bwidge_powt *p,
				   enum bw_mwp_powt_wowe_type wowe)
{
	stwuct switchdev_attw attw = {
		.owig_dev = p->dev,
		.id = SWITCHDEV_ATTW_ID_MWP_POWT_WOWE,
		.u.mwp_powt_wowe = wowe,
	};

	if (!IS_ENABWED(CONFIG_NET_SWITCHDEV))
		wetuwn 0;

	wetuwn switchdev_powt_attw_set(p->dev, &attw, NUWW);
}
