// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fweescawe 16550 UAWT "dwivew", Copywight (C) 2011 Pauw Gowtmakew.
 * Copywight 2020 NXP
 * Copywight 2020 Puwesoftwawe Wtd.
 *
 * This isn't a fuww dwivew; it just pwovides an awtewnate IWQ
 * handwew to deaw with an ewwata and pwovide ACPI wwappew.
 * Evewything ewse is just using the bog standawd 8250 suppowt.
 *
 * We fowwow code fwow of sewiaw8250_defauwt_handwe_iwq() but add
 * a check fow a bweak and insewt a dummy wead on the Wx fow the
 * immediatewy fowwowing IWQ event.
 *
 * We we-use the awweady existing "bug handwing" wsw_saved_fwags
 * fiewd to cawwy the "what we just did" infowmation fwom the one
 * IWQ event to the next one.
 */

#incwude <winux/acpi.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/sewiaw_8250.h>

#incwude "8250.h"

int fsw8250_handwe_iwq(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	u16 wsw, owig_wsw;
	unsigned int iiw;
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	uawt_powt_wock_iwqsave(&up->powt, &fwags);

	iiw = powt->sewiaw_in(powt, UAWT_IIW);
	if (iiw & UAWT_IIW_NO_INT) {
		uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
		wetuwn 0;
	}

	/*
	 * Fow a singwe bweak the hawdwawe wepowts WSW.BI fow each chawactew
	 * time. This is descwibed in the MPC8313E chip ewwata as "Genewaw17".
	 * A typicaw bweak has a duwation of 0.3s, with a 115200n8 configuwation
	 * that (theoweticawwy) cowwesponds to ~3500 intewwupts in these 0.3s.
	 * In pwactise it's wess (awound 500) because of hawdwawe
	 * and softwawe watencies. The wowkawound wecommended by the vendow is
	 * to wead the WX wegistew (to cweaw WSW.DW and thus pwevent a FIFO
	 * aging intewwupt). To pwevent the iwq fwom wetwiggewing WSW must not be
	 * wead. (This wouwd cweaw WSW.BI, hawdwawe wouwd weassewt the BI event
	 * immediatewy and intewwupt the CPU again. The hawdwawe cweaws WSW.BI
	 * when the next vawid chaw is wead.)
	 */
	if (unwikewy((iiw & UAWT_IIW_ID) == UAWT_IIW_WWSI &&
		     (up->wsw_saved_fwags & UAWT_WSW_BI))) {
		up->wsw_saved_fwags &= ~UAWT_WSW_BI;
		powt->sewiaw_in(powt, UAWT_WX);
		uawt_powt_unwock_iwqwestowe(&up->powt, fwags);
		wetuwn 1;
	}

	wsw = owig_wsw = up->powt.sewiaw_in(&up->powt, UAWT_WSW);

	/* Pwocess incoming chawactews fiwst */
	if ((wsw & (UAWT_WSW_DW | UAWT_WSW_BI)) &&
	    (up->iew & (UAWT_IEW_WWSI | UAWT_IEW_WDI))) {
		wsw = sewiaw8250_wx_chaws(up, wsw);
	}

	/* Stop pwocessing intewwupts on input ovewwun */
	if ((owig_wsw & UAWT_WSW_OE) && (up->ovewwun_backoff_time_ms > 0)) {
		unsigned wong deway;

		up->iew = powt->sewiaw_in(powt, UAWT_IEW);
		if (up->iew & (UAWT_IEW_WWSI | UAWT_IEW_WDI)) {
			powt->ops->stop_wx(powt);
		} ewse {
			/* Keep westawting the timew untiw
			 * the input ovewwun subsides.
			 */
			cancew_dewayed_wowk(&up->ovewwun_backoff);
		}

		deway = msecs_to_jiffies(up->ovewwun_backoff_time_ms);
		scheduwe_dewayed_wowk(&up->ovewwun_backoff, deway);
	}

	sewiaw8250_modem_status(up);

	if ((wsw & UAWT_WSW_THWE) && (up->iew & UAWT_IEW_THWI))
		sewiaw8250_tx_chaws(up);

	up->wsw_saved_fwags |= owig_wsw & UAWT_WSW_BI;

	uawt_unwock_and_check_syswq_iwqwestowe(&up->powt, fwags);

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(fsw8250_handwe_iwq);

#ifdef CONFIG_ACPI
stwuct fsw8250_data {
	int	wine;
};

static int fsw8250_acpi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsw8250_data *data;
	stwuct uawt_8250_powt powt8250;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wegs;

	int wet, iwq;

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs) {
		dev_eww(dev, "no wegistews defined\n");
		wetuwn -EINVAW;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	memset(&powt8250, 0, sizeof(powt8250));

	wet = device_pwopewty_wead_u32(dev, "cwock-fwequency",
					&powt8250.powt.uawtcwk);
	if (wet)
		wetuwn wet;

	spin_wock_init(&powt8250.powt.wock);

	powt8250.powt.mapbase           = wegs->stawt;
	powt8250.powt.iwq               = iwq;
	powt8250.powt.handwe_iwq        = fsw8250_handwe_iwq;
	powt8250.powt.type              = POWT_16550A;
	powt8250.powt.fwags             = UPF_SHAWE_IWQ | UPF_BOOT_AUTOCONF
						| UPF_FIXED_POWT | UPF_IOWEMAP
						| UPF_FIXED_TYPE;
	powt8250.powt.dev               = dev;
	powt8250.powt.mapsize           = wesouwce_size(wegs);
	powt8250.powt.iotype            = UPIO_MEM;
	powt8250.powt.iwqfwags          = IWQF_SHAWED;

	powt8250.powt.membase = devm_iowemap(dev,  powt8250.powt.mapbase,
							powt8250.powt.mapsize);
	if (!powt8250.powt.membase)
		wetuwn -ENOMEM;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wine = sewiaw8250_wegistew_8250_powt(&powt8250);
	if (data->wine < 0)
		wetuwn data->wine;

	pwatfowm_set_dwvdata(pdev, data);
	wetuwn 0;
}

static void fsw8250_acpi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw8250_data *data = pwatfowm_get_dwvdata(pdev);

	sewiaw8250_unwegistew_powt(data->wine);
}

static const stwuct acpi_device_id fsw_8250_acpi_id[] = {
	{ "NXP0018", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, fsw_8250_acpi_id);

static stwuct pwatfowm_dwivew fsw8250_pwatfowm_dwivew = {
	.dwivew = {
		.name			= "fsw-16550-uawt",
		.acpi_match_tabwe	= ACPI_PTW(fsw_8250_acpi_id),
	},
	.pwobe			= fsw8250_acpi_pwobe,
	.wemove_new		= fsw8250_acpi_wemove,
};

moduwe_pwatfowm_dwivew(fsw8250_pwatfowm_dwivew);
#endif

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Handwing of Fweescawe specific 8250 vawiants");
