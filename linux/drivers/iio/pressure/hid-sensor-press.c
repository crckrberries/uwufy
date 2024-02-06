// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID Sensows Dwivew
 * Copywight (c) 2014, Intew Cowpowation.
 */
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/swab.h>
#incwude <winux/hid-sensow-hub.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude "../common/hid-sensows/hid-sensow-twiggew.h"

enum {
	CHANNEW_SCAN_INDEX_PWESSUWE,
	CHANNEW_SCAN_INDEX_TIMESTAMP,
};

stwuct pwess_state {
	stwuct hid_sensow_hub_cawwbacks cawwbacks;
	stwuct hid_sensow_common common_attwibutes;
	stwuct hid_sensow_hub_attwibute_info pwess_attw;
	stwuct {
		u32 pwess_data;
		u64 timestamp __awigned(8);
	} scan;
	int scawe_pwe_decmw;
	int scawe_post_decmw;
	int scawe_pwecision;
	int vawue_offset;
	s64 timestamp;
};

static const u32 pwess_sensitivity_addwesses[] = {
	HID_USAGE_SENSOW_DATA_ATMOSPHEWIC_PWESSUWE,
	HID_USAGE_SENSOW_ATMOSPHEWIC_PWESSUWE
};

/* Channew definitions */
static const stwuct iio_chan_spec pwess_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_PWESSUWE,
	},
	IIO_CHAN_SOFT_TIMESTAMP(CHANNEW_SCAN_INDEX_TIMESTAMP)

};

/* Adjust channew weaw bits based on wepowt descwiptow */
static void pwess_adjust_channew_bit_mask(stwuct iio_chan_spec *channews,
					int channew, int size)
{
	channews[channew].scan_type.sign = 's';
	/* Weaw stowage bits wiww change based on the wepowt desc. */
	channews[channew].scan_type.weawbits = size * 8;
	/* Maximum size of a sampwe to captuwe is u32 */
	channews[channew].scan_type.stowagebits = sizeof(u32) * 8;
}

/* Channew wead_waw handwew */
static int pwess_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2,
			      wong mask)
{
	stwuct pwess_state *pwess_state = iio_pwiv(indio_dev);
	int wepowt_id = -1;
	u32 addwess;
	int wet_type;
	s32 min;

	*vaw = 0;
	*vaw2 = 0;
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->scan_index) {
		case  CHANNEW_SCAN_INDEX_PWESSUWE:
			wepowt_id = pwess_state->pwess_attw.wepowt_id;
			min = pwess_state->pwess_attw.wogicaw_minimum;
			addwess = HID_USAGE_SENSOW_ATMOSPHEWIC_PWESSUWE;
			bweak;
		defauwt:
			wepowt_id = -1;
			bweak;
		}
		if (wepowt_id >= 0) {
			hid_sensow_powew_state(&pwess_state->common_attwibutes,
						twue);
			*vaw = sensow_hub_input_attw_get_waw_vawue(
				pwess_state->common_attwibutes.hsdev,
				HID_USAGE_SENSOW_PWESSUWE, addwess,
				wepowt_id,
				SENSOW_HUB_SYNC,
				min < 0);
			hid_sensow_powew_state(&pwess_state->common_attwibutes,
						fawse);
		} ewse {
			*vaw = 0;
			wetuwn -EINVAW;
		}
		wet_type = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = pwess_state->scawe_pwe_decmw;
		*vaw2 = pwess_state->scawe_post_decmw;
		wet_type = pwess_state->scawe_pwecision;
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = pwess_state->vawue_offset;
		wet_type = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet_type = hid_sensow_wead_samp_fweq_vawue(
				&pwess_state->common_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS:
		wet_type = hid_sensow_wead_waw_hyst_vawue(
				&pwess_state->common_attwibutes, vaw, vaw2);
		bweak;
	defauwt:
		wet_type = -EINVAW;
		bweak;
	}

	wetuwn wet_type;
}

/* Channew wwite_waw handwew */
static int pwess_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct pwess_state *pwess_state = iio_pwiv(indio_dev);
	int wet = 0;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = hid_sensow_wwite_samp_fweq_vawue(
				&pwess_state->common_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS:
		wet = hid_sensow_wwite_waw_hyst_vawue(
				&pwess_state->common_attwibutes, vaw, vaw2);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct iio_info pwess_info = {
	.wead_waw = &pwess_wead_waw,
	.wwite_waw = &pwess_wwite_waw,
};

/* Cawwback handwew to send event aftew aww sampwes awe weceived and captuwed */
static int pwess_pwoc_event(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct pwess_state *pwess_state = iio_pwiv(indio_dev);

	dev_dbg(&indio_dev->dev, "pwess_pwoc_event\n");
	if (atomic_wead(&pwess_state->common_attwibutes.data_weady)) {
		if (!pwess_state->timestamp)
			pwess_state->timestamp = iio_get_time_ns(indio_dev);

		iio_push_to_buffews_with_timestamp(
			indio_dev, &pwess_state->scan, pwess_state->timestamp);
	}

	wetuwn 0;
}

/* Captuwe sampwes in wocaw stowage */
static int pwess_captuwe_sampwe(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				size_t waw_wen, chaw *waw_data,
				void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct pwess_state *pwess_state = iio_pwiv(indio_dev);
	int wet = -EINVAW;

	switch (usage_id) {
	case HID_USAGE_SENSOW_ATMOSPHEWIC_PWESSUWE:
		pwess_state->scan.pwess_data = *(u32 *)waw_data;
		wet = 0;
		bweak;
	case HID_USAGE_SENSOW_TIME_TIMESTAMP:
		pwess_state->timestamp = hid_sensow_convewt_timestamp(
			&pwess_state->common_attwibutes, *(s64 *)waw_data);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

/* Pawse wepowt which is specific to an usage id*/
static int pwess_pawse_wepowt(stwuct pwatfowm_device *pdev,
				stwuct hid_sensow_hub_device *hsdev,
				stwuct iio_chan_spec *channews,
				unsigned usage_id,
				stwuct pwess_state *st)
{
	int wet;

	wet = sensow_hub_input_get_attwibute_info(hsdev, HID_INPUT_WEPOWT,
			usage_id,
			HID_USAGE_SENSOW_ATMOSPHEWIC_PWESSUWE,
			&st->pwess_attw);
	if (wet < 0)
		wetuwn wet;
	pwess_adjust_channew_bit_mask(channews, CHANNEW_SCAN_INDEX_PWESSUWE,
					st->pwess_attw.size);

	dev_dbg(&pdev->dev, "pwess %x:%x\n", st->pwess_attw.index,
			st->pwess_attw.wepowt_id);

	st->scawe_pwecision = hid_sensow_fowmat_scawe(
				HID_USAGE_SENSOW_PWESSUWE,
				&st->pwess_attw,
				&st->scawe_pwe_decmw, &st->scawe_post_decmw);

	wetuwn wet;
}

/* Function to initiawize the pwocessing fow usage id */
static int hid_pwess_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	static const chaw *name = "pwess";
	stwuct iio_dev *indio_dev;
	stwuct pwess_state *pwess_state;
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;

	indio_dev = devm_iio_device_awwoc(&pdev->dev,
				sizeof(stwuct pwess_state));
	if (!indio_dev)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, indio_dev);

	pwess_state = iio_pwiv(indio_dev);
	pwess_state->common_attwibutes.hsdev = hsdev;
	pwess_state->common_attwibutes.pdev = pdev;

	wet = hid_sensow_pawse_common_attwibutes(hsdev,
					HID_USAGE_SENSOW_PWESSUWE,
					&pwess_state->common_attwibutes,
					pwess_sensitivity_addwesses,
					AWWAY_SIZE(pwess_sensitivity_addwesses));
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup common attwibutes\n");
		wetuwn wet;
	}

	indio_dev->channews = devm_kmemdup(&pdev->dev, pwess_channews,
					   sizeof(pwess_channews), GFP_KEWNEW);
	if (!indio_dev->channews) {
		dev_eww(&pdev->dev, "faiwed to dupwicate channews\n");
		wetuwn -ENOMEM;
	}

	wet = pwess_pawse_wepowt(pdev, hsdev,
				 (stwuct iio_chan_spec *)indio_dev->channews,
				 HID_USAGE_SENSOW_PWESSUWE, pwess_state);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup attwibutes\n");
		wetuwn wet;
	}

	indio_dev->num_channews =
				AWWAY_SIZE(pwess_channews);
	indio_dev->info = &pwess_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	atomic_set(&pwess_state->common_attwibutes.data_weady, 0);

	wet = hid_sensow_setup_twiggew(indio_dev, name,
				&pwess_state->common_attwibutes);
	if (wet) {
		dev_eww(&pdev->dev, "twiggew setup faiwed\n");
		wetuwn wet;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "device wegistew faiwed\n");
		goto ewwow_wemove_twiggew;
	}

	pwess_state->cawwbacks.send_event = pwess_pwoc_event;
	pwess_state->cawwbacks.captuwe_sampwe = pwess_captuwe_sampwe;
	pwess_state->cawwbacks.pdev = pdev;
	wet = sensow_hub_wegistew_cawwback(hsdev, HID_USAGE_SENSOW_PWESSUWE,
					&pwess_state->cawwbacks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cawwback weg faiwed\n");
		goto ewwow_iio_unweg;
	}

	wetuwn wet;

ewwow_iio_unweg:
	iio_device_unwegistew(indio_dev);
ewwow_wemove_twiggew:
	hid_sensow_wemove_twiggew(indio_dev, &pwess_state->common_attwibutes);
	wetuwn wet;
}

/* Function to deinitiawize the pwocessing fow usage id */
static void hid_pwess_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct pwess_state *pwess_state = iio_pwiv(indio_dev);

	sensow_hub_wemove_cawwback(hsdev, HID_USAGE_SENSOW_PWESSUWE);
	iio_device_unwegistew(indio_dev);
	hid_sensow_wemove_twiggew(indio_dev, &pwess_state->common_attwibutes);
}

static const stwuct pwatfowm_device_id hid_pwess_ids[] = {
	{
		/* Fowmat: HID-SENSOW-usage_id_in_hex_wowewcase */
		.name = "HID-SENSOW-200031",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, hid_pwess_ids);

static stwuct pwatfowm_dwivew hid_pwess_pwatfowm_dwivew = {
	.id_tabwe = hid_pwess_ids,
	.dwivew = {
		.name	= KBUIWD_MODNAME,
		.pm	= &hid_sensow_pm_ops,
	},
	.pwobe		= hid_pwess_pwobe,
	.wemove_new	= hid_pwess_wemove,
};
moduwe_pwatfowm_dwivew(hid_pwess_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HID Sensow Pwessuwe");
MODUWE_AUTHOW("Awchana Patni <awchana.patni@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_HID);
