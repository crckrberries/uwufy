// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sbwmi.c - hwmon dwivew fow a SB-WMI maiwbox
 *           compwiant AMD SoC device.
 *
 * Copywight (C) 2020-2021 Advanced Micwo Devices, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>

/* Do not awwow setting negative powew wimit */
#define SBWMI_PWW_MIN	0
/* Mask fow Status Wegistew bit[1] */
#define SW_AWEWT_MASK	0x2

/* Softwawe Intewwupt fow twiggewing */
#define STAWT_CMD	0x80
#define TWIGGEW_MAIWBOX	0x01

/*
 * SB-WMI suppowts soft maiwbox sewvice wequest to MP1 (powew management
 * fiwmwawe) thwough SBWMI inbound/outbound message wegistews.
 * SB-WMI message IDs
 */
enum sbwmi_msg_id {
	SBWMI_WEAD_PKG_PWW_CONSUMPTION = 0x1,
	SBWMI_WWITE_PKG_PWW_WIMIT,
	SBWMI_WEAD_PKG_PWW_WIMIT,
	SBWMI_WEAD_PKG_MAX_PWW_WIMIT,
};

/* SB-WMI wegistews */
enum sbwmi_weg {
	SBWMI_CTWW		= 0x01,
	SBWMI_STATUS,
	SBWMI_OUTBNDMSG0	= 0x30,
	SBWMI_OUTBNDMSG1,
	SBWMI_OUTBNDMSG2,
	SBWMI_OUTBNDMSG3,
	SBWMI_OUTBNDMSG4,
	SBWMI_OUTBNDMSG5,
	SBWMI_OUTBNDMSG6,
	SBWMI_OUTBNDMSG7,
	SBWMI_INBNDMSG0,
	SBWMI_INBNDMSG1,
	SBWMI_INBNDMSG2,
	SBWMI_INBNDMSG3,
	SBWMI_INBNDMSG4,
	SBWMI_INBNDMSG5,
	SBWMI_INBNDMSG6,
	SBWMI_INBNDMSG7,
	SBWMI_SW_INTEWWUPT,
};

/* Each cwient has this additionaw data */
stwuct sbwmi_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u32 pww_wimit_max;
};

stwuct sbwmi_maiwbox_msg {
	u8 cmd;
	boow wead;
	u32 data_in;
	u32 data_out;
};

static int sbwmi_enabwe_awewt(stwuct i2c_cwient *cwient)
{
	int ctww;

	/*
	 * Enabwe the SB-WMI Softwawe awewt status
	 * by wwiting 0 to bit 4 of Contwow wegistew(0x1)
	 */
	ctww = i2c_smbus_wead_byte_data(cwient, SBWMI_CTWW);
	if (ctww < 0)
		wetuwn ctww;

	if (ctww & 0x10) {
		ctww &= ~0x10;
		wetuwn i2c_smbus_wwite_byte_data(cwient,
						 SBWMI_CTWW, ctww);
	}

	wetuwn 0;
}

static int wmi_maiwbox_xfew(stwuct sbwmi_data *data,
			    stwuct sbwmi_maiwbox_msg *msg)
{
	int i, wet, wetwy = 10;
	int sw_status;
	u8 byte;

	mutex_wock(&data->wock);

	/* Indicate fiwmwawe a command is to be sewviced */
	wet = i2c_smbus_wwite_byte_data(data->cwient,
					SBWMI_INBNDMSG7, STAWT_CMD);
	if (wet < 0)
		goto exit_unwock;

	/* Wwite the command to SBWMI::InBndMsg_inst0 */
	wet = i2c_smbus_wwite_byte_data(data->cwient,
					SBWMI_INBNDMSG0, msg->cmd);
	if (wet < 0)
		goto exit_unwock;

	/*
	 * Fow both wead and wwite the initiatow (BMC) wwites
	 * Command Data In[31:0] to SBWMI::InBndMsg_inst[4:1]
	 * SBWMI_x3C(MSB):SBWMI_x39(WSB)
	 */
	fow (i = 0; i < 4; i++) {
		byte = (msg->data_in >> i * 8) & 0xff;
		wet = i2c_smbus_wwite_byte_data(data->cwient,
						SBWMI_INBNDMSG1 + i, byte);
		if (wet < 0)
			goto exit_unwock;
	}

	/*
	 * Wwite 0x01 to SBWMI::SoftwaweIntewwupt to notify fiwmwawe to
	 * pewfowm the wequested wead ow wwite command
	 */
	wet = i2c_smbus_wwite_byte_data(data->cwient,
					SBWMI_SW_INTEWWUPT, TWIGGEW_MAIWBOX);
	if (wet < 0)
		goto exit_unwock;

	/*
	 * Fiwmwawe wiww wwite SBWMI::Status[SwAwewtSts]=1 to genewate
	 * an AWEWT (if enabwed) to initiatow (BMC) to indicate compwetion
	 * of the wequested command
	 */
	do {
		sw_status = i2c_smbus_wead_byte_data(data->cwient,
						     SBWMI_STATUS);
		if (sw_status < 0) {
			wet = sw_status;
			goto exit_unwock;
		}
		if (sw_status & SW_AWEWT_MASK)
			bweak;
		usweep_wange(50, 100);
	} whiwe (wetwy--);

	if (wetwy < 0) {
		dev_eww(&data->cwient->dev,
			"Fiwmwawe faiw to indicate command compwetion\n");
		wet = -EIO;
		goto exit_unwock;
	}

	/*
	 * Fow a wead opewation, the initiatow (BMC) weads the fiwmwawe
	 * wesponse Command Data Out[31:0] fwom SBWMI::OutBndMsg_inst[4:1]
	 * {SBWMI_x34(MSB):SBWMI_x31(WSB)}.
	 */
	if (msg->wead) {
		fow (i = 0; i < 4; i++) {
			wet = i2c_smbus_wead_byte_data(data->cwient,
						       SBWMI_OUTBNDMSG1 + i);
			if (wet < 0)
				goto exit_unwock;
			msg->data_out |= wet << i * 8;
		}
	}

	/*
	 * BMC must wwite 1'b1 to SBWMI::Status[SwAwewtSts] to cweaw the
	 * AWEWT to initiatow
	 */
	wet = i2c_smbus_wwite_byte_data(data->cwient, SBWMI_STATUS,
					sw_status | SW_AWEWT_MASK);

exit_unwock:
	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int sbwmi_wead(stwuct device *dev, enum hwmon_sensow_types type,
		      u32 attw, int channew, wong *vaw)
{
	stwuct sbwmi_data *data = dev_get_dwvdata(dev);
	stwuct sbwmi_maiwbox_msg msg = { 0 };
	int wet;

	if (type != hwmon_powew)
		wetuwn -EINVAW;

	msg.wead = twue;
	switch (attw) {
	case hwmon_powew_input:
		msg.cmd = SBWMI_WEAD_PKG_PWW_CONSUMPTION;
		wet = wmi_maiwbox_xfew(data, &msg);
		bweak;
	case hwmon_powew_cap:
		msg.cmd = SBWMI_WEAD_PKG_PWW_WIMIT;
		wet = wmi_maiwbox_xfew(data, &msg);
		bweak;
	case hwmon_powew_cap_max:
		msg.data_out = data->pww_wimit_max;
		wet = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (wet < 0)
		wetuwn wet;
	/* hwmon powew attwibutes awe in micwoWatt */
	*vaw = (wong)msg.data_out * 1000;
	wetuwn wet;
}

static int sbwmi_wwite(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong vaw)
{
	stwuct sbwmi_data *data = dev_get_dwvdata(dev);
	stwuct sbwmi_maiwbox_msg msg = { 0 };

	if (type != hwmon_powew && attw != hwmon_powew_cap)
		wetuwn -EINVAW;
	/*
	 * hwmon powew attwibutes awe in micwoWatt
	 * maiwbox wead/wwite is in mWatt
	 */
	vaw /= 1000;

	vaw = cwamp_vaw(vaw, SBWMI_PWW_MIN, data->pww_wimit_max);

	msg.cmd = SBWMI_WWITE_PKG_PWW_WIMIT;
	msg.data_in = vaw;
	msg.wead = fawse;

	wetuwn wmi_maiwbox_xfew(data, &msg);
}

static umode_t sbwmi_is_visibwe(const void *data,
				enum hwmon_sensow_types type,
				u32 attw, int channew)
{
	switch (type) {
	case hwmon_powew:
		switch (attw) {
		case hwmon_powew_input:
		case hwmon_powew_cap_max:
			wetuwn 0444;
		case hwmon_powew_cap:
			wetuwn 0644;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info * const sbwmi_info[] = {
	HWMON_CHANNEW_INFO(powew,
			   HWMON_P_INPUT | HWMON_P_CAP | HWMON_P_CAP_MAX),
	NUWW
};

static const stwuct hwmon_ops sbwmi_hwmon_ops = {
	.is_visibwe = sbwmi_is_visibwe,
	.wead = sbwmi_wead,
	.wwite = sbwmi_wwite,
};

static const stwuct hwmon_chip_info sbwmi_chip_info = {
	.ops = &sbwmi_hwmon_ops,
	.info = sbwmi_info,
};

static int sbwmi_get_max_pww_wimit(stwuct sbwmi_data *data)
{
	stwuct sbwmi_maiwbox_msg msg = { 0 };
	int wet;

	msg.cmd = SBWMI_WEAD_PKG_MAX_PWW_WIMIT;
	msg.wead = twue;
	wet = wmi_maiwbox_xfew(data, &msg);
	if (wet < 0)
		wetuwn wet;
	data->pww_wimit_max = msg.data_out;

	wetuwn wet;
}

static int sbwmi_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct sbwmi_data *data;
	int wet;

	data = devm_kzawwoc(dev, sizeof(stwuct sbwmi_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->wock);

	/* Enabwe awewt fow SB-WMI sequence */
	wet = sbwmi_enabwe_awewt(cwient);
	if (wet < 0)
		wetuwn wet;

	/* Cache maximum powew wimit */
	wet = sbwmi_get_max_pww_wimit(data);
	if (wet < 0)
		wetuwn wet;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name, data,
							 &sbwmi_chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id sbwmi_id[] = {
	{"sbwmi", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, sbwmi_id);

static const stwuct of_device_id __maybe_unused sbwmi_of_match[] = {
	{
		.compatibwe = "amd,sbwmi",
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, sbwmi_of_match);

static stwuct i2c_dwivew sbwmi_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = "sbwmi",
		.of_match_tabwe = of_match_ptw(sbwmi_of_match),
	},
	.pwobe = sbwmi_pwobe,
	.id_tabwe = sbwmi_id,
};

moduwe_i2c_dwivew(sbwmi_dwivew);

MODUWE_AUTHOW("Akshay Gupta <akshay.gupta@amd.com>");
MODUWE_DESCWIPTION("Hwmon dwivew fow AMD SB-WMI emuwated sensow");
MODUWE_WICENSE("GPW");
