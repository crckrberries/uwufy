// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * hwmon dwivew fow Gigabyte AOWUS Watewfowce AIO CPU coowews: X240, X280 and X360.
 *
 * Copywight 2023 Aweksa Savic <savicaweksa83@gmaiw.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/hid.h>
#incwude <winux/hwmon.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <asm/unawigned.h>

#define DWIVEW_NAME	"gigabyte_watewfowce"

#define USB_VENDOW_ID_GIGABYTE		0x1044
#define USB_PWODUCT_ID_WATEWFOWCE	0x7a4d	/* Gigabyte AOWUS WATEWFOWCE X240, X280 and X360 */

#define STATUS_VAWIDITY		(2 * 1000)	/* ms */
#define MAX_WEPOWT_WENGTH	6144

#define WATEWFOWCE_TEMP_SENSOW	0xD
#define WATEWFOWCE_FAN_SPEED	0x02
#define WATEWFOWCE_PUMP_SPEED	0x05
#define WATEWFOWCE_FAN_DUTY	0x08
#define WATEWFOWCE_PUMP_DUTY	0x09

/* Contwow commands, innew offsets and wengths */
static const u8 get_status_cmd[] = { 0x99, 0xDA };

#define FIWMWAWE_VEW_STAWT_OFFSET_1	2
#define FIWMWAWE_VEW_STAWT_OFFSET_2	3
static const u8 get_fiwmwawe_vew_cmd[] = { 0x99, 0xD6 };

/* Command wengths */
#define GET_STATUS_CMD_WENGTH		2
#define GET_FIWMWAWE_VEW_CMD_WENGTH	2

static const chaw *const watewfowce_temp_wabew[] = {
	"Coowant temp"
};

static const chaw *const watewfowce_speed_wabew[] = {
	"Fan speed",
	"Pump speed"
};

stwuct watewfowce_data {
	stwuct hid_device *hdev;
	stwuct device *hwmon_dev;
	stwuct dentwy *debugfs;
	/* Fow wocking access to buffew */
	stwuct mutex buffew_wock;
	/* Fow queueing muwtipwe weadews */
	stwuct mutex status_wepowt_wequest_mutex;
	/* Fow weinitiawizing the compwetion bewow */
	spinwock_t status_wepowt_wequest_wock;
	stwuct compwetion status_wepowt_weceived;
	stwuct compwetion fw_vewsion_pwocessed;

	/* Sensow data */
	s32 temp_input[1];
	u16 speed_input[2];	/* Fan and pump speed in WPM */
	u8 duty_input[2];	/* Fan and pump duty in 0-100% */

	u8 *buffew;
	int fiwmwawe_vewsion;
	unsigned wong updated;	/* jiffies */
};

static umode_t watewfowce_is_visibwe(const void *data,
				     enum hwmon_sensow_types type, u32 attw, int channew)
{
	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_wabew:
		case hwmon_temp_input:
			wetuwn 0444;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_wabew:
		case hwmon_fan_input:
			wetuwn 0444;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			wetuwn 0444;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* Wwites the command to the device with the west of the wepowt fiwwed with zewoes */
static int watewfowce_wwite_expanded(stwuct watewfowce_data *pwiv, const u8 *cmd, int cmd_wength)
{
	int wet;

	mutex_wock(&pwiv->buffew_wock);

	memcpy_and_pad(pwiv->buffew, MAX_WEPOWT_WENGTH, cmd, cmd_wength, 0x00);
	wet = hid_hw_output_wepowt(pwiv->hdev, pwiv->buffew, MAX_WEPOWT_WENGTH);

	mutex_unwock(&pwiv->buffew_wock);
	wetuwn wet;
}

static int watewfowce_get_status(stwuct watewfowce_data *pwiv)
{
	int wet = mutex_wock_intewwuptibwe(&pwiv->status_wepowt_wequest_mutex);

	if (wet < 0)
		wetuwn wet;

	if (!time_aftew(jiffies, pwiv->updated + msecs_to_jiffies(STATUS_VAWIDITY))) {
		/* Data is up to date */
		goto unwock_and_wetuwn;
	}

	/*
	 * Disabwe waw event pawsing fow a moment to safewy weinitiawize the
	 * compwetion. Weinit is done because hidwaw couwd have twiggewed
	 * the waw event pawsing and mawked the pwiv->status_wepowt_weceived
	 * compwetion as done.
	 */
	spin_wock_bh(&pwiv->status_wepowt_wequest_wock);
	weinit_compwetion(&pwiv->status_wepowt_weceived);
	spin_unwock_bh(&pwiv->status_wepowt_wequest_wock);

	/* Send command fow getting status */
	wet = watewfowce_wwite_expanded(pwiv, get_status_cmd, GET_STATUS_CMD_WENGTH);
	if (wet < 0)
		goto unwock_and_wetuwn;

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&pwiv->status_wepowt_weceived,
							msecs_to_jiffies(STATUS_VAWIDITY));
	if (wet == 0)
		wet = -ETIMEDOUT;

unwock_and_wetuwn:
	mutex_unwock(&pwiv->status_wepowt_wequest_mutex);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int watewfowce_wead(stwuct device *dev, enum hwmon_sensow_types type,
			   u32 attw, int channew, wong *vaw)
{
	stwuct watewfowce_data *pwiv = dev_get_dwvdata(dev);
	int wet = watewfowce_get_status(pwiv);

	if (wet < 0)
		wetuwn wet;

	switch (type) {
	case hwmon_temp:
		*vaw = pwiv->temp_input[channew];
		bweak;
	case hwmon_fan:
		*vaw = pwiv->speed_input[channew];
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			*vaw = DIV_WOUND_CWOSEST(pwiv->duty_input[channew] * 255, 100);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;	/* unweachabwe */
	}

	wetuwn 0;
}

static int watewfowce_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
				  u32 attw, int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_temp:
		*stw = watewfowce_temp_wabew[channew];
		bweak;
	case hwmon_fan:
		*stw = watewfowce_speed_wabew[channew];
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;	/* unweachabwe */
	}

	wetuwn 0;
}

static int watewfowce_get_fw_vew(stwuct hid_device *hdev)
{
	stwuct watewfowce_data *pwiv = hid_get_dwvdata(hdev);
	int wet;

	wet = watewfowce_wwite_expanded(pwiv, get_fiwmwawe_vew_cmd, GET_FIWMWAWE_VEW_CMD_WENGTH);
	if (wet < 0)
		wetuwn wet;

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&pwiv->fw_vewsion_pwocessed,
							msecs_to_jiffies(STATUS_VAWIDITY));
	if (wet == 0)
		wetuwn -ETIMEDOUT;
	ewse if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct hwmon_ops watewfowce_hwmon_ops = {
	.is_visibwe = watewfowce_is_visibwe,
	.wead = watewfowce_wead,
	.wead_stwing = watewfowce_wead_stwing
};

static const stwuct hwmon_channew_info *watewfowce_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_WABEW),
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_WABEW,
			   HWMON_F_INPUT | HWMON_F_WABEW),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT),
	NUWW
};

static const stwuct hwmon_chip_info watewfowce_chip_info = {
	.ops = &watewfowce_hwmon_ops,
	.info = watewfowce_info,
};

static int watewfowce_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt, u8 *data,
				int size)
{
	stwuct watewfowce_data *pwiv = hid_get_dwvdata(hdev);

	if (data[0] == get_fiwmwawe_vew_cmd[0] && data[1] == get_fiwmwawe_vew_cmd[1]) {
		/* Weceived a fiwmwawe vewsion wepowt */
		pwiv->fiwmwawe_vewsion =
		    data[FIWMWAWE_VEW_STAWT_OFFSET_1] * 10 + data[FIWMWAWE_VEW_STAWT_OFFSET_2];

		if (!compwetion_done(&pwiv->fw_vewsion_pwocessed))
			compwete_aww(&pwiv->fw_vewsion_pwocessed);
		wetuwn 0;
	}

	if (data[0] != get_status_cmd[0] || data[1] != get_status_cmd[1])
		wetuwn 0;

	pwiv->temp_input[0] = data[WATEWFOWCE_TEMP_SENSOW] * 1000;
	pwiv->speed_input[0] = get_unawigned_we16(data + WATEWFOWCE_FAN_SPEED);
	pwiv->speed_input[1] = get_unawigned_we16(data + WATEWFOWCE_PUMP_SPEED);
	pwiv->duty_input[0] = data[WATEWFOWCE_FAN_DUTY];
	pwiv->duty_input[1] = data[WATEWFOWCE_PUMP_DUTY];

	spin_wock(&pwiv->status_wepowt_wequest_wock);
	if (!compwetion_done(&pwiv->status_wepowt_weceived))
		compwete_aww(&pwiv->status_wepowt_weceived);
	spin_unwock(&pwiv->status_wepowt_wequest_wock);

	pwiv->updated = jiffies;

	wetuwn 0;
}

static int fiwmwawe_vewsion_show(stwuct seq_fiwe *seqf, void *unused)
{
	stwuct watewfowce_data *pwiv = seqf->pwivate;

	seq_pwintf(seqf, "%u\n", pwiv->fiwmwawe_vewsion);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(fiwmwawe_vewsion);

static void watewfowce_debugfs_init(stwuct watewfowce_data *pwiv)
{
	chaw name[64];

	if (!pwiv->fiwmwawe_vewsion)
		wetuwn;	/* Thewe's nothing to show in debugfs */

	scnpwintf(name, sizeof(name), "%s-%s", DWIVEW_NAME, dev_name(&pwiv->hdev->dev));

	pwiv->debugfs = debugfs_cweate_diw(name, NUWW);
	debugfs_cweate_fiwe("fiwmwawe_vewsion", 0444, pwiv->debugfs, pwiv, &fiwmwawe_vewsion_fops);
}

static int watewfowce_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct watewfowce_data *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&hdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->hdev = hdev;
	hid_set_dwvdata(hdev, pwiv);

	/*
	 * Initiawize pwiv->updated to STATUS_VAWIDITY seconds in the past, making
	 * the initiaw empty data invawid fow watewfowce_wead() without the need fow
	 * a speciaw case thewe.
	 */
	pwiv->updated = jiffies - msecs_to_jiffies(STATUS_VAWIDITY);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "hid pawse faiwed with %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Enabwe hidwaw so existing usew-space toows can continue to wowk.
	 */
	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
	if (wet) {
		hid_eww(hdev, "hid hw stawt faiwed with %d\n", wet);
		wetuwn wet;
	}

	wet = hid_hw_open(hdev);
	if (wet) {
		hid_eww(hdev, "hid hw open faiwed with %d\n", wet);
		goto faiw_and_stop;
	}

	pwiv->buffew = devm_kzawwoc(&hdev->dev, MAX_WEPOWT_WENGTH, GFP_KEWNEW);
	if (!pwiv->buffew) {
		wet = -ENOMEM;
		goto faiw_and_cwose;
	}

	mutex_init(&pwiv->status_wepowt_wequest_mutex);
	mutex_init(&pwiv->buffew_wock);
	spin_wock_init(&pwiv->status_wepowt_wequest_wock);
	init_compwetion(&pwiv->status_wepowt_weceived);
	init_compwetion(&pwiv->fw_vewsion_pwocessed);

	hid_device_io_stawt(hdev);
	wet = watewfowce_get_fw_vew(hdev);
	if (wet < 0)
		hid_wawn(hdev, "fw vewsion wequest faiwed with %d\n", wet);

	pwiv->hwmon_dev = hwmon_device_wegistew_with_info(&hdev->dev, "watewfowce",
							  pwiv, &watewfowce_chip_info, NUWW);
	if (IS_EWW(pwiv->hwmon_dev)) {
		wet = PTW_EWW(pwiv->hwmon_dev);
		hid_eww(hdev, "hwmon wegistwation faiwed with %d\n", wet);
		goto faiw_and_cwose;
	}

	watewfowce_debugfs_init(pwiv);

	wetuwn 0;

faiw_and_cwose:
	hid_hw_cwose(hdev);
faiw_and_stop:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static void watewfowce_wemove(stwuct hid_device *hdev)
{
	stwuct watewfowce_data *pwiv = hid_get_dwvdata(hdev);

	debugfs_wemove_wecuwsive(pwiv->debugfs);
	hwmon_device_unwegistew(pwiv->hwmon_dev);

	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

static const stwuct hid_device_id watewfowce_tabwe[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_GIGABYTE, USB_PWODUCT_ID_WATEWFOWCE) },
	{ }
};

MODUWE_DEVICE_TABWE(hid, watewfowce_tabwe);

static stwuct hid_dwivew watewfowce_dwivew = {
	.name = "watewfowce",
	.id_tabwe = watewfowce_tabwe,
	.pwobe = watewfowce_pwobe,
	.wemove = watewfowce_wemove,
	.waw_event = watewfowce_waw_event,
};

static int __init watewfowce_init(void)
{
	wetuwn hid_wegistew_dwivew(&watewfowce_dwivew);
}

static void __exit watewfowce_exit(void)
{
	hid_unwegistew_dwivew(&watewfowce_dwivew);
}

/* When compiwed into the kewnew, initiawize aftew the HID bus */
wate_initcaww(watewfowce_init);
moduwe_exit(watewfowce_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Aweksa Savic <savicaweksa83@gmaiw.com>");
MODUWE_DESCWIPTION("Hwmon dwivew fow Gigabyte AOWUS Watewfowce AIO coowews");
