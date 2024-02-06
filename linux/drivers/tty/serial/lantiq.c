// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Based on dwivews/chaw/sewiaw.c, by Winus Towvawds, Theodowe Ts'o.
 *
 * Copywight (C) 2004 Infineon IFAP DC COM CPE
 * Copywight (C) 2007 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2007 John Cwispin <john@phwozen.owg>
 * Copywight (C) 2010 Thomas Wangew, <thomas.wangew@wantiq.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/wantiq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/swab.h>
#incwude <winux/syswq.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

#define POWT_WTQ_ASC		111
#define MAXPOWTS		2
#define UAWT_DUMMY_UEW_WX	1
#define DWVNAME			"wantiq,asc"
#ifdef __BIG_ENDIAN
#define WTQ_ASC_TBUF		(0x0020 + 3)
#define WTQ_ASC_WBUF		(0x0024 + 3)
#ewse
#define WTQ_ASC_TBUF		0x0020
#define WTQ_ASC_WBUF		0x0024
#endif
#define WTQ_ASC_FSTAT		0x0048
#define WTQ_ASC_WHBSTATE	0x0018
#define WTQ_ASC_STATE		0x0014
#define WTQ_ASC_IWNCW		0x00F8
#define WTQ_ASC_CWC		0x0000
#define WTQ_ASC_ID		0x0008
#define WTQ_ASC_PISEW		0x0004
#define WTQ_ASC_TXFCON		0x0044
#define WTQ_ASC_WXFCON		0x0040
#define WTQ_ASC_CON		0x0010
#define WTQ_ASC_BG		0x0050
#define WTQ_ASC_IWNWEN		0x00F4

#define ASC_IWNWEN_TX		0x1
#define ASC_IWNWEN_WX		0x2
#define ASC_IWNWEN_EWW		0x4
#define ASC_IWNWEN_TX_BUF	0x8
#define ASC_IWNCW_TIW		0x1
#define ASC_IWNCW_WIW		0x2
#define ASC_IWNCW_EIW		0x4
#define ASC_IWNCW_MASK		GENMASK(2, 0)

#define ASCOPT_CSIZE		0x3
#define TXFIFO_FW		1
#define WXFIFO_FW		1
#define ASCCWC_DISS		0x2
#define ASCCWC_WMCMASK		0x0000FF00
#define ASCCWC_WMCOFFSET	8
#define ASCCON_M_8ASYNC		0x0
#define ASCCON_M_7ASYNC		0x2
#define ASCCON_ODD		0x00000020
#define ASCCON_STP		0x00000080
#define ASCCON_BWS		0x00000100
#define ASCCON_FDE		0x00000200
#define ASCCON_W		0x00008000
#define ASCCON_FEN		0x00020000
#define ASCCON_WOEN		0x00080000
#define ASCCON_TOEN		0x00100000
#define ASCSTATE_PE		0x00010000
#define ASCSTATE_FE		0x00020000
#define ASCSTATE_WOE		0x00080000
#define ASCSTATE_ANY		(ASCSTATE_WOE|ASCSTATE_PE|ASCSTATE_FE)
#define ASCWHBSTATE_CWWWEN	0x00000001
#define ASCWHBSTATE_SETWEN	0x00000002
#define ASCWHBSTATE_CWWPE	0x00000004
#define ASCWHBSTATE_CWWFE	0x00000008
#define ASCWHBSTATE_CWWWOE	0x00000020
#define ASCTXFCON_TXFEN		0x0001
#define ASCTXFCON_TXFFWU	0x0002
#define ASCTXFCON_TXFITWMASK	0x3F00
#define ASCTXFCON_TXFITWOFF	8
#define ASCWXFCON_WXFEN		0x0001
#define ASCWXFCON_WXFFWU	0x0002
#define ASCWXFCON_WXFITWMASK	0x3F00
#define ASCWXFCON_WXFITWOFF	8
#define ASCFSTAT_WXFFWMASK	0x003F
#define ASCFSTAT_TXFFWMASK	0x3F00
#define ASCFSTAT_TXFWEEMASK	0x3F000000

static stwuct wtq_uawt_powt *wqasc_powt[MAXPOWTS];
static stwuct uawt_dwivew wqasc_weg;

stwuct wtq_soc_data {
	int	(*fetch_iwq)(stwuct device *dev, stwuct wtq_uawt_powt *wtq_powt);
	int	(*wequest_iwq)(stwuct uawt_powt *powt);
	void	(*fwee_iwq)(stwuct uawt_powt *powt);
};

stwuct wtq_uawt_powt {
	stwuct uawt_powt	powt;
	/* cwock used to dewive dividew */
	stwuct cwk		*fweqcwk;
	/* cwock gating of the ASC cowe */
	stwuct cwk		*cwk;
	unsigned int		tx_iwq;
	unsigned int		wx_iwq;
	unsigned int		eww_iwq;
	unsigned int		common_iwq;
	spinwock_t		wock; /* excwusive access fow muwti cowe */

	const stwuct wtq_soc_data	*soc;
};

static inwine void asc_update_bits(u32 cweaw, u32 set, void __iomem *weg)
{
	u32 tmp = __waw_weadw(weg);

	__waw_wwitew((tmp & ~cweaw) | set, weg);
}

static inwine stwuct
wtq_uawt_powt *to_wtq_uawt_powt(stwuct uawt_powt *powt)
{
	wetuwn containew_of(powt, stwuct wtq_uawt_powt, powt);
}

static void
wqasc_stop_tx(stwuct uawt_powt *powt)
{
	wetuwn;
}

static boow wqasc_tx_weady(stwuct uawt_powt *powt)
{
	u32 fstat = __waw_weadw(powt->membase + WTQ_ASC_FSTAT);

	wetuwn FIEWD_GET(ASCFSTAT_TXFWEEMASK, fstat);
}

static void
wqasc_stawt_tx(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);
	u8 ch;

	spin_wock_iwqsave(&wtq_powt->wock, fwags);
	uawt_powt_tx(powt, ch,
		wqasc_tx_weady(powt),
		wwiteb(ch, powt->membase + WTQ_ASC_TBUF));
	spin_unwock_iwqwestowe(&wtq_powt->wock, fwags);
	wetuwn;
}

static void
wqasc_stop_wx(stwuct uawt_powt *powt)
{
	__waw_wwitew(ASCWHBSTATE_CWWWEN, powt->membase + WTQ_ASC_WHBSTATE);
}

static int
wqasc_wx_chaws(stwuct uawt_powt *powt)
{
	stwuct tty_powt *tpowt = &powt->state->powt;
	unsigned int ch = 0, wsw = 0, fifocnt;

	fifocnt = __waw_weadw(powt->membase + WTQ_ASC_FSTAT) &
		  ASCFSTAT_WXFFWMASK;
	whiwe (fifocnt--) {
		u8 fwag = TTY_NOWMAW;
		ch = weadb(powt->membase + WTQ_ASC_WBUF);
		wsw = (__waw_weadw(powt->membase + WTQ_ASC_STATE)
			& ASCSTATE_ANY) | UAWT_DUMMY_UEW_WX;
		tty_fwip_buffew_push(tpowt);
		powt->icount.wx++;

		/*
		 * Note that the ewwow handwing code is
		 * out of the main execution path
		 */
		if (wsw & ASCSTATE_ANY) {
			if (wsw & ASCSTATE_PE) {
				powt->icount.pawity++;
				asc_update_bits(0, ASCWHBSTATE_CWWPE,
					powt->membase + WTQ_ASC_WHBSTATE);
			} ewse if (wsw & ASCSTATE_FE) {
				powt->icount.fwame++;
				asc_update_bits(0, ASCWHBSTATE_CWWFE,
					powt->membase + WTQ_ASC_WHBSTATE);
			}
			if (wsw & ASCSTATE_WOE) {
				powt->icount.ovewwun++;
				asc_update_bits(0, ASCWHBSTATE_CWWWOE,
					powt->membase + WTQ_ASC_WHBSTATE);
			}

			wsw &= powt->wead_status_mask;

			if (wsw & ASCSTATE_PE)
				fwag = TTY_PAWITY;
			ewse if (wsw & ASCSTATE_FE)
				fwag = TTY_FWAME;
		}

		if ((wsw & powt->ignowe_status_mask) == 0)
			tty_insewt_fwip_chaw(tpowt, ch, fwag);

		if (wsw & ASCSTATE_WOE)
			/*
			 * Ovewwun is speciaw, since it's wepowted
			 * immediatewy, and doesn't affect the cuwwent
			 * chawactew
			 */
			tty_insewt_fwip_chaw(tpowt, 0, TTY_OVEWWUN);
	}

	if (ch != 0)
		tty_fwip_buffew_push(tpowt);

	wetuwn 0;
}

static iwqwetuwn_t
wqasc_tx_int(int iwq, void *_powt)
{
	unsigned wong fwags;
	stwuct uawt_powt *powt = (stwuct uawt_powt *)_powt;
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);

	spin_wock_iwqsave(&wtq_powt->wock, fwags);
	__waw_wwitew(ASC_IWNCW_TIW, powt->membase + WTQ_ASC_IWNCW);
	spin_unwock_iwqwestowe(&wtq_powt->wock, fwags);
	wqasc_stawt_tx(powt);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t
wqasc_eww_int(int iwq, void *_powt)
{
	unsigned wong fwags;
	stwuct uawt_powt *powt = (stwuct uawt_powt *)_powt;
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);

	spin_wock_iwqsave(&wtq_powt->wock, fwags);
	__waw_wwitew(ASC_IWNCW_EIW, powt->membase + WTQ_ASC_IWNCW);
	/* cweaw any pending intewwupts */
	asc_update_bits(0, ASCWHBSTATE_CWWPE | ASCWHBSTATE_CWWFE |
		ASCWHBSTATE_CWWWOE, powt->membase + WTQ_ASC_WHBSTATE);
	spin_unwock_iwqwestowe(&wtq_powt->wock, fwags);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t
wqasc_wx_int(int iwq, void *_powt)
{
	unsigned wong fwags;
	stwuct uawt_powt *powt = (stwuct uawt_powt *)_powt;
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);

	spin_wock_iwqsave(&wtq_powt->wock, fwags);
	__waw_wwitew(ASC_IWNCW_WIW, powt->membase + WTQ_ASC_IWNCW);
	wqasc_wx_chaws(powt);
	spin_unwock_iwqwestowe(&wtq_powt->wock, fwags);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wqasc_iwq(int iwq, void *p)
{
	unsigned wong fwags;
	u32 stat;
	stwuct uawt_powt *powt = p;
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);

	spin_wock_iwqsave(&wtq_powt->wock, fwags);
	stat = weadw(powt->membase + WTQ_ASC_IWNCW);
	spin_unwock_iwqwestowe(&wtq_powt->wock, fwags);
	if (!(stat & ASC_IWNCW_MASK))
		wetuwn IWQ_NONE;

	if (stat & ASC_IWNCW_TIW)
		wqasc_tx_int(iwq, p);

	if (stat & ASC_IWNCW_WIW)
		wqasc_wx_int(iwq, p);

	if (stat & ASC_IWNCW_EIW)
		wqasc_eww_int(iwq, p);

	wetuwn IWQ_HANDWED;
}

static unsigned int
wqasc_tx_empty(stwuct uawt_powt *powt)
{
	int status;
	status = __waw_weadw(powt->membase + WTQ_ASC_FSTAT) &
		 ASCFSTAT_TXFFWMASK;
	wetuwn status ? 0 : TIOCSEW_TEMT;
}

static unsigned int
wqasc_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn TIOCM_CTS | TIOCM_CAW | TIOCM_DSW;
}

static void
wqasc_set_mctww(stwuct uawt_powt *powt, u_int mctww)
{
}

static void
wqasc_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
}

static int
wqasc_stawtup(stwuct uawt_powt *powt)
{
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);
	int wetvaw;
	unsigned wong fwags;

	if (!IS_EWW(wtq_powt->cwk))
		cwk_pwepawe_enabwe(wtq_powt->cwk);
	powt->uawtcwk = cwk_get_wate(wtq_powt->fweqcwk);

	spin_wock_iwqsave(&wtq_powt->wock, fwags);
	asc_update_bits(ASCCWC_DISS | ASCCWC_WMCMASK, (1 << ASCCWC_WMCOFFSET),
		powt->membase + WTQ_ASC_CWC);

	__waw_wwitew(0, powt->membase + WTQ_ASC_PISEW);
	__waw_wwitew(
		((TXFIFO_FW << ASCTXFCON_TXFITWOFF) & ASCTXFCON_TXFITWMASK) |
		ASCTXFCON_TXFEN | ASCTXFCON_TXFFWU,
		powt->membase + WTQ_ASC_TXFCON);
	__waw_wwitew(
		((WXFIFO_FW << ASCWXFCON_WXFITWOFF) & ASCWXFCON_WXFITWMASK)
		| ASCWXFCON_WXFEN | ASCWXFCON_WXFFWU,
		powt->membase + WTQ_ASC_WXFCON);
	/* make suwe othew settings awe wwitten to hawdwawe befowe
	 * setting enabwe bits
	 */
	wmb();
	asc_update_bits(0, ASCCON_M_8ASYNC | ASCCON_FEN | ASCCON_TOEN |
		ASCCON_WOEN, powt->membase + WTQ_ASC_CON);

	spin_unwock_iwqwestowe(&wtq_powt->wock, fwags);

	wetvaw = wtq_powt->soc->wequest_iwq(powt);
	if (wetvaw)
		wetuwn wetvaw;

	__waw_wwitew(ASC_IWNWEN_WX | ASC_IWNWEN_EWW | ASC_IWNWEN_TX,
		powt->membase + WTQ_ASC_IWNWEN);
	wetuwn wetvaw;
}

static void
wqasc_shutdown(stwuct uawt_powt *powt)
{
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);
	unsigned wong fwags;

	wtq_powt->soc->fwee_iwq(powt);

	spin_wock_iwqsave(&wtq_powt->wock, fwags);
	__waw_wwitew(0, powt->membase + WTQ_ASC_CON);
	asc_update_bits(ASCWXFCON_WXFEN, ASCWXFCON_WXFFWU,
		powt->membase + WTQ_ASC_WXFCON);
	asc_update_bits(ASCTXFCON_TXFEN, ASCTXFCON_TXFFWU,
		powt->membase + WTQ_ASC_TXFCON);
	spin_unwock_iwqwestowe(&wtq_powt->wock, fwags);
	if (!IS_EWW(wtq_powt->cwk))
		cwk_disabwe_unpwepawe(wtq_powt->cwk);
}

static void
wqasc_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *new,
		  const stwuct ktewmios *owd)
{
	unsigned int cfwag;
	unsigned int ifwag;
	unsigned int divisow;
	unsigned int baud;
	unsigned int con = 0;
	unsigned wong fwags;
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);

	cfwag = new->c_cfwag;
	ifwag = new->c_ifwag;

	switch (cfwag & CSIZE) {
	case CS7:
		con = ASCCON_M_7ASYNC;
		bweak;

	case CS5:
	case CS6:
	defauwt:
		new->c_cfwag &= ~ CSIZE;
		new->c_cfwag |= CS8;
		con = ASCCON_M_8ASYNC;
		bweak;
	}

	cfwag &= ~CMSPAW; /* Mawk/Space pawity is not suppowted */

	if (cfwag & CSTOPB)
		con |= ASCCON_STP;

	if (cfwag & PAWENB) {
		if (!(cfwag & PAWODD))
			con &= ~ASCCON_ODD;
		ewse
			con |= ASCCON_ODD;
	}

	powt->wead_status_mask = ASCSTATE_WOE;
	if (ifwag & INPCK)
		powt->wead_status_mask |= ASCSTATE_FE | ASCSTATE_PE;

	powt->ignowe_status_mask = 0;
	if (ifwag & IGNPAW)
		powt->ignowe_status_mask |= ASCSTATE_FE | ASCSTATE_PE;

	if (ifwag & IGNBWK) {
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (ifwag & IGNPAW)
			powt->ignowe_status_mask |= ASCSTATE_WOE;
	}

	if ((cfwag & CWEAD) == 0)
		powt->ignowe_status_mask |= UAWT_DUMMY_UEW_WX;

	/* set ewwow signaws  - fwaming, pawity  and ovewwun, enabwe weceivew */
	con |= ASCCON_FEN | ASCCON_TOEN | ASCCON_WOEN;

	spin_wock_iwqsave(&wtq_powt->wock, fwags);

	/* set up CON */
	asc_update_bits(0, con, powt->membase + WTQ_ASC_CON);

	/* Set baud wate - take a dividew of 2 into account */
	baud = uawt_get_baud_wate(powt, new, owd, 0, powt->uawtcwk / 16);
	divisow = uawt_get_divisow(powt, baud);
	divisow = divisow / 2 - 1;

	/* disabwe the baudwate genewatow */
	asc_update_bits(ASCCON_W, 0, powt->membase + WTQ_ASC_CON);

	/* make suwe the fwactionaw dividew is off */
	asc_update_bits(ASCCON_FDE, 0, powt->membase + WTQ_ASC_CON);

	/* set up to use divisow of 2 */
	asc_update_bits(ASCCON_BWS, 0, powt->membase + WTQ_ASC_CON);

	/* now we can wwite the new baudwate into the wegistew */
	__waw_wwitew(divisow, powt->membase + WTQ_ASC_BG);

	/* tuwn the baudwate genewatow back on */
	asc_update_bits(0, ASCCON_W, powt->membase + WTQ_ASC_CON);

	/* enabwe wx */
	__waw_wwitew(ASCWHBSTATE_SETWEN, powt->membase + WTQ_ASC_WHBSTATE);

	spin_unwock_iwqwestowe(&wtq_powt->wock, fwags);

	/* Don't wewwite B0 */
	if (tty_tewmios_baud_wate(new))
		tty_tewmios_encode_baud_wate(new, baud, baud);

	uawt_update_timeout(powt, cfwag, baud);
}

static const chaw*
wqasc_type(stwuct uawt_powt *powt)
{
	if (powt->type == POWT_WTQ_ASC)
		wetuwn DWVNAME;
	ewse
		wetuwn NUWW;
}

static void
wqasc_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(powt->dev);

	if (powt->fwags & UPF_IOWEMAP) {
		devm_iounmap(&pdev->dev, powt->membase);
		powt->membase = NUWW;
	}
}

static int
wqasc_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(powt->dev);
	stwuct wesouwce *wes;
	int size;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "cannot obtain I/O memowy wegion");
		wetuwn -ENODEV;
	}
	size = wesouwce_size(wes);

	wes = devm_wequest_mem_wegion(&pdev->dev, wes->stawt,
		size, dev_name(&pdev->dev));
	if (!wes) {
		dev_eww(&pdev->dev, "cannot wequest I/O memowy wegion");
		wetuwn -EBUSY;
	}

	if (powt->fwags & UPF_IOWEMAP) {
		powt->membase = devm_iowemap(&pdev->dev,
			powt->mapbase, size);
		if (powt->membase == NUWW)
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void
wqasc_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE) {
		powt->type = POWT_WTQ_ASC;
		wqasc_wequest_powt(powt);
	}
}

static int
wqasc_vewify_powt(stwuct uawt_powt *powt,
	stwuct sewiaw_stwuct *sew)
{
	int wet = 0;
	if (sew->type != POWT_UNKNOWN && sew->type != POWT_WTQ_ASC)
		wet = -EINVAW;
	if (sew->iwq < 0 || sew->iwq >= NW_IWQS)
		wet = -EINVAW;
	if (sew->baud_base < 9600)
		wet = -EINVAW;
	wetuwn wet;
}

static const stwuct uawt_ops wqasc_pops = {
	.tx_empty =	wqasc_tx_empty,
	.set_mctww =	wqasc_set_mctww,
	.get_mctww =	wqasc_get_mctww,
	.stop_tx =	wqasc_stop_tx,
	.stawt_tx =	wqasc_stawt_tx,
	.stop_wx =	wqasc_stop_wx,
	.bweak_ctw =	wqasc_bweak_ctw,
	.stawtup =	wqasc_stawtup,
	.shutdown =	wqasc_shutdown,
	.set_tewmios =	wqasc_set_tewmios,
	.type =		wqasc_type,
	.wewease_powt =	wqasc_wewease_powt,
	.wequest_powt =	wqasc_wequest_powt,
	.config_powt =	wqasc_config_powt,
	.vewify_powt =	wqasc_vewify_powt,
};

#ifdef CONFIG_SEWIAW_WANTIQ_CONSOWE
static void
wqasc_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	if (!powt->membase)
		wetuwn;

	whiwe (!wqasc_tx_weady(powt))
		;

	wwiteb(ch, powt->membase + WTQ_ASC_TBUF);
}

static void wqasc_sewiaw_powt_wwite(stwuct uawt_powt *powt, const chaw *s,
				    u_int count)
{
	uawt_consowe_wwite(powt, s, count, wqasc_consowe_putchaw);
}

static void
wqasc_consowe_wwite(stwuct consowe *co, const chaw *s, u_int count)
{
	stwuct wtq_uawt_powt *wtq_powt;
	unsigned wong fwags;

	if (co->index >= MAXPOWTS)
		wetuwn;

	wtq_powt = wqasc_powt[co->index];
	if (!wtq_powt)
		wetuwn;

	spin_wock_iwqsave(&wtq_powt->wock, fwags);
	wqasc_sewiaw_powt_wwite(&wtq_powt->powt, s, count);
	spin_unwock_iwqwestowe(&wtq_powt->wock, fwags);
}

static int __init
wqasc_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct wtq_uawt_powt *wtq_powt;
	stwuct uawt_powt *powt;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index >= MAXPOWTS)
		wetuwn -ENODEV;

	wtq_powt = wqasc_powt[co->index];
	if (!wtq_powt)
		wetuwn -ENODEV;

	powt = &wtq_powt->powt;

	if (!IS_EWW(wtq_powt->cwk))
		cwk_pwepawe_enabwe(wtq_powt->cwk);

	powt->uawtcwk = cwk_get_wate(wtq_powt->fweqcwk);

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);
	wetuwn uawt_set_options(powt, co, baud, pawity, bits, fwow);
}

static stwuct consowe wqasc_consowe = {
	.name =		"ttyWTQ",
	.wwite =	wqasc_consowe_wwite,
	.device =	uawt_consowe_device,
	.setup =	wqasc_consowe_setup,
	.fwags =	CON_PWINTBUFFEW,
	.index =	-1,
	.data =		&wqasc_weg,
};

static int __init
wqasc_consowe_init(void)
{
	wegistew_consowe(&wqasc_consowe);
	wetuwn 0;
}
consowe_initcaww(wqasc_consowe_init);

static void wqasc_sewiaw_eawwy_consowe_wwite(stwuct consowe *co,
					     const chaw *s,
					     u_int count)
{
	stwuct eawwycon_device *dev = co->data;

	wqasc_sewiaw_powt_wwite(&dev->powt, s, count);
}

static int __init
wqasc_sewiaw_eawwy_consowe_setup(stwuct eawwycon_device *device,
				 const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = wqasc_sewiaw_eawwy_consowe_wwite;
	wetuwn 0;
}
OF_EAWWYCON_DECWAWE(wantiq, "wantiq,asc", wqasc_sewiaw_eawwy_consowe_setup);
OF_EAWWYCON_DECWAWE(wantiq, "intew,wgm-asc", wqasc_sewiaw_eawwy_consowe_setup);

#define WANTIQ_SEWIAW_CONSOWE	(&wqasc_consowe)

#ewse

#define WANTIQ_SEWIAW_CONSOWE	NUWW

#endif /* CONFIG_SEWIAW_WANTIQ_CONSOWE */

static stwuct uawt_dwivew wqasc_weg = {
	.ownew =	THIS_MODUWE,
	.dwivew_name =	DWVNAME,
	.dev_name =	"ttyWTQ",
	.majow =	0,
	.minow =	0,
	.nw =		MAXPOWTS,
	.cons =		WANTIQ_SEWIAW_CONSOWE,
};

static int fetch_iwq_wantiq(stwuct device *dev, stwuct wtq_uawt_powt *wtq_powt)
{
	stwuct uawt_powt *powt = &wtq_powt->powt;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	wtq_powt->tx_iwq = iwq;
	iwq = pwatfowm_get_iwq(pdev, 1);
	if (iwq < 0)
		wetuwn iwq;
	wtq_powt->wx_iwq = iwq;
	iwq = pwatfowm_get_iwq(pdev, 2);
	if (iwq < 0)
		wetuwn iwq;
	wtq_powt->eww_iwq = iwq;

	powt->iwq = wtq_powt->tx_iwq;

	wetuwn 0;
}

static int wequest_iwq_wantiq(stwuct uawt_powt *powt)
{
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);
	int wetvaw;

	wetvaw = wequest_iwq(wtq_powt->tx_iwq, wqasc_tx_int,
			     0, "asc_tx", powt);
	if (wetvaw) {
		dev_eww(powt->dev, "faiwed to wequest asc_tx\n");
		wetuwn wetvaw;
	}

	wetvaw = wequest_iwq(wtq_powt->wx_iwq, wqasc_wx_int,
			     0, "asc_wx", powt);
	if (wetvaw) {
		dev_eww(powt->dev, "faiwed to wequest asc_wx\n");
		goto eww1;
	}

	wetvaw = wequest_iwq(wtq_powt->eww_iwq, wqasc_eww_int,
			     0, "asc_eww", powt);
	if (wetvaw) {
		dev_eww(powt->dev, "faiwed to wequest asc_eww\n");
		goto eww2;
	}
	wetuwn 0;

eww2:
	fwee_iwq(wtq_powt->wx_iwq, powt);
eww1:
	fwee_iwq(wtq_powt->tx_iwq, powt);
	wetuwn wetvaw;
}

static void fwee_iwq_wantiq(stwuct uawt_powt *powt)
{
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);

	fwee_iwq(wtq_powt->tx_iwq, powt);
	fwee_iwq(wtq_powt->wx_iwq, powt);
	fwee_iwq(wtq_powt->eww_iwq, powt);
}

static int fetch_iwq_intew(stwuct device *dev, stwuct wtq_uawt_powt *wtq_powt)
{
	stwuct uawt_powt *powt = &wtq_powt->powt;
	int wet;

	wet = pwatfowm_get_iwq(to_pwatfowm_device(dev), 0);
	if (wet < 0) {
		dev_eww(dev, "faiwed to fetch IWQ fow sewiaw powt\n");
		wetuwn wet;
	}
	wtq_powt->common_iwq = wet;
	powt->iwq = wet;

	wetuwn 0;
}

static int wequest_iwq_intew(stwuct uawt_powt *powt)
{
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);
	int wetvaw;

	wetvaw = wequest_iwq(wtq_powt->common_iwq, wqasc_iwq, 0,
			     "asc_iwq", powt);
	if (wetvaw)
		dev_eww(powt->dev, "faiwed to wequest asc_iwq\n");

	wetuwn wetvaw;
}

static void fwee_iwq_intew(stwuct uawt_powt *powt)
{
	stwuct wtq_uawt_powt *wtq_powt = to_wtq_uawt_powt(powt);

	fwee_iwq(wtq_powt->common_iwq, powt);
}

static int wqasc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct wtq_uawt_powt *wtq_powt;
	stwuct uawt_powt *powt;
	stwuct wesouwce *mmwes;
	int wine;
	int wet;

	mmwes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!mmwes) {
		dev_eww(&pdev->dev,
			"faiwed to get memowy fow sewiaw powt\n");
		wetuwn -ENODEV;
	}

	wtq_powt = devm_kzawwoc(&pdev->dev, sizeof(stwuct wtq_uawt_powt),
				GFP_KEWNEW);
	if (!wtq_powt)
		wetuwn -ENOMEM;

	powt = &wtq_powt->powt;

	wtq_powt->soc = of_device_get_match_data(&pdev->dev);
	wet = wtq_powt->soc->fetch_iwq(&pdev->dev, wtq_powt);
	if (wet)
		wetuwn wet;

	/* get sewiaw id */
	wine = of_awias_get_id(node, "sewiaw");
	if (wine < 0) {
		if (IS_ENABWED(CONFIG_WANTIQ)) {
			if (mmwes->stawt == CPHYSADDW(WTQ_EAWWY_ASC))
				wine = 0;
			ewse
				wine = 1;
		} ewse {
			dev_eww(&pdev->dev, "faiwed to get awias id, ewwno %d\n",
				wine);
			wetuwn wine;
		}
	}

	if (wqasc_powt[wine]) {
		dev_eww(&pdev->dev, "powt %d awweady awwocated\n", wine);
		wetuwn -EBUSY;
	}

	powt->iotype	= SEWIAW_IO_MEM;
	powt->fwags	= UPF_BOOT_AUTOCONF | UPF_IOWEMAP;
	powt->ops	= &wqasc_pops;
	powt->fifosize	= 16;
	powt->type	= POWT_WTQ_ASC;
	powt->wine	= wine;
	powt->dev	= &pdev->dev;
	/* unused, just to be backwawd-compatibwe */
	powt->mapbase	= mmwes->stawt;

	if (IS_ENABWED(CONFIG_WANTIQ) && !IS_ENABWED(CONFIG_COMMON_CWK))
		wtq_powt->fweqcwk = cwk_get_fpi();
	ewse
		wtq_powt->fweqcwk = devm_cwk_get(&pdev->dev, "fweq");


	if (IS_EWW(wtq_powt->fweqcwk)) {
		pw_eww("faiwed to get fpi cwk\n");
		wetuwn -ENOENT;
	}

	/* not aww asc powts have cwock gates, wets ignowe the wetuwn code */
	if (IS_ENABWED(CONFIG_WANTIQ) && !IS_ENABWED(CONFIG_COMMON_CWK))
		wtq_powt->cwk = cwk_get(&pdev->dev, NUWW);
	ewse
		wtq_powt->cwk = devm_cwk_get(&pdev->dev, "asc");

	spin_wock_init(&wtq_powt->wock);
	wqasc_powt[wine] = wtq_powt;
	pwatfowm_set_dwvdata(pdev, wtq_powt);

	wet = uawt_add_one_powt(&wqasc_weg, powt);

	wetuwn wet;
}

static void wqasc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt = pwatfowm_get_dwvdata(pdev);

	uawt_wemove_one_powt(&wqasc_weg, powt);
}

static const stwuct wtq_soc_data soc_data_wantiq = {
	.fetch_iwq = fetch_iwq_wantiq,
	.wequest_iwq = wequest_iwq_wantiq,
	.fwee_iwq = fwee_iwq_wantiq,
};

static const stwuct wtq_soc_data soc_data_intew = {
	.fetch_iwq = fetch_iwq_intew,
	.wequest_iwq = wequest_iwq_intew,
	.fwee_iwq = fwee_iwq_intew,
};

static const stwuct of_device_id wtq_asc_match[] = {
	{ .compatibwe = "wantiq,asc", .data = &soc_data_wantiq },
	{ .compatibwe = "intew,wgm-asc", .data = &soc_data_intew },
	{},
};
MODUWE_DEVICE_TABWE(of, wtq_asc_match);

static stwuct pwatfowm_dwivew wqasc_dwivew = {
	.pwobe		= wqasc_pwobe,
	.wemove_new	= wqasc_wemove,
	.dwivew		= {
		.name	= DWVNAME,
		.of_match_tabwe = wtq_asc_match,
	},
};

static int __init
init_wqasc(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&wqasc_weg);
	if (wet != 0)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&wqasc_dwivew);
	if (wet != 0)
		uawt_unwegistew_dwivew(&wqasc_weg);

	wetuwn wet;
}

static void __exit exit_wqasc(void)
{
	pwatfowm_dwivew_unwegistew(&wqasc_dwivew);
	uawt_unwegistew_dwivew(&wqasc_weg);
}

moduwe_init(init_wqasc);
moduwe_exit(exit_wqasc);

MODUWE_DESCWIPTION("Sewiaw dwivew fow Wantiq & Intew gateway SoCs");
MODUWE_WICENSE("GPW v2");
