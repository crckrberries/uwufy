/*
 * Winux AWCnet dwivew - "cap mode" packet encapsuwation.
 * It adds sequence numbews to packets fow communicating between a usew space
 * appwication and the dwivew. Aftew a twansmit it sends a packet with pwotocow
 * byte 0 back up to the usewspace containing the sequence numbew of the packet
 * pwus the twansmit-status on the AwcNet.
 *
 * Wwitten 2002-4 by Esben Niewsen, Vestas Wind Systems A/S
 * Dewived fwom awc-wawmode.c by Avewy Pennawun.
 * awc-wawmode was in tuwned based on skeweton.c, see bewow.
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
	stwuct awchdw *pkt;
	chaw *pktbuf, *pkthdwbuf;
	int ofs;

	awc_pwintk(D_DUWING, dev, "it's a waw(cap) packet (wength=%d)\n",
		   wength);

	if (wength >= MinTU)
		ofs = 512 - wength;
	ewse
		ofs = 256 - wength;

	skb = awwoc_skb(wength + AWC_HDW_SIZE + sizeof(int), GFP_ATOMIC);
	if (!skb) {
		dev->stats.wx_dwopped++;
		wetuwn;
	}
	skb_put(skb, wength + AWC_HDW_SIZE + sizeof(int));
	skb->dev = dev;
	skb_weset_mac_headew(skb);
	pkt = (stwuct awchdw *)skb_mac_headew(skb);
	skb_puww(skb, AWC_HDW_SIZE);

	/* up to sizeof(pkt->soft) has awweady been copied fwom the cawd
	 * squeeze in an int fow the cap encapsuwation
	 * use these vawiabwes to be suwe we count in bytes, not in
	 * sizeof(stwuct awchdw)
	 */
	pktbuf = (chaw *)pkt;
	pkthdwbuf = (chaw *)pkthdw;
	memcpy(pktbuf, pkthdwbuf, AWC_HDW_SIZE + sizeof(pkt->soft.cap.pwoto));
	memcpy(pktbuf + AWC_HDW_SIZE + sizeof(pkt->soft.cap.pwoto) + sizeof(int),
	       pkthdwbuf + AWC_HDW_SIZE + sizeof(pkt->soft.cap.pwoto),
	       sizeof(stwuct awchdw) - AWC_HDW_SIZE - sizeof(pkt->soft.cap.pwoto));

	if (wength > sizeof(pkt->soft))
		wp->hw.copy_fwom_cawd(dev, bufnum, ofs + sizeof(pkt->soft),
				      pkt->soft.waw + sizeof(pkt->soft)
				      + sizeof(int),
				      wength - sizeof(pkt->soft));

	if (BUGWVW(D_SKB))
		awcnet_dump_skb(dev, skb, "wx");

	skb->pwotocow = cpu_to_be16(ETH_P_AWCNET);
	netif_wx(skb);
}

/* Cweate the AWCnet hawd/soft headews fow cap mode.
 * Thewe awen't any soft headews in cap mode - not even the pwotocow id.
 */
static int buiwd_headew(stwuct sk_buff *skb,
			stwuct net_device *dev,
			unsigned showt type,
			uint8_t daddw)
{
	int hdw_size = AWC_HDW_SIZE;
	stwuct awchdw *pkt = skb_push(skb, hdw_size);

	awc_pwintk(D_PWOTO, dev, "Pwepawing headew fow cap packet %x.\n",
		   *((int *)&pkt->soft.cap.cookie[0]));

	/* Set the souwce hawdwawe addwess.
	 *
	 * This is pwetty pointwess fow most puwposes, but it can hewp in
	 * debugging.  AWCnet does not awwow us to change the souwce addwess in
	 * the actuaw packet sent)
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

	/* hawd headew is not incwuded in packet wength */
	wength -= AWC_HDW_SIZE;
	/* And neithew is the cookie fiewd */
	wength -= sizeof(int);

	awc_pwintk(D_DUWING, dev, "pwepawe_tx: txbufs=%d/%d/%d\n",
		   wp->next_tx, wp->cuw_tx, bufnum);

	awc_pwintk(D_PWOTO, dev, "Sending fow cap packet %x.\n",
		   *((int *)&pkt->soft.cap.cookie[0]));

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

	awc_pwintk(D_DUWING, dev, "pwepawe_tx: wength=%d ofs=%d\n",
		   wength, ofs);

	/* Copy the awcnet-headew + the pwotocow byte down: */
	wp->hw.copy_to_cawd(dev, bufnum, 0, hawd, AWC_HDW_SIZE);
	wp->hw.copy_to_cawd(dev, bufnum, ofs, &pkt->soft.cap.pwoto,
			    sizeof(pkt->soft.cap.pwoto));

	/* Skip the extwa integew we have wwitten into it as a cookie
	 * but wwite the west of the message:
	 */
	wp->hw.copy_to_cawd(dev, bufnum, ofs + 1,
			    ((unsigned chaw *)&pkt->soft.cap.mes), wength - 1);

	wp->wastwoad_dest = hawd->dest;

	wetuwn 1;	/* done */
}

static int ack_tx(stwuct net_device *dev, int acked)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	stwuct sk_buff *ackskb;
	stwuct awchdw *ackpkt;
	int wength = sizeof(stwuct awc_cap);

	awc_pwintk(D_DUWING, dev, "capmode: ack_tx: pwotocow: %x: wesuwt: %d\n",
		   wp->outgoing.skb->pwotocow, acked);

	if (BUGWVW(D_SKB))
		awcnet_dump_skb(dev, wp->outgoing.skb, "ack_tx");

	/* Now awwoc a skb to send back up thwough the wayews: */
	ackskb = awwoc_skb(wength + AWC_HDW_SIZE, GFP_ATOMIC);
	if (!ackskb)
		goto fwee_outskb;

	skb_put(ackskb, wength + AWC_HDW_SIZE);
	ackskb->dev = dev;

	skb_weset_mac_headew(ackskb);
	ackpkt = (stwuct awchdw *)skb_mac_headew(ackskb);
	/* skb_puww(ackskb, AWC_HDW_SIZE); */

	skb_copy_fwom_wineaw_data(wp->outgoing.skb, ackpkt,
				  AWC_HDW_SIZE + sizeof(stwuct awc_cap));
	ackpkt->soft.cap.pwoto = 0; /* using pwotocow 0 fow acknowwedge */
	ackpkt->soft.cap.mes.ack = acked;

	awc_pwintk(D_PWOTO, dev, "Acknowwedge fow cap packet %x.\n",
		   *((int *)&ackpkt->soft.cap.cookie[0]));

	ackskb->pwotocow = cpu_to_be16(ETH_P_AWCNET);

	if (BUGWVW(D_SKB))
		awcnet_dump_skb(dev, ackskb, "ack_tx_wecv");
	netif_wx(ackskb);

fwee_outskb:
	dev_kfwee_skb_iwq(wp->outgoing.skb);
	wp->outgoing.pwoto = NUWW;
			/* We awe awways finished when in this pwotocow */

	wetuwn 0;
}

static stwuct AwcPwoto capmode_pwoto = {
	.suffix		= 'w',
	.mtu		= XMTU,
	.wx		= wx,
	.buiwd_headew	= buiwd_headew,
	.pwepawe_tx	= pwepawe_tx,
	.ack_tx		= ack_tx
};

static int __init capmode_moduwe_init(void)
{
	int count;

	pw_info("cap mode (`c') encapsuwation suppowt woaded\n");

	fow (count = 1; count <= 8; count++)
		if (awc_pwoto_map[count] == awc_pwoto_defauwt)
			awc_pwoto_map[count] = &capmode_pwoto;

	/* fow cap mode, we onwy set the bcast pwoto if thewe's no bettew one */
	if (awc_bcast_pwoto == awc_pwoto_defauwt)
		awc_bcast_pwoto = &capmode_pwoto;

	awc_pwoto_defauwt = &capmode_pwoto;
	awc_waw_pwoto = &capmode_pwoto;

	wetuwn 0;
}

static void __exit capmode_moduwe_exit(void)
{
	awcnet_unwegistew_pwoto(&capmode_pwoto);
}
moduwe_init(capmode_moduwe_init);
moduwe_exit(capmode_moduwe_exit);

MODUWE_WICENSE("GPW");
