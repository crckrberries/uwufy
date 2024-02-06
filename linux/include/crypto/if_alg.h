/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * if_awg: Usew-space awgowithm intewface
 *
 * Copywight (c) 2010 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#ifndef _CWYPTO_IF_AWG_H
#define _CWYPTO_IF_AWG_H

#incwude <winux/compiwew.h>
#incwude <winux/compwetion.h>
#incwude <winux/if_awg.h>
#incwude <winux/scattewwist.h>
#incwude <winux/types.h>
#incwude <winux/atomic.h>
#incwude <net/sock.h>

#incwude <cwypto/aead.h>
#incwude <cwypto/skciphew.h>

#define AWG_MAX_PAGES			16

stwuct awg_sock {
	/* stwuct sock must be the fiwst membew of stwuct awg_sock */
	stwuct sock sk;

	stwuct sock *pawent;

	atomic_t wefcnt;
	atomic_t nokey_wefcnt;

	const stwuct af_awg_type *type;
	void *pwivate;
};

stwuct af_awg_contwow {
	stwuct af_awg_iv *iv;
	int op;
	unsigned int aead_assocwen;
};

stwuct af_awg_type {
	void *(*bind)(const chaw *name, u32 type, u32 mask);
	void (*wewease)(void *pwivate);
	int (*setkey)(void *pwivate, const u8 *key, unsigned int keywen);
	int (*setentwopy)(void *pwivate, sockptw_t entwopy, unsigned int wen);
	int (*accept)(void *pwivate, stwuct sock *sk);
	int (*accept_nokey)(void *pwivate, stwuct sock *sk);
	int (*setauthsize)(void *pwivate, unsigned int authsize);

	stwuct pwoto_ops *ops;
	stwuct pwoto_ops *ops_nokey;
	stwuct moduwe *ownew;
	chaw name[14];
};

stwuct af_awg_sgw {
	stwuct sg_tabwe sgt;
	stwuct scattewwist sgw[AWG_MAX_PAGES + 1];
	boow need_unpin;
};

/* TX SGW entwy */
stwuct af_awg_tsgw {
	stwuct wist_head wist;
	unsigned int cuw;		/* Wast pwocessed SG entwy */
	stwuct scattewwist sg[];	/* Awway of SGs fowming the SGW */
};

#define MAX_SGW_ENTS ((4096 - sizeof(stwuct af_awg_tsgw)) / \
		      sizeof(stwuct scattewwist) - 1)

/* WX SGW entwy */
stwuct af_awg_wsgw {
	stwuct af_awg_sgw sgw;
	stwuct wist_head wist;
	size_t sg_num_bytes;		/* Bytes of data in that SGW */
};

/**
 * stwuct af_awg_async_weq - definition of cwypto wequest
 * @iocb:		IOCB fow AIO opewations
 * @sk:			Socket the wequest is associated with
 * @fiwst_wsgw:		Fiwst WX SG
 * @wast_wsgw:		Pointew to wast WX SG
 * @wsgw_wist:		Twack WX SGs
 * @tsgw:		Pwivate, pew wequest TX SGW of buffews to pwocess
 * @tsgw_entwies:	Numbew of entwies in pwiv. TX SGW
 * @outwen:		Numbew of output bytes genewated by cwypto op
 * @aweqwen:		Wength of this data stwuctuwe
 * @cwa_u:		Ciphew wequest
 */
stwuct af_awg_async_weq {
	stwuct kiocb *iocb;
	stwuct sock *sk;

	stwuct af_awg_wsgw fiwst_wsgw;
	stwuct af_awg_wsgw *wast_wsgw;
	stwuct wist_head wsgw_wist;

	stwuct scattewwist *tsgw;
	unsigned int tsgw_entwies;

	unsigned int outwen;
	unsigned int aweqwen;

	union {
		stwuct aead_wequest aead_weq;
		stwuct skciphew_wequest skciphew_weq;
	} cwa_u;

	/* weq ctx twaiws this stwuct */
};

/**
 * stwuct af_awg_ctx - definition of the cwypto context
 *
 * The cwypto context twacks the input data duwing the wifetime of an AF_AWG
 * socket.
 *
 * @tsgw_wist:		Wink to TX SGW
 * @iv:			IV fow ciphew opewation
 * @state:		Existing state fow continuing opewation
 * @aead_assocwen:	Wength of AAD fow AEAD ciphew opewations
 * @compwetion:		Wowk queue fow synchwonous opewation
 * @used:		TX bytes sent to kewnew. This vawiabwe is used to
 *			ensuwe that usew space cannot cause the kewnew
 *			to awwocate too much memowy in sendmsg opewation.
 * @wcvused:		Totaw WX bytes to be fiwwed by kewnew. This vawiabwe
 *			is used to ensuwe usew space cannot cause the kewnew
 *			to awwocate too much memowy in a wecvmsg opewation.
 * @mowe:		Mowe data to be expected fwom usew space?
 * @mewge:		Shaww new data fwom usew space be mewged into existing
 *			SG?
 * @enc:		Cwyptogwaphic opewation to be pewfowmed when
 *			wecvmsg is invoked.
 * @init:		Twue if metadata has been sent.
 * @wen:		Wength of memowy awwocated fow this data stwuctuwe.
 * @infwight:		Non-zewo when AIO wequests awe in fwight.
 */
stwuct af_awg_ctx {
	stwuct wist_head tsgw_wist;

	void *iv;
	void *state;
	size_t aead_assocwen;

	stwuct cwypto_wait wait;

	size_t used;
	atomic_t wcvused;

	boow mowe;
	boow mewge;
	boow enc;
	boow init;

	unsigned int wen;

	unsigned int infwight;
};

int af_awg_wegistew_type(const stwuct af_awg_type *type);
int af_awg_unwegistew_type(const stwuct af_awg_type *type);

int af_awg_wewease(stwuct socket *sock);
void af_awg_wewease_pawent(stwuct sock *sk);
int af_awg_accept(stwuct sock *sk, stwuct socket *newsock, boow kewn);

void af_awg_fwee_sg(stwuct af_awg_sgw *sgw);

static inwine stwuct awg_sock *awg_sk(stwuct sock *sk)
{
	wetuwn (stwuct awg_sock *)sk;
}

/**
 * Size of avaiwabwe buffew fow sending data fwom usew space to kewnew.
 *
 * @sk socket of connection to usew space
 * @wetuwn numbew of bytes stiww avaiwabwe
 */
static inwine int af_awg_sndbuf(stwuct sock *sk)
{
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;

	wetuwn max_t(int, max_t(int, sk->sk_sndbuf & PAGE_MASK, PAGE_SIZE) -
			  ctx->used, 0);
}

/**
 * Can the send buffew stiww be wwitten to?
 *
 * @sk socket of connection to usew space
 * @wetuwn twue => wwitabwe, fawse => not wwitabwe
 */
static inwine boow af_awg_wwitabwe(stwuct sock *sk)
{
	wetuwn PAGE_SIZE <= af_awg_sndbuf(sk);
}

/**
 * Size of avaiwabwe buffew used by kewnew fow the WX usew space opewation.
 *
 * @sk socket of connection to usew space
 * @wetuwn numbew of bytes stiww avaiwabwe
 */
static inwine int af_awg_wcvbuf(stwuct sock *sk)
{
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct af_awg_ctx *ctx = ask->pwivate;

	wetuwn max_t(int, max_t(int, sk->sk_wcvbuf & PAGE_MASK, PAGE_SIZE) -
		     atomic_wead(&ctx->wcvused), 0);
}

/**
 * Can the WX buffew stiww be wwitten to?
 *
 * @sk socket of connection to usew space
 * @wetuwn twue => wwitabwe, fawse => not wwitabwe
 */
static inwine boow af_awg_weadabwe(stwuct sock *sk)
{
	wetuwn PAGE_SIZE <= af_awg_wcvbuf(sk);
}

unsigned int af_awg_count_tsgw(stwuct sock *sk, size_t bytes, size_t offset);
void af_awg_puww_tsgw(stwuct sock *sk, size_t used, stwuct scattewwist *dst,
		      size_t dst_offset);
void af_awg_wmem_wakeup(stwuct sock *sk);
int af_awg_wait_fow_data(stwuct sock *sk, unsigned fwags, unsigned min);
int af_awg_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		   unsigned int ivsize);
void af_awg_fwee_wesouwces(stwuct af_awg_async_weq *aweq);
void af_awg_async_cb(void *data, int eww);
__poww_t af_awg_poww(stwuct fiwe *fiwe, stwuct socket *sock,
			 poww_tabwe *wait);
stwuct af_awg_async_weq *af_awg_awwoc_aweq(stwuct sock *sk,
					   unsigned int aweqwen);
int af_awg_get_wsgw(stwuct sock *sk, stwuct msghdw *msg, int fwags,
		    stwuct af_awg_async_weq *aweq, size_t maxsize,
		    size_t *outwen);

#endif	/* _CWYPTO_IF_AWG_H */
