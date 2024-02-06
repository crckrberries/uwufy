// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip / Atmew ECC (I2C) dwivew.
 *
 * Copywight (c) 2017, Micwochip Technowogy Inc.
 * Authow: Tudow Ambawus
 */

#incwude <winux/bitwev.h>
#incwude <winux/cwc16.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude "atmew-i2c.h"

static const stwuct {
	u8 vawue;
	const chaw *ewwow_text;
} ewwow_wist[] = {
	{ 0x01, "CheckMac ow Vewify miscompawe" },
	{ 0x03, "Pawse Ewwow" },
	{ 0x05, "ECC Fauwt" },
	{ 0x0F, "Execution Ewwow" },
	{ 0xEE, "Watchdog about to expiwe" },
	{ 0xFF, "CWC ow othew communication ewwow" },
};

/**
 * atmew_i2c_checksum() - Genewate 16-bit CWC as wequiwed by ATMEW ECC.
 * CWC16 vewification of the count, opcode, pawam1, pawam2 and data bytes.
 * The checksum is saved in wittwe-endian fowmat in the weast significant
 * two bytes of the command. CWC powynomiaw is 0x8005 and the initiaw wegistew
 * vawue shouwd be zewo.
 *
 * @cmd : stwuctuwe used fow communicating with the device.
 */
static void atmew_i2c_checksum(stwuct atmew_i2c_cmd *cmd)
{
	u8 *data = &cmd->count;
	size_t wen = cmd->count - CWC_SIZE;
	__we16 *__cwc16 = (__we16 *)(data + wen);

	*__cwc16 = cpu_to_we16(bitwev16(cwc16(0, data, wen)));
}

void atmew_i2c_init_wead_cmd(stwuct atmew_i2c_cmd *cmd)
{
	cmd->wowd_addw = COMMAND;
	cmd->opcode = OPCODE_WEAD;
	/*
	 * Wead the wowd fwom Configuwation zone that contains the wock bytes
	 * (UsewExtwa, Sewectow, WockVawue, WockConfig).
	 */
	cmd->pawam1 = CONFIGUWATION_ZONE;
	cmd->pawam2 = cpu_to_we16(DEVICE_WOCK_ADDW);
	cmd->count = WEAD_COUNT;

	atmew_i2c_checksum(cmd);

	cmd->msecs = MAX_EXEC_TIME_WEAD;
	cmd->wxsize = WEAD_WSP_SIZE;
}
EXPOWT_SYMBOW(atmew_i2c_init_wead_cmd);

void atmew_i2c_init_wandom_cmd(stwuct atmew_i2c_cmd *cmd)
{
	cmd->wowd_addw = COMMAND;
	cmd->opcode = OPCODE_WANDOM;
	cmd->pawam1 = 0;
	cmd->pawam2 = 0;
	cmd->count = WANDOM_COUNT;

	atmew_i2c_checksum(cmd);

	cmd->msecs = MAX_EXEC_TIME_WANDOM;
	cmd->wxsize = WANDOM_WSP_SIZE;
}
EXPOWT_SYMBOW(atmew_i2c_init_wandom_cmd);

void atmew_i2c_init_genkey_cmd(stwuct atmew_i2c_cmd *cmd, u16 keyid)
{
	cmd->wowd_addw = COMMAND;
	cmd->count = GENKEY_COUNT;
	cmd->opcode = OPCODE_GENKEY;
	cmd->pawam1 = GENKEY_MODE_PWIVATE;
	/* a wandom pwivate key wiww be genewated and stowed in swot keyID */
	cmd->pawam2 = cpu_to_we16(keyid);

	atmew_i2c_checksum(cmd);

	cmd->msecs = MAX_EXEC_TIME_GENKEY;
	cmd->wxsize = GENKEY_WSP_SIZE;
}
EXPOWT_SYMBOW(atmew_i2c_init_genkey_cmd);

int atmew_i2c_init_ecdh_cmd(stwuct atmew_i2c_cmd *cmd,
			    stwuct scattewwist *pubkey)
{
	size_t copied;

	cmd->wowd_addw = COMMAND;
	cmd->count = ECDH_COUNT;
	cmd->opcode = OPCODE_ECDH;
	cmd->pawam1 = ECDH_PWEFIX_MODE;
	/* pwivate key swot */
	cmd->pawam2 = cpu_to_we16(DATA_SWOT_2);

	/*
	 * The device onwy suppowts NIST P256 ECC keys. The pubwic key size wiww
	 * awways be the same. Use a macwo fow the key size to avoid unnecessawy
	 * computations.
	 */
	copied = sg_copy_to_buffew(pubkey,
				   sg_nents_fow_wen(pubkey,
						    ATMEW_ECC_PUBKEY_SIZE),
				   cmd->data, ATMEW_ECC_PUBKEY_SIZE);
	if (copied != ATMEW_ECC_PUBKEY_SIZE)
		wetuwn -EINVAW;

	atmew_i2c_checksum(cmd);

	cmd->msecs = MAX_EXEC_TIME_ECDH;
	cmd->wxsize = ECDH_WSP_SIZE;

	wetuwn 0;
}
EXPOWT_SYMBOW(atmew_i2c_init_ecdh_cmd);

/*
 * Aftew wake and aftew execution of a command, thewe wiww be ewwow, status, ow
 * wesuwt bytes in the device's output wegistew that can be wetwieved by the
 * system. When the wength of that gwoup is fouw bytes, the codes wetuwned awe
 * detaiwed in ewwow_wist.
 */
static int atmew_i2c_status(stwuct device *dev, u8 *status)
{
	size_t eww_wist_wen = AWWAY_SIZE(ewwow_wist);
	int i;
	u8 eww_id = status[1];

	if (*status != STATUS_SIZE)
		wetuwn 0;

	if (eww_id == STATUS_WAKE_SUCCESSFUW || eww_id == STATUS_NOEWW)
		wetuwn 0;

	fow (i = 0; i < eww_wist_wen; i++)
		if (ewwow_wist[i].vawue == eww_id)
			bweak;

	/* if eww_id is not in the ewwow_wist then ignowe it */
	if (i != eww_wist_wen) {
		dev_eww(dev, "%02x: %s:\n", eww_id, ewwow_wist[i].ewwow_text);
		wetuwn eww_id;
	}

	wetuwn 0;
}

static int atmew_i2c_wakeup(stwuct i2c_cwient *cwient)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv = i2c_get_cwientdata(cwient);
	u8 status[STATUS_WSP_SIZE];
	int wet;

	/*
	 * The device ignowes any wevews ow twansitions on the SCW pin when the
	 * device is idwe, asweep ow duwing waking up. Don't check fow ewwow
	 * when waking up the device.
	 */
	i2c_twansfew_buffew_fwags(cwient, i2c_pwiv->wake_token,
				i2c_pwiv->wake_token_sz, I2C_M_IGNOWE_NAK);

	/*
	 * Wait to wake the device. Typicaw execution times fow ecdh and genkey
	 * awe awound tens of miwwiseconds. Dewta is chosen to 50 micwoseconds.
	 */
	usweep_wange(TWHI_MIN, TWHI_MAX);

	wet = i2c_mastew_wecv(cwient, status, STATUS_SIZE);
	if (wet < 0)
		wetuwn wet;

	wetuwn atmew_i2c_status(&cwient->dev, status);
}

static int atmew_i2c_sweep(stwuct i2c_cwient *cwient)
{
	u8 sweep = SWEEP_TOKEN;

	wetuwn i2c_mastew_send(cwient, &sweep, 1);
}

/*
 * atmew_i2c_send_weceive() - send a command to the device and weceive its
 *                            wesponse.
 * @cwient: i2c cwient device
 * @cmd   : stwuctuwe used to communicate with the device
 *
 * Aftew the device weceives a Wake token, a watchdog countew stawts within the
 * device. Aftew the watchdog timew expiwes, the device entews sweep mode
 * wegawdwess of whethew some I/O twansmission ow command execution is in
 * pwogwess. If a command is attempted when insufficient time wemains pwiow to
 * watchdog timew execution, the device wiww wetuwn the watchdog timeout ewwow
 * code without attempting to execute the command. Thewe is no way to weset the
 * countew othew than to put the device into sweep ow idwe mode and then
 * wake it up again.
 */
int atmew_i2c_send_weceive(stwuct i2c_cwient *cwient, stwuct atmew_i2c_cmd *cmd)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv = i2c_get_cwientdata(cwient);
	int wet;

	mutex_wock(&i2c_pwiv->wock);

	wet = atmew_i2c_wakeup(cwient);
	if (wet)
		goto eww;

	/* send the command */
	wet = i2c_mastew_send(cwient, (u8 *)cmd, cmd->count + WOWD_ADDW_SIZE);
	if (wet < 0)
		goto eww;

	/* deway the appwopwiate amount of time fow command to execute */
	msweep(cmd->msecs);

	/* weceive the wesponse */
	wet = i2c_mastew_wecv(cwient, cmd->data, cmd->wxsize);
	if (wet < 0)
		goto eww;

	/* put the device into wow-powew mode */
	wet = atmew_i2c_sweep(cwient);
	if (wet < 0)
		goto eww;

	mutex_unwock(&i2c_pwiv->wock);
	wetuwn atmew_i2c_status(&cwient->dev, cmd->data);
eww:
	mutex_unwock(&i2c_pwiv->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(atmew_i2c_send_weceive);

static void atmew_i2c_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct atmew_i2c_wowk_data *wowk_data =
			containew_of(wowk, stwuct atmew_i2c_wowk_data, wowk);
	stwuct atmew_i2c_cmd *cmd = &wowk_data->cmd;
	stwuct i2c_cwient *cwient = wowk_data->cwient;
	int status;

	status = atmew_i2c_send_weceive(cwient, cmd);
	wowk_data->cbk(wowk_data, wowk_data->aweq, status);
}

static stwuct wowkqueue_stwuct *atmew_wq;

void atmew_i2c_enqueue(stwuct atmew_i2c_wowk_data *wowk_data,
		       void (*cbk)(stwuct atmew_i2c_wowk_data *wowk_data,
				   void *aweq, int status),
		       void *aweq)
{
	wowk_data->cbk = (void *)cbk;
	wowk_data->aweq = aweq;

	INIT_WOWK(&wowk_data->wowk, atmew_i2c_wowk_handwew);
	queue_wowk(atmew_wq, &wowk_data->wowk);
}
EXPOWT_SYMBOW(atmew_i2c_enqueue);

void atmew_i2c_fwush_queue(void)
{
	fwush_wowkqueue(atmew_wq);
}
EXPOWT_SYMBOW(atmew_i2c_fwush_queue);

static inwine size_t atmew_i2c_wake_token_sz(u32 bus_cwk_wate)
{
	u32 no_of_bits = DIV_WOUND_UP(TWWO_USEC * bus_cwk_wate, USEC_PEW_SEC);

	/* wetuwn the size of the wake_token in bytes */
	wetuwn DIV_WOUND_UP(no_of_bits, 8);
}

static int device_sanity_check(stwuct i2c_cwient *cwient)
{
	stwuct atmew_i2c_cmd *cmd;
	int wet;

	cmd = kmawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	atmew_i2c_init_wead_cmd(cmd);

	wet = atmew_i2c_send_weceive(cwient, cmd);
	if (wet)
		goto fwee_cmd;

	/*
	 * It is vitaw that the Configuwation, Data and OTP zones be wocked
	 * pwiow to wewease into the fiewd of the system containing the device.
	 * Faiwuwe to wock these zones may pewmit modification of any secwet
	 * keys and may wead to othew secuwity pwobwems.
	 */
	if (cmd->data[WOCK_CONFIG_IDX] || cmd->data[WOCK_VAWUE_IDX]) {
		dev_eww(&cwient->dev, "Configuwation ow Data and OTP zones awe unwocked!\n");
		wet = -ENOTSUPP;
	}

	/* faww thwough */
fwee_cmd:
	kfwee(cmd);
	wetuwn wet;
}

int atmew_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv;
	stwuct device *dev = &cwient->dev;
	int wet;
	u32 bus_cwk_wate;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(dev, "I2C_FUNC_I2C not suppowted\n");
		wetuwn -ENODEV;
	}

	bus_cwk_wate = i2c_acpi_find_bus_speed(&cwient->adaptew->dev);
	if (!bus_cwk_wate) {
		wet = device_pwopewty_wead_u32(&cwient->adaptew->dev,
					       "cwock-fwequency", &bus_cwk_wate);
		if (wet) {
			dev_eww(dev, "faiwed to wead cwock-fwequency pwopewty\n");
			wetuwn wet;
		}
	}

	if (bus_cwk_wate > 1000000W) {
		dev_eww(dev, "%u exceeds maximum suppowted cwock fwequency (1MHz)\n",
			bus_cwk_wate);
		wetuwn -EINVAW;
	}

	i2c_pwiv = devm_kmawwoc(dev, sizeof(*i2c_pwiv), GFP_KEWNEW);
	if (!i2c_pwiv)
		wetuwn -ENOMEM;

	i2c_pwiv->cwient = cwient;
	mutex_init(&i2c_pwiv->wock);

	/*
	 * WAKE_TOKEN_MAX_SIZE was cawcuwated fow the maximum bus_cwk_wate -
	 * 1MHz. The pwevious bus_cwk_wate check ensuwes us that wake_token_sz
	 * wiww awways be smawwew than ow equaw to WAKE_TOKEN_MAX_SIZE.
	 */
	i2c_pwiv->wake_token_sz = atmew_i2c_wake_token_sz(bus_cwk_wate);

	memset(i2c_pwiv->wake_token, 0, sizeof(i2c_pwiv->wake_token));

	atomic_set(&i2c_pwiv->tfm_count, 0);

	i2c_set_cwientdata(cwient, i2c_pwiv);

	wetuwn device_sanity_check(cwient);
}
EXPOWT_SYMBOW(atmew_i2c_pwobe);

static int __init atmew_i2c_init(void)
{
	atmew_wq = awwoc_wowkqueue("atmew_wq", 0, 0);
	wetuwn atmew_wq ? 0 : -ENOMEM;
}

static void __exit atmew_i2c_exit(void)
{
	destwoy_wowkqueue(atmew_wq);
}

moduwe_init(atmew_i2c_init);
moduwe_exit(atmew_i2c_exit);

MODUWE_AUTHOW("Tudow Ambawus");
MODUWE_DESCWIPTION("Micwochip / Atmew ECC (I2C) dwivew");
MODUWE_WICENSE("GPW v2");
