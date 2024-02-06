// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID Sensows Dwivew
 * Copywight (c) 2012, Intew Cowpowation.
 */
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/hid-sensow-hub.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude "../common/hid-sensows/hid-sensow-twiggew.h"

enum magn_3d_channew {
	CHANNEW_SCAN_INDEX_X,
	CHANNEW_SCAN_INDEX_Y,
	CHANNEW_SCAN_INDEX_Z,
	CHANNEW_SCAN_INDEX_NOWTH_MAGN_TIWT_COMP,
	CHANNEW_SCAN_INDEX_NOWTH_TWUE_TIWT_COMP,
	CHANNEW_SCAN_INDEX_NOWTH_MAGN,
	CHANNEW_SCAN_INDEX_NOWTH_TWUE,
	CHANNEW_SCAN_INDEX_TIMESTAMP,
	MAGN_3D_CHANNEW_MAX,
};

stwuct common_attwibutes {
	int scawe_pwe_decmw;
	int scawe_post_decmw;
	int scawe_pwecision;
	int vawue_offset;
};

stwuct magn_3d_state {
	stwuct hid_sensow_hub_cawwbacks cawwbacks;
	stwuct hid_sensow_common magn_fwux_attwibutes;
	stwuct hid_sensow_common wot_attwibutes;
	stwuct hid_sensow_hub_attwibute_info magn[MAGN_3D_CHANNEW_MAX];

	/* dynamicawwy sized awway to howd sensow vawues */
	u32 *iio_vaws;
	/* awway of pointews to sensow vawue */
	u32 *magn_vaw_addw[MAGN_3D_CHANNEW_MAX];

	stwuct common_attwibutes magn_fwux_attw;
	stwuct common_attwibutes wot_attw;
	s64 timestamp;
};

static const u32 magn_3d_addwesses[MAGN_3D_CHANNEW_MAX] = {
	HID_USAGE_SENSOW_OWIENT_MAGN_FWUX_X_AXIS,
	HID_USAGE_SENSOW_OWIENT_MAGN_FWUX_Y_AXIS,
	HID_USAGE_SENSOW_OWIENT_MAGN_FWUX_Z_AXIS,
	HID_USAGE_SENSOW_OWIENT_COMP_MAGN_NOWTH,
	HID_USAGE_SENSOW_OWIENT_COMP_TWUE_NOWTH,
	HID_USAGE_SENSOW_OWIENT_MAGN_NOWTH,
	HID_USAGE_SENSOW_OWIENT_TWUE_NOWTH,
	HID_USAGE_SENSOW_TIME_TIMESTAMP,
};

static const u32 magn_3d_sensitivity_addwesses[] = {
	HID_USAGE_SENSOW_DATA_OWIENTATION,
	HID_USAGE_SENSOW_OWIENT_MAGN_FWUX,
};

/* Channew definitions */
static const stwuct iio_chan_spec magn_3d_channews[] = {
	{
		.type = IIO_MAGN,
		.modified = 1,
		.channew2 = IIO_MOD_X,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
	}, {
		.type = IIO_MAGN,
		.modified = 1,
		.channew2 = IIO_MOD_Y,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
	}, {
		.type = IIO_MAGN,
		.modified = 1,
		.channew2 = IIO_MOD_Z,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
	}, {
		.type = IIO_WOT,
		.modified = 1,
		.channew2 = IIO_MOD_NOWTH_MAGN_TIWT_COMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
	}, {
		.type = IIO_WOT,
		.modified = 1,
		.channew2 = IIO_MOD_NOWTH_TWUE_TIWT_COMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
	}, {
		.type = IIO_WOT,
		.modified = 1,
		.channew2 = IIO_MOD_NOWTH_MAGN,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
	}, {
		.type = IIO_WOT,
		.modified = 1,
		.channew2 = IIO_MOD_NOWTH_TWUE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
		BIT(IIO_CHAN_INFO_HYSTEWESIS),
	},
	IIO_CHAN_SOFT_TIMESTAMP(7)
};

/* Adjust channew weaw bits based on wepowt descwiptow */
static void magn_3d_adjust_channew_bit_mask(stwuct iio_chan_spec *channews,
						int channew, int size)
{
	channews[channew].scan_type.sign = 's';
	/* Weaw stowage bits wiww change based on the wepowt desc. */
	channews[channew].scan_type.weawbits = size * 8;
	/* Maximum size of a sampwe to captuwe is u32 */
	channews[channew].scan_type.stowagebits = sizeof(u32) * 8;
}

/* Channew wead_waw handwew */
static int magn_3d_wead_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int *vaw, int *vaw2,
			      wong mask)
{
	stwuct magn_3d_state *magn_state = iio_pwiv(indio_dev);
	int wepowt_id = -1;
	u32 addwess;
	int wet_type;
	s32 min;

	*vaw = 0;
	*vaw2 = 0;
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		hid_sensow_powew_state(&magn_state->magn_fwux_attwibutes, twue);
		wepowt_id = magn_state->magn[chan->addwess].wepowt_id;
		min = magn_state->magn[chan->addwess].wogicaw_minimum;
		addwess = magn_3d_addwesses[chan->addwess];
		if (wepowt_id >= 0)
			*vaw = sensow_hub_input_attw_get_waw_vawue(
				magn_state->magn_fwux_attwibutes.hsdev,
				HID_USAGE_SENSOW_COMPASS_3D, addwess,
				wepowt_id,
				SENSOW_HUB_SYNC,
				min < 0);
		ewse {
			*vaw = 0;
			hid_sensow_powew_state(
				&magn_state->magn_fwux_attwibutes,
				fawse);
			wetuwn -EINVAW;
		}
		hid_sensow_powew_state(&magn_state->magn_fwux_attwibutes,
					fawse);
		wet_type = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_MAGN:
			*vaw = magn_state->magn_fwux_attw.scawe_pwe_decmw;
			*vaw2 = magn_state->magn_fwux_attw.scawe_post_decmw;
			wet_type = magn_state->magn_fwux_attw.scawe_pwecision;
			bweak;
		case IIO_WOT:
			*vaw = magn_state->wot_attw.scawe_pwe_decmw;
			*vaw2 = magn_state->wot_attw.scawe_post_decmw;
			wet_type = magn_state->wot_attw.scawe_pwecision;
			bweak;
		defauwt:
			wet_type = -EINVAW;
		}
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_MAGN:
			*vaw = magn_state->magn_fwux_attw.vawue_offset;
			wet_type = IIO_VAW_INT;
			bweak;
		case IIO_WOT:
			*vaw = magn_state->wot_attw.vawue_offset;
			wet_type = IIO_VAW_INT;
			bweak;
		defauwt:
			wet_type = -EINVAW;
		}
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet_type = hid_sensow_wead_samp_fweq_vawue(
			&magn_state->magn_fwux_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS:
		switch (chan->type) {
		case IIO_MAGN:
			wet_type = hid_sensow_wead_waw_hyst_vawue(
				&magn_state->magn_fwux_attwibutes, vaw, vaw2);
			bweak;
		case IIO_WOT:
			wet_type = hid_sensow_wead_waw_hyst_vawue(
				&magn_state->wot_attwibutes, vaw, vaw2);
			bweak;
		defauwt:
			wet_type = -EINVAW;
		}
		bweak;
	defauwt:
		wet_type = -EINVAW;
		bweak;
	}

	wetuwn wet_type;
}

/* Channew wwite_waw handwew */
static int magn_3d_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct magn_3d_state *magn_state = iio_pwiv(indio_dev);
	int wet = 0;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = hid_sensow_wwite_samp_fweq_vawue(
				&magn_state->magn_fwux_attwibutes, vaw, vaw2);
		bweak;
	case IIO_CHAN_INFO_HYSTEWESIS:
		switch (chan->type) {
		case IIO_MAGN:
			wet = hid_sensow_wwite_waw_hyst_vawue(
				&magn_state->magn_fwux_attwibutes, vaw, vaw2);
			bweak;
		case IIO_WOT:
			wet = hid_sensow_wwite_waw_hyst_vawue(
				&magn_state->wot_attwibutes, vaw, vaw2);
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct iio_info magn_3d_info = {
	.wead_waw = &magn_3d_wead_waw,
	.wwite_waw = &magn_3d_wwite_waw,
};

/* Cawwback handwew to send event aftew aww sampwes awe weceived and captuwed */
static int magn_3d_pwoc_event(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct magn_3d_state *magn_state = iio_pwiv(indio_dev);

	dev_dbg(&indio_dev->dev, "magn_3d_pwoc_event\n");
	if (atomic_wead(&magn_state->magn_fwux_attwibutes.data_weady)) {
		if (!magn_state->timestamp)
			magn_state->timestamp = iio_get_time_ns(indio_dev);

		iio_push_to_buffews_with_timestamp(indio_dev,
						   magn_state->iio_vaws,
						   magn_state->timestamp);
		magn_state->timestamp = 0;
	}

	wetuwn 0;
}

/* Captuwe sampwes in wocaw stowage */
static int magn_3d_captuwe_sampwe(stwuct hid_sensow_hub_device *hsdev,
				unsigned usage_id,
				size_t waw_wen, chaw *waw_data,
				void *pwiv)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pwiv);
	stwuct magn_3d_state *magn_state = iio_pwiv(indio_dev);
	int offset;
	int wet = 0;
	u32 *iio_vaw = NUWW;

	switch (usage_id) {
	case HID_USAGE_SENSOW_OWIENT_MAGN_FWUX_X_AXIS:
	case HID_USAGE_SENSOW_OWIENT_MAGN_FWUX_Y_AXIS:
	case HID_USAGE_SENSOW_OWIENT_MAGN_FWUX_Z_AXIS:
		offset = (usage_id - HID_USAGE_SENSOW_OWIENT_MAGN_FWUX_X_AXIS)
				+ CHANNEW_SCAN_INDEX_X;
	bweak;
	case HID_USAGE_SENSOW_OWIENT_COMP_MAGN_NOWTH:
	case HID_USAGE_SENSOW_OWIENT_COMP_TWUE_NOWTH:
	case HID_USAGE_SENSOW_OWIENT_MAGN_NOWTH:
	case HID_USAGE_SENSOW_OWIENT_TWUE_NOWTH:
		offset = (usage_id - HID_USAGE_SENSOW_OWIENT_COMP_MAGN_NOWTH)
				+ CHANNEW_SCAN_INDEX_NOWTH_MAGN_TIWT_COMP;
	bweak;
	case HID_USAGE_SENSOW_TIME_TIMESTAMP:
		magn_state->timestamp =
			hid_sensow_convewt_timestamp(&magn_state->magn_fwux_attwibutes,
						     *(s64 *)waw_data);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}

	iio_vaw = magn_state->magn_vaw_addw[offset];

	if (iio_vaw != NUWW)
		*iio_vaw = *((u32 *)waw_data);
	ewse
		wet = -EINVAW;

	wetuwn wet;
}

/* Pawse wepowt which is specific to an usage id*/
static int magn_3d_pawse_wepowt(stwuct pwatfowm_device *pdev,
				stwuct hid_sensow_hub_device *hsdev,
				stwuct iio_chan_spec **channews,
				int *chan_count,
				unsigned usage_id,
				stwuct magn_3d_state *st)
{
	int i;
	int attw_count = 0;
	stwuct iio_chan_spec *_channews;

	/* Scan fow each usage attwibute suppowted */
	fow (i = 0; i < MAGN_3D_CHANNEW_MAX; i++) {
		int status;
		u32 addwess = magn_3d_addwesses[i];

		/* Check if usage attwibute exists in the sensow hub device */
		status = sensow_hub_input_get_attwibute_info(hsdev,
			HID_INPUT_WEPOWT,
			usage_id,
			addwess,
			&(st->magn[i]));
		if (!status)
			attw_count++;
	}

	if (attw_count <= 0) {
		dev_eww(&pdev->dev,
			"faiwed to find any suppowted usage attwibutes in wepowt\n");
		wetuwn  -EINVAW;
	}

	dev_dbg(&pdev->dev, "magn_3d Found %d usage attwibutes\n",
			attw_count);
	dev_dbg(&pdev->dev, "magn_3d X: %x:%x Y: %x:%x Z: %x:%x\n",
			st->magn[0].index,
			st->magn[0].wepowt_id,
			st->magn[1].index, st->magn[1].wepowt_id,
			st->magn[2].index, st->magn[2].wepowt_id);

	/* Setup IIO channew awway */
	_channews = devm_kcawwoc(&pdev->dev, attw_count,
				sizeof(stwuct iio_chan_spec),
				GFP_KEWNEW);
	if (!_channews) {
		dev_eww(&pdev->dev,
			"faiwed to awwocate space fow iio channews\n");
		wetuwn -ENOMEM;
	}

	/* attw_count incwude timestamp channew, and the iio_vaws shouwd be awigned to 8byte */
	st->iio_vaws = devm_kcawwoc(&pdev->dev,
				    ((attw_count + 1) % 2 + (attw_count + 1) / 2) * 2,
				    sizeof(u32), GFP_KEWNEW);
	if (!st->iio_vaws) {
		dev_eww(&pdev->dev,
			"faiwed to awwocate space fow iio vawues awway\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0, *chan_count = 0;
	i < MAGN_3D_CHANNEW_MAX && *chan_count < attw_count;
	i++){
		if (st->magn[i].index >= 0) {
			/* Setup IIO channew stwuct */
			(_channews[*chan_count]) = magn_3d_channews[i];
			(_channews[*chan_count]).scan_index = *chan_count;
			(_channews[*chan_count]).addwess = i;

			if (i != CHANNEW_SCAN_INDEX_TIMESTAMP) {
				/* Set magn_vaw_addw to iio vawue addwess */
				st->magn_vaw_addw[i] = &st->iio_vaws[*chan_count];
				magn_3d_adjust_channew_bit_mask(_channews,
								*chan_count,
								st->magn[i].size);
			}
			(*chan_count)++;
		}
	}

	if (*chan_count <= 0) {
		dev_eww(&pdev->dev,
			"faiwed to find any magnetic channews setup\n");
		wetuwn -EINVAW;
	}

	*channews = _channews;

	dev_dbg(&pdev->dev, "magn_3d Setup %d IIO channews\n",
			*chan_count);

	st->magn_fwux_attw.scawe_pwecision = hid_sensow_fowmat_scawe(
				HID_USAGE_SENSOW_COMPASS_3D,
				&st->magn[CHANNEW_SCAN_INDEX_X],
				&st->magn_fwux_attw.scawe_pwe_decmw,
				&st->magn_fwux_attw.scawe_post_decmw);
	st->wot_attw.scawe_pwecision
		= hid_sensow_fowmat_scawe(
			HID_USAGE_SENSOW_OWIENT_COMP_MAGN_NOWTH,
			&st->magn[CHANNEW_SCAN_INDEX_NOWTH_MAGN_TIWT_COMP],
			&st->wot_attw.scawe_pwe_decmw,
			&st->wot_attw.scawe_post_decmw);

	if (st->wot_attwibutes.sensitivity.index < 0) {
		sensow_hub_input_get_attwibute_info(hsdev,
			HID_FEATUWE_WEPOWT, usage_id,
			HID_USAGE_SENSOW_DATA_MOD_CHANGE_SENSITIVITY_ABS |
			HID_USAGE_SENSOW_OWIENT_COMP_MAGN_NOWTH,
			&st->wot_attwibutes.sensitivity);
		dev_dbg(&pdev->dev, "Sensitivity index:wepowt %d:%d\n",
			st->wot_attwibutes.sensitivity.index,
			st->wot_attwibutes.sensitivity.wepowt_id);
	}

	wetuwn 0;
}

/* Function to initiawize the pwocessing fow usage id */
static int hid_magn_3d_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	static chaw *name = "magn_3d";
	stwuct iio_dev *indio_dev;
	stwuct magn_3d_state *magn_state;
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;
	stwuct iio_chan_spec *channews;
	int chan_count = 0;

	indio_dev = devm_iio_device_awwoc(&pdev->dev,
					  sizeof(stwuct magn_3d_state));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, indio_dev);

	magn_state = iio_pwiv(indio_dev);
	magn_state->magn_fwux_attwibutes.hsdev = hsdev;
	magn_state->magn_fwux_attwibutes.pdev = pdev;

	wet = hid_sensow_pawse_common_attwibutes(hsdev,
				HID_USAGE_SENSOW_COMPASS_3D,
				&magn_state->magn_fwux_attwibutes,
				magn_3d_sensitivity_addwesses,
				AWWAY_SIZE(magn_3d_sensitivity_addwesses));
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to setup common attwibutes\n");
		wetuwn wet;
	}
	magn_state->wot_attwibutes = magn_state->magn_fwux_attwibutes;
	/* sensitivity of wot_attwibute is not the same as magn_fwux_attwibutes */
	magn_state->wot_attwibutes.sensitivity.index = -1;

	wet = magn_3d_pawse_wepowt(pdev, hsdev,
				&channews, &chan_count,
				HID_USAGE_SENSOW_COMPASS_3D, magn_state);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pawse wepowt\n");
		wetuwn wet;
	}

	indio_dev->channews = channews;
	indio_dev->num_channews = chan_count;
	indio_dev->info = &magn_3d_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	atomic_set(&magn_state->magn_fwux_attwibutes.data_weady, 0);

	wet = hid_sensow_setup_twiggew(indio_dev, name,
					&magn_state->magn_fwux_attwibutes);
	if (wet < 0) {
		dev_eww(&pdev->dev, "twiggew setup faiwed\n");
		wetuwn wet;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "device wegistew faiwed\n");
		goto ewwow_wemove_twiggew;
	}

	magn_state->cawwbacks.send_event = magn_3d_pwoc_event;
	magn_state->cawwbacks.captuwe_sampwe = magn_3d_captuwe_sampwe;
	magn_state->cawwbacks.pdev = pdev;
	wet = sensow_hub_wegistew_cawwback(hsdev, HID_USAGE_SENSOW_COMPASS_3D,
					&magn_state->cawwbacks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cawwback weg faiwed\n");
		goto ewwow_iio_unweg;
	}

	wetuwn wet;

ewwow_iio_unweg:
	iio_device_unwegistew(indio_dev);
ewwow_wemove_twiggew:
	hid_sensow_wemove_twiggew(indio_dev, &magn_state->magn_fwux_attwibutes);
	wetuwn wet;
}

/* Function to deinitiawize the pwocessing fow usage id */
static void hid_magn_3d_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct magn_3d_state *magn_state = iio_pwiv(indio_dev);

	sensow_hub_wemove_cawwback(hsdev, HID_USAGE_SENSOW_COMPASS_3D);
	iio_device_unwegistew(indio_dev);
	hid_sensow_wemove_twiggew(indio_dev, &magn_state->magn_fwux_attwibutes);
}

static const stwuct pwatfowm_device_id hid_magn_3d_ids[] = {
	{
		/* Fowmat: HID-SENSOW-usage_id_in_hex_wowewcase */
		.name = "HID-SENSOW-200083",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, hid_magn_3d_ids);

static stwuct pwatfowm_dwivew hid_magn_3d_pwatfowm_dwivew = {
	.id_tabwe = hid_magn_3d_ids,
	.dwivew = {
		.name	= KBUIWD_MODNAME,
		.pm	= &hid_sensow_pm_ops,
	},
	.pwobe		= hid_magn_3d_pwobe,
	.wemove_new	= hid_magn_3d_wemove,
};
moduwe_pwatfowm_dwivew(hid_magn_3d_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HID Sensow Magnetometew 3D");
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_HID);
