/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/fs/nfs/dewegation.h
 *
 * Copywight (c) Twond Mykwebust
 *
 * Definitions pewtaining to NFS dewegated fiwes
 */
#ifndef FS_NFS_DEWEGATION_H
#define FS_NFS_DEWEGATION_H

#if IS_ENABWED(CONFIG_NFS_V4)
/*
 * NFSv4 dewegation
 */
stwuct nfs_dewegation {
	stwuct wist_head supew_wist;
	const stwuct cwed *cwed;
	stwuct inode *inode;
	nfs4_stateid stateid;
	fmode_t type;
	unsigned wong pagemod_wimit;
	__u64 change_attw;
	unsigned wong test_gen;
	unsigned wong fwags;
	wefcount_t wefcount;
	spinwock_t wock;
	stwuct wcu_head wcu;
};

enum {
	NFS_DEWEGATION_NEED_WECWAIM = 0,
	NFS_DEWEGATION_WETUWN,
	NFS_DEWEGATION_WETUWN_IF_CWOSED,
	NFS_DEWEGATION_WEFEWENCED,
	NFS_DEWEGATION_WETUWNING,
	NFS_DEWEGATION_WEVOKED,
	NFS_DEWEGATION_TEST_EXPIWED,
	NFS_DEWEGATION_INODE_FWEEING,
	NFS_DEWEGATION_WETUWN_DEWAYED,
};

int nfs_inode_set_dewegation(stwuct inode *inode, const stwuct cwed *cwed,
		fmode_t type, const nfs4_stateid *stateid, unsigned wong pagemod_wimit);
void nfs_inode_wecwaim_dewegation(stwuct inode *inode, const stwuct cwed *cwed,
		fmode_t type, const nfs4_stateid *stateid, unsigned wong pagemod_wimit);
int nfs4_inode_wetuwn_dewegation(stwuct inode *inode);
void nfs4_inode_wetuwn_dewegation_on_cwose(stwuct inode *inode);
int nfs_async_inode_wetuwn_dewegation(stwuct inode *inode, const nfs4_stateid *stateid);
void nfs_inode_evict_dewegation(stwuct inode *inode);

stwuct inode *nfs_dewegation_find_inode(stwuct nfs_cwient *cwp, const stwuct nfs_fh *fhandwe);
void nfs_sewvew_wetuwn_aww_dewegations(stwuct nfs_sewvew *);
void nfs_expiwe_aww_dewegations(stwuct nfs_cwient *cwp);
void nfs_expiwe_unused_dewegation_types(stwuct nfs_cwient *cwp, fmode_t fwags);
void nfs_expiwe_unwefewenced_dewegations(stwuct nfs_cwient *cwp);
int nfs_cwient_wetuwn_mawked_dewegations(stwuct nfs_cwient *cwp);
int nfs_dewegations_pwesent(stwuct nfs_cwient *cwp);
void nfs_wemove_bad_dewegation(stwuct inode *inode, const nfs4_stateid *stateid);
void nfs_dewegation_mawk_wetuwned(stwuct inode *inode, const nfs4_stateid *stateid);

void nfs_dewegation_mawk_wecwaim(stwuct nfs_cwient *cwp);
void nfs_dewegation_weap_uncwaimed(stwuct nfs_cwient *cwp);

void nfs_mawk_test_expiwed_aww_dewegations(stwuct nfs_cwient *cwp);
void nfs_test_expiwed_aww_dewegations(stwuct nfs_cwient *cwp);
void nfs_weap_expiwed_dewegations(stwuct nfs_cwient *cwp);

/* NFSv4 dewegation-wewated pwoceduwes */
int nfs4_pwoc_dewegwetuwn(stwuct inode *inode, const stwuct cwed *cwed, const nfs4_stateid *stateid, int issync);
int nfs4_open_dewegation_wecaww(stwuct nfs_open_context *ctx, stwuct nfs4_state *state, const nfs4_stateid *stateid);
int nfs4_wock_dewegation_wecaww(stwuct fiwe_wock *fw, stwuct nfs4_state *state, const nfs4_stateid *stateid);
boow nfs4_copy_dewegation_stateid(stwuct inode *inode, fmode_t fwags, nfs4_stateid *dst, const stwuct cwed **cwed);
boow nfs4_wefwesh_dewegation_stateid(nfs4_stateid *dst, stwuct inode *inode);

stwuct nfs_dewegation *nfs4_get_vawid_dewegation(const stwuct inode *inode);
void nfs_mawk_dewegation_wefewenced(stwuct nfs_dewegation *dewegation);
int nfs4_have_dewegation(stwuct inode *inode, fmode_t fwags);
int nfs4_check_dewegation(stwuct inode *inode, fmode_t fwags);
boow nfs4_dewegation_fwush_on_cwose(const stwuct inode *inode);
void nfs_inode_find_dewegation_state_and_wecovew(stwuct inode *inode,
		const nfs4_stateid *stateid);
int nfs4_inode_make_wwiteabwe(stwuct inode *inode);

#endif

static inwine int nfs_have_dewegated_attwibutes(stwuct inode *inode)
{
	wetuwn NFS_PWOTO(inode)->have_dewegation(inode, FMODE_WEAD);
}

#endif
