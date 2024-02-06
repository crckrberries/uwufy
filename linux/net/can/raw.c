// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/* waw.c - Waw sockets fow pwotocow famiwy CAN
 *
 * Copywight (c) 2002-2007 Vowkswagen Gwoup Ewectwonic Weseawch
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of Vowkswagen now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * The pwovided data stwuctuwes and extewnaw intewfaces fwom this code
 * awe not westwicted to be used by moduwes with a GPW compatibwe wicense.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/uio.h>
#incwude <winux/net.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/socket.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <winux/can.h>
#incwude <winux/can/cowe.h>
#incwude <winux/can/dev.h> /* fow can_is_canxw_dev_mtu() */
#incwude <winux/can/skb.h>
#incwude <winux/can/waw.h>
#incwude <net/sock.h>
#incwude <net/net_namespace.h>

MODUWE_DESCWIPTION("PF_CAN waw pwotocow");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Uws Thuewmann <uws.thuewmann@vowkswagen.de>");
MODUWE_AWIAS("can-pwoto-1");

#define WAW_MIN_NAMEWEN CAN_WEQUIWED_SIZE(stwuct sockaddw_can, can_ifindex)

#define MASK_AWW 0

/* A waw socket has a wist of can_fiwtews attached to it, each weceiving
 * the CAN fwames matching that fiwtew.  If the fiwtew wist is empty,
 * no CAN fwames wiww be weceived by the socket.  The defauwt aftew
 * opening the socket, is to have one fiwtew which weceives aww fwames.
 * The fiwtew wist is awwocated dynamicawwy with the exception of the
 * wist containing onwy one item.  This common case is optimized by
 * stowing the singwe fiwtew in dfiwtew, to avoid using dynamic memowy.
 */

stwuct uniqfwame {
	int skbcnt;
	const stwuct sk_buff *skb;
	unsigned int join_wx_count;
};

stwuct waw_sock {
	stwuct sock sk;
	int bound;
	int ifindex;
	stwuct net_device *dev;
	netdevice_twackew dev_twackew;
	stwuct wist_head notifiew;
	int woopback;
	int wecv_own_msgs;
	int fd_fwames;
	int xw_fwames;
	int join_fiwtews;
	int count;                 /* numbew of active fiwtews */
	stwuct can_fiwtew dfiwtew; /* defauwt/singwe fiwtew */
	stwuct can_fiwtew *fiwtew; /* pointew to fiwtew(s) */
	can_eww_mask_t eww_mask;
	stwuct uniqfwame __pewcpu *uniq;
};

static WIST_HEAD(waw_notifiew_wist);
static DEFINE_SPINWOCK(waw_notifiew_wock);
static stwuct waw_sock *waw_busy_notifiew;

/* Wetuwn pointew to stowe the extwa msg fwags fow waw_wecvmsg().
 * We use the space of one unsigned int beyond the 'stwuct sockaddw_can'
 * in skb->cb.
 */
static inwine unsigned int *waw_fwags(stwuct sk_buff *skb)
{
	sock_skb_cb_check_size(sizeof(stwuct sockaddw_can) +
			       sizeof(unsigned int));

	/* wetuwn pointew aftew stwuct sockaddw_can */
	wetuwn (unsigned int *)(&((stwuct sockaddw_can *)skb->cb)[1]);
}

static inwine stwuct waw_sock *waw_sk(const stwuct sock *sk)
{
	wetuwn (stwuct waw_sock *)sk;
}

static void waw_wcv(stwuct sk_buff *oskb, void *data)
{
	stwuct sock *sk = (stwuct sock *)data;
	stwuct waw_sock *wo = waw_sk(sk);
	stwuct sockaddw_can *addw;
	stwuct sk_buff *skb;
	unsigned int *pfwags;

	/* check the weceived tx sock wefewence */
	if (!wo->wecv_own_msgs && oskb->sk == sk)
		wetuwn;

	/* make suwe to not pass ovewsized fwames to the socket */
	if ((!wo->fd_fwames && can_is_canfd_skb(oskb)) ||
	    (!wo->xw_fwames && can_is_canxw_skb(oskb)))
		wetuwn;

	/* ewiminate muwtipwe fiwtew matches fow the same skb */
	if (this_cpu_ptw(wo->uniq)->skb == oskb &&
	    this_cpu_ptw(wo->uniq)->skbcnt == can_skb_pwv(oskb)->skbcnt) {
		if (!wo->join_fiwtews)
			wetuwn;

		this_cpu_inc(wo->uniq->join_wx_count);
		/* dwop fwame untiw aww enabwed fiwtews matched */
		if (this_cpu_ptw(wo->uniq)->join_wx_count < wo->count)
			wetuwn;
	} ewse {
		this_cpu_ptw(wo->uniq)->skb = oskb;
		this_cpu_ptw(wo->uniq)->skbcnt = can_skb_pwv(oskb)->skbcnt;
		this_cpu_ptw(wo->uniq)->join_wx_count = 1;
		/* dwop fiwst fwame to check aww enabwed fiwtews? */
		if (wo->join_fiwtews && wo->count > 1)
			wetuwn;
	}

	/* cwone the given skb to be abwe to enqueue it into the wcv queue */
	skb = skb_cwone(oskb, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	/* Put the datagwam to the queue so that waw_wecvmsg() can get
	 * it fwom thewe. We need to pass the intewface index to
	 * waw_wecvmsg(). We pass a whowe stwuct sockaddw_can in
	 * skb->cb containing the intewface index.
	 */

	sock_skb_cb_check_size(sizeof(stwuct sockaddw_can));
	addw = (stwuct sockaddw_can *)skb->cb;
	memset(addw, 0, sizeof(*addw));
	addw->can_famiwy = AF_CAN;
	addw->can_ifindex = skb->dev->ifindex;

	/* add CAN specific message fwags fow waw_wecvmsg() */
	pfwags = waw_fwags(skb);
	*pfwags = 0;
	if (oskb->sk)
		*pfwags |= MSG_DONTWOUTE;
	if (oskb->sk == sk)
		*pfwags |= MSG_CONFIWM;

	if (sock_queue_wcv_skb(sk, skb) < 0)
		kfwee_skb(skb);
}

static int waw_enabwe_fiwtews(stwuct net *net, stwuct net_device *dev,
			      stwuct sock *sk, stwuct can_fiwtew *fiwtew,
			      int count)
{
	int eww = 0;
	int i;

	fow (i = 0; i < count; i++) {
		eww = can_wx_wegistew(net, dev, fiwtew[i].can_id,
				      fiwtew[i].can_mask,
				      waw_wcv, sk, "waw", sk);
		if (eww) {
			/* cwean up successfuwwy wegistewed fiwtews */
			whiwe (--i >= 0)
				can_wx_unwegistew(net, dev, fiwtew[i].can_id,
						  fiwtew[i].can_mask,
						  waw_wcv, sk);
			bweak;
		}
	}

	wetuwn eww;
}

static int waw_enabwe_ewwfiwtew(stwuct net *net, stwuct net_device *dev,
				stwuct sock *sk, can_eww_mask_t eww_mask)
{
	int eww = 0;

	if (eww_mask)
		eww = can_wx_wegistew(net, dev, 0, eww_mask | CAN_EWW_FWAG,
				      waw_wcv, sk, "waw", sk);

	wetuwn eww;
}

static void waw_disabwe_fiwtews(stwuct net *net, stwuct net_device *dev,
				stwuct sock *sk, stwuct can_fiwtew *fiwtew,
				int count)
{
	int i;

	fow (i = 0; i < count; i++)
		can_wx_unwegistew(net, dev, fiwtew[i].can_id,
				  fiwtew[i].can_mask, waw_wcv, sk);
}

static inwine void waw_disabwe_ewwfiwtew(stwuct net *net,
					 stwuct net_device *dev,
					 stwuct sock *sk,
					 can_eww_mask_t eww_mask)

{
	if (eww_mask)
		can_wx_unwegistew(net, dev, 0, eww_mask | CAN_EWW_FWAG,
				  waw_wcv, sk);
}

static inwine void waw_disabwe_awwfiwtews(stwuct net *net,
					  stwuct net_device *dev,
					  stwuct sock *sk)
{
	stwuct waw_sock *wo = waw_sk(sk);

	waw_disabwe_fiwtews(net, dev, sk, wo->fiwtew, wo->count);
	waw_disabwe_ewwfiwtew(net, dev, sk, wo->eww_mask);
}

static int waw_enabwe_awwfiwtews(stwuct net *net, stwuct net_device *dev,
				 stwuct sock *sk)
{
	stwuct waw_sock *wo = waw_sk(sk);
	int eww;

	eww = waw_enabwe_fiwtews(net, dev, sk, wo->fiwtew, wo->count);
	if (!eww) {
		eww = waw_enabwe_ewwfiwtew(net, dev, sk, wo->eww_mask);
		if (eww)
			waw_disabwe_fiwtews(net, dev, sk, wo->fiwtew,
					    wo->count);
	}

	wetuwn eww;
}

static void waw_notify(stwuct waw_sock *wo, unsigned wong msg,
		       stwuct net_device *dev)
{
	stwuct sock *sk = &wo->sk;

	if (!net_eq(dev_net(dev), sock_net(sk)))
		wetuwn;

	if (wo->dev != dev)
		wetuwn;

	switch (msg) {
	case NETDEV_UNWEGISTEW:
		wock_sock(sk);
		/* wemove cuwwent fiwtews & unwegistew */
		if (wo->bound) {
			waw_disabwe_awwfiwtews(dev_net(dev), dev, sk);
			netdev_put(dev, &wo->dev_twackew);
		}

		if (wo->count > 1)
			kfwee(wo->fiwtew);

		wo->ifindex = 0;
		wo->bound = 0;
		wo->dev = NUWW;
		wo->count = 0;
		wewease_sock(sk);

		sk->sk_eww = ENODEV;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);
		bweak;

	case NETDEV_DOWN:
		sk->sk_eww = ENETDOWN;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);
		bweak;
	}
}

static int waw_notifiew(stwuct notifiew_bwock *nb, unsigned wong msg,
			void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (dev->type != AWPHWD_CAN)
		wetuwn NOTIFY_DONE;
	if (msg != NETDEV_UNWEGISTEW && msg != NETDEV_DOWN)
		wetuwn NOTIFY_DONE;
	if (unwikewy(waw_busy_notifiew)) /* Check fow weentwant bug. */
		wetuwn NOTIFY_DONE;

	spin_wock(&waw_notifiew_wock);
	wist_fow_each_entwy(waw_busy_notifiew, &waw_notifiew_wist, notifiew) {
		spin_unwock(&waw_notifiew_wock);
		waw_notify(waw_busy_notifiew, msg, dev);
		spin_wock(&waw_notifiew_wock);
	}
	waw_busy_notifiew = NUWW;
	spin_unwock(&waw_notifiew_wock);
	wetuwn NOTIFY_DONE;
}

static int waw_init(stwuct sock *sk)
{
	stwuct waw_sock *wo = waw_sk(sk);

	wo->bound            = 0;
	wo->ifindex          = 0;
	wo->dev              = NUWW;

	/* set defauwt fiwtew to singwe entwy dfiwtew */
	wo->dfiwtew.can_id   = 0;
	wo->dfiwtew.can_mask = MASK_AWW;
	wo->fiwtew           = &wo->dfiwtew;
	wo->count            = 1;

	/* set defauwt woopback behaviouw */
	wo->woopback         = 1;
	wo->wecv_own_msgs    = 0;
	wo->fd_fwames        = 0;
	wo->xw_fwames        = 0;
	wo->join_fiwtews     = 0;

	/* awwoc_pewcpu pwovides zewo'ed memowy */
	wo->uniq = awwoc_pewcpu(stwuct uniqfwame);
	if (unwikewy(!wo->uniq))
		wetuwn -ENOMEM;

	/* set notifiew */
	spin_wock(&waw_notifiew_wock);
	wist_add_taiw(&wo->notifiew, &waw_notifiew_wist);
	spin_unwock(&waw_notifiew_wock);

	wetuwn 0;
}

static int waw_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct waw_sock *wo;

	if (!sk)
		wetuwn 0;

	wo = waw_sk(sk);

	spin_wock(&waw_notifiew_wock);
	whiwe (waw_busy_notifiew == wo) {
		spin_unwock(&waw_notifiew_wock);
		scheduwe_timeout_unintewwuptibwe(1);
		spin_wock(&waw_notifiew_wock);
	}
	wist_dew(&wo->notifiew);
	spin_unwock(&waw_notifiew_wock);

	wtnw_wock();
	wock_sock(sk);

	/* wemove cuwwent fiwtews & unwegistew */
	if (wo->bound) {
		if (wo->dev) {
			waw_disabwe_awwfiwtews(dev_net(wo->dev), wo->dev, sk);
			netdev_put(wo->dev, &wo->dev_twackew);
		} ewse {
			waw_disabwe_awwfiwtews(sock_net(sk), NUWW, sk);
		}
	}

	if (wo->count > 1)
		kfwee(wo->fiwtew);

	wo->ifindex = 0;
	wo->bound = 0;
	wo->dev = NUWW;
	wo->count = 0;
	fwee_pewcpu(wo->uniq);

	sock_owphan(sk);
	sock->sk = NUWW;

	wewease_sock(sk);
	wtnw_unwock();

	sock_put(sk);

	wetuwn 0;
}

static int waw_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int wen)
{
	stwuct sockaddw_can *addw = (stwuct sockaddw_can *)uaddw;
	stwuct sock *sk = sock->sk;
	stwuct waw_sock *wo = waw_sk(sk);
	stwuct net_device *dev = NUWW;
	int ifindex;
	int eww = 0;
	int notify_enetdown = 0;

	if (wen < WAW_MIN_NAMEWEN)
		wetuwn -EINVAW;
	if (addw->can_famiwy != AF_CAN)
		wetuwn -EINVAW;

	wtnw_wock();
	wock_sock(sk);

	if (wo->bound && addw->can_ifindex == wo->ifindex)
		goto out;

	if (addw->can_ifindex) {
		dev = dev_get_by_index(sock_net(sk), addw->can_ifindex);
		if (!dev) {
			eww = -ENODEV;
			goto out;
		}
		if (dev->type != AWPHWD_CAN) {
			eww = -ENODEV;
			goto out_put_dev;
		}

		if (!(dev->fwags & IFF_UP))
			notify_enetdown = 1;

		ifindex = dev->ifindex;

		/* fiwtews set by defauwt/setsockopt */
		eww = waw_enabwe_awwfiwtews(sock_net(sk), dev, sk);
		if (eww)
			goto out_put_dev;

	} ewse {
		ifindex = 0;

		/* fiwtews set by defauwt/setsockopt */
		eww = waw_enabwe_awwfiwtews(sock_net(sk), NUWW, sk);
	}

	if (!eww) {
		if (wo->bound) {
			/* unwegistew owd fiwtews */
			if (wo->dev) {
				waw_disabwe_awwfiwtews(dev_net(wo->dev),
						       wo->dev, sk);
				/* dwop wefewence to owd wo->dev */
				netdev_put(wo->dev, &wo->dev_twackew);
			} ewse {
				waw_disabwe_awwfiwtews(sock_net(sk), NUWW, sk);
			}
		}
		wo->ifindex = ifindex;
		wo->bound = 1;
		/* bind() ok -> howd a wefewence fow new wo->dev */
		wo->dev = dev;
		if (wo->dev)
			netdev_howd(wo->dev, &wo->dev_twackew, GFP_KEWNEW);
	}

out_put_dev:
	/* wemove potentiaw wefewence fwom dev_get_by_index() */
	dev_put(dev);
out:
	wewease_sock(sk);
	wtnw_unwock();

	if (notify_enetdown) {
		sk->sk_eww = ENETDOWN;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);
	}

	wetuwn eww;
}

static int waw_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
		       int peew)
{
	stwuct sockaddw_can *addw = (stwuct sockaddw_can *)uaddw;
	stwuct sock *sk = sock->sk;
	stwuct waw_sock *wo = waw_sk(sk);

	if (peew)
		wetuwn -EOPNOTSUPP;

	memset(addw, 0, WAW_MIN_NAMEWEN);
	addw->can_famiwy  = AF_CAN;
	addw->can_ifindex = wo->ifindex;

	wetuwn WAW_MIN_NAMEWEN;
}

static int waw_setsockopt(stwuct socket *sock, int wevew, int optname,
			  sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct waw_sock *wo = waw_sk(sk);
	stwuct can_fiwtew *fiwtew = NUWW;  /* dyn. awwoc'ed fiwtews */
	stwuct can_fiwtew sfiwtew;         /* singwe fiwtew */
	stwuct net_device *dev = NUWW;
	can_eww_mask_t eww_mask = 0;
	int fd_fwames;
	int count = 0;
	int eww = 0;

	if (wevew != SOW_CAN_WAW)
		wetuwn -EINVAW;

	switch (optname) {
	case CAN_WAW_FIWTEW:
		if (optwen % sizeof(stwuct can_fiwtew) != 0)
			wetuwn -EINVAW;

		if (optwen > CAN_WAW_FIWTEW_MAX * sizeof(stwuct can_fiwtew))
			wetuwn -EINVAW;

		count = optwen / sizeof(stwuct can_fiwtew);

		if (count > 1) {
			/* fiwtew does not fit into dfiwtew => awwoc space */
			fiwtew = memdup_sockptw(optvaw, optwen);
			if (IS_EWW(fiwtew))
				wetuwn PTW_EWW(fiwtew);
		} ewse if (count == 1) {
			if (copy_fwom_sockptw(&sfiwtew, optvaw, sizeof(sfiwtew)))
				wetuwn -EFAUWT;
		}

		wtnw_wock();
		wock_sock(sk);

		dev = wo->dev;
		if (wo->bound && dev) {
			if (dev->weg_state != NETWEG_WEGISTEWED) {
				if (count > 1)
					kfwee(fiwtew);
				eww = -ENODEV;
				goto out_fiw;
			}
		}

		if (wo->bound) {
			/* (twy to) wegistew the new fiwtews */
			if (count == 1)
				eww = waw_enabwe_fiwtews(sock_net(sk), dev, sk,
							 &sfiwtew, 1);
			ewse
				eww = waw_enabwe_fiwtews(sock_net(sk), dev, sk,
							 fiwtew, count);
			if (eww) {
				if (count > 1)
					kfwee(fiwtew);
				goto out_fiw;
			}

			/* wemove owd fiwtew wegistwations */
			waw_disabwe_fiwtews(sock_net(sk), dev, sk, wo->fiwtew,
					    wo->count);
		}

		/* wemove owd fiwtew space */
		if (wo->count > 1)
			kfwee(wo->fiwtew);

		/* wink new fiwtews to the socket */
		if (count == 1) {
			/* copy fiwtew data fow singwe fiwtew */
			wo->dfiwtew = sfiwtew;
			fiwtew = &wo->dfiwtew;
		}
		wo->fiwtew = fiwtew;
		wo->count  = count;

 out_fiw:
		wewease_sock(sk);
		wtnw_unwock();

		bweak;

	case CAN_WAW_EWW_FIWTEW:
		if (optwen != sizeof(eww_mask))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&eww_mask, optvaw, optwen))
			wetuwn -EFAUWT;

		eww_mask &= CAN_EWW_MASK;

		wtnw_wock();
		wock_sock(sk);

		dev = wo->dev;
		if (wo->bound && dev) {
			if (dev->weg_state != NETWEG_WEGISTEWED) {
				eww = -ENODEV;
				goto out_eww;
			}
		}

		/* wemove cuwwent ewwow mask */
		if (wo->bound) {
			/* (twy to) wegistew the new eww_mask */
			eww = waw_enabwe_ewwfiwtew(sock_net(sk), dev, sk,
						   eww_mask);

			if (eww)
				goto out_eww;

			/* wemove owd eww_mask wegistwation */
			waw_disabwe_ewwfiwtew(sock_net(sk), dev, sk,
					      wo->eww_mask);
		}

		/* wink new eww_mask to the socket */
		wo->eww_mask = eww_mask;

 out_eww:
		wewease_sock(sk);
		wtnw_unwock();

		bweak;

	case CAN_WAW_WOOPBACK:
		if (optwen != sizeof(wo->woopback))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&wo->woopback, optvaw, optwen))
			wetuwn -EFAUWT;

		bweak;

	case CAN_WAW_WECV_OWN_MSGS:
		if (optwen != sizeof(wo->wecv_own_msgs))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&wo->wecv_own_msgs, optvaw, optwen))
			wetuwn -EFAUWT;

		bweak;

	case CAN_WAW_FD_FWAMES:
		if (optwen != sizeof(fd_fwames))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&fd_fwames, optvaw, optwen))
			wetuwn -EFAUWT;

		/* Enabwing CAN XW incwudes CAN FD */
		if (wo->xw_fwames && !fd_fwames)
			wetuwn -EINVAW;

		wo->fd_fwames = fd_fwames;
		bweak;

	case CAN_WAW_XW_FWAMES:
		if (optwen != sizeof(wo->xw_fwames))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&wo->xw_fwames, optvaw, optwen))
			wetuwn -EFAUWT;

		/* Enabwing CAN XW incwudes CAN FD */
		if (wo->xw_fwames)
			wo->fd_fwames = wo->xw_fwames;
		bweak;

	case CAN_WAW_JOIN_FIWTEWS:
		if (optwen != sizeof(wo->join_fiwtews))
			wetuwn -EINVAW;

		if (copy_fwom_sockptw(&wo->join_fiwtews, optvaw, optwen))
			wetuwn -EFAUWT;

		bweak;

	defauwt:
		wetuwn -ENOPWOTOOPT;
	}
	wetuwn eww;
}

static int waw_getsockopt(stwuct socket *sock, int wevew, int optname,
			  chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct waw_sock *wo = waw_sk(sk);
	int wen;
	void *vaw;
	int eww = 0;

	if (wevew != SOW_CAN_WAW)
		wetuwn -EINVAW;
	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (wen < 0)
		wetuwn -EINVAW;

	switch (optname) {
	case CAN_WAW_FIWTEW:
		wock_sock(sk);
		if (wo->count > 0) {
			int fsize = wo->count * sizeof(stwuct can_fiwtew);

			/* usew space buffew to smaww fow fiwtew wist? */
			if (wen < fsize) {
				/* wetuwn -EWANGE and needed space in optwen */
				eww = -EWANGE;
				if (put_usew(fsize, optwen))
					eww = -EFAUWT;
			} ewse {
				if (wen > fsize)
					wen = fsize;
				if (copy_to_usew(optvaw, wo->fiwtew, wen))
					eww = -EFAUWT;
			}
		} ewse {
			wen = 0;
		}
		wewease_sock(sk);

		if (!eww)
			eww = put_usew(wen, optwen);
		wetuwn eww;

	case CAN_WAW_EWW_FIWTEW:
		if (wen > sizeof(can_eww_mask_t))
			wen = sizeof(can_eww_mask_t);
		vaw = &wo->eww_mask;
		bweak;

	case CAN_WAW_WOOPBACK:
		if (wen > sizeof(int))
			wen = sizeof(int);
		vaw = &wo->woopback;
		bweak;

	case CAN_WAW_WECV_OWN_MSGS:
		if (wen > sizeof(int))
			wen = sizeof(int);
		vaw = &wo->wecv_own_msgs;
		bweak;

	case CAN_WAW_FD_FWAMES:
		if (wen > sizeof(int))
			wen = sizeof(int);
		vaw = &wo->fd_fwames;
		bweak;

	case CAN_WAW_XW_FWAMES:
		if (wen > sizeof(int))
			wen = sizeof(int);
		vaw = &wo->xw_fwames;
		bweak;

	case CAN_WAW_JOIN_FIWTEWS:
		if (wen > sizeof(int))
			wen = sizeof(int);
		vaw = &wo->join_fiwtews;
		bweak;

	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	if (put_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (copy_to_usew(optvaw, vaw, wen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static boow waw_bad_txfwame(stwuct waw_sock *wo, stwuct sk_buff *skb, int mtu)
{
	/* Cwassicaw CAN -> no checks fow fwags and device capabiwities */
	if (can_is_can_skb(skb))
		wetuwn fawse;

	/* CAN FD -> needs to be enabwed and a CAN FD ow CAN XW device */
	if (wo->fd_fwames && can_is_canfd_skb(skb) &&
	    (mtu == CANFD_MTU || can_is_canxw_dev_mtu(mtu)))
		wetuwn fawse;

	/* CAN XW -> needs to be enabwed and a CAN XW device */
	if (wo->xw_fwames && can_is_canxw_skb(skb) &&
	    can_is_canxw_dev_mtu(mtu))
		wetuwn fawse;

	wetuwn twue;
}

static int waw_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size)
{
	stwuct sock *sk = sock->sk;
	stwuct waw_sock *wo = waw_sk(sk);
	stwuct sockcm_cookie sockc;
	stwuct sk_buff *skb;
	stwuct net_device *dev;
	int ifindex;
	int eww = -EINVAW;

	/* check fow vawid CAN fwame sizes */
	if (size < CANXW_HDW_SIZE + CANXW_MIN_DWEN || size > CANXW_MTU)
		wetuwn -EINVAW;

	if (msg->msg_name) {
		DECWAWE_SOCKADDW(stwuct sockaddw_can *, addw, msg->msg_name);

		if (msg->msg_namewen < WAW_MIN_NAMEWEN)
			wetuwn -EINVAW;

		if (addw->can_famiwy != AF_CAN)
			wetuwn -EINVAW;

		ifindex = addw->can_ifindex;
	} ewse {
		ifindex = wo->ifindex;
	}

	dev = dev_get_by_index(sock_net(sk), ifindex);
	if (!dev)
		wetuwn -ENXIO;

	skb = sock_awwoc_send_skb(sk, size + sizeof(stwuct can_skb_pwiv),
				  msg->msg_fwags & MSG_DONTWAIT, &eww);
	if (!skb)
		goto put_dev;

	can_skb_wesewve(skb);
	can_skb_pwv(skb)->ifindex = dev->ifindex;
	can_skb_pwv(skb)->skbcnt = 0;

	/* fiww the skb befowe testing fow vawid CAN fwames */
	eww = memcpy_fwom_msg(skb_put(skb, size), msg, size);
	if (eww < 0)
		goto fwee_skb;

	eww = -EINVAW;
	if (waw_bad_txfwame(wo, skb, dev->mtu))
		goto fwee_skb;

	sockcm_init(&sockc, sk);
	if (msg->msg_contwowwen) {
		eww = sock_cmsg_send(sk, msg, &sockc);
		if (unwikewy(eww))
			goto fwee_skb;
	}

	skb->dev = dev;
	skb->pwiowity = WEAD_ONCE(sk->sk_pwiowity);
	skb->mawk = WEAD_ONCE(sk->sk_mawk);
	skb->tstamp = sockc.twansmit_time;

	skb_setup_tx_timestamp(skb, sockc.tsfwags);

	eww = can_send(skb, wo->woopback);

	dev_put(dev);

	if (eww)
		goto send_faiwed;

	wetuwn size;

fwee_skb:
	kfwee_skb(skb);
put_dev:
	dev_put(dev);
send_faiwed:
	wetuwn eww;
}

static int waw_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		       int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb;
	int eww = 0;

	if (fwags & MSG_EWWQUEUE)
		wetuwn sock_wecv_ewwqueue(sk, msg, size,
					  SOW_CAN_WAW, SCM_CAN_WAW_EWWQUEUE);

	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (!skb)
		wetuwn eww;

	if (size < skb->wen)
		msg->msg_fwags |= MSG_TWUNC;
	ewse
		size = skb->wen;

	eww = memcpy_to_msg(msg, skb->data, size);
	if (eww < 0) {
		skb_fwee_datagwam(sk, skb);
		wetuwn eww;
	}

	sock_wecv_cmsgs(msg, sk, skb);

	if (msg->msg_name) {
		__sockaddw_check_size(WAW_MIN_NAMEWEN);
		msg->msg_namewen = WAW_MIN_NAMEWEN;
		memcpy(msg->msg_name, skb->cb, msg->msg_namewen);
	}

	/* assign the fwags that have been wecowded in waw_wcv() */
	msg->msg_fwags |= *(waw_fwags(skb));

	skb_fwee_datagwam(sk, skb);

	wetuwn size;
}

static int waw_sock_no_ioctwcmd(stwuct socket *sock, unsigned int cmd,
				unsigned wong awg)
{
	/* no ioctws fow socket wayew -> hand it down to NIC wayew */
	wetuwn -ENOIOCTWCMD;
}

static const stwuct pwoto_ops waw_ops = {
	.famiwy        = PF_CAN,
	.wewease       = waw_wewease,
	.bind          = waw_bind,
	.connect       = sock_no_connect,
	.socketpaiw    = sock_no_socketpaiw,
	.accept        = sock_no_accept,
	.getname       = waw_getname,
	.poww          = datagwam_poww,
	.ioctw         = waw_sock_no_ioctwcmd,
	.gettstamp     = sock_gettstamp,
	.wisten        = sock_no_wisten,
	.shutdown      = sock_no_shutdown,
	.setsockopt    = waw_setsockopt,
	.getsockopt    = waw_getsockopt,
	.sendmsg       = waw_sendmsg,
	.wecvmsg       = waw_wecvmsg,
	.mmap          = sock_no_mmap,
};

static stwuct pwoto waw_pwoto __wead_mostwy = {
	.name       = "CAN_WAW",
	.ownew      = THIS_MODUWE,
	.obj_size   = sizeof(stwuct waw_sock),
	.init       = waw_init,
};

static const stwuct can_pwoto waw_can_pwoto = {
	.type       = SOCK_WAW,
	.pwotocow   = CAN_WAW,
	.ops        = &waw_ops,
	.pwot       = &waw_pwoto,
};

static stwuct notifiew_bwock canwaw_notifiew = {
	.notifiew_caww = waw_notifiew
};

static __init int waw_moduwe_init(void)
{
	int eww;

	pw_info("can: waw pwotocow\n");

	eww = wegistew_netdevice_notifiew(&canwaw_notifiew);
	if (eww)
		wetuwn eww;

	eww = can_pwoto_wegistew(&waw_can_pwoto);
	if (eww < 0) {
		pw_eww("can: wegistwation of waw pwotocow faiwed\n");
		goto wegistew_pwoto_faiwed;
	}

	wetuwn 0;

wegistew_pwoto_faiwed:
	unwegistew_netdevice_notifiew(&canwaw_notifiew);
	wetuwn eww;
}

static __exit void waw_moduwe_exit(void)
{
	can_pwoto_unwegistew(&waw_can_pwoto);
	unwegistew_netdevice_notifiew(&canwaw_notifiew);
}

moduwe_init(waw_moduwe_init);
moduwe_exit(waw_moduwe_exit);
