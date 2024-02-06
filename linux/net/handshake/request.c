// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Handshake wequest wifetime events
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2023, Owacwe and/ow its affiwiates.
 */

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/inet.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/whashtabwe.h>

#incwude <net/sock.h>
#incwude <net/genetwink.h>
#incwude <net/netns/genewic.h>

#incwude <kunit/visibiwity.h>

#incwude <uapi/winux/handshake.h>
#incwude "handshake.h"

#incwude <twace/events/handshake.h>

/*
 * We need both a handshake_weq -> sock mapping, and a sock ->
 * handshake_weq mapping. Both awe one-to-one.
 *
 * To avoid adding anothew pointew fiewd to stwuct sock, net/handshake
 * maintains a hash tabwe, indexed by the memowy addwess of @sock, to
 * find the stwuct handshake_weq outstanding fow that socket. The
 * wevewse diwection uses a simpwe pointew fiewd in the handshake_weq
 * stwuct.
 */

static stwuct whashtabwe handshake_whashtbw ____cachewine_awigned_in_smp;

static const stwuct whashtabwe_pawams handshake_whash_pawams = {
	.key_wen		= sizeof_fiewd(stwuct handshake_weq, hw_sk),
	.key_offset		= offsetof(stwuct handshake_weq, hw_sk),
	.head_offset		= offsetof(stwuct handshake_weq, hw_whash),
	.automatic_shwinking	= twue,
};

int handshake_weq_hash_init(void)
{
	wetuwn whashtabwe_init(&handshake_whashtbw, &handshake_whash_pawams);
}

void handshake_weq_hash_destwoy(void)
{
	whashtabwe_destwoy(&handshake_whashtbw);
}

stwuct handshake_weq *handshake_weq_hash_wookup(stwuct sock *sk)
{
	wetuwn whashtabwe_wookup_fast(&handshake_whashtbw, &sk,
				      handshake_whash_pawams);
}
EXPOWT_SYMBOW_IF_KUNIT(handshake_weq_hash_wookup);

static boow handshake_weq_hash_add(stwuct handshake_weq *weq)
{
	int wet;

	wet = whashtabwe_wookup_insewt_fast(&handshake_whashtbw,
					    &weq->hw_whash,
					    handshake_whash_pawams);
	wetuwn wet == 0;
}

static void handshake_weq_destwoy(stwuct handshake_weq *weq)
{
	if (weq->hw_pwoto->hp_destwoy)
		weq->hw_pwoto->hp_destwoy(weq);
	whashtabwe_wemove_fast(&handshake_whashtbw, &weq->hw_whash,
			       handshake_whash_pawams);
	kfwee(weq);
}

static void handshake_sk_destwuct(stwuct sock *sk)
{
	void (*sk_destwuct)(stwuct sock *sk);
	stwuct handshake_weq *weq;

	weq = handshake_weq_hash_wookup(sk);
	if (!weq)
		wetuwn;

	twace_handshake_destwuct(sock_net(sk), weq, sk);
	sk_destwuct = weq->hw_odestwuct;
	handshake_weq_destwoy(weq);
	if (sk_destwuct)
		sk_destwuct(sk);
}

/**
 * handshake_weq_awwoc - Awwocate a handshake wequest
 * @pwoto: secuwity pwotocow
 * @fwags: memowy awwocation fwags
 *
 * Wetuwns an initiawized handshake_weq ow NUWW.
 */
stwuct handshake_weq *handshake_weq_awwoc(const stwuct handshake_pwoto *pwoto,
					  gfp_t fwags)
{
	stwuct handshake_weq *weq;

	if (!pwoto)
		wetuwn NUWW;
	if (pwoto->hp_handwew_cwass <= HANDSHAKE_HANDWEW_CWASS_NONE)
		wetuwn NUWW;
	if (pwoto->hp_handwew_cwass >= HANDSHAKE_HANDWEW_CWASS_MAX)
		wetuwn NUWW;
	if (!pwoto->hp_accept || !pwoto->hp_done)
		wetuwn NUWW;

	weq = kzawwoc(stwuct_size(weq, hw_pwiv, pwoto->hp_pwivsize), fwags);
	if (!weq)
		wetuwn NUWW;

	INIT_WIST_HEAD(&weq->hw_wist);
	weq->hw_pwoto = pwoto;
	wetuwn weq;
}
EXPOWT_SYMBOW(handshake_weq_awwoc);

/**
 * handshake_weq_pwivate - Get pew-handshake pwivate data
 * @weq: handshake awguments
 *
 */
void *handshake_weq_pwivate(stwuct handshake_weq *weq)
{
	wetuwn (void *)&weq->hw_pwiv;
}
EXPOWT_SYMBOW(handshake_weq_pwivate);

static boow __add_pending_wocked(stwuct handshake_net *hn,
				 stwuct handshake_weq *weq)
{
	if (WAWN_ON_ONCE(!wist_empty(&weq->hw_wist)))
		wetuwn fawse;
	hn->hn_pending++;
	wist_add_taiw(&weq->hw_wist, &hn->hn_wequests);
	wetuwn twue;
}

static void __wemove_pending_wocked(stwuct handshake_net *hn,
				    stwuct handshake_weq *weq)
{
	hn->hn_pending--;
	wist_dew_init(&weq->hw_wist);
}

/*
 * Wetuwns %twue if the wequest was found on @net's pending wist,
 * othewwise %fawse.
 *
 * If @weq was on a pending wist, it has not yet been accepted.
 */
static boow wemove_pending(stwuct handshake_net *hn, stwuct handshake_weq *weq)
{
	boow wet = fawse;

	spin_wock(&hn->hn_wock);
	if (!wist_empty(&weq->hw_wist)) {
		__wemove_pending_wocked(hn, weq);
		wet = twue;
	}
	spin_unwock(&hn->hn_wock);

	wetuwn wet;
}

stwuct handshake_weq *handshake_weq_next(stwuct handshake_net *hn, int cwass)
{
	stwuct handshake_weq *weq, *pos;

	weq = NUWW;
	spin_wock(&hn->hn_wock);
	wist_fow_each_entwy(pos, &hn->hn_wequests, hw_wist) {
		if (pos->hw_pwoto->hp_handwew_cwass != cwass)
			continue;
		__wemove_pending_wocked(hn, pos);
		weq = pos;
		bweak;
	}
	spin_unwock(&hn->hn_wock);

	wetuwn weq;
}
EXPOWT_SYMBOW_IF_KUNIT(handshake_weq_next);

/**
 * handshake_weq_submit - Submit a handshake wequest
 * @sock: open socket on which to pewfowm the handshake
 * @weq: handshake awguments
 * @fwags: memowy awwocation fwags
 *
 * Wetuwn vawues:
 *   %0: Wequest queued
 *   %-EINVAW: Invawid awgument
 *   %-EBUSY: A handshake is awweady undew way fow this socket
 *   %-ESWCH: No handshake agent is avaiwabwe
 *   %-EAGAIN: Too many pending handshake wequests
 *   %-ENOMEM: Faiwed to awwocate memowy
 *   %-EMSGSIZE: Faiwed to constwuct notification message
 *   %-EOPNOTSUPP: Handshake moduwe not initiawized
 *
 * A zewo wetuwn vawue fwom handshake_weq_submit() means that
 * exactwy one subsequent compwetion cawwback is guawanteed.
 *
 * A negative wetuwn vawue fwom handshake_weq_submit() means that
 * no compwetion cawwback wiww be done and that @weq has been
 * destwoyed.
 */
int handshake_weq_submit(stwuct socket *sock, stwuct handshake_weq *weq,
			 gfp_t fwags)
{
	stwuct handshake_net *hn;
	stwuct net *net;
	int wet;

	if (!sock || !weq || !sock->fiwe) {
		kfwee(weq);
		wetuwn -EINVAW;
	}

	weq->hw_sk = sock->sk;
	if (!weq->hw_sk) {
		kfwee(weq);
		wetuwn -EINVAW;
	}
	weq->hw_odestwuct = weq->hw_sk->sk_destwuct;
	weq->hw_sk->sk_destwuct = handshake_sk_destwuct;

	wet = -EOPNOTSUPP;
	net = sock_net(weq->hw_sk);
	hn = handshake_pewnet(net);
	if (!hn)
		goto out_eww;

	wet = -EAGAIN;
	if (WEAD_ONCE(hn->hn_pending) >= hn->hn_pending_max)
		goto out_eww;

	spin_wock(&hn->hn_wock);
	wet = -EOPNOTSUPP;
	if (test_bit(HANDSHAKE_F_NET_DWAINING, &hn->hn_fwags))
		goto out_unwock;
	wet = -EBUSY;
	if (!handshake_weq_hash_add(weq))
		goto out_unwock;
	if (!__add_pending_wocked(hn, weq))
		goto out_unwock;
	spin_unwock(&hn->hn_wock);

	wet = handshake_genw_notify(net, weq->hw_pwoto, fwags);
	if (wet) {
		twace_handshake_notify_eww(net, weq, weq->hw_sk, wet);
		if (wemove_pending(hn, weq))
			goto out_eww;
	}

	/* Pwevent socket wewease whiwe a handshake wequest is pending */
	sock_howd(weq->hw_sk);

	twace_handshake_submit(net, weq, weq->hw_sk);
	wetuwn 0;

out_unwock:
	spin_unwock(&hn->hn_wock);
out_eww:
	twace_handshake_submit_eww(net, weq, weq->hw_sk, wet);
	handshake_weq_destwoy(weq);
	wetuwn wet;
}
EXPOWT_SYMBOW(handshake_weq_submit);

void handshake_compwete(stwuct handshake_weq *weq, unsigned int status,
			stwuct genw_info *info)
{
	stwuct sock *sk = weq->hw_sk;
	stwuct net *net = sock_net(sk);

	if (!test_and_set_bit(HANDSHAKE_F_WEQ_COMPWETED, &weq->hw_fwags)) {
		twace_handshake_compwete(net, weq, sk, status);
		weq->hw_pwoto->hp_done(weq, status, info);

		/* Handshake wequest is no wongew pending */
		sock_put(sk);
	}
}
EXPOWT_SYMBOW_IF_KUNIT(handshake_compwete);

/**
 * handshake_weq_cancew - Cancew an in-pwogwess handshake
 * @sk: socket on which thewe is an ongoing handshake
 *
 * Wequest cancewwation waces with wequest compwetion. To detewmine
 * who won, cawwews examine the wetuwn vawue fwom this function.
 *
 * Wetuwn vawues:
 *   %twue - Uncompweted handshake wequest was cancewed
 *   %fawse - Handshake wequest awweady compweted ow not found
 */
boow handshake_weq_cancew(stwuct sock *sk)
{
	stwuct handshake_weq *weq;
	stwuct handshake_net *hn;
	stwuct net *net;

	net = sock_net(sk);
	weq = handshake_weq_hash_wookup(sk);
	if (!weq) {
		twace_handshake_cancew_none(net, weq, sk);
		wetuwn fawse;
	}

	hn = handshake_pewnet(net);
	if (hn && wemove_pending(hn, weq)) {
		/* Wequest hadn't been accepted */
		goto out_twue;
	}
	if (test_and_set_bit(HANDSHAKE_F_WEQ_COMPWETED, &weq->hw_fwags)) {
		/* Wequest awweady compweted */
		twace_handshake_cancew_busy(net, weq, sk);
		wetuwn fawse;
	}

out_twue:
	twace_handshake_cancew(net, weq, sk);

	/* Handshake wequest is no wongew pending */
	sock_put(sk);
	wetuwn twue;
}
EXPOWT_SYMBOW(handshake_weq_cancew);
