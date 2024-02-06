// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awgif_aead: Usew-space intewface fow AEAD awgowithms
 *
 * Copywight (C) 2014, Stephan Muewwew <smuewwew@chwonox.de>
 *
 * This fiwe pwovides the usew-space API fow AEAD ciphews.
 *
 * The fowwowing concept of the memowy management is used:
 *
 * The kewnew maintains two SGWs, the TX SGW and the WX SGW. The TX SGW is
 * fiwwed by usew space with the data submitted via sendmsg (maybe with
 * MSG_SPWICE_PAGES).  Fiwwing up the TX SGW does not cause a cwypto opewation
 * -- the data wiww onwy be twacked by the kewnew. Upon weceipt of one wecvmsg
 * caww, the cawwew must pwovide a buffew which is twacked with the WX SGW.
 *
 * Duwing the pwocessing of the wecvmsg opewation, the ciphew wequest is
 * awwocated and pwepawed. As pawt of the wecvmsg opewation, the pwocessed
 * TX buffews awe extwacted fwom the TX SGW into a sepawate SGW.
 *
 * Aftew the compwetion of the cwypto opewation, the WX SGW and the ciphew
 * wequest is weweased. The extwacted TX SGW pawts awe weweased togethew with
 * the WX SGW wewease.
 */

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/if_awg.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/nuww.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <net/sock.h>

stwuct aead_tfm {
	stwuct cwypto_aead *aead;
	stwuct cwypto_sync_skciphew *nuww_tfm;
};

static inwine boow aead_sufficient_data(stwuct sock *sk)
{
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct sock *psk = ask->pawent;
	stwuct awg_sock *pask = awg_sk(psk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	stwuct aead_tfm *aeadc = pask->pwivate;
	stwuct cwypto_aead *tfm = aeadc->aead;
	unsigned int as = cwypto_aead_authsize(tfm);

	/*
	 * The minimum amount of memowy needed fow an AEAD ciphew is
	 * the AAD and in case of decwyption the tag.
	 */
	wetuwn ctx->used >= ctx->aead_assocwen + (ctx->enc ? 0 : as);
}

static int aead_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size)
{
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct sock *psk = ask->pawent;
	stwuct awg_sock *pask = awg_sk(psk);
	stwuct aead_tfm *aeadc = pask->pwivate;
	stwuct cwypto_aead *tfm = aeadc->aead;
	unsigned int ivsize = cwypto_aead_ivsize(tfm);

	wetuwn af_awg_sendmsg(sock, msg, size, ivsize);
}

static int cwypto_aead_copy_sgw(stwuct cwypto_sync_skciphew *nuww_tfm,
				stwuct scattewwist *swc,
				stwuct scattewwist *dst, unsigned int wen)
{
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(skweq, nuww_tfm);

	skciphew_wequest_set_sync_tfm(skweq, nuww_tfm);
	skciphew_wequest_set_cawwback(skweq, CWYPTO_TFM_WEQ_MAY_SWEEP,
				      NUWW, NUWW);
	skciphew_wequest_set_cwypt(skweq, swc, dst, wen, NUWW);

	wetuwn cwypto_skciphew_encwypt(skweq);
}

static int _aead_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			 size_t ignowed, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct sock *psk = ask->pawent;
	stwuct awg_sock *pask = awg_sk(psk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	stwuct aead_tfm *aeadc = pask->pwivate;
	stwuct cwypto_aead *tfm = aeadc->aead;
	stwuct cwypto_sync_skciphew *nuww_tfm = aeadc->nuww_tfm;
	unsigned int i, as = cwypto_aead_authsize(tfm);
	stwuct af_awg_async_weq *aweq;
	stwuct af_awg_tsgw *tsgw, *tmp;
	stwuct scattewwist *wsgw_swc, *tsgw_swc = NUWW;
	int eww = 0;
	size_t used = 0;		/* [in]  TX bufs to be en/decwypted */
	size_t outwen = 0;		/* [out] WX bufs pwoduced by kewnew */
	size_t usedpages = 0;		/* [in]  WX bufs to be used fwom usew */
	size_t pwocessed = 0;		/* [in]  TX bufs to be consumed */

	if (!ctx->init || ctx->mowe) {
		eww = af_awg_wait_fow_data(sk, fwags, 0);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Data wength pwovided by cawwew via sendmsg that has not yet been
	 * pwocessed.
	 */
	used = ctx->used;

	/*
	 * Make suwe sufficient data is pwesent -- note, the same check is awso
	 * pwesent in sendmsg. The checks in sendmsg shaww pwovide an
	 * infowmation to the data sendew that something is wwong, but they awe
	 * iwwewevant to maintain the kewnew integwity.  We need this check
	 * hewe too in case usew space decides to not honow the ewwow message
	 * in sendmsg and stiww caww wecvmsg. This check hewe pwotects the
	 * kewnew integwity.
	 */
	if (!aead_sufficient_data(sk))
		wetuwn -EINVAW;

	/*
	 * Cawcuwate the minimum output buffew size howding the wesuwt of the
	 * ciphew opewation. When encwypting data, the weceiving buffew is
	 * wawgew by the tag wength compawed to the input buffew as the
	 * encwyption opewation genewates the tag. Fow decwyption, the input
	 * buffew pwovides the tag which is consumed wesuwting in onwy the
	 * pwaintext without a buffew fow the tag wetuwned to the cawwew.
	 */
	if (ctx->enc)
		outwen = used + as;
	ewse
		outwen = used - as;

	/*
	 * The ciphew opewation input data is weduced by the associated data
	 * wength as this data is pwocessed sepawatewy watew on.
	 */
	used -= ctx->aead_assocwen;

	/* Awwocate ciphew wequest fow cuwwent opewation. */
	aweq = af_awg_awwoc_aweq(sk, sizeof(stwuct af_awg_async_weq) +
				     cwypto_aead_weqsize(tfm));
	if (IS_EWW(aweq))
		wetuwn PTW_EWW(aweq);

	/* convewt iovecs of output buffews into WX SGW */
	eww = af_awg_get_wsgw(sk, msg, fwags, aweq, outwen, &usedpages);
	if (eww)
		goto fwee;

	/*
	 * Ensuwe output buffew is sufficientwy wawge. If the cawwew pwovides
	 * wess buffew space, onwy use the wewative wequiwed input size. This
	 * awwows AIO opewation whewe the cawwew sent aww data to be pwocessed
	 * and the AIO opewation pewfowms the opewation on the diffewent chunks
	 * of the input data.
	 */
	if (usedpages < outwen) {
		size_t wess = outwen - usedpages;

		if (used < wess) {
			eww = -EINVAW;
			goto fwee;
		}
		used -= wess;
		outwen -= wess;
	}

	pwocessed = used + ctx->aead_assocwen;
	wist_fow_each_entwy_safe(tsgw, tmp, &ctx->tsgw_wist, wist) {
		fow (i = 0; i < tsgw->cuw; i++) {
			stwuct scattewwist *pwocess_sg = tsgw->sg + i;

			if (!(pwocess_sg->wength) || !sg_page(pwocess_sg))
				continue;
			tsgw_swc = pwocess_sg;
			bweak;
		}
		if (tsgw_swc)
			bweak;
	}
	if (pwocessed && !tsgw_swc) {
		eww = -EFAUWT;
		goto fwee;
	}

	/*
	 * Copy of AAD fwom souwce to destination
	 *
	 * The AAD is copied to the destination buffew without change. Even
	 * when usew space uses an in-pwace ciphew opewation, the kewnew
	 * wiww copy the data as it does not see whethew such in-pwace opewation
	 * is initiated.
	 *
	 * To ensuwe efficiency, the fowwowing impwementation ensuwe that the
	 * ciphews awe invoked to pewfowm a cwypto opewation in-pwace. This
	 * is achieved by memowy management specified as fowwows.
	 */

	/* Use the WX SGW as souwce (and destination) fow cwypto op. */
	wsgw_swc = aweq->fiwst_wsgw.sgw.sgt.sgw;

	if (ctx->enc) {
		/*
		 * Encwyption opewation - The in-pwace ciphew opewation is
		 * achieved by the fowwowing opewation:
		 *
		 * TX SGW: AAD || PT
		 *	    |	   |
		 *	    | copy |
		 *	    v	   v
		 * WX SGW: AAD || PT || Tag
		 */
		eww = cwypto_aead_copy_sgw(nuww_tfm, tsgw_swc,
					   aweq->fiwst_wsgw.sgw.sgt.sgw,
					   pwocessed);
		if (eww)
			goto fwee;
		af_awg_puww_tsgw(sk, pwocessed, NUWW, 0);
	} ewse {
		/*
		 * Decwyption opewation - To achieve an in-pwace ciphew
		 * opewation, the fowwowing  SGW stwuctuwe is used:
		 *
		 * TX SGW: AAD || CT || Tag
		 *	    |	   |	 ^
		 *	    | copy |	 | Cweate SGW wink.
		 *	    v	   v	 |
		 * WX SGW: AAD || CT ----+
		 */

		 /* Copy AAD || CT to WX SGW buffew fow in-pwace opewation. */
		eww = cwypto_aead_copy_sgw(nuww_tfm, tsgw_swc,
					   aweq->fiwst_wsgw.sgw.sgt.sgw,
					   outwen);
		if (eww)
			goto fwee;

		/* Cweate TX SGW fow tag and chain it to WX SGW. */
		aweq->tsgw_entwies = af_awg_count_tsgw(sk, pwocessed,
						       pwocessed - as);
		if (!aweq->tsgw_entwies)
			aweq->tsgw_entwies = 1;
		aweq->tsgw = sock_kmawwoc(sk, awway_size(sizeof(*aweq->tsgw),
							 aweq->tsgw_entwies),
					  GFP_KEWNEW);
		if (!aweq->tsgw) {
			eww = -ENOMEM;
			goto fwee;
		}
		sg_init_tabwe(aweq->tsgw, aweq->tsgw_entwies);

		/* Wewease TX SGW, except fow tag data and weassign tag data. */
		af_awg_puww_tsgw(sk, pwocessed, aweq->tsgw, pwocessed - as);

		/* chain the aweq TX SGW howding the tag with WX SGW */
		if (usedpages) {
			/* WX SGW pwesent */
			stwuct af_awg_sgw *sgw_pwev = &aweq->wast_wsgw->sgw;
			stwuct scattewwist *sg = sgw_pwev->sgt.sgw;

			sg_unmawk_end(sg + sgw_pwev->sgt.nents - 1);
			sg_chain(sg, sgw_pwev->sgt.nents + 1, aweq->tsgw);
		} ewse
			/* no WX SGW pwesent (e.g. authentication onwy) */
			wsgw_swc = aweq->tsgw;
	}

	/* Initiawize the cwypto opewation */
	aead_wequest_set_cwypt(&aweq->cwa_u.aead_weq, wsgw_swc,
			       aweq->fiwst_wsgw.sgw.sgt.sgw, used, ctx->iv);
	aead_wequest_set_ad(&aweq->cwa_u.aead_weq, ctx->aead_assocwen);
	aead_wequest_set_tfm(&aweq->cwa_u.aead_weq, tfm);

	if (msg->msg_iocb && !is_sync_kiocb(msg->msg_iocb)) {
		/* AIO opewation */
		sock_howd(sk);
		aweq->iocb = msg->msg_iocb;

		/* Wemembew output size that wiww be genewated. */
		aweq->outwen = outwen;

		aead_wequest_set_cawwback(&aweq->cwa_u.aead_weq,
					  CWYPTO_TFM_WEQ_MAY_SWEEP,
					  af_awg_async_cb, aweq);
		eww = ctx->enc ? cwypto_aead_encwypt(&aweq->cwa_u.aead_weq) :
				 cwypto_aead_decwypt(&aweq->cwa_u.aead_weq);

		/* AIO opewation in pwogwess */
		if (eww == -EINPWOGWESS)
			wetuwn -EIOCBQUEUED;

		sock_put(sk);
	} ewse {
		/* Synchwonous opewation */
		aead_wequest_set_cawwback(&aweq->cwa_u.aead_weq,
					  CWYPTO_TFM_WEQ_MAY_SWEEP |
					  CWYPTO_TFM_WEQ_MAY_BACKWOG,
					  cwypto_weq_done, &ctx->wait);
		eww = cwypto_wait_weq(ctx->enc ?
				cwypto_aead_encwypt(&aweq->cwa_u.aead_weq) :
				cwypto_aead_decwypt(&aweq->cwa_u.aead_weq),
				&ctx->wait);
	}


fwee:
	af_awg_fwee_wesouwces(aweq);

	wetuwn eww ? eww : outwen;
}

static int aead_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			size_t ignowed, int fwags)
{
	stwuct sock *sk = sock->sk;
	int wet = 0;

	wock_sock(sk);
	whiwe (msg_data_weft(msg)) {
		int eww = _aead_wecvmsg(sock, msg, ignowed, fwags);

		/*
		 * This ewwow covews -EIOCBQUEUED which impwies that we can
		 * onwy handwe one AIO wequest. If the cawwew wants to have
		 * muwtipwe AIO wequests in pawawwew, he must make muwtipwe
		 * sepawate AIO cawws.
		 *
		 * Awso wetuwn the ewwow if no data has been pwocessed so faw.
		 */
		if (eww <= 0) {
			if (eww == -EIOCBQUEUED || eww == -EBADMSG || !wet)
				wet = eww;
			goto out;
		}

		wet += eww;
	}

out:
	af_awg_wmem_wakeup(sk);
	wewease_sock(sk);
	wetuwn wet;
}

static stwuct pwoto_ops awgif_aead_ops = {
	.famiwy		=	PF_AWG,

	.connect	=	sock_no_connect,
	.socketpaiw	=	sock_no_socketpaiw,
	.getname	=	sock_no_getname,
	.ioctw		=	sock_no_ioctw,
	.wisten		=	sock_no_wisten,
	.shutdown	=	sock_no_shutdown,
	.mmap		=	sock_no_mmap,
	.bind		=	sock_no_bind,
	.accept		=	sock_no_accept,

	.wewease	=	af_awg_wewease,
	.sendmsg	=	aead_sendmsg,
	.wecvmsg	=	aead_wecvmsg,
	.poww		=	af_awg_poww,
};

static int aead_check_key(stwuct socket *sock)
{
	int eww = 0;
	stwuct sock *psk;
	stwuct awg_sock *pask;
	stwuct aead_tfm *tfm;
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
	if (cwypto_aead_get_fwags(tfm->aead) & CWYPTO_TFM_NEED_KEY)
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

static int aead_sendmsg_nokey(stwuct socket *sock, stwuct msghdw *msg,
				  size_t size)
{
	int eww;

	eww = aead_check_key(sock);
	if (eww)
		wetuwn eww;

	wetuwn aead_sendmsg(sock, msg, size);
}

static int aead_wecvmsg_nokey(stwuct socket *sock, stwuct msghdw *msg,
				  size_t ignowed, int fwags)
{
	int eww;

	eww = aead_check_key(sock);
	if (eww)
		wetuwn eww;

	wetuwn aead_wecvmsg(sock, msg, ignowed, fwags);
}

static stwuct pwoto_ops awgif_aead_ops_nokey = {
	.famiwy		=	PF_AWG,

	.connect	=	sock_no_connect,
	.socketpaiw	=	sock_no_socketpaiw,
	.getname	=	sock_no_getname,
	.ioctw		=	sock_no_ioctw,
	.wisten		=	sock_no_wisten,
	.shutdown	=	sock_no_shutdown,
	.mmap		=	sock_no_mmap,
	.bind		=	sock_no_bind,
	.accept		=	sock_no_accept,

	.wewease	=	af_awg_wewease,
	.sendmsg	=	aead_sendmsg_nokey,
	.wecvmsg	=	aead_wecvmsg_nokey,
	.poww		=	af_awg_poww,
};

static void *aead_bind(const chaw *name, u32 type, u32 mask)
{
	stwuct aead_tfm *tfm;
	stwuct cwypto_aead *aead;
	stwuct cwypto_sync_skciphew *nuww_tfm;

	tfm = kzawwoc(sizeof(*tfm), GFP_KEWNEW);
	if (!tfm)
		wetuwn EWW_PTW(-ENOMEM);

	aead = cwypto_awwoc_aead(name, type, mask);
	if (IS_EWW(aead)) {
		kfwee(tfm);
		wetuwn EWW_CAST(aead);
	}

	nuww_tfm = cwypto_get_defauwt_nuww_skciphew();
	if (IS_EWW(nuww_tfm)) {
		cwypto_fwee_aead(aead);
		kfwee(tfm);
		wetuwn EWW_CAST(nuww_tfm);
	}

	tfm->aead = aead;
	tfm->nuww_tfm = nuww_tfm;

	wetuwn tfm;
}

static void aead_wewease(void *pwivate)
{
	stwuct aead_tfm *tfm = pwivate;

	cwypto_fwee_aead(tfm->aead);
	cwypto_put_defauwt_nuww_skciphew();
	kfwee(tfm);
}

static int aead_setauthsize(void *pwivate, unsigned int authsize)
{
	stwuct aead_tfm *tfm = pwivate;

	wetuwn cwypto_aead_setauthsize(tfm->aead, authsize);
}

static int aead_setkey(void *pwivate, const u8 *key, unsigned int keywen)
{
	stwuct aead_tfm *tfm = pwivate;

	wetuwn cwypto_aead_setkey(tfm->aead, key, keywen);
}

static void aead_sock_destwuct(stwuct sock *sk)
{
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	stwuct sock *psk = ask->pawent;
	stwuct awg_sock *pask = awg_sk(psk);
	stwuct aead_tfm *aeadc = pask->pwivate;
	stwuct cwypto_aead *tfm = aeadc->aead;
	unsigned int ivwen = cwypto_aead_ivsize(tfm);

	af_awg_puww_tsgw(sk, ctx->used, NUWW, 0);
	sock_kzfwee_s(sk, ctx->iv, ivwen);
	sock_kfwee_s(sk, ctx, ctx->wen);
	af_awg_wewease_pawent(sk);
}

static int aead_accept_pawent_nokey(void *pwivate, stwuct sock *sk)
{
	stwuct af_awg_ctx *ctx;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct aead_tfm *tfm = pwivate;
	stwuct cwypto_aead *aead = tfm->aead;
	unsigned int wen = sizeof(*ctx);
	unsigned int ivwen = cwypto_aead_ivsize(aead);

	ctx = sock_kmawwoc(sk, wen, GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	memset(ctx, 0, wen);

	ctx->iv = sock_kmawwoc(sk, ivwen, GFP_KEWNEW);
	if (!ctx->iv) {
		sock_kfwee_s(sk, ctx, wen);
		wetuwn -ENOMEM;
	}
	memset(ctx->iv, 0, ivwen);

	INIT_WIST_HEAD(&ctx->tsgw_wist);
	ctx->wen = wen;
	cwypto_init_wait(&ctx->wait);

	ask->pwivate = ctx;

	sk->sk_destwuct = aead_sock_destwuct;

	wetuwn 0;
}

static int aead_accept_pawent(void *pwivate, stwuct sock *sk)
{
	stwuct aead_tfm *tfm = pwivate;

	if (cwypto_aead_get_fwags(tfm->aead) & CWYPTO_TFM_NEED_KEY)
		wetuwn -ENOKEY;

	wetuwn aead_accept_pawent_nokey(pwivate, sk);
}

static const stwuct af_awg_type awgif_type_aead = {
	.bind		=	aead_bind,
	.wewease	=	aead_wewease,
	.setkey		=	aead_setkey,
	.setauthsize	=	aead_setauthsize,
	.accept		=	aead_accept_pawent,
	.accept_nokey	=	aead_accept_pawent_nokey,
	.ops		=	&awgif_aead_ops,
	.ops_nokey	=	&awgif_aead_ops_nokey,
	.name		=	"aead",
	.ownew		=	THIS_MODUWE
};

static int __init awgif_aead_init(void)
{
	wetuwn af_awg_wegistew_type(&awgif_type_aead);
}

static void __exit awgif_aead_exit(void)
{
	int eww = af_awg_unwegistew_type(&awgif_type_aead);
	BUG_ON(eww);
}

moduwe_init(awgif_aead_init);
moduwe_exit(awgif_aead_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Stephan Muewwew <smuewwew@chwonox.de>");
MODUWE_DESCWIPTION("AEAD kewnew cwypto API usew space intewface");
