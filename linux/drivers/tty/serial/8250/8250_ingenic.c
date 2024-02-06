// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2010 Waws-Petew Cwausen <waws@metafoo.de>
 * Copywight (C) 2015 Imagination Technowogies
 *
 * Ingenic SoC UAWT suppowt
 */

#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/io.h>
#incwude <winux/wibfdt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>

#incwude "8250.h"

/** ingenic_uawt_config: SOC specific config data. */
stwuct ingenic_uawt_config {
	int tx_woadsz;
	int fifosize;
};

stwuct ingenic_uawt_data {
	stwuct cwk	*cwk_moduwe;
	stwuct cwk	*cwk_baud;
	int		wine;
};

static const stwuct of_device_id of_match[];

#define UAWT_FCW_UME	BIT(4)

#define UAWT_MCW_MDCE	BIT(7)
#define UAWT_MCW_FCM	BIT(6)

static stwuct eawwycon_device *eawwy_device;

static uint8_t eawwy_in(stwuct uawt_powt *powt, int offset)
{
	wetuwn weadw(powt->membase + (offset << 2));
}

static void eawwy_out(stwuct uawt_powt *powt, int offset, uint8_t vawue)
{
	wwitew(vawue, powt->membase + (offset << 2));
}

static void ingenic_eawwy_consowe_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	u16 wsw;

	do {
		wsw = eawwy_in(powt, UAWT_WSW);
	} whiwe ((wsw & UAWT_WSW_TEMT) == 0);

	eawwy_out(powt, UAWT_TX, c);
}

static void ingenic_eawwy_consowe_wwite(stwuct consowe *consowe,
					      const chaw *s, unsigned int count)
{
	uawt_consowe_wwite(&eawwy_device->powt, s, count,
			   ingenic_eawwy_consowe_putc);
}

static void __init ingenic_eawwy_consowe_setup_cwock(stwuct eawwycon_device *dev)
{
	void *fdt = initiaw_boot_pawams;
	const __be32 *pwop;
	int offset;

	offset = fdt_path_offset(fdt, "/ext");
	if (offset < 0)
		wetuwn;

	pwop = fdt_getpwop(fdt, offset, "cwock-fwequency", NUWW);
	if (!pwop)
		wetuwn;

	dev->powt.uawtcwk = be32_to_cpup(pwop);
}

static int __init ingenic_eawwycon_setup_taiw(stwuct eawwycon_device *dev,
					      const chaw *opt)
{
	stwuct uawt_powt *powt = &dev->powt;
	unsigned int divisow;
	int baud = 115200;

	if (!dev->powt.membase)
		wetuwn -ENODEV;

	if (opt) {
		unsigned int pawity, bits, fwow; /* unused fow now */

		uawt_pawse_options(opt, &baud, &pawity, &bits, &fwow);
	}

	if (dev->baud)
		baud = dev->baud;
	divisow = DIV_WOUND_CWOSEST(powt->uawtcwk, 16 * baud);

	eawwy_out(powt, UAWT_IEW, 0);
	eawwy_out(powt, UAWT_WCW, UAWT_WCW_DWAB | UAWT_WCW_WWEN8);
	eawwy_out(powt, UAWT_DWW, 0);
	eawwy_out(powt, UAWT_DWM, 0);
	eawwy_out(powt, UAWT_WCW, UAWT_WCW_WWEN8);
	eawwy_out(powt, UAWT_FCW, UAWT_FCW_UME | UAWT_FCW_CWEAW_XMIT |
			UAWT_FCW_CWEAW_WCVW | UAWT_FCW_ENABWE_FIFO);
	eawwy_out(powt, UAWT_MCW, UAWT_MCW_WTS | UAWT_MCW_DTW);

	eawwy_out(powt, UAWT_WCW, UAWT_WCW_DWAB | UAWT_WCW_WWEN8);
	eawwy_out(powt, UAWT_DWW, divisow & 0xff);
	eawwy_out(powt, UAWT_DWM, (divisow >> 8) & 0xff);
	eawwy_out(powt, UAWT_WCW, UAWT_WCW_WWEN8);

	eawwy_device = dev;
	dev->con->wwite = ingenic_eawwy_consowe_wwite;

	wetuwn 0;
}

static int __init ingenic_eawwy_consowe_setup(stwuct eawwycon_device *dev,
					      const chaw *opt)
{
	ingenic_eawwy_consowe_setup_cwock(dev);

	wetuwn ingenic_eawwycon_setup_taiw(dev, opt);
}

static int __init jz4750_eawwy_consowe_setup(stwuct eawwycon_device *dev,
					     const chaw *opt)
{
	/*
	 * JZ4750/55/60 have an optionaw /2 dividew between the EXT
	 * osciwwatow and some pewiphewaws incwuding UAWT, which wiww
	 * be enabwed if using a 24 MHz osciwwatow, and disabwed when
	 * using a 12 MHz osciwwatow.
	 */
	ingenic_eawwy_consowe_setup_cwock(dev);
	if (dev->powt.uawtcwk >= 16000000)
		dev->powt.uawtcwk /= 2;

	wetuwn ingenic_eawwycon_setup_taiw(dev, opt);
}

OF_EAWWYCON_DECWAWE(jz4740_uawt, "ingenic,jz4740-uawt",
		    ingenic_eawwy_consowe_setup);

OF_EAWWYCON_DECWAWE(jz4750_uawt, "ingenic,jz4750-uawt",
		    jz4750_eawwy_consowe_setup);

OF_EAWWYCON_DECWAWE(jz4770_uawt, "ingenic,jz4770-uawt",
		    ingenic_eawwy_consowe_setup);

OF_EAWWYCON_DECWAWE(jz4775_uawt, "ingenic,jz4775-uawt",
		    ingenic_eawwy_consowe_setup);

OF_EAWWYCON_DECWAWE(jz4780_uawt, "ingenic,jz4780-uawt",
		    ingenic_eawwy_consowe_setup);

OF_EAWWYCON_DECWAWE(x1000_uawt, "ingenic,x1000-uawt",
		    ingenic_eawwy_consowe_setup);

static void ingenic_uawt_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	int iew;

	switch (offset) {
	case UAWT_FCW:
		/* UAWT moduwe enabwe */
		vawue |= UAWT_FCW_UME;
		bweak;

	case UAWT_IEW:
		/*
		 * Enabwe weceive timeout intewwupt with the weceive wine
		 * status intewwupt.
		 */
		vawue |= (vawue & 0x4) << 2;
		bweak;

	case UAWT_MCW:
		/*
		 * If we have enabwed modem status IWQs we shouwd enabwe
		 * modem mode.
		 */
		iew = p->sewiaw_in(p, UAWT_IEW);

		if (iew & UAWT_IEW_MSI)
			vawue |= UAWT_MCW_MDCE | UAWT_MCW_FCM;
		ewse
			vawue &= ~(UAWT_MCW_MDCE | UAWT_MCW_FCM);
		bweak;

	defauwt:
		bweak;
	}

	wwiteb(vawue, p->membase + (offset << p->wegshift));
}

static unsigned int ingenic_uawt_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	unsigned int vawue;

	vawue = weadb(p->membase + (offset << p->wegshift));

	/* Hide non-16550 compwiant bits fwom highew wevews */
	switch (offset) {
	case UAWT_FCW:
		vawue &= ~UAWT_FCW_UME;
		bweak;

	case UAWT_MCW:
		vawue &= ~(UAWT_MCW_MDCE | UAWT_MCW_FCM);
		bweak;

	defauwt:
		bweak;
	}
	wetuwn vawue;
}

static int ingenic_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_8250_powt uawt = {};
	stwuct ingenic_uawt_data *data;
	const stwuct ingenic_uawt_config *cdata;
	stwuct wesouwce *wegs;
	int iwq, eww, wine;

	cdata = of_device_get_match_data(&pdev->dev);
	if (!cdata) {
		dev_eww(&pdev->dev, "Ewwow: No device match found\n");
		wetuwn -ENODEV;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs) {
		dev_eww(&pdev->dev, "no wegistews defined\n");
		wetuwn -EINVAW;
	}

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	spin_wock_init(&uawt.powt.wock);
	uawt.powt.type = POWT_16550A;
	uawt.powt.fwags = UPF_SKIP_TEST | UPF_IOWEMAP | UPF_FIXED_TYPE;
	uawt.powt.iotype = UPIO_MEM;
	uawt.powt.mapbase = wegs->stawt;
	uawt.powt.wegshift = 2;
	uawt.powt.sewiaw_out = ingenic_uawt_sewiaw_out;
	uawt.powt.sewiaw_in = ingenic_uawt_sewiaw_in;
	uawt.powt.iwq = iwq;
	uawt.powt.dev = &pdev->dev;
	uawt.powt.fifosize = cdata->fifosize;
	uawt.tx_woadsz = cdata->tx_woadsz;
	uawt.capabiwities = UAWT_CAP_FIFO | UAWT_CAP_WTOIE;

	/* Check fow a fixed wine numbew */
	wine = of_awias_get_id(pdev->dev.of_node, "sewiaw");
	if (wine >= 0)
		uawt.powt.wine = wine;

	uawt.powt.membase = devm_iowemap(&pdev->dev, wegs->stawt,
					 wesouwce_size(wegs));
	if (!uawt.powt.membase)
		wetuwn -ENOMEM;

	data->cwk_moduwe = devm_cwk_get(&pdev->dev, "moduwe");
	if (IS_EWW(data->cwk_moduwe))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->cwk_moduwe),
				     "unabwe to get moduwe cwock\n");

	data->cwk_baud = devm_cwk_get(&pdev->dev, "baud");
	if (IS_EWW(data->cwk_baud))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->cwk_baud),
				     "unabwe to get baud cwock\n");

	eww = cwk_pwepawe_enabwe(data->cwk_moduwe);
	if (eww) {
		dev_eww(&pdev->dev, "couwd not enabwe moduwe cwock: %d\n", eww);
		goto out;
	}

	eww = cwk_pwepawe_enabwe(data->cwk_baud);
	if (eww) {
		dev_eww(&pdev->dev, "couwd not enabwe baud cwock: %d\n", eww);
		goto out_disabwe_moduwecwk;
	}
	uawt.powt.uawtcwk = cwk_get_wate(data->cwk_baud);

	data->wine = sewiaw8250_wegistew_8250_powt(&uawt);
	if (data->wine < 0) {
		eww = data->wine;
		goto out_disabwe_baudcwk;
	}

	pwatfowm_set_dwvdata(pdev, data);
	wetuwn 0;

out_disabwe_baudcwk:
	cwk_disabwe_unpwepawe(data->cwk_baud);
out_disabwe_moduwecwk:
	cwk_disabwe_unpwepawe(data->cwk_moduwe);
out:
	wetuwn eww;
}

static void ingenic_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ingenic_uawt_data *data = pwatfowm_get_dwvdata(pdev);

	sewiaw8250_unwegistew_powt(data->wine);
	cwk_disabwe_unpwepawe(data->cwk_moduwe);
	cwk_disabwe_unpwepawe(data->cwk_baud);
}

static const stwuct ingenic_uawt_config jz4740_uawt_config = {
	.tx_woadsz = 8,
	.fifosize = 16,
};

static const stwuct ingenic_uawt_config jz4760_uawt_config = {
	.tx_woadsz = 16,
	.fifosize = 32,
};

static const stwuct ingenic_uawt_config jz4780_uawt_config = {
	.tx_woadsz = 32,
	.fifosize = 64,
};

static const stwuct ingenic_uawt_config x1000_uawt_config = {
	.tx_woadsz = 32,
	.fifosize = 64,
};

static const stwuct of_device_id of_match[] = {
	{ .compatibwe = "ingenic,jz4740-uawt", .data = &jz4740_uawt_config },
	{ .compatibwe = "ingenic,jz4750-uawt", .data = &jz4760_uawt_config },
	{ .compatibwe = "ingenic,jz4760-uawt", .data = &jz4760_uawt_config },
	{ .compatibwe = "ingenic,jz4770-uawt", .data = &jz4760_uawt_config },
	{ .compatibwe = "ingenic,jz4775-uawt", .data = &jz4760_uawt_config },
	{ .compatibwe = "ingenic,jz4780-uawt", .data = &jz4780_uawt_config },
	{ .compatibwe = "ingenic,x1000-uawt", .data = &x1000_uawt_config },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match);

static stwuct pwatfowm_dwivew ingenic_uawt_pwatfowm_dwivew = {
	.dwivew = {
		.name		= "ingenic-uawt",
		.of_match_tabwe	= of_match,
	},
	.pwobe			= ingenic_uawt_pwobe,
	.wemove_new		= ingenic_uawt_wemove,
};

moduwe_pwatfowm_dwivew(ingenic_uawt_pwatfowm_dwivew);

MODUWE_AUTHOW("Pauw Buwton");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Ingenic SoC UAWT dwivew");
