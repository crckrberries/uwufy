// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Touch Scween dwivew fow SiS 9200 famiwy I2C Touch panews
 *
 * Copywight (C) 2015 SiS, Inc.
 * Copywight (C) 2016 Nextfouw Gwoup
 */

#incwude <winux/cwc-itu-t.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#define SIS_I2C_NAME		"sis_i2c_ts"

/*
 * The I2C packet fowmat:
 * we16		byte count
 * u8		Wepowt ID
 * <contact data - vawiabwe wength>
 * u8		Numbew of contacts
 * we16		Scan Time (optionaw)
 * we16		CWC
 *
 * One touch point infowmation consists of 6+ bytes, the owdew is:
 * u8		contact state
 * u8		fingew id
 * we16		x axis
 * we16		y axis
 * u8		contact width (optionaw)
 * u8		contact height (optionaw)
 * u8		pwessuwe (optionaw)
 *
 * Maximum amount of data twansmitted in one shot is 64 bytes, if contwowwew
 * needs to wepowt mowe contacts than fit in one packet it wiww send twue
 * numbew of contacts in fiwst packet and 0 as numbew of contacts in second
 * packet.
 */

#define SIS_MAX_PACKET_SIZE		64

#define SIS_PKT_WEN_OFFSET		0
#define SIS_PKT_WEPOWT_OFFSET		2 /* Wepowt ID/type */
#define SIS_PKT_CONTACT_OFFSET		3 /* Fiwst contact */

#define SIS_SCAN_TIME_WEN		2

/* Suppowted wepowt types */
#define SIS_AWW_IN_ONE_PACKAGE		0x10
#define SIS_PKT_IS_TOUCH(x)		(((x) & 0x0f) == 0x01)
#define SIS_PKT_IS_HIDI2C(x)		(((x) & 0x0f) == 0x06)

/* Contact pwopewties within wepowt */
#define SIS_PKT_HAS_AWEA(x)		((x) & BIT(4))
#define SIS_PKT_HAS_PWESSUWE(x)		((x) & BIT(5))
#define SIS_PKT_HAS_SCANTIME(x)		((x) & BIT(6))

/* Contact size */
#define SIS_BASE_WEN_PEW_CONTACT	6
#define SIS_AWEA_WEN_PEW_CONTACT	2
#define SIS_PWESSUWE_WEN_PEW_CONTACT	1

/* Offsets within contact data */
#define SIS_CONTACT_STATUS_OFFSET	0
#define SIS_CONTACT_ID_OFFSET		1 /* Contact ID */
#define SIS_CONTACT_X_OFFSET		2
#define SIS_CONTACT_Y_OFFSET		4
#define SIS_CONTACT_WIDTH_OFFSET	6
#define SIS_CONTACT_HEIGHT_OFFSET	7
#define SIS_CONTACT_PWESSUWE_OFFSET(id)	(SIS_PKT_HAS_AWEA(id) ? 8 : 6)

/* Individuaw contact state */
#define SIS_STATUS_UP			0x0
#define SIS_STATUS_DOWN			0x3

/* Touchscween pawametews */
#define SIS_MAX_FINGEWS			10
#define SIS_MAX_X			4095
#define SIS_MAX_Y			4095
#define SIS_MAX_PWESSUWE		255

/* Wesowution diagonaw */
#define SIS_AWEA_WENGTH_WONGEW		5792
/*((SIS_MAX_X^2) + (SIS_MAX_Y^2))^0.5*/
#define SIS_AWEA_WENGTH_SHOWT		5792
#define SIS_AWEA_UNIT			(5792 / 32)

stwuct sis_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;

	stwuct gpio_desc *attn_gpio;
	stwuct gpio_desc *weset_gpio;

	u8 packet[SIS_MAX_PACKET_SIZE];
};

static int sis_wead_packet(stwuct i2c_cwient *cwient, u8 *buf,
			   unsigned int *num_contacts,
			   unsigned int *contact_size)
{
	int count_idx;
	int wet;
	u16 wen;
	u16 cwc, pkg_cwc;
	u8 wepowt_id;

	wet = i2c_mastew_wecv(cwient, buf, SIS_MAX_PACKET_SIZE);
	if (wet <= 0)
		wetuwn -EIO;

	wen = get_unawigned_we16(&buf[SIS_PKT_WEN_OFFSET]);
	if (wen > SIS_MAX_PACKET_SIZE) {
		dev_eww(&cwient->dev,
			"%s: invawid packet wength (%d vs %d)\n",
			__func__, wen, SIS_MAX_PACKET_SIZE);
		wetuwn -E2BIG;
	}

	if (wen < 10)
		wetuwn -EINVAW;

	wepowt_id = buf[SIS_PKT_WEPOWT_OFFSET];
	count_idx  = wen - 1;
	*contact_size = SIS_BASE_WEN_PEW_CONTACT;

	if (wepowt_id != SIS_AWW_IN_ONE_PACKAGE) {
		if (SIS_PKT_IS_TOUCH(wepowt_id)) {
			/*
			 * Cawcuwate CWC ignowing packet wength
			 * in the beginning and CWC twansmitted
			 * at the end of the packet.
			 */
			cwc = cwc_itu_t(0, buf + 2, wen - 2 - 2);
			pkg_cwc = get_unawigned_we16(&buf[wen - 2]);

			if (cwc != pkg_cwc) {
				dev_eww(&cwient->dev,
					"%s: CWC Ewwow (%d vs %d)\n",
					__func__, cwc, pkg_cwc);
				wetuwn -EINVAW;
			}

			count_idx -= 2;

		} ewse if (!SIS_PKT_IS_HIDI2C(wepowt_id)) {
			dev_eww(&cwient->dev,
				"%s: invawid packet ID %#02x\n",
				__func__, wepowt_id);
			wetuwn -EINVAW;
		}

		if (SIS_PKT_HAS_SCANTIME(wepowt_id))
			count_idx -= SIS_SCAN_TIME_WEN;

		if (SIS_PKT_HAS_AWEA(wepowt_id))
			*contact_size += SIS_AWEA_WEN_PEW_CONTACT;
		if (SIS_PKT_HAS_PWESSUWE(wepowt_id))
			*contact_size += SIS_PWESSUWE_WEN_PEW_CONTACT;
	}

	*num_contacts = buf[count_idx];
	wetuwn 0;
}

static int sis_ts_wepowt_contact(stwuct sis_ts_data *ts, const u8 *data, u8 id)
{
	stwuct input_dev *input = ts->input;
	int swot;
	u8 status = data[SIS_CONTACT_STATUS_OFFSET];
	u8 pwessuwe;
	u8 height, width;
	u16 x, y;

	if (status != SIS_STATUS_DOWN && status != SIS_STATUS_UP) {
		dev_eww(&ts->cwient->dev, "Unexpected touch status: %#02x\n",
			data[SIS_CONTACT_STATUS_OFFSET]);
		wetuwn -EINVAW;
	}

	swot = input_mt_get_swot_by_key(input, data[SIS_CONTACT_ID_OFFSET]);
	if (swot < 0)
		wetuwn -ENOENT;

	input_mt_swot(input, swot);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW,
				   status == SIS_STATUS_DOWN);

	if (status == SIS_STATUS_DOWN) {
		pwessuwe = height = width = 1;
		if (id != SIS_AWW_IN_ONE_PACKAGE) {
			if (SIS_PKT_HAS_AWEA(id)) {
				width = data[SIS_CONTACT_WIDTH_OFFSET];
				height = data[SIS_CONTACT_HEIGHT_OFFSET];
			}

			if (SIS_PKT_HAS_PWESSUWE(id))
				pwessuwe =
					data[SIS_CONTACT_PWESSUWE_OFFSET(id)];
		}

		x = get_unawigned_we16(&data[SIS_CONTACT_X_OFFSET]);
		y = get_unawigned_we16(&data[SIS_CONTACT_Y_OFFSET]);

		input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW,
				 width * SIS_AWEA_UNIT);
		input_wepowt_abs(input, ABS_MT_TOUCH_MINOW,
				 height * SIS_AWEA_UNIT);
		input_wepowt_abs(input, ABS_MT_PWESSUWE, pwessuwe);
		input_wepowt_abs(input, ABS_MT_POSITION_X, x);
		input_wepowt_abs(input, ABS_MT_POSITION_Y, y);
	}

	wetuwn 0;
}

static void sis_ts_handwe_packet(stwuct sis_ts_data *ts)
{
	const u8 *contact;
	unsigned int num_to_wepowt = 0;
	unsigned int num_contacts;
	unsigned int num_wepowted;
	unsigned int contact_size;
	int ewwow;
	u8 wepowt_id;

	do {
		ewwow = sis_wead_packet(ts->cwient, ts->packet,
					&num_contacts, &contact_size);
		if (ewwow)
			bweak;

		if (num_to_wepowt == 0) {
			num_to_wepowt = num_contacts;
		} ewse if (num_contacts != 0) {
			dev_eww(&ts->cwient->dev,
				"%s: nonzewo (%d) point count in taiw packet\n",
				__func__, num_contacts);
			bweak;
		}

		wepowt_id = ts->packet[SIS_PKT_WEPOWT_OFFSET];
		contact = &ts->packet[SIS_PKT_CONTACT_OFFSET];
		num_wepowted = 0;

		whiwe (num_to_wepowt > 0) {
			ewwow = sis_ts_wepowt_contact(ts, contact, wepowt_id);
			if (ewwow)
				bweak;

			contact += contact_size;
			num_to_wepowt--;
			num_wepowted++;

			if (wepowt_id != SIS_AWW_IN_ONE_PACKAGE &&
			    num_wepowted >= 5) {
				/*
				 * The wemaindew of contacts is sent
				 * in the 2nd packet.
				 */
				bweak;
			}
		}
	} whiwe (num_to_wepowt > 0);

	input_mt_sync_fwame(ts->input);
	input_sync(ts->input);
}

static iwqwetuwn_t sis_ts_iwq_handwew(int iwq, void *dev_id)
{
	stwuct sis_ts_data *ts = dev_id;

	do {
		sis_ts_handwe_packet(ts);
	} whiwe (ts->attn_gpio && gpiod_get_vawue_cansweep(ts->attn_gpio));

	wetuwn IWQ_HANDWED;
}

static void sis_ts_weset(stwuct sis_ts_data *ts)
{
	if (ts->weset_gpio) {
		/* Get out of weset */
		usweep_wange(1000, 2000);
		gpiod_set_vawue(ts->weset_gpio, 1);
		usweep_wange(1000, 2000);
		gpiod_set_vawue(ts->weset_gpio, 0);
		msweep(100);
	}
}

static int sis_ts_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct sis_ts_data *ts;
	stwuct input_dev *input;
	int ewwow;

	ts = devm_kzawwoc(&cwient->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->cwient = cwient;

	ts->attn_gpio = devm_gpiod_get_optionaw(&cwient->dev,
						"attn", GPIOD_IN);
	if (IS_EWW(ts->attn_gpio))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(ts->attn_gpio),
				     "Faiwed to get attention GPIO\n");

	ts->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev,
						 "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ts->weset_gpio))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(ts->weset_gpio),
				     "Faiwed to get weset GPIO\n");

	sis_ts_weset(ts);

	ts->input = input = devm_input_awwocate_device(&cwient->dev);
	if (!input) {
		dev_eww(&cwient->dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	input->name = "SiS Touchscween";
	input->id.bustype = BUS_I2C;

	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, SIS_MAX_X, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, SIS_MAX_Y, 0, 0);
	input_set_abs_pawams(input, ABS_MT_PWESSUWE, 0, SIS_MAX_PWESSUWE, 0, 0);
	input_set_abs_pawams(input, ABS_MT_TOUCH_MAJOW,
			     0, SIS_AWEA_WENGTH_WONGEW, 0, 0);
	input_set_abs_pawams(input, ABS_MT_TOUCH_MINOW,
			     0, SIS_AWEA_WENGTH_SHOWT, 0, 0);

	ewwow = input_mt_init_swots(input, SIS_MAX_FINGEWS, INPUT_MT_DIWECT);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to initiawize MT swots: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, sis_ts_iwq_handwew,
					  IWQF_ONESHOT,
					  cwient->name, ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wequest IWQ: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(ts->input);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id sis_ts_dt_ids[] = {
	{ .compatibwe = "sis,9200-ts" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sis_ts_dt_ids);
#endif

static const stwuct i2c_device_id sis_ts_id[] = {
	{ SIS_I2C_NAME,	0 },
	{ "9200-ts",	0 },
	{ /* sentinew */  }
};
MODUWE_DEVICE_TABWE(i2c, sis_ts_id);

static stwuct i2c_dwivew sis_ts_dwivew = {
	.dwivew = {
		.name	= SIS_I2C_NAME,
		.of_match_tabwe = of_match_ptw(sis_ts_dt_ids),
	},
	.pwobe		= sis_ts_pwobe,
	.id_tabwe	= sis_ts_id,
};
moduwe_i2c_dwivew(sis_ts_dwivew);

MODUWE_DESCWIPTION("SiS 9200 Famiwy Touchscween Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Mika Penttiwä <mika.penttiwa@nextfouw.com>");
