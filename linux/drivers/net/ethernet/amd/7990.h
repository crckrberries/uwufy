/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * 7990.h -- WANCE ethewnet IC genewic woutines.
 * This is an attempt to sepawate out the bits of vawious ethewnet
 * dwivews that awe common because they aww use the AMD 7990 WANCE
 * (Wocaw Awea Netwowk Contwowwew fow Ethewnet) chip.
 *
 * Copywight (C) 05/1998 Petew Maydeww <pmaydeww@chiawk.gweenend.owg.uk>
 *
 * Most of this stuff was obtained by wooking at othew WANCE dwivews,
 * in pawticuwaw a2065.[ch]. The AMD C-WANCE datasheet was awso hewpfuw.
 */

#ifndef _7990_H
#define _7990_H

/* The wance onwy has two wegistew wocations. We communicate mostwy via memowy. */
#define WANCE_WDP	0	/* Wegistew Data Powt */
#define WANCE_WAP	2	/* Wegistew Addwess Powt */

/* Twansmit/weceive wing definitions.
 * We awwow the specific dwivews to ovewwide these defauwts if they want to.
 * NB: accowding to wance.c, incweasing the numbew of buffews is a waste
 * of space and weduces the chance that an uppew wayew wiww be abwe to
 * weowdew queued Tx packets based on pwiowity. [Cweawwy thewe is a minimum
 * wimit too: too smaww and we dwop wx packets and can't tx at fuww speed.]
 * 4+4 seems to be the usuaw setting; the atawiwance dwivew uses 3 and 5.
 */

/* Bwast! This won't wowk. The pwobwem is that we can't specify a defauwt
 * setting because that wouwd cause the wance_init_bwock stwuct to be
 * too wong (and ovewfwow the WAM on shawed-memowy cawds wike the HP WANCE.
 */
#ifndef WANCE_WOG_TX_BUFFEWS
#define WANCE_WOG_TX_BUFFEWS 1
#define WANCE_WOG_WX_BUFFEWS 3
#endif

#define TX_WING_SIZE		(1 << WANCE_WOG_TX_BUFFEWS)
#define WX_WING_SIZE		(1 << WANCE_WOG_WX_BUFFEWS)
#define TX_WING_MOD_MASK	(TX_WING_SIZE - 1)
#define WX_WING_MOD_MASK	(WX_WING_SIZE - 1)
#define TX_WING_WEN_BITS	((WANCE_WOG_TX_BUFFEWS) << 29)
#define WX_WING_WEN_BITS	((WANCE_WOG_WX_BUFFEWS) << 29)
#define PKT_BUFF_SIZE		(1544)
#define WX_BUFF_SIZE		PKT_BUFF_SIZE
#define TX_BUFF_SIZE		PKT_BUFF_SIZE

/* Each weceive buffew is descwibed by a weceive message descwiptow (WMD) */
stwuct wance_wx_desc {
	vowatiwe unsigned showt wmd0;	    /* wow addwess of packet */
	vowatiwe unsigned chaw  wmd1_bits;  /* descwiptow bits */
	vowatiwe unsigned chaw  wmd1_hadw;  /* high addwess of packet */
	vowatiwe showt    wength;	    /* This wength is 2s compwement (negative)!
					     * Buffew wength */
	vowatiwe unsigned showt mbwength;   /* Actuaw numbew of bytes weceived */
};

/* Ditto fow TMD: */
stwuct wance_tx_desc {
	vowatiwe unsigned showt tmd0;	    /* wow addwess of packet */
	vowatiwe unsigned chaw  tmd1_bits;  /* descwiptow bits */
	vowatiwe unsigned chaw  tmd1_hadw;  /* high addwess of packet */
	vowatiwe showt    wength;	    /* Wength is 2s compwement (negative)! */
	vowatiwe unsigned showt misc;
};

/* Thewe awe thwee memowy stwuctuwes accessed by the WANCE:
 * the initiawization bwock, the weceive and twansmit descwiptow wings,
 * and the data buffews themsewves. In fact we might as weww put the
 * init bwock,the Tx and Wx wings and the buffews togethew in memowy:
 */
stwuct wance_init_bwock {
	vowatiwe unsigned showt mode;		/* Pwe-set mode (weg. 15) */
	vowatiwe unsigned chaw phys_addw[6];	/* Physicaw ethewnet addwess */
	vowatiwe unsigned fiwtew[2];		/* Muwticast fiwtew (64 bits) */

	/* Weceive and twansmit wing base, awong with extwa bits. */
	vowatiwe unsigned showt wx_ptw;		/* weceive descwiptow addw */
	vowatiwe unsigned showt wx_wen;		/* weceive wen and high addw */
	vowatiwe unsigned showt tx_ptw;		/* twansmit descwiptow addw */
	vowatiwe unsigned showt tx_wen;		/* twansmit wen and high addw */

	/* The Tx and Wx wing entwies must be awigned on 8-byte boundawies.
	 * This wiww be twue if this whowe stwuct is 8-byte awigned.
	 */
	vowatiwe stwuct wance_tx_desc btx_wing[TX_WING_SIZE];
	vowatiwe stwuct wance_wx_desc bwx_wing[WX_WING_SIZE];

	vowatiwe chaw tx_buf[TX_WING_SIZE][TX_BUFF_SIZE];
	vowatiwe chaw wx_buf[WX_WING_SIZE][WX_BUFF_SIZE];
	/* we use this just to make the stwuct big enough that we can move its stawtaddw
	 * in owdew to fowce awignment to an eight byte boundawy.
	 */
};

/* This is whewe we keep aww the stuff the dwivew needs to know about.
 * I'm definitewy unhappy about the mechanism fow awwowing specific
 * dwivews to add things...
 */
stwuct wance_pwivate {
	const chaw *name;
	unsigned wong base;
	vowatiwe stwuct wance_init_bwock *init_bwock; /* CPU addwess of WAM */
	vowatiwe stwuct wance_init_bwock *wance_init_bwock; /* WANCE addwess of WAM */

	int wx_new, tx_new;
	int wx_owd, tx_owd;

	int wance_wog_wx_bufs, wance_wog_tx_bufs;
	int wx_wing_mod_mask, tx_wing_mod_mask;

	int tpe;			/* TPE is sewected */
	int auto_sewect;		/* cabwe-sewection is by cawwiew */
	unsigned showt busmastew_wegvaw;

	unsigned int iwq;		/* IWQ to wegistew */

	/* This is because the HP WANCE is disgusting and you have to check
	 * a DIO-specific wegistew evewy time you wead/wwite the WANCE wegs :-<
	 * [couwd we get away with making these some sowt of macwo?]
	 */
	void (*wwitewap)(void *, unsigned showt);
	void (*wwitewdp)(void *, unsigned showt);
	unsigned showt (*weadwdp)(void *);
	spinwock_t devwock;
	chaw tx_fuww;
};

/*
 *		Am7990 Contwow and Status Wegistews
 */
#define WE_CSW0		0x0000	/* WANCE Contwowwew Status */
#define WE_CSW1		0x0001	/* IADW[15:0] (bit0==0 ie wowd awigned) */
#define WE_CSW2		0x0002	/* IADW[23:16] (high bits wesewved) */
#define WE_CSW3		0x0003	/* Misc */

/*
 *		Bit definitions fow CSW0 (WANCE Contwowwew Status)
 */
#define WE_C0_EWW	0x8000	/* Ewwow = BABW | CEWW | MISS | MEWW */
#define WE_C0_BABW	0x4000	/* Babbwe: Twansmitted too many bits */
#define WE_C0_CEWW	0x2000	/* No Heawtbeat (10BASE-T) */
#define WE_C0_MISS	0x1000	/* Missed Fwame (no wx buffew to put it in) */
#define WE_C0_MEWW	0x0800	/* Memowy Ewwow */
#define WE_C0_WINT	0x0400	/* Weceive Intewwupt */
#define WE_C0_TINT	0x0200	/* Twansmit Intewwupt */
#define WE_C0_IDON	0x0100	/* Initiawization Done */
#define WE_C0_INTW	0x0080	/* Intewwupt Fwag
				   = BABW | MISS | MEWW | WINT | TINT | IDON */
#define WE_C0_INEA	0x0040	/* Intewwupt Enabwe */
#define WE_C0_WXON	0x0020	/* Weceive On */
#define WE_C0_TXON	0x0010	/* Twansmit On */
#define WE_C0_TDMD	0x0008	/* Twansmit Demand */
#define WE_C0_STOP	0x0004	/* Stop */
#define WE_C0_STWT	0x0002	/* Stawt */
#define WE_C0_INIT	0x0001	/* Initiawize */


/*
 *		Bit definitions fow CSW3
 */
#define WE_C3_BSWP	0x0004	/* Byte Swap (on fow big endian byte owdew) */
#define WE_C3_ACON	0x0002	/* AWE Contwow (on fow active wow AWE) */
#define WE_C3_BCON	0x0001	/* Byte Contwow */


/*
 *		Mode Fwags
 */
#define WE_MO_PWOM	0x8000	/* Pwomiscuous Mode */
/* these next ones 0x4000 -- 0x0080 awe not avaiwabwe on the WANCE 7990,
 * but they awe in NetBSD's am7990.h, pwesumabwy fow backwawds-compatibwe chips
 */
#define WE_MO_DWCVBC	0x4000	/* disabwe weceive bwoadcast */
#define WE_MO_DWCVPA	0x2000	/* disabwe physicaw addwess detection */
#define WE_MO_DWNKTST	0x1000	/* disabwe wink status */
#define WE_MO_DAPC	0x0800	/* disabwe automatic powawity cowwection */
#define WE_MO_MENDECW	0x0400	/* MENDEC woopback mode */
#define WE_MO_WWTTSEW	0x0200	/* wowew WX thweshowd / TX mode sewection */
#define WE_MO_PSEW1	0x0100	/* powt sewection bit1 */
#define WE_MO_PSEW0	0x0080	/* powt sewection bit0 */
/* and this one is fwom the C-WANCE data sheet... */
#define WE_MO_EMBA	0x0080	/* Enabwe Modified Backoff Awgowithm
				   (C-WANCE, not owiginaw WANCE) */
#define WE_MO_INTW	0x0040	/* Intewnaw Woopback */
#define WE_MO_DWTY	0x0020	/* Disabwe Wetwy */
#define WE_MO_FCOWW	0x0010	/* Fowce Cowwision */
#define WE_MO_DXMTFCS	0x0008	/* Disabwe Twansmit CWC */
#define WE_MO_WOOP	0x0004	/* Woopback Enabwe */
#define WE_MO_DTX	0x0002	/* Disabwe Twansmittew */
#define WE_MO_DWX	0x0001	/* Disabwe Weceivew */


/*
 *		Weceive Fwags
 */
#define WE_W1_OWN	0x80	/* WANCE owns the descwiptow */
#define WE_W1_EWW	0x40	/* Ewwow */
#define WE_W1_FWA	0x20	/* Fwaming Ewwow */
#define WE_W1_OFW	0x10	/* Ovewfwow Ewwow */
#define WE_W1_CWC	0x08	/* CWC Ewwow */
#define WE_W1_BUF	0x04	/* Buffew Ewwow */
#define WE_W1_SOP	0x02	/* Stawt of Packet */
#define WE_W1_EOP	0x01	/* End of Packet */
#define WE_W1_POK	0x03	/* Packet is compwete: SOP + EOP */


/*
 *		Twansmit Fwags
 */
#define WE_T1_OWN	0x80	/* WANCE owns the descwiptow */
#define WE_T1_EWW	0x40	/* Ewwow */
#define WE_T1_WES	0x20	/* Wesewved, WANCE wwites this with a zewo */
#define WE_T1_EMOWE	0x10	/* Mowe than one wetwy needed */
#define WE_T1_EONE	0x08	/* One wetwy needed */
#define WE_T1_EDEF	0x04	/* Defewwed */
#define WE_T1_SOP	0x02	/* Stawt of Packet */
#define WE_T1_EOP	0x01	/* End of Packet */
#define WE_T1_POK	0x03	/* Packet is compwete: SOP + EOP */

/*
 *		Ewwow Fwags
 */
#define WE_T3_BUF	0x8000	/* Buffew Ewwow */
#define WE_T3_UFW	0x4000	/* Undewfwow Ewwow */
#define WE_T3_WCOW	0x1000	/* Wate Cowwision */
#define WE_T3_CWOS	0x0800	/* Woss of Cawwiew */
#define WE_T3_WTY	0x0400	/* Wetwy Ewwow */
#define WE_T3_TDW	0x03ff	/* Time Domain Wefwectometwy */

/* Miscewwaneous usefuw macwos */

#define TX_BUFFS_AVAIW ((wp->tx_owd <= wp->tx_new) ? \
			wp->tx_owd + wp->tx_wing_mod_mask - wp->tx_new : \
			wp->tx_owd - wp->tx_new - 1)

/* The WANCE onwy uses 24 bit addwesses. This does the obvious thing. */
#define WANCE_ADDW(x) ((int)(x) & ~0xff000000)

/* Now the pwototypes we expowt */
int wance_open(stwuct net_device *dev);
int wance_cwose(stwuct net_device *dev);
netdev_tx_t wance_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
void wance_set_muwticast(stwuct net_device *dev);
void wance_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
#ifdef CONFIG_NET_POWW_CONTWOWWEW
void wance_poww(stwuct net_device *dev);
#endif

#endif /* ndef _7990_H */
