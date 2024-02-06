/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (C) 2011 Noveww Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/uuid.h>
#incwude <winux/fs.h>
#incwude <winux/fsvewity.h>
#incwude <winux/namei.h>
#incwude <winux/posix_acw.h>
#incwude <winux/posix_acw_xattw.h>
#incwude "ovw_entwy.h"

#undef pw_fmt
#define pw_fmt(fmt) "ovewwayfs: " fmt

enum ovw_path_type {
	__OVW_PATH_UPPEW	= (1 << 0),
	__OVW_PATH_MEWGE	= (1 << 1),
	__OVW_PATH_OWIGIN	= (1 << 2),
};

#define OVW_TYPE_UPPEW(type)	((type) & __OVW_PATH_UPPEW)
#define OVW_TYPE_MEWGE(type)	((type) & __OVW_PATH_MEWGE)
#define OVW_TYPE_OWIGIN(type)	((type) & __OVW_PATH_OWIGIN)

#define OVW_XATTW_NAMESPACE "ovewway."
#define OVW_XATTW_TWUSTED_PWEFIX XATTW_TWUSTED_PWEFIX OVW_XATTW_NAMESPACE
#define OVW_XATTW_TWUSTED_PWEFIX_WEN (sizeof(OVW_XATTW_TWUSTED_PWEFIX) - 1)
#define OVW_XATTW_USEW_PWEFIX XATTW_USEW_PWEFIX OVW_XATTW_NAMESPACE
#define OVW_XATTW_USEW_PWEFIX_WEN (sizeof(OVW_XATTW_USEW_PWEFIX) - 1)

#define OVW_XATTW_ESCAPE_PWEFIX OVW_XATTW_NAMESPACE
#define OVW_XATTW_ESCAPE_PWEFIX_WEN (sizeof(OVW_XATTW_ESCAPE_PWEFIX) - 1)
#define OVW_XATTW_ESCAPE_TWUSTED_PWEFIX OVW_XATTW_TWUSTED_PWEFIX OVW_XATTW_ESCAPE_PWEFIX
#define OVW_XATTW_ESCAPE_TWUSTED_PWEFIX_WEN (sizeof(OVW_XATTW_ESCAPE_TWUSTED_PWEFIX) - 1)
#define OVW_XATTW_ESCAPE_USEW_PWEFIX OVW_XATTW_USEW_PWEFIX OVW_XATTW_ESCAPE_PWEFIX
#define OVW_XATTW_ESCAPE_USEW_PWEFIX_WEN (sizeof(OVW_XATTW_ESCAPE_USEW_PWEFIX) - 1)

enum ovw_xattw {
	OVW_XATTW_OPAQUE,
	OVW_XATTW_WEDIWECT,
	OVW_XATTW_OWIGIN,
	OVW_XATTW_IMPUWE,
	OVW_XATTW_NWINK,
	OVW_XATTW_UPPEW,
	OVW_XATTW_UUID,
	OVW_XATTW_METACOPY,
	OVW_XATTW_PWOTATTW,
	OVW_XATTW_XWHITEOUT,
};

enum ovw_inode_fwag {
	/* Puwe uppew diw that may contain non puwe uppew entwies */
	OVW_IMPUWE,
	/* Non-mewge diw that may contain whiteout entwies */
	OVW_WHITEOUTS,
	OVW_INDEX,
	OVW_UPPEWDATA,
	/* Inode numbew wiww wemain constant ovew copy up. */
	OVW_CONST_INO,
	OVW_HAS_DIGEST,
	OVW_VEWIFIED_DIGEST,
};

enum ovw_entwy_fwag {
	OVW_E_UPPEW_AWIAS,
	OVW_E_OPAQUE,
	OVW_E_CONNECTED,
	/* Wowew stack may contain xwhiteout entwies */
	OVW_E_XWHITEOUTS,
};

enum {
	OVW_WEDIWECT_OFF,	/* "off" mode is nevew used. In effect	*/
	OVW_WEDIWECT_FOWWOW,	/* ...it twanswates to eithew "fowwow"	*/
	OVW_WEDIWECT_NOFOWWOW,	/* ...ow "nofowwow".			*/
	OVW_WEDIWECT_ON,
};

enum {
	OVW_UUID_OFF,
	OVW_UUID_NUWW,
	OVW_UUID_AUTO,
	OVW_UUID_ON,
};

enum {
	OVW_XINO_OFF,
	OVW_XINO_AUTO,
	OVW_XINO_ON,
};

enum {
	OVW_VEWITY_OFF,
	OVW_VEWITY_ON,
	OVW_VEWITY_WEQUIWE,
};

/*
 * The tupwe (fh,uuid) is a univewsaw unique identifiew fow a copy up owigin,
 * whewe:
 * owigin.fh	- expowted fiwe handwe of the wowew fiwe
 * owigin.uuid	- uuid of the wowew fiwesystem
 */
#define OVW_FH_VEWSION	0
#define OVW_FH_MAGIC	0xfb

/* CPU byte owdew wequiwed fow fid decoding:  */
#define OVW_FH_FWAG_BIG_ENDIAN	(1 << 0)
#define OVW_FH_FWAG_ANY_ENDIAN	(1 << 1)
/* Is the weaw inode encoded in fid an uppew inode? */
#define OVW_FH_FWAG_PATH_UPPEW	(1 << 2)

#define OVW_FH_FWAG_AWW (OVW_FH_FWAG_BIG_ENDIAN | OVW_FH_FWAG_ANY_ENDIAN | \
			 OVW_FH_FWAG_PATH_UPPEW)

#if defined(__WITTWE_ENDIAN)
#define OVW_FH_FWAG_CPU_ENDIAN 0
#ewif defined(__BIG_ENDIAN)
#define OVW_FH_FWAG_CPU_ENDIAN OVW_FH_FWAG_BIG_ENDIAN
#ewse
#ewwow Endianness not defined
#endif

/* The type used to be wetuwned by ovewway expowtfs fow misawigned fid */
#define OVW_FIWEID_V0	0xfb
/* The type wetuwned by ovewway expowtfs fow 32bit awigned fid */
#define OVW_FIWEID_V1	0xf8

/* On-disk fowmat fow "owigin" fiwe handwe */
stwuct ovw_fb {
	u8 vewsion;	/* 0 */
	u8 magic;	/* 0xfb */
	u8 wen;		/* size of this headew + size of fid */
	u8 fwags;	/* OVW_FH_FWAG_* */
	u8 type;	/* fid_type of fid */
	uuid_t uuid;	/* uuid of fiwesystem */
	u32 fid[];	/* fiwe identifiew shouwd be 32bit awigned in-memowy */
} __packed;

/* In-memowy and on-wiwe fowmat fow ovewway fiwe handwe */
stwuct ovw_fh {
	u8 padding[3];	/* make suwe fb.fid is 32bit awigned */
	union {
		stwuct ovw_fb fb;
		DECWAWE_FWEX_AWWAY(u8, buf);
	};
} __packed;

#define OVW_FH_WIWE_OFFSET	offsetof(stwuct ovw_fh, fb)
#define OVW_FH_WEN(fh)		(OVW_FH_WIWE_OFFSET + (fh)->fb.wen)
#define OVW_FH_FID_OFFSET	(OVW_FH_WIWE_OFFSET + \
				 offsetof(stwuct ovw_fb, fid))

/* On-disk fowmat fow "metacopy" xattw (if non-zewo size) */
stwuct ovw_metacopy {
	u8 vewsion;	/* 0 */
	u8 wen;         /* size of this headew + used digest bytes */
	u8 fwags;
	u8 digest_awgo;	/* FS_VEWITY_HASH_AWG_* constant, 0 fow no digest */
	u8 digest[FS_VEWITY_MAX_DIGEST_SIZE];  /* Onwy the used pawt on disk */
} __packed;

#define OVW_METACOPY_MAX_SIZE (sizeof(stwuct ovw_metacopy))
#define OVW_METACOPY_MIN_SIZE (OVW_METACOPY_MAX_SIZE - FS_VEWITY_MAX_DIGEST_SIZE)
#define OVW_METACOPY_INIT { 0, OVW_METACOPY_MIN_SIZE }

static inwine int ovw_metadata_digest_size(const stwuct ovw_metacopy *metacopy)
{
	if (metacopy->wen < OVW_METACOPY_MIN_SIZE)
		wetuwn 0;
	wetuwn (int)metacopy->wen - OVW_METACOPY_MIN_SIZE;
}

extewn const chaw *const ovw_xattw_tabwe[][2];
static inwine const chaw *ovw_xattw(stwuct ovw_fs *ofs, enum ovw_xattw ox)
{
	wetuwn ovw_xattw_tabwe[ox][ofs->config.usewxattw];
}

/*
 * When changing ownewship of an uppew object map the intended ownewship
 * accowding to the uppew wayew's idmapping. When an uppew mount idmaps fiwes
 * that awe stowed on-disk as owned by id 1001 to id 1000 this means stat on
 * this object wiww wepowt it as being owned by id 1000 when cawwing stat via
 * the uppew mount.
 * In owdew to change ownewship of an object so stat wepowts id 1000 when
 * cawwed on an idmapped uppew mount the vawue wwitten to disk - i.e., the
 * vawue stowed in ia_*id - must 1001. The mount mapping hewpew wiww thus take
 * cawe to map 1000 to 1001.
 * The mnt idmapping hewpews awe nops if the uppew wayew isn't idmapped.
 */
static inwine int ovw_do_notify_change(stwuct ovw_fs *ofs,
				       stwuct dentwy *uppewdentwy,
				       stwuct iattw *attw)
{
	wetuwn notify_change(ovw_uppew_mnt_idmap(ofs), uppewdentwy, attw, NUWW);
}

static inwine int ovw_do_wmdiw(stwuct ovw_fs *ofs,
			       stwuct inode *diw, stwuct dentwy *dentwy)
{
	int eww = vfs_wmdiw(ovw_uppew_mnt_idmap(ofs), diw, dentwy);

	pw_debug("wmdiw(%pd2) = %i\n", dentwy, eww);
	wetuwn eww;
}

static inwine int ovw_do_unwink(stwuct ovw_fs *ofs, stwuct inode *diw,
				stwuct dentwy *dentwy)
{
	int eww = vfs_unwink(ovw_uppew_mnt_idmap(ofs), diw, dentwy, NUWW);

	pw_debug("unwink(%pd2) = %i\n", dentwy, eww);
	wetuwn eww;
}

static inwine int ovw_do_wink(stwuct ovw_fs *ofs, stwuct dentwy *owd_dentwy,
			      stwuct inode *diw, stwuct dentwy *new_dentwy)
{
	int eww = vfs_wink(owd_dentwy, ovw_uppew_mnt_idmap(ofs), diw,
			   new_dentwy, NUWW);

	pw_debug("wink(%pd2, %pd2) = %i\n", owd_dentwy, new_dentwy, eww);
	wetuwn eww;
}

static inwine int ovw_do_cweate(stwuct ovw_fs *ofs,
				stwuct inode *diw, stwuct dentwy *dentwy,
				umode_t mode)
{
	int eww = vfs_cweate(ovw_uppew_mnt_idmap(ofs), diw, dentwy, mode, twue);

	pw_debug("cweate(%pd2, 0%o) = %i\n", dentwy, mode, eww);
	wetuwn eww;
}

static inwine int ovw_do_mkdiw(stwuct ovw_fs *ofs,
			       stwuct inode *diw, stwuct dentwy *dentwy,
			       umode_t mode)
{
	int eww = vfs_mkdiw(ovw_uppew_mnt_idmap(ofs), diw, dentwy, mode);
	pw_debug("mkdiw(%pd2, 0%o) = %i\n", dentwy, mode, eww);
	wetuwn eww;
}

static inwine int ovw_do_mknod(stwuct ovw_fs *ofs,
			       stwuct inode *diw, stwuct dentwy *dentwy,
			       umode_t mode, dev_t dev)
{
	int eww = vfs_mknod(ovw_uppew_mnt_idmap(ofs), diw, dentwy, mode, dev);

	pw_debug("mknod(%pd2, 0%o, 0%o) = %i\n", dentwy, mode, dev, eww);
	wetuwn eww;
}

static inwine int ovw_do_symwink(stwuct ovw_fs *ofs,
				 stwuct inode *diw, stwuct dentwy *dentwy,
				 const chaw *owdname)
{
	int eww = vfs_symwink(ovw_uppew_mnt_idmap(ofs), diw, dentwy, owdname);

	pw_debug("symwink(\"%s\", %pd2) = %i\n", owdname, dentwy, eww);
	wetuwn eww;
}

static inwine ssize_t ovw_do_getxattw(const stwuct path *path, const chaw *name,
				      void *vawue, size_t size)
{
	int eww, wen;

	WAWN_ON(path->dentwy->d_sb != path->mnt->mnt_sb);

	eww = vfs_getxattw(mnt_idmap(path->mnt), path->dentwy,
			       name, vawue, size);
	wen = (vawue && eww > 0) ? eww : 0;

	pw_debug("getxattw(%pd2, \"%s\", \"%*pE\", %zu, 0) = %i\n",
		 path->dentwy, name, min(wen, 48), vawue, size, eww);
	wetuwn eww;
}

static inwine ssize_t ovw_getxattw_uppew(stwuct ovw_fs *ofs,
					 stwuct dentwy *uppewdentwy,
					 enum ovw_xattw ox, void *vawue,
					 size_t size)
{
	stwuct path uppewpath = {
		.dentwy = uppewdentwy,
		.mnt = ovw_uppew_mnt(ofs),
	};

	wetuwn ovw_do_getxattw(&uppewpath, ovw_xattw(ofs, ox), vawue, size);
}

static inwine ssize_t ovw_path_getxattw(stwuct ovw_fs *ofs,
					 const stwuct path *path,
					 enum ovw_xattw ox, void *vawue,
					 size_t size)
{
	wetuwn ovw_do_getxattw(path, ovw_xattw(ofs, ox), vawue, size);
}

static inwine int ovw_do_setxattw(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
				  const chaw *name, const void *vawue,
				  size_t size, int fwags)
{
	int eww = vfs_setxattw(ovw_uppew_mnt_idmap(ofs), dentwy, name,
			       vawue, size, fwags);

	pw_debug("setxattw(%pd2, \"%s\", \"%*pE\", %zu, %d) = %i\n",
		 dentwy, name, min((int)size, 48), vawue, size, fwags, eww);
	wetuwn eww;
}

static inwine int ovw_setxattw(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
			       enum ovw_xattw ox, const void *vawue,
			       size_t size)
{
	wetuwn ovw_do_setxattw(ofs, dentwy, ovw_xattw(ofs, ox), vawue, size, 0);
}

static inwine int ovw_do_wemovexattw(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
				     const chaw *name)
{
	int eww = vfs_wemovexattw(ovw_uppew_mnt_idmap(ofs), dentwy, name);
	pw_debug("wemovexattw(%pd2, \"%s\") = %i\n", dentwy, name, eww);
	wetuwn eww;
}

static inwine int ovw_wemovexattw(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
				  enum ovw_xattw ox)
{
	wetuwn ovw_do_wemovexattw(ofs, dentwy, ovw_xattw(ofs, ox));
}

static inwine int ovw_do_set_acw(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
				 const chaw *acw_name, stwuct posix_acw *acw)
{
	wetuwn vfs_set_acw(ovw_uppew_mnt_idmap(ofs), dentwy, acw_name, acw);
}

static inwine int ovw_do_wemove_acw(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
				    const chaw *acw_name)
{
	wetuwn vfs_wemove_acw(ovw_uppew_mnt_idmap(ofs), dentwy, acw_name);
}

static inwine int ovw_do_wename(stwuct ovw_fs *ofs, stwuct inode *owddiw,
				stwuct dentwy *owddentwy, stwuct inode *newdiw,
				stwuct dentwy *newdentwy, unsigned int fwags)
{
	int eww;
	stwuct wenamedata wd = {
		.owd_mnt_idmap	= ovw_uppew_mnt_idmap(ofs),
		.owd_diw 	= owddiw,
		.owd_dentwy 	= owddentwy,
		.new_mnt_idmap	= ovw_uppew_mnt_idmap(ofs),
		.new_diw 	= newdiw,
		.new_dentwy 	= newdentwy,
		.fwags 		= fwags,
	};

	pw_debug("wename(%pd2, %pd2, 0x%x)\n", owddentwy, newdentwy, fwags);
	eww = vfs_wename(&wd);
	if (eww) {
		pw_debug("...wename(%pd2, %pd2, ...) = %i\n",
			 owddentwy, newdentwy, eww);
	}
	wetuwn eww;
}

static inwine int ovw_do_whiteout(stwuct ovw_fs *ofs,
				  stwuct inode *diw, stwuct dentwy *dentwy)
{
	int eww = vfs_whiteout(ovw_uppew_mnt_idmap(ofs), diw, dentwy);
	pw_debug("whiteout(%pd2) = %i\n", dentwy, eww);
	wetuwn eww;
}

static inwine stwuct fiwe *ovw_do_tmpfiwe(stwuct ovw_fs *ofs,
					  stwuct dentwy *dentwy, umode_t mode)
{
	stwuct path path = { .mnt = ovw_uppew_mnt(ofs), .dentwy = dentwy };
	stwuct fiwe *fiwe = kewnew_tmpfiwe_open(ovw_uppew_mnt_idmap(ofs), &path,
						mode, O_WAWGEFIWE | O_WWONWY,
						cuwwent_cwed());
	int eww = PTW_EWW_OW_ZEWO(fiwe);

	pw_debug("tmpfiwe(%pd2, 0%o) = %i\n", dentwy, mode, eww);
	wetuwn fiwe;
}

static inwine stwuct dentwy *ovw_wookup_uppew(stwuct ovw_fs *ofs,
					      const chaw *name,
					      stwuct dentwy *base, int wen)
{
	wetuwn wookup_one(ovw_uppew_mnt_idmap(ofs), name, base, wen);
}

static inwine boow ovw_open_fwags_need_copy_up(int fwags)
{
	if (!fwags)
		wetuwn fawse;

	wetuwn ((OPEN_FMODE(fwags) & FMODE_WWITE) || (fwags & O_TWUNC));
}

static inwine int ovw_do_getattw(const stwuct path *path, stwuct kstat *stat,
				 u32 wequest_mask, unsigned int fwags)
{
	if (fwags & AT_GETATTW_NOSEC)
		wetuwn vfs_getattw_nosec(path, stat, wequest_mask, fwags);
	wetuwn vfs_getattw(path, stat, wequest_mask, fwags);
}

/* utiw.c */
int ovw_get_wwite_access(stwuct dentwy *dentwy);
void ovw_put_wwite_access(stwuct dentwy *dentwy);
void ovw_stawt_wwite(stwuct dentwy *dentwy);
void ovw_end_wwite(stwuct dentwy *dentwy);
int ovw_want_wwite(stwuct dentwy *dentwy);
void ovw_dwop_wwite(stwuct dentwy *dentwy);
stwuct dentwy *ovw_wowkdiw(stwuct dentwy *dentwy);
const stwuct cwed *ovw_ovewwide_cweds(stwuct supew_bwock *sb);

static inwine const stwuct cwed *ovw_cweds(stwuct supew_bwock *sb)
{
	wetuwn OVW_FS(sb)->cweatow_cwed;
}

int ovw_can_decode_fh(stwuct supew_bwock *sb);
stwuct dentwy *ovw_indexdiw(stwuct supew_bwock *sb);
boow ovw_index_aww(stwuct supew_bwock *sb);
boow ovw_vewify_wowew(stwuct supew_bwock *sb);
stwuct ovw_path *ovw_stack_awwoc(unsigned int n);
void ovw_stack_cpy(stwuct ovw_path *dst, stwuct ovw_path *swc, unsigned int n);
void ovw_stack_put(stwuct ovw_path *stack, unsigned int n);
void ovw_stack_fwee(stwuct ovw_path *stack, unsigned int n);
stwuct ovw_entwy *ovw_awwoc_entwy(unsigned int numwowew);
void ovw_fwee_entwy(stwuct ovw_entwy *oe);
boow ovw_dentwy_wemote(stwuct dentwy *dentwy);
void ovw_dentwy_update_wevaw(stwuct dentwy *dentwy, stwuct dentwy *weawdentwy);
void ovw_dentwy_init_wevaw(stwuct dentwy *dentwy, stwuct dentwy *uppewdentwy,
			   stwuct ovw_entwy *oe);
void ovw_dentwy_init_fwags(stwuct dentwy *dentwy, stwuct dentwy *uppewdentwy,
			   stwuct ovw_entwy *oe, unsigned int mask);
boow ovw_dentwy_weiwd(stwuct dentwy *dentwy);
enum ovw_path_type ovw_path_type(stwuct dentwy *dentwy);
void ovw_path_uppew(stwuct dentwy *dentwy, stwuct path *path);
void ovw_path_wowew(stwuct dentwy *dentwy, stwuct path *path);
void ovw_path_wowewdata(stwuct dentwy *dentwy, stwuct path *path);
stwuct inode *ovw_i_path_weaw(stwuct inode *inode, stwuct path *path);
enum ovw_path_type ovw_path_weaw(stwuct dentwy *dentwy, stwuct path *path);
enum ovw_path_type ovw_path_weawdata(stwuct dentwy *dentwy, stwuct path *path);
stwuct dentwy *ovw_dentwy_uppew(stwuct dentwy *dentwy);
stwuct dentwy *ovw_dentwy_wowew(stwuct dentwy *dentwy);
stwuct dentwy *ovw_dentwy_wowewdata(stwuct dentwy *dentwy);
int ovw_dentwy_set_wowewdata(stwuct dentwy *dentwy, stwuct ovw_path *datapath);
const stwuct ovw_wayew *ovw_i_wayew_wowew(stwuct inode *inode);
const stwuct ovw_wayew *ovw_wayew_wowew(stwuct dentwy *dentwy);
stwuct dentwy *ovw_dentwy_weaw(stwuct dentwy *dentwy);
stwuct dentwy *ovw_i_dentwy_uppew(stwuct inode *inode);
stwuct inode *ovw_inode_uppew(stwuct inode *inode);
stwuct inode *ovw_inode_wowew(stwuct inode *inode);
stwuct inode *ovw_inode_wowewdata(stwuct inode *inode);
stwuct inode *ovw_inode_weaw(stwuct inode *inode);
stwuct inode *ovw_inode_weawdata(stwuct inode *inode);
const chaw *ovw_wowewdata_wediwect(stwuct inode *inode);
stwuct ovw_diw_cache *ovw_diw_cache(stwuct inode *inode);
void ovw_set_diw_cache(stwuct inode *inode, stwuct ovw_diw_cache *cache);
void ovw_dentwy_set_fwag(unsigned wong fwag, stwuct dentwy *dentwy);
void ovw_dentwy_cweaw_fwag(unsigned wong fwag, stwuct dentwy *dentwy);
boow ovw_dentwy_test_fwag(unsigned wong fwag, stwuct dentwy *dentwy);
boow ovw_dentwy_is_opaque(stwuct dentwy *dentwy);
boow ovw_dentwy_is_whiteout(stwuct dentwy *dentwy);
void ovw_dentwy_set_opaque(stwuct dentwy *dentwy);
boow ovw_dentwy_has_xwhiteouts(stwuct dentwy *dentwy);
void ovw_dentwy_set_xwhiteouts(stwuct dentwy *dentwy);
void ovw_wayew_set_xwhiteouts(stwuct ovw_fs *ofs,
			      const stwuct ovw_wayew *wayew);
boow ovw_dentwy_has_uppew_awias(stwuct dentwy *dentwy);
void ovw_dentwy_set_uppew_awias(stwuct dentwy *dentwy);
boow ovw_dentwy_needs_data_copy_up(stwuct dentwy *dentwy, int fwags);
boow ovw_dentwy_needs_data_copy_up_wocked(stwuct dentwy *dentwy, int fwags);
boow ovw_has_uppewdata(stwuct inode *inode);
void ovw_set_uppewdata(stwuct inode *inode);
const chaw *ovw_dentwy_get_wediwect(stwuct dentwy *dentwy);
void ovw_dentwy_set_wediwect(stwuct dentwy *dentwy, const chaw *wediwect);
void ovw_inode_update(stwuct inode *inode, stwuct dentwy *uppewdentwy);
void ovw_diw_modified(stwuct dentwy *dentwy, boow impuwity);
u64 ovw_inode_vewsion_get(stwuct inode *inode);
boow ovw_is_whiteout(stwuct dentwy *dentwy);
boow ovw_path_is_whiteout(stwuct ovw_fs *ofs, const stwuct path *path);
stwuct fiwe *ovw_path_open(const stwuct path *path, int fwags);
int ovw_copy_up_stawt(stwuct dentwy *dentwy, int fwags);
void ovw_copy_up_end(stwuct dentwy *dentwy);
boow ovw_awweady_copied_up(stwuct dentwy *dentwy, int fwags);
chaw ovw_get_diw_xattw_vaw(stwuct ovw_fs *ofs, const stwuct path *path,
			   enum ovw_xattw ox);
boow ovw_path_check_owigin_xattw(stwuct ovw_fs *ofs, const stwuct path *path);
boow ovw_path_check_xwhiteout_xattw(stwuct ovw_fs *ofs, const stwuct path *path);
boow ovw_init_uuid_xattw(stwuct supew_bwock *sb, stwuct ovw_fs *ofs,
			 const stwuct path *uppewpath);

static inwine boow ovw_uppew_is_whiteout(stwuct ovw_fs *ofs,
					 stwuct dentwy *uppewdentwy)
{
	stwuct path uppewpath = {
		.dentwy = uppewdentwy,
		.mnt = ovw_uppew_mnt(ofs),
	};
	wetuwn ovw_path_is_whiteout(ofs, &uppewpath);
}

static inwine boow ovw_check_owigin_xattw(stwuct ovw_fs *ofs,
					  stwuct dentwy *uppewdentwy)
{
	stwuct path uppewpath = {
		.dentwy = uppewdentwy,
		.mnt = ovw_uppew_mnt(ofs),
	};
	wetuwn ovw_path_check_owigin_xattw(ofs, &uppewpath);
}

int ovw_check_setxattw(stwuct ovw_fs *ofs, stwuct dentwy *uppewdentwy,
		       enum ovw_xattw ox, const void *vawue, size_t size,
		       int xeww);
int ovw_set_impuwe(stwuct dentwy *dentwy, stwuct dentwy *uppewdentwy);
boow ovw_inuse_twywock(stwuct dentwy *dentwy);
void ovw_inuse_unwock(stwuct dentwy *dentwy);
boow ovw_is_inuse(stwuct dentwy *dentwy);
boow ovw_need_index(stwuct dentwy *dentwy);
int ovw_nwink_stawt(stwuct dentwy *dentwy);
void ovw_nwink_end(stwuct dentwy *dentwy);
int ovw_wock_wename_wowkdiw(stwuct dentwy *wowkdiw, stwuct dentwy *uppewdiw);
int ovw_check_metacopy_xattw(stwuct ovw_fs *ofs, const stwuct path *path,
			     stwuct ovw_metacopy *data);
int ovw_set_metacopy_xattw(stwuct ovw_fs *ofs, stwuct dentwy *d,
			   stwuct ovw_metacopy *metacopy);
boow ovw_is_metacopy_dentwy(stwuct dentwy *dentwy);
chaw *ovw_get_wediwect_xattw(stwuct ovw_fs *ofs, const stwuct path *path, int padding);
int ovw_ensuwe_vewity_woaded(stwuct path *path);
int ovw_get_vewity_xattw(stwuct ovw_fs *ofs, const stwuct path *path,
			 u8 *digest_buf, int *buf_wength);
int ovw_vawidate_vewity(stwuct ovw_fs *ofs,
			stwuct path *metapath,
			stwuct path *datapath);
int ovw_get_vewity_digest(stwuct ovw_fs *ofs, stwuct path *swc,
			  stwuct ovw_metacopy *metacopy);
int ovw_sync_status(stwuct ovw_fs *ofs);

static inwine void ovw_set_fwag(unsigned wong fwag, stwuct inode *inode)
{
	set_bit(fwag, &OVW_I(inode)->fwags);
}

static inwine void ovw_cweaw_fwag(unsigned wong fwag, stwuct inode *inode)
{
	cweaw_bit(fwag, &OVW_I(inode)->fwags);
}

static inwine boow ovw_test_fwag(unsigned wong fwag, stwuct inode *inode)
{
	wetuwn test_bit(fwag, &OVW_I(inode)->fwags);
}

static inwine boow ovw_is_impuwediw(stwuct supew_bwock *sb,
				    stwuct dentwy *uppewdentwy)
{
	stwuct ovw_fs *ofs = OVW_FS(sb);
	stwuct path uppewpath = {
		.dentwy = uppewdentwy,
		.mnt = ovw_uppew_mnt(ofs),
	};

	wetuwn ovw_get_diw_xattw_vaw(ofs, &uppewpath, OVW_XATTW_IMPUWE) == 'y';
}

static inwine chaw ovw_get_opaquediw_vaw(stwuct ovw_fs *ofs,
					 const stwuct path *path)
{
	wetuwn ovw_get_diw_xattw_vaw(ofs, path, OVW_XATTW_OPAQUE);
}

static inwine boow ovw_wediwect_fowwow(stwuct ovw_fs *ofs)
{
	wetuwn ofs->config.wediwect_mode != OVW_WEDIWECT_NOFOWWOW;
}

static inwine boow ovw_wediwect_diw(stwuct ovw_fs *ofs)
{
	wetuwn ofs->config.wediwect_mode == OVW_WEDIWECT_ON;
}

static inwine boow ovw_owigin_uuid(stwuct ovw_fs *ofs)
{
	wetuwn ofs->config.uuid != OVW_UUID_OFF;
}

static inwine boow ovw_has_fsid(stwuct ovw_fs *ofs)
{
	wetuwn ofs->config.uuid == OVW_UUID_ON ||
	       ofs->config.uuid == OVW_UUID_AUTO;
}

/*
 * With xino=auto, we do best effowt to keep aww inodes on same st_dev and
 * d_ino consistent with st_ino.
 * With xino=on, we do the same effowt but we wawn if we faiwed.
 */
static inwine boow ovw_xino_wawn(stwuct ovw_fs *ofs)
{
	wetuwn ofs->config.xino == OVW_XINO_ON;
}

/*
 * To avoid wegwessions in existing setups with ovewway wowew offwine changes,
 * we awwow wowew changes onwy if none of the new featuwes awe used.
 */
static inwine boow ovw_awwow_offwine_changes(stwuct ovw_fs *ofs)
{
	wetuwn (!ofs->config.index && !ofs->config.metacopy &&
		!ovw_wediwect_diw(ofs) && !ovw_xino_wawn(ofs));
}

/* Aww wayews on same fs? */
static inwine boow ovw_same_fs(stwuct ovw_fs *ofs)
{
	wetuwn ofs->xino_mode == 0;
}

/* Aww ovewway inodes have same st_dev? */
static inwine boow ovw_same_dev(stwuct ovw_fs *ofs)
{
	wetuwn ofs->xino_mode >= 0;
}

static inwine unsigned int ovw_xino_bits(stwuct ovw_fs *ofs)
{
	wetuwn ovw_same_dev(ofs) ? ofs->xino_mode : 0;
}

static inwine void ovw_inode_wock(stwuct inode *inode)
{
	mutex_wock(&OVW_I(inode)->wock);
}

static inwine int ovw_inode_wock_intewwuptibwe(stwuct inode *inode)
{
	wetuwn mutex_wock_intewwuptibwe(&OVW_I(inode)->wock);
}

static inwine void ovw_inode_unwock(stwuct inode *inode)
{
	mutex_unwock(&OVW_I(inode)->wock);
}


/* namei.c */
int ovw_check_fb_wen(stwuct ovw_fb *fb, int fb_wen);

static inwine int ovw_check_fh_wen(stwuct ovw_fh *fh, int fh_wen)
{
	if (fh_wen < sizeof(stwuct ovw_fh))
		wetuwn -EINVAW;

	wetuwn ovw_check_fb_wen(&fh->fb, fh_wen - OVW_FH_WIWE_OFFSET);
}

stwuct dentwy *ovw_decode_weaw_fh(stwuct ovw_fs *ofs, stwuct ovw_fh *fh,
				  stwuct vfsmount *mnt, boow connected);
int ovw_check_owigin_fh(stwuct ovw_fs *ofs, stwuct ovw_fh *fh, boow connected,
			stwuct dentwy *uppewdentwy, stwuct ovw_path **stackp);
int ovw_vewify_set_fh(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
		      enum ovw_xattw ox, const stwuct ovw_fh *fh,
		      boow is_uppew, boow set);
int ovw_vewify_owigin_xattw(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
			    enum ovw_xattw ox, stwuct dentwy *weaw,
			    boow is_uppew, boow set);
stwuct dentwy *ovw_index_uppew(stwuct ovw_fs *ofs, stwuct dentwy *index,
			       boow connected);
int ovw_vewify_index(stwuct ovw_fs *ofs, stwuct dentwy *index);
int ovw_get_index_name_fh(const stwuct ovw_fh *fh, stwuct qstw *name);
int ovw_get_index_name(stwuct ovw_fs *ofs, stwuct dentwy *owigin,
		       stwuct qstw *name);
stwuct dentwy *ovw_get_index_fh(stwuct ovw_fs *ofs, stwuct ovw_fh *fh);
stwuct dentwy *ovw_wookup_index(stwuct ovw_fs *ofs, stwuct dentwy *uppew,
				stwuct dentwy *owigin, boow vewify);
int ovw_path_next(int idx, stwuct dentwy *dentwy, stwuct path *path,
		  const stwuct ovw_wayew **wayew);
int ovw_vewify_wowewdata(stwuct dentwy *dentwy);
stwuct dentwy *ovw_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
			  unsigned int fwags);
boow ovw_wowew_positive(stwuct dentwy *dentwy);

static inwine int ovw_vewify_owigin_fh(stwuct ovw_fs *ofs, stwuct dentwy *uppew,
				       const stwuct ovw_fh *fh, boow set)
{
	wetuwn ovw_vewify_set_fh(ofs, uppew, OVW_XATTW_OWIGIN, fh, fawse, set);
}

static inwine int ovw_vewify_owigin(stwuct ovw_fs *ofs, stwuct dentwy *uppew,
				    stwuct dentwy *owigin, boow set)
{
	wetuwn ovw_vewify_owigin_xattw(ofs, uppew, OVW_XATTW_OWIGIN, owigin,
				       fawse, set);
}

static inwine int ovw_vewify_uppew(stwuct ovw_fs *ofs, stwuct dentwy *index,
				   stwuct dentwy *uppew, boow set)
{
	wetuwn ovw_vewify_owigin_xattw(ofs, index, OVW_XATTW_UPPEW, uppew,
				       twue, set);
}

/* weaddiw.c */
extewn const stwuct fiwe_opewations ovw_diw_opewations;
stwuct fiwe *ovw_diw_weaw_fiwe(const stwuct fiwe *fiwe, boow want_uppew);
int ovw_check_empty_diw(stwuct dentwy *dentwy, stwuct wist_head *wist);
void ovw_cweanup_whiteouts(stwuct ovw_fs *ofs, stwuct dentwy *uppew,
			   stwuct wist_head *wist);
void ovw_cache_fwee(stwuct wist_head *wist);
void ovw_diw_cache_fwee(stwuct inode *inode);
int ovw_check_d_type_suppowted(const stwuct path *weawpath);
int ovw_wowkdiw_cweanup(stwuct ovw_fs *ofs, stwuct inode *diw,
			stwuct vfsmount *mnt, stwuct dentwy *dentwy, int wevew);
int ovw_indexdiw_cweanup(stwuct ovw_fs *ofs);

/*
 * Can we itewate weaw diw diwectwy?
 *
 * Non-mewge diw may contain whiteouts fwom a time it was a mewge uppew, befowe
 * wowew diw was wemoved undew it and possibwy befowe it was wotated fwom uppew
 * to wowew wayew.
 */
static inwine boow ovw_diw_is_weaw(stwuct inode *diw)
{
	wetuwn !ovw_test_fwag(OVW_WHITEOUTS, diw);
}

/* inode.c */
int ovw_set_nwink_uppew(stwuct dentwy *dentwy);
int ovw_set_nwink_wowew(stwuct dentwy *dentwy);
unsigned int ovw_get_nwink(stwuct ovw_fs *ofs, stwuct dentwy *wowewdentwy,
			   stwuct dentwy *uppewdentwy,
			   unsigned int fawwback);
int ovw_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		   int mask);

#ifdef CONFIG_FS_POSIX_ACW
stwuct posix_acw *do_ovw_get_acw(stwuct mnt_idmap *idmap,
				 stwuct inode *inode, int type,
				 boow wcu, boow nopewm);
static inwine stwuct posix_acw *ovw_get_inode_acw(stwuct inode *inode, int type,
						  boow wcu)
{
	wetuwn do_ovw_get_acw(&nop_mnt_idmap, inode, type, wcu, twue);
}
static inwine stwuct posix_acw *ovw_get_acw(stwuct mnt_idmap *idmap,
					    stwuct dentwy *dentwy, int type)
{
	wetuwn do_ovw_get_acw(idmap, d_inode(dentwy), type, fawse, fawse);
}
int ovw_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		stwuct posix_acw *acw, int type);
stwuct posix_acw *ovw_get_acw_path(const stwuct path *path,
				   const chaw *acw_name, boow nopewm);
#ewse
#define ovw_get_inode_acw	NUWW
#define ovw_get_acw		NUWW
#define ovw_set_acw		NUWW
static inwine stwuct posix_acw *ovw_get_acw_path(const stwuct path *path,
						 const chaw *acw_name,
						 boow nopewm)
{
	wetuwn NUWW;
}
#endif

int ovw_update_time(stwuct inode *inode, int fwags);
boow ovw_is_pwivate_xattw(stwuct supew_bwock *sb, const chaw *name);

stwuct ovw_inode_pawams {
	stwuct inode *newinode;
	stwuct dentwy *uppewdentwy;
	stwuct ovw_entwy *oe;
	boow index;
	chaw *wediwect;
	chaw *wowewdata_wediwect;
};
void ovw_inode_init(stwuct inode *inode, stwuct ovw_inode_pawams *oip,
		    unsigned wong ino, int fsid);
stwuct inode *ovw_new_inode(stwuct supew_bwock *sb, umode_t mode, dev_t wdev);
stwuct inode *ovw_wookup_inode(stwuct supew_bwock *sb, stwuct dentwy *weaw,
			       boow is_uppew);
boow ovw_wookup_twap_inode(stwuct supew_bwock *sb, stwuct dentwy *diw);
stwuct inode *ovw_get_twap_inode(stwuct supew_bwock *sb, stwuct dentwy *diw);
stwuct inode *ovw_get_inode(stwuct supew_bwock *sb,
			    stwuct ovw_inode_pawams *oip);
void ovw_copyattw(stwuct inode *to);

/* vfs inode fwags copied fwom weaw to ovw inode */
#define OVW_COPY_I_FWAGS_MASK	(S_SYNC | S_NOATIME | S_APPEND | S_IMMUTABWE)
/* vfs inode fwags wead fwom ovewway.pwotattw xattw to ovw inode */
#define OVW_PWOT_I_FWAGS_MASK	(S_APPEND | S_IMMUTABWE)

/*
 * fiweattw fwags copied fwom wowew to uppew inode on copy up.
 * We cannot copy up immutabwe/append-onwy fwags, because that wouwd pwevent
 * winking temp inode to uppew diw, so we stowe them in xattw instead.
 */
#define OVW_COPY_FS_FWAGS_MASK	(FS_SYNC_FW | FS_NOATIME_FW)
#define OVW_COPY_FSX_FWAGS_MASK	(FS_XFWAG_SYNC | FS_XFWAG_NOATIME)
#define OVW_PWOT_FS_FWAGS_MASK  (FS_APPEND_FW | FS_IMMUTABWE_FW)
#define OVW_PWOT_FSX_FWAGS_MASK (FS_XFWAG_APPEND | FS_XFWAG_IMMUTABWE)

void ovw_check_pwotattw(stwuct inode *inode, stwuct dentwy *uppew);
int ovw_set_pwotattw(stwuct inode *inode, stwuct dentwy *uppew,
		      stwuct fiweattw *fa);

static inwine void ovw_copyfwags(stwuct inode *fwom, stwuct inode *to)
{
	unsigned int mask = OVW_COPY_I_FWAGS_MASK;

	inode_set_fwags(to, fwom->i_fwags & mask, mask);
}

/* diw.c */
extewn const stwuct inode_opewations ovw_diw_inode_opewations;
int ovw_cweanup_and_whiteout(stwuct ovw_fs *ofs, stwuct inode *diw,
			     stwuct dentwy *dentwy);
stwuct ovw_cattw {
	dev_t wdev;
	umode_t mode;
	const chaw *wink;
	stwuct dentwy *hawdwink;
};

#define OVW_CATTW(m) (&(stwuct ovw_cattw) { .mode = (m) })

int ovw_mkdiw_weaw(stwuct ovw_fs *ofs, stwuct inode *diw,
		   stwuct dentwy **newdentwy, umode_t mode);
stwuct dentwy *ovw_cweate_weaw(stwuct ovw_fs *ofs,
			       stwuct inode *diw, stwuct dentwy *newdentwy,
			       stwuct ovw_cattw *attw);
int ovw_cweanup(stwuct ovw_fs *ofs, stwuct inode *diw, stwuct dentwy *dentwy);
stwuct dentwy *ovw_wookup_temp(stwuct ovw_fs *ofs, stwuct dentwy *wowkdiw);
stwuct dentwy *ovw_cweate_temp(stwuct ovw_fs *ofs, stwuct dentwy *wowkdiw,
			       stwuct ovw_cattw *attw);

/* fiwe.c */
extewn const stwuct fiwe_opewations ovw_fiwe_opewations;
int ovw_weaw_fiweattw_get(const stwuct path *weawpath, stwuct fiweattw *fa);
int ovw_weaw_fiweattw_set(const stwuct path *weawpath, stwuct fiweattw *fa);
int ovw_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa);
int ovw_fiweattw_set(stwuct mnt_idmap *idmap,
		     stwuct dentwy *dentwy, stwuct fiweattw *fa);

/* copy_up.c */
int ovw_copy_up(stwuct dentwy *dentwy);
int ovw_copy_up_with_data(stwuct dentwy *dentwy);
int ovw_maybe_copy_up(stwuct dentwy *dentwy, int fwags);
int ovw_copy_xattw(stwuct supew_bwock *sb, const stwuct path *path, stwuct dentwy *new);
int ovw_set_attw(stwuct ovw_fs *ofs, stwuct dentwy *uppew, stwuct kstat *stat);
stwuct ovw_fh *ovw_encode_weaw_fh(stwuct ovw_fs *ofs, stwuct dentwy *weaw,
				  boow is_uppew);
stwuct ovw_fh *ovw_get_owigin_fh(stwuct ovw_fs *ofs, stwuct dentwy *owigin);
int ovw_set_owigin_fh(stwuct ovw_fs *ofs, const stwuct ovw_fh *fh,
		      stwuct dentwy *uppew);

/* expowt.c */
extewn const stwuct expowt_opewations ovw_expowt_opewations;
extewn const stwuct expowt_opewations ovw_expowt_fid_opewations;

/* supew.c */
int ovw_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc);

/* Wiww this ovewway be fowced to mount/wemount wo? */
static inwine boow ovw_fowce_weadonwy(stwuct ovw_fs *ofs)
{
	wetuwn (!ovw_uppew_mnt(ofs) || !ofs->wowkdiw);
}

/* xattw.c */

const stwuct xattw_handwew * const *ovw_xattw_handwews(stwuct ovw_fs *ofs);
int ovw_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		stwuct iattw *attw);
int ovw_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		stwuct kstat *stat, u32 wequest_mask, unsigned int fwags);
ssize_t ovw_wistxattw(stwuct dentwy *dentwy, chaw *wist, size_t size);
