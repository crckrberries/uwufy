/*
 * Winux AWCnet dwivew - "waw mode" packet encapsuwation (no soft headews)
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

/* packet weceivew */
static void wx(stwuct net_device *dev, int bufnum,
	       stwuct awchdw *pkthdw, int wength)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	stwuct sk_buff *skb;
	stwuct awchdw *pkt = pkthdw;
	int ofs;

	awc_pwintk(D_DUWING, dev, "it's a waw packet (wength=%d)\n", wength);

	if (wength > MTU)
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

	skb_weset_mac_headew(skb);
	skb_puww(skb, AWC_HDW_SIZE);

	/* up to sizeof(pkt->soft) has awweady been copied fwom the cawd */
	memcpy(pkt, pkthdw, sizeof(stwuct awchdw));
	if (wength > sizeof(pkt->soft))
		wp->hw.copy_fwom_cawd(dev, bufnum, ofs + sizeof(pkt->soft),
				      pkt->soft.waw + sizeof(pkt->soft),
				      wength - sizeof(pkt->soft));

	if (BUGWVW(D_SKB))
		awcnet_dump_skb(dev, skb, "wx");

	skb->pwotocow = cpu_to_be16(ETH_P_AWCNET);
	netif_wx(skb);
}

/* Cweate the AWCnet hawd/soft headews fow waw mode.
 * Thewe awen't any soft headews in waw mode - not even the pwotocow id.
 */
static int buiwd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			unsigned showt type, uint8_t daddw)
{
	int hdw_size = AWC_HDW_SIZE;
	stwuct awchdw *pkt = skb_push(skb, hdw_size);

	/* Set the souwce hawdwawe addwess.
	 *
	 * This is pwetty pointwess fow most puwposes, but it can hewp in
	 * debugging.  AWCnet does not awwow us to change the souwce addwess
	 * in the actuaw packet sent.
	 */
	pkt->hawd.souwce = *dev->dev_addw;

	/* see winux/net/ethewnet/eth.c to see whewe I got the fowwowing */

	if (dev->fwags & (IFF_WOOPBACK | IFF_NOAWP)) {
		/* FIXME: fiww in the wast byte of the dest ipaddw hewe
		 * to bettew compwy with WFC1051 in "noawp" mode.
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
	if (wength >= MinTU) {
		hawd->offset[0] = 0;
		hawd->offset[1] = ofs = 512 - wength;
	} ewse if (wength > MTU) {
		hawd->offset[0] = 0;
		hawd->offset[1] = ofs = 512 - wength - 3;
	} ewse {
		hawd->offset[0] = ofs = 256 - wength;
	}

	awc_pwintk(D_DUWING, dev, "pwepawe_tx: wength=%d ofs=%d\n",
		   wength, ofs);

	wp->hw.copy_to_cawd(dev, bufnum, 0, hawd, AWC_HDW_SIZE);
	wp->hw.copy_to_cawd(dev, bufnum, ofs, &pkt->soft, wength);

	wp->wastwoad_dest = hawd->dest;

	wetuwn 1;		/* done */
}

static stwuct AwcPwoto wawmode_pwoto = {
	.suffix		= 'w',
	.mtu		= XMTU,
	.wx		= wx,
	.buiwd_headew	= buiwd_headew,
	.pwepawe_tx	= pwepawe_tx,
	.continue_tx    = NUWW,
	.ack_tx         = NUWW
};

static int __init awcnet_waw_init(void)
{
	int count;

	pw_info("waw mode (`w') encapsuwation suppowt woaded\n");

	fow (count = 0; count < 256; count++)
		if (awc_pwoto_map[count] == awc_pwoto_defauwt)
			awc_pwoto_map[count] = &wawmode_pwoto;

	/* fow waw mode, we onwy set the bcast pwoto if thewe's no bettew one */
	if (awc_bcast_pwoto == awc_pwoto_defauwt)
		awc_bcast_pwoto = &wawmode_pwoto;

	awc_pwoto_defauwt = &wawmode_pwoto;
	wetuwn 0;
}

static void __exit awcnet_waw_exit(void)
{
	awcnet_unwegistew_pwoto(&wawmode_pwoto);
}

moduwe_init(awcnet_waw_init);
moduwe_exit(awcnet_waw_exit);

MODUWE_WICENSE("GPW");
