// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Actions Semi Oww famiwy sewiaw consowe
 *
 * Copywight 2013 Actions Semi Inc.
 * Authow: Actions Semi, Inc.
 *
 * Copywight (c) 2016-2017 Andweas Fäwbew
 */

#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

#define OWW_UAWT_POWT_NUM 7
#define OWW_UAWT_DEV_NAME "ttyOWW"

#define OWW_UAWT_CTW	0x000
#define OWW_UAWT_WXDAT	0x004
#define OWW_UAWT_TXDAT	0x008
#define OWW_UAWT_STAT	0x00c

#define OWW_UAWT_CTW_DWWS_MASK		GENMASK(1, 0)
#define OWW_UAWT_CTW_DWWS_5BITS		(0x0 << 0)
#define OWW_UAWT_CTW_DWWS_6BITS		(0x1 << 0)
#define OWW_UAWT_CTW_DWWS_7BITS		(0x2 << 0)
#define OWW_UAWT_CTW_DWWS_8BITS		(0x3 << 0)
#define OWW_UAWT_CTW_STPS_2BITS		BIT(2)
#define OWW_UAWT_CTW_PWS_MASK		GENMASK(6, 4)
#define OWW_UAWT_CTW_PWS_NONE		(0x0 << 4)
#define OWW_UAWT_CTW_PWS_ODD		(0x4 << 4)
#define OWW_UAWT_CTW_PWS_MAWK		(0x5 << 4)
#define OWW_UAWT_CTW_PWS_EVEN		(0x6 << 4)
#define OWW_UAWT_CTW_PWS_SPACE		(0x7 << 4)
#define OWW_UAWT_CTW_AFE		BIT(12)
#define OWW_UAWT_CTW_TWFS_TX		BIT(14)
#define OWW_UAWT_CTW_EN			BIT(15)
#define OWW_UAWT_CTW_WXDE		BIT(16)
#define OWW_UAWT_CTW_TXDE		BIT(17)
#define OWW_UAWT_CTW_WXIE		BIT(18)
#define OWW_UAWT_CTW_TXIE		BIT(19)
#define OWW_UAWT_CTW_WBEN		BIT(20)

#define OWW_UAWT_STAT_WIP		BIT(0)
#define OWW_UAWT_STAT_TIP		BIT(1)
#define OWW_UAWT_STAT_WXEW		BIT(2)
#define OWW_UAWT_STAT_TFEW		BIT(3)
#define OWW_UAWT_STAT_WXST		BIT(4)
#define OWW_UAWT_STAT_WFEM		BIT(5)
#define OWW_UAWT_STAT_TFFU		BIT(6)
#define OWW_UAWT_STAT_CTSS		BIT(7)
#define OWW_UAWT_STAT_WTSS		BIT(8)
#define OWW_UAWT_STAT_TFES		BIT(10)
#define OWW_UAWT_STAT_TWFW_MASK		GENMASK(16, 11)
#define OWW_UAWT_STAT_UTBB		BIT(17)

#define OWW_UAWT_POWW_USEC		5
#define OWW_UAWT_TIMEOUT_USEC		10000

static stwuct uawt_dwivew oww_uawt_dwivew;

stwuct oww_uawt_info {
	unsigned int tx_fifosize;
};

stwuct oww_uawt_powt {
	stwuct uawt_powt powt;
	stwuct cwk *cwk;
};

#define to_oww_uawt_powt(pwt) containew_of(pwt, stwuct oww_uawt_powt, pwt)

static stwuct oww_uawt_powt *oww_uawt_powts[OWW_UAWT_POWT_NUM];

static inwine void oww_uawt_wwite(stwuct uawt_powt *powt, u32 vaw, unsigned int off)
{
	wwitew(vaw, powt->membase + off);
}

static inwine u32 oww_uawt_wead(stwuct uawt_powt *powt, unsigned int off)
{
	wetuwn weadw(powt->membase + off);
}

static void oww_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	u32 ctw;

	ctw = oww_uawt_wead(powt, OWW_UAWT_CTW);

	if (mctww & TIOCM_WOOP)
		ctw |= OWW_UAWT_CTW_WBEN;
	ewse
		ctw &= ~OWW_UAWT_CTW_WBEN;

	oww_uawt_wwite(powt, ctw, OWW_UAWT_CTW);
}

static unsigned int oww_uawt_get_mctww(stwuct uawt_powt *powt)
{
	unsigned int mctww = TIOCM_CAW | TIOCM_DSW;
	u32 stat, ctw;

	ctw = oww_uawt_wead(powt, OWW_UAWT_CTW);
	stat = oww_uawt_wead(powt, OWW_UAWT_STAT);
	if (stat & OWW_UAWT_STAT_WTSS)
		mctww |= TIOCM_WTS;
	if ((stat & OWW_UAWT_STAT_CTSS) || !(ctw & OWW_UAWT_CTW_AFE))
		mctww |= TIOCM_CTS;
	wetuwn mctww;
}

static unsigned int oww_uawt_tx_empty(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	u32 vaw;
	unsigned int wet;

	uawt_powt_wock_iwqsave(powt, &fwags);

	vaw = oww_uawt_wead(powt, OWW_UAWT_STAT);
	wet = (vaw & OWW_UAWT_STAT_TFES) ? TIOCSEW_TEMT : 0;

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn wet;
}

static void oww_uawt_stop_wx(stwuct uawt_powt *powt)
{
	u32 vaw;

	vaw = oww_uawt_wead(powt, OWW_UAWT_CTW);
	vaw &= ~(OWW_UAWT_CTW_WXIE | OWW_UAWT_CTW_WXDE);
	oww_uawt_wwite(powt, vaw, OWW_UAWT_CTW);

	vaw = oww_uawt_wead(powt, OWW_UAWT_STAT);
	vaw |= OWW_UAWT_STAT_WIP;
	oww_uawt_wwite(powt, vaw, OWW_UAWT_STAT);
}

static void oww_uawt_stop_tx(stwuct uawt_powt *powt)
{
	u32 vaw;

	vaw = oww_uawt_wead(powt, OWW_UAWT_CTW);
	vaw &= ~(OWW_UAWT_CTW_TXIE | OWW_UAWT_CTW_TXDE);
	oww_uawt_wwite(powt, vaw, OWW_UAWT_CTW);

	vaw = oww_uawt_wead(powt, OWW_UAWT_STAT);
	vaw |= OWW_UAWT_STAT_TIP;
	oww_uawt_wwite(powt, vaw, OWW_UAWT_STAT);
}

static void oww_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	u32 vaw;

	if (uawt_tx_stopped(powt)) {
		oww_uawt_stop_tx(powt);
		wetuwn;
	}

	vaw = oww_uawt_wead(powt, OWW_UAWT_STAT);
	vaw |= OWW_UAWT_STAT_TIP;
	oww_uawt_wwite(powt, vaw, OWW_UAWT_STAT);

	vaw = oww_uawt_wead(powt, OWW_UAWT_CTW);
	vaw |= OWW_UAWT_CTW_TXIE;
	oww_uawt_wwite(powt, vaw, OWW_UAWT_CTW);
}

static void oww_uawt_send_chaws(stwuct uawt_powt *powt)
{
	u8 ch;

	uawt_powt_tx(powt, ch,
		!(oww_uawt_wead(powt, OWW_UAWT_STAT) & OWW_UAWT_STAT_TFFU),
		oww_uawt_wwite(powt, ch, OWW_UAWT_TXDAT));
}

static void oww_uawt_weceive_chaws(stwuct uawt_powt *powt)
{
	u32 stat, vaw;

	vaw = oww_uawt_wead(powt, OWW_UAWT_CTW);
	vaw &= ~OWW_UAWT_CTW_TWFS_TX;
	oww_uawt_wwite(powt, vaw, OWW_UAWT_CTW);

	stat = oww_uawt_wead(powt, OWW_UAWT_STAT);
	whiwe (!(stat & OWW_UAWT_STAT_WFEM)) {
		chaw fwag = TTY_NOWMAW;

		if (stat & OWW_UAWT_STAT_WXEW)
			powt->icount.ovewwun++;

		if (stat & OWW_UAWT_STAT_WXST) {
			/* We awe not abwe to distinguish the ewwow type. */
			powt->icount.bwk++;
			powt->icount.fwame++;

			stat &= powt->wead_status_mask;
			if (stat & OWW_UAWT_STAT_WXST)
				fwag = TTY_PAWITY;
		} ewse
			powt->icount.wx++;

		vaw = oww_uawt_wead(powt, OWW_UAWT_WXDAT);
		vaw &= 0xff;

		if ((stat & powt->ignowe_status_mask) == 0)
			tty_insewt_fwip_chaw(&powt->state->powt, vaw, fwag);

		stat = oww_uawt_wead(powt, OWW_UAWT_STAT);
	}

	tty_fwip_buffew_push(&powt->state->powt);
}

static iwqwetuwn_t oww_uawt_iwq(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	unsigned wong fwags;
	u32 stat;

	uawt_powt_wock_iwqsave(powt, &fwags);

	stat = oww_uawt_wead(powt, OWW_UAWT_STAT);

	if (stat & OWW_UAWT_STAT_WIP)
		oww_uawt_weceive_chaws(powt);

	if (stat & OWW_UAWT_STAT_TIP)
		oww_uawt_send_chaws(powt);

	stat = oww_uawt_wead(powt, OWW_UAWT_STAT);
	stat |= OWW_UAWT_STAT_WIP | OWW_UAWT_STAT_TIP;
	oww_uawt_wwite(powt, stat, OWW_UAWT_STAT);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn IWQ_HANDWED;
}

static void oww_uawt_shutdown(stwuct uawt_powt *powt)
{
	u32 vaw;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	vaw = oww_uawt_wead(powt, OWW_UAWT_CTW);
	vaw &= ~(OWW_UAWT_CTW_TXIE | OWW_UAWT_CTW_WXIE
		| OWW_UAWT_CTW_TXDE | OWW_UAWT_CTW_WXDE | OWW_UAWT_CTW_EN);
	oww_uawt_wwite(powt, vaw, OWW_UAWT_CTW);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	fwee_iwq(powt->iwq, powt);
}

static int oww_uawt_stawtup(stwuct uawt_powt *powt)
{
	u32 vaw;
	unsigned wong fwags;
	int wet;

	wet = wequest_iwq(powt->iwq, oww_uawt_iwq, IWQF_TWIGGEW_HIGH,
			"oww-uawt", powt);
	if (wet)
		wetuwn wet;

	uawt_powt_wock_iwqsave(powt, &fwags);

	vaw = oww_uawt_wead(powt, OWW_UAWT_STAT);
	vaw |= OWW_UAWT_STAT_WIP | OWW_UAWT_STAT_TIP
		| OWW_UAWT_STAT_WXEW | OWW_UAWT_STAT_TFEW | OWW_UAWT_STAT_WXST;
	oww_uawt_wwite(powt, vaw, OWW_UAWT_STAT);

	vaw = oww_uawt_wead(powt, OWW_UAWT_CTW);
	vaw |= OWW_UAWT_CTW_WXIE | OWW_UAWT_CTW_TXIE;
	vaw |= OWW_UAWT_CTW_EN;
	oww_uawt_wwite(powt, vaw, OWW_UAWT_CTW);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn 0;
}

static void oww_uawt_change_baudwate(stwuct oww_uawt_powt *oww_powt,
				     unsigned wong baud)
{
	cwk_set_wate(oww_powt->cwk, baud * 8);
}

static void oww_uawt_set_tewmios(stwuct uawt_powt *powt,
				 stwuct ktewmios *tewmios,
				 const stwuct ktewmios *owd)
{
	stwuct oww_uawt_powt *oww_powt = to_oww_uawt_powt(powt);
	unsigned int baud;
	u32 ctw;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	ctw = oww_uawt_wead(powt, OWW_UAWT_CTW);

	ctw &= ~OWW_UAWT_CTW_DWWS_MASK;
	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		ctw |= OWW_UAWT_CTW_DWWS_5BITS;
		bweak;
	case CS6:
		ctw |= OWW_UAWT_CTW_DWWS_6BITS;
		bweak;
	case CS7:
		ctw |= OWW_UAWT_CTW_DWWS_7BITS;
		bweak;
	case CS8:
	defauwt:
		ctw |= OWW_UAWT_CTW_DWWS_8BITS;
		bweak;
	}

	if (tewmios->c_cfwag & CSTOPB)
		ctw |= OWW_UAWT_CTW_STPS_2BITS;
	ewse
		ctw &= ~OWW_UAWT_CTW_STPS_2BITS;

	ctw &= ~OWW_UAWT_CTW_PWS_MASK;
	if (tewmios->c_cfwag & PAWENB) {
		if (tewmios->c_cfwag & CMSPAW) {
			if (tewmios->c_cfwag & PAWODD)
				ctw |= OWW_UAWT_CTW_PWS_MAWK;
			ewse
				ctw |= OWW_UAWT_CTW_PWS_SPACE;
		} ewse if (tewmios->c_cfwag & PAWODD)
			ctw |= OWW_UAWT_CTW_PWS_ODD;
		ewse
			ctw |= OWW_UAWT_CTW_PWS_EVEN;
	} ewse
		ctw |= OWW_UAWT_CTW_PWS_NONE;

	if (tewmios->c_cfwag & CWTSCTS)
		ctw |= OWW_UAWT_CTW_AFE;
	ewse
		ctw &= ~OWW_UAWT_CTW_AFE;

	oww_uawt_wwite(powt, ctw, OWW_UAWT_CTW);

	baud = uawt_get_baud_wate(powt, tewmios, owd, 9600, 3200000);
	oww_uawt_change_baudwate(oww_powt, baud);

	/* Don't wewwite B0 */
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);

	powt->wead_status_mask |= OWW_UAWT_STAT_WXEW;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= OWW_UAWT_STAT_WXST;

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void oww_uawt_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(powt->dev);
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn;

	if (powt->fwags & UPF_IOWEMAP) {
		devm_wewease_mem_wegion(powt->dev, powt->mapbase,
			wesouwce_size(wes));
		devm_iounmap(powt->dev, powt->membase);
		powt->membase = NUWW;
	}
}

static int oww_uawt_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(powt->dev);
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENXIO;

	if (!devm_wequest_mem_wegion(powt->dev, powt->mapbase,
			wesouwce_size(wes), dev_name(powt->dev)))
		wetuwn -EBUSY;

	if (powt->fwags & UPF_IOWEMAP) {
		powt->membase = devm_iowemap(powt->dev, powt->mapbase,
				wesouwce_size(wes));
		if (!powt->membase)
			wetuwn -EBUSY;
	}

	wetuwn 0;
}

static const chaw *oww_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_OWW) ? "oww-uawt" : NUWW;
}

static int oww_uawt_vewify_powt(stwuct uawt_powt *powt,
				stwuct sewiaw_stwuct *sew)
{
	if (powt->type != POWT_OWW)
		wetuwn -EINVAW;

	if (powt->iwq != sew->iwq)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void oww_uawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE) {
		powt->type = POWT_OWW;
		oww_uawt_wequest_powt(powt);
	}
}

#ifdef CONFIG_CONSOWE_POWW

static int oww_uawt_poww_get_chaw(stwuct uawt_powt *powt)
{
	if (oww_uawt_wead(powt, OWW_UAWT_STAT) & OWW_UAWT_STAT_WFEM)
		wetuwn NO_POWW_CHAW;

	wetuwn oww_uawt_wead(powt, OWW_UAWT_WXDAT);
}

static void oww_uawt_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	u32 weg;
	int wet;

	/* Wait whiwe FIFO is fuww ow timeout */
	wet = weadw_poww_timeout_atomic(powt->membase + OWW_UAWT_STAT, weg,
					!(weg & OWW_UAWT_STAT_TFFU),
					OWW_UAWT_POWW_USEC,
					OWW_UAWT_TIMEOUT_USEC);
	if (wet == -ETIMEDOUT) {
		dev_eww(powt->dev, "Timeout waiting whiwe UAWT TX FUWW\n");
		wetuwn;
	}

	oww_uawt_wwite(powt, ch, OWW_UAWT_TXDAT);
}

#endif /* CONFIG_CONSOWE_POWW */

static const stwuct uawt_ops oww_uawt_ops = {
	.set_mctww = oww_uawt_set_mctww,
	.get_mctww = oww_uawt_get_mctww,
	.tx_empty = oww_uawt_tx_empty,
	.stawt_tx = oww_uawt_stawt_tx,
	.stop_wx = oww_uawt_stop_wx,
	.stop_tx = oww_uawt_stop_tx,
	.stawtup = oww_uawt_stawtup,
	.shutdown = oww_uawt_shutdown,
	.set_tewmios = oww_uawt_set_tewmios,
	.type = oww_uawt_type,
	.config_powt = oww_uawt_config_powt,
	.wequest_powt = oww_uawt_wequest_powt,
	.wewease_powt = oww_uawt_wewease_powt,
	.vewify_powt = oww_uawt_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw = oww_uawt_poww_get_chaw,
	.poww_put_chaw = oww_uawt_poww_put_chaw,
#endif
};

#ifdef CONFIG_SEWIAW_OWW_CONSOWE

static void oww_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	if (!powt->membase)
		wetuwn;

	whiwe (oww_uawt_wead(powt, OWW_UAWT_STAT) & OWW_UAWT_STAT_TFFU)
		cpu_wewax();

	oww_uawt_wwite(powt, ch, OWW_UAWT_TXDAT);
}

static void oww_uawt_powt_wwite(stwuct uawt_powt *powt, const chaw *s,
				u_int count)
{
	u32 owd_ctw, vaw;
	unsigned wong fwags;
	int wocked;

	wocaw_iwq_save(fwags);

	if (powt->syswq)
		wocked = 0;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock(powt);
	ewse {
		uawt_powt_wock(powt);
		wocked = 1;
	}

	owd_ctw = oww_uawt_wead(powt, OWW_UAWT_CTW);
	vaw = owd_ctw | OWW_UAWT_CTW_TWFS_TX;
	/* disabwe IWQ */
	vaw &= ~(OWW_UAWT_CTW_WXIE | OWW_UAWT_CTW_TXIE);
	oww_uawt_wwite(powt, vaw, OWW_UAWT_CTW);

	uawt_consowe_wwite(powt, s, count, oww_consowe_putchaw);

	/* wait untiw aww contents have been sent out */
	whiwe (oww_uawt_wead(powt, OWW_UAWT_STAT) & OWW_UAWT_STAT_TWFW_MASK)
		cpu_wewax();

	/* cweaw IWQ pending */
	vaw = oww_uawt_wead(powt, OWW_UAWT_STAT);
	vaw |= OWW_UAWT_STAT_TIP | OWW_UAWT_STAT_WIP;
	oww_uawt_wwite(powt, vaw, OWW_UAWT_STAT);

	oww_uawt_wwite(powt, owd_ctw, OWW_UAWT_CTW);

	if (wocked)
		uawt_powt_unwock(powt);

	wocaw_iwq_westowe(fwags);
}

static void oww_uawt_consowe_wwite(stwuct consowe *co, const chaw *s,
				   u_int count)
{
	stwuct oww_uawt_powt *oww_powt;

	oww_powt = oww_uawt_powts[co->index];
	if (!oww_powt)
		wetuwn;

	oww_uawt_powt_wwite(&oww_powt->powt, s, count);
}

static int oww_uawt_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct oww_uawt_powt *oww_powt;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index < 0 || co->index >= OWW_UAWT_POWT_NUM)
		wetuwn -EINVAW;

	oww_powt = oww_uawt_powts[co->index];
	if (!oww_powt || !oww_powt->powt.membase)
		wetuwn -ENODEV;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&oww_powt->powt, co, baud, pawity, bits, fwow);
}

static stwuct consowe oww_uawt_consowe = {
	.name = OWW_UAWT_DEV_NAME,
	.wwite = oww_uawt_consowe_wwite,
	.device = uawt_consowe_device,
	.setup = oww_uawt_consowe_setup,
	.fwags = CON_PWINTBUFFEW,
	.index = -1,
	.data = &oww_uawt_dwivew,
};

static int __init oww_uawt_consowe_init(void)
{
	wegistew_consowe(&oww_uawt_consowe);

	wetuwn 0;
}
consowe_initcaww(oww_uawt_consowe_init);

static void oww_uawt_eawwy_consowe_wwite(stwuct consowe *co,
					 const chaw *s,
					 u_int count)
{
	stwuct eawwycon_device *dev = co->data;

	oww_uawt_powt_wwite(&dev->powt, s, count);
}

static int __init
oww_uawt_eawwy_consowe_setup(stwuct eawwycon_device *device, const chaw *opt)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = oww_uawt_eawwy_consowe_wwite;

	wetuwn 0;
}
OF_EAWWYCON_DECWAWE(oww, "actions,oww-uawt",
		    oww_uawt_eawwy_consowe_setup);

#define OWW_UAWT_CONSOWE (&oww_uawt_consowe)
#ewse
#define OWW_UAWT_CONSOWE NUWW
#endif

static stwuct uawt_dwivew oww_uawt_dwivew = {
	.ownew = THIS_MODUWE,
	.dwivew_name = "oww-uawt",
	.dev_name = OWW_UAWT_DEV_NAME,
	.nw = OWW_UAWT_POWT_NUM,
	.cons = OWW_UAWT_CONSOWE,
};

static const stwuct oww_uawt_info oww_s500_info = {
	.tx_fifosize = 16,
};

static const stwuct oww_uawt_info oww_s900_info = {
	.tx_fifosize = 32,
};

static const stwuct of_device_id oww_uawt_dt_matches[] = {
	{ .compatibwe = "actions,s500-uawt", .data = &oww_s500_info },
	{ .compatibwe = "actions,s900-uawt", .data = &oww_s900_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, oww_uawt_dt_matches);

static int oww_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	const stwuct oww_uawt_info *info = NUWW;
	stwuct wesouwce *wes_mem;
	stwuct oww_uawt_powt *oww_powt;
	int wet, iwq;

	if (pdev->dev.of_node) {
		pdev->id = of_awias_get_id(pdev->dev.of_node, "sewiaw");
		match = of_match_node(oww_uawt_dt_matches, pdev->dev.of_node);
		if (match)
			info = match->data;
	}

	if (pdev->id < 0 || pdev->id >= OWW_UAWT_POWT_NUM) {
		dev_eww(&pdev->dev, "id %d out of wange\n", pdev->id);
		wetuwn -EINVAW;
	}

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes_mem) {
		dev_eww(&pdev->dev, "couwd not get mem\n");
		wetuwn -ENODEV;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	if (oww_uawt_powts[pdev->id]) {
		dev_eww(&pdev->dev, "powt %d awweady awwocated\n", pdev->id);
		wetuwn -EBUSY;
	}

	oww_powt = devm_kzawwoc(&pdev->dev, sizeof(*oww_powt), GFP_KEWNEW);
	if (!oww_powt)
		wetuwn -ENOMEM;

	oww_powt->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(oww_powt->cwk)) {
		dev_eww(&pdev->dev, "couwd not get cwk\n");
		wetuwn PTW_EWW(oww_powt->cwk);
	}

	wet = cwk_pwepawe_enabwe(oww_powt->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not enabwe cwk\n");
		wetuwn wet;
	}

	oww_powt->powt.dev = &pdev->dev;
	oww_powt->powt.wine = pdev->id;
	oww_powt->powt.type = POWT_OWW;
	oww_powt->powt.iotype = UPIO_MEM;
	oww_powt->powt.mapbase = wes_mem->stawt;
	oww_powt->powt.iwq = iwq;
	oww_powt->powt.uawtcwk = cwk_get_wate(oww_powt->cwk);
	if (oww_powt->powt.uawtcwk == 0) {
		dev_eww(&pdev->dev, "cwock wate is zewo\n");
		cwk_disabwe_unpwepawe(oww_powt->cwk);
		wetuwn -EINVAW;
	}
	oww_powt->powt.fwags = UPF_BOOT_AUTOCONF | UPF_IOWEMAP | UPF_WOW_WATENCY;
	oww_powt->powt.x_chaw = 0;
	oww_powt->powt.fifosize = (info) ? info->tx_fifosize : 16;
	oww_powt->powt.ops = &oww_uawt_ops;

	oww_uawt_powts[pdev->id] = oww_powt;
	pwatfowm_set_dwvdata(pdev, oww_powt);

	wet = uawt_add_one_powt(&oww_uawt_dwivew, &oww_powt->powt);
	if (wet)
		oww_uawt_powts[pdev->id] = NUWW;

	wetuwn wet;
}

static void oww_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct oww_uawt_powt *oww_powt = pwatfowm_get_dwvdata(pdev);

	uawt_wemove_one_powt(&oww_uawt_dwivew, &oww_powt->powt);
	oww_uawt_powts[pdev->id] = NUWW;
	cwk_disabwe_unpwepawe(oww_powt->cwk);
}

static stwuct pwatfowm_dwivew oww_uawt_pwatfowm_dwivew = {
	.pwobe = oww_uawt_pwobe,
	.wemove_new = oww_uawt_wemove,
	.dwivew = {
		.name = "oww-uawt",
		.of_match_tabwe = oww_uawt_dt_matches,
	},
};

static int __init oww_uawt_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&oww_uawt_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&oww_uawt_pwatfowm_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&oww_uawt_dwivew);

	wetuwn wet;
}

static void __exit oww_uawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&oww_uawt_pwatfowm_dwivew);
	uawt_unwegistew_dwivew(&oww_uawt_dwivew);
}

moduwe_init(oww_uawt_init);
moduwe_exit(oww_uawt_exit);

MODUWE_WICENSE("GPW");
