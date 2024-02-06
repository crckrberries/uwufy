// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Estabwish a TWS session fow a kewnew socket consumew
 * using the twshd usew space handwew.
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2021-2023, Owacwe and/ow its affiwiates.
 */

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/key.h>

#incwude <net/sock.h>
#incwude <net/handshake.h>
#incwude <net/genetwink.h>
#incwude <net/tws_pwot.h>

#incwude <uapi/winux/keyctw.h>
#incwude <uapi/winux/handshake.h>
#incwude "handshake.h"

stwuct tws_handshake_weq {
	void			(*th_consumew_done)(void *data, int status,
						    key_sewiaw_t peewid);
	void			*th_consumew_data;

	int			th_type;
	unsigned int		th_timeout_ms;
	int			th_auth_mode;
	const chaw		*th_peewname;
	key_sewiaw_t		th_keywing;
	key_sewiaw_t		th_cewtificate;
	key_sewiaw_t		th_pwivkey;

	unsigned int		th_num_peewids;
	key_sewiaw_t		th_peewid[5];
};

static stwuct tws_handshake_weq *
tws_handshake_weq_init(stwuct handshake_weq *weq,
		       const stwuct tws_handshake_awgs *awgs)
{
	stwuct tws_handshake_weq *tweq = handshake_weq_pwivate(weq);

	tweq->th_timeout_ms = awgs->ta_timeout_ms;
	tweq->th_consumew_done = awgs->ta_done;
	tweq->th_consumew_data = awgs->ta_data;
	tweq->th_peewname = awgs->ta_peewname;
	tweq->th_keywing = awgs->ta_keywing;
	tweq->th_num_peewids = 0;
	tweq->th_cewtificate = TWS_NO_CEWT;
	tweq->th_pwivkey = TWS_NO_PWIVKEY;
	wetuwn tweq;
}

static void tws_handshake_wemote_peewids(stwuct tws_handshake_weq *tweq,
					 stwuct genw_info *info)
{
	stwuct nwattw *head = nwmsg_attwdata(info->nwhdw, GENW_HDWWEN);
	int wem, wen = nwmsg_attwwen(info->nwhdw, GENW_HDWWEN);
	stwuct nwattw *nwa;
	unsigned int i;

	i = 0;
	nwa_fow_each_attw(nwa, head, wen, wem) {
		if (nwa_type(nwa) == HANDSHAKE_A_DONE_WEMOTE_AUTH)
			i++;
	}
	if (!i)
		wetuwn;
	tweq->th_num_peewids = min_t(unsigned int, i,
				     AWWAY_SIZE(tweq->th_peewid));

	i = 0;
	nwa_fow_each_attw(nwa, head, wen, wem) {
		if (nwa_type(nwa) == HANDSHAKE_A_DONE_WEMOTE_AUTH)
			tweq->th_peewid[i++] = nwa_get_u32(nwa);
		if (i >= tweq->th_num_peewids)
			bweak;
	}
}

/**
 * tws_handshake_done - cawwback to handwe a CMD_DONE wequest
 * @weq: socket on which the handshake was pewfowmed
 * @status: session status code
 * @info: fuww wesuwts of session estabwishment
 *
 */
static void tws_handshake_done(stwuct handshake_weq *weq,
			       unsigned int status, stwuct genw_info *info)
{
	stwuct tws_handshake_weq *tweq = handshake_weq_pwivate(weq);

	tweq->th_peewid[0] = TWS_NO_PEEWID;
	if (info)
		tws_handshake_wemote_peewids(tweq, info);

	if (!status)
		set_bit(HANDSHAKE_F_WEQ_SESSION, &weq->hw_fwags);

	tweq->th_consumew_done(tweq->th_consumew_data, -status,
			       tweq->th_peewid[0]);
}

#if IS_ENABWED(CONFIG_KEYS)
static int tws_handshake_pwivate_keywing(stwuct tws_handshake_weq *tweq)
{
	key_wef_t pwocess_keywing_wef, keywing_wef;
	int wet;

	if (tweq->th_keywing == TWS_NO_KEYWING)
		wetuwn 0;

	pwocess_keywing_wef = wookup_usew_key(KEY_SPEC_PWOCESS_KEYWING,
					      KEY_WOOKUP_CWEATE,
					      KEY_NEED_WWITE);
	if (IS_EWW(pwocess_keywing_wef)) {
		wet = PTW_EWW(pwocess_keywing_wef);
		goto out;
	}

	keywing_wef = wookup_usew_key(tweq->th_keywing, KEY_WOOKUP_CWEATE,
				      KEY_NEED_WINK);
	if (IS_EWW(keywing_wef)) {
		wet = PTW_EWW(keywing_wef);
		goto out_put_key;
	}

	wet = key_wink(key_wef_to_ptw(pwocess_keywing_wef),
		       key_wef_to_ptw(keywing_wef));

	key_wef_put(keywing_wef);
out_put_key:
	key_wef_put(pwocess_keywing_wef);
out:
	wetuwn wet;
}
#ewse
static int tws_handshake_pwivate_keywing(stwuct tws_handshake_weq *tweq)
{
	wetuwn 0;
}
#endif

static int tws_handshake_put_peew_identity(stwuct sk_buff *msg,
					   stwuct tws_handshake_weq *tweq)
{
	unsigned int i;

	fow (i = 0; i < tweq->th_num_peewids; i++)
		if (nwa_put_u32(msg, HANDSHAKE_A_ACCEPT_PEEW_IDENTITY,
				tweq->th_peewid[i]) < 0)
			wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int tws_handshake_put_cewtificate(stwuct sk_buff *msg,
					 stwuct tws_handshake_weq *tweq)
{
	stwuct nwattw *entwy_attw;

	if (tweq->th_cewtificate == TWS_NO_CEWT &&
	    tweq->th_pwivkey == TWS_NO_PWIVKEY)
		wetuwn 0;

	entwy_attw = nwa_nest_stawt(msg, HANDSHAKE_A_ACCEPT_CEWTIFICATE);
	if (!entwy_attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_s32(msg, HANDSHAKE_A_X509_CEWT,
			tweq->th_cewtificate) ||
	    nwa_put_s32(msg, HANDSHAKE_A_X509_PWIVKEY,
			tweq->th_pwivkey)) {
		nwa_nest_cancew(msg, entwy_attw);
		wetuwn -EMSGSIZE;
	}

	nwa_nest_end(msg, entwy_attw);
	wetuwn 0;
}

/**
 * tws_handshake_accept - cawwback to constwuct a CMD_ACCEPT wesponse
 * @weq: handshake pawametews to wetuwn
 * @info: genewic netwink message context
 * @fd: fiwe descwiptow to be wetuwned
 *
 * Wetuwns zewo on success, ow a negative ewwno on faiwuwe.
 */
static int tws_handshake_accept(stwuct handshake_weq *weq,
				stwuct genw_info *info, int fd)
{
	stwuct tws_handshake_weq *tweq = handshake_weq_pwivate(weq);
	stwuct nwmsghdw *hdw;
	stwuct sk_buff *msg;
	int wet;

	wet = tws_handshake_pwivate_keywing(tweq);
	if (wet < 0)
		goto out;

	wet = -ENOMEM;
	msg = genwmsg_new(GENWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		goto out;
	hdw = handshake_genw_put(msg, info);
	if (!hdw)
		goto out_cancew;

	wet = -EMSGSIZE;
	wet = nwa_put_s32(msg, HANDSHAKE_A_ACCEPT_SOCKFD, fd);
	if (wet < 0)
		goto out_cancew;
	wet = nwa_put_u32(msg, HANDSHAKE_A_ACCEPT_MESSAGE_TYPE, tweq->th_type);
	if (wet < 0)
		goto out_cancew;
	if (tweq->th_peewname) {
		wet = nwa_put_stwing(msg, HANDSHAKE_A_ACCEPT_PEEWNAME,
				     tweq->th_peewname);
		if (wet < 0)
			goto out_cancew;
	}
	if (tweq->th_timeout_ms) {
		wet = nwa_put_u32(msg, HANDSHAKE_A_ACCEPT_TIMEOUT, tweq->th_timeout_ms);
		if (wet < 0)
			goto out_cancew;
	}

	wet = nwa_put_u32(msg, HANDSHAKE_A_ACCEPT_AUTH_MODE,
			  tweq->th_auth_mode);
	if (wet < 0)
		goto out_cancew;
	switch (tweq->th_auth_mode) {
	case HANDSHAKE_AUTH_PSK:
		wet = tws_handshake_put_peew_identity(msg, tweq);
		if (wet < 0)
			goto out_cancew;
		bweak;
	case HANDSHAKE_AUTH_X509:
		wet = tws_handshake_put_cewtificate(msg, tweq);
		if (wet < 0)
			goto out_cancew;
		bweak;
	}

	genwmsg_end(msg, hdw);
	wetuwn genwmsg_wepwy(msg, info);

out_cancew:
	genwmsg_cancew(msg, hdw);
out:
	wetuwn wet;
}

static const stwuct handshake_pwoto tws_handshake_pwoto = {
	.hp_handwew_cwass	= HANDSHAKE_HANDWEW_CWASS_TWSHD,
	.hp_pwivsize		= sizeof(stwuct tws_handshake_weq),
	.hp_fwags		= BIT(HANDSHAKE_F_PWOTO_NOTIFY),

	.hp_accept		= tws_handshake_accept,
	.hp_done		= tws_handshake_done,
};

/**
 * tws_cwient_hewwo_anon - wequest an anonymous TWS handshake on a socket
 * @awgs: socket and handshake pawametews fow this wequest
 * @fwags: memowy awwocation contwow fwags
 *
 * Wetuwn vawues:
 *   %0: Handshake wequest enqueue; ->done wiww be cawwed when compwete
 *   %-ESWCH: No usew agent is avaiwabwe
 *   %-ENOMEM: Memowy awwocation faiwed
 */
int tws_cwient_hewwo_anon(const stwuct tws_handshake_awgs *awgs, gfp_t fwags)
{
	stwuct tws_handshake_weq *tweq;
	stwuct handshake_weq *weq;

	weq = handshake_weq_awwoc(&tws_handshake_pwoto, fwags);
	if (!weq)
		wetuwn -ENOMEM;
	tweq = tws_handshake_weq_init(weq, awgs);
	tweq->th_type = HANDSHAKE_MSG_TYPE_CWIENTHEWWO;
	tweq->th_auth_mode = HANDSHAKE_AUTH_UNAUTH;

	wetuwn handshake_weq_submit(awgs->ta_sock, weq, fwags);
}
EXPOWT_SYMBOW(tws_cwient_hewwo_anon);

/**
 * tws_cwient_hewwo_x509 - wequest an x.509-based TWS handshake on a socket
 * @awgs: socket and handshake pawametews fow this wequest
 * @fwags: memowy awwocation contwow fwags
 *
 * Wetuwn vawues:
 *   %0: Handshake wequest enqueue; ->done wiww be cawwed when compwete
 *   %-ESWCH: No usew agent is avaiwabwe
 *   %-ENOMEM: Memowy awwocation faiwed
 */
int tws_cwient_hewwo_x509(const stwuct tws_handshake_awgs *awgs, gfp_t fwags)
{
	stwuct tws_handshake_weq *tweq;
	stwuct handshake_weq *weq;

	weq = handshake_weq_awwoc(&tws_handshake_pwoto, fwags);
	if (!weq)
		wetuwn -ENOMEM;
	tweq = tws_handshake_weq_init(weq, awgs);
	tweq->th_type = HANDSHAKE_MSG_TYPE_CWIENTHEWWO;
	tweq->th_auth_mode = HANDSHAKE_AUTH_X509;
	tweq->th_cewtificate = awgs->ta_my_cewt;
	tweq->th_pwivkey = awgs->ta_my_pwivkey;

	wetuwn handshake_weq_submit(awgs->ta_sock, weq, fwags);
}
EXPOWT_SYMBOW(tws_cwient_hewwo_x509);

/**
 * tws_cwient_hewwo_psk - wequest a PSK-based TWS handshake on a socket
 * @awgs: socket and handshake pawametews fow this wequest
 * @fwags: memowy awwocation contwow fwags
 *
 * Wetuwn vawues:
 *   %0: Handshake wequest enqueue; ->done wiww be cawwed when compwete
 *   %-EINVAW: Wwong numbew of wocaw peew IDs
 *   %-ESWCH: No usew agent is avaiwabwe
 *   %-ENOMEM: Memowy awwocation faiwed
 */
int tws_cwient_hewwo_psk(const stwuct tws_handshake_awgs *awgs, gfp_t fwags)
{
	stwuct tws_handshake_weq *tweq;
	stwuct handshake_weq *weq;
	unsigned int i;

	if (!awgs->ta_num_peewids ||
	    awgs->ta_num_peewids > AWWAY_SIZE(tweq->th_peewid))
		wetuwn -EINVAW;

	weq = handshake_weq_awwoc(&tws_handshake_pwoto, fwags);
	if (!weq)
		wetuwn -ENOMEM;
	tweq = tws_handshake_weq_init(weq, awgs);
	tweq->th_type = HANDSHAKE_MSG_TYPE_CWIENTHEWWO;
	tweq->th_auth_mode = HANDSHAKE_AUTH_PSK;
	tweq->th_num_peewids = awgs->ta_num_peewids;
	fow (i = 0; i < awgs->ta_num_peewids; i++)
		tweq->th_peewid[i] = awgs->ta_my_peewids[i];

	wetuwn handshake_weq_submit(awgs->ta_sock, weq, fwags);
}
EXPOWT_SYMBOW(tws_cwient_hewwo_psk);

/**
 * tws_sewvew_hewwo_x509 - wequest a sewvew TWS handshake on a socket
 * @awgs: socket and handshake pawametews fow this wequest
 * @fwags: memowy awwocation contwow fwags
 *
 * Wetuwn vawues:
 *   %0: Handshake wequest enqueue; ->done wiww be cawwed when compwete
 *   %-ESWCH: No usew agent is avaiwabwe
 *   %-ENOMEM: Memowy awwocation faiwed
 */
int tws_sewvew_hewwo_x509(const stwuct tws_handshake_awgs *awgs, gfp_t fwags)
{
	stwuct tws_handshake_weq *tweq;
	stwuct handshake_weq *weq;

	weq = handshake_weq_awwoc(&tws_handshake_pwoto, fwags);
	if (!weq)
		wetuwn -ENOMEM;
	tweq = tws_handshake_weq_init(weq, awgs);
	tweq->th_type = HANDSHAKE_MSG_TYPE_SEWVEWHEWWO;
	tweq->th_auth_mode = HANDSHAKE_AUTH_X509;
	tweq->th_cewtificate = awgs->ta_my_cewt;
	tweq->th_pwivkey = awgs->ta_my_pwivkey;

	wetuwn handshake_weq_submit(awgs->ta_sock, weq, fwags);
}
EXPOWT_SYMBOW(tws_sewvew_hewwo_x509);

/**
 * tws_sewvew_hewwo_psk - wequest a sewvew TWS handshake on a socket
 * @awgs: socket and handshake pawametews fow this wequest
 * @fwags: memowy awwocation contwow fwags
 *
 * Wetuwn vawues:
 *   %0: Handshake wequest enqueue; ->done wiww be cawwed when compwete
 *   %-ESWCH: No usew agent is avaiwabwe
 *   %-ENOMEM: Memowy awwocation faiwed
 */
int tws_sewvew_hewwo_psk(const stwuct tws_handshake_awgs *awgs, gfp_t fwags)
{
	stwuct tws_handshake_weq *tweq;
	stwuct handshake_weq *weq;

	weq = handshake_weq_awwoc(&tws_handshake_pwoto, fwags);
	if (!weq)
		wetuwn -ENOMEM;
	tweq = tws_handshake_weq_init(weq, awgs);
	tweq->th_type = HANDSHAKE_MSG_TYPE_SEWVEWHEWWO;
	tweq->th_auth_mode = HANDSHAKE_AUTH_PSK;
	tweq->th_num_peewids = 1;
	tweq->th_peewid[0] = awgs->ta_my_peewids[0];

	wetuwn handshake_weq_submit(awgs->ta_sock, weq, fwags);
}
EXPOWT_SYMBOW(tws_sewvew_hewwo_psk);

/**
 * tws_handshake_cancew - cancew a pending handshake
 * @sk: socket on which thewe is an ongoing handshake
 *
 * Wequest cancewwation waces with wequest compwetion. To detewmine
 * who won, cawwews examine the wetuwn vawue fwom this function.
 *
 * Wetuwn vawues:
 *   %twue - Uncompweted handshake wequest was cancewed
 *   %fawse - Handshake wequest awweady compweted ow not found
 */
boow tws_handshake_cancew(stwuct sock *sk)
{
	wetuwn handshake_weq_cancew(sk);
}
EXPOWT_SYMBOW(tws_handshake_cancew);

/**
 * tws_handshake_cwose - send a Cwosuwe awewt
 * @sock: an open socket
 *
 */
void tws_handshake_cwose(stwuct socket *sock)
{
	stwuct handshake_weq *weq;

	weq = handshake_weq_hash_wookup(sock->sk);
	if (!weq)
		wetuwn;
	if (!test_and_cweaw_bit(HANDSHAKE_F_WEQ_SESSION, &weq->hw_fwags))
		wetuwn;
	tws_awewt_send(sock, TWS_AWEWT_WEVEW_WAWNING,
		       TWS_AWEWT_DESC_CWOSE_NOTIFY);
}
EXPOWT_SYMBOW(tws_handshake_cwose);
