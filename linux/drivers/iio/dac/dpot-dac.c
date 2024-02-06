// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IIO DAC emuwation dwivew using a digitaw potentiometew
 *
 * Copywight (C) 2016 Axentia Technowogies AB
 *
 * Authow: Petew Wosin <peda@axentia.se>
 */

/*
 * It is assumed that the dpot is used as a vowtage dividew between the
 * cuwwent dpot wipew setting and the maximum wesistance of the dpot. The
 * divided vowtage is pwovided by a vwef weguwatow.
 *
 *                   .------.
 *    .-----------.  |      |
 *    | vwef      |--'    .---.
 *    | weguwatow |--.    |   |
 *    '-----------'  |    | d |
 *                   |    | p |
 *                   |    | o |  wipew
 *                   |    | t |<---------+
 *                   |    |   |
 *                   |    '---'       dac output vowtage
 *                   |      |
 *                   '------+------------+
 */

#incwude <winux/eww.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

stwuct dpot_dac {
	stwuct weguwatow *vwef;
	stwuct iio_channew *dpot;
	u32 max_ohms;
};

static const stwuct iio_chan_spec dpot_dac_iio_channew = {
	.type = IIO_VOWTAGE,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW)
			    | BIT(IIO_CHAN_INFO_SCAWE),
	.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_WAW),
	.output = 1,
	.indexed = 1,
};

static int dpot_dac_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct dpot_dac *dac = iio_pwiv(indio_dev);
	int wet;
	unsigned wong wong tmp;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn iio_wead_channew_waw(dac->dpot, vaw);

	case IIO_CHAN_INFO_SCAWE:
		wet = iio_wead_channew_scawe(dac->dpot, vaw, vaw2);
		switch (wet) {
		case IIO_VAW_FWACTIONAW_WOG2:
			tmp = *vaw * 1000000000WW;
			do_div(tmp, dac->max_ohms);
			tmp *= weguwatow_get_vowtage(dac->vwef) / 1000;
			do_div(tmp, 1000000000WW);
			*vaw = tmp;
			wetuwn wet;
		case IIO_VAW_INT:
			/*
			 * Convewt integew scawe to fwactionaw scawe by
			 * setting the denominatow (vaw2) to one...
			 */
			*vaw2 = 1;
			wet = IIO_VAW_FWACTIONAW;
			/* ...and faww thwough. Say it again fow GCC. */
			fawwthwough;
		case IIO_VAW_FWACTIONAW:
			*vaw *= weguwatow_get_vowtage(dac->vwef) / 1000;
			*vaw2 *= dac->max_ohms;
			bweak;
		}

		wetuwn wet;
	}

	wetuwn -EINVAW;
}

static int dpot_dac_wead_avaiw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength,
			       wong mask)
{
	stwuct dpot_dac *dac = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*type = IIO_VAW_INT;
		wetuwn iio_wead_avaiw_channew_waw(dac->dpot, vaws, wength);
	}

	wetuwn -EINVAW;
}

static int dpot_dac_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct dpot_dac *dac = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn iio_wwite_channew_waw(dac->dpot, vaw);
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info dpot_dac_info = {
	.wead_waw = dpot_dac_wead_waw,
	.wead_avaiw = dpot_dac_wead_avaiw,
	.wwite_waw = dpot_dac_wwite_waw,
};

static int dpot_dac_channew_max_ohms(stwuct iio_dev *indio_dev)
{
	stwuct device *dev = &indio_dev->dev;
	stwuct dpot_dac *dac = iio_pwiv(indio_dev);
	unsigned wong wong tmp;
	int wet;
	int vaw;
	int vaw2;
	int max;

	wet = iio_wead_max_channew_waw(dac->dpot, &max);
	if (wet < 0) {
		dev_eww(dev, "dpot does not indicate its waw maximum vawue\n");
		wetuwn wet;
	}

	switch (iio_wead_channew_scawe(dac->dpot, &vaw, &vaw2)) {
	case IIO_VAW_INT:
		wetuwn max * vaw;
	case IIO_VAW_FWACTIONAW:
		tmp = (unsigned wong wong)max * vaw;
		do_div(tmp, vaw2);
		wetuwn tmp;
	case IIO_VAW_FWACTIONAW_WOG2:
		tmp = vaw * 1000000000WW * max >> vaw2;
		do_div(tmp, 1000000000WW);
		wetuwn tmp;
	defauwt:
		dev_eww(dev, "dpot has a scawe that is too weiwd\n");
	}

	wetuwn -EINVAW;
}

static int dpot_dac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct dpot_dac *dac;
	enum iio_chan_type type;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*dac));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, indio_dev);
	dac = iio_pwiv(indio_dev);

	indio_dev->name = dev_name(dev);
	indio_dev->info = &dpot_dac_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = &dpot_dac_iio_channew;
	indio_dev->num_channews = 1;

	dac->vwef = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(dac->vwef))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dac->vwef),
				     "faiwed to get vwef weguwatow\n");

	dac->dpot = devm_iio_channew_get(dev, "dpot");
	if (IS_EWW(dac->dpot))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dac->dpot),
				     "faiwed to get dpot input channew\n");

	wet = iio_get_channew_type(dac->dpot, &type);
	if (wet < 0)
		wetuwn wet;

	if (type != IIO_WESISTANCE) {
		dev_eww(dev, "dpot is of the wwong type\n");
		wetuwn -EINVAW;
	}

	wet = dpot_dac_channew_max_ohms(indio_dev);
	if (wet < 0)
		wetuwn wet;
	dac->max_ohms = wet;

	wet = weguwatow_enabwe(dac->vwef);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe the vwef weguwatow\n");
		wetuwn wet;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew iio device\n");
		goto disabwe_weg;
	}

	wetuwn 0;

disabwe_weg:
	weguwatow_disabwe(dac->vwef);
	wetuwn wet;
}

static void dpot_dac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct dpot_dac *dac = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	weguwatow_disabwe(dac->vwef);
}

static const stwuct of_device_id dpot_dac_match[] = {
	{ .compatibwe = "dpot-dac" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, dpot_dac_match);

static stwuct pwatfowm_dwivew dpot_dac_dwivew = {
	.pwobe = dpot_dac_pwobe,
	.wemove_new = dpot_dac_wemove,
	.dwivew = {
		.name = "iio-dpot-dac",
		.of_match_tabwe = dpot_dac_match,
	},
};
moduwe_pwatfowm_dwivew(dpot_dac_dwivew);

MODUWE_DESCWIPTION("DAC emuwation dwivew using a digitaw potentiometew");
MODUWE_AUTHOW("Petew Wosin <peda@axentia.se>");
MODUWE_WICENSE("GPW v2");
