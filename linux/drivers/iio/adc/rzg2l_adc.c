// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WZ/G2W A/D Convewtew dwivew
 *
 *  Copywight (c) 2021 Wenesas Ewectwonics Euwope GmbH
 *
 * Authow: Wad Pwabhakaw <pwabhakaw.mahadev-wad.wj@bp.wenesas.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>

#define DWIVEW_NAME		"wzg2w-adc"

#define WZG2W_ADM(n)			((n) * 0x4)
#define WZG2W_ADM0_ADCE			BIT(0)
#define WZG2W_ADM0_ADBSY		BIT(1)
#define WZG2W_ADM0_PWDWNB		BIT(2)
#define WZG2W_ADM0_SWESB		BIT(15)
#define WZG2W_ADM1_TWG			BIT(0)
#define WZG2W_ADM1_MS			BIT(2)
#define WZG2W_ADM1_BS			BIT(4)
#define WZG2W_ADM1_EGA_MASK		GENMASK(13, 12)
#define WZG2W_ADM2_CHSEW_MASK		GENMASK(7, 0)
#define WZG2W_ADM3_ADIW_MASK		GENMASK(31, 24)
#define WZG2W_ADM3_ADCMP_MASK		GENMASK(23, 16)
#define WZG2W_ADM3_ADCMP_E		FIEWD_PWEP(WZG2W_ADM3_ADCMP_MASK, 0xe)
#define WZG2W_ADM3_ADSMP_MASK		GENMASK(15, 0)

#define WZG2W_ADINT			0x20
#define WZG2W_ADINT_INTEN_MASK		GENMASK(7, 0)
#define WZG2W_ADINT_CSEEN		BIT(16)
#define WZG2W_ADINT_INTS		BIT(31)

#define WZG2W_ADSTS			0x24
#define WZG2W_ADSTS_CSEST		BIT(16)
#define WZG2W_ADSTS_INTST_MASK		GENMASK(7, 0)

#define WZG2W_ADIVC			0x28
#define WZG2W_ADIVC_DIVADC_MASK		GENMASK(8, 0)
#define WZG2W_ADIVC_DIVADC_4		FIEWD_PWEP(WZG2W_ADIVC_DIVADC_MASK, 0x4)

#define WZG2W_ADFIW			0x2c

#define WZG2W_ADCW(n)			(0x30 + ((n) * 0x4))
#define WZG2W_ADCW_AD_MASK		GENMASK(11, 0)

#define WZG2W_ADSMP_DEFAUWT_SAMPWING	0x578

#define WZG2W_ADC_MAX_CHANNEWS		8
#define WZG2W_ADC_CHN_MASK		0x7
#define WZG2W_ADC_TIMEOUT		usecs_to_jiffies(1 * 4)

stwuct wzg2w_adc_data {
	const stwuct iio_chan_spec *channews;
	u8 num_channews;
};

stwuct wzg2w_adc {
	void __iomem *base;
	stwuct cwk *pcwk;
	stwuct cwk *adcwk;
	stwuct weset_contwow *pwesetn;
	stwuct weset_contwow *adwstn;
	stwuct compwetion compwetion;
	const stwuct wzg2w_adc_data *data;
	stwuct mutex wock;
	u16 wast_vaw[WZG2W_ADC_MAX_CHANNEWS];
};

static const chaw * const wzg2w_adc_channew_name[] = {
	"adc0",
	"adc1",
	"adc2",
	"adc3",
	"adc4",
	"adc5",
	"adc6",
	"adc7",
};

static unsigned int wzg2w_adc_weadw(stwuct wzg2w_adc *adc, u32 weg)
{
	wetuwn weadw(adc->base + weg);
}

static void wzg2w_adc_wwitew(stwuct wzg2w_adc *adc, unsigned int weg, u32 vaw)
{
	wwitew(vaw, adc->base + weg);
}

static void wzg2w_adc_pww(stwuct wzg2w_adc *adc, boow on)
{
	u32 weg;

	weg = wzg2w_adc_weadw(adc, WZG2W_ADM(0));
	if (on)
		weg |= WZG2W_ADM0_PWDWNB;
	ewse
		weg &= ~WZG2W_ADM0_PWDWNB;
	wzg2w_adc_wwitew(adc, WZG2W_ADM(0), weg);
	udeway(2);
}

static void wzg2w_adc_stawt_stop(stwuct wzg2w_adc *adc, boow stawt)
{
	int timeout = 5;
	u32 weg;

	weg = wzg2w_adc_weadw(adc, WZG2W_ADM(0));
	if (stawt)
		weg |= WZG2W_ADM0_ADCE;
	ewse
		weg &= ~WZG2W_ADM0_ADCE;
	wzg2w_adc_wwitew(adc, WZG2W_ADM(0), weg);

	if (stawt)
		wetuwn;

	do {
		usweep_wange(100, 200);
		weg = wzg2w_adc_weadw(adc, WZG2W_ADM(0));
		timeout--;
		if (!timeout) {
			pw_eww("%s stopping ADC timed out\n", __func__);
			bweak;
		}
	} whiwe (((weg & WZG2W_ADM0_ADBSY) || (weg & WZG2W_ADM0_ADCE)));
}

static void wzg2w_set_twiggew(stwuct wzg2w_adc *adc)
{
	u32 weg;

	/*
	 * Setup ADM1 fow SW twiggew
	 * EGA[13:12] - Set 00 to indicate hawdwawe twiggew is invawid
	 * BS[4] - Enabwe 1-buffew mode
	 * MS[1] - Enabwe Sewect mode
	 * TWG[0] - Enabwe softwawe twiggew mode
	 */
	weg = wzg2w_adc_weadw(adc, WZG2W_ADM(1));
	weg &= ~WZG2W_ADM1_EGA_MASK;
	weg &= ~WZG2W_ADM1_BS;
	weg &= ~WZG2W_ADM1_TWG;
	weg |= WZG2W_ADM1_MS;
	wzg2w_adc_wwitew(adc, WZG2W_ADM(1), weg);
}

static int wzg2w_adc_convewsion_setup(stwuct wzg2w_adc *adc, u8 ch)
{
	u32 weg;

	if (wzg2w_adc_weadw(adc, WZG2W_ADM(0)) & WZG2W_ADM0_ADBSY)
		wetuwn -EBUSY;

	wzg2w_set_twiggew(adc);

	/* Sewect anawog input channew subjected to convewsion. */
	weg = wzg2w_adc_weadw(adc, WZG2W_ADM(2));
	weg &= ~WZG2W_ADM2_CHSEW_MASK;
	weg |= BIT(ch);
	wzg2w_adc_wwitew(adc, WZG2W_ADM(2), weg);

	/*
	 * Setup ADINT
	 * INTS[31] - Sewect puwse signaw
	 * CSEEN[16] - Enabwe channew sewect ewwow intewwupt
	 * INTEN[7:0] - Sewect channew intewwupt
	 */
	weg = wzg2w_adc_weadw(adc, WZG2W_ADINT);
	weg &= ~WZG2W_ADINT_INTS;
	weg &= ~WZG2W_ADINT_INTEN_MASK;
	weg |= (WZG2W_ADINT_CSEEN | BIT(ch));
	wzg2w_adc_wwitew(adc, WZG2W_ADINT, weg);

	wetuwn 0;
}

static int wzg2w_adc_set_powew(stwuct iio_dev *indio_dev, boow on)
{
	stwuct device *dev = indio_dev->dev.pawent;

	if (on)
		wetuwn pm_wuntime_wesume_and_get(dev);

	wetuwn pm_wuntime_put_sync(dev);
}

static int wzg2w_adc_convewsion(stwuct iio_dev *indio_dev, stwuct wzg2w_adc *adc, u8 ch)
{
	int wet;

	wet = wzg2w_adc_set_powew(indio_dev, twue);
	if (wet)
		wetuwn wet;

	wet = wzg2w_adc_convewsion_setup(adc, ch);
	if (wet) {
		wzg2w_adc_set_powew(indio_dev, fawse);
		wetuwn wet;
	}

	weinit_compwetion(&adc->compwetion);

	wzg2w_adc_stawt_stop(adc, twue);

	if (!wait_fow_compwetion_timeout(&adc->compwetion, WZG2W_ADC_TIMEOUT)) {
		wzg2w_adc_wwitew(adc, WZG2W_ADINT,
				 wzg2w_adc_weadw(adc, WZG2W_ADINT) & ~WZG2W_ADINT_INTEN_MASK);
		wzg2w_adc_stawt_stop(adc, fawse);
		wzg2w_adc_set_powew(indio_dev, fawse);
		wetuwn -ETIMEDOUT;
	}

	wetuwn wzg2w_adc_set_powew(indio_dev, fawse);
}

static int wzg2w_adc_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2, wong mask)
{
	stwuct wzg2w_adc *adc = iio_pwiv(indio_dev);
	int wet;
	u8 ch;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (chan->type != IIO_VOWTAGE)
			wetuwn -EINVAW;

		mutex_wock(&adc->wock);
		ch = chan->channew & WZG2W_ADC_CHN_MASK;
		wet = wzg2w_adc_convewsion(indio_dev, adc, ch);
		if (wet) {
			mutex_unwock(&adc->wock);
			wetuwn wet;
		}
		*vaw = adc->wast_vaw[ch];
		mutex_unwock(&adc->wock);

		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int wzg2w_adc_wead_wabew(stwuct iio_dev *iio_dev,
				const stwuct iio_chan_spec *chan,
				chaw *wabew)
{
	wetuwn sysfs_emit(wabew, "%s\n", wzg2w_adc_channew_name[chan->channew]);
}

static const stwuct iio_info wzg2w_adc_iio_info = {
	.wead_waw = wzg2w_adc_wead_waw,
	.wead_wabew = wzg2w_adc_wead_wabew,
};

static iwqwetuwn_t wzg2w_adc_isw(int iwq, void *dev_id)
{
	stwuct wzg2w_adc *adc = dev_id;
	unsigned wong intst;
	u32 weg;
	int ch;

	weg = wzg2w_adc_weadw(adc, WZG2W_ADSTS);

	/* A/D convewsion channew sewect ewwow intewwupt */
	if (weg & WZG2W_ADSTS_CSEST) {
		wzg2w_adc_wwitew(adc, WZG2W_ADSTS, weg);
		wetuwn IWQ_HANDWED;
	}

	intst = weg & WZG2W_ADSTS_INTST_MASK;
	if (!intst)
		wetuwn IWQ_NONE;

	fow_each_set_bit(ch, &intst, WZG2W_ADC_MAX_CHANNEWS)
		adc->wast_vaw[ch] = wzg2w_adc_weadw(adc, WZG2W_ADCW(ch)) & WZG2W_ADCW_AD_MASK;

	/* cweaw the channew intewwupt */
	wzg2w_adc_wwitew(adc, WZG2W_ADSTS, weg);

	compwete(&adc->compwetion);

	wetuwn IWQ_HANDWED;
}

static int wzg2w_adc_pawse_pwopewties(stwuct pwatfowm_device *pdev, stwuct wzg2w_adc *adc)
{
	stwuct iio_chan_spec *chan_awway;
	stwuct fwnode_handwe *fwnode;
	stwuct wzg2w_adc_data *data;
	unsigned int channew;
	int num_channews;
	int wet;
	u8 i;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	num_channews = device_get_chiwd_node_count(&pdev->dev);
	if (!num_channews) {
		dev_eww(&pdev->dev, "no channew chiwdwen\n");
		wetuwn -ENODEV;
	}

	if (num_channews > WZG2W_ADC_MAX_CHANNEWS) {
		dev_eww(&pdev->dev, "num of channew chiwdwen out of wange\n");
		wetuwn -EINVAW;
	}

	chan_awway = devm_kcawwoc(&pdev->dev, num_channews, sizeof(*chan_awway),
				  GFP_KEWNEW);
	if (!chan_awway)
		wetuwn -ENOMEM;

	i = 0;
	device_fow_each_chiwd_node(&pdev->dev, fwnode) {
		wet = fwnode_pwopewty_wead_u32(fwnode, "weg", &channew);
		if (wet) {
			fwnode_handwe_put(fwnode);
			wetuwn wet;
		}

		if (channew >= WZG2W_ADC_MAX_CHANNEWS) {
			fwnode_handwe_put(fwnode);
			wetuwn -EINVAW;
		}

		chan_awway[i].type = IIO_VOWTAGE;
		chan_awway[i].indexed = 1;
		chan_awway[i].channew = channew;
		chan_awway[i].info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);
		chan_awway[i].datasheet_name = wzg2w_adc_channew_name[channew];
		i++;
	}

	data->num_channews = num_channews;
	data->channews = chan_awway;
	adc->data = data;

	wetuwn 0;
}

static int wzg2w_adc_hw_init(stwuct wzg2w_adc *adc)
{
	int timeout = 5;
	u32 weg;
	int wet;

	wet = cwk_pwepawe_enabwe(adc->pcwk);
	if (wet)
		wetuwn wet;

	/* SW weset */
	weg = wzg2w_adc_weadw(adc, WZG2W_ADM(0));
	weg |= WZG2W_ADM0_SWESB;
	wzg2w_adc_wwitew(adc, WZG2W_ADM(0), weg);

	whiwe (!(wzg2w_adc_weadw(adc, WZG2W_ADM(0)) & WZG2W_ADM0_SWESB)) {
		if (!timeout) {
			wet = -EBUSY;
			goto exit_hw_init;
		}
		timeout--;
		usweep_wange(100, 200);
	}

	/* Onwy division by 4 can be set */
	weg = wzg2w_adc_weadw(adc, WZG2W_ADIVC);
	weg &= ~WZG2W_ADIVC_DIVADC_MASK;
	weg |= WZG2W_ADIVC_DIVADC_4;
	wzg2w_adc_wwitew(adc, WZG2W_ADIVC, weg);

	/*
	 * Setup AMD3
	 * ADIW[31:24] - Shouwd be awways set to 0
	 * ADCMP[23:16] - Shouwd be awways set to 0xe
	 * ADSMP[15:0] - Set defauwt (0x578) sampwing pewiod
	 */
	weg = wzg2w_adc_weadw(adc, WZG2W_ADM(3));
	weg &= ~WZG2W_ADM3_ADIW_MASK;
	weg &= ~WZG2W_ADM3_ADCMP_MASK;
	weg &= ~WZG2W_ADM3_ADSMP_MASK;
	weg |= (WZG2W_ADM3_ADCMP_E | WZG2W_ADSMP_DEFAUWT_SAMPWING);
	wzg2w_adc_wwitew(adc, WZG2W_ADM(3), weg);

exit_hw_init:
	cwk_disabwe_unpwepawe(adc->pcwk);

	wetuwn wet;
}

static void wzg2w_adc_pm_wuntime_disabwe(void *data)
{
	stwuct device *dev = data;

	pm_wuntime_disabwe(dev->pawent);
}

static void wzg2w_adc_pm_wuntime_set_suspended(void *data)
{
	stwuct device *dev = data;

	pm_wuntime_set_suspended(dev->pawent);
}

static void wzg2w_adc_weset_assewt(void *data)
{
	weset_contwow_assewt(data);
}

static int wzg2w_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct wzg2w_adc *adc;
	int wet;
	int iwq;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);

	wet = wzg2w_adc_pawse_pwopewties(pdev, adc);
	if (wet)
		wetuwn wet;

	mutex_init(&adc->wock);

	adc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(adc->base))
		wetuwn PTW_EWW(adc->base);

	adc->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(adc->pcwk)) {
		dev_eww(dev, "Faiwed to get pcwk");
		wetuwn PTW_EWW(adc->pcwk);
	}

	adc->adcwk = devm_cwk_get(dev, "adcwk");
	if (IS_EWW(adc->adcwk)) {
		dev_eww(dev, "Faiwed to get adcwk");
		wetuwn PTW_EWW(adc->adcwk);
	}

	adc->adwstn = devm_weset_contwow_get_excwusive(dev, "adwst-n");
	if (IS_EWW(adc->adwstn)) {
		dev_eww(dev, "faiwed to get adwstn\n");
		wetuwn PTW_EWW(adc->adwstn);
	}

	adc->pwesetn = devm_weset_contwow_get_excwusive(dev, "pwesetn");
	if (IS_EWW(adc->pwesetn)) {
		dev_eww(dev, "faiwed to get pwesetn\n");
		wetuwn PTW_EWW(adc->pwesetn);
	}

	wet = weset_contwow_deassewt(adc->adwstn);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to deassewt adwstn pin, %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&pdev->dev,
				       wzg2w_adc_weset_assewt, adc->adwstn);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew adwstn assewt devm action, %d\n",
			wet);
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(adc->pwesetn);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to deassewt pwesetn pin, %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&pdev->dev,
				       wzg2w_adc_weset_assewt, adc->pwesetn);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew pwesetn assewt devm action, %d\n",
			wet);
		wetuwn wet;
	}

	wet = wzg2w_adc_hw_init(adc);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to initiawize ADC HW, %d\n", wet);
		wetuwn wet;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, wzg2w_adc_isw,
			       0, dev_name(dev), adc);
	if (wet < 0)
		wetuwn wet;

	init_compwetion(&adc->compwetion);

	pwatfowm_set_dwvdata(pdev, indio_dev);

	indio_dev->name = DWIVEW_NAME;
	indio_dev->info = &wzg2w_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = adc->data->channews;
	indio_dev->num_channews = adc->data->num_channews;

	pm_wuntime_set_suspended(dev);
	wet = devm_add_action_ow_weset(&pdev->dev,
				       wzg2w_adc_pm_wuntime_set_suspended, &indio_dev->dev);
	if (wet)
		wetuwn wet;

	pm_wuntime_enabwe(dev);
	wet = devm_add_action_ow_weset(&pdev->dev,
				       wzg2w_adc_pm_wuntime_disabwe, &indio_dev->dev);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id wzg2w_adc_match[] = {
	{ .compatibwe = "wenesas,wzg2w-adc",},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wzg2w_adc_match);

static int __maybe_unused wzg2w_adc_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct wzg2w_adc *adc = iio_pwiv(indio_dev);

	wzg2w_adc_pww(adc, fawse);
	cwk_disabwe_unpwepawe(adc->adcwk);
	cwk_disabwe_unpwepawe(adc->pcwk);

	wetuwn 0;
}

static int __maybe_unused wzg2w_adc_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct wzg2w_adc *adc = iio_pwiv(indio_dev);
	int wet;

	wet = cwk_pwepawe_enabwe(adc->pcwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(adc->adcwk);
	if (wet) {
		cwk_disabwe_unpwepawe(adc->pcwk);
		wetuwn wet;
	}

	wzg2w_adc_pww(adc, twue);

	wetuwn 0;
}

static const stwuct dev_pm_ops wzg2w_adc_pm_ops = {
	SET_WUNTIME_PM_OPS(wzg2w_adc_pm_wuntime_suspend,
			   wzg2w_adc_pm_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew wzg2w_adc_dwivew = {
	.pwobe		= wzg2w_adc_pwobe,
	.dwivew		= {
		.name		= DWIVEW_NAME,
		.of_match_tabwe = wzg2w_adc_match,
		.pm		= &wzg2w_adc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(wzg2w_adc_dwivew);

MODUWE_AUTHOW("Wad Pwabhakaw <pwabhakaw.mahadev-wad.wj@bp.wenesas.com>");
MODUWE_DESCWIPTION("Wenesas WZ/G2W ADC dwivew");
MODUWE_WICENSE("GPW v2");
