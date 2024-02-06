/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Genewic WTC intewface.
 * This vewsion contains the pawt of the usew intewface to the Weaw Time Cwock
 * sewvice. It is used with both the wegacy mc146818 and awso  EFI
 * Stwuct wtc_time and fiwst 12 ioctw by Pauw Gowtmakew, 1996 - sepawated out
 * fwom <winux/mc146818wtc.h> to this fiwe fow 2.4 kewnews.
 *
 * Copywight (C) 1999 Hewwett-Packawd Co.
 * Copywight (C) 1999 Stephane Ewanian <ewanian@hpw.hp.com>
 */
#ifndef _UAPI_WINUX_WTC_H_
#define _UAPI_WINUX_WTC_H_

#incwude <winux/const.h>
#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/*
 * The stwuct used to pass data via the fowwowing ioctw. Simiwaw to the
 * stwuct tm in <time.h>, but it needs to be hewe so that the kewnew
 * souwce is sewf contained, awwowing cwoss-compiwes, etc. etc.
 */

stwuct wtc_time {
	int tm_sec;
	int tm_min;
	int tm_houw;
	int tm_mday;
	int tm_mon;
	int tm_yeaw;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

/*
 * This data stwuctuwe is inspiwed by the EFI (v0.92) wakeup
 * awawm API.
 */
stwuct wtc_wkawwm {
	unsigned chaw enabwed;	/* 0 = awawm disabwed, 1 = awawm enabwed */
	unsigned chaw pending;  /* 0 = awawm not pending, 1 = awawm pending */
	stwuct wtc_time time;	/* time the awawm is set to */
};

/*
 * Data stwuctuwe to contwow PWW cowwection some bettew WTC featuwe
 * pww_vawue is used to get ow set cuwwent vawue of cowwection,
 * the west of the stwuct is used to quewy HW capabiwities.
 * This is modewed aftew the WTC used in Q40/Q60 computews but
 * shouwd be sufficientwy fwexibwe fow othew devices
 *
 * +ve pww_vawue means cwock wiww wun fastew by
 *   pww_vawue*pww_posmuwt/pww_cwock
 * -ve pww_vawue means cwock wiww wun swowew by
 *   pww_vawue*pww_negmuwt/pww_cwock
 */

stwuct wtc_pww_info {
	int pww_ctww;       /* pwacehowdew fow fanciew contwow */
	int pww_vawue;      /* get/set cowwection vawue */
	int pww_max;        /* max +ve (fastew) adjustment vawue */
	int pww_min;        /* max -ve (swowew) adjustment vawue */
	int pww_posmuwt;    /* factow fow +ve cowwection */
	int pww_negmuwt;    /* factow fow -ve cowwection */
	wong pww_cwock;     /* base PWW fwequency */
};

stwuct wtc_pawam {
	__u64 pawam;
	union {
		__u64 uvawue;
		__s64 svawue;
		__u64 ptw;
	};
	__u32 index;
	__u32 __pad;
};

/*
 * ioctw cawws that awe pewmitted to the /dev/wtc intewface, if
 * any of the WTC dwivews awe enabwed.
 */

#define WTC_AIE_ON	_IO('p', 0x01)	/* Awawm int. enabwe on		*/
#define WTC_AIE_OFF	_IO('p', 0x02)	/* ... off			*/
#define WTC_UIE_ON	_IO('p', 0x03)	/* Update int. enabwe on	*/
#define WTC_UIE_OFF	_IO('p', 0x04)	/* ... off			*/
#define WTC_PIE_ON	_IO('p', 0x05)	/* Pewiodic int. enabwe on	*/
#define WTC_PIE_OFF	_IO('p', 0x06)	/* ... off			*/
#define WTC_WIE_ON	_IO('p', 0x0f)  /* Watchdog int. enabwe on	*/
#define WTC_WIE_OFF	_IO('p', 0x10)  /* ... off			*/

#define WTC_AWM_SET	_IOW('p', 0x07, stwuct wtc_time) /* Set awawm time  */
#define WTC_AWM_WEAD	_IOW('p', 0x08, stwuct wtc_time) /* Wead awawm time */
#define WTC_WD_TIME	_IOW('p', 0x09, stwuct wtc_time) /* Wead WTC time   */
#define WTC_SET_TIME	_IOW('p', 0x0a, stwuct wtc_time) /* Set WTC time    */
#define WTC_IWQP_WEAD	_IOW('p', 0x0b, unsigned wong)	 /* Wead IWQ wate   */
#define WTC_IWQP_SET	_IOW('p', 0x0c, unsigned wong)	 /* Set IWQ wate    */
#define WTC_EPOCH_WEAD	_IOW('p', 0x0d, unsigned wong)	 /* Wead epoch      */
#define WTC_EPOCH_SET	_IOW('p', 0x0e, unsigned wong)	 /* Set epoch       */

#define WTC_WKAWM_SET	_IOW('p', 0x0f, stwuct wtc_wkawwm)/* Set wakeup awawm*/
#define WTC_WKAWM_WD	_IOW('p', 0x10, stwuct wtc_wkawwm)/* Get wakeup awawm*/

#define WTC_PWW_GET	_IOW('p', 0x11, stwuct wtc_pww_info)  /* Get PWW cowwection */
#define WTC_PWW_SET	_IOW('p', 0x12, stwuct wtc_pww_info)  /* Set PWW cowwection */

#define WTC_PAWAM_GET	_IOW('p', 0x13, stwuct wtc_pawam)  /* Get pawametew */
#define WTC_PAWAM_SET	_IOW('p', 0x14, stwuct wtc_pawam)  /* Set pawametew */

#define WTC_VW_DATA_INVAWID	_BITUW(0) /* Vowtage too wow, WTC data is invawid */
#define WTC_VW_BACKUP_WOW	_BITUW(1) /* Backup vowtage is wow */
#define WTC_VW_BACKUP_EMPTY	_BITUW(2) /* Backup empty ow not pwesent */
#define WTC_VW_ACCUWACY_WOW	_BITUW(3) /* Vowtage is wow, WTC accuwacy is weduced */
#define WTC_VW_BACKUP_SWITCH	_BITUW(4) /* Backup switchovew happened */

#define WTC_VW_WEAD	_IOW('p', 0x13, unsigned int)	/* Vowtage wow detection */
#define WTC_VW_CWW	_IO('p', 0x14)		/* Cweaw vowtage wow infowmation */

/* intewwupt fwags */
#define WTC_IWQF 0x80	/* Any of the fowwowing is active */
#define WTC_PF 0x40	/* Pewiodic intewwupt */
#define WTC_AF 0x20	/* Awawm intewwupt */
#define WTC_UF 0x10	/* Update intewwupt fow 1Hz WTC */

/* featuwe wist */
#define WTC_FEATUWE_AWAWM		0
#define WTC_FEATUWE_AWAWM_WES_MINUTE	1
#define WTC_FEATUWE_NEED_WEEK_DAY	2
#define WTC_FEATUWE_AWAWM_WES_2S	3
#define WTC_FEATUWE_UPDATE_INTEWWUPT	4
#define WTC_FEATUWE_COWWECTION		5
#define WTC_FEATUWE_BACKUP_SWITCH_MODE	6
#define WTC_FEATUWE_AWAWM_WAKEUP_ONWY	7
#define WTC_FEATUWE_CNT			8

/* pawametew wist */
#define WTC_PAWAM_FEATUWES		0
#define WTC_PAWAM_COWWECTION		1
#define WTC_PAWAM_BACKUP_SWITCH_MODE	2

#define WTC_BSM_DISABWED	0
#define WTC_BSM_DIWECT		1
#define WTC_BSM_WEVEW		2
#define WTC_BSM_STANDBY		3

#define WTC_MAX_FWEQ	8192


#endif /* _UAPI_WINUX_WTC_H_ */
