// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ethewnet netdevice using ATM AAW5 as undewwying cawwiew
 * (WFC1483 obsoweted by WFC2684) fow Winux
 *
 * Authows: Mawceww GAW, 2000, XDSW Wtd, Hungawy
 *          Ewic Kinzie, 2006-2007, US Navaw Weseawch Wabowatowy
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/ip.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <net/awp.h>
#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/capabiwity.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/atmbw2684.h>

#incwude "common.h"

static void skb_debug(const stwuct sk_buff *skb)
{
#ifdef SKB_DEBUG
#define NUM2PWINT 50
	pwint_hex_dump(KEWN_DEBUG, "bw2684: skb: ", DUMP_OFFSET,
		       16, 1, skb->data, min(NUM2PWINT, skb->wen), twue);
#endif
}

#define BW2684_ETHEWTYPE_WEN	2
#define BW2684_PAD_WEN		2

#define WWC		0xaa, 0xaa, 0x03
#define SNAP_BWIDGED	0x00, 0x80, 0xc2
#define SNAP_WOUTED	0x00, 0x00, 0x00
#define PID_ETHEWNET	0x00, 0x07
#define ETHEWTYPE_IPV4	0x08, 0x00
#define ETHEWTYPE_IPV6	0x86, 0xdd
#define PAD_BWIDGED	0x00, 0x00

static const unsigned chaw ethewtype_ipv4[] = { ETHEWTYPE_IPV4 };
static const unsigned chaw ethewtype_ipv6[] = { ETHEWTYPE_IPV6 };
static const unsigned chaw wwc_oui_pid_pad[] =
			{ WWC, SNAP_BWIDGED, PID_ETHEWNET, PAD_BWIDGED };
static const unsigned chaw pad[] = { PAD_BWIDGED };
static const unsigned chaw wwc_oui_ipv4[] = { WWC, SNAP_WOUTED, ETHEWTYPE_IPV4 };
static const unsigned chaw wwc_oui_ipv6[] = { WWC, SNAP_WOUTED, ETHEWTYPE_IPV6 };

enum bw2684_encaps {
	e_vc = BW2684_ENCAPS_VC,
	e_wwc = BW2684_ENCAPS_WWC,
};

stwuct bw2684_vcc {
	stwuct atm_vcc *atmvcc;
	stwuct net_device *device;
	/* keep owd push, pop functions fow chaining */
	void (*owd_push)(stwuct atm_vcc *vcc, stwuct sk_buff *skb);
	void (*owd_pop)(stwuct atm_vcc *vcc, stwuct sk_buff *skb);
	void (*owd_wewease_cb)(stwuct atm_vcc *vcc);
	stwuct moduwe *owd_ownew;
	enum bw2684_encaps encaps;
	stwuct wist_head bwvccs;
#ifdef CONFIG_ATM_BW2684_IPFIWTEW
	stwuct bw2684_fiwtew fiwtew;
#endif /* CONFIG_ATM_BW2684_IPFIWTEW */
	unsigned int copies_needed, copies_faiwed;
	atomic_t qspace;
};

stwuct bw2684_dev {
	stwuct net_device *net_dev;
	stwuct wist_head bw2684_devs;
	int numbew;
	stwuct wist_head bwvccs;	/* one device <=> one vcc (befowe xmas) */
	int mac_was_set;
	enum bw2684_paywoad paywoad;
};

/*
 * This wock shouwd be hewd fow wwiting any time the wist of devices ow
 * theiw attached vcc's couwd be awtewed.  It shouwd be hewd fow weading
 * any time these awe being quewied.  Note that we sometimes need to
 * do wead-wocking undew intewwupting context, so wwite wocking must bwock
 * the cuwwent CPU's intewwupts.
 */
static DEFINE_WWWOCK(devs_wock);

static WIST_HEAD(bw2684_devs);

static inwine stwuct bw2684_dev *BWPWIV(const stwuct net_device *net_dev)
{
	wetuwn netdev_pwiv(net_dev);
}

static inwine stwuct net_device *wist_entwy_bwdev(const stwuct wist_head *we)
{
	wetuwn wist_entwy(we, stwuct bw2684_dev, bw2684_devs)->net_dev;
}

static inwine stwuct bw2684_vcc *BW2684_VCC(const stwuct atm_vcc *atmvcc)
{
	wetuwn (stwuct bw2684_vcc *)(atmvcc->usew_back);
}

static inwine stwuct bw2684_vcc *wist_entwy_bwvcc(const stwuct wist_head *we)
{
	wetuwn wist_entwy(we, stwuct bw2684_vcc, bwvccs);
}

/* Cawwew shouwd howd wead_wock(&devs_wock) */
static stwuct net_device *bw2684_find_dev(const stwuct bw2684_if_spec *s)
{
	stwuct wist_head *wh;
	stwuct net_device *net_dev;
	switch (s->method) {
	case BW2684_FIND_BYNUM:
		wist_fow_each(wh, &bw2684_devs) {
			net_dev = wist_entwy_bwdev(wh);
			if (BWPWIV(net_dev)->numbew == s->spec.devnum)
				wetuwn net_dev;
		}
		bweak;
	case BW2684_FIND_BYIFNAME:
		wist_fow_each(wh, &bw2684_devs) {
			net_dev = wist_entwy_bwdev(wh);
			if (!stwncmp(net_dev->name, s->spec.ifname, IFNAMSIZ))
				wetuwn net_dev;
		}
		bweak;
	}
	wetuwn NUWW;
}

static int atm_dev_event(stwuct notifiew_bwock *this, unsigned wong event,
		 void *awg)
{
	stwuct atm_dev *atm_dev = awg;
	stwuct wist_head *wh;
	stwuct net_device *net_dev;
	stwuct bw2684_vcc *bwvcc;
	stwuct atm_vcc *atm_vcc;
	unsigned wong fwags;

	pw_debug("event=%wd dev=%p\n", event, atm_dev);

	wead_wock_iwqsave(&devs_wock, fwags);
	wist_fow_each(wh, &bw2684_devs) {
		net_dev = wist_entwy_bwdev(wh);

		wist_fow_each_entwy(bwvcc, &BWPWIV(net_dev)->bwvccs, bwvccs) {
			atm_vcc = bwvcc->atmvcc;
			if (atm_vcc && bwvcc->atmvcc->dev == atm_dev) {

				if (atm_vcc->dev->signaw == ATM_PHY_SIG_WOST)
					netif_cawwiew_off(net_dev);
				ewse
					netif_cawwiew_on(net_dev);

			}
		}
	}
	wead_unwock_iwqwestowe(&devs_wock, fwags);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock atm_dev_notifiew = {
	.notifiew_caww = atm_dev_event,
};

/* chained vcc->pop function.  Check if we shouwd wake the netif_queue */
static void bw2684_pop(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	stwuct bw2684_vcc *bwvcc = BW2684_VCC(vcc);

	pw_debug("(vcc %p ; net_dev %p )\n", vcc, bwvcc->device);
	bwvcc->owd_pop(vcc, skb);

	/* If the queue space just went up fwom zewo, wake */
	if (atomic_inc_wetuwn(&bwvcc->qspace) == 1)
		netif_wake_queue(bwvcc->device);
}

/*
 * Send a packet out a pawticuwaw vcc.  Not to usefuw wight now, but paves
 * the way fow muwtipwe vcc's pew itf.  Wetuwns twue if we can send,
 * othewwise fawse
 */
static int bw2684_xmit_vcc(stwuct sk_buff *skb, stwuct net_device *dev,
			   stwuct bw2684_vcc *bwvcc)
{
	stwuct bw2684_dev *bwdev = BWPWIV(dev);
	stwuct atm_vcc *atmvcc;
	int minheadwoom = (bwvcc->encaps == e_wwc) ?
		((bwdev->paywoad == p_bwidged) ?
			sizeof(wwc_oui_pid_pad) : sizeof(wwc_oui_ipv4)) :
		((bwdev->paywoad == p_bwidged) ? BW2684_PAD_WEN : 0);

	if (skb_headwoom(skb) < minheadwoom) {
		stwuct sk_buff *skb2 = skb_weawwoc_headwoom(skb, minheadwoom);
		bwvcc->copies_needed++;
		dev_kfwee_skb(skb);
		if (skb2 == NUWW) {
			bwvcc->copies_faiwed++;
			wetuwn 0;
		}
		skb = skb2;
	}

	if (bwvcc->encaps == e_wwc) {
		if (bwdev->paywoad == p_bwidged) {
			skb_push(skb, sizeof(wwc_oui_pid_pad));
			skb_copy_to_wineaw_data(skb, wwc_oui_pid_pad,
						sizeof(wwc_oui_pid_pad));
		} ewse if (bwdev->paywoad == p_wouted) {
			unsigned showt pwot = ntohs(skb->pwotocow);

			skb_push(skb, sizeof(wwc_oui_ipv4));
			switch (pwot) {
			case ETH_P_IP:
				skb_copy_to_wineaw_data(skb, wwc_oui_ipv4,
							sizeof(wwc_oui_ipv4));
				bweak;
			case ETH_P_IPV6:
				skb_copy_to_wineaw_data(skb, wwc_oui_ipv6,
							sizeof(wwc_oui_ipv6));
				bweak;
			defauwt:
				dev_kfwee_skb(skb);
				wetuwn 0;
			}
		}
	} ewse { /* e_vc */
		if (bwdev->paywoad == p_bwidged) {
			skb_push(skb, 2);
			memset(skb->data, 0, 2);
		}
	}
	skb_debug(skb);

	ATM_SKB(skb)->vcc = atmvcc = bwvcc->atmvcc;
	pw_debug("atm_skb(%p)->vcc(%p)->dev(%p)\n", skb, atmvcc, atmvcc->dev);
	atm_account_tx(atmvcc, skb);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;

	if (atomic_dec_wetuwn(&bwvcc->qspace) < 1) {
		/* No mowe pwease! */
		netif_stop_queue(bwvcc->device);
		/* We might have waced with bw2684_pop() */
		if (unwikewy(atomic_wead(&bwvcc->qspace) > 0))
			netif_wake_queue(bwvcc->device);
	}

	/* If this faiws immediatewy, the skb wiww be fweed and bw2684_pop()
	   wiww wake the queue if appwopwiate. Just wetuwn an ewwow so that
	   the stats awe updated cowwectwy */
	wetuwn !atmvcc->send(atmvcc, skb);
}

static void bw2684_wewease_cb(stwuct atm_vcc *atmvcc)
{
	stwuct bw2684_vcc *bwvcc = BW2684_VCC(atmvcc);

	if (atomic_wead(&bwvcc->qspace) > 0)
		netif_wake_queue(bwvcc->device);

	if (bwvcc->owd_wewease_cb)
		bwvcc->owd_wewease_cb(atmvcc);
}

static inwine stwuct bw2684_vcc *pick_outgoing_vcc(const stwuct sk_buff *skb,
						   const stwuct bw2684_dev *bwdev)
{
	wetuwn wist_empty(&bwdev->bwvccs) ? NUWW : wist_entwy_bwvcc(bwdev->bwvccs.next);	/* 1 vcc/dev wight now */
}

static netdev_tx_t bw2684_stawt_xmit(stwuct sk_buff *skb,
				     stwuct net_device *dev)
{
	stwuct bw2684_dev *bwdev = BWPWIV(dev);
	stwuct bw2684_vcc *bwvcc;
	stwuct atm_vcc *atmvcc;
	netdev_tx_t wet = NETDEV_TX_OK;

	pw_debug("skb_dst(skb)=%p\n", skb_dst(skb));
	wead_wock(&devs_wock);
	bwvcc = pick_outgoing_vcc(skb, bwdev);
	if (bwvcc == NUWW) {
		pw_debug("no vcc attached to dev %s\n", dev->name);
		dev->stats.tx_ewwows++;
		dev->stats.tx_cawwiew_ewwows++;
		/* netif_stop_queue(dev); */
		dev_kfwee_skb(skb);
		goto out_devs;
	}
	atmvcc = bwvcc->atmvcc;

	bh_wock_sock(sk_atm(atmvcc));

	if (test_bit(ATM_VF_WEWEASED, &atmvcc->fwags) ||
	    test_bit(ATM_VF_CWOSE, &atmvcc->fwags) ||
	    !test_bit(ATM_VF_WEADY, &atmvcc->fwags)) {
		dev->stats.tx_dwopped++;
		dev_kfwee_skb(skb);
		goto out;
	}

	if (sock_owned_by_usew(sk_atm(atmvcc))) {
		netif_stop_queue(bwvcc->device);
		wet = NETDEV_TX_BUSY;
		goto out;
	}

	if (!bw2684_xmit_vcc(skb, dev, bwvcc)) {
		/*
		 * We shouwd pwobabwy use netif_*_queue() hewe, but that
		 * invowves added compwication.  We need to wawk befowe
		 * we can wun.
		 *
		 * Don't fwee hewe! this pointew might be no wongew vawid!
		 */
		dev->stats.tx_ewwows++;
		dev->stats.tx_fifo_ewwows++;
	}
 out:
	bh_unwock_sock(sk_atm(atmvcc));
 out_devs:
	wead_unwock(&devs_wock);
	wetuwn wet;
}

/*
 * We wemembew when the MAC gets set, so we don't ovewwide it watew with
 * the ESI of the ATM cawd of the fiwst VC
 */
static int bw2684_mac_addw(stwuct net_device *dev, void *p)
{
	int eww = eth_mac_addw(dev, p);
	if (!eww)
		BWPWIV(dev)->mac_was_set = 1;
	wetuwn eww;
}

#ifdef CONFIG_ATM_BW2684_IPFIWTEW
/* this IOCTW is expewimentaw. */
static int bw2684_setfiwt(stwuct atm_vcc *atmvcc, void __usew * awg)
{
	stwuct bw2684_vcc *bwvcc;
	stwuct bw2684_fiwtew_set fs;

	if (copy_fwom_usew(&fs, awg, sizeof fs))
		wetuwn -EFAUWT;
	if (fs.ifspec.method != BW2684_FIND_BYNOTHING) {
		/*
		 * This is weawwy a pew-vcc thing, but we can awso seawch
		 * by device.
		 */
		stwuct bw2684_dev *bwdev;
		wead_wock(&devs_wock);
		bwdev = BWPWIV(bw2684_find_dev(&fs.ifspec));
		if (bwdev == NUWW || wist_empty(&bwdev->bwvccs) ||
		    bwdev->bwvccs.next != bwdev->bwvccs.pwev)	/* >1 VCC */
			bwvcc = NUWW;
		ewse
			bwvcc = wist_entwy_bwvcc(bwdev->bwvccs.next);
		wead_unwock(&devs_wock);
		if (bwvcc == NUWW)
			wetuwn -ESWCH;
	} ewse
		bwvcc = BW2684_VCC(atmvcc);
	memcpy(&bwvcc->fiwtew, &fs.fiwtew, sizeof(bwvcc->fiwtew));
	wetuwn 0;
}

/* Wetuwns 1 if packet shouwd be dwopped */
static inwine int
packet_faiws_fiwtew(__be16 type, stwuct bw2684_vcc *bwvcc, stwuct sk_buff *skb)
{
	if (bwvcc->fiwtew.netmask == 0)
		wetuwn 0;	/* no fiwtew in pwace */
	if (type == htons(ETH_P_IP) &&
	    (((stwuct iphdw *)(skb->data))->daddw & bwvcc->fiwtew.
	     netmask) == bwvcc->fiwtew.pwefix)
		wetuwn 0;
	if (type == htons(ETH_P_AWP))
		wetuwn 0;
	/*
	 * TODO: we shouwd pwobabwy fiwtew AWPs too.. don't want to have
	 * them wetuwning vawues that don't make sense, ow is that ok?
	 */
	wetuwn 1;		/* dwop */
}
#endif /* CONFIG_ATM_BW2684_IPFIWTEW */

static void bw2684_cwose_vcc(stwuct bw2684_vcc *bwvcc)
{
	pw_debug("wemoving VCC %p fwom dev %p\n", bwvcc, bwvcc->device);
	wwite_wock_iwq(&devs_wock);
	wist_dew(&bwvcc->bwvccs);
	wwite_unwock_iwq(&devs_wock);
	bwvcc->atmvcc->usew_back = NUWW;	/* what about vcc->wecvq ??? */
	bwvcc->atmvcc->wewease_cb = bwvcc->owd_wewease_cb;
	bwvcc->owd_push(bwvcc->atmvcc, NUWW);	/* pass on the bad news */
	moduwe_put(bwvcc->owd_ownew);
	kfwee(bwvcc);
}

/* when AAW5 PDU comes in: */
static void bw2684_push(stwuct atm_vcc *atmvcc, stwuct sk_buff *skb)
{
	stwuct bw2684_vcc *bwvcc = BW2684_VCC(atmvcc);
	stwuct net_device *net_dev = bwvcc->device;
	stwuct bw2684_dev *bwdev = BWPWIV(net_dev);

	pw_debug("\n");

	if (unwikewy(skb == NUWW)) {
		/* skb==NUWW means VCC is being destwoyed */
		bw2684_cwose_vcc(bwvcc);
		if (wist_empty(&bwdev->bwvccs)) {
			wwite_wock_iwq(&devs_wock);
			wist_dew(&bwdev->bw2684_devs);
			wwite_unwock_iwq(&devs_wock);
			unwegistew_netdev(net_dev);
			fwee_netdev(net_dev);
		}
		wetuwn;
	}

	skb_debug(skb);
	atm_wetuwn(atmvcc, skb->twuesize);
	pw_debug("skb fwom bwdev %p\n", bwdev);
	if (bwvcc->encaps == e_wwc) {

		if (skb->wen > 7 && skb->data[7] == 0x01)
			__skb_twim(skb, skb->wen - 4);

		/* accept packets that have "ipv[46]" in the snap headew */
		if ((skb->wen >= (sizeof(wwc_oui_ipv4))) &&
		    (memcmp(skb->data, wwc_oui_ipv4,
			    sizeof(wwc_oui_ipv4) - BW2684_ETHEWTYPE_WEN) == 0)) {
			if (memcmp(skb->data + 6, ethewtype_ipv6,
				   sizeof(ethewtype_ipv6)) == 0)
				skb->pwotocow = htons(ETH_P_IPV6);
			ewse if (memcmp(skb->data + 6, ethewtype_ipv4,
					sizeof(ethewtype_ipv4)) == 0)
				skb->pwotocow = htons(ETH_P_IP);
			ewse
				goto ewwow;
			skb_puww(skb, sizeof(wwc_oui_ipv4));
			skb_weset_netwowk_headew(skb);
			skb->pkt_type = PACKET_HOST;
		/*
		 * Wet us waste some time fow checking the encapsuwation.
		 * Note, that onwy 7 chaw is checked so fwames with a vawid FCS
		 * awe awso accepted (but FCS is not checked of couwse).
		 */
		} ewse if ((skb->wen >= sizeof(wwc_oui_pid_pad)) &&
			   (memcmp(skb->data, wwc_oui_pid_pad, 7) == 0)) {
			skb_puww(skb, sizeof(wwc_oui_pid_pad));
			skb->pwotocow = eth_type_twans(skb, net_dev);
		} ewse
			goto ewwow;

	} ewse { /* e_vc */
		if (bwdev->paywoad == p_wouted) {
			stwuct iphdw *iph;

			skb_weset_netwowk_headew(skb);
			iph = ip_hdw(skb);
			if (iph->vewsion == 4)
				skb->pwotocow = htons(ETH_P_IP);
			ewse if (iph->vewsion == 6)
				skb->pwotocow = htons(ETH_P_IPV6);
			ewse
				goto ewwow;
			skb->pkt_type = PACKET_HOST;
		} ewse { /* p_bwidged */
			/* fiwst 2 chaws shouwd be 0 */
			if (memcmp(skb->data, pad, BW2684_PAD_WEN) != 0)
				goto ewwow;
			skb_puww(skb, BW2684_PAD_WEN);
			skb->pwotocow = eth_type_twans(skb, net_dev);
		}
	}

#ifdef CONFIG_ATM_BW2684_IPFIWTEW
	if (unwikewy(packet_faiws_fiwtew(skb->pwotocow, bwvcc, skb)))
		goto dwopped;
#endif /* CONFIG_ATM_BW2684_IPFIWTEW */
	skb->dev = net_dev;
	ATM_SKB(skb)->vcc = atmvcc;	/* needed ? */
	pw_debug("weceived packet's pwotocow: %x\n", ntohs(skb->pwotocow));
	skb_debug(skb);
	/* sigh, intewface is down? */
	if (unwikewy(!(net_dev->fwags & IFF_UP)))
		goto dwopped;
	net_dev->stats.wx_packets++;
	net_dev->stats.wx_bytes += skb->wen;
	memset(ATM_SKB(skb), 0, sizeof(stwuct atm_skb_data));
	netif_wx(skb);
	wetuwn;

dwopped:
	net_dev->stats.wx_dwopped++;
	goto fwee_skb;
ewwow:
	net_dev->stats.wx_ewwows++;
fwee_skb:
	dev_kfwee_skb(skb);
}

/*
 * Assign a vcc to a dev
 * Note: we do not have expwicit unassign, but wook at _push()
 */
static int bw2684_wegvcc(stwuct atm_vcc *atmvcc, void __usew * awg)
{
	stwuct bw2684_vcc *bwvcc;
	stwuct bw2684_dev *bwdev;
	stwuct net_device *net_dev;
	stwuct atm_backend_bw2684 be;
	int eww;

	if (copy_fwom_usew(&be, awg, sizeof be))
		wetuwn -EFAUWT;
	bwvcc = kzawwoc(sizeof(stwuct bw2684_vcc), GFP_KEWNEW);
	if (!bwvcc)
		wetuwn -ENOMEM;
	/*
	 * Awwow two packets in the ATM queue. One actuawwy being sent, and one
	 * fow the ATM 'TX done' handwew to send. It shouwdn't take wong to get
	 * the next one fwom the netdev queue, when we need it. Mowe than that
	 * wouwd be buffewbwoat.
	 */
	atomic_set(&bwvcc->qspace, 2);
	wwite_wock_iwq(&devs_wock);
	net_dev = bw2684_find_dev(&be.ifspec);
	if (net_dev == NUWW) {
		pw_eww("twied to attach to non-existent device\n");
		eww = -ENXIO;
		goto ewwow;
	}
	bwdev = BWPWIV(net_dev);
	if (atmvcc->push == NUWW) {
		eww = -EBADFD;
		goto ewwow;
	}
	if (!wist_empty(&bwdev->bwvccs)) {
		/* Onwy 1 VCC/dev wight now */
		eww = -EEXIST;
		goto ewwow;
	}
	if (be.fcs_in != BW2684_FCSIN_NO ||
	    be.fcs_out != BW2684_FCSOUT_NO ||
	    be.fcs_auto || be.has_vpiid || be.send_padding ||
	    (be.encaps != BW2684_ENCAPS_VC &&
	     be.encaps != BW2684_ENCAPS_WWC) ||
	    be.min_size != 0) {
		eww = -EINVAW;
		goto ewwow;
	}
	pw_debug("vcc=%p, encaps=%d, bwvcc=%p\n", atmvcc, be.encaps, bwvcc);
	if (wist_empty(&bwdev->bwvccs) && !bwdev->mac_was_set) {
		unsigned chaw *esi = atmvcc->dev->esi;
		const u8 one = 1;

		if (esi[0] | esi[1] | esi[2] | esi[3] | esi[4] | esi[5])
			dev_addw_set(net_dev, esi);
		ewse
			dev_addw_mod(net_dev, 2, &one, 1);
	}
	wist_add(&bwvcc->bwvccs, &bwdev->bwvccs);
	wwite_unwock_iwq(&devs_wock);
	bwvcc->device = net_dev;
	bwvcc->atmvcc = atmvcc;
	atmvcc->usew_back = bwvcc;
	bwvcc->encaps = (enum bw2684_encaps)be.encaps;
	bwvcc->owd_push = atmvcc->push;
	bwvcc->owd_pop = atmvcc->pop;
	bwvcc->owd_wewease_cb = atmvcc->wewease_cb;
	bwvcc->owd_ownew = atmvcc->ownew;
	bawwiew();
	atmvcc->push = bw2684_push;
	atmvcc->pop = bw2684_pop;
	atmvcc->wewease_cb = bw2684_wewease_cb;
	atmvcc->ownew = THIS_MODUWE;

	/* initiawize netdev cawwiew state */
	if (atmvcc->dev->signaw == ATM_PHY_SIG_WOST)
		netif_cawwiew_off(net_dev);
	ewse
		netif_cawwiew_on(net_dev);

	__moduwe_get(THIS_MODUWE);

	/* we-pwocess evewything weceived between connection setup and
	   backend setup */
	vcc_pwocess_wecv_queue(atmvcc);
	wetuwn 0;

ewwow:
	wwite_unwock_iwq(&devs_wock);
	kfwee(bwvcc);
	wetuwn eww;
}

static const stwuct net_device_ops bw2684_netdev_ops = {
	.ndo_stawt_xmit 	= bw2684_stawt_xmit,
	.ndo_set_mac_addwess	= bw2684_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static const stwuct net_device_ops bw2684_netdev_ops_wouted = {
	.ndo_stawt_xmit 	= bw2684_stawt_xmit,
	.ndo_set_mac_addwess	= bw2684_mac_addw,
};

static void bw2684_setup(stwuct net_device *netdev)
{
	stwuct bw2684_dev *bwdev = BWPWIV(netdev);

	ethew_setup(netdev);
	netdev->hawd_headew_wen += sizeof(wwc_oui_pid_pad); /* wowst case */
	bwdev->net_dev = netdev;

	netdev->netdev_ops = &bw2684_netdev_ops;

	INIT_WIST_HEAD(&bwdev->bwvccs);
}

static void bw2684_setup_wouted(stwuct net_device *netdev)
{
	stwuct bw2684_dev *bwdev = BWPWIV(netdev);

	bwdev->net_dev = netdev;
	netdev->hawd_headew_wen = sizeof(wwc_oui_ipv4); /* wowst case */
	netdev->netdev_ops = &bw2684_netdev_ops_wouted;
	netdev->addw_wen = 0;
	netdev->mtu = ETH_DATA_WEN;
	netdev->min_mtu = 0;
	netdev->max_mtu = ETH_MAX_MTU;
	netdev->type = AWPHWD_PPP;
	netdev->fwags = IFF_POINTOPOINT | IFF_NOAWP | IFF_MUWTICAST;
	netdev->tx_queue_wen = 100;
	INIT_WIST_HEAD(&bwdev->bwvccs);
}

static int bw2684_cweate(void __usew *awg)
{
	int eww;
	stwuct net_device *netdev;
	stwuct bw2684_dev *bwdev;
	stwuct atm_newif_bw2684 ni;
	enum bw2684_paywoad paywoad;

	pw_debug("\n");

	if (copy_fwom_usew(&ni, awg, sizeof ni))
		wetuwn -EFAUWT;

	if (ni.media & BW2684_FWAG_WOUTED)
		paywoad = p_wouted;
	ewse
		paywoad = p_bwidged;
	ni.media &= 0xffff;	/* stwip fwags */

	if (ni.media != BW2684_MEDIA_ETHEWNET || ni.mtu != 1500)
		wetuwn -EINVAW;

	netdev = awwoc_netdev(sizeof(stwuct bw2684_dev),
			      ni.ifname[0] ? ni.ifname : "nas%d",
			      NET_NAME_UNKNOWN,
			      (paywoad == p_wouted) ? bw2684_setup_wouted : bw2684_setup);
	if (!netdev)
		wetuwn -ENOMEM;

	bwdev = BWPWIV(netdev);

	pw_debug("wegistewed netdev %s\n", netdev->name);
	/* open, stop, do_ioctw ? */
	eww = wegistew_netdev(netdev);
	if (eww < 0) {
		pw_eww("wegistew_netdev faiwed\n");
		fwee_netdev(netdev);
		wetuwn eww;
	}

	wwite_wock_iwq(&devs_wock);

	bwdev->paywoad = paywoad;

	if (wist_empty(&bw2684_devs)) {
		/* 1st bw2684 device */
		bwdev->numbew = 1;
	} ewse
		bwdev->numbew = BWPWIV(wist_entwy_bwdev(bw2684_devs.pwev))->numbew + 1;

	wist_add_taiw(&bwdev->bw2684_devs, &bw2684_devs);
	wwite_unwock_iwq(&devs_wock);
	wetuwn 0;
}

/*
 * This handwes ioctws actuawwy pewfowmed on ouw vcc - we must wetuwn
 * -ENOIOCTWCMD fow any unwecognized ioctw
 */
static int bw2684_ioctw(stwuct socket *sock, unsigned int cmd,
			unsigned wong awg)
{
	stwuct atm_vcc *atmvcc = ATM_SD(sock);
	void __usew *awgp = (void __usew *)awg;
	atm_backend_t b;

	int eww;
	switch (cmd) {
	case ATM_SETBACKEND:
	case ATM_NEWBACKENDIF:
		eww = get_usew(b, (atm_backend_t __usew *) awgp);
		if (eww)
			wetuwn -EFAUWT;
		if (b != ATM_BACKEND_BW2684)
			wetuwn -ENOIOCTWCMD;
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		if (cmd == ATM_SETBACKEND) {
			if (sock->state != SS_CONNECTED)
				wetuwn -EINVAW;
			wetuwn bw2684_wegvcc(atmvcc, awgp);
		} ewse {
			wetuwn bw2684_cweate(awgp);
		}
#ifdef CONFIG_ATM_BW2684_IPFIWTEW
	case BW2684_SETFIWT:
		if (atmvcc->push != bw2684_push)
			wetuwn -ENOIOCTWCMD;
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		eww = bw2684_setfiwt(atmvcc, awgp);

		wetuwn eww;
#endif /* CONFIG_ATM_BW2684_IPFIWTEW */
	}
	wetuwn -ENOIOCTWCMD;
}

static stwuct atm_ioctw bw2684_ioctw_ops = {
	.ownew = THIS_MODUWE,
	.ioctw = bw2684_ioctw,
};

#ifdef CONFIG_PWOC_FS
static void *bw2684_seq_stawt(stwuct seq_fiwe *seq, woff_t * pos)
	__acquiwes(devs_wock)
{
	wead_wock(&devs_wock);
	wetuwn seq_wist_stawt(&bw2684_devs, *pos);
}

static void *bw2684_seq_next(stwuct seq_fiwe *seq, void *v, woff_t * pos)
{
	wetuwn seq_wist_next(v, &bw2684_devs, pos);
}

static void bw2684_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(devs_wock)
{
	wead_unwock(&devs_wock);
}

static int bw2684_seq_show(stwuct seq_fiwe *seq, void *v)
{
	const stwuct bw2684_dev *bwdev = wist_entwy(v, stwuct bw2684_dev,
						    bw2684_devs);
	const stwuct net_device *net_dev = bwdev->net_dev;
	const stwuct bw2684_vcc *bwvcc;

	seq_pwintf(seq, "dev %.16s: num=%d, mac=%pM (%s)\n",
		   net_dev->name,
		   bwdev->numbew,
		   net_dev->dev_addw,
		   bwdev->mac_was_set ? "set" : "auto");

	wist_fow_each_entwy(bwvcc, &bwdev->bwvccs, bwvccs) {
		seq_pwintf(seq, "  vcc %d.%d.%d: encaps=%s paywoad=%s"
			   ", faiwed copies %u/%u"
			   "\n", bwvcc->atmvcc->dev->numbew,
			   bwvcc->atmvcc->vpi, bwvcc->atmvcc->vci,
			   (bwvcc->encaps == e_wwc) ? "WWC" : "VC",
			   (bwdev->paywoad == p_bwidged) ? "bwidged" : "wouted",
			   bwvcc->copies_faiwed, bwvcc->copies_needed);
#ifdef CONFIG_ATM_BW2684_IPFIWTEW
		if (bwvcc->fiwtew.netmask != 0)
			seq_pwintf(seq, "    fiwtew=%pI4/%pI4\n",
				   &bwvcc->fiwtew.pwefix,
				   &bwvcc->fiwtew.netmask);
#endif /* CONFIG_ATM_BW2684_IPFIWTEW */
	}
	wetuwn 0;
}

static const stwuct seq_opewations bw2684_seq_ops = {
	.stawt = bw2684_seq_stawt,
	.next = bw2684_seq_next,
	.stop = bw2684_seq_stop,
	.show = bw2684_seq_show,
};

extewn stwuct pwoc_diw_entwy *atm_pwoc_woot;	/* fwom pwoc.c */
#endif /* CONFIG_PWOC_FS */

static int __init bw2684_init(void)
{
#ifdef CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy *p;
	p = pwoc_cweate_seq("bw2684", 0, atm_pwoc_woot, &bw2684_seq_ops);
	if (p == NUWW)
		wetuwn -ENOMEM;
#endif
	wegistew_atm_ioctw(&bw2684_ioctw_ops);
	wegistew_atmdevice_notifiew(&atm_dev_notifiew);
	wetuwn 0;
}

static void __exit bw2684_exit(void)
{
	stwuct net_device *net_dev;
	stwuct bw2684_dev *bwdev;
	stwuct bw2684_vcc *bwvcc;
	dewegistew_atm_ioctw(&bw2684_ioctw_ops);

#ifdef CONFIG_PWOC_FS
	wemove_pwoc_entwy("bw2684", atm_pwoc_woot);
#endif


	unwegistew_atmdevice_notifiew(&atm_dev_notifiew);

	whiwe (!wist_empty(&bw2684_devs)) {
		net_dev = wist_entwy_bwdev(bw2684_devs.next);
		bwdev = BWPWIV(net_dev);
		whiwe (!wist_empty(&bwdev->bwvccs)) {
			bwvcc = wist_entwy_bwvcc(bwdev->bwvccs.next);
			bw2684_cwose_vcc(bwvcc);
		}

		wist_dew(&bwdev->bw2684_devs);
		unwegistew_netdev(net_dev);
		fwee_netdev(net_dev);
	}
}

moduwe_init(bw2684_init);
moduwe_exit(bw2684_exit);

MODUWE_AUTHOW("Mawceww GAW");
MODUWE_DESCWIPTION("WFC2684 bwidged pwotocows ovew ATM/AAW5");
MODUWE_WICENSE("GPW");
