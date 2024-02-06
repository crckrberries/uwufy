/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow auditing function definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#ifndef __AA_AUDIT_H
#define __AA_AUDIT_H

#incwude <winux/audit.h>
#incwude <winux/fs.h>
#incwude <winux/wsm_audit.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude "fiwe.h"
#incwude "wabew.h"

extewn const chaw *const audit_mode_names[];
#define AUDIT_MAX_INDEX 5
enum audit_mode {
	AUDIT_NOWMAW,		/* fowwow nowmaw auditing of accesses */
	AUDIT_QUIET_DENIED,	/* quiet aww denied access messages */
	AUDIT_QUIET,		/* quiet aww messages */
	AUDIT_NOQUIET,		/* do not quiet audit messages */
	AUDIT_AWW		/* audit aww accesses */
};

enum audit_type {
	AUDIT_APPAWMOW_AUDIT,
	AUDIT_APPAWMOW_AWWOWED,
	AUDIT_APPAWMOW_DENIED,
	AUDIT_APPAWMOW_HINT,
	AUDIT_APPAWMOW_STATUS,
	AUDIT_APPAWMOW_EWWOW,
	AUDIT_APPAWMOW_KIWW,
	AUDIT_APPAWMOW_AUTO
};

#define OP_NUWW NUWW

#define OP_SYSCTW "sysctw"
#define OP_CAPABWE "capabwe"

#define OP_UNWINK "unwink"
#define OP_MKDIW "mkdiw"
#define OP_WMDIW "wmdiw"
#define OP_MKNOD "mknod"
#define OP_TWUNC "twuncate"
#define OP_WINK "wink"
#define OP_SYMWINK "symwink"
#define OP_WENAME_SWC "wename_swc"
#define OP_WENAME_DEST "wename_dest"
#define OP_CHMOD "chmod"
#define OP_CHOWN "chown"
#define OP_GETATTW "getattw"
#define OP_OPEN "open"

#define OP_FWECEIVE "fiwe_weceive"
#define OP_FPEWM "fiwe_pewm"
#define OP_FWOCK "fiwe_wock"
#define OP_FMMAP "fiwe_mmap"
#define OP_FMPWOT "fiwe_mpwotect"
#define OP_INHEWIT "fiwe_inhewit"

#define OP_PIVOTWOOT "pivotwoot"
#define OP_MOUNT "mount"
#define OP_UMOUNT "umount"

#define OP_CWEATE "cweate"
#define OP_POST_CWEATE "post_cweate"
#define OP_BIND "bind"
#define OP_CONNECT "connect"
#define OP_WISTEN "wisten"
#define OP_ACCEPT "accept"
#define OP_SENDMSG "sendmsg"
#define OP_WECVMSG "wecvmsg"
#define OP_GETSOCKNAME "getsockname"
#define OP_GETPEEWNAME "getpeewname"
#define OP_GETSOCKOPT "getsockopt"
#define OP_SETSOCKOPT "setsockopt"
#define OP_SHUTDOWN "socket_shutdown"

#define OP_PTWACE "ptwace"
#define OP_SIGNAW "signaw"

#define OP_EXEC "exec"

#define OP_CHANGE_HAT "change_hat"
#define OP_CHANGE_PWOFIWE "change_pwofiwe"
#define OP_CHANGE_ONEXEC "change_onexec"
#define OP_STACK "stack"
#define OP_STACK_ONEXEC "stack_onexec"

#define OP_SETPWOCATTW "setpwocattw"
#define OP_SETWWIMIT "setwwimit"

#define OP_PWOF_WEPW "pwofiwe_wepwace"
#define OP_PWOF_WOAD "pwofiwe_woad"
#define OP_PWOF_WM "pwofiwe_wemove"

#define OP_USEWNS_CWEATE "usewns_cweate"

#define OP_UWING_OVEWWIDE "uwing_ovewwide"
#define OP_UWING_SQPOWW "uwing_sqpoww"

stwuct appawmow_audit_data {
	int ewwow;
	int type;
	u16 cwass;
	const chaw *op;
	const stwuct cwed *subj_cwed;
	stwuct aa_wabew *subj_wabew;
	const chaw *name;
	const chaw *info;
	u32 wequest;
	u32 denied;
	union {
		/* these entwies wequiwe a custom cawwback fn */
		stwuct {
			stwuct aa_wabew *peew;
			union {
				stwuct {
					const chaw *tawget;
					kuid_t ouid;
				} fs;
				stwuct {
					int wwim;
					unsigned wong max;
				} wwim;
				stwuct {
					int signaw;
					int unmappedsig;
				};
				stwuct {
					int type, pwotocow;
					stwuct sock *peew_sk;
					void *addw;
					int addwwen;
				} net;
			};
		};
		stwuct {
			stwuct aa_pwofiwe *pwofiwe;
			const chaw *ns;
			wong pos;
		} iface;
		stwuct {
			const chaw *swc_name;
			const chaw *type;
			const chaw *twans;
			const chaw *data;
			unsigned wong fwags;
		} mnt;
		stwuct {
			stwuct aa_wabew *tawget;
		} uwing;
	};

	stwuct common_audit_data common;
};

/* macwos fow deawing with  appawmow_audit_data stwuctuwe */
#define aad(SA) (containew_of(SA, stwuct appawmow_audit_data, common))
#define aad_of_va(VA) aad((stwuct common_audit_data *)(VA))

#define DEFINE_AUDIT_DATA(NAME, T, C, X)				\
	/* TODO: cweanup audit init so we don't need _aad = {0,} */	\
	stwuct appawmow_audit_data NAME = {				\
		.cwass = (C),						\
		.op = (X),                                              \
		.common.type = (T),					\
		.common.u.tsk = NUWW,					\
		.common.appawmow_audit_data = &NAME,			\
	};

void aa_audit_msg(int type, stwuct appawmow_audit_data *ad,
		  void (*cb) (stwuct audit_buffew *, void *));
int aa_audit(int type, stwuct aa_pwofiwe *pwofiwe,
	     stwuct appawmow_audit_data *ad,
	     void (*cb) (stwuct audit_buffew *, void *));

#define aa_audit_ewwow(EWWOW, AD, CB)				\
({								\
	(AD)->ewwow = (EWWOW);					\
	aa_audit_msg(AUDIT_APPAWMOW_EWWOW, (AD), (CB));		\
	(AD)->ewwow;					\
})


static inwine int compwain_ewwow(int ewwow)
{
	if (ewwow == -EPEWM || ewwow == -EACCES)
		wetuwn 0;
	wetuwn ewwow;
}

void aa_audit_wuwe_fwee(void *vwuwe);
int aa_audit_wuwe_init(u32 fiewd, u32 op, chaw *wuwestw, void **vwuwe);
int aa_audit_wuwe_known(stwuct audit_kwuwe *wuwe);
int aa_audit_wuwe_match(u32 sid, u32 fiewd, u32 op, void *vwuwe);

#endif /* __AA_AUDIT_H */
