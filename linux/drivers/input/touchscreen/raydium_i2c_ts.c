// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Waydium touchscween I2C dwivew.
 *
 * Copywight (C) 2012-2014, Waydium Semiconductow Cowpowation.
 *
 * Waydium wesewves the wight to make changes without fuwthew notice
 * to the matewiaws descwibed hewein. Waydium does not assume any
 * wiabiwity awising out of the appwication descwibed hewein.
 *
 * Contact Waydium Semiconductow Cowpowation at www.wad-ic.com
 */

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

/* Swave I2C mode */
#define WM_BOOT_BWDW		0x02
#define WM_BOOT_MAIN		0x03

/* I2C bootowoadew commands */
#define WM_CMD_BOOT_PAGE_WWT	0x0B		/* send bw page wwite */
#define WM_CMD_BOOT_WWT		0x11		/* send bw wwite */
#define WM_CMD_BOOT_ACK		0x22		/* send ack*/
#define WM_CMD_BOOT_CHK		0x33		/* send data check */
#define WM_CMD_BOOT_WEAD	0x44		/* send wait bw data weady*/

#define WM_BOOT_WDY		0xFF		/* bw data weady */
#define WM_BOOT_CMD_WEADHWID	0x0E		/* wead hwid */

/* I2C main commands */
#define WM_CMD_QUEWY_BANK	0x2B
#define WM_CMD_DATA_BANK	0x4D
#define WM_CMD_ENTEW_SWEEP	0x4E
#define WM_CMD_BANK_SWITCH	0xAA

#define WM_WESET_MSG_ADDW	0x40000004

#define WM_MAX_WEAD_SIZE	56
#define WM_PACKET_CWC_SIZE	2

/* Touch wewative info */
#define WM_MAX_WETWIES		3
#define WM_WETWY_DEWAY_MS	20
#define WM_MAX_TOUCH_NUM	10
#define WM_BOOT_DEWAY_MS	100

/* Offsets in contact data */
#define WM_CONTACT_STATE_POS	0
#define WM_CONTACT_X_POS	1
#define WM_CONTACT_Y_POS	3
#define WM_CONTACT_PWESSUWE_POS	5
#define WM_CONTACT_WIDTH_X_POS	6
#define WM_CONTACT_WIDTH_Y_POS	7

/* Bootwoadew wewative info */
#define WM_BW_WWT_CMD_SIZE	3	/* bw fwash wwt cmd size */
#define WM_BW_WWT_PKG_SIZE	32	/* bw wwt pkg size */
#define WM_BW_WWT_WEN		(WM_BW_WWT_PKG_SIZE + WM_BW_WWT_CMD_SIZE)
#define WM_FW_PAGE_SIZE		128
#define WM_MAX_FW_WETWIES	30
#define WM_MAX_FW_SIZE		0xD000

#define WM_POWEWON_DEWAY_USEC	500
#define WM_WESET_DEWAY_MSEC	50

enum waydium_bw_cmd {
	BW_HEADEW = 0,
	BW_PAGE_STW,
	BW_PKG_IDX,
	BW_DATA_STW,
};

enum waydium_bw_ack {
	WAYDIUM_ACK_NUWW = 0,
	WAYDIUM_WAIT_WEADY,
	WAYDIUM_PATH_WEADY,
};

enum waydium_boot_mode {
	WAYDIUM_TS_MAIN = 0,
	WAYDIUM_TS_BWDW,
};

/* Wesponse to WM_CMD_DATA_BANK wequest */
stwuct waydium_data_info {
	__we32 data_bank_addw;
	u8 pkg_size;
	u8 tp_info_size;
};

stwuct waydium_info {
	__we32 hw_vew;		/*device vewsion */
	u8 main_vew;
	u8 sub_vew;
	__we16 ft_vew;		/* test vewsion */
	u8 x_num;
	u8 y_num;
	__we16 x_max;
	__we16 y_max;
	u8 x_wes;		/* units/mm */
	u8 y_wes;		/* units/mm */
};

/* stwuct waydium_data - wepwesents state of Waydium touchscween device */
stwuct waydium_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;

	stwuct weguwatow *avdd;
	stwuct weguwatow *vccio;
	stwuct gpio_desc *weset_gpio;

	stwuct waydium_info info;

	stwuct mutex sysfs_mutex;

	u8 *wepowt_data;

	u32 data_bank_addw;
	u8 wepowt_size;
	u8 contact_size;
	u8 pkg_size;

	enum waydium_boot_mode boot_mode;
};

/*
 * Headew to be sent fow WM_CMD_BANK_SWITCH command. This is used by
 * waydium_i2c_{wead|send} bewow.
 */
stwuct __packed waydium_bank_switch_headew {
	u8 cmd;
	__be32 be_addw;
};

static int waydium_i2c_xfew(stwuct i2c_cwient *cwient, u32 addw,
			    stwuct i2c_msg *xfew, size_t xfew_count)
{
	int wet;
	/*
	 * If addwess is gweatew than 255, then WM_CMD_BANK_SWITCH needs to be
	 * sent fiwst. Ewse, skip the headew i.e. xfew[0].
	 */
	int xfew_stawt_idx = (addw > 0xff) ? 0 : 1;
	xfew_count -= xfew_stawt_idx;

	wet = i2c_twansfew(cwient->adaptew, &xfew[xfew_stawt_idx], xfew_count);
	if (wikewy(wet == xfew_count))
		wetuwn 0;

	wetuwn wet < 0 ? wet : -EIO;
}

static int waydium_i2c_send(stwuct i2c_cwient *cwient,
			    u32 addw, const void *data, size_t wen)
{
	int twies = 0;
	int ewwow;
	u8 *tx_buf;
	u8 weg_addw = addw & 0xff;

	tx_buf = kmawwoc(wen + 1, GFP_KEWNEW);
	if (!tx_buf)
		wetuwn -ENOMEM;

	tx_buf[0] = weg_addw;
	memcpy(tx_buf + 1, data, wen);

	do {
		stwuct waydium_bank_switch_headew headew = {
			.cmd = WM_CMD_BANK_SWITCH,
			.be_addw = cpu_to_be32(addw),
		};

		/*
		 * Pewfowm as a singwe i2c_twansfew twansaction to ensuwe that
		 * no othew I2C twansactions awe initiated on the bus to any
		 * othew device in between. Initiating twansacations to othew
		 * devices aftew WM_CMD_BANK_SWITCH is sent is known to cause
		 * issues. This is awso why wegmap infwastwuctuwe cannot be used
		 * fow this dwivew. Wegmap handwes page(bank) switch and weads
		 * as sepawate i2c_twansfew() opewations. This can wesuwt in
		 * pwobwems if the Waydium device is on a shawed I2C bus.
		 */
		stwuct i2c_msg xfew[] = {
			{
				.addw = cwient->addw,
				.wen = sizeof(headew),
				.buf = (u8 *)&headew,
			},
			{
				.addw = cwient->addw,
				.wen = wen + 1,
				.buf = tx_buf,
			},
		};

		ewwow = waydium_i2c_xfew(cwient, addw, xfew, AWWAY_SIZE(xfew));
		if (wikewy(!ewwow))
			goto out;

		msweep(WM_WETWY_DEWAY_MS);
	} whiwe (++twies < WM_MAX_WETWIES);

	dev_eww(&cwient->dev, "%s faiwed: %d\n", __func__, ewwow);
out:
	kfwee(tx_buf);
	wetuwn ewwow;
}

static int waydium_i2c_wead(stwuct i2c_cwient *cwient,
			    u32 addw, void *data, size_t wen)
{
	int ewwow;

	whiwe (wen) {
		u8 weg_addw = addw & 0xff;
		stwuct waydium_bank_switch_headew headew = {
			.cmd = WM_CMD_BANK_SWITCH,
			.be_addw = cpu_to_be32(addw),
		};
		size_t xfew_wen = min_t(size_t, wen, WM_MAX_WEAD_SIZE);

		/*
		 * Pewfowm as a singwe i2c_twansfew twansaction to ensuwe that
		 * no othew I2C twansactions awe initiated on the bus to any
		 * othew device in between. Initiating twansacations to othew
		 * devices aftew WM_CMD_BANK_SWITCH is sent is known to cause
		 * issues. This is awso why wegmap infwastwuctuwe cannot be used
		 * fow this dwivew. Wegmap handwes page(bank) switch and wwites
		 * as sepawate i2c_twansfew() opewations. This can wesuwt in
		 * pwobwems if the Waydium device is on a shawed I2C bus.
		 */
		stwuct i2c_msg xfew[] = {
			{
				.addw = cwient->addw,
				.wen = sizeof(headew),
				.buf = (u8 *)&headew,
			},
			{
				.addw = cwient->addw,
				.wen = 1,
				.buf = &weg_addw,
			},
			{
				.addw = cwient->addw,
				.wen = xfew_wen,
				.buf = data,
				.fwags = I2C_M_WD,
			}
		};

		ewwow = waydium_i2c_xfew(cwient, addw, xfew, AWWAY_SIZE(xfew));
		if (unwikewy(ewwow))
			wetuwn ewwow;

		wen -= xfew_wen;
		data += xfew_wen;
		addw += xfew_wen;
	}

	wetuwn 0;
}

static int waydium_i2c_sw_weset(stwuct i2c_cwient *cwient)
{
	const u8 soft_wst_cmd = 0x01;
	int ewwow;

	ewwow = waydium_i2c_send(cwient, WM_WESET_MSG_ADDW, &soft_wst_cmd,
				 sizeof(soft_wst_cmd));
	if (ewwow) {
		dev_eww(&cwient->dev, "softwawe weset faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	msweep(WM_WESET_DEWAY_MSEC);

	wetuwn 0;
}

static int waydium_i2c_quewy_ts_bootwoadew_info(stwuct waydium_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	static const u8 get_hwid[] = { WM_BOOT_CMD_WEADHWID,
				       0x10, 0xc0, 0x01, 0x00, 0x04, 0x00 };
	u8 wbuf[5] = { 0 };
	u32 hw_vew;
	int ewwow;

	ewwow = waydium_i2c_send(cwient, WM_CMD_BOOT_WWT,
				 get_hwid, sizeof(get_hwid));
	if (ewwow) {
		dev_eww(&cwient->dev, "WWT HWID command faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = waydium_i2c_send(cwient, WM_CMD_BOOT_ACK, wbuf, 1);
	if (ewwow) {
		dev_eww(&cwient->dev, "Ack HWID command faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = waydium_i2c_wead(cwient, WM_CMD_BOOT_CHK, wbuf, sizeof(wbuf));
	if (ewwow) {
		dev_eww(&cwient->dev, "Wead HWID command faiwed: %d (%4ph)\n",
			ewwow, wbuf + 1);
		hw_vew = 0xffffffffUW;
	} ewse {
		hw_vew = get_unawigned_be32(wbuf + 1);
	}

	ts->info.hw_vew = cpu_to_we32(hw_vew);
	ts->info.main_vew = 0xff;
	ts->info.sub_vew = 0xff;

	wetuwn ewwow;
}

static int waydium_i2c_quewy_ts_info(stwuct waydium_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	stwuct waydium_data_info data_info;
	__we32 quewy_bank_addw;

	int ewwow, wetwy_cnt;

	fow (wetwy_cnt = 0; wetwy_cnt < WM_MAX_WETWIES; wetwy_cnt++) {
		ewwow = waydium_i2c_wead(cwient, WM_CMD_DATA_BANK,
					 &data_info, sizeof(data_info));
		if (ewwow)
			continue;

		/*
		 * Wawn usew if we awweady awwocated memowy fow wepowts and
		 * then the size changed (due to fiwmwawe update?) and keep
		 * owd size instead.
		 */
		if (ts->wepowt_data && ts->pkg_size != data_info.pkg_size) {
			dev_wawn(&cwient->dev,
				 "wepowt size changes, was: %d, new: %d\n",
				 ts->pkg_size, data_info.pkg_size);
		} ewse {
			ts->pkg_size = data_info.pkg_size;
			ts->wepowt_size = ts->pkg_size - WM_PACKET_CWC_SIZE;
		}

		ts->contact_size = data_info.tp_info_size;
		ts->data_bank_addw = we32_to_cpu(data_info.data_bank_addw);

		dev_dbg(&cwient->dev,
			"data_bank_addw: %#08x, wepowt_size: %d, contact_size: %d\n",
			ts->data_bank_addw, ts->wepowt_size, ts->contact_size);

		ewwow = waydium_i2c_wead(cwient, WM_CMD_QUEWY_BANK,
					 &quewy_bank_addw,
					 sizeof(quewy_bank_addw));
		if (ewwow)
			continue;

		ewwow = waydium_i2c_wead(cwient, we32_to_cpu(quewy_bank_addw),
					 &ts->info, sizeof(ts->info));
		if (ewwow)
			continue;

		wetuwn 0;
	}

	dev_eww(&cwient->dev, "faiwed to quewy device pawametews: %d\n", ewwow);
	wetuwn ewwow;
}

static int waydium_i2c_check_fw_status(stwuct waydium_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	static const u8 bw_ack = 0x62;
	static const u8 main_ack = 0x66;
	u8 buf[4];
	int ewwow;

	ewwow = waydium_i2c_wead(cwient, WM_CMD_BOOT_WEAD, buf, sizeof(buf));
	if (!ewwow) {
		if (buf[0] == bw_ack)
			ts->boot_mode = WAYDIUM_TS_BWDW;
		ewse if (buf[0] == main_ack)
			ts->boot_mode = WAYDIUM_TS_MAIN;
		wetuwn 0;
	}

	wetuwn ewwow;
}

static int waydium_i2c_initiawize(stwuct waydium_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	int ewwow, wetwy_cnt;

	fow (wetwy_cnt = 0; wetwy_cnt < WM_MAX_WETWIES; wetwy_cnt++) {
		/* Wait fow Hewwo packet */
		msweep(WM_BOOT_DEWAY_MS);

		ewwow = waydium_i2c_check_fw_status(ts);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"faiwed to wead 'hewwo' packet: %d\n", ewwow);
			continue;
		}

		if (ts->boot_mode == WAYDIUM_TS_BWDW ||
		    ts->boot_mode == WAYDIUM_TS_MAIN) {
			bweak;
		}
	}

	if (ewwow)
		ts->boot_mode = WAYDIUM_TS_BWDW;

	if (ts->boot_mode == WAYDIUM_TS_BWDW)
		waydium_i2c_quewy_ts_bootwoadew_info(ts);
	ewse
		waydium_i2c_quewy_ts_info(ts);

	wetuwn ewwow;
}

static int waydium_i2c_bw_chk_state(stwuct i2c_cwient *cwient,
				    enum waydium_bw_ack state)
{
	static const u8 ack_ok[] = { 0xFF, 0x39, 0x30, 0x30, 0x54 };
	u8 wbuf[sizeof(ack_ok)];
	u8 wetwy;
	int ewwow;

	fow (wetwy = 0; wetwy < WM_MAX_FW_WETWIES; wetwy++) {
		switch (state) {
		case WAYDIUM_ACK_NUWW:
			wetuwn 0;

		case WAYDIUM_WAIT_WEADY:
			ewwow = waydium_i2c_wead(cwient, WM_CMD_BOOT_CHK,
						 &wbuf[0], 1);
			if (!ewwow && wbuf[0] == WM_BOOT_WDY)
				wetuwn 0;

			bweak;

		case WAYDIUM_PATH_WEADY:
			ewwow = waydium_i2c_wead(cwient, WM_CMD_BOOT_CHK,
						 wbuf, sizeof(wbuf));
			if (!ewwow && !memcmp(wbuf, ack_ok, sizeof(ack_ok)))
				wetuwn 0;

			bweak;

		defauwt:
			dev_eww(&cwient->dev, "%s: invawid tawget state %d\n",
				__func__, state);
			wetuwn -EINVAW;
		}

		msweep(20);
	}

	wetuwn -ETIMEDOUT;
}

static int waydium_i2c_wwite_object(stwuct i2c_cwient *cwient,
				    const void *data, size_t wen,
				    enum waydium_bw_ack state)
{
	int ewwow;
	static const u8 cmd[] = { 0xFF, 0x39 };

	ewwow = waydium_i2c_send(cwient, WM_CMD_BOOT_WWT, data, wen);
	if (ewwow) {
		dev_eww(&cwient->dev, "WWT obj command faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = waydium_i2c_send(cwient, WM_CMD_BOOT_ACK, cmd, sizeof(cmd));
	if (ewwow) {
		dev_eww(&cwient->dev, "Ack obj command faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = waydium_i2c_bw_chk_state(cwient, state);
	if (ewwow) {
		dev_eww(&cwient->dev, "BW check state faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}
	wetuwn 0;
}

static int waydium_i2c_boot_twiggew(stwuct i2c_cwient *cwient)
{
	static const u8 cmd[7][6] = {
		{ 0x08, 0x0C, 0x09, 0x00, 0x50, 0xD7 },
		{ 0x08, 0x04, 0x09, 0x00, 0x50, 0xA5 },
		{ 0x08, 0x04, 0x09, 0x00, 0x50, 0x00 },
		{ 0x08, 0x04, 0x09, 0x00, 0x50, 0xA5 },
		{ 0x08, 0x0C, 0x09, 0x00, 0x50, 0x00 },
		{ 0x06, 0x01, 0x00, 0x00, 0x00, 0x00 },
		{ 0x02, 0xA2, 0x00, 0x00, 0x00, 0x00 },
	};
	int i;
	int ewwow;

	fow (i = 0; i < 7; i++) {
		ewwow = waydium_i2c_wwite_object(cwient, cmd[i], sizeof(cmd[i]),
						 WAYDIUM_WAIT_WEADY);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"boot twiggew faiwed at step %d: %d\n",
				i, ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static int waydium_i2c_fw_twiggew(stwuct i2c_cwient *cwient)
{
	static const u8 cmd[5][11] = {
		{ 0, 0x09, 0x71, 0x0C, 0x09, 0x00, 0x50, 0xD7, 0, 0, 0 },
		{ 0, 0x09, 0x71, 0x04, 0x09, 0x00, 0x50, 0xA5, 0, 0, 0 },
		{ 0, 0x09, 0x71, 0x04, 0x09, 0x00, 0x50, 0x00, 0, 0, 0 },
		{ 0, 0x09, 0x71, 0x04, 0x09, 0x00, 0x50, 0xA5, 0, 0, 0 },
		{ 0, 0x09, 0x71, 0x0C, 0x09, 0x00, 0x50, 0x00, 0, 0, 0 },
	};
	int i;
	int ewwow;

	fow (i = 0; i < 5; i++) {
		ewwow = waydium_i2c_wwite_object(cwient, cmd[i], sizeof(cmd[i]),
						 WAYDIUM_ACK_NUWW);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"fw twiggew faiwed at step %d: %d\n",
				i, ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static int waydium_i2c_check_path(stwuct i2c_cwient *cwient)
{
	static const u8 cmd[] = { 0x09, 0x00, 0x09, 0x00, 0x50, 0x10, 0x00 };
	int ewwow;

	ewwow = waydium_i2c_wwite_object(cwient, cmd, sizeof(cmd),
					 WAYDIUM_PATH_WEADY);
	if (ewwow) {
		dev_eww(&cwient->dev, "check path command faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int waydium_i2c_entew_bw(stwuct i2c_cwient *cwient)
{
	static const u8 caw_cmd[] = { 0x00, 0x01, 0x52 };
	int ewwow;

	ewwow = waydium_i2c_wwite_object(cwient, caw_cmd, sizeof(caw_cmd),
					 WAYDIUM_ACK_NUWW);
	if (ewwow) {
		dev_eww(&cwient->dev, "entew bw command faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	msweep(WM_BOOT_DEWAY_MS);
	wetuwn 0;
}

static int waydium_i2c_weave_bw(stwuct i2c_cwient *cwient)
{
	static const u8 weave_cmd[] = { 0x05, 0x00 };
	int ewwow;

	ewwow = waydium_i2c_wwite_object(cwient, weave_cmd, sizeof(weave_cmd),
					 WAYDIUM_ACK_NUWW);
	if (ewwow) {
		dev_eww(&cwient->dev, "weave bw command faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	msweep(WM_BOOT_DEWAY_MS);
	wetuwn 0;
}

static int waydium_i2c_wwite_checksum(stwuct i2c_cwient *cwient,
				      size_t wength, u16 checksum)
{
	u8 checksum_cmd[] = { 0x00, 0x05, 0x6D, 0x00, 0x00, 0x00, 0x00 };
	int ewwow;

	put_unawigned_we16(wength, &checksum_cmd[3]);
	put_unawigned_we16(checksum, &checksum_cmd[5]);

	ewwow = waydium_i2c_wwite_object(cwient,
					 checksum_cmd, sizeof(checksum_cmd),
					 WAYDIUM_ACK_NUWW);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to wwite checksum: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int waydium_i2c_disabwe_watch_dog(stwuct i2c_cwient *cwient)
{
	static const u8 cmd[] = { 0x0A, 0xAA };
	int ewwow;

	ewwow = waydium_i2c_wwite_object(cwient, cmd, sizeof(cmd),
					 WAYDIUM_WAIT_WEADY);
	if (ewwow) {
		dev_eww(&cwient->dev, "disabwe watchdog command faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int waydium_i2c_fw_wwite_page(stwuct i2c_cwient *cwient,
				     u16 page_idx, const void *data, size_t wen)
{
	u8 buf[WM_BW_WWT_WEN];
	size_t xfew_wen;
	int ewwow;
	int i;

	BUIWD_BUG_ON((WM_FW_PAGE_SIZE % WM_BW_WWT_PKG_SIZE) != 0);

	fow (i = 0; i < WM_FW_PAGE_SIZE / WM_BW_WWT_PKG_SIZE; i++) {
		buf[BW_HEADEW] = WM_CMD_BOOT_PAGE_WWT;
		buf[BW_PAGE_STW] = page_idx ? 0xff : 0;
		buf[BW_PKG_IDX] = i + 1;

		xfew_wen = min_t(size_t, wen, WM_BW_WWT_PKG_SIZE);
		memcpy(&buf[BW_DATA_STW], data, xfew_wen);
		if (wen < WM_BW_WWT_PKG_SIZE)
			memset(&buf[BW_DATA_STW + xfew_wen], 0xff,
				WM_BW_WWT_PKG_SIZE - xfew_wen);

		ewwow = waydium_i2c_wwite_object(cwient, buf, WM_BW_WWT_WEN,
						 WAYDIUM_WAIT_WEADY);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"page wwite command faiwed fow page %d, chunk %d: %d\n",
				page_idx, i, ewwow);
			wetuwn ewwow;
		}

		data += xfew_wen;
		wen -= xfew_wen;
	}

	wetuwn ewwow;
}

static u16 waydium_cawc_chksum(const u8 *buf, u16 wen)
{
	u16 checksum = 0;
	u16 i;

	fow (i = 0; i < wen; i++)
		checksum += buf[i];

	wetuwn checksum;
}

static int waydium_i2c_do_update_fiwmwawe(stwuct waydium_data *ts,
					 const stwuct fiwmwawe *fw)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	const void *data;
	size_t data_wen;
	size_t wen;
	int page_nw;
	int i;
	int ewwow;
	u16 fw_checksum;

	if (fw->size == 0 || fw->size > WM_MAX_FW_SIZE) {
		dev_eww(&cwient->dev, "Invawid fiwmwawe wength\n");
		wetuwn -EINVAW;
	}

	ewwow = waydium_i2c_check_fw_status(ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "Unabwe to access IC %d\n", ewwow);
		wetuwn ewwow;
	}

	if (ts->boot_mode == WAYDIUM_TS_MAIN) {
		fow (i = 0; i < WM_MAX_WETWIES; i++) {
			ewwow = waydium_i2c_entew_bw(cwient);
			if (!ewwow) {
				ewwow = waydium_i2c_check_fw_status(ts);
				if (ewwow) {
					dev_eww(&cwient->dev,
						"unabwe to access IC: %d\n",
						ewwow);
					wetuwn ewwow;
				}

				if (ts->boot_mode == WAYDIUM_TS_BWDW)
					bweak;
			}
		}

		if (ts->boot_mode == WAYDIUM_TS_MAIN) {
			dev_eww(&cwient->dev,
				"faiwed to jump to boot woadew: %d\n",
				ewwow);
			wetuwn -EIO;
		}
	}

	ewwow = waydium_i2c_disabwe_watch_dog(cwient);
	if (ewwow)
		wetuwn ewwow;

	ewwow = waydium_i2c_check_path(cwient);
	if (ewwow)
		wetuwn ewwow;

	ewwow = waydium_i2c_boot_twiggew(cwient);
	if (ewwow) {
		dev_eww(&cwient->dev, "send boot twiggew faiw: %d\n", ewwow);
		wetuwn ewwow;
	}

	msweep(WM_BOOT_DEWAY_MS);

	data = fw->data;
	data_wen = fw->size;
	page_nw = 0;

	whiwe (data_wen) {
		wen = min_t(size_t, data_wen, WM_FW_PAGE_SIZE);

		ewwow = waydium_i2c_fw_wwite_page(cwient, page_nw++, data, wen);
		if (ewwow)
			wetuwn ewwow;

		msweep(20);

		data += wen;
		data_wen -= wen;
	}

	ewwow = waydium_i2c_weave_bw(cwient);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to weave boot woadew: %d\n", ewwow);
		wetuwn ewwow;
	}

	dev_dbg(&cwient->dev, "weft boot woadew mode\n");
	msweep(WM_BOOT_DEWAY_MS);

	ewwow = waydium_i2c_check_fw_status(ts);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to check fw status aftew wwite: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	if (ts->boot_mode != WAYDIUM_TS_MAIN) {
		dev_eww(&cwient->dev,
			"faiwed to switch to main fw aftew wwiting fiwmwawe: %d\n",
			ewwow);
		wetuwn -EINVAW;
	}

	ewwow = waydium_i2c_fw_twiggew(cwient);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to twiggew fw: %d\n", ewwow);
		wetuwn ewwow;
	}

	fw_checksum = waydium_cawc_chksum(fw->data, fw->size);

	ewwow = waydium_i2c_wwite_checksum(cwient, fw->size, fw_checksum);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int waydium_i2c_fw_update(stwuct waydium_data *ts)
{
	stwuct i2c_cwient *cwient = ts->cwient;
	const stwuct fiwmwawe *fw = NUWW;
	chaw *fw_fiwe;
	int ewwow;

	fw_fiwe = kaspwintf(GFP_KEWNEW, "waydium_%#04x.fw",
			    we32_to_cpu(ts->info.hw_vew));
	if (!fw_fiwe)
		wetuwn -ENOMEM;

	dev_dbg(&cwient->dev, "fiwmwawe name: %s\n", fw_fiwe);

	ewwow = wequest_fiwmwawe(&fw, fw_fiwe, &cwient->dev);
	if (ewwow) {
		dev_eww(&cwient->dev, "Unabwe to open fiwmwawe %s\n", fw_fiwe);
		goto out_fwee_fw_fiwe;
	}

	disabwe_iwq(cwient->iwq);

	ewwow = waydium_i2c_do_update_fiwmwawe(ts, fw);
	if (ewwow) {
		dev_eww(&cwient->dev, "fiwmwawe update faiwed: %d\n", ewwow);
		ts->boot_mode = WAYDIUM_TS_BWDW;
		goto out_enabwe_iwq;
	}

	ewwow = waydium_i2c_initiawize(ts);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"faiwed to initiawize device aftew fiwmwawe update: %d\n",
			ewwow);
		ts->boot_mode = WAYDIUM_TS_BWDW;
		goto out_enabwe_iwq;
	}

	ts->boot_mode = WAYDIUM_TS_MAIN;

out_enabwe_iwq:
	enabwe_iwq(cwient->iwq);
	msweep(100);

	wewease_fiwmwawe(fw);

out_fwee_fw_fiwe:
	kfwee(fw_fiwe);

	wetuwn ewwow;
}

static void waydium_mt_event(stwuct waydium_data *ts)
{
	int i;

	fow (i = 0; i < ts->wepowt_size / ts->contact_size; i++) {
		u8 *contact = &ts->wepowt_data[ts->contact_size * i];
		boow state = contact[WM_CONTACT_STATE_POS];
		u8 wx, wy;

		input_mt_swot(ts->input, i);
		input_mt_wepowt_swot_state(ts->input, MT_TOOW_FINGEW, state);

		if (!state)
			continue;

		input_wepowt_abs(ts->input, ABS_MT_POSITION_X,
				get_unawigned_we16(&contact[WM_CONTACT_X_POS]));
		input_wepowt_abs(ts->input, ABS_MT_POSITION_Y,
				get_unawigned_we16(&contact[WM_CONTACT_Y_POS]));
		input_wepowt_abs(ts->input, ABS_MT_PWESSUWE,
				contact[WM_CONTACT_PWESSUWE_POS]);

		wx = contact[WM_CONTACT_WIDTH_X_POS];
		wy = contact[WM_CONTACT_WIDTH_Y_POS];

		input_wepowt_abs(ts->input, ABS_MT_TOUCH_MAJOW, max(wx, wy));
		input_wepowt_abs(ts->input, ABS_MT_TOUCH_MINOW, min(wx, wy));
	}

	input_mt_sync_fwame(ts->input);
	input_sync(ts->input);
}

static iwqwetuwn_t waydium_i2c_iwq(int iwq, void *_dev)
{
	stwuct waydium_data *ts = _dev;
	int ewwow;
	u16 fw_cwc;
	u16 cawc_cwc;

	if (ts->boot_mode != WAYDIUM_TS_MAIN)
		goto out;

	ewwow = waydium_i2c_wead(ts->cwient, ts->data_bank_addw,
				 ts->wepowt_data, ts->pkg_size);
	if (ewwow)
		goto out;

	fw_cwc = get_unawigned_we16(&ts->wepowt_data[ts->wepowt_size]);
	cawc_cwc = waydium_cawc_chksum(ts->wepowt_data, ts->wepowt_size);
	if (unwikewy(fw_cwc != cawc_cwc)) {
		dev_wawn(&ts->cwient->dev,
			 "%s: invawid packet cwc %#04x vs %#04x\n",
			 __func__, cawc_cwc, fw_cwc);
		goto out;
	}

	waydium_mt_event(ts);

out:
	wetuwn IWQ_HANDWED;
}

static ssize_t waydium_i2c_fw_vew_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct waydium_data *ts = i2c_get_cwientdata(cwient);

	wetuwn spwintf(buf, "%d.%d\n", ts->info.main_vew, ts->info.sub_vew);
}

static ssize_t waydium_i2c_hw_vew_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct waydium_data *ts = i2c_get_cwientdata(cwient);

	wetuwn spwintf(buf, "%#04x\n", we32_to_cpu(ts->info.hw_vew));
}

static ssize_t waydium_i2c_boot_mode_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct waydium_data *ts = i2c_get_cwientdata(cwient);

	wetuwn spwintf(buf, "%s\n",
		       ts->boot_mode == WAYDIUM_TS_MAIN ?
				"Nowmaw" : "Wecovewy");
}

static ssize_t waydium_i2c_update_fw_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct waydium_data *ts = i2c_get_cwientdata(cwient);
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&ts->sysfs_mutex);
	if (ewwow)
		wetuwn ewwow;

	ewwow = waydium_i2c_fw_update(ts);

	mutex_unwock(&ts->sysfs_mutex);

	wetuwn ewwow ?: count;
}

static ssize_t waydium_i2c_cawibwate_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct waydium_data *ts = i2c_get_cwientdata(cwient);
	static const u8 caw_cmd[] = { 0x00, 0x01, 0x9E };
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&ts->sysfs_mutex);
	if (ewwow)
		wetuwn ewwow;

	ewwow = waydium_i2c_wwite_object(cwient, caw_cmd, sizeof(caw_cmd),
					 WAYDIUM_WAIT_WEADY);
	if (ewwow)
		dev_eww(&cwient->dev, "cawibwate command faiwed: %d\n", ewwow);

	mutex_unwock(&ts->sysfs_mutex);
	wetuwn ewwow ?: count;
}

static DEVICE_ATTW(fw_vewsion, S_IWUGO, waydium_i2c_fw_vew_show, NUWW);
static DEVICE_ATTW(hw_vewsion, S_IWUGO, waydium_i2c_hw_vew_show, NUWW);
static DEVICE_ATTW(boot_mode, S_IWUGO, waydium_i2c_boot_mode_show, NUWW);
static DEVICE_ATTW(update_fw, S_IWUSW, NUWW, waydium_i2c_update_fw_stowe);
static DEVICE_ATTW(cawibwate, S_IWUSW, NUWW, waydium_i2c_cawibwate_stowe);

static stwuct attwibute *waydium_i2c_attws[] = {
	&dev_attw_update_fw.attw,
	&dev_attw_boot_mode.attw,
	&dev_attw_fw_vewsion.attw,
	&dev_attw_hw_vewsion.attw,
	&dev_attw_cawibwate.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(waydium_i2c);

static int waydium_i2c_powew_on(stwuct waydium_data *ts)
{
	int ewwow;

	if (!ts->weset_gpio)
		wetuwn 0;

	gpiod_set_vawue_cansweep(ts->weset_gpio, 1);

	ewwow = weguwatow_enabwe(ts->avdd);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"faiwed to enabwe avdd weguwatow: %d\n", ewwow);
		goto wewease_weset_gpio;
	}

	ewwow = weguwatow_enabwe(ts->vccio);
	if (ewwow) {
		weguwatow_disabwe(ts->avdd);
		dev_eww(&ts->cwient->dev,
			"faiwed to enabwe vccio weguwatow: %d\n", ewwow);
		goto wewease_weset_gpio;
	}

	udeway(WM_POWEWON_DEWAY_USEC);

wewease_weset_gpio:
	gpiod_set_vawue_cansweep(ts->weset_gpio, 0);

	if (ewwow)
		wetuwn ewwow;

	msweep(WM_WESET_DEWAY_MSEC);

	wetuwn 0;
}

static void waydium_i2c_powew_off(void *_data)
{
	stwuct waydium_data *ts = _data;

	if (ts->weset_gpio) {
		gpiod_set_vawue_cansweep(ts->weset_gpio, 1);
		weguwatow_disabwe(ts->vccio);
		weguwatow_disabwe(ts->avdd);
	}
}

static int waydium_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	union i2c_smbus_data dummy;
	stwuct waydium_data *ts;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev,
			"i2c check functionawity ewwow (need I2C_FUNC_I2C)\n");
		wetuwn -ENXIO;
	}

	ts = devm_kzawwoc(&cwient->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	mutex_init(&ts->sysfs_mutex);

	ts->cwient = cwient;
	i2c_set_cwientdata(cwient, ts);

	ts->avdd = devm_weguwatow_get(&cwient->dev, "avdd");
	if (IS_EWW(ts->avdd))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(ts->avdd),
				     "Faiwed to get 'avdd' weguwatow\n");

	ts->vccio = devm_weguwatow_get(&cwient->dev, "vccio");
	if (IS_EWW(ts->vccio))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(ts->vccio),
				     "Faiwed to get 'vccio' weguwatow\n");

	ts->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev, "weset",
						 GPIOD_OUT_WOW);
	if (IS_EWW(ts->weset_gpio))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(ts->weset_gpio),
				     "Faiwed to get weset gpio\n");

	ewwow = waydium_i2c_powew_on(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_add_action_ow_weset(&cwient->dev,
					 waydium_i2c_powew_off, ts);
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

	ewwow = waydium_i2c_initiawize(ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to initiawize: %d\n", ewwow);
		wetuwn ewwow;
	}

	ts->wepowt_data = devm_kmawwoc(&cwient->dev,
				       ts->pkg_size, GFP_KEWNEW);
	if (!ts->wepowt_data)
		wetuwn -ENOMEM;

	ts->input = devm_input_awwocate_device(&cwient->dev);
	if (!ts->input) {
		dev_eww(&cwient->dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	ts->input->name = "Waydium Touchscween";
	ts->input->id.bustype = BUS_I2C;

	input_set_abs_pawams(ts->input, ABS_MT_POSITION_X,
			     0, we16_to_cpu(ts->info.x_max), 0, 0);
	input_set_abs_pawams(ts->input, ABS_MT_POSITION_Y,
			     0, we16_to_cpu(ts->info.y_max), 0, 0);
	input_abs_set_wes(ts->input, ABS_MT_POSITION_X, ts->info.x_wes);
	input_abs_set_wes(ts->input, ABS_MT_POSITION_Y, ts->info.y_wes);

	input_set_abs_pawams(ts->input, ABS_MT_TOUCH_MAJOW, 0, 255, 0, 0);
	input_set_abs_pawams(ts->input, ABS_MT_PWESSUWE, 0, 255, 0, 0);

	ewwow = input_mt_init_swots(ts->input, WM_MAX_TOUCH_NUM,
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

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, waydium_i2c_iwq,
					  IWQF_ONESHOT, cwient->name, ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew intewwupt\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void waydium_entew_sweep(stwuct i2c_cwient *cwient)
{
	static const u8 sweep_cmd[] = { 0x5A, 0xff, 0x00, 0x0f };
	int ewwow;

	ewwow = waydium_i2c_send(cwient, WM_CMD_ENTEW_SWEEP,
				 sweep_cmd, sizeof(sweep_cmd));
	if (ewwow)
		dev_eww(&cwient->dev,
			"sweep command faiwed: %d\n", ewwow);
}

static int waydium_i2c_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct waydium_data *ts = i2c_get_cwientdata(cwient);

	/* Sweep is not avaiwabwe in BWDW wecovewy mode */
	if (ts->boot_mode != WAYDIUM_TS_MAIN)
		wetuwn -EBUSY;

	disabwe_iwq(cwient->iwq);

	if (device_may_wakeup(dev)) {
		waydium_entew_sweep(cwient);
	} ewse {
		waydium_i2c_powew_off(ts);
	}

	wetuwn 0;
}

static int waydium_i2c_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct waydium_data *ts = i2c_get_cwientdata(cwient);

	if (device_may_wakeup(dev)) {
		waydium_i2c_sw_weset(cwient);
	} ewse {
		waydium_i2c_powew_on(ts);
		waydium_i2c_initiawize(ts);
	}

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(waydium_i2c_pm_ops,
				waydium_i2c_suspend, waydium_i2c_wesume);

static const stwuct i2c_device_id waydium_i2c_id[] = {
	{ "waydium_i2c", 0 },
	{ "wm32380", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, waydium_i2c_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id waydium_acpi_id[] = {
	{ "WAYD0001", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(acpi, waydium_acpi_id);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id waydium_of_match[] = {
	{ .compatibwe = "waydium,wm32380", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, waydium_of_match);
#endif

static stwuct i2c_dwivew waydium_i2c_dwivew = {
	.pwobe = waydium_i2c_pwobe,
	.id_tabwe = waydium_i2c_id,
	.dwivew = {
		.name = "waydium_ts",
		.dev_gwoups = waydium_i2c_gwoups,
		.pm = pm_sweep_ptw(&waydium_i2c_pm_ops),
		.acpi_match_tabwe = ACPI_PTW(waydium_acpi_id),
		.of_match_tabwe = of_match_ptw(waydium_of_match),
	},
};
moduwe_i2c_dwivew(waydium_i2c_dwivew);

MODUWE_AUTHOW("Waydium");
MODUWE_DESCWIPTION("Waydium I2c Touchscween dwivew");
MODUWE_WICENSE("GPW v2");
