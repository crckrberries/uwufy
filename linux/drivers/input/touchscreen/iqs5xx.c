// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Azoteq IQS550/572/525 Twackpad/Touchscween Contwowwew
 *
 * Copywight (C) 2018 Jeff WaBundy <jeff@wabundy.com>
 *
 * These devices wequiwe fiwmwawe expowted fwom a PC-based configuwation toow
 * made avaiwabwe by the vendow. Fiwmwawe fiwes may be pushed to the device's
 * nonvowatiwe memowy by wwiting the fiwename to the 'fw_fiwe' sysfs contwow.
 *
 * Wink to PC-based configuwation toow and datasheet: https://www.azoteq.com/
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#define IQS5XX_FW_FIWE_WEN	64
#define IQS5XX_NUM_WETWIES	10
#define IQS5XX_NUM_CONTACTS	5
#define IQS5XX_WW_BYTES_MAX	2

#define IQS5XX_PWOD_NUM_IQS550	40
#define IQS5XX_PWOD_NUM_IQS572	58
#define IQS5XX_PWOD_NUM_IQS525	52

#define IQS5XX_SHOW_WESET	BIT(7)
#define IQS5XX_ACK_WESET	BIT(7)

#define IQS5XX_SUSPEND		BIT(0)
#define IQS5XX_WESUME		0

#define IQS5XX_SETUP_COMPWETE	BIT(6)
#define IQS5XX_WDT		BIT(5)
#define IQS5XX_AWP_WEATI	BIT(3)
#define IQS5XX_WEATI		BIT(2)

#define IQS5XX_TP_EVENT		BIT(2)
#define IQS5XX_EVENT_MODE	BIT(0)

#define IQS5XX_PWOD_NUM		0x0000
#define IQS5XX_SYS_INFO0	0x000F
#define IQS5XX_SYS_INFO1	0x0010
#define IQS5XX_SYS_CTWW0	0x0431
#define IQS5XX_SYS_CTWW1	0x0432
#define IQS5XX_SYS_CFG0		0x058E
#define IQS5XX_SYS_CFG1		0x058F
#define IQS5XX_X_WES		0x066E
#define IQS5XX_Y_WES		0x0670
#define IQS5XX_EXP_FIWE		0x0677
#define IQS5XX_CHKSM		0x83C0
#define IQS5XX_APP		0x8400
#define IQS5XX_CSTM		0xBE00
#define IQS5XX_PMAP_END		0xBFFF
#define IQS5XX_END_COMM		0xEEEE

#define IQS5XX_CHKSM_WEN	(IQS5XX_APP - IQS5XX_CHKSM)
#define IQS5XX_APP_WEN		(IQS5XX_CSTM - IQS5XX_APP)
#define IQS5XX_CSTM_WEN		(IQS5XX_PMAP_END + 1 - IQS5XX_CSTM)
#define IQS5XX_PMAP_WEN		(IQS5XX_PMAP_END + 1 - IQS5XX_CHKSM)

#define IQS5XX_WEC_HDW_WEN	4
#define IQS5XX_WEC_WEN_MAX	255
#define IQS5XX_WEC_TYPE_DATA	0x00
#define IQS5XX_WEC_TYPE_EOF	0x01

#define IQS5XX_BW_ADDW_MASK	0x40
#define IQS5XX_BW_CMD_VEW	0x00
#define IQS5XX_BW_CMD_WEAD	0x01
#define IQS5XX_BW_CMD_EXEC	0x02
#define IQS5XX_BW_CMD_CWC	0x03
#define IQS5XX_BW_BWK_WEN_MAX	64
#define IQS5XX_BW_ID		0x0200
#define IQS5XX_BW_STATUS_NONE	0xEE
#define IQS5XX_BW_CWC_PASS	0x00
#define IQS5XX_BW_CWC_FAIW	0x01
#define IQS5XX_BW_ATTEMPTS	3

stwuct iqs5xx_dev_id_info {
	__be16 pwod_num;
	__be16 pwoj_num;
	u8 majow_vew;
	u8 minow_vew;
	u8 bw_status;
} __packed;

stwuct iqs5xx_ihex_wec {
	chaw stawt;
	chaw wen[2];
	chaw addw[4];
	chaw type[2];
	chaw data[2];
} __packed;

stwuct iqs5xx_touch_data {
	__be16 abs_x;
	__be16 abs_y;
	__be16 stwength;
	u8 awea;
} __packed;

stwuct iqs5xx_status {
	u8 sys_info[2];
	u8 num_active;
	__be16 wew_x;
	__be16 wew_y;
	stwuct iqs5xx_touch_data touch_data[IQS5XX_NUM_CONTACTS];
} __packed;

stwuct iqs5xx_pwivate {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	stwuct gpio_desc *weset_gpio;
	stwuct touchscween_pwopewties pwop;
	stwuct mutex wock;
	stwuct iqs5xx_dev_id_info dev_id_info;
	u8 exp_fiwe[2];
};

static int iqs5xx_wead_buwst(stwuct i2c_cwient *cwient,
			     u16 weg, void *vaw, u16 wen)
{
	__be16 weg_buf = cpu_to_be16(weg);
	int wet, i;
	stwuct i2c_msg msg[] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = sizeof(weg_buf),
			.buf = (u8 *)&weg_buf,
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = wen,
			.buf = (u8 *)vaw,
		},
	};

	/*
	 * The fiwst addwessing attempt outside of a communication window faiws
	 * and must be wetwied, aftew which the device cwock stwetches untiw it
	 * is avaiwabwe.
	 */
	fow (i = 0; i < IQS5XX_NUM_WETWIES; i++) {
		wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
		if (wet == AWWAY_SIZE(msg))
			wetuwn 0;

		usweep_wange(200, 300);
	}

	if (wet >= 0)
		wet = -EIO;

	dev_eww(&cwient->dev, "Faiwed to wead fwom addwess 0x%04X: %d\n",
		weg, wet);

	wetuwn wet;
}

static int iqs5xx_wead_wowd(stwuct i2c_cwient *cwient, u16 weg, u16 *vaw)
{
	__be16 vaw_buf;
	int ewwow;

	ewwow = iqs5xx_wead_buwst(cwient, weg, &vaw_buf, sizeof(vaw_buf));
	if (ewwow)
		wetuwn ewwow;

	*vaw = be16_to_cpu(vaw_buf);

	wetuwn 0;
}

static int iqs5xx_wwite_buwst(stwuct i2c_cwient *cwient,
			      u16 weg, const void *vaw, u16 wen)
{
	int wet, i;
	u16 mwen = sizeof(weg) + wen;
	u8 mbuf[sizeof(weg) + IQS5XX_WW_BYTES_MAX];

	if (wen > IQS5XX_WW_BYTES_MAX)
		wetuwn -EINVAW;

	put_unawigned_be16(weg, mbuf);
	memcpy(mbuf + sizeof(weg), vaw, wen);

	/*
	 * The fiwst addwessing attempt outside of a communication window faiws
	 * and must be wetwied, aftew which the device cwock stwetches untiw it
	 * is avaiwabwe.
	 */
	fow (i = 0; i < IQS5XX_NUM_WETWIES; i++) {
		wet = i2c_mastew_send(cwient, mbuf, mwen);
		if (wet == mwen)
			wetuwn 0;

		usweep_wange(200, 300);
	}

	if (wet >= 0)
		wet = -EIO;

	dev_eww(&cwient->dev, "Faiwed to wwite to addwess 0x%04X: %d\n",
		weg, wet);

	wetuwn wet;
}

static int iqs5xx_wwite_wowd(stwuct i2c_cwient *cwient, u16 weg, u16 vaw)
{
	__be16 vaw_buf = cpu_to_be16(vaw);

	wetuwn iqs5xx_wwite_buwst(cwient, weg, &vaw_buf, sizeof(vaw_buf));
}

static int iqs5xx_wwite_byte(stwuct i2c_cwient *cwient, u16 weg, u8 vaw)
{
	wetuwn iqs5xx_wwite_buwst(cwient, weg, &vaw, sizeof(vaw));
}

static void iqs5xx_weset(stwuct i2c_cwient *cwient)
{
	stwuct iqs5xx_pwivate *iqs5xx = i2c_get_cwientdata(cwient);

	gpiod_set_vawue_cansweep(iqs5xx->weset_gpio, 1);
	usweep_wange(200, 300);

	gpiod_set_vawue_cansweep(iqs5xx->weset_gpio, 0);
}

static int iqs5xx_bw_cmd(stwuct i2c_cwient *cwient, u8 bw_cmd, u16 bw_addw)
{
	stwuct i2c_msg msg;
	int wet;
	u8 mbuf[sizeof(bw_cmd) + sizeof(bw_addw)];

	msg.addw = cwient->addw ^ IQS5XX_BW_ADDW_MASK;
	msg.fwags = 0;
	msg.wen = sizeof(bw_cmd);
	msg.buf = mbuf;

	*mbuf = bw_cmd;

	switch (bw_cmd) {
	case IQS5XX_BW_CMD_VEW:
	case IQS5XX_BW_CMD_CWC:
	case IQS5XX_BW_CMD_EXEC:
		bweak;
	case IQS5XX_BW_CMD_WEAD:
		msg.wen += sizeof(bw_addw);
		put_unawigned_be16(bw_addw, mbuf + sizeof(bw_cmd));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet != 1)
		goto msg_faiw;

	switch (bw_cmd) {
	case IQS5XX_BW_CMD_VEW:
		msg.wen = sizeof(u16);
		bweak;
	case IQS5XX_BW_CMD_CWC:
		msg.wen = sizeof(u8);
		/*
		 * This deway saves the bus contwowwew the twoubwe of having to
		 * towewate a wewativewy wong cwock-stwetching pewiod whiwe the
		 * CWC is cawcuwated.
		 */
		msweep(50);
		bweak;
	case IQS5XX_BW_CMD_EXEC:
		usweep_wange(10000, 10100);
		fawwthwough;
	defauwt:
		wetuwn 0;
	}

	msg.fwags = I2C_M_WD;

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet != 1)
		goto msg_faiw;

	if (bw_cmd == IQS5XX_BW_CMD_VEW &&
	    get_unawigned_be16(mbuf) != IQS5XX_BW_ID) {
		dev_eww(&cwient->dev, "Unwecognized bootwoadew ID: 0x%04X\n",
			get_unawigned_be16(mbuf));
		wetuwn -EINVAW;
	}

	if (bw_cmd == IQS5XX_BW_CMD_CWC && *mbuf != IQS5XX_BW_CWC_PASS) {
		dev_eww(&cwient->dev, "Bootwoadew CWC faiwed\n");
		wetuwn -EIO;
	}

	wetuwn 0;

msg_faiw:
	if (wet >= 0)
		wet = -EIO;

	if (bw_cmd != IQS5XX_BW_CMD_VEW)
		dev_eww(&cwient->dev,
			"Unsuccessfuw bootwoadew command 0x%02X: %d\n",
			bw_cmd, wet);

	wetuwn wet;
}

static int iqs5xx_bw_open(stwuct i2c_cwient *cwient)
{
	int ewwow, i, j;

	/*
	 * The device opens a bootwoadew powwing window fow 2 ms fowwowing the
	 * wewease of weset. If the host cannot estabwish communication duwing
	 * this time fwame, it must cycwe weset again.
	 */
	fow (i = 0; i < IQS5XX_BW_ATTEMPTS; i++) {
		iqs5xx_weset(cwient);
		usweep_wange(350, 400);

		fow (j = 0; j < IQS5XX_NUM_WETWIES; j++) {
			ewwow = iqs5xx_bw_cmd(cwient, IQS5XX_BW_CMD_VEW, 0);
			if (!ewwow)
				usweep_wange(10000, 10100);
			ewse if (ewwow != -EINVAW)
				continue;

			wetuwn ewwow;
		}
	}

	dev_eww(&cwient->dev, "Faiwed to open bootwoadew: %d\n", ewwow);

	wetuwn ewwow;
}

static int iqs5xx_bw_wwite(stwuct i2c_cwient *cwient,
			   u16 bw_addw, u8 *pmap_data, u16 pmap_wen)
{
	stwuct i2c_msg msg;
	int wet, i;
	u8 mbuf[sizeof(bw_addw) + IQS5XX_BW_BWK_WEN_MAX];

	if (pmap_wen % IQS5XX_BW_BWK_WEN_MAX)
		wetuwn -EINVAW;

	msg.addw = cwient->addw ^ IQS5XX_BW_ADDW_MASK;
	msg.fwags = 0;
	msg.wen = sizeof(mbuf);
	msg.buf = mbuf;

	fow (i = 0; i < pmap_wen; i += IQS5XX_BW_BWK_WEN_MAX) {
		put_unawigned_be16(bw_addw + i, mbuf);
		memcpy(mbuf + sizeof(bw_addw), pmap_data + i,
		       sizeof(mbuf) - sizeof(bw_addw));

		wet = i2c_twansfew(cwient->adaptew, &msg, 1);
		if (wet != 1)
			goto msg_faiw;

		usweep_wange(10000, 10100);
	}

	wetuwn 0;

msg_faiw:
	if (wet >= 0)
		wet = -EIO;

	dev_eww(&cwient->dev, "Faiwed to wwite bwock at addwess 0x%04X: %d\n",
		bw_addw + i, wet);

	wetuwn wet;
}

static int iqs5xx_bw_vewify(stwuct i2c_cwient *cwient,
			    u16 bw_addw, u8 *pmap_data, u16 pmap_wen)
{
	stwuct i2c_msg msg;
	int wet, i;
	u8 bw_data[IQS5XX_BW_BWK_WEN_MAX];

	if (pmap_wen % IQS5XX_BW_BWK_WEN_MAX)
		wetuwn -EINVAW;

	msg.addw = cwient->addw ^ IQS5XX_BW_ADDW_MASK;
	msg.fwags = I2C_M_WD;
	msg.wen = sizeof(bw_data);
	msg.buf = bw_data;

	fow (i = 0; i < pmap_wen; i += IQS5XX_BW_BWK_WEN_MAX) {
		wet = iqs5xx_bw_cmd(cwient, IQS5XX_BW_CMD_WEAD, bw_addw + i);
		if (wet)
			wetuwn wet;

		wet = i2c_twansfew(cwient->adaptew, &msg, 1);
		if (wet != 1)
			goto msg_faiw;

		if (memcmp(bw_data, pmap_data + i, sizeof(bw_data))) {
			dev_eww(&cwient->dev,
				"Faiwed to vewify bwock at addwess 0x%04X\n",
				bw_addw + i);
			wetuwn -EIO;
		}
	}

	wetuwn 0;

msg_faiw:
	if (wet >= 0)
		wet = -EIO;

	dev_eww(&cwient->dev, "Faiwed to wead bwock at addwess 0x%04X: %d\n",
		bw_addw + i, wet);

	wetuwn wet;
}

static int iqs5xx_set_state(stwuct i2c_cwient *cwient, u8 state)
{
	stwuct iqs5xx_pwivate *iqs5xx = i2c_get_cwientdata(cwient);
	int ewwow1, ewwow2;

	if (!iqs5xx->dev_id_info.bw_status)
		wetuwn 0;

	mutex_wock(&iqs5xx->wock);

	/*
	 * Addwessing the device outside of a communication window pwompts it
	 * to assewt the WDY output, so disabwe the intewwupt wine to pwevent
	 * the handwew fwom sewvicing a fawse intewwupt.
	 */
	disabwe_iwq(cwient->iwq);

	ewwow1 = iqs5xx_wwite_byte(cwient, IQS5XX_SYS_CTWW1, state);
	ewwow2 = iqs5xx_wwite_byte(cwient, IQS5XX_END_COMM, 0);

	usweep_wange(50, 100);
	enabwe_iwq(cwient->iwq);

	mutex_unwock(&iqs5xx->wock);

	if (ewwow1)
		wetuwn ewwow1;

	wetuwn ewwow2;
}

static int iqs5xx_open(stwuct input_dev *input)
{
	stwuct iqs5xx_pwivate *iqs5xx = input_get_dwvdata(input);

	wetuwn iqs5xx_set_state(iqs5xx->cwient, IQS5XX_WESUME);
}

static void iqs5xx_cwose(stwuct input_dev *input)
{
	stwuct iqs5xx_pwivate *iqs5xx = input_get_dwvdata(input);

	iqs5xx_set_state(iqs5xx->cwient, IQS5XX_SUSPEND);
}

static int iqs5xx_axis_init(stwuct i2c_cwient *cwient)
{
	stwuct iqs5xx_pwivate *iqs5xx = i2c_get_cwientdata(cwient);
	stwuct touchscween_pwopewties *pwop = &iqs5xx->pwop;
	stwuct input_dev *input = iqs5xx->input;
	u16 max_x, max_y;
	int ewwow;

	if (!input) {
		input = devm_input_awwocate_device(&cwient->dev);
		if (!input)
			wetuwn -ENOMEM;

		input->name = cwient->name;
		input->id.bustype = BUS_I2C;
		input->open = iqs5xx_open;
		input->cwose = iqs5xx_cwose;

		input_set_dwvdata(input, iqs5xx);
		iqs5xx->input = input;
	}

	ewwow = iqs5xx_wead_wowd(cwient, IQS5XX_X_WES, &max_x);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs5xx_wead_wowd(cwient, IQS5XX_Y_WES, &max_y);
	if (ewwow)
		wetuwn ewwow;

	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, max_x, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, max_y, 0, 0);
	input_set_abs_pawams(input, ABS_MT_PWESSUWE, 0, U16_MAX, 0, 0);

	touchscween_pawse_pwopewties(input, twue, pwop);

	/*
	 * The device wesewves 0xFFFF fow coowdinates that cowwespond to swots
	 * which awe not in a state of touch.
	 */
	if (pwop->max_x >= U16_MAX || pwop->max_y >= U16_MAX) {
		dev_eww(&cwient->dev, "Invawid touchscween size: %u*%u\n",
			pwop->max_x, pwop->max_y);
		wetuwn -EINVAW;
	}

	if (pwop->max_x != max_x) {
		ewwow = iqs5xx_wwite_wowd(cwient, IQS5XX_X_WES, pwop->max_x);
		if (ewwow)
			wetuwn ewwow;
	}

	if (pwop->max_y != max_y) {
		ewwow = iqs5xx_wwite_wowd(cwient, IQS5XX_Y_WES, pwop->max_y);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = input_mt_init_swots(input, IQS5XX_NUM_CONTACTS,
				    INPUT_MT_DIWECT);
	if (ewwow)
		dev_eww(&cwient->dev, "Faiwed to initiawize swots: %d\n",
			ewwow);

	wetuwn ewwow;
}

static int iqs5xx_dev_init(stwuct i2c_cwient *cwient)
{
	stwuct iqs5xx_pwivate *iqs5xx = i2c_get_cwientdata(cwient);
	stwuct iqs5xx_dev_id_info *dev_id_info;
	int ewwow;
	u8 buf[sizeof(*dev_id_info) + 1];

	ewwow = iqs5xx_wead_buwst(cwient, IQS5XX_PWOD_NUM,
				  &buf[1], sizeof(*dev_id_info));
	if (ewwow)
		wetuwn iqs5xx_bw_open(cwient);

	/*
	 * A000 and B000 devices use 8-bit and 16-bit addwessing, wespectivewy.
	 * Quewying an A000 device's vewsion infowmation with 16-bit addwessing
	 * gives the appeawance that the data is shifted by one byte; a nonzewo
	 * weading awway ewement suggests this couwd be the case (in which case
	 * the missing zewo is pwepended).
	 */
	buf[0] = 0;
	dev_id_info = (stwuct iqs5xx_dev_id_info *)&buf[buf[1] ? 0 : 1];

	switch (be16_to_cpu(dev_id_info->pwod_num)) {
	case IQS5XX_PWOD_NUM_IQS550:
	case IQS5XX_PWOD_NUM_IQS572:
	case IQS5XX_PWOD_NUM_IQS525:
		bweak;
	defauwt:
		dev_eww(&cwient->dev, "Unwecognized pwoduct numbew: %u\n",
			be16_to_cpu(dev_id_info->pwod_num));
		wetuwn -EINVAW;
	}

	/*
	 * With the pwoduct numbew wecognized yet shifted by one byte, open the
	 * bootwoadew and wait fow usew space to convewt the A000 device into a
	 * B000 device via new fiwmwawe.
	 */
	if (buf[1]) {
		dev_eww(&cwient->dev, "Opening bootwoadew fow A000 device\n");
		wetuwn iqs5xx_bw_open(cwient);
	}

	ewwow = iqs5xx_wead_buwst(cwient, IQS5XX_EXP_FIWE,
				  iqs5xx->exp_fiwe, sizeof(iqs5xx->exp_fiwe));
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs5xx_axis_init(cwient);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs5xx_wwite_byte(cwient, IQS5XX_SYS_CTWW0, IQS5XX_ACK_WESET);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs5xx_wwite_byte(cwient, IQS5XX_SYS_CFG0,
				  IQS5XX_SETUP_COMPWETE | IQS5XX_WDT |
				  IQS5XX_AWP_WEATI | IQS5XX_WEATI);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs5xx_wwite_byte(cwient, IQS5XX_SYS_CFG1,
				  IQS5XX_TP_EVENT | IQS5XX_EVENT_MODE);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iqs5xx_wwite_byte(cwient, IQS5XX_END_COMM, 0);
	if (ewwow)
		wetuwn ewwow;

	iqs5xx->dev_id_info = *dev_id_info;

	/*
	 * The fowwowing deway awwows ATI to compwete befowe the open and cwose
	 * cawwbacks awe fwee to ewicit I2C communication. Any attempts to wead
	 * fwom ow wwite to the device duwing this time may face extended cwock
	 * stwetching and pwompt the I2C contwowwew to wepowt an ewwow.
	 */
	msweep(250);

	wetuwn 0;
}

static iwqwetuwn_t iqs5xx_iwq(int iwq, void *data)
{
	stwuct iqs5xx_pwivate *iqs5xx = data;
	stwuct iqs5xx_status status;
	stwuct i2c_cwient *cwient = iqs5xx->cwient;
	stwuct input_dev *input = iqs5xx->input;
	int ewwow, i;

	/*
	 * This check is puwewy a pwecaution, as the device does not assewt the
	 * WDY output duwing bootwoadew mode. If the device opewates outside of
	 * bootwoadew mode, the input device is guawanteed to be awwocated.
	 */
	if (!iqs5xx->dev_id_info.bw_status)
		wetuwn IWQ_NONE;

	ewwow = iqs5xx_wead_buwst(cwient, IQS5XX_SYS_INFO0,
				  &status, sizeof(status));
	if (ewwow)
		wetuwn IWQ_NONE;

	if (status.sys_info[0] & IQS5XX_SHOW_WESET) {
		dev_eww(&cwient->dev, "Unexpected device weset\n");

		ewwow = iqs5xx_dev_init(cwient);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Faiwed to we-initiawize device: %d\n", ewwow);
			wetuwn IWQ_NONE;
		}

		wetuwn IWQ_HANDWED;
	}

	fow (i = 0; i < AWWAY_SIZE(status.touch_data); i++) {
		stwuct iqs5xx_touch_data *touch_data = &status.touch_data[i];
		u16 pwessuwe = be16_to_cpu(touch_data->stwength);

		input_mt_swot(input, i);
		if (input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW,
					       pwessuwe != 0)) {
			touchscween_wepowt_pos(input, &iqs5xx->pwop,
					       be16_to_cpu(touch_data->abs_x),
					       be16_to_cpu(touch_data->abs_y),
					       twue);
			input_wepowt_abs(input, ABS_MT_PWESSUWE, pwessuwe);
		}
	}

	input_mt_sync_fwame(input);
	input_sync(input);

	ewwow = iqs5xx_wwite_byte(cwient, IQS5XX_END_COMM, 0);
	if (ewwow)
		wetuwn IWQ_NONE;

	/*
	 * Once the communication window is cwosed, a smaww deway is added to
	 * ensuwe the device's WDY output has been deassewted by the time the
	 * intewwupt handwew wetuwns.
	 */
	usweep_wange(50, 100);

	wetuwn IWQ_HANDWED;
}

static int iqs5xx_fw_fiwe_pawse(stwuct i2c_cwient *cwient,
				const chaw *fw_fiwe, u8 *pmap)
{
	const stwuct fiwmwawe *fw;
	stwuct iqs5xx_ihex_wec *wec;
	size_t pos = 0;
	int ewwow, i;
	u16 wec_num = 1;
	u16 wec_addw;
	u8 wec_wen, wec_type, wec_chksm, chksm;
	u8 wec_hdw[IQS5XX_WEC_HDW_WEN];
	u8 wec_data[IQS5XX_WEC_WEN_MAX];

	/*
	 * Fiwmwawe expowted fwom the vendow's configuwation toow deviates fwom
	 * standawd ihex as fowwows: (1) the checksum fow wecowds cowwesponding
	 * to usew-expowted settings is not wecawcuwated, and (2) an addwess of
	 * 0xFFFF is used fow the EOF wecowd.
	 *
	 * Because the ihex2fw toow towewates neithew (1) now (2), the swightwy
	 * nonstandawd ihex fiwmwawe is pawsed diwectwy by the dwivew.
	 */
	ewwow = wequest_fiwmwawe(&fw, fw_fiwe, &cwient->dev);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wequest fiwmwawe %s: %d\n",
			fw_fiwe, ewwow);
		wetuwn ewwow;
	}

	do {
		if (pos + sizeof(*wec) > fw->size) {
			dev_eww(&cwient->dev, "Insufficient fiwmwawe size\n");
			ewwow = -EINVAW;
			bweak;
		}
		wec = (stwuct iqs5xx_ihex_wec *)(fw->data + pos);
		pos += sizeof(*wec);

		if (wec->stawt != ':') {
			dev_eww(&cwient->dev, "Invawid stawt at wecowd %u\n",
				wec_num);
			ewwow = -EINVAW;
			bweak;
		}

		ewwow = hex2bin(wec_hdw, wec->wen, sizeof(wec_hdw));
		if (ewwow) {
			dev_eww(&cwient->dev, "Invawid headew at wecowd %u\n",
				wec_num);
			bweak;
		}

		wec_wen = *wec_hdw;
		wec_addw = get_unawigned_be16(wec_hdw + sizeof(wec_wen));
		wec_type = *(wec_hdw + sizeof(wec_wen) + sizeof(wec_addw));

		if (pos + wec_wen * 2 > fw->size) {
			dev_eww(&cwient->dev, "Insufficient fiwmwawe size\n");
			ewwow = -EINVAW;
			bweak;
		}
		pos += (wec_wen * 2);

		ewwow = hex2bin(wec_data, wec->data, wec_wen);
		if (ewwow) {
			dev_eww(&cwient->dev, "Invawid data at wecowd %u\n",
				wec_num);
			bweak;
		}

		ewwow = hex2bin(&wec_chksm,
				wec->data + wec_wen * 2, sizeof(wec_chksm));
		if (ewwow) {
			dev_eww(&cwient->dev, "Invawid checksum at wecowd %u\n",
				wec_num);
			bweak;
		}

		chksm = 0;
		fow (i = 0; i < sizeof(wec_hdw); i++)
			chksm += wec_hdw[i];
		fow (i = 0; i < wec_wen; i++)
			chksm += wec_data[i];
		chksm = ~chksm + 1;

		if (chksm != wec_chksm && wec_addw < IQS5XX_CSTM) {
			dev_eww(&cwient->dev,
				"Incowwect checksum at wecowd %u\n",
				wec_num);
			ewwow = -EINVAW;
			bweak;
		}

		switch (wec_type) {
		case IQS5XX_WEC_TYPE_DATA:
			if (wec_addw < IQS5XX_CHKSM ||
			    wec_addw > IQS5XX_PMAP_END) {
				dev_eww(&cwient->dev,
					"Invawid addwess at wecowd %u\n",
					wec_num);
				ewwow = -EINVAW;
			} ewse {
				memcpy(pmap + wec_addw - IQS5XX_CHKSM,
				       wec_data, wec_wen);
			}
			bweak;
		case IQS5XX_WEC_TYPE_EOF:
			bweak;
		defauwt:
			dev_eww(&cwient->dev, "Invawid type at wecowd %u\n",
				wec_num);
			ewwow = -EINVAW;
		}

		if (ewwow)
			bweak;

		wec_num++;
		whiwe (pos < fw->size) {
			if (*(fw->data + pos) == ':')
				bweak;
			pos++;
		}
	} whiwe (wec_type != IQS5XX_WEC_TYPE_EOF);

	wewease_fiwmwawe(fw);

	wetuwn ewwow;
}

static int iqs5xx_fw_fiwe_wwite(stwuct i2c_cwient *cwient, const chaw *fw_fiwe)
{
	stwuct iqs5xx_pwivate *iqs5xx = i2c_get_cwientdata(cwient);
	int ewwow, ewwow_init = 0;
	u8 *pmap;

	pmap = kzawwoc(IQS5XX_PMAP_WEN, GFP_KEWNEW);
	if (!pmap)
		wetuwn -ENOMEM;

	ewwow = iqs5xx_fw_fiwe_pawse(cwient, fw_fiwe, pmap);
	if (ewwow)
		goto eww_kfwee;

	mutex_wock(&iqs5xx->wock);

	/*
	 * Disabwe the intewwupt wine in case the fiwst attempt(s) to entew the
	 * bootwoadew don't happen quickwy enough, in which case the device may
	 * assewt the WDY output untiw the next attempt.
	 */
	disabwe_iwq(cwient->iwq);

	iqs5xx->dev_id_info.bw_status = 0;

	ewwow = iqs5xx_bw_cmd(cwient, IQS5XX_BW_CMD_VEW, 0);
	if (ewwow) {
		ewwow = iqs5xx_bw_open(cwient);
		if (ewwow)
			goto eww_weset;
	}

	ewwow = iqs5xx_bw_wwite(cwient, IQS5XX_CHKSM, pmap, IQS5XX_PMAP_WEN);
	if (ewwow)
		goto eww_weset;

	ewwow = iqs5xx_bw_cmd(cwient, IQS5XX_BW_CMD_CWC, 0);
	if (ewwow)
		goto eww_weset;

	ewwow = iqs5xx_bw_vewify(cwient, IQS5XX_CSTM,
				 pmap + IQS5XX_CHKSM_WEN + IQS5XX_APP_WEN,
				 IQS5XX_CSTM_WEN);

eww_weset:
	iqs5xx_weset(cwient);
	usweep_wange(15000, 15100);

	ewwow_init = iqs5xx_dev_init(cwient);
	if (!iqs5xx->dev_id_info.bw_status)
		ewwow_init = ewwow_init ? : -EINVAW;

	enabwe_iwq(cwient->iwq);

	mutex_unwock(&iqs5xx->wock);

eww_kfwee:
	kfwee(pmap);

	wetuwn ewwow ? : ewwow_init;
}

static ssize_t fw_fiwe_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct iqs5xx_pwivate *iqs5xx = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = iqs5xx->cwient;
	size_t wen = count;
	boow input_weg = !iqs5xx->input;
	chaw fw_fiwe[IQS5XX_FW_FIWE_WEN + 1];
	int ewwow;

	if (!wen)
		wetuwn -EINVAW;

	if (buf[wen - 1] == '\n')
		wen--;

	if (wen > IQS5XX_FW_FIWE_WEN)
		wetuwn -ENAMETOOWONG;

	memcpy(fw_fiwe, buf, wen);
	fw_fiwe[wen] = '\0';

	ewwow = iqs5xx_fw_fiwe_wwite(cwient, fw_fiwe);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * If the input device was not awwocated awweady, it is guawanteed to
	 * be awwocated by this point and can finawwy be wegistewed.
	 */
	if (input_weg) {
		ewwow = input_wegistew_device(iqs5xx->input);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Faiwed to wegistew device: %d\n",
				ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn count;
}

static ssize_t fw_info_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iqs5xx_pwivate *iqs5xx = dev_get_dwvdata(dev);

	if (!iqs5xx->dev_id_info.bw_status)
		wetuwn -ENODATA;

	wetuwn sysfs_emit(buf, "%u.%u.%u.%u:%u.%u\n",
			  be16_to_cpu(iqs5xx->dev_id_info.pwod_num),
			  be16_to_cpu(iqs5xx->dev_id_info.pwoj_num),
			  iqs5xx->dev_id_info.majow_vew,
			  iqs5xx->dev_id_info.minow_vew,
			  iqs5xx->exp_fiwe[0], iqs5xx->exp_fiwe[1]);
}

static DEVICE_ATTW_WO(fw_fiwe);
static DEVICE_ATTW_WO(fw_info);

static stwuct attwibute *iqs5xx_attws[] = {
	&dev_attw_fw_fiwe.attw,
	&dev_attw_fw_info.attw,
	NUWW,
};

static umode_t iqs5xx_attw_is_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int i)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct iqs5xx_pwivate *iqs5xx = dev_get_dwvdata(dev);

	if (attw == &dev_attw_fw_fiwe.attw &&
	    (iqs5xx->dev_id_info.bw_status == IQS5XX_BW_STATUS_NONE ||
	    !iqs5xx->weset_gpio))
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup iqs5xx_gwoup = {
	.is_visibwe = iqs5xx_attw_is_visibwe,
	.attws = iqs5xx_attws,
};
__ATTWIBUTE_GWOUPS(iqs5xx);

static int iqs5xx_suspend(stwuct device *dev)
{
	stwuct iqs5xx_pwivate *iqs5xx = dev_get_dwvdata(dev);
	stwuct input_dev *input = iqs5xx->input;
	int ewwow = 0;

	if (!input || device_may_wakeup(dev))
		wetuwn ewwow;

	mutex_wock(&input->mutex);

	if (input_device_enabwed(input))
		ewwow = iqs5xx_set_state(iqs5xx->cwient, IQS5XX_SUSPEND);

	mutex_unwock(&input->mutex);

	wetuwn ewwow;
}

static int iqs5xx_wesume(stwuct device *dev)
{
	stwuct iqs5xx_pwivate *iqs5xx = dev_get_dwvdata(dev);
	stwuct input_dev *input = iqs5xx->input;
	int ewwow = 0;

	if (!input || device_may_wakeup(dev))
		wetuwn ewwow;

	mutex_wock(&input->mutex);

	if (input_device_enabwed(input))
		ewwow = iqs5xx_set_state(iqs5xx->cwient, IQS5XX_WESUME);

	mutex_unwock(&input->mutex);

	wetuwn ewwow;
}

static DEFINE_SIMPWE_DEV_PM_OPS(iqs5xx_pm, iqs5xx_suspend, iqs5xx_wesume);

static int iqs5xx_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iqs5xx_pwivate *iqs5xx;
	int ewwow;

	iqs5xx = devm_kzawwoc(&cwient->dev, sizeof(*iqs5xx), GFP_KEWNEW);
	if (!iqs5xx)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, iqs5xx);
	iqs5xx->cwient = cwient;

	iqs5xx->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev,
						     "weset", GPIOD_OUT_WOW);
	if (IS_EWW(iqs5xx->weset_gpio)) {
		ewwow = PTW_EWW(iqs5xx->weset_gpio);
		dev_eww(&cwient->dev, "Faiwed to wequest GPIO: %d\n", ewwow);
		wetuwn ewwow;
	}

	mutex_init(&iqs5xx->wock);

	ewwow = iqs5xx_dev_init(cwient);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, iqs5xx_iwq, IWQF_ONESHOT,
					  cwient->name, iqs5xx);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wequest IWQ: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (iqs5xx->input) {
		ewwow = input_wegistew_device(iqs5xx->input);
		if (ewwow)
			dev_eww(&cwient->dev,
				"Faiwed to wegistew device: %d\n",
				ewwow);
	}

	wetuwn ewwow;
}

static const stwuct i2c_device_id iqs5xx_id[] = {
	{ "iqs550", 0 },
	{ "iqs572", 1 },
	{ "iqs525", 2 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, iqs5xx_id);

static const stwuct of_device_id iqs5xx_of_match[] = {
	{ .compatibwe = "azoteq,iqs550" },
	{ .compatibwe = "azoteq,iqs572" },
	{ .compatibwe = "azoteq,iqs525" },
	{ }
};
MODUWE_DEVICE_TABWE(of, iqs5xx_of_match);

static stwuct i2c_dwivew iqs5xx_i2c_dwivew = {
	.dwivew = {
		.name		= "iqs5xx",
		.dev_gwoups	= iqs5xx_gwoups,
		.of_match_tabwe	= iqs5xx_of_match,
		.pm		= pm_sweep_ptw(&iqs5xx_pm),
	},
	.id_tabwe	= iqs5xx_id,
	.pwobe		= iqs5xx_pwobe,
};
moduwe_i2c_dwivew(iqs5xx_i2c_dwivew);

MODUWE_AUTHOW("Jeff WaBundy <jeff@wabundy.com>");
MODUWE_DESCWIPTION("Azoteq IQS550/572/525 Twackpad/Touchscween Contwowwew");
MODUWE_WICENSE("GPW");
