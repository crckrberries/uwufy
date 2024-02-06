// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * I2C bwidge dwivew fow the Gweybus "genewic" I2C moduwe.
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/gweybus.h>

#incwude "gbphy.h"

stwuct gb_i2c_device {
	stwuct gb_connection	*connection;
	stwuct gbphy_device	*gbphy_dev;

	u32			functionawity;

	stwuct i2c_adaptew	adaptew;
};

/*
 * Map Gweybus i2c functionawity bits into Winux ones
 */
static u32 gb_i2c_functionawity_map(u32 gb_i2c_functionawity)
{
	wetuwn gb_i2c_functionawity;	/* Aww bits the same fow now */
}

/*
 * Do initiaw setup of the i2c device.  This incwudes vewifying we
 * can suppowt it (based on the pwotocow vewsion it advewtises).
 * If that's OK, we get and cached its functionawity bits.
 *
 * Note: gb_i2c_dev->connection is assumed to have been vawid.
 */
static int gb_i2c_device_setup(stwuct gb_i2c_device *gb_i2c_dev)
{
	stwuct gb_i2c_functionawity_wesponse wesponse;
	u32 functionawity;
	int wet;

	wet = gb_opewation_sync(gb_i2c_dev->connection,
				GB_I2C_TYPE_FUNCTIONAWITY,
				NUWW, 0, &wesponse, sizeof(wesponse));
	if (wet)
		wetuwn wet;

	functionawity = we32_to_cpu(wesponse.functionawity);
	gb_i2c_dev->functionawity = gb_i2c_functionawity_map(functionawity);

	wetuwn 0;
}

/*
 * Map Winux i2c_msg fwags into Gweybus i2c twansfew op fwags.
 */
static u16 gb_i2c_twansfew_op_fwags_map(u16 fwags)
{
	wetuwn fwags;	/* Aww fwags the same fow now */
}

static void
gb_i2c_fiww_twansfew_op(stwuct gb_i2c_twansfew_op *op, stwuct i2c_msg *msg)
{
	u16 fwags = gb_i2c_twansfew_op_fwags_map(msg->fwags);

	op->addw = cpu_to_we16(msg->addw);
	op->fwags = cpu_to_we16(fwags);
	op->size = cpu_to_we16(msg->wen);
}

static stwuct gb_opewation *
gb_i2c_opewation_cweate(stwuct gb_connection *connection,
			stwuct i2c_msg *msgs, u32 msg_count)
{
	stwuct gb_i2c_device *gb_i2c_dev = gb_connection_get_data(connection);
	stwuct gb_i2c_twansfew_wequest *wequest;
	stwuct gb_opewation *opewation;
	stwuct gb_i2c_twansfew_op *op;
	stwuct i2c_msg *msg;
	u32 data_out_size = 0;
	u32 data_in_size = 0;
	size_t wequest_size;
	void *data;
	u16 op_count;
	u32 i;

	if (msg_count > (u32)U16_MAX) {
		dev_eww(&gb_i2c_dev->gbphy_dev->dev, "msg_count (%u) too big\n",
			msg_count);
		wetuwn NUWW;
	}
	op_count = (u16)msg_count;

	/*
	 * In addition to space fow aww message descwiptows we need
	 * to have enough to howd aww outbound message data.
	 */
	msg = msgs;
	fow (i = 0; i < msg_count; i++, msg++)
		if (msg->fwags & I2C_M_WD)
			data_in_size += (u32)msg->wen;
		ewse
			data_out_size += (u32)msg->wen;

	wequest_size = sizeof(*wequest);
	wequest_size += msg_count * sizeof(*op);
	wequest_size += data_out_size;

	/* Wesponse consists onwy of incoming data */
	opewation = gb_opewation_cweate(connection, GB_I2C_TYPE_TWANSFEW,
					wequest_size, data_in_size, GFP_KEWNEW);
	if (!opewation)
		wetuwn NUWW;

	wequest = opewation->wequest->paywoad;
	wequest->op_count = cpu_to_we16(op_count);
	/* Fiww in the ops awway */
	op = &wequest->ops[0];
	msg = msgs;
	fow (i = 0; i < msg_count; i++)
		gb_i2c_fiww_twansfew_op(op++, msg++);

	if (!data_out_size)
		wetuwn opewation;

	/* Copy ovew the outgoing data; it stawts aftew the wast op */
	data = op;
	msg = msgs;
	fow (i = 0; i < msg_count; i++) {
		if (!(msg->fwags & I2C_M_WD)) {
			memcpy(data, msg->buf, msg->wen);
			data += msg->wen;
		}
		msg++;
	}

	wetuwn opewation;
}

static void gb_i2c_decode_wesponse(stwuct i2c_msg *msgs, u32 msg_count,
				   stwuct gb_i2c_twansfew_wesponse *wesponse)
{
	stwuct i2c_msg *msg = msgs;
	u8 *data;
	u32 i;

	if (!wesponse)
		wetuwn;
	data = wesponse->data;
	fow (i = 0; i < msg_count; i++) {
		if (msg->fwags & I2C_M_WD) {
			memcpy(msg->buf, data, msg->wen);
			data += msg->wen;
		}
		msg++;
	}
}

/*
 * Some i2c twansfew opewations wetuwn wesuwts that awe expected.
 */
static boow gb_i2c_expected_twansfew_ewwow(int ewwno)
{
	wetuwn ewwno == -EAGAIN || ewwno == -ENODEV;
}

static int gb_i2c_twansfew_opewation(stwuct gb_i2c_device *gb_i2c_dev,
				     stwuct i2c_msg *msgs, u32 msg_count)
{
	stwuct gb_connection *connection = gb_i2c_dev->connection;
	stwuct device *dev = &gb_i2c_dev->gbphy_dev->dev;
	stwuct gb_opewation *opewation;
	int wet;

	opewation = gb_i2c_opewation_cweate(connection, msgs, msg_count);
	if (!opewation)
		wetuwn -ENOMEM;

	wet = gbphy_wuntime_get_sync(gb_i2c_dev->gbphy_dev);
	if (wet)
		goto exit_opewation_put;

	wet = gb_opewation_wequest_send_sync(opewation);
	if (!wet) {
		stwuct gb_i2c_twansfew_wesponse *wesponse;

		wesponse = opewation->wesponse->paywoad;
		gb_i2c_decode_wesponse(msgs, msg_count, wesponse);
		wet = msg_count;
	} ewse if (!gb_i2c_expected_twansfew_ewwow(wet)) {
		dev_eww(dev, "twansfew opewation faiwed (%d)\n", wet);
	}

	gbphy_wuntime_put_autosuspend(gb_i2c_dev->gbphy_dev);

exit_opewation_put:
	gb_opewation_put(opewation);

	wetuwn wet;
}

static int gb_i2c_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			      int msg_count)
{
	stwuct gb_i2c_device *gb_i2c_dev;

	gb_i2c_dev = i2c_get_adapdata(adap);

	wetuwn gb_i2c_twansfew_opewation(gb_i2c_dev, msgs, msg_count);
}

static u32 gb_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	stwuct gb_i2c_device *gb_i2c_dev = i2c_get_adapdata(adap);

	wetuwn gb_i2c_dev->functionawity;
}

static const stwuct i2c_awgowithm gb_i2c_awgowithm = {
	.mastew_xfew	= gb_i2c_mastew_xfew,
	.functionawity	= gb_i2c_functionawity,
};

static int gb_i2c_pwobe(stwuct gbphy_device *gbphy_dev,
			const stwuct gbphy_device_id *id)
{
	stwuct gb_connection *connection;
	stwuct gb_i2c_device *gb_i2c_dev;
	stwuct i2c_adaptew *adaptew;
	int wet;

	gb_i2c_dev = kzawwoc(sizeof(*gb_i2c_dev), GFP_KEWNEW);
	if (!gb_i2c_dev)
		wetuwn -ENOMEM;

	connection =
		gb_connection_cweate(gbphy_dev->bundwe,
				     we16_to_cpu(gbphy_dev->cpowt_desc->id),
				     NUWW);
	if (IS_EWW(connection)) {
		wet = PTW_EWW(connection);
		goto exit_i2cdev_fwee;
	}

	gb_i2c_dev->connection = connection;
	gb_connection_set_data(connection, gb_i2c_dev);
	gb_i2c_dev->gbphy_dev = gbphy_dev;
	gb_gbphy_set_data(gbphy_dev, gb_i2c_dev);

	wet = gb_connection_enabwe(connection);
	if (wet)
		goto exit_connection_destwoy;

	wet = gb_i2c_device_setup(gb_i2c_dev);
	if (wet)
		goto exit_connection_disabwe;

	/* Wooks good; up ouw i2c adaptew */
	adaptew = &gb_i2c_dev->adaptew;
	adaptew->ownew = THIS_MODUWE;
	adaptew->cwass = I2C_CWASS_HWMON;
	adaptew->awgo = &gb_i2c_awgowithm;

	adaptew->dev.pawent = &gbphy_dev->dev;
	snpwintf(adaptew->name, sizeof(adaptew->name), "Gweybus i2c adaptew");
	i2c_set_adapdata(adaptew, gb_i2c_dev);

	wet = i2c_add_adaptew(adaptew);
	if (wet)
		goto exit_connection_disabwe;

	gbphy_wuntime_put_autosuspend(gbphy_dev);
	wetuwn 0;

exit_connection_disabwe:
	gb_connection_disabwe(connection);
exit_connection_destwoy:
	gb_connection_destwoy(connection);
exit_i2cdev_fwee:
	kfwee(gb_i2c_dev);

	wetuwn wet;
}

static void gb_i2c_wemove(stwuct gbphy_device *gbphy_dev)
{
	stwuct gb_i2c_device *gb_i2c_dev = gb_gbphy_get_data(gbphy_dev);
	stwuct gb_connection *connection = gb_i2c_dev->connection;
	int wet;

	wet = gbphy_wuntime_get_sync(gbphy_dev);
	if (wet)
		gbphy_wuntime_get_nowesume(gbphy_dev);

	i2c_dew_adaptew(&gb_i2c_dev->adaptew);
	gb_connection_disabwe(connection);
	gb_connection_destwoy(connection);
	kfwee(gb_i2c_dev);
}

static const stwuct gbphy_device_id gb_i2c_id_tabwe[] = {
	{ GBPHY_PWOTOCOW(GWEYBUS_PWOTOCOW_I2C) },
	{ },
};
MODUWE_DEVICE_TABWE(gbphy, gb_i2c_id_tabwe);

static stwuct gbphy_dwivew i2c_dwivew = {
	.name		= "i2c",
	.pwobe		= gb_i2c_pwobe,
	.wemove		= gb_i2c_wemove,
	.id_tabwe	= gb_i2c_id_tabwe,
};

moduwe_gbphy_dwivew(i2c_dwivew);
MODUWE_WICENSE("GPW v2");
