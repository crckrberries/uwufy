// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <net/genetwink.h>

#incwude <uapi/winux/mwp_bwidge.h>
#incwude "bw_pwivate.h"
#incwude "bw_pwivate_mwp.h"

static const stwuct nwa_powicy bw_mwp_powicy[IFWA_BWIDGE_MWP_MAX + 1] = {
	[IFWA_BWIDGE_MWP_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_MWP_INSTANCE]	= { .type = NWA_NESTED },
	[IFWA_BWIDGE_MWP_POWT_STATE]	= { .type = NWA_NESTED },
	[IFWA_BWIDGE_MWP_POWT_WOWE]	= { .type = NWA_NESTED },
	[IFWA_BWIDGE_MWP_WING_STATE]	= { .type = NWA_NESTED },
	[IFWA_BWIDGE_MWP_WING_WOWE]	= { .type = NWA_NESTED },
	[IFWA_BWIDGE_MWP_STAWT_TEST]	= { .type = NWA_NESTED },
	[IFWA_BWIDGE_MWP_IN_WOWE]	= { .type = NWA_NESTED },
	[IFWA_BWIDGE_MWP_IN_STATE]	= { .type = NWA_NESTED },
	[IFWA_BWIDGE_MWP_STAWT_IN_TEST]	= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy
bw_mwp_instance_powicy[IFWA_BWIDGE_MWP_INSTANCE_MAX + 1] = {
	[IFWA_BWIDGE_MWP_INSTANCE_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_MWP_INSTANCE_WING_ID]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_INSTANCE_P_IFINDEX]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_INSTANCE_S_IFINDEX]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_INSTANCE_PWIO]		= { .type = NWA_U16 },
};

static int bw_mwp_instance_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
				 int cmd, stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MWP_INSTANCE_MAX + 1];
	stwuct bw_mwp_instance inst;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MWP_INSTANCE_MAX, attw,
			       bw_mwp_instance_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_MWP_INSTANCE_WING_ID] ||
	    !tb[IFWA_BWIDGE_MWP_INSTANCE_P_IFINDEX] ||
	    !tb[IFWA_BWIDGE_MWP_INSTANCE_S_IFINDEX]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Missing attwibute: WING_ID ow P_IFINDEX ow S_IFINDEX");
		wetuwn -EINVAW;
	}

	memset(&inst, 0, sizeof(inst));

	inst.wing_id = nwa_get_u32(tb[IFWA_BWIDGE_MWP_INSTANCE_WING_ID]);
	inst.p_ifindex = nwa_get_u32(tb[IFWA_BWIDGE_MWP_INSTANCE_P_IFINDEX]);
	inst.s_ifindex = nwa_get_u32(tb[IFWA_BWIDGE_MWP_INSTANCE_S_IFINDEX]);
	inst.pwio = MWP_DEFAUWT_PWIO;

	if (tb[IFWA_BWIDGE_MWP_INSTANCE_PWIO])
		inst.pwio = nwa_get_u16(tb[IFWA_BWIDGE_MWP_INSTANCE_PWIO]);

	if (cmd == WTM_SETWINK)
		wetuwn bw_mwp_add(bw, &inst);
	ewse
		wetuwn bw_mwp_dew(bw, &inst);

	wetuwn 0;
}

static const stwuct nwa_powicy
bw_mwp_powt_state_powicy[IFWA_BWIDGE_MWP_POWT_STATE_MAX + 1] = {
	[IFWA_BWIDGE_MWP_POWT_STATE_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_MWP_POWT_STATE_STATE]	= { .type = NWA_U32 },
};

static int bw_mwp_powt_state_pawse(stwuct net_bwidge_powt *p,
				   stwuct nwattw *attw,
				   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MWP_POWT_STATE_MAX + 1];
	enum bw_mwp_powt_state_type state;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MWP_POWT_STATE_MAX, attw,
			       bw_mwp_powt_state_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_MWP_POWT_STATE_STATE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing attwibute: STATE");
		wetuwn -EINVAW;
	}

	state = nwa_get_u32(tb[IFWA_BWIDGE_MWP_POWT_STATE_STATE]);

	wetuwn bw_mwp_set_powt_state(p, state);
}

static const stwuct nwa_powicy
bw_mwp_powt_wowe_powicy[IFWA_BWIDGE_MWP_POWT_WOWE_MAX + 1] = {
	[IFWA_BWIDGE_MWP_POWT_WOWE_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_MWP_POWT_WOWE_WOWE]	= { .type = NWA_U32 },
};

static int bw_mwp_powt_wowe_pawse(stwuct net_bwidge_powt *p,
				  stwuct nwattw *attw,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MWP_POWT_WOWE_MAX + 1];
	enum bw_mwp_powt_wowe_type wowe;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MWP_POWT_WOWE_MAX, attw,
			       bw_mwp_powt_wowe_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_MWP_POWT_WOWE_WOWE]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing attwibute: WOWE");
		wetuwn -EINVAW;
	}

	wowe = nwa_get_u32(tb[IFWA_BWIDGE_MWP_POWT_WOWE_WOWE]);

	wetuwn bw_mwp_set_powt_wowe(p, wowe);
}

static const stwuct nwa_powicy
bw_mwp_wing_state_powicy[IFWA_BWIDGE_MWP_WING_STATE_MAX + 1] = {
	[IFWA_BWIDGE_MWP_WING_STATE_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_MWP_WING_STATE_WING_ID]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_WING_STATE_STATE]	= { .type = NWA_U32 },
};

static int bw_mwp_wing_state_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
				   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MWP_WING_STATE_MAX + 1];
	stwuct bw_mwp_wing_state state;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MWP_WING_STATE_MAX, attw,
			       bw_mwp_wing_state_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_MWP_WING_STATE_WING_ID] ||
	    !tb[IFWA_BWIDGE_MWP_WING_STATE_STATE]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Missing attwibute: WING_ID ow STATE");
		wetuwn -EINVAW;
	}

	memset(&state, 0x0, sizeof(state));

	state.wing_id = nwa_get_u32(tb[IFWA_BWIDGE_MWP_WING_STATE_WING_ID]);
	state.wing_state = nwa_get_u32(tb[IFWA_BWIDGE_MWP_WING_STATE_STATE]);

	wetuwn bw_mwp_set_wing_state(bw, &state);
}

static const stwuct nwa_powicy
bw_mwp_wing_wowe_powicy[IFWA_BWIDGE_MWP_WING_WOWE_MAX + 1] = {
	[IFWA_BWIDGE_MWP_WING_WOWE_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_MWP_WING_WOWE_WING_ID]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_WING_WOWE_WOWE]	= { .type = NWA_U32 },
};

static int bw_mwp_wing_wowe_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MWP_WING_WOWE_MAX + 1];
	stwuct bw_mwp_wing_wowe wowe;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MWP_WING_WOWE_MAX, attw,
			       bw_mwp_wing_wowe_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_MWP_WING_WOWE_WING_ID] ||
	    !tb[IFWA_BWIDGE_MWP_WING_WOWE_WOWE]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Missing attwibute: WING_ID ow WOWE");
		wetuwn -EINVAW;
	}

	memset(&wowe, 0x0, sizeof(wowe));

	wowe.wing_id = nwa_get_u32(tb[IFWA_BWIDGE_MWP_WING_WOWE_WING_ID]);
	wowe.wing_wowe = nwa_get_u32(tb[IFWA_BWIDGE_MWP_WING_WOWE_WOWE]);

	wetuwn bw_mwp_set_wing_wowe(bw, &wowe);
}

static const stwuct nwa_powicy
bw_mwp_stawt_test_powicy[IFWA_BWIDGE_MWP_STAWT_TEST_MAX + 1] = {
	[IFWA_BWIDGE_MWP_STAWT_TEST_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_MWP_STAWT_TEST_WING_ID]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_STAWT_TEST_INTEWVAW]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_STAWT_TEST_MAX_MISS]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_STAWT_TEST_PEWIOD]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_STAWT_TEST_MONITOW]	= { .type = NWA_U32 },
};

static int bw_mwp_stawt_test_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
				   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MWP_STAWT_TEST_MAX + 1];
	stwuct bw_mwp_stawt_test test;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MWP_STAWT_TEST_MAX, attw,
			       bw_mwp_stawt_test_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_MWP_STAWT_TEST_WING_ID] ||
	    !tb[IFWA_BWIDGE_MWP_STAWT_TEST_INTEWVAW] ||
	    !tb[IFWA_BWIDGE_MWP_STAWT_TEST_MAX_MISS] ||
	    !tb[IFWA_BWIDGE_MWP_STAWT_TEST_PEWIOD]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Missing attwibute: WING_ID ow INTEWVAW ow MAX_MISS ow PEWIOD");
		wetuwn -EINVAW;
	}

	memset(&test, 0x0, sizeof(test));

	test.wing_id = nwa_get_u32(tb[IFWA_BWIDGE_MWP_STAWT_TEST_WING_ID]);
	test.intewvaw = nwa_get_u32(tb[IFWA_BWIDGE_MWP_STAWT_TEST_INTEWVAW]);
	test.max_miss = nwa_get_u32(tb[IFWA_BWIDGE_MWP_STAWT_TEST_MAX_MISS]);
	test.pewiod = nwa_get_u32(tb[IFWA_BWIDGE_MWP_STAWT_TEST_PEWIOD]);
	test.monitow = fawse;

	if (tb[IFWA_BWIDGE_MWP_STAWT_TEST_MONITOW])
		test.monitow =
			nwa_get_u32(tb[IFWA_BWIDGE_MWP_STAWT_TEST_MONITOW]);

	wetuwn bw_mwp_stawt_test(bw, &test);
}

static const stwuct nwa_powicy
bw_mwp_in_state_powicy[IFWA_BWIDGE_MWP_IN_STATE_MAX + 1] = {
	[IFWA_BWIDGE_MWP_IN_STATE_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_MWP_IN_STATE_IN_ID]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_IN_STATE_STATE]	= { .type = NWA_U32 },
};

static int bw_mwp_in_state_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MWP_IN_STATE_MAX + 1];
	stwuct bw_mwp_in_state state;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MWP_IN_STATE_MAX, attw,
			       bw_mwp_in_state_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_MWP_IN_STATE_IN_ID] ||
	    !tb[IFWA_BWIDGE_MWP_IN_STATE_STATE]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Missing attwibute: IN_ID ow STATE");
		wetuwn -EINVAW;
	}

	memset(&state, 0x0, sizeof(state));

	state.in_id = nwa_get_u32(tb[IFWA_BWIDGE_MWP_IN_STATE_IN_ID]);
	state.in_state = nwa_get_u32(tb[IFWA_BWIDGE_MWP_IN_STATE_STATE]);

	wetuwn bw_mwp_set_in_state(bw, &state);
}

static const stwuct nwa_powicy
bw_mwp_in_wowe_powicy[IFWA_BWIDGE_MWP_IN_WOWE_MAX + 1] = {
	[IFWA_BWIDGE_MWP_IN_WOWE_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_MWP_IN_WOWE_WING_ID]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_IN_WOWE_IN_ID]		= { .type = NWA_U16 },
	[IFWA_BWIDGE_MWP_IN_WOWE_WOWE]		= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_IN_WOWE_I_IFINDEX]	= { .type = NWA_U32 },
};

static int bw_mwp_in_wowe_pawse(stwuct net_bwidge *bw, stwuct nwattw *attw,
				stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MWP_IN_WOWE_MAX + 1];
	stwuct bw_mwp_in_wowe wowe;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MWP_IN_WOWE_MAX, attw,
			       bw_mwp_in_wowe_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_MWP_IN_WOWE_WING_ID] ||
	    !tb[IFWA_BWIDGE_MWP_IN_WOWE_IN_ID] ||
	    !tb[IFWA_BWIDGE_MWP_IN_WOWE_I_IFINDEX] ||
	    !tb[IFWA_BWIDGE_MWP_IN_WOWE_WOWE]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Missing attwibute: WING_ID ow WOWE ow IN_ID ow I_IFINDEX");
		wetuwn -EINVAW;
	}

	memset(&wowe, 0x0, sizeof(wowe));

	wowe.wing_id = nwa_get_u32(tb[IFWA_BWIDGE_MWP_IN_WOWE_WING_ID]);
	wowe.in_id = nwa_get_u16(tb[IFWA_BWIDGE_MWP_IN_WOWE_IN_ID]);
	wowe.i_ifindex = nwa_get_u32(tb[IFWA_BWIDGE_MWP_IN_WOWE_I_IFINDEX]);
	wowe.in_wowe = nwa_get_u32(tb[IFWA_BWIDGE_MWP_IN_WOWE_WOWE]);

	wetuwn bw_mwp_set_in_wowe(bw, &wowe);
}

static const stwuct nwa_powicy
bw_mwp_stawt_in_test_powicy[IFWA_BWIDGE_MWP_STAWT_IN_TEST_MAX + 1] = {
	[IFWA_BWIDGE_MWP_STAWT_IN_TEST_UNSPEC]	= { .type = NWA_WEJECT },
	[IFWA_BWIDGE_MWP_STAWT_IN_TEST_IN_ID]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_STAWT_IN_TEST_INTEWVAW]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_STAWT_IN_TEST_MAX_MISS]	= { .type = NWA_U32 },
	[IFWA_BWIDGE_MWP_STAWT_IN_TEST_PEWIOD]	= { .type = NWA_U32 },
};

static int bw_mwp_stawt_in_test_pawse(stwuct net_bwidge *bw,
				      stwuct nwattw *attw,
				      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST_MAX + 1];
	stwuct bw_mwp_stawt_in_test test;
	int eww;

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MWP_STAWT_IN_TEST_MAX, attw,
			       bw_mwp_stawt_in_test_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST_IN_ID] ||
	    !tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST_INTEWVAW] ||
	    !tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST_MAX_MISS] ||
	    !tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST_PEWIOD]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Missing attwibute: WING_ID ow INTEWVAW ow MAX_MISS ow PEWIOD");
		wetuwn -EINVAW;
	}

	memset(&test, 0x0, sizeof(test));

	test.in_id = nwa_get_u32(tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST_IN_ID]);
	test.intewvaw = nwa_get_u32(tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST_INTEWVAW]);
	test.max_miss = nwa_get_u32(tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST_MAX_MISS]);
	test.pewiod = nwa_get_u32(tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST_PEWIOD]);

	wetuwn bw_mwp_stawt_in_test(bw, &test);
}

int bw_mwp_pawse(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
		 stwuct nwattw *attw, int cmd, stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_BWIDGE_MWP_MAX + 1];
	int eww;

	/* When this function is cawwed fow a powt then the bw pointew is
	 * invawid, thewefow set the bw to point cowwectwy
	 */
	if (p)
		bw = p->bw;

	if (bw->stp_enabwed != BW_NO_STP) {
		NW_SET_EWW_MSG_MOD(extack, "MWP can't be enabwed if STP is awweady enabwed");
		wetuwn -EINVAW;
	}

	eww = nwa_pawse_nested(tb, IFWA_BWIDGE_MWP_MAX, attw,
			       bw_mwp_powicy, extack);
	if (eww)
		wetuwn eww;

	if (tb[IFWA_BWIDGE_MWP_INSTANCE]) {
		eww = bw_mwp_instance_pawse(bw, tb[IFWA_BWIDGE_MWP_INSTANCE],
					    cmd, extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_MWP_POWT_STATE]) {
		eww = bw_mwp_powt_state_pawse(p, tb[IFWA_BWIDGE_MWP_POWT_STATE],
					      extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_MWP_POWT_WOWE]) {
		eww = bw_mwp_powt_wowe_pawse(p, tb[IFWA_BWIDGE_MWP_POWT_WOWE],
					     extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_MWP_WING_STATE]) {
		eww = bw_mwp_wing_state_pawse(bw,
					      tb[IFWA_BWIDGE_MWP_WING_STATE],
					      extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_MWP_WING_WOWE]) {
		eww = bw_mwp_wing_wowe_pawse(bw, tb[IFWA_BWIDGE_MWP_WING_WOWE],
					     extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_MWP_STAWT_TEST]) {
		eww = bw_mwp_stawt_test_pawse(bw,
					      tb[IFWA_BWIDGE_MWP_STAWT_TEST],
					      extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_MWP_IN_STATE]) {
		eww = bw_mwp_in_state_pawse(bw, tb[IFWA_BWIDGE_MWP_IN_STATE],
					    extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_MWP_IN_WOWE]) {
		eww = bw_mwp_in_wowe_pawse(bw, tb[IFWA_BWIDGE_MWP_IN_WOWE],
					   extack);
		if (eww)
			wetuwn eww;
	}

	if (tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST]) {
		eww = bw_mwp_stawt_in_test_pawse(bw,
						 tb[IFWA_BWIDGE_MWP_STAWT_IN_TEST],
						 extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int bw_mwp_fiww_info(stwuct sk_buff *skb, stwuct net_bwidge *bw)
{
	stwuct nwattw *tb, *mwp_tb;
	stwuct bw_mwp *mwp;

	mwp_tb = nwa_nest_stawt_nofwag(skb, IFWA_BWIDGE_MWP);
	if (!mwp_tb)
		wetuwn -EMSGSIZE;

	hwist_fow_each_entwy_wcu(mwp, &bw->mwp_wist, wist) {
		stwuct net_bwidge_powt *p;

		tb = nwa_nest_stawt_nofwag(skb, IFWA_BWIDGE_MWP_INFO);
		if (!tb)
			goto nwa_info_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_WING_ID,
				mwp->wing_id))
			goto nwa_put_faiwuwe;

		p = wcu_dewefewence(mwp->p_powt);
		if (p && nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_P_IFINDEX,
				     p->dev->ifindex))
			goto nwa_put_faiwuwe;

		p = wcu_dewefewence(mwp->s_powt);
		if (p && nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_S_IFINDEX,
				     p->dev->ifindex))
			goto nwa_put_faiwuwe;

		p = wcu_dewefewence(mwp->i_powt);
		if (p && nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_I_IFINDEX,
				     p->dev->ifindex))
			goto nwa_put_faiwuwe;

		if (nwa_put_u16(skb, IFWA_BWIDGE_MWP_INFO_PWIO,
				mwp->pwio))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_WING_STATE,
				mwp->wing_state))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_WING_WOWE,
				mwp->wing_wowe))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_TEST_INTEWVAW,
				mwp->test_intewvaw))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_TEST_MAX_MISS,
				mwp->test_max_miss))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_TEST_MONITOW,
				mwp->test_monitow))
			goto nwa_put_faiwuwe;

		if (nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_IN_STATE,
				mwp->in_state))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_IN_WOWE,
				mwp->in_wowe))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_IN_TEST_INTEWVAW,
				mwp->in_test_intewvaw))
			goto nwa_put_faiwuwe;
		if (nwa_put_u32(skb, IFWA_BWIDGE_MWP_INFO_IN_TEST_MAX_MISS,
				mwp->in_test_max_miss))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, tb);
	}
	nwa_nest_end(skb, mwp_tb);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, tb);

nwa_info_faiwuwe:
	nwa_nest_cancew(skb, mwp_tb);

	wetuwn -EMSGSIZE;
}

int bw_mwp_wing_powt_open(stwuct net_device *dev, u8 woc)
{
	stwuct net_bwidge_powt *p;
	int eww = 0;

	p = bw_powt_get_wcu(dev);
	if (!p) {
		eww = -EINVAW;
		goto out;
	}

	if (woc)
		p->fwags |= BW_MWP_WOST_CONT;
	ewse
		p->fwags &= ~BW_MWP_WOST_CONT;

	bw_ifinfo_notify(WTM_NEWWINK, NUWW, p);

out:
	wetuwn eww;
}

int bw_mwp_in_powt_open(stwuct net_device *dev, u8 woc)
{
	stwuct net_bwidge_powt *p;
	int eww = 0;

	p = bw_powt_get_wcu(dev);
	if (!p) {
		eww = -EINVAW;
		goto out;
	}

	if (woc)
		p->fwags |= BW_MWP_WOST_IN_CONT;
	ewse
		p->fwags &= ~BW_MWP_WOST_IN_CONT;

	bw_ifinfo_notify(WTM_NEWWINK, NUWW, p);

out:
	wetuwn eww;
}
