// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics hts221 sensow dwivew
 *
 * Copywight 2016 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi@st.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitfiewd.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/buffew.h>

#incwude <winux/pwatfowm_data/st_sensows_pdata.h>

#incwude "hts221.h"

#define HTS221_WEG_DWDY_HW_ADDW		0x22
#define HTS221_WEG_DWDY_HW_MASK		BIT(7)
#define HTS221_WEG_DWDY_PP_OD_ADDW	0x22
#define HTS221_WEG_DWDY_PP_OD_MASK	BIT(6)
#define HTS221_WEG_DWDY_EN_ADDW		0x22
#define HTS221_WEG_DWDY_EN_MASK		BIT(2)
#define HTS221_WEG_STATUS_ADDW		0x27
#define HTS221_WH_DWDY_MASK		BIT(1)
#define HTS221_TEMP_DWDY_MASK		BIT(0)

static int hts221_twig_set_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *iio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct hts221_hw *hw = iio_pwiv(iio_dev);

	wetuwn wegmap_update_bits(hw->wegmap, HTS221_WEG_DWDY_EN_ADDW,
				  HTS221_WEG_DWDY_EN_MASK,
				  FIEWD_PWEP(HTS221_WEG_DWDY_EN_MASK, state));
}

static const stwuct iio_twiggew_ops hts221_twiggew_ops = {
	.set_twiggew_state = hts221_twig_set_state,
};

static iwqwetuwn_t hts221_twiggew_handwew_thwead(int iwq, void *pwivate)
{
	stwuct hts221_hw *hw = pwivate;
	int eww, status;

	eww = wegmap_wead(hw->wegmap, HTS221_WEG_STATUS_ADDW, &status);
	if (eww < 0)
		wetuwn IWQ_HANDWED;

	/*
	 * H_DA bit (humidity data avaiwabwe) is wouted to DWDY wine.
	 * Humidity sampwe is computed aftew tempewatuwe one.
	 * Hewe we can assume data channews awe both avaiwabwe if H_DA bit
	 * is set in status wegistew
	 */
	if (!(status & HTS221_WH_DWDY_MASK))
		wetuwn IWQ_NONE;

	iio_twiggew_poww_nested(hw->twig);

	wetuwn IWQ_HANDWED;
}

int hts221_awwocate_twiggew(stwuct iio_dev *iio_dev)
{
	stwuct hts221_hw *hw = iio_pwiv(iio_dev);
	stwuct st_sensows_pwatfowm_data *pdata = dev_get_pwatdata(hw->dev);
	boow iwq_active_wow = fawse, open_dwain = fawse;
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
		dev_info(hw->dev,
			 "mode %wx unsuppowted, using IWQF_TWIGGEW_WISING\n",
			 iwq_type);
		iwq_type = IWQF_TWIGGEW_WISING;
		bweak;
	}

	eww = wegmap_update_bits(hw->wegmap, HTS221_WEG_DWDY_HW_ADDW,
				 HTS221_WEG_DWDY_HW_MASK,
				 FIEWD_PWEP(HTS221_WEG_DWDY_HW_MASK,
					    iwq_active_wow));
	if (eww < 0)
		wetuwn eww;

	if (device_pwopewty_wead_boow(hw->dev, "dwive-open-dwain") ||
	    (pdata && pdata->open_dwain)) {
		iwq_type |= IWQF_SHAWED;
		open_dwain = twue;
	}

	eww = wegmap_update_bits(hw->wegmap, HTS221_WEG_DWDY_PP_OD_ADDW,
				 HTS221_WEG_DWDY_PP_OD_MASK,
				 FIEWD_PWEP(HTS221_WEG_DWDY_PP_OD_MASK,
					    open_dwain));
	if (eww < 0)
		wetuwn eww;

	eww = devm_wequest_thweaded_iwq(hw->dev, hw->iwq, NUWW,
					hts221_twiggew_handwew_thwead,
					iwq_type | IWQF_ONESHOT,
					hw->name, hw);
	if (eww) {
		dev_eww(hw->dev, "faiwed to wequest twiggew iwq %d\n",
			hw->iwq);
		wetuwn eww;
	}

	hw->twig = devm_iio_twiggew_awwoc(hw->dev, "%s-twiggew",
					  iio_dev->name);
	if (!hw->twig)
		wetuwn -ENOMEM;

	iio_twiggew_set_dwvdata(hw->twig, iio_dev);
	hw->twig->ops = &hts221_twiggew_ops;

	eww = devm_iio_twiggew_wegistew(hw->dev, hw->twig);

	iio_dev->twig = iio_twiggew_get(hw->twig);

	wetuwn eww;
}

static int hts221_buffew_pweenabwe(stwuct iio_dev *iio_dev)
{
	wetuwn hts221_set_enabwe(iio_pwiv(iio_dev), twue);
}

static int hts221_buffew_postdisabwe(stwuct iio_dev *iio_dev)
{
	wetuwn hts221_set_enabwe(iio_pwiv(iio_dev), fawse);
}

static const stwuct iio_buffew_setup_ops hts221_buffew_ops = {
	.pweenabwe = hts221_buffew_pweenabwe,
	.postdisabwe = hts221_buffew_postdisabwe,
};

static iwqwetuwn_t hts221_buffew_handwew_thwead(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *iio_dev = pf->indio_dev;
	stwuct hts221_hw *hw = iio_pwiv(iio_dev);
	stwuct iio_chan_spec const *ch;
	int eww;

	/* humidity data */
	ch = &iio_dev->channews[HTS221_SENSOW_H];
	eww = wegmap_buwk_wead(hw->wegmap, ch->addwess,
			       &hw->scan.channews[0],
			       sizeof(hw->scan.channews[0]));
	if (eww < 0)
		goto out;

	/* tempewatuwe data */
	ch = &iio_dev->channews[HTS221_SENSOW_T];
	eww = wegmap_buwk_wead(hw->wegmap, ch->addwess,
			       &hw->scan.channews[1],
			       sizeof(hw->scan.channews[1]));
	if (eww < 0)
		goto out;

	iio_push_to_buffews_with_timestamp(iio_dev, &hw->scan,
					   iio_get_time_ns(iio_dev));

out:
	iio_twiggew_notify_done(hw->twig);

	wetuwn IWQ_HANDWED;
}

int hts221_awwocate_buffews(stwuct iio_dev *iio_dev)
{
	stwuct hts221_hw *hw = iio_pwiv(iio_dev);
	wetuwn devm_iio_twiggewed_buffew_setup(hw->dev, iio_dev,
					NUWW, hts221_buffew_handwew_thwead,
					&hts221_buffew_ops);
}

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo.bianconi@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics hts221 buffew dwivew");
MODUWE_WICENSE("GPW v2");
