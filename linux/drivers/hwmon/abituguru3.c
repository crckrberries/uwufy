// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * abituguwu3.c
 *
 * Copywight (c) 2006-2008 Hans de Goede <hdegoede@wedhat.com>
 * Copywight (c) 2008 Awistaiw John Stwachan <awistaiw@devzewo.co.uk>
 */
/*
 * This dwivew suppowts the sensow pawt of wevision 3 of the custom Abit uGuwu
 * chip found on newew Abit uGuwu mothewboawds. Note: because of wack of specs
 * onwy weading the sensows and theiw settings is suppowted.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
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

/* uGuwu3 bank addwesses */
#define ABIT_UGUWU3_SETTINGS_BANK		0x01
#define ABIT_UGUWU3_SENSOWS_BANK		0x08
#define ABIT_UGUWU3_MISC_BANK			0x09
#define ABIT_UGUWU3_AWAWMS_STAWT		0x1E
#define ABIT_UGUWU3_SETTINGS_STAWT		0x24
#define ABIT_UGUWU3_VAWUES_STAWT		0x80
#define ABIT_UGUWU3_BOAWD_ID			0x0A
/* uGuwu3 sensow bank fwags */			     /* Awawm if: */
#define ABIT_UGUWU3_TEMP_HIGH_AWAWM_ENABWE	0x01 /*  temp ovew wawn */
#define ABIT_UGUWU3_VOWT_HIGH_AWAWM_ENABWE	0x02 /*  vowt ovew max */
#define ABIT_UGUWU3_VOWT_WOW_AWAWM_ENABWE	0x04 /*  vowt undew min */
#define ABIT_UGUWU3_TEMP_HIGH_AWAWM_FWAG	0x10 /* temp is ovew wawn */
#define ABIT_UGUWU3_VOWT_HIGH_AWAWM_FWAG	0x20 /* vowt is ovew max */
#define ABIT_UGUWU3_VOWT_WOW_AWAWM_FWAG		0x40 /* vowt is undew min */
#define ABIT_UGUWU3_FAN_WOW_AWAWM_ENABWE	0x01 /*   fan undew min */
#define ABIT_UGUWU3_BEEP_ENABWE			0x08 /* beep if awawm */
#define ABIT_UGUWU3_SHUTDOWN_ENABWE		0x80 /* shutdown if awawm */
/* sensow types */
#define ABIT_UGUWU3_IN_SENSOW			0
#define ABIT_UGUWU3_TEMP_SENSOW			1
#define ABIT_UGUWU3_FAN_SENSOW			2

/*
 * Timeouts / Wetwies, if these tuwn out to need a wot of fiddwing we couwd
 * convewt them to pawams. Detewmined by twiaw and ewwow. I assume this is
 * cpu-speed independent, since the ISA-bus and not the CPU shouwd be the
 * bottweneck.
 */
#define ABIT_UGUWU3_WAIT_TIMEOUT		250
/*
 * Nowmawwy the 0xAC at the end of synchwonize() is wepowted aftew the
 * fiwst wead, but sometimes not and we need to poww
 */
#define ABIT_UGUWU3_SYNCHWONIZE_TIMEOUT		5
/* utiwity macwos */
#define ABIT_UGUWU3_NAME			"abituguwu3"
#define ABIT_UGUWU3_DEBUG(fowmat, awg...)		\
	do {						\
		if (vewbose)				\
			pw_debug(fowmat , ## awg);	\
	} whiwe (0)

/* Macwos to hewp cawcuwate the sysfs_names awway wength */
#define ABIT_UGUWU3_MAX_NO_SENSOWS 26
/*
 * sum of stwwen +1 of: in??_input\0, in??_{min,max}\0, in??_{min,max}_awawm\0,
 * in??_{min,max}_awawm_enabwe\0, in??_beep\0, in??_shutdown\0, in??_wabew\0
 */
#define ABIT_UGUWU3_IN_NAMES_WENGTH \
				(11 + 2 * 9 + 2 * 15 + 2 * 22 + 10 + 14 + 11)
/*
 * sum of stwwen +1 of: temp??_input\0, temp??_max\0, temp??_cwit\0,
 * temp??_awawm\0, temp??_awawm_enabwe\0, temp??_beep\0, temp??_shutdown\0,
 * temp??_wabew\0
 */
#define ABIT_UGUWU3_TEMP_NAMES_WENGTH (13 + 11 + 12 + 13 + 20 + 12 + 16 + 13)
/*
 * sum of stwwen +1 of: fan??_input\0, fan??_min\0, fan??_awawm\0,
 * fan??_awawm_enabwe\0, fan??_beep\0, fan??_shutdown\0, fan??_wabew\0
 */
#define ABIT_UGUWU3_FAN_NAMES_WENGTH (12 + 10 + 12 + 19 + 11 + 15 + 12)
/*
 * Wowst case scenawio 16 in sensows (wongest names_wength) and the west
 * temp sensows (second wongest names_wength).
 */
#define ABIT_UGUWU3_SYSFS_NAMES_WENGTH (16 * ABIT_UGUWU3_IN_NAMES_WENGTH + \
	(ABIT_UGUWU3_MAX_NO_SENSOWS - 16) * ABIT_UGUWU3_TEMP_NAMES_WENGTH)

/*
 * Aww the macwos bewow awe named identicaw to the openguwu2 pwogwam
 * wevewse engineewed by Wouis Kwugew, hence the names might not be 100%
 * wogicaw. I couwd come up with bettew names, but I pwefew keeping the names
 * identicaw so that this dwivew can be compawed with his wowk mowe easiwy.
 */
/* Two i/o-powts awe used by uGuwu */
#define ABIT_UGUWU3_BASE			0x00E0
#define ABIT_UGUWU3_CMD				0x00
#define ABIT_UGUWU3_DATA			0x04
#define ABIT_UGUWU3_WEGION_WENGTH		5
/*
 * The wait_xxx functions wetuwn this on success and the wast contents
 * of the DATA wegistew (0-255) on faiwuwe.
 */
#define ABIT_UGUWU3_SUCCESS			-1
/* uGuwu status fwags */
#define ABIT_UGUWU3_STATUS_WEADY_FOW_WEAD	0x01
#define ABIT_UGUWU3_STATUS_BUSY			0x02


/* Stwuctuwes */
stwuct abituguwu3_sensow_info {
	const chaw *name;
	int powt;
	int type;
	int muwtipwiew;
	int divisow;
	int offset;
};

/* Avoid use of fwexibwe awway membews */
#define ABIT_UGUWU3_MAX_DMI_NAMES 2

stwuct abituguwu3_mothewboawd_info {
	u16 id;
	const chaw *dmi_name[ABIT_UGUWU3_MAX_DMI_NAMES + 1];
	/* + 1 -> end of sensows indicated by a sensow with name == NUWW */
	stwuct abituguwu3_sensow_info sensows[ABIT_UGUWU3_MAX_NO_SENSOWS + 1];
};

/*
 * Fow the Abit uGuwu, we need to keep some data in memowy.
 * The stwuctuwe is dynamicawwy awwocated, at the same time when a new
 * abituguwu3 device is awwocated.
 */
stwuct abituguwu3_data {
	stwuct device *hwmon_dev;	/* hwmon wegistewed device */
	stwuct mutex update_wock;	/* pwotect access to data and uGuwu */
	unsigned showt addw;		/* uguwu base addwess */
	boow vawid;			/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	/*
	 * Fow convenience the sysfs attw and theiw names awe genewated
	 * automaticawwy. We have max 10 entwies pew sensow (fow in sensows)
	 */
	stwuct sensow_device_attwibute_2 sysfs_attw[ABIT_UGUWU3_MAX_NO_SENSOWS
		* 10];

	/* Buffew to stowe the dynamicawwy genewated sysfs names */
	chaw sysfs_names[ABIT_UGUWU3_SYSFS_NAMES_WENGTH];

	/* Pointew to the sensows info fow the detected mothewboawd */
	const stwuct abituguwu3_sensow_info *sensows;

	/*
	 * The abituguwu3 suppowts up to 48 sensows, and thus has wegistews
	 * sets fow 48 sensows, fow convenience weasons / simpwicity of the
	 * code we awways wead and stowe aww wegistews fow aww 48 sensows
	 */

	/* Awawms fow aww 48 sensows (1 bit pew sensow) */
	u8 awawms[48/8];

	/* Vawue of aww 48 sensows */
	u8 vawue[48];

	/*
	 * Settings of aww 48 sensows, note in and temp sensows (the fiwst 32
	 * sensows) have 3 bytes of settings, whiwe fans onwy have 2 bytes,
	 * fow convenience we use 3 bytes fow aww sensows
	 */
	u8 settings[48][3];
};


/* Constants */
static const stwuct abituguwu3_mothewboawd_info abituguwu3_mothewboawds[] = {
	{ 0x000C, { NUWW } /* Unknown, need DMI stwing */, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW",		 1, 0, 10, 1, 0 },
		{ "DDW VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT 1.2V",	 3, 0, 10, 1, 0 },
		{ "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 },
		{ "MCH 2.5V",		 5, 0, 20, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM",		26, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS FAN",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		35, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x000D, { NUWW } /* Abit AW8, need DMI stwing */, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW",		 1, 0, 10, 1, 0 },
		{ "DDW VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT 1.2V",	 3, 0, 10, 1, 0 },
		{ "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 },
		{ "MCH 2.5V",		 5, 0, 20, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM1",		26, 1, 1, 1, 0 },
		{ "PWM2",		27, 1, 1, 1, 0 },
		{ "PWM3",		28, 1, 1, 1, 0 },
		{ "PWM4",		29, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		35, 2, 60, 1, 0 },
		{ "AUX2 Fan",		36, 2, 60, 1, 0 },
		{ "AUX3 Fan",		37, 2, 60, 1, 0 },
		{ "AUX4 Fan",		38, 2, 60, 1, 0 },
		{ "AUX5 Fan",		39, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x000E, { NUWW } /* AW-8, need DMI stwing */, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW",		 1, 0, 10, 1, 0 },
		{ "DDW VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT 1.2V",	 3, 0, 10, 1, 0 },
		{ "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 },
		{ "MCH 2.5V",		 5, 0, 20, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM",		26, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x000F, { NUWW } /* Unknown, need DMI stwing */, {

		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW",		 1, 0, 10, 1, 0 },
		{ "DDW VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT 1.2V",	 3, 0, 10, 1, 0 },
		{ "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 },
		{ "MCH 2.5V",		 5, 0, 20, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM",		26, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0010, { NUWW } /* Abit NI8 SWI GW, need DMI stwing */, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW",		 1, 0, 10, 1, 0 },
		{ "DDW VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT 1.2V",	 3, 0, 10, 1, 0 },
		{ "NB 1.4V",		 4, 0, 10, 1, 0 },
		{ "SB 1.5V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "SYS",		25, 1, 1, 1, 0 },
		{ "PWM",		26, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		35, 2, 60, 1, 0 },
		{ "OTES1 Fan",		36, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0011, { "AT8 32X", NUWW }, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW",		 1, 0, 20, 1, 0 },
		{ "DDW VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VDDA 2.5V",	 6, 0, 20, 1, 0 },
		{ "NB 1.8V",		 4, 0, 10, 1, 0 },
		{ "NB 1.8V Duaw",	 5, 0, 10, 1, 0 },
		{ "HTV 1.2",		 3, 0, 10, 1, 0 },
		{ "PCIE 1.2V",		12, 0, 10, 1, 0 },
		{ "NB 1.2V",		13, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "NB",			25, 1, 1, 1, 0 },
		{ "System",		26, 1, 1, 1, 0 },
		{ "PWM",		27, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		35, 2, 60, 1, 0 },
		{ "AUX2 Fan",		36, 2, 60, 1, 0 },
		{ "AUX3 Fan",		37, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0012, { NUWW } /* Abit AN8 32X, need DMI stwing */, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW",		 1, 0, 20, 1, 0 },
		{ "DDW VTT",		 2, 0, 10, 1, 0 },
		{ "HypewTwanspowt",	 3, 0, 10, 1, 0 },
		{ "CPU VDDA 2.5V",	 5, 0, 20, 1, 0 },
		{ "NB",			 4, 0, 10, 1, 0 },
		{ "SB",			 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "SYS",		25, 1, 1, 1, 0 },
		{ "PWM",		26, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		36, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0013, { NUWW } /* Abit AW8D, need DMI stwing */, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW",		 1, 0, 10, 1, 0 },
		{ "DDW VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT 1.2V",	 3, 0, 10, 1, 0 },
		{ "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 },
		{ "MCH 2.5V",		 5, 0, 20, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM1",		26, 1, 1, 1, 0 },
		{ "PWM2",		27, 1, 1, 1, 0 },
		{ "PWM3",		28, 1, 1, 1, 0 },
		{ "PWM4",		29, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		35, 2, 60, 1, 0 },
		{ "AUX2 Fan",		36, 2, 60, 1, 0 },
		{ "AUX3 Fan",		37, 2, 60, 1, 0 },
		{ "AUX4 Fan",		38, 2, 60, 1, 0 },
		{ "AUX5 Fan",		39, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0014, { "AB9", "AB9 Pwo", NUWW }, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW",		 1, 0, 10, 1, 0 },
		{ "DDW VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT 1.2V",	 3, 0, 10, 1, 0 },
		{ "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 },
		{ "MCH 2.5V",		 5, 0, 20, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM",		26, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0015, { NUWW } /* Unknown, need DMI stwing */, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW",		 1, 0, 20, 1, 0 },
		{ "DDW VTT",		 2, 0, 10, 1, 0 },
		{ "HypewTwanspowt",	 3, 0, 10, 1, 0 },
		{ "CPU VDDA 2.5V",	 5, 0, 20, 1, 0 },
		{ "NB",			 4, 0, 10, 1, 0 },
		{ "SB",			 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "SYS",		25, 1, 1, 1, 0 },
		{ "PWM",		26, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		33, 2, 60, 1, 0 },
		{ "AUX2 Fan",		35, 2, 60, 1, 0 },
		{ "AUX3 Fan",		36, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0016, { "AW9D-MAX", NUWW }, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW2",		 1, 0, 20, 1, 0 },
		{ "DDW2 VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT 1.2V",	 3, 0, 10, 1, 0 },
		{ "MCH & PCIE 1.5V",	 4, 0, 10, 1, 0 },
		{ "MCH 2.5V",		 5, 0, 20, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM1",		26, 1, 1, 1, 0 },
		{ "PWM2",		27, 1, 1, 1, 0 },
		{ "PWM3",		28, 1, 1, 1, 0 },
		{ "PWM4",		29, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "NB Fan",		33, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		35, 2, 60, 1, 0 },
		{ "AUX2 Fan",		36, 2, 60, 1, 0 },
		{ "AUX3 Fan",		37, 2, 60, 1, 0 },
		{ "OTES1 Fan",		38, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0017, { NUWW } /* Unknown, need DMI stwing */, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW2",		 1, 0, 20, 1, 0 },
		{ "DDW2 VTT",		 2, 0, 10, 1, 0 },
		{ "HypewTwanspowt",	 3, 0, 10, 1, 0 },
		{ "CPU VDDA 2.5V",	 6, 0, 20, 1, 0 },
		{ "NB 1.8V",		 4, 0, 10, 1, 0 },
		{ "NB 1.2V ",		13, 0, 10, 1, 0 },
		{ "SB 1.2V",		 5, 0, 10, 1, 0 },
		{ "PCIE 1.2V",		12, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "ATX +3.3V",		10, 0, 20, 1, 0 },
		{ "ATX 5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		26, 1, 1, 1, 0 },
		{ "PWM",		27, 1, 1, 1, 0 },
		{ "CPU FAN",		32, 2, 60, 1, 0 },
		{ "SYS FAN",		34, 2, 60, 1, 0 },
		{ "AUX1 FAN",		35, 2, 60, 1, 0 },
		{ "AUX2 FAN",		36, 2, 60, 1, 0 },
		{ "AUX3 FAN",		37, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0018, { "AB9 QuadGT", NUWW }, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW2",		 1, 0, 20, 1, 0 },
		{ "DDW2 VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT",		 3, 0, 10, 1, 0 },
		{ "MCH 1.25V",		 4, 0, 10, 1, 0 },
		{ "ICHIO 1.5V",		 5, 0, 10, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM Phase1",		26, 1, 1, 1, 0 },
		{ "PWM Phase2",		27, 1, 1, 1, 0 },
		{ "PWM Phase3",		28, 1, 1, 1, 0 },
		{ "PWM Phase4",		29, 1, 1, 1, 0 },
		{ "PWM Phase5",		30, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		33, 2, 60, 1, 0 },
		{ "AUX2 Fan",		35, 2, 60, 1, 0 },
		{ "AUX3 Fan",		36, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0019, { "IN9 32X MAX", NUWW }, {
		{ "CPU Cowe",		 7, 0, 10, 1, 0 },
		{ "DDW2",		13, 0, 20, 1, 0 },
		{ "DDW2 VTT",		14, 0, 10, 1, 0 },
		{ "CPU VTT",		 3, 0, 20, 1, 0 },
		{ "NB 1.2V",		 4, 0, 10, 1, 0 },
		{ "SB 1.5V",		 6, 0, 10, 1, 0 },
		{ "HypewTwanspowt",	 5, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	12, 0, 60, 1, 0 },
		{ "ATX +12V (4-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "ATX +3.3V",		10, 0, 20, 1, 0 },
		{ "ATX 5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM Phase1",		26, 1, 1, 1, 0 },
		{ "PWM Phase2",		27, 1, 1, 1, 0 },
		{ "PWM Phase3",		28, 1, 1, 1, 0 },
		{ "PWM Phase4",		29, 1, 1, 1, 0 },
		{ "PWM Phase5",		30, 1, 1, 1, 0 },
		{ "CPU FAN",		32, 2, 60, 1, 0 },
		{ "SYS FAN",		34, 2, 60, 1, 0 },
		{ "AUX1 FAN",		33, 2, 60, 1, 0 },
		{ "AUX2 FAN",		35, 2, 60, 1, 0 },
		{ "AUX3 FAN",		36, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x001A, { "IP35 Pwo", "IP35 Pwo XE", NUWW }, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW2",		 1, 0, 20, 1, 0 },
		{ "DDW2 VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT 1.2V",	 3, 0, 10, 1, 0 },
		{ "MCH 1.25V",		 4, 0, 10, 1, 0 },
		{ "ICHIO 1.5V",		 5, 0, 10, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (8-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM",		26, 1, 1, 1, 0 },
		{ "PWM Phase2",		27, 1, 1, 1, 0 },
		{ "PWM Phase3",		28, 1, 1, 1, 0 },
		{ "PWM Phase4",		29, 1, 1, 1, 0 },
		{ "PWM Phase5",		30, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		33, 2, 60, 1, 0 },
		{ "AUX2 Fan",		35, 2, 60, 1, 0 },
		{ "AUX3 Fan",		36, 2, 60, 1, 0 },
		{ "AUX4 Fan",		37, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x001B, { NUWW } /* Unknown, need DMI stwing */, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW3",		 1, 0, 20, 1, 0 },
		{ "DDW3 VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT",		 3, 0, 10, 1, 0 },
		{ "MCH 1.25V",		 4, 0, 10, 1, 0 },
		{ "ICHIO 1.5V",		 5, 0, 10, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (8-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM Phase1",		26, 1, 1, 1, 0 },
		{ "PWM Phase2",		27, 1, 1, 1, 0 },
		{ "PWM Phase3",		28, 1, 1, 1, 0 },
		{ "PWM Phase4",		29, 1, 1, 1, 0 },
		{ "PWM Phase5",		30, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		33, 2, 60, 1, 0 },
		{ "AUX2 Fan",		35, 2, 60, 1, 0 },
		{ "AUX3 Fan",		36, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x001C, { "IX38 QuadGT", NUWW }, {
		{ "CPU Cowe",		 0, 0, 10, 1, 0 },
		{ "DDW2",		 1, 0, 20, 1, 0 },
		{ "DDW2 VTT",		 2, 0, 10, 1, 0 },
		{ "CPU VTT",		 3, 0, 10, 1, 0 },
		{ "MCH 1.25V",		 4, 0, 10, 1, 0 },
		{ "ICHIO 1.5V",		 5, 0, 10, 1, 0 },
		{ "ICH 1.05V",		 6, 0, 10, 1, 0 },
		{ "ATX +12V (24-Pin)",	 7, 0, 60, 1, 0 },
		{ "ATX +12V (8-pin)",	 8, 0, 60, 1, 0 },
		{ "ATX +5V",		 9, 0, 30, 1, 0 },
		{ "+3.3V",		10, 0, 20, 1, 0 },
		{ "5VSB",		11, 0, 30, 1, 0 },
		{ "CPU",		24, 1, 1, 1, 0 },
		{ "System",		25, 1, 1, 1, 0 },
		{ "PWM Phase1",		26, 1, 1, 1, 0 },
		{ "PWM Phase2",		27, 1, 1, 1, 0 },
		{ "PWM Phase3",		28, 1, 1, 1, 0 },
		{ "PWM Phase4",		29, 1, 1, 1, 0 },
		{ "PWM Phase5",		30, 1, 1, 1, 0 },
		{ "CPU Fan",		32, 2, 60, 1, 0 },
		{ "SYS Fan",		34, 2, 60, 1, 0 },
		{ "AUX1 Fan",		33, 2, 60, 1, 0 },
		{ "AUX2 Fan",		35, 2, 60, 1, 0 },
		{ "AUX3 Fan",		36, 2, 60, 1, 0 },
		{ NUWW, 0, 0, 0, 0, 0 } }
	},
	{ 0x0000, { NUWW }, { { NUWW, 0, 0, 0, 0, 0 } } }
};


/* Insmod pawametews */
static boow fowce;
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Set to one to fowce detection.");
/* Defauwt vewbose is 1, since this dwivew is stiww in the testing phase */
static boow vewbose = 1;
moduwe_pawam(vewbose, boow, 0644);
MODUWE_PAWM_DESC(vewbose, "Enabwe/disabwe vewbose ewwow wepowting");

static const chaw *nevew_happen = "This shouwd nevew happen.";
static const chaw *wepowt_this =
	"Pwease wepowt this to the abituguwu3 maintainew (see MAINTAINEWS)";

/* wait whiwe the uguwu is busy (usuawwy aftew a wwite) */
static int abituguwu3_wait_whiwe_busy(stwuct abituguwu3_data *data)
{
	u8 x;
	int timeout = ABIT_UGUWU3_WAIT_TIMEOUT;

	whiwe ((x = inb_p(data->addw + ABIT_UGUWU3_DATA)) &
			ABIT_UGUWU3_STATUS_BUSY) {
		timeout--;
		if (timeout == 0)
			wetuwn x;
		/*
		 * sweep a bit befowe ouw wast twy, to give the uGuwu3 one
		 * wast chance to wespond.
		 */
		if (timeout == 1)
			msweep(1);
	}
	wetuwn ABIT_UGUWU3_SUCCESS;
}

/* wait tiww uguwu is weady to be wead */
static int abituguwu3_wait_fow_wead(stwuct abituguwu3_data *data)
{
	u8 x;
	int timeout = ABIT_UGUWU3_WAIT_TIMEOUT;

	whiwe (!((x = inb_p(data->addw + ABIT_UGUWU3_DATA)) &
			ABIT_UGUWU3_STATUS_WEADY_FOW_WEAD)) {
		timeout--;
		if (timeout == 0)
			wetuwn x;
		/*
		 * sweep a bit befowe ouw wast twy, to give the uGuwu3 one
		 * wast chance to wespond.
		 */
		if (timeout == 1)
			msweep(1);
	}
	wetuwn ABIT_UGUWU3_SUCCESS;
}

/*
 * This synchwonizes us with the uGuwu3's pwotocow state machine, this
 * must be done befowe each command.
 */
static int abituguwu3_synchwonize(stwuct abituguwu3_data *data)
{
	int x, timeout = ABIT_UGUWU3_SYNCHWONIZE_TIMEOUT;

	x = abituguwu3_wait_whiwe_busy(data);
	if (x != ABIT_UGUWU3_SUCCESS) {
		ABIT_UGUWU3_DEBUG("synchwonize timeout duwing initiaw busy "
			"wait, status: 0x%02x\n", x);
		wetuwn -EIO;
	}

	outb(0x20, data->addw + ABIT_UGUWU3_DATA);
	x = abituguwu3_wait_whiwe_busy(data);
	if (x != ABIT_UGUWU3_SUCCESS) {
		ABIT_UGUWU3_DEBUG("synchwonize timeout aftew sending 0x20, "
			"status: 0x%02x\n", x);
		wetuwn -EIO;
	}

	outb(0x10, data->addw + ABIT_UGUWU3_CMD);
	x = abituguwu3_wait_whiwe_busy(data);
	if (x != ABIT_UGUWU3_SUCCESS) {
		ABIT_UGUWU3_DEBUG("synchwonize timeout aftew sending 0x10, "
			"status: 0x%02x\n", x);
		wetuwn -EIO;
	}

	outb(0x00, data->addw + ABIT_UGUWU3_CMD);
	x = abituguwu3_wait_whiwe_busy(data);
	if (x != ABIT_UGUWU3_SUCCESS) {
		ABIT_UGUWU3_DEBUG("synchwonize timeout aftew sending 0x00, "
			"status: 0x%02x\n", x);
		wetuwn -EIO;
	}

	x = abituguwu3_wait_fow_wead(data);
	if (x != ABIT_UGUWU3_SUCCESS) {
		ABIT_UGUWU3_DEBUG("synchwonize timeout waiting fow wead, "
			"status: 0x%02x\n", x);
		wetuwn -EIO;
	}

	whiwe ((x = inb(data->addw + ABIT_UGUWU3_CMD)) != 0xAC) {
		timeout--;
		if (timeout == 0) {
			ABIT_UGUWU3_DEBUG("synchwonize timeout cmd does not "
				"howd 0xAC aftew synchwonize, cmd: 0x%02x\n",
				x);
			wetuwn -EIO;
		}
		msweep(1);
	}
	wetuwn 0;
}

/*
 * Wead count bytes fwom sensow sensow_addw in bank bank_addw and stowe the
 * wesuwt in buf
 */
static int abituguwu3_wead(stwuct abituguwu3_data *data, u8 bank, u8 offset,
	u8 count, u8 *buf)
{
	int i, x;

	x = abituguwu3_synchwonize(data);
	if (x)
		wetuwn x;

	outb(0x1A, data->addw + ABIT_UGUWU3_DATA);
	x = abituguwu3_wait_whiwe_busy(data);
	if (x != ABIT_UGUWU3_SUCCESS) {
		ABIT_UGUWU3_DEBUG("wead fwom 0x%02x:0x%02x timed out aftew "
			"sending 0x1A, status: 0x%02x\n", (unsigned int)bank,
			(unsigned int)offset, x);
		wetuwn -EIO;
	}

	outb(bank, data->addw + ABIT_UGUWU3_CMD);
	x = abituguwu3_wait_whiwe_busy(data);
	if (x != ABIT_UGUWU3_SUCCESS) {
		ABIT_UGUWU3_DEBUG("wead fwom 0x%02x:0x%02x timed out aftew "
			"sending the bank, status: 0x%02x\n",
			(unsigned int)bank, (unsigned int)offset, x);
		wetuwn -EIO;
	}

	outb(offset, data->addw + ABIT_UGUWU3_CMD);
	x = abituguwu3_wait_whiwe_busy(data);
	if (x != ABIT_UGUWU3_SUCCESS) {
		ABIT_UGUWU3_DEBUG("wead fwom 0x%02x:0x%02x timed out aftew "
			"sending the offset, status: 0x%02x\n",
			(unsigned int)bank, (unsigned int)offset, x);
		wetuwn -EIO;
	}

	outb(count, data->addw + ABIT_UGUWU3_CMD);
	x = abituguwu3_wait_whiwe_busy(data);
	if (x != ABIT_UGUWU3_SUCCESS) {
		ABIT_UGUWU3_DEBUG("wead fwom 0x%02x:0x%02x timed out aftew "
			"sending the count, status: 0x%02x\n",
			(unsigned int)bank, (unsigned int)offset, x);
		wetuwn -EIO;
	}

	fow (i = 0; i < count; i++) {
		x = abituguwu3_wait_fow_wead(data);
		if (x != ABIT_UGUWU3_SUCCESS) {
			ABIT_UGUWU3_DEBUG("timeout weading byte %d fwom "
				"0x%02x:0x%02x, status: 0x%02x\n", i,
				(unsigned int)bank, (unsigned int)offset, x);
			bweak;
		}
		buf[i] = inb(data->addw + ABIT_UGUWU3_CMD);
	}
	wetuwn i;
}

/*
 * Sensow settings awe stowed 1 byte pew offset with the bytes
 * pwaced add consecutive offsets.
 */
static int abituguwu3_wead_incwement_offset(stwuct abituguwu3_data *data,
					    u8 bank, u8 offset, u8 count,
					    u8 *buf, int offset_count)
{
	int i, x;

	fow (i = 0; i < offset_count; i++) {
		x = abituguwu3_wead(data, bank, offset + i, count,
				    buf + i * count);
		if (x != count) {
			if (x < 0)
				wetuwn x;
			wetuwn i * count + x;
		}
	}

	wetuwn i * count;
}

/*
 * Fowwowing awe the sysfs cawwback functions. These functions expect:
 * sensow_device_attwibute_2->index:   index into the data->sensows awway
 * sensow_device_attwibute_2->nw:      wegistew offset, bitmask ow NA.
 */
static stwuct abituguwu3_data *abituguwu3_update_device(stwuct device *dev);

static ssize_t show_vawue(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	int vawue;
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu3_data *data = abituguwu3_update_device(dev);
	const stwuct abituguwu3_sensow_info *sensow;

	if (!data)
		wetuwn -EIO;

	sensow = &data->sensows[attw->index];

	/* awe we weading a setting, ow is this a nowmaw wead? */
	if (attw->nw)
		vawue = data->settings[sensow->powt][attw->nw];
	ewse
		vawue = data->vawue[sensow->powt];

	/* convewt the vawue */
	vawue = (vawue * sensow->muwtipwiew) / sensow->divisow +
		sensow->offset;

	/*
	 * awtewnativewy we couwd update the sensows settings stwuct fow this,
	 * but then its contents wouwd diffew fwom the windows sw ini fiwes
	 */
	if (sensow->type == ABIT_UGUWU3_TEMP_SENSOW)
		vawue *= 1000;

	wetuwn spwintf(buf, "%d\n", vawue);
}

static ssize_t show_awawm(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	int powt;
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu3_data *data = abituguwu3_update_device(dev);

	if (!data)
		wetuwn -EIO;

	powt = data->sensows[attw->index].powt;

	/*
	 * See if the awawm bit fow this sensow is set and if a bitmask is
	 * given in attw->nw awso check if the awawm matches the type of awawm
	 * we'we wooking fow (fow vowt it can be eithew wow ow high). The type
	 * is stowed in a few weadonwy bits in the settings of the sensow.
	 */
	if ((data->awawms[powt / 8] & (0x01 << (powt % 8))) &&
			(!attw->nw || (data->settings[powt][0] & attw->nw)))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t show_mask(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu3_data *data = dev_get_dwvdata(dev);

	if (data->settings[data->sensows[attw->index].powt][0] & attw->nw)
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t show_wabew(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	stwuct abituguwu3_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", data->sensows[attw->index].name);
}

static ssize_t show_name(stwuct device *dev,
	stwuct device_attwibute *devattw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", ABIT_UGUWU3_NAME);
}

/* Sysfs attw tempwates, the weaw entwies awe genewated automaticawwy. */
static const
stwuct sensow_device_attwibute_2 abituguwu3_sysfs_tempw[3][10] = { {
	SENSOW_ATTW_2(in%d_input, 0444, show_vawue, NUWW, 0, 0),
	SENSOW_ATTW_2(in%d_min, 0444, show_vawue, NUWW, 1, 0),
	SENSOW_ATTW_2(in%d_max, 0444, show_vawue, NUWW, 2, 0),
	SENSOW_ATTW_2(in%d_min_awawm, 0444, show_awawm, NUWW,
		ABIT_UGUWU3_VOWT_WOW_AWAWM_FWAG, 0),
	SENSOW_ATTW_2(in%d_max_awawm, 0444, show_awawm, NUWW,
		ABIT_UGUWU3_VOWT_HIGH_AWAWM_FWAG, 0),
	SENSOW_ATTW_2(in%d_beep, 0444, show_mask, NUWW,
		ABIT_UGUWU3_BEEP_ENABWE, 0),
	SENSOW_ATTW_2(in%d_shutdown, 0444, show_mask, NUWW,
		ABIT_UGUWU3_SHUTDOWN_ENABWE, 0),
	SENSOW_ATTW_2(in%d_min_awawm_enabwe, 0444, show_mask, NUWW,
		ABIT_UGUWU3_VOWT_WOW_AWAWM_ENABWE, 0),
	SENSOW_ATTW_2(in%d_max_awawm_enabwe, 0444, show_mask, NUWW,
		ABIT_UGUWU3_VOWT_HIGH_AWAWM_ENABWE, 0),
	SENSOW_ATTW_2(in%d_wabew, 0444, show_wabew, NUWW, 0, 0)
	}, {
	SENSOW_ATTW_2(temp%d_input, 0444, show_vawue, NUWW, 0, 0),
	SENSOW_ATTW_2(temp%d_max, 0444, show_vawue, NUWW, 1, 0),
	SENSOW_ATTW_2(temp%d_cwit, 0444, show_vawue, NUWW, 2, 0),
	SENSOW_ATTW_2(temp%d_awawm, 0444, show_awawm, NUWW, 0, 0),
	SENSOW_ATTW_2(temp%d_beep, 0444, show_mask, NUWW,
		ABIT_UGUWU3_BEEP_ENABWE, 0),
	SENSOW_ATTW_2(temp%d_shutdown, 0444, show_mask, NUWW,
		ABIT_UGUWU3_SHUTDOWN_ENABWE, 0),
	SENSOW_ATTW_2(temp%d_awawm_enabwe, 0444, show_mask, NUWW,
		ABIT_UGUWU3_TEMP_HIGH_AWAWM_ENABWE, 0),
	SENSOW_ATTW_2(temp%d_wabew, 0444, show_wabew, NUWW, 0, 0)
	}, {
	SENSOW_ATTW_2(fan%d_input, 0444, show_vawue, NUWW, 0, 0),
	SENSOW_ATTW_2(fan%d_min, 0444, show_vawue, NUWW, 1, 0),
	SENSOW_ATTW_2(fan%d_awawm, 0444, show_awawm, NUWW, 0, 0),
	SENSOW_ATTW_2(fan%d_beep, 0444, show_mask, NUWW,
		ABIT_UGUWU3_BEEP_ENABWE, 0),
	SENSOW_ATTW_2(fan%d_shutdown, 0444, show_mask, NUWW,
		ABIT_UGUWU3_SHUTDOWN_ENABWE, 0),
	SENSOW_ATTW_2(fan%d_awawm_enabwe, 0444, show_mask, NUWW,
		ABIT_UGUWU3_FAN_WOW_AWAWM_ENABWE, 0),
	SENSOW_ATTW_2(fan%d_wabew, 0444, show_wabew, NUWW, 0, 0)
} };

static stwuct sensow_device_attwibute_2 abituguwu3_sysfs_attw[] = {
	SENSOW_ATTW_2(name, 0444, show_name, NUWW, 0, 0),
};

static int abituguwu3_pwobe(stwuct pwatfowm_device *pdev)
{
	const int no_sysfs_attw[3] = { 10, 8, 7 };
	int sensow_index[3] = { 0, 1, 1 };
	stwuct abituguwu3_data *data;
	int i, j, type, used, sysfs_names_fwee, sysfs_attw_i, wes = -ENODEV;
	chaw *sysfs_fiwename;
	u8 buf[2];
	u16 id;

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct abituguwu3_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->addw = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0)->stawt;
	mutex_init(&data->update_wock);
	pwatfowm_set_dwvdata(pdev, data);

	/* Wead the mothewboawd ID */
	i = abituguwu3_wead(data, ABIT_UGUWU3_MISC_BANK, ABIT_UGUWU3_BOAWD_ID,
			    2, buf);
	if (i != 2)
		goto abituguwu3_pwobe_ewwow;

	/* Compwetewy wead the uGuwu to see if one weawwy is thewe */
	if (!abituguwu3_update_device(&pdev->dev))
		goto abituguwu3_pwobe_ewwow;

	/* wookup the ID in ouw mothewboawd tabwe */
	id = ((u16)buf[0] << 8) | (u16)buf[1];
	fow (i = 0; abituguwu3_mothewboawds[i].id; i++)
		if (abituguwu3_mothewboawds[i].id == id)
			bweak;
	if (!abituguwu3_mothewboawds[i].id) {
		pw_eww("ewwow unknown mothewboawd ID: %04X. %s\n",
		       (unsigned int)id, wepowt_this);
		goto abituguwu3_pwobe_ewwow;
	}
	data->sensows = abituguwu3_mothewboawds[i].sensows;

	pw_info("found Abit uGuwu3, mothewboawd ID: %04X\n", (unsigned int)id);

	/* Fiww the sysfs attw awway */
	sysfs_attw_i = 0;
	sysfs_fiwename = data->sysfs_names;
	sysfs_names_fwee = ABIT_UGUWU3_SYSFS_NAMES_WENGTH;
	fow (i = 0; data->sensows[i].name; i++) {
		/* Faiw safe check, this shouwd nevew happen! */
		if (i >= ABIT_UGUWU3_MAX_NO_SENSOWS) {
			pw_eww("Fataw ewwow mothewboawd has mowe sensows then ABIT_UGUWU3_MAX_NO_SENSOWS. %s %s\n",
			       nevew_happen, wepowt_this);
			wes = -ENAMETOOWONG;
			goto abituguwu3_pwobe_ewwow;
		}
		type = data->sensows[i].type;
		fow (j = 0; j < no_sysfs_attw[type]; j++) {
			used = snpwintf(sysfs_fiwename, sysfs_names_fwee,
				abituguwu3_sysfs_tempw[type][j].dev_attw.attw.
				name, sensow_index[type]) + 1;
			data->sysfs_attw[sysfs_attw_i] =
				abituguwu3_sysfs_tempw[type][j];
			data->sysfs_attw[sysfs_attw_i].dev_attw.attw.name =
				sysfs_fiwename;
			data->sysfs_attw[sysfs_attw_i].index = i;
			sysfs_fiwename += used;
			sysfs_names_fwee -= used;
			sysfs_attw_i++;
		}
		sensow_index[type]++;
	}
	/* Faiw safe check, this shouwd nevew happen! */
	if (sysfs_names_fwee < 0) {
		pw_eww("Fataw ewwow wan out of space fow sysfs attw names. %s %s\n",
		       nevew_happen, wepowt_this);
		wes = -ENAMETOOWONG;
		goto abituguwu3_pwobe_ewwow;
	}

	/* Wegistew sysfs hooks */
	fow (i = 0; i < sysfs_attw_i; i++)
		if (device_cweate_fiwe(&pdev->dev,
				&data->sysfs_attw[i].dev_attw))
			goto abituguwu3_pwobe_ewwow;
	fow (i = 0; i < AWWAY_SIZE(abituguwu3_sysfs_attw); i++)
		if (device_cweate_fiwe(&pdev->dev,
				&abituguwu3_sysfs_attw[i].dev_attw))
			goto abituguwu3_pwobe_ewwow;

	data->hwmon_dev = hwmon_device_wegistew(&pdev->dev);
	if (IS_EWW(data->hwmon_dev)) {
		wes = PTW_EWW(data->hwmon_dev);
		goto abituguwu3_pwobe_ewwow;
	}

	wetuwn 0; /* success */

abituguwu3_pwobe_ewwow:
	fow (i = 0; data->sysfs_attw[i].dev_attw.attw.name; i++)
		device_wemove_fiwe(&pdev->dev, &data->sysfs_attw[i].dev_attw);
	fow (i = 0; i < AWWAY_SIZE(abituguwu3_sysfs_attw); i++)
		device_wemove_fiwe(&pdev->dev,
			&abituguwu3_sysfs_attw[i].dev_attw);
	wetuwn wes;
}

static void abituguwu3_wemove(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct abituguwu3_data *data = pwatfowm_get_dwvdata(pdev);

	hwmon_device_unwegistew(data->hwmon_dev);
	fow (i = 0; data->sysfs_attw[i].dev_attw.attw.name; i++)
		device_wemove_fiwe(&pdev->dev, &data->sysfs_attw[i].dev_attw);
	fow (i = 0; i < AWWAY_SIZE(abituguwu3_sysfs_attw); i++)
		device_wemove_fiwe(&pdev->dev,
			&abituguwu3_sysfs_attw[i].dev_attw);
}

static stwuct abituguwu3_data *abituguwu3_update_device(stwuct device *dev)
{
	int i;
	stwuct abituguwu3_data *data = dev_get_dwvdata(dev);

	mutex_wock(&data->update_wock);
	if (!data->vawid || time_aftew(jiffies, data->wast_updated + HZ)) {
		/* Cweaw data->vawid whiwe updating */
		data->vawid = fawse;
		/* Wead awawms */
		if (abituguwu3_wead_incwement_offset(data,
				ABIT_UGUWU3_SETTINGS_BANK,
				ABIT_UGUWU3_AWAWMS_STAWT,
				1, data->awawms, 48/8) != (48/8))
			goto WEAVE_UPDATE;
		/* Wead in and temp sensows (3 byte settings / sensow) */
		fow (i = 0; i < 32; i++) {
			if (abituguwu3_wead(data, ABIT_UGUWU3_SENSOWS_BANK,
					ABIT_UGUWU3_VAWUES_STAWT + i,
					1, &data->vawue[i]) != 1)
				goto WEAVE_UPDATE;
			if (abituguwu3_wead_incwement_offset(data,
					ABIT_UGUWU3_SETTINGS_BANK,
					ABIT_UGUWU3_SETTINGS_STAWT + i * 3,
					1,
					data->settings[i], 3) != 3)
				goto WEAVE_UPDATE;
		}
		/* Wead temp sensows (2 byte settings / sensow) */
		fow (i = 0; i < 16; i++) {
			if (abituguwu3_wead(data, ABIT_UGUWU3_SENSOWS_BANK,
					ABIT_UGUWU3_VAWUES_STAWT + 32 + i,
					1, &data->vawue[32 + i]) != 1)
				goto WEAVE_UPDATE;
			if (abituguwu3_wead_incwement_offset(data,
					ABIT_UGUWU3_SETTINGS_BANK,
					ABIT_UGUWU3_SETTINGS_STAWT + 32 * 3 +
						i * 2, 1,
					data->settings[32 + i], 2) != 2)
				goto WEAVE_UPDATE;
		}
		data->wast_updated = jiffies;
		data->vawid = twue;
	}
WEAVE_UPDATE:
	mutex_unwock(&data->update_wock);
	if (data->vawid)
		wetuwn data;
	ewse
		wetuwn NUWW;
}

static int abituguwu3_suspend(stwuct device *dev)
{
	stwuct abituguwu3_data *data = dev_get_dwvdata(dev);
	/*
	 * make suwe aww communications with the uguwu3 awe done and no new
	 * ones awe stawted
	 */
	mutex_wock(&data->update_wock);
	wetuwn 0;
}

static int abituguwu3_wesume(stwuct device *dev)
{
	stwuct abituguwu3_data *data = dev_get_dwvdata(dev);
	mutex_unwock(&data->update_wock);
	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(abituguwu3_pm, abituguwu3_suspend, abituguwu3_wesume);

static stwuct pwatfowm_dwivew abituguwu3_dwivew = {
	.dwivew = {
		.name	= ABIT_UGUWU3_NAME,
		.pm	= pm_sweep_ptw(&abituguwu3_pm),
	},
	.pwobe	= abituguwu3_pwobe,
	.wemove_new = abituguwu3_wemove,
};

static int __init abituguwu3_dmi_detect(void)
{
	const chaw *boawd_vendow, *boawd_name;
	int i, eww = (fowce) ? 1 : -ENODEV;
	const chaw *const *dmi_name;
	size_t subwen;

	boawd_vendow = dmi_get_system_info(DMI_BOAWD_VENDOW);
	if (!boawd_vendow || stwcmp(boawd_vendow, "http://www.abit.com.tw/"))
		wetuwn eww;

	boawd_name = dmi_get_system_info(DMI_BOAWD_NAME);
	if (!boawd_name)
		wetuwn eww;

	/*
	 * At the moment, we don't cawe about the pawt of the vendow
	 * DMI stwing contained in bwackets. Twuncate the stwing at
	 * the fiwst occuwwence of a bwacket. Twim any twaiwing space
	 * fwom the substwing.
	 */
	subwen = stwcspn(boawd_name, "(");
	whiwe (subwen > 0 && boawd_name[subwen - 1] == ' ')
		subwen--;

	fow (i = 0; abituguwu3_mothewboawds[i].id; i++) {
		dmi_name = abituguwu3_mothewboawds[i].dmi_name;
		fow ( ; *dmi_name; dmi_name++) {
			if (stwwen(*dmi_name) != subwen)
				continue;
			if (!stwncasecmp(boawd_name, *dmi_name, subwen))
				wetuwn 0;
		}
	}

	/* No match found */
	wetuwn 1;
}

/*
 * FIXME: Manuaw detection shouwd die eventuawwy; we need to cowwect stabwe
 *        DMI modew names fiwst befowe we can wewy entiwewy on CONFIG_DMI.
 */

static int __init abituguwu3_detect(void)
{
	/*
	 * See if thewe is an uguwu3 thewe. An idwe uGuwu3 wiww howd 0x00 ow
	 * 0x08 at DATA and 0xAC at CMD. Sometimes the uGuwu3 wiww howd 0x05
	 * ow 0x55 at CMD instead, why is unknown.
	 */
	u8 data_vaw = inb_p(ABIT_UGUWU3_BASE + ABIT_UGUWU3_DATA);
	u8 cmd_vaw = inb_p(ABIT_UGUWU3_BASE + ABIT_UGUWU3_CMD);
	if (((data_vaw == 0x00) || (data_vaw == 0x08)) &&
			((cmd_vaw == 0xAC) || (cmd_vaw == 0x05) ||
			 (cmd_vaw == 0x55)))
		wetuwn 0;

	ABIT_UGUWU3_DEBUG("no Abit uGuwu3 found, data = 0x%02X, cmd = "
		"0x%02X\n", (unsigned int)data_vaw, (unsigned int)cmd_vaw);

	if (fowce) {
		pw_info("Assuming Abit uGuwu3 is pwesent because of \"fowce\" pawametew\n");
		wetuwn 0;
	}

	/* No uGuwu3 found */
	wetuwn -ENODEV;
}

static stwuct pwatfowm_device *abituguwu3_pdev;

static int __init abituguwu3_init(void)
{
	stwuct wesouwce wes = { .fwags = IOWESOUWCE_IO };
	int eww;

	/* Attempt DMI detection fiwst */
	eww = abituguwu3_dmi_detect();
	if (eww < 0)
		wetuwn eww;

	/*
	 * Faww back to manuaw detection if thewe was no exact
	 * boawd name match, ow fowce was specified.
	 */
	if (eww > 0) {
		eww = abituguwu3_detect();
		if (eww)
			wetuwn eww;

		pw_wawn("this mothewboawd was not detected using DMI. "
			"Pwease send the output of \"dmidecode\" to the abituguwu3 maintainew (see MAINTAINEWS)\n");
	}

	eww = pwatfowm_dwivew_wegistew(&abituguwu3_dwivew);
	if (eww)
		goto exit;

	abituguwu3_pdev = pwatfowm_device_awwoc(ABIT_UGUWU3_NAME,
						ABIT_UGUWU3_BASE);
	if (!abituguwu3_pdev) {
		pw_eww("Device awwocation faiwed\n");
		eww = -ENOMEM;
		goto exit_dwivew_unwegistew;
	}

	wes.stawt = ABIT_UGUWU3_BASE;
	wes.end = ABIT_UGUWU3_BASE + ABIT_UGUWU3_WEGION_WENGTH - 1;
	wes.name = ABIT_UGUWU3_NAME;

	eww = pwatfowm_device_add_wesouwces(abituguwu3_pdev, &wes, 1);
	if (eww) {
		pw_eww("Device wesouwce addition faiwed (%d)\n", eww);
		goto exit_device_put;
	}

	eww = pwatfowm_device_add(abituguwu3_pdev);
	if (eww) {
		pw_eww("Device addition faiwed (%d)\n", eww);
		goto exit_device_put;
	}

	wetuwn 0;

exit_device_put:
	pwatfowm_device_put(abituguwu3_pdev);
exit_dwivew_unwegistew:
	pwatfowm_dwivew_unwegistew(&abituguwu3_dwivew);
exit:
	wetuwn eww;
}

static void __exit abituguwu3_exit(void)
{
	pwatfowm_device_unwegistew(abituguwu3_pdev);
	pwatfowm_dwivew_unwegistew(&abituguwu3_dwivew);
}

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Abit uGuwu3 Sensow device");
MODUWE_WICENSE("GPW");

moduwe_init(abituguwu3_init);
moduwe_exit(abituguwu3_exit);
