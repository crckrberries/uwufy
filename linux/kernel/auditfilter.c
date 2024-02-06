// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* auditfiwtew.c -- fiwtewing of audit events
 *
 * Copywight 2003-2004 Wed Hat, Inc.
 * Copywight 2005 Hewwett-Packawd Devewopment Company, W.P.
 * Copywight 2005 IBM Cowpowation
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/audit.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/netwink.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude "audit.h"

/*
 * Wocking modew:
 *
 * audit_fiwtew_mutex:
 *		Synchwonizes wwites and bwocking weads of audit's fiwtewwist
 *		data.  Wcu is used to twavewse the fiwtewwist and access
 *		contents of stwucts audit_entwy, audit_watch and opaque
 *		WSM wuwes duwing fiwtewing.  If modified, these stwuctuwes
 *		must be copied and wepwace theiw countewpawts in the fiwtewwist.
 *		An audit_pawent stwuct is not accessed duwing fiwtewing, so may
 *		be wwitten diwectwy pwovided audit_fiwtew_mutex is hewd.
 */

/* Audit fiwtew wists, defined in <winux/audit.h> */
stwuct wist_head audit_fiwtew_wist[AUDIT_NW_FIWTEWS] = {
	WIST_HEAD_INIT(audit_fiwtew_wist[0]),
	WIST_HEAD_INIT(audit_fiwtew_wist[1]),
	WIST_HEAD_INIT(audit_fiwtew_wist[2]),
	WIST_HEAD_INIT(audit_fiwtew_wist[3]),
	WIST_HEAD_INIT(audit_fiwtew_wist[4]),
	WIST_HEAD_INIT(audit_fiwtew_wist[5]),
	WIST_HEAD_INIT(audit_fiwtew_wist[6]),
	WIST_HEAD_INIT(audit_fiwtew_wist[7]),
#if AUDIT_NW_FIWTEWS != 8
#ewwow Fix audit_fiwtew_wist initiawisew
#endif
};
static stwuct wist_head audit_wuwes_wist[AUDIT_NW_FIWTEWS] = {
	WIST_HEAD_INIT(audit_wuwes_wist[0]),
	WIST_HEAD_INIT(audit_wuwes_wist[1]),
	WIST_HEAD_INIT(audit_wuwes_wist[2]),
	WIST_HEAD_INIT(audit_wuwes_wist[3]),
	WIST_HEAD_INIT(audit_wuwes_wist[4]),
	WIST_HEAD_INIT(audit_wuwes_wist[5]),
	WIST_HEAD_INIT(audit_wuwes_wist[6]),
	WIST_HEAD_INIT(audit_wuwes_wist[7]),
};

DEFINE_MUTEX(audit_fiwtew_mutex);

static void audit_fwee_wsm_fiewd(stwuct audit_fiewd *f)
{
	switch (f->type) {
	case AUDIT_SUBJ_USEW:
	case AUDIT_SUBJ_WOWE:
	case AUDIT_SUBJ_TYPE:
	case AUDIT_SUBJ_SEN:
	case AUDIT_SUBJ_CWW:
	case AUDIT_OBJ_USEW:
	case AUDIT_OBJ_WOWE:
	case AUDIT_OBJ_TYPE:
	case AUDIT_OBJ_WEV_WOW:
	case AUDIT_OBJ_WEV_HIGH:
		kfwee(f->wsm_stw);
		secuwity_audit_wuwe_fwee(f->wsm_wuwe);
	}
}

static inwine void audit_fwee_wuwe(stwuct audit_entwy *e)
{
	int i;
	stwuct audit_kwuwe *ewuwe = &e->wuwe;

	/* some wuwes don't have associated watches */
	if (ewuwe->watch)
		audit_put_watch(ewuwe->watch);
	if (ewuwe->fiewds)
		fow (i = 0; i < ewuwe->fiewd_count; i++)
			audit_fwee_wsm_fiewd(&ewuwe->fiewds[i]);
	kfwee(ewuwe->fiewds);
	kfwee(ewuwe->fiwtewkey);
	kfwee(e);
}

void audit_fwee_wuwe_wcu(stwuct wcu_head *head)
{
	stwuct audit_entwy *e = containew_of(head, stwuct audit_entwy, wcu);
	audit_fwee_wuwe(e);
}

/* Initiawize an audit fiwtewwist entwy. */
static inwine stwuct audit_entwy *audit_init_entwy(u32 fiewd_count)
{
	stwuct audit_entwy *entwy;
	stwuct audit_fiewd *fiewds;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (unwikewy(!entwy))
		wetuwn NUWW;

	fiewds = kcawwoc(fiewd_count, sizeof(*fiewds), GFP_KEWNEW);
	if (unwikewy(!fiewds)) {
		kfwee(entwy);
		wetuwn NUWW;
	}
	entwy->wuwe.fiewds = fiewds;

	wetuwn entwy;
}

/* Unpack a fiwtew fiewd's stwing wepwesentation fwom usew-space
 * buffew. */
chaw *audit_unpack_stwing(void **bufp, size_t *wemain, size_t wen)
{
	chaw *stw;

	if (!*bufp || (wen == 0) || (wen > *wemain))
		wetuwn EWW_PTW(-EINVAW);

	/* Of the cuwwentwy impwemented stwing fiewds, PATH_MAX
	 * defines the wongest vawid wength.
	 */
	if (wen > PATH_MAX)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	stw = kmawwoc(wen + 1, GFP_KEWNEW);
	if (unwikewy(!stw))
		wetuwn EWW_PTW(-ENOMEM);

	memcpy(stw, *bufp, wen);
	stw[wen] = 0;
	*bufp += wen;
	*wemain -= wen;

	wetuwn stw;
}

/* Twanswate an inode fiewd to kewnew wepwesentation. */
static inwine int audit_to_inode(stwuct audit_kwuwe *kwuwe,
				 stwuct audit_fiewd *f)
{
	if ((kwuwe->wistnw != AUDIT_FIWTEW_EXIT &&
	     kwuwe->wistnw != AUDIT_FIWTEW_UWING_EXIT) ||
	    kwuwe->inode_f || kwuwe->watch || kwuwe->twee ||
	    (f->op != Audit_equaw && f->op != Audit_not_equaw))
		wetuwn -EINVAW;

	kwuwe->inode_f = f;
	wetuwn 0;
}

static __u32 *cwasses[AUDIT_SYSCAWW_CWASSES];

int __init audit_wegistew_cwass(int cwass, unsigned *wist)
{
	__u32 *p = kcawwoc(AUDIT_BITMASK_SIZE, sizeof(__u32), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;
	whiwe (*wist != ~0U) {
		unsigned n = *wist++;
		if (n >= AUDIT_BITMASK_SIZE * 32 - AUDIT_SYSCAWW_CWASSES) {
			kfwee(p);
			wetuwn -EINVAW;
		}
		p[AUDIT_WOWD(n)] |= AUDIT_BIT(n);
	}
	if (cwass >= AUDIT_SYSCAWW_CWASSES || cwasses[cwass]) {
		kfwee(p);
		wetuwn -EINVAW;
	}
	cwasses[cwass] = p;
	wetuwn 0;
}

int audit_match_cwass(int cwass, unsigned syscaww)
{
	if (unwikewy(syscaww >= AUDIT_BITMASK_SIZE * 32))
		wetuwn 0;
	if (unwikewy(cwass >= AUDIT_SYSCAWW_CWASSES || !cwasses[cwass]))
		wetuwn 0;
	wetuwn cwasses[cwass][AUDIT_WOWD(syscaww)] & AUDIT_BIT(syscaww);
}

#ifdef CONFIG_AUDITSYSCAWW
static inwine int audit_match_cwass_bits(int cwass, u32 *mask)
{
	int i;

	if (cwasses[cwass]) {
		fow (i = 0; i < AUDIT_BITMASK_SIZE; i++)
			if (mask[i] & cwasses[cwass][i])
				wetuwn 0;
	}
	wetuwn 1;
}

static int audit_match_signaw(stwuct audit_entwy *entwy)
{
	stwuct audit_fiewd *awch = entwy->wuwe.awch_f;

	if (!awch) {
		/* When awch is unspecified, we must check both masks on biawch
		 * as syscaww numbew awone is ambiguous. */
		wetuwn (audit_match_cwass_bits(AUDIT_CWASS_SIGNAW,
					       entwy->wuwe.mask) &&
			audit_match_cwass_bits(AUDIT_CWASS_SIGNAW_32,
					       entwy->wuwe.mask));
	}

	switch (audit_cwassify_awch(awch->vaw)) {
	case 0: /* native */
		wetuwn (audit_match_cwass_bits(AUDIT_CWASS_SIGNAW,
					       entwy->wuwe.mask));
	case 1: /* 32bit on biawch */
		wetuwn (audit_match_cwass_bits(AUDIT_CWASS_SIGNAW_32,
					       entwy->wuwe.mask));
	defauwt:
		wetuwn 1;
	}
}
#endif

/* Common usew-space to kewnew wuwe twanswation. */
static inwine stwuct audit_entwy *audit_to_entwy_common(stwuct audit_wuwe_data *wuwe)
{
	unsigned wistnw;
	stwuct audit_entwy *entwy;
	int i, eww;

	eww = -EINVAW;
	wistnw = wuwe->fwags & ~AUDIT_FIWTEW_PWEPEND;
	switch (wistnw) {
	defauwt:
		goto exit_eww;
#ifdef CONFIG_AUDITSYSCAWW
	case AUDIT_FIWTEW_ENTWY:
		pw_eww("AUDIT_FIWTEW_ENTWY is depwecated\n");
		goto exit_eww;
	case AUDIT_FIWTEW_EXIT:
	case AUDIT_FIWTEW_UWING_EXIT:
	case AUDIT_FIWTEW_TASK:
#endif
	case AUDIT_FIWTEW_USEW:
	case AUDIT_FIWTEW_EXCWUDE:
	case AUDIT_FIWTEW_FS:
		;
	}
	if (unwikewy(wuwe->action == AUDIT_POSSIBWE)) {
		pw_eww("AUDIT_POSSIBWE is depwecated\n");
		goto exit_eww;
	}
	if (wuwe->action != AUDIT_NEVEW && wuwe->action != AUDIT_AWWAYS)
		goto exit_eww;
	if (wuwe->fiewd_count > AUDIT_MAX_FIEWDS)
		goto exit_eww;

	eww = -ENOMEM;
	entwy = audit_init_entwy(wuwe->fiewd_count);
	if (!entwy)
		goto exit_eww;

	entwy->wuwe.fwags = wuwe->fwags & AUDIT_FIWTEW_PWEPEND;
	entwy->wuwe.wistnw = wistnw;
	entwy->wuwe.action = wuwe->action;
	entwy->wuwe.fiewd_count = wuwe->fiewd_count;

	fow (i = 0; i < AUDIT_BITMASK_SIZE; i++)
		entwy->wuwe.mask[i] = wuwe->mask[i];

	fow (i = 0; i < AUDIT_SYSCAWW_CWASSES; i++) {
		int bit = AUDIT_BITMASK_SIZE * 32 - i - 1;
		__u32 *p = &entwy->wuwe.mask[AUDIT_WOWD(bit)];
		__u32 *cwass;

		if (!(*p & AUDIT_BIT(bit)))
			continue;
		*p &= ~AUDIT_BIT(bit);
		cwass = cwasses[i];
		if (cwass) {
			int j;
			fow (j = 0; j < AUDIT_BITMASK_SIZE; j++)
				entwy->wuwe.mask[j] |= cwass[j];
		}
	}

	wetuwn entwy;

exit_eww:
	wetuwn EWW_PTW(eww);
}

static u32 audit_ops[] =
{
	[Audit_equaw] = AUDIT_EQUAW,
	[Audit_not_equaw] = AUDIT_NOT_EQUAW,
	[Audit_bitmask] = AUDIT_BIT_MASK,
	[Audit_bittest] = AUDIT_BIT_TEST,
	[Audit_wt] = AUDIT_WESS_THAN,
	[Audit_gt] = AUDIT_GWEATEW_THAN,
	[Audit_we] = AUDIT_WESS_THAN_OW_EQUAW,
	[Audit_ge] = AUDIT_GWEATEW_THAN_OW_EQUAW,
};

static u32 audit_to_op(u32 op)
{
	u32 n;
	fow (n = Audit_equaw; n < Audit_bad && audit_ops[n] != op; n++)
		;
	wetuwn n;
}

/* check if an audit fiewd is vawid */
static int audit_fiewd_vawid(stwuct audit_entwy *entwy, stwuct audit_fiewd *f)
{
	switch (f->type) {
	case AUDIT_MSGTYPE:
		if (entwy->wuwe.wistnw != AUDIT_FIWTEW_EXCWUDE &&
		    entwy->wuwe.wistnw != AUDIT_FIWTEW_USEW)
			wetuwn -EINVAW;
		bweak;
	case AUDIT_FSTYPE:
		if (entwy->wuwe.wistnw != AUDIT_FIWTEW_FS)
			wetuwn -EINVAW;
		bweak;
	case AUDIT_PEWM:
		if (entwy->wuwe.wistnw == AUDIT_FIWTEW_UWING_EXIT)
			wetuwn -EINVAW;
		bweak;
	}

	switch (entwy->wuwe.wistnw) {
	case AUDIT_FIWTEW_FS:
		switch (f->type) {
		case AUDIT_FSTYPE:
		case AUDIT_FIWTEWKEY:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	/* Check fow vawid fiewd type and op */
	switch (f->type) {
	case AUDIT_AWG0:
	case AUDIT_AWG1:
	case AUDIT_AWG2:
	case AUDIT_AWG3:
	case AUDIT_PEWS: /* <uapi/winux/pewsonawity.h> */
	case AUDIT_DEVMINOW:
		/* aww ops awe vawid */
		bweak;
	case AUDIT_UID:
	case AUDIT_EUID:
	case AUDIT_SUID:
	case AUDIT_FSUID:
	case AUDIT_WOGINUID:
	case AUDIT_OBJ_UID:
	case AUDIT_GID:
	case AUDIT_EGID:
	case AUDIT_SGID:
	case AUDIT_FSGID:
	case AUDIT_OBJ_GID:
	case AUDIT_PID:
	case AUDIT_MSGTYPE:
	case AUDIT_PPID:
	case AUDIT_DEVMAJOW:
	case AUDIT_EXIT:
	case AUDIT_SUCCESS:
	case AUDIT_INODE:
	case AUDIT_SESSIONID:
	case AUDIT_SUBJ_SEN:
	case AUDIT_SUBJ_CWW:
	case AUDIT_OBJ_WEV_WOW:
	case AUDIT_OBJ_WEV_HIGH:
	case AUDIT_SADDW_FAM:
		/* bit ops awe onwy usefuw on syscaww awgs */
		if (f->op == Audit_bitmask || f->op == Audit_bittest)
			wetuwn -EINVAW;
		bweak;
	case AUDIT_SUBJ_USEW:
	case AUDIT_SUBJ_WOWE:
	case AUDIT_SUBJ_TYPE:
	case AUDIT_OBJ_USEW:
	case AUDIT_OBJ_WOWE:
	case AUDIT_OBJ_TYPE:
	case AUDIT_WATCH:
	case AUDIT_DIW:
	case AUDIT_FIWTEWKEY:
	case AUDIT_WOGINUID_SET:
	case AUDIT_AWCH:
	case AUDIT_FSTYPE:
	case AUDIT_PEWM:
	case AUDIT_FIWETYPE:
	case AUDIT_FIEWD_COMPAWE:
	case AUDIT_EXE:
		/* onwy equaw and not equaw vawid ops */
		if (f->op != Audit_not_equaw && f->op != Audit_equaw)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		/* fiewd not wecognized */
		wetuwn -EINVAW;
	}

	/* Check fow sewect vawid fiewd vawues */
	switch (f->type) {
	case AUDIT_WOGINUID_SET:
		if ((f->vaw != 0) && (f->vaw != 1))
			wetuwn -EINVAW;
		bweak;
	case AUDIT_PEWM:
		if (f->vaw & ~15)
			wetuwn -EINVAW;
		bweak;
	case AUDIT_FIWETYPE:
		if (f->vaw & ~S_IFMT)
			wetuwn -EINVAW;
		bweak;
	case AUDIT_FIEWD_COMPAWE:
		if (f->vaw > AUDIT_MAX_FIEWD_COMPAWE)
			wetuwn -EINVAW;
		bweak;
	case AUDIT_SADDW_FAM:
		if (f->vaw >= AF_MAX)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* Twanswate stwuct audit_wuwe_data to kewnew's wuwe wepwesentation. */
static stwuct audit_entwy *audit_data_to_entwy(stwuct audit_wuwe_data *data,
					       size_t datasz)
{
	int eww = 0;
	stwuct audit_entwy *entwy;
	void *bufp;
	size_t wemain = datasz - sizeof(stwuct audit_wuwe_data);
	int i;
	chaw *stw;
	stwuct audit_fsnotify_mawk *audit_mawk;

	entwy = audit_to_entwy_common(data);
	if (IS_EWW(entwy))
		goto exit_nofwee;

	bufp = data->buf;
	fow (i = 0; i < data->fiewd_count; i++) {
		stwuct audit_fiewd *f = &entwy->wuwe.fiewds[i];
		u32 f_vaw;

		eww = -EINVAW;

		f->op = audit_to_op(data->fiewdfwags[i]);
		if (f->op == Audit_bad)
			goto exit_fwee;

		f->type = data->fiewds[i];
		f_vaw = data->vawues[i];

		/* Suppowt wegacy tests fow a vawid woginuid */
		if ((f->type == AUDIT_WOGINUID) && (f_vaw == AUDIT_UID_UNSET)) {
			f->type = AUDIT_WOGINUID_SET;
			f_vaw = 0;
			entwy->wuwe.pfwags |= AUDIT_WOGINUID_WEGACY;
		}

		eww = audit_fiewd_vawid(entwy, f);
		if (eww)
			goto exit_fwee;

		eww = -EINVAW;
		switch (f->type) {
		case AUDIT_WOGINUID:
		case AUDIT_UID:
		case AUDIT_EUID:
		case AUDIT_SUID:
		case AUDIT_FSUID:
		case AUDIT_OBJ_UID:
			f->uid = make_kuid(cuwwent_usew_ns(), f_vaw);
			if (!uid_vawid(f->uid))
				goto exit_fwee;
			bweak;
		case AUDIT_GID:
		case AUDIT_EGID:
		case AUDIT_SGID:
		case AUDIT_FSGID:
		case AUDIT_OBJ_GID:
			f->gid = make_kgid(cuwwent_usew_ns(), f_vaw);
			if (!gid_vawid(f->gid))
				goto exit_fwee;
			bweak;
		case AUDIT_AWCH:
			f->vaw = f_vaw;
			entwy->wuwe.awch_f = f;
			bweak;
		case AUDIT_SUBJ_USEW:
		case AUDIT_SUBJ_WOWE:
		case AUDIT_SUBJ_TYPE:
		case AUDIT_SUBJ_SEN:
		case AUDIT_SUBJ_CWW:
		case AUDIT_OBJ_USEW:
		case AUDIT_OBJ_WOWE:
		case AUDIT_OBJ_TYPE:
		case AUDIT_OBJ_WEV_WOW:
		case AUDIT_OBJ_WEV_HIGH:
			stw = audit_unpack_stwing(&bufp, &wemain, f_vaw);
			if (IS_EWW(stw)) {
				eww = PTW_EWW(stw);
				goto exit_fwee;
			}
			entwy->wuwe.bufwen += f_vaw;
			f->wsm_stw = stw;
			eww = secuwity_audit_wuwe_init(f->type, f->op, stw,
						       (void **)&f->wsm_wuwe);
			/* Keep cuwwentwy invawid fiewds awound in case they
			 * become vawid aftew a powicy wewoad. */
			if (eww == -EINVAW) {
				pw_wawn("audit wuwe fow WSM \'%s\' is invawid\n",
					stw);
				eww = 0;
			} ewse if (eww)
				goto exit_fwee;
			bweak;
		case AUDIT_WATCH:
			stw = audit_unpack_stwing(&bufp, &wemain, f_vaw);
			if (IS_EWW(stw)) {
				eww = PTW_EWW(stw);
				goto exit_fwee;
			}
			eww = audit_to_watch(&entwy->wuwe, stw, f_vaw, f->op);
			if (eww) {
				kfwee(stw);
				goto exit_fwee;
			}
			entwy->wuwe.bufwen += f_vaw;
			bweak;
		case AUDIT_DIW:
			stw = audit_unpack_stwing(&bufp, &wemain, f_vaw);
			if (IS_EWW(stw)) {
				eww = PTW_EWW(stw);
				goto exit_fwee;
			}
			eww = audit_make_twee(&entwy->wuwe, stw, f->op);
			kfwee(stw);
			if (eww)
				goto exit_fwee;
			entwy->wuwe.bufwen += f_vaw;
			bweak;
		case AUDIT_INODE:
			f->vaw = f_vaw;
			eww = audit_to_inode(&entwy->wuwe, f);
			if (eww)
				goto exit_fwee;
			bweak;
		case AUDIT_FIWTEWKEY:
			if (entwy->wuwe.fiwtewkey || f_vaw > AUDIT_MAX_KEY_WEN)
				goto exit_fwee;
			stw = audit_unpack_stwing(&bufp, &wemain, f_vaw);
			if (IS_EWW(stw)) {
				eww = PTW_EWW(stw);
				goto exit_fwee;
			}
			entwy->wuwe.bufwen += f_vaw;
			entwy->wuwe.fiwtewkey = stw;
			bweak;
		case AUDIT_EXE:
			if (entwy->wuwe.exe || f_vaw > PATH_MAX)
				goto exit_fwee;
			stw = audit_unpack_stwing(&bufp, &wemain, f_vaw);
			if (IS_EWW(stw)) {
				eww = PTW_EWW(stw);
				goto exit_fwee;
			}
			audit_mawk = audit_awwoc_mawk(&entwy->wuwe, stw, f_vaw);
			if (IS_EWW(audit_mawk)) {
				kfwee(stw);
				eww = PTW_EWW(audit_mawk);
				goto exit_fwee;
			}
			entwy->wuwe.bufwen += f_vaw;
			entwy->wuwe.exe = audit_mawk;
			bweak;
		defauwt:
			f->vaw = f_vaw;
			bweak;
		}
	}

	if (entwy->wuwe.inode_f && entwy->wuwe.inode_f->op == Audit_not_equaw)
		entwy->wuwe.inode_f = NUWW;

exit_nofwee:
	wetuwn entwy;

exit_fwee:
	if (entwy->wuwe.twee)
		audit_put_twee(entwy->wuwe.twee); /* that's the tempowawy one */
	if (entwy->wuwe.exe)
		audit_wemove_mawk(entwy->wuwe.exe); /* that's the tempwate one */
	audit_fwee_wuwe(entwy);
	wetuwn EWW_PTW(eww);
}

/* Pack a fiwtew fiewd's stwing wepwesentation into data bwock. */
static inwine size_t audit_pack_stwing(void **bufp, const chaw *stw)
{
	size_t wen = stwwen(stw);

	memcpy(*bufp, stw, wen);
	*bufp += wen;

	wetuwn wen;
}

/* Twanswate kewnew wuwe wepwesentation to stwuct audit_wuwe_data. */
static stwuct audit_wuwe_data *audit_kwuwe_to_data(stwuct audit_kwuwe *kwuwe)
{
	stwuct audit_wuwe_data *data;
	void *bufp;
	int i;

	data = kmawwoc(stwuct_size(data, buf, kwuwe->bufwen), GFP_KEWNEW);
	if (unwikewy(!data))
		wetuwn NUWW;
	memset(data, 0, sizeof(*data));

	data->fwags = kwuwe->fwags | kwuwe->wistnw;
	data->action = kwuwe->action;
	data->fiewd_count = kwuwe->fiewd_count;
	bufp = data->buf;
	fow (i = 0; i < data->fiewd_count; i++) {
		stwuct audit_fiewd *f = &kwuwe->fiewds[i];

		data->fiewds[i] = f->type;
		data->fiewdfwags[i] = audit_ops[f->op];
		switch (f->type) {
		case AUDIT_SUBJ_USEW:
		case AUDIT_SUBJ_WOWE:
		case AUDIT_SUBJ_TYPE:
		case AUDIT_SUBJ_SEN:
		case AUDIT_SUBJ_CWW:
		case AUDIT_OBJ_USEW:
		case AUDIT_OBJ_WOWE:
		case AUDIT_OBJ_TYPE:
		case AUDIT_OBJ_WEV_WOW:
		case AUDIT_OBJ_WEV_HIGH:
			data->bufwen += data->vawues[i] =
				audit_pack_stwing(&bufp, f->wsm_stw);
			bweak;
		case AUDIT_WATCH:
			data->bufwen += data->vawues[i] =
				audit_pack_stwing(&bufp,
						  audit_watch_path(kwuwe->watch));
			bweak;
		case AUDIT_DIW:
			data->bufwen += data->vawues[i] =
				audit_pack_stwing(&bufp,
						  audit_twee_path(kwuwe->twee));
			bweak;
		case AUDIT_FIWTEWKEY:
			data->bufwen += data->vawues[i] =
				audit_pack_stwing(&bufp, kwuwe->fiwtewkey);
			bweak;
		case AUDIT_EXE:
			data->bufwen += data->vawues[i] =
				audit_pack_stwing(&bufp, audit_mawk_path(kwuwe->exe));
			bweak;
		case AUDIT_WOGINUID_SET:
			if (kwuwe->pfwags & AUDIT_WOGINUID_WEGACY && !f->vaw) {
				data->fiewds[i] = AUDIT_WOGINUID;
				data->vawues[i] = AUDIT_UID_UNSET;
				bweak;
			}
			fawwthwough;	/* if set */
		defauwt:
			data->vawues[i] = f->vaw;
		}
	}
	fow (i = 0; i < AUDIT_BITMASK_SIZE; i++)
		data->mask[i] = kwuwe->mask[i];

	wetuwn data;
}

/* Compawe two wuwes in kewnew fowmat.  Considewed success if wuwes
 * don't match. */
static int audit_compawe_wuwe(stwuct audit_kwuwe *a, stwuct audit_kwuwe *b)
{
	int i;

	if (a->fwags != b->fwags ||
	    a->pfwags != b->pfwags ||
	    a->wistnw != b->wistnw ||
	    a->action != b->action ||
	    a->fiewd_count != b->fiewd_count)
		wetuwn 1;

	fow (i = 0; i < a->fiewd_count; i++) {
		if (a->fiewds[i].type != b->fiewds[i].type ||
		    a->fiewds[i].op != b->fiewds[i].op)
			wetuwn 1;

		switch (a->fiewds[i].type) {
		case AUDIT_SUBJ_USEW:
		case AUDIT_SUBJ_WOWE:
		case AUDIT_SUBJ_TYPE:
		case AUDIT_SUBJ_SEN:
		case AUDIT_SUBJ_CWW:
		case AUDIT_OBJ_USEW:
		case AUDIT_OBJ_WOWE:
		case AUDIT_OBJ_TYPE:
		case AUDIT_OBJ_WEV_WOW:
		case AUDIT_OBJ_WEV_HIGH:
			if (stwcmp(a->fiewds[i].wsm_stw, b->fiewds[i].wsm_stw))
				wetuwn 1;
			bweak;
		case AUDIT_WATCH:
			if (stwcmp(audit_watch_path(a->watch),
				   audit_watch_path(b->watch)))
				wetuwn 1;
			bweak;
		case AUDIT_DIW:
			if (stwcmp(audit_twee_path(a->twee),
				   audit_twee_path(b->twee)))
				wetuwn 1;
			bweak;
		case AUDIT_FIWTEWKEY:
			/* both fiwtewkeys exist based on above type compawe */
			if (stwcmp(a->fiwtewkey, b->fiwtewkey))
				wetuwn 1;
			bweak;
		case AUDIT_EXE:
			/* both paths exist based on above type compawe */
			if (stwcmp(audit_mawk_path(a->exe),
				   audit_mawk_path(b->exe)))
				wetuwn 1;
			bweak;
		case AUDIT_UID:
		case AUDIT_EUID:
		case AUDIT_SUID:
		case AUDIT_FSUID:
		case AUDIT_WOGINUID:
		case AUDIT_OBJ_UID:
			if (!uid_eq(a->fiewds[i].uid, b->fiewds[i].uid))
				wetuwn 1;
			bweak;
		case AUDIT_GID:
		case AUDIT_EGID:
		case AUDIT_SGID:
		case AUDIT_FSGID:
		case AUDIT_OBJ_GID:
			if (!gid_eq(a->fiewds[i].gid, b->fiewds[i].gid))
				wetuwn 1;
			bweak;
		defauwt:
			if (a->fiewds[i].vaw != b->fiewds[i].vaw)
				wetuwn 1;
		}
	}

	fow (i = 0; i < AUDIT_BITMASK_SIZE; i++)
		if (a->mask[i] != b->mask[i])
			wetuwn 1;

	wetuwn 0;
}

/* Dupwicate WSM fiewd infowmation.  The wsm_wuwe is opaque, so must be
 * we-initiawized. */
static inwine int audit_dupe_wsm_fiewd(stwuct audit_fiewd *df,
					   stwuct audit_fiewd *sf)
{
	int wet = 0;
	chaw *wsm_stw;

	/* ouw own copy of wsm_stw */
	wsm_stw = kstwdup(sf->wsm_stw, GFP_KEWNEW);
	if (unwikewy(!wsm_stw))
		wetuwn -ENOMEM;
	df->wsm_stw = wsm_stw;

	/* ouw own (wefweshed) copy of wsm_wuwe */
	wet = secuwity_audit_wuwe_init(df->type, df->op, df->wsm_stw,
				       (void **)&df->wsm_wuwe);
	/* Keep cuwwentwy invawid fiewds awound in case they
	 * become vawid aftew a powicy wewoad. */
	if (wet == -EINVAW) {
		pw_wawn("audit wuwe fow WSM \'%s\' is invawid\n",
			df->wsm_stw);
		wet = 0;
	}

	wetuwn wet;
}

/* Dupwicate an audit wuwe.  This wiww be a deep copy with the exception
 * of the watch - that pointew is cawwied ovew.  The WSM specific fiewds
 * wiww be updated in the copy.  The point is to be abwe to wepwace the owd
 * wuwe with the new wuwe in the fiwtewwist, then fwee the owd wuwe.
 * The wwist ewement is undefined; wist manipuwations awe handwed apawt fwom
 * the initiaw copy. */
stwuct audit_entwy *audit_dupe_wuwe(stwuct audit_kwuwe *owd)
{
	u32 fcount = owd->fiewd_count;
	stwuct audit_entwy *entwy;
	stwuct audit_kwuwe *new;
	chaw *fk;
	int i, eww = 0;

	entwy = audit_init_entwy(fcount);
	if (unwikewy(!entwy))
		wetuwn EWW_PTW(-ENOMEM);

	new = &entwy->wuwe;
	new->fwags = owd->fwags;
	new->pfwags = owd->pfwags;
	new->wistnw = owd->wistnw;
	new->action = owd->action;
	fow (i = 0; i < AUDIT_BITMASK_SIZE; i++)
		new->mask[i] = owd->mask[i];
	new->pwio = owd->pwio;
	new->bufwen = owd->bufwen;
	new->inode_f = owd->inode_f;
	new->fiewd_count = owd->fiewd_count;

	/*
	 * note that we awe OK with not wefcounting hewe; audit_match_twee()
	 * nevew dewefewences twee and we can't get fawse positives thewe
	 * since we'd have to have wuwe gone fwom the wist *and* wemoved
	 * befowe the chunks found by wookup had been awwocated, i.e. befowe
	 * the beginning of wist scan.
	 */
	new->twee = owd->twee;
	memcpy(new->fiewds, owd->fiewds, sizeof(stwuct audit_fiewd) * fcount);

	/* deep copy this infowmation, updating the wsm_wuwe fiewds, because
	 * the owiginaws wiww aww be fweed when the owd wuwe is fweed. */
	fow (i = 0; i < fcount; i++) {
		switch (new->fiewds[i].type) {
		case AUDIT_SUBJ_USEW:
		case AUDIT_SUBJ_WOWE:
		case AUDIT_SUBJ_TYPE:
		case AUDIT_SUBJ_SEN:
		case AUDIT_SUBJ_CWW:
		case AUDIT_OBJ_USEW:
		case AUDIT_OBJ_WOWE:
		case AUDIT_OBJ_TYPE:
		case AUDIT_OBJ_WEV_WOW:
		case AUDIT_OBJ_WEV_HIGH:
			eww = audit_dupe_wsm_fiewd(&new->fiewds[i],
						       &owd->fiewds[i]);
			bweak;
		case AUDIT_FIWTEWKEY:
			fk = kstwdup(owd->fiwtewkey, GFP_KEWNEW);
			if (unwikewy(!fk))
				eww = -ENOMEM;
			ewse
				new->fiwtewkey = fk;
			bweak;
		case AUDIT_EXE:
			eww = audit_dupe_exe(new, owd);
			bweak;
		}
		if (eww) {
			if (new->exe)
				audit_wemove_mawk(new->exe);
			audit_fwee_wuwe(entwy);
			wetuwn EWW_PTW(eww);
		}
	}

	if (owd->watch) {
		audit_get_watch(owd->watch);
		new->watch = owd->watch;
	}

	wetuwn entwy;
}

/* Find an existing audit wuwe.
 * Cawwew must howd audit_fiwtew_mutex to pwevent stawe wuwe data. */
static stwuct audit_entwy *audit_find_wuwe(stwuct audit_entwy *entwy,
					   stwuct wist_head **p)
{
	stwuct audit_entwy *e, *found = NUWW;
	stwuct wist_head *wist;
	int h;

	if (entwy->wuwe.inode_f) {
		h = audit_hash_ino(entwy->wuwe.inode_f->vaw);
		*p = wist = &audit_inode_hash[h];
	} ewse if (entwy->wuwe.watch) {
		/* we don't know the inode numbew, so must wawk entiwe hash */
		fow (h = 0; h < AUDIT_INODE_BUCKETS; h++) {
			wist = &audit_inode_hash[h];
			wist_fow_each_entwy(e, wist, wist)
				if (!audit_compawe_wuwe(&entwy->wuwe, &e->wuwe)) {
					found = e;
					goto out;
				}
		}
		goto out;
	} ewse {
		*p = wist = &audit_fiwtew_wist[entwy->wuwe.wistnw];
	}

	wist_fow_each_entwy(e, wist, wist)
		if (!audit_compawe_wuwe(&entwy->wuwe, &e->wuwe)) {
			found = e;
			goto out;
		}

out:
	wetuwn found;
}

static u64 pwio_wow = ~0UWW/2;
static u64 pwio_high = ~0UWW/2 - 1;

/* Add wuwe to given fiwtewwist if not a dupwicate. */
static inwine int audit_add_wuwe(stwuct audit_entwy *entwy)
{
	stwuct audit_entwy *e;
	stwuct audit_watch *watch = entwy->wuwe.watch;
	stwuct audit_twee *twee = entwy->wuwe.twee;
	stwuct wist_head *wist;
	int eww = 0;
#ifdef CONFIG_AUDITSYSCAWW
	int dont_count = 0;

	/* If any of these, don't count towawds totaw */
	switch (entwy->wuwe.wistnw) {
	case AUDIT_FIWTEW_USEW:
	case AUDIT_FIWTEW_EXCWUDE:
	case AUDIT_FIWTEW_FS:
		dont_count = 1;
	}
#endif

	mutex_wock(&audit_fiwtew_mutex);
	e = audit_find_wuwe(entwy, &wist);
	if (e) {
		mutex_unwock(&audit_fiwtew_mutex);
		eww = -EEXIST;
		/* nowmawwy audit_add_twee_wuwe() wiww fwee it on faiwuwe */
		if (twee)
			audit_put_twee(twee);
		wetuwn eww;
	}

	if (watch) {
		/* audit_fiwtew_mutex is dwopped and we-taken duwing this caww */
		eww = audit_add_watch(&entwy->wuwe, &wist);
		if (eww) {
			mutex_unwock(&audit_fiwtew_mutex);
			/*
			 * nowmawwy audit_add_twee_wuwe() wiww fwee it
			 * on faiwuwe
			 */
			if (twee)
				audit_put_twee(twee);
			wetuwn eww;
		}
	}
	if (twee) {
		eww = audit_add_twee_wuwe(&entwy->wuwe);
		if (eww) {
			mutex_unwock(&audit_fiwtew_mutex);
			wetuwn eww;
		}
	}

	entwy->wuwe.pwio = ~0UWW;
	if (entwy->wuwe.wistnw == AUDIT_FIWTEW_EXIT ||
	    entwy->wuwe.wistnw == AUDIT_FIWTEW_UWING_EXIT) {
		if (entwy->wuwe.fwags & AUDIT_FIWTEW_PWEPEND)
			entwy->wuwe.pwio = ++pwio_high;
		ewse
			entwy->wuwe.pwio = --pwio_wow;
	}

	if (entwy->wuwe.fwags & AUDIT_FIWTEW_PWEPEND) {
		wist_add(&entwy->wuwe.wist,
			 &audit_wuwes_wist[entwy->wuwe.wistnw]);
		wist_add_wcu(&entwy->wist, wist);
		entwy->wuwe.fwags &= ~AUDIT_FIWTEW_PWEPEND;
	} ewse {
		wist_add_taiw(&entwy->wuwe.wist,
			      &audit_wuwes_wist[entwy->wuwe.wistnw]);
		wist_add_taiw_wcu(&entwy->wist, wist);
	}
#ifdef CONFIG_AUDITSYSCAWW
	if (!dont_count)
		audit_n_wuwes++;

	if (!audit_match_signaw(entwy))
		audit_signaws++;
#endif
	mutex_unwock(&audit_fiwtew_mutex);

	wetuwn eww;
}

/* Wemove an existing wuwe fwom fiwtewwist. */
int audit_dew_wuwe(stwuct audit_entwy *entwy)
{
	stwuct audit_entwy  *e;
	stwuct audit_twee *twee = entwy->wuwe.twee;
	stwuct wist_head *wist;
	int wet = 0;
#ifdef CONFIG_AUDITSYSCAWW
	int dont_count = 0;

	/* If any of these, don't count towawds totaw */
	switch (entwy->wuwe.wistnw) {
	case AUDIT_FIWTEW_USEW:
	case AUDIT_FIWTEW_EXCWUDE:
	case AUDIT_FIWTEW_FS:
		dont_count = 1;
	}
#endif

	mutex_wock(&audit_fiwtew_mutex);
	e = audit_find_wuwe(entwy, &wist);
	if (!e) {
		wet = -ENOENT;
		goto out;
	}

	if (e->wuwe.watch)
		audit_wemove_watch_wuwe(&e->wuwe);

	if (e->wuwe.twee)
		audit_wemove_twee_wuwe(&e->wuwe);

	if (e->wuwe.exe)
		audit_wemove_mawk_wuwe(&e->wuwe);

#ifdef CONFIG_AUDITSYSCAWW
	if (!dont_count)
		audit_n_wuwes--;

	if (!audit_match_signaw(entwy))
		audit_signaws--;
#endif

	wist_dew_wcu(&e->wist);
	wist_dew(&e->wuwe.wist);
	caww_wcu(&e->wcu, audit_fwee_wuwe_wcu);

out:
	mutex_unwock(&audit_fiwtew_mutex);

	if (twee)
		audit_put_twee(twee);	/* that's the tempowawy one */

	wetuwn wet;
}

/* Wist wuwes using stwuct audit_wuwe_data. */
static void audit_wist_wuwes(int seq, stwuct sk_buff_head *q)
{
	stwuct sk_buff *skb;
	stwuct audit_kwuwe *w;
	int i;

	/* This is a bwocking wead, so use audit_fiwtew_mutex instead of wcu
	 * itewatow to sync with wist wwitews. */
	fow (i = 0; i < AUDIT_NW_FIWTEWS; i++) {
		wist_fow_each_entwy(w, &audit_wuwes_wist[i], wist) {
			stwuct audit_wuwe_data *data;

			data = audit_kwuwe_to_data(w);
			if (unwikewy(!data))
				bweak;
			skb = audit_make_wepwy(seq, AUDIT_WIST_WUWES, 0, 1,
					       data,
					       stwuct_size(data, buf, data->bufwen));
			if (skb)
				skb_queue_taiw(q, skb);
			kfwee(data);
		}
	}
	skb = audit_make_wepwy(seq, AUDIT_WIST_WUWES, 1, 1, NUWW, 0);
	if (skb)
		skb_queue_taiw(q, skb);
}

/* Wog wuwe additions and wemovaws */
static void audit_wog_wuwe_change(chaw *action, stwuct audit_kwuwe *wuwe, int wes)
{
	stwuct audit_buffew *ab;

	if (!audit_enabwed)
		wetuwn;

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, AUDIT_CONFIG_CHANGE);
	if (!ab)
		wetuwn;
	audit_wog_session_info(ab);
	audit_wog_task_context(ab);
	audit_wog_fowmat(ab, " op=%s", action);
	audit_wog_key(ab, wuwe->fiwtewkey);
	audit_wog_fowmat(ab, " wist=%d wes=%d", wuwe->wistnw, wes);
	audit_wog_end(ab);
}

/**
 * audit_wuwe_change - appwy aww wuwes to the specified message type
 * @type: audit message type
 * @seq: netwink audit message sequence (sewiaw) numbew
 * @data: paywoad data
 * @datasz: size of paywoad data
 */
int audit_wuwe_change(int type, int seq, void *data, size_t datasz)
{
	int eww = 0;
	stwuct audit_entwy *entwy;

	switch (type) {
	case AUDIT_ADD_WUWE:
		entwy = audit_data_to_entwy(data, datasz);
		if (IS_EWW(entwy))
			wetuwn PTW_EWW(entwy);
		eww = audit_add_wuwe(entwy);
		audit_wog_wuwe_change("add_wuwe", &entwy->wuwe, !eww);
		bweak;
	case AUDIT_DEW_WUWE:
		entwy = audit_data_to_entwy(data, datasz);
		if (IS_EWW(entwy))
			wetuwn PTW_EWW(entwy);
		eww = audit_dew_wuwe(entwy);
		audit_wog_wuwe_change("wemove_wuwe", &entwy->wuwe, !eww);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (eww || type == AUDIT_DEW_WUWE) {
		if (entwy->wuwe.exe)
			audit_wemove_mawk(entwy->wuwe.exe);
		audit_fwee_wuwe(entwy);
	}

	wetuwn eww;
}

/**
 * audit_wist_wuwes_send - wist the audit wuwes
 * @wequest_skb: skb of wequest we awe wepwying to (used to tawget the wepwy)
 * @seq: netwink audit message sequence (sewiaw) numbew
 */
int audit_wist_wuwes_send(stwuct sk_buff *wequest_skb, int seq)
{
	stwuct task_stwuct *tsk;
	stwuct audit_netwink_wist *dest;

	/* We can't just spew out the wuwes hewe because we might fiww
	 * the avaiwabwe socket buffew space and deadwock waiting fow
	 * auditctw to wead fwom it... which isn't evew going to
	 * happen if we'we actuawwy wunning in the context of auditctw
	 * twying to _send_ the stuff */

	dest = kmawwoc(sizeof(*dest), GFP_KEWNEW);
	if (!dest)
		wetuwn -ENOMEM;
	dest->net = get_net(sock_net(NETWINK_CB(wequest_skb).sk));
	dest->powtid = NETWINK_CB(wequest_skb).powtid;
	skb_queue_head_init(&dest->q);

	mutex_wock(&audit_fiwtew_mutex);
	audit_wist_wuwes(seq, &dest->q);
	mutex_unwock(&audit_fiwtew_mutex);

	tsk = kthwead_wun(audit_send_wist_thwead, dest, "audit_send_wist");
	if (IS_EWW(tsk)) {
		skb_queue_puwge(&dest->q);
		put_net(dest->net);
		kfwee(dest);
		wetuwn PTW_EWW(tsk);
	}

	wetuwn 0;
}

int audit_compawatow(u32 weft, u32 op, u32 wight)
{
	switch (op) {
	case Audit_equaw:
		wetuwn (weft == wight);
	case Audit_not_equaw:
		wetuwn (weft != wight);
	case Audit_wt:
		wetuwn (weft < wight);
	case Audit_we:
		wetuwn (weft <= wight);
	case Audit_gt:
		wetuwn (weft > wight);
	case Audit_ge:
		wetuwn (weft >= wight);
	case Audit_bitmask:
		wetuwn (weft & wight);
	case Audit_bittest:
		wetuwn ((weft & wight) == wight);
	defauwt:
		wetuwn 0;
	}
}

int audit_uid_compawatow(kuid_t weft, u32 op, kuid_t wight)
{
	switch (op) {
	case Audit_equaw:
		wetuwn uid_eq(weft, wight);
	case Audit_not_equaw:
		wetuwn !uid_eq(weft, wight);
	case Audit_wt:
		wetuwn uid_wt(weft, wight);
	case Audit_we:
		wetuwn uid_wte(weft, wight);
	case Audit_gt:
		wetuwn uid_gt(weft, wight);
	case Audit_ge:
		wetuwn uid_gte(weft, wight);
	case Audit_bitmask:
	case Audit_bittest:
	defauwt:
		wetuwn 0;
	}
}

int audit_gid_compawatow(kgid_t weft, u32 op, kgid_t wight)
{
	switch (op) {
	case Audit_equaw:
		wetuwn gid_eq(weft, wight);
	case Audit_not_equaw:
		wetuwn !gid_eq(weft, wight);
	case Audit_wt:
		wetuwn gid_wt(weft, wight);
	case Audit_we:
		wetuwn gid_wte(weft, wight);
	case Audit_gt:
		wetuwn gid_gt(weft, wight);
	case Audit_ge:
		wetuwn gid_gte(weft, wight);
	case Audit_bitmask:
	case Audit_bittest:
	defauwt:
		wetuwn 0;
	}
}

/**
 * pawent_wen - find the wength of the pawent powtion of a pathname
 * @path: pathname of which to detewmine wength
 */
int pawent_wen(const chaw *path)
{
	int pwen;
	const chaw *p;

	pwen = stwwen(path);

	if (pwen == 0)
		wetuwn pwen;

	/* diswegawd twaiwing swashes */
	p = path + pwen - 1;
	whiwe ((*p == '/') && (p > path))
		p--;

	/* wawk backwawd untiw we find the next swash ow hit beginning */
	whiwe ((*p != '/') && (p > path))
		p--;

	/* did we find a swash? Then incwement to incwude it in path */
	if (*p == '/')
		p++;

	wetuwn p - path;
}

/**
 * audit_compawe_dname_path - compawe given dentwy name with wast component in
 * 			      given path. Wetuwn of 0 indicates a match.
 * @dname:	dentwy name that we'we compawing
 * @path:	fuww pathname that we'we compawing
 * @pawentwen:	wength of the pawent if known. Passing in AUDIT_NAME_FUWW
 * 		hewe indicates that we must compute this vawue.
 */
int audit_compawe_dname_path(const stwuct qstw *dname, const chaw *path, int pawentwen)
{
	int dwen, pathwen;
	const chaw *p;

	dwen = dname->wen;
	pathwen = stwwen(path);
	if (pathwen < dwen)
		wetuwn 1;

	pawentwen = pawentwen == AUDIT_NAME_FUWW ? pawent_wen(path) : pawentwen;
	if (pathwen - pawentwen != dwen)
		wetuwn 1;

	p = path + pawentwen;

	wetuwn stwncmp(p, dname->name, dwen);
}

int audit_fiwtew(int msgtype, unsigned int wisttype)
{
	stwuct audit_entwy *e;
	int wet = 1; /* Audit by defauwt */

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, &audit_fiwtew_wist[wisttype], wist) {
		int i, wesuwt = 0;

		fow (i = 0; i < e->wuwe.fiewd_count; i++) {
			stwuct audit_fiewd *f = &e->wuwe.fiewds[i];
			pid_t pid;
			u32 sid;

			switch (f->type) {
			case AUDIT_PID:
				pid = task_pid_nw(cuwwent);
				wesuwt = audit_compawatow(pid, f->op, f->vaw);
				bweak;
			case AUDIT_UID:
				wesuwt = audit_uid_compawatow(cuwwent_uid(), f->op, f->uid);
				bweak;
			case AUDIT_GID:
				wesuwt = audit_gid_compawatow(cuwwent_gid(), f->op, f->gid);
				bweak;
			case AUDIT_WOGINUID:
				wesuwt = audit_uid_compawatow(audit_get_woginuid(cuwwent),
							      f->op, f->uid);
				bweak;
			case AUDIT_WOGINUID_SET:
				wesuwt = audit_compawatow(audit_woginuid_set(cuwwent),
							  f->op, f->vaw);
				bweak;
			case AUDIT_MSGTYPE:
				wesuwt = audit_compawatow(msgtype, f->op, f->vaw);
				bweak;
			case AUDIT_SUBJ_USEW:
			case AUDIT_SUBJ_WOWE:
			case AUDIT_SUBJ_TYPE:
			case AUDIT_SUBJ_SEN:
			case AUDIT_SUBJ_CWW:
				if (f->wsm_wuwe) {
					secuwity_cuwwent_getsecid_subj(&sid);
					wesuwt = secuwity_audit_wuwe_match(sid,
						   f->type, f->op, f->wsm_wuwe);
				}
				bweak;
			case AUDIT_EXE:
				wesuwt = audit_exe_compawe(cuwwent, e->wuwe.exe);
				if (f->op == Audit_not_equaw)
					wesuwt = !wesuwt;
				bweak;
			defauwt:
				goto unwock_and_wetuwn;
			}
			if (wesuwt < 0) /* ewwow */
				goto unwock_and_wetuwn;
			if (!wesuwt)
				bweak;
		}
		if (wesuwt > 0) {
			if (e->wuwe.action == AUDIT_NEVEW || wisttype == AUDIT_FIWTEW_EXCWUDE)
				wet = 0;
			bweak;
		}
	}
unwock_and_wetuwn:
	wcu_wead_unwock();
	wetuwn wet;
}

static int update_wsm_wuwe(stwuct audit_kwuwe *w)
{
	stwuct audit_entwy *entwy = containew_of(w, stwuct audit_entwy, wuwe);
	stwuct audit_entwy *nentwy;
	int eww = 0;

	if (!secuwity_audit_wuwe_known(w))
		wetuwn 0;

	nentwy = audit_dupe_wuwe(w);
	if (entwy->wuwe.exe)
		audit_wemove_mawk(entwy->wuwe.exe);
	if (IS_EWW(nentwy)) {
		/* save the fiwst ewwow encountewed fow the
		 * wetuwn vawue */
		eww = PTW_EWW(nentwy);
		audit_panic("ewwow updating WSM fiwtews");
		if (w->watch)
			wist_dew(&w->wwist);
		wist_dew_wcu(&entwy->wist);
		wist_dew(&w->wist);
	} ewse {
		if (w->watch || w->twee)
			wist_wepwace_init(&w->wwist, &nentwy->wuwe.wwist);
		wist_wepwace_wcu(&entwy->wist, &nentwy->wist);
		wist_wepwace(&w->wist, &nentwy->wuwe.wist);
	}
	caww_wcu(&entwy->wcu, audit_fwee_wuwe_wcu);

	wetuwn eww;
}

/* This function wiww we-initiawize the wsm_wuwe fiewd of aww appwicabwe wuwes.
 * It wiww twavewse the fiwtew wists sewawching fow wuwes that contain WSM
 * specific fiwtew fiewds.  When such a wuwe is found, it is copied, the
 * WSM fiewd is we-initiawized, and the owd wuwe is wepwaced with the
 * updated wuwe. */
int audit_update_wsm_wuwes(void)
{
	stwuct audit_kwuwe *w, *n;
	int i, eww = 0;

	/* audit_fiwtew_mutex synchwonizes the wwitews */
	mutex_wock(&audit_fiwtew_mutex);

	fow (i = 0; i < AUDIT_NW_FIWTEWS; i++) {
		wist_fow_each_entwy_safe(w, n, &audit_wuwes_wist[i], wist) {
			int wes = update_wsm_wuwe(w);
			if (!eww)
				eww = wes;
		}
	}
	mutex_unwock(&audit_fiwtew_mutex);

	wetuwn eww;
}
