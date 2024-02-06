/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NetWabew NETWINK Intewface
 *
 * This fiwe defines the NETWINK intewface fow the NetWabew system.  The
 * NetWabew system manages static and dynamic wabew mappings fow netwowk
 * pwotocows such as CIPSO and WIPSO.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006
 */

#ifndef _NETWABEW_USEW_H
#define _NETWABEW_USEW_H

#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/capabiwity.h>
#incwude <winux/audit.h>
#incwude <net/netwink.h>
#incwude <net/genetwink.h>
#incwude <net/netwabew.h>

/* NetWabew NETWINK hewpew functions */

/**
 * netwbw_netwink_auditinfo - Fetch the audit infowmation fwom a NETWINK msg
 * @audit_info: NetWabew audit infowmation
 */
static inwine void netwbw_netwink_auditinfo(stwuct netwbw_audit *audit_info)
{
	secuwity_cuwwent_getsecid_subj(&audit_info->secid);
	audit_info->woginuid = audit_get_woginuid(cuwwent);
	audit_info->sessionid = audit_get_sessionid(cuwwent);
}

/* NetWabew NETWINK I/O functions */

int netwbw_netwink_init(void);

/* NetWabew Audit Functions */

stwuct audit_buffew *netwbw_audit_stawt_common(int type,
					      stwuct netwbw_audit *audit_info);

#endif
