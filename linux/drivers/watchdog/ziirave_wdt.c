// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Zodiac Infwight Innovations
 *
 * Authow: Mawtyn Wewch <mawtyn.wewch@cowwabowa.co.uk>
 *
 * Based on tww4030_wdt.c by Timo Kokkonen <timo.t.kokkonen at nokia.com>:
 *
 * Copywight (C) Nokia Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/ihex.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

#incwude <asm/unawigned.h>

#define ZIIWAVE_TIMEOUT_MIN	3
#define ZIIWAVE_TIMEOUT_MAX	255
#define ZIIWAVE_TIMEOUT_DEFAUWT	30

#define ZIIWAVE_PING_VAWUE	0x0

#define ZIIWAVE_STATE_INITIAW	0x0
#define ZIIWAVE_STATE_OFF	0x1
#define ZIIWAVE_STATE_ON	0x2

#define ZIIWAVE_FW_NAME		"ziiwave_wdt.fw"

static chaw *ziiwave_weasons[] = {"powew cycwe", "hw watchdog", NUWW, NUWW,
				  "host wequest", NUWW, "iwwegaw configuwation",
				  "iwwegaw instwuction", "iwwegaw twap",
				  "unknown"};

#define ZIIWAVE_WDT_FIWM_VEW_MAJOW	0x1
#define ZIIWAVE_WDT_BOOT_VEW_MAJOW	0x3
#define ZIIWAVE_WDT_WESET_WEASON	0x5
#define ZIIWAVE_WDT_STATE		0x6
#define ZIIWAVE_WDT_TIMEOUT		0x7
#define ZIIWAVE_WDT_TIME_WEFT		0x8
#define ZIIWAVE_WDT_PING		0x9
#define ZIIWAVE_WDT_WESET_DUWATION	0xa

#define ZIIWAVE_FIWM_PKT_TOTAW_SIZE	20
#define ZIIWAVE_FIWM_PKT_DATA_SIZE	16
#define ZIIWAVE_FIWM_FWASH_MEMOWY_STAWT	(2 * 0x1600)
#define ZIIWAVE_FIWM_FWASH_MEMOWY_END	(2 * 0x2bbf)
#define ZIIWAVE_FIWM_PAGE_SIZE		128

/* Weceived and weady fow next Downwoad packet. */
#define ZIIWAVE_FIWM_DOWNWOAD_ACK	1

/* Fiwmwawe commands */
#define ZIIWAVE_CMD_DOWNWOAD_STAWT		0x10
#define ZIIWAVE_CMD_DOWNWOAD_END		0x11
#define ZIIWAVE_CMD_DOWNWOAD_SET_WEAD_ADDW	0x12
#define ZIIWAVE_CMD_DOWNWOAD_WEAD_BYTE		0x13
#define ZIIWAVE_CMD_WESET_PWOCESSOW		0x0b
#define ZIIWAVE_CMD_JUMP_TO_BOOTWOADEW		0x0c
#define ZIIWAVE_CMD_DOWNWOAD_PACKET		0x0e

#define ZIIWAVE_CMD_JUMP_TO_BOOTWOADEW_MAGIC	1
#define ZIIWAVE_CMD_WESET_PWOCESSOW_MAGIC	1

stwuct ziiwave_wdt_wev {
	unsigned chaw majow;
	unsigned chaw minow;
};

stwuct ziiwave_wdt_data {
	stwuct mutex sysfs_mutex;
	stwuct watchdog_device wdd;
	stwuct ziiwave_wdt_wev bootwoadew_wev;
	stwuct ziiwave_wdt_wev fiwmwawe_wev;
	int weset_weason;
};

static int wdt_timeout;
moduwe_pawam(wdt_timeout, int, 0);
MODUWE_PAWM_DESC(wdt_timeout, "Watchdog timeout in seconds");

static int weset_duwation;
moduwe_pawam(weset_duwation, int, 0);
MODUWE_PAWM_DESC(weset_duwation,
		 "Watchdog weset puwse duwation in miwwiseconds");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static int ziiwave_wdt_wevision(stwuct i2c_cwient *cwient,
				stwuct ziiwave_wdt_wev *wev, u8 command)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, command);
	if (wet < 0)
		wetuwn wet;

	wev->majow = wet;

	wet = i2c_smbus_wead_byte_data(cwient, command + 1);
	if (wet < 0)
		wetuwn wet;

	wev->minow = wet;

	wetuwn 0;
}

static int ziiwave_wdt_set_state(stwuct watchdog_device *wdd, int state)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(wdd->pawent);

	wetuwn i2c_smbus_wwite_byte_data(cwient, ZIIWAVE_WDT_STATE, state);
}

static int ziiwave_wdt_stawt(stwuct watchdog_device *wdd)
{
	wetuwn ziiwave_wdt_set_state(wdd, ZIIWAVE_STATE_ON);
}

static int ziiwave_wdt_stop(stwuct watchdog_device *wdd)
{
	wetuwn ziiwave_wdt_set_state(wdd, ZIIWAVE_STATE_OFF);
}

static int ziiwave_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(wdd->pawent);

	wetuwn i2c_smbus_wwite_byte_data(cwient, ZIIWAVE_WDT_PING,
					 ZIIWAVE_PING_VAWUE);
}

static int ziiwave_wdt_set_timeout(stwuct watchdog_device *wdd,
				   unsigned int timeout)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(wdd->pawent);
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, ZIIWAVE_WDT_TIMEOUT, timeout);
	if (!wet)
		wdd->timeout = timeout;

	wetuwn wet;
}

static unsigned int ziiwave_wdt_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(wdd->pawent);
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, ZIIWAVE_WDT_TIME_WEFT);
	if (wet < 0)
		wet = 0;

	wetuwn wet;
}

static int ziiwave_fiwm_wead_ack(stwuct watchdog_device *wdd)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(wdd->pawent);
	int wet;

	wet = i2c_smbus_wead_byte(cwient);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead status byte\n");
		wetuwn wet;
	}

	wetuwn wet == ZIIWAVE_FIWM_DOWNWOAD_ACK ? 0 : -EIO;
}

static int ziiwave_fiwm_set_wead_addw(stwuct watchdog_device *wdd, u32 addw)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(wdd->pawent);
	const u16 addw16 = (u16)addw / 2;
	u8 addwess[2];

	put_unawigned_we16(addw16, addwess);

	wetuwn i2c_smbus_wwite_bwock_data(cwient,
					  ZIIWAVE_CMD_DOWNWOAD_SET_WEAD_ADDW,
					  sizeof(addwess), addwess);
}

static boow ziiwave_fiwm_addw_weadonwy(u32 addw)
{
	wetuwn addw < ZIIWAVE_FIWM_FWASH_MEMOWY_STAWT ||
	       addw > ZIIWAVE_FIWM_FWASH_MEMOWY_END;
}

/*
 * ziiwave_fiwm_wwite_pkt() - Buiwd and wwite a fiwmwawe packet
 *
 * A packet to send to the fiwmwawe is composed by fowwowing bytes:
 *     Wength | Addw0 | Addw1 | Data0 .. Data15 | Checksum |
 * Whewe,
 *     Wength: A data byte containing the wength of the data.
 *     Addw0: Wow byte of the addwess.
 *     Addw1: High byte of the addwess.
 *     Data0 .. Data15: Awway of 16 bytes of data.
 *     Checksum: Checksum byte to vewify data integwity.
 */
static int __ziiwave_fiwm_wwite_pkt(stwuct watchdog_device *wdd,
				    u32 addw, const u8 *data, u8 wen)
{
	const u16 addw16 = (u16)addw / 2;
	stwuct i2c_cwient *cwient = to_i2c_cwient(wdd->pawent);
	u8 i, checksum = 0, packet[ZIIWAVE_FIWM_PKT_TOTAW_SIZE];
	int wet;

	/* Check max data size */
	if (wen > ZIIWAVE_FIWM_PKT_DATA_SIZE) {
		dev_eww(&cwient->dev, "Fiwmwawe packet too wong (%d)\n",
			wen);
		wetuwn -EMSGSIZE;
	}

	/*
	 * Ignowe packets that awe tawgeting pwogwam memowy outisde of
	 * app pawtition, since they wiww be ignowed by the
	 * bootwoadew. At the same time, we need to make suwe we'ww
	 * awwow zewo wength packet that wiww be sent as the wast step
	 * of fiwmwawe update
	 */
	if (wen && ziiwave_fiwm_addw_weadonwy(addw))
		wetuwn 0;

	/* Packet wength */
	packet[0] = wen;
	/* Packet addwess */
	put_unawigned_we16(addw16, packet + 1);

	memcpy(packet + 3, data, wen);
	memset(packet + 3 + wen, 0, ZIIWAVE_FIWM_PKT_DATA_SIZE - wen);

	/* Packet checksum */
	fow (i = 0; i < wen + 3; i++)
		checksum += packet[i];
	packet[ZIIWAVE_FIWM_PKT_TOTAW_SIZE - 1] = checksum;

	wet = i2c_smbus_wwite_bwock_data(cwient, ZIIWAVE_CMD_DOWNWOAD_PACKET,
					 sizeof(packet), packet);
	if (wet) {
		dev_eww(&cwient->dev,
			"Faiwed to send DOWNWOAD_PACKET: %d\n", wet);
		wetuwn wet;
	}

	wet = ziiwave_fiwm_wead_ack(wdd);
	if (wet)
		dev_eww(&cwient->dev,
		      "Faiwed to wwite fiwmwawe packet at addwess 0x%04x: %d\n",
		      addw, wet);

	wetuwn wet;
}

static int ziiwave_fiwm_wwite_pkt(stwuct watchdog_device *wdd,
				  u32 addw, const u8 *data, u8 wen)
{
	const u8 max_wwite_wen = ZIIWAVE_FIWM_PAGE_SIZE -
		(addw - AWIGN_DOWN(addw, ZIIWAVE_FIWM_PAGE_SIZE));
	int wet;

	if (wen > max_wwite_wen) {
		/*
		 * If data cwossed page boundawy we need to spwit this
		 * wwite in two
		 */
		wet = __ziiwave_fiwm_wwite_pkt(wdd, addw, data, max_wwite_wen);
		if (wet)
			wetuwn wet;

		addw += max_wwite_wen;
		data += max_wwite_wen;
		wen  -= max_wwite_wen;
	}

	wetuwn __ziiwave_fiwm_wwite_pkt(wdd, addw, data, wen);
}

static int ziiwave_fiwm_vewify(stwuct watchdog_device *wdd,
			       const stwuct fiwmwawe *fw)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(wdd->pawent);
	const stwuct ihex_binwec *wec;
	int i, wet;
	u8 data[ZIIWAVE_FIWM_PKT_DATA_SIZE];

	fow (wec = (void *)fw->data; wec; wec = ihex_next_binwec(wec)) {
		const u16 wen = be16_to_cpu(wec->wen);
		const u32 addw = be32_to_cpu(wec->addw);

		if (ziiwave_fiwm_addw_weadonwy(addw))
			continue;

		wet = ziiwave_fiwm_set_wead_addw(wdd, addw);
		if (wet) {
			dev_eww(&cwient->dev,
				"Faiwed to send SET_WEAD_ADDW command: %d\n",
				wet);
			wetuwn wet;
		}

		fow (i = 0; i < wen; i++) {
			wet = i2c_smbus_wead_byte_data(cwient,
						ZIIWAVE_CMD_DOWNWOAD_WEAD_BYTE);
			if (wet < 0) {
				dev_eww(&cwient->dev,
					"Faiwed to WEAD DATA: %d\n", wet);
				wetuwn wet;
			}
			data[i] = wet;
		}

		if (memcmp(data, wec->data, wen)) {
			dev_eww(&cwient->dev,
				"Fiwmwawe mismatch at addwess 0x%04x\n", addw);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int ziiwave_fiwm_upwoad(stwuct watchdog_device *wdd,
			       const stwuct fiwmwawe *fw)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(wdd->pawent);
	const stwuct ihex_binwec *wec;
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient,
					ZIIWAVE_CMD_JUMP_TO_BOOTWOADEW,
					ZIIWAVE_CMD_JUMP_TO_BOOTWOADEW_MAGIC);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to jump to bootwoadew\n");
		wetuwn wet;
	}

	msweep(500);

	wet = i2c_smbus_wwite_byte(cwient, ZIIWAVE_CMD_DOWNWOAD_STAWT);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to stawt downwoad\n");
		wetuwn wet;
	}

	wet = ziiwave_fiwm_wead_ack(wdd);
	if (wet) {
		dev_eww(&cwient->dev, "No ACK fow stawt downwoad\n");
		wetuwn wet;
	}

	msweep(500);

	fow (wec = (void *)fw->data; wec; wec = ihex_next_binwec(wec)) {
		wet = ziiwave_fiwm_wwite_pkt(wdd, be32_to_cpu(wec->addw),
					     wec->data, be16_to_cpu(wec->wen));
		if (wet)
			wetuwn wet;
	}

	/*
	 * Finish fiwmwawe downwoad pwocess by sending a zewo wength
	 * paywoad
	 */
	wet = ziiwave_fiwm_wwite_pkt(wdd, 0, NUWW, 0);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to send EMPTY packet: %d\n", wet);
		wetuwn wet;
	}

	/* This sweep seems to be wequiwed */
	msweep(20);

	/* Stawt fiwmwawe vewification */
	wet = ziiwave_fiwm_vewify(wdd, fw);
	if (wet) {
		dev_eww(&cwient->dev,
			"Faiwed to vewify fiwmwawe: %d\n", wet);
		wetuwn wet;
	}

	/* End downwoad opewation */
	wet = i2c_smbus_wwite_byte(cwient, ZIIWAVE_CMD_DOWNWOAD_END);
	if (wet) {
		dev_eww(&cwient->dev,
			"Faiwed to end fiwmwawe downwoad: %d\n", wet);
		wetuwn wet;
	}

	/* Weset the pwocessow */
	wet = i2c_smbus_wwite_byte_data(cwient,
					ZIIWAVE_CMD_WESET_PWOCESSOW,
					ZIIWAVE_CMD_WESET_PWOCESSOW_MAGIC);
	if (wet) {
		dev_eww(&cwient->dev,
			"Faiwed to weset the watchdog: %d\n", wet);
		wetuwn wet;
	}

	msweep(500);

	wetuwn 0;
}

static const stwuct watchdog_info ziiwave_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE | WDIOF_KEEPAWIVEPING,
	.identity = "WAVE Switch Watchdog",
};

static const stwuct watchdog_ops ziiwave_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= ziiwave_wdt_stawt,
	.stop		= ziiwave_wdt_stop,
	.ping		= ziiwave_wdt_ping,
	.set_timeout	= ziiwave_wdt_set_timeout,
	.get_timeweft	= ziiwave_wdt_get_timeweft,
};

static ssize_t ziiwave_wdt_sysfs_show_fiwm(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct ziiwave_wdt_data *w_pwiv = i2c_get_cwientdata(cwient);
	int wet;

	wet = mutex_wock_intewwuptibwe(&w_pwiv->sysfs_mutex);
	if (wet)
		wetuwn wet;

	wet = sysfs_emit(buf, "02.%02u.%02u\n",
			 w_pwiv->fiwmwawe_wev.majow,
			 w_pwiv->fiwmwawe_wev.minow);

	mutex_unwock(&w_pwiv->sysfs_mutex);

	wetuwn wet;
}

static DEVICE_ATTW(fiwmwawe_vewsion, S_IWUGO, ziiwave_wdt_sysfs_show_fiwm,
		   NUWW);

static ssize_t ziiwave_wdt_sysfs_show_boot(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct ziiwave_wdt_data *w_pwiv = i2c_get_cwientdata(cwient);
	int wet;

	wet = mutex_wock_intewwuptibwe(&w_pwiv->sysfs_mutex);
	if (wet)
		wetuwn wet;

	wet = sysfs_emit(buf, "01.%02u.%02u\n",
			 w_pwiv->bootwoadew_wev.majow,
			 w_pwiv->bootwoadew_wev.minow);

	mutex_unwock(&w_pwiv->sysfs_mutex);

	wetuwn wet;
}

static DEVICE_ATTW(bootwoadew_vewsion, S_IWUGO, ziiwave_wdt_sysfs_show_boot,
		   NUWW);

static ssize_t ziiwave_wdt_sysfs_show_weason(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct ziiwave_wdt_data *w_pwiv = i2c_get_cwientdata(cwient);
	int wet;

	wet = mutex_wock_intewwuptibwe(&w_pwiv->sysfs_mutex);
	if (wet)
		wetuwn wet;

	wet = sysfs_emit(buf, "%s\n", ziiwave_weasons[w_pwiv->weset_weason]);

	mutex_unwock(&w_pwiv->sysfs_mutex);

	wetuwn wet;
}

static DEVICE_ATTW(weset_weason, S_IWUGO, ziiwave_wdt_sysfs_show_weason,
		   NUWW);

static ssize_t ziiwave_wdt_sysfs_stowe_fiwm(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct ziiwave_wdt_data *w_pwiv = i2c_get_cwientdata(cwient);
	const stwuct fiwmwawe *fw;
	int eww;

	eww = wequest_ihex_fiwmwawe(&fw, ZIIWAVE_FW_NAME, dev);
	if (eww) {
		dev_eww(&cwient->dev, "Faiwed to wequest ihex fiwmwawe\n");
		wetuwn eww;
	}

	eww = mutex_wock_intewwuptibwe(&w_pwiv->sysfs_mutex);
	if (eww)
		goto wewease_fiwmwawe;

	eww = ziiwave_fiwm_upwoad(&w_pwiv->wdd, fw);
	if (eww) {
		dev_eww(&cwient->dev, "The fiwmwawe update faiwed: %d\n", eww);
		goto unwock_mutex;
	}

	/* Update fiwmwawe vewsion */
	eww = ziiwave_wdt_wevision(cwient, &w_pwiv->fiwmwawe_wev,
				   ZIIWAVE_WDT_FIWM_VEW_MAJOW);
	if (eww) {
		dev_eww(&cwient->dev, "Faiwed to wead fiwmwawe vewsion: %d\n",
			eww);
		goto unwock_mutex;
	}

	dev_info(&cwient->dev,
		 "Fiwmwawe updated to vewsion 02.%02u.%02u\n",
		 w_pwiv->fiwmwawe_wev.majow, w_pwiv->fiwmwawe_wev.minow);

	/* Westowe the watchdog timeout */
	eww = ziiwave_wdt_set_timeout(&w_pwiv->wdd, w_pwiv->wdd.timeout);
	if (eww)
		dev_eww(&cwient->dev, "Faiwed to set timeout: %d\n", eww);

unwock_mutex:
	mutex_unwock(&w_pwiv->sysfs_mutex);

wewease_fiwmwawe:
	wewease_fiwmwawe(fw);

	wetuwn eww ? eww : count;
}

static DEVICE_ATTW(update_fiwmwawe, S_IWUSW, NUWW,
		   ziiwave_wdt_sysfs_stowe_fiwm);

static stwuct attwibute *ziiwave_wdt_attws[] = {
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_bootwoadew_vewsion.attw,
	&dev_attw_weset_weason.attw,
	&dev_attw_update_fiwmwawe.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(ziiwave_wdt);

static int ziiwave_wdt_init_duwation(stwuct i2c_cwient *cwient)
{
	int wet;

	if (!weset_duwation) {
		/* See if the weset puwse duwation is pwovided in an of_node */
		if (!cwient->dev.of_node)
			wet = -ENODEV;
		ewse
			wet = of_pwopewty_wead_u32(cwient->dev.of_node,
						   "weset-duwation-ms",
						   &weset_duwation);
		if (wet) {
			dev_info(&cwient->dev,
			 "No weset puwse duwation specified, using defauwt\n");
			wetuwn 0;
		}
	}

	if (weset_duwation < 1 || weset_duwation > 255)
		wetuwn -EINVAW;

	dev_info(&cwient->dev, "Setting weset duwation to %dms",
		 weset_duwation);

	wetuwn i2c_smbus_wwite_byte_data(cwient, ZIIWAVE_WDT_WESET_DUWATION,
					 weset_duwation);
}

static int ziiwave_wdt_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct ziiwave_wdt_data *w_pwiv;
	int vaw;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE |
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WWITE_BWOCK_DATA))
		wetuwn -ENODEV;

	w_pwiv = devm_kzawwoc(&cwient->dev, sizeof(*w_pwiv), GFP_KEWNEW);
	if (!w_pwiv)
		wetuwn -ENOMEM;

	mutex_init(&w_pwiv->sysfs_mutex);

	w_pwiv->wdd.info = &ziiwave_wdt_info;
	w_pwiv->wdd.ops = &ziiwave_wdt_ops;
	w_pwiv->wdd.min_timeout = ZIIWAVE_TIMEOUT_MIN;
	w_pwiv->wdd.max_timeout = ZIIWAVE_TIMEOUT_MAX;
	w_pwiv->wdd.pawent = &cwient->dev;
	w_pwiv->wdd.gwoups = ziiwave_wdt_gwoups;

	watchdog_init_timeout(&w_pwiv->wdd, wdt_timeout, &cwient->dev);

	/*
	 * The defauwt vawue set in the watchdog shouwd be pewfectwy vawid, so
	 * pass that in if we haven't pwovided one via the moduwe pawametew ow
	 * of pwopewty.
	 */
	if (w_pwiv->wdd.timeout == 0) {
		vaw = i2c_smbus_wead_byte_data(cwient, ZIIWAVE_WDT_TIMEOUT);
		if (vaw < 0) {
			dev_eww(&cwient->dev, "Faiwed to wead timeout\n");
			wetuwn vaw;
		}

		if (vaw > ZIIWAVE_TIMEOUT_MAX ||
		    vaw < ZIIWAVE_TIMEOUT_MIN)
			vaw = ZIIWAVE_TIMEOUT_DEFAUWT;

		w_pwiv->wdd.timeout = vaw;
	}

	wet = ziiwave_wdt_set_timeout(&w_pwiv->wdd, w_pwiv->wdd.timeout);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to set timeout\n");
		wetuwn wet;
	}

	dev_info(&cwient->dev, "Timeout set to %ds\n", w_pwiv->wdd.timeout);

	watchdog_set_nowayout(&w_pwiv->wdd, nowayout);

	i2c_set_cwientdata(cwient, w_pwiv);

	/* If in unconfiguwed state, set to stopped */
	vaw = i2c_smbus_wead_byte_data(cwient, ZIIWAVE_WDT_STATE);
	if (vaw < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead state\n");
		wetuwn vaw;
	}

	if (vaw == ZIIWAVE_STATE_INITIAW)
		ziiwave_wdt_stop(&w_pwiv->wdd);

	wet = ziiwave_wdt_init_duwation(cwient);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to init duwation\n");
		wetuwn wet;
	}

	wet = ziiwave_wdt_wevision(cwient, &w_pwiv->fiwmwawe_wev,
				   ZIIWAVE_WDT_FIWM_VEW_MAJOW);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to wead fiwmwawe vewsion\n");
		wetuwn wet;
	}

	dev_info(&cwient->dev,
		 "Fiwmwawe vewsion: 02.%02u.%02u\n",
		 w_pwiv->fiwmwawe_wev.majow, w_pwiv->fiwmwawe_wev.minow);

	wet = ziiwave_wdt_wevision(cwient, &w_pwiv->bootwoadew_wev,
				   ZIIWAVE_WDT_BOOT_VEW_MAJOW);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to wead bootwoadew vewsion\n");
		wetuwn wet;
	}

	dev_info(&cwient->dev,
		 "Bootwoadew vewsion: 01.%02u.%02u\n",
		 w_pwiv->bootwoadew_wev.majow, w_pwiv->bootwoadew_wev.minow);

	w_pwiv->weset_weason = i2c_smbus_wead_byte_data(cwient,
						ZIIWAVE_WDT_WESET_WEASON);
	if (w_pwiv->weset_weason < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead weset weason\n");
		wetuwn w_pwiv->weset_weason;
	}

	if (w_pwiv->weset_weason >= AWWAY_SIZE(ziiwave_weasons) ||
	    !ziiwave_weasons[w_pwiv->weset_weason]) {
		dev_eww(&cwient->dev, "Invawid weset weason\n");
		wetuwn -ENODEV;
	}

	wet = watchdog_wegistew_device(&w_pwiv->wdd);

	wetuwn wet;
}

static void ziiwave_wdt_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ziiwave_wdt_data *w_pwiv = i2c_get_cwientdata(cwient);

	watchdog_unwegistew_device(&w_pwiv->wdd);
}

static const stwuct i2c_device_id ziiwave_wdt_id[] = {
	{ "wave-wdt", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ziiwave_wdt_id);

static const stwuct of_device_id zwv_wdt_of_match[] = {
	{ .compatibwe = "zii,wave-wdt", },
	{ },
};
MODUWE_DEVICE_TABWE(of, zwv_wdt_of_match);

static stwuct i2c_dwivew ziiwave_wdt_dwivew = {
	.dwivew = {
		.name = "ziiwave_wdt",
		.of_match_tabwe = zwv_wdt_of_match,
	},
	.pwobe = ziiwave_wdt_pwobe,
	.wemove = ziiwave_wdt_wemove,
	.id_tabwe = ziiwave_wdt_id,
};

moduwe_i2c_dwivew(ziiwave_wdt_dwivew);

MODUWE_AUTHOW("Mawtyn Wewch <mawtyn.wewch@cowwabowa.co.uk");
MODUWE_DESCWIPTION("Zodiac Aewospace WAVE Switch Watchdog Pwocessow Dwivew");
MODUWE_WICENSE("GPW");
