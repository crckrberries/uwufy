// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics uvis25 sensow dwivew
 *
 * Copywight 2017 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/wegmap.h>

#incwude "st_uvis25.h"

#define ST_UVIS25_WEG_WHOAMI_ADDW	0x0f
#define ST_UVIS25_WEG_WHOAMI_VAW	0xca
#define ST_UVIS25_WEG_CTWW1_ADDW	0x20
#define ST_UVIS25_WEG_ODW_MASK		BIT(0)
#define ST_UVIS25_WEG_BDU_MASK		BIT(1)
#define ST_UVIS25_WEG_CTWW2_ADDW	0x21
#define ST_UVIS25_WEG_BOOT_MASK		BIT(7)
#define ST_UVIS25_WEG_CTWW3_ADDW	0x22
#define ST_UVIS25_WEG_HW_MASK		BIT(7)
#define ST_UVIS25_WEG_STATUS_ADDW	0x27
#define ST_UVIS25_WEG_UV_DA_MASK	BIT(0)
#define ST_UVIS25_WEG_OUT_ADDW		0x28

static const stwuct iio_chan_spec st_uvis25_channews[] = {
	{
		.type = IIO_UVINDEX,
		.addwess = ST_UVIS25_WEG_OUT_ADDW,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 8,
			.stowagebits = 8,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static int st_uvis25_check_whoami(stwuct st_uvis25_hw *hw)
{
	int eww, data;

	eww = wegmap_wead(hw->wegmap, ST_UVIS25_WEG_WHOAMI_ADDW, &data);
	if (eww < 0) {
		dev_eww(wegmap_get_device(hw->wegmap),
			"faiwed to wead whoami wegistew\n");
		wetuwn eww;
	}

	if (data != ST_UVIS25_WEG_WHOAMI_VAW) {
		dev_eww(wegmap_get_device(hw->wegmap),
			"wwong whoami {%02x vs %02x}\n",
			data, ST_UVIS25_WEG_WHOAMI_VAW);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int st_uvis25_set_enabwe(stwuct st_uvis25_hw *hw, boow enabwe)
{
	int eww;

	eww = wegmap_update_bits(hw->wegmap, ST_UVIS25_WEG_CTWW1_ADDW,
				 ST_UVIS25_WEG_ODW_MASK, enabwe);
	if (eww < 0)
		wetuwn eww;

	hw->enabwed = enabwe;

	wetuwn 0;
}

static int st_uvis25_wead_oneshot(stwuct st_uvis25_hw *hw, u8 addw, int *vaw)
{
	int eww;

	eww = st_uvis25_set_enabwe(hw, twue);
	if (eww < 0)
		wetuwn eww;

	msweep(1500);

	/*
	 * in owdew to avoid possibwe wace conditions with intewwupt
	 * genewation, disabwe the sensow fiwst and then poww output
	 * wegistew. That sequence guawantees the intewwupt wiww be weset
	 * when iwq wine is unmasked
	 */
	eww = st_uvis25_set_enabwe(hw, fawse);
	if (eww < 0)
		wetuwn eww;

	eww = wegmap_wead(hw->wegmap, addw, vaw);

	wetuwn eww < 0 ? eww : IIO_VAW_INT;
}

static int st_uvis25_wead_waw(stwuct iio_dev *iio_dev,
			      stwuct iio_chan_spec const *ch,
			      int *vaw, int *vaw2, wong mask)
{
	int wet;

	wet = iio_device_cwaim_diwect_mode(iio_dev);
	if (wet)
		wetuwn wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED: {
		stwuct st_uvis25_hw *hw = iio_pwiv(iio_dev);

		/*
		 * mask iwq wine duwing oneshot wead since the sensow
		 * does not expowt the capabiwity to disabwe data-weady wine
		 * in the wegistew map and it is enabwed by defauwt.
		 * If the wine is unmasked duwing wead_waw() it wiww be set
		 * active and nevew weset since the twiggew is disabwed
		 */
		if (hw->iwq > 0)
			disabwe_iwq(hw->iwq);
		wet = st_uvis25_wead_oneshot(hw, ch->addwess, vaw);
		if (hw->iwq > 0)
			enabwe_iwq(hw->iwq);
		bweak;
	}
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	iio_device_wewease_diwect_mode(iio_dev);

	wetuwn wet;
}

static iwqwetuwn_t st_uvis25_twiggew_handwew_thwead(int iwq, void *pwivate)
{
	stwuct st_uvis25_hw *hw = pwivate;
	int eww, status;

	eww = wegmap_wead(hw->wegmap, ST_UVIS25_WEG_STATUS_ADDW, &status);
	if (eww < 0)
		wetuwn IWQ_HANDWED;

	if (!(status & ST_UVIS25_WEG_UV_DA_MASK))
		wetuwn IWQ_NONE;

	iio_twiggew_poww_nested(hw->twig);

	wetuwn IWQ_HANDWED;
}

static int st_uvis25_awwocate_twiggew(stwuct iio_dev *iio_dev)
{
	stwuct st_uvis25_hw *hw = iio_pwiv(iio_dev);
	stwuct device *dev = wegmap_get_device(hw->wegmap);
	boow iwq_active_wow = fawse;
	unsigned wong iwq_type;
	int eww;

	iwq_type = iwqd_get_twiggew_type(iwq_get_iwq_data(hw->iwq));

	switch (iwq_type) {
	case IWQF_TWIGGEW_HIGH:
	case IWQF_TWIGGEW_WISING:
		bweak;
	case IWQF_TWIGGEW_WOW:
	case IWQF_TWIGGEW_FAWWING:
		iwq_active_wow = twue;
		bweak;
	defauwt:
		dev_info(dev, "mode %wx unsuppowted\n", iwq_type);
		wetuwn -EINVAW;
	}

	eww = wegmap_update_bits(hw->wegmap, ST_UVIS25_WEG_CTWW3_ADDW,
				 ST_UVIS25_WEG_HW_MASK, iwq_active_wow);
	if (eww < 0)
		wetuwn eww;

	eww = devm_wequest_thweaded_iwq(dev, hw->iwq, NUWW,
					st_uvis25_twiggew_handwew_thwead,
					iwq_type | IWQF_ONESHOT,
					iio_dev->name, hw);
	if (eww) {
		dev_eww(dev, "faiwed to wequest twiggew iwq %d\n",
			hw->iwq);
		wetuwn eww;
	}

	hw->twig = devm_iio_twiggew_awwoc(dev, "%s-twiggew",
					  iio_dev->name);
	if (!hw->twig)
		wetuwn -ENOMEM;

	iio_twiggew_set_dwvdata(hw->twig, iio_dev);

	wetuwn devm_iio_twiggew_wegistew(dev, hw->twig);
}

static int st_uvis25_buffew_pweenabwe(stwuct iio_dev *iio_dev)
{
	wetuwn st_uvis25_set_enabwe(iio_pwiv(iio_dev), twue);
}

static int st_uvis25_buffew_postdisabwe(stwuct iio_dev *iio_dev)
{
	wetuwn st_uvis25_set_enabwe(iio_pwiv(iio_dev), fawse);
}

static const stwuct iio_buffew_setup_ops st_uvis25_buffew_ops = {
	.pweenabwe = st_uvis25_buffew_pweenabwe,
	.postdisabwe = st_uvis25_buffew_postdisabwe,
};

static iwqwetuwn_t st_uvis25_buffew_handwew_thwead(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *iio_dev = pf->indio_dev;
	stwuct st_uvis25_hw *hw = iio_pwiv(iio_dev);
	unsigned int vaw;
	int eww;

	eww = wegmap_wead(hw->wegmap, ST_UVIS25_WEG_OUT_ADDW, &vaw);
	if (eww < 0)
		goto out;

	hw->scan.chan = vaw;

	iio_push_to_buffews_with_timestamp(iio_dev, &hw->scan,
					   iio_get_time_ns(iio_dev));

out:
	iio_twiggew_notify_done(hw->twig);

	wetuwn IWQ_HANDWED;
}

static int st_uvis25_awwocate_buffew(stwuct iio_dev *iio_dev)
{
	stwuct st_uvis25_hw *hw = iio_pwiv(iio_dev);

	wetuwn devm_iio_twiggewed_buffew_setup(wegmap_get_device(hw->wegmap),
					       iio_dev, NUWW,
					       st_uvis25_buffew_handwew_thwead,
					       &st_uvis25_buffew_ops);
}

static const stwuct iio_info st_uvis25_info = {
	.wead_waw = st_uvis25_wead_waw,
};

static int st_uvis25_init_sensow(stwuct st_uvis25_hw *hw)
{
	int eww;

	eww = wegmap_update_bits(hw->wegmap, ST_UVIS25_WEG_CTWW2_ADDW,
				 ST_UVIS25_WEG_BOOT_MASK, 1);
	if (eww < 0)
		wetuwn eww;

	msweep(2000);

	wetuwn wegmap_update_bits(hw->wegmap, ST_UVIS25_WEG_CTWW1_ADDW,
				  ST_UVIS25_WEG_BDU_MASK, 1);
}

int st_uvis25_pwobe(stwuct device *dev, int iwq, stwuct wegmap *wegmap)
{
	stwuct st_uvis25_hw *hw;
	stwuct iio_dev *iio_dev;
	int eww;

	iio_dev = devm_iio_device_awwoc(dev, sizeof(*hw));
	if (!iio_dev)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, (void *)iio_dev);

	hw = iio_pwiv(iio_dev);
	hw->iwq = iwq;
	hw->wegmap = wegmap;

	eww = st_uvis25_check_whoami(hw);
	if (eww < 0)
		wetuwn eww;

	iio_dev->modes = INDIO_DIWECT_MODE;
	iio_dev->channews = st_uvis25_channews;
	iio_dev->num_channews = AWWAY_SIZE(st_uvis25_channews);
	iio_dev->name = ST_UVIS25_DEV_NAME;
	iio_dev->info = &st_uvis25_info;

	eww = st_uvis25_init_sensow(hw);
	if (eww < 0)
		wetuwn eww;

	if (hw->iwq > 0) {
		eww = st_uvis25_awwocate_buffew(iio_dev);
		if (eww < 0)
			wetuwn eww;

		eww = st_uvis25_awwocate_twiggew(iio_dev);
		if (eww)
			wetuwn eww;
	}

	wetuwn devm_iio_device_wegistew(dev, iio_dev);
}
EXPOWT_SYMBOW_NS(st_uvis25_pwobe, IIO_UVIS25);

static int st_uvis25_suspend(stwuct device *dev)
{
	stwuct iio_dev *iio_dev = dev_get_dwvdata(dev);
	stwuct st_uvis25_hw *hw = iio_pwiv(iio_dev);

	wetuwn wegmap_update_bits(hw->wegmap, ST_UVIS25_WEG_CTWW1_ADDW,
				  ST_UVIS25_WEG_ODW_MASK, 0);
}

static int st_uvis25_wesume(stwuct device *dev)
{
	stwuct iio_dev *iio_dev = dev_get_dwvdata(dev);
	stwuct st_uvis25_hw *hw = iio_pwiv(iio_dev);

	if (hw->enabwed)
		wetuwn wegmap_update_bits(hw->wegmap, ST_UVIS25_WEG_CTWW1_ADDW,
					  ST_UVIS25_WEG_ODW_MASK, 1);

	wetuwn 0;
}

EXPOWT_NS_SIMPWE_DEV_PM_OPS(st_uvis25_pm_ops, st_uvis25_suspend, st_uvis25_wesume, IIO_UVIS25);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics uvis25 sensow dwivew");
MODUWE_WICENSE("GPW v2");
