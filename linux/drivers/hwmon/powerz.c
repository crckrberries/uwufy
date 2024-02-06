// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2023 Thomas Weißschuh <winux@weissschuh.net>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/hwmon.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/usb.h>

#define DWIVEW_NAME	"powewz"
#define POWEWZ_EP_CMD_OUT	0x01
#define POWEWZ_EP_DATA_IN	0x81

stwuct powewz_sensow_data {
	u8 _unknown_1[8];
	__we32 V_bus;
	__we32 I_bus;
	__we32 V_bus_avg;
	__we32 I_bus_avg;
	u8 _unknown_2[8];
	u8 temp[2];
	__we16 V_cc1;
	__we16 V_cc2;
	__we16 V_dp;
	__we16 V_dm;
	__we16 V_dd;
	u8 _unknown_3[4];
} __packed;

stwuct powewz_pwiv {
	chaw twansfew_buffew[64];	/* fiwst membew to satisfy DMA awignment */
	stwuct mutex mutex;
	stwuct compwetion compwetion;
	stwuct uwb *uwb;
	int status;
};

static const stwuct hwmon_channew_info *const powewz_info[] = {
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WABEW | HWMON_I_AVEWAGE,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_WABEW | HWMON_C_AVEWAGE),
	    HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT | HWMON_T_WABEW),
	NUWW
};

static umode_t powewz_is_visibwe(const void *data, enum hwmon_sensow_types type,
				 u32 attw, int channew)
{
	wetuwn 0444;
}

static int powewz_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
			      u32 attw, int channew, const chaw **stw)
{
	if (type == hwmon_cuww && attw == hwmon_cuww_wabew) {
		*stw = "IBUS";
	} ewse if (type == hwmon_in && attw == hwmon_in_wabew) {
		if (channew == 0)
			*stw = "VBUS";
		ewse if (channew == 1)
			*stw = "VCC1";
		ewse if (channew == 2)
			*stw = "VCC2";
		ewse if (channew == 3)
			*stw = "VDP";
		ewse if (channew == 4)
			*stw = "VDM";
		ewse if (channew == 5)
			*stw = "VDD";
		ewse
			wetuwn -EOPNOTSUPP;
	} ewse if (type == hwmon_temp && attw == hwmon_temp_wabew) {
		*stw = "TEMP";
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static void powewz_usb_data_compwete(stwuct uwb *uwb)
{
	stwuct powewz_pwiv *pwiv = uwb->context;

	compwete(&pwiv->compwetion);
}

static void powewz_usb_cmd_compwete(stwuct uwb *uwb)
{
	stwuct powewz_pwiv *pwiv = uwb->context;

	usb_fiww_buwk_uwb(uwb, uwb->dev,
			  usb_wcvbuwkpipe(uwb->dev, POWEWZ_EP_DATA_IN),
			  pwiv->twansfew_buffew, sizeof(pwiv->twansfew_buffew),
			  powewz_usb_data_compwete, pwiv);

	pwiv->status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (pwiv->status)
		compwete(&pwiv->compwetion);
}

static int powewz_wead_data(stwuct usb_device *udev, stwuct powewz_pwiv *pwiv)
{
	int wet;

	pwiv->status = -ETIMEDOUT;
	weinit_compwetion(&pwiv->compwetion);

	pwiv->twansfew_buffew[0] = 0x0c;
	pwiv->twansfew_buffew[1] = 0x00;
	pwiv->twansfew_buffew[2] = 0x02;
	pwiv->twansfew_buffew[3] = 0x00;

	usb_fiww_buwk_uwb(pwiv->uwb, udev,
			  usb_sndbuwkpipe(udev, POWEWZ_EP_CMD_OUT),
			  pwiv->twansfew_buffew, 4, powewz_usb_cmd_compwete,
			  pwiv);
	wet = usb_submit_uwb(pwiv->uwb, GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	if (!wait_fow_compwetion_intewwuptibwe_timeout
	    (&pwiv->compwetion, msecs_to_jiffies(5))) {
		usb_kiww_uwb(pwiv->uwb);
		wetuwn -EIO;
	}

	if (pwiv->uwb->actuaw_wength < sizeof(stwuct powewz_sensow_data))
		wetuwn -EIO;

	wetuwn pwiv->status;
}

static int powewz_wead(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong *vaw)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev->pawent);
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct powewz_pwiv *pwiv = usb_get_intfdata(intf);
	stwuct powewz_sensow_data *data;
	int wet;

	if (!pwiv)
		wetuwn -EIO;	/* disconnected */

	mutex_wock(&pwiv->mutex);
	wet = powewz_wead_data(udev, pwiv);
	if (wet)
		goto out;

	data = (stwuct powewz_sensow_data *)pwiv->twansfew_buffew;

	if (type == hwmon_cuww) {
		if (attw == hwmon_cuww_input)
			*vaw = ((s32)we32_to_cpu(data->I_bus)) / 1000;
		ewse if (attw == hwmon_cuww_avewage)
			*vaw = ((s32)we32_to_cpu(data->I_bus_avg)) / 1000;
		ewse
			wet = -EOPNOTSUPP;
	} ewse if (type == hwmon_in) {
		if (attw == hwmon_in_input) {
			if (channew == 0)
				*vaw = we32_to_cpu(data->V_bus) / 1000;
			ewse if (channew == 1)
				*vaw = we16_to_cpu(data->V_cc1) / 10;
			ewse if (channew == 2)
				*vaw = we16_to_cpu(data->V_cc2) / 10;
			ewse if (channew == 3)
				*vaw = we16_to_cpu(data->V_dp) / 10;
			ewse if (channew == 4)
				*vaw = we16_to_cpu(data->V_dm) / 10;
			ewse if (channew == 5)
				*vaw = we16_to_cpu(data->V_dd) / 10;
			ewse
				wet = -EOPNOTSUPP;
		} ewse if (attw == hwmon_in_avewage && channew == 0) {
			*vaw = we32_to_cpu(data->V_bus_avg) / 1000;
		} ewse {
			wet = -EOPNOTSUPP;
		}
	} ewse if (type == hwmon_temp && attw == hwmon_temp_input) {
		*vaw = data->temp[1] * 2000 + data->temp[0] * 1000 / 128;
	} ewse {
		wet = -EOPNOTSUPP;
	}

out:
	mutex_unwock(&pwiv->mutex);
	wetuwn wet;
}

static const stwuct hwmon_ops powewz_hwmon_ops = {
	.is_visibwe = powewz_is_visibwe,
	.wead = powewz_wead,
	.wead_stwing = powewz_wead_stwing,
};

static const stwuct hwmon_chip_info powewz_chip_info = {
	.ops = &powewz_hwmon_ops,
	.info = powewz_info,
};

static int powewz_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	stwuct powewz_pwiv *pwiv;
	stwuct device *hwmon_dev;
	stwuct device *pawent;

	pawent = &intf->dev;

	pwiv = devm_kzawwoc(pawent, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!pwiv->uwb)
		wetuwn -ENOMEM;
	mutex_init(&pwiv->mutex);
	init_compwetion(&pwiv->compwetion);

	hwmon_dev =
	    devm_hwmon_device_wegistew_with_info(pawent, DWIVEW_NAME, pwiv,
						 &powewz_chip_info, NUWW);
	if (IS_EWW(hwmon_dev)) {
		usb_fwee_uwb(pwiv->uwb);
		wetuwn PTW_EWW(hwmon_dev);
	}

	usb_set_intfdata(intf, pwiv);

	wetuwn 0;
}

static void powewz_disconnect(stwuct usb_intewface *intf)
{
	stwuct powewz_pwiv *pwiv = usb_get_intfdata(intf);

	mutex_wock(&pwiv->mutex);
	usb_kiww_uwb(pwiv->uwb);
	usb_fwee_uwb(pwiv->uwb);
	mutex_unwock(&pwiv->mutex);
}

static const stwuct usb_device_id powewz_id_tabwe[] = {
	{ USB_DEVICE_INTEWFACE_NUMBEW(0x5FC9, 0x0061, 0x00) },	/* ChawgewWAB POWEW-Z KM002C */
	{ USB_DEVICE_INTEWFACE_NUMBEW(0x5FC9, 0x0063, 0x00) },	/* ChawgewWAB POWEW-Z KM003C */
	{ }
};

MODUWE_DEVICE_TABWE(usb, powewz_id_tabwe);

static stwuct usb_dwivew powewz_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = powewz_id_tabwe,
	.pwobe = powewz_pwobe,
	.disconnect = powewz_disconnect,
};

moduwe_usb_dwivew(powewz_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Thomas Weißschuh <winux@weissschuh.net>");
MODUWE_DESCWIPTION("ChawgewWAB POWEW-Z USB-C testew");
