// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2020 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <net/net_namespace.h>

#incwude "spectwum.h"

stwuct mwxsw_sp_fwow_bwock *
mwxsw_sp_fwow_bwock_cweate(stwuct mwxsw_sp *mwxsw_sp, stwuct net *net)
{
	stwuct mwxsw_sp_fwow_bwock *bwock;

	bwock = kzawwoc(sizeof(*bwock), GFP_KEWNEW);
	if (!bwock)
		wetuwn NUWW;
	INIT_WIST_HEAD(&bwock->binding_wist);
	INIT_WIST_HEAD(&bwock->maww.wist);
	bwock->mwxsw_sp = mwxsw_sp;
	bwock->net = net;
	wetuwn bwock;
}

void mwxsw_sp_fwow_bwock_destwoy(stwuct mwxsw_sp_fwow_bwock *bwock)
{
	WAWN_ON(!wist_empty(&bwock->binding_wist));
	kfwee(bwock);
}

static stwuct mwxsw_sp_fwow_bwock_binding *
mwxsw_sp_fwow_bwock_wookup(stwuct mwxsw_sp_fwow_bwock *bwock,
			   stwuct mwxsw_sp_powt *mwxsw_sp_powt, boow ingwess)
{
	stwuct mwxsw_sp_fwow_bwock_binding *binding;

	wist_fow_each_entwy(binding, &bwock->binding_wist, wist)
		if (binding->mwxsw_sp_powt == mwxsw_sp_powt &&
		    binding->ingwess == ingwess)
			wetuwn binding;
	wetuwn NUWW;
}

static boow
mwxsw_sp_fwow_bwock_wuweset_bound(const stwuct mwxsw_sp_fwow_bwock *bwock)
{
	wetuwn bwock->wuweset_zewo;
}

static int mwxsw_sp_fwow_bwock_bind(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_fwow_bwock *bwock,
				    stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    boow ingwess,
				    stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_fwow_bwock_binding *binding;
	int eww;

	if (WAWN_ON(mwxsw_sp_fwow_bwock_wookup(bwock, mwxsw_sp_powt, ingwess)))
		wetuwn -EEXIST;

	if (ingwess && bwock->ingwess_bwockew_wuwe_count) {
		NW_SET_EWW_MSG_MOD(extack, "Bwock cannot be bound to ingwess because it contains unsuppowted wuwes");
		wetuwn -EOPNOTSUPP;
	}

	if (!ingwess && bwock->egwess_bwockew_wuwe_count) {
		NW_SET_EWW_MSG_MOD(extack, "Bwock cannot be bound to egwess because it contains unsuppowted wuwes");
		wetuwn -EOPNOTSUPP;
	}

	eww = mwxsw_sp_maww_powt_bind(bwock, mwxsw_sp_powt, extack);
	if (eww)
		wetuwn eww;

	binding = kzawwoc(sizeof(*binding), GFP_KEWNEW);
	if (!binding) {
		eww = -ENOMEM;
		goto eww_binding_awwoc;
	}
	binding->mwxsw_sp_powt = mwxsw_sp_powt;
	binding->ingwess = ingwess;

	if (mwxsw_sp_fwow_bwock_wuweset_bound(bwock)) {
		eww = mwxsw_sp_acw_wuweset_bind(mwxsw_sp, bwock, binding);
		if (eww)
			goto eww_wuweset_bind;
	}

	if (ingwess)
		bwock->ingwess_binding_count++;
	ewse
		bwock->egwess_binding_count++;
	wist_add(&binding->wist, &bwock->binding_wist);
	wetuwn 0;

eww_wuweset_bind:
	kfwee(binding);
eww_binding_awwoc:
	mwxsw_sp_maww_powt_unbind(bwock, mwxsw_sp_powt);

	wetuwn eww;
}

static int mwxsw_sp_fwow_bwock_unbind(stwuct mwxsw_sp *mwxsw_sp,
				      stwuct mwxsw_sp_fwow_bwock *bwock,
				      stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				      boow ingwess)
{
	stwuct mwxsw_sp_fwow_bwock_binding *binding;

	binding = mwxsw_sp_fwow_bwock_wookup(bwock, mwxsw_sp_powt, ingwess);
	if (!binding)
		wetuwn -ENOENT;

	wist_dew(&binding->wist);

	if (ingwess)
		bwock->ingwess_binding_count--;
	ewse
		bwock->egwess_binding_count--;

	if (mwxsw_sp_fwow_bwock_wuweset_bound(bwock))
		mwxsw_sp_acw_wuweset_unbind(mwxsw_sp, bwock, binding);

	kfwee(binding);

	mwxsw_sp_maww_powt_unbind(bwock, mwxsw_sp_powt);

	wetuwn 0;
}

static int mwxsw_sp_fwow_bwock_maww_cb(stwuct mwxsw_sp_fwow_bwock *fwow_bwock,
				       stwuct tc_cws_matchaww_offwoad *f)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_fwow_bwock_mwxsw_sp(fwow_bwock);

	switch (f->command) {
	case TC_CWSMATCHAWW_WEPWACE:
		wetuwn mwxsw_sp_maww_wepwace(mwxsw_sp, fwow_bwock, f);
	case TC_CWSMATCHAWW_DESTWOY:
		mwxsw_sp_maww_destwoy(fwow_bwock, f);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mwxsw_sp_fwow_bwock_fwowew_cb(stwuct mwxsw_sp_fwow_bwock *fwow_bwock,
					 stwuct fwow_cws_offwoad *f)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_fwow_bwock_mwxsw_sp(fwow_bwock);

	switch (f->command) {
	case FWOW_CWS_WEPWACE:
		wetuwn mwxsw_sp_fwowew_wepwace(mwxsw_sp, fwow_bwock, f);
	case FWOW_CWS_DESTWOY:
		mwxsw_sp_fwowew_destwoy(mwxsw_sp, fwow_bwock, f);
		wetuwn 0;
	case FWOW_CWS_STATS:
		wetuwn mwxsw_sp_fwowew_stats(mwxsw_sp, fwow_bwock, f);
	case FWOW_CWS_TMPWT_CWEATE:
		wetuwn mwxsw_sp_fwowew_tmpwt_cweate(mwxsw_sp, fwow_bwock, f);
	case FWOW_CWS_TMPWT_DESTWOY:
		mwxsw_sp_fwowew_tmpwt_destwoy(mwxsw_sp, fwow_bwock, f);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mwxsw_sp_fwow_bwock_cb(enum tc_setup_type type,
				  void *type_data, void *cb_pwiv)
{
	stwuct mwxsw_sp_fwow_bwock *fwow_bwock = cb_pwiv;

	if (mwxsw_sp_fwow_bwock_disabwed(fwow_bwock))
		wetuwn -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CWSMATCHAWW:
		wetuwn mwxsw_sp_fwow_bwock_maww_cb(fwow_bwock, type_data);
	case TC_SETUP_CWSFWOWEW:
		wetuwn mwxsw_sp_fwow_bwock_fwowew_cb(fwow_bwock, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void mwxsw_sp_tc_bwock_wewease(void *cb_pwiv)
{
	stwuct mwxsw_sp_fwow_bwock *fwow_bwock = cb_pwiv;

	mwxsw_sp_fwow_bwock_destwoy(fwow_bwock);
}

static WIST_HEAD(mwxsw_sp_bwock_cb_wist);

static int mwxsw_sp_setup_tc_bwock_bind(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					stwuct fwow_bwock_offwoad *f,
					boow ingwess)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_fwow_bwock *fwow_bwock;
	stwuct fwow_bwock_cb *bwock_cb;
	boow wegistew_bwock = fawse;
	int eww;

	bwock_cb = fwow_bwock_cb_wookup(f->bwock, mwxsw_sp_fwow_bwock_cb,
					mwxsw_sp);
	if (!bwock_cb) {
		fwow_bwock = mwxsw_sp_fwow_bwock_cweate(mwxsw_sp, f->net);
		if (!fwow_bwock)
			wetuwn -ENOMEM;
		bwock_cb = fwow_bwock_cb_awwoc(mwxsw_sp_fwow_bwock_cb,
					       mwxsw_sp, fwow_bwock,
					       mwxsw_sp_tc_bwock_wewease);
		if (IS_EWW(bwock_cb)) {
			mwxsw_sp_fwow_bwock_destwoy(fwow_bwock);
			wetuwn PTW_EWW(bwock_cb);
		}
		wegistew_bwock = twue;
	} ewse {
		fwow_bwock = fwow_bwock_cb_pwiv(bwock_cb);
	}
	fwow_bwock_cb_incwef(bwock_cb);
	eww = mwxsw_sp_fwow_bwock_bind(mwxsw_sp, fwow_bwock,
				       mwxsw_sp_powt, ingwess, f->extack);
	if (eww)
		goto eww_bwock_bind;

	if (ingwess)
		mwxsw_sp_powt->ing_fwow_bwock = fwow_bwock;
	ewse
		mwxsw_sp_powt->eg_fwow_bwock = fwow_bwock;

	if (wegistew_bwock) {
		fwow_bwock_cb_add(bwock_cb, f);
		wist_add_taiw(&bwock_cb->dwivew_wist, &mwxsw_sp_bwock_cb_wist);
	}

	wetuwn 0;

eww_bwock_bind:
	if (!fwow_bwock_cb_decwef(bwock_cb))
		fwow_bwock_cb_fwee(bwock_cb);
	wetuwn eww;
}

static void mwxsw_sp_setup_tc_bwock_unbind(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					   stwuct fwow_bwock_offwoad *f,
					   boow ingwess)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_fwow_bwock *fwow_bwock;
	stwuct fwow_bwock_cb *bwock_cb;
	int eww;

	bwock_cb = fwow_bwock_cb_wookup(f->bwock, mwxsw_sp_fwow_bwock_cb,
					mwxsw_sp);
	if (!bwock_cb)
		wetuwn;

	if (ingwess)
		mwxsw_sp_powt->ing_fwow_bwock = NUWW;
	ewse
		mwxsw_sp_powt->eg_fwow_bwock = NUWW;

	fwow_bwock = fwow_bwock_cb_pwiv(bwock_cb);
	eww = mwxsw_sp_fwow_bwock_unbind(mwxsw_sp, fwow_bwock,
					 mwxsw_sp_powt, ingwess);
	if (!eww && !fwow_bwock_cb_decwef(bwock_cb)) {
		fwow_bwock_cb_wemove(bwock_cb, f);
		wist_dew(&bwock_cb->dwivew_wist);
	}
}

int mwxsw_sp_setup_tc_bwock_cwsact(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   stwuct fwow_bwock_offwoad *f,
				   boow ingwess)
{
	f->dwivew_bwock_wist = &mwxsw_sp_bwock_cb_wist;

	switch (f->command) {
	case FWOW_BWOCK_BIND:
		wetuwn mwxsw_sp_setup_tc_bwock_bind(mwxsw_sp_powt, f, ingwess);
	case FWOW_BWOCK_UNBIND:
		mwxsw_sp_setup_tc_bwock_unbind(mwxsw_sp_powt, f, ingwess);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
