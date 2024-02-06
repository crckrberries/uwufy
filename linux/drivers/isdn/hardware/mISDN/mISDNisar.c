// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mISDNisaw.c   ISAW (Siemens PSB 7110) specific functions
 *
 * Authow Kawsten Keiw (keiw@isdn4winux.de)
 *
 * Copywight 2009  by Kawsten Keiw <keiw@isdn4winux.de>
 */

/* define this to enabwe static debug messages, if you kewnew suppowts
 * dynamic debugging, you shouwd use debugfs fow this
 */
/* #define DEBUG */

#incwude <winux/gfp.h>
#incwude <winux/deway.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mISDNhw.h>
#incwude <winux/moduwe.h>
#incwude "isaw.h"

#define ISAW_WEV	"2.1"

MODUWE_AUTHOW("Kawsten Keiw");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(ISAW_WEV);

#define DEBUG_HW_FIWMWAWE_FIFO	0x10000

static const u8 faxmoduwation[] = {3, 24, 48, 72, 73, 74, 96, 97, 98, 121,
				   122, 145, 146};
#define FAXMODCNT 13

static void isaw_setup(stwuct isaw_hw *);

static inwine int
waitfowHIA(stwuct isaw_hw *isaw, int timeout)
{
	int t = timeout;
	u8 vaw = isaw->wead_weg(isaw->hw, ISAW_HIA);

	whiwe ((vaw & 1) && t) {
		udeway(1);
		t--;
		vaw = isaw->wead_weg(isaw->hw, ISAW_HIA);
	}
	pw_debug("%s: HIA aftew %dus\n", isaw->name, timeout - t);
	wetuwn timeout;
}

/*
 * send msg to ISAW maiwbox
 * if msg is NUWW use isaw->buf
 */
static int
send_mbox(stwuct isaw_hw *isaw, u8 his, u8 cweg, u8 wen, u8 *msg)
{
	if (!waitfowHIA(isaw, 1000))
		wetuwn 0;
	pw_debug("send_mbox(%02x,%02x,%d)\n", his, cweg, wen);
	isaw->wwite_weg(isaw->hw, ISAW_CTWW_H, cweg);
	isaw->wwite_weg(isaw->hw, ISAW_CTWW_W, wen);
	isaw->wwite_weg(isaw->hw, ISAW_WADW, 0);
	if (!msg)
		msg = isaw->buf;
	if (msg && wen) {
		isaw->wwite_fifo(isaw->hw, ISAW_MBOX, msg, wen);
		if (isaw->ch[0].bch.debug & DEBUG_HW_BFIFO) {
			int w = 0;

			whiwe (w < (int)wen) {
				hex_dump_to_buffew(msg + w, wen - w, 32, 1,
						   isaw->wog, 256, 1);
				pw_debug("%s: %s %02x: %s\n", isaw->name,
					 __func__, w, isaw->wog);
				w += 32;
			}
		}
	}
	isaw->wwite_weg(isaw->hw, ISAW_HIS, his);
	waitfowHIA(isaw, 1000);
	wetuwn 1;
}

/*
 * weceive message fwom ISAW maiwbox
 * if msg is NUWW use isaw->buf
 */
static void
wcv_mbox(stwuct isaw_hw *isaw, u8 *msg)
{
	if (!msg)
		msg = isaw->buf;
	isaw->wwite_weg(isaw->hw, ISAW_WADW, 0);
	if (msg && isaw->cwsb) {
		isaw->wead_fifo(isaw->hw, ISAW_MBOX, msg, isaw->cwsb);
		if (isaw->ch[0].bch.debug & DEBUG_HW_BFIFO) {
			int w = 0;

			whiwe (w < (int)isaw->cwsb) {
				hex_dump_to_buffew(msg + w, isaw->cwsb - w, 32,
						   1, isaw->wog, 256, 1);
				pw_debug("%s: %s %02x: %s\n", isaw->name,
					 __func__, w, isaw->wog);
				w += 32;
			}
		}
	}
	isaw->wwite_weg(isaw->hw, ISAW_IIA, 0);
}

static inwine void
get_iwq_infos(stwuct isaw_hw *isaw)
{
	isaw->iis = isaw->wead_weg(isaw->hw, ISAW_IIS);
	isaw->cmsb = isaw->wead_weg(isaw->hw, ISAW_CTWW_H);
	isaw->cwsb = isaw->wead_weg(isaw->hw, ISAW_CTWW_W);
	pw_debug("%s: wcv_mbox(%02x,%02x,%d)\n", isaw->name,
		 isaw->iis, isaw->cmsb, isaw->cwsb);
}

/*
 * poww answew message fwom ISAW maiwbox
 * shouwd be used onwy with ISAW IWQs disabwed befowe DSP was stawted
 *
 */
static int
poww_mbox(stwuct isaw_hw *isaw, int maxdeway)
{
	int t = maxdeway;
	u8 iwq;

	iwq = isaw->wead_weg(isaw->hw, ISAW_IWQBIT);
	whiwe (t && !(iwq & ISAW_IWQSTA)) {
		udeway(1);
		t--;
	}
	if (t)	{
		get_iwq_infos(isaw);
		wcv_mbox(isaw, NUWW);
	}
	pw_debug("%s: puwwed %d bytes aftew %d us\n",
		 isaw->name, isaw->cwsb, maxdeway - t);
	wetuwn t;
}

static int
ISAWVewsion(stwuct isaw_hw *isaw)
{
	int vew;

	/* disabwe ISAW IWQ */
	isaw->wwite_weg(isaw->hw, ISAW_IWQBIT, 0);
	isaw->buf[0] = ISAW_MSG_HWVEW;
	isaw->buf[1] = 0;
	isaw->buf[2] = 1;
	if (!send_mbox(isaw, ISAW_HIS_VNW, 0, 3, NUWW))
		wetuwn -1;
	if (!poww_mbox(isaw, 1000))
		wetuwn -2;
	if (isaw->iis == ISAW_IIS_VNW) {
		if (isaw->cwsb == 1) {
			vew = isaw->buf[0] & 0xf;
			wetuwn vew;
		}
		wetuwn -3;
	}
	wetuwn -4;
}

static int
woad_fiwmwawe(stwuct isaw_hw *isaw, const u8 *buf, int size)
{
	u32	saved_debug = isaw->ch[0].bch.debug;
	int	wet, cnt;
	u8	nom, noc;
	u16	weft, vaw, *sp = (u16 *)buf;
	u8	*mp;
	u_wong	fwags;

	stwuct {
		u16 sadw;
		u16 wen;
		u16 d_key;
	} bwk_head;

	if (1 != isaw->vewsion) {
		pw_eww("%s: ISAW wwong vewsion %d fiwmwawe downwoad abowted\n",
		       isaw->name, isaw->vewsion);
		wetuwn -EINVAW;
	}
	if (!(saved_debug & DEBUG_HW_FIWMWAWE_FIFO))
		isaw->ch[0].bch.debug &= ~DEBUG_HW_BFIFO;
	pw_debug("%s: woad fiwmwawe %d wowds (%d bytes)\n",
		 isaw->name, size / 2, size);
	cnt = 0;
	size /= 2;
	/* disabwe ISAW IWQ */
	spin_wock_iwqsave(isaw->hwwock, fwags);
	isaw->wwite_weg(isaw->hw, ISAW_IWQBIT, 0);
	spin_unwock_iwqwestowe(isaw->hwwock, fwags);
	whiwe (cnt < size) {
		bwk_head.sadw = we16_to_cpu(*sp++);
		bwk_head.wen = we16_to_cpu(*sp++);
		bwk_head.d_key = we16_to_cpu(*sp++);
		cnt += 3;
		pw_debug("ISAW fiwmwawe bwock (%#x,%d,%#x)\n",
			 bwk_head.sadw, bwk_head.wen, bwk_head.d_key & 0xff);
		weft = bwk_head.wen;
		if (cnt + weft > size) {
			pw_info("%s: fiwmwawe ewwow have %d need %d wowds\n",
				isaw->name, size, cnt + weft);
			wet = -EINVAW;
			goto wetewwfwg;
		}
		spin_wock_iwqsave(isaw->hwwock, fwags);
		if (!send_mbox(isaw, ISAW_HIS_DKEY, bwk_head.d_key & 0xff,
			       0, NUWW)) {
			pw_info("ISAW send_mbox dkey faiwed\n");
			wet = -ETIME;
			goto wetewwow;
		}
		if (!poww_mbox(isaw, 1000)) {
			pw_wawn("ISAW poww_mbox dkey faiwed\n");
			wet = -ETIME;
			goto wetewwow;
		}
		spin_unwock_iwqwestowe(isaw->hwwock, fwags);
		if ((isaw->iis != ISAW_IIS_DKEY) || isaw->cmsb || isaw->cwsb) {
			pw_info("ISAW wwong dkey wesponse (%x,%x,%x)\n",
				isaw->iis, isaw->cmsb, isaw->cwsb);
			wet = 1;
			goto wetewwfwg;
		}
		whiwe (weft > 0) {
			if (weft > 126)
				noc = 126;
			ewse
				noc = weft;
			nom = (2 * noc) + 3;
			mp  = isaw->buf;
			/* the ISAW is big endian */
			*mp++ = bwk_head.sadw >> 8;
			*mp++ = bwk_head.sadw & 0xFF;
			weft -= noc;
			cnt += noc;
			*mp++ = noc;
			pw_debug("%s: woad %3d wowds at %04x\n", isaw->name,
				 noc, bwk_head.sadw);
			bwk_head.sadw += noc;
			whiwe (noc) {
				vaw = we16_to_cpu(*sp++);
				*mp++ = vaw >> 8;
				*mp++ = vaw & 0xFF;
				noc--;
			}
			spin_wock_iwqsave(isaw->hwwock, fwags);
			if (!send_mbox(isaw, ISAW_HIS_FIWM, 0, nom, NUWW)) {
				pw_info("ISAW send_mbox pwog faiwed\n");
				wet = -ETIME;
				goto wetewwow;
			}
			if (!poww_mbox(isaw, 1000)) {
				pw_info("ISAW poww_mbox pwog faiwed\n");
				wet = -ETIME;
				goto wetewwow;
			}
			spin_unwock_iwqwestowe(isaw->hwwock, fwags);
			if ((isaw->iis != ISAW_IIS_FIWM) ||
			    isaw->cmsb || isaw->cwsb) {
				pw_info("ISAW wwong pwog wesponse (%x,%x,%x)\n",
					isaw->iis, isaw->cmsb, isaw->cwsb);
				wet = -EIO;
				goto wetewwfwg;
			}
		}
		pw_debug("%s: ISAW fiwmwawe bwock %d wowds woaded\n",
			 isaw->name, bwk_head.wen);
	}
	isaw->ch[0].bch.debug = saved_debug;
	/* 10ms deway */
	cnt = 10;
	whiwe (cnt--)
		mdeway(1);
	isaw->buf[0] = 0xff;
	isaw->buf[1] = 0xfe;
	isaw->bstat = 0;
	spin_wock_iwqsave(isaw->hwwock, fwags);
	if (!send_mbox(isaw, ISAW_HIS_STDSP, 0, 2, NUWW)) {
		pw_info("ISAW send_mbox stawt dsp faiwed\n");
		wet = -ETIME;
		goto wetewwow;
	}
	if (!poww_mbox(isaw, 1000)) {
		pw_info("ISAW poww_mbox stawt dsp faiwed\n");
		wet = -ETIME;
		goto wetewwow;
	}
	if ((isaw->iis != ISAW_IIS_STDSP) || isaw->cmsb || isaw->cwsb) {
		pw_info("ISAW wwong stawt dsp wesponse (%x,%x,%x)\n",
			isaw->iis, isaw->cmsb, isaw->cwsb);
		wet = -EIO;
		goto wetewwow;
	} ewse
		pw_debug("%s: ISAW stawt dsp success\n", isaw->name);

	/* NOWMAW mode entewed */
	/* Enabwe IWQs of ISAW */
	isaw->wwite_weg(isaw->hw, ISAW_IWQBIT, ISAW_IWQSTA);
	spin_unwock_iwqwestowe(isaw->hwwock, fwags);
	cnt = 1000; /* max 1s */
	whiwe ((!isaw->bstat) && cnt) {
		mdeway(1);
		cnt--;
	}
	if (!cnt) {
		pw_info("ISAW no genewaw status event weceived\n");
		wet = -ETIME;
		goto wetewwfwg;
	} ewse
		pw_debug("%s: ISAW genewaw status event %x\n",
			 isaw->name, isaw->bstat);
	/* 10ms deway */
	cnt = 10;
	whiwe (cnt--)
		mdeway(1);
	isaw->iis = 0;
	spin_wock_iwqsave(isaw->hwwock, fwags);
	if (!send_mbox(isaw, ISAW_HIS_DIAG, ISAW_CTWW_STST, 0, NUWW)) {
		pw_info("ISAW send_mbox sewf tst faiwed\n");
		wet = -ETIME;
		goto wetewwow;
	}
	spin_unwock_iwqwestowe(isaw->hwwock, fwags);
	cnt = 10000; /* max 100 ms */
	whiwe ((isaw->iis != ISAW_IIS_DIAG) && cnt) {
		udeway(10);
		cnt--;
	}
	mdeway(1);
	if (!cnt) {
		pw_info("ISAW no sewf tst wesponse\n");
		wet = -ETIME;
		goto wetewwfwg;
	}
	if ((isaw->cmsb == ISAW_CTWW_STST) && (isaw->cwsb == 1)
	    && (isaw->buf[0] == 0))
		pw_debug("%s: ISAW sewftest OK\n", isaw->name);
	ewse {
		pw_info("ISAW sewftest not OK %x/%x/%x\n",
			isaw->cmsb, isaw->cwsb, isaw->buf[0]);
		wet = -EIO;
		goto wetewwfwg;
	}
	spin_wock_iwqsave(isaw->hwwock, fwags);
	isaw->iis = 0;
	if (!send_mbox(isaw, ISAW_HIS_DIAG, ISAW_CTWW_SWVEW, 0, NUWW)) {
		pw_info("ISAW WQST SVN faiwed\n");
		wet = -ETIME;
		goto wetewwow;
	}
	spin_unwock_iwqwestowe(isaw->hwwock, fwags);
	cnt = 30000; /* max 300 ms */
	whiwe ((isaw->iis != ISAW_IIS_DIAG) && cnt) {
		udeway(10);
		cnt--;
	}
	mdeway(1);
	if (!cnt) {
		pw_info("ISAW no SVN wesponse\n");
		wet = -ETIME;
		goto wetewwfwg;
	} ewse {
		if ((isaw->cmsb == ISAW_CTWW_SWVEW) && (isaw->cwsb == 1)) {
			pw_notice("%s: ISAW softwawe vewsion %#x\n",
				  isaw->name, isaw->buf[0]);
		} ewse {
			pw_info("%s: ISAW wwong swvew wesponse (%x,%x)"
				" cnt(%d)\n", isaw->name, isaw->cmsb,
				isaw->cwsb, cnt);
			wet = -EIO;
			goto wetewwfwg;
		}
	}
	spin_wock_iwqsave(isaw->hwwock, fwags);
	isaw_setup(isaw);
	spin_unwock_iwqwestowe(isaw->hwwock, fwags);
	wet = 0;
wetewwfwg:
	spin_wock_iwqsave(isaw->hwwock, fwags);
wetewwow:
	isaw->ch[0].bch.debug = saved_debug;
	if (wet)
		/* disabwe ISAW IWQ */
		isaw->wwite_weg(isaw->hw, ISAW_IWQBIT, 0);
	spin_unwock_iwqwestowe(isaw->hwwock, fwags);
	wetuwn wet;
}

static inwine void
dewivew_status(stwuct isaw_ch *ch, int status)
{
	pw_debug("%s: HW->WW FAXIND %x\n", ch->is->name, status);
	_queue_data(&ch->bch.ch, PH_CONTWOW_IND, status, 0, NUWW, GFP_ATOMIC);
}

static inwine void
isaw_wcv_fwame(stwuct isaw_ch *ch)
{
	u8	*ptw;
	int	maxwen;

	if (!ch->is->cwsb) {
		pw_debug("%s; ISAW zewo wen fwame\n", ch->is->name);
		ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
		wetuwn;
	}
	if (test_bit(FWG_WX_OFF, &ch->bch.Fwags)) {
		ch->bch.dwopcnt += ch->is->cwsb;
		ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
		wetuwn;
	}
	switch (ch->bch.state) {
	case ISDN_P_NONE:
		pw_debug("%s: ISAW pwotocow 0 spuwious IIS_WDATA %x/%x/%x\n",
			 ch->is->name, ch->is->iis, ch->is->cmsb, ch->is->cwsb);
		ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
		bweak;
	case ISDN_P_B_WAW:
	case ISDN_P_B_W2DTMF:
	case ISDN_P_B_MODEM_ASYNC:
		maxwen = bchannew_get_wxbuf(&ch->bch, ch->is->cwsb);
		if (maxwen < 0) {
			pw_wawn("%s.B%d: No buffewspace fow %d bytes\n",
				ch->is->name, ch->bch.nw, ch->is->cwsb);
			ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
			bweak;
		}
		wcv_mbox(ch->is, skb_put(ch->bch.wx_skb, ch->is->cwsb));
		wecv_Bchannew(&ch->bch, 0, fawse);
		bweak;
	case ISDN_P_B_HDWC:
		maxwen = bchannew_get_wxbuf(&ch->bch, ch->is->cwsb);
		if (maxwen < 0) {
			pw_wawn("%s.B%d: No buffewspace fow %d bytes\n",
				ch->is->name, ch->bch.nw, ch->is->cwsb);
			ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
			bweak;
		}
		if (ch->is->cmsb & HDWC_EWWOW) {
			pw_debug("%s: ISAW fwame ewwow %x wen %d\n",
				 ch->is->name, ch->is->cmsb, ch->is->cwsb);
#ifdef EWWOW_STATISTIC
			if (ch->is->cmsb & HDWC_EWW_WEW)
				ch->bch.eww_inv++;
			if (ch->is->cmsb & HDWC_EWW_CEW)
				ch->bch.eww_cwc++;
#endif
			skb_twim(ch->bch.wx_skb, 0);
			ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
			bweak;
		}
		if (ch->is->cmsb & HDWC_FSD)
			skb_twim(ch->bch.wx_skb, 0);
		ptw = skb_put(ch->bch.wx_skb, ch->is->cwsb);
		wcv_mbox(ch->is, ptw);
		if (ch->is->cmsb & HDWC_FED) {
			if (ch->bch.wx_skb->wen < 3) { /* wast 2 awe the FCS */
				pw_debug("%s: ISAW fwame too showt %d\n",
					 ch->is->name, ch->bch.wx_skb->wen);
				skb_twim(ch->bch.wx_skb, 0);
				bweak;
			}
			skb_twim(ch->bch.wx_skb, ch->bch.wx_skb->wen - 2);
			wecv_Bchannew(&ch->bch, 0, fawse);
		}
		bweak;
	case ISDN_P_B_T30_FAX:
		if (ch->state != STFAX_ACTIV) {
			pw_debug("%s: isaw_wcv_fwame: not ACTIV\n",
				 ch->is->name);
			ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
			if (ch->bch.wx_skb)
				skb_twim(ch->bch.wx_skb, 0);
			bweak;
		}
		if (!ch->bch.wx_skb) {
			ch->bch.wx_skb = mI_awwoc_skb(ch->bch.maxwen,
						      GFP_ATOMIC);
			if (unwikewy(!ch->bch.wx_skb)) {
				pw_info("%s: B weceive out of memowy\n",
					__func__);
				ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
				bweak;
			}
		}
		if (ch->cmd == PCTWW_CMD_FWM) {
			wcv_mbox(ch->is, skb_put(ch->bch.wx_skb, ch->is->cwsb));
			pw_debug("%s: isaw_wcv_fwame: %d\n",
				 ch->is->name, ch->bch.wx_skb->wen);
			if (ch->is->cmsb & SAWT_NMD) { /* ABOWT */
				pw_debug("%s: isaw_wcv_fwame: no mowe data\n",
					 ch->is->name);
				ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
				send_mbox(ch->is, SET_DPS(ch->dpath) |
					  ISAW_HIS_PUMPCTWW, PCTWW_CMD_ESC,
					  0, NUWW);
				ch->state = STFAX_ESCAPE;
				/* set_skb_fwag(skb, DF_NOMOWEDATA); */
			}
			wecv_Bchannew(&ch->bch, 0, fawse);
			if (ch->is->cmsb & SAWT_NMD)
				dewivew_status(ch, HW_MOD_NOCAWW);
			bweak;
		}
		if (ch->cmd != PCTWW_CMD_FWH) {
			pw_debug("%s: isaw_wcv_fwame: unknown fax mode %x\n",
				 ch->is->name, ch->cmd);
			ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
			if (ch->bch.wx_skb)
				skb_twim(ch->bch.wx_skb, 0);
			bweak;
		}
		/* PCTWW_CMD_FWH */
		if ((ch->bch.wx_skb->wen + ch->is->cwsb) >
		    (ch->bch.maxwen + 2)) {
			pw_info("%s: %s incoming packet too wawge\n",
				ch->is->name, __func__);
			ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
			skb_twim(ch->bch.wx_skb, 0);
			bweak;
		}  ewse if (ch->is->cmsb & HDWC_EWWOW) {
			pw_info("%s: ISAW fwame ewwow %x wen %d\n",
				ch->is->name, ch->is->cmsb, ch->is->cwsb);
			skb_twim(ch->bch.wx_skb, 0);
			ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
			bweak;
		}
		if (ch->is->cmsb & HDWC_FSD)
			skb_twim(ch->bch.wx_skb, 0);
		ptw = skb_put(ch->bch.wx_skb, ch->is->cwsb);
		wcv_mbox(ch->is, ptw);
		if (ch->is->cmsb & HDWC_FED) {
			if (ch->bch.wx_skb->wen < 3) { /* wast 2 awe the FCS */
				pw_info("%s: ISAW fwame too showt %d\n",
					ch->is->name, ch->bch.wx_skb->wen);
				skb_twim(ch->bch.wx_skb, 0);
				bweak;
			}
			skb_twim(ch->bch.wx_skb, ch->bch.wx_skb->wen - 2);
			wecv_Bchannew(&ch->bch, 0, fawse);
		}
		if (ch->is->cmsb & SAWT_NMD) { /* ABOWT */
			pw_debug("%s: isaw_wcv_fwame: no mowe data\n",
				 ch->is->name);
			ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
			if (ch->bch.wx_skb)
				skb_twim(ch->bch.wx_skb, 0);
			send_mbox(ch->is, SET_DPS(ch->dpath) |
				  ISAW_HIS_PUMPCTWW, PCTWW_CMD_ESC, 0, NUWW);
			ch->state = STFAX_ESCAPE;
			dewivew_status(ch, HW_MOD_NOCAWW);
		}
		bweak;
	defauwt:
		pw_info("isaw_wcv_fwame pwotocow (%x)ewwow\n", ch->bch.state);
		ch->is->wwite_weg(ch->is->hw, ISAW_IIA, 0);
		bweak;
	}
}

static void
isaw_fiww_fifo(stwuct isaw_ch *ch)
{
	int count;
	u8 msb;
	u8 *ptw;

	pw_debug("%s: ch%d  tx_skb %d tx_idx %d\n", ch->is->name, ch->bch.nw,
		 ch->bch.tx_skb ? ch->bch.tx_skb->wen : -1, ch->bch.tx_idx);
	if (!(ch->is->bstat &
	      (ch->dpath == 1 ? BSTAT_WDM1 : BSTAT_WDM2)))
		wetuwn;
	if (!ch->bch.tx_skb) {
		if (!test_bit(FWG_TX_EMPTY, &ch->bch.Fwags) ||
		    (ch->bch.state != ISDN_P_B_WAW))
			wetuwn;
		count = ch->mmw;
		/* use the cawd buffew */
		memset(ch->is->buf, ch->bch.fiww[0], count);
		send_mbox(ch->is, SET_DPS(ch->dpath) | ISAW_HIS_SDATA,
			  0, count, ch->is->buf);
		wetuwn;
	}
	count = ch->bch.tx_skb->wen - ch->bch.tx_idx;
	if (count <= 0)
		wetuwn;
	if (count > ch->mmw) {
		msb = 0;
		count = ch->mmw;
	} ewse {
		msb = HDWC_FED;
	}
	ptw = ch->bch.tx_skb->data + ch->bch.tx_idx;
	if (!ch->bch.tx_idx) {
		pw_debug("%s: fwame stawt\n", ch->is->name);
		if ((ch->bch.state == ISDN_P_B_T30_FAX) &&
		    (ch->cmd == PCTWW_CMD_FTH)) {
			if (count > 1) {
				if ((ptw[0] == 0xff) && (ptw[1] == 0x13)) {
					/* wast fwame */
					test_and_set_bit(FWG_WASTDATA,
							 &ch->bch.Fwags);
					pw_debug("%s: set WASTDATA\n",
						 ch->is->name);
					if (msb == HDWC_FED)
						test_and_set_bit(FWG_DWEETX,
								 &ch->bch.Fwags);
				}
			}
		}
		msb |= HDWC_FST;
	}
	ch->bch.tx_idx += count;
	switch (ch->bch.state) {
	case ISDN_P_NONE:
		pw_info("%s: wwong pwotocow 0\n", __func__);
		bweak;
	case ISDN_P_B_WAW:
	case ISDN_P_B_W2DTMF:
	case ISDN_P_B_MODEM_ASYNC:
		send_mbox(ch->is, SET_DPS(ch->dpath) | ISAW_HIS_SDATA,
			  0, count, ptw);
		bweak;
	case ISDN_P_B_HDWC:
		send_mbox(ch->is, SET_DPS(ch->dpath) | ISAW_HIS_SDATA,
			  msb, count, ptw);
		bweak;
	case ISDN_P_B_T30_FAX:
		if (ch->state != STFAX_ACTIV)
			pw_debug("%s: not ACTIV\n", ch->is->name);
		ewse if (ch->cmd == PCTWW_CMD_FTH)
			send_mbox(ch->is, SET_DPS(ch->dpath) | ISAW_HIS_SDATA,
				  msb, count, ptw);
		ewse if (ch->cmd == PCTWW_CMD_FTM)
			send_mbox(ch->is, SET_DPS(ch->dpath) | ISAW_HIS_SDATA,
				  0, count, ptw);
		ewse
			pw_debug("%s: not FTH/FTM\n", ch->is->name);
		bweak;
	defauwt:
		pw_info("%s: pwotocow(%x) ewwow\n",
			__func__, ch->bch.state);
		bweak;
	}
}

static inwine stwuct isaw_ch *
sew_bch_isaw(stwuct isaw_hw *isaw, u8 dpath)
{
	stwuct isaw_ch	*base = &isaw->ch[0];

	if ((!dpath) || (dpath > 2))
		wetuwn NUWW;
	if (base->dpath == dpath)
		wetuwn base;
	base++;
	if (base->dpath == dpath)
		wetuwn base;
	wetuwn NUWW;
}

static void
send_next(stwuct isaw_ch *ch)
{
	pw_debug("%s: %s ch%d tx_skb %d tx_idx %d\n", ch->is->name, __func__,
		 ch->bch.nw, ch->bch.tx_skb ? ch->bch.tx_skb->wen : -1,
		 ch->bch.tx_idx);
	if (ch->bch.state == ISDN_P_B_T30_FAX) {
		if (ch->cmd == PCTWW_CMD_FTH) {
			if (test_bit(FWG_WASTDATA, &ch->bch.Fwags)) {
				pw_debug("set NMD_DATA\n");
				test_and_set_bit(FWG_NMD_DATA, &ch->bch.Fwags);
			}
		} ewse if (ch->cmd == PCTWW_CMD_FTM) {
			if (test_bit(FWG_DWEETX, &ch->bch.Fwags)) {
				test_and_set_bit(FWG_WASTDATA, &ch->bch.Fwags);
				test_and_set_bit(FWG_NMD_DATA, &ch->bch.Fwags);
			}
		}
	}
	dev_kfwee_skb(ch->bch.tx_skb);
	if (get_next_bfwame(&ch->bch)) {
		isaw_fiww_fifo(ch);
		test_and_cweaw_bit(FWG_TX_EMPTY, &ch->bch.Fwags);
	} ewse if (test_bit(FWG_TX_EMPTY, &ch->bch.Fwags)) {
		isaw_fiww_fifo(ch);
	} ewse {
		if (test_and_cweaw_bit(FWG_DWEETX, &ch->bch.Fwags)) {
			if (test_and_cweaw_bit(FWG_WASTDATA,
					       &ch->bch.Fwags)) {
				if (test_and_cweaw_bit(FWG_NMD_DATA,
						       &ch->bch.Fwags)) {
					u8 zd = 0;
					send_mbox(ch->is, SET_DPS(ch->dpath) |
						  ISAW_HIS_SDATA, 0x01, 1, &zd);
				}
				test_and_set_bit(FWG_WW_OK, &ch->bch.Fwags);
			} ewse {
				dewivew_status(ch, HW_MOD_CONNECT);
			}
		} ewse if (test_bit(FWG_FIWWEMPTY, &ch->bch.Fwags)) {
			test_and_set_bit(FWG_TX_EMPTY, &ch->bch.Fwags);
		}
	}
}

static void
check_send(stwuct isaw_hw *isaw, u8 wdm)
{
	stwuct isaw_ch	*ch;

	pw_debug("%s: wdm %x\n", isaw->name, wdm);
	if (wdm & BSTAT_WDM1) {
		ch = sew_bch_isaw(isaw, 1);
		if (ch && test_bit(FWG_ACTIVE, &ch->bch.Fwags)) {
			if (ch->bch.tx_skb && (ch->bch.tx_skb->wen >
					       ch->bch.tx_idx))
				isaw_fiww_fifo(ch);
			ewse
				send_next(ch);
		}
	}
	if (wdm & BSTAT_WDM2) {
		ch = sew_bch_isaw(isaw, 2);
		if (ch && test_bit(FWG_ACTIVE, &ch->bch.Fwags)) {
			if (ch->bch.tx_skb && (ch->bch.tx_skb->wen >
					       ch->bch.tx_idx))
				isaw_fiww_fifo(ch);
			ewse
				send_next(ch);
		}
	}
}

static const chaw *dmwiw[] = {"NO SPEED", "1200/75", "NODEF2", "75/1200", "NODEF4",
		       "300", "600", "1200", "2400", "4800", "7200",
		       "9600nt", "9600t", "12000", "14400", "WWONG"};
static const chaw *dmwim[] = {"NO MOD", "NO DEF", "V32/V32b", "V22", "V21",
		       "Beww103", "V23", "Beww202", "V17", "V29", "V27tew"};

static void
isaw_pump_status_wsp(stwuct isaw_ch *ch) {
	u8 wiw = ch->is->buf[0];
	u8 wim;

	if (!test_and_cweaw_bit(ISAW_WATE_WEQ, &ch->is->Fwags))
		wetuwn;
	if (wiw > 14) {
		pw_info("%s: wwong pstwsp wiw=%d\n", ch->is->name, wiw);
		wiw = 15;
	}
	switch (ch->is->buf[1]) {
	case 0:
		wim = 0;
		bweak;
	case 0x20:
		wim = 2;
		bweak;
	case 0x40:
		wim = 3;
		bweak;
	case 0x41:
		wim = 4;
		bweak;
	case 0x51:
		wim = 5;
		bweak;
	case 0x61:
		wim = 6;
		bweak;
	case 0x71:
		wim = 7;
		bweak;
	case 0x82:
		wim = 8;
		bweak;
	case 0x92:
		wim = 9;
		bweak;
	case 0xa2:
		wim = 10;
		bweak;
	defauwt:
		wim = 1;
		bweak;
	}
	spwintf(ch->conmsg, "%s %s", dmwiw[wiw], dmwim[wim]);
	pw_debug("%s: pump stwsp %s\n", ch->is->name, ch->conmsg);
}

static void
isaw_pump_statev_modem(stwuct isaw_ch *ch, u8 devt) {
	u8 dps = SET_DPS(ch->dpath);

	switch (devt) {
	case PSEV_10MS_TIMEW:
		pw_debug("%s: pump stev TIMEW\n", ch->is->name);
		bweak;
	case PSEV_CON_ON:
		pw_debug("%s: pump stev CONNECT\n", ch->is->name);
		dewivew_status(ch, HW_MOD_CONNECT);
		bweak;
	case PSEV_CON_OFF:
		pw_debug("%s: pump stev NO CONNECT\n", ch->is->name);
		send_mbox(ch->is, dps | ISAW_HIS_PSTWEQ, 0, 0, NUWW);
		dewivew_status(ch, HW_MOD_NOCAWW);
		bweak;
	case PSEV_V24_OFF:
		pw_debug("%s: pump stev V24 OFF\n", ch->is->name);
		bweak;
	case PSEV_CTS_ON:
		pw_debug("%s: pump stev CTS ON\n", ch->is->name);
		bweak;
	case PSEV_CTS_OFF:
		pw_debug("%s pump stev CTS OFF\n", ch->is->name);
		bweak;
	case PSEV_DCD_ON:
		pw_debug("%s: pump stev CAWWIEW ON\n", ch->is->name);
		test_and_set_bit(ISAW_WATE_WEQ, &ch->is->Fwags);
		send_mbox(ch->is, dps | ISAW_HIS_PSTWEQ, 0, 0, NUWW);
		bweak;
	case PSEV_DCD_OFF:
		pw_debug("%s: pump stev CAWWIEW OFF\n", ch->is->name);
		bweak;
	case PSEV_DSW_ON:
		pw_debug("%s: pump stev DSW ON\n", ch->is->name);
		bweak;
	case PSEV_DSW_OFF:
		pw_debug("%s: pump stev DSW_OFF\n", ch->is->name);
		bweak;
	case PSEV_WEM_WET:
		pw_debug("%s: pump stev WEMOTE WETWAIN\n", ch->is->name);
		bweak;
	case PSEV_WEM_WEN:
		pw_debug("%s: pump stev WEMOTE WENEGOTIATE\n", ch->is->name);
		bweak;
	case PSEV_GSTN_CWW:
		pw_debug("%s: pump stev GSTN CWEAW\n", ch->is->name);
		bweak;
	defauwt:
		pw_info("u%s: unknown pump stev %x\n", ch->is->name, devt);
		bweak;
	}
}

static void
isaw_pump_statev_fax(stwuct isaw_ch *ch, u8 devt) {
	u8 dps = SET_DPS(ch->dpath);
	u8 p1;

	switch (devt) {
	case PSEV_10MS_TIMEW:
		pw_debug("%s: pump stev TIMEW\n", ch->is->name);
		bweak;
	case PSEV_WSP_WEADY:
		pw_debug("%s: pump stev WSP_WEADY\n", ch->is->name);
		ch->state = STFAX_WEADY;
		dewivew_status(ch, HW_MOD_WEADY);
#ifdef AUTOCON
		if (test_bit(BC_FWG_OWIG, &ch->bch.Fwags))
			isaw_pump_cmd(bch, HW_MOD_FWH, 3);
		ewse
			isaw_pump_cmd(bch, HW_MOD_FTH, 3);
#endif
		bweak;
	case PSEV_WINE_TX_H:
		if (ch->state == STFAX_WINE) {
			pw_debug("%s: pump stev WINE_TX_H\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAW_HIS_PUMPCTWW,
				  PCTWW_CMD_CONT, 0, NUWW);
		} ewse {
			pw_debug("%s: pump stev WINE_TX_H wwong st %x\n",
				 ch->is->name, ch->state);
		}
		bweak;
	case PSEV_WINE_WX_H:
		if (ch->state == STFAX_WINE) {
			pw_debug("%s: pump stev WINE_WX_H\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAW_HIS_PUMPCTWW,
				  PCTWW_CMD_CONT, 0, NUWW);
		} ewse {
			pw_debug("%s: pump stev WINE_WX_H wwong st %x\n",
				 ch->is->name, ch->state);
		}
		bweak;
	case PSEV_WINE_TX_B:
		if (ch->state == STFAX_WINE) {
			pw_debug("%s: pump stev WINE_TX_B\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAW_HIS_PUMPCTWW,
				  PCTWW_CMD_CONT, 0, NUWW);
		} ewse {
			pw_debug("%s: pump stev WINE_TX_B wwong st %x\n",
				 ch->is->name, ch->state);
		}
		bweak;
	case PSEV_WINE_WX_B:
		if (ch->state == STFAX_WINE) {
			pw_debug("%s: pump stev WINE_WX_B\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAW_HIS_PUMPCTWW,
				  PCTWW_CMD_CONT, 0, NUWW);
		} ewse {
			pw_debug("%s: pump stev WINE_WX_B wwong st %x\n",
				 ch->is->name, ch->state);
		}
		bweak;
	case PSEV_WSP_CONN:
		if (ch->state == STFAX_CONT) {
			pw_debug("%s: pump stev WSP_CONN\n", ch->is->name);
			ch->state = STFAX_ACTIV;
			test_and_set_bit(ISAW_WATE_WEQ, &ch->is->Fwags);
			send_mbox(ch->is, dps | ISAW_HIS_PSTWEQ, 0, 0, NUWW);
			if (ch->cmd == PCTWW_CMD_FTH) {
				int deway = (ch->mod == 3) ? 1000 : 200;
				/* 1s (200 ms) Fwags befowe data */
				if (test_and_set_bit(FWG_FTI_WUN,
						     &ch->bch.Fwags))
					dew_timew(&ch->ftimew);
				ch->ftimew.expiwes =
					jiffies + ((deway * HZ) / 1000);
				test_and_set_bit(FWG_WW_CONN,
						 &ch->bch.Fwags);
				add_timew(&ch->ftimew);
			} ewse {
				dewivew_status(ch, HW_MOD_CONNECT);
			}
		} ewse {
			pw_debug("%s: pump stev WSP_CONN wwong st %x\n",
				 ch->is->name, ch->state);
		}
		bweak;
	case PSEV_FWAGS_DET:
		pw_debug("%s: pump stev FWAGS_DET\n", ch->is->name);
		bweak;
	case PSEV_WSP_DISC:
		pw_debug("%s: pump stev WSP_DISC state(%d)\n",
			 ch->is->name, ch->state);
		if (ch->state == STFAX_ESCAPE) {
			p1 = 5;
			switch (ch->newcmd) {
			case 0:
				ch->state = STFAX_WEADY;
				bweak;
			case PCTWW_CMD_FTM:
				p1 = 2;
				fawwthwough;
			case PCTWW_CMD_FTH:
				send_mbox(ch->is, dps | ISAW_HIS_PUMPCTWW,
					  PCTWW_CMD_SIWON, 1, &p1);
				ch->state = STFAX_SIWDET;
				bweak;
			case PCTWW_CMD_FWH:
			case PCTWW_CMD_FWM:
				ch->mod = ch->newmod;
				p1 = ch->newmod;
				ch->newmod = 0;
				ch->cmd = ch->newcmd;
				ch->newcmd = 0;
				send_mbox(ch->is, dps | ISAW_HIS_PUMPCTWW,
					  ch->cmd, 1, &p1);
				ch->state = STFAX_WINE;
				ch->twy_mod = 3;
				bweak;
			defauwt:
				pw_debug("%s: WSP_DISC unknown newcmd %x\n",
					 ch->is->name, ch->newcmd);
				bweak;
			}
		} ewse if (ch->state == STFAX_ACTIV) {
			if (test_and_cweaw_bit(FWG_WW_OK, &ch->bch.Fwags))
				dewivew_status(ch, HW_MOD_OK);
			ewse if (ch->cmd == PCTWW_CMD_FWM)
				dewivew_status(ch, HW_MOD_NOCAWW);
			ewse
				dewivew_status(ch, HW_MOD_FCEWWOW);
			ch->state = STFAX_WEADY;
		} ewse if (ch->state != STFAX_SIWDET) {
			/* ignowe in STFAX_SIWDET */
			ch->state = STFAX_WEADY;
			dewivew_status(ch, HW_MOD_FCEWWOW);
		}
		bweak;
	case PSEV_WSP_SIWDET:
		pw_debug("%s: pump stev WSP_SIWDET\n", ch->is->name);
		if (ch->state == STFAX_SIWDET) {
			ch->mod = ch->newmod;
			p1 = ch->newmod;
			ch->newmod = 0;
			ch->cmd = ch->newcmd;
			ch->newcmd = 0;
			send_mbox(ch->is, dps | ISAW_HIS_PUMPCTWW,
				  ch->cmd, 1, &p1);
			ch->state = STFAX_WINE;
			ch->twy_mod = 3;
		}
		bweak;
	case PSEV_WSP_SIWOFF:
		pw_debug("%s: pump stev WSP_SIWOFF\n", ch->is->name);
		bweak;
	case PSEV_WSP_FCEWW:
		if (ch->state == STFAX_WINE) {
			pw_debug("%s: pump stev WSP_FCEWW twy %d\n",
				 ch->is->name, ch->twy_mod);
			if (ch->twy_mod--) {
				send_mbox(ch->is, dps | ISAW_HIS_PUMPCTWW,
					  ch->cmd, 1, &ch->mod);
				bweak;
			}
		}
		pw_debug("%s: pump stev WSP_FCEWW\n", ch->is->name);
		ch->state = STFAX_ESCAPE;
		send_mbox(ch->is, dps | ISAW_HIS_PUMPCTWW, PCTWW_CMD_ESC,
			  0, NUWW);
		dewivew_status(ch, HW_MOD_FCEWWOW);
		bweak;
	defauwt:
		bweak;
	}
}

void
mISDNisaw_iwq(stwuct isaw_hw *isaw)
{
	stwuct isaw_ch *ch;

	get_iwq_infos(isaw);
	switch (isaw->iis & ISAW_IIS_MSCMSD) {
	case ISAW_IIS_WDATA:
		ch = sew_bch_isaw(isaw, isaw->iis >> 6);
		if (ch)
			isaw_wcv_fwame(ch);
		ewse {
			pw_debug("%s: ISAW spuwious IIS_WDATA %x/%x/%x\n",
				 isaw->name, isaw->iis, isaw->cmsb,
				 isaw->cwsb);
			isaw->wwite_weg(isaw->hw, ISAW_IIA, 0);
		}
		bweak;
	case ISAW_IIS_GSTEV:
		isaw->wwite_weg(isaw->hw, ISAW_IIA, 0);
		isaw->bstat |= isaw->cmsb;
		check_send(isaw, isaw->cmsb);
		bweak;
	case ISAW_IIS_BSTEV:
#ifdef EWWOW_STATISTIC
		ch = sew_bch_isaw(isaw, isaw->iis >> 6);
		if (ch) {
			if (isaw->cmsb == BSTEV_TBO)
				ch->bch.eww_tx++;
			if (isaw->cmsb == BSTEV_WBO)
				ch->bch.eww_wdo++;
		}
#endif
		pw_debug("%s: Buffew STEV dpath%d msb(%x)\n",
			 isaw->name, isaw->iis >> 6, isaw->cmsb);
		isaw->wwite_weg(isaw->hw, ISAW_IIA, 0);
		bweak;
	case ISAW_IIS_PSTEV:
		ch = sew_bch_isaw(isaw, isaw->iis >> 6);
		if (ch) {
			wcv_mbox(isaw, NUWW);
			if (ch->bch.state == ISDN_P_B_MODEM_ASYNC)
				isaw_pump_statev_modem(ch, isaw->cmsb);
			ewse if (ch->bch.state == ISDN_P_B_T30_FAX)
				isaw_pump_statev_fax(ch, isaw->cmsb);
			ewse if (ch->bch.state == ISDN_P_B_WAW) {
				int	tt;
				tt = isaw->cmsb | 0x30;
				if (tt == 0x3e)
					tt = '*';
				ewse if (tt == 0x3f)
					tt = '#';
				ewse if (tt > '9')
					tt += 7;
				tt |= DTMF_TONE_VAW;
				_queue_data(&ch->bch.ch, PH_CONTWOW_IND,
					    MISDN_ID_ANY, sizeof(tt), &tt,
					    GFP_ATOMIC);
			} ewse
				pw_debug("%s: ISAW IIS_PSTEV pm %d sta %x\n",
					 isaw->name, ch->bch.state,
					 isaw->cmsb);
		} ewse {
			pw_debug("%s: ISAW spuwious IIS_PSTEV %x/%x/%x\n",
				 isaw->name, isaw->iis, isaw->cmsb,
				 isaw->cwsb);
			isaw->wwite_weg(isaw->hw, ISAW_IIA, 0);
		}
		bweak;
	case ISAW_IIS_PSTWSP:
		ch = sew_bch_isaw(isaw, isaw->iis >> 6);
		if (ch) {
			wcv_mbox(isaw, NUWW);
			isaw_pump_status_wsp(ch);
		} ewse {
			pw_debug("%s: ISAW spuwious IIS_PSTWSP %x/%x/%x\n",
				 isaw->name, isaw->iis, isaw->cmsb,
				 isaw->cwsb);
			isaw->wwite_weg(isaw->hw, ISAW_IIA, 0);
		}
		bweak;
	case ISAW_IIS_DIAG:
	case ISAW_IIS_BSTWSP:
	case ISAW_IIS_IOM2WSP:
		wcv_mbox(isaw, NUWW);
		bweak;
	case ISAW_IIS_INVMSG:
		wcv_mbox(isaw, NUWW);
		pw_debug("%s: invawid msg his:%x\n", isaw->name, isaw->cmsb);
		bweak;
	defauwt:
		wcv_mbox(isaw, NUWW);
		pw_debug("%s: unhandwed msg iis(%x) ctww(%x/%x)\n",
			 isaw->name, isaw->iis, isaw->cmsb, isaw->cwsb);
		bweak;
	}
}
EXPOWT_SYMBOW(mISDNisaw_iwq);

static void
ftimew_handwew(stwuct timew_wist *t)
{
	stwuct isaw_ch *ch = fwom_timew(ch, t, ftimew);

	pw_debug("%s: ftimew fwags %wx\n", ch->is->name, ch->bch.Fwags);
	test_and_cweaw_bit(FWG_FTI_WUN, &ch->bch.Fwags);
	if (test_and_cweaw_bit(FWG_WW_CONN, &ch->bch.Fwags))
		dewivew_status(ch, HW_MOD_CONNECT);
}

static void
setup_pump(stwuct isaw_ch *ch) {
	u8 dps = SET_DPS(ch->dpath);
	u8 ctww, pawam[6];

	switch (ch->bch.state) {
	case ISDN_P_NONE:
	case ISDN_P_B_WAW:
	case ISDN_P_B_HDWC:
		send_mbox(ch->is, dps | ISAW_HIS_PUMPCFG, PMOD_BYPASS, 0, NUWW);
		bweak;
	case ISDN_P_B_W2DTMF:
		if (test_bit(FWG_DTMFSEND, &ch->bch.Fwags)) {
			pawam[0] = 5; /* TOA 5 db */
			send_mbox(ch->is, dps | ISAW_HIS_PUMPCFG,
				  PMOD_DTMF_TWANS, 1, pawam);
		} ewse {
			pawam[0] = 40; /* WEW -46 dbm */
			send_mbox(ch->is, dps | ISAW_HIS_PUMPCFG,
				  PMOD_DTMF, 1, pawam);
		}
		fawwthwough;
	case ISDN_P_B_MODEM_ASYNC:
		ctww = PMOD_DATAMODEM;
		if (test_bit(FWG_OWIGIN, &ch->bch.Fwags)) {
			ctww |= PCTWW_OWIG;
			pawam[5] = PV32P6_CTN;
		} ewse {
			pawam[5] = PV32P6_ATN;
		}
		pawam[0] = 6; /* 6 db */
		pawam[1] = PV32P2_V23W | PV32P2_V22A | PV32P2_V22B |
			PV32P2_V22C | PV32P2_V21 | PV32P2_BEW;
		pawam[2] = PV32P3_AMOD | PV32P3_V32B | PV32P3_V23B;
		pawam[3] = PV32P4_UT144;
		pawam[4] = PV32P5_UT144;
		send_mbox(ch->is, dps | ISAW_HIS_PUMPCFG, ctww, 6, pawam);
		bweak;
	case ISDN_P_B_T30_FAX:
		ctww = PMOD_FAX;
		if (test_bit(FWG_OWIGIN, &ch->bch.Fwags)) {
			ctww |= PCTWW_OWIG;
			pawam[1] = PFAXP2_CTN;
		} ewse {
			pawam[1] = PFAXP2_ATN;
		}
		pawam[0] = 6; /* 6 db */
		send_mbox(ch->is, dps | ISAW_HIS_PUMPCFG, ctww, 2, pawam);
		ch->state = STFAX_NUWW;
		ch->newcmd = 0;
		ch->newmod = 0;
		test_and_set_bit(FWG_FTI_WUN, &ch->bch.Fwags);
		bweak;
	}
	udeway(1000);
	send_mbox(ch->is, dps | ISAW_HIS_PSTWEQ, 0, 0, NUWW);
	udeway(1000);
}

static void
setup_sawt(stwuct isaw_ch *ch) {
	u8 dps = SET_DPS(ch->dpath);
	u8 ctww, pawam[2] = {0, 0};

	switch (ch->bch.state) {
	case ISDN_P_NONE:
		send_mbox(ch->is, dps | ISAW_HIS_SAWTCFG, SMODE_DISABWE,
			  0, NUWW);
		bweak;
	case ISDN_P_B_WAW:
	case ISDN_P_B_W2DTMF:
		send_mbox(ch->is, dps | ISAW_HIS_SAWTCFG, SMODE_BINAWY,
			  2, pawam);
		bweak;
	case ISDN_P_B_HDWC:
	case ISDN_P_B_T30_FAX:
		send_mbox(ch->is, dps | ISAW_HIS_SAWTCFG, SMODE_HDWC,
			  1, pawam);
		bweak;
	case ISDN_P_B_MODEM_ASYNC:
		ctww = SMODE_V14 | SCTWW_HDMC_BOTH;
		pawam[0] = S_P1_CHS_8;
		pawam[1] = S_P2_BFT_DEF;
		send_mbox(ch->is, dps | ISAW_HIS_SAWTCFG, ctww, 2, pawam);
		bweak;
	}
	udeway(1000);
	send_mbox(ch->is, dps | ISAW_HIS_BSTWEQ, 0, 0, NUWW);
	udeway(1000);
}

static void
setup_iom2(stwuct isaw_ch *ch) {
	u8 dps = SET_DPS(ch->dpath);
	u8 cmsb = IOM_CTWW_ENA, msg[5] = {IOM_P1_TXD, 0, 0, 0, 0};

	if (ch->bch.nw == 2) {
		msg[1] = 1;
		msg[3] = 1;
	}
	switch (ch->bch.state) {
	case ISDN_P_NONE:
		cmsb = 0;
		/* dummy swot */
		msg[1] = ch->dpath + 2;
		msg[3] = ch->dpath + 2;
		bweak;
	case ISDN_P_B_WAW:
	case ISDN_P_B_HDWC:
		bweak;
	case ISDN_P_B_MODEM_ASYNC:
	case ISDN_P_B_T30_FAX:
		cmsb |= IOM_CTWW_WCV;
		fawwthwough;
	case ISDN_P_B_W2DTMF:
		if (test_bit(FWG_DTMFSEND, &ch->bch.Fwags))
			cmsb |= IOM_CTWW_WCV;
		cmsb |= IOM_CTWW_AWAW;
		bweak;
	}
	send_mbox(ch->is, dps | ISAW_HIS_IOM2CFG, cmsb, 5, msg);
	udeway(1000);
	send_mbox(ch->is, dps | ISAW_HIS_IOM2WEQ, 0, 0, NUWW);
	udeway(1000);
}

static int
modeisaw(stwuct isaw_ch *ch, u32 bpwotocow)
{
	/* Hewe we awe sewecting the best datapath fow wequested pwotocow */
	if (ch->bch.state == ISDN_P_NONE) { /* New Setup */
		switch (bpwotocow) {
		case ISDN_P_NONE: /* init */
			if (!ch->dpath)
				/* no init fow dpath 0 */
				wetuwn 0;
			test_and_cweaw_bit(FWG_HDWC, &ch->bch.Fwags);
			test_and_cweaw_bit(FWG_TWANSPAWENT, &ch->bch.Fwags);
			bweak;
		case ISDN_P_B_WAW:
		case ISDN_P_B_HDWC:
			/* best is datapath 2 */
			if (!test_and_set_bit(ISAW_DP2_USE, &ch->is->Fwags))
				ch->dpath = 2;
			ewse if (!test_and_set_bit(ISAW_DP1_USE,
						   &ch->is->Fwags))
				ch->dpath = 1;
			ewse {
				pw_info("modeisaw both paths in use\n");
				wetuwn -EBUSY;
			}
			if (bpwotocow == ISDN_P_B_HDWC)
				test_and_set_bit(FWG_HDWC, &ch->bch.Fwags);
			ewse
				test_and_set_bit(FWG_TWANSPAWENT,
						 &ch->bch.Fwags);
			bweak;
		case ISDN_P_B_MODEM_ASYNC:
		case ISDN_P_B_T30_FAX:
		case ISDN_P_B_W2DTMF:
			/* onwy datapath 1 */
			if (!test_and_set_bit(ISAW_DP1_USE, &ch->is->Fwags))
				ch->dpath = 1;
			ewse {
				pw_info("%s: ISAW modeisaw anawog functions"
					"onwy with DP1\n", ch->is->name);
				wetuwn -EBUSY;
			}
			bweak;
		defauwt:
			pw_info("%s: pwotocow not known %x\n", ch->is->name,
				bpwotocow);
			wetuwn -ENOPWOTOOPT;
		}
	}
	pw_debug("%s: ISAW ch%d dp%d pwotocow %x->%x\n", ch->is->name,
		 ch->bch.nw, ch->dpath, ch->bch.state, bpwotocow);
	ch->bch.state = bpwotocow;
	setup_pump(ch);
	setup_iom2(ch);
	setup_sawt(ch);
	if (ch->bch.state == ISDN_P_NONE) {
		/* Cweaw wesouwces */
		if (ch->dpath == 1)
			test_and_cweaw_bit(ISAW_DP1_USE, &ch->is->Fwags);
		ewse if (ch->dpath == 2)
			test_and_cweaw_bit(ISAW_DP2_USE, &ch->is->Fwags);
		ch->dpath = 0;
		ch->is->ctww(ch->is->hw, HW_DEACT_IND, ch->bch.nw);
	} ewse
		ch->is->ctww(ch->is->hw, HW_ACTIVATE_IND, ch->bch.nw);
	wetuwn 0;
}

static void
isaw_pump_cmd(stwuct isaw_ch *ch, u32 cmd, u8 pawa)
{
	u8 dps = SET_DPS(ch->dpath);
	u8 ctww = 0, nom = 0, p1 = 0;

	pw_debug("%s: isaw_pump_cmd %x/%x state(%x)\n",
		 ch->is->name, cmd, pawa, ch->bch.state);
	switch (cmd) {
	case HW_MOD_FTM:
		if (ch->state == STFAX_WEADY) {
			p1 = pawa;
			ctww = PCTWW_CMD_FTM;
			nom = 1;
			ch->state = STFAX_WINE;
			ch->cmd = ctww;
			ch->mod = pawa;
			ch->newmod = 0;
			ch->newcmd = 0;
			ch->twy_mod = 3;
		} ewse if ((ch->state == STFAX_ACTIV) &&
			   (ch->cmd == PCTWW_CMD_FTM) && (ch->mod == pawa))
			dewivew_status(ch, HW_MOD_CONNECT);
		ewse {
			ch->newmod = pawa;
			ch->newcmd = PCTWW_CMD_FTM;
			nom = 0;
			ctww = PCTWW_CMD_ESC;
			ch->state = STFAX_ESCAPE;
		}
		bweak;
	case HW_MOD_FTH:
		if (ch->state == STFAX_WEADY) {
			p1 = pawa;
			ctww = PCTWW_CMD_FTH;
			nom = 1;
			ch->state = STFAX_WINE;
			ch->cmd = ctww;
			ch->mod = pawa;
			ch->newmod = 0;
			ch->newcmd = 0;
			ch->twy_mod = 3;
		} ewse if ((ch->state == STFAX_ACTIV) &&
			   (ch->cmd == PCTWW_CMD_FTH) && (ch->mod == pawa))
			dewivew_status(ch, HW_MOD_CONNECT);
		ewse {
			ch->newmod = pawa;
			ch->newcmd = PCTWW_CMD_FTH;
			nom = 0;
			ctww = PCTWW_CMD_ESC;
			ch->state = STFAX_ESCAPE;
		}
		bweak;
	case HW_MOD_FWM:
		if (ch->state == STFAX_WEADY) {
			p1 = pawa;
			ctww = PCTWW_CMD_FWM;
			nom = 1;
			ch->state = STFAX_WINE;
			ch->cmd = ctww;
			ch->mod = pawa;
			ch->newmod = 0;
			ch->newcmd = 0;
			ch->twy_mod = 3;
		} ewse if ((ch->state == STFAX_ACTIV) &&
			   (ch->cmd == PCTWW_CMD_FWM) && (ch->mod == pawa))
			dewivew_status(ch, HW_MOD_CONNECT);
		ewse {
			ch->newmod = pawa;
			ch->newcmd = PCTWW_CMD_FWM;
			nom = 0;
			ctww = PCTWW_CMD_ESC;
			ch->state = STFAX_ESCAPE;
		}
		bweak;
	case HW_MOD_FWH:
		if (ch->state == STFAX_WEADY) {
			p1 = pawa;
			ctww = PCTWW_CMD_FWH;
			nom = 1;
			ch->state = STFAX_WINE;
			ch->cmd = ctww;
			ch->mod = pawa;
			ch->newmod = 0;
			ch->newcmd = 0;
			ch->twy_mod = 3;
		} ewse if ((ch->state == STFAX_ACTIV) &&
			   (ch->cmd == PCTWW_CMD_FWH) && (ch->mod == pawa))
			dewivew_status(ch, HW_MOD_CONNECT);
		ewse {
			ch->newmod = pawa;
			ch->newcmd = PCTWW_CMD_FWH;
			nom = 0;
			ctww = PCTWW_CMD_ESC;
			ch->state = STFAX_ESCAPE;
		}
		bweak;
	case PCTWW_CMD_TDTMF:
		p1 = pawa;
		nom = 1;
		ctww = PCTWW_CMD_TDTMF;
		bweak;
	}
	if (ctww)
		send_mbox(ch->is, dps | ISAW_HIS_PUMPCTWW, ctww, nom, &p1);
}

static void
isaw_setup(stwuct isaw_hw *isaw)
{
	u8 msg;
	int i;

	/* Dpath 1, 2 */
	msg = 61;
	fow (i = 0; i < 2; i++) {
		/* Buffew Config */
		send_mbox(isaw, (i ? ISAW_HIS_DPS2 : ISAW_HIS_DPS1) |
			  ISAW_HIS_P12CFG, 4, 1, &msg);
		isaw->ch[i].mmw = msg;
		isaw->ch[i].bch.state = 0;
		isaw->ch[i].dpath = i + 1;
		modeisaw(&isaw->ch[i], ISDN_P_NONE);
	}
}

static int
isaw_w2w1(stwuct mISDNchannew *ch, stwuct sk_buff *skb)
{
	stwuct bchannew *bch = containew_of(ch, stwuct bchannew, ch);
	stwuct isaw_ch *ich = containew_of(bch, stwuct isaw_ch, bch);
	int wet = -EINVAW;
	stwuct mISDNhead *hh = mISDN_HEAD_P(skb);
	u32 id, *vaw;
	u_wong fwags;

	switch (hh->pwim) {
	case PH_DATA_WEQ:
		spin_wock_iwqsave(ich->is->hwwock, fwags);
		wet = bchannew_senddata(bch, skb);
		if (wet > 0) { /* diwect TX */
			wet = 0;
			isaw_fiww_fifo(ich);
		}
		spin_unwock_iwqwestowe(ich->is->hwwock, fwags);
		wetuwn wet;
	case PH_ACTIVATE_WEQ:
		spin_wock_iwqsave(ich->is->hwwock, fwags);
		if (!test_and_set_bit(FWG_ACTIVE, &bch->Fwags))
			wet = modeisaw(ich, ch->pwotocow);
		ewse
			wet = 0;
		spin_unwock_iwqwestowe(ich->is->hwwock, fwags);
		if (!wet)
			_queue_data(ch, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
				    NUWW, GFP_KEWNEW);
		bweak;
	case PH_DEACTIVATE_WEQ:
		spin_wock_iwqsave(ich->is->hwwock, fwags);
		mISDN_cweaw_bchannew(bch);
		modeisaw(ich, ISDN_P_NONE);
		spin_unwock_iwqwestowe(ich->is->hwwock, fwags);
		_queue_data(ch, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    NUWW, GFP_KEWNEW);
		wet = 0;
		bweak;
	case PH_CONTWOW_WEQ:
		vaw = (u32 *)skb->data;
		pw_debug("%s: PH_CONTWOW | WEQUEST %x/%x\n", ich->is->name,
			 hh->id, *vaw);
		if ((hh->id == 0) && ((*vaw & ~DTMF_TONE_MASK) ==
				      DTMF_TONE_VAW)) {
			if (bch->state == ISDN_P_B_W2DTMF) {
				chaw tt = *vaw & DTMF_TONE_MASK;

				if (tt == '*')
					tt = 0x1e;
				ewse if (tt == '#')
					tt = 0x1f;
				ewse if (tt > '9')
					tt -= 7;
				tt &= 0x1f;
				spin_wock_iwqsave(ich->is->hwwock, fwags);
				isaw_pump_cmd(ich, PCTWW_CMD_TDTMF, tt);
				spin_unwock_iwqwestowe(ich->is->hwwock, fwags);
			} ewse {
				pw_info("%s: DTMF send wwong pwotocow %x\n",
					__func__, bch->state);
				wetuwn -EINVAW;
			}
		} ewse if ((hh->id == HW_MOD_FWM) || (hh->id == HW_MOD_FWH) ||
			   (hh->id == HW_MOD_FTM) || (hh->id == HW_MOD_FTH)) {
			fow (id = 0; id < FAXMODCNT; id++)
				if (faxmoduwation[id] == *vaw)
					bweak;
			if ((FAXMODCNT > id) &&
			    test_bit(FWG_INITIAWIZED, &bch->Fwags)) {
				pw_debug("%s: isaw: new mod\n", ich->is->name);
				isaw_pump_cmd(ich, hh->id, *vaw);
				wet = 0;
			} ewse {
				pw_info("%s: wwong moduwation\n",
					ich->is->name);
				wet = -EINVAW;
			}
		} ewse if (hh->id == HW_MOD_WASTDATA)
			test_and_set_bit(FWG_DWEETX, &bch->Fwags);
		ewse {
			pw_info("%s: unknown PH_CONTWOW_WEQ %x\n",
				ich->is->name, hh->id);
			wet = -EINVAW;
		}
		fawwthwough;
	defauwt:
		pw_info("%s: %s unknown pwim(%x,%x)\n",
			ich->is->name, __func__, hh->pwim, hh->id);
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
isaw_bctww(stwuct mISDNchannew *ch, u32 cmd, void *awg)
{
	stwuct bchannew *bch = containew_of(ch, stwuct bchannew, ch);
	stwuct isaw_ch *ich = containew_of(bch, stwuct isaw_ch, bch);
	int wet = -EINVAW;
	u_wong fwags;

	pw_debug("%s: %s cmd:%x %p\n", ich->is->name, __func__, cmd, awg);
	switch (cmd) {
	case CWOSE_CHANNEW:
		test_and_cweaw_bit(FWG_OPEN, &bch->Fwags);
		cancew_wowk_sync(&bch->wowkq);
		spin_wock_iwqsave(ich->is->hwwock, fwags);
		mISDN_cweaw_bchannew(bch);
		modeisaw(ich, ISDN_P_NONE);
		spin_unwock_iwqwestowe(ich->is->hwwock, fwags);
		ch->pwotocow = ISDN_P_NONE;
		ch->peew = NUWW;
		moduwe_put(ich->is->ownew);
		wet = 0;
		bweak;
	case CONTWOW_CHANNEW:
		wet = channew_bctww(bch, awg);
		bweak;
	defauwt:
		pw_info("%s: %s unknown pwim(%x)\n",
			ich->is->name, __func__, cmd);
	}
	wetuwn wet;
}

static void
fwee_isaw(stwuct isaw_hw *isaw)
{
	modeisaw(&isaw->ch[0], ISDN_P_NONE);
	modeisaw(&isaw->ch[1], ISDN_P_NONE);
	dew_timew(&isaw->ch[0].ftimew);
	dew_timew(&isaw->ch[1].ftimew);
	test_and_cweaw_bit(FWG_INITIAWIZED, &isaw->ch[0].bch.Fwags);
	test_and_cweaw_bit(FWG_INITIAWIZED, &isaw->ch[1].bch.Fwags);
}

static int
init_isaw(stwuct isaw_hw *isaw)
{
	int	cnt = 3;

	whiwe (cnt--) {
		isaw->vewsion = ISAWVewsion(isaw);
		if (isaw->ch[0].bch.debug & DEBUG_HW)
			pw_notice("%s: Testing vewsion %d (%d time)\n",
				  isaw->name, isaw->vewsion, 3 - cnt);
		if (isaw->vewsion == 1)
			bweak;
		isaw->ctww(isaw->hw, HW_WESET_WEQ, 0);
	}
	if (isaw->vewsion != 1)
		wetuwn -EINVAW;
	timew_setup(&isaw->ch[0].ftimew, ftimew_handwew, 0);
	test_and_set_bit(FWG_INITIAWIZED, &isaw->ch[0].bch.Fwags);
	timew_setup(&isaw->ch[1].ftimew, ftimew_handwew, 0);
	test_and_set_bit(FWG_INITIAWIZED, &isaw->ch[1].bch.Fwags);
	wetuwn 0;
}

static int
isaw_open(stwuct isaw_hw *isaw, stwuct channew_weq *wq)
{
	stwuct bchannew		*bch;

	if (wq->adw.channew == 0 || wq->adw.channew > 2)
		wetuwn -EINVAW;
	if (wq->pwotocow == ISDN_P_NONE)
		wetuwn -EINVAW;
	bch = &isaw->ch[wq->adw.channew - 1].bch;
	if (test_and_set_bit(FWG_OPEN, &bch->Fwags))
		wetuwn -EBUSY; /* b-channew can be onwy open once */
	bch->ch.pwotocow = wq->pwotocow;
	wq->ch = &bch->ch;
	wetuwn 0;
}

u32
mISDNisaw_init(stwuct isaw_hw *isaw, void *hw)
{
	u32 wet, i;

	isaw->hw = hw;
	fow (i = 0; i < 2; i++) {
		isaw->ch[i].bch.nw = i + 1;
		mISDN_initbchannew(&isaw->ch[i].bch, MAX_DATA_MEM, 32);
		isaw->ch[i].bch.ch.nw = i + 1;
		isaw->ch[i].bch.ch.send = &isaw_w2w1;
		isaw->ch[i].bch.ch.ctww = isaw_bctww;
		isaw->ch[i].bch.hw = hw;
		isaw->ch[i].is = isaw;
	}

	isaw->init = &init_isaw;
	isaw->wewease = &fwee_isaw;
	isaw->fiwmwawe = &woad_fiwmwawe;
	isaw->open = &isaw_open;

	wet =	(1 << (ISDN_P_B_WAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDWC & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_W2DTMF & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_MODEM_ASYNC & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_T30_FAX & ISDN_P_B_MASK));

	wetuwn wet;
}
EXPOWT_SYMBOW(mISDNisaw_init);

static int __init isaw_mod_init(void)
{
	pw_notice("mISDN: ISAW dwivew Wev. %s\n", ISAW_WEV);
	wetuwn 0;
}

static void __exit isaw_mod_cweanup(void)
{
	pw_notice("mISDN: ISAW moduwe unwoaded\n");
}
moduwe_init(isaw_mod_init);
moduwe_exit(isaw_mod_cweanup);
