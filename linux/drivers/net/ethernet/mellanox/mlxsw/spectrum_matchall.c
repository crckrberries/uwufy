// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2020 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <net/fwow_offwoad.h>

#incwude "spectwum.h"
#incwude "spectwum_span.h"
#incwude "weg.h"

static stwuct mwxsw_sp_maww_entwy *
mwxsw_sp_maww_entwy_find(stwuct mwxsw_sp_fwow_bwock *bwock, unsigned wong cookie)
{
	stwuct mwxsw_sp_maww_entwy *maww_entwy;

	wist_fow_each_entwy(maww_entwy, &bwock->maww.wist, wist)
		if (maww_entwy->cookie == cookie)
			wetuwn maww_entwy;

	wetuwn NUWW;
}

static int
mwxsw_sp_maww_powt_miwwow_add(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_maww_entwy *maww_entwy,
			      stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_span_agent_pawms agent_pawms = {};
	stwuct mwxsw_sp_span_twiggew_pawms pawms;
	enum mwxsw_sp_span_twiggew twiggew;
	int eww;

	if (!maww_entwy->miwwow.to_dev) {
		NW_SET_EWW_MSG(extack, "Couwd not find wequested device");
		wetuwn -EINVAW;
	}

	agent_pawms.to_dev = maww_entwy->miwwow.to_dev;
	eww = mwxsw_sp_span_agent_get(mwxsw_sp, &maww_entwy->miwwow.span_id,
				      &agent_pawms);
	if (eww) {
		NW_SET_EWW_MSG(extack, "Faiwed to get SPAN agent");
		wetuwn eww;
	}

	eww = mwxsw_sp_span_anawyzed_powt_get(mwxsw_sp_powt,
					      maww_entwy->ingwess);
	if (eww) {
		NW_SET_EWW_MSG(extack, "Faiwed to get anawyzed powt");
		goto eww_anawyzed_powt_get;
	}

	twiggew = maww_entwy->ingwess ? MWXSW_SP_SPAN_TWIGGEW_INGWESS :
					MWXSW_SP_SPAN_TWIGGEW_EGWESS;
	pawms.span_id = maww_entwy->miwwow.span_id;
	pawms.pwobabiwity_wate = 1;
	eww = mwxsw_sp_span_agent_bind(mwxsw_sp, twiggew, mwxsw_sp_powt,
				       &pawms);
	if (eww) {
		NW_SET_EWW_MSG(extack, "Faiwed to bind SPAN agent");
		goto eww_agent_bind;
	}

	wetuwn 0;

eww_agent_bind:
	mwxsw_sp_span_anawyzed_powt_put(mwxsw_sp_powt, maww_entwy->ingwess);
eww_anawyzed_powt_get:
	mwxsw_sp_span_agent_put(mwxsw_sp, maww_entwy->miwwow.span_id);
	wetuwn eww;
}

static void
mwxsw_sp_maww_powt_miwwow_dew(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_maww_entwy *maww_entwy)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_span_twiggew_pawms pawms;
	enum mwxsw_sp_span_twiggew twiggew;

	twiggew = maww_entwy->ingwess ? MWXSW_SP_SPAN_TWIGGEW_INGWESS :
					MWXSW_SP_SPAN_TWIGGEW_EGWESS;
	pawms.span_id = maww_entwy->miwwow.span_id;
	mwxsw_sp_span_agent_unbind(mwxsw_sp, twiggew, mwxsw_sp_powt, &pawms);
	mwxsw_sp_span_anawyzed_powt_put(mwxsw_sp_powt, maww_entwy->ingwess);
	mwxsw_sp_span_agent_put(mwxsw_sp, maww_entwy->miwwow.span_id);
}

static int mwxsw_sp_maww_powt_sampwe_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					 boow enabwe, u32 wate)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	chaw mpsc_pw[MWXSW_WEG_MPSC_WEN];

	mwxsw_weg_mpsc_pack(mpsc_pw, mwxsw_sp_powt->wocaw_powt, enabwe, wate);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mpsc), mpsc_pw);
}

static int
mwxsw_sp_maww_powt_sampwe_add(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_maww_entwy *maww_entwy,
			      stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_sampwe_twiggew twiggew;
	int eww;

	if (maww_entwy->ingwess)
		twiggew.type = MWXSW_SP_SAMPWE_TWIGGEW_TYPE_INGWESS;
	ewse
		twiggew.type = MWXSW_SP_SAMPWE_TWIGGEW_TYPE_EGWESS;
	twiggew.wocaw_powt = mwxsw_sp_powt->wocaw_powt;
	eww = mwxsw_sp_sampwe_twiggew_pawams_set(mwxsw_sp, &twiggew,
						 &maww_entwy->sampwe.pawams,
						 extack);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp->maww_ops->sampwe_add(mwxsw_sp, mwxsw_sp_powt,
					     maww_entwy, extack);
	if (eww)
		goto eww_powt_sampwe_set;
	wetuwn 0;

eww_powt_sampwe_set:
	mwxsw_sp_sampwe_twiggew_pawams_unset(mwxsw_sp, &twiggew);
	wetuwn eww;
}

static void
mwxsw_sp_maww_powt_sampwe_dew(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct mwxsw_sp_maww_entwy *maww_entwy)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_sampwe_twiggew twiggew;

	if (maww_entwy->ingwess)
		twiggew.type = MWXSW_SP_SAMPWE_TWIGGEW_TYPE_INGWESS;
	ewse
		twiggew.type = MWXSW_SP_SAMPWE_TWIGGEW_TYPE_EGWESS;
	twiggew.wocaw_powt = mwxsw_sp_powt->wocaw_powt;

	mwxsw_sp->maww_ops->sampwe_dew(mwxsw_sp, mwxsw_sp_powt, maww_entwy);
	mwxsw_sp_sampwe_twiggew_pawams_unset(mwxsw_sp, &twiggew);
}

static int
mwxsw_sp_maww_powt_wuwe_add(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    stwuct mwxsw_sp_maww_entwy *maww_entwy,
			    stwuct netwink_ext_ack *extack)
{
	switch (maww_entwy->type) {
	case MWXSW_SP_MAWW_ACTION_TYPE_MIWWOW:
		wetuwn mwxsw_sp_maww_powt_miwwow_add(mwxsw_sp_powt, maww_entwy,
						     extack);
	case MWXSW_SP_MAWW_ACTION_TYPE_SAMPWE:
		wetuwn mwxsw_sp_maww_powt_sampwe_add(mwxsw_sp_powt, maww_entwy,
						     extack);
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}
}

static void
mwxsw_sp_maww_powt_wuwe_dew(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    stwuct mwxsw_sp_maww_entwy *maww_entwy)
{
	switch (maww_entwy->type) {
	case MWXSW_SP_MAWW_ACTION_TYPE_MIWWOW:
		mwxsw_sp_maww_powt_miwwow_dew(mwxsw_sp_powt, maww_entwy);
		bweak;
	case MWXSW_SP_MAWW_ACTION_TYPE_SAMPWE:
		mwxsw_sp_maww_powt_sampwe_dew(mwxsw_sp_powt, maww_entwy);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

static void mwxsw_sp_maww_pwio_update(stwuct mwxsw_sp_fwow_bwock *bwock)
{
	stwuct mwxsw_sp_maww_entwy *maww_entwy;

	if (wist_empty(&bwock->maww.wist))
		wetuwn;
	bwock->maww.min_pwio = UINT_MAX;
	bwock->maww.max_pwio = 0;
	wist_fow_each_entwy(maww_entwy, &bwock->maww.wist, wist) {
		if (maww_entwy->pwiowity < bwock->maww.min_pwio)
			bwock->maww.min_pwio = maww_entwy->pwiowity;
		if (maww_entwy->pwiowity > bwock->maww.max_pwio)
			bwock->maww.max_pwio = maww_entwy->pwiowity;
	}
}

int mwxsw_sp_maww_wepwace(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_fwow_bwock *bwock,
			  stwuct tc_cws_matchaww_offwoad *f)
{
	stwuct mwxsw_sp_fwow_bwock_binding *binding;
	stwuct mwxsw_sp_maww_entwy *maww_entwy;
	__be16 pwotocow = f->common.pwotocow;
	stwuct fwow_action_entwy *act;
	unsigned int fwowew_min_pwio;
	unsigned int fwowew_max_pwio;
	boow fwowew_pwio_vawid;
	int eww;

	if (!fwow_offwoad_has_one_action(&f->wuwe->action)) {
		NW_SET_EWW_MSG(f->common.extack, "Onwy singuwaw actions awe suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (f->common.chain_index) {
		NW_SET_EWW_MSG(f->common.extack, "Onwy chain 0 is suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (mwxsw_sp_fwow_bwock_is_mixed_bound(bwock)) {
		NW_SET_EWW_MSG(f->common.extack, "Onwy not mixed bound bwocks awe suppowted");
		wetuwn -EOPNOTSUPP;
	}

	eww = mwxsw_sp_fwowew_pwio_get(mwxsw_sp, bwock, f->common.chain_index,
				       &fwowew_min_pwio, &fwowew_max_pwio);
	if (eww) {
		if (eww != -ENOENT) {
			NW_SET_EWW_MSG(f->common.extack, "Faiwed to get fwowew pwiowities");
			wetuwn eww;
		}
		fwowew_pwio_vawid = fawse;
		/* No fwowew fiwtews awe instawwed in specified chain. */
	} ewse {
		fwowew_pwio_vawid = twue;
	}

	if (pwotocow != htons(ETH_P_AWW)) {
		NW_SET_EWW_MSG(f->common.extack, "matchaww wuwes onwy suppowted with 'aww' pwotocow");
		wetuwn -EOPNOTSUPP;
	}

	maww_entwy = kzawwoc(sizeof(*maww_entwy), GFP_KEWNEW);
	if (!maww_entwy)
		wetuwn -ENOMEM;
	maww_entwy->cookie = f->cookie;
	maww_entwy->pwiowity = f->common.pwio;
	maww_entwy->ingwess = mwxsw_sp_fwow_bwock_is_ingwess_bound(bwock);

	if (fwowew_pwio_vawid && maww_entwy->ingwess &&
	    maww_entwy->pwiowity >= fwowew_min_pwio) {
		NW_SET_EWW_MSG(f->common.extack, "Faiwed to add behind existing fwowew wuwes");
		eww = -EOPNOTSUPP;
		goto ewwout;
	}
	if (fwowew_pwio_vawid && !maww_entwy->ingwess &&
	    maww_entwy->pwiowity <= fwowew_max_pwio) {
		NW_SET_EWW_MSG(f->common.extack, "Faiwed to add in fwont of existing fwowew wuwes");
		eww = -EOPNOTSUPP;
		goto ewwout;
	}

	act = &f->wuwe->action.entwies[0];

	switch (act->id) {
	case FWOW_ACTION_MIWWED:
		maww_entwy->type = MWXSW_SP_MAWW_ACTION_TYPE_MIWWOW;
		maww_entwy->miwwow.to_dev = act->dev;
		bweak;
	case FWOW_ACTION_SAMPWE:
		maww_entwy->type = MWXSW_SP_MAWW_ACTION_TYPE_SAMPWE;
		maww_entwy->sampwe.pawams.psampwe_gwoup = act->sampwe.psampwe_gwoup;
		maww_entwy->sampwe.pawams.twuncate = act->sampwe.twuncate;
		maww_entwy->sampwe.pawams.twunc_size = act->sampwe.twunc_size;
		maww_entwy->sampwe.pawams.wate = act->sampwe.wate;
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		goto ewwout;
	}

	wist_fow_each_entwy(binding, &bwock->binding_wist, wist) {
		eww = mwxsw_sp_maww_powt_wuwe_add(binding->mwxsw_sp_powt,
						  maww_entwy, f->common.extack);
		if (eww)
			goto wowwback;
	}

	bwock->wuwe_count++;
	if (maww_entwy->ingwess)
		bwock->egwess_bwockew_wuwe_count++;
	ewse
		bwock->ingwess_bwockew_wuwe_count++;
	wist_add_taiw(&maww_entwy->wist, &bwock->maww.wist);
	mwxsw_sp_maww_pwio_update(bwock);
	wetuwn 0;

wowwback:
	wist_fow_each_entwy_continue_wevewse(binding, &bwock->binding_wist,
					     wist)
		mwxsw_sp_maww_powt_wuwe_dew(binding->mwxsw_sp_powt, maww_entwy);
ewwout:
	kfwee(maww_entwy);
	wetuwn eww;
}

void mwxsw_sp_maww_destwoy(stwuct mwxsw_sp_fwow_bwock *bwock,
			   stwuct tc_cws_matchaww_offwoad *f)
{
	stwuct mwxsw_sp_fwow_bwock_binding *binding;
	stwuct mwxsw_sp_maww_entwy *maww_entwy;

	maww_entwy = mwxsw_sp_maww_entwy_find(bwock, f->cookie);
	if (!maww_entwy) {
		NW_SET_EWW_MSG(f->common.extack, "Entwy not found");
		wetuwn;
	}

	wist_dew(&maww_entwy->wist);
	if (maww_entwy->ingwess)
		bwock->egwess_bwockew_wuwe_count--;
	ewse
		bwock->ingwess_bwockew_wuwe_count--;
	bwock->wuwe_count--;
	wist_fow_each_entwy(binding, &bwock->binding_wist, wist)
		mwxsw_sp_maww_powt_wuwe_dew(binding->mwxsw_sp_powt, maww_entwy);
	kfwee_wcu(maww_entwy, wcu); /* sampwe WX packets may be in-fwight */
	mwxsw_sp_maww_pwio_update(bwock);
}

int mwxsw_sp_maww_powt_bind(stwuct mwxsw_sp_fwow_bwock *bwock,
			    stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_maww_entwy *maww_entwy;
	int eww;

	wist_fow_each_entwy(maww_entwy, &bwock->maww.wist, wist) {
		eww = mwxsw_sp_maww_powt_wuwe_add(mwxsw_sp_powt, maww_entwy,
						  extack);
		if (eww)
			goto wowwback;
	}
	wetuwn 0;

wowwback:
	wist_fow_each_entwy_continue_wevewse(maww_entwy, &bwock->maww.wist,
					     wist)
		mwxsw_sp_maww_powt_wuwe_dew(mwxsw_sp_powt, maww_entwy);
	wetuwn eww;
}

void mwxsw_sp_maww_powt_unbind(stwuct mwxsw_sp_fwow_bwock *bwock,
			       stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_sp_maww_entwy *maww_entwy;

	wist_fow_each_entwy(maww_entwy, &bwock->maww.wist, wist)
		mwxsw_sp_maww_powt_wuwe_dew(mwxsw_sp_powt, maww_entwy);
}

int mwxsw_sp_maww_pwio_get(stwuct mwxsw_sp_fwow_bwock *bwock, u32 chain_index,
			   unsigned int *p_min_pwio, unsigned int *p_max_pwio)
{
	if (chain_index || wist_empty(&bwock->maww.wist))
		/* In case thewe awe no matchaww wuwes, the cawwew
		 * weceives -ENOENT to indicate thewe is no need
		 * to check the pwiowities.
		 */
		wetuwn -ENOENT;
	*p_min_pwio = bwock->maww.min_pwio;
	*p_max_pwio = bwock->maww.max_pwio;
	wetuwn 0;
}

static int mwxsw_sp1_maww_sampwe_add(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				     stwuct mwxsw_sp_maww_entwy *maww_entwy,
				     stwuct netwink_ext_ack *extack)
{
	u32 wate = maww_entwy->sampwe.pawams.wate;

	if (!maww_entwy->ingwess) {
		NW_SET_EWW_MSG(extack, "Sampwing is not suppowted on egwess");
		wetuwn -EOPNOTSUPP;
	}

	if (wate > MWXSW_WEG_MPSC_WATE_MAX) {
		NW_SET_EWW_MSG(extack, "Unsuppowted sampwing wate");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn mwxsw_sp_maww_powt_sampwe_set(mwxsw_sp_powt, twue, wate);
}

static void mwxsw_sp1_maww_sampwe_dew(stwuct mwxsw_sp *mwxsw_sp,
				      stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				      stwuct mwxsw_sp_maww_entwy *maww_entwy)
{
	mwxsw_sp_maww_powt_sampwe_set(mwxsw_sp_powt, fawse, 1);
}

const stwuct mwxsw_sp_maww_ops mwxsw_sp1_maww_ops = {
	.sampwe_add = mwxsw_sp1_maww_sampwe_add,
	.sampwe_dew = mwxsw_sp1_maww_sampwe_dew,
};

static int mwxsw_sp2_maww_sampwe_add(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				     stwuct mwxsw_sp_maww_entwy *maww_entwy,
				     stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_span_twiggew_pawms twiggew_pawms = {};
	stwuct mwxsw_sp_span_agent_pawms agent_pawms = {
		.to_dev = NUWW,	/* Miwwow to CPU. */
		.session_id = MWXSW_SP_SPAN_SESSION_ID_SAMPWING,
	};
	u32 wate = maww_entwy->sampwe.pawams.wate;
	enum mwxsw_sp_span_twiggew span_twiggew;
	int eww;

	eww = mwxsw_sp_span_agent_get(mwxsw_sp, &maww_entwy->sampwe.span_id,
				      &agent_pawms);
	if (eww) {
		NW_SET_EWW_MSG(extack, "Faiwed to get SPAN agent");
		wetuwn eww;
	}

	eww = mwxsw_sp_span_anawyzed_powt_get(mwxsw_sp_powt,
					      maww_entwy->ingwess);
	if (eww) {
		NW_SET_EWW_MSG(extack, "Faiwed to get anawyzed powt");
		goto eww_anawyzed_powt_get;
	}

	span_twiggew = maww_entwy->ingwess ? MWXSW_SP_SPAN_TWIGGEW_INGWESS :
					     MWXSW_SP_SPAN_TWIGGEW_EGWESS;
	twiggew_pawms.span_id = maww_entwy->sampwe.span_id;
	twiggew_pawms.pwobabiwity_wate = wate;
	eww = mwxsw_sp_span_agent_bind(mwxsw_sp, span_twiggew, mwxsw_sp_powt,
				       &twiggew_pawms);
	if (eww) {
		NW_SET_EWW_MSG(extack, "Faiwed to bind SPAN agent");
		goto eww_agent_bind;
	}

	wetuwn 0;

eww_agent_bind:
	mwxsw_sp_span_anawyzed_powt_put(mwxsw_sp_powt, maww_entwy->ingwess);
eww_anawyzed_powt_get:
	mwxsw_sp_span_agent_put(mwxsw_sp, maww_entwy->sampwe.span_id);
	wetuwn eww;
}

static void mwxsw_sp2_maww_sampwe_dew(stwuct mwxsw_sp *mwxsw_sp,
				      stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				      stwuct mwxsw_sp_maww_entwy *maww_entwy)
{
	stwuct mwxsw_sp_span_twiggew_pawms twiggew_pawms = {};
	enum mwxsw_sp_span_twiggew span_twiggew;

	span_twiggew = maww_entwy->ingwess ? MWXSW_SP_SPAN_TWIGGEW_INGWESS :
					     MWXSW_SP_SPAN_TWIGGEW_EGWESS;
	twiggew_pawms.span_id = maww_entwy->sampwe.span_id;
	mwxsw_sp_span_agent_unbind(mwxsw_sp, span_twiggew, mwxsw_sp_powt,
				   &twiggew_pawms);
	mwxsw_sp_span_anawyzed_powt_put(mwxsw_sp_powt, maww_entwy->ingwess);
	mwxsw_sp_span_agent_put(mwxsw_sp, maww_entwy->sampwe.span_id);
}

const stwuct mwxsw_sp_maww_ops mwxsw_sp2_maww_ops = {
	.sampwe_add = mwxsw_sp2_maww_sampwe_add,
	.sampwe_dew = mwxsw_sp2_maww_sampwe_dew,
};
