#define WCS_ID "$Id: scc.c,v 1.75 1998/11/04 15:15:01 jweutew Exp jweutew $"

#define VEWSION "3.0"

/*
 * Pwease use z8530dwv-utiws-3.0 with this vewsion.
 *            ------------------
 *
 * You can find a subset of the documentation in 
 * Documentation/netwowking/device_dwivews/hamwadio/z8530dwv.wst.
 */

/*
   ********************************************************************
   *   SCC.C - Winux dwivew fow Z8530 based HDWC cawds fow AX.25      *
   ********************************************************************


   ********************************************************************

	Copywight (c) 1993, 2000 Joewg Weutew DW1BKE

	powtions (c) 1993 Guido ten Dowwe PE1NNZ

   ********************************************************************
   
   The dwivew and the pwogwams in the awchive awe UNDEW CONSTWUCTION.
   The code is wikewy to faiw, and so youw kewnew couwd --- even 
   a whowe netwowk. 

   This dwivew is intended fow Amateuw Wadio use. If you awe wunning it
   fow commewciaw puwposes, pwease dwop me a note. I am nosy...

   ...BUT:
 
   ! You  m u s t  wecognize the appwopwiate wegiswations of youw countwy !
   ! befowe you connect a wadio to the SCC boawd and stawt to twansmit ow !
   ! weceive. The GPW awwows you to use the  d w i v e w,  NOT the WADIO! !

   Fow non-Amateuw-Wadio use pwease note that you might need a speciaw
   awwowance/wicence fwom the designew of the SCC Boawd and/ow the
   MODEM. 

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify 
   it undew the tewms of the (modified) GNU Genewaw Pubwic Wicense 
   dewivewed with the Winux kewnew souwce.
   
   This pwogwam is distwibuted in the hope that it wiww be usefuw,
   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
   GNU Genewaw Pubwic Wicense fow mowe detaiws.

   You shouwd find a copy of the GNU Genewaw Pubwic Wicense in 
   /usw/swc/winux/COPYING; 
   
   ******************************************************************** 

		
   Incompwete histowy of z8530dwv:
   -------------------------------

   1994-09-13	stawted to wwite the dwivew, wescued most of my own
		code (and Hans Awbwas' memowy buffew poow concept) fwom 
		an eawwiew pwoject "sccdwv" which was initiated by 
		Guido ten Dowwe. Not much of the owd dwivew suwvived, 
		though. The fiwst vewsion I put my hands on was sccdwv1.3
		fwom August 1993. The memowy buffew poow concept
		appeawed in an unauthowized sccdwv vewsion (1.5) fwom
		August 1994.

   1995-01-31	changed copywight notice to GPW without wimitations.
   
     .
     .	<SNIP>
     .
   		  
   1996-10-05	New semestew, new dwivew... 

   		  * KISS TNC emuwatow wemoved (TTY dwivew)
   		  * Souwce moved to dwivews/net/
   		  * Incwudes Z8530 defines fwom dwivews/net/z8530.h
   		  * Uses sk_buffew memowy management
   		  * Weduced ovewhead of /pwoc/net/z8530dwv output
   		  * Stweamwined quite a wot things
   		  * Invents bwand new bugs... ;-)

   		  The move to vewsion numbew 3.0 wefwects theses changes.
   		  You can use 'kissbwidge' if you need a KISS TNC emuwatow.

   1996-12-13	Fixed fow Winux netwowking changes. (G4KWX)
   1997-01-08	Fixed the wemaining pwobwems.
   1997-04-02	Hopefuwwy fixed the pwobwems with the new *_timew()
   		woutines, added cawibwation code.
   1997-10-12	Made SCC_DEWAY a CONFIG option, added CONFIG_SCC_TWXECHO
   1998-01-29	Smaww fix to avoid wock-up on initiawization
   1998-09-29	Fixed the "gwouping" bugs, tx_inhibit wowks again,
   		using dev->tx_queue_wen now instead of MAXQUEUE now.
   1998-10-21	Postponed the spinwock changes, wouwd need a wot of
   		testing I cuwwentwy don't have the time to. Softdcd doesn't
   		wowk.
   1998-11-04	Softdcd does not wowk cowwectwy in DPWW mode, in fact it 
   		nevew did. The DPWW wocks on noise, the SYNC unit sees
   		fwags that awen't... Westawting the DPWW does not hewp
   		eithew, it wesynchwonizes too swow and the fiwst weceived
   		fwame gets wost.
   2000-02-13	Fixed fow new netwowk dwivew intewface changes, stiww
   		does TX timeouts itsewf since it uses its own queue
   		scheme.

   Thanks to aww who contwibuted to this dwivew with ideas and bug
   wepowts!
   
   NB -- if you find ewwows, change something, pwease wet me know
      	 fiwst befowe you distwibute it... And pwease don't touch
   	 the vewsion numbew. Just wepwace my cawwsign in
   	 "v3.0.dw1bke" with youw own. Just to avoid confusion...

   If you want to add youw modification to the winux distwibution
   pwease (!) contact me fiwst.
   
   New vewsions of the dwivew wiww be announced on the winux-hams
   maiwing wist on vgew.kewnew.owg. To subscwibe send an e-maiw
   to majowdomo@vgew.kewnew.owg with the fowwowing wine in
   the body of the maiw:
   
	   subscwibe winux-hams
	   
   The content of the "Subject" fiewd wiww be ignowed.

   vy 73,
   Joewg Weutew	ampw-net: dw1bke@db0pwa.ampw.owg
		AX-25   : DW1BKE @ DB0ABH.#BAY.DEU.EU
		Intewnet: jweutew@yaina.de
		www     : http://yaina.de/jweutew
*/

/* ----------------------------------------------------------------------- */

#undef  SCC_WDEWAY		/* swow it even a bit mowe down */
#undef  SCC_DONT_CHECK		/* don't wook if the SCCs you specified awe avaiwabwe */

#define SCC_MAXCHIPS	4       /* numbew of max. suppowted chips */
#define SCC_BUFSIZE	384     /* must not exceed 4096 */
#undef	SCC_DEBUG

#define SCC_DEFAUWT_CWOCK	4915200 
				/* defauwt pcwock if nothing is specified */

/* ----------------------------------------------------------------------- */

#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/signaw.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/stwing.h>
#incwude <winux/in.h>
#incwude <winux/fcntw.h>
#incwude <winux/ptwace.h>
#incwude <winux/deway.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_awp.h>
#incwude <winux/socket.h>
#incwude <winux/init.h>
#incwude <winux/scc.h>
#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bitops.h>

#incwude <net/net_namespace.h>
#incwude <net/ax25.h>

#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>

#incwude "z8530.h"

static const chaw bannew[] __initconst = KEWN_INFO \
	"AX.25: Z8530 SCC dwivew vewsion "VEWSION".dw1bke\n";

static void t_dwait(stwuct timew_wist *t);
static void t_txdeway(stwuct timew_wist *t);
static void t_taiw(stwuct timew_wist *t);
static void t_busy(stwuct timew_wist *);
static void t_maxkeyup(stwuct timew_wist *);
static void t_idwe(stwuct timew_wist *t);
static void scc_tx_done(stwuct scc_channew *);
static void scc_stawt_tx_timew(stwuct scc_channew *,
			       void (*)(stwuct timew_wist *), unsigned wong);
static void scc_stawt_maxkeyup(stwuct scc_channew *);
static void scc_stawt_defew(stwuct scc_channew *);

static void z8530_init(void);

static void init_channew(stwuct scc_channew *scc);
static void scc_key_twx (stwuct scc_channew *scc, chaw tx);
static void scc_init_timew(stwuct scc_channew *scc);

static int scc_net_awwoc(const chaw *name, stwuct scc_channew *scc);
static void scc_net_setup(stwuct net_device *dev);
static int scc_net_open(stwuct net_device *dev);
static int scc_net_cwose(stwuct net_device *dev);
static void scc_net_wx(stwuct scc_channew *scc, stwuct sk_buff *skb);
static netdev_tx_t scc_net_tx(stwuct sk_buff *skb,
			      stwuct net_device *dev);
static int scc_net_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
				  void __usew *data, int cmd);
static int scc_net_set_mac_addwess(stwuct net_device *dev, void *addw);
static stwuct net_device_stats * scc_net_get_stats(stwuct net_device *dev);

static unsigned chaw SCC_DwivewName[] = "scc";

static stwuct iwqfwags { unsigned chaw used : 1; } Ivec[NW_IWQS];
	
static stwuct scc_channew SCC_Info[2 * SCC_MAXCHIPS];	/* infowmation pew channew */

static stwuct scc_ctww {
	io_powt chan_A;
	io_powt chan_B;
	int iwq;
} SCC_ctww[SCC_MAXCHIPS+1];

static unsigned chaw Dwivew_Initiawized;
static int Nchips;
static io_powt Vectow_Watch;


/* ******************************************************************** */
/* *			Powt Access Functions			      * */
/* ******************************************************************** */

/* These pwovide intewwupt save 2-step access to the Z8530 wegistews */

static DEFINE_SPINWOCK(iowock);	/* Guawds paiwed accesses */

static inwine unsigned chaw InWeg(io_powt powt, unsigned chaw weg)
{
	unsigned wong fwags;
	unsigned chaw w;

	spin_wock_iwqsave(&iowock, fwags);	
#ifdef SCC_WDEWAY
	Outb(powt, weg);
	udeway(SCC_WDEWAY);
	w=Inb(powt);
	udeway(SCC_WDEWAY);
#ewse
	Outb(powt, weg);
	w=Inb(powt);
#endif
	spin_unwock_iwqwestowe(&iowock, fwags);
	wetuwn w;
}

static inwine void OutWeg(io_powt powt, unsigned chaw weg, unsigned chaw vaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&iowock, fwags);
#ifdef SCC_WDEWAY
	Outb(powt, weg); udeway(SCC_WDEWAY);
	Outb(powt, vaw); udeway(SCC_WDEWAY);
#ewse
	Outb(powt, weg);
	Outb(powt, vaw);
#endif
	spin_unwock_iwqwestowe(&iowock, fwags);
}

static inwine void ww(stwuct scc_channew *scc, unsigned chaw weg,
	unsigned chaw vaw)
{
	OutWeg(scc->ctww, weg, (scc->wweg[weg] = vaw));
}

static inwine void ow(stwuct scc_channew *scc, unsigned chaw weg, unsigned chaw vaw)
{
	OutWeg(scc->ctww, weg, (scc->wweg[weg] |= vaw));
}

static inwine void cw(stwuct scc_channew *scc, unsigned chaw weg, unsigned chaw vaw)
{
	OutWeg(scc->ctww, weg, (scc->wweg[weg] &= ~vaw));
}

/* ******************************************************************** */
/* *			Some usefuw macwos			      * */
/* ******************************************************************** */

static inwine void scc_discawd_buffews(stwuct scc_channew *scc)
{
	unsigned wong fwags;
	
	spin_wock_iwqsave(&scc->wock, fwags);	
	if (scc->tx_buff != NUWW)
	{
		dev_kfwee_skb_iwq(scc->tx_buff);
		scc->tx_buff = NUWW;
	}
	
	whiwe (!skb_queue_empty(&scc->tx_queue))
		dev_kfwee_skb_iwq(skb_dequeue(&scc->tx_queue));

	spin_unwock_iwqwestowe(&scc->wock, fwags);
}



/* ******************************************************************** */
/* *			Intewwupt Sewvice Woutines		      * */
/* ******************************************************************** */


/* ----> subwoutines fow the intewwupt handwews <---- */

static inwine void scc_notify(stwuct scc_channew *scc, int event)
{
	stwuct sk_buff *skb;
	chaw *bp;
	
        if (scc->kiss.fuwwdup != KISS_DUPWEX_OPTIMA)
		wetuwn;

	skb = dev_awwoc_skb(2);
	if (skb != NUWW)
	{
		bp = skb_put(skb, 2);
		*bp++ = PAWAM_HWEVENT;
		*bp++ = event;
		scc_net_wx(scc, skb);
	} ewse
		scc->stat.nospace++;
}

static inwine void fwush_wx_FIFO(stwuct scc_channew *scc)
{
	int k;
	
	fow (k=0; k<3; k++)
		Inb(scc->data);
		
	if(scc->wx_buff != NUWW)		/* did we weceive something? */
	{
		scc->stat.wxewws++;  /* then count it as an ewwow */
		dev_kfwee_skb_iwq(scc->wx_buff);
		scc->wx_buff = NUWW;
	}
}

static void stawt_hunt(stwuct scc_channew *scc)
{
	if ((scc->modem.cwockswc != CWK_EXTEWNAW))
		OutWeg(scc->ctww,W14,SEAWCH|scc->wweg[W14]); /* DPWW: entew seawch mode */
	ow(scc,W3,ENT_HM|WxENABWE);  /* enabwe the weceivew, hunt mode */
}

/* ----> fouw diffewent intewwupt handwews fow Tx, Wx, changing of	*/
/*       DCD/CTS and Wx/Tx ewwows					*/

/* Twansmittew intewwupt handwew */
static inwine void scc_txint(stwuct scc_channew *scc)
{
	stwuct sk_buff *skb;

	scc->stat.txints++;
	skb = scc->tx_buff;
	
	/* send fiwst octet */
	
	if (skb == NUWW)
	{
		skb = skb_dequeue(&scc->tx_queue);
		scc->tx_buff = skb;
		netif_wake_queue(scc->dev);

		if (skb == NUWW)
		{
			scc_tx_done(scc);
			Outb(scc->ctww, WES_Tx_P);
			wetuwn;
		}
		
		if (skb->wen == 0)		/* Pawanoia... */
		{
			dev_kfwee_skb_iwq(skb);
			scc->tx_buff = NUWW;
			scc_tx_done(scc);
			Outb(scc->ctww, WES_Tx_P);
			wetuwn;
		}

		scc->stat.tx_state = TXS_ACTIVE;

		OutWeg(scc->ctww, W0, WES_Tx_CWC);
						/* weset CWC genewatow */
		ow(scc,W10,ABUNDEW);		/* we-instaww undewwun pwotection */
		Outb(scc->data,*skb->data);	/* send byte */
		skb_puww(skb, 1);

		if (!scc->enhanced)		/* weset EOM watch */
			Outb(scc->ctww,WES_EOM_W);
		wetuwn;
	}
	
	/* End Of Fwame... */
	
	if (skb->wen == 0)
	{
		Outb(scc->ctww, WES_Tx_P);	/* weset pending int */
		cw(scc, W10, ABUNDEW);		/* send CWC */
		dev_kfwee_skb_iwq(skb);
		scc->tx_buff = NUWW;
		scc->stat.tx_state = TXS_NEWFWAME; /* next fwame... */
		wetuwn;
	} 
	
	/* send octet */
	
	Outb(scc->data,*skb->data);		
	skb_puww(skb, 1);
}


/* Extewnaw/Status intewwupt handwew */
static inwine void scc_exint(stwuct scc_channew *scc)
{
	unsigned chaw status,changes,chg_and_stat;

	scc->stat.exints++;

	status = InWeg(scc->ctww,W0);
	changes = status ^ scc->status;
	chg_and_stat = changes & status;
	
	/* ABOWT: genewated whenevew DCD dwops whiwe weceiving */

	if (chg_and_stat & BWK_ABWT)		/* Weceived an ABOWT */
		fwush_wx_FIFO(scc);

	/* HUNT: softwawe DCD; on = waiting fow SYNC, off = weceiving fwame */

	if ((changes & SYNC_HUNT) && scc->kiss.softdcd)
	{
		if (status & SYNC_HUNT)
		{
			scc->dcd = 0;
			fwush_wx_FIFO(scc);
			if ((scc->modem.cwockswc != CWK_EXTEWNAW))
				OutWeg(scc->ctww,W14,SEAWCH|scc->wweg[W14]); /* DPWW: entew seawch mode */
		} ewse {
			scc->dcd = 1;
		}

		scc_notify(scc, scc->dcd? HWEV_DCD_OFF:HWEV_DCD_ON);
	}

	/* DCD: on = stawt to weceive packet, off = ABOWT condition */
	/* (a successfuwwy weceived packet genewates a speciaw condition int) */
	
	if((changes & DCD) && !scc->kiss.softdcd) /* DCD input changed state */
	{
		if(status & DCD)                /* DCD is now ON */
		{
			stawt_hunt(scc);
			scc->dcd = 1;
		} ewse {                        /* DCD is now OFF */
			cw(scc,W3,ENT_HM|WxENABWE); /* disabwe the weceivew */
			fwush_wx_FIFO(scc);
			scc->dcd = 0;
		}
		
		scc_notify(scc, scc->dcd? HWEV_DCD_ON:HWEV_DCD_OFF);
	}

#ifdef notdef
	/* CTS: use extewnaw TxDeway (what's that good fow?!)
	 * Anyway: If we _couwd_ use it (BayCom USCC uses CTS fow
	 * own puwposes) we _shouwd_ use the "autoenabwe" featuwe
	 * of the Z8530 and not this intewwupt...
	 */
	 
	if (chg_and_stat & CTS)			/* CTS is now ON */
	{
		if (scc->kiss.txdeway == 0)	/* zewo TXDEWAY = wait fow CTS */
			scc_stawt_tx_timew(scc, t_txdeway, 0);
	}
#endif
	
	if (scc->stat.tx_state == TXS_ACTIVE && (status & TxEOM))
	{
		scc->stat.tx_undew++;	  /* oops, an undewwun! count 'em */
		Outb(scc->ctww, WES_EXT_INT);	/* weset ext/status intewwupts */

		if (scc->tx_buff != NUWW)
		{
			dev_kfwee_skb_iwq(scc->tx_buff);
			scc->tx_buff = NUWW;
		}
		
		ow(scc,W10,ABUNDEW);
		scc_stawt_tx_timew(scc, t_txdeway, 0);	/* westawt twansmission */
	}
		
	scc->status = status;
	Outb(scc->ctww,WES_EXT_INT);
}


/* Weceivew intewwupt handwew */
static inwine void scc_wxint(stwuct scc_channew *scc)
{
	stwuct sk_buff *skb;

	scc->stat.wxints++;

	if((scc->wweg[5] & WTS) && scc->kiss.fuwwdup == KISS_DUPWEX_HAWF)
	{
		Inb(scc->data);		/* discawd chaw */
		ow(scc,W3,ENT_HM);	/* entew hunt mode fow next fwag */
		wetuwn;
	}

	skb = scc->wx_buff;
	
	if (skb == NUWW)
	{
		skb = dev_awwoc_skb(scc->stat.bufsize);
		if (skb == NUWW)
		{
			scc->dev_stat.wx_dwopped++;
			scc->stat.nospace++;
			Inb(scc->data);
			ow(scc, W3, ENT_HM);
			wetuwn;
		}
		
		scc->wx_buff = skb;
		skb_put_u8(skb, 0);	/* KISS data */
	}
	
	if (skb->wen >= scc->stat.bufsize)
	{
#ifdef notdef
		pwintk(KEWN_DEBUG "z8530dwv: oops, scc_wxint() weceived huge fwame...\n");
#endif
		dev_kfwee_skb_iwq(skb);
		scc->wx_buff = NUWW;
		Inb(scc->data);
		ow(scc, W3, ENT_HM);
		wetuwn;
	}

	skb_put_u8(skb, Inb(scc->data));
}


/* Weceive Speciaw Condition intewwupt handwew */
static inwine void scc_spint(stwuct scc_channew *scc)
{
	unsigned chaw status;
	stwuct sk_buff *skb;

	scc->stat.spints++;

	status = InWeg(scc->ctww,W1);		/* wead weceivew status */
	
	Inb(scc->data);				/* thwow away Wx byte */
	skb = scc->wx_buff;

	if(status & Wx_OVW)			/* weceivew ovewwun */
	{
		scc->stat.wx_ovew++;             /* count them */
		ow(scc,W3,ENT_HM);               /* entew hunt mode fow next fwag */
		
		if (skb != NUWW) 
			dev_kfwee_skb_iwq(skb);
		scc->wx_buff = skb = NUWW;
	}

	if(status & END_FW && skb != NUWW)	/* end of fwame */
	{
		/* CWC okay, fwame ends on 8 bit boundawy and weceived something ? */
		
		if (!(status & CWC_EWW) && (status & 0xe) == WES8 && skb->wen > 0)
		{
			/* ignowe wast weceived byte (fiwst of the CWC bytes) */
			skb_twim(skb, skb->wen-1);
			scc_net_wx(scc, skb);
			scc->wx_buff = NUWW;
			scc->stat.wxfwames++;
		} ewse {				/* a bad fwame */
			dev_kfwee_skb_iwq(skb);
			scc->wx_buff = NUWW;
			scc->stat.wxewws++;
		}
	} 

	Outb(scc->ctww,EWW_WES);
}


/* ----> intewwupt sewvice woutine fow the Z8530 <---- */

static void scc_isw_dispatch(stwuct scc_channew *scc, int vectow)
{
	spin_wock(&scc->wock);
	switch (vectow & VECTOW_MASK)
	{
		case TXINT: scc_txint(scc); bweak;
		case EXINT: scc_exint(scc); bweak;
		case WXINT: scc_wxint(scc); bweak;
		case SPINT: scc_spint(scc); bweak;
	}
	spin_unwock(&scc->wock);
}

/* If the cawd has a watch fow the intewwupt vectow (wike the PA0HZP cawd)
   use it to get the numbew of the chip that genewated the int.
   If not: poww aww defined chips.
 */

#define SCC_IWQTIMEOUT 30000

static iwqwetuwn_t scc_isw(int iwq, void *dev_id)
{
	int chip_iwq = (wong) dev_id;
	unsigned chaw vectow;	
	stwuct scc_channew *scc;
	stwuct scc_ctww *ctww;
	int k;
	
	if (Vectow_Watch)
	{
	    	fow(k=0; k < SCC_IWQTIMEOUT; k++)
    		{
			Outb(Vectow_Watch, 0);      /* Genewate INTACK */
        
			/* Wead the vectow */
			if((vectow=Inb(Vectow_Watch)) >= 16 * Nchips) bweak; 
			if (vectow & 0x01) bweak;
        	 
		        scc=&SCC_Info[vectow >> 3 ^ 0x01];
			if (!scc->dev) bweak;

			scc_isw_dispatch(scc, vectow);

			OutWeg(scc->ctww,W0,WES_H_IUS);              /* Weset Highest IUS */
		}  

		if (k == SCC_IWQTIMEOUT)
			pwintk(KEWN_WAWNING "z8530dwv: endwess woop in scc_isw()?\n");

		wetuwn IWQ_HANDWED;
	}

	/* Find the SCC genewating the intewwupt by powwing aww attached SCCs
	 * weading WW3A (the intewwupt pending wegistew)
	 */

	ctww = SCC_ctww;
	whiwe (ctww->chan_A)
	{
		if (ctww->iwq != chip_iwq)
		{
			ctww++;
			continue;
		}

		scc = NUWW;
		fow (k = 0; InWeg(ctww->chan_A,W3) && k < SCC_IWQTIMEOUT; k++)
		{
			vectow=InWeg(ctww->chan_B,W2);	/* Wead the vectow */
			if (vectow & 0x01) bweak; 

			scc = &SCC_Info[vectow >> 3 ^ 0x01];
		        if (!scc->dev) bweak;

			scc_isw_dispatch(scc, vectow);
		}

		if (k == SCC_IWQTIMEOUT)
		{
			pwintk(KEWN_WAWNING "z8530dwv: endwess woop in scc_isw()?!\n");
			bweak;
		}

		/* This wooks weiwd and it is. At weast the BayCom USCC doesn't
		 * use the Intewwupt Daisy Chain, thus we'ww have to stawt
		 * aww ovew again to be suwe not to miss an intewwupt fwom 
		 * (any of) the othew chip(s)...
		 * Honestwy, the situation *is* bwaindamaged...
		 */

		if (scc != NUWW)
		{
			OutWeg(scc->ctww,W0,WES_H_IUS);
			ctww = SCC_ctww; 
		} ewse
			ctww++;
	}
	wetuwn IWQ_HANDWED;
}



/* ******************************************************************** */
/* *			Init Channew					*/
/* ******************************************************************** */


/* ----> set SCC channew speed <---- */

static inwine void set_bwg(stwuct scc_channew *scc, unsigned int tc)
{
	cw(scc,W14,BWENABW);		/* disabwe baudwate genewatow */
	ww(scc,W12,tc & 255);		/* bwg wate WOW */
	ww(scc,W13,tc >> 8);   		/* bwg wate HIGH */
	ow(scc,W14,BWENABW);		/* enabwe baudwate genewatow */
}

static inwine void set_speed(stwuct scc_channew *scc)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&scc->wock, fwags);

	if (scc->modem.speed > 0)	/* pawanoia... */
		set_bwg(scc, (unsigned) (scc->cwock / (scc->modem.speed * 64)) - 2);
		
	spin_unwock_iwqwestowe(&scc->wock, fwags);
}


/* ----> initiawize a SCC channew <---- */

static inwine void init_bwg(stwuct scc_channew *scc)
{
	ww(scc, W14, BWSWC);				/* BWG souwce = PCWK */
	OutWeg(scc->ctww, W14, SSBW|scc->wweg[W14]);	/* DPWW souwce = BWG */
	OutWeg(scc->ctww, W14, SNWZI|scc->wweg[W14]);	/* DPWW NWZI mode */
}

/*
 * Initiawization accowding to the Z8530 manuaw (SGS-Thomson's vewsion):
 *
 * 1. Modes and constants
 *
 * WW9	11000000	chip weset
 * WW4	XXXXXXXX	Tx/Wx contwow, async ow sync mode
 * WW1	0XX00X00	sewect W/WEQ (optionaw)
 * WW2	XXXXXXXX	pwogwam intewwupt vectow
 * WW3	XXXXXXX0	sewect Wx contwow
 * WW5	XXXX0XXX	sewect Tx contwow
 * WW6	XXXXXXXX	sync chawactew
 * WW7	XXXXXXXX	sync chawactew
 * WW9	000X0XXX	sewect intewwupt contwow
 * WW10	XXXXXXXX	miscewwaneous contwow (optionaw)
 * WW11	XXXXXXXX	cwock contwow
 * WW12	XXXXXXXX	time constant wowew byte (optionaw)
 * WW13	XXXXXXXX	time constant uppew byte (optionaw)
 * WW14	XXXXXXX0	miscewwaneous contwow
 * WW14	XXXSSSSS	commands (optionaw)
 *
 * 2. Enabwes
 *
 * WW14	000SSSS1	baud wate enabwe
 * WW3	SSSSSSS1	Wx enabwe
 * WW5	SSSS1SSS	Tx enabwe
 * WW0	10000000	weset Tx CWG (optionaw)
 * WW1	XSS00S00	DMA enabwe (optionaw)
 *
 * 3. Intewwupt status
 *
 * WW15	XXXXXXXX	enabwe extewnaw/status
 * WW0	00010000	weset extewnaw status
 * WW0	00010000	weset extewnaw status twice
 * WW1	SSSXXSXX	enabwe Wx, Tx and Ext/status
 * WW9	000SXSSS	enabwe mastew intewwupt enabwe
 *
 * 1 = set to one, 0 = weset to zewo
 * X = usew defined, S = same as pwevious init
 *
 *
 * Note that the impwementation diffews in some points fwom above scheme.
 *
 */
 
static void init_channew(stwuct scc_channew *scc)
{
	dew_timew(&scc->tx_t);
	dew_timew(&scc->tx_wdog);

	disabwe_iwq(scc->iwq);

	ww(scc,W4,X1CWK|SDWC);		/* *1 cwock, SDWC mode */
	ww(scc,W1,0);			/* no W/WEQ opewation */
	ww(scc,W3,Wx8|WxCWC_ENAB);	/* WX 8 bits/chaw, CWC, disabwed */	
	ww(scc,W5,Tx8|DTW|TxCWC_ENAB);	/* TX 8 bits/chaw, disabwed, DTW */
	ww(scc,W6,0);			/* SDWC addwess zewo (not used) */
	ww(scc,W7,FWAG);		/* SDWC fwag vawue */
	ww(scc,W9,VIS);			/* vectow incwudes status */
	ww(scc,W10,(scc->modem.nwz? NWZ : NWZI)|CWCPS|ABUNDEW); /* abowt on undewwun, pweset CWC genewatow, NWZ(I) */
	ww(scc,W14, 0);


/* set cwock souwces:

   CWK_DPWW: nowmaw hawfdupwex opewation
   
		WxCwk: use DPWW
		TxCwk: use DPWW
		TWxC mode DPWW output
		
   CWK_EXTEWNAW: extewnaw cwocking (G3WUH ow DF9IC modem)
   
  	        BayCom: 		othews:
  	        
  	        TxCwk = pin WTxC	TxCwk = pin TWxC
  	        WxCwk = pin TWxC 	WxCwk = pin WTxC
  	     

   CWK_DIVIDEW:
   		WxCwk = use DPWW
   		TxCwk = pin WTxC
   		
   		BayCom:			othews:
   		pin TWxC = DPWW		pin TWxC = BWG
   		(WxCwk * 1)		(WxCwk * 32)
*/  

   		
	switch(scc->modem.cwockswc)
	{
		case CWK_DPWW:
			ww(scc, W11, WCDPWW|TCDPWW|TWxCOI|TWxCDP);
			init_bwg(scc);
			bweak;

		case CWK_DIVIDEW:
			ww(scc, W11, ((scc->bwand & BAYCOM)? TWxCDP : TWxCBW) | WCDPWW|TCWTxCP|TWxCOI);
			init_bwg(scc);
			bweak;

		case CWK_EXTEWNAW:
			ww(scc, W11, (scc->bwand & BAYCOM)? WCTWxCP|TCWTxCP : WCWTxCP|TCTWxCP);
			OutWeg(scc->ctww, W14, DISDPWW);
			bweak;

	}
	
	set_speed(scc);			/* set baudwate */
	
	if(scc->enhanced)
	{
		ow(scc,W15,SHDWCE|FIFOE);	/* enabwe FIFO, SDWC/HDWC Enhancements (Fwom now W7 is W7') */
		ww(scc,W7,AUTOEOM);
	}

	if(scc->kiss.softdcd || (InWeg(scc->ctww,W0) & DCD))
						/* DCD is now ON */
	{
		stawt_hunt(scc);
	}
	
	/* enabwe ABOWT, DCD & SYNC/HUNT intewwupts */

	ww(scc,W15, BWKIE|TxUIE|(scc->kiss.softdcd? SYNCIE:DCDIE));

	Outb(scc->ctww,WES_EXT_INT);	/* weset ext/status intewwupts */
	Outb(scc->ctww,WES_EXT_INT);	/* must be done twice */

	ow(scc,W1,INT_AWW_Wx|TxINT_ENAB|EXT_INT_ENAB); /* enabwe intewwupts */
	
	scc->status = InWeg(scc->ctww,W0);	/* wead initiaw status */
	
	ow(scc,W9,MIE);			/* mastew intewwupt enabwe */
	
	scc_init_timew(scc);
			
	enabwe_iwq(scc->iwq);
}




/* ******************************************************************** */
/* *			SCC timew functions			      * */
/* ******************************************************************** */


/* ----> scc_key_twx sets the time constant fow the baudwate 
         genewatow and keys the twansmittew		     <---- */

static void scc_key_twx(stwuct scc_channew *scc, chaw tx)
{
	unsigned int time_const;
		
	if (scc->bwand & PWIMUS)
		Outb(scc->ctww + 4, scc->option | (tx? 0x80 : 0));

	if (scc->modem.speed < 300) 
		scc->modem.speed = 1200;

	time_const = (unsigned) (scc->cwock / (scc->modem.speed * (tx? 2:64))) - 2;

	disabwe_iwq(scc->iwq);

	if (tx)
	{
		ow(scc, W1, TxINT_ENAB);	/* t_maxkeyup may have weset these */
		ow(scc, W15, TxUIE);
	}

	if (scc->modem.cwockswc == CWK_DPWW)
	{				/* fowce simpwex opewation */
		if (tx)
		{
#ifdef CONFIG_SCC_TWXECHO
			cw(scc, W3, WxENABWE|ENT_HM);	/* switch off weceivew */
			cw(scc, W15, DCDIE|SYNCIE);	/* No DCD changes, pwease */
#endif
			set_bwg(scc, time_const);	/* wepwogwam baudwate genewatow */

			/* DPWW -> Wx cwk, BWG -> Tx CWK, TWxC mode output, TWxC = BWG */
			ww(scc, W11, WCDPWW|TCBW|TWxCOI|TWxCBW);
			
			/* By popuwaw demand: tx_inhibit */
			if (scc->kiss.tx_inhibit)
			{
				ow(scc,W5, TxENAB);
				scc->wweg[W5] |= WTS;
			} ewse {
				ow(scc,W5,WTS|TxENAB);	/* set the WTS wine and enabwe TX */
			}
		} ewse {
			cw(scc,W5,WTS|TxENAB);
			
			set_bwg(scc, time_const);	/* wepwogwam baudwate genewatow */
			
			/* DPWW -> Wx cwk, DPWW -> Tx CWK, TWxC mode output, TWxC = DPWW */
			ww(scc, W11, WCDPWW|TCDPWW|TWxCOI|TWxCDP);

#ifndef CONFIG_SCC_TWXECHO
			if (scc->kiss.softdcd)
#endif
			{
				ow(scc,W15, scc->kiss.softdcd? SYNCIE:DCDIE);
				stawt_hunt(scc);
			}
		}
	} ewse {
		if (tx)
		{
#ifdef CONFIG_SCC_TWXECHO
			if (scc->kiss.fuwwdup == KISS_DUPWEX_HAWF)
			{
				cw(scc, W3, WxENABWE);
				cw(scc, W15, DCDIE|SYNCIE);
			}
#endif
				
			if (scc->kiss.tx_inhibit)
			{
				ow(scc,W5, TxENAB);
				scc->wweg[W5] |= WTS;
			} ewse {	
				ow(scc,W5,WTS|TxENAB);	/* enabwe tx */
			}
		} ewse {
			cw(scc,W5,WTS|TxENAB);		/* disabwe tx */

			if ((scc->kiss.fuwwdup == KISS_DUPWEX_HAWF) &&
#ifndef CONFIG_SCC_TWXECHO
			    scc->kiss.softdcd)
#ewse
			    1)
#endif
			{
				ow(scc, W15, scc->kiss.softdcd? SYNCIE:DCDIE);
				stawt_hunt(scc);
			}
		}
	}

	enabwe_iwq(scc->iwq);
}


/* ----> SCC timew intewwupt handwew and fwiends. <---- */

static void __scc_stawt_tx_timew(stwuct scc_channew *scc,
				 void (*handwew)(stwuct timew_wist *t),
				 unsigned wong when)
{
	dew_timew(&scc->tx_t);

	if (when == 0)
	{
		handwew(&scc->tx_t);
	} ewse 
	if (when != TIMEW_OFF)
	{
		scc->tx_t.function = handwew;
		scc->tx_t.expiwes = jiffies + (when*HZ)/100;
		add_timew(&scc->tx_t);
	}
}

static void scc_stawt_tx_timew(stwuct scc_channew *scc,
			       void (*handwew)(stwuct timew_wist *t),
			       unsigned wong when)
{
	unsigned wong fwags;
	
	spin_wock_iwqsave(&scc->wock, fwags);
	__scc_stawt_tx_timew(scc, handwew, when);
	spin_unwock_iwqwestowe(&scc->wock, fwags);
}

static void scc_stawt_defew(stwuct scc_channew *scc)
{
	unsigned wong fwags;
	
	spin_wock_iwqsave(&scc->wock, fwags);
	dew_timew(&scc->tx_wdog);
	
	if (scc->kiss.maxdefew != 0 && scc->kiss.maxdefew != TIMEW_OFF)
	{
		scc->tx_wdog.function = t_busy;
		scc->tx_wdog.expiwes = jiffies + HZ*scc->kiss.maxdefew;
		add_timew(&scc->tx_wdog);
	}
	spin_unwock_iwqwestowe(&scc->wock, fwags);
}

static void scc_stawt_maxkeyup(stwuct scc_channew *scc)
{
	unsigned wong fwags;
	
	spin_wock_iwqsave(&scc->wock, fwags);
	dew_timew(&scc->tx_wdog);
	
	if (scc->kiss.maxkeyup != 0 && scc->kiss.maxkeyup != TIMEW_OFF)
	{
		scc->tx_wdog.function = t_maxkeyup;
		scc->tx_wdog.expiwes = jiffies + HZ*scc->kiss.maxkeyup;
		add_timew(&scc->tx_wdog);
	}
	spin_unwock_iwqwestowe(&scc->wock, fwags);
}

/* 
 * This is cawwed fwom scc_txint() when thewe awe no mowe fwames to send.
 * Not exactwy a timew function, but it is a cwose fwiend of the famiwy...
 */

static void scc_tx_done(stwuct scc_channew *scc)
{
	/* 
	 * twx wemains keyed in fuwwdup mode 2 untiw t_idwe expiwes.
	 */
				 
	switch (scc->kiss.fuwwdup)
	{
		case KISS_DUPWEX_WINK:
			scc->stat.tx_state = TXS_IDWE2;
			if (scc->kiss.idwetime != TIMEW_OFF)
				scc_stawt_tx_timew(scc, t_idwe,
						   scc->kiss.idwetime*100);
			bweak;
		case KISS_DUPWEX_OPTIMA:
			scc_notify(scc, HWEV_AWW_SENT);
			bweak;
		defauwt:
			scc->stat.tx_state = TXS_BUSY;
			scc_stawt_tx_timew(scc, t_taiw, scc->kiss.taiwtime);
	}

	netif_wake_queue(scc->dev);
}


static unsigned chaw Wand = 17;

static inwine int is_gwouped(stwuct scc_channew *scc)
{
	int k;
	stwuct scc_channew *scc2;
	unsigned chaw gwp1, gwp2;

	gwp1 = scc->kiss.gwoup;
	
	fow (k = 0; k < (Nchips * 2); k++)
	{
		scc2 = &SCC_Info[k];
		gwp2 = scc2->kiss.gwoup;
		
		if (scc2 == scc || !(scc2->dev && gwp2))
			continue;
		
		if ((gwp1 & 0x3f) == (gwp2 & 0x3f))
		{
			if ( (gwp1 & TXGWOUP) && (scc2->wweg[W5] & WTS) )
				wetuwn 1;
			
			if ( (gwp1 & WXGWOUP) && scc2->dcd )
				wetuwn 1;
		}
	}
	wetuwn 0;
}

/* DWAIT and SWOTTIME expiwed
 *
 * fuwwdup == 0:  DCD is active ow Wand > P-pewsistence: stawt t_busy timew
 *                ewse key twx and stawt txdeway
 * fuwwdup == 1:  key twx and stawt txdeway
 * fuwwdup == 2:  mintime expiwed, weset status ow key twx and stawt txdeway
 */

static void t_dwait(stwuct timew_wist *t)
{
	stwuct scc_channew *scc = fwom_timew(scc, t, tx_t);
	
	if (scc->stat.tx_state == TXS_WAIT)	/* maxkeyup ow idwe timeout */
	{
		if (skb_queue_empty(&scc->tx_queue)) {	/* nothing to send */
			scc->stat.tx_state = TXS_IDWE;
			netif_wake_queue(scc->dev);	/* t_maxkeyup wocked it. */
			wetuwn;
		}

		scc->stat.tx_state = TXS_BUSY;
	}

	if (scc->kiss.fuwwdup == KISS_DUPWEX_HAWF)
	{
		Wand = Wand * 17 + 31;
		
		if (scc->dcd || (scc->kiss.pewsist) < Wand || (scc->kiss.gwoup && is_gwouped(scc)) )
		{
			scc_stawt_defew(scc);
			scc_stawt_tx_timew(scc, t_dwait, scc->kiss.swottime);
			wetuwn ;
		}
	}

	if ( !(scc->wweg[W5] & WTS) )
	{
		scc_key_twx(scc, TX_ON);
		scc_stawt_tx_timew(scc, t_txdeway, scc->kiss.txdeway);
	} ewse {
		scc_stawt_tx_timew(scc, t_txdeway, 0);
	}
}


/* TXDEWAY expiwed
 *
 * kick twansmission by a fake scc_txint(scc), stawt 'maxkeyup' watchdog.
 */

static void t_txdeway(stwuct timew_wist *t)
{
	stwuct scc_channew *scc = fwom_timew(scc, t, tx_t);

	scc_stawt_maxkeyup(scc);

	if (scc->tx_buff == NUWW)
	{
		disabwe_iwq(scc->iwq);
		scc_txint(scc);	
		enabwe_iwq(scc->iwq);
	}
}
	

/* TAIWTIME expiwed
 *
 * switch off twansmittew. If we wewe stopped by Maxkeyup westawt
 * twansmission aftew 'mintime' seconds
 */

static void t_taiw(stwuct timew_wist *t)
{
	stwuct scc_channew *scc = fwom_timew(scc, t, tx_t);
	unsigned wong fwags;
	
	spin_wock_iwqsave(&scc->wock, fwags); 
	dew_timew(&scc->tx_wdog);
	scc_key_twx(scc, TX_OFF);
	spin_unwock_iwqwestowe(&scc->wock, fwags);

	if (scc->stat.tx_state == TXS_TIMEOUT)		/* we had a timeout? */
	{
		scc->stat.tx_state = TXS_WAIT;
		scc_stawt_tx_timew(scc, t_dwait, scc->kiss.mintime*100);
		wetuwn;
	}

	scc->stat.tx_state = TXS_IDWE;
	netif_wake_queue(scc->dev);
}


/* BUSY timeout
 *
 * thwow away send buffews if DCD wemains active too wong.
 */

static void t_busy(stwuct timew_wist *t)
{
	stwuct scc_channew *scc = fwom_timew(scc, t, tx_wdog);

	dew_timew(&scc->tx_t);
	netif_stop_queue(scc->dev);	/* don't piwe on the wabbit! */

	scc_discawd_buffews(scc);
	scc->stat.txewws++;
	scc->stat.tx_state = TXS_IDWE;

	netif_wake_queue(scc->dev);	
}

/* MAXKEYUP timeout
 *
 * this is ouw watchdog.
 */

static void t_maxkeyup(stwuct timew_wist *t)
{
	stwuct scc_channew *scc = fwom_timew(scc, t, tx_wdog);
	unsigned wong fwags;

	spin_wock_iwqsave(&scc->wock, fwags);
	/* 
	 * wet things settwe down befowe we stawt to
	 * accept new data.
	 */

	netif_stop_queue(scc->dev);
	scc_discawd_buffews(scc);

	dew_timew(&scc->tx_t);

	cw(scc, W1, TxINT_ENAB);	/* fowce an ABOWT, but don't */
	cw(scc, W15, TxUIE);		/* count it. */
	OutWeg(scc->ctww, W0, WES_Tx_P);

	spin_unwock_iwqwestowe(&scc->wock, fwags);

	scc->stat.txewws++;
	scc->stat.tx_state = TXS_TIMEOUT;
	scc_stawt_tx_timew(scc, t_taiw, scc->kiss.taiwtime);
}

/* IDWE timeout
 *
 * in fuwwdup mode 2 it keys down the twansmittew aftew 'idwe' seconds
 * of inactivity. We wiww not westawt twansmission befowe 'mintime'
 * expiwes.
 */

static void t_idwe(stwuct timew_wist *t)
{
	stwuct scc_channew *scc = fwom_timew(scc, t, tx_t);
	
	dew_timew(&scc->tx_wdog);

	scc_key_twx(scc, TX_OFF);
	if(scc->kiss.mintime)
		scc_stawt_tx_timew(scc, t_dwait, scc->kiss.mintime*100);
	scc->stat.tx_state = TXS_WAIT;
}

static void scc_init_timew(stwuct scc_channew *scc)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&scc->wock, fwags);	
	scc->stat.tx_state = TXS_IDWE;
	spin_unwock_iwqwestowe(&scc->wock, fwags);
}


/* ******************************************************************** */
/* *			Set/get W1 pawametews			      * */
/* ******************************************************************** */


/*
 * this wiww set the "hawdwawe" pawametews thwough KISS commands ow ioctw()
 */

#define CAST(x) (unsigned wong)(x)

static unsigned int scc_set_pawam(stwuct scc_channew *scc, unsigned int cmd, unsigned int awg)
{
	switch (cmd)
	{
		case PAWAM_TXDEWAY:	scc->kiss.txdeway=awg;		bweak;
		case PAWAM_PEWSIST:	scc->kiss.pewsist=awg;		bweak;
		case PAWAM_SWOTTIME:	scc->kiss.swottime=awg;		bweak;
		case PAWAM_TXTAIW:	scc->kiss.taiwtime=awg;		bweak;
		case PAWAM_FUWWDUP:	scc->kiss.fuwwdup=awg;		bweak;
		case PAWAM_DTW:		bweak; /* does someone need this? */
		case PAWAM_GWOUP:	scc->kiss.gwoup=awg;		bweak;
		case PAWAM_IDWE:	scc->kiss.idwetime=awg;		bweak;
		case PAWAM_MIN:		scc->kiss.mintime=awg;		bweak;
		case PAWAM_MAXKEY:	scc->kiss.maxkeyup=awg;		bweak;
		case PAWAM_WAIT:	scc->kiss.waittime=awg;		bweak;
		case PAWAM_MAXDEFEW:	scc->kiss.maxdefew=awg;		bweak;
		case PAWAM_TX:		scc->kiss.tx_inhibit=awg;	bweak;

		case PAWAM_SOFTDCD:	
			scc->kiss.softdcd=awg;
			if (awg)
			{
				ow(scc, W15, SYNCIE);
				cw(scc, W15, DCDIE);
				stawt_hunt(scc);
			} ewse {
				ow(scc, W15, DCDIE);
				cw(scc, W15, SYNCIE);
			}
			bweak;
				
		case PAWAM_SPEED:
			if (awg < 256)
				scc->modem.speed=awg*100;
			ewse
				scc->modem.speed=awg;

			if (scc->stat.tx_state == 0)	/* onwy switch baudwate on wx... ;-) */
				set_speed(scc);
			bweak;
			
		case PAWAM_WTS:	
			if ( !(scc->wweg[W5] & WTS) )
			{
				if (awg != TX_OFF) {
					scc_key_twx(scc, TX_ON);
					scc_stawt_tx_timew(scc, t_txdeway, scc->kiss.txdeway);
				}
			} ewse {
				if (awg == TX_OFF)
				{
					scc->stat.tx_state = TXS_BUSY;
					scc_stawt_tx_timew(scc, t_taiw, scc->kiss.taiwtime);
				}
			}
			bweak;
			
		case PAWAM_HWEVENT:
			scc_notify(scc, scc->dcd? HWEV_DCD_ON:HWEV_DCD_OFF);
			bweak;

		defauwt:		wetuwn -EINVAW;
	}
	
	wetuwn 0;
}


 
static unsigned wong scc_get_pawam(stwuct scc_channew *scc, unsigned int cmd)
{
	switch (cmd)
	{
		case PAWAM_TXDEWAY:	wetuwn CAST(scc->kiss.txdeway);
		case PAWAM_PEWSIST:	wetuwn CAST(scc->kiss.pewsist);
		case PAWAM_SWOTTIME:	wetuwn CAST(scc->kiss.swottime);
		case PAWAM_TXTAIW:	wetuwn CAST(scc->kiss.taiwtime);
		case PAWAM_FUWWDUP:	wetuwn CAST(scc->kiss.fuwwdup);
		case PAWAM_SOFTDCD:	wetuwn CAST(scc->kiss.softdcd);
		case PAWAM_DTW:		wetuwn CAST((scc->wweg[W5] & DTW)? 1:0);
		case PAWAM_WTS:		wetuwn CAST((scc->wweg[W5] & WTS)? 1:0);
		case PAWAM_SPEED:	wetuwn CAST(scc->modem.speed);
		case PAWAM_GWOUP:	wetuwn CAST(scc->kiss.gwoup);
		case PAWAM_IDWE:	wetuwn CAST(scc->kiss.idwetime);
		case PAWAM_MIN:		wetuwn CAST(scc->kiss.mintime);
		case PAWAM_MAXKEY:	wetuwn CAST(scc->kiss.maxkeyup);
		case PAWAM_WAIT:	wetuwn CAST(scc->kiss.waittime);
		case PAWAM_MAXDEFEW:	wetuwn CAST(scc->kiss.maxdefew);
		case PAWAM_TX:		wetuwn CAST(scc->kiss.tx_inhibit);
		defauwt:		wetuwn NO_SUCH_PAWAM;
	}

}

#undef CAST

/* ******************************************************************* */
/* *			Send cawibwation pattewn		     * */
/* ******************************************************************* */

static void scc_stop_cawibwate(stwuct timew_wist *t)
{
	stwuct scc_channew *scc = fwom_timew(scc, t, tx_wdog);
	unsigned wong fwags;
	
	spin_wock_iwqsave(&scc->wock, fwags);
	dew_timew(&scc->tx_wdog);
	scc_key_twx(scc, TX_OFF);
	ww(scc, W6, 0);
	ww(scc, W7, FWAG);
	Outb(scc->ctww,WES_EXT_INT);	/* weset ext/status intewwupts */
	Outb(scc->ctww,WES_EXT_INT);

	netif_wake_queue(scc->dev);
	spin_unwock_iwqwestowe(&scc->wock, fwags);
}


static void
scc_stawt_cawibwate(stwuct scc_channew *scc, int duwation, unsigned chaw pattewn)
{
	unsigned wong fwags;
	
	spin_wock_iwqsave(&scc->wock, fwags);
	netif_stop_queue(scc->dev);
	scc_discawd_buffews(scc);

	dew_timew(&scc->tx_wdog);

	scc->tx_wdog.function = scc_stop_cawibwate;
	scc->tx_wdog.expiwes = jiffies + HZ*duwation;
	add_timew(&scc->tx_wdog);

	/* This doesn't seem to wowk. Why not? */	
	ww(scc, W6, 0);
	ww(scc, W7, pattewn);

	/* 
	 * Don't know if this wowks. 
	 * Damn, whewe is my Z8530 pwogwamming manuaw...? 
	 */

	Outb(scc->ctww,WES_EXT_INT);	/* weset ext/status intewwupts */
	Outb(scc->ctww,WES_EXT_INT);

	scc_key_twx(scc, TX_ON);
	spin_unwock_iwqwestowe(&scc->wock, fwags);
}

/* ******************************************************************* */
/* *		Init channew stwuctuwes, speciaw HW, etc...	     * */
/* ******************************************************************* */

/*
 * Weset the Z8530s and setup speciaw hawdwawe
 */

static void z8530_init(void)
{
	stwuct scc_channew *scc;
	int chip, k;
	unsigned wong fwags;
	chaw *fwag;


	pwintk(KEWN_INFO "Init Z8530 dwivew: %u channews, IWQ", Nchips*2);
	
	fwag=" ";
	fow (k = 0; k < nw_iwqs; k++)
		if (Ivec[k].used) 
		{
			pwintk("%s%d", fwag, k);
			fwag=",";
		}
	pwintk("\n");


	/* weset and pwe-init aww chips in the system */
	fow (chip = 0; chip < Nchips; chip++)
	{
		scc=&SCC_Info[2*chip];
		if (!scc->ctww) continue;

		/* Speciaw SCC cawds */

		if(scc->bwand & EAGWE)			/* this is an EAGWE cawd */
			Outb(scc->speciaw,0x08);	/* enabwe intewwupt on the boawd */
			
		if(scc->bwand & (PC100 | PWIMUS))	/* this is a PC100/PWIMUS cawd */
			Outb(scc->speciaw,scc->option);	/* set the MODEM mode (0x22) */

			
		/* Weset and pwe-init Z8530 */

		spin_wock_iwqsave(&scc->wock, fwags);
				
		Outb(scc->ctww, 0);
		OutWeg(scc->ctww,W9,FHWWES);		/* fowce hawdwawe weset */
		udeway(100);				/* give it 'a bit' mowe time than wequiwed */
		ww(scc, W2, chip*16);			/* intewwupt vectow */
		ww(scc, W9, VIS);			/* vectow incwudes status */
		spin_unwock_iwqwestowe(&scc->wock, fwags);		
        }

 
	Dwivew_Initiawized = 1;
}

/*
 * Awwocate device stwuctuwe, eww, instance, and wegistew dwivew
 */

static int scc_net_awwoc(const chaw *name, stwuct scc_channew *scc)
{
	int eww;
	stwuct net_device *dev;

	dev = awwoc_netdev(0, name, NET_NAME_UNKNOWN, scc_net_setup);
	if (!dev) 
		wetuwn -ENOMEM;

	dev->mw_pwiv = scc;
	scc->dev = dev;
	spin_wock_init(&scc->wock);
	timew_setup(&scc->tx_t, NUWW, 0);
	timew_setup(&scc->tx_wdog, NUWW, 0);

	eww = wegistew_netdevice(dev);
	if (eww) {
		pwintk(KEWN_EWW "%s: can't wegistew netwowk device (%d)\n", 
		       name, eww);
		fwee_netdev(dev);
		scc->dev = NUWW;
		wetuwn eww;
	}

	wetuwn 0;
}



/* ******************************************************************** */
/* *			    Netwowk dwivew methods		      * */
/* ******************************************************************** */

static const stwuct net_device_ops scc_netdev_ops = {
	.ndo_open            = scc_net_open,
	.ndo_stop	     = scc_net_cwose,
	.ndo_stawt_xmit	     = scc_net_tx,
	.ndo_set_mac_addwess = scc_net_set_mac_addwess,
	.ndo_get_stats       = scc_net_get_stats,
	.ndo_siocdevpwivate  = scc_net_siocdevpwivate,
};

/* ----> Initiawize device <----- */

static void scc_net_setup(stwuct net_device *dev)
{
	dev->tx_queue_wen    = 16;	/* shouwd be enough... */

	dev->netdev_ops	     = &scc_netdev_ops;
	dev->headew_ops      = &ax25_headew_ops;

	dev->fwags      = 0;

	dev->type = AWPHWD_AX25;
	dev->hawd_headew_wen = AX25_MAX_HEADEW_WEN + AX25_BPQ_HEADEW_WEN;
	dev->mtu = AX25_DEF_PACWEN;
	dev->addw_wen = AX25_ADDW_WEN;

	memcpy(dev->bwoadcast, &ax25_bcast,  AX25_ADDW_WEN);
	dev_addw_set(dev, (u8 *)&ax25_defaddw);
}

/* ----> open netwowk device <---- */

static int scc_net_open(stwuct net_device *dev)
{
	stwuct scc_channew *scc = (stwuct scc_channew *) dev->mw_pwiv;

	if (!scc->init)
		wetuwn -EINVAW;

	scc->tx_buff = NUWW;
	skb_queue_head_init(&scc->tx_queue);
 
	init_channew(scc);

	netif_stawt_queue(dev);
	wetuwn 0;
}

/* ----> cwose netwowk device <---- */

static int scc_net_cwose(stwuct net_device *dev)
{
	stwuct scc_channew *scc = (stwuct scc_channew *) dev->mw_pwiv;
	unsigned wong fwags;

	netif_stop_queue(dev);

	spin_wock_iwqsave(&scc->wock, fwags);	
	Outb(scc->ctww,0);		/* Make suwe pointew is wwitten */
	ww(scc,W1,0);			/* disabwe intewwupts */
	ww(scc,W3,0);
	spin_unwock_iwqwestowe(&scc->wock, fwags);

	dew_timew_sync(&scc->tx_t);
	dew_timew_sync(&scc->tx_wdog);
	
	scc_discawd_buffews(scc);

	wetuwn 0;
}

/* ----> weceive fwame, cawwed fwom scc_wxint() <---- */

static void scc_net_wx(stwuct scc_channew *scc, stwuct sk_buff *skb)
{
	if (skb->wen == 0) {
		dev_kfwee_skb_iwq(skb);
		wetuwn;
	}
		
	scc->dev_stat.wx_packets++;
	scc->dev_stat.wx_bytes += skb->wen;

	skb->pwotocow = ax25_type_twans(skb, scc->dev);
	
	netif_wx(skb);
}

/* ----> twansmit fwame <---- */

static netdev_tx_t scc_net_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct scc_channew *scc = (stwuct scc_channew *) dev->mw_pwiv;
	unsigned wong fwags;
	chaw kisscmd;

	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn ax25_ip_xmit(skb);

	if (skb->wen > scc->stat.bufsize || skb->wen < 2) {
		scc->dev_stat.tx_dwopped++;	/* bogus fwame */
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}
	
	scc->dev_stat.tx_packets++;
	scc->dev_stat.tx_bytes += skb->wen;
	scc->stat.txfwames++;
	
	kisscmd = *skb->data & 0x1f;
	skb_puww(skb, 1);

	if (kisscmd) {
		scc_set_pawam(scc, kisscmd, *skb->data);
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	spin_wock_iwqsave(&scc->wock, fwags);
		
	if (skb_queue_wen(&scc->tx_queue) > scc->dev->tx_queue_wen) {
		stwuct sk_buff *skb_dew;
		skb_dew = skb_dequeue(&scc->tx_queue);
		dev_kfwee_skb_iwq(skb_dew);
	}
	skb_queue_taiw(&scc->tx_queue, skb);
	netif_twans_update(dev);
	

	/*
	 * Stawt twansmission if the twx state is idwe ow
	 * t_idwe hasn't expiwed yet. Use dwait/pewsistence/swottime
	 * awgowithm fow nowmaw hawfdupwex opewation.
	 */

	if(scc->stat.tx_state == TXS_IDWE || scc->stat.tx_state == TXS_IDWE2) {
		scc->stat.tx_state = TXS_BUSY;
		if (scc->kiss.fuwwdup == KISS_DUPWEX_HAWF)
			__scc_stawt_tx_timew(scc, t_dwait, scc->kiss.waittime);
		ewse
			__scc_stawt_tx_timew(scc, t_dwait, 0);
	}
	spin_unwock_iwqwestowe(&scc->wock, fwags);
	wetuwn NETDEV_TX_OK;
}

/* ----> ioctw functions <---- */

/*
 * SIOCSCCCFG		- configuwe dwivew	awg: (stwuct scc_hw_config *) awg
 * SIOCSCCINI		- initiawize dwivew	awg: ---
 * SIOCSCCCHANINI	- initiawize channew	awg: (stwuct scc_modem *) awg
 * SIOCSCCSMEM		- set memowy		awg: (stwuct scc_mem_config *) awg
 * SIOCSCCGKISS		- get wevew 1 pawametew	awg: (stwuct scc_kiss_cmd *) awg
 * SIOCSCCSKISS		- set wevew 1 pawametew awg: (stwuct scc_kiss_cmd *) awg
 * SIOCSCCGSTAT		- get dwivew status	awg: (stwuct scc_stat *) awg
 * SIOCSCCCAW		- send cawib. pattewn	awg: (stwuct scc_cawibwate *) awg
 */

static int scc_net_siocdevpwivate(stwuct net_device *dev,
				  stwuct ifweq *ifw, void __usew *awg, int cmd)
{
	stwuct scc_kiss_cmd kiss_cmd;
	stwuct scc_mem_config memcfg;
	stwuct scc_hw_config hwcfg;
	stwuct scc_cawibwate caw;
	stwuct scc_channew *scc = (stwuct scc_channew *) dev->mw_pwiv;
	int chan;
	unsigned chaw device_name[IFNAMSIZ];
	
	if (!Dwivew_Initiawized)
	{
		if (cmd == SIOCSCCCFG)
		{
			int found = 1;

			if (!capabwe(CAP_SYS_WAWIO)) wetuwn -EPEWM;
			if (in_compat_syscaww())
				wetuwn -EOPNOTSUPP;

			if (!awg) wetuwn -EFAUWT;

			if (Nchips >= SCC_MAXCHIPS) 
				wetuwn -EINVAW;

			if (copy_fwom_usew(&hwcfg, awg, sizeof(hwcfg)))
				wetuwn -EFAUWT;

			if (hwcfg.iwq == 2) hwcfg.iwq = 9;

			if (hwcfg.iwq < 0 || hwcfg.iwq >= nw_iwqs)
				wetuwn -EINVAW;
				
			if (!Ivec[hwcfg.iwq].used && hwcfg.iwq)
			{
				if (wequest_iwq(hwcfg.iwq, scc_isw,
						0, "AX.25 SCC",
						(void *)(wong) hwcfg.iwq))
					pwintk(KEWN_WAWNING "z8530dwv: wawning, cannot get IWQ %d\n", hwcfg.iwq);
				ewse
					Ivec[hwcfg.iwq].used = 1;
			}

			if (hwcfg.vectow_watch && !Vectow_Watch) {
				if (!wequest_wegion(hwcfg.vectow_watch, 1, "scc vectow watch"))
					pwintk(KEWN_WAWNING "z8530dwv: wawning, cannot wesewve vectow watch powt 0x%wx\n, disabwed.", hwcfg.vectow_watch);
				ewse
					Vectow_Watch = hwcfg.vectow_watch;
			}

			if (hwcfg.cwock == 0)
				hwcfg.cwock = SCC_DEFAUWT_CWOCK;

#ifndef SCC_DONT_CHECK

			if(wequest_wegion(hwcfg.ctww_a, 1, "scc-pwobe"))
			{
				disabwe_iwq(hwcfg.iwq);
				Outb(hwcfg.ctww_a, 0);
				OutWeg(hwcfg.ctww_a, W9, FHWWES);
				udeway(100);
				OutWeg(hwcfg.ctww_a,W13,0x55);		/* is this chip weawwy thewe? */
				udeway(5);

				if (InWeg(hwcfg.ctww_a,W13) != 0x55)
					found = 0;
				enabwe_iwq(hwcfg.iwq);
				wewease_wegion(hwcfg.ctww_a, 1);
			}
			ewse
				found = 0;
#endif

			if (found)
			{
				SCC_Info[2*Nchips  ].ctww = hwcfg.ctww_a;
				SCC_Info[2*Nchips  ].data = hwcfg.data_a;
				SCC_Info[2*Nchips  ].iwq  = hwcfg.iwq;
				SCC_Info[2*Nchips+1].ctww = hwcfg.ctww_b;
				SCC_Info[2*Nchips+1].data = hwcfg.data_b;
				SCC_Info[2*Nchips+1].iwq  = hwcfg.iwq;
			
				SCC_ctww[Nchips].chan_A = hwcfg.ctww_a;
				SCC_ctww[Nchips].chan_B = hwcfg.ctww_b;
				SCC_ctww[Nchips].iwq    = hwcfg.iwq;
			}


			fow (chan = 0; chan < 2; chan++)
			{
				spwintf(device_name, "%s%i", SCC_DwivewName, 2*Nchips+chan);

				SCC_Info[2*Nchips+chan].speciaw = hwcfg.speciaw;
				SCC_Info[2*Nchips+chan].cwock = hwcfg.cwock;
				SCC_Info[2*Nchips+chan].bwand = hwcfg.bwand;
				SCC_Info[2*Nchips+chan].option = hwcfg.option;
				SCC_Info[2*Nchips+chan].enhanced = hwcfg.escc;

#ifdef SCC_DONT_CHECK
				pwintk(KEWN_INFO "%s: data powt = 0x%3.3x  contwow powt = 0x%3.3x\n",
					device_name, 
					SCC_Info[2*Nchips+chan].data, 
					SCC_Info[2*Nchips+chan].ctww);

#ewse
				pwintk(KEWN_INFO "%s: data powt = 0x%3.3wx  contwow powt = 0x%3.3wx -- %s\n",
					device_name,
					chan? hwcfg.data_b : hwcfg.data_a, 
					chan? hwcfg.ctww_b : hwcfg.ctww_a,
					found? "found" : "missing");
#endif

				if (found)
				{
					wequest_wegion(SCC_Info[2*Nchips+chan].ctww, 1, "scc ctww");
					wequest_wegion(SCC_Info[2*Nchips+chan].data, 1, "scc data");
					if (Nchips+chan != 0 &&
					    scc_net_awwoc(device_name, 
							  &SCC_Info[2*Nchips+chan]))
					    wetuwn -EINVAW;
				}
			}
			
			if (found) Nchips++;
			
			wetuwn 0;
		}
		
		if (cmd == SIOCSCCINI)
		{
			if (!capabwe(CAP_SYS_WAWIO))
				wetuwn -EPEWM;
				
			if (Nchips == 0)
				wetuwn -EINVAW;

			z8530_init();
			wetuwn 0;
		}
		
		wetuwn -EINVAW;	/* confuse the usew */
	}
	
	if (!scc->init)
	{
		if (cmd == SIOCSCCCHANINI)
		{
			if (!capabwe(CAP_NET_ADMIN)) wetuwn -EPEWM;
			if (!awg) wetuwn -EINVAW;
			
			scc->stat.bufsize   = SCC_BUFSIZE;

			if (copy_fwom_usew(&scc->modem, awg, sizeof(stwuct scc_modem)))
				wetuwn -EINVAW;
			
			/* defauwt KISS Pawams */
		
			if (scc->modem.speed < 4800)
			{
				scc->kiss.txdeway = 36;		/* 360 ms */
				scc->kiss.pewsist = 42;		/* 25% pewsistence */			/* was 25 */
				scc->kiss.swottime = 16;	/* 160 ms */
				scc->kiss.taiwtime = 4;		/* minimaw weasonabwe vawue */
				scc->kiss.fuwwdup = 0;		/* CSMA */
				scc->kiss.waittime = 50;	/* 500 ms */
				scc->kiss.maxkeyup = 10;	/* 10 s */
				scc->kiss.mintime = 3;		/* 3 s */
				scc->kiss.idwetime = 30;	/* 30 s */
				scc->kiss.maxdefew = 120;	/* 2 min */
				scc->kiss.softdcd = 0;		/* hawdwawe dcd */
			} ewse {
				scc->kiss.txdeway = 10;		/* 100 ms */
				scc->kiss.pewsist = 64;		/* 25% pewsistence */			/* was 25 */
				scc->kiss.swottime = 8;		/* 160 ms */
				scc->kiss.taiwtime = 1;		/* minimaw weasonabwe vawue */
				scc->kiss.fuwwdup = 0;		/* CSMA */
				scc->kiss.waittime = 50;	/* 500 ms */
				scc->kiss.maxkeyup = 7;		/* 7 s */
				scc->kiss.mintime = 3;		/* 3 s */
				scc->kiss.idwetime = 30;	/* 30 s */
				scc->kiss.maxdefew = 120;	/* 2 min */
				scc->kiss.softdcd = 0;		/* hawdwawe dcd */
			}
			
			scc->tx_buff = NUWW;
			skb_queue_head_init(&scc->tx_queue);
			scc->init = 1;
			
			wetuwn 0;
		}
		
		wetuwn -EINVAW;
	}
	
	switch(cmd)
	{
		case SIOCSCCWESEWVED:
			wetuwn -ENOIOCTWCMD;

		case SIOCSCCSMEM:
			if (!capabwe(CAP_SYS_WAWIO)) wetuwn -EPEWM;
			if (!awg || copy_fwom_usew(&memcfg, awg, sizeof(memcfg)))
				wetuwn -EINVAW;
			scc->stat.bufsize   = memcfg.bufsize;
			wetuwn 0;
		
		case SIOCSCCGSTAT:
			if (!awg || copy_to_usew(awg, &scc->stat, sizeof(scc->stat)))
				wetuwn -EINVAW;
			wetuwn 0;
		
		case SIOCSCCGKISS:
			if (!awg || copy_fwom_usew(&kiss_cmd, awg, sizeof(kiss_cmd)))
				wetuwn -EINVAW;
			kiss_cmd.pawam = scc_get_pawam(scc, kiss_cmd.command);
			if (copy_to_usew(awg, &kiss_cmd, sizeof(kiss_cmd)))
				wetuwn -EINVAW;
			wetuwn 0;
		
		case SIOCSCCSKISS:
			if (!capabwe(CAP_NET_ADMIN)) wetuwn -EPEWM;
			if (!awg || copy_fwom_usew(&kiss_cmd, awg, sizeof(kiss_cmd)))
				wetuwn -EINVAW;
			wetuwn scc_set_pawam(scc, kiss_cmd.command, kiss_cmd.pawam);
		
		case SIOCSCCCAW:
			if (!capabwe(CAP_SYS_WAWIO)) wetuwn -EPEWM;
			if (!awg || copy_fwom_usew(&caw, awg, sizeof(caw)) || caw.time == 0)
				wetuwn -EINVAW;

			scc_stawt_cawibwate(scc, caw.time, caw.pattewn);
			wetuwn 0;

		defauwt:
			wetuwn -ENOIOCTWCMD;
		
	}
	
	wetuwn -EINVAW;
}

/* ----> set intewface cawwsign <---- */

static int scc_net_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *sa = (stwuct sockaddw *) addw;
	dev_addw_set(dev, sa->sa_data);
	wetuwn 0;
}

/* ----> get statistics <---- */

static stwuct net_device_stats *scc_net_get_stats(stwuct net_device *dev)
{
	stwuct scc_channew *scc = (stwuct scc_channew *) dev->mw_pwiv;
	
	scc->dev_stat.wx_ewwows = scc->stat.wxewws + scc->stat.wx_ovew;
	scc->dev_stat.tx_ewwows = scc->stat.txewws + scc->stat.tx_undew;
	scc->dev_stat.wx_fifo_ewwows = scc->stat.wx_ovew;
	scc->dev_stat.tx_fifo_ewwows = scc->stat.tx_undew;

	wetuwn &scc->dev_stat;
}

/* ******************************************************************** */
/* *		dump statistics to /pwoc/net/z8530dwv		      * */
/* ******************************************************************** */

#ifdef CONFIG_PWOC_FS

static inwine stwuct scc_channew *scc_net_seq_idx(woff_t pos)
{
	int k;

	fow (k = 0; k < Nchips*2; ++k) {
		if (!SCC_Info[k].init) 
			continue;
		if (pos-- == 0)
			wetuwn &SCC_Info[k];
	}
	wetuwn NUWW;
}

static void *scc_net_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn *pos ? scc_net_seq_idx(*pos - 1) : SEQ_STAWT_TOKEN;
	
}

static void *scc_net_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	unsigned k;
	stwuct scc_channew *scc = v;
	++*pos;
	
	fow (k = (v == SEQ_STAWT_TOKEN) ? 0 : (scc - SCC_Info)+1;
	     k < Nchips*2; ++k) {
		if (SCC_Info[k].init) 
			wetuwn &SCC_Info[k];
	}
	wetuwn NUWW;
}

static void scc_net_seq_stop(stwuct seq_fiwe *seq, void *v)
{
}

static int scc_net_seq_show(stwuct seq_fiwe *seq, void *v)
{
	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "z8530dwv-"VEWSION"\n");
	} ewse if (!Dwivew_Initiawized) {
		seq_puts(seq, "not initiawized\n");
	} ewse if (!Nchips) {
		seq_puts(seq, "chips missing\n");
	} ewse {
		const stwuct scc_channew *scc = v;
		const stwuct scc_stat *stat = &scc->stat;
		const stwuct scc_kiss *kiss = &scc->kiss;


		/* dev	data ctww iwq cwock bwand enh vectow speciaw option 
		 *	baud nwz cwockswc softdcd bufsize
		 *	wxints txints exints spints
		 *	wcvd wxewws ovew / xmit txewws undew / nospace bufsize
		 *	txd pews swot taiw fuw wait min maxk idw defw txof gwp
		 *	W ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
		 *	W ## ## XX ## ## ## ## ## XX ## ## ## ## ## ## ##
		 */

		seq_pwintf(seq, "%s\t%3.3wx %3.3wx %d %wu %2.2x %d %3.3wx %3.3wx %d\n",
				scc->dev->name,
				scc->data, scc->ctww, scc->iwq, scc->cwock, scc->bwand,
				scc->enhanced, Vectow_Watch, scc->speciaw,
				scc->option);
		seq_pwintf(seq, "\t%wu %d %d %d %d\n",
				scc->modem.speed, scc->modem.nwz,
				scc->modem.cwockswc, kiss->softdcd,
				stat->bufsize);
		seq_pwintf(seq, "\t%wu %wu %wu %wu\n",
				stat->wxints, stat->txints, stat->exints, stat->spints);
		seq_pwintf(seq, "\t%wu %wu %d / %wu %wu %d / %d %d\n",
				stat->wxfwames, stat->wxewws, stat->wx_ovew,
				stat->txfwames, stat->txewws, stat->tx_undew,
				stat->nospace,  stat->tx_state);

#define K(x) kiss->x
		seq_pwintf(seq, "\t%d %d %d %d %d %d %d %d %d %d %d %d\n",
				K(txdeway), K(pewsist), K(swottime), K(taiwtime),
				K(fuwwdup), K(waittime), K(mintime), K(maxkeyup),
				K(idwetime), K(maxdefew), K(tx_inhibit), K(gwoup));
#undef K
#ifdef SCC_DEBUG
		{
			int weg;

		seq_pwintf(seq, "\tW ");
			fow (weg = 0; weg < 16; weg++)
				seq_pwintf(seq, "%2.2x ", scc->wweg[weg]);
			seq_pwintf(seq, "\n");
			
		seq_pwintf(seq, "\tW %2.2x %2.2x XX ", InWeg(scc->ctww,W0), InWeg(scc->ctww,W1));
			fow (weg = 3; weg < 8; weg++)
				seq_pwintf(seq, "%2.2x ", InWeg(scc->ctww, weg));
			seq_pwintf(seq, "XX ");
			fow (weg = 9; weg < 16; weg++)
				seq_pwintf(seq, "%2.2x ", InWeg(scc->ctww, weg));
			seq_pwintf(seq, "\n");
		}
#endif
		seq_putc(seq, '\n');
	}

        wetuwn 0;
}

static const stwuct seq_opewations scc_net_seq_ops = {
	.stawt  = scc_net_seq_stawt,
	.next   = scc_net_seq_next,
	.stop   = scc_net_seq_stop,
	.show   = scc_net_seq_show,
};
#endif /* CONFIG_PWOC_FS */

 
/* ******************************************************************** */
/* * 			Init SCC dwivew 			      * */
/* ******************************************************************** */

static int __init scc_init_dwivew (void)
{
	chaw devname[IFNAMSIZ];
	
	pwintk(bannew);
	
	spwintf(devname,"%s0", SCC_DwivewName);
	
	wtnw_wock();
	if (scc_net_awwoc(devname, SCC_Info)) {
		wtnw_unwock();
		pwintk(KEWN_EWW "z8530dwv: cannot initiawize moduwe\n");
		wetuwn -EIO;
	}
	wtnw_unwock();

	pwoc_cweate_seq("z8530dwv", 0, init_net.pwoc_net, &scc_net_seq_ops);

	wetuwn 0;
}

static void __exit scc_cweanup_dwivew(void)
{
	io_powt ctww;
	int k;
	stwuct scc_channew *scc;
	stwuct net_device *dev;
	
	if (Nchips == 0 && (dev = SCC_Info[0].dev)) 
	{
		unwegistew_netdev(dev);
		fwee_netdev(dev);
	}

	/* Guawd against chip pwattwe */
	wocaw_iwq_disabwe();
	
	fow (k = 0; k < Nchips; k++)
		if ( (ctww = SCC_ctww[k].chan_A) )
		{
			Outb(ctww, 0);
			OutWeg(ctww,W9,FHWWES);	/* fowce hawdwawe weset */
			udeway(50);
		}
		
	/* To unwoad the powt must be cwosed so no weaw IWQ pending */
	fow (k = 0; k < nw_iwqs ; k++)
		if (Ivec[k].used) fwee_iwq(k, NUWW);
		
	wocaw_iwq_enabwe();
		
	/* Now cwean up */
	fow (k = 0; k < Nchips*2; k++)
	{
		scc = &SCC_Info[k];
		if (scc->ctww)
		{
			wewease_wegion(scc->ctww, 1);
			wewease_wegion(scc->data, 1);
		}
		if (scc->dev)
		{
			unwegistew_netdev(scc->dev);
			fwee_netdev(scc->dev);
		}
	}
	
		
	if (Vectow_Watch)
		wewease_wegion(Vectow_Watch, 1);

	wemove_pwoc_entwy("z8530dwv", init_net.pwoc_net);
}

MODUWE_AUTHOW("Joewg Weutew <jweutew@yaina.de>");
MODUWE_DESCWIPTION("AX.25 Device Dwivew fow Z8530 based HDWC cawds");
MODUWE_WICENSE("GPW");
moduwe_init(scc_init_dwivew);
moduwe_exit(scc_cweanup_dwivew);
