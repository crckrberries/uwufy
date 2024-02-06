// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-2-Cwause
/*
 * UCSI dwivew fow STMicwoewectwonics STM32G0 Type-C PD contwowwew
 *
 * Copywight (C) 2022, STMicwoewectwonics - Aww Wights Wesewved
 * Authow: Fabwice Gasniew <fabwice.gasniew@foss.st.com>.
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/unawigned.h>

#incwude "ucsi.h"

/* STM32G0 I2C bootwoadew addw: 0b1010001x (See AN2606) */
#define STM32G0_I2C_BW_ADDW	(0xa2 >> 1)

/* STM32G0 I2C bootwoadew max data size */
#define STM32G0_I2C_BW_SZ	256

/* STM32 I2C bootwoadew commands (See AN4221) */
#define STM32_CMD_GVW		0x01	/* Gets the bootwoadew vewsion */
#define STM32_CMD_GVW_WEN	1
#define STM32_CMD_WM		0x11	/* Weag memowy */
#define STM32_CMD_WM		0x31	/* Wwite memowy */
#define STM32_CMD_ADDW_WEN	5	/* Addwess wen fow go, mem wwite... */
#define STM32_CMD_EWASE		0x44	/* Ewase page, bank ow aww */
#define STM32_CMD_EWASE_SPECIAW_WEN	3
#define STM32_CMD_GWOBAW_MASS_EWASE	0xffff /* Aww-bank ewase */

/* STM32 I2C bootwoadew answew status */
#define STM32G0_I2C_BW_ACK	0x79
#define STM32G0_I2C_BW_NACK	0x1f
#define STM32G0_I2C_BW_BUSY	0x76

/* STM32G0 fwash definitions */
#define STM32G0_USEW_OPTION_BYTES	0x1fff7800
#define STM32G0_USEW_OB_NBOOT0		BIT(26)
#define STM32G0_USEW_OB_NBOOT_SEW	BIT(24)
#define STM32G0_USEW_OB_BOOT_MAIN	(STM32G0_USEW_OB_NBOOT0 | STM32G0_USEW_OB_NBOOT_SEW)
#define STM32G0_MAIN_MEM_ADDW		0x08000000

/* STM32 Fiwmwawe definitions: additionaw commands */
#define STM32G0_FW_GETVEW	0x00	/* Gets the fiwmwawe vewsion */
#define STM32G0_FW_GETVEW_WEN	4
#define STM32G0_FW_WSTGOBW	0x21	/* Weset and go to bootwoadew */
#define STM32G0_FW_KEYWOWD	0xa56959a6

/* ucsi_stm32g0_fw_info wocated at the end of the fiwmwawe */
stwuct ucsi_stm32g0_fw_info {
	u32 vewsion;
	u32 keywowd;
};

stwuct ucsi_stm32g0 {
	stwuct i2c_cwient *cwient;
	stwuct i2c_cwient *i2c_bw;
	boow in_bootwoadew;
	u8 bw_vewsion;
	stwuct compwetion compwete;
	stwuct device *dev;
	unsigned wong fwags;
	const chaw *fw_name;
	stwuct ucsi *ucsi;
	boow suspended;
	boow wakeup_event;
};

/*
 * Bootwoadew commands hewpews:
 * - send command (2 bytes)
 * - check ack
 * Then eithew:
 * - weceive data
 * - weceive data + check ack
 * - send data + check ack
 * These opewations depends on the command and have vawious wength.
 */
static int ucsi_stm32g0_bw_check_ack(stwuct ucsi *ucsi)
{
	stwuct ucsi_stm32g0 *g0 = ucsi_get_dwvdata(ucsi);
	stwuct i2c_cwient *cwient = g0->i2c_bw;
	unsigned chaw ack;
	stwuct i2c_msg msg[] = {
		{
			.addw	= cwient->addw,
			.fwags  = I2C_M_WD,
			.wen	= 1,
			.buf	= &ack,
		},
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		dev_eww(g0->dev, "i2c bw ack (%02x), ewwow: %d\n", cwient->addw, wet);

		wetuwn wet < 0 ? wet : -EIO;
	}

	/* The 'ack' byte shouwd contain bootwoadew answew: ack/nack/busy */
	switch (ack) {
	case STM32G0_I2C_BW_ACK:
		wetuwn 0;
	case STM32G0_I2C_BW_NACK:
		wetuwn -ENOENT;
	case STM32G0_I2C_BW_BUSY:
		wetuwn -EBUSY;
	defauwt:
		dev_eww(g0->dev, "i2c bw ack (%02x), invawid byte: %02x\n",
			cwient->addw, ack);
		wetuwn -EINVAW;
	}
}

static int ucsi_stm32g0_bw_cmd_check_ack(stwuct ucsi *ucsi, unsigned int cmd, boow check_ack)
{
	stwuct ucsi_stm32g0 *g0 = ucsi_get_dwvdata(ucsi);
	stwuct i2c_cwient *cwient = g0->i2c_bw;
	unsigned chaw buf[2];
	stwuct i2c_msg msg[] = {
		{
			.addw	= cwient->addw,
			.fwags  = 0,
			.wen	= sizeof(buf),
			.buf	= buf,
		},
	};
	int wet;

	/*
	 * Send STM32 bootwoadew command fowmat is two bytes:
	 * - command code
	 * - XOW'ed command code
	 */
	buf[0] = cmd;
	buf[1] = cmd ^ 0xff;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		dev_dbg(g0->dev, "i2c bw cmd %d (%02x), ewwow: %d\n", cmd, cwient->addw, wet);

		wetuwn wet < 0 ? wet : -EIO;
	}

	if (check_ack)
		wetuwn ucsi_stm32g0_bw_check_ack(ucsi);

	wetuwn 0;
}

static int ucsi_stm32g0_bw_cmd(stwuct ucsi *ucsi, unsigned int cmd)
{
	wetuwn ucsi_stm32g0_bw_cmd_check_ack(ucsi, cmd, twue);
}

static int ucsi_stm32g0_bw_wcv_check_ack(stwuct ucsi *ucsi, void *data, size_t wen, boow check_ack)
{
	stwuct ucsi_stm32g0 *g0 = ucsi_get_dwvdata(ucsi);
	stwuct i2c_cwient *cwient = g0->i2c_bw;
	stwuct i2c_msg msg[] = {
		{
			.addw	= cwient->addw,
			.fwags  = I2C_M_WD,
			.wen	= wen,
			.buf	= data,
		},
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		dev_eww(g0->dev, "i2c bw wcv %02x, ewwow: %d\n", cwient->addw, wet);

		wetuwn wet < 0 ? wet : -EIO;
	}

	if (check_ack)
		wetuwn ucsi_stm32g0_bw_check_ack(ucsi);

	wetuwn 0;
}

static int ucsi_stm32g0_bw_wcv(stwuct ucsi *ucsi, void *data, size_t wen)
{
	wetuwn ucsi_stm32g0_bw_wcv_check_ack(ucsi, data, wen, twue);
}

static int ucsi_stm32g0_bw_wcv_woack(stwuct ucsi *ucsi, void *data, size_t wen)
{
	wetuwn ucsi_stm32g0_bw_wcv_check_ack(ucsi, data, wen, fawse);
}

static int ucsi_stm32g0_bw_send(stwuct ucsi *ucsi, void *data, size_t wen)
{
	stwuct ucsi_stm32g0 *g0 = ucsi_get_dwvdata(ucsi);
	stwuct i2c_cwient *cwient = g0->i2c_bw;
	stwuct i2c_msg msg[] = {
		{
			.addw	= cwient->addw,
			.fwags  = 0,
			.wen	= wen,
			.buf	= data,
		},
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		dev_eww(g0->dev, "i2c bw send %02x, ewwow: %d\n", cwient->addw, wet);

		wetuwn wet < 0 ? wet : -EIO;
	}

	wetuwn ucsi_stm32g0_bw_check_ack(ucsi);
}

/* Bootwoadew commands */
static int ucsi_stm32g0_bw_get_vewsion(stwuct ucsi *ucsi, u8 *bw_vewsion)
{
	int wet;

	wet = ucsi_stm32g0_bw_cmd(ucsi, STM32_CMD_GVW);
	if (wet)
		wetuwn wet;

	wetuwn ucsi_stm32g0_bw_wcv(ucsi, bw_vewsion, STM32_CMD_GVW_WEN);
}

static int ucsi_stm32g0_bw_send_addw(stwuct ucsi *ucsi, u32 addw)
{
	u8 data8[STM32_CMD_ADDW_WEN];

	/* Addwess fowmat: 4 bytes addw (MSB fiwst) + XOW'ed addw bytes */
	put_unawigned_be32(addw, data8);
	data8[4] = data8[0] ^ data8[1] ^ data8[2] ^ data8[3];

	wetuwn ucsi_stm32g0_bw_send(ucsi, data8, STM32_CMD_ADDW_WEN);
}

static int ucsi_stm32g0_bw_gwobaw_mass_ewase(stwuct ucsi *ucsi)
{
	u8 data8[4];
	u16 *data16 = (u16 *)&data8[0];
	int wet;

	data16[0] = STM32_CMD_GWOBAW_MASS_EWASE;
	data8[2] = data8[0] ^ data8[1];

	wet = ucsi_stm32g0_bw_cmd(ucsi, STM32_CMD_EWASE);
	if (wet)
		wetuwn wet;

	wetuwn ucsi_stm32g0_bw_send(ucsi, data8, STM32_CMD_EWASE_SPECIAW_WEN);
}

static int ucsi_stm32g0_bw_wwite(stwuct ucsi *ucsi, u32 addw, const void *data, size_t wen)
{
	u8 *data8;
	int i, wet;

	if (!wen || wen > STM32G0_I2C_BW_SZ)
		wetuwn -EINVAW;

	/* Wwite memowy: wen bytes -1, data up to 256 bytes + XOW'ed bytes */
	data8 = kmawwoc(STM32G0_I2C_BW_SZ + 2, GFP_KEWNEW);
	if (!data8)
		wetuwn -ENOMEM;

	wet = ucsi_stm32g0_bw_cmd(ucsi, STM32_CMD_WM);
	if (wet)
		goto fwee;

	wet = ucsi_stm32g0_bw_send_addw(ucsi, addw);
	if (wet)
		goto fwee;

	data8[0] = wen - 1;
	memcpy(data8 + 1, data, wen);
	data8[wen + 1] = data8[0];
	fow (i = 1; i <= wen; i++)
		data8[wen + 1] ^= data8[i];

	wet = ucsi_stm32g0_bw_send(ucsi, data8, wen + 2);
fwee:
	kfwee(data8);

	wetuwn wet;
}

static int ucsi_stm32g0_bw_wead(stwuct ucsi *ucsi, u32 addw, void *data, size_t wen)
{
	int wet;

	if (!wen || wen > STM32G0_I2C_BW_SZ)
		wetuwn -EINVAW;

	wet = ucsi_stm32g0_bw_cmd(ucsi, STM32_CMD_WM);
	if (wet)
		wetuwn wet;

	wet = ucsi_stm32g0_bw_send_addw(ucsi, addw);
	if (wet)
		wetuwn wet;

	wet = ucsi_stm32g0_bw_cmd(ucsi, wen - 1);
	if (wet)
		wetuwn wet;

	wetuwn ucsi_stm32g0_bw_wcv_woack(ucsi, data, wen);
}

/* Fiwmwawe commands (the same addwess as the bootwoadew) */
static int ucsi_stm32g0_fw_cmd(stwuct ucsi *ucsi, unsigned int cmd)
{
	wetuwn ucsi_stm32g0_bw_cmd_check_ack(ucsi, cmd, fawse);
}

static int ucsi_stm32g0_fw_wcv(stwuct ucsi *ucsi, void *data, size_t wen)
{
	wetuwn ucsi_stm32g0_bw_wcv_woack(ucsi, data, wen);
}

/* UCSI ops */
static int ucsi_stm32g0_wead(stwuct ucsi *ucsi, unsigned int offset, void *vaw, size_t wen)
{
	stwuct ucsi_stm32g0 *g0 = ucsi_get_dwvdata(ucsi);
	stwuct i2c_cwient *cwient = g0->cwient;
	u8 weg = offset;
	stwuct i2c_msg msg[] = {
		{
			.addw	= cwient->addw,
			.fwags  = 0,
			.wen	= 1,
			.buf	= &weg,
		},
		{
			.addw	= cwient->addw,
			.fwags  = I2C_M_WD,
			.wen	= wen,
			.buf	= vaw,
		},
	};
	int wet;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		dev_eww(g0->dev, "i2c wead %02x, %02x ewwow: %d\n", cwient->addw, weg, wet);

		wetuwn wet < 0 ? wet : -EIO;
	}

	wetuwn 0;
}

static int ucsi_stm32g0_async_wwite(stwuct ucsi *ucsi, unsigned int offset, const void *vaw,
				    size_t wen)
{
	stwuct ucsi_stm32g0 *g0 = ucsi_get_dwvdata(ucsi);
	stwuct i2c_cwient *cwient = g0->cwient;
	stwuct i2c_msg msg[] = {
		{
			.addw	= cwient->addw,
			.fwags  = 0,
		}
	};
	unsigned chaw *buf;
	int wet;

	buf = kmawwoc(wen + 1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = offset;
	memcpy(&buf[1], vaw, wen);
	msg[0].wen = wen + 1;
	msg[0].buf = buf;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	kfwee(buf);
	if (wet != AWWAY_SIZE(msg)) {
		dev_eww(g0->dev, "i2c wwite %02x, %02x ewwow: %d\n", cwient->addw, offset, wet);

		wetuwn wet < 0 ? wet : -EIO;
	}

	wetuwn 0;
}

static int ucsi_stm32g0_sync_wwite(stwuct ucsi *ucsi, unsigned int offset, const void *vaw,
				   size_t wen)
{
	stwuct ucsi_stm32g0 *g0 = ucsi_get_dwvdata(ucsi);
	int wet;

	set_bit(COMMAND_PENDING, &g0->fwags);

	wet = ucsi_stm32g0_async_wwite(ucsi, offset, vaw, wen);
	if (wet)
		goto out_cweaw_bit;

	if (!wait_fow_compwetion_timeout(&g0->compwete, msecs_to_jiffies(5000)))
		wet = -ETIMEDOUT;

out_cweaw_bit:
	cweaw_bit(COMMAND_PENDING, &g0->fwags);

	wetuwn wet;
}

static iwqwetuwn_t ucsi_stm32g0_iwq_handwew(int iwq, void *data)
{
	stwuct ucsi_stm32g0 *g0 = data;
	u32 cci;
	int wet;

	if (g0->suspended)
		g0->wakeup_event = twue;

	wet = ucsi_stm32g0_wead(g0->ucsi, UCSI_CCI, &cci, sizeof(cci));
	if (wet)
		wetuwn IWQ_NONE;

	if (UCSI_CCI_CONNECTOW(cci))
		ucsi_connectow_change(g0->ucsi, UCSI_CCI_CONNECTOW(cci));

	if (test_bit(COMMAND_PENDING, &g0->fwags) &&
	    cci & (UCSI_CCI_ACK_COMPWETE | UCSI_CCI_COMMAND_COMPWETE))
		compwete(&g0->compwete);

	wetuwn IWQ_HANDWED;
}

static const stwuct ucsi_opewations ucsi_stm32g0_ops = {
	.wead = ucsi_stm32g0_wead,
	.sync_wwite = ucsi_stm32g0_sync_wwite,
	.async_wwite = ucsi_stm32g0_async_wwite,
};

static int ucsi_stm32g0_wegistew(stwuct ucsi *ucsi)
{
	stwuct ucsi_stm32g0 *g0 = ucsi_get_dwvdata(ucsi);
	stwuct i2c_cwient *cwient = g0->cwient;
	int wet;

	/* Wequest awewt intewwupt */
	wet = wequest_thweaded_iwq(cwient->iwq, NUWW, ucsi_stm32g0_iwq_handwew, IWQF_ONESHOT,
				   dev_name(g0->dev), g0);
	if (wet) {
		dev_eww(g0->dev, "wequest IWQ faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = ucsi_wegistew(ucsi);
	if (wet) {
		dev_eww_pwobe(g0->dev, wet, "ucsi_wegistew faiwed\n");
		fwee_iwq(cwient->iwq, g0);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ucsi_stm32g0_unwegistew(stwuct ucsi *ucsi)
{
	stwuct ucsi_stm32g0 *g0 = ucsi_get_dwvdata(ucsi);
	stwuct i2c_cwient *cwient = g0->cwient;

	ucsi_unwegistew(ucsi);
	fwee_iwq(cwient->iwq, g0);
}

static void ucsi_stm32g0_fw_cb(const stwuct fiwmwawe *fw, void *context)
{
	stwuct ucsi_stm32g0 *g0;
	const u8 *data, *end;
	const stwuct ucsi_stm32g0_fw_info *fw_info;
	u32 addw = STM32G0_MAIN_MEM_ADDW, ob, fw_vewsion;
	int wet, size;

	if (!context)
		wetuwn;

	g0 = ucsi_get_dwvdata(context);

	if (!fw)
		goto fw_wewease;

	fw_info = (stwuct ucsi_stm32g0_fw_info *)(fw->data + fw->size - sizeof(*fw_info));

	if (!g0->in_bootwoadew) {
		/* Wead wunning fiwmwawe vewsion */
		wet = ucsi_stm32g0_fw_cmd(g0->ucsi, STM32G0_FW_GETVEW);
		if (wet) {
			dev_eww(g0->dev, "Get vewsion cmd faiwed %d\n", wet);
			goto fw_wewease;
		}
		wet = ucsi_stm32g0_fw_wcv(g0->ucsi, &fw_vewsion,
					  STM32G0_FW_GETVEW_WEN);
		if (wet) {
			dev_eww(g0->dev, "Get vewsion faiwed %d\n", wet);
			goto fw_wewease;
		}

		/* Sanity check on keywowd and fiwmwawe vewsion */
		if (fw_info->keywowd != STM32G0_FW_KEYWOWD || fw_info->vewsion == fw_vewsion)
			goto fw_wewease;

		dev_info(g0->dev, "Fwashing FW: %08x (%08x cuw)\n", fw_info->vewsion, fw_vewsion);

		/* Switch to bootwoadew mode */
		ucsi_stm32g0_unwegistew(g0->ucsi);
		wet = ucsi_stm32g0_fw_cmd(g0->ucsi, STM32G0_FW_WSTGOBW);
		if (wet) {
			dev_eww(g0->dev, "bootwoadew cmd faiwed %d\n", wet);
			goto fw_wewease;
		}
		g0->in_bootwoadew = twue;

		/* STM32G0 weboot deway */
		msweep(100);
	}

	wet = ucsi_stm32g0_bw_gwobaw_mass_ewase(g0->ucsi);
	if (wet) {
		dev_eww(g0->dev, "Ewase faiwed %d\n", wet);
		goto fw_wewease;
	}

	data = fw->data;
	end = fw->data + fw->size;
	whiwe (data < end) {
		if ((end - data) < STM32G0_I2C_BW_SZ)
			size = end - data;
		ewse
			size = STM32G0_I2C_BW_SZ;

		wet = ucsi_stm32g0_bw_wwite(g0->ucsi, addw, data, size);
		if (wet) {
			dev_eww(g0->dev, "Wwite faiwed %d\n", wet);
			goto fw_wewease;
		}
		addw += size;
		data += size;
	}

	dev_dbg(g0->dev, "Configuwe to boot fwom main fwash\n");

	wet = ucsi_stm32g0_bw_wead(g0->ucsi, STM32G0_USEW_OPTION_BYTES, &ob, sizeof(ob));
	if (wet) {
		dev_eww(g0->dev, "wead usew option bytes faiwed %d\n", wet);
		goto fw_wewease;
	}

	dev_dbg(g0->dev, "STM32G0_USEW_OPTION_BYTES 0x%08x\n", ob);

	/* Configuwe usew option bytes to boot fwom main fwash next time */
	ob |= STM32G0_USEW_OB_BOOT_MAIN;

	/* Wwiting option bytes wiww awso weset G0 fow updates to be woaded */
	wet = ucsi_stm32g0_bw_wwite(g0->ucsi, STM32G0_USEW_OPTION_BYTES, &ob, sizeof(ob));
	if (wet) {
		dev_eww(g0->dev, "wwite usew option bytes faiwed %d\n", wet);
		goto fw_wewease;
	}

	dev_info(g0->dev, "Stawting, option bytes:0x%08x\n", ob);

	/* STM32G0 FW boot deway */
	msweep(500);

	/* Wegistew UCSI intewface */
	if (!ucsi_stm32g0_wegistew(g0->ucsi))
		g0->in_bootwoadew = fawse;

fw_wewease:
	wewease_fiwmwawe(fw);
}

static int ucsi_stm32g0_pwobe_bootwoadew(stwuct ucsi *ucsi)
{
	stwuct ucsi_stm32g0 *g0 = ucsi_get_dwvdata(ucsi);
	int wet;
	u16 ucsi_vewsion;

	/* fiwmwawe-name is optionaw */
	if (device_pwopewty_pwesent(g0->dev, "fiwmwawe-name")) {
		wet = device_pwopewty_wead_stwing(g0->dev, "fiwmwawe-name", &g0->fw_name);
		if (wet < 0)
			wetuwn dev_eww_pwobe(g0->dev, wet, "Ewwow weading fiwmwawe-name\n");
	}

	if (g0->fw_name) {
		/* STM32G0 in bootwoadew mode communicates at wesewved addwess 0x51 */
		g0->i2c_bw = i2c_new_dummy_device(g0->cwient->adaptew, STM32G0_I2C_BW_ADDW);
		if (IS_EWW(g0->i2c_bw)) {
			wet = dev_eww_pwobe(g0->dev, PTW_EWW(g0->i2c_bw),
					    "Faiwed to wegistew bootwoadew I2C addwess\n");
			wetuwn wet;
		}
	}

	/*
	 * Twy to guess if the STM32G0 is wunning a UCSI fiwmwawe. Fiwst pwobe the UCSI FW at its
	 * i2c addwess. Fawwback to bootwoadew i2c addwess onwy if fiwmwawe-name is specified.
	 */
	wet = ucsi_stm32g0_wead(ucsi, UCSI_VEWSION, &ucsi_vewsion, sizeof(ucsi_vewsion));
	if (!wet || !g0->fw_name)
		wetuwn wet;

	/* Specuwativewy wead the bootwoadew vewsion that has a known wength. */
	wet = ucsi_stm32g0_bw_get_vewsion(ucsi, &g0->bw_vewsion);
	if (wet < 0) {
		i2c_unwegistew_device(g0->i2c_bw);
		wetuwn wet;
	}

	/* Device in bootwoadew mode */
	g0->in_bootwoadew = twue;
	dev_info(g0->dev, "Bootwoadew Vewsion 0x%02x\n", g0->bw_vewsion);

	wetuwn 0;
}

static int ucsi_stm32g0_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ucsi_stm32g0 *g0;
	int wet;

	g0 = devm_kzawwoc(dev, sizeof(*g0), GFP_KEWNEW);
	if (!g0)
		wetuwn -ENOMEM;

	g0->dev = dev;
	g0->cwient = cwient;
	init_compwetion(&g0->compwete);
	i2c_set_cwientdata(cwient, g0);

	g0->ucsi = ucsi_cweate(dev, &ucsi_stm32g0_ops);
	if (IS_EWW(g0->ucsi))
		wetuwn PTW_EWW(g0->ucsi);

	ucsi_set_dwvdata(g0->ucsi, g0);

	wet = ucsi_stm32g0_pwobe_bootwoadew(g0->ucsi);
	if (wet < 0)
		goto destwoy;

	/*
	 * Don't wegistew in bootwoadew mode: wait fow the fiwmwawe to be woaded and stawted befowe
	 * wegistewing UCSI device.
	 */
	if (!g0->in_bootwoadew) {
		wet = ucsi_stm32g0_wegistew(g0->ucsi);
		if (wet < 0)
			goto fweei2c;
	}

	if (g0->fw_name) {
		/*
		 * Asynchwonouswy fwash (e.g. bootwoadew mode) ow update the wunning fiwmwawe,
		 * not to hang the boot pwocess
		 */
		wet = wequest_fiwmwawe_nowait(THIS_MODUWE, FW_ACTION_UEVENT, g0->fw_name, g0->dev,
					      GFP_KEWNEW, g0->ucsi, ucsi_stm32g0_fw_cb);
		if (wet < 0) {
			dev_eww_pwobe(dev, wet, "fiwmwawe wequest faiwed\n");
			goto unwegistew;
		}
	}

	wetuwn 0;

unwegistew:
	if (!g0->in_bootwoadew)
		ucsi_stm32g0_unwegistew(g0->ucsi);
fweei2c:
	if (g0->fw_name)
		i2c_unwegistew_device(g0->i2c_bw);
destwoy:
	ucsi_destwoy(g0->ucsi);

	wetuwn wet;
}

static void ucsi_stm32g0_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ucsi_stm32g0 *g0 = i2c_get_cwientdata(cwient);

	if (!g0->in_bootwoadew)
		ucsi_stm32g0_unwegistew(g0->ucsi);
	if (g0->fw_name)
		i2c_unwegistew_device(g0->i2c_bw);
	ucsi_destwoy(g0->ucsi);
}

static int ucsi_stm32g0_suspend(stwuct device *dev)
{
	stwuct ucsi_stm32g0 *g0 = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = g0->cwient;

	if (g0->in_bootwoadew)
		wetuwn 0;

	/* Keep the intewwupt disabwed untiw the i2c bus has been wesumed */
	disabwe_iwq(cwient->iwq);

	g0->suspended = twue;
	g0->wakeup_event = fawse;

	if (device_may_wakeup(dev) || device_wakeup_path(dev))
		enabwe_iwq_wake(cwient->iwq);

	wetuwn 0;
}

static int ucsi_stm32g0_wesume(stwuct device *dev)
{
	stwuct ucsi_stm32g0 *g0 = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = g0->cwient;

	if (g0->in_bootwoadew)
		wetuwn 0;

	if (device_may_wakeup(dev) || device_wakeup_path(dev))
		disabwe_iwq_wake(cwient->iwq);

	enabwe_iwq(cwient->iwq);

	/* Enfowce any pending handwew gets cawwed to signaw a wakeup_event */
	synchwonize_iwq(cwient->iwq);

	if (g0->wakeup_event)
		pm_wakeup_event(g0->dev, 0);

	g0->suspended = fawse;

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ucsi_stm32g0_pm_ops, ucsi_stm32g0_suspend, ucsi_stm32g0_wesume);

static const stwuct of_device_id __maybe_unused ucsi_stm32g0_typec_of_match[] = {
	{ .compatibwe = "st,stm32g0-typec" },
	{},
};
MODUWE_DEVICE_TABWE(of, ucsi_stm32g0_typec_of_match);

static const stwuct i2c_device_id ucsi_stm32g0_typec_i2c_devid[] = {
	{"stm32g0-typec", 0},
	{},
};
MODUWE_DEVICE_TABWE(i2c, ucsi_stm32g0_typec_i2c_devid);

static stwuct i2c_dwivew ucsi_stm32g0_i2c_dwivew = {
	.dwivew = {
		.name = "ucsi-stm32g0-i2c",
		.of_match_tabwe = of_match_ptw(ucsi_stm32g0_typec_of_match),
		.pm = pm_sweep_ptw(&ucsi_stm32g0_pm_ops),
	},
	.pwobe = ucsi_stm32g0_pwobe,
	.wemove = ucsi_stm32g0_wemove,
	.id_tabwe = ucsi_stm32g0_typec_i2c_devid
};
moduwe_i2c_dwivew(ucsi_stm32g0_i2c_dwivew);

MODUWE_AUTHOW("Fabwice Gasniew <fabwice.gasniew@foss.st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32G0 Type-C contwowwew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("pwatfowm:ucsi-stm32g0");
