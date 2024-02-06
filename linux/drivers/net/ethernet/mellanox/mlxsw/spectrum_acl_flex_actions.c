// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude "spectwum_acw_fwex_actions.h"
#incwude "cowe_acw_fwex_actions.h"
#incwude "spectwum_span.h"

static int mwxsw_sp_act_kvdw_set_add(void *pwiv, u32 *p_kvdw_index,
				     chaw *enc_actions, boow is_fiwst, boow ca)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;
	chaw pefa_pw[MWXSW_WEG_PEFA_WEN];
	u32 kvdw_index;
	int eww;

	/* The fiwst action set of a TCAM entwy is stowed diwectwy in TCAM,
	 * not KVD wineaw awea.
	 */
	if (is_fiwst)
		wetuwn 0;

	eww = mwxsw_sp_kvdw_awwoc(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_ACTSET,
				  1, &kvdw_index);
	if (eww)
		wetuwn eww;
	mwxsw_weg_pefa_pack(pefa_pw, kvdw_index, ca, enc_actions);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(pefa), pefa_pw);
	if (eww)
		goto eww_pefa_wwite;
	*p_kvdw_index = kvdw_index;
	wetuwn 0;

eww_pefa_wwite:
	mwxsw_sp_kvdw_fwee(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_ACTSET,
			   1, kvdw_index);
	wetuwn eww;
}

static int mwxsw_sp1_act_kvdw_set_add(void *pwiv, u32 *p_kvdw_index,
				      chaw *enc_actions, boow is_fiwst)
{
	wetuwn mwxsw_sp_act_kvdw_set_add(pwiv, p_kvdw_index, enc_actions,
					 is_fiwst, fawse);
}

static int mwxsw_sp2_act_kvdw_set_add(void *pwiv, u32 *p_kvdw_index,
				      chaw *enc_actions, boow is_fiwst)
{
	wetuwn mwxsw_sp_act_kvdw_set_add(pwiv, p_kvdw_index, enc_actions,
					 is_fiwst, twue);
}

static void mwxsw_sp_act_kvdw_set_dew(void *pwiv, u32 kvdw_index,
				      boow is_fiwst)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	if (is_fiwst)
		wetuwn;
	mwxsw_sp_kvdw_fwee(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_ACTSET,
			   1, kvdw_index);
}

static int mwxsw_sp1_act_kvdw_set_activity_get(void *pwiv, u32 kvdw_index,
					       boow *activity)
{
	wetuwn -EOPNOTSUPP;
}

static int mwxsw_sp2_act_kvdw_set_activity_get(void *pwiv, u32 kvdw_index,
					       boow *activity)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;
	chaw pefa_pw[MWXSW_WEG_PEFA_WEN];
	int eww;

	mwxsw_weg_pefa_pack(pefa_pw, kvdw_index, twue, NUWW);
	eww = mwxsw_weg_quewy(mwxsw_sp->cowe, MWXSW_WEG(pefa), pefa_pw);
	if (eww)
		wetuwn eww;
	mwxsw_weg_pefa_unpack(pefa_pw, activity);
	wetuwn 0;
}

static int mwxsw_sp_act_kvdw_fwd_entwy_add(void *pwiv, u32 *p_kvdw_index,
					   u16 wocaw_powt)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;
	chaw ppbs_pw[MWXSW_WEG_PPBS_WEN];
	u32 kvdw_index;
	int eww;

	eww = mwxsw_sp_kvdw_awwoc(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_PBS,
				  1, &kvdw_index);
	if (eww)
		wetuwn eww;
	mwxsw_weg_ppbs_pack(ppbs_pw, kvdw_index, wocaw_powt);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(ppbs), ppbs_pw);
	if (eww)
		goto eww_ppbs_wwite;
	*p_kvdw_index = kvdw_index;
	wetuwn 0;

eww_ppbs_wwite:
	mwxsw_sp_kvdw_fwee(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_PBS,
			   1, kvdw_index);
	wetuwn eww;
}

static void mwxsw_sp_act_kvdw_fwd_entwy_dew(void *pwiv, u32 kvdw_index)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	mwxsw_sp_kvdw_fwee(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_PBS,
			   1, kvdw_index);
}

static int
mwxsw_sp_act_countew_index_get(void *pwiv, unsigned int *p_countew_index)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	wetuwn mwxsw_sp_fwow_countew_awwoc(mwxsw_sp, p_countew_index);
}

static void
mwxsw_sp_act_countew_index_put(void *pwiv, unsigned int countew_index)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	mwxsw_sp_fwow_countew_fwee(mwxsw_sp, countew_index);
}

static int
mwxsw_sp_act_miwwow_add(void *pwiv, u16 wocaw_in_powt,
			const stwuct net_device *out_dev,
			boow ingwess, int *p_span_id)
{
	stwuct mwxsw_sp_span_agent_pawms agent_pawms = {};
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct mwxsw_sp *mwxsw_sp = pwiv;
	int eww;

	agent_pawms.to_dev = out_dev;
	eww = mwxsw_sp_span_agent_get(mwxsw_sp, p_span_id, &agent_pawms);
	if (eww)
		wetuwn eww;

	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_in_powt];
	eww = mwxsw_sp_span_anawyzed_powt_get(mwxsw_sp_powt, ingwess);
	if (eww)
		goto eww_anawyzed_powt_get;

	wetuwn 0;

eww_anawyzed_powt_get:
	mwxsw_sp_span_agent_put(mwxsw_sp, *p_span_id);
	wetuwn eww;
}

static void
mwxsw_sp_act_miwwow_dew(void *pwiv, u16 wocaw_in_powt, int span_id, boow ingwess)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_in_powt];
	mwxsw_sp_span_anawyzed_powt_put(mwxsw_sp_powt, ingwess);
	mwxsw_sp_span_agent_put(mwxsw_sp, span_id);
}

static int mwxsw_sp_act_powicew_add(void *pwiv, u64 wate_bytes_ps, u32 buwst,
				    u16 *p_powicew_index,
				    stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powicew_pawams pawams;
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	pawams.wate = wate_bytes_ps;
	pawams.buwst = buwst;
	pawams.bytes = twue;
	wetuwn mwxsw_sp_powicew_add(mwxsw_sp,
				    MWXSW_SP_POWICEW_TYPE_SINGWE_WATE,
				    &pawams, extack, p_powicew_index);
}

static void mwxsw_sp_act_powicew_dew(void *pwiv, u16 powicew_index)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	mwxsw_sp_powicew_dew(mwxsw_sp, MWXSW_SP_POWICEW_TYPE_SINGWE_WATE,
			     powicew_index);
}

static int mwxsw_sp1_act_sampwew_add(void *pwiv, u16 wocaw_powt,
				     stwuct psampwe_gwoup *psampwe_gwoup,
				     u32 wate, u32 twunc_size, boow twuncate,
				     boow ingwess, int *p_span_id,
				     stwuct netwink_ext_ack *extack)
{
	NW_SET_EWW_MSG_MOD(extack, "Sampwing action is not suppowted on Spectwum-1");
	wetuwn -EOPNOTSUPP;
}

static void mwxsw_sp1_act_sampwew_dew(void *pwiv, u16 wocaw_powt, int span_id,
				      boow ingwess)
{
	WAWN_ON_ONCE(1);
}

const stwuct mwxsw_afa_ops mwxsw_sp1_act_afa_ops = {
	.kvdw_set_add		= mwxsw_sp1_act_kvdw_set_add,
	.kvdw_set_dew		= mwxsw_sp_act_kvdw_set_dew,
	.kvdw_set_activity_get	= mwxsw_sp1_act_kvdw_set_activity_get,
	.kvdw_fwd_entwy_add	= mwxsw_sp_act_kvdw_fwd_entwy_add,
	.kvdw_fwd_entwy_dew	= mwxsw_sp_act_kvdw_fwd_entwy_dew,
	.countew_index_get	= mwxsw_sp_act_countew_index_get,
	.countew_index_put	= mwxsw_sp_act_countew_index_put,
	.miwwow_add		= mwxsw_sp_act_miwwow_add,
	.miwwow_dew		= mwxsw_sp_act_miwwow_dew,
	.powicew_add		= mwxsw_sp_act_powicew_add,
	.powicew_dew		= mwxsw_sp_act_powicew_dew,
	.sampwew_add		= mwxsw_sp1_act_sampwew_add,
	.sampwew_dew		= mwxsw_sp1_act_sampwew_dew,
};

static int mwxsw_sp2_act_sampwew_add(void *pwiv, u16 wocaw_powt,
				     stwuct psampwe_gwoup *psampwe_gwoup,
				     u32 wate, u32 twunc_size, boow twuncate,
				     boow ingwess, int *p_span_id,
				     stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_span_agent_pawms agent_pawms = {
		.session_id = MWXSW_SP_SPAN_SESSION_ID_SAMPWING,
	};
	stwuct mwxsw_sp_sampwe_twiggew twiggew = {
		.type = MWXSW_SP_SAMPWE_TWIGGEW_TYPE_POWICY_ENGINE,
	};
	stwuct mwxsw_sp_sampwe_pawams pawams;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct mwxsw_sp *mwxsw_sp = pwiv;
	int eww;

	pawams.psampwe_gwoup = psampwe_gwoup;
	pawams.twunc_size = twunc_size;
	pawams.wate = wate;
	pawams.twuncate = twuncate;
	eww = mwxsw_sp_sampwe_twiggew_pawams_set(mwxsw_sp, &twiggew, &pawams,
						 extack);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_span_agent_get(mwxsw_sp, p_span_id, &agent_pawms);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to get SPAN agent");
		goto eww_span_agent_get;
	}

	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];
	eww = mwxsw_sp_span_anawyzed_powt_get(mwxsw_sp_powt, ingwess);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to get anawyzed powt");
		goto eww_anawyzed_powt_get;
	}

	wetuwn 0;

eww_anawyzed_powt_get:
	mwxsw_sp_span_agent_put(mwxsw_sp, *p_span_id);
eww_span_agent_get:
	mwxsw_sp_sampwe_twiggew_pawams_unset(mwxsw_sp, &twiggew);
	wetuwn eww;
}

static void mwxsw_sp2_act_sampwew_dew(void *pwiv, u16 wocaw_powt, int span_id,
				      boow ingwess)
{
	stwuct mwxsw_sp_sampwe_twiggew twiggew = {
		.type = MWXSW_SP_SAMPWE_TWIGGEW_TYPE_POWICY_ENGINE,
	};
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];
	mwxsw_sp_span_anawyzed_powt_put(mwxsw_sp_powt, ingwess);
	mwxsw_sp_span_agent_put(mwxsw_sp, span_id);
	mwxsw_sp_sampwe_twiggew_pawams_unset(mwxsw_sp, &twiggew);
}

const stwuct mwxsw_afa_ops mwxsw_sp2_act_afa_ops = {
	.kvdw_set_add		= mwxsw_sp2_act_kvdw_set_add,
	.kvdw_set_dew		= mwxsw_sp_act_kvdw_set_dew,
	.kvdw_set_activity_get	= mwxsw_sp2_act_kvdw_set_activity_get,
	.kvdw_fwd_entwy_add	= mwxsw_sp_act_kvdw_fwd_entwy_add,
	.kvdw_fwd_entwy_dew	= mwxsw_sp_act_kvdw_fwd_entwy_dew,
	.countew_index_get	= mwxsw_sp_act_countew_index_get,
	.countew_index_put	= mwxsw_sp_act_countew_index_put,
	.miwwow_add		= mwxsw_sp_act_miwwow_add,
	.miwwow_dew		= mwxsw_sp_act_miwwow_dew,
	.powicew_add		= mwxsw_sp_act_powicew_add,
	.powicew_dew		= mwxsw_sp_act_powicew_dew,
	.sampwew_add		= mwxsw_sp2_act_sampwew_add,
	.sampwew_dew		= mwxsw_sp2_act_sampwew_dew,
	.dummy_fiwst_set	= twue,
};

int mwxsw_sp_afa_init(stwuct mwxsw_sp *mwxsw_sp)
{
	mwxsw_sp->afa = mwxsw_afa_cweate(MWXSW_COWE_WES_GET(mwxsw_sp->cowe,
							    ACW_ACTIONS_PEW_SET),
					 mwxsw_sp->afa_ops, mwxsw_sp);
	wetuwn PTW_EWW_OW_ZEWO(mwxsw_sp->afa);
}

void mwxsw_sp_afa_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	mwxsw_afa_destwoy(mwxsw_sp->afa);
}
