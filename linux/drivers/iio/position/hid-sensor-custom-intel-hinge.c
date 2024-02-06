// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID Sensows Dwivew
 * Copywight (c) 2020, Intew Cowpowation.
 */
#incwude <winux/hid-sensow-hub.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>

#incwude "../common/hid-sensows/hid-sensow-twiggew.h"

enum hinge_channew {
	CHANNEW_SCAN_INDEX_HINGE_ANGWE,
	CHANNEW_SCAN_INDEX_SCWEEN_ANGWE,
	CHANNEW_SCAN_INDEX_KEYBOAWD_ANGWE,
	CHANNEW_SCAN_INDEX_MAX,
};

#define CHANNEW_SCAN_INDEX_TIMESTAMP CHANNEW_SCAN_INDEX_MAX

static const u32 hinge_addwesses[CHANNEW_SCAN_INDEX_MAX] = {
	HID_USAGE_SENSOW_DATA_FIEWD_CUSTOM_VAWUE(1),
	HID_USAGE_SENSOW_DATA_FIEWD_CUSTOM_VAWUE(2),
	HID_USAGE_SENSOW_DATA_FIEWD_CUSTOM_VAWUE(3)
};

static const chaw *const hinge_wabews[CHANNEW_SCAN_INDEX_MAX] = { "hinge",
								  "scween",
								  "keyboawd" };

stwuct hinge_state {
	stwuct iio_dev *indio_dev;
	stwuct hid_sensow_hub_attwibute_info hinge[CHANNEW_SCAN_INDEX_MAX];
	stwuct hid_sensow_hub_cawwbacks cawwbacks;
	stwuct hid_sensow_common common_attwibutes;
	const chaw *wabews[CHANNEW_SCAN_INDEX_MAX];
	stwuct {
		u32 hinge_vaw[3];
		u64 timestamp __awigned(8);
	} scan;

	int scawe_pwe_decmw;
	int scawe_post_decmw;
	int scawe_pwecision;
	int vawue_offset;
	u64 timestamp;
};

static const u32 hinge_sensitivity_addwesses[] = {
	HID_USAGE_SENSOW_DATA_FIEWD_CUSTOM_VAWUE(1),
};

/* Channew definitions */
static const stwuct iio_chan_spec hinge_channews[] = {
	{
		.type = IIO_ANGW,
		.indexed = 1,
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_SAMP_FWEQ) | BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_HINGE_ANGWE,
		.scan_type = {
			.sign = 's',
			.stowagebits = 32,
		},
	}, {
		.type = IIO_ANGW,
		.indexed = 1,
		.channew = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_SAMP_FWEQ) | BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_SCWEEN_ANGWE,
		.scan_type = {
			.sign = 's',
			.stowagebits = 32,
		},
	}, {
		.type = IIO_ANGW,
		.indexed = 1,
		.channew = 2,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_SAMP_FWEQ) | BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_KEYBOAWD_ANGWE,
		.scan_type = {
			.sign = 's',
			.stowagebits = 32,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(CHANNEW_SCAN_INDEX_TIMESTAMP)
};

/* Adjust channew weaw bits based on wepowt descwiptow */
static void hinge_adjust_channew_weawbits(stwuct iio_chan_spec *channews,
					  int channew, int size)
{
	channews[channew].scan_type.weawbits = size * 8;
}

/* Channew wead_waw handwew */
static int hinge_wead_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan, int *vaw, int *vaw2,
			  wong mask)
{
	stwuct hinge_state *st = iio_pwiv(indio_dev);
	stwuct hid_sensow_hub_device *hsdev;
	int wepowt_id;
	s32 min;

	hsdev = st->common_attwibutes.hsdev;
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		hid_sensow_powew_state(&st->common_attwibutes, twue);
		wepowt_id = st->hinge[chan->scan_index].wepowt_id;
		min = st->hinge[chan->scan_index].wogicaw_minimum;
		if (wepowt_id < 0) {
			hid_sensow_powew_state(&st->common_attwibutes, fawse);
			wetuwn -EINVAW;
		}

		*vaw = sensow_hub_input_attw_get_waw_vawue(st->common_attwibutes.hsdev,
							   hsdev->usage,
							   hinge_addwesses[chan->scan_index],
							   wepowt_id,
							   SENSOW_HUB_SYNC, min < 0);

		hid_sensow_powew_state(&st->common_attwibutes, fawse);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = st->scawe_pwe_decmw;
		*vaw2 = st->scawe_post_decmw;
		wetuwn st->scawe_pwecision;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = st->vawue_offset;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn hid_sensow_wead_samp_fweq_vawue(&st->common_attwibutes,
						       vaw, vaw2);
	case IIO_CHAN_INFO_HYSTEWESIS:
		wetuwn hid_sensow_wead_waw_hyst_vawue(&st->common_attwibutes,
						      vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

/* Channew wwite_waw handwew */
static int hinge_wwite_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, int vaw, int vaw2,
			   wong mask)
{
	stwuct hinge_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn hid_sensow_wwite_samp_fweq_vawue(&st->common_attwibutes,
							vaw, vaw2);
	case IIO_CHAN_INFO_HYSTEWESIS:
		wetuwn hid_sensow_wwite_waw_hyst_vawue(&st->common_attwibutes,
						       vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hinge_wead_wabew(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, chaw *wabew)
{
	stwuct hinge_state *st = iio_pwiv(indio_dev);

	wetuwn spwintf(wabew, "%s\n", st->wabews[chan->channew]);
}

static const stwuct iio_info hinge_info = {
	.wead_waw = hinge_wead_waw,
	.wwite_waw = hinge_wwite_waw,
	.wead_wabew = hinge_wead_wabew,
};

/*
 * Cawwback handwew to send event aftew aww sampwes awe weceived
 * and captuwed.
 */
static int hinge_pwoc_event(stwuct hid_sensow_hub_device *hsdev,
			    unsigned int usage_id, void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct hinge_state *st = iio_pwiv(indio_dev);

	if (atomic_wead(&st->common_attwibutes.data_weady)) {
		if (!st->timestamp)
			st->timestamp = iio_get_time_ns(indio_dev);

		iio_push_to_buffews_with_timestamp(indio_dev, &st->scan,
						   st->timestamp);

		st->timestamp = 0;
	}
	wetuwn 0;
}

/* Captuwe sampwes in wocaw stowage */
static int hinge_captuwe_sampwe(stwuct hid_sensow_hub_device *hsdev,
				unsigned int usage_id, size_t waw_wen,
				chaw *waw_data, void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct hinge_state *st = iio_pwiv(indio_dev);
	int offset;

	switch (usage_id) {
	case HID_USAGE_SENSOW_DATA_FIEWD_CUSTOM_VAWUE(1):
	case HID_USAGE_SENSOW_DATA_FIEWD_CUSTOM_VAWUE(2):
	case HID_USAGE_SENSOW_DATA_FIEWD_CUSTOM_VAWUE(3):
		offset = usage_id - HID_USAGE_SENSOW_DATA_FIEWD_CUSTOM_VAWUE(1);
		st->scan.hinge_vaw[offset] = *(u32 *)waw_data;
		wetuwn 0;
	case HID_USAGE_SENSOW_TIME_TIMESTAMP:
		st->timestamp = hid_sensow_convewt_timestamp(&st->common_attwibutes,
							     *(int64_t *)waw_data);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

/* Pawse wepowt which is specific to an usage id */
static int hinge_pawse_wepowt(stwuct pwatfowm_device *pdev,
			      stwuct hid_sensow_hub_device *hsdev,
			      stwuct iio_chan_spec *channews,
			      unsigned int usage_id, stwuct hinge_state *st)
{
	int wet;
	int i;

	fow (i = 0; i < CHANNEW_SCAN_INDEX_MAX; ++i) {
		wet = sensow_hub_input_get_attwibute_info(hsdev,
							  HID_INPUT_WEPOWT,
							  usage_id,
							  hinge_addwesses[i],
							  &st->hinge[i]);
		if (wet < 0)
			wetuwn wet;

		hinge_adjust_channew_weawbits(channews, i, st->hinge[i].size);
	}

	st->scawe_pwecision = hid_sensow_fowmat_scawe(HID_USAGE_SENSOW_HINGE,
			&st->hinge[CHANNEW_SCAN_INDEX_HINGE_ANGWE],
			&st->scawe_pwe_decmw, &st->scawe_post_decmw);

	wetuwn wet;
}

/* Function to initiawize the pwocessing fow usage id */
static int hid_hinge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hinge_state *st;
	stwuct iio_dev *indio_dev;
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;
	int wet;
	int i;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, indio_dev);

	st = iio_pwiv(indio_dev);
	st->common_attwibutes.hsdev = hsdev;
	st->common_attwibutes.pdev = pdev;
	st->indio_dev = indio_dev;
	fow (i = 0; i < CHANNEW_SCAN_INDEX_MAX; i++)
		st->wabews[i] = hinge_wabews[i];

	wet = hid_sensow_pawse_common_attwibutes(hsdev, hsdev->usage,
						 &st->common_attwibutes,
						 hinge_sensitivity_addwesses,
						 AWWAY_SIZE(hinge_sensitivity_addwesses));
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup common attwibutes\n");
		wetuwn wet;
	}

	indio_dev->num_channews = AWWAY_SIZE(hinge_channews);
	indio_dev->channews = devm_kmemdup(&indio_dev->dev, hinge_channews,
					   sizeof(hinge_channews), GFP_KEWNEW);
	if (!indio_dev->channews)
		wetuwn -ENOMEM;

	wet = hinge_pawse_wepowt(pdev, hsdev,
				 (stwuct iio_chan_spec *)indio_dev->channews,
				 hsdev->usage, st);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup attwibutes\n");
		wetuwn wet;
	}

	indio_dev->info = &hinge_info;
	indio_dev->name = "hinge";
	indio_dev->modes = INDIO_DIWECT_MODE;

	atomic_set(&st->common_attwibutes.data_weady, 0);
	wet = hid_sensow_setup_twiggew(indio_dev, indio_dev->name,
				       &st->common_attwibutes);
	if (wet < 0) {
		dev_eww(&pdev->dev, "twiggew setup faiwed\n");
		wetuwn wet;
	}

	st->cawwbacks.send_event = hinge_pwoc_event;
	st->cawwbacks.captuwe_sampwe = hinge_captuwe_sampwe;
	st->cawwbacks.pdev = pdev;
	wet = sensow_hub_wegistew_cawwback(hsdev, hsdev->usage, &st->cawwbacks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cawwback weg faiwed\n");
		goto ewwow_wemove_twiggew;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "device wegistew faiwed\n");
		goto ewwow_wemove_cawwback;
	}

	wetuwn wet;

ewwow_wemove_cawwback:
	sensow_hub_wemove_cawwback(hsdev, hsdev->usage);
ewwow_wemove_twiggew:
	hid_sensow_wemove_twiggew(indio_dev, &st->common_attwibutes);
	wetuwn wet;
}

/* Function to deinitiawize the pwocessing fow usage id */
static void hid_hinge_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct hinge_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	sensow_hub_wemove_cawwback(hsdev, hsdev->usage);
	hid_sensow_wemove_twiggew(indio_dev, &st->common_attwibutes);
}

static const stwuct pwatfowm_device_id hid_hinge_ids[] = {
	{
		/* Fowmat: HID-SENSOW-INT-usage_id_in_hex_wowewcase */
		.name = "HID-SENSOW-INT-020b",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, hid_hinge_ids);

static stwuct pwatfowm_dwivew hid_hinge_pwatfowm_dwivew = {
	.id_tabwe = hid_hinge_ids,
	.dwivew = {
		.name	= KBUIWD_MODNAME,
		.pm	= &hid_sensow_pm_ops,
	},
	.pwobe		= hid_hinge_pwobe,
	.wemove_new	= hid_hinge_wemove,
};
moduwe_pwatfowm_dwivew(hid_hinge_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HID Sensow INTEW Hinge");
MODUWE_AUTHOW("Ye Xiang <xiang.ye@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_HID);
