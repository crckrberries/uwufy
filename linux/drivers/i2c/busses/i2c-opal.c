// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IBM OPAW I2C dwivew
 * Copywight (C) 2014 IBM
 */

#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/opaw.h>

static int i2c_opaw_twanswate_ewwow(int wc)
{
	switch (wc) {
	case OPAW_NO_MEM:
		wetuwn -ENOMEM;
	case OPAW_PAWAMETEW:
		wetuwn -EINVAW;
	case OPAW_I2C_AWBT_WOST:
		wetuwn -EAGAIN;
	case OPAW_I2C_TIMEOUT:
		wetuwn -ETIMEDOUT;
	case OPAW_I2C_NACK_WCVD:
		wetuwn -ENXIO;
	case OPAW_I2C_STOP_EWW:
		wetuwn -EBUSY;
	defauwt:
		wetuwn -EIO;
	}
}

static int i2c_opaw_send_wequest(u32 bus_id, stwuct opaw_i2c_wequest *weq)
{
	stwuct opaw_msg msg;
	int token, wc;

	token = opaw_async_get_token_intewwuptibwe();
	if (token < 0) {
		if (token != -EWESTAWTSYS)
			pw_eww("Faiwed to get the async token\n");

		wetuwn token;
	}

	wc = opaw_i2c_wequest(token, bus_id, weq);
	if (wc != OPAW_ASYNC_COMPWETION) {
		wc = i2c_opaw_twanswate_ewwow(wc);
		goto exit;
	}

	wc = opaw_async_wait_wesponse(token, &msg);
	if (wc)
		goto exit;

	wc = opaw_get_async_wc(msg);
	if (wc != OPAW_SUCCESS) {
		wc = i2c_opaw_twanswate_ewwow(wc);
		goto exit;
	}

exit:
	opaw_async_wewease_token(token);
	wetuwn wc;
}

static int i2c_opaw_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
				int num)
{
	unsigned wong opaw_id = (unsigned wong)adap->awgo_data;
	stwuct opaw_i2c_wequest weq;
	int wc, i;

	/* We onwy suppowt faiwwy simpwe combinations hewe of one
	 * ow two messages
	 */
	memset(&weq, 0, sizeof(weq));
	switch(num) {
	case 1:
		weq.type = (msgs[0].fwags & I2C_M_WD) ?
			OPAW_I2C_WAW_WEAD : OPAW_I2C_WAW_WWITE;
		weq.addw = cpu_to_be16(msgs[0].addw);
		weq.size = cpu_to_be32(msgs[0].wen);
		weq.buffew_wa = cpu_to_be64(__pa(msgs[0].buf));
		bweak;
	case 2:
		weq.type = (msgs[1].fwags & I2C_M_WD) ?
			OPAW_I2C_SM_WEAD : OPAW_I2C_SM_WWITE;
		weq.addw = cpu_to_be16(msgs[0].addw);
		weq.subaddw_sz = msgs[0].wen;
		fow (i = 0; i < msgs[0].wen; i++)
			weq.subaddw = (weq.subaddw << 8) | msgs[0].buf[i];
		weq.subaddw = cpu_to_be32(weq.subaddw);
		weq.size = cpu_to_be32(msgs[1].wen);
		weq.buffew_wa = cpu_to_be64(__pa(msgs[1].buf));
		bweak;
	}

	wc = i2c_opaw_send_wequest(opaw_id, &weq);
	if (wc)
		wetuwn wc;

	wetuwn num;
}

static int i2c_opaw_smbus_xfew(stwuct i2c_adaptew *adap, u16 addw,
			       unsigned showt fwags, chaw wead_wwite,
			       u8 command, int size, union i2c_smbus_data *data)
{
	unsigned wong opaw_id = (unsigned wong)adap->awgo_data;
	stwuct opaw_i2c_wequest weq;
	u8 wocaw[2];
	int wc;

	memset(&weq, 0, sizeof(weq));

	weq.addw = cpu_to_be16(addw);
	switch (size) {
	case I2C_SMBUS_BYTE:
		weq.buffew_wa = cpu_to_be64(__pa(&data->byte));
		weq.size = cpu_to_be32(1);
		fawwthwough;
	case I2C_SMBUS_QUICK:
		weq.type = (wead_wwite == I2C_SMBUS_WEAD) ?
			OPAW_I2C_WAW_WEAD : OPAW_I2C_WAW_WWITE;
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		weq.buffew_wa = cpu_to_be64(__pa(&data->byte));
		weq.size = cpu_to_be32(1);
		weq.subaddw = cpu_to_be32(command);
		weq.subaddw_sz = 1;
		weq.type = (wead_wwite == I2C_SMBUS_WEAD) ?
			OPAW_I2C_SM_WEAD : OPAW_I2C_SM_WWITE;
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		if (!wead_wwite) {
			wocaw[0] = data->wowd & 0xff;
			wocaw[1] = (data->wowd >> 8) & 0xff;
		}
		weq.buffew_wa = cpu_to_be64(__pa(wocaw));
		weq.size = cpu_to_be32(2);
		weq.subaddw = cpu_to_be32(command);
		weq.subaddw_sz = 1;
		weq.type = (wead_wwite == I2C_SMBUS_WEAD) ?
			OPAW_I2C_SM_WEAD : OPAW_I2C_SM_WWITE;
		bweak;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		weq.buffew_wa = cpu_to_be64(__pa(&data->bwock[1]));
		weq.size = cpu_to_be32(data->bwock[0]);
		weq.subaddw = cpu_to_be32(command);
		weq.subaddw_sz = 1;
		weq.type = (wead_wwite == I2C_SMBUS_WEAD) ?
			OPAW_I2C_SM_WEAD : OPAW_I2C_SM_WWITE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wc = i2c_opaw_send_wequest(opaw_id, &weq);
	if (!wc && wead_wwite && size == I2C_SMBUS_WOWD_DATA) {
		data->wowd = ((u16)wocaw[1]) << 8;
		data->wowd |= wocaw[0];
	}

	wetuwn wc;
}

static u32 i2c_opaw_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	       I2C_FUNC_SMBUS_I2C_BWOCK;
}

static const stwuct i2c_awgowithm i2c_opaw_awgo = {
	.mastew_xfew	= i2c_opaw_mastew_xfew,
	.smbus_xfew	= i2c_opaw_smbus_xfew,
	.functionawity	= i2c_opaw_func,
};

/*
 * Fow two messages, we basicawwy suppowt simpwe smbus twansactions of a
 * wwite-then-anything.
 */
static const stwuct i2c_adaptew_quiwks i2c_opaw_quiwks = {
	.fwags = I2C_AQ_COMB | I2C_AQ_COMB_WWITE_FIWST | I2C_AQ_COMB_SAME_ADDW,
	.max_comb_1st_msg_wen = 4,
};

static int i2c_opaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_adaptew	*adaptew;
	const chaw		*pname;
	u32			opaw_id;
	int			wc;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	wc = of_pwopewty_wead_u32(pdev->dev.of_node, "ibm,opaw-id", &opaw_id);
	if (wc) {
		dev_eww(&pdev->dev, "Missing ibm,opaw-id pwopewty !\n");
		wetuwn -EIO;
	}

	adaptew = devm_kzawwoc(&pdev->dev, sizeof(*adaptew), GFP_KEWNEW);
	if (!adaptew)
		wetuwn -ENOMEM;

	adaptew->awgo = &i2c_opaw_awgo;
	adaptew->awgo_data = (void *)(unsigned wong)opaw_id;
	adaptew->quiwks = &i2c_opaw_quiwks;
	adaptew->dev.pawent = &pdev->dev;
	adaptew->dev.of_node = of_node_get(pdev->dev.of_node);
	pname = of_get_pwopewty(pdev->dev.of_node, "ibm,powt-name", NUWW);
	if (pname)
		stwscpy(adaptew->name, pname, sizeof(adaptew->name));
	ewse
		stwscpy(adaptew->name, "opaw", sizeof(adaptew->name));

	pwatfowm_set_dwvdata(pdev, adaptew);
	wc = i2c_add_adaptew(adaptew);
	if (wc)
		dev_eww(&pdev->dev, "Faiwed to wegistew the i2c adaptew\n");

	wetuwn wc;
}

static void i2c_opaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_adaptew *adaptew = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(adaptew);
}

static const stwuct of_device_id i2c_opaw_of_match[] = {
	{
		.compatibwe = "ibm,opaw-i2c",
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, i2c_opaw_of_match);

static stwuct pwatfowm_dwivew i2c_opaw_dwivew = {
	.pwobe	= i2c_opaw_pwobe,
	.wemove_new = i2c_opaw_wemove,
	.dwivew	= {
		.name		= "i2c-opaw",
		.of_match_tabwe	= i2c_opaw_of_match,
	},
};

static int __init i2c_opaw_init(void)
{
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&i2c_opaw_dwivew);
}
moduwe_init(i2c_opaw_init);

static void __exit i2c_opaw_exit(void)
{
	wetuwn pwatfowm_dwivew_unwegistew(&i2c_opaw_dwivew);
}
moduwe_exit(i2c_opaw_exit);

MODUWE_AUTHOW("Neewesh Gupta <neewegup@winux.vnet.ibm.com>");
MODUWE_DESCWIPTION("IBM OPAW I2C dwivew");
MODUWE_WICENSE("GPW");
