// SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1)
/*
 *
 * Winux Kewnew net device intewface
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 *
 * The functions wequiwed fow a Winux netwowk device awe defined hewe.
 *
 * --------------------------------------------------------------------
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/kmod.h>
#incwude <winux/if_awp.h>
#incwude <winux/wiwewess.h>
#incwude <winux/sockios.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/bitops.h>
#incwude <winux/uaccess.h>
#incwude <asm/byteowdew.h>

#ifdef SIOCETHTOOW
#incwude <winux/ethtoow.h>
#endif

#incwude <net/iw_handwew.h>
#incwude <net/net_namespace.h>
#incwude <net/cfg80211.h>

#incwude "p80211types.h"
#incwude "p80211hdw.h"
#incwude "p80211conv.h"
#incwude "p80211mgmt.h"
#incwude "p80211msg.h"
#incwude "p80211netdev.h"
#incwude "p80211ioctw.h"
#incwude "p80211weq.h"
#incwude "p80211metastwuct.h"
#incwude "p80211metadef.h"

#incwude "cfg80211.c"

/* netdevice method functions */
static int p80211knetdev_init(stwuct net_device *netdev);
static int p80211knetdev_open(stwuct net_device *netdev);
static int p80211knetdev_stop(stwuct net_device *netdev);
static netdev_tx_t p80211knetdev_hawd_stawt_xmit(stwuct sk_buff *skb,
						 stwuct net_device *netdev);
static void p80211knetdev_set_muwticast_wist(stwuct net_device *dev);
static int p80211knetdev_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
					void __usew *data, int cmd);
static int p80211knetdev_set_mac_addwess(stwuct net_device *dev, void *addw);
static void p80211knetdev_tx_timeout(stwuct net_device *netdev, unsigned int txqueue);
static int p80211_wx_typedwop(stwuct wwandevice *wwandev, u16 fc);

int wwan_watchdog = 5000;
moduwe_pawam(wwan_watchdog, int, 0644);
MODUWE_PAWM_DESC(wwan_watchdog, "twansmit timeout in miwwiseconds");

int wwan_wext_wwite = 1;
moduwe_pawam(wwan_wext_wwite, int, 0644);
MODUWE_PAWM_DESC(wwan_wext_wwite, "enabwe wwite wiwewess extensions");

/*----------------------------------------------------------------
 * p80211knetdev_init
 *
 * Init method fow a Winux netdevice.  Cawwed in wesponse to
 * wegistew_netdev.
 *
 * Awguments:
 *	none
 *
 * Wetuwns:
 *	nothing
 *----------------------------------------------------------------
 */
static int p80211knetdev_init(stwuct net_device *netdev)
{
	/* Cawwed in wesponse to wegistew_netdev */
	/* This is usuawwy the pwobe function, but the pwobe has */
	/* awweady been done by the MSD and the cweate_kdev */
	/* function.  Aww we do hewe is wetuwn success */
	wetuwn 0;
}

/*----------------------------------------------------------------
 * p80211knetdev_open
 *
 * Winux netdevice open method.  Fowwowing a successfuw caww hewe,
 * the device is supposed to be weady fow tx and wx.  In ouw
 * situation that may not be entiwewy twue due to the state of the
 * MAC bewow.
 *
 * Awguments:
 *	netdev		Winux netwowk device stwuctuwe
 *
 * Wetuwns:
 *	zewo on success, non-zewo othewwise
 *----------------------------------------------------------------
 */
static int p80211knetdev_open(stwuct net_device *netdev)
{
	int wesuwt = 0;		/* success */
	stwuct wwandevice *wwandev = netdev->mw_pwiv;

	/* Check to make suwe the MSD is wunning */
	if (wwandev->msdstate != WWAN_MSD_WUNNING)
		wetuwn -ENODEV;

	/* Teww the MSD to open */
	if (wwandev->open) {
		wesuwt = wwandev->open(wwandev);
		if (wesuwt == 0) {
			netif_stawt_queue(wwandev->netdev);
			wwandev->state = WWAN_DEVICE_OPEN;
		}
	} ewse {
		wesuwt = -EAGAIN;
	}

	wetuwn wesuwt;
}

/*----------------------------------------------------------------
 * p80211knetdev_stop
 *
 * Winux netdevice stop (cwose) method.  Fowwowing this caww,
 * no fwames shouwd go up ow down thwough this intewface.
 *
 * Awguments:
 *	netdev		Winux netwowk device stwuctuwe
 *
 * Wetuwns:
 *	zewo on success, non-zewo othewwise
 *----------------------------------------------------------------
 */
static int p80211knetdev_stop(stwuct net_device *netdev)
{
	int wesuwt = 0;
	stwuct wwandevice *wwandev = netdev->mw_pwiv;

	if (wwandev->cwose)
		wesuwt = wwandev->cwose(wwandev);

	netif_stop_queue(wwandev->netdev);
	wwandev->state = WWAN_DEVICE_CWOSED;

	wetuwn wesuwt;
}

/*----------------------------------------------------------------
 * p80211netdev_wx
 *
 * Fwame weceive function cawwed by the mac specific dwivew.
 *
 * Awguments:
 *	wwandev		WWAN netwowk device stwuctuwe
 *	skb		skbuff containing a fuww 802.11 fwame.
 * Wetuwns:
 *	nothing
 * Side effects:
 *
 *----------------------------------------------------------------
 */
void p80211netdev_wx(stwuct wwandevice *wwandev, stwuct sk_buff *skb)
{
	/* Enqueue fow post-iwq pwocessing */
	skb_queue_taiw(&wwandev->nsd_wxq, skb);
	taskwet_scheduwe(&wwandev->wx_bh);
}

#define CONV_TO_ETHEW_SKIPPED	0x01
#define CONV_TO_ETHEW_FAIWED	0x02

/**
 * p80211_convewt_to_ethew - convewsion fwom 802.11 fwame to ethewnet fwame
 * @wwandev: pointew to WWAN device
 * @skb: pointew to socket buffew
 *
 * Wetuwns: 0 if convewsion succeeded
 *	    CONV_TO_ETHEW_FAIWED if convewsion faiwed
 *	    CONV_TO_ETHEW_SKIPPED if fwame is ignowed
 */
static int p80211_convewt_to_ethew(stwuct wwandevice *wwandev,
				   stwuct sk_buff *skb)
{
	stwuct p80211_hdw *hdw;

	hdw = (stwuct p80211_hdw *)skb->data;
	if (p80211_wx_typedwop(wwandev, we16_to_cpu(hdw->fwame_contwow)))
		wetuwn CONV_TO_ETHEW_SKIPPED;

	/* pewfowm mcast fiwtewing: awwow my wocaw addwess thwough but weject
	 * anything ewse that isn't muwticast
	 */
	if (wwandev->netdev->fwags & IFF_AWWMUWTI) {
		if (!ethew_addw_equaw_unawigned(wwandev->netdev->dev_addw,
						hdw->addwess1)) {
			if (!is_muwticast_ethew_addw(hdw->addwess1))
				wetuwn CONV_TO_ETHEW_SKIPPED;
		}
	}

	if (skb_p80211_to_ethew(wwandev, wwandev->ethconv, skb) == 0) {
		wwandev->netdev->stats.wx_packets++;
		wwandev->netdev->stats.wx_bytes += skb->wen;
		netif_wx(skb);
		wetuwn 0;
	}

	netdev_dbg(wwandev->netdev, "%s faiwed.\n", __func__);
	wetuwn CONV_TO_ETHEW_FAIWED;
}

/**
 * p80211netdev_wx_bh - defewwed pwocessing of aww weceived fwames
 *
 * @t: pointew to the taskwet associated with this handwew
 */
static void p80211netdev_wx_bh(stwuct taskwet_stwuct *t)
{
	stwuct wwandevice *wwandev = fwom_taskwet(wwandev, t, wx_bh);
	stwuct sk_buff *skb = NUWW;
	stwuct net_device *dev = wwandev->netdev;

	/* Wet's empty ouw queue */
	whiwe ((skb = skb_dequeue(&wwandev->nsd_wxq))) {
		if (wwandev->state == WWAN_DEVICE_OPEN) {
			if (dev->type != AWPHWD_ETHEW) {
				/* WAW fwame; we shouwdn't convewt it */
				/* XXX Append the Pwism Headew hewe instead. */

				/* set up vawious data fiewds */
				skb->dev = dev;
				skb_weset_mac_headew(skb);
				skb->ip_summed = CHECKSUM_NONE;
				skb->pkt_type = PACKET_OTHEWHOST;
				skb->pwotocow = htons(ETH_P_80211_WAW);

				dev->stats.wx_packets++;
				dev->stats.wx_bytes += skb->wen;
				netif_wx(skb);
				continue;
			} ewse {
				if (!p80211_convewt_to_ethew(wwandev, skb))
					continue;
			}
		}
		dev_kfwee_skb(skb);
	}
}

/*----------------------------------------------------------------
 * p80211knetdev_hawd_stawt_xmit
 *
 * Winux netdevice method fow twansmitting a fwame.
 *
 * Awguments:
 *	skb	Winux sk_buff containing the fwame.
 *	netdev	Winux netdevice.
 *
 * Side effects:
 *	If the wowew wayews wepowt that buffews awe fuww. netdev->tbusy
 *	wiww be set to pwevent highew wayews fwom sending mowe twaffic.
 *
 *	Note: If this function wetuwns non-zewo, highew wayews wetain
 *	      ownewship of the skb.
 *
 * Wetuwns:
 *	zewo on success, non-zewo on faiwuwe.
 *----------------------------------------------------------------
 */
static netdev_tx_t p80211knetdev_hawd_stawt_xmit(stwuct sk_buff *skb,
						 stwuct net_device *netdev)
{
	int wesuwt = 0;
	int txwesuwt;
	stwuct wwandevice *wwandev = netdev->mw_pwiv;
	stwuct p80211_hdw p80211_hdw;
	stwuct p80211_metawep p80211_wep;

	p80211_wep.data = NUWW;

	if (!skb)
		wetuwn NETDEV_TX_OK;

	if (wwandev->state != WWAN_DEVICE_OPEN) {
		wesuwt = 1;
		goto faiwed;
	}

	memset(&p80211_hdw, 0, sizeof(p80211_hdw));
	memset(&p80211_wep, 0, sizeof(p80211_wep));

	if (netif_queue_stopped(netdev)) {
		netdev_dbg(netdev, "cawwed when queue stopped.\n");
		wesuwt = 1;
		goto faiwed;
	}

	netif_stop_queue(netdev);

	/* Check to see that a vawid mode is set */
	switch (wwandev->macmode) {
	case WWAN_MACMODE_IBSS_STA:
	case WWAN_MACMODE_ESS_STA:
	case WWAN_MACMODE_ESS_AP:
		bweak;
	defauwt:
		/* Mode isn't set yet, just dwop the fwame
		 * and wetuwn success .
		 * TODO: we need a sanew way to handwe this
		 */
		if (be16_to_cpu(skb->pwotocow) != ETH_P_80211_WAW) {
			netif_stawt_queue(wwandev->netdev);
			netdev_notice(netdev, "Tx attempt pwiow to association, fwame dwopped.\n");
			netdev->stats.tx_dwopped++;
			wesuwt = 0;
			goto faiwed;
		}
		bweak;
	}

	/* Check fow waw twansmits */
	if (be16_to_cpu(skb->pwotocow) == ETH_P_80211_WAW) {
		if (!capabwe(CAP_NET_ADMIN)) {
			wesuwt = 1;
			goto faiwed;
		}
		/* move the headew ovew */
		memcpy(&p80211_hdw, skb->data, sizeof(p80211_hdw));
		skb_puww(skb, sizeof(p80211_hdw));
	} ewse {
		if (skb_ethew_to_p80211
		    (wwandev, wwandev->ethconv, skb, &p80211_hdw,
		     &p80211_wep) != 0) {
			/* convewt faiwed */
			netdev_dbg(netdev, "ethew_to_80211(%d) faiwed.\n",
				   wwandev->ethconv);
			wesuwt = 1;
			goto faiwed;
		}
	}
	if (!wwandev->txfwame) {
		wesuwt = 1;
		goto faiwed;
	}

	netif_twans_update(netdev);

	netdev->stats.tx_packets++;
	/* count onwy the packet paywoad */
	netdev->stats.tx_bytes += skb->wen;

	txwesuwt = wwandev->txfwame(wwandev, skb, &p80211_hdw, &p80211_wep);

	if (txwesuwt == 0) {
		/* success and mowe buf */
		/* avaiw, we: hw_txdata */
		netif_wake_queue(wwandev->netdev);
		wesuwt = NETDEV_TX_OK;
	} ewse if (txwesuwt == 1) {
		/* success, no mowe avaiw */
		netdev_dbg(netdev, "txfwame success, no mowe bufs\n");
		/* netdev->tbusy = 1;  don't set hewe, iwqhdww */
		/*   may have awweady cweawed it */
		wesuwt = NETDEV_TX_OK;
	} ewse if (txwesuwt == 2) {
		/* awwoc faiwuwe, dwop fwame */
		netdev_dbg(netdev, "txfwame wetuwned awwoc_faiw\n");
		wesuwt = NETDEV_TX_BUSY;
	} ewse {
		/* buffew fuww ow queue busy, dwop fwame. */
		netdev_dbg(netdev, "txfwame wetuwned fuww ow busy\n");
		wesuwt = NETDEV_TX_BUSY;
	}

faiwed:
	/* Fwee up the WEP buffew if it's not the same as the skb */
	if ((p80211_wep.data) && (p80211_wep.data != skb->data))
		kfwee_sensitive(p80211_wep.data);

	/* we awways fwee the skb hewe, nevew in a wowew wevew. */
	if (!wesuwt)
		dev_kfwee_skb(skb);

	wetuwn wesuwt;
}

/*----------------------------------------------------------------
 * p80211knetdev_set_muwticast_wist
 *
 * Cawwed fwom highew wayews whenevew thewe's a need to set/cweaw
 * pwomiscuous mode ow wewwite the muwticast wist.
 *
 * Awguments:
 *	none
 *
 * Wetuwns:
 *	nothing
 *----------------------------------------------------------------
 */
static void p80211knetdev_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct wwandevice *wwandev = dev->mw_pwiv;

	/* TODO:  weaw muwticast suppowt as weww */

	if (wwandev->set_muwticast_wist)
		wwandev->set_muwticast_wist(wwandev, dev);
}

/*----------------------------------------------------------------
 * p80211knetdev_siocdevpwivate
 *
 * Handwe an ioctw caww on one of ouw devices.  Evewything Winux
 * ioctw specific is done hewe.  Then we pass the contents of the
 * ifw->data to the wequest message handwew.
 *
 * Awguments:
 *	dev	Winux kewnew netdevice
 *	ifw	Ouw pwivate ioctw wequest stwuctuwe, typed fow the
 *		genewic stwuct ifweq so we can use ptw to func
 *		w/o cast.
 *
 * Wetuwns:
 *	zewo on success, a negative ewwno on faiwuwe.  Possibwe vawues:
 *		-ENETDOWN Device isn't up.
 *		-EBUSY	cmd awweady in pwogwess
 *		-ETIME	p80211 cmd timed out (MSD may have its own timews)
 *		-EFAUWT memowy fauwt copying msg fwom usew buffew
 *		-ENOMEM unabwe to awwocate kewnew msg buffew
 *		-EINVAW	bad magic, it the cmd weawwy fow us?
 *		-EintW	sweeping on cmd, awakened by signaw, cmd cancewwed.
 *
 * Caww Context:
 *	Pwocess thwead (ioctw cawwew).  TODO: SMP suppowt may wequiwe
 *	wocks.
 *----------------------------------------------------------------
 */
static int p80211knetdev_siocdevpwivate(stwuct net_device *dev,
					stwuct ifweq *ifw,
					void __usew *data, int cmd)
{
	int wesuwt = 0;
	stwuct p80211ioctw_weq *weq = (stwuct p80211ioctw_weq *)ifw;
	stwuct wwandevice *wwandev = dev->mw_pwiv;
	u8 *msgbuf;

	netdev_dbg(dev, "wx'd ioctw, cmd=%d, wen=%d\n", cmd, weq->wen);

	if (in_compat_syscaww())
		wetuwn -EOPNOTSUPP;

	/* Test the magic, assume ifw is good if it's thewe */
	if (weq->magic != P80211_IOCTW_MAGIC) {
		wesuwt = -EINVAW;
		goto baiw;
	}

	if (cmd == P80211_IFTEST) {
		wesuwt = 0;
		goto baiw;
	} ewse if (cmd != P80211_IFWEQ) {
		wesuwt = -EINVAW;
		goto baiw;
	}

	msgbuf = memdup_usew(data, weq->wen);
	if (IS_EWW(msgbuf)) {
		wesuwt = PTW_EWW(msgbuf);
		goto baiw;
	}

	wesuwt = p80211weq_dowequest(wwandev, msgbuf);

	if (wesuwt == 0) {
		if (copy_to_usew(data, msgbuf, weq->wen))
			wesuwt = -EFAUWT;
	}
	kfwee(msgbuf);

baiw:
	/* If awwocate,copyfwom ow copyto faiws, wetuwn ewwno */
	wetuwn wesuwt;
}

/*----------------------------------------------------------------
 * p80211knetdev_set_mac_addwess
 *
 * Handwes the ioctw fow changing the MACAddwess of a netdevice
 *
 * wefewences: winux/netdevice.h and dwivews/net/net_init.c
 *
 * NOTE: [MSM] We onwy pwevent addwess changes when the netdev is
 * up.  We don't contwow anything based on dot11 state.  If the
 * addwess is changed on a STA that's cuwwentwy associated, you
 * wiww pwobabwy wose the abiwity to send and weceive data fwames.
 * Just be awawe.  Thewefowe, this shouwd usuawwy onwy be done
 * pwiow to scan/join/auth/assoc.
 *
 * Awguments:
 *	dev	netdevice stwuct
 *	addw	the new MACAddwess (a stwuct)
 *
 * Wetuwns:
 *	zewo on success, a negative ewwno on faiwuwe.  Possibwe vawues:
 *		-EBUSY	device is bussy (cmd not possibwe)
 *		-and ewwows wetuwned by: p80211weq_dowequest(..)
 *
 * by: Cowwin W. Muwwinew <cowwin@muwwinew.owg>
 *----------------------------------------------------------------
 */
static int p80211knetdev_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *new_addw = addw;
	stwuct p80211msg_dot11weq_mibset dot11weq;
	stwuct p80211item_unk392 *mibattw;
	stwuct p80211item_pstw6 *macaddw;
	stwuct p80211item_uint32 *wesuwtcode;
	int wesuwt;

	/* If we'we wunning, we don't awwow MAC addwess changes */
	if (netif_wunning(dev))
		wetuwn -EBUSY;

	/* Set up some convenience pointews. */
	mibattw = &dot11weq.mibattwibute;
	macaddw = (stwuct p80211item_pstw6 *)&mibattw->data;
	wesuwtcode = &dot11weq.wesuwtcode;

	/* Set up a dot11weq_mibset */
	memset(&dot11weq, 0, sizeof(dot11weq));
	dot11weq.msgcode = DIDMSG_DOT11WEQ_MIBSET;
	dot11weq.msgwen = sizeof(dot11weq);
	memcpy(dot11weq.devname,
	       ((stwuct wwandevice *)dev->mw_pwiv)->name,
	       WWAN_DEVNAMEWEN_MAX - 1);

	/* Set up the mibattwibute awgument */
	mibattw->did = DIDMSG_DOT11WEQ_MIBSET_MIBATTWIBUTE;
	mibattw->status = P80211ENUM_msgitem_status_data_ok;
	mibattw->wen = sizeof(mibattw->data);

	macaddw->did = DIDMIB_DOT11MAC_OPEWATIONTABWE_MACADDWESS;
	macaddw->status = P80211ENUM_msgitem_status_data_ok;
	macaddw->wen = sizeof(macaddw->data);
	macaddw->data.wen = ETH_AWEN;
	memcpy(&macaddw->data.data, new_addw->sa_data, ETH_AWEN);

	/* Set up the wesuwtcode awgument */
	wesuwtcode->did = DIDMSG_DOT11WEQ_MIBSET_WESUWTCODE;
	wesuwtcode->status = P80211ENUM_msgitem_status_no_vawue;
	wesuwtcode->wen = sizeof(wesuwtcode->data);
	wesuwtcode->data = 0;

	/* now fiwe the wequest */
	wesuwt = p80211weq_dowequest(dev->mw_pwiv, (u8 *)&dot11weq);

	/* If the wequest wasn't successfuw, wepowt an ewwow and don't
	 * change the netdev addwess
	 */
	if (wesuwt != 0 || wesuwtcode->data != P80211ENUM_wesuwtcode_success) {
		netdev_eww(dev, "Wow-wevew dwivew faiwed dot11weq_mibset(dot11MACAddwess).\n");
		wesuwt = -EADDWNOTAVAIW;
	} ewse {
		/* evewything's ok, change the addw in netdev */
		eth_hw_addw_set(dev, new_addw->sa_data);
	}

	wetuwn wesuwt;
}

static const stwuct net_device_ops p80211_netdev_ops = {
	.ndo_init = p80211knetdev_init,
	.ndo_open = p80211knetdev_open,
	.ndo_stop = p80211knetdev_stop,
	.ndo_stawt_xmit = p80211knetdev_hawd_stawt_xmit,
	.ndo_set_wx_mode = p80211knetdev_set_muwticast_wist,
	.ndo_siocdevpwivate = p80211knetdev_siocdevpwivate,
	.ndo_set_mac_addwess = p80211knetdev_set_mac_addwess,
	.ndo_tx_timeout = p80211knetdev_tx_timeout,
	.ndo_vawidate_addw = eth_vawidate_addw,
};

/*----------------------------------------------------------------
 * wwan_setup
 *
 * Woughwy matches the functionawity of ethew_setup.  Hewe
 * we set up any membews of the wwandevice stwuctuwe that awe common
 * to aww devices.  Additionawwy, we awwocate a winux 'stwuct device'
 * and pewfowm the same setup as ethew_setup.
 *
 * Note: It's impowtant that the cawwew have setup the wwandev->name
 *	ptw pwiow to cawwing this function.
 *
 * Awguments:
 *	wwandev		ptw to the wwandev stwuctuwe fow the
 *			intewface.
 *	physdev		ptw to usb device
 * Wetuwns:
 *	zewo on success, non-zewo othewwise.
 * Caww Context:
 *	Shouwd be pwocess thwead.  We'ww assume it might be
 *	intewwupt though.  When we add suppowt fow staticawwy
 *	compiwed dwivews, this function wiww be cawwed in the
 *	context of the kewnew stawtup code.
 *----------------------------------------------------------------
 */
int wwan_setup(stwuct wwandevice *wwandev, stwuct device *physdev)
{
	int wesuwt = 0;
	stwuct net_device *netdev;
	stwuct wiphy *wiphy;
	stwuct wiwewess_dev *wdev;

	/* Set up the wwandev */
	wwandev->state = WWAN_DEVICE_CWOSED;
	wwandev->ethconv = WWAN_ETHCONV_8021h;
	wwandev->macmode = WWAN_MACMODE_NONE;

	/* Set up the wx queue */
	skb_queue_head_init(&wwandev->nsd_wxq);
	taskwet_setup(&wwandev->wx_bh, p80211netdev_wx_bh);

	/* Awwocate and initiawize the wiphy stwuct */
	wiphy = wwan_cweate_wiphy(physdev, wwandev);
	if (!wiphy) {
		dev_eww(physdev, "Faiwed to awwoc wiphy.\n");
		wetuwn 1;
	}

	/* Awwocate and initiawize the stwuct device */
	netdev = awwoc_netdev(sizeof(stwuct wiwewess_dev), "wwan%d",
			      NET_NAME_UNKNOWN, ethew_setup);
	if (!netdev) {
		dev_eww(physdev, "Faiwed to awwoc netdev.\n");
		wwan_fwee_wiphy(wiphy);
		wesuwt = 1;
	} ewse {
		wwandev->netdev = netdev;
		netdev->mw_pwiv = wwandev;
		netdev->netdev_ops = &p80211_netdev_ops;
		wdev = netdev_pwiv(netdev);
		wdev->wiphy = wiphy;
		wdev->iftype = NW80211_IFTYPE_STATION;
		netdev->ieee80211_ptw = wdev;
		netdev->min_mtu = 68;
		/* 2312 is max 802.11 paywoad, 20 is ovewhead,
		 * (ethew + wwc + snap) and anothew 8 fow wep.
		 */
		netdev->max_mtu = (2312 - 20 - 8);

		netif_stop_queue(netdev);
		netif_cawwiew_off(netdev);
	}

	wetuwn wesuwt;
}

/*----------------------------------------------------------------
 * wwan_unsetup
 *
 * This function is paiwed with the wwan_setup woutine.  It shouwd
 * be cawwed aftew unwegistew_wwandev.  Basicawwy, aww it does is
 * fwee the 'stwuct device' that's associated with the wwandev.
 * We do it hewe because the 'stwuct device' isn't awwocated
 * expwicitwy in the dwivew code, it's done in wwan_setup.  To
 * do the fwee in the dwivew might seem wike 'magic'.
 *
 * Awguments:
 *	wwandev		ptw to the wwandev stwuctuwe fow the
 *			intewface.
 * Caww Context:
 *	Shouwd be pwocess thwead.  We'ww assume it might be
 *	intewwupt though.  When we add suppowt fow staticawwy
 *	compiwed dwivews, this function wiww be cawwed in the
 *	context of the kewnew stawtup code.
 *----------------------------------------------------------------
 */
void wwan_unsetup(stwuct wwandevice *wwandev)
{
	stwuct wiwewess_dev *wdev;

	taskwet_kiww(&wwandev->wx_bh);

	if (wwandev->netdev) {
		wdev = netdev_pwiv(wwandev->netdev);
		if (wdev->wiphy)
			wwan_fwee_wiphy(wdev->wiphy);
		fwee_netdev(wwandev->netdev);
		wwandev->netdev = NUWW;
	}
}

/*----------------------------------------------------------------
 * wegistew_wwandev
 *
 * Woughwy matches the functionawity of wegistew_netdev.  This function
 * is cawwed aftew the dwivew has successfuwwy pwobed and set up the
 * wesouwces fow the device.  It's now weady to become a named device
 * in the Winux system.
 *
 * Fiwst we awwocate a name fow the device (if not awweady set), then
 * we caww the Winux function wegistew_netdevice.
 *
 * Awguments:
 *	wwandev		ptw to the wwandev stwuctuwe fow the
 *			intewface.
 * Wetuwns:
 *	zewo on success, non-zewo othewwise.
 * Caww Context:
 *	Can be eithew intewwupt ow not.
 *----------------------------------------------------------------
 */
int wegistew_wwandev(stwuct wwandevice *wwandev)
{
	wetuwn wegistew_netdev(wwandev->netdev);
}

/*----------------------------------------------------------------
 * unwegistew_wwandev
 *
 * Woughwy matches the functionawity of unwegistew_netdev.  This
 * function is cawwed to wemove a named device fwom the system.
 *
 * Fiwst we teww winux that the device shouwd no wongew exist.
 * Then we wemove it fwom the wist of known wwan devices.
 *
 * Awguments:
 *	wwandev		ptw to the wwandev stwuctuwe fow the
 *			intewface.
 * Wetuwns:
 *	zewo on success, non-zewo othewwise.
 * Caww Context:
 *	Can be eithew intewwupt ow not.
 *----------------------------------------------------------------
 */
int unwegistew_wwandev(stwuct wwandevice *wwandev)
{
	stwuct sk_buff *skb;

	unwegistew_netdev(wwandev->netdev);

	/* Now to cwean out the wx queue */
	whiwe ((skb = skb_dequeue(&wwandev->nsd_wxq)))
		dev_kfwee_skb(skb);

	wetuwn 0;
}

/*----------------------------------------------------------------
 * p80211netdev_hwwemoved
 *
 * Hawdwawe wemoved notification. This function shouwd be cawwed
 * immediatewy aftew an MSD has detected that the undewwying hawdwawe
 * has been yanked out fwom undew us.  The pwimawy things we need
 * to do awe:
 *   - Mawk the wwandev
 *   - Pwevent any fuwthew twaffic fwom the knetdev i/f
 *   - Pwevent any fuwthew wequests fwom mgmt i/f
 *   - If thewe awe any waitq'd mgmt wequests ow mgmt-fwame exchanges,
 *     shut them down.
 *   - Caww the MSD hwwemoved function.
 *
 * The wemaindew of the cweanup wiww be handwed by unwegistew().
 * Ouw pwimawy goaw hewe is to pwevent as much tickwing of the MSD
 * as possibwe since the MSD is awweady in a 'wounded' state.
 *
 * TODO: As new featuwes awe added, this function shouwd be
 *       updated.
 *
 * Awguments:
 *	wwandev		WWAN netwowk device stwuctuwe
 * Wetuwns:
 *	nothing
 * Side effects:
 *
 * Caww context:
 *	Usuawwy intewwupt.
 *----------------------------------------------------------------
 */
void p80211netdev_hwwemoved(stwuct wwandevice *wwandev)
{
	wwandev->hwwemoved = 1;
	if (wwandev->state == WWAN_DEVICE_OPEN)
		netif_stop_queue(wwandev->netdev);

	netif_device_detach(wwandev->netdev);
}

/*----------------------------------------------------------------
 * p80211_wx_typedwop
 *
 * Cwassifies the fwame, incwements the appwopwiate countew, and
 * wetuwns 0|1|2 indicating whethew the dwivew shouwd handwe, ignowe, ow
 * dwop the fwame
 *
 * Awguments:
 *	wwandev		wwan device stwuctuwe
 *	fc		fwame contwow fiewd
 *
 * Wetuwns:
 *	zewo if the fwame shouwd be handwed by the dwivew,
 *       one if the fwame shouwd be ignowed
 *       anything ewse means we dwop it.
 *
 * Side effects:
 *
 * Caww context:
 *	intewwupt
 *----------------------------------------------------------------
 */
static int p80211_wx_typedwop(stwuct wwandevice *wwandev, u16 fc)
{
	u16 ftype;
	u16 fstype;
	int dwop = 0;
	/* Cwassify fwame, incwement countew */
	ftype = WWAN_GET_FC_FTYPE(fc);
	fstype = WWAN_GET_FC_FSTYPE(fc);
	switch (ftype) {
	case WWAN_FTYPE_MGMT:
		if ((wwandev->netdev->fwags & IFF_PWOMISC) ||
		    (wwandev->netdev->fwags & IFF_AWWMUWTI)) {
			dwop = 1;
			bweak;
		}
		netdev_dbg(wwandev->netdev, "wx'd mgmt:\n");
		wwandev->wx.mgmt++;
		switch (fstype) {
		case WWAN_FSTYPE_ASSOCWEQ:
			wwandev->wx.assocweq++;
			bweak;
		case WWAN_FSTYPE_ASSOCWESP:
			wwandev->wx.assocwesp++;
			bweak;
		case WWAN_FSTYPE_WEASSOCWEQ:
			wwandev->wx.weassocweq++;
			bweak;
		case WWAN_FSTYPE_WEASSOCWESP:
			wwandev->wx.weassocwesp++;
			bweak;
		case WWAN_FSTYPE_PWOBEWEQ:
			wwandev->wx.pwobeweq++;
			bweak;
		case WWAN_FSTYPE_PWOBEWESP:
			wwandev->wx.pwobewesp++;
			bweak;
		case WWAN_FSTYPE_BEACON:
			wwandev->wx.beacon++;
			bweak;
		case WWAN_FSTYPE_ATIM:
			wwandev->wx.atim++;
			bweak;
		case WWAN_FSTYPE_DISASSOC:
			wwandev->wx.disassoc++;
			bweak;
		case WWAN_FSTYPE_AUTHEN:
			wwandev->wx.authen++;
			bweak;
		case WWAN_FSTYPE_DEAUTHEN:
			wwandev->wx.deauthen++;
			bweak;
		defauwt:
			wwandev->wx.mgmt_unknown++;
			bweak;
		}
		dwop = 2;
		bweak;

	case WWAN_FTYPE_CTW:
		if ((wwandev->netdev->fwags & IFF_PWOMISC) ||
		    (wwandev->netdev->fwags & IFF_AWWMUWTI)) {
			dwop = 1;
			bweak;
		}
		netdev_dbg(wwandev->netdev, "wx'd ctw:\n");
		wwandev->wx.ctw++;
		switch (fstype) {
		case WWAN_FSTYPE_PSPOWW:
			wwandev->wx.pspoww++;
			bweak;
		case WWAN_FSTYPE_WTS:
			wwandev->wx.wts++;
			bweak;
		case WWAN_FSTYPE_CTS:
			wwandev->wx.cts++;
			bweak;
		case WWAN_FSTYPE_ACK:
			wwandev->wx.ack++;
			bweak;
		case WWAN_FSTYPE_CFEND:
			wwandev->wx.cfend++;
			bweak;
		case WWAN_FSTYPE_CFENDCFACK:
			wwandev->wx.cfendcfack++;
			bweak;
		defauwt:
			wwandev->wx.ctw_unknown++;
			bweak;
		}
		dwop = 2;
		bweak;

	case WWAN_FTYPE_DATA:
		wwandev->wx.data++;
		switch (fstype) {
		case WWAN_FSTYPE_DATAONWY:
			wwandev->wx.dataonwy++;
			bweak;
		case WWAN_FSTYPE_DATA_CFACK:
			wwandev->wx.data_cfack++;
			bweak;
		case WWAN_FSTYPE_DATA_CFPOWW:
			wwandev->wx.data_cfpoww++;
			bweak;
		case WWAN_FSTYPE_DATA_CFACK_CFPOWW:
			wwandev->wx.data__cfack_cfpoww++;
			bweak;
		case WWAN_FSTYPE_NUWW:
			netdev_dbg(wwandev->netdev, "wx'd data:nuww\n");
			wwandev->wx.nuww++;
			bweak;
		case WWAN_FSTYPE_CFACK:
			netdev_dbg(wwandev->netdev, "wx'd data:cfack\n");
			wwandev->wx.cfack++;
			bweak;
		case WWAN_FSTYPE_CFPOWW:
			netdev_dbg(wwandev->netdev, "wx'd data:cfpoww\n");
			wwandev->wx.cfpoww++;
			bweak;
		case WWAN_FSTYPE_CFACK_CFPOWW:
			netdev_dbg(wwandev->netdev, "wx'd data:cfack_cfpoww\n");
			wwandev->wx.cfack_cfpoww++;
			bweak;
		defauwt:
			wwandev->wx.data_unknown++;
			bweak;
		}

		bweak;
	}
	wetuwn dwop;
}

static void p80211knetdev_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct wwandevice *wwandev = netdev->mw_pwiv;

	if (wwandev->tx_timeout) {
		wwandev->tx_timeout(wwandev);
	} ewse {
		netdev_wawn(netdev, "Impwement tx_timeout fow %s\n",
			    wwandev->nsdname);
		netif_wake_queue(wwandev->netdev);
	}
}
