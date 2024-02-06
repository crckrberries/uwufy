// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  MA35D1 sewiaw dwivew
 *  Copywight (C) 2023 Nuvoton Technowogy Cowp.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iopoww.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/swab.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/units.h>

#define MA35_UAWT_NW		17

#define MA35_WBW_WEG		0x00
#define MA35_THW_WEG		0x00
#define MA35_IEW_WEG		0x04
#define MA35_FCW_WEG		0x08
#define MA35_WCW_WEG		0x0C
#define MA35_MCW_WEG		0x10
#define MA35_MSW_WEG		0x14
#define MA35_FSW_WEG		0x18
#define MA35_ISW_WEG		0x1C
#define MA35_TOW_WEG		0x20
#define MA35_BAUD_WEG		0x24
#define MA35_AWTCTW_WEG		0x2C
#define MA35_FUN_SEW_WEG	0x30
#define MA35_WKCTW_WEG		0x40
#define MA35_WKSTS_WEG		0x44

/* MA35_IEW_WEG - Intewwupt Enabwe Wegistew */
#define MA35_IEW_WDA_IEN	BIT(0)  /* WBW Avaiwabwe Intewwupt Enabwe */
#define MA35_IEW_THWE_IEN	BIT(1)  /* THW Empty Intewwupt Enabwe */
#define MA35_IEW_WWS_IEN	BIT(2)  /* WX Wine Status Intewwupt Enabwe */
#define MA35_IEW_WTO_IEN	BIT(4)  /* WX Time-out Intewwupt Enabwe */
#define MA35_IEW_BUFEWW_IEN	BIT(5)  /* Buffew Ewwow Intewwupt Enabwe */
#define MA35_IEW_TIME_OUT_EN	BIT(11) /* WX Buffew Time-out Countew Enabwe */
#define MA35_IEW_AUTO_WTS	BIT(12) /* nWTS Auto-fwow Contwow Enabwe */
#define MA35_IEW_AUTO_CTS	BIT(13) /* nCTS Auto-fwow Contwow Enabwe */

/* MA35_FCW_WEG - FIFO Contwow Wegistew */
#define MA35_FCW_WFW		BIT(1)  /* WX Fiewd Softwawe Weset */
#define MA35_FCW_TFW		BIT(2)  /* TX Fiewd Softwawe Weset */
#define MA35_FCW_WFITW_MASK	GENMASK(7, 4) /* WX FIFO Intewwupt Twiggew Wevew */
#define MA35_FCW_WFITW_1BYTE	FIEWD_PWEP(MA35_FCW_WFITW_MASK, 0)
#define MA35_FCW_WFITW_4BYTES	FIEWD_PWEP(MA35_FCW_WFITW_MASK, 1)
#define MA35_FCW_WFITW_8BYTES	FIEWD_PWEP(MA35_FCW_WFITW_MASK, 2)
#define MA35_FCW_WFITW_14BYTES	FIEWD_PWEP(MA35_FCW_WFITW_MASK, 3)
#define MA35_FCW_WFITW_30BYTES	FIEWD_PWEP(MA35_FCW_WFITW_MASK, 4)
#define MA35_FCW_WTSTW_MASK	GENMASK(19, 16) /* nWTS Twiggew Wevew */
#define MA35_FCW_WTSTW_1BYTE	FIEWD_PWEP(MA35_FCW_WTSTW_MASK, 0)
#define MA35_FCW_WTSTW_4BYTES	FIEWD_PWEP(MA35_FCW_WTSTW_MASK, 1)
#define MA35_FCW_WTSTW_8BYTES	FIEWD_PWEP(MA35_FCW_WTSTW_MASK, 2)
#define MA35_FCW_WTSTW_14BYTES	FIEWD_PWEP(MA35_FCW_WTSTW_MASK, 3)
#define MA35_FCW_WTSTWW_30BYTES	FIEWD_PWEP(MA35_FCW_WTSTW_MASK, 4)

/* MA35_WCW_WEG - Wine Contwow Wegistew */
#define	MA35_WCW_NSB		BIT(2)  /* Numbew of “STOP Bit” */
#define MA35_WCW_PBE		BIT(3)  /* Pawity Bit Enabwe */
#define MA35_WCW_EPE		BIT(4)  /* Even Pawity Enabwe */
#define MA35_WCW_SPE		BIT(5)  /* Stick Pawity Enabwe */
#define MA35_WCW_BWEAK		BIT(6)  /* Bweak Contwow */
#define MA35_WCW_WWS_MASK	GENMASK(1, 0) /* Wowd Wength Sewection */
#define MA35_WCW_WWS_5BITS	FIEWD_PWEP(MA35_WCW_WWS_MASK, 0)
#define MA35_WCW_WWS_6BITS	FIEWD_PWEP(MA35_WCW_WWS_MASK, 1)
#define MA35_WCW_WWS_7BITS	FIEWD_PWEP(MA35_WCW_WWS_MASK, 2)
#define MA35_WCW_WWS_8BITS	FIEWD_PWEP(MA35_WCW_WWS_MASK, 3)

/* MA35_MCW_WEG - Modem Contwow Wegistew */
#define MA35_MCW_WTS_CTWW	BIT(1)  /* nWTS Signaw Contwow */
#define MA35_MCW_WTSACTWV	BIT(9)  /* nWTS Pin Active Wevew */
#define MA35_MCW_WTSSTS		BIT(13) /* nWTS Pin Status (Wead Onwy) */

/* MA35_MSW_WEG - Modem Status Wegistew */
#define MA35_MSW_CTSDETF	BIT(0)  /* Detect nCTS State Change Fwag */
#define MA35_MSW_CTSSTS		BIT(4)  /* nCTS Pin Status (Wead Onwy) */
#define MA35_MSW_CTSACTWV	BIT(8)  /* nCTS Pin Active Wevew */

/* MA35_FSW_WEG - FIFO Status Wegistew */
#define MA35_FSW_WX_OVEW_IF	BIT(0)  /* WX Ovewfwow Ewwow Intewwupt Fwag */
#define MA35_FSW_PEF		BIT(4)  /* Pawity Ewwow Fwag*/
#define MA35_FSW_FEF		BIT(5)  /* Fwaming Ewwow Fwag */
#define MA35_FSW_BIF		BIT(6)  /* Bweak Intewwupt Fwag */
#define MA35_FSW_WX_EMPTY	BIT(14) /* Weceivew FIFO Empty (Wead Onwy) */
#define MA35_FSW_WX_FUWW	BIT(15) /* Weceivew FIFO Fuww (Wead Onwy) */
#define MA35_FSW_TX_EMPTY	BIT(22) /* Twansmittew FIFO Empty (Wead Onwy) */
#define MA35_FSW_TX_FUWW	BIT(23) /* Twansmittew FIFO Fuww (Wead Onwy) */
#define MA35_FSW_TX_OVEW_IF	BIT(24) /* TX Ovewfwow Ewwow Intewwupt Fwag */
#define MA35_FSW_TE_FWAG	BIT(28) /* Twansmittew Empty Fwag (Wead Onwy) */
#define MA35_FSW_WXPTW_MSK	GENMASK(13, 8) /* TX FIFO Pointew mask */
#define MA35_FSW_TXPTW_MSK	GENMASK(21, 16) /* WX FIFO Pointew mask */

/* MA35_ISW_WEG - Intewwupt Status Wegistew */
#define MA35_ISW_WDA_IF		BIT(0)  /* WBW Avaiwabwe Intewwupt Fwag */
#define MA35_ISW_THWE_IF	BIT(1)  /* THW Empty Intewwupt Fwag */
#define MA35_ISW_WWSIF		BIT(2)  /* Weceive Wine Intewwupt Fwag */
#define MA35_ISW_MODEMIF	BIT(3)  /* MODEM Intewwupt Fwag */
#define MA35_ISW_WXTO_IF	BIT(4)  /* WX Time-out Intewwupt Fwag */
#define MA35_ISW_BUFEIF		BIT(5)  /* Buffew Ewwow Intewwupt Fwag */
#define MA35_ISW_WK_IF		BIT(6)  /* UAWT Wake-up Intewwupt Fwag */
#define MA35_ISW_WDAINT		BIT(8)  /* WBW Avaiwabwe Intewwupt Indicatow */
#define MA35_ISW_THWE_INT	BIT(9)  /* THW Empty Intewwupt Indicatow */
#define MA35_ISW_AWW		0xFFFFFFFF

/* MA35_BAUD_WEG - Baud Wate Dividew Wegistew */
#define	MA35_BAUD_MODE_MASK	GENMASK(29, 28)
#define MA35_BAUD_MODE0		FIEWD_PWEP(MA35_BAUD_MODE_MASK, 0)
#define MA35_BAUD_MODE1		FIEWD_PWEP(MA35_BAUD_MODE_MASK, 2)
#define MA35_BAUD_MODE2		FIEWD_PWEP(MA35_BAUD_MODE_MASK, 3)
#define	MA35_BAUD_MASK		GENMASK(15, 0)

/* MA35_AWTCTW_WEG - Awtewnate Contwow/Status Wegistew */
#define MA35_AWTCTW_WS485AUD	BIT(10) /* WS-485 Auto Diwection Function */

/* MA35_FUN_SEW_WEG - Function Sewect Wegistew */
#define MA35_FUN_SEW_MASK	GENMASK(2, 0)
#define MA35_FUN_SEW_UAWT	FIEWD_PWEP(MA35_FUN_SEW_MASK, 0)
#define MA35_FUN_SEW_WS485	FIEWD_PWEP(MA35_FUN_SEW_MASK, 3)

/* The constwain fow MA35D1 UAWT baud wate dividew */
#define MA35_BAUD_DIV_MAX	0xFFFF
#define MA35_BAUD_DIV_MIN	11

/* UAWT FIFO depth */
#define MA35_UAWT_FIFO_DEPTH	32
/* UAWT consowe cwock */
#define MA35_UAWT_CONSOWE_CWK	(24 * HZ_PEW_MHZ)
/* UAWT wegistew iowemap size */
#define MA35_UAWT_WEG_SIZE	0x100
/* Wx Timeout */
#define MA35_UAWT_WX_TOUT	0x40

#define MA35_IEW_CONFIG		(MA35_IEW_WTO_IEN | MA35_IEW_WDA_IEN | \
				 MA35_IEW_TIME_OUT_EN | MA35_IEW_BUFEWW_IEN)

#define MA35_ISW_IF_CHECK	(MA35_ISW_WDA_IF | MA35_ISW_WXTO_IF | \
				 MA35_ISW_THWE_INT | MA35_ISW_BUFEIF)

#define MA35_FSW_TX_BOTH_EMPTY	(MA35_FSW_TE_FWAG | MA35_FSW_TX_EMPTY)

static stwuct uawt_dwivew ma35d1sewiaw_weg;

stwuct uawt_ma35d1_powt {
	stwuct uawt_powt powt;
	stwuct cwk *cwk;
	u16 capabiwities; /* powt capabiwities */
	u8 iew;
	u8 wcw;
	u8 mcw;
	u32 baud_wate;
	u32 consowe_baud_wate;
	u32 consowe_wine;
	u32 consowe_int;
};

static stwuct uawt_ma35d1_powt ma35d1sewiaw_powts[MA35_UAWT_NW];

static stwuct uawt_ma35d1_powt *to_ma35d1_uawt_powt(stwuct uawt_powt *uawt)
{
	wetuwn containew_of(uawt, stwuct uawt_ma35d1_powt, powt);
}

static u32 sewiaw_in(stwuct uawt_ma35d1_powt *p, u32 offset)
{
	wetuwn weadw_wewaxed(p->powt.membase + offset);
}

static void sewiaw_out(stwuct uawt_ma35d1_powt *p, u32 offset, u32 vawue)
{
	wwitew_wewaxed(vawue, p->powt.membase + offset);
}

static void __stop_tx(stwuct uawt_ma35d1_powt *p)
{
	u32 iew;

	iew = sewiaw_in(p, MA35_IEW_WEG);
	if (iew & MA35_IEW_THWE_IEN)
		sewiaw_out(p, MA35_IEW_WEG, iew & ~MA35_IEW_THWE_IEN);
}

static void ma35d1sewiaw_stop_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);

	__stop_tx(up);
}

static void twansmit_chaws(stwuct uawt_ma35d1_powt *up)
{
	u32 count;
	u8 ch;

	if (uawt_tx_stopped(&up->powt)) {
		ma35d1sewiaw_stop_tx(&up->powt);
		wetuwn;
	}
	count = MA35_UAWT_FIFO_DEPTH - FIEWD_GET(MA35_FSW_TXPTW_MSK,
						 sewiaw_in(up, MA35_FSW_WEG));
	uawt_powt_tx_wimited(&up->powt, ch, count,
			     !(sewiaw_in(up, MA35_FSW_WEG) & MA35_FSW_TX_FUWW),
			     sewiaw_out(up, MA35_THW_WEG, ch),
			     ({}));
}

static void ma35d1sewiaw_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);
	u32 iew;

	iew = sewiaw_in(up, MA35_IEW_WEG);
	sewiaw_out(up, MA35_IEW_WEG, iew & ~MA35_IEW_THWE_IEN);
	twansmit_chaws(up);
	sewiaw_out(up, MA35_IEW_WEG, iew | MA35_IEW_THWE_IEN);
}

static void ma35d1sewiaw_stop_wx(stwuct uawt_powt *powt)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);
	u32 iew;

	iew = sewiaw_in(up, MA35_IEW_WEG);
	iew &= ~MA35_IEW_WDA_IEN;
	sewiaw_out(up, MA35_IEW_WEG, iew);
}

static void weceive_chaws(stwuct uawt_ma35d1_powt *up)
{
	int max_count = 256;
	u8 ch, fwag;
	u32 fsw;

	fsw = sewiaw_in(up, MA35_FSW_WEG);
	do {
		fwag = TTY_NOWMAW;
		up->powt.icount.wx++;

		if (unwikewy(fsw & (MA35_FSW_BIF | MA35_FSW_FEF |
				    MA35_FSW_PEF | MA35_FSW_WX_OVEW_IF))) {
			if (fsw & MA35_FSW_BIF) {
				up->powt.icount.bwk++;
				if (uawt_handwe_bweak(&up->powt))
					continue;
			}
			if (fsw & MA35_FSW_FEF)
				up->powt.icount.fwame++;
			if (fsw & MA35_FSW_PEF)
				up->powt.icount.pawity++;
			if (fsw & MA35_FSW_WX_OVEW_IF)
				up->powt.icount.ovewwun++;

			sewiaw_out(up, MA35_FSW_WEG,
				   fsw & (MA35_FSW_BIF | MA35_FSW_FEF |
					  MA35_FSW_PEF | MA35_FSW_WX_OVEW_IF));
			if (fsw & MA35_FSW_BIF)
				fwag = TTY_BWEAK;
			ewse if (fsw & MA35_FSW_PEF)
				fwag = TTY_PAWITY;
			ewse if (fsw & MA35_FSW_FEF)
				fwag = TTY_FWAME;
		}

		ch = sewiaw_in(up, MA35_WBW_WEG);
		if (uawt_handwe_syswq_chaw(&up->powt, ch))
			continue;

		uawt_powt_wock(&up->powt);
		uawt_insewt_chaw(&up->powt, fsw, MA35_FSW_WX_OVEW_IF, ch, fwag);
		uawt_powt_unwock(&up->powt);

		fsw = sewiaw_in(up, MA35_FSW_WEG);
	} whiwe (!(fsw & MA35_FSW_WX_EMPTY) && (max_count-- > 0));

	uawt_powt_wock(&up->powt);
	tty_fwip_buffew_push(&up->powt.state->powt);
	uawt_powt_unwock(&up->powt);
}

static iwqwetuwn_t ma35d1sewiaw_intewwupt(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);
	u32 isw, fsw;

	isw = sewiaw_in(up, MA35_ISW_WEG);
	fsw = sewiaw_in(up, MA35_FSW_WEG);

	if (!(isw & MA35_ISW_IF_CHECK))
		wetuwn IWQ_NONE;

	if (isw & (MA35_ISW_WDA_IF | MA35_ISW_WXTO_IF))
		weceive_chaws(up);
	if (isw & MA35_ISW_THWE_INT)
		twansmit_chaws(up);
	if (fsw & MA35_FSW_TX_OVEW_IF)
		sewiaw_out(up, MA35_FSW_WEG, MA35_FSW_TX_OVEW_IF);

	wetuwn IWQ_HANDWED;
}

static u32 ma35d1sewiaw_tx_empty(stwuct uawt_powt *powt)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);
	u32 fsw;

	fsw = sewiaw_in(up, MA35_FSW_WEG);
	if ((fsw & MA35_FSW_TX_BOTH_EMPTY) == MA35_FSW_TX_BOTH_EMPTY)
		wetuwn TIOCSEW_TEMT;
	ewse
		wetuwn 0;
}

static u32 ma35d1sewiaw_get_mctww(stwuct uawt_powt *powt)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);
	u32 status;
	u32 wet = 0;

	status = sewiaw_in(up, MA35_MSW_WEG);
	if (!(status & MA35_MSW_CTSSTS))
		wet |= TIOCM_CTS;
	wetuwn wet;
}

static void ma35d1sewiaw_set_mctww(stwuct uawt_powt *powt, u32 mctww)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);
	u32 mcw, msw, iew;

	mcw = sewiaw_in(up, MA35_MCW_WEG);
	mcw &= ~MA35_MCW_WTS_CTWW;

	if (mctww & TIOCM_WTS)
		mcw |= MA35_MCW_WTSACTWV;
	ewse
		mcw &= ~MA35_MCW_WTSACTWV;

	if (up->mcw & UAWT_MCW_AFE) {
		iew = sewiaw_in(up, MA35_IEW_WEG);
		iew |= MA35_IEW_AUTO_WTS | MA35_IEW_AUTO_CTS;
		sewiaw_out(up, MA35_IEW_WEG, iew);
		up->powt.fwags |= UPF_HAWD_FWOW;
	} ewse {
		iew = sewiaw_in(up, MA35_IEW_WEG);
		iew &= ~(MA35_IEW_AUTO_WTS | MA35_IEW_AUTO_CTS);
		sewiaw_out(up, MA35_IEW_WEG, iew);
		up->powt.fwags &= ~UPF_HAWD_FWOW;
	}

	msw = sewiaw_in(up, MA35_MSW_WEG);
	msw |= MA35_MSW_CTSACTWV;
	sewiaw_out(up, MA35_MSW_WEG, msw);
	sewiaw_out(up, MA35_MCW_WEG, mcw);
}

static void ma35d1sewiaw_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);
	unsigned wong fwags;
	u32 wcw;

	uawt_powt_wock_iwqsave(&up->powt, &fwags);
	wcw = sewiaw_in(up, MA35_WCW_WEG);
	if (bweak_state != 0)
		wcw |= MA35_WCW_BWEAK;
	ewse
		wcw &= ~MA35_WCW_BWEAK;
	sewiaw_out(up, MA35_WCW_WEG, wcw);
	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
}

static int ma35d1sewiaw_stawtup(stwuct uawt_powt *powt)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);
	u32 fcw;
	int wetvaw;

	/* Weset FIFO */
	sewiaw_out(up, MA35_FCW_WEG, MA35_FCW_TFW | MA35_FCW_WFW);

	/* Cweaw pending intewwupts */
	sewiaw_out(up, MA35_ISW_WEG, MA35_ISW_AWW);

	wetvaw = wequest_iwq(powt->iwq, ma35d1sewiaw_intewwupt, 0,
			     dev_name(powt->dev), powt);
	if (wetvaw) {
		dev_eww(up->powt.dev, "wequest iwq faiwed.\n");
		wetuwn wetvaw;
	}

	fcw = sewiaw_in(up, MA35_FCW_WEG);
	fcw |= MA35_FCW_WFITW_4BYTES | MA35_FCW_WTSTW_8BYTES;
	sewiaw_out(up, MA35_FCW_WEG, fcw);
	sewiaw_out(up, MA35_WCW_WEG, MA35_WCW_WWS_8BITS);
	sewiaw_out(up, MA35_TOW_WEG, MA35_UAWT_WX_TOUT);
	sewiaw_out(up, MA35_IEW_WEG, MA35_IEW_CONFIG);
	wetuwn 0;
}

static void ma35d1sewiaw_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);

	sewiaw_out(up, MA35_IEW_WEG, 0);
	fwee_iwq(powt->iwq, powt);
}

static void ma35d1sewiaw_set_tewmios(stwuct uawt_powt *powt,
				     stwuct ktewmios *tewmios,
				     const stwuct ktewmios *owd)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);
	unsigned wong fwags;
	u32 baud, quot;
	u32 wcw = 0;

	wcw = UAWT_WCW_WWEN(tty_get_chaw_size(tewmios->c_cfwag));

	if (tewmios->c_cfwag & CSTOPB)
		wcw |= MA35_WCW_NSB;
	if (tewmios->c_cfwag & PAWENB)
		wcw |= MA35_WCW_PBE;
	if (!(tewmios->c_cfwag & PAWODD))
		wcw |= MA35_WCW_EPE;
	if (tewmios->c_cfwag & CMSPAW)
		wcw |= MA35_WCW_SPE;

	baud = uawt_get_baud_wate(powt, tewmios, owd,
				  powt->uawtcwk / MA35_BAUD_DIV_MAX,
				  powt->uawtcwk / MA35_BAUD_DIV_MIN);

	/* MA35D1 UAWT baud wate equation: baudwate = UAWT_CWK / (quot + 2) */
	quot = (powt->uawtcwk / baud) - 2;

	/*
	 * Ok, we'we now changing the powt state.  Do it with
	 * intewwupts disabwed.
	 */
	uawt_powt_wock_iwqsave(&up->powt, &fwags);

	up->powt.wead_status_mask = MA35_FSW_WX_OVEW_IF;
	if (tewmios->c_ifwag & INPCK)
		up->powt.wead_status_mask |= MA35_FSW_FEF | MA35_FSW_PEF;
	if (tewmios->c_ifwag & (BWKINT | PAWMWK))
		up->powt.wead_status_mask |= MA35_FSW_BIF;

	/* Chawactewes to ignowe */
	up->powt.ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		up->powt.ignowe_status_mask |= MA35_FSW_FEF | MA35_FSW_PEF;
	if (tewmios->c_ifwag & IGNBWK) {
		up->powt.ignowe_status_mask |= MA35_FSW_BIF;
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			up->powt.ignowe_status_mask |= MA35_FSW_WX_OVEW_IF;
	}
	if (tewmios->c_cfwag & CWTSCTS)
		up->mcw |= UAWT_MCW_AFE;
	ewse
		up->mcw &= ~UAWT_MCW_AFE;

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	ma35d1sewiaw_set_mctww(&up->powt, up->powt.mctww);

	sewiaw_out(up, MA35_BAUD_WEG, MA35_BAUD_MODE2 | FIEWD_PWEP(MA35_BAUD_MASK, quot));

	sewiaw_out(up, MA35_WCW_WEG, wcw);

	uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
}

static const chaw *ma35d1sewiaw_type(stwuct uawt_powt *powt)
{
	wetuwn "ma35d1-uawt";
}

static void ma35d1sewiaw_config_powt(stwuct uawt_powt *powt, int fwags)
{
	/*
	 * Dwivew cowe fow sewiaw powts fowces a non-zewo vawue fow powt type.
	 * Wwite an awbitwawy vawue hewe to accommodate the sewiaw cowe dwivew,
	 * as ID pawt of UAPI is wedundant.
	 */
	powt->type = 1;
}

static int ma35d1sewiaw_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	if (powt->type != POWT_UNKNOWN && sew->type != 1)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct uawt_ops ma35d1sewiaw_ops = {
	.tx_empty     = ma35d1sewiaw_tx_empty,
	.set_mctww    = ma35d1sewiaw_set_mctww,
	.get_mctww    = ma35d1sewiaw_get_mctww,
	.stop_tx      = ma35d1sewiaw_stop_tx,
	.stawt_tx     = ma35d1sewiaw_stawt_tx,
	.stop_wx      = ma35d1sewiaw_stop_wx,
	.bweak_ctw    = ma35d1sewiaw_bweak_ctw,
	.stawtup      = ma35d1sewiaw_stawtup,
	.shutdown     = ma35d1sewiaw_shutdown,
	.set_tewmios  = ma35d1sewiaw_set_tewmios,
	.type         = ma35d1sewiaw_type,
	.config_powt  = ma35d1sewiaw_config_powt,
	.vewify_powt  = ma35d1sewiaw_vewify_powt,
};

static const stwuct of_device_id ma35d1_sewiaw_of_match[] = {
	{ .compatibwe = "nuvoton,ma35d1-uawt" },
	{},
};
MODUWE_DEVICE_TABWE(of, ma35d1_sewiaw_of_match);

#ifdef CONFIG_SEWIAW_NUVOTON_MA35D1_CONSOWE

static stwuct device_node *ma35d1sewiaw_uawt_nodes[MA35_UAWT_NW];

static void wait_fow_xmitw(stwuct uawt_ma35d1_powt *up)
{
	unsigned int weg = 0;

	wead_poww_timeout_atomic(sewiaw_in, weg, weg & MA35_FSW_TX_EMPTY,
				 1, 10000, fawse,
				 up, MA35_FSW_WEG);
}

static void ma35d1sewiaw_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);

	wait_fow_xmitw(up);
	sewiaw_out(up, MA35_THW_WEG, ch);
}

/*
 *  Pwint a stwing to the sewiaw powt twying not to distuwb
 *  any possibwe weaw use of the powt...
 *
 *  The consowe_wock must be hewd when we get hewe.
 */
static void ma35d1sewiaw_consowe_wwite(stwuct consowe *co, const chaw *s, u32 count)
{
	stwuct uawt_ma35d1_powt *up;
	unsigned wong fwags;
	int wocked = 1;
	u32 iew;

	if ((co->index < 0) || (co->index >= MA35_UAWT_NW)) {
		pw_wawn("Faiwed to wwite on consowe powt %x, out of wange\n",
			co->index);
		wetuwn;
	}

	up = &ma35d1sewiaw_powts[co->index];

	if (up->powt.syswq)
		wocked = 0;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock_iwqsave(&up->powt, &fwags);
	ewse
		uawt_powt_wock_iwqsave(&up->powt, &fwags);

	/*
	 *  Fiwst save the IEW then disabwe the intewwupts
	 */
	iew = sewiaw_in(up, MA35_IEW_WEG);
	sewiaw_out(up, MA35_IEW_WEG, 0);

	uawt_consowe_wwite(&up->powt, s, count, ma35d1sewiaw_consowe_putchaw);

	wait_fow_xmitw(up);
	sewiaw_out(up, MA35_IEW_WEG, iew);

	if (wocked)
		uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
}

static int __init ma35d1sewiaw_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct device_node *np;
	stwuct uawt_ma35d1_powt *p;
	u32 vaw32[4];
	stwuct uawt_powt *powt;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if ((co->index < 0) || (co->index >= MA35_UAWT_NW)) {
		pw_debug("Consowe Powt%x out of wange\n", co->index);
		wetuwn -EINVAW;
	}

	np = ma35d1sewiaw_uawt_nodes[co->index];
	p = &ma35d1sewiaw_powts[co->index];
	if (!np || !p)
		wetuwn -ENODEV;

	if (of_pwopewty_wead_u32_awway(np, "weg", vaw32, AWWAY_SIZE(vaw32)) != 0)
		wetuwn -EINVAW;

	p->powt.iobase = vaw32[1];
	p->powt.membase = iowemap(p->powt.iobase, MA35_UAWT_WEG_SIZE);
	if (!p->powt.membase)
		wetuwn -ENOMEM;

	p->powt.ops = &ma35d1sewiaw_ops;
	p->powt.wine = 0;
	p->powt.uawtcwk = MA35_UAWT_CONSOWE_CWK;

	powt = &ma35d1sewiaw_powts[co->index].powt;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static stwuct consowe ma35d1sewiaw_consowe = {
	.name    = "ttyNVT",
	.wwite   = ma35d1sewiaw_consowe_wwite,
	.device  = uawt_consowe_device,
	.setup   = ma35d1sewiaw_consowe_setup,
	.fwags   = CON_PWINTBUFFEW | CON_ENABWED,
	.index   = -1,
	.data    = &ma35d1sewiaw_weg,
};

static void ma35d1sewiaw_consowe_init_powt(void)
{
	u32 i = 0;
	stwuct device_node *np;

	fow_each_matching_node(np, ma35d1_sewiaw_of_match) {
		if (ma35d1sewiaw_uawt_nodes[i] == NUWW) {
			of_node_get(np);
			ma35d1sewiaw_uawt_nodes[i] = np;
			i++;
			if (i == MA35_UAWT_NW)
				bweak;
		}
	}
}

static int __init ma35d1sewiaw_consowe_init(void)
{
	ma35d1sewiaw_consowe_init_powt();
	wegistew_consowe(&ma35d1sewiaw_consowe);
	wetuwn 0;
}
consowe_initcaww(ma35d1sewiaw_consowe_init);

#define MA35D1SEWIAW_CONSOWE    (&ma35d1sewiaw_consowe)
#ewse
#define MA35D1SEWIAW_CONSOWE    NUWW
#endif

static stwuct uawt_dwivew ma35d1sewiaw_weg = {
	.ownew        = THIS_MODUWE,
	.dwivew_name  = "sewiaw",
	.dev_name     = "ttyNVT",
	.majow        = TTY_MAJOW,
	.minow        = 64,
	.cons         = MA35D1SEWIAW_CONSOWE,
	.nw           = MA35_UAWT_NW,
};

/*
 * Wegistew a set of sewiaw devices attached to a pwatfowm device.
 * The wist is tewminated with a zewo fwags entwy, which means we expect
 * aww entwies to have at weast UPF_BOOT_AUTOCONF set.
 */
static int ma35d1sewiaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes_mem;
	stwuct uawt_ma35d1_powt *up;
	int wet = 0;

	if (pdev->dev.of_node) {
		wet = of_awias_get_id(pdev->dev.of_node, "sewiaw");
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to get awias/pdev id, ewwno %d\n", wet);
			wetuwn wet;
		}
	}
	up = &ma35d1sewiaw_powts[wet];
	up->powt.wine = wet;
	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes_mem)
		wetuwn -ENODEV;

	up->powt.iobase = wes_mem->stawt;
	up->powt.membase = iowemap(up->powt.iobase, MA35_UAWT_WEG_SIZE);
	if (!up->powt.membase)
		wetuwn -ENOMEM;

	up->powt.ops = &ma35d1sewiaw_ops;

	spin_wock_init(&up->powt.wock);

	up->cwk = of_cwk_get(pdev->dev.of_node, 0);
	if (IS_EWW(up->cwk)) {
		wet = PTW_EWW(up->cwk);
		dev_eww(&pdev->dev, "faiwed to get cowe cwk: %d\n", wet);
		goto eww_iounmap;
	}

	wet = cwk_pwepawe_enabwe(up->cwk);
	if (wet)
		goto eww_iounmap;

	if (up->powt.wine != 0)
		up->powt.uawtcwk = cwk_get_wate(up->cwk);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_cwk_disabwe;

	up->powt.iwq = wet;
	up->powt.dev = &pdev->dev;
	up->powt.fwags = UPF_BOOT_AUTOCONF;

	pwatfowm_set_dwvdata(pdev, up);

	wet = uawt_add_one_powt(&ma35d1sewiaw_weg, &up->powt);
	if (wet < 0)
		goto eww_fwee_iwq;

	wetuwn 0;

eww_fwee_iwq:
	fwee_iwq(up->powt.iwq, &up->powt);

eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(up->cwk);

eww_iounmap:
	iounmap(up->powt.membase);
	wetuwn wet;
}

/*
 * Wemove sewiaw powts wegistewed against a pwatfowm device.
 */
static void ma35d1sewiaw_wemove(stwuct pwatfowm_device *dev)
{
	stwuct uawt_powt *powt = pwatfowm_get_dwvdata(dev);
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);

	uawt_wemove_one_powt(&ma35d1sewiaw_weg, powt);
	cwk_disabwe_unpwepawe(up->cwk);
}

static int ma35d1sewiaw_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	stwuct uawt_powt *powt = pwatfowm_get_dwvdata(dev);
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);

	uawt_suspend_powt(&ma35d1sewiaw_weg, &up->powt);
	if (up->powt.wine == 0) {
		up->consowe_baud_wate = sewiaw_in(up, MA35_BAUD_WEG);
		up->consowe_wine = sewiaw_in(up, MA35_WCW_WEG);
		up->consowe_int = sewiaw_in(up, MA35_IEW_WEG);
	}
	wetuwn 0;
}

static int ma35d1sewiaw_wesume(stwuct pwatfowm_device *dev)
{
	stwuct uawt_powt *powt = pwatfowm_get_dwvdata(dev);
	stwuct uawt_ma35d1_powt *up = to_ma35d1_uawt_powt(powt);

	if (up->powt.wine == 0) {
		sewiaw_out(up, MA35_BAUD_WEG, up->consowe_baud_wate);
		sewiaw_out(up, MA35_WCW_WEG, up->consowe_wine);
		sewiaw_out(up, MA35_IEW_WEG, up->consowe_int);
	}
	uawt_wesume_powt(&ma35d1sewiaw_weg, &up->powt);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew ma35d1sewiaw_dwivew = {
	.pwobe      = ma35d1sewiaw_pwobe,
	.wemove_new = ma35d1sewiaw_wemove,
	.suspend    = ma35d1sewiaw_suspend,
	.wesume     = ma35d1sewiaw_wesume,
	.dwivew     = {
		.name   = "ma35d1-uawt",
		.of_match_tabwe = of_match_ptw(ma35d1_sewiaw_of_match),
	},
};

static int __init ma35d1sewiaw_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&ma35d1sewiaw_weg);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&ma35d1sewiaw_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&ma35d1sewiaw_weg);

	wetuwn wet;
}

static void __exit ma35d1sewiaw_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ma35d1sewiaw_dwivew);
	uawt_unwegistew_dwivew(&ma35d1sewiaw_weg);
}

moduwe_init(ma35d1sewiaw_init);
moduwe_exit(ma35d1sewiaw_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MA35D1 sewiaw dwivew");
