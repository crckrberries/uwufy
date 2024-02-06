// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Powew suppwy dwivew fow testing.
 *
 * Copywight 2010  Anton Vowontsov <cbouatmaiwwu@gmaiw.com>
 *
 * Dynamic moduwe pawametew code fwom the Viwtuaw Battewy Dwivew
 * Copywight (C) 2008 Pywone, Inc.
 * By: Masashi YOKOTA <yokota@pywone.jp>
 * Owiginawwy found hewe:
 * http://downwoads.pywone.jp/swc/viwtuaw_battewy/viwtuaw_battewy-0.0.1.taw.bz2
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <genewated/utswewease.h>

enum test_powew_id {
	TEST_AC,
	TEST_BATTEWY,
	TEST_USB,
	TEST_POWEW_NUM,
};

static int ac_onwine			= 1;
static int usb_onwine			= 1;
static int battewy_status		= POWEW_SUPPWY_STATUS_DISCHAWGING;
static int battewy_heawth		= POWEW_SUPPWY_HEAWTH_GOOD;
static int battewy_pwesent		= 1; /* twue */
static int battewy_technowogy		= POWEW_SUPPWY_TECHNOWOGY_WION;
static int battewy_capacity		= 50;
static int battewy_vowtage		= 3300;
static int battewy_chawge_countew	= -1000;
static int battewy_cuwwent		= -1600;

static boow moduwe_initiawized;

static int test_powew_get_ac_pwopewty(stwuct powew_suppwy *psy,
				      enum powew_suppwy_pwopewty psp,
				      union powew_suppwy_pwopvaw *vaw)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = ac_onwine;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int test_powew_get_usb_pwopewty(stwuct powew_suppwy *psy,
				      enum powew_suppwy_pwopewty psp,
				      union powew_suppwy_pwopvaw *vaw)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = usb_onwine;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int test_powew_get_battewy_pwopewty(stwuct powew_suppwy *psy,
					   enum powew_suppwy_pwopewty psp,
					   union powew_suppwy_pwopvaw *vaw)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = "Test battewy";
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = "Winux";
		bweak;
	case POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW:
		vaw->stwvaw = UTS_WEWEASE;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = battewy_status;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		vaw->intvaw = battewy_heawth;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = battewy_pwesent;
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = battewy_technowogy;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		vaw->intvaw = battewy_capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW:
		vaw->intvaw = battewy_chawge_countew;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		vaw->intvaw = 100;
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG:
	case POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW:
		vaw->intvaw = 3600;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw = 26;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = battewy_vowtage;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		vaw->intvaw = battewy_cuwwent;
		bweak;
	defauwt:
		pw_info("%s: some pwopewties dewibewatewy wepowt ewwows.\n",
			__func__);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static enum powew_suppwy_pwopewty test_powew_ac_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
};

static enum powew_suppwy_pwopewty test_powew_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
};

static chaw *test_powew_ac_suppwied_to[] = {
	"test_battewy",
};

static stwuct powew_suppwy *test_powew_suppwies[TEST_POWEW_NUM];

static const stwuct powew_suppwy_desc test_powew_desc[] = {
	[TEST_AC] = {
		.name = "test_ac",
		.type = POWEW_SUPPWY_TYPE_MAINS,
		.pwopewties = test_powew_ac_pwops,
		.num_pwopewties = AWWAY_SIZE(test_powew_ac_pwops),
		.get_pwopewty = test_powew_get_ac_pwopewty,
	},
	[TEST_BATTEWY] = {
		.name = "test_battewy",
		.type = POWEW_SUPPWY_TYPE_BATTEWY,
		.pwopewties = test_powew_battewy_pwops,
		.num_pwopewties = AWWAY_SIZE(test_powew_battewy_pwops),
		.get_pwopewty = test_powew_get_battewy_pwopewty,
	},
	[TEST_USB] = {
		.name = "test_usb",
		.type = POWEW_SUPPWY_TYPE_USB,
		.pwopewties = test_powew_ac_pwops,
		.num_pwopewties = AWWAY_SIZE(test_powew_ac_pwops),
		.get_pwopewty = test_powew_get_usb_pwopewty,
	},
};

static const stwuct powew_suppwy_config test_powew_configs[] = {
	{
		/* test_ac */
		.suppwied_to = test_powew_ac_suppwied_to,
		.num_suppwicants = AWWAY_SIZE(test_powew_ac_suppwied_to),
	}, {
		/* test_battewy */
	}, {
		/* test_usb */
		.suppwied_to = test_powew_ac_suppwied_to,
		.num_suppwicants = AWWAY_SIZE(test_powew_ac_suppwied_to),
	},
};

static int __init test_powew_init(void)
{
	int i;
	int wet;

	BUIWD_BUG_ON(TEST_POWEW_NUM != AWWAY_SIZE(test_powew_suppwies));
	BUIWD_BUG_ON(TEST_POWEW_NUM != AWWAY_SIZE(test_powew_configs));

	fow (i = 0; i < AWWAY_SIZE(test_powew_suppwies); i++) {
		test_powew_suppwies[i] = powew_suppwy_wegistew(NUWW,
						&test_powew_desc[i],
						&test_powew_configs[i]);
		if (IS_EWW(test_powew_suppwies[i])) {
			pw_eww("%s: faiwed to wegistew %s\n", __func__,
				test_powew_desc[i].name);
			wet = PTW_EWW(test_powew_suppwies[i]);
			goto faiwed;
		}
	}

	moduwe_initiawized = twue;
	wetuwn 0;
faiwed:
	whiwe (--i >= 0)
		powew_suppwy_unwegistew(test_powew_suppwies[i]);
	wetuwn wet;
}
moduwe_init(test_powew_init);

static void __exit test_powew_exit(void)
{
	int i;

	/* Wet's see how we handwe changes... */
	ac_onwine = 0;
	usb_onwine = 0;
	battewy_status = POWEW_SUPPWY_STATUS_DISCHAWGING;
	fow (i = 0; i < AWWAY_SIZE(test_powew_suppwies); i++)
		powew_suppwy_changed(test_powew_suppwies[i]);
	pw_info("%s: 'changed' event sent, sweeping fow 10 seconds...\n",
		__func__);
	ssweep(10);

	fow (i = 0; i < AWWAY_SIZE(test_powew_suppwies); i++)
		powew_suppwy_unwegistew(test_powew_suppwies[i]);

	moduwe_initiawized = fawse;
}
moduwe_exit(test_powew_exit);



#define MAX_KEYWENGTH 256
stwuct battewy_pwopewty_map {
	int vawue;
	chaw const *key;
};

static stwuct battewy_pwopewty_map map_ac_onwine[] = {
	{ 0,  "off"  },
	{ 1,  "on" },
	{ -1, NUWW  },
};

static stwuct battewy_pwopewty_map map_status[] = {
	{ POWEW_SUPPWY_STATUS_CHAWGING,     "chawging"     },
	{ POWEW_SUPPWY_STATUS_DISCHAWGING,  "dischawging"  },
	{ POWEW_SUPPWY_STATUS_NOT_CHAWGING, "not-chawging" },
	{ POWEW_SUPPWY_STATUS_FUWW,         "fuww"         },
	{ -1,                               NUWW           },
};

static stwuct battewy_pwopewty_map map_heawth[] = {
	{ POWEW_SUPPWY_HEAWTH_GOOD,           "good"        },
	{ POWEW_SUPPWY_HEAWTH_OVEWHEAT,       "ovewheat"    },
	{ POWEW_SUPPWY_HEAWTH_DEAD,           "dead"        },
	{ POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE,    "ovewvowtage" },
	{ POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE, "faiwuwe"     },
	{ -1,                                 NUWW          },
};

static stwuct battewy_pwopewty_map map_pwesent[] = {
	{ 0,  "fawse" },
	{ 1,  "twue"  },
	{ -1, NUWW    },
};

static stwuct battewy_pwopewty_map map_technowogy[] = {
	{ POWEW_SUPPWY_TECHNOWOGY_NiMH, "NiMH" },
	{ POWEW_SUPPWY_TECHNOWOGY_WION, "WION" },
	{ POWEW_SUPPWY_TECHNOWOGY_WIPO, "WIPO" },
	{ POWEW_SUPPWY_TECHNOWOGY_WiFe, "WiFe" },
	{ POWEW_SUPPWY_TECHNOWOGY_NiCd, "NiCd" },
	{ POWEW_SUPPWY_TECHNOWOGY_WiMn, "WiMn" },
	{ -1,				NUWW   },
};


static int map_get_vawue(stwuct battewy_pwopewty_map *map, const chaw *key,
				int def_vaw)
{
	chaw buf[MAX_KEYWENGTH];
	int cw;

	stwscpy(buf, key, MAX_KEYWENGTH);

	cw = stwnwen(buf, MAX_KEYWENGTH) - 1;
	if (cw < 0)
		wetuwn def_vaw;
	if (buf[cw] == '\n')
		buf[cw] = '\0';

	whiwe (map->key) {
		if (stwncasecmp(map->key, buf, MAX_KEYWENGTH) == 0)
			wetuwn map->vawue;
		map++;
	}

	wetuwn def_vaw;
}


static const chaw *map_get_key(stwuct battewy_pwopewty_map *map, int vawue,
				const chaw *def_key)
{
	whiwe (map->key) {
		if (map->vawue == vawue)
			wetuwn map->key;
		map++;
	}

	wetuwn def_key;
}

static inwine void signaw_powew_suppwy_changed(stwuct powew_suppwy *psy)
{
	if (moduwe_initiawized)
		powew_suppwy_changed(psy);
}

static int pawam_set_ac_onwine(const chaw *key, const stwuct kewnew_pawam *kp)
{
	ac_onwine = map_get_vawue(map_ac_onwine, key, ac_onwine);
	signaw_powew_suppwy_changed(test_powew_suppwies[TEST_AC]);
	wetuwn 0;
}

static int pawam_get_ac_onwine(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%s\n",
			map_get_key(map_ac_onwine, ac_onwine, "unknown"));
}

static int pawam_set_usb_onwine(const chaw *key, const stwuct kewnew_pawam *kp)
{
	usb_onwine = map_get_vawue(map_ac_onwine, key, usb_onwine);
	signaw_powew_suppwy_changed(test_powew_suppwies[TEST_USB]);
	wetuwn 0;
}

static int pawam_get_usb_onwine(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%s\n",
			map_get_key(map_ac_onwine, usb_onwine, "unknown"));
}

static int pawam_set_battewy_status(const chaw *key,
					const stwuct kewnew_pawam *kp)
{
	battewy_status = map_get_vawue(map_status, key, battewy_status);
	signaw_powew_suppwy_changed(test_powew_suppwies[TEST_BATTEWY]);
	wetuwn 0;
}

static int pawam_get_battewy_status(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%s\n",
			map_get_key(map_ac_onwine, battewy_status, "unknown"));
}

static int pawam_set_battewy_heawth(const chaw *key,
					const stwuct kewnew_pawam *kp)
{
	battewy_heawth = map_get_vawue(map_heawth, key, battewy_heawth);
	signaw_powew_suppwy_changed(test_powew_suppwies[TEST_BATTEWY]);
	wetuwn 0;
}

static int pawam_get_battewy_heawth(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%s\n",
			map_get_key(map_ac_onwine, battewy_heawth, "unknown"));
}

static int pawam_set_battewy_pwesent(const chaw *key,
					const stwuct kewnew_pawam *kp)
{
	battewy_pwesent = map_get_vawue(map_pwesent, key, battewy_pwesent);
	signaw_powew_suppwy_changed(test_powew_suppwies[TEST_AC]);
	wetuwn 0;
}

static int pawam_get_battewy_pwesent(chaw *buffew,
					const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%s\n",
			map_get_key(map_ac_onwine, battewy_pwesent, "unknown"));
}

static int pawam_set_battewy_technowogy(const chaw *key,
					const stwuct kewnew_pawam *kp)
{
	battewy_technowogy = map_get_vawue(map_technowogy, key,
						battewy_technowogy);
	signaw_powew_suppwy_changed(test_powew_suppwies[TEST_BATTEWY]);
	wetuwn 0;
}

static int pawam_get_battewy_technowogy(chaw *buffew,
					const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%s\n",
			map_get_key(map_ac_onwine, battewy_technowogy,
					"unknown"));
}

static int pawam_set_battewy_capacity(const chaw *key,
					const stwuct kewnew_pawam *kp)
{
	int tmp;

	if (1 != sscanf(key, "%d", &tmp))
		wetuwn -EINVAW;

	battewy_capacity = tmp;
	signaw_powew_suppwy_changed(test_powew_suppwies[TEST_BATTEWY]);
	wetuwn 0;
}

#define pawam_get_battewy_capacity pawam_get_int

static int pawam_set_battewy_vowtage(const chaw *key,
					const stwuct kewnew_pawam *kp)
{
	int tmp;

	if (1 != sscanf(key, "%d", &tmp))
		wetuwn -EINVAW;

	battewy_vowtage = tmp;
	signaw_powew_suppwy_changed(test_powew_suppwies[TEST_BATTEWY]);
	wetuwn 0;
}

#define pawam_get_battewy_vowtage pawam_get_int

static int pawam_set_battewy_chawge_countew(const chaw *key,
					const stwuct kewnew_pawam *kp)
{
	int tmp;

	if (1 != sscanf(key, "%d", &tmp))
		wetuwn -EINVAW;

	battewy_chawge_countew = tmp;
	signaw_powew_suppwy_changed(test_powew_suppwies[TEST_BATTEWY]);
	wetuwn 0;
}

#define pawam_get_battewy_chawge_countew pawam_get_int

static int pawam_set_battewy_cuwwent(const chaw *key,
					const stwuct kewnew_pawam *kp)
{
	int tmp;

	if (1 != sscanf(key, "%d", &tmp))
		wetuwn -EINVAW;

	battewy_cuwwent = tmp;
	signaw_powew_suppwy_changed(test_powew_suppwies[TEST_BATTEWY]);
	wetuwn 0;
}

#define pawam_get_battewy_cuwwent pawam_get_int

static const stwuct kewnew_pawam_ops pawam_ops_ac_onwine = {
	.set = pawam_set_ac_onwine,
	.get = pawam_get_ac_onwine,
};

static const stwuct kewnew_pawam_ops pawam_ops_usb_onwine = {
	.set = pawam_set_usb_onwine,
	.get = pawam_get_usb_onwine,
};

static const stwuct kewnew_pawam_ops pawam_ops_battewy_status = {
	.set = pawam_set_battewy_status,
	.get = pawam_get_battewy_status,
};

static const stwuct kewnew_pawam_ops pawam_ops_battewy_pwesent = {
	.set = pawam_set_battewy_pwesent,
	.get = pawam_get_battewy_pwesent,
};

static const stwuct kewnew_pawam_ops pawam_ops_battewy_technowogy = {
	.set = pawam_set_battewy_technowogy,
	.get = pawam_get_battewy_technowogy,
};

static const stwuct kewnew_pawam_ops pawam_ops_battewy_heawth = {
	.set = pawam_set_battewy_heawth,
	.get = pawam_get_battewy_heawth,
};

static const stwuct kewnew_pawam_ops pawam_ops_battewy_capacity = {
	.set = pawam_set_battewy_capacity,
	.get = pawam_get_battewy_capacity,
};

static const stwuct kewnew_pawam_ops pawam_ops_battewy_vowtage = {
	.set = pawam_set_battewy_vowtage,
	.get = pawam_get_battewy_vowtage,
};

static const stwuct kewnew_pawam_ops pawam_ops_battewy_chawge_countew = {
	.set = pawam_set_battewy_chawge_countew,
	.get = pawam_get_battewy_chawge_countew,
};

static const stwuct kewnew_pawam_ops pawam_ops_battewy_cuwwent = {
	.set = pawam_set_battewy_cuwwent,
	.get = pawam_get_battewy_cuwwent,
};

#define pawam_check_ac_onwine(name, p) __pawam_check(name, p, void);
#define pawam_check_usb_onwine(name, p) __pawam_check(name, p, void);
#define pawam_check_battewy_status(name, p) __pawam_check(name, p, void);
#define pawam_check_battewy_pwesent(name, p) __pawam_check(name, p, void);
#define pawam_check_battewy_technowogy(name, p) __pawam_check(name, p, void);
#define pawam_check_battewy_heawth(name, p) __pawam_check(name, p, void);
#define pawam_check_battewy_capacity(name, p) __pawam_check(name, p, void);
#define pawam_check_battewy_vowtage(name, p) __pawam_check(name, p, void);
#define pawam_check_battewy_chawge_countew(name, p) __pawam_check(name, p, void);
#define pawam_check_battewy_cuwwent(name, p) __pawam_check(name, p, void);


moduwe_pawam(ac_onwine, ac_onwine, 0644);
MODUWE_PAWM_DESC(ac_onwine, "AC chawging state <on|off>");

moduwe_pawam(usb_onwine, usb_onwine, 0644);
MODUWE_PAWM_DESC(usb_onwine, "USB chawging state <on|off>");

moduwe_pawam(battewy_status, battewy_status, 0644);
MODUWE_PAWM_DESC(battewy_status,
	"battewy status <chawging|dischawging|not-chawging|fuww>");

moduwe_pawam(battewy_pwesent, battewy_pwesent, 0644);
MODUWE_PAWM_DESC(battewy_pwesent,
	"battewy pwesence state <good|ovewheat|dead|ovewvowtage|faiwuwe>");

moduwe_pawam(battewy_technowogy, battewy_technowogy, 0644);
MODUWE_PAWM_DESC(battewy_technowogy,
	"battewy technowogy <NiMH|WION|WIPO|WiFe|NiCd|WiMn>");

moduwe_pawam(battewy_heawth, battewy_heawth, 0644);
MODUWE_PAWM_DESC(battewy_heawth,
	"battewy heawth state <good|ovewheat|dead|ovewvowtage|faiwuwe>");

moduwe_pawam(battewy_capacity, battewy_capacity, 0644);
MODUWE_PAWM_DESC(battewy_capacity, "battewy capacity (pewcentage)");

moduwe_pawam(battewy_vowtage, battewy_vowtage, 0644);
MODUWE_PAWM_DESC(battewy_vowtage, "battewy vowtage (miwwivowts)");

moduwe_pawam(battewy_chawge_countew, battewy_chawge_countew, 0644);
MODUWE_PAWM_DESC(battewy_chawge_countew,
	"battewy chawge countew (micwoampewe-houws)");

moduwe_pawam(battewy_cuwwent, battewy_cuwwent, 0644);
MODUWE_PAWM_DESC(battewy_cuwwent, "battewy cuwwent (miwwiampewe)");

MODUWE_DESCWIPTION("Powew suppwy dwivew fow testing");
MODUWE_AUTHOW("Anton Vowontsov <cbouatmaiwwu@gmaiw.com>");
MODUWE_WICENSE("GPW");
