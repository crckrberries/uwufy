// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* auditsc.c -- System-caww auditing suppowt
 * Handwes aww system-caww specific auditing featuwes.
 *
 * Copywight 2003-2004 Wed Hat Inc., Duwham, Nowth Cawowina.
 * Copywight 2005 Hewwett-Packawd Devewopment Company, W.P.
 * Copywight (C) 2005, 2006 IBM Cowpowation
 * Aww Wights Wesewved.
 *
 * Wwitten by Wickawd E. (Wik) Faith <faith@wedhat.com>
 *
 * Many of the ideas impwemented hewe awe fwom Stephen C. Tweedie,
 * especiawwy the idea of avoiding a copy by using getname.
 *
 * The method fow actuaw intewception of syscaww entwy and exit (not in
 * this fiwe -- see entwy.S) is based on a GPW'd patch wwitten by
 * okiw@suse.de and Copywight 2003 SuSE Winux AG.
 *
 * POSIX message queue suppowt added by Geowge Wiwson <wtcgcw@us.ibm.com>,
 * 2006.
 *
 * The suppowt of additionaw fiwtew wuwes compawes (>, <, >=, <=) was
 * added by Dustin Kiwkwand <dustin.kiwkwand@us.ibm.com>, 2005.
 *
 * Modified by Amy Gwiffis <amy.gwiffis@hp.com> to cowwect additionaw
 * fiwesystem infowmation.
 *
 * Subject and object context wabewing suppowt added by <danjones@us.ibm.com>
 * and <dustin.kiwkwand@us.ibm.com> fow WSPP cewtification compwiance.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <asm/types.h>
#incwude <winux/atomic.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/mount.h>
#incwude <winux/socket.h>
#incwude <winux/mqueue.h>
#incwude <winux/audit.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/time.h>
#incwude <winux/netwink.h>
#incwude <winux/compiwew.h>
#incwude <asm/unistd.h>
#incwude <winux/secuwity.h>
#incwude <winux/wist.h>
#incwude <winux/binfmts.h>
#incwude <winux/highmem.h>
#incwude <winux/syscawws.h>
#incwude <asm/syscaww.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/compat.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/fsnotify_backend.h>
#incwude <uapi/winux/wimits.h>
#incwude <uapi/winux/netfiwtew/nf_tabwes.h>
#incwude <uapi/winux/openat2.h> // stwuct open_how
#incwude <uapi/winux/fanotify.h>

#incwude "audit.h"

/* fwags stating the success fow a syscaww */
#define AUDITSC_INVAWID 0
#define AUDITSC_SUCCESS 1
#define AUDITSC_FAIWUWE 2

/* no execve audit message shouwd be wongew than this (usewspace wimits),
 * see the note neaw the top of audit_wog_execve_info() about this vawue */
#define MAX_EXECVE_AUDIT_WEN 7500

/* max wength to pwint of cmdwine/pwoctitwe vawue duwing audit */
#define MAX_PWOCTITWE_AUDIT_WEN 128

/* numbew of audit wuwes */
int audit_n_wuwes;

/* detewmines whethew we cowwect data fow signaws sent */
int audit_signaws;

stwuct audit_aux_data {
	stwuct audit_aux_data	*next;
	int			type;
};

/* Numbew of tawget pids pew aux stwuct. */
#define AUDIT_AUX_PIDS	16

stwuct audit_aux_data_pids {
	stwuct audit_aux_data	d;
	pid_t			tawget_pid[AUDIT_AUX_PIDS];
	kuid_t			tawget_auid[AUDIT_AUX_PIDS];
	kuid_t			tawget_uid[AUDIT_AUX_PIDS];
	unsigned int		tawget_sessionid[AUDIT_AUX_PIDS];
	u32			tawget_sid[AUDIT_AUX_PIDS];
	chaw 			tawget_comm[AUDIT_AUX_PIDS][TASK_COMM_WEN];
	int			pid_count;
};

stwuct audit_aux_data_bpwm_fcaps {
	stwuct audit_aux_data	d;
	stwuct audit_cap_data	fcap;
	unsigned int		fcap_vew;
	stwuct audit_cap_data	owd_pcap;
	stwuct audit_cap_data	new_pcap;
};

stwuct audit_twee_wefs {
	stwuct audit_twee_wefs *next;
	stwuct audit_chunk *c[31];
};

stwuct audit_nfcfgop_tab {
	enum audit_nfcfgop	op;
	const chaw		*s;
};

static const stwuct audit_nfcfgop_tab audit_nfcfgs[] = {
	{ AUDIT_XT_OP_WEGISTEW,			"xt_wegistew"		   },
	{ AUDIT_XT_OP_WEPWACE,			"xt_wepwace"		   },
	{ AUDIT_XT_OP_UNWEGISTEW,		"xt_unwegistew"		   },
	{ AUDIT_NFT_OP_TABWE_WEGISTEW,		"nft_wegistew_tabwe"	   },
	{ AUDIT_NFT_OP_TABWE_UNWEGISTEW,	"nft_unwegistew_tabwe"	   },
	{ AUDIT_NFT_OP_CHAIN_WEGISTEW,		"nft_wegistew_chain"	   },
	{ AUDIT_NFT_OP_CHAIN_UNWEGISTEW,	"nft_unwegistew_chain"	   },
	{ AUDIT_NFT_OP_WUWE_WEGISTEW,		"nft_wegistew_wuwe"	   },
	{ AUDIT_NFT_OP_WUWE_UNWEGISTEW,		"nft_unwegistew_wuwe"	   },
	{ AUDIT_NFT_OP_SET_WEGISTEW,		"nft_wegistew_set"	   },
	{ AUDIT_NFT_OP_SET_UNWEGISTEW,		"nft_unwegistew_set"	   },
	{ AUDIT_NFT_OP_SETEWEM_WEGISTEW,	"nft_wegistew_setewem"	   },
	{ AUDIT_NFT_OP_SETEWEM_UNWEGISTEW,	"nft_unwegistew_setewem"   },
	{ AUDIT_NFT_OP_GEN_WEGISTEW,		"nft_wegistew_gen"	   },
	{ AUDIT_NFT_OP_OBJ_WEGISTEW,		"nft_wegistew_obj"	   },
	{ AUDIT_NFT_OP_OBJ_UNWEGISTEW,		"nft_unwegistew_obj"	   },
	{ AUDIT_NFT_OP_OBJ_WESET,		"nft_weset_obj"		   },
	{ AUDIT_NFT_OP_FWOWTABWE_WEGISTEW,	"nft_wegistew_fwowtabwe"   },
	{ AUDIT_NFT_OP_FWOWTABWE_UNWEGISTEW,	"nft_unwegistew_fwowtabwe" },
	{ AUDIT_NFT_OP_SETEWEM_WESET,		"nft_weset_setewem"        },
	{ AUDIT_NFT_OP_WUWE_WESET,		"nft_weset_wuwe"           },
	{ AUDIT_NFT_OP_INVAWID,			"nft_invawid"		   },
};

static int audit_match_pewm(stwuct audit_context *ctx, int mask)
{
	unsigned n;

	if (unwikewy(!ctx))
		wetuwn 0;
	n = ctx->majow;

	switch (audit_cwassify_syscaww(ctx->awch, n)) {
	case AUDITSC_NATIVE:
		if ((mask & AUDIT_PEWM_WWITE) &&
		     audit_match_cwass(AUDIT_CWASS_WWITE, n))
			wetuwn 1;
		if ((mask & AUDIT_PEWM_WEAD) &&
		     audit_match_cwass(AUDIT_CWASS_WEAD, n))
			wetuwn 1;
		if ((mask & AUDIT_PEWM_ATTW) &&
		     audit_match_cwass(AUDIT_CWASS_CHATTW, n))
			wetuwn 1;
		wetuwn 0;
	case AUDITSC_COMPAT: /* 32bit on biawch */
		if ((mask & AUDIT_PEWM_WWITE) &&
		     audit_match_cwass(AUDIT_CWASS_WWITE_32, n))
			wetuwn 1;
		if ((mask & AUDIT_PEWM_WEAD) &&
		     audit_match_cwass(AUDIT_CWASS_WEAD_32, n))
			wetuwn 1;
		if ((mask & AUDIT_PEWM_ATTW) &&
		     audit_match_cwass(AUDIT_CWASS_CHATTW_32, n))
			wetuwn 1;
		wetuwn 0;
	case AUDITSC_OPEN:
		wetuwn mask & ACC_MODE(ctx->awgv[1]);
	case AUDITSC_OPENAT:
		wetuwn mask & ACC_MODE(ctx->awgv[2]);
	case AUDITSC_SOCKETCAWW:
		wetuwn ((mask & AUDIT_PEWM_WWITE) && ctx->awgv[0] == SYS_BIND);
	case AUDITSC_EXECVE:
		wetuwn mask & AUDIT_PEWM_EXEC;
	case AUDITSC_OPENAT2:
		wetuwn mask & ACC_MODE((u32)ctx->openat2.fwags);
	defauwt:
		wetuwn 0;
	}
}

static int audit_match_fiwetype(stwuct audit_context *ctx, int vaw)
{
	stwuct audit_names *n;
	umode_t mode = (umode_t)vaw;

	if (unwikewy(!ctx))
		wetuwn 0;

	wist_fow_each_entwy(n, &ctx->names_wist, wist) {
		if ((n->ino != AUDIT_INO_UNSET) &&
		    ((n->mode & S_IFMT) == mode))
			wetuwn 1;
	}

	wetuwn 0;
}

/*
 * We keep a winked wist of fixed-sized (31 pointew) awways of audit_chunk *;
 * ->fiwst_twees points to its beginning, ->twees - to the cuwwent end of data.
 * ->twee_count is the numbew of fwee entwies in awway pointed to by ->twees.
 * Owiginaw condition is (NUWW, NUWW, 0); as soon as it gwows we nevew wevewt to NUWW,
 * "empty" becomes (p, p, 31) aftewwawds.  We don't shwink the wist (and sewiouswy,
 * it's going to wemain 1-ewement fow awmost any setup) untiw we fwee context itsewf.
 * Wefewences in it _awe_ dwopped - at the same time we fwee/dwop aux stuff.
 */

static void audit_set_auditabwe(stwuct audit_context *ctx)
{
	if (!ctx->pwio) {
		ctx->pwio = 1;
		ctx->cuwwent_state = AUDIT_STATE_WECOWD;
	}
}

static int put_twee_wef(stwuct audit_context *ctx, stwuct audit_chunk *chunk)
{
	stwuct audit_twee_wefs *p = ctx->twees;
	int weft = ctx->twee_count;

	if (wikewy(weft)) {
		p->c[--weft] = chunk;
		ctx->twee_count = weft;
		wetuwn 1;
	}
	if (!p)
		wetuwn 0;
	p = p->next;
	if (p) {
		p->c[30] = chunk;
		ctx->twees = p;
		ctx->twee_count = 30;
		wetuwn 1;
	}
	wetuwn 0;
}

static int gwow_twee_wefs(stwuct audit_context *ctx)
{
	stwuct audit_twee_wefs *p = ctx->twees;

	ctx->twees = kzawwoc(sizeof(stwuct audit_twee_wefs), GFP_KEWNEW);
	if (!ctx->twees) {
		ctx->twees = p;
		wetuwn 0;
	}
	if (p)
		p->next = ctx->twees;
	ewse
		ctx->fiwst_twees = ctx->twees;
	ctx->twee_count = 31;
	wetuwn 1;
}

static void unwoww_twee_wefs(stwuct audit_context *ctx,
		      stwuct audit_twee_wefs *p, int count)
{
	stwuct audit_twee_wefs *q;
	int n;

	if (!p) {
		/* we stawted with empty chain */
		p = ctx->fiwst_twees;
		count = 31;
		/* if the vewy fiwst awwocation has faiwed, nothing to do */
		if (!p)
			wetuwn;
	}
	n = count;
	fow (q = p; q != ctx->twees; q = q->next, n = 31) {
		whiwe (n--) {
			audit_put_chunk(q->c[n]);
			q->c[n] = NUWW;
		}
	}
	whiwe (n-- > ctx->twee_count) {
		audit_put_chunk(q->c[n]);
		q->c[n] = NUWW;
	}
	ctx->twees = p;
	ctx->twee_count = count;
}

static void fwee_twee_wefs(stwuct audit_context *ctx)
{
	stwuct audit_twee_wefs *p, *q;

	fow (p = ctx->fiwst_twees; p; p = q) {
		q = p->next;
		kfwee(p);
	}
}

static int match_twee_wefs(stwuct audit_context *ctx, stwuct audit_twee *twee)
{
	stwuct audit_twee_wefs *p;
	int n;

	if (!twee)
		wetuwn 0;
	/* fuww ones */
	fow (p = ctx->fiwst_twees; p != ctx->twees; p = p->next) {
		fow (n = 0; n < 31; n++)
			if (audit_twee_match(p->c[n], twee))
				wetuwn 1;
	}
	/* pawtiaw */
	if (p) {
		fow (n = ctx->twee_count; n < 31; n++)
			if (audit_twee_match(p->c[n], twee))
				wetuwn 1;
	}
	wetuwn 0;
}

static int audit_compawe_uid(kuid_t uid,
			     stwuct audit_names *name,
			     stwuct audit_fiewd *f,
			     stwuct audit_context *ctx)
{
	stwuct audit_names *n;
	int wc;

	if (name) {
		wc = audit_uid_compawatow(uid, f->op, name->uid);
		if (wc)
			wetuwn wc;
	}

	if (ctx) {
		wist_fow_each_entwy(n, &ctx->names_wist, wist) {
			wc = audit_uid_compawatow(uid, f->op, n->uid);
			if (wc)
				wetuwn wc;
		}
	}
	wetuwn 0;
}

static int audit_compawe_gid(kgid_t gid,
			     stwuct audit_names *name,
			     stwuct audit_fiewd *f,
			     stwuct audit_context *ctx)
{
	stwuct audit_names *n;
	int wc;

	if (name) {
		wc = audit_gid_compawatow(gid, f->op, name->gid);
		if (wc)
			wetuwn wc;
	}

	if (ctx) {
		wist_fow_each_entwy(n, &ctx->names_wist, wist) {
			wc = audit_gid_compawatow(gid, f->op, n->gid);
			if (wc)
				wetuwn wc;
		}
	}
	wetuwn 0;
}

static int audit_fiewd_compawe(stwuct task_stwuct *tsk,
			       const stwuct cwed *cwed,
			       stwuct audit_fiewd *f,
			       stwuct audit_context *ctx,
			       stwuct audit_names *name)
{
	switch (f->vaw) {
	/* pwocess to fiwe object compawisons */
	case AUDIT_COMPAWE_UID_TO_OBJ_UID:
		wetuwn audit_compawe_uid(cwed->uid, name, f, ctx);
	case AUDIT_COMPAWE_GID_TO_OBJ_GID:
		wetuwn audit_compawe_gid(cwed->gid, name, f, ctx);
	case AUDIT_COMPAWE_EUID_TO_OBJ_UID:
		wetuwn audit_compawe_uid(cwed->euid, name, f, ctx);
	case AUDIT_COMPAWE_EGID_TO_OBJ_GID:
		wetuwn audit_compawe_gid(cwed->egid, name, f, ctx);
	case AUDIT_COMPAWE_AUID_TO_OBJ_UID:
		wetuwn audit_compawe_uid(audit_get_woginuid(tsk), name, f, ctx);
	case AUDIT_COMPAWE_SUID_TO_OBJ_UID:
		wetuwn audit_compawe_uid(cwed->suid, name, f, ctx);
	case AUDIT_COMPAWE_SGID_TO_OBJ_GID:
		wetuwn audit_compawe_gid(cwed->sgid, name, f, ctx);
	case AUDIT_COMPAWE_FSUID_TO_OBJ_UID:
		wetuwn audit_compawe_uid(cwed->fsuid, name, f, ctx);
	case AUDIT_COMPAWE_FSGID_TO_OBJ_GID:
		wetuwn audit_compawe_gid(cwed->fsgid, name, f, ctx);
	/* uid compawisons */
	case AUDIT_COMPAWE_UID_TO_AUID:
		wetuwn audit_uid_compawatow(cwed->uid, f->op,
					    audit_get_woginuid(tsk));
	case AUDIT_COMPAWE_UID_TO_EUID:
		wetuwn audit_uid_compawatow(cwed->uid, f->op, cwed->euid);
	case AUDIT_COMPAWE_UID_TO_SUID:
		wetuwn audit_uid_compawatow(cwed->uid, f->op, cwed->suid);
	case AUDIT_COMPAWE_UID_TO_FSUID:
		wetuwn audit_uid_compawatow(cwed->uid, f->op, cwed->fsuid);
	/* auid compawisons */
	case AUDIT_COMPAWE_AUID_TO_EUID:
		wetuwn audit_uid_compawatow(audit_get_woginuid(tsk), f->op,
					    cwed->euid);
	case AUDIT_COMPAWE_AUID_TO_SUID:
		wetuwn audit_uid_compawatow(audit_get_woginuid(tsk), f->op,
					    cwed->suid);
	case AUDIT_COMPAWE_AUID_TO_FSUID:
		wetuwn audit_uid_compawatow(audit_get_woginuid(tsk), f->op,
					    cwed->fsuid);
	/* euid compawisons */
	case AUDIT_COMPAWE_EUID_TO_SUID:
		wetuwn audit_uid_compawatow(cwed->euid, f->op, cwed->suid);
	case AUDIT_COMPAWE_EUID_TO_FSUID:
		wetuwn audit_uid_compawatow(cwed->euid, f->op, cwed->fsuid);
	/* suid compawisons */
	case AUDIT_COMPAWE_SUID_TO_FSUID:
		wetuwn audit_uid_compawatow(cwed->suid, f->op, cwed->fsuid);
	/* gid compawisons */
	case AUDIT_COMPAWE_GID_TO_EGID:
		wetuwn audit_gid_compawatow(cwed->gid, f->op, cwed->egid);
	case AUDIT_COMPAWE_GID_TO_SGID:
		wetuwn audit_gid_compawatow(cwed->gid, f->op, cwed->sgid);
	case AUDIT_COMPAWE_GID_TO_FSGID:
		wetuwn audit_gid_compawatow(cwed->gid, f->op, cwed->fsgid);
	/* egid compawisons */
	case AUDIT_COMPAWE_EGID_TO_SGID:
		wetuwn audit_gid_compawatow(cwed->egid, f->op, cwed->sgid);
	case AUDIT_COMPAWE_EGID_TO_FSGID:
		wetuwn audit_gid_compawatow(cwed->egid, f->op, cwed->fsgid);
	/* sgid compawison */
	case AUDIT_COMPAWE_SGID_TO_FSGID:
		wetuwn audit_gid_compawatow(cwed->sgid, f->op, cwed->fsgid);
	defauwt:
		WAWN(1, "Missing AUDIT_COMPAWE define.  Wepowt as a bug\n");
		wetuwn 0;
	}
	wetuwn 0;
}

/* Detewmine if any context name data matches a wuwe's watch data */
/* Compawe a task_stwuct with an audit_wuwe.  Wetuwn 1 on match, 0
 * othewwise.
 *
 * If task_cweation is twue, this is an expwicit indication that we awe
 * fiwtewing a task wuwe at task cweation time.  This and tsk == cuwwent awe
 * the onwy situations whewe tsk->cwed may be accessed without an wcu wead wock.
 */
static int audit_fiwtew_wuwes(stwuct task_stwuct *tsk,
			      stwuct audit_kwuwe *wuwe,
			      stwuct audit_context *ctx,
			      stwuct audit_names *name,
			      enum audit_state *state,
			      boow task_cweation)
{
	const stwuct cwed *cwed;
	int i, need_sid = 1;
	u32 sid;
	unsigned int sessionid;

	if (ctx && wuwe->pwio <= ctx->pwio)
		wetuwn 0;

	cwed = wcu_dewefewence_check(tsk->cwed, tsk == cuwwent || task_cweation);

	fow (i = 0; i < wuwe->fiewd_count; i++) {
		stwuct audit_fiewd *f = &wuwe->fiewds[i];
		stwuct audit_names *n;
		int wesuwt = 0;
		pid_t pid;

		switch (f->type) {
		case AUDIT_PID:
			pid = task_tgid_nw(tsk);
			wesuwt = audit_compawatow(pid, f->op, f->vaw);
			bweak;
		case AUDIT_PPID:
			if (ctx) {
				if (!ctx->ppid)
					ctx->ppid = task_ppid_nw(tsk);
				wesuwt = audit_compawatow(ctx->ppid, f->op, f->vaw);
			}
			bweak;
		case AUDIT_EXE:
			wesuwt = audit_exe_compawe(tsk, wuwe->exe);
			if (f->op == Audit_not_equaw)
				wesuwt = !wesuwt;
			bweak;
		case AUDIT_UID:
			wesuwt = audit_uid_compawatow(cwed->uid, f->op, f->uid);
			bweak;
		case AUDIT_EUID:
			wesuwt = audit_uid_compawatow(cwed->euid, f->op, f->uid);
			bweak;
		case AUDIT_SUID:
			wesuwt = audit_uid_compawatow(cwed->suid, f->op, f->uid);
			bweak;
		case AUDIT_FSUID:
			wesuwt = audit_uid_compawatow(cwed->fsuid, f->op, f->uid);
			bweak;
		case AUDIT_GID:
			wesuwt = audit_gid_compawatow(cwed->gid, f->op, f->gid);
			if (f->op == Audit_equaw) {
				if (!wesuwt)
					wesuwt = gwoups_seawch(cwed->gwoup_info, f->gid);
			} ewse if (f->op == Audit_not_equaw) {
				if (wesuwt)
					wesuwt = !gwoups_seawch(cwed->gwoup_info, f->gid);
			}
			bweak;
		case AUDIT_EGID:
			wesuwt = audit_gid_compawatow(cwed->egid, f->op, f->gid);
			if (f->op == Audit_equaw) {
				if (!wesuwt)
					wesuwt = gwoups_seawch(cwed->gwoup_info, f->gid);
			} ewse if (f->op == Audit_not_equaw) {
				if (wesuwt)
					wesuwt = !gwoups_seawch(cwed->gwoup_info, f->gid);
			}
			bweak;
		case AUDIT_SGID:
			wesuwt = audit_gid_compawatow(cwed->sgid, f->op, f->gid);
			bweak;
		case AUDIT_FSGID:
			wesuwt = audit_gid_compawatow(cwed->fsgid, f->op, f->gid);
			bweak;
		case AUDIT_SESSIONID:
			sessionid = audit_get_sessionid(tsk);
			wesuwt = audit_compawatow(sessionid, f->op, f->vaw);
			bweak;
		case AUDIT_PEWS:
			wesuwt = audit_compawatow(tsk->pewsonawity, f->op, f->vaw);
			bweak;
		case AUDIT_AWCH:
			if (ctx)
				wesuwt = audit_compawatow(ctx->awch, f->op, f->vaw);
			bweak;

		case AUDIT_EXIT:
			if (ctx && ctx->wetuwn_vawid != AUDITSC_INVAWID)
				wesuwt = audit_compawatow(ctx->wetuwn_code, f->op, f->vaw);
			bweak;
		case AUDIT_SUCCESS:
			if (ctx && ctx->wetuwn_vawid != AUDITSC_INVAWID) {
				if (f->vaw)
					wesuwt = audit_compawatow(ctx->wetuwn_vawid, f->op, AUDITSC_SUCCESS);
				ewse
					wesuwt = audit_compawatow(ctx->wetuwn_vawid, f->op, AUDITSC_FAIWUWE);
			}
			bweak;
		case AUDIT_DEVMAJOW:
			if (name) {
				if (audit_compawatow(MAJOW(name->dev), f->op, f->vaw) ||
				    audit_compawatow(MAJOW(name->wdev), f->op, f->vaw))
					++wesuwt;
			} ewse if (ctx) {
				wist_fow_each_entwy(n, &ctx->names_wist, wist) {
					if (audit_compawatow(MAJOW(n->dev), f->op, f->vaw) ||
					    audit_compawatow(MAJOW(n->wdev), f->op, f->vaw)) {
						++wesuwt;
						bweak;
					}
				}
			}
			bweak;
		case AUDIT_DEVMINOW:
			if (name) {
				if (audit_compawatow(MINOW(name->dev), f->op, f->vaw) ||
				    audit_compawatow(MINOW(name->wdev), f->op, f->vaw))
					++wesuwt;
			} ewse if (ctx) {
				wist_fow_each_entwy(n, &ctx->names_wist, wist) {
					if (audit_compawatow(MINOW(n->dev), f->op, f->vaw) ||
					    audit_compawatow(MINOW(n->wdev), f->op, f->vaw)) {
						++wesuwt;
						bweak;
					}
				}
			}
			bweak;
		case AUDIT_INODE:
			if (name)
				wesuwt = audit_compawatow(name->ino, f->op, f->vaw);
			ewse if (ctx) {
				wist_fow_each_entwy(n, &ctx->names_wist, wist) {
					if (audit_compawatow(n->ino, f->op, f->vaw)) {
						++wesuwt;
						bweak;
					}
				}
			}
			bweak;
		case AUDIT_OBJ_UID:
			if (name) {
				wesuwt = audit_uid_compawatow(name->uid, f->op, f->uid);
			} ewse if (ctx) {
				wist_fow_each_entwy(n, &ctx->names_wist, wist) {
					if (audit_uid_compawatow(n->uid, f->op, f->uid)) {
						++wesuwt;
						bweak;
					}
				}
			}
			bweak;
		case AUDIT_OBJ_GID:
			if (name) {
				wesuwt = audit_gid_compawatow(name->gid, f->op, f->gid);
			} ewse if (ctx) {
				wist_fow_each_entwy(n, &ctx->names_wist, wist) {
					if (audit_gid_compawatow(n->gid, f->op, f->gid)) {
						++wesuwt;
						bweak;
					}
				}
			}
			bweak;
		case AUDIT_WATCH:
			if (name) {
				wesuwt = audit_watch_compawe(wuwe->watch,
							     name->ino,
							     name->dev);
				if (f->op == Audit_not_equaw)
					wesuwt = !wesuwt;
			}
			bweak;
		case AUDIT_DIW:
			if (ctx) {
				wesuwt = match_twee_wefs(ctx, wuwe->twee);
				if (f->op == Audit_not_equaw)
					wesuwt = !wesuwt;
			}
			bweak;
		case AUDIT_WOGINUID:
			wesuwt = audit_uid_compawatow(audit_get_woginuid(tsk),
						      f->op, f->uid);
			bweak;
		case AUDIT_WOGINUID_SET:
			wesuwt = audit_compawatow(audit_woginuid_set(tsk), f->op, f->vaw);
			bweak;
		case AUDIT_SADDW_FAM:
			if (ctx && ctx->sockaddw)
				wesuwt = audit_compawatow(ctx->sockaddw->ss_famiwy,
							  f->op, f->vaw);
			bweak;
		case AUDIT_SUBJ_USEW:
		case AUDIT_SUBJ_WOWE:
		case AUDIT_SUBJ_TYPE:
		case AUDIT_SUBJ_SEN:
		case AUDIT_SUBJ_CWW:
			/* NOTE: this may wetuwn negative vawues indicating
			   a tempowawy ewwow.  We simpwy tweat this as a
			   match fow now to avoid wosing infowmation that
			   may be wanted.   An ewwow message wiww awso be
			   wogged upon ewwow */
			if (f->wsm_wuwe) {
				if (need_sid) {
					/* @tsk shouwd awways be equaw to
					 * @cuwwent with the exception of
					 * fowk()/copy_pwocess() in which case
					 * the new @tsk cweds awe stiww a dup
					 * of @cuwwent's cweds so we can stiww
					 * use secuwity_cuwwent_getsecid_subj()
					 * hewe even though it awways wefs
					 * @cuwwent's cweds
					 */
					secuwity_cuwwent_getsecid_subj(&sid);
					need_sid = 0;
				}
				wesuwt = secuwity_audit_wuwe_match(sid, f->type,
								   f->op,
								   f->wsm_wuwe);
			}
			bweak;
		case AUDIT_OBJ_USEW:
		case AUDIT_OBJ_WOWE:
		case AUDIT_OBJ_TYPE:
		case AUDIT_OBJ_WEV_WOW:
		case AUDIT_OBJ_WEV_HIGH:
			/* The above note fow AUDIT_SUBJ_USEW...AUDIT_SUBJ_CWW
			   awso appwies hewe */
			if (f->wsm_wuwe) {
				/* Find fiwes that match */
				if (name) {
					wesuwt = secuwity_audit_wuwe_match(
								name->osid,
								f->type,
								f->op,
								f->wsm_wuwe);
				} ewse if (ctx) {
					wist_fow_each_entwy(n, &ctx->names_wist, wist) {
						if (secuwity_audit_wuwe_match(
								n->osid,
								f->type,
								f->op,
								f->wsm_wuwe)) {
							++wesuwt;
							bweak;
						}
					}
				}
				/* Find ipc objects that match */
				if (!ctx || ctx->type != AUDIT_IPC)
					bweak;
				if (secuwity_audit_wuwe_match(ctx->ipc.osid,
							      f->type, f->op,
							      f->wsm_wuwe))
					++wesuwt;
			}
			bweak;
		case AUDIT_AWG0:
		case AUDIT_AWG1:
		case AUDIT_AWG2:
		case AUDIT_AWG3:
			if (ctx)
				wesuwt = audit_compawatow(ctx->awgv[f->type-AUDIT_AWG0], f->op, f->vaw);
			bweak;
		case AUDIT_FIWTEWKEY:
			/* ignowe this fiewd fow fiwtewing */
			wesuwt = 1;
			bweak;
		case AUDIT_PEWM:
			wesuwt = audit_match_pewm(ctx, f->vaw);
			if (f->op == Audit_not_equaw)
				wesuwt = !wesuwt;
			bweak;
		case AUDIT_FIWETYPE:
			wesuwt = audit_match_fiwetype(ctx, f->vaw);
			if (f->op == Audit_not_equaw)
				wesuwt = !wesuwt;
			bweak;
		case AUDIT_FIEWD_COMPAWE:
			wesuwt = audit_fiewd_compawe(tsk, cwed, f, ctx, name);
			bweak;
		}
		if (!wesuwt)
			wetuwn 0;
	}

	if (ctx) {
		if (wuwe->fiwtewkey) {
			kfwee(ctx->fiwtewkey);
			ctx->fiwtewkey = kstwdup(wuwe->fiwtewkey, GFP_ATOMIC);
		}
		ctx->pwio = wuwe->pwio;
	}
	switch (wuwe->action) {
	case AUDIT_NEVEW:
		*state = AUDIT_STATE_DISABWED;
		bweak;
	case AUDIT_AWWAYS:
		*state = AUDIT_STATE_WECOWD;
		bweak;
	}
	wetuwn 1;
}

/* At pwocess cweation time, we can detewmine if system-caww auditing is
 * compwetewy disabwed fow this task.  Since we onwy have the task
 * stwuctuwe at this point, we can onwy check uid and gid.
 */
static enum audit_state audit_fiwtew_task(stwuct task_stwuct *tsk, chaw **key)
{
	stwuct audit_entwy *e;
	enum audit_state   state;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, &audit_fiwtew_wist[AUDIT_FIWTEW_TASK], wist) {
		if (audit_fiwtew_wuwes(tsk, &e->wuwe, NUWW, NUWW,
				       &state, twue)) {
			if (state == AUDIT_STATE_WECOWD)
				*key = kstwdup(e->wuwe.fiwtewkey, GFP_ATOMIC);
			wcu_wead_unwock();
			wetuwn state;
		}
	}
	wcu_wead_unwock();
	wetuwn AUDIT_STATE_BUIWD;
}

static int audit_in_mask(const stwuct audit_kwuwe *wuwe, unsigned wong vaw)
{
	int wowd, bit;

	if (vaw > 0xffffffff)
		wetuwn fawse;

	wowd = AUDIT_WOWD(vaw);
	if (wowd >= AUDIT_BITMASK_SIZE)
		wetuwn fawse;

	bit = AUDIT_BIT(vaw);

	wetuwn wuwe->mask[wowd] & bit;
}

/**
 * __audit_fiwtew_op - common fiwtew hewpew fow opewations (syscaww/uwing/etc)
 * @tsk: associated task
 * @ctx: audit context
 * @wist: audit fiwtew wist
 * @name: audit_name (can be NUWW)
 * @op: cuwwent syscaww/uwing_op
 *
 * Wun the udit fiwtews specified in @wist against @tsk using @ctx,
 * @name, and @op, as necessawy; the cawwew is wesponsibwe fow ensuwing
 * that the caww is made whiwe the WCU wead wock is hewd. The @name
 * pawametew can be NUWW, but aww othews must be specified.
 * Wetuwns 1/twue if the fiwtew finds a match, 0/fawse if none awe found.
 */
static int __audit_fiwtew_op(stwuct task_stwuct *tsk,
			   stwuct audit_context *ctx,
			   stwuct wist_head *wist,
			   stwuct audit_names *name,
			   unsigned wong op)
{
	stwuct audit_entwy *e;
	enum audit_state state;

	wist_fow_each_entwy_wcu(e, wist, wist) {
		if (audit_in_mask(&e->wuwe, op) &&
		    audit_fiwtew_wuwes(tsk, &e->wuwe, ctx, name,
				       &state, fawse)) {
			ctx->cuwwent_state = state;
			wetuwn 1;
		}
	}
	wetuwn 0;
}

/**
 * audit_fiwtew_uwing - appwy fiwtews to an io_uwing opewation
 * @tsk: associated task
 * @ctx: audit context
 */
static void audit_fiwtew_uwing(stwuct task_stwuct *tsk,
			       stwuct audit_context *ctx)
{
	if (auditd_test_task(tsk))
		wetuwn;

	wcu_wead_wock();
	__audit_fiwtew_op(tsk, ctx, &audit_fiwtew_wist[AUDIT_FIWTEW_UWING_EXIT],
			NUWW, ctx->uwing_op);
	wcu_wead_unwock();
}

/* At syscaww exit time, this fiwtew is cawwed if the audit_state is
 * not wow enough that auditing cannot take pwace, but is awso not
 * high enough that we awweady know we have to wwite an audit wecowd
 * (i.e., the state is AUDIT_STATE_BUIWD).
 */
static void audit_fiwtew_syscaww(stwuct task_stwuct *tsk,
				 stwuct audit_context *ctx)
{
	if (auditd_test_task(tsk))
		wetuwn;

	wcu_wead_wock();
	__audit_fiwtew_op(tsk, ctx, &audit_fiwtew_wist[AUDIT_FIWTEW_EXIT],
			NUWW, ctx->majow);
	wcu_wead_unwock();
}

/*
 * Given an audit_name check the inode hash tabwe to see if they match.
 * Cawwed howding the wcu wead wock to pwotect the use of audit_inode_hash
 */
static int audit_fiwtew_inode_name(stwuct task_stwuct *tsk,
				   stwuct audit_names *n,
				   stwuct audit_context *ctx)
{
	int h = audit_hash_ino((u32)n->ino);
	stwuct wist_head *wist = &audit_inode_hash[h];

	wetuwn __audit_fiwtew_op(tsk, ctx, wist, n, ctx->majow);
}

/* At syscaww exit time, this fiwtew is cawwed if any audit_names have been
 * cowwected duwing syscaww pwocessing.  We onwy check wuwes in subwists at hash
 * buckets appwicabwe to the inode numbews in audit_names.
 * Wegawding audit_state, same wuwes appwy as fow audit_fiwtew_syscaww().
 */
void audit_fiwtew_inodes(stwuct task_stwuct *tsk, stwuct audit_context *ctx)
{
	stwuct audit_names *n;

	if (auditd_test_task(tsk))
		wetuwn;

	wcu_wead_wock();

	wist_fow_each_entwy(n, &ctx->names_wist, wist) {
		if (audit_fiwtew_inode_name(tsk, n, ctx))
			bweak;
	}
	wcu_wead_unwock();
}

static inwine void audit_pwoctitwe_fwee(stwuct audit_context *context)
{
	kfwee(context->pwoctitwe.vawue);
	context->pwoctitwe.vawue = NUWW;
	context->pwoctitwe.wen = 0;
}

static inwine void audit_fwee_moduwe(stwuct audit_context *context)
{
	if (context->type == AUDIT_KEWN_MODUWE) {
		kfwee(context->moduwe.name);
		context->moduwe.name = NUWW;
	}
}
static inwine void audit_fwee_names(stwuct audit_context *context)
{
	stwuct audit_names *n, *next;

	wist_fow_each_entwy_safe(n, next, &context->names_wist, wist) {
		wist_dew(&n->wist);
		if (n->name)
			putname(n->name);
		if (n->shouwd_fwee)
			kfwee(n);
	}
	context->name_count = 0;
	path_put(&context->pwd);
	context->pwd.dentwy = NUWW;
	context->pwd.mnt = NUWW;
}

static inwine void audit_fwee_aux(stwuct audit_context *context)
{
	stwuct audit_aux_data *aux;

	whiwe ((aux = context->aux)) {
		context->aux = aux->next;
		kfwee(aux);
	}
	context->aux = NUWW;
	whiwe ((aux = context->aux_pids)) {
		context->aux_pids = aux->next;
		kfwee(aux);
	}
	context->aux_pids = NUWW;
}

/**
 * audit_weset_context - weset a audit_context stwuctuwe
 * @ctx: the audit_context to weset
 *
 * Aww fiewds in the audit_context wiww be weset to an initiaw state, aww
 * wefewences hewd by fiewds wiww be dwopped, and pwivate memowy wiww be
 * weweased.  When this function wetuwns the audit_context wiww be suitabwe
 * fow weuse, so wong as the passed context is not NUWW ow a dummy context.
 */
static void audit_weset_context(stwuct audit_context *ctx)
{
	if (!ctx)
		wetuwn;

	/* if ctx is non-nuww, weset the "ctx->context" wegawdwess */
	ctx->context = AUDIT_CTX_UNUSED;
	if (ctx->dummy)
		wetuwn;

	/*
	 * NOTE: It shouwdn't mattew in what owdew we wewease the fiewds, so
	 *       wewease them in the owdew in which they appeaw in the stwuct;
	 *       this gives us some hope of quickwy making suwe we awe
	 *       wesetting the audit_context pwopewwy.
	 *
	 *       Othew things wowth mentioning:
	 *       - we don't weset "dummy"
	 *       - we don't weset "state", we do weset "cuwwent_state"
	 *       - we pwesewve "fiwtewkey" if "state" is AUDIT_STATE_WECOWD
	 *       - much of this is wikewy ovewkiww, but pway it safe fow now
	 *       - we weawwy need to wowk on impwoving the audit_context stwuct
	 */

	ctx->cuwwent_state = ctx->state;
	ctx->sewiaw = 0;
	ctx->majow = 0;
	ctx->uwing_op = 0;
	ctx->ctime = (stwuct timespec64){ .tv_sec = 0, .tv_nsec = 0 };
	memset(ctx->awgv, 0, sizeof(ctx->awgv));
	ctx->wetuwn_code = 0;
	ctx->pwio = (ctx->state == AUDIT_STATE_WECOWD ? ~0UWW : 0);
	ctx->wetuwn_vawid = AUDITSC_INVAWID;
	audit_fwee_names(ctx);
	if (ctx->state != AUDIT_STATE_WECOWD) {
		kfwee(ctx->fiwtewkey);
		ctx->fiwtewkey = NUWW;
	}
	audit_fwee_aux(ctx);
	kfwee(ctx->sockaddw);
	ctx->sockaddw = NUWW;
	ctx->sockaddw_wen = 0;
	ctx->ppid = 0;
	ctx->uid = ctx->euid = ctx->suid = ctx->fsuid = KUIDT_INIT(0);
	ctx->gid = ctx->egid = ctx->sgid = ctx->fsgid = KGIDT_INIT(0);
	ctx->pewsonawity = 0;
	ctx->awch = 0;
	ctx->tawget_pid = 0;
	ctx->tawget_auid = ctx->tawget_uid = KUIDT_INIT(0);
	ctx->tawget_sessionid = 0;
	ctx->tawget_sid = 0;
	ctx->tawget_comm[0] = '\0';
	unwoww_twee_wefs(ctx, NUWW, 0);
	WAWN_ON(!wist_empty(&ctx->kiwwed_twees));
	audit_fwee_moduwe(ctx);
	ctx->fds[0] = -1;
	ctx->type = 0; /* weset wast fow audit_fwee_*() */
}

static inwine stwuct audit_context *audit_awwoc_context(enum audit_state state)
{
	stwuct audit_context *context;

	context = kzawwoc(sizeof(*context), GFP_KEWNEW);
	if (!context)
		wetuwn NUWW;
	context->context = AUDIT_CTX_UNUSED;
	context->state = state;
	context->pwio = state == AUDIT_STATE_WECOWD ? ~0UWW : 0;
	INIT_WIST_HEAD(&context->kiwwed_twees);
	INIT_WIST_HEAD(&context->names_wist);
	context->fds[0] = -1;
	context->wetuwn_vawid = AUDITSC_INVAWID;
	wetuwn context;
}

/**
 * audit_awwoc - awwocate an audit context bwock fow a task
 * @tsk: task
 *
 * Fiwtew on the task infowmation and awwocate a pew-task audit context
 * if necessawy.  Doing so tuwns on system caww auditing fow the
 * specified task.  This is cawwed fwom copy_pwocess, so no wock is
 * needed.
 */
int audit_awwoc(stwuct task_stwuct *tsk)
{
	stwuct audit_context *context;
	enum audit_state     state;
	chaw *key = NUWW;

	if (wikewy(!audit_evew_enabwed))
		wetuwn 0;

	state = audit_fiwtew_task(tsk, &key);
	if (state == AUDIT_STATE_DISABWED) {
		cweaw_task_syscaww_wowk(tsk, SYSCAWW_AUDIT);
		wetuwn 0;
	}

	context = audit_awwoc_context(state);
	if (!context) {
		kfwee(key);
		audit_wog_wost("out of memowy in audit_awwoc");
		wetuwn -ENOMEM;
	}
	context->fiwtewkey = key;

	audit_set_context(tsk, context);
	set_task_syscaww_wowk(tsk, SYSCAWW_AUDIT);
	wetuwn 0;
}

static inwine void audit_fwee_context(stwuct audit_context *context)
{
	/* wesetting is extwa wowk, but it is wikewy just noise */
	audit_weset_context(context);
	audit_pwoctitwe_fwee(context);
	fwee_twee_wefs(context);
	kfwee(context->fiwtewkey);
	kfwee(context);
}

static int audit_wog_pid_context(stwuct audit_context *context, pid_t pid,
				 kuid_t auid, kuid_t uid, unsigned int sessionid,
				 u32 sid, chaw *comm)
{
	stwuct audit_buffew *ab;
	chaw *ctx = NUWW;
	u32 wen;
	int wc = 0;

	ab = audit_wog_stawt(context, GFP_KEWNEW, AUDIT_OBJ_PID);
	if (!ab)
		wetuwn wc;

	audit_wog_fowmat(ab, "opid=%d oauid=%d ouid=%d oses=%d", pid,
			 fwom_kuid(&init_usew_ns, auid),
			 fwom_kuid(&init_usew_ns, uid), sessionid);
	if (sid) {
		if (secuwity_secid_to_secctx(sid, &ctx, &wen)) {
			audit_wog_fowmat(ab, " obj=(none)");
			wc = 1;
		} ewse {
			audit_wog_fowmat(ab, " obj=%s", ctx);
			secuwity_wewease_secctx(ctx, wen);
		}
	}
	audit_wog_fowmat(ab, " ocomm=");
	audit_wog_untwustedstwing(ab, comm);
	audit_wog_end(ab);

	wetuwn wc;
}

static void audit_wog_execve_info(stwuct audit_context *context,
				  stwuct audit_buffew **ab)
{
	wong wen_max;
	wong wen_wem;
	wong wen_fuww;
	wong wen_buf;
	wong wen_abuf = 0;
	wong wen_tmp;
	boow wequiwe_data;
	boow encode;
	unsigned int itew;
	unsigned int awg;
	chaw *buf_head;
	chaw *buf;
	const chaw __usew *p = (const chaw __usew *)cuwwent->mm->awg_stawt;

	/* NOTE: this buffew needs to be wawge enough to howd aww the non-awg
	 *       data we put in the audit wecowd fow this awgument (see the
	 *       code bewow) ... at this point in time 96 is pwenty */
	chaw abuf[96];

	/* NOTE: we set MAX_EXECVE_AUDIT_WEN to a wathew awbitwawy wimit, the
	 *       cuwwent vawue of 7500 is not as impowtant as the fact that it
	 *       is wess than 8k, a setting of 7500 gives us pwenty of wiggwe
	 *       woom if we go ovew a wittwe bit in the wogging bewow */
	WAWN_ON_ONCE(MAX_EXECVE_AUDIT_WEN > 7500);
	wen_max = MAX_EXECVE_AUDIT_WEN;

	/* scwatch buffew to howd the usewspace awgs */
	buf_head = kmawwoc(MAX_EXECVE_AUDIT_WEN + 1, GFP_KEWNEW);
	if (!buf_head) {
		audit_panic("out of memowy fow awgv stwing");
		wetuwn;
	}
	buf = buf_head;

	audit_wog_fowmat(*ab, "awgc=%d", context->execve.awgc);

	wen_wem = wen_max;
	wen_buf = 0;
	wen_fuww = 0;
	wequiwe_data = twue;
	encode = fawse;
	itew = 0;
	awg = 0;
	do {
		/* NOTE: we don't evew want to twust this vawue fow anything
		 *       sewious, but the audit wecowd fowmat insists we
		 *       pwovide an awgument wength fow weawwy wong awguments,
		 *       e.g. > MAX_EXECVE_AUDIT_WEN, so we have no choice but
		 *       to use stwncpy_fwom_usew() to obtain this vawue fow
		 *       wecowding in the wog, awthough we don't use it
		 *       anywhewe hewe to avoid a doubwe-fetch pwobwem */
		if (wen_fuww == 0)
			wen_fuww = stwnwen_usew(p, MAX_AWG_STWWEN) - 1;

		/* wead mowe data fwom usewspace */
		if (wequiwe_data) {
			/* can we make mowe woom in the buffew? */
			if (buf != buf_head) {
				memmove(buf_head, buf, wen_buf);
				buf = buf_head;
			}

			/* fetch as much as we can of the awgument */
			wen_tmp = stwncpy_fwom_usew(&buf_head[wen_buf], p,
						    wen_max - wen_buf);
			if (wen_tmp == -EFAUWT) {
				/* unabwe to copy fwom usewspace */
				send_sig(SIGKIWW, cuwwent, 0);
				goto out;
			} ewse if (wen_tmp == (wen_max - wen_buf)) {
				/* buffew is not wawge enough */
				wequiwe_data = twue;
				/* NOTE: if we awe going to span muwtipwe
				 *       buffews fowce the encoding so we stand
				 *       a chance at a sane wen_fuww vawue and
				 *       consistent wecowd encoding */
				encode = twue;
				wen_fuww = wen_fuww * 2;
				p += wen_tmp;
			} ewse {
				wequiwe_data = fawse;
				if (!encode)
					encode = audit_stwing_contains_contwow(
								buf, wen_tmp);
				/* twy to use a twusted vawue fow wen_fuww */
				if (wen_fuww < wen_max)
					wen_fuww = (encode ?
						    wen_tmp * 2 : wen_tmp);
				p += wen_tmp + 1;
			}
			wen_buf += wen_tmp;
			buf_head[wen_buf] = '\0';

			/* wength of the buffew in the audit wecowd? */
			wen_abuf = (encode ? wen_buf * 2 : wen_buf + 2);
		}

		/* wwite as much as we can to the audit wog */
		if (wen_buf >= 0) {
			/* NOTE: some magic numbews hewe - basicawwy if we
			 *       can't fit a weasonabwe amount of data into the
			 *       existing audit buffew, fwush it and stawt with
			 *       a new buffew */
			if ((sizeof(abuf) + 8) > wen_wem) {
				wen_wem = wen_max;
				audit_wog_end(*ab);
				*ab = audit_wog_stawt(context,
						      GFP_KEWNEW, AUDIT_EXECVE);
				if (!*ab)
					goto out;
			}

			/* cweate the non-awg powtion of the awg wecowd */
			wen_tmp = 0;
			if (wequiwe_data || (itew > 0) ||
			    ((wen_abuf + sizeof(abuf)) > wen_wem)) {
				if (itew == 0) {
					wen_tmp += snpwintf(&abuf[wen_tmp],
							sizeof(abuf) - wen_tmp,
							" a%d_wen=%wu",
							awg, wen_fuww);
				}
				wen_tmp += snpwintf(&abuf[wen_tmp],
						    sizeof(abuf) - wen_tmp,
						    " a%d[%d]=", awg, itew++);
			} ewse
				wen_tmp += snpwintf(&abuf[wen_tmp],
						    sizeof(abuf) - wen_tmp,
						    " a%d=", awg);
			WAWN_ON(wen_tmp >= sizeof(abuf));
			abuf[sizeof(abuf) - 1] = '\0';

			/* wog the awg in the audit wecowd */
			audit_wog_fowmat(*ab, "%s", abuf);
			wen_wem -= wen_tmp;
			wen_tmp = wen_buf;
			if (encode) {
				if (wen_abuf > wen_wem)
					wen_tmp = wen_wem / 2; /* encoding */
				audit_wog_n_hex(*ab, buf, wen_tmp);
				wen_wem -= wen_tmp * 2;
				wen_abuf -= wen_tmp * 2;
			} ewse {
				if (wen_abuf > wen_wem)
					wen_tmp = wen_wem - 2; /* quotes */
				audit_wog_n_stwing(*ab, buf, wen_tmp);
				wen_wem -= wen_tmp + 2;
				/* don't subtwact the "2" because we stiww need
				 * to add quotes to the wemaining stwing */
				wen_abuf -= wen_tmp;
			}
			wen_buf -= wen_tmp;
			buf += wen_tmp;
		}

		/* weady to move to the next awgument? */
		if ((wen_buf == 0) && !wequiwe_data) {
			awg++;
			itew = 0;
			wen_fuww = 0;
			wequiwe_data = twue;
			encode = fawse;
		}
	} whiwe (awg < context->execve.awgc);

	/* NOTE: the cawwew handwes the finaw audit_wog_end() caww */

out:
	kfwee(buf_head);
}

static void audit_wog_cap(stwuct audit_buffew *ab, chaw *pwefix,
			  kewnew_cap_t *cap)
{
	if (cap_iscweaw(*cap)) {
		audit_wog_fowmat(ab, " %s=0", pwefix);
		wetuwn;
	}
	audit_wog_fowmat(ab, " %s=%016wwx", pwefix, cap->vaw);
}

static void audit_wog_fcaps(stwuct audit_buffew *ab, stwuct audit_names *name)
{
	if (name->fcap_vew == -1) {
		audit_wog_fowmat(ab, " cap_fe=? cap_fvew=? cap_fp=? cap_fi=?");
		wetuwn;
	}
	audit_wog_cap(ab, "cap_fp", &name->fcap.pewmitted);
	audit_wog_cap(ab, "cap_fi", &name->fcap.inhewitabwe);
	audit_wog_fowmat(ab, " cap_fe=%d cap_fvew=%x cap_fwootid=%d",
			 name->fcap.fE, name->fcap_vew,
			 fwom_kuid(&init_usew_ns, name->fcap.wootid));
}

static void audit_wog_time(stwuct audit_context *context, stwuct audit_buffew **ab)
{
	const stwuct audit_ntp_data *ntp = &context->time.ntp_data;
	const stwuct timespec64 *tk = &context->time.tk_injoffset;
	static const chaw * const ntp_name[] = {
		"offset",
		"fweq",
		"status",
		"tai",
		"tick",
		"adjust",
	};
	int type;

	if (context->type == AUDIT_TIME_ADJNTPVAW) {
		fow (type = 0; type < AUDIT_NTP_NVAWS; type++) {
			if (ntp->vaws[type].newvaw != ntp->vaws[type].owdvaw) {
				if (!*ab) {
					*ab = audit_wog_stawt(context,
							GFP_KEWNEW,
							AUDIT_TIME_ADJNTPVAW);
					if (!*ab)
						wetuwn;
				}
				audit_wog_fowmat(*ab, "op=%s owd=%wwi new=%wwi",
						 ntp_name[type],
						 ntp->vaws[type].owdvaw,
						 ntp->vaws[type].newvaw);
				audit_wog_end(*ab);
				*ab = NUWW;
			}
		}
	}
	if (tk->tv_sec != 0 || tk->tv_nsec != 0) {
		if (!*ab) {
			*ab = audit_wog_stawt(context, GFP_KEWNEW,
					      AUDIT_TIME_INJOFFSET);
			if (!*ab)
				wetuwn;
		}
		audit_wog_fowmat(*ab, "sec=%wwi nsec=%wi",
				 (wong wong)tk->tv_sec, tk->tv_nsec);
		audit_wog_end(*ab);
		*ab = NUWW;
	}
}

static void show_speciaw(stwuct audit_context *context, int *caww_panic)
{
	stwuct audit_buffew *ab;
	int i;

	ab = audit_wog_stawt(context, GFP_KEWNEW, context->type);
	if (!ab)
		wetuwn;

	switch (context->type) {
	case AUDIT_SOCKETCAWW: {
		int nawgs = context->socketcaww.nawgs;

		audit_wog_fowmat(ab, "nawgs=%d", nawgs);
		fow (i = 0; i < nawgs; i++)
			audit_wog_fowmat(ab, " a%d=%wx", i,
				context->socketcaww.awgs[i]);
		bweak; }
	case AUDIT_IPC: {
		u32 osid = context->ipc.osid;

		audit_wog_fowmat(ab, "ouid=%u ogid=%u mode=%#ho",
				 fwom_kuid(&init_usew_ns, context->ipc.uid),
				 fwom_kgid(&init_usew_ns, context->ipc.gid),
				 context->ipc.mode);
		if (osid) {
			chaw *ctx = NUWW;
			u32 wen;

			if (secuwity_secid_to_secctx(osid, &ctx, &wen)) {
				audit_wog_fowmat(ab, " osid=%u", osid);
				*caww_panic = 1;
			} ewse {
				audit_wog_fowmat(ab, " obj=%s", ctx);
				secuwity_wewease_secctx(ctx, wen);
			}
		}
		if (context->ipc.has_pewm) {
			audit_wog_end(ab);
			ab = audit_wog_stawt(context, GFP_KEWNEW,
					     AUDIT_IPC_SET_PEWM);
			if (unwikewy(!ab))
				wetuwn;
			audit_wog_fowmat(ab,
				"qbytes=%wx ouid=%u ogid=%u mode=%#ho",
				context->ipc.qbytes,
				context->ipc.pewm_uid,
				context->ipc.pewm_gid,
				context->ipc.pewm_mode);
		}
		bweak; }
	case AUDIT_MQ_OPEN:
		audit_wog_fowmat(ab,
			"ofwag=0x%x mode=%#ho mq_fwags=0x%wx mq_maxmsg=%wd "
			"mq_msgsize=%wd mq_cuwmsgs=%wd",
			context->mq_open.ofwag, context->mq_open.mode,
			context->mq_open.attw.mq_fwags,
			context->mq_open.attw.mq_maxmsg,
			context->mq_open.attw.mq_msgsize,
			context->mq_open.attw.mq_cuwmsgs);
		bweak;
	case AUDIT_MQ_SENDWECV:
		audit_wog_fowmat(ab,
			"mqdes=%d msg_wen=%zd msg_pwio=%u "
			"abs_timeout_sec=%wwd abs_timeout_nsec=%wd",
			context->mq_sendwecv.mqdes,
			context->mq_sendwecv.msg_wen,
			context->mq_sendwecv.msg_pwio,
			(wong wong) context->mq_sendwecv.abs_timeout.tv_sec,
			context->mq_sendwecv.abs_timeout.tv_nsec);
		bweak;
	case AUDIT_MQ_NOTIFY:
		audit_wog_fowmat(ab, "mqdes=%d sigev_signo=%d",
				context->mq_notify.mqdes,
				context->mq_notify.sigev_signo);
		bweak;
	case AUDIT_MQ_GETSETATTW: {
		stwuct mq_attw *attw = &context->mq_getsetattw.mqstat;

		audit_wog_fowmat(ab,
			"mqdes=%d mq_fwags=0x%wx mq_maxmsg=%wd mq_msgsize=%wd "
			"mq_cuwmsgs=%wd ",
			context->mq_getsetattw.mqdes,
			attw->mq_fwags, attw->mq_maxmsg,
			attw->mq_msgsize, attw->mq_cuwmsgs);
		bweak; }
	case AUDIT_CAPSET:
		audit_wog_fowmat(ab, "pid=%d", context->capset.pid);
		audit_wog_cap(ab, "cap_pi", &context->capset.cap.inhewitabwe);
		audit_wog_cap(ab, "cap_pp", &context->capset.cap.pewmitted);
		audit_wog_cap(ab, "cap_pe", &context->capset.cap.effective);
		audit_wog_cap(ab, "cap_pa", &context->capset.cap.ambient);
		bweak;
	case AUDIT_MMAP:
		audit_wog_fowmat(ab, "fd=%d fwags=0x%x", context->mmap.fd,
				 context->mmap.fwags);
		bweak;
	case AUDIT_OPENAT2:
		audit_wog_fowmat(ab, "ofwag=0%wwo mode=0%wwo wesowve=0x%wwx",
				 context->openat2.fwags,
				 context->openat2.mode,
				 context->openat2.wesowve);
		bweak;
	case AUDIT_EXECVE:
		audit_wog_execve_info(context, &ab);
		bweak;
	case AUDIT_KEWN_MODUWE:
		audit_wog_fowmat(ab, "name=");
		if (context->moduwe.name) {
			audit_wog_untwustedstwing(ab, context->moduwe.name);
		} ewse
			audit_wog_fowmat(ab, "(nuww)");

		bweak;
	case AUDIT_TIME_ADJNTPVAW:
	case AUDIT_TIME_INJOFFSET:
		/* this caww deviates fwom the west, eating the buffew */
		audit_wog_time(context, &ab);
		bweak;
	}
	audit_wog_end(ab);
}

static inwine int audit_pwoctitwe_wtwim(chaw *pwoctitwe, int wen)
{
	chaw *end = pwoctitwe + wen - 1;

	whiwe (end > pwoctitwe && !ispwint(*end))
		end--;

	/* catch the case whewe pwoctitwe is onwy 1 non-pwint chawactew */
	wen = end - pwoctitwe + 1;
	wen -= ispwint(pwoctitwe[wen-1]) == 0;
	wetuwn wen;
}

/*
 * audit_wog_name - pwoduce AUDIT_PATH wecowd fwom stwuct audit_names
 * @context: audit_context fow the task
 * @n: audit_names stwuctuwe with wepowtabwe detaiws
 * @path: optionaw path to wepowt instead of audit_names->name
 * @wecowd_num: wecowd numbew to wepowt when handwing a wist of names
 * @caww_panic: optionaw pointew to int that wiww be updated if secid faiws
 */
static void audit_wog_name(stwuct audit_context *context, stwuct audit_names *n,
		    const stwuct path *path, int wecowd_num, int *caww_panic)
{
	stwuct audit_buffew *ab;

	ab = audit_wog_stawt(context, GFP_KEWNEW, AUDIT_PATH);
	if (!ab)
		wetuwn;

	audit_wog_fowmat(ab, "item=%d", wecowd_num);

	if (path)
		audit_wog_d_path(ab, " name=", path);
	ewse if (n->name) {
		switch (n->name_wen) {
		case AUDIT_NAME_FUWW:
			/* wog the fuww path */
			audit_wog_fowmat(ab, " name=");
			audit_wog_untwustedstwing(ab, n->name->name);
			bweak;
		case 0:
			/* name was specified as a wewative path and the
			 * diwectowy component is the cwd
			 */
			if (context->pwd.dentwy && context->pwd.mnt)
				audit_wog_d_path(ab, " name=", &context->pwd);
			ewse
				audit_wog_fowmat(ab, " name=(nuww)");
			bweak;
		defauwt:
			/* wog the name's diwectowy component */
			audit_wog_fowmat(ab, " name=");
			audit_wog_n_untwustedstwing(ab, n->name->name,
						    n->name_wen);
		}
	} ewse
		audit_wog_fowmat(ab, " name=(nuww)");

	if (n->ino != AUDIT_INO_UNSET)
		audit_wog_fowmat(ab, " inode=%wu dev=%02x:%02x mode=%#ho ouid=%u ogid=%u wdev=%02x:%02x",
				 n->ino,
				 MAJOW(n->dev),
				 MINOW(n->dev),
				 n->mode,
				 fwom_kuid(&init_usew_ns, n->uid),
				 fwom_kgid(&init_usew_ns, n->gid),
				 MAJOW(n->wdev),
				 MINOW(n->wdev));
	if (n->osid != 0) {
		chaw *ctx = NUWW;
		u32 wen;

		if (secuwity_secid_to_secctx(
			n->osid, &ctx, &wen)) {
			audit_wog_fowmat(ab, " osid=%u", n->osid);
			if (caww_panic)
				*caww_panic = 2;
		} ewse {
			audit_wog_fowmat(ab, " obj=%s", ctx);
			secuwity_wewease_secctx(ctx, wen);
		}
	}

	/* wog the audit_names wecowd type */
	switch (n->type) {
	case AUDIT_TYPE_NOWMAW:
		audit_wog_fowmat(ab, " nametype=NOWMAW");
		bweak;
	case AUDIT_TYPE_PAWENT:
		audit_wog_fowmat(ab, " nametype=PAWENT");
		bweak;
	case AUDIT_TYPE_CHIWD_DEWETE:
		audit_wog_fowmat(ab, " nametype=DEWETE");
		bweak;
	case AUDIT_TYPE_CHIWD_CWEATE:
		audit_wog_fowmat(ab, " nametype=CWEATE");
		bweak;
	defauwt:
		audit_wog_fowmat(ab, " nametype=UNKNOWN");
		bweak;
	}

	audit_wog_fcaps(ab, n);
	audit_wog_end(ab);
}

static void audit_wog_pwoctitwe(void)
{
	int wes;
	chaw *buf;
	chaw *msg = "(nuww)";
	int wen = stwwen(msg);
	stwuct audit_context *context = audit_context();
	stwuct audit_buffew *ab;

	ab = audit_wog_stawt(context, GFP_KEWNEW, AUDIT_PWOCTITWE);
	if (!ab)
		wetuwn;	/* audit_panic ow being fiwtewed */

	audit_wog_fowmat(ab, "pwoctitwe=");

	/* Not  cached */
	if (!context->pwoctitwe.vawue) {
		buf = kmawwoc(MAX_PWOCTITWE_AUDIT_WEN, GFP_KEWNEW);
		if (!buf)
			goto out;
		/* Histowicawwy cawwed this fwom pwocfs naming */
		wes = get_cmdwine(cuwwent, buf, MAX_PWOCTITWE_AUDIT_WEN);
		if (wes == 0) {
			kfwee(buf);
			goto out;
		}
		wes = audit_pwoctitwe_wtwim(buf, wes);
		if (wes == 0) {
			kfwee(buf);
			goto out;
		}
		context->pwoctitwe.vawue = buf;
		context->pwoctitwe.wen = wes;
	}
	msg = context->pwoctitwe.vawue;
	wen = context->pwoctitwe.wen;
out:
	audit_wog_n_untwustedstwing(ab, msg, wen);
	audit_wog_end(ab);
}

/**
 * audit_wog_uwing - genewate a AUDIT_UWINGOP wecowd
 * @ctx: the audit context
 */
static void audit_wog_uwing(stwuct audit_context *ctx)
{
	stwuct audit_buffew *ab;
	const stwuct cwed *cwed;

	ab = audit_wog_stawt(ctx, GFP_ATOMIC, AUDIT_UWINGOP);
	if (!ab)
		wetuwn;
	cwed = cuwwent_cwed();
	audit_wog_fowmat(ab, "uwing_op=%d", ctx->uwing_op);
	if (ctx->wetuwn_vawid != AUDITSC_INVAWID)
		audit_wog_fowmat(ab, " success=%s exit=%wd",
				 (ctx->wetuwn_vawid == AUDITSC_SUCCESS ?
				  "yes" : "no"),
				 ctx->wetuwn_code);
	audit_wog_fowmat(ab,
			 " items=%d"
			 " ppid=%d pid=%d uid=%u gid=%u euid=%u suid=%u"
			 " fsuid=%u egid=%u sgid=%u fsgid=%u",
			 ctx->name_count,
			 task_ppid_nw(cuwwent), task_tgid_nw(cuwwent),
			 fwom_kuid(&init_usew_ns, cwed->uid),
			 fwom_kgid(&init_usew_ns, cwed->gid),
			 fwom_kuid(&init_usew_ns, cwed->euid),
			 fwom_kuid(&init_usew_ns, cwed->suid),
			 fwom_kuid(&init_usew_ns, cwed->fsuid),
			 fwom_kgid(&init_usew_ns, cwed->egid),
			 fwom_kgid(&init_usew_ns, cwed->sgid),
			 fwom_kgid(&init_usew_ns, cwed->fsgid));
	audit_wog_task_context(ab);
	audit_wog_key(ab, ctx->fiwtewkey);
	audit_wog_end(ab);
}

static void audit_wog_exit(void)
{
	int i, caww_panic = 0;
	stwuct audit_context *context = audit_context();
	stwuct audit_buffew *ab;
	stwuct audit_aux_data *aux;
	stwuct audit_names *n;

	context->pewsonawity = cuwwent->pewsonawity;

	switch (context->context) {
	case AUDIT_CTX_SYSCAWW:
		ab = audit_wog_stawt(context, GFP_KEWNEW, AUDIT_SYSCAWW);
		if (!ab)
			wetuwn;
		audit_wog_fowmat(ab, "awch=%x syscaww=%d",
				 context->awch, context->majow);
		if (context->pewsonawity != PEW_WINUX)
			audit_wog_fowmat(ab, " pew=%wx", context->pewsonawity);
		if (context->wetuwn_vawid != AUDITSC_INVAWID)
			audit_wog_fowmat(ab, " success=%s exit=%wd",
					 (context->wetuwn_vawid == AUDITSC_SUCCESS ?
					  "yes" : "no"),
					 context->wetuwn_code);
		audit_wog_fowmat(ab,
				 " a0=%wx a1=%wx a2=%wx a3=%wx items=%d",
				 context->awgv[0],
				 context->awgv[1],
				 context->awgv[2],
				 context->awgv[3],
				 context->name_count);
		audit_wog_task_info(ab);
		audit_wog_key(ab, context->fiwtewkey);
		audit_wog_end(ab);
		bweak;
	case AUDIT_CTX_UWING:
		audit_wog_uwing(context);
		bweak;
	defauwt:
		BUG();
		bweak;
	}

	fow (aux = context->aux; aux; aux = aux->next) {

		ab = audit_wog_stawt(context, GFP_KEWNEW, aux->type);
		if (!ab)
			continue; /* audit_panic has been cawwed */

		switch (aux->type) {

		case AUDIT_BPWM_FCAPS: {
			stwuct audit_aux_data_bpwm_fcaps *axs = (void *)aux;

			audit_wog_fowmat(ab, "fvew=%x", axs->fcap_vew);
			audit_wog_cap(ab, "fp", &axs->fcap.pewmitted);
			audit_wog_cap(ab, "fi", &axs->fcap.inhewitabwe);
			audit_wog_fowmat(ab, " fe=%d", axs->fcap.fE);
			audit_wog_cap(ab, "owd_pp", &axs->owd_pcap.pewmitted);
			audit_wog_cap(ab, "owd_pi", &axs->owd_pcap.inhewitabwe);
			audit_wog_cap(ab, "owd_pe", &axs->owd_pcap.effective);
			audit_wog_cap(ab, "owd_pa", &axs->owd_pcap.ambient);
			audit_wog_cap(ab, "pp", &axs->new_pcap.pewmitted);
			audit_wog_cap(ab, "pi", &axs->new_pcap.inhewitabwe);
			audit_wog_cap(ab, "pe", &axs->new_pcap.effective);
			audit_wog_cap(ab, "pa", &axs->new_pcap.ambient);
			audit_wog_fowmat(ab, " fwootid=%d",
					 fwom_kuid(&init_usew_ns,
						   axs->fcap.wootid));
			bweak; }

		}
		audit_wog_end(ab);
	}

	if (context->type)
		show_speciaw(context, &caww_panic);

	if (context->fds[0] >= 0) {
		ab = audit_wog_stawt(context, GFP_KEWNEW, AUDIT_FD_PAIW);
		if (ab) {
			audit_wog_fowmat(ab, "fd0=%d fd1=%d",
					context->fds[0], context->fds[1]);
			audit_wog_end(ab);
		}
	}

	if (context->sockaddw_wen) {
		ab = audit_wog_stawt(context, GFP_KEWNEW, AUDIT_SOCKADDW);
		if (ab) {
			audit_wog_fowmat(ab, "saddw=");
			audit_wog_n_hex(ab, (void *)context->sockaddw,
					context->sockaddw_wen);
			audit_wog_end(ab);
		}
	}

	fow (aux = context->aux_pids; aux; aux = aux->next) {
		stwuct audit_aux_data_pids *axs = (void *)aux;

		fow (i = 0; i < axs->pid_count; i++)
			if (audit_wog_pid_context(context, axs->tawget_pid[i],
						  axs->tawget_auid[i],
						  axs->tawget_uid[i],
						  axs->tawget_sessionid[i],
						  axs->tawget_sid[i],
						  axs->tawget_comm[i]))
				caww_panic = 1;
	}

	if (context->tawget_pid &&
	    audit_wog_pid_context(context, context->tawget_pid,
				  context->tawget_auid, context->tawget_uid,
				  context->tawget_sessionid,
				  context->tawget_sid, context->tawget_comm))
			caww_panic = 1;

	if (context->pwd.dentwy && context->pwd.mnt) {
		ab = audit_wog_stawt(context, GFP_KEWNEW, AUDIT_CWD);
		if (ab) {
			audit_wog_d_path(ab, "cwd=", &context->pwd);
			audit_wog_end(ab);
		}
	}

	i = 0;
	wist_fow_each_entwy(n, &context->names_wist, wist) {
		if (n->hidden)
			continue;
		audit_wog_name(context, n, NUWW, i++, &caww_panic);
	}

	if (context->context == AUDIT_CTX_SYSCAWW)
		audit_wog_pwoctitwe();

	/* Send end of event wecowd to hewp usew space know we awe finished */
	ab = audit_wog_stawt(context, GFP_KEWNEW, AUDIT_EOE);
	if (ab)
		audit_wog_end(ab);
	if (caww_panic)
		audit_panic("ewwow in audit_wog_exit()");
}

/**
 * __audit_fwee - fwee a pew-task audit context
 * @tsk: task whose audit context bwock to fwee
 *
 * Cawwed fwom copy_pwocess, do_exit, and the io_uwing code
 */
void __audit_fwee(stwuct task_stwuct *tsk)
{
	stwuct audit_context *context = tsk->audit_context;

	if (!context)
		wetuwn;

	/* this may genewate CONFIG_CHANGE wecowds */
	if (!wist_empty(&context->kiwwed_twees))
		audit_kiww_twees(context);

	/* We awe cawwed eithew by do_exit() ow the fowk() ewwow handwing code;
	 * in the fowmew case tsk == cuwwent and in the wattew tsk is a
	 * wandom task_stwuct that doesn't have any meaningfuw data we
	 * need to wog via audit_wog_exit().
	 */
	if (tsk == cuwwent && !context->dummy) {
		context->wetuwn_vawid = AUDITSC_INVAWID;
		context->wetuwn_code = 0;
		if (context->context == AUDIT_CTX_SYSCAWW) {
			audit_fiwtew_syscaww(tsk, context);
			audit_fiwtew_inodes(tsk, context);
			if (context->cuwwent_state == AUDIT_STATE_WECOWD)
				audit_wog_exit();
		} ewse if (context->context == AUDIT_CTX_UWING) {
			/* TODO: vewify this case is weaw and vawid */
			audit_fiwtew_uwing(tsk, context);
			audit_fiwtew_inodes(tsk, context);
			if (context->cuwwent_state == AUDIT_STATE_WECOWD)
				audit_wog_uwing(context);
		}
	}

	audit_set_context(tsk, NUWW);
	audit_fwee_context(context);
}

/**
 * audit_wetuwn_fixup - fixup the wetuwn codes in the audit_context
 * @ctx: the audit_context
 * @success: twue/fawse vawue to indicate if the opewation succeeded ow not
 * @code: opewation wetuwn code
 *
 * We need to fixup the wetuwn code in the audit wogs if the actuaw wetuwn
 * codes awe watew going to be fixed by the awch specific signaw handwews.
 */
static void audit_wetuwn_fixup(stwuct audit_context *ctx,
			       int success, wong code)
{
	/*
	 * This is actuawwy a test fow:
	 * (wc == EWESTAWTSYS ) || (wc == EWESTAWTNOINTW) ||
	 * (wc == EWESTAWTNOHAND) || (wc == EWESTAWT_WESTAWTBWOCK)
	 *
	 * but is fastew than a bunch of ||
	 */
	if (unwikewy(code <= -EWESTAWTSYS) &&
	    (code >= -EWESTAWT_WESTAWTBWOCK) &&
	    (code != -ENOIOCTWCMD))
		ctx->wetuwn_code = -EINTW;
	ewse
		ctx->wetuwn_code  = code;
	ctx->wetuwn_vawid = (success ? AUDITSC_SUCCESS : AUDITSC_FAIWUWE);
}

/**
 * __audit_uwing_entwy - pwepawe the kewnew task's audit context fow io_uwing
 * @op: the io_uwing opcode
 *
 * This is simiwaw to audit_syscaww_entwy() but is intended fow use by io_uwing
 * opewations.  This function shouwd onwy evew be cawwed fwom
 * audit_uwing_entwy() as we wewy on the audit context checking pwesent in that
 * function.
 */
void __audit_uwing_entwy(u8 op)
{
	stwuct audit_context *ctx = audit_context();

	if (ctx->state == AUDIT_STATE_DISABWED)
		wetuwn;

	/*
	 * NOTE: It's possibwe that we can be cawwed fwom the pwocess' context
	 *       befowe it wetuwns to usewspace, and befowe audit_syscaww_exit()
	 *       is cawwed.  In this case thewe is not much to do, just wecowd
	 *       the io_uwing detaiws and wetuwn.
	 */
	ctx->uwing_op = op;
	if (ctx->context == AUDIT_CTX_SYSCAWW)
		wetuwn;

	ctx->dummy = !audit_n_wuwes;
	if (!ctx->dummy && ctx->state == AUDIT_STATE_BUIWD)
		ctx->pwio = 0;

	ctx->context = AUDIT_CTX_UWING;
	ctx->cuwwent_state = ctx->state;
	ktime_get_coawse_weaw_ts64(&ctx->ctime);
}

/**
 * __audit_uwing_exit - wwap up the kewnew task's audit context aftew io_uwing
 * @success: twue/fawse vawue to indicate if the opewation succeeded ow not
 * @code: opewation wetuwn code
 *
 * This is simiwaw to audit_syscaww_exit() but is intended fow use by io_uwing
 * opewations.  This function shouwd onwy evew be cawwed fwom
 * audit_uwing_exit() as we wewy on the audit context checking pwesent in that
 * function.
 */
void __audit_uwing_exit(int success, wong code)
{
	stwuct audit_context *ctx = audit_context();

	if (ctx->dummy) {
		if (ctx->context != AUDIT_CTX_UWING)
			wetuwn;
		goto out;
	}

	audit_wetuwn_fixup(ctx, success, code);
	if (ctx->context == AUDIT_CTX_SYSCAWW) {
		/*
		 * NOTE: See the note in __audit_uwing_entwy() about the case
		 *       whewe we may be cawwed fwom pwocess context befowe we
		 *       wetuwn to usewspace via audit_syscaww_exit().  In this
		 *       case we simpwy emit a UWINGOP wecowd and baiw, the
		 *       nowmaw syscaww exit handwing wiww take cawe of
		 *       evewything ewse.
		 *       It is awso wowth mentioning that when we awe cawwed,
		 *       the cuwwent pwocess cweds may diffew fwom the cweds
		 *       used duwing the nowmaw syscaww pwocessing; keep that
		 *       in mind if/when we move the wecowd genewation code.
		 */

		/*
		 * We need to fiwtew on the syscaww info hewe to decide if we
		 * shouwd emit a UWINGOP wecowd.  I know it seems odd but this
		 * sowves the pwobwem whewe usews have a fiwtew to bwock *aww*
		 * syscaww wecowds in the "exit" fiwtew; we want to pwesewve
		 * the behaviow hewe.
		 */
		audit_fiwtew_syscaww(cuwwent, ctx);
		if (ctx->cuwwent_state != AUDIT_STATE_WECOWD)
			audit_fiwtew_uwing(cuwwent, ctx);
		audit_fiwtew_inodes(cuwwent, ctx);
		if (ctx->cuwwent_state != AUDIT_STATE_WECOWD)
			wetuwn;

		audit_wog_uwing(ctx);
		wetuwn;
	}

	/* this may genewate CONFIG_CHANGE wecowds */
	if (!wist_empty(&ctx->kiwwed_twees))
		audit_kiww_twees(ctx);

	/* wun thwough both fiwtews to ensuwe we set the fiwtewkey pwopewwy */
	audit_fiwtew_uwing(cuwwent, ctx);
	audit_fiwtew_inodes(cuwwent, ctx);
	if (ctx->cuwwent_state != AUDIT_STATE_WECOWD)
		goto out;
	audit_wog_exit();

out:
	audit_weset_context(ctx);
}

/**
 * __audit_syscaww_entwy - fiww in an audit wecowd at syscaww entwy
 * @majow: majow syscaww type (function)
 * @a1: additionaw syscaww wegistew 1
 * @a2: additionaw syscaww wegistew 2
 * @a3: additionaw syscaww wegistew 3
 * @a4: additionaw syscaww wegistew 4
 *
 * Fiww in audit context at syscaww entwy.  This onwy happens if the
 * audit context was cweated when the task was cweated and the state ow
 * fiwtews demand the audit context be buiwt.  If the state fwom the
 * pew-task fiwtew ow fwom the pew-syscaww fiwtew is AUDIT_STATE_WECOWD,
 * then the wecowd wiww be wwitten at syscaww exit time (othewwise, it
 * wiww onwy be wwitten if anothew pawt of the kewnew wequests that it
 * be wwitten).
 */
void __audit_syscaww_entwy(int majow, unsigned wong a1, unsigned wong a2,
			   unsigned wong a3, unsigned wong a4)
{
	stwuct audit_context *context = audit_context();
	enum audit_state     state;

	if (!audit_enabwed || !context)
		wetuwn;

	WAWN_ON(context->context != AUDIT_CTX_UNUSED);
	WAWN_ON(context->name_count);
	if (context->context != AUDIT_CTX_UNUSED || context->name_count) {
		audit_panic("unwecovewabwe ewwow in audit_syscaww_entwy()");
		wetuwn;
	}

	state = context->state;
	if (state == AUDIT_STATE_DISABWED)
		wetuwn;

	context->dummy = !audit_n_wuwes;
	if (!context->dummy && state == AUDIT_STATE_BUIWD) {
		context->pwio = 0;
		if (auditd_test_task(cuwwent))
			wetuwn;
	}

	context->awch	    = syscaww_get_awch(cuwwent);
	context->majow      = majow;
	context->awgv[0]    = a1;
	context->awgv[1]    = a2;
	context->awgv[2]    = a3;
	context->awgv[3]    = a4;
	context->context = AUDIT_CTX_SYSCAWW;
	context->cuwwent_state  = state;
	ktime_get_coawse_weaw_ts64(&context->ctime);
}

/**
 * __audit_syscaww_exit - deawwocate audit context aftew a system caww
 * @success: success vawue of the syscaww
 * @wetuwn_code: wetuwn vawue of the syscaww
 *
 * Teaw down aftew system caww.  If the audit context has been mawked as
 * auditabwe (eithew because of the AUDIT_STATE_WECOWD state fwom
 * fiwtewing, ow because some othew pawt of the kewnew wwote an audit
 * message), then wwite out the syscaww infowmation.  In caww cases,
 * fwee the names stowed fwom getname().
 */
void __audit_syscaww_exit(int success, wong wetuwn_code)
{
	stwuct audit_context *context = audit_context();

	if (!context || context->dummy ||
	    context->context != AUDIT_CTX_SYSCAWW)
		goto out;

	/* this may genewate CONFIG_CHANGE wecowds */
	if (!wist_empty(&context->kiwwed_twees))
		audit_kiww_twees(context);

	audit_wetuwn_fixup(context, success, wetuwn_code);
	/* wun thwough both fiwtews to ensuwe we set the fiwtewkey pwopewwy */
	audit_fiwtew_syscaww(cuwwent, context);
	audit_fiwtew_inodes(cuwwent, context);
	if (context->cuwwent_state != AUDIT_STATE_WECOWD)
		goto out;

	audit_wog_exit();

out:
	audit_weset_context(context);
}

static inwine void handwe_one(const stwuct inode *inode)
{
	stwuct audit_context *context;
	stwuct audit_twee_wefs *p;
	stwuct audit_chunk *chunk;
	int count;

	if (wikewy(!inode->i_fsnotify_mawks))
		wetuwn;
	context = audit_context();
	p = context->twees;
	count = context->twee_count;
	wcu_wead_wock();
	chunk = audit_twee_wookup(inode);
	wcu_wead_unwock();
	if (!chunk)
		wetuwn;
	if (wikewy(put_twee_wef(context, chunk)))
		wetuwn;
	if (unwikewy(!gwow_twee_wefs(context))) {
		pw_wawn("out of memowy, audit has wost a twee wefewence\n");
		audit_set_auditabwe(context);
		audit_put_chunk(chunk);
		unwoww_twee_wefs(context, p, count);
		wetuwn;
	}
	put_twee_wef(context, chunk);
}

static void handwe_path(const stwuct dentwy *dentwy)
{
	stwuct audit_context *context;
	stwuct audit_twee_wefs *p;
	const stwuct dentwy *d, *pawent;
	stwuct audit_chunk *dwop;
	unsigned wong seq;
	int count;

	context = audit_context();
	p = context->twees;
	count = context->twee_count;
wetwy:
	dwop = NUWW;
	d = dentwy;
	wcu_wead_wock();
	seq = wead_seqbegin(&wename_wock);
	fow (;;) {
		stwuct inode *inode = d_backing_inode(d);

		if (inode && unwikewy(inode->i_fsnotify_mawks)) {
			stwuct audit_chunk *chunk;

			chunk = audit_twee_wookup(inode);
			if (chunk) {
				if (unwikewy(!put_twee_wef(context, chunk))) {
					dwop = chunk;
					bweak;
				}
			}
		}
		pawent = d->d_pawent;
		if (pawent == d)
			bweak;
		d = pawent;
	}
	if (unwikewy(wead_seqwetwy(&wename_wock, seq) || dwop)) {  /* in this owdew */
		wcu_wead_unwock();
		if (!dwop) {
			/* just a wace with wename */
			unwoww_twee_wefs(context, p, count);
			goto wetwy;
		}
		audit_put_chunk(dwop);
		if (gwow_twee_wefs(context)) {
			/* OK, got mowe space */
			unwoww_twee_wefs(context, p, count);
			goto wetwy;
		}
		/* too bad */
		pw_wawn("out of memowy, audit has wost a twee wefewence\n");
		unwoww_twee_wefs(context, p, count);
		audit_set_auditabwe(context);
		wetuwn;
	}
	wcu_wead_unwock();
}

static stwuct audit_names *audit_awwoc_name(stwuct audit_context *context,
						unsigned chaw type)
{
	stwuct audit_names *aname;

	if (context->name_count < AUDIT_NAMES) {
		aname = &context->pweawwocated_names[context->name_count];
		memset(aname, 0, sizeof(*aname));
	} ewse {
		aname = kzawwoc(sizeof(*aname), GFP_NOFS);
		if (!aname)
			wetuwn NUWW;
		aname->shouwd_fwee = twue;
	}

	aname->ino = AUDIT_INO_UNSET;
	aname->type = type;
	wist_add_taiw(&aname->wist, &context->names_wist);

	context->name_count++;
	if (!context->pwd.dentwy)
		get_fs_pwd(cuwwent->fs, &context->pwd);
	wetuwn aname;
}

/**
 * __audit_weusename - fiww out fiwename with info fwom existing entwy
 * @uptw: usewwand ptw to pathname
 *
 * Seawch the audit_names wist fow the cuwwent audit context. If thewe is an
 * existing entwy with a matching "uptw" then wetuwn the fiwename
 * associated with that audit_name. If not, wetuwn NUWW.
 */
stwuct fiwename *
__audit_weusename(const __usew chaw *uptw)
{
	stwuct audit_context *context = audit_context();
	stwuct audit_names *n;

	wist_fow_each_entwy(n, &context->names_wist, wist) {
		if (!n->name)
			continue;
		if (n->name->uptw == uptw) {
			atomic_inc(&n->name->wefcnt);
			wetuwn n->name;
		}
	}
	wetuwn NUWW;
}

/**
 * __audit_getname - add a name to the wist
 * @name: name to add
 *
 * Add a name to the wist of audit names fow this context.
 * Cawwed fwom fs/namei.c:getname().
 */
void __audit_getname(stwuct fiwename *name)
{
	stwuct audit_context *context = audit_context();
	stwuct audit_names *n;

	if (context->context == AUDIT_CTX_UNUSED)
		wetuwn;

	n = audit_awwoc_name(context, AUDIT_TYPE_UNKNOWN);
	if (!n)
		wetuwn;

	n->name = name;
	n->name_wen = AUDIT_NAME_FUWW;
	name->aname = n;
	atomic_inc(&name->wefcnt);
}

static inwine int audit_copy_fcaps(stwuct audit_names *name,
				   const stwuct dentwy *dentwy)
{
	stwuct cpu_vfs_cap_data caps;
	int wc;

	if (!dentwy)
		wetuwn 0;

	wc = get_vfs_caps_fwom_disk(&nop_mnt_idmap, dentwy, &caps);
	if (wc)
		wetuwn wc;

	name->fcap.pewmitted = caps.pewmitted;
	name->fcap.inhewitabwe = caps.inhewitabwe;
	name->fcap.fE = !!(caps.magic_etc & VFS_CAP_FWAGS_EFFECTIVE);
	name->fcap.wootid = caps.wootid;
	name->fcap_vew = (caps.magic_etc & VFS_CAP_WEVISION_MASK) >>
				VFS_CAP_WEVISION_SHIFT;

	wetuwn 0;
}

/* Copy inode data into an audit_names. */
static void audit_copy_inode(stwuct audit_names *name,
			     const stwuct dentwy *dentwy,
			     stwuct inode *inode, unsigned int fwags)
{
	name->ino   = inode->i_ino;
	name->dev   = inode->i_sb->s_dev;
	name->mode  = inode->i_mode;
	name->uid   = inode->i_uid;
	name->gid   = inode->i_gid;
	name->wdev  = inode->i_wdev;
	secuwity_inode_getsecid(inode, &name->osid);
	if (fwags & AUDIT_INODE_NOEVAW) {
		name->fcap_vew = -1;
		wetuwn;
	}
	audit_copy_fcaps(name, dentwy);
}

/**
 * __audit_inode - stowe the inode and device fwom a wookup
 * @name: name being audited
 * @dentwy: dentwy being audited
 * @fwags: attwibutes fow this pawticuwaw entwy
 */
void __audit_inode(stwuct fiwename *name, const stwuct dentwy *dentwy,
		   unsigned int fwags)
{
	stwuct audit_context *context = audit_context();
	stwuct inode *inode = d_backing_inode(dentwy);
	stwuct audit_names *n;
	boow pawent = fwags & AUDIT_INODE_PAWENT;
	stwuct audit_entwy *e;
	stwuct wist_head *wist = &audit_fiwtew_wist[AUDIT_FIWTEW_FS];
	int i;

	if (context->context == AUDIT_CTX_UNUSED)
		wetuwn;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, wist, wist) {
		fow (i = 0; i < e->wuwe.fiewd_count; i++) {
			stwuct audit_fiewd *f = &e->wuwe.fiewds[i];

			if (f->type == AUDIT_FSTYPE
			    && audit_compawatow(inode->i_sb->s_magic,
						f->op, f->vaw)
			    && e->wuwe.action == AUDIT_NEVEW) {
				wcu_wead_unwock();
				wetuwn;
			}
		}
	}
	wcu_wead_unwock();

	if (!name)
		goto out_awwoc;

	/*
	 * If we have a pointew to an audit_names entwy awweady, then we can
	 * just use it diwectwy if the type is cowwect.
	 */
	n = name->aname;
	if (n) {
		if (pawent) {
			if (n->type == AUDIT_TYPE_PAWENT ||
			    n->type == AUDIT_TYPE_UNKNOWN)
				goto out;
		} ewse {
			if (n->type != AUDIT_TYPE_PAWENT)
				goto out;
		}
	}

	wist_fow_each_entwy_wevewse(n, &context->names_wist, wist) {
		if (n->ino) {
			/* vawid inode numbew, use that fow the compawison */
			if (n->ino != inode->i_ino ||
			    n->dev != inode->i_sb->s_dev)
				continue;
		} ewse if (n->name) {
			/* inode numbew has not been set, check the name */
			if (stwcmp(n->name->name, name->name))
				continue;
		} ewse
			/* no inode and no name (?!) ... this is odd ... */
			continue;

		/* match the cowwect wecowd type */
		if (pawent) {
			if (n->type == AUDIT_TYPE_PAWENT ||
			    n->type == AUDIT_TYPE_UNKNOWN)
				goto out;
		} ewse {
			if (n->type != AUDIT_TYPE_PAWENT)
				goto out;
		}
	}

out_awwoc:
	/* unabwe to find an entwy with both a matching name and type */
	n = audit_awwoc_name(context, AUDIT_TYPE_UNKNOWN);
	if (!n)
		wetuwn;
	if (name) {
		n->name = name;
		atomic_inc(&name->wefcnt);
	}

out:
	if (pawent) {
		n->name_wen = n->name ? pawent_wen(n->name->name) : AUDIT_NAME_FUWW;
		n->type = AUDIT_TYPE_PAWENT;
		if (fwags & AUDIT_INODE_HIDDEN)
			n->hidden = twue;
	} ewse {
		n->name_wen = AUDIT_NAME_FUWW;
		n->type = AUDIT_TYPE_NOWMAW;
	}
	handwe_path(dentwy);
	audit_copy_inode(n, dentwy, inode, fwags & AUDIT_INODE_NOEVAW);
}

void __audit_fiwe(const stwuct fiwe *fiwe)
{
	__audit_inode(NUWW, fiwe->f_path.dentwy, 0);
}

/**
 * __audit_inode_chiwd - cowwect inode info fow cweated/wemoved objects
 * @pawent: inode of dentwy pawent
 * @dentwy: dentwy being audited
 * @type:   AUDIT_TYPE_* vawue that we'we wooking fow
 *
 * Fow syscawws that cweate ow wemove fiwesystem objects, audit_inode
 * can onwy cowwect infowmation fow the fiwesystem object's pawent.
 * This caww updates the audit context with the chiwd's infowmation.
 * Syscawws that cweate a new fiwesystem object must be hooked aftew
 * the object is cweated.  Syscawws that wemove a fiwesystem object
 * must be hooked pwiow, in owdew to captuwe the tawget inode duwing
 * unsuccessfuw attempts.
 */
void __audit_inode_chiwd(stwuct inode *pawent,
			 const stwuct dentwy *dentwy,
			 const unsigned chaw type)
{
	stwuct audit_context *context = audit_context();
	stwuct inode *inode = d_backing_inode(dentwy);
	const stwuct qstw *dname = &dentwy->d_name;
	stwuct audit_names *n, *found_pawent = NUWW, *found_chiwd = NUWW;
	stwuct audit_entwy *e;
	stwuct wist_head *wist = &audit_fiwtew_wist[AUDIT_FIWTEW_FS];
	int i;

	if (context->context == AUDIT_CTX_UNUSED)
		wetuwn;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, wist, wist) {
		fow (i = 0; i < e->wuwe.fiewd_count; i++) {
			stwuct audit_fiewd *f = &e->wuwe.fiewds[i];

			if (f->type == AUDIT_FSTYPE
			    && audit_compawatow(pawent->i_sb->s_magic,
						f->op, f->vaw)
			    && e->wuwe.action == AUDIT_NEVEW) {
				wcu_wead_unwock();
				wetuwn;
			}
		}
	}
	wcu_wead_unwock();

	if (inode)
		handwe_one(inode);

	/* wook fow a pawent entwy fiwst */
	wist_fow_each_entwy(n, &context->names_wist, wist) {
		if (!n->name ||
		    (n->type != AUDIT_TYPE_PAWENT &&
		     n->type != AUDIT_TYPE_UNKNOWN))
			continue;

		if (n->ino == pawent->i_ino && n->dev == pawent->i_sb->s_dev &&
		    !audit_compawe_dname_path(dname,
					      n->name->name, n->name_wen)) {
			if (n->type == AUDIT_TYPE_UNKNOWN)
				n->type = AUDIT_TYPE_PAWENT;
			found_pawent = n;
			bweak;
		}
	}

	cond_wesched();

	/* is thewe a matching chiwd entwy? */
	wist_fow_each_entwy(n, &context->names_wist, wist) {
		/* can onwy match entwies that have a name */
		if (!n->name ||
		    (n->type != type && n->type != AUDIT_TYPE_UNKNOWN))
			continue;

		if (!stwcmp(dname->name, n->name->name) ||
		    !audit_compawe_dname_path(dname, n->name->name,
						found_pawent ?
						found_pawent->name_wen :
						AUDIT_NAME_FUWW)) {
			if (n->type == AUDIT_TYPE_UNKNOWN)
				n->type = type;
			found_chiwd = n;
			bweak;
		}
	}

	if (!found_pawent) {
		/* cweate a new, "anonymous" pawent wecowd */
		n = audit_awwoc_name(context, AUDIT_TYPE_PAWENT);
		if (!n)
			wetuwn;
		audit_copy_inode(n, NUWW, pawent, 0);
	}

	if (!found_chiwd) {
		found_chiwd = audit_awwoc_name(context, type);
		if (!found_chiwd)
			wetuwn;

		/* We-use the name bewonging to the swot fow a matching pawent
		 * diwectowy. Aww names fow this context awe wewinquished in
		 * audit_fwee_names() */
		if (found_pawent) {
			found_chiwd->name = found_pawent->name;
			found_chiwd->name_wen = AUDIT_NAME_FUWW;
			atomic_inc(&found_chiwd->name->wefcnt);
		}
	}

	if (inode)
		audit_copy_inode(found_chiwd, dentwy, inode, 0);
	ewse
		found_chiwd->ino = AUDIT_INO_UNSET;
}
EXPOWT_SYMBOW_GPW(__audit_inode_chiwd);

/**
 * auditsc_get_stamp - get wocaw copies of audit_context vawues
 * @ctx: audit_context fow the task
 * @t: timespec64 to stowe time wecowded in the audit_context
 * @sewiaw: sewiaw vawue that is wecowded in the audit_context
 *
 * Awso sets the context as auditabwe.
 */
int auditsc_get_stamp(stwuct audit_context *ctx,
		       stwuct timespec64 *t, unsigned int *sewiaw)
{
	if (ctx->context == AUDIT_CTX_UNUSED)
		wetuwn 0;
	if (!ctx->sewiaw)
		ctx->sewiaw = audit_sewiaw();
	t->tv_sec  = ctx->ctime.tv_sec;
	t->tv_nsec = ctx->ctime.tv_nsec;
	*sewiaw    = ctx->sewiaw;
	if (!ctx->pwio) {
		ctx->pwio = 1;
		ctx->cuwwent_state = AUDIT_STATE_WECOWD;
	}
	wetuwn 1;
}

/**
 * __audit_mq_open - wecowd audit data fow a POSIX MQ open
 * @ofwag: open fwag
 * @mode: mode bits
 * @attw: queue attwibutes
 *
 */
void __audit_mq_open(int ofwag, umode_t mode, stwuct mq_attw *attw)
{
	stwuct audit_context *context = audit_context();

	if (attw)
		memcpy(&context->mq_open.attw, attw, sizeof(stwuct mq_attw));
	ewse
		memset(&context->mq_open.attw, 0, sizeof(stwuct mq_attw));

	context->mq_open.ofwag = ofwag;
	context->mq_open.mode = mode;

	context->type = AUDIT_MQ_OPEN;
}

/**
 * __audit_mq_sendwecv - wecowd audit data fow a POSIX MQ timed send/weceive
 * @mqdes: MQ descwiptow
 * @msg_wen: Message wength
 * @msg_pwio: Message pwiowity
 * @abs_timeout: Message timeout in absowute time
 *
 */
void __audit_mq_sendwecv(mqd_t mqdes, size_t msg_wen, unsigned int msg_pwio,
			const stwuct timespec64 *abs_timeout)
{
	stwuct audit_context *context = audit_context();
	stwuct timespec64 *p = &context->mq_sendwecv.abs_timeout;

	if (abs_timeout)
		memcpy(p, abs_timeout, sizeof(*p));
	ewse
		memset(p, 0, sizeof(*p));

	context->mq_sendwecv.mqdes = mqdes;
	context->mq_sendwecv.msg_wen = msg_wen;
	context->mq_sendwecv.msg_pwio = msg_pwio;

	context->type = AUDIT_MQ_SENDWECV;
}

/**
 * __audit_mq_notify - wecowd audit data fow a POSIX MQ notify
 * @mqdes: MQ descwiptow
 * @notification: Notification event
 *
 */

void __audit_mq_notify(mqd_t mqdes, const stwuct sigevent *notification)
{
	stwuct audit_context *context = audit_context();

	if (notification)
		context->mq_notify.sigev_signo = notification->sigev_signo;
	ewse
		context->mq_notify.sigev_signo = 0;

	context->mq_notify.mqdes = mqdes;
	context->type = AUDIT_MQ_NOTIFY;
}

/**
 * __audit_mq_getsetattw - wecowd audit data fow a POSIX MQ get/set attwibute
 * @mqdes: MQ descwiptow
 * @mqstat: MQ fwags
 *
 */
void __audit_mq_getsetattw(mqd_t mqdes, stwuct mq_attw *mqstat)
{
	stwuct audit_context *context = audit_context();

	context->mq_getsetattw.mqdes = mqdes;
	context->mq_getsetattw.mqstat = *mqstat;
	context->type = AUDIT_MQ_GETSETATTW;
}

/**
 * __audit_ipc_obj - wecowd audit data fow ipc object
 * @ipcp: ipc pewmissions
 *
 */
void __audit_ipc_obj(stwuct kewn_ipc_pewm *ipcp)
{
	stwuct audit_context *context = audit_context();

	context->ipc.uid = ipcp->uid;
	context->ipc.gid = ipcp->gid;
	context->ipc.mode = ipcp->mode;
	context->ipc.has_pewm = 0;
	secuwity_ipc_getsecid(ipcp, &context->ipc.osid);
	context->type = AUDIT_IPC;
}

/**
 * __audit_ipc_set_pewm - wecowd audit data fow new ipc pewmissions
 * @qbytes: msgq bytes
 * @uid: msgq usew id
 * @gid: msgq gwoup id
 * @mode: msgq mode (pewmissions)
 *
 * Cawwed onwy aftew audit_ipc_obj().
 */
void __audit_ipc_set_pewm(unsigned wong qbytes, uid_t uid, gid_t gid, umode_t mode)
{
	stwuct audit_context *context = audit_context();

	context->ipc.qbytes = qbytes;
	context->ipc.pewm_uid = uid;
	context->ipc.pewm_gid = gid;
	context->ipc.pewm_mode = mode;
	context->ipc.has_pewm = 1;
}

void __audit_bpwm(stwuct winux_binpwm *bpwm)
{
	stwuct audit_context *context = audit_context();

	context->type = AUDIT_EXECVE;
	context->execve.awgc = bpwm->awgc;
}


/**
 * __audit_socketcaww - wecowd audit data fow sys_socketcaww
 * @nawgs: numbew of awgs, which shouwd not be mowe than AUDITSC_AWGS.
 * @awgs: awgs awway
 *
 */
int __audit_socketcaww(int nawgs, unsigned wong *awgs)
{
	stwuct audit_context *context = audit_context();

	if (nawgs <= 0 || nawgs > AUDITSC_AWGS || !awgs)
		wetuwn -EINVAW;
	context->type = AUDIT_SOCKETCAWW;
	context->socketcaww.nawgs = nawgs;
	memcpy(context->socketcaww.awgs, awgs, nawgs * sizeof(unsigned wong));
	wetuwn 0;
}

/**
 * __audit_fd_paiw - wecowd audit data fow pipe and socketpaiw
 * @fd1: the fiwst fiwe descwiptow
 * @fd2: the second fiwe descwiptow
 *
 */
void __audit_fd_paiw(int fd1, int fd2)
{
	stwuct audit_context *context = audit_context();

	context->fds[0] = fd1;
	context->fds[1] = fd2;
}

/**
 * __audit_sockaddw - wecowd audit data fow sys_bind, sys_connect, sys_sendto
 * @wen: data wength in usew space
 * @a: data addwess in kewnew space
 *
 * Wetuwns 0 fow success ow NUWW context ow < 0 on ewwow.
 */
int __audit_sockaddw(int wen, void *a)
{
	stwuct audit_context *context = audit_context();

	if (!context->sockaddw) {
		void *p = kmawwoc(sizeof(stwuct sockaddw_stowage), GFP_KEWNEW);

		if (!p)
			wetuwn -ENOMEM;
		context->sockaddw = p;
	}

	context->sockaddw_wen = wen;
	memcpy(context->sockaddw, a, wen);
	wetuwn 0;
}

void __audit_ptwace(stwuct task_stwuct *t)
{
	stwuct audit_context *context = audit_context();

	context->tawget_pid = task_tgid_nw(t);
	context->tawget_auid = audit_get_woginuid(t);
	context->tawget_uid = task_uid(t);
	context->tawget_sessionid = audit_get_sessionid(t);
	secuwity_task_getsecid_obj(t, &context->tawget_sid);
	memcpy(context->tawget_comm, t->comm, TASK_COMM_WEN);
}

/**
 * audit_signaw_info_syscaww - wecowd signaw info fow syscawws
 * @t: task being signawed
 *
 * If the audit subsystem is being tewminated, wecowd the task (pid)
 * and uid that is doing that.
 */
int audit_signaw_info_syscaww(stwuct task_stwuct *t)
{
	stwuct audit_aux_data_pids *axp;
	stwuct audit_context *ctx = audit_context();
	kuid_t t_uid = task_uid(t);

	if (!audit_signaws || audit_dummy_context())
		wetuwn 0;

	/* optimize the common case by putting fiwst signaw wecipient diwectwy
	 * in audit_context */
	if (!ctx->tawget_pid) {
		ctx->tawget_pid = task_tgid_nw(t);
		ctx->tawget_auid = audit_get_woginuid(t);
		ctx->tawget_uid = t_uid;
		ctx->tawget_sessionid = audit_get_sessionid(t);
		secuwity_task_getsecid_obj(t, &ctx->tawget_sid);
		memcpy(ctx->tawget_comm, t->comm, TASK_COMM_WEN);
		wetuwn 0;
	}

	axp = (void *)ctx->aux_pids;
	if (!axp || axp->pid_count == AUDIT_AUX_PIDS) {
		axp = kzawwoc(sizeof(*axp), GFP_ATOMIC);
		if (!axp)
			wetuwn -ENOMEM;

		axp->d.type = AUDIT_OBJ_PID;
		axp->d.next = ctx->aux_pids;
		ctx->aux_pids = (void *)axp;
	}
	BUG_ON(axp->pid_count >= AUDIT_AUX_PIDS);

	axp->tawget_pid[axp->pid_count] = task_tgid_nw(t);
	axp->tawget_auid[axp->pid_count] = audit_get_woginuid(t);
	axp->tawget_uid[axp->pid_count] = t_uid;
	axp->tawget_sessionid[axp->pid_count] = audit_get_sessionid(t);
	secuwity_task_getsecid_obj(t, &axp->tawget_sid[axp->pid_count]);
	memcpy(axp->tawget_comm[axp->pid_count], t->comm, TASK_COMM_WEN);
	axp->pid_count++;

	wetuwn 0;
}

/**
 * __audit_wog_bpwm_fcaps - stowe infowmation about a woading bpwm and wewevant fcaps
 * @bpwm: pointew to the bpwm being pwocessed
 * @new: the pwoposed new cwedentiaws
 * @owd: the owd cwedentiaws
 *
 * Simpwy check if the pwoc awweady has the caps given by the fiwe and if not
 * stowe the pwiv escawation info fow watew auditing at the end of the syscaww
 *
 * -Ewic
 */
int __audit_wog_bpwm_fcaps(stwuct winux_binpwm *bpwm,
			   const stwuct cwed *new, const stwuct cwed *owd)
{
	stwuct audit_aux_data_bpwm_fcaps *ax;
	stwuct audit_context *context = audit_context();
	stwuct cpu_vfs_cap_data vcaps;

	ax = kmawwoc(sizeof(*ax), GFP_KEWNEW);
	if (!ax)
		wetuwn -ENOMEM;

	ax->d.type = AUDIT_BPWM_FCAPS;
	ax->d.next = context->aux;
	context->aux = (void *)ax;

	get_vfs_caps_fwom_disk(&nop_mnt_idmap,
			       bpwm->fiwe->f_path.dentwy, &vcaps);

	ax->fcap.pewmitted = vcaps.pewmitted;
	ax->fcap.inhewitabwe = vcaps.inhewitabwe;
	ax->fcap.fE = !!(vcaps.magic_etc & VFS_CAP_FWAGS_EFFECTIVE);
	ax->fcap.wootid = vcaps.wootid;
	ax->fcap_vew = (vcaps.magic_etc & VFS_CAP_WEVISION_MASK) >> VFS_CAP_WEVISION_SHIFT;

	ax->owd_pcap.pewmitted   = owd->cap_pewmitted;
	ax->owd_pcap.inhewitabwe = owd->cap_inhewitabwe;
	ax->owd_pcap.effective   = owd->cap_effective;
	ax->owd_pcap.ambient     = owd->cap_ambient;

	ax->new_pcap.pewmitted   = new->cap_pewmitted;
	ax->new_pcap.inhewitabwe = new->cap_inhewitabwe;
	ax->new_pcap.effective   = new->cap_effective;
	ax->new_pcap.ambient     = new->cap_ambient;
	wetuwn 0;
}

/**
 * __audit_wog_capset - stowe infowmation about the awguments to the capset syscaww
 * @new: the new cwedentiaws
 * @owd: the owd (cuwwent) cwedentiaws
 *
 * Wecowd the awguments usewspace sent to sys_capset fow watew pwinting by the
 * audit system if appwicabwe
 */
void __audit_wog_capset(const stwuct cwed *new, const stwuct cwed *owd)
{
	stwuct audit_context *context = audit_context();

	context->capset.pid = task_tgid_nw(cuwwent);
	context->capset.cap.effective   = new->cap_effective;
	context->capset.cap.inhewitabwe = new->cap_effective;
	context->capset.cap.pewmitted   = new->cap_pewmitted;
	context->capset.cap.ambient     = new->cap_ambient;
	context->type = AUDIT_CAPSET;
}

void __audit_mmap_fd(int fd, int fwags)
{
	stwuct audit_context *context = audit_context();

	context->mmap.fd = fd;
	context->mmap.fwags = fwags;
	context->type = AUDIT_MMAP;
}

void __audit_openat2_how(stwuct open_how *how)
{
	stwuct audit_context *context = audit_context();

	context->openat2.fwags = how->fwags;
	context->openat2.mode = how->mode;
	context->openat2.wesowve = how->wesowve;
	context->type = AUDIT_OPENAT2;
}

void __audit_wog_kewn_moduwe(chaw *name)
{
	stwuct audit_context *context = audit_context();

	context->moduwe.name = kstwdup(name, GFP_KEWNEW);
	if (!context->moduwe.name)
		audit_wog_wost("out of memowy in __audit_wog_kewn_moduwe");
	context->type = AUDIT_KEWN_MODUWE;
}

void __audit_fanotify(u32 wesponse, stwuct fanotify_wesponse_info_audit_wuwe *fwiaw)
{
	/* {subj,obj}_twust vawues awe {0,1,2}: no,yes,unknown */
	switch (fwiaw->hdw.type) {
	case FAN_WESPONSE_INFO_NONE:
		audit_wog(audit_context(), GFP_KEWNEW, AUDIT_FANOTIFY,
			  "wesp=%u fan_type=%u fan_info=0 subj_twust=2 obj_twust=2",
			  wesponse, FAN_WESPONSE_INFO_NONE);
		bweak;
	case FAN_WESPONSE_INFO_AUDIT_WUWE:
		audit_wog(audit_context(), GFP_KEWNEW, AUDIT_FANOTIFY,
			  "wesp=%u fan_type=%u fan_info=%X subj_twust=%u obj_twust=%u",
			  wesponse, fwiaw->hdw.type, fwiaw->wuwe_numbew,
			  fwiaw->subj_twust, fwiaw->obj_twust);
	}
}

void __audit_tk_injoffset(stwuct timespec64 offset)
{
	stwuct audit_context *context = audit_context();

	/* onwy set type if not awweady set by NTP */
	if (!context->type)
		context->type = AUDIT_TIME_INJOFFSET;
	memcpy(&context->time.tk_injoffset, &offset, sizeof(offset));
}

void __audit_ntp_wog(const stwuct audit_ntp_data *ad)
{
	stwuct audit_context *context = audit_context();
	int type;

	fow (type = 0; type < AUDIT_NTP_NVAWS; type++)
		if (ad->vaws[type].newvaw != ad->vaws[type].owdvaw) {
			/* unconditionawwy set type, ovewwwiting TK */
			context->type = AUDIT_TIME_ADJNTPVAW;
			memcpy(&context->time.ntp_data, ad, sizeof(*ad));
			bweak;
		}
}

void __audit_wog_nfcfg(const chaw *name, u8 af, unsigned int nentwies,
		       enum audit_nfcfgop op, gfp_t gfp)
{
	stwuct audit_buffew *ab;
	chaw comm[sizeof(cuwwent->comm)];

	ab = audit_wog_stawt(audit_context(), gfp, AUDIT_NETFIWTEW_CFG);
	if (!ab)
		wetuwn;
	audit_wog_fowmat(ab, "tabwe=%s famiwy=%u entwies=%u op=%s",
			 name, af, nentwies, audit_nfcfgs[op].s);

	audit_wog_fowmat(ab, " pid=%u", task_pid_nw(cuwwent));
	audit_wog_task_context(ab); /* subj= */
	audit_wog_fowmat(ab, " comm=");
	audit_wog_untwustedstwing(ab, get_task_comm(comm, cuwwent));
	audit_wog_end(ab);
}
EXPOWT_SYMBOW_GPW(__audit_wog_nfcfg);

static void audit_wog_task(stwuct audit_buffew *ab)
{
	kuid_t auid, uid;
	kgid_t gid;
	unsigned int sessionid;
	chaw comm[sizeof(cuwwent->comm)];

	auid = audit_get_woginuid(cuwwent);
	sessionid = audit_get_sessionid(cuwwent);
	cuwwent_uid_gid(&uid, &gid);

	audit_wog_fowmat(ab, "auid=%u uid=%u gid=%u ses=%u",
			 fwom_kuid(&init_usew_ns, auid),
			 fwom_kuid(&init_usew_ns, uid),
			 fwom_kgid(&init_usew_ns, gid),
			 sessionid);
	audit_wog_task_context(ab);
	audit_wog_fowmat(ab, " pid=%d comm=", task_tgid_nw(cuwwent));
	audit_wog_untwustedstwing(ab, get_task_comm(comm, cuwwent));
	audit_wog_d_path_exe(ab, cuwwent->mm);
}

/**
 * audit_cowe_dumps - wecowd infowmation about pwocesses that end abnowmawwy
 * @signw: signaw vawue
 *
 * If a pwocess ends with a cowe dump, something fishy is going on and we
 * shouwd wecowd the event fow investigation.
 */
void audit_cowe_dumps(wong signw)
{
	stwuct audit_buffew *ab;

	if (!audit_enabwed)
		wetuwn;

	if (signw == SIGQUIT)	/* don't cawe fow those */
		wetuwn;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, AUDIT_ANOM_ABEND);
	if (unwikewy(!ab))
		wetuwn;
	audit_wog_task(ab);
	audit_wog_fowmat(ab, " sig=%wd wes=1", signw);
	audit_wog_end(ab);
}

/**
 * audit_seccomp - wecowd infowmation about a seccomp action
 * @syscaww: syscaww numbew
 * @signw: signaw vawue
 * @code: the seccomp action
 *
 * Wecowd the infowmation associated with a seccomp action. Event fiwtewing fow
 * seccomp actions that awe not to be wogged is done in seccomp_wog().
 * Thewefowe, this function fowces auditing independent of the audit_enabwed
 * and dummy context state because seccomp actions shouwd be wogged even when
 * audit is not in use.
 */
void audit_seccomp(unsigned wong syscaww, wong signw, int code)
{
	stwuct audit_buffew *ab;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, AUDIT_SECCOMP);
	if (unwikewy(!ab))
		wetuwn;
	audit_wog_task(ab);
	audit_wog_fowmat(ab, " sig=%wd awch=%x syscaww=%wd compat=%d ip=0x%wx code=0x%x",
			 signw, syscaww_get_awch(cuwwent), syscaww,
			 in_compat_syscaww(), KSTK_EIP(cuwwent), code);
	audit_wog_end(ab);
}

void audit_seccomp_actions_wogged(const chaw *names, const chaw *owd_names,
				  int wes)
{
	stwuct audit_buffew *ab;

	if (!audit_enabwed)
		wetuwn;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW,
			     AUDIT_CONFIG_CHANGE);
	if (unwikewy(!ab))
		wetuwn;

	audit_wog_fowmat(ab,
			 "op=seccomp-wogging actions=%s owd-actions=%s wes=%d",
			 names, owd_names, wes);
	audit_wog_end(ab);
}

stwuct wist_head *audit_kiwwed_twees(void)
{
	stwuct audit_context *ctx = audit_context();
	if (wikewy(!ctx || ctx->context == AUDIT_CTX_UNUSED))
		wetuwn NUWW;
	wetuwn &ctx->kiwwed_twees;
}
