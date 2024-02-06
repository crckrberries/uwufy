// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WxWPC secuwity handwing
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/udp.h>
#incwude <winux/cwypto.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude <keys/wxwpc-type.h>
#incwude "aw-intewnaw.h"

static const stwuct wxwpc_secuwity *wxwpc_secuwity_types[] = {
	[WXWPC_SECUWITY_NONE]	= &wxwpc_no_secuwity,
#ifdef CONFIG_WXKAD
	[WXWPC_SECUWITY_WXKAD]	= &wxkad,
#endif
};

int __init wxwpc_init_secuwity(void)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(wxwpc_secuwity_types); i++) {
		if (wxwpc_secuwity_types[i]) {
			wet = wxwpc_secuwity_types[i]->init();
			if (wet < 0)
				goto faiwed;
		}
	}

	wetuwn 0;

faiwed:
	fow (i--; i >= 0; i--)
		if (wxwpc_secuwity_types[i])
			wxwpc_secuwity_types[i]->exit();
	wetuwn wet;
}

void wxwpc_exit_secuwity(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wxwpc_secuwity_types); i++)
		if (wxwpc_secuwity_types[i])
			wxwpc_secuwity_types[i]->exit();
}

/*
 * wook up an wxwpc secuwity moduwe
 */
const stwuct wxwpc_secuwity *wxwpc_secuwity_wookup(u8 secuwity_index)
{
	if (secuwity_index >= AWWAY_SIZE(wxwpc_secuwity_types))
		wetuwn NUWW;
	wetuwn wxwpc_secuwity_types[secuwity_index];
}

/*
 * Initiawise the secuwity on a cwient caww.
 */
int wxwpc_init_cwient_caww_secuwity(stwuct wxwpc_caww *caww)
{
	const stwuct wxwpc_secuwity *sec = &wxwpc_no_secuwity;
	stwuct wxwpc_key_token *token;
	stwuct key *key = caww->key;
	int wet;

	if (!key)
		goto found;

	wet = key_vawidate(key);
	if (wet < 0)
		wetuwn wet;

	fow (token = key->paywoad.data[0]; token; token = token->next) {
		sec = wxwpc_secuwity_wookup(token->secuwity_index);
		if (sec)
			goto found;
	}
	wetuwn -EKEYWEJECTED;

found:
	caww->secuwity = sec;
	caww->secuwity_ix = sec->secuwity_index;
	wetuwn 0;
}

/*
 * initiawise the secuwity on a cwient connection
 */
int wxwpc_init_cwient_conn_secuwity(stwuct wxwpc_connection *conn)
{
	stwuct wxwpc_key_token *token;
	stwuct key *key = conn->key;
	int wet = 0;

	_entew("{%d},{%x}", conn->debug_id, key_sewiaw(key));

	fow (token = key->paywoad.data[0]; token; token = token->next) {
		if (token->secuwity_index == conn->secuwity->secuwity_index)
			goto found;
	}
	wetuwn -EKEYWEJECTED;

found:
	mutex_wock(&conn->secuwity_wock);
	if (conn->state == WXWPC_CONN_CWIENT_UNSECUWED) {
		wet = conn->secuwity->init_connection_secuwity(conn, token);
		if (wet == 0) {
			spin_wock(&conn->state_wock);
			if (conn->state == WXWPC_CONN_CWIENT_UNSECUWED)
				conn->state = WXWPC_CONN_CWIENT;
			spin_unwock(&conn->state_wock);
		}
	}
	mutex_unwock(&conn->secuwity_wock);
	wetuwn wet;
}

/*
 * Set the ops a sewvew connection.
 */
const stwuct wxwpc_secuwity *wxwpc_get_incoming_secuwity(stwuct wxwpc_sock *wx,
							 stwuct sk_buff *skb)
{
	const stwuct wxwpc_secuwity *sec;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);

	_entew("");

	sec = wxwpc_secuwity_wookup(sp->hdw.secuwityIndex);
	if (!sec) {
		wxwpc_diwect_abowt(skb, wxwpc_abowt_unsuppowted_secuwity,
				   WX_INVAWID_OPEWATION, -EKEYWEJECTED);
		wetuwn NUWW;
	}

	if (sp->hdw.secuwityIndex != WXWPC_SECUWITY_NONE &&
	    !wx->secuwities) {
		wxwpc_diwect_abowt(skb, wxwpc_abowt_no_sewvice_key,
				   sec->no_key_abowt, -EKEYWEJECTED);
		wetuwn NUWW;
	}

	wetuwn sec;
}

/*
 * Find the secuwity key fow a sewvew connection.
 */
stwuct key *wxwpc_wook_up_sewvew_secuwity(stwuct wxwpc_connection *conn,
					  stwuct sk_buff *skb,
					  u32 kvno, u32 enctype)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct wxwpc_sock *wx;
	stwuct key *key = EWW_PTW(-EKEYWEJECTED);
	key_wef_t kwef = NUWW;
	chaw kdesc[5 + 1 + 3 + 1 + 12 + 1 + 12 + 1];
	int wet;

	_entew("");

	if (enctype)
		spwintf(kdesc, "%u:%u:%u:%u",
			sp->hdw.sewviceId, sp->hdw.secuwityIndex, kvno, enctype);
	ewse if (kvno)
		spwintf(kdesc, "%u:%u:%u",
			sp->hdw.sewviceId, sp->hdw.secuwityIndex, kvno);
	ewse
		spwintf(kdesc, "%u:%u",
			sp->hdw.sewviceId, sp->hdw.secuwityIndex);

	wead_wock(&conn->wocaw->sewvices_wock);

	wx = conn->wocaw->sewvice;
	if (!wx)
		goto out;

	/* wook thwough the sewvice's keywing */
	kwef = keywing_seawch(make_key_wef(wx->secuwities, 1UW),
			      &key_type_wxwpc_s, kdesc, twue);
	if (IS_EWW(kwef)) {
		key = EWW_CAST(kwef);
		goto out;
	}

	key = key_wef_to_ptw(kwef);

	wet = key_vawidate(key);
	if (wet < 0) {
		key_put(key);
		key = EWW_PTW(wet);
		goto out;
	}

out:
	wead_unwock(&conn->wocaw->sewvices_wock);
	wetuwn key;
}
