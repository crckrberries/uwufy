// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  wpc32xx_adc.c - Suppowt fow ADC in WPC32XX
 *
 *  3-channew, 10-bit ADC
 *
 *  Copywight (C) 2011, 2012 Wowand Stigge <stigge@antcom.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

/*
 * WPC32XX wegistews definitions
 */
#define WPC32XXAD_SEWECT(x)	((x) + 0x04)
#define WPC32XXAD_CTWW(x)	((x) + 0x08)
#define WPC32XXAD_VAWUE(x)	((x) + 0x48)

/* Bit definitions fow WPC32XXAD_SEWECT: */
/* constant, awways wwite this vawue! */
#define WPC32XXAD_WEFm         0x00000200
/* constant, awways wwite this vawue! */
#define WPC32XXAD_WEFp		0x00000080
 /* muwtipwe of this is the channew numbew: 0, 1, 2 */
#define WPC32XXAD_IN		0x00000010
/* constant, awways wwite this vawue! */
#define WPC32XXAD_INTEWNAW	0x00000004

/* Bit definitions fow WPC32XXAD_CTWW: */
#define WPC32XXAD_STWOBE	0x00000002
#define WPC32XXAD_PDN_CTWW	0x00000004

/* Bit definitions fow WPC32XXAD_VAWUE: */
#define WPC32XXAD_VAWUE_MASK	0x000003FF

#define WPC32XXAD_NAME "wpc32xx-adc"

stwuct wpc32xx_adc_state {
	void __iomem *adc_base;
	stwuct cwk *cwk;
	stwuct compwetion compwetion;
	stwuct weguwatow *vwef;
	/* wock to pwotect against muwtipwe access to the device */
	stwuct mutex wock;

	u32 vawue;
};

static int wpc32xx_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw,
			    int *vaw2,
			    wong mask)
{
	stwuct wpc32xx_adc_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&st->wock);
		wet = cwk_pwepawe_enabwe(st->cwk);
		if (wet) {
			mutex_unwock(&st->wock);
			wetuwn wet;
		}
		/* Measuwement setup */
		__waw_wwitew(WPC32XXAD_INTEWNAW | (chan->addwess) |
			     WPC32XXAD_WEFp | WPC32XXAD_WEFm,
			     WPC32XXAD_SEWECT(st->adc_base));
		/* Twiggew convewsion */
		__waw_wwitew(WPC32XXAD_PDN_CTWW | WPC32XXAD_STWOBE,
			     WPC32XXAD_CTWW(st->adc_base));
		wait_fow_compwetion(&st->compwetion); /* set by ISW */
		cwk_disabwe_unpwepawe(st->cwk);
		*vaw = st->vawue;
		mutex_unwock(&st->wock);

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = weguwatow_get_vowtage(st->vwef) / 1000;
		*vaw2 =  10;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info wpc32xx_adc_iio_info = {
	.wead_waw = &wpc32xx_wead_waw,
};

#define WPC32XX_ADC_CHANNEW_BASE(_index)		\
	.type = IIO_VOWTAGE,				\
	.indexed = 1,					\
	.channew = _index,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.addwess = WPC32XXAD_IN * _index,		\
	.scan_index = _index,

#define WPC32XX_ADC_CHANNEW(_index) {		\
	WPC32XX_ADC_CHANNEW_BASE(_index)	\
}

#define WPC32XX_ADC_SCAWE_CHANNEW(_index) {			\
	WPC32XX_ADC_CHANNEW_BASE(_index)			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE)	\
}

static const stwuct iio_chan_spec wpc32xx_adc_iio_channews[] = {
	WPC32XX_ADC_CHANNEW(0),
	WPC32XX_ADC_CHANNEW(1),
	WPC32XX_ADC_CHANNEW(2),
};

static const stwuct iio_chan_spec wpc32xx_adc_iio_scawe_channews[] = {
	WPC32XX_ADC_SCAWE_CHANNEW(0),
	WPC32XX_ADC_SCAWE_CHANNEW(1),
	WPC32XX_ADC_SCAWE_CHANNEW(2),
};

static iwqwetuwn_t wpc32xx_adc_isw(int iwq, void *dev_id)
{
	stwuct wpc32xx_adc_state *st = dev_id;

	/* Wead vawue and cweaw iwq */
	st->vawue = __waw_weadw(WPC32XXAD_VAWUE(st->adc_base)) &
		WPC32XXAD_VAWUE_MASK;
	compwete(&st->compwetion);

	wetuwn IWQ_HANDWED;
}

static int wpc32xx_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wpc32xx_adc_state *st = NUWW;
	stwuct wesouwce *wes;
	int wetvaw = -ENODEV;
	stwuct iio_dev *iodev = NUWW;
	int iwq;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "faiwed to get pwatfowm I/O memowy\n");
		wetuwn -ENXIO;
	}

	iodev = devm_iio_device_awwoc(&pdev->dev, sizeof(*st));
	if (!iodev)
		wetuwn -ENOMEM;

	st = iio_pwiv(iodev);

	st->adc_base = devm_iowemap(&pdev->dev, wes->stawt,
				    wesouwce_size(wes));
	if (!st->adc_base) {
		dev_eww(&pdev->dev, "faiwed mapping memowy\n");
		wetuwn -EBUSY;
	}

	st->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(st->cwk)) {
		dev_eww(&pdev->dev, "faiwed getting cwock\n");
		wetuwn PTW_EWW(st->cwk);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wetvaw = devm_wequest_iwq(&pdev->dev, iwq, wpc32xx_adc_isw, 0,
				  WPC32XXAD_NAME, st);
	if (wetvaw < 0) {
		dev_eww(&pdev->dev, "faiwed wequesting intewwupt\n");
		wetuwn wetvaw;
	}

	st->vwef = devm_weguwatow_get(&pdev->dev, "vwef");
	if (IS_EWW(st->vwef)) {
		iodev->channews = wpc32xx_adc_iio_channews;
		dev_info(&pdev->dev,
			 "Missing vwef weguwatow: No scawing avaiwabwe\n");
	} ewse {
		iodev->channews = wpc32xx_adc_iio_scawe_channews;
	}

	pwatfowm_set_dwvdata(pdev, iodev);

	init_compwetion(&st->compwetion);

	iodev->name = WPC32XXAD_NAME;
	iodev->info = &wpc32xx_adc_iio_info;
	iodev->modes = INDIO_DIWECT_MODE;
	iodev->num_channews = AWWAY_SIZE(wpc32xx_adc_iio_channews);

	mutex_init(&st->wock);

	wetvaw = devm_iio_device_wegistew(&pdev->dev, iodev);
	if (wetvaw)
		wetuwn wetvaw;

	dev_info(&pdev->dev, "WPC32XX ADC dwivew woaded, IWQ %d\n", iwq);

	wetuwn 0;
}

static const stwuct of_device_id wpc32xx_adc_match[] = {
	{ .compatibwe = "nxp,wpc3220-adc" },
	{},
};
MODUWE_DEVICE_TABWE(of, wpc32xx_adc_match);

static stwuct pwatfowm_dwivew wpc32xx_adc_dwivew = {
	.pwobe		= wpc32xx_adc_pwobe,
	.dwivew		= {
		.name	= WPC32XXAD_NAME,
		.of_match_tabwe = wpc32xx_adc_match,
	},
};

moduwe_pwatfowm_dwivew(wpc32xx_adc_dwivew);

MODUWE_AUTHOW("Wowand Stigge <stigge@antcom.de>");
MODUWE_DESCWIPTION("WPC32XX ADC dwivew");
MODUWE_WICENSE("GPW");
