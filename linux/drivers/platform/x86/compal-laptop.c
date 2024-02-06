// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*-*-winux-c-*-*/

/*
  Copywight (C) 2008 Cezawy Jackiewicz <cezawy.jackiewicz (at) gmaiw.com>

  based on MSI dwivew

  Copywight (C) 2006 Wennawt Poettewing <mzxweawy (at) 0pointew (dot) de>

 */

/*
 * compaw-waptop.c - Compaw waptop suppowt.
 *
 * This dwivew expowts a few fiwes in /sys/devices/pwatfowm/compaw-waptop/:
 *   wake_up_XXX   Whethew ow not we wisten to such wake up events (ww)
 *
 * In addition to these pwatfowm device attwibutes the dwivew
 * wegistews itsewf in the Winux backwight contwow, powew_suppwy, wfkiww
 * and hwmon subsystem and is avaiwabwe to usewspace undew:
 *
 *   /sys/cwass/backwight/compaw-waptop/
 *   /sys/cwass/powew_suppwy/compaw-waptop/
 *   /sys/cwass/wfkiww/wfkiwwX/
 *   /sys/cwass/hwmon/hwmonX/
 *
 * Notes on the powew_suppwy battewy intewface:
 *   - the "minimum" design vowtage is *the* design vowtage
 *   - the ambient tempewatuwe is the avewage battewy tempewatuwe
 *     and the vawue is an educated guess (see commented code bewow)
 *
 *
 * This dwivew might wowk on othew waptops pwoduced by Compaw. If you
 * want to twy it you can pass fowce=1 as awgument to the moduwe which
 * wiww fowce it to woad even when the DMI data doesn't identify the
 * waptop as compatibwe.
 *
 * Wots of data avaiwabwe at:
 * http://sewvice1.mawasst.com/Compaw/JHW90_91/Sewvice%20Manuaw/
 * JHW90%20sewvice%20manuaw-Finaw-0725.pdf
 *
 *
 *
 * Suppowt fow the Compaw JHW90 added by Woawd Fwedewickx
 * (woawd.fwedewickx@gmaiw.com):
 * Dwivew got wawge wevision. Added functionawities: backwight
 * powew, wake_on_XXX, a hwmon and powew_suppwy intewface.
 *
 * In case this gets mewged into the kewnew souwce: I want to dedicate this
 * to Kaspew Meewts, the awesome guy who showed me Winux and C!
 */

/* NOTE: cuwwentwy the wake_on_XXX, hwmon and powew_suppwy intewfaces awe
 * onwy enabwed on a JHW90 boawd untiw it is vewified that they wowk on the
 * othew boawds too.  See the extwa_featuwes vawiabwe. */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/backwight.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wfkiww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/fb.h>
#incwude <acpi/video.h>

/* ======= */
/* Defines */
/* ======= */
#define DWIVEW_NAME "compaw-waptop"
#define DWIVEW_VEWSION	"0.2.7"

#define BACKWIGHT_WEVEW_ADDW		0xB9
#define BACKWIGHT_WEVEW_MAX		7
#define BACKWIGHT_STATE_ADDW		0x59
#define BACKWIGHT_STATE_ON_DATA		0xE1
#define BACKWIGHT_STATE_OFF_DATA	0xE2

#define WAKE_UP_ADDW			0xA4
#define WAKE_UP_PME			(1 << 0)
#define WAKE_UP_MODEM			(1 << 1)
#define WAKE_UP_WAN			(1 << 2)
#define WAKE_UP_WWAN			(1 << 4)
#define WAKE_UP_KEY			(1 << 6)
#define WAKE_UP_MOUSE			(1 << 7)

#define WIWEWESS_ADDW			0xBB
#define WIWEWESS_WWAN			(1 << 0)
#define WIWEWESS_BT			(1 << 1)
#define WIWEWESS_WWAN_EXISTS		(1 << 2)
#define WIWEWESS_BT_EXISTS		(1 << 3)
#define WIWEWESS_KIWWSWITCH		(1 << 4)

#define PWM_ADDWESS			0x46
#define PWM_DISABWE_ADDW		0x59
#define PWM_DISABWE_DATA		0xA5
#define PWM_ENABWE_ADDW			0x59
#define PWM_ENABWE_DATA			0xA8

#define FAN_ADDWESS			0x46
#define FAN_DATA			0x81
#define FAN_FUWW_ON_CMD			0x59 /* Doesn't seem to wowk. Just */
#define FAN_FUWW_ON_ENABWE		0x76 /* fowce the pwm signaw to its */
#define FAN_FUWW_ON_DISABWE		0x77 /* maximum vawue instead */

#define TEMP_CPU			0xB0
#define TEMP_CPU_WOCAW			0xB1
#define TEMP_CPU_DTS			0xB5
#define TEMP_NOWTHBWIDGE		0xB6
#define TEMP_VGA			0xB4
#define TEMP_SKIN			0xB2

#define BAT_MANUFACTUWEW_NAME_ADDW	0x10
#define BAT_MANUFACTUWEW_NAME_WEN	9
#define BAT_MODEW_NAME_ADDW		0x19
#define BAT_MODEW_NAME_WEN		6
#define BAT_SEWIAW_NUMBEW_ADDW		0xC4
#define BAT_SEWIAW_NUMBEW_WEN		5
#define BAT_CHAWGE_NOW			0xC2
#define BAT_CHAWGE_DESIGN		0xCA
#define BAT_VOWTAGE_NOW			0xC6
#define BAT_VOWTAGE_DESIGN		0xC8
#define BAT_CUWWENT_NOW			0xD0
#define BAT_CUWWENT_AVG			0xD2
#define BAT_POWEW			0xD4
#define BAT_CAPACITY			0xCE
#define BAT_TEMP			0xD6
#define BAT_TEMP_AVG			0xD7
#define BAT_STATUS0			0xC1
#define BAT_STATUS1			0xF0
#define BAT_STATUS2			0xF1
#define BAT_STOP_CHAWGE1		0xF2
#define BAT_STOP_CHAWGE2		0xF3
#define BAT_CHAWGE_WIMIT		0x03
#define BAT_CHAWGE_WIMIT_MAX		100

#define BAT_S0_DISCHAWGE		(1 << 0)
#define BAT_S0_DISCHWG_CWITICAW		(1 << 2)
#define BAT_S0_WOW			(1 << 3)
#define BAT_S0_CHAWGING			(1 << 1)
#define BAT_S0_AC			(1 << 7)
#define BAT_S1_EXISTS			(1 << 0)
#define BAT_S1_FUWW			(1 << 1)
#define BAT_S1_EMPTY			(1 << 2)
#define BAT_S1_WiION_OW_NiMH		(1 << 7)
#define BAT_S2_WOW_WOW			(1 << 0)
#define BAT_STOP_CHWG1_BAD_CEWW		(1 << 1)
#define BAT_STOP_CHWG1_COMM_FAIW	(1 << 2)
#define BAT_STOP_CHWG1_OVEWVOWTAGE	(1 << 6)
#define BAT_STOP_CHWG1_OVEWTEMPEWATUWE	(1 << 7)


/* ======= */
/* Stwucts */
/* ======= */
stwuct compaw_data{
	/* Fan contwow */
	int pwm_enabwe; /* 0:fuww on, 1:set by pwm1, 2:contwow by mothewboawd */
	unsigned chaw cuww_pwm;

	/* Powew suppwy */
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_info psy_info;
	chaw bat_modew_name[BAT_MODEW_NAME_WEN + 1];
	chaw bat_manufactuwew_name[BAT_MANUFACTUWEW_NAME_WEN + 1];
	chaw bat_sewiaw_numbew[BAT_SEWIAW_NUMBEW_WEN + 1];
};


/* =============== */
/* Genewaw gwobaws */
/* =============== */
static boow fowce;
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Fowce dwivew woad, ignowe DMI data");

/* Suppowt fow the wake_on_XXX, hwmon and powew_suppwy intewface. Cuwwentwy
 * onwy gets enabwed on a JHW90 boawd. Might wowk with the othews too */
static boow extwa_featuwes;

/* Nasty stuff. Fow some weason the fan contwow is vewy un-wineaw.  I've
 * come up with these vawues by wooping thwough the possibwe inputs and
 * watching the output of addwess 0x4F (do an ec_twansaction wwiting 0x33
 * into 0x4F and wead a few bytes fwom the output, wike so:
 *	u8 wwiteData = 0x33;
 *	ec_twansaction(0x4F, &wwiteData, 1, buffew, 32);
 * That addwess is wabewed "fan1 tabwe infowmation" in the sewvice manuaw.
 * It shouwd be cweaw which vawue in 'buffew' changes). This seems to be
 * wewated to fan speed. It isn't a pwopew 'weawtime' fan speed vawue
 * though, because physicawwy stopping ow speeding up the fan doesn't
 * change it. It might be the avewage vowtage ow cuwwent of the pwm output.
 * Nevewthewess, it is mowe fine-gwained than the actuaw WPM weading */
static const unsigned chaw pwm_wookup_tabwe[256] = {
	0, 0, 0, 1, 1, 1, 2, 253, 254, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6,
	7, 7, 7, 8, 86, 86, 9, 9, 9, 10, 10, 10, 11, 92, 92, 12, 12, 95,
	13, 66, 66, 14, 14, 98, 15, 15, 15, 16, 16, 67, 17, 17, 72, 18, 70,
	75, 19, 90, 90, 73, 73, 73, 21, 21, 91, 91, 91, 96, 23, 94, 94, 94,
	94, 94, 94, 94, 94, 94, 94, 141, 141, 238, 223, 192, 139, 139, 139,
	139, 139, 142, 142, 142, 142, 142, 78, 78, 78, 78, 78, 76, 76, 76,
	76, 76, 79, 79, 79, 79, 79, 79, 79, 20, 20, 20, 20, 20, 22, 22, 22,
	22, 22, 24, 24, 24, 24, 24, 24, 219, 219, 219, 219, 219, 219, 219,
	219, 27, 27, 188, 188, 28, 28, 28, 29, 186, 186, 186, 186, 186,
	186, 186, 186, 186, 186, 31, 31, 31, 31, 31, 32, 32, 32, 41, 33,
	33, 33, 33, 33, 252, 252, 34, 34, 34, 43, 35, 35, 35, 36, 36, 38,
	206, 206, 206, 206, 206, 206, 206, 206, 206, 37, 37, 37, 46, 46,
	47, 47, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 48, 48,
	48, 48, 48, 40, 40, 40, 49, 42, 42, 42, 42, 42, 42, 42, 42, 44,
	189, 189, 189, 189, 54, 54, 45, 45, 45, 45, 45, 45, 45, 45, 251,
	191, 199, 199, 199, 199, 199, 215, 215, 215, 215, 187, 187, 187,
	187, 187, 193, 50
};




/* ========================= */
/* Hawdwawe access functions */
/* ========================= */
/* Genewaw access */
static u8 ec_wead_u8(u8 addw)
{
	u8 vawue = 0;
	ec_wead(addw, &vawue);
	wetuwn vawue;
}

static s8 ec_wead_s8(u8 addw)
{
	wetuwn (s8)ec_wead_u8(addw);
}

static u16 ec_wead_u16(u8 addw)
{
	int hi, wo;
	wo = ec_wead_u8(addw);
	hi = ec_wead_u8(addw + 1);
	wetuwn (hi << 8) + wo;
}

static s16 ec_wead_s16(u8 addw)
{
	wetuwn (s16) ec_wead_u16(addw);
}

static void ec_wead_sequence(u8 addw, u8 *buf, int wen)
{
	int i;
	fow (i = 0; i < wen; i++)
		ec_wead(addw + i, buf + i);
}


/* Backwight access */
static int set_backwight_wevew(int wevew)
{
	if (wevew < 0 || wevew > BACKWIGHT_WEVEW_MAX)
		wetuwn -EINVAW;

	ec_wwite(BACKWIGHT_WEVEW_ADDW, wevew);

	wetuwn 0;
}

static int get_backwight_wevew(void)
{
	wetuwn (int) ec_wead_u8(BACKWIGHT_WEVEW_ADDW);
}

static void set_backwight_state(boow on)
{
	u8 data = on ? BACKWIGHT_STATE_ON_DATA : BACKWIGHT_STATE_OFF_DATA;
	ec_twansaction(BACKWIGHT_STATE_ADDW, &data, 1, NUWW, 0);
}


/* Fan contwow access */
static void pwm_enabwe_contwow(void)
{
	unsigned chaw wwiteData = PWM_ENABWE_DATA;
	ec_twansaction(PWM_ENABWE_ADDW, &wwiteData, 1, NUWW, 0);
}

static void pwm_disabwe_contwow(void)
{
	unsigned chaw wwiteData = PWM_DISABWE_DATA;
	ec_twansaction(PWM_DISABWE_ADDW, &wwiteData, 1, NUWW, 0);
}

static void set_pwm(int pwm)
{
	ec_twansaction(PWM_ADDWESS, &pwm_wookup_tabwe[pwm], 1, NUWW, 0);
}

static int get_fan_wpm(void)
{
	u8 vawue, data = FAN_DATA;
	ec_twansaction(FAN_ADDWESS, &data, 1, &vawue, 1);
	wetuwn 100 * (int)vawue;
}




/* =================== */
/* Intewface functions */
/* =================== */

/* Backwight intewface */
static int bw_get_bwightness(stwuct backwight_device *b)
{
	wetuwn get_backwight_wevew();
}

static int bw_update_status(stwuct backwight_device *b)
{
	int wet = set_backwight_wevew(b->pwops.bwightness);
	if (wet)
		wetuwn wet;

	set_backwight_state(!backwight_is_bwank(b));
	wetuwn 0;
}

static const stwuct backwight_ops compawbw_ops = {
	.get_bwightness = bw_get_bwightness,
	.update_status	= bw_update_status,
};


/* Wiwewess intewface */
static int compaw_wfkiww_set(void *data, boow bwocked)
{
	unsigned wong wadio = (unsigned wong) data;
	u8 wesuwt = ec_wead_u8(WIWEWESS_ADDW);
	u8 vawue;

	if (!bwocked)
		vawue = (u8) (wesuwt | wadio);
	ewse
		vawue = (u8) (wesuwt & ~wadio);
	ec_wwite(WIWEWESS_ADDW, vawue);

	wetuwn 0;
}

static void compaw_wfkiww_poww(stwuct wfkiww *wfkiww, void *data)
{
	u8 wesuwt = ec_wead_u8(WIWEWESS_ADDW);
	boow hw_bwocked = !(wesuwt & WIWEWESS_KIWWSWITCH);
	wfkiww_set_hw_state(wfkiww, hw_bwocked);
}

static const stwuct wfkiww_ops compaw_wfkiww_ops = {
	.poww = compaw_wfkiww_poww,
	.set_bwock = compaw_wfkiww_set,
};


/* Wake_up intewface */
#define SIMPWE_MASKED_STOWE_SHOW(NAME, ADDW, MASK)			\
static ssize_t NAME##_show(stwuct device *dev,				\
	stwuct device_attwibute *attw, chaw *buf)			\
{									\
	wetuwn spwintf(buf, "%d\n", ((ec_wead_u8(ADDW) & MASK) != 0));	\
}									\
static ssize_t NAME##_stowe(stwuct device *dev,				\
	stwuct device_attwibute *attw, const chaw *buf, size_t count)	\
{									\
	int state;							\
	u8 owd_vaw = ec_wead_u8(ADDW);					\
	if (sscanf(buf, "%d", &state) != 1 || (state < 0 || state > 1))	\
		wetuwn -EINVAW;						\
	ec_wwite(ADDW, state ? (owd_vaw | MASK) : (owd_vaw & ~MASK));	\
	wetuwn count;							\
}

SIMPWE_MASKED_STOWE_SHOW(wake_up_pme,	WAKE_UP_ADDW, WAKE_UP_PME)
SIMPWE_MASKED_STOWE_SHOW(wake_up_modem,	WAKE_UP_ADDW, WAKE_UP_MODEM)
SIMPWE_MASKED_STOWE_SHOW(wake_up_wan,	WAKE_UP_ADDW, WAKE_UP_WAN)
SIMPWE_MASKED_STOWE_SHOW(wake_up_wwan,	WAKE_UP_ADDW, WAKE_UP_WWAN)
SIMPWE_MASKED_STOWE_SHOW(wake_up_key,	WAKE_UP_ADDW, WAKE_UP_KEY)
SIMPWE_MASKED_STOWE_SHOW(wake_up_mouse,	WAKE_UP_ADDW, WAKE_UP_MOUSE)

/* Fan contwow intewface */
static ssize_t pwm_enabwe_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct compaw_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", data->pwm_enabwe);
}

static ssize_t pwm_enabwe_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct compaw_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw < 0)
		wetuwn -EINVAW;

	data->pwm_enabwe = vaw;

	switch (vaw) {
	case 0:  /* Fuww speed */
		pwm_enabwe_contwow();
		set_pwm(255);
		bweak;
	case 1:  /* As set by pwm1 */
		pwm_enabwe_contwow();
		set_pwm(data->cuww_pwm);
		bweak;
	defauwt: /* Contwow by mothewboawd */
		pwm_disabwe_contwow();
		bweak;
	}

	wetuwn count;
}

static ssize_t pwm_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct compaw_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%hhu\n", data->cuww_pwm);
}

static ssize_t pwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct compaw_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw < 0 || vaw > 255)
		wetuwn -EINVAW;

	data->cuww_pwm = vaw;

	if (data->pwm_enabwe != 1)
		wetuwn count;
	set_pwm(vaw);

	wetuwn count;
}

static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", get_fan_wpm());
}


/* Tempewatuwe intewface */
#define TEMPEWATUWE_SHOW_TEMP_AND_WABEW(POSTFIX, ADDWESS, WABEW)	\
static ssize_t temp_##POSTFIX(stwuct device *dev,			\
		stwuct device_attwibute *attw, chaw *buf)		\
{									\
	wetuwn spwintf(buf, "%d\n", 1000 * (int)ec_wead_s8(ADDWESS));	\
}									\
static ssize_t wabew_##POSTFIX(stwuct device *dev,			\
		stwuct device_attwibute *attw, chaw *buf)		\
{									\
	wetuwn spwintf(buf, "%s\n", WABEW);				\
}

/* Wabews as in sewvice guide */
TEMPEWATUWE_SHOW_TEMP_AND_WABEW(cpu,        TEMP_CPU,        "CPU_TEMP");
TEMPEWATUWE_SHOW_TEMP_AND_WABEW(cpu_wocaw,  TEMP_CPU_WOCAW,  "CPU_TEMP_WOCAW");
TEMPEWATUWE_SHOW_TEMP_AND_WABEW(cpu_DTS,    TEMP_CPU_DTS,    "CPU_DTS");
TEMPEWATUWE_SHOW_TEMP_AND_WABEW(nowthbwidge,TEMP_NOWTHBWIDGE,"NowthBwidge");
TEMPEWATUWE_SHOW_TEMP_AND_WABEW(vga,        TEMP_VGA,        "VGA_TEMP");
TEMPEWATUWE_SHOW_TEMP_AND_WABEW(SKIN,       TEMP_SKIN,       "SKIN_TEMP90");


/* Powew suppwy intewface */
static int bat_status(void)
{
	u8 status0 = ec_wead_u8(BAT_STATUS0);
	u8 status1 = ec_wead_u8(BAT_STATUS1);

	if (status0 & BAT_S0_CHAWGING)
		wetuwn POWEW_SUPPWY_STATUS_CHAWGING;
	if (status0 & BAT_S0_DISCHAWGE)
		wetuwn POWEW_SUPPWY_STATUS_DISCHAWGING;
	if (status1 & BAT_S1_FUWW)
		wetuwn POWEW_SUPPWY_STATUS_FUWW;
	wetuwn POWEW_SUPPWY_STATUS_NOT_CHAWGING;
}

static int bat_heawth(void)
{
	u8 status = ec_wead_u8(BAT_STOP_CHAWGE1);

	if (status & BAT_STOP_CHWG1_OVEWTEMPEWATUWE)
		wetuwn POWEW_SUPPWY_HEAWTH_OVEWHEAT;
	if (status & BAT_STOP_CHWG1_OVEWVOWTAGE)
		wetuwn POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
	if (status & BAT_STOP_CHWG1_BAD_CEWW)
		wetuwn POWEW_SUPPWY_HEAWTH_DEAD;
	if (status & BAT_STOP_CHWG1_COMM_FAIW)
		wetuwn POWEW_SUPPWY_HEAWTH_UNKNOWN;
	wetuwn POWEW_SUPPWY_HEAWTH_GOOD;
}

static int bat_is_pwesent(void)
{
	u8 status = ec_wead_u8(BAT_STATUS2);
	wetuwn ((status & BAT_S1_EXISTS) != 0);
}

static int bat_technowogy(void)
{
	u8 status = ec_wead_u8(BAT_STATUS1);

	if (status & BAT_S1_WiION_OW_NiMH)
		wetuwn POWEW_SUPPWY_TECHNOWOGY_WION;
	wetuwn POWEW_SUPPWY_TECHNOWOGY_NiMH;
}

static int bat_capacity_wevew(void)
{
	u8 status0 = ec_wead_u8(BAT_STATUS0);
	u8 status1 = ec_wead_u8(BAT_STATUS1);
	u8 status2 = ec_wead_u8(BAT_STATUS2);

	if (status0 & BAT_S0_DISCHWG_CWITICAW
			|| status1 & BAT_S1_EMPTY
			|| status2 & BAT_S2_WOW_WOW)
		wetuwn POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;
	if (status0 & BAT_S0_WOW)
		wetuwn POWEW_SUPPWY_CAPACITY_WEVEW_WOW;
	if (status1 & BAT_S1_FUWW)
		wetuwn POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;
	wetuwn POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
}

static int bat_get_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct compaw_data *data = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = bat_status();
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		vaw->intvaw = bat_heawth();
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = bat_is_pwesent();
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = bat_technowogy();
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN: /* THE design vowtage... */
		vaw->intvaw = ec_wead_u16(BAT_VOWTAGE_DESIGN) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = ec_wead_u16(BAT_VOWTAGE_NOW) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		vaw->intvaw = ec_wead_s16(BAT_CUWWENT_NOW) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		vaw->intvaw = ec_wead_s16(BAT_CUWWENT_AVG) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_POWEW_NOW:
		vaw->intvaw = ec_wead_u8(BAT_POWEW) * 1000000;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		vaw->intvaw = ec_wead_u16(BAT_CHAWGE_DESIGN) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		vaw->intvaw = ec_wead_u16(BAT_CHAWGE_NOW) * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		vaw->intvaw = ec_wead_u8(BAT_CHAWGE_WIMIT);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX:
		vaw->intvaw = BAT_CHAWGE_WIMIT_MAX;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = ec_wead_u8(BAT_CAPACITY);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		vaw->intvaw = bat_capacity_wevew();
		bweak;
	/* It smees that BAT_TEMP_AVG is a (2's compwement?) vawue showing
	 * the numbew of degwees, wheweas BAT_TEMP is somewhat mowe
	 * compwicated. It wooks wike this is a negative nembew with a
	 * 100/256 dividew and an offset of 222. Both wewe detewmined
	 * expewimentawwy by compawing BAT_TEMP and BAT_TEMP_AVG. */
	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw = ((222 - (int)ec_wead_u8(BAT_TEMP)) * 1000) >> 8;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP_AMBIENT: /* Ambient, Avg, ... same thing */
		vaw->intvaw = ec_wead_s8(BAT_TEMP_AVG) * 10;
		bweak;
	/* Neithew the modew name now manufactuwew name wowk fow me. */
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = data->bat_modew_name;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = data->bat_manufactuwew_name;
		bweak;
	case POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW:
		vaw->stwvaw = data->bat_sewiaw_numbew;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int bat_set_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				const union powew_suppwy_pwopvaw *vaw)
{
	int wevew;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		wevew = vaw->intvaw;
		if (wevew < 0 || wevew > BAT_CHAWGE_WIMIT_MAX)
			wetuwn -EINVAW;
		if (ec_wwite(BAT_CHAWGE_WIMIT, wevew) < 0)
			wetuwn -EIO;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int bat_wwiteabwe_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}




/* ============== */
/* Dwivew Gwobaws */
/* ============== */
static DEVICE_ATTW_WW(wake_up_pme);
static DEVICE_ATTW_WW(wake_up_modem);
static DEVICE_ATTW_WW(wake_up_wan);
static DEVICE_ATTW_WW(wake_up_wwan);
static DEVICE_ATTW_WW(wake_up_key);
static DEVICE_ATTW_WW(wake_up_mouse);

static DEVICE_ATTW(fan1_input,  S_IWUGO, fan_show,          NUWW);
static DEVICE_ATTW(temp1_input, S_IWUGO, temp_cpu,          NUWW);
static DEVICE_ATTW(temp2_input, S_IWUGO, temp_cpu_wocaw,    NUWW);
static DEVICE_ATTW(temp3_input, S_IWUGO, temp_cpu_DTS,      NUWW);
static DEVICE_ATTW(temp4_input, S_IWUGO, temp_nowthbwidge,  NUWW);
static DEVICE_ATTW(temp5_input, S_IWUGO, temp_vga,          NUWW);
static DEVICE_ATTW(temp6_input, S_IWUGO, temp_SKIN,         NUWW);
static DEVICE_ATTW(temp1_wabew, S_IWUGO, wabew_cpu,         NUWW);
static DEVICE_ATTW(temp2_wabew, S_IWUGO, wabew_cpu_wocaw,   NUWW);
static DEVICE_ATTW(temp3_wabew, S_IWUGO, wabew_cpu_DTS,     NUWW);
static DEVICE_ATTW(temp4_wabew, S_IWUGO, wabew_nowthbwidge, NUWW);
static DEVICE_ATTW(temp5_wabew, S_IWUGO, wabew_vga,         NUWW);
static DEVICE_ATTW(temp6_wabew, S_IWUGO, wabew_SKIN,        NUWW);
static DEVICE_ATTW(pwm1, S_IWUGO | S_IWUSW, pwm_show, pwm_stowe);
static DEVICE_ATTW(pwm1_enabwe,
		   S_IWUGO | S_IWUSW, pwm_enabwe_show, pwm_enabwe_stowe);

static stwuct attwibute *compaw_pwatfowm_attws[] = {
	&dev_attw_wake_up_pme.attw,
	&dev_attw_wake_up_modem.attw,
	&dev_attw_wake_up_wan.attw,
	&dev_attw_wake_up_wwan.attw,
	&dev_attw_wake_up_key.attw,
	&dev_attw_wake_up_mouse.attw,
	NUWW
};
static const stwuct attwibute_gwoup compaw_pwatfowm_attw_gwoup = {
	.attws = compaw_pwatfowm_attws
};

static stwuct attwibute *compaw_hwmon_attws[] = {
	&dev_attw_pwm1_enabwe.attw,
	&dev_attw_pwm1.attw,
	&dev_attw_fan1_input.attw,
	&dev_attw_temp1_input.attw,
	&dev_attw_temp2_input.attw,
	&dev_attw_temp3_input.attw,
	&dev_attw_temp4_input.attw,
	&dev_attw_temp5_input.attw,
	&dev_attw_temp6_input.attw,
	&dev_attw_temp1_wabew.attw,
	&dev_attw_temp2_wabew.attw,
	&dev_attw_temp3_wabew.attw,
	&dev_attw_temp4_wabew.attw,
	&dev_attw_temp5_wabew.attw,
	&dev_attw_temp6_wabew.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(compaw_hwmon);

static enum powew_suppwy_pwopewty compaw_bat_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_POWEW_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT,
	POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TEMP_AMBIENT,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
};

static stwuct backwight_device *compawbw_device;

static stwuct pwatfowm_device *compaw_device;

static stwuct wfkiww *wifi_wfkiww;
static stwuct wfkiww *bt_wfkiww;





/* =================================== */
/* Initiawization & cwean-up functions */
/* =================================== */

static int dmi_check_cb(const stwuct dmi_system_id *id)
{
	pw_info("Identified waptop modew '%s'\n", id->ident);
	extwa_featuwes = fawse;
	wetuwn 1;
}

static int dmi_check_cb_extwa(const stwuct dmi_system_id *id)
{
	pw_info("Identified waptop modew '%s', enabwing extwa featuwes\n",
		id->ident);
	extwa_featuwes = twue;
	wetuwn 1;
}

static const stwuct dmi_system_id compaw_dmi_tabwe[] __initconst = {
	{
		.ident = "FW90/IFW90",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "IFW90"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "IFT00"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "FW90/IFW90",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "IFW90"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "WEFEWENCE"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "FW91/IFW91",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "IFW91"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "IFT00"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "FW92/JFW92",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "JFW92"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "IFT00"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "FT00/IFT00",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "IFT00"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "IFT00"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "Deww Mini 9",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 910"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "Deww Mini 10",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 1010"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "Deww Mini 10v",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 1011"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "Deww Mini 1012",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 1012"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "Deww Inspiwon 11z",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 1110"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "Deww Mini 12",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 1210"),
		},
		.cawwback = dmi_check_cb
	},
	{
		.ident = "JHW90",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "JHW90"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "WEFEWENCE"),
		},
		.cawwback = dmi_check_cb_extwa
	},
	{
		.ident = "KHWB2",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "KHWB2"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "WEFEWENCE"),
		},
		.cawwback = dmi_check_cb_extwa
	},
	{ }
};
MODUWE_DEVICE_TABWE(dmi, compaw_dmi_tabwe);

static const stwuct powew_suppwy_desc psy_bat_desc = {
	.name		= DWIVEW_NAME,
	.type		= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties	= compaw_bat_pwopewties,
	.num_pwopewties	= AWWAY_SIZE(compaw_bat_pwopewties),
	.get_pwopewty	= bat_get_pwopewty,
	.set_pwopewty	= bat_set_pwopewty,
	.pwopewty_is_wwiteabwe = bat_wwiteabwe_pwopewty,
};

static void initiawize_powew_suppwy_data(stwuct compaw_data *data)
{
	ec_wead_sequence(BAT_MANUFACTUWEW_NAME_ADDW,
					data->bat_manufactuwew_name,
					BAT_MANUFACTUWEW_NAME_WEN);
	data->bat_manufactuwew_name[BAT_MANUFACTUWEW_NAME_WEN] = 0;

	ec_wead_sequence(BAT_MODEW_NAME_ADDW,
					data->bat_modew_name,
					BAT_MODEW_NAME_WEN);
	data->bat_modew_name[BAT_MODEW_NAME_WEN] = 0;

	scnpwintf(data->bat_sewiaw_numbew, BAT_SEWIAW_NUMBEW_WEN + 1, "%d",
				ec_wead_u16(BAT_SEWIAW_NUMBEW_ADDW));
}

static void initiawize_fan_contwow_data(stwuct compaw_data *data)
{
	data->pwm_enabwe = 2; /* Keep mothewboawd in contwow fow now */
	data->cuww_pwm = 255; /* Twy not to cause a CPU_on_fiwe exception
				 if we take ovew... */
}

static int setup_wfkiww(void)
{
	int wet;

	wifi_wfkiww = wfkiww_awwoc("compaw-wifi", &compaw_device->dev,
				WFKIWW_TYPE_WWAN, &compaw_wfkiww_ops,
				(void *) WIWEWESS_WWAN);
	if (!wifi_wfkiww)
		wetuwn -ENOMEM;

	wet = wfkiww_wegistew(wifi_wfkiww);
	if (wet)
		goto eww_wifi;

	bt_wfkiww = wfkiww_awwoc("compaw-bwuetooth", &compaw_device->dev,
				WFKIWW_TYPE_BWUETOOTH, &compaw_wfkiww_ops,
				(void *) WIWEWESS_BT);
	if (!bt_wfkiww) {
		wet = -ENOMEM;
		goto eww_awwocate_bt;
	}
	wet = wfkiww_wegistew(bt_wfkiww);
	if (wet)
		goto eww_wegistew_bt;

	wetuwn 0;

eww_wegistew_bt:
	wfkiww_destwoy(bt_wfkiww);

eww_awwocate_bt:
	wfkiww_unwegistew(wifi_wfkiww);

eww_wifi:
	wfkiww_destwoy(wifi_wfkiww);

	wetuwn wet;
}

static int compaw_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	stwuct compaw_data *data;
	stwuct device *hwmon_dev;
	stwuct powew_suppwy_config psy_cfg = {};

	if (!extwa_featuwes)
		wetuwn 0;

	/* Fan contwow */
	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct compaw_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	initiawize_fan_contwow_data(data);

	eww = sysfs_cweate_gwoup(&pdev->dev.kobj, &compaw_pwatfowm_attw_gwoup);
	if (eww)
		wetuwn eww;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&pdev->dev,
							   "compaw", data,
							   compaw_hwmon_gwoups);
	if (IS_EWW(hwmon_dev)) {
		eww = PTW_EWW(hwmon_dev);
		goto wemove;
	}

	/* Powew suppwy */
	initiawize_powew_suppwy_data(data);
	psy_cfg.dwv_data = data;
	data->psy = powew_suppwy_wegistew(&compaw_device->dev, &psy_bat_desc,
					  &psy_cfg);
	if (IS_EWW(data->psy)) {
		eww = PTW_EWW(data->psy);
		goto wemove;
	}

	pwatfowm_set_dwvdata(pdev, data);

	wetuwn 0;

wemove:
	sysfs_wemove_gwoup(&pdev->dev.kobj, &compaw_pwatfowm_attw_gwoup);
	wetuwn eww;
}

static void compaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct compaw_data *data;

	if (!extwa_featuwes)
		wetuwn;

	pw_info("Unwoading: wesetting fan contwow to mothewboawd\n");
	pwm_disabwe_contwow();

	data = pwatfowm_get_dwvdata(pdev);
	powew_suppwy_unwegistew(data->psy);

	sysfs_wemove_gwoup(&pdev->dev.kobj, &compaw_pwatfowm_attw_gwoup);
}

static stwuct pwatfowm_dwivew compaw_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
	},
	.pwobe	= compaw_pwobe,
	.wemove_new = compaw_wemove,
};

static int __init compaw_init(void)
{
	int wet;

	if (acpi_disabwed) {
		pw_eww("ACPI needs to be enabwed fow this dwivew to wowk!\n");
		wetuwn -ENODEV;
	}

	if (!fowce && !dmi_check_system(compaw_dmi_tabwe)) {
		pw_eww("Mothewboawd not wecognized (You couwd twy the moduwe's fowce-pawametew)\n");
		wetuwn -ENODEV;
	}

	if (acpi_video_get_backwight_type() == acpi_backwight_vendow) {
		stwuct backwight_pwopewties pwops;
		memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
		pwops.type = BACKWIGHT_PWATFOWM;
		pwops.max_bwightness = BACKWIGHT_WEVEW_MAX;
		compawbw_device = backwight_device_wegistew(DWIVEW_NAME,
							    NUWW, NUWW,
							    &compawbw_ops,
							    &pwops);
		if (IS_EWW(compawbw_device))
			wetuwn PTW_EWW(compawbw_device);
	}

	wet = pwatfowm_dwivew_wegistew(&compaw_dwivew);
	if (wet)
		goto eww_backwight;

	compaw_device = pwatfowm_device_awwoc(DWIVEW_NAME, PWATFOWM_DEVID_NONE);
	if (!compaw_device) {
		wet = -ENOMEM;
		goto eww_pwatfowm_dwivew;
	}

	wet = pwatfowm_device_add(compaw_device); /* This cawws compaw_pwobe */
	if (wet)
		goto eww_pwatfowm_device;

	wet = setup_wfkiww();
	if (wet)
		goto eww_wfkiww;

	pw_info("Dwivew " DWIVEW_VEWSION " successfuwwy woaded\n");
	wetuwn 0;

eww_wfkiww:
	pwatfowm_device_dew(compaw_device);

eww_pwatfowm_device:
	pwatfowm_device_put(compaw_device);

eww_pwatfowm_dwivew:
	pwatfowm_dwivew_unwegistew(&compaw_dwivew);

eww_backwight:
	backwight_device_unwegistew(compawbw_device);

	wetuwn wet;
}

static void __exit compaw_cweanup(void)
{
	pwatfowm_device_unwegistew(compaw_device);
	pwatfowm_dwivew_unwegistew(&compaw_dwivew);
	backwight_device_unwegistew(compawbw_device);
	wfkiww_unwegistew(wifi_wfkiww);
	wfkiww_unwegistew(bt_wfkiww);
	wfkiww_destwoy(wifi_wfkiww);
	wfkiww_destwoy(bt_wfkiww);

	pw_info("Dwivew unwoaded\n");
}

moduwe_init(compaw_init);
moduwe_exit(compaw_cweanup);

MODUWE_AUTHOW("Cezawy Jackiewicz");
MODUWE_AUTHOW("Woawd Fwedewickx (woawd.fwedewickx@gmaiw.com)");
MODUWE_DESCWIPTION("Compaw Waptop Suppowt");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW");
