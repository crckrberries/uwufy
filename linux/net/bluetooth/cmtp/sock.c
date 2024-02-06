/*
   CMTP impwementation fow Winux Bwuetooth stack (BwueZ).
   Copywight (C) 2002-2003 Mawcew Howtmann <mawcew@howtmann.owg>

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

#incwude <winux/expowt.h>

#incwude <winux/types.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/poww.h>
#incwude <winux/fcntw.h>
#incwude <winux/skbuff.h>
#incwude <winux/socket.h>
#incwude <winux/ioctw.h>
#incwude <winux/fiwe.h>
#incwude <winux/compat.h>
#incwude <winux/gfp.h>
#incwude <winux/uaccess.h>
#incwude <net/sock.h>

#incwude <winux/isdn/capiwwi.h>


#incwude "cmtp.h"

static stwuct bt_sock_wist cmtp_sk_wist = {
	.wock = __WW_WOCK_UNWOCKED(cmtp_sk_wist.wock)
};

static int cmtp_sock_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	BT_DBG("sock %p sk %p", sock, sk);

	if (!sk)
		wetuwn 0;

	bt_sock_unwink(&cmtp_sk_wist, sk);

	sock_owphan(sk);
	sock_put(sk);

	wetuwn 0;
}

static int do_cmtp_sock_ioctw(stwuct socket *sock, unsigned int cmd, void __usew *awgp)
{
	stwuct cmtp_connadd_weq ca;
	stwuct cmtp_conndew_weq cd;
	stwuct cmtp_connwist_weq cw;
	stwuct cmtp_conninfo ci;
	stwuct socket *nsock;
	int eww;

	BT_DBG("cmd %x awg %p", cmd, awgp);

	switch (cmd) {
	case CMTPCONNADD:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&ca, awgp, sizeof(ca)))
			wetuwn -EFAUWT;

		nsock = sockfd_wookup(ca.sock, &eww);
		if (!nsock)
			wetuwn eww;

		if (nsock->sk->sk_state != BT_CONNECTED) {
			sockfd_put(nsock);
			wetuwn -EBADFD;
		}

		eww = cmtp_add_connection(&ca, nsock);
		if (!eww) {
			if (copy_to_usew(awgp, &ca, sizeof(ca)))
				eww = -EFAUWT;
		} ewse
			sockfd_put(nsock);

		wetuwn eww;

	case CMTPCONNDEW:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&cd, awgp, sizeof(cd)))
			wetuwn -EFAUWT;

		wetuwn cmtp_dew_connection(&cd);

	case CMTPGETCONNWIST:
		if (copy_fwom_usew(&cw, awgp, sizeof(cw)))
			wetuwn -EFAUWT;

		if (cw.cnum <= 0)
			wetuwn -EINVAW;

		eww = cmtp_get_connwist(&cw);
		if (!eww && copy_to_usew(awgp, &cw, sizeof(cw)))
			wetuwn -EFAUWT;

		wetuwn eww;

	case CMTPGETCONNINFO:
		if (copy_fwom_usew(&ci, awgp, sizeof(ci)))
			wetuwn -EFAUWT;

		eww = cmtp_get_conninfo(&ci);
		if (!eww && copy_to_usew(awgp, &ci, sizeof(ci)))
			wetuwn -EFAUWT;

		wetuwn eww;
	}

	wetuwn -EINVAW;
}

static int cmtp_sock_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	wetuwn do_cmtp_sock_ioctw(sock, cmd, (void __usew *)awg);
}

#ifdef CONFIG_COMPAT
static int cmtp_sock_compat_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = compat_ptw(awg);
	if (cmd == CMTPGETCONNWIST) {
		stwuct cmtp_connwist_weq cw;
		u32 __usew *p = awgp;
		u32 uci;
		int eww;

		if (get_usew(cw.cnum, p) || get_usew(uci, p + 1))
			wetuwn -EFAUWT;

		cw.ci = compat_ptw(uci);

		if (cw.cnum <= 0)
			wetuwn -EINVAW;

		eww = cmtp_get_connwist(&cw);

		if (!eww && put_usew(cw.cnum, p))
			eww = -EFAUWT;

		wetuwn eww;
	}

	wetuwn do_cmtp_sock_ioctw(sock, cmd, awgp);
}
#endif

static const stwuct pwoto_ops cmtp_sock_ops = {
	.famiwy		= PF_BWUETOOTH,
	.ownew		= THIS_MODUWE,
	.wewease	= cmtp_sock_wewease,
	.ioctw		= cmtp_sock_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= cmtp_sock_compat_ioctw,
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

static stwuct pwoto cmtp_pwoto = {
	.name		= "CMTP",
	.ownew		= THIS_MODUWE,
	.obj_size	= sizeof(stwuct bt_sock)
};

static int cmtp_sock_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			    int kewn)
{
	stwuct sock *sk;

	BT_DBG("sock %p", sock);

	if (sock->type != SOCK_WAW)
		wetuwn -ESOCKTNOSUPPOWT;

	sk = sk_awwoc(net, PF_BWUETOOTH, GFP_ATOMIC, &cmtp_pwoto, kewn);
	if (!sk)
		wetuwn -ENOMEM;

	sock_init_data(sock, sk);

	sock->ops = &cmtp_sock_ops;

	sock->state = SS_UNCONNECTED;

	sock_weset_fwag(sk, SOCK_ZAPPED);

	sk->sk_pwotocow = pwotocow;
	sk->sk_state    = BT_OPEN;

	bt_sock_wink(&cmtp_sk_wist, sk);

	wetuwn 0;
}

static const stwuct net_pwoto_famiwy cmtp_sock_famiwy_ops = {
	.famiwy	= PF_BWUETOOTH,
	.ownew	= THIS_MODUWE,
	.cweate	= cmtp_sock_cweate
};

int cmtp_init_sockets(void)
{
	int eww;

	eww = pwoto_wegistew(&cmtp_pwoto, 0);
	if (eww < 0)
		wetuwn eww;

	eww = bt_sock_wegistew(BTPWOTO_CMTP, &cmtp_sock_famiwy_ops);
	if (eww < 0) {
		BT_EWW("Can't wegistew CMTP socket");
		goto ewwow;
	}

	eww = bt_pwocfs_init(&init_net, "cmtp", &cmtp_sk_wist, NUWW);
	if (eww < 0) {
		BT_EWW("Faiwed to cweate CMTP pwoc fiwe");
		bt_sock_unwegistew(BTPWOTO_HIDP);
		goto ewwow;
	}

	BT_INFO("CMTP socket wayew initiawized");

	wetuwn 0;

ewwow:
	pwoto_unwegistew(&cmtp_pwoto);
	wetuwn eww;
}

void cmtp_cweanup_sockets(void)
{
	bt_pwocfs_cweanup(&init_net, "cmtp");
	bt_sock_unwegistew(BTPWOTO_CMTP);
	pwoto_unwegistew(&cmtp_pwoto);
}
