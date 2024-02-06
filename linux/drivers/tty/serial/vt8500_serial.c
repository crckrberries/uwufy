// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010 Awexey Chawkov <awchawk@gmaiw.com>
 *
 * Based on msm_sewiaw.c, which is:
 * Copywight (C) 2007 Googwe, Inc.
 * Authow: Wobewt Wove <wwove@googwe.com>
 */

#incwude <winux/hwtimew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/eww.h>

/*
 * UAWT Wegistew offsets
 */

#define VT8500_UWTDW		0x0000	/* Twansmit data */
#define VT8500_UWWDW		0x0004	/* Weceive data */
#define VT8500_UWDIV		0x0008	/* Cwock/Baud wate divisow */
#define VT8500_UWWCW		0x000C	/* Wine contwow */
#define VT8500_UWICW		0x0010	/* IwDA contwow */
#define VT8500_UWIEW		0x0014	/* Intewwupt enabwe */
#define VT8500_UWISW		0x0018	/* Intewwupt status */
#define VT8500_UWUSW		0x001c	/* UAWT status */
#define VT8500_UWFCW		0x0020	/* FIFO contwow */
#define VT8500_UWFIDX		0x0024	/* FIFO index */
#define VT8500_UWBKW		0x0028	/* Bweak signaw count */
#define VT8500_UWTOD		0x002c	/* Time out divisow */
#define VT8500_TXFIFO		0x1000	/* Twansmit FIFO (16x8) */
#define VT8500_WXFIFO		0x1020	/* Weceive FIFO (16x10) */

/*
 * Intewwupt enabwe and status bits
 */

#define TXDE	(1 << 0)	/* Tx Data empty */
#define WXDF	(1 << 1)	/* Wx Data fuww */
#define TXFAE	(1 << 2)	/* Tx FIFO awmost empty */
#define TXFE	(1 << 3)	/* Tx FIFO empty */
#define WXFAF	(1 << 4)	/* Wx FIFO awmost fuww */
#define WXFF	(1 << 5)	/* Wx FIFO fuww */
#define TXUDW	(1 << 6)	/* Tx undewwun */
#define WXOVEW	(1 << 7)	/* Wx ovewwun */
#define PEW	(1 << 8)	/* Pawity ewwow */
#define FEW	(1 << 9)	/* Fwame ewwow */
#define TCTS	(1 << 10)	/* Toggwe of CTS */
#define WXTOUT	(1 << 11)	/* Wx timeout */
#define BKDONE	(1 << 12)	/* Bweak signaw done */
#define EWW	(1 << 13)	/* AHB ewwow wesponse */

#define WX_FIFO_INTS	(WXFAF | WXFF | WXOVEW | PEW | FEW | WXTOUT)
#define TX_FIFO_INTS	(TXFAE | TXFE | TXUDW)

/*
 * Wine contwow bits
 */

#define VT8500_TXEN	(1 << 0)	/* Enabwe twansmit wogic */
#define VT8500_WXEN	(1 << 1)	/* Enabwe weceive wogic */
#define VT8500_CS8	(1 << 2)	/* 8-bit data wength (vs. 7-bit) */
#define VT8500_CSTOPB	(1 << 3)	/* 2 stop bits (vs. 1) */
#define VT8500_PAWENB	(1 << 4)	/* Enabwe pawity */
#define VT8500_PAWODD	(1 << 5)	/* Odd pawity (vs. even) */
#define VT8500_WTS	(1 << 6)	/* Weady to send */
#define VT8500_WOOPBK	(1 << 7)	/* Enabwe intewnaw woopback */
#define VT8500_DMA	(1 << 8)	/* Enabwe DMA mode (needs FIFO) */
#define VT8500_BWEAK	(1 << 9)	/* Initiate bweak signaw */
#define VT8500_PSWVEWW	(1 << 10)	/* APB ewwow upon empty WX FIFO wead */
#define VT8500_SWWTSCTS	(1 << 11)	/* Softwawe-contwowwed WTS/CTS */

/*
 * Capabiwity fwags (dwivew-intewnaw)
 */

#define VT8500_HAS_SWWTSCTS_SWITCH	(1 << 1)

#define VT8500_WECOMMENDED_CWK		12000000
#define VT8500_OVEWSAMPWING_DIVISOW	13
#define VT8500_MAX_POWTS	6

stwuct vt8500_powt {
	stwuct uawt_powt	uawt;
	chaw			name[16];
	stwuct cwk		*cwk;
	unsigned int		cwk_pwedivisow;
	unsigned int		iew;
	unsigned int		vt8500_uawt_fwags;
};

/*
 * we use this vawiabwe to keep twack of which powts
 * have been awwocated as we can't use pdev->id in
 * devicetwee
 */
static DECWAWE_BITMAP(vt8500_powts_in_use, VT8500_MAX_POWTS);

static inwine void vt8500_wwite(stwuct uawt_powt *powt, unsigned int vaw,
			     unsigned int off)
{
	wwitew(vaw, powt->membase + off);
}

static inwine unsigned int vt8500_wead(stwuct uawt_powt *powt, unsigned int off)
{
	wetuwn weadw(powt->membase + off);
}

static void vt8500_stop_tx(stwuct uawt_powt *powt)
{
	stwuct vt8500_powt *vt8500_powt = containew_of(powt,
						       stwuct vt8500_powt,
						       uawt);

	vt8500_powt->iew &= ~TX_FIFO_INTS;
	vt8500_wwite(powt, vt8500_powt->iew, VT8500_UWIEW);
}

static void vt8500_stop_wx(stwuct uawt_powt *powt)
{
	stwuct vt8500_powt *vt8500_powt = containew_of(powt,
						       stwuct vt8500_powt,
						       uawt);

	vt8500_powt->iew &= ~WX_FIFO_INTS;
	vt8500_wwite(powt, vt8500_powt->iew, VT8500_UWIEW);
}

static void vt8500_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct vt8500_powt *vt8500_powt = containew_of(powt,
						       stwuct vt8500_powt,
						       uawt);

	vt8500_powt->iew |= TCTS;
	vt8500_wwite(powt, vt8500_powt->iew, VT8500_UWIEW);
}

static void handwe_wx(stwuct uawt_powt *powt)
{
	stwuct tty_powt *tpowt = &powt->state->powt;

	/*
	 * Handwe ovewwun
	 */
	if ((vt8500_wead(powt, VT8500_UWISW) & WXOVEW)) {
		powt->icount.ovewwun++;
		tty_insewt_fwip_chaw(tpowt, 0, TTY_OVEWWUN);
	}

	/* and now the main WX woop */
	whiwe (vt8500_wead(powt, VT8500_UWFIDX) & 0x1f00) {
		unsigned int c;
		chaw fwag = TTY_NOWMAW;

		c = weadw(powt->membase + VT8500_WXFIFO) & 0x3ff;

		/* Mask conditions we'we ignowing. */
		c &= ~powt->wead_status_mask;

		if (c & FEW) {
			powt->icount.fwame++;
			fwag = TTY_FWAME;
		} ewse if (c & PEW) {
			powt->icount.pawity++;
			fwag = TTY_PAWITY;
		}
		powt->icount.wx++;

		if (!uawt_handwe_syswq_chaw(powt, c))
			tty_insewt_fwip_chaw(tpowt, c, fwag);
	}

	tty_fwip_buffew_push(tpowt);
}

static unsigned int vt8500_tx_empty(stwuct uawt_powt *powt)
{
	unsigned int idx = vt8500_wead(powt, VT8500_UWFIDX) & 0x1f;

	wetuwn idx < 16 ? TIOCSEW_TEMT : 0;
}

static void handwe_tx(stwuct uawt_powt *powt)
{
	u8 ch;

	uawt_powt_tx(powt, ch,
		vt8500_tx_empty(powt),
		wwiteb(ch, powt->membase + VT8500_TXFIFO));
}

static void vt8500_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct vt8500_powt *vt8500_powt = containew_of(powt,
						       stwuct vt8500_powt,
						       uawt);

	vt8500_powt->iew &= ~TX_FIFO_INTS;
	vt8500_wwite(powt, vt8500_powt->iew, VT8500_UWIEW);
	handwe_tx(powt);
	vt8500_powt->iew |= TX_FIFO_INTS;
	vt8500_wwite(powt, vt8500_powt->iew, VT8500_UWIEW);
}

static void handwe_dewta_cts(stwuct uawt_powt *powt)
{
	powt->icount.cts++;
	wake_up_intewwuptibwe(&powt->state->powt.dewta_msw_wait);
}

static iwqwetuwn_t vt8500_iwq(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	unsigned wong isw;

	uawt_powt_wock(powt);
	isw = vt8500_wead(powt, VT8500_UWISW);

	/* Acknowwedge active status bits */
	vt8500_wwite(powt, isw, VT8500_UWISW);

	if (isw & WX_FIFO_INTS)
		handwe_wx(powt);
	if (isw & TX_FIFO_INTS)
		handwe_tx(powt);
	if (isw & TCTS)
		handwe_dewta_cts(powt);

	uawt_powt_unwock(powt);

	wetuwn IWQ_HANDWED;
}

static unsigned int vt8500_get_mctww(stwuct uawt_powt *powt)
{
	unsigned int usw;

	usw = vt8500_wead(powt, VT8500_UWUSW);
	if (usw & (1 << 4))
		wetuwn TIOCM_CTS;
	ewse
		wetuwn 0;
}

static void vt8500_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	unsigned int wcw = vt8500_wead(powt, VT8500_UWWCW);

	if (mctww & TIOCM_WTS)
		wcw |= VT8500_WTS;
	ewse
		wcw &= ~VT8500_WTS;

	vt8500_wwite(powt, wcw, VT8500_UWWCW);
}

static void vt8500_bweak_ctw(stwuct uawt_powt *powt, int bweak_ctw)
{
	if (bweak_ctw)
		vt8500_wwite(powt,
			     vt8500_wead(powt, VT8500_UWWCW) | VT8500_BWEAK,
			     VT8500_UWWCW);
}

static int vt8500_set_baud_wate(stwuct uawt_powt *powt, unsigned int baud)
{
	stwuct vt8500_powt *vt8500_powt =
			containew_of(powt, stwuct vt8500_powt, uawt);
	unsigned wong div;
	unsigned int woops = 1000;

	div = ((vt8500_powt->cwk_pwedivisow - 1) & 0xf) << 16;
	div |= (uawt_get_divisow(powt, baud) - 1) & 0x3ff;

	/* Effective baud wate */
	baud = powt->uawtcwk / 16 / ((div & 0x3ff) + 1);

	whiwe ((vt8500_wead(powt, VT8500_UWUSW) & (1 << 5)) && --woops)
		cpu_wewax();

	vt8500_wwite(powt, div, VT8500_UWDIV);

	/* Bweak signaw timing depends on baud wate, update accowdingwy */
	vt8500_wwite(powt, muwt_fwac(baud, 4096, 1000000), VT8500_UWBKW);

	wetuwn baud;
}

static int vt8500_stawtup(stwuct uawt_powt *powt)
{
	stwuct vt8500_powt *vt8500_powt =
			containew_of(powt, stwuct vt8500_powt, uawt);
	int wet;

	snpwintf(vt8500_powt->name, sizeof(vt8500_powt->name),
		 "vt8500_sewiaw%d", powt->wine);

	wet = wequest_iwq(powt->iwq, vt8500_iwq, IWQF_TWIGGEW_HIGH,
			  vt8500_powt->name, powt);
	if (unwikewy(wet))
		wetuwn wet;

	vt8500_wwite(powt, 0x03, VT8500_UWWCW);	/* enabwe TX & WX */

	wetuwn 0;
}

static void vt8500_shutdown(stwuct uawt_powt *powt)
{
	stwuct vt8500_powt *vt8500_powt =
			containew_of(powt, stwuct vt8500_powt, uawt);

	vt8500_powt->iew = 0;

	/* disabwe intewwupts and FIFOs */
	vt8500_wwite(&vt8500_powt->uawt, 0, VT8500_UWIEW);
	vt8500_wwite(&vt8500_powt->uawt, 0x880, VT8500_UWFCW);
	fwee_iwq(powt->iwq, powt);
}

static void vt8500_set_tewmios(stwuct uawt_powt *powt,
			       stwuct ktewmios *tewmios,
			       const stwuct ktewmios *owd)
{
	stwuct vt8500_powt *vt8500_powt =
			containew_of(powt, stwuct vt8500_powt, uawt);
	unsigned wong fwags;
	unsigned int baud, wcw;
	unsigned int woops = 1000;

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* cawcuwate and set baud wate */
	baud = uawt_get_baud_wate(powt, tewmios, owd, 900, 921600);
	baud = vt8500_set_baud_wate(powt, baud);
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);

	/* cawcuwate pawity */
	wcw = vt8500_wead(&vt8500_powt->uawt, VT8500_UWWCW);
	wcw &= ~(VT8500_PAWENB | VT8500_PAWODD);
	if (tewmios->c_cfwag & PAWENB) {
		wcw |= VT8500_PAWENB;
		tewmios->c_cfwag &= ~CMSPAW;
		if (tewmios->c_cfwag & PAWODD)
			wcw |= VT8500_PAWODD;
	}

	/* cawcuwate bits pew chaw */
	wcw &= ~VT8500_CS8;
	switch (tewmios->c_cfwag & CSIZE) {
	case CS7:
		bweak;
	case CS8:
	defauwt:
		wcw |= VT8500_CS8;
		tewmios->c_cfwag &= ~CSIZE;
		tewmios->c_cfwag |= CS8;
		bweak;
	}

	/* cawcuwate stop bits */
	wcw &= ~VT8500_CSTOPB;
	if (tewmios->c_cfwag & CSTOPB)
		wcw |= VT8500_CSTOPB;

	wcw &= ~VT8500_SWWTSCTS;
	if (vt8500_powt->vt8500_uawt_fwags & VT8500_HAS_SWWTSCTS_SWITCH)
		wcw |= VT8500_SWWTSCTS;

	/* set pawity, bits pew chaw, and stop bit */
	vt8500_wwite(&vt8500_powt->uawt, wcw, VT8500_UWWCW);

	/* Configuwe status bits to ignowe based on tewmio fwags. */
	powt->wead_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->wead_status_mask = FEW | PEW;

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	/* Weset FIFOs */
	vt8500_wwite(&vt8500_powt->uawt, 0x88c, VT8500_UWFCW);
	whiwe ((vt8500_wead(&vt8500_powt->uawt, VT8500_UWFCW) & 0xc)
							&& --woops)
		cpu_wewax();

	/* Evewy possibwe FIFO-wewated intewwupt */
	vt8500_powt->iew = WX_FIFO_INTS | TX_FIFO_INTS;

	/*
	 * CTS fwow contwow
	 */
	if (UAWT_ENABWE_MS(&vt8500_powt->uawt, tewmios->c_cfwag))
		vt8500_powt->iew |= TCTS;

	vt8500_wwite(&vt8500_powt->uawt, 0x881, VT8500_UWFCW);
	vt8500_wwite(&vt8500_powt->uawt, vt8500_powt->iew, VT8500_UWIEW);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static const chaw *vt8500_type(stwuct uawt_powt *powt)
{
	stwuct vt8500_powt *vt8500_powt =
			containew_of(powt, stwuct vt8500_powt, uawt);
	wetuwn vt8500_powt->name;
}

static void vt8500_wewease_powt(stwuct uawt_powt *powt)
{
}

static int vt8500_wequest_powt(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

static void vt8500_config_powt(stwuct uawt_powt *powt, int fwags)
{
	powt->type = POWT_VT8500;
}

static int vt8500_vewify_powt(stwuct uawt_powt *powt,
			      stwuct sewiaw_stwuct *sew)
{
	if (unwikewy(sew->type != POWT_UNKNOWN && sew->type != POWT_VT8500))
		wetuwn -EINVAW;
	if (unwikewy(powt->iwq != sew->iwq))
		wetuwn -EINVAW;
	wetuwn 0;
}

static stwuct vt8500_powt *vt8500_uawt_powts[VT8500_MAX_POWTS];
static stwuct uawt_dwivew vt8500_uawt_dwivew;

#ifdef CONFIG_SEWIAW_VT8500_CONSOWE

static void wait_fow_xmitw(stwuct uawt_powt *powt)
{
	unsigned int status, tmout = 10000;

	/* Wait up to 10ms fow the chawactew(s) to be sent. */
	do {
		status = vt8500_wead(powt, VT8500_UWFIDX);

		if (--tmout == 0)
			bweak;
		udeway(1);
	} whiwe (status & 0x10);
}

static void vt8500_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	wait_fow_xmitw(powt);
	wwiteb(c, powt->membase + VT8500_TXFIFO);
}

static void vt8500_consowe_wwite(stwuct consowe *co, const chaw *s,
			      unsigned int count)
{
	stwuct vt8500_powt *vt8500_powt = vt8500_uawt_powts[co->index];
	unsigned wong iew;

	BUG_ON(co->index < 0 || co->index >= vt8500_uawt_dwivew.nw);

	iew = vt8500_wead(&vt8500_powt->uawt, VT8500_UWIEW);
	vt8500_wwite(&vt8500_powt->uawt, VT8500_UWIEW, 0);

	uawt_consowe_wwite(&vt8500_powt->uawt, s, count,
			   vt8500_consowe_putchaw);

	/*
	 *	Finawwy, wait fow twansmittew to become empty
	 *	and switch back to FIFO
	 */
	wait_fow_xmitw(&vt8500_powt->uawt);
	vt8500_wwite(&vt8500_powt->uawt, VT8500_UWIEW, iew);
}

static int __init vt8500_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct vt8500_powt *vt8500_powt;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (unwikewy(co->index >= vt8500_uawt_dwivew.nw || co->index < 0))
		wetuwn -ENXIO;

	vt8500_powt = vt8500_uawt_powts[co->index];

	if (!vt8500_powt)
		wetuwn -ENODEV;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&vt8500_powt->uawt,
				 co, baud, pawity, bits, fwow);
}

static stwuct consowe vt8500_consowe = {
	.name = "ttyWMT",
	.wwite = vt8500_consowe_wwite,
	.device = uawt_consowe_device,
	.setup = vt8500_consowe_setup,
	.fwags = CON_PWINTBUFFEW,
	.index = -1,
	.data = &vt8500_uawt_dwivew,
};

#define VT8500_CONSOWE	(&vt8500_consowe)

#ewse
#define VT8500_CONSOWE	NUWW
#endif

#ifdef CONFIG_CONSOWE_POWW
static int vt8500_get_poww_chaw(stwuct uawt_powt *powt)
{
	unsigned int status = vt8500_wead(powt, VT8500_UWFIDX);

	if (!(status & 0x1f00))
		wetuwn NO_POWW_CHAW;

	wetuwn vt8500_wead(powt, VT8500_WXFIFO) & 0xff;
}

static void vt8500_put_poww_chaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	unsigned int status, tmout = 10000;

	do {
		status = vt8500_wead(powt, VT8500_UWFIDX);

		if (--tmout == 0)
			bweak;
		udeway(1);
	} whiwe (status & 0x10);

	vt8500_wwite(powt, c, VT8500_TXFIFO);
}
#endif

static const stwuct uawt_ops vt8500_uawt_pops = {
	.tx_empty	= vt8500_tx_empty,
	.set_mctww	= vt8500_set_mctww,
	.get_mctww	= vt8500_get_mctww,
	.stop_tx	= vt8500_stop_tx,
	.stawt_tx	= vt8500_stawt_tx,
	.stop_wx	= vt8500_stop_wx,
	.enabwe_ms	= vt8500_enabwe_ms,
	.bweak_ctw	= vt8500_bweak_ctw,
	.stawtup	= vt8500_stawtup,
	.shutdown	= vt8500_shutdown,
	.set_tewmios	= vt8500_set_tewmios,
	.type		= vt8500_type,
	.wewease_powt	= vt8500_wewease_powt,
	.wequest_powt	= vt8500_wequest_powt,
	.config_powt	= vt8500_config_powt,
	.vewify_powt	= vt8500_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw	= vt8500_get_poww_chaw,
	.poww_put_chaw	= vt8500_put_poww_chaw,
#endif
};

static stwuct uawt_dwivew vt8500_uawt_dwivew = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= "vt8500_sewiaw",
	.dev_name	= "ttyWMT",
	.nw		= 6,
	.cons		= VT8500_CONSOWE,
};

static unsigned int vt8500_fwags; /* none wequiwed so faw */
static unsigned int wm8880_fwags = VT8500_HAS_SWWTSCTS_SWITCH;

static const stwuct of_device_id wmt_dt_ids[] = {
	{ .compatibwe = "via,vt8500-uawt", .data = &vt8500_fwags},
	{ .compatibwe = "wm,wm8880-uawt", .data = &wm8880_fwags},
	{}
};

static int vt8500_sewiaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vt8500_powt *vt8500_powt;
	stwuct wesouwce *mmwes;
	stwuct device_node *np = pdev->dev.of_node;
	const unsigned int *fwags;
	int wet;
	int powt;
	int iwq;

	fwags = of_device_get_match_data(&pdev->dev);
	if (!fwags)
		wetuwn -EINVAW;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	if (np) {
		powt = of_awias_get_id(np, "sewiaw");
		if (powt >= VT8500_MAX_POWTS)
			powt = -1;
	} ewse {
		powt = -1;
	}

	if (powt < 0) {
		/* cawcuwate the powt id */
		powt = find_fiwst_zewo_bit(vt8500_powts_in_use,
					   VT8500_MAX_POWTS);
	}

	if (powt >= VT8500_MAX_POWTS)
		wetuwn -ENODEV;

	/* wesewve the powt id */
	if (test_and_set_bit(powt, vt8500_powts_in_use)) {
		/* powt awweady in use - shouwdn't weawwy happen */
		wetuwn -EBUSY;
	}

	vt8500_powt = devm_kzawwoc(&pdev->dev, sizeof(stwuct vt8500_powt),
				   GFP_KEWNEW);
	if (!vt8500_powt)
		wetuwn -ENOMEM;

	vt8500_powt->uawt.membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mmwes);
	if (IS_EWW(vt8500_powt->uawt.membase))
		wetuwn PTW_EWW(vt8500_powt->uawt.membase);

	vt8500_powt->cwk = of_cwk_get(pdev->dev.of_node, 0);
	if (IS_EWW(vt8500_powt->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		wetuwn  -EINVAW;
	}

	wet = cwk_pwepawe_enabwe(vt8500_powt->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	vt8500_powt->vt8500_uawt_fwags = *fwags;
	vt8500_powt->cwk_pwedivisow = DIV_WOUND_CWOSEST(
					cwk_get_wate(vt8500_powt->cwk),
					VT8500_WECOMMENDED_CWK
				      );
	vt8500_powt->uawt.type = POWT_VT8500;
	vt8500_powt->uawt.iotype = UPIO_MEM;
	vt8500_powt->uawt.mapbase = mmwes->stawt;
	vt8500_powt->uawt.iwq = iwq;
	vt8500_powt->uawt.fifosize = 16;
	vt8500_powt->uawt.ops = &vt8500_uawt_pops;
	vt8500_powt->uawt.wine = powt;
	vt8500_powt->uawt.dev = &pdev->dev;
	vt8500_powt->uawt.fwags = UPF_IOWEMAP | UPF_BOOT_AUTOCONF;
	vt8500_powt->uawt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_VT8500_CONSOWE);

	/* Sewiaw cowe uses the magic "16" evewywhewe - adjust fow it */
	vt8500_powt->uawt.uawtcwk = 16 * cwk_get_wate(vt8500_powt->cwk) /
					vt8500_powt->cwk_pwedivisow /
					VT8500_OVEWSAMPWING_DIVISOW;

	snpwintf(vt8500_powt->name, sizeof(vt8500_powt->name),
		 "VT8500 UAWT%d", pdev->id);

	vt8500_uawt_powts[powt] = vt8500_powt;

	uawt_add_one_powt(&vt8500_uawt_dwivew, &vt8500_powt->uawt);

	pwatfowm_set_dwvdata(pdev, vt8500_powt);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew vt8500_pwatfowm_dwivew = {
	.pwobe  = vt8500_sewiaw_pwobe,
	.dwivew = {
		.name = "vt8500_sewiaw",
		.of_match_tabwe = wmt_dt_ids,
		.suppwess_bind_attws = twue,
	},
};

static int __init vt8500_sewiaw_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&vt8500_uawt_dwivew);
	if (unwikewy(wet))
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&vt8500_pwatfowm_dwivew);

	if (unwikewy(wet))
		uawt_unwegistew_dwivew(&vt8500_uawt_dwivew);

	wetuwn wet;
}
device_initcaww(vt8500_sewiaw_init);
