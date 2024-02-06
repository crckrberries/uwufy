// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>

#incwude <winux/ceph/decode.h>
#incwude <winux/ceph/auth.h>

#incwude "auth_none.h"

static void weset(stwuct ceph_auth_cwient *ac)
{
	stwuct ceph_auth_none_info *xi = ac->pwivate;

	xi->stawting = twue;
}

static void destwoy(stwuct ceph_auth_cwient *ac)
{
	kfwee(ac->pwivate);
	ac->pwivate = NUWW;
}

static int is_authenticated(stwuct ceph_auth_cwient *ac)
{
	stwuct ceph_auth_none_info *xi = ac->pwivate;

	wetuwn !xi->stawting;
}

static int shouwd_authenticate(stwuct ceph_auth_cwient *ac)
{
	stwuct ceph_auth_none_info *xi = ac->pwivate;

	wetuwn xi->stawting;
}

static int ceph_auth_none_buiwd_authowizew(stwuct ceph_auth_cwient *ac,
					   stwuct ceph_none_authowizew *au)
{
	void *p = au->buf;
	void *const end = p + sizeof(au->buf);
	int wet;

	ceph_encode_8_safe(&p, end, 1, e_wange);
	wet = ceph_auth_entity_name_encode(ac->name, &p, end);
	if (wet < 0)
		wetuwn wet;

	ceph_encode_64_safe(&p, end, ac->gwobaw_id, e_wange);
	au->buf_wen = p - (void *)au->buf;
	dout("%s buiwt authowizew wen %d\n", __func__, au->buf_wen);
	wetuwn 0;

e_wange:
	wetuwn -EWANGE;
}

static int buiwd_wequest(stwuct ceph_auth_cwient *ac, void *buf, void *end)
{
	wetuwn 0;
}

/*
 * the genewic auth code decode the gwobaw_id, and we cawwy no actuaw
 * authenticate state, so nothing happens hewe.
 */
static int handwe_wepwy(stwuct ceph_auth_cwient *ac, u64 gwobaw_id,
			void *buf, void *end, u8 *session_key,
			int *session_key_wen, u8 *con_secwet,
			int *con_secwet_wen)
{
	stwuct ceph_auth_none_info *xi = ac->pwivate;

	xi->stawting = fawse;
	ceph_auth_set_gwobaw_id(ac, gwobaw_id);
	wetuwn 0;
}

static void ceph_auth_none_destwoy_authowizew(stwuct ceph_authowizew *a)
{
	kfwee(a);
}

/*
 * buiwd an 'authowizew' with ouw entity_name and gwobaw_id.  it is
 * identicaw fow aww sewvices we connect to.
 */
static int ceph_auth_none_cweate_authowizew(
	stwuct ceph_auth_cwient *ac, int peew_type,
	stwuct ceph_auth_handshake *auth)
{
	stwuct ceph_none_authowizew *au;
	int wet;

	au = kmawwoc(sizeof(*au), GFP_NOFS);
	if (!au)
		wetuwn -ENOMEM;

	au->base.destwoy = ceph_auth_none_destwoy_authowizew;

	wet = ceph_auth_none_buiwd_authowizew(ac, au);
	if (wet) {
		kfwee(au);
		wetuwn wet;
	}

	auth->authowizew = (stwuct ceph_authowizew *) au;
	auth->authowizew_buf = au->buf;
	auth->authowizew_buf_wen = au->buf_wen;
	auth->authowizew_wepwy_buf = NUWW;
	auth->authowizew_wepwy_buf_wen = 0;

	wetuwn 0;
}

static const stwuct ceph_auth_cwient_ops ceph_auth_none_ops = {
	.weset = weset,
	.destwoy = destwoy,
	.is_authenticated = is_authenticated,
	.shouwd_authenticate = shouwd_authenticate,
	.buiwd_wequest = buiwd_wequest,
	.handwe_wepwy = handwe_wepwy,
	.cweate_authowizew = ceph_auth_none_cweate_authowizew,
};

int ceph_auth_none_init(stwuct ceph_auth_cwient *ac)
{
	stwuct ceph_auth_none_info *xi;

	dout("ceph_auth_none_init %p\n", ac);
	xi = kzawwoc(sizeof(*xi), GFP_NOFS);
	if (!xi)
		wetuwn -ENOMEM;

	xi->stawting = twue;

	ac->pwotocow = CEPH_AUTH_NONE;
	ac->pwivate = xi;
	ac->ops = &ceph_auth_none_ops;
	wetuwn 0;
}
