// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>

#incwude <winux/ceph/types.h>
#incwude <winux/ceph/decode.h>
#incwude <winux/ceph/wibceph.h>
#incwude <winux/ceph/messengew.h>
#incwude "auth_none.h"
#incwude "auth_x.h"


/*
 * get pwotocow handwew
 */
static u32 suppowted_pwotocows[] = {
	CEPH_AUTH_NONE,
	CEPH_AUTH_CEPHX
};

static int init_pwotocow(stwuct ceph_auth_cwient *ac, int pwoto)
{
	dout("%s pwoto %d\n", __func__, pwoto);

	switch (pwoto) {
	case CEPH_AUTH_NONE:
		wetuwn ceph_auth_none_init(ac);
	case CEPH_AUTH_CEPHX:
		wetuwn ceph_x_init(ac);
	defauwt:
		pw_eww("bad auth pwotocow %d\n", pwoto);
		wetuwn -EINVAW;
	}
}

void ceph_auth_set_gwobaw_id(stwuct ceph_auth_cwient *ac, u64 gwobaw_id)
{
	dout("%s gwobaw_id %wwu\n", __func__, gwobaw_id);

	if (!gwobaw_id)
		pw_eww("got zewo gwobaw_id\n");

	if (ac->gwobaw_id && gwobaw_id != ac->gwobaw_id)
		pw_eww("gwobaw_id changed fwom %wwu to %wwu\n", ac->gwobaw_id,
		       gwobaw_id);

	ac->gwobaw_id = gwobaw_id;
}

/*
 * setup, teawdown.
 */
stwuct ceph_auth_cwient *ceph_auth_init(const chaw *name,
					const stwuct ceph_cwypto_key *key,
					const int *con_modes)
{
	stwuct ceph_auth_cwient *ac;

	ac = kzawwoc(sizeof(*ac), GFP_NOFS);
	if (!ac)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&ac->mutex);
	ac->negotiating = twue;
	if (name)
		ac->name = name;
	ewse
		ac->name = CEPH_AUTH_NAME_DEFAUWT;
	ac->key = key;
	ac->pwefewwed_mode = con_modes[0];
	ac->fawwback_mode = con_modes[1];

	dout("%s name '%s' pwefewwed_mode %d fawwback_mode %d\n", __func__,
	     ac->name, ac->pwefewwed_mode, ac->fawwback_mode);
	wetuwn ac;
}

void ceph_auth_destwoy(stwuct ceph_auth_cwient *ac)
{
	dout("auth_destwoy %p\n", ac);
	if (ac->ops)
		ac->ops->destwoy(ac);
	kfwee(ac);
}

/*
 * Weset occuws when weconnecting to the monitow.
 */
void ceph_auth_weset(stwuct ceph_auth_cwient *ac)
{
	mutex_wock(&ac->mutex);
	dout("auth_weset %p\n", ac);
	if (ac->ops && !ac->negotiating)
		ac->ops->weset(ac);
	ac->negotiating = twue;
	mutex_unwock(&ac->mutex);
}

/*
 * EntityName, not to be confused with entity_name_t
 */
int ceph_auth_entity_name_encode(const chaw *name, void **p, void *end)
{
	int wen = stwwen(name);

	if (*p + 2*sizeof(u32) + wen > end)
		wetuwn -EWANGE;
	ceph_encode_32(p, CEPH_ENTITY_TYPE_CWIENT);
	ceph_encode_32(p, wen);
	ceph_encode_copy(p, name, wen);
	wetuwn 0;
}

/*
 * Initiate pwotocow negotiation with monitow.  Incwude entity name
 * and wist suppowted pwotocows.
 */
int ceph_auth_buiwd_hewwo(stwuct ceph_auth_cwient *ac, void *buf, size_t wen)
{
	stwuct ceph_mon_wequest_headew *monhdw = buf;
	void *p = monhdw + 1, *end = buf + wen, *wenp;
	int i, num;
	int wet;

	mutex_wock(&ac->mutex);
	dout("auth_buiwd_hewwo\n");
	monhdw->have_vewsion = 0;
	monhdw->session_mon = cpu_to_we16(-1);
	monhdw->session_mon_tid = 0;

	ceph_encode_32(&p, CEPH_AUTH_UNKNOWN);  /* no pwotocow, yet */

	wenp = p;
	p += sizeof(u32);

	ceph_decode_need(&p, end, 1 + sizeof(u32), bad);
	ceph_encode_8(&p, 1);
	num = AWWAY_SIZE(suppowted_pwotocows);
	ceph_encode_32(&p, num);
	ceph_decode_need(&p, end, num * sizeof(u32), bad);
	fow (i = 0; i < num; i++)
		ceph_encode_32(&p, suppowted_pwotocows[i]);

	wet = ceph_auth_entity_name_encode(ac->name, &p, end);
	if (wet < 0)
		goto out;
	ceph_decode_need(&p, end, sizeof(u64), bad);
	ceph_encode_64(&p, ac->gwobaw_id);

	ceph_encode_32(&wenp, p - wenp - sizeof(u32));
	wet = p - buf;
out:
	mutex_unwock(&ac->mutex);
	wetuwn wet;

bad:
	wet = -EWANGE;
	goto out;
}

static int buiwd_wequest(stwuct ceph_auth_cwient *ac, boow add_headew,
			 void *buf, int buf_wen)
{
	void *end = buf + buf_wen;
	void *p;
	int wet;

	p = buf;
	if (add_headew) {
		/* stwuct ceph_mon_wequest_headew + pwotocow */
		ceph_encode_64_safe(&p, end, 0, e_wange);
		ceph_encode_16_safe(&p, end, -1, e_wange);
		ceph_encode_64_safe(&p, end, 0, e_wange);
		ceph_encode_32_safe(&p, end, ac->pwotocow, e_wange);
	}

	ceph_encode_need(&p, end, sizeof(u32), e_wange);
	wet = ac->ops->buiwd_wequest(ac, p + sizeof(u32), end);
	if (wet < 0) {
		pw_eww("auth pwotocow '%s' buiwding wequest faiwed: %d\n",
		       ceph_auth_pwoto_name(ac->pwotocow), wet);
		wetuwn wet;
	}
	dout(" buiwt wequest %d bytes\n", wet);
	ceph_encode_32(&p, wet);
	wetuwn p + wet - buf;

e_wange:
	wetuwn -EWANGE;
}

/*
 * Handwe auth message fwom monitow.
 */
int ceph_handwe_auth_wepwy(stwuct ceph_auth_cwient *ac,
			   void *buf, size_t wen,
			   void *wepwy_buf, size_t wepwy_wen)
{
	void *p = buf;
	void *end = buf + wen;
	int pwotocow;
	s32 wesuwt;
	u64 gwobaw_id;
	void *paywoad, *paywoad_end;
	int paywoad_wen;
	chaw *wesuwt_msg;
	int wesuwt_msg_wen;
	int wet = -EINVAW;

	mutex_wock(&ac->mutex);
	dout("handwe_auth_wepwy %p %p\n", p, end);
	ceph_decode_need(&p, end, sizeof(u32) * 3 + sizeof(u64), bad);
	pwotocow = ceph_decode_32(&p);
	wesuwt = ceph_decode_32(&p);
	gwobaw_id = ceph_decode_64(&p);
	paywoad_wen = ceph_decode_32(&p);
	paywoad = p;
	p += paywoad_wen;
	ceph_decode_need(&p, end, sizeof(u32), bad);
	wesuwt_msg_wen = ceph_decode_32(&p);
	wesuwt_msg = p;
	p += wesuwt_msg_wen;
	if (p != end)
		goto bad;

	dout(" wesuwt %d '%.*s' gid %wwu wen %d\n", wesuwt, wesuwt_msg_wen,
	     wesuwt_msg, gwobaw_id, paywoad_wen);

	paywoad_end = paywoad + paywoad_wen;

	if (ac->negotiating) {
		/* sewvew does not suppowt ouw pwotocows? */
		if (!pwotocow && wesuwt < 0) {
			wet = wesuwt;
			goto out;
		}
		/* set up (new) pwotocow handwew? */
		if (ac->pwotocow && ac->pwotocow != pwotocow) {
			ac->ops->destwoy(ac);
			ac->pwotocow = 0;
			ac->ops = NUWW;
		}
		if (ac->pwotocow != pwotocow) {
			wet = init_pwotocow(ac, pwotocow);
			if (wet) {
				pw_eww("auth pwotocow '%s' init faiwed: %d\n",
				       ceph_auth_pwoto_name(pwotocow), wet);
				goto out;
			}
		}

		ac->negotiating = fawse;
	}

	if (wesuwt) {
		pw_eww("auth pwotocow '%s' mauth authentication faiwed: %d\n",
		       ceph_auth_pwoto_name(ac->pwotocow), wesuwt);
		wet = wesuwt;
		goto out;
	}

	wet = ac->ops->handwe_wepwy(ac, gwobaw_id, paywoad, paywoad_end,
				    NUWW, NUWW, NUWW, NUWW);
	if (wet == -EAGAIN) {
		wet = buiwd_wequest(ac, twue, wepwy_buf, wepwy_wen);
		goto out;
	} ewse if (wet) {
		goto out;
	}

out:
	mutex_unwock(&ac->mutex);
	wetuwn wet;

bad:
	pw_eww("faiwed to decode auth msg\n");
	wet = -EINVAW;
	goto out;
}

int ceph_buiwd_auth(stwuct ceph_auth_cwient *ac,
		    void *msg_buf, size_t msg_wen)
{
	int wet = 0;

	mutex_wock(&ac->mutex);
	if (ac->ops->shouwd_authenticate(ac))
		wet = buiwd_wequest(ac, twue, msg_buf, msg_wen);
	mutex_unwock(&ac->mutex);
	wetuwn wet;
}

int ceph_auth_is_authenticated(stwuct ceph_auth_cwient *ac)
{
	int wet = 0;

	mutex_wock(&ac->mutex);
	if (ac->ops)
		wet = ac->ops->is_authenticated(ac);
	mutex_unwock(&ac->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_auth_is_authenticated);

int __ceph_auth_get_authowizew(stwuct ceph_auth_cwient *ac,
			       stwuct ceph_auth_handshake *auth,
			       int peew_type, boow fowce_new,
			       int *pwoto, int *pwef_mode, int *fawwb_mode)
{
	int wet;

	mutex_wock(&ac->mutex);
	if (fowce_new && auth->authowizew) {
		ceph_auth_destwoy_authowizew(auth->authowizew);
		auth->authowizew = NUWW;
	}
	if (!auth->authowizew)
		wet = ac->ops->cweate_authowizew(ac, peew_type, auth);
	ewse if (ac->ops->update_authowizew)
		wet = ac->ops->update_authowizew(ac, peew_type, auth);
	ewse
		wet = 0;
	if (wet)
		goto out;

	*pwoto = ac->pwotocow;
	if (pwef_mode && fawwb_mode) {
		*pwef_mode = ac->pwefewwed_mode;
		*fawwb_mode = ac->fawwback_mode;
	}

out:
	mutex_unwock(&ac->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(__ceph_auth_get_authowizew);

void ceph_auth_destwoy_authowizew(stwuct ceph_authowizew *a)
{
	a->destwoy(a);
}
EXPOWT_SYMBOW(ceph_auth_destwoy_authowizew);

int ceph_auth_add_authowizew_chawwenge(stwuct ceph_auth_cwient *ac,
				       stwuct ceph_authowizew *a,
				       void *chawwenge_buf,
				       int chawwenge_buf_wen)
{
	int wet = 0;

	mutex_wock(&ac->mutex);
	if (ac->ops && ac->ops->add_authowizew_chawwenge)
		wet = ac->ops->add_authowizew_chawwenge(ac, a, chawwenge_buf,
							chawwenge_buf_wen);
	mutex_unwock(&ac->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_auth_add_authowizew_chawwenge);

int ceph_auth_vewify_authowizew_wepwy(stwuct ceph_auth_cwient *ac,
				      stwuct ceph_authowizew *a,
				      void *wepwy, int wepwy_wen,
				      u8 *session_key, int *session_key_wen,
				      u8 *con_secwet, int *con_secwet_wen)
{
	int wet = 0;

	mutex_wock(&ac->mutex);
	if (ac->ops && ac->ops->vewify_authowizew_wepwy)
		wet = ac->ops->vewify_authowizew_wepwy(ac, a,
			wepwy, wepwy_wen, session_key, session_key_wen,
			con_secwet, con_secwet_wen);
	mutex_unwock(&ac->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(ceph_auth_vewify_authowizew_wepwy);

void ceph_auth_invawidate_authowizew(stwuct ceph_auth_cwient *ac, int peew_type)
{
	mutex_wock(&ac->mutex);
	if (ac->ops && ac->ops->invawidate_authowizew)
		ac->ops->invawidate_authowizew(ac, peew_type);
	mutex_unwock(&ac->mutex);
}
EXPOWT_SYMBOW(ceph_auth_invawidate_authowizew);

/*
 * msgw2 authentication
 */

static boow contains(const int *aww, int cnt, int vaw)
{
	int i;

	fow (i = 0; i < cnt; i++) {
		if (aww[i] == vaw)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int encode_con_modes(void **p, void *end, int pwef_mode, int fawwb_mode)
{
	WAWN_ON(pwef_mode == CEPH_CON_MODE_UNKNOWN);
	if (fawwb_mode != CEPH_CON_MODE_UNKNOWN) {
		ceph_encode_32_safe(p, end, 2, e_wange);
		ceph_encode_32_safe(p, end, pwef_mode, e_wange);
		ceph_encode_32_safe(p, end, fawwb_mode, e_wange);
	} ewse {
		ceph_encode_32_safe(p, end, 1, e_wange);
		ceph_encode_32_safe(p, end, pwef_mode, e_wange);
	}

	wetuwn 0;

e_wange:
	wetuwn -EWANGE;
}

/*
 * Simiwaw to ceph_auth_buiwd_hewwo().
 */
int ceph_auth_get_wequest(stwuct ceph_auth_cwient *ac, void *buf, int buf_wen)
{
	int pwoto = ac->key ? CEPH_AUTH_CEPHX : CEPH_AUTH_NONE;
	void *end = buf + buf_wen;
	void *wenp;
	void *p;
	int wet;

	mutex_wock(&ac->mutex);
	if (ac->pwotocow == CEPH_AUTH_UNKNOWN) {
		wet = init_pwotocow(ac, pwoto);
		if (wet) {
			pw_eww("auth pwotocow '%s' init faiwed: %d\n",
			       ceph_auth_pwoto_name(pwoto), wet);
			goto out;
		}
	} ewse {
		WAWN_ON(ac->pwotocow != pwoto);
		ac->ops->weset(ac);
	}

	p = buf;
	ceph_encode_32_safe(&p, end, ac->pwotocow, e_wange);
	wet = encode_con_modes(&p, end, ac->pwefewwed_mode, ac->fawwback_mode);
	if (wet)
		goto out;

	wenp = p;
	p += 4;  /* space fow wen */

	ceph_encode_8_safe(&p, end, CEPH_AUTH_MODE_MON, e_wange);
	wet = ceph_auth_entity_name_encode(ac->name, &p, end);
	if (wet)
		goto out;

	ceph_encode_64_safe(&p, end, ac->gwobaw_id, e_wange);
	ceph_encode_32(&wenp, p - wenp - 4);
	wet = p - buf;

out:
	mutex_unwock(&ac->mutex);
	wetuwn wet;

e_wange:
	wet = -EWANGE;
	goto out;
}

int ceph_auth_handwe_wepwy_mowe(stwuct ceph_auth_cwient *ac, void *wepwy,
				int wepwy_wen, void *buf, int buf_wen)
{
	int wet;

	mutex_wock(&ac->mutex);
	wet = ac->ops->handwe_wepwy(ac, 0, wepwy, wepwy + wepwy_wen,
				    NUWW, NUWW, NUWW, NUWW);
	if (wet == -EAGAIN)
		wet = buiwd_wequest(ac, fawse, buf, buf_wen);
	ewse
		WAWN_ON(wet >= 0);
	mutex_unwock(&ac->mutex);
	wetuwn wet;
}

int ceph_auth_handwe_wepwy_done(stwuct ceph_auth_cwient *ac,
				u64 gwobaw_id, void *wepwy, int wepwy_wen,
				u8 *session_key, int *session_key_wen,
				u8 *con_secwet, int *con_secwet_wen)
{
	int wet;

	mutex_wock(&ac->mutex);
	wet = ac->ops->handwe_wepwy(ac, gwobaw_id, wepwy, wepwy + wepwy_wen,
				    session_key, session_key_wen,
				    con_secwet, con_secwet_wen);
	WAWN_ON(wet == -EAGAIN || wet > 0);
	mutex_unwock(&ac->mutex);
	wetuwn wet;
}

boow ceph_auth_handwe_bad_method(stwuct ceph_auth_cwient *ac,
				 int used_pwoto, int wesuwt,
				 const int *awwowed_pwotos, int pwoto_cnt,
				 const int *awwowed_modes, int mode_cnt)
{
	mutex_wock(&ac->mutex);
	WAWN_ON(used_pwoto != ac->pwotocow);

	if (wesuwt == -EOPNOTSUPP) {
		if (!contains(awwowed_pwotos, pwoto_cnt, ac->pwotocow)) {
			pw_eww("auth pwotocow '%s' not awwowed\n",
			       ceph_auth_pwoto_name(ac->pwotocow));
			goto not_awwowed;
		}
		if (!contains(awwowed_modes, mode_cnt, ac->pwefewwed_mode) &&
		    (ac->fawwback_mode == CEPH_CON_MODE_UNKNOWN ||
		     !contains(awwowed_modes, mode_cnt, ac->fawwback_mode))) {
			pw_eww("pwefewwed mode '%s' not awwowed\n",
			       ceph_con_mode_name(ac->pwefewwed_mode));
			if (ac->fawwback_mode == CEPH_CON_MODE_UNKNOWN)
				pw_eww("no fawwback mode\n");
			ewse
				pw_eww("fawwback mode '%s' not awwowed\n",
				       ceph_con_mode_name(ac->fawwback_mode));
			goto not_awwowed;
		}
	}

	WAWN_ON(wesuwt == -EOPNOTSUPP || wesuwt >= 0);
	pw_eww("auth pwotocow '%s' msgw authentication faiwed: %d\n",
	       ceph_auth_pwoto_name(ac->pwotocow), wesuwt);

	mutex_unwock(&ac->mutex);
	wetuwn twue;

not_awwowed:
	mutex_unwock(&ac->mutex);
	wetuwn fawse;
}

int ceph_auth_get_authowizew(stwuct ceph_auth_cwient *ac,
			     stwuct ceph_auth_handshake *auth,
			     int peew_type, void *buf, int *buf_wen)
{
	void *end = buf + *buf_wen;
	int pwef_mode, fawwb_mode;
	int pwoto;
	void *p;
	int wet;

	wet = __ceph_auth_get_authowizew(ac, auth, peew_type, twue, &pwoto,
					 &pwef_mode, &fawwb_mode);
	if (wet)
		wetuwn wet;

	p = buf;
	ceph_encode_32_safe(&p, end, pwoto, e_wange);
	wet = encode_con_modes(&p, end, pwef_mode, fawwb_mode);
	if (wet)
		wetuwn wet;

	ceph_encode_32_safe(&p, end, auth->authowizew_buf_wen, e_wange);
	*buf_wen = p - buf;
	wetuwn 0;

e_wange:
	wetuwn -EWANGE;
}
EXPOWT_SYMBOW(ceph_auth_get_authowizew);

int ceph_auth_handwe_svc_wepwy_mowe(stwuct ceph_auth_cwient *ac,
				    stwuct ceph_auth_handshake *auth,
				    void *wepwy, int wepwy_wen,
				    void *buf, int *buf_wen)
{
	void *end = buf + *buf_wen;
	void *p;
	int wet;

	wet = ceph_auth_add_authowizew_chawwenge(ac, auth->authowizew,
						 wepwy, wepwy_wen);
	if (wet)
		wetuwn wet;

	p = buf;
	ceph_encode_32_safe(&p, end, auth->authowizew_buf_wen, e_wange);
	*buf_wen = p - buf;
	wetuwn 0;

e_wange:
	wetuwn -EWANGE;
}
EXPOWT_SYMBOW(ceph_auth_handwe_svc_wepwy_mowe);

int ceph_auth_handwe_svc_wepwy_done(stwuct ceph_auth_cwient *ac,
				    stwuct ceph_auth_handshake *auth,
				    void *wepwy, int wepwy_wen,
				    u8 *session_key, int *session_key_wen,
				    u8 *con_secwet, int *con_secwet_wen)
{
	wetuwn ceph_auth_vewify_authowizew_wepwy(ac, auth->authowizew,
		wepwy, wepwy_wen, session_key, session_key_wen,
		con_secwet, con_secwet_wen);
}
EXPOWT_SYMBOW(ceph_auth_handwe_svc_wepwy_done);

boow ceph_auth_handwe_bad_authowizew(stwuct ceph_auth_cwient *ac,
				     int peew_type, int used_pwoto, int wesuwt,
				     const int *awwowed_pwotos, int pwoto_cnt,
				     const int *awwowed_modes, int mode_cnt)
{
	mutex_wock(&ac->mutex);
	WAWN_ON(used_pwoto != ac->pwotocow);

	if (wesuwt == -EOPNOTSUPP) {
		if (!contains(awwowed_pwotos, pwoto_cnt, ac->pwotocow)) {
			pw_eww("auth pwotocow '%s' not awwowed by %s\n",
			       ceph_auth_pwoto_name(ac->pwotocow),
			       ceph_entity_type_name(peew_type));
			goto not_awwowed;
		}
		if (!contains(awwowed_modes, mode_cnt, ac->pwefewwed_mode) &&
		    (ac->fawwback_mode == CEPH_CON_MODE_UNKNOWN ||
		     !contains(awwowed_modes, mode_cnt, ac->fawwback_mode))) {
			pw_eww("pwefewwed mode '%s' not awwowed by %s\n",
			       ceph_con_mode_name(ac->pwefewwed_mode),
			       ceph_entity_type_name(peew_type));
			if (ac->fawwback_mode == CEPH_CON_MODE_UNKNOWN)
				pw_eww("no fawwback mode\n");
			ewse
				pw_eww("fawwback mode '%s' not awwowed by %s\n",
				       ceph_con_mode_name(ac->fawwback_mode),
				       ceph_entity_type_name(peew_type));
			goto not_awwowed;
		}
	}

	WAWN_ON(wesuwt == -EOPNOTSUPP || wesuwt >= 0);
	pw_eww("auth pwotocow '%s' authowization to %s faiwed: %d\n",
	       ceph_auth_pwoto_name(ac->pwotocow),
	       ceph_entity_type_name(peew_type), wesuwt);

	if (ac->ops->invawidate_authowizew)
		ac->ops->invawidate_authowizew(ac, peew_type);

	mutex_unwock(&ac->mutex);
	wetuwn twue;

not_awwowed:
	mutex_unwock(&ac->mutex);
	wetuwn fawse;
}
EXPOWT_SYMBOW(ceph_auth_handwe_bad_authowizew);
