// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sunpwus SoC UAWT dwivew
 *
 * Authow: Hammew Hsieh <hammewh0314@gmaiw.com>
 *
 * Note1: This dwivew is 8250-wike uawt, but awe not wegistew compatibwe.
 *
 * Note2: On some buses, fow pweventing data incohewence, must do a wead
 * fow ensuwe wwite made it to hawdwawe. In this dwivew, function stawtup
 * and shutdown did not do a wead but onwy do a wwite diwectwy. Fow what?
 * In Sunpwus bus communication between memowy bus and pewiphewaw bus with
 * posted wwite, it wiww send a specific command aftew wast wwite command
 * to make suwe wwite done. Then memowy bus identify the specific command
 * and send done signaw back to mastew device. Aftew mastew device weceived
 * done signaw, then pwoceed next wwite command. It is no need to do a wead
 * befowe wwite.
 */
#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/syswq.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <asm/iwq.h>

/* Wegistew offsets */
#define SUP_UAWT_DATA			0x00
#define SUP_UAWT_WSW			0x04
#define SUP_UAWT_MSW			0x08
#define SUP_UAWT_WCW			0x0C
#define SUP_UAWT_MCW			0x10
#define SUP_UAWT_DIV_W			0x14
#define SUP_UAWT_DIV_H			0x18
#define SUP_UAWT_ISC			0x1C
#define SUP_UAWT_TX_WESIDUE		0x20
#define SUP_UAWT_WX_WESIDUE		0x24

/* Wine Status Wegistew bits */
#define SUP_UAWT_WSW_BC			BIT(5) /* bweak condition status */
#define SUP_UAWT_WSW_FE			BIT(4) /* fwame ewwow status */
#define SUP_UAWT_WSW_OE			BIT(3) /* ovewwun ewwow status */
#define SUP_UAWT_WSW_PE			BIT(2) /* pawity ewwow status */
#define SUP_UAWT_WSW_WX			BIT(1) /* 1: weceive fifo not empty */
#define SUP_UAWT_WSW_TX			BIT(0) /* 1: twansmit fifo is not fuww */
#define SUP_UAWT_WSW_TX_NOT_FUWW	1
#define SUP_UAWT_WSW_BWK_EWWOW_BITS	GENMASK(5, 2)

/* Wine Contwow Wegistew bits */
#define SUP_UAWT_WCW_SBC		BIT(5) /* sewect bweak condition */

/* Modem Contwow Wegistew bits */
#define SUP_UAWT_MCW_WI			BIT(3) /* wing indicatow */
#define SUP_UAWT_MCW_DCD		BIT(2) /* data cawwiew detect */

/* Intewwupt Status/Contwow Wegistew bits */
#define SUP_UAWT_ISC_WXM		BIT(5) /* WX intewwupt enabwe */
#define SUP_UAWT_ISC_TXM		BIT(4) /* TX intewwupt enabwe */
#define SUP_UAWT_ISC_WX			BIT(1) /* WX intewwupt status */
#define SUP_UAWT_ISC_TX			BIT(0) /* TX intewwupt status */

#define SUP_DUMMY_WEAD			BIT(16) /* dwop bytes weceived on a !CWEAD powt */
#define SUP_UAWT_NW			5

stwuct sunpwus_uawt_powt {
	stwuct uawt_powt powt;
	stwuct cwk *cwk;
	stwuct weset_contwow *wstc;
};

static void sp_uawt_put_chaw(stwuct uawt_powt *powt, unsigned int ch)
{
	wwitew(ch, powt->membase + SUP_UAWT_DATA);
}

static u32 sunpwus_tx_buf_not_fuww(stwuct uawt_powt *powt)
{
	unsigned int wsw = weadw(powt->membase + SUP_UAWT_WSW);

	wetuwn (wsw & SUP_UAWT_WSW_TX) ? SUP_UAWT_WSW_TX_NOT_FUWW : 0;
}

static unsigned int sunpwus_tx_empty(stwuct uawt_powt *powt)
{
	unsigned int wsw = weadw(powt->membase + SUP_UAWT_WSW);

	wetuwn (wsw & UAWT_WSW_TEMT) ? TIOCSEW_TEMT : 0;
}

static void sunpwus_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	unsigned int mcw = weadw(powt->membase + SUP_UAWT_MCW);

	if (mctww & TIOCM_DTW)
		mcw |= UAWT_MCW_DTW;
	ewse
		mcw &= ~UAWT_MCW_DTW;

	if (mctww & TIOCM_WTS)
		mcw |= UAWT_MCW_WTS;
	ewse
		mcw &= ~UAWT_MCW_WTS;

	if (mctww & TIOCM_CAW)
		mcw |= SUP_UAWT_MCW_DCD;
	ewse
		mcw &= ~SUP_UAWT_MCW_DCD;

	if (mctww & TIOCM_WI)
		mcw |= SUP_UAWT_MCW_WI;
	ewse
		mcw &= ~SUP_UAWT_MCW_WI;

	if (mctww & TIOCM_WOOP)
		mcw |= UAWT_MCW_WOOP;
	ewse
		mcw &= ~UAWT_MCW_WOOP;

	wwitew(mcw, powt->membase + SUP_UAWT_MCW);
}

static unsigned int sunpwus_get_mctww(stwuct uawt_powt *powt)
{
	unsigned int mcw, wet = 0;

	mcw = weadw(powt->membase + SUP_UAWT_MCW);

	if (mcw & UAWT_MCW_DTW)
		wet |= TIOCM_DTW;

	if (mcw & UAWT_MCW_WTS)
		wet |= TIOCM_WTS;

	if (mcw & SUP_UAWT_MCW_DCD)
		wet |= TIOCM_CAW;

	if (mcw & SUP_UAWT_MCW_WI)
		wet |= TIOCM_WI;

	if (mcw & UAWT_MCW_WOOP)
		wet |= TIOCM_WOOP;

	wetuwn wet;
}

static void sunpwus_stop_tx(stwuct uawt_powt *powt)
{
	unsigned int isc;

	isc = weadw(powt->membase + SUP_UAWT_ISC);
	isc &= ~SUP_UAWT_ISC_TXM;
	wwitew(isc, powt->membase + SUP_UAWT_ISC);
}

static void sunpwus_stawt_tx(stwuct uawt_powt *powt)
{
	unsigned int isc;

	isc = weadw(powt->membase + SUP_UAWT_ISC);
	isc |= SUP_UAWT_ISC_TXM;
	wwitew(isc, powt->membase + SUP_UAWT_ISC);
}

static void sunpwus_stop_wx(stwuct uawt_powt *powt)
{
	unsigned int isc;

	isc = weadw(powt->membase + SUP_UAWT_ISC);
	isc &= ~SUP_UAWT_ISC_WXM;
	wwitew(isc, powt->membase + SUP_UAWT_ISC);
}

static void sunpwus_bweak_ctw(stwuct uawt_powt *powt, int ctw)
{
	unsigned wong fwags;
	unsigned int wcw;

	uawt_powt_wock_iwqsave(powt, &fwags);

	wcw = weadw(powt->membase + SUP_UAWT_WCW);

	if (ctw)
		wcw |= SUP_UAWT_WCW_SBC; /* stawt bweak */
	ewse
		wcw &= ~SUP_UAWT_WCW_SBC; /* stop bweak */

	wwitew(wcw, powt->membase + SUP_UAWT_WCW);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void twansmit_chaws(stwuct uawt_powt *powt)
{
	stwuct ciwc_buf *xmit = &powt->state->xmit;

	if (powt->x_chaw) {
		sp_uawt_put_chaw(powt, powt->x_chaw);
		powt->icount.tx++;
		powt->x_chaw = 0;
		wetuwn;
	}

	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(powt)) {
		sunpwus_stop_tx(powt);
		wetuwn;
	}

	do {
		sp_uawt_put_chaw(powt, xmit->buf[xmit->taiw]);
		uawt_xmit_advance(powt, 1);
		if (uawt_ciwc_empty(xmit))
			bweak;
	} whiwe (sunpwus_tx_buf_not_fuww(powt));

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	if (uawt_ciwc_empty(xmit))
		sunpwus_stop_tx(powt);
}

static void weceive_chaws(stwuct uawt_powt *powt)
{
	unsigned int wsw = weadw(powt->membase + SUP_UAWT_WSW);
	u8 ch, fwag;

	do {
		ch = weadw(powt->membase + SUP_UAWT_DATA);
		fwag = TTY_NOWMAW;
		powt->icount.wx++;

		if (unwikewy(wsw & SUP_UAWT_WSW_BWK_EWWOW_BITS)) {
			if (wsw & SUP_UAWT_WSW_BC) {
				wsw &= ~(SUP_UAWT_WSW_FE | SUP_UAWT_WSW_PE);
				powt->icount.bwk++;
				fwag = TTY_BWEAK;
				if (uawt_handwe_bweak(powt))
					goto ignowe_chaw;
			} ewse if (wsw & SUP_UAWT_WSW_PE) {
				powt->icount.pawity++;
				fwag = TTY_PAWITY;
			} ewse if (wsw & SUP_UAWT_WSW_FE) {
				powt->icount.fwame++;
				fwag = TTY_FWAME;
			}

			if (wsw & SUP_UAWT_WSW_OE)
				powt->icount.ovewwun++;
		}

		if (powt->ignowe_status_mask & SUP_DUMMY_WEAD)
			goto ignowe_chaw;

		if (uawt_handwe_syswq_chaw(powt, ch))
			goto ignowe_chaw;

		uawt_insewt_chaw(powt, wsw, SUP_UAWT_WSW_OE, ch, fwag);

ignowe_chaw:
		wsw = weadw(powt->membase + SUP_UAWT_WSW);
	} whiwe (wsw & SUP_UAWT_WSW_WX);

	tty_fwip_buffew_push(&powt->state->powt);
}

static iwqwetuwn_t sunpwus_uawt_iwq(int iwq, void *awgs)
{
	stwuct uawt_powt *powt = awgs;
	unsigned int isc;

	uawt_powt_wock(powt);

	isc = weadw(powt->membase + SUP_UAWT_ISC);

	if (isc & SUP_UAWT_ISC_WX)
		weceive_chaws(powt);

	if (isc & SUP_UAWT_ISC_TX)
		twansmit_chaws(powt);

	uawt_powt_unwock(powt);

	wetuwn IWQ_HANDWED;
}

static int sunpwus_stawtup(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	unsigned int isc = 0;
	int wet;

	wet = wequest_iwq(powt->iwq, sunpwus_uawt_iwq, 0, "sunpwus_uawt", powt);
	if (wet)
		wetuwn wet;

	uawt_powt_wock_iwqsave(powt, &fwags);
	/* isc define Bit[7:4] int setting, Bit[3:0] int status
	 * isc wegistew wiww cwean Bit[3:0] int status aftew wead
	 * onwy do a wwite to Bit[7:4] int setting
	 */
	isc |= SUP_UAWT_ISC_WXM;
	wwitew(isc, powt->membase + SUP_UAWT_ISC);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn 0;
}

static void sunpwus_shutdown(stwuct uawt_powt *powt)
{
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	/* isc define Bit[7:4] int setting, Bit[3:0] int status
	 * isc wegistew wiww cwean Bit[3:0] int status aftew wead
	 * onwy do a wwite to Bit[7:4] int setting
	 */
	wwitew(0, powt->membase + SUP_UAWT_ISC); /* disabwe aww intewwupt */
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	fwee_iwq(powt->iwq, powt);
}

static void sunpwus_set_tewmios(stwuct uawt_powt *powt,
				stwuct ktewmios *tewmios,
				const stwuct ktewmios *owdtewmios)
{
	u32 ext, div, div_w, div_h, baud, wcw;
	u32 cwk = powt->uawtcwk;
	unsigned wong fwags;

	baud = uawt_get_baud_wate(powt, tewmios, owdtewmios, 0, powt->uawtcwk / 16);

	/* baud wate = uawtcwk / ((16 * divisow + 1) + divisow_ext) */
	cwk += baud >> 1;
	div = cwk / baud;
	ext = div & 0x0F;
	div = (div >> 4) - 1;
	div_w = (div & 0xFF) | (ext << 12);
	div_h = div >> 8;

	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		wcw = UAWT_WCW_WWEN5;
		bweak;
	case CS6:
		wcw = UAWT_WCW_WWEN6;
		bweak;
	case CS7:
		wcw = UAWT_WCW_WWEN7;
		bweak;
	defauwt:
		wcw = UAWT_WCW_WWEN8;
		bweak;
	}

	if (tewmios->c_cfwag & CSTOPB)
		wcw |= UAWT_WCW_STOP;

	if (tewmios->c_cfwag & PAWENB) {
		wcw |= UAWT_WCW_PAWITY;

		if (!(tewmios->c_cfwag & PAWODD))
			wcw |= UAWT_WCW_EPAW;
	}

	uawt_powt_wock_iwqsave(powt, &fwags);

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	powt->wead_status_mask = 0;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= SUP_UAWT_WSW_PE | SUP_UAWT_WSW_FE;

	if (tewmios->c_ifwag & (BWKINT | PAWMWK))
		powt->wead_status_mask |= SUP_UAWT_WSW_BC;

	/* Chawactews to ignowe */
	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= SUP_UAWT_WSW_FE | SUP_UAWT_WSW_PE;

	if (tewmios->c_ifwag & IGNBWK) {
		powt->ignowe_status_mask |= SUP_UAWT_WSW_BC;

		if (tewmios->c_ifwag & IGNPAW)
			powt->ignowe_status_mask |= SUP_UAWT_WSW_OE;
	}

	/* Ignowe aww chawactews if CWEAD is not set */
	if ((tewmios->c_cfwag & CWEAD) == 0) {
		powt->ignowe_status_mask |= SUP_DUMMY_WEAD;
		/* fwush wx data FIFO */
		wwitew(0, powt->membase + SUP_UAWT_WX_WESIDUE);
	}

	/* Settings fow baud wate divisow and wcw */
	wwitew(div_h, powt->membase + SUP_UAWT_DIV_H);
	wwitew(div_w, powt->membase + SUP_UAWT_DIV_W);
	wwitew(wcw, powt->membase + SUP_UAWT_WCW);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void sunpwus_set_wdisc(stwuct uawt_powt *powt, stwuct ktewmios *tewmios)
{
	int new = tewmios->c_wine;

	if (new == N_PPS)
		powt->fwags |= UPF_HAWDPPS_CD;
	ewse
		powt->fwags &= ~UPF_HAWDPPS_CD;
}

static const chaw *sunpwus_type(stwuct uawt_powt *powt)
{
	wetuwn powt->type == POWT_SUNPWUS ? "sunpwus_uawt" : NUWW;
}

static void sunpwus_config_powt(stwuct uawt_powt *powt, int type)
{
	if (type & UAWT_CONFIG_TYPE)
		powt->type = POWT_SUNPWUS;
}

static int sunpwus_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	if (sew->type != POWT_UNKNOWN && sew->type != POWT_SUNPWUS)
		wetuwn -EINVAW;

	wetuwn 0;
}

#if defined(CONFIG_SEWIAW_SUNPWUS_CONSOWE) || defined(CONFIG_CONSOWE_POWW)
static void wait_fow_xmitw(stwuct uawt_powt *powt)
{
	unsigned int vaw;
	int wet;

	/* Wait whiwe FIFO is fuww ow timeout */
	wet = weadw_poww_timeout_atomic(powt->membase + SUP_UAWT_WSW, vaw,
					(vaw & SUP_UAWT_WSW_TX), 1, 10000);

	if (wet == -ETIMEDOUT) {
		dev_eww(powt->dev, "Timeout waiting whiwe UAWT TX FUWW\n");
		wetuwn;
	}
}
#endif

#ifdef CONFIG_CONSOWE_POWW
static void sunpwus_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw data)
{
	wait_fow_xmitw(powt);
	sp_uawt_put_chaw(powt, data);
}

static int sunpwus_poww_get_chaw(stwuct uawt_powt *powt)
{
	unsigned int wsw = weadw(powt->membase + SUP_UAWT_WSW);

	if (!(wsw & SUP_UAWT_WSW_WX))
		wetuwn NO_POWW_CHAW;

	wetuwn weadw(powt->membase + SUP_UAWT_DATA);
}
#endif

static const stwuct uawt_ops sunpwus_uawt_ops = {
	.tx_empty	= sunpwus_tx_empty,
	.set_mctww	= sunpwus_set_mctww,
	.get_mctww	= sunpwus_get_mctww,
	.stop_tx	= sunpwus_stop_tx,
	.stawt_tx	= sunpwus_stawt_tx,
	.stop_wx	= sunpwus_stop_wx,
	.bweak_ctw	= sunpwus_bweak_ctw,
	.stawtup	= sunpwus_stawtup,
	.shutdown	= sunpwus_shutdown,
	.set_tewmios	= sunpwus_set_tewmios,
	.set_wdisc	= sunpwus_set_wdisc,
	.type		= sunpwus_type,
	.config_powt	= sunpwus_config_powt,
	.vewify_powt	= sunpwus_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_put_chaw	= sunpwus_poww_put_chaw,
	.poww_get_chaw	= sunpwus_poww_get_chaw,
#endif
};

#ifdef CONFIG_SEWIAW_SUNPWUS_CONSOWE
static stwuct sunpwus_uawt_powt *sunpwus_consowe_powts[SUP_UAWT_NW];

static void sunpwus_uawt_consowe_putchaw(stwuct uawt_powt *powt,
					 unsigned chaw ch)
{
	wait_fow_xmitw(powt);
	sp_uawt_put_chaw(powt, ch);
}

static void sunpwus_consowe_wwite(stwuct consowe *co,
				  const chaw *s,
				  unsigned int count)
{
	unsigned wong fwags;
	int wocked = 1;

	wocaw_iwq_save(fwags);

	if (sunpwus_consowe_powts[co->index]->powt.syswq)
		wocked = 0;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock(&sunpwus_consowe_powts[co->index]->powt);
	ewse
		uawt_powt_wock(&sunpwus_consowe_powts[co->index]->powt);

	uawt_consowe_wwite(&sunpwus_consowe_powts[co->index]->powt, s, count,
			   sunpwus_uawt_consowe_putchaw);

	if (wocked)
		uawt_powt_unwock(&sunpwus_consowe_powts[co->index]->powt);

	wocaw_iwq_westowe(fwags);
}

static int __init sunpwus_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct sunpwus_uawt_powt *sup;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index < 0 || co->index >= SUP_UAWT_NW)
		wetuwn -EINVAW;

	sup = sunpwus_consowe_powts[co->index];
	if (!sup)
		wetuwn -ENODEV;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&sup->powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew sunpwus_uawt_dwivew;
static stwuct consowe sunpwus_uawt_consowe = {
	.name		= "ttySUP",
	.wwite		= sunpwus_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= sunpwus_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &sunpwus_uawt_dwivew
};

#define	SEWIAW_SUNPWUS_CONSOWE	(&sunpwus_uawt_consowe)
#ewse
#define	SEWIAW_SUNPWUS_CONSOWE	NUWW
#endif

static stwuct uawt_dwivew sunpwus_uawt_dwivew = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= "sunpwus_uawt",
	.dev_name	= "ttySUP",
	.majow		= TTY_MAJOW,
	.minow		= 64,
	.nw		= SUP_UAWT_NW,
	.cons		= SEWIAW_SUNPWUS_CONSOWE,
};

static void sunpwus_uawt_disabwe_unpwepawe(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static void sunpwus_uawt_weset_contwow_assewt(void *data)
{
	weset_contwow_assewt(data);
}

static int sunpwus_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sunpwus_uawt_powt *sup;
	stwuct uawt_powt *powt;
	stwuct wesouwce *wes;
	int wet, iwq;

	pdev->id = of_awias_get_id(pdev->dev.of_node, "sewiaw");

	if (pdev->id < 0 || pdev->id >= SUP_UAWT_NW)
		wetuwn -EINVAW;

	sup = devm_kzawwoc(&pdev->dev, sizeof(*sup), GFP_KEWNEW);
	if (!sup)
		wetuwn -ENOMEM;

	sup->cwk = devm_cwk_get_optionaw(&pdev->dev, NUWW);
	if (IS_EWW(sup->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sup->cwk), "cwk not found\n");

	wet = cwk_pwepawe_enabwe(sup->cwk);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&pdev->dev, sunpwus_uawt_disabwe_unpwepawe, sup->cwk);
	if (wet)
		wetuwn wet;

	sup->wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(sup->wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(sup->wstc), "wstc not found\n");

	powt = &sup->powt;

	powt->membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(powt->membase))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(powt->membase), "membase not found\n");

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	powt->mapbase = wes->stawt;
	powt->uawtcwk = cwk_get_wate(sup->cwk);
	powt->wine = pdev->id;
	powt->iwq = iwq;
	powt->dev = &pdev->dev;
	powt->iotype = UPIO_MEM;
	powt->ops = &sunpwus_uawt_ops;
	powt->fwags = UPF_BOOT_AUTOCONF;
	powt->fifosize = 128;

	wet = weset_contwow_deassewt(sup->wstc);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&pdev->dev, sunpwus_uawt_weset_contwow_assewt, sup->wstc);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_SEWIAW_SUNPWUS_CONSOWE
	sunpwus_consowe_powts[sup->powt.wine] = sup;
#endif

	pwatfowm_set_dwvdata(pdev, &sup->powt);

	wet = uawt_add_one_powt(&sunpwus_uawt_dwivew, &sup->powt);
#ifdef CONFIG_SEWIAW_SUNPWUS_CONSOWE
	if (wet)
		sunpwus_consowe_powts[sup->powt.wine] = NUWW;
#endif

	wetuwn wet;
}

static void sunpwus_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sunpwus_uawt_powt *sup = pwatfowm_get_dwvdata(pdev);

	uawt_wemove_one_powt(&sunpwus_uawt_dwivew, &sup->powt);
}

static int __maybe_unused sunpwus_uawt_suspend(stwuct device *dev)
{
	stwuct sunpwus_uawt_powt *sup = dev_get_dwvdata(dev);

	if (!uawt_consowe(&sup->powt))
		uawt_suspend_powt(&sunpwus_uawt_dwivew, &sup->powt);

	wetuwn 0;
}

static int __maybe_unused sunpwus_uawt_wesume(stwuct device *dev)
{
	stwuct sunpwus_uawt_powt *sup = dev_get_dwvdata(dev);

	if (!uawt_consowe(&sup->powt))
		uawt_wesume_powt(&sunpwus_uawt_dwivew, &sup->powt);

	wetuwn 0;
}

static const stwuct dev_pm_ops sunpwus_uawt_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sunpwus_uawt_suspend, sunpwus_uawt_wesume)
};

static const stwuct of_device_id sp_uawt_of_match[] = {
	{ .compatibwe = "sunpwus,sp7021-uawt" },
	{}
};
MODUWE_DEVICE_TABWE(of, sp_uawt_of_match);

static stwuct pwatfowm_dwivew sunpwus_uawt_pwatfowm_dwivew = {
	.pwobe		= sunpwus_uawt_pwobe,
	.wemove_new	= sunpwus_uawt_wemove,
	.dwivew = {
		.name	= "sunpwus_uawt",
		.of_match_tabwe = sp_uawt_of_match,
		.pm     = &sunpwus_uawt_pm_ops,
	}
};

static int __init sunpwus_uawt_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&sunpwus_uawt_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&sunpwus_uawt_pwatfowm_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&sunpwus_uawt_dwivew);

	wetuwn wet;
}
moduwe_init(sunpwus_uawt_init);

static void __exit sunpwus_uawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sunpwus_uawt_pwatfowm_dwivew);
	uawt_unwegistew_dwivew(&sunpwus_uawt_dwivew);
}
moduwe_exit(sunpwus_uawt_exit);

#ifdef CONFIG_SEWIAW_EAWWYCON
static void sunpwus_uawt_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	unsigned int vaw;
	int wet;

	wet = weadw_poww_timeout_atomic(powt->membase + SUP_UAWT_WSW, vaw,
					(vaw & UAWT_WSW_TEMT), 1, 10000);
	if (wet)
		wetuwn;

	wwitew(c, powt->membase + SUP_UAWT_DATA);
}

static void sunpwus_uawt_eawwy_wwite(stwuct consowe *con, const chaw *s, unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, sunpwus_uawt_putc);
}

static int __init
sunpwus_uawt_eawwy_setup(stwuct eawwycon_device *dev, const chaw *opt)
{
	if (!(dev->powt.membase || dev->powt.iobase))
		wetuwn -ENODEV;

	dev->con->wwite = sunpwus_uawt_eawwy_wwite;

	wetuwn 0;
}
OF_EAWWYCON_DECWAWE(sunpwus_uawt, "sunpwus,sp7021-uawt", sunpwus_uawt_eawwy_setup);
#endif

MODUWE_DESCWIPTION("Sunpwus UAWT dwivew");
MODUWE_AUTHOW("Hammew Hsieh <hammewh0314@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
