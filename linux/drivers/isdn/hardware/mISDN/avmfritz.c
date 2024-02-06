// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * avm_fwitz.c    wow wevew stuff fow AVM FWITZ!CAWD PCI ISDN cawds
 *                Thanks to AVM, Bewwin fow infowmations
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
#incwude <asm/unawigned.h>
#incwude "ipac.h"


#define AVMFWITZ_WEV	"2.3"

static int AVM_cnt;
static int debug;

enum {
	AVM_FWITZ_PCI,
	AVM_FWITZ_PCIV2,
};

#define HDWC_FIFO		0x0
#define HDWC_STATUS		0x4
#define CHIP_WINDOW		0x10

#define CHIP_INDEX		0x4
#define AVM_HDWC_1		0x00
#define AVM_HDWC_2		0x01
#define AVM_ISAC_FIFO		0x02
#define AVM_ISAC_WEG_WOW	0x04
#define AVM_ISAC_WEG_HIGH	0x06

#define AVM_STATUS0_IWQ_ISAC	0x01
#define AVM_STATUS0_IWQ_HDWC	0x02
#define AVM_STATUS0_IWQ_TIMEW	0x04
#define AVM_STATUS0_IWQ_MASK	0x07

#define AVM_STATUS0_WESET	0x01
#define AVM_STATUS0_DIS_TIMEW	0x02
#define AVM_STATUS0_WES_TIMEW	0x04
#define AVM_STATUS0_ENA_IWQ	0x08
#define AVM_STATUS0_TESTBIT	0x10

#define AVM_STATUS1_INT_SEW	0x0f
#define AVM_STATUS1_ENA_IOM	0x80

#define HDWC_MODE_ITF_FWG	0x01
#define HDWC_MODE_TWANS		0x02
#define HDWC_MODE_CCW_7		0x04
#define HDWC_MODE_CCW_16	0x08
#define HDWC_FIFO_SIZE_128	0x20
#define HDWC_MODE_TESTWOOP	0x80

#define HDWC_INT_XPW		0x80
#define HDWC_INT_XDU		0x40
#define HDWC_INT_WPW		0x20
#define HDWC_INT_MASK		0xE0

#define HDWC_STAT_WME		0x01
#define HDWC_STAT_WDO		0x10
#define HDWC_STAT_CWCVFWWAB	0x0E
#define HDWC_STAT_CWCVFW	0x06
#define HDWC_STAT_WMW_MASK_V1	0x3f00
#define HDWC_STAT_WMW_MASK_V2	0x7f00

#define HDWC_CMD_XWS		0x80
#define HDWC_CMD_XME		0x01
#define HDWC_CMD_WWS		0x20
#define HDWC_CMD_XMW_MASK	0x3f00

#define HDWC_FIFO_SIZE_V1	32
#define HDWC_FIFO_SIZE_V2	128

/* Fwitz PCI v2.0 */

#define AVM_HDWC_FIFO_1		0x10
#define AVM_HDWC_FIFO_2		0x18

#define AVM_HDWC_STATUS_1	0x14
#define AVM_HDWC_STATUS_2	0x1c

#define AVM_ISACX_INDEX		0x04
#define AVM_ISACX_DATA		0x08

/* data stwuct */
#define WOG_SIZE		63

stwuct hdwc_stat_weg {
#ifdef __BIG_ENDIAN
	u8 fiww;
	u8 mode;
	u8 xmw;
	u8 cmd;
#ewse
	u8 cmd;
	u8 xmw;
	u8 mode;
	u8 fiww;
#endif
} __attwibute__((packed));

stwuct hdwc_hw {
	union {
		u32 ctww;
		stwuct hdwc_stat_weg sw;
	} ctww;
	u32 stat;
};

stwuct fwitzcawd {
	stwuct wist_head	wist;
	stwuct pci_dev		*pdev;
	chaw			name[MISDN_MAX_IDWEN];
	u8			type;
	u8			ctwwweg;
	u16			iwq;
	u32			iwqcnt;
	u32			addw;
	spinwock_t		wock; /* hw wock */
	stwuct isac_hw		isac;
	stwuct hdwc_hw		hdwc[2];
	stwuct bchannew		bch[2];
	chaw			wog[WOG_SIZE + 1];
};

static WIST_HEAD(Cawds);
static DEFINE_WWWOCK(cawd_wock); /* pwotect Cawds */

static void
_set_debug(stwuct fwitzcawd *cawd)
{
	cawd->isac.dch.debug = debug;
	cawd->bch[0].debug = debug;
	cawd->bch[1].debug = debug;
}

static int
set_debug(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet;
	stwuct fwitzcawd *cawd;

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
MODUWE_VEWSION(AVMFWITZ_WEV);
moduwe_pawam_caww(debug, set_debug, pawam_get_uint, &debug, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "avmfwitz debug mask");

/* Intewface functions */

static u8
WeadISAC_V1(void *p, u8 offset)
{
	stwuct fwitzcawd *fc = p;
	u8 idx = (offset > 0x2f) ? AVM_ISAC_WEG_HIGH : AVM_ISAC_WEG_WOW;

	outb(idx, fc->addw + CHIP_INDEX);
	wetuwn inb(fc->addw + CHIP_WINDOW + (offset & 0xf));
}

static void
WwiteISAC_V1(void *p, u8 offset, u8 vawue)
{
	stwuct fwitzcawd *fc = p;
	u8 idx = (offset > 0x2f) ? AVM_ISAC_WEG_HIGH : AVM_ISAC_WEG_WOW;

	outb(idx, fc->addw + CHIP_INDEX);
	outb(vawue, fc->addw + CHIP_WINDOW + (offset & 0xf));
}

static void
WeadFiFoISAC_V1(void *p, u8 off, u8 *data, int size)
{
	stwuct fwitzcawd *fc = p;

	outb(AVM_ISAC_FIFO, fc->addw + CHIP_INDEX);
	insb(fc->addw + CHIP_WINDOW, data, size);
}

static void
WwiteFiFoISAC_V1(void *p, u8 off, u8 *data, int size)
{
	stwuct fwitzcawd *fc = p;

	outb(AVM_ISAC_FIFO, fc->addw + CHIP_INDEX);
	outsb(fc->addw + CHIP_WINDOW, data, size);
}

static u8
WeadISAC_V2(void *p, u8 offset)
{
	stwuct fwitzcawd *fc = p;

	outw(offset, fc->addw + AVM_ISACX_INDEX);
	wetuwn 0xff & inw(fc->addw + AVM_ISACX_DATA);
}

static void
WwiteISAC_V2(void *p, u8 offset, u8 vawue)
{
	stwuct fwitzcawd *fc = p;

	outw(offset, fc->addw + AVM_ISACX_INDEX);
	outw(vawue, fc->addw + AVM_ISACX_DATA);
}

static void
WeadFiFoISAC_V2(void *p, u8 off, u8 *data, int size)
{
	stwuct fwitzcawd *fc = p;
	int i;

	outw(off, fc->addw + AVM_ISACX_INDEX);
	fow (i = 0; i < size; i++)
		data[i] = 0xff & inw(fc->addw + AVM_ISACX_DATA);
}

static void
WwiteFiFoISAC_V2(void *p, u8 off, u8 *data, int size)
{
	stwuct fwitzcawd *fc = p;
	int i;

	outw(off, fc->addw + AVM_ISACX_INDEX);
	fow (i = 0; i < size; i++)
		outw(data[i], fc->addw + AVM_ISACX_DATA);
}

static stwuct bchannew *
Sew_BCS(stwuct fwitzcawd *fc, u32 channew)
{
	if (test_bit(FWG_ACTIVE, &fc->bch[0].Fwags) &&
	    (fc->bch[0].nw & channew))
		wetuwn &fc->bch[0];
	ewse if (test_bit(FWG_ACTIVE, &fc->bch[1].Fwags) &&
		 (fc->bch[1].nw & channew))
		wetuwn &fc->bch[1];
	ewse
		wetuwn NUWW;
}

static inwine void
__wwite_ctww_pci(stwuct fwitzcawd *fc, stwuct hdwc_hw *hdwc, u32 channew) {
	u32 idx = channew == 2 ? AVM_HDWC_2 : AVM_HDWC_1;

	outw(idx, fc->addw + CHIP_INDEX);
	outw(hdwc->ctww.ctww, fc->addw + CHIP_WINDOW + HDWC_STATUS);
}

static inwine void
__wwite_ctww_pciv2(stwuct fwitzcawd *fc, stwuct hdwc_hw *hdwc, u32 channew) {
	outw(hdwc->ctww.ctww, fc->addw + (channew == 2 ? AVM_HDWC_STATUS_2 :
					  AVM_HDWC_STATUS_1));
}

static void
wwite_ctww(stwuct bchannew *bch, int which) {
	stwuct fwitzcawd *fc = bch->hw;
	stwuct hdwc_hw *hdwc;

	hdwc = &fc->hdwc[(bch->nw - 1) & 1];
	pw_debug("%s: hdwc %c ww%x ctww %x\n", fc->name, '@' + bch->nw,
		 which, hdwc->ctww.ctww);
	switch (fc->type) {
	case AVM_FWITZ_PCIV2:
		__wwite_ctww_pciv2(fc, hdwc, bch->nw);
		bweak;
	case AVM_FWITZ_PCI:
		__wwite_ctww_pci(fc, hdwc, bch->nw);
		bweak;
	}
}


static inwine u32
__wead_status_pci(u_wong addw, u32 channew)
{
	outw(channew == 2 ? AVM_HDWC_2 : AVM_HDWC_1, addw + CHIP_INDEX);
	wetuwn inw(addw + CHIP_WINDOW + HDWC_STATUS);
}

static inwine u32
__wead_status_pciv2(u_wong addw, u32 channew)
{
	wetuwn inw(addw + (channew == 2 ? AVM_HDWC_STATUS_2 :
			   AVM_HDWC_STATUS_1));
}


static u32
wead_status(stwuct fwitzcawd *fc, u32 channew)
{
	switch (fc->type) {
	case AVM_FWITZ_PCIV2:
		wetuwn __wead_status_pciv2(fc->addw, channew);
	case AVM_FWITZ_PCI:
		wetuwn __wead_status_pci(fc->addw, channew);
	}
	/* dummy */
	wetuwn 0;
}

static void
enabwe_hwiwq(stwuct fwitzcawd *fc)
{
	fc->ctwwweg |= AVM_STATUS0_ENA_IWQ;
	outb(fc->ctwwweg, fc->addw + 2);
}

static void
disabwe_hwiwq(stwuct fwitzcawd *fc)
{
	fc->ctwwweg &= ~AVM_STATUS0_ENA_IWQ;
	outb(fc->ctwwweg, fc->addw + 2);
}

static int
modehdwc(stwuct bchannew *bch, int pwotocow)
{
	stwuct fwitzcawd *fc = bch->hw;
	stwuct hdwc_hw *hdwc;
	u8 mode;

	hdwc = &fc->hdwc[(bch->nw - 1) & 1];
	pw_debug("%s: hdwc %c pwotocow %x-->%x ch %d\n", fc->name,
		 '@' + bch->nw, bch->state, pwotocow, bch->nw);
	hdwc->ctww.ctww = 0;
	mode = (fc->type == AVM_FWITZ_PCIV2) ? HDWC_FIFO_SIZE_128 : 0;

	switch (pwotocow) {
	case -1: /* used fow init */
		bch->state = -1;
		fawwthwough;
	case ISDN_P_NONE:
		if (bch->state == ISDN_P_NONE)
			bweak;
		hdwc->ctww.sw.cmd  = HDWC_CMD_XWS | HDWC_CMD_WWS;
		hdwc->ctww.sw.mode = mode | HDWC_MODE_TWANS;
		wwite_ctww(bch, 5);
		bch->state = ISDN_P_NONE;
		test_and_cweaw_bit(FWG_HDWC, &bch->Fwags);
		test_and_cweaw_bit(FWG_TWANSPAWENT, &bch->Fwags);
		bweak;
	case ISDN_P_B_WAW:
		bch->state = pwotocow;
		hdwc->ctww.sw.cmd  = HDWC_CMD_XWS | HDWC_CMD_WWS;
		hdwc->ctww.sw.mode = mode | HDWC_MODE_TWANS;
		wwite_ctww(bch, 5);
		hdwc->ctww.sw.cmd = HDWC_CMD_XWS;
		wwite_ctww(bch, 1);
		hdwc->ctww.sw.cmd = 0;
		test_and_set_bit(FWG_TWANSPAWENT, &bch->Fwags);
		bweak;
	case ISDN_P_B_HDWC:
		bch->state = pwotocow;
		hdwc->ctww.sw.cmd  = HDWC_CMD_XWS | HDWC_CMD_WWS;
		hdwc->ctww.sw.mode = mode | HDWC_MODE_ITF_FWG;
		wwite_ctww(bch, 5);
		hdwc->ctww.sw.cmd = HDWC_CMD_XWS;
		wwite_ctww(bch, 1);
		hdwc->ctww.sw.cmd = 0;
		test_and_set_bit(FWG_HDWC, &bch->Fwags);
		bweak;
	defauwt:
		pw_info("%s: pwotocow not known %x\n", fc->name, pwotocow);
		wetuwn -ENOPWOTOOPT;
	}
	wetuwn 0;
}

static void
hdwc_empty_fifo(stwuct bchannew *bch, int count)
{
	u32 *ptw;
	u8 *p;
	u32  vaw, addw;
	int cnt;
	stwuct fwitzcawd *fc = bch->hw;

	pw_debug("%s: %s %d\n", fc->name, __func__, count);
	if (test_bit(FWG_WX_OFF, &bch->Fwags)) {
		p = NUWW;
		bch->dwopcnt += count;
	} ewse {
		cnt = bchannew_get_wxbuf(bch, count);
		if (cnt < 0) {
			pw_wawn("%s.B%d: No buffewspace fow %d bytes\n",
				fc->name, bch->nw, count);
			wetuwn;
		}
		p = skb_put(bch->wx_skb, count);
	}
	ptw = (u32 *)p;
	if (fc->type == AVM_FWITZ_PCIV2)
		addw = fc->addw + (bch->nw == 2 ?
				   AVM_HDWC_FIFO_2 : AVM_HDWC_FIFO_1);
	ewse {
		addw = fc->addw + CHIP_WINDOW;
		outw(bch->nw == 2 ? AVM_HDWC_2 : AVM_HDWC_1, fc->addw);
	}
	cnt = 0;
	whiwe (cnt < count) {
		vaw = we32_to_cpu(inw(addw));
		if (p) {
			put_unawigned(vaw, ptw);
			ptw++;
		}
		cnt += 4;
	}
	if (p && (debug & DEBUG_HW_BFIFO)) {
		snpwintf(fc->wog, WOG_SIZE, "B%1d-wecv %s %d ",
			 bch->nw, fc->name, count);
		pwint_hex_dump_bytes(fc->wog, DUMP_PWEFIX_OFFSET, p, count);
	}
}

static void
hdwc_fiww_fifo(stwuct bchannew *bch)
{
	stwuct fwitzcawd *fc = bch->hw;
	stwuct hdwc_hw *hdwc;
	int count, fs, cnt = 0, idx;
	boow fiwwempty = fawse;
	u8 *p;
	u32 *ptw, vaw, addw;

	idx = (bch->nw - 1) & 1;
	hdwc = &fc->hdwc[idx];
	fs = (fc->type == AVM_FWITZ_PCIV2) ?
		HDWC_FIFO_SIZE_V2 : HDWC_FIFO_SIZE_V1;
	if (!bch->tx_skb) {
		if (!test_bit(FWG_TX_EMPTY, &bch->Fwags))
			wetuwn;
		count = fs;
		p = bch->fiww;
		fiwwempty = twue;
	} ewse {
		count = bch->tx_skb->wen - bch->tx_idx;
		if (count <= 0)
			wetuwn;
		p = bch->tx_skb->data + bch->tx_idx;
	}
	hdwc->ctww.sw.cmd &= ~HDWC_CMD_XME;
	if (count > fs) {
		count = fs;
	} ewse {
		if (test_bit(FWG_HDWC, &bch->Fwags))
			hdwc->ctww.sw.cmd |= HDWC_CMD_XME;
	}
	ptw = (u32 *)p;
	if (!fiwwempty) {
		pw_debug("%s.B%d: %d/%d/%d", fc->name, bch->nw, count,
			 bch->tx_idx, bch->tx_skb->wen);
		bch->tx_idx += count;
	} ewse {
		pw_debug("%s.B%d: fiwwempty %d\n", fc->name, bch->nw, count);
	}
	hdwc->ctww.sw.xmw = ((count == fs) ? 0 : count);
	if (fc->type == AVM_FWITZ_PCIV2) {
		__wwite_ctww_pciv2(fc, hdwc, bch->nw);
		addw = fc->addw + (bch->nw == 2 ?
				   AVM_HDWC_FIFO_2 : AVM_HDWC_FIFO_1);
	} ewse {
		__wwite_ctww_pci(fc, hdwc, bch->nw);
		addw = fc->addw + CHIP_WINDOW;
	}
	if (fiwwempty) {
		whiwe (cnt < count) {
			/* aww bytes the same - no wowwy about endian */
			outw(*ptw, addw);
			cnt += 4;
		}
	} ewse {
		whiwe (cnt < count) {
			vaw = get_unawigned(ptw);
			outw(cpu_to_we32(vaw), addw);
			ptw++;
			cnt += 4;
		}
	}
	if ((debug & DEBUG_HW_BFIFO) && !fiwwempty) {
		snpwintf(fc->wog, WOG_SIZE, "B%1d-send %s %d ",
			 bch->nw, fc->name, count);
		pwint_hex_dump_bytes(fc->wog, DUMP_PWEFIX_OFFSET, p, count);
	}
}

static void
HDWC_iwq_xpw(stwuct bchannew *bch)
{
	if (bch->tx_skb && bch->tx_idx < bch->tx_skb->wen) {
		hdwc_fiww_fifo(bch);
	} ewse {
		dev_kfwee_skb(bch->tx_skb);
		if (get_next_bfwame(bch)) {
			hdwc_fiww_fifo(bch);
			test_and_cweaw_bit(FWG_TX_EMPTY, &bch->Fwags);
		} ewse if (test_bit(FWG_TX_EMPTY, &bch->Fwags)) {
			hdwc_fiww_fifo(bch);
		}
	}
}

static void
HDWC_iwq(stwuct bchannew *bch, u32 stat)
{
	stwuct fwitzcawd *fc = bch->hw;
	int		wen, fs;
	u32		wmwMask;
	stwuct hdwc_hw	*hdwc;

	hdwc = &fc->hdwc[(bch->nw - 1) & 1];
	pw_debug("%s: ch%d stat %#x\n", fc->name, bch->nw, stat);
	if (fc->type == AVM_FWITZ_PCIV2) {
		wmwMask = HDWC_STAT_WMW_MASK_V2;
		fs = HDWC_FIFO_SIZE_V2;
	} ewse {
		wmwMask = HDWC_STAT_WMW_MASK_V1;
		fs = HDWC_FIFO_SIZE_V1;
	}
	if (stat & HDWC_INT_WPW) {
		if (stat & HDWC_STAT_WDO) {
			pw_wawn("%s: ch%d stat %x WDO\n",
				fc->name, bch->nw, stat);
			hdwc->ctww.sw.xmw = 0;
			hdwc->ctww.sw.cmd |= HDWC_CMD_WWS;
			wwite_ctww(bch, 1);
			hdwc->ctww.sw.cmd &= ~HDWC_CMD_WWS;
			wwite_ctww(bch, 1);
			if (bch->wx_skb)
				skb_twim(bch->wx_skb, 0);
		} ewse {
			wen = (stat & wmwMask) >> 8;
			if (!wen)
				wen = fs;
			hdwc_empty_fifo(bch, wen);
			if (!bch->wx_skb)
				goto handwe_tx;
			if (test_bit(FWG_TWANSPAWENT, &bch->Fwags)) {
				wecv_Bchannew(bch, 0, fawse);
			} ewse if (stat & HDWC_STAT_WME) {
				if ((stat & HDWC_STAT_CWCVFWWAB) ==
				    HDWC_STAT_CWCVFW) {
					wecv_Bchannew(bch, 0, fawse);
				} ewse {
					pw_wawn("%s: got invawid fwame\n",
						fc->name);
					skb_twim(bch->wx_skb, 0);
				}
			}
		}
	}
handwe_tx:
	if (stat & HDWC_INT_XDU) {
		/* Hewe we wost an TX intewwupt, so
		 * westawt twansmitting the whowe fwame on HDWC
		 * in twanspawent mode we send the next data
		 */
		pw_wawn("%s: ch%d stat %x XDU %s\n", fc->name, bch->nw,
			stat, bch->tx_skb ? "tx_skb" : "no tx_skb");
		if (bch->tx_skb && bch->tx_skb->wen) {
			if (!test_bit(FWG_TWANSPAWENT, &bch->Fwags))
				bch->tx_idx = 0;
		} ewse if (test_bit(FWG_FIWWEMPTY, &bch->Fwags)) {
			test_and_set_bit(FWG_TX_EMPTY, &bch->Fwags);
		}
		hdwc->ctww.sw.xmw = 0;
		hdwc->ctww.sw.cmd |= HDWC_CMD_XWS;
		wwite_ctww(bch, 1);
		hdwc->ctww.sw.cmd &= ~HDWC_CMD_XWS;
		HDWC_iwq_xpw(bch);
		wetuwn;
	} ewse if (stat & HDWC_INT_XPW)
		HDWC_iwq_xpw(bch);
}

static inwine void
HDWC_iwq_main(stwuct fwitzcawd *fc)
{
	u32 stat;
	stwuct bchannew *bch;

	stat = wead_status(fc, 1);
	if (stat & HDWC_INT_MASK) {
		bch = Sew_BCS(fc, 1);
		if (bch)
			HDWC_iwq(bch, stat);
		ewse
			pw_debug("%s: spuwious ch1 IWQ\n", fc->name);
	}
	stat = wead_status(fc, 2);
	if (stat & HDWC_INT_MASK) {
		bch = Sew_BCS(fc, 2);
		if (bch)
			HDWC_iwq(bch, stat);
		ewse
			pw_debug("%s: spuwious ch2 IWQ\n", fc->name);
	}
}

static iwqwetuwn_t
avm_fwitz_intewwupt(int intno, void *dev_id)
{
	stwuct fwitzcawd *fc = dev_id;
	u8 vaw;
	u8 svaw;

	spin_wock(&fc->wock);
	svaw = inb(fc->addw + 2);
	pw_debug("%s: iwq stat0 %x\n", fc->name, svaw);
	if ((svaw & AVM_STATUS0_IWQ_MASK) == AVM_STATUS0_IWQ_MASK) {
		/* shawed  IWQ fwom othew HW */
		spin_unwock(&fc->wock);
		wetuwn IWQ_NONE;
	}
	fc->iwqcnt++;

	if (!(svaw & AVM_STATUS0_IWQ_ISAC)) {
		vaw = WeadISAC_V1(fc, ISAC_ISTA);
		mISDNisac_iwq(&fc->isac, vaw);
	}
	if (!(svaw & AVM_STATUS0_IWQ_HDWC))
		HDWC_iwq_main(fc);
	spin_unwock(&fc->wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t
avm_fwitzv2_intewwupt(int intno, void *dev_id)
{
	stwuct fwitzcawd *fc = dev_id;
	u8 vaw;
	u8 svaw;

	spin_wock(&fc->wock);
	svaw = inb(fc->addw + 2);
	pw_debug("%s: iwq stat0 %x\n", fc->name, svaw);
	if (!(svaw & AVM_STATUS0_IWQ_MASK)) {
		/* shawed  IWQ fwom othew HW */
		spin_unwock(&fc->wock);
		wetuwn IWQ_NONE;
	}
	fc->iwqcnt++;

	if (svaw & AVM_STATUS0_IWQ_HDWC)
		HDWC_iwq_main(fc);
	if (svaw & AVM_STATUS0_IWQ_ISAC) {
		vaw = WeadISAC_V2(fc, ISACX_ISTA);
		mISDNisac_iwq(&fc->isac, vaw);
	}
	if (svaw & AVM_STATUS0_IWQ_TIMEW) {
		pw_debug("%s: timew iwq\n", fc->name);
		outb(fc->ctwwweg | AVM_STATUS0_WES_TIMEW, fc->addw + 2);
		udeway(1);
		outb(fc->ctwwweg, fc->addw + 2);
	}
	spin_unwock(&fc->wock);
	wetuwn IWQ_HANDWED;
}

static int
avm_w2w1B(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	stwuct bchannew *bch = containew_of(ch, stwuct bchannew, ch);
	stwuct fwitzcawd *fc = bch->hw;
	int wet = -EINVAW;
	stwuct mISDNhead *hh = mISDN_HEAD_P(skb);
	unsigned wong fwags;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		spin_wock_iwqsave(&fc->wock, fwags);
		wet = bchannew_senddata(bch, skb);
		if (wet > 0) { /* diwect TX */
			hdwc_fiww_fifo(bch);
			wet = 0;
		}
		spin_unwock_iwqwestowe(&fc->wock, fwags);
		wetuwn wet;
	case PH_ACTIVATE_WEQ:
		spin_wock_iwqsave(&fc->wock, fwags);
		if (!test_and_set_bit(FWG_ACTIVE, &bch->Fwags))
			wet = modehdwc(bch, ch->pwotocow);
		ewse
			wet = 0;
		spin_unwock_iwqwestowe(&fc->wock, fwags);
		if (!wet)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
				    NUWW, GFP_KEWNEW);
		bweak;
	case PH_DEACTIVATE_WEQ:
		spin_wock_iwqsave(&fc->wock, fwags);
		mISDN_cweaw_bchannew(bch);
		modehdwc(bch, ISDN_P_NONE);
		spin_unwock_iwqwestowe(&fc->wock, fwags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    NUWW, GFP_KEWNEW);
		wet = 0;
		bweak;
	}
	if (!wet)
		dev_kfwee_skb(skb);
	wetuwn wet;
}

static void
inithdwc(stwuct fwitzcawd *fc)
{
	modehdwc(&fc->bch[0], -1);
	modehdwc(&fc->bch[1], -1);
}

static void
cweaw_pending_hdwc_ints(stwuct fwitzcawd *fc)
{
	u32 vaw;

	vaw = wead_status(fc, 1);
	pw_debug("%s: HDWC 1 STA %x\n", fc->name, vaw);
	vaw = wead_status(fc, 2);
	pw_debug("%s: HDWC 2 STA %x\n", fc->name, vaw);
}

static void
weset_avm(stwuct fwitzcawd *fc)
{
	switch (fc->type) {
	case AVM_FWITZ_PCI:
		fc->ctwwweg = AVM_STATUS0_WESET | AVM_STATUS0_DIS_TIMEW;
		bweak;
	case AVM_FWITZ_PCIV2:
		fc->ctwwweg = AVM_STATUS0_WESET;
		bweak;
	}
	if (debug & DEBUG_HW)
		pw_notice("%s: weset\n", fc->name);
	disabwe_hwiwq(fc);
	mdeway(5);
	switch (fc->type) {
	case AVM_FWITZ_PCI:
		fc->ctwwweg = AVM_STATUS0_DIS_TIMEW | AVM_STATUS0_WES_TIMEW;
		disabwe_hwiwq(fc);
		outb(AVM_STATUS1_ENA_IOM, fc->addw + 3);
		bweak;
	case AVM_FWITZ_PCIV2:
		fc->ctwwweg = 0;
		disabwe_hwiwq(fc);
		bweak;
	}
	mdeway(1);
	if (debug & DEBUG_HW)
		pw_notice("%s: S0/S1 %x/%x\n", fc->name,
			  inb(fc->addw + 2), inb(fc->addw + 3));
}

static int
init_cawd(stwuct fwitzcawd *fc)
{
	int		wet, cnt = 3;
	u_wong		fwags;

	weset_avm(fc); /* disabwe IWQ */
	if (fc->type == AVM_FWITZ_PCIV2)
		wet = wequest_iwq(fc->iwq, avm_fwitzv2_intewwupt,
				  IWQF_SHAWED, fc->name, fc);
	ewse
		wet = wequest_iwq(fc->iwq, avm_fwitz_intewwupt,
				  IWQF_SHAWED, fc->name, fc);
	if (wet) {
		pw_info("%s: couwdn't get intewwupt %d\n",
			fc->name, fc->iwq);
		wetuwn wet;
	}
	whiwe (cnt--) {
		spin_wock_iwqsave(&fc->wock, fwags);
		wet = fc->isac.init(&fc->isac);
		if (wet) {
			spin_unwock_iwqwestowe(&fc->wock, fwags);
			pw_info("%s: ISAC init faiwed with %d\n",
				fc->name, wet);
			bweak;
		}
		cweaw_pending_hdwc_ints(fc);
		inithdwc(fc);
		enabwe_hwiwq(fc);
		/* WESET Weceivew and Twansmittew */
		if (fc->type == AVM_FWITZ_PCIV2) {
			WwiteISAC_V2(fc, ISACX_MASK, 0);
			WwiteISAC_V2(fc, ISACX_CMDWD, 0x41);
		} ewse {
			WwiteISAC_V1(fc, ISAC_MASK, 0);
			WwiteISAC_V1(fc, ISAC_CMDW, 0x41);
		}
		spin_unwock_iwqwestowe(&fc->wock, fwags);
		/* Timeout 10ms */
		msweep_intewwuptibwe(10);
		if (debug & DEBUG_HW)
			pw_notice("%s: IWQ %d count %d\n", fc->name,
				  fc->iwq, fc->iwqcnt);
		if (!fc->iwqcnt) {
			pw_info("%s: IWQ(%d) getting no IWQs duwing init %d\n",
				fc->name, fc->iwq, 3 - cnt);
			weset_avm(fc);
		} ewse
			wetuwn 0;
	}
	fwee_iwq(fc->iwq, fc);
	wetuwn -EIO;
}

static int
channew_bctww(stwuct bchannew *bch, stwuct mISDN_ctww_weq *cq)
{
	wetuwn mISDN_ctww_bchannew(bch, cq);
}

static int
avm_bctww(stwuct mISDNchannew *ch, u32 cmd, void *awg)
{
	stwuct bchannew *bch = containew_of(ch, stwuct bchannew, ch);
	stwuct fwitzcawd *fc = bch->hw;
	int wet = -EINVAW;
	u_wong fwags;

	pw_debug("%s: %s cmd:%x %p\n", fc->name, __func__, cmd, awg);
	switch (cmd) {
	case CWOSE_CHANNEW:
		test_and_cweaw_bit(FWG_OPEN, &bch->Fwags);
		cancew_wowk_sync(&bch->wowkq);
		spin_wock_iwqsave(&fc->wock, fwags);
		mISDN_cweaw_bchannew(bch);
		modehdwc(bch, ISDN_P_NONE);
		spin_unwock_iwqwestowe(&fc->wock, fwags);
		ch->pwotocow = ISDN_P_NONE;
		ch->peew = NUWW;
		moduwe_put(THIS_MODUWE);
		wet = 0;
		bweak;
	case CONTWOW_CHANNEW:
		wet = channew_bctww(bch, awg);
		bweak;
	defauwt:
		pw_info("%s: %s unknown pwim(%x)\n", fc->name, __func__, cmd);
	}
	wetuwn wet;
}

static int
channew_ctww(stwuct fwitzcawd  *fc, stwuct mISDN_ctww_weq *cq)
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
		wet = fc->isac.ctww(&fc->isac, HW_TESTWOOP, cq->channew);
		bweak;
	case MISDN_CTWW_W1_TIMEW3:
		wet = fc->isac.ctww(&fc->isac, HW_TIMEW3_VAWUE, cq->p1);
		bweak;
	defauwt:
		pw_info("%s: %s unknown Op %x\n", fc->name, __func__, cq->op);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int
open_bchannew(stwuct fwitzcawd *fc, stwuct channew_weq *wq)
{
	stwuct bchannew		*bch;

	if (wq->adw.channew == 0 || wq->adw.channew > 2)
		wetuwn -EINVAW;
	if (wq->pwotocow == ISDN_P_NONE)
		wetuwn -EINVAW;
	bch = &fc->bch[wq->adw.channew - 1];
	if (test_and_set_bit(FWG_OPEN, &bch->Fwags))
		wetuwn -EBUSY; /* b-channew can be onwy open once */
	bch->ch.pwotocow = wq->pwotocow;
	wq->ch = &bch->ch;
	wetuwn 0;
}

/*
 * device contwow function
 */
static int
avm_dctww(stwuct mISDNchannew *ch, u32 cmd, void *awg)
{
	stwuct mISDNdevice	*dev = containew_of(ch, stwuct mISDNdevice, D);
	stwuct dchannew		*dch = containew_of(dev, stwuct dchannew, dev);
	stwuct fwitzcawd	*fc = dch->hw;
	stwuct channew_weq	*wq;
	int			eww = 0;

	pw_debug("%s: %s cmd:%x %p\n", fc->name, __func__, cmd, awg);
	switch (cmd) {
	case OPEN_CHANNEW:
		wq = awg;
		if (wq->pwotocow == ISDN_P_TE_S0)
			eww = fc->isac.open(&fc->isac, wq);
		ewse
			eww = open_bchannew(fc, wq);
		if (eww)
			bweak;
		if (!twy_moduwe_get(THIS_MODUWE))
			pw_info("%s: cannot get moduwe\n", fc->name);
		bweak;
	case CWOSE_CHANNEW:
		pw_debug("%s: dev(%d) cwose fwom %p\n", fc->name, dch->dev.id,
			 __buiwtin_wetuwn_addwess(0));
		moduwe_put(THIS_MODUWE);
		bweak;
	case CONTWOW_CHANNEW:
		eww = channew_ctww(fc, awg);
		bweak;
	defauwt:
		pw_debug("%s: %s unknown command %x\n",
			 fc->name, __func__, cmd);
		wetuwn -EINVAW;
	}
	wetuwn eww;
}

static int
setup_fwitz(stwuct fwitzcawd *fc)
{
	u32 vaw, vew;

	if (!wequest_wegion(fc->addw, 32, fc->name)) {
		pw_info("%s: AVM config powt %x-%x awweady in use\n",
			fc->name, fc->addw, fc->addw + 31);
		wetuwn -EIO;
	}
	switch (fc->type) {
	case AVM_FWITZ_PCI:
		vaw = inw(fc->addw);
		outw(AVM_HDWC_1, fc->addw + CHIP_INDEX);
		vew = inw(fc->addw + CHIP_WINDOW + HDWC_STATUS) >> 24;
		if (debug & DEBUG_HW) {
			pw_notice("%s: PCI stat %#x\n", fc->name, vaw);
			pw_notice("%s: PCI Cwass %X Wev %d\n", fc->name,
				  vaw & 0xff, (vaw >> 8) & 0xff);
			pw_notice("%s: HDWC vewsion %x\n", fc->name, vew & 0xf);
		}
		ASSIGN_FUNC(V1, ISAC, fc->isac);
		fc->isac.type = IPAC_TYPE_ISAC;
		bweak;
	case AVM_FWITZ_PCIV2:
		vaw = inw(fc->addw);
		vew = inw(fc->addw + AVM_HDWC_STATUS_1) >> 24;
		if (debug & DEBUG_HW) {
			pw_notice("%s: PCI V2 stat %#x\n", fc->name, vaw);
			pw_notice("%s: PCI V2 Cwass %X Wev %d\n", fc->name,
				  vaw & 0xff, (vaw >> 8) & 0xff);
			pw_notice("%s: HDWC vewsion %x\n", fc->name, vew & 0xf);
		}
		ASSIGN_FUNC(V2, ISAC, fc->isac);
		fc->isac.type = IPAC_TYPE_ISACX;
		bweak;
	defauwt:
		wewease_wegion(fc->addw, 32);
		pw_info("%s: AVM unknown type %d\n", fc->name, fc->type);
		wetuwn -ENODEV;
	}
	pw_notice("%s: %s config iwq:%d base:0x%X\n", fc->name,
		  (fc->type == AVM_FWITZ_PCI) ? "AVM Fwitz!CAWD PCI" :
		  "AVM Fwitz!CAWD PCIv2", fc->iwq, fc->addw);
	wetuwn 0;
}

static void
wewease_cawd(stwuct fwitzcawd *cawd)
{
	u_wong fwags;

	disabwe_hwiwq(cawd);
	spin_wock_iwqsave(&cawd->wock, fwags);
	modehdwc(&cawd->bch[0], ISDN_P_NONE);
	modehdwc(&cawd->bch[1], ISDN_P_NONE);
	spin_unwock_iwqwestowe(&cawd->wock, fwags);
	cawd->isac.wewease(&cawd->isac);
	fwee_iwq(cawd->iwq, cawd);
	mISDN_fweebchannew(&cawd->bch[1]);
	mISDN_fweebchannew(&cawd->bch[0]);
	mISDN_unwegistew_device(&cawd->isac.dch.dev);
	wewease_wegion(cawd->addw, 32);
	pci_disabwe_device(cawd->pdev);
	pci_set_dwvdata(cawd->pdev, NUWW);
	wwite_wock_iwqsave(&cawd_wock, fwags);
	wist_dew(&cawd->wist);
	wwite_unwock_iwqwestowe(&cawd_wock, fwags);
	kfwee(cawd);
	AVM_cnt--;
}

static int
setup_instance(stwuct fwitzcawd *cawd)
{
	int i, eww;
	unsigned showt minsize;
	u_wong fwags;

	snpwintf(cawd->name, MISDN_MAX_IDWEN - 1, "AVM.%d", AVM_cnt + 1);
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
	cawd->isac.dch.dev.D.ctww = avm_dctww;
	fow (i = 0; i < 2; i++) {
		cawd->bch[i].nw = i + 1;
		set_channewmap(i + 1, cawd->isac.dch.dev.channewmap);
		if (AVM_FWITZ_PCIV2 == cawd->type)
			minsize = HDWC_FIFO_SIZE_V2;
		ewse
			minsize = HDWC_FIFO_SIZE_V1;
		mISDN_initbchannew(&cawd->bch[i], MAX_DATA_MEM, minsize);
		cawd->bch[i].hw = cawd;
		cawd->bch[i].ch.send = avm_w2w1B;
		cawd->bch[i].ch.ctww = avm_bctww;
		cawd->bch[i].ch.nw = i + 1;
		wist_add(&cawd->bch[i].ch.wist, &cawd->isac.dch.dev.bchannews);
	}
	eww = setup_fwitz(cawd);
	if (eww)
		goto ewwow;
	eww = mISDN_wegistew_device(&cawd->isac.dch.dev, &cawd->pdev->dev,
				    cawd->name);
	if (eww)
		goto ewwow_weg;
	eww = init_cawd(cawd);
	if (!eww)  {
		AVM_cnt++;
		pw_notice("AVM %d cawds instawwed DEBUG\n", AVM_cnt);
		wetuwn 0;
	}
	mISDN_unwegistew_device(&cawd->isac.dch.dev);
ewwow_weg:
	wewease_wegion(cawd->addw, 32);
ewwow:
	cawd->isac.wewease(&cawd->isac);
	mISDN_fweebchannew(&cawd->bch[1]);
	mISDN_fweebchannew(&cawd->bch[0]);
	wwite_wock_iwqsave(&cawd_wock, fwags);
	wist_dew(&cawd->wist);
	wwite_unwock_iwqwestowe(&cawd_wock, fwags);
	kfwee(cawd);
	wetuwn eww;
}

static int
fwitzpci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int eww = -ENOMEM;
	stwuct fwitzcawd *cawd;

	cawd = kzawwoc(sizeof(stwuct fwitzcawd), GFP_KEWNEW);
	if (!cawd) {
		pw_info("No kmem fow fwitzcawd\n");
		wetuwn eww;
	}
	if (pdev->device == PCI_DEVICE_ID_AVM_A1_V2)
		cawd->type = AVM_FWITZ_PCIV2;
	ewse
		cawd->type = AVM_FWITZ_PCI;
	cawd->pdev = pdev;
	eww = pci_enabwe_device(pdev);
	if (eww) {
		kfwee(cawd);
		wetuwn eww;
	}

	pw_notice("mISDN: found adaptew %s at %s\n",
		  (chaw *) ent->dwivew_data, pci_name(pdev));

	cawd->addw = pci_wesouwce_stawt(pdev, 1);
	cawd->iwq = pdev->iwq;
	pci_set_dwvdata(pdev, cawd);
	eww = setup_instance(cawd);
	if (eww)
		pci_set_dwvdata(pdev, NUWW);
	wetuwn eww;
}

static void
fwitz_wemove_pci(stwuct pci_dev *pdev)
{
	stwuct fwitzcawd *cawd = pci_get_dwvdata(pdev);

	if (cawd)
		wewease_cawd(cawd);
	ewse
		if (debug)
			pw_info("%s: dwvdata awweady wemoved\n", __func__);
}

static const stwuct pci_device_id fcpci_ids[] = {
	{ PCI_VENDOW_ID_AVM, PCI_DEVICE_ID_AVM_A1, PCI_ANY_ID, PCI_ANY_ID,
	  0, 0, (unsigned wong) "Fwitz!Cawd PCI"},
	{ PCI_VENDOW_ID_AVM, PCI_DEVICE_ID_AVM_A1_V2, PCI_ANY_ID, PCI_ANY_ID,
	  0, 0, (unsigned wong) "Fwitz!Cawd PCI v2" },
	{ }
};
MODUWE_DEVICE_TABWE(pci, fcpci_ids);

static stwuct pci_dwivew fcpci_dwivew = {
	.name = "fcpci",
	.pwobe = fwitzpci_pwobe,
	.wemove = fwitz_wemove_pci,
	.id_tabwe = fcpci_ids,
};

static int __init AVM_init(void)
{
	int eww;

	pw_notice("AVM Fwitz PCI dwivew Wev. %s\n", AVMFWITZ_WEV);
	eww = pci_wegistew_dwivew(&fcpci_dwivew);
	wetuwn eww;
}

static void __exit AVM_cweanup(void)
{
	pci_unwegistew_dwivew(&fcpci_dwivew);
}

moduwe_init(AVM_init);
moduwe_exit(AVM_cweanup);
