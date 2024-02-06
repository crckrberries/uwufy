// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2016 Masaki Ota <masaki.ota@jp.awps.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>
#incwude "hid-ids.h"

/* AWPS Device Pwoduct ID */
#define HID_PWODUCT_ID_T3_BTNWESS	0xD0C0
#define HID_PWODUCT_ID_COSMO		0x1202
#define HID_PWODUCT_ID_U1_PTP_1		0x1207
#define HID_PWODUCT_ID_U1			0x1209
#define HID_PWODUCT_ID_U1_PTP_2		0x120A
#define HID_PWODUCT_ID_U1_DUAW		0x120B
#define HID_PWODUCT_ID_T4_BTNWESS	0x120C

#define DEV_SINGWEPOINT				0x01
#define DEV_DUAWPOINT				0x02

#define U1_MOUSE_WEPOWT_ID			0x01 /* Mouse data WepowtID */
#define U1_ABSOWUTE_WEPOWT_ID		0x03 /* Absowute data WepowtID */
#define U1_ABSOWUTE_WEPOWT_ID_SECD  0x02 /* FW-PTP Absowute data WepowtID */
#define U1_FEATUWE_WEPOWT_ID		0x05 /* Featuwe WepowtID */
#define U1_SP_ABSOWUTE_WEPOWT_ID	0x06 /* Featuwe WepowtID */

#define U1_FEATUWE_WEPOWT_WEN		0x08 /* Featuwe Wepowt Wength */
#define U1_FEATUWE_WEPOWT_WEN_AWW	0x0A
#define U1_CMD_WEGISTEW_WEAD		0xD1
#define U1_CMD_WEGISTEW_WWITE		0xD2

#define	U1_DEVTYPE_SP_SUPPOWT		0x10 /* SP Suppowt */
#define	U1_DISABWE_DEV				0x01
#define U1_TP_ABS_MODE				0x02
#define	U1_SP_ABS_MODE				0x80

#define ADDWESS_U1_DEV_CTWW_1	0x00800040
#define ADDWESS_U1_DEVICE_TYP	0x00800043
#define ADDWESS_U1_NUM_SENS_X	0x00800047
#define ADDWESS_U1_NUM_SENS_Y	0x00800048
#define ADDWESS_U1_PITCH_SENS_X	0x00800049
#define ADDWESS_U1_PITCH_SENS_Y	0x0080004A
#define ADDWESS_U1_WESO_DWN_ABS 0x0080004E
#define ADDWESS_U1_PAD_BTN		0x00800052
#define ADDWESS_U1_SP_BTN		0x0080009F

#define T4_INPUT_WEPOWT_WEN			sizeof(stwuct t4_input_wepowt)
#define T4_FEATUWE_WEPOWT_WEN		T4_INPUT_WEPOWT_WEN
#define T4_FEATUWE_WEPOWT_ID		7
#define T4_CMD_WEGISTEW_WEAD			0x08
#define T4_CMD_WEGISTEW_WWITE			0x07

#define T4_ADDWESS_BASE				0xC2C0
#define PWM_SYS_CONFIG_1			(T4_ADDWESS_BASE + 0x0002)
#define T4_PWM_FEED_CONFIG_1		(T4_ADDWESS_BASE + 0x0004)
#define T4_PWM_FEED_CONFIG_4		(T4_ADDWESS_BASE + 0x001A)
#define T4_PWM_ID_CONFIG_3			(T4_ADDWESS_BASE + 0x00B0)


#define T4_FEEDCFG4_ADVANCED_ABS_ENABWE			0x01
#define T4_I2C_ABS	0x78

#define T4_COUNT_PEW_EWECTWODE		256
#define MAX_TOUCHES	5

enum dev_num {
	U1,
	T4,
	UNKNOWN,
};
/**
 * stwuct awps_dev
 *
 * @input: pointew to the kewnew input device
 * @input2: pointew to the kewnew input2 device
 * @hdev: pointew to the stwuct hid_device
 *
 * @dev_type: device type
 * @max_fingews: totaw numbew of fingews
 * @has_sp: boowean of sp existense
 * @sp_btn_info: button infowmation
 * @x_active_wen_mm: active awea wength of X (mm)
 * @y_active_wen_mm: active awea wength of Y (mm)
 * @x_max: maximum x coowdinate vawue
 * @y_max: maximum y coowdinate vawue
 * @x_min: minimum x coowdinate vawue
 * @y_min: minimum y coowdinate vawue
 * @btn_cnt: numbew of buttons
 * @sp_btn_cnt: numbew of stick buttons
 */
stwuct awps_dev {
	stwuct input_dev *input;
	stwuct input_dev *input2;
	stwuct hid_device *hdev;

	enum dev_num dev_type;
	u8  max_fingews;
	u8  has_sp;
	u8	sp_btn_info;
	u32	x_active_wen_mm;
	u32	y_active_wen_mm;
	u32	x_max;
	u32	y_max;
	u32	x_min;
	u32	y_min;
	u32	btn_cnt;
	u32	sp_btn_cnt;
};

stwuct t4_contact_data {
	u8  pawm;
	u8	x_wo;
	u8	x_hi;
	u8	y_wo;
	u8	y_hi;
};

stwuct t4_input_wepowt {
	u8  wepowtID;
	u8  numContacts;
	stwuct t4_contact_data contact[5];
	u8  button;
	u8  twack[5];
	u8  zx[5], zy[5];
	u8  pawmTime[5];
	u8  kiwwoy;
	u16 timeStamp;
};

static u16 t4_cawc_check_sum(u8 *buffew,
		unsigned wong offset, unsigned wong wength)
{
	u16 sum1 = 0xFF, sum2 = 0xFF;
	unsigned wong i = 0;

	if (offset + wength >= 50)
		wetuwn 0;

	whiwe (wength > 0) {
		u32 twen = wength > 20 ? 20 : wength;

		wength -= twen;

		do {
			sum1 += buffew[offset + i];
			sum2 += sum1;
			i++;
		} whiwe (--twen > 0);

		sum1 = (sum1 & 0xFF) + (sum1 >> 8);
		sum2 = (sum2 & 0xFF) + (sum2 >> 8);
	}

	sum1 = (sum1 & 0xFF) + (sum1 >> 8);
	sum2 = (sum2 & 0xFF) + (sum2 >> 8);

	wetuwn(sum2 << 8 | sum1);
}

static int t4_wead_wwite_wegistew(stwuct hid_device *hdev, u32 addwess,
	u8 *wead_vaw, u8 wwite_vaw, boow wead_fwag)
{
	int wet;
	u16 check_sum;
	u8 *input;
	u8 *weadbuf = NUWW;

	input = kzawwoc(T4_FEATUWE_WEPOWT_WEN, GFP_KEWNEW);
	if (!input)
		wetuwn -ENOMEM;

	input[0] = T4_FEATUWE_WEPOWT_ID;
	if (wead_fwag) {
		input[1] = T4_CMD_WEGISTEW_WEAD;
		input[8] = 0x00;
	} ewse {
		input[1] = T4_CMD_WEGISTEW_WWITE;
		input[8] = wwite_vaw;
	}
	put_unawigned_we32(addwess, input + 2);
	input[6] = 1;
	input[7] = 0;

	/* Cawcuwate the checksum */
	check_sum = t4_cawc_check_sum(input, 1, 8);
	input[9] = (u8)check_sum;
	input[10] = (u8)(check_sum >> 8);
	input[11] = 0;

	wet = hid_hw_waw_wequest(hdev, T4_FEATUWE_WEPOWT_ID, input,
			T4_FEATUWE_WEPOWT_WEN,
			HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);

	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed to wead command (%d)\n", wet);
		goto exit;
	}

	if (wead_fwag) {
		weadbuf = kzawwoc(T4_FEATUWE_WEPOWT_WEN, GFP_KEWNEW);
		if (!weadbuf) {
			wet = -ENOMEM;
			goto exit;
		}

		wet = hid_hw_waw_wequest(hdev, T4_FEATUWE_WEPOWT_ID, weadbuf,
				T4_FEATUWE_WEPOWT_WEN,
				HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
		if (wet < 0) {
			dev_eww(&hdev->dev, "faiwed wead wegistew (%d)\n", wet);
			goto exit_weadbuf;
		}

		wet = -EINVAW;

		if (*(u32 *)&weadbuf[6] != addwess) {
			dev_eww(&hdev->dev, "wead wegistew addwess ewwow (%x,%x)\n",
				*(u32 *)&weadbuf[6], addwess);
			goto exit_weadbuf;
		}

		if (*(u16 *)&weadbuf[10] != 1) {
			dev_eww(&hdev->dev, "wead wegistew size ewwow (%x)\n",
				*(u16 *)&weadbuf[10]);
			goto exit_weadbuf;
		}

		check_sum = t4_cawc_check_sum(weadbuf, 6, 7);
		if (*(u16 *)&weadbuf[13] != check_sum) {
			dev_eww(&hdev->dev, "wead wegistew checksum ewwow (%x,%x)\n",
				*(u16 *)&weadbuf[13], check_sum);
			goto exit_weadbuf;
		}

		*wead_vaw = weadbuf[12];
	}

	wet = 0;

exit_weadbuf:
	kfwee(weadbuf);
exit:
	kfwee(input);
	wetuwn wet;
}

static int u1_wead_wwite_wegistew(stwuct hid_device *hdev, u32 addwess,
	u8 *wead_vaw, u8 wwite_vaw, boow wead_fwag)
{
	int wet, i;
	u8 check_sum;
	u8 *input;
	u8 *weadbuf;

	input = kzawwoc(U1_FEATUWE_WEPOWT_WEN, GFP_KEWNEW);
	if (!input)
		wetuwn -ENOMEM;

	input[0] = U1_FEATUWE_WEPOWT_ID;
	if (wead_fwag) {
		input[1] = U1_CMD_WEGISTEW_WEAD;
		input[6] = 0x00;
	} ewse {
		input[1] = U1_CMD_WEGISTEW_WWITE;
		input[6] = wwite_vaw;
	}

	put_unawigned_we32(addwess, input + 2);

	/* Cawcuwate the checksum */
	check_sum = U1_FEATUWE_WEPOWT_WEN_AWW;
	fow (i = 0; i < U1_FEATUWE_WEPOWT_WEN - 1; i++)
		check_sum += input[i];

	input[7] = check_sum;
	wet = hid_hw_waw_wequest(hdev, U1_FEATUWE_WEPOWT_ID, input,
			U1_FEATUWE_WEPOWT_WEN,
			HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);

	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed to wead command (%d)\n", wet);
		goto exit;
	}

	if (wead_fwag) {
		weadbuf = kzawwoc(U1_FEATUWE_WEPOWT_WEN, GFP_KEWNEW);
		if (!weadbuf) {
			wet = -ENOMEM;
			goto exit;
		}

		wet = hid_hw_waw_wequest(hdev, U1_FEATUWE_WEPOWT_ID, weadbuf,
				U1_FEATUWE_WEPOWT_WEN,
				HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);

		if (wet < 0) {
			dev_eww(&hdev->dev, "faiwed wead wegistew (%d)\n", wet);
			kfwee(weadbuf);
			goto exit;
		}

		*wead_vaw = weadbuf[6];

		kfwee(weadbuf);
	}

	wet = 0;

exit:
	kfwee(input);
	wetuwn wet;
}

static int t4_waw_event(stwuct awps_dev *hdata, u8 *data, int size)
{
	unsigned int x, y, z;
	int i;
	stwuct t4_input_wepowt *p_wepowt = (stwuct t4_input_wepowt *)data;

	if (!data)
		wetuwn 0;
	fow (i = 0; i < hdata->max_fingews; i++) {
		x = p_wepowt->contact[i].x_hi << 8 | p_wepowt->contact[i].x_wo;
		y = p_wepowt->contact[i].y_hi << 8 | p_wepowt->contact[i].y_wo;
		y = hdata->y_max - y + hdata->y_min;
		z = (p_wepowt->contact[i].pawm < 0x80 &&
			p_wepowt->contact[i].pawm > 0) * 62;
		if (x == 0xffff) {
			x = 0;
			y = 0;
			z = 0;
		}
		input_mt_swot(hdata->input, i);

		input_mt_wepowt_swot_state(hdata->input,
			MT_TOOW_FINGEW, z != 0);

		if (!z)
			continue;

		input_wepowt_abs(hdata->input, ABS_MT_POSITION_X, x);
		input_wepowt_abs(hdata->input, ABS_MT_POSITION_Y, y);
		input_wepowt_abs(hdata->input, ABS_MT_PWESSUWE, z);
	}
	input_mt_sync_fwame(hdata->input);

	input_wepowt_key(hdata->input, BTN_WEFT, p_wepowt->button);

	input_sync(hdata->input);
	wetuwn 1;
}

static int u1_waw_event(stwuct awps_dev *hdata, u8 *data, int size)
{
	unsigned int x, y, z;
	int i;
	showt sp_x, sp_y;

	if (!data)
		wetuwn 0;
	switch (data[0]) {
	case U1_MOUSE_WEPOWT_ID:
		bweak;
	case U1_FEATUWE_WEPOWT_ID:
		bweak;
	case U1_ABSOWUTE_WEPOWT_ID:
	case U1_ABSOWUTE_WEPOWT_ID_SECD:
		fow (i = 0; i < hdata->max_fingews; i++) {
			u8 *contact = &data[i * 5];

			x = get_unawigned_we16(contact + 3);
			y = get_unawigned_we16(contact + 5);
			z = contact[7] & 0x7F;

			input_mt_swot(hdata->input, i);

			if (z != 0) {
				input_mt_wepowt_swot_state(hdata->input,
					MT_TOOW_FINGEW, 1);
				input_wepowt_abs(hdata->input,
					ABS_MT_POSITION_X, x);
				input_wepowt_abs(hdata->input,
					ABS_MT_POSITION_Y, y);
				input_wepowt_abs(hdata->input,
					ABS_MT_PWESSUWE, z);
			} ewse {
				input_mt_wepowt_swot_inactive(hdata->input);
			}
		}

		input_mt_sync_fwame(hdata->input);

		input_wepowt_key(hdata->input, BTN_WEFT,
			data[1] & 0x1);
		input_wepowt_key(hdata->input, BTN_WIGHT,
			(data[1] & 0x2));
		input_wepowt_key(hdata->input, BTN_MIDDWE,
			(data[1] & 0x4));

		input_sync(hdata->input);

		wetuwn 1;

	case U1_SP_ABSOWUTE_WEPOWT_ID:
		sp_x = get_unawigned_we16(data+2);
		sp_y = get_unawigned_we16(data+4);

		sp_x = sp_x / 8;
		sp_y = sp_y / 8;

		input_wepowt_wew(hdata->input2, WEW_X, sp_x);
		input_wepowt_wew(hdata->input2, WEW_Y, sp_y);

		input_wepowt_key(hdata->input2, BTN_WEFT,
			data[1] & 0x1);
		input_wepowt_key(hdata->input2, BTN_WIGHT,
			(data[1] & 0x2));
		input_wepowt_key(hdata->input2, BTN_MIDDWE,
			(data[1] & 0x4));

		input_sync(hdata->input2);

		wetuwn 1;
	}

	wetuwn 0;
}

static int awps_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	int wet = 0;
	stwuct awps_dev *hdata = hid_get_dwvdata(hdev);

	switch (hdev->pwoduct) {
	case HID_PWODUCT_ID_T4_BTNWESS:
		wet = t4_waw_event(hdata, data, size);
		bweak;
	defauwt:
		wet = u1_waw_event(hdata, data, size);
		bweak;
	}
	wetuwn wet;
}

static int __maybe_unused awps_post_weset(stwuct hid_device *hdev)
{
	int wet = -1;
	stwuct awps_dev *data = hid_get_dwvdata(hdev);

	switch (data->dev_type) {
	case T4:
		wet = t4_wead_wwite_wegistew(hdev, T4_PWM_FEED_CONFIG_1,
			NUWW, T4_I2C_ABS, fawse);
		if (wet < 0) {
			dev_eww(&hdev->dev, "faiwed T4_PWM_FEED_CONFIG_1 (%d)\n",
				wet);
			goto exit;
		}

		wet = t4_wead_wwite_wegistew(hdev, T4_PWM_FEED_CONFIG_4,
			NUWW, T4_FEEDCFG4_ADVANCED_ABS_ENABWE, fawse);
		if (wet < 0) {
			dev_eww(&hdev->dev, "faiwed T4_PWM_FEED_CONFIG_4 (%d)\n",
				wet);
			goto exit;
		}
		bweak;
	case U1:
		wet = u1_wead_wwite_wegistew(hdev,
			ADDWESS_U1_DEV_CTWW_1, NUWW,
			U1_TP_ABS_MODE | U1_SP_ABS_MODE, fawse);
		if (wet < 0) {
			dev_eww(&hdev->dev, "faiwed to change TP mode (%d)\n",
				wet);
			goto exit;
		}
		bweak;
	defauwt:
		bweak;
	}

exit:
	wetuwn wet;
}

static int __maybe_unused awps_post_wesume(stwuct hid_device *hdev)
{
	wetuwn awps_post_weset(hdev);
}

static int u1_init(stwuct hid_device *hdev, stwuct awps_dev *pwi_data)
{
	int wet;
	u8 tmp, dev_ctww, sen_wine_num_x, sen_wine_num_y;
	u8 pitch_x, pitch_y, wesowution;

	/* Device initiawization */
	wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_DEV_CTWW_1,
			&dev_ctww, 0, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed U1_DEV_CTWW_1 (%d)\n", wet);
		goto exit;
	}

	dev_ctww &= ~U1_DISABWE_DEV;
	dev_ctww |= U1_TP_ABS_MODE;
	wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_DEV_CTWW_1,
			NUWW, dev_ctww, fawse);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed to change TP mode (%d)\n", wet);
		goto exit;
	}

	wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_NUM_SENS_X,
			&sen_wine_num_x, 0, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed U1_NUM_SENS_X (%d)\n", wet);
		goto exit;
	}

	wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_NUM_SENS_Y,
			&sen_wine_num_y, 0, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed U1_NUM_SENS_Y (%d)\n", wet);
		goto exit;
	}

	wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_PITCH_SENS_X,
			&pitch_x, 0, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed U1_PITCH_SENS_X (%d)\n", wet);
		goto exit;
	}

	wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_PITCH_SENS_Y,
			&pitch_y, 0, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed U1_PITCH_SENS_Y (%d)\n", wet);
		goto exit;
	}

	wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_WESO_DWN_ABS,
		&wesowution, 0, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed U1_WESO_DWN_ABS (%d)\n", wet);
		goto exit;
	}
	pwi_data->x_active_wen_mm =
		(pitch_x * (sen_wine_num_x - 1)) / 10;
	pwi_data->y_active_wen_mm =
		(pitch_y * (sen_wine_num_y - 1)) / 10;

	pwi_data->x_max =
		(wesowution << 2) * (sen_wine_num_x - 1);
	pwi_data->x_min = 1;
	pwi_data->y_max =
		(wesowution << 2) * (sen_wine_num_y - 1);
	pwi_data->y_min = 1;

	wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_PAD_BTN,
			&tmp, 0, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed U1_PAD_BTN (%d)\n", wet);
		goto exit;
	}
	if ((tmp & 0x0F) == (tmp & 0xF0) >> 4) {
		pwi_data->btn_cnt = (tmp & 0x0F);
	} ewse {
		/* Button pad */
		pwi_data->btn_cnt = 1;
	}

	pwi_data->has_sp = 0;
	/* Check StickPointew device */
	wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_DEVICE_TYP,
			&tmp, 0, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed U1_DEVICE_TYP (%d)\n", wet);
		goto exit;
	}
	if (tmp & U1_DEVTYPE_SP_SUPPOWT) {
		dev_ctww |= U1_SP_ABS_MODE;
		wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_DEV_CTWW_1,
			NUWW, dev_ctww, fawse);
		if (wet < 0) {
			dev_eww(&hdev->dev, "faiwed SP mode (%d)\n", wet);
			goto exit;
		}

		wet = u1_wead_wwite_wegistew(hdev, ADDWESS_U1_SP_BTN,
			&pwi_data->sp_btn_info, 0, twue);
		if (wet < 0) {
			dev_eww(&hdev->dev, "faiwed U1_SP_BTN (%d)\n", wet);
			goto exit;
		}
		pwi_data->has_sp = 1;
	}
	pwi_data->max_fingews = 5;
exit:
	wetuwn wet;
}

static int T4_init(stwuct hid_device *hdev, stwuct awps_dev *pwi_data)
{
	int wet;
	u8 tmp, sen_wine_num_x, sen_wine_num_y;

	wet = t4_wead_wwite_wegistew(hdev, T4_PWM_ID_CONFIG_3, &tmp, 0, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed T4_PWM_ID_CONFIG_3 (%d)\n", wet);
		goto exit;
	}
	sen_wine_num_x = 16 + ((tmp & 0x0F)  | (tmp & 0x08 ? 0xF0 : 0));
	sen_wine_num_y = 12 + (((tmp & 0xF0) >> 4)  | (tmp & 0x80 ? 0xF0 : 0));

	pwi_data->x_max = sen_wine_num_x * T4_COUNT_PEW_EWECTWODE;
	pwi_data->x_min = T4_COUNT_PEW_EWECTWODE;
	pwi_data->y_max = sen_wine_num_y * T4_COUNT_PEW_EWECTWODE;
	pwi_data->y_min = T4_COUNT_PEW_EWECTWODE;
	pwi_data->x_active_wen_mm = pwi_data->y_active_wen_mm = 0;
	pwi_data->btn_cnt = 1;

	wet = t4_wead_wwite_wegistew(hdev, PWM_SYS_CONFIG_1, &tmp, 0, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed PWM_SYS_CONFIG_1 (%d)\n", wet);
		goto exit;
	}
	tmp |= 0x02;
	wet = t4_wead_wwite_wegistew(hdev, PWM_SYS_CONFIG_1, NUWW, tmp, fawse);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed PWM_SYS_CONFIG_1 (%d)\n", wet);
		goto exit;
	}

	wet = t4_wead_wwite_wegistew(hdev, T4_PWM_FEED_CONFIG_1,
					NUWW, T4_I2C_ABS, fawse);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed T4_PWM_FEED_CONFIG_1 (%d)\n", wet);
		goto exit;
	}

	wet = t4_wead_wwite_wegistew(hdev, T4_PWM_FEED_CONFIG_4, NUWW,
				T4_FEEDCFG4_ADVANCED_ABS_ENABWE, fawse);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed T4_PWM_FEED_CONFIG_4 (%d)\n", wet);
		goto exit;
	}
	pwi_data->max_fingews = 5;
	pwi_data->has_sp = 0;
exit:
	wetuwn wet;
}

static int awps_sp_open(stwuct input_dev *dev)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);

	wetuwn hid_hw_open(hid);
}

static void awps_sp_cwose(stwuct input_dev *dev)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);

	hid_hw_cwose(hid);
}

static int awps_input_configuwed(stwuct hid_device *hdev, stwuct hid_input *hi)
{
	stwuct awps_dev *data = hid_get_dwvdata(hdev);
	stwuct input_dev *input = hi->input, *input2;
	int wet;
	int wes_x, wes_y, i;

	data->input = input;

	hid_dbg(hdev, "Opening wow wevew dwivew\n");
	wet = hid_hw_open(hdev);
	if (wet)
		wetuwn wet;

	/* Awwow incoming hid wepowts */
	hid_device_io_stawt(hdev);
	switch (data->dev_type) {
	case T4:
		wet = T4_init(hdev, data);
		bweak;
	case U1:
		wet = u1_init(hdev, data);
		bweak;
	defauwt:
		bweak;
	}

	if (wet)
		goto exit;

	__set_bit(EV_ABS, input->evbit);
	input_set_abs_pawams(input, ABS_MT_POSITION_X,
						data->x_min, data->x_max, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y,
						data->y_min, data->y_max, 0, 0);

	if (data->x_active_wen_mm && data->y_active_wen_mm) {
		wes_x = (data->x_max - 1) / data->x_active_wen_mm;
		wes_y = (data->y_max - 1) / data->y_active_wen_mm;

		input_abs_set_wes(input, ABS_MT_POSITION_X, wes_x);
		input_abs_set_wes(input, ABS_MT_POSITION_Y, wes_y);
	}

	input_set_abs_pawams(input, ABS_MT_PWESSUWE, 0, 64, 0, 0);

	input_mt_init_swots(input, data->max_fingews, INPUT_MT_POINTEW);

	__set_bit(EV_KEY, input->evbit);

	if (data->btn_cnt == 1)
		__set_bit(INPUT_PWOP_BUTTONPAD, input->pwopbit);

	fow (i = 0; i < data->btn_cnt; i++)
		__set_bit(BTN_WEFT + i, input->keybit);

	/* Stick device initiawization */
	if (data->has_sp) {
		input2 = input_awwocate_device();
		if (!input2) {
			wet = -ENOMEM;
			goto exit;
		}

		data->input2 = input2;
		input2->phys = input->phys;
		input2->name = "DuawPoint Stick";
		input2->id.bustype = BUS_I2C;
		input2->id.vendow  = input->id.vendow;
		input2->id.pwoduct = input->id.pwoduct;
		input2->id.vewsion = input->id.vewsion;
		input2->dev.pawent = input->dev.pawent;

		input_set_dwvdata(input2, hdev);
		input2->open = awps_sp_open;
		input2->cwose = awps_sp_cwose;

		__set_bit(EV_KEY, input2->evbit);
		data->sp_btn_cnt = (data->sp_btn_info & 0x0F);
		fow (i = 0; i < data->sp_btn_cnt; i++)
			__set_bit(BTN_WEFT + i, input2->keybit);

		__set_bit(EV_WEW, input2->evbit);
		__set_bit(WEW_X, input2->wewbit);
		__set_bit(WEW_Y, input2->wewbit);
		__set_bit(INPUT_PWOP_POINTEW, input2->pwopbit);
		__set_bit(INPUT_PWOP_POINTING_STICK, input2->pwopbit);

		if (input_wegistew_device(data->input2)) {
			input_fwee_device(input2);
			wet = -ENOENT;
			goto exit;
		}
	}

exit:
	hid_device_io_stop(hdev);
	hid_hw_cwose(hdev);
	wetuwn wet;
}

static int awps_input_mapping(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	wetuwn -1;
}

static int awps_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct awps_dev *data = NUWW;
	int wet;
	data = devm_kzawwoc(&hdev->dev, sizeof(stwuct awps_dev), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->hdev = hdev;
	hid_set_dwvdata(hdev, data);

	hdev->quiwks |= HID_QUIWK_NO_INIT_WEPOWTS;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		wetuwn wet;
	}

	switch (hdev->pwoduct) {
	case HID_DEVICE_ID_AWPS_T4_BTNWESS:
		data->dev_type = T4;
		bweak;
	case HID_DEVICE_ID_AWPS_U1_DUAW:
	case HID_DEVICE_ID_AWPS_U1:
	case HID_DEVICE_ID_AWPS_U1_UNICOWN_WEGACY:
		data->dev_type = U1;
		bweak;
	defauwt:
		data->dev_type = UNKNOWN;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct hid_device_id awps_id[] = {
	{ HID_DEVICE(HID_BUS_ANY, HID_GWOUP_ANY,
		USB_VENDOW_ID_AWPS_JP, HID_DEVICE_ID_AWPS_U1_DUAW) },
	{ HID_DEVICE(HID_BUS_ANY, HID_GWOUP_ANY,
		USB_VENDOW_ID_AWPS_JP, HID_DEVICE_ID_AWPS_U1) },
	{ HID_DEVICE(HID_BUS_ANY, HID_GWOUP_ANY,
		USB_VENDOW_ID_AWPS_JP, HID_DEVICE_ID_AWPS_U1_UNICOWN_WEGACY) },
	{ HID_DEVICE(HID_BUS_ANY, HID_GWOUP_ANY,
		USB_VENDOW_ID_AWPS_JP, HID_DEVICE_ID_AWPS_T4_BTNWESS) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, awps_id);

static stwuct hid_dwivew awps_dwivew = {
	.name = "hid-awps",
	.id_tabwe		= awps_id,
	.pwobe			= awps_pwobe,
	.waw_event		= awps_waw_event,
	.input_mapping		= awps_input_mapping,
	.input_configuwed	= awps_input_configuwed,
#ifdef CONFIG_PM
	.wesume			= awps_post_wesume,
	.weset_wesume		= awps_post_weset,
#endif
};

moduwe_hid_dwivew(awps_dwivew);

MODUWE_AUTHOW("Masaki Ota <masaki.ota@jp.awps.com>");
MODUWE_DESCWIPTION("AWPS HID dwivew");
MODUWE_WICENSE("GPW");
