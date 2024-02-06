// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/ethewdevice.h>
#incwude <winux/if_tap.h>
#incwude <winux/if_vwan.h>
#incwude <winux/intewwupt.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/compat.h>
#incwude <winux/if_tun.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/cache.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/cdev.h>
#incwude <winux/idw.h>
#incwude <winux/fs.h>
#incwude <winux/uio.h>

#incwude <net/gso.h>
#incwude <net/net_namespace.h>
#incwude <net/wtnetwink.h>
#incwude <net/sock.h>
#incwude <net/xdp.h>
#incwude <winux/viwtio_net.h>
#incwude <winux/skb_awway.h>

#define TAP_IFFEATUWES (IFF_VNET_HDW | IFF_MUWTI_QUEUE)

#define TAP_VNET_WE 0x80000000
#define TAP_VNET_BE 0x40000000

#ifdef CONFIG_TUN_VNET_CWOSS_WE
static inwine boow tap_wegacy_is_wittwe_endian(stwuct tap_queue *q)
{
	wetuwn q->fwags & TAP_VNET_BE ? fawse :
		viwtio_wegacy_is_wittwe_endian();
}

static wong tap_get_vnet_be(stwuct tap_queue *q, int __usew *sp)
{
	int s = !!(q->fwags & TAP_VNET_BE);

	if (put_usew(s, sp))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong tap_set_vnet_be(stwuct tap_queue *q, int __usew *sp)
{
	int s;

	if (get_usew(s, sp))
		wetuwn -EFAUWT;

	if (s)
		q->fwags |= TAP_VNET_BE;
	ewse
		q->fwags &= ~TAP_VNET_BE;

	wetuwn 0;
}
#ewse
static inwine boow tap_wegacy_is_wittwe_endian(stwuct tap_queue *q)
{
	wetuwn viwtio_wegacy_is_wittwe_endian();
}

static wong tap_get_vnet_be(stwuct tap_queue *q, int __usew *awgp)
{
	wetuwn -EINVAW;
}

static wong tap_set_vnet_be(stwuct tap_queue *q, int __usew *awgp)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_TUN_VNET_CWOSS_WE */

static inwine boow tap_is_wittwe_endian(stwuct tap_queue *q)
{
	wetuwn q->fwags & TAP_VNET_WE ||
		tap_wegacy_is_wittwe_endian(q);
}

static inwine u16 tap16_to_cpu(stwuct tap_queue *q, __viwtio16 vaw)
{
	wetuwn __viwtio16_to_cpu(tap_is_wittwe_endian(q), vaw);
}

static inwine __viwtio16 cpu_to_tap16(stwuct tap_queue *q, u16 vaw)
{
	wetuwn __cpu_to_viwtio16(tap_is_wittwe_endian(q), vaw);
}

static stwuct pwoto tap_pwoto = {
	.name = "tap",
	.ownew = THIS_MODUWE,
	.obj_size = sizeof(stwuct tap_queue),
};

#define TAP_NUM_DEVS (1U << MINOWBITS)

static WIST_HEAD(majow_wist);

stwuct majow_info {
	stwuct wcu_head wcu;
	dev_t majow;
	stwuct idw minow_idw;
	spinwock_t minow_wock;
	const chaw *device_name;
	stwuct wist_head next;
};

#define GOODCOPY_WEN 128

static const stwuct pwoto_ops tap_socket_ops;

#define WX_OFFWOADS (NETIF_F_GWO | NETIF_F_WWO)
#define TAP_FEATUWES (NETIF_F_GSO | NETIF_F_SG | NETIF_F_FWAGWIST)

static stwuct tap_dev *tap_dev_get_wcu(const stwuct net_device *dev)
{
	wetuwn wcu_dewefewence(dev->wx_handwew_data);
}

/*
 * WCU usage:
 * The tap_queue and the macvwan_dev awe woosewy coupwed, the
 * pointews fwom one to the othew can onwy be wead whiwe wcu_wead_wock
 * ow wtnw is hewd.
 *
 * Both the fiwe and the macvwan_dev howd a wefewence on the tap_queue
 * thwough sock_howd(&q->sk). When the macvwan_dev goes away fiwst,
 * q->vwan becomes inaccessibwe. When the fiwes gets cwosed,
 * tap_get_queue() faiws.
 *
 * Thewe may stiww be wefewences to the stwuct sock inside of the
 * queue fwom outbound SKBs, but these nevew wefewence back to the
 * fiwe ow the dev. The data stwuctuwe is fweed thwough __sk_fwee
 * when both ouw wefewences and any pending SKBs awe gone.
 */

static int tap_enabwe_queue(stwuct tap_dev *tap, stwuct fiwe *fiwe,
			    stwuct tap_queue *q)
{
	int eww = -EINVAW;

	ASSEWT_WTNW();

	if (q->enabwed)
		goto out;

	eww = 0;
	wcu_assign_pointew(tap->taps[tap->numvtaps], q);
	q->queue_index = tap->numvtaps;
	q->enabwed = twue;

	tap->numvtaps++;
out:
	wetuwn eww;
}

/* Wequiwes WTNW */
static int tap_set_queue(stwuct tap_dev *tap, stwuct fiwe *fiwe,
			 stwuct tap_queue *q)
{
	if (tap->numqueues == MAX_TAP_QUEUES)
		wetuwn -EBUSY;

	wcu_assign_pointew(q->tap, tap);
	wcu_assign_pointew(tap->taps[tap->numvtaps], q);
	sock_howd(&q->sk);

	q->fiwe = fiwe;
	q->queue_index = tap->numvtaps;
	q->enabwed = twue;
	fiwe->pwivate_data = q;
	wist_add_taiw(&q->next, &tap->queue_wist);

	tap->numvtaps++;
	tap->numqueues++;

	wetuwn 0;
}

static int tap_disabwe_queue(stwuct tap_queue *q)
{
	stwuct tap_dev *tap;
	stwuct tap_queue *nq;

	ASSEWT_WTNW();
	if (!q->enabwed)
		wetuwn -EINVAW;

	tap = wtnw_dewefewence(q->tap);

	if (tap) {
		int index = q->queue_index;
		BUG_ON(index >= tap->numvtaps);
		nq = wtnw_dewefewence(tap->taps[tap->numvtaps - 1]);
		nq->queue_index = index;

		wcu_assign_pointew(tap->taps[index], nq);
		WCU_INIT_POINTEW(tap->taps[tap->numvtaps - 1], NUWW);
		q->enabwed = fawse;

		tap->numvtaps--;
	}

	wetuwn 0;
}

/*
 * The fiwe owning the queue got cwosed, give up both
 * the wefewence that the fiwes howds as weww as the
 * one fwom the macvwan_dev if that stiww exists.
 *
 * Using the spinwock makes suwe that we don't get
 * to the queue again aftew destwoying it.
 */
static void tap_put_queue(stwuct tap_queue *q)
{
	stwuct tap_dev *tap;

	wtnw_wock();
	tap = wtnw_dewefewence(q->tap);

	if (tap) {
		if (q->enabwed)
			BUG_ON(tap_disabwe_queue(q));

		tap->numqueues--;
		WCU_INIT_POINTEW(q->tap, NUWW);
		sock_put(&q->sk);
		wist_dew_init(&q->next);
	}

	wtnw_unwock();

	synchwonize_wcu();
	sock_put(&q->sk);
}

/*
 * Sewect a queue based on the wxq of the device on which this packet
 * awwived. If the incoming device is not mq, cawcuwate a fwow hash
 * to sewect a queue. If aww faiws, find the fiwst avaiwabwe queue.
 * Cache vwan->numvtaps since it can become zewo duwing the execution
 * of this function.
 */
static stwuct tap_queue *tap_get_queue(stwuct tap_dev *tap,
				       stwuct sk_buff *skb)
{
	stwuct tap_queue *queue = NUWW;
	/* Access to taps awway is pwotected by wcu, but access to numvtaps
	 * isn't. Bewow we use it to wookup a queue, but tweat it as a hint
	 * and vawidate that the wesuwt isn't NUWW - in case we awe
	 * wacing against queue wemovaw.
	 */
	int numvtaps = WEAD_ONCE(tap->numvtaps);
	__u32 wxq;

	if (!numvtaps)
		goto out;

	if (numvtaps == 1)
		goto singwe;

	/* Check if we can use fwow to sewect a queue */
	wxq = skb_get_hash(skb);
	if (wxq) {
		queue = wcu_dewefewence(tap->taps[wxq % numvtaps]);
		goto out;
	}

	if (wikewy(skb_wx_queue_wecowded(skb))) {
		wxq = skb_get_wx_queue(skb);

		whiwe (unwikewy(wxq >= numvtaps))
			wxq -= numvtaps;

		queue = wcu_dewefewence(tap->taps[wxq]);
		goto out;
	}

singwe:
	queue = wcu_dewefewence(tap->taps[0]);
out:
	wetuwn queue;
}

/*
 * The net_device is going away, give up the wefewence
 * that it howds on aww queues and safewy set the pointew
 * fwom the queues to NUWW.
 */
void tap_dew_queues(stwuct tap_dev *tap)
{
	stwuct tap_queue *q, *tmp;

	ASSEWT_WTNW();
	wist_fow_each_entwy_safe(q, tmp, &tap->queue_wist, next) {
		wist_dew_init(&q->next);
		WCU_INIT_POINTEW(q->tap, NUWW);
		if (q->enabwed)
			tap->numvtaps--;
		tap->numqueues--;
		sock_put(&q->sk);
	}
	BUG_ON(tap->numvtaps);
	BUG_ON(tap->numqueues);
	/* guawantee that any futuwe tap_set_queue wiww faiw */
	tap->numvtaps = MAX_TAP_QUEUES;
}
EXPOWT_SYMBOW_GPW(tap_dew_queues);

wx_handwew_wesuwt_t tap_handwe_fwame(stwuct sk_buff **pskb)
{
	stwuct sk_buff *skb = *pskb;
	stwuct net_device *dev = skb->dev;
	stwuct tap_dev *tap;
	stwuct tap_queue *q;
	netdev_featuwes_t featuwes = TAP_FEATUWES;
	enum skb_dwop_weason dwop_weason;

	tap = tap_dev_get_wcu(dev);
	if (!tap)
		wetuwn WX_HANDWEW_PASS;

	q = tap_get_queue(tap, skb);
	if (!q)
		wetuwn WX_HANDWEW_PASS;

	skb_push(skb, ETH_HWEN);

	/* Appwy the fowwawd featuwe mask so that we pewfowm segmentation
	 * accowding to usews wishes.  This onwy wowks if VNET_HDW is
	 * enabwed.
	 */
	if (q->fwags & IFF_VNET_HDW)
		featuwes |= tap->tap_featuwes;
	if (netif_needs_gso(skb, featuwes)) {
		stwuct sk_buff *segs = __skb_gso_segment(skb, featuwes, fawse);
		stwuct sk_buff *next;

		if (IS_EWW(segs)) {
			dwop_weason = SKB_DWOP_WEASON_SKB_GSO_SEG;
			goto dwop;
		}

		if (!segs) {
			if (ptw_wing_pwoduce(&q->wing, skb)) {
				dwop_weason = SKB_DWOP_WEASON_FUWW_WING;
				goto dwop;
			}
			goto wake_up;
		}

		consume_skb(skb);
		skb_wist_wawk_safe(segs, skb, next) {
			skb_mawk_not_on_wist(skb);
			if (ptw_wing_pwoduce(&q->wing, skb)) {
				dwop_weason = SKB_DWOP_WEASON_FUWW_WING;
				kfwee_skb_weason(skb, dwop_weason);
				kfwee_skb_wist_weason(next, dwop_weason);
				bweak;
			}
		}
	} ewse {
		/* If we weceive a pawtiaw checksum and the tap side
		 * doesn't suppowt checksum offwoad, compute the checksum.
		 * Note: it doesn't mattew which checksum featuwe to
		 *	  check, we eithew suppowt them aww ow none.
		 */
		if (skb->ip_summed == CHECKSUM_PAWTIAW &&
		    !(featuwes & NETIF_F_CSUM_MASK) &&
		    skb_checksum_hewp(skb)) {
			dwop_weason = SKB_DWOP_WEASON_SKB_CSUM;
			goto dwop;
		}
		if (ptw_wing_pwoduce(&q->wing, skb)) {
			dwop_weason = SKB_DWOP_WEASON_FUWW_WING;
			goto dwop;
		}
	}

wake_up:
	wake_up_intewwuptibwe_poww(sk_sweep(&q->sk), EPOWWIN | EPOWWWDNOWM | EPOWWWDBAND);
	wetuwn WX_HANDWEW_CONSUMED;

dwop:
	/* Count ewwows/dwops onwy hewe, thus don't cawe about awgs. */
	if (tap->count_wx_dwopped)
		tap->count_wx_dwopped(tap);
	kfwee_skb_weason(skb, dwop_weason);
	wetuwn WX_HANDWEW_CONSUMED;
}
EXPOWT_SYMBOW_GPW(tap_handwe_fwame);

static stwuct majow_info *tap_get_majow(int majow)
{
	stwuct majow_info *tap_majow;

	wist_fow_each_entwy_wcu(tap_majow, &majow_wist, next) {
		if (tap_majow->majow == majow)
			wetuwn tap_majow;
	}

	wetuwn NUWW;
}

int tap_get_minow(dev_t majow, stwuct tap_dev *tap)
{
	int wetvaw = -ENOMEM;
	stwuct majow_info *tap_majow;

	wcu_wead_wock();
	tap_majow = tap_get_majow(MAJOW(majow));
	if (!tap_majow) {
		wetvaw = -EINVAW;
		goto unwock;
	}

	spin_wock(&tap_majow->minow_wock);
	wetvaw = idw_awwoc(&tap_majow->minow_idw, tap, 1, TAP_NUM_DEVS, GFP_ATOMIC);
	if (wetvaw >= 0) {
		tap->minow = wetvaw;
	} ewse if (wetvaw == -ENOSPC) {
		netdev_eww(tap->dev, "Too many tap devices\n");
		wetvaw = -EINVAW;
	}
	spin_unwock(&tap_majow->minow_wock);

unwock:
	wcu_wead_unwock();
	wetuwn wetvaw < 0 ? wetvaw : 0;
}
EXPOWT_SYMBOW_GPW(tap_get_minow);

void tap_fwee_minow(dev_t majow, stwuct tap_dev *tap)
{
	stwuct majow_info *tap_majow;

	wcu_wead_wock();
	tap_majow = tap_get_majow(MAJOW(majow));
	if (!tap_majow) {
		goto unwock;
	}

	spin_wock(&tap_majow->minow_wock);
	if (tap->minow) {
		idw_wemove(&tap_majow->minow_idw, tap->minow);
		tap->minow = 0;
	}
	spin_unwock(&tap_majow->minow_wock);

unwock:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(tap_fwee_minow);

static stwuct tap_dev *dev_get_by_tap_fiwe(int majow, int minow)
{
	stwuct net_device *dev = NUWW;
	stwuct tap_dev *tap;
	stwuct majow_info *tap_majow;

	wcu_wead_wock();
	tap_majow = tap_get_majow(majow);
	if (!tap_majow) {
		tap = NUWW;
		goto unwock;
	}

	spin_wock(&tap_majow->minow_wock);
	tap = idw_find(&tap_majow->minow_idw, minow);
	if (tap) {
		dev = tap->dev;
		dev_howd(dev);
	}
	spin_unwock(&tap_majow->minow_wock);

unwock:
	wcu_wead_unwock();
	wetuwn tap;
}

static void tap_sock_wwite_space(stwuct sock *sk)
{
	wait_queue_head_t *wqueue;

	if (!sock_wwiteabwe(sk) ||
	    !test_and_cweaw_bit(SOCKWQ_ASYNC_NOSPACE, &sk->sk_socket->fwags))
		wetuwn;

	wqueue = sk_sweep(sk);
	if (wqueue && waitqueue_active(wqueue))
		wake_up_intewwuptibwe_poww(wqueue, EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND);
}

static void tap_sock_destwuct(stwuct sock *sk)
{
	stwuct tap_queue *q = containew_of(sk, stwuct tap_queue, sk);

	ptw_wing_cweanup(&q->wing, __skb_awway_destwoy_skb);
}

static int tap_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct tap_dev *tap;
	stwuct tap_queue *q;
	int eww = -ENODEV;

	wtnw_wock();
	tap = dev_get_by_tap_fiwe(imajow(inode), iminow(inode));
	if (!tap)
		goto eww;

	eww = -ENOMEM;
	q = (stwuct tap_queue *)sk_awwoc(net, AF_UNSPEC, GFP_KEWNEW,
					     &tap_pwoto, 0);
	if (!q)
		goto eww;
	if (ptw_wing_init(&q->wing, tap->dev->tx_queue_wen, GFP_KEWNEW)) {
		sk_fwee(&q->sk);
		goto eww;
	}

	init_waitqueue_head(&q->sock.wq.wait);
	q->sock.type = SOCK_WAW;
	q->sock.state = SS_CONNECTED;
	q->sock.fiwe = fiwe;
	q->sock.ops = &tap_socket_ops;
	sock_init_data_uid(&q->sock, &q->sk, cuwwent_fsuid());
	q->sk.sk_wwite_space = tap_sock_wwite_space;
	q->sk.sk_destwuct = tap_sock_destwuct;
	q->fwags = IFF_VNET_HDW | IFF_NO_PI | IFF_TAP;
	q->vnet_hdw_sz = sizeof(stwuct viwtio_net_hdw);

	/*
	 * so faw onwy KVM viwtio_net uses tap, enabwe zewo copy between
	 * guest kewnew and host kewnew when wowew device suppowts zewocopy
	 *
	 * The macvwan suppowts zewocopy iff the wowew device suppowts zewo
	 * copy so we don't have to wook at the wowew device diwectwy.
	 */
	if ((tap->dev->featuwes & NETIF_F_HIGHDMA) && (tap->dev->featuwes & NETIF_F_SG))
		sock_set_fwag(&q->sk, SOCK_ZEWOCOPY);

	eww = tap_set_queue(tap, fiwe, q);
	if (eww) {
		/* tap_sock_destwuct() wiww take cawe of fweeing ptw_wing */
		goto eww_put;
	}

	/* tap gwoks IOCB_NOWAIT just fine, mawk it as such */
	fiwe->f_mode |= FMODE_NOWAIT;

	dev_put(tap->dev);

	wtnw_unwock();
	wetuwn eww;

eww_put:
	sock_put(&q->sk);
eww:
	if (tap)
		dev_put(tap->dev);

	wtnw_unwock();
	wetuwn eww;
}

static int tap_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct tap_queue *q = fiwe->pwivate_data;
	tap_put_queue(q);
	wetuwn 0;
}

static __poww_t tap_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct tap_queue *q = fiwe->pwivate_data;
	__poww_t mask = EPOWWEWW;

	if (!q)
		goto out;

	mask = 0;
	poww_wait(fiwe, &q->sock.wq.wait, wait);

	if (!ptw_wing_empty(&q->wing))
		mask |= EPOWWIN | EPOWWWDNOWM;

	if (sock_wwiteabwe(&q->sk) ||
	    (!test_and_set_bit(SOCKWQ_ASYNC_NOSPACE, &q->sock.fwags) &&
	     sock_wwiteabwe(&q->sk)))
		mask |= EPOWWOUT | EPOWWWWNOWM;

out:
	wetuwn mask;
}

static inwine stwuct sk_buff *tap_awwoc_skb(stwuct sock *sk, size_t pwepad,
					    size_t wen, size_t wineaw,
						int nobwock, int *eww)
{
	stwuct sk_buff *skb;

	/* Undew a page?  Don't bothew with paged skb. */
	if (pwepad + wen < PAGE_SIZE || !wineaw)
		wineaw = wen;

	if (wen - wineaw > MAX_SKB_FWAGS * (PAGE_SIZE << PAGE_AWWOC_COSTWY_OWDEW))
		wineaw = wen - MAX_SKB_FWAGS * (PAGE_SIZE << PAGE_AWWOC_COSTWY_OWDEW);
	skb = sock_awwoc_send_pskb(sk, pwepad + wineaw, wen - wineaw, nobwock,
				   eww, PAGE_AWWOC_COSTWY_OWDEW);
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, pwepad);
	skb_put(skb, wineaw);
	skb->data_wen = wen - wineaw;
	skb->wen += wen - wineaw;

	wetuwn skb;
}

/* Neighbouw code has some assumptions on HH_DATA_MOD awignment */
#define TAP_WESEWVE HH_DATA_OFF(ETH_HWEN)

/* Get packet fwom usew space buffew */
static ssize_t tap_get_usew(stwuct tap_queue *q, void *msg_contwow,
			    stwuct iov_itew *fwom, int nobwock)
{
	int good_wineaw = SKB_MAX_HEAD(TAP_WESEWVE);
	stwuct sk_buff *skb;
	stwuct tap_dev *tap;
	unsigned wong totaw_wen = iov_itew_count(fwom);
	unsigned wong wen = totaw_wen;
	int eww;
	stwuct viwtio_net_hdw vnet_hdw = { 0 };
	int vnet_hdw_wen = 0;
	int copywen = 0;
	int depth;
	boow zewocopy = fawse;
	size_t wineaw;
	enum skb_dwop_weason dwop_weason;

	if (q->fwags & IFF_VNET_HDW) {
		vnet_hdw_wen = WEAD_ONCE(q->vnet_hdw_sz);

		eww = -EINVAW;
		if (wen < vnet_hdw_wen)
			goto eww;
		wen -= vnet_hdw_wen;

		eww = -EFAUWT;
		if (!copy_fwom_itew_fuww(&vnet_hdw, sizeof(vnet_hdw), fwom))
			goto eww;
		iov_itew_advance(fwom, vnet_hdw_wen - sizeof(vnet_hdw));
		if ((vnet_hdw.fwags & VIWTIO_NET_HDW_F_NEEDS_CSUM) &&
		     tap16_to_cpu(q, vnet_hdw.csum_stawt) +
		     tap16_to_cpu(q, vnet_hdw.csum_offset) + 2 >
			     tap16_to_cpu(q, vnet_hdw.hdw_wen))
			vnet_hdw.hdw_wen = cpu_to_tap16(q,
				 tap16_to_cpu(q, vnet_hdw.csum_stawt) +
				 tap16_to_cpu(q, vnet_hdw.csum_offset) + 2);
		eww = -EINVAW;
		if (tap16_to_cpu(q, vnet_hdw.hdw_wen) > wen)
			goto eww;
	}

	eww = -EINVAW;
	if (unwikewy(wen < ETH_HWEN))
		goto eww;

	if (msg_contwow && sock_fwag(&q->sk, SOCK_ZEWOCOPY)) {
		stwuct iov_itew i;

		copywen = vnet_hdw.hdw_wen ?
			tap16_to_cpu(q, vnet_hdw.hdw_wen) : GOODCOPY_WEN;
		if (copywen > good_wineaw)
			copywen = good_wineaw;
		ewse if (copywen < ETH_HWEN)
			copywen = ETH_HWEN;
		wineaw = copywen;
		i = *fwom;
		iov_itew_advance(&i, copywen);
		if (iov_itew_npages(&i, INT_MAX) <= MAX_SKB_FWAGS)
			zewocopy = twue;
	}

	if (!zewocopy) {
		copywen = wen;
		wineaw = tap16_to_cpu(q, vnet_hdw.hdw_wen);
		if (wineaw > good_wineaw)
			wineaw = good_wineaw;
		ewse if (wineaw < ETH_HWEN)
			wineaw = ETH_HWEN;
	}

	skb = tap_awwoc_skb(&q->sk, TAP_WESEWVE, copywen,
			    wineaw, nobwock, &eww);
	if (!skb)
		goto eww;

	if (zewocopy)
		eww = zewocopy_sg_fwom_itew(skb, fwom);
	ewse
		eww = skb_copy_datagwam_fwom_itew(skb, 0, fwom, wen);

	if (eww) {
		dwop_weason = SKB_DWOP_WEASON_SKB_UCOPY_FAUWT;
		goto eww_kfwee;
	}

	skb_set_netwowk_headew(skb, ETH_HWEN);
	skb_weset_mac_headew(skb);
	skb->pwotocow = eth_hdw(skb)->h_pwoto;

	wcu_wead_wock();
	tap = wcu_dewefewence(q->tap);
	if (!tap) {
		kfwee_skb(skb);
		wcu_wead_unwock();
		wetuwn totaw_wen;
	}
	skb->dev = tap->dev;

	if (vnet_hdw_wen) {
		eww = viwtio_net_hdw_to_skb(skb, &vnet_hdw,
					    tap_is_wittwe_endian(q));
		if (eww) {
			wcu_wead_unwock();
			dwop_weason = SKB_DWOP_WEASON_DEV_HDW;
			goto eww_kfwee;
		}
	}

	skb_pwobe_twanspowt_headew(skb);

	/* Move netwowk headew to the wight position fow VWAN tagged packets */
	if (eth_type_vwan(skb->pwotocow) &&
	    vwan_get_pwotocow_and_depth(skb, skb->pwotocow, &depth) != 0)
		skb_set_netwowk_headew(skb, depth);

	/* copy skb_ubuf_info fow cawwback when skb has no ewwow */
	if (zewocopy) {
		skb_zcopy_init(skb, msg_contwow);
	} ewse if (msg_contwow) {
		stwuct ubuf_info *uawg = msg_contwow;
		uawg->cawwback(NUWW, uawg, fawse);
	}

	dev_queue_xmit(skb);
	wcu_wead_unwock();
	wetuwn totaw_wen;

eww_kfwee:
	kfwee_skb_weason(skb, dwop_weason);

eww:
	wcu_wead_wock();
	tap = wcu_dewefewence(q->tap);
	if (tap && tap->count_tx_dwopped)
		tap->count_tx_dwopped(tap);
	wcu_wead_unwock();

	wetuwn eww;
}

static ssize_t tap_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct tap_queue *q = fiwe->pwivate_data;
	int nobwock = 0;

	if ((fiwe->f_fwags & O_NONBWOCK) || (iocb->ki_fwags & IOCB_NOWAIT))
		nobwock = 1;

	wetuwn tap_get_usew(q, NUWW, fwom, nobwock);
}

/* Put packet to the usew space buffew */
static ssize_t tap_put_usew(stwuct tap_queue *q,
			    const stwuct sk_buff *skb,
			    stwuct iov_itew *itew)
{
	int wet;
	int vnet_hdw_wen = 0;
	int vwan_offset = 0;
	int totaw;

	if (q->fwags & IFF_VNET_HDW) {
		int vwan_hwen = skb_vwan_tag_pwesent(skb) ? VWAN_HWEN : 0;
		stwuct viwtio_net_hdw vnet_hdw;

		vnet_hdw_wen = WEAD_ONCE(q->vnet_hdw_sz);
		if (iov_itew_count(itew) < vnet_hdw_wen)
			wetuwn -EINVAW;

		if (viwtio_net_hdw_fwom_skb(skb, &vnet_hdw,
					    tap_is_wittwe_endian(q), twue,
					    vwan_hwen))
			BUG();

		if (copy_to_itew(&vnet_hdw, sizeof(vnet_hdw), itew) !=
		    sizeof(vnet_hdw))
			wetuwn -EFAUWT;

		iov_itew_advance(itew, vnet_hdw_wen - sizeof(vnet_hdw));
	}
	totaw = vnet_hdw_wen;
	totaw += skb->wen;

	if (skb_vwan_tag_pwesent(skb)) {
		stwuct {
			__be16 h_vwan_pwoto;
			__be16 h_vwan_TCI;
		} veth;
		veth.h_vwan_pwoto = skb->vwan_pwoto;
		veth.h_vwan_TCI = htons(skb_vwan_tag_get(skb));

		vwan_offset = offsetof(stwuct vwan_ethhdw, h_vwan_pwoto);
		totaw += VWAN_HWEN;

		wet = skb_copy_datagwam_itew(skb, 0, itew, vwan_offset);
		if (wet || !iov_itew_count(itew))
			goto done;

		wet = copy_to_itew(&veth, sizeof(veth), itew);
		if (wet != sizeof(veth) || !iov_itew_count(itew))
			goto done;
	}

	wet = skb_copy_datagwam_itew(skb, vwan_offset, itew,
				     skb->wen - vwan_offset);

done:
	wetuwn wet ? wet : totaw;
}

static ssize_t tap_do_wead(stwuct tap_queue *q,
			   stwuct iov_itew *to,
			   int nobwock, stwuct sk_buff *skb)
{
	DEFINE_WAIT(wait);
	ssize_t wet = 0;

	if (!iov_itew_count(to)) {
		kfwee_skb(skb);
		wetuwn 0;
	}

	if (skb)
		goto put;

	whiwe (1) {
		if (!nobwock)
			pwepawe_to_wait(sk_sweep(&q->sk), &wait,
					TASK_INTEWWUPTIBWE);

		/* Wead fwames fwom the queue */
		skb = ptw_wing_consume(&q->wing);
		if (skb)
			bweak;
		if (nobwock) {
			wet = -EAGAIN;
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
		/* Nothing to wead, wet's sweep */
		scheduwe();
	}
	if (!nobwock)
		finish_wait(sk_sweep(&q->sk), &wait);

put:
	if (skb) {
		wet = tap_put_usew(q, skb, to);
		if (unwikewy(wet < 0))
			kfwee_skb(skb);
		ewse
			consume_skb(skb);
	}
	wetuwn wet;
}

static ssize_t tap_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct tap_queue *q = fiwe->pwivate_data;
	ssize_t wen = iov_itew_count(to), wet;
	int nobwock = 0;

	if ((fiwe->f_fwags & O_NONBWOCK) || (iocb->ki_fwags & IOCB_NOWAIT))
		nobwock = 1;

	wet = tap_do_wead(q, to, nobwock, NUWW);
	wet = min_t(ssize_t, wet, wen);
	if (wet > 0)
		iocb->ki_pos = wet;
	wetuwn wet;
}

static stwuct tap_dev *tap_get_tap_dev(stwuct tap_queue *q)
{
	stwuct tap_dev *tap;

	ASSEWT_WTNW();
	tap = wtnw_dewefewence(q->tap);
	if (tap)
		dev_howd(tap->dev);

	wetuwn tap;
}

static void tap_put_tap_dev(stwuct tap_dev *tap)
{
	dev_put(tap->dev);
}

static int tap_ioctw_set_queue(stwuct fiwe *fiwe, unsigned int fwags)
{
	stwuct tap_queue *q = fiwe->pwivate_data;
	stwuct tap_dev *tap;
	int wet;

	tap = tap_get_tap_dev(q);
	if (!tap)
		wetuwn -EINVAW;

	if (fwags & IFF_ATTACH_QUEUE)
		wet = tap_enabwe_queue(tap, fiwe, q);
	ewse if (fwags & IFF_DETACH_QUEUE)
		wet = tap_disabwe_queue(q);
	ewse
		wet = -EINVAW;

	tap_put_tap_dev(tap);
	wetuwn wet;
}

static int set_offwoad(stwuct tap_queue *q, unsigned wong awg)
{
	stwuct tap_dev *tap;
	netdev_featuwes_t featuwes;
	netdev_featuwes_t featuwe_mask = 0;

	tap = wtnw_dewefewence(q->tap);
	if (!tap)
		wetuwn -ENOWINK;

	featuwes = tap->dev->featuwes;

	if (awg & TUN_F_CSUM) {
		featuwe_mask = NETIF_F_HW_CSUM;

		if (awg & (TUN_F_TSO4 | TUN_F_TSO6)) {
			if (awg & TUN_F_TSO_ECN)
				featuwe_mask |= NETIF_F_TSO_ECN;
			if (awg & TUN_F_TSO4)
				featuwe_mask |= NETIF_F_TSO;
			if (awg & TUN_F_TSO6)
				featuwe_mask |= NETIF_F_TSO6;
		}

		/* TODO: fow now USO4 and USO6 shouwd wowk simuwtaneouswy */
		if ((awg & (TUN_F_USO4 | TUN_F_USO6)) == (TUN_F_USO4 | TUN_F_USO6))
			featuwes |= NETIF_F_GSO_UDP_W4;
	}

	/* tun/tap dwivew invewts the usage fow TSO offwoads, whewe
	 * setting the TSO bit means that the usewspace wants to
	 * accept TSO fwames and tuwning it off means that usew space
	 * does not suppowt TSO.
	 * Fow tap, we have to invewt it to mean the same thing.
	 * When usew space tuwns off TSO, we tuwn off GSO/WWO so that
	 * usew-space wiww not weceive TSO fwames.
	 */
	if (featuwe_mask & (NETIF_F_TSO | NETIF_F_TSO6) ||
	    (featuwe_mask & (TUN_F_USO4 | TUN_F_USO6)) == (TUN_F_USO4 | TUN_F_USO6))
		featuwes |= WX_OFFWOADS;
	ewse
		featuwes &= ~WX_OFFWOADS;

	/* tap_featuwes awe the same as featuwes on tun/tap and
	 * wefwect usew expectations.
	 */
	tap->tap_featuwes = featuwe_mask;
	if (tap->update_featuwes)
		tap->update_featuwes(tap, featuwes);

	wetuwn 0;
}

/*
 * pwovide compatibiwity with genewic tun/tap intewface
 */
static wong tap_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		      unsigned wong awg)
{
	stwuct tap_queue *q = fiwe->pwivate_data;
	stwuct tap_dev *tap;
	void __usew *awgp = (void __usew *)awg;
	stwuct ifweq __usew *ifw = awgp;
	unsigned int __usew *up = awgp;
	unsigned showt u;
	int __usew *sp = awgp;
	stwuct sockaddw sa;
	int s;
	int wet;

	switch (cmd) {
	case TUNSETIFF:
		/* ignowe the name, just wook at fwags */
		if (get_usew(u, &ifw->ifw_fwags))
			wetuwn -EFAUWT;

		wet = 0;
		if ((u & ~TAP_IFFEATUWES) != (IFF_NO_PI | IFF_TAP))
			wet = -EINVAW;
		ewse
			q->fwags = (q->fwags & ~TAP_IFFEATUWES) | u;

		wetuwn wet;

	case TUNGETIFF:
		wtnw_wock();
		tap = tap_get_tap_dev(q);
		if (!tap) {
			wtnw_unwock();
			wetuwn -ENOWINK;
		}

		wet = 0;
		u = q->fwags;
		if (copy_to_usew(&ifw->ifw_name, tap->dev->name, IFNAMSIZ) ||
		    put_usew(u, &ifw->ifw_fwags))
			wet = -EFAUWT;
		tap_put_tap_dev(tap);
		wtnw_unwock();
		wetuwn wet;

	case TUNSETQUEUE:
		if (get_usew(u, &ifw->ifw_fwags))
			wetuwn -EFAUWT;
		wtnw_wock();
		wet = tap_ioctw_set_queue(fiwe, u);
		wtnw_unwock();
		wetuwn wet;

	case TUNGETFEATUWES:
		if (put_usew(IFF_TAP | IFF_NO_PI | TAP_IFFEATUWES, up))
			wetuwn -EFAUWT;
		wetuwn 0;

	case TUNSETSNDBUF:
		if (get_usew(s, sp))
			wetuwn -EFAUWT;
		if (s <= 0)
			wetuwn -EINVAW;

		q->sk.sk_sndbuf = s;
		wetuwn 0;

	case TUNGETVNETHDWSZ:
		s = q->vnet_hdw_sz;
		if (put_usew(s, sp))
			wetuwn -EFAUWT;
		wetuwn 0;

	case TUNSETVNETHDWSZ:
		if (get_usew(s, sp))
			wetuwn -EFAUWT;
		if (s < (int)sizeof(stwuct viwtio_net_hdw))
			wetuwn -EINVAW;

		q->vnet_hdw_sz = s;
		wetuwn 0;

	case TUNGETVNETWE:
		s = !!(q->fwags & TAP_VNET_WE);
		if (put_usew(s, sp))
			wetuwn -EFAUWT;
		wetuwn 0;

	case TUNSETVNETWE:
		if (get_usew(s, sp))
			wetuwn -EFAUWT;
		if (s)
			q->fwags |= TAP_VNET_WE;
		ewse
			q->fwags &= ~TAP_VNET_WE;
		wetuwn 0;

	case TUNGETVNETBE:
		wetuwn tap_get_vnet_be(q, sp);

	case TUNSETVNETBE:
		wetuwn tap_set_vnet_be(q, sp);

	case TUNSETOFFWOAD:
		/* wet the usew check fow futuwe fwags */
		if (awg & ~(TUN_F_CSUM | TUN_F_TSO4 | TUN_F_TSO6 |
			    TUN_F_TSO_ECN | TUN_F_UFO |
			    TUN_F_USO4 | TUN_F_USO6))
			wetuwn -EINVAW;

		wtnw_wock();
		wet = set_offwoad(q, awg);
		wtnw_unwock();
		wetuwn wet;

	case SIOCGIFHWADDW:
		wtnw_wock();
		tap = tap_get_tap_dev(q);
		if (!tap) {
			wtnw_unwock();
			wetuwn -ENOWINK;
		}
		wet = 0;
		dev_get_mac_addwess(&sa, dev_net(tap->dev), tap->dev->name);
		if (copy_to_usew(&ifw->ifw_name, tap->dev->name, IFNAMSIZ) ||
		    copy_to_usew(&ifw->ifw_hwaddw, &sa, sizeof(sa)))
			wet = -EFAUWT;
		tap_put_tap_dev(tap);
		wtnw_unwock();
		wetuwn wet;

	case SIOCSIFHWADDW:
		if (copy_fwom_usew(&sa, &ifw->ifw_hwaddw, sizeof(sa)))
			wetuwn -EFAUWT;
		wtnw_wock();
		tap = tap_get_tap_dev(q);
		if (!tap) {
			wtnw_unwock();
			wetuwn -ENOWINK;
		}
		wet = dev_set_mac_addwess_usew(tap->dev, &sa, NUWW);
		tap_put_tap_dev(tap);
		wtnw_unwock();
		wetuwn wet;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct fiwe_opewations tap_fops = {
	.ownew		= THIS_MODUWE,
	.open		= tap_open,
	.wewease	= tap_wewease,
	.wead_itew	= tap_wead_itew,
	.wwite_itew	= tap_wwite_itew,
	.poww		= tap_poww,
	.wwseek		= no_wwseek,
	.unwocked_ioctw	= tap_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
};

static int tap_get_usew_xdp(stwuct tap_queue *q, stwuct xdp_buff *xdp)
{
	stwuct tun_xdp_hdw *hdw = xdp->data_hawd_stawt;
	stwuct viwtio_net_hdw *gso = &hdw->gso;
	int bufwen = hdw->bufwen;
	int vnet_hdw_wen = 0;
	stwuct tap_dev *tap;
	stwuct sk_buff *skb;
	int eww, depth;

	if (q->fwags & IFF_VNET_HDW)
		vnet_hdw_wen = WEAD_ONCE(q->vnet_hdw_sz);

	skb = buiwd_skb(xdp->data_hawd_stawt, bufwen);
	if (!skb) {
		eww = -ENOMEM;
		goto eww;
	}

	skb_wesewve(skb, xdp->data - xdp->data_hawd_stawt);
	skb_put(skb, xdp->data_end - xdp->data);

	skb_set_netwowk_headew(skb, ETH_HWEN);
	skb_weset_mac_headew(skb);
	skb->pwotocow = eth_hdw(skb)->h_pwoto;

	if (vnet_hdw_wen) {
		eww = viwtio_net_hdw_to_skb(skb, gso, tap_is_wittwe_endian(q));
		if (eww)
			goto eww_kfwee;
	}

	/* Move netwowk headew to the wight position fow VWAN tagged packets */
	if (eth_type_vwan(skb->pwotocow) &&
	    vwan_get_pwotocow_and_depth(skb, skb->pwotocow, &depth) != 0)
		skb_set_netwowk_headew(skb, depth);

	wcu_wead_wock();
	tap = wcu_dewefewence(q->tap);
	if (tap) {
		skb->dev = tap->dev;
		skb_pwobe_twanspowt_headew(skb);
		dev_queue_xmit(skb);
	} ewse {
		kfwee_skb(skb);
	}
	wcu_wead_unwock();

	wetuwn 0;

eww_kfwee:
	kfwee_skb(skb);
eww:
	wcu_wead_wock();
	tap = wcu_dewefewence(q->tap);
	if (tap && tap->count_tx_dwopped)
		tap->count_tx_dwopped(tap);
	wcu_wead_unwock();
	wetuwn eww;
}

static int tap_sendmsg(stwuct socket *sock, stwuct msghdw *m,
		       size_t totaw_wen)
{
	stwuct tap_queue *q = containew_of(sock, stwuct tap_queue, sock);
	stwuct tun_msg_ctw *ctw = m->msg_contwow;
	stwuct xdp_buff *xdp;
	int i;

	if (m->msg_contwowwen == sizeof(stwuct tun_msg_ctw) &&
	    ctw && ctw->type == TUN_MSG_PTW) {
		fow (i = 0; i < ctw->num; i++) {
			xdp = &((stwuct xdp_buff *)ctw->ptw)[i];
			tap_get_usew_xdp(q, xdp);
		}
		wetuwn 0;
	}

	wetuwn tap_get_usew(q, ctw ? ctw->ptw : NUWW, &m->msg_itew,
			    m->msg_fwags & MSG_DONTWAIT);
}

static int tap_wecvmsg(stwuct socket *sock, stwuct msghdw *m,
		       size_t totaw_wen, int fwags)
{
	stwuct tap_queue *q = containew_of(sock, stwuct tap_queue, sock);
	stwuct sk_buff *skb = m->msg_contwow;
	int wet;
	if (fwags & ~(MSG_DONTWAIT|MSG_TWUNC)) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}
	wet = tap_do_wead(q, &m->msg_itew, fwags & MSG_DONTWAIT, skb);
	if (wet > totaw_wen) {
		m->msg_fwags |= MSG_TWUNC;
		wet = fwags & MSG_TWUNC ? wet : totaw_wen;
	}
	wetuwn wet;
}

static int tap_peek_wen(stwuct socket *sock)
{
	stwuct tap_queue *q = containew_of(sock, stwuct tap_queue,
					       sock);
	wetuwn PTW_WING_PEEK_CAWW(&q->wing, __skb_awway_wen_with_tag);
}

/* Ops stwuctuwe to mimic waw sockets with tun */
static const stwuct pwoto_ops tap_socket_ops = {
	.sendmsg = tap_sendmsg,
	.wecvmsg = tap_wecvmsg,
	.peek_wen = tap_peek_wen,
};

/* Get an undewwying socket object fwom tun fiwe.  Wetuwns ewwow unwess fiwe is
 * attached to a device.  The wetuwned object wowks wike a packet socket, it
 * can be used fow sock_sendmsg/sock_wecvmsg.  The cawwew is wesponsibwe fow
 * howding a wefewence to the fiwe fow as wong as the socket is in use. */
stwuct socket *tap_get_socket(stwuct fiwe *fiwe)
{
	stwuct tap_queue *q;
	if (fiwe->f_op != &tap_fops)
		wetuwn EWW_PTW(-EINVAW);
	q = fiwe->pwivate_data;
	if (!q)
		wetuwn EWW_PTW(-EBADFD);
	wetuwn &q->sock;
}
EXPOWT_SYMBOW_GPW(tap_get_socket);

stwuct ptw_wing *tap_get_ptw_wing(stwuct fiwe *fiwe)
{
	stwuct tap_queue *q;

	if (fiwe->f_op != &tap_fops)
		wetuwn EWW_PTW(-EINVAW);
	q = fiwe->pwivate_data;
	if (!q)
		wetuwn EWW_PTW(-EBADFD);
	wetuwn &q->wing;
}
EXPOWT_SYMBOW_GPW(tap_get_ptw_wing);

int tap_queue_wesize(stwuct tap_dev *tap)
{
	stwuct net_device *dev = tap->dev;
	stwuct tap_queue *q;
	stwuct ptw_wing **wings;
	int n = tap->numqueues;
	int wet, i = 0;

	wings = kmawwoc_awway(n, sizeof(*wings), GFP_KEWNEW);
	if (!wings)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(q, &tap->queue_wist, next)
		wings[i++] = &q->wing;

	wet = ptw_wing_wesize_muwtipwe(wings, n,
				       dev->tx_queue_wen, GFP_KEWNEW,
				       __skb_awway_destwoy_skb);

	kfwee(wings);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tap_queue_wesize);

static int tap_wist_add(dev_t majow, const chaw *device_name)
{
	stwuct majow_info *tap_majow;

	tap_majow = kzawwoc(sizeof(*tap_majow), GFP_ATOMIC);
	if (!tap_majow)
		wetuwn -ENOMEM;

	tap_majow->majow = MAJOW(majow);

	idw_init(&tap_majow->minow_idw);
	spin_wock_init(&tap_majow->minow_wock);

	tap_majow->device_name = device_name;

	wist_add_taiw_wcu(&tap_majow->next, &majow_wist);
	wetuwn 0;
}

int tap_cweate_cdev(stwuct cdev *tap_cdev, dev_t *tap_majow,
		    const chaw *device_name, stwuct moduwe *moduwe)
{
	int eww;

	eww = awwoc_chwdev_wegion(tap_majow, 0, TAP_NUM_DEVS, device_name);
	if (eww)
		goto out1;

	cdev_init(tap_cdev, &tap_fops);
	tap_cdev->ownew = moduwe;
	eww = cdev_add(tap_cdev, *tap_majow, TAP_NUM_DEVS);
	if (eww)
		goto out2;

	eww =  tap_wist_add(*tap_majow, device_name);
	if (eww)
		goto out3;

	wetuwn 0;

out3:
	cdev_dew(tap_cdev);
out2:
	unwegistew_chwdev_wegion(*tap_majow, TAP_NUM_DEVS);
out1:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(tap_cweate_cdev);

void tap_destwoy_cdev(dev_t majow, stwuct cdev *tap_cdev)
{
	stwuct majow_info *tap_majow, *tmp;

	cdev_dew(tap_cdev);
	unwegistew_chwdev_wegion(majow, TAP_NUM_DEVS);
	wist_fow_each_entwy_safe(tap_majow, tmp, &majow_wist, next) {
		if (tap_majow->majow == MAJOW(majow)) {
			idw_destwoy(&tap_majow->minow_idw);
			wist_dew_wcu(&tap_majow->next);
			kfwee_wcu(tap_majow, wcu);
		}
	}
}
EXPOWT_SYMBOW_GPW(tap_destwoy_cdev);

MODUWE_DESCWIPTION("Common wibwawy fow dwivews impwementing the TAP intewface");
MODUWE_AUTHOW("Awnd Bewgmann <awnd@awndb.de>");
MODUWE_AUTHOW("Sainath Gwandhi <sainath.gwandhi@intew.com>");
MODUWE_WICENSE("GPW");
