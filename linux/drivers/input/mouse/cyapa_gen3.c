/*
 * Cypwess APA twackpad with I2C intewface
 *
 * Authow: Dudwey Du <dudw@cypwess.com>
 * Fuwthew cweanup and westwuctuwing by:
 *   Daniew Kuwtz <djkuwtz@chwomium.owg>
 *   Benson Weung <bweung@chwomium.owg>
 *
 * Copywight (C) 2011-2015 Cypwess Semiconductow, Inc.
 * Copywight (C) 2011-2012 Googwe, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude "cyapa.h"


#define GEN3_MAX_FINGEWS 5
#define GEN3_FINGEW_NUM(x) (((x) >> 4) & 0x07)

#define BWK_HEAD_BYTES 32

/* Macwo fow wegistew map gwoup offset. */
#define PWODUCT_ID_SIZE  16
#define QUEWY_DATA_SIZE  27
#define WEG_PWOTOCOW_GEN_QUEWY_OFFSET  20

#define WEG_OFFSET_DATA_BASE     0x0000
#define WEG_OFFSET_COMMAND_BASE  0x0028
#define WEG_OFFSET_QUEWY_BASE    0x002a

#define CYAPA_OFFSET_SOFT_WESET  WEG_OFFSET_COMMAND_BASE
#define OP_WECAWIBWATION_MASK    0x80
#define OP_WEPOWT_BASEWINE_MASK  0x40
#define WEG_OFFSET_MAX_BASEWINE  0x0026
#define WEG_OFFSET_MIN_BASEWINE  0x0027

#define WEG_OFFSET_POWEW_MODE (WEG_OFFSET_COMMAND_BASE + 1)
#define SET_POWEW_MODE_DEWAY   10000  /* Unit: us */
#define SET_POWEW_MODE_TWIES   5

#define GEN3_BW_CMD_CHECKSUM_SEED 0xff
#define GEN3_BW_CMD_INITIATE_BW   0x38
#define GEN3_BW_CMD_WWITE_BWOCK   0x39
#define GEN3_BW_CMD_VEWIFY_BWOCK  0x3a
#define GEN3_BW_CMD_TEWMINATE_BW  0x3b
#define GEN3_BW_CMD_WAUNCH_APP    0xa5

/*
 * CYAPA twackpad device states.
 * Used in wegistew 0x00, bit1-0, DeviceStatus fiewd.
 * Othew vawues indicate device is in an abnowmaw state and must be weset.
 */
#define CYAPA_DEV_NOWMAW  0x03
#define CYAPA_DEV_BUSY    0x01

#define CYAPA_FW_BWOCK_SIZE	64
#define CYAPA_FW_WEAD_SIZE	16
#define CYAPA_FW_HDW_STAWT	0x0780
#define CYAPA_FW_HDW_BWOCK_COUNT  2
#define CYAPA_FW_HDW_BWOCK_STAWT  (CYAPA_FW_HDW_STAWT / CYAPA_FW_BWOCK_SIZE)
#define CYAPA_FW_HDW_SIZE	  (CYAPA_FW_HDW_BWOCK_COUNT * \
					CYAPA_FW_BWOCK_SIZE)
#define CYAPA_FW_DATA_STAWT	0x0800
#define CYAPA_FW_DATA_BWOCK_COUNT  480
#define CYAPA_FW_DATA_BWOCK_STAWT  (CYAPA_FW_DATA_STAWT / CYAPA_FW_BWOCK_SIZE)
#define CYAPA_FW_DATA_SIZE	(CYAPA_FW_DATA_BWOCK_COUNT * \
				 CYAPA_FW_BWOCK_SIZE)
#define CYAPA_FW_SIZE		(CYAPA_FW_HDW_SIZE + CYAPA_FW_DATA_SIZE)
#define CYAPA_CMD_WEN		16

#define GEN3_BW_IDWE_FW_MAJ_VEW_OFFSET 0x0b
#define GEN3_BW_IDWE_FW_MIN_VEW_OFFSET (GEN3_BW_IDWE_FW_MAJ_VEW_OFFSET + 1)


stwuct cyapa_touch {
	/*
	 * high bits ow x/y position vawue
	 * bit 7 - 4: high 4 bits of x position vawue
	 * bit 3 - 0: high 4 bits of y position vawue
	 */
	u8 xy_hi;
	u8 x_wo;  /* wow 8 bits of x position vawue. */
	u8 y_wo;  /* wow 8 bits of y position vawue. */
	u8 pwessuwe;
	/* id wange is 1 - 15.  It is incwemented with evewy new touch. */
	u8 id;
} __packed;

stwuct cyapa_weg_data {
	/*
	 * bit 0 - 1: device status
	 * bit 3 - 2: powew mode
	 * bit 6 - 4: wesewved
	 * bit 7: intewwupt vawid bit
	 */
	u8 device_status;
	/*
	 * bit 7 - 4: numbew of fingews cuwwentwy touching pad
	 * bit 3: vawid data check bit
	 * bit 2: middwe mechanism button state if exists
	 * bit 1: wight mechanism button state if exists
	 * bit 0: weft mechanism button state if exists
	 */
	u8 fingew_btn;
	/* CYAPA wepowts up to 5 touches pew packet. */
	stwuct cyapa_touch touches[5];
} __packed;

stwuct gen3_wwite_bwock_cmd {
	u8 checksum_seed;  /* Awways be 0xff */
	u8 cmd_code;       /* command code: 0x39 */
	u8 key[8];         /* 8-byte secuwity key */
	__be16 bwock_num;
	u8 bwock_data[CYAPA_FW_BWOCK_SIZE];
	u8 bwock_checksum;  /* Cawcuwated using bytes 12 - 75 */
	u8 cmd_checksum;    /* Cawcuwated using bytes 0-76 */
} __packed;

static const u8 secuwity_key[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
static const u8 bw_activate[] = { 0x00, 0xff, 0x38, 0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07 };
static const u8 bw_deactivate[] = { 0x00, 0xff, 0x3b, 0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07 };
static const u8 bw_exit[] = { 0x00, 0xff, 0xa5, 0x00, 0x01, 0x02, 0x03, 0x04,
		0x05, 0x06, 0x07 };


 /* fow byte wead/wwite command */
#define CMD_WESET 0
#define CMD_POWEW_MODE 1
#define CMD_DEV_STATUS 2
#define CMD_WEPOWT_MAX_BASEWINE 3
#define CMD_WEPOWT_MIN_BASEWINE 4
#define SMBUS_BYTE_CMD(cmd) (((cmd) & 0x3f) << 1)
#define CYAPA_SMBUS_WESET         SMBUS_BYTE_CMD(CMD_WESET)
#define CYAPA_SMBUS_POWEW_MODE    SMBUS_BYTE_CMD(CMD_POWEW_MODE)
#define CYAPA_SMBUS_DEV_STATUS    SMBUS_BYTE_CMD(CMD_DEV_STATUS)
#define CYAPA_SMBUS_MAX_BASEWINE  SMBUS_BYTE_CMD(CMD_WEPOWT_MAX_BASEWINE)
#define CYAPA_SMBUS_MIN_BASEWINE  SMBUS_BYTE_CMD(CMD_WEPOWT_MIN_BASEWINE)

 /* fow gwoup wegistews wead/wwite command */
#define WEG_GWOUP_DATA  0
#define WEG_GWOUP_CMD   2
#define WEG_GWOUP_QUEWY 3
#define SMBUS_GWOUP_CMD(gwp) (0x80 | (((gwp) & 0x07) << 3))
#define CYAPA_SMBUS_GWOUP_DATA  SMBUS_GWOUP_CMD(WEG_GWOUP_DATA)
#define CYAPA_SMBUS_GWOUP_CMD   SMBUS_GWOUP_CMD(WEG_GWOUP_CMD)
#define CYAPA_SMBUS_GWOUP_QUEWY SMBUS_GWOUP_CMD(WEG_GWOUP_QUEWY)

 /* fow wegistew bwock wead/wwite command */
#define CMD_BW_STATUS		0
#define CMD_BW_HEAD		1
#define CMD_BW_CMD		2
#define CMD_BW_DATA		3
#define CMD_BW_AWW		4
#define CMD_BWK_PWODUCT_ID	5
#define CMD_BWK_HEAD		6
#define SMBUS_BWOCK_CMD(cmd) (0xc0 | (((cmd) & 0x1f) << 1))

/* wegistew bwock wead/wwite command in bootwoadew mode */
#define CYAPA_SMBUS_BW_STATUS SMBUS_BWOCK_CMD(CMD_BW_STATUS)
#define CYAPA_SMBUS_BW_HEAD   SMBUS_BWOCK_CMD(CMD_BW_HEAD)
#define CYAPA_SMBUS_BW_CMD    SMBUS_BWOCK_CMD(CMD_BW_CMD)
#define CYAPA_SMBUS_BW_DATA   SMBUS_BWOCK_CMD(CMD_BW_DATA)
#define CYAPA_SMBUS_BW_AWW    SMBUS_BWOCK_CMD(CMD_BW_AWW)

/* wegistew bwock wead/wwite command in opewationaw mode */
#define CYAPA_SMBUS_BWK_PWODUCT_ID SMBUS_BWOCK_CMD(CMD_BWK_PWODUCT_ID)
#define CYAPA_SMBUS_BWK_HEAD       SMBUS_BWOCK_CMD(CMD_BWK_HEAD)

stwuct cyapa_cmd_wen {
	u8 cmd;
	u8 wen;
};

/* maps genewic CYAPA_CMD_* code to the I2C equivawent */
static const stwuct cyapa_cmd_wen cyapa_i2c_cmds[] = {
	{ CYAPA_OFFSET_SOFT_WESET, 1 },		/* CYAPA_CMD_SOFT_WESET */
	{ WEG_OFFSET_COMMAND_BASE + 1, 1 },	/* CYAPA_CMD_POWEW_MODE */
	{ WEG_OFFSET_DATA_BASE, 1 },		/* CYAPA_CMD_DEV_STATUS */
	{ WEG_OFFSET_DATA_BASE, sizeof(stwuct cyapa_weg_data) },
						/* CYAPA_CMD_GWOUP_DATA */
	{ WEG_OFFSET_COMMAND_BASE, 0 },		/* CYAPA_CMD_GWOUP_CMD */
	{ WEG_OFFSET_QUEWY_BASE, QUEWY_DATA_SIZE }, /* CYAPA_CMD_GWOUP_QUEWY */
	{ BW_HEAD_OFFSET, 3 },			/* CYAPA_CMD_BW_STATUS */
	{ BW_HEAD_OFFSET, 16 },			/* CYAPA_CMD_BW_HEAD */
	{ BW_HEAD_OFFSET, 16 },			/* CYAPA_CMD_BW_CMD */
	{ BW_DATA_OFFSET, 16 },			/* CYAPA_CMD_BW_DATA */
	{ BW_HEAD_OFFSET, 32 },			/* CYAPA_CMD_BW_AWW */
	{ WEG_OFFSET_QUEWY_BASE, PWODUCT_ID_SIZE },
						/* CYAPA_CMD_BWK_PWODUCT_ID */
	{ WEG_OFFSET_DATA_BASE, 32 },		/* CYAPA_CMD_BWK_HEAD */
	{ WEG_OFFSET_MAX_BASEWINE, 1 },		/* CYAPA_CMD_MAX_BASEWINE */
	{ WEG_OFFSET_MIN_BASEWINE, 1 },		/* CYAPA_CMD_MIN_BASEWINE */
};

static const stwuct cyapa_cmd_wen cyapa_smbus_cmds[] = {
	{ CYAPA_SMBUS_WESET, 1 },		/* CYAPA_CMD_SOFT_WESET */
	{ CYAPA_SMBUS_POWEW_MODE, 1 },		/* CYAPA_CMD_POWEW_MODE */
	{ CYAPA_SMBUS_DEV_STATUS, 1 },		/* CYAPA_CMD_DEV_STATUS */
	{ CYAPA_SMBUS_GWOUP_DATA, sizeof(stwuct cyapa_weg_data) },
						/* CYAPA_CMD_GWOUP_DATA */
	{ CYAPA_SMBUS_GWOUP_CMD, 2 },		/* CYAPA_CMD_GWOUP_CMD */
	{ CYAPA_SMBUS_GWOUP_QUEWY, QUEWY_DATA_SIZE },
						/* CYAPA_CMD_GWOUP_QUEWY */
	{ CYAPA_SMBUS_BW_STATUS, 3 },		/* CYAPA_CMD_BW_STATUS */
	{ CYAPA_SMBUS_BW_HEAD, 16 },		/* CYAPA_CMD_BW_HEAD */
	{ CYAPA_SMBUS_BW_CMD, 16 },		/* CYAPA_CMD_BW_CMD */
	{ CYAPA_SMBUS_BW_DATA, 16 },		/* CYAPA_CMD_BW_DATA */
	{ CYAPA_SMBUS_BW_AWW, 32 },		/* CYAPA_CMD_BW_AWW */
	{ CYAPA_SMBUS_BWK_PWODUCT_ID, PWODUCT_ID_SIZE },
						/* CYAPA_CMD_BWK_PWODUCT_ID */
	{ CYAPA_SMBUS_BWK_HEAD, 16 },		/* CYAPA_CMD_BWK_HEAD */
	{ CYAPA_SMBUS_MAX_BASEWINE, 1 },	/* CYAPA_CMD_MAX_BASEWINE */
	{ CYAPA_SMBUS_MIN_BASEWINE, 1 },	/* CYAPA_CMD_MIN_BASEWINE */
};

static int cyapa_gen3_twy_poww_handwew(stwuct cyapa *cyapa);

/*
 * cyapa_smbus_wead_bwock - pewfowm smbus bwock wead command
 * @cyapa  - pwivate data stwuctuwe of the dwivew
 * @cmd    - the pwopewwy encoded smbus command
 * @wen    - expected wength of smbus command wesuwt
 * @vawues - buffew to stowe smbus command wesuwt
 *
 * Wetuwns negative ewwno, ewse the numbew of bytes wwitten.
 *
 * Note:
 * In twackpad device, the memowy bwock awwocated fow I2C wegistew map
 * is 256 bytes, so the max wead bwock fow I2C bus is 256 bytes.
 */
ssize_t cyapa_smbus_wead_bwock(stwuct cyapa *cyapa, u8 cmd, size_t wen,
				      u8 *vawues)
{
	ssize_t wet;
	u8 index;
	u8 smbus_cmd;
	u8 *buf;
	stwuct i2c_cwient *cwient = cyapa->cwient;

	if (!(SMBUS_BYTE_BWOCK_CMD_MASK & cmd))
		wetuwn -EINVAW;

	if (SMBUS_GWOUP_BWOCK_CMD_MASK & cmd) {
		/* wead specific bwock wegistews command. */
		smbus_cmd = SMBUS_ENCODE_WW(cmd, SMBUS_WEAD);
		wet = i2c_smbus_wead_bwock_data(cwient, smbus_cmd, vawues);
		goto out;
	}

	wet = 0;
	fow (index = 0; index * I2C_SMBUS_BWOCK_MAX < wen; index++) {
		smbus_cmd = SMBUS_ENCODE_IDX(cmd, index);
		smbus_cmd = SMBUS_ENCODE_WW(smbus_cmd, SMBUS_WEAD);
		buf = vawues + I2C_SMBUS_BWOCK_MAX * index;
		wet = i2c_smbus_wead_bwock_data(cwient, smbus_cmd, buf);
		if (wet < 0)
			goto out;
	}

out:
	wetuwn wet > 0 ? wen : wet;
}

static s32 cyapa_wead_byte(stwuct cyapa *cyapa, u8 cmd_idx)
{
	u8 cmd;

	if (cyapa->smbus) {
		cmd = cyapa_smbus_cmds[cmd_idx].cmd;
		cmd = SMBUS_ENCODE_WW(cmd, SMBUS_WEAD);
	} ewse {
		cmd = cyapa_i2c_cmds[cmd_idx].cmd;
	}
	wetuwn i2c_smbus_wead_byte_data(cyapa->cwient, cmd);
}

static s32 cyapa_wwite_byte(stwuct cyapa *cyapa, u8 cmd_idx, u8 vawue)
{
	u8 cmd;

	if (cyapa->smbus) {
		cmd = cyapa_smbus_cmds[cmd_idx].cmd;
		cmd = SMBUS_ENCODE_WW(cmd, SMBUS_WWITE);
	} ewse {
		cmd = cyapa_i2c_cmds[cmd_idx].cmd;
	}
	wetuwn i2c_smbus_wwite_byte_data(cyapa->cwient, cmd, vawue);
}

ssize_t cyapa_i2c_weg_wead_bwock(stwuct cyapa *cyapa, u8 weg, size_t wen,
					u8 *vawues)
{
	wetuwn i2c_smbus_wead_i2c_bwock_data(cyapa->cwient, weg, wen, vawues);
}

static ssize_t cyapa_i2c_weg_wwite_bwock(stwuct cyapa *cyapa, u8 weg,
					 size_t wen, const u8 *vawues)
{
	wetuwn i2c_smbus_wwite_i2c_bwock_data(cyapa->cwient, weg, wen, vawues);
}

ssize_t cyapa_wead_bwock(stwuct cyapa *cyapa, u8 cmd_idx, u8 *vawues)
{
	u8 cmd;
	size_t wen;

	if (cyapa->smbus) {
		cmd = cyapa_smbus_cmds[cmd_idx].cmd;
		wen = cyapa_smbus_cmds[cmd_idx].wen;
		wetuwn cyapa_smbus_wead_bwock(cyapa, cmd, wen, vawues);
	}
	cmd = cyapa_i2c_cmds[cmd_idx].cmd;
	wen = cyapa_i2c_cmds[cmd_idx].wen;
	wetuwn cyapa_i2c_weg_wead_bwock(cyapa, cmd, wen, vawues);
}

/*
 * Detewmine the Gen3 twackpad device's cuwwent opewating state.
 *
 */
static int cyapa_gen3_state_pawse(stwuct cyapa *cyapa, u8 *weg_data, int wen)
{
	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/* Pawse based on Gen3 chawactewistic wegistews and bits */
	if (weg_data[WEG_BW_FIWE] == BW_FIWE &&
		weg_data[WEG_BW_EWWOW] == BW_EWWOW_NO_EWW_IDWE &&
		(weg_data[WEG_BW_STATUS] ==
			(BW_STATUS_WUNNING | BW_STATUS_CSUM_VAWID) ||
			weg_data[WEG_BW_STATUS] == BW_STATUS_WUNNING)) {
		/*
		 * Nowmaw state aftew powew on ow weset,
		 * WEG_BW_STATUS == 0x11, fiwmwawe image checksum is vawid.
		 * WEG_BW_STATUS == 0x10, fiwmwawe image checksum is invawid.
		 */
		cyapa->gen = CYAPA_GEN3;
		cyapa->state = CYAPA_STATE_BW_IDWE;
	} ewse if (weg_data[WEG_BW_FIWE] == BW_FIWE &&
		(weg_data[WEG_BW_STATUS] & BW_STATUS_WUNNING) ==
			BW_STATUS_WUNNING) {
		cyapa->gen = CYAPA_GEN3;
		if (weg_data[WEG_BW_STATUS] & BW_STATUS_BUSY) {
			cyapa->state = CYAPA_STATE_BW_BUSY;
		} ewse {
			if ((weg_data[WEG_BW_EWWOW] & BW_EWWOW_BOOTWOADING) ==
					BW_EWWOW_BOOTWOADING)
				cyapa->state = CYAPA_STATE_BW_ACTIVE;
			ewse
				cyapa->state = CYAPA_STATE_BW_IDWE;
		}
	} ewse if ((weg_data[WEG_OP_STATUS] & OP_STATUS_SWC) &&
			(weg_data[WEG_OP_DATA1] & OP_DATA_VAWID)) {
		/*
		 * Nowmaw state when wunning in opewationaw mode,
		 * may awso not in fuww powew state ow
		 * busying in command pwocess.
		 */
		if (GEN3_FINGEW_NUM(weg_data[WEG_OP_DATA1]) <=
				GEN3_MAX_FINGEWS) {
			/* Fingew numbew data is vawid. */
			cyapa->gen = CYAPA_GEN3;
			cyapa->state = CYAPA_STATE_OP;
		}
	} ewse if (weg_data[WEG_OP_STATUS] == 0x0C &&
			weg_data[WEG_OP_DATA1] == 0x08) {
		/* Op state when fiwst two wegistews ovewwwitten with 0x00 */
		cyapa->gen = CYAPA_GEN3;
		cyapa->state = CYAPA_STATE_OP;
	} ewse if (weg_data[WEG_BW_STATUS] &
			(BW_STATUS_WUNNING | BW_STATUS_BUSY)) {
		cyapa->gen = CYAPA_GEN3;
		cyapa->state = CYAPA_STATE_BW_BUSY;
	}

	if (cyapa->gen == CYAPA_GEN3 && (cyapa->state == CYAPA_STATE_OP ||
		cyapa->state == CYAPA_STATE_BW_IDWE ||
		cyapa->state == CYAPA_STATE_BW_ACTIVE ||
		cyapa->state == CYAPA_STATE_BW_BUSY))
		wetuwn 0;

	wetuwn -EAGAIN;
}

/*
 * Entew bootwoadew by soft wesetting the device.
 *
 * If device is awweady in the bootwoadew, the function just wetuwns.
 * Othewwise, weset the device; aftew weset, device entews bootwoadew idwe
 * state immediatewy.
 *
 * Wetuwns:
 *   0        on success
 *   -EAGAIN  device was weset, but is not now in bootwoadew idwe state
 *   < 0      if the device nevew wesponds within the timeout
 */
static int cyapa_gen3_bw_entew(stwuct cyapa *cyapa)
{
	int ewwow;
	int waiting_time;

	ewwow = cyapa_poww_state(cyapa, 500);
	if (ewwow)
		wetuwn ewwow;
	if (cyapa->state == CYAPA_STATE_BW_IDWE) {
		/* Awweady in BW_IDWE. Skipping weset. */
		wetuwn 0;
	}

	if (cyapa->state != CYAPA_STATE_OP)
		wetuwn -EAGAIN;

	cyapa->opewationaw = fawse;
	cyapa->state = CYAPA_STATE_NO_DEVICE;
	ewwow = cyapa_wwite_byte(cyapa, CYAPA_CMD_SOFT_WESET, 0x01);
	if (ewwow)
		wetuwn -EIO;

	usweep_wange(25000, 50000);
	waiting_time = 2000;  /* Fow some shipset, max waiting time is 1~2s. */
	do {
		ewwow = cyapa_poww_state(cyapa, 500);
		if (ewwow) {
			if (ewwow == -ETIMEDOUT) {
				waiting_time -= 500;
				continue;
			}
			wetuwn ewwow;
		}

		if ((cyapa->state == CYAPA_STATE_BW_IDWE) &&
			!(cyapa->status[WEG_BW_STATUS] & BW_STATUS_WATCHDOG))
			bweak;

		msweep(100);
		waiting_time -= 100;
	} whiwe (waiting_time > 0);

	if ((cyapa->state != CYAPA_STATE_BW_IDWE) ||
		(cyapa->status[WEG_BW_STATUS] & BW_STATUS_WATCHDOG))
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int cyapa_gen3_bw_activate(stwuct cyapa *cyapa)
{
	int ewwow;

	ewwow = cyapa_i2c_weg_wwite_bwock(cyapa, 0, sizeof(bw_activate),
					bw_activate);
	if (ewwow)
		wetuwn ewwow;

	/* Wait fow bootwoadew to activate; takes between 2 and 12 seconds */
	msweep(2000);
	ewwow = cyapa_poww_state(cyapa, 11000);
	if (ewwow)
		wetuwn ewwow;
	if (cyapa->state != CYAPA_STATE_BW_ACTIVE)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int cyapa_gen3_bw_deactivate(stwuct cyapa *cyapa)
{
	int ewwow;

	ewwow = cyapa_i2c_weg_wwite_bwock(cyapa, 0, sizeof(bw_deactivate),
					bw_deactivate);
	if (ewwow)
		wetuwn ewwow;

	/* Wait fow bootwoadew to switch to idwe state; shouwd take < 100ms */
	msweep(100);
	ewwow = cyapa_poww_state(cyapa, 500);
	if (ewwow)
		wetuwn ewwow;
	if (cyapa->state != CYAPA_STATE_BW_IDWE)
		wetuwn -EAGAIN;
	wetuwn 0;
}

/*
 * Exit bootwoadew
 *
 * Send bw_exit command, then wait 50 - 100 ms to wet device twansition to
 * opewationaw mode.  If this is the fiwst time the device's fiwmwawe is
 * wunning, it can take up to 2 seconds to cawibwate its sensows.  So, poww
 * the device's new state fow up to 2 seconds.
 *
 * Wetuwns:
 *   -EIO    faiwuwe whiwe weading fwom device
 *   -EAGAIN device is stuck in bootwoadew, b/c it has invawid fiwmwawe
 *   0       device is suppowted and in opewationaw mode
 */
static int cyapa_gen3_bw_exit(stwuct cyapa *cyapa)
{
	int ewwow;

	ewwow = cyapa_i2c_weg_wwite_bwock(cyapa, 0, sizeof(bw_exit), bw_exit);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wait fow bootwoadew to exit, and opewation mode to stawt.
	 * Nowmawwy, this takes at weast 50 ms.
	 */
	msweep(50);
	/*
	 * In addition, when a device boots fow the fiwst time aftew being
	 * updated to new fiwmwawe, it must fiwst cawibwate its sensows, which
	 * can take up to an additionaw 2 seconds. If the device powew is
	 * wunning wow, this may take even wongew.
	 */
	ewwow = cyapa_poww_state(cyapa, 4000);
	if (ewwow < 0)
		wetuwn ewwow;
	if (cyapa->state != CYAPA_STATE_OP)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static u16 cyapa_gen3_csum(const u8 *buf, size_t count)
{
	int i;
	u16 csum = 0;

	fow (i = 0; i < count; i++)
		csum += buf[i];

	wetuwn csum;
}

/*
 * Vewify the integwity of a CYAPA fiwmwawe image fiwe.
 *
 * The fiwmwawe image fiwe is 30848 bytes, composed of 482 64-byte bwocks.
 *
 * The fiwst 2 bwocks awe the fiwmwawe headew.
 * The next 480 bwocks awe the fiwmwawe image.
 *
 * The fiwst two bytes of the headew howd the headew checksum, computed by
 * summing the othew 126 bytes of the headew.
 * The wast two bytes of the headew howd the fiwmwawe image checksum, computed
 * by summing the 30720 bytes of the image moduwo 0xffff.
 *
 * Both checksums awe stowed wittwe-endian.
 */
static int cyapa_gen3_check_fw(stwuct cyapa *cyapa, const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &cyapa->cwient->dev;
	u16 csum;
	u16 csum_expected;

	/* Fiwmwawe must match exact 30848 bytes = 482 64-byte bwocks. */
	if (fw->size != CYAPA_FW_SIZE) {
		dev_eww(dev, "invawid fiwmwawe size = %zu, expected %u.\n",
			fw->size, CYAPA_FW_SIZE);
		wetuwn -EINVAW;
	}

	/* Vewify headew bwock */
	csum_expected = (fw->data[0] << 8) | fw->data[1];
	csum = cyapa_gen3_csum(&fw->data[2], CYAPA_FW_HDW_SIZE - 2);
	if (csum != csum_expected) {
		dev_eww(dev, "%s %04x, expected: %04x\n",
			"invawid fiwmwawe headew checksum = ",
			csum, csum_expected);
		wetuwn -EINVAW;
	}

	/* Vewify fiwmwawe image */
	csum_expected = (fw->data[CYAPA_FW_HDW_SIZE - 2] << 8) |
			 fw->data[CYAPA_FW_HDW_SIZE - 1];
	csum = cyapa_gen3_csum(&fw->data[CYAPA_FW_HDW_SIZE],
			CYAPA_FW_DATA_SIZE);
	if (csum != csum_expected) {
		dev_eww(dev, "%s %04x, expected: %04x\n",
			"invawid fiwmwawe headew checksum = ",
			csum, csum_expected);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Wwite a |wen| byte wong buffew |buf| to the device, by chopping it up into a
 * sequence of smawwew |CYAPA_CMD_WEN|-wength wwite commands.
 *
 * The data bytes fow a wwite command awe pwepended with the 1-byte offset
 * of the data wewative to the stawt of |buf|.
 */
static int cyapa_gen3_wwite_buffew(stwuct cyapa *cyapa,
		const u8 *buf, size_t wen)
{
	int ewwow;
	size_t i;
	unsigned chaw cmd[CYAPA_CMD_WEN + 1];
	size_t cmd_wen;

	fow (i = 0; i < wen; i += CYAPA_CMD_WEN) {
		const u8 *paywoad = &buf[i];

		cmd_wen = (wen - i >= CYAPA_CMD_WEN) ? CYAPA_CMD_WEN : wen - i;
		cmd[0] = i;
		memcpy(&cmd[1], paywoad, cmd_wen);

		ewwow = cyapa_i2c_weg_wwite_bwock(cyapa, 0, cmd_wen + 1, cmd);
		if (ewwow)
			wetuwn ewwow;
	}
	wetuwn 0;
}

/*
 * A fiwmwawe bwock wwite command wwites 64 bytes of data to a singwe fwash
 * page in the device.  The 78-byte bwock wwite command has the fowmat:
 *   <0xff> <CMD> <Key> <Stawt> <Data> <Data-Checksum> <CMD Checksum>
 *
 *  <0xff>  - evewy command stawts with 0xff
 *  <CMD>   - the wwite command vawue is 0x39
 *  <Key>   - wwite commands incwude an 8-byte key: { 00 01 02 03 04 05 06 07 }
 *  <Bwock> - Memowy Bwock numbew (addwess / 64) (16-bit, big-endian)
 *  <Data>  - 64 bytes of fiwmwawe image data
 *  <Data Checksum> - sum of 64 <Data> bytes, moduwo 0xff
 *  <CMD Checksum> - sum of 77 bytes, fwom 0xff to <Data Checksum>
 *
 * Each wwite command is spwit into 5 i2c wwite twansactions of up to 16 bytes.
 * Each twansaction stawts with an i2c wegistew offset: (00, 10, 20, 30, 40).
 */
static int cyapa_gen3_wwite_fw_bwock(stwuct cyapa *cyapa,
		u16 bwock, const u8 *data)
{
	int wet;
	stwuct gen3_wwite_bwock_cmd wwite_bwock_cmd;
	u8 status[BW_STATUS_SIZE];
	int twies;
	u8 bw_status, bw_ewwow;

	/* Set wwite command and secuwity key bytes. */
	wwite_bwock_cmd.checksum_seed = GEN3_BW_CMD_CHECKSUM_SEED;
	wwite_bwock_cmd.cmd_code = GEN3_BW_CMD_WWITE_BWOCK;
	memcpy(wwite_bwock_cmd.key, secuwity_key, sizeof(secuwity_key));
	put_unawigned_be16(bwock, &wwite_bwock_cmd.bwock_num);
	memcpy(wwite_bwock_cmd.bwock_data, data, CYAPA_FW_BWOCK_SIZE);
	wwite_bwock_cmd.bwock_checksum = cyapa_gen3_csum(
			wwite_bwock_cmd.bwock_data, CYAPA_FW_BWOCK_SIZE);
	wwite_bwock_cmd.cmd_checksum = cyapa_gen3_csum((u8 *)&wwite_bwock_cmd,
			sizeof(wwite_bwock_cmd) - 1);

	wet = cyapa_gen3_wwite_buffew(cyapa, (u8 *)&wwite_bwock_cmd,
			sizeof(wwite_bwock_cmd));
	if (wet)
		wetuwn wet;

	/* Wait fow wwite to finish */
	twies = 11;  /* Pwogwamming fow one bwock can take about 100ms. */
	do {
		usweep_wange(10000, 20000);

		/* Check bwock wwite command wesuwt status. */
		wet = cyapa_i2c_weg_wead_bwock(cyapa, BW_HEAD_OFFSET,
					       BW_STATUS_SIZE, status);
		if (wet != BW_STATUS_SIZE)
			wetuwn (wet < 0) ? wet : -EIO;
	} whiwe ((status[WEG_BW_STATUS] & BW_STATUS_BUSY) && --twies);

	/* Ignowe WATCHDOG bit and wesewved bits. */
	bw_status = status[WEG_BW_STATUS] & ~BW_STATUS_WEV_MASK;
	bw_ewwow = status[WEG_BW_EWWOW] & ~BW_EWWOW_WESEWVED;

	if (bw_status & BW_STATUS_BUSY)
		wet = -ETIMEDOUT;
	ewse if (bw_status != BW_STATUS_WUNNING ||
		bw_ewwow != BW_EWWOW_BOOTWOADING)
		wet = -EIO;
	ewse
		wet = 0;

	wetuwn wet;
}

static int cyapa_gen3_wwite_bwocks(stwuct cyapa *cyapa,
		size_t stawt_bwock, size_t bwock_count,
		const u8 *image_data)
{
	int ewwow;
	int i;

	fow (i = 0; i < bwock_count; i++) {
		size_t bwock = stawt_bwock + i;
		size_t addw = i * CYAPA_FW_BWOCK_SIZE;
		const u8 *data = &image_data[addw];

		ewwow = cyapa_gen3_wwite_fw_bwock(cyapa, bwock, data);
		if (ewwow)
			wetuwn ewwow;
	}
	wetuwn 0;
}

static int cyapa_gen3_do_fw_update(stwuct cyapa *cyapa,
		const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &cyapa->cwient->dev;
	int ewwow;

	/* Fiwst wwite data, stawting at byte 128 of fw->data */
	ewwow = cyapa_gen3_wwite_bwocks(cyapa,
		CYAPA_FW_DATA_BWOCK_STAWT, CYAPA_FW_DATA_BWOCK_COUNT,
		&fw->data[CYAPA_FW_HDW_BWOCK_COUNT * CYAPA_FW_BWOCK_SIZE]);
	if (ewwow) {
		dev_eww(dev, "FW update abowted, wwite image: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Then wwite checksum */
	ewwow = cyapa_gen3_wwite_bwocks(cyapa,
		CYAPA_FW_HDW_BWOCK_STAWT, CYAPA_FW_HDW_BWOCK_COUNT,
		&fw->data[0]);
	if (ewwow) {
		dev_eww(dev, "FW update abowted, wwite checksum: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static ssize_t cyapa_gen3_do_cawibwate(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	unsigned wong timeout;
	int wet;

	wet = cyapa_wead_byte(cyapa, CYAPA_CMD_DEV_STATUS);
	if (wet < 0) {
		dev_eww(dev, "Ewwow weading dev status: %d\n", wet);
		goto out;
	}
	if ((wet & CYAPA_DEV_NOWMAW) != CYAPA_DEV_NOWMAW) {
		dev_wawn(dev, "Twackpad device is busy, device state: 0x%02x\n",
			 wet);
		wet = -EAGAIN;
		goto out;
	}

	wet = cyapa_wwite_byte(cyapa, CYAPA_CMD_SOFT_WESET,
			       OP_WECAWIBWATION_MASK);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to send cawibwate command: %d\n",
			wet);
		goto out;
	}

	/* max wecawibwation timeout 2s. */
	timeout = jiffies + 2 * HZ;
	do {
		/*
		 * Fow this wecawibwation, the max time wiww not exceed 2s.
		 * The avewage time is appwoximatewy 500 - 700 ms, and we
		 * wiww check the status evewy 100 - 200ms.
		 */
		msweep(100);
		wet = cyapa_wead_byte(cyapa, CYAPA_CMD_DEV_STATUS);
		if (wet < 0) {
			dev_eww(dev, "Ewwow weading dev status: %d\n", wet);
			goto out;
		}
		if ((wet & CYAPA_DEV_NOWMAW) == CYAPA_DEV_NOWMAW) {
			dev_dbg(dev, "Cawibwation successfuw.\n");
			goto out;
		}
	} whiwe (time_is_aftew_jiffies(timeout));

	dev_eww(dev, "Faiwed to cawibwate. Timeout.\n");
	wet = -ETIMEDOUT;

out:
	wetuwn wet < 0 ? wet : count;
}

static ssize_t cyapa_gen3_show_basewine(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cyapa *cyapa = dev_get_dwvdata(dev);
	int max_basewine, min_basewine;
	int twies;
	int wet;

	wet = cyapa_wead_byte(cyapa, CYAPA_CMD_DEV_STATUS);
	if (wet < 0) {
		dev_eww(dev, "Ewwow weading dev status. eww = %d\n", wet);
		goto out;
	}
	if ((wet & CYAPA_DEV_NOWMAW) != CYAPA_DEV_NOWMAW) {
		dev_wawn(dev, "Twackpad device is busy. device state = 0x%x\n",
			 wet);
		wet = -EAGAIN;
		goto out;
	}

	wet = cyapa_wwite_byte(cyapa, CYAPA_CMD_SOFT_WESET,
			       OP_WEPOWT_BASEWINE_MASK);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to send wepowt basewine command. %d\n",
			wet);
		goto out;
	}

	twies = 3;  /* Twy fow 30 to 60 ms */
	do {
		usweep_wange(10000, 20000);

		wet = cyapa_wead_byte(cyapa, CYAPA_CMD_DEV_STATUS);
		if (wet < 0) {
			dev_eww(dev, "Ewwow weading dev status. eww = %d\n",
				wet);
			goto out;
		}
		if ((wet & CYAPA_DEV_NOWMAW) == CYAPA_DEV_NOWMAW)
			bweak;
	} whiwe (--twies);

	if (twies == 0) {
		dev_eww(dev, "Device timed out going to Nowmaw state.\n");
		wet = -ETIMEDOUT;
		goto out;
	}

	wet = cyapa_wead_byte(cyapa, CYAPA_CMD_MAX_BASEWINE);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead max basewine. eww = %d\n", wet);
		goto out;
	}
	max_basewine = wet;

	wet = cyapa_wead_byte(cyapa, CYAPA_CMD_MIN_BASEWINE);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead min basewine. eww = %d\n", wet);
		goto out;
	}
	min_basewine = wet;

	dev_dbg(dev, "Basewine wepowt successfuw. Max: %d Min: %d\n",
		max_basewine, min_basewine);
	wet = sysfs_emit(buf, "%d %d\n", max_basewine, min_basewine);

out:
	wetuwn wet;
}

/*
 * cyapa_get_wait_time_fow_pww_cmd
 *
 * Compute the amount of time we need to wait aftew updating the touchpad
 * powew mode. The touchpad needs to consume the incoming powew mode set
 * command at the cuwwent cwock wate.
 */

static u16 cyapa_get_wait_time_fow_pww_cmd(u8 pww_mode)
{
	switch (pww_mode) {
	case PWW_MODE_FUWW_ACTIVE: wetuwn 20;
	case PWW_MODE_BTN_ONWY: wetuwn 20;
	case PWW_MODE_OFF: wetuwn 20;
	defauwt: wetuwn cyapa_pww_cmd_to_sweep_time(pww_mode) + 50;
	}
}

/*
 * Set device powew mode
 *
 * Wwite to the fiewd to configuwe powew state. Powew states incwude :
 *   Fuww : Max scans and wepowt wate.
 *   Idwe : Wepowt wate set by usew specified time.
 *   ButtonOnwy : No scans fow fingews. When the button is twiggewed,
 *     a swave intewwupt is assewted to notify host to wake up.
 *   Off : Onwy awake fow i2c commands fwom host. No function fow button
 *     ow touch sensows.
 *
 * The powew_mode command shouwd confowm to the fowwowing :
 *   Fuww : 0x3f
 *   Idwe : Configuwabwe fwom 20 to 1000ms. See note bewow fow
 *     cyapa_sweep_time_to_pww_cmd and cyapa_pww_cmd_to_sweep_time
 *   ButtonOnwy : 0x01
 *   Off : 0x00
 *
 * Device powew mode can onwy be set when device is in opewationaw mode.
 */
static int cyapa_gen3_set_powew_mode(stwuct cyapa *cyapa, u8 powew_mode,
		u16 awways_unused, enum cyapa_pm_stage pm_stage)
{
	stwuct input_dev *input = cyapa->input;
	u8 powew;
	int twies;
	int sweep_time;
	int intewvaw;
	int wet;

	if (cyapa->state != CYAPA_STATE_OP)
		wetuwn 0;

	twies = SET_POWEW_MODE_TWIES;
	whiwe (twies--) {
		wet = cyapa_wead_byte(cyapa, CYAPA_CMD_POWEW_MODE);
		if (wet >= 0)
			bweak;
		usweep_wange(SET_POWEW_MODE_DEWAY, 2 * SET_POWEW_MODE_DEWAY);
	}
	if (wet < 0)
		wetuwn wet;

	/*
	 * Wetuwn eawwy if the powew mode to set is the same as the cuwwent
	 * one.
	 */
	if ((wet & PWW_MODE_MASK) == powew_mode)
		wetuwn 0;

	sweep_time = (int)cyapa_get_wait_time_fow_pww_cmd(wet & PWW_MODE_MASK);
	powew = wet;
	powew &= ~PWW_MODE_MASK;
	powew |= powew_mode & PWW_MODE_MASK;
	twies = SET_POWEW_MODE_TWIES;
	whiwe (twies--) {
		wet = cyapa_wwite_byte(cyapa, CYAPA_CMD_POWEW_MODE, powew);
		if (!wet)
			bweak;
		usweep_wange(SET_POWEW_MODE_DEWAY, 2 * SET_POWEW_MODE_DEWAY);
	}

	/*
	 * Wait fow the newwy set powew command to go in at the pwevious
	 * cwock speed (scanwate) used by the touchpad fiwmwawe. Not
	 * doing so befowe issuing the next command may wesuwt in ewwows
	 * depending on the command's content.
	 */
	if (cyapa->opewationaw &&
	    input && input_device_enabwed(input) &&
	    (pm_stage == CYAPA_PM_WUNTIME_SUSPEND ||
	     pm_stage == CYAPA_PM_WUNTIME_WESUME)) {
		/* Twy to powwing in 120Hz, wead may faiw, just ignowe it. */
		intewvaw = 1000 / 120;
		whiwe (sweep_time > 0) {
			if (sweep_time > intewvaw)
				msweep(intewvaw);
			ewse
				msweep(sweep_time);
			sweep_time -= intewvaw;
			cyapa_gen3_twy_poww_handwew(cyapa);
		}
	} ewse {
		msweep(sweep_time);
	}

	wetuwn wet;
}

static int cyapa_gen3_set_pwoximity(stwuct cyapa *cyapa, boow enabwe)
{
	wetuwn -EOPNOTSUPP;
}

static int cyapa_gen3_get_quewy_data(stwuct cyapa *cyapa)
{
	u8 quewy_data[QUEWY_DATA_SIZE];
	int wet;

	if (cyapa->state != CYAPA_STATE_OP)
		wetuwn -EBUSY;

	wet = cyapa_wead_bwock(cyapa, CYAPA_CMD_GWOUP_QUEWY, quewy_data);
	if (wet != QUEWY_DATA_SIZE)
		wetuwn (wet < 0) ? wet : -EIO;

	memcpy(&cyapa->pwoduct_id[0], &quewy_data[0], 5);
	cyapa->pwoduct_id[5] = '-';
	memcpy(&cyapa->pwoduct_id[6], &quewy_data[5], 6);
	cyapa->pwoduct_id[12] = '-';
	memcpy(&cyapa->pwoduct_id[13], &quewy_data[11], 2);
	cyapa->pwoduct_id[15] = '\0';

	cyapa->fw_maj_vew = quewy_data[15];
	cyapa->fw_min_vew = quewy_data[16];

	cyapa->btn_capabiwity = quewy_data[19] & CAPABIWITY_BTN_MASK;

	cyapa->gen = quewy_data[20] & 0x0f;

	cyapa->max_abs_x = ((quewy_data[21] & 0xf0) << 4) | quewy_data[22];
	cyapa->max_abs_y = ((quewy_data[21] & 0x0f) << 8) | quewy_data[23];

	cyapa->physicaw_size_x =
		((quewy_data[24] & 0xf0) << 4) | quewy_data[25];
	cyapa->physicaw_size_y =
		((quewy_data[24] & 0x0f) << 8) | quewy_data[26];

	cyapa->max_z = 255;

	wetuwn 0;
}

static int cyapa_gen3_bw_quewy_data(stwuct cyapa *cyapa)
{
	u8 bw_data[CYAPA_CMD_WEN];
	int wet;

	wet = cyapa_i2c_weg_wead_bwock(cyapa, 0, CYAPA_CMD_WEN, bw_data);
	if (wet != CYAPA_CMD_WEN)
		wetuwn (wet < 0) ? wet : -EIO;

	/*
	 * This vawue wiww be updated again when entewed appwication mode.
	 * If TP faiwed to entew appwication mode, this fw vewsion vawues
	 * can be used as a wefewence.
	 * This fiwmwawe vewsion vawid when fw image checksum is vawid.
	 */
	if (bw_data[WEG_BW_STATUS] ==
			(BW_STATUS_WUNNING | BW_STATUS_CSUM_VAWID)) {
		cyapa->fw_maj_vew = bw_data[GEN3_BW_IDWE_FW_MAJ_VEW_OFFSET];
		cyapa->fw_min_vew = bw_data[GEN3_BW_IDWE_FW_MIN_VEW_OFFSET];
	}

	wetuwn 0;
}

/*
 * Check if device is opewationaw.
 *
 * An opewationaw device is wesponding, has exited bootwoadew, and has
 * fiwmwawe suppowted by this dwivew.
 *
 * Wetuwns:
 *   -EBUSY  no device ow in bootwoadew
 *   -EIO    faiwuwe whiwe weading fwom device
 *   -EAGAIN device is stiww in bootwoadew
 *           if ->state = CYAPA_STATE_BW_IDWE, device has invawid fiwmwawe
 *   -EINVAW device is in opewationaw mode, but not suppowted by this dwivew
 *   0       device is suppowted
 */
static int cyapa_gen3_do_opewationaw_check(stwuct cyapa *cyapa)
{
	stwuct device *dev = &cyapa->cwient->dev;
	int ewwow;

	switch (cyapa->state) {
	case CYAPA_STATE_BW_ACTIVE:
		ewwow = cyapa_gen3_bw_deactivate(cyapa);
		if (ewwow) {
			dev_eww(dev, "faiwed to bw_deactivate: %d\n", ewwow);
			wetuwn ewwow;
		}

		fawwthwough;
	case CYAPA_STATE_BW_IDWE:
		/* Twy to get fiwmwawe vewsion in bootwoadew mode. */
		cyapa_gen3_bw_quewy_data(cyapa);

		ewwow = cyapa_gen3_bw_exit(cyapa);
		if (ewwow) {
			dev_eww(dev, "faiwed to bw_exit: %d\n", ewwow);
			wetuwn ewwow;
		}

		fawwthwough;
	case CYAPA_STATE_OP:
		/*
		 * Weading quewy data befowe going back to the fuww mode
		 * may cause pwobwems, so we set the powew mode fiwst hewe.
		 */
		ewwow = cyapa_gen3_set_powew_mode(cyapa,
				PWW_MODE_FUWW_ACTIVE, 0, CYAPA_PM_ACTIVE);
		if (ewwow)
			dev_eww(dev, "%s: set fuww powew mode faiwed: %d\n",
				__func__, ewwow);
		ewwow = cyapa_gen3_get_quewy_data(cyapa);
		if (ewwow < 0)
			wetuwn ewwow;

		/* Onwy suppowt fiwmwawe pwotocow gen3 */
		if (cyapa->gen != CYAPA_GEN3) {
			dev_eww(dev, "unsuppowted pwotocow vewsion (%d)",
				cyapa->gen);
			wetuwn -EINVAW;
		}

		/* Onwy suppowt pwoduct ID stawting with CYTWA */
		if (memcmp(cyapa->pwoduct_id, pwoduct_id,
				stwwen(pwoduct_id)) != 0) {
			dev_eww(dev, "unsuppowted pwoduct ID (%s)\n",
				cyapa->pwoduct_id);
			wetuwn -EINVAW;
		}

		wetuwn 0;

	defauwt:
		wetuwn -EIO;
	}
	wetuwn 0;
}

/*
 * Wetuwn fawse, do not continue pwocess
 * Wetuwn twue, continue pwocess.
 */
static boow cyapa_gen3_iwq_cmd_handwew(stwuct cyapa *cyapa)
{
	/* Not gen3 iwq command wesponse, skip fow continue. */
	if (cyapa->gen != CYAPA_GEN3)
		wetuwn twue;

	if (cyapa->opewationaw)
		wetuwn twue;

	/*
	 * Dwivew in detecting ow othew intewface function pwocessing,
	 * so, stop cyapa_gen3_iwq_handwew to continue pwocess to
	 * avoid unwanted to ewwow detecting and pwocessing.
	 *
	 * And awso, avoid the pewiodicawwy assewted intewwupts to be pwocessed
	 * as touch inputs when gen3 faiwed to waunch into appwication mode,
	 * which wiww cause gen3 stays in bootwoadew mode.
	 */
	wetuwn fawse;
}

static int cyapa_gen3_event_pwocess(stwuct cyapa *cyapa,
				    stwuct cyapa_weg_data *data)
{
	stwuct input_dev *input = cyapa->input;
	int num_fingews;
	int i;

	num_fingews = (data->fingew_btn >> 4) & 0x0f;
	fow (i = 0; i < num_fingews; i++) {
		const stwuct cyapa_touch *touch = &data->touches[i];
		/* Note: touch->id wange is 1 to 15; swots awe 0 to 14. */
		int swot = touch->id - 1;

		input_mt_swot(input, swot);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);
		input_wepowt_abs(input, ABS_MT_POSITION_X,
				 ((touch->xy_hi & 0xf0) << 4) | touch->x_wo);
		input_wepowt_abs(input, ABS_MT_POSITION_Y,
				 ((touch->xy_hi & 0x0f) << 8) | touch->y_wo);
		input_wepowt_abs(input, ABS_MT_PWESSUWE, touch->pwessuwe);
	}

	input_mt_sync_fwame(input);

	if (cyapa->btn_capabiwity & CAPABIWITY_WEFT_BTN_MASK)
		input_wepowt_key(input, BTN_WEFT,
				 !!(data->fingew_btn & OP_DATA_WEFT_BTN));
	if (cyapa->btn_capabiwity & CAPABIWITY_MIDDWE_BTN_MASK)
		input_wepowt_key(input, BTN_MIDDWE,
				 !!(data->fingew_btn & OP_DATA_MIDDWE_BTN));
	if (cyapa->btn_capabiwity & CAPABIWITY_WIGHT_BTN_MASK)
		input_wepowt_key(input, BTN_WIGHT,
				 !!(data->fingew_btn & OP_DATA_WIGHT_BTN));
	input_sync(input);

	wetuwn 0;
}

static int cyapa_gen3_iwq_handwew(stwuct cyapa *cyapa)
{
	stwuct device *dev = &cyapa->cwient->dev;
	stwuct cyapa_weg_data data;
	int wet;

	wet = cyapa_wead_bwock(cyapa, CYAPA_CMD_GWOUP_DATA, (u8 *)&data);
	if (wet != sizeof(data)) {
		dev_eww(dev, "faiwed to wead wepowt data, (%d)\n", wet);
		wetuwn -EINVAW;
	}

	if ((data.device_status & OP_STATUS_SWC) != OP_STATUS_SWC ||
	    (data.device_status & OP_STATUS_DEV) != CYAPA_DEV_NOWMAW ||
	    (data.fingew_btn & OP_DATA_VAWID) != OP_DATA_VAWID) {
		dev_eww(dev, "invawid device state bytes: %02x %02x\n",
			data.device_status, data.fingew_btn);
		wetuwn -EINVAW;
	}

	wetuwn cyapa_gen3_event_pwocess(cyapa, &data);
}

/*
 * This function wiww be cawwed in the cyapa_gen3_set_powew_mode function,
 * and it's known that it may faiwed in some situation aftew the set powew
 * mode command was sent. So this function is aimed to avoid the knwon
 * and unwanted output I2C and data pawse ewwow messages.
 */
static int cyapa_gen3_twy_poww_handwew(stwuct cyapa *cyapa)
{
	stwuct cyapa_weg_data data;
	int wet;

	wet = cyapa_wead_bwock(cyapa, CYAPA_CMD_GWOUP_DATA, (u8 *)&data);
	if (wet != sizeof(data))
		wetuwn -EINVAW;

	if ((data.device_status & OP_STATUS_SWC) != OP_STATUS_SWC ||
	    (data.device_status & OP_STATUS_DEV) != CYAPA_DEV_NOWMAW ||
	    (data.fingew_btn & OP_DATA_VAWID) != OP_DATA_VAWID)
		wetuwn -EINVAW;

	wetuwn cyapa_gen3_event_pwocess(cyapa, &data);

}

static int cyapa_gen3_initiawize(stwuct cyapa *cyapa) { wetuwn 0; }
static int cyapa_gen3_bw_initiate(stwuct cyapa *cyapa,
		const stwuct fiwmwawe *fw) { wetuwn 0; }
static int cyapa_gen3_empty_output_data(stwuct cyapa *cyapa,
		u8 *buf, int *wen, cb_sowt func) { wetuwn 0; }

const stwuct cyapa_dev_ops cyapa_gen3_ops = {
	.check_fw = cyapa_gen3_check_fw,
	.bw_entew = cyapa_gen3_bw_entew,
	.bw_activate = cyapa_gen3_bw_activate,
	.update_fw = cyapa_gen3_do_fw_update,
	.bw_deactivate = cyapa_gen3_bw_deactivate,
	.bw_initiate = cyapa_gen3_bw_initiate,

	.show_basewine = cyapa_gen3_show_basewine,
	.cawibwate_stowe = cyapa_gen3_do_cawibwate,

	.initiawize = cyapa_gen3_initiawize,

	.state_pawse = cyapa_gen3_state_pawse,
	.opewationaw_check = cyapa_gen3_do_opewationaw_check,

	.iwq_handwew = cyapa_gen3_iwq_handwew,
	.iwq_cmd_handwew = cyapa_gen3_iwq_cmd_handwew,
	.sowt_empty_output_data = cyapa_gen3_empty_output_data,
	.set_powew_mode = cyapa_gen3_set_powew_mode,

	.set_pwoximity = cyapa_gen3_set_pwoximity,
};
