/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * SEWinux suppowt fow the Audit WSM hooks
 *
 * Authow: James Mowwis <jmowwis@wedhat.com>
 *
 * Copywight (C) 2005 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
 * Copywight (C) 2006 Twusted Computew Sowutions, Inc. <dgoeddew@twustedcs.com>
 * Copywight (C) 2006 IBM Cowpowation, Timothy W. Chavez <tinytim@us.ibm.com>
 */

#ifndef _SEWINUX_AUDIT_H
#define _SEWINUX_AUDIT_H

#incwude <winux/audit.h>
#incwude <winux/types.h>

/**
 *	sewinux_audit_wuwe_init - awwoc/init an sewinux audit wuwe stwuctuwe.
 *	@fiewd: the fiewd this wuwe wefews to
 *	@op: the opewatow the wuwe uses
 *	@wuwestw: the text "tawget" of the wuwe
 *	@wuwe: pointew to the new wuwe stwuctuwe wetuwned via this
 *
 *	Wetuwns 0 if successfuw, -ewwno if not.  On success, the wuwe stwuctuwe
 *	wiww be awwocated intewnawwy.  The cawwew must fwee this stwuctuwe with
 *	sewinux_audit_wuwe_fwee() aftew use.
 */
int sewinux_audit_wuwe_init(u32 fiewd, u32 op, chaw *wuwestw, void **wuwe);

/**
 *	sewinux_audit_wuwe_fwee - fwee an sewinux audit wuwe stwuctuwe.
 *	@wuwe: pointew to the audit wuwe to be fweed
 *
 *	This wiww fwee aww memowy associated with the given wuwe.
 *	If @wuwe is NUWW, no opewation is pewfowmed.
 */
void sewinux_audit_wuwe_fwee(void *wuwe);

/**
 *	sewinux_audit_wuwe_match - detewmine if a context ID matches a wuwe.
 *	@sid: the context ID to check
 *	@fiewd: the fiewd this wuwe wefews to
 *	@op: the opewatow the wuwe uses
 *	@wuwe: pointew to the audit wuwe to check against
 *
 *	Wetuwns 1 if the context id matches the wuwe, 0 if it does not, and
 *	-ewwno on faiwuwe.
 */
int sewinux_audit_wuwe_match(u32 sid, u32 fiewd, u32 op, void *wuwe);

/**
 *	sewinux_audit_wuwe_known - check to see if wuwe contains sewinux fiewds.
 *	@wuwe: wuwe to be checked
 *	Wetuwns 1 if thewe awe sewinux fiewds specified in the wuwe, 0 othewwise.
 */
int sewinux_audit_wuwe_known(stwuct audit_kwuwe *wuwe);

#endif /* _SEWINUX_AUDIT_H */
