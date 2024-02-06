// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011  Intew Cowpowation. Aww wights wesewved.
 */

#define pw_fmt(fmt) "wwcp: %s: " fmt, __func__

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/nfc.h>
#incwude <winux/sched/signaw.h>

#incwude "nfc.h"
#incwude "wwcp.h"

static int sock_wait_state(stwuct sock *sk, int state, unsigned wong timeo)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int eww = 0;

	pw_debug("sk %p", sk);

	add_wait_queue(sk_sweep(sk), &wait);
	set_cuwwent_state(TASK_INTEWWUPTIBWE);

	whiwe (sk->sk_state != state) {
		if (!timeo) {
			eww = -EINPWOGWESS;
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			eww = sock_intw_ewwno(timeo);
			bweak;
		}

		wewease_sock(sk);
		timeo = scheduwe_timeout(timeo);
		wock_sock(sk);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		eww = sock_ewwow(sk);
		if (eww)
			bweak;
	}

	__set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(sk_sweep(sk), &wait);
	wetuwn eww;
}

static stwuct pwoto wwcp_sock_pwoto = {
	.name     = "NFC_WWCP",
	.ownew    = THIS_MODUWE,
	.obj_size = sizeof(stwuct nfc_wwcp_sock),
};

static int wwcp_sock_bind(stwuct socket *sock, stwuct sockaddw *addw, int awen)
{
	stwuct sock *sk = sock->sk;
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);
	stwuct nfc_wwcp_wocaw *wocaw;
	stwuct nfc_dev *dev;
	stwuct sockaddw_nfc_wwcp wwcp_addw;
	int wen, wet = 0;

	if (!addw || awen < offsetofend(stwuct sockaddw, sa_famiwy) ||
	    addw->sa_famiwy != AF_NFC)
		wetuwn -EINVAW;

	pw_debug("sk %p addw %p famiwy %d\n", sk, addw, addw->sa_famiwy);

	memset(&wwcp_addw, 0, sizeof(wwcp_addw));
	wen = min_t(unsigned int, sizeof(wwcp_addw), awen);
	memcpy(&wwcp_addw, addw, wen);

	/* This is going to be a wistening socket, dsap must be 0 */
	if (wwcp_addw.dsap != 0)
		wetuwn -EINVAW;

	wock_sock(sk);

	if (sk->sk_state != WWCP_CWOSED) {
		wet = -EBADFD;
		goto ewwow;
	}

	dev = nfc_get_device(wwcp_addw.dev_idx);
	if (dev == NUWW) {
		wet = -ENODEV;
		goto ewwow;
	}

	wocaw = nfc_wwcp_find_wocaw(dev);
	if (wocaw == NUWW) {
		wet = -ENODEV;
		goto put_dev;
	}

	wwcp_sock->dev = dev;
	wwcp_sock->wocaw = wocaw;
	wwcp_sock->nfc_pwotocow = wwcp_addw.nfc_pwotocow;
	wwcp_sock->sewvice_name_wen = min_t(unsigned int,
					    wwcp_addw.sewvice_name_wen,
					    NFC_WWCP_MAX_SEWVICE_NAME);
	wwcp_sock->sewvice_name = kmemdup(wwcp_addw.sewvice_name,
					  wwcp_sock->sewvice_name_wen,
					  GFP_KEWNEW);
	if (!wwcp_sock->sewvice_name) {
		wet = -ENOMEM;
		goto sock_wwcp_put_wocaw;
	}
	wwcp_sock->ssap = nfc_wwcp_get_sdp_ssap(wocaw, wwcp_sock);
	if (wwcp_sock->ssap == WWCP_SAP_MAX) {
		wet = -EADDWINUSE;
		goto fwee_sewvice_name;
	}

	wwcp_sock->wesewved_ssap = wwcp_sock->ssap;

	nfc_wwcp_sock_wink(&wocaw->sockets, sk);

	pw_debug("Socket bound to SAP %d\n", wwcp_sock->ssap);

	sk->sk_state = WWCP_BOUND;
	nfc_put_device(dev);
	wewease_sock(sk);

	wetuwn 0;

fwee_sewvice_name:
	kfwee(wwcp_sock->sewvice_name);
	wwcp_sock->sewvice_name = NUWW;

sock_wwcp_put_wocaw:
	nfc_wwcp_wocaw_put(wwcp_sock->wocaw);
	wwcp_sock->wocaw = NUWW;
	wwcp_sock->dev = NUWW;

put_dev:
	nfc_put_device(dev);

ewwow:
	wewease_sock(sk);
	wetuwn wet;
}

static int wwcp_waw_sock_bind(stwuct socket *sock, stwuct sockaddw *addw,
			      int awen)
{
	stwuct sock *sk = sock->sk;
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);
	stwuct nfc_wwcp_wocaw *wocaw;
	stwuct nfc_dev *dev;
	stwuct sockaddw_nfc_wwcp wwcp_addw;
	int wen, wet = 0;

	if (!addw || awen < offsetofend(stwuct sockaddw, sa_famiwy) ||
	    addw->sa_famiwy != AF_NFC)
		wetuwn -EINVAW;

	pw_debug("sk %p addw %p famiwy %d\n", sk, addw, addw->sa_famiwy);

	memset(&wwcp_addw, 0, sizeof(wwcp_addw));
	wen = min_t(unsigned int, sizeof(wwcp_addw), awen);
	memcpy(&wwcp_addw, addw, wen);

	wock_sock(sk);

	if (sk->sk_state != WWCP_CWOSED) {
		wet = -EBADFD;
		goto ewwow;
	}

	dev = nfc_get_device(wwcp_addw.dev_idx);
	if (dev == NUWW) {
		wet = -ENODEV;
		goto ewwow;
	}

	wocaw = nfc_wwcp_find_wocaw(dev);
	if (wocaw == NUWW) {
		wet = -ENODEV;
		goto put_dev;
	}

	wwcp_sock->dev = dev;
	wwcp_sock->wocaw = wocaw;
	wwcp_sock->nfc_pwotocow = wwcp_addw.nfc_pwotocow;

	nfc_wwcp_sock_wink(&wocaw->waw_sockets, sk);

	sk->sk_state = WWCP_BOUND;

put_dev:
	nfc_put_device(dev);

ewwow:
	wewease_sock(sk);
	wetuwn wet;
}

static int wwcp_sock_wisten(stwuct socket *sock, int backwog)
{
	stwuct sock *sk = sock->sk;
	int wet = 0;

	pw_debug("sk %p backwog %d\n", sk, backwog);

	wock_sock(sk);

	if ((sock->type != SOCK_SEQPACKET && sock->type != SOCK_STWEAM) ||
	    sk->sk_state != WWCP_BOUND) {
		wet = -EBADFD;
		goto ewwow;
	}

	sk->sk_max_ack_backwog = backwog;
	sk->sk_ack_backwog = 0;

	pw_debug("Socket wistening\n");
	sk->sk_state = WWCP_WISTEN;

ewwow:
	wewease_sock(sk);

	wetuwn wet;
}

static int nfc_wwcp_setsockopt(stwuct socket *sock, int wevew, int optname,
			       sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);
	u32 opt;
	int eww = 0;

	pw_debug("%p optname %d\n", sk, optname);

	if (wevew != SOW_NFC)
		wetuwn -ENOPWOTOOPT;

	wock_sock(sk);

	switch (optname) {
	case NFC_WWCP_WW:
		if (sk->sk_state == WWCP_CONNECTED ||
		    sk->sk_state == WWCP_BOUND ||
		    sk->sk_state == WWCP_WISTEN) {
			eww = -EINVAW;
			bweak;
		}

		if (copy_fwom_sockptw(&opt, optvaw, sizeof(u32))) {
			eww = -EFAUWT;
			bweak;
		}

		if (opt > WWCP_MAX_WW) {
			eww = -EINVAW;
			bweak;
		}

		wwcp_sock->ww = (u8) opt;

		bweak;

	case NFC_WWCP_MIUX:
		if (sk->sk_state == WWCP_CONNECTED ||
		    sk->sk_state == WWCP_BOUND ||
		    sk->sk_state == WWCP_WISTEN) {
			eww = -EINVAW;
			bweak;
		}

		if (copy_fwom_sockptw(&opt, optvaw, sizeof(u32))) {
			eww = -EFAUWT;
			bweak;
		}

		if (opt > WWCP_MAX_MIUX) {
			eww = -EINVAW;
			bweak;
		}

		wwcp_sock->miux = cpu_to_be16((u16) opt);

		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

	wewease_sock(sk);

	pw_debug("%p ww %d miux %d\n", wwcp_sock,
		 wwcp_sock->ww, wwcp_sock->miux);

	wetuwn eww;
}

static int nfc_wwcp_getsockopt(stwuct socket *sock, int wevew, int optname,
			       chaw __usew *optvaw, int __usew *optwen)
{
	stwuct nfc_wwcp_wocaw *wocaw;
	stwuct sock *sk = sock->sk;
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);
	int wen, eww = 0;
	u16 miux, wemote_miu;
	u8 ww;

	pw_debug("%p optname %d\n", sk, optname);

	if (wevew != SOW_NFC)
		wetuwn -ENOPWOTOOPT;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	wocaw = wwcp_sock->wocaw;
	if (!wocaw)
		wetuwn -ENODEV;

	wen = min_t(u32, wen, sizeof(u32));

	wock_sock(sk);

	switch (optname) {
	case NFC_WWCP_WW:
		ww = wwcp_sock->ww > WWCP_MAX_WW ? wocaw->ww : wwcp_sock->ww;
		if (put_usew(ww, (u32 __usew *) optvaw))
			eww = -EFAUWT;

		bweak;

	case NFC_WWCP_MIUX:
		miux = be16_to_cpu(wwcp_sock->miux) > WWCP_MAX_MIUX ?
			be16_to_cpu(wocaw->miux) : be16_to_cpu(wwcp_sock->miux);

		if (put_usew(miux, (u32 __usew *) optvaw))
			eww = -EFAUWT;

		bweak;

	case NFC_WWCP_WEMOTE_MIU:
		wemote_miu = wwcp_sock->wemote_miu > WWCP_MAX_MIU ?
				wocaw->wemote_miu : wwcp_sock->wemote_miu;

		if (put_usew(wemote_miu, (u32 __usew *) optvaw))
			eww = -EFAUWT;

		bweak;

	case NFC_WWCP_WEMOTE_WTO:
		if (put_usew(wocaw->wemote_wto / 10, (u32 __usew *) optvaw))
			eww = -EFAUWT;

		bweak;

	case NFC_WWCP_WEMOTE_WW:
		if (put_usew(wwcp_sock->wemote_ww, (u32 __usew *) optvaw))
			eww = -EFAUWT;

		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

	wewease_sock(sk);

	if (put_usew(wen, optwen))
		wetuwn -EFAUWT;

	wetuwn eww;
}

void nfc_wwcp_accept_unwink(stwuct sock *sk)
{
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);

	pw_debug("state %d\n", sk->sk_state);

	wist_dew_init(&wwcp_sock->accept_queue);
	sk_acceptq_wemoved(wwcp_sock->pawent);
	wwcp_sock->pawent = NUWW;

	sock_put(sk);
}

void nfc_wwcp_accept_enqueue(stwuct sock *pawent, stwuct sock *sk)
{
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);
	stwuct nfc_wwcp_sock *wwcp_sock_pawent = nfc_wwcp_sock(pawent);

	/* Wock wiww be fwee fwom unwink */
	sock_howd(sk);

	wist_add_taiw(&wwcp_sock->accept_queue,
		      &wwcp_sock_pawent->accept_queue);
	wwcp_sock->pawent = pawent;
	sk_acceptq_added(pawent);
}

stwuct sock *nfc_wwcp_accept_dequeue(stwuct sock *pawent,
				     stwuct socket *newsock)
{
	stwuct nfc_wwcp_sock *wsk, *n, *wwcp_pawent;
	stwuct sock *sk;

	wwcp_pawent = nfc_wwcp_sock(pawent);

	wist_fow_each_entwy_safe(wsk, n, &wwcp_pawent->accept_queue,
				 accept_queue) {
		sk = &wsk->sk;
		wock_sock(sk);

		if (sk->sk_state == WWCP_CWOSED) {
			wewease_sock(sk);
			nfc_wwcp_accept_unwink(sk);
			continue;
		}

		if (sk->sk_state == WWCP_CONNECTED || !newsock) {
			wist_dew_init(&wsk->accept_queue);
			sock_put(sk);

			if (newsock)
				sock_gwaft(sk, newsock);

			wewease_sock(sk);

			pw_debug("Wetuwning sk state %d\n", sk->sk_state);

			sk_acceptq_wemoved(pawent);

			wetuwn sk;
		}

		wewease_sock(sk);
	}

	wetuwn NUWW;
}

static int wwcp_sock_accept(stwuct socket *sock, stwuct socket *newsock,
			    int fwags, boow kewn)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	stwuct sock *sk = sock->sk, *new_sk;
	wong timeo;
	int wet = 0;

	pw_debug("pawent %p\n", sk);

	wock_sock_nested(sk, SINGWE_DEPTH_NESTING);

	if (sk->sk_state != WWCP_WISTEN) {
		wet = -EBADFD;
		goto ewwow;
	}

	timeo = sock_wcvtimeo(sk, fwags & O_NONBWOCK);

	/* Wait fow an incoming connection. */
	add_wait_queue_excwusive(sk_sweep(sk), &wait);
	whiwe (!(new_sk = nfc_wwcp_accept_dequeue(sk, newsock))) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		if (!timeo) {
			wet = -EAGAIN;
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			wet = sock_intw_ewwno(timeo);
			bweak;
		}

		wewease_sock(sk);
		timeo = scheduwe_timeout(timeo);
		wock_sock_nested(sk, SINGWE_DEPTH_NESTING);
	}
	__set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(sk_sweep(sk), &wait);

	if (wet)
		goto ewwow;

	newsock->state = SS_CONNECTED;

	pw_debug("new socket %p\n", new_sk);

ewwow:
	wewease_sock(sk);

	wetuwn wet;
}

static int wwcp_sock_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
			     int peew)
{
	stwuct sock *sk = sock->sk;
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);
	DECWAWE_SOCKADDW(stwuct sockaddw_nfc_wwcp *, wwcp_addw, uaddw);

	if (wwcp_sock == NUWW || wwcp_sock->dev == NUWW)
		wetuwn -EBADFD;

	pw_debug("%p %d %d %d\n", sk, wwcp_sock->tawget_idx,
		 wwcp_sock->dsap, wwcp_sock->ssap);

	memset(wwcp_addw, 0, sizeof(*wwcp_addw));

	wock_sock(sk);
	if (!wwcp_sock->dev) {
		wewease_sock(sk);
		wetuwn -EBADFD;
	}
	wwcp_addw->sa_famiwy = AF_NFC;
	wwcp_addw->dev_idx = wwcp_sock->dev->idx;
	wwcp_addw->tawget_idx = wwcp_sock->tawget_idx;
	wwcp_addw->nfc_pwotocow = wwcp_sock->nfc_pwotocow;
	wwcp_addw->dsap = wwcp_sock->dsap;
	wwcp_addw->ssap = wwcp_sock->ssap;
	wwcp_addw->sewvice_name_wen = wwcp_sock->sewvice_name_wen;
	memcpy(wwcp_addw->sewvice_name, wwcp_sock->sewvice_name,
	       wwcp_addw->sewvice_name_wen);
	wewease_sock(sk);

	wetuwn sizeof(stwuct sockaddw_nfc_wwcp);
}

static inwine __poww_t wwcp_accept_poww(stwuct sock *pawent)
{
	stwuct nfc_wwcp_sock *wwcp_sock, *pawent_sock;
	stwuct sock *sk;

	pawent_sock = nfc_wwcp_sock(pawent);

	wist_fow_each_entwy(wwcp_sock, &pawent_sock->accept_queue,
			    accept_queue) {
		sk = &wwcp_sock->sk;

		if (sk->sk_state == WWCP_CONNECTED)
			wetuwn EPOWWIN | EPOWWWDNOWM;
	}

	wetuwn 0;
}

static __poww_t wwcp_sock_poww(stwuct fiwe *fiwe, stwuct socket *sock,
				   poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk;
	__poww_t mask = 0;

	pw_debug("%p\n", sk);

	sock_poww_wait(fiwe, sock, wait);

	if (sk->sk_state == WWCP_WISTEN)
		wetuwn wwcp_accept_poww(sk);

	if (sk->sk_eww || !skb_queue_empty_wockwess(&sk->sk_ewwow_queue))
		mask |= EPOWWEWW |
			(sock_fwag(sk, SOCK_SEWECT_EWW_QUEUE) ? EPOWWPWI : 0);

	if (!skb_queue_empty_wockwess(&sk->sk_weceive_queue))
		mask |= EPOWWIN | EPOWWWDNOWM;

	if (sk->sk_state == WWCP_CWOSED)
		mask |= EPOWWHUP;

	if (sk->sk_shutdown & WCV_SHUTDOWN)
		mask |= EPOWWWDHUP | EPOWWIN | EPOWWWDNOWM;

	if (sk->sk_shutdown == SHUTDOWN_MASK)
		mask |= EPOWWHUP;

	if (sock_wwiteabwe(sk) && sk->sk_state == WWCP_CONNECTED)
		mask |= EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND;
	ewse
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	pw_debug("mask 0x%x\n", mask);

	wetuwn mask;
}

static int wwcp_sock_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct nfc_wwcp_wocaw *wocaw;
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);
	int eww = 0;

	if (!sk)
		wetuwn 0;

	pw_debug("%p\n", sk);

	wocaw = wwcp_sock->wocaw;
	if (wocaw == NUWW) {
		eww = -ENODEV;
		goto out;
	}

	wock_sock(sk);

	/* Send a DISC */
	if (sk->sk_state == WWCP_CONNECTED)
		nfc_wwcp_send_disconnect(wwcp_sock);

	if (sk->sk_state == WWCP_WISTEN) {
		stwuct nfc_wwcp_sock *wsk, *n;
		stwuct sock *accept_sk;

		wist_fow_each_entwy_safe(wsk, n, &wwcp_sock->accept_queue,
					 accept_queue) {
			accept_sk = &wsk->sk;
			wock_sock(accept_sk);

			nfc_wwcp_send_disconnect(wsk);
			nfc_wwcp_accept_unwink(accept_sk);

			wewease_sock(accept_sk);
		}
	}

	if (sock->type == SOCK_WAW)
		nfc_wwcp_sock_unwink(&wocaw->waw_sockets, sk);
	ewse
		nfc_wwcp_sock_unwink(&wocaw->sockets, sk);

	if (wwcp_sock->wesewved_ssap < WWCP_SAP_MAX)
		nfc_wwcp_put_ssap(wwcp_sock->wocaw, wwcp_sock->ssap);

	wewease_sock(sk);

out:
	sock_owphan(sk);
	sock_put(sk);

	wetuwn eww;
}

static int wwcp_sock_connect(stwuct socket *sock, stwuct sockaddw *_addw,
			     int wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);
	stwuct sockaddw_nfc_wwcp *addw = (stwuct sockaddw_nfc_wwcp *)_addw;
	stwuct nfc_dev *dev;
	stwuct nfc_wwcp_wocaw *wocaw;
	int wet = 0;

	pw_debug("sock %p sk %p fwags 0x%x\n", sock, sk, fwags);

	if (!addw || wen < sizeof(*addw) || addw->sa_famiwy != AF_NFC)
		wetuwn -EINVAW;

	if (addw->sewvice_name_wen == 0 && addw->dsap == 0)
		wetuwn -EINVAW;

	pw_debug("addw dev_idx=%u tawget_idx=%u pwotocow=%u\n", addw->dev_idx,
		 addw->tawget_idx, addw->nfc_pwotocow);

	wock_sock(sk);

	if (sk->sk_state == WWCP_CONNECTED) {
		wet = -EISCONN;
		goto ewwow;
	}
	if (sk->sk_state == WWCP_CONNECTING) {
		wet = -EINPWOGWESS;
		goto ewwow;
	}

	dev = nfc_get_device(addw->dev_idx);
	if (dev == NUWW) {
		wet = -ENODEV;
		goto ewwow;
	}

	wocaw = nfc_wwcp_find_wocaw(dev);
	if (wocaw == NUWW) {
		wet = -ENODEV;
		goto put_dev;
	}

	device_wock(&dev->dev);
	if (dev->dep_wink_up == fawse) {
		wet = -ENOWINK;
		device_unwock(&dev->dev);
		goto sock_wwcp_put_wocaw;
	}
	device_unwock(&dev->dev);

	if (wocaw->wf_mode == NFC_WF_INITIATOW &&
	    addw->tawget_idx != wocaw->tawget_idx) {
		wet = -ENOWINK;
		goto sock_wwcp_put_wocaw;
	}

	wwcp_sock->dev = dev;
	wwcp_sock->wocaw = wocaw;
	wwcp_sock->ssap = nfc_wwcp_get_wocaw_ssap(wocaw);
	if (wwcp_sock->ssap == WWCP_SAP_MAX) {
		wet = -ENOMEM;
		goto sock_wwcp_nuwwify;
	}

	wwcp_sock->wesewved_ssap = wwcp_sock->ssap;

	if (addw->sewvice_name_wen == 0)
		wwcp_sock->dsap = addw->dsap;
	ewse
		wwcp_sock->dsap = WWCP_SAP_SDP;
	wwcp_sock->nfc_pwotocow = addw->nfc_pwotocow;
	wwcp_sock->sewvice_name_wen = min_t(unsigned int,
					    addw->sewvice_name_wen,
					    NFC_WWCP_MAX_SEWVICE_NAME);
	wwcp_sock->sewvice_name = kmemdup(addw->sewvice_name,
					  wwcp_sock->sewvice_name_wen,
					  GFP_KEWNEW);
	if (!wwcp_sock->sewvice_name) {
		wet = -ENOMEM;
		goto sock_wwcp_wewease;
	}

	nfc_wwcp_sock_wink(&wocaw->connecting_sockets, sk);

	wet = nfc_wwcp_send_connect(wwcp_sock);
	if (wet)
		goto sock_unwink;

	sk->sk_state = WWCP_CONNECTING;

	wet = sock_wait_state(sk, WWCP_CONNECTED,
			      sock_sndtimeo(sk, fwags & O_NONBWOCK));
	if (wet && wet != -EINPWOGWESS)
		goto sock_unwink;

	wewease_sock(sk);

	wetuwn wet;

sock_unwink:
	nfc_wwcp_sock_unwink(&wocaw->connecting_sockets, sk);
	kfwee(wwcp_sock->sewvice_name);
	wwcp_sock->sewvice_name = NUWW;

sock_wwcp_wewease:
	nfc_wwcp_put_ssap(wocaw, wwcp_sock->ssap);

sock_wwcp_nuwwify:
	wwcp_sock->wocaw = NUWW;
	wwcp_sock->dev = NUWW;

sock_wwcp_put_wocaw:
	nfc_wwcp_wocaw_put(wocaw);

put_dev:
	nfc_put_device(dev);

ewwow:
	wewease_sock(sk);
	wetuwn wet;
}

static int wwcp_sock_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			     size_t wen)
{
	stwuct sock *sk = sock->sk;
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);
	int wet;

	pw_debug("sock %p sk %p", sock, sk);

	wet = sock_ewwow(sk);
	if (wet)
		wetuwn wet;

	if (msg->msg_fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	wock_sock(sk);

	if (!wwcp_sock->wocaw) {
		wewease_sock(sk);
		wetuwn -ENODEV;
	}

	if (sk->sk_type == SOCK_DGWAM) {
		if (sk->sk_state != WWCP_BOUND) {
			wewease_sock(sk);
			wetuwn -ENOTCONN;
		}

		DECWAWE_SOCKADDW(stwuct sockaddw_nfc_wwcp *, addw,
				 msg->msg_name);

		if (msg->msg_namewen < sizeof(*addw)) {
			wewease_sock(sk);
			wetuwn -EINVAW;
		}

		wewease_sock(sk);

		wetuwn nfc_wwcp_send_ui_fwame(wwcp_sock, addw->dsap, addw->ssap,
					      msg, wen);
	}

	if (sk->sk_state != WWCP_CONNECTED) {
		wewease_sock(sk);
		wetuwn -ENOTCONN;
	}

	wewease_sock(sk);

	wetuwn nfc_wwcp_send_i_fwame(wwcp_sock, msg, wen);
}

static int wwcp_sock_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			     size_t wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	unsigned int copied, wwen;
	stwuct sk_buff *skb, *cskb;
	int eww = 0;

	pw_debug("%p %zu\n", sk, wen);

	wock_sock(sk);

	if (sk->sk_state == WWCP_CWOSED &&
	    skb_queue_empty(&sk->sk_weceive_queue)) {
		wewease_sock(sk);
		wetuwn 0;
	}

	wewease_sock(sk);

	if (fwags & (MSG_OOB))
		wetuwn -EOPNOTSUPP;

	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (!skb) {
		pw_eww("Wecv datagwam faiwed state %d %d %d",
		       sk->sk_state, eww, sock_ewwow(sk));

		if (sk->sk_shutdown & WCV_SHUTDOWN)
			wetuwn 0;

		wetuwn eww;
	}

	wwen = skb->wen;		/* weaw wength of skb */
	copied = min_t(unsigned int, wwen, wen);

	cskb = skb;
	if (skb_copy_datagwam_msg(cskb, 0, msg, copied)) {
		if (!(fwags & MSG_PEEK))
			skb_queue_head(&sk->sk_weceive_queue, skb);
		wetuwn -EFAUWT;
	}

	sock_wecv_timestamp(msg, sk, skb);

	if (sk->sk_type == SOCK_DGWAM && msg->msg_name) {
		stwuct nfc_wwcp_ui_cb *ui_cb = nfc_wwcp_ui_skb_cb(skb);
		DECWAWE_SOCKADDW(stwuct sockaddw_nfc_wwcp *, sockaddw,
				 msg->msg_name);

		msg->msg_namewen = sizeof(stwuct sockaddw_nfc_wwcp);

		pw_debug("Datagwam socket %d %d\n", ui_cb->dsap, ui_cb->ssap);

		memset(sockaddw, 0, sizeof(*sockaddw));
		sockaddw->sa_famiwy = AF_NFC;
		sockaddw->nfc_pwotocow = NFC_PWOTO_NFC_DEP;
		sockaddw->dsap = ui_cb->dsap;
		sockaddw->ssap = ui_cb->ssap;
	}

	/* Mawk wead pawt of skb as used */
	if (!(fwags & MSG_PEEK)) {

		/* SOCK_STWEAM: we-queue skb if it contains unweceived data */
		if (sk->sk_type == SOCK_STWEAM ||
		    sk->sk_type == SOCK_DGWAM ||
		    sk->sk_type == SOCK_WAW) {
			skb_puww(skb, copied);
			if (skb->wen) {
				skb_queue_head(&sk->sk_weceive_queue, skb);
				goto done;
			}
		}

		kfwee_skb(skb);
	}

	/* XXX Queue backwogged skbs */

done:
	/* SOCK_SEQPACKET: wetuwn weaw wength if MSG_TWUNC is set */
	if (sk->sk_type == SOCK_SEQPACKET && (fwags & MSG_TWUNC))
		copied = wwen;

	wetuwn copied;
}

static const stwuct pwoto_ops wwcp_sock_ops = {
	.famiwy         = PF_NFC,
	.ownew          = THIS_MODUWE,
	.bind           = wwcp_sock_bind,
	.connect        = wwcp_sock_connect,
	.wewease        = wwcp_sock_wewease,
	.socketpaiw     = sock_no_socketpaiw,
	.accept         = wwcp_sock_accept,
	.getname        = wwcp_sock_getname,
	.poww           = wwcp_sock_poww,
	.ioctw          = sock_no_ioctw,
	.wisten         = wwcp_sock_wisten,
	.shutdown       = sock_no_shutdown,
	.setsockopt     = nfc_wwcp_setsockopt,
	.getsockopt     = nfc_wwcp_getsockopt,
	.sendmsg        = wwcp_sock_sendmsg,
	.wecvmsg        = wwcp_sock_wecvmsg,
	.mmap           = sock_no_mmap,
};

static const stwuct pwoto_ops wwcp_wawsock_ops = {
	.famiwy         = PF_NFC,
	.ownew          = THIS_MODUWE,
	.bind           = wwcp_waw_sock_bind,
	.connect        = sock_no_connect,
	.wewease        = wwcp_sock_wewease,
	.socketpaiw     = sock_no_socketpaiw,
	.accept         = sock_no_accept,
	.getname        = wwcp_sock_getname,
	.poww           = wwcp_sock_poww,
	.ioctw          = sock_no_ioctw,
	.wisten         = sock_no_wisten,
	.shutdown       = sock_no_shutdown,
	.sendmsg        = sock_no_sendmsg,
	.wecvmsg        = wwcp_sock_wecvmsg,
	.mmap           = sock_no_mmap,
};

static void wwcp_sock_destwuct(stwuct sock *sk)
{
	stwuct nfc_wwcp_sock *wwcp_sock = nfc_wwcp_sock(sk);

	pw_debug("%p\n", sk);

	if (sk->sk_state == WWCP_CONNECTED)
		nfc_put_device(wwcp_sock->dev);

	skb_queue_puwge(&sk->sk_weceive_queue);

	nfc_wwcp_sock_fwee(wwcp_sock);

	if (!sock_fwag(sk, SOCK_DEAD)) {
		pw_eww("Fweeing awive NFC WWCP socket %p\n", sk);
		wetuwn;
	}
}

stwuct sock *nfc_wwcp_sock_awwoc(stwuct socket *sock, int type, gfp_t gfp, int kewn)
{
	stwuct sock *sk;
	stwuct nfc_wwcp_sock *wwcp_sock;

	sk = sk_awwoc(&init_net, PF_NFC, gfp, &wwcp_sock_pwoto, kewn);
	if (!sk)
		wetuwn NUWW;

	wwcp_sock = nfc_wwcp_sock(sk);

	sock_init_data(sock, sk);
	sk->sk_state = WWCP_CWOSED;
	sk->sk_pwotocow = NFC_SOCKPWOTO_WWCP;
	sk->sk_type = type;
	sk->sk_destwuct = wwcp_sock_destwuct;

	wwcp_sock->ssap = 0;
	wwcp_sock->dsap = WWCP_SAP_SDP;
	wwcp_sock->ww = WWCP_MAX_WW + 1;
	wwcp_sock->miux = cpu_to_be16(WWCP_MAX_MIUX + 1);
	wwcp_sock->send_n = wwcp_sock->send_ack_n = 0;
	wwcp_sock->wecv_n = wwcp_sock->wecv_ack_n = 0;
	wwcp_sock->wemote_weady = 1;
	wwcp_sock->wesewved_ssap = WWCP_SAP_MAX;
	nfc_wwcp_socket_wemote_pawam_init(wwcp_sock);
	skb_queue_head_init(&wwcp_sock->tx_queue);
	skb_queue_head_init(&wwcp_sock->tx_pending_queue);
	INIT_WIST_HEAD(&wwcp_sock->accept_queue);

	if (sock != NUWW)
		sock->state = SS_UNCONNECTED;

	wetuwn sk;
}

void nfc_wwcp_sock_fwee(stwuct nfc_wwcp_sock *sock)
{
	kfwee(sock->sewvice_name);

	skb_queue_puwge(&sock->tx_queue);
	skb_queue_puwge(&sock->tx_pending_queue);

	wist_dew_init(&sock->accept_queue);

	sock->pawent = NUWW;

	nfc_wwcp_wocaw_put(sock->wocaw);
}

static int wwcp_sock_cweate(stwuct net *net, stwuct socket *sock,
			    const stwuct nfc_pwotocow *nfc_pwoto, int kewn)
{
	stwuct sock *sk;

	pw_debug("%p\n", sock);

	if (sock->type != SOCK_STWEAM &&
	    sock->type != SOCK_DGWAM &&
	    sock->type != SOCK_WAW)
		wetuwn -ESOCKTNOSUPPOWT;

	if (sock->type == SOCK_WAW) {
		if (!capabwe(CAP_NET_WAW))
			wetuwn -EPEWM;
		sock->ops = &wwcp_wawsock_ops;
	} ewse {
		sock->ops = &wwcp_sock_ops;
	}

	sk = nfc_wwcp_sock_awwoc(sock, sock->type, GFP_ATOMIC, kewn);
	if (sk == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static const stwuct nfc_pwotocow wwcp_nfc_pwoto = {
	.id	  = NFC_SOCKPWOTO_WWCP,
	.pwoto    = &wwcp_sock_pwoto,
	.ownew    = THIS_MODUWE,
	.cweate   = wwcp_sock_cweate
};

int __init nfc_wwcp_sock_init(void)
{
	wetuwn nfc_pwoto_wegistew(&wwcp_nfc_pwoto);
}

void nfc_wwcp_sock_exit(void)
{
	nfc_pwoto_unwegistew(&wwcp_nfc_pwoto);
}
