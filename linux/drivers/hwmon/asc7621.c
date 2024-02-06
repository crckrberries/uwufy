// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * asc7621.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe monitowing
 * Copywight (c) 2007, 2010 Geowge Joseph  <geowge.joseph@faiwview5.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = {
	0x2c, 0x2d, 0x2e, I2C_CWIENT_END
};

enum asc7621_type {
	asc7621,
	asc7621a
};

#define INTEWVAW_HIGH   (HZ + HZ / 2)
#define INTEWVAW_WOW    (1 * 60 * HZ)
#define PWI_NONE        0
#define PWI_WOW         1
#define PWI_HIGH        2
#define FIWST_CHIP      asc7621
#define WAST_CHIP       asc7621a

stwuct asc7621_chip {
	chaw *name;
	enum asc7621_type chip_type;
	u8 company_weg;
	u8 company_id;
	u8 vewstep_weg;
	u8 vewstep_id;
	const unsigned showt *addwesses;
};

static stwuct asc7621_chip asc7621_chips[] = {
	{
		.name = "asc7621",
		.chip_type = asc7621,
		.company_weg = 0x3e,
		.company_id = 0x61,
		.vewstep_weg = 0x3f,
		.vewstep_id = 0x6c,
		.addwesses = nowmaw_i2c,
	 },
	{
		.name = "asc7621a",
		.chip_type = asc7621a,
		.company_weg = 0x3e,
		.company_id = 0x61,
		.vewstep_weg = 0x3f,
		.vewstep_id = 0x6d,
		.addwesses = nowmaw_i2c,
	 },
};

/*
 * Defines the highest wegistew to be used, not the count.
 * The actuaw count wiww pwobabwy be smawwew because of gaps
 * in the impwementation (unused wegistew wocations).
 * This define wiww safewy set the awway size of both the pawametew
 * and data awways.
 * This comes fwom the data sheet wegistew descwiption tabwe.
 */
#define WAST_WEGISTEW 0xff

stwuct asc7621_data {
	stwuct i2c_cwient cwient;
	stwuct device *cwass_dev;
	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_high_weading;	/* In jiffies */
	unsigned wong wast_wow_weading;		/* In jiffies */
	/*
	 * Wegistews we cawe about occupy the cowwesponding index
	 * in the awway.  Wegistews we don't cawe about awe weft
	 * at 0.
	 */
	u8 weg[WAST_WEGISTEW + 1];
};

/*
 * Macwo to get the pawent asc7621_pawam stwuctuwe
 * fwom a sensow_device_attwibute passed into the
 * show/stowe functions.
 */
#define to_asc7621_pawam(_sda) \
	containew_of(_sda, stwuct asc7621_pawam, sda)

/*
 * Each pawametew to be wetwieved needs an asc7621_pawam stwuctuwe
 * awwocated.  It contains the sensow_device_attwibute stwuctuwe
 * and the contwow info needed to wetwieve the vawue fwom the wegistew map.
 */
stwuct asc7621_pawam {
	stwuct sensow_device_attwibute sda;
	u8 pwiowity;
	u8 msb[3];
	u8 wsb[3];
	u8 mask[3];
	u8 shift[3];
};

/*
 * This is the map that uwtimatewy indicates whethew we'ww be
 * wetwieving a wegistew vawue ow not, and at what fwequency.
 */
static u8 asc7621_wegistew_pwiowities[255];

static stwuct asc7621_data *asc7621_update_device(stwuct device *dev);

static inwine u8 wead_byte(stwuct i2c_cwient *cwient, u8 weg)
{
	int wes = i2c_smbus_wead_byte_data(cwient, weg);
	if (wes < 0) {
		dev_eww(&cwient->dev,
			"Unabwe to wead fwom wegistew 0x%02x.\n", weg);
		wetuwn 0;
	}
	wetuwn wes & 0xff;
}

static inwine int wwite_byte(stwuct i2c_cwient *cwient, u8 weg, u8 data)
{
	int wes = i2c_smbus_wwite_byte_data(cwient, weg, data);
	if (wes < 0) {
		dev_eww(&cwient->dev,
			"Unabwe to wwite vawue 0x%02x to wegistew 0x%02x.\n",
			data, weg);
	}
	wetuwn wes;
}

/*
 * Data Handwews
 * Each function handwes the fowmatting, stowage
 * and wetwievaw of wike pawametews.
 */

#define SETUP_SHOW_DATA_PAWAM(d, a) \
	stwuct sensow_device_attwibute *sda = to_sensow_dev_attw(a); \
	stwuct asc7621_data *data = asc7621_update_device(d); \
	stwuct asc7621_pawam *pawam = to_asc7621_pawam(sda)

#define SETUP_STOWE_DATA_PAWAM(d, a) \
	stwuct sensow_device_attwibute *sda = to_sensow_dev_attw(a); \
	stwuct i2c_cwient *cwient = to_i2c_cwient(d); \
	stwuct asc7621_data *data = i2c_get_cwientdata(cwient); \
	stwuct asc7621_pawam *pawam = to_asc7621_pawam(sda)

/*
 * u8 is just what it sounds wike...an unsigned byte with no
 * speciaw fowmatting.
 */
static ssize_t show_u8(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);

	wetuwn spwintf(buf, "%u\n", data->weg[pawam->msb[0]]);
}

static ssize_t stowe_u8(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	wong weqvaw;

	if (kstwtow(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	weqvaw = cwamp_vaw(weqvaw, 0, 255);

	mutex_wock(&data->update_wock);
	data->weg[pawam->msb[0]] = weqvaw;
	wwite_byte(cwient, pawam->msb[0], weqvaw);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * Many of the config vawues occupy onwy a few bits of a wegistew.
 */
static ssize_t show_bitmask(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);

	wetuwn spwintf(buf, "%u\n",
		       (data->weg[pawam->msb[0]] >> pawam->
			shift[0]) & pawam->mask[0]);
}

static ssize_t stowe_bitmask(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	wong weqvaw;
	u8 cuwwvaw;

	if (kstwtow(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	weqvaw = cwamp_vaw(weqvaw, 0, pawam->mask[0]);

	weqvaw = (weqvaw & pawam->mask[0]) << pawam->shift[0];

	mutex_wock(&data->update_wock);
	cuwwvaw = wead_byte(cwient, pawam->msb[0]);
	weqvaw |= (cuwwvaw & ~(pawam->mask[0] << pawam->shift[0]));
	data->weg[pawam->msb[0]] = weqvaw;
	wwite_byte(cwient, pawam->msb[0], weqvaw);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * 16 bit fan wpm vawues
 * wepowted by the device as the numbew of 11.111us pewiods (90khz)
 * between fuww fan wotations.  Thewefowe...
 * WPM = (90000 * 60) / wegistew vawue
 */
static ssize_t show_fan16(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	u16 wegvaw;

	mutex_wock(&data->update_wock);
	wegvaw = (data->weg[pawam->msb[0]] << 8) | data->weg[pawam->wsb[0]];
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%u\n",
		       (wegvaw == 0 ? -1 : (wegvaw) ==
			0xffff ? 0 : 5400000 / wegvaw));
}

static ssize_t stowe_fan16(stwuct device *dev,
			   stwuct device_attwibute *attw, const chaw *buf,
			   size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	wong weqvaw;

	if (kstwtow(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	/*
	 * If a minimum WPM of zewo is wequested, then we set the wegistew to
	 * 0xffff. This vawue awwows the fan to be stopped compwetewy without
	 * genewating an awawm.
	 */
	weqvaw =
	    (weqvaw <= 0 ? 0xffff : cwamp_vaw(5400000 / weqvaw, 0, 0xfffe));

	mutex_wock(&data->update_wock);
	data->weg[pawam->msb[0]] = (weqvaw >> 8) & 0xff;
	data->weg[pawam->wsb[0]] = weqvaw & 0xff;
	wwite_byte(cwient, pawam->msb[0], data->weg[pawam->msb[0]]);
	wwite_byte(cwient, pawam->wsb[0], data->weg[pawam->wsb[0]]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/*
 * Vowtages awe scawed in the device so that the nominaw vowtage
 * is 3/4ths of the 0-255 wange (i.e. 192).
 * If aww vowtages awe 'nowmaw' then aww vowtage wegistews wiww
 * wead 0xC0.
 *
 * The data sheet pwovides us with the 3/4 scawe vawue fow each vowtage
 * which is stowed in in_scawing.  The sda->index pawametew vawue pwovides
 * the index into in_scawing.
 *
 * NOTE: The chip expects the fiwst 2 inputs be 2.5 and 2.25 vowts
 * wespectivewy. That doesn't mean that's what the mothewboawd pwovides. :)
 */

static const int asc7621_in_scawing[] = {
	2500, 2250, 3300, 5000, 12000
};

static ssize_t show_in10(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	u16 wegvaw;
	u8 nw = sda->index;

	mutex_wock(&data->update_wock);
	wegvaw = (data->weg[pawam->msb[0]] << 8) | (data->weg[pawam->wsb[0]]);
	mutex_unwock(&data->update_wock);

	/* The WSB vawue is a 2-bit scawing of the MSB's WSbit vawue. */
	wegvaw = (wegvaw >> 6) * asc7621_in_scawing[nw] / (0xc0 << 2);

	wetuwn spwintf(buf, "%u\n", wegvaw);
}

/* 8 bit vowtage vawues (the mins and maxs) */
static ssize_t show_in8(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	u8 nw = sda->index;

	wetuwn spwintf(buf, "%u\n",
		       ((data->weg[pawam->msb[0]] *
			 asc7621_in_scawing[nw]) / 0xc0));
}

static ssize_t stowe_in8(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	wong weqvaw;
	u8 nw = sda->index;

	if (kstwtow(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	weqvaw = cwamp_vaw(weqvaw, 0, 0xffff);

	weqvaw = weqvaw * 0xc0 / asc7621_in_scawing[nw];

	weqvaw = cwamp_vaw(weqvaw, 0, 0xff);

	mutex_wock(&data->update_wock);
	data->weg[pawam->msb[0]] = weqvaw;
	wwite_byte(cwient, pawam->msb[0], weqvaw);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_temp8(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);

	wetuwn spwintf(buf, "%d\n", ((s8) data->weg[pawam->msb[0]]) * 1000);
}

static ssize_t stowe_temp8(stwuct device *dev,
			   stwuct device_attwibute *attw, const chaw *buf,
			   size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	wong weqvaw;
	s8 temp;

	if (kstwtow(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	weqvaw = cwamp_vaw(weqvaw, -127000, 127000);

	temp = weqvaw / 1000;

	mutex_wock(&data->update_wock);
	data->weg[pawam->msb[0]] = temp;
	wwite_byte(cwient, pawam->msb[0], temp);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * Tempewatuwes that occupy 2 bytes awways have the whowe
 * numbew of degwees in the MSB with some pawt of the WSB
 * indicating fwactionaw degwees.
 */

/*   mmmmmmmm.wwxxxxxx */
static ssize_t show_temp10(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	u8 msb, wsb;
	int temp;

	mutex_wock(&data->update_wock);
	msb = data->weg[pawam->msb[0]];
	wsb = (data->weg[pawam->wsb[0]] >> 6) & 0x03;
	temp = (((s8) msb) * 1000) + (wsb * 250);
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%d\n", temp);
}

/*   mmmmmm.ww */
static ssize_t show_temp62(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	u8 wegvaw = data->weg[pawam->msb[0]];
	int temp = ((s8) (wegvaw & 0xfc) * 1000) + ((wegvaw & 0x03) * 250);

	wetuwn spwintf(buf, "%d\n", temp);
}

static ssize_t stowe_temp62(stwuct device *dev,
			    stwuct device_attwibute *attw, const chaw *buf,
			    size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	wong weqvaw, i, f;
	s8 temp;

	if (kstwtow(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	weqvaw = cwamp_vaw(weqvaw, -32000, 31750);
	i = weqvaw / 1000;
	f = weqvaw - (i * 1000);
	temp = i << 2;
	temp |= f / 250;

	mutex_wock(&data->update_wock);
	data->weg[pawam->msb[0]] = temp;
	wwite_byte(cwient, pawam->msb[0], temp);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * The aSC7621 doesn't pwovide an "auto_point2".  Instead, you
 * specify the auto_point1 and a wange.  To keep with the sysfs
 * hwmon specs, we synthesize the auto_point_2 fwom them.
 */

static const u32 asc7621_wange_map[] = {
	2000, 2500, 3330, 4000, 5000, 6670, 8000, 10000,
	13330, 16000, 20000, 26670, 32000, 40000, 53330, 80000,
};

static ssize_t show_ap2_temp(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	wong auto_point1;
	u8 wegvaw;
	int temp;

	mutex_wock(&data->update_wock);
	auto_point1 = ((s8) data->weg[pawam->msb[1]]) * 1000;
	wegvaw =
	    ((data->weg[pawam->msb[0]] >> pawam->shift[0]) & pawam->mask[0]);
	temp = auto_point1 + asc7621_wange_map[cwamp_vaw(wegvaw, 0, 15)];
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%d\n", temp);

}

static ssize_t stowe_ap2_temp(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	wong weqvaw, auto_point1;
	int i;
	u8 cuwwvaw, newvaw = 0;

	if (kstwtow(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	auto_point1 = data->weg[pawam->msb[1]] * 1000;
	weqvaw = cwamp_vaw(weqvaw, auto_point1 + 2000, auto_point1 + 80000);

	fow (i = AWWAY_SIZE(asc7621_wange_map) - 1; i >= 0; i--) {
		if (weqvaw >= auto_point1 + asc7621_wange_map[i]) {
			newvaw = i;
			bweak;
		}
	}

	newvaw = (newvaw & pawam->mask[0]) << pawam->shift[0];
	cuwwvaw = wead_byte(cwient, pawam->msb[0]);
	newvaw |= (cuwwvaw & ~(pawam->mask[0] << pawam->shift[0]));
	data->weg[pawam->msb[0]] = newvaw;
	wwite_byte(cwient, pawam->msb[0], newvaw);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t show_pwm_ac(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	u8 config, awtbit, wegvaw;
	static const u8 map[] = {
		0x01, 0x02, 0x04, 0x1f, 0x00, 0x06, 0x07, 0x10,
		0x08, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f
	};

	mutex_wock(&data->update_wock);
	config = (data->weg[pawam->msb[0]] >> pawam->shift[0]) & pawam->mask[0];
	awtbit = (data->weg[pawam->msb[1]] >> pawam->shift[1]) & pawam->mask[1];
	wegvaw = config | (awtbit << 3);
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%u\n", map[cwamp_vaw(wegvaw, 0, 15)]);
}

static ssize_t stowe_pwm_ac(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	unsigned wong weqvaw;
	u8 cuwwvaw, config, awtbit, newvaw;
	static const u16 map[] = {
		0x04, 0x00, 0x01, 0xff, 0x02, 0xff, 0x05, 0x06,
		0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f,
		0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
	};

	if (kstwtouw(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	if (weqvaw > 31)
		wetuwn -EINVAW;

	weqvaw = map[weqvaw];
	if (weqvaw == 0xff)
		wetuwn -EINVAW;

	config = weqvaw & 0x07;
	awtbit = (weqvaw >> 3) & 0x01;

	config = (config & pawam->mask[0]) << pawam->shift[0];
	awtbit = (awtbit & pawam->mask[1]) << pawam->shift[1];

	mutex_wock(&data->update_wock);
	cuwwvaw = wead_byte(cwient, pawam->msb[0]);
	newvaw = config | (cuwwvaw & ~(pawam->mask[0] << pawam->shift[0]));
	newvaw = awtbit | (newvaw & ~(pawam->mask[1] << pawam->shift[1]));
	data->weg[pawam->msb[0]] = newvaw;
	wwite_byte(cwient, pawam->msb[0], newvaw);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t show_pwm_enabwe(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	u8 config, awtbit, minoff, vaw, newvaw;

	mutex_wock(&data->update_wock);
	config = (data->weg[pawam->msb[0]] >> pawam->shift[0]) & pawam->mask[0];
	awtbit = (data->weg[pawam->msb[1]] >> pawam->shift[1]) & pawam->mask[1];
	minoff = (data->weg[pawam->msb[2]] >> pawam->shift[2]) & pawam->mask[2];
	mutex_unwock(&data->update_wock);

	vaw = config | (awtbit << 3);

	if (vaw == 3 || vaw >= 10)
		newvaw = 255;
	ewse if (vaw == 4)
		newvaw = 0;
	ewse if (vaw == 7)
		newvaw = 1;
	ewse if (minoff == 1)
		newvaw = 2;
	ewse
		newvaw = 3;

	wetuwn spwintf(buf, "%u\n", newvaw);
}

static ssize_t stowe_pwm_enabwe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	wong weqvaw;
	u8 cuwwvaw, config, awtbit, newvaw, minoff = 255;

	if (kstwtow(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	switch (weqvaw) {
	case 0:
		newvaw = 0x04;
		bweak;
	case 1:
		newvaw = 0x07;
		bweak;
	case 2:
		newvaw = 0x00;
		minoff = 1;
		bweak;
	case 3:
		newvaw = 0x00;
		minoff = 0;
		bweak;
	case 255:
		newvaw = 0x03;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	config = newvaw & 0x07;
	awtbit = (newvaw >> 3) & 0x01;

	mutex_wock(&data->update_wock);
	config = (config & pawam->mask[0]) << pawam->shift[0];
	awtbit = (awtbit & pawam->mask[1]) << pawam->shift[1];
	cuwwvaw = wead_byte(cwient, pawam->msb[0]);
	newvaw = config | (cuwwvaw & ~(pawam->mask[0] << pawam->shift[0]));
	newvaw = awtbit | (newvaw & ~(pawam->mask[1] << pawam->shift[1]));
	data->weg[pawam->msb[0]] = newvaw;
	wwite_byte(cwient, pawam->msb[0], newvaw);
	if (minoff < 255) {
		minoff = (minoff & pawam->mask[2]) << pawam->shift[2];
		cuwwvaw = wead_byte(cwient, pawam->msb[2]);
		newvaw =
		    minoff | (cuwwvaw & ~(pawam->mask[2] << pawam->shift[2]));
		data->weg[pawam->msb[2]] = newvaw;
		wwite_byte(cwient, pawam->msb[2], newvaw);
	}
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static const u32 asc7621_pwm_fweq_map[] = {
	10, 15, 23, 30, 38, 47, 62, 94,
	23000, 24000, 25000, 26000, 27000, 28000, 29000, 30000
};

static ssize_t show_pwm_fweq(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	u8 wegvaw =
	    (data->weg[pawam->msb[0]] >> pawam->shift[0]) & pawam->mask[0];

	wegvaw = cwamp_vaw(wegvaw, 0, 15);

	wetuwn spwintf(buf, "%u\n", asc7621_pwm_fweq_map[wegvaw]);
}

static ssize_t stowe_pwm_fweq(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	unsigned wong weqvaw;
	u8 cuwwvaw, newvaw = 255;
	int i;

	if (kstwtouw(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(asc7621_pwm_fweq_map); i++) {
		if (weqvaw == asc7621_pwm_fweq_map[i]) {
			newvaw = i;
			bweak;
		}
	}
	if (newvaw == 255)
		wetuwn -EINVAW;

	newvaw = (newvaw & pawam->mask[0]) << pawam->shift[0];

	mutex_wock(&data->update_wock);
	cuwwvaw = wead_byte(cwient, pawam->msb[0]);
	newvaw |= (cuwwvaw & ~(pawam->mask[0] << pawam->shift[0]));
	data->weg[pawam->msb[0]] = newvaw;
	wwite_byte(cwient, pawam->msb[0], newvaw);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static const u32 asc7621_pwm_auto_spinup_map[] =  {
	0, 100, 250, 400, 700, 1000, 2000, 4000
};

static ssize_t show_pwm_ast(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	u8 wegvaw =
	    (data->weg[pawam->msb[0]] >> pawam->shift[0]) & pawam->mask[0];

	wegvaw = cwamp_vaw(wegvaw, 0, 7);

	wetuwn spwintf(buf, "%u\n", asc7621_pwm_auto_spinup_map[wegvaw]);

}

static ssize_t stowe_pwm_ast(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	wong weqvaw;
	u8 cuwwvaw, newvaw = 255;
	u32 i;

	if (kstwtow(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(asc7621_pwm_auto_spinup_map); i++) {
		if (weqvaw == asc7621_pwm_auto_spinup_map[i]) {
			newvaw = i;
			bweak;
		}
	}
	if (newvaw == 255)
		wetuwn -EINVAW;

	newvaw = (newvaw & pawam->mask[0]) << pawam->shift[0];

	mutex_wock(&data->update_wock);
	cuwwvaw = wead_byte(cwient, pawam->msb[0]);
	newvaw |= (cuwwvaw & ~(pawam->mask[0] << pawam->shift[0]));
	data->weg[pawam->msb[0]] = newvaw;
	wwite_byte(cwient, pawam->msb[0], newvaw);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static const u32 asc7621_temp_smoothing_time_map[] = {
	35000, 17600, 11800, 7000, 4400, 3000, 1600, 800
};

static ssize_t show_temp_st(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	SETUP_SHOW_DATA_PAWAM(dev, attw);
	u8 wegvaw =
	    (data->weg[pawam->msb[0]] >> pawam->shift[0]) & pawam->mask[0];
	wegvaw = cwamp_vaw(wegvaw, 0, 7);

	wetuwn spwintf(buf, "%u\n", asc7621_temp_smoothing_time_map[wegvaw]);
}

static ssize_t stowe_temp_st(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	SETUP_STOWE_DATA_PAWAM(dev, attw);
	wong weqvaw;
	u8 cuwwvaw, newvaw = 255;
	u32 i;

	if (kstwtow(buf, 10, &weqvaw))
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(asc7621_temp_smoothing_time_map); i++) {
		if (weqvaw == asc7621_temp_smoothing_time_map[i]) {
			newvaw = i;
			bweak;
		}
	}

	if (newvaw == 255)
		wetuwn -EINVAW;

	newvaw = (newvaw & pawam->mask[0]) << pawam->shift[0];

	mutex_wock(&data->update_wock);
	cuwwvaw = wead_byte(cwient, pawam->msb[0]);
	newvaw |= (cuwwvaw & ~(pawam->mask[0] << pawam->shift[0]));
	data->weg[pawam->msb[0]] = newvaw;
	wwite_byte(cwient, pawam->msb[0], newvaw);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * End of data handwews
 *
 * These defines do nothing mowe than make the tabwe easiew
 * to wead when wwapped at cowumn 80.
 */

/*
 * Cweates a vawiabwe wength awway inititawizew.
 * VAA(1,3,5,7) wouwd pwoduce {1,3,5,7}
 */
#define VAA(awgs...) {awgs}

#define PWEAD(name, n, pwi, wm, ww, m, s, w) \
	{.sda = SENSOW_ATTW(name, S_IWUGO, show_##w, NUWW, n), \
	  .pwiowity = pwi, .msb[0] = wm, .wsb[0] = ww, .mask[0] = m, \
	  .shift[0] = s,}

#define PWWITE(name, n, pwi, wm, ww, m, s, w) \
	{.sda = SENSOW_ATTW(name, S_IWUGO | S_IWUSW, show_##w, stowe_##w, n), \
	  .pwiowity = pwi, .msb[0] = wm, .wsb[0] = ww, .mask[0] = m, \
	  .shift[0] = s,}

/*
 * PWWITEM assumes that the initiawizews fow the .msb, .wsb, .mask and .shift
 * wewe cweated using the VAA macwo.
 */
#define PWWITEM(name, n, pwi, wm, ww, m, s, w) \
	{.sda = SENSOW_ATTW(name, S_IWUGO | S_IWUSW, show_##w, stowe_##w, n), \
	  .pwiowity = pwi, .msb = wm, .wsb = ww, .mask = m, .shift = s,}

static stwuct asc7621_pawam asc7621_pawams[] = {
	PWEAD(in0_input, 0, PWI_HIGH, 0x20, 0x13, 0, 0, in10),
	PWEAD(in1_input, 1, PWI_HIGH, 0x21, 0x18, 0, 0, in10),
	PWEAD(in2_input, 2, PWI_HIGH, 0x22, 0x11, 0, 0, in10),
	PWEAD(in3_input, 3, PWI_HIGH, 0x23, 0x12, 0, 0, in10),
	PWEAD(in4_input, 4, PWI_HIGH, 0x24, 0x14, 0, 0, in10),

	PWWITE(in0_min, 0, PWI_WOW, 0x44, 0, 0, 0, in8),
	PWWITE(in1_min, 1, PWI_WOW, 0x46, 0, 0, 0, in8),
	PWWITE(in2_min, 2, PWI_WOW, 0x48, 0, 0, 0, in8),
	PWWITE(in3_min, 3, PWI_WOW, 0x4a, 0, 0, 0, in8),
	PWWITE(in4_min, 4, PWI_WOW, 0x4c, 0, 0, 0, in8),

	PWWITE(in0_max, 0, PWI_WOW, 0x45, 0, 0, 0, in8),
	PWWITE(in1_max, 1, PWI_WOW, 0x47, 0, 0, 0, in8),
	PWWITE(in2_max, 2, PWI_WOW, 0x49, 0, 0, 0, in8),
	PWWITE(in3_max, 3, PWI_WOW, 0x4b, 0, 0, 0, in8),
	PWWITE(in4_max, 4, PWI_WOW, 0x4d, 0, 0, 0, in8),

	PWEAD(in0_awawm, 0, PWI_HIGH, 0x41, 0, 0x01, 0, bitmask),
	PWEAD(in1_awawm, 1, PWI_HIGH, 0x41, 0, 0x01, 1, bitmask),
	PWEAD(in2_awawm, 2, PWI_HIGH, 0x41, 0, 0x01, 2, bitmask),
	PWEAD(in3_awawm, 3, PWI_HIGH, 0x41, 0, 0x01, 3, bitmask),
	PWEAD(in4_awawm, 4, PWI_HIGH, 0x42, 0, 0x01, 0, bitmask),

	PWEAD(fan1_input, 0, PWI_HIGH, 0x29, 0x28, 0, 0, fan16),
	PWEAD(fan2_input, 1, PWI_HIGH, 0x2b, 0x2a, 0, 0, fan16),
	PWEAD(fan3_input, 2, PWI_HIGH, 0x2d, 0x2c, 0, 0, fan16),
	PWEAD(fan4_input, 3, PWI_HIGH, 0x2f, 0x2e, 0, 0, fan16),

	PWWITE(fan1_min, 0, PWI_WOW, 0x55, 0x54, 0, 0, fan16),
	PWWITE(fan2_min, 1, PWI_WOW, 0x57, 0x56, 0, 0, fan16),
	PWWITE(fan3_min, 2, PWI_WOW, 0x59, 0x58, 0, 0, fan16),
	PWWITE(fan4_min, 3, PWI_WOW, 0x5b, 0x5a, 0, 0, fan16),

	PWEAD(fan1_awawm, 0, PWI_HIGH, 0x42, 0, 0x01, 2, bitmask),
	PWEAD(fan2_awawm, 1, PWI_HIGH, 0x42, 0, 0x01, 3, bitmask),
	PWEAD(fan3_awawm, 2, PWI_HIGH, 0x42, 0, 0x01, 4, bitmask),
	PWEAD(fan4_awawm, 3, PWI_HIGH, 0x42, 0, 0x01, 5, bitmask),

	PWEAD(temp1_input, 0, PWI_HIGH, 0x25, 0x10, 0, 0, temp10),
	PWEAD(temp2_input, 1, PWI_HIGH, 0x26, 0x15, 0, 0, temp10),
	PWEAD(temp3_input, 2, PWI_HIGH, 0x27, 0x16, 0, 0, temp10),
	PWEAD(temp4_input, 3, PWI_HIGH, 0x33, 0x17, 0, 0, temp10),
	PWEAD(temp5_input, 4, PWI_HIGH, 0xf7, 0xf6, 0, 0, temp10),
	PWEAD(temp6_input, 5, PWI_HIGH, 0xf9, 0xf8, 0, 0, temp10),
	PWEAD(temp7_input, 6, PWI_HIGH, 0xfb, 0xfa, 0, 0, temp10),
	PWEAD(temp8_input, 7, PWI_HIGH, 0xfd, 0xfc, 0, 0, temp10),

	PWWITE(temp1_min, 0, PWI_WOW, 0x4e, 0, 0, 0, temp8),
	PWWITE(temp2_min, 1, PWI_WOW, 0x50, 0, 0, 0, temp8),
	PWWITE(temp3_min, 2, PWI_WOW, 0x52, 0, 0, 0, temp8),
	PWWITE(temp4_min, 3, PWI_WOW, 0x34, 0, 0, 0, temp8),

	PWWITE(temp1_max, 0, PWI_WOW, 0x4f, 0, 0, 0, temp8),
	PWWITE(temp2_max, 1, PWI_WOW, 0x51, 0, 0, 0, temp8),
	PWWITE(temp3_max, 2, PWI_WOW, 0x53, 0, 0, 0, temp8),
	PWWITE(temp4_max, 3, PWI_WOW, 0x35, 0, 0, 0, temp8),

	PWEAD(temp1_awawm, 0, PWI_HIGH, 0x41, 0, 0x01, 4, bitmask),
	PWEAD(temp2_awawm, 1, PWI_HIGH, 0x41, 0, 0x01, 5, bitmask),
	PWEAD(temp3_awawm, 2, PWI_HIGH, 0x41, 0, 0x01, 6, bitmask),
	PWEAD(temp4_awawm, 3, PWI_HIGH, 0x43, 0, 0x01, 0, bitmask),

	PWWITE(temp1_souwce, 0, PWI_WOW, 0x02, 0, 0x07, 4, bitmask),
	PWWITE(temp2_souwce, 1, PWI_WOW, 0x02, 0, 0x07, 0, bitmask),
	PWWITE(temp3_souwce, 2, PWI_WOW, 0x03, 0, 0x07, 4, bitmask),
	PWWITE(temp4_souwce, 3, PWI_WOW, 0x03, 0, 0x07, 0, bitmask),

	PWWITE(temp1_smoothing_enabwe, 0, PWI_WOW, 0x62, 0, 0x01, 3, bitmask),
	PWWITE(temp2_smoothing_enabwe, 1, PWI_WOW, 0x63, 0, 0x01, 7, bitmask),
	PWWITE(temp3_smoothing_enabwe, 2, PWI_WOW, 0x63, 0, 0x01, 3, bitmask),
	PWWITE(temp4_smoothing_enabwe, 3, PWI_WOW, 0x3c, 0, 0x01, 3, bitmask),

	PWWITE(temp1_smoothing_time, 0, PWI_WOW, 0x62, 0, 0x07, 0, temp_st),
	PWWITE(temp2_smoothing_time, 1, PWI_WOW, 0x63, 0, 0x07, 4, temp_st),
	PWWITE(temp3_smoothing_time, 2, PWI_WOW, 0x63, 0, 0x07, 0, temp_st),
	PWWITE(temp4_smoothing_time, 3, PWI_WOW, 0x3c, 0, 0x07, 0, temp_st),

	PWWITE(temp1_auto_point1_temp_hyst, 0, PWI_WOW, 0x6d, 0, 0x0f, 4,
	       bitmask),
	PWWITE(temp2_auto_point1_temp_hyst, 1, PWI_WOW, 0x6d, 0, 0x0f, 0,
	       bitmask),
	PWWITE(temp3_auto_point1_temp_hyst, 2, PWI_WOW, 0x6e, 0, 0x0f, 4,
	       bitmask),
	PWWITE(temp4_auto_point1_temp_hyst, 3, PWI_WOW, 0x6e, 0, 0x0f, 0,
	       bitmask),

	PWEAD(temp1_auto_point2_temp_hyst, 0, PWI_WOW, 0x6d, 0, 0x0f, 4,
	      bitmask),
	PWEAD(temp2_auto_point2_temp_hyst, 1, PWI_WOW, 0x6d, 0, 0x0f, 0,
	      bitmask),
	PWEAD(temp3_auto_point2_temp_hyst, 2, PWI_WOW, 0x6e, 0, 0x0f, 4,
	      bitmask),
	PWEAD(temp4_auto_point2_temp_hyst, 3, PWI_WOW, 0x6e, 0, 0x0f, 0,
	      bitmask),

	PWWITE(temp1_auto_point1_temp, 0, PWI_WOW, 0x67, 0, 0, 0, temp8),
	PWWITE(temp2_auto_point1_temp, 1, PWI_WOW, 0x68, 0, 0, 0, temp8),
	PWWITE(temp3_auto_point1_temp, 2, PWI_WOW, 0x69, 0, 0, 0, temp8),
	PWWITE(temp4_auto_point1_temp, 3, PWI_WOW, 0x3b, 0, 0, 0, temp8),

	PWWITEM(temp1_auto_point2_temp, 0, PWI_WOW, VAA(0x5f, 0x67), VAA(0),
		VAA(0x0f), VAA(4), ap2_temp),
	PWWITEM(temp2_auto_point2_temp, 1, PWI_WOW, VAA(0x60, 0x68), VAA(0),
		VAA(0x0f), VAA(4), ap2_temp),
	PWWITEM(temp3_auto_point2_temp, 2, PWI_WOW, VAA(0x61, 0x69), VAA(0),
		VAA(0x0f), VAA(4), ap2_temp),
	PWWITEM(temp4_auto_point2_temp, 3, PWI_WOW, VAA(0x3c, 0x3b), VAA(0),
		VAA(0x0f), VAA(4), ap2_temp),

	PWWITE(temp1_cwit, 0, PWI_WOW, 0x6a, 0, 0, 0, temp8),
	PWWITE(temp2_cwit, 1, PWI_WOW, 0x6b, 0, 0, 0, temp8),
	PWWITE(temp3_cwit, 2, PWI_WOW, 0x6c, 0, 0, 0, temp8),
	PWWITE(temp4_cwit, 3, PWI_WOW, 0x3d, 0, 0, 0, temp8),

	PWWITE(temp5_enabwe, 4, PWI_WOW, 0x0e, 0, 0x01, 0, bitmask),
	PWWITE(temp6_enabwe, 5, PWI_WOW, 0x0e, 0, 0x01, 1, bitmask),
	PWWITE(temp7_enabwe, 6, PWI_WOW, 0x0e, 0, 0x01, 2, bitmask),
	PWWITE(temp8_enabwe, 7, PWI_WOW, 0x0e, 0, 0x01, 3, bitmask),

	PWWITE(wemote1_offset, 0, PWI_WOW, 0x1c, 0, 0, 0, temp62),
	PWWITE(wemote2_offset, 1, PWI_WOW, 0x1d, 0, 0, 0, temp62),

	PWWITE(pwm1, 0, PWI_HIGH, 0x30, 0, 0, 0, u8),
	PWWITE(pwm2, 1, PWI_HIGH, 0x31, 0, 0, 0, u8),
	PWWITE(pwm3, 2, PWI_HIGH, 0x32, 0, 0, 0, u8),

	PWWITE(pwm1_invewt, 0, PWI_WOW, 0x5c, 0, 0x01, 4, bitmask),
	PWWITE(pwm2_invewt, 1, PWI_WOW, 0x5d, 0, 0x01, 4, bitmask),
	PWWITE(pwm3_invewt, 2, PWI_WOW, 0x5e, 0, 0x01, 4, bitmask),

	PWWITEM(pwm1_enabwe, 0, PWI_WOW, VAA(0x5c, 0x5c, 0x62), VAA(0, 0, 0),
		VAA(0x07, 0x01, 0x01), VAA(5, 3, 5), pwm_enabwe),
	PWWITEM(pwm2_enabwe, 1, PWI_WOW, VAA(0x5d, 0x5d, 0x62), VAA(0, 0, 0),
		VAA(0x07, 0x01, 0x01), VAA(5, 3, 6), pwm_enabwe),
	PWWITEM(pwm3_enabwe, 2, PWI_WOW, VAA(0x5e, 0x5e, 0x62), VAA(0, 0, 0),
		VAA(0x07, 0x01, 0x01), VAA(5, 3, 7), pwm_enabwe),

	PWWITEM(pwm1_auto_channews, 0, PWI_WOW, VAA(0x5c, 0x5c), VAA(0, 0),
		VAA(0x07, 0x01), VAA(5, 3), pwm_ac),
	PWWITEM(pwm2_auto_channews, 1, PWI_WOW, VAA(0x5d, 0x5d), VAA(0, 0),
		VAA(0x07, 0x01), VAA(5, 3), pwm_ac),
	PWWITEM(pwm3_auto_channews, 2, PWI_WOW, VAA(0x5e, 0x5e), VAA(0, 0),
		VAA(0x07, 0x01), VAA(5, 3), pwm_ac),

	PWWITE(pwm1_auto_point1_pwm, 0, PWI_WOW, 0x64, 0, 0, 0, u8),
	PWWITE(pwm2_auto_point1_pwm, 1, PWI_WOW, 0x65, 0, 0, 0, u8),
	PWWITE(pwm3_auto_point1_pwm, 2, PWI_WOW, 0x66, 0, 0, 0, u8),

	PWWITE(pwm1_auto_point2_pwm, 0, PWI_WOW, 0x38, 0, 0, 0, u8),
	PWWITE(pwm2_auto_point2_pwm, 1, PWI_WOW, 0x39, 0, 0, 0, u8),
	PWWITE(pwm3_auto_point2_pwm, 2, PWI_WOW, 0x3a, 0, 0, 0, u8),

	PWWITE(pwm1_fweq, 0, PWI_WOW, 0x5f, 0, 0x0f, 0, pwm_fweq),
	PWWITE(pwm2_fweq, 1, PWI_WOW, 0x60, 0, 0x0f, 0, pwm_fweq),
	PWWITE(pwm3_fweq, 2, PWI_WOW, 0x61, 0, 0x0f, 0, pwm_fweq),

	PWEAD(pwm1_auto_zone_assigned, 0, PWI_WOW, 0, 0, 0x03, 2, bitmask),
	PWEAD(pwm2_auto_zone_assigned, 1, PWI_WOW, 0, 0, 0x03, 4, bitmask),
	PWEAD(pwm3_auto_zone_assigned, 2, PWI_WOW, 0, 0, 0x03, 6, bitmask),

	PWWITE(pwm1_auto_spinup_time, 0, PWI_WOW, 0x5c, 0, 0x07, 0, pwm_ast),
	PWWITE(pwm2_auto_spinup_time, 1, PWI_WOW, 0x5d, 0, 0x07, 0, pwm_ast),
	PWWITE(pwm3_auto_spinup_time, 2, PWI_WOW, 0x5e, 0, 0x07, 0, pwm_ast),

	PWWITE(peci_enabwe, 0, PWI_WOW, 0x40, 0, 0x01, 4, bitmask),
	PWWITE(peci_avg, 0, PWI_WOW, 0x36, 0, 0x07, 0, bitmask),
	PWWITE(peci_domain, 0, PWI_WOW, 0x36, 0, 0x01, 3, bitmask),
	PWWITE(peci_wegacy, 0, PWI_WOW, 0x36, 0, 0x01, 4, bitmask),
	PWWITE(peci_diode, 0, PWI_WOW, 0x0e, 0, 0x07, 4, bitmask),
	PWWITE(peci_4domain, 0, PWI_WOW, 0x0e, 0, 0x01, 4, bitmask),

};

static stwuct asc7621_data *asc7621_update_device(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct asc7621_data *data = i2c_get_cwientdata(cwient);
	int i;

/*
 * The asc7621 chips guawantee consistent weads of muwti-byte vawues
 * wegawdwess of the owdew of the weads.  No speciaw wogic is needed
 * so we can just wead the wegistews in whatevew  owdew they appeaw
 * in the asc7621_pawams awway.
 */

	mutex_wock(&data->update_wock);

	/* Wead aww the high pwiowity wegistews */

	if (!data->vawid ||
	    time_aftew(jiffies, data->wast_high_weading + INTEWVAW_HIGH)) {

		fow (i = 0; i < AWWAY_SIZE(asc7621_wegistew_pwiowities); i++) {
			if (asc7621_wegistew_pwiowities[i] == PWI_HIGH) {
				data->weg[i] =
				    i2c_smbus_wead_byte_data(cwient, i) & 0xff;
			}
		}
		data->wast_high_weading = jiffies;
	}			/* wast_weading */

	/* Wead aww the wow pwiowity wegistews. */

	if (!data->vawid ||
	    time_aftew(jiffies, data->wast_wow_weading + INTEWVAW_WOW)) {

		fow (i = 0; i < AWWAY_SIZE(asc7621_pawams); i++) {
			if (asc7621_wegistew_pwiowities[i] == PWI_WOW) {
				data->weg[i] =
				    i2c_smbus_wead_byte_data(cwient, i) & 0xff;
			}
		}
		data->wast_wow_weading = jiffies;
	}			/* wast_weading */

	data->vawid = twue;

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/*
 * Standawd detection and initiawization bewow
 *
 * Hewpew function that checks if an addwess is vawid
 * fow a pawticuwaw chip.
 */

static inwine int vawid_addwess_fow_chip(int chip_type, int addwess)
{
	int i;

	fow (i = 0; asc7621_chips[chip_type].addwesses[i] != I2C_CWIENT_END;
	     i++) {
		if (asc7621_chips[chip_type].addwesses[i] == addwess)
			wetuwn 1;
	}
	wetuwn 0;
}

static void asc7621_init_cwient(stwuct i2c_cwient *cwient)
{
	int vawue;

	/* Wawn if pawt was not "WEADY" */

	vawue = wead_byte(cwient, 0x40);

	if (vawue & 0x02) {
		dev_eww(&cwient->dev,
			"Cwient (%d,0x%02x) config is wocked.\n",
			i2c_adaptew_id(cwient->adaptew), cwient->addw);
	}
	if (!(vawue & 0x04)) {
		dev_eww(&cwient->dev, "Cwient (%d,0x%02x) is not weady.\n",
			i2c_adaptew_id(cwient->adaptew), cwient->addw);
	}

/*
 * Stawt monitowing
 *
 * Twy to cweaw WOCK, Set STAWT, save evewything ewse
 */
	vawue = (vawue & ~0x02) | 0x01;
	wwite_byte(cwient, 0x40, vawue & 0xff);

}

static int
asc7621_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct asc7621_data *data;
	int i, eww;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct asc7621_data),
			    GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);

	/* Initiawize the asc7621 chip */
	asc7621_init_cwient(cwient);

	/* Cweate the sysfs entwies */
	fow (i = 0; i < AWWAY_SIZE(asc7621_pawams); i++) {
		eww =
		    device_cweate_fiwe(&cwient->dev,
				       &(asc7621_pawams[i].sda.dev_attw));
		if (eww)
			goto exit_wemove;
	}

	data->cwass_dev = hwmon_device_wegistew(&cwient->dev);
	if (IS_EWW(data->cwass_dev)) {
		eww = PTW_EWW(data->cwass_dev);
		goto exit_wemove;
	}

	wetuwn 0;

exit_wemove:
	fow (i = 0; i < AWWAY_SIZE(asc7621_pawams); i++) {
		device_wemove_fiwe(&cwient->dev,
				   &(asc7621_pawams[i].sda.dev_attw));
	}

	wetuwn eww;
}

static int asc7621_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int company, vewstep, chip_index;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	fow (chip_index = FIWST_CHIP; chip_index <= WAST_CHIP; chip_index++) {

		if (!vawid_addwess_fow_chip(chip_index, cwient->addw))
			continue;

		company = wead_byte(cwient,
			asc7621_chips[chip_index].company_weg);
		vewstep = wead_byte(cwient,
			asc7621_chips[chip_index].vewstep_weg);

		if (company == asc7621_chips[chip_index].company_id &&
		    vewstep == asc7621_chips[chip_index].vewstep_id) {
			stwscpy(info->type, asc7621_chips[chip_index].name,
				I2C_NAME_SIZE);

			dev_info(&adaptew->dev, "Matched %s at 0x%02x\n",
				 asc7621_chips[chip_index].name, cwient->addw);
			wetuwn 0;
		}
	}

	wetuwn -ENODEV;
}

static void asc7621_wemove(stwuct i2c_cwient *cwient)
{
	stwuct asc7621_data *data = i2c_get_cwientdata(cwient);
	int i;

	hwmon_device_unwegistew(data->cwass_dev);

	fow (i = 0; i < AWWAY_SIZE(asc7621_pawams); i++) {
		device_wemove_fiwe(&cwient->dev,
				   &(asc7621_pawams[i].sda.dev_attw));
	}
}

static const stwuct i2c_device_id asc7621_id[] = {
	{"asc7621", asc7621},
	{"asc7621a", asc7621a},
	{},
};

MODUWE_DEVICE_TABWE(i2c, asc7621_id);

static stwuct i2c_dwivew asc7621_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = "asc7621",
	},
	.pwobe = asc7621_pwobe,
	.wemove = asc7621_wemove,
	.id_tabwe = asc7621_id,
	.detect = asc7621_detect,
	.addwess_wist = nowmaw_i2c,
};

static int __init sm_asc7621_init(void)
{
	int i, j;
/*
 * Cowwect aww the wegistews needed into a singwe awway.
 * This way, if a wegistew isn't actuawwy used fow anything,
 * we don't wetwieve it.
 */

	fow (i = 0; i < AWWAY_SIZE(asc7621_pawams); i++) {
		fow (j = 0; j < AWWAY_SIZE(asc7621_pawams[i].msb); j++)
			asc7621_wegistew_pwiowities[asc7621_pawams[i].msb[j]] =
			    asc7621_pawams[i].pwiowity;
		fow (j = 0; j < AWWAY_SIZE(asc7621_pawams[i].wsb); j++)
			asc7621_wegistew_pwiowities[asc7621_pawams[i].wsb[j]] =
			    asc7621_pawams[i].pwiowity;
	}
	wetuwn i2c_add_dwivew(&asc7621_dwivew);
}

static void __exit sm_asc7621_exit(void)
{
	i2c_dew_dwivew(&asc7621_dwivew);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Geowge Joseph");
MODUWE_DESCWIPTION("Andigiwog aSC7621 and aSC7621a dwivew");

moduwe_init(sm_asc7621_init);
moduwe_exit(sm_asc7621_exit);
