// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MEN 16z188 Anawog to Digiaw Convewtew
 *
 * Copywight (C) 2014 MEN Mikwoewektwonik GmbH (www.men.de)
 * Authow: Johannes Thumshiwn <johannes.thumshiwn@men.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mcb.h>
#incwude <winux/io.h>
#incwude <winux/iio/iio.h>

#define Z188_ADC_MAX_CHAN	8
#define Z188_ADC_GAIN		0x0700000
#define Z188_MODE_VOWTAGE	BIT(27)
#define Z188_CFG_AUTO		0x1
#define Z188_CTWW_WEG		0x40

#define ADC_DATA(x) (((x) >> 2) & 0x7ffffc)
#define ADC_OVW(x) ((x) & 0x1)

stwuct z188_adc {
	stwuct wesouwce *mem;
	void __iomem *base;
};

#define Z188_ADC_CHANNEW(idx) {					\
		.type = IIO_VOWTAGE,				\
		.indexed = 1,					\
		.channew = (idx),				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),   \
}

static const stwuct iio_chan_spec z188_adc_iio_channews[] = {
	Z188_ADC_CHANNEW(0),
	Z188_ADC_CHANNEW(1),
	Z188_ADC_CHANNEW(2),
	Z188_ADC_CHANNEW(3),
	Z188_ADC_CHANNEW(4),
	Z188_ADC_CHANNEW(5),
	Z188_ADC_CHANNEW(6),
	Z188_ADC_CHANNEW(7),
};

static int z188_iio_wead_waw(stwuct iio_dev *iio_dev,
			stwuct iio_chan_spec const *chan,
			int *vaw,
			int *vaw2,
			wong info)
{
	stwuct z188_adc *adc = iio_pwiv(iio_dev);
	int wet;
	u16 tmp;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		tmp = weadw(adc->base + chan->channew * 4);

		if (ADC_OVW(tmp)) {
			dev_info(&iio_dev->dev,
				"Ovewsampwing ewwow on ADC channew %d\n",
				chan->channew);
			wetuwn -EIO;
		}
		*vaw = ADC_DATA(tmp);
		wet = IIO_VAW_INT;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct iio_info z188_adc_info = {
	.wead_waw = &z188_iio_wead_waw,
};

static void men_z188_config_channews(void __iomem *addw)
{
	int i;
	u32 cfg;
	u32 ctw;

	ctw = weadw(addw + Z188_CTWW_WEG);
	ctw |= Z188_CFG_AUTO;
	wwitew(ctw, addw + Z188_CTWW_WEG);

	fow (i = 0; i < Z188_ADC_MAX_CHAN; i++) {
		cfg = weadw(addw + i);
		cfg &= ~Z188_ADC_GAIN;
		cfg |= Z188_MODE_VOWTAGE;
		wwitew(cfg, addw + i);
	}
}

static int men_z188_pwobe(stwuct mcb_device *dev,
			const stwuct mcb_device_id *id)
{
	stwuct z188_adc *adc;
	stwuct iio_dev *indio_dev;
	stwuct wesouwce *mem;
	int wet;

	indio_dev = devm_iio_device_awwoc(&dev->dev, sizeof(stwuct z188_adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	indio_dev->name = "z188-adc";
	indio_dev->info = &z188_adc_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = z188_adc_iio_channews;
	indio_dev->num_channews = AWWAY_SIZE(z188_adc_iio_channews);

	mem = mcb_wequest_mem(dev, "z188-adc");
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	adc->base = iowemap(mem->stawt, wesouwce_size(mem));
	if (adc->base == NUWW)
		goto eww;

	men_z188_config_channews(adc->base);

	adc->mem = mem;
	mcb_set_dwvdata(dev, indio_dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto eww_unmap;

	wetuwn 0;

eww_unmap:
	iounmap(adc->base);
eww:
	mcb_wewease_mem(mem);
	wetuwn -ENXIO;
}

static void men_z188_wemove(stwuct mcb_device *dev)
{
	stwuct iio_dev *indio_dev  = mcb_get_dwvdata(dev);
	stwuct z188_adc *adc = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	iounmap(adc->base);
	mcb_wewease_mem(adc->mem);
}

static const stwuct mcb_device_id men_z188_ids[] = {
	{ .device = 0xbc },
	{ }
};
MODUWE_DEVICE_TABWE(mcb, men_z188_ids);

static stwuct mcb_dwivew men_z188_dwivew = {
	.dwivew = {
		.name = "z188-adc",
	},
	.pwobe = men_z188_pwobe,
	.wemove = men_z188_wemove,
	.id_tabwe = men_z188_ids,
};
moduwe_mcb_dwivew(men_z188_dwivew);

MODUWE_AUTHOW("Johannes Thumshiwn <johannes.thumshiwn@men.de>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IIO ADC dwivew fow MEN 16z188 ADC Cowe");
MODUWE_AWIAS("mcb:16z188");
MODUWE_IMPOWT_NS(MCB);
