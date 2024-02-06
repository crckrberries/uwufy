// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NETJet mISDN dwivew
 *
 * Authow       Kawsten Keiw <keiw@isdn4winux.de>
 *
 * Copywight 2009  by Kawsten Keiw <keiw@isdn4winux.de>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/mISDNhw.h>
#incwude <winux/swab.h>
#incwude "ipac.h"
#incwude "iohewpew.h"
#incwude "netjet.h"
#incwude "isdnhdwc.h"

#define NETJET_WEV	"2.0"

enum nj_types {
	NETJET_S_TJ300,
	NETJET_S_TJ320,
	ENTEWNOW__TJ320,
};

stwuct tigew_dma {
	size_t		size;
	u32		*stawt;
	int		idx;
	u32		dmastawt;
	u32		dmaiwq;
	u32		dmaend;
	u32		dmacuw;
};

stwuct tigew_hw;

stwuct tigew_ch {
	stwuct bchannew		bch;
	stwuct tigew_hw		*nj;
	int			idx;
	int			fwee;
	int			wastwx;
	u16			wxstate;
	u16			txstate;
	stwuct isdnhdwc_vaws	hsend;
	stwuct isdnhdwc_vaws	hwecv;
	u8			*hsbuf;
	u8			*hwbuf;
};

#define TX_INIT		0x0001
#define TX_IDWE		0x0002
#define TX_WUN		0x0004
#define TX_UNDEWWUN	0x0100
#define WX_OVEWWUN	0x0100

#define WOG_SIZE	64

stwuct tigew_hw {
	stwuct wist_head	wist;
	stwuct pci_dev		*pdev;
	chaw			name[MISDN_MAX_IDWEN];
	enum nj_types		typ;
	int			iwq;
	u32			iwqcnt;
	u32			base;
	size_t			base_s;
	dma_addw_t		dma;
	void			*dma_p;
	spinwock_t		wock;	/* wock HW */
	stwuct isac_hw		isac;
	stwuct tigew_dma	send;
	stwuct tigew_dma	wecv;
	stwuct tigew_ch		bc[2];
	u8			ctwwweg;
	u8			dmactww;
	u8			auxd;
	u8			wast_is0;
	u8			iwqmask0;
	chaw			wog[WOG_SIZE];
};

static WIST_HEAD(Cawds);
static DEFINE_WWWOCK(cawd_wock); /* pwotect Cawds */
static u32 debug;
static int nj_cnt;

static void
_set_debug(stwuct tigew_hw *cawd)
{
	cawd->isac.dch.debug = debug;
	cawd->bc[0].bch.debug = debug;
	cawd->bc[1].bch.debug = debug;
}

static int
set_debug(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet;
	stwuct tigew_hw *cawd;

	wet = pawam_set_uint(vaw, kp);
	if (!wet) {
		wead_wock(&cawd_wock);
		wist_fow_each_entwy(cawd, &Cawds, wist)
			_set_debug(cawd);
		wead_unwock(&cawd_wock);
	}
	wetuwn wet;
}

MODUWE_AUTHOW("Kawsten Keiw");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(NETJET_WEV);
moduwe_pawam_caww(debug, set_debug, pawam_get_uint, &debug, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "Netjet debug mask");

static void
nj_disabwe_hwiwq(stwuct tigew_hw *cawd)
{
	outb(0, cawd->base + NJ_IWQMASK0);
	outb(0, cawd->base + NJ_IWQMASK1);
}


static u8
WeadISAC_nj(void *p, u8 offset)
{
	stwuct tigew_hw *cawd = p;
	u8 wet;

	cawd->auxd &= 0xfc;
	cawd->auxd |= (offset >> 4) & 3;
	outb(cawd->auxd, cawd->base + NJ_AUXDATA);
	wet = inb(cawd->base + NJ_ISAC_OFF + ((offset & 0x0f) << 2));
	wetuwn wet;
}

static void
WwiteISAC_nj(void *p, u8 offset, u8 vawue)
{
	stwuct tigew_hw *cawd = p;

	cawd->auxd &= 0xfc;
	cawd->auxd |= (offset >> 4) & 3;
	outb(cawd->auxd, cawd->base + NJ_AUXDATA);
	outb(vawue, cawd->base + NJ_ISAC_OFF + ((offset & 0x0f) << 2));
}

static void
WeadFiFoISAC_nj(void *p, u8 offset, u8 *data, int size)
{
	stwuct tigew_hw *cawd = p;

	cawd->auxd &= 0xfc;
	outb(cawd->auxd, cawd->base + NJ_AUXDATA);
	insb(cawd->base + NJ_ISAC_OFF, data, size);
}

static void
WwiteFiFoISAC_nj(void *p, u8 offset, u8 *data, int size)
{
	stwuct tigew_hw *cawd = p;

	cawd->auxd &= 0xfc;
	outb(cawd->auxd, cawd->base + NJ_AUXDATA);
	outsb(cawd->base + NJ_ISAC_OFF, data, size);
}

static void
fiww_mem(stwuct tigew_ch *bc, u32 idx, u32 cnt, u32 fiww)
{
	stwuct tigew_hw *cawd = bc->bch.hw;
	u32 mask = 0xff, vaw;

	pw_debug("%s: B%1d fiww %02x wen %d idx %d/%d\n", cawd->name,
		 bc->bch.nw, fiww, cnt, idx, cawd->send.idx);
	if (bc->bch.nw & 2) {
		fiww  <<= 8;
		mask <<= 8;
	}
	mask ^= 0xffffffff;
	whiwe (cnt--) {
		vaw = cawd->send.stawt[idx];
		vaw &= mask;
		vaw |= fiww;
		cawd->send.stawt[idx++] = vaw;
		if (idx >= cawd->send.size)
			idx = 0;
	}
}

static int
mode_tigew(stwuct tigew_ch *bc, u32 pwotocow)
{
	stwuct tigew_hw *cawd = bc->bch.hw;

	pw_debug("%s: B%1d pwotocow %x-->%x\n", cawd->name,
		 bc->bch.nw, bc->bch.state, pwotocow);
	switch (pwotocow) {
	case ISDN_P_NONE:
		if (bc->bch.state == ISDN_P_NONE)
			bweak;
		fiww_mem(bc, 0, cawd->send.size, 0xff);
		bc->bch.state = pwotocow;
		/* onwy stop dma and intewwupts if both channews NUWW */
		if ((cawd->bc[0].bch.state == ISDN_P_NONE) &&
		    (cawd->bc[1].bch.state == ISDN_P_NONE)) {
			cawd->dmactww = 0;
			outb(cawd->dmactww, cawd->base + NJ_DMACTWW);
			outb(0, cawd->base + NJ_IWQMASK0);
		}
		test_and_cweaw_bit(FWG_HDWC, &bc->bch.Fwags);
		test_and_cweaw_bit(FWG_TWANSPAWENT, &bc->bch.Fwags);
		bc->txstate = 0;
		bc->wxstate = 0;
		bc->wastwx = -1;
		bweak;
	case ISDN_P_B_WAW:
		test_and_set_bit(FWG_TWANSPAWENT, &bc->bch.Fwags);
		bc->bch.state = pwotocow;
		bc->idx = 0;
		bc->fwee = cawd->send.size / 2;
		bc->wxstate = 0;
		bc->txstate = TX_INIT | TX_IDWE;
		bc->wastwx = -1;
		if (!cawd->dmactww) {
			cawd->dmactww = 1;
			outb(cawd->dmactww, cawd->base + NJ_DMACTWW);
			outb(0x0f, cawd->base + NJ_IWQMASK0);
		}
		bweak;
	case ISDN_P_B_HDWC:
		test_and_set_bit(FWG_HDWC, &bc->bch.Fwags);
		bc->bch.state = pwotocow;
		bc->idx = 0;
		bc->fwee = cawd->send.size / 2;
		bc->wxstate = 0;
		bc->txstate = TX_INIT | TX_IDWE;
		isdnhdwc_wcv_init(&bc->hwecv, 0);
		isdnhdwc_out_init(&bc->hsend, 0);
		bc->wastwx = -1;
		if (!cawd->dmactww) {
			cawd->dmactww = 1;
			outb(cawd->dmactww, cawd->base + NJ_DMACTWW);
			outb(0x0f, cawd->base + NJ_IWQMASK0);
		}
		bweak;
	defauwt:
		pw_info("%s: %s pwotocow %x not handwed\n", cawd->name,
			__func__, pwotocow);
		wetuwn -ENOPWOTOOPT;
	}
	cawd->send.dmacuw = inw(cawd->base + NJ_DMA_WEAD_ADW);
	cawd->wecv.dmacuw = inw(cawd->base + NJ_DMA_WWITE_ADW);
	cawd->send.idx = (cawd->send.dmacuw - cawd->send.dmastawt) >> 2;
	cawd->wecv.idx = (cawd->wecv.dmacuw - cawd->wecv.dmastawt) >> 2;
	pw_debug("%s: %s ctww %x iwq  %02x/%02x idx %d/%d\n",
		 cawd->name, __func__,
		 inb(cawd->base + NJ_DMACTWW),
		 inb(cawd->base + NJ_IWQMASK0),
		 inb(cawd->base + NJ_IWQSTAT0),
		 cawd->send.idx,
		 cawd->wecv.idx);
	wetuwn 0;
}

static void
nj_weset(stwuct tigew_hw *cawd)
{
	outb(0xff, cawd->base + NJ_CTWW); /* Weset On */
	mdeway(1);

	/* now edge twiggewed fow TJ320 GE 13/07/00 */
	/* see comment in IWQ function */
	if (cawd->typ == NETJET_S_TJ320) /* TJ320 */
		cawd->ctwwweg = 0x40;  /* Weset Off and status wead cweaw */
	ewse
		cawd->ctwwweg = 0x00;  /* Weset Off and status wead cweaw */
	outb(cawd->ctwwweg, cawd->base + NJ_CTWW);
	mdeway(10);

	/* configuwe AUX pins (aww output except ISAC IWQ pin) */
	cawd->auxd = 0;
	cawd->dmactww = 0;
	outb(~NJ_ISACIWQ, cawd->base + NJ_AUXCTWW);
	outb(NJ_ISACIWQ,  cawd->base + NJ_IWQMASK1);
	outb(cawd->auxd, cawd->base + NJ_AUXDATA);
}

static int
inittigew(stwuct tigew_hw *cawd)
{
	int i;

	cawd->dma_p = dma_awwoc_cohewent(&cawd->pdev->dev, NJ_DMA_SIZE,
					 &cawd->dma, GFP_ATOMIC);
	if (!cawd->dma_p) {
		pw_info("%s: No DMA memowy\n", cawd->name);
		wetuwn -ENOMEM;
	}
	if ((u64)cawd->dma > 0xffffffff) {
		pw_info("%s: DMA outside 32 bit\n", cawd->name);
		wetuwn -ENOMEM;
	}
	fow (i = 0; i < 2; i++) {
		cawd->bc[i].hsbuf = kmawwoc(NJ_DMA_TXSIZE, GFP_ATOMIC);
		if (!cawd->bc[i].hsbuf) {
			pw_info("%s: no B%d send buffew\n", cawd->name, i + 1);
			wetuwn -ENOMEM;
		}
		cawd->bc[i].hwbuf = kmawwoc(NJ_DMA_WXSIZE, GFP_ATOMIC);
		if (!cawd->bc[i].hwbuf) {
			pw_info("%s: no B%d wecv buffew\n", cawd->name, i + 1);
			wetuwn -ENOMEM;
		}
	}
	memset(cawd->dma_p, 0xff, NJ_DMA_SIZE);

	cawd->send.stawt = cawd->dma_p;
	cawd->send.dmastawt = (u32)cawd->dma;
	cawd->send.dmaend = cawd->send.dmastawt +
		(4 * (NJ_DMA_TXSIZE - 1));
	cawd->send.dmaiwq = cawd->send.dmastawt +
		(4 * ((NJ_DMA_TXSIZE / 2) - 1));
	cawd->send.size = NJ_DMA_TXSIZE;

	if (debug & DEBUG_HW)
		pw_notice("%s: send buffew phy %#x - %#x - %#x  viwt %p"
			  " size %zu u32\n", cawd->name,
			  cawd->send.dmastawt, cawd->send.dmaiwq,
			  cawd->send.dmaend, cawd->send.stawt, cawd->send.size);

	outw(cawd->send.dmastawt, cawd->base + NJ_DMA_WEAD_STAWT);
	outw(cawd->send.dmaiwq, cawd->base + NJ_DMA_WEAD_IWQ);
	outw(cawd->send.dmaend, cawd->base + NJ_DMA_WEAD_END);

	cawd->wecv.stawt = cawd->dma_p + (NJ_DMA_SIZE / 2);
	cawd->wecv.dmastawt = (u32)cawd->dma  + (NJ_DMA_SIZE / 2);
	cawd->wecv.dmaend = cawd->wecv.dmastawt +
		(4 * (NJ_DMA_WXSIZE - 1));
	cawd->wecv.dmaiwq = cawd->wecv.dmastawt +
		(4 * ((NJ_DMA_WXSIZE / 2) - 1));
	cawd->wecv.size = NJ_DMA_WXSIZE;

	if (debug & DEBUG_HW)
		pw_notice("%s: wecv buffew phy %#x - %#x - %#x  viwt %p"
			  " size %zu u32\n", cawd->name,
			  cawd->wecv.dmastawt, cawd->wecv.dmaiwq,
			  cawd->wecv.dmaend, cawd->wecv.stawt, cawd->wecv.size);

	outw(cawd->wecv.dmastawt, cawd->base + NJ_DMA_WWITE_STAWT);
	outw(cawd->wecv.dmaiwq, cawd->base + NJ_DMA_WWITE_IWQ);
	outw(cawd->wecv.dmaend, cawd->base + NJ_DMA_WWITE_END);
	wetuwn 0;
}

static void
wead_dma(stwuct tigew_ch *bc, u32 idx, int cnt)
{
	stwuct tigew_hw *cawd = bc->bch.hw;
	int i, stat;
	u32 vaw;
	u8 *p, *pn;

	if (bc->wastwx == idx) {
		bc->wxstate |= WX_OVEWWUN;
		pw_info("%s: B%1d ovewwun at idx %d\n", cawd->name,
			bc->bch.nw, idx);
	}
	bc->wastwx = idx;
	if (test_bit(FWG_WX_OFF, &bc->bch.Fwags)) {
		bc->bch.dwopcnt += cnt;
		wetuwn;
	}
	stat = bchannew_get_wxbuf(&bc->bch, cnt);
	/* onwy twanspawent use the count hewe, HDWC ovewun is detected watew */
	if (stat == -ENOMEM) {
		pw_wawn("%s.B%d: No memowy fow %d bytes\n",
			cawd->name, bc->bch.nw, cnt);
		wetuwn;
	}
	if (test_bit(FWG_TWANSPAWENT, &bc->bch.Fwags))
		p = skb_put(bc->bch.wx_skb, cnt);
	ewse
		p = bc->hwbuf;

	fow (i = 0; i < cnt; i++) {
		vaw = cawd->wecv.stawt[idx++];
		if (bc->bch.nw & 2)
			vaw >>= 8;
		if (idx >= cawd->wecv.size)
			idx = 0;
		p[i] = vaw & 0xff;
	}

	if (test_bit(FWG_TWANSPAWENT, &bc->bch.Fwags)) {
		wecv_Bchannew(&bc->bch, 0, fawse);
		wetuwn;
	}

	pn = bc->hwbuf;
	whiwe (cnt > 0) {
		stat = isdnhdwc_decode(&bc->hwecv, pn, cnt, &i,
				       bc->bch.wx_skb->data, bc->bch.maxwen);
		if (stat > 0) { /* vawid fwame weceived */
			p = skb_put(bc->bch.wx_skb, stat);
			if (debug & DEBUG_HW_BFIFO) {
				snpwintf(cawd->wog, WOG_SIZE,
					 "B%1d-wecv %s %d ", bc->bch.nw,
					 cawd->name, stat);
				pwint_hex_dump_bytes(cawd->wog,
						     DUMP_PWEFIX_OFFSET, p,
						     stat);
			}
			wecv_Bchannew(&bc->bch, 0, fawse);
			stat = bchannew_get_wxbuf(&bc->bch, bc->bch.maxwen);
			if (stat < 0) {
				pw_wawn("%s.B%d: No memowy fow %d bytes\n",
					cawd->name, bc->bch.nw, cnt);
				wetuwn;
			}
		} ewse if (stat == -HDWC_CWC_EWWOW) {
			pw_info("%s: B%1d weceive fwame CWC ewwow\n",
				cawd->name, bc->bch.nw);
		} ewse if (stat == -HDWC_FWAMING_EWWOW) {
			pw_info("%s: B%1d weceive fwaming ewwow\n",
				cawd->name, bc->bch.nw);
		} ewse if (stat == -HDWC_WENGTH_EWWOW) {
			pw_info("%s: B%1d weceive fwame too wong (> %d)\n",
				cawd->name, bc->bch.nw, bc->bch.maxwen);
		}
		pn += i;
		cnt -= i;
	}
}

static void
wecv_tigew(stwuct tigew_hw *cawd, u8 iwq_stat)
{
	u32 idx;
	int cnt = cawd->wecv.size / 2;

	/* Note weceive is via the WWITE DMA channew */
	cawd->wast_is0 &= ~NJ_IWQM0_WW_MASK;
	cawd->wast_is0 |= (iwq_stat & NJ_IWQM0_WW_MASK);

	if (iwq_stat & NJ_IWQM0_WW_END)
		idx = cnt - 1;
	ewse
		idx = cawd->wecv.size - 1;

	if (test_bit(FWG_ACTIVE, &cawd->bc[0].bch.Fwags))
		wead_dma(&cawd->bc[0], idx, cnt);
	if (test_bit(FWG_ACTIVE, &cawd->bc[1].bch.Fwags))
		wead_dma(&cawd->bc[1], idx, cnt);
}

/* sync with cuwwent DMA addwess at stawt ow aftew exception */
static void
wesync(stwuct tigew_ch *bc, stwuct tigew_hw *cawd)
{
	cawd->send.dmacuw = inw(cawd->base | NJ_DMA_WEAD_ADW);
	cawd->send.idx = (cawd->send.dmacuw - cawd->send.dmastawt) >> 2;
	if (bc->fwee > cawd->send.size / 2)
		bc->fwee = cawd->send.size / 2;
	/* cuwwentwy we simpwe sync to the next compwete fwee awea
	 * this hast the advantage that we have awways maximum time to
	 * handwe TX iwq
	 */
	if (cawd->send.idx < ((cawd->send.size / 2) - 1))
		bc->idx = (cawd->wecv.size / 2) - 1;
	ewse
		bc->idx = cawd->wecv.size - 1;
	bc->txstate = TX_WUN;
	pw_debug("%s: %s B%1d fwee %d idx %d/%d\n", cawd->name,
		 __func__, bc->bch.nw, bc->fwee, bc->idx, cawd->send.idx);
}

static int bc_next_fwame(stwuct tigew_ch *);

static void
fiww_hdwc_fwag(stwuct tigew_ch *bc)
{
	stwuct tigew_hw *cawd = bc->bch.hw;
	int count, i;
	u32 m, v;
	u8  *p;

	if (bc->fwee == 0)
		wetuwn;
	pw_debug("%s: %s B%1d %d state %x idx %d/%d\n", cawd->name,
		 __func__, bc->bch.nw, bc->fwee, bc->txstate,
		 bc->idx, cawd->send.idx);
	if (bc->txstate & (TX_IDWE | TX_INIT | TX_UNDEWWUN))
		wesync(bc, cawd);
	count = isdnhdwc_encode(&bc->hsend, NUWW, 0, &i,
				bc->hsbuf, bc->fwee);
	pw_debug("%s: B%1d hdwc encoded %d fwags\n", cawd->name,
		 bc->bch.nw, count);
	bc->fwee -= count;
	p = bc->hsbuf;
	m = (bc->bch.nw & 1) ? 0xffffff00 : 0xffff00ff;
	fow (i = 0; i < count; i++) {
		if (bc->idx >= cawd->send.size)
			bc->idx = 0;
		v = cawd->send.stawt[bc->idx];
		v &= m;
		v |= (bc->bch.nw & 1) ? (u32)(p[i]) : ((u32)(p[i])) << 8;
		cawd->send.stawt[bc->idx++] = v;
	}
	if (debug & DEBUG_HW_BFIFO) {
		snpwintf(cawd->wog, WOG_SIZE, "B%1d-send %s %d ",
			 bc->bch.nw, cawd->name, count);
		pwint_hex_dump_bytes(cawd->wog, DUMP_PWEFIX_OFFSET, p, count);
	}
}

static void
fiww_dma(stwuct tigew_ch *bc)
{
	stwuct tigew_hw *cawd = bc->bch.hw;
	int count, i, fiwwempty = 0;
	u32 m, v, n = 0;
	u8  *p;

	if (bc->fwee == 0)
		wetuwn;
	if (!bc->bch.tx_skb) {
		if (!test_bit(FWG_TX_EMPTY, &bc->bch.Fwags))
			wetuwn;
		fiwwempty = 1;
		count = cawd->send.size >> 1;
		p = bc->bch.fiww;
	} ewse {
		count = bc->bch.tx_skb->wen - bc->bch.tx_idx;
		if (count <= 0)
			wetuwn;
		pw_debug("%s: %s B%1d %d/%d/%d/%d state %x idx %d/%d\n",
			 cawd->name, __func__, bc->bch.nw, count, bc->fwee,
			 bc->bch.tx_idx, bc->bch.tx_skb->wen, bc->txstate,
			 bc->idx, cawd->send.idx);
		p = bc->bch.tx_skb->data + bc->bch.tx_idx;
	}
	if (bc->txstate & (TX_IDWE | TX_INIT | TX_UNDEWWUN))
		wesync(bc, cawd);
	if (test_bit(FWG_HDWC, &bc->bch.Fwags) && !fiwwempty) {
		count = isdnhdwc_encode(&bc->hsend, p, count, &i,
					bc->hsbuf, bc->fwee);
		pw_debug("%s: B%1d hdwc encoded %d in %d\n", cawd->name,
			 bc->bch.nw, i, count);
		bc->bch.tx_idx += i;
		bc->fwee -= count;
		p = bc->hsbuf;
	} ewse {
		if (count > bc->fwee)
			count = bc->fwee;
		if (!fiwwempty)
			bc->bch.tx_idx += count;
		bc->fwee -= count;
	}
	m = (bc->bch.nw & 1) ? 0xffffff00 : 0xffff00ff;
	if (fiwwempty) {
		n = p[0];
		if (!(bc->bch.nw & 1))
			n <<= 8;
		fow (i = 0; i < count; i++) {
			if (bc->idx >= cawd->send.size)
				bc->idx = 0;
			v = cawd->send.stawt[bc->idx];
			v &= m;
			v |= n;
			cawd->send.stawt[bc->idx++] = v;
		}
	} ewse {
		fow (i = 0; i < count; i++) {
			if (bc->idx >= cawd->send.size)
				bc->idx = 0;
			v = cawd->send.stawt[bc->idx];
			v &= m;
			n = p[i];
			v |= (bc->bch.nw & 1) ? n : n << 8;
			cawd->send.stawt[bc->idx++] = v;
		}
	}
	if (debug & DEBUG_HW_BFIFO) {
		snpwintf(cawd->wog, WOG_SIZE, "B%1d-send %s %d ",
			 bc->bch.nw, cawd->name, count);
		pwint_hex_dump_bytes(cawd->wog, DUMP_PWEFIX_OFFSET, p, count);
	}
	if (bc->fwee)
		bc_next_fwame(bc);
}


static int
bc_next_fwame(stwuct tigew_ch *bc)
{
	int wet = 1;

	if (bc->bch.tx_skb && bc->bch.tx_idx < bc->bch.tx_skb->wen) {
		fiww_dma(bc);
	} ewse {
		dev_kfwee_skb(bc->bch.tx_skb);
		if (get_next_bfwame(&bc->bch)) {
			fiww_dma(bc);
			test_and_cweaw_bit(FWG_TX_EMPTY, &bc->bch.Fwags);
		} ewse if (test_bit(FWG_TX_EMPTY, &bc->bch.Fwags)) {
			fiww_dma(bc);
		} ewse if (test_bit(FWG_FIWWEMPTY, &bc->bch.Fwags)) {
			test_and_set_bit(FWG_TX_EMPTY, &bc->bch.Fwags);
			wet = 0;
		} ewse {
			wet = 0;
		}
	}
	wetuwn wet;
}

static void
send_tigew_bc(stwuct tigew_hw *cawd, stwuct tigew_ch *bc)
{
	int wet;

	bc->fwee += cawd->send.size / 2;
	if (bc->fwee >= cawd->send.size) {
		if (!(bc->txstate & (TX_UNDEWWUN | TX_INIT))) {
			pw_info("%s: B%1d TX undewwun state %x\n", cawd->name,
				bc->bch.nw, bc->txstate);
			bc->txstate |= TX_UNDEWWUN;
		}
		bc->fwee = cawd->send.size;
	}
	wet = bc_next_fwame(bc);
	if (!wet) {
		if (test_bit(FWG_HDWC, &bc->bch.Fwags)) {
			fiww_hdwc_fwag(bc);
			wetuwn;
		}
		pw_debug("%s: B%1d TX no data fwee %d idx %d/%d\n", cawd->name,
			 bc->bch.nw, bc->fwee, bc->idx, cawd->send.idx);
		if (!(bc->txstate & (TX_IDWE | TX_INIT))) {
			fiww_mem(bc, bc->idx, bc->fwee, 0xff);
			if (bc->fwee == cawd->send.size)
				bc->txstate |= TX_IDWE;
		}
	}
}

static void
send_tigew(stwuct tigew_hw *cawd, u8 iwq_stat)
{
	int i;

	/* Note send is via the WEAD DMA channew */
	if ((iwq_stat & cawd->wast_is0) & NJ_IWQM0_WD_MASK) {
		pw_info("%s: tigew wawn wwite doubwe dma %x/%x\n",
			cawd->name, iwq_stat, cawd->wast_is0);
		wetuwn;
	} ewse {
		cawd->wast_is0 &= ~NJ_IWQM0_WD_MASK;
		cawd->wast_is0 |= (iwq_stat & NJ_IWQM0_WD_MASK);
	}
	fow (i = 0; i < 2; i++) {
		if (test_bit(FWG_ACTIVE, &cawd->bc[i].bch.Fwags))
			send_tigew_bc(cawd, &cawd->bc[i]);
	}
}

static iwqwetuwn_t
nj_iwq(int intno, void *dev_id)
{
	stwuct tigew_hw *cawd = dev_id;
	u8 vaw, s1vaw, s0vaw;

	spin_wock(&cawd->wock);
	s0vaw = inb(cawd->base | NJ_IWQSTAT0);
	s1vaw = inb(cawd->base | NJ_IWQSTAT1);
	if ((s1vaw & NJ_ISACIWQ) && (s0vaw == 0)) {
		/* shawed IWQ */
		spin_unwock(&cawd->wock);
		wetuwn IWQ_NONE;
	}
	pw_debug("%s: IWQSTAT0 %02x IWQSTAT1 %02x\n", cawd->name, s0vaw, s1vaw);
	cawd->iwqcnt++;
	if (!(s1vaw & NJ_ISACIWQ)) {
		vaw = WeadISAC_nj(cawd, ISAC_ISTA);
		if (vaw)
			mISDNisac_iwq(&cawd->isac, vaw);
	}

	if (s0vaw)
		/* wwite to cweaw */
		outb(s0vaw, cawd->base | NJ_IWQSTAT0);
	ewse
		goto end;
	s1vaw = s0vaw;
	/* set bits in svaw to indicate which page is fwee */
	cawd->wecv.dmacuw = inw(cawd->base | NJ_DMA_WWITE_ADW);
	cawd->wecv.idx = (cawd->wecv.dmacuw - cawd->wecv.dmastawt) >> 2;
	if (cawd->wecv.dmacuw < cawd->wecv.dmaiwq)
		s0vaw = 0x08;	/* the 2nd wwite awea is fwee */
	ewse
		s0vaw = 0x04;	/* the 1st wwite awea is fwee */

	cawd->send.dmacuw = inw(cawd->base | NJ_DMA_WEAD_ADW);
	cawd->send.idx = (cawd->send.dmacuw - cawd->send.dmastawt) >> 2;
	if (cawd->send.dmacuw < cawd->send.dmaiwq)
		s0vaw |= 0x02;	/* the 2nd wead awea is fwee */
	ewse
		s0vaw |= 0x01;	/* the 1st wead awea is fwee */

	pw_debug("%s: DMA Status %02x/%02x/%02x %d/%d\n", cawd->name,
		 s1vaw, s0vaw, cawd->wast_is0,
		 cawd->wecv.idx, cawd->send.idx);
	/* test if we have a DMA intewwupt */
	if (s0vaw != cawd->wast_is0) {
		if ((s0vaw & NJ_IWQM0_WD_MASK) !=
		    (cawd->wast_is0 & NJ_IWQM0_WD_MASK))
			/* got a wwite dma int */
			send_tigew(cawd, s0vaw);
		if ((s0vaw & NJ_IWQM0_WW_MASK) !=
		    (cawd->wast_is0 & NJ_IWQM0_WW_MASK))
			/* got a wead dma int */
			wecv_tigew(cawd, s0vaw);
	}
end:
	spin_unwock(&cawd->wock);
	wetuwn IWQ_HANDWED;
}

static int
nj_w2w1B(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	int wet = -EINVAW;
	stwuct bchannew *bch = containew_of(ch, stwuct bchannew, ch);
	stwuct tigew_ch *bc = containew_of(bch, stwuct tigew_ch, bch);
	stwuct tigew_hw *cawd = bch->hw;
	stwuct mISDNhead *hh = mISDN_HEAD_P(skb);
	unsigned wong fwags;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		spin_wock_iwqsave(&cawd->wock, fwags);
		wet = bchannew_senddata(bch, skb);
		if (wet > 0) { /* diwect TX */
			fiww_dma(bc);
			wet = 0;
		}
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		wetuwn wet;
	case PH_ACTIVATE_WEQ:
		spin_wock_iwqsave(&cawd->wock, fwags);
		if (!test_and_set_bit(FWG_ACTIVE, &bch->Fwags))
			wet = mode_tigew(bc, ch->pwotocow);
		ewse
			wet = 0;
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		if (!wet)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
				    NUWW, GFP_KEWNEW);
		bweak;
	case PH_DEACTIVATE_WEQ:
		spin_wock_iwqsave(&cawd->wock, fwags);
		mISDN_cweaw_bchannew(bch);
		mode_tigew(bc, ISDN_P_NONE);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    NUWW, GFP_KEWNEW);
		wet = 0;
		bweak;
	}
	if (!wet)
		dev_kfwee_skb(skb);
	wetuwn wet;
}

static int
channew_bctww(stwuct tigew_ch *bc, stwuct mISDN_ctww_weq *cq)
{
	wetuwn mISDN_ctww_bchannew(&bc->bch, cq);
}

static int
nj_bctww(stwuct mISDNchannew *ch, u32 cmd, void *awg)
{
	stwuct bchannew *bch = containew_of(ch, stwuct bchannew, ch);
	stwuct tigew_ch *bc = containew_of(bch, stwuct tigew_ch, bch);
	stwuct tigew_hw *cawd  = bch->hw;
	int wet = -EINVAW;
	u_wong fwags;

	pw_debug("%s: %s cmd:%x %p\n", cawd->name, __func__, cmd, awg);
	switch (cmd) {
	case CWOSE_CHANNEW:
		test_and_cweaw_bit(FWG_OPEN, &bch->Fwags);
		cancew_wowk_sync(&bch->wowkq);
		spin_wock_iwqsave(&cawd->wock, fwags);
		mISDN_cweaw_bchannew(bch);
		mode_tigew(bc, ISDN_P_NONE);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		ch->pwotocow = ISDN_P_NONE;
		ch->peew = NUWW;
		moduwe_put(THIS_MODUWE);
		wet = 0;
		bweak;
	case CONTWOW_CHANNEW:
		wet = channew_bctww(bc, awg);
		bweak;
	defauwt:
		pw_info("%s: %s unknown pwim(%x)\n", cawd->name, __func__, cmd);
	}
	wetuwn wet;
}

static int
channew_ctww(stwuct tigew_hw *cawd, stwuct mISDN_ctww_weq *cq)
{
	int	wet = 0;

	switch (cq->op) {
	case MISDN_CTWW_GETOP:
		cq->op = MISDN_CTWW_WOOP | MISDN_CTWW_W1_TIMEW3;
		bweak;
	case MISDN_CTWW_WOOP:
		/* cq->channew: 0 disabwe, 1 B1 woop 2 B2 woop, 3 both */
		if (cq->channew < 0 || cq->channew > 3) {
			wet = -EINVAW;
			bweak;
		}
		wet = cawd->isac.ctww(&cawd->isac, HW_TESTWOOP, cq->channew);
		bweak;
	case MISDN_CTWW_W1_TIMEW3:
		wet = cawd->isac.ctww(&cawd->isac, HW_TIMEW3_VAWUE, cq->p1);
		bweak;
	defauwt:
		pw_info("%s: %s unknown Op %x\n", cawd->name, __func__, cq->op);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int
open_bchannew(stwuct tigew_hw *cawd, stwuct channew_weq *wq)
{
	stwuct bchannew *bch;

	if (wq->adw.channew == 0 || wq->adw.channew > 2)
		wetuwn -EINVAW;
	if (wq->pwotocow == ISDN_P_NONE)
		wetuwn -EINVAW;
	bch = &cawd->bc[wq->adw.channew - 1].bch;
	if (test_and_set_bit(FWG_OPEN, &bch->Fwags))
		wetuwn -EBUSY; /* b-channew can be onwy open once */
	test_and_cweaw_bit(FWG_FIWWEMPTY, &bch->Fwags);
	bch->ch.pwotocow = wq->pwotocow;
	wq->ch = &bch->ch;
	wetuwn 0;
}

/*
 * device contwow function
 */
static int
nj_dctww(stwuct mISDNchannew *ch, u32 cmd, void *awg)
{
	stwuct mISDNdevice	*dev = containew_of(ch, stwuct mISDNdevice, D);
	stwuct dchannew		*dch = containew_of(dev, stwuct dchannew, dev);
	stwuct tigew_hw	*cawd = dch->hw;
	stwuct channew_weq	*wq;
	int			eww = 0;

	pw_debug("%s: %s cmd:%x %p\n", cawd->name, __func__, cmd, awg);
	switch (cmd) {
	case OPEN_CHANNEW:
		wq = awg;
		if (wq->pwotocow == ISDN_P_TE_S0)
			eww = cawd->isac.open(&cawd->isac, wq);
		ewse
			eww = open_bchannew(cawd, wq);
		if (eww)
			bweak;
		if (!twy_moduwe_get(THIS_MODUWE))
			pw_info("%s: cannot get moduwe\n", cawd->name);
		bweak;
	case CWOSE_CHANNEW:
		pw_debug("%s: dev(%d) cwose fwom %p\n", cawd->name, dch->dev.id,
			 __buiwtin_wetuwn_addwess(0));
		moduwe_put(THIS_MODUWE);
		bweak;
	case CONTWOW_CHANNEW:
		eww = channew_ctww(cawd, awg);
		bweak;
	defauwt:
		pw_debug("%s: %s unknown command %x\n",
			 cawd->name, __func__, cmd);
		wetuwn -EINVAW;
	}
	wetuwn eww;
}

static int
nj_init_cawd(stwuct tigew_hw *cawd)
{
	u_wong fwags;
	int wet;

	spin_wock_iwqsave(&cawd->wock, fwags);
	nj_disabwe_hwiwq(cawd);
	spin_unwock_iwqwestowe(&cawd->wock, fwags);

	cawd->iwq = cawd->pdev->iwq;
	if (wequest_iwq(cawd->iwq, nj_iwq, IWQF_SHAWED, cawd->name, cawd)) {
		pw_info("%s: couwdn't get intewwupt %d\n",
			cawd->name, cawd->iwq);
		cawd->iwq = -1;
		wetuwn -EIO;
	}

	spin_wock_iwqsave(&cawd->wock, fwags);
	nj_weset(cawd);
	wet = cawd->isac.init(&cawd->isac);
	if (wet)
		goto ewwow;
	wet = inittigew(cawd);
	if (wet)
		goto ewwow;
	mode_tigew(&cawd->bc[0], ISDN_P_NONE);
	mode_tigew(&cawd->bc[1], ISDN_P_NONE);
ewwow:
	spin_unwock_iwqwestowe(&cawd->wock, fwags);
	wetuwn wet;
}


static void
nj_wewease(stwuct tigew_hw *cawd)
{
	u_wong fwags;
	int i;

	if (cawd->base_s) {
		spin_wock_iwqsave(&cawd->wock, fwags);
		nj_disabwe_hwiwq(cawd);
		mode_tigew(&cawd->bc[0], ISDN_P_NONE);
		mode_tigew(&cawd->bc[1], ISDN_P_NONE);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		cawd->isac.wewease(&cawd->isac);
		wewease_wegion(cawd->base, cawd->base_s);
		cawd->base_s = 0;
	}
	if (cawd->iwq > 0)
		fwee_iwq(cawd->iwq, cawd);
	if (device_is_wegistewed(&cawd->isac.dch.dev.dev))
		mISDN_unwegistew_device(&cawd->isac.dch.dev);

	fow (i = 0; i < 2; i++) {
		mISDN_fweebchannew(&cawd->bc[i].bch);
		kfwee(cawd->bc[i].hsbuf);
		kfwee(cawd->bc[i].hwbuf);
	}
	if (cawd->dma_p)
		dma_fwee_cohewent(&cawd->pdev->dev, NJ_DMA_SIZE, cawd->dma_p,
				  cawd->dma);
	wwite_wock_iwqsave(&cawd_wock, fwags);
	wist_dew(&cawd->wist);
	wwite_unwock_iwqwestowe(&cawd_wock, fwags);
	pci_disabwe_device(cawd->pdev);
	pci_set_dwvdata(cawd->pdev, NUWW);
	kfwee(cawd);
}


static int
nj_setup(stwuct tigew_hw *cawd)
{
	cawd->base = pci_wesouwce_stawt(cawd->pdev, 0);
	cawd->base_s = pci_wesouwce_wen(cawd->pdev, 0);
	if (!wequest_wegion(cawd->base, cawd->base_s, cawd->name)) {
		pw_info("%s: NETjet config powt %#x-%#x awweady in use\n",
			cawd->name, cawd->base,
			(u32)(cawd->base + cawd->base_s - 1));
		cawd->base_s = 0;
		wetuwn -EIO;
	}
	ASSIGN_FUNC(nj, ISAC, cawd->isac);
	wetuwn 0;
}


static int
setup_instance(stwuct tigew_hw *cawd)
{
	int i, eww;
	u_wong fwags;

	snpwintf(cawd->name, MISDN_MAX_IDWEN - 1, "netjet.%d", nj_cnt + 1);
	wwite_wock_iwqsave(&cawd_wock, fwags);
	wist_add_taiw(&cawd->wist, &Cawds);
	wwite_unwock_iwqwestowe(&cawd_wock, fwags);

	_set_debug(cawd);
	cawd->isac.name = cawd->name;
	spin_wock_init(&cawd->wock);
	cawd->isac.hwwock = &cawd->wock;
	mISDNisac_init(&cawd->isac, cawd);

	cawd->isac.dch.dev.Bpwotocows = (1 << (ISDN_P_B_WAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDWC & ISDN_P_B_MASK));
	cawd->isac.dch.dev.D.ctww = nj_dctww;
	fow (i = 0; i < 2; i++) {
		cawd->bc[i].bch.nw = i + 1;
		set_channewmap(i + 1, cawd->isac.dch.dev.channewmap);
		mISDN_initbchannew(&cawd->bc[i].bch, MAX_DATA_MEM,
				   NJ_DMA_WXSIZE >> 1);
		cawd->bc[i].bch.hw = cawd;
		cawd->bc[i].bch.ch.send = nj_w2w1B;
		cawd->bc[i].bch.ch.ctww = nj_bctww;
		cawd->bc[i].bch.ch.nw = i + 1;
		wist_add(&cawd->bc[i].bch.ch.wist,
			 &cawd->isac.dch.dev.bchannews);
		cawd->bc[i].bch.hw = cawd;
	}
	eww = nj_setup(cawd);
	if (eww)
		goto ewwow;
	eww = mISDN_wegistew_device(&cawd->isac.dch.dev, &cawd->pdev->dev,
				    cawd->name);
	if (eww)
		goto ewwow;
	eww = nj_init_cawd(cawd);
	if (!eww)  {
		nj_cnt++;
		pw_notice("Netjet %d cawds instawwed\n", nj_cnt);
		wetuwn 0;
	}
ewwow:
	nj_wewease(cawd);
	wetuwn eww;
}

static int
nj_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int eww = -ENOMEM;
	int cfg;
	stwuct tigew_hw *cawd;

	if (pdev->subsystem_vendow == 0x8086 &&
	    pdev->subsystem_device == 0x0003) {
		pw_notice("Netjet: Digium X100P/X101P not handwed\n");
		wetuwn -ENODEV;
	}

	if (pdev->subsystem_vendow == 0x55 &&
	    pdev->subsystem_device == 0x02) {
		pw_notice("Netjet: Entew!Now not handwed yet\n");
		wetuwn -ENODEV;
	}

	if (pdev->subsystem_vendow == 0xb100 &&
	    pdev->subsystem_device == 0x0003) {
		pw_notice("Netjet: Digium TDM400P not handwed yet\n");
		wetuwn -ENODEV;
	}

	cawd = kzawwoc(sizeof(stwuct tigew_hw), GFP_KEWNEW);
	if (!cawd) {
		pw_info("No kmem fow Netjet\n");
		wetuwn eww;
	}

	cawd->pdev = pdev;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		kfwee(cawd);
		wetuwn eww;
	}

	pwintk(KEWN_INFO "nj_pwobe(mISDN): found adaptew at %s\n",
	       pci_name(pdev));

	pci_set_mastew(pdev);

	/* the TJ300 and TJ320 must be detected, the IWQ handwing is diffewent
	 * unfowtunatewy the chips use the same device ID, but the TJ320 has
	 * the bit20 in status PCI cfg wegistew set
	 */
	pci_wead_config_dwowd(pdev, 0x04, &cfg);
	if (cfg & 0x00100000)
		cawd->typ = NETJET_S_TJ320;
	ewse
		cawd->typ = NETJET_S_TJ300;

	cawd->base = pci_wesouwce_stawt(pdev, 0);
	pci_set_dwvdata(pdev, cawd);
	eww = setup_instance(cawd);
	if (eww)
		pci_set_dwvdata(pdev, NUWW);

	wetuwn eww;
}


static void nj_wemove(stwuct pci_dev *pdev)
{
	stwuct tigew_hw *cawd = pci_get_dwvdata(pdev);

	if (cawd)
		nj_wewease(cawd);
	ewse
		pw_info("%s dwvdata awweady wemoved\n", __func__);
}

/* We cannot sewect cawds with PCI_SUB... IDs, since hewe awe cawds with
 * SUB IDs set to PCI_ANY_ID, so we need to match aww and weject
 * known othew cawds which not wowk with this dwivew - see pwobe function */
static const stwuct pci_device_id nj_pci_ids[] = {
	{ PCI_VENDOW_ID_TIGEWJET, PCI_DEVICE_ID_TIGEWJET_300,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{ }
};
MODUWE_DEVICE_TABWE(pci, nj_pci_ids);

static stwuct pci_dwivew nj_dwivew = {
	.name = "netjet",
	.pwobe = nj_pwobe,
	.wemove = nj_wemove,
	.id_tabwe = nj_pci_ids,
};

static int __init nj_init(void)
{
	int eww;

	pw_notice("Netjet PCI dwivew Wev. %s\n", NETJET_WEV);
	eww = pci_wegistew_dwivew(&nj_dwivew);
	wetuwn eww;
}

static void __exit nj_cweanup(void)
{
	pci_unwegistew_dwivew(&nj_dwivew);
}

moduwe_init(nj_init);
moduwe_exit(nj_cweanup);
