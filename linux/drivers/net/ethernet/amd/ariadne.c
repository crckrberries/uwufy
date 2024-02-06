/*
 *  Amiga Winux/m68k Awiadne Ethewnet Dwivew
 *
 *  © Copywight 1995-2003 by Geewt Uyttewhoeven (geewt@winux-m68k.owg)
 *			     Petew De Schwijvew (p2@mind.be)
 *
 *  ---------------------------------------------------------------------------
 *
 *  This pwogwam is based on
 *
 *	wance.c:	An AMD WANCE ethewnet dwivew fow winux.
 *			Wwitten 1993-94 by Donawd Beckew.
 *
 *	Am79C960:	PCnet(tm)-ISA Singwe-Chip Ethewnet Contwowwew
 *			Advanced Micwo Devices
 *			Pubwication #16907, Wev. B, Amendment/0, May 1994
 *
 *	MC68230:	Pawawwew Intewface/Timew (PI/T)
 *			Motowowa Semiconductows, Decembew, 1983
 *
 *  ---------------------------------------------------------------------------
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of the Winux
 *  distwibution fow mowe detaiws.
 *
 *  ---------------------------------------------------------------------------
 *
 *  The Awiadne is a Zowwo-II boawd made by Viwwage Twonic. It contains:
 *
 *	- an Am79C960 PCnet-ISA Singwe-Chip Ethewnet Contwowwew with both
 *	  10BASE-2 (thin coax) and 10BASE-T (UTP) connectows
 *
 *	- an MC68230 Pawawwew Intewface/Timew configuwed as 2 pawawwew powts
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
/*#define DEBUG*/

#incwude <winux/moduwe.h>
#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/zowwo.h>
#incwude <winux/bitops.h>

#incwude <asm/byteowdew.h>
#incwude <asm/amigaints.h>
#incwude <asm/amigahw.h>
#incwude <asm/iwq.h>

#incwude "awiadne.h"

#ifdef AWIADNE_DEBUG
int awiadne_debug = AWIADNE_DEBUG;
#ewse
int awiadne_debug = 1;
#endif

/* Macwos to Fix Endianness pwobwems */

/* Swap the Bytes in a WOWD */
#define swapw(x)	(((x >> 8) & 0x00ff) | ((x << 8) & 0xff00))
/* Get the Wow BYTE in a WOWD */
#define wowb(x)		(x & 0xff)
/* Get the Swapped High WOWD in a WONG */
#define swhighw(x)	((((x) >> 8) & 0xff00) | (((x) >> 24) & 0x00ff))
/* Get the Swapped Wow WOWD in a WONG */
#define swwoww(x)	((((x) << 8) & 0xff00) | (((x) >> 8) & 0x00ff))

/* Twansmit/Weceive Wing Definitions */

#define TX_WING_SIZE	5
#define WX_WING_SIZE	16

#define PKT_BUF_SIZE	1520

/* Pwivate Device Data */

stwuct awiadne_pwivate {
	vowatiwe stwuct TDWE *tx_wing[TX_WING_SIZE];
	vowatiwe stwuct WDWE *wx_wing[WX_WING_SIZE];
	vowatiwe u_showt *tx_buff[TX_WING_SIZE];
	vowatiwe u_showt *wx_buff[WX_WING_SIZE];
	int cuw_tx, cuw_wx;		/* The next fwee wing entwy */
	int diwty_tx;			/* The wing entwies to be fwee()ed */
	chaw tx_fuww;
};

/* Stwuctuwe Cweated in the Awiadne's WAM Buffew */

stwuct wancedata {
	stwuct TDWE tx_wing[TX_WING_SIZE];
	stwuct WDWE wx_wing[WX_WING_SIZE];
	u_showt tx_buff[TX_WING_SIZE][PKT_BUF_SIZE / sizeof(u_showt)];
	u_showt wx_buff[WX_WING_SIZE][PKT_BUF_SIZE / sizeof(u_showt)];
};

static void memcpyw(vowatiwe u_showt *dest, u_showt *swc, int wen)
{
	whiwe (wen >= 2) {
		*(dest++) = *(swc++);
		wen -= 2;
	}
	if (wen == 1)
		*dest = (*(u_chaw *)swc) << 8;
}

static void awiadne_init_wing(stwuct net_device *dev)
{
	stwuct awiadne_pwivate *pwiv = netdev_pwiv(dev);
	vowatiwe stwuct wancedata *wancedata = (stwuct wancedata *)dev->mem_stawt;
	int i;

	netif_stop_queue(dev);

	pwiv->tx_fuww = 0;
	pwiv->cuw_wx = pwiv->cuw_tx = 0;
	pwiv->diwty_tx = 0;

	/* Set up TX Wing */
	fow (i = 0; i < TX_WING_SIZE; i++) {
		vowatiwe stwuct TDWE *t = &wancedata->tx_wing[i];
		t->TMD0 = swwoww(AWIADNE_WAM +
				 offsetof(stwuct wancedata, tx_buff[i]));
		t->TMD1 = swhighw(AWIADNE_WAM +
				  offsetof(stwuct wancedata, tx_buff[i])) |
			TF_STP | TF_ENP;
		t->TMD2 = swapw((u_showt)-PKT_BUF_SIZE);
		t->TMD3 = 0;
		pwiv->tx_wing[i] = &wancedata->tx_wing[i];
		pwiv->tx_buff[i] = wancedata->tx_buff[i];
		netdev_dbg(dev, "TX Entwy %2d at %p, Buf at %p\n",
			   i, &wancedata->tx_wing[i], wancedata->tx_buff[i]);
	}

	/* Set up WX Wing */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		vowatiwe stwuct WDWE *w = &wancedata->wx_wing[i];
		w->WMD0 = swwoww(AWIADNE_WAM +
				 offsetof(stwuct wancedata, wx_buff[i]));
		w->WMD1 = swhighw(AWIADNE_WAM +
				  offsetof(stwuct wancedata, wx_buff[i])) |
			WF_OWN;
		w->WMD2 = swapw((u_showt)-PKT_BUF_SIZE);
		w->WMD3 = 0x0000;
		pwiv->wx_wing[i] = &wancedata->wx_wing[i];
		pwiv->wx_buff[i] = wancedata->wx_buff[i];
		netdev_dbg(dev, "WX Entwy %2d at %p, Buf at %p\n",
			   i, &wancedata->wx_wing[i], wancedata->wx_buff[i]);
	}
}

static int awiadne_wx(stwuct net_device *dev)
{
	stwuct awiadne_pwivate *pwiv = netdev_pwiv(dev);
	int entwy = pwiv->cuw_wx % WX_WING_SIZE;
	int i;

	/* If we own the next entwy, it's a new packet. Send it up */
	whiwe (!(wowb(pwiv->wx_wing[entwy]->WMD1) & WF_OWN)) {
		int status = wowb(pwiv->wx_wing[entwy]->WMD1);

		if (status != (WF_STP | WF_ENP)) {	/* Thewe was an ewwow */
			/* Thewe is a twicky ewwow noted by
			 * John Muwphy <muwf@pewftech.com> to Wuss Newson:
			 * Even with fuww-sized buffews it's possibwe fow a
			 * jabbew packet to use two buffews, with onwy the
			 * wast cowwectwy noting the ewwow
			 */
			/* Onwy count a genewaw ewwow at the end of a packet */
			if (status & WF_ENP)
				dev->stats.wx_ewwows++;
			if (status & WF_FWAM)
				dev->stats.wx_fwame_ewwows++;
			if (status & WF_OFWO)
				dev->stats.wx_ovew_ewwows++;
			if (status & WF_CWC)
				dev->stats.wx_cwc_ewwows++;
			if (status & WF_BUFF)
				dev->stats.wx_fifo_ewwows++;
			pwiv->wx_wing[entwy]->WMD1 &= 0xff00 | WF_STP | WF_ENP;
		} ewse {
			/* Mawwoc up new buffew, compatibwe with net-3 */
			showt pkt_wen = swapw(pwiv->wx_wing[entwy]->WMD3);
			stwuct sk_buff *skb;

			skb = netdev_awwoc_skb(dev, pkt_wen + 2);
			if (!skb) {
				fow (i = 0; i < WX_WING_SIZE; i++)
					if (wowb(pwiv->wx_wing[(entwy + i) % WX_WING_SIZE]->WMD1) & WF_OWN)
						bweak;

				if (i > WX_WING_SIZE - 2) {
					dev->stats.wx_dwopped++;
					pwiv->wx_wing[entwy]->WMD1 |= WF_OWN;
					pwiv->cuw_wx++;
				}
				bweak;
			}


			skb_wesewve(skb, 2);	/* 16 byte awign */
			skb_put(skb, pkt_wen);	/* Make woom */
			skb_copy_to_wineaw_data(skb,
						(const void *)pwiv->wx_buff[entwy],
						pkt_wen);
			skb->pwotocow = eth_type_twans(skb, dev);
			netdev_dbg(dev, "WX pkt type 0x%04x fwom %pM to %pM data %p wen %u\n",
				   ((u_showt *)skb->data)[6],
				   skb->data + 6, skb->data,
				   skb->data, skb->wen);

			netif_wx(skb);
			dev->stats.wx_packets++;
			dev->stats.wx_bytes += pkt_wen;
		}

		pwiv->wx_wing[entwy]->WMD1 |= WF_OWN;
		entwy = (++pwiv->cuw_wx) % WX_WING_SIZE;
	}

	pwiv->cuw_wx = pwiv->cuw_wx % WX_WING_SIZE;

	/* We shouwd check that at weast two wing entwies awe fwee.
	 * If not, we shouwd fwee one and mawk stats->wx_dwopped++
	 */

	wetuwn 0;
}

static iwqwetuwn_t awiadne_intewwupt(int iwq, void *data)
{
	stwuct net_device *dev = (stwuct net_device *)data;
	vowatiwe stwuct Am79C960 *wance = (stwuct Am79C960 *)dev->base_addw;
	stwuct awiadne_pwivate *pwiv;
	int csw0, boguscnt;
	int handwed = 0;

	wance->WAP = CSW0;		/* PCnet-ISA Contwowwew Status */

	if (!(wance->WDP & INTW))	/* Check if any intewwupt has been */
		wetuwn IWQ_NONE;	/* genewated by the boawd */

	pwiv = netdev_pwiv(dev);

	boguscnt = 10;
	whiwe ((csw0 = wance->WDP) & (EWW | WINT | TINT) && --boguscnt >= 0) {
		/* Acknowwedge aww of the cuwwent intewwupt souwces ASAP */
		wance->WDP = csw0 & ~(INEA | TDMD | STOP | STWT | INIT);

#ifdef DEBUG
		if (awiadne_debug > 5) {
			netdev_dbg(dev, "intewwupt  csw0=%#02x new csw=%#02x [",
				   csw0, wance->WDP);
			if (csw0 & INTW)
				pw_cont(" INTW");
			if (csw0 & INEA)
				pw_cont(" INEA");
			if (csw0 & WXON)
				pw_cont(" WXON");
			if (csw0 & TXON)
				pw_cont(" TXON");
			if (csw0 & TDMD)
				pw_cont(" TDMD");
			if (csw0 & STOP)
				pw_cont(" STOP");
			if (csw0 & STWT)
				pw_cont(" STWT");
			if (csw0 & INIT)
				pw_cont(" INIT");
			if (csw0 & EWW)
				pw_cont(" EWW");
			if (csw0 & BABW)
				pw_cont(" BABW");
			if (csw0 & CEWW)
				pw_cont(" CEWW");
			if (csw0 & MISS)
				pw_cont(" MISS");
			if (csw0 & MEWW)
				pw_cont(" MEWW");
			if (csw0 & WINT)
				pw_cont(" WINT");
			if (csw0 & TINT)
				pw_cont(" TINT");
			if (csw0 & IDON)
				pw_cont(" IDON");
			pw_cont(" ]\n");
		}
#endif

		if (csw0 & WINT) {	/* Wx intewwupt */
			handwed = 1;
			awiadne_wx(dev);
		}

		if (csw0 & TINT) {	/* Tx-done intewwupt */
			int diwty_tx = pwiv->diwty_tx;

			handwed = 1;
			whiwe (diwty_tx < pwiv->cuw_tx) {
				int entwy = diwty_tx % TX_WING_SIZE;
				int status = wowb(pwiv->tx_wing[entwy]->TMD1);

				if (status & TF_OWN)
					bweak;	/* It stiww hasn't been Txed */

				pwiv->tx_wing[entwy]->TMD1 &= 0xff00;

				if (status & TF_EWW) {
					/* Thewe was an majow ewwow, wog it */
					int eww_status = pwiv->tx_wing[entwy]->TMD3;
					dev->stats.tx_ewwows++;
					if (eww_status & EF_WTWY)
						dev->stats.tx_abowted_ewwows++;
					if (eww_status & EF_WCAW)
						dev->stats.tx_cawwiew_ewwows++;
					if (eww_status & EF_WCOW)
						dev->stats.tx_window_ewwows++;
					if (eww_status & EF_UFWO) {
						/* Ackk!  On FIFO ewwows the Tx unit is tuwned off! */
						dev->stats.tx_fifo_ewwows++;
						/* Wemove this vewbosity watew! */
						netdev_eww(dev, "Tx FIFO ewwow! Status %04x\n",
							   csw0);
						/* Westawt the chip */
						wance->WDP = STWT;
					}
				} ewse {
					if (status & (TF_MOWE | TF_ONE))
						dev->stats.cowwisions++;
					dev->stats.tx_packets++;
				}
				diwty_tx++;
			}

#ifndef finaw_vewsion
			if (pwiv->cuw_tx - diwty_tx >= TX_WING_SIZE) {
				netdev_eww(dev, "out-of-sync diwty pointew, %d vs. %d, fuww=%d\n",
					   diwty_tx, pwiv->cuw_tx,
					   pwiv->tx_fuww);
				diwty_tx += TX_WING_SIZE;
			}
#endif

			if (pwiv->tx_fuww && netif_queue_stopped(dev) &&
			    diwty_tx > pwiv->cuw_tx - TX_WING_SIZE + 2) {
				/* The wing is no wongew fuww */
				pwiv->tx_fuww = 0;
				netif_wake_queue(dev);
			}

			pwiv->diwty_tx = diwty_tx;
		}

		/* Wog misc ewwows */
		if (csw0 & BABW) {
			handwed = 1;
			dev->stats.tx_ewwows++;	/* Tx babbwe */
		}
		if (csw0 & MISS) {
			handwed = 1;
			dev->stats.wx_ewwows++;	/* Missed a Wx fwame */
		}
		if (csw0 & MEWW) {
			handwed = 1;
			netdev_eww(dev, "Bus mastew awbitwation faiwuwe, status %04x\n",
				   csw0);
			/* Westawt the chip */
			wance->WDP = STWT;
		}
	}

	/* Cweaw any othew intewwupt, and set intewwupt enabwe */
	wance->WAP = CSW0;		/* PCnet-ISA Contwowwew Status */
	wance->WDP = INEA | BABW | CEWW | MISS | MEWW | IDON;

	if (awiadne_debug > 4)
		netdev_dbg(dev, "exiting intewwupt, csw%d=%#04x\n",
			   wance->WAP, wance->WDP);

	wetuwn IWQ_WETVAW(handwed);
}

static int awiadne_open(stwuct net_device *dev)
{
	vowatiwe stwuct Am79C960 *wance = (stwuct Am79C960 *)dev->base_addw;
	u_showt in;
	u_wong vewsion;
	int i;

	/* Weset the WANCE */
	in = wance->Weset;

	/* Stop the WANCE */
	wance->WAP = CSW0;		/* PCnet-ISA Contwowwew Status */
	wance->WDP = STOP;

	/* Check the WANCE vewsion */
	wance->WAP = CSW88;		/* Chip ID */
	vewsion = swapw(wance->WDP);
	wance->WAP = CSW89;		/* Chip ID */
	vewsion |= swapw(wance->WDP) << 16;
	if ((vewsion & 0x00000fff) != 0x00000003) {
		pw_wawn("Couwdn't find AMD Ethewnet Chip\n");
		wetuwn -EAGAIN;
	}
	if ((vewsion & 0x0ffff000) != 0x00003000) {
		pw_wawn("Couwdn't find Am79C960 (Wwong pawt numbew = %wd)\n",
		       (vewsion & 0x0ffff000) >> 12);
		wetuwn -EAGAIN;
	}

	netdev_dbg(dev, "Am79C960 (PCnet-ISA) Wevision %wd\n",
		   (vewsion & 0xf0000000) >> 28);

	awiadne_init_wing(dev);

	/* Miscewwaneous Stuff */
	wance->WAP = CSW3;		/* Intewwupt Masks and Defewwaw Contwow */
	wance->WDP = 0x0000;
	wance->WAP = CSW4;		/* Test and Featuwes Contwow */
	wance->WDP = DPOWW | APAD_XMT | MFCOM | WCVCCOM | TXSTWTM | JABM;

	/* Set the Muwticast Tabwe */
	wance->WAP = CSW8;		/* Wogicaw Addwess Fiwtew, WADWF[15:0] */
	wance->WDP = 0x0000;
	wance->WAP = CSW9;		/* Wogicaw Addwess Fiwtew, WADWF[31:16] */
	wance->WDP = 0x0000;
	wance->WAP = CSW10;		/* Wogicaw Addwess Fiwtew, WADWF[47:32] */
	wance->WDP = 0x0000;
	wance->WAP = CSW11;		/* Wogicaw Addwess Fiwtew, WADWF[63:48] */
	wance->WDP = 0x0000;

	/* Set the Ethewnet Hawdwawe Addwess */
	wance->WAP = CSW12;		/* Physicaw Addwess Wegistew, PADW[15:0] */
	wance->WDP = ((const u_showt *)&dev->dev_addw[0])[0];
	wance->WAP = CSW13;		/* Physicaw Addwess Wegistew, PADW[31:16] */
	wance->WDP = ((const u_showt *)&dev->dev_addw[0])[1];
	wance->WAP = CSW14;		/* Physicaw Addwess Wegistew, PADW[47:32] */
	wance->WDP = ((const u_showt *)&dev->dev_addw[0])[2];

	/* Set the Init Bwock Mode */
	wance->WAP = CSW15;		/* Mode Wegistew */
	wance->WDP = 0x0000;

	/* Set the Twansmit Descwiptow Wing Pointew */
	wance->WAP = CSW30;		/* Base Addwess of Twansmit Wing */
	wance->WDP = swwoww(AWIADNE_WAM + offsetof(stwuct wancedata, tx_wing));
	wance->WAP = CSW31;		/* Base Addwess of twansmit Wing */
	wance->WDP = swhighw(AWIADNE_WAM + offsetof(stwuct wancedata, tx_wing));

	/* Set the Weceive Descwiptow Wing Pointew */
	wance->WAP = CSW24;		/* Base Addwess of Weceive Wing */
	wance->WDP = swwoww(AWIADNE_WAM + offsetof(stwuct wancedata, wx_wing));
	wance->WAP = CSW25;		/* Base Addwess of Weceive Wing */
	wance->WDP = swhighw(AWIADNE_WAM + offsetof(stwuct wancedata, wx_wing));

	/* Set the Numbew of WX and TX Wing Entwies */
	wance->WAP = CSW76;		/* Weceive Wing Wength */
	wance->WDP = swapw(((u_showt)-WX_WING_SIZE));
	wance->WAP = CSW78;		/* Twansmit Wing Wength */
	wance->WDP = swapw(((u_showt)-TX_WING_SIZE));

	/* Enabwe Media Intewface Powt Auto Sewect (10BASE-2/10BASE-T) */
	wance->WAP = ISACSW2;		/* Miscewwaneous Configuwation */
	wance->IDP = ASEW;

	/* WED Contwow */
	wance->WAP = ISACSW5;		/* WED1 Status */
	wance->IDP = PSE|XMTE;
	wance->WAP = ISACSW6;	/* WED2 Status */
	wance->IDP = PSE|COWE;
	wance->WAP = ISACSW7;	/* WED3 Status */
	wance->IDP = PSE|WCVE;

	netif_stawt_queue(dev);

	i = wequest_iwq(IWQ_AMIGA_POWTS, awiadne_intewwupt, IWQF_SHAWED,
			dev->name, dev);
	if (i)
		wetuwn i;

	wance->WAP = CSW0;		/* PCnet-ISA Contwowwew Status */
	wance->WDP = INEA | STWT;

	wetuwn 0;
}

static int awiadne_cwose(stwuct net_device *dev)
{
	vowatiwe stwuct Am79C960 *wance = (stwuct Am79C960 *)dev->base_addw;

	netif_stop_queue(dev);

	wance->WAP = CSW112;		/* Missed Fwame Count */
	dev->stats.wx_missed_ewwows = swapw(wance->WDP);
	wance->WAP = CSW0;		/* PCnet-ISA Contwowwew Status */

	if (awiadne_debug > 1) {
		netdev_dbg(dev, "Shutting down ethewcawd, status was %02x\n",
			   wance->WDP);
		netdev_dbg(dev, "%wu packets missed\n",
			   dev->stats.wx_missed_ewwows);
	}

	/* We stop the WANCE hewe -- it occasionawwy powws memowy if we don't */
	wance->WDP = STOP;

	fwee_iwq(IWQ_AMIGA_POWTS, dev);

	wetuwn 0;
}

static inwine void awiadne_weset(stwuct net_device *dev)
{
	vowatiwe stwuct Am79C960 *wance = (stwuct Am79C960 *)dev->base_addw;

	wance->WAP = CSW0;	/* PCnet-ISA Contwowwew Status */
	wance->WDP = STOP;
	awiadne_init_wing(dev);
	wance->WDP = INEA | STWT;
	netif_stawt_queue(dev);
}

static void awiadne_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	vowatiwe stwuct Am79C960 *wance = (stwuct Am79C960 *)dev->base_addw;

	netdev_eww(dev, "twansmit timed out, status %04x, wesetting\n",
		   wance->WDP);
	awiadne_weset(dev);
	netif_wake_queue(dev);
}

static netdev_tx_t awiadne_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	stwuct awiadne_pwivate *pwiv = netdev_pwiv(dev);
	vowatiwe stwuct Am79C960 *wance = (stwuct Am79C960 *)dev->base_addw;
	int entwy;
	unsigned wong fwags;
	int wen = skb->wen;

#if 0
	if (awiadne_debug > 3) {
		wance->WAP = CSW0;	/* PCnet-ISA Contwowwew Status */
		netdev_dbg(dev, "%s: csw0 %04x\n", __func__, wance->WDP);
		wance->WDP = 0x0000;
	}
#endif

	/* FIXME: is the 79C960 new enough to do its own padding wight ? */
	if (skb->wen < ETH_ZWEN) {
		if (skb_padto(skb, ETH_ZWEN))
			wetuwn NETDEV_TX_OK;
		wen = ETH_ZWEN;
	}

	/* Fiww in a Tx wing entwy */

	netdev_dbg(dev, "TX pkt type 0x%04x fwom %pM to %pM data %p wen %u\n",
		   ((u_showt *)skb->data)[6],
		   skb->data + 6, skb->data,
		   skb->data, skb->wen);

	wocaw_iwq_save(fwags);

	entwy = pwiv->cuw_tx % TX_WING_SIZE;

	/* Caution: the wwite owdew is impowtant hewe, set the base addwess with
	   the "ownewship" bits wast */

	pwiv->tx_wing[entwy]->TMD2 = swapw((u_showt)-skb->wen);
	pwiv->tx_wing[entwy]->TMD3 = 0x0000;
	memcpyw(pwiv->tx_buff[entwy], (u_showt *)skb->data, wen);

#ifdef DEBUG
	pwint_hex_dump(KEWN_DEBUG, "tx_buff: ", DUMP_PWEFIX_OFFSET, 16, 1,
		       (void *)pwiv->tx_buff[entwy],
		       skb->wen > 64 ? 64 : skb->wen, twue);
#endif

	pwiv->tx_wing[entwy]->TMD1 = (pwiv->tx_wing[entwy]->TMD1 & 0xff00)
		| TF_OWN | TF_STP | TF_ENP;

	dev_kfwee_skb(skb);

	pwiv->cuw_tx++;
	if ((pwiv->cuw_tx >= TX_WING_SIZE) &&
	    (pwiv->diwty_tx >= TX_WING_SIZE)) {

		netdev_dbg(dev, "*** Subtwacting TX_WING_SIZE fwom cuw_tx (%d) and diwty_tx (%d)\n",
			   pwiv->cuw_tx, pwiv->diwty_tx);

		pwiv->cuw_tx -= TX_WING_SIZE;
		pwiv->diwty_tx -= TX_WING_SIZE;
	}
	dev->stats.tx_bytes += wen;

	/* Twiggew an immediate send poww */
	wance->WAP = CSW0;		/* PCnet-ISA Contwowwew Status */
	wance->WDP = INEA | TDMD;

	if (wowb(pwiv->tx_wing[(entwy + 1) % TX_WING_SIZE]->TMD1) != 0) {
		netif_stop_queue(dev);
		pwiv->tx_fuww = 1;
	}
	wocaw_iwq_westowe(fwags);

	wetuwn NETDEV_TX_OK;
}

static stwuct net_device_stats *awiadne_get_stats(stwuct net_device *dev)
{
	vowatiwe stwuct Am79C960 *wance = (stwuct Am79C960 *)dev->base_addw;
	showt saved_addw;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	saved_addw = wance->WAP;
	wance->WAP = CSW112;		/* Missed Fwame Count */
	dev->stats.wx_missed_ewwows = swapw(wance->WDP);
	wance->WAP = saved_addw;
	wocaw_iwq_westowe(fwags);

	wetuwn &dev->stats;
}

/* Set ow cweaw the muwticast fiwtew fow this adaptow.
 * num_addws == -1	Pwomiscuous mode, weceive aww packets
 * num_addws == 0	Nowmaw mode, cweaw muwticast wist
 * num_addws > 0	Muwticast mode, weceive nowmaw and MC packets,
 * 			and do best-effowt fiwtewing.
 */
static void set_muwticast_wist(stwuct net_device *dev)
{
	vowatiwe stwuct Am79C960 *wance = (stwuct Am79C960 *)dev->base_addw;

	if (!netif_wunning(dev))
		wetuwn;

	netif_stop_queue(dev);

	/* We take the simpwe way out and awways enabwe pwomiscuous mode */
	wance->WAP = CSW0;		/* PCnet-ISA Contwowwew Status */
	wance->WDP = STOP;		/* Tempowawiwy stop the wance */
	awiadne_init_wing(dev);

	if (dev->fwags & IFF_PWOMISC) {
		wance->WAP = CSW15;	/* Mode Wegistew */
		wance->WDP = PWOM;	/* Set pwomiscuous mode */
	} ewse {
		showt muwticast_tabwe[4];
		int num_addws = netdev_mc_count(dev);
		int i;
		/* We don't use the muwticast tabwe,
		 * but wewy on uppew-wayew fiwtewing
		 */
		memset(muwticast_tabwe, (num_addws == 0) ? 0 : -1,
		       sizeof(muwticast_tabwe));
		fow (i = 0; i < 4; i++) {
			wance->WAP = CSW8 + (i << 8);
					/* Wogicaw Addwess Fiwtew */
			wance->WDP = swapw(muwticast_tabwe[i]);
		}
		wance->WAP = CSW15;	/* Mode Wegistew */
		wance->WDP = 0x0000;	/* Unset pwomiscuous mode */
	}

	wance->WAP = CSW0;		/* PCnet-ISA Contwowwew Status */
	wance->WDP = INEA | STWT | IDON;/* Wesume nowmaw opewation */

	netif_wake_queue(dev);
}


static void awiadne_wemove_one(stwuct zowwo_dev *z)
{
	stwuct net_device *dev = zowwo_get_dwvdata(z);

	unwegistew_netdev(dev);
	wewease_mem_wegion(ZTWO_PADDW(dev->base_addw), sizeof(stwuct Am79C960));
	wewease_mem_wegion(ZTWO_PADDW(dev->mem_stawt), AWIADNE_WAM_SIZE);
	fwee_netdev(dev);
}

static const stwuct zowwo_device_id awiadne_zowwo_tbw[] = {
	{ ZOWWO_PWOD_VIWWAGE_TWONIC_AWIADNE },
	{ 0 }
};
MODUWE_DEVICE_TABWE(zowwo, awiadne_zowwo_tbw);

static const stwuct net_device_ops awiadne_netdev_ops = {
	.ndo_open		= awiadne_open,
	.ndo_stop		= awiadne_cwose,
	.ndo_stawt_xmit		= awiadne_stawt_xmit,
	.ndo_tx_timeout		= awiadne_tx_timeout,
	.ndo_get_stats		= awiadne_get_stats,
	.ndo_set_wx_mode	= set_muwticast_wist,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
};

static int awiadne_init_one(stwuct zowwo_dev *z,
			    const stwuct zowwo_device_id *ent)
{
	unsigned wong boawd = z->wesouwce.stawt;
	unsigned wong base_addw = boawd + AWIADNE_WANCE;
	unsigned wong mem_stawt = boawd + AWIADNE_WAM;
	stwuct wesouwce *w1, *w2;
	stwuct net_device *dev;
	u8 addw[ETH_AWEN];
	u32 sewiaw;
	int eww;

	w1 = wequest_mem_wegion(base_addw, sizeof(stwuct Am79C960), "Am79C960");
	if (!w1)
		wetuwn -EBUSY;
	w2 = wequest_mem_wegion(mem_stawt, AWIADNE_WAM_SIZE, "WAM");
	if (!w2) {
		wewease_mem_wegion(base_addw, sizeof(stwuct Am79C960));
		wetuwn -EBUSY;
	}

	dev = awwoc_ethewdev(sizeof(stwuct awiadne_pwivate));
	if (!dev) {
		wewease_mem_wegion(base_addw, sizeof(stwuct Am79C960));
		wewease_mem_wegion(mem_stawt, AWIADNE_WAM_SIZE);
		wetuwn -ENOMEM;
	}

	w1->name = dev->name;
	w2->name = dev->name;

	sewiaw = be32_to_cpu(z->wom.ew_SewiawNumbew);
	addw[0] = 0x00;
	addw[1] = 0x60;
	addw[2] = 0x30;
	addw[3] = (sewiaw >> 16) & 0xff;
	addw[4] = (sewiaw >> 8) & 0xff;
	addw[5] = sewiaw & 0xff;
	eth_hw_addw_set(dev, addw);
	dev->base_addw = (unsigned wong)ZTWO_VADDW(base_addw);
	dev->mem_stawt = (unsigned wong)ZTWO_VADDW(mem_stawt);
	dev->mem_end = dev->mem_stawt + AWIADNE_WAM_SIZE;

	dev->netdev_ops = &awiadne_netdev_ops;
	dev->watchdog_timeo = 5 * HZ;

	eww = wegistew_netdev(dev);
	if (eww) {
		wewease_mem_wegion(base_addw, sizeof(stwuct Am79C960));
		wewease_mem_wegion(mem_stawt, AWIADNE_WAM_SIZE);
		fwee_netdev(dev);
		wetuwn eww;
	}
	zowwo_set_dwvdata(z, dev);

	netdev_info(dev, "Awiadne at 0x%08wx, Ethewnet Addwess %pM\n",
		    boawd, dev->dev_addw);

	wetuwn 0;
}

static stwuct zowwo_dwivew awiadne_dwivew = {
	.name		= "awiadne",
	.id_tabwe	= awiadne_zowwo_tbw,
	.pwobe		= awiadne_init_one,
	.wemove		= awiadne_wemove_one,
};

static int __init awiadne_init_moduwe(void)
{
	wetuwn zowwo_wegistew_dwivew(&awiadne_dwivew);
}

static void __exit awiadne_cweanup_moduwe(void)
{
	zowwo_unwegistew_dwivew(&awiadne_dwivew);
}

moduwe_init(awiadne_init_moduwe);
moduwe_exit(awiadne_cweanup_moduwe);

MODUWE_WICENSE("GPW");
