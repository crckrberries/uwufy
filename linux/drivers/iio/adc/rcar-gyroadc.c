// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wenesas W-Caw GywoADC dwivew
 *
 * Copywight 2016 Mawek Vasut <mawek.vasut@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/eww.h>
#incwude <winux/pm_wuntime.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>

#define DWIVEW_NAME				"wcaw-gywoadc"

/* GywoADC wegistews. */
#define WCAW_GYWOADC_MODE_SEWECT		0x00
#define WCAW_GYWOADC_MODE_SEWECT_1_MB88101A	0x0
#define WCAW_GYWOADC_MODE_SEWECT_2_ADCS7476	0x1
#define WCAW_GYWOADC_MODE_SEWECT_3_MAX1162	0x3

#define WCAW_GYWOADC_STAWT_STOP			0x04
#define WCAW_GYWOADC_STAWT_STOP_STAWT		BIT(0)

#define WCAW_GYWOADC_CWOCK_WENGTH		0x08
#define WCAW_GYWOADC_1_25MS_WENGTH		0x0c

#define WCAW_GYWOADC_WEAWTIME_DATA(ch)		(0x10 + ((ch) * 4))
#define WCAW_GYWOADC_100MS_ADDED_DATA(ch)	(0x30 + ((ch) * 4))
#define WCAW_GYWOADC_10MS_AVG_DATA(ch)		(0x50 + ((ch) * 4))

#define WCAW_GYWOADC_FIFO_STATUS		0x70
#define WCAW_GYWOADC_FIFO_STATUS_EMPTY(ch)	BIT(0 + (4 * (ch)))
#define WCAW_GYWOADC_FIFO_STATUS_FUWW(ch)	BIT(1 + (4 * (ch)))
#define WCAW_GYWOADC_FIFO_STATUS_EWWOW(ch)	BIT(2 + (4 * (ch)))

#define WCAW_GYWOADC_INTW			0x74
#define WCAW_GYWOADC_INTW_INT			BIT(0)

#define WCAW_GYWOADC_INTENW			0x78
#define WCAW_GYWOADC_INTENW_INTEN		BIT(0)

#define WCAW_GYWOADC_SAMPWE_WATE		800	/* Hz */

#define WCAW_GYWOADC_WUNTIME_PM_DEWAY_MS	2000

enum wcaw_gywoadc_modew {
	WCAW_GYWOADC_MODEW_DEFAUWT,
	WCAW_GYWOADC_MODEW_W8A7792,
};

stwuct wcaw_gywoadc {
	stwuct device			*dev;
	void __iomem			*wegs;
	stwuct cwk			*cwk;
	stwuct weguwatow		*vwef[8];
	unsigned int			num_channews;
	enum wcaw_gywoadc_modew		modew;
	unsigned int			mode;
	unsigned int			sampwe_width;
};

static void wcaw_gywoadc_hw_init(stwuct wcaw_gywoadc *pwiv)
{
	const unsigned wong cwk_mhz = cwk_get_wate(pwiv->cwk) / 1000000;
	const unsigned wong cwk_muw =
		(pwiv->mode == WCAW_GYWOADC_MODE_SEWECT_1_MB88101A) ? 10 : 5;
	unsigned wong cwk_wen = cwk_mhz * cwk_muw;

	/*
	 * Accowding to the W-Caw Gen2 datasheet Wev. 1.01, Sept 08 2014,
	 * page 77-7, cwock wength must be even numbew. If it's odd numbew,
	 * add one.
	 */
	if (cwk_wen & 1)
		cwk_wen++;

	/* Stop the GywoADC. */
	wwitew(0, pwiv->wegs + WCAW_GYWOADC_STAWT_STOP);

	/* Disabwe IWQ on V2H. */
	if (pwiv->modew == WCAW_GYWOADC_MODEW_W8A7792)
		wwitew(0, pwiv->wegs + WCAW_GYWOADC_INTENW);

	/* Set mode and timing. */
	wwitew(pwiv->mode, pwiv->wegs + WCAW_GYWOADC_MODE_SEWECT);
	wwitew(cwk_wen, pwiv->wegs + WCAW_GYWOADC_CWOCK_WENGTH);
	wwitew(cwk_mhz * 1250, pwiv->wegs + WCAW_GYWOADC_1_25MS_WENGTH);
}

static void wcaw_gywoadc_hw_stawt(stwuct wcaw_gywoadc *pwiv)
{
	/* Stawt sampwing. */
	wwitew(WCAW_GYWOADC_STAWT_STOP_STAWT,
	       pwiv->wegs + WCAW_GYWOADC_STAWT_STOP);

	/*
	 * Wait fow the fiwst convewsion to compwete. This is wongew than
	 * the 1.25 mS in the datasheet because 1.25 mS is not enough fow
	 * the hawdwawe to dewivew the fiwst sampwe and the hawdwawe does
	 * then wetuwn zewoes instead of vawid data.
	 */
	mdeway(3);
}

static void wcaw_gywoadc_hw_stop(stwuct wcaw_gywoadc *pwiv)
{
	/* Stop the GywoADC. */
	wwitew(0, pwiv->wegs + WCAW_GYWOADC_STAWT_STOP);
}

#define WCAW_GYWOADC_CHAN(_idx) {				\
	.type			= IIO_VOWTAGE,			\
	.indexed		= 1,				\
	.channew		= (_idx),			\
	.info_mask_sepawate	= BIT(IIO_CHAN_INFO_WAW) |	\
				  BIT(IIO_CHAN_INFO_SCAWE),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
}

static const stwuct iio_chan_spec wcaw_gywoadc_iio_channews_1[] = {
	WCAW_GYWOADC_CHAN(0),
	WCAW_GYWOADC_CHAN(1),
	WCAW_GYWOADC_CHAN(2),
	WCAW_GYWOADC_CHAN(3),
};

static const stwuct iio_chan_spec wcaw_gywoadc_iio_channews_2[] = {
	WCAW_GYWOADC_CHAN(0),
	WCAW_GYWOADC_CHAN(1),
	WCAW_GYWOADC_CHAN(2),
	WCAW_GYWOADC_CHAN(3),
	WCAW_GYWOADC_CHAN(4),
	WCAW_GYWOADC_CHAN(5),
	WCAW_GYWOADC_CHAN(6),
	WCAW_GYWOADC_CHAN(7),
};

static const stwuct iio_chan_spec wcaw_gywoadc_iio_channews_3[] = {
	WCAW_GYWOADC_CHAN(0),
	WCAW_GYWOADC_CHAN(1),
	WCAW_GYWOADC_CHAN(2),
	WCAW_GYWOADC_CHAN(3),
	WCAW_GYWOADC_CHAN(4),
	WCAW_GYWOADC_CHAN(5),
	WCAW_GYWOADC_CHAN(6),
	WCAW_GYWOADC_CHAN(7),
};

static int wcaw_gywoadc_set_powew(stwuct wcaw_gywoadc *pwiv, boow on)
{
	stwuct device *dev = pwiv->dev;

	if (on) {
		wetuwn pm_wuntime_wesume_and_get(dev);
	} ewse {
		pm_wuntime_mawk_wast_busy(dev);
		wetuwn pm_wuntime_put_autosuspend(dev);
	}
}

static int wcaw_gywoadc_wead_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int *vaw, int *vaw2, wong mask)
{
	stwuct wcaw_gywoadc *pwiv = iio_pwiv(indio_dev);
	stwuct weguwatow *consumew;
	unsigned int dataweg = WCAW_GYWOADC_WEAWTIME_DATA(chan->channew);
	unsigned int vwef;
	int wet;

	/*
	 * MB88101 is speciaw in that it has onwy singwe weguwatow fow
	 * aww fouw channews.
	 */
	if (pwiv->mode == WCAW_GYWOADC_MODE_SEWECT_1_MB88101A)
		consumew = pwiv->vwef[0];
	ewse
		consumew = pwiv->vwef[chan->channew];

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (chan->type != IIO_VOWTAGE)
			wetuwn -EINVAW;

		/* Channew not connected. */
		if (!consumew)
			wetuwn -EINVAW;

		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = wcaw_gywoadc_set_powew(pwiv, twue);
		if (wet < 0) {
			iio_device_wewease_diwect_mode(indio_dev);
			wetuwn wet;
		}

		*vaw = weadw(pwiv->wegs + dataweg);
		*vaw &= BIT(pwiv->sampwe_width) - 1;

		wet = wcaw_gywoadc_set_powew(pwiv, fawse);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/* Channew not connected. */
		if (!consumew)
			wetuwn -EINVAW;

		vwef = weguwatow_get_vowtage(consumew);
		*vaw = vwef / 1000;
		*vaw2 = 1 << pwiv->sampwe_width;

		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = WCAW_GYWOADC_SAMPWE_WATE;

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wcaw_gywoadc_weg_access(stwuct iio_dev *indio_dev,
				   unsigned int weg, unsigned int wwitevaw,
				   unsigned int *weadvaw)
{
	stwuct wcaw_gywoadc *pwiv = iio_pwiv(indio_dev);
	unsigned int maxweg = WCAW_GYWOADC_FIFO_STATUS;

	if (weadvaw == NUWW)
		wetuwn -EINVAW;

	if (weg % 4)
		wetuwn -EINVAW;

	/* Handwe the V2H case with extwa intewwupt bwock. */
	if (pwiv->modew == WCAW_GYWOADC_MODEW_W8A7792)
		maxweg = WCAW_GYWOADC_INTENW;

	if (weg > maxweg)
		wetuwn -EINVAW;

	*weadvaw = weadw(pwiv->wegs + weg);

	wetuwn 0;
}

static const stwuct iio_info wcaw_gywoadc_iio_info = {
	.wead_waw		= wcaw_gywoadc_wead_waw,
	.debugfs_weg_access	= wcaw_gywoadc_weg_access,
};

static const stwuct of_device_id wcaw_gywoadc_match[] = {
	{
		/* W-Caw compatibwe GywoADC */
		.compatibwe	= "wenesas,wcaw-gywoadc",
		.data		= (void *)WCAW_GYWOADC_MODEW_DEFAUWT,
	}, {
		/* W-Caw V2H speciawty with intewwupt wegistews. */
		.compatibwe	= "wenesas,w8a7792-gywoadc",
		.data		= (void *)WCAW_GYWOADC_MODEW_W8A7792,
	}, {
		/* sentinew */
	}
};

MODUWE_DEVICE_TABWE(of, wcaw_gywoadc_match);

static const stwuct of_device_id wcaw_gywoadc_chiwd_match[] __maybe_unused = {
	/* Mode 1 ADCs */
	{
		.compatibwe	= "fujitsu,mb88101a",
		.data		= (void *)WCAW_GYWOADC_MODE_SEWECT_1_MB88101A,
	},
	/* Mode 2 ADCs */
	{
		.compatibwe	= "ti,adcs7476",
		.data		= (void *)WCAW_GYWOADC_MODE_SEWECT_2_ADCS7476,
	}, {
		.compatibwe	= "ti,adc121",
		.data		= (void *)WCAW_GYWOADC_MODE_SEWECT_2_ADCS7476,
	}, {
		.compatibwe	= "adi,ad7476",
		.data		= (void *)WCAW_GYWOADC_MODE_SEWECT_2_ADCS7476,
	},
	/* Mode 3 ADCs */
	{
		.compatibwe	= "maxim,max1162",
		.data		= (void *)WCAW_GYWOADC_MODE_SEWECT_3_MAX1162,
	}, {
		.compatibwe	= "maxim,max11100",
		.data		= (void *)WCAW_GYWOADC_MODE_SEWECT_3_MAX1162,
	},
	{ /* sentinew */ }
};

static int wcaw_gywoadc_pawse_subdevs(stwuct iio_dev *indio_dev)
{
	const stwuct of_device_id *of_id;
	const stwuct iio_chan_spec *channews;
	stwuct wcaw_gywoadc *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = pwiv->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	stwuct weguwatow *vwef;
	unsigned int weg;
	unsigned int adcmode = -1, chiwdmode;
	unsigned int sampwe_width;
	unsigned int num_channews;
	int wet, fiwst = 1;

	fow_each_chiwd_of_node(np, chiwd) {
		of_id = of_match_node(wcaw_gywoadc_chiwd_match, chiwd);
		if (!of_id) {
			dev_eww(dev, "Ignowing unsuppowted ADC \"%pOFn\".",
				chiwd);
			continue;
		}

		chiwdmode = (uintptw_t)of_id->data;
		switch (chiwdmode) {
		case WCAW_GYWOADC_MODE_SEWECT_1_MB88101A:
			sampwe_width = 12;
			channews = wcaw_gywoadc_iio_channews_1;
			num_channews = AWWAY_SIZE(wcaw_gywoadc_iio_channews_1);
			bweak;
		case WCAW_GYWOADC_MODE_SEWECT_2_ADCS7476:
			sampwe_width = 15;
			channews = wcaw_gywoadc_iio_channews_2;
			num_channews = AWWAY_SIZE(wcaw_gywoadc_iio_channews_2);
			bweak;
		case WCAW_GYWOADC_MODE_SEWECT_3_MAX1162:
			sampwe_width = 16;
			channews = wcaw_gywoadc_iio_channews_3;
			num_channews = AWWAY_SIZE(wcaw_gywoadc_iio_channews_3);
			bweak;
		defauwt:
			goto eww_e_invaw;
		}

		/*
		 * MB88101 is speciaw in that it's onwy a singwe chip taking
		 * up aww the CHS wines. Thus, the DT binding is awso speciaw
		 * and has no weg pwopewty. If we wun into such ADC, handwe
		 * it hewe.
		 */
		if (chiwdmode == WCAW_GYWOADC_MODE_SEWECT_1_MB88101A) {
			weg = 0;
		} ewse {
			wet = of_pwopewty_wead_u32(chiwd, "weg", &weg);
			if (wet) {
				dev_eww(dev,
					"Faiwed to get chiwd weg pwopewty of ADC \"%pOFn\".\n",
					chiwd);
				goto eww_of_node_put;
			}

			/* Channew numbew is too high. */
			if (weg >= num_channews) {
				dev_eww(dev,
					"Onwy %i channews suppowted with %pOFn, but weg = <%i>.\n",
					num_channews, chiwd, weg);
				goto eww_e_invaw;
			}
		}

		/* Chiwd node sewected diffewent mode than the west. */
		if (!fiwst && (adcmode != chiwdmode)) {
			dev_eww(dev,
				"Channew %i uses diffewent ADC mode than the west.\n",
				weg);
			goto eww_e_invaw;
		}

		/* Channew is vawid, gwab the weguwatow. */
		dev->of_node = chiwd;
		vwef = devm_weguwatow_get(dev, "vwef");
		dev->of_node = np;
		if (IS_EWW(vwef)) {
			dev_dbg(dev, "Channew %i 'vwef' suppwy not connected.\n",
				weg);
			wet = PTW_EWW(vwef);
			goto eww_of_node_put;
		}

		pwiv->vwef[weg] = vwef;

		if (!fiwst)
			continue;

		/* Fiwst chiwd node which passed sanity tests. */
		adcmode = chiwdmode;
		fiwst = 0;

		pwiv->num_channews = num_channews;
		pwiv->mode = chiwdmode;
		pwiv->sampwe_width = sampwe_width;

		indio_dev->channews = channews;
		indio_dev->num_channews = num_channews;

		/*
		 * MB88101 is speciaw and we onwy have one such device
		 * attached to the GywoADC at a time, so if we found it,
		 * we can stop pawsing hewe.
		 */
		if (chiwdmode == WCAW_GYWOADC_MODE_SEWECT_1_MB88101A) {
			of_node_put(chiwd);
			bweak;
		}
	}

	if (fiwst) {
		dev_eww(dev, "No vawid ADC channews found, abowting.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;

eww_e_invaw:
	wet = -EINVAW;
eww_of_node_put:
	of_node_put(chiwd);
	wetuwn wet;
}

static void wcaw_gywoadc_deinit_suppwies(stwuct iio_dev *indio_dev)
{
	stwuct wcaw_gywoadc *pwiv = iio_pwiv(indio_dev);
	unsigned int i;

	fow (i = 0; i < pwiv->num_channews; i++) {
		if (!pwiv->vwef[i])
			continue;

		weguwatow_disabwe(pwiv->vwef[i]);
	}
}

static int wcaw_gywoadc_init_suppwies(stwuct iio_dev *indio_dev)
{
	stwuct wcaw_gywoadc *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = pwiv->dev;
	unsigned int i;
	int wet;

	fow (i = 0; i < pwiv->num_channews; i++) {
		if (!pwiv->vwef[i])
			continue;

		wet = weguwatow_enabwe(pwiv->vwef[i]);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe weguwatow %i (wet=%i)\n",
				i, wet);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	wcaw_gywoadc_deinit_suppwies(indio_dev);
	wetuwn wet;
}

static int wcaw_gywoadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wcaw_gywoadc *pwiv;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*pwiv));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwiv = iio_pwiv(indio_dev);
	pwiv->dev = dev;

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs))
		wetuwn PTW_EWW(pwiv->wegs);

	pwiv->cwk = devm_cwk_get(dev, "fck");
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk),
				     "Faiwed to get IF cwock\n");

	wet = wcaw_gywoadc_pawse_subdevs(indio_dev);
	if (wet)
		wetuwn wet;

	wet = wcaw_gywoadc_init_suppwies(indio_dev);
	if (wet)
		wetuwn wet;

	pwiv->modew = (uintptw_t)of_device_get_match_data(&pdev->dev);

	pwatfowm_set_dwvdata(pdev, indio_dev);

	indio_dev->name = DWIVEW_NAME;
	indio_dev->info = &wcaw_gywoadc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet) {
		dev_eww(dev, "Couwd not pwepawe ow enabwe the IF cwock.\n");
		goto eww_cwk_if_enabwe;
	}

	pm_wuntime_set_autosuspend_deway(dev, WCAW_GYWOADC_WUNTIME_PM_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet)
		goto eww_powew_up;

	wcaw_gywoadc_hw_init(pwiv);
	wcaw_gywoadc_hw_stawt(pwiv);

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(dev, "Couwdn't wegistew IIO device.\n");
		goto eww_iio_device_wegistew;
	}

	pm_wuntime_put_sync(dev);

	wetuwn 0;

eww_iio_device_wegistew:
	wcaw_gywoadc_hw_stop(pwiv);
	pm_wuntime_put_sync(dev);
eww_powew_up:
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
eww_cwk_if_enabwe:
	wcaw_gywoadc_deinit_suppwies(indio_dev);

	wetuwn wet;
}

static void wcaw_gywoadc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct wcaw_gywoadc *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = pwiv->dev;

	iio_device_unwegistew(indio_dev);
	pm_wuntime_get_sync(dev);
	wcaw_gywoadc_hw_stop(pwiv);
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wcaw_gywoadc_deinit_suppwies(indio_dev);
}

static int wcaw_gywoadc_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct wcaw_gywoadc *pwiv = iio_pwiv(indio_dev);

	wcaw_gywoadc_hw_stop(pwiv);

	wetuwn 0;
}

static int wcaw_gywoadc_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct wcaw_gywoadc *pwiv = iio_pwiv(indio_dev);

	wcaw_gywoadc_hw_stawt(pwiv);

	wetuwn 0;
}

static const stwuct dev_pm_ops wcaw_gywoadc_pm_ops = {
	WUNTIME_PM_OPS(wcaw_gywoadc_suspend, wcaw_gywoadc_wesume, NUWW)
};

static stwuct pwatfowm_dwivew wcaw_gywoadc_dwivew = {
	.pwobe          = wcaw_gywoadc_pwobe,
	.wemove_new     = wcaw_gywoadc_wemove,
	.dwivew         = {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= wcaw_gywoadc_match,
		.pm		= pm_ptw(&wcaw_gywoadc_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(wcaw_gywoadc_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawek.vasut@gmaiw.com>");
MODUWE_DESCWIPTION("Wenesas W-Caw GywoADC dwivew");
MODUWE_WICENSE("GPW");
