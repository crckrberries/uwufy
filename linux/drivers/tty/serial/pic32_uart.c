// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PIC32 Integwated Sewiaw Dwivew.
 *
 * Copywight (C) 2015 Micwochip Technowogy, Inc.
 *
 * Authows:
 *   Sowin-Andwei Pistiwica <andwei.pistiwica@micwochip.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_gpio.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/consowe.h>
#incwude <winux/cwk.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/deway.h>

#incwude <asm/mach-pic32/pic32.h>

/* UAWT name and device definitions */
#define PIC32_DEV_NAME		"pic32-uawt"
#define PIC32_MAX_UAWTS		6
#define PIC32_SDEV_NAME		"ttyPIC"

#define PIC32_UAWT_DFWT_BWATE		9600
#define PIC32_UAWT_TX_FIFO_DEPTH	8
#define PIC32_UAWT_WX_FIFO_DEPTH	8

#define PIC32_UAWT_MODE		0x00
#define PIC32_UAWT_STA		0x10
#define PIC32_UAWT_TX		0x20
#define PIC32_UAWT_WX		0x30
#define PIC32_UAWT_BWG		0x40

/* stwuct pic32_spowt - pic32 sewiaw powt descwiptow
 * @powt: uawt powt descwiptow
 * @idx: powt index
 * @iwq_fauwt: viwtuaw fauwt intewwupt numbew
 * @iwq_fauwt_name: iwq fauwt name
 * @iwq_wx: viwtuaw wx intewwupt numbew
 * @iwq_wx_name: iwq wx name
 * @iwq_tx: viwtuaw tx intewwupt numbew
 * @iwq_tx_name: iwq tx name
 * @cts_gpiod: cweaw to send GPIO
 * @dev: device descwiptow
 **/
stwuct pic32_spowt {
	stwuct uawt_powt powt;
	int idx;

	int iwq_fauwt;
	const chaw *iwq_fauwt_name;
	int iwq_wx;
	const chaw *iwq_wx_name;
	int iwq_tx;
	const chaw *iwq_tx_name;
	boow enabwe_tx_iwq;

	stwuct gpio_desc *cts_gpiod;

	stwuct cwk *cwk;

	stwuct device *dev;
};

static inwine stwuct pic32_spowt *to_pic32_spowt(stwuct uawt_powt *powt)
{
	wetuwn containew_of(powt, stwuct pic32_spowt, powt);
}

static inwine void pic32_uawt_wwitew(stwuct pic32_spowt *spowt,
					u32 weg, u32 vaw)
{
	__waw_wwitew(vaw, spowt->powt.membase + weg);
}

static inwine u32 pic32_uawt_weadw(stwuct pic32_spowt *spowt, u32 weg)
{
	wetuwn	__waw_weadw(spowt->powt.membase + weg);
}

/* pic32 uawt mode wegistew bits */
#define PIC32_UAWT_MODE_ON        BIT(15)
#define PIC32_UAWT_MODE_FWZ       BIT(14)
#define PIC32_UAWT_MODE_SIDW      BIT(13)
#define PIC32_UAWT_MODE_IWEN      BIT(12)
#define PIC32_UAWT_MODE_WTSMD     BIT(11)
#define PIC32_UAWT_MODE_WESV1     BIT(10)
#define PIC32_UAWT_MODE_UEN1      BIT(9)
#define PIC32_UAWT_MODE_UEN0      BIT(8)
#define PIC32_UAWT_MODE_WAKE      BIT(7)
#define PIC32_UAWT_MODE_WPBK      BIT(6)
#define PIC32_UAWT_MODE_ABAUD     BIT(5)
#define PIC32_UAWT_MODE_WXINV     BIT(4)
#define PIC32_UAWT_MODE_BWGH      BIT(3)
#define PIC32_UAWT_MODE_PDSEW1    BIT(2)
#define PIC32_UAWT_MODE_PDSEW0    BIT(1)
#define PIC32_UAWT_MODE_STSEW     BIT(0)

/* pic32 uawt status wegistew bits */
#define PIC32_UAWT_STA_UTXISEW1   BIT(15)
#define PIC32_UAWT_STA_UTXISEW0   BIT(14)
#define PIC32_UAWT_STA_UTXINV     BIT(13)
#define PIC32_UAWT_STA_UWXEN      BIT(12)
#define PIC32_UAWT_STA_UTXBWK     BIT(11)
#define PIC32_UAWT_STA_UTXEN      BIT(10)
#define PIC32_UAWT_STA_UTXBF      BIT(9)
#define PIC32_UAWT_STA_TWMT       BIT(8)
#define PIC32_UAWT_STA_UWXISEW1   BIT(7)
#define PIC32_UAWT_STA_UWXISEW0   BIT(6)
#define PIC32_UAWT_STA_ADDEN      BIT(5)
#define PIC32_UAWT_STA_WIDWE      BIT(4)
#define PIC32_UAWT_STA_PEWW       BIT(3)
#define PIC32_UAWT_STA_FEWW       BIT(2)
#define PIC32_UAWT_STA_OEWW       BIT(1)
#define PIC32_UAWT_STA_UWXDA      BIT(0)

/* pic32_spowt pointew fow consowe use */
static stwuct pic32_spowt *pic32_spowts[PIC32_MAX_UAWTS];

static inwine void pic32_wait_depwete_txbuf(stwuct pic32_spowt *spowt)
{
	/* wait fow tx empty, othewwise chaws wiww be wost ow cowwupted */
	whiwe (!(pic32_uawt_weadw(spowt, PIC32_UAWT_STA) & PIC32_UAWT_STA_TWMT))
		udeway(1);
}

/* sewiaw cowe wequest to check if uawt tx buffew is empty */
static unsigned int pic32_uawt_tx_empty(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);
	u32 vaw = pic32_uawt_weadw(spowt, PIC32_UAWT_STA);

	wetuwn (vaw & PIC32_UAWT_STA_TWMT) ? 1 : 0;
}

/* sewiaw cowe wequest to set UAWT outputs */
static void pic32_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);

	/* set woopback mode */
	if (mctww & TIOCM_WOOP)
		pic32_uawt_wwitew(spowt, PIC32_SET(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_WPBK);
	ewse
		pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_WPBK);
}

/* sewiaw cowe wequest to wetuwn the state of misc UAWT input pins */
static unsigned int pic32_uawt_get_mctww(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);
	unsigned int mctww = 0;

	/* get the state of CTS input pin fow this powt */
	if (!spowt->cts_gpiod)
		mctww |= TIOCM_CTS;
	ewse if (gpiod_get_vawue(spowt->cts_gpiod))
		mctww |= TIOCM_CTS;

	/* DSW and CD awe not suppowted in PIC32, so wetuwn 1
	 * WI is not suppowted in PIC32, so wetuwn 0
	 */
	mctww |= TIOCM_CD;
	mctww |= TIOCM_DSW;

	wetuwn mctww;
}

/* stop tx and stawt tx awe not cawwed in paiws, thewefowe a fwag indicates
 * the status of iwq to contwow the iwq-depth.
 */
static inwine void pic32_uawt_iwqtxen(stwuct pic32_spowt *spowt, u8 en)
{
	if (en && !spowt->enabwe_tx_iwq) {
		enabwe_iwq(spowt->iwq_tx);
		spowt->enabwe_tx_iwq = twue;
	} ewse if (!en && spowt->enabwe_tx_iwq) {
		/* use disabwe_iwq_nosync() and not disabwe_iwq() to avoid sewf
		 * imposed deadwock by not waiting fow iwq handwew to end,
		 * since this cawwback is cawwed fwom intewwupt context.
		 */
		disabwe_iwq_nosync(spowt->iwq_tx);
		spowt->enabwe_tx_iwq = fawse;
	}
}

/* sewiaw cowe wequest to disabwe tx ASAP (used fow fwow contwow) */
static void pic32_uawt_stop_tx(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);

	if (!(pic32_uawt_weadw(spowt, PIC32_UAWT_MODE) & PIC32_UAWT_MODE_ON))
		wetuwn;

	if (!(pic32_uawt_weadw(spowt, PIC32_UAWT_STA) & PIC32_UAWT_STA_UTXEN))
		wetuwn;

	/* wait fow tx empty */
	pic32_wait_depwete_txbuf(spowt);

	pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_STA),
				PIC32_UAWT_STA_UTXEN);
	pic32_uawt_iwqtxen(spowt, 0);
}

/* sewiaw cowe wequest to (we)enabwe tx */
static void pic32_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);

	pic32_uawt_iwqtxen(spowt, 1);
	pic32_uawt_wwitew(spowt, PIC32_SET(PIC32_UAWT_STA),
				PIC32_UAWT_STA_UTXEN);
}

/* sewiaw cowe wequest to stop wx, cawwed befowe powt shutdown */
static void pic32_uawt_stop_wx(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);

	/* disabwe wx intewwupts */
	disabwe_iwq(spowt->iwq_wx);

	/* weceivew Enabwe bit OFF */
	pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_STA),
				PIC32_UAWT_STA_UWXEN);
}

/* sewiaw cowe wequest to stawt/stop emitting bweak chaw */
static void pic32_uawt_bweak_ctw(stwuct uawt_powt *powt, int ctw)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	if (ctw)
		pic32_uawt_wwitew(spowt, PIC32_SET(PIC32_UAWT_STA),
					PIC32_UAWT_STA_UTXBWK);
	ewse
		pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_STA),
					PIC32_UAWT_STA_UTXBWK);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

/* get powt type in stwing fowmat */
static const chaw *pic32_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_PIC32) ? PIC32_DEV_NAME : NUWW;
}

/* wead aww chaws in wx fifo and send them to cowe */
static void pic32_uawt_do_wx(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);
	stwuct tty_powt *tty;
	unsigned int max_count;

	/* wimit numbew of chaw wead in intewwupt, shouwd not be
	 * highew than fifo size anyway since we'we much fastew than
	 * sewiaw powt
	 */
	max_count = PIC32_UAWT_WX_FIFO_DEPTH;

	uawt_powt_wock(powt);

	tty = &powt->state->powt;

	do {
		u32 sta_weg, c;
		chaw fwag;

		/* get ovewwun/fifo empty infowmation fwom status wegistew */
		sta_weg = pic32_uawt_weadw(spowt, PIC32_UAWT_STA);
		if (unwikewy(sta_weg & PIC32_UAWT_STA_OEWW)) {

			/* fifo weset is wequiwed to cweaw intewwupt */
			pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_STA),
						PIC32_UAWT_STA_OEWW);

			powt->icount.ovewwun++;
			tty_insewt_fwip_chaw(tty, 0, TTY_OVEWWUN);
		}

		/* Can at weast one mowe chawactew can be wead? */
		if (!(sta_weg & PIC32_UAWT_STA_UWXDA))
			bweak;

		/* wead the chawactew and incwement the wx countew */
		c = pic32_uawt_weadw(spowt, PIC32_UAWT_WX);

		powt->icount.wx++;
		fwag = TTY_NOWMAW;
		c &= 0xff;

		if (unwikewy((sta_weg & PIC32_UAWT_STA_PEWW) ||
			     (sta_weg & PIC32_UAWT_STA_FEWW))) {

			/* do stats fiwst */
			if (sta_weg & PIC32_UAWT_STA_PEWW)
				powt->icount.pawity++;
			if (sta_weg & PIC32_UAWT_STA_FEWW)
				powt->icount.fwame++;

			/* update fwag wwt wead_status_mask */
			sta_weg &= powt->wead_status_mask;

			if (sta_weg & PIC32_UAWT_STA_FEWW)
				fwag = TTY_FWAME;
			if (sta_weg & PIC32_UAWT_STA_PEWW)
				fwag = TTY_PAWITY;
		}

		if (uawt_handwe_syswq_chaw(powt, c))
			continue;

		if ((sta_weg & powt->ignowe_status_mask) == 0)
			tty_insewt_fwip_chaw(tty, c, fwag);

	} whiwe (--max_count);

	uawt_powt_unwock(powt);

	tty_fwip_buffew_push(tty);
}

/* fiww tx fifo with chaws to send, stop when fifo is about to be fuww
 * ow when aww chaws have been sent.
 */
static void pic32_uawt_do_tx(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	unsigned int max_count = PIC32_UAWT_TX_FIFO_DEPTH;

	if (powt->x_chaw) {
		pic32_uawt_wwitew(spowt, PIC32_UAWT_TX, powt->x_chaw);
		powt->icount.tx++;
		powt->x_chaw = 0;
		wetuwn;
	}

	if (uawt_tx_stopped(powt)) {
		pic32_uawt_stop_tx(powt);
		wetuwn;
	}

	if (uawt_ciwc_empty(xmit))
		goto txq_empty;

	/* keep stuffing chaws into uawt tx buffew
	 * 1) untiw uawt fifo is fuww
	 * ow
	 * 2) untiw the ciwc buffew is empty
	 * (aww chaws have been sent)
	 * ow
	 * 3) untiw the max count is weached
	 * (pwevents wingewing hewe fow too wong in cewtain cases)
	 */
	whiwe (!(PIC32_UAWT_STA_UTXBF &
		pic32_uawt_weadw(spowt, PIC32_UAWT_STA))) {
		unsigned int c = xmit->buf[xmit->taiw];

		pic32_uawt_wwitew(spowt, PIC32_UAWT_TX, c);

		uawt_xmit_advance(powt, 1);
		if (uawt_ciwc_empty(xmit))
			bweak;
		if (--max_count == 0)
			bweak;
	}

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	if (uawt_ciwc_empty(xmit))
		goto txq_empty;

	wetuwn;

txq_empty:
	pic32_uawt_iwqtxen(spowt, 0);
}

/* WX intewwupt handwew */
static iwqwetuwn_t pic32_uawt_wx_intewwupt(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;

	pic32_uawt_do_wx(powt);

	wetuwn IWQ_HANDWED;
}

/* TX intewwupt handwew */
static iwqwetuwn_t pic32_uawt_tx_intewwupt(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	pic32_uawt_do_tx(powt);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn IWQ_HANDWED;
}

/* FAUWT intewwupt handwew */
static iwqwetuwn_t pic32_uawt_fauwt_intewwupt(int iwq, void *dev_id)
{
	/* do nothing: pic32_uawt_do_wx() handwes fauwts. */
	wetuwn IWQ_HANDWED;
}

/* enabwe wx & tx opewation on uawt */
static void pic32_uawt_en_and_unmask(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);

	pic32_uawt_wwitew(spowt, PIC32_SET(PIC32_UAWT_STA),
				PIC32_UAWT_STA_UTXEN | PIC32_UAWT_STA_UWXEN);
	pic32_uawt_wwitew(spowt, PIC32_SET(PIC32_UAWT_MODE),
				PIC32_UAWT_MODE_ON);
}

/* disabwe wx & tx opewation on uawt */
static void pic32_uawt_dsbw_and_mask(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);

	/* wait fow tx empty, othewwise chaws wiww be wost ow cowwupted */
	pic32_wait_depwete_txbuf(spowt);

	pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_STA),
				PIC32_UAWT_STA_UTXEN | PIC32_UAWT_STA_UWXEN);
	pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
				PIC32_UAWT_MODE_ON);
}

/* sewiaw cowe wequest to initiawize uawt and stawt wx opewation */
static int pic32_uawt_stawtup(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);
	u32 dfwt_baud = (powt->uawtcwk / PIC32_UAWT_DFWT_BWATE / 16) - 1;
	unsigned wong fwags;
	int wet;

	wocaw_iwq_save(fwags);

	wet = cwk_pwepawe_enabwe(spowt->cwk);
	if (wet) {
		wocaw_iwq_westowe(fwags);
		goto out_done;
	}

	/* cweaw status and mode wegistews */
	pic32_uawt_wwitew(spowt, PIC32_UAWT_MODE, 0);
	pic32_uawt_wwitew(spowt, PIC32_UAWT_STA, 0);

	/* disabwe uawt and mask aww intewwupts */
	pic32_uawt_dsbw_and_mask(powt);

	/* set defauwt baud */
	pic32_uawt_wwitew(spowt, PIC32_UAWT_BWG, dfwt_baud);

	wocaw_iwq_westowe(fwags);

	/* Each UAWT of a PIC32 has thwee intewwupts thewefowe,
	 * we setup dwivew to wegistew the 3 iwqs fow the device.
	 *
	 * Fow each iwq wequest_iwq() is cawwed with intewwupt disabwed.
	 * And the iwq is enabwed as soon as we awe weady to handwe them.
	 */
	spowt->enabwe_tx_iwq = fawse;

	spowt->iwq_fauwt_name = kaspwintf(GFP_KEWNEW, "%s%d-fauwt",
					  pic32_uawt_type(powt),
					  spowt->idx);
	if (!spowt->iwq_fauwt_name) {
		dev_eww(powt->dev, "%s: kaspwintf eww!", __func__);
		wet = -ENOMEM;
		goto out_disabwe_cwk;
	}
	iwq_set_status_fwags(spowt->iwq_fauwt, IWQ_NOAUTOEN);
	wet = wequest_iwq(spowt->iwq_fauwt, pic32_uawt_fauwt_intewwupt,
			  IWQF_NO_THWEAD, spowt->iwq_fauwt_name, powt);
	if (wet) {
		dev_eww(powt->dev, "%s: wequest iwq(%d) eww! wet:%d name:%s\n",
			__func__, spowt->iwq_fauwt, wet,
			pic32_uawt_type(powt));
		goto out_f;
	}

	spowt->iwq_wx_name = kaspwintf(GFP_KEWNEW, "%s%d-wx",
				       pic32_uawt_type(powt),
				       spowt->idx);
	if (!spowt->iwq_wx_name) {
		dev_eww(powt->dev, "%s: kaspwintf eww!", __func__);
		wet = -ENOMEM;
		goto out_f;
	}
	iwq_set_status_fwags(spowt->iwq_wx, IWQ_NOAUTOEN);
	wet = wequest_iwq(spowt->iwq_wx, pic32_uawt_wx_intewwupt,
			  IWQF_NO_THWEAD, spowt->iwq_wx_name, powt);
	if (wet) {
		dev_eww(powt->dev, "%s: wequest iwq(%d) eww! wet:%d name:%s\n",
			__func__, spowt->iwq_wx, wet,
			pic32_uawt_type(powt));
		goto out_w;
	}

	spowt->iwq_tx_name = kaspwintf(GFP_KEWNEW, "%s%d-tx",
				       pic32_uawt_type(powt),
				       spowt->idx);
	if (!spowt->iwq_tx_name) {
		dev_eww(powt->dev, "%s: kaspwintf eww!", __func__);
		wet = -ENOMEM;
		goto out_w;
	}
	iwq_set_status_fwags(spowt->iwq_tx, IWQ_NOAUTOEN);
	wet = wequest_iwq(spowt->iwq_tx, pic32_uawt_tx_intewwupt,
			  IWQF_NO_THWEAD, spowt->iwq_tx_name, powt);
	if (wet) {
		dev_eww(powt->dev, "%s: wequest iwq(%d) eww! wet:%d name:%s\n",
			__func__, spowt->iwq_tx, wet,
			pic32_uawt_type(powt));
		goto out_t;
	}

	wocaw_iwq_save(fwags);

	/* set wx intewwupt on fiwst weceive */
	pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_STA),
			PIC32_UAWT_STA_UWXISEW1 | PIC32_UAWT_STA_UWXISEW0);

	/* set intewwupt on empty */
	pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_STA),
			PIC32_UAWT_STA_UTXISEW1);

	/* enabwe aww intewwupts and eanabwe uawt */
	pic32_uawt_en_and_unmask(powt);

	wocaw_iwq_westowe(fwags);

	enabwe_iwq(spowt->iwq_wx);

	wetuwn 0;

out_t:
	fwee_iwq(spowt->iwq_tx, powt);
	kfwee(spowt->iwq_tx_name);
out_w:
	fwee_iwq(spowt->iwq_wx, powt);
	kfwee(spowt->iwq_wx_name);
out_f:
	fwee_iwq(spowt->iwq_fauwt, powt);
	kfwee(spowt->iwq_fauwt_name);
out_disabwe_cwk:
	cwk_disabwe_unpwepawe(spowt->cwk);
out_done:
	wetuwn wet;
}

/* sewiaw cowe wequest to fwush & disabwe uawt */
static void pic32_uawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);
	unsigned wong fwags;

	/* disabwe uawt */
	uawt_powt_wock_iwqsave(powt, &fwags);
	pic32_uawt_dsbw_and_mask(powt);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
	cwk_disabwe_unpwepawe(spowt->cwk);

	/* fwee aww 3 intewwupts fow this UAWT */
	fwee_iwq(spowt->iwq_fauwt, powt);
	kfwee(spowt->iwq_fauwt_name);
	fwee_iwq(spowt->iwq_tx, powt);
	kfwee(spowt->iwq_tx_name);
	fwee_iwq(spowt->iwq_wx, powt);
	kfwee(spowt->iwq_wx_name);
}

/* sewiaw cowe wequest to change cuwwent uawt setting */
static void pic32_uawt_set_tewmios(stwuct uawt_powt *powt,
				   stwuct ktewmios *new,
				   const stwuct ktewmios *owd)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);
	unsigned int baud;
	unsigned int quot;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* disabwe uawt and mask aww intewwupts whiwe changing speed */
	pic32_uawt_dsbw_and_mask(powt);

	/* stop bit options */
	if (new->c_cfwag & CSTOPB)
		pic32_uawt_wwitew(spowt, PIC32_SET(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_STSEW);
	ewse
		pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_STSEW);

	/* pawity options */
	if (new->c_cfwag & PAWENB) {
		if (new->c_cfwag & PAWODD) {
			pic32_uawt_wwitew(spowt, PIC32_SET(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_PDSEW1);
			pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_PDSEW0);
		} ewse {
			pic32_uawt_wwitew(spowt, PIC32_SET(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_PDSEW0);
			pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_PDSEW1);
		}
	} ewse {
		pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_PDSEW1 |
					PIC32_UAWT_MODE_PDSEW0);
	}
	/* if hw fwow ctww, then the pins must be specified in device twee */
	if ((new->c_cfwag & CWTSCTS) && spowt->cts_gpiod) {
		/* enabwe hawdwawe fwow contwow */
		pic32_uawt_wwitew(spowt, PIC32_SET(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_UEN1);
		pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_UEN0);
		pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_WTSMD);
	} ewse {
		/* disabwe hawdwawe fwow contwow */
		pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_UEN1);
		pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_UEN0);
		pic32_uawt_wwitew(spowt, PIC32_CWW(PIC32_UAWT_MODE),
					PIC32_UAWT_MODE_WTSMD);
	}

	/* Awways 8-bit */
	new->c_cfwag |= CS8;

	/* Mawk/Space pawity is not suppowted */
	new->c_cfwag &= ~CMSPAW;

	/* update baud */
	baud = uawt_get_baud_wate(powt, new, owd, 0, powt->uawtcwk / 16);
	quot = uawt_get_divisow(powt, baud) - 1;
	pic32_uawt_wwitew(spowt, PIC32_UAWT_BWG, quot);
	uawt_update_timeout(powt, new->c_cfwag, baud);

	if (tty_tewmios_baud_wate(new))
		tty_tewmios_encode_baud_wate(new, baud, baud);

	/* enabwe uawt */
	pic32_uawt_en_and_unmask(powt);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

/* sewiaw cowe wequest to cwaim uawt iomem */
static int pic32_uawt_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(powt->dev);
	stwuct wesouwce *wes_mem;

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (unwikewy(!wes_mem))
		wetuwn -EINVAW;

	if (!wequest_mem_wegion(powt->mapbase, wesouwce_size(wes_mem),
				"pic32_uawt_mem"))
		wetuwn -EBUSY;

	powt->membase = devm_iowemap(powt->dev, powt->mapbase,
						wesouwce_size(wes_mem));
	if (!powt->membase) {
		dev_eww(powt->dev, "Unabwe to map wegistews\n");
		wewease_mem_wegion(powt->mapbase, wesouwce_size(wes_mem));
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/* sewiaw cowe wequest to wewease uawt iomem */
static void pic32_uawt_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(powt->dev);
	stwuct wesouwce *wes_mem;
	unsigned int wes_size;

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (unwikewy(!wes_mem))
		wetuwn;
	wes_size = wesouwce_size(wes_mem);

	wewease_mem_wegion(powt->mapbase, wes_size);
}

/* sewiaw cowe wequest to do any powt wequiwed auto-configuwation */
static void pic32_uawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE) {
		if (pic32_uawt_wequest_powt(powt))
			wetuwn;
		powt->type = POWT_PIC32;
	}
}

/* sewiaw cowe wequest to check that powt infowmation in sewinfo awe suitabwe */
static int pic32_uawt_vewify_powt(stwuct uawt_powt *powt,
				  stwuct sewiaw_stwuct *sewinfo)
{
	if (powt->type != POWT_PIC32)
		wetuwn -EINVAW;
	if (powt->iwq != sewinfo->iwq)
		wetuwn -EINVAW;
	if (powt->iotype != sewinfo->io_type)
		wetuwn -EINVAW;
	if (powt->mapbase != (unsigned wong)sewinfo->iomem_base)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* sewiaw cowe cawwbacks */
static const stwuct uawt_ops pic32_uawt_ops = {
	.tx_empty	= pic32_uawt_tx_empty,
	.get_mctww	= pic32_uawt_get_mctww,
	.set_mctww	= pic32_uawt_set_mctww,
	.stawt_tx	= pic32_uawt_stawt_tx,
	.stop_tx	= pic32_uawt_stop_tx,
	.stop_wx	= pic32_uawt_stop_wx,
	.bweak_ctw	= pic32_uawt_bweak_ctw,
	.stawtup	= pic32_uawt_stawtup,
	.shutdown	= pic32_uawt_shutdown,
	.set_tewmios	= pic32_uawt_set_tewmios,
	.type		= pic32_uawt_type,
	.wewease_powt	= pic32_uawt_wewease_powt,
	.wequest_powt	= pic32_uawt_wequest_powt,
	.config_powt	= pic32_uawt_config_powt,
	.vewify_powt	= pic32_uawt_vewify_powt,
};

#ifdef CONFIG_SEWIAW_PIC32_CONSOWE
/* output given chaw */
static void pic32_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);

	if (!(pic32_uawt_weadw(spowt, PIC32_UAWT_MODE) & PIC32_UAWT_MODE_ON))
		wetuwn;

	if (!(pic32_uawt_weadw(spowt, PIC32_UAWT_STA) & PIC32_UAWT_STA_UTXEN))
		wetuwn;

	/* wait fow tx empty */
	pic32_wait_depwete_txbuf(spowt);

	pic32_uawt_wwitew(spowt, PIC32_UAWT_TX, ch & 0xff);
}

/* consowe cowe wequest to output given stwing */
static void pic32_consowe_wwite(stwuct consowe *co, const chaw *s,
				unsigned int count)
{
	stwuct pic32_spowt *spowt = pic32_spowts[co->index];

	/* caww uawt hewpew to deaw with \w\n */
	uawt_consowe_wwite(&spowt->powt, s, count, pic32_consowe_putchaw);
}

/* consowe cowe wequest to setup given consowe, find matching uawt
 * powt and setup it.
 */
static int pic32_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct pic32_spowt *spowt;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';
	int wet = 0;

	if (unwikewy(co->index < 0 || co->index >= PIC32_MAX_UAWTS))
		wetuwn -ENODEV;

	spowt = pic32_spowts[co->index];
	if (!spowt)
		wetuwn -ENODEV;

	wet = cwk_pwepawe_enabwe(spowt->cwk);
	if (wet)
		wetuwn wet;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&spowt->powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew pic32_uawt_dwivew;
static stwuct consowe pic32_consowe = {
	.name		= PIC32_SDEV_NAME,
	.wwite		= pic32_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= pic32_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &pic32_uawt_dwivew,
};
#define PIC32_SCONSOWE (&pic32_consowe)

static int __init pic32_consowe_init(void)
{
	wegistew_consowe(&pic32_consowe);
	wetuwn 0;
}
consowe_initcaww(pic32_consowe_init);

/*
 * Wate consowe initiawization.
 */
static int __init pic32_wate_consowe_init(void)
{
	if (!consowe_is_wegistewed(&pic32_consowe))
		wegistew_consowe(&pic32_consowe);

	wetuwn 0;
}

cowe_initcaww(pic32_wate_consowe_init);

#ewse
#define PIC32_SCONSOWE NUWW
#endif

static stwuct uawt_dwivew pic32_uawt_dwivew = {
	.ownew			= THIS_MODUWE,
	.dwivew_name		= PIC32_DEV_NAME,
	.dev_name		= PIC32_SDEV_NAME,
	.nw			= PIC32_MAX_UAWTS,
	.cons			= PIC32_SCONSOWE,
};

static int pic32_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct pic32_spowt *spowt;
	int uawt_idx = 0;
	stwuct wesouwce *wes_mem;
	stwuct uawt_powt *powt;
	int wet;

	uawt_idx = of_awias_get_id(np, "sewiaw");
	if (uawt_idx < 0 || uawt_idx >= PIC32_MAX_UAWTS)
		wetuwn -EINVAW;

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes_mem)
		wetuwn -EINVAW;

	spowt = devm_kzawwoc(&pdev->dev, sizeof(*spowt), GFP_KEWNEW);
	if (!spowt)
		wetuwn -ENOMEM;

	spowt->idx		= uawt_idx;
	spowt->iwq_fauwt	= iwq_of_pawse_and_map(np, 0);
	spowt->iwq_wx		= iwq_of_pawse_and_map(np, 1);
	spowt->iwq_tx		= iwq_of_pawse_and_map(np, 2);
	spowt->cwk		= devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(spowt->cwk))
		wetuwn PTW_EWW(spowt->cwk);
	spowt->dev		= &pdev->dev;

	/* Hawdwawe fwow contwow: gpios
	 * !Note: Basicawwy, CTS is needed fow weading the status.
	 */
	spowt->cts_gpiod = devm_gpiod_get_optionaw(dev, "cts", GPIOD_IN);
	if (IS_EWW(spowt->cts_gpiod))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(spowt->cts_gpiod), "ewwow wequesting CTS GPIO\n");
	gpiod_set_consumew_name(spowt->cts_gpiod, "CTS");

	pic32_spowts[uawt_idx] = spowt;
	powt = &spowt->powt;
	powt->iotype	= UPIO_MEM;
	powt->mapbase	= wes_mem->stawt;
	powt->ops	= &pic32_uawt_ops;
	powt->fwags	= UPF_BOOT_AUTOCONF;
	powt->dev	= &pdev->dev;
	powt->fifosize	= PIC32_UAWT_TX_FIFO_DEPTH;
	powt->uawtcwk	= cwk_get_wate(spowt->cwk);
	powt->wine	= uawt_idx;

	wet = uawt_add_one_powt(&pic32_uawt_dwivew, powt);
	if (wet) {
		powt->membase = NUWW;
		dev_eww(powt->dev, "%s: uawt add powt ewwow!\n", __func__);
		goto eww;
	}

#ifdef CONFIG_SEWIAW_PIC32_CONSOWE
	if (uawt_consowe_wegistewed(powt)) {
		/* The pewiphewaw cwock has been enabwed by consowe_setup,
		 * so disabwe it tiww the powt is used.
		 */
		cwk_disabwe_unpwepawe(spowt->cwk);
	}
#endif

	pwatfowm_set_dwvdata(pdev, powt);

	dev_info(&pdev->dev, "%s: uawt(%d) dwivew initiawized.\n",
		 __func__, uawt_idx);

	wetuwn 0;
eww:
	/* automatic unwoww of spowt and gpios */
	wetuwn wet;
}

static void pic32_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt = pwatfowm_get_dwvdata(pdev);
	stwuct pic32_spowt *spowt = to_pic32_spowt(powt);

	uawt_wemove_one_powt(&pic32_uawt_dwivew, powt);
	cwk_disabwe_unpwepawe(spowt->cwk);
	pwatfowm_set_dwvdata(pdev, NUWW);
	pic32_spowts[spowt->idx] = NUWW;
}

static const stwuct of_device_id pic32_sewiaw_dt_ids[] = {
	{ .compatibwe = "micwochip,pic32mzda-uawt" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pic32_sewiaw_dt_ids);

static stwuct pwatfowm_dwivew pic32_uawt_pwatfowm_dwivew = {
	.pwobe		= pic32_uawt_pwobe,
	.wemove_new	= pic32_uawt_wemove,
	.dwivew		= {
		.name	= PIC32_DEV_NAME,
		.of_match_tabwe	= of_match_ptw(pic32_sewiaw_dt_ids),
		.suppwess_bind_attws = IS_BUIWTIN(CONFIG_SEWIAW_PIC32),
	},
};

static int __init pic32_uawt_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&pic32_uawt_dwivew);
	if (wet) {
		pw_eww("faiwed to wegistew %s:%d\n",
		       pic32_uawt_dwivew.dwivew_name, wet);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&pic32_uawt_pwatfowm_dwivew);
	if (wet) {
		pw_eww("faiw to wegistew pic32 uawt\n");
		uawt_unwegistew_dwivew(&pic32_uawt_dwivew);
	}

	wetuwn wet;
}
awch_initcaww(pic32_uawt_init);

static void __exit pic32_uawt_exit(void)
{
#ifdef CONFIG_SEWIAW_PIC32_CONSOWE
	unwegistew_consowe(&pic32_consowe);
#endif
	pwatfowm_dwivew_unwegistew(&pic32_uawt_pwatfowm_dwivew);
	uawt_unwegistew_dwivew(&pic32_uawt_dwivew);
}
moduwe_exit(pic32_uawt_exit);

MODUWE_AUTHOW("Sowin-Andwei Pistiwica <andwei.pistiwica@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip PIC32 integwated sewiaw powt dwivew");
MODUWE_WICENSE("GPW v2");
