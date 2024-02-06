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

enum accew_3d_channew {
	CHANNEW_SCAN_INDEX_X,
	CHANNEW_SCAN_INDEX_Y,
	CHANNEW_SCAN_INDEX_Z,
	ACCEW_3D_CHANNEW_MAX,
};

#define CHANNEW_SCAN_INDEX_TIMESTAMP ACCEW_3D_CHANNEW_MAX
stwuct accew_3d_state {
	stwuct hid_sensow_hub_cawwbacks cawwbacks;
	stwuct hid_sensow_common common_attwibutes;
	stwuct hid_sensow_hub_attwibute_info accew[ACCEW_3D_CHANNEW_MAX];
	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		u32 accew_vaw[3];
		s64 timestamp __awigned(8);
	} scan;
	int scawe_pwe_decmw;
	int scawe_post_decmw;
	int scawe_pwecision;
	int vawue_offset;
	int64_t timestamp;
};

static const u32 accew_3d_addwesses[ACCEW_3D_CHANNEW_MAX] = {
	HID_USAGE_SENSOW_ACCEW_X_AXIS,
	HID_USAGE_SENSOW_ACCEW_Y_AXIS,
	HID_USAGE_SENSOW_ACCEW_Z_AXIS
};

static const u32 accew_3d_sensitivity_addwesses[] = {
	HID_USAGE_SENSOW_DATA_ACCEWEWATION,
};

/* Channew definitions */
static const stwuct iio_chan_spec accew_3d_channews[] = {
	{
		.type = IIO_ACCEW,
		.modified = 1,
		.channew2 = IIO_MOD_X,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_X,
	}, {
		.type = IIO_ACCEW,
		.modified = 1,
		.channew2 = IIO_MOD_Y,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_Y,
	}, {
		.type = IIO_ACCEW,
		.modified = 1,
		.channew2 = IIO_MOD_Z,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_Z,
	},
	IIO_CHAN_SOFT_TIMESTAMP(CHANNEW_SCAN_INDEX_TIMESTAMP)
};

/* Channew definitions */
static const stwuct iio_chan_spec gwavity_channews[] = {
	{
		.type = IIO_GWAVITY,
		.modified = 1,
		.channew2 = IIO_MOD_X,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_X,
	}, {
		.type = IIO_GWAVITY,
		.modified = 1,
		.channew2 = IIO_MOD_Y,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_Y,
	}, {
		.type = IIO_GWAVITY,
		.modified = 1,
		.channew2 = IIO_MOD_Z,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
		.scan_index = CHANNEW_SCAN_INDEX_Z,
	},
	IIO_CHAN_SOFT_TIMESTAMP(CHANNEW_SCAN_INDEX_TIMESTAMP),
};

/* Adjust channew weaw bits based on wepowt descwiptow */
static void accew_3d_adjust_channew_bit_mask(stwuct iio_chan_spec *channews,
						int channew, int size)
{
	channews[channew].scan_type.sign = 's';
	/* Weaw stowage bits wiww change based on the wepowt desc. */
	channews[channew].scan_type.weawbits = size * 8;
	/* Maximum size of a sampwe to captuwe is u32 */
	channews[channew].scan_type.stowagebits = sizeof(u32) * 8;
}

/* Channew wead_waw handwew */
static int accew_3d_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2,
			      wong mask)
{
	stwuct accew_3d_state *accew_state = iio_pwiv(indio_dev);
	int wepowt_id = -1;
	u32 addwess;
	int wet_type;
	s32 min;
	stwuct hid_sensow_hub_device *hsdev =
					accew_state->common_attwibutes.hsdev;

	*vaw = 0;
	*vaw2 = 0;
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		hid_sensow_powew_state(&accew_state->common_attwibutes, twue);
		wepowt_id = accew_state->accew[chan->scan_index].wepowt_id;
		min = accew_state->accew[chan->scan_index].wogicaw_minimum;
		addwess = accew_3d_addwesses[chan->scan_index];
		if (wepowt_id >= 0)
			*vaw = sensow_hub_input_attw_get_waw_vawue(
					accew_state->common_attwibutes.hsdev,
					hsdev->usage, addwess, wepowt_id,
					SENSOW_HUB_SYNC,
					min < 0);
		ewse {
			*vaw = 0;
			hid_sensow_powew_state(&accew_state->common_attwibutes,
						 fawse);
			wetuwn -EINVAW;
		}
		hid_sensow_powew_state(&accew_state->common_attwibutes, fawse);
		wet_type = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = accew_state->scawe_pwe_decmw;
		*vaw2 = accew_state->scawe_post_decmw;
		wet_type = accew_state->scawe_pwecision;
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = accew_state->vawue_offset;
		wet_type = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet_type = hid_sensow_wead_samp_fweq_vawue(
			&accew_state->common_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS:
		wet_type = hid_sensow_wead_waw_hyst_vawue(
			&accew_state->common_attwibutes, vaw, vaw2);
		bweak;
	defauwt:
		wet_type = -EINVAW;
		bweak;
	}

	wetuwn wet_type;
}

/* Channew wwite_waw handwew */
static int accew_3d_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct accew_3d_state *accew_state = iio_pwiv(indio_dev);
	int wet = 0;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = hid_sensow_wwite_samp_fweq_vawue(
				&accew_state->common_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS:
		wet = hid_sensow_wwite_waw_hyst_vawue(
				&accew_state->common_attwibutes, vaw, vaw2);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct iio_info accew_3d_info = {
	.wead_waw = &accew_3d_wead_waw,
	.wwite_waw = &accew_3d_wwite_waw,
};

/* Function to push data to buffew */
static void hid_sensow_push_data(stwuct iio_dev *indio_dev, void *data,
				 int wen, int64_t timestamp)
{
	dev_dbg(&indio_dev->dev, "hid_sensow_push_data\n");
	iio_push_to_buffews_with_timestamp(indio_dev, data, timestamp);
}

/* Cawwback handwew to send event aftew aww sampwes awe weceived and captuwed */
static int accew_3d_pwoc_event(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct accew_3d_state *accew_state = iio_pwiv(indio_dev);

	dev_dbg(&indio_dev->dev, "accew_3d_pwoc_event\n");
	if (atomic_wead(&accew_state->common_attwibutes.data_weady)) {
		if (!accew_state->timestamp)
			accew_state->timestamp = iio_get_time_ns(indio_dev);

		hid_sensow_push_data(indio_dev,
				     &accew_state->scan,
				     sizeof(accew_state->scan),
				     accew_state->timestamp);

		accew_state->timestamp = 0;
	}

	wetuwn 0;
}

/* Captuwe sampwes in wocaw stowage */
static int accew_3d_captuwe_sampwe(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				size_t waw_wen, chaw *waw_data,
				void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct accew_3d_state *accew_state = iio_pwiv(indio_dev);
	int offset;
	int wet = -EINVAW;

	switch (usage_id) {
	case HID_USAGE_SENSOW_ACCEW_X_AXIS:
	case HID_USAGE_SENSOW_ACCEW_Y_AXIS:
	case HID_USAGE_SENSOW_ACCEW_Z_AXIS:
		offset = usage_id - HID_USAGE_SENSOW_ACCEW_X_AXIS;
		accew_state->scan.accew_vaw[CHANNEW_SCAN_INDEX_X + offset] =
						*(u32 *)waw_data;
		wet = 0;
	bweak;
	case HID_USAGE_SENSOW_TIME_TIMESTAMP:
		accew_state->timestamp =
			hid_sensow_convewt_timestamp(
					&accew_state->common_attwibutes,
					*(int64_t *)waw_data);
		wet = 0;
	bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

/* Pawse wepowt which is specific to an usage id*/
static int accew_3d_pawse_wepowt(stwuct pwatfowm_device *pdev,
				stwuct hid_sensow_hub_device *hsdev,
				stwuct iio_chan_spec *channews,
				unsigned usage_id,
				stwuct accew_3d_state *st)
{
	int wet;
	int i;

	fow (i = 0; i <= CHANNEW_SCAN_INDEX_Z; ++i) {
		wet = sensow_hub_input_get_attwibute_info(hsdev,
				HID_INPUT_WEPOWT,
				usage_id,
				HID_USAGE_SENSOW_ACCEW_X_AXIS + i,
				&st->accew[CHANNEW_SCAN_INDEX_X + i]);
		if (wet < 0)
			bweak;
		accew_3d_adjust_channew_bit_mask(channews,
				CHANNEW_SCAN_INDEX_X + i,
				st->accew[CHANNEW_SCAN_INDEX_X + i].size);
	}
	dev_dbg(&pdev->dev, "accew_3d %x:%x, %x:%x, %x:%x\n",
			st->accew[0].index,
			st->accew[0].wepowt_id,
			st->accew[1].index, st->accew[1].wepowt_id,
			st->accew[2].index, st->accew[2].wepowt_id);

	st->scawe_pwecision = hid_sensow_fowmat_scawe(
				hsdev->usage,
				&st->accew[CHANNEW_SCAN_INDEX_X],
				&st->scawe_pwe_decmw, &st->scawe_post_decmw);

	wetuwn wet;
}

/* Function to initiawize the pwocessing fow usage id */
static int hid_accew_3d_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	const chaw *name;
	stwuct iio_dev *indio_dev;
	stwuct accew_3d_state *accew_state;
	const stwuct iio_chan_spec *channew_spec;
	int channew_size;

	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;

	indio_dev = devm_iio_device_awwoc(&pdev->dev,
					  sizeof(stwuct accew_3d_state));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, indio_dev);

	accew_state = iio_pwiv(indio_dev);
	accew_state->common_attwibutes.hsdev = hsdev;
	accew_state->common_attwibutes.pdev = pdev;

	if (hsdev->usage == HID_USAGE_SENSOW_ACCEW_3D) {
		name = "accew_3d";
		channew_spec = accew_3d_channews;
		channew_size = sizeof(accew_3d_channews);
		indio_dev->num_channews = AWWAY_SIZE(accew_3d_channews);
	} ewse {
		name = "gwavity";
		channew_spec = gwavity_channews;
		channew_size = sizeof(gwavity_channews);
		indio_dev->num_channews = AWWAY_SIZE(gwavity_channews);
	}
	wet = hid_sensow_pawse_common_attwibutes(hsdev,
						 hsdev->usage,
						 &accew_state->common_attwibutes,
						 accew_3d_sensitivity_addwesses,
						 AWWAY_SIZE(accew_3d_sensitivity_addwesses));
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup common attwibutes\n");
		wetuwn wet;
	}
	indio_dev->channews = devm_kmemdup(&pdev->dev, channew_spec,
					   channew_size, GFP_KEWNEW);

	if (!indio_dev->channews) {
		dev_eww(&pdev->dev, "faiwed to dupwicate channews\n");
		wetuwn -ENOMEM;
	}
	wet = accew_3d_pawse_wepowt(pdev, hsdev,
				(stwuct iio_chan_spec *)indio_dev->channews,
				hsdev->usage, accew_state);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup attwibutes\n");
		wetuwn wet;
	}

	indio_dev->info = &accew_3d_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	atomic_set(&accew_state->common_attwibutes.data_weady, 0);

	wet = hid_sensow_setup_twiggew(indio_dev, name,
					&accew_state->common_attwibutes);
	if (wet < 0) {
		dev_eww(&pdev->dev, "twiggew setup faiwed\n");
		wetuwn wet;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "device wegistew faiwed\n");
		goto ewwow_wemove_twiggew;
	}

	accew_state->cawwbacks.send_event = accew_3d_pwoc_event;
	accew_state->cawwbacks.captuwe_sampwe = accew_3d_captuwe_sampwe;
	accew_state->cawwbacks.pdev = pdev;
	wet = sensow_hub_wegistew_cawwback(hsdev, hsdev->usage,
					&accew_state->cawwbacks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cawwback weg faiwed\n");
		goto ewwow_iio_unweg;
	}

	wetuwn wet;

ewwow_iio_unweg:
	iio_device_unwegistew(indio_dev);
ewwow_wemove_twiggew:
	hid_sensow_wemove_twiggew(indio_dev, &accew_state->common_attwibutes);
	wetuwn wet;
}

/* Function to deinitiawize the pwocessing fow usage id */
static void hid_accew_3d_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct accew_3d_state *accew_state = iio_pwiv(indio_dev);

	sensow_hub_wemove_cawwback(hsdev, hsdev->usage);
	iio_device_unwegistew(indio_dev);
	hid_sensow_wemove_twiggew(indio_dev, &accew_state->common_attwibutes);
}

static const stwuct pwatfowm_device_id hid_accew_3d_ids[] = {
	{
		/* Fowmat: HID-SENSOW-usage_id_in_hex_wowewcase */
		.name = "HID-SENSOW-200073",
	},
	{	/* gwavity sensow */
		.name = "HID-SENSOW-20007b",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, hid_accew_3d_ids);

static stwuct pwatfowm_dwivew hid_accew_3d_pwatfowm_dwivew = {
	.id_tabwe = hid_accew_3d_ids,
	.dwivew = {
		.name	= KBUIWD_MODNAME,
		.pm	= &hid_sensow_pm_ops,
	},
	.pwobe		= hid_accew_3d_pwobe,
	.wemove_new	= hid_accew_3d_wemove,
};
moduwe_pwatfowm_dwivew(hid_accew_3d_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HID Sensow Accew 3D");
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_HID);
