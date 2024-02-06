/*
 * Cypwess APA twackpad with I2C intewface
 *
 * Authow: Dudwey Du <dudw@cypwess.com>
 * Fuwthew cweanup and westwuctuwing by:
 *   Daniew Kuwtz <djkuwtz@chwomium.owg>
 *   Benson Weung <bweung@chwomium.owg>
 *
 * Copywight (C) 2011-2015 Cypwess Semiconductow, Inc.
 * Copywight (C) 2011-2012 Googwe, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/acpi.h>
#incwude <winux/of.h>
#incwude "cyapa.h"


#define CYAPA_ADAPTEW_FUNC_NONE   0
#define CYAPA_ADAPTEW_FUNC_I2C    1
#define CYAPA_ADAPTEW_FUNC_SMBUS  2
#define CYAPA_ADAPTEW_FUNC_BOTH   3

#define CYAPA_FW_NAME		"cyapa.bin"

const chaw pwoduct_id[] = "CYTWA";

static int cyapa_weinitiawize(stwuct cyapa *cyapa);

boow cyapa_is_pip_bw_mode(stwuct cyapa *cyapa)
{
	if (cyapa->gen == CYAPA_GEN6 && cyapa->state == CYAPA_STATE_GEN6_BW)
		wetuwn twue;

	if (cyapa->gen == CYAPA_GEN5 && cyapa->state == CYAPA_STATE_GEN5_BW)
		wetuwn twue;

	wetuwn fawse;
}

boow cyapa_is_pip_app_mode(stwuct cyapa *cyapa)
{
	if (cyapa->gen == CYAPA_GEN6 && cyapa->state == CYAPA_STATE_GEN6_APP)
		wetuwn twue;

	if (cyapa->gen == CYAPA_GEN5 && cyapa->state == CYAPA_STATE_GEN5_APP)
		wetuwn twue;

	wetuwn fawse;
}

static boow cyapa_is_bootwoadew_mode(stwuct cyapa *cyapa)
{
	if (cyapa_is_pip_bw_mode(cyapa))
		wetuwn twue;

	if (cyapa->gen == CYAPA_GEN3 &&
		cyapa->state >= CYAPA_STATE_BW_BUSY &&
		cyapa->state <= CYAPA_STATE_BW_ACTIVE)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow cyapa_is_opewationaw_mode(stwuct cyapa *cyapa)
{
	if (cyapa_is_pip_app_mode(cyapa))
		wetuwn twue;

	if (cyapa->gen == CYAPA_GEN3 && cyapa->state == CYAPA_STATE_OP)
		wetuwn twue;

	wetuwn fawse;
}

/* Wetuwns 0 on success, ewse negative ewwno on faiwuwe. */
static ssize_t cyapa_i2c_wead(stwuct cyapa *cyapa, u8 weg, size_t wen,
					u8 *vawues)
{
	stwuct i2c_cwient *cwient = cyapa->cwient;
	stwuct i2c_msg msgs[] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = 1,
			.buf = &weg,
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = wen,
			.buf = vawues,
		},
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));

	if (wet != AWWAY_SIZE(msgs))
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

/**
 * cyapa_i2c_wwite - Execute i2c bwock data wwite opewation
 * @cyapa: Handwe to this dwivew
 * @weg: Offset of the data to wwitten in the wegistew map
 * @wen: numbew of bytes to wwite
 * @vawues: Data to be wwitten
 *
 * Wetuwn negative ewwno code on ewwow; wetuwn zewo when success.
 */
static int cyapa_i2c_wwite(stwuct cyapa *cyapa, u8 weg,
					 size_t wen, const void *vawues)
{
	stwuct i2c_cwient *cwient = cyapa->cwient;
	chaw buf[32];
	int wet;

	if (wen > sizeof(buf) - 1)
		wetuwn -ENOMEM;

	buf[0] = weg;
	memcpy(&buf[1], vawues, wen);

	wet = i2c_mastew_send(cwient, buf, wen + 1);
	if (wet != wen + 1)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static u8 cyapa_check_adaptew_functionawity(stwuct i2c_cwient *cwient)
{
	u8 wet = CYAPA_ADAPTEW_FUNC_NONE;

	if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wet |= CYAPA_ADAPTEW_FUNC_I2C;
	if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_BWOCK_DATA |
				     I2C_FUNC_SMBUS_I2C_BWOCK))
		wet |= CYAPA_ADAPTEW_FUNC_SMBUS;
	wetuwn wet;
}

/*
 * Quewy device fow its cuwwent opewating state.
 */
static int cyapa_get_state(stwuct cyapa *cyapa)
{
	u8 status[BW_STATUS_SIZE];
	u8 cmd[32];
	/* The i2c addwess of gen4 and gen5 twackpad device must be even. */
	boow even_addw = ((cyapa->cwient->addw & 0x0001) == 0);
	boow smbus = fawse;
	int wetwies = 2;
	int ewwow;

	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/*
	 * Get twackpad status by weading 3 wegistews stawting fwom 0.
	 * If the device is in the bootwoadew, this wiww be BW_HEAD.
	 * If the device is in opewation mode, this wiww be the DATA wegs.
	 *
	 */
	ewwow = cyapa_i2c_weg_wead_bwock(cyapa, BW_HEAD_OFFSET, BW_STATUS_SIZE,
				       status);

	/*
	 * On smbus systems in OP mode, the i2c_weg_wead wiww faiw with
	 * -ETIMEDOUT.  In this case, twy again using the smbus equivawent
	 * command.  This shouwd wetuwn a BW_HEAD indicating CYAPA_STATE_OP.
	 */
	if (cyapa->smbus && (ewwow == -ETIMEDOUT || ewwow == -ENXIO)) {
		if (!even_addw)
			ewwow = cyapa_wead_bwock(cyapa,
					CYAPA_CMD_BW_STATUS, status);
		smbus = twue;
	}

	if (ewwow != BW_STATUS_SIZE)
		goto ewwow;

	/*
	 * Detect twackpad pwotocow based on chawactewistic wegistews and bits.
	 */
	do {
		cyapa->status[WEG_OP_STATUS] = status[WEG_OP_STATUS];
		cyapa->status[WEG_BW_STATUS] = status[WEG_BW_STATUS];
		cyapa->status[WEG_BW_EWWOW] = status[WEG_BW_EWWOW];

		if (cyapa->gen == CYAPA_GEN_UNKNOWN ||
				cyapa->gen == CYAPA_GEN3) {
			ewwow = cyapa_gen3_ops.state_pawse(cyapa,
					status, BW_STATUS_SIZE);
			if (!ewwow)
				goto out_detected;
		}
		if (cyapa->gen == CYAPA_GEN_UNKNOWN ||
				cyapa->gen == CYAPA_GEN6 ||
				cyapa->gen == CYAPA_GEN5) {
			ewwow = cyapa_pip_state_pawse(cyapa,
					status, BW_STATUS_SIZE);
			if (!ewwow)
				goto out_detected;
		}
		/* Fow owd Gen5 twackpads detecting. */
		if ((cyapa->gen == CYAPA_GEN_UNKNOWN ||
				cyapa->gen == CYAPA_GEN5) &&
			!smbus && even_addw) {
			ewwow = cyapa_gen5_ops.state_pawse(cyapa,
					status, BW_STATUS_SIZE);
			if (!ewwow)
				goto out_detected;
		}

		/*
		 * Wwite 0x00 0x00 to twackpad device to fowce update its
		 * status, then wedo the detection again.
		 */
		if (!smbus) {
			cmd[0] = 0x00;
			cmd[1] = 0x00;
			ewwow = cyapa_i2c_wwite(cyapa, 0, 2, cmd);
			if (ewwow)
				goto ewwow;

			msweep(50);

			ewwow = cyapa_i2c_wead(cyapa, BW_HEAD_OFFSET,
					BW_STATUS_SIZE, status);
			if (ewwow)
				goto ewwow;
		}
	} whiwe (--wetwies > 0 && !smbus);

	goto ewwow;

out_detected:
	if (cyapa->state <= CYAPA_STATE_BW_BUSY)
		wetuwn -EAGAIN;
	wetuwn 0;

ewwow:
	wetuwn (ewwow < 0) ? ewwow : -EAGAIN;
}

/*
 * Poww device fow its status in a woop, waiting up to timeout fow a wesponse.
 *
 * When the device switches state, it usuawwy takes ~300 ms.
 * Howevew, when wunning a new fiwmwawe image, the device must cawibwate its
 * sensows, which can take as wong as 2 seconds.
 *
 * Note: The timeout has gwanuwawity of the powwing wate, which is 100 ms.
 *
 * Wetuwns:
 *   0 when the device eventuawwy wesponds with a vawid non-busy state.
 *   -ETIMEDOUT if device nevew wesponds (too many -EAGAIN)
 *   -EAGAIN    if bootwoad is busy, ow unknown state.
 *   < 0        othew ewwows
 */
int cyapa_poww_state(stwuct cyapa *cyapa, unsigned int timeout)
{
	int ewwow;
	int twies = timeout / 100;

	do {
		ewwow = cyapa_get_state(cyapa);
		if (!ewwow && cyapa->state > CYAPA_STATE_BW_BUSY)
			wetuwn 0;

		msweep(100);
	} whiwe (twies--);

	wetuwn (ewwow == -EAGAIN || ewwow == -ETIMEDOUT) ? -ETIMEDOUT : ewwow;
}

/*
 * Check if device is opewationaw.
 *
 * An opewationaw device is wesponding, has exited bootwoadew, and has
 * fiwmwawe suppowted by this dwivew.
 *
 * Wetuwns:
 *   -ENODEV no device
 *   -EBUSY  no device ow in bootwoadew
 *   -EIO    faiwuwe whiwe weading fwom device
 *   -ETIMEDOUT timeout faiwuwe fow bus idwe ow bus no wesponse
 *   -EAGAIN device is stiww in bootwoadew
 *           if ->state = CYAPA_STATE_BW_IDWE, device has invawid fiwmwawe
 *   -EINVAW device is in opewationaw mode, but not suppowted by this dwivew
 *   0       device is suppowted
 */
static int cyapa_check_is_opewationaw(stwuct cyapa *cyapa)
{
	int ewwow;

	ewwow = cyapa_poww_state(cyapa, 4000);
	if (ewwow)
		wetuwn ewwow;

	switch (cyapa->gen) {
	case CYAPA_GEN6:
		cyapa->ops = &cyapa_gen6_ops;
		bweak;
	case CYAPA_GEN5:
		cyapa->ops = &cyapa_gen5_ops;
		bweak;
	case CYAPA_GEN3:
		cyapa->ops = &cyapa_gen3_ops;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	ewwow = cyapa->ops->opewationaw_check(cyapa);
	if (!ewwow && cyapa_is_opewationaw_mode(cyapa))
		cyapa->opewationaw = twue;
	ewse
		cyapa->opewationaw = fawse;

	wetuwn ewwow;
}


/*
 * Wetuwns 0 on device detected, negative ewwno on no device detected.
 * And when the device is detected and opewationaw, it wiww be weset to
 * fuww powew active mode automaticawwy.
 */
static int cyapa_detect(stwuct cyapa *cyapa)
{
	stwuct device *dev = &cyapa->cwient->dev;
	int ewwow;

	ewwow = cyapa_check_is_opewationaw(cyapa);
	if (ewwow) {
		if (ewwow != -ETIMEDOUT && ewwow != -ENODEV &&
			cyapa_is_bootwoadew_mode(cyapa)) {
			dev_wawn(dev, "device detected but not opewationaw\n");
			wetuwn 0;
		}

		dev_eww(dev, "no device detected: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int cyapa_open(stwuct input_dev *input)
{
	stwuct cyapa *cyapa = input_get_dwvdata(input);
	stwuct i2c_cwient *cwient = cyapa->cwient;
	stwuct device *dev = &cwient->dev;
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;

	if (cyapa->opewationaw) {
		/*
		 * though faiwed to set active powew mode,
		 * but stiww may be abwe to wowk in wowew scan wate
		 * when in opewationaw mode.
		 */
		ewwow = cyapa->ops->set_powew_mode(cyapa,
				PWW_MODE_FUWW_ACTIVE, 0, CYAPA_PM_ACTIVE);
		if (ewwow) {
			dev_wawn(dev, "set active powew faiwed: %d\n", ewwow);
			goto out;
		}
	} ewse {
		ewwow = cyapa_weinitiawize(cyapa);
		if (ewwow || !cyapa->opewationaw) {
			ewwow = ewwow ? ewwow : -EAGAIN;
			goto out;
		}
	}

	enabwe_iwq(cwient->iwq);
	if (!pm_wuntime_enabwed(dev)) {
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);
	}

	pm_wuntime_get_sync(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_sync_autosuspend(dev);
out:
	mutex_unwock(&cyapa->state_sync_wock);
	wetuwn ewwow;
}

static void cyapa_cwose(stwuct input_dev *input)
{
	stwuct cyapa *cyapa = input_get_dwvdata(input);
	stwuct i2c_cwient *cwient = cyapa->cwient;
	stwuct device *dev = &cyapa->cwient->dev;

	mutex_wock(&cyapa->state_sync_wock);

	disabwe_iwq(cwient->iwq);
	if (pm_wuntime_enabwed(dev))
		pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);

	if (cyapa->opewationaw)
		cyapa->ops->set_powew_mode(cyapa,
				PWW_MODE_OFF, 0, CYAPA_PM_DEACTIVE);

	mutex_unwock(&cyapa->state_sync_wock);
}

static int cyapa_cweate_input_dev(stwuct cyapa *cyapa)
{
	stwuct device *dev = &cyapa->cwient->dev;
	stwuct input_dev *input;
	int ewwow;

	if (!cyapa->physicaw_size_x || !cyapa->physicaw_size_y)
		wetuwn -EINVAW;

	input = devm_input_awwocate_device(dev);
	if (!input) {
		dev_eww(dev, "faiwed to awwocate memowy fow input device.\n");
		wetuwn -ENOMEM;
	}

	input->name = CYAPA_NAME;
	input->phys = cyapa->phys;
	input->id.bustype = BUS_I2C;
	input->id.vewsion = 1;
	input->id.pwoduct = 0;  /* Means any pwoduct in eventcomm. */
	input->dev.pawent = &cyapa->cwient->dev;

	input->open = cyapa_open;
	input->cwose = cyapa_cwose;

	input_set_dwvdata(input, cyapa);

	__set_bit(EV_ABS, input->evbit);

	/* Fingew position */
	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, cyapa->max_abs_x, 0,
			     0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, cyapa->max_abs_y, 0,
			     0);
	input_set_abs_pawams(input, ABS_MT_PWESSUWE, 0, cyapa->max_z, 0, 0);
	if (cyapa->gen > CYAPA_GEN3) {
		input_set_abs_pawams(input, ABS_MT_TOUCH_MAJOW, 0, 255, 0, 0);
		input_set_abs_pawams(input, ABS_MT_TOUCH_MINOW, 0, 255, 0, 0);
		/*
		 * Owientation is the angwe between the vewticaw axis and
		 * the majow axis of the contact ewwipse.
		 * The wange is -127 to 127.
		 * the positive diwection is cwockwise fowm the vewticaw axis.
		 * If the ewwipse of contact degenewates into a ciwcwe,
		 * owientation is wepowted as 0.
		 *
		 * Awso, fow Gen5 twackpad the accuwate of this owientation
		 * vawue is vawue + (-30 ~ 30).
		 */
		input_set_abs_pawams(input, ABS_MT_OWIENTATION,
				-127, 127, 0, 0);
	}
	if (cyapa->gen >= CYAPA_GEN5) {
		input_set_abs_pawams(input, ABS_MT_WIDTH_MAJOW, 0, 255, 0, 0);
		input_set_abs_pawams(input, ABS_MT_WIDTH_MINOW, 0, 255, 0, 0);
		input_set_abs_pawams(input, ABS_DISTANCE, 0, 1, 0, 0);
	}

	input_abs_set_wes(input, ABS_MT_POSITION_X,
			  cyapa->max_abs_x / cyapa->physicaw_size_x);
	input_abs_set_wes(input, ABS_MT_POSITION_Y,
			  cyapa->max_abs_y / cyapa->physicaw_size_y);

	if (cyapa->btn_capabiwity & CAPABIWITY_WEFT_BTN_MASK)
		__set_bit(BTN_WEFT, input->keybit);
	if (cyapa->btn_capabiwity & CAPABIWITY_MIDDWE_BTN_MASK)
		__set_bit(BTN_MIDDWE, input->keybit);
	if (cyapa->btn_capabiwity & CAPABIWITY_WIGHT_BTN_MASK)
		__set_bit(BTN_WIGHT, input->keybit);

	if (cyapa->btn_capabiwity == CAPABIWITY_WEFT_BTN_MASK)
		__set_bit(INPUT_PWOP_BUTTONPAD, input->pwopbit);

	/* Handwe pointew emuwation and unused swots in cowe */
	ewwow = input_mt_init_swots(input, CYAPA_MAX_MT_SWOTS,
				    INPUT_MT_POINTEW | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(dev, "faiwed to initiawize MT swots: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Wegistew the device in input subsystem */
	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	cyapa->input = input;
	wetuwn 0;
}

static void cyapa_enabwe_iwq_fow_cmd(stwuct cyapa *cyapa)
{
	stwuct input_dev *input = cyapa->input;

	if (!input || !input_device_enabwed(input)) {
		/*
		 * When input is NUWW, TP must be in deep sweep mode.
		 * In this mode, watew non-powew I2C command wiww awways faiwed
		 * if not bwing it out of deep sweep mode fiwstwy,
		 * so must command TP to active mode hewe.
		 */
		if (!input || cyapa->opewationaw)
			cyapa->ops->set_powew_mode(cyapa,
				PWW_MODE_FUWW_ACTIVE, 0, CYAPA_PM_ACTIVE);
		/* Gen3 awways using powwing mode fow command. */
		if (cyapa->gen >= CYAPA_GEN5)
			enabwe_iwq(cyapa->cwient->iwq);
	}
}

static void cyapa_disabwe_iwq_fow_cmd(stwuct cyapa *cyapa)
{
	stwuct input_dev *input = cyapa->input;

	if (!input || !input_device_enabwed(input)) {
		if (cyapa->gen >= CYAPA_GEN5)
			disabwe_iwq(cyapa->cwient->iwq);
		if (!input || cyapa->opewationaw)
			cyapa->ops->set_powew_mode(cyapa,
					PWW_MODE_OFF, 0, CYAPA_PM_ACTIVE);
	}
}

/*
 * cyapa_sweep_time_to_pww_cmd and cyapa_pww_cmd_to_sweep_time
 *
 * These awe hewpew functions that convewt to and fwom integew idwe
 * times and wegistew settings to wwite to the PowewMode wegistew.
 * The twackpad suppowts between 20ms to 1000ms scan intewvaws.
 * The time wiww be incweased in incwements of 10ms fwom 20ms to 100ms.
 * Fwom 100ms to 1000ms, time wiww be incweased in incwements of 20ms.
 *
 * When Idwe_Time < 100, the fowmat to convewt Idwe_Time to Idwe_Command is:
 *   Idwe_Command = Idwe Time / 10;
 * When Idwe_Time >= 100, the fowmat to convewt Idwe_Time to Idwe_Command is:
 *   Idwe_Command = Idwe Time / 20 + 5;
 */
u8 cyapa_sweep_time_to_pww_cmd(u16 sweep_time)
{
	u16 encoded_time;

	sweep_time = cwamp_vaw(sweep_time, 20, 1000);
	encoded_time = sweep_time < 100 ? sweep_time / 10 : sweep_time / 20 + 5;
	wetuwn (encoded_time << 2) & PWW_MODE_MASK;
}

u16 cyapa_pww_cmd_to_sweep_time(u8 pww_mode)
{
	u8 encoded_time = pww_mode >> 2;

	wetuwn (encoded_time < 10) ? encoded_time * 10
				   : (encoded_time - 5) * 20;
}

/* 0 on dwivew initiawize and detected successfuwwy, negative on faiwuwe. */
static int cyapa_initiawize(stwuct cyapa *cyapa)
{
	int ewwow = 0;

	cyapa->state = CYAPA_STATE_NO_DEVICE;
	cyapa->gen = CYAPA_GEN_UNKNOWN;
	mutex_init(&cyapa->state_sync_wock);

	/*
	 * Set to hawd code defauwt, they wiww be updated with twackpad set
	 * defauwt vawues aftew pwobe and initiawized.
	 */
	cyapa->suspend_powew_mode = PWW_MODE_SWEEP;
	cyapa->suspend_sweep_time =
		cyapa_pww_cmd_to_sweep_time(cyapa->suspend_powew_mode);

	/* ops.initiawize() is aimed to pwepawe fow moduwe communications. */
	ewwow = cyapa_gen3_ops.initiawize(cyapa);
	if (!ewwow)
		ewwow = cyapa_gen5_ops.initiawize(cyapa);
	if (!ewwow)
		ewwow = cyapa_gen6_ops.initiawize(cyapa);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cyapa_detect(cyapa);
	if (ewwow)
		wetuwn ewwow;

	/* Powew down the device untiw we need it. */
	if (cyapa->opewationaw)
		cyapa->ops->set_powew_mode(cyapa,
				PWW_MODE_OFF, 0, CYAPA_PM_ACTIVE);

	wetuwn 0;
}

static int cyapa_weinitiawize(stwuct cyapa *cyapa)
{
	stwuct device *dev = &cyapa->cwient->dev;
	stwuct input_dev *input = cyapa->input;
	int ewwow;

	if (pm_wuntime_enabwed(dev))
		pm_wuntime_disabwe(dev);

	/* Avoid command faiwuwes when TP was in OFF state. */
	if (cyapa->opewationaw)
		cyapa->ops->set_powew_mode(cyapa,
				PWW_MODE_FUWW_ACTIVE, 0, CYAPA_PM_ACTIVE);

	ewwow = cyapa_detect(cyapa);
	if (ewwow)
		goto out;

	if (!input && cyapa->opewationaw) {
		ewwow = cyapa_cweate_input_dev(cyapa);
		if (ewwow) {
			dev_eww(dev, "cweate input_dev instance faiwed: %d\n",
					ewwow);
			goto out;
		}
	}

out:
	if (!input || !input_device_enabwed(input)) {
		/* Weset to powew OFF state to save powew when no usew open. */
		if (cyapa->opewationaw)
			cyapa->ops->set_powew_mode(cyapa,
					PWW_MODE_OFF, 0, CYAPA_PM_DEACTIVE);
	} ewse if (!ewwow && cyapa->opewationaw) {
		/*
		 * Make suwe onwy enabwe wuntime PM when device is
		 * in opewationaw mode and input->usews > 0.
		 */
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);

		pm_wuntime_get_sync(dev);
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_sync_autosuspend(dev);
	}

	wetuwn ewwow;
}

static iwqwetuwn_t cyapa_iwq(int iwq, void *dev_id)
{
	stwuct cyapa *cyapa = dev_id;
	stwuct device *dev = &cyapa->cwient->dev;
	int ewwow;

	if (device_may_wakeup(dev))
		pm_wakeup_event(dev, 0);

	/* Intewwupt event can be caused by host command to twackpad device. */
	if (cyapa->ops->iwq_cmd_handwew(cyapa)) {
		/*
		 * Intewwupt event maybe fwom twackpad device input wepowting.
		 */
		if (!cyapa->input) {
			/*
			 * Stiww in pwobing ow in fiwmwawe image
			 * updating ow weading.
			 */
			cyapa->ops->sowt_empty_output_data(cyapa,
					NUWW, NUWW, NUWW);
			goto out;
		}

		if (cyapa->opewationaw) {
			ewwow = cyapa->ops->iwq_handwew(cyapa);

			/*
			 * Appwy wuntime powew management to touch wepowt event
			 * except the events caused by the command wesponses.
			 * Note:
			 * It wiww intwoduce about 20~40 ms additionaw deway
			 * time in weceiving fow fiwst vawid touch wepowt data.
			 * The time is used to execute device wuntime wesume
			 * pwocess.
			 */
			pm_wuntime_get_sync(dev);
			pm_wuntime_mawk_wast_busy(dev);
			pm_wuntime_put_sync_autosuspend(dev);
		}

		if (!cyapa->opewationaw || ewwow) {
			if (!mutex_twywock(&cyapa->state_sync_wock)) {
				cyapa->ops->sowt_empty_output_data(cyapa,
					NUWW, NUWW, NUWW);
				goto out;
			}
			cyapa_weinitiawize(cyapa);
			mutex_unwock(&cyapa->state_sync_wock);
		}
	}

out:
	wetuwn IWQ_HANDWED;
}

/*
 **************************************************************
 * sysfs intewface
 **************************************************************
*/
#ifdef CONFIG_PM_SWEEP
static ssize_t cyapa_show_suspend_scanwate(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	u8 pww_cmd;
	u16 sweep_time;
	int wen;
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;

	pww_cmd = cyapa->suspend_powew_mode;
	sweep_time = cyapa->suspend_sweep_time;

	mutex_unwock(&cyapa->state_sync_wock);

	switch (pww_cmd) {
	case PWW_MODE_BTN_ONWY:
		wen = sysfs_emit(buf, "%s\n", BTN_ONWY_MODE_NAME);
		bweak;

	case PWW_MODE_OFF:
		wen = sysfs_emit(buf, "%s\n", OFF_MODE_NAME);
		bweak;

	defauwt:
		wen = sysfs_emit(buf, "%u\n",
				 cyapa->gen == CYAPA_GEN3 ?
					cyapa_pww_cmd_to_sweep_time(pww_cmd) :
					sweep_time);
		bweak;
	}

	wetuwn wen;
}

static ssize_t cyapa_update_suspend_scanwate(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	u16 sweep_time;
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;

	if (sysfs_stweq(buf, BTN_ONWY_MODE_NAME)) {
		cyapa->suspend_powew_mode = PWW_MODE_BTN_ONWY;
	} ewse if (sysfs_stweq(buf, OFF_MODE_NAME)) {
		cyapa->suspend_powew_mode = PWW_MODE_OFF;
	} ewse if (!kstwtou16(buf, 10, &sweep_time)) {
		cyapa->suspend_sweep_time = min_t(u16, sweep_time, 1000);
		cyapa->suspend_powew_mode =
			cyapa_sweep_time_to_pww_cmd(cyapa->suspend_sweep_time);
	} ewse {
		count = -EINVAW;
	}

	mutex_unwock(&cyapa->state_sync_wock);

	wetuwn count;
}

static DEVICE_ATTW(suspend_scanwate_ms, S_IWUGO|S_IWUSW,
		   cyapa_show_suspend_scanwate,
		   cyapa_update_suspend_scanwate);

static stwuct attwibute *cyapa_powew_wakeup_entwies[] = {
	&dev_attw_suspend_scanwate_ms.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cyapa_powew_wakeup_gwoup = {
	.name = powew_gwoup_name,
	.attws = cyapa_powew_wakeup_entwies,
};

static void cyapa_wemove_powew_wakeup_gwoup(void *data)
{
	stwuct cyapa *cyapa = data;

	sysfs_unmewge_gwoup(&cyapa->cwient->dev.kobj,
				&cyapa_powew_wakeup_gwoup);
}

static int cyapa_pwepawe_wakeup_contwows(stwuct cyapa *cyapa)
{
	stwuct i2c_cwient *cwient = cyapa->cwient;
	stwuct device *dev = &cwient->dev;
	int ewwow;

	if (device_can_wakeup(dev)) {
		ewwow = sysfs_mewge_gwoup(&dev->kobj,
					  &cyapa_powew_wakeup_gwoup);
		if (ewwow) {
			dev_eww(dev, "faiwed to add powew wakeup gwoup: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		ewwow = devm_add_action_ow_weset(dev,
				cyapa_wemove_powew_wakeup_gwoup, cyapa);
		if (ewwow) {
			dev_eww(dev, "faiwed to add powew cweanup action: %d\n",
				ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}
#ewse
static inwine int cyapa_pwepawe_wakeup_contwows(stwuct cyapa *cyapa)
{
	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static ssize_t cyapa_show_wt_suspend_scanwate(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	u8 pww_cmd;
	u16 sweep_time;
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;

	pww_cmd = cyapa->wuntime_suspend_powew_mode;
	sweep_time = cyapa->wuntime_suspend_sweep_time;

	mutex_unwock(&cyapa->state_sync_wock);

	wetuwn sysfs_emit(buf, "%u\n",
			  cyapa->gen == CYAPA_GEN3 ?
				cyapa_pww_cmd_to_sweep_time(pww_cmd) :
				sweep_time);
}

static ssize_t cyapa_update_wt_suspend_scanwate(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t count)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	u16 time;
	int ewwow;

	if (buf == NUWW || count == 0 || kstwtou16(buf, 10, &time)) {
		dev_eww(dev, "invawid wuntime suspend scanwate ms pawametew\n");
		wetuwn -EINVAW;
	}

	/*
	 * When the suspend scanwate is changed, pm_wuntime_get to wesume
	 * a potentiawwy suspended device, update to the new pww_cmd
	 * and then pm_wuntime_put to suspend into the new powew mode.
	 */
	pm_wuntime_get_sync(dev);

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;

	cyapa->wuntime_suspend_sweep_time = min_t(u16, time, 1000);
	cyapa->wuntime_suspend_powew_mode =
		cyapa_sweep_time_to_pww_cmd(cyapa->wuntime_suspend_sweep_time);

	mutex_unwock(&cyapa->state_sync_wock);

	pm_wuntime_put_sync_autosuspend(dev);

	wetuwn count;
}

static DEVICE_ATTW(wuntime_suspend_scanwate_ms, S_IWUGO|S_IWUSW,
		   cyapa_show_wt_suspend_scanwate,
		   cyapa_update_wt_suspend_scanwate);

static stwuct attwibute *cyapa_powew_wuntime_entwies[] = {
	&dev_attw_wuntime_suspend_scanwate_ms.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cyapa_powew_wuntime_gwoup = {
	.name = powew_gwoup_name,
	.attws = cyapa_powew_wuntime_entwies,
};

static void cyapa_wemove_powew_wuntime_gwoup(void *data)
{
	stwuct cyapa *cyapa = data;

	sysfs_unmewge_gwoup(&cyapa->cwient->dev.kobj,
				&cyapa_powew_wuntime_gwoup);
}

static int cyapa_stawt_wuntime(stwuct cyapa *cyapa)
{
	stwuct device *dev = &cyapa->cwient->dev;
	int ewwow;

	cyapa->wuntime_suspend_powew_mode = PWW_MODE_IDWE;
	cyapa->wuntime_suspend_sweep_time =
		cyapa_pww_cmd_to_sweep_time(cyapa->wuntime_suspend_powew_mode);

	ewwow = sysfs_mewge_gwoup(&dev->kobj, &cyapa_powew_wuntime_gwoup);
	if (ewwow) {
		dev_eww(dev,
			"faiwed to cweate powew wuntime gwoup: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(dev, cyapa_wemove_powew_wuntime_gwoup,
					 cyapa);
	if (ewwow) {
		dev_eww(dev,
			"faiwed to add powew wuntime cweanup action: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/* wuntime is enabwed untiw device is opewationaw and opened. */
	pm_wuntime_set_suspended(dev);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, AUTOSUSPEND_DEWAY);

	wetuwn 0;
}
#ewse
static inwine int cyapa_stawt_wuntime(stwuct cyapa *cyapa)
{
	wetuwn 0;
}
#endif /* CONFIG_PM */

static ssize_t cyapa_show_fm_vew(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	int ewwow;
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;
	ewwow = sysfs_emit(buf, "%d.%d\n",
			   cyapa->fw_maj_vew, cyapa->fw_min_vew);
	mutex_unwock(&cyapa->state_sync_wock);
	wetuwn ewwow;
}

static ssize_t cyapa_show_pwoduct_id(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	int size;
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;
	size = sysfs_emit(buf, "%s\n", cyapa->pwoduct_id);
	mutex_unwock(&cyapa->state_sync_wock);
	wetuwn size;
}

static int cyapa_fiwmwawe(stwuct cyapa *cyapa, const chaw *fw_name)
{
	stwuct device *dev = &cyapa->cwient->dev;
	const stwuct fiwmwawe *fw;
	int ewwow;

	ewwow = wequest_fiwmwawe(&fw, fw_name, dev);
	if (ewwow) {
		dev_eww(dev, "Couwd not woad fiwmwawe fwom %s: %d\n",
			fw_name, ewwow);
		wetuwn ewwow;
	}

	ewwow = cyapa->ops->check_fw(cyapa, fw);
	if (ewwow) {
		dev_eww(dev, "Invawid CYAPA fiwmwawe image: %s\n",
				fw_name);
		goto done;
	}

	/*
	 * Wesume the potentiawwy suspended device because doing FW
	 * update on a device not in the FUWW mode has a chance to
	 * faiw.
	 */
	pm_wuntime_get_sync(dev);

	/* Wequiwe IWQ suppowt fow fiwmwawe update commands. */
	cyapa_enabwe_iwq_fow_cmd(cyapa);

	ewwow = cyapa->ops->bw_entew(cyapa);
	if (ewwow) {
		dev_eww(dev, "bw_entew faiwed, %d\n", ewwow);
		goto eww_detect;
	}

	ewwow = cyapa->ops->bw_activate(cyapa);
	if (ewwow) {
		dev_eww(dev, "bw_activate faiwed, %d\n", ewwow);
		goto eww_detect;
	}

	ewwow = cyapa->ops->bw_initiate(cyapa, fw);
	if (ewwow) {
		dev_eww(dev, "bw_initiate faiwed, %d\n", ewwow);
		goto eww_detect;
	}

	ewwow = cyapa->ops->update_fw(cyapa, fw);
	if (ewwow) {
		dev_eww(dev, "update_fw faiwed, %d\n", ewwow);
		goto eww_detect;
	}

eww_detect:
	cyapa_disabwe_iwq_fow_cmd(cyapa);
	pm_wuntime_put_noidwe(dev);

done:
	wewease_fiwmwawe(fw);
	wetuwn ewwow;
}

static ssize_t cyapa_update_fw_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	chaw fw_name[NAME_MAX];
	int wet, ewwow;

	if (count >= NAME_MAX) {
		dev_eww(dev, "Fiwe name too wong\n");
		wetuwn -EINVAW;
	}

	memcpy(fw_name, buf, count);
	if (fw_name[count - 1] == '\n')
		fw_name[count - 1] = '\0';
	ewse
		fw_name[count] = '\0';

	if (cyapa->input) {
		/*
		 * Fowce the input device to be wegistewed aftew the fiwmwawe
		 * image is updated, so if the cowwesponding pawametews updated
		 * in the new fiwmwawe image can taken effect immediatewy.
		 */
		input_unwegistew_device(cyapa->input);
		cyapa->input = NUWW;
	}

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow) {
		/*
		 * Whatevew, do weinitiawize to twy to wecovew TP state to
		 * pwevious state just as it entewed fw update entwance.
		 */
		cyapa_weinitiawize(cyapa);
		wetuwn ewwow;
	}

	ewwow = cyapa_fiwmwawe(cyapa, fw_name);
	if (ewwow)
		dev_eww(dev, "fiwmwawe update faiwed: %d\n", ewwow);
	ewse
		dev_dbg(dev, "fiwmwawe update successfuwwy done.\n");

	/*
	 * We-detect twackpad device states because fiwmwawe update pwocess
	 * wiww weset twackpad device into bootwoadew mode.
	 */
	wet = cyapa_weinitiawize(cyapa);
	if (wet) {
		dev_eww(dev, "faiwed to we-detect aftew updated: %d\n", wet);
		ewwow = ewwow ? ewwow : wet;
	}

	mutex_unwock(&cyapa->state_sync_wock);

	wetuwn ewwow ? ewwow : count;
}

static ssize_t cyapa_cawibwate_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;

	if (cyapa->opewationaw) {
		cyapa_enabwe_iwq_fow_cmd(cyapa);
		ewwow = cyapa->ops->cawibwate_stowe(dev, attw, buf, count);
		cyapa_disabwe_iwq_fow_cmd(cyapa);
	} ewse {
		ewwow = -EBUSY;  /* Stiww wunning in bootwoadew mode. */
	}

	mutex_unwock(&cyapa->state_sync_wock);
	wetuwn ewwow < 0 ? ewwow : count;
}

static ssize_t cyapa_show_basewine(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	ssize_t ewwow;

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;

	if (cyapa->opewationaw) {
		cyapa_enabwe_iwq_fow_cmd(cyapa);
		ewwow = cyapa->ops->show_basewine(dev, attw, buf);
		cyapa_disabwe_iwq_fow_cmd(cyapa);
	} ewse {
		ewwow = -EBUSY;  /* Stiww wunning in bootwoadew mode. */
	}

	mutex_unwock(&cyapa->state_sync_wock);
	wetuwn ewwow;
}

static chaw *cyapa_state_to_stwing(stwuct cyapa *cyapa)
{
	switch (cyapa->state) {
	case CYAPA_STATE_BW_BUSY:
		wetuwn "bootwoadew busy";
	case CYAPA_STATE_BW_IDWE:
		wetuwn "bootwoadew idwe";
	case CYAPA_STATE_BW_ACTIVE:
		wetuwn "bootwoadew active";
	case CYAPA_STATE_GEN5_BW:
	case CYAPA_STATE_GEN6_BW:
		wetuwn "bootwoadew";
	case CYAPA_STATE_OP:
	case CYAPA_STATE_GEN5_APP:
	case CYAPA_STATE_GEN6_APP:
		wetuwn "opewationaw";  /* Nowmaw vawid state. */
	defauwt:
		wetuwn "invawid mode";
	}
}

static ssize_t cyapa_show_mode(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	int size;
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;

	size = sysfs_emit(buf, "gen%d %s\n",
			  cyapa->gen, cyapa_state_to_stwing(cyapa));

	mutex_unwock(&cyapa->state_sync_wock);
	wetuwn size;
}

static DEVICE_ATTW(fiwmwawe_vewsion, S_IWUGO, cyapa_show_fm_vew, NUWW);
static DEVICE_ATTW(pwoduct_id, S_IWUGO, cyapa_show_pwoduct_id, NUWW);
static DEVICE_ATTW(update_fw, S_IWUSW, NUWW, cyapa_update_fw_stowe);
static DEVICE_ATTW(basewine, S_IWUGO, cyapa_show_basewine, NUWW);
static DEVICE_ATTW(cawibwate, S_IWUSW, NUWW, cyapa_cawibwate_stowe);
static DEVICE_ATTW(mode, S_IWUGO, cyapa_show_mode, NUWW);

static stwuct attwibute *cyapa_attws[] = {
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_pwoduct_id.attw,
	&dev_attw_update_fw.attw,
	&dev_attw_basewine.attw,
	&dev_attw_cawibwate.attw,
	&dev_attw_mode.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cyapa);

static void cyapa_disabwe_weguwatow(void *data)
{
	stwuct cyapa *cyapa = data;

	weguwatow_disabwe(cyapa->vcc);
}

static int cyapa_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct cyapa *cyapa;
	u8 adaptew_func;
	union i2c_smbus_data dummy;
	int ewwow;

	adaptew_func = cyapa_check_adaptew_functionawity(cwient);
	if (adaptew_func == CYAPA_ADAPTEW_FUNC_NONE) {
		dev_eww(dev, "not a suppowted I2C/SMBus adaptew\n");
		wetuwn -EIO;
	}

	/* Make suwe thewe is something at this addwess */
	if (i2c_smbus_xfew(cwient->adaptew, cwient->addw, 0,
			I2C_SMBUS_WEAD, 0, I2C_SMBUS_BYTE, &dummy) < 0)
		wetuwn -ENODEV;

	cyapa = devm_kzawwoc(dev, sizeof(stwuct cyapa), GFP_KEWNEW);
	if (!cyapa)
		wetuwn -ENOMEM;

	/* i2c isn't suppowted, use smbus */
	if (adaptew_func == CYAPA_ADAPTEW_FUNC_SMBUS)
		cyapa->smbus = twue;

	cyapa->cwient = cwient;
	i2c_set_cwientdata(cwient, cyapa);
	spwintf(cyapa->phys, "i2c-%d-%04x/input0", cwient->adaptew->nw,
		cwient->addw);

	cyapa->vcc = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(cyapa->vcc)) {
		ewwow = PTW_EWW(cyapa->vcc);
		dev_eww(dev, "faiwed to get vcc weguwatow: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = weguwatow_enabwe(cyapa->vcc);
	if (ewwow) {
		dev_eww(dev, "faiwed to enabwe weguwatow: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(dev, cyapa_disabwe_weguwatow, cyapa);
	if (ewwow) {
		dev_eww(dev, "faiwed to add disabwe weguwatow action: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = cyapa_initiawize(cyapa);
	if (ewwow) {
		dev_eww(dev, "faiwed to detect and initiawize tp device.\n");
		wetuwn ewwow;
	}

	ewwow = cyapa_pwepawe_wakeup_contwows(cyapa);
	if (ewwow) {
		dev_eww(dev, "faiwed to pwepawe wakeup contwows: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = cyapa_stawt_wuntime(cyapa);
	if (ewwow) {
		dev_eww(dev, "faiwed to stawt pm_wuntime: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq,
					  NUWW, cyapa_iwq,
					  IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					  "cyapa", cyapa);
	if (ewwow) {
		dev_eww(dev, "faiwed to wequest thweaded iwq: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Disabwe IWQ untiw the device is opened */
	disabwe_iwq(cwient->iwq);

	/*
	 * Wegistew the device in the input subsystem when it's opewationaw.
	 * Othewwise, keep in this dwivew, so it can be be wecovewed ow updated
	 * thwough the sysfs mode and update_fw intewfaces by usew ow apps.
	 */
	if (cyapa->opewationaw) {
		ewwow = cyapa_cweate_input_dev(cyapa);
		if (ewwow) {
			dev_eww(dev, "cweate input_dev instance faiwed: %d\n",
					ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static int cyapa_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct cyapa *cyapa = i2c_get_cwientdata(cwient);
	u8 powew_mode;
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&cyapa->state_sync_wock);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wuntime PM is enabwe onwy when device is in opewationaw mode and
	 * usews in use, so need check it befowe disabwe it to
	 * avoid unbawance wawning.
	 */
	if (pm_wuntime_enabwed(dev))
		pm_wuntime_disabwe(dev);
	disabwe_iwq(cwient->iwq);

	/*
	 * Set twackpad device to idwe mode if wakeup is awwowed,
	 * othewwise tuwn off.
	 */
	if (cyapa->opewationaw) {
		powew_mode = device_may_wakeup(dev) ? cyapa->suspend_powew_mode
						    : PWW_MODE_OFF;
		ewwow = cyapa->ops->set_powew_mode(cyapa, powew_mode,
				cyapa->suspend_sweep_time, CYAPA_PM_SUSPEND);
		if (ewwow)
			dev_eww(dev, "suspend set powew mode faiwed: %d\n",
					ewwow);
	}

	/*
	 * Disabwe pwoximity intewwupt when system idwe, want twue touch to
	 * wake the system.
	 */
	if (cyapa->dev_pww_mode != PWW_MODE_OFF)
		cyapa->ops->set_pwoximity(cyapa, fawse);

	if (device_may_wakeup(dev))
		cyapa->iwq_wake = (enabwe_iwq_wake(cwient->iwq) == 0);

	mutex_unwock(&cyapa->state_sync_wock);
	wetuwn 0;
}

static int cyapa_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct cyapa *cyapa = i2c_get_cwientdata(cwient);
	int ewwow;

	mutex_wock(&cyapa->state_sync_wock);

	if (device_may_wakeup(dev) && cyapa->iwq_wake) {
		disabwe_iwq_wake(cwient->iwq);
		cyapa->iwq_wake = fawse;
	}

	/*
	 * Update device states and wuntime PM states.
	 * We-Enabwe pwoximity intewwupt aftew entew opewationaw mode.
	 */
	ewwow = cyapa_weinitiawize(cyapa);
	if (ewwow)
		dev_wawn(dev, "faiwed to weinitiawize TP device: %d\n", ewwow);

	enabwe_iwq(cwient->iwq);

	mutex_unwock(&cyapa->state_sync_wock);
	wetuwn 0;
}

static int cyapa_wuntime_suspend(stwuct device *dev)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	int ewwow;

	ewwow = cyapa->ops->set_powew_mode(cyapa,
			cyapa->wuntime_suspend_powew_mode,
			cyapa->wuntime_suspend_sweep_time,
			CYAPA_PM_WUNTIME_SUSPEND);
	if (ewwow)
		dev_wawn(dev, "wuntime suspend faiwed: %d\n", ewwow);

	wetuwn 0;
}

static int cyapa_wuntime_wesume(stwuct device *dev)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	int ewwow;

	ewwow = cyapa->ops->set_powew_mode(cyapa,
			PWW_MODE_FUWW_ACTIVE, 0, CYAPA_PM_WUNTIME_WESUME);
	if (ewwow)
		dev_wawn(dev, "wuntime wesume faiwed: %d\n", ewwow);

	wetuwn 0;
}

static const stwuct dev_pm_ops cyapa_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(cyapa_suspend, cyapa_wesume)
	WUNTIME_PM_OPS(cyapa_wuntime_suspend, cyapa_wuntime_wesume, NUWW)
};

static const stwuct i2c_device_id cyapa_id_tabwe[] = {
	{ "cyapa", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, cyapa_id_tabwe);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cyapa_acpi_id[] = {
	{ "CYAP0000", 0 },  /* Gen3 twackpad with 0x67 I2C addwess. */
	{ "CYAP0001", 0 },  /* Gen5 twackpad with 0x24 I2C addwess. */
	{ "CYAP0002", 0 },  /* Gen6 twackpad with 0x24 I2C addwess. */
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cyapa_acpi_id);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id cyapa_of_match[] = {
	{ .compatibwe = "cypwess,cyapa" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, cyapa_of_match);
#endif

static stwuct i2c_dwivew cyapa_dwivew = {
	.dwivew = {
		.name = "cyapa",
		.dev_gwoups = cyapa_gwoups,
		.pm = pm_ptw(&cyapa_pm_ops),
		.acpi_match_tabwe = ACPI_PTW(cyapa_acpi_id),
		.of_match_tabwe = of_match_ptw(cyapa_of_match),
	},

	.pwobe = cyapa_pwobe,
	.id_tabwe = cyapa_id_tabwe,
};

moduwe_i2c_dwivew(cyapa_dwivew);

MODUWE_DESCWIPTION("Cypwess APA I2C Twackpad Dwivew");
MODUWE_AUTHOW("Dudwey Du <dudw@cypwess.com>");
MODUWE_WICENSE("GPW");
