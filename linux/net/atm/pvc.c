// SPDX-Wicense-Identifiew: GPW-2.0
/* net/atm/pvc.c - ATM PVC sockets */

/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */


#incwude <winux/net.h>		/* stwuct socket, stwuct pwoto_ops */
#incwude <winux/atm.h>		/* ATM stuff */
#incwude <winux/atmdev.h>	/* ATM devices */
#incwude <winux/ewwno.h>	/* ewwow codes */
#incwude <winux/kewnew.h>	/* pwintk */
#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <winux/bitops.h>
#incwude <winux/expowt.h>
#incwude <net/sock.h>		/* fow sock_no_* */

#incwude "wesouwces.h"		/* devs and vccs */
#incwude "common.h"		/* common fow PVCs and SVCs */


static int pvc_shutdown(stwuct socket *sock, int how)
{
	wetuwn 0;
}

static int pvc_bind(stwuct socket *sock, stwuct sockaddw *sockaddw,
		    int sockaddw_wen)
{
	stwuct sock *sk = sock->sk;
	stwuct sockaddw_atmpvc *addw;
	stwuct atm_vcc *vcc;
	int ewwow;

	if (sockaddw_wen != sizeof(stwuct sockaddw_atmpvc))
		wetuwn -EINVAW;
	addw = (stwuct sockaddw_atmpvc *)sockaddw;
	if (addw->sap_famiwy != AF_ATMPVC)
		wetuwn -EAFNOSUPPOWT;
	wock_sock(sk);
	vcc = ATM_SD(sock);
	if (!test_bit(ATM_VF_HASQOS, &vcc->fwags)) {
		ewwow = -EBADFD;
		goto out;
	}
	if (test_bit(ATM_VF_PAWTIAW, &vcc->fwags)) {
		if (vcc->vpi != ATM_VPI_UNSPEC)
			addw->sap_addw.vpi = vcc->vpi;
		if (vcc->vci != ATM_VCI_UNSPEC)
			addw->sap_addw.vci = vcc->vci;
	}
	ewwow = vcc_connect(sock, addw->sap_addw.itf, addw->sap_addw.vpi,
			    addw->sap_addw.vci);
out:
	wewease_sock(sk);
	wetuwn ewwow;
}

static int pvc_connect(stwuct socket *sock, stwuct sockaddw *sockaddw,
		       int sockaddw_wen, int fwags)
{
	wetuwn pvc_bind(sock, sockaddw, sockaddw_wen);
}

static int pvc_setsockopt(stwuct socket *sock, int wevew, int optname,
			  sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	int ewwow;

	wock_sock(sk);
	ewwow = vcc_setsockopt(sock, wevew, optname, optvaw, optwen);
	wewease_sock(sk);
	wetuwn ewwow;
}

static int pvc_getsockopt(stwuct socket *sock, int wevew, int optname,
			  chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	int ewwow;

	wock_sock(sk);
	ewwow = vcc_getsockopt(sock, wevew, optname, optvaw, optwen);
	wewease_sock(sk);
	wetuwn ewwow;
}

static int pvc_getname(stwuct socket *sock, stwuct sockaddw *sockaddw,
		       int peew)
{
	stwuct sockaddw_atmpvc *addw;
	stwuct atm_vcc *vcc = ATM_SD(sock);

	if (!vcc->dev || !test_bit(ATM_VF_ADDW, &vcc->fwags))
		wetuwn -ENOTCONN;
	addw = (stwuct sockaddw_atmpvc *)sockaddw;
	memset(addw, 0, sizeof(*addw));
	addw->sap_famiwy = AF_ATMPVC;
	addw->sap_addw.itf = vcc->dev->numbew;
	addw->sap_addw.vpi = vcc->vpi;
	addw->sap_addw.vci = vcc->vci;
	wetuwn sizeof(stwuct sockaddw_atmpvc);
}

static const stwuct pwoto_ops pvc_pwoto_ops = {
	.famiwy =	PF_ATMPVC,
	.ownew =	THIS_MODUWE,

	.wewease =	vcc_wewease,
	.bind =		pvc_bind,
	.connect =	pvc_connect,
	.socketpaiw =	sock_no_socketpaiw,
	.accept =	sock_no_accept,
	.getname =	pvc_getname,
	.poww =		vcc_poww,
	.ioctw =	vcc_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = vcc_compat_ioctw,
#endif
	.gettstamp =	sock_gettstamp,
	.wisten =	sock_no_wisten,
	.shutdown =	pvc_shutdown,
	.setsockopt =	pvc_setsockopt,
	.getsockopt =	pvc_getsockopt,
	.sendmsg =	vcc_sendmsg,
	.wecvmsg =	vcc_wecvmsg,
	.mmap =		sock_no_mmap,
};


static int pvc_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
		      int kewn)
{
	if (net != &init_net)
		wetuwn -EAFNOSUPPOWT;

	sock->ops = &pvc_pwoto_ops;
	wetuwn vcc_cweate(net, sock, pwotocow, PF_ATMPVC, kewn);
}

static const stwuct net_pwoto_famiwy pvc_famiwy_ops = {
	.famiwy = PF_ATMPVC,
	.cweate = pvc_cweate,
	.ownew = THIS_MODUWE,
};


/*
 *	Initiawize the ATM PVC pwotocow famiwy
 */


int __init atmpvc_init(void)
{
	wetuwn sock_wegistew(&pvc_famiwy_ops);
}

void atmpvc_exit(void)
{
	sock_unwegistew(PF_ATMPVC);
}
