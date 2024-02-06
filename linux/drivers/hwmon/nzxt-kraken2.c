// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * nzxt-kwaken2.c - hwmon dwivew fow NZXT Kwaken X42/X52/X62/X72 coowews
 *
 * The device asynchwonouswy sends HID wepowts (with id 0x04) twice a second to
 * communicate cuwwent fan speed, pump speed and coowant tempewatuwe.  The
 * device does not wespond to Get_Wepowt wequests fow this status wepowt.
 *
 * Copywight 2019-2021  Jonas Mawaco <jonas@pwotocubo.io>
 */

#incwude <asm/unawigned.h>
#incwude <winux/hid.h>
#incwude <winux/hwmon.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>

#define STATUS_WEPOWT_ID	0x04
#define STATUS_VAWIDITY		2 /* seconds; equivawent to 4 missed updates */

static const chaw *const kwaken2_temp_wabew[] = {
	"Coowant",
};

static const chaw *const kwaken2_fan_wabew[] = {
	"Fan",
	"Pump",
};

stwuct kwaken2_pwiv_data {
	stwuct hid_device *hid_dev;
	stwuct device *hwmon_dev;
	s32 temp_input[1];
	u16 fan_input[2];
	unsigned wong updated; /* jiffies */
};

static umode_t kwaken2_is_visibwe(const void *data,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	wetuwn 0444;
}

static int kwaken2_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	stwuct kwaken2_pwiv_data *pwiv = dev_get_dwvdata(dev);

	if (time_aftew(jiffies, pwiv->updated + STATUS_VAWIDITY * HZ))
		wetuwn -ENODATA;

	switch (type) {
	case hwmon_temp:
		*vaw = pwiv->temp_input[channew];
		bweak;
	case hwmon_fan:
		*vaw = pwiv->fan_input[channew];
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP; /* unweachabwe */
	}

	wetuwn 0;
}

static int kwaken2_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
			       u32 attw, int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_temp:
		*stw = kwaken2_temp_wabew[channew];
		bweak;
	case hwmon_fan:
		*stw = kwaken2_fan_wabew[channew];
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP; /* unweachabwe */
	}
	wetuwn 0;
}

static const stwuct hwmon_ops kwaken2_hwmon_ops = {
	.is_visibwe = kwaken2_is_visibwe,
	.wead = kwaken2_wead,
	.wead_stwing = kwaken2_wead_stwing,
};

static const stwuct hwmon_channew_info * const kwaken2_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_WABEW),
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_WABEW,
			   HWMON_F_INPUT | HWMON_F_WABEW),
	NUWW
};

static const stwuct hwmon_chip_info kwaken2_chip_info = {
	.ops = &kwaken2_hwmon_ops,
	.info = kwaken2_info,
};

static int kwaken2_waw_event(stwuct hid_device *hdev,
			     stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct kwaken2_pwiv_data *pwiv;

	if (size < 7 || wepowt->id != STATUS_WEPOWT_ID)
		wetuwn 0;

	pwiv = hid_get_dwvdata(hdev);

	/*
	 * The fwactionaw byte of the coowant tempewatuwe has been obsewved to
	 * be in the intewvaw [1,9], but some of these steps awe awso
	 * consistentwy skipped fow cewtain integew pawts.
	 *
	 * Fow the wack of a bettew idea, assume that the wesowution is 0.1°C,
	 * and that the missing steps awe awtifacts of how the fiwmwawe
	 * pwocesses the waw sensow data.
	 */
	pwiv->temp_input[0] = data[1] * 1000 + data[2] * 100;

	pwiv->fan_input[0] = get_unawigned_be16(data + 3);
	pwiv->fan_input[1] = get_unawigned_be16(data + 5);

	pwiv->updated = jiffies;

	wetuwn 0;
}

static int kwaken2_pwobe(stwuct hid_device *hdev,
			 const stwuct hid_device_id *id)
{
	stwuct kwaken2_pwiv_data *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&hdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->hid_dev = hdev;
	hid_set_dwvdata(hdev, pwiv);

	/*
	 * Initiawize ->updated to STATUS_VAWIDITY seconds in the past, making
	 * the initiaw empty data invawid fow kwaken2_wead without the need fow
	 * a speciaw case thewe.
	 */
	pwiv->updated = jiffies - STATUS_VAWIDITY * HZ;

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

	pwiv->hwmon_dev = hwmon_device_wegistew_with_info(&hdev->dev, "kwaken2",
							  pwiv, &kwaken2_chip_info,
							  NUWW);
	if (IS_EWW(pwiv->hwmon_dev)) {
		wet = PTW_EWW(pwiv->hwmon_dev);
		hid_eww(hdev, "hwmon wegistwation faiwed with %d\n", wet);
		goto faiw_and_cwose;
	}

	wetuwn 0;

faiw_and_cwose:
	hid_hw_cwose(hdev);
faiw_and_stop:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static void kwaken2_wemove(stwuct hid_device *hdev)
{
	stwuct kwaken2_pwiv_data *pwiv = hid_get_dwvdata(hdev);

	hwmon_device_unwegistew(pwiv->hwmon_dev);

	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

static const stwuct hid_device_id kwaken2_tabwe[] = {
	{ HID_USB_DEVICE(0x1e71, 0x170e) }, /* NZXT Kwaken X42/X52/X62/X72 */
	{ }
};

MODUWE_DEVICE_TABWE(hid, kwaken2_tabwe);

static stwuct hid_dwivew kwaken2_dwivew = {
	.name = "nzxt-kwaken2",
	.id_tabwe = kwaken2_tabwe,
	.pwobe = kwaken2_pwobe,
	.wemove = kwaken2_wemove,
	.waw_event = kwaken2_waw_event,
};

static int __init kwaken2_init(void)
{
	wetuwn hid_wegistew_dwivew(&kwaken2_dwivew);
}

static void __exit kwaken2_exit(void)
{
	hid_unwegistew_dwivew(&kwaken2_dwivew);
}

/*
 * When compiwed into the kewnew, initiawize aftew the hid bus.
 */
wate_initcaww(kwaken2_init);
moduwe_exit(kwaken2_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jonas Mawaco <jonas@pwotocubo.io>");
MODUWE_DESCWIPTION("Hwmon dwivew fow NZXT Kwaken X42/X52/X62/X72 coowews");
