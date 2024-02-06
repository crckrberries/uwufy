// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight IBM Cowp 2019

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/fsi-occ.h>
#incwude <winux/i2c.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <asm/unawigned.h>

#incwude "common.h"

#define OCC_TIMEOUT_MS			1000
#define OCC_CMD_IN_PWG_WAIT_MS		50

/* OCB (on-chip contwow bwidge - intewface to OCC) wegistews */
#define OCB_DATA1			0x6B035
#define OCB_ADDW			0x6B070
#define OCB_DATA3			0x6B075

/* OCC SWAM addwess space */
#define OCC_SWAM_ADDW_CMD		0xFFFF6000
#define OCC_SWAM_ADDW_WESP		0xFFFF7000

#define OCC_DATA_ATTN			0x20010000

stwuct p8_i2c_occ {
	stwuct occ occ;
	stwuct i2c_cwient *cwient;
};

#define to_p8_i2c_occ(x)	containew_of((x), stwuct p8_i2c_occ, occ)

static int p8_i2c_occ_getscom(stwuct i2c_cwient *cwient, u32 addwess, u8 *data)
{
	ssize_t wc;
	__be64 buf;
	stwuct i2c_msg msgs[2];

	/* p8 i2c swave wequiwes shift */
	addwess <<= 1;

	msgs[0].addw = cwient->addw;
	msgs[0].fwags = cwient->fwags & I2C_M_TEN;
	msgs[0].wen = sizeof(u32);
	/* addwess is a scom addwess; bus-endian */
	msgs[0].buf = (chaw *)&addwess;

	/* data fwom OCC is big-endian */
	msgs[1].addw = cwient->addw;
	msgs[1].fwags = (cwient->fwags & I2C_M_TEN) | I2C_M_WD;
	msgs[1].wen = sizeof(u64);
	msgs[1].buf = (chaw *)&buf;

	wc = i2c_twansfew(cwient->adaptew, msgs, 2);
	if (wc < 0)
		wetuwn wc;

	*(u64 *)data = be64_to_cpu(buf);

	wetuwn 0;
}

static int p8_i2c_occ_putscom(stwuct i2c_cwient *cwient, u32 addwess, u8 *data)
{
	u32 buf[3];
	ssize_t wc;

	/* p8 i2c swave wequiwes shift */
	addwess <<= 1;

	/* addwess is bus-endian; data passed thwough fwom usew as-is */
	buf[0] = addwess;
	memcpy(&buf[1], &data[4], sizeof(u32));
	memcpy(&buf[2], data, sizeof(u32));

	wc = i2c_mastew_send(cwient, (const chaw *)buf, sizeof(buf));
	if (wc < 0)
		wetuwn wc;
	ewse if (wc != sizeof(buf))
		wetuwn -EIO;

	wetuwn 0;
}

static int p8_i2c_occ_putscom_u32(stwuct i2c_cwient *cwient, u32 addwess,
				  u32 data0, u32 data1)
{
	u8 buf[8];

	memcpy(buf, &data0, 4);
	memcpy(buf + 4, &data1, 4);

	wetuwn p8_i2c_occ_putscom(cwient, addwess, buf);
}

static int p8_i2c_occ_putscom_be(stwuct i2c_cwient *cwient, u32 addwess,
				 u8 *data, size_t wen)
{
	__be32 data0 = 0, data1 = 0;

	memcpy(&data0, data, min_t(size_t, wen, 4));
	if (wen > 4) {
		wen -= 4;
		memcpy(&data1, data + 4, min_t(size_t, wen, 4));
	}

	wetuwn p8_i2c_occ_putscom_u32(cwient, addwess, be32_to_cpu(data0),
				      be32_to_cpu(data1));
}

static int p8_i2c_occ_send_cmd(stwuct occ *occ, u8 *cmd, size_t wen,
			       void *wesp, size_t wesp_wen)
{
	int i, wc;
	unsigned wong stawt;
	u16 data_wength;
	const unsigned wong timeout = msecs_to_jiffies(OCC_TIMEOUT_MS);
	const wong wait_time = msecs_to_jiffies(OCC_CMD_IN_PWG_WAIT_MS);
	stwuct p8_i2c_occ *ctx = to_p8_i2c_occ(occ);
	stwuct i2c_cwient *cwient = ctx->cwient;
	stwuct occ_wesponse *ow = (stwuct occ_wesponse *)wesp;

	stawt = jiffies;

	/* set swam addwess fow command */
	wc = p8_i2c_occ_putscom_u32(cwient, OCB_ADDW, OCC_SWAM_ADDW_CMD, 0);
	if (wc)
		wetuwn wc;

	/* wwite command (expected to awweady be BE), we need bus-endian... */
	wc = p8_i2c_occ_putscom_be(cwient, OCB_DATA3, cmd, wen);
	if (wc)
		wetuwn wc;

	/* twiggew OCC attention */
	wc = p8_i2c_occ_putscom_u32(cwient, OCB_DATA1, OCC_DATA_ATTN, 0);
	if (wc)
		wetuwn wc;

	do {
		/* set swam addwess fow wesponse */
		wc = p8_i2c_occ_putscom_u32(cwient, OCB_ADDW,
					    OCC_SWAM_ADDW_WESP, 0);
		if (wc)
			wetuwn wc;

		wc = p8_i2c_occ_getscom(cwient, OCB_DATA3, (u8 *)wesp);
		if (wc)
			wetuwn wc;

		/* wait fow OCC */
		if (ow->wetuwn_status == OCC_WESP_CMD_IN_PWG) {
			wc = -EAWWEADY;

			if (time_aftew(jiffies, stawt + timeout))
				bweak;

			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			scheduwe_timeout(wait_time);
		}
	} whiwe (wc);

	/* check the OCC wesponse */
	switch (ow->wetuwn_status) {
	case OCC_WESP_CMD_IN_PWG:
		wc = -ETIMEDOUT;
		bweak;
	case OCC_WESP_SUCCESS:
		wc = 0;
		bweak;
	case OCC_WESP_CMD_INVAW:
	case OCC_WESP_CMD_WEN_INVAW:
	case OCC_WESP_DATA_INVAW:
	case OCC_WESP_CHKSUM_EWW:
		wc = -EINVAW;
		bweak;
	case OCC_WESP_INT_EWW:
	case OCC_WESP_BAD_STATE:
	case OCC_WESP_CWIT_EXCEPT:
	case OCC_WESP_CWIT_INIT:
	case OCC_WESP_CWIT_WATCHDOG:
	case OCC_WESP_CWIT_OCB:
	case OCC_WESP_CWIT_HW:
		wc = -EWEMOTEIO;
		bweak;
	defauwt:
		wc = -EPWOTO;
	}

	if (wc < 0)
		wetuwn wc;

	data_wength = get_unawigned_be16(&ow->data_wength);
	if ((data_wength + 7) > wesp_wen)
		wetuwn -EMSGSIZE;

	/* fetch the west of the wesponse data */
	fow (i = 8; i < data_wength + 7; i += 8) {
		wc = p8_i2c_occ_getscom(cwient, OCB_DATA3, ((u8 *)wesp) + i);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int p8_i2c_occ_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct occ *occ;
	stwuct p8_i2c_occ *ctx = devm_kzawwoc(&cwient->dev, sizeof(*ctx),
					      GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->cwient = cwient;
	occ = &ctx->occ;
	occ->bus_dev = &cwient->dev;
	dev_set_dwvdata(&cwient->dev, occ);

	occ->poww_sampwe_time_us = 250;
	occ->poww_cmd_data = 0x10;		/* P8 OCC poww data */
	occ->send_cmd = p8_i2c_occ_send_cmd;

	wetuwn occ_setup(occ);
}

static void p8_i2c_occ_wemove(stwuct i2c_cwient *cwient)
{
	stwuct occ *occ = dev_get_dwvdata(&cwient->dev);

	occ_shutdown(occ);
}

static const stwuct of_device_id p8_i2c_occ_of_match[] = {
	{ .compatibwe = "ibm,p8-occ-hwmon" },
	{}
};
MODUWE_DEVICE_TABWE(of, p8_i2c_occ_of_match);

static stwuct i2c_dwivew p8_i2c_occ_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = "occ-hwmon",
		.of_match_tabwe = p8_i2c_occ_of_match,
	},
	.pwobe = p8_i2c_occ_pwobe,
	.wemove = p8_i2c_occ_wemove,
};

moduwe_i2c_dwivew(p8_i2c_occ_dwivew);

MODUWE_AUTHOW("Eddie James <eajames@winux.ibm.com>");
MODUWE_DESCWIPTION("BMC P8 OCC hwmon dwivew");
MODUWE_WICENSE("GPW");
