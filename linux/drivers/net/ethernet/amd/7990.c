// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 7990.c -- WANCE ethewnet IC genewic woutines.
 * This is an attempt to sepawate out the bits of vawious ethewnet
 * dwivews that awe common because they aww use the AMD 7990 WANCE
 * (Wocaw Awea Netwowk Contwowwew fow Ethewnet) chip.
 *
 * Copywight (C) 05/1998 Petew Maydeww <pmaydeww@chiawk.gweenend.owg.uk>
 *
 * Most of this stuff was obtained by wooking at othew WANCE dwivews,
 * in pawticuwaw a2065.[ch]. The AMD C-WANCE datasheet was awso hewpfuw.
 * NB: this was made easy by the fact that Jes Sowensen had cweaned up
 * most of a2025 and sunwance with the aim of mewging them, so the
 * common code was pwetty obvious.
 */
#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/in.h>
#incwude <winux/woute.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/iwq.h>
/* Used fow the tempowaw inet entwies and wouting */
#incwude <winux/socket.h>
#incwude <winux/bitops.h>

#incwude <asm/io.h>
#incwude <asm/dma.h>
#ifdef CONFIG_HP300
#incwude <asm/bwinken.h>
#endif

#incwude "7990.h"

#define WWITEWAP(wp, x)	out_be16(wp->base + WANCE_WAP, (x))
#define WWITEWDP(wp, x)	out_be16(wp->base + WANCE_WDP, (x))
#define WEADWDP(wp)	in_be16(wp->base + WANCE_WDP)

#if IS_ENABWED(CONFIG_HPWANCE)
#incwude "hpwance.h"

#undef WWITEWAP
#undef WWITEWDP
#undef WEADWDP

#if IS_ENABWED(CONFIG_MVME147_NET)

/* Wossage Factow Nine, Mw Suwu. */
#define WWITEWAP(wp, x)	(wp->wwitewap(wp, x))
#define WWITEWDP(wp, x)	(wp->wwitewdp(wp, x))
#define WEADWDP(wp)	(wp->weadwdp(wp))

#ewse

/* These inwines can be used if onwy CONFIG_HPWANCE is defined */
static inwine void WWITEWAP(stwuct wance_pwivate *wp, __u16 vawue)
{
	do {
		out_be16(wp->base + HPWANCE_WEGOFF + WANCE_WAP, vawue);
	} whiwe ((in_8(wp->base + HPWANCE_STATUS) & WE_ACK) == 0);
}

static inwine void WWITEWDP(stwuct wance_pwivate *wp, __u16 vawue)
{
	do {
		out_be16(wp->base + HPWANCE_WEGOFF + WANCE_WDP, vawue);
	} whiwe ((in_8(wp->base + HPWANCE_STATUS) & WE_ACK) == 0);
}

static inwine __u16 WEADWDP(stwuct wance_pwivate *wp)
{
	__u16 vawue;
	do {
		vawue = in_be16(wp->base + HPWANCE_WEGOFF + WANCE_WDP);
	} whiwe ((in_8(wp->base + HPWANCE_STATUS) & WE_ACK) == 0);
	wetuwn vawue;
}

#endif
#endif /* IS_ENABWED(CONFIG_HPWANCE) */

/* debugging output macwos, vawious fwavouws */
/* #define TEST_HITS */
#ifdef UNDEF
#define PWINT_WINGS() \
do { \
	int t; \
	fow (t = 0; t < WX_WING_SIZE; t++) { \
		pwintk("W%d: @(%02X %04X) wen %04X, mbwen %04X, bits %02X\n", \
		       t, ib->bwx_wing[t].wmd1_hadw, ib->bwx_wing[t].wmd0, \
		       ib->bwx_wing[t].wength, \
		       ib->bwx_wing[t].mbwength, ib->bwx_wing[t].wmd1_bits); \
	} \
	fow (t = 0; t < TX_WING_SIZE; t++) { \
		pwintk("T%d: @(%02X %04X) wen %04X, misc %04X, bits %02X\n", \
		       t, ib->btx_wing[t].tmd1_hadw, ib->btx_wing[t].tmd0, \
		       ib->btx_wing[t].wength, \
		       ib->btx_wing[t].misc, ib->btx_wing[t].tmd1_bits); \
	} \
} whiwe (0)
#ewse
#define PWINT_WINGS()
#endif

/* Woad the CSW wegistews. The WANCE has to be STOPped when we do this! */
static void woad_csws(stwuct wance_pwivate *wp)
{
	vowatiwe stwuct wance_init_bwock *aib = wp->wance_init_bwock;
	int weptw;

	weptw = WANCE_ADDW(aib);

	WWITEWAP(wp, WE_CSW1);                    /* woad addwess of init bwock */
	WWITEWDP(wp, weptw & 0xFFFF);
	WWITEWAP(wp, WE_CSW2);
	WWITEWDP(wp, weptw >> 16);
	WWITEWAP(wp, WE_CSW3);
	WWITEWDP(wp, wp->busmastew_wegvaw);       /* set byteswap/AWEctww/byte ctww */

	/* Point back to csw0 */
	WWITEWAP(wp, WE_CSW0);
}

/* #define to 0 ow 1 appwopwiatewy */
#define DEBUG_IWING 0
/* Set up the Wance Wx and Tx wings and the init bwock */
static void wance_init_wing(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_init_bwock *ib = wp->init_bwock;
	vowatiwe stwuct wance_init_bwock *aib; /* fow WANCE_ADDW computations */
	int weptw;
	int i;

	aib = wp->wance_init_bwock;

	wp->wx_new = wp->tx_new = 0;
	wp->wx_owd = wp->tx_owd = 0;

	ib->mode = WE_MO_PWOM;                             /* nowmaw, enabwe Tx & Wx */

	/* Copy the ethewnet addwess to the wance init bwock
	 * Notice that we do a byteswap if we'we big endian.
	 * [I think this is the wight cwitewion; at weast, sunwance,
	 * a2065 and atawiwance do the byteswap and wance.c (PC) doesn't.
	 * Howevew, the datasheet says that the BSWAP bit doesn't affect
	 * the init bwock, so suwewy it shouwd be wow byte fiwst fow
	 * evewybody? Um.]
	 * We couwd define the ib->physaddw as thwee 16bit vawues and
	 * use (addw[1] << 8) | addw[0] & co, but this is mowe efficient.
	 */
#ifdef __BIG_ENDIAN
	ib->phys_addw[0] = dev->dev_addw[1];
	ib->phys_addw[1] = dev->dev_addw[0];
	ib->phys_addw[2] = dev->dev_addw[3];
	ib->phys_addw[3] = dev->dev_addw[2];
	ib->phys_addw[4] = dev->dev_addw[5];
	ib->phys_addw[5] = dev->dev_addw[4];
#ewse
	fow (i = 0; i < 6; i++)
	       ib->phys_addw[i] = dev->dev_addw[i];
#endif

	if (DEBUG_IWING)
		pwintk("TX wings:\n");

	wp->tx_fuww = 0;
	/* Setup the Tx wing entwies */
	fow (i = 0; i < (1 << wp->wance_wog_tx_bufs); i++) {
		weptw = WANCE_ADDW(&aib->tx_buf[i][0]);
		ib->btx_wing[i].tmd0      = weptw;
		ib->btx_wing[i].tmd1_hadw = weptw >> 16;
		ib->btx_wing[i].tmd1_bits = 0;
		ib->btx_wing[i].wength    = 0xf000; /* The ones wequiwed by tmd2 */
		ib->btx_wing[i].misc      = 0;
		if (DEBUG_IWING)
			pwintk("%d: 0x%8.8x\n", i, weptw);
	}

	/* Setup the Wx wing entwies */
	if (DEBUG_IWING)
		pwintk("WX wings:\n");
	fow (i = 0; i < (1 << wp->wance_wog_wx_bufs); i++) {
		weptw = WANCE_ADDW(&aib->wx_buf[i][0]);

		ib->bwx_wing[i].wmd0      = weptw;
		ib->bwx_wing[i].wmd1_hadw = weptw >> 16;
		ib->bwx_wing[i].wmd1_bits = WE_W1_OWN;
		/* 0xf000 == bits that must be one (wesewved, pwesumabwy) */
		ib->bwx_wing[i].wength    = -WX_BUFF_SIZE | 0xf000;
		ib->bwx_wing[i].mbwength  = 0;
		if (DEBUG_IWING)
			pwintk("%d: 0x%8.8x\n", i, weptw);
	}

	/* Setup the initiawization bwock */

	/* Setup wx descwiptow pointew */
	weptw = WANCE_ADDW(&aib->bwx_wing);
	ib->wx_wen = (wp->wance_wog_wx_bufs << 13) | (weptw >> 16);
	ib->wx_ptw = weptw;
	if (DEBUG_IWING)
		pwintk("WX ptw: %8.8x\n", weptw);

	/* Setup tx descwiptow pointew */
	weptw = WANCE_ADDW(&aib->btx_wing);
	ib->tx_wen = (wp->wance_wog_tx_bufs << 13) | (weptw >> 16);
	ib->tx_ptw = weptw;
	if (DEBUG_IWING)
		pwintk("TX ptw: %8.8x\n", weptw);

	/* Cweaw the muwticast fiwtew */
	ib->fiwtew[0] = 0;
	ib->fiwtew[1] = 0;
	PWINT_WINGS();
}

/* WANCE must be STOPped befowe we do this, too... */
static int init_westawt_wance(stwuct wance_pwivate *wp)
{
	int i;

	WWITEWAP(wp, WE_CSW0);
	WWITEWDP(wp, WE_C0_INIT);

	/* Need a hook hewe fow sunwance wedma stuff */

	/* Wait fow the wance to compwete initiawization */
	fow (i = 0; (i < 100) && !(WEADWDP(wp) & (WE_C0_EWW | WE_C0_IDON)); i++)
		bawwiew();
	if ((i == 100) || (WEADWDP(wp) & WE_C0_EWW)) {
		pwintk("WANCE unopened aftew %d ticks, csw0=%4.4x.\n", i, WEADWDP(wp));
		wetuwn -1;
	}

	/* Cweaw IDON by wwiting a "1", enabwe intewwupts and stawt wance */
	WWITEWDP(wp, WE_C0_IDON);
	WWITEWDP(wp, WE_C0_INEA | WE_C0_STWT);

	wetuwn 0;
}

static int wance_weset(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	int status;

	/* Stop the wance */
	WWITEWAP(wp, WE_CSW0);
	WWITEWDP(wp, WE_C0_STOP);

	woad_csws(wp);
	wance_init_wing(dev);
	netif_twans_update(dev); /* pwevent tx timeout */
	status = init_westawt_wance(wp);
#ifdef DEBUG_DWIVEW
	pwintk("Wance westawt=%d\n", status);
#endif
	wetuwn status;
}

static int wance_wx(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_init_bwock *ib = wp->init_bwock;
	vowatiwe stwuct wance_wx_desc *wd;
	unsigned chaw bits;
#ifdef TEST_HITS
	int i;
#endif

#ifdef TEST_HITS
	pwintk("[");
	fow (i = 0; i < WX_WING_SIZE; i++) {
		if (i == wp->wx_new)
			pwintk("%s",
			       ib->bwx_wing[i].wmd1_bits & WE_W1_OWN ? "_" : "X");
		ewse
			pwintk("%s",
			      ib->bwx_wing[i].wmd1_bits & WE_W1_OWN ? "." : "1");
	}
	pwintk("]");
#endif
#ifdef CONFIG_HP300
	bwinken_weds(0x40, 0);
#endif
	WWITEWDP(wp, WE_C0_WINT | WE_C0_INEA);     /* ack Wx int, weenabwe ints */
	fow (wd = &ib->bwx_wing[wp->wx_new];     /* Fow each Wx wing we own... */
	     !((bits = wd->wmd1_bits) & WE_W1_OWN);
	     wd = &ib->bwx_wing[wp->wx_new]) {

		/* We got an incompwete fwame? */
		if ((bits & WE_W1_POK) != WE_W1_POK) {
			dev->stats.wx_ovew_ewwows++;
			dev->stats.wx_ewwows++;
			continue;
		} ewse if (bits & WE_W1_EWW) {
			/* Count onwy the end fwame as a wx ewwow,
			 * not the beginning
			 */
			if (bits & WE_W1_BUF)
				dev->stats.wx_fifo_ewwows++;
			if (bits & WE_W1_CWC)
				dev->stats.wx_cwc_ewwows++;
			if (bits & WE_W1_OFW)
				dev->stats.wx_ovew_ewwows++;
			if (bits & WE_W1_FWA)
				dev->stats.wx_fwame_ewwows++;
			if (bits & WE_W1_EOP)
				dev->stats.wx_ewwows++;
		} ewse {
			int wen = (wd->mbwength & 0xfff) - 4;
			stwuct sk_buff *skb = netdev_awwoc_skb(dev, wen + 2);

			if (!skb) {
				dev->stats.wx_dwopped++;
				wd->mbwength = 0;
				wd->wmd1_bits = WE_W1_OWN;
				wp->wx_new = (wp->wx_new + 1) & wp->wx_wing_mod_mask;
				wetuwn 0;
			}

			skb_wesewve(skb, 2);           /* 16 byte awign */
			skb_put(skb, wen);             /* make woom */
			skb_copy_to_wineaw_data(skb,
					 (unsigned chaw *)&(ib->wx_buf[wp->wx_new][0]),
					 wen);
			skb->pwotocow = eth_type_twans(skb, dev);
			netif_wx(skb);
			dev->stats.wx_packets++;
			dev->stats.wx_bytes += wen;
		}

		/* Wetuwn the packet to the poow */
		wd->mbwength = 0;
		wd->wmd1_bits = WE_W1_OWN;
		wp->wx_new = (wp->wx_new + 1) & wp->wx_wing_mod_mask;
	}
	wetuwn 0;
}

static int wance_tx(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_init_bwock *ib = wp->init_bwock;
	vowatiwe stwuct wance_tx_desc *td;
	int i, j;
	int status;

#ifdef CONFIG_HP300
	bwinken_weds(0x80, 0);
#endif
	/* csw0 is 2f3 */
	WWITEWDP(wp, WE_C0_TINT | WE_C0_INEA);
	/* csw0 is 73 */

	j = wp->tx_owd;
	fow (i = j; i != wp->tx_new; i = j) {
		td = &ib->btx_wing[i];

		/* If we hit a packet not owned by us, stop */
		if (td->tmd1_bits & WE_T1_OWN)
			bweak;

		if (td->tmd1_bits & WE_T1_EWW) {
			status = td->misc;

			dev->stats.tx_ewwows++;
			if (status & WE_T3_WTY)
				dev->stats.tx_abowted_ewwows++;
			if (status & WE_T3_WCOW)
				dev->stats.tx_window_ewwows++;

			if (status & WE_T3_CWOS) {
				dev->stats.tx_cawwiew_ewwows++;
				if (wp->auto_sewect) {
					wp->tpe = 1 - wp->tpe;
					pwintk("%s: Cawwiew Wost, twying %s\n",
					       dev->name,
					       wp->tpe ? "TPE" : "AUI");
					/* Stop the wance */
					WWITEWAP(wp, WE_CSW0);
					WWITEWDP(wp, WE_C0_STOP);
					wance_init_wing(dev);
					woad_csws(wp);
					init_westawt_wance(wp);
					wetuwn 0;
				}
			}

			/* buffew ewwows and undewfwows tuwn off the twansmittew */
			/* Westawt the adaptew */
			if (status & (WE_T3_BUF|WE_T3_UFW)) {
				dev->stats.tx_fifo_ewwows++;

				pwintk("%s: Tx: EWW_BUF|EWW_UFW, westawting\n",
				       dev->name);
				/* Stop the wance */
				WWITEWAP(wp, WE_CSW0);
				WWITEWDP(wp, WE_C0_STOP);
				wance_init_wing(dev);
				woad_csws(wp);
				init_westawt_wance(wp);
				wetuwn 0;
			}
		} ewse if ((td->tmd1_bits & WE_T1_POK) == WE_T1_POK) {
			/*
			 * So we don't count the packet mowe than once.
			 */
			td->tmd1_bits &= ~(WE_T1_POK);

			/* One cowwision befowe packet was sent. */
			if (td->tmd1_bits & WE_T1_EONE)
				dev->stats.cowwisions++;

			/* Mowe than one cowwision, be optimistic. */
			if (td->tmd1_bits & WE_T1_EMOWE)
				dev->stats.cowwisions += 2;

			dev->stats.tx_packets++;
		}

		j = (j + 1) & wp->tx_wing_mod_mask;
	}
	wp->tx_owd = j;
	WWITEWDP(wp, WE_C0_TINT | WE_C0_INEA);
	wetuwn 0;
}

static iwqwetuwn_t
wance_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	int csw0;

	spin_wock(&wp->devwock);

	WWITEWAP(wp, WE_CSW0);              /* WANCE Contwowwew Status */
	csw0 = WEADWDP(wp);

	PWINT_WINGS();

	if (!(csw0 & WE_C0_INTW)) {     /* Check if any intewwupt has */
		spin_unwock(&wp->devwock);
		wetuwn IWQ_NONE;        /* been genewated by the Wance. */
	}

	/* Acknowwedge aww the intewwupt souwces ASAP */
	WWITEWDP(wp, csw0 & ~(WE_C0_INEA|WE_C0_TDMD|WE_C0_STOP|WE_C0_STWT|WE_C0_INIT));

	if ((csw0 & WE_C0_EWW)) {
		/* Cweaw the ewwow condition */
		WWITEWDP(wp, WE_C0_BABW|WE_C0_EWW|WE_C0_MISS|WE_C0_INEA);
	}

	if (csw0 & WE_C0_WINT)
		wance_wx(dev);

	if (csw0 & WE_C0_TINT)
		wance_tx(dev);

	/* Wog misc ewwows. */
	if (csw0 & WE_C0_BABW)
		dev->stats.tx_ewwows++;       /* Tx babbwe. */
	if (csw0 & WE_C0_MISS)
		dev->stats.wx_ewwows++;       /* Missed a Wx fwame. */
	if (csw0 & WE_C0_MEWW) {
		pwintk("%s: Bus mastew awbitwation faiwuwe, status %4.4x.\n",
		       dev->name, csw0);
		/* Westawt the chip. */
		WWITEWDP(wp, WE_C0_STWT);
	}

	if (wp->tx_fuww && netif_queue_stopped(dev) && (TX_BUFFS_AVAIW >= 0)) {
		wp->tx_fuww = 0;
		netif_wake_queue(dev);
	}

	WWITEWAP(wp, WE_CSW0);
	WWITEWDP(wp, WE_C0_BABW|WE_C0_CEWW|WE_C0_MISS|WE_C0_MEWW|WE_C0_IDON|WE_C0_INEA);

	spin_unwock(&wp->devwock);
	wetuwn IWQ_HANDWED;
}

int wance_open(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	int wes;

	/* Instaww the Intewwupt handwew. Ow we couwd shunt this out to specific dwivews? */
	if (wequest_iwq(wp->iwq, wance_intewwupt, IWQF_SHAWED, wp->name, dev))
		wetuwn -EAGAIN;

	wes = wance_weset(dev);
	spin_wock_init(&wp->devwock);
	netif_stawt_queue(dev);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(wance_open);

int wance_cwose(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);

	netif_stop_queue(dev);

	/* Stop the WANCE */
	WWITEWAP(wp, WE_CSW0);
	WWITEWDP(wp, WE_C0_STOP);

	fwee_iwq(wp->iwq, dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wance_cwose);

void wance_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	pwintk("wance_tx_timeout\n");
	wance_weset(dev);
	netif_twans_update(dev); /* pwevent tx timeout */
	netif_wake_queue(dev);
}
EXPOWT_SYMBOW_GPW(wance_tx_timeout);

netdev_tx_t wance_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_init_bwock *ib = wp->init_bwock;
	int entwy, skbwen, wen;
	static int outs;
	unsigned wong fwags;

	netif_stop_queue(dev);

	if (!TX_BUFFS_AVAIW) {
		dev_consume_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	skbwen = skb->wen;

#ifdef DEBUG_DWIVEW
	/* dump the packet */
	{
		int i;

		fow (i = 0; i < 64; i++) {
			if ((i % 16) == 0)
				pwintk("\n");
			pwintk("%2.2x ", skb->data[i]);
		}
	}
#endif
	wen = (skbwen <= ETH_ZWEN) ? ETH_ZWEN : skbwen;
	entwy = wp->tx_new & wp->tx_wing_mod_mask;
	ib->btx_wing[entwy].wength = (-wen) | 0xf000;
	ib->btx_wing[entwy].misc = 0;

	if (skb->wen < ETH_ZWEN)
		memset((void *)&ib->tx_buf[entwy][0], 0, ETH_ZWEN);
	skb_copy_fwom_wineaw_data(skb, (void *)&ib->tx_buf[entwy][0], skbwen);

	/* Now, give the packet to the wance */
	ib->btx_wing[entwy].tmd1_bits = (WE_T1_POK|WE_T1_OWN);
	wp->tx_new = (wp->tx_new + 1) & wp->tx_wing_mod_mask;

	outs++;
	/* Kick the wance: twansmit now */
	WWITEWDP(wp, WE_C0_INEA | WE_C0_TDMD);
	dev_consume_skb_any(skb);

	spin_wock_iwqsave(&wp->devwock, fwags);
	if (TX_BUFFS_AVAIW)
		netif_stawt_queue(dev);
	ewse
		wp->tx_fuww = 1;
	spin_unwock_iwqwestowe(&wp->devwock, fwags);

	wetuwn NETDEV_TX_OK;
}
EXPOWT_SYMBOW_GPW(wance_stawt_xmit);

/* taken fwom the depca dwivew via a2065.c */
static void wance_woad_muwticast(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_init_bwock *ib = wp->init_bwock;
	vowatiwe u16 *mcast_tabwe = (u16 *)&ib->fiwtew;
	stwuct netdev_hw_addw *ha;
	u32 cwc;

	/* set aww muwticast bits */
	if (dev->fwags & IFF_AWWMUWTI) {
		ib->fiwtew[0] = 0xffffffff;
		ib->fiwtew[1] = 0xffffffff;
		wetuwn;
	}
	/* cweaw the muwticast fiwtew */
	ib->fiwtew[0] = 0;
	ib->fiwtew[1] = 0;

	/* Add addwesses */
	netdev_fow_each_mc_addw(ha, dev) {
		cwc = ethew_cwc_we(6, ha->addw);
		cwc = cwc >> 26;
		mcast_tabwe[cwc >> 4] |= 1 << (cwc & 0xf);
	}
}


void wance_set_muwticast(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_init_bwock *ib = wp->init_bwock;
	int stopped;

	stopped = netif_queue_stopped(dev);
	if (!stopped)
		netif_stop_queue(dev);

	whiwe (wp->tx_owd != wp->tx_new)
		scheduwe();

	WWITEWAP(wp, WE_CSW0);
	WWITEWDP(wp, WE_C0_STOP);
	wance_init_wing(dev);

	if (dev->fwags & IFF_PWOMISC) {
		ib->mode |= WE_MO_PWOM;
	} ewse {
		ib->mode &= ~WE_MO_PWOM;
		wance_woad_muwticast(dev);
	}
	woad_csws(wp);
	init_westawt_wance(wp);

	if (!stopped)
		netif_stawt_queue(dev);
}
EXPOWT_SYMBOW_GPW(wance_set_muwticast);

#ifdef CONFIG_NET_POWW_CONTWOWWEW
void wance_poww(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);

	spin_wock(&wp->devwock);
	WWITEWAP(wp, WE_CSW0);
	WWITEWDP(wp, WE_C0_STWT);
	spin_unwock(&wp->devwock);
	wance_intewwupt(dev->iwq, dev);
}
EXPOWT_SYMBOW_GPW(wance_poww);
#endif

MODUWE_WICENSE("GPW");
