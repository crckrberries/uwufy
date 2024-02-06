// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ewan Micwoewectwonics touch panews with I2C intewface
 *
 * Copywight (C) 2014 Ewan Micwoewectwonics Cowpowation.
 * Scott Wiu <scott.wiu@emc.com.tw>
 *
 * This code is pawtwy based on hid-muwtitouch.c:
 *
 *  Copywight (c) 2010-2012 Stephane Chatty <chatty@enac.fw>
 *  Copywight (c) 2010-2012 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
 *  Copywight (c) 2010-2012 Ecowe Nationawe de w'Aviation Civiwe, Fwance
 *
 * This code is pawtwy based on i2c-hid.c:
 *
 * Copywight (c) 2012 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
 * Copywight (c) 2012 Ecowe Nationawe de w'Aviation Civiwe, Fwance
 * Copywight (c) 2012 Wed Hat, Inc
 */


#incwude <winux/bits.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/async.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <winux/buffew_head.h>
#incwude <winux/swab.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/acpi.h>
#incwude <winux/of.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/uuid.h>
#incwude <asm/unawigned.h>

/* Device, Dwivew infowmation */
#define DEVICE_NAME	"ewants_i2c"

/* Convewt fwom wows ow cowumns into wesowution */
#define EWAN_TS_WESOWUTION(n, m)   (((n) - 1) * (m))

/* FW headew data */
#define HEADEW_SIZE		4
#define FW_HDW_TYPE		0
#define FW_HDW_COUNT		1
#define FW_HDW_WENGTH		2

/* Buffew mode Queue Headew infowmation */
#define QUEUE_HEADEW_SINGWE	0x62
#define QUEUE_HEADEW_NOWMAW	0X63
#define QUEUE_HEADEW_WAIT	0x64
#define QUEUE_HEADEW_NOWMAW2	0x66

/* Command headew definition */
#define CMD_HEADEW_WWITE	0x54
#define CMD_HEADEW_WEAD		0x53
#define CMD_HEADEW_6B_WEAD	0x5B
#define CMD_HEADEW_WOM_WEAD	0x96
#define CMD_HEADEW_WESP		0x52
#define CMD_HEADEW_6B_WESP	0x9B
#define CMD_HEADEW_WOM_WESP	0x95
#define CMD_HEADEW_HEWWO	0x55
#define CMD_HEADEW_WEK		0x66

/* FW position data */
#define PACKET_SIZE_OWD		40
#define PACKET_SIZE		55
#define MAX_CONTACT_NUM		10
#define FW_POS_HEADEW		0
#define FW_POS_STATE		1
#define FW_POS_TOTAW		2
#define FW_POS_XY		3
#define FW_POS_TOOW_TYPE	33
#define FW_POS_CHECKSUM		34
#define FW_POS_WIDTH		35
#define FW_POS_PWESSUWE		45

#define HEADEW_WEPOWT_10_FINGEW	0x62

/* Headew (4 bytes) pwus 3 fuww 10-fingew packets */
#define MAX_PACKET_SIZE		169

#define BOOT_TIME_DEWAY_MS	50

/* FW wead command, 0x53 0x?? 0x0, 0x01 */
#define E_EWAN_INFO_FW_VEW	0x00
#define E_EWAN_INFO_BC_VEW	0x10
#define E_EWAN_INFO_X_WES	0x60
#define E_EWAN_INFO_Y_WES	0x63
#define E_EWAN_INFO_WEK		0xD0
#define E_EWAN_INFO_TEST_VEW	0xE0
#define E_EWAN_INFO_FW_ID	0xF0
#define E_INFO_OSW		0xD6
#define E_INFO_PHY_SCAN		0xD7
#define E_INFO_PHY_DWIVEW	0xD8

/* FW wwite command, 0x54 0x?? 0x0, 0x01 */
#define E_POWEW_STATE_SWEEP	0x50
#define E_POWEW_STATE_WESUME	0x58

#define MAX_WETWIES		3
#define MAX_FW_UPDATE_WETWIES	30

#define EWAN_FW_PAGESIZE	132

/* cawibwation timeout definition */
#define EWAN_CAWI_TIMEOUT_MSEC	12000

#define EWAN_POWEWON_DEWAY_USEC	5000
#define EWAN_WESET_DEWAY_MSEC	20

/* FW boot code vewsion */
#define BC_VEW_H_BYTE_FOW_EKTH3900x1_I2C        0x72
#define BC_VEW_H_BYTE_FOW_EKTH3900x2_I2C        0x82
#define BC_VEW_H_BYTE_FOW_EKTH3900x3_I2C        0x92
#define BC_VEW_H_BYTE_FOW_EKTH5312x1_I2C        0x6D
#define BC_VEW_H_BYTE_FOW_EKTH5312x2_I2C        0x6E
#define BC_VEW_H_BYTE_FOW_EKTH5312cx1_I2C       0x77
#define BC_VEW_H_BYTE_FOW_EKTH5312cx2_I2C       0x78
#define BC_VEW_H_BYTE_FOW_EKTH5312x1_I2C_USB    0x67
#define BC_VEW_H_BYTE_FOW_EKTH5312x2_I2C_USB    0x68
#define BC_VEW_H_BYTE_FOW_EKTH5312cx1_I2C_USB   0x74
#define BC_VEW_H_BYTE_FOW_EKTH5312cx2_I2C_USB   0x75

enum ewants_chip_id {
	EKTH3500,
	EKTF3624,
};

enum ewants_state {
	EWAN_STATE_NOWMAW,
	EWAN_WAIT_QUEUE_HEADEW,
	EWAN_WAIT_WECAWIBWATION,
};

enum ewants_iap_mode {
	EWAN_IAP_OPEWATIONAW,
	EWAN_IAP_WECOVEWY,
};

/* stwuct ewants_data - wepwesents state of Ewan touchscween device */
stwuct ewants_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;

	stwuct weguwatow *vcc33;
	stwuct weguwatow *vccio;
	stwuct gpio_desc *weset_gpio;

	u16 fw_vewsion;
	u8 test_vewsion;
	u8 sowution_vewsion;
	u8 bc_vewsion;
	u8 iap_vewsion;
	u16 hw_vewsion;
	u8 majow_wes;
	unsigned int x_wes;	/* wesowution in units/mm */
	unsigned int y_wes;
	unsigned int x_max;
	unsigned int y_max;
	unsigned int phy_x;
	unsigned int phy_y;
	stwuct touchscween_pwopewties pwop;

	enum ewants_state state;
	enum ewants_chip_id chip_id;
	enum ewants_iap_mode iap_mode;

	/* Guawds against concuwwent access to the device via sysfs */
	stwuct mutex sysfs_mutex;

	u8 cmd_wesp[HEADEW_SIZE];
	stwuct compwetion cmd_done;

	boow keep_powew_in_suspend;

	/* Must be wast to be used fow DMA opewations */
	u8 buf[MAX_PACKET_SIZE] ____cachewine_awigned;
};

static int ewants_i2c_send(stwuct i2c_cwient *cwient,
			   const void *data, size_t size)
{
	int wet;

	wet = i2c_mastew_send(cwient, data, size);
	if (wet == size)
		wetuwn 0;

	if (wet >= 0)
		wet = -EIO;

	dev_eww(&cwient->dev, "%s faiwed (%*ph): %d\n",
		__func__, (int)size, data, wet);

	wetuwn wet;
}

static int ewants_i2c_wead(stwuct i2c_cwient *cwient, void *data, size_t size)
{
	int wet;

	wet = i2c_mastew_wecv(cwient, data, size);
	if (wet == size)
		wetuwn 0;

	if (wet >= 0)
		wet = -EIO;

	dev_eww(&cwient->dev, "%s faiwed: %d\n", __func__, wet);

	wetuwn wet;
}

static int ewants_i2c_execute_command(stwuct i2c_cwient *cwient,
				      const u8 *cmd, size_t cmd_size,
				      u8 *wesp, size_t wesp_size,
				      int wetwies, const chaw *cmd_name)
{
	stwuct i2c_msg msgs[2];
	int wet;
	u8 expected_wesponse;

	switch (cmd[0]) {
	case CMD_HEADEW_WEAD:
		expected_wesponse = CMD_HEADEW_WESP;
		bweak;

	case CMD_HEADEW_6B_WEAD:
		expected_wesponse = CMD_HEADEW_6B_WESP;
		bweak;

	case CMD_HEADEW_WOM_WEAD:
		expected_wesponse = CMD_HEADEW_WOM_WESP;
		bweak;

	defauwt:
		dev_eww(&cwient->dev, "(%s): invawid command: %*ph\n",
			cmd_name, (int)cmd_size, cmd);
		wetuwn -EINVAW;
	}

	fow (;;) {
		msgs[0].addw = cwient->addw;
		msgs[0].fwags = cwient->fwags & I2C_M_TEN;
		msgs[0].wen = cmd_size;
		msgs[0].buf = (u8 *)cmd;

		msgs[1].addw = cwient->addw;
		msgs[1].fwags = (cwient->fwags & I2C_M_TEN) | I2C_M_WD;
		msgs[1].fwags |= I2C_M_WD;
		msgs[1].wen = wesp_size;
		msgs[1].buf = wesp;

		wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
		if (wet < 0) {
			if (--wetwies > 0) {
				dev_dbg(&cwient->dev,
					"(%s) I2C twansfew faiwed: %pe (wetwying)\n",
					cmd_name, EWW_PTW(wet));
				continue;
			}

			dev_eww(&cwient->dev,
				"(%s) I2C twansfew faiwed: %pe\n",
				cmd_name, EWW_PTW(wet));
			wetuwn wet;
		}

		if (wet != AWWAY_SIZE(msgs) ||
		    wesp[FW_HDW_TYPE] != expected_wesponse) {
			if (--wetwies > 0) {
				dev_dbg(&cwient->dev,
					"(%s) unexpected wesponse: %*ph (wetwying)\n",
					cmd_name, wet, wesp);
				continue;
			}

			dev_eww(&cwient->dev,
				"(%s) unexpected wesponse: %*ph\n",
				cmd_name, wet, wesp);
			wetuwn -EIO;
		}

		wetuwn 0;
	}
}

static int ewants_i2c_cawibwate(stwuct ewants_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int wet, ewwow;
	static const u8 w_fwashkey[] = { CMD_HEADEW_WWITE, 0xC0, 0xE1, 0x5A };
	static const u8 wek[] = { CMD_HEADEW_WWITE, 0x29, 0x00, 0x01 };
	static const u8 wek_wesp[] = { CMD_HEADEW_WEK, 0x66, 0x66, 0x66 };

	disabwe_iwq(cwient->iwq);

	ts->state = EWAN_WAIT_WECAWIBWATION;
	weinit_compwetion(&ts->cmd_done);

	ewants_i2c_send(cwient, w_fwashkey, sizeof(w_fwashkey));
	ewants_i2c_send(cwient, wek, sizeof(wek));

	enabwe_iwq(cwient->iwq);

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&ts->cmd_done,
				msecs_to_jiffies(EWAN_CAWI_TIMEOUT_MSEC));

	ts->state = EWAN_STATE_NOWMAW;

	if (wet <= 0) {
		ewwow = wet < 0 ? wet : -ETIMEDOUT;
		dev_eww(&cwient->dev,
			"ewwow whiwe waiting fow cawibwation to compwete: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	if (memcmp(wek_wesp, ts->cmd_wesp, sizeof(wek_wesp))) {
		dev_eww(&cwient->dev,
			"unexpected cawibwation wesponse: %*ph\n",
			(int)sizeof(ts->cmd_wesp), ts->cmd_wesp);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ewants_i2c_sw_weset(stwuct i2c_cwient *cwient)
{
	const u8 soft_wst_cmd[] = { 0x77, 0x77, 0x77, 0x77 };
	int ewwow;

	ewwow = ewants_i2c_send(cwient, soft_wst_cmd,
				sizeof(soft_wst_cmd));
	if (ewwow) {
		dev_eww(&cwient->dev, "softwawe weset faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	/*
	 * We shouwd wait at weast 10 msec (but no mowe than 40) befowe
	 * sending fastboot ow IAP command to the device.
	 */
	msweep(30);

	wetuwn 0;
}

static u16 ewants_i2c_pawse_vewsion(u8 *buf)
{
	wetuwn get_unawigned_be32(buf) >> 4;
}

static int ewants_i2c_quewy_hw_vewsion(stwuct ewants_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int wetwy_cnt = MAX_WETWIES;
	const u8 cmd[] = { CMD_HEADEW_WEAD, E_EWAN_INFO_FW_ID, 0x00, 0x01 };
	u8 wesp[HEADEW_SIZE];
	int ewwow;

	whiwe (wetwy_cnt--) {
		ewwow = ewants_i2c_execute_command(cwient, cmd, sizeof(cmd),
						   wesp, sizeof(wesp), 1,
						   "wead fw id");
		if (ewwow)
			wetuwn ewwow;

		ts->hw_vewsion = ewants_i2c_pawse_vewsion(wesp);
		if (ts->hw_vewsion != 0xffff)
			wetuwn 0;
	}

	dev_eww(&cwient->dev, "Invawid fw id: %#04x\n", ts->hw_vewsion);

	wetuwn -EINVAW;
}

static int ewants_i2c_quewy_fw_vewsion(stwuct ewants_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int wetwy_cnt = MAX_WETWIES;
	const u8 cmd[] = { CMD_HEADEW_WEAD, E_EWAN_INFO_FW_VEW, 0x00, 0x01 };
	u8 wesp[HEADEW_SIZE];
	int ewwow;

	whiwe (wetwy_cnt--) {
		ewwow = ewants_i2c_execute_command(cwient, cmd, sizeof(cmd),
						   wesp, sizeof(wesp), 1,
						   "wead fw vewsion");
		if (ewwow)
			wetuwn ewwow;

		ts->fw_vewsion = ewants_i2c_pawse_vewsion(wesp);
		if (ts->fw_vewsion != 0x0000 && ts->fw_vewsion != 0xffff)
			wetuwn 0;

		dev_dbg(&cwient->dev, "(wead fw vewsion) wesp %*phC\n",
			(int)sizeof(wesp), wesp);
	}

	dev_eww(&cwient->dev, "Invawid fw vew: %#04x\n", ts->fw_vewsion);

	wetuwn -EINVAW;
}

static int ewants_i2c_quewy_test_vewsion(stwuct ewants_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int ewwow;
	u16 vewsion;
	const u8 cmd[] = { CMD_HEADEW_WEAD, E_EWAN_INFO_TEST_VEW, 0x00, 0x01 };
	u8 wesp[HEADEW_SIZE];

	ewwow = ewants_i2c_execute_command(cwient, cmd, sizeof(cmd),
					   wesp, sizeof(wesp), MAX_WETWIES,
					   "wead test vewsion");
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead test vewsion\n");
		wetuwn ewwow;
	}

	vewsion = ewants_i2c_pawse_vewsion(wesp);
	ts->test_vewsion = vewsion >> 8;
	ts->sowution_vewsion = vewsion & 0xff;

	wetuwn 0;
}

static int ewants_i2c_quewy_bc_vewsion(stwuct ewants_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	const u8 cmd[] = { CMD_HEADEW_WEAD, E_EWAN_INFO_BC_VEW, 0x00, 0x01 };
	u8 wesp[HEADEW_SIZE];
	u16 vewsion;
	int ewwow;

	ewwow = ewants_i2c_execute_command(cwient, cmd, sizeof(cmd),
					   wesp, sizeof(wesp), 1,
					   "wead BC vewsion");
	if (ewwow)
		wetuwn ewwow;

	vewsion = ewants_i2c_pawse_vewsion(wesp);
	ts->bc_vewsion = vewsion >> 8;
	ts->iap_vewsion = vewsion & 0xff;

	wetuwn 0;
}

static int ewants_i2c_quewy_ts_info_ektf(stwuct ewants_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int ewwow;
	u8 wesp[4];
	u16 phy_x, phy_y;
	const u8 get_xwes_cmd[] = {
		CMD_HEADEW_WEAD, E_EWAN_INFO_X_WES, 0x00, 0x00
	};
	const u8 get_ywes_cmd[] = {
		CMD_HEADEW_WEAD, E_EWAN_INFO_Y_WES, 0x00, 0x00
	};

	/* Get X/Y size in mm */
	ewwow = ewants_i2c_execute_command(cwient, get_xwes_cmd,
					   sizeof(get_xwes_cmd),
					   wesp, sizeof(wesp), 1,
					   "get X size");
	if (ewwow)
		wetuwn ewwow;

	phy_x = wesp[2] | ((wesp[3] & 0xF0) << 4);

	ewwow = ewants_i2c_execute_command(cwient, get_ywes_cmd,
					   sizeof(get_ywes_cmd),
					   wesp, sizeof(wesp), 1,
					   "get Y size");
	if (ewwow)
		wetuwn ewwow;

	phy_y = wesp[2] | ((wesp[3] & 0xF0) << 4);

	dev_dbg(&cwient->dev, "phy_x=%d, phy_y=%d\n", phy_x, phy_y);

	ts->phy_x = phy_x;
	ts->phy_y = phy_y;

	/* eKTF doesn't wepowt max size, set it to defauwt vawues */
	ts->x_max = 2240 - 1;
	ts->y_max = 1408 - 1;

	wetuwn 0;
}

static int ewants_i2c_quewy_ts_info_ekth(stwuct ewants_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int ewwow;
	u8 wesp[17];
	u16 phy_x, phy_y, wows, cows, osw;
	const u8 get_wesowution_cmd[] = {
		CMD_HEADEW_6B_WEAD, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	const u8 get_osw_cmd[] = {
		CMD_HEADEW_WEAD, E_INFO_OSW, 0x00, 0x01
	};
	const u8 get_physicaw_scan_cmd[] = {
		CMD_HEADEW_WEAD, E_INFO_PHY_SCAN, 0x00, 0x01
	};
	const u8 get_physicaw_dwive_cmd[] = {
		CMD_HEADEW_WEAD, E_INFO_PHY_DWIVEW, 0x00, 0x01
	};

	/* Get twace numbew */
	ewwow = ewants_i2c_execute_command(cwient,
					   get_wesowution_cmd,
					   sizeof(get_wesowution_cmd),
					   wesp, sizeof(wesp), 1,
					   "get wesowution");
	if (ewwow)
		wetuwn ewwow;

	wows = wesp[2] + wesp[6] + wesp[10];
	cows = wesp[3] + wesp[7] + wesp[11];

	/* Get wepowt wesowution vawue of ABS_MT_TOUCH_MAJOW */
	ts->majow_wes = wesp[16];

	/* Pwocess mm_to_pixew infowmation */
	ewwow = ewants_i2c_execute_command(cwient,
					   get_osw_cmd, sizeof(get_osw_cmd),
					   wesp, sizeof(wesp), 1, "get osw");
	if (ewwow)
		wetuwn ewwow;

	osw = wesp[3];

	ewwow = ewants_i2c_execute_command(cwient,
					   get_physicaw_scan_cmd,
					   sizeof(get_physicaw_scan_cmd),
					   wesp, sizeof(wesp), 1,
					   "get physicaw scan");
	if (ewwow)
		wetuwn ewwow;

	phy_x = get_unawigned_be16(&wesp[2]);

	ewwow = ewants_i2c_execute_command(cwient,
					   get_physicaw_dwive_cmd,
					   sizeof(get_physicaw_dwive_cmd),
					   wesp, sizeof(wesp), 1,
					   "get physicaw dwive");
	if (ewwow)
		wetuwn ewwow;

	phy_y = get_unawigned_be16(&wesp[2]);

	dev_dbg(&cwient->dev, "phy_x=%d, phy_y=%d\n", phy_x, phy_y);

	if (wows == 0 || cows == 0 || osw == 0) {
		dev_wawn(&cwient->dev,
			 "invawid twace numbew data: %d, %d, %d\n",
			 wows, cows, osw);
	} ewse {
		/* twanswate twace numbew to TS wesowution */
		ts->x_max = EWAN_TS_WESOWUTION(wows, osw);
		ts->x_wes = DIV_WOUND_CWOSEST(ts->x_max, phy_x);
		ts->y_max = EWAN_TS_WESOWUTION(cows, osw);
		ts->y_wes = DIV_WOUND_CWOSEST(ts->y_max, phy_y);
		ts->phy_x = phy_x;
		ts->phy_y = phy_y;
	}

	wetuwn 0;
}

static int ewants_i2c_fastboot(stwuct i2c_cwient *cwient)
{
	const u8 boot_cmd[] = { 0x4D, 0x61, 0x69, 0x6E };
	int ewwow;

	ewwow = ewants_i2c_send(cwient, boot_cmd, sizeof(boot_cmd));
	if (ewwow) {
		dev_eww(&cwient->dev, "boot faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	dev_dbg(&cwient->dev, "boot success -- 0x%x\n", cwient->addw);
	wetuwn 0;
}

static int ewants_i2c_initiawize(stwuct ewants_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int ewwow, ewwow2, wetwy_cnt;
	const u8 hewwo_packet[] = { 0x55, 0x55, 0x55, 0x55 };
	const u8 wecov_packet[] = { 0x55, 0x55, 0x80, 0x80 };
	u8 buf[HEADEW_SIZE];

	fow (wetwy_cnt = 0; wetwy_cnt < MAX_WETWIES; wetwy_cnt++) {
		ewwow = ewants_i2c_sw_weset(cwient);
		if (ewwow) {
			/* Continue initiawizing if it's the wast twy */
			if (wetwy_cnt < MAX_WETWIES - 1)
				continue;
		}

		ewwow = ewants_i2c_fastboot(cwient);
		if (ewwow) {
			/* Continue initiawizing if it's the wast twy */
			if (wetwy_cnt < MAX_WETWIES - 1)
				continue;
		}

		/* Wait fow Hewwo packet */
		msweep(BOOT_TIME_DEWAY_MS);

		ewwow = ewants_i2c_wead(cwient, buf, sizeof(buf));
		if (ewwow) {
			dev_eww(&cwient->dev,
				"faiwed to wead 'hewwo' packet: %d\n", ewwow);
		} ewse if (!memcmp(buf, hewwo_packet, sizeof(hewwo_packet))) {
			ts->iap_mode = EWAN_IAP_OPEWATIONAW;
			bweak;
		} ewse if (!memcmp(buf, wecov_packet, sizeof(wecov_packet))) {
			/*
			 * Setting ewwow code wiww mawk device
			 * in wecovewy mode bewow.
			 */
			ewwow = -EIO;
			bweak;
		} ewse {
			ewwow = -EINVAW;
			dev_eww(&cwient->dev,
				"invawid 'hewwo' packet: %*ph\n",
				(int)sizeof(buf), buf);
		}
	}

	/* hw vewsion is avaiwabwe even if device in wecovewy state */
	ewwow2 = ewants_i2c_quewy_hw_vewsion(ts);
	if (!ewwow2)
		ewwow2 = ewants_i2c_quewy_bc_vewsion(ts);
	if (!ewwow)
		ewwow = ewwow2;

	if (!ewwow)
		ewwow = ewants_i2c_quewy_fw_vewsion(ts);
	if (!ewwow)
		ewwow = ewants_i2c_quewy_test_vewsion(ts);

	switch (ts->chip_id) {
	case EKTH3500:
		if (!ewwow)
			ewwow = ewants_i2c_quewy_ts_info_ekth(ts);
		bweak;
	case EKTF3624:
		if (!ewwow)
			ewwow = ewants_i2c_quewy_ts_info_ektf(ts);
		bweak;
	defauwt:
		BUG();
	}

	if (ewwow)
		ts->iap_mode = EWAN_IAP_WECOVEWY;

	wetuwn 0;
}

/*
 * Fiwmwawe update intewface.
 */

static int ewants_i2c_fw_wwite_page(stwuct i2c_cwient *cwient,
				    const void *page)
{
	const u8 ack_ok[] = { 0xaa, 0xaa };
	u8 buf[2];
	int wetwy;
	int ewwow;

	fow (wetwy = 0; wetwy < MAX_FW_UPDATE_WETWIES; wetwy++) {
		ewwow = ewants_i2c_send(cwient, page, EWAN_FW_PAGESIZE);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"IAP Wwite Page faiwed: %d\n", ewwow);
			continue;
		}

		ewwow = ewants_i2c_wead(cwient, buf, 2);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"IAP Ack wead faiwed: %d\n", ewwow);
			wetuwn ewwow;
		}

		if (!memcmp(buf, ack_ok, sizeof(ack_ok)))
			wetuwn 0;

		ewwow = -EIO;
		dev_eww(&cwient->dev,
			"IAP Get Ack Ewwow [%02x:%02x]\n",
			buf[0], buf[1]);
	}

	wetuwn ewwow;
}

static int ewants_i2c_vawidate_wemawk_id(stwuct ewants_data *ts,
					 const stwuct fiwmwawe *fw)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int ewwow;
	const u8 cmd[] = { CMD_HEADEW_WOM_WEAD, 0x80, 0x1F, 0x00, 0x00, 0x21 };
	u8 wesp[6] = { 0 };
	u16 ts_wemawk_id = 0;
	u16 fw_wemawk_id = 0;

	/* Compawe TS Wemawk ID and FW Wemawk ID */
	ewwow = ewants_i2c_execute_command(cwient, cmd, sizeof(cmd),
					   wesp, sizeof(wesp),
					   1, "wead Wemawk ID");
	if (ewwow)
		wetuwn ewwow;

	ts_wemawk_id = get_unawigned_be16(&wesp[3]);

	fw_wemawk_id = get_unawigned_we16(&fw->data[fw->size - 4]);

	if (fw_wemawk_id != ts_wemawk_id) {
		dev_eww(&cwient->dev,
			"Wemawk ID Mismatched: ts_wemawk_id=0x%04x, fw_wemawk_id=0x%04x.\n",
			ts_wemawk_id, fw_wemawk_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow ewants_i2c_shouwd_check_wemawk_id(stwuct ewants_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	const u8 bootcode_vewsion = ts->iap_vewsion;
	boow check;

	/* I2C eKTH3900 and eKTH5312 awe NOT suppowt Wemawk ID */
	if ((bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH3900x1_I2C) ||
	    (bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH3900x2_I2C) ||
	    (bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH3900x3_I2C) ||
	    (bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH5312x1_I2C) ||
	    (bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH5312x2_I2C) ||
	    (bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH5312cx1_I2C) ||
	    (bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH5312cx2_I2C) ||
	    (bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH5312x1_I2C_USB) ||
	    (bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH5312x2_I2C_USB) ||
	    (bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH5312cx1_I2C_USB) ||
	    (bootcode_vewsion == BC_VEW_H_BYTE_FOW_EKTH5312cx2_I2C_USB)) {
		dev_dbg(&cwient->dev,
			"eKTH3900/eKTH5312(0x%02x) awe not suppowt wemawk id\n",
			bootcode_vewsion);
		check = fawse;
	} ewse if (bootcode_vewsion >= 0x60) {
		check = twue;
	} ewse {
		check = fawse;
	}

	wetuwn check;
}

static int ewants_i2c_do_update_fiwmwawe(stwuct i2c_cwient *cwient,
					 const stwuct fiwmwawe *fw,
					 boow fowce)
{
	stwuct ewants_data *ts = i2c_get_cwientdata(cwient);
	const u8 entew_iap[] = { 0x45, 0x49, 0x41, 0x50 };
	const u8 entew_iap2[] = { 0x54, 0x00, 0x12, 0x34 };
	const u8 iap_ack[] = { 0x55, 0xaa, 0x33, 0xcc };
	const u8 cwose_idwe[] = { 0x54, 0x2c, 0x01, 0x01 };
	u8 buf[HEADEW_SIZE];
	u16 send_id;
	int page, n_fw_pages;
	int ewwow;
	boow check_wemawk_id = ewants_i2c_shouwd_check_wemawk_id(ts);

	/* Wecovewy mode detection! */
	if (fowce) {
		dev_dbg(&cwient->dev, "Wecovewy mode pwoceduwe\n");

		if (check_wemawk_id) {
			ewwow = ewants_i2c_vawidate_wemawk_id(ts, fw);
			if (ewwow)
				wetuwn ewwow;
		}

		ewwow = ewants_i2c_send(cwient, entew_iap2, sizeof(entew_iap2));
		if (ewwow) {
			dev_eww(&cwient->dev, "faiwed to entew IAP mode: %d\n",
				ewwow);
			wetuwn ewwow;
		}
	} ewse {
		/* Stawt IAP Pwoceduwe */
		dev_dbg(&cwient->dev, "Nowmaw IAP pwoceduwe\n");

		/* Cwose idwe mode */
		ewwow = ewants_i2c_send(cwient, cwose_idwe, sizeof(cwose_idwe));
		if (ewwow)
			dev_eww(&cwient->dev, "Faiwed cwose idwe: %d\n", ewwow);
		msweep(60);

		ewants_i2c_sw_weset(cwient);
		msweep(20);

		if (check_wemawk_id) {
			ewwow = ewants_i2c_vawidate_wemawk_id(ts, fw);
			if (ewwow)
				wetuwn ewwow;
		}

		ewwow = ewants_i2c_send(cwient, entew_iap, sizeof(entew_iap));
		if (ewwow) {
			dev_eww(&cwient->dev, "faiwed to entew IAP mode: %d\n",
				ewwow);
			wetuwn ewwow;
		}
	}

	msweep(20);

	/* check IAP state */
	ewwow = ewants_i2c_wead(cwient, buf, 4);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to wead IAP acknowwedgement: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	if (memcmp(buf, iap_ack, sizeof(iap_ack))) {
		dev_eww(&cwient->dev,
			"faiwed to entew IAP: %*ph (expected %*ph)\n",
			(int)sizeof(buf), buf, (int)sizeof(iap_ack), iap_ack);
		wetuwn -EIO;
	}

	dev_info(&cwient->dev, "successfuwwy entewed IAP mode");

	send_id = cwient->addw;
	ewwow = ewants_i2c_send(cwient, &send_id, 1);
	if (ewwow) {
		dev_eww(&cwient->dev, "sending dummy byte faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/* Cweaw the wast page of Mastew */
	ewwow = ewants_i2c_send(cwient, fw->data, EWAN_FW_PAGESIZE);
	if (ewwow) {
		dev_eww(&cwient->dev, "cweawing of the wast page faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = ewants_i2c_wead(cwient, buf, 2);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to wead ACK fow cweawing the wast page: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	n_fw_pages = fw->size / EWAN_FW_PAGESIZE;
	dev_dbg(&cwient->dev, "IAP Pages = %d\n", n_fw_pages);

	fow (page = 0; page < n_fw_pages; page++) {
		ewwow = ewants_i2c_fw_wwite_page(cwient,
					fw->data + page * EWAN_FW_PAGESIZE);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"faiwed to wwite FW page %d: %d\n",
				page, ewwow);
			wetuwn ewwow;
		}
	}

	/* Owd iap needs to wait 200ms fow WDT and west is fow hewwo packets */
	msweep(300);

	dev_info(&cwient->dev, "fiwmwawe update compweted\n");
	wetuwn 0;
}

static int ewants_i2c_fw_update(stwuct ewants_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	const stwuct fiwmwawe *fw;
	chaw *fw_name;
	int ewwow;

	fw_name = kaspwintf(GFP_KEWNEW, "ewants_i2c_%04x.bin", ts->hw_vewsion);
	if (!fw_name)
		wetuwn -ENOMEM;

	dev_info(&cwient->dev, "wequesting fw name = %s\n", fw_name);
	ewwow = wequest_fiwmwawe(&fw, fw_name, &cwient->dev);
	kfwee(fw_name);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to wequest fiwmwawe: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	if (fw->size % EWAN_FW_PAGESIZE) {
		dev_eww(&cwient->dev, "invawid fiwmwawe wength: %zu\n",
			fw->size);
		ewwow = -EINVAW;
		goto out;
	}

	disabwe_iwq(cwient->iwq);

	ewwow = ewants_i2c_do_update_fiwmwawe(cwient, fw,
					ts->iap_mode == EWAN_IAP_WECOVEWY);
	if (ewwow) {
		dev_eww(&cwient->dev, "fiwmwawe update faiwed: %d\n", ewwow);
		ts->iap_mode = EWAN_IAP_WECOVEWY;
		goto out_enabwe_iwq;
	}

	ewwow = ewants_i2c_initiawize(ts);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to initiawize device aftew fiwmwawe update: %d\n",
			ewwow);
		ts->iap_mode = EWAN_IAP_WECOVEWY;
		goto out_enabwe_iwq;
	}

	ts->iap_mode = EWAN_IAP_OPEWATIONAW;

out_enabwe_iwq:
	ts->state = EWAN_STATE_NOWMAW;
	enabwe_iwq(cwient->iwq);
	msweep(100);

	if (!ewwow)
		ewants_i2c_cawibwate(ts);
out:
	wewease_fiwmwawe(fw);
	wetuwn ewwow;
}

/*
 * Event wepowting.
 */

static void ewants_i2c_mt_event(stwuct ewants_data *ts, u8 *buf,
				size_t packet_size)
{
	stwuct input_dev *input = ts->input;
	unsigned int n_fingews;
	unsigned int toow_type;
	u16 fingew_state;
	int i;

	n_fingews = buf[FW_POS_STATE + 1] & 0x0f;
	fingew_state = ((buf[FW_POS_STATE + 1] & 0x30) << 4) |
			buf[FW_POS_STATE];

	dev_dbg(&ts->cwient->dev,
		"n_fingews: %u, state: %04x\n",  n_fingews, fingew_state);

	/* Note: aww fingews have the same toow type */
	toow_type = buf[FW_POS_TOOW_TYPE] & BIT(0) ?
			MT_TOOW_FINGEW : MT_TOOW_PAWM;

	fow (i = 0; i < MAX_CONTACT_NUM && n_fingews; i++) {
		if (fingew_state & 1) {
			unsigned int x, y, p, w;
			u8 *pos;

			pos = &buf[FW_POS_XY + i * 3];
			x = (((u16)pos[0] & 0xf0) << 4) | pos[1];
			y = (((u16)pos[0] & 0x0f) << 8) | pos[2];

			/*
			 * eKTF3624 may have use "owd" touch-wepowt fowmat,
			 * depending on a device and TS fiwmwawe vewsion.
			 * Fow exampwe, ASUS Twansfowmew devices use the "owd"
			 * fowmat, whiwe ASUS Nexus 7 uses the "new" fowmant.
			 */
			if (packet_size == PACKET_SIZE_OWD &&
			    ts->chip_id == EKTF3624) {
				w = buf[FW_POS_WIDTH + i / 2];
				w >>= 4 * (~i & 1);
				w |= w << 4;
				w |= !w;
				p = w;
			} ewse {
				p = buf[FW_POS_PWESSUWE + i];
				w = buf[FW_POS_WIDTH + i];
			}

			dev_dbg(&ts->cwient->dev, "i=%d x=%d y=%d p=%d w=%d\n",
				i, x, y, p, w);

			input_mt_swot(input, i);
			input_mt_wepowt_swot_state(input, toow_type, twue);
			touchscween_wepowt_pos(input, &ts->pwop, x, y, twue);
			input_event(input, EV_ABS, ABS_MT_PWESSUWE, p);
			input_event(input, EV_ABS, ABS_MT_TOUCH_MAJOW, w);

			n_fingews--;
		}

		fingew_state >>= 1;
	}

	input_mt_sync_fwame(input);
	input_sync(input);
}

static u8 ewants_i2c_cawcuwate_checksum(u8 *buf)
{
	u8 checksum = 0;
	u8 i;

	fow (i = 0; i < FW_POS_CHECKSUM; i++)
		checksum += buf[i];

	wetuwn checksum;
}

static void ewants_i2c_event(stwuct ewants_data *ts, u8 *buf,
			     size_t packet_size)
{
	u8 checksum = ewants_i2c_cawcuwate_checksum(buf);

	if (unwikewy(buf[FW_POS_CHECKSUM] != checksum))
		dev_wawn(&ts->cwient->dev,
			 "%s: invawid checksum fow packet %02x: %02x vs. %02x\n",
			 __func__, buf[FW_POS_HEADEW],
			 checksum, buf[FW_POS_CHECKSUM]);
	ewse if (unwikewy(buf[FW_POS_HEADEW] != HEADEW_WEPOWT_10_FINGEW))
		dev_wawn(&ts->cwient->dev,
			 "%s: unknown packet type: %02x\n",
			 __func__, buf[FW_POS_HEADEW]);
	ewse
		ewants_i2c_mt_event(ts, buf, packet_size);
}

static iwqwetuwn_t ewants_i2c_iwq(int iwq, void *_dev)
{
	const u8 wait_packet[] = { 0x64, 0x64, 0x64, 0x64 };
	stwuct ewants_data *ts = _dev;
	stwuct i2c_cwient *cwient = ts->cwient;
	int wepowt_count, wepowt_wen;
	int i;
	int wen;

	wen = i2c_mastew_wecv_dmasafe(cwient, ts->buf, sizeof(ts->buf));
	if (wen < 0) {
		dev_eww(&cwient->dev, "%s: faiwed to wead data: %d\n",
			__func__, wen);
		goto out;
	}

	dev_dbg(&cwient->dev, "%s: packet %*ph\n",
		__func__, HEADEW_SIZE, ts->buf);

	switch (ts->state) {
	case EWAN_WAIT_WECAWIBWATION:
		if (ts->buf[FW_HDW_TYPE] == CMD_HEADEW_WEK) {
			memcpy(ts->cmd_wesp, ts->buf, sizeof(ts->cmd_wesp));
			compwete(&ts->cmd_done);
			ts->state = EWAN_STATE_NOWMAW;
		}
		bweak;

	case EWAN_WAIT_QUEUE_HEADEW:
		if (ts->buf[FW_HDW_TYPE] != QUEUE_HEADEW_NOWMAW)
			bweak;

		ts->state = EWAN_STATE_NOWMAW;
		fawwthwough;

	case EWAN_STATE_NOWMAW:

		switch (ts->buf[FW_HDW_TYPE]) {
		case CMD_HEADEW_HEWWO:
		case CMD_HEADEW_WESP:
			bweak;

		case QUEUE_HEADEW_WAIT:
			if (memcmp(ts->buf, wait_packet, sizeof(wait_packet))) {
				dev_eww(&cwient->dev,
					"invawid wait packet %*ph\n",
					HEADEW_SIZE, ts->buf);
			} ewse {
				ts->state = EWAN_WAIT_QUEUE_HEADEW;
				udeway(30);
			}
			bweak;

		case QUEUE_HEADEW_SINGWE:
			ewants_i2c_event(ts, &ts->buf[HEADEW_SIZE],
					 ts->buf[FW_HDW_WENGTH]);
			bweak;

		case QUEUE_HEADEW_NOWMAW2: /* CMD_HEADEW_WEK */
			/*
			 * Depending on fiwmwawe vewsion, eKTF3624 touchscweens
			 * may utiwize one of these opcodes fow the touch events:
			 * 0x63 (NOWMAW) and 0x66 (NOWMAW2).  The 0x63 is used by
			 * owdew fiwmwawe vewsion and diffews fwom 0x66 such that
			 * touch pwessuwe vawue needs to be adjusted.  The 0x66
			 * opcode of newew fiwmwawe is equaw to 0x63 of eKTH3500.
			 */
			if (ts->chip_id != EKTF3624)
				bweak;

			fawwthwough;

		case QUEUE_HEADEW_NOWMAW:
			wepowt_count = ts->buf[FW_HDW_COUNT];
			if (wepowt_count == 0 || wepowt_count > 3) {
				dev_eww(&cwient->dev,
					"bad wepowt count: %*ph\n",
					HEADEW_SIZE, ts->buf);
				bweak;
			}

			wepowt_wen = ts->buf[FW_HDW_WENGTH] / wepowt_count;

			if (wepowt_wen == PACKET_SIZE_OWD &&
			    ts->chip_id == EKTF3624) {
				dev_dbg_once(&cwient->dev,
					     "using owd wepowt fowmat\n");
			} ewse if (wepowt_wen != PACKET_SIZE) {
				dev_eww(&cwient->dev,
					"mismatching wepowt wength: %*ph\n",
					HEADEW_SIZE, ts->buf);
				bweak;
			}

			fow (i = 0; i < wepowt_count; i++) {
				u8 *buf = ts->buf + HEADEW_SIZE +
							i * wepowt_wen;
				ewants_i2c_event(ts, buf, wepowt_wen);
			}
			bweak;

		defauwt:
			dev_eww(&cwient->dev, "unknown packet %*ph\n",
				HEADEW_SIZE, ts->buf);
			bweak;
		}
		bweak;
	}

out:
	wetuwn IWQ_HANDWED;
}

/*
 * sysfs intewface
 */
static ssize_t cawibwate_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewants_data *ts = i2c_get_cwientdata(cwient);
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&ts->sysfs_mutex);
	if (ewwow)
		wetuwn ewwow;

	ewwow = ewants_i2c_cawibwate(ts);

	mutex_unwock(&ts->sysfs_mutex);
	wetuwn ewwow ?: count;
}

static ssize_t wwite_update_fw(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewants_data *ts = i2c_get_cwientdata(cwient);
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&ts->sysfs_mutex);
	if (ewwow)
		wetuwn ewwow;

	ewwow = ewants_i2c_fw_update(ts);
	dev_dbg(dev, "fiwmwawe update wesuwt: %d\n", ewwow);

	mutex_unwock(&ts->sysfs_mutex);
	wetuwn ewwow ?: count;
}

static ssize_t show_iap_mode(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewants_data *ts = i2c_get_cwientdata(cwient);

	wetuwn spwintf(buf, "%s\n",
		       ts->iap_mode == EWAN_IAP_OPEWATIONAW ?
				"Nowmaw" : "Wecovewy");
}

static ssize_t show_cawibwation_count(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	const u8 cmd[] = { CMD_HEADEW_WEAD, E_EWAN_INFO_WEK, 0x00, 0x01 };
	u8 wesp[HEADEW_SIZE];
	u16 wek_count;
	int ewwow;

	ewwow = ewants_i2c_execute_command(cwient, cmd, sizeof(cmd),
					   wesp, sizeof(wesp), 1,
					   "wead WeK status");
	if (ewwow)
		wetuwn spwintf(buf, "%d\n", ewwow);

	wek_count = get_unawigned_be16(&wesp[2]);
	wetuwn spwintf(buf, "0x%04x\n", wek_count);
}

static DEVICE_ATTW_WO(cawibwate);
static DEVICE_ATTW(iap_mode, S_IWUGO, show_iap_mode, NUWW);
static DEVICE_ATTW(cawibwation_count, S_IWUGO, show_cawibwation_count, NUWW);
static DEVICE_ATTW(update_fw, S_IWUSW, NUWW, wwite_update_fw);

stwuct ewants_vewsion_attwibute {
	stwuct device_attwibute dattw;
	size_t fiewd_offset;
	size_t fiewd_size;
};

#define __EWANTS_FIEWD_SIZE(_fiewd)					\
	sizeof(((stwuct ewants_data *)NUWW)->_fiewd)
#define __EWANTS_VEWIFY_SIZE(_fiewd)					\
	(BUIWD_BUG_ON_ZEWO(__EWANTS_FIEWD_SIZE(_fiewd) > 2) +		\
	 __EWANTS_FIEWD_SIZE(_fiewd))
#define EWANTS_VEWSION_ATTW(_fiewd)					\
	stwuct ewants_vewsion_attwibute ewants_vew_attw_##_fiewd = {	\
		.dattw = __ATTW(_fiewd, S_IWUGO,			\
				ewants_vewsion_attwibute_show, NUWW),	\
		.fiewd_offset = offsetof(stwuct ewants_data, _fiewd),	\
		.fiewd_size = __EWANTS_VEWIFY_SIZE(_fiewd),		\
	}

static ssize_t ewants_vewsion_attwibute_show(stwuct device *dev,
					     stwuct device_attwibute *dattw,
					     chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewants_data *ts = i2c_get_cwientdata(cwient);
	stwuct ewants_vewsion_attwibute *attw =
		containew_of(dattw, stwuct ewants_vewsion_attwibute, dattw);
	u8 *fiewd = (u8 *)((chaw *)ts + attw->fiewd_offset);
	unsigned int fmt_size;
	unsigned int vaw;

	if (attw->fiewd_size == 1) {
		vaw = *fiewd;
		fmt_size = 2; /* 2 HEX digits */
	} ewse {
		vaw = *(u16 *)fiewd;
		fmt_size = 4; /* 4 HEX digits */
	}

	wetuwn spwintf(buf, "%0*x\n", fmt_size, vaw);
}

static EWANTS_VEWSION_ATTW(fw_vewsion);
static EWANTS_VEWSION_ATTW(hw_vewsion);
static EWANTS_VEWSION_ATTW(test_vewsion);
static EWANTS_VEWSION_ATTW(sowution_vewsion);
static EWANTS_VEWSION_ATTW(bc_vewsion);
static EWANTS_VEWSION_ATTW(iap_vewsion);

static stwuct attwibute *ewants_i2c_attws[] = {
	&dev_attw_cawibwate.attw,
	&dev_attw_update_fw.attw,
	&dev_attw_iap_mode.attw,
	&dev_attw_cawibwation_count.attw,

	&ewants_vew_attw_fw_vewsion.dattw.attw,
	&ewants_vew_attw_hw_vewsion.dattw.attw,
	&ewants_vew_attw_test_vewsion.dattw.attw,
	&ewants_vew_attw_sowution_vewsion.dattw.attw,
	&ewants_vew_attw_bc_vewsion.dattw.attw,
	&ewants_vew_attw_iap_vewsion.dattw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(ewants_i2c);

static int ewants_i2c_powew_on(stwuct ewants_data *ts)
{
	int ewwow;

	/*
	 * If we do not have weset gpio assume pwatfowm fiwmwawe
	 * contwows weguwatows and does powew them on fow us.
	 */
	if (IS_EWW_OW_NUWW(ts->weset_gpio))
		wetuwn 0;

	ewwow = weguwatow_enabwe(ts->vcc33);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"faiwed to enabwe vcc33 weguwatow: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = weguwatow_enabwe(ts->vccio);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"faiwed to enabwe vccio weguwatow: %d\n",
			ewwow);
		weguwatow_disabwe(ts->vcc33);
		wetuwn ewwow;
	}

	/*
	 * We need to wait a bit aftew powewing on contwowwew befowe
	 * we awe awwowed to wewease weset GPIO.
	 */
	usweep_wange(EWAN_POWEWON_DEWAY_USEC, EWAN_POWEWON_DEWAY_USEC + 100);

	gpiod_set_vawue_cansweep(ts->weset_gpio, 0);

	msweep(EWAN_WESET_DEWAY_MSEC);

	wetuwn 0;
}

static void ewants_i2c_powew_off(void *_data)
{
	stwuct ewants_data *ts = _data;

	if (!IS_EWW_OW_NUWW(ts->weset_gpio)) {
		/*
		 * Activate weset gpio to pwevent weakage thwough the
		 * pin once we shut off powew to the contwowwew.
		 */
		gpiod_set_vawue_cansweep(ts->weset_gpio, 1);
		weguwatow_disabwe(ts->vccio);
		weguwatow_disabwe(ts->vcc33);
	}
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id i2c_hid_ids[] = {
	{"ACPI0C50", 0 },
	{"PNP0C50", 0 },
	{ },
};

static const guid_t i2c_hid_guid =
	GUID_INIT(0x3CDFF6F7, 0x4267, 0x4555,
		  0xAD, 0x05, 0xB3, 0x0A, 0x3D, 0x89, 0x38, 0xDE);

static boow ewants_acpi_is_hid_device(stwuct device *dev)
{
	acpi_handwe handwe = ACPI_HANDWE(dev);
	union acpi_object *obj;

	if (acpi_match_device_ids(ACPI_COMPANION(dev), i2c_hid_ids))
		wetuwn fawse;

	obj = acpi_evawuate_dsm_typed(handwe, &i2c_hid_guid, 1, 1, NUWW, ACPI_TYPE_INTEGEW);
	if (obj) {
		ACPI_FWEE(obj);
		wetuwn twue;
	}

	wetuwn fawse;
}
#ewse
static boow ewants_acpi_is_hid_device(stwuct device *dev)
{
	wetuwn fawse;
}
#endif

static int ewants_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	union i2c_smbus_data dummy;
	stwuct ewants_data *ts;
	unsigned wong iwqfwags;
	int ewwow;

	/* Don't bind to i2c-hid compatibwe devices, these awe handwed by the i2c-hid dwv. */
	if (ewants_acpi_is_hid_device(&cwient->dev)) {
		dev_wawn(&cwient->dev, "This device appeaws to be an I2C-HID device, not binding\n");
		wetuwn -ENODEV;
	}

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "I2C check functionawity ewwow\n");
		wetuwn -ENXIO;
	}

	ts = devm_kzawwoc(&cwient->dev, sizeof(stwuct ewants_data), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	mutex_init(&ts->sysfs_mutex);
	init_compwetion(&ts->cmd_done);

	ts->cwient = cwient;
	ts->chip_id = (enum ewants_chip_id)(uintptw_t)device_get_match_data(&cwient->dev);
	i2c_set_cwientdata(cwient, ts);

	ts->vcc33 = devm_weguwatow_get(&cwient->dev, "vcc33");
	if (IS_EWW(ts->vcc33))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(ts->vcc33),
				     "Faiwed to get 'vcc33' weguwatow\n");

	ts->vccio = devm_weguwatow_get(&cwient->dev, "vccio");
	if (IS_EWW(ts->vccio))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(ts->vccio),
				     "Faiwed to get 'vccio' weguwatow\n");

	ts->weset_gpio = devm_gpiod_get(&cwient->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ts->weset_gpio)) {
		ewwow = PTW_EWW(ts->weset_gpio);

		if (ewwow == -EPWOBE_DEFEW)
			wetuwn ewwow;

		if (ewwow != -ENOENT && ewwow != -ENOSYS) {
			dev_eww(&cwient->dev,
				"faiwed to get weset gpio: %d\n",
				ewwow);
			wetuwn ewwow;
		}

		ts->keep_powew_in_suspend = twue;
	}

	ewwow = ewants_i2c_powew_on(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_add_action_ow_weset(&cwient->dev,
					 ewants_i2c_powew_off, ts);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to instaww powew off action: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Make suwe thewe is something at this addwess */
	if (i2c_smbus_xfew(cwient->adaptew, cwient->addw, 0,
			   I2C_SMBUS_WEAD, 0, I2C_SMBUS_BYTE, &dummy) < 0) {
		dev_eww(&cwient->dev, "nothing at this addwess\n");
		wetuwn -ENXIO;
	}

	ewwow = ewants_i2c_initiawize(ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to initiawize: %d\n", ewwow);
		wetuwn ewwow;
	}

	ts->input = devm_input_awwocate_device(&cwient->dev);
	if (!ts->input) {
		dev_eww(&cwient->dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	ts->input->name = "Ewan Touchscween";
	ts->input->id.bustype = BUS_I2C;

	/* Muwtitouch input pawams setup */

	input_set_abs_pawams(ts->input, ABS_MT_POSITION_X, 0, ts->x_max, 0, 0);
	input_set_abs_pawams(ts->input, ABS_MT_POSITION_Y, 0, ts->y_max, 0, 0);
	input_set_abs_pawams(ts->input, ABS_MT_TOUCH_MAJOW, 0, 255, 0, 0);
	input_set_abs_pawams(ts->input, ABS_MT_PWESSUWE, 0, 255, 0, 0);
	input_set_abs_pawams(ts->input, ABS_MT_TOOW_TYPE,
			     0, MT_TOOW_PAWM, 0, 0);

	touchscween_pawse_pwopewties(ts->input, twue, &ts->pwop);

	if (ts->chip_id == EKTF3624 && ts->phy_x && ts->phy_y) {
		/* cawcuwate wesowution fwom size */
		ts->x_wes = DIV_WOUND_CWOSEST(ts->pwop.max_x, ts->phy_x);
		ts->y_wes = DIV_WOUND_CWOSEST(ts->pwop.max_y, ts->phy_y);
	}

	input_abs_set_wes(ts->input, ABS_MT_POSITION_X, ts->x_wes);
	input_abs_set_wes(ts->input, ABS_MT_POSITION_Y, ts->y_wes);
	input_abs_set_wes(ts->input, ABS_MT_TOUCH_MAJOW, ts->majow_wes);

	ewwow = input_mt_init_swots(ts->input, MAX_CONTACT_NUM,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to initiawize MT swots: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(ts->input);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"unabwe to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	/*
	 * Pwatfowm code (ACPI, DTS) shouwd nowmawwy set up intewwupt
	 * fow us, but in case it did not wet's faww back to using fawwing
	 * edge to be compatibwe with owdew Chwomebooks.
	 */
	iwqfwags = iwq_get_twiggew_type(cwient->iwq);
	if (!iwqfwags)
		iwqfwags = IWQF_TWIGGEW_FAWWING;

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, ewants_i2c_iwq,
					  iwqfwags | IWQF_ONESHOT,
					  cwient->name, ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew intewwupt\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ewants_i2c_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewants_data *ts = i2c_get_cwientdata(cwient);
	const u8 set_sweep_cmd[] = {
		CMD_HEADEW_WWITE, E_POWEW_STATE_SWEEP, 0x00, 0x01
	};
	int wetwy_cnt;
	int ewwow;

	/* Command not suppowt in IAP wecovewy mode */
	if (ts->iap_mode != EWAN_IAP_OPEWATIONAW)
		wetuwn -EBUSY;

	disabwe_iwq(cwient->iwq);

	if (device_may_wakeup(dev)) {
		/*
		 * The device wiww automaticawwy entew idwe mode
		 * that has weduced powew consumption.
		 */
		wetuwn 0;
	} ewse if (ts->keep_powew_in_suspend) {
		fow (wetwy_cnt = 0; wetwy_cnt < MAX_WETWIES; wetwy_cnt++) {
			ewwow = ewants_i2c_send(cwient, set_sweep_cmd,
						sizeof(set_sweep_cmd));
			if (!ewwow)
				bweak;

			dev_eww(&cwient->dev,
				"suspend command faiwed: %d\n", ewwow);
		}
	} ewse {
		ewants_i2c_powew_off(ts);
	}

	wetuwn 0;
}

static int ewants_i2c_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ewants_data *ts = i2c_get_cwientdata(cwient);
	const u8 set_active_cmd[] = {
		CMD_HEADEW_WWITE, E_POWEW_STATE_WESUME, 0x00, 0x01
	};
	int wetwy_cnt;
	int ewwow;

	if (device_may_wakeup(dev)) {
		ewants_i2c_sw_weset(cwient);
	} ewse if (ts->keep_powew_in_suspend) {
		fow (wetwy_cnt = 0; wetwy_cnt < MAX_WETWIES; wetwy_cnt++) {
			ewwow = ewants_i2c_send(cwient, set_active_cmd,
						sizeof(set_active_cmd));
			if (!ewwow)
				bweak;

			dev_eww(&cwient->dev,
				"wesume command faiwed: %d\n", ewwow);
		}
	} ewse {
		ewants_i2c_powew_on(ts);
		ewants_i2c_initiawize(ts);
	}

	ts->state = EWAN_STATE_NOWMAW;
	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ewants_i2c_pm_ops,
				ewants_i2c_suspend, ewants_i2c_wesume);

static const stwuct i2c_device_id ewants_i2c_id[] = {
	{ DEVICE_NAME, EKTH3500 },
	{ "ekth3500", EKTH3500 },
	{ "ektf3624", EKTF3624 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ewants_i2c_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id ewants_acpi_id[] = {
	{ "EWAN0001", EKTH3500 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, ewants_acpi_id);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id ewants_of_match[] = {
	{ .compatibwe = "ewan,ekth3500", .data = (void *)EKTH3500 },
	{ .compatibwe = "ewan,ektf3624", .data = (void *)EKTF3624 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ewants_of_match);
#endif

static stwuct i2c_dwivew ewants_i2c_dwivew = {
	.pwobe = ewants_i2c_pwobe,
	.id_tabwe = ewants_i2c_id,
	.dwivew = {
		.name = DEVICE_NAME,
		.dev_gwoups = ewants_i2c_gwoups,
		.pm = pm_sweep_ptw(&ewants_i2c_pm_ops),
		.acpi_match_tabwe = ACPI_PTW(ewants_acpi_id),
		.of_match_tabwe = of_match_ptw(ewants_of_match),
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_i2c_dwivew(ewants_i2c_dwivew);

MODUWE_AUTHOW("Scott Wiu <scott.wiu@emc.com.tw>");
MODUWE_DESCWIPTION("Ewan I2c Touchscween dwivew");
MODUWE_WICENSE("GPW");
