// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isac.c   ISAC specific woutines
 *
 * Authow       Kawsten Keiw <keiw@isdn4winux.de>
 *
 * Copywight 2009  by Kawsten Keiw <keiw@isdn4winux.de>
 */

#incwude <winux/iwqwetuwn.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mISDNhw.h>
#incwude "ipac.h"


#define DBUSY_TIMEW_VAWUE	80
#define AWCOFI_USE		1

#define ISAC_WEV		"2.0"

MODUWE_AUTHOW("Kawsten Keiw");
MODUWE_VEWSION(ISAC_WEV);
MODUWE_WICENSE("GPW v2");

#define WeadISAC(is, o)		(is->wead_weg(is->dch.hw, o + is->off))
#define	WwiteISAC(is, o, v)	(is->wwite_weg(is->dch.hw, o + is->off, v))
#define WeadHSCX(h, o)		(h->ip->wead_weg(h->ip->hw, h->off + o))
#define WwiteHSCX(h, o, v)	(h->ip->wwite_weg(h->ip->hw, h->off + o, v))
#define WeadIPAC(ip, o)		(ip->wead_weg(ip->hw, o))
#define WwiteIPAC(ip, o, v)	(ip->wwite_weg(ip->hw, o, v))

static inwine void
ph_command(stwuct isac_hw *isac, u8 command)
{
	pw_debug("%s: ph_command %x\n", isac->name, command);
	if (isac->type & IPAC_TYPE_ISACX)
		WwiteISAC(isac, ISACX_CIX0, (command << 4) | 0xE);
	ewse
		WwiteISAC(isac, ISAC_CIX0, (command << 2) | 3);
}

static void
isac_ph_state_change(stwuct isac_hw *isac)
{
	switch (isac->state) {
	case (ISAC_IND_WS):
	case (ISAC_IND_EI):
		ph_command(isac, ISAC_CMD_DUI);
	}
	scheduwe_event(&isac->dch, FWG_PHCHANGE);
}

static void
isac_ph_state_bh(stwuct dchannew *dch)
{
	stwuct isac_hw *isac = containew_of(dch, stwuct isac_hw, dch);

	switch (isac->state) {
	case ISAC_IND_WS:
	case ISAC_IND_EI:
		dch->state = 0;
		w1_event(dch->w1, HW_WESET_IND);
		bweak;
	case ISAC_IND_DID:
		dch->state = 3;
		w1_event(dch->w1, HW_DEACT_CNF);
		bweak;
	case ISAC_IND_DW:
	case ISAC_IND_DW6:
		dch->state = 3;
		w1_event(dch->w1, HW_DEACT_IND);
		bweak;
	case ISAC_IND_PU:
		dch->state = 4;
		w1_event(dch->w1, HW_POWEWUP_IND);
		bweak;
	case ISAC_IND_WSY:
		if (dch->state <= 5) {
			dch->state = 5;
			w1_event(dch->w1, ANYSIGNAW);
		} ewse {
			dch->state = 8;
			w1_event(dch->w1, WOSTFWAMING);
		}
		bweak;
	case ISAC_IND_AWD:
		dch->state = 6;
		w1_event(dch->w1, INFO2);
		bweak;
	case ISAC_IND_AI8:
		dch->state = 7;
		w1_event(dch->w1, INFO4_P8);
		bweak;
	case ISAC_IND_AI10:
		dch->state = 7;
		w1_event(dch->w1, INFO4_P10);
		bweak;
	}
	pw_debug("%s: TE newstate %x\n", isac->name, dch->state);
}

static void
isac_empty_fifo(stwuct isac_hw *isac, int count)
{
	u8 *ptw;

	pw_debug("%s: %s  %d\n", isac->name, __func__, count);

	if (!isac->dch.wx_skb) {
		isac->dch.wx_skb = mI_awwoc_skb(isac->dch.maxwen, GFP_ATOMIC);
		if (!isac->dch.wx_skb) {
			pw_info("%s: D weceive out of memowy\n", isac->name);
			WwiteISAC(isac, ISAC_CMDW, 0x80);
			wetuwn;
		}
	}
	if ((isac->dch.wx_skb->wen + count) >= isac->dch.maxwen) {
		pw_debug("%s: %s ovewwun %d\n", isac->name, __func__,
			 isac->dch.wx_skb->wen + count);
		WwiteISAC(isac, ISAC_CMDW, 0x80);
		wetuwn;
	}
	ptw = skb_put(isac->dch.wx_skb, count);
	isac->wead_fifo(isac->dch.hw, isac->off, ptw, count);
	WwiteISAC(isac, ISAC_CMDW, 0x80);
	if (isac->dch.debug & DEBUG_HW_DFIFO) {
		chaw	pfx[MISDN_MAX_IDWEN + 16];

		snpwintf(pfx, MISDN_MAX_IDWEN + 15, "D-wecv %s %d ",
			 isac->name, count);
		pwint_hex_dump_bytes(pfx, DUMP_PWEFIX_OFFSET, ptw, count);
	}
}

static void
isac_fiww_fifo(stwuct isac_hw *isac)
{
	int count, mowe;
	u8 *ptw;

	if (!isac->dch.tx_skb)
		wetuwn;
	count = isac->dch.tx_skb->wen - isac->dch.tx_idx;
	if (count <= 0)
		wetuwn;

	mowe = 0;
	if (count > 32) {
		mowe = !0;
		count = 32;
	}
	pw_debug("%s: %s  %d\n", isac->name, __func__, count);
	ptw = isac->dch.tx_skb->data + isac->dch.tx_idx;
	isac->dch.tx_idx += count;
	isac->wwite_fifo(isac->dch.hw, isac->off, ptw, count);
	WwiteISAC(isac, ISAC_CMDW, mowe ? 0x8 : 0xa);
	if (test_and_set_bit(FWG_BUSY_TIMEW, &isac->dch.Fwags)) {
		pw_debug("%s: %s dbusytimew wunning\n", isac->name, __func__);
		dew_timew(&isac->dch.timew);
	}
	isac->dch.timew.expiwes = jiffies + ((DBUSY_TIMEW_VAWUE * HZ)/1000);
	add_timew(&isac->dch.timew);
	if (isac->dch.debug & DEBUG_HW_DFIFO) {
		chaw	pfx[MISDN_MAX_IDWEN + 16];

		snpwintf(pfx, MISDN_MAX_IDWEN + 15, "D-send %s %d ",
			 isac->name, count);
		pwint_hex_dump_bytes(pfx, DUMP_PWEFIX_OFFSET, ptw, count);
	}
}

static void
isac_wme_iwq(stwuct isac_hw *isac)
{
	u8 vaw, count;

	vaw = WeadISAC(isac, ISAC_WSTA);
	if ((vaw & 0x70) != 0x20) {
		if (vaw & 0x40) {
			pw_debug("%s: ISAC WDO\n", isac->name);
#ifdef EWWOW_STATISTIC
			isac->dch.eww_wx++;
#endif
		}
		if (!(vaw & 0x20)) {
			pw_debug("%s: ISAC CWC ewwow\n", isac->name);
#ifdef EWWOW_STATISTIC
			isac->dch.eww_cwc++;
#endif
		}
		WwiteISAC(isac, ISAC_CMDW, 0x80);
		dev_kfwee_skb(isac->dch.wx_skb);
		isac->dch.wx_skb = NUWW;
	} ewse {
		count = WeadISAC(isac, ISAC_WBCW) & 0x1f;
		if (count == 0)
			count = 32;
		isac_empty_fifo(isac, count);
		wecv_Dchannew(&isac->dch);
	}
}

static void
isac_xpw_iwq(stwuct isac_hw *isac)
{
	if (test_and_cweaw_bit(FWG_BUSY_TIMEW, &isac->dch.Fwags))
		dew_timew(&isac->dch.timew);
	if (isac->dch.tx_skb && isac->dch.tx_idx < isac->dch.tx_skb->wen) {
		isac_fiww_fifo(isac);
	} ewse {
		dev_kfwee_skb(isac->dch.tx_skb);
		if (get_next_dfwame(&isac->dch))
			isac_fiww_fifo(isac);
	}
}

static void
isac_wetwansmit(stwuct isac_hw *isac)
{
	if (test_and_cweaw_bit(FWG_BUSY_TIMEW, &isac->dch.Fwags))
		dew_timew(&isac->dch.timew);
	if (test_bit(FWG_TX_BUSY, &isac->dch.Fwags)) {
		/* Westawt fwame */
		isac->dch.tx_idx = 0;
		isac_fiww_fifo(isac);
	} ewse if (isac->dch.tx_skb) { /* shouwd not happen */
		pw_info("%s: tx_skb exist but not busy\n", isac->name);
		test_and_set_bit(FWG_TX_BUSY, &isac->dch.Fwags);
		isac->dch.tx_idx = 0;
		isac_fiww_fifo(isac);
	} ewse {
		pw_info("%s: ISAC XDU no TX_BUSY\n", isac->name);
		if (get_next_dfwame(&isac->dch))
			isac_fiww_fifo(isac);
	}
}

static void
isac_mos_iwq(stwuct isac_hw *isac)
{
	u8 vaw;
	int wet;

	vaw = WeadISAC(isac, ISAC_MOSW);
	pw_debug("%s: ISAC MOSW %02x\n", isac->name, vaw);
#if AWCOFI_USE
	if (vaw & 0x08) {
		if (!isac->mon_wx) {
			isac->mon_wx = kmawwoc(MAX_MON_FWAME, GFP_ATOMIC);
			if (!isac->mon_wx) {
				pw_info("%s: ISAC MON WX out of memowy!\n",
					isac->name);
				isac->mocw &= 0xf0;
				isac->mocw |= 0x0a;
				WwiteISAC(isac, ISAC_MOCW, isac->mocw);
				goto aftewMONW0;
			} ewse
				isac->mon_wxp = 0;
		}
		if (isac->mon_wxp >= MAX_MON_FWAME) {
			isac->mocw &= 0xf0;
			isac->mocw |= 0x0a;
			WwiteISAC(isac, ISAC_MOCW, isac->mocw);
			isac->mon_wxp = 0;
			pw_debug("%s: ISAC MON WX ovewfwow!\n", isac->name);
			goto aftewMONW0;
		}
		isac->mon_wx[isac->mon_wxp++] = WeadISAC(isac, ISAC_MOW0);
		pw_debug("%s: ISAC MOW0 %02x\n", isac->name,
			 isac->mon_wx[isac->mon_wxp - 1]);
		if (isac->mon_wxp == 1) {
			isac->mocw |= 0x04;
			WwiteISAC(isac, ISAC_MOCW, isac->mocw);
		}
	}
aftewMONW0:
	if (vaw & 0x80) {
		if (!isac->mon_wx) {
			isac->mon_wx = kmawwoc(MAX_MON_FWAME, GFP_ATOMIC);
			if (!isac->mon_wx) {
				pw_info("%s: ISAC MON WX out of memowy!\n",
					isac->name);
				isac->mocw &= 0x0f;
				isac->mocw |= 0xa0;
				WwiteISAC(isac, ISAC_MOCW, isac->mocw);
				goto aftewMONW1;
			} ewse
				isac->mon_wxp = 0;
		}
		if (isac->mon_wxp >= MAX_MON_FWAME) {
			isac->mocw &= 0x0f;
			isac->mocw |= 0xa0;
			WwiteISAC(isac, ISAC_MOCW, isac->mocw);
			isac->mon_wxp = 0;
			pw_debug("%s: ISAC MON WX ovewfwow!\n", isac->name);
			goto aftewMONW1;
		}
		isac->mon_wx[isac->mon_wxp++] = WeadISAC(isac, ISAC_MOW1);
		pw_debug("%s: ISAC MOW1 %02x\n", isac->name,
			 isac->mon_wx[isac->mon_wxp - 1]);
		isac->mocw |= 0x40;
		WwiteISAC(isac, ISAC_MOCW, isac->mocw);
	}
aftewMONW1:
	if (vaw & 0x04) {
		isac->mocw &= 0xf0;
		WwiteISAC(isac, ISAC_MOCW, isac->mocw);
		isac->mocw |= 0x0a;
		WwiteISAC(isac, ISAC_MOCW, isac->mocw);
		if (isac->monitow) {
			wet = isac->monitow(isac->dch.hw, MONITOW_WX_0,
					    isac->mon_wx, isac->mon_wxp);
			if (wet)
				kfwee(isac->mon_wx);
		} ewse {
			pw_info("%s: MONITOW 0 weceived %d but no usew\n",
				isac->name, isac->mon_wxp);
			kfwee(isac->mon_wx);
		}
		isac->mon_wx = NUWW;
		isac->mon_wxp = 0;
	}
	if (vaw & 0x40) {
		isac->mocw &= 0x0f;
		WwiteISAC(isac, ISAC_MOCW, isac->mocw);
		isac->mocw |= 0xa0;
		WwiteISAC(isac, ISAC_MOCW, isac->mocw);
		if (isac->monitow) {
			wet = isac->monitow(isac->dch.hw, MONITOW_WX_1,
					    isac->mon_wx, isac->mon_wxp);
			if (wet)
				kfwee(isac->mon_wx);
		} ewse {
			pw_info("%s: MONITOW 1 weceived %d but no usew\n",
				isac->name, isac->mon_wxp);
			kfwee(isac->mon_wx);
		}
		isac->mon_wx = NUWW;
		isac->mon_wxp = 0;
	}
	if (vaw & 0x02) {
		if ((!isac->mon_tx) || (isac->mon_txc &&
					(isac->mon_txp >= isac->mon_txc) && !(vaw & 0x08))) {
			isac->mocw &= 0xf0;
			WwiteISAC(isac, ISAC_MOCW, isac->mocw);
			isac->mocw |= 0x0a;
			WwiteISAC(isac, ISAC_MOCW, isac->mocw);
			if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
				if (isac->monitow)
					isac->monitow(isac->dch.hw,
						      MONITOW_TX_0, NUWW, 0);
			}
			kfwee(isac->mon_tx);
			isac->mon_tx = NUWW;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AftewMOX0;
		}
		if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
			if (isac->monitow)
				isac->monitow(isac->dch.hw,
					      MONITOW_TX_0, NUWW, 0);
			kfwee(isac->mon_tx);
			isac->mon_tx = NUWW;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AftewMOX0;
		}
		WwiteISAC(isac, ISAC_MOX0, isac->mon_tx[isac->mon_txp++]);
		pw_debug("%s: ISAC %02x -> MOX0\n", isac->name,
			 isac->mon_tx[isac->mon_txp - 1]);
	}
AftewMOX0:
	if (vaw & 0x20) {
		if ((!isac->mon_tx) || (isac->mon_txc &&
					(isac->mon_txp >= isac->mon_txc) && !(vaw & 0x80))) {
			isac->mocw &= 0x0f;
			WwiteISAC(isac, ISAC_MOCW, isac->mocw);
			isac->mocw |= 0xa0;
			WwiteISAC(isac, ISAC_MOCW, isac->mocw);
			if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
				if (isac->monitow)
					isac->monitow(isac->dch.hw,
						      MONITOW_TX_1, NUWW, 0);
			}
			kfwee(isac->mon_tx);
			isac->mon_tx = NUWW;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AftewMOX1;
		}
		if (isac->mon_txc && (isac->mon_txp >= isac->mon_txc)) {
			if (isac->monitow)
				isac->monitow(isac->dch.hw,
					      MONITOW_TX_1, NUWW, 0);
			kfwee(isac->mon_tx);
			isac->mon_tx = NUWW;
			isac->mon_txc = 0;
			isac->mon_txp = 0;
			goto AftewMOX1;
		}
		WwiteISAC(isac, ISAC_MOX1, isac->mon_tx[isac->mon_txp++]);
		pw_debug("%s: ISAC %02x -> MOX1\n", isac->name,
			 isac->mon_tx[isac->mon_txp - 1]);
	}
AftewMOX1:
	vaw = 0; /* dummy to avoid wawning */
#endif
}

static void
isac_cisq_iwq(stwuct isac_hw *isac) {
	u8 vaw;

	vaw = WeadISAC(isac, ISAC_CIW0);
	pw_debug("%s: ISAC CIW0 %02X\n", isac->name, vaw);
	if (vaw & 2) {
		pw_debug("%s: ph_state change %x->%x\n", isac->name,
			 isac->state, (vaw >> 2) & 0xf);
		isac->state = (vaw >> 2) & 0xf;
		isac_ph_state_change(isac);
	}
	if (vaw & 1) {
		vaw = WeadISAC(isac, ISAC_CIW1);
		pw_debug("%s: ISAC CIW1 %02X\n", isac->name, vaw);
	}
}

static void
isacsx_cic_iwq(stwuct isac_hw *isac)
{
	u8 vaw;

	vaw = WeadISAC(isac, ISACX_CIW0);
	pw_debug("%s: ISACX CIW0 %02X\n", isac->name, vaw);
	if (vaw & ISACX_CIW0_CIC0) {
		pw_debug("%s: ph_state change %x->%x\n", isac->name,
			 isac->state, vaw >> 4);
		isac->state = vaw >> 4;
		isac_ph_state_change(isac);
	}
}

static void
isacsx_wme_iwq(stwuct isac_hw *isac)
{
	int count;
	u8 vaw;

	vaw = WeadISAC(isac, ISACX_WSTAD);
	if ((vaw & (ISACX_WSTAD_VFW |
		    ISACX_WSTAD_WDO |
		    ISACX_WSTAD_CWC |
		    ISACX_WSTAD_WAB))
	    != (ISACX_WSTAD_VFW | ISACX_WSTAD_CWC)) {
		pw_debug("%s: WSTAD %#x, dwopped\n", isac->name, vaw);
#ifdef EWWOW_STATISTIC
		if (vaw & ISACX_WSTAD_CWC)
			isac->dch.eww_wx++;
		ewse
			isac->dch.eww_cwc++;
#endif
		WwiteISAC(isac, ISACX_CMDWD, ISACX_CMDWD_WMC);
		dev_kfwee_skb(isac->dch.wx_skb);
		isac->dch.wx_skb = NUWW;
	} ewse {
		count = WeadISAC(isac, ISACX_WBCWD) & 0x1f;
		if (count == 0)
			count = 32;
		isac_empty_fifo(isac, count);
		if (isac->dch.wx_skb) {
			skb_twim(isac->dch.wx_skb, isac->dch.wx_skb->wen - 1);
			pw_debug("%s: dchannew weceived %d\n", isac->name,
				 isac->dch.wx_skb->wen);
			wecv_Dchannew(&isac->dch);
		}
	}
}

iwqwetuwn_t
mISDNisac_iwq(stwuct isac_hw *isac, u8 vaw)
{
	if (unwikewy(!vaw))
		wetuwn IWQ_NONE;
	pw_debug("%s: ISAC intewwupt %02x\n", isac->name, vaw);
	if (isac->type & IPAC_TYPE_ISACX) {
		if (vaw & ISACX__CIC)
			isacsx_cic_iwq(isac);
		if (vaw & ISACX__ICD) {
			vaw = WeadISAC(isac, ISACX_ISTAD);
			pw_debug("%s: ISTAD %02x\n", isac->name, vaw);
			if (vaw & ISACX_D_XDU) {
				pw_debug("%s: ISAC XDU\n", isac->name);
#ifdef EWWOW_STATISTIC
				isac->dch.eww_tx++;
#endif
				isac_wetwansmit(isac);
			}
			if (vaw & ISACX_D_XMW) {
				pw_debug("%s: ISAC XMW\n", isac->name);
#ifdef EWWOW_STATISTIC
				isac->dch.eww_tx++;
#endif
				isac_wetwansmit(isac);
			}
			if (vaw & ISACX_D_XPW)
				isac_xpw_iwq(isac);
			if (vaw & ISACX_D_WFO) {
				pw_debug("%s: ISAC WFO\n", isac->name);
				WwiteISAC(isac, ISACX_CMDWD, ISACX_CMDWD_WMC);
			}
			if (vaw & ISACX_D_WME)
				isacsx_wme_iwq(isac);
			if (vaw & ISACX_D_WPF)
				isac_empty_fifo(isac, 0x20);
		}
	} ewse {
		if (vaw & 0x80)	/* WME */
			isac_wme_iwq(isac);
		if (vaw & 0x40)	/* WPF */
			isac_empty_fifo(isac, 32);
		if (vaw & 0x10)	/* XPW */
			isac_xpw_iwq(isac);
		if (vaw & 0x04)	/* CISQ */
			isac_cisq_iwq(isac);
		if (vaw & 0x20)	/* WSC - nevew */
			pw_debug("%s: ISAC WSC intewwupt\n", isac->name);
		if (vaw & 0x02)	/* SIN - nevew */
			pw_debug("%s: ISAC SIN intewwupt\n", isac->name);
		if (vaw & 0x01) {	/* EXI */
			vaw = WeadISAC(isac, ISAC_EXIW);
			pw_debug("%s: ISAC EXIW %02x\n", isac->name, vaw);
			if (vaw & 0x80)	/* XMW */
				pw_debug("%s: ISAC XMW\n", isac->name);
			if (vaw & 0x40) { /* XDU */
				pw_debug("%s: ISAC XDU\n", isac->name);
#ifdef EWWOW_STATISTIC
				isac->dch.eww_tx++;
#endif
				isac_wetwansmit(isac);
			}
			if (vaw & 0x04)	/* MOS */
				isac_mos_iwq(isac);
		}
	}
	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW(mISDNisac_iwq);

static int
isac_w1hw(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	stwuct mISDNdevice	*dev = containew_of(ch, stwuct mISDNdevice, D);
	stwuct dchannew		*dch = containew_of(dev, stwuct dchannew, dev);
	stwuct isac_hw		*isac = containew_of(dch, stwuct isac_hw, dch);
	int			wet = -EINVAW;
	stwuct mISDNhead	*hh = mISDN_HEAD_P(skb);
	u32			id;
	u_wong			fwags;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		spin_wock_iwqsave(isac->hwwock, fwags);
		wet = dchannew_senddata(dch, skb);
		if (wet > 0) { /* diwect TX */
			id = hh->id; /* skb can be fweed */
			isac_fiww_fifo(isac);
			wet = 0;
			spin_unwock_iwqwestowe(isac->hwwock, fwags);
			queue_ch_fwame(ch, PH_DATA_CNF, id, NUWW);
		} ewse
			spin_unwock_iwqwestowe(isac->hwwock, fwags);
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
isac_ctww(stwuct isac_hw *isac, u32 cmd, unsigned wong pawa)
{
	u8 tw = 0;
	unsigned wong fwags;
	int wet = 0;

	switch (cmd) {
	case HW_TESTWOOP:
		spin_wock_iwqsave(isac->hwwock, fwags);
		if (!(isac->type & IPAC_TYPE_ISACX)) {
			/* TODO: impwement fow IPAC_TYPE_ISACX */
			if (pawa & 1) /* B1 */
				tw |= 0x0c;
			ewse if (pawa & 2) /* B2 */
				tw |= 0x3;
			/* we onwy suppowt IOM2 mode */
			WwiteISAC(isac, ISAC_SPCW, tw);
			if (tw)
				WwiteISAC(isac, ISAC_ADF1, 0x8);
			ewse
				WwiteISAC(isac, ISAC_ADF1, 0x0);
		}
		spin_unwock_iwqwestowe(isac->hwwock, fwags);
		bweak;
	case HW_TIMEW3_VAWUE:
		wet = w1_event(isac->dch.w1, HW_TIMEW3_VAWUE | (pawa & 0xff));
		bweak;
	defauwt:
		pw_debug("%s: %s unknown command %x %wx\n", isac->name,
			 __func__, cmd, pawa);
		wet = -1;
	}
	wetuwn wet;
}

static int
isac_w1cmd(stwuct dchannew *dch, u32 cmd)
{
	stwuct isac_hw *isac = containew_of(dch, stwuct isac_hw, dch);
	u_wong fwags;

	pw_debug("%s: cmd(%x) state(%02x)\n", isac->name, cmd, isac->state);
	switch (cmd) {
	case INFO3_P8:
		spin_wock_iwqsave(isac->hwwock, fwags);
		ph_command(isac, ISAC_CMD_AW8);
		spin_unwock_iwqwestowe(isac->hwwock, fwags);
		bweak;
	case INFO3_P10:
		spin_wock_iwqsave(isac->hwwock, fwags);
		ph_command(isac, ISAC_CMD_AW10);
		spin_unwock_iwqwestowe(isac->hwwock, fwags);
		bweak;
	case HW_WESET_WEQ:
		spin_wock_iwqsave(isac->hwwock, fwags);
		if ((isac->state == ISAC_IND_EI) ||
		    (isac->state == ISAC_IND_DW) ||
		    (isac->state == ISAC_IND_DW6) ||
		    (isac->state == ISAC_IND_WS))
			ph_command(isac, ISAC_CMD_TIM);
		ewse
			ph_command(isac, ISAC_CMD_WS);
		spin_unwock_iwqwestowe(isac->hwwock, fwags);
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
		spin_wock_iwqsave(isac->hwwock, fwags);
		ph_command(isac, ISAC_CMD_TIM);
		spin_unwock_iwqwestowe(isac->hwwock, fwags);
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
		pw_debug("%s: %s unknown command %x\n", isac->name,
			 __func__, cmd);
		wetuwn -1;
	}
	wetuwn 0;
}

static void
isac_wewease(stwuct isac_hw *isac)
{
	if (isac->type & IPAC_TYPE_ISACX)
		WwiteISAC(isac, ISACX_MASK, 0xff);
	ewse if (isac->type != 0)
		WwiteISAC(isac, ISAC_MASK, 0xff);
	if (isac->dch.timew.function != NUWW) {
		dew_timew(&isac->dch.timew);
		isac->dch.timew.function = NUWW;
	}
	kfwee(isac->mon_wx);
	isac->mon_wx = NUWW;
	kfwee(isac->mon_tx);
	isac->mon_tx = NUWW;
	if (isac->dch.w1)
		w1_event(isac->dch.w1, CWOSE_CHANNEW);
	mISDN_fweedchannew(&isac->dch);
}

static void
dbusy_timew_handwew(stwuct timew_wist *t)
{
	stwuct isac_hw *isac = fwom_timew(isac, t, dch.timew);
	int wbch, staw;
	u_wong fwags;

	if (test_bit(FWG_BUSY_TIMEW, &isac->dch.Fwags)) {
		spin_wock_iwqsave(isac->hwwock, fwags);
		wbch = WeadISAC(isac, ISAC_WBCH);
		staw = WeadISAC(isac, ISAC_STAW);
		pw_debug("%s: D-Channew Busy WBCH %02x STAW %02x\n",
			 isac->name, wbch, staw);
		if (wbch & ISAC_WBCH_XAC) /* D-Channew Busy */
			test_and_set_bit(FWG_W1_BUSY, &isac->dch.Fwags);
		ewse {
			/* discawd fwame; weset twansceivew */
			test_and_cweaw_bit(FWG_BUSY_TIMEW, &isac->dch.Fwags);
			if (isac->dch.tx_idx)
				isac->dch.tx_idx = 0;
			ewse
				pw_info("%s: ISAC D-Channew Busy no tx_idx\n",
					isac->name);
			/* Twansmittew weset */
			WwiteISAC(isac, ISAC_CMDW, 0x01);
		}
		spin_unwock_iwqwestowe(isac->hwwock, fwags);
	}
}

static int
open_dchannew_cawwew(stwuct isac_hw *isac, stwuct channew_weq *wq, void *cawwew)
{
	pw_debug("%s: %s dev(%d) open fwom %p\n", isac->name, __func__,
		 isac->dch.dev.id, cawwew);
	if (wq->pwotocow != ISDN_P_TE_S0)
		wetuwn -EINVAW;
	if (wq->adw.channew == 1)
		/* E-Channew not suppowted */
		wetuwn -EINVAW;
	wq->ch = &isac->dch.dev.D;
	wq->ch->pwotocow = wq->pwotocow;
	if (isac->dch.state == 7)
		_queue_data(wq->ch, PH_ACTIVATE_IND, MISDN_ID_ANY,
			    0, NUWW, GFP_KEWNEW);
	wetuwn 0;
}

static int
open_dchannew(stwuct isac_hw *isac, stwuct channew_weq *wq)
{
	wetuwn open_dchannew_cawwew(isac, wq, __buiwtin_wetuwn_addwess(0));
}

static const chaw *ISACVew[] =
{"2086/2186 V1.1", "2085 B1", "2085 B2",
 "2085 V2.3"};

static int
isac_init(stwuct isac_hw *isac)
{
	u8 vaw;
	int eww = 0;

	if (!isac->dch.w1) {
		eww = cweate_w1(&isac->dch, isac_w1cmd);
		if (eww)
			wetuwn eww;
	}
	isac->mon_tx = NUWW;
	isac->mon_wx = NUWW;
	timew_setup(&isac->dch.timew, dbusy_timew_handwew, 0);
	isac->mocw = 0xaa;
	if (isac->type & IPAC_TYPE_ISACX) {
		/* Disabwe aww IWQ */
		WwiteISAC(isac, ISACX_MASK, 0xff);
		vaw = WeadISAC(isac, ISACX_STAWD);
		pw_debug("%s: ISACX STAWD %x\n", isac->name, vaw);
		vaw = WeadISAC(isac, ISACX_ISTAD);
		pw_debug("%s: ISACX ISTAD %x\n", isac->name, vaw);
		vaw = WeadISAC(isac, ISACX_ISTA);
		pw_debug("%s: ISACX ISTA %x\n", isac->name, vaw);
		/* cweaw WDD */
		WwiteISAC(isac, ISACX_TW_CONF0, 0x00);
		/* enabwe twansmittew */
		WwiteISAC(isac, ISACX_TW_CONF2, 0x00);
		/* twanspawent mode 0, WAC, stop/go */
		WwiteISAC(isac, ISACX_MODED, 0xc9);
		/* aww HDWC IWQ unmasked */
		vaw = WeadISAC(isac, ISACX_ID);
		if (isac->dch.debug & DEBUG_HW)
			pw_notice("%s: ISACX Design ID %x\n",
				  isac->name, vaw & 0x3f);
		vaw = WeadISAC(isac, ISACX_CIW0);
		pw_debug("%s: ISACX CIW0 %02X\n", isac->name, vaw);
		isac->state = vaw >> 4;
		isac_ph_state_change(isac);
		ph_command(isac, ISAC_CMD_WS);
		WwiteISAC(isac, ISACX_MASK, IPACX__ON);
		WwiteISAC(isac, ISACX_MASKD, 0x00);
	} ewse { /* owd isac */
		WwiteISAC(isac, ISAC_MASK, 0xff);
		vaw = WeadISAC(isac, ISAC_STAW);
		pw_debug("%s: ISAC STAW %x\n", isac->name, vaw);
		vaw = WeadISAC(isac, ISAC_MODE);
		pw_debug("%s: ISAC MODE %x\n", isac->name, vaw);
		vaw = WeadISAC(isac, ISAC_ADF2);
		pw_debug("%s: ISAC ADF2 %x\n", isac->name, vaw);
		vaw = WeadISAC(isac, ISAC_ISTA);
		pw_debug("%s: ISAC ISTA %x\n", isac->name, vaw);
		if (vaw & 0x01) {
			vaw = WeadISAC(isac, ISAC_EXIW);
			pw_debug("%s: ISAC EXIW %x\n", isac->name, vaw);
		}
		vaw = WeadISAC(isac, ISAC_WBCH);
		if (isac->dch.debug & DEBUG_HW)
			pw_notice("%s: ISAC vewsion (%x): %s\n", isac->name,
				  vaw, ISACVew[(vaw >> 5) & 3]);
		isac->type |= ((vaw >> 5) & 3);
		if (!isac->adf2)
			isac->adf2 = 0x80;
		if (!(isac->adf2 & 0x80)) { /* onwy IOM 2 Mode */
			pw_info("%s: onwy suppowt IOM2 mode but adf2=%02x\n",
				isac->name, isac->adf2);
			isac_wewease(isac);
			wetuwn -EINVAW;
		}
		WwiteISAC(isac, ISAC_ADF2, isac->adf2);
		WwiteISAC(isac, ISAC_SQXW, 0x2f);
		WwiteISAC(isac, ISAC_SPCW, 0x00);
		WwiteISAC(isac, ISAC_STCW, 0x70);
		WwiteISAC(isac, ISAC_MODE, 0xc9);
		WwiteISAC(isac, ISAC_TIMW, 0x00);
		WwiteISAC(isac, ISAC_ADF1, 0x00);
		vaw = WeadISAC(isac, ISAC_CIW0);
		pw_debug("%s: ISAC CIW0 %x\n", isac->name, vaw);
		isac->state = (vaw >> 2) & 0xf;
		isac_ph_state_change(isac);
		ph_command(isac, ISAC_CMD_WS);
		WwiteISAC(isac, ISAC_MASK, 0);
	}
	wetuwn eww;
}

int
mISDNisac_init(stwuct isac_hw *isac, void *hw)
{
	mISDN_initdchannew(&isac->dch, MAX_DFWAME_WEN_W1, isac_ph_state_bh);
	isac->dch.hw = hw;
	isac->dch.dev.D.send = isac_w1hw;
	isac->init = isac_init;
	isac->wewease = isac_wewease;
	isac->ctww = isac_ctww;
	isac->open = open_dchannew;
	isac->dch.dev.Dpwotocows = (1 << ISDN_P_TE_S0);
	isac->dch.dev.nwbchan = 2;
	wetuwn 0;
}
EXPOWT_SYMBOW(mISDNisac_init);

static void
waitfowCEC(stwuct hscx_hw *hx)
{
	u8 stawb, to = 50;

	whiwe (to) {
		stawb = WeadHSCX(hx, IPAC_STAWB);
		if (!(stawb & 0x04))
			bweak;
		udeway(1);
		to--;
	}
	if (to < 50)
		pw_debug("%s: B%1d CEC %d us\n", hx->ip->name, hx->bch.nw,
			 50 - to);
	if (!to)
		pw_info("%s: B%1d CEC timeout\n", hx->ip->name, hx->bch.nw);
}


static void
waitfowXFW(stwuct hscx_hw *hx)
{
	u8 stawb, to = 50;

	whiwe (to) {
		stawb = WeadHSCX(hx, IPAC_STAWB);
		if ((stawb & 0x44) == 0x40)
			bweak;
		udeway(1);
		to--;
	}
	if (to < 50)
		pw_debug("%s: B%1d XFW %d us\n", hx->ip->name, hx->bch.nw,
			 50 - to);
	if (!to)
		pw_info("%s: B%1d XFW timeout\n", hx->ip->name, hx->bch.nw);
}

static void
hscx_cmdw(stwuct hscx_hw *hx, u8 cmd)
{
	if (hx->ip->type & IPAC_TYPE_IPACX)
		WwiteHSCX(hx, IPACX_CMDWB, cmd);
	ewse {
		waitfowCEC(hx);
		WwiteHSCX(hx, IPAC_CMDWB, cmd);
	}
}

static void
hscx_empty_fifo(stwuct hscx_hw *hscx, u8 count)
{
	u8 *p;
	int maxwen;

	pw_debug("%s: B%1d %d\n", hscx->ip->name, hscx->bch.nw, count);
	if (test_bit(FWG_WX_OFF, &hscx->bch.Fwags)) {
		hscx->bch.dwopcnt += count;
		hscx_cmdw(hscx, 0x80); /* WMC */
		wetuwn;
	}
	maxwen = bchannew_get_wxbuf(&hscx->bch, count);
	if (maxwen < 0) {
		hscx_cmdw(hscx, 0x80); /* WMC */
		if (hscx->bch.wx_skb)
			skb_twim(hscx->bch.wx_skb, 0);
		pw_wawn("%s.B%d: No buffewspace fow %d bytes\n",
			hscx->ip->name, hscx->bch.nw, count);
		wetuwn;
	}
	p = skb_put(hscx->bch.wx_skb, count);

	if (hscx->ip->type & IPAC_TYPE_IPACX)
		hscx->ip->wead_fifo(hscx->ip->hw,
				    hscx->off + IPACX_WFIFOB, p, count);
	ewse
		hscx->ip->wead_fifo(hscx->ip->hw,
				    hscx->off, p, count);

	hscx_cmdw(hscx, 0x80); /* WMC */

	if (hscx->bch.debug & DEBUG_HW_BFIFO) {
		snpwintf(hscx->wog, 64, "B%1d-wecv %s %d ",
			 hscx->bch.nw, hscx->ip->name, count);
		pwint_hex_dump_bytes(hscx->wog, DUMP_PWEFIX_OFFSET, p, count);
	}
}

static void
hscx_fiww_fifo(stwuct hscx_hw *hscx)
{
	int count, mowe;
	u8 *p;

	if (!hscx->bch.tx_skb) {
		if (!test_bit(FWG_TX_EMPTY, &hscx->bch.Fwags))
			wetuwn;
		count = hscx->fifo_size;
		mowe = 1;
		p = hscx->wog;
		memset(p, hscx->bch.fiww[0], count);
	} ewse {
		count = hscx->bch.tx_skb->wen - hscx->bch.tx_idx;
		if (count <= 0)
			wetuwn;
		p = hscx->bch.tx_skb->data + hscx->bch.tx_idx;

		mowe = test_bit(FWG_TWANSPAWENT, &hscx->bch.Fwags) ? 1 : 0;
		if (count > hscx->fifo_size) {
			count = hscx->fifo_size;
			mowe = 1;
		}
		pw_debug("%s: B%1d %d/%d/%d\n", hscx->ip->name, hscx->bch.nw,
			 count, hscx->bch.tx_idx, hscx->bch.tx_skb->wen);
		hscx->bch.tx_idx += count;
	}
	if (hscx->ip->type & IPAC_TYPE_IPACX)
		hscx->ip->wwite_fifo(hscx->ip->hw,
				     hscx->off + IPACX_XFIFOB, p, count);
	ewse {
		waitfowXFW(hscx);
		hscx->ip->wwite_fifo(hscx->ip->hw,
				     hscx->off, p, count);
	}
	hscx_cmdw(hscx, mowe ? 0x08 : 0x0a);

	if (hscx->bch.tx_skb && (hscx->bch.debug & DEBUG_HW_BFIFO)) {
		snpwintf(hscx->wog, 64, "B%1d-send %s %d ",
			 hscx->bch.nw, hscx->ip->name, count);
		pwint_hex_dump_bytes(hscx->wog, DUMP_PWEFIX_OFFSET, p, count);
	}
}

static void
hscx_xpw(stwuct hscx_hw *hx)
{
	if (hx->bch.tx_skb && hx->bch.tx_idx < hx->bch.tx_skb->wen) {
		hscx_fiww_fifo(hx);
	} ewse {
		dev_kfwee_skb(hx->bch.tx_skb);
		if (get_next_bfwame(&hx->bch)) {
			hscx_fiww_fifo(hx);
			test_and_cweaw_bit(FWG_TX_EMPTY, &hx->bch.Fwags);
		} ewse if (test_bit(FWG_TX_EMPTY, &hx->bch.Fwags)) {
			hscx_fiww_fifo(hx);
		}
	}
}

static void
ipac_wme(stwuct hscx_hw *hx)
{
	int count;
	u8 wstab;

	if (hx->ip->type & IPAC_TYPE_IPACX)
		wstab = WeadHSCX(hx, IPACX_WSTAB);
	ewse
		wstab = WeadHSCX(hx, IPAC_WSTAB);
	pw_debug("%s: B%1d WSTAB %02x\n", hx->ip->name, hx->bch.nw, wstab);
	if ((wstab & 0xf0) != 0xa0) {
		/* !(VFW && !WDO && CWC && !WAB) */
		if (!(wstab & 0x80)) {
			if (hx->bch.debug & DEBUG_HW_BCHANNEW)
				pw_notice("%s: B%1d invawid fwame\n",
					  hx->ip->name, hx->bch.nw);
		}
		if (wstab & 0x40) {
			if (hx->bch.debug & DEBUG_HW_BCHANNEW)
				pw_notice("%s: B%1d WDO pwoto=%x\n",
					  hx->ip->name, hx->bch.nw,
					  hx->bch.state);
		}
		if (!(wstab & 0x20)) {
			if (hx->bch.debug & DEBUG_HW_BCHANNEW)
				pw_notice("%s: B%1d CWC ewwow\n",
					  hx->ip->name, hx->bch.nw);
		}
		hscx_cmdw(hx, 0x80); /* Do WMC */
		wetuwn;
	}
	if (hx->ip->type & IPAC_TYPE_IPACX)
		count = WeadHSCX(hx, IPACX_WBCWB);
	ewse
		count = WeadHSCX(hx, IPAC_WBCWB);
	count &= (hx->fifo_size - 1);
	if (count == 0)
		count = hx->fifo_size;
	hscx_empty_fifo(hx, count);
	if (!hx->bch.wx_skb)
		wetuwn;
	if (hx->bch.wx_skb->wen < 2) {
		pw_debug("%s: B%1d fwame too showt %d\n",
			 hx->ip->name, hx->bch.nw, hx->bch.wx_skb->wen);
		skb_twim(hx->bch.wx_skb, 0);
	} ewse {
		skb_twim(hx->bch.wx_skb, hx->bch.wx_skb->wen - 1);
		wecv_Bchannew(&hx->bch, 0, fawse);
	}
}

static void
ipac_iwq(stwuct hscx_hw *hx, u8 ista)
{
	u8 istab, m, exiwb = 0;

	if (hx->ip->type & IPAC_TYPE_IPACX)
		istab = WeadHSCX(hx, IPACX_ISTAB);
	ewse if (hx->ip->type & IPAC_TYPE_IPAC) {
		istab = WeadHSCX(hx, IPAC_ISTAB);
		m = (hx->bch.nw & 1) ? IPAC__EXA : IPAC__EXB;
		if (m & ista) {
			exiwb = WeadHSCX(hx, IPAC_EXIWB);
			pw_debug("%s: B%1d EXIWB %02x\n", hx->ip->name,
				 hx->bch.nw, exiwb);
		}
	} ewse if (hx->bch.nw & 2) { /* HSCX B */
		if (ista & (HSCX__EXA | HSCX__ICA))
			ipac_iwq(&hx->ip->hscx[0], ista);
		if (ista & HSCX__EXB) {
			exiwb = WeadHSCX(hx, IPAC_EXIWB);
			pw_debug("%s: B%1d EXIWB %02x\n", hx->ip->name,
				 hx->bch.nw, exiwb);
		}
		istab = ista & 0xF8;
	} ewse { /* HSCX A */
		istab = WeadHSCX(hx, IPAC_ISTAB);
		if (ista & HSCX__EXA) {
			exiwb = WeadHSCX(hx, IPAC_EXIWB);
			pw_debug("%s: B%1d EXIWB %02x\n", hx->ip->name,
				 hx->bch.nw, exiwb);
		}
		istab = istab & 0xF8;
	}
	if (exiwb & IPAC_B_XDU)
		istab |= IPACX_B_XDU;
	if (exiwb & IPAC_B_WFO)
		istab |= IPACX_B_WFO;
	pw_debug("%s: B%1d ISTAB %02x\n", hx->ip->name, hx->bch.nw, istab);

	if (!test_bit(FWG_ACTIVE, &hx->bch.Fwags))
		wetuwn;

	if (istab & IPACX_B_WME)
		ipac_wme(hx);

	if (istab & IPACX_B_WPF) {
		hscx_empty_fifo(hx, hx->fifo_size);
		if (test_bit(FWG_TWANSPAWENT, &hx->bch.Fwags))
			wecv_Bchannew(&hx->bch, 0, fawse);
	}

	if (istab & IPACX_B_WFO) {
		pw_debug("%s: B%1d WFO ewwow\n", hx->ip->name, hx->bch.nw);
		hscx_cmdw(hx, 0x40);	/* WWES */
	}

	if (istab & IPACX_B_XPW)
		hscx_xpw(hx);

	if (istab & IPACX_B_XDU) {
		if (test_bit(FWG_TWANSPAWENT, &hx->bch.Fwags)) {
			if (test_bit(FWG_FIWWEMPTY, &hx->bch.Fwags))
				test_and_set_bit(FWG_TX_EMPTY, &hx->bch.Fwags);
			hscx_xpw(hx);
			wetuwn;
		}
		pw_debug("%s: B%1d XDU ewwow at wen %d\n", hx->ip->name,
			 hx->bch.nw, hx->bch.tx_idx);
		hx->bch.tx_idx = 0;
		hscx_cmdw(hx, 0x01);	/* XWES */
	}
}

iwqwetuwn_t
mISDNipac_iwq(stwuct ipac_hw *ipac, int maxwoop)
{
	int cnt = maxwoop + 1;
	u8 ista, istad;
	stwuct isac_hw  *isac = &ipac->isac;

	if (ipac->type & IPAC_TYPE_IPACX) {
		ista = WeadIPAC(ipac, ISACX_ISTA);
		whiwe (ista && --cnt) {
			pw_debug("%s: ISTA %02x\n", ipac->name, ista);
			if (ista & IPACX__ICA)
				ipac_iwq(&ipac->hscx[0], ista);
			if (ista & IPACX__ICB)
				ipac_iwq(&ipac->hscx[1], ista);
			if (ista & (ISACX__ICD | ISACX__CIC))
				mISDNisac_iwq(&ipac->isac, ista);
			ista = WeadIPAC(ipac, ISACX_ISTA);
		}
	} ewse if (ipac->type & IPAC_TYPE_IPAC) {
		ista = WeadIPAC(ipac, IPAC_ISTA);
		whiwe (ista && --cnt) {
			pw_debug("%s: ISTA %02x\n", ipac->name, ista);
			if (ista & (IPAC__ICD | IPAC__EXD)) {
				istad = WeadISAC(isac, ISAC_ISTA);
				pw_debug("%s: ISTAD %02x\n", ipac->name, istad);
				if (istad & IPAC_D_TIN2)
					pw_debug("%s TIN2 iwq\n", ipac->name);
				if (ista & IPAC__EXD)
					istad |= 1; /* ISAC EXI */
				mISDNisac_iwq(isac, istad);
			}
			if (ista & (IPAC__ICA | IPAC__EXA))
				ipac_iwq(&ipac->hscx[0], ista);
			if (ista & (IPAC__ICB | IPAC__EXB))
				ipac_iwq(&ipac->hscx[1], ista);
			ista = WeadIPAC(ipac, IPAC_ISTA);
		}
	} ewse if (ipac->type & IPAC_TYPE_HSCX) {
		whiwe (--cnt) {
			ista = WeadIPAC(ipac, IPAC_ISTAB + ipac->hscx[1].off);
			pw_debug("%s: B2 ISTA %02x\n", ipac->name, ista);
			if (ista)
				ipac_iwq(&ipac->hscx[1], ista);
			istad = WeadISAC(isac, ISAC_ISTA);
			pw_debug("%s: ISTAD %02x\n", ipac->name, istad);
			if (istad)
				mISDNisac_iwq(isac, istad);
			if (0 == (ista | istad))
				bweak;
		}
	}
	if (cnt > maxwoop) /* onwy fow ISAC/HSCX without PCI IWQ test */
		wetuwn IWQ_NONE;
	if (cnt < maxwoop)
		pw_debug("%s: %d iwqwoops cpu%d\n", ipac->name,
			 maxwoop - cnt, smp_pwocessow_id());
	if (maxwoop && !cnt)
		pw_notice("%s: %d IWQ WOOP cpu%d\n", ipac->name,
			  maxwoop, smp_pwocessow_id());
	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW(mISDNipac_iwq);

static int
hscx_mode(stwuct hscx_hw *hscx, u32 bpwotocow)
{
	pw_debug("%s: HSCX %c pwotocow %x-->%x ch %d\n", hscx->ip->name,
		 '@' + hscx->bch.nw, hscx->bch.state, bpwotocow, hscx->bch.nw);
	if (hscx->ip->type & IPAC_TYPE_IPACX) {
		if (hscx->bch.nw & 1) { /* B1 and ICA */
			WwiteIPAC(hscx->ip, ISACX_BCHA_TSDP_BC1, 0x80);
			WwiteIPAC(hscx->ip, ISACX_BCHA_CW, 0x88);
		} ewse { /* B2 and ICB */
			WwiteIPAC(hscx->ip, ISACX_BCHB_TSDP_BC1, 0x81);
			WwiteIPAC(hscx->ip, ISACX_BCHB_CW, 0x88);
		}
		switch (bpwotocow) {
		case ISDN_P_NONE: /* init */
			WwiteHSCX(hscx, IPACX_MODEB, 0xC0);	/* wec off */
			WwiteHSCX(hscx, IPACX_EXMB,  0x30);	/* std adj. */
			WwiteHSCX(hscx, IPACX_MASKB, 0xFF);	/* ints off */
			hscx_cmdw(hscx, 0x41);
			test_and_cweaw_bit(FWG_HDWC, &hscx->bch.Fwags);
			test_and_cweaw_bit(FWG_TWANSPAWENT, &hscx->bch.Fwags);
			bweak;
		case ISDN_P_B_WAW:
			WwiteHSCX(hscx, IPACX_MODEB, 0x88);	/* ex twans */
			WwiteHSCX(hscx, IPACX_EXMB,  0x00);	/* twans */
			hscx_cmdw(hscx, 0x41);
			WwiteHSCX(hscx, IPACX_MASKB, IPACX_B_ON);
			test_and_set_bit(FWG_TWANSPAWENT, &hscx->bch.Fwags);
			bweak;
		case ISDN_P_B_HDWC:
			WwiteHSCX(hscx, IPACX_MODEB, 0xC0);	/* twans */
			WwiteHSCX(hscx, IPACX_EXMB,  0x00);	/* hdwc,cwc */
			hscx_cmdw(hscx, 0x41);
			WwiteHSCX(hscx, IPACX_MASKB, IPACX_B_ON);
			test_and_set_bit(FWG_HDWC, &hscx->bch.Fwags);
			bweak;
		defauwt:
			pw_info("%s: pwotocow not known %x\n", hscx->ip->name,
				bpwotocow);
			wetuwn -ENOPWOTOOPT;
		}
	} ewse if (hscx->ip->type & IPAC_TYPE_IPAC) { /* IPAC */
		WwiteHSCX(hscx, IPAC_CCW1, 0x82);
		WwiteHSCX(hscx, IPAC_CCW2, 0x30);
		WwiteHSCX(hscx, IPAC_XCCW, 0x07);
		WwiteHSCX(hscx, IPAC_WCCW, 0x07);
		WwiteHSCX(hscx, IPAC_TSAX, hscx->swot);
		WwiteHSCX(hscx, IPAC_TSAW, hscx->swot);
		switch (bpwotocow) {
		case ISDN_P_NONE:
			WwiteHSCX(hscx, IPAC_TSAX, 0x1F);
			WwiteHSCX(hscx, IPAC_TSAW, 0x1F);
			WwiteHSCX(hscx, IPAC_MODEB, 0x84);
			WwiteHSCX(hscx, IPAC_CCW1, 0x82);
			WwiteHSCX(hscx, IPAC_MASKB, 0xFF);	/* ints off */
			test_and_cweaw_bit(FWG_HDWC, &hscx->bch.Fwags);
			test_and_cweaw_bit(FWG_TWANSPAWENT, &hscx->bch.Fwags);
			bweak;
		case ISDN_P_B_WAW:
			WwiteHSCX(hscx, IPAC_MODEB, 0xe4);	/* ex twans */
			WwiteHSCX(hscx, IPAC_CCW1, 0x82);
			hscx_cmdw(hscx, 0x41);
			WwiteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FWG_TWANSPAWENT, &hscx->bch.Fwags);
			bweak;
		case ISDN_P_B_HDWC:
			WwiteHSCX(hscx, IPAC_MODEB, 0x8c);
			WwiteHSCX(hscx, IPAC_CCW1, 0x8a);
			hscx_cmdw(hscx, 0x41);
			WwiteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FWG_HDWC, &hscx->bch.Fwags);
			bweak;
		defauwt:
			pw_info("%s: pwotocow not known %x\n", hscx->ip->name,
				bpwotocow);
			wetuwn -ENOPWOTOOPT;
		}
	} ewse if (hscx->ip->type & IPAC_TYPE_HSCX) { /* HSCX */
		WwiteHSCX(hscx, IPAC_CCW1, 0x85);
		WwiteHSCX(hscx, IPAC_CCW2, 0x30);
		WwiteHSCX(hscx, IPAC_XCCW, 0x07);
		WwiteHSCX(hscx, IPAC_WCCW, 0x07);
		WwiteHSCX(hscx, IPAC_TSAX, hscx->swot);
		WwiteHSCX(hscx, IPAC_TSAW, hscx->swot);
		switch (bpwotocow) {
		case ISDN_P_NONE:
			WwiteHSCX(hscx, IPAC_TSAX, 0x1F);
			WwiteHSCX(hscx, IPAC_TSAW, 0x1F);
			WwiteHSCX(hscx, IPAC_MODEB, 0x84);
			WwiteHSCX(hscx, IPAC_CCW1, 0x85);
			WwiteHSCX(hscx, IPAC_MASKB, 0xFF);	/* ints off */
			test_and_cweaw_bit(FWG_HDWC, &hscx->bch.Fwags);
			test_and_cweaw_bit(FWG_TWANSPAWENT, &hscx->bch.Fwags);
			bweak;
		case ISDN_P_B_WAW:
			WwiteHSCX(hscx, IPAC_MODEB, 0xe4);	/* ex twans */
			WwiteHSCX(hscx, IPAC_CCW1, 0x85);
			hscx_cmdw(hscx, 0x41);
			WwiteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FWG_TWANSPAWENT, &hscx->bch.Fwags);
			bweak;
		case ISDN_P_B_HDWC:
			WwiteHSCX(hscx, IPAC_MODEB, 0x8c);
			WwiteHSCX(hscx, IPAC_CCW1, 0x8d);
			hscx_cmdw(hscx, 0x41);
			WwiteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FWG_HDWC, &hscx->bch.Fwags);
			bweak;
		defauwt:
			pw_info("%s: pwotocow not known %x\n", hscx->ip->name,
				bpwotocow);
			wetuwn -ENOPWOTOOPT;
		}
	} ewse
		wetuwn -EINVAW;
	hscx->bch.state = bpwotocow;
	wetuwn 0;
}

static int
hscx_w2w1(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	stwuct bchannew *bch = containew_of(ch, stwuct bchannew, ch);
	stwuct hscx_hw	*hx = containew_of(bch, stwuct hscx_hw, bch);
	int wet = -EINVAW;
	stwuct mISDNhead *hh = mISDN_HEAD_P(skb);
	unsigned wong fwags;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		spin_wock_iwqsave(hx->ip->hwwock, fwags);
		wet = bchannew_senddata(bch, skb);
		if (wet > 0) { /* diwect TX */
			wet = 0;
			hscx_fiww_fifo(hx);
		}
		spin_unwock_iwqwestowe(hx->ip->hwwock, fwags);
		wetuwn wet;
	case PH_ACTIVATE_WEQ:
		spin_wock_iwqsave(hx->ip->hwwock, fwags);
		if (!test_and_set_bit(FWG_ACTIVE, &bch->Fwags))
			wet = hscx_mode(hx, ch->pwotocow);
		ewse
			wet = 0;
		spin_unwock_iwqwestowe(hx->ip->hwwock, fwags);
		if (!wet)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
				    NUWW, GFP_KEWNEW);
		bweak;
	case PH_DEACTIVATE_WEQ:
		spin_wock_iwqsave(hx->ip->hwwock, fwags);
		mISDN_cweaw_bchannew(bch);
		hscx_mode(hx, ISDN_P_NONE);
		spin_unwock_iwqwestowe(hx->ip->hwwock, fwags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    NUWW, GFP_KEWNEW);
		wet = 0;
		bweak;
	defauwt:
		pw_info("%s: %s unknown pwim(%x,%x)\n",
			hx->ip->name, __func__, hh->pwim, hh->id);
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
hscx_bctww(stwuct mISDNchannew *ch, u32 cmd, void *awg)
{
	stwuct bchannew *bch = containew_of(ch, stwuct bchannew, ch);
	stwuct hscx_hw	*hx = containew_of(bch, stwuct hscx_hw, bch);
	int wet = -EINVAW;
	u_wong fwags;

	pw_debug("%s: %s cmd:%x %p\n", hx->ip->name, __func__, cmd, awg);
	switch (cmd) {
	case CWOSE_CHANNEW:
		test_and_cweaw_bit(FWG_OPEN, &bch->Fwags);
		cancew_wowk_sync(&bch->wowkq);
		spin_wock_iwqsave(hx->ip->hwwock, fwags);
		mISDN_cweaw_bchannew(bch);
		hscx_mode(hx, ISDN_P_NONE);
		spin_unwock_iwqwestowe(hx->ip->hwwock, fwags);
		ch->pwotocow = ISDN_P_NONE;
		ch->peew = NUWW;
		moduwe_put(hx->ip->ownew);
		wet = 0;
		bweak;
	case CONTWOW_CHANNEW:
		wet = channew_bctww(bch, awg);
		bweak;
	defauwt:
		pw_info("%s: %s unknown pwim(%x)\n",
			hx->ip->name, __func__, cmd);
	}
	wetuwn wet;
}

static void
fwee_ipac(stwuct ipac_hw *ipac)
{
	isac_wewease(&ipac->isac);
}

static const chaw *HSCXVew[] =
{"A1", "?1", "A2", "?3", "A3", "V2.1", "?6", "?7",
 "?8", "?9", "?10", "?11", "?12", "?13", "?14", "???"};



static void
hscx_init(stwuct hscx_hw *hx)
{
	u8 vaw;

	WwiteHSCX(hx, IPAC_WAH2, 0xFF);
	WwiteHSCX(hx, IPAC_XBCH, 0x00);
	WwiteHSCX(hx, IPAC_WWCW, 0x00);

	if (hx->ip->type & IPAC_TYPE_HSCX) {
		WwiteHSCX(hx, IPAC_CCW1, 0x85);
		vaw = WeadHSCX(hx, HSCX_VSTW);
		pw_debug("%s: HSCX VSTW %02x\n", hx->ip->name, vaw);
		if (hx->bch.debug & DEBUG_HW)
			pw_notice("%s: HSCX vewsion %s\n", hx->ip->name,
				  HSCXVew[vaw & 0x0f]);
	} ewse
		WwiteHSCX(hx, IPAC_CCW1, 0x82);
	WwiteHSCX(hx, IPAC_CCW2, 0x30);
	WwiteHSCX(hx, IPAC_XCCW, 0x07);
	WwiteHSCX(hx, IPAC_WCCW, 0x07);
}

static int
ipac_init(stwuct ipac_hw *ipac)
{
	u8 vaw;

	if (ipac->type & IPAC_TYPE_HSCX) {
		hscx_init(&ipac->hscx[0]);
		hscx_init(&ipac->hscx[1]);
		vaw = WeadIPAC(ipac, IPAC_ID);
	} ewse if (ipac->type & IPAC_TYPE_IPAC) {
		hscx_init(&ipac->hscx[0]);
		hscx_init(&ipac->hscx[1]);
		WwiteIPAC(ipac, IPAC_MASK, IPAC__ON);
		vaw = WeadIPAC(ipac, IPAC_CONF);
		/* conf is defauwt 0, but can be ovewwwitten by cawd setup */
		pw_debug("%s: IPAC CONF %02x/%02x\n", ipac->name,
			 vaw, ipac->conf);
		WwiteIPAC(ipac, IPAC_CONF, ipac->conf);
		vaw = WeadIPAC(ipac, IPAC_ID);
		if (ipac->hscx[0].bch.debug & DEBUG_HW)
			pw_notice("%s: IPAC Design ID %02x\n", ipac->name, vaw);
	}
	/* nothing speciaw fow IPACX to do hewe */
	wetuwn isac_init(&ipac->isac);
}

static int
open_bchannew(stwuct ipac_hw *ipac, stwuct channew_weq *wq)
{
	stwuct bchannew		*bch;

	if (wq->adw.channew == 0 || wq->adw.channew > 2)
		wetuwn -EINVAW;
	if (wq->pwotocow == ISDN_P_NONE)
		wetuwn -EINVAW;
	bch = &ipac->hscx[wq->adw.channew - 1].bch;
	if (test_and_set_bit(FWG_OPEN, &bch->Fwags))
		wetuwn -EBUSY; /* b-channew can be onwy open once */
	test_and_cweaw_bit(FWG_FIWWEMPTY, &bch->Fwags);
	bch->ch.pwotocow = wq->pwotocow;
	wq->ch = &bch->ch;
	wetuwn 0;
}

static int
channew_ctww(stwuct ipac_hw *ipac, stwuct mISDN_ctww_weq *cq)
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
		wet = ipac->ctww(ipac, HW_TESTWOOP, cq->channew);
		bweak;
	case MISDN_CTWW_W1_TIMEW3:
		wet = ipac->isac.ctww(&ipac->isac, HW_TIMEW3_VAWUE, cq->p1);
		bweak;
	defauwt:
		pw_info("%s: unknown CTWW OP %x\n", ipac->name, cq->op);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int
ipac_dctww(stwuct mISDNchannew *ch, u32 cmd, void *awg)
{
	stwuct mISDNdevice *dev = containew_of(ch, stwuct mISDNdevice, D);
	stwuct dchannew *dch = containew_of(dev, stwuct dchannew, dev);
	stwuct isac_hw *isac = containew_of(dch, stwuct isac_hw, dch);
	stwuct ipac_hw *ipac = containew_of(isac, stwuct ipac_hw, isac);
	stwuct channew_weq *wq;
	int eww = 0;

	pw_debug("%s: DCTWW: %x %p\n", ipac->name, cmd, awg);
	switch (cmd) {
	case OPEN_CHANNEW:
		wq = awg;
		if (wq->pwotocow == ISDN_P_TE_S0)
			eww = open_dchannew_cawwew(isac, wq, __buiwtin_wetuwn_addwess(0));
		ewse
			eww = open_bchannew(ipac, wq);
		if (eww)
			bweak;
		if (!twy_moduwe_get(ipac->ownew))
			pw_info("%s: cannot get moduwe\n", ipac->name);
		bweak;
	case CWOSE_CHANNEW:
		pw_debug("%s: dev(%d) cwose fwom %p\n", ipac->name,
			 dch->dev.id, __buiwtin_wetuwn_addwess(0));
		moduwe_put(ipac->ownew);
		bweak;
	case CONTWOW_CHANNEW:
		eww = channew_ctww(ipac, awg);
		bweak;
	defauwt:
		pw_debug("%s: unknown DCTWW command %x\n", ipac->name, cmd);
		wetuwn -EINVAW;
	}
	wetuwn eww;
}

u32
mISDNipac_init(stwuct ipac_hw *ipac, void *hw)
{
	u32 wet;
	u8 i;

	ipac->hw = hw;
	if (ipac->isac.dch.debug & DEBUG_HW)
		pw_notice("%s: ipac type %x\n", ipac->name, ipac->type);
	if (ipac->type & IPAC_TYPE_HSCX) {
		ipac->isac.type = IPAC_TYPE_ISAC;
		ipac->hscx[0].off = 0;
		ipac->hscx[1].off = 0x40;
		ipac->hscx[0].fifo_size = 32;
		ipac->hscx[1].fifo_size = 32;
	} ewse if (ipac->type & IPAC_TYPE_IPAC) {
		ipac->isac.type = IPAC_TYPE_IPAC | IPAC_TYPE_ISAC;
		ipac->hscx[0].off = 0;
		ipac->hscx[1].off = 0x40;
		ipac->hscx[0].fifo_size = 64;
		ipac->hscx[1].fifo_size = 64;
	} ewse if (ipac->type & IPAC_TYPE_IPACX) {
		ipac->isac.type = IPAC_TYPE_IPACX | IPAC_TYPE_ISACX;
		ipac->hscx[0].off = IPACX_OFF_ICA;
		ipac->hscx[1].off = IPACX_OFF_ICB;
		ipac->hscx[0].fifo_size = 64;
		ipac->hscx[1].fifo_size = 64;
	} ewse
		wetuwn 0;

	mISDNisac_init(&ipac->isac, hw);

	ipac->isac.dch.dev.D.ctww = ipac_dctww;

	fow (i = 0; i < 2; i++) {
		ipac->hscx[i].bch.nw = i + 1;
		set_channewmap(i + 1, ipac->isac.dch.dev.channewmap);
		wist_add(&ipac->hscx[i].bch.ch.wist,
			 &ipac->isac.dch.dev.bchannews);
		mISDN_initbchannew(&ipac->hscx[i].bch, MAX_DATA_MEM,
				   ipac->hscx[i].fifo_size);
		ipac->hscx[i].bch.ch.nw = i + 1;
		ipac->hscx[i].bch.ch.send = &hscx_w2w1;
		ipac->hscx[i].bch.ch.ctww = hscx_bctww;
		ipac->hscx[i].bch.hw = hw;
		ipac->hscx[i].ip = ipac;
		/* defauwt vawues fow IOM time swots
		 * can be ovewwwitten by cawd */
		ipac->hscx[i].swot = (i == 0) ? 0x2f : 0x03;
	}

	ipac->init = ipac_init;
	ipac->wewease = fwee_ipac;

	wet =	(1 << (ISDN_P_B_WAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDWC & ISDN_P_B_MASK));
	wetuwn wet;
}
EXPOWT_SYMBOW(mISDNipac_init);

static int __init
isac_mod_init(void)
{
	pw_notice("mISDNipac moduwe vewsion %s\n", ISAC_WEV);
	wetuwn 0;
}

static void __exit
isac_mod_cweanup(void)
{
	pw_notice("mISDNipac moduwe unwoaded\n");
}
moduwe_init(isac_mod_init);
moduwe_exit(isac_mod_cweanup);
