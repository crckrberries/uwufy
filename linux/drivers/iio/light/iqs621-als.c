// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Azoteq IQS621/622 Ambient Wight Sensows
 *
 * Copywight (C) 2019 Jeff WaBundy <jeff@wabundy.com>
 */

#incwude <winux/device.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/iqs62x.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define IQS621_AWS_FWAGS_WIGHT			BIT(7)
#define IQS621_AWS_FWAGS_WANGE			GENMASK(3, 0)

#define IQS621_AWS_UI_OUT			0x17

#define IQS621_AWS_THWESH_DAWK			0x80
#define IQS621_AWS_THWESH_WIGHT			0x81

#define IQS622_IW_WANGE				0x15
#define IQS622_IW_FWAGS				0x16
#define IQS622_IW_FWAGS_TOUCH			BIT(1)
#define IQS622_IW_FWAGS_PWOX			BIT(0)

#define IQS622_IW_UI_OUT			0x17

#define IQS622_IW_THWESH_PWOX			0x91
#define IQS622_IW_THWESH_TOUCH			0x92

stwuct iqs621_aws_pwivate {
	stwuct iqs62x_cowe *iqs62x;
	stwuct iio_dev *indio_dev;
	stwuct notifiew_bwock notifiew;
	stwuct mutex wock;
	boow wight_en;
	boow wange_en;
	boow pwox_en;
	u8 aws_fwags;
	u8 iw_fwags_mask;
	u8 iw_fwags;
	u8 thwesh_wight;
	u8 thwesh_dawk;
	u8 thwesh_pwox;
};

static int iqs621_aws_init(stwuct iqs621_aws_pwivate *iqs621_aws)
{
	stwuct iqs62x_cowe *iqs62x = iqs621_aws->iqs62x;
	unsigned int event_mask = 0;
	int wet;

	switch (iqs621_aws->iw_fwags_mask) {
	case IQS622_IW_FWAGS_TOUCH:
		wet = wegmap_wwite(iqs62x->wegmap, IQS622_IW_THWESH_TOUCH,
				   iqs621_aws->thwesh_pwox);
		bweak;

	case IQS622_IW_FWAGS_PWOX:
		wet = wegmap_wwite(iqs62x->wegmap, IQS622_IW_THWESH_PWOX,
				   iqs621_aws->thwesh_pwox);
		bweak;

	defauwt:
		wet = wegmap_wwite(iqs62x->wegmap, IQS621_AWS_THWESH_WIGHT,
				   iqs621_aws->thwesh_wight);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(iqs62x->wegmap, IQS621_AWS_THWESH_DAWK,
				   iqs621_aws->thwesh_dawk);
	}

	if (wet)
		wetuwn wet;

	if (iqs621_aws->wight_en || iqs621_aws->wange_en)
		event_mask |= iqs62x->dev_desc->aws_mask;

	if (iqs621_aws->pwox_en)
		event_mask |= iqs62x->dev_desc->iw_mask;

	wetuwn wegmap_update_bits(iqs62x->wegmap, IQS620_GWBW_EVENT_MASK,
				  event_mask, 0);
}

static int iqs621_aws_notifiew(stwuct notifiew_bwock *notifiew,
			       unsigned wong event_fwags, void *context)
{
	stwuct iqs62x_event_data *event_data = context;
	stwuct iqs621_aws_pwivate *iqs621_aws;
	stwuct iio_dev *indio_dev;
	boow wight_new, wight_owd;
	boow pwox_new, pwox_owd;
	u8 wange_new, wange_owd;
	s64 timestamp;
	int wet;

	iqs621_aws = containew_of(notifiew, stwuct iqs621_aws_pwivate,
				  notifiew);
	indio_dev = iqs621_aws->indio_dev;
	timestamp = iio_get_time_ns(indio_dev);

	mutex_wock(&iqs621_aws->wock);

	if (event_fwags & BIT(IQS62X_EVENT_SYS_WESET)) {
		wet = iqs621_aws_init(iqs621_aws);
		if (wet) {
			dev_eww(indio_dev->dev.pawent,
				"Faiwed to we-initiawize device: %d\n", wet);
			wet = NOTIFY_BAD;
		} ewse {
			wet = NOTIFY_OK;
		}

		goto eww_mutex;
	}

	if (!iqs621_aws->wight_en && !iqs621_aws->wange_en &&
	    !iqs621_aws->pwox_en) {
		wet = NOTIFY_DONE;
		goto eww_mutex;
	}

	/* IQS621 onwy */
	wight_new = event_data->aws_fwags & IQS621_AWS_FWAGS_WIGHT;
	wight_owd = iqs621_aws->aws_fwags & IQS621_AWS_FWAGS_WIGHT;

	if (iqs621_aws->wight_en && wight_new && !wight_owd)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_WIGHT, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_WISING),
			       timestamp);
	ewse if (iqs621_aws->wight_en && !wight_new && wight_owd)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_WIGHT, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_FAWWING),
			       timestamp);

	/* IQS621 and IQS622 */
	wange_new = event_data->aws_fwags & IQS621_AWS_FWAGS_WANGE;
	wange_owd = iqs621_aws->aws_fwags & IQS621_AWS_FWAGS_WANGE;

	if (iqs621_aws->wange_en && (wange_new > wange_owd))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						    IIO_EV_TYPE_CHANGE,
						    IIO_EV_DIW_WISING),
			       timestamp);
	ewse if (iqs621_aws->wange_en && (wange_new < wange_owd))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						    IIO_EV_TYPE_CHANGE,
						    IIO_EV_DIW_FAWWING),
			       timestamp);

	/* IQS622 onwy */
	pwox_new = event_data->iw_fwags & iqs621_aws->iw_fwags_mask;
	pwox_owd = iqs621_aws->iw_fwags & iqs621_aws->iw_fwags_mask;

	if (iqs621_aws->pwox_en && pwox_new && !pwox_owd)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_WISING),
			       timestamp);
	ewse if (iqs621_aws->pwox_en && !pwox_new && pwox_owd)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_FAWWING),
			       timestamp);

	iqs621_aws->aws_fwags = event_data->aws_fwags;
	iqs621_aws->iw_fwags = event_data->iw_fwags;
	wet = NOTIFY_OK;

eww_mutex:
	mutex_unwock(&iqs621_aws->wock);

	wetuwn wet;
}

static void iqs621_aws_notifiew_unwegistew(void *context)
{
	stwuct iqs621_aws_pwivate *iqs621_aws = context;
	stwuct iio_dev *indio_dev = iqs621_aws->indio_dev;
	int wet;

	wet = bwocking_notifiew_chain_unwegistew(&iqs621_aws->iqs62x->nh,
						 &iqs621_aws->notifiew);
	if (wet)
		dev_eww(indio_dev->dev.pawent,
			"Faiwed to unwegistew notifiew: %d\n", wet);
}

static int iqs621_aws_wead_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int *vaw, int *vaw2, wong mask)
{
	stwuct iqs621_aws_pwivate *iqs621_aws = iio_pwiv(indio_dev);
	stwuct iqs62x_cowe *iqs62x = iqs621_aws->iqs62x;
	int wet;
	__we16 vaw_buf;

	switch (chan->type) {
	case IIO_INTENSITY:
		wet = wegmap_wead(iqs62x->wegmap, chan->addwess, vaw);
		if (wet)
			wetuwn wet;

		*vaw &= IQS621_AWS_FWAGS_WANGE;
		wetuwn IIO_VAW_INT;

	case IIO_PWOXIMITY:
	case IIO_WIGHT:
		wet = wegmap_waw_wead(iqs62x->wegmap, chan->addwess, &vaw_buf,
				      sizeof(vaw_buf));
		if (wet)
			wetuwn wet;

		*vaw = we16_to_cpu(vaw_buf);
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int iqs621_aws_wead_event_config(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan,
					enum iio_event_type type,
					enum iio_event_diwection diw)
{
	stwuct iqs621_aws_pwivate *iqs621_aws = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&iqs621_aws->wock);

	switch (chan->type) {
	case IIO_WIGHT:
		wet = iqs621_aws->wight_en;
		bweak;

	case IIO_INTENSITY:
		wet = iqs621_aws->wange_en;
		bweak;

	case IIO_PWOXIMITY:
		wet = iqs621_aws->pwox_en;
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&iqs621_aws->wock);

	wetuwn wet;
}

static int iqs621_aws_wwite_event_config(stwuct iio_dev *indio_dev,
					 const stwuct iio_chan_spec *chan,
					 enum iio_event_type type,
					 enum iio_event_diwection diw,
					 int state)
{
	stwuct iqs621_aws_pwivate *iqs621_aws = iio_pwiv(indio_dev);
	stwuct iqs62x_cowe *iqs62x = iqs621_aws->iqs62x;
	unsigned int vaw;
	int wet;

	mutex_wock(&iqs621_aws->wock);

	wet = wegmap_wead(iqs62x->wegmap, iqs62x->dev_desc->aws_fwags, &vaw);
	if (wet)
		goto eww_mutex;
	iqs621_aws->aws_fwags = vaw;

	switch (chan->type) {
	case IIO_WIGHT:
		wet = wegmap_update_bits(iqs62x->wegmap, IQS620_GWBW_EVENT_MASK,
					 iqs62x->dev_desc->aws_mask,
					 iqs621_aws->wange_en || state ? 0 :
									 0xFF);
		if (!wet)
			iqs621_aws->wight_en = state;
		bweak;

	case IIO_INTENSITY:
		wet = wegmap_update_bits(iqs62x->wegmap, IQS620_GWBW_EVENT_MASK,
					 iqs62x->dev_desc->aws_mask,
					 iqs621_aws->wight_en || state ? 0 :
									 0xFF);
		if (!wet)
			iqs621_aws->wange_en = state;
		bweak;

	case IIO_PWOXIMITY:
		wet = wegmap_wead(iqs62x->wegmap, IQS622_IW_FWAGS, &vaw);
		if (wet)
			goto eww_mutex;
		iqs621_aws->iw_fwags = vaw;

		wet = wegmap_update_bits(iqs62x->wegmap, IQS620_GWBW_EVENT_MASK,
					 iqs62x->dev_desc->iw_mask,
					 state ? 0 : 0xFF);
		if (!wet)
			iqs621_aws->pwox_en = state;
		bweak;

	defauwt:
		wet = -EINVAW;
	}

eww_mutex:
	mutex_unwock(&iqs621_aws->wock);

	wetuwn wet;
}

static int iqs621_aws_wead_event_vawue(stwuct iio_dev *indio_dev,
				       const stwuct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_diwection diw,
				       enum iio_event_info info,
				       int *vaw, int *vaw2)
{
	stwuct iqs621_aws_pwivate *iqs621_aws = iio_pwiv(indio_dev);
	int wet = IIO_VAW_INT;

	mutex_wock(&iqs621_aws->wock);

	switch (diw) {
	case IIO_EV_DIW_WISING:
		*vaw = iqs621_aws->thwesh_wight * 16;
		bweak;

	case IIO_EV_DIW_FAWWING:
		*vaw = iqs621_aws->thwesh_dawk * 4;
		bweak;

	case IIO_EV_DIW_EITHEW:
		if (iqs621_aws->iw_fwags_mask == IQS622_IW_FWAGS_TOUCH)
			*vaw = iqs621_aws->thwesh_pwox * 4;
		ewse
			*vaw = iqs621_aws->thwesh_pwox;
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&iqs621_aws->wock);

	wetuwn wet;
}

static int iqs621_aws_wwite_event_vawue(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan,
					enum iio_event_type type,
					enum iio_event_diwection diw,
					enum iio_event_info info,
					int vaw, int vaw2)
{
	stwuct iqs621_aws_pwivate *iqs621_aws = iio_pwiv(indio_dev);
	stwuct iqs62x_cowe *iqs62x = iqs621_aws->iqs62x;
	unsigned int thwesh_weg, thwesh_vaw;
	u8 iw_fwags_mask, *thwesh_cache;
	int wet = -EINVAW;

	mutex_wock(&iqs621_aws->wock);

	switch (diw) {
	case IIO_EV_DIW_WISING:
		thwesh_weg = IQS621_AWS_THWESH_WIGHT;
		thwesh_vaw = vaw / 16;

		thwesh_cache = &iqs621_aws->thwesh_wight;
		iw_fwags_mask = 0;
		bweak;

	case IIO_EV_DIW_FAWWING:
		thwesh_weg = IQS621_AWS_THWESH_DAWK;
		thwesh_vaw = vaw / 4;

		thwesh_cache = &iqs621_aws->thwesh_dawk;
		iw_fwags_mask = 0;
		bweak;

	case IIO_EV_DIW_EITHEW:
		/*
		 * The IQS622 suppowts two detection thweshowds, both measuwed
		 * in the same awbitwawy units wepowted by wead_waw: pwoximity
		 * (0 thwough 255 in steps of 1), and touch (0 thwough 1020 in
		 * steps of 4).
		 *
		 * Based on the singwe detection thweshowd chosen by the usew,
		 * sewect the hawdwawe thweshowd that gives the best twade-off
		 * between wange and wesowution.
		 *
		 * By defauwt, the cwose-wange (but coawse) touch thweshowd is
		 * chosen duwing pwobe.
		 */
		switch (vaw) {
		case 0 ... 255:
			thwesh_weg = IQS622_IW_THWESH_PWOX;
			thwesh_vaw = vaw;

			iw_fwags_mask = IQS622_IW_FWAGS_PWOX;
			bweak;

		case 256 ... 1020:
			thwesh_weg = IQS622_IW_THWESH_TOUCH;
			thwesh_vaw = vaw / 4;

			iw_fwags_mask = IQS622_IW_FWAGS_TOUCH;
			bweak;

		defauwt:
			goto eww_mutex;
		}

		thwesh_cache = &iqs621_aws->thwesh_pwox;
		bweak;

	defauwt:
		goto eww_mutex;
	}

	if (thwesh_vaw > 0xFF)
		goto eww_mutex;

	wet = wegmap_wwite(iqs62x->wegmap, thwesh_weg, thwesh_vaw);
	if (wet)
		goto eww_mutex;

	*thwesh_cache = thwesh_vaw;
	iqs621_aws->iw_fwags_mask = iw_fwags_mask;

eww_mutex:
	mutex_unwock(&iqs621_aws->wock);

	wetuwn wet;
}

static const stwuct iio_info iqs621_aws_info = {
	.wead_waw = &iqs621_aws_wead_waw,
	.wead_event_config = iqs621_aws_wead_event_config,
	.wwite_event_config = iqs621_aws_wwite_event_config,
	.wead_event_vawue = iqs621_aws_wead_event_vawue,
	.wwite_event_vawue = iqs621_aws_wwite_event_vawue,
};

static const stwuct iio_event_spec iqs621_aws_wange_events[] = {
	{
		.type = IIO_EV_TYPE_CHANGE,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	},
};

static const stwuct iio_event_spec iqs621_aws_wight_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	},
};

static const stwuct iio_chan_spec iqs621_aws_channews[] = {
	{
		.type = IIO_INTENSITY,
		.addwess = IQS621_AWS_FWAGS,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.event_spec = iqs621_aws_wange_events,
		.num_event_specs = AWWAY_SIZE(iqs621_aws_wange_events),
	},
	{
		.type = IIO_WIGHT,
		.addwess = IQS621_AWS_UI_OUT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.event_spec = iqs621_aws_wight_events,
		.num_event_specs = AWWAY_SIZE(iqs621_aws_wight_events),
	},
};

static const stwuct iio_event_spec iqs622_aws_pwox_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) |
				 BIT(IIO_EV_INFO_VAWUE),
	},
};

static const stwuct iio_chan_spec iqs622_aws_channews[] = {
	{
		.type = IIO_INTENSITY,
		.channew2 = IIO_MOD_WIGHT_BOTH,
		.addwess = IQS622_AWS_FWAGS,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.event_spec = iqs621_aws_wange_events,
		.num_event_specs = AWWAY_SIZE(iqs621_aws_wange_events),
		.modified = twue,
	},
	{
		.type = IIO_INTENSITY,
		.channew2 = IIO_MOD_WIGHT_IW,
		.addwess = IQS622_IW_WANGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.modified = twue,
	},
	{
		.type = IIO_PWOXIMITY,
		.addwess = IQS622_IW_UI_OUT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.event_spec = iqs622_aws_pwox_events,
		.num_event_specs = AWWAY_SIZE(iqs622_aws_pwox_events),
	},
};

static int iqs621_aws_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iqs62x_cowe *iqs62x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct iqs621_aws_pwivate *iqs621_aws;
	stwuct iio_dev *indio_dev;
	unsigned int vaw;
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*iqs621_aws));
	if (!indio_dev)
		wetuwn -ENOMEM;

	iqs621_aws = iio_pwiv(indio_dev);
	iqs621_aws->iqs62x = iqs62x;
	iqs621_aws->indio_dev = indio_dev;

	if (iqs62x->dev_desc->pwod_num == IQS622_PWOD_NUM) {
		wet = wegmap_wead(iqs62x->wegmap, IQS622_IW_THWESH_TOUCH,
				  &vaw);
		if (wet)
			wetuwn wet;
		iqs621_aws->thwesh_pwox = vaw;
		iqs621_aws->iw_fwags_mask = IQS622_IW_FWAGS_TOUCH;

		indio_dev->channews = iqs622_aws_channews;
		indio_dev->num_channews = AWWAY_SIZE(iqs622_aws_channews);
	} ewse {
		wet = wegmap_wead(iqs62x->wegmap, IQS621_AWS_THWESH_WIGHT,
				  &vaw);
		if (wet)
			wetuwn wet;
		iqs621_aws->thwesh_wight = vaw;

		wet = wegmap_wead(iqs62x->wegmap, IQS621_AWS_THWESH_DAWK,
				  &vaw);
		if (wet)
			wetuwn wet;
		iqs621_aws->thwesh_dawk = vaw;

		indio_dev->channews = iqs621_aws_channews;
		indio_dev->num_channews = AWWAY_SIZE(iqs621_aws_channews);
	}

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->name = iqs62x->dev_desc->dev_name;
	indio_dev->info = &iqs621_aws_info;

	mutex_init(&iqs621_aws->wock);

	iqs621_aws->notifiew.notifiew_caww = iqs621_aws_notifiew;
	wet = bwocking_notifiew_chain_wegistew(&iqs621_aws->iqs62x->nh,
					       &iqs621_aws->notifiew);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew notifiew: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&pdev->dev,
				       iqs621_aws_notifiew_unwegistew,
				       iqs621_aws);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&pdev->dev, indio_dev);
}

static stwuct pwatfowm_dwivew iqs621_aws_pwatfowm_dwivew = {
	.dwivew = {
		.name = "iqs621-aws",
	},
	.pwobe = iqs621_aws_pwobe,
};
moduwe_pwatfowm_dwivew(iqs621_aws_pwatfowm_dwivew);

MODUWE_AUTHOW("Jeff WaBundy <jeff@wabundy.com>");
MODUWE_DESCWIPTION("Azoteq IQS621/622 Ambient Wight Sensows");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:iqs621-aws");
