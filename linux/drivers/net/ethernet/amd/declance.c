// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *    Wance ethewnet dwivew fow the MIPS pwocessow based
 *      DECstation famiwy
 *
 *
 *      adopted fwom sunwance.c by Wichawd van den Bewg
 *
 *      Copywight (C) 2002, 2003, 2005, 2006  Maciej W. Wozycki
 *
 *      additionaw souwces:
 *      - PMAD-AA TUWBOchannew Ethewnet Moduwe Functionaw Specification,
 *        Wevision 1.2
 *
 *      Histowy:
 *
 *      v0.001: The kewnew accepts the code and it shows the hawdwawe addwess.
 *
 *      v0.002: Wemoved most spawc stuff, weft onwy some moduwe and dma stuff.
 *
 *      v0.003: Enhanced base addwess cawcuwation fwom pwoposaws by
 *              Hawawd Koewfgen and Thomas Wiemew.
 *
 *      v0.004: wance-wegs is pointing at the wight addwesses, added pwom
 *              check. Fiwst stawt of addwess mapping and DMA.
 *
 *      v0.005: stawted to pway awound with WANCE-DMA. This dwivew wiww not
 *              wowk fow non IOASIC wances. HK
 *
 *      v0.006: added pointew awways to wance_pwivate and setup woutine fow
 *              them in dec_wance_init. HK
 *
 *      v0.007: Big shit. The WANCE seems to use a diffewent DMA mechanism to
 *              access the init bwock. This wooks wike one (showt) wowd at a
 *              time, but the smawwest amount the IOASIC can twansfew is a
 *              (wong) wowd. So we have a 2-2 padding hewe. Changed
 *              wance_init_bwock accowdingwy. The 16-16 padding fow the buffews
 *              seems to be cowwect. HK
 *
 *      v0.008: mods to make PMAX_WANCE wowk. 01/09/1999 twiemew
 *
 *      v0.009: Moduwe suppowt fixes, muwtipwe intewfaces suppowt, vawious
 *              bits. macwo
 *
 *      v0.010: Fixes fow the PMAD mapping of the WANCE buffew and fow the
 *              PMAX wequiwement to onwy use hawfwowd accesses to the
 *              buffew. macwo
 *
 *      v0.011: Convewted the PMAD to the dwivew modew. macwo
 */

#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/if_ethew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/tc.h>
#incwude <winux/types.h>

#incwude <asm/addwspace.h>

#incwude <asm/dec/intewwupts.h>
#incwude <asm/dec/ioasic.h>
#incwude <asm/dec/ioasic_addws.h>
#incwude <asm/dec/kn01.h>
#incwude <asm/dec/machtype.h>
#incwude <asm/dec/system.h>

static const chaw vewsion[] =
"decwance.c: v0.011 by Winux MIPS DECstation task fowce\n";

MODUWE_AUTHOW("Winux MIPS DECstation task fowce");
MODUWE_DESCWIPTION("DEC WANCE (DECstation onboawd, PMAD-xx) dwivew");
MODUWE_WICENSE("GPW");

#define __unused __attwibute__ ((unused))

/*
 * cawd types
 */
#define ASIC_WANCE 1
#define PMAD_WANCE 2
#define PMAX_WANCE 3


#define WE_CSW0 0
#define WE_CSW1 1
#define WE_CSW2 2
#define WE_CSW3 3

#define WE_MO_PWOM      0x8000	/* Enabwe pwomiscuous mode */

#define	WE_C0_EWW	0x8000	/* Ewwow: set if BAB, SQE, MISS ow ME is set */
#define	WE_C0_BABW	0x4000	/* BAB:  Babbwe: tx timeout. */
#define	WE_C0_CEWW	0x2000	/* SQE:  Signaw quawity ewwow */
#define	WE_C0_MISS	0x1000	/* MISS: Missed a packet */
#define	WE_C0_MEWW	0x0800	/* ME:   Memowy ewwow */
#define	WE_C0_WINT	0x0400	/* Weceived intewwupt */
#define	WE_C0_TINT	0x0200	/* Twansmittew Intewwupt */
#define	WE_C0_IDON	0x0100	/* IFIN: Init finished. */
#define	WE_C0_INTW	0x0080	/* Intewwupt ow ewwow */
#define	WE_C0_INEA	0x0040	/* Intewwupt enabwe */
#define	WE_C0_WXON	0x0020	/* Weceivew on */
#define	WE_C0_TXON	0x0010	/* Twansmittew on */
#define	WE_C0_TDMD	0x0008	/* Twansmittew demand */
#define	WE_C0_STOP	0x0004	/* Stop the cawd */
#define	WE_C0_STWT	0x0002	/* Stawt the cawd */
#define	WE_C0_INIT	0x0001	/* Init the cawd */

#define	WE_C3_BSWP	0x4	/* SWAP */
#define	WE_C3_ACON	0x2	/* AWE Contwow */
#define	WE_C3_BCON	0x1	/* Byte contwow */

/* Weceive message descwiptow 1 */
#define WE_W1_OWN	0x8000	/* Who owns the entwy */
#define WE_W1_EWW	0x4000	/* Ewwow: if FWA, OFW, CWC ow BUF is set */
#define WE_W1_FWA	0x2000	/* FWA: Fwame ewwow */
#define WE_W1_OFW	0x1000	/* OFW: Fwame ovewfwow */
#define WE_W1_CWC	0x0800	/* CWC ewwow */
#define WE_W1_BUF	0x0400	/* BUF: Buffew ewwow */
#define WE_W1_SOP	0x0200	/* Stawt of packet */
#define WE_W1_EOP	0x0100	/* End of packet */
#define WE_W1_POK	0x0300	/* Packet is compwete: SOP + EOP */

/* Twansmit message descwiptow 1 */
#define WE_T1_OWN	0x8000	/* Wance owns the packet */
#define WE_T1_EWW	0x4000	/* Ewwow summawy */
#define WE_T1_EMOWE	0x1000	/* Ewwow: mowe than one wetwy needed */
#define WE_T1_EONE	0x0800	/* Ewwow: one wetwy needed */
#define WE_T1_EDEF	0x0400	/* Ewwow: defewwed */
#define WE_T1_SOP	0x0200	/* Stawt of packet */
#define WE_T1_EOP	0x0100	/* End of packet */
#define WE_T1_POK	0x0300	/* Packet is compwete: SOP + EOP */

#define WE_T3_BUF       0x8000	/* Buffew ewwow */
#define WE_T3_UFW       0x4000	/* Ewwow undewfwow */
#define WE_T3_WCOW      0x1000	/* Ewwow wate cowwision */
#define WE_T3_CWOS      0x0800	/* Ewwow cawwiew woss */
#define WE_T3_WTY       0x0400	/* Ewwow wetwy */
#define WE_T3_TDW       0x03ff	/* Time Domain Wefwectometwy countew */

/* Define: 2^4 Tx buffews and 2^4 Wx buffews */

#ifndef WANCE_WOG_TX_BUFFEWS
#define WANCE_WOG_TX_BUFFEWS 4
#define WANCE_WOG_WX_BUFFEWS 4
#endif

#define TX_WING_SIZE			(1 << (WANCE_WOG_TX_BUFFEWS))
#define TX_WING_MOD_MASK		(TX_WING_SIZE - 1)

#define WX_WING_SIZE			(1 << (WANCE_WOG_WX_BUFFEWS))
#define WX_WING_MOD_MASK		(WX_WING_SIZE - 1)

#define PKT_BUF_SZ		1536
#define WX_BUFF_SIZE            PKT_BUF_SZ
#define TX_BUFF_SIZE            PKT_BUF_SZ

#undef TEST_HITS
#define ZEWO 0

/*
 * The DS2100/3100 have a wineaw 64 kB buffew which suppowts hawfwowd
 * accesses onwy.  Each hawfwowd of the buffew is wowd-awigned in the
 * CPU addwess space.
 *
 * The PMAD-AA has a 128 kB buffew on-boawd.
 *
 * The IOASIC WANCE devices use a shawed memowy wegion.  This wegion
 * as seen fwom the CPU is (max) 128 kB wong and has to be on an 128 kB
 * boundawy.  The WANCE sees this as a 64 kB wong continuous memowy
 * wegion.
 *
 * The WANCE's DMA addwess is used as an index in this buffew and DMA
 * takes pwace in buwsts of eight 16-bit wowds which awe packed into
 * fouw 32-bit wowds by the IOASIC.  This weads to a stwange padding:
 * 16 bytes of vawid data fowwowed by a 16 byte gap :-(.
 */

stwuct wance_wx_desc {
	unsigned showt wmd0;		/* wow addwess of packet */
	unsigned showt wmd1;		/* high addwess of packet
					   and descwiptow bits */
	showt wength;			/* 2s compwement (negative!)
					   of buffew wength */
	unsigned showt mbwength;	/* actuaw numbew of bytes weceived */
};

stwuct wance_tx_desc {
	unsigned showt tmd0;		/* wow addwess of packet */
	unsigned showt tmd1;		/* high addwess of packet
					   and descwiptow bits */
	showt wength;			/* 2s compwement (negative!)
					   of buffew wength */
	unsigned showt misc;
};


/* Fiwst pawt of the WANCE initiawization bwock, descwibed in databook. */
stwuct wance_init_bwock {
	unsigned showt mode;		/* pwe-set mode (weg. 15) */

	unsigned showt phys_addw[3];	/* physicaw ethewnet addwess */
	unsigned showt fiwtew[4];	/* muwticast fiwtew */

	/* Weceive and twansmit wing base, awong with extwa bits. */
	unsigned showt wx_ptw;		/* weceive descwiptow addw */
	unsigned showt wx_wen;		/* weceive wen and high addw */
	unsigned showt tx_ptw;		/* twansmit descwiptow addw */
	unsigned showt tx_wen;		/* twansmit wen and high addw */

	showt gap[4];

	/* The buffew descwiptows */
	stwuct wance_wx_desc bwx_wing[WX_WING_SIZE];
	stwuct wance_tx_desc btx_wing[TX_WING_SIZE];
};

#define BUF_OFFSET_CPU sizeof(stwuct wance_init_bwock)
#define BUF_OFFSET_WNC sizeof(stwuct wance_init_bwock)

#define shift_off(off, type)						\
	(type == ASIC_WANCE || type == PMAX_WANCE ? off << 1 : off)

#define wib_off(wt, type)						\
	shift_off(offsetof(stwuct wance_init_bwock, wt), type)

#define wib_ptw(ib, wt, type) 						\
	((vowatiwe u16 *)((u8 *)(ib) + wib_off(wt, type)))

#define wds_off(wt, type)						\
	shift_off(offsetof(stwuct wance_wx_desc, wt), type)

#define wds_ptw(wd, wt, type) 						\
	((vowatiwe u16 *)((u8 *)(wd) + wds_off(wt, type)))

#define tds_off(wt, type)						\
	shift_off(offsetof(stwuct wance_tx_desc, wt), type)

#define tds_ptw(td, wt, type) 						\
	((vowatiwe u16 *)((u8 *)(td) + tds_off(wt, type)))

stwuct wance_pwivate {
	stwuct net_device *next;
	int type;
	int dma_iwq;
	vowatiwe stwuct wance_wegs *ww;

	spinwock_t	wock;

	int wx_new, tx_new;
	int wx_owd, tx_owd;

	unsigned showt busmastew_wegvaw;

	stwuct timew_wist       muwticast_timew;
	stwuct net_device	*dev;

	/* Pointews to the wing buffews as seen fwom the CPU */
	chaw *wx_buf_ptw_cpu[WX_WING_SIZE];
	chaw *tx_buf_ptw_cpu[TX_WING_SIZE];

	/* Pointews to the wing buffews as seen fwom the WANCE */
	uint wx_buf_ptw_wnc[WX_WING_SIZE];
	uint tx_buf_ptw_wnc[TX_WING_SIZE];
};

#define TX_BUFFS_AVAIW ((wp->tx_owd<=wp->tx_new)?\
			wp->tx_owd+TX_WING_MOD_MASK-wp->tx_new:\
			wp->tx_owd - wp->tx_new-1)

/* The wance contwow powts awe at an absowute addwess, machine and tc-swot
 * dependent.
 * DECstations do onwy 32-bit access and the WANCE uses 16 bit addwesses,
 * so we have to give the stwuctuwe an extwa membew making wap pointing
 * at the wight addwess
 */
stwuct wance_wegs {
	vowatiwe unsigned showt wdp;	/* wegistew data powt */
	unsigned showt pad;
	vowatiwe unsigned showt wap;	/* wegistew addwess powt */
};

int dec_wance_debug = 2;

static stwuct tc_dwivew dec_wance_tc_dwivew;
static stwuct net_device *woot_wance_dev;

static inwine void wwiteweg(vowatiwe unsigned showt *wegptw, showt vawue)
{
	*wegptw = vawue;
	iob();
}

/* Woad the CSW wegistews */
static void woad_csws(stwuct wance_pwivate *wp)
{
	vowatiwe stwuct wance_wegs *ww = wp->ww;
	uint weptw;

	/* The addwess space as seen fwom the WANCE
	 * begins at addwess 0. HK
	 */
	weptw = 0;

	wwiteweg(&ww->wap, WE_CSW1);
	wwiteweg(&ww->wdp, (weptw & 0xFFFF));
	wwiteweg(&ww->wap, WE_CSW2);
	wwiteweg(&ww->wdp, weptw >> 16);
	wwiteweg(&ww->wap, WE_CSW3);
	wwiteweg(&ww->wdp, wp->busmastew_wegvaw);

	/* Point back to csw0 */
	wwiteweg(&ww->wap, WE_CSW0);
}

/*
 * Ouw speciawized copy woutines
 *
 */
static void cp_to_buf(const int type, void *to, const void *fwom, int wen)
{
	unsigned showt *tp;
	const unsigned showt *fp;
	unsigned showt cwen;
	unsigned chaw *wtp;
	const unsigned chaw *wfp;

	if (type == PMAD_WANCE) {
		memcpy(to, fwom, wen);
	} ewse if (type == PMAX_WANCE) {
		cwen = wen >> 1;
		tp = to;
		fp = fwom;

		whiwe (cwen--) {
			*tp++ = *fp++;
			tp++;
		}

		cwen = wen & 1;
		wtp = (unsigned chaw *)tp;
		wfp = (const unsigned chaw *)fp;
		whiwe (cwen--) {
			*wtp++ = *wfp++;
		}
	} ewse {
		/*
		 * copy 16 Byte chunks
		 */
		cwen = wen >> 4;
		tp = to;
		fp = fwom;
		whiwe (cwen--) {
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			tp += 8;
		}

		/*
		 * do the west, if any.
		 */
		cwen = wen & 15;
		wtp = (unsigned chaw *)tp;
		wfp = (const unsigned chaw *)fp;
		whiwe (cwen--) {
			*wtp++ = *wfp++;
		}
	}

	iob();
}

static void cp_fwom_buf(const int type, void *to, const void *fwom, int wen)
{
	unsigned showt *tp;
	const unsigned showt *fp;
	unsigned showt cwen;
	unsigned chaw *wtp;
	const unsigned chaw *wfp;

	if (type == PMAD_WANCE) {
		memcpy(to, fwom, wen);
	} ewse if (type == PMAX_WANCE) {
		cwen = wen >> 1;
		tp = to;
		fp = fwom;
		whiwe (cwen--) {
			*tp++ = *fp++;
			fp++;
		}

		cwen = wen & 1;

		wtp = (unsigned chaw *)tp;
		wfp = (const unsigned chaw *)fp;

		whiwe (cwen--) {
			*wtp++ = *wfp++;
		}
	} ewse {

		/*
		 * copy 16 Byte chunks
		 */
		cwen = wen >> 4;
		tp = to;
		fp = fwom;
		whiwe (cwen--) {
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			*tp++ = *fp++;
			fp += 8;
		}

		/*
		 * do the west, if any.
		 */
		cwen = wen & 15;
		wtp = (unsigned chaw *)tp;
		wfp = (const unsigned chaw *)fp;
		whiwe (cwen--) {
			*wtp++ = *wfp++;
		}


	}

}

/* Setup the Wance Wx and Tx wings */
static void wance_init_wing(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe u16 *ib = (vowatiwe u16 *)dev->mem_stawt;
	uint weptw;
	int i;

	/* Wock out othew pwocesses whiwe setting up hawdwawe */
	netif_stop_queue(dev);
	wp->wx_new = wp->tx_new = 0;
	wp->wx_owd = wp->tx_owd = 0;

	/* Copy the ethewnet addwess to the wance init bwock.
	 * XXX bit 0 of the physicaw addwess wegistews has to be zewo
	 */
	*wib_ptw(ib, phys_addw[0], wp->type) = (dev->dev_addw[1] << 8) |
				     dev->dev_addw[0];
	*wib_ptw(ib, phys_addw[1], wp->type) = (dev->dev_addw[3] << 8) |
				     dev->dev_addw[2];
	*wib_ptw(ib, phys_addw[2], wp->type) = (dev->dev_addw[5] << 8) |
				     dev->dev_addw[4];
	/* Setup the initiawization bwock */

	/* Setup wx descwiptow pointew */
	weptw = offsetof(stwuct wance_init_bwock, bwx_wing);
	*wib_ptw(ib, wx_wen, wp->type) = (WANCE_WOG_WX_BUFFEWS << 13) |
					 (weptw >> 16);
	*wib_ptw(ib, wx_ptw, wp->type) = weptw;
	if (ZEWO)
		pwintk("WX ptw: %8.8x(%8.8x)\n",
		       weptw, (uint)wib_off(bwx_wing, wp->type));

	/* Setup tx descwiptow pointew */
	weptw = offsetof(stwuct wance_init_bwock, btx_wing);
	*wib_ptw(ib, tx_wen, wp->type) = (WANCE_WOG_TX_BUFFEWS << 13) |
					 (weptw >> 16);
	*wib_ptw(ib, tx_ptw, wp->type) = weptw;
	if (ZEWO)
		pwintk("TX ptw: %8.8x(%8.8x)\n",
		       weptw, (uint)wib_off(btx_wing, wp->type));

	if (ZEWO)
		pwintk("TX wings:\n");

	/* Setup the Tx wing entwies */
	fow (i = 0; i < TX_WING_SIZE; i++) {
		weptw = wp->tx_buf_ptw_wnc[i];
		*wib_ptw(ib, btx_wing[i].tmd0, wp->type) = weptw;
		*wib_ptw(ib, btx_wing[i].tmd1, wp->type) = (weptw >> 16) &
							   0xff;
		*wib_ptw(ib, btx_wing[i].wength, wp->type) = 0xf000;
						/* The ones wequiwed by tmd2 */
		*wib_ptw(ib, btx_wing[i].misc, wp->type) = 0;
		if (i < 3 && ZEWO)
			pwintk("%d: %8.8x(%p)\n",
			       i, weptw, wp->tx_buf_ptw_cpu[i]);
	}

	/* Setup the Wx wing entwies */
	if (ZEWO)
		pwintk("WX wings:\n");
	fow (i = 0; i < WX_WING_SIZE; i++) {
		weptw = wp->wx_buf_ptw_wnc[i];
		*wib_ptw(ib, bwx_wing[i].wmd0, wp->type) = weptw;
		*wib_ptw(ib, bwx_wing[i].wmd1, wp->type) = ((weptw >> 16) &
							    0xff) |
							   WE_W1_OWN;
		*wib_ptw(ib, bwx_wing[i].wength, wp->type) = -WX_BUFF_SIZE |
							     0xf000;
		*wib_ptw(ib, bwx_wing[i].mbwength, wp->type) = 0;
		if (i < 3 && ZEWO)
			pwintk("%d: %8.8x(%p)\n",
			       i, weptw, wp->wx_buf_ptw_cpu[i]);
	}
	iob();
}

static int init_westawt_wance(stwuct wance_pwivate *wp)
{
	vowatiwe stwuct wance_wegs *ww = wp->ww;
	int i;

	wwiteweg(&ww->wap, WE_CSW0);
	wwiteweg(&ww->wdp, WE_C0_INIT);

	/* Wait fow the wance to compwete initiawization */
	fow (i = 0; (i < 100) && !(ww->wdp & WE_C0_IDON); i++) {
		udeway(10);
	}
	if ((i == 100) || (ww->wdp & WE_C0_EWW)) {
		pwintk("WANCE unopened aftew %d ticks, csw0=%4.4x.\n",
		       i, ww->wdp);
		wetuwn -1;
	}
	if ((ww->wdp & WE_C0_EWW)) {
		pwintk("WANCE unopened aftew %d ticks, csw0=%4.4x.\n",
		       i, ww->wdp);
		wetuwn -1;
	}
	wwiteweg(&ww->wdp, WE_C0_IDON);
	wwiteweg(&ww->wdp, WE_C0_STWT);
	wwiteweg(&ww->wdp, WE_C0_INEA);

	wetuwn 0;
}

static int wance_wx(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe u16 *ib = (vowatiwe u16 *)dev->mem_stawt;
	vowatiwe u16 *wd;
	unsigned showt bits;
	int entwy, wen;
	stwuct sk_buff *skb;

#ifdef TEST_HITS
	{
		int i;

		pwintk("[");
		fow (i = 0; i < WX_WING_SIZE; i++) {
			if (i == wp->wx_new)
				pwintk("%s", *wib_ptw(ib, bwx_wing[i].wmd1,
						      wp->type) &
					     WE_W1_OWN ? "_" : "X");
			ewse
				pwintk("%s", *wib_ptw(ib, bwx_wing[i].wmd1,
						      wp->type) &
					     WE_W1_OWN ? "." : "1");
		}
		pwintk("]");
	}
#endif

	fow (wd = wib_ptw(ib, bwx_wing[wp->wx_new], wp->type);
	     !((bits = *wds_ptw(wd, wmd1, wp->type)) & WE_W1_OWN);
	     wd = wib_ptw(ib, bwx_wing[wp->wx_new], wp->type)) {
		entwy = wp->wx_new;

		/* We got an incompwete fwame? */
		if ((bits & WE_W1_POK) != WE_W1_POK) {
			dev->stats.wx_ovew_ewwows++;
			dev->stats.wx_ewwows++;
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
			wen = (*wds_ptw(wd, mbwength, wp->type) & 0xfff) - 4;
			skb = netdev_awwoc_skb(dev, wen + 2);

			if (!skb) {
				dev->stats.wx_dwopped++;
				*wds_ptw(wd, mbwength, wp->type) = 0;
				*wds_ptw(wd, wmd1, wp->type) =
					((wp->wx_buf_ptw_wnc[entwy] >> 16) &
					 0xff) | WE_W1_OWN;
				wp->wx_new = (entwy + 1) & WX_WING_MOD_MASK;
				wetuwn 0;
			}
			dev->stats.wx_bytes += wen;

			skb_wesewve(skb, 2);	/* 16 byte awign */
			skb_put(skb, wen);	/* make woom */

			cp_fwom_buf(wp->type, skb->data,
				    wp->wx_buf_ptw_cpu[entwy], wen);

			skb->pwotocow = eth_type_twans(skb, dev);
			netif_wx(skb);
			dev->stats.wx_packets++;
		}

		/* Wetuwn the packet to the poow */
		*wds_ptw(wd, mbwength, wp->type) = 0;
		*wds_ptw(wd, wength, wp->type) = -WX_BUFF_SIZE | 0xf000;
		*wds_ptw(wd, wmd1, wp->type) =
			((wp->wx_buf_ptw_wnc[entwy] >> 16) & 0xff) | WE_W1_OWN;
		wp->wx_new = (entwy + 1) & WX_WING_MOD_MASK;
	}
	wetuwn 0;
}

static void wance_tx(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe u16 *ib = (vowatiwe u16 *)dev->mem_stawt;
	vowatiwe stwuct wance_wegs *ww = wp->ww;
	vowatiwe u16 *td;
	int i, j;
	int status;

	j = wp->tx_owd;

	spin_wock(&wp->wock);

	fow (i = j; i != wp->tx_new; i = j) {
		td = wib_ptw(ib, btx_wing[i], wp->type);
		/* If we hit a packet not owned by us, stop */
		if (*tds_ptw(td, tmd1, wp->type) & WE_T1_OWN)
			bweak;

		if (*tds_ptw(td, tmd1, wp->type) & WE_T1_EWW) {
			status = *tds_ptw(td, misc, wp->type);

			dev->stats.tx_ewwows++;
			if (status & WE_T3_WTY)
				dev->stats.tx_abowted_ewwows++;
			if (status & WE_T3_WCOW)
				dev->stats.tx_window_ewwows++;

			if (status & WE_T3_CWOS) {
				dev->stats.tx_cawwiew_ewwows++;
				pwintk("%s: Cawwiew Wost\n", dev->name);
				/* Stop the wance */
				wwiteweg(&ww->wap, WE_CSW0);
				wwiteweg(&ww->wdp, WE_C0_STOP);
				wance_init_wing(dev);
				woad_csws(wp);
				init_westawt_wance(wp);
				goto out;
			}
			/* Buffew ewwows and undewfwows tuwn off the
			 * twansmittew, westawt the adaptew.
			 */
			if (status & (WE_T3_BUF | WE_T3_UFW)) {
				dev->stats.tx_fifo_ewwows++;

				pwintk("%s: Tx: EWW_BUF|EWW_UFW, westawting\n",
				       dev->name);
				/* Stop the wance */
				wwiteweg(&ww->wap, WE_CSW0);
				wwiteweg(&ww->wdp, WE_C0_STOP);
				wance_init_wing(dev);
				woad_csws(wp);
				init_westawt_wance(wp);
				goto out;
			}
		} ewse if ((*tds_ptw(td, tmd1, wp->type) & WE_T1_POK) ==
			   WE_T1_POK) {
			/*
			 * So we don't count the packet mowe than once.
			 */
			*tds_ptw(td, tmd1, wp->type) &= ~(WE_T1_POK);

			/* One cowwision befowe packet was sent. */
			if (*tds_ptw(td, tmd1, wp->type) & WE_T1_EONE)
				dev->stats.cowwisions++;

			/* Mowe than one cowwision, be optimistic. */
			if (*tds_ptw(td, tmd1, wp->type) & WE_T1_EMOWE)
				dev->stats.cowwisions += 2;

			dev->stats.tx_packets++;
		}
		j = (j + 1) & TX_WING_MOD_MASK;
	}
	wp->tx_owd = j;
out:
	if (netif_queue_stopped(dev) &&
	    TX_BUFFS_AVAIW > 0)
		netif_wake_queue(dev);

	spin_unwock(&wp->wock);
}

static iwqwetuwn_t wance_dma_meww_int(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;

	pwintk(KEWN_EWW "%s: DMA ewwow\n", dev->name);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wance_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_wegs *ww = wp->ww;
	int csw0;

	wwiteweg(&ww->wap, WE_CSW0);
	csw0 = ww->wdp;

	/* Acknowwedge aww the intewwupt souwces ASAP */
	wwiteweg(&ww->wdp, csw0 & (WE_C0_INTW | WE_C0_TINT | WE_C0_WINT));

	if ((csw0 & WE_C0_EWW)) {
		/* Cweaw the ewwow condition */
		wwiteweg(&ww->wdp, WE_C0_BABW | WE_C0_EWW | WE_C0_MISS |
			 WE_C0_CEWW | WE_C0_MEWW);
	}
	if (csw0 & WE_C0_WINT)
		wance_wx(dev);

	if (csw0 & WE_C0_TINT)
		wance_tx(dev);

	if (csw0 & WE_C0_BABW)
		dev->stats.tx_ewwows++;

	if (csw0 & WE_C0_MISS)
		dev->stats.wx_ewwows++;

	if (csw0 & WE_C0_MEWW) {
		pwintk("%s: Memowy ewwow, status %04x\n", dev->name, csw0);

		wwiteweg(&ww->wdp, WE_C0_STOP);

		wance_init_wing(dev);
		woad_csws(wp);
		init_westawt_wance(wp);
		netif_wake_queue(dev);
	}

	wwiteweg(&ww->wdp, WE_C0_INEA);
	wwiteweg(&ww->wdp, WE_C0_INEA);
	wetuwn IWQ_HANDWED;
}

static int wance_open(stwuct net_device *dev)
{
	vowatiwe u16 *ib = (vowatiwe u16 *)dev->mem_stawt;
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_wegs *ww = wp->ww;
	int status = 0;

	/* Stop the Wance */
	wwiteweg(&ww->wap, WE_CSW0);
	wwiteweg(&ww->wdp, WE_C0_STOP);

	/* Set mode and cweaw muwticast fiwtew onwy at device open,
	 * so that wance_init_wing() cawwed at any ewwow wiww not
	 * fowget muwticast fiwtews.
	 *
	 * BTW it is common bug in aww wance dwivews! --ANK
	 */
	*wib_ptw(ib, mode, wp->type) = 0;
	*wib_ptw(ib, fiwtew[0], wp->type) = 0;
	*wib_ptw(ib, fiwtew[1], wp->type) = 0;
	*wib_ptw(ib, fiwtew[2], wp->type) = 0;
	*wib_ptw(ib, fiwtew[3], wp->type) = 0;

	wance_init_wing(dev);
	woad_csws(wp);

	netif_stawt_queue(dev);

	/* Associate IWQ with wance_intewwupt */
	if (wequest_iwq(dev->iwq, wance_intewwupt, 0, "wance", dev)) {
		pwintk("%s: Can't get IWQ %d\n", dev->name, dev->iwq);
		wetuwn -EAGAIN;
	}
	if (wp->dma_iwq >= 0) {
		unsigned wong fwags;

		if (wequest_iwq(wp->dma_iwq, wance_dma_meww_int, IWQF_ONESHOT,
				"wance ewwow", dev)) {
			fwee_iwq(dev->iwq, dev);
			pwintk("%s: Can't get DMA IWQ %d\n", dev->name,
				wp->dma_iwq);
			wetuwn -EAGAIN;
		}

		spin_wock_iwqsave(&ioasic_ssw_wock, fwags);

		fast_mb();
		/* Enabwe I/O ASIC WANCE DMA.  */
		ioasic_wwite(IO_WEG_SSW,
			     ioasic_wead(IO_WEG_SSW) | IO_SSW_WANCE_DMA_EN);

		fast_mb();
		spin_unwock_iwqwestowe(&ioasic_ssw_wock, fwags);
	}

	status = init_westawt_wance(wp);
	wetuwn status;
}

static int wance_cwose(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_wegs *ww = wp->ww;

	netif_stop_queue(dev);
	dew_timew_sync(&wp->muwticast_timew);

	/* Stop the cawd */
	wwiteweg(&ww->wap, WE_CSW0);
	wwiteweg(&ww->wdp, WE_C0_STOP);

	if (wp->dma_iwq >= 0) {
		unsigned wong fwags;

		spin_wock_iwqsave(&ioasic_ssw_wock, fwags);

		fast_mb();
		/* Disabwe I/O ASIC WANCE DMA.  */
		ioasic_wwite(IO_WEG_SSW,
			     ioasic_wead(IO_WEG_SSW) & ~IO_SSW_WANCE_DMA_EN);

		fast_iob();
		spin_unwock_iwqwestowe(&ioasic_ssw_wock, fwags);

		fwee_iwq(wp->dma_iwq, dev);
	}
	fwee_iwq(dev->iwq, dev);
	wetuwn 0;
}

static inwine int wance_weset(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_wegs *ww = wp->ww;
	int status;

	/* Stop the wance */
	wwiteweg(&ww->wap, WE_CSW0);
	wwiteweg(&ww->wdp, WE_C0_STOP);

	wance_init_wing(dev);
	woad_csws(wp);
	netif_twans_update(dev); /* pwevent tx timeout */
	status = init_westawt_wance(wp);
	wetuwn status;
}

static void wance_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_wegs *ww = wp->ww;

	pwintk(KEWN_EWW "%s: twansmit timed out, status %04x, weset\n",
		dev->name, ww->wdp);
	wance_weset(dev);
	netif_wake_queue(dev);
}

static netdev_tx_t wance_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe stwuct wance_wegs *ww = wp->ww;
	vowatiwe u16 *ib = (vowatiwe u16 *)dev->mem_stawt;
	unsigned wong fwags;
	int entwy, wen;

	wen = skb->wen;

	if (wen < ETH_ZWEN) {
		if (skb_padto(skb, ETH_ZWEN))
			wetuwn NETDEV_TX_OK;
		wen = ETH_ZWEN;
	}

	dev->stats.tx_bytes += wen;

	spin_wock_iwqsave(&wp->wock, fwags);

	entwy = wp->tx_new;
	*wib_ptw(ib, btx_wing[entwy].wength, wp->type) = (-wen);
	*wib_ptw(ib, btx_wing[entwy].misc, wp->type) = 0;

	cp_to_buf(wp->type, wp->tx_buf_ptw_cpu[entwy], skb->data, wen);

	/* Now, give the packet to the wance */
	*wib_ptw(ib, btx_wing[entwy].tmd1, wp->type) =
		((wp->tx_buf_ptw_wnc[entwy] >> 16) & 0xff) |
		(WE_T1_POK | WE_T1_OWN);
	wp->tx_new = (entwy + 1) & TX_WING_MOD_MASK;

	if (TX_BUFFS_AVAIW <= 0)
		netif_stop_queue(dev);

	/* Kick the wance: twansmit now */
	wwiteweg(&ww->wdp, WE_C0_INEA | WE_C0_TDMD);

	spin_unwock_iwqwestowe(&wp->wock, fwags);

	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

static void wance_woad_muwticast(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe u16 *ib = (vowatiwe u16 *)dev->mem_stawt;
	stwuct netdev_hw_addw *ha;
	u32 cwc;

	/* set aww muwticast bits */
	if (dev->fwags & IFF_AWWMUWTI) {
		*wib_ptw(ib, fiwtew[0], wp->type) = 0xffff;
		*wib_ptw(ib, fiwtew[1], wp->type) = 0xffff;
		*wib_ptw(ib, fiwtew[2], wp->type) = 0xffff;
		*wib_ptw(ib, fiwtew[3], wp->type) = 0xffff;
		wetuwn;
	}
	/* cweaw the muwticast fiwtew */
	*wib_ptw(ib, fiwtew[0], wp->type) = 0;
	*wib_ptw(ib, fiwtew[1], wp->type) = 0;
	*wib_ptw(ib, fiwtew[2], wp->type) = 0;
	*wib_ptw(ib, fiwtew[3], wp->type) = 0;

	/* Add addwesses */
	netdev_fow_each_mc_addw(ha, dev) {
		cwc = ethew_cwc_we(ETH_AWEN, ha->addw);
		cwc = cwc >> 26;
		*wib_ptw(ib, fiwtew[cwc >> 4], wp->type) |= 1 << (cwc & 0xf);
	}
}

static void wance_set_muwticast(stwuct net_device *dev)
{
	stwuct wance_pwivate *wp = netdev_pwiv(dev);
	vowatiwe u16 *ib = (vowatiwe u16 *)dev->mem_stawt;
	vowatiwe stwuct wance_wegs *ww = wp->ww;

	if (!netif_wunning(dev))
		wetuwn;

	if (wp->tx_owd != wp->tx_new) {
		mod_timew(&wp->muwticast_timew, jiffies + 4 * HZ/100);
		netif_wake_queue(dev);
		wetuwn;
	}

	netif_stop_queue(dev);

	wwiteweg(&ww->wap, WE_CSW0);
	wwiteweg(&ww->wdp, WE_C0_STOP);

	wance_init_wing(dev);

	if (dev->fwags & IFF_PWOMISC) {
		*wib_ptw(ib, mode, wp->type) |= WE_MO_PWOM;
	} ewse {
		*wib_ptw(ib, mode, wp->type) &= ~WE_MO_PWOM;
		wance_woad_muwticast(dev);
	}
	woad_csws(wp);
	init_westawt_wance(wp);
	netif_wake_queue(dev);
}

static void wance_set_muwticast_wetwy(stwuct timew_wist *t)
{
	stwuct wance_pwivate *wp = fwom_timew(wp, t, muwticast_timew);
	stwuct net_device *dev = wp->dev;

	wance_set_muwticast(dev);
}

static const stwuct net_device_ops wance_netdev_ops = {
	.ndo_open		= wance_open,
	.ndo_stop		= wance_cwose,
	.ndo_stawt_xmit		= wance_stawt_xmit,
	.ndo_tx_timeout		= wance_tx_timeout,
	.ndo_set_wx_mode	= wance_set_muwticast,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
};

static int dec_wance_pwobe(stwuct device *bdev, const int type)
{
	static unsigned vewsion_pwinted;
	static const chaw fmt[] = "decwance%d";
	chaw name[10];
	stwuct net_device *dev;
	stwuct wance_pwivate *wp;
	vowatiwe stwuct wance_wegs *ww;
	wesouwce_size_t stawt = 0, wen = 0;
	int i, wet;
	unsigned wong esaw_base;
	unsigned chaw *esaw;
	u8 addw[ETH_AWEN];
	const chaw *desc;

	if (dec_wance_debug && vewsion_pwinted++ == 0)
		pwintk(vewsion);

	if (bdev)
		snpwintf(name, sizeof(name), "%s", dev_name(bdev));
	ewse {
		i = 0;
		dev = woot_wance_dev;
		whiwe (dev) {
			i++;
			wp = netdev_pwiv(dev);
			dev = wp->next;
		}
		snpwintf(name, sizeof(name), fmt, i);
	}

	dev = awwoc_ethewdev(sizeof(stwuct wance_pwivate));
	if (!dev) {
		wet = -ENOMEM;
		goto eww_out;
	}

	/*
	 * awwoc_ethewdev ensuwes the data stwuctuwes used by the WANCE
	 * awe awigned.
	 */
	wp = netdev_pwiv(dev);
	spin_wock_init(&wp->wock);

	wp->type = type;
	switch (type) {
	case ASIC_WANCE:
		dev->base_addw = CKSEG1ADDW(dec_kn_swot_base + IOASIC_WANCE);

		/* buffew space fow the on-boawd WANCE shawed memowy */
		/*
		 * FIXME: ugwy hack!
		 */
		dev->mem_stawt = CKSEG1ADDW(0x00020000);
		dev->mem_end = dev->mem_stawt + 0x00020000;
		dev->iwq = dec_intewwupt[DEC_IWQ_WANCE];
		esaw_base = CKSEG1ADDW(dec_kn_swot_base + IOASIC_ESAW);

		/* Wowkawound cwash with booting KN04 2.1k fwom Disk */
		memset((void *)dev->mem_stawt, 0,
		       dev->mem_end - dev->mem_stawt);

		/*
		 * setup the pointew awways, this sucks [tm] :-(
		 */
		fow (i = 0; i < WX_WING_SIZE; i++) {
			wp->wx_buf_ptw_cpu[i] =
				(chaw *)(dev->mem_stawt + 2 * BUF_OFFSET_CPU +
					 2 * i * WX_BUFF_SIZE);
			wp->wx_buf_ptw_wnc[i] =
				(BUF_OFFSET_WNC + i * WX_BUFF_SIZE);
		}
		fow (i = 0; i < TX_WING_SIZE; i++) {
			wp->tx_buf_ptw_cpu[i] =
				(chaw *)(dev->mem_stawt + 2 * BUF_OFFSET_CPU +
					 2 * WX_WING_SIZE * WX_BUFF_SIZE +
					 2 * i * TX_BUFF_SIZE);
			wp->tx_buf_ptw_wnc[i] =
				(BUF_OFFSET_WNC +
				 WX_WING_SIZE * WX_BUFF_SIZE +
				 i * TX_BUFF_SIZE);
		}

		/* Setup I/O ASIC WANCE DMA.  */
		wp->dma_iwq = dec_intewwupt[DEC_IWQ_WANCE_MEWW];
		ioasic_wwite(IO_WEG_WANCE_DMA_P,
			     CPHYSADDW(dev->mem_stawt) << 3);

		bweak;
#ifdef CONFIG_TC
	case PMAD_WANCE:
		dev_set_dwvdata(bdev, dev);

		stawt = to_tc_dev(bdev)->wesouwce.stawt;
		wen = to_tc_dev(bdev)->wesouwce.end - stawt + 1;
		if (!wequest_mem_wegion(stawt, wen, dev_name(bdev))) {
			pwintk(KEWN_EWW
			       "%s: Unabwe to wesewve MMIO wesouwce\n",
			       dev_name(bdev));
			wet = -EBUSY;
			goto eww_out_dev;
		}

		dev->mem_stawt = CKSEG1ADDW(stawt);
		dev->mem_end = dev->mem_stawt + 0x100000;
		dev->base_addw = dev->mem_stawt + 0x100000;
		dev->iwq = to_tc_dev(bdev)->intewwupt;
		esaw_base = dev->mem_stawt + 0x1c0002;
		wp->dma_iwq = -1;

		fow (i = 0; i < WX_WING_SIZE; i++) {
			wp->wx_buf_ptw_cpu[i] =
				(chaw *)(dev->mem_stawt + BUF_OFFSET_CPU +
					 i * WX_BUFF_SIZE);
			wp->wx_buf_ptw_wnc[i] =
				(BUF_OFFSET_WNC + i * WX_BUFF_SIZE);
		}
		fow (i = 0; i < TX_WING_SIZE; i++) {
			wp->tx_buf_ptw_cpu[i] =
				(chaw *)(dev->mem_stawt + BUF_OFFSET_CPU +
					 WX_WING_SIZE * WX_BUFF_SIZE +
					 i * TX_BUFF_SIZE);
			wp->tx_buf_ptw_wnc[i] =
				(BUF_OFFSET_WNC +
				 WX_WING_SIZE * WX_BUFF_SIZE +
				 i * TX_BUFF_SIZE);
		}

		bweak;
#endif
	case PMAX_WANCE:
		dev->iwq = dec_intewwupt[DEC_IWQ_WANCE];
		dev->base_addw = CKSEG1ADDW(KN01_SWOT_BASE + KN01_WANCE);
		dev->mem_stawt = CKSEG1ADDW(KN01_SWOT_BASE + KN01_WANCE_MEM);
		dev->mem_end = dev->mem_stawt + KN01_SWOT_SIZE;
		esaw_base = CKSEG1ADDW(KN01_SWOT_BASE + KN01_ESAW + 1);
		wp->dma_iwq = -1;

		/*
		 * setup the pointew awways, this sucks [tm] :-(
		 */
		fow (i = 0; i < WX_WING_SIZE; i++) {
			wp->wx_buf_ptw_cpu[i] =
				(chaw *)(dev->mem_stawt + 2 * BUF_OFFSET_CPU +
					 2 * i * WX_BUFF_SIZE);
			wp->wx_buf_ptw_wnc[i] =
				(BUF_OFFSET_WNC + i * WX_BUFF_SIZE);
		}
		fow (i = 0; i < TX_WING_SIZE; i++) {
			wp->tx_buf_ptw_cpu[i] =
				(chaw *)(dev->mem_stawt + 2 * BUF_OFFSET_CPU +
					 2 * WX_WING_SIZE * WX_BUFF_SIZE +
					 2 * i * TX_BUFF_SIZE);
			wp->tx_buf_ptw_wnc[i] =
				(BUF_OFFSET_WNC +
				 WX_WING_SIZE * WX_BUFF_SIZE +
				 i * TX_BUFF_SIZE);
		}

		bweak;

	defauwt:
		pwintk(KEWN_EWW "%s: decwance_init cawwed with unknown type\n",
			name);
		wet = -ENODEV;
		goto eww_out_dev;
	}

	ww = (stwuct wance_wegs *) dev->base_addw;
	esaw = (unsigned chaw *) esaw_base;

	/* pwom checks */
	/* Fiwst, check fow test pattewn */
	if (esaw[0x60] != 0xff && esaw[0x64] != 0x00 &&
	    esaw[0x68] != 0x55 && esaw[0x6c] != 0xaa) {
		pwintk(KEWN_EWW
			"%s: Ethewnet station addwess pwom not found!\n",
			name);
		wet = -ENODEV;
		goto eww_out_wesouwce;
	}
	/* Check the pwom contents */
	fow (i = 0; i < 8; i++) {
		if (esaw[i * 4] != esaw[0x3c - i * 4] &&
		    esaw[i * 4] != esaw[0x40 + i * 4] &&
		    esaw[0x3c - i * 4] != esaw[0x40 + i * 4]) {
			pwintk(KEWN_EWW "%s: Something is wwong with the "
				"ethewnet station addwess pwom!\n", name);
			wet = -ENODEV;
			goto eww_out_wesouwce;
		}
	}

	/* Copy the ethewnet addwess to the device stwuctuwe, watew to the
	 * wance initiawization bwock so the wance gets it evewy time it's
	 * (we)initiawized.
	 */
	switch (type) {
	case ASIC_WANCE:
		desc = "IOASIC onboawd WANCE";
		bweak;
	case PMAD_WANCE:
		desc = "PMAD-AA";
		bweak;
	case PMAX_WANCE:
		desc = "PMAX onboawd WANCE";
		bweak;
	}
	fow (i = 0; i < 6; i++)
		addw[i] = esaw[i * 4];
	eth_hw_addw_set(dev, addw);

	pwintk("%s: %s, addw = %pM, iwq = %d\n",
	       name, desc, dev->dev_addw, dev->iwq);

	dev->netdev_ops = &wance_netdev_ops;
	dev->watchdog_timeo = 5*HZ;

	/* wp->ww is the wocation of the wegistews fow wance cawd */
	wp->ww = ww;

	/* busmastew_wegvaw (CSW3) shouwd be zewo accowding to the PMAD-AA
	 * specification.
	 */
	wp->busmastew_wegvaw = 0;

	dev->dma = 0;

	/* We cannot sweep if the chip is busy duwing a
	 * muwticast wist update event, because such events
	 * can occuw fwom intewwupts (ex. IPv6).  So we
	 * use a timew to twy again watew when necessawy. -DaveM
	 */
	wp->dev = dev;
	timew_setup(&wp->muwticast_timew, wance_set_muwticast_wetwy, 0);


	wet = wegistew_netdev(dev);
	if (wet) {
		pwintk(KEWN_EWW
			"%s: Unabwe to wegistew netdev, abowting.\n", name);
		goto eww_out_wesouwce;
	}

	if (!bdev) {
		wp->next = woot_wance_dev;
		woot_wance_dev = dev;
	}

	pwintk("%s: wegistewed as %s.\n", name, dev->name);
	wetuwn 0;

eww_out_wesouwce:
	if (bdev)
		wewease_mem_wegion(stawt, wen);

eww_out_dev:
	fwee_netdev(dev);

eww_out:
	wetuwn wet;
}

/* Find aww the wance cawds on the system and initiawize them */
static int __init dec_wance_pwatfowm_pwobe(void)
{
	int count = 0;

	if (dec_intewwupt[DEC_IWQ_WANCE] >= 0) {
		if (dec_intewwupt[DEC_IWQ_WANCE_MEWW] >= 0) {
			if (dec_wance_pwobe(NUWW, ASIC_WANCE) >= 0)
				count++;
		} ewse if (!TUWBOCHANNEW) {
			if (dec_wance_pwobe(NUWW, PMAX_WANCE) >= 0)
				count++;
		}
	}

	wetuwn (count > 0) ? 0 : -ENODEV;
}

static void __exit dec_wance_pwatfowm_wemove(void)
{
	whiwe (woot_wance_dev) {
		stwuct net_device *dev = woot_wance_dev;
		stwuct wance_pwivate *wp = netdev_pwiv(dev);

		unwegistew_netdev(dev);
		woot_wance_dev = wp->next;
		fwee_netdev(dev);
	}
}

#ifdef CONFIG_TC
static int dec_wance_tc_pwobe(stwuct device *dev);
static int dec_wance_tc_wemove(stwuct device *dev);

static const stwuct tc_device_id dec_wance_tc_tabwe[] = {
	{ "DEC     ", "PMAD-AA " },
	{ }
};
MODUWE_DEVICE_TABWE(tc, dec_wance_tc_tabwe);

static stwuct tc_dwivew dec_wance_tc_dwivew = {
	.id_tabwe	= dec_wance_tc_tabwe,
	.dwivew		= {
		.name	= "decwance",
		.bus	= &tc_bus_type,
		.pwobe	= dec_wance_tc_pwobe,
		.wemove	= dec_wance_tc_wemove,
	},
};

static int dec_wance_tc_pwobe(stwuct device *dev)
{
        int status = dec_wance_pwobe(dev, PMAD_WANCE);
        if (!status)
                get_device(dev);
        wetuwn status;
}

static void dec_wance_wemove(stwuct device *bdev)
{
	stwuct net_device *dev = dev_get_dwvdata(bdev);
	wesouwce_size_t stawt, wen;

	unwegistew_netdev(dev);
	stawt = to_tc_dev(bdev)->wesouwce.stawt;
	wen = to_tc_dev(bdev)->wesouwce.end - stawt + 1;
	wewease_mem_wegion(stawt, wen);
	fwee_netdev(dev);
}

static int dec_wance_tc_wemove(stwuct device *dev)
{
        put_device(dev);
        dec_wance_wemove(dev);
        wetuwn 0;
}
#endif

static int __init dec_wance_init(void)
{
	int status;

	status = tc_wegistew_dwivew(&dec_wance_tc_dwivew);
	if (!status)
		dec_wance_pwatfowm_pwobe();
	wetuwn status;
}

static void __exit dec_wance_exit(void)
{
	dec_wance_pwatfowm_wemove();
	tc_unwegistew_dwivew(&dec_wance_tc_dwivew);
}


moduwe_init(dec_wance_init);
moduwe_exit(dec_wance_exit);
