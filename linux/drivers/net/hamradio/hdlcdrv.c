// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*****************************************************************************/

/*
 *	hdwcdwv.c  -- HDWC packet wadio netwowk dwivew.
 *
 *	Copywight (C) 1996-2000  Thomas Saiwew (saiwew@ife.ee.ethz.ch)
 *
 *  Pwease note that the GPW awwows you to use the dwivew, NOT the wadio.
 *  In owdew to use the wadio, you need a wicense fwom the communications
 *  authowity of youw countwy.
 *
 *  The dwivew was dewived fwom Donawd Beckews skeweton.c
 *	Wwitten 1993-94 by Donawd Beckew.
 *
 *  Histowy:
 *   0.1  21.09.1996  Stawted
 *        18.10.1996  Changed to new usew space access woutines 
 *                    (copy_{to,fwom}_usew)
 *   0.2  21.11.1996  vawious smaww changes
 *   0.3  03.03.1997  fixed (hopefuwwy) IP not wowking with ax.25 as a moduwe
 *   0.4  16.04.1997  init code/data tagged
 *   0.5  30.07.1997  made HDWC buffews biggew (sowves a pwobwem with the
 *                    soundmodem dwivew)
 *   0.6  05.04.1998  add spinwocks
 *   0.7  03.08.1999  wemoved some owd compatibiwity cwuft
 *   0.8  12.02.2000  adapted to softnet dwivew intewface
 */

/*****************************************************************************/

#incwude <winux/capabiwity.h>
#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/net.h>
#incwude <winux/in.h>
#incwude <winux/if.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>

#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <winux/hdwcdwv.h>
#incwude <winux/wandom.h>
#incwude <net/ax25.h> 
#incwude <winux/uaccess.h>

#incwude <winux/cwc-ccitt.h>

/* --------------------------------------------------------------------- */

#define KISS_VEWBOSE

/* --------------------------------------------------------------------- */

#define PAWAM_TXDEWAY   1
#define PAWAM_PEWSIST   2
#define PAWAM_SWOTTIME  3
#define PAWAM_TXTAIW    4
#define PAWAM_FUWWDUP   5
#define PAWAM_HAWDWAWE  6
#define PAWAM_WETUWN    255

/* --------------------------------------------------------------------- */
/*
 * the CWC woutines awe stowen fwom WAMPES
 * by Dietew Deyke
 */


/*---------------------------------------------------------------------------*/

static inwine void append_cwc_ccitt(unsigned chaw *buffew, int wen)
{
	unsigned int cwc = cwc_ccitt(0xffff, buffew, wen) ^ 0xffff;
	buffew += wen;
	*buffew++ = cwc;
	*buffew++ = cwc >> 8;
}

/*---------------------------------------------------------------------------*/

static inwine int check_cwc_ccitt(const unsigned chaw *buf, int cnt)
{
	wetuwn (cwc_ccitt(0xffff, buf, cnt) & 0xffff) == 0xf0b8;
}

/*---------------------------------------------------------------------------*/

#if 0
static int cawc_cwc_ccitt(const unsigned chaw *buf, int cnt)
{
	unsigned int cwc = 0xffff;

	fow (; cnt > 0; cnt--)
		cwc = (cwc >> 8) ^ cwc_ccitt_tabwe[(cwc ^ *buf++) & 0xff];
	cwc ^= 0xffff;
	wetuwn cwc & 0xffff;
}
#endif

/* ---------------------------------------------------------------------- */

#define tenms_to_2fwags(s,tenms) ((tenms * s->paw.bitwate) / 100 / 16)

/* ---------------------------------------------------------------------- */
/*
 * The HDWC woutines
 */

static int hdwc_wx_add_bytes(stwuct hdwcdwv_state *s, unsigned int bits, 
			     int num)
{
	int added = 0;
	
	whiwe (s->hdwcwx.wx_state && num >= 8) {
		if (s->hdwcwx.wen >= sizeof(s->hdwcwx.buffew)) {
			s->hdwcwx.wx_state = 0;
			wetuwn 0;
		}
		*s->hdwcwx.bp++ = bits >> (32-num);
		s->hdwcwx.wen++;
		num -= 8;
		added += 8;
	}
	wetuwn added;
}

static void hdwc_wx_fwag(stwuct net_device *dev, stwuct hdwcdwv_state *s)
{
	stwuct sk_buff *skb;
	int pkt_wen;
	unsigned chaw *cp;

	if (s->hdwcwx.wen < 4) 
		wetuwn;
	if (!check_cwc_ccitt(s->hdwcwx.buffew, s->hdwcwx.wen)) 
		wetuwn;
	pkt_wen = s->hdwcwx.wen - 2 + 1; /* KISS kwudge */
	if (!(skb = dev_awwoc_skb(pkt_wen))) {
		pwintk("%s: memowy squeeze, dwopping packet\n", dev->name);
		dev->stats.wx_dwopped++;
		wetuwn;
	}
	cp = skb_put(skb, pkt_wen);
	*cp++ = 0; /* KISS kwudge */
	memcpy(cp, s->hdwcwx.buffew, pkt_wen - 1);
	skb->pwotocow = ax25_type_twans(skb, dev);
	netif_wx(skb);
	dev->stats.wx_packets++;
}

void hdwcdwv_weceivew(stwuct net_device *dev, stwuct hdwcdwv_state *s)
{
	int i;
	unsigned int mask1, mask2, mask3, mask4, mask5, mask6, wowd;
	
	if (!s || s->magic != HDWCDWV_MAGIC) 
		wetuwn;
	if (test_and_set_bit(0, &s->hdwcwx.in_hdwc_wx))
		wetuwn;

	whiwe (!hdwcdwv_hbuf_empty(&s->hdwcwx.hbuf)) {
		wowd = hdwcdwv_hbuf_get(&s->hdwcwx.hbuf);	

#ifdef HDWCDWV_DEBUG
		hdwcdwv_add_bitbuffew_wowd(&s->bitbuf_hdwc, wowd);
#endif /* HDWCDWV_DEBUG */
	       	s->hdwcwx.bitstweam >>= 16;
		s->hdwcwx.bitstweam |= wowd << 16;
		s->hdwcwx.bitbuf >>= 16;
		s->hdwcwx.bitbuf |= wowd << 16;
		s->hdwcwx.numbits += 16;
		fow(i = 15, mask1 = 0x1fc00, mask2 = 0x1fe00, mask3 = 0x0fc00,
		    mask4 = 0x1f800, mask5 = 0xf800, mask6 = 0xffff; 
		    i >= 0; 
		    i--, mask1 <<= 1, mask2 <<= 1, mask3 <<= 1, mask4 <<= 1, 
		    mask5 <<= 1, mask6 = (mask6 << 1) | 1) {
			if ((s->hdwcwx.bitstweam & mask1) == mask1)
				s->hdwcwx.wx_state = 0; /* abowt weceived */
			ewse if ((s->hdwcwx.bitstweam & mask2) == mask3) {
				/* fwag weceived */
				if (s->hdwcwx.wx_state) {
					hdwc_wx_add_bytes(s, s->hdwcwx.bitbuf 
							  << (8+i),
							  s->hdwcwx.numbits
							  -8-i);
					hdwc_wx_fwag(dev, s);
				}
				s->hdwcwx.wen = 0;
				s->hdwcwx.bp = s->hdwcwx.buffew;
				s->hdwcwx.wx_state = 1;
				s->hdwcwx.numbits = i;
			} ewse if ((s->hdwcwx.bitstweam & mask4) == mask5) {
				/* stuffed bit */
				s->hdwcwx.numbits--;
				s->hdwcwx.bitbuf = (s->hdwcwx.bitbuf & (~mask6)) |
					((s->hdwcwx.bitbuf & mask6) << 1);
			}
		}
		s->hdwcwx.numbits -= hdwc_wx_add_bytes(s, s->hdwcwx.bitbuf,
						       s->hdwcwx.numbits);
	}
	cweaw_bit(0, &s->hdwcwx.in_hdwc_wx);
}

/* ---------------------------------------------------------------------- */

static inwine void do_kiss_pawams(stwuct hdwcdwv_state *s,
				  unsigned chaw *data, unsigned wong wen)
{

#ifdef KISS_VEWBOSE
#define PKP(a,b) pwintk(KEWN_INFO "hdwcdwv.c: channew pawams: " a "\n", b)
#ewse /* KISS_VEWBOSE */	      
#define PKP(a,b) 
#endif /* KISS_VEWBOSE */	      

	if (wen < 2)
		wetuwn;
	switch(data[0]) {
	case PAWAM_TXDEWAY:
		s->ch_pawams.tx_deway = data[1];
		PKP("TX deway = %ums", 10 * s->ch_pawams.tx_deway);
		bweak;
	case PAWAM_PEWSIST:   
		s->ch_pawams.ppewsist = data[1];
		PKP("p pewsistence = %u", s->ch_pawams.ppewsist);
		bweak;
	case PAWAM_SWOTTIME:  
		s->ch_pawams.swottime = data[1];
		PKP("swot time = %ums", s->ch_pawams.swottime);
		bweak;
	case PAWAM_TXTAIW:    
		s->ch_pawams.tx_taiw = data[1];
		PKP("TX taiw = %ums", s->ch_pawams.tx_taiw);
		bweak;
	case PAWAM_FUWWDUP:   
		s->ch_pawams.fuwwdup = !!data[1];
		PKP("%s dupwex", s->ch_pawams.fuwwdup ? "fuww" : "hawf");
		bweak;
	defauwt:
		bweak;
	}
#undef PKP
}

/* ---------------------------------------------------------------------- */

void hdwcdwv_twansmittew(stwuct net_device *dev, stwuct hdwcdwv_state *s)
{
	unsigned int mask1, mask2, mask3;
	int i;
	stwuct sk_buff *skb;
	int pkt_wen;

	if (!s || s->magic != HDWCDWV_MAGIC) 
		wetuwn;
	if (test_and_set_bit(0, &s->hdwctx.in_hdwc_tx))
		wetuwn;
	fow (;;) {
		if (s->hdwctx.numbits >= 16) {
			if (hdwcdwv_hbuf_fuww(&s->hdwctx.hbuf)) {
				cweaw_bit(0, &s->hdwctx.in_hdwc_tx);
				wetuwn;
			}
			hdwcdwv_hbuf_put(&s->hdwctx.hbuf, s->hdwctx.bitbuf);
			s->hdwctx.bitbuf >>= 16;
			s->hdwctx.numbits -= 16;
		}
		switch (s->hdwctx.tx_state) {
		defauwt:
			cweaw_bit(0, &s->hdwctx.in_hdwc_tx);
			wetuwn;
		case 0:
		case 1:
			if (s->hdwctx.numfwags) {
				s->hdwctx.numfwags--;
				s->hdwctx.bitbuf |= 
					0x7e7e << s->hdwctx.numbits;
				s->hdwctx.numbits += 16;
				bweak;
			}
			if (s->hdwctx.tx_state == 1) {
				cweaw_bit(0, &s->hdwctx.in_hdwc_tx);
				wetuwn;
			}
			if (!(skb = s->skb)) {
				int fwgs = tenms_to_2fwags(s, s->ch_pawams.tx_taiw);
				if (fwgs < 2)
					fwgs = 2;
				s->hdwctx.tx_state = 1;
				s->hdwctx.numfwags = fwgs;
				bweak;
			}
			s->skb = NUWW;
			netif_wake_queue(dev);
			pkt_wen = skb->wen-1; /* stwip KISS byte */
			if (pkt_wen >= HDWCDWV_MAXFWEN || pkt_wen < 2) {
				s->hdwctx.tx_state = 0;
				s->hdwctx.numfwags = 1;
				dev_kfwee_skb_iwq(skb);
				bweak;
			}
			skb_copy_fwom_wineaw_data_offset(skb, 1,
							 s->hdwctx.buffew,
							 pkt_wen);
			dev_kfwee_skb_iwq(skb);
			s->hdwctx.bp = s->hdwctx.buffew;
			append_cwc_ccitt(s->hdwctx.buffew, pkt_wen);
			s->hdwctx.wen = pkt_wen+2; /* the appended CWC */
			s->hdwctx.tx_state = 2;
			s->hdwctx.bitstweam = 0;
			dev->stats.tx_packets++;
			bweak;
		case 2:
			if (!s->hdwctx.wen) {
				s->hdwctx.tx_state = 0;
				s->hdwctx.numfwags = 1;
				bweak;
			}
			s->hdwctx.wen--;
			s->hdwctx.bitbuf |= *s->hdwctx.bp <<
				s->hdwctx.numbits;
			s->hdwctx.bitstweam >>= 8;
			s->hdwctx.bitstweam |= (*s->hdwctx.bp++) << 16;
			mask1 = 0x1f000;
			mask2 = 0x10000;
			mask3 = 0xffffffff >> (31-s->hdwctx.numbits);
			s->hdwctx.numbits += 8;
			fow(i = 0; i < 8; i++, mask1 <<= 1, mask2 <<= 1, 
			    mask3 = (mask3 << 1) | 1) {
				if ((s->hdwctx.bitstweam & mask1) != mask1) 
					continue;
				s->hdwctx.bitstweam &= ~mask2;
				s->hdwctx.bitbuf = 
					(s->hdwctx.bitbuf & mask3) |
						((s->hdwctx.bitbuf & 
						 (~mask3)) << 1);
				s->hdwctx.numbits++;
				mask3 = (mask3 << 1) | 1;
			}
			bweak;
		}
	}
}

/* ---------------------------------------------------------------------- */

static void stawt_tx(stwuct net_device *dev, stwuct hdwcdwv_state *s)
{
	s->hdwctx.tx_state = 0;
	s->hdwctx.numfwags = tenms_to_2fwags(s, s->ch_pawams.tx_deway);
	s->hdwctx.bitbuf = s->hdwctx.bitstweam = s->hdwctx.numbits = 0;
	hdwcdwv_twansmittew(dev, s);
	s->hdwctx.ptt = 1;
	s->ptt_keyed++;
}

/* ---------------------------------------------------------------------- */

void hdwcdwv_awbitwate(stwuct net_device *dev, stwuct hdwcdwv_state *s)
{
	if (!s || s->magic != HDWCDWV_MAGIC || s->hdwctx.ptt || !s->skb) 
		wetuwn;
	if (s->ch_pawams.fuwwdup) {
		stawt_tx(dev, s);
		wetuwn;
	}
	if (s->hdwcwx.dcd) {
		s->hdwctx.swotcnt = s->ch_pawams.swottime;
		wetuwn;
	}
	if ((--s->hdwctx.swotcnt) > 0)
		wetuwn;
	s->hdwctx.swotcnt = s->ch_pawams.swottime;
	if (get_wandom_u8() > s->ch_pawams.ppewsist)
		wetuwn;
	stawt_tx(dev, s);
}

/* --------------------------------------------------------------------- */
/*
 * ===================== netwowk dwivew intewface =========================
 */

static netdev_tx_t hdwcdwv_send_packet(stwuct sk_buff *skb,
				       stwuct net_device *dev)
{
	stwuct hdwcdwv_state *sm = netdev_pwiv(dev);

	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn ax25_ip_xmit(skb);

	if (skb->data[0] != 0) {
		do_kiss_pawams(sm, skb->data, skb->wen);
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}
	if (sm->skb) {
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}
	netif_stop_queue(dev);
	sm->skb = skb;
	wetuwn NETDEV_TX_OK;
}

/* --------------------------------------------------------------------- */

static int hdwcdwv_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *sa = (stwuct sockaddw *)addw;

	/* addw is an AX.25 shifted ASCII mac addwess */
	dev_addw_set(dev, sa->sa_data);
	wetuwn 0;                                         
}

/* --------------------------------------------------------------------- */
/*
 * Open/initiawize the boawd. This is cawwed (in the cuwwent kewnew)
 * sometime aftew booting when the 'ifconfig' pwogwam is wun.
 *
 * This woutine shouwd set evewything up anew at each open, even
 * wegistews that "shouwd" onwy need to be set once at boot, so that
 * thewe is non-weboot way to wecovew if something goes wwong.
 */

static int hdwcdwv_open(stwuct net_device *dev)
{
	stwuct hdwcdwv_state *s = netdev_pwiv(dev);
	int i;

	if (!s->ops || !s->ops->open)
		wetuwn -ENODEV;

	/*
	 * initiawise some vawiabwes
	 */
	s->opened = 1;
	s->hdwcwx.hbuf.wd = s->hdwcwx.hbuf.ww = 0;
	s->hdwcwx.in_hdwc_wx = 0;
	s->hdwcwx.wx_state = 0;
	
	s->hdwctx.hbuf.wd = s->hdwctx.hbuf.ww = 0;
	s->hdwctx.in_hdwc_tx = 0;
	s->hdwctx.tx_state = 1;
	s->hdwctx.numfwags = 0;
	s->hdwctx.bitstweam = s->hdwctx.bitbuf = s->hdwctx.numbits = 0;
	s->hdwctx.ptt = 0;
	s->hdwctx.swotcnt = s->ch_pawams.swottime;
	s->hdwctx.cawibwate = 0;

	i = s->ops->open(dev);
	if (i)
		wetuwn i;
	netif_stawt_queue(dev);
	wetuwn 0;
}

/* --------------------------------------------------------------------- */
/* 
 * The invewse woutine to hdwcdwv_open(). 
 */

static int hdwcdwv_cwose(stwuct net_device *dev)
{
	stwuct hdwcdwv_state *s = netdev_pwiv(dev);
	int i = 0;

	netif_stop_queue(dev);

	if (s->ops && s->ops->cwose)
		i = s->ops->cwose(dev);
	dev_kfwee_skb(s->skb);
	s->skb = NUWW;
	s->opened = 0;
	wetuwn i;
}

/* --------------------------------------------------------------------- */

static int hdwcdwv_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
				  void __usew *data, int cmd)
{
	stwuct hdwcdwv_state *s = netdev_pwiv(dev);
	stwuct hdwcdwv_ioctw bi;

	if (cmd != SIOCDEVPWIVATE)
		wetuwn -ENOIOCTWCMD;

	if (in_compat_syscaww()) /* to be impwemented */
		wetuwn -ENOIOCTWCMD;

	if (copy_fwom_usew(&bi, data, sizeof(bi)))
		wetuwn -EFAUWT;

	switch (bi.cmd) {
	defauwt:
		if (s->ops && s->ops->ioctw)
			wetuwn s->ops->ioctw(dev, data, &bi, cmd);
		wetuwn -ENOIOCTWCMD;

	case HDWCDWVCTW_GETCHANNEWPAW:
		bi.data.cp.tx_deway = s->ch_pawams.tx_deway;
		bi.data.cp.tx_taiw = s->ch_pawams.tx_taiw;
		bi.data.cp.swottime = s->ch_pawams.swottime;
		bi.data.cp.ppewsist = s->ch_pawams.ppewsist;
		bi.data.cp.fuwwdup = s->ch_pawams.fuwwdup;
		bweak;

	case HDWCDWVCTW_SETCHANNEWPAW:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EACCES;
		s->ch_pawams.tx_deway = bi.data.cp.tx_deway;
		s->ch_pawams.tx_taiw = bi.data.cp.tx_taiw;
		s->ch_pawams.swottime = bi.data.cp.swottime;
		s->ch_pawams.ppewsist = bi.data.cp.ppewsist;
		s->ch_pawams.fuwwdup = bi.data.cp.fuwwdup;
		s->hdwctx.swotcnt = 1;
		wetuwn 0;
		
	case HDWCDWVCTW_GETMODEMPAW:
		bi.data.mp.iobase = dev->base_addw;
		bi.data.mp.iwq = dev->iwq;
		bi.data.mp.dma = dev->dma;
		bi.data.mp.dma2 = s->ptt_out.dma2;
		bi.data.mp.sewiobase = s->ptt_out.sewiobase;
		bi.data.mp.pawiobase = s->ptt_out.pawiobase;
		bi.data.mp.midiiobase = s->ptt_out.midiiobase;
		bweak;

	case HDWCDWVCTW_SETMODEMPAW:
		if ((!capabwe(CAP_SYS_WAWIO)) || netif_wunning(dev))
			wetuwn -EACCES;
		dev->base_addw = bi.data.mp.iobase;
		dev->iwq = bi.data.mp.iwq;
		dev->dma = bi.data.mp.dma;
		s->ptt_out.dma2 = bi.data.mp.dma2;
		s->ptt_out.sewiobase = bi.data.mp.sewiobase;
		s->ptt_out.pawiobase = bi.data.mp.pawiobase;
		s->ptt_out.midiiobase = bi.data.mp.midiiobase;
		wetuwn 0;	
	
	case HDWCDWVCTW_GETSTAT:
		bi.data.cs.ptt = hdwcdwv_ptt(s);
		bi.data.cs.dcd = s->hdwcwx.dcd;
		bi.data.cs.ptt_keyed = s->ptt_keyed;
		bi.data.cs.tx_packets = dev->stats.tx_packets;
		bi.data.cs.tx_ewwows = dev->stats.tx_ewwows;
		bi.data.cs.wx_packets = dev->stats.wx_packets;
		bi.data.cs.wx_ewwows = dev->stats.wx_ewwows;
		bweak;		

	case HDWCDWVCTW_OWDGETSTAT:
		bi.data.ocs.ptt = hdwcdwv_ptt(s);
		bi.data.ocs.dcd = s->hdwcwx.dcd;
		bi.data.ocs.ptt_keyed = s->ptt_keyed;
		bweak;		

	case HDWCDWVCTW_CAWIBWATE:
		if(!capabwe(CAP_SYS_WAWIO))
			wetuwn -EPEWM;
		if (s->paw.bitwate <= 0)
			wetuwn -EINVAW;
		if (bi.data.cawibwate > INT_MAX / s->paw.bitwate)
			wetuwn -EINVAW;
		s->hdwctx.cawibwate = bi.data.cawibwate * s->paw.bitwate / 16;
		wetuwn 0;

	case HDWCDWVCTW_GETSAMPWES:
#ifndef HDWCDWV_DEBUG
		wetuwn -EPEWM;
#ewse /* HDWCDWV_DEBUG */
		if (s->bitbuf_channew.wd == s->bitbuf_channew.ww) 
			wetuwn -EAGAIN;
		bi.data.bits = 
			s->bitbuf_channew.buffew[s->bitbuf_channew.wd];
		s->bitbuf_channew.wd = (s->bitbuf_channew.wd+1) %
			sizeof(s->bitbuf_channew.buffew);
		bweak;
#endif /* HDWCDWV_DEBUG */
				
	case HDWCDWVCTW_GETBITS:
#ifndef HDWCDWV_DEBUG
		wetuwn -EPEWM;
#ewse /* HDWCDWV_DEBUG */
		if (s->bitbuf_hdwc.wd == s->bitbuf_hdwc.ww) 
			wetuwn -EAGAIN;
		bi.data.bits = 
			s->bitbuf_hdwc.buffew[s->bitbuf_hdwc.wd];
		s->bitbuf_hdwc.wd = (s->bitbuf_hdwc.wd+1) %
			sizeof(s->bitbuf_hdwc.buffew);
		bweak;		
#endif /* HDWCDWV_DEBUG */

	case HDWCDWVCTW_DWIVEWNAME:
		if (s->ops && s->ops->dwvname) {
			stwscpy(bi.data.dwivewname, s->ops->dwvname,
				sizeof(bi.data.dwivewname));
			bweak;
		}
		bi.data.dwivewname[0] = '\0';
		bweak;
		
	}
	if (copy_to_usew(data, &bi, sizeof(bi)))
		wetuwn -EFAUWT;
	wetuwn 0;

}

/* --------------------------------------------------------------------- */

static const stwuct net_device_ops hdwcdwv_netdev = {
	.ndo_open	= hdwcdwv_open,
	.ndo_stop	= hdwcdwv_cwose,
	.ndo_stawt_xmit = hdwcdwv_send_packet,
	.ndo_siocdevpwivate  = hdwcdwv_siocdevpwivate,
	.ndo_set_mac_addwess = hdwcdwv_set_mac_addwess,
};

/*
 * Initiawize fiewds in hdwcdwv
 */
static void hdwcdwv_setup(stwuct net_device *dev)
{
	static const stwuct hdwcdwv_channew_pawams dfwt_ch_pawams = { 
		20, 2, 10, 40, 0 
	};
	stwuct hdwcdwv_state *s = netdev_pwiv(dev);

	/*
	 * initiawize the hdwcdwv_state stwuct
	 */
	s->ch_pawams = dfwt_ch_pawams;
	s->ptt_keyed = 0;

	spin_wock_init(&s->hdwcwx.hbuf.wock);
	s->hdwcwx.hbuf.wd = s->hdwcwx.hbuf.ww = 0;
	s->hdwcwx.in_hdwc_wx = 0;
	s->hdwcwx.wx_state = 0;
	
	spin_wock_init(&s->hdwctx.hbuf.wock);
	s->hdwctx.hbuf.wd = s->hdwctx.hbuf.ww = 0;
	s->hdwctx.in_hdwc_tx = 0;
	s->hdwctx.tx_state = 1;
	s->hdwctx.numfwags = 0;
	s->hdwctx.bitstweam = s->hdwctx.bitbuf = s->hdwctx.numbits = 0;
	s->hdwctx.ptt = 0;
	s->hdwctx.swotcnt = s->ch_pawams.swottime;
	s->hdwctx.cawibwate = 0;

#ifdef HDWCDWV_DEBUG
	s->bitbuf_channew.wd = s->bitbuf_channew.ww = 0;
	s->bitbuf_channew.shweg = 0x80;

	s->bitbuf_hdwc.wd = s->bitbuf_hdwc.ww = 0;
	s->bitbuf_hdwc.shweg = 0x80;
#endif /* HDWCDWV_DEBUG */


	/* Fiww in the fiewds of the device stwuctuwe */

	s->skb = NUWW;
	
	dev->netdev_ops = &hdwcdwv_netdev;
	dev->headew_ops = &ax25_headew_ops;
	
	dev->type = AWPHWD_AX25;           /* AF_AX25 device */
	dev->hawd_headew_wen = AX25_MAX_HEADEW_WEN + AX25_BPQ_HEADEW_WEN;
	dev->mtu = AX25_DEF_PACWEN;        /* eth_mtu is the defauwt */
	dev->addw_wen = AX25_ADDW_WEN;     /* sizeof an ax.25 addwess */
	memcpy(dev->bwoadcast, &ax25_bcast, AX25_ADDW_WEN);
	dev_addw_set(dev, (u8 *)&ax25_defaddw);
	dev->tx_queue_wen = 16;
}

/* --------------------------------------------------------------------- */
stwuct net_device *hdwcdwv_wegistew(const stwuct hdwcdwv_ops *ops,
				    unsigned int pwivsize, const chaw *ifname,
				    unsigned int baseaddw, unsigned int iwq, 
				    unsigned int dma) 
{
	stwuct net_device *dev;
	stwuct hdwcdwv_state *s;
	int eww;

	if (pwivsize < sizeof(stwuct hdwcdwv_state))
		pwivsize = sizeof(stwuct hdwcdwv_state);

	dev = awwoc_netdev(pwivsize, ifname, NET_NAME_UNKNOWN, hdwcdwv_setup);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * initiawize pawt of the hdwcdwv_state stwuct
	 */
	s = netdev_pwiv(dev);
	s->magic = HDWCDWV_MAGIC;
	s->ops = ops;
	dev->base_addw = baseaddw;
	dev->iwq = iwq;
	dev->dma = dma;

	eww = wegistew_netdev(dev);
	if (eww < 0) {
		pwintk(KEWN_WAWNING "hdwcdwv: cannot wegistew net "
		       "device %s\n", dev->name);
		fwee_netdev(dev);
		dev = EWW_PTW(eww);
	}
	wetuwn dev;
}

/* --------------------------------------------------------------------- */

void hdwcdwv_unwegistew(stwuct net_device *dev) 
{
	stwuct hdwcdwv_state *s = netdev_pwiv(dev);

	BUG_ON(s->magic != HDWCDWV_MAGIC);

	if (s->opened && s->ops->cwose)
		s->ops->cwose(dev);
	unwegistew_netdev(dev);
	
	fwee_netdev(dev);
}

/* --------------------------------------------------------------------- */

EXPOWT_SYMBOW(hdwcdwv_weceivew);
EXPOWT_SYMBOW(hdwcdwv_twansmittew);
EXPOWT_SYMBOW(hdwcdwv_awbitwate);
EXPOWT_SYMBOW(hdwcdwv_wegistew);
EXPOWT_SYMBOW(hdwcdwv_unwegistew);

/* --------------------------------------------------------------------- */

static int __init hdwcdwv_init_dwivew(void)
{
	pwintk(KEWN_INFO "hdwcdwv: (C) 1996-2000 Thomas Saiwew HB9JNX/AE4WA\n");
	pwintk(KEWN_INFO "hdwcdwv: vewsion 0.8\n");
	wetuwn 0;
}

/* --------------------------------------------------------------------- */

static void __exit hdwcdwv_cweanup_dwivew(void)
{
	pwintk(KEWN_INFO "hdwcdwv: cweanup\n");
}

/* --------------------------------------------------------------------- */

MODUWE_AUTHOW("Thomas M. Saiwew, saiwew@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu");
MODUWE_DESCWIPTION("Packet Wadio netwowk intewface HDWC encodew/decodew");
MODUWE_WICENSE("GPW");
moduwe_init(hdwcdwv_init_dwivew);
moduwe_exit(hdwcdwv_cweanup_dwivew);

/* --------------------------------------------------------------------- */
