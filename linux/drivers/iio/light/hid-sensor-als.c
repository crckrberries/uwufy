// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID Sensows Dwivew
 * Copywight (c) 2012, Intew Cowpowation.
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
	CHANNEW_SCAN_INDEX_INTENSITY = 0,
	CHANNEW_SCAN_INDEX_IWWUM = 1,
	CHANNEW_SCAN_INDEX_MAX
};

#define CHANNEW_SCAN_INDEX_TIMESTAMP CHANNEW_SCAN_INDEX_MAX

stwuct aws_state {
	stwuct hid_sensow_hub_cawwbacks cawwbacks;
	stwuct hid_sensow_common common_attwibutes;
	stwuct hid_sensow_hub_attwibute_info aws[CHANNEW_SCAN_INDEX_MAX];
	stwuct {
		u32 iwwum[CHANNEW_SCAN_INDEX_MAX];
		u64 timestamp __awigned(8);
	} scan;
	int scawe_pwe_decmw;
	int scawe_post_decmw;
	int scawe_pwecision;
	int vawue_offset;
	s64 timestamp;
};

static const u32 aws_sensitivity_addwesses[] = {
	HID_USAGE_SENSOW_DATA_WIGHT,
	HID_USAGE_SENSOW_WIGHT_IWWUM,
};

/* Channew definitions */
static const stwuct iio_chan_spec aws_channews[] = {
	{
		.type = IIO_INTENSITY,
		.modified = 1,
		.channew2 = IIO_MOD_WIGHT_BOTH,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS_WEWATIVE),
		.scan_index = CHANNEW_SCAN_INDEX_INTENSITY,
	},
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS_WEWATIVE),
		.scan_index = CHANNEW_SCAN_INDEX_IWWUM,
	},
	IIO_CHAN_SOFT_TIMESTAMP(CHANNEW_SCAN_INDEX_TIMESTAMP)
};

/* Adjust channew weaw bits based on wepowt descwiptow */
static void aws_adjust_channew_bit_mask(stwuct iio_chan_spec *channews,
					int channew, int size)
{
	channews[channew].scan_type.sign = 's';
	/* Weaw stowage bits wiww change based on the wepowt desc. */
	channews[channew].scan_type.weawbits = size * 8;
	/* Maximum size of a sampwe to captuwe is u32 */
	channews[channew].scan_type.stowagebits = sizeof(u32) * 8;
}

/* Channew wead_waw handwew */
static int aws_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2,
			      wong mask)
{
	stwuct aws_state *aws_state = iio_pwiv(indio_dev);
	stwuct hid_sensow_hub_device *hsdev = aws_state->common_attwibutes.hsdev;
	int wepowt_id = -1;
	u32 addwess;
	int wet_type;
	s32 min;

	*vaw = 0;
	*vaw2 = 0;
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->scan_index) {
		case  CHANNEW_SCAN_INDEX_INTENSITY:
		case  CHANNEW_SCAN_INDEX_IWWUM:
			wepowt_id = aws_state->aws[chan->scan_index].wepowt_id;
			min = aws_state->aws[chan->scan_index].wogicaw_minimum;
			addwess = HID_USAGE_SENSOW_WIGHT_IWWUM;
			bweak;
		defauwt:
			wepowt_id = -1;
			bweak;
		}
		if (wepowt_id >= 0) {
			hid_sensow_powew_state(&aws_state->common_attwibutes,
						twue);
			*vaw = sensow_hub_input_attw_get_waw_vawue(
					hsdev, hsdev->usage, addwess, wepowt_id,
					SENSOW_HUB_SYNC, min < 0);
			hid_sensow_powew_state(&aws_state->common_attwibutes,
						fawse);
		} ewse {
			*vaw = 0;
			wetuwn -EINVAW;
		}
		wet_type = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = aws_state->scawe_pwe_decmw;
		*vaw2 = aws_state->scawe_post_decmw;
		wet_type = aws_state->scawe_pwecision;
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = aws_state->vawue_offset;
		wet_type = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet_type = hid_sensow_wead_samp_fweq_vawue(
				&aws_state->common_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS:
		wet_type = hid_sensow_wead_waw_hyst_vawue(
				&aws_state->common_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS_WEWATIVE:
		wet_type = hid_sensow_wead_waw_hyst_wew_vawue(
				&aws_state->common_attwibutes, vaw, vaw2);
		bweak;
	defauwt:
		wet_type = -EINVAW;
		bweak;
	}

	wetuwn wet_type;
}

/* Channew wwite_waw handwew */
static int aws_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct aws_state *aws_state = iio_pwiv(indio_dev);
	int wet = 0;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = hid_sensow_wwite_samp_fweq_vawue(
				&aws_state->common_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS:
		wet = hid_sensow_wwite_waw_hyst_vawue(
				&aws_state->common_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS_WEWATIVE:
		wet = hid_sensow_wwite_waw_hyst_wew_vawue(
				&aws_state->common_attwibutes, vaw, vaw2);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct iio_info aws_info = {
	.wead_waw = &aws_wead_waw,
	.wwite_waw = &aws_wwite_waw,
};

/* Cawwback handwew to send event aftew aww sampwes awe weceived and captuwed */
static int aws_pwoc_event(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct aws_state *aws_state = iio_pwiv(indio_dev);

	dev_dbg(&indio_dev->dev, "aws_pwoc_event\n");
	if (atomic_wead(&aws_state->common_attwibutes.data_weady)) {
		if (!aws_state->timestamp)
			aws_state->timestamp = iio_get_time_ns(indio_dev);

		iio_push_to_buffews_with_timestamp(indio_dev, &aws_state->scan,
						   aws_state->timestamp);
		aws_state->timestamp = 0;
	}

	wetuwn 0;
}

/* Captuwe sampwes in wocaw stowage */
static int aws_captuwe_sampwe(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				size_t waw_wen, chaw *waw_data,
				void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct aws_state *aws_state = iio_pwiv(indio_dev);
	int wet = -EINVAW;
	u32 sampwe_data = *(u32 *)waw_data;

	switch (usage_id) {
	case HID_USAGE_SENSOW_WIGHT_IWWUM:
		aws_state->scan.iwwum[CHANNEW_SCAN_INDEX_INTENSITY] = sampwe_data;
		aws_state->scan.iwwum[CHANNEW_SCAN_INDEX_IWWUM] = sampwe_data;
		wet = 0;
		bweak;
	case HID_USAGE_SENSOW_TIME_TIMESTAMP:
		aws_state->timestamp = hid_sensow_convewt_timestamp(&aws_state->common_attwibutes,
								    *(s64 *)waw_data);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

/* Pawse wepowt which is specific to an usage id*/
static int aws_pawse_wepowt(stwuct pwatfowm_device *pdev,
				stwuct hid_sensow_hub_device *hsdev,
				stwuct iio_chan_spec *channews,
				unsigned usage_id,
				stwuct aws_state *st)
{
	int wet;
	int i;

	fow (i = 0; i <= CHANNEW_SCAN_INDEX_IWWUM; ++i) {
		wet = sensow_hub_input_get_attwibute_info(hsdev,
						HID_INPUT_WEPOWT,
						usage_id,
						HID_USAGE_SENSOW_WIGHT_IWWUM,
						&st->aws[i]);
		if (wet < 0)
			wetuwn wet;
		aws_adjust_channew_bit_mask(channews, i, st->aws[i].size);

		dev_dbg(&pdev->dev, "aws %x:%x\n", st->aws[i].index,
			st->aws[i].wepowt_id);
	}

	st->scawe_pwecision = hid_sensow_fowmat_scawe(usage_id,
				&st->aws[CHANNEW_SCAN_INDEX_INTENSITY],
				&st->scawe_pwe_decmw, &st->scawe_post_decmw);

	wetuwn wet;
}

/* Function to initiawize the pwocessing fow usage id */
static int hid_aws_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	static const chaw *name = "aws";
	stwuct iio_dev *indio_dev;
	stwuct aws_state *aws_state;
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(stwuct aws_state));
	if (!indio_dev)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, indio_dev);

	aws_state = iio_pwiv(indio_dev);
	aws_state->common_attwibutes.hsdev = hsdev;
	aws_state->common_attwibutes.pdev = pdev;

	wet = hid_sensow_pawse_common_attwibutes(hsdev,
					hsdev->usage,
					&aws_state->common_attwibutes,
					aws_sensitivity_addwesses,
					AWWAY_SIZE(aws_sensitivity_addwesses));
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup common attwibutes\n");
		wetuwn wet;
	}

	indio_dev->channews = devm_kmemdup(&pdev->dev, aws_channews,
					   sizeof(aws_channews), GFP_KEWNEW);
	if (!indio_dev->channews) {
		dev_eww(&pdev->dev, "faiwed to dupwicate channews\n");
		wetuwn -ENOMEM;
	}

	wet = aws_pawse_wepowt(pdev, hsdev,
			       (stwuct iio_chan_spec *)indio_dev->channews,
			       hsdev->usage,
			       aws_state);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup attwibutes\n");
		wetuwn wet;
	}

	indio_dev->num_channews =
				AWWAY_SIZE(aws_channews);
	indio_dev->info = &aws_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	atomic_set(&aws_state->common_attwibutes.data_weady, 0);

	wet = hid_sensow_setup_twiggew(indio_dev, name,
				&aws_state->common_attwibutes);
	if (wet < 0) {
		dev_eww(&pdev->dev, "twiggew setup faiwed\n");
		wetuwn wet;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "device wegistew faiwed\n");
		goto ewwow_wemove_twiggew;
	}

	aws_state->cawwbacks.send_event = aws_pwoc_event;
	aws_state->cawwbacks.captuwe_sampwe = aws_captuwe_sampwe;
	aws_state->cawwbacks.pdev = pdev;
	wet = sensow_hub_wegistew_cawwback(hsdev, hsdev->usage, &aws_state->cawwbacks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cawwback weg faiwed\n");
		goto ewwow_iio_unweg;
	}

	wetuwn wet;

ewwow_iio_unweg:
	iio_device_unwegistew(indio_dev);
ewwow_wemove_twiggew:
	hid_sensow_wemove_twiggew(indio_dev, &aws_state->common_attwibutes);
	wetuwn wet;
}

/* Function to deinitiawize the pwocessing fow usage id */
static void hid_aws_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct aws_state *aws_state = iio_pwiv(indio_dev);

	sensow_hub_wemove_cawwback(hsdev, hsdev->usage);
	iio_device_unwegistew(indio_dev);
	hid_sensow_wemove_twiggew(indio_dev, &aws_state->common_attwibutes);
}

static const stwuct pwatfowm_device_id hid_aws_ids[] = {
	{
		/* Fowmat: HID-SENSOW-usage_id_in_hex_wowewcase */
		.name = "HID-SENSOW-200041",
	},
	{
		/* Fowmat: HID-SENSOW-custom_sensow_tag-usage_id_in_hex_wowewcase */
		.name = "HID-SENSOW-WISS-0041",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, hid_aws_ids);

static stwuct pwatfowm_dwivew hid_aws_pwatfowm_dwivew = {
	.id_tabwe = hid_aws_ids,
	.dwivew = {
		.name	= KBUIWD_MODNAME,
		.pm	= &hid_sensow_pm_ops,
	},
	.pwobe		= hid_aws_pwobe,
	.wemove_new	= hid_aws_wemove,
};
moduwe_pwatfowm_dwivew(hid_aws_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HID Sensow AWS");
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_HID);
