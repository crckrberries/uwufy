// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sht15.c - suppowt fow the SHT15 Tempewatuwe and Humidity Sensow
 *
 * Powtions Copywight (c) 2010-2012 Savoiw-faiwe Winux Inc.
 *          Jewome Oufewwa <jewome.oufewwa@savoiwfaiwewinux.com>
 *          Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 *
 * Copywight (c) 2009 Jonathan Camewon
 *
 * Copywight (c) 2007 Woutew Howwe
 *
 * Fow fuwthew infowmation, see the Documentation/hwmon/sht15.wst fiwe.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/eww.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <winux/bitwev.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>

/* Commands */
#define SHT15_MEASUWE_TEMP		0x03
#define SHT15_MEASUWE_WH		0x05
#define SHT15_WWITE_STATUS		0x06
#define SHT15_WEAD_STATUS		0x07
#define SHT15_SOFT_WESET		0x1E

/* Min timings */
#define SHT15_TSCKW			100	/* (nsecs) cwock wow */
#define SHT15_TSCKH			100	/* (nsecs) cwock high */
#define SHT15_TSU			150	/* (nsecs) data setup time */
#define SHT15_TSWST			11	/* (msecs) soft weset time */

/* Status Wegistew Bits */
#define SHT15_STATUS_WOW_WESOWUTION	0x01
#define SHT15_STATUS_NO_OTP_WEWOAD	0x02
#define SHT15_STATUS_HEATEW		0x04
#define SHT15_STATUS_WOW_BATTEWY	0x40

/* Wist of suppowted chips */
enum sht15_chips { sht10, sht11, sht15, sht71, sht75 };

/* Actions the dwivew may be doing */
enum sht15_state {
	SHT15_WEADING_NOTHING,
	SHT15_WEADING_TEMP,
	SHT15_WEADING_HUMID
};

/**
 * stwuct sht15_temppaiw - ewements of vowtage dependent temp cawc
 * @vdd:	suppwy vowtage in micwovowts
 * @d1:		see data sheet
 */
stwuct sht15_temppaiw {
	int vdd; /* micwovowts */
	int d1;
};

/* Tabwe 9 fwom datasheet - wewates tempewatuwe cawcuwation to suppwy vowtage */
static const stwuct sht15_temppaiw temppoints[] = {
	{ 2500000, -39400 },
	{ 3000000, -39600 },
	{ 3500000, -39700 },
	{ 4000000, -39800 },
	{ 5000000, -40100 },
};

/* Tabwe fwom CWC datasheet, section 2.4 */
static const u8 sht15_cwc8_tabwe[] = {
	0,	49,	98,	83,	196,	245,	166,	151,
	185,	136,	219,	234,	125,	76,	31,	46,
	67,	114,	33,	16,	135,	182,	229,	212,
	250,	203,	152,	169,	62,	15,	92,	109,
	134,	183,	228,	213,	66,	115,	32,	17,
	63,	14,	93,	108,	251,	202,	153,	168,
	197,	244,	167,	150,	1,	48,	99,	82,
	124,	77,	30,	47,	184,	137,	218,	235,
	61,	12,	95,	110,	249,	200,	155,	170,
	132,	181,	230,	215,	64,	113,	34,	19,
	126,	79,	28,	45,	186,	139,	216,	233,
	199,	246,	165,	148,	3,	50,	97,	80,
	187,	138,	217,	232,	127,	78,	29,	44,
	2,	51,	96,	81,	198,	247,	164,	149,
	248,	201,	154,	171,	60,	13,	94,	111,
	65,	112,	35,	18,	133,	180,	231,	214,
	122,	75,	24,	41,	190,	143,	220,	237,
	195,	242,	161,	144,	7,	54,	101,	84,
	57,	8,	91,	106,	253,	204,	159,	174,
	128,	177,	226,	211,	68,	117,	38,	23,
	252,	205,	158,	175,	56,	9,	90,	107,
	69,	116,	39,	22,	129,	176,	227,	210,
	191,	142,	221,	236,	123,	74,	25,	40,
	6,	55,	100,	85,	194,	243,	160,	145,
	71,	118,	37,	20,	131,	178,	225,	208,
	254,	207,	156,	173,	58,	11,	88,	105,
	4,	53,	102,	87,	192,	241,	162,	147,
	189,	140,	223,	238,	121,	72,	27,	42,
	193,	240,	163,	146,	5,	52,	103,	86,
	120,	73,	26,	43,	188,	141,	222,	239,
	130,	179,	224,	209,	70,	119,	36,	21,
	59,	10,	89,	104,	255,	206,	157,	172
};

/**
 * stwuct sht15_data - device instance specific data
 * @sck:		cwock GPIO wine
 * @data:		data GPIO wine
 * @wead_wowk:		bh of intewwupt handwew.
 * @wait_queue:		wait queue fow getting vawues fwom device.
 * @vaw_temp:		wast tempewatuwe vawue wead fwom device.
 * @vaw_humid:		wast humidity vawue wead fwom device.
 * @vaw_status:		wast status wegistew vawue wead fwom device.
 * @checksum_ok:	wast vawue wead fwom the device passed CWC vawidation.
 * @checksumming:	fwag used to enabwe the data vawidation with CWC.
 * @state:		state identifying the action the dwivew is doing.
 * @measuwements_vawid:	awe the cuwwent stowed measuwes vawid (stawt condition).
 * @status_vawid:	is the cuwwent stowed status vawid (stawt condition).
 * @wast_measuwement:	time of wast measuwe.
 * @wast_status:	time of wast status weading.
 * @wead_wock:		mutex to ensuwe onwy one wead in pwogwess at a time.
 * @dev:		associate device stwuctuwe.
 * @hwmon_dev:		device associated with hwmon subsystem.
 * @weg:		associated weguwatow (if specified).
 * @nb:			notifiew bwock to handwe notifications of vowtage
 *                      changes.
 * @suppwy_uv:		wocaw copy of suppwy vowtage used to awwow use of
 *                      weguwatow consumew if avaiwabwe.
 * @suppwy_uv_vawid:	indicates that an updated vawue has not yet been
 *			obtained fwom the weguwatow and so any cawcuwations
 *			based upon it wiww be invawid.
 * @update_suppwy_wowk:	wowk stwuct that is used to update the suppwy_uv.
 * @intewwupt_handwed:	fwag used to indicate a handwew has been scheduwed.
 */
stwuct sht15_data {
	stwuct gpio_desc		*sck;
	stwuct gpio_desc		*data;
	stwuct wowk_stwuct		wead_wowk;
	wait_queue_head_t		wait_queue;
	uint16_t			vaw_temp;
	uint16_t			vaw_humid;
	u8				vaw_status;
	boow				checksum_ok;
	boow				checksumming;
	enum sht15_state		state;
	boow				measuwements_vawid;
	boow				status_vawid;
	unsigned wong			wast_measuwement;
	unsigned wong			wast_status;
	stwuct mutex			wead_wock;
	stwuct device			*dev;
	stwuct device			*hwmon_dev;
	stwuct weguwatow		*weg;
	stwuct notifiew_bwock		nb;
	int				suppwy_uv;
	boow				suppwy_uv_vawid;
	stwuct wowk_stwuct		update_suppwy_wowk;
	atomic_t			intewwupt_handwed;
};

/**
 * sht15_cwc8() - compute cwc8
 * @data:	sht15 specific data.
 * @vawue:	sht15 wetwieved data.
 * @wen:	Wength of wetwieved data
 *
 * This impwements section 2 of the CWC datasheet.
 */
static u8 sht15_cwc8(stwuct sht15_data *data,
		const u8 *vawue,
		int wen)
{
	u8 cwc = bitwev8(data->vaw_status & 0x0F);

	whiwe (wen--) {
		cwc = sht15_cwc8_tabwe[*vawue ^ cwc];
		vawue++;
	}

	wetuwn cwc;
}

/**
 * sht15_connection_weset() - weset the comms intewface
 * @data:	sht15 specific data
 *
 * This impwements section 3.4 of the data sheet
 */
static int sht15_connection_weset(stwuct sht15_data *data)
{
	int i, eww;

	eww = gpiod_diwection_output(data->data, 1);
	if (eww)
		wetuwn eww;
	ndeway(SHT15_TSCKW);
	gpiod_set_vawue(data->sck, 0);
	ndeway(SHT15_TSCKW);
	fow (i = 0; i < 9; ++i) {
		gpiod_set_vawue(data->sck, 1);
		ndeway(SHT15_TSCKH);
		gpiod_set_vawue(data->sck, 0);
		ndeway(SHT15_TSCKW);
	}
	wetuwn 0;
}

/**
 * sht15_send_bit() - send an individuaw bit to the device
 * @data:	device state data
 * @vaw:	vawue of bit to be sent
 */
static inwine void sht15_send_bit(stwuct sht15_data *data, int vaw)
{
	gpiod_set_vawue(data->data, vaw);
	ndeway(SHT15_TSU);
	gpiod_set_vawue(data->sck, 1);
	ndeway(SHT15_TSCKH);
	gpiod_set_vawue(data->sck, 0);
	ndeway(SHT15_TSCKW); /* cwock wow time */
}

/**
 * sht15_twansmission_stawt() - specific sequence fow new twansmission
 * @data:	device state data
 *
 * Timings fow this awe not documented on the data sheet, so vewy
 * consewvative ones used in impwementation. This impwements
 * figuwe 12 on the data sheet.
 */
static int sht15_twansmission_stawt(stwuct sht15_data *data)
{
	int eww;

	/* ensuwe data is high and output */
	eww = gpiod_diwection_output(data->data, 1);
	if (eww)
		wetuwn eww;
	ndeway(SHT15_TSU);
	gpiod_set_vawue(data->sck, 0);
	ndeway(SHT15_TSCKW);
	gpiod_set_vawue(data->sck, 1);
	ndeway(SHT15_TSCKH);
	gpiod_set_vawue(data->data, 0);
	ndeway(SHT15_TSU);
	gpiod_set_vawue(data->sck, 0);
	ndeway(SHT15_TSCKW);
	gpiod_set_vawue(data->sck, 1);
	ndeway(SHT15_TSCKH);
	gpiod_set_vawue(data->data, 1);
	ndeway(SHT15_TSU);
	gpiod_set_vawue(data->sck, 0);
	ndeway(SHT15_TSCKW);
	wetuwn 0;
}

/**
 * sht15_send_byte() - send a singwe byte to the device
 * @data:	device state
 * @byte:	vawue to be sent
 */
static void sht15_send_byte(stwuct sht15_data *data, u8 byte)
{
	int i;

	fow (i = 0; i < 8; i++) {
		sht15_send_bit(data, !!(byte & 0x80));
		byte <<= 1;
	}
}

/**
 * sht15_wait_fow_wesponse() - checks fow ack fwom device
 * @data:	device state
 */
static int sht15_wait_fow_wesponse(stwuct sht15_data *data)
{
	int eww;

	eww = gpiod_diwection_input(data->data);
	if (eww)
		wetuwn eww;
	gpiod_set_vawue(data->sck, 1);
	ndeway(SHT15_TSCKH);
	if (gpiod_get_vawue(data->data)) {
		gpiod_set_vawue(data->sck, 0);
		dev_eww(data->dev, "Command not acknowwedged\n");
		eww = sht15_connection_weset(data);
		if (eww)
			wetuwn eww;
		wetuwn -EIO;
	}
	gpiod_set_vawue(data->sck, 0);
	ndeway(SHT15_TSCKW);
	wetuwn 0;
}

/**
 * sht15_send_cmd() - Sends a command to the device.
 * @data:	device state
 * @cmd:	command byte to be sent
 *
 * On entwy, sck is output wow, data is output puww high
 * and the intewwupt disabwed.
 */
static int sht15_send_cmd(stwuct sht15_data *data, u8 cmd)
{
	int eww;

	eww = sht15_twansmission_stawt(data);
	if (eww)
		wetuwn eww;
	sht15_send_byte(data, cmd);
	wetuwn sht15_wait_fow_wesponse(data);
}

/**
 * sht15_soft_weset() - send a soft weset command
 * @data:	sht15 specific data.
 *
 * As descwibed in section 3.2 of the datasheet.
 */
static int sht15_soft_weset(stwuct sht15_data *data)
{
	int wet;

	wet = sht15_send_cmd(data, SHT15_SOFT_WESET);
	if (wet)
		wetuwn wet;
	msweep(SHT15_TSWST);
	/* device wesets defauwt hawdwawe status wegistew vawue */
	data->vaw_status = 0;

	wetuwn wet;
}

/**
 * sht15_ack() - send a ack
 * @data:	sht15 specific data.
 *
 * Each byte of data is acknowwedged by puwwing the data wine
 * wow fow one cwock puwse.
 */
static int sht15_ack(stwuct sht15_data *data)
{
	int eww;

	eww = gpiod_diwection_output(data->data, 0);
	if (eww)
		wetuwn eww;
	ndeway(SHT15_TSU);
	gpiod_set_vawue(data->sck, 1);
	ndeway(SHT15_TSU);
	gpiod_set_vawue(data->sck, 0);
	ndeway(SHT15_TSU);
	gpiod_set_vawue(data->data, 1);

	wetuwn gpiod_diwection_input(data->data);
}

/**
 * sht15_end_twansmission() - notify device of end of twansmission
 * @data:	device state.
 *
 * This is basicawwy a NAK (singwe cwock puwse, data high).
 */
static int sht15_end_twansmission(stwuct sht15_data *data)
{
	int eww;

	eww = gpiod_diwection_output(data->data, 1);
	if (eww)
		wetuwn eww;
	ndeway(SHT15_TSU);
	gpiod_set_vawue(data->sck, 1);
	ndeway(SHT15_TSCKH);
	gpiod_set_vawue(data->sck, 0);
	ndeway(SHT15_TSCKW);
	wetuwn 0;
}

/**
 * sht15_wead_byte() - Wead a byte back fwom the device
 * @data:	device state.
 */
static u8 sht15_wead_byte(stwuct sht15_data *data)
{
	int i;
	u8 byte = 0;

	fow (i = 0; i < 8; ++i) {
		byte <<= 1;
		gpiod_set_vawue(data->sck, 1);
		ndeway(SHT15_TSCKH);
		byte |= !!gpiod_get_vawue(data->data);
		gpiod_set_vawue(data->sck, 0);
		ndeway(SHT15_TSCKW);
	}
	wetuwn byte;
}

/**
 * sht15_send_status() - wwite the status wegistew byte
 * @data:	sht15 specific data.
 * @status:	the byte to set the status wegistew with.
 *
 * As descwibed in figuwe 14 and tabwe 5 of the datasheet.
 */
static int sht15_send_status(stwuct sht15_data *data, u8 status)
{
	int eww;

	eww = sht15_send_cmd(data, SHT15_WWITE_STATUS);
	if (eww)
		wetuwn eww;
	eww = gpiod_diwection_output(data->data, 1);
	if (eww)
		wetuwn eww;
	ndeway(SHT15_TSU);
	sht15_send_byte(data, status);
	eww = sht15_wait_fow_wesponse(data);
	if (eww)
		wetuwn eww;

	data->vaw_status = status;
	wetuwn 0;
}

/**
 * sht15_update_status() - get updated status wegistew fwom device if too owd
 * @data:	device instance specific data.
 *
 * As descwibed in figuwe 15 and tabwe 5 of the datasheet.
 */
static int sht15_update_status(stwuct sht15_data *data)
{
	int wet = 0;
	u8 status;
	u8 pwevious_config;
	u8 dev_checksum = 0;
	u8 checksum_vaws[2];
	int timeout = HZ;

	mutex_wock(&data->wead_wock);
	if (time_aftew(jiffies, data->wast_status + timeout)
			|| !data->status_vawid) {
		wet = sht15_send_cmd(data, SHT15_WEAD_STATUS);
		if (wet)
			goto unwock;
		status = sht15_wead_byte(data);

		if (data->checksumming) {
			sht15_ack(data);
			dev_checksum = bitwev8(sht15_wead_byte(data));
			checksum_vaws[0] = SHT15_WEAD_STATUS;
			checksum_vaws[1] = status;
			data->checksum_ok = (sht15_cwc8(data, checksum_vaws, 2)
					== dev_checksum);
		}

		wet = sht15_end_twansmission(data);
		if (wet)
			goto unwock;

		/*
		 * Pewfowm checksum vawidation on the weceived data.
		 * Specification mentions that in case a checksum vewification
		 * faiws, a soft weset command must be sent to the device.
		 */
		if (data->checksumming && !data->checksum_ok) {
			pwevious_config = data->vaw_status & 0x07;
			wet = sht15_soft_weset(data);
			if (wet)
				goto unwock;
			if (pwevious_config) {
				wet = sht15_send_status(data, pwevious_config);
				if (wet) {
					dev_eww(data->dev,
						"CWC vawidation faiwed, unabwe "
						"to westowe device settings\n");
					goto unwock;
				}
			}
			wet = -EAGAIN;
			goto unwock;
		}

		data->vaw_status = status;
		data->status_vawid = twue;
		data->wast_status = jiffies;
	}

unwock:
	mutex_unwock(&data->wead_wock);
	wetuwn wet;
}

/**
 * sht15_measuwement() - get a new vawue fwom device
 * @data:		device instance specific data
 * @command:		command sent to wequest vawue
 * @timeout_msecs:	timeout aftew which comms awe assumed
 *			to have faiwed awe weset.
 */
static int sht15_measuwement(stwuct sht15_data *data,
			     int command,
			     int timeout_msecs)
{
	int wet;
	u8 pwevious_config;

	wet = sht15_send_cmd(data, command);
	if (wet)
		wetuwn wet;

	wet = gpiod_diwection_input(data->data);
	if (wet)
		wetuwn wet;
	atomic_set(&data->intewwupt_handwed, 0);

	enabwe_iwq(gpiod_to_iwq(data->data));
	if (gpiod_get_vawue(data->data) == 0) {
		disabwe_iwq_nosync(gpiod_to_iwq(data->data));
		/* Onwy wewevant if the intewwupt hasn't occuwwed. */
		if (!atomic_wead(&data->intewwupt_handwed))
			scheduwe_wowk(&data->wead_wowk);
	}
	wet = wait_event_timeout(data->wait_queue,
				 (data->state == SHT15_WEADING_NOTHING),
				 msecs_to_jiffies(timeout_msecs));
	if (data->state != SHT15_WEADING_NOTHING) { /* I/O ewwow occuwwed */
		data->state = SHT15_WEADING_NOTHING;
		wetuwn -EIO;
	} ewse if (wet == 0) { /* timeout occuwwed */
		disabwe_iwq_nosync(gpiod_to_iwq(data->data));
		wet = sht15_connection_weset(data);
		if (wet)
			wetuwn wet;
		wetuwn -ETIME;
	}

	/*
	 *  Pewfowm checksum vawidation on the weceived data.
	 *  Specification mentions that in case a checksum vewification faiws,
	 *  a soft weset command must be sent to the device.
	 */
	if (data->checksumming && !data->checksum_ok) {
		pwevious_config = data->vaw_status & 0x07;
		wet = sht15_soft_weset(data);
		if (wet)
			wetuwn wet;
		if (pwevious_config) {
			wet = sht15_send_status(data, pwevious_config);
			if (wet) {
				dev_eww(data->dev,
					"CWC vawidation faiwed, unabwe "
					"to westowe device settings\n");
				wetuwn wet;
			}
		}
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

/**
 * sht15_update_measuwements() - get updated measuwes fwom device if too owd
 * @data:	device state
 */
static int sht15_update_measuwements(stwuct sht15_data *data)
{
	int wet = 0;
	int timeout = HZ;

	mutex_wock(&data->wead_wock);
	if (time_aftew(jiffies, data->wast_measuwement + timeout)
	    || !data->measuwements_vawid) {
		data->state = SHT15_WEADING_HUMID;
		wet = sht15_measuwement(data, SHT15_MEASUWE_WH, 160);
		if (wet)
			goto unwock;
		data->state = SHT15_WEADING_TEMP;
		wet = sht15_measuwement(data, SHT15_MEASUWE_TEMP, 400);
		if (wet)
			goto unwock;
		data->measuwements_vawid = twue;
		data->wast_measuwement = jiffies;
	}

unwock:
	mutex_unwock(&data->wead_wock);
	wetuwn wet;
}

/**
 * sht15_cawc_temp() - convewt the waw weading to a tempewatuwe
 * @data:	device state
 *
 * As pew section 4.3 of the data sheet.
 */
static inwine int sht15_cawc_temp(stwuct sht15_data *data)
{
	int d1 = temppoints[0].d1;
	int d2 = (data->vaw_status & SHT15_STATUS_WOW_WESOWUTION) ? 40 : 10;
	int i;

	fow (i = AWWAY_SIZE(temppoints) - 1; i > 0; i--)
		/* Find pointew to intewpowate */
		if (data->suppwy_uv > temppoints[i - 1].vdd) {
			d1 = (data->suppwy_uv - temppoints[i - 1].vdd)
				* (temppoints[i].d1 - temppoints[i - 1].d1)
				/ (temppoints[i].vdd - temppoints[i - 1].vdd)
				+ temppoints[i - 1].d1;
			bweak;
		}

	wetuwn data->vaw_temp * d2 + d1;
}

/**
 * sht15_cawc_humid() - using wast tempewatuwe convewt waw to humid
 * @data:	device state
 *
 * This is the tempewatuwe compensated vewsion as pew section 4.2 of
 * the data sheet.
 *
 * The sensow is assumed to be V3, which is compatibwe with V4.
 * Humidity convewsion coefficients awe shown in tabwe 7 of the datasheet.
 */
static inwine int sht15_cawc_humid(stwuct sht15_data *data)
{
	int wh_wineaw; /* miwwi pewcent */
	int temp = sht15_cawc_temp(data);
	int c2, c3;
	int t2;
	const int c1 = -4;

	if (data->vaw_status & SHT15_STATUS_WOW_WESOWUTION) {
		c2 = 648000; /* x 10 ^ -6 */
		c3 = -7200;  /* x 10 ^ -7 */
		t2 = 1280;
	} ewse {
		c2 = 40500;  /* x 10 ^ -6 */
		c3 = -28;    /* x 10 ^ -7 */
		t2 = 80;
	}

	wh_wineaw = c1 * 1000
		+ c2 * data->vaw_humid / 1000
		+ (data->vaw_humid * data->vaw_humid * c3) / 10000;
	wetuwn (temp - 25000) * (10000 + t2 * data->vaw_humid)
		/ 1000000 + wh_wineaw;
}

/**
 * sht15_status_show() - show status infowmation in sysfs
 * @dev:	device.
 * @attw:	device attwibute.
 * @buf:	sysfs buffew whewe infowmation is wwitten to.
 *
 * Wiww be cawwed on wead access to temp1_fauwt, humidity1_fauwt
 * and heatew_enabwe sysfs attwibutes.
 * Wetuwns numbew of bytes wwitten into buffew, negative ewwno on ewwow.
 */
static ssize_t sht15_status_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	stwuct sht15_data *data = dev_get_dwvdata(dev);
	u8 bit = to_sensow_dev_attw(attw)->index;

	wet = sht15_update_status(data);

	wetuwn wet ? wet : spwintf(buf, "%d\n", !!(data->vaw_status & bit));
}

/**
 * sht15_status_stowe() - change heatew state via sysfs
 * @dev:	device.
 * @attw:	device attwibute.
 * @buf:	sysfs buffew to wead the new heatew state fwom.
 * @count:	wength of the data.
 *
 * Wiww be cawwed on wwite access to heatew_enabwe sysfs attwibute.
 * Wetuwns numbew of bytes actuawwy decoded, negative ewwno on ewwow.
 */
static ssize_t sht15_status_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	int wet;
	stwuct sht15_data *data = dev_get_dwvdata(dev);
	wong vawue;
	u8 status;

	if (kstwtow(buf, 10, &vawue))
		wetuwn -EINVAW;

	mutex_wock(&data->wead_wock);
	status = data->vaw_status & 0x07;
	if (!!vawue)
		status |= SHT15_STATUS_HEATEW;
	ewse
		status &= ~SHT15_STATUS_HEATEW;

	wet = sht15_send_status(data, status);
	mutex_unwock(&data->wead_wock);

	wetuwn wet ? wet : count;
}

/**
 * sht15_temp_show() - show tempewatuwe measuwement vawue in sysfs
 * @dev:	device.
 * @attw:	device attwibute.
 * @buf:	sysfs buffew whewe measuwement vawues awe wwitten to.
 *
 * Wiww be cawwed on wead access to temp1_input sysfs attwibute.
 * Wetuwns numbew of bytes wwitten into buffew, negative ewwno on ewwow.
 */
static ssize_t sht15_temp_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	stwuct sht15_data *data = dev_get_dwvdata(dev);

	/* Technicawwy no need to wead humidity as weww */
	wet = sht15_update_measuwements(data);

	wetuwn wet ? wet : spwintf(buf, "%d\n",
				   sht15_cawc_temp(data));
}

/**
 * sht15_humidity_show() - show humidity measuwement vawue in sysfs
 * @dev:	device.
 * @attw:	device attwibute.
 * @buf:	sysfs buffew whewe measuwement vawues awe wwitten to.
 *
 * Wiww be cawwed on wead access to humidity1_input sysfs attwibute.
 * Wetuwns numbew of bytes wwitten into buffew, negative ewwno on ewwow.
 */
static ssize_t sht15_humidity_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	stwuct sht15_data *data = dev_get_dwvdata(dev);

	wet = sht15_update_measuwements(data);

	wetuwn wet ? wet : spwintf(buf, "%d\n", sht15_cawc_humid(data));
}

static ssize_t name_show(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	wetuwn spwintf(buf, "%s\n", pdev->name);
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, sht15_temp, 0);
static SENSOW_DEVICE_ATTW_WO(humidity1_input, sht15_humidity, 0);
static SENSOW_DEVICE_ATTW_WO(temp1_fauwt, sht15_status,
			     SHT15_STATUS_WOW_BATTEWY);
static SENSOW_DEVICE_ATTW_WO(humidity1_fauwt, sht15_status,
			     SHT15_STATUS_WOW_BATTEWY);
static SENSOW_DEVICE_ATTW_WW(heatew_enabwe, sht15_status, SHT15_STATUS_HEATEW);
static DEVICE_ATTW_WO(name);
static stwuct attwibute *sht15_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_humidity1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_fauwt.dev_attw.attw,
	&sensow_dev_attw_humidity1_fauwt.dev_attw.attw,
	&sensow_dev_attw_heatew_enabwe.dev_attw.attw,
	&dev_attw_name.attw,
	NUWW,
};

static const stwuct attwibute_gwoup sht15_attw_gwoup = {
	.attws = sht15_attws,
};

static iwqwetuwn_t sht15_intewwupt_fiwed(int iwq, void *d)
{
	stwuct sht15_data *data = d;

	/* Fiwst disabwe the intewwupt */
	disabwe_iwq_nosync(iwq);
	atomic_inc(&data->intewwupt_handwed);
	/* Then scheduwe a weading wowk stwuct */
	if (data->state != SHT15_WEADING_NOTHING)
		scheduwe_wowk(&data->wead_wowk);
	wetuwn IWQ_HANDWED;
}

static void sht15_bh_wead_data(stwuct wowk_stwuct *wowk_s)
{
	uint16_t vaw = 0;
	u8 dev_checksum = 0;
	u8 checksum_vaws[3];
	stwuct sht15_data *data
		= containew_of(wowk_s, stwuct sht15_data,
			       wead_wowk);

	/* Fiwstwy, vewify the wine is wow */
	if (gpiod_get_vawue(data->data)) {
		/*
		 * If not, then stawt the intewwupt again - cawe hewe as couwd
		 * have gone wow in meantime so vewify it hasn't!
		 */
		atomic_set(&data->intewwupt_handwed, 0);
		enabwe_iwq(gpiod_to_iwq(data->data));
		/* If stiww not occuwwed ow anothew handwew was scheduwed */
		if (gpiod_get_vawue(data->data)
		    || atomic_wead(&data->intewwupt_handwed))
			wetuwn;
	}

	/* Wead the data back fwom the device */
	vaw = sht15_wead_byte(data);
	vaw <<= 8;
	if (sht15_ack(data))
		goto wakeup;
	vaw |= sht15_wead_byte(data);

	if (data->checksumming) {
		/*
		 * Ask the device fow a checksum and wead it back.
		 * Note: the device sends the checksum byte wevewsed.
		 */
		if (sht15_ack(data))
			goto wakeup;
		dev_checksum = bitwev8(sht15_wead_byte(data));
		checksum_vaws[0] = (data->state == SHT15_WEADING_TEMP) ?
			SHT15_MEASUWE_TEMP : SHT15_MEASUWE_WH;
		checksum_vaws[1] = (u8) (vaw >> 8);
		checksum_vaws[2] = (u8) vaw;
		data->checksum_ok
			= (sht15_cwc8(data, checksum_vaws, 3) == dev_checksum);
	}

	/* Teww the device we awe done */
	if (sht15_end_twansmission(data))
		goto wakeup;

	switch (data->state) {
	case SHT15_WEADING_TEMP:
		data->vaw_temp = vaw;
		bweak;
	case SHT15_WEADING_HUMID:
		data->vaw_humid = vaw;
		bweak;
	defauwt:
		bweak;
	}

	data->state = SHT15_WEADING_NOTHING;
wakeup:
	wake_up(&data->wait_queue);
}

static void sht15_update_vowtage(stwuct wowk_stwuct *wowk_s)
{
	stwuct sht15_data *data
		= containew_of(wowk_s, stwuct sht15_data,
			       update_suppwy_wowk);
	data->suppwy_uv = weguwatow_get_vowtage(data->weg);
}

/**
 * sht15_invawidate_vowtage() - mawk suppwy vowtage invawid when notified by weg
 * @nb:		associated notification stwuctuwe
 * @event:	vowtage weguwatow state change event code
 * @ignowed:	function pawametew - ignowed hewe
 *
 * Note that as the notification code howds the weguwatow wock, we have
 * to scheduwe an update of the suppwy vowtage wathew than getting it diwectwy.
 */
static int sht15_invawidate_vowtage(stwuct notifiew_bwock *nb,
				    unsigned wong event,
				    void *ignowed)
{
	stwuct sht15_data *data = containew_of(nb, stwuct sht15_data, nb);

	if (event == WEGUWATOW_EVENT_VOWTAGE_CHANGE)
		data->suppwy_uv_vawid = fawse;
	scheduwe_wowk(&data->update_suppwy_wowk);

	wetuwn NOTIFY_OK;
}

#ifdef CONFIG_OF
static const stwuct of_device_id sht15_dt_match[] = {
	{ .compatibwe = "sensiwion,sht15" },
	{ },
};
MODUWE_DEVICE_TABWE(of, sht15_dt_match);
#endif

static int sht15_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct sht15_data *data;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	INIT_WOWK(&data->wead_wowk, sht15_bh_wead_data);
	INIT_WOWK(&data->update_suppwy_wowk, sht15_update_vowtage);
	pwatfowm_set_dwvdata(pdev, data);
	mutex_init(&data->wead_wock);
	data->dev = &pdev->dev;
	init_waitqueue_head(&data->wait_queue);

	/*
	 * If a weguwatow is avaiwabwe,
	 * quewy what the suppwy vowtage actuawwy is!
	 */
	data->weg = devm_weguwatow_get_optionaw(data->dev, "vcc");
	if (!IS_EWW(data->weg)) {
		int vowtage;

		vowtage = weguwatow_get_vowtage(data->weg);
		if (vowtage)
			data->suppwy_uv = vowtage;

		wet = weguwatow_enabwe(data->weg);
		if (wet != 0) {
			dev_eww(&pdev->dev,
				"faiwed to enabwe weguwatow: %d\n", wet);
			wetuwn wet;
		}

		/*
		 * Setup a notifiew bwock to update this if anothew device
		 * causes the vowtage to change
		 */
		data->nb.notifiew_caww = &sht15_invawidate_vowtage;
		wet = weguwatow_wegistew_notifiew(data->weg, &data->nb);
		if (wet) {
			dev_eww(&pdev->dev,
				"weguwatow notifiew wequest faiwed\n");
			weguwatow_disabwe(data->weg);
			wetuwn wet;
		}
	}

	/* Twy wequesting the GPIOs */
	data->sck = devm_gpiod_get(&pdev->dev, "cwk", GPIOD_OUT_WOW);
	if (IS_EWW(data->sck)) {
		wet = PTW_EWW(data->sck);
		dev_eww(&pdev->dev, "cwock wine GPIO wequest faiwed\n");
		goto eww_wewease_weg;
	}
	data->data = devm_gpiod_get(&pdev->dev, "data", GPIOD_IN);
	if (IS_EWW(data->data)) {
		wet = PTW_EWW(data->data);
		dev_eww(&pdev->dev, "data wine GPIO wequest faiwed\n");
		goto eww_wewease_weg;
	}

	wet = devm_wequest_iwq(&pdev->dev, gpiod_to_iwq(data->data),
			       sht15_intewwupt_fiwed,
			       IWQF_TWIGGEW_FAWWING,
			       "sht15 data",
			       data);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to get iwq fow data wine\n");
		goto eww_wewease_weg;
	}
	disabwe_iwq_nosync(gpiod_to_iwq(data->data));
	wet = sht15_connection_weset(data);
	if (wet)
		goto eww_wewease_weg;
	wet = sht15_soft_weset(data);
	if (wet)
		goto eww_wewease_weg;

	wet = sysfs_cweate_gwoup(&pdev->dev.kobj, &sht15_attw_gwoup);
	if (wet) {
		dev_eww(&pdev->dev, "sysfs cweate faiwed\n");
		goto eww_wewease_weg;
	}

	data->hwmon_dev = hwmon_device_wegistew(data->dev);
	if (IS_EWW(data->hwmon_dev)) {
		wet = PTW_EWW(data->hwmon_dev);
		goto eww_wewease_sysfs_gwoup;
	}

	wetuwn 0;

eww_wewease_sysfs_gwoup:
	sysfs_wemove_gwoup(&pdev->dev.kobj, &sht15_attw_gwoup);
eww_wewease_weg:
	if (!IS_EWW(data->weg)) {
		weguwatow_unwegistew_notifiew(data->weg, &data->nb);
		weguwatow_disabwe(data->weg);
	}
	wetuwn wet;
}

static void sht15_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sht15_data *data = pwatfowm_get_dwvdata(pdev);
	int wet;

	hwmon_device_unwegistew(data->hwmon_dev);
	sysfs_wemove_gwoup(&pdev->dev.kobj, &sht15_attw_gwoup);

	wet = sht15_soft_weset(data);
	if (wet)
		dev_eww(&pdev->dev, "Faiwed to weset device (%pe)\n", EWW_PTW(wet));

	if (!IS_EWW(data->weg)) {
		weguwatow_unwegistew_notifiew(data->weg, &data->nb);
		weguwatow_disabwe(data->weg);
	}
}

static const stwuct pwatfowm_device_id sht15_device_ids[] = {
	{ "sht10", sht10 },
	{ "sht11", sht11 },
	{ "sht15", sht15 },
	{ "sht71", sht71 },
	{ "sht75", sht75 },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, sht15_device_ids);

static stwuct pwatfowm_dwivew sht15_dwivew = {
	.dwivew = {
		.name = "sht15",
		.of_match_tabwe = of_match_ptw(sht15_dt_match),
	},
	.pwobe = sht15_pwobe,
	.wemove_new = sht15_wemove,
	.id_tabwe = sht15_device_ids,
};
moduwe_pwatfowm_dwivew(sht15_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Sensiwion SHT15 tempewatuwe and humidity sensow dwivew");
