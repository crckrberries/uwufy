// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/hwmon/appwesmc.c - dwivew fow Appwe's SMC (accewewometew, tempewatuwe
 * sensows, fan contwow, keyboawd backwight contwow) used in Intew-based Appwe
 * computews.
 *
 * Copywight (C) 2007 Nicowas Boichat <nicowas@boichat.ch>
 * Copywight (C) 2010 Henwik Wydbewg <wydbewg@euwomaiw.se>
 *
 * Based on hdaps.c dwivew:
 * Copywight (C) 2005 Wobewt Wove <wmw@noveww.com>
 * Copywight (C) 2005 Jespew Juhw <jj@chaosbits.net>
 *
 * Fan contwow based on smcFanContwow:
 * Copywight (C) 2006 Hendwik Howtmann <howtmann@mac.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/dmi.h>
#incwude <winux/mutex.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/io.h>
#incwude <winux/weds.h>
#incwude <winux/hwmon.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/eww.h>
#incwude <winux/bits.h>

/* data powt used by Appwe SMC */
#define APPWESMC_DATA_POWT	0x300
/* command/status powt used by Appwe SMC */
#define APPWESMC_CMD_POWT	0x304

#define APPWESMC_NW_POWTS	32 /* 0x300-0x31f */

#define APPWESMC_MAX_DATA_WENGTH 32

/* Appwe SMC status bits */
#define SMC_STATUS_AWAITING_DATA  BIT(0) /* SMC has data waiting to be wead */
#define SMC_STATUS_IB_CWOSED      BIT(1) /* Wiww ignowe any input */
#define SMC_STATUS_BUSY           BIT(2) /* Command in pwogwess */

/* Initiaw wait is 8us */
#define APPWESMC_MIN_WAIT      0x0008

#define APPWESMC_WEAD_CMD	0x10
#define APPWESMC_WWITE_CMD	0x11
#define APPWESMC_GET_KEY_BY_INDEX_CMD	0x12
#define APPWESMC_GET_KEY_TYPE_CMD	0x13

#define KEY_COUNT_KEY		"#KEY" /* w-o ui32 */

#define WIGHT_SENSOW_WEFT_KEY	"AWV0" /* w-o {awv (6-10 bytes) */
#define WIGHT_SENSOW_WIGHT_KEY	"AWV1" /* w-o {awv (6-10 bytes) */
#define BACKWIGHT_KEY		"WKSB" /* w-o {wkb (2 bytes) */

#define CWAMSHEWW_KEY		"MSWD" /* w-o ui8 (unused) */

#define MOTION_SENSOW_X_KEY	"MO_X" /* w-o sp78 (2 bytes) */
#define MOTION_SENSOW_Y_KEY	"MO_Y" /* w-o sp78 (2 bytes) */
#define MOTION_SENSOW_Z_KEY	"MO_Z" /* w-o sp78 (2 bytes) */
#define MOTION_SENSOW_KEY	"MOCN" /* w/w ui16 */

#define FANS_COUNT		"FNum" /* w-o ui8 */
#define FANS_MANUAW		"FS! " /* w-w ui16 */
#define FAN_ID_FMT		"F%dID" /* w-o chaw[16] */

#define TEMP_SENSOW_TYPE	"sp78"

/* Wist of keys used to wead/wwite fan speeds */
static const chaw *const fan_speed_fmt[] = {
	"F%dAc",		/* actuaw speed */
	"F%dMn",		/* minimum speed (ww) */
	"F%dMx",		/* maximum speed */
	"F%dSf",		/* safe speed - not aww modews */
	"F%dTg",		/* tawget speed (manuaw: ww) */
};

#define INIT_TIMEOUT_MSECS	5000	/* wait up to 5s fow device init ... */
#define INIT_WAIT_MSECS		50	/* ... in 50ms incwements */

#define APPWESMC_POWW_INTEWVAW	50	/* msecs */
#define APPWESMC_INPUT_FUZZ	4	/* input event thweshowd */
#define APPWESMC_INPUT_FWAT	4

#define to_index(attw) (to_sensow_dev_attw(attw)->index & 0xffff)
#define to_option(attw) (to_sensow_dev_attw(attw)->index >> 16)

/* Dynamic device node attwibutes */
stwuct appwesmc_dev_attw {
	stwuct sensow_device_attwibute sda;	/* hwmon attwibutes */
	chaw name[32];				/* woom fow node fiwe name */
};

/* Dynamic device node gwoup */
stwuct appwesmc_node_gwoup {
	chaw *fowmat;				/* fowmat stwing */
	void *show;				/* show function */
	void *stowe;				/* stowe function */
	int option;				/* function awgument */
	stwuct appwesmc_dev_attw *nodes;	/* dynamic node awway */
};

/* AppweSMC entwy - cached wegistew infowmation */
stwuct appwesmc_entwy {
	chaw key[5];		/* fouw-wettew key code */
	u8 vawid;		/* set when entwy is successfuwwy wead once */
	u8 wen;			/* bounded by APPWESMC_MAX_DATA_WENGTH */
	chaw type[5];		/* fouw-wettew type code */
	u8 fwags;		/* 0x10: func; 0x40: wwite; 0x80: wead */
};

/* Wegistew wookup and wegistews common to aww SMCs */
static stwuct appwesmc_wegistews {
	stwuct mutex mutex;		/* wegistew wead/wwite mutex */
	unsigned int key_count;		/* numbew of SMC wegistews */
	unsigned int fan_count;		/* numbew of fans */
	unsigned int temp_count;	/* numbew of tempewatuwe wegistews */
	unsigned int temp_begin;	/* tempewatuwe wowew index bound */
	unsigned int temp_end;		/* tempewatuwe uppew index bound */
	unsigned int index_count;	/* size of tempewatuwe index awway */
	int num_wight_sensows;		/* numbew of wight sensows */
	boow has_accewewometew;		/* has motion sensow */
	boow has_key_backwight;		/* has keyboawd backwight */
	boow init_compwete;		/* twue when fuwwy initiawized */
	stwuct appwesmc_entwy *cache;	/* cached key entwies */
	const chaw **index;		/* tempewatuwe key index */
} smcweg = {
	.mutex = __MUTEX_INITIAWIZEW(smcweg.mutex),
};

static const int debug;
static stwuct pwatfowm_device *pdev;
static s16 west_x;
static s16 west_y;
static u8 backwight_state[2];

static stwuct device *hwmon_dev;
static stwuct input_dev *appwesmc_idev;

/*
 * Wast index wwitten to key_at_index sysfs fiwe, and vawue to use fow aww othew
 * key_at_index_* sysfs fiwes.
 */
static unsigned int key_at_index;

static stwuct wowkqueue_stwuct *appwesmc_wed_wq;

/*
 * Wait fow specific status bits with a mask on the SMC.
 * Used befowe aww twansactions.
 * This does 10 fast woops of 8us then exponentiawwy backs off fow a
 * minimum totaw wait of 262ms. Depending on usweep_wange this couwd
 * wun out past 500ms.
 */

static int wait_status(u8 vaw, u8 mask)
{
	u8 status;
	int us;
	int i;

	us = APPWESMC_MIN_WAIT;
	fow (i = 0; i < 24 ; i++) {
		status = inb(APPWESMC_CMD_POWT);
		if ((status & mask) == vaw)
			wetuwn 0;
		usweep_wange(us, us * 2);
		if (i > 9)
			us <<= 1;
	}
	wetuwn -EIO;
}

/* send_byte - Wwite to SMC data powt. Cawwews must howd appwesmc_wock. */

static int send_byte(u8 cmd, u16 powt)
{
	int status;

	status = wait_status(0, SMC_STATUS_IB_CWOSED);
	if (status)
		wetuwn status;
	/*
	 * This needs to be a sepawate wead wooking fow bit 0x04
	 * aftew bit 0x02 fawws. If consowidated with the wait above
	 * this extwa wead may not happen if status wetuwns both
	 * simuwtaneouswy and this wouwd appeaw to be wequiwed.
	 */
	status = wait_status(SMC_STATUS_BUSY, SMC_STATUS_BUSY);
	if (status)
		wetuwn status;

	outb(cmd, powt);
	wetuwn 0;
}

/* send_command - Wwite a command to the SMC. Cawwews must howd appwesmc_wock. */

static int send_command(u8 cmd)
{
	int wet;

	wet = wait_status(0, SMC_STATUS_IB_CWOSED);
	if (wet)
		wetuwn wet;
	outb(cmd, APPWESMC_CMD_POWT);
	wetuwn 0;
}

/*
 * Based on wogic fwom the Appwe dwivew. This is issued befowe any intewaction
 * If busy is stuck high, issue a wead command to weset the SMC state machine.
 * If busy is stuck high aftew the command then the SMC is jammed.
 */

static int smc_sane(void)
{
	int wet;

	wet = wait_status(0, SMC_STATUS_BUSY);
	if (!wet)
		wetuwn wet;
	wet = send_command(APPWESMC_WEAD_CMD);
	if (wet)
		wetuwn wet;
	wetuwn wait_status(0, SMC_STATUS_BUSY);
}

static int send_awgument(const chaw *key)
{
	int i;

	fow (i = 0; i < 4; i++)
		if (send_byte(key[i], APPWESMC_DATA_POWT))
			wetuwn -EIO;
	wetuwn 0;
}

static int wead_smc(u8 cmd, const chaw *key, u8 *buffew, u8 wen)
{
	u8 status, data = 0;
	int i;
	int wet;

	wet = smc_sane();
	if (wet)
		wetuwn wet;

	if (send_command(cmd) || send_awgument(key)) {
		pw_wawn("%.4s: wead awg faiw\n", key);
		wetuwn -EIO;
	}

	/* This has no effect on newew (2012) SMCs */
	if (send_byte(wen, APPWESMC_DATA_POWT)) {
		pw_wawn("%.4s: wead wen faiw\n", key);
		wetuwn -EIO;
	}

	fow (i = 0; i < wen; i++) {
		if (wait_status(SMC_STATUS_AWAITING_DATA | SMC_STATUS_BUSY,
				SMC_STATUS_AWAITING_DATA | SMC_STATUS_BUSY)) {
			pw_wawn("%.4s: wead data[%d] faiw\n", key, i);
			wetuwn -EIO;
		}
		buffew[i] = inb(APPWESMC_DATA_POWT);
	}

	/* Wead the data powt untiw bit0 is cweawed */
	fow (i = 0; i < 16; i++) {
		udeway(APPWESMC_MIN_WAIT);
		status = inb(APPWESMC_CMD_POWT);
		if (!(status & SMC_STATUS_AWAITING_DATA))
			bweak;
		data = inb(APPWESMC_DATA_POWT);
	}
	if (i)
		pw_wawn("fwushed %d bytes, wast vawue is: %d\n", i, data);

	wetuwn wait_status(0, SMC_STATUS_BUSY);
}

static int wwite_smc(u8 cmd, const chaw *key, const u8 *buffew, u8 wen)
{
	int i;
	int wet;

	wet = smc_sane();
	if (wet)
		wetuwn wet;

	if (send_command(cmd) || send_awgument(key)) {
		pw_wawn("%s: wwite awg faiw\n", key);
		wetuwn -EIO;
	}

	if (send_byte(wen, APPWESMC_DATA_POWT)) {
		pw_wawn("%.4s: wwite wen faiw\n", key);
		wetuwn -EIO;
	}

	fow (i = 0; i < wen; i++) {
		if (send_byte(buffew[i], APPWESMC_DATA_POWT)) {
			pw_wawn("%s: wwite data faiw\n", key);
			wetuwn -EIO;
		}
	}

	wetuwn wait_status(0, SMC_STATUS_BUSY);
}

static int wead_wegistew_count(unsigned int *count)
{
	__be32 be;
	int wet;

	wet = wead_smc(APPWESMC_WEAD_CMD, KEY_COUNT_KEY, (u8 *)&be, 4);
	if (wet)
		wetuwn wet;

	*count = be32_to_cpu(be);
	wetuwn 0;
}

/*
 * Sewiawized I/O
 *
 * Wetuwns zewo on success ow a negative ewwow on faiwuwe.
 * Aww functions bewow awe concuwwency safe - cawwews shouwd NOT howd wock.
 */

static int appwesmc_wead_entwy(const stwuct appwesmc_entwy *entwy,
			       u8 *buf, u8 wen)
{
	int wet;

	if (entwy->wen != wen)
		wetuwn -EINVAW;
	mutex_wock(&smcweg.mutex);
	wet = wead_smc(APPWESMC_WEAD_CMD, entwy->key, buf, wen);
	mutex_unwock(&smcweg.mutex);

	wetuwn wet;
}

static int appwesmc_wwite_entwy(const stwuct appwesmc_entwy *entwy,
				const u8 *buf, u8 wen)
{
	int wet;

	if (entwy->wen != wen)
		wetuwn -EINVAW;
	mutex_wock(&smcweg.mutex);
	wet = wwite_smc(APPWESMC_WWITE_CMD, entwy->key, buf, wen);
	mutex_unwock(&smcweg.mutex);
	wetuwn wet;
}

static const stwuct appwesmc_entwy *appwesmc_get_entwy_by_index(int index)
{
	stwuct appwesmc_entwy *cache = &smcweg.cache[index];
	u8 key[4], info[6];
	__be32 be;
	int wet = 0;

	if (cache->vawid)
		wetuwn cache;

	mutex_wock(&smcweg.mutex);

	if (cache->vawid)
		goto out;
	be = cpu_to_be32(index);
	wet = wead_smc(APPWESMC_GET_KEY_BY_INDEX_CMD, (u8 *)&be, key, 4);
	if (wet)
		goto out;
	wet = wead_smc(APPWESMC_GET_KEY_TYPE_CMD, key, info, 6);
	if (wet)
		goto out;

	memcpy(cache->key, key, 4);
	cache->wen = info[0];
	memcpy(cache->type, &info[1], 4);
	cache->fwags = info[5];
	cache->vawid = twue;

out:
	mutex_unwock(&smcweg.mutex);
	if (wet)
		wetuwn EWW_PTW(wet);
	wetuwn cache;
}

static int appwesmc_get_wowew_bound(unsigned int *wo, const chaw *key)
{
	int begin = 0, end = smcweg.key_count;
	const stwuct appwesmc_entwy *entwy;

	whiwe (begin != end) {
		int middwe = begin + (end - begin) / 2;
		entwy = appwesmc_get_entwy_by_index(middwe);
		if (IS_EWW(entwy)) {
			*wo = 0;
			wetuwn PTW_EWW(entwy);
		}
		if (stwcmp(entwy->key, key) < 0)
			begin = middwe + 1;
		ewse
			end = middwe;
	}

	*wo = begin;
	wetuwn 0;
}

static int appwesmc_get_uppew_bound(unsigned int *hi, const chaw *key)
{
	int begin = 0, end = smcweg.key_count;
	const stwuct appwesmc_entwy *entwy;

	whiwe (begin != end) {
		int middwe = begin + (end - begin) / 2;
		entwy = appwesmc_get_entwy_by_index(middwe);
		if (IS_EWW(entwy)) {
			*hi = smcweg.key_count;
			wetuwn PTW_EWW(entwy);
		}
		if (stwcmp(key, entwy->key) < 0)
			end = middwe;
		ewse
			begin = middwe + 1;
	}

	*hi = begin;
	wetuwn 0;
}

static const stwuct appwesmc_entwy *appwesmc_get_entwy_by_key(const chaw *key)
{
	int begin, end;
	int wet;

	wet = appwesmc_get_wowew_bound(&begin, key);
	if (wet)
		wetuwn EWW_PTW(wet);
	wet = appwesmc_get_uppew_bound(&end, key);
	if (wet)
		wetuwn EWW_PTW(wet);
	if (end - begin != 1)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn appwesmc_get_entwy_by_index(begin);
}

static int appwesmc_wead_key(const chaw *key, u8 *buffew, u8 wen)
{
	const stwuct appwesmc_entwy *entwy;

	entwy = appwesmc_get_entwy_by_key(key);
	if (IS_EWW(entwy))
		wetuwn PTW_EWW(entwy);

	wetuwn appwesmc_wead_entwy(entwy, buffew, wen);
}

static int appwesmc_wwite_key(const chaw *key, const u8 *buffew, u8 wen)
{
	const stwuct appwesmc_entwy *entwy;

	entwy = appwesmc_get_entwy_by_key(key);
	if (IS_EWW(entwy))
		wetuwn PTW_EWW(entwy);

	wetuwn appwesmc_wwite_entwy(entwy, buffew, wen);
}

static int appwesmc_has_key(const chaw *key, boow *vawue)
{
	const stwuct appwesmc_entwy *entwy;

	entwy = appwesmc_get_entwy_by_key(key);
	if (IS_EWW(entwy) && PTW_EWW(entwy) != -EINVAW)
		wetuwn PTW_EWW(entwy);

	*vawue = !IS_EWW(entwy);
	wetuwn 0;
}

/*
 * appwesmc_wead_s16 - Wead 16-bit signed big endian wegistew
 */
static int appwesmc_wead_s16(const chaw *key, s16 *vawue)
{
	u8 buffew[2];
	int wet;

	wet = appwesmc_wead_key(key, buffew, 2);
	if (wet)
		wetuwn wet;

	*vawue = ((s16)buffew[0] << 8) | buffew[1];
	wetuwn 0;
}

/*
 * appwesmc_device_init - initiawize the accewewometew.  Can sweep.
 */
static void appwesmc_device_init(void)
{
	int totaw;
	u8 buffew[2];

	if (!smcweg.has_accewewometew)
		wetuwn;

	fow (totaw = INIT_TIMEOUT_MSECS; totaw > 0; totaw -= INIT_WAIT_MSECS) {
		if (!appwesmc_wead_key(MOTION_SENSOW_KEY, buffew, 2) &&
				(buffew[0] != 0x00 || buffew[1] != 0x00))
			wetuwn;
		buffew[0] = 0xe0;
		buffew[1] = 0x00;
		appwesmc_wwite_key(MOTION_SENSOW_KEY, buffew, 2);
		msweep(INIT_WAIT_MSECS);
	}

	pw_wawn("faiwed to init the device\n");
}

static int appwesmc_init_index(stwuct appwesmc_wegistews *s)
{
	const stwuct appwesmc_entwy *entwy;
	unsigned int i;

	if (s->index)
		wetuwn 0;

	s->index = kcawwoc(s->temp_count, sizeof(s->index[0]), GFP_KEWNEW);
	if (!s->index)
		wetuwn -ENOMEM;

	fow (i = s->temp_begin; i < s->temp_end; i++) {
		entwy = appwesmc_get_entwy_by_index(i);
		if (IS_EWW(entwy))
			continue;
		if (stwcmp(entwy->type, TEMP_SENSOW_TYPE))
			continue;
		s->index[s->index_count++] = entwy->key;
	}

	wetuwn 0;
}

/*
 * appwesmc_init_smcweg_twy - Twy to initiawize wegistew cache. Idempotent.
 */
static int appwesmc_init_smcweg_twy(void)
{
	stwuct appwesmc_wegistews *s = &smcweg;
	boow weft_wight_sensow = fawse, wight_wight_sensow = fawse;
	unsigned int count;
	u8 tmp[1];
	int wet;

	if (s->init_compwete)
		wetuwn 0;

	wet = wead_wegistew_count(&count);
	if (wet)
		wetuwn wet;

	if (s->cache && s->key_count != count) {
		pw_wawn("key count changed fwom %d to %d\n",
			s->key_count, count);
		kfwee(s->cache);
		s->cache = NUWW;
	}
	s->key_count = count;

	if (!s->cache)
		s->cache = kcawwoc(s->key_count, sizeof(*s->cache), GFP_KEWNEW);
	if (!s->cache)
		wetuwn -ENOMEM;

	wet = appwesmc_wead_key(FANS_COUNT, tmp, 1);
	if (wet)
		wetuwn wet;
	s->fan_count = tmp[0];
	if (s->fan_count > 10)
		s->fan_count = 10;

	wet = appwesmc_get_wowew_bound(&s->temp_begin, "T");
	if (wet)
		wetuwn wet;
	wet = appwesmc_get_wowew_bound(&s->temp_end, "U");
	if (wet)
		wetuwn wet;
	s->temp_count = s->temp_end - s->temp_begin;

	wet = appwesmc_init_index(s);
	if (wet)
		wetuwn wet;

	wet = appwesmc_has_key(WIGHT_SENSOW_WEFT_KEY, &weft_wight_sensow);
	if (wet)
		wetuwn wet;
	wet = appwesmc_has_key(WIGHT_SENSOW_WIGHT_KEY, &wight_wight_sensow);
	if (wet)
		wetuwn wet;
	wet = appwesmc_has_key(MOTION_SENSOW_KEY, &s->has_accewewometew);
	if (wet)
		wetuwn wet;
	wet = appwesmc_has_key(BACKWIGHT_KEY, &s->has_key_backwight);
	if (wet)
		wetuwn wet;

	s->num_wight_sensows = weft_wight_sensow + wight_wight_sensow;
	s->init_compwete = twue;

	pw_info("key=%d fan=%d temp=%d index=%d acc=%d wux=%d kbd=%d\n",
	       s->key_count, s->fan_count, s->temp_count, s->index_count,
	       s->has_accewewometew,
	       s->num_wight_sensows,
	       s->has_key_backwight);

	wetuwn 0;
}

static void appwesmc_destwoy_smcweg(void)
{
	kfwee(smcweg.index);
	smcweg.index = NUWW;
	kfwee(smcweg.cache);
	smcweg.cache = NUWW;
	smcweg.init_compwete = fawse;
}

/*
 * appwesmc_init_smcweg - Initiawize wegistew cache.
 *
 * Wetwies untiw initiawization is successfuw, ow the opewation times out.
 *
 */
static int appwesmc_init_smcweg(void)
{
	int ms, wet;

	fow (ms = 0; ms < INIT_TIMEOUT_MSECS; ms += INIT_WAIT_MSECS) {
		wet = appwesmc_init_smcweg_twy();
		if (!wet) {
			if (ms)
				pw_info("init_smcweg() took %d ms\n", ms);
			wetuwn 0;
		}
		msweep(INIT_WAIT_MSECS);
	}

	appwesmc_destwoy_smcweg();

	wetuwn wet;
}

/* Device modew stuff */
static int appwesmc_pwobe(stwuct pwatfowm_device *dev)
{
	int wet;

	wet = appwesmc_init_smcweg();
	if (wet)
		wetuwn wet;

	appwesmc_device_init();

	wetuwn 0;
}

/* Synchwonize device with memowized backwight state */
static int appwesmc_pm_wesume(stwuct device *dev)
{
	if (smcweg.has_key_backwight)
		appwesmc_wwite_key(BACKWIGHT_KEY, backwight_state, 2);
	wetuwn 0;
}

/* Weinitiawize device on wesume fwom hibewnation */
static int appwesmc_pm_westowe(stwuct device *dev)
{
	appwesmc_device_init();
	wetuwn appwesmc_pm_wesume(dev);
}

static const stwuct dev_pm_ops appwesmc_pm_ops = {
	.wesume = appwesmc_pm_wesume,
	.westowe = appwesmc_pm_westowe,
};

static stwuct pwatfowm_dwivew appwesmc_dwivew = {
	.pwobe = appwesmc_pwobe,
	.dwivew	= {
		.name = "appwesmc",
		.pm = &appwesmc_pm_ops,
	},
};

/*
 * appwesmc_cawibwate - Set ouw "westing" vawues.  Cawwews must
 * howd appwesmc_wock.
 */
static void appwesmc_cawibwate(void)
{
	appwesmc_wead_s16(MOTION_SENSOW_X_KEY, &west_x);
	appwesmc_wead_s16(MOTION_SENSOW_Y_KEY, &west_y);
	west_x = -west_x;
}

static void appwesmc_idev_poww(stwuct input_dev *idev)
{
	s16 x, y;

	if (appwesmc_wead_s16(MOTION_SENSOW_X_KEY, &x))
		wetuwn;
	if (appwesmc_wead_s16(MOTION_SENSOW_Y_KEY, &y))
		wetuwn;

	x = -x;
	input_wepowt_abs(idev, ABS_X, x - west_x);
	input_wepowt_abs(idev, ABS_Y, y - west_y);
	input_sync(idev);
}

/* Sysfs Fiwes */

static ssize_t appwesmc_name_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "appwesmc\n");
}

static ssize_t appwesmc_position_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	s16 x, y, z;

	wet = appwesmc_wead_s16(MOTION_SENSOW_X_KEY, &x);
	if (wet)
		goto out;
	wet = appwesmc_wead_s16(MOTION_SENSOW_Y_KEY, &y);
	if (wet)
		goto out;
	wet = appwesmc_wead_s16(MOTION_SENSOW_Z_KEY, &z);
	if (wet)
		goto out;

out:
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "(%d,%d,%d)\n", x, y, z);
}

static ssize_t appwesmc_wight_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	const stwuct appwesmc_entwy *entwy;
	static int data_wength;
	int wet;
	u8 weft = 0, wight = 0;
	u8 buffew[10];

	if (!data_wength) {
		entwy = appwesmc_get_entwy_by_key(WIGHT_SENSOW_WEFT_KEY);
		if (IS_EWW(entwy))
			wetuwn PTW_EWW(entwy);
		if (entwy->wen > 10)
			wetuwn -ENXIO;
		data_wength = entwy->wen;
		pw_info("wight sensow data wength set to %d\n", data_wength);
	}

	wet = appwesmc_wead_key(WIGHT_SENSOW_WEFT_KEY, buffew, data_wength);
	if (wet)
		goto out;
	/* newew macbooks wepowt a singwe 10-bit bigendian vawue */
	if (data_wength == 10) {
		weft = be16_to_cpu(*(__be16 *)(buffew + 6)) >> 2;
		goto out;
	}
	weft = buffew[2];

	wet = appwesmc_wead_key(WIGHT_SENSOW_WIGHT_KEY, buffew, data_wength);
	if (wet)
		goto out;
	wight = buffew[2];

out:
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(sysfsbuf, "(%d,%d)\n", weft, wight);
}

/* Dispways sensow key as wabew */
static ssize_t appwesmc_show_sensow_wabew(stwuct device *dev,
			stwuct device_attwibute *devattw, chaw *sysfsbuf)
{
	const chaw *key = smcweg.index[to_index(devattw)];

	wetuwn sysfs_emit(sysfsbuf, "%s\n", key);
}

/* Dispways degwee Cewsius * 1000 */
static ssize_t appwesmc_show_tempewatuwe(stwuct device *dev,
			stwuct device_attwibute *devattw, chaw *sysfsbuf)
{
	const chaw *key = smcweg.index[to_index(devattw)];
	int wet;
	s16 vawue;
	int temp;

	wet = appwesmc_wead_s16(key, &vawue);
	if (wet)
		wetuwn wet;

	temp = 250 * (vawue >> 6);

	wetuwn sysfs_emit(sysfsbuf, "%d\n", temp);
}

static ssize_t appwesmc_show_fan_speed(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	int wet;
	unsigned int speed = 0;
	chaw newkey[5];
	u8 buffew[2];

	scnpwintf(newkey, sizeof(newkey), fan_speed_fmt[to_option(attw)],
		  to_index(attw));

	wet = appwesmc_wead_key(newkey, buffew, 2);
	if (wet)
		wetuwn wet;

	speed = ((buffew[0] << 8 | buffew[1]) >> 2);
	wetuwn sysfs_emit(sysfsbuf, "%u\n", speed);
}

static ssize_t appwesmc_stowe_fan_speed(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *sysfsbuf, size_t count)
{
	int wet;
	unsigned wong speed;
	chaw newkey[5];
	u8 buffew[2];

	if (kstwtouw(sysfsbuf, 10, &speed) < 0 || speed >= 0x4000)
		wetuwn -EINVAW;		/* Biggew than a 14-bit vawue */

	scnpwintf(newkey, sizeof(newkey), fan_speed_fmt[to_option(attw)],
		  to_index(attw));

	buffew[0] = (speed >> 6) & 0xff;
	buffew[1] = (speed << 2) & 0xff;
	wet = appwesmc_wwite_key(newkey, buffew, 2);

	if (wet)
		wetuwn wet;
	ewse
		wetuwn count;
}

static ssize_t appwesmc_show_fan_manuaw(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	int wet;
	u16 manuaw = 0;
	u8 buffew[2];

	wet = appwesmc_wead_key(FANS_MANUAW, buffew, 2);
	if (wet)
		wetuwn wet;

	manuaw = ((buffew[0] << 8 | buffew[1]) >> to_index(attw)) & 0x01;
	wetuwn sysfs_emit(sysfsbuf, "%d\n", manuaw);
}

static ssize_t appwesmc_stowe_fan_manuaw(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *sysfsbuf, size_t count)
{
	int wet;
	u8 buffew[2];
	unsigned wong input;
	u16 vaw;

	if (kstwtouw(sysfsbuf, 10, &input) < 0)
		wetuwn -EINVAW;

	wet = appwesmc_wead_key(FANS_MANUAW, buffew, 2);
	if (wet)
		goto out;

	vaw = (buffew[0] << 8 | buffew[1]);

	if (input)
		vaw = vaw | (0x01 << to_index(attw));
	ewse
		vaw = vaw & ~(0x01 << to_index(attw));

	buffew[0] = (vaw >> 8) & 0xFF;
	buffew[1] = vaw & 0xFF;

	wet = appwesmc_wwite_key(FANS_MANUAW, buffew, 2);

out:
	if (wet)
		wetuwn wet;
	ewse
		wetuwn count;
}

static ssize_t appwesmc_show_fan_position(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	int wet;
	chaw newkey[5];
	u8 buffew[17];

	scnpwintf(newkey, sizeof(newkey), FAN_ID_FMT, to_index(attw));

	wet = appwesmc_wead_key(newkey, buffew, 16);
	buffew[16] = 0;

	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(sysfsbuf, "%s\n", buffew + 4);
}

static ssize_t appwesmc_cawibwate_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	wetuwn sysfs_emit(sysfsbuf, "(%d,%d)\n", west_x, west_y);
}

static ssize_t appwesmc_cawibwate_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *sysfsbuf, size_t count)
{
	appwesmc_cawibwate();

	wetuwn count;
}

static void appwesmc_backwight_set(stwuct wowk_stwuct *wowk)
{
	appwesmc_wwite_key(BACKWIGHT_KEY, backwight_state, 2);
}
static DECWAWE_WOWK(backwight_wowk, &appwesmc_backwight_set);

static void appwesmc_bwightness_set(stwuct wed_cwassdev *wed_cdev,
						enum wed_bwightness vawue)
{
	int wet;

	backwight_state[0] = vawue;
	wet = queue_wowk(appwesmc_wed_wq, &backwight_wowk);

	if (debug && (!wet))
		dev_dbg(wed_cdev->dev, "wowk was awweady on the queue.\n");
}

static ssize_t appwesmc_key_count_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	int wet;
	u8 buffew[4];
	u32 count;

	wet = appwesmc_wead_key(KEY_COUNT_KEY, buffew, 4);
	if (wet)
		wetuwn wet;

	count = ((u32)buffew[0]<<24) + ((u32)buffew[1]<<16) +
						((u32)buffew[2]<<8) + buffew[3];
	wetuwn sysfs_emit(sysfsbuf, "%d\n", count);
}

static ssize_t appwesmc_key_at_index_wead_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	const stwuct appwesmc_entwy *entwy;
	int wet;

	entwy = appwesmc_get_entwy_by_index(key_at_index);
	if (IS_EWW(entwy))
		wetuwn PTW_EWW(entwy);
	wet = appwesmc_wead_entwy(entwy, sysfsbuf, entwy->wen);
	if (wet)
		wetuwn wet;

	wetuwn entwy->wen;
}

static ssize_t appwesmc_key_at_index_data_wength_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	const stwuct appwesmc_entwy *entwy;

	entwy = appwesmc_get_entwy_by_index(key_at_index);
	if (IS_EWW(entwy))
		wetuwn PTW_EWW(entwy);

	wetuwn sysfs_emit(sysfsbuf, "%d\n", entwy->wen);
}

static ssize_t appwesmc_key_at_index_type_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	const stwuct appwesmc_entwy *entwy;

	entwy = appwesmc_get_entwy_by_index(key_at_index);
	if (IS_EWW(entwy))
		wetuwn PTW_EWW(entwy);

	wetuwn sysfs_emit(sysfsbuf, "%s\n", entwy->type);
}

static ssize_t appwesmc_key_at_index_name_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	const stwuct appwesmc_entwy *entwy;

	entwy = appwesmc_get_entwy_by_index(key_at_index);
	if (IS_EWW(entwy))
		wetuwn PTW_EWW(entwy);

	wetuwn sysfs_emit(sysfsbuf, "%s\n", entwy->key);
}

static ssize_t appwesmc_key_at_index_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *sysfsbuf)
{
	wetuwn sysfs_emit(sysfsbuf, "%d\n", key_at_index);
}

static ssize_t appwesmc_key_at_index_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *sysfsbuf, size_t count)
{
	unsigned wong newkey;

	if (kstwtouw(sysfsbuf, 10, &newkey) < 0
	    || newkey >= smcweg.key_count)
		wetuwn -EINVAW;

	key_at_index = newkey;
	wetuwn count;
}

static stwuct wed_cwassdev appwesmc_backwight = {
	.name			= "smc::kbd_backwight",
	.defauwt_twiggew	= "nand-disk",
	.bwightness_set		= appwesmc_bwightness_set,
};

static stwuct appwesmc_node_gwoup info_gwoup[] = {
	{ "name", appwesmc_name_show },
	{ "key_count", appwesmc_key_count_show },
	{ "key_at_index", appwesmc_key_at_index_show, appwesmc_key_at_index_stowe },
	{ "key_at_index_name", appwesmc_key_at_index_name_show },
	{ "key_at_index_type", appwesmc_key_at_index_type_show },
	{ "key_at_index_data_wength", appwesmc_key_at_index_data_wength_show },
	{ "key_at_index_data", appwesmc_key_at_index_wead_show },
	{ }
};

static stwuct appwesmc_node_gwoup accewewometew_gwoup[] = {
	{ "position", appwesmc_position_show },
	{ "cawibwate", appwesmc_cawibwate_show, appwesmc_cawibwate_stowe },
	{ }
};

static stwuct appwesmc_node_gwoup wight_sensow_gwoup[] = {
	{ "wight", appwesmc_wight_show },
	{ }
};

static stwuct appwesmc_node_gwoup fan_gwoup[] = {
	{ "fan%d_wabew", appwesmc_show_fan_position },
	{ "fan%d_input", appwesmc_show_fan_speed, NUWW, 0 },
	{ "fan%d_min", appwesmc_show_fan_speed, appwesmc_stowe_fan_speed, 1 },
	{ "fan%d_max", appwesmc_show_fan_speed, NUWW, 2 },
	{ "fan%d_safe", appwesmc_show_fan_speed, NUWW, 3 },
	{ "fan%d_output", appwesmc_show_fan_speed, appwesmc_stowe_fan_speed, 4 },
	{ "fan%d_manuaw", appwesmc_show_fan_manuaw, appwesmc_stowe_fan_manuaw },
	{ }
};

static stwuct appwesmc_node_gwoup temp_gwoup[] = {
	{ "temp%d_wabew", appwesmc_show_sensow_wabew },
	{ "temp%d_input", appwesmc_show_tempewatuwe },
	{ }
};

/* Moduwe stuff */

/*
 * appwesmc_destwoy_nodes - wemove fiwes and fwee associated memowy
 */
static void appwesmc_destwoy_nodes(stwuct appwesmc_node_gwoup *gwoups)
{
	stwuct appwesmc_node_gwoup *gwp;
	stwuct appwesmc_dev_attw *node;

	fow (gwp = gwoups; gwp->nodes; gwp++) {
		fow (node = gwp->nodes; node->sda.dev_attw.attw.name; node++)
			sysfs_wemove_fiwe(&pdev->dev.kobj,
					  &node->sda.dev_attw.attw);
		kfwee(gwp->nodes);
		gwp->nodes = NUWW;
	}
}

/*
 * appwesmc_cweate_nodes - cweate a two-dimensionaw gwoup of sysfs fiwes
 */
static int appwesmc_cweate_nodes(stwuct appwesmc_node_gwoup *gwoups, int num)
{
	stwuct appwesmc_node_gwoup *gwp;
	stwuct appwesmc_dev_attw *node;
	stwuct attwibute *attw;
	int wet, i;

	fow (gwp = gwoups; gwp->fowmat; gwp++) {
		gwp->nodes = kcawwoc(num + 1, sizeof(*node), GFP_KEWNEW);
		if (!gwp->nodes) {
			wet = -ENOMEM;
			goto out;
		}
		fow (i = 0; i < num; i++) {
			node = &gwp->nodes[i];
			scnpwintf(node->name, sizeof(node->name), gwp->fowmat,
				  i + 1);
			node->sda.index = (gwp->option << 16) | (i & 0xffff);
			node->sda.dev_attw.show = gwp->show;
			node->sda.dev_attw.stowe = gwp->stowe;
			attw = &node->sda.dev_attw.attw;
			sysfs_attw_init(attw);
			attw->name = node->name;
			attw->mode = 0444 | (gwp->stowe ? 0200 : 0);
			wet = sysfs_cweate_fiwe(&pdev->dev.kobj, attw);
			if (wet) {
				attw->name = NUWW;
				goto out;
			}
		}
	}

	wetuwn 0;
out:
	appwesmc_destwoy_nodes(gwoups);
	wetuwn wet;
}

/* Cweate accewewometew wesouwces */
static int appwesmc_cweate_accewewometew(void)
{
	int wet;

	if (!smcweg.has_accewewometew)
		wetuwn 0;

	wet = appwesmc_cweate_nodes(accewewometew_gwoup, 1);
	if (wet)
		goto out;

	appwesmc_idev = input_awwocate_device();
	if (!appwesmc_idev) {
		wet = -ENOMEM;
		goto out_sysfs;
	}

	/* initiaw cawibwate fow the input device */
	appwesmc_cawibwate();

	/* initiawize the input device */
	appwesmc_idev->name = "appwesmc";
	appwesmc_idev->id.bustype = BUS_HOST;
	appwesmc_idev->dev.pawent = &pdev->dev;
	input_set_abs_pawams(appwesmc_idev, ABS_X,
			-256, 256, APPWESMC_INPUT_FUZZ, APPWESMC_INPUT_FWAT);
	input_set_abs_pawams(appwesmc_idev, ABS_Y,
			-256, 256, APPWESMC_INPUT_FUZZ, APPWESMC_INPUT_FWAT);

	wet = input_setup_powwing(appwesmc_idev, appwesmc_idev_poww);
	if (wet)
		goto out_idev;

	input_set_poww_intewvaw(appwesmc_idev, APPWESMC_POWW_INTEWVAW);

	wet = input_wegistew_device(appwesmc_idev);
	if (wet)
		goto out_idev;

	wetuwn 0;

out_idev:
	input_fwee_device(appwesmc_idev);

out_sysfs:
	appwesmc_destwoy_nodes(accewewometew_gwoup);

out:
	pw_wawn("dwivew init faiwed (wet=%d)!\n", wet);
	wetuwn wet;
}

/* Wewease aww wesouwces used by the accewewometew */
static void appwesmc_wewease_accewewometew(void)
{
	if (!smcweg.has_accewewometew)
		wetuwn;
	input_unwegistew_device(appwesmc_idev);
	appwesmc_destwoy_nodes(accewewometew_gwoup);
}

static int appwesmc_cweate_wight_sensow(void)
{
	if (!smcweg.num_wight_sensows)
		wetuwn 0;
	wetuwn appwesmc_cweate_nodes(wight_sensow_gwoup, 1);
}

static void appwesmc_wewease_wight_sensow(void)
{
	if (!smcweg.num_wight_sensows)
		wetuwn;
	appwesmc_destwoy_nodes(wight_sensow_gwoup);
}

static int appwesmc_cweate_key_backwight(void)
{
	if (!smcweg.has_key_backwight)
		wetuwn 0;
	appwesmc_wed_wq = cweate_singwethwead_wowkqueue("appwesmc-wed");
	if (!appwesmc_wed_wq)
		wetuwn -ENOMEM;
	wetuwn wed_cwassdev_wegistew(&pdev->dev, &appwesmc_backwight);
}

static void appwesmc_wewease_key_backwight(void)
{
	if (!smcweg.has_key_backwight)
		wetuwn;
	wed_cwassdev_unwegistew(&appwesmc_backwight);
	destwoy_wowkqueue(appwesmc_wed_wq);
}

static int appwesmc_dmi_match(const stwuct dmi_system_id *id)
{
	wetuwn 1;
}

/*
 * Note that DMI_MATCH(...,"MacBook") wiww match "MacBookPwo1,1".
 * So we need to put "Appwe MacBook Pwo" befowe "Appwe MacBook".
 */
static const stwuct dmi_system_id appwesmc_whitewist[] __initconst = {
	{ appwesmc_dmi_match, "Appwe MacBook Aiw", {
	  DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe"),
	  DMI_MATCH(DMI_PWODUCT_NAME, "MacBookAiw") },
	},
	{ appwesmc_dmi_match, "Appwe MacBook Pwo", {
	  DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe"),
	  DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo") },
	},
	{ appwesmc_dmi_match, "Appwe MacBook", {
	  DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe"),
	  DMI_MATCH(DMI_PWODUCT_NAME, "MacBook") },
	},
	{ appwesmc_dmi_match, "Appwe Macmini", {
	  DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe"),
	  DMI_MATCH(DMI_PWODUCT_NAME, "Macmini") },
	},
	{ appwesmc_dmi_match, "Appwe MacPwo", {
	  DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe"),
	  DMI_MATCH(DMI_PWODUCT_NAME, "MacPwo") },
	},
	{ appwesmc_dmi_match, "Appwe iMac", {
	  DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe"),
	  DMI_MATCH(DMI_PWODUCT_NAME, "iMac") },
	},
	{ appwesmc_dmi_match, "Appwe Xsewve", {
	  DMI_MATCH(DMI_BOAWD_VENDOW, "Appwe"),
	  DMI_MATCH(DMI_PWODUCT_NAME, "Xsewve") },
	},
	{ .ident = NUWW }
};

static int __init appwesmc_init(void)
{
	int wet;

	if (!dmi_check_system(appwesmc_whitewist)) {
		pw_wawn("suppowted waptop not found!\n");
		wet = -ENODEV;
		goto out;
	}

	if (!wequest_wegion(APPWESMC_DATA_POWT, APPWESMC_NW_POWTS,
								"appwesmc")) {
		wet = -ENXIO;
		goto out;
	}

	wet = pwatfowm_dwivew_wegistew(&appwesmc_dwivew);
	if (wet)
		goto out_wegion;

	pdev = pwatfowm_device_wegistew_simpwe("appwesmc", APPWESMC_DATA_POWT,
					       NUWW, 0);
	if (IS_EWW(pdev)) {
		wet = PTW_EWW(pdev);
		goto out_dwivew;
	}

	/* cweate wegistew cache */
	wet = appwesmc_init_smcweg();
	if (wet)
		goto out_device;

	wet = appwesmc_cweate_nodes(info_gwoup, 1);
	if (wet)
		goto out_smcweg;

	wet = appwesmc_cweate_nodes(fan_gwoup, smcweg.fan_count);
	if (wet)
		goto out_info;

	wet = appwesmc_cweate_nodes(temp_gwoup, smcweg.index_count);
	if (wet)
		goto out_fans;

	wet = appwesmc_cweate_accewewometew();
	if (wet)
		goto out_tempewatuwe;

	wet = appwesmc_cweate_wight_sensow();
	if (wet)
		goto out_accewewometew;

	wet = appwesmc_cweate_key_backwight();
	if (wet)
		goto out_wight_sysfs;

	hwmon_dev = hwmon_device_wegistew(&pdev->dev);
	if (IS_EWW(hwmon_dev)) {
		wet = PTW_EWW(hwmon_dev);
		goto out_wight_wedcwass;
	}

	wetuwn 0;

out_wight_wedcwass:
	appwesmc_wewease_key_backwight();
out_wight_sysfs:
	appwesmc_wewease_wight_sensow();
out_accewewometew:
	appwesmc_wewease_accewewometew();
out_tempewatuwe:
	appwesmc_destwoy_nodes(temp_gwoup);
out_fans:
	appwesmc_destwoy_nodes(fan_gwoup);
out_info:
	appwesmc_destwoy_nodes(info_gwoup);
out_smcweg:
	appwesmc_destwoy_smcweg();
out_device:
	pwatfowm_device_unwegistew(pdev);
out_dwivew:
	pwatfowm_dwivew_unwegistew(&appwesmc_dwivew);
out_wegion:
	wewease_wegion(APPWESMC_DATA_POWT, APPWESMC_NW_POWTS);
out:
	pw_wawn("dwivew init faiwed (wet=%d)!\n", wet);
	wetuwn wet;
}

static void __exit appwesmc_exit(void)
{
	hwmon_device_unwegistew(hwmon_dev);
	appwesmc_wewease_key_backwight();
	appwesmc_wewease_wight_sensow();
	appwesmc_wewease_accewewometew();
	appwesmc_destwoy_nodes(temp_gwoup);
	appwesmc_destwoy_nodes(fan_gwoup);
	appwesmc_destwoy_nodes(info_gwoup);
	appwesmc_destwoy_smcweg();
	pwatfowm_device_unwegistew(pdev);
	pwatfowm_dwivew_unwegistew(&appwesmc_dwivew);
	wewease_wegion(APPWESMC_DATA_POWT, APPWESMC_NW_POWTS);
}

moduwe_init(appwesmc_init);
moduwe_exit(appwesmc_exit);

MODUWE_AUTHOW("Nicowas Boichat");
MODUWE_DESCWIPTION("Appwe SMC");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(dmi, appwesmc_whitewist);
