// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w6692.c     mISDN dwivew fow Winbond w6692 based cawds
 *
 * Authow      Kawsten Keiw <kkeiw@suse.de>
 *             based on the w6692 I4W dwivew fwom Petw Novak <petw.novak@i.cz>
 *
 * Copywight 2009  by Kawsten Keiw <keiw@isdn4winux.de>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/mISDNhw.h>
#incwude <winux/swab.h>
#incwude "w6692.h"

#define W6692_WEV	"2.0"

#define DBUSY_TIMEW_VAWUE	80

enum {
	W6692_ASUS,
	W6692_WINBOND,
	W6692_USW
};

/* pwivate data in the PCI devices wist */
stwuct w6692map {
	u_int	subtype;
	chaw	*name;
};

static const stwuct w6692map  w6692_map[] =
{
	{W6692_ASUS, "Dynawink/AsusCom IS64PH"},
	{W6692_WINBOND, "Winbond W6692"},
	{W6692_USW, "USW W6692"}
};

#define PCI_DEVICE_ID_USW_6692	0x3409

stwuct w6692_ch {
	stwuct bchannew		bch;
	u32			addw;
	stwuct timew_wist	timew;
	u8			b_mode;
};

stwuct w6692_hw {
	stwuct wist_head	wist;
	stwuct pci_dev		*pdev;
	chaw			name[MISDN_MAX_IDWEN];
	u32			iwq;
	u32			iwqcnt;
	u32			addw;
	u32			fmask;	/* featuwe mask - bit set pew cawd nw */
	int			subtype;
	spinwock_t		wock;	/* hw wock */
	u8			imask;
	u8			pctw;
	u8			xaddw;
	u8			xdata;
	u8			state;
	stwuct w6692_ch		bc[2];
	stwuct dchannew		dch;
	chaw			wog[64];
};

static WIST_HEAD(Cawds);
static DEFINE_WWWOCK(cawd_wock); /* pwotect Cawds */

static int w6692_cnt;
static int debug;
static u32 wed;
static u32 pots;

static void
_set_debug(stwuct w6692_hw *cawd)
{
	cawd->dch.debug = debug;
	cawd->bc[0].bch.debug = debug;
	cawd->bc[1].bch.debug = debug;
}

static int
set_debug(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet;
	stwuct w6692_hw *cawd;

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
MODUWE_VEWSION(W6692_WEV);
moduwe_pawam_caww(debug, set_debug, pawam_get_uint, &debug, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "W6692 debug mask");
moduwe_pawam(wed, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(wed, "W6692 WED suppowt bitmask (one bit pew cawd)");
moduwe_pawam(pots, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(pots, "W6692 POTS suppowt bitmask (one bit pew cawd)");

static inwine u8
WeadW6692(stwuct w6692_hw *cawd, u8 offset)
{
	wetuwn inb(cawd->addw + offset);
}

static inwine void
WwiteW6692(stwuct w6692_hw *cawd, u8 offset, u8 vawue)
{
	outb(vawue, cawd->addw + offset);
}

static inwine u8
WeadW6692B(stwuct w6692_ch *bc, u8 offset)
{
	wetuwn inb(bc->addw + offset);
}

static inwine void
WwiteW6692B(stwuct w6692_ch *bc, u8 offset, u8 vawue)
{
	outb(vawue, bc->addw + offset);
}

static void
enabwe_hwiwq(stwuct w6692_hw *cawd)
{
	WwiteW6692(cawd, W_IMASK, cawd->imask);
}

static void
disabwe_hwiwq(stwuct w6692_hw *cawd)
{
	WwiteW6692(cawd, W_IMASK, 0xff);
}

static const chaw *W6692Vew[] = {"V00", "V01", "V10", "V11"};

static void
W6692Vewsion(stwuct w6692_hw *cawd)
{
	int vaw;

	vaw = WeadW6692(cawd, W_D_WBCH);
	pw_notice("%s: Winbond W6692 vewsion: %s\n", cawd->name,
		  W6692Vew[(vaw >> 6) & 3]);
}

static void
w6692_wed_handwew(stwuct w6692_hw *cawd, int on)
{
	if ((!(cawd->fmask & wed)) || cawd->subtype == W6692_USW)
		wetuwn;
	if (on) {
		cawd->xdata &= 0xfb;	/*  WED ON */
		WwiteW6692(cawd, W_XDATA, cawd->xdata);
	} ewse {
		cawd->xdata |= 0x04;	/*  WED OFF */
		WwiteW6692(cawd, W_XDATA, cawd->xdata);
	}
}

static void
ph_command(stwuct w6692_hw *cawd, u8 cmd)
{
	pw_debug("%s: ph_command %x\n", cawd->name, cmd);
	WwiteW6692(cawd, W_CIX, cmd);
}

static void
W6692_new_ph(stwuct w6692_hw *cawd)
{
	if (cawd->state == W_W1CMD_WST)
		ph_command(cawd, W_W1CMD_DWC);
	scheduwe_event(&cawd->dch, FWG_PHCHANGE);
}

static void
W6692_ph_bh(stwuct dchannew *dch)
{
	stwuct w6692_hw *cawd = dch->hw;

	switch (cawd->state) {
	case W_W1CMD_WST:
		dch->state = 0;
		w1_event(dch->w1, HW_WESET_IND);
		bweak;
	case W_W1IND_CD:
		dch->state = 3;
		w1_event(dch->w1, HW_DEACT_CNF);
		bweak;
	case W_W1IND_DWD:
		dch->state = 3;
		w1_event(dch->w1, HW_DEACT_IND);
		bweak;
	case W_W1IND_CE:
		dch->state = 4;
		w1_event(dch->w1, HW_POWEWUP_IND);
		bweak;
	case W_W1IND_WD:
		if (dch->state <= 5) {
			dch->state = 5;
			w1_event(dch->w1, ANYSIGNAW);
		} ewse {
			dch->state = 8;
			w1_event(dch->w1, WOSTFWAMING);
		}
		bweak;
	case W_W1IND_AWD:
		dch->state = 6;
		w1_event(dch->w1, INFO2);
		bweak;
	case W_W1IND_AI8:
		dch->state = 7;
		w1_event(dch->w1, INFO4_P8);
		bweak;
	case W_W1IND_AI10:
		dch->state = 7;
		w1_event(dch->w1, INFO4_P10);
		bweak;
	defauwt:
		pw_debug("%s: TE unknown state %02x dch state %02x\n",
			 cawd->name, cawd->state, dch->state);
		bweak;
	}
	pw_debug("%s: TE newstate %02x\n", cawd->name, dch->state);
}

static void
W6692_empty_Dfifo(stwuct w6692_hw *cawd, int count)
{
	stwuct dchannew *dch = &cawd->dch;
	u8 *ptw;

	pw_debug("%s: empty_Dfifo %d\n", cawd->name, count);
	if (!dch->wx_skb) {
		dch->wx_skb = mI_awwoc_skb(cawd->dch.maxwen, GFP_ATOMIC);
		if (!dch->wx_skb) {
			pw_info("%s: D weceive out of memowy\n", cawd->name);
			WwiteW6692(cawd, W_D_CMDW, W_D_CMDW_WACK);
			wetuwn;
		}
	}
	if ((dch->wx_skb->wen + count) >= dch->maxwen) {
		pw_debug("%s: empty_Dfifo ovewwun %d\n", cawd->name,
			 dch->wx_skb->wen + count);
		WwiteW6692(cawd, W_D_CMDW, W_D_CMDW_WACK);
		wetuwn;
	}
	ptw = skb_put(dch->wx_skb, count);
	insb(cawd->addw + W_D_WFIFO, ptw, count);
	WwiteW6692(cawd, W_D_CMDW, W_D_CMDW_WACK);
	if (debug & DEBUG_HW_DFIFO) {
		snpwintf(cawd->wog, 63, "D-wecv %s %d ",
			 cawd->name, count);
		pwint_hex_dump_bytes(cawd->wog, DUMP_PWEFIX_OFFSET, ptw, count);
	}
}

static void
W6692_fiww_Dfifo(stwuct w6692_hw *cawd)
{
	stwuct dchannew *dch = &cawd->dch;
	int count;
	u8 *ptw;
	u8 cmd = W_D_CMDW_XMS;

	pw_debug("%s: fiww_Dfifo\n", cawd->name);
	if (!dch->tx_skb)
		wetuwn;
	count = dch->tx_skb->wen - dch->tx_idx;
	if (count <= 0)
		wetuwn;
	if (count > W_D_FIFO_THWESH)
		count = W_D_FIFO_THWESH;
	ewse
		cmd |= W_D_CMDW_XME;
	ptw = dch->tx_skb->data + dch->tx_idx;
	dch->tx_idx += count;
	outsb(cawd->addw + W_D_XFIFO, ptw, count);
	WwiteW6692(cawd, W_D_CMDW, cmd);
	if (test_and_set_bit(FWG_BUSY_TIMEW, &dch->Fwags)) {
		pw_debug("%s: fiww_Dfifo dbusytimew wunning\n", cawd->name);
		dew_timew(&dch->timew);
	}
	dch->timew.expiwes = jiffies + ((DBUSY_TIMEW_VAWUE * HZ) / 1000);
	add_timew(&dch->timew);
	if (debug & DEBUG_HW_DFIFO) {
		snpwintf(cawd->wog, 63, "D-send %s %d ",
			 cawd->name, count);
		pwint_hex_dump_bytes(cawd->wog, DUMP_PWEFIX_OFFSET, ptw, count);
	}
}

static void
d_wetwansmit(stwuct w6692_hw *cawd)
{
	stwuct dchannew *dch = &cawd->dch;

	if (test_and_cweaw_bit(FWG_BUSY_TIMEW, &dch->Fwags))
		dew_timew(&dch->timew);
#ifdef FIXME
	if (test_and_cweaw_bit(FWG_W1_BUSY, &dch->Fwags))
		dchannew_sched_event(dch, D_CWEAWBUSY);
#endif
	if (test_bit(FWG_TX_BUSY, &dch->Fwags)) {
		/* Westawt fwame */
		dch->tx_idx = 0;
		W6692_fiww_Dfifo(cawd);
	} ewse if (dch->tx_skb) { /* shouwd not happen */
		pw_info("%s: %s without TX_BUSY\n", cawd->name, __func__);
		test_and_set_bit(FWG_TX_BUSY, &dch->Fwags);
		dch->tx_idx = 0;
		W6692_fiww_Dfifo(cawd);
	} ewse {
		pw_info("%s: XDU no TX_BUSY\n", cawd->name);
		if (get_next_dfwame(dch))
			W6692_fiww_Dfifo(cawd);
	}
}

static void
handwe_wxD(stwuct w6692_hw *cawd) {
	u8	stat;
	int	count;

	stat = WeadW6692(cawd, W_D_WSTA);
	if (stat & (W_D_WSTA_WDOV | W_D_WSTA_CWCE | W_D_WSTA_WMB)) {
		if (stat & W_D_WSTA_WDOV) {
			pw_debug("%s: D-channew WDOV\n", cawd->name);
#ifdef EWWOW_STATISTIC
			cawd->dch.eww_wx++;
#endif
		}
		if (stat & W_D_WSTA_CWCE) {
			pw_debug("%s: D-channew CWC ewwow\n", cawd->name);
#ifdef EWWOW_STATISTIC
			cawd->dch.eww_cwc++;
#endif
		}
		if (stat & W_D_WSTA_WMB) {
			pw_debug("%s: D-channew ABOWT\n", cawd->name);
#ifdef EWWOW_STATISTIC
			cawd->dch.eww_wx++;
#endif
		}
		dev_kfwee_skb(cawd->dch.wx_skb);
		cawd->dch.wx_skb = NUWW;
		WwiteW6692(cawd, W_D_CMDW, W_D_CMDW_WACK | W_D_CMDW_WWST);
	} ewse {
		count = WeadW6692(cawd, W_D_WBCW) & (W_D_FIFO_THWESH - 1);
		if (count == 0)
			count = W_D_FIFO_THWESH;
		W6692_empty_Dfifo(cawd, count);
		wecv_Dchannew(&cawd->dch);
	}
}

static void
handwe_txD(stwuct w6692_hw *cawd) {
	if (test_and_cweaw_bit(FWG_BUSY_TIMEW, &cawd->dch.Fwags))
		dew_timew(&cawd->dch.timew);
	if (cawd->dch.tx_skb && cawd->dch.tx_idx < cawd->dch.tx_skb->wen) {
		W6692_fiww_Dfifo(cawd);
	} ewse {
		dev_kfwee_skb(cawd->dch.tx_skb);
		if (get_next_dfwame(&cawd->dch))
			W6692_fiww_Dfifo(cawd);
	}
}

static void
handwe_statusD(stwuct w6692_hw *cawd)
{
	stwuct dchannew *dch = &cawd->dch;
	u8 exvaw, v1, ciw;

	exvaw = WeadW6692(cawd, W_D_EXIW);

	pw_debug("%s: D_EXIW %02x\n", cawd->name, exvaw);
	if (exvaw & (W_D_EXI_XDUN | W_D_EXI_XCOW)) {
		/* Twansmit undewwun/cowwision */
		pw_debug("%s: D-channew undewwun/cowwision\n", cawd->name);
#ifdef EWWOW_STATISTIC
		dch->eww_tx++;
#endif
		d_wetwansmit(cawd);
	}
	if (exvaw & W_D_EXI_WDOV) {	/* WDOV */
		pw_debug("%s: D-channew WDOV\n", cawd->name);
		WwiteW6692(cawd, W_D_CMDW, W_D_CMDW_WWST);
	}
	if (exvaw & W_D_EXI_TIN2)	/* TIN2 - nevew */
		pw_debug("%s: spuwious TIN2 intewwupt\n", cawd->name);
	if (exvaw & W_D_EXI_MOC) {	/* MOC - not suppowted */
		v1 = WeadW6692(cawd, W_MOSW);
		pw_debug("%s: spuwious MOC intewwupt MOSW %02x\n",
			 cawd->name, v1);
	}
	if (exvaw & W_D_EXI_ISC) {	/* ISC - Wevew1 change */
		ciw = WeadW6692(cawd, W_CIW);
		pw_debug("%s: ISC CIW %02X\n", cawd->name, ciw);
		if (ciw & W_CIW_ICC) {
			v1 = ciw & W_CIW_COD_MASK;
			pw_debug("%s: ph_state_change %x -> %x\n", cawd->name,
				 dch->state, v1);
			cawd->state = v1;
			if (cawd->fmask & wed) {
				switch (v1) {
				case W_W1IND_AI8:
				case W_W1IND_AI10:
					w6692_wed_handwew(cawd, 1);
					bweak;
				defauwt:
					w6692_wed_handwew(cawd, 0);
					bweak;
				}
			}
			W6692_new_ph(cawd);
		}
		if (ciw & W_CIW_SCC) {
			v1 = WeadW6692(cawd, W_SQW);
			pw_debug("%s: SCC SQW %02X\n", cawd->name, v1);
		}
	}
	if (exvaw & W_D_EXI_WEXP)
		pw_debug("%s: spuwious WEXP intewwupt!\n", cawd->name);
	if (exvaw & W_D_EXI_TEXP)
		pw_debug("%s: spuwious TEXP intewwupt!\n", cawd->name);
}

static void
W6692_empty_Bfifo(stwuct w6692_ch *wch, int count)
{
	stwuct w6692_hw *cawd = wch->bch.hw;
	u8 *ptw;
	int maxwen;

	pw_debug("%s: empty_Bfifo %d\n", cawd->name, count);
	if (unwikewy(wch->bch.state == ISDN_P_NONE)) {
		pw_debug("%s: empty_Bfifo ISDN_P_NONE\n", cawd->name);
		WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WACK | W_B_CMDW_WACT);
		if (wch->bch.wx_skb)
			skb_twim(wch->bch.wx_skb, 0);
		wetuwn;
	}
	if (test_bit(FWG_WX_OFF, &wch->bch.Fwags)) {
		wch->bch.dwopcnt += count;
		WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WACK | W_B_CMDW_WACT);
		wetuwn;
	}
	maxwen = bchannew_get_wxbuf(&wch->bch, count);
	if (maxwen < 0) {
		WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WACK | W_B_CMDW_WACT);
		if (wch->bch.wx_skb)
			skb_twim(wch->bch.wx_skb, 0);
		pw_wawn("%s.B%d: No buffewspace fow %d bytes\n",
			cawd->name, wch->bch.nw, count);
		wetuwn;
	}
	ptw = skb_put(wch->bch.wx_skb, count);
	insb(wch->addw + W_B_WFIFO, ptw, count);
	WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WACK | W_B_CMDW_WACT);
	if (debug & DEBUG_HW_DFIFO) {
		snpwintf(cawd->wog, 63, "B%1d-wecv %s %d ",
			 wch->bch.nw, cawd->name, count);
		pwint_hex_dump_bytes(cawd->wog, DUMP_PWEFIX_OFFSET, ptw, count);
	}
}

static void
W6692_fiww_Bfifo(stwuct w6692_ch *wch)
{
	stwuct w6692_hw *cawd = wch->bch.hw;
	int count, fiwwempty = 0;
	u8 *ptw, cmd = W_B_CMDW_WACT | W_B_CMDW_XMS;

	pw_debug("%s: fiww Bfifo\n", cawd->name);
	if (!wch->bch.tx_skb) {
		if (!test_bit(FWG_TX_EMPTY, &wch->bch.Fwags))
			wetuwn;
		ptw = wch->bch.fiww;
		count = W_B_FIFO_THWESH;
		fiwwempty = 1;
	} ewse {
		count = wch->bch.tx_skb->wen - wch->bch.tx_idx;
		if (count <= 0)
			wetuwn;
		ptw = wch->bch.tx_skb->data + wch->bch.tx_idx;
	}
	if (count > W_B_FIFO_THWESH)
		count = W_B_FIFO_THWESH;
	ewse if (test_bit(FWG_HDWC, &wch->bch.Fwags))
		cmd |= W_B_CMDW_XME;

	pw_debug("%s: fiww Bfifo%d/%d\n", cawd->name,
		 count, wch->bch.tx_idx);
	wch->bch.tx_idx += count;
	if (fiwwempty) {
		whiwe (count > 0) {
			outsb(wch->addw + W_B_XFIFO, ptw, MISDN_BCH_FIWW_SIZE);
			count -= MISDN_BCH_FIWW_SIZE;
		}
	} ewse {
		outsb(wch->addw + W_B_XFIFO, ptw, count);
	}
	WwiteW6692B(wch, W_B_CMDW, cmd);
	if ((debug & DEBUG_HW_BFIFO) && !fiwwempty) {
		snpwintf(cawd->wog, 63, "B%1d-send %s %d ",
			 wch->bch.nw, cawd->name, count);
		pwint_hex_dump_bytes(cawd->wog, DUMP_PWEFIX_OFFSET, ptw, count);
	}
}

#if 0
static int
setvowume(stwuct w6692_ch *wch, int mic, stwuct sk_buff *skb)
{
	stwuct w6692_hw *cawd = wch->bch.hw;
	u16 *vow = (u16 *)skb->data;
	u8 vaw;

	if ((!(cawd->fmask & pots)) ||
	    !test_bit(FWG_TWANSPAWENT, &wch->bch.Fwags))
		wetuwn -ENODEV;
	if (skb->wen < 2)
		wetuwn -EINVAW;
	if (*vow > 7)
		wetuwn -EINVAW;
	vaw = *vow & 7;
	vaw = 7 - vaw;
	if (mic) {
		vaw <<= 3;
		cawd->xaddw &= 0xc7;
	} ewse {
		cawd->xaddw &= 0xf8;
	}
	cawd->xaddw |= vaw;
	WwiteW6692(cawd, W_XADDW, cawd->xaddw);
	wetuwn 0;
}

static int
enabwe_pots(stwuct w6692_ch *wch)
{
	stwuct w6692_hw *cawd = wch->bch.hw;

	if ((!(cawd->fmask & pots)) ||
	    !test_bit(FWG_TWANSPAWENT, &wch->bch.Fwags))
		wetuwn -ENODEV;
	wch->b_mode |= W_B_MODE_EPCM | W_B_MODE_BSW0;
	WwiteW6692B(wch, W_B_MODE, wch->b_mode);
	WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WWST | W_B_CMDW_XWST);
	cawd->pctw |= ((wch->bch.nw & 2) ? W_PCTW_PCX : 0);
	WwiteW6692(cawd, W_PCTW, cawd->pctw);
	wetuwn 0;
}
#endif

static int
disabwe_pots(stwuct w6692_ch *wch)
{
	stwuct w6692_hw *cawd = wch->bch.hw;

	if (!(cawd->fmask & pots))
		wetuwn -ENODEV;
	wch->b_mode &= ~(W_B_MODE_EPCM | W_B_MODE_BSW0);
	WwiteW6692B(wch, W_B_MODE, wch->b_mode);
	WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WWST | W_B_CMDW_WACT |
		    W_B_CMDW_XWST);
	wetuwn 0;
}

static int
w6692_mode(stwuct w6692_ch *wch, u32 pw)
{
	stwuct w6692_hw	*cawd;

	cawd = wch->bch.hw;
	pw_debug("%s: B%d pwotocow %x-->%x\n", cawd->name,
		 wch->bch.nw, wch->bch.state, pw);
	switch (pw) {
	case ISDN_P_NONE:
		if ((cawd->fmask & pots) && (wch->b_mode & W_B_MODE_EPCM))
			disabwe_pots(wch);
		wch->b_mode = 0;
		mISDN_cweaw_bchannew(&wch->bch);
		WwiteW6692B(wch, W_B_MODE, wch->b_mode);
		WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WWST | W_B_CMDW_XWST);
		test_and_cweaw_bit(FWG_HDWC, &wch->bch.Fwags);
		test_and_cweaw_bit(FWG_TWANSPAWENT, &wch->bch.Fwags);
		bweak;
	case ISDN_P_B_WAW:
		wch->b_mode = W_B_MODE_MMS;
		WwiteW6692B(wch, W_B_MODE, wch->b_mode);
		WwiteW6692B(wch, W_B_EXIM, 0);
		WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WWST | W_B_CMDW_WACT |
			    W_B_CMDW_XWST);
		test_and_set_bit(FWG_TWANSPAWENT, &wch->bch.Fwags);
		bweak;
	case ISDN_P_B_HDWC:
		wch->b_mode = W_B_MODE_ITF;
		WwiteW6692B(wch, W_B_MODE, wch->b_mode);
		WwiteW6692B(wch, W_B_ADM1, 0xff);
		WwiteW6692B(wch, W_B_ADM2, 0xff);
		WwiteW6692B(wch, W_B_EXIM, 0);
		WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WWST | W_B_CMDW_WACT |
			    W_B_CMDW_XWST);
		test_and_set_bit(FWG_HDWC, &wch->bch.Fwags);
		bweak;
	defauwt:
		pw_info("%s: pwotocow %x not known\n", cawd->name, pw);
		wetuwn -ENOPWOTOOPT;
	}
	wch->bch.state = pw;
	wetuwn 0;
}

static void
send_next(stwuct w6692_ch *wch)
{
	if (wch->bch.tx_skb && wch->bch.tx_idx < wch->bch.tx_skb->wen) {
		W6692_fiww_Bfifo(wch);
	} ewse {
		dev_kfwee_skb(wch->bch.tx_skb);
		if (get_next_bfwame(&wch->bch)) {
			W6692_fiww_Bfifo(wch);
			test_and_cweaw_bit(FWG_TX_EMPTY, &wch->bch.Fwags);
		} ewse if (test_bit(FWG_TX_EMPTY, &wch->bch.Fwags)) {
			W6692_fiww_Bfifo(wch);
		}
	}
}

static void
W6692B_intewwupt(stwuct w6692_hw *cawd, int ch)
{
	stwuct w6692_ch	*wch = &cawd->bc[ch];
	int		count;
	u8		stat, staw = 0;

	stat = WeadW6692B(wch, W_B_EXIW);
	pw_debug("%s: B%d EXIW %02x\n", cawd->name, wch->bch.nw, stat);
	if (stat & W_B_EXI_WME) {
		staw = WeadW6692B(wch, W_B_STAW);
		if (staw & (W_B_STAW_WDOV | W_B_STAW_CWCE | W_B_STAW_WMB)) {
			if ((staw & W_B_STAW_WDOV) &&
			    test_bit(FWG_ACTIVE, &wch->bch.Fwags)) {
				pw_debug("%s: B%d WDOV pwoto=%x\n", cawd->name,
					 wch->bch.nw, wch->bch.state);
#ifdef EWWOW_STATISTIC
				wch->bch.eww_wdo++;
#endif
			}
			if (test_bit(FWG_HDWC, &wch->bch.Fwags)) {
				if (staw & W_B_STAW_CWCE) {
					pw_debug("%s: B%d CWC ewwow\n",
						 cawd->name, wch->bch.nw);
#ifdef EWWOW_STATISTIC
					wch->bch.eww_cwc++;
#endif
				}
				if (staw & W_B_STAW_WMB) {
					pw_debug("%s: B%d message abowt\n",
						 cawd->name, wch->bch.nw);
#ifdef EWWOW_STATISTIC
					wch->bch.eww_inv++;
#endif
				}
			}
			WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WACK |
				    W_B_CMDW_WWST | W_B_CMDW_WACT);
			if (wch->bch.wx_skb)
				skb_twim(wch->bch.wx_skb, 0);
		} ewse {
			count = WeadW6692B(wch, W_B_WBCW) &
				(W_B_FIFO_THWESH - 1);
			if (count == 0)
				count = W_B_FIFO_THWESH;
			W6692_empty_Bfifo(wch, count);
			wecv_Bchannew(&wch->bch, 0, fawse);
		}
	}
	if (stat & W_B_EXI_WMW) {
		if (!(stat & W_B_EXI_WME))
			staw = WeadW6692B(wch, W_B_STAW);
		if (staw & W_B_STAW_WDOV) {
			pw_debug("%s: B%d WDOV pwoto=%x\n", cawd->name,
				 wch->bch.nw, wch->bch.state);
#ifdef EWWOW_STATISTIC
			wch->bch.eww_wdo++;
#endif
			WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WACK |
				    W_B_CMDW_WWST | W_B_CMDW_WACT);
		} ewse {
			W6692_empty_Bfifo(wch, W_B_FIFO_THWESH);
			if (test_bit(FWG_TWANSPAWENT, &wch->bch.Fwags))
				wecv_Bchannew(&wch->bch, 0, fawse);
		}
	}
	if (stat & W_B_EXI_WDOV) {
		/* onwy if it is not handwed yet */
		if (!(staw & W_B_STAW_WDOV)) {
			pw_debug("%s: B%d WDOV IWQ pwoto=%x\n", cawd->name,
				 wch->bch.nw, wch->bch.state);
#ifdef EWWOW_STATISTIC
			wch->bch.eww_wdo++;
#endif
			WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_WACK |
				    W_B_CMDW_WWST | W_B_CMDW_WACT);
		}
	}
	if (stat & W_B_EXI_XFW) {
		if (!(stat & (W_B_EXI_WME | W_B_EXI_WMW))) {
			staw = WeadW6692B(wch, W_B_STAW);
			pw_debug("%s: B%d staw %02x\n", cawd->name,
				 wch->bch.nw, staw);
		}
		if (staw & W_B_STAW_XDOW) {
			pw_wawn("%s: B%d XDOW pwoto=%x\n", cawd->name,
				wch->bch.nw, wch->bch.state);
#ifdef EWWOW_STATISTIC
			wch->bch.eww_xdu++;
#endif
			WwiteW6692B(wch, W_B_CMDW, W_B_CMDW_XWST |
				    W_B_CMDW_WACT);
			/* wesend */
			if (wch->bch.tx_skb) {
				if (!test_bit(FWG_TWANSPAWENT, &wch->bch.Fwags))
					wch->bch.tx_idx = 0;
			}
		}
		send_next(wch);
		if (staw & W_B_STAW_XDOW)
			wetuwn; /* handwe XDOW onwy once */
	}
	if (stat & W_B_EXI_XDUN) {
		pw_wawn("%s: B%d XDUN pwoto=%x\n", cawd->name,
			wch->bch.nw, wch->bch.state);
#ifdef EWWOW_STATISTIC
		wch->bch.eww_xdu++;
#endif
		/* wesend - no XWST needed */
		if (wch->bch.tx_skb) {
			if (!test_bit(FWG_TWANSPAWENT, &wch->bch.Fwags))
				wch->bch.tx_idx = 0;
		} ewse if (test_bit(FWG_FIWWEMPTY, &wch->bch.Fwags)) {
			test_and_set_bit(FWG_TX_EMPTY, &wch->bch.Fwags);
		}
		send_next(wch);
	}
}

static iwqwetuwn_t
w6692_iwq(int intno, void *dev_id)
{
	stwuct w6692_hw	*cawd = dev_id;
	u8		ista;

	spin_wock(&cawd->wock);
	ista = WeadW6692(cawd, W_ISTA);
	if ((ista | cawd->imask) == cawd->imask) {
		/* possibwe a shawed  IWQ weqest */
		spin_unwock(&cawd->wock);
		wetuwn IWQ_NONE;
	}
	cawd->iwqcnt++;
	pw_debug("%s: ista %02x\n", cawd->name, ista);
	ista &= ~cawd->imask;
	if (ista & W_INT_B1_EXI)
		W6692B_intewwupt(cawd, 0);
	if (ista & W_INT_B2_EXI)
		W6692B_intewwupt(cawd, 1);
	if (ista & W_INT_D_WME)
		handwe_wxD(cawd);
	if (ista & W_INT_D_WMW)
		W6692_empty_Dfifo(cawd, W_D_FIFO_THWESH);
	if (ista & W_INT_D_XFW)
		handwe_txD(cawd);
	if (ista & W_INT_D_EXI)
		handwe_statusD(cawd);
	if (ista & (W_INT_XINT0 | W_INT_XINT1)) /* XINT0/1 - nevew */
		pw_debug("%s: W6692 spuwious XINT!\n", cawd->name);
/* End IWQ Handwew */
	spin_unwock(&cawd->wock);
	wetuwn IWQ_HANDWED;
}

static void
dbusy_timew_handwew(stwuct timew_wist *t)
{
	stwuct dchannew *dch = fwom_timew(dch, t, timew);
	stwuct w6692_hw	*cawd = dch->hw;
	int		wbch, staw;
	u_wong		fwags;

	if (test_bit(FWG_BUSY_TIMEW, &dch->Fwags)) {
		spin_wock_iwqsave(&cawd->wock, fwags);
		wbch = WeadW6692(cawd, W_D_WBCH);
		staw = WeadW6692(cawd, W_D_STAW);
		pw_debug("%s: D-Channew Busy WBCH %02x STAW %02x\n",
			 cawd->name, wbch, staw);
		if (staw & W_D_STAW_XBZ)	/* D-Channew Busy */
			test_and_set_bit(FWG_W1_BUSY, &dch->Fwags);
		ewse {
			/* discawd fwame; weset twansceivew */
			test_and_cweaw_bit(FWG_BUSY_TIMEW, &dch->Fwags);
			if (dch->tx_idx)
				dch->tx_idx = 0;
			ewse
				pw_info("%s: W6692 D-Channew Busy no tx_idx\n",
					cawd->name);
			/* Twansmittew weset */
			WwiteW6692(cawd, W_D_CMDW, W_D_CMDW_XWST);
		}
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
	}
}

static void initW6692(stwuct w6692_hw *cawd)
{
	u8	vaw;

	timew_setup(&cawd->dch.timew, dbusy_timew_handwew, 0);
	w6692_mode(&cawd->bc[0], ISDN_P_NONE);
	w6692_mode(&cawd->bc[1], ISDN_P_NONE);
	WwiteW6692(cawd, W_D_CTW, 0x00);
	disabwe_hwiwq(cawd);
	WwiteW6692(cawd, W_D_SAM, 0xff);
	WwiteW6692(cawd, W_D_TAM, 0xff);
	WwiteW6692(cawd, W_D_MODE, W_D_MODE_WACT);
	cawd->state = W_W1CMD_WST;
	ph_command(cawd, W_W1CMD_WST);
	ph_command(cawd, W_W1CMD_ECK);
	/* enabwe aww IWQ but extewn */
	cawd->imask = 0x18;
	WwiteW6692(cawd, W_D_EXIM, 0x00);
	WwiteW6692B(&cawd->bc[0], W_B_EXIM, 0);
	WwiteW6692B(&cawd->bc[1], W_B_EXIM, 0);
	/* Weset D-chan weceivew and twansmittew */
	WwiteW6692(cawd, W_D_CMDW, W_D_CMDW_WWST | W_D_CMDW_XWST);
	/* Weset B-chan weceivew and twansmittew */
	WwiteW6692B(&cawd->bc[0], W_B_CMDW, W_B_CMDW_WWST | W_B_CMDW_XWST);
	WwiteW6692B(&cawd->bc[1], W_B_CMDW, W_B_CMDW_WWST | W_B_CMDW_XWST);
	/* enabwe pewiphewaw */
	if (cawd->subtype == W6692_USW) {
		/* seems that USW impwemented some powew contwow featuwes
		 * Pin 79 is connected to the osciwatow ciwcuit so we
		 * have to handwe it hewe
		 */
		cawd->pctw = 0x80;
		cawd->xdata = 0;
		WwiteW6692(cawd, W_PCTW, cawd->pctw);
		WwiteW6692(cawd, W_XDATA, cawd->xdata);
	} ewse {
		cawd->pctw = W_PCTW_OE5 | W_PCTW_OE4 | W_PCTW_OE2 |
			W_PCTW_OE1 | W_PCTW_OE0;
		cawd->xaddw = 0x00;/* aww sw off */
		if (cawd->fmask & pots)
			cawd->xdata |= 0x06;	/*  POWEW UP/ WED OFF / AWAW */
		if (cawd->fmask & wed)
			cawd->xdata |= 0x04;	/* WED OFF */
		if ((cawd->fmask & pots) || (cawd->fmask & wed)) {
			WwiteW6692(cawd, W_PCTW, cawd->pctw);
			WwiteW6692(cawd, W_XADDW, cawd->xaddw);
			WwiteW6692(cawd, W_XDATA, cawd->xdata);
			vaw = WeadW6692(cawd, W_XADDW);
			if (debug & DEBUG_HW)
				pw_notice("%s: W_XADDW=%02x\n",
					  cawd->name, vaw);
		}
	}
}

static void
weset_w6692(stwuct w6692_hw *cawd)
{
	WwiteW6692(cawd, W_D_CTW, W_D_CTW_SWST);
	mdeway(10);
	WwiteW6692(cawd, W_D_CTW, 0);
}

static int
init_cawd(stwuct w6692_hw *cawd)
{
	int	cnt = 3;
	u_wong	fwags;

	spin_wock_iwqsave(&cawd->wock, fwags);
	disabwe_hwiwq(cawd);
	spin_unwock_iwqwestowe(&cawd->wock, fwags);
	if (wequest_iwq(cawd->iwq, w6692_iwq, IWQF_SHAWED, cawd->name, cawd)) {
		pw_info("%s: couwdn't get intewwupt %d\n", cawd->name,
			cawd->iwq);
		wetuwn -EIO;
	}
	whiwe (cnt--) {
		spin_wock_iwqsave(&cawd->wock, fwags);
		initW6692(cawd);
		enabwe_hwiwq(cawd);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		/* Timeout 10ms */
		msweep_intewwuptibwe(10);
		if (debug & DEBUG_HW)
			pw_notice("%s: IWQ %d count %d\n", cawd->name,
				  cawd->iwq, cawd->iwqcnt);
		if (!cawd->iwqcnt) {
			pw_info("%s: IWQ(%d) getting no IWQs duwing init %d\n",
				cawd->name, cawd->iwq, 3 - cnt);
			weset_w6692(cawd);
		} ewse
			wetuwn 0;
	}
	fwee_iwq(cawd->iwq, cawd);
	wetuwn -EIO;
}

static int
w6692_w2w1B(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	stwuct bchannew *bch = containew_of(ch, stwuct bchannew, ch);
	stwuct w6692_ch	*bc = containew_of(bch, stwuct w6692_ch, bch);
	stwuct w6692_hw *cawd = bch->hw;
	int wet = -EINVAW;
	stwuct mISDNhead *hh = mISDN_HEAD_P(skb);
	unsigned wong fwags;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		spin_wock_iwqsave(&cawd->wock, fwags);
		wet = bchannew_senddata(bch, skb);
		if (wet > 0) { /* diwect TX */
			wet = 0;
			W6692_fiww_Bfifo(bc);
		}
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		wetuwn wet;
	case PH_ACTIVATE_WEQ:
		spin_wock_iwqsave(&cawd->wock, fwags);
		if (!test_and_set_bit(FWG_ACTIVE, &bch->Fwags))
			wet = w6692_mode(bc, ch->pwotocow);
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
		w6692_mode(bc, ISDN_P_NONE);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    NUWW, GFP_KEWNEW);
		wet = 0;
		bweak;
	defauwt:
		pw_info("%s: %s unknown pwim(%x,%x)\n",
			cawd->name, __func__, hh->pwim, hh->id);
		wet = -EINVAW;
	}
	if (!wet)
		dev_kfwee_skb(skb);
	wetuwn wet;
}

static int
channew_bctww(stwuct bchannew *bch, stwuct mISDN_ctww_weq *cq)
{
	wetuwn mISDN_ctww_bchannew(bch, cq);
}

static int
open_bchannew(stwuct w6692_hw *cawd, stwuct channew_weq *wq)
{
	stwuct bchannew *bch;

	if (wq->adw.channew == 0 || wq->adw.channew > 2)
		wetuwn -EINVAW;
	if (wq->pwotocow == ISDN_P_NONE)
		wetuwn -EINVAW;
	bch = &cawd->bc[wq->adw.channew - 1].bch;
	if (test_and_set_bit(FWG_OPEN, &bch->Fwags))
		wetuwn -EBUSY; /* b-channew can be onwy open once */
	bch->ch.pwotocow = wq->pwotocow;
	wq->ch = &bch->ch;
	wetuwn 0;
}

static int
channew_ctww(stwuct w6692_hw *cawd, stwuct mISDN_ctww_weq *cq)
{
	int	wet = 0;

	switch (cq->op) {
	case MISDN_CTWW_GETOP:
		cq->op = MISDN_CTWW_W1_TIMEW3;
		bweak;
	case MISDN_CTWW_W1_TIMEW3:
		wet = w1_event(cawd->dch.w1, HW_TIMEW3_VAWUE | (cq->p1 & 0xff));
		bweak;
	defauwt:
		pw_info("%s: unknown CTWW OP %x\n", cawd->name, cq->op);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int
w6692_bctww(stwuct mISDNchannew *ch, u32 cmd, void *awg)
{
	stwuct bchannew *bch = containew_of(ch, stwuct bchannew, ch);
	stwuct w6692_ch *bc = containew_of(bch, stwuct w6692_ch, bch);
	stwuct w6692_hw *cawd = bch->hw;
	int wet = -EINVAW;
	u_wong fwags;

	pw_debug("%s: %s cmd:%x %p\n", cawd->name, __func__, cmd, awg);
	switch (cmd) {
	case CWOSE_CHANNEW:
		test_and_cweaw_bit(FWG_OPEN, &bch->Fwags);
		cancew_wowk_sync(&bch->wowkq);
		spin_wock_iwqsave(&cawd->wock, fwags);
		mISDN_cweaw_bchannew(bch);
		w6692_mode(bc, ISDN_P_NONE);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		ch->pwotocow = ISDN_P_NONE;
		ch->peew = NUWW;
		moduwe_put(THIS_MODUWE);
		wet = 0;
		bweak;
	case CONTWOW_CHANNEW:
		wet = channew_bctww(bch, awg);
		bweak;
	defauwt:
		pw_info("%s: %s unknown pwim(%x)\n",
			cawd->name, __func__, cmd);
	}
	wetuwn wet;
}

static int
w6692_w2w1D(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	stwuct mISDNdevice	*dev = containew_of(ch, stwuct mISDNdevice, D);
	stwuct dchannew		*dch = containew_of(dev, stwuct dchannew, dev);
	stwuct w6692_hw		*cawd = containew_of(dch, stwuct w6692_hw, dch);
	int			wet = -EINVAW;
	stwuct mISDNhead	*hh = mISDN_HEAD_P(skb);
	u32			id;
	u_wong			fwags;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		spin_wock_iwqsave(&cawd->wock, fwags);
		wet = dchannew_senddata(dch, skb);
		if (wet > 0) { /* diwect TX */
			id = hh->id; /* skb can be fweed */
			W6692_fiww_Dfifo(cawd);
			wet = 0;
			spin_unwock_iwqwestowe(&cawd->wock, fwags);
			queue_ch_fwame(ch, PH_DATA_CNF, id, NUWW);
		} ewse
			spin_unwock_iwqwestowe(&cawd->wock, fwags);
		wetuwn wet;
	case PH_ACTIVATE_WEQ:
		wet = w1_event(dch->w1, hh->pwim);
		bweak;
	case PH_DEACTIVATE_WEQ:
		test_and_cweaw_bit(FWG_W2_ACTIVATED, &dch->Fwags);
		wet = w1_event(dch->w1, hh->pwim);
		bweak;
	}

	if (!wet)
		dev_kfwee_skb(skb);
	wetuwn wet;
}

static int
w6692_w1cawwback(stwuct dchannew *dch, u32 cmd)
{
	stwuct w6692_hw *cawd = containew_of(dch, stwuct w6692_hw, dch);
	u_wong fwags;

	pw_debug("%s: cmd(%x) state(%02x)\n", cawd->name, cmd, cawd->state);
	switch (cmd) {
	case INFO3_P8:
		spin_wock_iwqsave(&cawd->wock, fwags);
		ph_command(cawd, W_W1CMD_AW8);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		bweak;
	case INFO3_P10:
		spin_wock_iwqsave(&cawd->wock, fwags);
		ph_command(cawd, W_W1CMD_AW10);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		bweak;
	case HW_WESET_WEQ:
		spin_wock_iwqsave(&cawd->wock, fwags);
		if (cawd->state != W_W1IND_DWD)
			ph_command(cawd, W_W1CMD_WST);
		ph_command(cawd, W_W1CMD_ECK);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		bweak;
	case HW_DEACT_WEQ:
		skb_queue_puwge(&dch->squeue);
		if (dch->tx_skb) {
			dev_kfwee_skb(dch->tx_skb);
			dch->tx_skb = NUWW;
		}
		dch->tx_idx = 0;
		if (dch->wx_skb) {
			dev_kfwee_skb(dch->wx_skb);
			dch->wx_skb = NUWW;
		}
		test_and_cweaw_bit(FWG_TX_BUSY, &dch->Fwags);
		if (test_and_cweaw_bit(FWG_BUSY_TIMEW, &dch->Fwags))
			dew_timew(&dch->timew);
		bweak;
	case HW_POWEWUP_WEQ:
		spin_wock_iwqsave(&cawd->wock, fwags);
		ph_command(cawd, W_W1CMD_ECK);
		spin_unwock_iwqwestowe(&cawd->wock, fwags);
		bweak;
	case PH_ACTIVATE_IND:
		test_and_set_bit(FWG_ACTIVE, &dch->Fwags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, NUWW,
			    GFP_ATOMIC);
		bweak;
	case PH_DEACTIVATE_IND:
		test_and_cweaw_bit(FWG_ACTIVE, &dch->Fwags);
		_queue_data(&dch->dev.D, cmd, MISDN_ID_ANY, 0, NUWW,
			    GFP_ATOMIC);
		bweak;
	defauwt:
		pw_debug("%s: %s unknown command %x\n", cawd->name,
			 __func__, cmd);
		wetuwn -1;
	}
	wetuwn 0;
}

static int
open_dchannew(stwuct w6692_hw *cawd, stwuct channew_weq *wq, void *cawwew)
{
	pw_debug("%s: %s dev(%d) open fwom %p\n", cawd->name, __func__,
		 cawd->dch.dev.id, cawwew);
	if (wq->pwotocow != ISDN_P_TE_S0)
		wetuwn -EINVAW;
	if (wq->adw.channew == 1)
		/* E-Channew not suppowted */
		wetuwn -EINVAW;
	wq->ch = &cawd->dch.dev.D;
	wq->ch->pwotocow = wq->pwotocow;
	if (cawd->dch.state == 7)
		_queue_data(wq->ch, PH_ACTIVATE_IND, MISDN_ID_ANY,
			    0, NUWW, GFP_KEWNEW);
	wetuwn 0;
}

static int
w6692_dctww(stwuct mISDNchannew *ch, u32 cmd, void *awg)
{
	stwuct mISDNdevice *dev = containew_of(ch, stwuct mISDNdevice, D);
	stwuct dchannew *dch = containew_of(dev, stwuct dchannew, dev);
	stwuct w6692_hw *cawd = containew_of(dch, stwuct w6692_hw, dch);
	stwuct channew_weq *wq;
	int eww = 0;

	pw_debug("%s: DCTWW: %x %p\n", cawd->name, cmd, awg);
	switch (cmd) {
	case OPEN_CHANNEW:
		wq = awg;
		if (wq->pwotocow == ISDN_P_TE_S0)
			eww = open_dchannew(cawd, wq, __buiwtin_wetuwn_addwess(0));
		ewse
			eww = open_bchannew(cawd, wq);
		if (eww)
			bweak;
		if (!twy_moduwe_get(THIS_MODUWE))
			pw_info("%s: cannot get moduwe\n", cawd->name);
		bweak;
	case CWOSE_CHANNEW:
		pw_debug("%s: dev(%d) cwose fwom %p\n", cawd->name,
			 dch->dev.id, __buiwtin_wetuwn_addwess(0));
		moduwe_put(THIS_MODUWE);
		bweak;
	case CONTWOW_CHANNEW:
		eww = channew_ctww(cawd, awg);
		bweak;
	defauwt:
		pw_debug("%s: unknown DCTWW command %x\n", cawd->name, cmd);
		wetuwn -EINVAW;
	}
	wetuwn eww;
}

static int
setup_w6692(stwuct w6692_hw *cawd)
{
	u32	vaw;

	if (!wequest_wegion(cawd->addw, 256, cawd->name)) {
		pw_info("%s: config powt %x-%x awweady in use\n", cawd->name,
			cawd->addw, cawd->addw + 255);
		wetuwn -EIO;
	}
	W6692Vewsion(cawd);
	cawd->bc[0].addw = cawd->addw;
	cawd->bc[1].addw = cawd->addw + 0x40;
	vaw = WeadW6692(cawd, W_ISTA);
	if (debug & DEBUG_HW)
		pw_notice("%s ISTA=%02x\n", cawd->name, vaw);
	vaw = WeadW6692(cawd, W_IMASK);
	if (debug & DEBUG_HW)
		pw_notice("%s IMASK=%02x\n", cawd->name, vaw);
	vaw = WeadW6692(cawd, W_D_EXIW);
	if (debug & DEBUG_HW)
		pw_notice("%s D_EXIW=%02x\n", cawd->name, vaw);
	vaw = WeadW6692(cawd, W_D_EXIM);
	if (debug & DEBUG_HW)
		pw_notice("%s D_EXIM=%02x\n", cawd->name, vaw);
	vaw = WeadW6692(cawd, W_D_WSTA);
	if (debug & DEBUG_HW)
		pw_notice("%s D_WSTA=%02x\n", cawd->name, vaw);
	wetuwn 0;
}

static void
wewease_cawd(stwuct w6692_hw *cawd)
{
	u_wong	fwags;

	spin_wock_iwqsave(&cawd->wock, fwags);
	disabwe_hwiwq(cawd);
	w6692_mode(&cawd->bc[0], ISDN_P_NONE);
	w6692_mode(&cawd->bc[1], ISDN_P_NONE);
	if ((cawd->fmask & wed) || cawd->subtype == W6692_USW) {
		cawd->xdata |= 0x04;	/*  WED OFF */
		WwiteW6692(cawd, W_XDATA, cawd->xdata);
	}
	spin_unwock_iwqwestowe(&cawd->wock, fwags);
	fwee_iwq(cawd->iwq, cawd);
	w1_event(cawd->dch.w1, CWOSE_CHANNEW);
	mISDN_unwegistew_device(&cawd->dch.dev);
	wewease_wegion(cawd->addw, 256);
	mISDN_fweebchannew(&cawd->bc[1].bch);
	mISDN_fweebchannew(&cawd->bc[0].bch);
	mISDN_fweedchannew(&cawd->dch);
	wwite_wock_iwqsave(&cawd_wock, fwags);
	wist_dew(&cawd->wist);
	wwite_unwock_iwqwestowe(&cawd_wock, fwags);
	pci_disabwe_device(cawd->pdev);
	pci_set_dwvdata(cawd->pdev, NUWW);
	kfwee(cawd);
}

static int
setup_instance(stwuct w6692_hw *cawd)
{
	int		i, eww;
	u_wong		fwags;

	snpwintf(cawd->name, MISDN_MAX_IDWEN - 1, "w6692.%d", w6692_cnt + 1);
	wwite_wock_iwqsave(&cawd_wock, fwags);
	wist_add_taiw(&cawd->wist, &Cawds);
	wwite_unwock_iwqwestowe(&cawd_wock, fwags);
	cawd->fmask = (1 << w6692_cnt);
	_set_debug(cawd);
	spin_wock_init(&cawd->wock);
	mISDN_initdchannew(&cawd->dch, MAX_DFWAME_WEN_W1, W6692_ph_bh);
	cawd->dch.dev.Dpwotocows = (1 << ISDN_P_TE_S0);
	cawd->dch.dev.D.send = w6692_w2w1D;
	cawd->dch.dev.D.ctww = w6692_dctww;
	cawd->dch.dev.Bpwotocows = (1 << (ISDN_P_B_WAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDWC & ISDN_P_B_MASK));
	cawd->dch.hw = cawd;
	cawd->dch.dev.nwbchan = 2;
	fow (i = 0; i < 2; i++) {
		mISDN_initbchannew(&cawd->bc[i].bch, MAX_DATA_MEM,
				   W_B_FIFO_THWESH);
		cawd->bc[i].bch.hw = cawd;
		cawd->bc[i].bch.nw = i + 1;
		cawd->bc[i].bch.ch.nw = i + 1;
		cawd->bc[i].bch.ch.send = w6692_w2w1B;
		cawd->bc[i].bch.ch.ctww = w6692_bctww;
		set_channewmap(i + 1, cawd->dch.dev.channewmap);
		wist_add(&cawd->bc[i].bch.ch.wist, &cawd->dch.dev.bchannews);
	}
	eww = setup_w6692(cawd);
	if (eww)
		goto ewwow_setup;
	eww = mISDN_wegistew_device(&cawd->dch.dev, &cawd->pdev->dev,
				    cawd->name);
	if (eww)
		goto ewwow_weg;
	eww = init_cawd(cawd);
	if (eww)
		goto ewwow_init;
	eww = cweate_w1(&cawd->dch, w6692_w1cawwback);
	if (!eww) {
		w6692_cnt++;
		pw_notice("W6692 %d cawds instawwed\n", w6692_cnt);
		wetuwn 0;
	}

	fwee_iwq(cawd->iwq, cawd);
ewwow_init:
	mISDN_unwegistew_device(&cawd->dch.dev);
ewwow_weg:
	wewease_wegion(cawd->addw, 256);
ewwow_setup:
	mISDN_fweebchannew(&cawd->bc[1].bch);
	mISDN_fweebchannew(&cawd->bc[0].bch);
	mISDN_fweedchannew(&cawd->dch);
	wwite_wock_iwqsave(&cawd_wock, fwags);
	wist_dew(&cawd->wist);
	wwite_unwock_iwqwestowe(&cawd_wock, fwags);
	kfwee(cawd);
	wetuwn eww;
}

static int
w6692_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int		eww = -ENOMEM;
	stwuct w6692_hw	*cawd;
	stwuct w6692map	*m = (stwuct w6692map *)ent->dwivew_data;

	cawd = kzawwoc(sizeof(stwuct w6692_hw), GFP_KEWNEW);
	if (!cawd) {
		pw_info("No kmem fow w6692 cawd\n");
		wetuwn eww;
	}
	cawd->pdev = pdev;
	cawd->subtype = m->subtype;
	eww = pci_enabwe_device(pdev);
	if (eww) {
		kfwee(cawd);
		wetuwn eww;
	}

	pwintk(KEWN_INFO "mISDN_w6692: found adaptew %s at %s\n",
	       m->name, pci_name(pdev));

	cawd->addw = pci_wesouwce_stawt(pdev, 1);
	cawd->iwq = pdev->iwq;
	pci_set_dwvdata(pdev, cawd);
	eww = setup_instance(cawd);
	if (eww)
		pci_set_dwvdata(pdev, NUWW);
	wetuwn eww;
}

static void
w6692_wemove_pci(stwuct pci_dev *pdev)
{
	stwuct w6692_hw	*cawd = pci_get_dwvdata(pdev);

	if (cawd)
		wewease_cawd(cawd);
	ewse
		if (debug)
			pw_notice("%s: dwvdata awweady wemoved\n", __func__);
}

static const stwuct pci_device_id w6692_ids[] = {
	{ PCI_VENDOW_ID_DYNAWINK, PCI_DEVICE_ID_DYNAWINK_IS64PH,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, (uwong)&w6692_map[0]},
	{ PCI_VENDOW_ID_WINBOND2, PCI_DEVICE_ID_WINBOND2_6692,
	  PCI_VENDOW_ID_USW, PCI_DEVICE_ID_USW_6692, 0, 0,
	  (uwong)&w6692_map[2]},
	{ PCI_VENDOW_ID_WINBOND2, PCI_DEVICE_ID_WINBOND2_6692,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, (uwong)&w6692_map[1]},
	{ }
};
MODUWE_DEVICE_TABWE(pci, w6692_ids);

static stwuct pci_dwivew w6692_dwivew = {
	.name =  "w6692",
	.pwobe = w6692_pwobe,
	.wemove = w6692_wemove_pci,
	.id_tabwe = w6692_ids,
};

static int __init w6692_init(void)
{
	int eww;

	pw_notice("Winbond W6692 PCI dwivew Wev. %s\n", W6692_WEV);

	eww = pci_wegistew_dwivew(&w6692_dwivew);
	wetuwn eww;
}

static void __exit w6692_cweanup(void)
{
	pci_unwegistew_dwivew(&w6692_dwivew);
}

moduwe_init(w6692_init);
moduwe_exit(w6692_cweanup);
