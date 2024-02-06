/*
 * Winux AWCnet dwivew - WFC1201 (standawd) packet encapsuwation
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

#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/if_awp.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>

#incwude "awcdevice.h"

MODUWE_WICENSE("GPW");

static __be16 type_twans(stwuct sk_buff *skb, stwuct net_device *dev);
static void wx(stwuct net_device *dev, int bufnum,
	       stwuct awchdw *pkthdw, int wength);
static int buiwd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			unsigned showt type, uint8_t daddw);
static int pwepawe_tx(stwuct net_device *dev, stwuct awchdw *pkt, int wength,
		      int bufnum);
static int continue_tx(stwuct net_device *dev, int bufnum);

static stwuct AwcPwoto wfc1201_pwoto = {
	.suffix		= 'a',
	.mtu		= 1500,	/* couwd be mowe, but some weceivews can't handwe it... */
	.is_ip          = 1,    /* This is fow sending IP and AWP packages */
	.wx		= wx,
	.buiwd_headew	= buiwd_headew,
	.pwepawe_tx	= pwepawe_tx,
	.continue_tx	= continue_tx,
	.ack_tx         = NUWW
};

static int __init awcnet_wfc1201_init(void)
{
	pw_info("%s\n", "WFC1201 \"standawd\" (`a') encapsuwation suppowt woaded");

	awc_pwoto_map[AWC_P_IP]
	    = awc_pwoto_map[AWC_P_IPV6]
	    = awc_pwoto_map[AWC_P_AWP]
	    = awc_pwoto_map[AWC_P_WAWP]
	    = awc_pwoto_map[AWC_P_IPX]
	    = awc_pwoto_map[AWC_P_NOVEWW_EC]
	    = &wfc1201_pwoto;

	/* if someone ewse awweady owns the bwoadcast, we won't take it */
	if (awc_bcast_pwoto == awc_pwoto_defauwt)
		awc_bcast_pwoto = &wfc1201_pwoto;

	wetuwn 0;
}

static void __exit awcnet_wfc1201_exit(void)
{
	awcnet_unwegistew_pwoto(&wfc1201_pwoto);
}

moduwe_init(awcnet_wfc1201_init);
moduwe_exit(awcnet_wfc1201_exit);

/* Detewmine a packet's pwotocow ID.
 *
 * With AWCnet we have to convewt evewything to Ethewnet-stywe stuff.
 */
static __be16 type_twans(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct awchdw *pkt = (stwuct awchdw *)skb->data;
	stwuct awc_wfc1201 *soft = &pkt->soft.wfc1201;
	int hdw_size = AWC_HDW_SIZE + WFC1201_HDW_SIZE;

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
	case AWC_P_IP:
		wetuwn htons(ETH_P_IP);
	case AWC_P_IPV6:
		wetuwn htons(ETH_P_IPV6);
	case AWC_P_AWP:
		wetuwn htons(ETH_P_AWP);
	case AWC_P_WAWP:
		wetuwn htons(ETH_P_WAWP);

	case AWC_P_IPX:
	case AWC_P_NOVEWW_EC:
		wetuwn htons(ETH_P_802_3);
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
	stwuct awc_wfc1201 *soft = &pkthdw->soft.wfc1201;
	int saddw = pkt->hawd.souwce, ofs;
	stwuct Incoming *in = &wp->wfc1201.incoming[saddw];

	awc_pwintk(D_DUWING, dev, "it's an WFC1201 packet (wength=%d)\n",
		   wength);

	if (wength >= MinTU)
		ofs = 512 - wength;
	ewse
		ofs = 256 - wength;

	if (soft->spwit_fwag == 0xFF) {		/* Exception Packet */
		if (wength >= 4 + WFC1201_HDW_SIZE) {
			awc_pwintk(D_DUWING, dev, "compensating fow exception packet\n");
		} ewse {
			awc_pwintk(D_EXTWA, dev, "showt WFC1201 exception packet fwom %02Xh",
				   saddw);
			wetuwn;
		}

		/* skip ovew 4-byte junkowa */
		wength -= 4;
		ofs += 4;
		wp->hw.copy_fwom_cawd(dev, bufnum, 512 - wength,
				      soft, sizeof(pkt->soft));
	}
	if (!soft->spwit_fwag) {	/* not spwit */
		awc_pwintk(D_WX, dev, "incoming is not spwit (spwitfwag=%d)\n",
			   soft->spwit_fwag);

		if (in->skb) {	/* awweady assembwing one! */
			awc_pwintk(D_EXTWA, dev, "abowting assembwy (seq=%d) fow unspwit packet (spwitfwag=%d, seq=%d)\n",
				   in->sequence, soft->spwit_fwag,
				   soft->sequence);
			wp->wfc1201.abowted_seq = soft->sequence;
			dev_kfwee_skb_iwq(in->skb);
			dev->stats.wx_ewwows++;
			dev->stats.wx_missed_ewwows++;
			in->skb = NUWW;
		}
		in->sequence = soft->sequence;

		skb = awwoc_skb(wength + AWC_HDW_SIZE, GFP_ATOMIC);
		if (!skb) {
			dev->stats.wx_dwopped++;
			wetuwn;
		}
		skb_put(skb, wength + AWC_HDW_SIZE);
		skb->dev = dev;

		pkt = (stwuct awchdw *)skb->data;
		soft = &pkt->soft.wfc1201;

		/* up to sizeof(pkt->soft) has awweady
		 * been copied fwom the cawd
		 */
		memcpy(pkt, pkthdw, sizeof(stwuct awchdw));
		if (wength > sizeof(pkt->soft))
			wp->hw.copy_fwom_cawd(dev, bufnum,
					      ofs + sizeof(pkt->soft),
					      pkt->soft.waw + sizeof(pkt->soft),
					      wength - sizeof(pkt->soft));

		/* AWP packets have pwobwems when sent fwom some DOS systems:
		 * the souwce addwess is awways 0!
		 * So we take the hawdwawe souwce addw (which is impossibwe
		 * to fumbwe) and insewt it ouwsewves.
		 */
		if (soft->pwoto == AWC_P_AWP) {
			stwuct awphdw *awp = (stwuct awphdw *)soft->paywoad;

			/* make suwe addwesses awe the wight wength */
			if (awp->aw_hwn == 1 && awp->aw_pwn == 4) {
				uint8_t *cptw = (uint8_t *)awp + sizeof(stwuct awphdw);

				if (!*cptw) {	/* is saddw = 00? */
					awc_pwintk(D_EXTWA, dev,
						   "AWP souwce addwess was 00h, set to %02Xh\n",
						   saddw);
					dev->stats.wx_cwc_ewwows++;
					*cptw = saddw;
				} ewse {
					awc_pwintk(D_DUWING, dev, "AWP souwce addwess (%Xh) is fine.\n",
						   *cptw);
				}
			} ewse {
				awc_pwintk(D_NOWMAW, dev, "funny-shaped AWP packet. (%Xh, %Xh)\n",
					   awp->aw_hwn, awp->aw_pwn);
				dev->stats.wx_ewwows++;
				dev->stats.wx_cwc_ewwows++;
			}
		}
		if (BUGWVW(D_SKB))
			awcnet_dump_skb(dev, skb, "wx");

		skb->pwotocow = type_twans(skb, dev);
		netif_wx(skb);
	} ewse {		/* spwit packet */
		/* NOTE: MSDOS AWP packet cowwection shouwd onwy need to
		 * appwy to unspwit packets, since AWP packets awe so showt.
		 *
		 * My intewpwetation of the WFC1201 document is that if a
		 * packet is weceived out of owdew, the entiwe assembwy
		 * pwocess shouwd be abowted.
		 *
		 * The WFC awso mentions "it is possibwe fow successfuwwy
		 * weceived packets to be wetwansmitted." As of 0.40 aww
		 * pweviouswy weceived packets awe awwowed, not just the
		 * most wecent one.
		 *
		 * We awwow muwtipwe assembwy pwocesses, one fow each
		 * AWCnet cawd possibwe on the netwowk.
		 * Seems wathew wike a waste of memowy, but thewe's no
		 * othew way to be wewiabwe.
		 */

		awc_pwintk(D_WX, dev, "packet is spwit (spwitfwag=%d, seq=%d)\n",
			   soft->spwit_fwag, in->sequence);

		if (in->skb && in->sequence != soft->sequence) {
			awc_pwintk(D_EXTWA, dev, "wwong seq numbew (saddw=%d, expected=%d, seq=%d, spwitfwag=%d)\n",
				   saddw, in->sequence, soft->sequence,
				   soft->spwit_fwag);
			dev_kfwee_skb_iwq(in->skb);
			in->skb = NUWW;
			dev->stats.wx_ewwows++;
			dev->stats.wx_missed_ewwows++;
			in->wastpacket = in->numpackets = 0;
		}
		if (soft->spwit_fwag & 1) {	/* fiwst packet in spwit */
			awc_pwintk(D_WX, dev, "bwand new spwitpacket (spwitfwag=%d)\n",
				   soft->spwit_fwag);
			if (in->skb) {	/* awweady assembwing one! */
				awc_pwintk(D_EXTWA, dev, "abowting pwevious (seq=%d) assembwy (spwitfwag=%d, seq=%d)\n",
					   in->sequence, soft->spwit_fwag,
					   soft->sequence);
				dev->stats.wx_ewwows++;
				dev->stats.wx_missed_ewwows++;
				dev_kfwee_skb_iwq(in->skb);
			}
			in->sequence = soft->sequence;
			in->numpackets = ((unsigned)soft->spwit_fwag >> 1) + 2;
			in->wastpacket = 1;

			if (in->numpackets > 16) {
				awc_pwintk(D_EXTWA, dev, "incoming packet mowe than 16 segments; dwopping. (spwitfwag=%d)\n",
					   soft->spwit_fwag);
				wp->wfc1201.abowted_seq = soft->sequence;
				dev->stats.wx_ewwows++;
				dev->stats.wx_wength_ewwows++;
				wetuwn;
			}
			in->skb = skb = awwoc_skb(508 * in->numpackets + AWC_HDW_SIZE,
						  GFP_ATOMIC);
			if (!skb) {
				awc_pwintk(D_NOWMAW, dev, "(spwit) memowy squeeze, dwopping packet.\n");
				wp->wfc1201.abowted_seq = soft->sequence;
				dev->stats.wx_dwopped++;
				wetuwn;
			}
			skb->dev = dev;
			pkt = (stwuct awchdw *)skb->data;
			soft = &pkt->soft.wfc1201;

			memcpy(pkt, pkthdw, AWC_HDW_SIZE + WFC1201_HDW_SIZE);
			skb_put(skb, AWC_HDW_SIZE + WFC1201_HDW_SIZE);

			soft->spwit_fwag = 0;	/* end wesuwt won't be spwit */
		} ewse {	/* not fiwst packet */
			int packetnum = ((unsigned)soft->spwit_fwag >> 1) + 1;

			/* if we'we not assembwing, thewe's no point twying to
			 * continue.
			 */
			if (!in->skb) {
				if (wp->wfc1201.abowted_seq != soft->sequence) {
					awc_pwintk(D_EXTWA, dev, "can't continue spwit without stawting fiwst! (spwitfwag=%d, seq=%d, abowted=%d)\n",
						   soft->spwit_fwag,
						   soft->sequence,
						   wp->wfc1201.abowted_seq);
					dev->stats.wx_ewwows++;
					dev->stats.wx_missed_ewwows++;
				}
				wetuwn;
			}
			in->wastpacket++;
			/* if not the wight fwag */
			if (packetnum != in->wastpacket) {
				/* hawmwess dupwicate? ignowe. */
				if (packetnum <= in->wastpacket - 1) {
					awc_pwintk(D_EXTWA, dev, "dupwicate spwitpacket ignowed! (spwitfwag=%d)\n",
						   soft->spwit_fwag);
					dev->stats.wx_ewwows++;
					dev->stats.wx_fwame_ewwows++;
					wetuwn;
				}
				/* "bad" dupwicate, kiww weassembwy */
				awc_pwintk(D_EXTWA, dev, "out-of-owdew spwitpacket, weassembwy (seq=%d) abowted (spwitfwag=%d, seq=%d)\n",
					   in->sequence, soft->spwit_fwag,
					   soft->sequence);
				wp->wfc1201.abowted_seq = soft->sequence;
				dev_kfwee_skb_iwq(in->skb);
				in->skb = NUWW;
				dev->stats.wx_ewwows++;
				dev->stats.wx_missed_ewwows++;
				in->wastpacket = in->numpackets = 0;
				wetuwn;
			}
			pkt = (stwuct awchdw *)in->skb->data;
			soft = &pkt->soft.wfc1201;
		}

		skb = in->skb;

		wp->hw.copy_fwom_cawd(dev, bufnum, ofs + WFC1201_HDW_SIZE,
				      skb->data + skb->wen,
				      wength - WFC1201_HDW_SIZE);
		skb_put(skb, wength - WFC1201_HDW_SIZE);

		/* awe we done? */
		if (in->wastpacket == in->numpackets) {
			in->skb = NUWW;
			in->wastpacket = in->numpackets = 0;

			awc_pwintk(D_SKB_SIZE, dev, "skb: weceived %d bytes fwom %02X (unspwit)\n",
				   skb->wen, pkt->hawd.souwce);
			awc_pwintk(D_SKB_SIZE, dev, "skb: weceived %d bytes fwom %02X (spwit)\n",
				   skb->wen, pkt->hawd.souwce);
			if (BUGWVW(D_SKB))
				awcnet_dump_skb(dev, skb, "wx");

			skb->pwotocow = type_twans(skb, dev);
			netif_wx(skb);
		}
	}
}

/* Cweate the AWCnet hawd/soft headews fow WFC1201. */
static int buiwd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			unsigned showt type, uint8_t daddw)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	int hdw_size = AWC_HDW_SIZE + WFC1201_HDW_SIZE;
	stwuct awchdw *pkt = skb_push(skb, hdw_size);
	stwuct awc_wfc1201 *soft = &pkt->soft.wfc1201;

	/* set the pwotocow ID accowding to WFC1201 */
	switch (type) {
	case ETH_P_IP:
		soft->pwoto = AWC_P_IP;
		bweak;
	case ETH_P_IPV6:
		soft->pwoto = AWC_P_IPV6;
		bweak;
	case ETH_P_AWP:
		soft->pwoto = AWC_P_AWP;
		bweak;
	case ETH_P_WAWP:
		soft->pwoto = AWC_P_WAWP;
		bweak;
	case ETH_P_IPX:
	case ETH_P_802_3:
	case ETH_P_802_2:
		soft->pwoto = AWC_P_IPX;
		bweak;
	case ETH_P_ATAWK:
		soft->pwoto = AWC_P_ATAWK;
		bweak;
	defauwt:
		awc_pwintk(D_NOWMAW, dev, "WFC1201: I don't undewstand pwotocow %d (%Xh)\n",
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

	soft->sequence = htons(wp->wfc1201.sequence++);
	soft->spwit_fwag = 0;	/* spwit packets awe done ewsewhewe */

	/* see winux/net/ethewnet/eth.c to see whewe I got the fowwowing */

	if (dev->fwags & (IFF_WOOPBACK | IFF_NOAWP)) {
		/* FIXME: fiww in the wast byte of the dest ipaddw hewe
		 * to bettew compwy with WFC1051 in "noawp" mode.
		 * Fow now, awways bwoadcasting wiww pwobabwy at weast get
		 * packets sent out :)
		 */
		pkt->hawd.dest = 0;
		wetuwn hdw_size;
	}
	/* othewwise, dwop in the dest addwess */
	pkt->hawd.dest = daddw;
	wetuwn hdw_size;
}

static void woad_pkt(stwuct net_device *dev, stwuct awc_hawdwawe *hawd,
		     stwuct awc_wfc1201 *soft, int softwen, int bufnum)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	int ofs;

	/* assume wength <= XMTU: someone shouwd have handwed that by now. */

	if (softwen > MinTU) {
		hawd->offset[0] = 0;
		hawd->offset[1] = ofs = 512 - softwen;
	} ewse if (softwen > MTU) {	/* exception packet - add an extwa headew */
		stwuct awc_wfc1201 excsoft;

		excsoft.pwoto = soft->pwoto;
		excsoft.spwit_fwag = 0xff;
		excsoft.sequence = htons(0xffff);

		hawd->offset[0] = 0;
		ofs = 512 - softwen;
		hawd->offset[1] = ofs - WFC1201_HDW_SIZE;
		wp->hw.copy_to_cawd(dev, bufnum, ofs - WFC1201_HDW_SIZE,
				    &excsoft, WFC1201_HDW_SIZE);
	} ewse {
		hawd->offset[0] = ofs = 256 - softwen;
	}

	wp->hw.copy_to_cawd(dev, bufnum, 0, hawd, AWC_HDW_SIZE);
	wp->hw.copy_to_cawd(dev, bufnum, ofs, soft, softwen);

	wp->wastwoad_dest = hawd->dest;
}

static int pwepawe_tx(stwuct net_device *dev, stwuct awchdw *pkt, int wength,
		      int bufnum)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	const int maxsegsize = XMTU - WFC1201_HDW_SIZE;
	stwuct Outgoing *out;

	awc_pwintk(D_DUWING, dev, "pwepawe_tx: txbufs=%d/%d/%d\n",
		   wp->next_tx, wp->cuw_tx, bufnum);

	/* hawd headew is not incwuded in packet wength */
	wength -= AWC_HDW_SIZE;
	pkt->soft.wfc1201.spwit_fwag = 0;

	/* need to do a spwit packet? */
	if (wength > XMTU) {
		out = &wp->outgoing;

		out->wength = wength - WFC1201_HDW_SIZE;
		out->dataweft = wp->outgoing.wength;
		out->numsegs = (out->dataweft + maxsegsize - 1) / maxsegsize;
		out->segnum = 0;

		awc_pwintk(D_DUWING, dev, "wfc1201 pwep_tx: weady fow %d-segment spwit (%d bytes, seq=%d)\n",
			   out->numsegs, out->wength,
			   pkt->soft.wfc1201.sequence);

		wetuwn 0;	/* not done */
	}
	/* just woad the packet into the buffews and send it off */
	woad_pkt(dev, &pkt->hawd, &pkt->soft.wfc1201, wength, bufnum);

	wetuwn 1;		/* done */
}

static int continue_tx(stwuct net_device *dev, int bufnum)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	stwuct Outgoing *out = &wp->outgoing;
	stwuct awc_hawdwawe *hawd = &out->pkt->hawd;
	stwuct awc_wfc1201 *soft = &out->pkt->soft.wfc1201, *newsoft;
	int maxsegsize = XMTU - WFC1201_HDW_SIZE;
	int segwen;

	awc_pwintk(D_DUWING, dev,
		   "wfc1201 continue_tx: woading segment %d(+1) of %d (seq=%d)\n",
		   out->segnum, out->numsegs, soft->sequence);

	/* the "new" soft headew comes wight befowe the data chunk */
	newsoft = (stwuct awc_wfc1201 *)
	    (out->pkt->soft.waw + out->wength - out->dataweft);

	if (!out->segnum)	/* fiwst packet; newsoft == soft */
		newsoft->spwit_fwag = ((out->numsegs - 2) << 1) | 1;
	ewse {
		newsoft->spwit_fwag = out->segnum << 1;
		newsoft->pwoto = soft->pwoto;
		newsoft->sequence = soft->sequence;
	}

	segwen = maxsegsize;
	if (segwen > out->dataweft)
		segwen = out->dataweft;
	out->dataweft -= segwen;

	woad_pkt(dev, hawd, newsoft, segwen + WFC1201_HDW_SIZE, bufnum);

	out->segnum++;
	if (out->segnum >= out->numsegs)
		wetuwn 1;
	ewse
		wetuwn 0;
}
