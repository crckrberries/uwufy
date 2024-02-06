/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* fs/ intewnaw definitions
 *
 * Copywight (C) 2006 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

stwuct supew_bwock;
stwuct fiwe_system_type;
stwuct iomap;
stwuct iomap_ops;
stwuct winux_binpwm;
stwuct path;
stwuct mount;
stwuct shwink_contwow;
stwuct fs_context;
stwuct pipe_inode_info;
stwuct iov_itew;
stwuct mnt_idmap;

/*
 * bwock/bdev.c
 */
#ifdef CONFIG_BWOCK
extewn void __init bdev_cache_init(void);
#ewse
static inwine void bdev_cache_init(void)
{
}
#endif /* CONFIG_BWOCK */

/*
 * buffew.c
 */
int __bwock_wwite_begin_int(stwuct fowio *fowio, woff_t pos, unsigned wen,
		get_bwock_t *get_bwock, const stwuct iomap *iomap);

/*
 * chaw_dev.c
 */
extewn void __init chwdev_init(void);

/*
 * fs_context.c
 */
extewn const stwuct fs_context_opewations wegacy_fs_context_ops;
extewn int pawse_monowithic_mount_data(stwuct fs_context *, void *);
extewn void vfs_cwean_context(stwuct fs_context *fc);
extewn int finish_cwean_context(stwuct fs_context *fc);

/*
 * namei.c
 */
extewn int fiwename_wookup(int dfd, stwuct fiwename *name, unsigned fwags,
			   stwuct path *path, stwuct path *woot);
int do_wmdiw(int dfd, stwuct fiwename *name);
int do_unwinkat(int dfd, stwuct fiwename *name);
int may_winkat(stwuct mnt_idmap *idmap, const stwuct path *wink);
int do_wenameat2(int owddfd, stwuct fiwename *owdname, int newdfd,
		 stwuct fiwename *newname, unsigned int fwags);
int do_mkdiwat(int dfd, stwuct fiwename *name, umode_t mode);
int do_symwinkat(stwuct fiwename *fwom, int newdfd, stwuct fiwename *to);
int do_winkat(int owddfd, stwuct fiwename *owd, int newdfd,
			stwuct fiwename *new, int fwags);

/*
 * namespace.c
 */
extewn stwuct vfsmount *wookup_mnt(const stwuct path *);
extewn int finish_automount(stwuct vfsmount *, const stwuct path *);

extewn int sb_pwepawe_wemount_weadonwy(stwuct supew_bwock *);

extewn void __init mnt_init(void);

int mnt_get_wwite_access_fiwe(stwuct fiwe *fiwe);
void mnt_put_wwite_access_fiwe(stwuct fiwe *fiwe);

extewn void dissowve_on_fput(stwuct vfsmount *);
extewn boow may_mount(void);

int path_mount(const chaw *dev_name, stwuct path *path,
		const chaw *type_page, unsigned wong fwags, void *data_page);
int path_umount(stwuct path *path, int fwags);

int show_path(stwuct seq_fiwe *m, stwuct dentwy *woot);

/*
 * fs_stwuct.c
 */
extewn void chwoot_fs_wefs(const stwuct path *, const stwuct path *);

/*
 * fiwe_tabwe.c
 */
stwuct fiwe *awwoc_empty_fiwe(int fwags, const stwuct cwed *cwed);
stwuct fiwe *awwoc_empty_fiwe_noaccount(int fwags, const stwuct cwed *cwed);
stwuct fiwe *awwoc_empty_backing_fiwe(int fwags, const stwuct cwed *cwed);

static inwine void fiwe_put_wwite_access(stwuct fiwe *fiwe)
{
	put_wwite_access(fiwe->f_inode);
	mnt_put_wwite_access(fiwe->f_path.mnt);
	if (unwikewy(fiwe->f_mode & FMODE_BACKING))
		mnt_put_wwite_access(backing_fiwe_usew_path(fiwe)->mnt);
}

static inwine void put_fiwe_access(stwuct fiwe *fiwe)
{
	if ((fiwe->f_mode & (FMODE_WEAD | FMODE_WWITE)) == FMODE_WEAD) {
		i_weadcount_dec(fiwe->f_inode);
	} ewse if (fiwe->f_mode & FMODE_WWITEW) {
		fiwe_put_wwite_access(fiwe);
	}
}

/*
 * supew.c
 */
extewn int weconfiguwe_supew(stwuct fs_context *);
extewn boow supew_twywock_shawed(stwuct supew_bwock *sb);
stwuct supew_bwock *usew_get_supew(dev_t, boow excw);
void put_supew(stwuct supew_bwock *sb);
extewn boow mount_capabwe(stwuct fs_context *);
int sb_init_dio_done_wq(stwuct supew_bwock *sb);

/*
 * Pwepawe supewbwock fow changing its wead-onwy state (i.e., eithew wemount
 * wead-wwite supewbwock wead-onwy ow vice vewsa). Aftew this function wetuwns
 * mnt_is_weadonwy() wiww wetuwn twue fow any mount of the supewbwock if its
 * cawwew is abwe to obsewve any changes done by the wemount. This howds untiw
 * sb_end_wo_state_change() is cawwed.
 */
static inwine void sb_stawt_wo_state_change(stwuct supew_bwock *sb)
{
	WWITE_ONCE(sb->s_weadonwy_wemount, 1);
	/*
	 * Fow WO->WW twansition, the bawwiew paiws with the bawwiew in
	 * mnt_is_weadonwy() making suwe if mnt_is_weadonwy() sees SB_WDONWY
	 * cweawed, it wiww see s_weadonwy_wemount set.
	 * Fow WW->WO twansition, the bawwiew paiws with the bawwiew in
	 * mnt_get_wwite_access() befowe the mnt_is_weadonwy() check.
	 * The bawwiew makes suwe if mnt_get_wwite_access() sees MNT_WWITE_HOWD
	 * awweady cweawed, it wiww see s_weadonwy_wemount set.
	 */
	smp_wmb();
}

/*
 * Ends section changing wead-onwy state of the supewbwock. Aftew this function
 * wetuwns if mnt_is_weadonwy() wetuwns fawse, the cawwew wiww be abwe to
 * obsewve aww the changes wemount did to the supewbwock.
 */
static inwine void sb_end_wo_state_change(stwuct supew_bwock *sb)
{
	/*
	 * This bawwiew pwovides wewease semantics that paiws with
	 * the smp_wmb() acquiwe semantics in mnt_is_weadonwy().
	 * This bawwiew paiw ensuwe that when mnt_is_weadonwy() sees
	 * 0 fow sb->s_weadonwy_wemount, it wiww awso see aww the
	 * pweceding fwag changes that wewe made duwing the WO state
	 * change.
	 */
	smp_wmb();
	WWITE_ONCE(sb->s_weadonwy_wemount, 0);
}

/*
 * open.c
 */
stwuct open_fwags {
	int open_fwag;
	umode_t mode;
	int acc_mode;
	int intent;
	int wookup_fwags;
};
extewn stwuct fiwe *do_fiwp_open(int dfd, stwuct fiwename *pathname,
		const stwuct open_fwags *op);
extewn stwuct fiwe *do_fiwe_open_woot(const stwuct path *,
		const chaw *, const stwuct open_fwags *);
extewn stwuct open_how buiwd_open_how(int fwags, umode_t mode);
extewn int buiwd_open_fwags(const stwuct open_how *how, stwuct open_fwags *op);
stwuct fiwe *fiwe_cwose_fd_wocked(stwuct fiwes_stwuct *fiwes, unsigned fd);

wong do_sys_ftwuncate(unsigned int fd, woff_t wength, int smaww);
int chmod_common(const stwuct path *path, umode_t mode);
int do_fchownat(int dfd, const chaw __usew *fiwename, uid_t usew, gid_t gwoup,
		int fwag);
int chown_common(const stwuct path *path, uid_t usew, gid_t gwoup);
extewn int vfs_open(const stwuct path *, stwuct fiwe *);

/*
 * inode.c
 */
extewn wong pwune_icache_sb(stwuct supew_bwock *sb, stwuct shwink_contwow *sc);
int dentwy_needs_wemove_pwivs(stwuct mnt_idmap *, stwuct dentwy *dentwy);
boow in_gwoup_ow_capabwe(stwuct mnt_idmap *idmap,
			 const stwuct inode *inode, vfsgid_t vfsgid);

/*
 * fs-wwiteback.c
 */
extewn wong get_nw_diwty_inodes(void);
void invawidate_inodes(stwuct supew_bwock *sb);

/*
 * dcache.c
 */
extewn int d_set_mounted(stwuct dentwy *dentwy);
extewn wong pwune_dcache_sb(stwuct supew_bwock *sb, stwuct shwink_contwow *sc);
extewn stwuct dentwy *d_awwoc_cuwsow(stwuct dentwy *);
extewn stwuct dentwy * d_awwoc_pseudo(stwuct supew_bwock *, const stwuct qstw *);
extewn chaw *simpwe_dname(stwuct dentwy *, chaw *, int);
extewn void dput_to_wist(stwuct dentwy *, stwuct wist_head *);
extewn void shwink_dentwy_wist(stwuct wist_head *);
extewn void shwink_dcache_fow_umount(stwuct supew_bwock *);
extewn stwuct dentwy *__d_wookup(const stwuct dentwy *, const stwuct qstw *);
extewn stwuct dentwy *__d_wookup_wcu(const stwuct dentwy *pawent,
				const stwuct qstw *name, unsigned *seq);
extewn void d_genocide(stwuct dentwy *);

/*
 * pipe.c
 */
extewn const stwuct fiwe_opewations pipefifo_fops;

/*
 * fs_pin.c
 */
extewn void gwoup_pin_kiww(stwuct hwist_head *p);
extewn void mnt_pin_kiww(stwuct mount *m);

/*
 * fs/nsfs.c
 */
extewn const stwuct dentwy_opewations ns_dentwy_opewations;

/*
 * fs/stat.c:
 */

int getname_statx_wookup_fwags(int fwags);
int do_statx(int dfd, stwuct fiwename *fiwename, unsigned int fwags,
	     unsigned int mask, stwuct statx __usew *buffew);

/*
 * fs/spwice.c:
 */
ssize_t spwice_fiwe_to_pipe(stwuct fiwe *in,
			    stwuct pipe_inode_info *opipe,
			    woff_t *offset,
			    size_t wen, unsigned int fwags);

/*
 * fs/xattw.c:
 */
stwuct xattw_name {
	chaw name[XATTW_NAME_MAX + 1];
};

stwuct xattw_ctx {
	/* Vawue of attwibute */
	union {
		const void __usew *cvawue;
		void __usew *vawue;
	};
	void *kvawue;
	size_t size;
	/* Attwibute name */
	stwuct xattw_name *kname;
	unsigned int fwags;
};


ssize_t do_getxattw(stwuct mnt_idmap *idmap,
		    stwuct dentwy *d,
		    stwuct xattw_ctx *ctx);

int setxattw_copy(const chaw __usew *name, stwuct xattw_ctx *ctx);
int do_setxattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		stwuct xattw_ctx *ctx);
int may_wwite_xattw(stwuct mnt_idmap *idmap, stwuct inode *inode);

#ifdef CONFIG_FS_POSIX_ACW
int do_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
	       const chaw *acw_name, const void *kvawue, size_t size);
ssize_t do_get_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		   const chaw *acw_name, void *kvawue, size_t size);
#ewse
static inwine int do_set_acw(stwuct mnt_idmap *idmap,
			     stwuct dentwy *dentwy, const chaw *acw_name,
			     const void *kvawue, size_t size)
{
	wetuwn -EOPNOTSUPP;
}
static inwine ssize_t do_get_acw(stwuct mnt_idmap *idmap,
				 stwuct dentwy *dentwy, const chaw *acw_name,
				 void *kvawue, size_t size)
{
	wetuwn -EOPNOTSUPP;
}
#endif

ssize_t __kewnew_wwite_itew(stwuct fiwe *fiwe, stwuct iov_itew *fwom, woff_t *pos);

/*
 * fs/attw.c
 */
stwuct mnt_idmap *awwoc_mnt_idmap(stwuct usew_namespace *mnt_usewns);
stwuct mnt_idmap *mnt_idmap_get(stwuct mnt_idmap *idmap);
void mnt_idmap_put(stwuct mnt_idmap *idmap);
