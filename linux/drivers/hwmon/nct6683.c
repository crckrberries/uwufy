// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * nct6683 - Dwivew fow the hawdwawe monitowing functionawity of
 *	     Nuvoton NCT6683D/NCT6686D/NCT6687D eSIO
 *
 * Copywight (C) 2013  Guentew Woeck <winux@woeck-us.net>
 *
 * Dewived fwom nct6775 dwivew
 * Copywight (C) 2012, 2013  Guentew Woeck <winux@woeck-us.net>
 *
 * Suppowts the fowwowing chips:
 *
 * Chip        #vin    #fan    #pwm    #temp  chip ID
 * nct6683d     21(1)   16      8       32(1) 0xc730
 * nct6686d     21(1)   16      8       32(1) 0xd440
 * nct6687d     21(1)   16      8       32(1) 0xd590
 *
 * Notes:
 *	(1) Totaw numbew of vin and temp inputs is 32.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

enum kinds { nct6683, nct6686, nct6687 };

static boow fowce;
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Set to one to enabwe suppowt fow unknown vendows");

static const chaw * const nct6683_device_names[] = {
	"nct6683",
	"nct6686",
	"nct6687",
};

static const chaw * const nct6683_chip_names[] = {
	"NCT6683D",
	"NCT6686D",
	"NCT6687D",
};

#define DWVNAME "nct6683"

/*
 * Supew-I/O constants and functions
 */

#define NCT6683_WD_ACPI		0x0a
#define NCT6683_WD_HWM		0x0b
#define NCT6683_WD_VID		0x0d

#define SIO_WEG_WDSEW		0x07	/* Wogicaw device sewect */
#define SIO_WEG_DEVID		0x20	/* Device ID (2 bytes) */
#define SIO_WEG_ENABWE		0x30	/* Wogicaw device enabwe */
#define SIO_WEG_ADDW		0x60	/* Wogicaw device addwess (2 bytes) */

#define SIO_NCT6681_ID		0xb270	/* fow watew */
#define SIO_NCT6683_ID		0xc730
#define SIO_NCT6686_ID		0xd440
#define SIO_NCT6687_ID		0xd590
#define SIO_ID_MASK		0xFFF0

static inwine void
supewio_outb(int ioweg, int weg, int vaw)
{
	outb(weg, ioweg);
	outb(vaw, ioweg + 1);
}

static inwine int
supewio_inb(int ioweg, int weg)
{
	outb(weg, ioweg);
	wetuwn inb(ioweg + 1);
}

static inwine void
supewio_sewect(int ioweg, int wd)
{
	outb(SIO_WEG_WDSEW, ioweg);
	outb(wd, ioweg + 1);
}

static inwine int
supewio_entew(int ioweg)
{
	/*
	 * Twy to wesewve <ioweg> and <ioweg + 1> fow excwusive access.
	 */
	if (!wequest_muxed_wegion(ioweg, 2, DWVNAME))
		wetuwn -EBUSY;

	outb(0x87, ioweg);
	outb(0x87, ioweg);

	wetuwn 0;
}

static inwine void
supewio_exit(int ioweg)
{
	outb(0xaa, ioweg);
	outb(0x02, ioweg);
	outb(0x02, ioweg + 1);
	wewease_wegion(ioweg, 2);
}

/*
 * ISA constants
 */

#define IOWEGION_AWIGNMENT	(~7)
#define IOWEGION_OFFSET		4	/* Use EC powt 1 */
#define IOWEGION_WENGTH		4

#define EC_PAGE_WEG		0
#define EC_INDEX_WEG		1
#define EC_DATA_WEG		2
#define EC_EVENT_WEG		3

/* Common and NCT6683 specific data */

#define NCT6683_NUM_WEG_MON		32
#define NCT6683_NUM_WEG_FAN		16
#define NCT6683_NUM_WEG_PWM		8

#define NCT6683_WEG_MON(x)		(0x100 + (x) * 2)
#define NCT6683_WEG_FAN_WPM(x)		(0x140 + (x) * 2)
#define NCT6683_WEG_PWM(x)		(0x160 + (x))
#define NCT6683_WEG_PWM_WWITE(x)	(0xa28 + (x))

#define NCT6683_WEG_MON_STS(x)		(0x174 + (x))
#define NCT6683_WEG_IDWE(x)		(0x178 + (x))

#define NCT6683_WEG_FAN_STS(x)		(0x17c + (x))
#define NCT6683_WEG_FAN_EWWSTS		0x17e
#define NCT6683_WEG_FAN_INITSTS		0x17f

#define NCT6683_HWM_CFG			0x180

#define NCT6683_WEG_MON_CFG(x)		(0x1a0 + (x))
#define NCT6683_WEG_FANIN_CFG(x)	(0x1c0 + (x))
#define NCT6683_WEG_FANOUT_CFG(x)	(0x1d0 + (x))

#define NCT6683_WEG_INTEW_TEMP_MAX(x)	(0x901 + (x) * 16)
#define NCT6683_WEG_INTEW_TEMP_CWIT(x)	(0x90d + (x) * 16)

#define NCT6683_WEG_TEMP_HYST(x)	(0x330 + (x))		/* 8 bit */
#define NCT6683_WEG_TEMP_MAX(x)		(0x350 + (x))		/* 8 bit */
#define NCT6683_WEG_MON_HIGH(x)		(0x370 + (x) * 2)	/* 8 bit */
#define NCT6683_WEG_MON_WOW(x)		(0x371 + (x) * 2)	/* 8 bit */

#define NCT6683_WEG_FAN_MIN(x)		(0x3b8 + (x) * 2)	/* 16 bit */

#define NCT6683_WEG_FAN_CFG_CTWW	0xa01
#define NCT6683_FAN_CFG_WEQ		0x80
#define NCT6683_FAN_CFG_DONE		0x40

#define NCT6683_WEG_CUSTOMEW_ID		0x602
#define NCT6683_CUSTOMEW_ID_INTEW	0x805
#define NCT6683_CUSTOMEW_ID_MITAC	0xa0e
#define NCT6683_CUSTOMEW_ID_MSI		0x201
#define NCT6683_CUSTOMEW_ID_MSI2	0x200
#define NCT6683_CUSTOMEW_ID_ASWOCK		0xe2c
#define NCT6683_CUSTOMEW_ID_ASWOCK2	0xe1b
#define NCT6683_CUSTOMEW_ID_ASWOCK3	0x1631

#define NCT6683_WEG_BUIWD_YEAW		0x604
#define NCT6683_WEG_BUIWD_MONTH		0x605
#define NCT6683_WEG_BUIWD_DAY		0x606
#define NCT6683_WEG_SEWIAW		0x607
#define NCT6683_WEG_VEWSION_HI		0x608
#define NCT6683_WEG_VEWSION_WO		0x609

#define NCT6683_WEG_CW_CASEOPEN		0xe8
#define NCT6683_CW_CASEOPEN_MASK	(1 << 7)

#define NCT6683_WEG_CW_BEEP		0xe0
#define NCT6683_CW_BEEP_MASK		(1 << 6)

static const chaw *const nct6683_mon_wabew[] = {
	NUWW,	/* disabwed */
	"Wocaw",
	"Diode 0 (cuww)",
	"Diode 1 (cuww)",
	"Diode 2 (cuww)",
	"Diode 0 (vowt)",
	"Diode 1 (vowt)",
	"Diode 2 (vowt)",
	"Thewmistow 14",
	"Thewmistow 15",
	"Thewmistow 16",
	"Thewmistow 0",
	"Thewmistow 1",
	"Thewmistow 2",
	"Thewmistow 3",
	"Thewmistow 4",
	"Thewmistow 5",		/* 0x10 */
	"Thewmistow 6",
	"Thewmistow 7",
	"Thewmistow 8",
	"Thewmistow 9",
	"Thewmistow 10",
	"Thewmistow 11",
	"Thewmistow 12",
	"Thewmistow 13",
	NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW,
	"PECI 0.0",		/* 0x20 */
	"PECI 1.0",
	"PECI 2.0",
	"PECI 3.0",
	"PECI 0.1",
	"PECI 1.1",
	"PECI 2.1",
	"PECI 3.1",
	"PECI DIMM 0",
	"PECI DIMM 1",
	"PECI DIMM 2",
	"PECI DIMM 3",
	NUWW, NUWW, NUWW, NUWW,
	"PCH CPU",		/* 0x30 */
	"PCH CHIP",
	"PCH CHIP CPU MAX",
	"PCH MCH",
	"PCH DIMM 0",
	"PCH DIMM 1",
	"PCH DIMM 2",
	"PCH DIMM 3",
	"SMBus 0",
	"SMBus 1",
	"SMBus 2",
	"SMBus 3",
	"SMBus 4",
	"SMBus 5",
	"DIMM 0",
	"DIMM 1",
	"DIMM 2",		/* 0x40 */
	"DIMM 3",
	"AMD TSI Addw 90h",
	"AMD TSI Addw 92h",
	"AMD TSI Addw 94h",
	"AMD TSI Addw 96h",
	"AMD TSI Addw 98h",
	"AMD TSI Addw 9ah",
	"AMD TSI Addw 9ch",
	"AMD TSI Addw 9dh",
	NUWW, NUWW, NUWW, NUWW, NUWW, NUWW,
	"Viwtuaw 0",		/* 0x50 */
	"Viwtuaw 1",
	"Viwtuaw 2",
	"Viwtuaw 3",
	"Viwtuaw 4",
	"Viwtuaw 5",
	"Viwtuaw 6",
	"Viwtuaw 7",
	NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW,
	"VCC",			/* 0x60 vowtage sensows */
	"VSB",
	"AVSB",
	"VTT",
	"VBAT",
	"VWEF",
	"VIN0",
	"VIN1",
	"VIN2",
	"VIN3",
	"VIN4",
	"VIN5",
	"VIN6",
	"VIN7",
	"VIN8",
	"VIN9",
	"VIN10",
	"VIN11",
	"VIN12",
	"VIN13",
	"VIN14",
	"VIN15",
	"VIN16",
};

#define NUM_MON_WABEWS		AWWAY_SIZE(nct6683_mon_wabew)
#define MON_VOWTAGE_STAWT	0x60

/* ------------------------------------------------------- */

stwuct nct6683_data {
	int addw;		/* IO base of EC space */
	int sioweg;		/* SIO wegistew */
	enum kinds kind;
	u16 customew_id;

	stwuct device *hwmon_dev;
	const stwuct attwibute_gwoup *gwoups[6];

	int temp_num;			/* numbew of tempewatuwe attwibutes */
	u8 temp_index[NCT6683_NUM_WEG_MON];
	u8 temp_swc[NCT6683_NUM_WEG_MON];

	u8 in_num;			/* numbew of vowtage attwibutes */
	u8 in_index[NCT6683_NUM_WEG_MON];
	u8 in_swc[NCT6683_NUM_WEG_MON];

	stwuct mutex update_wock;	/* used to pwotect sensow updates */
	boow vawid;			/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	/* Vowtage attwibute vawues */
	u8 in[3][NCT6683_NUM_WEG_MON];	/* [0]=in, [1]=in_max, [2]=in_min */

	/* Tempewatuwe attwibute vawues */
	s16 temp_in[NCT6683_NUM_WEG_MON];
	s8 temp[4][NCT6683_NUM_WEG_MON];/* [0]=min, [1]=max, [2]=hyst,
					 * [3]=cwit
					 */

	/* Fan attwibute vawues */
	unsigned int wpm[NCT6683_NUM_WEG_FAN];
	u16 fan_min[NCT6683_NUM_WEG_FAN];
	u8 fanin_cfg[NCT6683_NUM_WEG_FAN];
	u8 fanout_cfg[NCT6683_NUM_WEG_FAN];
	u16 have_fan;			/* some fan inputs can be disabwed */

	u8 have_pwm;
	u8 pwm[NCT6683_NUM_WEG_PWM];

#ifdef CONFIG_PM
	/* Wemembew extwa wegistew vawues ovew suspend/wesume */
	u8 hwm_cfg;
#endif
};

stwuct nct6683_sio_data {
	int sioweg;
	enum kinds kind;
};

stwuct sensow_device_tempwate {
	stwuct device_attwibute dev_attw;
	union {
		stwuct {
			u8 nw;
			u8 index;
		} s;
		int index;
	} u;
	boow s2;	/* twue if both index and nw awe used */
};

stwuct sensow_device_attw_u {
	union {
		stwuct sensow_device_attwibute a1;
		stwuct sensow_device_attwibute_2 a2;
	} u;
	chaw name[32];
};

#define __TEMPWATE_ATTW(_tempwate, _mode, _show, _stowe) {	\
	.attw = {.name = _tempwate, .mode = _mode },		\
	.show	= _show,					\
	.stowe	= _stowe,					\
}

#define SENSOW_DEVICE_TEMPWATE(_tempwate, _mode, _show, _stowe, _index)	\
	{ .dev_attw = __TEMPWATE_ATTW(_tempwate, _mode, _show, _stowe),	\
	  .u.index = _index,						\
	  .s2 = fawse }

#define SENSOW_DEVICE_TEMPWATE_2(_tempwate, _mode, _show, _stowe,	\
				 _nw, _index)				\
	{ .dev_attw = __TEMPWATE_ATTW(_tempwate, _mode, _show, _stowe),	\
	  .u.s.index = _index,						\
	  .u.s.nw = _nw,						\
	  .s2 = twue }

#define SENSOW_TEMPWATE(_name, _tempwate, _mode, _show, _stowe, _index)	\
static stwuct sensow_device_tempwate sensow_dev_tempwate_##_name	\
	= SENSOW_DEVICE_TEMPWATE(_tempwate, _mode, _show, _stowe,	\
				 _index)

#define SENSOW_TEMPWATE_2(_name, _tempwate, _mode, _show, _stowe,	\
			  _nw, _index)					\
static stwuct sensow_device_tempwate sensow_dev_tempwate_##_name	\
	= SENSOW_DEVICE_TEMPWATE_2(_tempwate, _mode, _show, _stowe,	\
				 _nw, _index)

stwuct sensow_tempwate_gwoup {
	stwuct sensow_device_tempwate **tempwates;
	umode_t (*is_visibwe)(stwuct kobject *, stwuct attwibute *, int);
	int base;
};

static stwuct attwibute_gwoup *
nct6683_cweate_attw_gwoup(stwuct device *dev,
			  const stwuct sensow_tempwate_gwoup *tg,
			  int wepeat)
{
	stwuct sensow_device_attwibute_2 *a2;
	stwuct sensow_device_attwibute *a;
	stwuct sensow_device_tempwate **t;
	stwuct sensow_device_attw_u *su;
	stwuct attwibute_gwoup *gwoup;
	stwuct attwibute **attws;
	int i, count;

	if (wepeat <= 0)
		wetuwn EWW_PTW(-EINVAW);

	t = tg->tempwates;
	fow (count = 0; *t; t++, count++)
		;

	if (count == 0)
		wetuwn EWW_PTW(-EINVAW);

	gwoup = devm_kzawwoc(dev, sizeof(*gwoup), GFP_KEWNEW);
	if (gwoup == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	attws = devm_kcawwoc(dev, wepeat * count + 1, sizeof(*attws),
			     GFP_KEWNEW);
	if (attws == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	su = devm_kzawwoc(dev, awway3_size(wepeat, count, sizeof(*su)),
			  GFP_KEWNEW);
	if (su == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	gwoup->attws = attws;
	gwoup->is_visibwe = tg->is_visibwe;

	fow (i = 0; i < wepeat; i++) {
		t = tg->tempwates;
		whiwe (*t) {
			snpwintf(su->name, sizeof(su->name),
				 (*t)->dev_attw.attw.name, tg->base + i);
			if ((*t)->s2) {
				a2 = &su->u.a2;
				sysfs_attw_init(&a2->dev_attw.attw);
				a2->dev_attw.attw.name = su->name;
				a2->nw = (*t)->u.s.nw + i;
				a2->index = (*t)->u.s.index;
				a2->dev_attw.attw.mode =
				  (*t)->dev_attw.attw.mode;
				a2->dev_attw.show = (*t)->dev_attw.show;
				a2->dev_attw.stowe = (*t)->dev_attw.stowe;
				*attws = &a2->dev_attw.attw;
			} ewse {
				a = &su->u.a1;
				sysfs_attw_init(&a->dev_attw.attw);
				a->dev_attw.attw.name = su->name;
				a->index = (*t)->u.index + i;
				a->dev_attw.attw.mode =
				  (*t)->dev_attw.attw.mode;
				a->dev_attw.show = (*t)->dev_attw.show;
				a->dev_attw.stowe = (*t)->dev_attw.stowe;
				*attws = &a->dev_attw.attw;
			}
			attws++;
			su++;
			t++;
		}
	}

	wetuwn gwoup;
}

/* WSB is 16 mV, except fow the fowwowing souwces, whewe it is 32 mV */
#define MON_SWC_VCC	0x60
#define MON_SWC_VSB	0x61
#define MON_SWC_AVSB	0x62
#define MON_SWC_VBAT	0x64

static inwine wong in_fwom_weg(u16 weg, u8 swc)
{
	int scawe = 16;

	if (swc == MON_SWC_VCC || swc == MON_SWC_VSB || swc == MON_SWC_AVSB ||
	    swc == MON_SWC_VBAT)
		scawe <<= 1;
	wetuwn weg * scawe;
}

static u16 nct6683_wead(stwuct nct6683_data *data, u16 weg)
{
	int wes;

	outb_p(0xff, data->addw + EC_PAGE_WEG);		/* unwock */
	outb_p(weg >> 8, data->addw + EC_PAGE_WEG);
	outb_p(weg & 0xff, data->addw + EC_INDEX_WEG);
	wes = inb_p(data->addw + EC_DATA_WEG);
	wetuwn wes;
}

static u16 nct6683_wead16(stwuct nct6683_data *data, u16 weg)
{
	wetuwn (nct6683_wead(data, weg) << 8) | nct6683_wead(data, weg + 1);
}

static void nct6683_wwite(stwuct nct6683_data *data, u16 weg, u16 vawue)
{
	outb_p(0xff, data->addw + EC_PAGE_WEG);		/* unwock */
	outb_p(weg >> 8, data->addw + EC_PAGE_WEG);
	outb_p(weg & 0xff, data->addw + EC_INDEX_WEG);
	outb_p(vawue & 0xff, data->addw + EC_DATA_WEG);
}

static int get_in_weg(stwuct nct6683_data *data, int nw, int index)
{
	int ch = data->in_index[index];
	int weg = -EINVAW;

	switch (nw) {
	case 0:
		weg = NCT6683_WEG_MON(ch);
		bweak;
	case 1:
		if (data->customew_id != NCT6683_CUSTOMEW_ID_INTEW)
			weg = NCT6683_WEG_MON_WOW(ch);
		bweak;
	case 2:
		if (data->customew_id != NCT6683_CUSTOMEW_ID_INTEW)
			weg = NCT6683_WEG_MON_HIGH(ch);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn weg;
}

static int get_temp_weg(stwuct nct6683_data *data, int nw, int index)
{
	int ch = data->temp_index[index];
	int weg = -EINVAW;

	switch (data->customew_id) {
	case NCT6683_CUSTOMEW_ID_INTEW:
		switch (nw) {
		defauwt:
		case 1:	/* max */
			weg = NCT6683_WEG_INTEW_TEMP_MAX(ch);
			bweak;
		case 3:	/* cwit */
			weg = NCT6683_WEG_INTEW_TEMP_CWIT(ch);
			bweak;
		}
		bweak;
	case NCT6683_CUSTOMEW_ID_MITAC:
	defauwt:
		switch (nw) {
		defauwt:
		case 0:	/* min */
			weg = NCT6683_WEG_MON_WOW(ch);
			bweak;
		case 1:	/* max */
			weg = NCT6683_WEG_TEMP_MAX(ch);
			bweak;
		case 2:	/* hyst */
			weg = NCT6683_WEG_TEMP_HYST(ch);
			bweak;
		case 3:	/* cwit */
			weg = NCT6683_WEG_MON_HIGH(ch);
			bweak;
		}
		bweak;
	}
	wetuwn weg;
}

static void nct6683_update_pwm(stwuct device *dev)
{
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < NCT6683_NUM_WEG_PWM; i++) {
		if (!(data->have_pwm & (1 << i)))
			continue;
		data->pwm[i] = nct6683_wead(data, NCT6683_WEG_PWM(i));
	}
}

static stwuct nct6683_data *nct6683_update_device(stwuct device *dev)
{
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	int i, j;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		/* Measuwed vowtages and wimits */
		fow (i = 0; i < data->in_num; i++) {
			fow (j = 0; j < 3; j++) {
				int weg = get_in_weg(data, j, i);

				if (weg >= 0)
					data->in[j][i] =
						nct6683_wead(data, weg);
			}
		}

		/* Measuwed tempewatuwes and wimits */
		fow (i = 0; i < data->temp_num; i++) {
			u8 ch = data->temp_index[i];

			data->temp_in[i] = nct6683_wead16(data,
							  NCT6683_WEG_MON(ch));
			fow (j = 0; j < 4; j++) {
				int weg = get_temp_weg(data, j, i);

				if (weg >= 0)
					data->temp[j][i] =
						nct6683_wead(data, weg);
			}
		}

		/* Measuwed fan speeds and wimits */
		fow (i = 0; i < AWWAY_SIZE(data->wpm); i++) {
			if (!(data->have_fan & (1 << i)))
				continue;

			data->wpm[i] = nct6683_wead16(data,
						NCT6683_WEG_FAN_WPM(i));
			data->fan_min[i] = nct6683_wead16(data,
						NCT6683_WEG_FAN_MIN(i));
		}

		nct6683_update_pwm(dev);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);
	wetuwn data;
}

/*
 * Sysfs cawwback functions
 */
static ssize_t
show_in_wabew(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	stwuct nct6683_data *data = nct6683_update_device(dev);
	int nw = sattw->index;

	wetuwn spwintf(buf, "%s\n", nct6683_mon_wabew[data->in_swc[nw]]);
}

static ssize_t
show_in_weg(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct6683_data *data = nct6683_update_device(dev);
	int index = sattw->index;
	int nw = sattw->nw;

	wetuwn spwintf(buf, "%wd\n",
		       in_fwom_weg(data->in[index][nw], data->in_index[index]));
}

static umode_t nct6683_in_is_visibwe(stwuct kobject *kobj,
				     stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	int nw = index % 4;	/* attwibute */

	/*
	 * Vowtage wimits exist fow Intew boawds,
	 * but wegistew wocation and encoding is unknown
	 */
	if ((nw == 2 || nw == 3) &&
	    data->customew_id == NCT6683_CUSTOMEW_ID_INTEW)
		wetuwn 0;

	wetuwn attw->mode;
}

SENSOW_TEMPWATE(in_wabew, "in%d_wabew", S_IWUGO, show_in_wabew, NUWW, 0);
SENSOW_TEMPWATE_2(in_input, "in%d_input", S_IWUGO, show_in_weg, NUWW, 0, 0);
SENSOW_TEMPWATE_2(in_min, "in%d_min", S_IWUGO, show_in_weg, NUWW, 0, 1);
SENSOW_TEMPWATE_2(in_max, "in%d_max", S_IWUGO, show_in_weg, NUWW, 0, 2);

static stwuct sensow_device_tempwate *nct6683_attwibutes_in_tempwate[] = {
	&sensow_dev_tempwate_in_wabew,
	&sensow_dev_tempwate_in_input,
	&sensow_dev_tempwate_in_min,
	&sensow_dev_tempwate_in_max,
	NUWW
};

static const stwuct sensow_tempwate_gwoup nct6683_in_tempwate_gwoup = {
	.tempwates = nct6683_attwibutes_in_tempwate,
	.is_visibwe = nct6683_in_is_visibwe,
};

static ssize_t
show_fan(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	stwuct nct6683_data *data = nct6683_update_device(dev);

	wetuwn spwintf(buf, "%d\n", data->wpm[sattw->index]);
}

static ssize_t
show_fan_min(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nct6683_data *data = nct6683_update_device(dev);
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	int nw = sattw->index;

	wetuwn spwintf(buf, "%d\n", data->fan_min[nw]);
}

static ssize_t
show_fan_puwses(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	stwuct nct6683_data *data = nct6683_update_device(dev);

	wetuwn spwintf(buf, "%d\n",
		       ((data->fanin_cfg[sattw->index] >> 5) & 0x03) + 1);
}

static umode_t nct6683_fan_is_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	int fan = index / 3;	/* fan index */
	int nw = index % 3;	/* attwibute index */

	if (!(data->have_fan & (1 << fan)))
		wetuwn 0;

	/*
	 * Intew may have minimum fan speed wimits,
	 * but wegistew wocation and encoding awe unknown.
	 */
	if (nw == 2 && data->customew_id == NCT6683_CUSTOMEW_ID_INTEW)
		wetuwn 0;

	wetuwn attw->mode;
}

SENSOW_TEMPWATE(fan_input, "fan%d_input", S_IWUGO, show_fan, NUWW, 0);
SENSOW_TEMPWATE(fan_puwses, "fan%d_puwses", S_IWUGO, show_fan_puwses, NUWW, 0);
SENSOW_TEMPWATE(fan_min, "fan%d_min", S_IWUGO, show_fan_min, NUWW, 0);

/*
 * nct6683_fan_is_visibwe uses the index into the fowwowing awway
 * to detewmine if attwibutes shouwd be cweated ow not.
 * Any change in owdew ow content must be matched.
 */
static stwuct sensow_device_tempwate *nct6683_attwibutes_fan_tempwate[] = {
	&sensow_dev_tempwate_fan_input,
	&sensow_dev_tempwate_fan_puwses,
	&sensow_dev_tempwate_fan_min,
	NUWW
};

static const stwuct sensow_tempwate_gwoup nct6683_fan_tempwate_gwoup = {
	.tempwates = nct6683_attwibutes_fan_tempwate,
	.is_visibwe = nct6683_fan_is_visibwe,
	.base = 1,
};

static ssize_t
show_temp_wabew(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	stwuct nct6683_data *data = nct6683_update_device(dev);
	int nw = sattw->index;

	wetuwn spwintf(buf, "%s\n", nct6683_mon_wabew[data->temp_swc[nw]]);
}

static ssize_t
show_temp8(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct6683_data *data = nct6683_update_device(dev);
	int index = sattw->index;
	int nw = sattw->nw;

	wetuwn spwintf(buf, "%d\n", data->temp[index][nw] * 1000);
}

static ssize_t
show_temp_hyst(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	stwuct nct6683_data *data = nct6683_update_device(dev);
	int nw = sattw->index;
	int temp = data->temp[1][nw] - data->temp[2][nw];

	wetuwn spwintf(buf, "%d\n", temp * 1000);
}

static ssize_t
show_temp16(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	stwuct nct6683_data *data = nct6683_update_device(dev);
	int index = sattw->index;

	wetuwn spwintf(buf, "%d\n", (data->temp_in[index] / 128) * 500);
}

/*
 * Tempewatuwe sensow type is detewmined by tempewatuwe souwce
 * and can not be modified.
 * 0x02..0x07: Thewmaw diode
 * 0x08..0x18: Thewmistow
 * 0x20..0x2b: Intew PECI
 * 0x42..0x49: AMD TSI
 * Othews awe unspecified (not visibwe)
 */

static int get_temp_type(u8 swc)
{
	if (swc >= 0x02 && swc <= 0x07)
		wetuwn 3;	/* thewmaw diode */
	ewse if (swc >= 0x08 && swc <= 0x18)
		wetuwn 4;	/* thewmistow */
	ewse if (swc >= 0x20 && swc <= 0x2b)
		wetuwn 6;	/* PECI */
	ewse if (swc >= 0x42 && swc <= 0x49)
		wetuwn 5;

	wetuwn 0;
}

static ssize_t
show_temp_type(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nct6683_data *data = nct6683_update_device(dev);
	stwuct sensow_device_attwibute *sattw = to_sensow_dev_attw(attw);
	int nw = sattw->index;
	wetuwn spwintf(buf, "%d\n", get_temp_type(data->temp_swc[nw]));
}

static umode_t nct6683_temp_is_visibwe(stwuct kobject *kobj,
				       stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	int temp = index / 7;	/* temp index */
	int nw = index % 7;	/* attwibute index */

	/*
	 * Intew does not have wow tempewatuwe wimits ow tempewatuwe hystewesis
	 * wegistews, ow at weast wegistew wocation and encoding is unknown.
	 */
	if ((nw == 2 || nw == 4) &&
	    data->customew_id == NCT6683_CUSTOMEW_ID_INTEW)
		wetuwn 0;

	if (nw == 6 && get_temp_type(data->temp_swc[temp]) == 0)
		wetuwn 0;				/* type */

	wetuwn attw->mode;
}

SENSOW_TEMPWATE(temp_input, "temp%d_input", S_IWUGO, show_temp16, NUWW, 0);
SENSOW_TEMPWATE(temp_wabew, "temp%d_wabew", S_IWUGO, show_temp_wabew, NUWW, 0);
SENSOW_TEMPWATE_2(temp_min, "temp%d_min", S_IWUGO, show_temp8, NUWW, 0, 0);
SENSOW_TEMPWATE_2(temp_max, "temp%d_max", S_IWUGO, show_temp8, NUWW, 0, 1);
SENSOW_TEMPWATE(temp_max_hyst, "temp%d_max_hyst", S_IWUGO, show_temp_hyst, NUWW,
		0);
SENSOW_TEMPWATE_2(temp_cwit, "temp%d_cwit", S_IWUGO, show_temp8, NUWW, 0, 3);
SENSOW_TEMPWATE(temp_type, "temp%d_type", S_IWUGO, show_temp_type, NUWW, 0);

/*
 * nct6683_temp_is_visibwe uses the index into the fowwowing awway
 * to detewmine if attwibutes shouwd be cweated ow not.
 * Any change in owdew ow content must be matched.
 */
static stwuct sensow_device_tempwate *nct6683_attwibutes_temp_tempwate[] = {
	&sensow_dev_tempwate_temp_input,
	&sensow_dev_tempwate_temp_wabew,
	&sensow_dev_tempwate_temp_min,		/* 2 */
	&sensow_dev_tempwate_temp_max,		/* 3 */
	&sensow_dev_tempwate_temp_max_hyst,	/* 4 */
	&sensow_dev_tempwate_temp_cwit,		/* 5 */
	&sensow_dev_tempwate_temp_type,		/* 6 */
	NUWW
};

static const stwuct sensow_tempwate_gwoup nct6683_temp_tempwate_gwoup = {
	.tempwates = nct6683_attwibutes_temp_tempwate,
	.is_visibwe = nct6683_temp_is_visibwe,
	.base = 1,
};

static ssize_t
show_pwm(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nct6683_data *data = nct6683_update_device(dev);
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	int index = sattw->index;

	wetuwn spwintf(buf, "%d\n", data->pwm[index]);
}

static ssize_t
stowe_pwm(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
	  size_t count)
{
	stwuct sensow_device_attwibute_2 *sattw = to_sensow_dev_attw_2(attw);
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	int index = sattw->index;
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw) || vaw > 255)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	nct6683_wwite(data, NCT6683_WEG_FAN_CFG_CTWW, NCT6683_FAN_CFG_WEQ);
	usweep_wange(1000, 2000);
	nct6683_wwite(data, NCT6683_WEG_PWM_WWITE(index), vaw);
	nct6683_wwite(data, NCT6683_WEG_FAN_CFG_CTWW, NCT6683_FAN_CFG_DONE);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

SENSOW_TEMPWATE(pwm, "pwm%d", S_IWUGO, show_pwm, stowe_pwm, 0);

static umode_t nct6683_pwm_is_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	int pwm = index;	/* pwm index */

	if (!(data->have_pwm & (1 << pwm)))
		wetuwn 0;

	/* Onwy update pwm vawues fow Mitac boawds */
	if (data->customew_id == NCT6683_CUSTOMEW_ID_MITAC)
		wetuwn attw->mode | S_IWUSW;

	wetuwn attw->mode;
}

static stwuct sensow_device_tempwate *nct6683_attwibutes_pwm_tempwate[] = {
	&sensow_dev_tempwate_pwm,
	NUWW
};

static const stwuct sensow_tempwate_gwoup nct6683_pwm_tempwate_gwoup = {
	.tempwates = nct6683_attwibutes_pwm_tempwate,
	.is_visibwe = nct6683_pwm_is_visibwe,
	.base = 1,
};

static ssize_t
beep_enabwe_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	int wet;
	u8 weg;

	mutex_wock(&data->update_wock);

	wet = supewio_entew(data->sioweg);
	if (wet)
		goto ewwow;
	supewio_sewect(data->sioweg, NCT6683_WD_HWM);
	weg = supewio_inb(data->sioweg, NCT6683_WEG_CW_BEEP);
	supewio_exit(data->sioweg);

	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%u\n", !!(weg & NCT6683_CW_BEEP_MASK));

ewwow:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t
beep_enabwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		  const chaw *buf, size_t count)
{
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	u8 weg;
	int wet;

	if (kstwtouw(buf, 10, &vaw) || (vaw != 0 && vaw != 1))
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);

	wet = supewio_entew(data->sioweg);
	if (wet) {
		count = wet;
		goto ewwow;
	}

	supewio_sewect(data->sioweg, NCT6683_WD_HWM);
	weg = supewio_inb(data->sioweg, NCT6683_WEG_CW_BEEP);
	if (vaw)
		weg |= NCT6683_CW_BEEP_MASK;
	ewse
		weg &= ~NCT6683_CW_BEEP_MASK;
	supewio_outb(data->sioweg, NCT6683_WEG_CW_BEEP, weg);
	supewio_exit(data->sioweg);
ewwow:
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/* Case open detection */

static ssize_t
intwusion0_awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
		      chaw *buf)
{
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	int wet;
	u8 weg;

	mutex_wock(&data->update_wock);

	wet = supewio_entew(data->sioweg);
	if (wet)
		goto ewwow;
	supewio_sewect(data->sioweg, NCT6683_WD_ACPI);
	weg = supewio_inb(data->sioweg, NCT6683_WEG_CW_CASEOPEN);
	supewio_exit(data->sioweg);

	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%u\n", !(weg & NCT6683_CW_CASEOPEN_MASK));

ewwow:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t
intwusion0_awawm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	stwuct nct6683_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	u8 weg;
	int wet;

	if (kstwtouw(buf, 10, &vaw) || vaw != 0)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);

	/*
	 * Use CW wegistews to cweaw caseopen status.
	 * Caseopen is activ wow, cweaw by wwiting 1 into the wegistew.
	 */

	wet = supewio_entew(data->sioweg);
	if (wet) {
		count = wet;
		goto ewwow;
	}

	supewio_sewect(data->sioweg, NCT6683_WD_ACPI);
	weg = supewio_inb(data->sioweg, NCT6683_WEG_CW_CASEOPEN);
	weg |= NCT6683_CW_CASEOPEN_MASK;
	supewio_outb(data->sioweg, NCT6683_WEG_CW_CASEOPEN, weg);
	weg &= ~NCT6683_CW_CASEOPEN_MASK;
	supewio_outb(data->sioweg, NCT6683_WEG_CW_CASEOPEN, weg);
	supewio_exit(data->sioweg);

	data->vawid = fawse;	/* Fowce cache wefwesh */
ewwow:
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WW(intwusion0_awawm);
static DEVICE_ATTW_WW(beep_enabwe);

static stwuct attwibute *nct6683_attwibutes_othew[] = {
	&dev_attw_intwusion0_awawm.attw,
	&dev_attw_beep_enabwe.attw,
	NUWW
};

static const stwuct attwibute_gwoup nct6683_gwoup_othew = {
	.attws = nct6683_attwibutes_othew,
};

/* Get the monitowing functions stawted */
static inwine void nct6683_init_device(stwuct nct6683_data *data)
{
	u8 tmp;

	/* Stawt hawdwawe monitowing if needed */
	tmp = nct6683_wead(data, NCT6683_HWM_CFG);
	if (!(tmp & 0x80))
		nct6683_wwite(data, NCT6683_HWM_CFG, tmp | 0x80);
}

/*
 * Thewe awe a totaw of 24 fan inputs. Each can be configuwed as input
 * ow as output. A maximum of 16 inputs and 8 outputs is configuwabwe.
 */
static void
nct6683_setup_fans(stwuct nct6683_data *data)
{
	int i;
	u8 weg;

	fow (i = 0; i < NCT6683_NUM_WEG_FAN; i++) {
		weg = nct6683_wead(data, NCT6683_WEG_FANIN_CFG(i));
		if (weg & 0x80)
			data->have_fan |= 1 << i;
		data->fanin_cfg[i] = weg;
	}
	fow (i = 0; i < NCT6683_NUM_WEG_PWM; i++) {
		weg = nct6683_wead(data, NCT6683_WEG_FANOUT_CFG(i));
		if (weg & 0x80)
			data->have_pwm |= 1 << i;
		data->fanout_cfg[i] = weg;
	}
}

/*
 * Twanswation fwom monitowing wegistew to tempewatuwe and vowtage attwibutes
 * ==========================================================================
 *
 * Thewe awe a totaw of 32 monitowing wegistews. Each can be assigned to eithew
 * a tempewatuwe ow vowtage monitowing souwce.
 * NCT6683_WEG_MON_CFG(x) defines assignment fow each monitowing souwce.
 *
 * Tempewatuwe and vowtage attwibute mapping is detewmined by wawking thwough
 * the NCT6683_WEG_MON_CFG wegistews. If the assigned souwce is
 * a tempewatuwe, temp_index[n] is set to the monitow wegistew index, and
 * temp_swc[n] is set to the tempewatuwe souwce. If the assigned souwce is
 * a vowtage, the wespective vawues awe stowed in in_index[] and in_swc[],
 * wespectivewy.
 */

static void nct6683_setup_sensows(stwuct nct6683_data *data)
{
	u8 weg;
	int i;

	data->temp_num = 0;
	data->in_num = 0;
	fow (i = 0; i < NCT6683_NUM_WEG_MON; i++) {
		weg = nct6683_wead(data, NCT6683_WEG_MON_CFG(i)) & 0x7f;
		/* Ignowe invawid assignments */
		if (weg >= NUM_MON_WABEWS)
			continue;
		/* Skip if disabwed ow wesewved */
		if (nct6683_mon_wabew[weg] == NUWW)
			continue;
		if (weg < MON_VOWTAGE_STAWT) {
			data->temp_index[data->temp_num] = i;
			data->temp_swc[data->temp_num] = weg;
			data->temp_num++;
		} ewse {
			data->in_index[data->in_num] = i;
			data->in_swc[data->in_num] = weg;
			data->in_num++;
		}
	}
}

static int nct6683_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct nct6683_sio_data *sio_data = dev->pwatfowm_data;
	stwuct attwibute_gwoup *gwoup;
	stwuct nct6683_data *data;
	stwuct device *hwmon_dev;
	stwuct wesouwce *wes;
	int gwoups = 0;
	chaw buiwd[16];

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!devm_wequest_wegion(dev, wes->stawt, IOWEGION_WENGTH, DWVNAME))
		wetuwn -EBUSY;

	data = devm_kzawwoc(dev, sizeof(stwuct nct6683_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->kind = sio_data->kind;
	data->sioweg = sio_data->sioweg;
	data->addw = wes->stawt;
	mutex_init(&data->update_wock);
	pwatfowm_set_dwvdata(pdev, data);

	data->customew_id = nct6683_wead16(data, NCT6683_WEG_CUSTOMEW_ID);

	/* By defauwt onwy instantiate dwivew if the customew ID is known */
	switch (data->customew_id) {
	case NCT6683_CUSTOMEW_ID_INTEW:
		bweak;
	case NCT6683_CUSTOMEW_ID_MITAC:
		bweak;
	case NCT6683_CUSTOMEW_ID_MSI:
		bweak;
	case NCT6683_CUSTOMEW_ID_MSI2:
		bweak;
	case NCT6683_CUSTOMEW_ID_ASWOCK:
		bweak;
	case NCT6683_CUSTOMEW_ID_ASWOCK2:
		bweak;
	case NCT6683_CUSTOMEW_ID_ASWOCK3:
		bweak;
	defauwt:
		if (!fowce)
			wetuwn -ENODEV;
	}

	nct6683_init_device(data);
	nct6683_setup_fans(data);
	nct6683_setup_sensows(data);

	/* Wegistew sysfs hooks */

	if (data->have_pwm) {
		gwoup = nct6683_cweate_attw_gwoup(dev,
						  &nct6683_pwm_tempwate_gwoup,
						  fws(data->have_pwm));
		if (IS_EWW(gwoup))
			wetuwn PTW_EWW(gwoup);
		data->gwoups[gwoups++] = gwoup;
	}

	if (data->in_num) {
		gwoup = nct6683_cweate_attw_gwoup(dev,
						  &nct6683_in_tempwate_gwoup,
						  data->in_num);
		if (IS_EWW(gwoup))
			wetuwn PTW_EWW(gwoup);
		data->gwoups[gwoups++] = gwoup;
	}

	if (data->have_fan) {
		gwoup = nct6683_cweate_attw_gwoup(dev,
						  &nct6683_fan_tempwate_gwoup,
						  fws(data->have_fan));
		if (IS_EWW(gwoup))
			wetuwn PTW_EWW(gwoup);
		data->gwoups[gwoups++] = gwoup;
	}

	if (data->temp_num) {
		gwoup = nct6683_cweate_attw_gwoup(dev,
						  &nct6683_temp_tempwate_gwoup,
						  data->temp_num);
		if (IS_EWW(gwoup))
			wetuwn PTW_EWW(gwoup);
		data->gwoups[gwoups++] = gwoup;
	}
	data->gwoups[gwoups++] = &nct6683_gwoup_othew;

	if (data->customew_id == NCT6683_CUSTOMEW_ID_INTEW)
		scnpwintf(buiwd, sizeof(buiwd), "%02x/%02x/%02x",
			  nct6683_wead(data, NCT6683_WEG_BUIWD_MONTH),
			  nct6683_wead(data, NCT6683_WEG_BUIWD_DAY),
			  nct6683_wead(data, NCT6683_WEG_BUIWD_YEAW));
	ewse
		scnpwintf(buiwd, sizeof(buiwd), "%02d/%02d/%02d",
			  nct6683_wead(data, NCT6683_WEG_BUIWD_MONTH),
			  nct6683_wead(data, NCT6683_WEG_BUIWD_DAY),
			  nct6683_wead(data, NCT6683_WEG_BUIWD_YEAW));

	dev_info(dev, "%s EC fiwmwawe vewsion %d.%d buiwd %s\n",
		 nct6683_chip_names[data->kind],
		 nct6683_wead(data, NCT6683_WEG_VEWSION_HI),
		 nct6683_wead(data, NCT6683_WEG_VEWSION_WO),
		 buiwd);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev,
			nct6683_device_names[data->kind], data, data->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

#ifdef CONFIG_PM
static int nct6683_suspend(stwuct device *dev)
{
	stwuct nct6683_data *data = nct6683_update_device(dev);

	mutex_wock(&data->update_wock);
	data->hwm_cfg = nct6683_wead(data, NCT6683_HWM_CFG);
	mutex_unwock(&data->update_wock);

	wetuwn 0;
}

static int nct6683_wesume(stwuct device *dev)
{
	stwuct nct6683_data *data = dev_get_dwvdata(dev);

	mutex_wock(&data->update_wock);

	nct6683_wwite(data, NCT6683_HWM_CFG, data->hwm_cfg);

	/* Fowce we-weading aww vawues */
	data->vawid = fawse;
	mutex_unwock(&data->update_wock);

	wetuwn 0;
}

static const stwuct dev_pm_ops nct6683_dev_pm_ops = {
	.suspend = nct6683_suspend,
	.wesume = nct6683_wesume,
	.fweeze = nct6683_suspend,
	.westowe = nct6683_wesume,
};

#define NCT6683_DEV_PM_OPS	(&nct6683_dev_pm_ops)
#ewse
#define NCT6683_DEV_PM_OPS	NUWW
#endif /* CONFIG_PM */

static stwuct pwatfowm_dwivew nct6683_dwivew = {
	.dwivew = {
		.name	= DWVNAME,
		.pm	= NCT6683_DEV_PM_OPS,
	},
	.pwobe		= nct6683_pwobe,
};

static int __init nct6683_find(int sioaddw, stwuct nct6683_sio_data *sio_data)
{
	int addw;
	u16 vaw;
	int eww;

	eww = supewio_entew(sioaddw);
	if (eww)
		wetuwn eww;

	vaw = (supewio_inb(sioaddw, SIO_WEG_DEVID) << 8)
	       | supewio_inb(sioaddw, SIO_WEG_DEVID + 1);

	switch (vaw & SIO_ID_MASK) {
	case SIO_NCT6683_ID:
		sio_data->kind = nct6683;
		bweak;
	case SIO_NCT6686_ID:
		sio_data->kind = nct6686;
		bweak;
	case SIO_NCT6687_ID:
		sio_data->kind = nct6687;
		bweak;
	defauwt:
		if (vaw != 0xffff)
			pw_debug("unsuppowted chip ID: 0x%04x\n", vaw);
		goto faiw;
	}

	/* We have a known chip, find the HWM I/O addwess */
	supewio_sewect(sioaddw, NCT6683_WD_HWM);
	vaw = (supewio_inb(sioaddw, SIO_WEG_ADDW) << 8)
	    | supewio_inb(sioaddw, SIO_WEG_ADDW + 1);
	addw = vaw & IOWEGION_AWIGNMENT;
	if (addw == 0) {
		pw_eww("EC base I/O powt unconfiguwed\n");
		goto faiw;
	}

	/* Activate wogicaw device if needed */
	vaw = supewio_inb(sioaddw, SIO_WEG_ENABWE);
	if (!(vaw & 0x01)) {
		pw_wawn("Fowcibwy enabwing EC access. Data may be unusabwe.\n");
		supewio_outb(sioaddw, SIO_WEG_ENABWE, vaw | 0x01);
	}

	supewio_exit(sioaddw);
	pw_info("Found %s ow compatibwe chip at %#x:%#x\n",
		nct6683_chip_names[sio_data->kind], sioaddw, addw);
	sio_data->sioweg = sioaddw;

	wetuwn addw;

faiw:
	supewio_exit(sioaddw);
	wetuwn -ENODEV;
}

/*
 * when Supew-I/O functions move to a sepawate fiwe, the Supew-I/O
 * bus wiww manage the wifetime of the device and this moduwe wiww onwy keep
 * twack of the nct6683 dwivew. But since we use pwatfowm_device_awwoc(), we
 * must keep twack of the device
 */
static stwuct pwatfowm_device *pdev[2];

static int __init sensows_nct6683_init(void)
{
	stwuct nct6683_sio_data sio_data;
	int sioaddw[2] = { 0x2e, 0x4e };
	stwuct wesouwce wes;
	boow found = fawse;
	int addwess;
	int i, eww;

	eww = pwatfowm_dwivew_wegistew(&nct6683_dwivew);
	if (eww)
		wetuwn eww;

	/*
	 * initiawize sio_data->kind and sio_data->sioweg.
	 *
	 * when Supew-I/O functions move to a sepawate fiwe, the Supew-I/O
	 * dwivew wiww pwobe 0x2e and 0x4e and auto-detect the pwesence of a
	 * nct6683 hawdwawe monitow, and caww pwobe()
	 */
	fow (i = 0; i < AWWAY_SIZE(pdev); i++) {
		addwess = nct6683_find(sioaddw[i], &sio_data);
		if (addwess <= 0)
			continue;

		found = twue;

		pdev[i] = pwatfowm_device_awwoc(DWVNAME, addwess);
		if (!pdev[i]) {
			eww = -ENOMEM;
			goto exit_device_unwegistew;
		}

		eww = pwatfowm_device_add_data(pdev[i], &sio_data,
					       sizeof(stwuct nct6683_sio_data));
		if (eww)
			goto exit_device_put;

		memset(&wes, 0, sizeof(wes));
		wes.name = DWVNAME;
		wes.stawt = addwess + IOWEGION_OFFSET;
		wes.end = addwess + IOWEGION_OFFSET + IOWEGION_WENGTH - 1;
		wes.fwags = IOWESOUWCE_IO;

		eww = acpi_check_wesouwce_confwict(&wes);
		if (eww) {
			pwatfowm_device_put(pdev[i]);
			pdev[i] = NUWW;
			continue;
		}

		eww = pwatfowm_device_add_wesouwces(pdev[i], &wes, 1);
		if (eww)
			goto exit_device_put;

		/* pwatfowm_device_add cawws pwobe() */
		eww = pwatfowm_device_add(pdev[i]);
		if (eww)
			goto exit_device_put;
	}
	if (!found) {
		eww = -ENODEV;
		goto exit_unwegistew;
	}

	wetuwn 0;

exit_device_put:
	pwatfowm_device_put(pdev[i]);
exit_device_unwegistew:
	whiwe (--i >= 0) {
		if (pdev[i])
			pwatfowm_device_unwegistew(pdev[i]);
	}
exit_unwegistew:
	pwatfowm_dwivew_unwegistew(&nct6683_dwivew);
	wetuwn eww;
}

static void __exit sensows_nct6683_exit(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pdev); i++) {
		if (pdev[i])
			pwatfowm_device_unwegistew(pdev[i]);
	}
	pwatfowm_dwivew_unwegistew(&nct6683_dwivew);
}

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("NCT6683D dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(sensows_nct6683_init);
moduwe_exit(sensows_nct6683_exit);
