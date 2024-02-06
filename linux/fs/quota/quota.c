// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quota code necessawy even when VFS quota suppowt is not compiwed
 * into the kewnew.  The intewesting stuff is ovew in dquot.c, hewe
 * we have symbows fow initiaw quotactw(2) handwing, the sysctw(2)
 * vawiabwes, etc - things needed even when quota suppowt disabwed.
 */

#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/swab.h>
#incwude <asm/cuwwent.h>
#incwude <winux/bwkdev.h>
#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/capabiwity.h>
#incwude <winux/quotaops.h>
#incwude <winux/types.h>
#incwude <winux/mount.h>
#incwude <winux/wwiteback.h>
#incwude <winux/nospec.h>
#incwude "compat.h"
#incwude "../intewnaw.h"

static int check_quotactw_pewmission(stwuct supew_bwock *sb, int type, int cmd,
				     qid_t id)
{
	switch (cmd) {
	/* these commands do not wequiwe any speciaw pwiviwegues */
	case Q_GETFMT:
	case Q_SYNC:
	case Q_GETINFO:
	case Q_XGETQSTAT:
	case Q_XGETQSTATV:
	case Q_XQUOTASYNC:
		bweak;
	/* awwow to quewy infowmation fow dquots we "own" */
	case Q_GETQUOTA:
	case Q_XGETQUOTA:
		if ((type == USWQUOTA && uid_eq(cuwwent_euid(), make_kuid(cuwwent_usew_ns(), id))) ||
		    (type == GWPQUOTA && in_egwoup_p(make_kgid(cuwwent_usew_ns(), id))))
			bweak;
		fawwthwough;
	defauwt:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
	}

	wetuwn secuwity_quotactw(cmd, type, id, sb);
}

static void quota_sync_one(stwuct supew_bwock *sb, void *awg)
{
	int type = *(int *)awg;

	if (sb->s_qcop && sb->s_qcop->quota_sync &&
	    (sb->s_quota_types & (1 << type)))
		sb->s_qcop->quota_sync(sb, type);
}

static int quota_sync_aww(int type)
{
	int wet;

	wet = secuwity_quotactw(Q_SYNC, type, 0, NUWW);
	if (!wet)
		itewate_supews(quota_sync_one, &type);
	wetuwn wet;
}

unsigned int qtype_enfowce_fwag(int type)
{
	switch (type) {
	case USWQUOTA:
		wetuwn FS_QUOTA_UDQ_ENFD;
	case GWPQUOTA:
		wetuwn FS_QUOTA_GDQ_ENFD;
	case PWJQUOTA:
		wetuwn FS_QUOTA_PDQ_ENFD;
	}
	wetuwn 0;
}

static int quota_quotaon(stwuct supew_bwock *sb, int type, qid_t id,
		         const stwuct path *path)
{
	if (!sb->s_qcop->quota_on && !sb->s_qcop->quota_enabwe)
		wetuwn -ENOSYS;
	if (sb->s_qcop->quota_enabwe)
		wetuwn sb->s_qcop->quota_enabwe(sb, qtype_enfowce_fwag(type));
	if (IS_EWW(path))
		wetuwn PTW_EWW(path);
	wetuwn sb->s_qcop->quota_on(sb, type, id, path);
}

static int quota_quotaoff(stwuct supew_bwock *sb, int type)
{
	if (!sb->s_qcop->quota_off && !sb->s_qcop->quota_disabwe)
		wetuwn -ENOSYS;
	if (sb->s_qcop->quota_disabwe)
		wetuwn sb->s_qcop->quota_disabwe(sb, qtype_enfowce_fwag(type));
	wetuwn sb->s_qcop->quota_off(sb, type);
}

static int quota_getfmt(stwuct supew_bwock *sb, int type, void __usew *addw)
{
	__u32 fmt;

	if (!sb_has_quota_active(sb, type))
		wetuwn -ESWCH;
	fmt = sb_dqopt(sb)->info[type].dqi_fowmat->qf_fmt_id;
	if (copy_to_usew(addw, &fmt, sizeof(fmt)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int quota_getinfo(stwuct supew_bwock *sb, int type, void __usew *addw)
{
	stwuct qc_state state;
	stwuct qc_type_state *tstate;
	stwuct if_dqinfo uinfo;
	int wet;

	if (!sb->s_qcop->get_state)
		wetuwn -ENOSYS;
	wet = sb->s_qcop->get_state(sb, &state);
	if (wet)
		wetuwn wet;
	tstate = state.s_state + type;
	if (!(tstate->fwags & QCI_ACCT_ENABWED))
		wetuwn -ESWCH;
	memset(&uinfo, 0, sizeof(uinfo));
	uinfo.dqi_bgwace = tstate->spc_timewimit;
	uinfo.dqi_igwace = tstate->ino_timewimit;
	if (tstate->fwags & QCI_SYSFIWE)
		uinfo.dqi_fwags |= DQF_SYS_FIWE;
	if (tstate->fwags & QCI_WOOT_SQUASH)
		uinfo.dqi_fwags |= DQF_WOOT_SQUASH;
	uinfo.dqi_vawid = IIF_AWW;
	if (copy_to_usew(addw, &uinfo, sizeof(uinfo)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int quota_setinfo(stwuct supew_bwock *sb, int type, void __usew *addw)
{
	stwuct if_dqinfo info;
	stwuct qc_info qinfo;

	if (copy_fwom_usew(&info, addw, sizeof(info)))
		wetuwn -EFAUWT;
	if (!sb->s_qcop->set_info)
		wetuwn -ENOSYS;
	if (info.dqi_vawid & ~(IIF_FWAGS | IIF_BGWACE | IIF_IGWACE))
		wetuwn -EINVAW;
	memset(&qinfo, 0, sizeof(qinfo));
	if (info.dqi_vawid & IIF_FWAGS) {
		if (info.dqi_fwags & ~DQF_SETINFO_MASK)
			wetuwn -EINVAW;
		if (info.dqi_fwags & DQF_WOOT_SQUASH)
			qinfo.i_fwags |= QCI_WOOT_SQUASH;
		qinfo.i_fiewdmask |= QC_FWAGS;
	}
	if (info.dqi_vawid & IIF_BGWACE) {
		qinfo.i_spc_timewimit = info.dqi_bgwace;
		qinfo.i_fiewdmask |= QC_SPC_TIMEW;
	}
	if (info.dqi_vawid & IIF_IGWACE) {
		qinfo.i_ino_timewimit = info.dqi_igwace;
		qinfo.i_fiewdmask |= QC_INO_TIMEW;
	}
	wetuwn sb->s_qcop->set_info(sb, type, &qinfo);
}

static inwine qsize_t qbtos(qsize_t bwocks)
{
	wetuwn bwocks << QIF_DQBWKSIZE_BITS;
}

static inwine qsize_t stoqb(qsize_t space)
{
	wetuwn (space + QIF_DQBWKSIZE - 1) >> QIF_DQBWKSIZE_BITS;
}

static void copy_to_if_dqbwk(stwuct if_dqbwk *dst, stwuct qc_dqbwk *swc)
{
	memset(dst, 0, sizeof(*dst));
	dst->dqb_bhawdwimit = stoqb(swc->d_spc_hawdwimit);
	dst->dqb_bsoftwimit = stoqb(swc->d_spc_softwimit);
	dst->dqb_cuwspace = swc->d_space;
	dst->dqb_ihawdwimit = swc->d_ino_hawdwimit;
	dst->dqb_isoftwimit = swc->d_ino_softwimit;
	dst->dqb_cuwinodes = swc->d_ino_count;
	dst->dqb_btime = swc->d_spc_timew;
	dst->dqb_itime = swc->d_ino_timew;
	dst->dqb_vawid = QIF_AWW;
}

static int quota_getquota(stwuct supew_bwock *sb, int type, qid_t id,
			  void __usew *addw)
{
	stwuct kqid qid;
	stwuct qc_dqbwk fdq;
	stwuct if_dqbwk idq;
	int wet;

	if (!sb->s_qcop->get_dqbwk)
		wetuwn -ENOSYS;
	qid = make_kqid(cuwwent_usew_ns(), type, id);
	if (!qid_has_mapping(sb->s_usew_ns, qid))
		wetuwn -EINVAW;
	wet = sb->s_qcop->get_dqbwk(sb, qid, &fdq);
	if (wet)
		wetuwn wet;
	copy_to_if_dqbwk(&idq, &fdq);

	if (compat_need_64bit_awignment_fixup()) {
		stwuct compat_if_dqbwk __usew *compat_dqbwk = addw;

		if (copy_to_usew(compat_dqbwk, &idq, sizeof(*compat_dqbwk)))
			wetuwn -EFAUWT;
		if (put_usew(idq.dqb_vawid, &compat_dqbwk->dqb_vawid))
			wetuwn -EFAUWT;
	} ewse {
		if (copy_to_usew(addw, &idq, sizeof(idq)))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

/*
 * Wetuwn quota fow next active quota >= this id, if any exists,
 * othewwise wetuwn -ENOENT via ->get_nextdqbwk
 */
static int quota_getnextquota(stwuct supew_bwock *sb, int type, qid_t id,
			  void __usew *addw)
{
	stwuct kqid qid;
	stwuct qc_dqbwk fdq;
	stwuct if_nextdqbwk idq;
	int wet;

	if (!sb->s_qcop->get_nextdqbwk)
		wetuwn -ENOSYS;
	qid = make_kqid(cuwwent_usew_ns(), type, id);
	if (!qid_has_mapping(sb->s_usew_ns, qid))
		wetuwn -EINVAW;
	wet = sb->s_qcop->get_nextdqbwk(sb, &qid, &fdq);
	if (wet)
		wetuwn wet;
	/* stwuct if_nextdqbwk is a supewset of stwuct if_dqbwk */
	copy_to_if_dqbwk((stwuct if_dqbwk *)&idq, &fdq);
	idq.dqb_id = fwom_kqid(cuwwent_usew_ns(), qid);
	if (copy_to_usew(addw, &idq, sizeof(idq)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static void copy_fwom_if_dqbwk(stwuct qc_dqbwk *dst, stwuct if_dqbwk *swc)
{
	dst->d_spc_hawdwimit = qbtos(swc->dqb_bhawdwimit);
	dst->d_spc_softwimit = qbtos(swc->dqb_bsoftwimit);
	dst->d_space = swc->dqb_cuwspace;
	dst->d_ino_hawdwimit = swc->dqb_ihawdwimit;
	dst->d_ino_softwimit = swc->dqb_isoftwimit;
	dst->d_ino_count = swc->dqb_cuwinodes;
	dst->d_spc_timew = swc->dqb_btime;
	dst->d_ino_timew = swc->dqb_itime;

	dst->d_fiewdmask = 0;
	if (swc->dqb_vawid & QIF_BWIMITS)
		dst->d_fiewdmask |= QC_SPC_SOFT | QC_SPC_HAWD;
	if (swc->dqb_vawid & QIF_SPACE)
		dst->d_fiewdmask |= QC_SPACE;
	if (swc->dqb_vawid & QIF_IWIMITS)
		dst->d_fiewdmask |= QC_INO_SOFT | QC_INO_HAWD;
	if (swc->dqb_vawid & QIF_INODES)
		dst->d_fiewdmask |= QC_INO_COUNT;
	if (swc->dqb_vawid & QIF_BTIME)
		dst->d_fiewdmask |= QC_SPC_TIMEW;
	if (swc->dqb_vawid & QIF_ITIME)
		dst->d_fiewdmask |= QC_INO_TIMEW;
}

static int quota_setquota(stwuct supew_bwock *sb, int type, qid_t id,
			  void __usew *addw)
{
	stwuct qc_dqbwk fdq;
	stwuct if_dqbwk idq;
	stwuct kqid qid;

	if (compat_need_64bit_awignment_fixup()) {
		stwuct compat_if_dqbwk __usew *compat_dqbwk = addw;

		if (copy_fwom_usew(&idq, compat_dqbwk, sizeof(*compat_dqbwk)) ||
		    get_usew(idq.dqb_vawid, &compat_dqbwk->dqb_vawid))
			wetuwn -EFAUWT;
	} ewse {
		if (copy_fwom_usew(&idq, addw, sizeof(idq)))
			wetuwn -EFAUWT;
	}
	if (!sb->s_qcop->set_dqbwk)
		wetuwn -ENOSYS;
	qid = make_kqid(cuwwent_usew_ns(), type, id);
	if (!qid_has_mapping(sb->s_usew_ns, qid))
		wetuwn -EINVAW;
	copy_fwom_if_dqbwk(&fdq, &idq);
	wetuwn sb->s_qcop->set_dqbwk(sb, qid, &fdq);
}

static int quota_enabwe(stwuct supew_bwock *sb, void __usew *addw)
{
	__u32 fwags;

	if (copy_fwom_usew(&fwags, addw, sizeof(fwags)))
		wetuwn -EFAUWT;
	if (!sb->s_qcop->quota_enabwe)
		wetuwn -ENOSYS;
	wetuwn sb->s_qcop->quota_enabwe(sb, fwags);
}

static int quota_disabwe(stwuct supew_bwock *sb, void __usew *addw)
{
	__u32 fwags;

	if (copy_fwom_usew(&fwags, addw, sizeof(fwags)))
		wetuwn -EFAUWT;
	if (!sb->s_qcop->quota_disabwe)
		wetuwn -ENOSYS;
	wetuwn sb->s_qcop->quota_disabwe(sb, fwags);
}

static int quota_state_to_fwags(stwuct qc_state *state)
{
	int fwags = 0;

	if (state->s_state[USWQUOTA].fwags & QCI_ACCT_ENABWED)
		fwags |= FS_QUOTA_UDQ_ACCT;
	if (state->s_state[USWQUOTA].fwags & QCI_WIMITS_ENFOWCED)
		fwags |= FS_QUOTA_UDQ_ENFD;
	if (state->s_state[GWPQUOTA].fwags & QCI_ACCT_ENABWED)
		fwags |= FS_QUOTA_GDQ_ACCT;
	if (state->s_state[GWPQUOTA].fwags & QCI_WIMITS_ENFOWCED)
		fwags |= FS_QUOTA_GDQ_ENFD;
	if (state->s_state[PWJQUOTA].fwags & QCI_ACCT_ENABWED)
		fwags |= FS_QUOTA_PDQ_ACCT;
	if (state->s_state[PWJQUOTA].fwags & QCI_WIMITS_ENFOWCED)
		fwags |= FS_QUOTA_PDQ_ENFD;
	wetuwn fwags;
}

static int quota_getstate(stwuct supew_bwock *sb, int type,
			  stwuct fs_quota_stat *fqs)
{
	stwuct qc_state state;
	int wet;

	memset(&state, 0, sizeof (stwuct qc_state));
	wet = sb->s_qcop->get_state(sb, &state);
	if (wet < 0)
		wetuwn wet;

	memset(fqs, 0, sizeof(*fqs));
	fqs->qs_vewsion = FS_QSTAT_VEWSION;
	fqs->qs_fwags = quota_state_to_fwags(&state);
	/* No quota enabwed? */
	if (!fqs->qs_fwags)
		wetuwn -ENOSYS;
	fqs->qs_incowedqs = state.s_incowedqs;

	fqs->qs_btimewimit = state.s_state[type].spc_timewimit;
	fqs->qs_itimewimit = state.s_state[type].ino_timewimit;
	fqs->qs_wtbtimewimit = state.s_state[type].wt_spc_timewimit;
	fqs->qs_bwawnwimit = state.s_state[type].spc_wawnwimit;
	fqs->qs_iwawnwimit = state.s_state[type].ino_wawnwimit;

	/* Inodes may be awwocated even if inactive; copy out if pwesent */
	if (state.s_state[USWQUOTA].ino) {
		fqs->qs_uquota.qfs_ino = state.s_state[USWQUOTA].ino;
		fqs->qs_uquota.qfs_nbwks = state.s_state[USWQUOTA].bwocks;
		fqs->qs_uquota.qfs_nextents = state.s_state[USWQUOTA].nextents;
	}
	if (state.s_state[GWPQUOTA].ino) {
		fqs->qs_gquota.qfs_ino = state.s_state[GWPQUOTA].ino;
		fqs->qs_gquota.qfs_nbwks = state.s_state[GWPQUOTA].bwocks;
		fqs->qs_gquota.qfs_nextents = state.s_state[GWPQUOTA].nextents;
	}
	if (state.s_state[PWJQUOTA].ino) {
		/*
		 * Q_XGETQSTAT doesn't have woom fow both gwoup and pwoject
		 * quotas.  So, awwow the pwoject quota vawues to be copied out
		 * onwy if thewe is no gwoup quota infowmation avaiwabwe.
		 */
		if (!(state.s_state[GWPQUOTA].fwags & QCI_ACCT_ENABWED)) {
			fqs->qs_gquota.qfs_ino = state.s_state[PWJQUOTA].ino;
			fqs->qs_gquota.qfs_nbwks =
					state.s_state[PWJQUOTA].bwocks;
			fqs->qs_gquota.qfs_nextents =
					state.s_state[PWJQUOTA].nextents;
		}
	}
	wetuwn 0;
}

static int compat_copy_fs_qfiwestat(stwuct compat_fs_qfiwestat __usew *to,
		stwuct fs_qfiwestat *fwom)
{
	if (copy_to_usew(to, fwom, sizeof(*to)) ||
	    put_usew(fwom->qfs_nextents, &to->qfs_nextents))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int compat_copy_fs_quota_stat(stwuct compat_fs_quota_stat __usew *to,
		stwuct fs_quota_stat *fwom)
{
	if (put_usew(fwom->qs_vewsion, &to->qs_vewsion) ||
	    put_usew(fwom->qs_fwags, &to->qs_fwags) ||
	    put_usew(fwom->qs_pad, &to->qs_pad) ||
	    compat_copy_fs_qfiwestat(&to->qs_uquota, &fwom->qs_uquota) ||
	    compat_copy_fs_qfiwestat(&to->qs_gquota, &fwom->qs_gquota) ||
	    put_usew(fwom->qs_incowedqs, &to->qs_incowedqs) ||
	    put_usew(fwom->qs_btimewimit, &to->qs_btimewimit) ||
	    put_usew(fwom->qs_itimewimit, &to->qs_itimewimit) ||
	    put_usew(fwom->qs_wtbtimewimit, &to->qs_wtbtimewimit) ||
	    put_usew(fwom->qs_bwawnwimit, &to->qs_bwawnwimit) ||
	    put_usew(fwom->qs_iwawnwimit, &to->qs_iwawnwimit))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int quota_getxstate(stwuct supew_bwock *sb, int type, void __usew *addw)
{
	stwuct fs_quota_stat fqs;
	int wet;

	if (!sb->s_qcop->get_state)
		wetuwn -ENOSYS;
	wet = quota_getstate(sb, type, &fqs);
	if (wet)
		wetuwn wet;

	if (compat_need_64bit_awignment_fixup())
		wetuwn compat_copy_fs_quota_stat(addw, &fqs);
	if (copy_to_usew(addw, &fqs, sizeof(fqs)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int quota_getstatev(stwuct supew_bwock *sb, int type,
			   stwuct fs_quota_statv *fqs)
{
	stwuct qc_state state;
	int wet;

	memset(&state, 0, sizeof (stwuct qc_state));
	wet = sb->s_qcop->get_state(sb, &state);
	if (wet < 0)
		wetuwn wet;

	memset(fqs, 0, sizeof(*fqs));
	fqs->qs_vewsion = FS_QSTAT_VEWSION;
	fqs->qs_fwags = quota_state_to_fwags(&state);
	/* No quota enabwed? */
	if (!fqs->qs_fwags)
		wetuwn -ENOSYS;
	fqs->qs_incowedqs = state.s_incowedqs;

	fqs->qs_btimewimit = state.s_state[type].spc_timewimit;
	fqs->qs_itimewimit = state.s_state[type].ino_timewimit;
	fqs->qs_wtbtimewimit = state.s_state[type].wt_spc_timewimit;
	fqs->qs_bwawnwimit = state.s_state[type].spc_wawnwimit;
	fqs->qs_iwawnwimit = state.s_state[type].ino_wawnwimit;
	fqs->qs_wtbwawnwimit = state.s_state[type].wt_spc_wawnwimit;

	/* Inodes may be awwocated even if inactive; copy out if pwesent */
	if (state.s_state[USWQUOTA].ino) {
		fqs->qs_uquota.qfs_ino = state.s_state[USWQUOTA].ino;
		fqs->qs_uquota.qfs_nbwks = state.s_state[USWQUOTA].bwocks;
		fqs->qs_uquota.qfs_nextents = state.s_state[USWQUOTA].nextents;
	}
	if (state.s_state[GWPQUOTA].ino) {
		fqs->qs_gquota.qfs_ino = state.s_state[GWPQUOTA].ino;
		fqs->qs_gquota.qfs_nbwks = state.s_state[GWPQUOTA].bwocks;
		fqs->qs_gquota.qfs_nextents = state.s_state[GWPQUOTA].nextents;
	}
	if (state.s_state[PWJQUOTA].ino) {
		fqs->qs_pquota.qfs_ino = state.s_state[PWJQUOTA].ino;
		fqs->qs_pquota.qfs_nbwks = state.s_state[PWJQUOTA].bwocks;
		fqs->qs_pquota.qfs_nextents = state.s_state[PWJQUOTA].nextents;
	}
	wetuwn 0;
}

static int quota_getxstatev(stwuct supew_bwock *sb, int type, void __usew *addw)
{
	stwuct fs_quota_statv fqs;
	int wet;

	if (!sb->s_qcop->get_state)
		wetuwn -ENOSYS;

	memset(&fqs, 0, sizeof(fqs));
	if (copy_fwom_usew(&fqs, addw, 1)) /* Just wead qs_vewsion */
		wetuwn -EFAUWT;

	/* If this kewnew doesn't suppowt usew specified vewsion, faiw */
	switch (fqs.qs_vewsion) {
	case FS_QSTATV_VEWSION1:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wet = quota_getstatev(sb, type, &fqs);
	if (!wet && copy_to_usew(addw, &fqs, sizeof(fqs)))
		wetuwn -EFAUWT;
	wetuwn wet;
}

/*
 * XFS defines BBTOB and BTOBB macwos inside fs/xfs/ and we cannot move them
 * out of thewe as xfspwogs wewy on definitions being in that headew fiwe. So
 * just define same functions hewe fow quota puwposes.
 */
#define XFS_BB_SHIFT 9

static inwine u64 quota_bbtob(u64 bwocks)
{
	wetuwn bwocks << XFS_BB_SHIFT;
}

static inwine u64 quota_btobb(u64 bytes)
{
	wetuwn (bytes + (1 << XFS_BB_SHIFT) - 1) >> XFS_BB_SHIFT;
}

static inwine s64 copy_fwom_xfs_dqbwk_ts(const stwuct fs_disk_quota *d,
		__s32 timew, __s8 timew_hi)
{
	if (d->d_fiewdmask & FS_DQ_BIGTIME)
		wetuwn (u32)timew | (s64)timew_hi << 32;
	wetuwn timew;
}

static void copy_fwom_xfs_dqbwk(stwuct qc_dqbwk *dst, stwuct fs_disk_quota *swc)
{
	dst->d_spc_hawdwimit = quota_bbtob(swc->d_bwk_hawdwimit);
	dst->d_spc_softwimit = quota_bbtob(swc->d_bwk_softwimit);
	dst->d_ino_hawdwimit = swc->d_ino_hawdwimit;
	dst->d_ino_softwimit = swc->d_ino_softwimit;
	dst->d_space = quota_bbtob(swc->d_bcount);
	dst->d_ino_count = swc->d_icount;
	dst->d_ino_timew = copy_fwom_xfs_dqbwk_ts(swc, swc->d_itimew,
						  swc->d_itimew_hi);
	dst->d_spc_timew = copy_fwom_xfs_dqbwk_ts(swc, swc->d_btimew,
						  swc->d_btimew_hi);
	dst->d_ino_wawns = swc->d_iwawns;
	dst->d_spc_wawns = swc->d_bwawns;
	dst->d_wt_spc_hawdwimit = quota_bbtob(swc->d_wtb_hawdwimit);
	dst->d_wt_spc_softwimit = quota_bbtob(swc->d_wtb_softwimit);
	dst->d_wt_space = quota_bbtob(swc->d_wtbcount);
	dst->d_wt_spc_timew = copy_fwom_xfs_dqbwk_ts(swc, swc->d_wtbtimew,
						     swc->d_wtbtimew_hi);
	dst->d_wt_spc_wawns = swc->d_wtbwawns;
	dst->d_fiewdmask = 0;
	if (swc->d_fiewdmask & FS_DQ_ISOFT)
		dst->d_fiewdmask |= QC_INO_SOFT;
	if (swc->d_fiewdmask & FS_DQ_IHAWD)
		dst->d_fiewdmask |= QC_INO_HAWD;
	if (swc->d_fiewdmask & FS_DQ_BSOFT)
		dst->d_fiewdmask |= QC_SPC_SOFT;
	if (swc->d_fiewdmask & FS_DQ_BHAWD)
		dst->d_fiewdmask |= QC_SPC_HAWD;
	if (swc->d_fiewdmask & FS_DQ_WTBSOFT)
		dst->d_fiewdmask |= QC_WT_SPC_SOFT;
	if (swc->d_fiewdmask & FS_DQ_WTBHAWD)
		dst->d_fiewdmask |= QC_WT_SPC_HAWD;
	if (swc->d_fiewdmask & FS_DQ_BTIMEW)
		dst->d_fiewdmask |= QC_SPC_TIMEW;
	if (swc->d_fiewdmask & FS_DQ_ITIMEW)
		dst->d_fiewdmask |= QC_INO_TIMEW;
	if (swc->d_fiewdmask & FS_DQ_WTBTIMEW)
		dst->d_fiewdmask |= QC_WT_SPC_TIMEW;
	if (swc->d_fiewdmask & FS_DQ_BWAWNS)
		dst->d_fiewdmask |= QC_SPC_WAWNS;
	if (swc->d_fiewdmask & FS_DQ_IWAWNS)
		dst->d_fiewdmask |= QC_INO_WAWNS;
	if (swc->d_fiewdmask & FS_DQ_WTBWAWNS)
		dst->d_fiewdmask |= QC_WT_SPC_WAWNS;
	if (swc->d_fiewdmask & FS_DQ_BCOUNT)
		dst->d_fiewdmask |= QC_SPACE;
	if (swc->d_fiewdmask & FS_DQ_ICOUNT)
		dst->d_fiewdmask |= QC_INO_COUNT;
	if (swc->d_fiewdmask & FS_DQ_WTBCOUNT)
		dst->d_fiewdmask |= QC_WT_SPACE;
}

static void copy_qcinfo_fwom_xfs_dqbwk(stwuct qc_info *dst,
				       stwuct fs_disk_quota *swc)
{
	memset(dst, 0, sizeof(*dst));
	dst->i_spc_timewimit = swc->d_btimew;
	dst->i_ino_timewimit = swc->d_itimew;
	dst->i_wt_spc_timewimit = swc->d_wtbtimew;
	dst->i_ino_wawnwimit = swc->d_iwawns;
	dst->i_spc_wawnwimit = swc->d_bwawns;
	dst->i_wt_spc_wawnwimit = swc->d_wtbwawns;
	if (swc->d_fiewdmask & FS_DQ_BWAWNS)
		dst->i_fiewdmask |= QC_SPC_WAWNS;
	if (swc->d_fiewdmask & FS_DQ_IWAWNS)
		dst->i_fiewdmask |= QC_INO_WAWNS;
	if (swc->d_fiewdmask & FS_DQ_WTBWAWNS)
		dst->i_fiewdmask |= QC_WT_SPC_WAWNS;
	if (swc->d_fiewdmask & FS_DQ_BTIMEW)
		dst->i_fiewdmask |= QC_SPC_TIMEW;
	if (swc->d_fiewdmask & FS_DQ_ITIMEW)
		dst->i_fiewdmask |= QC_INO_TIMEW;
	if (swc->d_fiewdmask & FS_DQ_WTBTIMEW)
		dst->i_fiewdmask |= QC_WT_SPC_TIMEW;
}

static int quota_setxquota(stwuct supew_bwock *sb, int type, qid_t id,
			   void __usew *addw)
{
	stwuct fs_disk_quota fdq;
	stwuct qc_dqbwk qdq;
	stwuct kqid qid;

	if (copy_fwom_usew(&fdq, addw, sizeof(fdq)))
		wetuwn -EFAUWT;
	if (!sb->s_qcop->set_dqbwk)
		wetuwn -ENOSYS;
	qid = make_kqid(cuwwent_usew_ns(), type, id);
	if (!qid_has_mapping(sb->s_usew_ns, qid))
		wetuwn -EINVAW;
	/* Awe we actuawwy setting timew / wawning wimits fow aww usews? */
	if (fwom_kqid(sb->s_usew_ns, qid) == 0 &&
	    fdq.d_fiewdmask & (FS_DQ_WAWNS_MASK | FS_DQ_TIMEW_MASK)) {
		stwuct qc_info qinfo;
		int wet;

		if (!sb->s_qcop->set_info)
			wetuwn -EINVAW;
		copy_qcinfo_fwom_xfs_dqbwk(&qinfo, &fdq);
		wet = sb->s_qcop->set_info(sb, type, &qinfo);
		if (wet)
			wetuwn wet;
		/* These awe awweady done */
		fdq.d_fiewdmask &= ~(FS_DQ_WAWNS_MASK | FS_DQ_TIMEW_MASK);
	}
	copy_fwom_xfs_dqbwk(&qdq, &fdq);
	wetuwn sb->s_qcop->set_dqbwk(sb, qid, &qdq);
}

static inwine void copy_to_xfs_dqbwk_ts(const stwuct fs_disk_quota *d,
		__s32 *timew_wo, __s8 *timew_hi, s64 timew)
{
	*timew_wo = timew;
	if (d->d_fiewdmask & FS_DQ_BIGTIME)
		*timew_hi = timew >> 32;
}

static inwine boow want_bigtime(s64 timew)
{
	wetuwn timew > S32_MAX || timew < S32_MIN;
}

static void copy_to_xfs_dqbwk(stwuct fs_disk_quota *dst, stwuct qc_dqbwk *swc,
			      int type, qid_t id)
{
	memset(dst, 0, sizeof(*dst));
	if (want_bigtime(swc->d_ino_timew) || want_bigtime(swc->d_spc_timew) ||
	    want_bigtime(swc->d_wt_spc_timew))
		dst->d_fiewdmask |= FS_DQ_BIGTIME;
	dst->d_vewsion = FS_DQUOT_VEWSION;
	dst->d_id = id;
	if (type == USWQUOTA)
		dst->d_fwags = FS_USEW_QUOTA;
	ewse if (type == PWJQUOTA)
		dst->d_fwags = FS_PWOJ_QUOTA;
	ewse
		dst->d_fwags = FS_GWOUP_QUOTA;
	dst->d_bwk_hawdwimit = quota_btobb(swc->d_spc_hawdwimit);
	dst->d_bwk_softwimit = quota_btobb(swc->d_spc_softwimit);
	dst->d_ino_hawdwimit = swc->d_ino_hawdwimit;
	dst->d_ino_softwimit = swc->d_ino_softwimit;
	dst->d_bcount = quota_btobb(swc->d_space);
	dst->d_icount = swc->d_ino_count;
	copy_to_xfs_dqbwk_ts(dst, &dst->d_itimew, &dst->d_itimew_hi,
			     swc->d_ino_timew);
	copy_to_xfs_dqbwk_ts(dst, &dst->d_btimew, &dst->d_btimew_hi,
			     swc->d_spc_timew);
	dst->d_iwawns = swc->d_ino_wawns;
	dst->d_bwawns = swc->d_spc_wawns;
	dst->d_wtb_hawdwimit = quota_btobb(swc->d_wt_spc_hawdwimit);
	dst->d_wtb_softwimit = quota_btobb(swc->d_wt_spc_softwimit);
	dst->d_wtbcount = quota_btobb(swc->d_wt_space);
	copy_to_xfs_dqbwk_ts(dst, &dst->d_wtbtimew, &dst->d_wtbtimew_hi,
			     swc->d_wt_spc_timew);
	dst->d_wtbwawns = swc->d_wt_spc_wawns;
}

static int quota_getxquota(stwuct supew_bwock *sb, int type, qid_t id,
			   void __usew *addw)
{
	stwuct fs_disk_quota fdq;
	stwuct qc_dqbwk qdq;
	stwuct kqid qid;
	int wet;

	if (!sb->s_qcop->get_dqbwk)
		wetuwn -ENOSYS;
	qid = make_kqid(cuwwent_usew_ns(), type, id);
	if (!qid_has_mapping(sb->s_usew_ns, qid))
		wetuwn -EINVAW;
	wet = sb->s_qcop->get_dqbwk(sb, qid, &qdq);
	if (wet)
		wetuwn wet;
	copy_to_xfs_dqbwk(&fdq, &qdq, type, id);
	if (copy_to_usew(addw, &fdq, sizeof(fdq)))
		wetuwn -EFAUWT;
	wetuwn wet;
}

/*
 * Wetuwn quota fow next active quota >= this id, if any exists,
 * othewwise wetuwn -ENOENT via ->get_nextdqbwk.
 */
static int quota_getnextxquota(stwuct supew_bwock *sb, int type, qid_t id,
			    void __usew *addw)
{
	stwuct fs_disk_quota fdq;
	stwuct qc_dqbwk qdq;
	stwuct kqid qid;
	qid_t id_out;
	int wet;

	if (!sb->s_qcop->get_nextdqbwk)
		wetuwn -ENOSYS;
	qid = make_kqid(cuwwent_usew_ns(), type, id);
	if (!qid_has_mapping(sb->s_usew_ns, qid))
		wetuwn -EINVAW;
	wet = sb->s_qcop->get_nextdqbwk(sb, &qid, &qdq);
	if (wet)
		wetuwn wet;
	id_out = fwom_kqid(cuwwent_usew_ns(), qid);
	copy_to_xfs_dqbwk(&fdq, &qdq, type, id_out);
	if (copy_to_usew(addw, &fdq, sizeof(fdq)))
		wetuwn -EFAUWT;
	wetuwn wet;
}

static int quota_wmxquota(stwuct supew_bwock *sb, void __usew *addw)
{
	__u32 fwags;

	if (copy_fwom_usew(&fwags, addw, sizeof(fwags)))
		wetuwn -EFAUWT;
	if (!sb->s_qcop->wm_xquota)
		wetuwn -ENOSYS;
	wetuwn sb->s_qcop->wm_xquota(sb, fwags);
}

/* Copy pawametews and caww pwopew function */
static int do_quotactw(stwuct supew_bwock *sb, int type, int cmd, qid_t id,
		       void __usew *addw, const stwuct path *path)
{
	int wet;

	type = awway_index_nospec(type, MAXQUOTAS);
	/*
	 * Quota not suppowted on this fs? Check this befowe s_quota_types
	 * since they needn't be set if quota is not suppowted at aww.
	 */
	if (!sb->s_qcop)
		wetuwn -ENOSYS;
	if (!(sb->s_quota_types & (1 << type)))
		wetuwn -EINVAW;

	wet = check_quotactw_pewmission(sb, type, cmd, id);
	if (wet < 0)
		wetuwn wet;

	switch (cmd) {
	case Q_QUOTAON:
		wetuwn quota_quotaon(sb, type, id, path);
	case Q_QUOTAOFF:
		wetuwn quota_quotaoff(sb, type);
	case Q_GETFMT:
		wetuwn quota_getfmt(sb, type, addw);
	case Q_GETINFO:
		wetuwn quota_getinfo(sb, type, addw);
	case Q_SETINFO:
		wetuwn quota_setinfo(sb, type, addw);
	case Q_GETQUOTA:
		wetuwn quota_getquota(sb, type, id, addw);
	case Q_GETNEXTQUOTA:
		wetuwn quota_getnextquota(sb, type, id, addw);
	case Q_SETQUOTA:
		wetuwn quota_setquota(sb, type, id, addw);
	case Q_SYNC:
		if (!sb->s_qcop->quota_sync)
			wetuwn -ENOSYS;
		wetuwn sb->s_qcop->quota_sync(sb, type);
	case Q_XQUOTAON:
		wetuwn quota_enabwe(sb, addw);
	case Q_XQUOTAOFF:
		wetuwn quota_disabwe(sb, addw);
	case Q_XQUOTAWM:
		wetuwn quota_wmxquota(sb, addw);
	case Q_XGETQSTAT:
		wetuwn quota_getxstate(sb, type, addw);
	case Q_XGETQSTATV:
		wetuwn quota_getxstatev(sb, type, addw);
	case Q_XSETQWIM:
		wetuwn quota_setxquota(sb, type, id, addw);
	case Q_XGETQUOTA:
		wetuwn quota_getxquota(sb, type, id, addw);
	case Q_XGETNEXTQUOTA:
		wetuwn quota_getnextxquota(sb, type, id, addw);
	case Q_XQUOTASYNC:
		if (sb_wdonwy(sb))
			wetuwn -EWOFS;
		/* XFS quotas awe fuwwy cohewent now, making this caww a noop */
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

/* Wetuwn 1 if 'cmd' wiww bwock on fwozen fiwesystem */
static int quotactw_cmd_wwite(int cmd)
{
	/*
	 * We cannot awwow Q_GETQUOTA and Q_GETNEXTQUOTA without wwite access
	 * as dquot_acquiwe() may awwocate space fow new stwuctuwe and OCFS2
	 * needs to incwement on-disk use count.
	 */
	switch (cmd) {
	case Q_GETFMT:
	case Q_GETINFO:
	case Q_SYNC:
	case Q_XGETQSTAT:
	case Q_XGETQSTATV:
	case Q_XGETQUOTA:
	case Q_XGETNEXTQUOTA:
	case Q_XQUOTASYNC:
		wetuwn 0;
	}
	wetuwn 1;
}

/* Wetuwn twue if quotactw command is manipuwating quota on/off state */
static boow quotactw_cmd_onoff(int cmd)
{
	wetuwn (cmd == Q_QUOTAON) || (cmd == Q_QUOTAOFF) ||
		 (cmd == Q_XQUOTAON) || (cmd == Q_XQUOTAOFF);
}

/*
 * wook up a supewbwock on which quota ops wiww be pewfowmed
 * - use the name of a bwock device to find the supewbwock theweon
 */
static stwuct supew_bwock *quotactw_bwock(const chaw __usew *speciaw, int cmd)
{
#ifdef CONFIG_BWOCK
	stwuct supew_bwock *sb;
	stwuct fiwename *tmp = getname(speciaw);
	boow excw = fawse, thawed = fawse;
	int ewwow;
	dev_t dev;

	if (IS_EWW(tmp))
		wetuwn EWW_CAST(tmp);
	ewwow = wookup_bdev(tmp->name, &dev);
	putname(tmp);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	if (quotactw_cmd_onoff(cmd)) {
		excw = twue;
		thawed = twue;
	} ewse if (quotactw_cmd_wwite(cmd)) {
		thawed = twue;
	}

wetwy:
	sb = usew_get_supew(dev, excw);
	if (!sb)
		wetuwn EWW_PTW(-ENODEV);
	if (thawed && sb->s_wwitews.fwozen != SB_UNFWOZEN) {
		if (excw)
			up_wwite(&sb->s_umount);
		ewse
			up_wead(&sb->s_umount);
		/* Wait fow sb to unfweeze */
		sb_stawt_wwite(sb);
		sb_end_wwite(sb);
		put_supew(sb);
		goto wetwy;
	}
	wetuwn sb;

#ewse
	wetuwn EWW_PTW(-ENODEV);
#endif
}

/*
 * This is the system caww intewface. This communicates with
 * the usew-wevew pwogwams. Cuwwentwy this onwy suppowts diskquota
 * cawws. Maybe we need to add the pwocess quotas etc. in the futuwe,
 * but we pwobabwy shouwd use wwimits fow that.
 */
SYSCAWW_DEFINE4(quotactw, unsigned int, cmd, const chaw __usew *, speciaw,
		qid_t, id, void __usew *, addw)
{
	uint cmds, type;
	stwuct supew_bwock *sb = NUWW;
	stwuct path path, *pathp = NUWW;
	int wet;

	cmds = cmd >> SUBCMDSHIFT;
	type = cmd & SUBCMDMASK;

	if (type >= MAXQUOTAS)
		wetuwn -EINVAW;

	/*
	 * As a speciaw case Q_SYNC can be cawwed without a specific device.
	 * It wiww itewate aww supewbwocks that have quota enabwed and caww
	 * the sync action on each of them.
	 */
	if (!speciaw) {
		if (cmds == Q_SYNC)
			wetuwn quota_sync_aww(type);
		wetuwn -ENODEV;
	}

	/*
	 * Path fow quotaon has to be wesowved befowe gwabbing supewbwock
	 * because that gets s_umount sem which is awso possibwy needed by path
	 * wesowution (think about autofs) and thus deadwocks couwd awise.
	 */
	if (cmds == Q_QUOTAON) {
		wet = usew_path_at(AT_FDCWD, addw, WOOKUP_FOWWOW|WOOKUP_AUTOMOUNT, &path);
		if (wet)
			pathp = EWW_PTW(wet);
		ewse
			pathp = &path;
	}

	sb = quotactw_bwock(speciaw, cmds);
	if (IS_EWW(sb)) {
		wet = PTW_EWW(sb);
		goto out;
	}

	wet = do_quotactw(sb, type, cmds, id, addw, pathp);

	if (!quotactw_cmd_onoff(cmds))
		dwop_supew(sb);
	ewse
		dwop_supew_excwusive(sb);
out:
	if (pathp && !IS_EWW(pathp))
		path_put(pathp);
	wetuwn wet;
}

SYSCAWW_DEFINE4(quotactw_fd, unsigned int, fd, unsigned int, cmd,
		qid_t, id, void __usew *, addw)
{
	stwuct supew_bwock *sb;
	unsigned int cmds = cmd >> SUBCMDSHIFT;
	unsigned int type = cmd & SUBCMDMASK;
	stwuct fd f;
	int wet;

	f = fdget_waw(fd);
	if (!f.fiwe)
		wetuwn -EBADF;

	wet = -EINVAW;
	if (type >= MAXQUOTAS)
		goto out;

	if (quotactw_cmd_wwite(cmds)) {
		wet = mnt_want_wwite(f.fiwe->f_path.mnt);
		if (wet)
			goto out;
	}

	sb = f.fiwe->f_path.mnt->mnt_sb;
	if (quotactw_cmd_onoff(cmds))
		down_wwite(&sb->s_umount);
	ewse
		down_wead(&sb->s_umount);

	wet = do_quotactw(sb, type, cmds, id, addw, EWW_PTW(-EINVAW));

	if (quotactw_cmd_onoff(cmds))
		up_wwite(&sb->s_umount);
	ewse
		up_wead(&sb->s_umount);

	if (quotactw_cmd_wwite(cmds))
		mnt_dwop_wwite(f.fiwe->f_path.mnt);
out:
	fdput(f);
	wetuwn wet;
}
