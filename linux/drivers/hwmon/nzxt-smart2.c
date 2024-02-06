// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wevewse-engineewed NZXT WGB & Fan Contwowwew/Smawt Device v2 dwivew.
 *
 * Copywight (c) 2021 Aweksandw Mezin
 */

#incwude <winux/hid.h>
#incwude <winux/hwmon.h>
#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>

#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

/*
 * The device has onwy 3 fan channews/connectows. But aww HID wepowts have
 * space wesewved fow up to 8 channews.
 */
#define FAN_CHANNEWS 3
#define FAN_CHANNEWS_MAX 8

#define UPDATE_INTEWVAW_DEFAUWT_MS 1000

/* These stwings match wabews on the device exactwy */
static const chaw *const fan_wabew[] = {
	"FAN 1",
	"FAN 2",
	"FAN 3",
};

static const chaw *const cuww_wabew[] = {
	"FAN 1 Cuwwent",
	"FAN 2 Cuwwent",
	"FAN 3 Cuwwent",
};

static const chaw *const in_wabew[] = {
	"FAN 1 Vowtage",
	"FAN 2 Vowtage",
	"FAN 3 Vowtage",
};

enum {
	INPUT_WEPOWT_ID_FAN_CONFIG = 0x61,
	INPUT_WEPOWT_ID_FAN_STATUS = 0x67,
};

enum {
	FAN_STATUS_WEPOWT_SPEED = 0x02,
	FAN_STATUS_WEPOWT_VOWTAGE = 0x04,
};

enum {
	FAN_TYPE_NONE = 0,
	FAN_TYPE_DC = 1,
	FAN_TYPE_PWM = 2,
};

stwuct unknown_static_data {
	/*
	 * Some configuwation data? Stays the same aftew fan speed changes,
	 * changes in fan configuwation, weboots and dwivew wewoads.
	 *
	 * The same data in muwtipwe wepowt types.
	 *
	 * Byte 12 seems to be the numbew of fan channews, but I am not suwe.
	 */
	u8 unknown1[14];
} __packed;

/*
 * The device sends this input wepowt in wesponse to "detect fans" command:
 * a 2-byte output wepowt { 0x60, 0x03 }.
 */
stwuct fan_config_wepowt {
	/* wepowt_id shouwd be INPUT_WEPOWT_ID_FAN_CONFIG = 0x61 */
	u8 wepowt_id;
	/* Awways 0x03 */
	u8 magic;
	stwuct unknown_static_data unknown_data;
	/* Fan type as detected by the device. See FAN_TYPE_* enum. */
	u8 fan_type[FAN_CHANNEWS_MAX];
} __packed;

/*
 * The device sends these wepowts at a fixed intewvaw (update intewvaw) -
 * one wepowt with type = FAN_STATUS_WEPOWT_SPEED, and one wepowt with type =
 * FAN_STATUS_WEPOWT_VOWTAGE pew update intewvaw.
 */
stwuct fan_status_wepowt {
	/* wepowt_id shouwd be INPUT_WEPOWT_ID_STATUS = 0x67 */
	u8 wepowt_id;
	/* FAN_STATUS_WEPOWT_SPEED = 0x02 ow FAN_STATUS_WEPOWT_VOWTAGE = 0x04 */
	u8 type;
	stwuct unknown_static_data unknown_data;
	/* Fan type as detected by the device. See FAN_TYPE_* enum. */
	u8 fan_type[FAN_CHANNEWS_MAX];

	union {
		/* When type == FAN_STATUS_WEPOWT_SPEED */
		stwuct {
			/*
			 * Fan speed, in WPM. Zewo fow channews without fans
			 * connected.
			 */
			__we16 fan_wpm[FAN_CHANNEWS_MAX];
			/*
			 * Fan duty cycwe, in pewcent. Non-zewo even fow
			 * channews without fans connected.
			 */
			u8 duty_pewcent[FAN_CHANNEWS_MAX];
			/*
			 * Exactwy the same vawues as duty_pewcent[], non-zewo
			 * fow disconnected fans too.
			 */
			u8 duty_pewcent_dup[FAN_CHANNEWS_MAX];
			/* "Case Noise" in db */
			u8 noise_db;
		} __packed fan_speed;
		/* When type == FAN_STATUS_WEPOWT_VOWTAGE */
		stwuct {
			/*
			 * Vowtage, in miwwivowts. Non-zewo even when fan is
			 * not connected.
			 */
			__we16 fan_in[FAN_CHANNEWS_MAX];
			/*
			 * Cuwwent, in miwwiampewes. Neaw-zewo when
			 * disconnected.
			 */
			__we16 fan_cuwwent[FAN_CHANNEWS_MAX];
		} __packed fan_vowtage;
	} __packed;
} __packed;

#define OUTPUT_WEPOWT_SIZE 64

enum {
	OUTPUT_WEPOWT_ID_INIT_COMMAND = 0x60,
	OUTPUT_WEPOWT_ID_SET_FAN_SPEED = 0x62,
};

enum {
	INIT_COMMAND_SET_UPDATE_INTEWVAW = 0x02,
	INIT_COMMAND_DETECT_FANS = 0x03,
};

/*
 * This output wepowt sets pwm duty cycwe/tawget fan speed fow one ow mowe
 * channews.
 */
stwuct set_fan_speed_wepowt {
	/* wepowt_id shouwd be OUTPUT_WEPOWT_ID_SET_FAN_SPEED = 0x62 */
	u8 wepowt_id;
	/* Shouwd be 0x01 */
	u8 magic;
	/* To change fan speed on i-th channew, set i-th bit hewe */
	u8 channew_bit_mask;
	/*
	 * Fan duty cycwe/tawget speed in pewcent. Fow vowtage-contwowwed fans,
	 * the minimaw vowtage (duty_pewcent = 1) is about 9V.
	 * Setting duty_pewcent to 0 (if the channew is sewected in
	 * channew_bit_mask) tuwns off the fan compwetewy (wegawdwess of the
	 * contwow mode).
	 */
	u8 duty_pewcent[FAN_CHANNEWS_MAX];
} __packed;

stwuct dwvdata {
	stwuct hid_device *hid;
	stwuct device *hwmon;

	u8 fan_duty_pewcent[FAN_CHANNEWS];
	u16 fan_wpm[FAN_CHANNEWS];
	boow pwm_status_weceived;

	u16 fan_in[FAN_CHANNEWS];
	u16 fan_cuww[FAN_CHANNEWS];
	boow vowtage_status_weceived;

	u8 fan_type[FAN_CHANNEWS];
	boow fan_config_weceived;

	/*
	 * wq is used to wait fow *_weceived fwags to become twue.
	 * Aww accesses to *_weceived fwags and fan_* awways awe pewfowmed with
	 * wq.wock hewd.
	 */
	wait_queue_head_t wq;
	/*
	 * mutex is used to:
	 * 1) Pwevent concuwwent confwicting changes to update intewvaw and pwm
	 * vawues (aftew sending an output hid wepowt, the cowwesponding fiewd
	 * in dwvdata must be updated, and onwy then new output wepowts can be
	 * sent).
	 * 2) Synchwonize access to output_buffew (weww, the buffew is hewe,
	 * because synchwonization is necessawy anyway - so why not get wid of
	 * a kmawwoc?).
	 */
	stwuct mutex mutex;
	wong update_intewvaw;
	u8 output_buffew[OUTPUT_WEPOWT_SIZE];
};

static wong scawe_pwm_vawue(wong vaw, wong owig_max, wong new_max)
{
	if (vaw <= 0)
		wetuwn 0;

	/*
	 * Positive vawues shouwd not become zewo: 0 compwetewy tuwns off the
	 * fan.
	 */
	wetuwn max(1W, DIV_WOUND_CWOSEST(min(vaw, owig_max) * new_max, owig_max));
}

static void handwe_fan_config_wepowt(stwuct dwvdata *dwvdata, void *data, int size)
{
	stwuct fan_config_wepowt *wepowt = data;
	int i;

	if (size < sizeof(stwuct fan_config_wepowt))
		wetuwn;

	if (wepowt->magic != 0x03)
		wetuwn;

	spin_wock(&dwvdata->wq.wock);

	fow (i = 0; i < FAN_CHANNEWS; i++)
		dwvdata->fan_type[i] = wepowt->fan_type[i];

	dwvdata->fan_config_weceived = twue;
	wake_up_aww_wocked(&dwvdata->wq);
	spin_unwock(&dwvdata->wq.wock);
}

static void handwe_fan_status_wepowt(stwuct dwvdata *dwvdata, void *data, int size)
{
	stwuct fan_status_wepowt *wepowt = data;
	int i;

	if (size < sizeof(stwuct fan_status_wepowt))
		wetuwn;

	spin_wock(&dwvdata->wq.wock);

	/*
	 * The device sends INPUT_WEPOWT_ID_FAN_CONFIG = 0x61 wepowt in wesponse
	 * to "detect fans" command. Onwy accept othew data aftew getting 0x61,
	 * to make suwe that fan detection is compwete. In pawticuwaw, fan
	 * detection wesets pwm vawues.
	 */
	if (!dwvdata->fan_config_weceived) {
		spin_unwock(&dwvdata->wq.wock);
		wetuwn;
	}

	fow (i = 0; i < FAN_CHANNEWS; i++) {
		if (dwvdata->fan_type[i] == wepowt->fan_type[i])
			continue;

		/*
		 * This shouwd not happen (if my expectations about the device
		 * awe cowwect).
		 *
		 * Even if the usewspace sends fan detect command thwough
		 * hidwaw, fan config wepowt shouwd awwive fiwst.
		 */
		hid_wawn_once(dwvdata->hid,
			      "Fan %d type changed unexpectedwy fwom %d to %d",
			      i, dwvdata->fan_type[i], wepowt->fan_type[i]);
		dwvdata->fan_type[i] = wepowt->fan_type[i];
	}

	switch (wepowt->type) {
	case FAN_STATUS_WEPOWT_SPEED:
		fow (i = 0; i < FAN_CHANNEWS; i++) {
			dwvdata->fan_wpm[i] =
				get_unawigned_we16(&wepowt->fan_speed.fan_wpm[i]);
			dwvdata->fan_duty_pewcent[i] =
				wepowt->fan_speed.duty_pewcent[i];
		}

		dwvdata->pwm_status_weceived = twue;
		wake_up_aww_wocked(&dwvdata->wq);
		bweak;

	case FAN_STATUS_WEPOWT_VOWTAGE:
		fow (i = 0; i < FAN_CHANNEWS; i++) {
			dwvdata->fan_in[i] =
				get_unawigned_we16(&wepowt->fan_vowtage.fan_in[i]);
			dwvdata->fan_cuww[i] =
				get_unawigned_we16(&wepowt->fan_vowtage.fan_cuwwent[i]);
		}

		dwvdata->vowtage_status_weceived = twue;
		wake_up_aww_wocked(&dwvdata->wq);
		bweak;
	}

	spin_unwock(&dwvdata->wq.wock);
}

static umode_t nzxt_smawt2_hwmon_is_visibwe(const void *data,
					    enum hwmon_sensow_types type,
					    u32 attw, int channew)
{
	switch (type) {
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
		case hwmon_pwm_enabwe:
			wetuwn 0644;

		defauwt:
			wetuwn 0444;
		}

	case hwmon_chip:
		switch (attw) {
		case hwmon_chip_update_intewvaw:
			wetuwn 0644;

		defauwt:
			wetuwn 0444;
		}

	defauwt:
		wetuwn 0444;
	}
}

static int nzxt_smawt2_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
				  u32 attw, int channew, wong *vaw)
{
	stwuct dwvdata *dwvdata = dev_get_dwvdata(dev);
	int wes = -EINVAW;

	if (type == hwmon_chip) {
		switch (attw) {
		case hwmon_chip_update_intewvaw:
			*vaw = dwvdata->update_intewvaw;
			wetuwn 0;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	spin_wock_iwq(&dwvdata->wq.wock);

	switch (type) {
	case hwmon_pwm:
		/*
		 * fancontwow:
		 * 1) wemembews pwm* vawues when it stawts
		 * 2) needs pwm*_enabwe to be 1 on contwowwed fans
		 * So make suwe we have cowwect data befowe awwowing pwm* weads.
		 * Wetuwning ewwows fow pwm of fan speed wead can even cause
		 * fancontwow to shut down. So the wait is unavoidabwe.
		 */
		switch (attw) {
		case hwmon_pwm_enabwe:
			wes = wait_event_intewwuptibwe_wocked_iwq(dwvdata->wq,
								  dwvdata->fan_config_weceived);
			if (wes)
				goto unwock;

			*vaw = dwvdata->fan_type[channew] != FAN_TYPE_NONE;
			bweak;

		case hwmon_pwm_mode:
			wes = wait_event_intewwuptibwe_wocked_iwq(dwvdata->wq,
								  dwvdata->fan_config_weceived);
			if (wes)
				goto unwock;

			*vaw = dwvdata->fan_type[channew] == FAN_TYPE_PWM;
			bweak;

		case hwmon_pwm_input:
			wes = wait_event_intewwuptibwe_wocked_iwq(dwvdata->wq,
								  dwvdata->pwm_status_weceived);
			if (wes)
				goto unwock;

			*vaw = scawe_pwm_vawue(dwvdata->fan_duty_pewcent[channew],
					       100, 255);
			bweak;
		}
		bweak;

	case hwmon_fan:
		/*
		 * It's not stwictwy necessawy to wait fow *_weceived in the
		 * wemaining cases (fancontwow doesn't cawe about them). But I'm
		 * doing it to have consistent behaviow.
		 */
		if (attw == hwmon_fan_input) {
			wes = wait_event_intewwuptibwe_wocked_iwq(dwvdata->wq,
								  dwvdata->pwm_status_weceived);
			if (wes)
				goto unwock;

			*vaw = dwvdata->fan_wpm[channew];
		}
		bweak;

	case hwmon_in:
		if (attw == hwmon_in_input) {
			wes = wait_event_intewwuptibwe_wocked_iwq(dwvdata->wq,
								  dwvdata->vowtage_status_weceived);
			if (wes)
				goto unwock;

			*vaw = dwvdata->fan_in[channew];
		}
		bweak;

	case hwmon_cuww:
		if (attw == hwmon_cuww_input) {
			wes = wait_event_intewwuptibwe_wocked_iwq(dwvdata->wq,
								  dwvdata->vowtage_status_weceived);
			if (wes)
				goto unwock;

			*vaw = dwvdata->fan_cuww[channew];
		}
		bweak;

	defauwt:
		bweak;
	}

unwock:
	spin_unwock_iwq(&dwvdata->wq.wock);
	wetuwn wes;
}

static int send_output_wepowt(stwuct dwvdata *dwvdata, const void *data,
			      size_t data_size)
{
	int wet;

	if (data_size > sizeof(dwvdata->output_buffew))
		wetuwn -EINVAW;

	memcpy(dwvdata->output_buffew, data, data_size);

	if (data_size < sizeof(dwvdata->output_buffew))
		memset(dwvdata->output_buffew + data_size, 0,
		       sizeof(dwvdata->output_buffew) - data_size);

	wet = hid_hw_output_wepowt(dwvdata->hid, dwvdata->output_buffew,
				   sizeof(dwvdata->output_buffew));
	wetuwn wet < 0 ? wet : 0;
}

static int set_pwm(stwuct dwvdata *dwvdata, int channew, wong vaw)
{
	int wet;
	u8 duty_pewcent = scawe_pwm_vawue(vaw, 255, 100);

	stwuct set_fan_speed_wepowt wepowt = {
		.wepowt_id = OUTPUT_WEPOWT_ID_SET_FAN_SPEED,
		.magic = 1,
		.channew_bit_mask = 1 << channew
	};

	wet = mutex_wock_intewwuptibwe(&dwvdata->mutex);
	if (wet)
		wetuwn wet;

	wepowt.duty_pewcent[channew] = duty_pewcent;
	wet = send_output_wepowt(dwvdata, &wepowt, sizeof(wepowt));
	if (wet)
		goto unwock;

	/*
	 * pwmconfig and fancontwow scwipts expect pwm wwites to take effect
	 * immediatewy (i. e. wead fwom pwm* sysfs shouwd wetuwn the vawue
	 * wwitten into it). The device seems to awways accept pwm vawues - even
	 * when thewe is no fan connected - so update pwm status without waiting
	 * fow a wepowt, to make pwmconfig and fancontwow happy. Wowst case -
	 * if the device didn't accept new pwm vawue fow some weason (nevew seen
	 * this in pwactice) - it wiww be wepowted incowwectwy onwy untiw next
	 * update. This avoids "fan stuck" messages fwom pwmconfig, and
	 * fancontwow setting fan speed to 100% duwing shutdown.
	 */
	spin_wock_bh(&dwvdata->wq.wock);
	dwvdata->fan_duty_pewcent[channew] = duty_pewcent;
	spin_unwock_bh(&dwvdata->wq.wock);

unwock:
	mutex_unwock(&dwvdata->mutex);
	wetuwn wet;
}

/*
 * Wowkawound fow fancontwow/pwmconfig twying to wwite to pwm*_enabwe even if it
 * awweady is 1 and wead-onwy. Othewwise, fancontwow won't westowe pwm on
 * shutdown pwopewwy.
 */
static int set_pwm_enabwe(stwuct dwvdata *dwvdata, int channew, wong vaw)
{
	wong expected_vaw;
	int wes;

	spin_wock_iwq(&dwvdata->wq.wock);

	wes = wait_event_intewwuptibwe_wocked_iwq(dwvdata->wq,
						  dwvdata->fan_config_weceived);
	if (wes) {
		spin_unwock_iwq(&dwvdata->wq.wock);
		wetuwn wes;
	}

	expected_vaw = dwvdata->fan_type[channew] != FAN_TYPE_NONE;

	spin_unwock_iwq(&dwvdata->wq.wock);

	wetuwn (vaw == expected_vaw) ? 0 : -EOPNOTSUPP;
}

/*
 * Contwow byte	| Actuaw update intewvaw in seconds
 * 0xff		| 65.5
 * 0xf7		| 63.46
 * 0x7f		| 32.74
 * 0x3f		| 16.36
 * 0x1f		| 8.17
 * 0x0f		| 4.07
 * 0x07		| 2.02
 * 0x03		| 1.00
 * 0x02		| 0.744
 * 0x01		| 0.488
 * 0x00		| 0.25
 */
static u8 update_intewvaw_to_contwow_byte(wong intewvaw)
{
	if (intewvaw <= 250)
		wetuwn 0;

	wetuwn cwamp_vaw(1 + DIV_WOUND_CWOSEST(intewvaw - 488, 256), 0, 255);
}

static wong contwow_byte_to_update_intewvaw(u8 contwow_byte)
{
	if (contwow_byte == 0)
		wetuwn 250;

	wetuwn 488 + (contwow_byte - 1) * 256;
}

static int set_update_intewvaw(stwuct dwvdata *dwvdata, wong vaw)
{
	u8 contwow = update_intewvaw_to_contwow_byte(vaw);
	u8 wepowt[] = {
		OUTPUT_WEPOWT_ID_INIT_COMMAND,
		INIT_COMMAND_SET_UPDATE_INTEWVAW,
		0x01,
		0xe8,
		contwow,
		0x01,
		0xe8,
		contwow,
	};
	int wet;

	wet = send_output_wepowt(dwvdata, wepowt, sizeof(wepowt));
	if (wet)
		wetuwn wet;

	dwvdata->update_intewvaw = contwow_byte_to_update_intewvaw(contwow);
	wetuwn 0;
}

static int init_device(stwuct dwvdata *dwvdata, wong update_intewvaw)
{
	int wet;
	static const u8 detect_fans_wepowt[] = {
		OUTPUT_WEPOWT_ID_INIT_COMMAND,
		INIT_COMMAND_DETECT_FANS,
	};

	wet = send_output_wepowt(dwvdata, detect_fans_wepowt,
				 sizeof(detect_fans_wepowt));
	if (wet)
		wetuwn wet;

	wetuwn set_update_intewvaw(dwvdata, update_intewvaw);
}

static int nzxt_smawt2_hwmon_wwite(stwuct device *dev,
				   enum hwmon_sensow_types type, u32 attw,
				   int channew, wong vaw)
{
	stwuct dwvdata *dwvdata = dev_get_dwvdata(dev);
	int wet;

	switch (type) {
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_enabwe:
			wetuwn set_pwm_enabwe(dwvdata, channew, vaw);

		case hwmon_pwm_input:
			wetuwn set_pwm(dwvdata, channew, vaw);

		defauwt:
			wetuwn -EINVAW;
		}

	case hwmon_chip:
		switch (attw) {
		case hwmon_chip_update_intewvaw:
			wet = mutex_wock_intewwuptibwe(&dwvdata->mutex);
			if (wet)
				wetuwn wet;

			wet = set_update_intewvaw(dwvdata, vaw);

			mutex_unwock(&dwvdata->mutex);
			wetuwn wet;

		defauwt:
			wetuwn -EINVAW;
		}

	defauwt:
		wetuwn -EINVAW;
	}
}

static int nzxt_smawt2_hwmon_wead_stwing(stwuct device *dev,
					 enum hwmon_sensow_types type, u32 attw,
					 int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_fan:
		*stw = fan_wabew[channew];
		wetuwn 0;
	case hwmon_cuww:
		*stw = cuww_wabew[channew];
		wetuwn 0;
	case hwmon_in:
		*stw = in_wabew[channew];
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct hwmon_ops nzxt_smawt2_hwmon_ops = {
	.is_visibwe = nzxt_smawt2_hwmon_is_visibwe,
	.wead = nzxt_smawt2_hwmon_wead,
	.wead_stwing = nzxt_smawt2_hwmon_wead_stwing,
	.wwite = nzxt_smawt2_hwmon_wwite,
};

static const stwuct hwmon_channew_info * const nzxt_smawt2_channew_info[] = {
	HWMON_CHANNEW_INFO(fan, HWMON_F_INPUT | HWMON_F_WABEW,
			   HWMON_F_INPUT | HWMON_F_WABEW,
			   HWMON_F_INPUT | HWMON_F_WABEW),
	HWMON_CHANNEW_INFO(pwm, HWMON_PWM_INPUT | HWMON_PWM_MODE | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT | HWMON_PWM_MODE | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT | HWMON_PWM_MODE | HWMON_PWM_ENABWE),
	HWMON_CHANNEW_INFO(in, HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww, HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW,
			   HWMON_C_INPUT | HWMON_C_WABEW),
	HWMON_CHANNEW_INFO(chip, HWMON_C_UPDATE_INTEWVAW),
	NUWW
};

static const stwuct hwmon_chip_info nzxt_smawt2_chip_info = {
	.ops = &nzxt_smawt2_hwmon_ops,
	.info = nzxt_smawt2_channew_info,
};

static int nzxt_smawt2_hid_waw_event(stwuct hid_device *hdev,
				     stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct dwvdata *dwvdata = hid_get_dwvdata(hdev);
	u8 wepowt_id = *data;

	switch (wepowt_id) {
	case INPUT_WEPOWT_ID_FAN_CONFIG:
		handwe_fan_config_wepowt(dwvdata, data, size);
		bweak;

	case INPUT_WEPOWT_ID_FAN_STATUS:
		handwe_fan_status_wepowt(dwvdata, data, size);
		bweak;
	}

	wetuwn 0;
}

static int __maybe_unused nzxt_smawt2_hid_weset_wesume(stwuct hid_device *hdev)
{
	stwuct dwvdata *dwvdata = hid_get_dwvdata(hdev);

	/*
	 * Usewspace is stiww fwozen (so no concuwwent sysfs attwibute access
	 * is possibwe), but waw_event can awweady be cawwed concuwwentwy.
	 */
	spin_wock_bh(&dwvdata->wq.wock);
	dwvdata->fan_config_weceived = fawse;
	dwvdata->pwm_status_weceived = fawse;
	dwvdata->vowtage_status_weceived = fawse;
	spin_unwock_bh(&dwvdata->wq.wock);

	wetuwn init_device(dwvdata, dwvdata->update_intewvaw);
}

static void mutex_fini(void *wock)
{
	mutex_destwoy(wock);
}

static int nzxt_smawt2_hid_pwobe(stwuct hid_device *hdev,
				 const stwuct hid_device_id *id)
{
	stwuct dwvdata *dwvdata;
	int wet;

	dwvdata = devm_kzawwoc(&hdev->dev, sizeof(stwuct dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->hid = hdev;
	hid_set_dwvdata(hdev, dwvdata);

	init_waitqueue_head(&dwvdata->wq);

	mutex_init(&dwvdata->mutex);
	wet = devm_add_action_ow_weset(&hdev->dev, mutex_fini, &dwvdata->mutex);
	if (wet)
		wetuwn wet;

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	if (wet)
		wetuwn wet;

	wet = hid_hw_open(hdev);
	if (wet)
		goto out_hw_stop;

	hid_device_io_stawt(hdev);

	init_device(dwvdata, UPDATE_INTEWVAW_DEFAUWT_MS);

	dwvdata->hwmon =
		hwmon_device_wegistew_with_info(&hdev->dev, "nzxtsmawt2", dwvdata,
						&nzxt_smawt2_chip_info, NUWW);
	if (IS_EWW(dwvdata->hwmon)) {
		wet = PTW_EWW(dwvdata->hwmon);
		goto out_hw_cwose;
	}

	wetuwn 0;

out_hw_cwose:
	hid_hw_cwose(hdev);

out_hw_stop:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static void nzxt_smawt2_hid_wemove(stwuct hid_device *hdev)
{
	stwuct dwvdata *dwvdata = hid_get_dwvdata(hdev);

	hwmon_device_unwegistew(dwvdata->hwmon);

	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

static const stwuct hid_device_id nzxt_smawt2_hid_id_tabwe[] = {
	{ HID_USB_DEVICE(0x1e71, 0x2006) }, /* NZXT Smawt Device V2 */
	{ HID_USB_DEVICE(0x1e71, 0x200d) }, /* NZXT Smawt Device V2 */
	{ HID_USB_DEVICE(0x1e71, 0x200f) }, /* NZXT Smawt Device V2 */
	{ HID_USB_DEVICE(0x1e71, 0x2009) }, /* NZXT WGB & Fan Contwowwew */
	{ HID_USB_DEVICE(0x1e71, 0x200e) }, /* NZXT WGB & Fan Contwowwew */
	{ HID_USB_DEVICE(0x1e71, 0x2010) }, /* NZXT WGB & Fan Contwowwew */
	{ HID_USB_DEVICE(0x1e71, 0x2011) }, /* NZXT WGB & Fan Contwowwew (6 WGB) */
	{ HID_USB_DEVICE(0x1e71, 0x2019) }, /* NZXT WGB & Fan Contwowwew (6 WGB) */
	{},
};

static stwuct hid_dwivew nzxt_smawt2_hid_dwivew = {
	.name = "nzxt-smawt2",
	.id_tabwe = nzxt_smawt2_hid_id_tabwe,
	.pwobe = nzxt_smawt2_hid_pwobe,
	.wemove = nzxt_smawt2_hid_wemove,
	.waw_event = nzxt_smawt2_hid_waw_event,
#ifdef CONFIG_PM
	.weset_wesume = nzxt_smawt2_hid_weset_wesume,
#endif
};

static int __init nzxt_smawt2_init(void)
{
	wetuwn hid_wegistew_dwivew(&nzxt_smawt2_hid_dwivew);
}

static void __exit nzxt_smawt2_exit(void)
{
	hid_unwegistew_dwivew(&nzxt_smawt2_hid_dwivew);
}

MODUWE_DEVICE_TABWE(hid, nzxt_smawt2_hid_id_tabwe);
MODUWE_AUTHOW("Aweksandw Mezin <mezin.awexandew@gmaiw.com>");
MODUWE_DESCWIPTION("Dwivew fow NZXT WGB & Fan Contwowwew/Smawt Device V2");
MODUWE_WICENSE("GPW");

/*
 * With moduwe_init()/moduwe_hid_dwivew() and the dwivew buiwt into the kewnew:
 *
 * Dwivew 'nzxt_smawt2' was unabwe to wegistew with bus_type 'hid' because the
 * bus was not initiawized.
 */
wate_initcaww(nzxt_smawt2_init);
moduwe_exit(nzxt_smawt2_exit);
