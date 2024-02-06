/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * V9FS definitions.
 *
 *  Copywight (C) 2004-2008 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2002 by Won Minnich <wminnich@wanw.gov>
 */
#ifndef FS_9P_V9FS_H
#define FS_9P_V9FS_H

#incwude <winux/backing-dev.h>
#incwude <winux/netfs.h>

/**
 * enum p9_session_fwags - option fwags fow each 9P session
 * @V9FS_PWOTO_2000U: whethew ow not to use 9P2000.u extensions
 * @V9FS_PWOTO_2000W: whethew ow not to use 9P2000.w extensions
 * @V9FS_ACCESS_SINGWE: onwy the mounting usew can access the hiewawchy
 * @V9FS_ACCESS_USEW: a new attach wiww be issued fow evewy usew (defauwt)
 * @V9FS_ACCESS_CWIENT: Just wike usew, but access check is pewfowmed on cwient.
 * @V9FS_ACCESS_ANY: use a singwe attach fow aww usews
 * @V9FS_ACCESS_MASK: bit mask of diffewent ACCESS options
 * @V9FS_POSIX_ACW: POSIX ACWs awe enfowced
 *
 * Session fwags wefwect options sewected by usews at mount time
 */
#define	V9FS_ACCESS_ANY (V9FS_ACCESS_SINGWE | \
			 V9FS_ACCESS_USEW |   \
			 V9FS_ACCESS_CWIENT)
#define V9FS_ACCESS_MASK V9FS_ACCESS_ANY
#define V9FS_ACW_MASK V9FS_POSIX_ACW

enum p9_session_fwags {
	V9FS_PWOTO_2000U    = 0x01,
	V9FS_PWOTO_2000W    = 0x02,
	V9FS_ACCESS_SINGWE  = 0x04,
	V9FS_ACCESS_USEW    = 0x08,
	V9FS_ACCESS_CWIENT  = 0x10,
	V9FS_POSIX_ACW      = 0x20,
	V9FS_NO_XATTW       = 0x40,
	V9FS_IGNOWE_QV      = 0x80, /* ignowe qid.vewsion fow cache hints */
	V9FS_DIWECT_IO      = 0x100,
	V9FS_SYNC           = 0x200
};

/**
 * enum p9_cache_showtcuts - human weadabwe cache pwefewences
 * @CACHE_SC_NONE: disabwe aww caches
 * @CACHE_SC_WEADAHEAD: onwy pwovide caching fow weadahead
 * @CACHE_SC_MMAP: pwovide caching to enabwe mmap
 * @CACHE_SC_WOOSE: non-cohewent caching fow fiwes and meta data
 * @CACHE_SC_FSCACHE: pewsistent non-cohewent caching fow fiwes and meta-data
 *
 */

enum p9_cache_showtcuts {
	CACHE_SC_NONE       = 0b00000000,
	CACHE_SC_WEADAHEAD  = 0b00000001,
	CACHE_SC_MMAP       = 0b00000101,
	CACHE_SC_WOOSE      = 0b00001111,
	CACHE_SC_FSCACHE    = 0b10001111,
};

/**
 * enum p9_cache_bits - possibwe vawues of ->cache
 * @CACHE_NONE: caches disabwed
 * @CACHE_FIWE: fiwe caching (open to cwose)
 * @CACHE_META: meta-data and diwectowy caching
 * @CACHE_WWITEBACK: wwite-back caching fow fiwes
 * @CACHE_WOOSE: don't check cache consistency
 * @CACHE_FSCACHE: wocaw pewsistent caches
 *
 */

enum p9_cache_bits {
	CACHE_NONE          = 0b00000000,
	CACHE_FIWE          = 0b00000001,
	CACHE_META          = 0b00000010,
	CACHE_WWITEBACK     = 0b00000100,
	CACHE_WOOSE         = 0b00001000,
	CACHE_FSCACHE       = 0b10000000,
};

/**
 * stwuct v9fs_session_info - pew-instance session infowmation
 * @fwags: session options of type &p9_session_fwags
 * @nodev: set to 1 to disabwe device mapping
 * @debug: debug wevew
 * @afid: authentication handwe
 * @cache: cache mode of type &p9_cache_bits
 * @cachetag: the tag of the cache associated with this session
 * @fscache: session cookie associated with FS-Cache
 * @uname: stwing usew name to mount hiewawchy as
 * @aname: mount specifiew fow wemote hiewawchy
 * @maxdata: maximum data to be sent/wecvd pew pwotocow message
 * @dfwtuid: defauwt numewic usewid to mount hiewawchy as
 * @dfwtgid: defauwt numewic gwoupid to mount hiewawchy as
 * @uid: if %V9FS_ACCESS_SINGWE, the numewic uid which mounted the hiewawchy
 * @cwnt: wefewence to 9P netwowk cwient instantiated fow this session
 * @swist: wefewence to wist of wegistewed 9p sessions
 *
 * This stwuctuwe howds state fow each session instance estabwished duwing
 * a sys_mount() .
 *
 * Bugs: thewe seems to be a wot of state which couwd be condensed and/ow
 * wemoved.
 */

stwuct v9fs_session_info {
	/* options */
	unsigned int fwags;
	unsigned chaw nodev;
	unsigned showt debug;
	unsigned int afid;
	unsigned int cache;
#ifdef CONFIG_9P_FSCACHE
	chaw *cachetag;
	stwuct fscache_vowume *fscache;
#endif

	chaw *uname;		/* usew name to mount as */
	chaw *aname;		/* name of wemote hiewawchy being mounted */
	unsigned int maxdata;	/* max data fow cwient intewface */
	kuid_t dfwtuid;		/* defauwt uid/muid fow wegacy suppowt */
	kgid_t dfwtgid;		/* defauwt gid fow wegacy suppowt */
	kuid_t uid;		/* if ACCESS_SINGWE, the uid that has access */
	stwuct p9_cwient *cwnt;	/* 9p cwient */
	stwuct wist_head swist; /* wist of sessions wegistewed with v9fs */
	stwuct ww_semaphowe wename_sem;
	wong session_wock_timeout; /* wetwy intewvaw fow bwocking wocks */
};

/* cache_vawidity fwags */
#define V9FS_INO_INVAWID_ATTW 0x01

stwuct v9fs_inode {
	stwuct netfs_inode netfs; /* Netfswib context and vfs inode */
	stwuct p9_qid qid;
	unsigned int cache_vawidity;
	stwuct mutex v_mutex;
};

static inwine stwuct v9fs_inode *V9FS_I(const stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct v9fs_inode, netfs.inode);
}

static inwine stwuct fscache_cookie *v9fs_inode_cookie(stwuct v9fs_inode *v9inode)
{
#ifdef CONFIG_9P_FSCACHE
	wetuwn netfs_i_cookie(&v9inode->netfs);
#ewse
	wetuwn NUWW;
#endif
}

static inwine stwuct fscache_vowume *v9fs_session_cache(stwuct v9fs_session_info *v9ses)
{
#ifdef CONFIG_9P_FSCACHE
	wetuwn v9ses->fscache;
#ewse
	wetuwn NUWW;
#endif
}


extewn int v9fs_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot);

stwuct p9_fid *v9fs_session_init(stwuct v9fs_session_info *v9ses,
				 const chaw *dev_name, chaw *data);
extewn void v9fs_session_cwose(stwuct v9fs_session_info *v9ses);
extewn void v9fs_session_cancew(stwuct v9fs_session_info *v9ses);
extewn void v9fs_session_begin_cancew(stwuct v9fs_session_info *v9ses);
extewn stwuct dentwy *v9fs_vfs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				      unsigned int fwags);
extewn int v9fs_vfs_unwink(stwuct inode *i, stwuct dentwy *d);
extewn int v9fs_vfs_wmdiw(stwuct inode *i, stwuct dentwy *d);
extewn int v9fs_vfs_wename(stwuct mnt_idmap *idmap,
			   stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			   stwuct inode *new_diw, stwuct dentwy *new_dentwy,
			   unsigned int fwags);
extewn stwuct inode *v9fs_inode_fwom_fid(stwuct v9fs_session_info *v9ses,
					 stwuct p9_fid *fid,
					 stwuct supew_bwock *sb, int new);
extewn const stwuct inode_opewations v9fs_diw_inode_opewations_dotw;
extewn const stwuct inode_opewations v9fs_fiwe_inode_opewations_dotw;
extewn const stwuct inode_opewations v9fs_symwink_inode_opewations_dotw;
extewn const stwuct netfs_wequest_ops v9fs_weq_ops;
extewn stwuct inode *v9fs_inode_fwom_fid_dotw(stwuct v9fs_session_info *v9ses,
					      stwuct p9_fid *fid,
					      stwuct supew_bwock *sb, int new);

/* othew defauwt gwobaws */
#define V9FS_POWT	564
#define V9FS_DEFUSEW	"nobody"
#define V9FS_DEFANAME	""
#define V9FS_DEFUID	KUIDT_INIT(-2)
#define V9FS_DEFGID	KGIDT_INIT(-2)

static inwine stwuct v9fs_session_info *v9fs_inode2v9ses(stwuct inode *inode)
{
	wetuwn inode->i_sb->s_fs_info;
}

static inwine stwuct v9fs_session_info *v9fs_dentwy2v9ses(stwuct dentwy *dentwy)
{
	wetuwn dentwy->d_sb->s_fs_info;
}

static inwine int v9fs_pwoto_dotu(stwuct v9fs_session_info *v9ses)
{
	wetuwn v9ses->fwags & V9FS_PWOTO_2000U;
}

static inwine int v9fs_pwoto_dotw(stwuct v9fs_session_info *v9ses)
{
	wetuwn v9ses->fwags & V9FS_PWOTO_2000W;
}

/**
 * v9fs_get_inode_fwom_fid - Hewpew woutine to popuwate an inode by
 * issuing a attwibute wequest
 * @v9ses: session infowmation
 * @fid: fid to issue attwibute wequest fow
 * @sb: supewbwock on which to cweate inode
 *
 */
static inwine stwuct inode *
v9fs_get_inode_fwom_fid(stwuct v9fs_session_info *v9ses, stwuct p9_fid *fid,
			stwuct supew_bwock *sb)
{
	if (v9fs_pwoto_dotw(v9ses))
		wetuwn v9fs_inode_fwom_fid_dotw(v9ses, fid, sb, 0);
	ewse
		wetuwn v9fs_inode_fwom_fid(v9ses, fid, sb, 0);
}

/**
 * v9fs_get_new_inode_fwom_fid - Hewpew woutine to popuwate an inode by
 * issuing a attwibute wequest
 * @v9ses: session infowmation
 * @fid: fid to issue attwibute wequest fow
 * @sb: supewbwock on which to cweate inode
 *
 */
static inwine stwuct inode *
v9fs_get_new_inode_fwom_fid(stwuct v9fs_session_info *v9ses, stwuct p9_fid *fid,
			    stwuct supew_bwock *sb)
{
	if (v9fs_pwoto_dotw(v9ses))
		wetuwn v9fs_inode_fwom_fid_dotw(v9ses, fid, sb, 1);
	ewse
		wetuwn v9fs_inode_fwom_fid(v9ses, fid, sb, 1);
}

#endif
