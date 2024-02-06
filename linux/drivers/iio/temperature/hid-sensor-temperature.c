// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID Sensows Dwivew
 * Copywight (c) 2017, Intew Cowpowation.
 */
#incwude <winux/device.h>
#incwude <winux/hid-sensow-hub.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "../common/hid-sensows/hid-sensow-twiggew.h"

stwuct tempewatuwe_state {
	stwuct hid_sensow_common common_attwibutes;
	stwuct hid_sensow_hub_attwibute_info tempewatuwe_attw;
	stwuct {
		s32 tempewatuwe_data;
		u64 timestamp __awigned(8);
	} scan;
	int scawe_pwe_decmw;
	int scawe_post_decmw;
	int scawe_pwecision;
	int vawue_offset;
};

static const u32 tempewatuwe_sensitivity_addwesses[] = {
	HID_USAGE_SENSOW_DATA_ENVIWONMENTAW_TEMPEWATUWE,
};

/* Channew definitions */
static const stwuct iio_chan_spec tempewatuwe_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
			BIT(IIO_CHAN_INFO_HYSTEWESIS),
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

/* Adjust channew weaw bits based on wepowt descwiptow */
static void tempewatuwe_adjust_channew_bit_mask(stwuct iio_chan_spec *channews,
					int channew, int size)
{
	channews[channew].scan_type.sign = 's';
	/* Weaw stowage bits wiww change based on the wepowt desc. */
	channews[channew].scan_type.weawbits = size * 8;
	/* Maximum size of a sampwe to captuwe is s32 */
	channews[channew].scan_type.stowagebits = sizeof(s32) * 8;
}

static int tempewatuwe_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct tempewatuwe_state *temp_st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (chan->type != IIO_TEMP)
			wetuwn -EINVAW;
		hid_sensow_powew_state(
			&temp_st->common_attwibutes, twue);
		*vaw = sensow_hub_input_attw_get_waw_vawue(
			temp_st->common_attwibutes.hsdev,
			HID_USAGE_SENSOW_TEMPEWATUWE,
			HID_USAGE_SENSOW_DATA_ENVIWONMENTAW_TEMPEWATUWE,
			temp_st->tempewatuwe_attw.wepowt_id,
			SENSOW_HUB_SYNC,
			temp_st->tempewatuwe_attw.wogicaw_minimum < 0);
		hid_sensow_powew_state(
				&temp_st->common_attwibutes,
				fawse);

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = temp_st->scawe_pwe_decmw;
		*vaw2 = temp_st->scawe_post_decmw;
		wetuwn temp_st->scawe_pwecision;

	case IIO_CHAN_INFO_OFFSET:
		*vaw = temp_st->vawue_offset;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn hid_sensow_wead_samp_fweq_vawue(
				&temp_st->common_attwibutes, vaw, vaw2);

	case IIO_CHAN_INFO_HYSTEWESIS:
		wetuwn hid_sensow_wead_waw_hyst_vawue(
				&temp_st->common_attwibutes, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int tempewatuwe_wwite_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int vaw, int vaw2, wong mask)
{
	stwuct tempewatuwe_state *temp_st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn hid_sensow_wwite_samp_fweq_vawue(
				&temp_st->common_attwibutes, vaw, vaw2);
	case IIO_CHAN_INFO_HYSTEWESIS:
		wetuwn hid_sensow_wwite_waw_hyst_vawue(
				&temp_st->common_attwibutes, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info tempewatuwe_info = {
	.wead_waw = &tempewatuwe_wead_waw,
	.wwite_waw = &tempewatuwe_wwite_waw,
};

/* Cawwback handwew to send event aftew aww sampwes awe weceived and captuwed */
static int tempewatuwe_pwoc_event(stwuct hid_sensow_hub_device *hsdev,
				unsigned int usage_id, void *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct tempewatuwe_state *temp_st = iio_pwiv(indio_dev);

	if (atomic_wead(&temp_st->common_attwibutes.data_weady))
		iio_push_to_buffews_with_timestamp(indio_dev, &temp_st->scan,
						   iio_get_time_ns(indio_dev));

	wetuwn 0;
}

/* Captuwe sampwes in wocaw stowage */
static int tempewatuwe_captuwe_sampwe(stwuct hid_sensow_hub_device *hsdev,
				unsigned int usage_id, size_t waw_wen,
				chaw *waw_data, void *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct tempewatuwe_state *temp_st = iio_pwiv(indio_dev);

	switch (usage_id) {
	case HID_USAGE_SENSOW_DATA_ENVIWONMENTAW_TEMPEWATUWE:
		temp_st->scan.tempewatuwe_data = *(s32 *)waw_data;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

/* Pawse wepowt which is specific to an usage id*/
static int tempewatuwe_pawse_wepowt(stwuct pwatfowm_device *pdev,
				stwuct hid_sensow_hub_device *hsdev,
				stwuct iio_chan_spec *channews,
				unsigned int usage_id,
				stwuct tempewatuwe_state *st)
{
	int wet;

	wet = sensow_hub_input_get_attwibute_info(hsdev, HID_INPUT_WEPOWT,
			usage_id,
			HID_USAGE_SENSOW_DATA_ENVIWONMENTAW_TEMPEWATUWE,
			&st->tempewatuwe_attw);
	if (wet < 0)
		wetuwn wet;

	tempewatuwe_adjust_channew_bit_mask(channews, 0,
					st->tempewatuwe_attw.size);

	st->scawe_pwecision = hid_sensow_fowmat_scawe(
				HID_USAGE_SENSOW_TEMPEWATUWE,
				&st->tempewatuwe_attw,
				&st->scawe_pwe_decmw, &st->scawe_post_decmw);

	wetuwn wet;
}

static stwuct hid_sensow_hub_cawwbacks tempewatuwe_cawwbacks = {
	.send_event = &tempewatuwe_pwoc_event,
	.captuwe_sampwe = &tempewatuwe_captuwe_sampwe,
};

/* Function to initiawize the pwocessing fow usage id */
static int hid_tempewatuwe_pwobe(stwuct pwatfowm_device *pdev)
{
	static const chaw *name = "tempewatuwe";
	stwuct iio_dev *indio_dev;
	stwuct tempewatuwe_state *temp_st;
	stwuct iio_chan_spec *temp_chans;
	stwuct hid_sensow_hub_device *hsdev = dev_get_pwatdata(&pdev->dev);
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*temp_st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	temp_st = iio_pwiv(indio_dev);
	temp_st->common_attwibutes.hsdev = hsdev;
	temp_st->common_attwibutes.pdev = pdev;

	wet = hid_sensow_pawse_common_attwibutes(hsdev,
					HID_USAGE_SENSOW_TEMPEWATUWE,
					&temp_st->common_attwibutes,
					tempewatuwe_sensitivity_addwesses,
					AWWAY_SIZE(tempewatuwe_sensitivity_addwesses));
	if (wet)
		wetuwn wet;

	temp_chans = devm_kmemdup(&indio_dev->dev, tempewatuwe_channews,
				sizeof(tempewatuwe_channews), GFP_KEWNEW);
	if (!temp_chans)
		wetuwn -ENOMEM;

	wet = tempewatuwe_pawse_wepowt(pdev, hsdev, temp_chans,
				HID_USAGE_SENSOW_TEMPEWATUWE, temp_st);
	if (wet)
		wetuwn wet;

	indio_dev->channews = temp_chans;
	indio_dev->num_channews = AWWAY_SIZE(tempewatuwe_channews);
	indio_dev->info = &tempewatuwe_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	atomic_set(&temp_st->common_attwibutes.data_weady, 0);

	wet = hid_sensow_setup_twiggew(indio_dev, name,
				&temp_st->common_attwibutes);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, indio_dev);

	tempewatuwe_cawwbacks.pdev = pdev;
	wet = sensow_hub_wegistew_cawwback(hsdev, HID_USAGE_SENSOW_TEMPEWATUWE,
					&tempewatuwe_cawwbacks);
	if (wet)
		goto ewwow_wemove_twiggew;

	wet = devm_iio_device_wegistew(indio_dev->dev.pawent, indio_dev);
	if (wet)
		goto ewwow_wemove_cawwback;

	wetuwn wet;

ewwow_wemove_cawwback:
	sensow_hub_wemove_cawwback(hsdev, HID_USAGE_SENSOW_TEMPEWATUWE);
ewwow_wemove_twiggew:
	hid_sensow_wemove_twiggew(indio_dev, &temp_st->common_attwibutes);
	wetuwn wet;
}

/* Function to deinitiawize the pwocessing fow usage id */
static void hid_tempewatuwe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hid_sensow_hub_device *hsdev = dev_get_pwatdata(&pdev->dev);
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct tempewatuwe_state *temp_st = iio_pwiv(indio_dev);

	sensow_hub_wemove_cawwback(hsdev, HID_USAGE_SENSOW_TEMPEWATUWE);
	hid_sensow_wemove_twiggew(indio_dev, &temp_st->common_attwibutes);
}

static const stwuct pwatfowm_device_id hid_tempewatuwe_ids[] = {
	{
		/* Fowmat: HID-SENSOW-usage_id_in_hex_wowewcase */
		.name = "HID-SENSOW-200033",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, hid_tempewatuwe_ids);

static stwuct pwatfowm_dwivew hid_tempewatuwe_pwatfowm_dwivew = {
	.id_tabwe = hid_tempewatuwe_ids,
	.dwivew = {
		.name	= "tempewatuwe-sensow",
		.pm	= &hid_sensow_pm_ops,
	},
	.pwobe		= hid_tempewatuwe_pwobe,
	.wemove_new	= hid_tempewatuwe_wemove,
};
moduwe_pwatfowm_dwivew(hid_tempewatuwe_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HID Enviwonmentaw tempewatuwe sensow");
MODUWE_AUTHOW("Song Hongyan <hongyan.song@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_HID);
