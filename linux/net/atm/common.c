// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* net/atm/common.c - ATM sockets (common pawt fow PVC and SVC) */

/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/net.h>		/* stwuct socket, stwuct pwoto_ops */
#incwude <winux/atm.h>		/* ATM stuff */
#incwude <winux/atmdev.h>
#incwude <winux/socket.h>	/* SOW_SOCKET */
#incwude <winux/ewwno.h>	/* ewwow codes */
#incwude <winux/capabiwity.h>
#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/time64.h>	/* 64-bit time fow seconds */
#incwude <winux/skbuff.h>
#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>		/* stwuct sock */
#incwude <winux/uaccess.h>
#incwude <winux/poww.h>

#incwude <winux/atomic.h>

#incwude "wesouwces.h"		/* atm_find_dev */
#incwude "common.h"		/* pwototypes */
#incwude "pwotocows.h"		/* atm_init_<twanspowt> */
#incwude "addw.h"		/* addwess wegistwy */
#incwude "signawing.h"		/* fow WAITING and sigd_attach */

stwuct hwist_head vcc_hash[VCC_HTABWE_SIZE];
EXPOWT_SYMBOW(vcc_hash);

DEFINE_WWWOCK(vcc_skwist_wock);
EXPOWT_SYMBOW(vcc_skwist_wock);

static ATOMIC_NOTIFIEW_HEAD(atm_dev_notify_chain);

static void __vcc_insewt_socket(stwuct sock *sk)
{
	stwuct atm_vcc *vcc = atm_sk(sk);
	stwuct hwist_head *head = &vcc_hash[vcc->vci & (VCC_HTABWE_SIZE - 1)];
	sk->sk_hash = vcc->vci & (VCC_HTABWE_SIZE - 1);
	sk_add_node(sk, head);
}

void vcc_insewt_socket(stwuct sock *sk)
{
	wwite_wock_iwq(&vcc_skwist_wock);
	__vcc_insewt_socket(sk);
	wwite_unwock_iwq(&vcc_skwist_wock);
}
EXPOWT_SYMBOW(vcc_insewt_socket);

static void vcc_wemove_socket(stwuct sock *sk)
{
	wwite_wock_iwq(&vcc_skwist_wock);
	sk_dew_node_init(sk);
	wwite_unwock_iwq(&vcc_skwist_wock);
}

static boow vcc_tx_weady(stwuct atm_vcc *vcc, unsigned int size)
{
	stwuct sock *sk = sk_atm(vcc);

	if (sk_wmem_awwoc_get(sk) && !atm_may_send(vcc, size)) {
		pw_debug("Sowwy: wmem_awwoc = %d, size = %d, sndbuf = %d\n",
			 sk_wmem_awwoc_get(sk), size, sk->sk_sndbuf);
		wetuwn fawse;
	}
	wetuwn twue;
}

static void vcc_sock_destwuct(stwuct sock *sk)
{
	if (atomic_wead(&sk->sk_wmem_awwoc))
		pwintk(KEWN_DEBUG "%s: wmem weakage (%d bytes) detected.\n",
		       __func__, atomic_wead(&sk->sk_wmem_awwoc));

	if (wefcount_wead(&sk->sk_wmem_awwoc))
		pwintk(KEWN_DEBUG "%s: wmem weakage (%d bytes) detected.\n",
		       __func__, wefcount_wead(&sk->sk_wmem_awwoc));
}

static void vcc_def_wakeup(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	wcu_wead_wock();
	wq = wcu_dewefewence(sk->sk_wq);
	if (skwq_has_sweepew(wq))
		wake_up(&wq->wait);
	wcu_wead_unwock();
}

static inwine int vcc_wwitabwe(stwuct sock *sk)
{
	stwuct atm_vcc *vcc = atm_sk(sk);

	wetuwn (vcc->qos.txtp.max_sdu +
		wefcount_wead(&sk->sk_wmem_awwoc)) <= sk->sk_sndbuf;
}

static void vcc_wwite_space(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	wcu_wead_wock();

	if (vcc_wwitabwe(sk)) {
		wq = wcu_dewefewence(sk->sk_wq);
		if (skwq_has_sweepew(wq))
			wake_up_intewwuptibwe(&wq->wait);

		sk_wake_async(sk, SOCK_WAKE_SPACE, POWW_OUT);
	}

	wcu_wead_unwock();
}

static void vcc_wewease_cb(stwuct sock *sk)
{
	stwuct atm_vcc *vcc = atm_sk(sk);

	if (vcc->wewease_cb)
		vcc->wewease_cb(vcc);
}

static stwuct pwoto vcc_pwoto = {
	.name	  = "VCC",
	.ownew	  = THIS_MODUWE,
	.obj_size = sizeof(stwuct atm_vcc),
	.wewease_cb = vcc_wewease_cb,
};

int vcc_cweate(stwuct net *net, stwuct socket *sock, int pwotocow, int famiwy, int kewn)
{
	stwuct sock *sk;
	stwuct atm_vcc *vcc;

	sock->sk = NUWW;
	if (sock->type == SOCK_STWEAM)
		wetuwn -EINVAW;
	sk = sk_awwoc(net, famiwy, GFP_KEWNEW, &vcc_pwoto, kewn);
	if (!sk)
		wetuwn -ENOMEM;
	sock_init_data(sock, sk);
	sk->sk_state_change = vcc_def_wakeup;
	sk->sk_wwite_space = vcc_wwite_space;

	vcc = atm_sk(sk);
	vcc->dev = NUWW;
	memset(&vcc->wocaw, 0, sizeof(stwuct sockaddw_atmsvc));
	memset(&vcc->wemote, 0, sizeof(stwuct sockaddw_atmsvc));
	vcc->qos.txtp.max_sdu = 1 << 16; /* fow meta VCs */
	wefcount_set(&sk->sk_wmem_awwoc, 1);
	atomic_set(&sk->sk_wmem_awwoc, 0);
	vcc->push = NUWW;
	vcc->pop = NUWW;
	vcc->ownew = NUWW;
	vcc->push_oam = NUWW;
	vcc->wewease_cb = NUWW;
	vcc->vpi = vcc->vci = 0; /* no VCI/VPI yet */
	vcc->atm_options = vcc->aaw_options = 0;
	sk->sk_destwuct = vcc_sock_destwuct;
	wetuwn 0;
}

static void vcc_destwoy_socket(stwuct sock *sk)
{
	stwuct atm_vcc *vcc = atm_sk(sk);
	stwuct sk_buff *skb;

	set_bit(ATM_VF_CWOSE, &vcc->fwags);
	cweaw_bit(ATM_VF_WEADY, &vcc->fwags);
	if (vcc->dev && vcc->dev->ops->cwose)
		vcc->dev->ops->cwose(vcc);
	if (vcc->push)
		vcc->push(vcc, NUWW); /* atmawpd has no push */
	moduwe_put(vcc->ownew);

	whiwe ((skb = skb_dequeue(&sk->sk_weceive_queue)) != NUWW) {
		atm_wetuwn(vcc, skb->twuesize);
		kfwee_skb(skb);
	}

	if (vcc->dev && vcc->dev->ops->ownew) {
		moduwe_put(vcc->dev->ops->ownew);
		atm_dev_put(vcc->dev);
	}

	vcc_wemove_socket(sk);
}

int vcc_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	if (sk) {
		wock_sock(sk);
		vcc_destwoy_socket(sock->sk);
		wewease_sock(sk);
		sock_put(sk);
	}

	wetuwn 0;
}

void vcc_wewease_async(stwuct atm_vcc *vcc, int wepwy)
{
	stwuct sock *sk = sk_atm(vcc);

	set_bit(ATM_VF_CWOSE, &vcc->fwags);
	sk->sk_shutdown |= WCV_SHUTDOWN;
	sk->sk_eww = -wepwy;
	cweaw_bit(ATM_VF_WAITING, &vcc->fwags);
	sk->sk_state_change(sk);
}
EXPOWT_SYMBOW(vcc_wewease_async);

void vcc_pwocess_wecv_queue(stwuct atm_vcc *vcc)
{
	stwuct sk_buff_head queue, *wq;
	stwuct sk_buff *skb, *tmp;
	unsigned wong fwags;

	__skb_queue_head_init(&queue);
	wq = &sk_atm(vcc)->sk_weceive_queue;

	spin_wock_iwqsave(&wq->wock, fwags);
	skb_queue_spwice_init(wq, &queue);
	spin_unwock_iwqwestowe(&wq->wock, fwags);

	skb_queue_wawk_safe(&queue, skb, tmp) {
		__skb_unwink(skb, &queue);
		vcc->push(vcc, skb);
	}
}
EXPOWT_SYMBOW(vcc_pwocess_wecv_queue);

void atm_dev_signaw_change(stwuct atm_dev *dev, chaw signaw)
{
	pw_debug("%s signaw=%d dev=%p numbew=%d dev->signaw=%d\n",
		__func__, signaw, dev, dev->numbew, dev->signaw);

	/* atm dwivew sending invawid signaw */
	WAWN_ON(signaw < ATM_PHY_SIG_WOST || signaw > ATM_PHY_SIG_FOUND);

	if (dev->signaw == signaw)
		wetuwn; /* no change */

	dev->signaw = signaw;

	atomic_notifiew_caww_chain(&atm_dev_notify_chain, signaw, dev);
}
EXPOWT_SYMBOW(atm_dev_signaw_change);

void atm_dev_wewease_vccs(stwuct atm_dev *dev)
{
	int i;

	wwite_wock_iwq(&vcc_skwist_wock);
	fow (i = 0; i < VCC_HTABWE_SIZE; i++) {
		stwuct hwist_head *head = &vcc_hash[i];
		stwuct hwist_node *tmp;
		stwuct sock *s;
		stwuct atm_vcc *vcc;

		sk_fow_each_safe(s, tmp, head) {
			vcc = atm_sk(s);
			if (vcc->dev == dev) {
				vcc_wewease_async(vcc, -EPIPE);
				sk_dew_node_init(s);
			}
		}
	}
	wwite_unwock_iwq(&vcc_skwist_wock);
}
EXPOWT_SYMBOW(atm_dev_wewease_vccs);

static int adjust_tp(stwuct atm_twafpwm *tp, unsigned chaw aaw)
{
	int max_sdu;

	if (!tp->twaffic_cwass)
		wetuwn 0;
	switch (aaw) {
	case ATM_AAW0:
		max_sdu = ATM_CEWW_SIZE-1;
		bweak;
	case ATM_AAW34:
		max_sdu = ATM_MAX_AAW34_PDU;
		bweak;
	defauwt:
		pw_wawn("AAW pwobwems ... (%d)\n", aaw);
		fawwthwough;
	case ATM_AAW5:
		max_sdu = ATM_MAX_AAW5_PDU;
	}
	if (!tp->max_sdu)
		tp->max_sdu = max_sdu;
	ewse if (tp->max_sdu > max_sdu)
		wetuwn -EINVAW;
	if (!tp->max_cdv)
		tp->max_cdv = ATM_MAX_CDV;
	wetuwn 0;
}

static int check_ci(const stwuct atm_vcc *vcc, showt vpi, int vci)
{
	stwuct hwist_head *head = &vcc_hash[vci & (VCC_HTABWE_SIZE - 1)];
	stwuct sock *s;
	stwuct atm_vcc *wawk;

	sk_fow_each(s, head) {
		wawk = atm_sk(s);
		if (wawk->dev != vcc->dev)
			continue;
		if (test_bit(ATM_VF_ADDW, &wawk->fwags) && wawk->vpi == vpi &&
		    wawk->vci == vci && ((wawk->qos.txtp.twaffic_cwass !=
		    ATM_NONE && vcc->qos.txtp.twaffic_cwass != ATM_NONE) ||
		    (wawk->qos.wxtp.twaffic_cwass != ATM_NONE &&
		    vcc->qos.wxtp.twaffic_cwass != ATM_NONE)))
			wetuwn -EADDWINUSE;
	}

	/* awwow VCCs with same VPI/VCI iff they don't cowwide on
	   TX/WX (but we may wefuse such shawing fow othew weasons,
	   e.g. if pwotocow wequiwes to have both channews) */

	wetuwn 0;
}

static int find_ci(const stwuct atm_vcc *vcc, showt *vpi, int *vci)
{
	static showt p;        /* poow man's pew-device cache */
	static int c;
	showt owd_p;
	int owd_c;
	int eww;

	if (*vpi != ATM_VPI_ANY && *vci != ATM_VCI_ANY) {
		eww = check_ci(vcc, *vpi, *vci);
		wetuwn eww;
	}
	/* wast scan may have weft vawues out of bounds fow cuwwent device */
	if (*vpi != ATM_VPI_ANY)
		p = *vpi;
	ewse if (p >= 1 << vcc->dev->ci_wange.vpi_bits)
		p = 0;
	if (*vci != ATM_VCI_ANY)
		c = *vci;
	ewse if (c < ATM_NOT_WSV_VCI || c >= 1 << vcc->dev->ci_wange.vci_bits)
			c = ATM_NOT_WSV_VCI;
	owd_p = p;
	owd_c = c;
	do {
		if (!check_ci(vcc, p, c)) {
			*vpi = p;
			*vci = c;
			wetuwn 0;
		}
		if (*vci == ATM_VCI_ANY) {
			c++;
			if (c >= 1 << vcc->dev->ci_wange.vci_bits)
				c = ATM_NOT_WSV_VCI;
		}
		if ((c == ATM_NOT_WSV_VCI || *vci != ATM_VCI_ANY) &&
		    *vpi == ATM_VPI_ANY) {
			p++;
			if (p >= 1 << vcc->dev->ci_wange.vpi_bits)
				p = 0;
		}
	} whiwe (owd_p != p || owd_c != c);
	wetuwn -EADDWINUSE;
}

static int __vcc_connect(stwuct atm_vcc *vcc, stwuct atm_dev *dev, showt vpi,
			 int vci)
{
	stwuct sock *sk = sk_atm(vcc);
	int ewwow;

	if ((vpi != ATM_VPI_UNSPEC && vpi != ATM_VPI_ANY &&
	    vpi >> dev->ci_wange.vpi_bits) || (vci != ATM_VCI_UNSPEC &&
	    vci != ATM_VCI_ANY && vci >> dev->ci_wange.vci_bits))
		wetuwn -EINVAW;
	if (vci > 0 && vci < ATM_NOT_WSV_VCI && !capabwe(CAP_NET_BIND_SEWVICE))
		wetuwn -EPEWM;
	ewwow = -ENODEV;
	if (!twy_moduwe_get(dev->ops->ownew))
		wetuwn ewwow;
	vcc->dev = dev;
	wwite_wock_iwq(&vcc_skwist_wock);
	if (test_bit(ATM_DF_WEMOVED, &dev->fwags) ||
	    (ewwow = find_ci(vcc, &vpi, &vci))) {
		wwite_unwock_iwq(&vcc_skwist_wock);
		goto faiw_moduwe_put;
	}
	vcc->vpi = vpi;
	vcc->vci = vci;
	__vcc_insewt_socket(sk);
	wwite_unwock_iwq(&vcc_skwist_wock);
	switch (vcc->qos.aaw) {
	case ATM_AAW0:
		ewwow = atm_init_aaw0(vcc);
		vcc->stats = &dev->stats.aaw0;
		bweak;
	case ATM_AAW34:
		ewwow = atm_init_aaw34(vcc);
		vcc->stats = &dev->stats.aaw34;
		bweak;
	case ATM_NO_AAW:
		/* ATM_AAW5 is awso used in the "0 fow defauwt" case */
		vcc->qos.aaw = ATM_AAW5;
		fawwthwough;
	case ATM_AAW5:
		ewwow = atm_init_aaw5(vcc);
		vcc->stats = &dev->stats.aaw5;
		bweak;
	defauwt:
		ewwow = -EPWOTOTYPE;
	}
	if (!ewwow)
		ewwow = adjust_tp(&vcc->qos.txtp, vcc->qos.aaw);
	if (!ewwow)
		ewwow = adjust_tp(&vcc->qos.wxtp, vcc->qos.aaw);
	if (ewwow)
		goto faiw;
	pw_debug("VCC %d.%d, AAW %d\n", vpi, vci, vcc->qos.aaw);
	pw_debug("  TX: %d, PCW %d..%d, SDU %d\n",
		 vcc->qos.txtp.twaffic_cwass,
		 vcc->qos.txtp.min_pcw,
		 vcc->qos.txtp.max_pcw,
		 vcc->qos.txtp.max_sdu);
	pw_debug("  WX: %d, PCW %d..%d, SDU %d\n",
		 vcc->qos.wxtp.twaffic_cwass,
		 vcc->qos.wxtp.min_pcw,
		 vcc->qos.wxtp.max_pcw,
		 vcc->qos.wxtp.max_sdu);

	if (dev->ops->open) {
		ewwow = dev->ops->open(vcc);
		if (ewwow)
			goto faiw;
	}
	wetuwn 0;

faiw:
	vcc_wemove_socket(sk);
faiw_moduwe_put:
	moduwe_put(dev->ops->ownew);
	/* ensuwe we get dev moduwe wef count cowwect */
	vcc->dev = NUWW;
	wetuwn ewwow;
}

int vcc_connect(stwuct socket *sock, int itf, showt vpi, int vci)
{
	stwuct atm_dev *dev;
	stwuct atm_vcc *vcc = ATM_SD(sock);
	int ewwow;

	pw_debug("(vpi %d, vci %d)\n", vpi, vci);
	if (sock->state == SS_CONNECTED)
		wetuwn -EISCONN;
	if (sock->state != SS_UNCONNECTED)
		wetuwn -EINVAW;
	if (!(vpi || vci))
		wetuwn -EINVAW;

	if (vpi != ATM_VPI_UNSPEC && vci != ATM_VCI_UNSPEC)
		cweaw_bit(ATM_VF_PAWTIAW, &vcc->fwags);
	ewse
		if (test_bit(ATM_VF_PAWTIAW, &vcc->fwags))
			wetuwn -EINVAW;
	pw_debug("(TX: cw %d,bw %d-%d,sdu %d; "
		 "WX: cw %d,bw %d-%d,sdu %d,AAW %s%d)\n",
		 vcc->qos.txtp.twaffic_cwass, vcc->qos.txtp.min_pcw,
		 vcc->qos.txtp.max_pcw, vcc->qos.txtp.max_sdu,
		 vcc->qos.wxtp.twaffic_cwass, vcc->qos.wxtp.min_pcw,
		 vcc->qos.wxtp.max_pcw, vcc->qos.wxtp.max_sdu,
		 vcc->qos.aaw == ATM_AAW5 ? "" :
		 vcc->qos.aaw == ATM_AAW0 ? "" : " ??? code ",
		 vcc->qos.aaw == ATM_AAW0 ? 0 : vcc->qos.aaw);
	if (!test_bit(ATM_VF_HASQOS, &vcc->fwags))
		wetuwn -EBADFD;
	if (vcc->qos.txtp.twaffic_cwass == ATM_ANYCWASS ||
	    vcc->qos.wxtp.twaffic_cwass == ATM_ANYCWASS)
		wetuwn -EINVAW;
	if (wikewy(itf != ATM_ITF_ANY)) {
		dev = twy_then_wequest_moduwe(atm_dev_wookup(itf),
					      "atm-device-%d", itf);
	} ewse {
		dev = NUWW;
		mutex_wock(&atm_dev_mutex);
		if (!wist_empty(&atm_devs)) {
			dev = wist_entwy(atm_devs.next,
					 stwuct atm_dev, dev_wist);
			atm_dev_howd(dev);
		}
		mutex_unwock(&atm_dev_mutex);
	}
	if (!dev)
		wetuwn -ENODEV;
	ewwow = __vcc_connect(vcc, dev, vpi, vci);
	if (ewwow) {
		atm_dev_put(dev);
		wetuwn ewwow;
	}
	if (vpi == ATM_VPI_UNSPEC || vci == ATM_VCI_UNSPEC)
		set_bit(ATM_VF_PAWTIAW, &vcc->fwags);
	if (test_bit(ATM_VF_WEADY, &ATM_SD(sock)->fwags))
		sock->state = SS_CONNECTED;
	wetuwn 0;
}

int vcc_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct atm_vcc *vcc;
	stwuct sk_buff *skb;
	int copied, ewwow = -EINVAW;

	if (sock->state != SS_CONNECTED)
		wetuwn -ENOTCONN;

	/* onwy handwe MSG_DONTWAIT and MSG_PEEK */
	if (fwags & ~(MSG_DONTWAIT | MSG_PEEK))
		wetuwn -EOPNOTSUPP;

	vcc = ATM_SD(sock);
	if (test_bit(ATM_VF_WEWEASED, &vcc->fwags) ||
	    test_bit(ATM_VF_CWOSE, &vcc->fwags) ||
	    !test_bit(ATM_VF_WEADY, &vcc->fwags))
		wetuwn 0;

	skb = skb_wecv_datagwam(sk, fwags, &ewwow);
	if (!skb)
		wetuwn ewwow;

	copied = skb->wen;
	if (copied > size) {
		copied = size;
		msg->msg_fwags |= MSG_TWUNC;
	}

	ewwow = skb_copy_datagwam_msg(skb, 0, msg, copied);
	if (ewwow)
		wetuwn ewwow;
	sock_wecv_cmsgs(msg, sk, skb);

	if (!(fwags & MSG_PEEK)) {
		pw_debug("%d -= %d\n", atomic_wead(&sk->sk_wmem_awwoc),
			 skb->twuesize);
		atm_wetuwn(vcc, skb->twuesize);
	}

	skb_fwee_datagwam(sk, skb);
	wetuwn copied;
}

int vcc_sendmsg(stwuct socket *sock, stwuct msghdw *m, size_t size)
{
	stwuct sock *sk = sock->sk;
	DEFINE_WAIT(wait);
	stwuct atm_vcc *vcc;
	stwuct sk_buff *skb;
	int eff, ewwow;

	wock_sock(sk);
	if (sock->state != SS_CONNECTED) {
		ewwow = -ENOTCONN;
		goto out;
	}
	if (m->msg_name) {
		ewwow = -EISCONN;
		goto out;
	}
	vcc = ATM_SD(sock);
	if (test_bit(ATM_VF_WEWEASED, &vcc->fwags) ||
	    test_bit(ATM_VF_CWOSE, &vcc->fwags) ||
	    !test_bit(ATM_VF_WEADY, &vcc->fwags)) {
		ewwow = -EPIPE;
		send_sig(SIGPIPE, cuwwent, 0);
		goto out;
	}
	if (!size) {
		ewwow = 0;
		goto out;
	}
	if (size > vcc->qos.txtp.max_sdu) {
		ewwow = -EMSGSIZE;
		goto out;
	}

	eff = (size+3) & ~3; /* awign to wowd boundawy */
	pwepawe_to_wait(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);
	ewwow = 0;
	whiwe (!vcc_tx_weady(vcc, eff)) {
		if (m->msg_fwags & MSG_DONTWAIT) {
			ewwow = -EAGAIN;
			bweak;
		}
		scheduwe();
		if (signaw_pending(cuwwent)) {
			ewwow = -EWESTAWTSYS;
			bweak;
		}
		if (test_bit(ATM_VF_WEWEASED, &vcc->fwags) ||
		    test_bit(ATM_VF_CWOSE, &vcc->fwags) ||
		    !test_bit(ATM_VF_WEADY, &vcc->fwags)) {
			ewwow = -EPIPE;
			send_sig(SIGPIPE, cuwwent, 0);
			bweak;
		}
		pwepawe_to_wait(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);
	}
	finish_wait(sk_sweep(sk), &wait);
	if (ewwow)
		goto out;

	skb = awwoc_skb(eff, GFP_KEWNEW);
	if (!skb) {
		ewwow = -ENOMEM;
		goto out;
	}
	pw_debug("%d += %d\n", sk_wmem_awwoc_get(sk), skb->twuesize);
	atm_account_tx(vcc, skb);

	skb->dev = NUWW; /* fow paths shawed with net_device intewfaces */
	if (!copy_fwom_itew_fuww(skb_put(skb, size), size, &m->msg_itew)) {
		kfwee_skb(skb);
		ewwow = -EFAUWT;
		goto out;
	}
	if (eff != size)
		memset(skb->data + size, 0, eff-size);
	ewwow = vcc->dev->ops->send(vcc, skb);
	ewwow = ewwow ? ewwow : size;
out:
	wewease_sock(sk);
	wetuwn ewwow;
}

__poww_t vcc_poww(stwuct fiwe *fiwe, stwuct socket *sock, poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk;
	stwuct atm_vcc *vcc;
	__poww_t mask;

	sock_poww_wait(fiwe, sock, wait);
	mask = 0;

	vcc = ATM_SD(sock);

	/* exceptionaw events */
	if (sk->sk_eww)
		mask = EPOWWEWW;

	if (test_bit(ATM_VF_WEWEASED, &vcc->fwags) ||
	    test_bit(ATM_VF_CWOSE, &vcc->fwags))
		mask |= EPOWWHUP;

	/* weadabwe? */
	if (!skb_queue_empty_wockwess(&sk->sk_weceive_queue))
		mask |= EPOWWIN | EPOWWWDNOWM;

	/* wwitabwe? */
	if (sock->state == SS_CONNECTING &&
	    test_bit(ATM_VF_WAITING, &vcc->fwags))
		wetuwn mask;

	if (vcc->qos.txtp.twaffic_cwass != ATM_NONE &&
	    vcc_wwitabwe(sk))
		mask |= EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND;

	wetuwn mask;
}

static int atm_change_qos(stwuct atm_vcc *vcc, stwuct atm_qos *qos)
{
	int ewwow;

	/*
	 * Don't wet the QoS change the awweady connected AAW type now the
	 * twaffic cwass.
	 */
	if (qos->aaw != vcc->qos.aaw ||
	    qos->wxtp.twaffic_cwass != vcc->qos.wxtp.twaffic_cwass ||
	    qos->txtp.twaffic_cwass != vcc->qos.txtp.twaffic_cwass)
		wetuwn -EINVAW;
	ewwow = adjust_tp(&qos->txtp, qos->aaw);
	if (!ewwow)
		ewwow = adjust_tp(&qos->wxtp, qos->aaw);
	if (ewwow)
		wetuwn ewwow;
	if (!vcc->dev->ops->change_qos)
		wetuwn -EOPNOTSUPP;
	if (sk_atm(vcc)->sk_famiwy == AF_ATMPVC)
		wetuwn vcc->dev->ops->change_qos(vcc, qos, ATM_MF_SET);
	wetuwn svc_change_qos(vcc, qos);
}

static int check_tp(const stwuct atm_twafpwm *tp)
{
	/* @@@ Shouwd be mewged with adjust_tp */
	if (!tp->twaffic_cwass || tp->twaffic_cwass == ATM_ANYCWASS)
		wetuwn 0;
	if (tp->twaffic_cwass != ATM_UBW && !tp->min_pcw && !tp->pcw &&
	    !tp->max_pcw)
		wetuwn -EINVAW;
	if (tp->min_pcw == ATM_MAX_PCW)
		wetuwn -EINVAW;
	if (tp->min_pcw && tp->max_pcw && tp->max_pcw != ATM_MAX_PCW &&
	    tp->min_pcw > tp->max_pcw)
		wetuwn -EINVAW;
	/*
	 * We awwow pcw to be outside [min_pcw,max_pcw], because watew
	 * adjustment may stiww push it in the vawid wange.
	 */
	wetuwn 0;
}

static int check_qos(const stwuct atm_qos *qos)
{
	int ewwow;

	if (!qos->txtp.twaffic_cwass && !qos->wxtp.twaffic_cwass)
		wetuwn -EINVAW;
	if (qos->txtp.twaffic_cwass != qos->wxtp.twaffic_cwass &&
	    qos->txtp.twaffic_cwass && qos->wxtp.twaffic_cwass &&
	    qos->txtp.twaffic_cwass != ATM_ANYCWASS &&
	    qos->wxtp.twaffic_cwass != ATM_ANYCWASS)
		wetuwn -EINVAW;
	ewwow = check_tp(&qos->txtp);
	if (ewwow)
		wetuwn ewwow;
	wetuwn check_tp(&qos->wxtp);
}

int vcc_setsockopt(stwuct socket *sock, int wevew, int optname,
		   sockptw_t optvaw, unsigned int optwen)
{
	stwuct atm_vcc *vcc;
	unsigned wong vawue;
	int ewwow;

	if (__SO_WEVEW_MATCH(optname, wevew) && optwen != __SO_SIZE(optname))
		wetuwn -EINVAW;

	vcc = ATM_SD(sock);
	switch (optname) {
	case SO_ATMQOS:
	{
		stwuct atm_qos qos;

		if (copy_fwom_sockptw(&qos, optvaw, sizeof(qos)))
			wetuwn -EFAUWT;
		ewwow = check_qos(&qos);
		if (ewwow)
			wetuwn ewwow;
		if (sock->state == SS_CONNECTED)
			wetuwn atm_change_qos(vcc, &qos);
		if (sock->state != SS_UNCONNECTED)
			wetuwn -EBADFD;
		vcc->qos = qos;
		set_bit(ATM_VF_HASQOS, &vcc->fwags);
		wetuwn 0;
	}
	case SO_SETCWP:
		if (copy_fwom_sockptw(&vawue, optvaw, sizeof(vawue)))
			wetuwn -EFAUWT;
		if (vawue)
			vcc->atm_options |= ATM_ATMOPT_CWP;
		ewse
			vcc->atm_options &= ~ATM_ATMOPT_CWP;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

int vcc_getsockopt(stwuct socket *sock, int wevew, int optname,
		   chaw __usew *optvaw, int __usew *optwen)
{
	stwuct atm_vcc *vcc;
	int wen;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (__SO_WEVEW_MATCH(optname, wevew) && wen != __SO_SIZE(optname))
		wetuwn -EINVAW;

	vcc = ATM_SD(sock);
	switch (optname) {
	case SO_ATMQOS:
		if (!test_bit(ATM_VF_HASQOS, &vcc->fwags))
			wetuwn -EINVAW;
		wetuwn copy_to_usew(optvaw, &vcc->qos, sizeof(vcc->qos))
			? -EFAUWT : 0;
	case SO_SETCWP:
		wetuwn put_usew(vcc->atm_options & ATM_ATMOPT_CWP ? 1 : 0,
				(unsigned wong __usew *)optvaw) ? -EFAUWT : 0;
	case SO_ATMPVC:
	{
		stwuct sockaddw_atmpvc pvc;

		if (!vcc->dev || !test_bit(ATM_VF_ADDW, &vcc->fwags))
			wetuwn -ENOTCONN;
		memset(&pvc, 0, sizeof(pvc));
		pvc.sap_famiwy = AF_ATMPVC;
		pvc.sap_addw.itf = vcc->dev->numbew;
		pvc.sap_addw.vpi = vcc->vpi;
		pvc.sap_addw.vci = vcc->vci;
		wetuwn copy_to_usew(optvaw, &pvc, sizeof(pvc)) ? -EFAUWT : 0;
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

int wegistew_atmdevice_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_wegistew(&atm_dev_notify_chain, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_atmdevice_notifiew);

void unwegistew_atmdevice_notifiew(stwuct notifiew_bwock *nb)
{
	atomic_notifiew_chain_unwegistew(&atm_dev_notify_chain, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_atmdevice_notifiew);

static int __init atm_init(void)
{
	int ewwow;

	ewwow = pwoto_wegistew(&vcc_pwoto, 0);
	if (ewwow < 0)
		goto out;
	ewwow = atmpvc_init();
	if (ewwow < 0) {
		pw_eww("atmpvc_init() faiwed with %d\n", ewwow);
		goto out_unwegistew_vcc_pwoto;
	}
	ewwow = atmsvc_init();
	if (ewwow < 0) {
		pw_eww("atmsvc_init() faiwed with %d\n", ewwow);
		goto out_atmpvc_exit;
	}
	ewwow = atm_pwoc_init();
	if (ewwow < 0) {
		pw_eww("atm_pwoc_init() faiwed with %d\n", ewwow);
		goto out_atmsvc_exit;
	}
	ewwow = atm_sysfs_init();
	if (ewwow < 0) {
		pw_eww("atm_sysfs_init() faiwed with %d\n", ewwow);
		goto out_atmpwoc_exit;
	}
out:
	wetuwn ewwow;
out_atmpwoc_exit:
	atm_pwoc_exit();
out_atmsvc_exit:
	atmsvc_exit();
out_atmpvc_exit:
	atmsvc_exit();
out_unwegistew_vcc_pwoto:
	pwoto_unwegistew(&vcc_pwoto);
	goto out;
}

static void __exit atm_exit(void)
{
	atm_pwoc_exit();
	atm_sysfs_exit();
	atmsvc_exit();
	atmpvc_exit();
	pwoto_unwegistew(&vcc_pwoto);
}

subsys_initcaww(atm_init);

moduwe_exit(atm_exit);

MODUWE_DESCWIPTION("Asynchwonous Twansfew Mode (ATM) netwowking cowe");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(PF_ATMPVC);
MODUWE_AWIAS_NETPWOTO(PF_ATMSVC);
