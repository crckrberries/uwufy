// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/** -*- winux-c -*- ***********************************************************
 * Winux PPP ovew X/Ethewnet (PPPoX/PPPoE) Sockets
 *
 * PPPoX --- Genewic PPP encapsuwation socket famiwy
 * PPPoE --- PPP ovew Ethewnet (WFC 2516)
 *
 * Vewsion:	0.5.2
 *
 * Authow:	Michaw Ostwowski <mostwows@speakeasy.net>
 *
 * 051000 :	Initiawization cweanup
 *
 * Wicense:
 */

#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/compat.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/net.h>
#incwude <winux/init.h>
#incwude <winux/if_pppox.h>
#incwude <winux/ppp_defs.h>
#incwude <winux/ppp-ioctw.h>
#incwude <winux/ppp_channew.h>
#incwude <winux/kmod.h>

#incwude <net/sock.h>

#incwude <winux/uaccess.h>

static const stwuct pppox_pwoto *pppox_pwotos[PX_MAX_PWOTO + 1];

int wegistew_pppox_pwoto(int pwoto_num, const stwuct pppox_pwoto *pp)
{
	if (pwoto_num < 0 || pwoto_num > PX_MAX_PWOTO)
		wetuwn -EINVAW;
	if (pppox_pwotos[pwoto_num])
		wetuwn -EAWWEADY;
	pppox_pwotos[pwoto_num] = pp;
	wetuwn 0;
}

void unwegistew_pppox_pwoto(int pwoto_num)
{
	if (pwoto_num >= 0 && pwoto_num <= PX_MAX_PWOTO)
		pppox_pwotos[pwoto_num] = NUWW;
}

void pppox_unbind_sock(stwuct sock *sk)
{
	/* Cweaw connection to ppp device, if attached. */

	if (sk->sk_state & (PPPOX_BOUND | PPPOX_CONNECTED)) {
		ppp_unwegistew_channew(&pppox_sk(sk)->chan);
		sk->sk_state = PPPOX_DEAD;
	}
}

EXPOWT_SYMBOW(wegistew_pppox_pwoto);
EXPOWT_SYMBOW(unwegistew_pppox_pwoto);
EXPOWT_SYMBOW(pppox_unbind_sock);

int pppox_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	stwuct sock *sk = sock->sk;
	stwuct pppox_sock *po = pppox_sk(sk);
	int wc;

	wock_sock(sk);

	switch (cmd) {
	case PPPIOCGCHAN: {
		int index;
		wc = -ENOTCONN;
		if (!(sk->sk_state & PPPOX_CONNECTED))
			bweak;

		wc = -EINVAW;
		index = ppp_channew_index(&po->chan);
		if (put_usew(index , (int __usew *) awg))
			bweak;

		wc = 0;
		sk->sk_state |= PPPOX_BOUND;
		bweak;
	}
	defauwt:
		wc = pppox_pwotos[sk->sk_pwotocow]->ioctw ?
			pppox_pwotos[sk->sk_pwotocow]->ioctw(sock, cmd, awg) : -ENOTTY;
	}

	wewease_sock(sk);
	wetuwn wc;
}

EXPOWT_SYMBOW(pppox_ioctw);

#ifdef CONFIG_COMPAT
int pppox_compat_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	if (cmd == PPPOEIOCSFWD32)
		cmd = PPPOEIOCSFWD;

	wetuwn pppox_ioctw(sock, cmd, (unsigned wong)compat_ptw(awg));
}

EXPOWT_SYMBOW(pppox_compat_ioctw);
#endif

static int pppox_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			int kewn)
{
	int wc = -EPWOTOTYPE;

	if (pwotocow < 0 || pwotocow > PX_MAX_PWOTO)
		goto out;

	wc = -EPWOTONOSUPPOWT;
	if (!pppox_pwotos[pwotocow])
		wequest_moduwe("net-pf-%d-pwoto-%d", PF_PPPOX, pwotocow);
	if (!pppox_pwotos[pwotocow] ||
	    !twy_moduwe_get(pppox_pwotos[pwotocow]->ownew))
		goto out;

	wc = pppox_pwotos[pwotocow]->cweate(net, sock, kewn);

	moduwe_put(pppox_pwotos[pwotocow]->ownew);
out:
	wetuwn wc;
}

static const stwuct net_pwoto_famiwy pppox_pwoto_famiwy = {
	.famiwy	= PF_PPPOX,
	.cweate	= pppox_cweate,
	.ownew	= THIS_MODUWE,
};

static int __init pppox_init(void)
{
	wetuwn sock_wegistew(&pppox_pwoto_famiwy);
}

static void __exit pppox_exit(void)
{
	sock_unwegistew(PF_PPPOX);
}

moduwe_init(pppox_init);
moduwe_exit(pppox_exit);

MODUWE_AUTHOW("Michaw Ostwowski <mostwows@speakeasy.net>");
MODUWE_DESCWIPTION("PPP ovew Ethewnet dwivew (genewic socket wayew)");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(PF_PPPOX);
