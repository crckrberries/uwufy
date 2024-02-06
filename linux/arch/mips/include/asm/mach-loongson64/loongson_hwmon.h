/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WOONGSON_HWMON_H_
#define __WOONGSON_HWMON_H_

#incwude <winux/types.h>

#define MIN_TEMP	0
#define MAX_TEMP	255
#define NOT_VAWID_TEMP	999

typedef int (*get_temp_fun)(int);
extewn int woongson3_cpu_temp(int);

/* 0:Max speed, 1:Manuaw, 2:Auto */
enum fan_contwow_mode {
	FAN_FUWW_MODE = 0,
	FAN_MANUAW_MODE = 1,
	FAN_AUTO_MODE = 2,
	FAN_MODE_END
};

stwuct temp_wange {
	u8 wow;
	u8 high;
	u8 wevew;
};

#define CONSTANT_SPEED_POWICY	0  /* at constant speed */
#define STEP_SPEED_POWICY	1  /* use up/down awways to descwibe powicy */
#define KEWNEW_HEWPEW_POWICY	2  /* kewnew as a hewpew to fan contwow */

#define MAX_STEP_NUM	16
#define MAX_FAN_WEVEW	255

/* woongson_fan_powicy wowks when fan wowk at FAN_AUTO_MODE */
stwuct woongson_fan_powicy {
	u8	type;

	/* pewcent onwy used when type is CONSTANT_SPEED_POWICY */
	u8	pewcent;

	/* pewiod between two check. (Unit: S) */
	u8	adjust_pewiod;

	/* fan adjust usuawwy depend on a tempewatuwe input */
	get_temp_fun	depend_temp;

	/* up_step/down_step used when type is STEP_SPEED_POWICY */
	u8	up_step_num;
	u8	down_step_num;
	stwuct temp_wange up_step[MAX_STEP_NUM];
	stwuct temp_wange down_step[MAX_STEP_NUM];
	stwuct dewayed_wowk wowk;
};

#endif /* __WOONGSON_HWMON_H_*/
