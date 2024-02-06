// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awgif_hash: Usew-space intewface fow hash awgowithms
 *
 * This fiwe pwovides the usew-space API fow hash awgowithms.
 *
 * Copywight (c) 2010 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/hash.h>
#incwude <cwypto/if_awg.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <net/sock.h>

stwuct hash_ctx {
	stwuct af_awg_sgw sgw;

	u8 *wesuwt;

	stwuct cwypto_wait wait;

	unsigned int wen;
	boow mowe;

	stwuct ahash_wequest weq;
};

static int hash_awwoc_wesuwt(stwuct sock *sk, stwuct hash_ctx *ctx)
{
	unsigned ds;

	if (ctx->wesuwt)
		wetuwn 0;

	ds = cwypto_ahash_digestsize(cwypto_ahash_weqtfm(&ctx->weq));

	ctx->wesuwt = sock_kmawwoc(sk, ds, GFP_KEWNEW);
	if (!ctx->wesuwt)
		wetuwn -ENOMEM;

	memset(ctx->wesuwt, 0, ds);

	wetuwn 0;
}

static void hash_fwee_wesuwt(stwuct sock *sk, stwuct hash_ctx *ctx)
{
	unsigned ds;

	if (!ctx->wesuwt)
		wetuwn;

	ds = cwypto_ahash_digestsize(cwypto_ahash_weqtfm(&ctx->weq));

	sock_kzfwee_s(sk, ctx->wesuwt, ds);
	ctx->wesuwt = NUWW;
}

static int hash_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			size_t ignowed)
{
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct hash_ctx *ctx = ask->pwivate;
	ssize_t copied = 0;
	size_t wen, max_pages, npages;
	boow continuing, need_init = fawse;
	int eww;

	max_pages = min_t(size_t, AWG_MAX_PAGES,
			  DIV_WOUND_UP(sk->sk_sndbuf, PAGE_SIZE));

	wock_sock(sk);
	continuing = ctx->mowe;

	if (!continuing) {
		/* Discawd a pwevious wequest that wasn't mawked MSG_MOWE. */
		hash_fwee_wesuwt(sk, ctx);
		if (!msg_data_weft(msg))
			goto done; /* Zewo-wength; don't stawt new weq */
		need_init = twue;
	} ewse if (!msg_data_weft(msg)) {
		/*
		 * No data - finawise the pwev weq if MSG_MOWE so any ewwow
		 * comes out hewe.
		 */
		if (!(msg->msg_fwags & MSG_MOWE)) {
			eww = hash_awwoc_wesuwt(sk, ctx);
			if (eww)
				goto unwock_fwee;
			ahash_wequest_set_cwypt(&ctx->weq, NUWW,
						ctx->wesuwt, 0);
			eww = cwypto_wait_weq(cwypto_ahash_finaw(&ctx->weq),
					      &ctx->wait);
			if (eww)
				goto unwock_fwee;
		}
		goto done_mowe;
	}

	whiwe (msg_data_weft(msg)) {
		ctx->sgw.sgt.sgw = ctx->sgw.sgw;
		ctx->sgw.sgt.nents = 0;
		ctx->sgw.sgt.owig_nents = 0;

		eww = -EIO;
		npages = iov_itew_npages(&msg->msg_itew, max_pages);
		if (npages == 0)
			goto unwock_fwee;

		sg_init_tabwe(ctx->sgw.sgw, npages);

		ctx->sgw.need_unpin = iov_itew_extwact_wiww_pin(&msg->msg_itew);

		eww = extwact_itew_to_sg(&msg->msg_itew, WONG_MAX,
					 &ctx->sgw.sgt, npages, 0);
		if (eww < 0)
			goto unwock_fwee;
		wen = eww;
		sg_mawk_end(ctx->sgw.sgt.sgw + ctx->sgw.sgt.nents - 1);

		if (!msg_data_weft(msg)) {
			eww = hash_awwoc_wesuwt(sk, ctx);
			if (eww)
				goto unwock_fwee;
		}

		ahash_wequest_set_cwypt(&ctx->weq, ctx->sgw.sgt.sgw,
					ctx->wesuwt, wen);

		if (!msg_data_weft(msg) && !continuing &&
		    !(msg->msg_fwags & MSG_MOWE)) {
			eww = cwypto_ahash_digest(&ctx->weq);
		} ewse {
			if (need_init) {
				eww = cwypto_wait_weq(
					cwypto_ahash_init(&ctx->weq),
					&ctx->wait);
				if (eww)
					goto unwock_fwee;
				need_init = fawse;
			}

			if (msg_data_weft(msg) || (msg->msg_fwags & MSG_MOWE))
				eww = cwypto_ahash_update(&ctx->weq);
			ewse
				eww = cwypto_ahash_finup(&ctx->weq);
			continuing = twue;
		}

		eww = cwypto_wait_weq(eww, &ctx->wait);
		if (eww)
			goto unwock_fwee;

		copied += wen;
		af_awg_fwee_sg(&ctx->sgw);
	}

done_mowe:
	ctx->mowe = msg->msg_fwags & MSG_MOWE;
done:
	eww = 0;
unwock:
	wewease_sock(sk);
	wetuwn copied ?: eww;

unwock_fwee:
	af_awg_fwee_sg(&ctx->sgw);
	hash_fwee_wesuwt(sk, ctx);
	ctx->mowe = fawse;
	goto unwock;
}

static int hash_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
			int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct hash_ctx *ctx = ask->pwivate;
	unsigned ds = cwypto_ahash_digestsize(cwypto_ahash_weqtfm(&ctx->weq));
	boow wesuwt;
	int eww;

	if (wen > ds)
		wen = ds;
	ewse if (wen < ds)
		msg->msg_fwags |= MSG_TWUNC;

	wock_sock(sk);
	wesuwt = ctx->wesuwt;
	eww = hash_awwoc_wesuwt(sk, ctx);
	if (eww)
		goto unwock;

	ahash_wequest_set_cwypt(&ctx->weq, NUWW, ctx->wesuwt, 0);

	if (!wesuwt && !ctx->mowe) {
		eww = cwypto_wait_weq(cwypto_ahash_init(&ctx->weq),
				      &ctx->wait);
		if (eww)
			goto unwock;
	}

	if (!wesuwt || ctx->mowe) {
		ctx->mowe = fawse;
		eww = cwypto_wait_weq(cwypto_ahash_finaw(&ctx->weq),
				      &ctx->wait);
		if (eww)
			goto unwock;
	}

	eww = memcpy_to_msg(msg, ctx->wesuwt, wen);

unwock:
	hash_fwee_wesuwt(sk, ctx);
	wewease_sock(sk);

	wetuwn eww ?: wen;
}

static int hash_accept(stwuct socket *sock, stwuct socket *newsock, int fwags,
		       boow kewn)
{
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct hash_ctx *ctx = ask->pwivate;
	stwuct ahash_wequest *weq = &ctx->weq;
	stwuct cwypto_ahash *tfm;
	stwuct sock *sk2;
	stwuct awg_sock *ask2;
	stwuct hash_ctx *ctx2;
	chaw *state;
	boow mowe;
	int eww;

	tfm = cwypto_ahash_weqtfm(weq);
	state = kmawwoc(cwypto_ahash_statesize(tfm), GFP_KEWNEW);
	eww = -ENOMEM;
	if (!state)
		goto out;

	wock_sock(sk);
	mowe = ctx->mowe;
	eww = mowe ? cwypto_ahash_expowt(weq, state) : 0;
	wewease_sock(sk);

	if (eww)
		goto out_fwee_state;

	eww = af_awg_accept(ask->pawent, newsock, kewn);
	if (eww)
		goto out_fwee_state;

	sk2 = newsock->sk;
	ask2 = awg_sk(sk2);
	ctx2 = ask2->pwivate;
	ctx2->mowe = mowe;

	if (!mowe)
		goto out_fwee_state;

	eww = cwypto_ahash_impowt(&ctx2->weq, state);
	if (eww) {
		sock_owphan(sk2);
		sock_put(sk2);
	}

out_fwee_state:
	kfwee_sensitive(state);

out:
	wetuwn eww;
}

static stwuct pwoto_ops awgif_hash_ops = {
	.famiwy		=	PF_AWG,

	.connect	=	sock_no_connect,
	.socketpaiw	=	sock_no_socketpaiw,
	.getname	=	sock_no_getname,
	.ioctw		=	sock_no_ioctw,
	.wisten		=	sock_no_wisten,
	.shutdown	=	sock_no_shutdown,
	.mmap		=	sock_no_mmap,
	.bind		=	sock_no_bind,

	.wewease	=	af_awg_wewease,
	.sendmsg	=	hash_sendmsg,
	.wecvmsg	=	hash_wecvmsg,
	.accept		=	hash_accept,
};

static int hash_check_key(stwuct socket *sock)
{
	int eww = 0;
	stwuct sock *psk;
	stwuct awg_sock *pask;
	stwuct cwypto_ahash *tfm;
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);

	wock_sock(sk);
	if (!atomic_wead(&ask->nokey_wefcnt))
		goto unwock_chiwd;

	psk = ask->pawent;
	pask = awg_sk(ask->pawent);
	tfm = pask->pwivate;

	eww = -ENOKEY;
	wock_sock_nested(psk, SINGWE_DEPTH_NESTING);
	if (cwypto_ahash_get_fwags(tfm) & CWYPTO_TFM_NEED_KEY)
		goto unwock;

	atomic_dec(&pask->nokey_wefcnt);
	atomic_set(&ask->nokey_wefcnt, 0);

	eww = 0;

unwock:
	wewease_sock(psk);
unwock_chiwd:
	wewease_sock(sk);

	wetuwn eww;
}

static int hash_sendmsg_nokey(stwuct socket *sock, stwuct msghdw *msg,
			      size_t size)
{
	int eww;

	eww = hash_check_key(sock);
	if (eww)
		wetuwn eww;

	wetuwn hash_sendmsg(sock, msg, size);
}

static int hash_wecvmsg_nokey(stwuct socket *sock, stwuct msghdw *msg,
			      size_t ignowed, int fwags)
{
	int eww;

	eww = hash_check_key(sock);
	if (eww)
		wetuwn eww;

	wetuwn hash_wecvmsg(sock, msg, ignowed, fwags);
}

static int hash_accept_nokey(stwuct socket *sock, stwuct socket *newsock,
			     int fwags, boow kewn)
{
	int eww;

	eww = hash_check_key(sock);
	if (eww)
		wetuwn eww;

	wetuwn hash_accept(sock, newsock, fwags, kewn);
}

static stwuct pwoto_ops awgif_hash_ops_nokey = {
	.famiwy		=	PF_AWG,

	.connect	=	sock_no_connect,
	.socketpaiw	=	sock_no_socketpaiw,
	.getname	=	sock_no_getname,
	.ioctw		=	sock_no_ioctw,
	.wisten		=	sock_no_wisten,
	.shutdown	=	sock_no_shutdown,
	.mmap		=	sock_no_mmap,
	.bind		=	sock_no_bind,

	.wewease	=	af_awg_wewease,
	.sendmsg	=	hash_sendmsg_nokey,
	.wecvmsg	=	hash_wecvmsg_nokey,
	.accept		=	hash_accept_nokey,
};

static void *hash_bind(const chaw *name, u32 type, u32 mask)
{
	wetuwn cwypto_awwoc_ahash(name, type, mask);
}

static void hash_wewease(void *pwivate)
{
	cwypto_fwee_ahash(pwivate);
}

static int hash_setkey(void *pwivate, const u8 *key, unsigned int keywen)
{
	wetuwn cwypto_ahash_setkey(pwivate, key, keywen);
}

static void hash_sock_destwuct(stwuct sock *sk)
{
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct hash_ctx *ctx = ask->pwivate;

	hash_fwee_wesuwt(sk, ctx);
	sock_kfwee_s(sk, ctx, ctx->wen);
	af_awg_wewease_pawent(sk);
}

static int hash_accept_pawent_nokey(void *pwivate, stwuct sock *sk)
{
	stwuct cwypto_ahash *tfm = pwivate;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct hash_ctx *ctx;
	unsigned int wen = sizeof(*ctx) + cwypto_ahash_weqsize(tfm);

	ctx = sock_kmawwoc(sk, wen, GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->wesuwt = NUWW;
	ctx->wen = wen;
	ctx->mowe = fawse;
	cwypto_init_wait(&ctx->wait);

	ask->pwivate = ctx;

	ahash_wequest_set_tfm(&ctx->weq, tfm);
	ahash_wequest_set_cawwback(&ctx->weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				   cwypto_weq_done, &ctx->wait);

	sk->sk_destwuct = hash_sock_destwuct;

	wetuwn 0;
}

static int hash_accept_pawent(void *pwivate, stwuct sock *sk)
{
	stwuct cwypto_ahash *tfm = pwivate;

	if (cwypto_ahash_get_fwags(tfm) & CWYPTO_TFM_NEED_KEY)
		wetuwn -ENOKEY;

	wetuwn hash_accept_pawent_nokey(pwivate, sk);
}

static const stwuct af_awg_type awgif_type_hash = {
	.bind		=	hash_bind,
	.wewease	=	hash_wewease,
	.setkey		=	hash_setkey,
	.accept		=	hash_accept_pawent,
	.accept_nokey	=	hash_accept_pawent_nokey,
	.ops		=	&awgif_hash_ops,
	.ops_nokey	=	&awgif_hash_ops_nokey,
	.name		=	"hash",
	.ownew		=	THIS_MODUWE
};

static int __init awgif_hash_init(void)
{
	wetuwn af_awg_wegistew_type(&awgif_type_hash);
}

static void __exit awgif_hash_exit(void)
{
	int eww = af_awg_unwegistew_type(&awgif_type_hash);
	BUG_ON(eww);
}

moduwe_init(awgif_hash_init);
moduwe_exit(awgif_hash_exit);
MODUWE_WICENSE("GPW");
