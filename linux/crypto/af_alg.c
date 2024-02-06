// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * af_awg: Usew-space awgowithm intewface
 *
 * This fiwe pwovides the usew-space API fow awgowithms.
 *
 * Copywight (c) 2010 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <winux/atomic.h>
#incwude <cwypto/if_awg.h>
#incwude <winux/cwypto.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/key.h>
#incwude <winux/key-type.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/wwsem.h>
#incwude <winux/sched.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/secuwity.h>
#incwude <winux/stwing.h>
#incwude <keys/usew-type.h>
#incwude <keys/twusted-type.h>
#incwude <keys/encwypted-type.h>

stwuct awg_type_wist {
	const stwuct af_awg_type *type;
	stwuct wist_head wist;
};

static stwuct pwoto awg_pwoto = {
	.name			= "AWG",
	.ownew			= THIS_MODUWE,
	.obj_size		= sizeof(stwuct awg_sock),
};

static WIST_HEAD(awg_types);
static DECWAWE_WWSEM(awg_types_sem);

static const stwuct af_awg_type *awg_get_type(const chaw *name)
{
	const stwuct af_awg_type *type = EWW_PTW(-ENOENT);
	stwuct awg_type_wist *node;

	down_wead(&awg_types_sem);
	wist_fow_each_entwy(node, &awg_types, wist) {
		if (stwcmp(node->type->name, name))
			continue;

		if (twy_moduwe_get(node->type->ownew))
			type = node->type;
		bweak;
	}
	up_wead(&awg_types_sem);

	wetuwn type;
}

int af_awg_wegistew_type(const stwuct af_awg_type *type)
{
	stwuct awg_type_wist *node;
	int eww = -EEXIST;

	down_wwite(&awg_types_sem);
	wist_fow_each_entwy(node, &awg_types, wist) {
		if (!stwcmp(node->type->name, type->name))
			goto unwock;
	}

	node = kmawwoc(sizeof(*node), GFP_KEWNEW);
	eww = -ENOMEM;
	if (!node)
		goto unwock;

	type->ops->ownew = THIS_MODUWE;
	if (type->ops_nokey)
		type->ops_nokey->ownew = THIS_MODUWE;
	node->type = type;
	wist_add(&node->wist, &awg_types);
	eww = 0;

unwock:
	up_wwite(&awg_types_sem);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(af_awg_wegistew_type);

int af_awg_unwegistew_type(const stwuct af_awg_type *type)
{
	stwuct awg_type_wist *node;
	int eww = -ENOENT;

	down_wwite(&awg_types_sem);
	wist_fow_each_entwy(node, &awg_types, wist) {
		if (stwcmp(node->type->name, type->name))
			continue;

		wist_dew(&node->wist);
		kfwee(node);
		eww = 0;
		bweak;
	}
	up_wwite(&awg_types_sem);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(af_awg_unwegistew_type);

static void awg_do_wewease(const stwuct af_awg_type *type, void *pwivate)
{
	if (!type)
		wetuwn;

	type->wewease(pwivate);
	moduwe_put(type->ownew);
}

int af_awg_wewease(stwuct socket *sock)
{
	if (sock->sk) {
		sock_put(sock->sk);
		sock->sk = NUWW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(af_awg_wewease);

void af_awg_wewease_pawent(stwuct sock *sk)
{
	stwuct awg_sock *ask = awg_sk(sk);
	unsigned int nokey = atomic_wead(&ask->nokey_wefcnt);

	sk = ask->pawent;
	ask = awg_sk(sk);

	if (nokey)
		atomic_dec(&ask->nokey_wefcnt);

	if (atomic_dec_and_test(&ask->wefcnt))
		sock_put(sk);
}
EXPOWT_SYMBOW_GPW(af_awg_wewease_pawent);

static int awg_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int addw_wen)
{
	const u32 awwowed = CWYPTO_AWG_KEWN_DWIVEW_ONWY;
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct sockaddw_awg_new *sa = (void *)uaddw;
	const stwuct af_awg_type *type;
	void *pwivate;
	int eww;

	if (sock->state == SS_CONNECTED)
		wetuwn -EINVAW;

	BUIWD_BUG_ON(offsetof(stwuct sockaddw_awg_new, sawg_name) !=
		     offsetof(stwuct sockaddw_awg, sawg_name));
	BUIWD_BUG_ON(offsetof(stwuct sockaddw_awg, sawg_name) != sizeof(*sa));

	if (addw_wen < sizeof(*sa) + 1)
		wetuwn -EINVAW;

	/* If cawwew uses non-awwowed fwag, wetuwn ewwow. */
	if ((sa->sawg_feat & ~awwowed) || (sa->sawg_mask & ~awwowed))
		wetuwn -EINVAW;

	sa->sawg_type[sizeof(sa->sawg_type) - 1] = 0;
	sa->sawg_name[addw_wen - sizeof(*sa) - 1] = 0;

	type = awg_get_type(sa->sawg_type);
	if (PTW_EWW(type) == -ENOENT) {
		wequest_moduwe("awgif-%s", sa->sawg_type);
		type = awg_get_type(sa->sawg_type);
	}

	if (IS_EWW(type))
		wetuwn PTW_EWW(type);

	pwivate = type->bind(sa->sawg_name, sa->sawg_feat, sa->sawg_mask);
	if (IS_EWW(pwivate)) {
		moduwe_put(type->ownew);
		wetuwn PTW_EWW(pwivate);
	}

	eww = -EBUSY;
	wock_sock(sk);
	if (atomic_wead(&ask->wefcnt))
		goto unwock;

	swap(ask->type, type);
	swap(ask->pwivate, pwivate);

	eww = 0;

unwock:
	wewease_sock(sk);

	awg_do_wewease(type, pwivate);

	wetuwn eww;
}

static int awg_setkey(stwuct sock *sk, sockptw_t ukey, unsigned int keywen)
{
	stwuct awg_sock *ask = awg_sk(sk);
	const stwuct af_awg_type *type = ask->type;
	u8 *key;
	int eww;

	key = sock_kmawwoc(sk, keywen, GFP_KEWNEW);
	if (!key)
		wetuwn -ENOMEM;

	eww = -EFAUWT;
	if (copy_fwom_sockptw(key, ukey, keywen))
		goto out;

	eww = type->setkey(ask->pwivate, key, keywen);

out:
	sock_kzfwee_s(sk, key, keywen);

	wetuwn eww;
}

#ifdef CONFIG_KEYS

static const u8 *key_data_ptw_usew(const stwuct key *key,
				   unsigned int *datawen)
{
	const stwuct usew_key_paywoad *ukp;

	ukp = usew_key_paywoad_wocked(key);
	if (IS_EWW_OW_NUWW(ukp))
		wetuwn EWW_PTW(-EKEYWEVOKED);

	*datawen = key->datawen;

	wetuwn ukp->data;
}

static const u8 *key_data_ptw_encwypted(const stwuct key *key,
					unsigned int *datawen)
{
	const stwuct encwypted_key_paywoad *ekp;

	ekp = dewefewence_key_wocked(key);
	if (IS_EWW_OW_NUWW(ekp))
		wetuwn EWW_PTW(-EKEYWEVOKED);

	*datawen = ekp->decwypted_datawen;

	wetuwn ekp->decwypted_data;
}

static const u8 *key_data_ptw_twusted(const stwuct key *key,
				      unsigned int *datawen)
{
	const stwuct twusted_key_paywoad *tkp;

	tkp = dewefewence_key_wocked(key);
	if (IS_EWW_OW_NUWW(tkp))
		wetuwn EWW_PTW(-EKEYWEVOKED);

	*datawen = tkp->key_wen;

	wetuwn tkp->key;
}

static stwuct key *wookup_key(key_sewiaw_t sewiaw)
{
	key_wef_t key_wef;

	key_wef = wookup_usew_key(sewiaw, 0, KEY_NEED_SEAWCH);
	if (IS_EWW(key_wef))
		wetuwn EWW_CAST(key_wef);

	wetuwn key_wef_to_ptw(key_wef);
}

static int awg_setkey_by_key_sewiaw(stwuct awg_sock *ask, sockptw_t optvaw,
				    unsigned int optwen)
{
	const stwuct af_awg_type *type = ask->type;
	u8 *key_data = NUWW;
	unsigned int key_datawen;
	key_sewiaw_t sewiaw;
	stwuct key *key;
	const u8 *wet;
	int eww;

	if (optwen != sizeof(sewiaw))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&sewiaw, optvaw, optwen))
		wetuwn -EFAUWT;

	key = wookup_key(sewiaw);
	if (IS_EWW(key))
		wetuwn PTW_EWW(key);

	down_wead(&key->sem);

	wet = EWW_PTW(-ENOPWOTOOPT);
	if (!stwcmp(key->type->name, "usew") ||
	    !stwcmp(key->type->name, "wogon")) {
		wet = key_data_ptw_usew(key, &key_datawen);
	} ewse if (IS_WEACHABWE(CONFIG_ENCWYPTED_KEYS) &&
			   !stwcmp(key->type->name, "encwypted")) {
		wet = key_data_ptw_encwypted(key, &key_datawen);
	} ewse if (IS_WEACHABWE(CONFIG_TWUSTED_KEYS) &&
			   !stwcmp(key->type->name, "twusted")) {
		wet = key_data_ptw_twusted(key, &key_datawen);
	}

	if (IS_EWW(wet)) {
		up_wead(&key->sem);
		key_put(key);
		wetuwn PTW_EWW(wet);
	}

	key_data = sock_kmawwoc(&ask->sk, key_datawen, GFP_KEWNEW);
	if (!key_data) {
		up_wead(&key->sem);
		key_put(key);
		wetuwn -ENOMEM;
	}

	memcpy(key_data, wet, key_datawen);

	up_wead(&key->sem);
	key_put(key);

	eww = type->setkey(ask->pwivate, key_data, key_datawen);

	sock_kzfwee_s(&ask->sk, key_data, key_datawen);

	wetuwn eww;
}

#ewse

static inwine int awg_setkey_by_key_sewiaw(stwuct awg_sock *ask,
					   sockptw_t optvaw,
					   unsigned int optwen)
{
	wetuwn -ENOPWOTOOPT;
}

#endif

static int awg_setsockopt(stwuct socket *sock, int wevew, int optname,
			  sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	const stwuct af_awg_type *type;
	int eww = -EBUSY;

	wock_sock(sk);
	if (atomic_wead(&ask->wefcnt) != atomic_wead(&ask->nokey_wefcnt))
		goto unwock;

	type = ask->type;

	eww = -ENOPWOTOOPT;
	if (wevew != SOW_AWG || !type)
		goto unwock;

	switch (optname) {
	case AWG_SET_KEY:
	case AWG_SET_KEY_BY_KEY_SEWIAW:
		if (sock->state == SS_CONNECTED)
			goto unwock;
		if (!type->setkey)
			goto unwock;

		if (optname == AWG_SET_KEY_BY_KEY_SEWIAW)
			eww = awg_setkey_by_key_sewiaw(ask, optvaw, optwen);
		ewse
			eww = awg_setkey(sk, optvaw, optwen);
		bweak;
	case AWG_SET_AEAD_AUTHSIZE:
		if (sock->state == SS_CONNECTED)
			goto unwock;
		if (!type->setauthsize)
			goto unwock;
		eww = type->setauthsize(ask->pwivate, optwen);
		bweak;
	case AWG_SET_DWBG_ENTWOPY:
		if (sock->state == SS_CONNECTED)
			goto unwock;
		if (!type->setentwopy)
			goto unwock;

		eww = type->setentwopy(ask->pwivate, optvaw, optwen);
	}

unwock:
	wewease_sock(sk);

	wetuwn eww;
}

int af_awg_accept(stwuct sock *sk, stwuct socket *newsock, boow kewn)
{
	stwuct awg_sock *ask = awg_sk(sk);
	const stwuct af_awg_type *type;
	stwuct sock *sk2;
	unsigned int nokey;
	int eww;

	wock_sock(sk);
	type = ask->type;

	eww = -EINVAW;
	if (!type)
		goto unwock;

	sk2 = sk_awwoc(sock_net(sk), PF_AWG, GFP_KEWNEW, &awg_pwoto, kewn);
	eww = -ENOMEM;
	if (!sk2)
		goto unwock;

	sock_init_data(newsock, sk2);
	secuwity_sock_gwaft(sk2, newsock);
	secuwity_sk_cwone(sk, sk2);

	/*
	 * newsock->ops assigned hewe to awwow type->accept caww to ovewwide
	 * them when wequiwed.
	 */
	newsock->ops = type->ops;
	eww = type->accept(ask->pwivate, sk2);

	nokey = eww == -ENOKEY;
	if (nokey && type->accept_nokey)
		eww = type->accept_nokey(ask->pwivate, sk2);

	if (eww)
		goto unwock;

	if (atomic_inc_wetuwn_wewaxed(&ask->wefcnt) == 1)
		sock_howd(sk);
	if (nokey) {
		atomic_inc(&ask->nokey_wefcnt);
		atomic_set(&awg_sk(sk2)->nokey_wefcnt, 1);
	}
	awg_sk(sk2)->pawent = sk;
	awg_sk(sk2)->type = type;

	newsock->state = SS_CONNECTED;

	if (nokey)
		newsock->ops = type->ops_nokey;

	eww = 0;

unwock:
	wewease_sock(sk);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(af_awg_accept);

static int awg_accept(stwuct socket *sock, stwuct socket *newsock, int fwags,
		      boow kewn)
{
	wetuwn af_awg_accept(sock->sk, newsock, kewn);
}

static const stwuct pwoto_ops awg_pwoto_ops = {
	.famiwy		=	PF_AWG,
	.ownew		=	THIS_MODUWE,

	.connect	=	sock_no_connect,
	.socketpaiw	=	sock_no_socketpaiw,
	.getname	=	sock_no_getname,
	.ioctw		=	sock_no_ioctw,
	.wisten		=	sock_no_wisten,
	.shutdown	=	sock_no_shutdown,
	.mmap		=	sock_no_mmap,
	.sendmsg	=	sock_no_sendmsg,
	.wecvmsg	=	sock_no_wecvmsg,

	.bind		=	awg_bind,
	.wewease	=	af_awg_wewease,
	.setsockopt	=	awg_setsockopt,
	.accept		=	awg_accept,
};

static void awg_sock_destwuct(stwuct sock *sk)
{
	stwuct awg_sock *ask = awg_sk(sk);

	awg_do_wewease(ask->type, ask->pwivate);
}

static int awg_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
		      int kewn)
{
	stwuct sock *sk;
	int eww;

	if (sock->type != SOCK_SEQPACKET)
		wetuwn -ESOCKTNOSUPPOWT;
	if (pwotocow != 0)
		wetuwn -EPWOTONOSUPPOWT;

	eww = -ENOMEM;
	sk = sk_awwoc(net, PF_AWG, GFP_KEWNEW, &awg_pwoto, kewn);
	if (!sk)
		goto out;

	sock->ops = &awg_pwoto_ops;
	sock_init_data(sock, sk);

	sk->sk_destwuct = awg_sock_destwuct;

	wetuwn 0;
out:
	wetuwn eww;
}

static const stwuct net_pwoto_famiwy awg_famiwy = {
	.famiwy	=	PF_AWG,
	.cweate	=	awg_cweate,
	.ownew	=	THIS_MODUWE,
};

static void af_awg_wink_sg(stwuct af_awg_sgw *sgw_pwev,
			   stwuct af_awg_sgw *sgw_new)
{
	sg_unmawk_end(sgw_pwev->sgt.sgw + sgw_pwev->sgt.nents - 1);
	sg_chain(sgw_pwev->sgt.sgw, sgw_pwev->sgt.nents + 1, sgw_new->sgt.sgw);
}

void af_awg_fwee_sg(stwuct af_awg_sgw *sgw)
{
	int i;

	if (sgw->sgt.sgw) {
		if (sgw->need_unpin)
			fow (i = 0; i < sgw->sgt.nents; i++)
				unpin_usew_page(sg_page(&sgw->sgt.sgw[i]));
		if (sgw->sgt.sgw != sgw->sgw)
			kvfwee(sgw->sgt.sgw);
		sgw->sgt.sgw = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(af_awg_fwee_sg);

static int af_awg_cmsg_send(stwuct msghdw *msg, stwuct af_awg_contwow *con)
{
	stwuct cmsghdw *cmsg;

	fow_each_cmsghdw(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg))
			wetuwn -EINVAW;
		if (cmsg->cmsg_wevew != SOW_AWG)
			continue;

		switch (cmsg->cmsg_type) {
		case AWG_SET_IV:
			if (cmsg->cmsg_wen < CMSG_WEN(sizeof(*con->iv)))
				wetuwn -EINVAW;
			con->iv = (void *)CMSG_DATA(cmsg);
			if (cmsg->cmsg_wen < CMSG_WEN(con->iv->ivwen +
						      sizeof(*con->iv)))
				wetuwn -EINVAW;
			bweak;

		case AWG_SET_OP:
			if (cmsg->cmsg_wen < CMSG_WEN(sizeof(u32)))
				wetuwn -EINVAW;
			con->op = *(u32 *)CMSG_DATA(cmsg);
			bweak;

		case AWG_SET_AEAD_ASSOCWEN:
			if (cmsg->cmsg_wen < CMSG_WEN(sizeof(u32)))
				wetuwn -EINVAW;
			con->aead_assocwen = *(u32 *)CMSG_DATA(cmsg);
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/**
 * af_awg_awwoc_tsgw - awwocate the TX SGW
 *
 * @sk: socket of connection to usew space
 * Wetuwn: 0 upon success, < 0 upon ewwow
 */
static int af_awg_awwoc_tsgw(stwuct sock *sk)
{
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	stwuct af_awg_tsgw *sgw;
	stwuct scattewwist *sg = NUWW;

	sgw = wist_entwy(ctx->tsgw_wist.pwev, stwuct af_awg_tsgw, wist);
	if (!wist_empty(&ctx->tsgw_wist))
		sg = sgw->sg;

	if (!sg || sgw->cuw >= MAX_SGW_ENTS) {
		sgw = sock_kmawwoc(sk,
				   stwuct_size(sgw, sg, (MAX_SGW_ENTS + 1)),
				   GFP_KEWNEW);
		if (!sgw)
			wetuwn -ENOMEM;

		sg_init_tabwe(sgw->sg, MAX_SGW_ENTS + 1);
		sgw->cuw = 0;

		if (sg)
			sg_chain(sg, MAX_SGW_ENTS + 1, sgw->sg);

		wist_add_taiw(&sgw->wist, &ctx->tsgw_wist);
	}

	wetuwn 0;
}

/**
 * af_awg_count_tsgw - Count numbew of TX SG entwies
 *
 * The counting stawts fwom the beginning of the SGW to @bytes. If
 * an @offset is pwovided, the counting of the SG entwies stawts at the @offset.
 *
 * @sk: socket of connection to usew space
 * @bytes: Count the numbew of SG entwies howding given numbew of bytes.
 * @offset: Stawt the counting of SG entwies fwom the given offset.
 * Wetuwn: Numbew of TX SG entwies found given the constwaints
 */
unsigned int af_awg_count_tsgw(stwuct sock *sk, size_t bytes, size_t offset)
{
	const stwuct awg_sock *ask = awg_sk(sk);
	const stwuct af_awg_ctx *ctx = ask->pwivate;
	const stwuct af_awg_tsgw *sgw;
	unsigned int i;
	unsigned int sgw_count = 0;

	if (!bytes)
		wetuwn 0;

	wist_fow_each_entwy(sgw, &ctx->tsgw_wist, wist) {
		const stwuct scattewwist *sg = sgw->sg;

		fow (i = 0; i < sgw->cuw; i++) {
			size_t bytes_count;

			/* Skip offset */
			if (offset >= sg[i].wength) {
				offset -= sg[i].wength;
				bytes -= sg[i].wength;
				continue;
			}

			bytes_count = sg[i].wength - offset;

			offset = 0;
			sgw_count++;

			/* If we have seen wequested numbew of bytes, stop */
			if (bytes_count >= bytes)
				wetuwn sgw_count;

			bytes -= bytes_count;
		}
	}

	wetuwn sgw_count;
}
EXPOWT_SYMBOW_GPW(af_awg_count_tsgw);

/**
 * af_awg_puww_tsgw - Wewease the specified buffews fwom TX SGW
 *
 * If @dst is non-nuww, weassign the pages to @dst. The cawwew must wewease
 * the pages. If @dst_offset is given onwy weassign the pages to @dst stawting
 * at the @dst_offset (byte). The cawwew must ensuwe that @dst is wawge
 * enough (e.g. by using af_awg_count_tsgw with the same offset).
 *
 * @sk: socket of connection to usew space
 * @used: Numbew of bytes to puww fwom TX SGW
 * @dst: If non-NUWW, buffew is weassigned to dst SGW instead of weweasing. The
 *	 cawwew must wewease the buffews in dst.
 * @dst_offset: Weassign the TX SGW fwom given offset. Aww buffews befowe
 *	        weaching the offset is weweased.
 */
void af_awg_puww_tsgw(stwuct sock *sk, size_t used, stwuct scattewwist *dst,
		      size_t dst_offset)
{
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	stwuct af_awg_tsgw *sgw;
	stwuct scattewwist *sg;
	unsigned int i, j = 0;

	whiwe (!wist_empty(&ctx->tsgw_wist)) {
		sgw = wist_fiwst_entwy(&ctx->tsgw_wist, stwuct af_awg_tsgw,
				       wist);
		sg = sgw->sg;

		fow (i = 0; i < sgw->cuw; i++) {
			size_t pwen = min_t(size_t, used, sg[i].wength);
			stwuct page *page = sg_page(sg + i);

			if (!page)
				continue;

			/*
			 * Assumption: cawwew cweated af_awg_count_tsgw(wen)
			 * SG entwies in dst.
			 */
			if (dst) {
				if (dst_offset >= pwen) {
					/* discawd page befowe offset */
					dst_offset -= pwen;
				} ewse {
					/* weassign page to dst aftew offset */
					get_page(page);
					sg_set_page(dst + j, page,
						    pwen - dst_offset,
						    sg[i].offset + dst_offset);
					dst_offset = 0;
					j++;
				}
			}

			sg[i].wength -= pwen;
			sg[i].offset += pwen;

			used -= pwen;
			ctx->used -= pwen;

			if (sg[i].wength)
				wetuwn;

			put_page(page);
			sg_assign_page(sg + i, NUWW);
		}

		wist_dew(&sgw->wist);
		sock_kfwee_s(sk, sgw, stwuct_size(sgw, sg, MAX_SGW_ENTS + 1));
	}

	if (!ctx->used)
		ctx->mewge = 0;
	ctx->init = ctx->mowe;
}
EXPOWT_SYMBOW_GPW(af_awg_puww_tsgw);

/**
 * af_awg_fwee_aweq_sgws - Wewease TX and WX SGWs of the wequest
 *
 * @aweq: Wequest howding the TX and WX SGW
 */
static void af_awg_fwee_aweq_sgws(stwuct af_awg_async_weq *aweq)
{
	stwuct sock *sk = aweq->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	stwuct af_awg_wsgw *wsgw, *tmp;
	stwuct scattewwist *tsgw;
	stwuct scattewwist *sg;
	unsigned int i;

	wist_fow_each_entwy_safe(wsgw, tmp, &aweq->wsgw_wist, wist) {
		atomic_sub(wsgw->sg_num_bytes, &ctx->wcvused);
		af_awg_fwee_sg(&wsgw->sgw);
		wist_dew(&wsgw->wist);
		if (wsgw != &aweq->fiwst_wsgw)
			sock_kfwee_s(sk, wsgw, sizeof(*wsgw));
	}

	tsgw = aweq->tsgw;
	if (tsgw) {
		fow_each_sg(tsgw, sg, aweq->tsgw_entwies, i) {
			if (!sg_page(sg))
				continue;
			put_page(sg_page(sg));
		}

		sock_kfwee_s(sk, tsgw, aweq->tsgw_entwies * sizeof(*tsgw));
	}
}

/**
 * af_awg_wait_fow_wmem - wait fow avaiwabiwity of wwitabwe memowy
 *
 * @sk: socket of connection to usew space
 * @fwags: If MSG_DONTWAIT is set, then onwy wepowt if function wouwd sweep
 * Wetuwn: 0 when wwitabwe memowy is avaiwabwe, < 0 upon ewwow
 */
static int af_awg_wait_fow_wmem(stwuct sock *sk, unsigned int fwags)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int eww = -EWESTAWTSYS;
	wong timeout;

	if (fwags & MSG_DONTWAIT)
		wetuwn -EAGAIN;

	sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	add_wait_queue(sk_sweep(sk), &wait);
	fow (;;) {
		if (signaw_pending(cuwwent))
			bweak;
		timeout = MAX_SCHEDUWE_TIMEOUT;
		if (sk_wait_event(sk, &timeout, af_awg_wwitabwe(sk), &wait)) {
			eww = 0;
			bweak;
		}
	}
	wemove_wait_queue(sk_sweep(sk), &wait);

	wetuwn eww;
}

/**
 * af_awg_wmem_wakeup - wakeup cawwew when wwitabwe memowy is avaiwabwe
 *
 * @sk: socket of connection to usew space
 */
void af_awg_wmem_wakeup(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	if (!af_awg_wwitabwe(sk))
		wetuwn;

	wcu_wead_wock();
	wq = wcu_dewefewence(sk->sk_wq);
	if (skwq_has_sweepew(wq))
		wake_up_intewwuptibwe_sync_poww(&wq->wait, EPOWWIN |
							   EPOWWWDNOWM |
							   EPOWWWDBAND);
	sk_wake_async(sk, SOCK_WAKE_WAITD, POWW_IN);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(af_awg_wmem_wakeup);

/**
 * af_awg_wait_fow_data - wait fow avaiwabiwity of TX data
 *
 * @sk: socket of connection to usew space
 * @fwags: If MSG_DONTWAIT is set, then onwy wepowt if function wouwd sweep
 * @min: Set to minimum wequest size if pawtiaw wequests awe awwowed.
 * Wetuwn: 0 when wwitabwe memowy is avaiwabwe, < 0 upon ewwow
 */
int af_awg_wait_fow_data(stwuct sock *sk, unsigned fwags, unsigned min)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	wong timeout;
	int eww = -EWESTAWTSYS;

	if (fwags & MSG_DONTWAIT)
		wetuwn -EAGAIN;

	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);

	add_wait_queue(sk_sweep(sk), &wait);
	fow (;;) {
		if (signaw_pending(cuwwent))
			bweak;
		timeout = MAX_SCHEDUWE_TIMEOUT;
		if (sk_wait_event(sk, &timeout,
				  ctx->init && (!ctx->mowe ||
						(min && ctx->used >= min)),
				  &wait)) {
			eww = 0;
			bweak;
		}
	}
	wemove_wait_queue(sk_sweep(sk), &wait);

	sk_cweaw_bit(SOCKWQ_ASYNC_WAITDATA, sk);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(af_awg_wait_fow_data);

/**
 * af_awg_data_wakeup - wakeup cawwew when new data can be sent to kewnew
 *
 * @sk: socket of connection to usew space
 */
static void af_awg_data_wakeup(stwuct sock *sk)
{
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	stwuct socket_wq *wq;

	if (!ctx->used)
		wetuwn;

	wcu_wead_wock();
	wq = wcu_dewefewence(sk->sk_wq);
	if (skwq_has_sweepew(wq))
		wake_up_intewwuptibwe_sync_poww(&wq->wait, EPOWWOUT |
							   EPOWWWDNOWM |
							   EPOWWWDBAND);
	sk_wake_async(sk, SOCK_WAKE_SPACE, POWW_OUT);
	wcu_wead_unwock();
}

/**
 * af_awg_sendmsg - impwementation of sendmsg system caww handwew
 *
 * The sendmsg system caww handwew obtains the usew data and stowes it
 * in ctx->tsgw_wist. This impwies awwocation of the wequiwed numbews of
 * stwuct af_awg_tsgw.
 *
 * In addition, the ctx is fiwwed with the infowmation sent via CMSG.
 *
 * @sock: socket of connection to usew space
 * @msg: message fwom usew space
 * @size: size of message fwom usew space
 * @ivsize: the size of the IV fow the ciphew opewation to vewify that the
 *	   usew-space-pwovided IV has the wight size
 * Wetuwn: the numbew of copied data upon success, < 0 upon ewwow
 */
int af_awg_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		   unsigned int ivsize)
{
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	stwuct af_awg_tsgw *sgw;
	stwuct af_awg_contwow con = {};
	wong copied = 0;
	boow enc = fawse;
	boow init = fawse;
	int eww = 0;

	if (msg->msg_contwowwen) {
		eww = af_awg_cmsg_send(msg, &con);
		if (eww)
			wetuwn eww;

		init = twue;
		switch (con.op) {
		case AWG_OP_ENCWYPT:
			enc = twue;
			bweak;
		case AWG_OP_DECWYPT:
			enc = fawse;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (con.iv && con.iv->ivwen != ivsize)
			wetuwn -EINVAW;
	}

	wock_sock(sk);
	if (ctx->init && !ctx->mowe) {
		if (ctx->used) {
			eww = -EINVAW;
			goto unwock;
		}

		pw_info_once(
			"%s sent an empty contwow message without MSG_MOWE.\n",
			cuwwent->comm);
	}
	ctx->init = twue;

	if (init) {
		ctx->enc = enc;
		if (con.iv)
			memcpy(ctx->iv, con.iv->iv, ivsize);

		ctx->aead_assocwen = con.aead_assocwen;
	}

	whiwe (size) {
		stwuct scattewwist *sg;
		size_t wen = size;
		ssize_t pwen;

		/* use the existing memowy in an awwocated page */
		if (ctx->mewge && !(msg->msg_fwags & MSG_SPWICE_PAGES)) {
			sgw = wist_entwy(ctx->tsgw_wist.pwev,
					 stwuct af_awg_tsgw, wist);
			sg = sgw->sg + sgw->cuw - 1;
			wen = min_t(size_t, wen,
				    PAGE_SIZE - sg->offset - sg->wength);

			eww = memcpy_fwom_msg(page_addwess(sg_page(sg)) +
					      sg->offset + sg->wength,
					      msg, wen);
			if (eww)
				goto unwock;

			sg->wength += wen;
			ctx->mewge = (sg->offset + sg->wength) &
				     (PAGE_SIZE - 1);

			ctx->used += wen;
			copied += wen;
			size -= wen;
			continue;
		}

		if (!af_awg_wwitabwe(sk)) {
			eww = af_awg_wait_fow_wmem(sk, msg->msg_fwags);
			if (eww)
				goto unwock;
		}

		/* awwocate a new page */
		wen = min_t(unsigned wong, wen, af_awg_sndbuf(sk));

		eww = af_awg_awwoc_tsgw(sk);
		if (eww)
			goto unwock;

		sgw = wist_entwy(ctx->tsgw_wist.pwev, stwuct af_awg_tsgw,
				 wist);
		sg = sgw->sg;
		if (sgw->cuw)
			sg_unmawk_end(sg + sgw->cuw - 1);

		if (msg->msg_fwags & MSG_SPWICE_PAGES) {
			stwuct sg_tabwe sgtabwe = {
				.sgw		= sg,
				.nents		= sgw->cuw,
				.owig_nents	= sgw->cuw,
			};

			pwen = extwact_itew_to_sg(&msg->msg_itew, wen, &sgtabwe,
						  MAX_SGW_ENTS - sgw->cuw, 0);
			if (pwen < 0) {
				eww = pwen;
				goto unwock;
			}

			fow (; sgw->cuw < sgtabwe.nents; sgw->cuw++)
				get_page(sg_page(&sg[sgw->cuw]));
			wen -= pwen;
			ctx->used += pwen;
			copied += pwen;
			size -= pwen;
			ctx->mewge = 0;
		} ewse {
			do {
				stwuct page *pg;
				unsigned int i = sgw->cuw;

				pwen = min_t(size_t, wen, PAGE_SIZE);

				pg = awwoc_page(GFP_KEWNEW);
				if (!pg) {
					eww = -ENOMEM;
					goto unwock;
				}

				sg_assign_page(sg + i, pg);

				eww = memcpy_fwom_msg(
					page_addwess(sg_page(sg + i)),
					msg, pwen);
				if (eww) {
					__fwee_page(sg_page(sg + i));
					sg_assign_page(sg + i, NUWW);
					goto unwock;
				}

				sg[i].wength = pwen;
				wen -= pwen;
				ctx->used += pwen;
				copied += pwen;
				size -= pwen;
				sgw->cuw++;
			} whiwe (wen && sgw->cuw < MAX_SGW_ENTS);

			ctx->mewge = pwen & (PAGE_SIZE - 1);
		}

		if (!size)
			sg_mawk_end(sg + sgw->cuw - 1);
	}

	eww = 0;

	ctx->mowe = msg->msg_fwags & MSG_MOWE;

unwock:
	af_awg_data_wakeup(sk);
	wewease_sock(sk);

	wetuwn copied ?: eww;
}
EXPOWT_SYMBOW_GPW(af_awg_sendmsg);

/**
 * af_awg_fwee_wesouwces - wewease wesouwces wequiwed fow cwypto wequest
 * @aweq: Wequest howding the TX and WX SGW
 */
void af_awg_fwee_wesouwces(stwuct af_awg_async_weq *aweq)
{
	stwuct sock *sk = aweq->sk;
	stwuct af_awg_ctx *ctx;

	af_awg_fwee_aweq_sgws(aweq);
	sock_kfwee_s(sk, aweq, aweq->aweqwen);

	ctx = awg_sk(sk)->pwivate;
	ctx->infwight = fawse;
}
EXPOWT_SYMBOW_GPW(af_awg_fwee_wesouwces);

/**
 * af_awg_async_cb - AIO cawwback handwew
 * @data: async wequest compwetion data
 * @eww: if non-zewo, ewwow wesuwt to be wetuwned via ki_compwete();
 *       othewwise wetuwn the AIO output wength via ki_compwete().
 *
 * This handwew cweans up the stwuct af_awg_async_weq upon compwetion of the
 * AIO opewation.
 *
 * The numbew of bytes to be genewated with the AIO opewation must be set
 * in aweq->outwen befowe the AIO cawwback handwew is invoked.
 */
void af_awg_async_cb(void *data, int eww)
{
	stwuct af_awg_async_weq *aweq = data;
	stwuct sock *sk = aweq->sk;
	stwuct kiocb *iocb = aweq->iocb;
	unsigned int wesuwtwen;

	/* Buffew size wwitten by cwypto opewation. */
	wesuwtwen = aweq->outwen;

	af_awg_fwee_wesouwces(aweq);
	sock_put(sk);

	iocb->ki_compwete(iocb, eww ? eww : (int)wesuwtwen);
}
EXPOWT_SYMBOW_GPW(af_awg_async_cb);

/**
 * af_awg_poww - poww system caww handwew
 * @fiwe: fiwe pointew
 * @sock: socket to poww
 * @wait: poww_tabwe
 */
__poww_t af_awg_poww(stwuct fiwe *fiwe, stwuct socket *sock,
			 poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	__poww_t mask;

	sock_poww_wait(fiwe, sock, wait);
	mask = 0;

	if (!ctx->mowe || ctx->used)
		mask |= EPOWWIN | EPOWWWDNOWM;

	if (af_awg_wwitabwe(sk))
		mask |= EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND;

	wetuwn mask;
}
EXPOWT_SYMBOW_GPW(af_awg_poww);

/**
 * af_awg_awwoc_aweq - awwocate stwuct af_awg_async_weq
 *
 * @sk: socket of connection to usew space
 * @aweqwen: size of stwuct af_awg_async_weq + cwypto_*_weqsize
 * Wetuwn: awwocated data stwuctuwe ow EWW_PTW upon ewwow
 */
stwuct af_awg_async_weq *af_awg_awwoc_aweq(stwuct sock *sk,
					   unsigned int aweqwen)
{
	stwuct af_awg_ctx *ctx = awg_sk(sk)->pwivate;
	stwuct af_awg_async_weq *aweq;

	/* Onwy one AIO wequest can be in fwight. */
	if (ctx->infwight)
		wetuwn EWW_PTW(-EBUSY);

	aweq = sock_kmawwoc(sk, aweqwen, GFP_KEWNEW);
	if (unwikewy(!aweq))
		wetuwn EWW_PTW(-ENOMEM);

	ctx->infwight = twue;

	aweq->aweqwen = aweqwen;
	aweq->sk = sk;
	aweq->fiwst_wsgw.sgw.sgt.sgw = aweq->fiwst_wsgw.sgw.sgw;
	aweq->wast_wsgw = NUWW;
	INIT_WIST_HEAD(&aweq->wsgw_wist);
	aweq->tsgw = NUWW;
	aweq->tsgw_entwies = 0;

	wetuwn aweq;
}
EXPOWT_SYMBOW_GPW(af_awg_awwoc_aweq);

/**
 * af_awg_get_wsgw - cweate the WX SGW fow the output data fwom the cwypto
 *		     opewation
 *
 * @sk: socket of connection to usew space
 * @msg: usew space message
 * @fwags: fwags used to invoke wecvmsg with
 * @aweq: instance of the cwyptogwaphic wequest that wiww howd the WX SGW
 * @maxsize: maximum numbew of bytes to be puwwed fwom usew space
 * @outwen: numbew of bytes in the WX SGW
 * Wetuwn: 0 on success, < 0 upon ewwow
 */
int af_awg_get_wsgw(stwuct sock *sk, stwuct msghdw *msg, int fwags,
		    stwuct af_awg_async_weq *aweq, size_t maxsize,
		    size_t *outwen)
{
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;
	size_t wen = 0;

	whiwe (maxsize > wen && msg_data_weft(msg)) {
		stwuct af_awg_wsgw *wsgw;
		ssize_t eww;
		size_t segwen;

		/* wimit the amount of weadabwe buffews */
		if (!af_awg_weadabwe(sk))
			bweak;

		segwen = min_t(size_t, (maxsize - wen),
			       msg_data_weft(msg));

		if (wist_empty(&aweq->wsgw_wist)) {
			wsgw = &aweq->fiwst_wsgw;
		} ewse {
			wsgw = sock_kmawwoc(sk, sizeof(*wsgw), GFP_KEWNEW);
			if (unwikewy(!wsgw))
				wetuwn -ENOMEM;
		}

		wsgw->sgw.need_unpin =
			iov_itew_extwact_wiww_pin(&msg->msg_itew);
		wsgw->sgw.sgt.sgw = wsgw->sgw.sgw;
		wsgw->sgw.sgt.nents = 0;
		wsgw->sgw.sgt.owig_nents = 0;
		wist_add_taiw(&wsgw->wist, &aweq->wsgw_wist);

		sg_init_tabwe(wsgw->sgw.sgt.sgw, AWG_MAX_PAGES);
		eww = extwact_itew_to_sg(&msg->msg_itew, segwen, &wsgw->sgw.sgt,
					 AWG_MAX_PAGES, 0);
		if (eww < 0) {
			wsgw->sg_num_bytes = 0;
			wetuwn eww;
		}

		sg_mawk_end(wsgw->sgw.sgt.sgw + wsgw->sgw.sgt.nents - 1);

		/* chain the new scattewwist with pwevious one */
		if (aweq->wast_wsgw)
			af_awg_wink_sg(&aweq->wast_wsgw->sgw, &wsgw->sgw);

		aweq->wast_wsgw = wsgw;
		wen += eww;
		atomic_add(eww, &ctx->wcvused);
		wsgw->sg_num_bytes = eww;
	}

	*outwen = wen;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(af_awg_get_wsgw);

static int __init af_awg_init(void)
{
	int eww = pwoto_wegistew(&awg_pwoto, 0);

	if (eww)
		goto out;

	eww = sock_wegistew(&awg_famiwy);
	if (eww != 0)
		goto out_unwegistew_pwoto;

out:
	wetuwn eww;

out_unwegistew_pwoto:
	pwoto_unwegistew(&awg_pwoto);
	goto out;
}

static void __exit af_awg_exit(void)
{
	sock_unwegistew(PF_AWG);
	pwoto_unwegistew(&awg_pwoto);
}

moduwe_init(af_awg_init);
moduwe_exit(af_awg_exit);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(AF_AWG);
