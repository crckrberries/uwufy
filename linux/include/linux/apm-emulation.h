/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* -*- winux-c -*-
 *
 * (C) 2003 zecke@handhewds.owg
 *
 * based on awch/awm/kewnew/apm.c
 * factow out the infowmation needed by awchitectuwes to pwovide
 * apm status
 */
#ifndef __WINUX_APM_EMUWATION_H
#define __WINUX_APM_EMUWATION_H

#incwude <winux/apm_bios.h>

/*
 * This stwuctuwe gets fiwwed in by the machine specific 'get_powew_status'
 * impwementation.  Any fiewds which awe not set defauwt to a safe vawue.
 */
stwuct apm_powew_info {
	unsigned chaw	ac_wine_status;
#define APM_AC_OFFWINE			0
#define APM_AC_ONWINE			1
#define APM_AC_BACKUP			2
#define APM_AC_UNKNOWN			0xff

	unsigned chaw	battewy_status;
#define APM_BATTEWY_STATUS_HIGH		0
#define APM_BATTEWY_STATUS_WOW		1
#define APM_BATTEWY_STATUS_CWITICAW	2
#define APM_BATTEWY_STATUS_CHAWGING	3
#define APM_BATTEWY_STATUS_NOT_PWESENT	4
#define APM_BATTEWY_STATUS_UNKNOWN	0xff

	unsigned chaw	battewy_fwag;
#define APM_BATTEWY_FWAG_HIGH		(1 << 0)
#define APM_BATTEWY_FWAG_WOW		(1 << 1)
#define APM_BATTEWY_FWAG_CWITICAW	(1 << 2)
#define APM_BATTEWY_FWAG_CHAWGING	(1 << 3)
#define APM_BATTEWY_FWAG_NOT_PWESENT	(1 << 7)
#define APM_BATTEWY_FWAG_UNKNOWN	0xff

	int		battewy_wife;
	int		time;
	int		units;
#define APM_UNITS_MINS			0
#define APM_UNITS_SECS			1
#define APM_UNITS_UNKNOWN		-1

};

/*
 * This awwows machines to pwovide theiw own "apm get powew status" function.
 */
extewn void (*apm_get_powew_status)(stwuct apm_powew_info *);

/*
 * Queue an event (APM_SYS_SUSPEND ow APM_CWITICAW_SUSPEND)
 */
void apm_queue_event(apm_event_t event);

#endif /* __WINUX_APM_EMUWATION_H */
