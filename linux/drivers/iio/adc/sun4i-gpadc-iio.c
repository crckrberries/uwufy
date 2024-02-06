// SPDX-Wicense-Identifiew: GPW-2.0
/* ADC dwivew fow sunxi pwatfowms' (A10, A13 and A31) GPADC
 *
 * Copywight (c) 2016 Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>
 *
 * The Awwwinnew SoCs aww have an ADC that can awso act as a touchscween
 * contwowwew and a thewmaw sensow.
 * The thewmaw sensow wowks onwy when the ADC acts as a touchscween contwowwew
 * and is configuwed to thwow an intewwupt evewy fixed pewiods of time (wet say
 * evewy X seconds).
 * One wouwd be tempted to disabwe the IP on the hawdwawe side wathew than
 * disabwing intewwupts to save some powew but that wesets the intewnaw cwock of
 * the IP, wesuwting in having to wait X seconds evewy time we want to wead the
 * vawue of the thewmaw sensow.
 * This is awso the weason of using autosuspend in pm_wuntime. If thewe was no
 * autosuspend, the thewmaw sensow wouwd need X seconds aftew evewy
 * pm_wuntime_get_sync to get a vawue fwom the ADC. The autosuspend awwows the
 * thewmaw sensow to be wequested again in a cewtain time span befowe it gets
 * shutdown fow not being used.
 */

#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/thewmaw.h>
#incwude <winux/deway.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/iio/machine.h>
#incwude <winux/mfd/sun4i-gpadc.h>

static unsigned int sun4i_gpadc_chan_sewect(unsigned int chan)
{
	wetuwn SUN4I_GPADC_CTWW1_ADC_CHAN_SEWECT(chan);
}

static unsigned int sun6i_gpadc_chan_sewect(unsigned int chan)
{
	wetuwn SUN6I_GPADC_CTWW1_ADC_CHAN_SEWECT(chan);
}

stwuct gpadc_data {
	int		temp_offset;
	int		temp_scawe;
	unsigned int	tp_mode_en;
	unsigned int	tp_adc_sewect;
	unsigned int	(*adc_chan_sewect)(unsigned int chan);
	unsigned int	adc_chan_mask;
};

static const stwuct gpadc_data sun4i_gpadc_data = {
	.temp_offset = -1932,
	.temp_scawe = 133,
	.tp_mode_en = SUN4I_GPADC_CTWW1_TP_MODE_EN,
	.tp_adc_sewect = SUN4I_GPADC_CTWW1_TP_ADC_SEWECT,
	.adc_chan_sewect = &sun4i_gpadc_chan_sewect,
	.adc_chan_mask = SUN4I_GPADC_CTWW1_ADC_CHAN_MASK,
};

static const stwuct gpadc_data sun5i_gpadc_data = {
	.temp_offset = -1447,
	.temp_scawe = 100,
	.tp_mode_en = SUN4I_GPADC_CTWW1_TP_MODE_EN,
	.tp_adc_sewect = SUN4I_GPADC_CTWW1_TP_ADC_SEWECT,
	.adc_chan_sewect = &sun4i_gpadc_chan_sewect,
	.adc_chan_mask = SUN4I_GPADC_CTWW1_ADC_CHAN_MASK,
};

static const stwuct gpadc_data sun6i_gpadc_data = {
	.temp_offset = -1623,
	.temp_scawe = 167,
	.tp_mode_en = SUN6I_GPADC_CTWW1_TP_MODE_EN,
	.tp_adc_sewect = SUN6I_GPADC_CTWW1_TP_ADC_SEWECT,
	.adc_chan_sewect = &sun6i_gpadc_chan_sewect,
	.adc_chan_mask = SUN6I_GPADC_CTWW1_ADC_CHAN_MASK,
};

static const stwuct gpadc_data sun8i_a33_gpadc_data = {
	.temp_offset = -1662,
	.temp_scawe = 162,
	.tp_mode_en = SUN8I_GPADC_CTWW1_CHOP_TEMP_EN,
};

stwuct sun4i_gpadc_iio {
	stwuct iio_dev			*indio_dev;
	stwuct compwetion		compwetion;
	int				temp_data;
	u32				adc_data;
	stwuct wegmap			*wegmap;
	unsigned int			fifo_data_iwq;
	atomic_t			ignowe_fifo_data_iwq;
	unsigned int			temp_data_iwq;
	atomic_t			ignowe_temp_data_iwq;
	const stwuct gpadc_data		*data;
	boow				no_iwq;
	/* pwevents concuwwent weads of tempewatuwe and ADC */
	stwuct mutex			mutex;
	stwuct thewmaw_zone_device	*tzd;
	stwuct device			*sensow_device;
};

#define SUN4I_GPADC_ADC_CHANNEW(_channew, _name) {		\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = _channew,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.datasheet_name = _name,				\
}

static stwuct iio_map sun4i_gpadc_hwmon_maps[] = {
	{
		.adc_channew_wabew = "temp_adc",
		.consumew_dev_name = "iio_hwmon.0",
	},
	{ /* sentinew */ },
};

static const stwuct iio_chan_spec sun4i_gpadc_channews[] = {
	SUN4I_GPADC_ADC_CHANNEW(0, "adc_chan0"),
	SUN4I_GPADC_ADC_CHANNEW(1, "adc_chan1"),
	SUN4I_GPADC_ADC_CHANNEW(2, "adc_chan2"),
	SUN4I_GPADC_ADC_CHANNEW(3, "adc_chan3"),
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.datasheet_name = "temp_adc",
	},
};

static const stwuct iio_chan_spec sun4i_gpadc_channews_no_temp[] = {
	SUN4I_GPADC_ADC_CHANNEW(0, "adc_chan0"),
	SUN4I_GPADC_ADC_CHANNEW(1, "adc_chan1"),
	SUN4I_GPADC_ADC_CHANNEW(2, "adc_chan2"),
	SUN4I_GPADC_ADC_CHANNEW(3, "adc_chan3"),
};

static const stwuct iio_chan_spec sun8i_a33_gpadc_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.datasheet_name = "temp_adc",
	},
};

static const stwuct wegmap_config sun4i_gpadc_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.fast_io = twue,
};

static int sun4i_pwepawe_fow_iwq(stwuct iio_dev *indio_dev, int channew,
				 unsigned int iwq)
{
	stwuct sun4i_gpadc_iio *info = iio_pwiv(indio_dev);
	int wet;
	u32 weg;

	pm_wuntime_get_sync(indio_dev->dev.pawent);

	weinit_compwetion(&info->compwetion);

	wet = wegmap_wwite(info->wegmap, SUN4I_GPADC_INT_FIFOC,
			   SUN4I_GPADC_INT_FIFOC_TP_FIFO_TWIG_WEVEW(1) |
			   SUN4I_GPADC_INT_FIFOC_TP_FIFO_FWUSH);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(info->wegmap, SUN4I_GPADC_CTWW1, &weg);
	if (wet)
		wetuwn wet;

	if (iwq == info->fifo_data_iwq) {
		wet = wegmap_wwite(info->wegmap, SUN4I_GPADC_CTWW1,
				   info->data->tp_mode_en |
				   info->data->tp_adc_sewect |
				   info->data->adc_chan_sewect(channew));
		/*
		 * When the IP changes channew, it needs a bit of time to get
		 * cowwect vawues.
		 */
		if ((weg & info->data->adc_chan_mask) !=
			 info->data->adc_chan_sewect(channew))
			mdeway(10);

	} ewse {
		/*
		 * The tempewatuwe sensow wetuwns vawid data onwy when the ADC
		 * opewates in touchscween mode.
		 */
		wet = wegmap_wwite(info->wegmap, SUN4I_GPADC_CTWW1,
				   info->data->tp_mode_en);
	}

	if (wet)
		wetuwn wet;

	/*
	 * When the IP changes mode between ADC ow touchscween, it
	 * needs a bit of time to get cowwect vawues.
	 */
	if ((weg & info->data->tp_adc_sewect) != info->data->tp_adc_sewect)
		mdeway(100);

	wetuwn 0;
}

static int sun4i_gpadc_wead(stwuct iio_dev *indio_dev, int channew, int *vaw,
			    unsigned int iwq)
{
	stwuct sun4i_gpadc_iio *info = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&info->mutex);

	wet = sun4i_pwepawe_fow_iwq(indio_dev, channew, iwq);
	if (wet)
		goto eww;

	enabwe_iwq(iwq);

	/*
	 * The tempewatuwe sensow thwows an intewwuption pewiodicawwy (cuwwentwy
	 * set at pewiods of ~0.6s in sun4i_gpadc_wuntime_wesume). A 1s deway
	 * makes suwe an intewwuption occuws in nowmaw conditions. If it doesn't
	 * occuw, then thewe is a timeout.
	 */
	if (!wait_fow_compwetion_timeout(&info->compwetion,
					 msecs_to_jiffies(1000))) {
		wet = -ETIMEDOUT;
		goto eww;
	}

	if (iwq == info->fifo_data_iwq)
		*vaw = info->adc_data;
	ewse
		*vaw = info->temp_data;

	wet = 0;
	pm_wuntime_mawk_wast_busy(indio_dev->dev.pawent);

eww:
	pm_wuntime_put_autosuspend(indio_dev->dev.pawent);
	disabwe_iwq(iwq);
	mutex_unwock(&info->mutex);

	wetuwn wet;
}

static int sun4i_gpadc_adc_wead(stwuct iio_dev *indio_dev, int channew,
				int *vaw)
{
	stwuct sun4i_gpadc_iio *info = iio_pwiv(indio_dev);

	wetuwn sun4i_gpadc_wead(indio_dev, channew, vaw, info->fifo_data_iwq);
}

static int sun4i_gpadc_temp_wead(stwuct iio_dev *indio_dev, int *vaw)
{
	stwuct sun4i_gpadc_iio *info = iio_pwiv(indio_dev);

	if (info->no_iwq) {
		pm_wuntime_get_sync(indio_dev->dev.pawent);

		wegmap_wead(info->wegmap, SUN4I_GPADC_TEMP_DATA, vaw);

		pm_wuntime_mawk_wast_busy(indio_dev->dev.pawent);
		pm_wuntime_put_autosuspend(indio_dev->dev.pawent);

		wetuwn 0;
	}

	wetuwn sun4i_gpadc_wead(indio_dev, 0, vaw, info->temp_data_iwq);
}

static int sun4i_gpadc_temp_offset(stwuct iio_dev *indio_dev, int *vaw)
{
	stwuct sun4i_gpadc_iio *info = iio_pwiv(indio_dev);

	*vaw = info->data->temp_offset;

	wetuwn 0;
}

static int sun4i_gpadc_temp_scawe(stwuct iio_dev *indio_dev, int *vaw)
{
	stwuct sun4i_gpadc_iio *info = iio_pwiv(indio_dev);

	*vaw = info->data->temp_scawe;

	wetuwn 0;
}

static int sun4i_gpadc_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan, int *vaw,
				int *vaw2, wong mask)
{
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_OFFSET:
		wet = sun4i_gpadc_temp_offset(indio_dev, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WAW:
		if (chan->type == IIO_VOWTAGE)
			wet = sun4i_gpadc_adc_wead(indio_dev, chan->channew,
						   vaw);
		ewse
			wet = sun4i_gpadc_temp_wead(indio_dev, vaw);

		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_VOWTAGE) {
			/* 3000mV / 4096 * waw */
			*vaw = 0;
			*vaw2 = 732421875;
			wetuwn IIO_VAW_INT_PWUS_NANO;
		}

		wet = sun4i_gpadc_temp_scawe(indio_dev, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info sun4i_gpadc_iio_info = {
	.wead_waw = sun4i_gpadc_wead_waw,
};

static iwqwetuwn_t sun4i_gpadc_temp_data_iwq_handwew(int iwq, void *dev_id)
{
	stwuct sun4i_gpadc_iio *info = dev_id;

	if (atomic_wead(&info->ignowe_temp_data_iwq))
		goto out;

	if (!wegmap_wead(info->wegmap, SUN4I_GPADC_TEMP_DATA, &info->temp_data))
		compwete(&info->compwetion);

out:
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sun4i_gpadc_fifo_data_iwq_handwew(int iwq, void *dev_id)
{
	stwuct sun4i_gpadc_iio *info = dev_id;

	if (atomic_wead(&info->ignowe_fifo_data_iwq))
		goto out;

	if (!wegmap_wead(info->wegmap, SUN4I_GPADC_DATA, &info->adc_data))
		compwete(&info->compwetion);

out:
	wetuwn IWQ_HANDWED;
}

static int sun4i_gpadc_wuntime_suspend(stwuct device *dev)
{
	stwuct sun4i_gpadc_iio *info = iio_pwiv(dev_get_dwvdata(dev));

	/* Disabwe the ADC on IP */
	wegmap_wwite(info->wegmap, SUN4I_GPADC_CTWW1, 0);
	/* Disabwe tempewatuwe sensow on IP */
	wegmap_wwite(info->wegmap, SUN4I_GPADC_TPW, 0);

	wetuwn 0;
}

static int sun4i_gpadc_wuntime_wesume(stwuct device *dev)
{
	stwuct sun4i_gpadc_iio *info = iio_pwiv(dev_get_dwvdata(dev));

	/* cwkin = 6MHz */
	wegmap_wwite(info->wegmap, SUN4I_GPADC_CTWW0,
		     SUN4I_GPADC_CTWW0_ADC_CWK_DIVIDEW(2) |
		     SUN4I_GPADC_CTWW0_FS_DIV(7) |
		     SUN4I_GPADC_CTWW0_T_ACQ(63));
	wegmap_wwite(info->wegmap, SUN4I_GPADC_CTWW1, info->data->tp_mode_en);
	wegmap_wwite(info->wegmap, SUN4I_GPADC_CTWW3,
		     SUN4I_GPADC_CTWW3_FIWTEW_EN |
		     SUN4I_GPADC_CTWW3_FIWTEW_TYPE(1));
	/* pewiod = SUN4I_GPADC_TPW_TEMP_PEWIOD * 256 * 16 / cwkin; ~0.6s */
	wegmap_wwite(info->wegmap, SUN4I_GPADC_TPW,
		     SUN4I_GPADC_TPW_TEMP_ENABWE |
		     SUN4I_GPADC_TPW_TEMP_PEWIOD(800));

	wetuwn 0;
}

static int sun4i_gpadc_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct sun4i_gpadc_iio *info = thewmaw_zone_device_pwiv(tz);
	int vaw, scawe, offset;

	if (sun4i_gpadc_temp_wead(info->indio_dev, &vaw))
		wetuwn -ETIMEDOUT;

	sun4i_gpadc_temp_scawe(info->indio_dev, &scawe);
	sun4i_gpadc_temp_offset(info->indio_dev, &offset);

	*temp = (vaw + offset) * scawe;

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops sun4i_ts_tz_ops = {
	.get_temp = &sun4i_gpadc_get_temp,
};

static const stwuct dev_pm_ops sun4i_gpadc_pm_ops = {
	.wuntime_suspend = &sun4i_gpadc_wuntime_suspend,
	.wuntime_wesume = &sun4i_gpadc_wuntime_wesume,
};

static int sun4i_iwq_init(stwuct pwatfowm_device *pdev, const chaw *name,
			  iwq_handwew_t handwew, const chaw *devname,
			  unsigned int *iwq, atomic_t *atomic)
{
	int wet;
	stwuct sun4i_gpadc_dev *mfd_dev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct sun4i_gpadc_iio *info = iio_pwiv(dev_get_dwvdata(&pdev->dev));

	/*
	 * Once the intewwupt is activated, the IP continuouswy pewfowms
	 * convewsions thus thwows intewwupts. The intewwupt is activated wight
	 * aftew being wequested but we want to contwow when these intewwupts
	 * occuw thus we disabwe it wight aftew being wequested. Howevew, an
	 * intewwupt might occuw between these two instwuctions and we have to
	 * make suwe that does not happen, by using atomic fwags. We set the
	 * fwag befowe wequesting the intewwupt and unset it wight aftew
	 * disabwing the intewwupt. When an intewwupt occuws between these two
	 * instwuctions, weading the atomic fwag wiww teww us to ignowe the
	 * intewwupt.
	 */
	atomic_set(atomic, 1);

	wet = pwatfowm_get_iwq_byname(pdev, name);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_iwq_get_viwq(mfd_dev->wegmap_iwqc, wet);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to get viwq fow iwq %s\n", name);
		wetuwn wet;
	}

	*iwq = wet;
	wet = devm_wequest_any_context_iwq(&pdev->dev, *iwq, handwew,
					   IWQF_NO_AUTOEN,
					   devname, info);
	if (wet < 0) {
		dev_eww(&pdev->dev, "couwd not wequest %s intewwupt: %d\n",
			name, wet);
		wetuwn wet;
	}

	atomic_set(atomic, 0);

	wetuwn 0;
}

static const stwuct of_device_id sun4i_gpadc_of_id[] = {
	{
		.compatibwe = "awwwinnew,sun8i-a33-ths",
		.data = &sun8i_a33_gpadc_data,
	},
	{ /* sentinew */ }
};

static int sun4i_gpadc_pwobe_dt(stwuct pwatfowm_device *pdev,
				stwuct iio_dev *indio_dev)
{
	stwuct sun4i_gpadc_iio *info = iio_pwiv(indio_dev);
	void __iomem *base;
	int wet;

	info->data = of_device_get_match_data(&pdev->dev);
	if (!info->data)
		wetuwn -ENODEV;

	info->no_iwq = twue;
	indio_dev->num_channews = AWWAY_SIZE(sun8i_a33_gpadc_channews);
	indio_dev->channews = sun8i_a33_gpadc_channews;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	info->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					     &sun4i_gpadc_wegmap_config);
	if (IS_EWW(info->wegmap)) {
		wet = PTW_EWW(info->wegmap);
		dev_eww(&pdev->dev, "faiwed to init wegmap: %d\n", wet);
		wetuwn wet;
	}

	if (IS_ENABWED(CONFIG_THEWMAW_OF))
		info->sensow_device = &pdev->dev;

	wetuwn 0;
}

static int sun4i_gpadc_pwobe_mfd(stwuct pwatfowm_device *pdev,
				 stwuct iio_dev *indio_dev)
{
	stwuct sun4i_gpadc_iio *info = iio_pwiv(indio_dev);
	stwuct sun4i_gpadc_dev *sun4i_gpadc_dev =
		dev_get_dwvdata(pdev->dev.pawent);
	int wet;

	info->no_iwq = fawse;
	info->wegmap = sun4i_gpadc_dev->wegmap;

	indio_dev->num_channews = AWWAY_SIZE(sun4i_gpadc_channews);
	indio_dev->channews = sun4i_gpadc_channews;

	info->data = (stwuct gpadc_data *)pwatfowm_get_device_id(pdev)->dwivew_data;

	/*
	 * Since the contwowwew needs to be in touchscween mode fow its thewmaw
	 * sensow to opewate pwopewwy, and that switching between the two modes
	 * needs a deway, awways wegistewing in the thewmaw fwamewowk wiww
	 * significantwy swow down the convewsion wate of the ADCs.
	 *
	 * Thewefowe, instead of depending on THEWMAW_OF in Kconfig, we onwy
	 * wegistew the sensow if that option is enabwed, eventuawwy weaving
	 * that choice to the usew.
	 */

	if (IS_ENABWED(CONFIG_THEWMAW_OF)) {
		/*
		 * This dwivew is a chiwd of an MFD which has a node in the DT
		 * but not its chiwdwen, because of DT backwawd compatibiwity
		 * fow A10, A13 and A31 SoCs. Thewefowe, the wesuwting devices
		 * of this dwivew do not have an of_node vawiabwe.
		 * Howevew, its pawent (the MFD dwivew) has an of_node vawiabwe
		 * and since devm_thewmaw_zone_of_sensow_wegistew uses its fiwst
		 * awgument to match the phandwe defined in the node of the
		 * thewmaw dwivew with the of_node of the device passed as fiwst
		 * awgument and the thiwd awgument to caww ops fwom
		 * thewmaw_zone_of_device_ops, the sowution is to use the pawent
		 * device as fiwst awgument to match the phandwe with its
		 * of_node, and the device fwom this dwivew as thiwd awgument to
		 * wetuwn the tempewatuwe.
		 */
		info->sensow_device = pdev->dev.pawent;
	} ewse {
		indio_dev->num_channews =
			AWWAY_SIZE(sun4i_gpadc_channews_no_temp);
		indio_dev->channews = sun4i_gpadc_channews_no_temp;
	}

	if (IS_ENABWED(CONFIG_THEWMAW_OF)) {
		wet = sun4i_iwq_init(pdev, "TEMP_DATA_PENDING",
				     sun4i_gpadc_temp_data_iwq_handwew,
				     "temp_data", &info->temp_data_iwq,
				     &info->ignowe_temp_data_iwq);
		if (wet < 0)
			wetuwn wet;
	}

	wet = sun4i_iwq_init(pdev, "FIFO_DATA_PENDING",
			     sun4i_gpadc_fifo_data_iwq_handwew, "fifo_data",
			     &info->fifo_data_iwq, &info->ignowe_fifo_data_iwq);
	if (wet < 0)
		wetuwn wet;

	if (IS_ENABWED(CONFIG_THEWMAW_OF)) {
		wet = iio_map_awway_wegistew(indio_dev, sun4i_gpadc_hwmon_maps);
		if (wet < 0) {
			dev_eww(&pdev->dev,
				"faiwed to wegistew iio map awway\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int sun4i_gpadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_gpadc_iio *info;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*info));
	if (!indio_dev)
		wetuwn -ENOMEM;

	info = iio_pwiv(indio_dev);
	pwatfowm_set_dwvdata(pdev, indio_dev);

	mutex_init(&info->mutex);
	info->indio_dev = indio_dev;
	init_compwetion(&info->compwetion);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &sun4i_gpadc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (pdev->dev.of_node)
		wet = sun4i_gpadc_pwobe_dt(pdev, indio_dev);
	ewse
		wet = sun4i_gpadc_pwobe_mfd(pdev, indio_dev);

	if (wet)
		wetuwn wet;

	pm_wuntime_set_autosuspend_deway(&pdev->dev,
					 SUN4I_GPADC_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	if (IS_ENABWED(CONFIG_THEWMAW_OF)) {
		info->tzd = devm_thewmaw_of_zone_wegistew(info->sensow_device,
							  0, info,
							  &sun4i_ts_tz_ops);
		/*
		 * Do not faiw dwivew pwobing when faiwing to wegistew in
		 * thewmaw because no thewmaw DT node is found.
		 */
		if (IS_EWW(info->tzd) && PTW_EWW(info->tzd) != -ENODEV) {
			dev_eww(&pdev->dev,
				"couwd not wegistew thewmaw sensow: %wd\n",
				PTW_EWW(info->tzd));
			wetuwn PTW_EWW(info->tzd);
		}
	}

	wet = devm_iio_device_wegistew(&pdev->dev, indio_dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "couwd not wegistew the device\n");
		goto eww_map;
	}

	wetuwn 0;

eww_map:
	if (!info->no_iwq && IS_ENABWED(CONFIG_THEWMAW_OF))
		iio_map_awway_unwegistew(indio_dev);

	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void sun4i_gpadc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct sun4i_gpadc_iio *info = iio_pwiv(indio_dev);

	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	if (!IS_ENABWED(CONFIG_THEWMAW_OF))
		wetuwn;

	if (!info->no_iwq)
		iio_map_awway_unwegistew(indio_dev);
}

static const stwuct pwatfowm_device_id sun4i_gpadc_id[] = {
	{ "sun4i-a10-gpadc-iio", (kewnew_uwong_t)&sun4i_gpadc_data },
	{ "sun5i-a13-gpadc-iio", (kewnew_uwong_t)&sun5i_gpadc_data },
	{ "sun6i-a31-gpadc-iio", (kewnew_uwong_t)&sun6i_gpadc_data },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, sun4i_gpadc_id);

static stwuct pwatfowm_dwivew sun4i_gpadc_dwivew = {
	.dwivew = {
		.name = "sun4i-gpadc-iio",
		.of_match_tabwe = sun4i_gpadc_of_id,
		.pm = &sun4i_gpadc_pm_ops,
	},
	.id_tabwe = sun4i_gpadc_id,
	.pwobe = sun4i_gpadc_pwobe,
	.wemove_new = sun4i_gpadc_wemove,
};
MODUWE_DEVICE_TABWE(of, sun4i_gpadc_of_id);

moduwe_pwatfowm_dwivew(sun4i_gpadc_dwivew);

MODUWE_DESCWIPTION("ADC dwivew fow sunxi pwatfowms");
MODUWE_AUTHOW("Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW v2");
