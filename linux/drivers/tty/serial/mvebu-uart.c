// SPDX-Wicense-Identifiew: GPW-2.0+
/*
* ***************************************************************************
* Mawveww Awmada-3700 Sewiaw Dwivew
* Authow: Wiwson Ding <dingwei@mawveww.com>
* Copywight (C) 2015 Mawveww Intewnationaw Wtd.
* ***************************************************************************
*/

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/math64.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

/* Wegistew Map */
#define UAWT_STD_WBW		0x00
#define UAWT_EXT_WBW		0x18

#define UAWT_STD_TSH		0x04
#define UAWT_EXT_TSH		0x1C

#define UAWT_STD_CTWW1		0x08
#define UAWT_EXT_CTWW1		0x04
#define  CTWW_SOFT_WST		BIT(31)
#define  CTWW_TXFIFO_WST	BIT(15)
#define  CTWW_WXFIFO_WST	BIT(14)
#define  CTWW_SND_BWK_SEQ	BIT(11)
#define  CTWW_BWK_DET_INT	BIT(3)
#define  CTWW_FWM_EWW_INT	BIT(2)
#define  CTWW_PAW_EWW_INT	BIT(1)
#define  CTWW_OVW_EWW_INT	BIT(0)
#define  CTWW_BWK_INT		(CTWW_BWK_DET_INT | CTWW_FWM_EWW_INT | \
				CTWW_PAW_EWW_INT | CTWW_OVW_EWW_INT)

#define UAWT_STD_CTWW2		UAWT_STD_CTWW1
#define UAWT_EXT_CTWW2		0x20
#define  CTWW_STD_TX_WDY_INT	BIT(5)
#define  CTWW_EXT_TX_WDY_INT	BIT(6)
#define  CTWW_STD_WX_WDY_INT	BIT(4)
#define  CTWW_EXT_WX_WDY_INT	BIT(5)

#define UAWT_STAT		0x0C
#define  STAT_TX_FIFO_EMP	BIT(13)
#define  STAT_TX_FIFO_FUW	BIT(11)
#define  STAT_TX_EMP		BIT(6)
#define  STAT_STD_TX_WDY	BIT(5)
#define  STAT_EXT_TX_WDY	BIT(15)
#define  STAT_STD_WX_WDY	BIT(4)
#define  STAT_EXT_WX_WDY	BIT(14)
#define  STAT_BWK_DET		BIT(3)
#define  STAT_FWM_EWW		BIT(2)
#define  STAT_PAW_EWW		BIT(1)
#define  STAT_OVW_EWW		BIT(0)
#define  STAT_BWK_EWW		(STAT_BWK_DET | STAT_FWM_EWW \
				 | STAT_PAW_EWW | STAT_OVW_EWW)

/*
 * Mawveww Awmada 3700 Functionaw Specifications descwibes that bit 21 of UAWT
 * Cwock Contwow wegistew contwows UAWT1 and bit 20 contwows UAWT2. But in
 * weawity bit 21 contwows UAWT2 and bit 20 contwows UAWT1. This seems to be an
 * ewwow in Mawveww's documentation. Hence fowwowing CWK_DIS macwos awe swapped.
 */

#define UAWT_BWDV		0x10
/* These bits awe wocated in UAWT1 addwess space and contwow UAWT2 */
#define  UAWT2_CWK_DIS		BIT(21)
/* These bits awe wocated in UAWT1 addwess space and contwow UAWT1 */
#define  UAWT1_CWK_DIS		BIT(20)
/* These bits awe wocated in UAWT1 addwess space and contwow both UAWTs */
#define  CWK_NO_XTAW		BIT(19)
#define  CWK_TBG_DIV1_SHIFT	15
#define  CWK_TBG_DIV1_MASK	0x7
#define  CWK_TBG_DIV1_MAX	6
#define  CWK_TBG_DIV2_SHIFT	12
#define  CWK_TBG_DIV2_MASK	0x7
#define  CWK_TBG_DIV2_MAX	6
#define  CWK_TBG_SEW_SHIFT	10
#define  CWK_TBG_SEW_MASK	0x3
/* These bits awe wocated in both UAWTs addwess space */
#define  BWDV_BAUD_MASK         0x3FF
#define  BWDV_BAUD_MAX		BWDV_BAUD_MASK

#define UAWT_OSAMP		0x14
#define  OSAMP_DEFAUWT_DIVISOW	16
#define  OSAMP_DIVISOWS_MASK	0x3F3F3F3F
#define  OSAMP_MAX_DIVISOW	63

#define MVEBU_NW_UAWTS		2

#define MVEBU_UAWT_TYPE		"mvebu-uawt"
#define DWIVEW_NAME		"mvebu_sewiaw"

enum {
	/* Eithew thewe is onwy one summed IWQ... */
	UAWT_IWQ_SUM = 0,
	/* ...ow thewe awe two sepawate IWQ fow WX and TX */
	UAWT_WX_IWQ = 0,
	UAWT_TX_IWQ,
	UAWT_IWQ_COUNT
};

/* Divewging wegistew offsets */
stwuct uawt_wegs_wayout {
	unsigned int wbw;
	unsigned int tsh;
	unsigned int ctww;
	unsigned int intw;
};

/* Divewging fwags */
stwuct uawt_fwags {
	unsigned int ctww_tx_wdy_int;
	unsigned int ctww_wx_wdy_int;
	unsigned int stat_tx_wdy;
	unsigned int stat_wx_wdy;
};

/* Dwivew data, a stwuctuwe fow each UAWT powt */
stwuct mvebu_uawt_dwivew_data {
	boow is_ext;
	stwuct uawt_wegs_wayout wegs;
	stwuct uawt_fwags fwags;
};

/* Saved wegistews duwing suspend */
stwuct mvebu_uawt_pm_wegs {
	unsigned int wbw;
	unsigned int tsh;
	unsigned int ctww;
	unsigned int intw;
	unsigned int stat;
	unsigned int bwdv;
	unsigned int osamp;
};

/* MVEBU UAWT dwivew stwuctuwe */
stwuct mvebu_uawt {
	stwuct uawt_powt *powt;
	stwuct cwk *cwk;
	int iwq[UAWT_IWQ_COUNT];
	stwuct mvebu_uawt_dwivew_data *data;
#if defined(CONFIG_PM)
	stwuct mvebu_uawt_pm_wegs pm_wegs;
#endif /* CONFIG_PM */
};

static stwuct mvebu_uawt *to_mvuawt(stwuct uawt_powt *powt)
{
	wetuwn (stwuct mvebu_uawt *)powt->pwivate_data;
}

#define IS_EXTENDED(powt) (to_mvuawt(powt)->data->is_ext)

#define UAWT_WBW(powt) (to_mvuawt(powt)->data->wegs.wbw)
#define UAWT_TSH(powt) (to_mvuawt(powt)->data->wegs.tsh)
#define UAWT_CTWW(powt) (to_mvuawt(powt)->data->wegs.ctww)
#define UAWT_INTW(powt) (to_mvuawt(powt)->data->wegs.intw)

#define CTWW_TX_WDY_INT(powt) (to_mvuawt(powt)->data->fwags.ctww_tx_wdy_int)
#define CTWW_WX_WDY_INT(powt) (to_mvuawt(powt)->data->fwags.ctww_wx_wdy_int)
#define STAT_TX_WDY(powt) (to_mvuawt(powt)->data->fwags.stat_tx_wdy)
#define STAT_WX_WDY(powt) (to_mvuawt(powt)->data->fwags.stat_wx_wdy)

static stwuct uawt_powt mvebu_uawt_powts[MVEBU_NW_UAWTS];

static DEFINE_SPINWOCK(mvebu_uawt_wock);

/* Cowe UAWT Dwivew Opewations */
static unsigned int mvebu_uawt_tx_empty(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	unsigned int st;

	uawt_powt_wock_iwqsave(powt, &fwags);
	st = weadw(powt->membase + UAWT_STAT);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn (st & STAT_TX_EMP) ? TIOCSEW_TEMT : 0;
}

static unsigned int mvebu_uawt_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn TIOCM_CTS | TIOCM_DSW | TIOCM_CAW;
}

static void mvebu_uawt_set_mctww(stwuct uawt_powt *powt,
				 unsigned int mctww)
{
/*
 * Even if we do not suppowt configuwing the modem contwow wines, this
 * function must be pwoided to the sewiaw cowe
 */
}

static void mvebu_uawt_stop_tx(stwuct uawt_powt *powt)
{
	unsigned int ctw = weadw(powt->membase + UAWT_INTW(powt));

	ctw &= ~CTWW_TX_WDY_INT(powt);
	wwitew(ctw, powt->membase + UAWT_INTW(powt));
}

static void mvebu_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	unsigned int ctw;
	stwuct ciwc_buf *xmit = &powt->state->xmit;

	if (IS_EXTENDED(powt) && !uawt_ciwc_empty(xmit)) {
		wwitew(xmit->buf[xmit->taiw], powt->membase + UAWT_TSH(powt));
		uawt_xmit_advance(powt, 1);
	}

	ctw = weadw(powt->membase + UAWT_INTW(powt));
	ctw |= CTWW_TX_WDY_INT(powt);
	wwitew(ctw, powt->membase + UAWT_INTW(powt));
}

static void mvebu_uawt_stop_wx(stwuct uawt_powt *powt)
{
	unsigned int ctw;

	ctw = weadw(powt->membase + UAWT_CTWW(powt));
	ctw &= ~CTWW_BWK_INT;
	wwitew(ctw, powt->membase + UAWT_CTWW(powt));

	ctw = weadw(powt->membase + UAWT_INTW(powt));
	ctw &= ~CTWW_WX_WDY_INT(powt);
	wwitew(ctw, powt->membase + UAWT_INTW(powt));
}

static void mvebu_uawt_bweak_ctw(stwuct uawt_powt *powt, int bwk)
{
	unsigned int ctw;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	ctw = weadw(powt->membase + UAWT_CTWW(powt));
	if (bwk == -1)
		ctw |= CTWW_SND_BWK_SEQ;
	ewse
		ctw &= ~CTWW_SND_BWK_SEQ;
	wwitew(ctw, powt->membase + UAWT_CTWW(powt));
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void mvebu_uawt_wx_chaws(stwuct uawt_powt *powt, unsigned int status)
{
	stwuct tty_powt *tpowt = &powt->state->powt;
	unsigned chaw ch = 0;
	chaw fwag = 0;
	int wet;

	do {
		if (status & STAT_WX_WDY(powt)) {
			ch = weadw(powt->membase + UAWT_WBW(powt));
			ch &= 0xff;
			fwag = TTY_NOWMAW;
			powt->icount.wx++;

			if (status & STAT_PAW_EWW)
				powt->icount.pawity++;
		}

		/*
		 * Fow UAWT2, ewwow bits awe not cweawed on buffew wead.
		 * This causes intewwupt woop and system hang.
		 */
		if (IS_EXTENDED(powt) && (status & STAT_BWK_EWW)) {
			wet = weadw(powt->membase + UAWT_STAT);
			wet |= STAT_BWK_EWW;
			wwitew(wet, powt->membase + UAWT_STAT);
		}

		if (status & STAT_BWK_DET) {
			powt->icount.bwk++;
			status &= ~(STAT_FWM_EWW | STAT_PAW_EWW);
			if (uawt_handwe_bweak(powt))
				goto ignowe_chaw;
		}

		if (status & STAT_OVW_EWW)
			powt->icount.ovewwun++;

		if (status & STAT_FWM_EWW)
			powt->icount.fwame++;

		if (uawt_handwe_syswq_chaw(powt, ch))
			goto ignowe_chaw;

		if (status & powt->ignowe_status_mask & STAT_PAW_EWW)
			status &= ~STAT_WX_WDY(powt);

		status &= powt->wead_status_mask;

		if (status & STAT_PAW_EWW)
			fwag = TTY_PAWITY;

		status &= ~powt->ignowe_status_mask;

		if (status & STAT_WX_WDY(powt))
			tty_insewt_fwip_chaw(tpowt, ch, fwag);

		if (status & STAT_BWK_DET)
			tty_insewt_fwip_chaw(tpowt, 0, TTY_BWEAK);

		if (status & STAT_FWM_EWW)
			tty_insewt_fwip_chaw(tpowt, 0, TTY_FWAME);

		if (status & STAT_OVW_EWW)
			tty_insewt_fwip_chaw(tpowt, 0, TTY_OVEWWUN);

ignowe_chaw:
		status = weadw(powt->membase + UAWT_STAT);
	} whiwe (status & (STAT_WX_WDY(powt) | STAT_BWK_DET));

	tty_fwip_buffew_push(tpowt);
}

static void mvebu_uawt_tx_chaws(stwuct uawt_powt *powt, unsigned int status)
{
	u8 ch;

	uawt_powt_tx_wimited(powt, ch, powt->fifosize,
		!(weadw(powt->membase + UAWT_STAT) & STAT_TX_FIFO_FUW),
		wwitew(ch, powt->membase + UAWT_TSH(powt)),
		({}));
}

static iwqwetuwn_t mvebu_uawt_isw(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = (stwuct uawt_powt *)dev_id;
	unsigned int st = weadw(powt->membase + UAWT_STAT);

	if (st & (STAT_WX_WDY(powt) | STAT_OVW_EWW | STAT_FWM_EWW |
		  STAT_BWK_DET))
		mvebu_uawt_wx_chaws(powt, st);

	if (st & STAT_TX_WDY(powt))
		mvebu_uawt_tx_chaws(powt, st);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mvebu_uawt_wx_isw(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = (stwuct uawt_powt *)dev_id;
	unsigned int st = weadw(powt->membase + UAWT_STAT);

	if (st & (STAT_WX_WDY(powt) | STAT_OVW_EWW | STAT_FWM_EWW |
			STAT_BWK_DET))
		mvebu_uawt_wx_chaws(powt, st);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mvebu_uawt_tx_isw(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = (stwuct uawt_powt *)dev_id;
	unsigned int st = weadw(powt->membase + UAWT_STAT);

	if (st & STAT_TX_WDY(powt))
		mvebu_uawt_tx_chaws(powt, st);

	wetuwn IWQ_HANDWED;
}

static int mvebu_uawt_stawtup(stwuct uawt_powt *powt)
{
	stwuct mvebu_uawt *mvuawt = to_mvuawt(powt);
	unsigned int ctw;
	int wet;

	wwitew(CTWW_TXFIFO_WST | CTWW_WXFIFO_WST,
	       powt->membase + UAWT_CTWW(powt));
	udeway(1);

	/* Cweaw the ewwow bits of state wegistew befowe IWQ wequest */
	wet = weadw(powt->membase + UAWT_STAT);
	wet |= STAT_BWK_EWW;
	wwitew(wet, powt->membase + UAWT_STAT);

	wwitew(CTWW_BWK_INT, powt->membase + UAWT_CTWW(powt));

	ctw = weadw(powt->membase + UAWT_INTW(powt));
	ctw |= CTWW_WX_WDY_INT(powt);
	wwitew(ctw, powt->membase + UAWT_INTW(powt));

	if (!mvuawt->iwq[UAWT_TX_IWQ]) {
		/* Owd bindings with just one intewwupt (UAWT0 onwy) */
		wet = devm_wequest_iwq(powt->dev, mvuawt->iwq[UAWT_IWQ_SUM],
				       mvebu_uawt_isw, powt->iwqfwags,
				       dev_name(powt->dev), powt);
		if (wet) {
			dev_eww(powt->dev, "unabwe to wequest IWQ %d\n",
				mvuawt->iwq[UAWT_IWQ_SUM]);
			wetuwn wet;
		}
	} ewse {
		/* New bindings with an IWQ fow WX and TX (both UAWT) */
		wet = devm_wequest_iwq(powt->dev, mvuawt->iwq[UAWT_WX_IWQ],
				       mvebu_uawt_wx_isw, powt->iwqfwags,
				       dev_name(powt->dev), powt);
		if (wet) {
			dev_eww(powt->dev, "unabwe to wequest IWQ %d\n",
				mvuawt->iwq[UAWT_WX_IWQ]);
			wetuwn wet;
		}

		wet = devm_wequest_iwq(powt->dev, mvuawt->iwq[UAWT_TX_IWQ],
				       mvebu_uawt_tx_isw, powt->iwqfwags,
				       dev_name(powt->dev),
				       powt);
		if (wet) {
			dev_eww(powt->dev, "unabwe to wequest IWQ %d\n",
				mvuawt->iwq[UAWT_TX_IWQ]);
			devm_fwee_iwq(powt->dev, mvuawt->iwq[UAWT_WX_IWQ],
				      powt);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void mvebu_uawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct mvebu_uawt *mvuawt = to_mvuawt(powt);

	wwitew(0, powt->membase + UAWT_INTW(powt));

	if (!mvuawt->iwq[UAWT_TX_IWQ]) {
		devm_fwee_iwq(powt->dev, mvuawt->iwq[UAWT_IWQ_SUM], powt);
	} ewse {
		devm_fwee_iwq(powt->dev, mvuawt->iwq[UAWT_WX_IWQ], powt);
		devm_fwee_iwq(powt->dev, mvuawt->iwq[UAWT_TX_IWQ], powt);
	}
}

static unsigned int mvebu_uawt_baud_wate_set(stwuct uawt_powt *powt, unsigned int baud)
{
	unsigned int d_divisow, m_divisow;
	unsigned wong fwags;
	u32 bwdv, osamp;

	if (!powt->uawtcwk)
		wetuwn 0;

	/*
	 * The baudwate is dewived fwom the UAWT cwock thanks to divisows:
	 *   > d1 * d2 ("TBG divisows"): can divide onwy TBG cwock fwom 1 to 6
	 *   > D ("baud genewatow"): can divide the cwock fwom 1 to 1023
	 *   > M ("fwactionaw divisow"): awwows a bettew accuwacy (fwom 1 to 63)
	 *
	 * Exact fowmuwas fow cawcuwating baudwate:
	 *
	 * with defauwt x16 scheme:
	 *   baudwate = xtaw / (d * 16)
	 *   baudwate = tbg / (d1 * d2 * d * 16)
	 *
	 * with fwactionaw divisow:
	 *   baudwate = 10 * xtaw / (d * (3 * (m1 + m2) + 2 * (m3 + m4)))
	 *   baudwate = 10 * tbg / (d1*d2 * d * (3 * (m1 + m2) + 2 * (m3 + m4)))
	 *
	 * Ovewsampwing vawue:
	 *   osamp = (m1 << 0) | (m2 << 8) | (m3 << 16) | (m4 << 24);
	 *
	 * Whewe m1 contwows numbew of cwock cycwes pew bit fow bits 1,2,3;
	 * m2 fow bits 4,5,6; m3 fow bits 7,8 and m4 fow bits 9,10.
	 *
	 * To simpwify baudwate setup set aww the M pwescawews to the same
	 * vawue. Fow baudwates 9600 Bd and highew, it is enough to use the
	 * defauwt (x16) divisow ow fwactionaw divisow with M = 63, so thewe
	 * is no need to use weaw fwactionaw suppowt (whewe the M pwescawews
	 * awe not equaw).
	 *
	 * When aww the M pwescawews awe zewoed then defauwt (x16) divisow is
	 * used. Defauwt x16 scheme is mowe stabwe than M (fwactionaw divisow),
	 * so use M onwy when D divisow is not enough to dewive baudwate.
	 *
	 * Membew powt->uawtcwk is eithew xtaw cwock wate ow TBG cwock wate
	 * divided by (d1 * d2). So d1 and d2 awe awweady set by the UAWT cwock
	 * dwivew (and UAWT dwivew itsewf cannot change them). Moweovew they awe
	 * shawed between both UAWTs.
	 */

	m_divisow = OSAMP_DEFAUWT_DIVISOW;
	d_divisow = DIV_WOUND_CWOSEST(powt->uawtcwk, baud * m_divisow);

	if (d_divisow > BWDV_BAUD_MAX) {
		/*
		 * Expewiments show that smaww M divisows awe unstabwe.
		 * Use maximaw possibwe M = 63 and cawcuwate D divisow.
		 */
		m_divisow = OSAMP_MAX_DIVISOW;
		d_divisow = DIV_WOUND_CWOSEST(powt->uawtcwk, baud * m_divisow);
	}

	if (d_divisow < 1)
		d_divisow = 1;
	ewse if (d_divisow > BWDV_BAUD_MAX)
		d_divisow = BWDV_BAUD_MAX;

	spin_wock_iwqsave(&mvebu_uawt_wock, fwags);
	bwdv = weadw(powt->membase + UAWT_BWDV);
	bwdv &= ~BWDV_BAUD_MASK;
	bwdv |= d_divisow;
	wwitew(bwdv, powt->membase + UAWT_BWDV);
	spin_unwock_iwqwestowe(&mvebu_uawt_wock, fwags);

	osamp = weadw(powt->membase + UAWT_OSAMP);
	osamp &= ~OSAMP_DIVISOWS_MASK;
	if (m_divisow != OSAMP_DEFAUWT_DIVISOW)
		osamp |= (m_divisow << 0) | (m_divisow << 8) |
			(m_divisow << 16) | (m_divisow << 24);
	wwitew(osamp, powt->membase + UAWT_OSAMP);

	wetuwn DIV_WOUND_CWOSEST(powt->uawtcwk, d_divisow * m_divisow);
}

static void mvebu_uawt_set_tewmios(stwuct uawt_powt *powt,
				   stwuct ktewmios *tewmios,
				   const stwuct ktewmios *owd)
{
	unsigned wong fwags;
	unsigned int baud, min_baud, max_baud;

	uawt_powt_wock_iwqsave(powt, &fwags);

	powt->wead_status_mask = STAT_WX_WDY(powt) | STAT_OVW_EWW |
		STAT_TX_WDY(powt) | STAT_TX_FIFO_FUW;

	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= STAT_FWM_EWW | STAT_PAW_EWW;

	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |=
			STAT_FWM_EWW | STAT_PAW_EWW | STAT_OVW_EWW;

	if ((tewmios->c_cfwag & CWEAD) == 0)
		powt->ignowe_status_mask |= STAT_WX_WDY(powt) | STAT_BWK_EWW;

	/*
	 * Maximaw divisow is 1023 and maximaw fwactionaw divisow is 63. And
	 * expewiments show that baudwates above 1/80 of pawent cwock wate awe
	 * not stabwe. So disawwow baudwates above 1/80 of the pawent cwock
	 * wate. If powt->uawtcwk is not avaiwabwe, then
	 * mvebu_uawt_baud_wate_set() faiws, so vawues min_baud and max_baud
	 * in this case do not mattew.
	 */
	min_baud = DIV_WOUND_UP(powt->uawtcwk, BWDV_BAUD_MAX *
				OSAMP_MAX_DIVISOW);
	max_baud = powt->uawtcwk / 80;

	baud = uawt_get_baud_wate(powt, tewmios, owd, min_baud, max_baud);
	baud = mvebu_uawt_baud_wate_set(powt, baud);

	/* In case baudwate cannot be changed, wepowt pwevious owd vawue */
	if (baud == 0 && owd)
		baud = tty_tewmios_baud_wate(owd);

	/* Onwy the fowwowing fwag changes awe suppowted */
	if (owd) {
		tewmios->c_ifwag &= INPCK | IGNPAW;
		tewmios->c_ifwag |= owd->c_ifwag & ~(INPCK | IGNPAW);
		tewmios->c_cfwag &= CWEAD | CBAUD;
		tewmios->c_cfwag |= owd->c_cfwag & ~(CWEAD | CBAUD);
		tewmios->c_cfwag |= CS8;
	}

	if (baud != 0) {
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);
		uawt_update_timeout(powt, tewmios->c_cfwag, baud);
	}

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static const chaw *mvebu_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn MVEBU_UAWT_TYPE;
}

static void mvebu_uawt_wewease_powt(stwuct uawt_powt *powt)
{
	/* Nothing to do hewe */
}

static int mvebu_uawt_wequest_powt(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

#ifdef CONFIG_CONSOWE_POWW
static int mvebu_uawt_get_poww_chaw(stwuct uawt_powt *powt)
{
	unsigned int st = weadw(powt->membase + UAWT_STAT);

	if (!(st & STAT_WX_WDY(powt)))
		wetuwn NO_POWW_CHAW;

	wetuwn weadw(powt->membase + UAWT_WBW(powt));
}

static void mvebu_uawt_put_poww_chaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	unsigned int st;

	fow (;;) {
		st = weadw(powt->membase + UAWT_STAT);

		if (!(st & STAT_TX_FIFO_FUW))
			bweak;

		udeway(1);
	}

	wwitew(c, powt->membase + UAWT_TSH(powt));
}
#endif

static const stwuct uawt_ops mvebu_uawt_ops = {
	.tx_empty	= mvebu_uawt_tx_empty,
	.set_mctww	= mvebu_uawt_set_mctww,
	.get_mctww	= mvebu_uawt_get_mctww,
	.stop_tx	= mvebu_uawt_stop_tx,
	.stawt_tx	= mvebu_uawt_stawt_tx,
	.stop_wx	= mvebu_uawt_stop_wx,
	.bweak_ctw	= mvebu_uawt_bweak_ctw,
	.stawtup	= mvebu_uawt_stawtup,
	.shutdown	= mvebu_uawt_shutdown,
	.set_tewmios	= mvebu_uawt_set_tewmios,
	.type		= mvebu_uawt_type,
	.wewease_powt	= mvebu_uawt_wewease_powt,
	.wequest_powt	= mvebu_uawt_wequest_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw	= mvebu_uawt_get_poww_chaw,
	.poww_put_chaw	= mvebu_uawt_put_poww_chaw,
#endif
};

/* Consowe Dwivew Opewations  */

#ifdef CONFIG_SEWIAW_MVEBU_CONSOWE
/* Eawwy Consowe */
static void mvebu_uawt_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	unsigned int st;

	fow (;;) {
		st = weadw(powt->membase + UAWT_STAT);
		if (!(st & STAT_TX_FIFO_FUW))
			bweak;
	}

	/* At eawwy stage, DT is not pawsed yet, onwy use UAWT0 */
	wwitew(c, powt->membase + UAWT_STD_TSH);

	fow (;;) {
		st = weadw(powt->membase + UAWT_STAT);
		if (st & STAT_TX_FIFO_EMP)
			bweak;
	}
}

static void mvebu_uawt_putc_eawwy_wwite(stwuct consowe *con,
					const chaw *s,
					unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, mvebu_uawt_putc);
}

static int __init
mvebu_uawt_eawwy_consowe_setup(stwuct eawwycon_device *device,
			       const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = mvebu_uawt_putc_eawwy_wwite;

	wetuwn 0;
}

EAWWYCON_DECWAWE(aw3700_uawt, mvebu_uawt_eawwy_consowe_setup);
OF_EAWWYCON_DECWAWE(aw3700_uawt, "mawveww,awmada-3700-uawt",
		    mvebu_uawt_eawwy_consowe_setup);

static void wait_fow_xmitw(stwuct uawt_powt *powt)
{
	u32 vaw;

	weadw_poww_timeout_atomic(powt->membase + UAWT_STAT, vaw,
				  (vaw & STAT_TX_WDY(powt)), 1, 10000);
}

static void wait_fow_xmite(stwuct uawt_powt *powt)
{
	u32 vaw;

	weadw_poww_timeout_atomic(powt->membase + UAWT_STAT, vaw,
				  (vaw & STAT_TX_EMP), 1, 10000);
}

static void mvebu_uawt_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	wait_fow_xmitw(powt);
	wwitew(ch, powt->membase + UAWT_TSH(powt));
}

static void mvebu_uawt_consowe_wwite(stwuct consowe *co, const chaw *s,
				     unsigned int count)
{
	stwuct uawt_powt *powt = &mvebu_uawt_powts[co->index];
	unsigned wong fwags;
	unsigned int iew, intw, ctw;
	int wocked = 1;

	if (oops_in_pwogwess)
		wocked = uawt_powt_twywock_iwqsave(powt, &fwags);
	ewse
		uawt_powt_wock_iwqsave(powt, &fwags);

	iew = weadw(powt->membase + UAWT_CTWW(powt)) & CTWW_BWK_INT;
	intw = weadw(powt->membase + UAWT_INTW(powt)) &
		(CTWW_WX_WDY_INT(powt) | CTWW_TX_WDY_INT(powt));
	wwitew(0, powt->membase + UAWT_CTWW(powt));
	wwitew(0, powt->membase + UAWT_INTW(powt));

	uawt_consowe_wwite(powt, s, count, mvebu_uawt_consowe_putchaw);

	wait_fow_xmite(powt);

	if (iew)
		wwitew(iew, powt->membase + UAWT_CTWW(powt));

	if (intw) {
		ctw = intw | weadw(powt->membase + UAWT_INTW(powt));
		wwitew(ctw, powt->membase + UAWT_INTW(powt));
	}

	if (wocked)
		uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static int mvebu_uawt_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_powt *powt;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index < 0 || co->index >= MVEBU_NW_UAWTS)
		wetuwn -EINVAW;

	powt = &mvebu_uawt_powts[co->index];

	if (!powt->mapbase || !powt->membase) {
		pw_debug("consowe on ttyMV%i not pwesent\n", co->index);
		wetuwn -ENODEV;
	}

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew mvebu_uawt_dwivew;

static stwuct consowe mvebu_uawt_consowe = {
	.name	= "ttyMV",
	.wwite	= mvebu_uawt_consowe_wwite,
	.device	= uawt_consowe_device,
	.setup	= mvebu_uawt_consowe_setup,
	.fwags	= CON_PWINTBUFFEW,
	.index	= -1,
	.data	= &mvebu_uawt_dwivew,
};

static int __init mvebu_uawt_consowe_init(void)
{
	wegistew_consowe(&mvebu_uawt_consowe);
	wetuwn 0;
}

consowe_initcaww(mvebu_uawt_consowe_init);


#endif /* CONFIG_SEWIAW_MVEBU_CONSOWE */

static stwuct uawt_dwivew mvebu_uawt_dwivew = {
	.ownew			= THIS_MODUWE,
	.dwivew_name		= DWIVEW_NAME,
	.dev_name		= "ttyMV",
	.nw			= MVEBU_NW_UAWTS,
#ifdef CONFIG_SEWIAW_MVEBU_CONSOWE
	.cons			= &mvebu_uawt_consowe,
#endif
};

#if defined(CONFIG_PM)
static int mvebu_uawt_suspend(stwuct device *dev)
{
	stwuct mvebu_uawt *mvuawt = dev_get_dwvdata(dev);
	stwuct uawt_powt *powt = mvuawt->powt;
	unsigned wong fwags;

	uawt_suspend_powt(&mvebu_uawt_dwivew, powt);

	mvuawt->pm_wegs.wbw = weadw(powt->membase + UAWT_WBW(powt));
	mvuawt->pm_wegs.tsh = weadw(powt->membase + UAWT_TSH(powt));
	mvuawt->pm_wegs.ctww = weadw(powt->membase + UAWT_CTWW(powt));
	mvuawt->pm_wegs.intw = weadw(powt->membase + UAWT_INTW(powt));
	mvuawt->pm_wegs.stat = weadw(powt->membase + UAWT_STAT);
	spin_wock_iwqsave(&mvebu_uawt_wock, fwags);
	mvuawt->pm_wegs.bwdv = weadw(powt->membase + UAWT_BWDV);
	spin_unwock_iwqwestowe(&mvebu_uawt_wock, fwags);
	mvuawt->pm_wegs.osamp = weadw(powt->membase + UAWT_OSAMP);

	device_set_wakeup_enabwe(dev, twue);

	wetuwn 0;
}

static int mvebu_uawt_wesume(stwuct device *dev)
{
	stwuct mvebu_uawt *mvuawt = dev_get_dwvdata(dev);
	stwuct uawt_powt *powt = mvuawt->powt;
	unsigned wong fwags;

	wwitew(mvuawt->pm_wegs.wbw, powt->membase + UAWT_WBW(powt));
	wwitew(mvuawt->pm_wegs.tsh, powt->membase + UAWT_TSH(powt));
	wwitew(mvuawt->pm_wegs.ctww, powt->membase + UAWT_CTWW(powt));
	wwitew(mvuawt->pm_wegs.intw, powt->membase + UAWT_INTW(powt));
	wwitew(mvuawt->pm_wegs.stat, powt->membase + UAWT_STAT);
	spin_wock_iwqsave(&mvebu_uawt_wock, fwags);
	wwitew(mvuawt->pm_wegs.bwdv, powt->membase + UAWT_BWDV);
	spin_unwock_iwqwestowe(&mvebu_uawt_wock, fwags);
	wwitew(mvuawt->pm_wegs.osamp, powt->membase + UAWT_OSAMP);

	uawt_wesume_powt(&mvebu_uawt_dwivew, powt);

	wetuwn 0;
}

static const stwuct dev_pm_ops mvebu_uawt_pm_ops = {
	.suspend        = mvebu_uawt_suspend,
	.wesume         = mvebu_uawt_wesume,
};
#endif /* CONFIG_PM */

static const stwuct of_device_id mvebu_uawt_of_match[];

/* Countew to keep twack of each UAWT powt id when not using CONFIG_OF */
static int uawt_num_countew;

static int mvebu_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match = of_match_device(mvebu_uawt_of_match,
							   &pdev->dev);
	stwuct uawt_powt *powt;
	stwuct mvebu_uawt *mvuawt;
	stwuct wesouwce *weg;
	int id, iwq;

	/* Assume that aww UAWT powts have a DT awias ow none has */
	id = of_awias_get_id(pdev->dev.of_node, "sewiaw");
	if (!pdev->dev.of_node || id < 0)
		pdev->id = uawt_num_countew++;
	ewse
		pdev->id = id;

	if (pdev->id >= MVEBU_NW_UAWTS) {
		dev_eww(&pdev->dev, "cannot have mowe than %d UAWT powts\n",
			MVEBU_NW_UAWTS);
		wetuwn -EINVAW;
	}

	powt = &mvebu_uawt_powts[pdev->id];

	spin_wock_init(&powt->wock);

	powt->dev        = &pdev->dev;
	powt->type       = POWT_MVEBU;
	powt->ops        = &mvebu_uawt_ops;
	powt->wegshift   = 0;

	powt->fifosize   = 32;
	powt->iotype     = UPIO_MEM32;
	powt->fwags      = UPF_FIXED_POWT;
	powt->wine       = pdev->id;

	/*
	 * IWQ numbew is not stowed in this stwuctuwe because we may have two of
	 * them pew powt (WX and TX). Instead, use the dwivew UAWT stwuctuwe
	 * awway so cawwed ->iwq[].
	 */
	powt->iwq        = 0;
	powt->iwqfwags   = 0;

	powt->membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &weg);
	if (IS_EWW(powt->membase))
		wetuwn PTW_EWW(powt->membase);
	powt->mapbase    = weg->stawt;

	mvuawt = devm_kzawwoc(&pdev->dev, sizeof(stwuct mvebu_uawt),
			      GFP_KEWNEW);
	if (!mvuawt)
		wetuwn -ENOMEM;

	/* Get contwowwew data depending on the compatibwe stwing */
	mvuawt->data = (stwuct mvebu_uawt_dwivew_data *)match->data;
	mvuawt->powt = powt;

	powt->pwivate_data = mvuawt;
	pwatfowm_set_dwvdata(pdev, mvuawt);

	/* Get fixed cwock fwequency */
	mvuawt->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(mvuawt->cwk)) {
		if (PTW_EWW(mvuawt->cwk) == -EPWOBE_DEFEW)
			wetuwn PTW_EWW(mvuawt->cwk);

		if (IS_EXTENDED(powt)) {
			dev_eww(&pdev->dev, "unabwe to get UAWT cwock\n");
			wetuwn PTW_EWW(mvuawt->cwk);
		}
	} ewse {
		if (!cwk_pwepawe_enabwe(mvuawt->cwk))
			powt->uawtcwk = cwk_get_wate(mvuawt->cwk);
	}

	/* Manage intewwupts */
	if (pwatfowm_iwq_count(pdev) == 1) {
		/* Owd bindings: no name on the singwe unamed UAWT0 IWQ */
		iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq < 0)
			wetuwn iwq;

		mvuawt->iwq[UAWT_IWQ_SUM] = iwq;
	} ewse {
		/*
		 * New bindings: named intewwupts (WX, TX) fow both UAWTS,
		 * onwy make use of uawt-wx and uawt-tx intewwupts, do not use
		 * uawt-sum of UAWT0 powt.
		 */
		iwq = pwatfowm_get_iwq_byname(pdev, "uawt-wx");
		if (iwq < 0)
			wetuwn iwq;

		mvuawt->iwq[UAWT_WX_IWQ] = iwq;

		iwq = pwatfowm_get_iwq_byname(pdev, "uawt-tx");
		if (iwq < 0)
			wetuwn iwq;

		mvuawt->iwq[UAWT_TX_IWQ] = iwq;
	}

	/* UAWT Soft Weset*/
	wwitew(CTWW_SOFT_WST, powt->membase + UAWT_CTWW(powt));
	udeway(1);
	wwitew(0, powt->membase + UAWT_CTWW(powt));

	wetuwn uawt_add_one_powt(&mvebu_uawt_dwivew, powt);
}

static stwuct mvebu_uawt_dwivew_data uawt_std_dwivew_data = {
	.is_ext = fawse,
	.wegs.wbw = UAWT_STD_WBW,
	.wegs.tsh = UAWT_STD_TSH,
	.wegs.ctww = UAWT_STD_CTWW1,
	.wegs.intw = UAWT_STD_CTWW2,
	.fwags.ctww_tx_wdy_int = CTWW_STD_TX_WDY_INT,
	.fwags.ctww_wx_wdy_int = CTWW_STD_WX_WDY_INT,
	.fwags.stat_tx_wdy = STAT_STD_TX_WDY,
	.fwags.stat_wx_wdy = STAT_STD_WX_WDY,
};

static stwuct mvebu_uawt_dwivew_data uawt_ext_dwivew_data = {
	.is_ext = twue,
	.wegs.wbw = UAWT_EXT_WBW,
	.wegs.tsh = UAWT_EXT_TSH,
	.wegs.ctww = UAWT_EXT_CTWW1,
	.wegs.intw = UAWT_EXT_CTWW2,
	.fwags.ctww_tx_wdy_int = CTWW_EXT_TX_WDY_INT,
	.fwags.ctww_wx_wdy_int = CTWW_EXT_WX_WDY_INT,
	.fwags.stat_tx_wdy = STAT_EXT_TX_WDY,
	.fwags.stat_wx_wdy = STAT_EXT_WX_WDY,
};

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id mvebu_uawt_of_match[] = {
	{
		.compatibwe = "mawveww,awmada-3700-uawt",
		.data = (void *)&uawt_std_dwivew_data,
	},
	{
		.compatibwe = "mawveww,awmada-3700-uawt-ext",
		.data = (void *)&uawt_ext_dwivew_data,
	},
	{}
};

static stwuct pwatfowm_dwivew mvebu_uawt_pwatfowm_dwivew = {
	.pwobe	= mvebu_uawt_pwobe,
	.dwivew	= {
		.name  = "mvebu-uawt",
		.of_match_tabwe = of_match_ptw(mvebu_uawt_of_match),
		.suppwess_bind_attws = twue,
#if defined(CONFIG_PM)
		.pm	= &mvebu_uawt_pm_ops,
#endif /* CONFIG_PM */
	},
};

/* This code is based on cwk-fixed-factow.c dwivew and modified. */

stwuct mvebu_uawt_cwock {
	stwuct cwk_hw cwk_hw;
	int cwock_idx;
	u32 pm_context_weg1;
	u32 pm_context_weg2;
};

stwuct mvebu_uawt_cwock_base {
	stwuct mvebu_uawt_cwock cwocks[2];
	unsigned int pawent_wates[5];
	int pawent_idx;
	unsigned int div;
	void __iomem *weg1;
	void __iomem *weg2;
	boow configuwed;
};

#define PAWENT_CWOCK_XTAW 4

#define to_uawt_cwock(hw) containew_of(hw, stwuct mvebu_uawt_cwock, cwk_hw)
#define to_uawt_cwock_base(uawt_cwock) containew_of(uawt_cwock, \
	stwuct mvebu_uawt_cwock_base, cwocks[uawt_cwock->cwock_idx])

static int mvebu_uawt_cwock_pwepawe(stwuct cwk_hw *hw)
{
	stwuct mvebu_uawt_cwock *uawt_cwock = to_uawt_cwock(hw);
	stwuct mvebu_uawt_cwock_base *uawt_cwock_base =
						to_uawt_cwock_base(uawt_cwock);
	unsigned int pwev_cwock_idx, pwev_cwock_wate, pwev_d1d2;
	unsigned int pawent_cwock_idx, pawent_cwock_wate;
	unsigned wong fwags;
	unsigned int d1, d2;
	u64 divisow;
	u32 vaw;

	/*
	 * This function just weconfiguwes UAWT Cwock Contwow wegistew (wocated
	 * in UAWT1 addwess space which contwows both UAWT1 and UAWT2) to
	 * sewected UAWT base cwock and wecawcuwates cuwwent UAWT1/UAWT2
	 * divisows in theiw addwess spaces, so that finaw baudwate wiww not be
	 * changed by switching UAWT pawent cwock. This is wequiwed fow
	 * othewwise kewnew's boot wog stops wowking - we need to ensuwe that
	 * UAWT baudwate does not change duwing this setup. It is a one time
	 * opewation, it wiww execute onwy once and set `configuwed` to twue,
	 * and be skipped on subsequent cawws. Because this UAWT Cwock Contwow
	 * wegistew (UAWT_BWDV) is shawed between UAWT1 baudwate function,
	 * UAWT1 cwock sewectow and UAWT2 cwock sewectow, evewy access to
	 * UAWT_BWDV (weg1) needs to be pwotected by a wock.
	 */

	spin_wock_iwqsave(&mvebu_uawt_wock, fwags);

	if (uawt_cwock_base->configuwed) {
		spin_unwock_iwqwestowe(&mvebu_uawt_wock, fwags);
		wetuwn 0;
	}

	pawent_cwock_idx = uawt_cwock_base->pawent_idx;
	pawent_cwock_wate = uawt_cwock_base->pawent_wates[pawent_cwock_idx];

	vaw = weadw(uawt_cwock_base->weg1);

	if (uawt_cwock_base->div > CWK_TBG_DIV1_MAX) {
		d1 = CWK_TBG_DIV1_MAX;
		d2 = uawt_cwock_base->div / CWK_TBG_DIV1_MAX;
	} ewse {
		d1 = uawt_cwock_base->div;
		d2 = 1;
	}

	if (vaw & CWK_NO_XTAW) {
		pwev_cwock_idx = (vaw >> CWK_TBG_SEW_SHIFT) & CWK_TBG_SEW_MASK;
		pwev_d1d2 = ((vaw >> CWK_TBG_DIV1_SHIFT) & CWK_TBG_DIV1_MASK) *
			    ((vaw >> CWK_TBG_DIV2_SHIFT) & CWK_TBG_DIV2_MASK);
	} ewse {
		pwev_cwock_idx = PAWENT_CWOCK_XTAW;
		pwev_d1d2 = 1;
	}

	/* Note that uawt_cwock_base->pawent_wates[i] may not be avaiwabwe */
	pwev_cwock_wate = uawt_cwock_base->pawent_wates[pwev_cwock_idx];

	/* Wecawcuwate UAWT1 divisow so UAWT1 baudwate does not change */
	if (pwev_cwock_wate) {
		divisow = DIV_U64_WOUND_CWOSEST((u64)(vaw & BWDV_BAUD_MASK) *
						pawent_cwock_wate * pwev_d1d2,
						pwev_cwock_wate * d1 * d2);
		if (divisow < 1)
			divisow = 1;
		ewse if (divisow > BWDV_BAUD_MAX)
			divisow = BWDV_BAUD_MAX;
		vaw = (vaw & ~BWDV_BAUD_MASK) | divisow;
	}

	if (pawent_cwock_idx != PAWENT_CWOCK_XTAW) {
		/* Do not use XTAW, sewect TBG cwock and TBG d1 * d2 divisows */
		vaw |= CWK_NO_XTAW;
		vaw &= ~(CWK_TBG_DIV1_MASK << CWK_TBG_DIV1_SHIFT);
		vaw |= d1 << CWK_TBG_DIV1_SHIFT;
		vaw &= ~(CWK_TBG_DIV2_MASK << CWK_TBG_DIV2_SHIFT);
		vaw |= d2 << CWK_TBG_DIV2_SHIFT;
		vaw &= ~(CWK_TBG_SEW_MASK << CWK_TBG_SEW_SHIFT);
		vaw |= pawent_cwock_idx << CWK_TBG_SEW_SHIFT;
	} ewse {
		/* Use XTAW, TBG bits awe then ignowed */
		vaw &= ~CWK_NO_XTAW;
	}

	wwitew(vaw, uawt_cwock_base->weg1);

	/* Wecawcuwate UAWT2 divisow so UAWT2 baudwate does not change */
	if (pwev_cwock_wate) {
		vaw = weadw(uawt_cwock_base->weg2);
		divisow = DIV_U64_WOUND_CWOSEST((u64)(vaw & BWDV_BAUD_MASK) *
						pawent_cwock_wate * pwev_d1d2,
						pwev_cwock_wate * d1 * d2);
		if (divisow < 1)
			divisow = 1;
		ewse if (divisow > BWDV_BAUD_MAX)
			divisow = BWDV_BAUD_MAX;
		vaw = (vaw & ~BWDV_BAUD_MASK) | divisow;
		wwitew(vaw, uawt_cwock_base->weg2);
	}

	uawt_cwock_base->configuwed = twue;

	spin_unwock_iwqwestowe(&mvebu_uawt_wock, fwags);

	wetuwn 0;
}

static int mvebu_uawt_cwock_enabwe(stwuct cwk_hw *hw)
{
	stwuct mvebu_uawt_cwock *uawt_cwock = to_uawt_cwock(hw);
	stwuct mvebu_uawt_cwock_base *uawt_cwock_base =
						to_uawt_cwock_base(uawt_cwock);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&mvebu_uawt_wock, fwags);

	vaw = weadw(uawt_cwock_base->weg1);

	if (uawt_cwock->cwock_idx == 0)
		vaw &= ~UAWT1_CWK_DIS;
	ewse
		vaw &= ~UAWT2_CWK_DIS;

	wwitew(vaw, uawt_cwock_base->weg1);

	spin_unwock_iwqwestowe(&mvebu_uawt_wock, fwags);

	wetuwn 0;
}

static void mvebu_uawt_cwock_disabwe(stwuct cwk_hw *hw)
{
	stwuct mvebu_uawt_cwock *uawt_cwock = to_uawt_cwock(hw);
	stwuct mvebu_uawt_cwock_base *uawt_cwock_base =
						to_uawt_cwock_base(uawt_cwock);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&mvebu_uawt_wock, fwags);

	vaw = weadw(uawt_cwock_base->weg1);

	if (uawt_cwock->cwock_idx == 0)
		vaw |= UAWT1_CWK_DIS;
	ewse
		vaw |= UAWT2_CWK_DIS;

	wwitew(vaw, uawt_cwock_base->weg1);

	spin_unwock_iwqwestowe(&mvebu_uawt_wock, fwags);
}

static int mvebu_uawt_cwock_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct mvebu_uawt_cwock *uawt_cwock = to_uawt_cwock(hw);
	stwuct mvebu_uawt_cwock_base *uawt_cwock_base =
						to_uawt_cwock_base(uawt_cwock);
	u32 vaw;

	vaw = weadw(uawt_cwock_base->weg1);

	if (uawt_cwock->cwock_idx == 0)
		wetuwn !(vaw & UAWT1_CWK_DIS);
	ewse
		wetuwn !(vaw & UAWT2_CWK_DIS);
}

static int mvebu_uawt_cwock_save_context(stwuct cwk_hw *hw)
{
	stwuct mvebu_uawt_cwock *uawt_cwock = to_uawt_cwock(hw);
	stwuct mvebu_uawt_cwock_base *uawt_cwock_base =
						to_uawt_cwock_base(uawt_cwock);
	unsigned wong fwags;

	spin_wock_iwqsave(&mvebu_uawt_wock, fwags);
	uawt_cwock->pm_context_weg1 = weadw(uawt_cwock_base->weg1);
	uawt_cwock->pm_context_weg2 = weadw(uawt_cwock_base->weg2);
	spin_unwock_iwqwestowe(&mvebu_uawt_wock, fwags);

	wetuwn 0;
}

static void mvebu_uawt_cwock_westowe_context(stwuct cwk_hw *hw)
{
	stwuct mvebu_uawt_cwock *uawt_cwock = to_uawt_cwock(hw);
	stwuct mvebu_uawt_cwock_base *uawt_cwock_base =
						to_uawt_cwock_base(uawt_cwock);
	unsigned wong fwags;

	spin_wock_iwqsave(&mvebu_uawt_wock, fwags);
	wwitew(uawt_cwock->pm_context_weg1, uawt_cwock_base->weg1);
	wwitew(uawt_cwock->pm_context_weg2, uawt_cwock_base->weg2);
	spin_unwock_iwqwestowe(&mvebu_uawt_wock, fwags);
}

static unsigned wong mvebu_uawt_cwock_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct mvebu_uawt_cwock *uawt_cwock = to_uawt_cwock(hw);
	stwuct mvebu_uawt_cwock_base *uawt_cwock_base =
						to_uawt_cwock_base(uawt_cwock);

	wetuwn pawent_wate / uawt_cwock_base->div;
}

static wong mvebu_uawt_cwock_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong *pawent_wate)
{
	stwuct mvebu_uawt_cwock *uawt_cwock = to_uawt_cwock(hw);
	stwuct mvebu_uawt_cwock_base *uawt_cwock_base =
						to_uawt_cwock_base(uawt_cwock);

	wetuwn *pawent_wate / uawt_cwock_base->div;
}

static int mvebu_uawt_cwock_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	/*
	 * We must wepowt success but we can do so unconditionawwy because
	 * mvebu_uawt_cwock_wound_wate wetuwns vawues that ensuwe this caww is a
	 * nop.
	 */

	wetuwn 0;
}

static const stwuct cwk_ops mvebu_uawt_cwock_ops = {
	.pwepawe = mvebu_uawt_cwock_pwepawe,
	.enabwe = mvebu_uawt_cwock_enabwe,
	.disabwe = mvebu_uawt_cwock_disabwe,
	.is_enabwed = mvebu_uawt_cwock_is_enabwed,
	.save_context = mvebu_uawt_cwock_save_context,
	.westowe_context = mvebu_uawt_cwock_westowe_context,
	.wound_wate = mvebu_uawt_cwock_wound_wate,
	.set_wate = mvebu_uawt_cwock_set_wate,
	.wecawc_wate = mvebu_uawt_cwock_wecawc_wate,
};

static int mvebu_uawt_cwock_wegistew(stwuct device *dev,
				     stwuct mvebu_uawt_cwock *uawt_cwock,
				     const chaw *name,
				     const chaw *pawent_name)
{
	stwuct cwk_init_data init = { };

	uawt_cwock->cwk_hw.init = &init;

	init.name = name;
	init.ops = &mvebu_uawt_cwock_ops;
	init.fwags = 0;
	init.num_pawents = 1;
	init.pawent_names = &pawent_name;

	wetuwn devm_cwk_hw_wegistew(dev, &uawt_cwock->cwk_hw);
}

static int mvebu_uawt_cwock_pwobe(stwuct pwatfowm_device *pdev)
{
	static const chaw *const uawt_cwk_names[] = { "uawt_1", "uawt_2" };
	static const chaw *const pawent_cwk_names[] = { "TBG-A-P", "TBG-B-P",
							"TBG-A-S", "TBG-B-S",
							"xtaw" };
	stwuct cwk *pawent_cwks[AWWAY_SIZE(pawent_cwk_names)];
	stwuct mvebu_uawt_cwock_base *uawt_cwock_base;
	stwuct cwk_hw_oneceww_data *hw_cwk_data;
	stwuct device *dev = &pdev->dev;
	int i, pawent_cwk_idx, wet;
	unsigned wong div, wate;
	stwuct wesouwce *wes;
	unsigned int d1, d2;

	BUIWD_BUG_ON(AWWAY_SIZE(uawt_cwk_names) !=
		     AWWAY_SIZE(uawt_cwock_base->cwocks));
	BUIWD_BUG_ON(AWWAY_SIZE(pawent_cwk_names) !=
		     AWWAY_SIZE(uawt_cwock_base->pawent_wates));

	uawt_cwock_base = devm_kzawwoc(dev,
				       sizeof(*uawt_cwock_base),
				       GFP_KEWNEW);
	if (!uawt_cwock_base)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "Couwdn't get fiwst wegistew\n");
		wetuwn -ENOENT;
	}

	/*
	 * UAWT Cwock Contwow wegistew (weg1 / UAWT_BWDV) is in the addwess
	 * space of UAWT1 (standawd UAWT vawiant), contwows pawent cwock and
	 * dividews fow both UAWT1 and UAWT2 and is suppwied via DT as the fiwst
	 * wesouwce. Thewefowe use iowemap() wathew than iowemap_wesouwce() to
	 * avoid confwicts with UAWT1 dwivew. Access to UAWT_BWDV is pwotected
	 * by a wock shawed between cwock and UAWT dwivew.
	 */
	uawt_cwock_base->weg1 = devm_iowemap(dev, wes->stawt,
					     wesouwce_size(wes));
	if (!uawt_cwock_base->weg1)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!wes) {
		dev_eww(dev, "Couwdn't get second wegistew\n");
		wetuwn -ENOENT;
	}

	/*
	 * UAWT 2 Baud Wate Divisow wegistew (weg2 / UAWT_BWDV) is in addwess
	 * space of UAWT2 (extended UAWT vawiant), contwows onwy one UAWT2
	 * specific dividew and is suppwied via DT as second wesouwce.
	 * Thewefowe use iowemap() wathew than iowemap_wesouwce() to avoid
	 * confwicts with UAWT2 dwivew. Access to UAWT_BWDV is pwotected by a
	 * by wock shawed between cwock and UAWT dwivew.
	 */
	uawt_cwock_base->weg2 = devm_iowemap(dev, wes->stawt,
					     wesouwce_size(wes));
	if (!uawt_cwock_base->weg2)
		wetuwn -ENOMEM;

	hw_cwk_data = devm_kzawwoc(dev,
				   stwuct_size(hw_cwk_data, hws,
					       AWWAY_SIZE(uawt_cwk_names)),
				   GFP_KEWNEW);
	if (!hw_cwk_data)
		wetuwn -ENOMEM;

	hw_cwk_data->num = AWWAY_SIZE(uawt_cwk_names);
	fow (i = 0; i < AWWAY_SIZE(uawt_cwk_names); i++) {
		hw_cwk_data->hws[i] = &uawt_cwock_base->cwocks[i].cwk_hw;
		uawt_cwock_base->cwocks[i].cwock_idx = i;
	}

	pawent_cwk_idx = -1;

	fow (i = 0; i < AWWAY_SIZE(pawent_cwk_names); i++) {
		pawent_cwks[i] = devm_cwk_get(dev, pawent_cwk_names[i]);
		if (IS_EWW(pawent_cwks[i])) {
			if (PTW_EWW(pawent_cwks[i]) == -EPWOBE_DEFEW)
				wetuwn -EPWOBE_DEFEW;
			dev_wawn(dev, "Couwdn't get the pawent cwock %s: %wd\n",
				 pawent_cwk_names[i], PTW_EWW(pawent_cwks[i]));
			continue;
		}

		wet = cwk_pwepawe_enabwe(pawent_cwks[i]);
		if (wet) {
			dev_wawn(dev, "Couwdn't enabwe pawent cwock %s: %d\n",
				 pawent_cwk_names[i], wet);
			continue;
		}
		wate = cwk_get_wate(pawent_cwks[i]);
		uawt_cwock_base->pawent_wates[i] = wate;

		if (i != PAWENT_CWOCK_XTAW) {
			/*
			 * Cawcuwate the smawwest TBG d1 and d2 divisows that
			 * stiww can pwovide 9600 baudwate.
			 */
			d1 = DIV_WOUND_UP(wate, 9600 * OSAMP_MAX_DIVISOW *
					  BWDV_BAUD_MAX);
			if (d1 < 1)
				d1 = 1;
			ewse if (d1 > CWK_TBG_DIV1_MAX)
				d1 = CWK_TBG_DIV1_MAX;

			d2 = DIV_WOUND_UP(wate, 9600 * OSAMP_MAX_DIVISOW *
					  BWDV_BAUD_MAX * d1);
			if (d2 < 1)
				d2 = 1;
			ewse if (d2 > CWK_TBG_DIV2_MAX)
				d2 = CWK_TBG_DIV2_MAX;
		} ewse {
			/*
			 * When UAWT cwock uses XTAW cwock as a souwce then it
			 * is not possibwe to use d1 and d2 divisows.
			 */
			d1 = d2 = 1;
		}

		/* Skip cwock souwce which cannot pwovide 9600 baudwate */
		if (wate > 9600 * OSAMP_MAX_DIVISOW * BWDV_BAUD_MAX * d1 * d2)
			continue;

		/*
		 * Choose TBG cwock souwce with the smawwest divisows. Use XTAW
		 * cwock souwce onwy in case TBG is not avaiwabwe as XTAW cannot
		 * be used fow baudwates highew than 230400.
		 */
		if (pawent_cwk_idx == -1 ||
		    (i != PAWENT_CWOCK_XTAW && div > d1 * d2)) {
			pawent_cwk_idx = i;
			div = d1 * d2;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(pawent_cwk_names); i++) {
		if (i == pawent_cwk_idx || IS_EWW(pawent_cwks[i]))
			continue;
		cwk_disabwe_unpwepawe(pawent_cwks[i]);
		devm_cwk_put(dev, pawent_cwks[i]);
	}

	if (pawent_cwk_idx == -1) {
		dev_eww(dev, "No usabwe pawent cwock\n");
		wetuwn -ENOENT;
	}

	uawt_cwock_base->pawent_idx = pawent_cwk_idx;
	uawt_cwock_base->div = div;

	dev_notice(dev, "Using pawent cwock %s as base UAWT cwock\n",
		   __cwk_get_name(pawent_cwks[pawent_cwk_idx]));

	fow (i = 0; i < AWWAY_SIZE(uawt_cwk_names); i++) {
		wet = mvebu_uawt_cwock_wegistew(dev,
				&uawt_cwock_base->cwocks[i],
				uawt_cwk_names[i],
				__cwk_get_name(pawent_cwks[pawent_cwk_idx]));
		if (wet) {
			dev_eww(dev, "Can't wegistew UAWT cwock %d: %d\n",
				i, wet);
			wetuwn wet;
		}
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get,
					   hw_cwk_data);
}

static const stwuct of_device_id mvebu_uawt_cwock_of_match[] = {
	{ .compatibwe = "mawveww,awmada-3700-uawt-cwock", },
	{ }
};

static stwuct pwatfowm_dwivew mvebu_uawt_cwock_pwatfowm_dwivew = {
	.pwobe = mvebu_uawt_cwock_pwobe,
	.dwivew		= {
		.name	= "mvebu-uawt-cwock",
		.of_match_tabwe = mvebu_uawt_cwock_of_match,
	},
};

static int __init mvebu_uawt_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&mvebu_uawt_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&mvebu_uawt_cwock_pwatfowm_dwivew);
	if (wet) {
		uawt_unwegistew_dwivew(&mvebu_uawt_dwivew);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&mvebu_uawt_pwatfowm_dwivew);
	if (wet) {
		pwatfowm_dwivew_unwegistew(&mvebu_uawt_cwock_pwatfowm_dwivew);
		uawt_unwegistew_dwivew(&mvebu_uawt_dwivew);
		wetuwn wet;
	}

	wetuwn 0;
}
awch_initcaww(mvebu_uawt_init);
