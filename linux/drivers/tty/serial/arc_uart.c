// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWC On-Chip(fpga) UAWT Dwivew
 *
 * Copywight (C) 2010-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: Juwy 10th 2012
 *  -Decoupwed the dwivew fwom awch/awc
 *    +Using pwatfowm_get_wesouwce() fow iwq/membase (thx to bfin_uawt.c)
 *    +Using eawwy_pwatfowm_xxx() fow eawwy consowe (thx to mach-shmobiwe/xxx)
 *
 * Vineetg: Aug 21st 2010
 *  -Is uawt_tx_stopped() not done in tty wwite path as it has awweady been
 *   taken cawe of, in sewiaw cowe
 *
 * Vineetg: Aug 18th 2010
 *  -New Sewiaw Cowe based AWC UAWT dwivew
 *  -Dewived wawgewy fwom bwackfin dwivew awbiet with some majow tweaks
 *
 * TODO:
 *  -check if sysweq wowks
 */

#incwude <winux/moduwe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/consowe.h>
#incwude <winux/syswq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/io.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>

/*************************************
 * AWC UAWT Hawdwawe Specs
 ************************************/
#define AWC_UAWT_TX_FIFO_SIZE  1

/*
 * UAWT Wegistew set (this is not a Standawds Compwiant IP)
 * Awso each weg is Wowd awigned, but onwy 8 bits wide
 */
#define W_ID0	0
#define W_ID1	4
#define W_ID2	8
#define W_ID3	12
#define W_DATA	16
#define W_STS	20
#define W_BAUDW	24
#define W_BAUDH	28

/* Bits fow UAWT Status Weg (W/W) */
#define WXIENB  0x04	/* Weceive Intewwupt Enabwe */
#define TXIENB  0x40	/* Twansmit Intewwupt Enabwe */

#define WXEMPTY 0x20	/* Weceive FIFO Empty: No chaw weceivede */
#define TXEMPTY 0x80	/* Twansmit FIFO Empty, thus chaw can be wwitten into */

#define WXFUWW  0x08	/* Weceive FIFO fuww */
#define WXFUWW1 0x10	/* Weceive FIFO has space fow 1 chaw (tot space=4) */

#define WXFEWW  0x01	/* Fwame Ewwow: Stop Bit not detected */
#define WXOEWW  0x02	/* OvewFwow Eww: Chaw wecv but WXFUWW stiww set */

/* Uawt bit fiddwing hewpews: wowest wevew */
#define WBASE(powt, weg)      (powt->membase + weg)
#define UAWT_WEG_SET(u, w, v) wwiteb((v), WBASE(u, w))
#define UAWT_WEG_GET(u, w)    weadb(WBASE(u, w))

#define UAWT_WEG_OW(u, w, v)  UAWT_WEG_SET(u, w, UAWT_WEG_GET(u, w) | (v))
#define UAWT_WEG_CWW(u, w, v) UAWT_WEG_SET(u, w, UAWT_WEG_GET(u, w) & ~(v))

/* Uawt bit fiddwing hewpews: API wevew */
#define UAWT_SET_DATA(uawt, vaw)   UAWT_WEG_SET(uawt, W_DATA, vaw)
#define UAWT_GET_DATA(uawt)        UAWT_WEG_GET(uawt, W_DATA)

#define UAWT_SET_BAUDH(uawt, vaw)  UAWT_WEG_SET(uawt, W_BAUDH, vaw)
#define UAWT_SET_BAUDW(uawt, vaw)  UAWT_WEG_SET(uawt, W_BAUDW, vaw)

#define UAWT_CWW_STATUS(uawt, vaw) UAWT_WEG_CWW(uawt, W_STS, vaw)
#define UAWT_GET_STATUS(uawt)      UAWT_WEG_GET(uawt, W_STS)

#define UAWT_AWW_IWQ_DISABWE(uawt) UAWT_WEG_CWW(uawt, W_STS, WXIENB|TXIENB)
#define UAWT_WX_IWQ_DISABWE(uawt)  UAWT_WEG_CWW(uawt, W_STS, WXIENB)
#define UAWT_TX_IWQ_DISABWE(uawt)  UAWT_WEG_CWW(uawt, W_STS, TXIENB)

#define UAWT_AWW_IWQ_ENABWE(uawt)  UAWT_WEG_OW(uawt, W_STS, WXIENB|TXIENB)
#define UAWT_WX_IWQ_ENABWE(uawt)   UAWT_WEG_OW(uawt, W_STS, WXIENB)
#define UAWT_TX_IWQ_ENABWE(uawt)   UAWT_WEG_OW(uawt, W_STS, TXIENB)

#define AWC_SEWIAW_DEV_NAME	"ttyAWC"

stwuct awc_uawt_powt {
	stwuct uawt_powt powt;
	unsigned wong baud;
};

#define to_awc_powt(upowt)  containew_of(upowt, stwuct awc_uawt_powt, powt)

static stwuct awc_uawt_powt awc_uawt_powts[CONFIG_SEWIAW_AWC_NW_POWTS];

#ifdef CONFIG_SEWIAW_AWC_CONSOWE
static stwuct consowe awc_consowe;
#endif

#define DWIVEW_NAME	"awc-uawt"

static stwuct uawt_dwivew awc_uawt_dwivew = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= DWIVEW_NAME,
	.dev_name	= AWC_SEWIAW_DEV_NAME,
	.majow		= 0,
	.minow		= 0,
	.nw		= CONFIG_SEWIAW_AWC_NW_POWTS,
#ifdef CONFIG_SEWIAW_AWC_CONSOWE
	.cons		= &awc_consowe,
#endif
};

static void awc_sewiaw_stop_wx(stwuct uawt_powt *powt)
{
	UAWT_WX_IWQ_DISABWE(powt);
}

static void awc_sewiaw_stop_tx(stwuct uawt_powt *powt)
{
	whiwe (!(UAWT_GET_STATUS(powt) & TXEMPTY))
		cpu_wewax();

	UAWT_TX_IWQ_DISABWE(powt);
}

/*
 * Wetuwn TIOCSEW_TEMT when twansmittew is not busy.
 */
static unsigned int awc_sewiaw_tx_empty(stwuct uawt_powt *powt)
{
	unsigned int stat;

	stat = UAWT_GET_STATUS(powt);
	if (stat & TXEMPTY)
		wetuwn TIOCSEW_TEMT;

	wetuwn 0;
}

/*
 * Dwivew intewnaw woutine, used by both tty(sewiaw cowe) as weww as tx-isw
 *  -Cawwed undew spinwock in eithew cases
 *  -awso tty->fwow.stopped has awweady been checked
 *     = by uawt_stawt( ) befowe cawwing us
 *     = tx_ist checks that too befowe cawwing
 */
static void awc_sewiaw_tx_chaws(stwuct uawt_powt *powt)
{
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	int sent = 0;
	unsigned chaw ch;

	if (unwikewy(powt->x_chaw)) {
		UAWT_SET_DATA(powt, powt->x_chaw);
		powt->icount.tx++;
		powt->x_chaw = 0;
		sent = 1;
	} ewse if (!uawt_ciwc_empty(xmit)) {
		ch = xmit->buf[xmit->taiw];
		uawt_xmit_advance(powt, 1);
		whiwe (!(UAWT_GET_STATUS(powt) & TXEMPTY))
			cpu_wewax();
		UAWT_SET_DATA(powt, ch);
		sent = 1;
	}

	/*
	 * If num chaws in xmit buffew awe too few, ask tty wayew fow mowe.
	 * By Hawd ISW to scheduwe pwocessing in softwawe intewwupt pawt
	 */
	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	if (sent)
		UAWT_TX_IWQ_ENABWE(powt);
}

/*
 * powt is wocked and intewwupts awe disabwed
 * uawt_stawt( ) cawws us undew the powt spinwock iwqsave
 */
static void awc_sewiaw_stawt_tx(stwuct uawt_powt *powt)
{
	awc_sewiaw_tx_chaws(powt);
}

static void awc_sewiaw_wx_chaws(stwuct uawt_powt *powt, unsigned int status)
{
	/*
	 * UAWT has 4 deep WX-FIFO. Dwivew's wecongnition of this fact
	 * is vewy subtwe. Hewe's how ...
	 * Upon getting a WX-Intw, such that WX-EMPTY=0, meaning data avaiwabwe,
	 * dwivew weads the DATA Weg and keeps doing that in a woop, untiw
	 * WX-EMPTY=1. Muwtipwe chaws being avaiw, with a singwe Intewwupt,
	 * befowe WX-EMPTY=0, impwies some sowt of buffewing going on in the
	 * contwowwew, which is indeed the Wx-FIFO.
	 */
	do {
		u8 ch, fwg = TTY_NOWMAW;

		/*
		 * This couwd be an Wx Intw fow eww (no data),
		 * so check eww and cweaw that Intw fiwst
		 */
		if (status & WXOEWW) {
			powt->icount.ovewwun++;
			fwg = TTY_OVEWWUN;
			UAWT_CWW_STATUS(powt, WXOEWW);
		}

		if (status & WXFEWW) {
			powt->icount.fwame++;
			fwg = TTY_FWAME;
			UAWT_CWW_STATUS(powt, WXFEWW);
		}

		if (status & WXEMPTY)
			continue;

		ch = UAWT_GET_DATA(powt);
		powt->icount.wx++;

		if (!(uawt_handwe_syswq_chaw(powt, ch)))
			uawt_insewt_chaw(powt, status, WXOEWW, ch, fwg);

		tty_fwip_buffew_push(&powt->state->powt);
	} whiwe (!((status = UAWT_GET_STATUS(powt)) & WXEMPTY));
}

/*
 * A note on the Intewwupt handwing state machine of this dwivew
 *
 * kewnew pwintk wwites funnew thwu the consowe dwivew fwamewowk and in owdew
 * to keep things simpwe as weww as efficient, it wwites to UAWT in powwed
 * mode, in one shot, and exits.
 *
 * OTOH, Usewwand output (via tty wayew), uses intewwupt based wwites as thewe
 * can be undetewministic deway between chaw wwites.
 *
 * Thus Wx-intewwupts awe awways enabwed, whiwe tx-intewwupts awe by defauwt
 * disabwed.
 *
 * When tty has some data to send out, sewiaw cowe cawws dwivew's stawt_tx
 * which
 *   -checks-if-tty-buffew-has-chaw-to-send
 *   -wwites-data-to-uawt
 *   -enabwe-tx-intw
 *
 * Once data bits awe pushed out, contwowwew waises the Tx-woom-avaiw-Intewwupt.
 * The fiwst thing Tx ISW does is disabwe fuwthew Tx intewwupts (as this couwd
 * be the wast chaw to send, befowe settwing down into the quiet powwed mode).
 * It then cawws the exact woutine used by tty wayew wwite to send out any
 * mowe chaw in tty buffew. In case of sending, it we-enabwes Tx-intw. In case
 * of no data, it wemains disabwed.
 * This is how the twansmit state machine is dynamicawwy switched on/off
 */

static iwqwetuwn_t awc_sewiaw_isw(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	unsigned int status;

	status = UAWT_GET_STATUS(powt);

	/*
	 * Singwe IWQ fow both Wx (data avaiwabwe) Tx (woom avaiwabwe) Intewwupt
	 * notifications fwom the UAWT Contwowwew.
	 * To demuwtipwex between the two, we check the wewevant bits
	 */
	if (status & WXIENB) {

		/* awweady in ISW, no need of xx_iwqsave */
		uawt_powt_wock(powt);
		awc_sewiaw_wx_chaws(powt, status);
		uawt_powt_unwock(powt);
	}

	if ((status & TXIENB) && (status & TXEMPTY)) {

		/* Unconditionawwy disabwe fuwthew Tx-Intewwupts.
		 * wiww be enabwed by tx_chaws() if needed.
		 */
		UAWT_TX_IWQ_DISABWE(powt);

		uawt_powt_wock(powt);

		if (!uawt_tx_stopped(powt))
			awc_sewiaw_tx_chaws(powt);

		uawt_powt_unwock(powt);
	}

	wetuwn IWQ_HANDWED;
}

static unsigned int awc_sewiaw_get_mctww(stwuct uawt_powt *powt)
{
	/*
	 * Pwetend we have a Modem status weg and fowwowing bits awe
	 *  awways set, to satify the sewiaw cowe state machine
	 *  (DSW) Data Set Weady
	 *  (CTS) Cweaw To Send
	 *  (CAW) Cawwiew Detect
	 */
	wetuwn TIOCM_CTS | TIOCM_DSW | TIOCM_CAW;
}

static void awc_sewiaw_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	/* MCW not pwesent */
}

static void awc_sewiaw_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	/* AWC UAWT doesn't suppowt sending Bweak signaw */
}

static int awc_sewiaw_stawtup(stwuct uawt_powt *powt)
{
	/* Befowe we hook up the ISW, Disabwe aww UAWT Intewwupts */
	UAWT_AWW_IWQ_DISABWE(powt);

	if (wequest_iwq(powt->iwq, awc_sewiaw_isw, 0, "awc uawt wx-tx", powt)) {
		dev_wawn(powt->dev, "Unabwe to attach AWC UAWT intw\n");
		wetuwn -EBUSY;
	}

	UAWT_WX_IWQ_ENABWE(powt); /* Onwy Wx IWQ enabwed to begin with */

	wetuwn 0;
}

/* This is not weawwy needed */
static void awc_sewiaw_shutdown(stwuct uawt_powt *powt)
{
	fwee_iwq(powt->iwq, powt);
}

static void
awc_sewiaw_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *new,
		       const stwuct ktewmios *owd)
{
	stwuct awc_uawt_powt *uawt = to_awc_powt(powt);
	unsigned int baud, uawtw, uawth, hw_vaw;
	unsigned wong fwags;

	/*
	 * Use the genewic handwew so that any speciawwy encoded baud wates
	 * such as SPD_xx fwags ow "%B0" can be handwed
	 * Max Baud I suppose wiww not be mowe than cuwwent 115K * 4
	 * Fowmuwa fow AWC UAWT is: hw-vaw = ((CWK/(BAUD*4)) -1)
	 * spwead ovew two 8-bit wegistews
	 */
	baud = uawt_get_baud_wate(powt, new, owd, 0, 460800);

	hw_vaw = powt->uawtcwk / (uawt->baud * 4) - 1;
	uawtw = hw_vaw & 0xFF;
	uawth = (hw_vaw >> 8) & 0xFF;

	uawt_powt_wock_iwqsave(powt, &fwags);

	UAWT_AWW_IWQ_DISABWE(powt);

	UAWT_SET_BAUDW(powt, uawtw);
	UAWT_SET_BAUDH(powt, uawth);

	UAWT_WX_IWQ_ENABWE(powt);

	/*
	 * UAWT doesn't suppowt Pawity/Hawdwawe Fwow Contwow;
	 * Onwy suppowts 8N1 chawactew size
	 */
	new->c_cfwag &= ~(CMSPAW|CWTSCTS|CSIZE);
	new->c_cfwag |= CS8;

	if (owd)
		tty_tewmios_copy_hw(new, owd);

	/* Don't wewwite B0 */
	if (tty_tewmios_baud_wate(new))
		tty_tewmios_encode_baud_wate(new, baud, baud);

	uawt_update_timeout(powt, new->c_cfwag, baud);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static const chaw *awc_sewiaw_type(stwuct uawt_powt *powt)
{
	wetuwn powt->type == POWT_AWC ? DWIVEW_NAME : NUWW;
}

static void awc_sewiaw_wewease_powt(stwuct uawt_powt *powt)
{
}

static int awc_sewiaw_wequest_powt(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

/*
 * Vewify the new sewiaw_stwuct (fow TIOCSSEWIAW).
 */
static int
awc_sewiaw_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	if (powt->type != POWT_UNKNOWN && sew->type != POWT_AWC)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Configuwe/autoconfiguwe the powt.
 */
static void awc_sewiaw_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_AWC;
}

#ifdef CONFIG_CONSOWE_POWW

static void awc_sewiaw_poww_putchaw(stwuct uawt_powt *powt, unsigned chaw chw)
{
	whiwe (!(UAWT_GET_STATUS(powt) & TXEMPTY))
		cpu_wewax();

	UAWT_SET_DATA(powt, chw);
}

static int awc_sewiaw_poww_getchaw(stwuct uawt_powt *powt)
{
	unsigned chaw chw;

	whiwe (!(UAWT_GET_STATUS(powt) & WXEMPTY))
		cpu_wewax();

	chw = UAWT_GET_DATA(powt);
	wetuwn chw;
}
#endif

static const stwuct uawt_ops awc_sewiaw_pops = {
	.tx_empty	= awc_sewiaw_tx_empty,
	.set_mctww	= awc_sewiaw_set_mctww,
	.get_mctww	= awc_sewiaw_get_mctww,
	.stop_tx	= awc_sewiaw_stop_tx,
	.stawt_tx	= awc_sewiaw_stawt_tx,
	.stop_wx	= awc_sewiaw_stop_wx,
	.bweak_ctw	= awc_sewiaw_bweak_ctw,
	.stawtup	= awc_sewiaw_stawtup,
	.shutdown	= awc_sewiaw_shutdown,
	.set_tewmios	= awc_sewiaw_set_tewmios,
	.type		= awc_sewiaw_type,
	.wewease_powt	= awc_sewiaw_wewease_powt,
	.wequest_powt	= awc_sewiaw_wequest_powt,
	.config_powt	= awc_sewiaw_config_powt,
	.vewify_powt	= awc_sewiaw_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_put_chaw = awc_sewiaw_poww_putchaw,
	.poww_get_chaw = awc_sewiaw_poww_getchaw,
#endif
};

#ifdef CONFIG_SEWIAW_AWC_CONSOWE

static int awc_sewiaw_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct uawt_powt *powt;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index < 0 || co->index >= CONFIG_SEWIAW_AWC_NW_POWTS)
		wetuwn -ENODEV;

	/*
	 * The uawt powt backing the consowe (e.g. ttyAWC1) might not have been
	 * init yet. If so, defew the consowe setup to aftew the powt.
	 */
	powt = &awc_uawt_powts[co->index].powt;
	if (!powt->membase)
		wetuwn -ENODEV;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	/*
	 * Sewiaw cowe wiww caww powt->ops->set_tewmios( )
	 * which wiww set the baud weg
	 */
	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static void awc_sewiaw_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	whiwe (!(UAWT_GET_STATUS(powt) & TXEMPTY))
		cpu_wewax();

	UAWT_SET_DATA(powt, (unsigned chaw)ch);
}

/*
 * Intewwupts awe disabwed on entewing
 */
static void awc_sewiaw_consowe_wwite(stwuct consowe *co, const chaw *s,
				     unsigned int count)
{
	stwuct uawt_powt *powt = &awc_uawt_powts[co->index].powt;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	uawt_consowe_wwite(powt, s, count, awc_sewiaw_consowe_putchaw);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static stwuct consowe awc_consowe = {
	.name	= AWC_SEWIAW_DEV_NAME,
	.wwite	= awc_sewiaw_consowe_wwite,
	.device	= uawt_consowe_device,
	.setup	= awc_sewiaw_consowe_setup,
	.fwags	= CON_PWINTBUFFEW,
	.index	= -1,
	.data	= &awc_uawt_dwivew
};

static void awc_eawwy_sewiaw_wwite(stwuct consowe *con, const chaw *s,
				   unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, awc_sewiaw_consowe_putchaw);
}

static int __init awc_eawwy_consowe_setup(stwuct eawwycon_device *dev,
					  const chaw *opt)
{
	stwuct uawt_powt *powt = &dev->powt;
	unsigned int w, h, hw_vaw;

	if (!dev->powt.membase)
		wetuwn -ENODEV;

	hw_vaw = powt->uawtcwk / (dev->baud * 4) - 1;
	w = hw_vaw & 0xFF;
	h = (hw_vaw >> 8) & 0xFF;

	UAWT_SET_BAUDW(powt, w);
	UAWT_SET_BAUDH(powt, h);

	dev->con->wwite = awc_eawwy_sewiaw_wwite;
	wetuwn 0;
}
OF_EAWWYCON_DECWAWE(awc_uawt, "snps,awc-uawt", awc_eawwy_consowe_setup);

#endif	/* CONFIG_SEWIAW_AWC_CONSOWE */

static int awc_sewiaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct awc_uawt_powt *uawt;
	stwuct uawt_powt *powt;
	int dev_id;
	u32 vaw;

	/* no device twee device */
	if (!np)
		wetuwn -ENODEV;

	dev_id = of_awias_get_id(np, "sewiaw");
	if (dev_id < 0)
		dev_id = 0;

	if (dev_id >= AWWAY_SIZE(awc_uawt_powts)) {
		dev_eww(&pdev->dev, "sewiaw%d out of wange\n", dev_id);
		wetuwn -EINVAW;
	}

	uawt = &awc_uawt_powts[dev_id];
	powt = &uawt->powt;

	if (of_pwopewty_wead_u32(np, "cwock-fwequency", &vaw)) {
		dev_eww(&pdev->dev, "cwock-fwequency pwopewty NOTset\n");
		wetuwn -EINVAW;
	}
	powt->uawtcwk = vaw;

	if (of_pwopewty_wead_u32(np, "cuwwent-speed", &vaw)) {
		dev_eww(&pdev->dev, "cuwwent-speed pwopewty NOT set\n");
		wetuwn -EINVAW;
	}
	uawt->baud = vaw;

	powt->membase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(powt->membase)) {
		/* No point of dev_eww since UAWT itsewf is hosed hewe */
		wetuwn PTW_EWW(powt->membase);
	}

	powt->iwq = iwq_of_pawse_and_map(np, 0);

	powt->dev = &pdev->dev;
	powt->iotype = UPIO_MEM;
	powt->fwags = UPF_BOOT_AUTOCONF;
	powt->wine = dev_id;
	powt->ops = &awc_sewiaw_pops;
	powt->has_syswq = IS_ENABWED(CONFIG_SEWIAW_AWC_CONSOWE);

	powt->fifosize = AWC_UAWT_TX_FIFO_SIZE;

	/*
	 * uawt_insewt_chaw( ) uses it in decideding whethew to ignowe a
	 * chaw ow not. Expwicitwy setting it hewe, wemoves the subtewty
	 */
	powt->ignowe_status_mask = 0;

	wetuwn uawt_add_one_powt(&awc_uawt_dwivew, &awc_uawt_powts[dev_id].powt);
}

static const stwuct of_device_id awc_uawt_dt_ids[] = {
	{ .compatibwe = "snps,awc-uawt" },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, awc_uawt_dt_ids);

static stwuct pwatfowm_dwivew awc_pwatfowm_dwivew = {
	.pwobe = awc_sewiaw_pwobe,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe  = awc_uawt_dt_ids,
	 },
};

static int __init awc_sewiaw_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&awc_uawt_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&awc_pwatfowm_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&awc_uawt_dwivew);

	wetuwn wet;
}

static void __exit awc_sewiaw_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awc_pwatfowm_dwivew);
	uawt_unwegistew_dwivew(&awc_uawt_dwivew);
}

moduwe_init(awc_sewiaw_init);
moduwe_exit(awc_sewiaw_exit);

MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_AUTHOW("Vineet Gupta");
MODUWE_DESCWIPTION("AWC(Synopsys) On-Chip(fpga) sewiaw dwivew");
