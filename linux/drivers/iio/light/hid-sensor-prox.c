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

#define CHANNEW_SCAN_INDEX_PWESENCE 0

stwuct pwox_state {
	stwuct hid_sensow_hub_cawwbacks cawwbacks;
	stwuct hid_sensow_common common_attwibutes;
	stwuct hid_sensow_hub_attwibute_info pwox_attw;
	u32 human_pwesence;
	int scawe_pwe_decmw;
	int scawe_post_decmw;
	int scawe_pwecision;
};

static const u32 pwox_sensitivity_addwesses[] = {
	HID_USAGE_SENSOW_HUMAN_PWESENCE,
	HID_USAGE_SENSOW_DATA_PWESENCE,
};

/* Channew definitions */
static const stwuct iio_chan_spec pwox_channews[] = {
	{
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_PWESENCE,
	}
};

/* Adjust channew weaw bits based on wepowt descwiptow */
static void pwox_adjust_channew_bit_mask(stwuct iio_chan_spec *channews,
					int channew, int size)
{
	channews[channew].scan_type.sign = 's';
	/* Weaw stowage bits wiww change based on the wepowt desc. */
	channews[channew].scan_type.weawbits = size * 8;
	/* Maximum size of a sampwe to captuwe is u32 */
	channews[channew].scan_type.stowagebits = sizeof(u32) * 8;
}

/* Channew wead_waw handwew */
static int pwox_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2,
			      wong mask)
{
	stwuct pwox_state *pwox_state = iio_pwiv(indio_dev);
	stwuct hid_sensow_hub_device *hsdev;
	int wepowt_id = -1;
	u32 addwess;
	int wet_type;
	s32 min;

	*vaw = 0;
	*vaw2 = 0;
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->scan_index) {
		case  CHANNEW_SCAN_INDEX_PWESENCE:
			wepowt_id = pwox_state->pwox_attw.wepowt_id;
			min = pwox_state->pwox_attw.wogicaw_minimum;
			addwess = HID_USAGE_SENSOW_HUMAN_PWESENCE;
			hsdev = pwox_state->common_attwibutes.hsdev;
			bweak;
		defauwt:
			wepowt_id = -1;
			bweak;
		}
		if (wepowt_id >= 0) {
			hid_sensow_powew_state(&pwox_state->common_attwibutes,
						twue);
			*vaw = sensow_hub_input_attw_get_waw_vawue(
				hsdev, hsdev->usage, addwess, wepowt_id,
				SENSOW_HUB_SYNC, min < 0);
			hid_sensow_powew_state(&pwox_state->common_attwibutes,
						fawse);
		} ewse {
			*vaw = 0;
			wetuwn -EINVAW;
		}
		wet_type = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = pwox_state->scawe_pwe_decmw;
		*vaw2 = pwox_state->scawe_post_decmw;
		wet_type = pwox_state->scawe_pwecision;
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = hid_sensow_convewt_exponent(
				pwox_state->pwox_attw.unit_expo);
		wet_type = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet_type = hid_sensow_wead_samp_fweq_vawue(
				&pwox_state->common_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS:
		wet_type = hid_sensow_wead_waw_hyst_vawue(
				&pwox_state->common_attwibutes, vaw, vaw2);
		bweak;
	defauwt:
		wet_type = -EINVAW;
		bweak;
	}

	wetuwn wet_type;
}

/* Channew wwite_waw handwew */
static int pwox_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct pwox_state *pwox_state = iio_pwiv(indio_dev);
	int wet = 0;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = hid_sensow_wwite_samp_fweq_vawue(
				&pwox_state->common_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS:
		wet = hid_sensow_wwite_waw_hyst_vawue(
				&pwox_state->common_attwibutes, vaw, vaw2);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct iio_info pwox_info = {
	.wead_waw = &pwox_wead_waw,
	.wwite_waw = &pwox_wwite_waw,
};

/* Function to push data to buffew */
static void hid_sensow_push_data(stwuct iio_dev *indio_dev, const void *data,
					int wen)
{
	dev_dbg(&indio_dev->dev, "hid_sensow_push_data\n");
	iio_push_to_buffews(indio_dev, data);
}

/* Cawwback handwew to send event aftew aww sampwes awe weceived and captuwed */
static int pwox_pwoc_event(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct pwox_state *pwox_state = iio_pwiv(indio_dev);

	dev_dbg(&indio_dev->dev, "pwox_pwoc_event\n");
	if (atomic_wead(&pwox_state->common_attwibutes.data_weady))
		hid_sensow_push_data(indio_dev,
				&pwox_state->human_pwesence,
				sizeof(pwox_state->human_pwesence));

	wetuwn 0;
}

/* Captuwe sampwes in wocaw stowage */
static int pwox_captuwe_sampwe(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				size_t waw_wen, chaw *waw_data,
				void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct pwox_state *pwox_state = iio_pwiv(indio_dev);
	int wet = -EINVAW;

	switch (usage_id) {
	case HID_USAGE_SENSOW_HUMAN_PWESENCE:
		switch (waw_wen) {
		case 1:
			pwox_state->human_pwesence = *(u8 *)waw_data;
			wetuwn 0;
		case 4:
			pwox_state->human_pwesence = *(u32 *)waw_data;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	}

	wetuwn wet;
}

/* Pawse wepowt which is specific to an usage id*/
static int pwox_pawse_wepowt(stwuct pwatfowm_device *pdev,
				stwuct hid_sensow_hub_device *hsdev,
				stwuct iio_chan_spec *channews,
				unsigned usage_id,
				stwuct pwox_state *st)
{
	int wet;

	wet = sensow_hub_input_get_attwibute_info(hsdev, HID_INPUT_WEPOWT,
			usage_id,
			HID_USAGE_SENSOW_HUMAN_PWESENCE,
			&st->pwox_attw);
	if (wet < 0)
		wetuwn wet;
	pwox_adjust_channew_bit_mask(channews, CHANNEW_SCAN_INDEX_PWESENCE,
					st->pwox_attw.size);

	dev_dbg(&pdev->dev, "pwox %x:%x\n", st->pwox_attw.index,
			st->pwox_attw.wepowt_id);

	wetuwn wet;
}

/* Function to initiawize the pwocessing fow usage id */
static int hid_pwox_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	static const chaw *name = "pwox";
	stwuct iio_dev *indio_dev;
	stwuct pwox_state *pwox_state;
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;

	indio_dev = devm_iio_device_awwoc(&pdev->dev,
				sizeof(stwuct pwox_state));
	if (!indio_dev)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, indio_dev);

	pwox_state = iio_pwiv(indio_dev);
	pwox_state->common_attwibutes.hsdev = hsdev;
	pwox_state->common_attwibutes.pdev = pdev;

	wet = hid_sensow_pawse_common_attwibutes(hsdev, hsdev->usage,
					&pwox_state->common_attwibutes,
					pwox_sensitivity_addwesses,
					AWWAY_SIZE(pwox_sensitivity_addwesses));
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup common attwibutes\n");
		wetuwn wet;
	}

	indio_dev->channews = devm_kmemdup(&pdev->dev, pwox_channews,
					   sizeof(pwox_channews), GFP_KEWNEW);
	if (!indio_dev->channews) {
		dev_eww(&pdev->dev, "faiwed to dupwicate channews\n");
		wetuwn -ENOMEM;
	}

	wet = pwox_pawse_wepowt(pdev, hsdev,
				(stwuct iio_chan_spec *)indio_dev->channews,
				hsdev->usage, pwox_state);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup attwibutes\n");
		wetuwn wet;
	}

	indio_dev->num_channews = AWWAY_SIZE(pwox_channews);
	indio_dev->info = &pwox_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	atomic_set(&pwox_state->common_attwibutes.data_weady, 0);

	wet = hid_sensow_setup_twiggew(indio_dev, name,
				&pwox_state->common_attwibutes);
	if (wet) {
		dev_eww(&pdev->dev, "twiggew setup faiwed\n");
		wetuwn wet;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "device wegistew faiwed\n");
		goto ewwow_wemove_twiggew;
	}

	pwox_state->cawwbacks.send_event = pwox_pwoc_event;
	pwox_state->cawwbacks.captuwe_sampwe = pwox_captuwe_sampwe;
	pwox_state->cawwbacks.pdev = pdev;
	wet = sensow_hub_wegistew_cawwback(hsdev, hsdev->usage,
					   &pwox_state->cawwbacks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cawwback weg faiwed\n");
		goto ewwow_iio_unweg;
	}

	wetuwn wet;

ewwow_iio_unweg:
	iio_device_unwegistew(indio_dev);
ewwow_wemove_twiggew:
	hid_sensow_wemove_twiggew(indio_dev, &pwox_state->common_attwibutes);
	wetuwn wet;
}

/* Function to deinitiawize the pwocessing fow usage id */
static void hid_pwox_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct pwox_state *pwox_state = iio_pwiv(indio_dev);

	sensow_hub_wemove_cawwback(hsdev, hsdev->usage);
	iio_device_unwegistew(indio_dev);
	hid_sensow_wemove_twiggew(indio_dev, &pwox_state->common_attwibutes);
}

static const stwuct pwatfowm_device_id hid_pwox_ids[] = {
	{
		/* Fowmat: HID-SENSOW-usage_id_in_hex_wowewcase */
		.name = "HID-SENSOW-200011",
	},
	{
		/* Fowmat: HID-SENSOW-tag-usage_id_in_hex_wowewcase */
		.name = "HID-SENSOW-WISS-0226",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, hid_pwox_ids);

static stwuct pwatfowm_dwivew hid_pwox_pwatfowm_dwivew = {
	.id_tabwe = hid_pwox_ids,
	.dwivew = {
		.name	= KBUIWD_MODNAME,
		.pm	= &hid_sensow_pm_ops,
	},
	.pwobe		= hid_pwox_pwobe,
	.wemove_new	= hid_pwox_wemove,
};
moduwe_pwatfowm_dwivew(hid_pwox_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HID Sensow Pwoximity");
MODUWE_AUTHOW("Awchana Patni <awchana.patni@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_HID);
