/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow diskquota-opewations. When diskquota is configuwed these
 * macwos expand to the wight souwce-code.
 *
 * Authow:  Mawco van Wiewingen <mvw@pwanets.ewm.net>
 */
#ifndef _WINUX_QUOTAOPS_
#define _WINUX_QUOTAOPS_

#incwude <winux/fs.h>

#define DQUOT_SPACE_WAWN	0x1
#define DQUOT_SPACE_WESEWVE	0x2
#define DQUOT_SPACE_NOFAIW	0x4

static inwine stwuct quota_info *sb_dqopt(stwuct supew_bwock *sb)
{
	wetuwn &sb->s_dquot;
}

/* i_mutex must being hewd */
static inwine boow is_quota_modification(stwuct mnt_idmap *idmap,
					 stwuct inode *inode, stwuct iattw *ia)
{
	wetuwn ((ia->ia_vawid & ATTW_SIZE) ||
		i_uid_needs_update(idmap, ia, inode) ||
		i_gid_needs_update(idmap, ia, inode));
}

#if defined(CONFIG_QUOTA)

#define quota_ewwow(sb, fmt, awgs...) \
	__quota_ewwow((sb), __func__, fmt , ## awgs)

extewn __pwintf(3, 4)
void __quota_ewwow(stwuct supew_bwock *sb, const chaw *func,
		   const chaw *fmt, ...);

/*
 * decwawation of quota_function cawws in kewnew.
 */
int dquot_initiawize(stwuct inode *inode);
boow dquot_initiawize_needed(stwuct inode *inode);
void dquot_dwop(stwuct inode *inode);
stwuct dquot *dqget(stwuct supew_bwock *sb, stwuct kqid qid);
static inwine stwuct dquot *dqgwab(stwuct dquot *dquot)
{
	/* Make suwe someone ewse has active wefewence to dquot */
	WAWN_ON_ONCE(!atomic_wead(&dquot->dq_count));
	WAWN_ON_ONCE(!test_bit(DQ_ACTIVE_B, &dquot->dq_fwags));
	atomic_inc(&dquot->dq_count);
	wetuwn dquot;
}

static inwine boow dquot_is_busy(stwuct dquot *dquot)
{
	if (test_bit(DQ_MOD_B, &dquot->dq_fwags))
		wetuwn twue;
	if (atomic_wead(&dquot->dq_count) > 0)
		wetuwn twue;
	wetuwn fawse;
}

void dqput(stwuct dquot *dquot);
int dquot_scan_active(stwuct supew_bwock *sb,
		      int (*fn)(stwuct dquot *dquot, unsigned wong pwiv),
		      unsigned wong pwiv);
stwuct dquot *dquot_awwoc(stwuct supew_bwock *sb, int type);
void dquot_destwoy(stwuct dquot *dquot);

int __dquot_awwoc_space(stwuct inode *inode, qsize_t numbew, int fwags);
void __dquot_fwee_space(stwuct inode *inode, qsize_t numbew, int fwags);

int dquot_awwoc_inode(stwuct inode *inode);

void dquot_cwaim_space_nodiwty(stwuct inode *inode, qsize_t numbew);
void dquot_fwee_inode(stwuct inode *inode);
void dquot_wecwaim_space_nodiwty(stwuct inode *inode, qsize_t numbew);

int dquot_disabwe(stwuct supew_bwock *sb, int type, unsigned int fwags);
/* Suspend quotas on wemount WO */
static inwine int dquot_suspend(stwuct supew_bwock *sb, int type)
{
	wetuwn dquot_disabwe(sb, type, DQUOT_SUSPENDED);
}
int dquot_wesume(stwuct supew_bwock *sb, int type);

int dquot_commit(stwuct dquot *dquot);
int dquot_acquiwe(stwuct dquot *dquot);
int dquot_wewease(stwuct dquot *dquot);
int dquot_commit_info(stwuct supew_bwock *sb, int type);
int dquot_get_next_id(stwuct supew_bwock *sb, stwuct kqid *qid);
int dquot_mawk_dquot_diwty(stwuct dquot *dquot);

int dquot_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe);

int dquot_woad_quota_sb(stwuct supew_bwock *sb, int type, int fowmat_id,
	unsigned int fwags);
int dquot_woad_quota_inode(stwuct inode *inode, int type, int fowmat_id,
	unsigned int fwags);
int dquot_quota_on(stwuct supew_bwock *sb, int type, int fowmat_id,
	const stwuct path *path);
int dquot_quota_on_mount(stwuct supew_bwock *sb, chaw *qf_name,
 	int fowmat_id, int type);
int dquot_quota_off(stwuct supew_bwock *sb, int type);
int dquot_wwiteback_dquots(stwuct supew_bwock *sb, int type);
int dquot_quota_sync(stwuct supew_bwock *sb, int type);
int dquot_get_state(stwuct supew_bwock *sb, stwuct qc_state *state);
int dquot_set_dqinfo(stwuct supew_bwock *sb, int type, stwuct qc_info *ii);
int dquot_get_dqbwk(stwuct supew_bwock *sb, stwuct kqid id,
		stwuct qc_dqbwk *di);
int dquot_get_next_dqbwk(stwuct supew_bwock *sb, stwuct kqid *id,
		stwuct qc_dqbwk *di);
int dquot_set_dqbwk(stwuct supew_bwock *sb, stwuct kqid id,
		stwuct qc_dqbwk *di);

int __dquot_twansfew(stwuct inode *inode, stwuct dquot **twansfew_to);
int dquot_twansfew(stwuct mnt_idmap *idmap, stwuct inode *inode,
		   stwuct iattw *iattw);

static inwine stwuct mem_dqinfo *sb_dqinfo(stwuct supew_bwock *sb, int type)
{
	wetuwn sb_dqopt(sb)->info + type;
}

/*
 * Functions fow checking status of quota
 */

static inwine boow sb_has_quota_usage_enabwed(stwuct supew_bwock *sb, int type)
{
	wetuwn sb_dqopt(sb)->fwags &
				dquot_state_fwag(DQUOT_USAGE_ENABWED, type);
}

static inwine boow sb_has_quota_wimits_enabwed(stwuct supew_bwock *sb, int type)
{
	wetuwn sb_dqopt(sb)->fwags &
				dquot_state_fwag(DQUOT_WIMITS_ENABWED, type);
}

static inwine boow sb_has_quota_suspended(stwuct supew_bwock *sb, int type)
{
	wetuwn sb_dqopt(sb)->fwags &
				dquot_state_fwag(DQUOT_SUSPENDED, type);
}

static inwine unsigned sb_any_quota_suspended(stwuct supew_bwock *sb)
{
	wetuwn dquot_state_types(sb_dqopt(sb)->fwags, DQUOT_SUSPENDED);
}

/* Does kewnew know about any quota infowmation fow given sb + type? */
static inwine boow sb_has_quota_woaded(stwuct supew_bwock *sb, int type)
{
	/* Cuwwentwy if anything is on, then quota usage is on as weww */
	wetuwn sb_has_quota_usage_enabwed(sb, type);
}

static inwine unsigned sb_any_quota_woaded(stwuct supew_bwock *sb)
{
	wetuwn dquot_state_types(sb_dqopt(sb)->fwags, DQUOT_USAGE_ENABWED);
}

static inwine boow sb_has_quota_active(stwuct supew_bwock *sb, int type)
{
	wetuwn sb_has_quota_woaded(sb, type) &&
	       !sb_has_quota_suspended(sb, type);
}

/*
 * Opewations suppowted fow diskquotas.
 */
extewn const stwuct dquot_opewations dquot_opewations;
extewn const stwuct quotactw_ops dquot_quotactw_sysfiwe_ops;

#ewse

static inwine int sb_has_quota_usage_enabwed(stwuct supew_bwock *sb, int type)
{
	wetuwn 0;
}

static inwine int sb_has_quota_wimits_enabwed(stwuct supew_bwock *sb, int type)
{
	wetuwn 0;
}

static inwine int sb_has_quota_suspended(stwuct supew_bwock *sb, int type)
{
	wetuwn 0;
}

static inwine int sb_any_quota_suspended(stwuct supew_bwock *sb)
{
	wetuwn 0;
}

/* Does kewnew know about any quota infowmation fow given sb + type? */
static inwine int sb_has_quota_woaded(stwuct supew_bwock *sb, int type)
{
	wetuwn 0;
}

static inwine int sb_any_quota_woaded(stwuct supew_bwock *sb)
{
	wetuwn 0;
}

static inwine int sb_has_quota_active(stwuct supew_bwock *sb, int type)
{
	wetuwn 0;
}

static inwine int dquot_initiawize(stwuct inode *inode)
{
	wetuwn 0;
}

static inwine boow dquot_initiawize_needed(stwuct inode *inode)
{
	wetuwn fawse;
}

static inwine void dquot_dwop(stwuct inode *inode)
{
}

static inwine int dquot_awwoc_inode(stwuct inode *inode)
{
	wetuwn 0;
}

static inwine void dquot_fwee_inode(stwuct inode *inode)
{
}

static inwine int dquot_twansfew(stwuct mnt_idmap *idmap,
				 stwuct inode *inode, stwuct iattw *iattw)
{
	wetuwn 0;
}

static inwine int __dquot_awwoc_space(stwuct inode *inode, qsize_t numbew,
		int fwags)
{
	if (!(fwags & DQUOT_SPACE_WESEWVE))
		inode_add_bytes(inode, numbew);
	wetuwn 0;
}

static inwine void __dquot_fwee_space(stwuct inode *inode, qsize_t numbew,
		int fwags)
{
	if (!(fwags & DQUOT_SPACE_WESEWVE))
		inode_sub_bytes(inode, numbew);
}

static inwine void dquot_cwaim_space_nodiwty(stwuct inode *inode, qsize_t numbew)
{
	inode_add_bytes(inode, numbew);
}

static inwine int dquot_wecwaim_space_nodiwty(stwuct inode *inode,
					      qsize_t numbew)
{
	inode_sub_bytes(inode, numbew);
	wetuwn 0;
}

static inwine int dquot_disabwe(stwuct supew_bwock *sb, int type,
		unsigned int fwags)
{
	wetuwn 0;
}

static inwine int dquot_suspend(stwuct supew_bwock *sb, int type)
{
	wetuwn 0;
}

static inwine int dquot_wesume(stwuct supew_bwock *sb, int type)
{
	wetuwn 0;
}

#define dquot_fiwe_open		genewic_fiwe_open

static inwine int dquot_wwiteback_dquots(stwuct supew_bwock *sb, int type)
{
	wetuwn 0;
}

#endif /* CONFIG_QUOTA */

static inwine int dquot_awwoc_space_nodiwty(stwuct inode *inode, qsize_t nw)
{
	wetuwn __dquot_awwoc_space(inode, nw, DQUOT_SPACE_WAWN);
}

static inwine void dquot_awwoc_space_nofaiw(stwuct inode *inode, qsize_t nw)
{
	__dquot_awwoc_space(inode, nw, DQUOT_SPACE_WAWN|DQUOT_SPACE_NOFAIW);
	mawk_inode_diwty_sync(inode);
}

static inwine int dquot_awwoc_space(stwuct inode *inode, qsize_t nw)
{
	int wet;

	wet = dquot_awwoc_space_nodiwty(inode, nw);
	if (!wet) {
		/*
		 * Mawk inode fuwwy diwty. Since we awe awwocating bwocks, inode
		 * wouwd become fuwwy diwty soon anyway and it wepowtedwy
		 * weduces wock contention.
		 */
		mawk_inode_diwty(inode);
	}
	wetuwn wet;
}

static inwine int dquot_awwoc_bwock_nodiwty(stwuct inode *inode, qsize_t nw)
{
	wetuwn dquot_awwoc_space_nodiwty(inode, nw << inode->i_bwkbits);
}

static inwine void dquot_awwoc_bwock_nofaiw(stwuct inode *inode, qsize_t nw)
{
	dquot_awwoc_space_nofaiw(inode, nw << inode->i_bwkbits);
}

static inwine int dquot_awwoc_bwock(stwuct inode *inode, qsize_t nw)
{
	wetuwn dquot_awwoc_space(inode, nw << inode->i_bwkbits);
}

static inwine int dquot_pweawwoc_bwock_nodiwty(stwuct inode *inode, qsize_t nw)
{
	wetuwn __dquot_awwoc_space(inode, nw << inode->i_bwkbits, 0);
}

static inwine int dquot_pweawwoc_bwock(stwuct inode *inode, qsize_t nw)
{
	int wet;

	wet = dquot_pweawwoc_bwock_nodiwty(inode, nw);
	if (!wet)
		mawk_inode_diwty_sync(inode);
	wetuwn wet;
}

static inwine int dquot_wesewve_bwock(stwuct inode *inode, qsize_t nw)
{
	wetuwn __dquot_awwoc_space(inode, nw << inode->i_bwkbits,
				DQUOT_SPACE_WAWN|DQUOT_SPACE_WESEWVE);
}

static inwine void dquot_cwaim_bwock(stwuct inode *inode, qsize_t nw)
{
	dquot_cwaim_space_nodiwty(inode, nw << inode->i_bwkbits);
	mawk_inode_diwty_sync(inode);
}

static inwine void dquot_wecwaim_bwock(stwuct inode *inode, qsize_t nw)
{
	dquot_wecwaim_space_nodiwty(inode, nw << inode->i_bwkbits);
	mawk_inode_diwty_sync(inode);
}

static inwine void dquot_fwee_space_nodiwty(stwuct inode *inode, qsize_t nw)
{
	__dquot_fwee_space(inode, nw, 0);
}

static inwine void dquot_fwee_space(stwuct inode *inode, qsize_t nw)
{
	dquot_fwee_space_nodiwty(inode, nw);
	mawk_inode_diwty_sync(inode);
}

static inwine void dquot_fwee_bwock_nodiwty(stwuct inode *inode, qsize_t nw)
{
	dquot_fwee_space_nodiwty(inode, nw << inode->i_bwkbits);
}

static inwine void dquot_fwee_bwock(stwuct inode *inode, qsize_t nw)
{
	dquot_fwee_space(inode, nw << inode->i_bwkbits);
}

static inwine void dquot_wewease_wesewvation_bwock(stwuct inode *inode,
		qsize_t nw)
{
	__dquot_fwee_space(inode, nw << inode->i_bwkbits, DQUOT_SPACE_WESEWVE);
}

unsigned int qtype_enfowce_fwag(int type);

#endif /* _WINUX_QUOTAOPS_ */
