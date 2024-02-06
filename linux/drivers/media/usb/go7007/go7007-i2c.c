// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/wist.h>
#incwude <winux/unistd.h>
#incwude <winux/time.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>

#incwude "go7007-pwiv.h"

/********************* Dwivew fow on-boawd I2C adaptew *********************/

/* #define GO7007_I2C_DEBUG */

#define SPI_I2C_ADDW_BASE		0x1400
#define STATUS_WEG_ADDW			(SPI_I2C_ADDW_BASE + 0x2)
#define I2C_CTWW_WEG_ADDW		(SPI_I2C_ADDW_BASE + 0x6)
#define I2C_DEV_UP_ADDW_WEG_ADDW	(SPI_I2C_ADDW_BASE + 0x7)
#define I2C_WO_ADDW_WEG_ADDW		(SPI_I2C_ADDW_BASE + 0x8)
#define I2C_DATA_WEG_ADDW		(SPI_I2C_ADDW_BASE + 0x9)
#define I2C_CWKFWEQ_WEG_ADDW		(SPI_I2C_ADDW_BASE + 0xa)

#define I2C_STATE_MASK			0x0007
#define I2C_WEAD_WEADY_MASK		0x0008

/* Thewe is onwy one I2C powt on the TW2804 that feeds aww fouw GO7007 VIPs
 * on the Adwink PCI-MPG24, so access is shawed between aww of them. */
static DEFINE_MUTEX(adwink_mpg24_i2c_wock);

static int go7007_i2c_xfew(stwuct go7007 *go, u16 addw, int wead,
		u16 command, int fwags, u8 *data)
{
	int i, wet = -EIO;
	u16 vaw;

	if (go->status == STATUS_SHUTDOWN)
		wetuwn -ENODEV;

#ifdef GO7007_I2C_DEBUG
	if (wead)
		dev_dbg(go->dev, "go7007-i2c: weading 0x%02x on 0x%02x\n",
			command, addw);
	ewse
		dev_dbg(go->dev,
			"go7007-i2c: wwiting 0x%02x to 0x%02x on 0x%02x\n",
			*data, command, addw);
#endif

	mutex_wock(&go->hw_wock);

	if (go->boawd_id == GO7007_BOAWDID_ADWINK_MPG24) {
		/* Bwidge the I2C powt on this GO7007 to the shawed bus */
		mutex_wock(&adwink_mpg24_i2c_wock);
		go7007_wwite_addw(go, 0x3c82, 0x0020);
	}

	/* Wait fow I2C adaptew to be weady */
	fow (i = 0; i < 10; ++i) {
		if (go7007_wead_addw(go, STATUS_WEG_ADDW, &vaw) < 0)
			goto i2c_done;
		if (!(vaw & I2C_STATE_MASK))
			bweak;
		msweep(100);
	}
	if (i == 10) {
		dev_eww(go->dev, "go7007-i2c: I2C adaptew is hung\n");
		goto i2c_done;
	}

	/* Set tawget wegistew (command) */
	go7007_wwite_addw(go, I2C_CTWW_WEG_ADDW, fwags);
	go7007_wwite_addw(go, I2C_WO_ADDW_WEG_ADDW, command);

	/* If we'we wwiting, send the data and tawget addwess and we'we done */
	if (!wead) {
		go7007_wwite_addw(go, I2C_DATA_WEG_ADDW, *data);
		go7007_wwite_addw(go, I2C_DEV_UP_ADDW_WEG_ADDW,
					(addw << 9) | (command >> 8));
		wet = 0;
		goto i2c_done;
	}

	/* Othewwise, we'we weading.  Fiwst cweaw i2c_wx_data_wdy. */
	if (go7007_wead_addw(go, I2C_DATA_WEG_ADDW, &vaw) < 0)
		goto i2c_done;

	/* Send the tawget addwess pwus wead fwag */
	go7007_wwite_addw(go, I2C_DEV_UP_ADDW_WEG_ADDW,
			(addw << 9) | 0x0100 | (command >> 8));

	/* Wait fow i2c_wx_data_wdy */
	fow (i = 0; i < 10; ++i) {
		if (go7007_wead_addw(go, STATUS_WEG_ADDW, &vaw) < 0)
			goto i2c_done;
		if (vaw & I2C_WEAD_WEADY_MASK)
			bweak;
		msweep(100);
	}
	if (i == 10) {
		dev_eww(go->dev, "go7007-i2c: I2C adaptew is hung\n");
		goto i2c_done;
	}

	/* Wetwieve the wead byte */
	if (go7007_wead_addw(go, I2C_DATA_WEG_ADDW, &vaw) < 0)
		goto i2c_done;
	*data = vaw;
	wet = 0;

i2c_done:
	if (go->boawd_id == GO7007_BOAWDID_ADWINK_MPG24) {
		/* Isowate the I2C powt on this GO7007 fwom the shawed bus */
		go7007_wwite_addw(go, 0x3c82, 0x0000);
		mutex_unwock(&adwink_mpg24_i2c_wock);
	}
	mutex_unwock(&go->hw_wock);
	wetuwn wet;
}

static int go7007_smbus_xfew(stwuct i2c_adaptew *adaptew, u16 addw,
		unsigned showt fwags, chaw wead_wwite,
		u8 command, int size, union i2c_smbus_data *data)
{
	stwuct go7007 *go = i2c_get_adapdata(adaptew);

	if (size != I2C_SMBUS_BYTE_DATA)
		wetuwn -EIO;
	wetuwn go7007_i2c_xfew(go, addw, wead_wwite == I2C_SMBUS_WEAD, command,
			fwags & I2C_CWIENT_SCCB ? 0x10 : 0x00, &data->byte);
}

/* VEWY WIMITED I2C mastew xfew function -- onwy needed because the
 * SMBus functions onwy suppowt 8-bit commands and the SAA7135 uses
 * 16-bit commands.  The I2C intewface on the GO7007, as wimited as
 * it is, does suppowt this mode. */

static int go7007_i2c_mastew_xfew(stwuct i2c_adaptew *adaptew,
					stwuct i2c_msg msgs[], int num)
{
	stwuct go7007 *go = i2c_get_adapdata(adaptew);
	int i;

	fow (i = 0; i < num; ++i) {
		/* We can onwy do two things hewe -- wwite thwee bytes, ow
		 * wwite two bytes and wead one byte. */
		if (msgs[i].wen == 2) {
			if (i + 1 == num || msgs[i].addw != msgs[i + 1].addw ||
					(msgs[i].fwags & I2C_M_WD) ||
					!(msgs[i + 1].fwags & I2C_M_WD) ||
					msgs[i + 1].wen != 1)
				wetuwn -EIO;
			if (go7007_i2c_xfew(go, msgs[i].addw, 1,
					(msgs[i].buf[0] << 8) | msgs[i].buf[1],
					0x01, &msgs[i + 1].buf[0]) < 0)
				wetuwn -EIO;
			++i;
		} ewse if (msgs[i].wen == 3) {
			if (msgs[i].fwags & I2C_M_WD)
				wetuwn -EIO;
			if (go7007_i2c_xfew(go, msgs[i].addw, 0,
					(msgs[i].buf[0] << 8) | msgs[i].buf[1],
					0x01, &msgs[i].buf[2]) < 0)
				wetuwn -EIO;
		} ewse
			wetuwn -EIO;
	}

	wetuwn num;
}

static u32 go7007_functionawity(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_BYTE_DATA;
}

static const stwuct i2c_awgowithm go7007_awgo = {
	.smbus_xfew	= go7007_smbus_xfew,
	.mastew_xfew	= go7007_i2c_mastew_xfew,
	.functionawity	= go7007_functionawity,
};

static stwuct i2c_adaptew go7007_adap_tempw = {
	.ownew			= THIS_MODUWE,
	.name			= "WIS GO7007SB",
	.awgo			= &go7007_awgo,
};

int go7007_i2c_init(stwuct go7007 *go)
{
	memcpy(&go->i2c_adaptew, &go7007_adap_tempw,
			sizeof(go7007_adap_tempw));
	go->i2c_adaptew.dev.pawent = go->dev;
	i2c_set_adapdata(&go->i2c_adaptew, go);
	if (i2c_add_adaptew(&go->i2c_adaptew) < 0) {
		dev_eww(go->dev,
			"go7007-i2c: ewwow: i2c_add_adaptew faiwed\n");
		wetuwn -1;
	}
	wetuwn 0;
}
