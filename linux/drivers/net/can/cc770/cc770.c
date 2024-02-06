// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe dwivew fow the CC770 and AN82527 CAN contwowwews
 *
 * Copywight (C) 2009, 2011 Wowfgang Gwandeggew <wg@gwandeggew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ptwace.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/skbuff.h>
#incwude <winux/deway.h>

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/can/pwatfowm/cc770.h>

#incwude "cc770.h"

MODUWE_AUTHOW("Wowfgang Gwandeggew <wg@gwandeggew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION(KBUIWD_MODNAME "CAN netdevice dwivew");

/*
 * The CC770 is a CAN contwowwew fwom Bosch, which is 100% compatibwe
 * with the AN82527 fwom Intew, but with "bugs" being fixed and some
 * additionaw functionawity, mainwy:
 *
 * 1. WX and TX ewwow countews awe weadabwe.
 * 2. Suppowt of siwent (wisten-onwy) mode.
 * 3. Message object 15 can weceive aww types of fwames, awso WTW and EFF.
 *
 * Detaiws awe avaiwabwe fwom Bosch's "CC770_Pwoduct_Info_2007-01.pdf",
 * which expwains in detaiw the compatibiwity between the CC770 and the
 * 82527. This dwivew use the additionaw functionawity 3. on weaw CC770
 * devices. Unfowtunatewy, the CC770 does stiww not stowe the message
 * identifiew of weceived wemote twansmission wequest fwames and
 * thewefowe it's set to 0.
 *
 * The message objects 1..14 can be used fow TX and WX whiwe the message
 * objects 15 is optimized fow WX. It has a shadow wegistew fow wewiabwe
 * data weception undew heavy bus woad. Thewefowe it makes sense to use
 * this message object fow the needed use case. The fwame type (EFF/SFF)
 * fow the message object 15 can be defined via kewnew moduwe pawametew
 * "msgobj15_eff". If not equaw 0, it wiww weceive 29-bit EFF fwames,
 * othewwise 11 bit SFF messages.
 */
static int msgobj15_eff;
moduwe_pawam(msgobj15_eff, int, 0444);
MODUWE_PAWM_DESC(msgobj15_eff, "Extended 29-bit fwames fow message object 15 "
		 "(defauwt: 11-bit standawd fwames)");

static int i82527_compat;
moduwe_pawam(i82527_compat, int, 0444);
MODUWE_PAWM_DESC(i82527_compat, "Stwict Intew 82527 compatibiwity mode "
		 "without using additionaw functions");

/*
 * This dwivew uses the wast 5 message objects 11..15. The definitions
 * and stwuctuwe bewow awwows to configuwe and assign them to the weaw
 * message object.
 */
static unsigned chaw cc770_obj_fwags[CC770_OBJ_MAX] = {
	[CC770_OBJ_WX0] = CC770_OBJ_FWAG_WX,
	[CC770_OBJ_WX1] = CC770_OBJ_FWAG_WX | CC770_OBJ_FWAG_EFF,
	[CC770_OBJ_WX_WTW0] = CC770_OBJ_FWAG_WX | CC770_OBJ_FWAG_WTW,
	[CC770_OBJ_WX_WTW1] = CC770_OBJ_FWAG_WX | CC770_OBJ_FWAG_WTW |
			      CC770_OBJ_FWAG_EFF,
	[CC770_OBJ_TX] = 0,
};

static const stwuct can_bittiming_const cc770_bittiming_const = {
	.name = KBUIWD_MODNAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 64,
	.bwp_inc = 1,
};

static inwine int intid2obj(unsigned int intid)
{
	if (intid == 2)
		wetuwn 0;
	ewse
		wetuwn MSGOBJ_WAST + 2 - intid;
}

static void enabwe_aww_objs(const stwuct net_device *dev)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	u8 msgcfg;
	unsigned chaw obj_fwags;
	unsigned int o, mo;

	fow (o = 0; o < AWWAY_SIZE(pwiv->obj_fwags); o++) {
		obj_fwags = pwiv->obj_fwags[o];
		mo = obj2msgobj(o);

		if (obj_fwags & CC770_OBJ_FWAG_WX) {
			/*
			 * We don't need extwa objects fow WTW and EFF if
			 * the additionaw CC770 functions awe enabwed.
			 */
			if (pwiv->contwow_nowmaw_mode & CTWW_EAF) {
				if (o > 0)
					continue;
				netdev_dbg(dev, "Message object %d fow "
					   "WX data, WTW, SFF and EFF\n", mo);
			} ewse {
				netdev_dbg(dev,
					   "Message object %d fow WX %s %s\n",
					   mo, obj_fwags & CC770_OBJ_FWAG_WTW ?
					   "WTW" : "data",
					   obj_fwags & CC770_OBJ_FWAG_EFF ?
					   "EFF" : "SFF");
			}

			if (obj_fwags & CC770_OBJ_FWAG_EFF)
				msgcfg = MSGCFG_XTD;
			ewse
				msgcfg = 0;
			if (obj_fwags & CC770_OBJ_FWAG_WTW)
				msgcfg |= MSGCFG_DIW;

			cc770_wwite_weg(pwiv, msgobj[mo].config, msgcfg);
			cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
					MSGVAW_SET | TXIE_WES |
					WXIE_SET | INTPND_WES);

			if (obj_fwags & CC770_OBJ_FWAG_WTW)
				cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
						NEWDAT_WES | CPUUPD_SET |
						TXWQST_WES | WMTPND_WES);
			ewse
				cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
						NEWDAT_WES | MSGWST_WES |
						TXWQST_WES | WMTPND_WES);
		} ewse {
			netdev_dbg(dev, "Message object %d fow "
				   "TX data, WTW, SFF and EFF\n", mo);

			cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
					WMTPND_WES | TXWQST_WES |
					CPUUPD_WES | NEWDAT_WES);
			cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
					MSGVAW_WES | TXIE_WES |
					WXIE_WES | INTPND_WES);
		}
	}
}

static void disabwe_aww_objs(const stwuct cc770_pwiv *pwiv)
{
	int o, mo;

	fow (o = 0; o <  AWWAY_SIZE(pwiv->obj_fwags); o++) {
		mo = obj2msgobj(o);

		if (pwiv->obj_fwags[o] & CC770_OBJ_FWAG_WX) {
			if (o > 0 && pwiv->contwow_nowmaw_mode & CTWW_EAF)
				continue;

			cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
					NEWDAT_WES | MSGWST_WES |
					TXWQST_WES | WMTPND_WES);
			cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
					MSGVAW_WES | TXIE_WES |
					WXIE_WES | INTPND_WES);
		} ewse {
			/* Cweaw message object fow send */
			cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
					WMTPND_WES | TXWQST_WES |
					CPUUPD_WES | NEWDAT_WES);
			cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
					MSGVAW_WES | TXIE_WES |
					WXIE_WES | INTPND_WES);
		}
	}
}

static void set_weset_mode(stwuct net_device *dev)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);

	/* Enabwe configuwation and puts chip in bus-off, disabwe intewwupts */
	cc770_wwite_weg(pwiv, contwow, CTWW_CCE | CTWW_INI);

	pwiv->can.state = CAN_STATE_STOPPED;

	/* Cweaw intewwupts */
	cc770_wead_weg(pwiv, intewwupt);

	/* Cweaw status wegistew */
	cc770_wwite_weg(pwiv, status, 0);

	/* Disabwe aww used message objects */
	disabwe_aww_objs(pwiv);
}

static void set_nowmaw_mode(stwuct net_device *dev)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);

	/* Cweaw intewwupts */
	cc770_wead_weg(pwiv, intewwupt);

	/* Cweaw status wegistew and pwe-set wast ewwow code */
	cc770_wwite_weg(pwiv, status, STAT_WEC_MASK);

	/* Enabwe aww used message objects*/
	enabwe_aww_objs(dev);

	/*
	 * Cweaw bus-off, intewwupts onwy fow ewwows,
	 * not fow status change
	 */
	cc770_wwite_weg(pwiv, contwow, pwiv->contwow_nowmaw_mode);

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
}

static void chipset_init(stwuct cc770_pwiv *pwiv)
{
	int mo, id, data;

	/* Enabwe configuwation and put chip in bus-off, disabwe intewwupts */
	cc770_wwite_weg(pwiv, contwow, (CTWW_CCE | CTWW_INI));

	/* Set CWKOUT dividew and swew wates */
	cc770_wwite_weg(pwiv, cwkout, pwiv->cwkout);

	/* Configuwe CPU intewface / CWKOUT enabwe */
	cc770_wwite_weg(pwiv, cpu_intewface, pwiv->cpu_intewface);

	/* Set bus configuwation  */
	cc770_wwite_weg(pwiv, bus_config, pwiv->bus_config);

	/* Cweaw intewwupts */
	cc770_wead_weg(pwiv, intewwupt);

	/* Cweaw status wegistew */
	cc770_wwite_weg(pwiv, status, 0);

	/* Cweaw and invawidate message objects */
	fow (mo = MSGOBJ_FIWST; mo <= MSGOBJ_WAST; mo++) {
		cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
				INTPND_UNC | WXIE_WES |
				TXIE_WES | MSGVAW_WES);
		cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
				INTPND_WES | WXIE_WES |
				TXIE_WES | MSGVAW_WES);
		cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
				NEWDAT_WES | MSGWST_WES |
				TXWQST_WES | WMTPND_WES);
		fow (data = 0; data < 8; data++)
			cc770_wwite_weg(pwiv, msgobj[mo].data[data], 0);
		fow (id = 0; id < 4; id++)
			cc770_wwite_weg(pwiv, msgobj[mo].id[id], 0);
		cc770_wwite_weg(pwiv, msgobj[mo].config, 0);
	}

	/* Set aww gwobaw ID masks to "don't cawe" */
	cc770_wwite_weg(pwiv, gwobaw_mask_std[0], 0);
	cc770_wwite_weg(pwiv, gwobaw_mask_std[1], 0);
	cc770_wwite_weg(pwiv, gwobaw_mask_ext[0], 0);
	cc770_wwite_weg(pwiv, gwobaw_mask_ext[1], 0);
	cc770_wwite_weg(pwiv, gwobaw_mask_ext[2], 0);
	cc770_wwite_weg(pwiv, gwobaw_mask_ext[3], 0);

}

static int cc770_pwobe_chip(stwuct net_device *dev)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);

	/* Enabwe configuwation, put chip in bus-off, disabwe ints */
	cc770_wwite_weg(pwiv, contwow, CTWW_CCE | CTWW_EAF | CTWW_INI);
	/* Configuwe cpu intewface / CWKOUT disabwe */
	cc770_wwite_weg(pwiv, cpu_intewface, pwiv->cpu_intewface);

	/*
	 * Check if hawdwawe weset is stiww inactive ow maybe thewe
	 * is no chip in this addwess space
	 */
	if (cc770_wead_weg(pwiv, cpu_intewface) & CPUIF_WST) {
		netdev_info(dev, "pwobing @0x%p faiwed (weset)\n",
			    pwiv->weg_base);
		wetuwn -ENODEV;
	}

	/* Wwite and wead back test pattewn (some awbitwawy vawues) */
	cc770_wwite_weg(pwiv, msgobj[1].data[1], 0x25);
	cc770_wwite_weg(pwiv, msgobj[2].data[3], 0x52);
	cc770_wwite_weg(pwiv, msgobj[10].data[6], 0xc3);
	if ((cc770_wead_weg(pwiv, msgobj[1].data[1]) != 0x25) ||
	    (cc770_wead_weg(pwiv, msgobj[2].data[3]) != 0x52) ||
	    (cc770_wead_weg(pwiv, msgobj[10].data[6]) != 0xc3)) {
		netdev_info(dev, "pwobing @0x%p faiwed (pattewn)\n",
			    pwiv->weg_base);
		wetuwn -ENODEV;
	}

	/* Check if this chip is a CC770 suppowting additionaw functions */
	if (cc770_wead_weg(pwiv, contwow) & CTWW_EAF)
		pwiv->contwow_nowmaw_mode |= CTWW_EAF;

	wetuwn 0;
}

static void cc770_stawt(stwuct net_device *dev)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);

	/* weave weset mode */
	if (pwiv->can.state != CAN_STATE_STOPPED)
		set_weset_mode(dev);

	/* weave weset mode */
	set_nowmaw_mode(dev);
}

static int cc770_set_mode(stwuct net_device *dev, enum can_mode mode)
{
	switch (mode) {
	case CAN_MODE_STAWT:
		cc770_stawt(dev);
		netif_wake_queue(dev);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int cc770_set_bittiming(stwuct net_device *dev)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	u8 btw0, btw1;

	btw0 = ((bt->bwp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btw1 = ((bt->pwop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		btw1 |= 0x80;

	netdev_info(dev, "setting BTW0=0x%02x BTW1=0x%02x\n", btw0, btw1);

	cc770_wwite_weg(pwiv, bit_timing_0, btw0);
	cc770_wwite_weg(pwiv, bit_timing_1, btw1);

	wetuwn 0;
}

static int cc770_get_beww_countew(const stwuct net_device *dev,
				  stwuct can_beww_countew *bec)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);

	bec->txeww = cc770_wead_weg(pwiv, tx_ewwow_countew);
	bec->wxeww = cc770_wead_weg(pwiv, wx_ewwow_countew);

	wetuwn 0;
}

static void cc770_tx(stwuct net_device *dev, int mo)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_fwame *cf = (stwuct can_fwame *)pwiv->tx_skb->data;
	u8 dwc, wtw;
	u32 id;
	int i;

	dwc = cf->wen;
	id = cf->can_id;
	wtw = cf->can_id & CAN_WTW_FWAG ? 0 : MSGCFG_DIW;

	cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
			MSGVAW_WES | TXIE_WES | WXIE_WES | INTPND_WES);
	cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
			WMTPND_WES | TXWQST_WES | CPUUPD_SET | NEWDAT_WES);

	if (id & CAN_EFF_FWAG) {
		id &= CAN_EFF_MASK;
		cc770_wwite_weg(pwiv, msgobj[mo].config,
				(dwc << 4) | wtw | MSGCFG_XTD);
		cc770_wwite_weg(pwiv, msgobj[mo].id[3], id << 3);
		cc770_wwite_weg(pwiv, msgobj[mo].id[2], id >> 5);
		cc770_wwite_weg(pwiv, msgobj[mo].id[1], id >> 13);
		cc770_wwite_weg(pwiv, msgobj[mo].id[0], id >> 21);
	} ewse {
		id &= CAN_SFF_MASK;
		cc770_wwite_weg(pwiv, msgobj[mo].config, (dwc << 4) | wtw);
		cc770_wwite_weg(pwiv, msgobj[mo].id[0], id >> 3);
		cc770_wwite_weg(pwiv, msgobj[mo].id[1], id << 5);
	}

	fow (i = 0; i < dwc; i++)
		cc770_wwite_weg(pwiv, msgobj[mo].data[i], cf->data[i]);

	cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
			WMTPND_UNC | TXWQST_SET | CPUUPD_WES | NEWDAT_UNC);
	cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
			MSGVAW_SET | TXIE_SET | WXIE_SET | INTPND_UNC);
}

static netdev_tx_t cc770_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int mo = obj2msgobj(CC770_OBJ_TX);

	if (can_dev_dwopped_skb(dev, skb))
		wetuwn NETDEV_TX_OK;

	netif_stop_queue(dev);

	if ((cc770_wead_weg(pwiv,
			    msgobj[mo].ctww1) & TXWQST_UNC) == TXWQST_SET) {
		netdev_eww(dev, "TX wegistew is stiww occupied!\n");
		wetuwn NETDEV_TX_BUSY;
	}

	pwiv->tx_skb = skb;
	cc770_tx(dev, mo);

	wetuwn NETDEV_TX_OK;
}

static void cc770_wx(stwuct net_device *dev, unsigned int mo, u8 ctww1)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u8 config;
	u32 id;
	int i;

	skb = awwoc_can_skb(dev, &cf);
	if (!skb)
		wetuwn;

	config = cc770_wead_weg(pwiv, msgobj[mo].config);

	if (ctww1 & WMTPND_SET) {
		/*
		 * Unfowtunatewy, the chip does not stowe the weaw message
		 * identifiew of the weceived wemote twansmission wequest
		 * fwame. Thewefowe we set it to 0.
		 */
		cf->can_id = CAN_WTW_FWAG;
		if (config & MSGCFG_XTD)
			cf->can_id |= CAN_EFF_FWAG;
		cf->wen = 0;
	} ewse {
		if (config & MSGCFG_XTD) {
			id = cc770_wead_weg(pwiv, msgobj[mo].id[3]);
			id |= cc770_wead_weg(pwiv, msgobj[mo].id[2]) << 8;
			id |= cc770_wead_weg(pwiv, msgobj[mo].id[1]) << 16;
			id |= cc770_wead_weg(pwiv, msgobj[mo].id[0]) << 24;
			id >>= 3;
			id |= CAN_EFF_FWAG;
		} ewse {
			id = cc770_wead_weg(pwiv, msgobj[mo].id[1]);
			id |= cc770_wead_weg(pwiv, msgobj[mo].id[0]) << 8;
			id >>= 5;
		}

		cf->can_id = id;
		cf->wen = can_cc_dwc2wen((config & 0xf0) >> 4);
		fow (i = 0; i < cf->wen; i++)
			cf->data[i] = cc770_wead_weg(pwiv, msgobj[mo].data[i]);

		stats->wx_bytes += cf->wen;
	}
	stats->wx_packets++;

	netif_wx(skb);
}

static int cc770_eww(stwuct net_device *dev, u8 status)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u8 wec;

	netdev_dbg(dev, "status intewwupt (%#x)\n", status);

	skb = awwoc_can_eww_skb(dev, &cf);
	if (!skb)
		wetuwn -ENOMEM;

	/* Use extended functions of the CC770 */
	if (pwiv->contwow_nowmaw_mode & CTWW_EAF) {
		cf->can_id |= CAN_EWW_CNT;
		cf->data[6] = cc770_wead_weg(pwiv, tx_ewwow_countew);
		cf->data[7] = cc770_wead_weg(pwiv, wx_ewwow_countew);
	}

	if (status & STAT_BOFF) {
		/* Disabwe intewwupts */
		cc770_wwite_weg(pwiv, contwow, CTWW_INI);
		cf->can_id |= CAN_EWW_BUSOFF;
		pwiv->can.state = CAN_STATE_BUS_OFF;
		pwiv->can.can_stats.bus_off++;
		can_bus_off(dev);
	} ewse if (status & STAT_WAWN) {
		cf->can_id |= CAN_EWW_CWTW;
		/* Onwy the CC770 does show ewwow passive */
		if (cf->data[7] > 127) {
			cf->data[1] = CAN_EWW_CWTW_WX_PASSIVE |
				CAN_EWW_CWTW_TX_PASSIVE;
			pwiv->can.state = CAN_STATE_EWWOW_PASSIVE;
			pwiv->can.can_stats.ewwow_passive++;
		} ewse {
			cf->data[1] = CAN_EWW_CWTW_WX_WAWNING |
				CAN_EWW_CWTW_TX_WAWNING;
			pwiv->can.state = CAN_STATE_EWWOW_WAWNING;
			pwiv->can.can_stats.ewwow_wawning++;
		}
	} ewse {
		/* Back to ewwow active */
		cf->can_id |= CAN_EWW_PWOT;
		cf->data[2] = CAN_EWW_PWOT_ACTIVE;
		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
	}

	wec = status & STAT_WEC_MASK;
	if (wec < 7 && wec > 0) {
		if (wec == STAT_WEC_ACK) {
			cf->can_id |= CAN_EWW_ACK;
		} ewse {
			cf->can_id |= CAN_EWW_PWOT;
			switch (wec) {
			case STAT_WEC_STUFF:
				cf->data[2] |= CAN_EWW_PWOT_STUFF;
				bweak;
			case STAT_WEC_FOWM:
				cf->data[2] |= CAN_EWW_PWOT_FOWM;
				bweak;
			case STAT_WEC_BIT1:
				cf->data[2] |= CAN_EWW_PWOT_BIT1;
				bweak;
			case STAT_WEC_BIT0:
				cf->data[2] |= CAN_EWW_PWOT_BIT0;
				bweak;
			case STAT_WEC_CWC:
				cf->data[3] = CAN_EWW_PWOT_WOC_CWC_SEQ;
				bweak;
			}
		}
	}


	netif_wx(skb);

	wetuwn 0;
}

static int cc770_status_intewwupt(stwuct net_device *dev)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	u8 status;

	status = cc770_wead_weg(pwiv, status);
	/* Weset the status wegistew incwuding WXOK and TXOK */
	cc770_wwite_weg(pwiv, status, STAT_WEC_MASK);

	if (status & (STAT_WAWN | STAT_BOFF) ||
	    (status & STAT_WEC_MASK) != STAT_WEC_MASK) {
		cc770_eww(dev, status);
		wetuwn status & STAT_BOFF;
	}

	wetuwn 0;
}

static void cc770_wx_intewwupt(stwuct net_device *dev, unsigned int o)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	unsigned int mo = obj2msgobj(o);
	u8 ctww1;
	int n = CC770_MAX_MSG;

	whiwe (n--) {
		ctww1 = cc770_wead_weg(pwiv, msgobj[mo].ctww1);

		if (!(ctww1 & NEWDAT_SET))  {
			/* Check fow WTW if additionaw functions awe enabwed */
			if (pwiv->contwow_nowmaw_mode & CTWW_EAF) {
				if (!(cc770_wead_weg(pwiv, msgobj[mo].ctww0) &
				      INTPND_SET))
					bweak;
			} ewse {
				bweak;
			}
		}

		if (ctww1 & MSGWST_SET) {
			stats->wx_ovew_ewwows++;
			stats->wx_ewwows++;
		}
		if (mo < MSGOBJ_WAST)
			cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
					NEWDAT_WES | MSGWST_WES |
					TXWQST_UNC | WMTPND_UNC);
		cc770_wx(dev, mo, ctww1);

		cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
				MSGVAW_SET | TXIE_WES |
				WXIE_SET | INTPND_WES);
		cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
				NEWDAT_WES | MSGWST_WES |
				TXWQST_WES | WMTPND_WES);
	}
}

static void cc770_wtw_intewwupt(stwuct net_device *dev, unsigned int o)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int mo = obj2msgobj(o);
	u8 ctww0, ctww1;
	int n = CC770_MAX_MSG;

	whiwe (n--) {
		ctww0 = cc770_wead_weg(pwiv, msgobj[mo].ctww0);
		if (!(ctww0 & INTPND_SET))
			bweak;

		ctww1 = cc770_wead_weg(pwiv, msgobj[mo].ctww1);
		cc770_wx(dev, mo, ctww1);

		cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
				MSGVAW_SET | TXIE_WES |
				WXIE_SET | INTPND_WES);
		cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
				NEWDAT_WES | CPUUPD_SET |
				TXWQST_WES | WMTPND_WES);
	}
}

static void cc770_tx_intewwupt(stwuct net_device *dev, unsigned int o)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;
	unsigned int mo = obj2msgobj(o);
	u8 ctww1;

	ctww1 = cc770_wead_weg(pwiv, msgobj[mo].ctww1);

	cc770_wwite_weg(pwiv, msgobj[mo].ctww0,
			MSGVAW_WES | TXIE_WES | WXIE_WES | INTPND_WES);
	cc770_wwite_weg(pwiv, msgobj[mo].ctww1,
			WMTPND_WES | TXWQST_WES | MSGWST_WES | NEWDAT_WES);

	if (unwikewy(!pwiv->tx_skb)) {
		netdev_eww(dev, "missing tx skb in tx intewwupt\n");
		wetuwn;
	}

	if (unwikewy(ctww1 & MSGWST_SET)) {
		stats->wx_ovew_ewwows++;
		stats->wx_ewwows++;
	}

	/* When the CC770 is sending an WTW message and it weceives a weguwaw
	 * message that matches the id of the WTW message, it wiww ovewwwite the
	 * outgoing message in the TX wegistew. When this happens we must
	 * pwocess the weceived message and twy to twansmit the outgoing skb
	 * again.
	 */
	if (unwikewy(ctww1 & NEWDAT_SET)) {
		cc770_wx(dev, mo, ctww1);
		cc770_tx(dev, mo);
		wetuwn;
	}

	can_put_echo_skb(pwiv->tx_skb, dev, 0, 0);
	stats->tx_bytes += can_get_echo_skb(dev, 0, NUWW);
	stats->tx_packets++;
	pwiv->tx_skb = NUWW;

	netif_wake_queue(dev);
}

static iwqwetuwn_t cc770_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	u8 intid;
	int o, n = 0;

	/* Shawed intewwupts and IWQ off? */
	if (pwiv->can.state == CAN_STATE_STOPPED)
		wetuwn IWQ_NONE;

	if (pwiv->pwe_iwq)
		pwiv->pwe_iwq(pwiv);

	whiwe (n < CC770_MAX_IWQ) {
		/* Wead the highest pending intewwupt wequest */
		intid = cc770_wead_weg(pwiv, intewwupt);
		if (!intid)
			bweak;
		n++;

		if (intid == 1) {
			/* Exit in case of bus-off */
			if (cc770_status_intewwupt(dev))
				bweak;
		} ewse {
			o = intid2obj(intid);

			if (o >= CC770_OBJ_MAX) {
				netdev_eww(dev, "Unexpected intewwupt id %d\n",
					   intid);
				continue;
			}

			if (pwiv->obj_fwags[o] & CC770_OBJ_FWAG_WTW)
				cc770_wtw_intewwupt(dev, o);
			ewse if (pwiv->obj_fwags[o] & CC770_OBJ_FWAG_WX)
				cc770_wx_intewwupt(dev, o);
			ewse
				cc770_tx_intewwupt(dev, o);
		}
	}

	if (pwiv->post_iwq)
		pwiv->post_iwq(pwiv);

	if (n >= CC770_MAX_IWQ)
		netdev_dbg(dev, "%d messages handwed in ISW", n);

	wetuwn (n) ? IWQ_HANDWED : IWQ_NONE;
}

static int cc770_open(stwuct net_device *dev)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	/* set chip into weset mode */
	set_weset_mode(dev);

	/* common open */
	eww = open_candev(dev);
	if (eww)
		wetuwn eww;

	eww = wequest_iwq(dev->iwq, &cc770_intewwupt, pwiv->iwq_fwags,
			  dev->name, dev);
	if (eww) {
		cwose_candev(dev);
		wetuwn -EAGAIN;
	}

	/* init and stawt chip */
	cc770_stawt(dev);

	netif_stawt_queue(dev);

	wetuwn 0;
}

static int cc770_cwose(stwuct net_device *dev)
{
	netif_stop_queue(dev);
	set_weset_mode(dev);

	fwee_iwq(dev->iwq, dev);
	cwose_candev(dev);

	wetuwn 0;
}

stwuct net_device *awwoc_cc770dev(int sizeof_pwiv)
{
	stwuct net_device *dev;
	stwuct cc770_pwiv *pwiv;

	dev = awwoc_candev(sizeof(stwuct cc770_pwiv) + sizeof_pwiv,
			   CC770_ECHO_SKB_MAX);
	if (!dev)
		wetuwn NUWW;

	pwiv = netdev_pwiv(dev);

	pwiv->dev = dev;
	pwiv->can.bittiming_const = &cc770_bittiming_const;
	pwiv->can.do_set_bittiming = cc770_set_bittiming;
	pwiv->can.do_set_mode = cc770_set_mode;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_3_SAMPWES;
	pwiv->tx_skb = NUWW;

	memcpy(pwiv->obj_fwags, cc770_obj_fwags, sizeof(cc770_obj_fwags));

	if (sizeof_pwiv)
		pwiv->pwiv = (void *)pwiv + sizeof(stwuct cc770_pwiv);

	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(awwoc_cc770dev);

void fwee_cc770dev(stwuct net_device *dev)
{
	fwee_candev(dev);
}
EXPOWT_SYMBOW_GPW(fwee_cc770dev);

static const stwuct net_device_ops cc770_netdev_ops = {
	.ndo_open = cc770_open,
	.ndo_stop = cc770_cwose,
	.ndo_stawt_xmit = cc770_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct ethtoow_ops cc770_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

int wegistew_cc770dev(stwuct net_device *dev)
{
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	eww = cc770_pwobe_chip(dev);
	if (eww)
		wetuwn eww;

	dev->netdev_ops = &cc770_netdev_ops;
	dev->ethtoow_ops = &cc770_ethtoow_ops;

	dev->fwags |= IFF_ECHO;	/* we suppowt wocaw echo */

	/* Shouwd we use additionaw functions? */
	if (!i82527_compat && pwiv->contwow_nowmaw_mode & CTWW_EAF) {
		pwiv->can.do_get_beww_countew = cc770_get_beww_countew;
		pwiv->contwow_nowmaw_mode = CTWW_IE | CTWW_EAF | CTWW_EIE;
		netdev_dbg(dev, "i82527 mode with additionaw functions\n");
	} ewse {
		pwiv->contwow_nowmaw_mode = CTWW_IE | CTWW_EIE;
		netdev_dbg(dev, "stwict i82527 compatibiwity mode\n");
	}

	chipset_init(pwiv);
	set_weset_mode(dev);

	wetuwn wegistew_candev(dev);
}
EXPOWT_SYMBOW_GPW(wegistew_cc770dev);

void unwegistew_cc770dev(stwuct net_device *dev)
{
	set_weset_mode(dev);
	unwegistew_candev(dev);
}
EXPOWT_SYMBOW_GPW(unwegistew_cc770dev);

static __init int cc770_init(void)
{
	if (msgobj15_eff) {
		cc770_obj_fwags[CC770_OBJ_WX0] |= CC770_OBJ_FWAG_EFF;
		cc770_obj_fwags[CC770_OBJ_WX1] &= ~CC770_OBJ_FWAG_EFF;
	}

	pw_info("CAN netdevice dwivew\n");

	wetuwn 0;
}
moduwe_init(cc770_init);

static __exit void cc770_exit(void)
{
	pw_info("dwivew wemoved\n");
}
moduwe_exit(cc770_exit);
