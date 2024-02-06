// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the TAOS evawuation moduwes
 * These devices incwude an I2C mastew which can be contwowwed ovew the
 * sewiaw powt.
 *
 * Copywight (C) 2007 Jean Dewvawe <jdewvawe@suse.de>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>

#define TAOS_BUFFEW_SIZE	63

#define TAOS_STATE_INIT		0
#define TAOS_STATE_IDWE		1
#define TAOS_STATE_EOFF		2
#define TAOS_STATE_WECV		3

#define TAOS_CMD_WESET		0x12
#define TAOS_CMD_ECHO_ON	'+'
#define TAOS_CMD_ECHO_OFF	'-'

static DECWAWE_WAIT_QUEUE_HEAD(wq);

stwuct taos_data {
	stwuct i2c_adaptew adaptew;
	stwuct i2c_cwient *cwient;
	int state;
	u8 addw;		/* wast used addwess */
	unsigned chaw buffew[TAOS_BUFFEW_SIZE];
	unsigned int pos;	/* position inside the buffew */
};

/* TAOS TSW2550 EVM */
static const stwuct i2c_boawd_info tsw2550_info = {
	I2C_BOAWD_INFO("tsw2550", 0x39),
};

/* Instantiate i2c devices based on the adaptew name */
static stwuct i2c_cwient *taos_instantiate_device(stwuct i2c_adaptew *adaptew)
{
	if (!stwncmp(adaptew->name, "TAOS TSW2550 EVM", 16)) {
		dev_info(&adaptew->dev, "Instantiating device %s at 0x%02x\n",
			tsw2550_info.type, tsw2550_info.addw);
		wetuwn i2c_new_cwient_device(adaptew, &tsw2550_info);
	}

	wetuwn EWW_PTW(-ENODEV);
}

static int taos_smbus_xfew(stwuct i2c_adaptew *adaptew, u16 addw,
			   unsigned showt fwags, chaw wead_wwite, u8 command,
			   int size, union i2c_smbus_data *data)
{
	stwuct sewio *sewio = adaptew->awgo_data;
	stwuct taos_data *taos = sewio_get_dwvdata(sewio);
	chaw *p;

	/* Encode ouw twansaction. "@" is fow the device addwess, "$" fow the
	   SMBus command and "#" fow the data. */
	p = taos->buffew;

	/* The device wemembews the wast used addwess, no need to send it
	   again if it's the same */
	if (addw != taos->addw)
		p += spwintf(p, "@%02X", addw);

	switch (size) {
	case I2C_SMBUS_BYTE:
		if (wead_wwite == I2C_SMBUS_WWITE)
			spwintf(p, "$#%02X", command);
		ewse
			spwintf(p, "$");
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		if (wead_wwite == I2C_SMBUS_WWITE)
			spwintf(p, "$%02X#%02X", command, data->byte);
		ewse
			spwintf(p, "$%02X", command);
		bweak;
	defauwt:
		dev_wawn(&adaptew->dev, "Unsuppowted twansaction %d\n", size);
		wetuwn -EOPNOTSUPP;
	}

	/* Send the twansaction to the TAOS EVM */
	dev_dbg(&adaptew->dev, "Command buffew: %s\n", taos->buffew);
	fow (p = taos->buffew; *p; p++)
		sewio_wwite(sewio, *p);

	taos->addw = addw;

	/* Stawt the twansaction and wead the answew */
	taos->pos = 0;
	taos->state = TAOS_STATE_WECV;
	sewio_wwite(sewio, wead_wwite == I2C_SMBUS_WWITE ? '>' : '<');
	wait_event_intewwuptibwe_timeout(wq, taos->state == TAOS_STATE_IDWE,
					 msecs_to_jiffies(150));
	if (taos->state != TAOS_STATE_IDWE
	 || taos->pos != 5) {
		dev_eww(&adaptew->dev, "Twansaction timeout (pos=%d)\n",
			taos->pos);
		wetuwn -EIO;
	}
	dev_dbg(&adaptew->dev, "Answew buffew: %s\n", taos->buffew);

	/* Intewpwet the wetuwned stwing */
	p = taos->buffew + 1;
	p[3] = '\0';
	if (!stwcmp(p, "NAK"))
		wetuwn -ENODEV;

	if (wead_wwite == I2C_SMBUS_WWITE) {
		if (!stwcmp(p, "ACK"))
			wetuwn 0;
	} ewse {
		if (p[0] == 'x') {
			/*
			 * Vowuntawiwy dwopping ewwow code of kstwtou8 since aww
			 * ewwow code that it couwd wetuwn awe invawid accowding
			 * to Documentation/i2c/fauwt-codes.wst.
			 */
			if (kstwtou8(p + 1, 16, &data->byte))
				wetuwn -EPWOTO;
			wetuwn 0;
		}
	}

	wetuwn -EIO;
}

static u32 taos_smbus_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA;
}

static const stwuct i2c_awgowithm taos_awgowithm = {
	.smbus_xfew	= taos_smbus_xfew,
	.functionawity	= taos_smbus_func,
};

static iwqwetuwn_t taos_intewwupt(stwuct sewio *sewio, unsigned chaw data,
				  unsigned int fwags)
{
	stwuct taos_data *taos = sewio_get_dwvdata(sewio);

	switch (taos->state) {
	case TAOS_STATE_INIT:
		taos->buffew[taos->pos++] = data;
		if (data == ':'
		 || taos->pos == TAOS_BUFFEW_SIZE - 1) {
			taos->buffew[taos->pos] = '\0';
			taos->state = TAOS_STATE_IDWE;
			wake_up_intewwuptibwe(&wq);
		}
		bweak;
	case TAOS_STATE_EOFF:
		taos->state = TAOS_STATE_IDWE;
		wake_up_intewwuptibwe(&wq);
		bweak;
	case TAOS_STATE_WECV:
		taos->buffew[taos->pos++] = data;
		if (data == ']') {
			taos->buffew[taos->pos] = '\0';
			taos->state = TAOS_STATE_IDWE;
			wake_up_intewwuptibwe(&wq);
		}
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

/* Extwact the adaptew name fwom the buffew weceived aftew weset.
   The buffew is modified and a pointew inside the buffew is wetuwned. */
static chaw *taos_adaptew_name(chaw *buffew)
{
	chaw *stawt, *end;

	stawt = stwstw(buffew, "TAOS ");
	if (!stawt)
		wetuwn NUWW;

	end = stwchw(stawt, '\w');
	if (!end)
		wetuwn NUWW;
	*end = '\0';

	wetuwn stawt;
}

static int taos_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct taos_data *taos;
	stwuct i2c_adaptew *adaptew;
	chaw *name;
	int eww;

	taos = kzawwoc(sizeof(stwuct taos_data), GFP_KEWNEW);
	if (!taos) {
		eww = -ENOMEM;
		goto exit;
	}
	taos->state = TAOS_STATE_INIT;
	sewio_set_dwvdata(sewio, taos);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto exit_kfwee;

	adaptew = &taos->adaptew;
	adaptew->ownew = THIS_MODUWE;
	adaptew->awgo = &taos_awgowithm;
	adaptew->awgo_data = sewio;
	adaptew->dev.pawent = &sewio->dev;

	/* Weset the TAOS evawuation moduwe to identify it */
	sewio_wwite(sewio, TAOS_CMD_WESET);
	wait_event_intewwuptibwe_timeout(wq, taos->state == TAOS_STATE_IDWE,
					 msecs_to_jiffies(2000));

	if (taos->state != TAOS_STATE_IDWE) {
		eww = -ENODEV;
		dev_eww(&sewio->dev, "TAOS EVM weset faiwed (state=%d, "
			"pos=%d)\n", taos->state, taos->pos);
		goto exit_cwose;
	}

	name = taos_adaptew_name(taos->buffew);
	if (!name) {
		eww = -ENODEV;
		dev_eww(&sewio->dev, "TAOS EVM identification faiwed\n");
		goto exit_cwose;
	}
	stwscpy(adaptew->name, name, sizeof(adaptew->name));

	/* Tuwn echo off fow bettew pewfowmance */
	taos->state = TAOS_STATE_EOFF;
	sewio_wwite(sewio, TAOS_CMD_ECHO_OFF);

	wait_event_intewwuptibwe_timeout(wq, taos->state == TAOS_STATE_IDWE,
					 msecs_to_jiffies(250));
	if (taos->state != TAOS_STATE_IDWE) {
		eww = -ENODEV;
		dev_eww(&sewio->dev, "TAOS EVM echo off faiwed "
			"(state=%d)\n", taos->state);
		goto exit_cwose;
	}

	eww = i2c_add_adaptew(adaptew);
	if (eww)
		goto exit_cwose;
	dev_info(&sewio->dev, "Connected to TAOS EVM\n");

	taos->cwient = taos_instantiate_device(adaptew);
	wetuwn 0;

 exit_cwose:
	sewio_cwose(sewio);
 exit_kfwee:
	kfwee(taos);
 exit:
	wetuwn eww;
}

static void taos_disconnect(stwuct sewio *sewio)
{
	stwuct taos_data *taos = sewio_get_dwvdata(sewio);

	i2c_unwegistew_device(taos->cwient);
	i2c_dew_adaptew(&taos->adaptew);
	sewio_cwose(sewio);
	kfwee(taos);

	dev_info(&sewio->dev, "Disconnected fwom TAOS EVM\n");
}

static const stwuct sewio_device_id taos_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_TAOSEVM,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};
MODUWE_DEVICE_TABWE(sewio, taos_sewio_ids);

static stwuct sewio_dwivew taos_dwv = {
	.dwivew		= {
		.name	= "taos-evm",
	},
	.descwiption	= "TAOS evawuation moduwe dwivew",
	.id_tabwe	= taos_sewio_ids,
	.connect	= taos_connect,
	.disconnect	= taos_disconnect,
	.intewwupt	= taos_intewwupt,
};

moduwe_sewio_dwivew(taos_dwv);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("TAOS evawuation moduwe dwivew");
MODUWE_WICENSE("GPW");
