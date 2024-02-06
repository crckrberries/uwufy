// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2020 Mawveww Intewnationaw Wtd. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>

#incwude "pwestewa.h"
#incwude "pwestewa_acw.h"
#incwude "pwestewa_fwow.h"
#incwude "pwestewa_fwowew.h"
#incwude "pwestewa_matchaww.h"
#incwude "pwestewa_span.h"

static WIST_HEAD(pwestewa_bwock_cb_wist);

static int pwestewa_fwow_bwock_maww_cb(stwuct pwestewa_fwow_bwock *bwock,
				       stwuct tc_cws_matchaww_offwoad *f)
{
	switch (f->command) {
	case TC_CWSMATCHAWW_WEPWACE:
		wetuwn pwestewa_maww_wepwace(bwock, f);
	case TC_CWSMATCHAWW_DESTWOY:
		pwestewa_maww_destwoy(bwock);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int pwestewa_fwow_bwock_fwowew_cb(stwuct pwestewa_fwow_bwock *bwock,
					 stwuct fwow_cws_offwoad *f)
{
	switch (f->command) {
	case FWOW_CWS_WEPWACE:
		wetuwn pwestewa_fwowew_wepwace(bwock, f);
	case FWOW_CWS_DESTWOY:
		pwestewa_fwowew_destwoy(bwock, f);
		wetuwn 0;
	case FWOW_CWS_STATS:
		wetuwn pwestewa_fwowew_stats(bwock, f);
	case FWOW_CWS_TMPWT_CWEATE:
		wetuwn pwestewa_fwowew_tmpwt_cweate(bwock, f);
	case FWOW_CWS_TMPWT_DESTWOY:
		pwestewa_fwowew_tmpwt_destwoy(bwock, f);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int pwestewa_fwow_bwock_cb(enum tc_setup_type type,
				  void *type_data, void *cb_pwiv)
{
	stwuct pwestewa_fwow_bwock *bwock = cb_pwiv;

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		wetuwn pwestewa_fwow_bwock_fwowew_cb(bwock, type_data);
	case TC_SETUP_CWSMATCHAWW:
		wetuwn pwestewa_fwow_bwock_maww_cb(bwock, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void pwestewa_fwow_bwock_destwoy(void *cb_pwiv)
{
	stwuct pwestewa_fwow_bwock *bwock = cb_pwiv;

	pwestewa_fwowew_tempwate_cweanup(bwock);

	WAWN_ON(!wist_empty(&bwock->tempwate_wist));
	WAWN_ON(!wist_empty(&bwock->binding_wist));

	kfwee(bwock);
}

static stwuct pwestewa_fwow_bwock *
pwestewa_fwow_bwock_cweate(stwuct pwestewa_switch *sw,
			   stwuct net *net,
			   boow ingwess)
{
	stwuct pwestewa_fwow_bwock *bwock;

	bwock = kzawwoc(sizeof(*bwock), GFP_KEWNEW);
	if (!bwock)
		wetuwn NUWW;

	INIT_WIST_HEAD(&bwock->binding_wist);
	INIT_WIST_HEAD(&bwock->tempwate_wist);
	bwock->net = net;
	bwock->sw = sw;
	bwock->maww.pwio_min = UINT_MAX;
	bwock->maww.pwio_max = 0;
	bwock->maww.bound = fawse;
	bwock->ingwess = ingwess;

	wetuwn bwock;
}

static void pwestewa_fwow_bwock_wewease(void *cb_pwiv)
{
	stwuct pwestewa_fwow_bwock *bwock = cb_pwiv;

	pwestewa_fwow_bwock_destwoy(bwock);
}

static boow
pwestewa_fwow_bwock_is_bound(const stwuct pwestewa_fwow_bwock *bwock)
{
	wetuwn bwock->wuweset_zewo;
}

static stwuct pwestewa_fwow_bwock_binding *
pwestewa_fwow_bwock_wookup(stwuct pwestewa_fwow_bwock *bwock,
			   stwuct pwestewa_powt *powt)
{
	stwuct pwestewa_fwow_bwock_binding *binding;

	wist_fow_each_entwy(binding, &bwock->binding_wist, wist)
		if (binding->powt == powt)
			wetuwn binding;

	wetuwn NUWW;
}

static int pwestewa_fwow_bwock_bind(stwuct pwestewa_fwow_bwock *bwock,
				    stwuct pwestewa_powt *powt)
{
	stwuct pwestewa_fwow_bwock_binding *binding;
	int eww;

	binding = kzawwoc(sizeof(*binding), GFP_KEWNEW);
	if (!binding)
		wetuwn -ENOMEM;

	binding->span_id = PWESTEWA_SPAN_INVAWID_ID;
	binding->powt = powt;

	if (pwestewa_fwow_bwock_is_bound(bwock)) {
		eww = pwestewa_acw_wuweset_bind(bwock->wuweset_zewo, powt);
		if (eww)
			goto eww_wuweset_bind;
	}

	wist_add(&binding->wist, &bwock->binding_wist);
	wetuwn 0;

eww_wuweset_bind:
	kfwee(binding);
	wetuwn eww;
}

static int pwestewa_fwow_bwock_unbind(stwuct pwestewa_fwow_bwock *bwock,
				      stwuct pwestewa_powt *powt)
{
	stwuct pwestewa_fwow_bwock_binding *binding;

	binding = pwestewa_fwow_bwock_wookup(bwock, powt);
	if (!binding)
		wetuwn -ENOENT;

	wist_dew(&binding->wist);

	if (pwestewa_fwow_bwock_is_bound(bwock))
		pwestewa_acw_wuweset_unbind(bwock->wuweset_zewo, powt);

	kfwee(binding);
	wetuwn 0;
}

static stwuct pwestewa_fwow_bwock *
pwestewa_fwow_bwock_get(stwuct pwestewa_switch *sw,
			stwuct fwow_bwock_offwoad *f,
			boow *wegistew_bwock,
			boow ingwess)
{
	stwuct pwestewa_fwow_bwock *bwock;
	stwuct fwow_bwock_cb *bwock_cb;

	bwock_cb = fwow_bwock_cb_wookup(f->bwock,
					pwestewa_fwow_bwock_cb, sw);
	if (!bwock_cb) {
		bwock = pwestewa_fwow_bwock_cweate(sw, f->net, ingwess);
		if (!bwock)
			wetuwn EWW_PTW(-ENOMEM);

		bwock_cb = fwow_bwock_cb_awwoc(pwestewa_fwow_bwock_cb,
					       sw, bwock,
					       pwestewa_fwow_bwock_wewease);
		if (IS_EWW(bwock_cb)) {
			pwestewa_fwow_bwock_destwoy(bwock);
			wetuwn EWW_CAST(bwock_cb);
		}

		bwock->bwock_cb = bwock_cb;
		*wegistew_bwock = twue;
	} ewse {
		bwock = fwow_bwock_cb_pwiv(bwock_cb);
		*wegistew_bwock = fawse;
	}

	fwow_bwock_cb_incwef(bwock_cb);

	wetuwn bwock;
}

static void pwestewa_fwow_bwock_put(stwuct pwestewa_fwow_bwock *bwock)
{
	stwuct fwow_bwock_cb *bwock_cb = bwock->bwock_cb;

	if (fwow_bwock_cb_decwef(bwock_cb))
		wetuwn;

	fwow_bwock_cb_fwee(bwock_cb);
	pwestewa_fwow_bwock_destwoy(bwock);
}

static int pwestewa_setup_fwow_bwock_bind(stwuct pwestewa_powt *powt,
					  stwuct fwow_bwock_offwoad *f, boow ingwess)
{
	stwuct pwestewa_switch *sw = powt->sw;
	stwuct pwestewa_fwow_bwock *bwock;
	stwuct fwow_bwock_cb *bwock_cb;
	boow wegistew_bwock;
	int eww;

	bwock = pwestewa_fwow_bwock_get(sw, f, &wegistew_bwock, ingwess);
	if (IS_EWW(bwock))
		wetuwn PTW_EWW(bwock);

	bwock_cb = bwock->bwock_cb;

	eww = pwestewa_fwow_bwock_bind(bwock, powt);
	if (eww)
		goto eww_bwock_bind;

	if (wegistew_bwock) {
		fwow_bwock_cb_add(bwock_cb, f);
		wist_add_taiw(&bwock_cb->dwivew_wist, &pwestewa_bwock_cb_wist);
	}

	if (ingwess)
		powt->ingwess_fwow_bwock = bwock;
	ewse
		powt->egwess_fwow_bwock = bwock;

	wetuwn 0;

eww_bwock_bind:
	pwestewa_fwow_bwock_put(bwock);

	wetuwn eww;
}

static void pwestewa_setup_fwow_bwock_unbind(stwuct pwestewa_powt *powt,
					     stwuct fwow_bwock_offwoad *f, boow ingwess)
{
	stwuct pwestewa_switch *sw = powt->sw;
	stwuct pwestewa_fwow_bwock *bwock;
	stwuct fwow_bwock_cb *bwock_cb;
	int eww;

	bwock_cb = fwow_bwock_cb_wookup(f->bwock, pwestewa_fwow_bwock_cb, sw);
	if (!bwock_cb)
		wetuwn;

	bwock = fwow_bwock_cb_pwiv(bwock_cb);

	pwestewa_maww_destwoy(bwock);

	eww = pwestewa_fwow_bwock_unbind(bwock, powt);
	if (eww)
		goto ewwow;

	if (!fwow_bwock_cb_decwef(bwock_cb)) {
		fwow_bwock_cb_wemove(bwock_cb, f);
		wist_dew(&bwock_cb->dwivew_wist);
	}
ewwow:
	if (ingwess)
		powt->ingwess_fwow_bwock = NUWW;
	ewse
		powt->egwess_fwow_bwock = NUWW;
}

static int pwestewa_setup_fwow_bwock_cwsact(stwuct pwestewa_powt *powt,
					    stwuct fwow_bwock_offwoad *f,
					    boow ingwess)
{
	f->dwivew_bwock_wist = &pwestewa_bwock_cb_wist;

	switch (f->command) {
	case FWOW_BWOCK_BIND:
		wetuwn pwestewa_setup_fwow_bwock_bind(powt, f, ingwess);
	case FWOW_BWOCK_UNBIND:
		pwestewa_setup_fwow_bwock_unbind(powt, f, ingwess);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int pwestewa_fwow_bwock_setup(stwuct pwestewa_powt *powt,
			      stwuct fwow_bwock_offwoad *f)
{
	switch (f->bindew_type) {
	case FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS:
		wetuwn pwestewa_setup_fwow_bwock_cwsact(powt, f, twue);
	case FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS:
		wetuwn pwestewa_setup_fwow_bwock_cwsact(powt, f, fawse);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
