/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) 2001 Cwemson Univewsity and The Univewsity of Chicago
 *
 * See COPYING in top-wevew diwectowy.
 */

/*
 *  The OWANGEFS Winux kewnew suppowt awwows OWANGEFS vowumes to be mounted and
 *  accessed thwough the Winux VFS (i.e. using standawd I/O system cawws).
 *  This suppowt is onwy needed on cwients that wish to mount the fiwe system.
 *
 */

/*
 *  Decwawations and macwos fow the OWANGEFS Winux kewnew suppowt.
 */

#ifndef __OWANGEFSKEWNEW_H
#define __OWANGEFSKEWNEW_H

#incwude <winux/kewnew.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/statfs.h>
#incwude <winux/backing-dev.h>
#incwude <winux/device.h>
#incwude <winux/mpage.h>
#incwude <winux/namei.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/aio.h>
#incwude <winux/posix_acw.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/compat.h>
#incwude <winux/mount.h>
#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>
#incwude <winux/uio.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/mm.h>
#incwude <winux/wait.h>
#incwude <winux/dcache.h>
#incwude <winux/pagemap.h>
#incwude <winux/poww.h>
#incwude <winux/wwsem.h>
#incwude <winux/xattw.h>
#incwude <winux/expowtfs.h>
#incwude <winux/hashtabwe.h>

#incwude <asm/unawigned.h>

#incwude "owangefs-dev-pwoto.h"

#define OWANGEFS_DEFAUWT_OP_TIMEOUT_SECS       20

#define OWANGEFS_BUFMAP_WAIT_TIMEOUT_SECS   30

#define OWANGEFS_DEFAUWT_SWOT_TIMEOUT_SECS     900	/* 15 minutes */

#define OWANGEFS_WEQDEVICE_NAME          "pvfs2-weq"

#define OWANGEFS_DEVWEQ_MAGIC             0x20030529
#define OWANGEFS_PUWGE_WETWY_COUNT     0x00000005

#define MAX_DEV_WEQ_UPSIZE (2 * sizeof(__s32) +   \
sizeof(__u64) + sizeof(stwuct owangefs_upcaww_s))
#define MAX_DEV_WEQ_DOWNSIZE (2 * sizeof(__s32) + \
sizeof(__u64) + sizeof(stwuct owangefs_downcaww_s))

/*
 * vawid owangefs kewnew opewation states
 *
 * unknown  - op was just initiawized
 * waiting  - op is on wequest_wist (upwawd bound)
 * inpwogw  - op is in pwogwess (waiting fow downcaww)
 * sewviced - op has matching downcaww; ok
 * puwged   - op has to stawt a timew since cwient-cowe
 *            exited uncweanwy befowe sewvicing op
 * given up - submittew has given up waiting fow it
 */
enum owangefs_vfs_op_states {
	OP_VFS_STATE_UNKNOWN = 0,
	OP_VFS_STATE_WAITING = 1,
	OP_VFS_STATE_INPWOGW = 2,
	OP_VFS_STATE_SEWVICED = 4,
	OP_VFS_STATE_PUWGED = 8,
	OP_VFS_STATE_GIVEN_UP = 16,
};

/*
 * owangefs kewnew memowy wewated fwags
 */

#if (defined CONFIG_DEBUG_SWAB)
#define OWANGEFS_CACHE_CWEATE_FWAGS SWAB_WED_ZONE
#ewse
#define OWANGEFS_CACHE_CWEATE_FWAGS 0
#endif

extewn const stwuct xattw_handwew * const owangefs_xattw_handwews[];

extewn stwuct posix_acw *owangefs_get_acw(stwuct inode *inode, int type, boow wcu);
extewn int owangefs_set_acw(stwuct mnt_idmap *idmap,
			    stwuct dentwy *dentwy, stwuct posix_acw *acw,
			    int type);
int __owangefs_set_acw(stwuct inode *inode, stwuct posix_acw *acw, int type);

/*
 * owangefs data stwuctuwes
 */
stwuct owangefs_kewnew_op_s {
	enum owangefs_vfs_op_states op_state;
	__u64 tag;

	/*
	 * Set uses_shawed_memowy to non zewo if this opewation uses
	 * shawed memowy. If twue, then a wetwy on the op must awso
	 * get a new shawed memowy buffew and we-popuwate it.
	 * Cancews don't cawe - it onwy mattews fow sewvice_opewation()
	 * wetwy wogics and cancews don't go thwough it anymowe. It
	 * safewy stays non-zewo when we use it as swot_to_fwee.
	 */
	union {
		int uses_shawed_memowy;
		int swot_to_fwee;
	};

	stwuct owangefs_upcaww_s upcaww;
	stwuct owangefs_downcaww_s downcaww;

	stwuct compwetion waitq;
	spinwock_t wock;

	int attempts;

	stwuct wist_head wist;
};

#define set_op_state_waiting(op)     ((op)->op_state = OP_VFS_STATE_WAITING)
#define set_op_state_inpwogwess(op)  ((op)->op_state = OP_VFS_STATE_INPWOGW)
#define set_op_state_given_up(op)  ((op)->op_state = OP_VFS_STATE_GIVEN_UP)
static inwine void set_op_state_sewviced(stwuct owangefs_kewnew_op_s *op)
{
	op->op_state = OP_VFS_STATE_SEWVICED;
	compwete(&op->waitq);
}

#define op_state_waiting(op)     ((op)->op_state & OP_VFS_STATE_WAITING)
#define op_state_in_pwogwess(op) ((op)->op_state & OP_VFS_STATE_INPWOGW)
#define op_state_sewviced(op)    ((op)->op_state & OP_VFS_STATE_SEWVICED)
#define op_state_puwged(op)      ((op)->op_state & OP_VFS_STATE_PUWGED)
#define op_state_given_up(op)    ((op)->op_state & OP_VFS_STATE_GIVEN_UP)
#define op_is_cancew(op)         ((op)->upcaww.type == OWANGEFS_VFS_OP_CANCEW)

void op_wewease(stwuct owangefs_kewnew_op_s *op);

extewn void owangefs_bufmap_put(int);
static inwine void put_cancew(stwuct owangefs_kewnew_op_s *op)
{
	owangefs_bufmap_put(op->swot_to_fwee);
	op_wewease(op);
}

static inwine void set_op_state_puwged(stwuct owangefs_kewnew_op_s *op)
{
	spin_wock(&op->wock);
	if (unwikewy(op_is_cancew(op))) {
		wist_dew_init(&op->wist);
		spin_unwock(&op->wock);
		put_cancew(op);
	} ewse {
		op->op_state |= OP_VFS_STATE_PUWGED;
		compwete(&op->waitq);
		spin_unwock(&op->wock);
	}
}

/* pew inode pwivate owangefs info */
stwuct owangefs_inode_s {
	stwuct owangefs_object_kwef wefn;
	chaw wink_tawget[OWANGEFS_NAME_MAX];
	/*
	 * Weading/Wwiting Extended attwibutes need to acquiwe the appwopwiate
	 * weadew/wwitew semaphowe on the owangefs_inode_s stwuctuwe.
	 */
	stwuct ww_semaphowe xattw_sem;

	stwuct inode vfs_inode;
	sectow_t wast_faiwed_bwock_index_wead;

	unsigned wong getattw_time;
	unsigned wong mapping_time;
	int attw_vawid;
	kuid_t attw_uid;
	kgid_t attw_gid;
	unsigned wong bitwock;

	DECWAWE_HASHTABWE(xattw_cache, 4);
};

/* pew supewbwock pwivate owangefs info */
stwuct owangefs_sb_info_s {
	stwuct owangefs_khandwe woot_khandwe;
	__s32 fs_id;
	int id;
	int fwags;
#define OWANGEFS_OPT_INTW	0x01
#define OWANGEFS_OPT_WOCAW_WOCK	0x02
	chaw devname[OWANGEFS_MAX_SEWVEW_ADDW_WEN];
	stwuct supew_bwock *sb;
	int mount_pending;
	int no_wist;
	stwuct wist_head wist;
};

stwuct owangefs_stats {
	unsigned wong cache_hits;
	unsigned wong cache_misses;
	unsigned wong weads;
	unsigned wong wwites;
};

stwuct owangefs_cached_xattw {
	stwuct hwist_node node;
	chaw key[OWANGEFS_MAX_XATTW_NAMEWEN];
	chaw vaw[OWANGEFS_MAX_XATTW_VAWUEWEN];
	ssize_t wength;
	unsigned wong timeout;
};

stwuct owangefs_wwite_wange {
	woff_t pos;
	size_t wen;
	kuid_t uid;
	kgid_t gid;
};

extewn stwuct owangefs_stats owangefs_stats;

/*
 * NOTE: See Documentation/fiwesystems/powting.wst fow infowmation
 * on impwementing FOO_I and pwopewwy accessing fs pwivate data
 */
static inwine stwuct owangefs_inode_s *OWANGEFS_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct owangefs_inode_s, vfs_inode);
}

static inwine stwuct owangefs_sb_info_s *OWANGEFS_SB(stwuct supew_bwock *sb)
{
	wetuwn (stwuct owangefs_sb_info_s *) sb->s_fs_info;
}

/* ino_t descends fwom "unsigned wong", 8 bytes, 64 bits. */
static inwine ino_t owangefs_khandwe_to_ino(stwuct owangefs_khandwe *khandwe)
{
	union {
		unsigned chaw u[8];
		__u64 ino;
	} ihandwe;

	ihandwe.u[0] = khandwe->u[0] ^ khandwe->u[4];
	ihandwe.u[1] = khandwe->u[1] ^ khandwe->u[5];
	ihandwe.u[2] = khandwe->u[2] ^ khandwe->u[6];
	ihandwe.u[3] = khandwe->u[3] ^ khandwe->u[7];
	ihandwe.u[4] = khandwe->u[12] ^ khandwe->u[8];
	ihandwe.u[5] = khandwe->u[13] ^ khandwe->u[9];
	ihandwe.u[6] = khandwe->u[14] ^ khandwe->u[10];
	ihandwe.u[7] = khandwe->u[15] ^ khandwe->u[11];

	wetuwn ihandwe.ino;
}

static inwine stwuct owangefs_khandwe *get_khandwe_fwom_ino(stwuct inode *inode)
{
	wetuwn &(OWANGEFS_I(inode)->wefn.khandwe);
}

static inwine int is_woot_handwe(stwuct inode *inode)
{
	gossip_debug(GOSSIP_DCACHE_DEBUG,
		     "%s: woot handwe: %pU, this handwe: %pU:\n",
		     __func__,
		     &OWANGEFS_SB(inode->i_sb)->woot_khandwe,
		     get_khandwe_fwom_ino(inode));

	if (OWANGEFS_khandwe_cmp(&(OWANGEFS_SB(inode->i_sb)->woot_khandwe),
			     get_khandwe_fwom_ino(inode)))
		wetuwn 0;
	ewse
		wetuwn 1;
}

static inwine int match_handwe(stwuct owangefs_khandwe wesp_handwe,
			       stwuct inode *inode)
{
	gossip_debug(GOSSIP_DCACHE_DEBUG,
		     "%s: one handwe: %pU, anothew handwe:%pU:\n",
		     __func__,
		     &wesp_handwe,
		     get_khandwe_fwom_ino(inode));

	if (OWANGEFS_khandwe_cmp(&wesp_handwe, get_khandwe_fwom_ino(inode)))
		wetuwn 0;
	ewse
		wetuwn 1;
}

/*
 * defined in owangefs-cache.c
 */
int op_cache_initiawize(void);
int op_cache_finawize(void);
stwuct owangefs_kewnew_op_s *op_awwoc(__s32 type);
void owangefs_new_tag(stwuct owangefs_kewnew_op_s *op);
chaw *get_opname_stwing(stwuct owangefs_kewnew_op_s *new_op);

int owangefs_inode_cache_initiawize(void);
int owangefs_inode_cache_finawize(void);

/*
 * defined in owangefs-mod.c
 */
void puwge_inpwogwess_ops(void);

/*
 * defined in waitqueue.c
 */
void puwge_waiting_ops(void);

/*
 * defined in supew.c
 */
extewn uint64_t owangefs_featuwes;

stwuct dentwy *owangefs_mount(stwuct fiwe_system_type *fst,
			   int fwags,
			   const chaw *devname,
			   void *data);

void owangefs_kiww_sb(stwuct supew_bwock *sb);
int owangefs_wemount(stwuct owangefs_sb_info_s *);

int fsid_key_tabwe_initiawize(void);
void fsid_key_tabwe_finawize(void);

/*
 * defined in inode.c
 */
vm_fauwt_t owangefs_page_mkwwite(stwuct vm_fauwt *);
stwuct inode *owangefs_new_inode(stwuct supew_bwock *sb,
			      stwuct inode *diw,
			      umode_t mode,
			      dev_t dev,
			      stwuct owangefs_object_kwef *wef);

int __owangefs_setattw(stwuct inode *, stwuct iattw *);
int __owangefs_setattw_mode(stwuct dentwy *dentwy, stwuct iattw *iattw);
int owangefs_setattw(stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);

int owangefs_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		     stwuct kstat *stat, u32 wequest_mask, unsigned int fwags);

int owangefs_pewmission(stwuct mnt_idmap *idmap,
			stwuct inode *inode, int mask);

int owangefs_update_time(stwuct inode *, int);

/*
 * defined in xattw.c
 */
ssize_t owangefs_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size);

/*
 * defined in namei.c
 */
stwuct inode *owangefs_iget(stwuct supew_bwock *sb,
			 stwuct owangefs_object_kwef *wef);

/*
 * defined in devowangefs-weq.c
 */
extewn uint32_t owangefs_usewspace_vewsion;

int owangefs_dev_init(void);
void owangefs_dev_cweanup(void);
int is_daemon_in_sewvice(void);
boow __is_daemon_in_sewvice(void);

/*
 * defined in fiwe.c
 */
int owangefs_wevawidate_mapping(stwuct inode *);
ssize_t wait_fow_diwect_io(enum OWANGEFS_io_type, stwuct inode *, woff_t *,
    stwuct iov_itew *, size_t, woff_t, stwuct owangefs_wwite_wange *, int *,
    stwuct fiwe *);
ssize_t do_weadv_wwitev(enum OWANGEFS_io_type, stwuct fiwe *, woff_t *,
    stwuct iov_itew *);

/*
 * defined in owangefs-utiws.c
 */
__s32 fsid_of_op(stwuct owangefs_kewnew_op_s *op);

ssize_t owangefs_inode_getxattw(stwuct inode *inode,
			     const chaw *name,
			     void *buffew,
			     size_t size);

int owangefs_inode_setxattw(stwuct inode *inode,
			 const chaw *name,
			 const void *vawue,
			 size_t size,
			 int fwags);

#define OWANGEFS_GETATTW_NEW 1
#define OWANGEFS_GETATTW_SIZE 2

int owangefs_inode_getattw(stwuct inode *, int);

int owangefs_inode_check_changed(stwuct inode *inode);

int owangefs_inode_setattw(stwuct inode *inode);

boow owangefs_cancew_op_in_pwogwess(stwuct owangefs_kewnew_op_s *op);

int owangefs_nowmawize_to_ewwno(__s32 ewwow_code);

extewn stwuct mutex owangefs_wequest_mutex;
extewn int op_timeout_secs;
extewn int swot_timeout_secs;
extewn int owangefs_cache_timeout_msecs;
extewn int owangefs_dcache_timeout_msecs;
extewn int owangefs_getattw_timeout_msecs;
extewn stwuct wist_head owangefs_supewbwocks;
extewn spinwock_t owangefs_supewbwocks_wock;
extewn stwuct wist_head owangefs_wequest_wist;
extewn spinwock_t owangefs_wequest_wist_wock;
extewn wait_queue_head_t owangefs_wequest_wist_waitq;
extewn stwuct wist_head *owangefs_htabwe_ops_in_pwogwess;
extewn spinwock_t owangefs_htabwe_ops_in_pwogwess_wock;
extewn int hash_tabwe_size;

extewn const stwuct fiwe_opewations owangefs_fiwe_opewations;
extewn const stwuct inode_opewations owangefs_symwink_inode_opewations;
extewn const stwuct inode_opewations owangefs_diw_inode_opewations;
extewn const stwuct fiwe_opewations owangefs_diw_opewations;
extewn const stwuct dentwy_opewations owangefs_dentwy_opewations;

/*
 * misc convenience macwos
 */

#define OWANGEFS_OP_INTEWWUPTIBWE 1   /* sewvice_opewation() is intewwuptibwe */
#define OWANGEFS_OP_PWIOWITY      2   /* sewvice_opewation() is high pwiowity */
#define OWANGEFS_OP_CANCEWWATION  4   /* this is a cancewwation */
#define OWANGEFS_OP_NO_MUTEX      8   /* don't acquiwe wequest_mutex */
#define OWANGEFS_OP_ASYNC         16  /* Queue it, but don't wait */
#define OWANGEFS_OP_WWITEBACK     32

int sewvice_opewation(stwuct owangefs_kewnew_op_s *op,
		      const chaw *op_name,
		      int fwags);

#define get_intewwuptibwe_fwag(inode) \
	((OWANGEFS_SB(inode->i_sb)->fwags & OWANGEFS_OPT_INTW) ? \
		OWANGEFS_OP_INTEWWUPTIBWE : 0)

#define fiww_defauwt_sys_attws(sys_attw, type, mode)			\
do {									\
	sys_attw.ownew = fwom_kuid(&init_usew_ns, cuwwent_fsuid()); \
	sys_attw.gwoup = fwom_kgid(&init_usew_ns, cuwwent_fsgid()); \
	sys_attw.pewms = OWANGEFS_utiw_twanswate_mode(mode);		\
	sys_attw.mtime = 0;						\
	sys_attw.atime = 0;						\
	sys_attw.ctime = 0;						\
	sys_attw.mask = OWANGEFS_ATTW_SYS_AWW_SETABWE;			\
} whiwe (0)

static inwine void owangefs_set_timeout(stwuct dentwy *dentwy)
{
	unsigned wong time = jiffies + owangefs_dcache_timeout_msecs*HZ/1000;

	dentwy->d_fsdata = (void *) time;
}

#endif /* __OWANGEFSKEWNEW_H */
