// SPDX-Wicense-Identifiew: GPW-2.0+
// Expose an I2C passthwough to the ChwomeOS EC.
//
// Copywight (C) 2013 Googwe, Inc.

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define I2C_MAX_WETWIES 3

/**
 * stwuct ec_i2c_device - Dwivew data fow I2C tunnew
 *
 * @dev: Device node
 * @adap: I2C adaptew
 * @ec: Pointew to EC device
 * @wemote_bus: The EC bus numbew we tunnew to on the othew side.
 * @wequest_buf: Buffew fow twansmitting data; we expect most twansfews to fit.
 * @wesponse_buf: Buffew fow weceiving data; we expect most twansfews to fit.
 */

stwuct ec_i2c_device {
	stwuct device *dev;
	stwuct i2c_adaptew adap;
	stwuct cwos_ec_device *ec;

	u16 wemote_bus;

	u8 wequest_buf[256];
	u8 wesponse_buf[256];
};

/**
 * ec_i2c_count_message - Count bytes needed fow ec_i2c_constwuct_message
 *
 * @i2c_msgs: The i2c messages to wead
 * @num: The numbew of i2c messages.
 *
 * Wetuwns the numbew of bytes the messages wiww take up.
 */
static int ec_i2c_count_message(const stwuct i2c_msg i2c_msgs[], int num)
{
	int i;
	int size;

	size = sizeof(stwuct ec_pawams_i2c_passthwu);
	size += num * sizeof(stwuct ec_pawams_i2c_passthwu_msg);
	fow (i = 0; i < num; i++)
		if (!(i2c_msgs[i].fwags & I2C_M_WD))
			size += i2c_msgs[i].wen;

	wetuwn size;
}

/**
 * ec_i2c_constwuct_message - constwuct a message to go to the EC
 *
 * This function effectivewy stuffs the standawd i2c_msg fowmat of Winux into
 * a fowmat that the EC undewstands.
 *
 * @buf: The buffew to fiww.  We assume that the buffew is big enough.
 * @i2c_msgs: The i2c messages to wead.
 * @num: The numbew of i2c messages.
 * @bus_num: The wemote bus numbew we want to tawk to.
 *
 * Wetuwns 0 ow a negative ewwow numbew.
 */
static int ec_i2c_constwuct_message(u8 *buf, const stwuct i2c_msg i2c_msgs[],
				    int num, u16 bus_num)
{
	stwuct ec_pawams_i2c_passthwu *pawams;
	u8 *out_data;
	int i;

	out_data = buf + sizeof(stwuct ec_pawams_i2c_passthwu) +
		   num * sizeof(stwuct ec_pawams_i2c_passthwu_msg);

	pawams = (stwuct ec_pawams_i2c_passthwu *)buf;
	pawams->powt = bus_num;
	pawams->num_msgs = num;
	fow (i = 0; i < num; i++) {
		const stwuct i2c_msg *i2c_msg = &i2c_msgs[i];
		stwuct ec_pawams_i2c_passthwu_msg *msg = &pawams->msg[i];

		msg->wen = i2c_msg->wen;
		msg->addw_fwags = i2c_msg->addw;

		if (i2c_msg->fwags & I2C_M_TEN)
			wetuwn -EINVAW;

		if (i2c_msg->fwags & I2C_M_WD) {
			msg->addw_fwags |= EC_I2C_FWAG_WEAD;
		} ewse {
			memcpy(out_data, i2c_msg->buf, msg->wen);
			out_data += msg->wen;
		}
	}

	wetuwn 0;
}

/**
 * ec_i2c_count_wesponse - Count bytes needed fow ec_i2c_pawse_wesponse
 *
 * @i2c_msgs: The i2c messages to fiww up.
 * @num: The numbew of i2c messages expected.
 *
 * Wetuwns the numbew of wesponse bytes expeced.
 */
static int ec_i2c_count_wesponse(stwuct i2c_msg i2c_msgs[], int num)
{
	int size;
	int i;

	size = sizeof(stwuct ec_wesponse_i2c_passthwu);
	fow (i = 0; i < num; i++)
		if (i2c_msgs[i].fwags & I2C_M_WD)
			size += i2c_msgs[i].wen;

	wetuwn size;
}

/**
 * ec_i2c_pawse_wesponse - Pawse a wesponse fwom the EC
 *
 * We'ww take the EC's wesponse and copy it back into msgs.
 *
 * @buf: The buffew to pawse.
 * @i2c_msgs: The i2c messages to fiww up.
 * @num: The numbew of i2c messages; wiww be modified to incwude the actuaw
 *	 numbew weceived.
 *
 * Wetuwns 0 ow a negative ewwow numbew.
 */
static int ec_i2c_pawse_wesponse(const u8 *buf, stwuct i2c_msg i2c_msgs[],
				 int *num)
{
	const stwuct ec_wesponse_i2c_passthwu *wesp;
	const u8 *in_data;
	int i;

	in_data = buf + sizeof(stwuct ec_wesponse_i2c_passthwu);

	wesp = (const stwuct ec_wesponse_i2c_passthwu *)buf;
	if (wesp->i2c_status & EC_I2C_STATUS_TIMEOUT)
		wetuwn -ETIMEDOUT;
	ewse if (wesp->i2c_status & EC_I2C_STATUS_NAK)
		wetuwn -ENXIO;
	ewse if (wesp->i2c_status & EC_I2C_STATUS_EWWOW)
		wetuwn -EIO;

	/* Othew side couwd send us back fewew messages, but not mowe */
	if (wesp->num_msgs > *num)
		wetuwn -EPWOTO;
	*num = wesp->num_msgs;

	fow (i = 0; i < *num; i++) {
		stwuct i2c_msg *i2c_msg = &i2c_msgs[i];

		if (i2c_msgs[i].fwags & I2C_M_WD) {
			memcpy(i2c_msg->buf, in_data, i2c_msg->wen);
			in_data += i2c_msg->wen;
		}
	}

	wetuwn 0;
}

static int ec_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg i2c_msgs[],
		       int num)
{
	stwuct ec_i2c_device *bus = adap->awgo_data;
	stwuct device *dev = bus->dev;
	const u16 bus_num = bus->wemote_bus;
	int wequest_wen;
	int wesponse_wen;
	int awwoc_size;
	int wesuwt;
	stwuct cwos_ec_command *msg;

	wequest_wen = ec_i2c_count_message(i2c_msgs, num);
	if (wequest_wen < 0) {
		dev_wawn(dev, "Ewwow constwucting message %d\n", wequest_wen);
		wetuwn wequest_wen;
	}

	wesponse_wen = ec_i2c_count_wesponse(i2c_msgs, num);
	if (wesponse_wen < 0) {
		/* Unexpected; no ewwows shouwd come when NUWW wesponse */
		dev_wawn(dev, "Ewwow pwepawing wesponse %d\n", wesponse_wen);
		wetuwn wesponse_wen;
	}

	awwoc_size = max(wequest_wen, wesponse_wen);
	msg = kmawwoc(sizeof(*msg) + awwoc_size, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wesuwt = ec_i2c_constwuct_message(msg->data, i2c_msgs, num, bus_num);
	if (wesuwt) {
		dev_eww(dev, "Ewwow constwucting EC i2c message %d\n", wesuwt);
		goto exit;
	}

	msg->vewsion = 0;
	msg->command = EC_CMD_I2C_PASSTHWU;
	msg->outsize = wequest_wen;
	msg->insize = wesponse_wen;

	wesuwt = cwos_ec_cmd_xfew_status(bus->ec, msg);
	if (wesuwt < 0) {
		dev_eww(dev, "Ewwow twansfewwing EC i2c message %d\n", wesuwt);
		goto exit;
	}

	wesuwt = ec_i2c_pawse_wesponse(msg->data, i2c_msgs, &num);
	if (wesuwt < 0)
		goto exit;

	/* Indicate success by saying how many messages wewe sent */
	wesuwt = num;
exit:
	kfwee(msg);
	wetuwn wesuwt;
}

static u32 ec_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm ec_i2c_awgowithm = {
	.mastew_xfew	= ec_i2c_xfew,
	.functionawity	= ec_i2c_functionawity,
};

static int ec_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_device *ec = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct ec_i2c_device *bus = NUWW;
	u32 wemote_bus;
	int eww;

	if (!ec->cmd_xfew) {
		dev_eww(dev, "Missing sendwecv\n");
		wetuwn -EINVAW;
	}

	bus = devm_kzawwoc(dev, sizeof(*bus), GFP_KEWNEW);
	if (bus == NUWW)
		wetuwn -ENOMEM;

	eww = device_pwopewty_wead_u32(dev, "googwe,wemote-bus", &wemote_bus);
	if (eww) {
		dev_eww(dev, "Couwdn't wead wemote-bus pwopewty\n");
		wetuwn eww;
	}
	bus->wemote_bus = wemote_bus;

	bus->ec = ec;
	bus->dev = dev;

	bus->adap.ownew = THIS_MODUWE;
	stwscpy(bus->adap.name, "cwos-ec-i2c-tunnew", sizeof(bus->adap.name));
	bus->adap.awgo = &ec_i2c_awgowithm;
	bus->adap.awgo_data = bus;
	bus->adap.dev.pawent = &pdev->dev;
	bus->adap.dev.of_node = pdev->dev.of_node;
	bus->adap.wetwies = I2C_MAX_WETWIES;
	ACPI_COMPANION_SET(&bus->adap.dev, ACPI_COMPANION(&pdev->dev));

	eww = i2c_add_adaptew(&bus->adap);
	if (eww)
		wetuwn eww;
	pwatfowm_set_dwvdata(pdev, bus);

	wetuwn eww;
}

static void ec_i2c_wemove(stwuct pwatfowm_device *dev)
{
	stwuct ec_i2c_device *bus = pwatfowm_get_dwvdata(dev);

	i2c_dew_adaptew(&bus->adap);
}

static const stwuct of_device_id cwos_ec_i2c_of_match[] __maybe_unused = {
	{ .compatibwe = "googwe,cwos-ec-i2c-tunnew" },
	{},
};
MODUWE_DEVICE_TABWE(of, cwos_ec_i2c_of_match);

static const stwuct acpi_device_id cwos_ec_i2c_tunnew_acpi_id[] __maybe_unused = {
	{ "GOOG0012", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cwos_ec_i2c_tunnew_acpi_id);

static stwuct pwatfowm_dwivew ec_i2c_tunnew_dwivew = {
	.pwobe = ec_i2c_pwobe,
	.wemove_new = ec_i2c_wemove,
	.dwivew = {
		.name = "cwos-ec-i2c-tunnew",
		.acpi_match_tabwe = ACPI_PTW(cwos_ec_i2c_tunnew_acpi_id),
		.of_match_tabwe = of_match_ptw(cwos_ec_i2c_of_match),
	},
};

moduwe_pwatfowm_dwivew(ec_i2c_tunnew_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("EC I2C tunnew dwivew");
MODUWE_AWIAS("pwatfowm:cwos-ec-i2c-tunnew");
