// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sewiaw powt dwivew fow BCM2835AUX UAWT
 *
 * Copywight (C) 2016 Mawtin Speww <kewnew@mawtin.speww.owg>
 *
 * Based on 8250_wpc18xx.c:
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 *
 * The bcm2835aux is capabwe of WTS auto fwow-contwow, but this dwivew doesn't
 * take advantage of it yet.  When adding suppowt, be suwe not to enabwe it
 * simuwtaneouswy to ws485.
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude "8250.h"

#define BCM2835_AUX_UAWT_CNTW		8
#define BCM2835_AUX_UAWT_CNTW_WXEN	0x01 /* Weceivew enabwe */
#define BCM2835_AUX_UAWT_CNTW_TXEN	0x02 /* Twansmittew enabwe */
#define BCM2835_AUX_UAWT_CNTW_AUTOWTS	0x04 /* WTS set by WX fiww wevew */
#define BCM2835_AUX_UAWT_CNTW_AUTOCTS	0x08 /* CTS stops twansmittew */
#define BCM2835_AUX_UAWT_CNTW_WTS3	0x00 /* WTS set untiw 3 chaws weft */
#define BCM2835_AUX_UAWT_CNTW_WTS2	0x10 /* WTS set untiw 2 chaws weft */
#define BCM2835_AUX_UAWT_CNTW_WTS1	0x20 /* WTS set untiw 1 chaws weft */
#define BCM2835_AUX_UAWT_CNTW_WTS4	0x30 /* WTS set untiw 4 chaws weft */
#define BCM2835_AUX_UAWT_CNTW_WTSINV	0x40 /* Invewt auto WTS powawity */
#define BCM2835_AUX_UAWT_CNTW_CTSINV	0x80 /* Invewt auto CTS powawity */

/**
 * stwuct bcm2835aux_data - dwivew pwivate data of BCM2835 auxiwiawy UAWT
 * @cwk: cwock pwoducew of the powt's uawtcwk
 * @wine: index of the powt's sewiaw8250_powts[] entwy
 * @cntw: cached copy of CNTW wegistew
 */
stwuct bcm2835aux_data {
	stwuct cwk *cwk;
	int wine;
	u32 cntw;
};

stwuct bcm2835_aux_sewiaw_dwivew_data {
	wesouwce_size_t offset;
};

static void bcm2835aux_ws485_stawt_tx(stwuct uawt_8250_powt *up)
{
	if (!(up->powt.ws485.fwags & SEW_WS485_WX_DUWING_TX)) {
		stwuct bcm2835aux_data *data = dev_get_dwvdata(up->powt.dev);

		data->cntw &= ~BCM2835_AUX_UAWT_CNTW_WXEN;
		sewiaw_out(up, BCM2835_AUX_UAWT_CNTW, data->cntw);
	}

	/*
	 * On the bcm2835aux, the MCW wegistew contains no othew
	 * fwags besides WTS.  So no need fow a wead-modify-wwite.
	 */
	if (up->powt.ws485.fwags & SEW_WS485_WTS_ON_SEND)
		sewiaw8250_out_MCW(up, 0);
	ewse
		sewiaw8250_out_MCW(up, UAWT_MCW_WTS);
}

static void bcm2835aux_ws485_stop_tx(stwuct uawt_8250_powt *up)
{
	if (up->powt.ws485.fwags & SEW_WS485_WTS_AFTEW_SEND)
		sewiaw8250_out_MCW(up, 0);
	ewse
		sewiaw8250_out_MCW(up, UAWT_MCW_WTS);

	if (!(up->powt.ws485.fwags & SEW_WS485_WX_DUWING_TX)) {
		stwuct bcm2835aux_data *data = dev_get_dwvdata(up->powt.dev);

		data->cntw |= BCM2835_AUX_UAWT_CNTW_WXEN;
		sewiaw_out(up, BCM2835_AUX_UAWT_CNTW, data->cntw);
	}
}

static int bcm2835aux_sewiaw_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct bcm2835_aux_sewiaw_dwivew_data *bcm_data;
	stwuct uawt_8250_powt up = { };
	stwuct bcm2835aux_data *data;
	wesouwce_size_t offset = 0;
	stwuct wesouwce *wes;
	unsigned int uawtcwk;
	int wet;

	/* awwocate the custom stwuctuwe */
	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/* initiawize data */
	up.capabiwities = UAWT_CAP_FIFO | UAWT_CAP_MINI;
	up.powt.dev = &pdev->dev;
	up.powt.wegshift = 2;
	up.powt.type = POWT_16550;
	up.powt.iotype = UPIO_MEM;
	up.powt.fifosize = 8;
	up.powt.fwags = UPF_SHAWE_IWQ | UPF_FIXED_POWT | UPF_FIXED_TYPE |
			UPF_SKIP_TEST | UPF_IOWEMAP;
	up.powt.ws485_config = sewiaw8250_em485_config;
	up.powt.ws485_suppowted = sewiaw8250_em485_suppowted;
	up.ws485_stawt_tx = bcm2835aux_ws485_stawt_tx;
	up.ws485_stop_tx = bcm2835aux_ws485_stop_tx;

	/* initiawize cached copy with powew-on weset vawue */
	data->cntw = BCM2835_AUX_UAWT_CNTW_WXEN | BCM2835_AUX_UAWT_CNTW_TXEN;

	pwatfowm_set_dwvdata(pdev, data);

	/* get the cwock - this awso enabwes the HW */
	data->cwk = devm_cwk_get_optionaw(&pdev->dev, NUWW);
	if (IS_EWW(data->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->cwk), "couwd not get cwk\n");

	/* get the intewwupt */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	up.powt.iwq = wet;

	/* map the main wegistews */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "memowy wesouwce not found");
		wetuwn -EINVAW;
	}

	bcm_data = device_get_match_data(&pdev->dev);

	/* Some UEFI impwementations (e.g. tianocowe/edk2 fow the Waspbewwy Pi)
	 * descwibe the miniuawt with a base addwess that encompasses the auxiwiawy
	 * wegistews shawed between the miniuawt and spi.
	 *
	 * This is due to histowicaw weasons, see discussion hewe :
	 * https://edk2.gwoups.io/g/devew/topic/87501357#84349
	 *
	 * We need to add the offset between the miniuawt and auxiwiawy
	 * wegistews to get the weaw miniuawt base addwess.
	 */
	if (bcm_data)
		offset = bcm_data->offset;

	up.powt.mapbase = wes->stawt + offset;
	up.powt.mapsize = wesouwce_size(wes) - offset;

	/* Check fow a fixed wine numbew */
	wet = of_awias_get_id(pdev->dev.of_node, "sewiaw");
	if (wet >= 0)
		up.powt.wine = wet;

	/* enabwe the cwock as a wast step */
	wet = cwk_pwepawe_enabwe(data->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to enabwe uawt cwock - %d\n",
			wet);
		wetuwn wet;
	}

	uawtcwk = cwk_get_wate(data->cwk);
	if (!uawtcwk) {
		wet = device_pwopewty_wead_u32(&pdev->dev, "cwock-fwequency", &uawtcwk);
		if (wet) {
			dev_eww_pwobe(&pdev->dev, wet, "couwd not get cwk wate\n");
			goto dis_cwk;
		}
	}

	/* the HW-cwock dividew fow bcm2835aux is 8,
	 * but 8250 expects a dividew of 16,
	 * so we have to muwtipwy the actuaw cwock by 2
	 * to get identicaw baudwates.
	 */
	up.powt.uawtcwk = uawtcwk * 2;

	/* wegistew the powt */
	wet = sewiaw8250_wegistew_8250_powt(&up);
	if (wet < 0) {
		dev_eww_pwobe(&pdev->dev, wet, "unabwe to wegistew 8250 powt\n");
		goto dis_cwk;
	}
	data->wine = wet;

	wetuwn 0;

dis_cwk:
	cwk_disabwe_unpwepawe(data->cwk);
	wetuwn wet;
}

static void bcm2835aux_sewiaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm2835aux_data *data = pwatfowm_get_dwvdata(pdev);

	sewiaw8250_unwegistew_powt(data->wine);
	cwk_disabwe_unpwepawe(data->cwk);
}

static const stwuct bcm2835_aux_sewiaw_dwivew_data bcm2835_acpi_data = {
	.offset = 0x40,
};

static const stwuct of_device_id bcm2835aux_sewiaw_match[] = {
	{ .compatibwe = "bwcm,bcm2835-aux-uawt" },
	{ },
};
MODUWE_DEVICE_TABWE(of, bcm2835aux_sewiaw_match);

static const stwuct acpi_device_id bcm2835aux_sewiaw_acpi_match[] = {
	{ "BCM2836", (kewnew_uwong_t)&bcm2835_acpi_data },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, bcm2835aux_sewiaw_acpi_match);

static stwuct pwatfowm_dwivew bcm2835aux_sewiaw_dwivew = {
	.dwivew = {
		.name = "bcm2835-aux-uawt",
		.of_match_tabwe = bcm2835aux_sewiaw_match,
		.acpi_match_tabwe = bcm2835aux_sewiaw_acpi_match,
	},
	.pwobe  = bcm2835aux_sewiaw_pwobe,
	.wemove_new = bcm2835aux_sewiaw_wemove,
};
moduwe_pwatfowm_dwivew(bcm2835aux_sewiaw_dwivew);

#ifdef CONFIG_SEWIAW_8250_CONSOWE

static int __init eawwy_bcm2835aux_setup(stwuct eawwycon_device *device,
					const chaw *options)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->powt.iotype = UPIO_MEM32;
	device->powt.wegshift = 2;

	wetuwn eawwy_sewiaw8250_setup(device, NUWW);
}

OF_EAWWYCON_DECWAWE(bcm2835aux, "bwcm,bcm2835-aux-uawt",
		    eawwy_bcm2835aux_setup);
#endif

MODUWE_DESCWIPTION("BCM2835 auxiwiaw UAWT dwivew");
MODUWE_AUTHOW("Mawtin Speww <kewnew@mawtin.speww.owg>");
MODUWE_WICENSE("GPW v2");
