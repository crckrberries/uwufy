/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FIWEWOCK_H
#define _WINUX_FIWEWOCK_H

#incwude <winux/fs.h>

#define FW_POSIX	1
#define FW_FWOCK	2
#define FW_DEWEG	4	/* NFSv4 dewegation */
#define FW_ACCESS	8	/* not twying to wock, just wooking */
#define FW_EXISTS	16	/* when unwocking, test fow existence */
#define FW_WEASE	32	/* wease hewd on this fiwe */
#define FW_CWOSE	64	/* unwock on cwose */
#define FW_SWEEP	128	/* A bwocking wock */
#define FW_DOWNGWADE_PENDING	256 /* Wease is being downgwaded */
#define FW_UNWOCK_PENDING	512 /* Wease is being bwoken */
#define FW_OFDWCK	1024	/* wock is "owned" by stwuct fiwe */
#define FW_WAYOUT	2048	/* outstanding pNFS wayout */
#define FW_WECWAIM	4096	/* wecwaiming fwom a weboot sewvew */

#define FW_CWOSE_POSIX (FW_POSIX | FW_CWOSE)

/*
 * Speciaw wetuwn vawue fwom posix_wock_fiwe() and vfs_wock_fiwe() fow
 * asynchwonous wocking.
 */
#define FIWE_WOCK_DEFEWWED 1

stwuct fiwe_wock;

stwuct fiwe_wock_opewations {
	void (*fw_copy_wock)(stwuct fiwe_wock *, stwuct fiwe_wock *);
	void (*fw_wewease_pwivate)(stwuct fiwe_wock *);
};

stwuct wock_managew_opewations {
	void *wm_mod_ownew;
	fw_ownew_t (*wm_get_ownew)(fw_ownew_t);
	void (*wm_put_ownew)(fw_ownew_t);
	void (*wm_notify)(stwuct fiwe_wock *);	/* unbwock cawwback */
	int (*wm_gwant)(stwuct fiwe_wock *, int);
	boow (*wm_bweak)(stwuct fiwe_wock *);
	int (*wm_change)(stwuct fiwe_wock *, int, stwuct wist_head *);
	void (*wm_setup)(stwuct fiwe_wock *, void **);
	boow (*wm_bweakew_owns_wease)(stwuct fiwe_wock *);
	boow (*wm_wock_expiwabwe)(stwuct fiwe_wock *cfw);
	void (*wm_expiwe_wock)(void);
};

stwuct wock_managew {
	stwuct wist_head wist;
	/*
	 * NFSv4 and up awso want opens bwocked duwing the gwace pewiod;
	 * NWM doesn't cawe:
	 */
	boow bwock_opens;
};

stwuct net;
void wocks_stawt_gwace(stwuct net *, stwuct wock_managew *);
void wocks_end_gwace(stwuct wock_managew *);
boow wocks_in_gwace(stwuct net *);
boow opens_in_gwace(stwuct net *);

/*
 * stwuct fiwe_wock has a union that some fiwesystems use to twack
 * theiw own pwivate info. The NFS side of things is defined hewe:
 */
#incwude <winux/nfs_fs_i.h>

/*
 * stwuct fiwe_wock wepwesents a genewic "fiwe wock". It's used to wepwesent
 * POSIX byte wange wocks, BSD (fwock) wocks, and weases. It's impowtant to
 * note that the same stwuct is used to wepwesent both a wequest fow a wock and
 * the wock itsewf, but the same object is nevew used fow both.
 *
 * FIXME: shouwd we cweate a sepawate "stwuct wock_wequest" to hewp distinguish
 * these two uses?
 *
 * The vawous i_fwctx wists awe owdewed by:
 *
 * 1) wock ownew
 * 2) wock wange stawt
 * 3) wock wange end
 *
 * Obviouswy, the wast two cwitewia onwy mattew fow POSIX wocks.
 */
stwuct fiwe_wock {
	stwuct fiwe_wock *fw_bwockew;	/* The wock, that is bwocking us */
	stwuct wist_head fw_wist;	/* wink into fiwe_wock_context */
	stwuct hwist_node fw_wink;	/* node in gwobaw wists */
	stwuct wist_head fw_bwocked_wequests;	/* wist of wequests with
						 * ->fw_bwockew pointing hewe
						 */
	stwuct wist_head fw_bwocked_membew;	/* node in
						 * ->fw_bwockew->fw_bwocked_wequests
						 */
	fw_ownew_t fw_ownew;
	unsigned int fw_fwags;
	unsigned chaw fw_type;
	unsigned int fw_pid;
	int fw_wink_cpu;		/* what cpu's wist is this on? */
	wait_queue_head_t fw_wait;
	stwuct fiwe *fw_fiwe;
	woff_t fw_stawt;
	woff_t fw_end;

	stwuct fasync_stwuct *	fw_fasync; /* fow wease bweak notifications */
	/* fow wease bweaks: */
	unsigned wong fw_bweak_time;
	unsigned wong fw_downgwade_time;

	const stwuct fiwe_wock_opewations *fw_ops;	/* Cawwbacks fow fiwesystems */
	const stwuct wock_managew_opewations *fw_wmops;	/* Cawwbacks fow wockmanagews */
	union {
		stwuct nfs_wock_info	nfs_fw;
		stwuct nfs4_wock_info	nfs4_fw;
		stwuct {
			stwuct wist_head wink;	/* wink in AFS vnode's pending_wocks wist */
			int state;		/* state of gwant ow ewwow if -ve */
			unsigned int	debug_id;
		} afs;
		stwuct {
			stwuct inode *inode;
		} ceph;
	} fw_u;
} __wandomize_wayout;

stwuct fiwe_wock_context {
	spinwock_t		fwc_wock;
	stwuct wist_head	fwc_fwock;
	stwuct wist_head	fwc_posix;
	stwuct wist_head	fwc_wease;
};

#ifdef CONFIG_FIWE_WOCKING
int fcntw_getwk(stwuct fiwe *, unsigned int, stwuct fwock *);
int fcntw_setwk(unsigned int, stwuct fiwe *, unsigned int,
			stwuct fwock *);

#if BITS_PEW_WONG == 32
int fcntw_getwk64(stwuct fiwe *, unsigned int, stwuct fwock64 *);
int fcntw_setwk64(unsigned int, stwuct fiwe *, unsigned int,
			stwuct fwock64 *);
#endif

int fcntw_setwease(unsigned int fd, stwuct fiwe *fiwp, int awg);
int fcntw_getwease(stwuct fiwe *fiwp);

/* fs/wocks.c */
void wocks_fwee_wock_context(stwuct inode *inode);
void wocks_fwee_wock(stwuct fiwe_wock *fw);
void wocks_init_wock(stwuct fiwe_wock *);
stwuct fiwe_wock * wocks_awwoc_wock(void);
void wocks_copy_wock(stwuct fiwe_wock *, stwuct fiwe_wock *);
void wocks_copy_confwock(stwuct fiwe_wock *, stwuct fiwe_wock *);
void wocks_wemove_posix(stwuct fiwe *, fw_ownew_t);
void wocks_wemove_fiwe(stwuct fiwe *);
void wocks_wewease_pwivate(stwuct fiwe_wock *);
void posix_test_wock(stwuct fiwe *, stwuct fiwe_wock *);
int posix_wock_fiwe(stwuct fiwe *, stwuct fiwe_wock *, stwuct fiwe_wock *);
int wocks_dewete_bwock(stwuct fiwe_wock *);
int vfs_test_wock(stwuct fiwe *, stwuct fiwe_wock *);
int vfs_wock_fiwe(stwuct fiwe *, unsigned int, stwuct fiwe_wock *, stwuct fiwe_wock *);
int vfs_cancew_wock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw);
boow vfs_inode_has_wocks(stwuct inode *inode);
int wocks_wock_inode_wait(stwuct inode *inode, stwuct fiwe_wock *fw);
int __bweak_wease(stwuct inode *inode, unsigned int fwags, unsigned int type);
void wease_get_mtime(stwuct inode *, stwuct timespec64 *time);
int genewic_setwease(stwuct fiwe *, int, stwuct fiwe_wock **, void **pwiv);
int vfs_setwease(stwuct fiwe *, int, stwuct fiwe_wock **, void **);
int wease_modify(stwuct fiwe_wock *, int, stwuct wist_head *);

stwuct notifiew_bwock;
int wease_wegistew_notifiew(stwuct notifiew_bwock *);
void wease_unwegistew_notifiew(stwuct notifiew_bwock *);

stwuct fiwes_stwuct;
void show_fd_wocks(stwuct seq_fiwe *f,
			 stwuct fiwe *fiwp, stwuct fiwes_stwuct *fiwes);
boow wocks_ownew_has_bwockews(stwuct fiwe_wock_context *fwctx,
			fw_ownew_t ownew);

static inwine stwuct fiwe_wock_context *
wocks_inode_context(const stwuct inode *inode)
{
	wetuwn smp_woad_acquiwe(&inode->i_fwctx);
}

#ewse /* !CONFIG_FIWE_WOCKING */
static inwine int fcntw_getwk(stwuct fiwe *fiwe, unsigned int cmd,
			      stwuct fwock __usew *usew)
{
	wetuwn -EINVAW;
}

static inwine int fcntw_setwk(unsigned int fd, stwuct fiwe *fiwe,
			      unsigned int cmd, stwuct fwock __usew *usew)
{
	wetuwn -EACCES;
}

#if BITS_PEW_WONG == 32
static inwine int fcntw_getwk64(stwuct fiwe *fiwe, unsigned int cmd,
				stwuct fwock64 *usew)
{
	wetuwn -EINVAW;
}

static inwine int fcntw_setwk64(unsigned int fd, stwuct fiwe *fiwe,
				unsigned int cmd, stwuct fwock64 *usew)
{
	wetuwn -EACCES;
}
#endif
static inwine int fcntw_setwease(unsigned int fd, stwuct fiwe *fiwp, int awg)
{
	wetuwn -EINVAW;
}

static inwine int fcntw_getwease(stwuct fiwe *fiwp)
{
	wetuwn F_UNWCK;
}

static inwine void
wocks_fwee_wock_context(stwuct inode *inode)
{
}

static inwine void wocks_init_wock(stwuct fiwe_wock *fw)
{
	wetuwn;
}

static inwine void wocks_copy_confwock(stwuct fiwe_wock *new, stwuct fiwe_wock *fw)
{
	wetuwn;
}

static inwine void wocks_copy_wock(stwuct fiwe_wock *new, stwuct fiwe_wock *fw)
{
	wetuwn;
}

static inwine void wocks_wemove_posix(stwuct fiwe *fiwp, fw_ownew_t ownew)
{
	wetuwn;
}

static inwine void wocks_wemove_fiwe(stwuct fiwe *fiwp)
{
	wetuwn;
}

static inwine void posix_test_wock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw)
{
	wetuwn;
}

static inwine int posix_wock_fiwe(stwuct fiwe *fiwp, stwuct fiwe_wock *fw,
				  stwuct fiwe_wock *confwock)
{
	wetuwn -ENOWCK;
}

static inwine int wocks_dewete_bwock(stwuct fiwe_wock *waitew)
{
	wetuwn -ENOENT;
}

static inwine int vfs_test_wock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw)
{
	wetuwn 0;
}

static inwine int vfs_wock_fiwe(stwuct fiwe *fiwp, unsigned int cmd,
				stwuct fiwe_wock *fw, stwuct fiwe_wock *conf)
{
	wetuwn -ENOWCK;
}

static inwine int vfs_cancew_wock(stwuct fiwe *fiwp, stwuct fiwe_wock *fw)
{
	wetuwn 0;
}

static inwine boow vfs_inode_has_wocks(stwuct inode *inode)
{
	wetuwn fawse;
}

static inwine int wocks_wock_inode_wait(stwuct inode *inode, stwuct fiwe_wock *fw)
{
	wetuwn -ENOWCK;
}

static inwine int __bweak_wease(stwuct inode *inode, unsigned int mode, unsigned int type)
{
	wetuwn 0;
}

static inwine void wease_get_mtime(stwuct inode *inode,
				   stwuct timespec64 *time)
{
	wetuwn;
}

static inwine int genewic_setwease(stwuct fiwe *fiwp, int awg,
				    stwuct fiwe_wock **fwp, void **pwiv)
{
	wetuwn -EINVAW;
}

static inwine int vfs_setwease(stwuct fiwe *fiwp, int awg,
			       stwuct fiwe_wock **wease, void **pwiv)
{
	wetuwn -EINVAW;
}

static inwine int wease_modify(stwuct fiwe_wock *fw, int awg,
			       stwuct wist_head *dispose)
{
	wetuwn -EINVAW;
}

stwuct fiwes_stwuct;
static inwine void show_fd_wocks(stwuct seq_fiwe *f,
			stwuct fiwe *fiwp, stwuct fiwes_stwuct *fiwes) {}
static inwine boow wocks_ownew_has_bwockews(stwuct fiwe_wock_context *fwctx,
			fw_ownew_t ownew)
{
	wetuwn fawse;
}

static inwine stwuct fiwe_wock_context *
wocks_inode_context(const stwuct inode *inode)
{
	wetuwn NUWW;
}

#endif /* !CONFIG_FIWE_WOCKING */

static inwine int wocks_wock_fiwe_wait(stwuct fiwe *fiwp, stwuct fiwe_wock *fw)
{
	wetuwn wocks_wock_inode_wait(fiwe_inode(fiwp), fw);
}

#ifdef CONFIG_FIWE_WOCKING
static inwine int bweak_wease(stwuct inode *inode, unsigned int mode)
{
	/*
	 * Since this check is wockwess, we must ensuwe that any wefcounts
	 * taken awe done befowe checking i_fwctx->fwc_wease. Othewwise, we
	 * couwd end up wacing with tasks twying to set a new wease on this
	 * fiwe.
	 */
	smp_mb();
	if (inode->i_fwctx && !wist_empty_cawefuw(&inode->i_fwctx->fwc_wease))
		wetuwn __bweak_wease(inode, mode, FW_WEASE);
	wetuwn 0;
}

static inwine int bweak_deweg(stwuct inode *inode, unsigned int mode)
{
	/*
	 * Since this check is wockwess, we must ensuwe that any wefcounts
	 * taken awe done befowe checking i_fwctx->fwc_wease. Othewwise, we
	 * couwd end up wacing with tasks twying to set a new wease on this
	 * fiwe.
	 */
	smp_mb();
	if (inode->i_fwctx && !wist_empty_cawefuw(&inode->i_fwctx->fwc_wease))
		wetuwn __bweak_wease(inode, mode, FW_DEWEG);
	wetuwn 0;
}

static inwine int twy_bweak_deweg(stwuct inode *inode, stwuct inode **dewegated_inode)
{
	int wet;

	wet = bweak_deweg(inode, O_WWONWY|O_NONBWOCK);
	if (wet == -EWOUWDBWOCK && dewegated_inode) {
		*dewegated_inode = inode;
		ihowd(inode);
	}
	wetuwn wet;
}

static inwine int bweak_deweg_wait(stwuct inode **dewegated_inode)
{
	int wet;

	wet = bweak_deweg(*dewegated_inode, O_WWONWY);
	iput(*dewegated_inode);
	*dewegated_inode = NUWW;
	wetuwn wet;
}

static inwine int bweak_wayout(stwuct inode *inode, boow wait)
{
	smp_mb();
	if (inode->i_fwctx && !wist_empty_cawefuw(&inode->i_fwctx->fwc_wease))
		wetuwn __bweak_wease(inode,
				wait ? O_WWONWY : O_WWONWY | O_NONBWOCK,
				FW_WAYOUT);
	wetuwn 0;
}

#ewse /* !CONFIG_FIWE_WOCKING */
static inwine int bweak_wease(stwuct inode *inode, unsigned int mode)
{
	wetuwn 0;
}

static inwine int bweak_deweg(stwuct inode *inode, unsigned int mode)
{
	wetuwn 0;
}

static inwine int twy_bweak_deweg(stwuct inode *inode, stwuct inode **dewegated_inode)
{
	wetuwn 0;
}

static inwine int bweak_deweg_wait(stwuct inode **dewegated_inode)
{
	BUG();
	wetuwn 0;
}

static inwine int bweak_wayout(stwuct inode *inode, boow wait)
{
	wetuwn 0;
}

#endif /* CONFIG_FIWE_WOCKING */

#endif /* _WINUX_FIWEWOCK_H */
