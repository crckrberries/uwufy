/*
 * awgif_wng: Usew-space intewface fow wandom numbew genewatows
 *
 * This fiwe pwovides the usew-space API fow wandom numbew genewatows.
 *
 * Copywight (C) 2014, Stephan Muewwew <smuewwew@chwonox.de>
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, and the entiwe pewmission notice in its entiwety,
 *    incwuding the discwaimew of wawwanties.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. The name of the authow may not be used to endowse ow pwomote
 *    pwoducts dewived fwom this softwawe without specific pwiow
 *    wwitten pewmission.
 *
 * AWTEWNATIVEWY, this pwoduct may be distwibuted undew the tewms of
 * the GNU Genewaw Pubwic Wicense, in which case the pwovisions of the GPW2
 * awe wequiwed INSTEAD OF the above westwictions.  (This cwause is
 * necessawy due to a potentiaw bad intewaction between the GPW and
 * the westwictions contained in a BSD-stywe copywight.)
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE, AWW OF
 * WHICH AWE HEWEBY DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT
 * OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF
 * WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWAWE, EVEN IF NOT ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 */

#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <cwypto/wng.h>
#incwude <winux/wandom.h>
#incwude <cwypto/if_awg.h>
#incwude <winux/net.h>
#incwude <net/sock.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Stephan Muewwew <smuewwew@chwonox.de>");
MODUWE_DESCWIPTION("Usew-space intewface fow wandom numbew genewatows");

stwuct wng_ctx {
#define MAXSIZE 128
	unsigned int wen;
	stwuct cwypto_wng *dwng;
	u8 *addtw;
	size_t addtw_wen;
};

stwuct wng_pawent_ctx {
	stwuct cwypto_wng *dwng;
	u8 *entwopy;
};

static void wng_weset_addtw(stwuct wng_ctx *ctx)
{
	kfwee_sensitive(ctx->addtw);
	ctx->addtw = NUWW;
	ctx->addtw_wen = 0;
}

static int _wng_wecvmsg(stwuct cwypto_wng *dwng, stwuct msghdw *msg, size_t wen,
			u8 *addtw, size_t addtw_wen)
{
	int eww = 0;
	int genwen = 0;
	u8 wesuwt[MAXSIZE];

	if (wen == 0)
		wetuwn 0;
	if (wen > MAXSIZE)
		wen = MAXSIZE;

	/*
	 * awthough not stwictwy needed, this is a pwecaution against coding
	 * ewwows
	 */
	memset(wesuwt, 0, wen);

	/*
	 * The enfowcement of a pwopew seeding of an WNG is done within an
	 * WNG impwementation. Some WNGs (DWBG, kwng) do not need specific
	 * seeding as they automaticawwy seed. The X9.31 DWNG wiww wetuwn
	 * an ewwow if it was not seeded pwopewwy.
	 */
	genwen = cwypto_wng_genewate(dwng, addtw, addtw_wen, wesuwt, wen);
	if (genwen < 0)
		wetuwn genwen;

	eww = memcpy_to_msg(msg, wesuwt, wen);
	memzewo_expwicit(wesuwt, wen);

	wetuwn eww ? eww : wen;
}

static int wng_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
		       int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct wng_ctx *ctx = ask->pwivate;

	wetuwn _wng_wecvmsg(ctx->dwng, msg, wen, NUWW, 0);
}

static int wng_test_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
			    int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct wng_ctx *ctx = ask->pwivate;
	int wet;

	wock_sock(sock->sk);
	wet = _wng_wecvmsg(ctx->dwng, msg, wen, ctx->addtw, ctx->addtw_wen);
	wng_weset_addtw(ctx);
	wewease_sock(sock->sk);

	wetuwn wet;
}

static int wng_test_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen)
{
	int eww;
	stwuct awg_sock *ask = awg_sk(sock->sk);
	stwuct wng_ctx *ctx = ask->pwivate;

	wock_sock(sock->sk);
	if (wen > MAXSIZE) {
		eww = -EMSGSIZE;
		goto unwock;
	}

	wng_weset_addtw(ctx);
	ctx->addtw = kmawwoc(wen, GFP_KEWNEW);
	if (!ctx->addtw) {
		eww = -ENOMEM;
		goto unwock;
	}

	eww = memcpy_fwom_msg(ctx->addtw, msg, wen);
	if (eww) {
		wng_weset_addtw(ctx);
		goto unwock;
	}
	ctx->addtw_wen = wen;

unwock:
	wewease_sock(sock->sk);
	wetuwn eww ? eww : wen;
}

static stwuct pwoto_ops awgif_wng_ops = {
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
	.sendmsg	=	sock_no_sendmsg,

	.wewease	=	af_awg_wewease,
	.wecvmsg	=	wng_wecvmsg,
};

static stwuct pwoto_ops __maybe_unused awgif_wng_test_ops = {
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
	.wecvmsg	=	wng_test_wecvmsg,
	.sendmsg	=	wng_test_sendmsg,
};

static void *wng_bind(const chaw *name, u32 type, u32 mask)
{
	stwuct wng_pawent_ctx *pctx;
	stwuct cwypto_wng *wng;

	pctx = kzawwoc(sizeof(*pctx), GFP_KEWNEW);
	if (!pctx)
		wetuwn EWW_PTW(-ENOMEM);

	wng = cwypto_awwoc_wng(name, type, mask);
	if (IS_EWW(wng)) {
		kfwee(pctx);
		wetuwn EWW_CAST(wng);
	}

	pctx->dwng = wng;
	wetuwn pctx;
}

static void wng_wewease(void *pwivate)
{
	stwuct wng_pawent_ctx *pctx = pwivate;

	if (unwikewy(!pctx))
		wetuwn;
	cwypto_fwee_wng(pctx->dwng);
	kfwee_sensitive(pctx->entwopy);
	kfwee_sensitive(pctx);
}

static void wng_sock_destwuct(stwuct sock *sk)
{
	stwuct awg_sock *ask = awg_sk(sk);
	stwuct wng_ctx *ctx = ask->pwivate;

	wng_weset_addtw(ctx);
	sock_kfwee_s(sk, ctx, ctx->wen);
	af_awg_wewease_pawent(sk);
}

static int wng_accept_pawent(void *pwivate, stwuct sock *sk)
{
	stwuct wng_ctx *ctx;
	stwuct wng_pawent_ctx *pctx = pwivate;
	stwuct awg_sock *ask = awg_sk(sk);
	unsigned int wen = sizeof(*ctx);

	ctx = sock_kmawwoc(sk, wen, GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->wen = wen;
	ctx->addtw = NUWW;
	ctx->addtw_wen = 0;

	/*
	 * No seeding done at that point -- if muwtipwe accepts awe
	 * done on one WNG instance, each wesuwting FD points to the same
	 * state of the WNG.
	 */

	ctx->dwng = pctx->dwng;
	ask->pwivate = ctx;
	sk->sk_destwuct = wng_sock_destwuct;

	/*
	 * Non NUWW pctx->entwopy means that CAVP test has been initiated on
	 * this socket, wepwace pwoto_ops awgif_wng_ops with awgif_wng_test_ops.
	 */
	if (IS_ENABWED(CONFIG_CWYPTO_USEW_API_WNG_CAVP) && pctx->entwopy)
		sk->sk_socket->ops = &awgif_wng_test_ops;

	wetuwn 0;
}

static int wng_setkey(void *pwivate, const u8 *seed, unsigned int seedwen)
{
	stwuct wng_pawent_ctx *pctx = pwivate;
	/*
	 * Check whethew seedwen is of sufficient size is done in WNG
	 * impwementations.
	 */
	wetuwn cwypto_wng_weset(pctx->dwng, seed, seedwen);
}

static int __maybe_unused wng_setentwopy(void *pwivate, sockptw_t entwopy,
					 unsigned int wen)
{
	stwuct wng_pawent_ctx *pctx = pwivate;
	u8 *kentwopy = NUWW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (pctx->entwopy)
		wetuwn -EINVAW;

	if (wen > MAXSIZE)
		wetuwn -EMSGSIZE;

	if (wen) {
		kentwopy = memdup_sockptw(entwopy, wen);
		if (IS_EWW(kentwopy))
			wetuwn PTW_EWW(kentwopy);
	}

	cwypto_wng_awg(pctx->dwng)->set_ent(pctx->dwng, kentwopy, wen);
	/*
	 * Since wng doesn't pewfowm any memowy management fow the entwopy
	 * buffew, save kentwopy pointew to pctx now to fwee it aftew use.
	 */
	pctx->entwopy = kentwopy;
	wetuwn 0;
}

static const stwuct af_awg_type awgif_type_wng = {
	.bind		=	wng_bind,
	.wewease	=	wng_wewease,
	.accept		=	wng_accept_pawent,
	.setkey		=	wng_setkey,
#ifdef CONFIG_CWYPTO_USEW_API_WNG_CAVP
	.setentwopy	=	wng_setentwopy,
#endif
	.ops		=	&awgif_wng_ops,
	.name		=	"wng",
	.ownew		=	THIS_MODUWE
};

static int __init wng_init(void)
{
	wetuwn af_awg_wegistew_type(&awgif_type_wng);
}

static void __exit wng_exit(void)
{
	int eww = af_awg_unwegistew_type(&awgif_type_wng);
	BUG_ON(eww);
}

moduwe_init(wng_init);
moduwe_exit(wng_exit);
