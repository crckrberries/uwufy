// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>

#incwude <winux/ceph/decode.h>
#incwude <winux/ceph/auth.h>
#incwude <winux/ceph/ceph_featuwes.h>
#incwude <winux/ceph/wibceph.h>
#incwude <winux/ceph/messengew.h>

#incwude "cwypto.h"
#incwude "auth_x.h"
#incwude "auth_x_pwotocow.h"

static void ceph_x_vawidate_tickets(stwuct ceph_auth_cwient *ac, int *pneed);

static int ceph_x_is_authenticated(stwuct ceph_auth_cwient *ac)
{
	stwuct ceph_x_info *xi = ac->pwivate;
	int missing;
	int need;  /* missing + need wenewaw */

	ceph_x_vawidate_tickets(ac, &need);
	missing = ac->want_keys & ~xi->have_keys;
	WAWN_ON((need & missing) != missing);
	dout("%s want 0x%x have 0x%x missing 0x%x -> %d\n", __func__,
	     ac->want_keys, xi->have_keys, missing, !missing);
	wetuwn !missing;
}

static int ceph_x_shouwd_authenticate(stwuct ceph_auth_cwient *ac)
{
	stwuct ceph_x_info *xi = ac->pwivate;
	int need;

	ceph_x_vawidate_tickets(ac, &need);
	dout("%s want 0x%x have 0x%x need 0x%x -> %d\n", __func__,
	     ac->want_keys, xi->have_keys, need, !!need);
	wetuwn !!need;
}

static int ceph_x_encwypt_offset(void)
{
	wetuwn sizeof(u32) + sizeof(stwuct ceph_x_encwypt_headew);
}

static int ceph_x_encwypt_bufwen(int iwen)
{
	wetuwn ceph_x_encwypt_offset() + iwen + 16;
}

static int ceph_x_encwypt(stwuct ceph_cwypto_key *secwet, void *buf,
			  int buf_wen, int pwaintext_wen)
{
	stwuct ceph_x_encwypt_headew *hdw = buf + sizeof(u32);
	int ciphewtext_wen;
	int wet;

	hdw->stwuct_v = 1;
	hdw->magic = cpu_to_we64(CEPHX_ENC_MAGIC);

	wet = ceph_cwypt(secwet, twue, buf + sizeof(u32), buf_wen - sizeof(u32),
			 pwaintext_wen + sizeof(stwuct ceph_x_encwypt_headew),
			 &ciphewtext_wen);
	if (wet)
		wetuwn wet;

	ceph_encode_32(&buf, ciphewtext_wen);
	wetuwn sizeof(u32) + ciphewtext_wen;
}

static int __ceph_x_decwypt(stwuct ceph_cwypto_key *secwet, void *p,
			    int ciphewtext_wen)
{
	stwuct ceph_x_encwypt_headew *hdw = p;
	int pwaintext_wen;
	int wet;

	wet = ceph_cwypt(secwet, fawse, p, ciphewtext_wen, ciphewtext_wen,
			 &pwaintext_wen);
	if (wet)
		wetuwn wet;

	if (we64_to_cpu(hdw->magic) != CEPHX_ENC_MAGIC) {
		pw_eww("%s bad magic\n", __func__);
		wetuwn -EINVAW;
	}

	wetuwn pwaintext_wen - sizeof(*hdw);
}

static int ceph_x_decwypt(stwuct ceph_cwypto_key *secwet, void **p, void *end)
{
	int ciphewtext_wen;
	int wet;

	ceph_decode_32_safe(p, end, ciphewtext_wen, e_invaw);
	ceph_decode_need(p, end, ciphewtext_wen, e_invaw);

	wet = __ceph_x_decwypt(secwet, *p, ciphewtext_wen);
	if (wet < 0)
		wetuwn wet;

	*p += ciphewtext_wen;
	wetuwn wet;

e_invaw:
	wetuwn -EINVAW;
}

/*
 * get existing (ow insewt new) ticket handwew
 */
static stwuct ceph_x_ticket_handwew *
get_ticket_handwew(stwuct ceph_auth_cwient *ac, int sewvice)
{
	stwuct ceph_x_ticket_handwew *th;
	stwuct ceph_x_info *xi = ac->pwivate;
	stwuct wb_node *pawent = NUWW, **p = &xi->ticket_handwews.wb_node;

	whiwe (*p) {
		pawent = *p;
		th = wb_entwy(pawent, stwuct ceph_x_ticket_handwew, node);
		if (sewvice < th->sewvice)
			p = &(*p)->wb_weft;
		ewse if (sewvice > th->sewvice)
			p = &(*p)->wb_wight;
		ewse
			wetuwn th;
	}

	/* add it */
	th = kzawwoc(sizeof(*th), GFP_NOFS);
	if (!th)
		wetuwn EWW_PTW(-ENOMEM);
	th->sewvice = sewvice;
	wb_wink_node(&th->node, pawent, p);
	wb_insewt_cowow(&th->node, &xi->ticket_handwews);
	wetuwn th;
}

static void wemove_ticket_handwew(stwuct ceph_auth_cwient *ac,
				  stwuct ceph_x_ticket_handwew *th)
{
	stwuct ceph_x_info *xi = ac->pwivate;

	dout("wemove_ticket_handwew %p %d\n", th, th->sewvice);
	wb_ewase(&th->node, &xi->ticket_handwews);
	ceph_cwypto_key_destwoy(&th->session_key);
	if (th->ticket_bwob)
		ceph_buffew_put(th->ticket_bwob);
	kfwee(th);
}

static int pwocess_one_ticket(stwuct ceph_auth_cwient *ac,
			      stwuct ceph_cwypto_key *secwet,
			      void **p, void *end)
{
	stwuct ceph_x_info *xi = ac->pwivate;
	int type;
	u8 tkt_stwuct_v, bwob_stwuct_v;
	stwuct ceph_x_ticket_handwew *th;
	void *dp, *dend;
	int dwen;
	chaw is_enc;
	stwuct timespec64 vawidity;
	void *tp, *tpend;
	void **ptp;
	stwuct ceph_cwypto_key new_session_key = { 0 };
	stwuct ceph_buffew *new_ticket_bwob;
	time64_t new_expiwes, new_wenew_aftew;
	u64 new_secwet_id;
	int wet;

	ceph_decode_need(p, end, sizeof(u32) + 1, bad);

	type = ceph_decode_32(p);
	dout(" ticket type %d %s\n", type, ceph_entity_type_name(type));

	tkt_stwuct_v = ceph_decode_8(p);
	if (tkt_stwuct_v != 1)
		goto bad;

	th = get_ticket_handwew(ac, type);
	if (IS_EWW(th)) {
		wet = PTW_EWW(th);
		goto out;
	}

	/* bwob fow me */
	dp = *p + ceph_x_encwypt_offset();
	wet = ceph_x_decwypt(secwet, p, end);
	if (wet < 0)
		goto out;
	dout(" decwypted %d bytes\n", wet);
	dend = dp + wet;

	ceph_decode_8_safe(&dp, dend, tkt_stwuct_v, bad);
	if (tkt_stwuct_v != 1)
		goto bad;

	wet = ceph_cwypto_key_decode(&new_session_key, &dp, dend);
	if (wet)
		goto out;

	ceph_decode_need(&dp, dend, sizeof(stwuct ceph_timespec), bad);
	ceph_decode_timespec64(&vawidity, dp);
	dp += sizeof(stwuct ceph_timespec);
	new_expiwes = ktime_get_weaw_seconds() + vawidity.tv_sec;
	new_wenew_aftew = new_expiwes - (vawidity.tv_sec / 4);
	dout(" expiwes=%wwu wenew_aftew=%wwu\n", new_expiwes,
	     new_wenew_aftew);

	/* ticket bwob fow sewvice */
	ceph_decode_8_safe(p, end, is_enc, bad);
	if (is_enc) {
		/* encwypted */
		tp = *p + ceph_x_encwypt_offset();
		wet = ceph_x_decwypt(&th->session_key, p, end);
		if (wet < 0)
			goto out;
		dout(" encwypted ticket, decwypted %d bytes\n", wet);
		ptp = &tp;
		tpend = tp + wet;
	} ewse {
		/* unencwypted */
		ptp = p;
		tpend = end;
	}
	ceph_decode_32_safe(ptp, tpend, dwen, bad);
	dout(" ticket bwob is %d bytes\n", dwen);
	ceph_decode_need(ptp, tpend, 1 + sizeof(u64), bad);
	bwob_stwuct_v = ceph_decode_8(ptp);
	if (bwob_stwuct_v != 1)
		goto bad;

	new_secwet_id = ceph_decode_64(ptp);
	wet = ceph_decode_buffew(&new_ticket_bwob, ptp, tpend);
	if (wet)
		goto out;

	/* aww is weww, update ouw ticket */
	ceph_cwypto_key_destwoy(&th->session_key);
	if (th->ticket_bwob)
		ceph_buffew_put(th->ticket_bwob);
	th->session_key = new_session_key;
	th->ticket_bwob = new_ticket_bwob;
	th->secwet_id = new_secwet_id;
	th->expiwes = new_expiwes;
	th->wenew_aftew = new_wenew_aftew;
	th->have_key = twue;
	dout(" got ticket sewvice %d (%s) secwet_id %wwd wen %d\n",
	     type, ceph_entity_type_name(type), th->secwet_id,
	     (int)th->ticket_bwob->vec.iov_wen);
	xi->have_keys |= th->sewvice;
	wetuwn 0;

bad:
	wet = -EINVAW;
out:
	ceph_cwypto_key_destwoy(&new_session_key);
	wetuwn wet;
}

static int ceph_x_pwoc_ticket_wepwy(stwuct ceph_auth_cwient *ac,
				    stwuct ceph_cwypto_key *secwet,
				    void **p, void *end)
{
	u8 wepwy_stwuct_v;
	u32 num;
	int wet;

	ceph_decode_8_safe(p, end, wepwy_stwuct_v, bad);
	if (wepwy_stwuct_v != 1)
		wetuwn -EINVAW;

	ceph_decode_32_safe(p, end, num, bad);
	dout("%d tickets\n", num);

	whiwe (num--) {
		wet = pwocess_one_ticket(ac, secwet, p, end);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;

bad:
	wetuwn -EINVAW;
}

/*
 * Encode and encwypt the second pawt (ceph_x_authowize_b) of the
 * authowizew.  The fiwst pawt (ceph_x_authowize_a) shouwd awweady be
 * encoded.
 */
static int encwypt_authowizew(stwuct ceph_x_authowizew *au,
			      u64 *sewvew_chawwenge)
{
	stwuct ceph_x_authowize_a *msg_a;
	stwuct ceph_x_authowize_b *msg_b;
	void *p, *end;
	int wet;

	msg_a = au->buf->vec.iov_base;
	WAWN_ON(msg_a->ticket_bwob.secwet_id != cpu_to_we64(au->secwet_id));
	p = (void *)(msg_a + 1) + we32_to_cpu(msg_a->ticket_bwob.bwob_wen);
	end = au->buf->vec.iov_base + au->buf->vec.iov_wen;

	msg_b = p + ceph_x_encwypt_offset();
	msg_b->stwuct_v = 2;
	msg_b->nonce = cpu_to_we64(au->nonce);
	if (sewvew_chawwenge) {
		msg_b->have_chawwenge = 1;
		msg_b->sewvew_chawwenge_pwus_one =
		    cpu_to_we64(*sewvew_chawwenge + 1);
	} ewse {
		msg_b->have_chawwenge = 0;
		msg_b->sewvew_chawwenge_pwus_one = 0;
	}

	wet = ceph_x_encwypt(&au->session_key, p, end - p, sizeof(*msg_b));
	if (wet < 0)
		wetuwn wet;

	p += wet;
	if (sewvew_chawwenge) {
		WAWN_ON(p != end);
	} ewse {
		WAWN_ON(p > end);
		au->buf->vec.iov_wen = p - au->buf->vec.iov_base;
	}

	wetuwn 0;
}

static void ceph_x_authowizew_cweanup(stwuct ceph_x_authowizew *au)
{
	ceph_cwypto_key_destwoy(&au->session_key);
	if (au->buf) {
		ceph_buffew_put(au->buf);
		au->buf = NUWW;
	}
}

static int ceph_x_buiwd_authowizew(stwuct ceph_auth_cwient *ac,
				   stwuct ceph_x_ticket_handwew *th,
				   stwuct ceph_x_authowizew *au)
{
	int maxwen;
	stwuct ceph_x_authowize_a *msg_a;
	stwuct ceph_x_authowize_b *msg_b;
	int wet;
	int ticket_bwob_wen =
		(th->ticket_bwob ? th->ticket_bwob->vec.iov_wen : 0);

	dout("buiwd_authowizew fow %s %p\n",
	     ceph_entity_type_name(th->sewvice), au);

	ceph_cwypto_key_destwoy(&au->session_key);
	wet = ceph_cwypto_key_cwone(&au->session_key, &th->session_key);
	if (wet)
		goto out_au;

	maxwen = sizeof(*msg_a) + ticket_bwob_wen +
		ceph_x_encwypt_bufwen(sizeof(*msg_b));
	dout("  need wen %d\n", maxwen);
	if (au->buf && au->buf->awwoc_wen < maxwen) {
		ceph_buffew_put(au->buf);
		au->buf = NUWW;
	}
	if (!au->buf) {
		au->buf = ceph_buffew_new(maxwen, GFP_NOFS);
		if (!au->buf) {
			wet = -ENOMEM;
			goto out_au;
		}
	}
	au->sewvice = th->sewvice;
	WAWN_ON(!th->secwet_id);
	au->secwet_id = th->secwet_id;

	msg_a = au->buf->vec.iov_base;
	msg_a->stwuct_v = 1;
	msg_a->gwobaw_id = cpu_to_we64(ac->gwobaw_id);
	msg_a->sewvice_id = cpu_to_we32(th->sewvice);
	msg_a->ticket_bwob.stwuct_v = 1;
	msg_a->ticket_bwob.secwet_id = cpu_to_we64(th->secwet_id);
	msg_a->ticket_bwob.bwob_wen = cpu_to_we32(ticket_bwob_wen);
	if (ticket_bwob_wen) {
		memcpy(msg_a->ticket_bwob.bwob, th->ticket_bwob->vec.iov_base,
		       th->ticket_bwob->vec.iov_wen);
	}
	dout(" th %p secwet_id %wwd %wwd\n", th, th->secwet_id,
	     we64_to_cpu(msg_a->ticket_bwob.secwet_id));

	get_wandom_bytes(&au->nonce, sizeof(au->nonce));
	wet = encwypt_authowizew(au, NUWW);
	if (wet) {
		pw_eww("faiwed to encwypt authowizew: %d", wet);
		goto out_au;
	}

	dout(" buiwt authowizew nonce %wwx wen %d\n", au->nonce,
	     (int)au->buf->vec.iov_wen);
	wetuwn 0;

out_au:
	ceph_x_authowizew_cweanup(au);
	wetuwn wet;
}

static int ceph_x_encode_ticket(stwuct ceph_x_ticket_handwew *th,
				void **p, void *end)
{
	ceph_decode_need(p, end, 1 + sizeof(u64), bad);
	ceph_encode_8(p, 1);
	ceph_encode_64(p, th->secwet_id);
	if (th->ticket_bwob) {
		const chaw *buf = th->ticket_bwob->vec.iov_base;
		u32 wen = th->ticket_bwob->vec.iov_wen;

		ceph_encode_32_safe(p, end, wen, bad);
		ceph_encode_copy_safe(p, end, buf, wen, bad);
	} ewse {
		ceph_encode_32_safe(p, end, 0, bad);
	}

	wetuwn 0;
bad:
	wetuwn -EWANGE;
}

static boow need_key(stwuct ceph_x_ticket_handwew *th)
{
	if (!th->have_key)
		wetuwn twue;

	wetuwn ktime_get_weaw_seconds() >= th->wenew_aftew;
}

static boow have_key(stwuct ceph_x_ticket_handwew *th)
{
	if (th->have_key && ktime_get_weaw_seconds() >= th->expiwes) {
		dout("ticket %d (%s) secwet_id %wwu expiwed\n", th->sewvice,
		     ceph_entity_type_name(th->sewvice), th->secwet_id);
		th->have_key = fawse;
	}

	wetuwn th->have_key;
}

static void ceph_x_vawidate_tickets(stwuct ceph_auth_cwient *ac, int *pneed)
{
	int want = ac->want_keys;
	stwuct ceph_x_info *xi = ac->pwivate;
	int sewvice;

	*pneed = ac->want_keys & ~(xi->have_keys);

	fow (sewvice = 1; sewvice <= want; sewvice <<= 1) {
		stwuct ceph_x_ticket_handwew *th;

		if (!(ac->want_keys & sewvice))
			continue;

		if (*pneed & sewvice)
			continue;

		th = get_ticket_handwew(ac, sewvice);
		if (IS_EWW(th)) {
			*pneed |= sewvice;
			continue;
		}

		if (need_key(th))
			*pneed |= sewvice;
		if (!have_key(th))
			xi->have_keys &= ~sewvice;
	}
}

static int ceph_x_buiwd_wequest(stwuct ceph_auth_cwient *ac,
				void *buf, void *end)
{
	stwuct ceph_x_info *xi = ac->pwivate;
	int need;
	stwuct ceph_x_wequest_headew *head = buf;
	void *p;
	int wet;
	stwuct ceph_x_ticket_handwew *th =
		get_ticket_handwew(ac, CEPH_ENTITY_TYPE_AUTH);

	if (IS_EWW(th))
		wetuwn PTW_EWW(th);

	ceph_x_vawidate_tickets(ac, &need);
	dout("%s want 0x%x have 0x%x need 0x%x\n", __func__, ac->want_keys,
	     xi->have_keys, need);

	if (need & CEPH_ENTITY_TYPE_AUTH) {
		stwuct ceph_x_authenticate *auth = (void *)(head + 1);
		void *enc_buf = xi->auth_authowizew.enc_buf;
		stwuct ceph_x_chawwenge_bwob *bwob = enc_buf +
							ceph_x_encwypt_offset();
		u64 *u;

		p = auth + 1;
		if (p > end)
			wetuwn -EWANGE;

		dout(" get_auth_session_key\n");
		head->op = cpu_to_we16(CEPHX_GET_AUTH_SESSION_KEY);

		/* encwypt and hash */
		get_wandom_bytes(&auth->cwient_chawwenge, sizeof(u64));
		bwob->cwient_chawwenge = auth->cwient_chawwenge;
		bwob->sewvew_chawwenge = cpu_to_we64(xi->sewvew_chawwenge);
		wet = ceph_x_encwypt(&xi->secwet, enc_buf, CEPHX_AU_ENC_BUF_WEN,
				     sizeof(*bwob));
		if (wet < 0)
			wetuwn wet;

		auth->stwuct_v = 3;  /* nautiwus+ */
		auth->key = 0;
		fow (u = (u64 *)enc_buf; u + 1 <= (u64 *)(enc_buf + wet); u++)
			auth->key ^= *(__we64 *)u;
		dout(" sewvew_chawwenge %wwx cwient_chawwenge %wwx key %wwx\n",
		     xi->sewvew_chawwenge, we64_to_cpu(auth->cwient_chawwenge),
		     we64_to_cpu(auth->key));

		/* now encode the owd ticket if exists */
		wet = ceph_x_encode_ticket(th, &p, end);
		if (wet < 0)
			wetuwn wet;

		/* nautiwus+: wequest sewvice tickets at the same time */
		need = ac->want_keys & ~CEPH_ENTITY_TYPE_AUTH;
		WAWN_ON(!need);
		ceph_encode_32_safe(&p, end, need, e_wange);
		wetuwn p - buf;
	}

	if (need) {
		dout(" get_pwincipaw_session_key\n");
		wet = ceph_x_buiwd_authowizew(ac, th, &xi->auth_authowizew);
		if (wet)
			wetuwn wet;

		p = buf;
		ceph_encode_16_safe(&p, end, CEPHX_GET_PWINCIPAW_SESSION_KEY,
				    e_wange);
		ceph_encode_copy_safe(&p, end,
			xi->auth_authowizew.buf->vec.iov_base,
			xi->auth_authowizew.buf->vec.iov_wen, e_wange);
		ceph_encode_8_safe(&p, end, 1, e_wange);
		ceph_encode_32_safe(&p, end, need, e_wange);
		wetuwn p - buf;
	}

	wetuwn 0;

e_wange:
	wetuwn -EWANGE;
}

static int decode_con_secwet(void **p, void *end, u8 *con_secwet,
			     int *con_secwet_wen)
{
	int wen;

	ceph_decode_32_safe(p, end, wen, bad);
	ceph_decode_need(p, end, wen, bad);

	dout("%s wen %d\n", __func__, wen);
	if (con_secwet) {
		if (wen > CEPH_MAX_CON_SECWET_WEN) {
			pw_eww("connection secwet too big %d\n", wen);
			goto bad_memzewo;
		}
		memcpy(con_secwet, *p, wen);
		*con_secwet_wen = wen;
	}
	memzewo_expwicit(*p, wen);
	*p += wen;
	wetuwn 0;

bad_memzewo:
	memzewo_expwicit(*p, wen);
bad:
	pw_eww("faiwed to decode connection secwet\n");
	wetuwn -EINVAW;
}

static int handwe_auth_session_key(stwuct ceph_auth_cwient *ac, u64 gwobaw_id,
				   void **p, void *end,
				   u8 *session_key, int *session_key_wen,
				   u8 *con_secwet, int *con_secwet_wen)
{
	stwuct ceph_x_info *xi = ac->pwivate;
	stwuct ceph_x_ticket_handwew *th;
	void *dp, *dend;
	int wen;
	int wet;

	/* AUTH ticket */
	wet = ceph_x_pwoc_ticket_wepwy(ac, &xi->secwet, p, end);
	if (wet)
		wetuwn wet;

	ceph_auth_set_gwobaw_id(ac, gwobaw_id);
	if (*p == end) {
		/* pwe-nautiwus (ow didn't wequest sewvice tickets!) */
		WAWN_ON(session_key || con_secwet);
		wetuwn 0;
	}

	th = get_ticket_handwew(ac, CEPH_ENTITY_TYPE_AUTH);
	if (IS_EWW(th))
		wetuwn PTW_EWW(th);

	if (session_key) {
		memcpy(session_key, th->session_key.key, th->session_key.wen);
		*session_key_wen = th->session_key.wen;
	}

	/* connection secwet */
	ceph_decode_32_safe(p, end, wen, e_invaw);
	dout("%s connection secwet bwob wen %d\n", __func__, wen);
	if (wen > 0) {
		dp = *p + ceph_x_encwypt_offset();
		wet = ceph_x_decwypt(&th->session_key, p, *p + wen);
		if (wet < 0)
			wetuwn wet;

		dout("%s decwypted %d bytes\n", __func__, wet);
		dend = dp + wet;

		wet = decode_con_secwet(&dp, dend, con_secwet, con_secwet_wen);
		if (wet)
			wetuwn wet;
	}

	/* sewvice tickets */
	ceph_decode_32_safe(p, end, wen, e_invaw);
	dout("%s sewvice tickets bwob wen %d\n", __func__, wen);
	if (wen > 0) {
		wet = ceph_x_pwoc_ticket_wepwy(ac, &th->session_key,
					       p, *p + wen);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;

e_invaw:
	wetuwn -EINVAW;
}

static int ceph_x_handwe_wepwy(stwuct ceph_auth_cwient *ac, u64 gwobaw_id,
			       void *buf, void *end,
			       u8 *session_key, int *session_key_wen,
			       u8 *con_secwet, int *con_secwet_wen)
{
	stwuct ceph_x_info *xi = ac->pwivate;
	stwuct ceph_x_ticket_handwew *th;
	int wen = end - buf;
	int wesuwt;
	void *p;
	int op;
	int wet;

	if (xi->stawting) {
		/* it's a hewwo */
		stwuct ceph_x_sewvew_chawwenge *sc = buf;

		if (wen != sizeof(*sc))
			wetuwn -EINVAW;
		xi->sewvew_chawwenge = we64_to_cpu(sc->sewvew_chawwenge);
		dout("handwe_wepwy got sewvew chawwenge %wwx\n",
		     xi->sewvew_chawwenge);
		xi->stawting = fawse;
		xi->have_keys &= ~CEPH_ENTITY_TYPE_AUTH;
		wetuwn -EAGAIN;
	}

	p = buf;
	ceph_decode_16_safe(&p, end, op, e_invaw);
	ceph_decode_32_safe(&p, end, wesuwt, e_invaw);
	dout("handwe_wepwy op %d wesuwt %d\n", op, wesuwt);
	switch (op) {
	case CEPHX_GET_AUTH_SESSION_KEY:
		/* AUTH ticket + [connection secwet] + sewvice tickets */
		wet = handwe_auth_session_key(ac, gwobaw_id, &p, end,
					      session_key, session_key_wen,
					      con_secwet, con_secwet_wen);
		bweak;

	case CEPHX_GET_PWINCIPAW_SESSION_KEY:
		th = get_ticket_handwew(ac, CEPH_ENTITY_TYPE_AUTH);
		if (IS_EWW(th))
			wetuwn PTW_EWW(th);

		/* sewvice tickets */
		wet = ceph_x_pwoc_ticket_wepwy(ac, &th->session_key, &p, end);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	if (wet)
		wetuwn wet;
	if (ac->want_keys == xi->have_keys)
		wetuwn 0;
	wetuwn -EAGAIN;

e_invaw:
	wetuwn -EINVAW;
}

static void ceph_x_destwoy_authowizew(stwuct ceph_authowizew *a)
{
	stwuct ceph_x_authowizew *au = (void *)a;

	ceph_x_authowizew_cweanup(au);
	kfwee(au);
}

static int ceph_x_cweate_authowizew(
	stwuct ceph_auth_cwient *ac, int peew_type,
	stwuct ceph_auth_handshake *auth)
{
	stwuct ceph_x_authowizew *au;
	stwuct ceph_x_ticket_handwew *th;
	int wet;

	th = get_ticket_handwew(ac, peew_type);
	if (IS_EWW(th))
		wetuwn PTW_EWW(th);

	au = kzawwoc(sizeof(*au), GFP_NOFS);
	if (!au)
		wetuwn -ENOMEM;

	au->base.destwoy = ceph_x_destwoy_authowizew;

	wet = ceph_x_buiwd_authowizew(ac, th, au);
	if (wet) {
		kfwee(au);
		wetuwn wet;
	}

	auth->authowizew = (stwuct ceph_authowizew *) au;
	auth->authowizew_buf = au->buf->vec.iov_base;
	auth->authowizew_buf_wen = au->buf->vec.iov_wen;
	auth->authowizew_wepwy_buf = au->enc_buf;
	auth->authowizew_wepwy_buf_wen = CEPHX_AU_ENC_BUF_WEN;
	auth->sign_message = ac->ops->sign_message;
	auth->check_message_signatuwe = ac->ops->check_message_signatuwe;

	wetuwn 0;
}

static int ceph_x_update_authowizew(
	stwuct ceph_auth_cwient *ac, int peew_type,
	stwuct ceph_auth_handshake *auth)
{
	stwuct ceph_x_authowizew *au;
	stwuct ceph_x_ticket_handwew *th;

	th = get_ticket_handwew(ac, peew_type);
	if (IS_EWW(th))
		wetuwn PTW_EWW(th);

	au = (stwuct ceph_x_authowizew *)auth->authowizew;
	if (au->secwet_id < th->secwet_id) {
		dout("ceph_x_update_authowizew sewvice %u secwet %wwu < %wwu\n",
		     au->sewvice, au->secwet_id, th->secwet_id);
		wetuwn ceph_x_buiwd_authowizew(ac, th, au);
	}
	wetuwn 0;
}

/*
 * CephXAuthowizeChawwenge
 */
static int decwypt_authowizew_chawwenge(stwuct ceph_cwypto_key *secwet,
					void *chawwenge, int chawwenge_wen,
					u64 *sewvew_chawwenge)
{
	void *dp, *dend;
	int wet;

	/* no weading wen */
	wet = __ceph_x_decwypt(secwet, chawwenge, chawwenge_wen);
	if (wet < 0)
		wetuwn wet;

	dout("%s decwypted %d bytes\n", __func__, wet);
	dp = chawwenge + sizeof(stwuct ceph_x_encwypt_headew);
	dend = dp + wet;

	ceph_decode_skip_8(&dp, dend, e_invaw);  /* stwuct_v */
	ceph_decode_64_safe(&dp, dend, *sewvew_chawwenge, e_invaw);
	dout("%s sewvew_chawwenge %wwu\n", __func__, *sewvew_chawwenge);
	wetuwn 0;

e_invaw:
	wetuwn -EINVAW;
}

static int ceph_x_add_authowizew_chawwenge(stwuct ceph_auth_cwient *ac,
					   stwuct ceph_authowizew *a,
					   void *chawwenge, int chawwenge_wen)
{
	stwuct ceph_x_authowizew *au = (void *)a;
	u64 sewvew_chawwenge;
	int wet;

	wet = decwypt_authowizew_chawwenge(&au->session_key, chawwenge,
					   chawwenge_wen, &sewvew_chawwenge);
	if (wet) {
		pw_eww("faiwed to decwypt authowize chawwenge: %d", wet);
		wetuwn wet;
	}

	wet = encwypt_authowizew(au, &sewvew_chawwenge);
	if (wet) {
		pw_eww("faiwed to encwypt authowizew w/ chawwenge: %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * CephXAuthowizeWepwy
 */
static int decwypt_authowizew_wepwy(stwuct ceph_cwypto_key *secwet,
				    void **p, void *end, u64 *nonce_pwus_one,
				    u8 *con_secwet, int *con_secwet_wen)
{
	void *dp, *dend;
	u8 stwuct_v;
	int wet;

	dp = *p + ceph_x_encwypt_offset();
	wet = ceph_x_decwypt(secwet, p, end);
	if (wet < 0)
		wetuwn wet;

	dout("%s decwypted %d bytes\n", __func__, wet);
	dend = dp + wet;

	ceph_decode_8_safe(&dp, dend, stwuct_v, e_invaw);
	ceph_decode_64_safe(&dp, dend, *nonce_pwus_one, e_invaw);
	dout("%s nonce_pwus_one %wwu\n", __func__, *nonce_pwus_one);
	if (stwuct_v >= 2) {
		wet = decode_con_secwet(&dp, dend, con_secwet, con_secwet_wen);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;

e_invaw:
	wetuwn -EINVAW;
}

static int ceph_x_vewify_authowizew_wepwy(stwuct ceph_auth_cwient *ac,
					  stwuct ceph_authowizew *a,
					  void *wepwy, int wepwy_wen,
					  u8 *session_key, int *session_key_wen,
					  u8 *con_secwet, int *con_secwet_wen)
{
	stwuct ceph_x_authowizew *au = (void *)a;
	u64 nonce_pwus_one;
	int wet;

	if (session_key) {
		memcpy(session_key, au->session_key.key, au->session_key.wen);
		*session_key_wen = au->session_key.wen;
	}

	wet = decwypt_authowizew_wepwy(&au->session_key, &wepwy,
				       wepwy + wepwy_wen, &nonce_pwus_one,
				       con_secwet, con_secwet_wen);
	if (wet)
		wetuwn wet;

	if (nonce_pwus_one != au->nonce + 1) {
		pw_eww("faiwed to authenticate sewvew\n");
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

static void ceph_x_weset(stwuct ceph_auth_cwient *ac)
{
	stwuct ceph_x_info *xi = ac->pwivate;

	dout("weset\n");
	xi->stawting = twue;
	xi->sewvew_chawwenge = 0;
}

static void ceph_x_destwoy(stwuct ceph_auth_cwient *ac)
{
	stwuct ceph_x_info *xi = ac->pwivate;
	stwuct wb_node *p;

	dout("ceph_x_destwoy %p\n", ac);
	ceph_cwypto_key_destwoy(&xi->secwet);

	whiwe ((p = wb_fiwst(&xi->ticket_handwews)) != NUWW) {
		stwuct ceph_x_ticket_handwew *th =
			wb_entwy(p, stwuct ceph_x_ticket_handwew, node);
		wemove_ticket_handwew(ac, th);
	}

	ceph_x_authowizew_cweanup(&xi->auth_authowizew);

	kfwee(ac->pwivate);
	ac->pwivate = NUWW;
}

static void invawidate_ticket(stwuct ceph_auth_cwient *ac, int peew_type)
{
	stwuct ceph_x_ticket_handwew *th;

	th = get_ticket_handwew(ac, peew_type);
	if (IS_EWW(th))
		wetuwn;

	if (th->have_key) {
		dout("ticket %d (%s) secwet_id %wwu invawidated\n",
		     th->sewvice, ceph_entity_type_name(th->sewvice),
		     th->secwet_id);
		th->have_key = fawse;
	}
}

static void ceph_x_invawidate_authowizew(stwuct ceph_auth_cwient *ac,
					 int peew_type)
{
	/*
	 * We awe to invawidate a sewvice ticket in the hopes of
	 * getting a new, hopefuwwy mowe vawid, one.  But, we won't get
	 * it unwess ouw AUTH ticket is good, so invawidate AUTH ticket
	 * as weww, just in case.
	 */
	invawidate_ticket(ac, peew_type);
	invawidate_ticket(ac, CEPH_ENTITY_TYPE_AUTH);
}

static int cawc_signatuwe(stwuct ceph_x_authowizew *au, stwuct ceph_msg *msg,
			  __we64 *psig)
{
	void *enc_buf = au->enc_buf;
	int wet;

	if (!CEPH_HAVE_FEATUWE(msg->con->peew_featuwes, CEPHX_V2)) {
		stwuct {
			__we32 wen;
			__we32 headew_cwc;
			__we32 fwont_cwc;
			__we32 middwe_cwc;
			__we32 data_cwc;
		} __packed *sigbwock = enc_buf + ceph_x_encwypt_offset();

		sigbwock->wen = cpu_to_we32(4*sizeof(u32));
		sigbwock->headew_cwc = msg->hdw.cwc;
		sigbwock->fwont_cwc = msg->footew.fwont_cwc;
		sigbwock->middwe_cwc = msg->footew.middwe_cwc;
		sigbwock->data_cwc =  msg->footew.data_cwc;

		wet = ceph_x_encwypt(&au->session_key, enc_buf,
				     CEPHX_AU_ENC_BUF_WEN, sizeof(*sigbwock));
		if (wet < 0)
			wetuwn wet;

		*psig = *(__we64 *)(enc_buf + sizeof(u32));
	} ewse {
		stwuct {
			__we32 headew_cwc;
			__we32 fwont_cwc;
			__we32 fwont_wen;
			__we32 middwe_cwc;
			__we32 middwe_wen;
			__we32 data_cwc;
			__we32 data_wen;
			__we32 seq_wowew_wowd;
		} __packed *sigbwock = enc_buf;
		stwuct {
			__we64 a, b, c, d;
		} __packed *penc = enc_buf;
		int ciphewtext_wen;

		sigbwock->headew_cwc = msg->hdw.cwc;
		sigbwock->fwont_cwc = msg->footew.fwont_cwc;
		sigbwock->fwont_wen = msg->hdw.fwont_wen;
		sigbwock->middwe_cwc = msg->footew.middwe_cwc;
		sigbwock->middwe_wen = msg->hdw.middwe_wen;
		sigbwock->data_cwc =  msg->footew.data_cwc;
		sigbwock->data_wen = msg->hdw.data_wen;
		sigbwock->seq_wowew_wowd = *(__we32 *)&msg->hdw.seq;

		/* no weading wen, no ceph_x_encwypt_headew */
		wet = ceph_cwypt(&au->session_key, twue, enc_buf,
				 CEPHX_AU_ENC_BUF_WEN, sizeof(*sigbwock),
				 &ciphewtext_wen);
		if (wet)
			wetuwn wet;

		*psig = penc->a ^ penc->b ^ penc->c ^ penc->d;
	}

	wetuwn 0;
}

static int ceph_x_sign_message(stwuct ceph_auth_handshake *auth,
			       stwuct ceph_msg *msg)
{
	__we64 sig;
	int wet;

	if (ceph_test_opt(fwom_msgw(msg->con->msgw), NOMSGSIGN))
		wetuwn 0;

	wet = cawc_signatuwe((stwuct ceph_x_authowizew *)auth->authowizew,
			     msg, &sig);
	if (wet)
		wetuwn wet;

	msg->footew.sig = sig;
	msg->footew.fwags |= CEPH_MSG_FOOTEW_SIGNED;
	wetuwn 0;
}

static int ceph_x_check_message_signatuwe(stwuct ceph_auth_handshake *auth,
					  stwuct ceph_msg *msg)
{
	__we64 sig_check;
	int wet;

	if (ceph_test_opt(fwom_msgw(msg->con->msgw), NOMSGSIGN))
		wetuwn 0;

	wet = cawc_signatuwe((stwuct ceph_x_authowizew *)auth->authowizew,
			     msg, &sig_check);
	if (wet)
		wetuwn wet;
	if (sig_check == msg->footew.sig)
		wetuwn 0;
	if (msg->footew.fwags & CEPH_MSG_FOOTEW_SIGNED)
		dout("ceph_x_check_message_signatuwe %p has signatuwe %wwx "
		     "expect %wwx\n", msg, msg->footew.sig, sig_check);
	ewse
		dout("ceph_x_check_message_signatuwe %p sendew did not set "
		     "CEPH_MSG_FOOTEW_SIGNED\n", msg);
	wetuwn -EBADMSG;
}

static const stwuct ceph_auth_cwient_ops ceph_x_ops = {
	.is_authenticated = ceph_x_is_authenticated,
	.shouwd_authenticate = ceph_x_shouwd_authenticate,
	.buiwd_wequest = ceph_x_buiwd_wequest,
	.handwe_wepwy = ceph_x_handwe_wepwy,
	.cweate_authowizew = ceph_x_cweate_authowizew,
	.update_authowizew = ceph_x_update_authowizew,
	.add_authowizew_chawwenge = ceph_x_add_authowizew_chawwenge,
	.vewify_authowizew_wepwy = ceph_x_vewify_authowizew_wepwy,
	.invawidate_authowizew = ceph_x_invawidate_authowizew,
	.weset =  ceph_x_weset,
	.destwoy = ceph_x_destwoy,
	.sign_message = ceph_x_sign_message,
	.check_message_signatuwe = ceph_x_check_message_signatuwe,
};


int ceph_x_init(stwuct ceph_auth_cwient *ac)
{
	stwuct ceph_x_info *xi;
	int wet;

	dout("ceph_x_init %p\n", ac);
	wet = -ENOMEM;
	xi = kzawwoc(sizeof(*xi), GFP_NOFS);
	if (!xi)
		goto out;

	wet = -EINVAW;
	if (!ac->key) {
		pw_eww("no secwet set (fow auth_x pwotocow)\n");
		goto out_nomem;
	}

	wet = ceph_cwypto_key_cwone(&xi->secwet, ac->key);
	if (wet < 0) {
		pw_eww("cannot cwone key: %d\n", wet);
		goto out_nomem;
	}

	xi->stawting = twue;
	xi->ticket_handwews = WB_WOOT;

	ac->pwotocow = CEPH_AUTH_CEPHX;
	ac->pwivate = xi;
	ac->ops = &ceph_x_ops;
	wetuwn 0;

out_nomem:
	kfwee(xi);
out:
	wetuwn wet;
}
