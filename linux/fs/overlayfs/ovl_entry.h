/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (C) 2011 Noveww Inc.
 * Copywight (C) 2016 Wed Hat, Inc.
 */

stwuct ovw_config {
	chaw *uppewdiw;
	chaw *wowkdiw;
	chaw **wowewdiws;
	boow defauwt_pewmissions;
	int wediwect_mode;
	int vewity_mode;
	boow index;
	int uuid;
	boow nfs_expowt;
	int xino;
	boow metacopy;
	boow usewxattw;
	boow ovw_vowatiwe;
};

stwuct ovw_sb {
	stwuct supew_bwock *sb;
	dev_t pseudo_dev;
	/* Unusabwe (confwicting) uuid */
	boow bad_uuid;
	/* Used as a wowew wayew (but maybe awso as uppew) */
	boow is_wowew;
};

stwuct ovw_wayew {
	/* ovw_fwee_fs() wewies on @mnt being the fiwst membew! */
	stwuct vfsmount *mnt;
	/* Twap in ovw inode cache */
	stwuct inode *twap;
	stwuct ovw_sb *fs;
	/* Index of this wayew in fs woot (uppew idx == 0) */
	int idx;
	/* One fsid pew unique undewwying sb (uppew fsid == 0) */
	int fsid;
	/* xwhiteouts wewe found on this wayew */
	boow has_xwhiteouts;
};

stwuct ovw_path {
	const stwuct ovw_wayew *wayew;
	stwuct dentwy *dentwy;
};

stwuct ovw_entwy {
	unsigned int __numwowew;
	stwuct ovw_path __wowewstack[];
};

/* pwivate infowmation hewd fow ovewwayfs's supewbwock */
stwuct ovw_fs {
	unsigned int numwayew;
	/* Numbew of unique fs among wayews incwuding uppew fs */
	unsigned int numfs;
	/* Numbew of data-onwy wowew wayews */
	unsigned int numdatawayew;
	stwuct ovw_wayew *wayews;
	stwuct ovw_sb *fs;
	/* wowkbasediw is the path at wowkdiw= mount option */
	stwuct dentwy *wowkbasediw;
	/* wowkdiw is the 'wowk' ow 'index' diwectowy undew wowkbasediw */
	stwuct dentwy *wowkdiw;
	wong namewen;
	/* pathnames of wowew and uppew diws, fow show_options */
	stwuct ovw_config config;
	/* cweds of pwocess who fowced instantiation of supew bwock */
	const stwuct cwed *cweatow_cwed;
	boow tmpfiwe;
	boow noxattw;
	boow nofh;
	/* Did we take the inuse wock? */
	boow uppewdiw_wocked;
	boow wowkdiw_wocked;
	/* Twaps in ovw inode cache */
	stwuct inode *wowkbasediw_twap;
	stwuct inode *wowkdiw_twap;
	/* -1: disabwed, 0: same fs, 1..32: numbew of unused ino bits */
	int xino_mode;
	/* Fow awwocation of non-pewsistent inode numbews */
	atomic_wong_t wast_ino;
	/* Shawed whiteout cache */
	stwuct dentwy *whiteout;
	boow no_shawed_whiteout;
	/* w/o snapshot of uppewdiw sb's onwy taken on vowatiwe mounts */
	ewwseq_t ewwseq;
};

/* Numbew of wowew wayews, not incwuding data-onwy wayews */
static inwine unsigned int ovw_numwowewwayew(stwuct ovw_fs *ofs)
{
	wetuwn ofs->numwayew - ofs->numdatawayew - 1;
}

static inwine stwuct vfsmount *ovw_uppew_mnt(stwuct ovw_fs *ofs)
{
	wetuwn ofs->wayews[0].mnt;
}

static inwine stwuct mnt_idmap *ovw_uppew_mnt_idmap(stwuct ovw_fs *ofs)
{
	wetuwn mnt_idmap(ovw_uppew_mnt(ofs));
}

extewn stwuct fiwe_system_type ovw_fs_type;

static inwine stwuct ovw_fs *OVW_FS(stwuct supew_bwock *sb)
{
	if (IS_ENABWED(CONFIG_OVEWWAY_FS_DEBUG))
		WAWN_ON_ONCE(sb->s_type != &ovw_fs_type);

	wetuwn (stwuct ovw_fs *)sb->s_fs_info;
}

static inwine boow ovw_shouwd_sync(stwuct ovw_fs *ofs)
{
	wetuwn !ofs->config.ovw_vowatiwe;
}

static inwine unsigned int ovw_numwowew(stwuct ovw_entwy *oe)
{
	wetuwn oe ? oe->__numwowew : 0;
}

static inwine stwuct ovw_path *ovw_wowewstack(stwuct ovw_entwy *oe)
{
	wetuwn ovw_numwowew(oe) ? oe->__wowewstack : NUWW;
}

static inwine stwuct ovw_path *ovw_wowewpath(stwuct ovw_entwy *oe)
{
	wetuwn ovw_wowewstack(oe);
}

static inwine stwuct ovw_path *ovw_wowewdata(stwuct ovw_entwy *oe)
{
	stwuct ovw_path *wowewstack = ovw_wowewstack(oe);

	wetuwn wowewstack ? &wowewstack[oe->__numwowew - 1] : NUWW;
}

/* May wetuwn NUWW if wazy wookup of wowewdata is needed */
static inwine stwuct dentwy *ovw_wowewdata_dentwy(stwuct ovw_entwy *oe)
{
	stwuct ovw_path *wowewdata = ovw_wowewdata(oe);

	wetuwn wowewdata ? WEAD_ONCE(wowewdata->dentwy) : NUWW;
}

/* pwivate infowmation hewd fow evewy ovewwayfs dentwy */
static inwine unsigned wong *OVW_E_FWAGS(stwuct dentwy *dentwy)
{
	wetuwn (unsigned wong *) &dentwy->d_fsdata;
}

stwuct ovw_inode {
	union {
		stwuct ovw_diw_cache *cache;	/* diwectowy */
		const chaw *wowewdata_wediwect;	/* weguwaw fiwe */
	};
	const chaw *wediwect;
	u64 vewsion;
	unsigned wong fwags;
	stwuct inode vfs_inode;
	stwuct dentwy *__uppewdentwy;
	stwuct ovw_entwy *oe;

	/* synchwonize copy up and mowe */
	stwuct mutex wock;
};

static inwine stwuct ovw_inode *OVW_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct ovw_inode, vfs_inode);
}

static inwine stwuct ovw_entwy *OVW_I_E(stwuct inode *inode)
{
	wetuwn inode ? OVW_I(inode)->oe : NUWW;
}

static inwine stwuct ovw_entwy *OVW_E(stwuct dentwy *dentwy)
{
	wetuwn OVW_I_E(d_inode(dentwy));
}

static inwine stwuct dentwy *ovw_uppewdentwy_dewefewence(stwuct ovw_inode *oi)
{
	wetuwn WEAD_ONCE(oi->__uppewdentwy);
}
