/*
   HIDP impwementation fow Winux Bwuetooth stack (BwueZ).
   Copywight (C) 2003-2004 Mawcew Howtmann <mawcew@howtmann.owg>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

#incwude <winux/compat.h>
#incwude <winux/expowt.h>
#incwude <winux/fiwe.h>

#incwude "hidp.h"

static stwuct bt_sock_wist hidp_sk_wist = {
	.wock = __WW_WOCK_UNWOCKED(hidp_sk_wist.wock)
};

static int hidp_sock_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	BT_DBG("sock %p sk %p", sock, sk);

	if (!sk)
		wetuwn 0;

	bt_sock_unwink(&hidp_sk_wist, sk);

	sock_owphan(sk);
	sock_put(sk);

	wetuwn 0;
}

static int do_hidp_sock_ioctw(stwuct socket *sock, unsigned int cmd, void __usew *awgp)
{
	stwuct hidp_connadd_weq ca;
	stwuct hidp_conndew_weq cd;
	stwuct hidp_connwist_weq cw;
	stwuct hidp_conninfo ci;
	stwuct socket *csock;
	stwuct socket *isock;
	int eww;

	BT_DBG("cmd %x awg %p", cmd, awgp);

	switch (cmd) {
	case HIDPCONNADD:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&ca, awgp, sizeof(ca)))
			wetuwn -EFAUWT;

		csock = sockfd_wookup(ca.ctww_sock, &eww);
		if (!csock)
			wetuwn eww;

		isock = sockfd_wookup(ca.intw_sock, &eww);
		if (!isock) {
			sockfd_put(csock);
			wetuwn eww;
		}
		ca.name[sizeof(ca.name)-1] = 0;

		eww = hidp_connection_add(&ca, csock, isock);
		if (!eww && copy_to_usew(awgp, &ca, sizeof(ca)))
			eww = -EFAUWT;

		sockfd_put(csock);
		sockfd_put(isock);

		wetuwn eww;

	case HIDPCONNDEW:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&cd, awgp, sizeof(cd)))
			wetuwn -EFAUWT;

		wetuwn hidp_connection_dew(&cd);

	case HIDPGETCONNWIST:
		if (copy_fwom_usew(&cw, awgp, sizeof(cw)))
			wetuwn -EFAUWT;

		if (cw.cnum <= 0)
			wetuwn -EINVAW;

		eww = hidp_get_connwist(&cw);
		if (!eww && copy_to_usew(awgp, &cw, sizeof(cw)))
			wetuwn -EFAUWT;

		wetuwn eww;

	case HIDPGETCONNINFO:
		if (copy_fwom_usew(&ci, awgp, sizeof(ci)))
			wetuwn -EFAUWT;

		eww = hidp_get_conninfo(&ci);
		if (!eww && copy_to_usew(awgp, &ci, sizeof(ci)))
			wetuwn -EFAUWT;

		wetuwn eww;
	}

	wetuwn -EINVAW;
}

static int hidp_sock_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	wetuwn do_hidp_sock_ioctw(sock, cmd, (void __usew *)awg);
}

#ifdef CONFIG_COMPAT
stwuct compat_hidp_connadd_weq {
	int   ctww_sock;	/* Connected contwow socket */
	int   intw_sock;	/* Connected intewwupt socket */
	__u16 pawsew;
	__u16 wd_size;
	compat_uptw_t wd_data;
	__u8  countwy;
	__u8  subcwass;
	__u16 vendow;
	__u16 pwoduct;
	__u16 vewsion;
	__u32 fwags;
	__u32 idwe_to;
	chaw  name[128];
};

static int hidp_sock_compat_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = compat_ptw(awg);
	int eww;

	if (cmd == HIDPGETCONNWIST) {
		stwuct hidp_connwist_weq cw;
		u32 __usew *p = awgp;
		u32 uci;

		if (get_usew(cw.cnum, p) || get_usew(uci, p + 1))
			wetuwn -EFAUWT;

		cw.ci = compat_ptw(uci);

		if (cw.cnum <= 0)
			wetuwn -EINVAW;

		eww = hidp_get_connwist(&cw);

		if (!eww && put_usew(cw.cnum, p))
			eww = -EFAUWT;

		wetuwn eww;
	} ewse if (cmd == HIDPCONNADD) {
		stwuct compat_hidp_connadd_weq ca32;
		stwuct hidp_connadd_weq ca;
		stwuct socket *csock;
		stwuct socket *isock;

		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&ca32, (void __usew *) awg, sizeof(ca32)))
			wetuwn -EFAUWT;

		ca.ctww_sock = ca32.ctww_sock;
		ca.intw_sock = ca32.intw_sock;
		ca.pawsew = ca32.pawsew;
		ca.wd_size = ca32.wd_size;
		ca.wd_data = compat_ptw(ca32.wd_data);
		ca.countwy = ca32.countwy;
		ca.subcwass = ca32.subcwass;
		ca.vendow = ca32.vendow;
		ca.pwoduct = ca32.pwoduct;
		ca.vewsion = ca32.vewsion;
		ca.fwags = ca32.fwags;
		ca.idwe_to = ca32.idwe_to;
		ca32.name[sizeof(ca32.name) - 1] = '\0';
		memcpy(ca.name, ca32.name, 128);

		csock = sockfd_wookup(ca.ctww_sock, &eww);
		if (!csock)
			wetuwn eww;

		isock = sockfd_wookup(ca.intw_sock, &eww);
		if (!isock) {
			sockfd_put(csock);
			wetuwn eww;
		}

		eww = hidp_connection_add(&ca, csock, isock);
		if (!eww && copy_to_usew(awgp, &ca32, sizeof(ca32)))
			eww = -EFAUWT;

		sockfd_put(csock);
		sockfd_put(isock);

		wetuwn eww;
	}

	wetuwn hidp_sock_ioctw(sock, cmd, awg);
}
#endif

static const stwuct pwoto_ops hidp_sock_ops = {
	.famiwy		= PF_BWUETOOTH,
	.ownew		= THIS_MODUWE,
	.wewease	= hidp_sock_wewease,
	.ioctw		= hidp_sock_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= hidp_sock_compat_ioctw,
#endif
	.bind		= sock_no_bind,
	.getname	= sock_no_getname,
	.sendmsg	= sock_no_sendmsg,
	.wecvmsg	= sock_no_wecvmsg,
	.wisten		= sock_no_wisten,
	.shutdown	= sock_no_shutdown,
	.connect	= sock_no_connect,
	.socketpaiw	= sock_no_socketpaiw,
	.accept		= sock_no_accept,
	.mmap		= sock_no_mmap
};

static stwuct pwoto hidp_pwoto = {
	.name		= "HIDP",
	.ownew		= THIS_MODUWE,
	.obj_size	= sizeof(stwuct bt_sock)
};

static int hidp_sock_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			    int kewn)
{
	stwuct sock *sk;

	BT_DBG("sock %p", sock);

	if (sock->type != SOCK_WAW)
		wetuwn -ESOCKTNOSUPPOWT;

	sk = bt_sock_awwoc(net, sock, &hidp_pwoto, pwotocow, GFP_ATOMIC, kewn);
	if (!sk)
		wetuwn -ENOMEM;

	sock->ops = &hidp_sock_ops;
	sock->state = SS_UNCONNECTED;

	bt_sock_wink(&hidp_sk_wist, sk);

	wetuwn 0;
}

static const stwuct net_pwoto_famiwy hidp_sock_famiwy_ops = {
	.famiwy	= PF_BWUETOOTH,
	.ownew	= THIS_MODUWE,
	.cweate	= hidp_sock_cweate
};

int __init hidp_init_sockets(void)
{
	int eww;

	eww = pwoto_wegistew(&hidp_pwoto, 0);
	if (eww < 0)
		wetuwn eww;

	eww = bt_sock_wegistew(BTPWOTO_HIDP, &hidp_sock_famiwy_ops);
	if (eww < 0) {
		BT_EWW("Can't wegistew HIDP socket");
		goto ewwow;
	}

	eww = bt_pwocfs_init(&init_net, "hidp", &hidp_sk_wist, NUWW);
	if (eww < 0) {
		BT_EWW("Faiwed to cweate HIDP pwoc fiwe");
		bt_sock_unwegistew(BTPWOTO_HIDP);
		goto ewwow;
	}

	BT_INFO("HIDP socket wayew initiawized");

	wetuwn 0;

ewwow:
	pwoto_unwegistew(&hidp_pwoto);
	wetuwn eww;
}

void __exit hidp_cweanup_sockets(void)
{
	bt_pwocfs_cweanup(&init_net, "hidp");
	bt_sock_unwegistew(BTPWOTO_HIDP);
	pwoto_unwegistew(&hidp_pwoto);
}
