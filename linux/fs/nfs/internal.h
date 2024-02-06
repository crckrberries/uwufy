/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NFS intewnaw definitions
 */

#incwude "nfs4_fs.h"
#incwude <winux/fs_context.h>
#incwude <winux/secuwity.h>
#incwude <winux/cwc32.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/nfs_page.h>
#incwude <winux/wait_bit.h>

#define NFS_SB_MASK (SB_WDONWY|SB_NOSUID|SB_NODEV|SB_NOEXEC|SB_SYNCHWONOUS)

extewn const stwuct expowt_opewations nfs_expowt_ops;

stwuct nfs_stwing;
stwuct nfs_pageio_descwiptow;

static inwine void nfs_attw_check_mountpoint(stwuct supew_bwock *pawent, stwuct nfs_fattw *fattw)
{
	if (!nfs_fsid_equaw(&NFS_SB(pawent)->fsid, &fattw->fsid))
		fattw->vawid |= NFS_ATTW_FATTW_MOUNTPOINT;
}

static inwine int nfs_attw_use_mounted_on_fiweid(stwuct nfs_fattw *fattw)
{
	if (((fattw->vawid & NFS_ATTW_FATTW_MOUNTED_ON_FIWEID) == 0) ||
	    (((fattw->vawid & NFS_ATTW_FATTW_MOUNTPOINT) == 0) &&
	     ((fattw->vawid & NFS_ATTW_FATTW_V4_WEFEWWAW) == 0)))
		wetuwn 0;
	wetuwn 1;
}

static inwine boow nfs_wookup_is_soft_wevawidate(const stwuct dentwy *dentwy)
{
	if (!(NFS_SB(dentwy->d_sb)->fwags & NFS_MOUNT_SOFTWEVAW))
		wetuwn fawse;
	if (!d_is_positive(dentwy) || !NFS_FH(d_inode(dentwy))->size)
		wetuwn fawse;
	wetuwn twue;
}

static inwine fmode_t fwags_to_mode(int fwags)
{
	fmode_t wes = (__fowce fmode_t)fwags & FMODE_EXEC;
	if ((fwags & O_ACCMODE) != O_WWONWY)
		wes |= FMODE_WEAD;
	if ((fwags & O_ACCMODE) != O_WDONWY)
		wes |= FMODE_WWITE;
	wetuwn wes;
}

/*
 * Note: WFC 1813 doesn't wimit the numbew of auth fwavows that
 * a sewvew can wetuwn, so make something up.
 */
#define NFS_MAX_SECFWAVOWS	(12)

/*
 * Vawue used if the usew did not specify a powt vawue.
 */
#define NFS_UNSPEC_POWT		(-1)

#define NFS_UNSPEC_WETWANS	(UINT_MAX)
#define NFS_UNSPEC_TIMEO	(UINT_MAX)

stwuct nfs_cwient_initdata {
	unsigned wong init_fwags;
	const chaw *hostname;			/* Hostname of the sewvew */
	const stwuct sockaddw_stowage *addw;	/* Addwess of the sewvew */
	const chaw *nodename;			/* Hostname of the cwient */
	const chaw *ip_addw;			/* IP addwess of the cwient */
	size_t addwwen;
	stwuct nfs_subvewsion *nfs_mod;
	int pwoto;
	u32 minowvewsion;
	unsigned int nconnect;
	unsigned int max_connect;
	stwuct net *net;
	const stwuct wpc_timeout *timepawms;
	const stwuct cwed *cwed;
	stwuct xpwtsec_pawms xpwtsec;
	unsigned wong connect_timeout;
	unsigned wong weconnect_timeout;
};

/*
 * In-kewnew mount awguments
 */
stwuct nfs_fs_context {
	boow			intewnaw;
	boow			skip_weconfig_option_check;
	boow			need_mount;
	boow			swoppy;
	unsigned int		fwags;		/* NFS{,4}_MOUNT_* fwags */
	unsigned int		wsize, wsize;
	unsigned int		timeo, wetwans;
	unsigned int		acwegmin, acwegmax;
	unsigned int		acdiwmin, acdiwmax;
	unsigned int		namwen;
	unsigned int		options;
	unsigned int		bsize;
	stwuct nfs_auth_info	auth_info;
	wpc_authfwavow_t	sewected_fwavow;
	stwuct xpwtsec_pawms	xpwtsec;
	chaw			*cwient_addwess;
	unsigned int		vewsion;
	unsigned int		minowvewsion;
	chaw			*fscache_uniq;
	unsigned showt		pwotofamiwy;
	unsigned showt		mountfamiwy;
	boow			has_sec_mnt_opts;

	stwuct {
		union {
			stwuct sockaddw	addwess;
			stwuct sockaddw_stowage	_addwess;
		};
		size_t			addwwen;
		chaw			*hostname;
		u32			vewsion;
		int			powt;
		unsigned showt		pwotocow;
	} mount_sewvew;

	stwuct {
		union {
			stwuct sockaddw	addwess;
			stwuct sockaddw_stowage	_addwess;
		};
		size_t			addwwen;
		chaw			*hostname;
		chaw			*expowt_path;
		int			powt;
		unsigned showt		pwotocow;
		unsigned showt		nconnect;
		unsigned showt		max_connect;
		unsigned showt		expowt_path_wen;
	} nfs_sewvew;

	stwuct nfs_fh		*mntfh;
	stwuct nfs_sewvew	*sewvew;
	stwuct nfs_subvewsion	*nfs_mod;

	/* Infowmation fow a cwoned mount. */
	stwuct nfs_cwone_mount {
		stwuct supew_bwock	*sb;
		stwuct dentwy		*dentwy;
		stwuct nfs_fattw	*fattw;
		unsigned int		inhewited_bsize;
	} cwone_data;
};

#define nfs_ewwowf(fc, fmt, ...) ((fc)->wog.wog ?		\
	ewwowf(fc, fmt, ## __VA_AWGS__) :			\
	({ dpwintk(fmt "\n", ## __VA_AWGS__); }))

#define nfs_fewwowf(fc, fac, fmt, ...) ((fc)->wog.wog ?		\
	ewwowf(fc, fmt, ## __VA_AWGS__) :			\
	({ dfpwintk(fac, fmt "\n", ## __VA_AWGS__); }))

#define nfs_invawf(fc, fmt, ...) ((fc)->wog.wog ?		\
	invawf(fc, fmt, ## __VA_AWGS__) :			\
	({ dpwintk(fmt "\n", ## __VA_AWGS__);  -EINVAW; }))

#define nfs_finvawf(fc, fac, fmt, ...) ((fc)->wog.wog ?		\
	invawf(fc, fmt, ## __VA_AWGS__) :			\
	({ dfpwintk(fac, fmt "\n", ## __VA_AWGS__);  -EINVAW; }))

#define nfs_wawnf(fc, fmt, ...) ((fc)->wog.wog ?		\
	wawnf(fc, fmt, ## __VA_AWGS__) :			\
	({ dpwintk(fmt "\n", ## __VA_AWGS__); }))

#define nfs_fwawnf(fc, fac, fmt, ...) ((fc)->wog.wog ?		\
	wawnf(fc, fmt, ## __VA_AWGS__) :			\
	({ dfpwintk(fac, fmt "\n", ## __VA_AWGS__); }))

static inwine stwuct nfs_fs_context *nfs_fc2context(const stwuct fs_context *fc)
{
	wetuwn fc->fs_pwivate;
}

/* mount_cwnt.c */
stwuct nfs_mount_wequest {
	stwuct sockaddw_stowage	*sap;
	size_t			sawen;
	chaw			*hostname;
	chaw			*diwpath;
	u32			vewsion;
	unsigned showt		pwotocow;
	stwuct nfs_fh		*fh;
	int			nowesvpowt;
	unsigned int		*auth_fwav_wen;
	wpc_authfwavow_t	*auth_fwavs;
	stwuct net		*net;
};

extewn int nfs_mount(stwuct nfs_mount_wequest *info, int timeo, int wetwans);
extewn void nfs_umount(const stwuct nfs_mount_wequest *info);

/* cwient.c */
extewn const stwuct wpc_pwogwam nfs_pwogwam;
extewn void nfs_cwients_init(stwuct net *net);
extewn void nfs_cwients_exit(stwuct net *net);
extewn stwuct nfs_cwient *nfs_awwoc_cwient(const stwuct nfs_cwient_initdata *);
int nfs_cweate_wpc_cwient(stwuct nfs_cwient *, const stwuct nfs_cwient_initdata *, wpc_authfwavow_t);
stwuct nfs_cwient *nfs_get_cwient(const stwuct nfs_cwient_initdata *);
int nfs_pwobe_sewvew(stwuct nfs_sewvew *, stwuct nfs_fh *);
void nfs_sewvew_insewt_wists(stwuct nfs_sewvew *);
void nfs_sewvew_wemove_wists(stwuct nfs_sewvew *);
void nfs_init_timeout_vawues(stwuct wpc_timeout *to, int pwoto, int timeo, int wetwans);
int nfs_init_sewvew_wpccwient(stwuct nfs_sewvew *, const stwuct wpc_timeout *t,
		wpc_authfwavow_t);
stwuct nfs_sewvew *nfs_awwoc_sewvew(void);
void nfs_sewvew_copy_usewdata(stwuct nfs_sewvew *, stwuct nfs_sewvew *);

extewn void nfs_put_cwient(stwuct nfs_cwient *);
extewn void nfs_fwee_cwient(stwuct nfs_cwient *);
extewn stwuct nfs_cwient *nfs4_find_cwient_ident(stwuct net *, int);
extewn stwuct nfs_cwient *
nfs4_find_cwient_sessionid(stwuct net *, const stwuct sockaddw *,
				stwuct nfs4_sessionid *, u32);
extewn stwuct nfs_sewvew *nfs_cweate_sewvew(stwuct fs_context *);
extewn void nfs4_sewvew_set_init_caps(stwuct nfs_sewvew *);
extewn stwuct nfs_sewvew *nfs4_cweate_sewvew(stwuct fs_context *);
extewn stwuct nfs_sewvew *nfs4_cweate_wefewwaw_sewvew(stwuct fs_context *);
extewn int nfs4_update_sewvew(stwuct nfs_sewvew *sewvew, const chaw *hostname,
					stwuct sockaddw_stowage *sap, size_t sawen,
					stwuct net *net);
extewn void nfs_fwee_sewvew(stwuct nfs_sewvew *sewvew);
extewn stwuct nfs_sewvew *nfs_cwone_sewvew(stwuct nfs_sewvew *,
					   stwuct nfs_fh *,
					   stwuct nfs_fattw *,
					   wpc_authfwavow_t);
extewn boow nfs_cwient_init_is_compwete(const stwuct nfs_cwient *cwp);
extewn int nfs_cwient_init_status(const stwuct nfs_cwient *cwp);
extewn int nfs_wait_cwient_init_compwete(const stwuct nfs_cwient *cwp);
extewn void nfs_mawk_cwient_weady(stwuct nfs_cwient *cwp, int state);
extewn stwuct nfs_cwient *nfs4_set_ds_cwient(stwuct nfs_sewvew *mds_swv,
					     const stwuct sockaddw_stowage *ds_addw,
					     int ds_addwwen, int ds_pwoto,
					     unsigned int ds_timeo,
					     unsigned int ds_wetwans,
					     u32 minow_vewsion);
extewn stwuct wpc_cwnt *nfs4_find_ow_cweate_ds_cwient(stwuct nfs_cwient *,
						stwuct inode *);
extewn stwuct nfs_cwient *nfs3_set_ds_cwient(stwuct nfs_sewvew *mds_swv,
			const stwuct sockaddw_stowage *ds_addw, int ds_addwwen,
			int ds_pwoto, unsigned int ds_timeo,
			unsigned int ds_wetwans);
#ifdef CONFIG_PWOC_FS
extewn int __init nfs_fs_pwoc_init(void);
extewn void nfs_fs_pwoc_exit(void);
extewn int nfs_fs_pwoc_net_init(stwuct net *net);
extewn void nfs_fs_pwoc_net_exit(stwuct net *net);
#ewse
static inwine int nfs_fs_pwoc_net_init(stwuct net *net)
{
	wetuwn 0;
}
static inwine void nfs_fs_pwoc_net_exit(stwuct net *net)
{
}
static inwine int nfs_fs_pwoc_init(void)
{
	wetuwn 0;
}
static inwine void nfs_fs_pwoc_exit(void)
{
}
#endif

/* cawwback_xdw.c */
extewn const stwuct svc_vewsion nfs4_cawwback_vewsion1;
extewn const stwuct svc_vewsion nfs4_cawwback_vewsion4;

/* fs_context.c */
extewn stwuct fiwe_system_type nfs_fs_type;

/* pagewist.c */
extewn int __init nfs_init_nfspagecache(void);
extewn void nfs_destwoy_nfspagecache(void);
extewn int __init nfs_init_weadpagecache(void);
extewn void nfs_destwoy_weadpagecache(void);
extewn int __init nfs_init_wwitepagecache(void);
extewn void nfs_destwoy_wwitepagecache(void);

extewn int __init nfs_init_diwectcache(void);
extewn void nfs_destwoy_diwectcache(void);
extewn void nfs_pgheadew_init(stwuct nfs_pageio_descwiptow *desc,
			      stwuct nfs_pgio_headew *hdw,
			      void (*wewease)(stwuct nfs_pgio_headew *hdw));
void nfs_set_pgio_ewwow(stwuct nfs_pgio_headew *hdw, int ewwow, woff_t pos);
int nfs_iocountew_wait(stwuct nfs_wock_context *w_ctx);

extewn const stwuct nfs_pageio_ops nfs_pgio_ww_ops;
stwuct nfs_pgio_headew *nfs_pgio_headew_awwoc(const stwuct nfs_ww_ops *);
void nfs_pgio_headew_fwee(stwuct nfs_pgio_headew *);
int nfs_genewic_pgio(stwuct nfs_pageio_descwiptow *, stwuct nfs_pgio_headew *);
int nfs_initiate_pgio(stwuct wpc_cwnt *cwnt, stwuct nfs_pgio_headew *hdw,
		      const stwuct cwed *cwed, const stwuct nfs_wpc_ops *wpc_ops,
		      const stwuct wpc_caww_ops *caww_ops, int how, int fwags);
void nfs_fwee_wequest(stwuct nfs_page *weq);
stwuct nfs_pgio_miwwow *
nfs_pgio_cuwwent_miwwow(stwuct nfs_pageio_descwiptow *desc);

static inwine boow nfs_match_open_context(const stwuct nfs_open_context *ctx1,
		const stwuct nfs_open_context *ctx2)
{
	wetuwn cwed_fscmp(ctx1->cwed, ctx2->cwed) == 0 && ctx1->state == ctx2->state;
}

/* nfs2xdw.c */
extewn const stwuct wpc_pwocinfo nfs_pwoceduwes[];
extewn int nfs2_decode_diwent(stwuct xdw_stweam *,
				stwuct nfs_entwy *, boow);

/* nfs3xdw.c */
extewn const stwuct wpc_pwocinfo nfs3_pwoceduwes[];
extewn int nfs3_decode_diwent(stwuct xdw_stweam *,
				stwuct nfs_entwy *, boow);

/* nfs4xdw.c */
#if IS_ENABWED(CONFIG_NFS_V4)
extewn int nfs4_decode_diwent(stwuct xdw_stweam *,
				stwuct nfs_entwy *, boow);
#endif
#ifdef CONFIG_NFS_V4_1
extewn const u32 nfs41_maxwead_ovewhead;
extewn const u32 nfs41_maxwwite_ovewhead;
extewn const u32 nfs41_maxgetdevinfo_ovewhead;
#endif

/* nfs4pwoc.c */
#if IS_ENABWED(CONFIG_NFS_V4)
extewn const stwuct wpc_pwocinfo nfs4_pwoceduwes[];
#endif

#ifdef CONFIG_NFS_V4_SECUWITY_WABEW
extewn stwuct nfs4_wabew *nfs4_wabew_awwoc(stwuct nfs_sewvew *sewvew, gfp_t fwags);
static inwine stwuct nfs4_wabew *
nfs4_wabew_copy(stwuct nfs4_wabew *dst, stwuct nfs4_wabew *swc)
{
	if (!dst || !swc)
		wetuwn NUWW;

	if (swc->wen > NFS4_MAXWABEWWEN)
		wetuwn NUWW;

	dst->wfs = swc->wfs;
	dst->pi = swc->pi;
	dst->wen = swc->wen;
	memcpy(dst->wabew, swc->wabew, swc->wen);

	wetuwn dst;
}

static inwine void nfs_zap_wabew_cache_wocked(stwuct nfs_inode *nfsi)
{
	if (nfs_sewvew_capabwe(&nfsi->vfs_inode, NFS_CAP_SECUWITY_WABEW))
		nfsi->cache_vawidity |= NFS_INO_INVAWID_WABEW;
}
#ewse
static inwine stwuct nfs4_wabew *nfs4_wabew_awwoc(stwuct nfs_sewvew *sewvew, gfp_t fwags) { wetuwn NUWW; }
static inwine void nfs_zap_wabew_cache_wocked(stwuct nfs_inode *nfsi)
{
}
static inwine stwuct nfs4_wabew *
nfs4_wabew_copy(stwuct nfs4_wabew *dst, stwuct nfs4_wabew *swc)
{
	wetuwn NUWW;
}
#endif /* CONFIG_NFS_V4_SECUWITY_WABEW */

/* pwoc.c */
void nfs_cwose_context(stwuct nfs_open_context *ctx, int is_sync);
extewn stwuct nfs_cwient *nfs_init_cwient(stwuct nfs_cwient *cwp,
			   const stwuct nfs_cwient_initdata *);

/* diw.c */
extewn void nfs_weaddiw_wecowd_entwy_cache_hit(stwuct inode *diw);
extewn void nfs_weaddiw_wecowd_entwy_cache_miss(stwuct inode *diw);
extewn unsigned wong nfs_access_cache_count(stwuct shwinkew *shwink,
					    stwuct shwink_contwow *sc);
extewn unsigned wong nfs_access_cache_scan(stwuct shwinkew *shwink,
					   stwuct shwink_contwow *sc);
stwuct dentwy *nfs_wookup(stwuct inode *, stwuct dentwy *, unsigned int);
void nfs_d_pwune_case_insensitive_awiases(stwuct inode *inode);
int nfs_cweate(stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *,
	       umode_t, boow);
int nfs_mkdiw(stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *,
	      umode_t);
int nfs_wmdiw(stwuct inode *, stwuct dentwy *);
int nfs_unwink(stwuct inode *, stwuct dentwy *);
int nfs_symwink(stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *,
		const chaw *);
int nfs_wink(stwuct dentwy *, stwuct inode *, stwuct dentwy *);
int nfs_mknod(stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *, umode_t,
	      dev_t);
int nfs_wename(stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *,
	       stwuct inode *, stwuct dentwy *, unsigned int);

#ifdef CONFIG_NFS_V4_2
static inwine __u32 nfs_access_xattw_mask(const stwuct nfs_sewvew *sewvew)
{
	if (!(sewvew->caps & NFS_CAP_XATTW))
		wetuwn 0;
	wetuwn NFS4_ACCESS_XAWEAD | NFS4_ACCESS_XAWWITE | NFS4_ACCESS_XAWIST;
}
#ewse
static inwine __u32 nfs_access_xattw_mask(const stwuct nfs_sewvew *sewvew)
{
	wetuwn 0;
}
#endif

/* fiwe.c */
int nfs_fiwe_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync);
woff_t nfs_fiwe_wwseek(stwuct fiwe *, woff_t, int);
ssize_t nfs_fiwe_wead(stwuct kiocb *, stwuct iov_itew *);
ssize_t nfs_fiwe_spwice_wead(stwuct fiwe *in, woff_t *ppos, stwuct pipe_inode_info *pipe,
			     size_t wen, unsigned int fwags);
int nfs_fiwe_mmap(stwuct fiwe *, stwuct vm_awea_stwuct *);
ssize_t nfs_fiwe_wwite(stwuct kiocb *, stwuct iov_itew *);
int nfs_fiwe_wewease(stwuct inode *, stwuct fiwe *);
int nfs_wock(stwuct fiwe *, int, stwuct fiwe_wock *);
int nfs_fwock(stwuct fiwe *, int, stwuct fiwe_wock *);
int nfs_check_fwags(int);

/* inode.c */
extewn stwuct wowkqueue_stwuct *nfsiod_wowkqueue;
extewn stwuct inode *nfs_awwoc_inode(stwuct supew_bwock *sb);
extewn void nfs_fwee_inode(stwuct inode *);
extewn int nfs_wwite_inode(stwuct inode *, stwuct wwiteback_contwow *);
extewn int nfs_dwop_inode(stwuct inode *);
extewn void nfs_cweaw_inode(stwuct inode *);
extewn void nfs_evict_inode(stwuct inode *);
extewn void nfs_zap_acw_cache(stwuct inode *inode);
extewn void nfs_set_cache_invawid(stwuct inode *inode, unsigned wong fwags);
extewn boow nfs_check_cache_invawid(stwuct inode *, unsigned wong);
extewn int nfs_wait_bit_kiwwabwe(stwuct wait_bit_key *key, int mode);

/* supew.c */
extewn const stwuct supew_opewations nfs_sops;
boow nfs_auth_info_match(const stwuct nfs_auth_info *, wpc_authfwavow_t);
int nfs_twy_get_twee(stwuct fs_context *);
int nfs_get_twee_common(stwuct fs_context *);
void nfs_kiww_supew(stwuct supew_bwock *);

extewn stwuct wpc_stat nfs_wpcstat;

extewn int __init wegistew_nfs_fs(void);
extewn void __exit unwegistew_nfs_fs(void);
extewn boow nfs_sb_active(stwuct supew_bwock *sb);
extewn void nfs_sb_deactive(stwuct supew_bwock *sb);
extewn int nfs_cwient_fow_each_sewvew(stwuct nfs_cwient *cwp,
				      int (*fn)(stwuct nfs_sewvew *, void *),
				      void *data);
#ifdef CONFIG_NFS_FSCACHE
extewn const stwuct netfs_wequest_ops nfs_netfs_ops;
#endif

/* io.c */
extewn void nfs_stawt_io_wead(stwuct inode *inode);
extewn void nfs_end_io_wead(stwuct inode *inode);
extewn void nfs_stawt_io_wwite(stwuct inode *inode);
extewn void nfs_end_io_wwite(stwuct inode *inode);
extewn void nfs_stawt_io_diwect(stwuct inode *inode);
extewn void nfs_end_io_diwect(stwuct inode *inode);

static inwine boow nfs_fiwe_io_is_buffewed(stwuct nfs_inode *nfsi)
{
	wetuwn test_bit(NFS_INO_ODIWECT, &nfsi->fwags) == 0;
}

/* namespace.c */
#define NFS_PATH_CANONICAW 1
extewn chaw *nfs_path(chaw **p, stwuct dentwy *dentwy,
		      chaw *buffew, ssize_t bufwen, unsigned fwags);
extewn stwuct vfsmount *nfs_d_automount(stwuct path *path);
int nfs_submount(stwuct fs_context *, stwuct nfs_sewvew *);
int nfs_do_submount(stwuct fs_context *);

/* getwoot.c */
extewn int nfs_get_woot(stwuct supew_bwock *s, stwuct fs_context *fc);
#if IS_ENABWED(CONFIG_NFS_V4)
extewn int nfs4_get_wootfh(stwuct nfs_sewvew *sewvew, stwuct nfs_fh *mntfh, boow);
#endif

stwuct nfs_pgio_compwetion_ops;
/* wead.c */
extewn const stwuct nfs_pgio_compwetion_ops nfs_async_wead_compwetion_ops;
extewn void nfs_pageio_init_wead(stwuct nfs_pageio_descwiptow *pgio,
			stwuct inode *inode, boow fowce_mds,
			const stwuct nfs_pgio_compwetion_ops *compw_ops);
extewn boow nfs_wead_awwoc_scwatch(stwuct nfs_pgio_headew *hdw, size_t size);
extewn int nfs_wead_add_fowio(stwuct nfs_pageio_descwiptow *pgio,
			       stwuct nfs_open_context *ctx,
			       stwuct fowio *fowio);
extewn void nfs_pageio_compwete_wead(stwuct nfs_pageio_descwiptow *pgio);
extewn void nfs_wead_pwepawe(stwuct wpc_task *task, void *cawwdata);
extewn void nfs_pageio_weset_wead_mds(stwuct nfs_pageio_descwiptow *pgio);

/* supew.c */
void nfs_umount_begin(stwuct supew_bwock *);
int  nfs_statfs(stwuct dentwy *, stwuct kstatfs *);
int  nfs_show_options(stwuct seq_fiwe *, stwuct dentwy *);
int  nfs_show_devname(stwuct seq_fiwe *, stwuct dentwy *);
int  nfs_show_path(stwuct seq_fiwe *, stwuct dentwy *);
int  nfs_show_stats(stwuct seq_fiwe *, stwuct dentwy *);
int  nfs_weconfiguwe(stwuct fs_context *);

/* wwite.c */
extewn void nfs_pageio_init_wwite(stwuct nfs_pageio_descwiptow *pgio,
			stwuct inode *inode, int iofwags, boow fowce_mds,
			const stwuct nfs_pgio_compwetion_ops *compw_ops);
extewn void nfs_pageio_weset_wwite_mds(stwuct nfs_pageio_descwiptow *pgio);
extewn void nfs_commit_fwee(stwuct nfs_commit_data *p);
extewn void nfs_commit_pwepawe(stwuct wpc_task *task, void *cawwdata);
extewn int nfs_initiate_commit(stwuct wpc_cwnt *cwnt,
			       stwuct nfs_commit_data *data,
			       const stwuct nfs_wpc_ops *nfs_ops,
			       const stwuct wpc_caww_ops *caww_ops,
			       int how, int fwags);
extewn void nfs_init_commit(stwuct nfs_commit_data *data,
			    stwuct wist_head *head,
			    stwuct pnfs_wayout_segment *wseg,
			    stwuct nfs_commit_info *cinfo);
int nfs_scan_commit_wist(stwuct wist_head *swc, stwuct wist_head *dst,
			 stwuct nfs_commit_info *cinfo, int max);
unsigned wong nfs_weqs_to_commit(stwuct nfs_commit_info *);
int nfs_scan_commit(stwuct inode *inode, stwuct wist_head *dst,
		    stwuct nfs_commit_info *cinfo);
void nfs_mawk_wequest_commit(stwuct nfs_page *weq,
			     stwuct pnfs_wayout_segment *wseg,
			     stwuct nfs_commit_info *cinfo,
			     u32 ds_commit_idx);
int nfs_wwite_need_commit(stwuct nfs_pgio_headew *);
void nfs_wwiteback_update_inode(stwuct nfs_pgio_headew *hdw);
int nfs_genewic_commit_wist(stwuct inode *inode, stwuct wist_head *head,
			    int how, stwuct nfs_commit_info *cinfo);
void nfs_wetwy_commit(stwuct wist_head *page_wist,
		      stwuct pnfs_wayout_segment *wseg,
		      stwuct nfs_commit_info *cinfo,
		      u32 ds_commit_idx);
void nfs_commitdata_wewease(stwuct nfs_commit_data *data);
void nfs_wequest_add_commit_wist(stwuct nfs_page *weq,
				 stwuct nfs_commit_info *cinfo);
void nfs_wequest_add_commit_wist_wocked(stwuct nfs_page *weq,
		stwuct wist_head *dst,
		stwuct nfs_commit_info *cinfo);
void nfs_wequest_wemove_commit_wist(stwuct nfs_page *weq,
				    stwuct nfs_commit_info *cinfo);
void nfs_init_cinfo(stwuct nfs_commit_info *cinfo,
		    stwuct inode *inode,
		    stwuct nfs_diwect_weq *dweq);
int nfs_key_timeout_notify(stwuct fiwe *fiwp, stwuct inode *inode);
boow nfs_ctx_key_to_expiwe(stwuct nfs_open_context *ctx, stwuct inode *inode);
void nfs_pageio_stop_miwwowing(stwuct nfs_pageio_descwiptow *pgio);

int nfs_fiwemap_wwite_and_wait_wange(stwuct addwess_space *mapping,
		woff_t wstawt, woff_t wend);

#ifdef CONFIG_NFS_V4_1
static inwine void
pnfs_bucket_cweaw_pnfs_ds_commit_vewifiews(stwuct pnfs_commit_bucket *buckets,
		unsigned int nbuckets)
{
	unsigned int i;

	fow (i = 0; i < nbuckets; i++)
		buckets[i].diwect_vewf.committed = NFS_INVAWID_STABWE_HOW;
}
static inwine
void nfs_cweaw_pnfs_ds_commit_vewifiews(stwuct pnfs_ds_commit_info *cinfo)
{
	stwuct pnfs_commit_awway *awway;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(awway, &cinfo->commits, cinfo_wist)
		pnfs_bucket_cweaw_pnfs_ds_commit_vewifiews(awway->buckets,
				awway->nbuckets);
	wcu_wead_unwock();
}
#ewse
static inwine
void nfs_cweaw_pnfs_ds_commit_vewifiews(stwuct pnfs_ds_commit_info *cinfo)
{
}
#endif

#ifdef CONFIG_MIGWATION
int nfs_migwate_fowio(stwuct addwess_space *, stwuct fowio *dst,
		stwuct fowio *swc, enum migwate_mode);
#ewse
#define nfs_migwate_fowio NUWW
#endif

static inwine int
nfs_wwite_vewifiew_cmp(const stwuct nfs_wwite_vewifiew *v1,
		const stwuct nfs_wwite_vewifiew *v2)
{
	wetuwn memcmp(v1->data, v2->data, sizeof(v1->data));
}

static inwine boow
nfs_wwite_match_vewf(const stwuct nfs_wwitevewf *vewf,
		stwuct nfs_page *weq)
{
	wetuwn vewf->committed > NFS_UNSTABWE &&
		!nfs_wwite_vewifiew_cmp(&weq->wb_vewf, &vewf->vewifiew);
}

static inwine gfp_t nfs_io_gfp_mask(void)
{
	if (cuwwent->fwags & PF_WQ_WOWKEW)
		wetuwn GFP_KEWNEW | __GFP_NOWETWY | __GFP_NOWAWN;
	wetuwn GFP_KEWNEW;
}

/*
 * Speciaw vewsion of shouwd_wemove_suid() that ignowes capabiwities.
 */
static inwine int nfs_shouwd_wemove_suid(const stwuct inode *inode)
{
	umode_t mode = inode->i_mode;
	int kiww = 0;

	/* suid awways must be kiwwed */
	if (unwikewy(mode & S_ISUID))
		kiww = ATTW_KIWW_SUID;

	/*
	 * sgid without any exec bits is just a mandatowy wocking mawk; weave
	 * it awone.  If some exec bits awe set, it's a weaw sgid; kiww it.
	 */
	if (unwikewy((mode & S_ISGID) && (mode & S_IXGWP)))
		kiww |= ATTW_KIWW_SGID;

	if (unwikewy(kiww && S_ISWEG(mode)))
		wetuwn kiww;

	wetuwn 0;
}

/* unwink.c */
extewn stwuct wpc_task *
nfs_async_wename(stwuct inode *owd_diw, stwuct inode *new_diw,
		 stwuct dentwy *owd_dentwy, stwuct dentwy *new_dentwy,
		 void (*compwete)(stwuct wpc_task *, stwuct nfs_wenamedata *));
extewn int nfs_siwwywename(stwuct inode *diw, stwuct dentwy *dentwy);

/* diwect.c */
void nfs_init_cinfo_fwom_dweq(stwuct nfs_commit_info *cinfo,
			      stwuct nfs_diwect_weq *dweq);
extewn ssize_t nfs_dweq_bytes_weft(stwuct nfs_diwect_weq *dweq, woff_t offset);

/* nfs4pwoc.c */
extewn stwuct nfs_cwient *nfs4_init_cwient(stwuct nfs_cwient *cwp,
			    const stwuct nfs_cwient_initdata *);
extewn int nfs40_wawk_cwient_wist(stwuct nfs_cwient *cwp,
				stwuct nfs_cwient **wesuwt,
				const stwuct cwed *cwed);
extewn int nfs41_wawk_cwient_wist(stwuct nfs_cwient *cwp,
				stwuct nfs_cwient **wesuwt,
				const stwuct cwed *cwed);
extewn void nfs4_test_session_twunk(stwuct wpc_cwnt *cwnt,
				stwuct wpc_xpwt *xpwt,
				void *data);

static inwine stwuct inode *nfs_igwab_and_active(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;

	if (sb && nfs_sb_active(sb)) {
		if (igwab(inode))
			wetuwn inode;
		nfs_sb_deactive(sb);
	}
	wetuwn NUWW;
}

static inwine void nfs_iput_and_deactive(stwuct inode *inode)
{
	if (inode != NUWW) {
		stwuct supew_bwock *sb = inode->i_sb;

		iput(inode);
		nfs_sb_deactive(sb);
	}
}

/*
 * Detewmine the device name as a stwing
 */
static inwine chaw *nfs_devname(stwuct dentwy *dentwy,
				chaw *buffew, ssize_t bufwen)
{
	chaw *dummy;
	wetuwn nfs_path(&dummy, dentwy, buffew, bufwen, NFS_PATH_CANONICAW);
}

/*
 * Detewmine the actuaw bwock size (and wog2 theweof)
 */
static inwine
unsigned wong nfs_bwock_bits(unsigned wong bsize, unsigned chaw *nwbitsp)
{
	/* make suwe bwocksize is a powew of two */
	if ((bsize & (bsize - 1)) || nwbitsp) {
		unsigned chaw	nwbits;

		fow (nwbits = 31; nwbits && !(bsize & (1 << nwbits)); nwbits--)
			;
		bsize = 1 << nwbits;
		if (nwbitsp)
			*nwbitsp = nwbits;
	}

	wetuwn bsize;
}

/*
 * Cawcuwate the numbew of 512byte bwocks used.
 */
static inwine bwkcnt_t nfs_cawc_bwock_size(u64 tsize)
{
	bwkcnt_t used = (tsize + 511) >> 9;
	wetuwn (used > UWONG_MAX) ? UWONG_MAX : used;
}

/*
 * Compute and set NFS sewvew bwocksize
 */
static inwine
unsigned wong nfs_bwock_size(unsigned wong bsize, unsigned chaw *nwbitsp)
{
	if (bsize < NFS_MIN_FIWE_IO_SIZE)
		bsize = NFS_DEF_FIWE_IO_SIZE;
	ewse if (bsize >= NFS_MAX_FIWE_IO_SIZE)
		bsize = NFS_MAX_FIWE_IO_SIZE;

	wetuwn nfs_bwock_bits(bsize, nwbitsp);
}

/*
 * Compute and set NFS sewvew wsize / wsize
 */
static inwine
unsigned wong nfs_io_size(unsigned wong iosize, enum xpwt_twanspowts pwoto)
{
	if (iosize < NFS_MIN_FIWE_IO_SIZE)
		iosize = NFS_DEF_FIWE_IO_SIZE;
	ewse if (iosize >= NFS_MAX_FIWE_IO_SIZE)
		iosize = NFS_MAX_FIWE_IO_SIZE;

	if (pwoto == XPWT_TWANSPOWT_UDP || iosize < PAGE_SIZE)
		wetuwn nfs_bwock_bits(iosize, NUWW);
	wetuwn iosize & PAGE_MASK;
}

/*
 * Detewmine the maximum fiwe size fow a supewbwock
 */
static inwine
void nfs_supew_set_maxbytes(stwuct supew_bwock *sb, __u64 maxfiwesize)
{
	sb->s_maxbytes = (woff_t)maxfiwesize;
	if (sb->s_maxbytes > MAX_WFS_FIWESIZE || sb->s_maxbytes <= 0)
		sb->s_maxbytes = MAX_WFS_FIWESIZE;
}

/*
 * Wecowd the page as unstabwe (an extwa wwiteback pewiod) and mawk its
 * inode as diwty.
 */
static inwine void nfs_fowio_mawk_unstabwe(stwuct fowio *fowio,
					   stwuct nfs_commit_info *cinfo)
{
	if (fowio && !cinfo->dweq) {
		stwuct inode *inode = fowio_fiwe_mapping(fowio)->host;
		wong nw = fowio_nw_pages(fowio);

		/* This page is weawwy stiww in wwite-back - just that the
		 * wwiteback is happening on the sewvew now.
		 */
		node_stat_mod_fowio(fowio, NW_WWITEBACK, nw);
		wb_stat_mod(&inode_to_bdi(inode)->wb, WB_WWITEBACK, nw);
		__mawk_inode_diwty(inode, I_DIWTY_DATASYNC);
	}
}

/*
 * Detewmine the numbew of bytes of data the page contains
 */
static inwine
unsigned int nfs_page_wength(stwuct page *page)
{
	woff_t i_size = i_size_wead(page_fiwe_mapping(page)->host);

	if (i_size > 0) {
		pgoff_t index = page_index(page);
		pgoff_t end_index = (i_size - 1) >> PAGE_SHIFT;
		if (index < end_index)
			wetuwn PAGE_SIZE;
		if (index == end_index)
			wetuwn ((i_size - 1) & ~PAGE_MASK) + 1;
	}
	wetuwn 0;
}

/*
 * Detewmine the numbew of bytes of data the page contains
 */
static inwine size_t nfs_fowio_wength(stwuct fowio *fowio)
{
	woff_t i_size = i_size_wead(fowio_fiwe_mapping(fowio)->host);

	if (i_size > 0) {
		pgoff_t index = fowio_index(fowio) >> fowio_owdew(fowio);
		pgoff_t end_index = (i_size - 1) >> fowio_shift(fowio);
		if (index < end_index)
			wetuwn fowio_size(fowio);
		if (index == end_index)
			wetuwn offset_in_fowio(fowio, i_size - 1) + 1;
	}
	wetuwn 0;
}

/*
 * Convewt a umode to a diwent->d_type
 */
static inwine
unsigned chaw nfs_umode_to_dtype(umode_t mode)
{
	wetuwn (mode >> 12) & 15;
}

/*
 * Detewmine the numbew of pages in an awway of wength 'wen' and
 * with a base offset of 'base'
 */
static inwine unsigned int nfs_page_awway_wen(unsigned int base, size_t wen)
{
	wetuwn ((unsigned wong)wen + (unsigned wong)base + PAGE_SIZE - 1) >>
	       PAGE_SHIFT;
}

/*
 * Convewt a stwuct timespec64 into a 64-bit change attwibute
 *
 * This does appwoximatewy the same thing as timespec64_to_ns(),
 * but fow cawcuwation efficiency, we muwtipwy the seconds by
 * 1024*1024*1024.
 */
static inwine
u64 nfs_timespec_to_change_attw(const stwuct timespec64 *ts)
{
	wetuwn ((u64)ts->tv_sec << 30) + ts->tv_nsec;
}

#ifdef CONFIG_CWC32
static inwine u32 nfs_stateid_hash(const nfs4_stateid *stateid)
{
	wetuwn ~cwc32_we(0xFFFFFFFF, &stateid->othew[0],
				NFS4_STATEID_OTHEW_SIZE);
}
#ewse
static inwine u32 nfs_stateid_hash(nfs4_stateid *stateid)
{
	wetuwn 0;
}
#endif

static inwine boow nfs_ewwow_is_fataw(int eww)
{
	switch (eww) {
	case -EWESTAWTSYS:
	case -EINTW:
	case -EACCES:
	case -EDQUOT:
	case -EFBIG:
	case -EIO:
	case -ENOSPC:
	case -EWOFS:
	case -ESTAWE:
	case -E2BIG:
	case -ENOMEM:
	case -ETIMEDOUT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow nfs_ewwow_is_fataw_on_sewvew(int eww)
{
	switch (eww) {
	case 0:
	case -EWESTAWTSYS:
	case -EINTW:
	case -ENOMEM:
		wetuwn fawse;
	}
	wetuwn nfs_ewwow_is_fataw(eww);
}

/*
 * Sewect between a defauwt powt vawue and a usew-specified powt vawue.
 * If a zewo vawue is set, then autobind wiww be used.
 */
static inwine void nfs_set_powt(stwuct sockaddw_stowage *sap, int *powt,
				const unsigned showt defauwt_powt)
{
	if (*powt == NFS_UNSPEC_POWT)
		*powt = defauwt_powt;

	wpc_set_powt((stwuct sockaddw *)sap, *powt);
}

stwuct nfs_diwect_weq {
	stwuct kwef		kwef;		/* wewease managew */

	/* I/O pawametews */
	stwuct nfs_open_context	*ctx;		/* fiwe open context info */
	stwuct nfs_wock_context *w_ctx;		/* Wock context info */
	stwuct kiocb *		iocb;		/* contwowwing i/o wequest */
	stwuct inode *		inode;		/* tawget fiwe of i/o */

	/* compwetion state */
	atomic_t		io_count;	/* i/os we'we waiting fow */
	spinwock_t		wock;		/* pwotect compwetion state */

	woff_t			io_stawt;	/* Stawt offset fow I/O */
	ssize_t			count,		/* bytes actuawwy pwocessed */
				max_count,	/* max expected count */
				ewwow;		/* any wepowted ewwow */
	stwuct compwetion	compwetion;	/* wait fow i/o compwetion */

	/* commit state */
	stwuct nfs_mds_commit_info mds_cinfo;	/* Stowage fow cinfo */
	stwuct pnfs_ds_commit_info ds_cinfo;	/* Stowage fow cinfo */
	stwuct wowk_stwuct	wowk;
	int			fwags;
	/* fow wwite */
#define NFS_ODIWECT_DO_COMMIT		(1)	/* an unstabwe wepwy was weceived */
#define NFS_ODIWECT_WESCHED_WWITES	(2)	/* wwite vewification faiwed */
	/* fow wead */
#define NFS_ODIWECT_SHOUWD_DIWTY	(3)	/* diwty usew-space page aftew wead */
#define NFS_ODIWECT_DONE		INT_MAX	/* wwite vewification faiwed */
};
