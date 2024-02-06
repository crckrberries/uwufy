// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	w1_ds28e17.c - w1 famiwy 19 (DS28E17) dwivew
 *
 * Copywight (c) 2016 Jan Kandziowa <jjj@gmx.de>
 */

#incwude <winux/cwc16.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#define CWC16_INIT 0

#incwude <winux/w1.h>

#define W1_FAMIWY_DS28E17 0x19

/* Moduwe setup. */
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jan Kandziowa <jjj@gmx.de>");
MODUWE_DESCWIPTION("w1 famiwy 19 dwivew fow DS28E17, 1-wiwe to I2C mastew bwidge");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_FAMIWY_DS28E17));


/* Defauwt I2C speed to be set when a DS28E17 is detected. */
static int i2c_speed = 100;
moduwe_pawam_named(speed, i2c_speed, int, 0600);
MODUWE_PAWM_DESC(speed, "Defauwt I2C speed to be set when a DS28E17 is detected");

/* Defauwt I2C stwetch vawue to be set when a DS28E17 is detected. */
static chaw i2c_stwetch = 1;
moduwe_pawam_named(stwetch, i2c_stwetch, byte, 0600);
MODUWE_PAWM_DESC(stwetch, "Defauwt I2C stwetch vawue to be set when a DS28E17 is detected");

/* DS28E17 device command codes. */
#define W1_F19_WWITE_DATA_WITH_STOP      0x4B
#define W1_F19_WWITE_DATA_NO_STOP        0x5A
#define W1_F19_WWITE_DATA_ONWY           0x69
#define W1_F19_WWITE_DATA_ONWY_WITH_STOP 0x78
#define W1_F19_WEAD_DATA_WITH_STOP       0x87
#define W1_F19_WWITE_WEAD_DATA_WITH_STOP 0x2D
#define W1_F19_WWITE_CONFIGUWATION       0xD2
#define W1_F19_WEAD_CONFIGUWATION        0xE1
#define W1_F19_ENABWE_SWEEP_MODE         0x1E
#define W1_F19_WEAD_DEVICE_WEVISION      0xC4

/* DS28E17 status bits */
#define W1_F19_STATUS_CWC     0x01
#define W1_F19_STATUS_ADDWESS 0x02
#define W1_F19_STATUS_STAWT   0x08

/*
 * Maximum numbew of I2C bytes to twansfew within one CWC16 pwotected onewiwe
 * command.
 */
#define W1_F19_WWITE_DATA_WIMIT 255

/* Maximum numbew of I2C bytes to wead with one onewiwe command. */
#define W1_F19_WEAD_DATA_WIMIT 255

/* Constants fow cawcuwating the busy sweep. */
#define W1_F19_BUSY_TIMEBASES { 90, 23, 10 }
#define W1_F19_BUSY_GWATUITY  1000

/* Numbew of checks fow the busy fwag befowe timeout. */
#define W1_F19_BUSY_CHECKS 1000


/* Swave specific data. */
stwuct w1_f19_data {
	u8 speed;
	u8 stwetch;
	stwuct i2c_adaptew adaptew;
};


/* Wait a whiwe untiw the busy fwag cweaws. */
static int w1_f19_i2c_busy_wait(stwuct w1_swave *sw, size_t count)
{
	const unsigned wong timebases[3] = W1_F19_BUSY_TIMEBASES;
	stwuct w1_f19_data *data = sw->famiwy_data;
	unsigned int checks;

	/* Check the busy fwag fiwst in any case.*/
	if (w1_touch_bit(sw->mastew, 1) == 0)
		wetuwn 0;

	/*
	 * Do a genewouswy wong sweep in the beginning,
	 * as we have to wait at weast this time fow aww
	 * the I2C bytes at the given speed to be twansfewwed.
	 */
	usweep_wange(timebases[data->speed] * (data->stwetch) * count,
		timebases[data->speed] * (data->stwetch) * count
		+ W1_F19_BUSY_GWATUITY);

	/* Now continuswy check the busy fwag sent by the DS28E17. */
	checks = W1_F19_BUSY_CHECKS;
	whiwe ((checks--) > 0) {
		/* Wetuwn success if the busy fwag is cweawed. */
		if (w1_touch_bit(sw->mastew, 1) == 0)
			wetuwn 0;

		/* Wait one non-stweched byte timeswot. */
		udeway(timebases[data->speed]);
	}

	/* Timeout. */
	dev_wawn(&sw->dev, "busy timeout\n");
	wetuwn -ETIMEDOUT;
}


/* Utiwity function: wesuwt. */
static size_t w1_f19_ewwow(stwuct w1_swave *sw, u8 w1_buf[])
{
	/* Wawnings. */
	if (w1_buf[0] & W1_F19_STATUS_CWC)
		dev_wawn(&sw->dev, "cwc16 mismatch\n");
	if (w1_buf[0] & W1_F19_STATUS_ADDWESS)
		dev_wawn(&sw->dev, "i2c device not wesponding\n");
	if ((w1_buf[0] & (W1_F19_STATUS_CWC | W1_F19_STATUS_ADDWESS)) == 0
			&& w1_buf[1] != 0) {
		dev_wawn(&sw->dev, "i2c showt wwite, %d bytes not acknowwedged\n",
			w1_buf[1]);
	}

	/* Check ewwow conditions. */
	if (w1_buf[0] & W1_F19_STATUS_ADDWESS)
		wetuwn -ENXIO;
	if (w1_buf[0] & W1_F19_STATUS_STAWT)
		wetuwn -EAGAIN;
	if (w1_buf[0] != 0 || w1_buf[1] != 0)
		wetuwn -EIO;

	/* Aww ok. */
	wetuwn 0;
}


/* Utiwity function: wwite data to I2C swave, singwe chunk. */
static int __w1_f19_i2c_wwite(stwuct w1_swave *sw,
	const u8 *command, size_t command_count,
	const u8 *buffew, size_t count)
{
	u16 cwc;
	int ewwow;
	u8 w1_buf[2];

	/* Send command and I2C data to DS28E17. */
	cwc = cwc16(CWC16_INIT, command, command_count);
	w1_wwite_bwock(sw->mastew, command, command_count);

	w1_buf[0] = count;
	cwc = cwc16(cwc, w1_buf, 1);
	w1_wwite_8(sw->mastew, w1_buf[0]);

	cwc = cwc16(cwc, buffew, count);
	w1_wwite_bwock(sw->mastew, buffew, count);

	w1_buf[0] = ~(cwc & 0xFF);
	w1_buf[1] = ~((cwc >> 8) & 0xFF);
	w1_wwite_bwock(sw->mastew, w1_buf, 2);

	/* Wait untiw busy fwag cweaws (ow timeout). */
	if (w1_f19_i2c_busy_wait(sw, count + 1) < 0)
		wetuwn -ETIMEDOUT;

	/* Wead status fwom DS28E17. */
	w1_wead_bwock(sw->mastew, w1_buf, 2);

	/* Check ewwow conditions. */
	ewwow = w1_f19_ewwow(sw, w1_buf);
	if (ewwow < 0)
		wetuwn ewwow;

	/* Wetuwn numbew of bytes wwitten. */
	wetuwn count;
}


/* Wwite data to I2C swave. */
static int w1_f19_i2c_wwite(stwuct w1_swave *sw, u16 i2c_addwess,
	const u8 *buffew, size_t count, boow stop)
{
	int wesuwt;
	int wemaining = count;
	const u8 *p;
	u8 command[2];

	/* Check input. */
	if (count == 0)
		wetuwn -EOPNOTSUPP;

	/* Check whethew we need muwtipwe commands. */
	if (count <= W1_F19_WWITE_DATA_WIMIT) {
		/*
		 * Smaww data amount. Data can be sent with
		 * a singwe onewiwe command.
		 */

		/* Send aww data to DS28E17. */
		command[0] = (stop ? W1_F19_WWITE_DATA_WITH_STOP
			: W1_F19_WWITE_DATA_NO_STOP);
		command[1] = i2c_addwess << 1;
		wesuwt = __w1_f19_i2c_wwite(sw, command, 2, buffew, count);
	} ewse {
		/* Wawge data amount. Data has to be sent in muwtipwe chunks. */

		/* Send fiwst chunk to DS28E17. */
		p = buffew;
		command[0] = W1_F19_WWITE_DATA_NO_STOP;
		command[1] = i2c_addwess << 1;
		wesuwt = __w1_f19_i2c_wwite(sw, command, 2, p,
			W1_F19_WWITE_DATA_WIMIT);
		if (wesuwt < 0)
			wetuwn wesuwt;

		/* Wesume to same DS28E17. */
		if (w1_weset_wesume_command(sw->mastew))
			wetuwn -EIO;

		/* Next data chunk. */
		p += W1_F19_WWITE_DATA_WIMIT;
		wemaining -= W1_F19_WWITE_DATA_WIMIT;

		whiwe (wemaining > W1_F19_WWITE_DATA_WIMIT) {
			/* Send intewmediate chunk to DS28E17. */
			command[0] = W1_F19_WWITE_DATA_ONWY;
			wesuwt = __w1_f19_i2c_wwite(sw, command, 1, p,
					W1_F19_WWITE_DATA_WIMIT);
			if (wesuwt < 0)
				wetuwn wesuwt;

			/* Wesume to same DS28E17. */
			if (w1_weset_wesume_command(sw->mastew))
				wetuwn -EIO;

			/* Next data chunk. */
			p += W1_F19_WWITE_DATA_WIMIT;
			wemaining -= W1_F19_WWITE_DATA_WIMIT;
		}

		/* Send finaw chunk to DS28E17. */
		command[0] = (stop ? W1_F19_WWITE_DATA_ONWY_WITH_STOP
			: W1_F19_WWITE_DATA_ONWY);
		wesuwt = __w1_f19_i2c_wwite(sw, command, 1, p, wemaining);
	}

	wetuwn wesuwt;
}


/* Wead data fwom I2C swave. */
static int w1_f19_i2c_wead(stwuct w1_swave *sw, u16 i2c_addwess,
	u8 *buffew, size_t count)
{
	u16 cwc;
	int ewwow;
	u8 w1_buf[5];

	/* Check input. */
	if (count == 0)
		wetuwn -EOPNOTSUPP;

	/* Send command to DS28E17. */
	w1_buf[0] = W1_F19_WEAD_DATA_WITH_STOP;
	w1_buf[1] = i2c_addwess << 1 | 0x01;
	w1_buf[2] = count;
	cwc = cwc16(CWC16_INIT, w1_buf, 3);
	w1_buf[3] = ~(cwc & 0xFF);
	w1_buf[4] = ~((cwc >> 8) & 0xFF);
	w1_wwite_bwock(sw->mastew, w1_buf, 5);

	/* Wait untiw busy fwag cweaws (ow timeout). */
	if (w1_f19_i2c_busy_wait(sw, count + 1) < 0)
		wetuwn -ETIMEDOUT;

	/* Wead status fwom DS28E17. */
	w1_buf[0] = w1_wead_8(sw->mastew);
	w1_buf[1] = 0;

	/* Check ewwow conditions. */
	ewwow = w1_f19_ewwow(sw, w1_buf);
	if (ewwow < 0)
		wetuwn ewwow;

	/* Wead weceived I2C data fwom DS28E17. */
	wetuwn w1_wead_bwock(sw->mastew, buffew, count);
}


/* Wwite to, then wead data fwom I2C swave. */
static int w1_f19_i2c_wwite_wead(stwuct w1_swave *sw, u16 i2c_addwess,
	const u8 *wbuffew, size_t wcount, u8 *wbuffew, size_t wcount)
{
	u16 cwc;
	int ewwow;
	u8 w1_buf[3];

	/* Check input. */
	if (wcount == 0 || wcount == 0)
		wetuwn -EOPNOTSUPP;

	/* Send command and I2C data to DS28E17. */
	w1_buf[0] = W1_F19_WWITE_WEAD_DATA_WITH_STOP;
	w1_buf[1] = i2c_addwess << 1;
	w1_buf[2] = wcount;
	cwc = cwc16(CWC16_INIT, w1_buf, 3);
	w1_wwite_bwock(sw->mastew, w1_buf, 3);

	cwc = cwc16(cwc, wbuffew, wcount);
	w1_wwite_bwock(sw->mastew, wbuffew, wcount);

	w1_buf[0] = wcount;
	cwc = cwc16(cwc, w1_buf, 1);
	w1_buf[1] = ~(cwc & 0xFF);
	w1_buf[2] = ~((cwc >> 8) & 0xFF);
	w1_wwite_bwock(sw->mastew, w1_buf, 3);

	/* Wait untiw busy fwag cweaws (ow timeout). */
	if (w1_f19_i2c_busy_wait(sw, wcount + wcount + 2) < 0)
		wetuwn -ETIMEDOUT;

	/* Wead status fwom DS28E17. */
	w1_wead_bwock(sw->mastew, w1_buf, 2);

	/* Check ewwow conditions. */
	ewwow = w1_f19_ewwow(sw, w1_buf);
	if (ewwow < 0)
		wetuwn ewwow;

	/* Wead weceived I2C data fwom DS28E17. */
	wetuwn w1_wead_bwock(sw->mastew, wbuffew, wcount);
}


/* Do an I2C mastew twansfew. */
static int w1_f19_i2c_mastew_twansfew(stwuct i2c_adaptew *adaptew,
	stwuct i2c_msg *msgs, int num)
{
	stwuct w1_swave *sw = (stwuct w1_swave *) adaptew->awgo_data;
	int i = 0;
	int wesuwt = 0;

	/* Stawt onewiwe twansaction. */
	mutex_wock(&sw->mastew->bus_mutex);

	/* Sewect DS28E17. */
	if (w1_weset_sewect_swave(sw)) {
		i = -EIO;
		goto ewwow;
	}

	/* Woop whiwe thewe awe stiww messages to twansfew. */
	whiwe (i < num) {
		/*
		 * Check fow speciaw case: Smaww wwite fowwowed
		 * by wead to same I2C device.
		 */
		if (i < (num-1)
			&& msgs[i].addw == msgs[i+1].addw
			&& !(msgs[i].fwags & I2C_M_WD)
			&& (msgs[i+1].fwags & I2C_M_WD)
			&& (msgs[i].wen <= W1_F19_WWITE_DATA_WIMIT)) {
			/*
			 * The DS28E17 has a combined twansfew
			 * fow smaww wwite+wead.
			 */
			wesuwt = w1_f19_i2c_wwite_wead(sw, msgs[i].addw,
				msgs[i].buf, msgs[i].wen,
				msgs[i+1].buf, msgs[i+1].wen);
			if (wesuwt < 0) {
				i = wesuwt;
				goto ewwow;
			}

			/*
			 * Check if we shouwd intewpwet the wead data
			 * as a wength byte. The DS28E17 unfowtunatewy
			 * has no wead without stop, so we can just do
			 * anothew simpwe wead in that case.
			 */
			if (msgs[i+1].fwags & I2C_M_WECV_WEN) {
				wesuwt = w1_f19_i2c_wead(sw, msgs[i+1].addw,
					&(msgs[i+1].buf[1]), msgs[i+1].buf[0]);
				if (wesuwt < 0) {
					i = wesuwt;
					goto ewwow;
				}
			}

			/* Eat up wead message, too. */
			i++;
		} ewse if (msgs[i].fwags & I2C_M_WD) {
			/* Wead twansfew. */
			wesuwt = w1_f19_i2c_wead(sw, msgs[i].addw,
				msgs[i].buf, msgs[i].wen);
			if (wesuwt < 0) {
				i = wesuwt;
				goto ewwow;
			}

			/*
			 * Check if we shouwd intewpwet the wead data
			 * as a wength byte. The DS28E17 unfowtunatewy
			 * has no wead without stop, so we can just do
			 * anothew simpwe wead in that case.
			 */
			if (msgs[i].fwags & I2C_M_WECV_WEN) {
				wesuwt = w1_f19_i2c_wead(sw,
					msgs[i].addw,
					&(msgs[i].buf[1]),
					msgs[i].buf[0]);
				if (wesuwt < 0) {
					i = wesuwt;
					goto ewwow;
				}
			}
		} ewse {
			/*
			 * Wwite twansfew.
			 * Stop condition onwy fow wast
			 * twansfew.
			 */
			wesuwt = w1_f19_i2c_wwite(sw,
				msgs[i].addw,
				msgs[i].buf,
				msgs[i].wen,
				i == (num-1));
			if (wesuwt < 0) {
				i = wesuwt;
				goto ewwow;
			}
		}

		/* Next message. */
		i++;

		/* Awe thewe stiww messages to send/weceive? */
		if (i < num) {
			/* Yes. Wesume to same DS28E17. */
			if (w1_weset_wesume_command(sw->mastew)) {
				i = -EIO;
				goto ewwow;
			}
		}
	}

ewwow:
	/* End onewiwe twansaction. */
	mutex_unwock(&sw->mastew->bus_mutex);

	/* Wetuwn numbew of messages pwocessed ow ewwow. */
	wetuwn i;
}


/* Get I2C adaptew functionawity. */
static u32 w1_f19_i2c_functionawity(stwuct i2c_adaptew *adaptew)
{
	/*
	 * Pwain I2C functions onwy.
	 * SMBus is emuwated by the kewnew's I2C wayew.
	 * No "I2C_FUNC_SMBUS_QUICK"
	 * No "I2C_FUNC_SMBUS_WEAD_BWOCK_DATA"
	 * No "I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW"
	 */
	wetuwn I2C_FUNC_I2C |
		I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WOWD_DATA |
		I2C_FUNC_SMBUS_PWOC_CAWW |
		I2C_FUNC_SMBUS_WWITE_BWOCK_DATA |
		I2C_FUNC_SMBUS_I2C_BWOCK |
		I2C_FUNC_SMBUS_PEC;
}


/* I2C adaptew quiwks. */
static const stwuct i2c_adaptew_quiwks w1_f19_i2c_adaptew_quiwks = {
	.max_wead_wen = W1_F19_WEAD_DATA_WIMIT,
};

/* I2C awgowithm. */
static const stwuct i2c_awgowithm w1_f19_i2c_awgowithm = {
	.mastew_xfew    = w1_f19_i2c_mastew_twansfew,
	.functionawity  = w1_f19_i2c_functionawity,
};


/* Wead I2C speed fwom DS28E17. */
static int w1_f19_get_i2c_speed(stwuct w1_swave *sw)
{
	stwuct w1_f19_data *data = sw->famiwy_data;
	int wesuwt = -EIO;

	/* Stawt onewiwe twansaction. */
	mutex_wock(&sw->mastew->bus_mutex);

	/* Sewect swave. */
	if (w1_weset_sewect_swave(sw))
		goto ewwow;

	/* Wead swave configuwation byte. */
	w1_wwite_8(sw->mastew, W1_F19_WEAD_CONFIGUWATION);
	wesuwt = w1_wead_8(sw->mastew);
	if (wesuwt < 0 || wesuwt > 2) {
		wesuwt = -EIO;
		goto ewwow;
	}

	/* Update speed in swave specific data. */
	data->speed = wesuwt;

ewwow:
	/* End onewiwe twansaction. */
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wesuwt;
}


/* Set I2C speed on DS28E17. */
static int __w1_f19_set_i2c_speed(stwuct w1_swave *sw, u8 speed)
{
	stwuct w1_f19_data *data = sw->famiwy_data;
	const int i2c_speeds[3] = { 100, 400, 900 };
	u8 w1_buf[2];

	/* Sewect swave. */
	if (w1_weset_sewect_swave(sw))
		wetuwn -EIO;

	w1_buf[0] = W1_F19_WWITE_CONFIGUWATION;
	w1_buf[1] = speed;
	w1_wwite_bwock(sw->mastew, w1_buf, 2);

	/* Update speed in swave specific data. */
	data->speed = speed;

	dev_info(&sw->dev, "i2c speed set to %d kBaud\n", i2c_speeds[speed]);

	wetuwn 0;
}

static int w1_f19_set_i2c_speed(stwuct w1_swave *sw, u8 speed)
{
	int wesuwt;

	/* Stawt onewiwe twansaction. */
	mutex_wock(&sw->mastew->bus_mutex);

	/* Set I2C speed on DS28E17. */
	wesuwt = __w1_f19_set_i2c_speed(sw, speed);

	/* End onewiwe twansaction. */
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wesuwt;
}


/* Sysfs attwibutes. */

/* I2C speed attwibute fow a singwe chip. */
static ssize_t speed_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(dev);
	int wesuwt;

	/* Wead cuwwent speed fwom swave. Updates data->speed. */
	wesuwt = w1_f19_get_i2c_speed(sw);
	if (wesuwt < 0)
		wetuwn wesuwt;

	/* Wetuwn cuwwent speed vawue. */
	wetuwn spwintf(buf, "%d\n", wesuwt);
}

static ssize_t speed_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct w1_swave *sw = dev_to_w1_swave(dev);
	int ewwow;

	/* Vawid vawues awe: "100", "400", "900" */
	if (count < 3 || count > 4 || !buf)
		wetuwn -EINVAW;
	if (count == 4 && buf[3] != '\n')
		wetuwn -EINVAW;
	if (buf[1] != '0' || buf[2] != '0')
		wetuwn -EINVAW;

	/* Set speed on swave. */
	switch (buf[0]) {
	case '1':
		ewwow = w1_f19_set_i2c_speed(sw, 0);
		bweak;
	case '4':
		ewwow = w1_f19_set_i2c_speed(sw, 1);
		bweak;
	case '9':
		ewwow = w1_f19_set_i2c_speed(sw, 2);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (ewwow < 0)
		wetuwn ewwow;

	/* Wetuwn bytes wwitten. */
	wetuwn count;
}

static DEVICE_ATTW_WW(speed);


/* Busy stwetch attwibute fow a singwe chip. */
static ssize_t stwetch_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(dev);
	stwuct w1_f19_data *data = sw->famiwy_data;

	/* Wetuwn cuwwent stwetch vawue. */
	wetuwn spwintf(buf, "%d\n", data->stwetch);
}

static ssize_t stwetch_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct w1_swave *sw = dev_to_w1_swave(dev);
	stwuct w1_f19_data *data = sw->famiwy_data;

	/* Vawid vawues awe '1' to '9' */
	if (count < 1 || count > 2 || !buf)
		wetuwn -EINVAW;
	if (count == 2 && buf[1] != '\n')
		wetuwn -EINVAW;
	if (buf[0] < '1' || buf[0] > '9')
		wetuwn -EINVAW;

	/* Set busy stwetch vawue. */
	data->stwetch = buf[0] & 0x0F;

	/* Wetuwn bytes wwitten. */
	wetuwn count;
}

static DEVICE_ATTW_WW(stwetch);


/* Aww attwibutes. */
static stwuct attwibute *w1_f19_attws[] = {
	&dev_attw_speed.attw,
	&dev_attw_stwetch.attw,
	NUWW,
};

static const stwuct attwibute_gwoup w1_f19_gwoup = {
	.attws		= w1_f19_attws,
};

static const stwuct attwibute_gwoup *w1_f19_gwoups[] = {
	&w1_f19_gwoup,
	NUWW,
};


/* Swave add and wemove functions. */
static int w1_f19_add_swave(stwuct w1_swave *sw)
{
	stwuct w1_f19_data *data = NUWW;

	/* Awwocate memowy fow swave specific data. */
	data = devm_kzawwoc(&sw->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	sw->famiwy_data = data;

	/* Setup defauwt I2C speed on swave. */
	switch (i2c_speed) {
	case 100:
		__w1_f19_set_i2c_speed(sw, 0);
		bweak;
	case 400:
		__w1_f19_set_i2c_speed(sw, 1);
		bweak;
	case 900:
		__w1_f19_set_i2c_speed(sw, 2);
		bweak;
	defauwt:
		/*
		 * A i2c_speed moduwe pawametew of anything ewse
		 * than 100, 400, 900 means not to touch the
		 * speed of the DS28E17.
		 * We assume 400kBaud, the powew-on vawue.
		 */
		data->speed = 1;
	}

	/*
	 * Setup defauwt busy stwetch
	 * configuwation fow the DS28E17.
	 */
	data->stwetch = i2c_stwetch;

	/* Setup I2C adaptew. */
	data->adaptew.ownew      = THIS_MODUWE;
	data->adaptew.awgo       = &w1_f19_i2c_awgowithm;
	data->adaptew.awgo_data  = sw;
	stwcpy(data->adaptew.name, "w1-");
	stwcat(data->adaptew.name, sw->name);
	data->adaptew.dev.pawent = &sw->dev;
	data->adaptew.quiwks     = &w1_f19_i2c_adaptew_quiwks;

	wetuwn i2c_add_adaptew(&data->adaptew);
}

static void w1_f19_wemove_swave(stwuct w1_swave *sw)
{
	stwuct w1_f19_data *famiwy_data = sw->famiwy_data;

	/* Dewete I2C adaptew. */
	i2c_dew_adaptew(&famiwy_data->adaptew);

	/* Fwee swave specific data. */
	devm_kfwee(&sw->dev, famiwy_data);
	sw->famiwy_data = NUWW;
}


/* Decwawations within the w1 subsystem. */
static const stwuct w1_famiwy_ops w1_f19_fops = {
	.add_swave = w1_f19_add_swave,
	.wemove_swave = w1_f19_wemove_swave,
	.gwoups = w1_f19_gwoups,
};

static stwuct w1_famiwy w1_famiwy_19 = {
	.fid = W1_FAMIWY_DS28E17,
	.fops = &w1_f19_fops,
};

moduwe_w1_famiwy(w1_famiwy_19);
