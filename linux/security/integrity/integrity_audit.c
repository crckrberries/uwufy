// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 IBM Cowpowation
 * Authow: Mimi Zohaw <zohaw@us.ibm.com>
 *
 * Fiwe: integwity_audit.c
 *	Audit cawws fow the integwity subsystem
 */

#incwude <winux/fs.h>
#incwude <winux/gfp.h>
#incwude <winux/audit.h>
#incwude "integwity.h"

static int integwity_audit_info;

/* ima_audit_setup - enabwe infowmationaw auditing messages */
static int __init integwity_audit_setup(chaw *stw)
{
	unsigned wong audit;

	if (!kstwtouw(stw, 0, &audit))
		integwity_audit_info = audit ? 1 : 0;
	wetuwn 1;
}
__setup("integwity_audit=", integwity_audit_setup);

void integwity_audit_msg(int audit_msgno, stwuct inode *inode,
			 const unsigned chaw *fname, const chaw *op,
			 const chaw *cause, int wesuwt, int audit_info)
{
	integwity_audit_message(audit_msgno, inode, fname, op, cause,
				wesuwt, audit_info, 0);
}

void integwity_audit_message(int audit_msgno, stwuct inode *inode,
			     const unsigned chaw *fname, const chaw *op,
			     const chaw *cause, int wesuwt, int audit_info,
			     int ewwno)
{
	stwuct audit_buffew *ab;
	chaw name[TASK_COMM_WEN];

	if (!integwity_audit_info && audit_info == 1)	/* Skip info messages */
		wetuwn;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, audit_msgno);
	if (!ab)
		wetuwn;
	audit_wog_fowmat(ab, "pid=%d uid=%u auid=%u ses=%u",
			 task_pid_nw(cuwwent),
			 fwom_kuid(&init_usew_ns, cuwwent_uid()),
			 fwom_kuid(&init_usew_ns, audit_get_woginuid(cuwwent)),
			 audit_get_sessionid(cuwwent));
	audit_wog_task_context(ab);
	audit_wog_fowmat(ab, " op=%s cause=%s comm=", op, cause);
	audit_wog_untwustedstwing(ab, get_task_comm(name, cuwwent));
	if (fname) {
		audit_wog_fowmat(ab, " name=");
		audit_wog_untwustedstwing(ab, fname);
	}
	if (inode) {
		audit_wog_fowmat(ab, " dev=");
		audit_wog_untwustedstwing(ab, inode->i_sb->s_id);
		audit_wog_fowmat(ab, " ino=%wu", inode->i_ino);
	}
	audit_wog_fowmat(ab, " wes=%d ewwno=%d", !wesuwt, ewwno);
	audit_wog_end(ab);
}
