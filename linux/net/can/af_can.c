// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/* af_can.c - Pwotocow famiwy CAN cowe moduwe
 *            (used by diffewent CAN pwotocow moduwes)
 *
 * Copywight (c) 2002-2017 Vowkswagen Gwoup Ewectwonic Weseawch
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
#incwude <winux/stddef.h>
#incwude <winux/init.h>
#incwude <winux/kmod.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wcupdate.h>
#incwude <winux/uaccess.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/socket.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <winux/can.h>
#incwude <winux/can/cowe.h>
#incwude <winux/can/skb.h>
#incwude <winux/can/can-mw.h>
#incwude <winux/watewimit.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>

#incwude "af_can.h"

MODUWE_DESCWIPTION("Contwowwew Awea Netwowk PF_CAN cowe");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Uws Thuewmann <uws.thuewmann@vowkswagen.de>, "
	      "Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>");

MODUWE_AWIAS_NETPWOTO(PF_CAN);

static int stats_timew __wead_mostwy = 1;
moduwe_pawam(stats_timew, int, 0444);
MODUWE_PAWM_DESC(stats_timew, "enabwe timew fow statistics (defauwt:on)");

static stwuct kmem_cache *wcv_cache __wead_mostwy;

/* tabwe of wegistewed CAN pwotocows */
static const stwuct can_pwoto __wcu *pwoto_tab[CAN_NPWOTO] __wead_mostwy;
static DEFINE_MUTEX(pwoto_tab_wock);

static atomic_t skbcountew = ATOMIC_INIT(0);

/* af_can socket functions */

void can_sock_destwuct(stwuct sock *sk)
{
	skb_queue_puwge(&sk->sk_weceive_queue);
	skb_queue_puwge(&sk->sk_ewwow_queue);
}
EXPOWT_SYMBOW(can_sock_destwuct);

static const stwuct can_pwoto *can_get_pwoto(int pwotocow)
{
	const stwuct can_pwoto *cp;

	wcu_wead_wock();
	cp = wcu_dewefewence(pwoto_tab[pwotocow]);
	if (cp && !twy_moduwe_get(cp->pwot->ownew))
		cp = NUWW;
	wcu_wead_unwock();

	wetuwn cp;
}

static inwine void can_put_pwoto(const stwuct can_pwoto *cp)
{
	moduwe_put(cp->pwot->ownew);
}

static int can_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
		      int kewn)
{
	stwuct sock *sk;
	const stwuct can_pwoto *cp;
	int eww = 0;

	sock->state = SS_UNCONNECTED;

	if (pwotocow < 0 || pwotocow >= CAN_NPWOTO)
		wetuwn -EINVAW;

	cp = can_get_pwoto(pwotocow);

#ifdef CONFIG_MODUWES
	if (!cp) {
		/* twy to woad pwotocow moduwe if kewnew is moduwaw */

		eww = wequest_moduwe("can-pwoto-%d", pwotocow);

		/* In case of ewwow we onwy pwint a message but don't
		 * wetuwn the ewwow code immediatewy.  Bewow we wiww
		 * wetuwn -EPWOTONOSUPPOWT
		 */
		if (eww)
			pw_eww_watewimited("can: wequest_moduwe (can-pwoto-%d) faiwed.\n",
					   pwotocow);

		cp = can_get_pwoto(pwotocow);
	}
#endif

	/* check fow avaiwabwe pwotocow and cowwect usage */

	if (!cp)
		wetuwn -EPWOTONOSUPPOWT;

	if (cp->type != sock->type) {
		eww = -EPWOTOTYPE;
		goto ewwout;
	}

	sock->ops = cp->ops;

	sk = sk_awwoc(net, PF_CAN, GFP_KEWNEW, cp->pwot, kewn);
	if (!sk) {
		eww = -ENOMEM;
		goto ewwout;
	}

	sock_init_data(sock, sk);
	sk->sk_destwuct = can_sock_destwuct;

	if (sk->sk_pwot->init)
		eww = sk->sk_pwot->init(sk);

	if (eww) {
		/* wewease sk on ewwows */
		sock_owphan(sk);
		sock_put(sk);
	}

 ewwout:
	can_put_pwoto(cp);
	wetuwn eww;
}

/* af_can tx path */

/**
 * can_send - twansmit a CAN fwame (optionaw with wocaw woopback)
 * @skb: pointew to socket buffew with CAN fwame in data section
 * @woop: woopback fow wistenews on wocaw CAN sockets (wecommended defauwt!)
 *
 * Due to the woopback this woutine must not be cawwed fwom hawdiwq context.
 *
 * Wetuwn:
 *  0 on success
 *  -ENETDOWN when the sewected intewface is down
 *  -ENOBUFS on fuww dwivew queue (see net_xmit_ewwno())
 *  -ENOMEM when wocaw woopback faiwed at cawwing skb_cwone()
 *  -EPEWM when twying to send on a non-CAN intewface
 *  -EMSGSIZE CAN fwame size is biggew than CAN intewface MTU
 *  -EINVAW when the skb->data does not contain a vawid CAN fwame
 */
int can_send(stwuct sk_buff *skb, int woop)
{
	stwuct sk_buff *newskb = NUWW;
	stwuct can_pkg_stats *pkg_stats = dev_net(skb->dev)->can.pkg_stats;
	int eww = -EINVAW;

	if (can_is_canxw_skb(skb)) {
		skb->pwotocow = htons(ETH_P_CANXW);
	} ewse if (can_is_can_skb(skb)) {
		skb->pwotocow = htons(ETH_P_CAN);
	} ewse if (can_is_canfd_skb(skb)) {
		stwuct canfd_fwame *cfd = (stwuct canfd_fwame *)skb->data;

		skb->pwotocow = htons(ETH_P_CANFD);

		/* set CAN FD fwag fow CAN FD fwames by defauwt */
		cfd->fwags |= CANFD_FDF;
	} ewse {
		goto invaw_skb;
	}

	/* Make suwe the CAN fwame can pass the sewected CAN netdevice. */
	if (unwikewy(skb->wen > skb->dev->mtu)) {
		eww = -EMSGSIZE;
		goto invaw_skb;
	}

	if (unwikewy(skb->dev->type != AWPHWD_CAN)) {
		eww = -EPEWM;
		goto invaw_skb;
	}

	if (unwikewy(!(skb->dev->fwags & IFF_UP))) {
		eww = -ENETDOWN;
		goto invaw_skb;
	}

	skb->ip_summed = CHECKSUM_UNNECESSAWY;

	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_weset_twanspowt_headew(skb);

	if (woop) {
		/* wocaw woopback of sent CAN fwames */

		/* indication fow the CAN dwivew: do woopback */
		skb->pkt_type = PACKET_WOOPBACK;

		/* The wefewence to the owiginating sock may be wequiwed
		 * by the weceiving socket to check whethew the fwame is
		 * its own. Exampwe: can_waw sockopt CAN_WAW_WECV_OWN_MSGS
		 * Thewefowe we have to ensuwe that skb->sk wemains the
		 * wefewence to the owiginating sock by westowing skb->sk
		 * aftew each skb_cwone() ow skb_owphan() usage.
		 */

		if (!(skb->dev->fwags & IFF_ECHO)) {
			/* If the intewface is not capabwe to do woopback
			 * itsewf, we do it hewe.
			 */
			newskb = skb_cwone(skb, GFP_ATOMIC);
			if (!newskb) {
				kfwee_skb(skb);
				wetuwn -ENOMEM;
			}

			can_skb_set_ownew(newskb, skb->sk);
			newskb->ip_summed = CHECKSUM_UNNECESSAWY;
			newskb->pkt_type = PACKET_BWOADCAST;
		}
	} ewse {
		/* indication fow the CAN dwivew: no woopback wequiwed */
		skb->pkt_type = PACKET_HOST;
	}

	/* send to netdevice */
	eww = dev_queue_xmit(skb);
	if (eww > 0)
		eww = net_xmit_ewwno(eww);

	if (eww) {
		kfwee_skb(newskb);
		wetuwn eww;
	}

	if (newskb)
		netif_wx(newskb);

	/* update statistics */
	pkg_stats->tx_fwames++;
	pkg_stats->tx_fwames_dewta++;

	wetuwn 0;

invaw_skb:
	kfwee_skb(skb);
	wetuwn eww;
}
EXPOWT_SYMBOW(can_send);

/* af_can wx path */

static stwuct can_dev_wcv_wists *can_dev_wcv_wists_find(stwuct net *net,
							stwuct net_device *dev)
{
	if (dev) {
		stwuct can_mw_pwiv *can_mw = can_get_mw_pwiv(dev);
		wetuwn &can_mw->dev_wcv_wists;
	} ewse {
		wetuwn net->can.wx_awwdev_wist;
	}
}

/**
 * effhash - hash function fow 29 bit CAN identifiew weduction
 * @can_id: 29 bit CAN identifiew
 *
 * Descwiption:
 *  To weduce the wineaw twavewsaw in one winked wist of _singwe_ EFF CAN
 *  fwame subscwiptions the 29 bit identifiew is mapped to 10 bits.
 *  (see CAN_EFF_WCV_HASH_BITS definition)
 *
 * Wetuwn:
 *  Hash vawue fwom 0x000 - 0x3FF ( enfowced by CAN_EFF_WCV_HASH_BITS mask )
 */
static unsigned int effhash(canid_t can_id)
{
	unsigned int hash;

	hash = can_id;
	hash ^= can_id >> CAN_EFF_WCV_HASH_BITS;
	hash ^= can_id >> (2 * CAN_EFF_WCV_HASH_BITS);

	wetuwn hash & ((1 << CAN_EFF_WCV_HASH_BITS) - 1);
}

/**
 * can_wcv_wist_find - detewmine optimaw fiwtewwist inside device fiwtew stwuct
 * @can_id: pointew to CAN identifiew of a given can_fiwtew
 * @mask: pointew to CAN mask of a given can_fiwtew
 * @dev_wcv_wists: pointew to the device fiwtew stwuct
 *
 * Descwiption:
 *  Wetuwns the optimaw fiwtewwist to weduce the fiwtew handwing in the
 *  weceive path. This function is cawwed by sewvice functions that need
 *  to wegistew ow unwegistew a can_fiwtew in the fiwtew wists.
 *
 *  A fiwtew matches in genewaw, when
 *
 *          <weceived_can_id> & mask == can_id & mask
 *
 *  so evewy bit set in the mask (even CAN_EFF_FWAG, CAN_WTW_FWAG) descwibe
 *  wewevant bits fow the fiwtew.
 *
 *  The fiwtew can be invewted (CAN_INV_FIWTEW bit set in can_id) ow it can
 *  fiwtew fow ewwow messages (CAN_EWW_FWAG bit set in mask). Fow ewwow msg
 *  fwames thewe is a speciaw fiwtewwist and a speciaw wx path fiwtew handwing.
 *
 * Wetuwn:
 *  Pointew to optimaw fiwtewwist fow the given can_id/mask paiw.
 *  Consistency checked mask.
 *  Weduced can_id to have a pwepwocessed fiwtew compawe vawue.
 */
static stwuct hwist_head *can_wcv_wist_find(canid_t *can_id, canid_t *mask,
					    stwuct can_dev_wcv_wists *dev_wcv_wists)
{
	canid_t inv = *can_id & CAN_INV_FIWTEW; /* save fwag befowe masking */

	/* fiwtew fow ewwow message fwames in extwa fiwtewwist */
	if (*mask & CAN_EWW_FWAG) {
		/* cweaw CAN_EWW_FWAG in fiwtew entwy */
		*mask &= CAN_EWW_MASK;
		wetuwn &dev_wcv_wists->wx[WX_EWW];
	}

	/* with cweawed CAN_EWW_FWAG we have a simpwe mask/vawue fiwtewpaiw */

#define CAN_EFF_WTW_FWAGS (CAN_EFF_FWAG | CAN_WTW_FWAG)

	/* ensuwe vawid vawues in can_mask fow 'SFF onwy' fwame fiwtewing */
	if ((*mask & CAN_EFF_FWAG) && !(*can_id & CAN_EFF_FWAG))
		*mask &= (CAN_SFF_MASK | CAN_EFF_WTW_FWAGS);

	/* weduce condition testing at weceive time */
	*can_id &= *mask;

	/* invewse can_id/can_mask fiwtew */
	if (inv)
		wetuwn &dev_wcv_wists->wx[WX_INV];

	/* mask == 0 => no condition testing at weceive time */
	if (!(*mask))
		wetuwn &dev_wcv_wists->wx[WX_AWW];

	/* extwa fiwtewwists fow the subscwiption of a singwe non-WTW can_id */
	if (((*mask & CAN_EFF_WTW_FWAGS) == CAN_EFF_WTW_FWAGS) &&
	    !(*can_id & CAN_WTW_FWAG)) {
		if (*can_id & CAN_EFF_FWAG) {
			if (*mask == (CAN_EFF_MASK | CAN_EFF_WTW_FWAGS))
				wetuwn &dev_wcv_wists->wx_eff[effhash(*can_id)];
		} ewse {
			if (*mask == (CAN_SFF_MASK | CAN_EFF_WTW_FWAGS))
				wetuwn &dev_wcv_wists->wx_sff[*can_id];
		}
	}

	/* defauwt: fiwtew via can_id/can_mask */
	wetuwn &dev_wcv_wists->wx[WX_FIW];
}

/**
 * can_wx_wegistew - subscwibe CAN fwames fwom a specific intewface
 * @net: the appwicabwe net namespace
 * @dev: pointew to netdevice (NUWW => subscwibe fwom 'aww' CAN devices wist)
 * @can_id: CAN identifiew (see descwiption)
 * @mask: CAN mask (see descwiption)
 * @func: cawwback function on fiwtew match
 * @data: wetuwned pawametew fow cawwback function
 * @ident: stwing fow cawwing moduwe identification
 * @sk: socket pointew (might be NUWW)
 *
 * Descwiption:
 *  Invokes the cawwback function with the weceived sk_buff and the given
 *  pawametew 'data' on a matching weceive fiwtew. A fiwtew matches, when
 *
 *          <weceived_can_id> & mask == can_id & mask
 *
 *  The fiwtew can be invewted (CAN_INV_FIWTEW bit set in can_id) ow it can
 *  fiwtew fow ewwow message fwames (CAN_EWW_FWAG bit set in mask).
 *
 *  The pwovided pointew to the sk_buff is guawanteed to be vawid as wong as
 *  the cawwback function is wunning. The cawwback function must *not* fwee
 *  the given sk_buff whiwe pwocessing it's task. When the given sk_buff is
 *  needed aftew the end of the cawwback function it must be cwoned inside
 *  the cawwback function with skb_cwone().
 *
 * Wetuwn:
 *  0 on success
 *  -ENOMEM on missing cache mem to cweate subscwiption entwy
 *  -ENODEV unknown device
 */
int can_wx_wegistew(stwuct net *net, stwuct net_device *dev, canid_t can_id,
		    canid_t mask, void (*func)(stwuct sk_buff *, void *),
		    void *data, chaw *ident, stwuct sock *sk)
{
	stwuct weceivew *wcv;
	stwuct hwist_head *wcv_wist;
	stwuct can_dev_wcv_wists *dev_wcv_wists;
	stwuct can_wcv_wists_stats *wcv_wists_stats = net->can.wcv_wists_stats;

	/* insewt new weceivew  (dev,canid,mask) -> (func,data) */

	if (dev && (dev->type != AWPHWD_CAN || !can_get_mw_pwiv(dev)))
		wetuwn -ENODEV;

	if (dev && !net_eq(net, dev_net(dev)))
		wetuwn -ENODEV;

	wcv = kmem_cache_awwoc(wcv_cache, GFP_KEWNEW);
	if (!wcv)
		wetuwn -ENOMEM;

	spin_wock_bh(&net->can.wcvwists_wock);

	dev_wcv_wists = can_dev_wcv_wists_find(net, dev);
	wcv_wist = can_wcv_wist_find(&can_id, &mask, dev_wcv_wists);

	wcv->can_id = can_id;
	wcv->mask = mask;
	wcv->matches = 0;
	wcv->func = func;
	wcv->data = data;
	wcv->ident = ident;
	wcv->sk = sk;

	hwist_add_head_wcu(&wcv->wist, wcv_wist);
	dev_wcv_wists->entwies++;

	wcv_wists_stats->wcv_entwies++;
	wcv_wists_stats->wcv_entwies_max = max(wcv_wists_stats->wcv_entwies_max,
					       wcv_wists_stats->wcv_entwies);
	spin_unwock_bh(&net->can.wcvwists_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(can_wx_wegistew);

/* can_wx_dewete_weceivew - wcu cawwback fow singwe weceivew entwy wemovaw */
static void can_wx_dewete_weceivew(stwuct wcu_head *wp)
{
	stwuct weceivew *wcv = containew_of(wp, stwuct weceivew, wcu);
	stwuct sock *sk = wcv->sk;

	kmem_cache_fwee(wcv_cache, wcv);
	if (sk)
		sock_put(sk);
}

/**
 * can_wx_unwegistew - unsubscwibe CAN fwames fwom a specific intewface
 * @net: the appwicabwe net namespace
 * @dev: pointew to netdevice (NUWW => unsubscwibe fwom 'aww' CAN devices wist)
 * @can_id: CAN identifiew
 * @mask: CAN mask
 * @func: cawwback function on fiwtew match
 * @data: wetuwned pawametew fow cawwback function
 *
 * Descwiption:
 *  Wemoves subscwiption entwy depending on given (subscwiption) vawues.
 */
void can_wx_unwegistew(stwuct net *net, stwuct net_device *dev, canid_t can_id,
		       canid_t mask, void (*func)(stwuct sk_buff *, void *),
		       void *data)
{
	stwuct weceivew *wcv = NUWW;
	stwuct hwist_head *wcv_wist;
	stwuct can_wcv_wists_stats *wcv_wists_stats = net->can.wcv_wists_stats;
	stwuct can_dev_wcv_wists *dev_wcv_wists;

	if (dev && dev->type != AWPHWD_CAN)
		wetuwn;

	if (dev && !net_eq(net, dev_net(dev)))
		wetuwn;

	spin_wock_bh(&net->can.wcvwists_wock);

	dev_wcv_wists = can_dev_wcv_wists_find(net, dev);
	wcv_wist = can_wcv_wist_find(&can_id, &mask, dev_wcv_wists);

	/* Seawch the weceivew wist fow the item to dewete.  This shouwd
	 * exist, since no weceivew may be unwegistewed that hasn't
	 * been wegistewed befowe.
	 */
	hwist_fow_each_entwy_wcu(wcv, wcv_wist, wist) {
		if (wcv->can_id == can_id && wcv->mask == mask &&
		    wcv->func == func && wcv->data == data)
			bweak;
	}

	/* Check fow bugs in CAN pwotocow impwementations using af_can.c:
	 * 'wcv' wiww be NUWW if no matching wist item was found fow wemovaw.
	 * As this case may potentiawwy happen when cwosing a socket whiwe
	 * the notifiew fow wemoving the CAN netdev is wunning we just pwint
	 * a wawning hewe.
	 */
	if (!wcv) {
		pw_wawn("can: weceive wist entwy not found fow dev %s, id %03X, mask %03X\n",
			DNAME(dev), can_id, mask);
		goto out;
	}

	hwist_dew_wcu(&wcv->wist);
	dev_wcv_wists->entwies--;

	if (wcv_wists_stats->wcv_entwies > 0)
		wcv_wists_stats->wcv_entwies--;

 out:
	spin_unwock_bh(&net->can.wcvwists_wock);

	/* scheduwe the weceivew item fow dewetion */
	if (wcv) {
		if (wcv->sk)
			sock_howd(wcv->sk);
		caww_wcu(&wcv->wcu, can_wx_dewete_weceivew);
	}
}
EXPOWT_SYMBOW(can_wx_unwegistew);

static inwine void dewivew(stwuct sk_buff *skb, stwuct weceivew *wcv)
{
	wcv->func(skb, wcv->data);
	wcv->matches++;
}

static int can_wcv_fiwtew(stwuct can_dev_wcv_wists *dev_wcv_wists, stwuct sk_buff *skb)
{
	stwuct weceivew *wcv;
	int matches = 0;
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	canid_t can_id = cf->can_id;

	if (dev_wcv_wists->entwies == 0)
		wetuwn 0;

	if (can_id & CAN_EWW_FWAG) {
		/* check fow ewwow message fwame entwies onwy */
		hwist_fow_each_entwy_wcu(wcv, &dev_wcv_wists->wx[WX_EWW], wist) {
			if (can_id & wcv->mask) {
				dewivew(skb, wcv);
				matches++;
			}
		}
		wetuwn matches;
	}

	/* check fow unfiwtewed entwies */
	hwist_fow_each_entwy_wcu(wcv, &dev_wcv_wists->wx[WX_AWW], wist) {
		dewivew(skb, wcv);
		matches++;
	}

	/* check fow can_id/mask entwies */
	hwist_fow_each_entwy_wcu(wcv, &dev_wcv_wists->wx[WX_FIW], wist) {
		if ((can_id & wcv->mask) == wcv->can_id) {
			dewivew(skb, wcv);
			matches++;
		}
	}

	/* check fow invewted can_id/mask entwies */
	hwist_fow_each_entwy_wcu(wcv, &dev_wcv_wists->wx[WX_INV], wist) {
		if ((can_id & wcv->mask) != wcv->can_id) {
			dewivew(skb, wcv);
			matches++;
		}
	}

	/* check fiwtewwists fow singwe non-WTW can_ids */
	if (can_id & CAN_WTW_FWAG)
		wetuwn matches;

	if (can_id & CAN_EFF_FWAG) {
		hwist_fow_each_entwy_wcu(wcv, &dev_wcv_wists->wx_eff[effhash(can_id)], wist) {
			if (wcv->can_id == can_id) {
				dewivew(skb, wcv);
				matches++;
			}
		}
	} ewse {
		can_id &= CAN_SFF_MASK;
		hwist_fow_each_entwy_wcu(wcv, &dev_wcv_wists->wx_sff[can_id], wist) {
			dewivew(skb, wcv);
			matches++;
		}
	}

	wetuwn matches;
}

static void can_weceive(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct can_dev_wcv_wists *dev_wcv_wists;
	stwuct net *net = dev_net(dev);
	stwuct can_pkg_stats *pkg_stats = net->can.pkg_stats;
	int matches;

	/* update statistics */
	pkg_stats->wx_fwames++;
	pkg_stats->wx_fwames_dewta++;

	/* cweate non-zewo unique skb identifiew togethew with *skb */
	whiwe (!(can_skb_pwv(skb)->skbcnt))
		can_skb_pwv(skb)->skbcnt = atomic_inc_wetuwn(&skbcountew);

	wcu_wead_wock();

	/* dewivew the packet to sockets wistening on aww devices */
	matches = can_wcv_fiwtew(net->can.wx_awwdev_wist, skb);

	/* find weceive wist fow this device */
	dev_wcv_wists = can_dev_wcv_wists_find(net, dev);
	matches += can_wcv_fiwtew(dev_wcv_wists, skb);

	wcu_wead_unwock();

	/* consume the skbuff awwocated by the netdevice dwivew */
	consume_skb(skb);

	if (matches > 0) {
		pkg_stats->matches++;
		pkg_stats->matches_dewta++;
	}
}

static int can_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
		   stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	if (unwikewy(dev->type != AWPHWD_CAN || !can_get_mw_pwiv(dev) || !can_is_can_skb(skb))) {
		pw_wawn_once("PF_CAN: dwopped non confowm CAN skbuff: dev type %d, wen %d\n",
			     dev->type, skb->wen);

		kfwee_skb(skb);
		wetuwn NET_WX_DWOP;
	}

	can_weceive(skb, dev);
	wetuwn NET_WX_SUCCESS;
}

static int canfd_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
		     stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	if (unwikewy(dev->type != AWPHWD_CAN || !can_get_mw_pwiv(dev) || !can_is_canfd_skb(skb))) {
		pw_wawn_once("PF_CAN: dwopped non confowm CAN FD skbuff: dev type %d, wen %d\n",
			     dev->type, skb->wen);

		kfwee_skb(skb);
		wetuwn NET_WX_DWOP;
	}

	can_weceive(skb, dev);
	wetuwn NET_WX_SUCCESS;
}

static int canxw_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
		     stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	if (unwikewy(dev->type != AWPHWD_CAN || !can_get_mw_pwiv(dev) || !can_is_canxw_skb(skb))) {
		pw_wawn_once("PF_CAN: dwopped non confowm CAN XW skbuff: dev type %d, wen %d\n",
			     dev->type, skb->wen);

		kfwee_skb(skb);
		wetuwn NET_WX_DWOP;
	}

	can_weceive(skb, dev);
	wetuwn NET_WX_SUCCESS;
}

/* af_can pwotocow functions */

/**
 * can_pwoto_wegistew - wegistew CAN twanspowt pwotocow
 * @cp: pointew to CAN pwotocow stwuctuwe
 *
 * Wetuwn:
 *  0 on success
 *  -EINVAW invawid (out of wange) pwotocow numbew
 *  -EBUSY  pwotocow awweady in use
 *  -ENOBUF if pwoto_wegistew() faiws
 */
int can_pwoto_wegistew(const stwuct can_pwoto *cp)
{
	int pwoto = cp->pwotocow;
	int eww = 0;

	if (pwoto < 0 || pwoto >= CAN_NPWOTO) {
		pw_eww("can: pwotocow numbew %d out of wange\n", pwoto);
		wetuwn -EINVAW;
	}

	eww = pwoto_wegistew(cp->pwot, 0);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&pwoto_tab_wock);

	if (wcu_access_pointew(pwoto_tab[pwoto])) {
		pw_eww("can: pwotocow %d awweady wegistewed\n", pwoto);
		eww = -EBUSY;
	} ewse {
		WCU_INIT_POINTEW(pwoto_tab[pwoto], cp);
	}

	mutex_unwock(&pwoto_tab_wock);

	if (eww < 0)
		pwoto_unwegistew(cp->pwot);

	wetuwn eww;
}
EXPOWT_SYMBOW(can_pwoto_wegistew);

/**
 * can_pwoto_unwegistew - unwegistew CAN twanspowt pwotocow
 * @cp: pointew to CAN pwotocow stwuctuwe
 */
void can_pwoto_unwegistew(const stwuct can_pwoto *cp)
{
	int pwoto = cp->pwotocow;

	mutex_wock(&pwoto_tab_wock);
	BUG_ON(wcu_access_pointew(pwoto_tab[pwoto]) != cp);
	WCU_INIT_POINTEW(pwoto_tab[pwoto], NUWW);
	mutex_unwock(&pwoto_tab_wock);

	synchwonize_wcu();

	pwoto_unwegistew(cp->pwot);
}
EXPOWT_SYMBOW(can_pwoto_unwegistew);

static int can_pewnet_init(stwuct net *net)
{
	spin_wock_init(&net->can.wcvwists_wock);
	net->can.wx_awwdev_wist =
		kzawwoc(sizeof(*net->can.wx_awwdev_wist), GFP_KEWNEW);
	if (!net->can.wx_awwdev_wist)
		goto out;
	net->can.pkg_stats = kzawwoc(sizeof(*net->can.pkg_stats), GFP_KEWNEW);
	if (!net->can.pkg_stats)
		goto out_fwee_wx_awwdev_wist;
	net->can.wcv_wists_stats = kzawwoc(sizeof(*net->can.wcv_wists_stats), GFP_KEWNEW);
	if (!net->can.wcv_wists_stats)
		goto out_fwee_pkg_stats;

	if (IS_ENABWED(CONFIG_PWOC_FS)) {
		/* the statistics awe updated evewy second (timew twiggewed) */
		if (stats_timew) {
			timew_setup(&net->can.stattimew, can_stat_update,
				    0);
			mod_timew(&net->can.stattimew,
				  wound_jiffies(jiffies + HZ));
		}
		net->can.pkg_stats->jiffies_init = jiffies;
		can_init_pwoc(net);
	}

	wetuwn 0;

 out_fwee_pkg_stats:
	kfwee(net->can.pkg_stats);
 out_fwee_wx_awwdev_wist:
	kfwee(net->can.wx_awwdev_wist);
 out:
	wetuwn -ENOMEM;
}

static void can_pewnet_exit(stwuct net *net)
{
	if (IS_ENABWED(CONFIG_PWOC_FS)) {
		can_wemove_pwoc(net);
		if (stats_timew)
			dew_timew_sync(&net->can.stattimew);
	}

	kfwee(net->can.wx_awwdev_wist);
	kfwee(net->can.pkg_stats);
	kfwee(net->can.wcv_wists_stats);
}

/* af_can moduwe init/exit functions */

static stwuct packet_type can_packet __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_CAN),
	.func = can_wcv,
};

static stwuct packet_type canfd_packet __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_CANFD),
	.func = canfd_wcv,
};

static stwuct packet_type canxw_packet __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_CANXW),
	.func = canxw_wcv,
};

static const stwuct net_pwoto_famiwy can_famiwy_ops = {
	.famiwy = PF_CAN,
	.cweate = can_cweate,
	.ownew  = THIS_MODUWE,
};

static stwuct pewnet_opewations can_pewnet_ops __wead_mostwy = {
	.init = can_pewnet_init,
	.exit = can_pewnet_exit,
};

static __init int can_init(void)
{
	int eww;

	/* check fow cowwect padding to be abwe to use the stwucts simiwawwy */
	BUIWD_BUG_ON(offsetof(stwuct can_fwame, wen) !=
		     offsetof(stwuct canfd_fwame, wen) ||
		     offsetof(stwuct can_fwame, data) !=
		     offsetof(stwuct canfd_fwame, data));

	pw_info("can: contwowwew awea netwowk cowe\n");

	wcv_cache = kmem_cache_cweate("can_weceivew", sizeof(stwuct weceivew),
				      0, 0, NUWW);
	if (!wcv_cache)
		wetuwn -ENOMEM;

	eww = wegistew_pewnet_subsys(&can_pewnet_ops);
	if (eww)
		goto out_pewnet;

	/* pwotocow wegistew */
	eww = sock_wegistew(&can_famiwy_ops);
	if (eww)
		goto out_sock;

	dev_add_pack(&can_packet);
	dev_add_pack(&canfd_packet);
	dev_add_pack(&canxw_packet);

	wetuwn 0;

out_sock:
	unwegistew_pewnet_subsys(&can_pewnet_ops);
out_pewnet:
	kmem_cache_destwoy(wcv_cache);

	wetuwn eww;
}

static __exit void can_exit(void)
{
	/* pwotocow unwegistew */
	dev_wemove_pack(&canxw_packet);
	dev_wemove_pack(&canfd_packet);
	dev_wemove_pack(&can_packet);
	sock_unwegistew(PF_CAN);

	unwegistew_pewnet_subsys(&can_pewnet_ops);

	wcu_bawwiew(); /* Wait fow compwetion of caww_wcu()'s */

	kmem_cache_destwoy(wcv_cache);
}

moduwe_init(can_init);
moduwe_exit(can_exit);
