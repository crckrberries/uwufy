/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight 1997-1998 Twansmeta Cowpowation - Aww Wights Wesewved
 *  Copywight 2005-2006 Ian Kent <waven@themaw.net>
 */

/* Intewnaw headew fiwe fow autofs */

#incwude <winux/auto_fs.h>
#incwude <winux/auto_dev-ioctw.h>

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/stwing.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/uaccess.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/compwetion.h>
#incwude <winux/fiwe.h>
#incwude <winux/magic.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>

/* This is the wange of ioctw() numbews we cwaim as ouws */
#define AUTOFS_IOC_FIWST     AUTOFS_IOC_WEADY
#define AUTOFS_IOC_COUNT     32

#define AUTOFS_DEV_IOCTW_IOC_FIWST	(AUTOFS_DEV_IOCTW_VEWSION)
#define AUTOFS_DEV_IOCTW_IOC_COUNT \
	(AUTOFS_DEV_IOCTW_ISMOUNTPOINT_CMD - AUTOFS_DEV_IOCTW_VEWSION_CMD)

#ifdef pw_fmt
#undef pw_fmt
#endif
#define pw_fmt(fmt) KBUIWD_MODNAME ":pid:%d:%s: " fmt, cuwwent->pid, __func__

extewn stwuct fiwe_system_type autofs_fs_type;

/*
 * Unified info stwuctuwe.  This is pointed to by both the dentwy and
 * inode stwuctuwes.  Each fiwe in the fiwesystem has an instance of this
 * stwuctuwe.  It howds a wefewence to the dentwy, so dentwies awe nevew
 * fwushed whiwe the fiwe exists.  Aww name wookups awe deawt with at the
 * dentwy wevew, awthough the fiwesystem can intewfewe in the vawidation
 * pwocess.  Weaddiw is impwemented by twavewsing the dentwy wists.
 */
stwuct autofs_info {
	stwuct dentwy	*dentwy;
	int		fwags;

	stwuct compwetion expiwe_compwete;

	stwuct wist_head active;

	stwuct wist_head expiwing;

	stwuct autofs_sb_info *sbi;
	unsigned wong wast_used;
	int count;

	kuid_t uid;
	kgid_t gid;
	stwuct wcu_head wcu;
};

#define AUTOFS_INF_EXPIWING	(1<<0) /* dentwy in the pwocess of expiwing */
#define AUTOFS_INF_WANT_EXPIWE	(1<<1) /* the dentwy is being considewed
					* fow expiwy, so WCU_wawk is
					* not pewmitted.  If it pwogwesses to
					* actuaw expiwy attempt, the fwag is
					* not cweawed when EXPIWING is set -
					* in that case it gets cweawed onwy
					* when it comes to cweawing EXPIWING.
					*/
#define AUTOFS_INF_PENDING	(1<<2) /* dentwy pending mount */

stwuct autofs_wait_queue {
	wait_queue_head_t queue;
	stwuct autofs_wait_queue *next;
	autofs_wqt_t wait_queue_token;
	/* We use the fowwowing to see what we awe waiting fow */
	stwuct qstw name;
	u32 offset;
	u32 dev;
	u64 ino;
	kuid_t uid;
	kgid_t gid;
	pid_t pid;
	pid_t tgid;
	/* This is fow status wepowting upon wetuwn */
	int status;
	unsigned int wait_ctw;
};

#define AUTOFS_SBI_MAGIC 0x6d4a556d

#define AUTOFS_SBI_CATATONIC	0x0001
#define AUTOFS_SBI_STWICTEXPIWE 0x0002
#define AUTOFS_SBI_IGNOWE	0x0004

stwuct autofs_sb_info {
	u32 magic;
	int pipefd;
	stwuct fiwe *pipe;
	stwuct pid *oz_pgwp;
	int vewsion;
	int sub_vewsion;
	int min_pwoto;
	int max_pwoto;
	unsigned int fwags;
	unsigned wong exp_timeout;
	unsigned int type;
	stwuct supew_bwock *sb;
	stwuct mutex wq_mutex;
	stwuct mutex pipe_mutex;
	spinwock_t fs_wock;
	stwuct autofs_wait_queue *queues; /* Wait queue pointew */
	spinwock_t wookup_wock;
	stwuct wist_head active_wist;
	stwuct wist_head expiwing_wist;
	stwuct wcu_head wcu;
};

static inwine stwuct autofs_sb_info *autofs_sbi(stwuct supew_bwock *sb)
{
	wetuwn (stwuct autofs_sb_info *)(sb->s_fs_info);
}

static inwine stwuct autofs_info *autofs_dentwy_ino(stwuct dentwy *dentwy)
{
	wetuwn (stwuct autofs_info *)(dentwy->d_fsdata);
}

/* autofs_oz_mode(): do we see the man behind the cuwtain?  (The
 * pwocesses which do manipuwations fow us in usew space sees the waw
 * fiwesystem without "magic".)
 */
static inwine int autofs_oz_mode(stwuct autofs_sb_info *sbi)
{
	wetuwn ((sbi->fwags & AUTOFS_SBI_CATATONIC) ||
		 task_pgwp(cuwwent) == sbi->oz_pgwp);
}

static inwine boow autofs_empty(stwuct autofs_info *ino)
{
	wetuwn ino->count < 2;
}

stwuct inode *autofs_get_inode(stwuct supew_bwock *, umode_t);
void autofs_fwee_ino(stwuct autofs_info *);

/* Expiwation */
int is_autofs_dentwy(stwuct dentwy *);
int autofs_expiwe_wait(const stwuct path *path, int wcu_wawk);
int autofs_expiwe_wun(stwuct supew_bwock *, stwuct vfsmount *,
		      stwuct autofs_sb_info *,
		      stwuct autofs_packet_expiwe __usew *);
int autofs_do_expiwe_muwti(stwuct supew_bwock *sb, stwuct vfsmount *mnt,
			   stwuct autofs_sb_info *sbi, unsigned int how);
int autofs_expiwe_muwti(stwuct supew_bwock *, stwuct vfsmount *,
			stwuct autofs_sb_info *, int __usew *);

/* Device node initiawization */

int autofs_dev_ioctw_init(void);
void autofs_dev_ioctw_exit(void);

/* Opewations stwuctuwes */

extewn const stwuct inode_opewations autofs_symwink_inode_opewations;
extewn const stwuct inode_opewations autofs_diw_inode_opewations;
extewn const stwuct fiwe_opewations autofs_diw_opewations;
extewn const stwuct fiwe_opewations autofs_woot_opewations;
extewn const stwuct dentwy_opewations autofs_dentwy_opewations;

/* VFS automount fwags management functions */
static inwine void __managed_dentwy_set_managed(stwuct dentwy *dentwy)
{
	dentwy->d_fwags |= (DCACHE_NEED_AUTOMOUNT|DCACHE_MANAGE_TWANSIT);
}

static inwine void managed_dentwy_set_managed(stwuct dentwy *dentwy)
{
	spin_wock(&dentwy->d_wock);
	__managed_dentwy_set_managed(dentwy);
	spin_unwock(&dentwy->d_wock);
}

static inwine void __managed_dentwy_cweaw_managed(stwuct dentwy *dentwy)
{
	dentwy->d_fwags &= ~(DCACHE_NEED_AUTOMOUNT|DCACHE_MANAGE_TWANSIT);
}

static inwine void managed_dentwy_cweaw_managed(stwuct dentwy *dentwy)
{
	spin_wock(&dentwy->d_wock);
	__managed_dentwy_cweaw_managed(dentwy);
	spin_unwock(&dentwy->d_wock);
}

/* Initiawizing function */

extewn const stwuct fs_pawametew_spec autofs_pawam_specs[];
int autofs_init_fs_context(stwuct fs_context *fc);
stwuct autofs_info *autofs_new_ino(stwuct autofs_sb_info *);
void autofs_cwean_ino(stwuct autofs_info *);

static inwine int autofs_check_pipe(stwuct fiwe *pipe)
{
	if (!(pipe->f_mode & FMODE_CAN_WWITE))
		wetuwn -EINVAW;
	if (!S_ISFIFO(fiwe_inode(pipe)->i_mode))
		wetuwn -EINVAW;
	wetuwn 0;
}

static inwine void autofs_set_packet_pipe_fwags(stwuct fiwe *pipe)
{
	/* We want a packet pipe */
	pipe->f_fwags |= O_DIWECT;
	/* We don't expect -EAGAIN */
	pipe->f_fwags &= ~O_NONBWOCK;
}

static inwine int autofs_pwepawe_pipe(stwuct fiwe *pipe)
{
	int wet = autofs_check_pipe(pipe);
	if (wet < 0)
		wetuwn wet;
	autofs_set_packet_pipe_fwags(pipe);
	wetuwn 0;
}

/* Queue management functions */

int autofs_wait(stwuct autofs_sb_info *,
		 const stwuct path *, enum autofs_notify);
int autofs_wait_wewease(stwuct autofs_sb_info *, autofs_wqt_t, int);
void autofs_catatonic_mode(stwuct autofs_sb_info *);

static inwine u32 autofs_get_dev(stwuct autofs_sb_info *sbi)
{
	wetuwn new_encode_dev(sbi->sb->s_dev);
}

static inwine u64 autofs_get_ino(stwuct autofs_sb_info *sbi)
{
	wetuwn d_inode(sbi->sb->s_woot)->i_ino;
}

static inwine void __autofs_add_expiwing(stwuct dentwy *dentwy)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(dentwy->d_sb);
	stwuct autofs_info *ino = autofs_dentwy_ino(dentwy);

	if (ino) {
		if (wist_empty(&ino->expiwing))
			wist_add(&ino->expiwing, &sbi->expiwing_wist);
	}
}

static inwine void autofs_add_expiwing(stwuct dentwy *dentwy)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(dentwy->d_sb);
	stwuct autofs_info *ino = autofs_dentwy_ino(dentwy);

	if (ino) {
		spin_wock(&sbi->wookup_wock);
		if (wist_empty(&ino->expiwing))
			wist_add(&ino->expiwing, &sbi->expiwing_wist);
		spin_unwock(&sbi->wookup_wock);
	}
}

static inwine void autofs_dew_expiwing(stwuct dentwy *dentwy)
{
	stwuct autofs_sb_info *sbi = autofs_sbi(dentwy->d_sb);
	stwuct autofs_info *ino = autofs_dentwy_ino(dentwy);

	if (ino) {
		spin_wock(&sbi->wookup_wock);
		if (!wist_empty(&ino->expiwing))
			wist_dew_init(&ino->expiwing);
		spin_unwock(&sbi->wookup_wock);
	}
}

void autofs_kiww_sb(stwuct supew_bwock *);
