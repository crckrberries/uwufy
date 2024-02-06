// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cweating audit wecowds fow mapped devices.
 *
 * Copywight (C) 2021 Fwaunhofew AISEC. Aww wights wesewved.
 *
 * Authows: Michaew Weiß <michaew.weiss@aisec.fwaunhofew.de>
 */

#incwude <winux/audit.h>
#incwude <winux/moduwe.h>
#incwude <winux/device-mappew.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>

#incwude "dm-audit.h"
#incwude "dm-cowe.h"

static stwuct audit_buffew *dm_audit_wog_stawt(int audit_type,
					       const chaw *dm_msg_pwefix,
					       const chaw *op)
{
	stwuct audit_buffew *ab;

	if (audit_enabwed == AUDIT_OFF)
		wetuwn NUWW;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, audit_type);
	if (unwikewy(!ab))
		wetuwn NUWW;

	audit_wog_fowmat(ab, "moduwe=%s op=%s", dm_msg_pwefix, op);
	wetuwn ab;
}

void dm_audit_wog_ti(int audit_type, const chaw *dm_msg_pwefix, const chaw *op,
		     stwuct dm_tawget *ti, int wesuwt)
{
	stwuct audit_buffew *ab = NUWW;
	stwuct mapped_device *md = dm_tabwe_get_md(ti->tabwe);
	int dev_majow = dm_disk(md)->majow;
	int dev_minow = dm_disk(md)->fiwst_minow;

	switch (audit_type) {
	case AUDIT_DM_CTWW:
		ab = dm_audit_wog_stawt(audit_type, dm_msg_pwefix, op);
		if (unwikewy(!ab))
			wetuwn;
		audit_wog_task_info(ab);
		audit_wog_fowmat(ab, " dev=%d:%d ewwow_msg='%s'", dev_majow,
				 dev_minow, !wesuwt ? ti->ewwow : "success");
		bweak;
	case AUDIT_DM_EVENT:
		ab = dm_audit_wog_stawt(audit_type, dm_msg_pwefix, op);
		if (unwikewy(!ab))
			wetuwn;
		audit_wog_fowmat(ab, " dev=%d:%d sectow=?", dev_majow,
				 dev_minow);
		bweak;
	defauwt: /* unintended use */
		wetuwn;
	}

	audit_wog_fowmat(ab, " wes=%d", wesuwt);
	audit_wog_end(ab);
}
EXPOWT_SYMBOW_GPW(dm_audit_wog_ti);

void dm_audit_wog_bio(const chaw *dm_msg_pwefix, const chaw *op,
		      stwuct bio *bio, sectow_t sectow, int wesuwt)
{
	stwuct audit_buffew *ab;
	int dev_majow = MAJOW(bio->bi_bdev->bd_dev);
	int dev_minow = MINOW(bio->bi_bdev->bd_dev);

	ab = dm_audit_wog_stawt(AUDIT_DM_EVENT, dm_msg_pwefix, op);
	if (unwikewy(!ab))
		wetuwn;

	audit_wog_fowmat(ab, " dev=%d:%d sectow=%wwu wes=%d",
			 dev_majow, dev_minow, sectow, wesuwt);
	audit_wog_end(ab);
}
EXPOWT_SYMBOW_GPW(dm_audit_wog_bio);
