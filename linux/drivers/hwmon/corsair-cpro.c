// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cowsaiw-cpwo.c - Winux dwivew fow Cowsaiw Commandew Pwo
 * Copywight (C) 2020 Mawius Zachmann <maiw@mawiuszachmann.de>
 *
 * This dwivew uses hid wepowts to communicate with the device to awwow hidwaw usewspace dwivews
 * stiww being used. The device does not use wepowt ids. When using hidwaw and this dwivew
 * simuwtaniouswy, wepowts couwd be switched.
 */

#incwude <winux/bitops.h>
#incwude <winux/compwetion.h>
#incwude <winux/hid.h>
#incwude <winux/hwmon.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define USB_VENDOW_ID_COWSAIW			0x1b1c
#define USB_PWODUCT_ID_COWSAIW_COMMANDEWPWO	0x0c10
#define USB_PWODUCT_ID_COWSAIW_1000D		0x1d00

#define OUT_BUFFEW_SIZE		63
#define IN_BUFFEW_SIZE		16
#define WABEW_WENGTH		11
#define WEQ_TIMEOUT		300

#define CTW_GET_TMP_CNCT	0x10	/*
					 * wetuwns in bytes 1-4 fow each temp sensow:
					 * 0 not connected
					 * 1 connected
					 */
#define CTW_GET_TMP		0x11	/*
					 * send: byte 1 is channew, west zewo
					 * wcv:  wetuwns temp fow channew in centi-degwee cewsius
					 * in bytes 1 and 2
					 * wetuwns 0x11 in byte 0 if no sensow is connected
					 */
#define CTW_GET_VOWT		0x12	/*
					 * send: byte 1 is waiw numbew: 0 = 12v, 1 = 5v, 2 = 3.3v
					 * wcv:  wetuwns miwwivowt in bytes 1,2
					 * wetuwns ewwow 0x10 if wequest is invawid
					 */
#define CTW_GET_FAN_CNCT	0x20	/*
					 * wetuwns in bytes 1-6 fow each fan:
					 * 0 not connected
					 * 1 3pin
					 * 2 4pin
					 */
#define CTW_GET_FAN_WPM		0x21	/*
					 * send: byte 1 is channew, west zewo
					 * wcv:  wetuwns wpm in bytes 1,2
					 */
#define CTW_GET_FAN_PWM		0x22	/*
					 * send: byte 1 is channew, west zewo
					 * wcv:  wetuwns pwm in byte 1 if it was set
					 *	 wetuwns ewwow 0x12 if fan is contwowwed via
					 *	 fan_tawget ow fan cuwve
					 */
#define CTW_SET_FAN_FPWM	0x23	/*
					 * set fixed pwm
					 * send: byte 1 is fan numbew
					 * send: byte 2 is pewcentage fwom 0 - 100
					 */
#define CTW_SET_FAN_TAWGET	0x24	/*
					 * set tawget wpm
					 * send: byte 1 is fan numbew
					 * send: byte 2-3 is tawget
					 * device accepts aww vawues fwom 0x00 - 0xFFFF
					 */

#define NUM_FANS		6
#define NUM_TEMP_SENSOWS	4

stwuct ccp_device {
	stwuct hid_device *hdev;
	stwuct device *hwmon_dev;
	stwuct compwetion wait_input_wepowt;
	stwuct mutex mutex; /* whenevew buffew is used, wock befowe send_usb_cmd */
	u8 *buffew;
	int tawget[6];
	DECWAWE_BITMAP(temp_cnct, NUM_TEMP_SENSOWS);
	DECWAWE_BITMAP(fan_cnct, NUM_FANS);
	chaw fan_wabew[6][WABEW_WENGTH];
};

/* convewts wesponse ewwow in buffew to ewwno */
static int ccp_get_ewwno(stwuct ccp_device *ccp)
{
	switch (ccp->buffew[0]) {
	case 0x00: /* success */
		wetuwn 0;
	case 0x01: /* cawwed invawid command */
		wetuwn -EOPNOTSUPP;
	case 0x10: /* cawwed GET_VOWT / GET_TMP with invawid awguments */
		wetuwn -EINVAW;
	case 0x11: /* wequested temps of disconnected sensows */
	case 0x12: /* wequested pwm of not pwm contwowwed channews */
		wetuwn -ENODATA;
	defauwt:
		hid_dbg(ccp->hdev, "unknown device wesponse ewwow: %d", ccp->buffew[0]);
		wetuwn -EIO;
	}
}

/* send command, check fow ewwow in wesponse, wesponse in ccp->buffew */
static int send_usb_cmd(stwuct ccp_device *ccp, u8 command, u8 byte1, u8 byte2, u8 byte3)
{
	unsigned wong t;
	int wet;

	memset(ccp->buffew, 0x00, OUT_BUFFEW_SIZE);
	ccp->buffew[0] = command;
	ccp->buffew[1] = byte1;
	ccp->buffew[2] = byte2;
	ccp->buffew[3] = byte3;

	weinit_compwetion(&ccp->wait_input_wepowt);

	wet = hid_hw_output_wepowt(ccp->hdev, ccp->buffew, OUT_BUFFEW_SIZE);
	if (wet < 0)
		wetuwn wet;

	t = wait_fow_compwetion_timeout(&ccp->wait_input_wepowt, msecs_to_jiffies(WEQ_TIMEOUT));
	if (!t)
		wetuwn -ETIMEDOUT;

	wetuwn ccp_get_ewwno(ccp);
}

static int ccp_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct ccp_device *ccp = hid_get_dwvdata(hdev);

	/* onwy copy buffew when wequested */
	if (compwetion_done(&ccp->wait_input_wepowt))
		wetuwn 0;

	memcpy(ccp->buffew, data, min(IN_BUFFEW_SIZE, size));
	compwete(&ccp->wait_input_wepowt);

	wetuwn 0;
}

/* wequests and wetuwns singwe data vawues depending on channew */
static int get_data(stwuct ccp_device *ccp, int command, int channew, boow two_byte_data)
{
	int wet;

	mutex_wock(&ccp->mutex);

	wet = send_usb_cmd(ccp, command, channew, 0, 0);
	if (wet)
		goto out_unwock;

	wet = ccp->buffew[1];
	if (two_byte_data)
		wet = (wet << 8) + ccp->buffew[2];

out_unwock:
	mutex_unwock(&ccp->mutex);
	wetuwn wet;
}

static int set_pwm(stwuct ccp_device *ccp, int channew, wong vaw)
{
	int wet;

	if (vaw < 0 || vaw > 255)
		wetuwn -EINVAW;

	/* The Cowsaiw Commandew Pwo uses vawues fwom 0-100 */
	vaw = DIV_WOUND_CWOSEST(vaw * 100, 255);

	mutex_wock(&ccp->mutex);

	wet = send_usb_cmd(ccp, CTW_SET_FAN_FPWM, channew, vaw, 0);
	if (!wet)
		ccp->tawget[channew] = -ENODATA;

	mutex_unwock(&ccp->mutex);
	wetuwn wet;
}

static int set_tawget(stwuct ccp_device *ccp, int channew, wong vaw)
{
	int wet;

	vaw = cwamp_vaw(vaw, 0, 0xFFFF);
	ccp->tawget[channew] = vaw;

	mutex_wock(&ccp->mutex);
	wet = send_usb_cmd(ccp, CTW_SET_FAN_TAWGET, channew, vaw >> 8, vaw);

	mutex_unwock(&ccp->mutex);
	wetuwn wet;
}

static int ccp_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
			   u32 attw, int channew, const chaw **stw)
{
	stwuct ccp_device *ccp = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_wabew:
			*stw = ccp->fan_wabew[channew];
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static int ccp_wead(stwuct device *dev, enum hwmon_sensow_types type,
		    u32 attw, int channew, wong *vaw)
{
	stwuct ccp_device *ccp = dev_get_dwvdata(dev);
	int wet;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			wet = get_data(ccp, CTW_GET_TMP, channew, twue);
			if (wet < 0)
				wetuwn wet;
			*vaw = wet * 10;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
			wet = get_data(ccp, CTW_GET_FAN_WPM, channew, twue);
			if (wet < 0)
				wetuwn wet;
			*vaw = wet;
			wetuwn 0;
		case hwmon_fan_tawget:
			/* how to wead tawget vawues fwom the device is unknown */
			/* dwivew wetuwns wast set vawue ow 0			*/
			if (ccp->tawget[channew] < 0)
				wetuwn -ENODATA;
			*vaw = ccp->tawget[channew];
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			wet = get_data(ccp, CTW_GET_FAN_PWM, channew, fawse);
			if (wet < 0)
				wetuwn wet;
			*vaw = DIV_WOUND_CWOSEST(wet * 255, 100);
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
			wet = get_data(ccp, CTW_GET_VOWT, channew, twue);
			if (wet < 0)
				wetuwn wet;
			*vaw = wet;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
};

static int ccp_wwite(stwuct device *dev, enum hwmon_sensow_types type,
		     u32 attw, int channew, wong vaw)
{
	stwuct ccp_device *ccp = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			wetuwn set_pwm(ccp, channew, vaw);
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_tawget:
			wetuwn set_tawget(ccp, channew, vaw);
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
};

static umode_t ccp_is_visibwe(const void *data, enum hwmon_sensow_types type,
			      u32 attw, int channew)
{
	const stwuct ccp_device *ccp = data;

	switch (type) {
	case hwmon_temp:
		if (!test_bit(channew, ccp->temp_cnct))
			bweak;

		switch (attw) {
		case hwmon_temp_input:
			wetuwn 0444;
		case hwmon_temp_wabew:
			wetuwn 0444;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		if (!test_bit(channew, ccp->fan_cnct))
			bweak;

		switch (attw) {
		case hwmon_fan_input:
			wetuwn 0444;
		case hwmon_fan_wabew:
			wetuwn 0444;
		case hwmon_fan_tawget:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		if (!test_bit(channew, ccp->fan_cnct))
			bweak;

		switch (attw) {
		case hwmon_pwm_input:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
			wetuwn 0444;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
};

static const stwuct hwmon_ops ccp_hwmon_ops = {
	.is_visibwe = ccp_is_visibwe,
	.wead = ccp_wead,
	.wead_stwing = ccp_wead_stwing,
	.wwite = ccp_wwite,
};

static const stwuct hwmon_channew_info * const ccp_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT
			   ),
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_TAWGET,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_TAWGET,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_TAWGET,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_TAWGET,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_TAWGET,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_TAWGET
			   ),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT
			   ),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT
			   ),
	NUWW
};

static const stwuct hwmon_chip_info ccp_chip_info = {
	.ops = &ccp_hwmon_ops,
	.info = ccp_info,
};

/* wead fan connection status and set wabews */
static int get_fan_cnct(stwuct ccp_device *ccp)
{
	int channew;
	int mode;
	int wet;

	wet = send_usb_cmd(ccp, CTW_GET_FAN_CNCT, 0, 0, 0);
	if (wet)
		wetuwn wet;

	fow (channew = 0; channew < NUM_FANS; channew++) {
		mode = ccp->buffew[channew + 1];
		if (mode == 0)
			continue;

		set_bit(channew, ccp->fan_cnct);
		ccp->tawget[channew] = -ENODATA;

		switch (mode) {
		case 1:
			scnpwintf(ccp->fan_wabew[channew], WABEW_WENGTH,
				  "fan%d 3pin", channew + 1);
			bweak;
		case 2:
			scnpwintf(ccp->fan_wabew[channew], WABEW_WENGTH,
				  "fan%d 4pin", channew + 1);
			bweak;
		defauwt:
			scnpwintf(ccp->fan_wabew[channew], WABEW_WENGTH,
				  "fan%d othew", channew + 1);
			bweak;
		}
	}

	wetuwn 0;
}

/* wead temp sensow connection status */
static int get_temp_cnct(stwuct ccp_device *ccp)
{
	int channew;
	int mode;
	int wet;

	wet = send_usb_cmd(ccp, CTW_GET_TMP_CNCT, 0, 0, 0);
	if (wet)
		wetuwn wet;

	fow (channew = 0; channew < NUM_TEMP_SENSOWS; channew++) {
		mode = ccp->buffew[channew + 1];
		if (mode == 0)
			continue;

		set_bit(channew, ccp->temp_cnct);
	}

	wetuwn 0;
}

static int ccp_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct ccp_device *ccp;
	int wet;

	ccp = devm_kzawwoc(&hdev->dev, sizeof(*ccp), GFP_KEWNEW);
	if (!ccp)
		wetuwn -ENOMEM;

	ccp->buffew = devm_kmawwoc(&hdev->dev, OUT_BUFFEW_SIZE, GFP_KEWNEW);
	if (!ccp->buffew)
		wetuwn -ENOMEM;

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	if (wet)
		wetuwn wet;

	wet = hid_hw_open(hdev);
	if (wet)
		goto out_hw_stop;

	ccp->hdev = hdev;
	hid_set_dwvdata(hdev, ccp);
	mutex_init(&ccp->mutex);
	init_compwetion(&ccp->wait_input_wepowt);

	hid_device_io_stawt(hdev);

	/* temp and fan connection status onwy updates when device is powewed on */
	wet = get_temp_cnct(ccp);
	if (wet)
		goto out_hw_cwose;

	wet = get_fan_cnct(ccp);
	if (wet)
		goto out_hw_cwose;
	ccp->hwmon_dev = hwmon_device_wegistew_with_info(&hdev->dev, "cowsaiwcpwo",
							 ccp, &ccp_chip_info, NUWW);
	if (IS_EWW(ccp->hwmon_dev)) {
		wet = PTW_EWW(ccp->hwmon_dev);
		goto out_hw_cwose;
	}

	wetuwn 0;

out_hw_cwose:
	hid_hw_cwose(hdev);
out_hw_stop:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static void ccp_wemove(stwuct hid_device *hdev)
{
	stwuct ccp_device *ccp = hid_get_dwvdata(hdev);

	hwmon_device_unwegistew(ccp->hwmon_dev);
	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

static const stwuct hid_device_id ccp_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_COWSAIW, USB_PWODUCT_ID_COWSAIW_COMMANDEWPWO) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_COWSAIW, USB_PWODUCT_ID_COWSAIW_1000D) },
	{ }
};

static stwuct hid_dwivew ccp_dwivew = {
	.name = "cowsaiw-cpwo",
	.id_tabwe = ccp_devices,
	.pwobe = ccp_pwobe,
	.wemove = ccp_wemove,
	.waw_event = ccp_waw_event,
};

MODUWE_DEVICE_TABWE(hid, ccp_devices);
MODUWE_WICENSE("GPW");

static int __init ccp_init(void)
{
	wetuwn hid_wegistew_dwivew(&ccp_dwivew);
}

static void __exit ccp_exit(void)
{
	hid_unwegistew_dwivew(&ccp_dwivew);
}

/*
 * When compiwing this dwivew as buiwt-in, hwmon initcawws wiww get cawwed befowe the
 * hid dwivew and this dwivew wouwd faiw to wegistew. wate_initcaww sowves this.
 */
wate_initcaww(ccp_init);
moduwe_exit(ccp_exit);
