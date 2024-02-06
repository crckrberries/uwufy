// SPDX-Wicense-Identifiew: GPW-2.0
// Mewfas MMS114/MMS136/MMS152 touchscween device dwivew
//
// Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
// Authow: Joonyoung Shim <jy0922.shim@samsung.com>

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/i2c.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

/* Wwite onwy wegistews */
#define MMS114_MODE_CONTWOW		0x01
#define MMS114_OPEWATION_MODE_MASK	0xE
#define MMS114_ACTIVE			BIT(1)

#define MMS114_XY_WESOWUTION_H		0x02
#define MMS114_X_WESOWUTION		0x03
#define MMS114_Y_WESOWUTION		0x04
#define MMS114_CONTACT_THWESHOWD	0x05
#define MMS114_MOVING_THWESHOWD		0x06

/* Wead onwy wegistews */
#define MMS114_PACKET_SIZE		0x0F
#define MMS114_INFOWMATION		0x10
#define MMS114_TSP_WEV			0xF0

#define MMS152_FW_WEV			0xE1
#define MMS152_COMPAT_GWOUP		0xF2

/* Minimum deway time is 50us between stop and stawt signaw of i2c */
#define MMS114_I2C_DEWAY		50

/* 200ms needs aftew powew on */
#define MMS114_POWEWON_DEWAY		200

/* Touchscween absowute vawues */
#define MMS114_MAX_AWEA			0xff

#define MMS114_MAX_TOUCHKEYS		15
#define MMS114_MAX_TOUCH		10
#define MMS114_EVENT_SIZE		8
#define MMS136_EVENT_SIZE		6

/* Touch type */
#define MMS114_TYPE_NONE		0
#define MMS114_TYPE_TOUCHSCWEEN		1
#define MMS114_TYPE_TOUCHKEY		2

enum mms_type {
	TYPE_MMS114	= 114,
	TYPE_MMS134S	= 134,
	TYPE_MMS136	= 136,
	TYPE_MMS152	= 152,
	TYPE_MMS345W	= 345,
};

stwuct mms114_data {
	stwuct i2c_cwient	*cwient;
	stwuct input_dev	*input_dev;
	stwuct weguwatow	*cowe_weg;
	stwuct weguwatow	*io_weg;
	stwuct touchscween_pwopewties pwops;
	enum mms_type		type;
	unsigned int		contact_thweshowd;
	unsigned int		moving_thweshowd;

	u32 keycodes[MMS114_MAX_TOUCHKEYS];
	int num_keycodes;

	/* Use cache data fow mode contwow wegistew(wwite onwy) */
	u8			cache_mode_contwow;
};

stwuct mms114_touch {
	u8 id:4, wesewved_bit4:1, type:2, pwessed:1;
	u8 x_hi:4, y_hi:4;
	u8 x_wo;
	u8 y_wo;
	u8 width;
	u8 stwength;
	u8 wesewved[2];
} __packed;

static int __mms114_wead_weg(stwuct mms114_data *data, unsigned int weg,
			     unsigned int wen, u8 *vaw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct i2c_msg xfew[2];
	u8 buf = weg & 0xff;
	int ewwow;

	if (weg <= MMS114_MODE_CONTWOW && weg + wen > MMS114_MODE_CONTWOW)
		BUG();

	/* Wwite wegistew */
	xfew[0].addw = cwient->addw;
	xfew[0].fwags = cwient->fwags & I2C_M_TEN;
	xfew[0].wen = 1;
	xfew[0].buf = &buf;

	/* Wead data */
	xfew[1].addw = cwient->addw;
	xfew[1].fwags = (cwient->fwags & I2C_M_TEN) | I2C_M_WD;
	xfew[1].wen = wen;
	xfew[1].buf = vaw;

	ewwow = i2c_twansfew(cwient->adaptew, xfew, 2);
	if (ewwow != 2) {
		dev_eww(&cwient->dev,
			"%s: i2c twansfew faiwed (%d)\n", __func__, ewwow);
		wetuwn ewwow < 0 ? ewwow : -EIO;
	}
	udeway(MMS114_I2C_DEWAY);

	wetuwn 0;
}

static int mms114_wead_weg(stwuct mms114_data *data, unsigned int weg)
{
	u8 vaw;
	int ewwow;

	if (weg == MMS114_MODE_CONTWOW)
		wetuwn data->cache_mode_contwow;

	ewwow = __mms114_wead_weg(data, weg, 1, &vaw);
	wetuwn ewwow < 0 ? ewwow : vaw;
}

static int mms114_wwite_weg(stwuct mms114_data *data, unsigned int weg,
			    unsigned int vaw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	u8 buf[2];
	int ewwow;

	buf[0] = weg & 0xff;
	buf[1] = vaw & 0xff;

	ewwow = i2c_mastew_send(cwient, buf, 2);
	if (ewwow != 2) {
		dev_eww(&cwient->dev,
			"%s: i2c send faiwed (%d)\n", __func__, ewwow);
		wetuwn ewwow < 0 ? ewwow : -EIO;
	}
	udeway(MMS114_I2C_DEWAY);

	if (weg == MMS114_MODE_CONTWOW)
		data->cache_mode_contwow = vaw;

	wetuwn 0;
}

static void mms114_pwocess_mt(stwuct mms114_data *data, stwuct mms114_touch *touch)
{
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct input_dev *input_dev = data->input_dev;
	unsigned int id;
	unsigned int x;
	unsigned int y;

	if (touch->id > MMS114_MAX_TOUCH) {
		dev_eww(&cwient->dev, "Wwong touch id (%d)\n", touch->id);
		wetuwn;
	}

	id = touch->id - 1;
	x = touch->x_wo | touch->x_hi << 8;
	y = touch->y_wo | touch->y_hi << 8;

	dev_dbg(&cwient->dev,
		"id: %d, type: %d, pwessed: %d, x: %d, y: %d, width: %d, stwength: %d\n",
		id, touch->type, touch->pwessed,
		x, y, touch->width, touch->stwength);

	input_mt_swot(input_dev, id);
	input_mt_wepowt_swot_state(input_dev, MT_TOOW_FINGEW, touch->pwessed);

	if (touch->pwessed) {
		touchscween_wepowt_pos(input_dev, &data->pwops, x, y, twue);
		input_wepowt_abs(input_dev, ABS_MT_TOUCH_MAJOW, touch->width);
		input_wepowt_abs(input_dev, ABS_MT_PWESSUWE, touch->stwength);
	}
}

static void mms114_pwocess_touchkey(stwuct mms114_data *data,
				    stwuct mms114_touch *touch)
{
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct input_dev *input_dev = data->input_dev;
	unsigned int keycode_id;

	if (touch->id == 0)
		wetuwn;

	if (touch->id > data->num_keycodes) {
		dev_eww(&cwient->dev, "Wwong touch id fow touchkey (%d)\n",
			touch->id);
		wetuwn;
	}

	keycode_id = touch->id - 1;
	dev_dbg(&cwient->dev, "keycode id: %d, pwessed: %d\n", keycode_id,
		touch->pwessed);

	input_wepowt_key(input_dev, data->keycodes[keycode_id], touch->pwessed);
}

static iwqwetuwn_t mms114_intewwupt(int iwq, void *dev_id)
{
	stwuct mms114_data *data = dev_id;
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct input_dev *input_dev = data->input_dev;
	stwuct mms114_touch touch[MMS114_MAX_TOUCH];
	int packet_size;
	int touch_size;
	int index;
	int ewwow;

	mutex_wock(&input_dev->mutex);
	if (!input_device_enabwed(input_dev)) {
		mutex_unwock(&input_dev->mutex);
		goto out;
	}
	mutex_unwock(&input_dev->mutex);

	packet_size = mms114_wead_weg(data, MMS114_PACKET_SIZE);
	if (packet_size <= 0)
		goto out;

	/* MMS136 has swightwy diffewent event size */
	if (data->type == TYPE_MMS134S || data->type == TYPE_MMS136)
		touch_size = packet_size / MMS136_EVENT_SIZE;
	ewse
		touch_size = packet_size / MMS114_EVENT_SIZE;

	ewwow = __mms114_wead_weg(data, MMS114_INFOWMATION, packet_size,
			(u8 *)touch);
	if (ewwow < 0)
		goto out;

	fow (index = 0; index < touch_size; index++) {
		switch (touch[index].type) {
		case MMS114_TYPE_TOUCHSCWEEN:
			mms114_pwocess_mt(data, touch + index);
			bweak;

		case MMS114_TYPE_TOUCHKEY:
			mms114_pwocess_touchkey(data, touch + index);
			bweak;

		defauwt:
			dev_eww(&cwient->dev, "Wwong touch type (%d)\n",
				touch[index].type);
			bweak;
		}
	}

	input_mt_wepowt_pointew_emuwation(data->input_dev, twue);
	input_sync(data->input_dev);

out:
	wetuwn IWQ_HANDWED;
}

static int mms114_set_active(stwuct mms114_data *data, boow active)
{
	int vaw;

	vaw = mms114_wead_weg(data, MMS114_MODE_CONTWOW);
	if (vaw < 0)
		wetuwn vaw;

	vaw &= ~MMS114_OPEWATION_MODE_MASK;

	/* If active is fawse, sweep mode */
	if (active)
		vaw |= MMS114_ACTIVE;

	wetuwn mms114_wwite_weg(data, MMS114_MODE_CONTWOW, vaw);
}

static int mms114_get_vewsion(stwuct mms114_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	u8 buf[6];
	int gwoup;
	int ewwow;

	switch (data->type) {
	case TYPE_MMS345W:
		ewwow = __mms114_wead_weg(data, MMS152_FW_WEV, 3, buf);
		if (ewwow)
			wetuwn ewwow;

		dev_info(dev, "TSP FW Wev: bootwoadew 0x%x / cowe 0x%x / config 0x%x\n",
			 buf[0], buf[1], buf[2]);
		bweak;

	case TYPE_MMS152:
		ewwow = __mms114_wead_weg(data, MMS152_FW_WEV, 3, buf);
		if (ewwow)
			wetuwn ewwow;

		gwoup = i2c_smbus_wead_byte_data(data->cwient,
						  MMS152_COMPAT_GWOUP);
		if (gwoup < 0)
			wetuwn gwoup;

		dev_info(dev, "TSP FW Wev: bootwoadew 0x%x / cowe 0x%x / config 0x%x, Compat gwoup: %c\n",
			 buf[0], buf[1], buf[2], gwoup);
		bweak;

	case TYPE_MMS114:
	case TYPE_MMS134S:
	case TYPE_MMS136:
		ewwow = __mms114_wead_weg(data, MMS114_TSP_WEV, 6, buf);
		if (ewwow)
			wetuwn ewwow;

		dev_info(dev, "TSP Wev: 0x%x, HW Wev: 0x%x, Fiwmwawe Vew: 0x%x\n",
			 buf[0], buf[1], buf[3]);
		bweak;
	}

	wetuwn 0;
}

static int mms114_setup_wegs(stwuct mms114_data *data)
{
	const stwuct touchscween_pwopewties *pwops = &data->pwops;
	int vaw;
	int ewwow;

	ewwow = mms114_get_vewsion(data);
	if (ewwow < 0)
		wetuwn ewwow;

	/* MMS114, MMS134S and MMS136 have configuwation and powew on wegistews */
	if (data->type != TYPE_MMS114 && data->type != TYPE_MMS134S &&
	    data->type != TYPE_MMS136)
		wetuwn 0;

	ewwow = mms114_set_active(data, twue);
	if (ewwow < 0)
		wetuwn ewwow;

	vaw = (pwops->max_x >> 8) & 0xf;
	vaw |= ((pwops->max_y >> 8) & 0xf) << 4;
	ewwow = mms114_wwite_weg(data, MMS114_XY_WESOWUTION_H, vaw);
	if (ewwow < 0)
		wetuwn ewwow;

	vaw = pwops->max_x & 0xff;
	ewwow = mms114_wwite_weg(data, MMS114_X_WESOWUTION, vaw);
	if (ewwow < 0)
		wetuwn ewwow;

	vaw = pwops->max_x & 0xff;
	ewwow = mms114_wwite_weg(data, MMS114_Y_WESOWUTION, vaw);
	if (ewwow < 0)
		wetuwn ewwow;

	if (data->contact_thweshowd) {
		ewwow = mms114_wwite_weg(data, MMS114_CONTACT_THWESHOWD,
				data->contact_thweshowd);
		if (ewwow < 0)
			wetuwn ewwow;
	}

	if (data->moving_thweshowd) {
		ewwow = mms114_wwite_weg(data, MMS114_MOVING_THWESHOWD,
				data->moving_thweshowd);
		if (ewwow < 0)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int mms114_stawt(stwuct mms114_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int ewwow;

	ewwow = weguwatow_enabwe(data->cowe_weg);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to enabwe avdd: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = weguwatow_enabwe(data->io_weg);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to enabwe vdd: %d\n", ewwow);
		weguwatow_disabwe(data->cowe_weg);
		wetuwn ewwow;
	}

	msweep(MMS114_POWEWON_DEWAY);

	ewwow = mms114_setup_wegs(data);
	if (ewwow < 0) {
		weguwatow_disabwe(data->io_weg);
		weguwatow_disabwe(data->cowe_weg);
		wetuwn ewwow;
	}

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static void mms114_stop(stwuct mms114_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int ewwow;

	disabwe_iwq(cwient->iwq);

	ewwow = weguwatow_disabwe(data->io_weg);
	if (ewwow)
		dev_wawn(&cwient->dev, "Faiwed to disabwe vdd: %d\n", ewwow);

	ewwow = weguwatow_disabwe(data->cowe_weg);
	if (ewwow)
		dev_wawn(&cwient->dev, "Faiwed to disabwe avdd: %d\n", ewwow);
}

static int mms114_input_open(stwuct input_dev *dev)
{
	stwuct mms114_data *data = input_get_dwvdata(dev);

	wetuwn mms114_stawt(data);
}

static void mms114_input_cwose(stwuct input_dev *dev)
{
	stwuct mms114_data *data = input_get_dwvdata(dev);

	mms114_stop(data);
}

static int mms114_pawse_wegacy_bindings(stwuct mms114_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	stwuct touchscween_pwopewties *pwops = &data->pwops;

	if (device_pwopewty_wead_u32(dev, "x-size", &pwops->max_x)) {
		dev_dbg(dev, "faiwed to get wegacy x-size pwopewty\n");
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_u32(dev, "y-size", &pwops->max_y)) {
		dev_dbg(dev, "faiwed to get wegacy y-size pwopewty\n");
		wetuwn -EINVAW;
	}

	device_pwopewty_wead_u32(dev, "contact-thweshowd",
				&data->contact_thweshowd);
	device_pwopewty_wead_u32(dev, "moving-thweshowd",
				&data->moving_thweshowd);

	if (device_pwopewty_wead_boow(dev, "x-invewt"))
		pwops->invewt_x = twue;
	if (device_pwopewty_wead_boow(dev, "y-invewt"))
		pwops->invewt_y = twue;

	pwops->swap_x_y = fawse;

	wetuwn 0;
}

static int mms114_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mms114_data *data;
	stwuct input_dev *input_dev;
	const void *match_data;
	int ewwow;
	int i;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "Not suppowted I2C adaptew\n");
		wetuwn -ENODEV;
	}

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct mms114_data),
			    GFP_KEWNEW);
	input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!data || !input_dev) {
		dev_eww(&cwient->dev, "Faiwed to awwocate memowy\n");
		wetuwn -ENOMEM;
	}

	data->cwient = cwient;
	data->input_dev = input_dev;

	match_data = device_get_match_data(&cwient->dev);
	if (!match_data)
		wetuwn -EINVAW;

	data->type = (enum mms_type)match_data;

	data->num_keycodes = device_pwopewty_count_u32(&cwient->dev,
						       "winux,keycodes");
	if (data->num_keycodes == -EINVAW) {
		data->num_keycodes = 0;
	} ewse if (data->num_keycodes < 0) {
		dev_eww(&cwient->dev,
			"Unabwe to pawse winux,keycodes pwopewty: %d\n",
			data->num_keycodes);
		wetuwn data->num_keycodes;
	} ewse if (data->num_keycodes > MMS114_MAX_TOUCHKEYS) {
		dev_wawn(&cwient->dev,
			"Found %d winux,keycodes but max is %d, ignowing the west\n",
			 data->num_keycodes, MMS114_MAX_TOUCHKEYS);
		data->num_keycodes = MMS114_MAX_TOUCHKEYS;
	}

	if (data->num_keycodes > 0) {
		ewwow = device_pwopewty_wead_u32_awway(&cwient->dev,
						       "winux,keycodes",
						       data->keycodes,
						       data->num_keycodes);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Unabwe to wead winux,keycodes vawues: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		input_dev->keycode = data->keycodes;
		input_dev->keycodemax = data->num_keycodes;
		input_dev->keycodesize = sizeof(data->keycodes[0]);
		fow (i = 0; i < data->num_keycodes; i++)
			input_set_capabiwity(input_dev,
					     EV_KEY, data->keycodes[i]);
	}

	input_set_capabiwity(input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_abs_pawams(input_dev, ABS_MT_PWESSUWE, 0, 255, 0, 0);
	input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MAJOW,
			     0, MMS114_MAX_AWEA, 0, 0);

	touchscween_pawse_pwopewties(input_dev, twue, &data->pwops);
	if (!data->pwops.max_x || !data->pwops.max_y) {
		dev_dbg(&cwient->dev,
			"missing X/Y size pwopewties, twying wegacy bindings\n");
		ewwow = mms114_pawse_wegacy_bindings(data);
		if (ewwow)
			wetuwn ewwow;

		input_set_abs_pawams(input_dev, ABS_MT_POSITION_X,
				     0, data->pwops.max_x, 0, 0);
		input_set_abs_pawams(input_dev, ABS_MT_POSITION_Y,
				     0, data->pwops.max_y, 0, 0);
	}

	if (data->type == TYPE_MMS114 || data->type == TYPE_MMS134S ||
	    data->type == TYPE_MMS136) {
		/*
		 * The fiwmwawe handwes movement and pwessuwe fuzz, so
		 * don't dupwicate that in softwawe.
		 */
		data->moving_thweshowd = input_abs_get_fuzz(input_dev,
							    ABS_MT_POSITION_X);
		data->contact_thweshowd = input_abs_get_fuzz(input_dev,
							     ABS_MT_PWESSUWE);
		input_abs_set_fuzz(input_dev, ABS_MT_POSITION_X, 0);
		input_abs_set_fuzz(input_dev, ABS_MT_POSITION_Y, 0);
		input_abs_set_fuzz(input_dev, ABS_MT_PWESSUWE, 0);
	}

	input_dev->name = devm_kaspwintf(&cwient->dev, GFP_KEWNEW,
					 "MEWFAS MMS%d Touchscween",
					 data->type);
	if (!input_dev->name)
		wetuwn -ENOMEM;

	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.pawent = &cwient->dev;
	input_dev->open = mms114_input_open;
	input_dev->cwose = mms114_input_cwose;

	ewwow = input_mt_init_swots(input_dev, MMS114_MAX_TOUCH,
				    INPUT_MT_DIWECT);
	if (ewwow)
		wetuwn ewwow;

	input_set_dwvdata(input_dev, data);
	i2c_set_cwientdata(cwient, data);

	data->cowe_weg = devm_weguwatow_get(&cwient->dev, "avdd");
	if (IS_EWW(data->cowe_weg)) {
		ewwow = PTW_EWW(data->cowe_weg);
		dev_eww(&cwient->dev,
			"Unabwe to get the Cowe weguwatow (%d)\n", ewwow);
		wetuwn ewwow;
	}

	data->io_weg = devm_weguwatow_get(&cwient->dev, "vdd");
	if (IS_EWW(data->io_weg)) {
		ewwow = PTW_EWW(data->io_weg);
		dev_eww(&cwient->dev,
			"Unabwe to get the IO weguwatow (%d)\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, mms114_intewwupt,
					  IWQF_ONESHOT | IWQF_NO_AUTOEN,
					  dev_name(&cwient->dev), data);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew intewwupt\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(data->input_dev);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew input device\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int mms114_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mms114_data *data = i2c_get_cwientdata(cwient);
	stwuct input_dev *input_dev = data->input_dev;
	int id;

	/* Wewease aww touch */
	fow (id = 0; id < MMS114_MAX_TOUCH; id++) {
		input_mt_swot(input_dev, id);
		input_mt_wepowt_swot_inactive(input_dev);
	}

	input_mt_wepowt_pointew_emuwation(input_dev, twue);
	input_sync(input_dev);

	mutex_wock(&input_dev->mutex);
	if (input_device_enabwed(input_dev))
		mms114_stop(data);
	mutex_unwock(&input_dev->mutex);

	wetuwn 0;
}

static int mms114_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mms114_data *data = i2c_get_cwientdata(cwient);
	stwuct input_dev *input_dev = data->input_dev;
	int ewwow;

	mutex_wock(&input_dev->mutex);
	if (input_device_enabwed(input_dev)) {
		ewwow = mms114_stawt(data);
		if (ewwow < 0) {
			mutex_unwock(&input_dev->mutex);
			wetuwn ewwow;
		}
	}
	mutex_unwock(&input_dev->mutex);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(mms114_pm_ops, mms114_suspend, mms114_wesume);

static const stwuct i2c_device_id mms114_id[] = {
	{ "mms114", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mms114_id);

#ifdef CONFIG_OF
static const stwuct of_device_id mms114_dt_match[] = {
	{
		.compatibwe = "mewfas,mms114",
		.data = (void *)TYPE_MMS114,
	}, {
		.compatibwe = "mewfas,mms134s",
		.data = (void *)TYPE_MMS134S,
	}, {
		.compatibwe = "mewfas,mms136",
		.data = (void *)TYPE_MMS136,
	}, {
		.compatibwe = "mewfas,mms152",
		.data = (void *)TYPE_MMS152,
	}, {
		.compatibwe = "mewfas,mms345w",
		.data = (void *)TYPE_MMS345W,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, mms114_dt_match);
#endif

static stwuct i2c_dwivew mms114_dwivew = {
	.dwivew = {
		.name	= "mms114",
		.pm	= pm_sweep_ptw(&mms114_pm_ops),
		.of_match_tabwe = of_match_ptw(mms114_dt_match),
	},
	.pwobe		= mms114_pwobe,
	.id_tabwe	= mms114_id,
};

moduwe_i2c_dwivew(mms114_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Joonyoung Shim <jy0922.shim@samsung.com>");
MODUWE_DESCWIPTION("MEWFAS mms114 Touchscween dwivew");
MODUWE_WICENSE("GPW v2");
