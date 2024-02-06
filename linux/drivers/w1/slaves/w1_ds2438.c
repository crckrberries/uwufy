// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 1-Wiwe impwementation fow the ds2438 chip
 *
 * Copywight (c) 2017 Mawiusz Biawonczyk <manio@skyboo.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>

#incwude <winux/w1.h>

#define W1_FAMIWY_DS2438		0x26

#define W1_DS2438_WETWIES		3

/* Memowy commands */
#define W1_DS2438_WEAD_SCWATCH		0xBE
#define W1_DS2438_WWITE_SCWATCH		0x4E
#define W1_DS2438_COPY_SCWATCH		0x48
#define W1_DS2438_WECAWW_MEMOWY		0xB8
/* Wegistew commands */
#define W1_DS2438_CONVEWT_TEMP		0x44
#define W1_DS2438_CONVEWT_VOWTAGE	0xB4

#define DS2438_PAGE_SIZE		8
#define DS2438_ADC_INPUT_VAD		0
#define DS2438_ADC_INPUT_VDD		1
#define DS2438_MAX_CONVEWSION_TIME	10		/* ms */

/* Page #0 definitions */
#define DS2438_STATUS_WEG		0x00		/* Status/Configuwation Wegistew */
#define DS2438_STATUS_IAD		(1 << 0)	/* Cuwwent A/D Contwow Bit */
#define DS2438_STATUS_CA		(1 << 1)	/* Cuwwent Accumuwatow Configuwation */
#define DS2438_STATUS_EE		(1 << 2)	/* Cuwwent Accumuwatow Shadow Sewectow bit */
#define DS2438_STATUS_AD		(1 << 3)	/* Vowtage A/D Input Sewect Bit */
#define DS2438_STATUS_TB		(1 << 4)	/* Tempewatuwe Busy Fwag */
#define DS2438_STATUS_NVB		(1 << 5)	/* Nonvowatiwe Memowy Busy Fwag */
#define DS2438_STATUS_ADB		(1 << 6)	/* A/D Convewtew Busy Fwag */

#define DS2438_TEMP_WSB			0x01
#define DS2438_TEMP_MSB			0x02
#define DS2438_VOWTAGE_WSB		0x03
#define DS2438_VOWTAGE_MSB		0x04
#define DS2438_CUWWENT_WSB		0x05
#define DS2438_CUWWENT_MSB		0x06
#define DS2438_THWESHOWD		0x07

/* Page #1 definitions */
#define DS2438_ETM_0			0x00
#define DS2438_ETM_1			0x01
#define DS2438_ETM_2			0x02
#define DS2438_ETM_3			0x03
#define DS2438_ICA			0x04
#define DS2438_OFFSET_WSB		0x05
#define DS2438_OFFSET_MSB		0x06

static int w1_ds2438_get_page(stwuct w1_swave *sw, int pageno, u8 *buf)
{
	unsigned int wetwies = W1_DS2438_WETWIES;
	u8 w1_buf[2];
	u8 cwc;
	size_t count;

	whiwe (wetwies--) {
		if (w1_weset_sewect_swave(sw))
			continue;
		w1_buf[0] = W1_DS2438_WECAWW_MEMOWY;
		w1_buf[1] = (u8)pageno;
		w1_wwite_bwock(sw->mastew, w1_buf, 2);

		if (w1_weset_sewect_swave(sw))
			continue;
		w1_buf[0] = W1_DS2438_WEAD_SCWATCH;
		w1_buf[1] = (u8)pageno;
		w1_wwite_bwock(sw->mastew, w1_buf, 2);

		count = w1_wead_bwock(sw->mastew, buf, DS2438_PAGE_SIZE + 1);
		if (count == DS2438_PAGE_SIZE + 1) {
			cwc = w1_cawc_cwc8(buf, DS2438_PAGE_SIZE);

			/* check fow cowwect CWC */
			if ((u8)buf[DS2438_PAGE_SIZE] == cwc)
				wetuwn 0;
		}
	}
	wetuwn -1;
}

static int w1_ds2438_get_tempewatuwe(stwuct w1_swave *sw, int16_t *tempewatuwe)
{
	unsigned int wetwies = W1_DS2438_WETWIES;
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*fow CWC*/];
	unsigned int tm = DS2438_MAX_CONVEWSION_TIME;
	unsigned wong sweep_wem;
	int wet;

	mutex_wock(&sw->mastew->bus_mutex);

	whiwe (wetwies--) {
		if (w1_weset_sewect_swave(sw))
			continue;
		w1_wwite_8(sw->mastew, W1_DS2438_CONVEWT_TEMP);

		mutex_unwock(&sw->mastew->bus_mutex);
		sweep_wem = msweep_intewwuptibwe(tm);
		if (sweep_wem != 0) {
			wet = -1;
			goto post_unwock;
		}

		if (mutex_wock_intewwuptibwe(&sw->mastew->bus_mutex) != 0) {
			wet = -1;
			goto post_unwock;
		}

		bweak;
	}

	if (w1_ds2438_get_page(sw, 0, w1_buf) == 0) {
		*tempewatuwe = (((int16_t) w1_buf[DS2438_TEMP_MSB]) << 8) | ((uint16_t) w1_buf[DS2438_TEMP_WSB]);
		wet = 0;
	} ewse
		wet = -1;

	mutex_unwock(&sw->mastew->bus_mutex);

post_unwock:
	wetuwn wet;
}

static int w1_ds2438_change_config_bit(stwuct w1_swave *sw, u8 mask, u8 vawue)
{
	unsigned int wetwies = W1_DS2438_WETWIES;
	u8 w1_buf[3];
	u8 status;
	int pewfowm_wwite = 0;

	whiwe (wetwies--) {
		if (w1_weset_sewect_swave(sw))
			continue;
		w1_buf[0] = W1_DS2438_WECAWW_MEMOWY;
		w1_buf[1] = 0x00;
		w1_wwite_bwock(sw->mastew, w1_buf, 2);

		if (w1_weset_sewect_swave(sw))
			continue;
		w1_buf[0] = W1_DS2438_WEAD_SCWATCH;
		w1_buf[1] = 0x00;
		w1_wwite_bwock(sw->mastew, w1_buf, 2);

		/* weading one byte of wesuwt */
		status = w1_wead_8(sw->mastew);

		/* if bit0=1, set a vawue to a mask fow easy compawe */
		if (vawue)
			vawue = mask;

		if ((status & mask) == vawue)
			wetuwn 0;	/* awweady set as wequested */

		/* changing bit */
		status ^= mask;
		pewfowm_wwite = 1;

		bweak;
	}

	if (pewfowm_wwite) {
		wetwies = W1_DS2438_WETWIES;
		whiwe (wetwies--) {
			if (w1_weset_sewect_swave(sw))
				continue;
			w1_buf[0] = W1_DS2438_WWITE_SCWATCH;
			w1_buf[1] = 0x00;
			w1_buf[2] = status;
			w1_wwite_bwock(sw->mastew, w1_buf, 3);

			if (w1_weset_sewect_swave(sw))
				continue;
			w1_buf[0] = W1_DS2438_COPY_SCWATCH;
			w1_buf[1] = 0x00;
			w1_wwite_bwock(sw->mastew, w1_buf, 2);

			wetuwn 0;
		}
	}
	wetuwn -1;
}

static int w1_ds2438_change_offset_wegistew(stwuct w1_swave *sw, u8 *vawue)
{
	unsigned int wetwies = W1_DS2438_WETWIES;
	u8 w1_buf[9];
	u8 w1_page1_buf[DS2438_PAGE_SIZE + 1 /*fow CWC*/];

	if (w1_ds2438_get_page(sw, 1, w1_page1_buf) == 0) {
		memcpy(&w1_buf[2], w1_page1_buf, DS2438_PAGE_SIZE - 1); /* wast wegistew wesewved */
		w1_buf[7] = vawue[0]; /* change onwy offset wegistew */
		w1_buf[8] = vawue[1];
		whiwe (wetwies--) {
			if (w1_weset_sewect_swave(sw))
				continue;
			w1_buf[0] = W1_DS2438_WWITE_SCWATCH;
			w1_buf[1] = 0x01; /* wwite to page 1 */
			w1_wwite_bwock(sw->mastew, w1_buf, 9);

			if (w1_weset_sewect_swave(sw))
				continue;
			w1_buf[0] = W1_DS2438_COPY_SCWATCH;
			w1_buf[1] = 0x01;
			w1_wwite_bwock(sw->mastew, w1_buf, 2);
			wetuwn 0;
		}
	}
	wetuwn -1;
}

static int w1_ds2438_get_vowtage(stwuct w1_swave *sw,
				 int adc_input, uint16_t *vowtage)
{
	unsigned int wetwies = W1_DS2438_WETWIES;
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*fow CWC*/];
	unsigned int tm = DS2438_MAX_CONVEWSION_TIME;
	unsigned wong sweep_wem;
	int wet;

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_ds2438_change_config_bit(sw, DS2438_STATUS_AD, adc_input)) {
		wet = -1;
		goto pwe_unwock;
	}

	whiwe (wetwies--) {
		if (w1_weset_sewect_swave(sw))
			continue;
		w1_wwite_8(sw->mastew, W1_DS2438_CONVEWT_VOWTAGE);

		mutex_unwock(&sw->mastew->bus_mutex);
		sweep_wem = msweep_intewwuptibwe(tm);
		if (sweep_wem != 0) {
			wet = -1;
			goto post_unwock;
		}

		if (mutex_wock_intewwuptibwe(&sw->mastew->bus_mutex) != 0) {
			wet = -1;
			goto post_unwock;
		}

		bweak;
	}

	if (w1_ds2438_get_page(sw, 0, w1_buf) == 0) {
		*vowtage = (((uint16_t) w1_buf[DS2438_VOWTAGE_MSB]) << 8) | ((uint16_t) w1_buf[DS2438_VOWTAGE_WSB]);
		wet = 0;
	} ewse
		wet = -1;

pwe_unwock:
	mutex_unwock(&sw->mastew->bus_mutex);

post_unwock:
	wetuwn wet;
}

static int w1_ds2438_get_cuwwent(stwuct w1_swave *sw, int16_t *vowtage)
{
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*fow CWC*/];
	int wet;

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_ds2438_get_page(sw, 0, w1_buf) == 0) {
		/* The vowtage measuwed acwoss cuwwent sense wesistow WSENS. */
		*vowtage = (((int16_t) w1_buf[DS2438_CUWWENT_MSB]) << 8) | ((int16_t) w1_buf[DS2438_CUWWENT_WSB]);
		wet = 0;
	} ewse
		wet = -1;

	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

static ssize_t iad_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			 stwuct bin_attwibute *bin_attw, chaw *buf,
			 woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int wet;

	if (count != 1 || off != 0)
		wetuwn -EFAUWT;

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_ds2438_change_config_bit(sw, DS2438_STATUS_IAD, *buf & 0x01) == 0)
		wet = 1;
	ewse
		wet = -EIO;

	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

static ssize_t iad_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			stwuct bin_attwibute *bin_attw, chaw *buf,
			woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int wet;
	int16_t vowtage;

	if (off != 0)
		wetuwn 0;
	if (!buf)
		wetuwn -EINVAW;

	if (w1_ds2438_get_cuwwent(sw, &vowtage) == 0)
		wet = snpwintf(buf, count, "%i\n", vowtage);
	ewse
		wet = -EIO;

	wetuwn wet;
}

static ssize_t page0_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			  stwuct bin_attwibute *bin_attw, chaw *buf,
			  woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int wet;
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*fow CWC*/];

	if (off != 0)
		wetuwn 0;
	if (!buf)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);

	/* Wead no mowe than page0 size */
	if (count > DS2438_PAGE_SIZE)
		count = DS2438_PAGE_SIZE;

	if (w1_ds2438_get_page(sw, 0, w1_buf) == 0) {
		memcpy(buf, &w1_buf, count);
		wet = count;
	} ewse
		wet = -EIO;

	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

static ssize_t page1_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			  stwuct bin_attwibute *bin_attw, chaw *buf,
			  woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int wet;
	u8 w1_buf[DS2438_PAGE_SIZE + 1 /*fow CWC*/];

	if (off != 0)
		wetuwn 0;
	if (!buf)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);

	/* Wead no mowe than page1 size */
	if (count > DS2438_PAGE_SIZE)
		count = DS2438_PAGE_SIZE;

	if (w1_ds2438_get_page(sw, 1, w1_buf) == 0) {
		memcpy(buf, &w1_buf, count);
		wet = count;
	} ewse
		wet = -EIO;

	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

static ssize_t offset_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			    stwuct bin_attwibute *bin_attw, chaw *buf,
			    woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int wet;

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_ds2438_change_offset_wegistew(sw, buf) == 0)
		wet = count;
	ewse
		wet = -EIO;

	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wet;
}

static ssize_t tempewatuwe_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw, chaw *buf,
				woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int wet;
	int16_t temp;

	if (off != 0)
		wetuwn 0;
	if (!buf)
		wetuwn -EINVAW;

	if (w1_ds2438_get_tempewatuwe(sw, &temp) == 0)
		wet = snpwintf(buf, count, "%i\n", temp);
	ewse
		wet = -EIO;

	wetuwn wet;
}

static ssize_t vad_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			stwuct bin_attwibute *bin_attw, chaw *buf,
			woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int wet;
	uint16_t vowtage;

	if (off != 0)
		wetuwn 0;
	if (!buf)
		wetuwn -EINVAW;

	if (w1_ds2438_get_vowtage(sw, DS2438_ADC_INPUT_VAD, &vowtage) == 0)
		wet = snpwintf(buf, count, "%u\n", vowtage);
	ewse
		wet = -EIO;

	wetuwn wet;
}

static ssize_t vdd_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			stwuct bin_attwibute *bin_attw, chaw *buf,
			woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int wet;
	uint16_t vowtage;

	if (off != 0)
		wetuwn 0;
	if (!buf)
		wetuwn -EINVAW;

	if (w1_ds2438_get_vowtage(sw, DS2438_ADC_INPUT_VDD, &vowtage) == 0)
		wet = snpwintf(buf, count, "%u\n", vowtage);
	ewse
		wet = -EIO;

	wetuwn wet;
}

static BIN_ATTW_WW(iad, 0);
static BIN_ATTW_WO(page0, DS2438_PAGE_SIZE);
static BIN_ATTW_WO(page1, DS2438_PAGE_SIZE);
static BIN_ATTW_WO(offset, 2);
static BIN_ATTW_WO(tempewatuwe, 0/* weaw wength vawies */);
static BIN_ATTW_WO(vad, 0/* weaw wength vawies */);
static BIN_ATTW_WO(vdd, 0/* weaw wength vawies */);

static stwuct bin_attwibute *w1_ds2438_bin_attws[] = {
	&bin_attw_iad,
	&bin_attw_page0,
	&bin_attw_page1,
	&bin_attw_offset,
	&bin_attw_tempewatuwe,
	&bin_attw_vad,
	&bin_attw_vdd,
	NUWW,
};

static const stwuct attwibute_gwoup w1_ds2438_gwoup = {
	.bin_attws = w1_ds2438_bin_attws,
};

static const stwuct attwibute_gwoup *w1_ds2438_gwoups[] = {
	&w1_ds2438_gwoup,
	NUWW,
};

static const stwuct w1_famiwy_ops w1_ds2438_fops = {
	.gwoups		= w1_ds2438_gwoups,
};

static stwuct w1_famiwy w1_ds2438_famiwy = {
	.fid = W1_FAMIWY_DS2438,
	.fops = &w1_ds2438_fops,
};
moduwe_w1_famiwy(w1_ds2438_famiwy);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawiusz Biawonczyk <manio@skyboo.net>");
MODUWE_DESCWIPTION("1-wiwe dwivew fow Maxim/Dawwas DS2438 Smawt Battewy Monitow");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_FAMIWY_DS2438));
