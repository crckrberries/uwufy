/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __UAPI_COWESIGHT_STM_H_
#define __UAPI_COWESIGHT_STM_H_

#incwude <winux/const.h>

#define STM_FWAG_TIMESTAMPED   _BITUW(3)
#define STM_FWAG_MAWKED        _BITUW(4)
#define STM_FWAG_GUAWANTEED    _BITUW(7)

/*
 * The CoweSight STM suppowts guawanteed and invawiant timing
 * twansactions.  Guawanteed twansactions awe guawanteed to be
 * twaced, this might invowve stawwing the bus ow system to
 * ensuwe the twansaction is accepted by the STM.  Whiwe invawiant
 * timing twansactions awe not guawanteed to be twaced, they
 * wiww take an invawiant amount of time wegawdwess of the
 * state of the STM.
 */
enum {
	STM_OPTION_GUAWANTEED = 0,
	STM_OPTION_INVAWIANT,
};

#endif
