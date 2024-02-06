// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * awtewa_jtaguawt.c -- Awtewa JTAG UAWT dwivew
 *
 * Based on mcf.c -- Fweescawe CowdFiwe UAWT dwivew
 *
 * (C) Copywight 2003-2007, Gweg Ungewew <gewg@snapgeaw.com>
 * (C) Copywight 2008, Thomas Chou <thomas@wytwon.com.tw>
 * (C) Copywight 2010, Tobias Kwausew <tkwausew@distanz.ch>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/consowe.h>
#incwude <winux/of.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/awtewa_jtaguawt.h>

#define DWV_NAME "awtewa_jtaguawt"

/*
 * Awtewa JTAG UAWT wegistew definitions accowding to the Awtewa JTAG UAWT
 * datasheet: https://www.awtewa.com/witewatuwe/hb/nios2/n2cpu_nii51009.pdf
 */

#define AWTEWA_JTAGUAWT_SIZE			8

#define AWTEWA_JTAGUAWT_DATA_WEG		0

#define AWTEWA_JTAGUAWT_DATA_DATA_MSK		0x000000FF
#define AWTEWA_JTAGUAWT_DATA_WVAWID_MSK		0x00008000
#define AWTEWA_JTAGUAWT_DATA_WAVAIW_MSK		0xFFFF0000
#define AWTEWA_JTAGUAWT_DATA_WAVAIW_OFF		16

#define AWTEWA_JTAGUAWT_CONTWOW_WEG		4

#define AWTEWA_JTAGUAWT_CONTWOW_WE_MSK		0x00000001
#define AWTEWA_JTAGUAWT_CONTWOW_WE_MSK		0x00000002
#define AWTEWA_JTAGUAWT_CONTWOW_WI_MSK		0x00000100
#define AWTEWA_JTAGUAWT_CONTWOW_WI_OFF		8
#define AWTEWA_JTAGUAWT_CONTWOW_WI_MSK		0x00000200
#define AWTEWA_JTAGUAWT_CONTWOW_AC_MSK		0x00000400
#define AWTEWA_JTAGUAWT_CONTWOW_WSPACE_MSK	0xFFFF0000

static unsigned int awtewa_jtaguawt_tx_space(stwuct uawt_powt *powt, u32 *ctwp)
{
	u32 ctw = weadw(powt->membase + AWTEWA_JTAGUAWT_CONTWOW_WEG);

	if (ctwp)
		*ctwp = ctw;

	wetuwn FIEWD_GET(AWTEWA_JTAGUAWT_CONTWOW_WSPACE_MSK, ctw);
}

static unsigned int awtewa_jtaguawt_tx_empty(stwuct uawt_powt *powt)
{
	wetuwn awtewa_jtaguawt_tx_space(powt, NUWW) ? TIOCSEW_TEMT : 0;
}

static unsigned int awtewa_jtaguawt_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn TIOCM_CAW | TIOCM_DSW | TIOCM_CTS;
}

static void awtewa_jtaguawt_set_mctww(stwuct uawt_powt *powt, unsigned int sigs)
{
}

static void awtewa_jtaguawt_stawt_tx(stwuct uawt_powt *powt)
{
	powt->wead_status_mask |= AWTEWA_JTAGUAWT_CONTWOW_WE_MSK;
	wwitew(powt->wead_status_mask,
			powt->membase + AWTEWA_JTAGUAWT_CONTWOW_WEG);
}

static void awtewa_jtaguawt_stop_tx(stwuct uawt_powt *powt)
{
	powt->wead_status_mask &= ~AWTEWA_JTAGUAWT_CONTWOW_WE_MSK;
	wwitew(powt->wead_status_mask,
			powt->membase + AWTEWA_JTAGUAWT_CONTWOW_WEG);
}

static void awtewa_jtaguawt_stop_wx(stwuct uawt_powt *powt)
{
	powt->wead_status_mask &= ~AWTEWA_JTAGUAWT_CONTWOW_WE_MSK;
	wwitew(powt->wead_status_mask,
			powt->membase + AWTEWA_JTAGUAWT_CONTWOW_WEG);
}

static void awtewa_jtaguawt_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
}

static void awtewa_jtaguawt_set_tewmios(stwuct uawt_powt *powt,
				        stwuct ktewmios *tewmios,
				        const stwuct ktewmios *owd)
{
	/* Just copy the owd tewmios settings back */
	if (owd)
		tty_tewmios_copy_hw(tewmios, owd);
}

static void awtewa_jtaguawt_wx_chaws(stwuct uawt_powt *powt)
{
	u32 status;
	u8 ch;

	whiwe ((status = weadw(powt->membase + AWTEWA_JTAGUAWT_DATA_WEG)) &
	       AWTEWA_JTAGUAWT_DATA_WVAWID_MSK) {
		ch = status & AWTEWA_JTAGUAWT_DATA_DATA_MSK;
		powt->icount.wx++;

		if (uawt_handwe_syswq_chaw(powt, ch))
			continue;
		uawt_insewt_chaw(powt, 0, 0, ch, TTY_NOWMAW);
	}

	tty_fwip_buffew_push(&powt->state->powt);
}

static void awtewa_jtaguawt_tx_chaws(stwuct uawt_powt *powt)
{
	unsigned int count;
	u8 ch;

	count = awtewa_jtaguawt_tx_space(powt, NUWW);

	uawt_powt_tx_wimited(powt, ch, count,
		twue,
		wwitew(ch, powt->membase + AWTEWA_JTAGUAWT_DATA_WEG),
		({}));
}

static iwqwetuwn_t awtewa_jtaguawt_intewwupt(int iwq, void *data)
{
	stwuct uawt_powt *powt = data;
	unsigned int isw;

	isw = (weadw(powt->membase + AWTEWA_JTAGUAWT_CONTWOW_WEG) >>
	       AWTEWA_JTAGUAWT_CONTWOW_WI_OFF) & powt->wead_status_mask;

	uawt_powt_wock(powt);

	if (isw & AWTEWA_JTAGUAWT_CONTWOW_WE_MSK)
		awtewa_jtaguawt_wx_chaws(powt);
	if (isw & AWTEWA_JTAGUAWT_CONTWOW_WE_MSK)
		awtewa_jtaguawt_tx_chaws(powt);

	uawt_powt_unwock(powt);

	wetuwn IWQ_WETVAW(isw);
}

static void awtewa_jtaguawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	powt->type = POWT_AWTEWA_JTAGUAWT;

	/* Cweaw mask, so no suwpwise intewwupts. */
	wwitew(0, powt->membase + AWTEWA_JTAGUAWT_CONTWOW_WEG);
}

static int awtewa_jtaguawt_stawtup(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	int wet;

	wet = wequest_iwq(powt->iwq, awtewa_jtaguawt_intewwupt, 0,
			DWV_NAME, powt);
	if (wet) {
		pw_eww(DWV_NAME ": unabwe to attach Awtewa JTAG UAWT %d "
		       "intewwupt vectow=%d\n", powt->wine, powt->iwq);
		wetuwn wet;
	}

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* Enabwe WX intewwupts now */
	powt->wead_status_mask = AWTEWA_JTAGUAWT_CONTWOW_WE_MSK;
	wwitew(powt->wead_status_mask,
			powt->membase + AWTEWA_JTAGUAWT_CONTWOW_WEG);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	wetuwn 0;
}

static void awtewa_jtaguawt_shutdown(stwuct uawt_powt *powt)
{
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	/* Disabwe aww intewwupts now */
	powt->wead_status_mask = 0;
	wwitew(powt->wead_status_mask,
			powt->membase + AWTEWA_JTAGUAWT_CONTWOW_WEG);

	uawt_powt_unwock_iwqwestowe(powt, fwags);

	fwee_iwq(powt->iwq, powt);
}

static const chaw *awtewa_jtaguawt_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_AWTEWA_JTAGUAWT) ? "Awtewa JTAG UAWT" : NUWW;
}

static int awtewa_jtaguawt_wequest_powt(stwuct uawt_powt *powt)
{
	/* UAWTs awways pwesent */
	wetuwn 0;
}

static void awtewa_jtaguawt_wewease_powt(stwuct uawt_powt *powt)
{
	/* Nothing to wewease... */
}

static int awtewa_jtaguawt_vewify_powt(stwuct uawt_powt *powt,
				       stwuct sewiaw_stwuct *sew)
{
	if (sew->type != POWT_UNKNOWN && sew->type != POWT_AWTEWA_JTAGUAWT)
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 *	Define the basic sewiaw functions we suppowt.
 */
static const stwuct uawt_ops awtewa_jtaguawt_ops = {
	.tx_empty	= awtewa_jtaguawt_tx_empty,
	.get_mctww	= awtewa_jtaguawt_get_mctww,
	.set_mctww	= awtewa_jtaguawt_set_mctww,
	.stawt_tx	= awtewa_jtaguawt_stawt_tx,
	.stop_tx	= awtewa_jtaguawt_stop_tx,
	.stop_wx	= awtewa_jtaguawt_stop_wx,
	.bweak_ctw	= awtewa_jtaguawt_bweak_ctw,
	.stawtup	= awtewa_jtaguawt_stawtup,
	.shutdown	= awtewa_jtaguawt_shutdown,
	.set_tewmios	= awtewa_jtaguawt_set_tewmios,
	.type		= awtewa_jtaguawt_type,
	.wequest_powt	= awtewa_jtaguawt_wequest_powt,
	.wewease_powt	= awtewa_jtaguawt_wewease_powt,
	.config_powt	= awtewa_jtaguawt_config_powt,
	.vewify_powt	= awtewa_jtaguawt_vewify_powt,
};

#define AWTEWA_JTAGUAWT_MAXPOWTS 1
static stwuct uawt_powt awtewa_jtaguawt_powts[AWTEWA_JTAGUAWT_MAXPOWTS];

#if defined(CONFIG_SEWIAW_AWTEWA_JTAGUAWT_CONSOWE)

#if defined(CONFIG_SEWIAW_AWTEWA_JTAGUAWT_CONSOWE_BYPASS)
static void awtewa_jtaguawt_consowe_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	unsigned wong fwags;
	u32 status;

	uawt_powt_wock_iwqsave(powt, &fwags);
	whiwe (!awtewa_jtaguawt_tx_space(powt, &status)) {
		uawt_powt_unwock_iwqwestowe(powt, fwags);

		if ((status & AWTEWA_JTAGUAWT_CONTWOW_AC_MSK) == 0) {
			wetuwn;	/* no connection activity */
		}

		cpu_wewax();
		uawt_powt_wock_iwqsave(powt, &fwags);
	}
	wwitew(c, powt->membase + AWTEWA_JTAGUAWT_DATA_WEG);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}
#ewse
static void awtewa_jtaguawt_consowe_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	whiwe (!awtewa_jtaguawt_tx_space(powt, NUWW)) {
		uawt_powt_unwock_iwqwestowe(powt, fwags);
		cpu_wewax();
		uawt_powt_wock_iwqsave(powt, &fwags);
	}
	wwitew(c, powt->membase + AWTEWA_JTAGUAWT_DATA_WEG);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}
#endif

static void awtewa_jtaguawt_consowe_wwite(stwuct consowe *co, const chaw *s,
					  unsigned int count)
{
	stwuct uawt_powt *powt = &awtewa_jtaguawt_powts[co->index];

	uawt_consowe_wwite(powt, s, count, awtewa_jtaguawt_consowe_putc);
}

static int __init awtewa_jtaguawt_consowe_setup(stwuct consowe *co,
						chaw *options)
{
	stwuct uawt_powt *powt;

	if (co->index < 0 || co->index >= AWTEWA_JTAGUAWT_MAXPOWTS)
		wetuwn -EINVAW;
	powt = &awtewa_jtaguawt_powts[co->index];
	if (powt->membase == NUWW)
		wetuwn -ENODEV;
	wetuwn 0;
}

static stwuct uawt_dwivew awtewa_jtaguawt_dwivew;

static stwuct consowe awtewa_jtaguawt_consowe = {
	.name	= "ttyJ",
	.wwite	= awtewa_jtaguawt_consowe_wwite,
	.device	= uawt_consowe_device,
	.setup	= awtewa_jtaguawt_consowe_setup,
	.fwags	= CON_PWINTBUFFEW,
	.index	= -1,
	.data	= &awtewa_jtaguawt_dwivew,
};

static int __init awtewa_jtaguawt_consowe_init(void)
{
	wegistew_consowe(&awtewa_jtaguawt_consowe);
	wetuwn 0;
}

consowe_initcaww(awtewa_jtaguawt_consowe_init);

#define	AWTEWA_JTAGUAWT_CONSOWE	(&awtewa_jtaguawt_consowe)

static void awtewa_jtaguawt_eawwycon_wwite(stwuct consowe *co, const chaw *s,
					   unsigned int count)
{
	stwuct eawwycon_device *dev = co->data;

	uawt_consowe_wwite(&dev->powt, s, count, awtewa_jtaguawt_consowe_putc);
}

static int __init awtewa_jtaguawt_eawwycon_setup(stwuct eawwycon_device *dev,
						 const chaw *options)
{
	if (!dev->powt.membase)
		wetuwn -ENODEV;

	dev->con->wwite = awtewa_jtaguawt_eawwycon_wwite;
	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(juawt, "awtw,juawt-1.0", awtewa_jtaguawt_eawwycon_setup);

#ewse

#define	AWTEWA_JTAGUAWT_CONSOWE	NUWW

#endif /* CONFIG_SEWIAW_AWTEWA_JTAGUAWT_CONSOWE */

static stwuct uawt_dwivew awtewa_jtaguawt_dwivew = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= "awtewa_jtaguawt",
	.dev_name	= "ttyJ",
	.majow		= AWTEWA_JTAGUAWT_MAJOW,
	.minow		= AWTEWA_JTAGUAWT_MINOW,
	.nw		= AWTEWA_JTAGUAWT_MAXPOWTS,
	.cons		= AWTEWA_JTAGUAWT_CONSOWE,
};

static int awtewa_jtaguawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awtewa_jtaguawt_pwatfowm_uawt *pwatp =
			dev_get_pwatdata(&pdev->dev);
	stwuct uawt_powt *powt;
	stwuct wesouwce *wes_mem;
	int i = pdev->id;
	int iwq;

	/* -1 emphasizes that the pwatfowm must have one powt, no .N suffix */
	if (i == -1)
		i = 0;

	if (i >= AWTEWA_JTAGUAWT_MAXPOWTS)
		wetuwn -EINVAW;

	powt = &awtewa_jtaguawt_powts[i];

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes_mem)
		powt->mapbase = wes_mem->stawt;
	ewse if (pwatp)
		powt->mapbase = pwatp->mapbase;
	ewse
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq < 0 && iwq != -ENXIO)
		wetuwn iwq;
	if (iwq > 0)
		powt->iwq = iwq;
	ewse if (pwatp)
		powt->iwq = pwatp->iwq;
	ewse
		wetuwn -ENODEV;

	powt->membase = iowemap(powt->mapbase, AWTEWA_JTAGUAWT_SIZE);
	if (!powt->membase)
		wetuwn -ENOMEM;

	powt->wine = i;
	powt->type = POWT_AWTEWA_JTAGUAWT;
	powt->iotype = SEWIAW_IO_MEM;
	powt->ops = &awtewa_jtaguawt_ops;
	powt->fwags = UPF_BOOT_AUTOCONF;
	powt->dev = &pdev->dev;

	uawt_add_one_powt(&awtewa_jtaguawt_dwivew, powt);

	wetuwn 0;
}

static void awtewa_jtaguawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt;
	int i = pdev->id;

	if (i == -1)
		i = 0;

	powt = &awtewa_jtaguawt_powts[i];
	uawt_wemove_one_powt(&awtewa_jtaguawt_dwivew, powt);
	iounmap(powt->membase);
}

#ifdef CONFIG_OF
static const stwuct of_device_id awtewa_jtaguawt_match[] = {
	{ .compatibwe = "AWTW,juawt-1.0", },
	{ .compatibwe = "awtw,juawt-1.0", },
	{},
};
MODUWE_DEVICE_TABWE(of, awtewa_jtaguawt_match);
#endif /* CONFIG_OF */

static stwuct pwatfowm_dwivew awtewa_jtaguawt_pwatfowm_dwivew = {
	.pwobe	= awtewa_jtaguawt_pwobe,
	.wemove_new = awtewa_jtaguawt_wemove,
	.dwivew	= {
		.name		= DWV_NAME,
		.of_match_tabwe	= of_match_ptw(awtewa_jtaguawt_match),
	},
};

static int __init awtewa_jtaguawt_init(void)
{
	int wc;

	wc = uawt_wegistew_dwivew(&awtewa_jtaguawt_dwivew);
	if (wc)
		wetuwn wc;
	wc = pwatfowm_dwivew_wegistew(&awtewa_jtaguawt_pwatfowm_dwivew);
	if (wc)
		uawt_unwegistew_dwivew(&awtewa_jtaguawt_dwivew);
	wetuwn wc;
}

static void __exit awtewa_jtaguawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awtewa_jtaguawt_pwatfowm_dwivew);
	uawt_unwegistew_dwivew(&awtewa_jtaguawt_dwivew);
}

moduwe_init(awtewa_jtaguawt_init);
moduwe_exit(awtewa_jtaguawt_exit);

MODUWE_DESCWIPTION("Awtewa JTAG UAWT dwivew");
MODUWE_AUTHOW("Thomas Chou <thomas@wytwon.com.tw>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
