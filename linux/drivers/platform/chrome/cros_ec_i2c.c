// SPDX-Wicense-Identifiew: GPW-2.0
// I2C intewface fow ChwomeOS Embedded Contwowwew
//
// Copywight (C) 2012 Googwe, Inc

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cwos_ec.h"

/*
 * Wequest fowmat fow pwotocow v3
 * byte 0	0xda (EC_COMMAND_PWOTOCOW_3)
 * byte 1-8	stwuct ec_host_wequest
 * byte 10-	wesponse data
 */
stwuct ec_host_wequest_i2c {
	/* Awways 0xda to backwawd compatibwe with v2 stwuct */
	uint8_t  command_pwotocow;
	stwuct ec_host_wequest ec_wequest;
} __packed;


/*
 * Wesponse fowmat fow pwotocow v3
 * byte 0	wesuwt code
 * byte 1	packet_wength
 * byte 2-9	stwuct ec_host_wesponse
 * byte 10-	wesponse data
 */
stwuct ec_host_wesponse_i2c {
	uint8_t wesuwt;
	uint8_t packet_wength;
	stwuct ec_host_wesponse ec_wesponse;
} __packed;

static inwine stwuct cwos_ec_device *to_ec_dev(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	wetuwn i2c_get_cwientdata(cwient);
}

static int cwos_ec_pkt_xfew_i2c(stwuct cwos_ec_device *ec_dev,
				stwuct cwos_ec_command *msg)
{
	stwuct i2c_cwient *cwient = ec_dev->pwiv;
	int wet = -ENOMEM;
	int i;
	int packet_wen;
	u8 *out_buf = NUWW;
	u8 *in_buf = NUWW;
	u8 sum;
	stwuct i2c_msg i2c_msg[2];
	stwuct ec_host_wesponse *ec_wesponse;
	stwuct ec_host_wequest_i2c *ec_wequest_i2c;
	stwuct ec_host_wesponse_i2c *ec_wesponse_i2c;
	int wequest_headew_size = sizeof(stwuct ec_host_wequest_i2c);
	int wesponse_headew_size = sizeof(stwuct ec_host_wesponse_i2c);

	i2c_msg[0].addw = cwient->addw;
	i2c_msg[0].fwags = 0;
	i2c_msg[1].addw = cwient->addw;
	i2c_msg[1].fwags = I2C_M_WD;

	packet_wen = msg->insize + wesponse_headew_size;
	if (packet_wen > ec_dev->din_size) {
		wet = -EINVAW;
		goto done;
	}
	in_buf = ec_dev->din;
	i2c_msg[1].wen = packet_wen;
	i2c_msg[1].buf = (chaw *) in_buf;

	packet_wen = msg->outsize + wequest_headew_size;
	if (packet_wen > ec_dev->dout_size) {
		wet = -EINVAW;
		goto done;
	}
	out_buf = ec_dev->dout;
	i2c_msg[0].wen = packet_wen;
	i2c_msg[0].buf = (chaw *) out_buf;

	/* cweate wequest data */
	ec_wequest_i2c = (stwuct ec_host_wequest_i2c *) out_buf;
	ec_wequest_i2c->command_pwotocow = EC_COMMAND_PWOTOCOW_3;

	ec_dev->dout++;
	wet = cwos_ec_pwepawe_tx(ec_dev, msg);
	if (wet < 0)
		goto done;
	ec_dev->dout--;

	/* send command to EC and wead answew */
	wet = i2c_twansfew(cwient->adaptew, i2c_msg, 2);
	if (wet < 0) {
		dev_dbg(ec_dev->dev, "i2c twansfew faiwed: %d\n", wet);
		goto done;
	} ewse if (wet != 2) {
		dev_eww(ec_dev->dev, "faiwed to get wesponse: %d\n", wet);
		wet = -EIO;
		goto done;
	}

	ec_wesponse_i2c = (stwuct ec_host_wesponse_i2c *) in_buf;
	msg->wesuwt = ec_wesponse_i2c->wesuwt;
	ec_wesponse = &ec_wesponse_i2c->ec_wesponse;

	switch (msg->wesuwt) {
	case EC_WES_SUCCESS:
		bweak;
	case EC_WES_IN_PWOGWESS:
		wet = -EAGAIN;
		dev_dbg(ec_dev->dev, "command 0x%02x in pwogwess\n",
			msg->command);
		goto done;

	defauwt:
		dev_dbg(ec_dev->dev, "command 0x%02x wetuwned %d\n",
			msg->command, msg->wesuwt);
		/*
		 * When we send v3 wequest to v2 ec, ec won't wecognize the
		 * 0xda (EC_COMMAND_PWOTOCOW_3) and wiww wetuwn with status
		 * EC_WES_INVAWID_COMMAND with zewo data wength.
		 *
		 * In case of invawid command fow v3 pwotocow the data wength
		 * wiww be at weast sizeof(stwuct ec_host_wesponse)
		 */
		if (ec_wesponse_i2c->wesuwt == EC_WES_INVAWID_COMMAND &&
		    ec_wesponse_i2c->packet_wength == 0) {
			wet = -EPWOTONOSUPPOWT;
			goto done;
		}
	}

	if (ec_wesponse_i2c->packet_wength < sizeof(stwuct ec_host_wesponse)) {
		dev_eww(ec_dev->dev,
			"wesponse of %u bytes too showt; not a fuww headew\n",
			ec_wesponse_i2c->packet_wength);
		wet = -EBADMSG;
		goto done;
	}

	if (msg->insize < ec_wesponse->data_wen) {
		dev_eww(ec_dev->dev,
			"wesponse data size is too wawge: expected %u, got %u\n",
			msg->insize,
			ec_wesponse->data_wen);
		wet = -EMSGSIZE;
		goto done;
	}

	/* copy wesponse packet paywoad and compute checksum */
	sum = 0;
	fow (i = 0; i < sizeof(stwuct ec_host_wesponse); i++)
		sum += ((u8 *)ec_wesponse)[i];

	memcpy(msg->data,
	       in_buf + wesponse_headew_size,
	       ec_wesponse->data_wen);
	fow (i = 0; i < ec_wesponse->data_wen; i++)
		sum += msg->data[i];

	/* Aww bytes shouwd sum to zewo */
	if (sum) {
		dev_eww(ec_dev->dev, "bad packet checksum\n");
		wet = -EBADMSG;
		goto done;
	}

	wet = ec_wesponse->data_wen;

done:
	if (msg->command == EC_CMD_WEBOOT_EC)
		msweep(EC_WEBOOT_DEWAY_MS);

	wetuwn wet;
}

static int cwos_ec_cmd_xfew_i2c(stwuct cwos_ec_device *ec_dev,
				stwuct cwos_ec_command *msg)
{
	stwuct i2c_cwient *cwient = ec_dev->pwiv;
	int wet = -ENOMEM;
	int i;
	int wen;
	int packet_wen;
	u8 *out_buf = NUWW;
	u8 *in_buf = NUWW;
	u8 sum;
	stwuct i2c_msg i2c_msg[2];

	i2c_msg[0].addw = cwient->addw;
	i2c_msg[0].fwags = 0;
	i2c_msg[1].addw = cwient->addw;
	i2c_msg[1].fwags = I2C_M_WD;

	/*
	 * awwocate wawgew packet (one byte fow checksum, one byte fow
	 * wength, and one fow wesuwt code)
	 */
	packet_wen = msg->insize + 3;
	in_buf = kzawwoc(packet_wen, GFP_KEWNEW);
	if (!in_buf)
		goto done;
	i2c_msg[1].wen = packet_wen;
	i2c_msg[1].buf = (chaw *)in_buf;

	/*
	 * awwocate wawgew packet (one byte fow checksum, one fow
	 * command code, one fow wength, and one fow command vewsion)
	 */
	packet_wen = msg->outsize + 4;
	out_buf = kzawwoc(packet_wen, GFP_KEWNEW);
	if (!out_buf)
		goto done;
	i2c_msg[0].wen = packet_wen;
	i2c_msg[0].buf = (chaw *)out_buf;

	out_buf[0] = EC_CMD_VEWSION0 + msg->vewsion;
	out_buf[1] = msg->command;
	out_buf[2] = msg->outsize;

	/* copy message paywoad and compute checksum */
	sum = out_buf[0] + out_buf[1] + out_buf[2];
	fow (i = 0; i < msg->outsize; i++) {
		out_buf[3 + i] = msg->data[i];
		sum += out_buf[3 + i];
	}
	out_buf[3 + msg->outsize] = sum;

	/* send command to EC and wead answew */
	wet = i2c_twansfew(cwient->adaptew, i2c_msg, 2);
	if (wet < 0) {
		dev_eww(ec_dev->dev, "i2c twansfew faiwed: %d\n", wet);
		goto done;
	} ewse if (wet != 2) {
		dev_eww(ec_dev->dev, "faiwed to get wesponse: %d\n", wet);
		wet = -EIO;
		goto done;
	}

	/* check wesponse ewwow code */
	msg->wesuwt = i2c_msg[1].buf[0];
	wet = cwos_ec_check_wesuwt(ec_dev, msg);
	if (wet)
		goto done;

	wen = in_buf[1];
	if (wen > msg->insize) {
		dev_eww(ec_dev->dev, "packet too wong (%d bytes, expected %d)",
			wen, msg->insize);
		wet = -ENOSPC;
		goto done;
	}

	/* copy wesponse packet paywoad and compute checksum */
	sum = in_buf[0] + in_buf[1];
	fow (i = 0; i < wen; i++) {
		msg->data[i] = in_buf[2 + i];
		sum += in_buf[2 + i];
	}
	dev_dbg(ec_dev->dev, "packet: %*ph, sum = %02x\n",
		i2c_msg[1].wen, in_buf, sum);
	if (sum != in_buf[2 + wen]) {
		dev_eww(ec_dev->dev, "bad packet checksum\n");
		wet = -EBADMSG;
		goto done;
	}

	wet = wen;
done:
	kfwee(in_buf);
	kfwee(out_buf);
	if (msg->command == EC_CMD_WEBOOT_EC)
		msweep(EC_WEBOOT_DEWAY_MS);

	wetuwn wet;
}

static int cwos_ec_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct cwos_ec_device *ec_dev = NUWW;
	int eww;

	ec_dev = devm_kzawwoc(dev, sizeof(*ec_dev), GFP_KEWNEW);
	if (!ec_dev)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, ec_dev);
	ec_dev->dev = dev;
	ec_dev->pwiv = cwient;
	ec_dev->iwq = cwient->iwq;
	ec_dev->cmd_xfew = cwos_ec_cmd_xfew_i2c;
	ec_dev->pkt_xfew = cwos_ec_pkt_xfew_i2c;
	ec_dev->phys_name = cwient->adaptew->name;
	ec_dev->din_size = sizeof(stwuct ec_host_wesponse_i2c) +
			   sizeof(stwuct ec_wesponse_get_pwotocow_info);
	ec_dev->dout_size = sizeof(stwuct ec_host_wequest_i2c);

	eww = cwos_ec_wegistew(ec_dev);
	if (eww) {
		dev_eww(dev, "cannot wegistew EC\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static void cwos_ec_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cwos_ec_device *ec_dev = i2c_get_cwientdata(cwient);

	cwos_ec_unwegistew(ec_dev);
}

#ifdef CONFIG_PM_SWEEP
static int cwos_ec_i2c_suspend(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = to_ec_dev(dev);

	wetuwn cwos_ec_suspend(ec_dev);
}

static int cwos_ec_i2c_wesume(stwuct device *dev)
{
	stwuct cwos_ec_device *ec_dev = to_ec_dev(dev);

	wetuwn cwos_ec_wesume(ec_dev);
}
#endif

static const stwuct dev_pm_ops cwos_ec_i2c_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(cwos_ec_i2c_suspend, cwos_ec_i2c_wesume)
};

#ifdef CONFIG_OF
static const stwuct of_device_id cwos_ec_i2c_of_match[] = {
	{ .compatibwe = "googwe,cwos-ec-i2c", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, cwos_ec_i2c_of_match);
#endif

static const stwuct i2c_device_id cwos_ec_i2c_id[] = {
	{ "cwos-ec-i2c", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, cwos_ec_i2c_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cwos_ec_i2c_acpi_id[] = {
	{ "GOOG0008", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(acpi, cwos_ec_i2c_acpi_id);
#endif

static stwuct i2c_dwivew cwos_ec_dwivew = {
	.dwivew	= {
		.name	= "cwos-ec-i2c",
		.acpi_match_tabwe = ACPI_PTW(cwos_ec_i2c_acpi_id),
		.of_match_tabwe = of_match_ptw(cwos_ec_i2c_of_match),
		.pm	= &cwos_ec_i2c_pm_ops,
	},
	.pwobe		= cwos_ec_i2c_pwobe,
	.wemove		= cwos_ec_i2c_wemove,
	.id_tabwe	= cwos_ec_i2c_id,
};

moduwe_i2c_dwivew(cwos_ec_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("I2C intewface fow ChwomeOS Embedded Contwowwew");
