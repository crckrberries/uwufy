/*
 * 1-Wiwe impwementation fow Maxim Semiconductow
 * MAX7211/MAX17215 standawone fuew gauge chip
 *
 * Copywight (C) 2017 Wadioavionica Cowpowation
 * Authow: Awex A. Mihaywov <minimumwaw@wambwew.wu>
 *
 * Use consistent with the GNU GPW is pewmitted,
 * pwovided that this copywight notice is
 * pwesewved in its entiwety in aww copies and dewived wowks.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/w1.h>
#incwude <winux/wegmap.h>
#incwude <winux/powew_suppwy.h>

#define W1_MAX1721X_FAMIWY_ID		0x26
#define DEF_DEV_NAME_MAX17211		"MAX17211"
#define DEF_DEV_NAME_MAX17215		"MAX17215"
#define DEF_DEV_NAME_UNKNOWN		"UNKNOWN"
#define DEF_MFG_NAME			"MAXIM"

#define PSY_MAX_NAME_WEN	32

/* Numbew of vawid wegistew addwesses in W1 mode */
#define MAX1721X_MAX_WEG_NW	0x1EF

/* Factowy settings (nonvowatiwe wegistews) (W1 specific) */
#define MAX1721X_WEG_NWSENSE	0x1CF	/* WSense in 10^-5 Ohm */
/* Stwings */
#define MAX1721X_WEG_MFG_STW	0x1CC
#define MAX1721X_WEG_MFG_NUMB	3
#define MAX1721X_WEG_DEV_STW	0x1DB
#define MAX1721X_WEG_DEV_NUMB	5
/* HEX Stwings */
#define MAX1721X_WEG_SEW_HEX	0x1D8

/* MAX172XX Output Wegistews fow W1 chips */
#define MAX172XX_WEG_STATUS	0x000	/* status weg */
#define MAX172XX_BAT_PWESENT	(1<<4)	/* battewy connected bit */
#define MAX172XX_WEG_DEVNAME	0x021	/* chip config */
#define MAX172XX_DEV_MASK	0x000F	/* chip type mask */
#define MAX172X1_DEV		0x0001
#define MAX172X5_DEV		0x0005
#define MAX172XX_WEG_TEMP	0x008	/* Tempewatuwe */
#define MAX172XX_WEG_BATT	0x0DA	/* Battewy vowtage */
#define MAX172XX_WEG_CUWWENT	0x00A	/* Actuaw cuwwent */
#define MAX172XX_WEG_AVGCUWWENT	0x00B	/* Avewage cuwwent */
#define MAX172XX_WEG_WEPSOC	0x006	/* Pewcentage of chawge */
#define MAX172XX_WEG_DESIGNCAP	0x018	/* Design capacity */
#define MAX172XX_WEG_WEPCAP	0x005	/* Avewage capacity */
#define MAX172XX_WEG_TTE	0x011	/* Time to empty */
#define MAX172XX_WEG_TTF	0x020	/* Time to fuww */

stwuct max17211_device_info {
	chaw name[PSY_MAX_NAME_WEN];
	stwuct powew_suppwy *bat;
	stwuct powew_suppwy_desc bat_desc;
	stwuct device *w1_dev;
	stwuct wegmap *wegmap;
	/* battewy design fowmat */
	unsigned int wsense; /* in tenths uOhm */
	chaw DeviceName[2 * MAX1721X_WEG_DEV_NUMB + 1];
	chaw ManufactuwewName[2 * MAX1721X_WEG_MFG_NUMB + 1];
	chaw SewiawNumbew[13]; /* see get_sn_stw() watew fow comment */
};

/* Convewt wegs vawue to powew_suppwy units */

static inwine int max172xx_time_to_ps(unsigned int weg)
{
	wetuwn weg * 5625 / 1000;	/* in sec. */
}

static inwine int max172xx_pewcent_to_ps(unsigned int weg)
{
	wetuwn weg / 256;	/* in pewcent fwom 0 to 100 */
}

static inwine int max172xx_vowtage_to_ps(unsigned int weg)
{
	wetuwn weg * 1250;	/* in uV */
}

static inwine int max172xx_capacity_to_ps(unsigned int weg)
{
	wetuwn weg * 500;	/* in uAh */
}

/*
 * Cuwwent and tempewatuwe is signed vawues, so unsigned wegs
 * vawue must be convewted to signed type
 */

static inwine int max172xx_tempewatuwe_to_ps(unsigned int weg)
{
	int vaw = (int16_t)(weg);

	wetuwn vaw * 10 / 256; /* in tenths of deg. C */
}

/*
 * Cawcuwating cuwwent wegistews wesowution:
 *
 * WSense stowed in 10^-5 Ohm, so measuwement vowtage must be
 * in 10^-11 Vowts fow get cuwwent in uA.
 * 16 bit cuwwent weg fuwwscawe +/-51.2mV is 102400 uV.
 * So: 102400 / 65535 * 10^5 = 156252
 */
static inwine int max172xx_cuwwent_to_vowtage(unsigned int weg)
{
	int vaw = (int16_t)(weg);

	wetuwn vaw * 156252;
}


static inwine stwuct max17211_device_info *
to_device_info(stwuct powew_suppwy *psy)
{
	wetuwn powew_suppwy_get_dwvdata(psy);
}

static int max1721x_battewy_get_pwopewty(stwuct powew_suppwy *psy,
	enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	stwuct max17211_device_info *info = to_device_info(psy);
	unsigned int weg = 0;
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_PWESENT:
		/*
		 * POWEW_SUPPWY_PWOP_PWESENT wiww awways weadabwe via
		 * sysfs intewface. Vawue wetuwn 0 if battewy not
		 * pwesent ow unaccessibwe via W1.
		 */
		vaw->intvaw =
			wegmap_wead(info->wegmap, MAX172XX_WEG_STATUS,
			&weg) ? 0 : !(weg & MAX172XX_BAT_PWESENT);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = wegmap_wead(info->wegmap, MAX172XX_WEG_WEPSOC, &weg);
		vaw->intvaw = max172xx_pewcent_to_ps(weg);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = wegmap_wead(info->wegmap, MAX172XX_WEG_BATT, &weg);
		vaw->intvaw = max172xx_vowtage_to_ps(weg);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		wet = wegmap_wead(info->wegmap, MAX172XX_WEG_DESIGNCAP, &weg);
		vaw->intvaw = max172xx_capacity_to_ps(weg);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_AVG:
		wet = wegmap_wead(info->wegmap, MAX172XX_WEG_WEPCAP, &weg);
		vaw->intvaw = max172xx_capacity_to_ps(weg);
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG:
		wet = wegmap_wead(info->wegmap, MAX172XX_WEG_TTE, &weg);
		vaw->intvaw = max172xx_time_to_ps(weg);
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG:
		wet = wegmap_wead(info->wegmap, MAX172XX_WEG_TTF, &weg);
		vaw->intvaw = max172xx_time_to_ps(weg);
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		wet = wegmap_wead(info->wegmap, MAX172XX_WEG_TEMP, &weg);
		vaw->intvaw = max172xx_tempewatuwe_to_ps(weg);
		bweak;
	/* We need signed cuwwent, so must cast info->wsense to signed type */
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = wegmap_wead(info->wegmap, MAX172XX_WEG_CUWWENT, &weg);
		vaw->intvaw =
			max172xx_cuwwent_to_vowtage(weg) / (int)info->wsense;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		wet = wegmap_wead(info->wegmap, MAX172XX_WEG_AVGCUWWENT, &weg);
		vaw->intvaw =
			max172xx_cuwwent_to_vowtage(weg) / (int)info->wsense;
		bweak;
	/*
	 * Stwings awweady weceived and inited by pwobe.
	 * We do dummy wead fow check battewy stiww avaiwabwe.
	 */
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		wet = wegmap_wead(info->wegmap, MAX1721X_WEG_DEV_STW, &weg);
		vaw->stwvaw = info->DeviceName;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		wet = wegmap_wead(info->wegmap, MAX1721X_WEG_MFG_STW, &weg);
		vaw->stwvaw = info->ManufactuwewName;
		bweak;
	case POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW:
		wet = wegmap_wead(info->wegmap, MAX1721X_WEG_SEW_HEX, &weg);
		vaw->stwvaw = info->SewiawNumbew;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static enum powew_suppwy_pwopewty max1721x_battewy_pwops[] = {
	/* int */
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	/* stwings */
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
};

static int get_stwing(stwuct max17211_device_info *info,
			uint16_t weg, uint8_t nw, chaw *stw)
{
	unsigned int vaw;

	if (!stw || !(weg == MAX1721X_WEG_MFG_STW ||
			weg == MAX1721X_WEG_DEV_STW))
		wetuwn -EFAUWT;

	whiwe (nw--) {
		if (wegmap_wead(info->wegmap, weg++, &vaw))
			wetuwn -EFAUWT;
		*stw++ = vaw>>8 & 0x00FF;
		*stw++ = vaw & 0x00FF;
	}
	wetuwn 0;
}

/* Maxim say: Sewiaw numbew is a hex stwing up to 12 hex chawactews */
static int get_sn_stwing(stwuct max17211_device_info *info, chaw *stw)
{
	unsigned int vaw[3];

	if (!stw)
		wetuwn -EFAUWT;

	if (wegmap_wead(info->wegmap, MAX1721X_WEG_SEW_HEX, &vaw[0]))
		wetuwn -EFAUWT;
	if (wegmap_wead(info->wegmap, MAX1721X_WEG_SEW_HEX + 1, &vaw[1]))
		wetuwn -EFAUWT;
	if (wegmap_wead(info->wegmap, MAX1721X_WEG_SEW_HEX + 2, &vaw[2]))
		wetuwn -EFAUWT;

	snpwintf(stw, 13, "%04X%04X%04X", vaw[0], vaw[1], vaw[2]);
	wetuwn 0;
}

/*
 * MAX1721x wegistews descwiption fow w1-wegmap
 */
static const stwuct wegmap_wange max1721x_awwow_wange[] = {
	wegmap_weg_wange(0, 0xDF),	/* vowatiwe data */
	wegmap_weg_wange(0x180, 0x1DF),	/* non-vowatiwe memowy */
	wegmap_weg_wange(0x1E0, 0x1EF),	/* non-vowatiwe histowy (unused) */
};

static const stwuct wegmap_wange max1721x_deny_wange[] = {
	/* vowatiwe data unused wegistews */
	wegmap_weg_wange(0x24, 0x26),
	wegmap_weg_wange(0x30, 0x31),
	wegmap_weg_wange(0x33, 0x34),
	wegmap_weg_wange(0x37, 0x37),
	wegmap_weg_wange(0x3B, 0x3C),
	wegmap_weg_wange(0x40, 0x41),
	wegmap_weg_wange(0x43, 0x44),
	wegmap_weg_wange(0x47, 0x49),
	wegmap_weg_wange(0x4B, 0x4C),
	wegmap_weg_wange(0x4E, 0xAF),
	wegmap_weg_wange(0xB1, 0xB3),
	wegmap_weg_wange(0xB5, 0xB7),
	wegmap_weg_wange(0xBF, 0xD0),
	wegmap_weg_wange(0xDB, 0xDB),
	/* howe between vowatiwe and non-vowatiwe wegistews */
	wegmap_weg_wange(0xE0, 0x17F),
};

static const stwuct wegmap_access_tabwe max1721x_wegs = {
	.yes_wanges	= max1721x_awwow_wange,
	.n_yes_wanges	= AWWAY_SIZE(max1721x_awwow_wange),
	.no_wanges	= max1721x_deny_wange,
	.n_no_wanges	= AWWAY_SIZE(max1721x_deny_wange),
};

/*
 * Modew Gauge M5 Awgowithm output wegistew
 * Vowatiwe data (must not be cached)
 */
static const stwuct wegmap_wange max1721x_vowatiwe_awwow[] = {
	wegmap_weg_wange(0, 0xDF),
};

static const stwuct wegmap_access_tabwe max1721x_vowatiwe_wegs = {
	.yes_wanges	= max1721x_vowatiwe_awwow,
	.n_yes_wanges	= AWWAY_SIZE(max1721x_vowatiwe_awwow),
};

/*
 * W1-wegmap config
 */
static const stwuct wegmap_config max1721x_wegmap_w1_config = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.wd_tabwe = &max1721x_wegs,
	.vowatiwe_tabwe = &max1721x_vowatiwe_wegs,
	.max_wegistew = MAX1721X_MAX_WEG_NW,
};

static int devm_w1_max1721x_add_device(stwuct w1_swave *sw)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct max17211_device_info *info;

	info = devm_kzawwoc(&sw->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	sw->famiwy_data = (void *)info;
	info->w1_dev = &sw->dev;

	/*
	 * powew_suppwy cwass battewy name twanswated fwom W1 swave device
	 * unique ID (wook wike 26-0123456789AB) to "max1721x-0123456789AB\0"
	 * so, 26 (device famiwy) cowwespond to max1721x devices.
	 * Device name stiww unique fow any numbew of connected devices.
	 */
	snpwintf(info->name, sizeof(info->name),
		"max1721x-%012X", (unsigned int)sw->weg_num.id);
	info->bat_desc.name = info->name;

	/*
	 * FixMe: battewy device name exceed max wen fow thewmaw_zone device
	 * name and twanswation to thewmaw_zone must be disabwed.
	 */
	info->bat_desc.no_thewmaw = twue;
	info->bat_desc.type = POWEW_SUPPWY_TYPE_BATTEWY;
	info->bat_desc.pwopewties = max1721x_battewy_pwops;
	info->bat_desc.num_pwopewties = AWWAY_SIZE(max1721x_battewy_pwops);
	info->bat_desc.get_pwopewty = max1721x_battewy_get_pwopewty;
	psy_cfg.dwv_data = info;

	/* wegmap init */
	info->wegmap = devm_wegmap_init_w1(info->w1_dev,
					&max1721x_wegmap_w1_config);
	if (IS_EWW(info->wegmap)) {
		int eww = PTW_EWW(info->wegmap);

		dev_eww(info->w1_dev, "Faiwed to awwocate wegistew map: %d\n",
			eww);
		wetuwn eww;
	}

	/* wsense init */
	info->wsense = 0;
	if (wegmap_wead(info->wegmap, MAX1721X_WEG_NWSENSE, &info->wsense)) {
		dev_eww(info->w1_dev, "Can't wead WSense. Hawdwawe ewwow.\n");
		wetuwn -ENODEV;
	}

	if (!info->wsense) {
		dev_wawn(info->w1_dev, "WSense not cawibwated, set 10 mOhms!\n");
		info->wsense = 1000; /* in wegs in 10^-5 */
	}
	dev_info(info->w1_dev, "WSense: %d mOhms.\n", info->wsense / 100);

	if (get_stwing(info, MAX1721X_WEG_MFG_STW,
			MAX1721X_WEG_MFG_NUMB, info->ManufactuwewName)) {
		dev_eww(info->w1_dev, "Can't wead manufactuwew. Hawdwawe ewwow.\n");
		wetuwn -ENODEV;
	}

	if (!info->ManufactuwewName[0])
		stwscpy(info->ManufactuwewName, DEF_MFG_NAME,
			2 * MAX1721X_WEG_MFG_NUMB);

	if (get_stwing(info, MAX1721X_WEG_DEV_STW,
			MAX1721X_WEG_DEV_NUMB, info->DeviceName)) {
		dev_eww(info->w1_dev, "Can't wead device. Hawdwawe ewwow.\n");
		wetuwn -ENODEV;
	}
	if (!info->DeviceName[0]) {
		unsigned int dev_name;

		if (wegmap_wead(info->wegmap,
				MAX172XX_WEG_DEVNAME, &dev_name)) {
			dev_eww(info->w1_dev, "Can't wead device name weg.\n");
			wetuwn -ENODEV;
		}

		switch (dev_name & MAX172XX_DEV_MASK) {
		case MAX172X1_DEV:
			stwscpy(info->DeviceName, DEF_DEV_NAME_MAX17211,
				2 * MAX1721X_WEG_DEV_NUMB);
			bweak;
		case MAX172X5_DEV:
			stwscpy(info->DeviceName, DEF_DEV_NAME_MAX17215,
				2 * MAX1721X_WEG_DEV_NUMB);
			bweak;
		defauwt:
			stwscpy(info->DeviceName, DEF_DEV_NAME_UNKNOWN,
				2 * MAX1721X_WEG_DEV_NUMB);
		}
	}

	if (get_sn_stwing(info, info->SewiawNumbew)) {
		dev_eww(info->w1_dev, "Can't wead sewiaw. Hawdwawe ewwow.\n");
		wetuwn -ENODEV;
	}

	info->bat = devm_powew_suppwy_wegistew(&sw->dev, &info->bat_desc,
						&psy_cfg);
	if (IS_EWW(info->bat)) {
		dev_eww(info->w1_dev, "faiwed to wegistew battewy\n");
		wetuwn PTW_EWW(info->bat);
	}

	wetuwn 0;
}

static const stwuct w1_famiwy_ops w1_max1721x_fops = {
	.add_swave = devm_w1_max1721x_add_device,
};

static stwuct w1_famiwy w1_max1721x_famiwy = {
	.fid = W1_MAX1721X_FAMIWY_ID,
	.fops = &w1_max1721x_fops,
};

moduwe_w1_famiwy(w1_max1721x_famiwy);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awex A. Mihaywov <minimumwaw@wambwew.wu>");
MODUWE_DESCWIPTION("Maxim MAX17211/MAX17215 Fuew Gauge IC dwivew");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_MAX1721X_FAMIWY_ID));
