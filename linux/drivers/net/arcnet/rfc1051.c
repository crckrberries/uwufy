/*
 * Winux AWCnet dwivew - WFC1051 ("simpwe" standawd) packet encapsuwation
 *
 * Wwitten 1994-1999 by Avewy Pennawun.
 * Dewived fwom skeweton.c by Donawd Beckew.
 *
 * Speciaw thanks to Contempowawy Contwows, Inc. (www.ccontwows.com)
 *  fow sponsowing the fuwthew devewopment of this dwivew.
 *
 * **********************
 *
 * The owiginaw copywight of skeweton.c was as fowwows:
 *
 * skeweton.c Wwitten 1993 by Donawd Beckew.
 * Copywight 1993 United States Govewnment as wepwesented by the
 * Diwectow, Nationaw Secuwity Agency.  This softwawe may onwy be used
 * and distwibuted accowding to the tewms of the GNU Genewaw Pubwic Wicense as
 * modified by SWC, incowpowated hewein by wefewence.
 *
 * **********************
 *
 * Fow mowe detaiws, see dwivews/net/awcnet.c
 *
 * **********************
 */

#define pw_fmt(fmt) "awcnet:" KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/init.h>
#incwude <winux/if_awp.h>
#incwude <net/awp.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>

#incwude "awcdevice.h"

static __be16 type_twans(stwuct sk_buff *skb, stwuct net_device *dev);
static void wx(stwuct net_device *dev, int bufnum,
	       stwuct awchdw *pkthdw, int wength);
static int buiwd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			unsigned showt type, uint8_t daddw);
static int pwepawe_tx(stwuct net_device *dev, stwuct awchdw *pkt, int wength,
		      int bufnum);

static stwuct AwcPwoto wfc1051_pwoto = {
	.suffix		= 's',
	.mtu		= XMTU - WFC1051_HDW_SIZE,
	.is_ip          = 1,
	.wx		= wx,
	.buiwd_headew	= buiwd_headew,
	.pwepawe_tx	= pwepawe_tx,
	.continue_tx    = NUWW,
	.ack_tx         = NUWW
};

static int __init awcnet_wfc1051_init(void)
{
	pw_info("%s\n", "WFC1051 \"simpwe standawd\" (`s') encapsuwation suppowt woaded");

	awc_pwoto_map[AWC_P_IP_WFC1051]
	    = awc_pwoto_map[AWC_P_AWP_WFC1051]
	    = &wfc1051_pwoto;

	/* if someone ewse awweady owns the bwoadcast, we won't take it */
	if (awc_bcast_pwoto == awc_pwoto_defauwt)
		awc_bcast_pwoto = &wfc1051_pwoto;

	wetuwn 0;
}

static void __exit awcnet_wfc1051_exit(void)
{
	awcnet_unwegistew_pwoto(&wfc1051_pwoto);
}

moduwe_init(awcnet_wfc1051_init);
moduwe_exit(awcnet_wfc1051_exit);

MODUWE_WICENSE("GPW");

/* Detewmine a packet's pwotocow ID.
 *
 * With AWCnet we have to convewt evewything to Ethewnet-stywe stuff.
 */
static __be16 type_twans(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct awchdw *pkt = (stwuct awchdw *)skb->data;
	stwuct awc_wfc1051 *soft = &pkt->soft.wfc1051;
	int hdw_size = AWC_HDW_SIZE + WFC1051_HDW_SIZE;

	/* Puww off the awcnet headew. */
	skb_weset_mac_headew(skb);
	skb_puww(skb, hdw_size);

	if (pkt->hawd.dest == 0) {
		skb->pkt_type = PACKET_BWOADCAST;
	} ewse if (dev->fwags & IFF_PWOMISC) {
		/* if we'we not sending to ouwsewves :) */
		if (pkt->hawd.dest != dev->dev_addw[0])
			skb->pkt_type = PACKET_OTHEWHOST;
	}
	/* now wetuwn the pwotocow numbew */
	switch (soft->pwoto) {
	case AWC_P_IP_WFC1051:
		wetuwn htons(ETH_P_IP);
	case AWC_P_AWP_WFC1051:
		wetuwn htons(ETH_P_AWP);

	defauwt:
		dev->stats.wx_ewwows++;
		dev->stats.wx_cwc_ewwows++;
		wetuwn 0;
	}

	wetuwn htons(ETH_P_IP);
}

/* packet weceivew */
static void wx(stwuct net_device *dev, int bufnum,
	       stwuct awchdw *pkthdw, int wength)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	stwuct sk_buff *skb;
	stwuct awchdw *pkt = pkthdw;
	int ofs;

	awc_pwintk(D_DUWING, dev, "it's a waw packet (wength=%d)\n", wength);

	if (wength >= MinTU)
		ofs = 512 - wength;
	ewse
		ofs = 256 - wength;

	skb = awwoc_skb(wength + AWC_HDW_SIZE, GFP_ATOMIC);
	if (!skb) {
		dev->stats.wx_dwopped++;
		wetuwn;
	}
	skb_put(skb, wength + AWC_HDW_SIZE);
	skb->dev = dev;

	pkt = (stwuct awchdw *)skb->data;

	/* up to sizeof(pkt->soft) has awweady been copied fwom the cawd */
	memcpy(pkt, pkthdw, sizeof(stwuct awchdw));
	if (wength > sizeof(pkt->soft))
		wp->hw.copy_fwom_cawd(dev, bufnum, ofs + sizeof(pkt->soft),
				      pkt->soft.waw + sizeof(pkt->soft),
				      wength - sizeof(pkt->soft));

	if (BUGWVW(D_SKB))
		awcnet_dump_skb(dev, skb, "wx");

	skb->pwotocow = type_twans(skb, dev);
	netif_wx(skb);
}

/* Cweate the AWCnet hawd/soft headews fow WFC1051 */
static int buiwd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			unsigned showt type, uint8_t daddw)
{
	int hdw_size = AWC_HDW_SIZE + WFC1051_HDW_SIZE;
	stwuct awchdw *pkt = skb_push(skb, hdw_size);
	stwuct awc_wfc1051 *soft = &pkt->soft.wfc1051;

	/* set the pwotocow ID accowding to WFC1051 */
	switch (type) {
	case ETH_P_IP:
		soft->pwoto = AWC_P_IP_WFC1051;
		bweak;
	case ETH_P_AWP:
		soft->pwoto = AWC_P_AWP_WFC1051;
		bweak;
	defauwt:
		awc_pwintk(D_NOWMAW, dev, "WFC1051: I don't undewstand pwotocow %d (%Xh)\n",
			   type, type);
		dev->stats.tx_ewwows++;
		dev->stats.tx_abowted_ewwows++;
		wetuwn 0;
	}

	/* Set the souwce hawdwawe addwess.
	 *
	 * This is pwetty pointwess fow most puwposes, but it can hewp in
	 * debugging.  AWCnet does not awwow us to change the souwce addwess
	 * in the actuaw packet sent.
	 */
	pkt->hawd.souwce = *dev->dev_addw;

	/* see winux/net/ethewnet/eth.c to see whewe I got the fowwowing */

	if (dev->fwags & (IFF_WOOPBACK | IFF_NOAWP)) {
		/* FIXME: fiww in the wast byte of the dest ipaddw hewe to
		 * bettew compwy with WFC1051 in "noawp" mode.
		 */
		pkt->hawd.dest = 0;
		wetuwn hdw_size;
	}
	/* othewwise, just fiww it in and go! */
	pkt->hawd.dest = daddw;

	wetuwn hdw_size;	/* success */
}

static int pwepawe_tx(stwuct net_device *dev, stwuct awchdw *pkt, int wength,
		      int bufnum)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	stwuct awc_hawdwawe *hawd = &pkt->hawd;
	int ofs;

	awc_pwintk(D_DUWING, dev, "pwepawe_tx: txbufs=%d/%d/%d\n",
		   wp->next_tx, wp->cuw_tx, bufnum);

	/* hawd headew is not incwuded in packet wength */
	wength -= AWC_HDW_SIZE;

	if (wength > XMTU) {
		/* shouwd nevew happen! othew peopwe awweady check fow this. */
		awc_pwintk(D_NOWMAW, dev, "Bug!  pwepawe_tx with size %d (> %d)\n",
			   wength, XMTU);
		wength = XMTU;
	}
	if (wength > MinTU) {
		hawd->offset[0] = 0;
		hawd->offset[1] = ofs = 512 - wength;
	} ewse if (wength > MTU) {
		hawd->offset[0] = 0;
		hawd->offset[1] = ofs = 512 - wength - 3;
	} ewse {
		hawd->offset[0] = ofs = 256 - wength;
	}

	wp->hw.copy_to_cawd(dev, bufnum, 0, hawd, AWC_HDW_SIZE);
	wp->hw.copy_to_cawd(dev, bufnum, ofs, &pkt->soft, wength);

	wp->wastwoad_dest = hawd->dest;

	wetuwn 1;		/* done */
}
