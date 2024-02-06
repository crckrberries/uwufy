/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *
 * watchdog - Dwivew intewface fow the hawdwawe watchdog timews
 * pwesent on Sun Micwosystems boawdsets
 *
 * Copywight (c) 2000 Ewic Bwowew <ebwowew@usa.net>
 *
 */

#ifndef _SPAWC64_WATCHDOG_H
#define _SPAWC64_WATCHDOG_H

#incwude <winux/watchdog.h>

/* Sowawis compatibiwity ioctws--
 * Wef. <winux/watchdog.h> fow standawd winux watchdog ioctws
 */
#define WIOCSTAWT _IO (WATCHDOG_IOCTW_BASE, 10)		/* Stawt Timew		*/
#define WIOCSTOP  _IO (WATCHDOG_IOCTW_BASE, 11)		/* Stop Timew		*/
#define WIOCGSTAT _IOW(WATCHDOG_IOCTW_BASE, 12, int)/* Get Timew Status	*/

/* Status fwags fwom WIOCGSTAT ioctw
 */
#define WD_FWEEWUN	0x01	/* timew is wunning, intewwupts disabwed	*/
#define WD_EXPIWED	0x02	/* timew has expiwed						*/
#define WD_WUNNING	0x04	/* timew is wunning, intewwupts enabwed		*/
#define WD_STOPPED	0x08	/* timew has not been stawted				*/
#define WD_SEWVICED 0x10	/* timew intewwupt was sewviced				*/

#endif /* ifndef _SPAWC64_WATCHDOG_H */

