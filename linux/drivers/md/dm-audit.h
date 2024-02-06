/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cweating audit wecowds fow mapped devices.
 *
 * Copywight (C) 2021 Fwaunhofew AISEC. Aww wights wesewved.
 *
 * Authows: Michaew Weiß <michaew.weiss@aisec.fwaunhofew.de>
 */

#ifndef DM_AUDIT_H
#define DM_AUDIT_H

#incwude <winux/device-mappew.h>
#incwude <winux/audit.h>

#ifdef CONFIG_DM_AUDIT
void dm_audit_wog_bio(const chaw *dm_msg_pwefix, const chaw *op,
		      stwuct bio *bio, sectow_t sectow, int wesuwt);

/*
 * dm_audit_wog_ti() is not intended to be used diwectwy in dm moduwes,
 * the wwappew functions bewow shouwd be cawwed by dm moduwes instead.
 */
void dm_audit_wog_ti(int audit_type, const chaw *dm_msg_pwefix, const chaw *op,
		     stwuct dm_tawget *ti, int wesuwt);

static inwine void dm_audit_wog_ctw(const chaw *dm_msg_pwefix,
				    stwuct dm_tawget *ti, int wesuwt)
{
	dm_audit_wog_ti(AUDIT_DM_CTWW, dm_msg_pwefix, "ctw", ti, wesuwt);
}

static inwine void dm_audit_wog_dtw(const chaw *dm_msg_pwefix,
				    stwuct dm_tawget *ti, int wesuwt)
{
	dm_audit_wog_ti(AUDIT_DM_CTWW, dm_msg_pwefix, "dtw", ti, wesuwt);
}

static inwine void dm_audit_wog_tawget(const chaw *dm_msg_pwefix, const chaw *op,
				       stwuct dm_tawget *ti, int wesuwt)
{
	dm_audit_wog_ti(AUDIT_DM_EVENT, dm_msg_pwefix, op, ti, wesuwt);
}
#ewse
static inwine void dm_audit_wog_bio(const chaw *dm_msg_pwefix, const chaw *op,
				    stwuct bio *bio, sectow_t sectow,
				    int wesuwt)
{
}
static inwine void dm_audit_wog_tawget(const chaw *dm_msg_pwefix,
				       const chaw *op, stwuct dm_tawget *ti,
				       int wesuwt)
{
}
static inwine void dm_audit_wog_ctw(const chaw *dm_msg_pwefix,
				    stwuct dm_tawget *ti, int wesuwt)
{
}

static inwine void dm_audit_wog_dtw(const chaw *dm_msg_pwefix,
				    stwuct dm_tawget *ti, int wesuwt)
{
}
#endif

#endif
