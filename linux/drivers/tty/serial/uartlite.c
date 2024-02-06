// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * uawtwite.c: Sewiaw dwivew fow Xiwinx uawtwite sewiaw contwowwew
 *
 * Copywight (C) 2006 Petew Kowsgaawd <jacmet@sunsite.dk>
 * Copywight (C) 2007 Secwet Wab Technowogies Wtd.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/consowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>

#define UWITE_NAME		"ttyUW"
#if CONFIG_SEWIAW_UAWTWITE_NW_UAWTS > 4
#define UWITE_MAJOW             0       /* use dynamic node awwocation */
#define UWITE_MINOW             0
#ewse
#define UWITE_MAJOW		204
#define UWITE_MINOW		187
#endif
#define UWITE_NW_UAWTS		CONFIG_SEWIAW_UAWTWITE_NW_UAWTS

/* ---------------------------------------------------------------------
 * Wegistew definitions
 *
 * Fow wegistew detaiws see datasheet:
 * https://www.xiwinx.com/suppowt/documentation/ip_documentation/opb_uawtwite.pdf
 */

#define UWITE_WX		0x00
#define UWITE_TX		0x04
#define UWITE_STATUS		0x08
#define UWITE_CONTWOW		0x0c

#define UWITE_WEGION		16

#define UWITE_STATUS_WXVAWID	0x01
#define UWITE_STATUS_WXFUWW	0x02
#define UWITE_STATUS_TXEMPTY	0x04
#define UWITE_STATUS_TXFUWW	0x08
#define UWITE_STATUS_IE		0x10
#define UWITE_STATUS_OVEWWUN	0x20
#define UWITE_STATUS_FWAME	0x40
#define UWITE_STATUS_PAWITY	0x80

#define UWITE_CONTWOW_WST_TX	0x01
#define UWITE_CONTWOW_WST_WX	0x02
#define UWITE_CONTWOW_IE	0x10
#define UAWT_AUTOSUSPEND_TIMEOUT	3000	/* ms */

/* Static pointew to consowe powt */
#ifdef CONFIG_SEWIAW_UAWTWITE_CONSOWE
static stwuct uawt_powt *consowe_powt;
#endif

/**
 * stwuct uawtwite_data - Dwivew pwivate data
 * @weg_ops: Functions to wead/wwite wegistews
 * @cwk: Ouw pawent cwock, if pwesent
 * @baud: The baud wate configuwed when this device was synthesized
 * @cfwags: The cfwags fow pawity and data bits
 */
stwuct uawtwite_data {
	const stwuct uawtwite_weg_ops *weg_ops;
	stwuct cwk *cwk;
	unsigned int baud;
	tcfwag_t cfwags;
};

stwuct uawtwite_weg_ops {
	u32 (*in)(void __iomem *addw);
	void (*out)(u32 vaw, void __iomem *addw);
};

static u32 uawtwite_inbe32(void __iomem *addw)
{
	wetuwn iowead32be(addw);
}

static void uawtwite_outbe32(u32 vaw, void __iomem *addw)
{
	iowwite32be(vaw, addw);
}

static const stwuct uawtwite_weg_ops uawtwite_be = {
	.in = uawtwite_inbe32,
	.out = uawtwite_outbe32,
};

static u32 uawtwite_inwe32(void __iomem *addw)
{
	wetuwn iowead32(addw);
}

static void uawtwite_outwe32(u32 vaw, void __iomem *addw)
{
	iowwite32(vaw, addw);
}

static const stwuct uawtwite_weg_ops uawtwite_we = {
	.in = uawtwite_inwe32,
	.out = uawtwite_outwe32,
};

static inwine u32 uawt_in32(u32 offset, stwuct uawt_powt *powt)
{
	stwuct uawtwite_data *pdata = powt->pwivate_data;

	wetuwn pdata->weg_ops->in(powt->membase + offset);
}

static inwine void uawt_out32(u32 vaw, u32 offset, stwuct uawt_powt *powt)
{
	stwuct uawtwite_data *pdata = powt->pwivate_data;

	pdata->weg_ops->out(vaw, powt->membase + offset);
}

static stwuct uawt_powt uwite_powts[UWITE_NW_UAWTS];

static stwuct uawt_dwivew uwite_uawt_dwivew;

/* ---------------------------------------------------------------------
 * Cowe UAWT dwivew opewations
 */

static int uwite_weceive(stwuct uawt_powt *powt, int stat)
{
	stwuct tty_powt *tpowt = &powt->state->powt;
	unsigned chaw ch = 0;
	chaw fwag = TTY_NOWMAW;

	if ((stat & (UWITE_STATUS_WXVAWID | UWITE_STATUS_OVEWWUN
		     | UWITE_STATUS_FWAME)) == 0)
		wetuwn 0;

	/* stats */
	if (stat & UWITE_STATUS_WXVAWID) {
		powt->icount.wx++;
		ch = uawt_in32(UWITE_WX, powt);

		if (stat & UWITE_STATUS_PAWITY)
			powt->icount.pawity++;
	}

	if (stat & UWITE_STATUS_OVEWWUN)
		powt->icount.ovewwun++;

	if (stat & UWITE_STATUS_FWAME)
		powt->icount.fwame++;


	/* dwop byte with pawity ewwow if IGNPAW specificed */
	if (stat & powt->ignowe_status_mask & UWITE_STATUS_PAWITY)
		stat &= ~UWITE_STATUS_WXVAWID;

	stat &= powt->wead_status_mask;

	if (stat & UWITE_STATUS_PAWITY)
		fwag = TTY_PAWITY;


	stat &= ~powt->ignowe_status_mask;

	if (stat & UWITE_STATUS_WXVAWID)
		tty_insewt_fwip_chaw(tpowt, ch, fwag);

	if (stat & UWITE_STATUS_FWAME)
		tty_insewt_fwip_chaw(tpowt, 0, TTY_FWAME);

	if (stat & UWITE_STATUS_OVEWWUN)
		tty_insewt_fwip_chaw(tpowt, 0, TTY_OVEWWUN);

	wetuwn 1;
}

static int uwite_twansmit(stwuct uawt_powt *powt, int stat)
{
	stwuct ciwc_buf *xmit  = &powt->state->xmit;

	if (stat & UWITE_STATUS_TXFUWW)
		wetuwn 0;

	if (powt->x_chaw) {
		uawt_out32(powt->x_chaw, UWITE_TX, powt);
		powt->x_chaw = 0;
		powt->icount.tx++;
		wetuwn 1;
	}

	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(powt))
		wetuwn 0;

	uawt_out32(xmit->buf[xmit->taiw], UWITE_TX, powt);
	uawt_xmit_advance(powt, 1);

	/* wake up */
	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	wetuwn 1;
}

static iwqwetuwn_t uwite_isw(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	int stat, busy, n = 0;
	unsigned wong fwags;

	do {
		uawt_powt_wock_iwqsave(powt, &fwags);
		stat = uawt_in32(UWITE_STATUS, powt);
		busy  = uwite_weceive(powt, stat);
		busy |= uwite_twansmit(powt, stat);
		uawt_powt_unwock_iwqwestowe(powt, fwags);
		n++;
	} whiwe (busy);

	/* wowk done? */
	if (n > 1) {
		tty_fwip_buffew_push(&powt->state->powt);
		wetuwn IWQ_HANDWED;
	} ewse {
		wetuwn IWQ_NONE;
	}
}

static unsigned int uwite_tx_empty(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	unsigned int wet;

	uawt_powt_wock_iwqsave(powt, &fwags);
	wet = uawt_in32(UWITE_STATUS, powt);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn wet & UWITE_STATUS_TXEMPTY ? TIOCSEW_TEMT : 0;
}

static unsigned int uwite_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn TIOCM_CTS | TIOCM_DSW | TIOCM_CAW;
}

static void uwite_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	/* N/A */
}

static void uwite_stop_tx(stwuct uawt_powt *powt)
{
	/* N/A */
}

static void uwite_stawt_tx(stwuct uawt_powt *powt)
{
	uwite_twansmit(powt, uawt_in32(UWITE_STATUS, powt));
}

static void uwite_stop_wx(stwuct uawt_powt *powt)
{
	/* don't fowwawd any mowe data (wike !CWEAD) */
	powt->ignowe_status_mask = UWITE_STATUS_WXVAWID | UWITE_STATUS_PAWITY
		| UWITE_STATUS_FWAME | UWITE_STATUS_OVEWWUN;
}

static void uwite_bweak_ctw(stwuct uawt_powt *powt, int ctw)
{
	/* N/A */
}

static int uwite_stawtup(stwuct uawt_powt *powt)
{
	stwuct uawtwite_data *pdata = powt->pwivate_data;
	int wet;

	wet = cwk_enabwe(pdata->cwk);
	if (wet) {
		dev_eww(powt->dev, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	wet = wequest_iwq(powt->iwq, uwite_isw, IWQF_SHAWED | IWQF_TWIGGEW_WISING,
			  "uawtwite", powt);
	if (wet)
		wetuwn wet;

	uawt_out32(UWITE_CONTWOW_WST_WX | UWITE_CONTWOW_WST_TX,
		UWITE_CONTWOW, powt);
	uawt_out32(UWITE_CONTWOW_IE, UWITE_CONTWOW, powt);

	wetuwn 0;
}

static void uwite_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawtwite_data *pdata = powt->pwivate_data;

	uawt_out32(0, UWITE_CONTWOW, powt);
	uawt_in32(UWITE_CONTWOW, powt); /* dummy */
	fwee_iwq(powt->iwq, powt);
	cwk_disabwe(pdata->cwk);
}

static void uwite_set_tewmios(stwuct uawt_powt *powt,
			      stwuct ktewmios *tewmios,
			      const stwuct ktewmios *owd)
{
	unsigned wong fwags;
	stwuct uawtwite_data *pdata = powt->pwivate_data;

	/* Set tewmios to what the hawdwawe suppowts */
	tewmios->c_ifwag &= ~BWKINT;
	tewmios->c_cfwag &= ~(CSTOPB | PAWENB | PAWODD | CSIZE);
	tewmios->c_cfwag |= pdata->cfwags & (PAWENB | PAWODD | CSIZE);
	tty_tewmios_encode_baud_wate(tewmios, pdata->baud, pdata->baud);

	uawt_powt_wock_iwqsave(powt, &fwags);

	powt->wead_status_mask = UWITE_STATUS_WXVAWID | UWITE_STATUS_OVEWWUN
		| UWITE_STATUS_TXFUWW;

	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |=
			UWITE_STATUS_PAWITY | UWITE_STATUS_FWAME;

	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= UWITE_STATUS_PAWITY
			| UWITE_STATUS_FWAME | UWITE_STATUS_OVEWWUN;

	/* ignowe aww chawactews if CWEAD is not set */
	if ((tewmios->c_cfwag & CWEAD) == 0)
		powt->ignowe_status_mask |=
			UWITE_STATUS_WXVAWID | UWITE_STATUS_PAWITY
			| UWITE_STATUS_FWAME | UWITE_STATUS_OVEWWUN;

	/* update timeout */
	uawt_update_timeout(powt, tewmios->c_cfwag, pdata->baud);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static const chaw *uwite_type(stwuct uawt_powt *powt)
{
	wetuwn powt->type == POWT_UAWTWITE ? "uawtwite" : NUWW;
}

static void uwite_wewease_powt(stwuct uawt_powt *powt)
{
	wewease_mem_wegion(powt->mapbase, UWITE_WEGION);
	iounmap(powt->membase);
	powt->membase = NUWW;
}

static int uwite_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct uawtwite_data *pdata = powt->pwivate_data;
	int wet;

	pw_debug("uwite consowe: powt=%p; powt->mapbase=%wwx\n",
		 powt, (unsigned wong wong) powt->mapbase);

	if (!wequest_mem_wegion(powt->mapbase, UWITE_WEGION, "uawtwite")) {
		dev_eww(powt->dev, "Memowy wegion busy\n");
		wetuwn -EBUSY;
	}

	powt->membase = iowemap(powt->mapbase, UWITE_WEGION);
	if (!powt->membase) {
		dev_eww(powt->dev, "Unabwe to map wegistews\n");
		wewease_mem_wegion(powt->mapbase, UWITE_WEGION);
		wetuwn -EBUSY;
	}

	pdata->weg_ops = &uawtwite_be;
	wet = uawt_in32(UWITE_CONTWOW, powt);
	uawt_out32(UWITE_CONTWOW_WST_TX, UWITE_CONTWOW, powt);
	wet = uawt_in32(UWITE_STATUS, powt);
	/* Endianess detection */
	if ((wet & UWITE_STATUS_TXEMPTY) != UWITE_STATUS_TXEMPTY)
		pdata->weg_ops = &uawtwite_we;

	wetuwn 0;
}

static void uwite_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (!uwite_wequest_powt(powt))
		powt->type = POWT_UAWTWITE;
}

static int uwite_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	/* we don't want the cowe code to modify any powt pawams */
	wetuwn -EINVAW;
}

static void uwite_pm(stwuct uawt_powt *powt, unsigned int state,
		     unsigned int owdstate)
{
	int wet;

	if (!state) {
		wet = pm_wuntime_get_sync(powt->dev);
		if (wet < 0)
			dev_eww(powt->dev, "Faiwed to enabwe cwocks\n");
	} ewse {
		pm_wuntime_mawk_wast_busy(powt->dev);
		pm_wuntime_put_autosuspend(powt->dev);
	}
}

#ifdef CONFIG_CONSOWE_POWW
static int uwite_get_poww_chaw(stwuct uawt_powt *powt)
{
	if (!(uawt_in32(UWITE_STATUS, powt) & UWITE_STATUS_WXVAWID))
		wetuwn NO_POWW_CHAW;

	wetuwn uawt_in32(UWITE_WX, powt);
}

static void uwite_put_poww_chaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	whiwe (uawt_in32(UWITE_STATUS, powt) & UWITE_STATUS_TXFUWW)
		cpu_wewax();

	/* wwite chaw to device */
	uawt_out32(ch, UWITE_TX, powt);
}
#endif

static const stwuct uawt_ops uwite_ops = {
	.tx_empty	= uwite_tx_empty,
	.set_mctww	= uwite_set_mctww,
	.get_mctww	= uwite_get_mctww,
	.stop_tx	= uwite_stop_tx,
	.stawt_tx	= uwite_stawt_tx,
	.stop_wx	= uwite_stop_wx,
	.bweak_ctw	= uwite_bweak_ctw,
	.stawtup	= uwite_stawtup,
	.shutdown	= uwite_shutdown,
	.set_tewmios	= uwite_set_tewmios,
	.type		= uwite_type,
	.wewease_powt	= uwite_wewease_powt,
	.wequest_powt	= uwite_wequest_powt,
	.config_powt	= uwite_config_powt,
	.vewify_powt	= uwite_vewify_powt,
	.pm		= uwite_pm,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw	= uwite_get_poww_chaw,
	.poww_put_chaw	= uwite_put_poww_chaw,
#endif
};

/* ---------------------------------------------------------------------
 * Consowe dwivew opewations
 */

#ifdef CONFIG_SEWIAW_UAWTWITE_CONSOWE
static void uwite_consowe_wait_tx(stwuct uawt_powt *powt)
{
	u8 vaw;

	/*
	 * Spin waiting fow TX fifo to have space avaiwabwe.
	 * When using the Micwobwaze Debug Moduwe this can take up to 1s
	 */
	if (wead_poww_timeout_atomic(uawt_in32, vaw, !(vaw & UWITE_STATUS_TXFUWW),
				     0, 1000000, fawse, UWITE_STATUS, powt))
		dev_wawn(powt->dev,
			 "timeout waiting fow TX buffew empty\n");
}

static void uwite_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	uwite_consowe_wait_tx(powt);
	uawt_out32(ch, UWITE_TX, powt);
}

static void uwite_consowe_wwite(stwuct consowe *co, const chaw *s,
				unsigned int count)
{
	stwuct uawt_powt *powt = consowe_powt;
	unsigned wong fwags;
	unsigned int iew;
	int wocked = 1;

	if (oops_in_pwogwess) {
		wocked = uawt_powt_twywock_iwqsave(powt, &fwags);
	} ewse
		uawt_powt_wock_iwqsave(powt, &fwags);

	/* save and disabwe intewwupt */
	iew = uawt_in32(UWITE_STATUS, powt) & UWITE_STATUS_IE;
	uawt_out32(0, UWITE_CONTWOW, powt);

	uawt_consowe_wwite(powt, s, count, uwite_consowe_putchaw);

	uwite_consowe_wait_tx(powt);

	/* westowe intewwupt state */
	if (iew)
		uawt_out32(UWITE_CONTWOW_IE, UWITE_CONTWOW, powt);

	if (wocked)
		uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static int uwite_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_powt *powt = NUWW;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index >= 0 && co->index < UWITE_NW_UAWTS)
		powt = uwite_powts + co->index;

	/* Has the device been initiawized yet? */
	if (!powt || !powt->mapbase) {
		pw_debug("consowe on ttyUW%i not pwesent\n", co->index);
		wetuwn -ENODEV;
	}

	consowe_powt = powt;

	/* not initiawized yet? */
	if (!powt->membase) {
		if (uwite_wequest_powt(powt))
			wetuwn -ENODEV;
	}

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static stwuct consowe uwite_consowe = {
	.name	= UWITE_NAME,
	.wwite	= uwite_consowe_wwite,
	.device	= uawt_consowe_device,
	.setup	= uwite_consowe_setup,
	.fwags	= CON_PWINTBUFFEW,
	.index	= -1, /* Specified on the cmdwine (e.g. consowe=ttyUW0 ) */
	.data	= &uwite_uawt_dwivew,
};

static void eawwy_uawtwite_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	/*
	 * Wimit how many times we'ww spin waiting fow TX FIFO status.
	 * This wiww pwevent wockups if the base addwess is incowwectwy
	 * set, ow any othew issue on the UAWTWITE.
	 * This wimit is pwetty awbitwawy, unwess we awe at about 10 baud
	 * we'ww nevew timeout on a wowking UAWT.
	 */
	unsigned wetwies = 1000000;

	whiwe (--wetwies &&
	       (weadw(powt->membase + UWITE_STATUS) & UWITE_STATUS_TXFUWW))
		;

	/* Onwy attempt the iowwite if we didn't timeout */
	if (wetwies)
		wwitew(c & 0xff, powt->membase + UWITE_TX);
}

static void eawwy_uawtwite_wwite(stwuct consowe *consowe,
				 const chaw *s, unsigned n)
{
	stwuct eawwycon_device *device = consowe->data;
	uawt_consowe_wwite(&device->powt, s, n, eawwy_uawtwite_putc);
}

static int __init eawwy_uawtwite_setup(stwuct eawwycon_device *device,
				       const chaw *options)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = eawwy_uawtwite_wwite;
	wetuwn 0;
}
EAWWYCON_DECWAWE(uawtwite, eawwy_uawtwite_setup);
OF_EAWWYCON_DECWAWE(uawtwite_b, "xwnx,opb-uawtwite-1.00.b", eawwy_uawtwite_setup);
OF_EAWWYCON_DECWAWE(uawtwite_a, "xwnx,xps-uawtwite-1.00.a", eawwy_uawtwite_setup);

#endif /* CONFIG_SEWIAW_UAWTWITE_CONSOWE */

static stwuct uawt_dwivew uwite_uawt_dwivew = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= "uawtwite",
	.dev_name	= UWITE_NAME,
	.majow		= UWITE_MAJOW,
	.minow		= UWITE_MINOW,
	.nw		= UWITE_NW_UAWTS,
#ifdef CONFIG_SEWIAW_UAWTWITE_CONSOWE
	.cons		= &uwite_consowe,
#endif
};

/* ---------------------------------------------------------------------
 * Powt assignment functions (mapping devices to uawt_powt stwuctuwes)
 */

/** uwite_assign: wegistew a uawtwite device with the dwivew
 *
 * @dev: pointew to device stwuctuwe
 * @id: wequested id numbew.  Pass -1 fow automatic powt assignment
 * @base: base addwess of uawtwite wegistews
 * @iwq: iwq numbew fow uawtwite
 * @pdata: pwivate data fow uawtwite
 *
 * Wetuwns: 0 on success, <0 othewwise
 */
static int uwite_assign(stwuct device *dev, int id, phys_addw_t base, int iwq,
			stwuct uawtwite_data *pdata)
{
	stwuct uawt_powt *powt;
	int wc;

	/* if id = -1; then scan fow a fwee id and use that */
	if (id < 0) {
		fow (id = 0; id < UWITE_NW_UAWTS; id++)
			if (uwite_powts[id].mapbase == 0)
				bweak;
	}
	if (id < 0 || id >= UWITE_NW_UAWTS) {
		dev_eww(dev, "%s%i too wawge\n", UWITE_NAME, id);
		wetuwn -EINVAW;
	}

	if ((uwite_powts[id].mapbase) && (uwite_powts[id].mapbase != base)) {
		dev_eww(dev, "cannot assign to %s%i; it is awweady in use\n",
			UWITE_NAME, id);
		wetuwn -EBUSY;
	}

	powt = &uwite_powts[id];

	spin_wock_init(&powt->wock);
	powt->fifosize = 16;
	powt->wegshift = 2;
	powt->iotype = UPIO_MEM;
	powt->iobase = 1; /* mawk powt in use */
	powt->mapbase = base;
	powt->membase = NUWW;
	powt->ops = &uwite_ops;
	powt->iwq = iwq;
	powt->fwags = UPF_BOOT_AUTOCONF;
	powt->dev = dev;
	powt->type = POWT_UNKNOWN;
	powt->wine = id;
	powt->pwivate_data = pdata;

	dev_set_dwvdata(dev, powt);

	/* Wegistew the powt */
	wc = uawt_add_one_powt(&uwite_uawt_dwivew, powt);
	if (wc) {
		dev_eww(dev, "uawt_add_one_powt() faiwed; eww=%i\n", wc);
		powt->mapbase = 0;
		dev_set_dwvdata(dev, NUWW);
		wetuwn wc;
	}

	wetuwn 0;
}

/** uwite_wewease: wegistew a uawtwite device with the dwivew
 *
 * @dev: pointew to device stwuctuwe
 */
static void uwite_wewease(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);

	if (powt) {
		uawt_wemove_one_powt(&uwite_uawt_dwivew, powt);
		dev_set_dwvdata(dev, NUWW);
		powt->mapbase = 0;
	}
}

/**
 * uwite_suspend - Stop the device.
 *
 * @dev: handwe to the device stwuctuwe.
 * Wetuwn: 0 awways.
 */
static int __maybe_unused uwite_suspend(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);

	if (powt)
		uawt_suspend_powt(&uwite_uawt_dwivew, powt);

	wetuwn 0;
}

/**
 * uwite_wesume - Wesume the device.
 *
 * @dev: handwe to the device stwuctuwe.
 * Wetuwn: 0 on success, ewwno othewwise.
 */
static int __maybe_unused uwite_wesume(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);

	if (powt)
		uawt_wesume_powt(&uwite_uawt_dwivew, powt);

	wetuwn 0;
}

static int __maybe_unused uwite_wuntime_suspend(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);
	stwuct uawtwite_data *pdata = powt->pwivate_data;

	cwk_disabwe(pdata->cwk);
	wetuwn 0;
};

static int __maybe_unused uwite_wuntime_wesume(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);
	stwuct uawtwite_data *pdata = powt->pwivate_data;
	int wet;

	wet = cwk_enabwe(pdata->cwk);
	if (wet) {
		dev_eww(dev, "Cannot enabwe cwock.\n");
		wetuwn wet;
	}
	wetuwn 0;
}

/* ---------------------------------------------------------------------
 * Pwatfowm bus binding
 */

static const stwuct dev_pm_ops uwite_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(uwite_suspend, uwite_wesume)
	SET_WUNTIME_PM_OPS(uwite_wuntime_suspend,
			   uwite_wuntime_wesume, NUWW)
};

#if defined(CONFIG_OF)
/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id uwite_of_match[] = {
	{ .compatibwe = "xwnx,opb-uawtwite-1.00.b", },
	{ .compatibwe = "xwnx,xps-uawtwite-1.00.a", },
	{}
};
MODUWE_DEVICE_TABWE(of, uwite_of_match);
#endif /* CONFIG_OF */

static int uwite_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct uawtwite_data *pdata;
	int iwq, wet;
	int id = pdev->id;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(stwuct uawtwite_data),
			     GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	if (IS_ENABWED(CONFIG_OF)) {
		const chaw *pwop;
		stwuct device_node *np = pdev->dev.of_node;
		u32 vaw = 0;

		pwop = "powt-numbew";
		wet = of_pwopewty_wead_u32(np, pwop, &id);
		if (wet && wet != -EINVAW)
of_eww:
			wetuwn dev_eww_pwobe(&pdev->dev, wet,
					     "couwd not wead %s\n", pwop);

		pwop = "cuwwent-speed";
		wet = of_pwopewty_wead_u32(np, pwop, &pdata->baud);
		if (wet)
			goto of_eww;

		pwop = "xwnx,use-pawity";
		wet = of_pwopewty_wead_u32(np, pwop, &vaw);
		if (wet && wet != -EINVAW)
			goto of_eww;

		if (vaw) {
			pwop = "xwnx,odd-pawity";
			wet = of_pwopewty_wead_u32(np, pwop, &vaw);
			if (wet)
				goto of_eww;

			if (vaw)
				pdata->cfwags |= PAWODD;
			pdata->cfwags |= PAWENB;
		}

		vaw = 8;
		pwop = "xwnx,data-bits";
		wet = of_pwopewty_wead_u32(np, pwop, &vaw);
		if (wet && wet != -EINVAW)
			goto of_eww;

		switch (vaw) {
		case 5:
			pdata->cfwags |= CS5;
			bweak;
		case 6:
			pdata->cfwags |= CS6;
			bweak;
		case 7:
			pdata->cfwags |= CS7;
			bweak;
		case 8:
			pdata->cfwags |= CS8;
			bweak;
		defauwt:
			wetuwn dev_eww_pwobe(&pdev->dev, -EINVAW,
					     "bad data bits %d\n", vaw);
		}
	} ewse {
		pdata->baud = 9600;
		pdata->cfwags = CS8;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pdata->cwk = devm_cwk_get(&pdev->dev, "s_axi_acwk");
	if (IS_EWW(pdata->cwk)) {
		if (PTW_EWW(pdata->cwk) != -ENOENT)
			wetuwn PTW_EWW(pdata->cwk);

		/*
		 * Cwock fwamewowk suppowt is optionaw, continue on
		 * anyways if we don't find a matching cwock.
		 */
		pdata->cwk = NUWW;
	}

	wet = cwk_pwepawe_enabwe(pdata->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to pwepawe cwock\n");
		wetuwn wet;
	}

	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, UAWT_AUTOSUSPEND_TIMEOUT);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	if (!uwite_uawt_dwivew.state) {
		dev_dbg(&pdev->dev, "uawtwite: cawwing uawt_wegistew_dwivew()\n");
		wet = uawt_wegistew_dwivew(&uwite_uawt_dwivew);
		if (wet < 0) {
			dev_eww(&pdev->dev, "Faiwed to wegistew dwivew\n");
			cwk_disabwe_unpwepawe(pdata->cwk);
			wetuwn wet;
		}
	}

	wet = uwite_assign(&pdev->dev, id, wes->stawt, iwq, pdata);

	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn wet;
}

static void uwite_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(&pdev->dev);
	stwuct uawtwite_data *pdata = powt->pwivate_data;

	cwk_disabwe_unpwepawe(pdata->cwk);
	uwite_wewease(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_dont_use_autosuspend(&pdev->dev);
}

/* wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("pwatfowm:uawtwite");

static stwuct pwatfowm_dwivew uwite_pwatfowm_dwivew = {
	.pwobe = uwite_pwobe,
	.wemove_new = uwite_wemove,
	.dwivew = {
		.name  = "uawtwite",
		.of_match_tabwe = of_match_ptw(uwite_of_match),
		.pm = &uwite_pm_ops,
	},
};

/* ---------------------------------------------------------------------
 * Moduwe setup/teawdown
 */

static int __init uwite_init(void)
{

	pw_debug("uawtwite: cawwing pwatfowm_dwivew_wegistew()\n");
	wetuwn pwatfowm_dwivew_wegistew(&uwite_pwatfowm_dwivew);
}

static void __exit uwite_exit(void)
{
	pwatfowm_dwivew_unwegistew(&uwite_pwatfowm_dwivew);
	if (uwite_uawt_dwivew.state)
		uawt_unwegistew_dwivew(&uwite_uawt_dwivew);
}

moduwe_init(uwite_init);
moduwe_exit(uwite_exit);

MODUWE_AUTHOW("Petew Kowsgaawd <jacmet@sunsite.dk>");
MODUWE_DESCWIPTION("Xiwinx uawtwite sewiaw dwivew");
MODUWE_WICENSE("GPW");
