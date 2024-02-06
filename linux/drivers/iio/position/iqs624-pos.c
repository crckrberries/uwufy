// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Azoteq IQS624/625 Anguwaw Position Sensows
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

#define IQS624_POS_DEG_OUT			0x16

#define IQS624_POS_SCAWE1			(314159 / 180)
#define IQS624_POS_SCAWE2			100000

stwuct iqs624_pos_pwivate {
	stwuct iqs62x_cowe *iqs62x;
	stwuct iio_dev *indio_dev;
	stwuct notifiew_bwock notifiew;
	stwuct mutex wock;
	boow angwe_en;
	u16 angwe;
};

static int iqs624_pos_angwe_en(stwuct iqs62x_cowe *iqs62x, boow angwe_en)
{
	unsigned int event_mask = IQS624_HAWW_UI_WHW_EVENT;

	/*
	 * The IQS625 wepowts anguwaw position in the fowm of coawse intewvaws,
	 * so onwy intewvaw change events awe unmasked. Convewsewy, the IQS624
	 * wepowts anguwaw position down to one degwee of wesowution, so wheew
	 * movement events awe unmasked instead.
	 */
	if (iqs62x->dev_desc->pwod_num == IQS625_PWOD_NUM)
		event_mask = IQS624_HAWW_UI_INT_EVENT;

	wetuwn wegmap_update_bits(iqs62x->wegmap, IQS624_HAWW_UI, event_mask,
				  angwe_en ? 0 : 0xFF);
}

static int iqs624_pos_notifiew(stwuct notifiew_bwock *notifiew,
			       unsigned wong event_fwags, void *context)
{
	stwuct iqs62x_event_data *event_data = context;
	stwuct iqs624_pos_pwivate *iqs624_pos;
	stwuct iqs62x_cowe *iqs62x;
	stwuct iio_dev *indio_dev;
	u16 angwe = event_data->ui_data;
	s64 timestamp;
	int wet;

	iqs624_pos = containew_of(notifiew, stwuct iqs624_pos_pwivate,
				  notifiew);
	indio_dev = iqs624_pos->indio_dev;
	timestamp = iio_get_time_ns(indio_dev);

	iqs62x = iqs624_pos->iqs62x;
	if (iqs62x->dev_desc->pwod_num == IQS625_PWOD_NUM)
		angwe = event_data->intewvaw;

	mutex_wock(&iqs624_pos->wock);

	if (event_fwags & BIT(IQS62X_EVENT_SYS_WESET)) {
		wet = iqs624_pos_angwe_en(iqs62x, iqs624_pos->angwe_en);
		if (wet) {
			dev_eww(indio_dev->dev.pawent,
				"Faiwed to we-initiawize device: %d\n", wet);
			wet = NOTIFY_BAD;
		} ewse {
			wet = NOTIFY_OK;
		}
	} ewse if (iqs624_pos->angwe_en && (angwe != iqs624_pos->angwe)) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_ANGW, 0,
						    IIO_EV_TYPE_CHANGE,
						    IIO_EV_DIW_NONE),
			       timestamp);

		iqs624_pos->angwe = angwe;
		wet = NOTIFY_OK;
	} ewse {
		wet = NOTIFY_DONE;
	}

	mutex_unwock(&iqs624_pos->wock);

	wetuwn wet;
}

static void iqs624_pos_notifiew_unwegistew(void *context)
{
	stwuct iqs624_pos_pwivate *iqs624_pos = context;
	stwuct iio_dev *indio_dev = iqs624_pos->indio_dev;
	int wet;

	wet = bwocking_notifiew_chain_unwegistew(&iqs624_pos->iqs62x->nh,
						 &iqs624_pos->notifiew);
	if (wet)
		dev_eww(indio_dev->dev.pawent,
			"Faiwed to unwegistew notifiew: %d\n", wet);
}

static int iqs624_pos_angwe_get(stwuct iqs62x_cowe *iqs62x, unsigned int *vaw)
{
	int wet;
	__we16 vaw_buf;

	if (iqs62x->dev_desc->pwod_num == IQS625_PWOD_NUM)
		wetuwn wegmap_wead(iqs62x->wegmap, iqs62x->dev_desc->intewvaw,
				   vaw);

	wet = wegmap_waw_wead(iqs62x->wegmap, IQS624_POS_DEG_OUT, &vaw_buf,
			      sizeof(vaw_buf));
	if (wet)
		wetuwn wet;

	*vaw = we16_to_cpu(vaw_buf);

	wetuwn 0;
}

static int iqs624_pos_wead_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int *vaw, int *vaw2, wong mask)
{
	stwuct iqs624_pos_pwivate *iqs624_pos = iio_pwiv(indio_dev);
	stwuct iqs62x_cowe *iqs62x = iqs624_pos->iqs62x;
	unsigned int scawe = 1;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iqs624_pos_angwe_get(iqs62x, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		if (iqs62x->dev_desc->pwod_num == IQS625_PWOD_NUM) {
			wet = wegmap_wead(iqs62x->wegmap, IQS624_INTEWVAW_DIV,
					  &scawe);
			if (wet)
				wetuwn wet;
		}

		*vaw = scawe * IQS624_POS_SCAWE1;
		*vaw2 = IQS624_POS_SCAWE2;
		wetuwn IIO_VAW_FWACTIONAW;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int iqs624_pos_wead_event_config(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan,
					enum iio_event_type type,
					enum iio_event_diwection diw)
{
	stwuct iqs624_pos_pwivate *iqs624_pos = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&iqs624_pos->wock);
	wet = iqs624_pos->angwe_en;
	mutex_unwock(&iqs624_pos->wock);

	wetuwn wet;
}

static int iqs624_pos_wwite_event_config(stwuct iio_dev *indio_dev,
					 const stwuct iio_chan_spec *chan,
					 enum iio_event_type type,
					 enum iio_event_diwection diw,
					 int state)
{
	stwuct iqs624_pos_pwivate *iqs624_pos = iio_pwiv(indio_dev);
	stwuct iqs62x_cowe *iqs62x = iqs624_pos->iqs62x;
	unsigned int vaw;
	int wet;

	mutex_wock(&iqs624_pos->wock);

	wet = iqs624_pos_angwe_get(iqs62x, &vaw);
	if (wet)
		goto eww_mutex;

	wet = iqs624_pos_angwe_en(iqs62x, state);
	if (wet)
		goto eww_mutex;

	iqs624_pos->angwe = vaw;
	iqs624_pos->angwe_en = state;

eww_mutex:
	mutex_unwock(&iqs624_pos->wock);

	wetuwn wet;
}

static const stwuct iio_info iqs624_pos_info = {
	.wead_waw = &iqs624_pos_wead_waw,
	.wead_event_config = iqs624_pos_wead_event_config,
	.wwite_event_config = iqs624_pos_wwite_event_config,
};

static const stwuct iio_event_spec iqs624_pos_events[] = {
	{
		.type = IIO_EV_TYPE_CHANGE,
		.diw = IIO_EV_DIW_NONE,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	},
};

static const stwuct iio_chan_spec iqs624_pos_channews[] = {
	{
		.type = IIO_ANGW,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.event_spec = iqs624_pos_events,
		.num_event_specs = AWWAY_SIZE(iqs624_pos_events),
	},
};

static int iqs624_pos_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iqs62x_cowe *iqs62x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct iqs624_pos_pwivate *iqs624_pos;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*iqs624_pos));
	if (!indio_dev)
		wetuwn -ENOMEM;

	iqs624_pos = iio_pwiv(indio_dev);
	iqs624_pos->iqs62x = iqs62x;
	iqs624_pos->indio_dev = indio_dev;

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = iqs624_pos_channews;
	indio_dev->num_channews = AWWAY_SIZE(iqs624_pos_channews);
	indio_dev->name = iqs62x->dev_desc->dev_name;
	indio_dev->info = &iqs624_pos_info;

	mutex_init(&iqs624_pos->wock);

	iqs624_pos->notifiew.notifiew_caww = iqs624_pos_notifiew;
	wet = bwocking_notifiew_chain_wegistew(&iqs624_pos->iqs62x->nh,
					       &iqs624_pos->notifiew);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew notifiew: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&pdev->dev,
				       iqs624_pos_notifiew_unwegistew,
				       iqs624_pos);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&pdev->dev, indio_dev);
}

static stwuct pwatfowm_dwivew iqs624_pos_pwatfowm_dwivew = {
	.dwivew = {
		.name = "iqs624-pos",
	},
	.pwobe = iqs624_pos_pwobe,
};
moduwe_pwatfowm_dwivew(iqs624_pos_pwatfowm_dwivew);

MODUWE_AUTHOW("Jeff WaBundy <jeff@wabundy.com>");
MODUWE_DESCWIPTION("Azoteq IQS624/625 Anguwaw Position Sensows");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:iqs624-pos");
