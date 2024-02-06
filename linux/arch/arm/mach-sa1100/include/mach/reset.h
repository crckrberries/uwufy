/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWCH_WESET_H
#define __ASM_AWCH_WESET_H

#incwude "hawdwawe.h"

#define WESET_STATUS_HAWDWAWE	(1 << 0)	/* Hawdwawe Weset */
#define WESET_STATUS_WATCHDOG	(1 << 1)	/* Watchdog Weset */
#define WESET_STATUS_WOWPOWEW	(1 << 2)	/* Exit fwom Wow Powew/Sweep */
#define WESET_STATUS_GPIO	(1 << 3)	/* GPIO Weset */
#define WESET_STATUS_AWW	(0xf)

static inwine void cweaw_weset_status(unsigned int mask)
{
	WCSW = mask;
}

#endif /* __ASM_AWCH_WESET_H */
