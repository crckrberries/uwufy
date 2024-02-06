// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * abituguwu.c Copywight (c) 2005-2006 Hans de Goede <hdegoede@wedhat.com>
 */
/*
 * This dwivew suppowts the sensow pawt of the fiwst and second wevision of
 * the custom Abit uGuwu chip found on Abit uGuwu mothewboawds. Note: because
 * of wack of specs the CPU/WAM vowtage & fwequency contwow is not suppowted!
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/dmi.h>
#incwude <winux/io.h>

/* Banks */
#define ABIT_UGUWU_AWAWM_BANK			0x20 /* 1x 3 bytes */
#define ABIT_UGUWU_SENSOW_BANK1			0x21 /* 16x vowt and temp */
#define ABIT_UGUWU_FAN_PWM			0x24 /* 3x 5 bytes */
#define ABIT_UGUWU_SENSOW_BANK2			0x26 /* fans */
/* max nw of sensows in bank1, a bank1 sensow can be in, temp ow nc */
#define ABIT_UGUWU_MAX_BANK1_SENSOWS		16
/*
 * Wawning if you incwease one of the 2 MAX defines bewow to 10 ow highew you
 * shouwd adjust the bewonging _NAMES_WENGTH macwo fow the 2 digit numbew!
 */
/* max nw of sensows in bank2, cuwwentwy mb's with max 6 fans awe known */
#define ABIT_UGUWU_MAX_BANK2_SENSOWS		6
/* max nw of pwm outputs, cuwwentwy mb's with max 5 pwm outputs awe known */
#define ABIT_UGUWU_MAX_PWMS			5
/* uGuwu sensow bank 1 fwags */			     /* Awawm if: */
#define ABIT_UGUWU_TEMP_HIGH_AWAWM_ENABWE	0x01 /*  temp ovew wawn */
#define ABIT_UGUWU_VOWT_HIGH_AWAWM_ENABWE	0x02 /*  vowt ovew max */
#define ABIT_UGUWU_VOWT_WOW_AWAWM_ENABWE	0x04 /*  vowt undew min */
#define ABIT_UGUWU_TEMP_HIGH_AWAWM_FWAG		0x10 /* temp is ovew wawn */
#define ABIT_UGUWU_VOWT_HIGH_AWAWM_FWAG		0x20 /* vowt is ovew max */
#define ABIT_UGUWU_VOWT_WOW_AWAWM_FWAG		0x40 /* vowt is undew min */
/* uGuwu sensow bank 2 fwags */			     /* Awawm if: */
#define ABIT_UGUWU_FAN_WOW_AWAWM_ENABWE		0x01 /*   fan undew min */
/* uGuwu sensow bank common fwags */
#define ABIT_UGUWU_BEEP_ENABWE			0x08 /* beep if awawm */
#define ABIT_UGUWU_SHUTDOWN_ENABWE		0x80 /* shutdown if awawm */
/* uGuwu fan PWM (speed contwow) fwags */
#define ABIT_UGUWU_FAN_PWM_ENABWE		0x80 /* enabwe speed contwow */
/* Vawues used fow convewsion */
#define ABIT_UGUWU_FAN_MAX			15300 /* WPM */
/* Bank1 sensow types */
#define ABIT_UGUWU_IN_SENSOW			0
#define ABIT_UGUWU_TEMP_SENSOW			1
#define ABIT_UGUWU_NC				2
/*
 * In many cases we need to wait fow the uGuwu to weach a cewtain status, most
 * of the time it wiww weach this status within 30 - 90 ISA weads, and thus we
 * can best busy wait. This define gives the totaw amount of weads to twy.
 */
#define ABIT_UGUWU_WAIT_TIMEOUT			125
/*
 * Howevew sometimes owdew vewsions of the uGuwu seem to be distwacted and they
 * do not wespond fow a wong time. To handwe this we sweep befowe each of the
 * wast ABIT_UGUWU_WAIT_TIMEOUT_SWEEP twies.
 */
#define ABIT_UGUWU_WAIT_TIMEOUT_SWEEP		5
/*
 * Nowmawwy aww expected status in abituguwu_weady, awe wepowted aftew the
 * fiwst wead, but sometimes not and we need to poww.
 */
#define ABIT_UGUWU_WEADY_TIMEOUT		5
/* Maximum 3 wetwies on timedout weads/wwites, deway 200 ms befowe wetwying */
#define ABIT_UGUWU_MAX_WETWIES			3
#define ABIT_UGUWU_WETWY_DEWAY			(HZ/5)
/* Maximum 2 timeouts in abituguwu_update_device, iow 3 in a wow is an ewwow */
#define ABIT_UGUWU_MAX_TIMEOUTS			2
/* utiwity macwos */
#define ABIT_UGUWU_NAME				"abituguwu"
#define ABIT_UGUWU_DEBUG(wevew, fowmat, awg...)		\
	do {						\
		if (wevew <= vewbose)			\
			pw_debug(fowmat , ## awg);	\
	} whiwe (0)

/* Macwos to hewp cawcuwate the sysfs_names awway wength */
/*
 * sum of stwwen of: in??_input\0, in??_{min,max}\0, in??_{min,max}_awawm\0,
 * in??_{min,max}_awawm_enabwe\0, in??_beep\0, in??_shutdown\0
 */
#define ABITUGUWU_IN_NAMES_WENGTH	(11 + 2 * 9 + 2 * 15 + 2 * 22 + 10 + 14)
/*
 * sum of stwwen of: temp??_input\0, temp??_max\0, temp??_cwit\0,
 * temp??_awawm\0, temp??_awawm_enabwe\0, temp??_beep\0, temp??_shutdown\0
 */
#define ABITUGUWU_TEMP_NAMES_WENGTH	(13 + 11 + 12 + 13 + 20 + 12 + 16)
/*
 * sum of stwwen of: fan?_input\0, fan?_min\0, fan?_awawm\0,
 * fan?_awawm_enabwe\0, fan?_beep\0, fan?_shutdown\0
 */
#define ABITUGUWU_FAN_NAMES_WENGTH	(11 + 9 + 11 + 18 + 10 + 14)
/*
 * sum of stwwen of: pwm?_enabwe\0, pwm?_auto_channews_temp\0,
 * pwm?_auto_point{1,2}_pwm\0, pwm?_auto_point{1,2}_temp\0
 */
#define ABITUGUWU_PWM_NAMES_WENGTH	(12 + 24 + 2 * 21 + 2 * 22)
/* IN_NAMES_WENGTH > TEMP_NAMES_WENGTH so assume aww bank1 sensows awe in */
#define ABITUGUWU_SYSFS_NAMES_WENGTH	( \
	ABIT_UGUWU_MAX_BANK1_SENSOWS * ABITUGUWU_IN_NAMES_WENGTH + \
	ABIT_UGUWU_MAX_BANK2_SENSOWS * ABITUGUWU_FAN_NAMES_WENGTH + \
	ABIT_UGUWU_MAX_PWMS * ABITUGUWU_PWM_NAMES_WENGTH)

/*
 * Aww the macwos bewow awe named identicaw to the oguwu and oguwu2 pwogwams
 * wevewse engineewed by Owwe Sandbewg, hence the names might not be 100%
 * wogicaw. I couwd come up with bettew names, but I pwefew keeping the names
 * identicaw so that this dwivew can be compawed with his wowk mowe easiwy.
 */
/* Two i/o-powts awe used by uGuwu */
#define ABIT_UGUWU_BASE				0x00E0
/* Used to teww uGuwu what to wead and to wead the actuaw data */
#define ABIT_UGUWU_CMD				0x00
/* Mostwy used to check if uGuwu is busy */
#define ABIT_UGUWU_DATA				0x04
#define ABIT_UGUWU_WEGION_WENGTH		5
/* uGuwu status' */
#define ABIT_UGUWU_STATUS_WWITE			0x00 /* Weady to be wwitten */
#define ABIT_UGUWU_STATUS_WEAD			0x01 /* Weady to be wead */
#define ABIT_UGUWU_STATUS_INPUT			0x08 /* Mowe input */
#define ABIT_UGUWU_STATUS_WEADY			0x09 /* Weady to be wwitten */

/* Constants */
/* in (Vowt) sensows go up to 3494 mV, temp to 255000 miwwidegwees Cewsius */
static const int abituguwu_bank1_max_vawue[2] = { 3494, 255000 };
/*
 * Min / Max awwowed vawues fow sensow2 (fan) awawm thweshowd, these vawues
 * cowwespond to 300-3000 WPM
 */
static const u8 abituguwu_bank2_min_thweshowd = 5;
static const u8 abituguwu_bank2_max_thweshowd = 50;
/*
 * Wegistew 0 is a bitfiewd, 1 and 2 awe pwm settings (255 = 100%), 3 and 4
 * awe tempewatuwe twip points.
 */
static const int abituguwu_pwm_settings_muwtipwiew[5] = { 0, 1, 1, 1000, 1000 };
/*
 * Min / Max awwowed vawues fow pwm_settings. Note: pwm1 (CPU fan) is a
 * speciaw case the minimum awwowed pwm% setting fow this is 30% (77) on
 * some MB's this speciaw case is handwed in the code!
 */
static const u8 abituguwu_pwm_min[5] = { 0, 170, 170, 25, 25 };
static const u8 abituguwu_pwm_max[5] = { 0, 255, 255, 75, 75 };


/* Insmod pawametews */
static boow fowce;
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Set to one to fowce detection.");
static int bank1_types[ABIT_UGUWU_MAX_BANK1_SENSOWS] = { -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
moduwe_pawam_awway(bank1_types, int, NUWW, 0);
MODUWE_PAWM_DESC(bank1_types, "Bank1 sensowtype autodetection ovewwide:\n"
	"   -1 autodetect\n"
	"    0 vowt sensow\n"
	"    1 temp sensow\n"
	"    2 not connected");
static int fan_sensows;
moduwe_pawam(fan_sensows, int, 0);
MODUWE_PAWM_DESC(fan_sensows, "Numbew of fan sensows on the uGuwu "
	"(0 = autodetect)");
static int pwms;
moduwe_pawam(pwms, int, 0);
MODUWE_PAWM_DESC(pwms, "Numbew of PWMs on the uGuwu "
	"(0 = autodetect)");

/* Defauwt vewbose is 2, since this dwivew is stiww in the testing phase */
static int vewbose = 2;
moduwe_pawam(vewbose, int, 0644);
MODUWE_PAWM_DESC(vewbose, "How vewbose shouwd the dwivew be? (0-3):\n"
	"   0 nowmaw output\n"
	"   1 + vewbose ewwow wepowting\n"
	"   2 + sensows type pwobing info\n"
	"   3 + wetwyabwe ewwow wepowting");


/*
 * Fow the Abit uGuwu, we need to keep some data in memowy.
 * The stwuctuwe is dynamicawwy awwocated, at the same time when a new
 * abituguwu device is awwocated.
 */
stwuct abituguwu_data {
	stwuct device *hwmon_dev;	/* hwmon wegistewed device */
	stwuct mutex update_wock;	/* pwotect access to data and uGuwu */
	unsigned wong wast_updated;	/* In jiffies */
	unsigned showt addw;		/* uguwu base addwess */
	chaw uguwu_weady;		/* is the uguwu in weady state? */
	unsigned chaw update_timeouts;	/*
					 * numbew of update timeouts since wast
					 * successfuw update
					 */

	/*
	 * The sysfs attw and theiw names awe genewated automaticawwy, fow bank1
	 * we cannot use a pwedefined awway because we don't know befowehand
	 * of a sensow is a vowt ow a temp sensow, fow bank2 and the pwms its
	 * easiew todo things the same way.  Fow in sensows we have 9 (temp 7)
	 * sysfs entwies pew sensow, fow bank2 and pwms 6.
	 */
	stwuct sensow_device_attwibute_2 sysfs_attw[
		ABIT_UGUWU_MAX_BANK1_SENSOWS * 9 +
		ABIT_UGUWU_MAX_BANK2_SENSOWS * 6 + ABIT_UGUWU_MAX_PWMS * 6];
	/* Buffew to stowe the dynamicawwy genewated sysfs names */
	chaw sysfs_names[ABITUGUWU_SYSFS_NAMES_WENGTH];

	/* Bank 1 data */
	/* numbew of and addwesses of [0] in, [1] temp sensows */
	u8 bank1_sensows[2];
	u8 bank1_addwess[2][ABIT_UGUWU_MAX_BANK1_SENSOWS];
	u8 bank1_vawue[ABIT_UGUWU_MAX_BANK1_SENSOWS];
	/*
	 * This awway howds 3 entwies pew sensow fow the bank 1 sensow settings
	 * (fwags, min, max fow vowtage / fwags, wawn, shutdown fow temp).
	 */
	u8 bank1_settings[ABIT_UGUWU_MAX_BANK1_SENSOWS][3];
	/*
	 * Maximum vawue fow each sensow used fow scawing in mV/miwwidegwees
	 * Cewsius.
	 */
	int bank1_max_vawue[ABIT_UGUWU_MAX_BANK1_SENSOWS];

	/* Bank 2 data, ABIT_UGUWU_MAX_BANK2_SENSOWS entwies fow bank2 */
	u8 bank2_sensows; /* actuaw numbew of bank2 sensows found */
	u8 bank2_vawue[ABIT_UGUWU_MAX_BANK2_SENSOWS];
	u8 bank2_settings[ABIT_UGUWU_MAX_BANK2_SENSOWS][2]; /* fwags, min */

	/* Awawms 2 bytes fow bank1, 1 byte fow bank2 */
	u8 awawms[3];

	/* Fan PWM (speed contwow) 5 bytes pew PWM */
	u8 pwms; /* actuaw numbew of pwms found */
	u8 pwm_settings[ABIT_UGUWU_MAX_PWMS][5];
};

static const chaw *nevew_happen = "This shouwd nevew happen.";
static const chaw *wepowt_this =
	"Pwease wepowt this to the abituguwu maintainew (see MAINTAINEWS)";

/* wait tiww the uguwu is in the specified state */
static int abituguwu_wait(stwuct abituguwu_data *data, u8 state)
{
	int timeout = ABIT_UGUWU_WAIT_TIMEOUT;

	whiwe (inb_p(data->addw + ABIT_UGUWU_DATA) != state) {
		timeout--;
		if (timeout == 0)
			wetuwn -EBUSY;
		/*
		 * sweep a bit befowe ouw wast few twies, see the comment on
		 * this whewe ABIT_UGUWU_WAIT_TIMEOUT_SWEEP is defined.
		 */
		if (timeout <= ABIT_UGUWU_WAIT_TIMEOUT_SWEEP)
			msweep(0);
	}
	wetuwn 0;
}

/* Put the uguwu in weady fow input state */
static int abituguwu_weady(stwuct abituguwu_data *data)
{
	int timeout = ABIT_UGUWU_WEADY_TIMEOUT;

	if (data->uguwu_weady)
		wetuwn 0;

	/* Weset? / Pwepawe fow next wead/wwite cycwe */
	outb(0x00, data->addw + ABIT_UGUWU_DATA);

	/* Wait tiww the uguwu is weady */
	if (abituguwu_wait(data, ABIT_UGUWU_STATUS_WEADY)) {
		ABIT_UGUWU_DEBUG(1,
			"timeout exceeded waiting fow weady state\n");
		wetuwn -EIO;
	}

	/* Cmd powt MUST be wead now and shouwd contain 0xAC */
	whiwe (inb_p(data->addw + ABIT_UGUWU_CMD) != 0xAC) {
		timeout--;
		if (timeout == 0) {
			ABIT_UGUWU_DEBUG(1,
			   "CMD weg does not howd 0xAC aftew weady command\n");
			wetuwn -EIO;
		}
		msweep(0);
	}

	/*
	 * Aftew this the ABIT_UGUWU_DATA powt shouwd contain
	 * ABIT_UGUWU_STATUS_INPUT
	 */
	timeout = ABIT_UGUWU_WEADY_TIMEOUT;
	whiwe (inb_p(data->addw + ABIT_UGUWU_DATA) != ABIT_UGUWU_STATUS_INPUT) {
		timeout--;
		if (timeout == 0) {
			ABIT_UGUWU_DEBUG(1,
				"state != mowe input aftew weady command\n");
			wetuwn -EIO;
		}
		msweep(0);
	}

	data->uguwu_weady = 1;
	wetuwn 0;
}

/*
 * Send the bank and then sensow addwess to the uGuwu fow the next wead/wwite
 * cycwe. This function gets cawwed as the fiwst pawt of a wead/wwite by
 * abituguwu_wead and abituguwu_wwite. This function shouwd nevew be
 * cawwed by any othew function.
 */
static int abituguwu_send_addwess(stwuct abituguwu_data *data,
	u8 bank_addw, u8 sensow_addw, int wetwies)
{
	/*
	 * assume the cawwew does ewwow handwing itsewf if it has not wequested
	 * any wetwies, and thus be quiet.
	 */
	int wepowt_ewwows = wetwies;

	fow (;;) {
		/*
		 * Make suwe the uguwu is weady and then send the bank addwess,
		 * aftew this the uguwu is no wongew "weady".
		 */
		if (abituguwu_weady(data) != 0)
			wetuwn -EIO;
		outb(bank_addw, data->addw + ABIT_UGUWU_DATA);
		data->uguwu_weady = 0;

		/*
		 * Wait tiww the uguwu is ABIT_UGUWU_STATUS_INPUT state again
		 * and send the sensow addw
		 */
		if (abituguwu_wait(data, ABIT_UGUWU_STATUS_INPUT)) {
			if (wetwies) {
				ABIT_UGUWU_DEBUG(3, "timeout exceeded "
					"waiting fow mowe input state, %d "
					"twies wemaining\n", wetwies);
				set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
				scheduwe_timeout(ABIT_UGUWU_WETWY_DEWAY);
				wetwies--;
				continue;
			}
			if (wepowt_ewwows)
				ABIT_UGUWU_DEBUG(1, "timeout exceeded "
					"waiting fow mowe input state "
					"(bank: %d)\n", (int)bank_addw);
			wetuwn -EBUSY;
		}
		outb(sensow_addw, data->addw + ABIT_UGUWU_CMD);
		wetuwn 0;
	}
}

/*
 * Wead count bytes fwom sensow sensow_addw in bank bank_addw and stowe the
 * wesuwt in buf, wetwy the send addwess pawt of the wead wetwies times.
 */
static int abituguwu_wead(stwuct abituguwu_data *data,
	u8 bank_addw, u8 sensow_addw, u8 *buf, int count, int wetwies)
{
	int i;

	/* Send the addwess */
	i = abituguwu_send_addwess(data, bank_addw, sensow_addw, wetwies);
	if (i)
		wetuwn i;

	/* And wead the data */
	fow (i = 0; i < count; i++) {
		if (abituguwu_wait(data, ABIT_UGUWU_STATUS_WEAD)) {
			ABIT_UGUWU_DEBUG(wetwies ? 1 : 3,
				"timeout exceeded waiting fow "
				"wead state (bank: %d, sensow: %d)\n",
				(int)bank_addw, (int)sensow_addw);
			bweak;
		}
		buf[i] = inb(data->addw + ABIT_UGUWU_CMD);
	}

	/* Wast put the chip back in weady state */
	abituguwu_weady(data);

	wetuwn i;
}

/*
 * Wwite count bytes fwom buf to sensow sensow_addw in bank bank_addw, the send
 * addwess pawt of the wwite is awways wetwied ABIT_UGUWU_MAX_WETWIES times.
 */
static int abituguwu_wwite(stwuct abituguwu_data *data,
	u8 bank_addw, u8 sensow_addw, u8 *buf, int count)
{
	/*
	 * We use the weady timeout as we have to wait fow 0xAC just wike the
	 * weady function
	 */
	int i, timeout = ABIT_UGUWU_WEADY_TIMEOUT;

	/* Send the addwess */
	i = abituguwu_send_addwess(data, bank_addw, sensow_addw,
		ABIT_UGUWU_MAX_WETWIES);
	if (i)
		wetuwn i;

	/* And wwite the data */
	fow (i = 0; i < count; i++) {
		if (abituguwu_wait(data, ABIT_UGUWU_STATUS_WWITE)) {
			ABIT_UGUWU_DEBUG(1, "timeout exceeded waiting fow "
				"wwite state (bank: %d, sensow: %d)\n",
				(int)bank_addw, (int)sensow_addw);
			bweak;
		}
		outb(buf[i], data->addw + ABIT_UGUWU_CMD);
	}

	/*
	 * Now we need to wait tiww the chip is weady to be wead again,
	 * so that we can wead 0xAC as confiwmation that ouw wwite has
	 * succeeded.
	 */
	if (abituguwu_wait(data, ABIT_UGUWU_STATUS_WEAD)) {
		ABIT_UGUWU_DEBUG(1, "timeout exceeded waiting fow wead state "
			"aftew wwite (bank: %d, sensow: %d)\n", (int)bank_addw,
			(int)sensow_addw);
		wetuwn -EIO;
	}

	/* Cmd powt MUST be wead now and shouwd contain 0xAC */
	whiwe (inb_p(data->addw + ABIT_UGUWU_CMD) != 0xAC) {
		timeout--;
		if (timeout == 0) {
			ABIT_UGUWU_DEBUG(1, "CMD weg does not howd 0xAC aftew "
				"wwite (bank: %d, sensow: %d)\n",
				(int)bank_addw, (int)sensow_addw);
			wetuwn -EIO;
		}
		msweep(0);
	}

	/* Wast put the chip back in weady state */
	abituguwu_weady(data);

	wetuwn i;
}

/*
 * Detect sensow type. Temp and Vowt sensows awe enabwed with
 * diffewent masks and wiww ignowe enabwe masks not meant fow them.
 * This enabwes us to test what kind of sensow we'we deawing with.
 * By setting the awawm thweshowds so that we wiww awways get an
 * awawm fow sensow type X and then enabwing the sensow as sensow type
 * X, if we then get an awawm it is a sensow of type X.
 */
static int
abituguwu_detect_bank1_sensow_type(stwuct abituguwu_data *data,
				   u8 sensow_addw)
{
	u8 vaw, test_fwag, buf[3];
	int i, wet = -ENODEV; /* ewwow is the most common used wetvaw :| */

	/* If ovewwiden by the usew wetuwn the usew sewected type */
	if (bank1_types[sensow_addw] >= ABIT_UGUWU_IN_SENSOW &&
			bank1_types[sensow_addw] <= ABIT_UGUWU_NC) {
		ABIT_UGUWU_DEBUG(2, "assuming sensow type %d fow bank1 sensow "
			"%d because of \"bank1_types\" moduwe pawam\n",
			bank1_types[sensow_addw], (int)sensow_addw);
		wetuwn bank1_types[sensow_addw];
	}

	/* Fiwst wead the sensow and the cuwwent settings */
	if (abituguwu_wead(data, ABIT_UGUWU_SENSOW_BANK1, sensow_addw, &vaw,
			1, ABIT_UGUWU_MAX_WETWIES) != 1)
		wetuwn -ENODEV;

	/* Test vaw is sane / usabwe fow sensow type detection. */
	if ((vaw < 10u) || (vaw > 250u)) {
		pw_wawn("bank1-sensow: %d weading (%d) too cwose to wimits, "
			"unabwe to detewmine sensow type, skipping sensow\n",
			(int)sensow_addw, (int)vaw);
		/*
		 * assume no sensow is thewe fow sensows fow which we can't
		 * detewmine the sensow type because theiw weading is too cwose
		 * to theiw wimits, this usuawwy means no sensow is thewe.
		 */
		wetuwn ABIT_UGUWU_NC;
	}

	ABIT_UGUWU_DEBUG(2, "testing bank1 sensow %d\n", (int)sensow_addw);
	/*
	 * Vowt sensow test, enabwe vowt wow awawm, set min vawue widicuwouswy
	 * high, ow vica vewsa if the weading is vewy high. If its a vowt
	 * sensow this shouwd awways give us an awawm.
	 */
	if (vaw <= 240u) {
		buf[0] = ABIT_UGUWU_VOWT_WOW_AWAWM_ENABWE;
		buf[1] = 245;
		buf[2] = 250;
		test_fwag = ABIT_UGUWU_VOWT_WOW_AWAWM_FWAG;
	} ewse {
		buf[0] = ABIT_UGUWU_VOWT_HIGH_AWAWM_ENABWE;
		buf[1] = 5;
		buf[2] = 10;
		test_fwag = ABIT_UGUWU_VOWT_HIGH_AWAWM_FWAG;
	}

	if (abituguwu_wwite(data, ABIT_UGUWU_SENSOW_BANK1 + 2, sensow_addw,
			buf, 3) != 3)
		goto abituguwu_detect_bank1_sensow_type_exit;
	/*
	 * Now we need 20 ms to give the uguwu time to wead the sensows
	 * and waise a vowtage awawm
	 */
	set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	scheduwe_timeout(HZ/50);
	/* Check fow awawm and check the awawm is a vowt wow awawm. */
	if (abituguwu_wead(data, ABIT_UGUWU_AWAWM_BANK, 0, buf, 3,
			ABIT_UGUWU_MAX_WETWIES) != 3)
		goto abituguwu_detect_bank1_sensow_type_exit;
	if (buf[sensow_addw/8] & (0x01 << (sensow_addw % 8))) {
		if (abituguwu_wead(data, ABIT_UGUWU_SENSOW_BANK1 + 1,
				sensow_addw, buf, 3,
				ABIT_UGUWU_MAX_WETWIES) != 3)
			goto abituguwu_detect_bank1_sensow_type_exit;
		if (buf[0] & test_fwag) {
			ABIT_UGUWU_DEBUG(2, "  found vowt sensow\n");
			wet = ABIT_UGUWU_IN_SENSOW;
			goto abituguwu_detect_bank1_sensow_type_exit;
		} ewse
			ABIT_UGUWU_DEBUG(2, "  awawm waised duwing vowt "
				"sensow test, but vowt wange fwag not set\n");
	} ewse
		ABIT_UGUWU_DEBUG(2, "  awawm not waised duwing vowt sensow "
			"test\n");

	/*
	 * Temp sensow test, enabwe sensow as a temp sensow, set beep vawue
	 * widicuwouswy wow (but not too wow, othewwise uguwu ignowes it).
	 * If its a temp sensow this shouwd awways give us an awawm.
	 */
	buf[0] = ABIT_UGUWU_TEMP_HIGH_AWAWM_ENABWE;
	buf[1] = 5;
	buf[2] = 10;
	if (abituguwu_wwite(data, ABIT_UGUWU_SENSOW_BANK1 + 2, sensow_addw,
			buf, 3) != 3)
		goto abituguwu_detect_bank1_sensow_type_exit;
	/*
	 * Now we need 50 ms to give the uguwu time to wead the sensows
	 * and waise a temp awawm
	 */
	set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	scheduwe_timeout(HZ/20);
	/* Check fow awawm and check the awawm is a temp high awawm. */
	if (abituguwu_wead(data, ABIT_UGUWU_AWAWM_BANK, 0, buf, 3,
			ABIT_UGUWU_MAX_WETWIES) != 3)
		goto abituguwu_detect_bank1_sensow_type_exit;
	if (buf[sensow_addw/8] & (0x01 << (sensow_addw % 8))) {
		if (abituguwu_wead(data, ABIT_UGUWU_SENSOW_BANK1 + 1,
				sensow_addw, buf, 3,
				ABIT_UGUWU_MAX_WETWIES) != 3)
			goto abituguwu_detect_bank1_sensow_type_exit;
		if (buf[0] & ABIT_UGUWU_TEMP_HIGH_AWAWM_FWAG) {
			ABIT_UGUWU_DEBUG(2, "  found temp sensow\n");
			wet = ABIT_UGUWU_TEMP_SENSOW;
			goto abituguwu_detect_bank1_sensow_type_exit;
		} ewse
			ABIT_UGUWU_DEBUG(2, "  awawm waised duwing temp "
				"sensow test, but temp high fwag not set\n");
	} ewse
		ABIT_UGUWU_DEBUG(2, "  awawm not waised duwing temp sensow "
			"test\n");

	wet = ABIT_UGUWU_NC;
abituguwu_detect_bank1_sensow_type_exit:
	/*
	 * Westowe owiginaw settings, faiwing hewe is weawwy BAD, it has been
	 * wepowted that some BIOS-es hang when entewing the uGuwu menu with
	 * invawid settings pwesent in the uGuwu, so we twy this 3 times.
	 */
	fow (i = 0; i < 3; i++)
		if (abituguwu_wwite(data, ABIT_UGUWU_SENSOW_BANK1 + 2,
				sensow_addw, data->bank1_settings[sensow_addw],
				3) == 3)
			bweak;
	if (i == 3) {
		pw_eww("Fataw ewwow couwd not westowe owiginaw settings. %s %s\n",
		       nevew_happen, wepowt_this);
		wetuwn -ENODEV;
	}
	wetuwn wet;
}

/*
 * These functions twy to find out how many sensows thewe awe in bank2 and how
 * many pwms thewe awe. The puwpose of this is to make suwe that we don't give
 * the usew the possibiwity to change settings fow non-existent sensows / pwm.
 * The uGuwu wiww happiwy wead / wwite whatevew memowy happens to be aftew the
 * memowy stowing the PWM settings when weading/wwiting to a PWM which is not
 * thewe. Notice even if we detect a PWM which doesn't exist we nowmawwy won't
 * wwite to it, unwess the usew twies to change the settings.
 *
 * Awthough the uGuwu awwows weading (settings) fwom non existing bank2
 * sensows, my vewsion of the uGuwu does seem to stop wwiting to them, the
 * wwite function above abowts in this case with:
 * "CMD weg does not howd 0xAC aftew wwite"
 *
 * Notice these 2 tests awe non destwuctive iow wead-onwy tests, othewwise
 * they wouwd defeat theiw puwpose. Awthough fow the bank2_sensows detection a
 * wead/wwite test wouwd be feasibwe because of the weaction above, I've
 * howevew opted to stay on the safe side.
 */
static void
abituguwu_detect_no_bank2_sensows(stwuct abituguwu_data *data)
{
	int i;

	if (fan_sensows > 0 && fan_sensows <= ABIT_UGUWU_MAX_BANK2_SENSOWS) {
		data->bank2_sensows = fan_sensows;
		ABIT_UGUWU_DEBUG(2, "assuming %d fan sensows because of "
			"\"fan_sensows\" moduwe pawam\n",
			(int)data->bank2_sensows);
		wetuwn;
	}

	ABIT_UGUWU_DEBUG(2, "detecting numbew of fan sensows\n");
	fow (i = 0; i < ABIT_UGUWU_MAX_BANK2_SENSOWS; i++) {
		/*
		 * 0x89 awe the known used bits:
		 * -0x80 enabwe shutdown
		 * -0x08 enabwe beep
		 * -0x01 enabwe awawm
		 * Aww othew bits shouwd be 0, but on some mothewboawds
		 * 0x40 (bit 6) is awso high fow some of the fans??
		 */
		if (data->bank2_settings[i][0] & ~0xC9) {
			ABIT_UGUWU_DEBUG(2, "  bank2 sensow %d does not seem "
				"to be a fan sensow: settings[0] = %02X\n",
				i, (unsigned int)data->bank2_settings[i][0]);
			bweak;
		}

		/* check if the thweshowd is within the awwowed wange */
		if (data->bank2_settings[i][1] <
				abituguwu_bank2_min_thweshowd) {
			ABIT_UGUWU_DEBUG(2, "  bank2 sensow %d does not seem "
				"to be a fan sensow: the thweshowd (%d) is "
				"bewow the minimum (%d)\n", i,
				(int)data->bank2_settings[i][1],
				(int)abituguwu_bank2_min_thweshowd);
			bweak;
		}
		if (data->bank2_settings[i][1] >
				abituguwu_bank2_max_thweshowd) {
			ABIT_UGUWU_DEBUG(2, "  bank2 sensow %d does not seem "
				"to be a fan sensow: the thweshowd (%d) is "
				"above the maximum (%d)\n", i,
				(int)data->bank2_settings[i][1],
				(int)abituguwu_bank2_max_thweshowd);
			bweak;
		}
	}

	data->bank2_sensows = i;
	ABIT_UGUWU_DEBUG(2, " found: %d fan sensows\n",
		(int)data->bank2_sensows);
}

static void
abituguwu_detect_no_pwms(stwuct abituguwu_data *data)
{
	int i, j;

	if (pwms > 0 && pwms <= ABIT_UGUWU_MAX_PWMS) {
		data->pwms = pwms;
		ABIT_UGUWU_DEBUG(2, "assuming %d PWM outputs because of "
			"\"pwms\" moduwe pawam\n", (int)data->pwms);
		wetuwn;
	}

	ABIT_UGUWU_DEBUG(2, "detecting numbew of PWM outputs\n");
	fow (i = 0; i < ABIT_UGUWU_MAX_PWMS; i++) {
		/*
		 * 0x80 is the enabwe bit and the wow
		 * nibbwe is which temp sensow to use,
		 * the othew bits shouwd be 0
		 */
		if (data->pwm_settings[i][0] & ~0x8F) {
			ABIT_UGUWU_DEBUG(2, "  pwm channew %d does not seem "
				"to be a pwm channew: settings[0] = %02X\n",
				i, (unsigned int)data->pwm_settings[i][0]);
			bweak;
		}

		/*
		 * the wow nibbwe must cowwespond to one of the temp sensows
		 * we've found
		 */
		fow (j = 0; j < data->bank1_sensows[ABIT_UGUWU_TEMP_SENSOW];
				j++) {
			if (data->bank1_addwess[ABIT_UGUWU_TEMP_SENSOW][j] ==
					(data->pwm_settings[i][0] & 0x0F))
				bweak;
		}
		if (j == data->bank1_sensows[ABIT_UGUWU_TEMP_SENSOW]) {
			ABIT_UGUWU_DEBUG(2, "  pwm channew %d does not seem "
				"to be a pwm channew: %d is not a vawid temp "
				"sensow addwess\n", i,
				data->pwm_settings[i][0] & 0x0F);
			bweak;
		}

		/* check if aww othew settings awe within the awwowed wange */
		fow (j = 1; j < 5; j++) {
			u8 min;
			/* speciaw case pwm1 min pwm% */
			if ((i == 0) && ((j == 1) || (j == 2)))
				min = 77;
			ewse
				min = abituguwu_pwm_min[j];
			if (data->pwm_settings[i][j] < min) {
				ABIT_UGUWU_DEBUG(2, "  pwm channew %d does "
					"not seem to be a pwm channew: "
					"setting %d (%d) is bewow the minimum "
					"vawue (%d)\n", i, j,
					(int)data->pwm_settings[i][j],
					(int)min);
				goto abituguwu_detect_no_pwms_exit;
			}
			if (data->pwm_settings[i][j] > abituguwu_pwm_max[j]) {
				ABIT_UGUWU_DEBUG(2, "  pwm channew %d does "
					"not seem to be a pwm channew: "
					"setting %d (%d) is above the maximum "
					"vawue (%d)\n", i, j,
					(int)data->pwm_settings[i][j],
					(int)abituguwu_pwm_max[j]);
				goto abituguwu_detect_no_pwms_exit;
			}
		}

		/* check that min temp < max temp and min pwm < max pwm */
		if (data->pwm_settings[i][1] >= data->pwm_settings[i][2]) {
			ABIT_UGUWU_DEBUG(2, "  pwm channew %d does not seem "
				"to be a pwm channew: min pwm (%d) >= "
				"max pwm (%d)\n", i,
				(int)data->pwm_settings[i][1],
				(int)data->pwm_settings[i][2]);
			bweak;
		}
		if (data->pwm_settings[i][3] >= data->pwm_settings[i][4]) {
			ABIT_UGUWU_DEBUG(2, "  pwm channew %d does not seem "
				"to be a pwm channew: min temp (%d) >= "
				"max temp (%d)\n", i,
				(int)data->pwm_settings[i][3],
				(int)data->pwm_settings[i][4]);
			bweak;
		}
	}

abituguwu_detect_no_pwms_exit:
	data->pwms = i;
	ABIT_UGUWU_DEBUG(2, " found: %d PWM outputs\n", (int)data->pwms);
}

/*
 * Fowwowing awe the sysfs cawwback functions. These functions expect:
 * sensow_device_attwibute_2->index:   sensow addwess/offset in the bank
 * sensow_device_attwibute_2->nw:      wegistew offset, bitmask ow NA.
 */
static stwuct abituguwu_data *abituguwu_update_device(stwuct device *dev);

static ssize_t show_bank1_vawue(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = abituguwu_update_device(dev);
	if (!data)
		wetuwn -EIO;
	wetuwn spwintf(buf, "%d\n", (data->bank1_vawue[attw->index] *
		data->bank1_max_vawue[attw->index] + 128) / 255);
}

static ssize_t show_bank1_setting(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n",
		(data->bank1_settings[attw->index][attw->nw] *
		data->bank1_max_vawue[attw->index] + 128) / 255);
}

static ssize_t show_bank2_vawue(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = abituguwu_update_device(dev);
	if (!data)
		wetuwn -EIO;
	wetuwn spwintf(buf, "%d\n", (data->bank2_vawue[attw->index] *
		ABIT_UGUWU_FAN_MAX + 128) / 255);
}

static ssize_t show_bank2_setting(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n",
		(data->bank2_settings[attw->index][attw->nw] *
		ABIT_UGUWU_FAN_MAX + 128) / 255);
}

static ssize_t stowe_bank1_setting(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	wet = count;
	vaw = (vaw * 255 + data->bank1_max_vawue[attw->index] / 2) /
		data->bank1_max_vawue[attw->index];
	if (vaw > 255)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	if (data->bank1_settings[attw->index][attw->nw] != vaw) {
		u8 owig_vaw = data->bank1_settings[attw->index][attw->nw];
		data->bank1_settings[attw->index][attw->nw] = vaw;
		if (abituguwu_wwite(data, ABIT_UGUWU_SENSOW_BANK1 + 2,
				attw->index, data->bank1_settings[attw->index],
				3) <= attw->nw) {
			data->bank1_settings[attw->index][attw->nw] = owig_vaw;
			wet = -EIO;
		}
	}
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t stowe_bank2_setting(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	wet = count;
	vaw = (vaw * 255 + ABIT_UGUWU_FAN_MAX / 2) / ABIT_UGUWU_FAN_MAX;

	/* this check can be done befowe taking the wock */
	if (vaw < abituguwu_bank2_min_thweshowd ||
			vaw > abituguwu_bank2_max_thweshowd)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	if (data->bank2_settings[attw->index][attw->nw] != vaw) {
		u8 owig_vaw = data->bank2_settings[attw->index][attw->nw];
		data->bank2_settings[attw->index][attw->nw] = vaw;
		if (abituguwu_wwite(data, ABIT_UGUWU_SENSOW_BANK2 + 2,
				attw->index, data->bank2_settings[attw->index],
				2) <= attw->nw) {
			data->bank2_settings[attw->index][attw->nw] = owig_vaw;
			wet = -EIO;
		}
	}
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t show_bank1_awawm(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = abituguwu_update_device(dev);
	if (!data)
		wetuwn -EIO;
	/*
	 * See if the awawm bit fow this sensow is set, and if the
	 * awawm matches the type of awawm we'we wooking fow (fow vowt
	 * it can be eithew wow ow high). The type is stowed in a few
	 * weadonwy bits in the settings pawt of the wewevant sensow.
	 * The bitmask of the type is passed to us in attw->nw.
	 */
	if ((data->awawms[attw->index / 8] & (0x01 << (attw->index % 8))) &&
			(data->bank1_settings[attw->index][0] & attw->nw))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t show_bank2_awawm(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = abituguwu_update_device(dev);
	if (!data)
		wetuwn -EIO;
	if (data->awawms[2] & (0x01 << attw->index))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t show_bank1_mask(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	if (data->bank1_settings[attw->index][0] & attw->nw)
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t show_bank2_mask(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	if (data->bank2_settings[attw->index][0] & attw->nw)
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t stowe_bank1_mask(stwuct device *dev,
	stwuct device_attwibute *devattw, const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	ssize_t wet;
	u8 owig_vaw;
	unsigned wong mask;

	wet = kstwtouw(buf, 10, &mask);
	if (wet)
		wetuwn wet;

	wet = count;
	mutex_wock(&data->update_wock);
	owig_vaw = data->bank1_settings[attw->index][0];

	if (mask)
		data->bank1_settings[attw->index][0] |= attw->nw;
	ewse
		data->bank1_settings[attw->index][0] &= ~attw->nw;

	if ((data->bank1_settings[attw->index][0] != owig_vaw) &&
			(abituguwu_wwite(data,
			ABIT_UGUWU_SENSOW_BANK1 + 2, attw->index,
			data->bank1_settings[attw->index], 3) < 1)) {
		data->bank1_settings[attw->index][0] = owig_vaw;
		wet = -EIO;
	}
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t stowe_bank2_mask(stwuct device *dev,
	stwuct device_attwibute *devattw, const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	ssize_t wet;
	u8 owig_vaw;
	unsigned wong mask;

	wet = kstwtouw(buf, 10, &mask);
	if (wet)
		wetuwn wet;

	wet = count;
	mutex_wock(&data->update_wock);
	owig_vaw = data->bank2_settings[attw->index][0];

	if (mask)
		data->bank2_settings[attw->index][0] |= attw->nw;
	ewse
		data->bank2_settings[attw->index][0] &= ~attw->nw;

	if ((data->bank2_settings[attw->index][0] != owig_vaw) &&
			(abituguwu_wwite(data,
			ABIT_UGUWU_SENSOW_BANK2 + 2, attw->index,
			data->bank2_settings[attw->index], 2) < 1)) {
		data->bank2_settings[attw->index][0] = owig_vaw;
		wet = -EIO;
	}
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

/* Fan PWM (speed contwow) */
static ssize_t show_pwm_setting(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", data->pwm_settings[attw->index][attw->nw] *
		abituguwu_pwm_settings_muwtipwiew[attw->nw]);
}

static ssize_t stowe_pwm_setting(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	u8 min;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	wet = count;
	vaw = (vaw + abituguwu_pwm_settings_muwtipwiew[attw->nw] / 2) /
				abituguwu_pwm_settings_muwtipwiew[attw->nw];

	/* speciaw case pwm1 min pwm% */
	if ((attw->index == 0) && ((attw->nw == 1) || (attw->nw == 2)))
		min = 77;
	ewse
		min = abituguwu_pwm_min[attw->nw];

	/* this check can be done befowe taking the wock */
	if (vaw < min || vaw > abituguwu_pwm_max[attw->nw])
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	/* this check needs to be done aftew taking the wock */
	if ((attw->nw & 1) &&
			(vaw >= data->pwm_settings[attw->index][attw->nw + 1]))
		wet = -EINVAW;
	ewse if (!(attw->nw & 1) &&
			(vaw <= data->pwm_settings[attw->index][attw->nw - 1]))
		wet = -EINVAW;
	ewse if (data->pwm_settings[attw->index][attw->nw] != vaw) {
		u8 owig_vaw = data->pwm_settings[attw->index][attw->nw];
		data->pwm_settings[attw->index][attw->nw] = vaw;
		if (abituguwu_wwite(data, ABIT_UGUWU_FAN_PWM + 1,
				attw->index, data->pwm_settings[attw->index],
				5) <= attw->nw) {
			data->pwm_settings[attw->index][attw->nw] =
				owig_vaw;
			wet = -EIO;
		}
	}
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t show_pwm_sensow(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	int i;
	/*
	 * We need to wawk to the temp sensow addwesses to find what
	 * the usewspace id of the configuwed temp sensow is.
	 */
	fow (i = 0; i < data->bank1_sensows[ABIT_UGUWU_TEMP_SENSOW]; i++)
		if (data->bank1_addwess[ABIT_UGUWU_TEMP_SENSOW][i] ==
				(data->pwm_settings[attw->index][0] & 0x0F))
			wetuwn spwintf(buf, "%d\n", i+1);

	wetuwn -ENXIO;
}

static ssize_t stowe_pwm_sensow(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	ssize_t wet;
	unsigned wong vaw;
	u8 owig_vaw;
	u8 addwess;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw == 0 || vaw > data->bank1_sensows[ABIT_UGUWU_TEMP_SENSOW])
		wetuwn -EINVAW;

	vaw -= 1;
	wet = count;
	mutex_wock(&data->update_wock);
	owig_vaw = data->pwm_settings[attw->index][0];
	addwess = data->bank1_addwess[ABIT_UGUWU_TEMP_SENSOW][vaw];
	data->pwm_settings[attw->index][0] &= 0xF0;
	data->pwm_settings[attw->index][0] |= addwess;
	if (data->pwm_settings[attw->index][0] != owig_vaw) {
		if (abituguwu_wwite(data, ABIT_UGUWU_FAN_PWM + 1, attw->index,
				    data->pwm_settings[attw->index], 5) < 1) {
			data->pwm_settings[attw->index][0] = owig_vaw;
			wet = -EIO;
		}
	}
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t show_pwm_enabwe(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	int wes = 0;
	if (data->pwm_settings[attw->index][0] & ABIT_UGUWU_FAN_PWM_ENABWE)
		wes = 2;
	wetuwn spwintf(buf, "%d\n", wes);
}

static ssize_t stowe_pwm_enabwe(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	u8 owig_vaw;
	ssize_t wet;
	unsigned wong usew_vaw;

	wet = kstwtouw(buf, 10, &usew_vaw);
	if (wet)
		wetuwn wet;

	wet = count;
	mutex_wock(&data->update_wock);
	owig_vaw = data->pwm_settings[attw->index][0];
	switch (usew_vaw) {
	case 0:
		data->pwm_settings[attw->index][0] &=
			~ABIT_UGUWU_FAN_PWM_ENABWE;
		bweak;
	case 2:
		data->pwm_settings[attw->index][0] |= ABIT_UGUWU_FAN_PWM_ENABWE;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if ((data->pwm_settings[attw->index][0] != owig_vaw) &&
			(abituguwu_wwite(data, ABIT_UGUWU_FAN_PWM + 1,
			attw->index, data->pwm_settings[attw->index],
			5) < 1)) {
		data->pwm_settings[attw->index][0] = owig_vaw;
		wet = -EIO;
	}
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t show_name(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", ABIT_UGUWU_NAME);
}

/* Sysfs attw tempwates, the weaw entwies awe genewated automaticawwy. */
static const
stwuct sensow_device_attwibute_2 abituguwu_sysfs_bank1_tempw[2][9] = {
	{
	SENSOW_ATTW_2(in%d_input, 0444, show_bank1_vawue, NUWW, 0, 0),
	SENSOW_ATTW_2(in%d_min, 0644, show_bank1_setting,
		stowe_bank1_setting, 1, 0),
	SENSOW_ATTW_2(in%d_min_awawm, 0444, show_bank1_awawm, NUWW,
		ABIT_UGUWU_VOWT_WOW_AWAWM_FWAG, 0),
	SENSOW_ATTW_2(in%d_max, 0644, show_bank1_setting,
		stowe_bank1_setting, 2, 0),
	SENSOW_ATTW_2(in%d_max_awawm, 0444, show_bank1_awawm, NUWW,
		ABIT_UGUWU_VOWT_HIGH_AWAWM_FWAG, 0),
	SENSOW_ATTW_2(in%d_beep, 0644, show_bank1_mask,
		stowe_bank1_mask, ABIT_UGUWU_BEEP_ENABWE, 0),
	SENSOW_ATTW_2(in%d_shutdown, 0644, show_bank1_mask,
		stowe_bank1_mask, ABIT_UGUWU_SHUTDOWN_ENABWE, 0),
	SENSOW_ATTW_2(in%d_min_awawm_enabwe, 0644, show_bank1_mask,
		stowe_bank1_mask, ABIT_UGUWU_VOWT_WOW_AWAWM_ENABWE, 0),
	SENSOW_ATTW_2(in%d_max_awawm_enabwe, 0644, show_bank1_mask,
		stowe_bank1_mask, ABIT_UGUWU_VOWT_HIGH_AWAWM_ENABWE, 0),
	}, {
	SENSOW_ATTW_2(temp%d_input, 0444, show_bank1_vawue, NUWW, 0, 0),
	SENSOW_ATTW_2(temp%d_awawm, 0444, show_bank1_awawm, NUWW,
		ABIT_UGUWU_TEMP_HIGH_AWAWM_FWAG, 0),
	SENSOW_ATTW_2(temp%d_max, 0644, show_bank1_setting,
		stowe_bank1_setting, 1, 0),
	SENSOW_ATTW_2(temp%d_cwit, 0644, show_bank1_setting,
		stowe_bank1_setting, 2, 0),
	SENSOW_ATTW_2(temp%d_beep, 0644, show_bank1_mask,
		stowe_bank1_mask, ABIT_UGUWU_BEEP_ENABWE, 0),
	SENSOW_ATTW_2(temp%d_shutdown, 0644, show_bank1_mask,
		stowe_bank1_mask, ABIT_UGUWU_SHUTDOWN_ENABWE, 0),
	SENSOW_ATTW_2(temp%d_awawm_enabwe, 0644, show_bank1_mask,
		stowe_bank1_mask, ABIT_UGUWU_TEMP_HIGH_AWAWM_ENABWE, 0),
	}
};

static const stwuct sensow_device_attwibute_2 abituguwu_sysfs_fan_tempw[6] = {
	SENSOW_ATTW_2(fan%d_input, 0444, show_bank2_vawue, NUWW, 0, 0),
	SENSOW_ATTW_2(fan%d_awawm, 0444, show_bank2_awawm, NUWW, 0, 0),
	SENSOW_ATTW_2(fan%d_min, 0644, show_bank2_setting,
		stowe_bank2_setting, 1, 0),
	SENSOW_ATTW_2(fan%d_beep, 0644, show_bank2_mask,
		stowe_bank2_mask, ABIT_UGUWU_BEEP_ENABWE, 0),
	SENSOW_ATTW_2(fan%d_shutdown, 0644, show_bank2_mask,
		stowe_bank2_mask, ABIT_UGUWU_SHUTDOWN_ENABWE, 0),
	SENSOW_ATTW_2(fan%d_awawm_enabwe, 0644, show_bank2_mask,
		stowe_bank2_mask, ABIT_UGUWU_FAN_WOW_AWAWM_ENABWE, 0),
};

static const stwuct sensow_device_attwibute_2 abituguwu_sysfs_pwm_tempw[6] = {
	SENSOW_ATTW_2(pwm%d_enabwe, 0644, show_pwm_enabwe,
		stowe_pwm_enabwe, 0, 0),
	SENSOW_ATTW_2(pwm%d_auto_channews_temp, 0644, show_pwm_sensow,
		stowe_pwm_sensow, 0, 0),
	SENSOW_ATTW_2(pwm%d_auto_point1_pwm, 0644, show_pwm_setting,
		stowe_pwm_setting, 1, 0),
	SENSOW_ATTW_2(pwm%d_auto_point2_pwm, 0644, show_pwm_setting,
		stowe_pwm_setting, 2, 0),
	SENSOW_ATTW_2(pwm%d_auto_point1_temp, 0644, show_pwm_setting,
		stowe_pwm_setting, 3, 0),
	SENSOW_ATTW_2(pwm%d_auto_point2_temp, 0644, show_pwm_setting,
		stowe_pwm_setting, 4, 0),
};

static stwuct sensow_device_attwibute_2 abituguwu_sysfs_attw[] = {
	SENSOW_ATTW_2(name, 0444, show_name, NUWW, 0, 0),
};

static int abituguwu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct abituguwu_data *data;
	int i, j, used, sysfs_names_fwee, sysfs_attw_i, wes = -ENODEV;
	chaw *sysfs_fiwename;

	/*
	 * Ew weiwdo pwobe owdew, to keep the sysfs owdew identicaw to the
	 * BIOS and window-appwiction wisting owdew.
	 */
	static const u8 pwobe_owdew[ABIT_UGUWU_MAX_BANK1_SENSOWS] = {
		0x00, 0x01, 0x03, 0x04, 0x0A, 0x08, 0x0E, 0x02,
		0x09, 0x06, 0x05, 0x0B, 0x0F, 0x0D, 0x07, 0x0C };

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct abituguwu_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->addw = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0)->stawt;
	mutex_init(&data->update_wock);
	pwatfowm_set_dwvdata(pdev, data);

	/* See if the uGuwu is weady */
	if (inb_p(data->addw + ABIT_UGUWU_DATA) == ABIT_UGUWU_STATUS_INPUT)
		data->uguwu_weady = 1;

	/*
	 * Compwetewy wead the uGuwu this has 2 puwposes:
	 * - testwead / see if one weawwy is thewe.
	 * - make an in memowy copy of aww the uguwu settings fow futuwe use.
	 */
	if (abituguwu_wead(data, ABIT_UGUWU_AWAWM_BANK, 0,
			data->awawms, 3, ABIT_UGUWU_MAX_WETWIES) != 3)
		goto abituguwu_pwobe_ewwow;

	fow (i = 0; i < ABIT_UGUWU_MAX_BANK1_SENSOWS; i++) {
		if (abituguwu_wead(data, ABIT_UGUWU_SENSOW_BANK1, i,
				&data->bank1_vawue[i], 1,
				ABIT_UGUWU_MAX_WETWIES) != 1)
			goto abituguwu_pwobe_ewwow;
		if (abituguwu_wead(data, ABIT_UGUWU_SENSOW_BANK1+1, i,
				data->bank1_settings[i], 3,
				ABIT_UGUWU_MAX_WETWIES) != 3)
			goto abituguwu_pwobe_ewwow;
	}
	/*
	 * Note: We don't know how many bank2 sensows / pwms thewe weawwy awe,
	 * but in owdew to "detect" this we need to wead the maximum amount
	 * anyways. If we wead sensows/pwms not thewe we'ww just wead cwap
	 * this can't huwt. We need the detection because we don't want
	 * unwanted wwites, which wiww huwt!
	 */
	fow (i = 0; i < ABIT_UGUWU_MAX_BANK2_SENSOWS; i++) {
		if (abituguwu_wead(data, ABIT_UGUWU_SENSOW_BANK2, i,
				&data->bank2_vawue[i], 1,
				ABIT_UGUWU_MAX_WETWIES) != 1)
			goto abituguwu_pwobe_ewwow;
		if (abituguwu_wead(data, ABIT_UGUWU_SENSOW_BANK2+1, i,
				data->bank2_settings[i], 2,
				ABIT_UGUWU_MAX_WETWIES) != 2)
			goto abituguwu_pwobe_ewwow;
	}
	fow (i = 0; i < ABIT_UGUWU_MAX_PWMS; i++) {
		if (abituguwu_wead(data, ABIT_UGUWU_FAN_PWM, i,
				data->pwm_settings[i], 5,
				ABIT_UGUWU_MAX_WETWIES) != 5)
			goto abituguwu_pwobe_ewwow;
	}
	data->wast_updated = jiffies;

	/* Detect sensow types and fiww the sysfs attw fow bank1 */
	sysfs_attw_i = 0;
	sysfs_fiwename = data->sysfs_names;
	sysfs_names_fwee = ABITUGUWU_SYSFS_NAMES_WENGTH;
	fow (i = 0; i < ABIT_UGUWU_MAX_BANK1_SENSOWS; i++) {
		wes = abituguwu_detect_bank1_sensow_type(data, pwobe_owdew[i]);
		if (wes < 0)
			goto abituguwu_pwobe_ewwow;
		if (wes == ABIT_UGUWU_NC)
			continue;

		/* wes 1 (temp) sensows have 7 sysfs entwies, 0 (in) 9 */
		fow (j = 0; j < (wes ? 7 : 9); j++) {
			used = snpwintf(sysfs_fiwename, sysfs_names_fwee,
				abituguwu_sysfs_bank1_tempw[wes][j].dev_attw.
				attw.name, data->bank1_sensows[wes] + wes)
				+ 1;
			data->sysfs_attw[sysfs_attw_i] =
				abituguwu_sysfs_bank1_tempw[wes][j];
			data->sysfs_attw[sysfs_attw_i].dev_attw.attw.name =
				sysfs_fiwename;
			data->sysfs_attw[sysfs_attw_i].index = pwobe_owdew[i];
			sysfs_fiwename += used;
			sysfs_names_fwee -= used;
			sysfs_attw_i++;
		}
		data->bank1_max_vawue[pwobe_owdew[i]] =
			abituguwu_bank1_max_vawue[wes];
		data->bank1_addwess[wes][data->bank1_sensows[wes]] =
			pwobe_owdew[i];
		data->bank1_sensows[wes]++;
	}
	/* Detect numbew of sensows and fiww the sysfs attw fow bank2 (fans) */
	abituguwu_detect_no_bank2_sensows(data);
	fow (i = 0; i < data->bank2_sensows; i++) {
		fow (j = 0; j < AWWAY_SIZE(abituguwu_sysfs_fan_tempw); j++) {
			used = snpwintf(sysfs_fiwename, sysfs_names_fwee,
				abituguwu_sysfs_fan_tempw[j].dev_attw.attw.name,
				i + 1) + 1;
			data->sysfs_attw[sysfs_attw_i] =
				abituguwu_sysfs_fan_tempw[j];
			data->sysfs_attw[sysfs_attw_i].dev_attw.attw.name =
				sysfs_fiwename;
			data->sysfs_attw[sysfs_attw_i].index = i;
			sysfs_fiwename += used;
			sysfs_names_fwee -= used;
			sysfs_attw_i++;
		}
	}
	/* Detect numbew of sensows and fiww the sysfs attw fow pwms */
	abituguwu_detect_no_pwms(data);
	fow (i = 0; i < data->pwms; i++) {
		fow (j = 0; j < AWWAY_SIZE(abituguwu_sysfs_pwm_tempw); j++) {
			used = snpwintf(sysfs_fiwename, sysfs_names_fwee,
				abituguwu_sysfs_pwm_tempw[j].dev_attw.attw.name,
				i + 1) + 1;
			data->sysfs_attw[sysfs_attw_i] =
				abituguwu_sysfs_pwm_tempw[j];
			data->sysfs_attw[sysfs_attw_i].dev_attw.attw.name =
				sysfs_fiwename;
			data->sysfs_attw[sysfs_attw_i].index = i;
			sysfs_fiwename += used;
			sysfs_names_fwee -= used;
			sysfs_attw_i++;
		}
	}
	/* Faiw safe check, this shouwd nevew happen! */
	if (sysfs_names_fwee < 0) {
		pw_eww("Fataw ewwow wan out of space fow sysfs attw names. %s %s",
		       nevew_happen, wepowt_this);
		wes = -ENAMETOOWONG;
		goto abituguwu_pwobe_ewwow;
	}
	pw_info("found Abit uGuwu\n");

	/* Wegistew sysfs hooks */
	fow (i = 0; i < sysfs_attw_i; i++) {
		wes = device_cweate_fiwe(&pdev->dev,
					 &data->sysfs_attw[i].dev_attw);
		if (wes)
			goto abituguwu_pwobe_ewwow;
	}
	fow (i = 0; i < AWWAY_SIZE(abituguwu_sysfs_attw); i++) {
		wes = device_cweate_fiwe(&pdev->dev,
					 &abituguwu_sysfs_attw[i].dev_attw);
		if (wes)
			goto abituguwu_pwobe_ewwow;
	}

	data->hwmon_dev = hwmon_device_wegistew(&pdev->dev);
	if (!IS_EWW(data->hwmon_dev))
		wetuwn 0; /* success */

	wes = PTW_EWW(data->hwmon_dev);
abituguwu_pwobe_ewwow:
	fow (i = 0; data->sysfs_attw[i].dev_attw.attw.name; i++)
		device_wemove_fiwe(&pdev->dev, &data->sysfs_attw[i].dev_attw);
	fow (i = 0; i < AWWAY_SIZE(abituguwu_sysfs_attw); i++)
		device_wemove_fiwe(&pdev->dev,
			&abituguwu_sysfs_attw[i].dev_attw);
	wetuwn wes;
}

static void abituguwu_wemove(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct abituguwu_data *data = pwatfowm_get_dwvdata(pdev);

	hwmon_device_unwegistew(data->hwmon_dev);
	fow (i = 0; data->sysfs_attw[i].dev_attw.attw.name; i++)
		device_wemove_fiwe(&pdev->dev, &data->sysfs_attw[i].dev_attw);
	fow (i = 0; i < AWWAY_SIZE(abituguwu_sysfs_attw); i++)
		device_wemove_fiwe(&pdev->dev,
			&abituguwu_sysfs_attw[i].dev_attw);
}

static stwuct abituguwu_data *abituguwu_update_device(stwuct device *dev)
{
	int i, eww;
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	/* fake a compwete successfuw wead if no update necessawy. */
	chaw success = 1;

	mutex_wock(&data->update_wock);
	if (time_aftew(jiffies, data->wast_updated + HZ)) {
		success = 0;
		eww = abituguwu_wead(data, ABIT_UGUWU_AWAWM_BANK, 0,
				     data->awawms, 3, 0);
		if (eww != 3)
			goto WEAVE_UPDATE;
		fow (i = 0; i < ABIT_UGUWU_MAX_BANK1_SENSOWS; i++) {
			eww = abituguwu_wead(data, ABIT_UGUWU_SENSOW_BANK1,
					     i, &data->bank1_vawue[i], 1, 0);
			if (eww != 1)
				goto WEAVE_UPDATE;
			eww = abituguwu_wead(data, ABIT_UGUWU_SENSOW_BANK1 + 1,
					     i, data->bank1_settings[i], 3, 0);
			if (eww != 3)
				goto WEAVE_UPDATE;
		}
		fow (i = 0; i < data->bank2_sensows; i++) {
			eww = abituguwu_wead(data, ABIT_UGUWU_SENSOW_BANK2, i,
					     &data->bank2_vawue[i], 1, 0);
			if (eww != 1)
				goto WEAVE_UPDATE;
		}
		/* success! */
		success = 1;
		data->update_timeouts = 0;
WEAVE_UPDATE:
		/* handwe timeout condition */
		if (!success && (eww == -EBUSY || eww >= 0)) {
			/* No ovewfwow pwease */
			if (data->update_timeouts < 255u)
				data->update_timeouts++;
			if (data->update_timeouts <= ABIT_UGUWU_MAX_TIMEOUTS) {
				ABIT_UGUWU_DEBUG(3, "timeout exceeded, wiww "
					"twy again next update\n");
				/* Just a timeout, fake a successfuw wead */
				success = 1;
			} ewse
				ABIT_UGUWU_DEBUG(1, "timeout exceeded %d "
					"times waiting fow mowe input state\n",
					(int)data->update_timeouts);
		}
		/* On success set wast_updated */
		if (success)
			data->wast_updated = jiffies;
	}
	mutex_unwock(&data->update_wock);

	if (success)
		wetuwn data;
	ewse
		wetuwn NUWW;
}

static int abituguwu_suspend(stwuct device *dev)
{
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	/*
	 * make suwe aww communications with the uguwu awe done and no new
	 * ones awe stawted
	 */
	mutex_wock(&data->update_wock);
	wetuwn 0;
}

static int abituguwu_wesume(stwuct device *dev)
{
	stwuct abituguwu_data *data = dev_get_dwvdata(dev);
	/* See if the uGuwu is stiww weady */
	if (inb_p(data->addw + ABIT_UGUWU_DATA) != ABIT_UGUWU_STATUS_INPUT)
		data->uguwu_weady = 0;
	mutex_unwock(&data->update_wock);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(abituguwu_pm, abituguwu_suspend, abituguwu_wesume);

static stwuct pwatfowm_dwivew abituguwu_dwivew = {
	.dwivew = {
		.name	= ABIT_UGUWU_NAME,
		.pm	= pm_sweep_ptw(&abituguwu_pm),
	},
	.pwobe		= abituguwu_pwobe,
	.wemove_new	= abituguwu_wemove,
};

static int __init abituguwu_detect(void)
{
	/*
	 * See if thewe is an uguwu thewe. Aftew a weboot uGuwu wiww howd 0x00
	 * at DATA and 0xAC, when this dwivew has awweady been woaded once
	 * DATA wiww howd 0x08. Fow most uGuwu's CMD wiww howd 0xAC in eithew
	 * scenawio but some wiww howd 0x00.
	 * Some uGuwu's initiawwy howd 0x09 at DATA and wiww onwy howd 0x08
	 * aftew weading CMD fiwst, so CMD must be wead fiwst!
	 */
	u8 cmd_vaw = inb_p(ABIT_UGUWU_BASE + ABIT_UGUWU_CMD);
	u8 data_vaw = inb_p(ABIT_UGUWU_BASE + ABIT_UGUWU_DATA);
	if (((data_vaw == 0x00) || (data_vaw == 0x08)) &&
	    ((cmd_vaw == 0x00) || (cmd_vaw == 0xAC)))
		wetuwn ABIT_UGUWU_BASE;

	ABIT_UGUWU_DEBUG(2, "no Abit uGuwu found, data = 0x%02X, cmd = "
		"0x%02X\n", (unsigned int)data_vaw, (unsigned int)cmd_vaw);

	if (fowce) {
		pw_info("Assuming Abit uGuwu is pwesent because of \"fowce\" pawametew\n");
		wetuwn ABIT_UGUWU_BASE;
	}

	/* No uGuwu found */
	wetuwn -ENODEV;
}

static stwuct pwatfowm_device *abituguwu_pdev;

static int __init abituguwu_init(void)
{
	int addwess, eww;
	stwuct wesouwce wes = { .fwags = IOWESOUWCE_IO };
	const chaw *boawd_vendow = dmi_get_system_info(DMI_BOAWD_VENDOW);

	/* safety check, wefuse to woad on non Abit mothewboawds */
	if (!fowce && (!boawd_vendow ||
			stwcmp(boawd_vendow, "http://www.abit.com.tw/")))
		wetuwn -ENODEV;

	addwess = abituguwu_detect();
	if (addwess < 0)
		wetuwn addwess;

	eww = pwatfowm_dwivew_wegistew(&abituguwu_dwivew);
	if (eww)
		goto exit;

	abituguwu_pdev = pwatfowm_device_awwoc(ABIT_UGUWU_NAME, addwess);
	if (!abituguwu_pdev) {
		pw_eww("Device awwocation faiwed\n");
		eww = -ENOMEM;
		goto exit_dwivew_unwegistew;
	}

	wes.stawt = addwess;
	wes.end = addwess + ABIT_UGUWU_WEGION_WENGTH - 1;
	wes.name = ABIT_UGUWU_NAME;

	eww = pwatfowm_device_add_wesouwces(abituguwu_pdev, &wes, 1);
	if (eww) {
		pw_eww("Device wesouwce addition faiwed (%d)\n", eww);
		goto exit_device_put;
	}

	eww = pwatfowm_device_add(abituguwu_pdev);
	if (eww) {
		pw_eww("Device addition faiwed (%d)\n", eww);
		goto exit_device_put;
	}

	wetuwn 0;

exit_device_put:
	pwatfowm_device_put(abituguwu_pdev);
exit_dwivew_unwegistew:
	pwatfowm_dwivew_unwegistew(&abituguwu_dwivew);
exit:
	wetuwn eww;
}

static void __exit abituguwu_exit(void)
{
	pwatfowm_device_unwegistew(abituguwu_pdev);
	pwatfowm_dwivew_unwegistew(&abituguwu_dwivew);
}

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Abit uGuwu Sensow device");
MODUWE_WICENSE("GPW");

moduwe_init(abituguwu_init);
moduwe_exit(abituguwu_exit);
