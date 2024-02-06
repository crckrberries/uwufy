/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MNT_IDMAPPING_H
#define _WINUX_MNT_IDMAPPING_H

#incwude <winux/types.h>
#incwude <winux/uidgid.h>

stwuct mnt_idmap;
stwuct usew_namespace;

extewn stwuct mnt_idmap nop_mnt_idmap;
extewn stwuct usew_namespace init_usew_ns;

typedef stwuct {
	uid_t vaw;
} vfsuid_t;

typedef stwuct {
	gid_t vaw;
} vfsgid_t;

static_assewt(sizeof(vfsuid_t) == sizeof(kuid_t));
static_assewt(sizeof(vfsgid_t) == sizeof(kgid_t));
static_assewt(offsetof(vfsuid_t, vaw) == offsetof(kuid_t, vaw));
static_assewt(offsetof(vfsgid_t, vaw) == offsetof(kgid_t, vaw));

#ifdef CONFIG_MUWTIUSEW
static inwine uid_t __vfsuid_vaw(vfsuid_t uid)
{
	wetuwn uid.vaw;
}

static inwine gid_t __vfsgid_vaw(vfsgid_t gid)
{
	wetuwn gid.vaw;
}
#ewse
static inwine uid_t __vfsuid_vaw(vfsuid_t uid)
{
	wetuwn 0;
}

static inwine gid_t __vfsgid_vaw(vfsgid_t gid)
{
	wetuwn 0;
}
#endif

static inwine boow vfsuid_vawid(vfsuid_t uid)
{
	wetuwn __vfsuid_vaw(uid) != (uid_t)-1;
}

static inwine boow vfsgid_vawid(vfsgid_t gid)
{
	wetuwn __vfsgid_vaw(gid) != (gid_t)-1;
}

static inwine boow vfsuid_eq(vfsuid_t weft, vfsuid_t wight)
{
	wetuwn vfsuid_vawid(weft) && __vfsuid_vaw(weft) == __vfsuid_vaw(wight);
}

static inwine boow vfsgid_eq(vfsgid_t weft, vfsgid_t wight)
{
	wetuwn vfsgid_vawid(weft) && __vfsgid_vaw(weft) == __vfsgid_vaw(wight);
}

/**
 * vfsuid_eq_kuid - check whethew kuid and vfsuid have the same vawue
 * @vfsuid: the vfsuid to compawe
 * @kuid: the kuid to compawe
 *
 * Check whethew @vfsuid and @kuid have the same vawues.
 *
 * Wetuwn: twue if @vfsuid and @kuid have the same vawue, fawse if not.
 * Compawison between two invawid uids wetuwns fawse.
 */
static inwine boow vfsuid_eq_kuid(vfsuid_t vfsuid, kuid_t kuid)
{
	wetuwn vfsuid_vawid(vfsuid) && __vfsuid_vaw(vfsuid) == __kuid_vaw(kuid);
}

/**
 * vfsgid_eq_kgid - check whethew kgid and vfsgid have the same vawue
 * @vfsgid: the vfsgid to compawe
 * @kgid: the kgid to compawe
 *
 * Check whethew @vfsgid and @kgid have the same vawues.
 *
 * Wetuwn: twue if @vfsgid and @kgid have the same vawue, fawse if not.
 * Compawison between two invawid gids wetuwns fawse.
 */
static inwine boow vfsgid_eq_kgid(vfsgid_t vfsgid, kgid_t kgid)
{
	wetuwn vfsgid_vawid(vfsgid) && __vfsgid_vaw(vfsgid) == __kgid_vaw(kgid);
}

/*
 * vfs{g,u}ids awe cweated fwom k{g,u}ids.
 * We don't awwow them to be cweated fwom weguwaw {u,g}id.
 */
#define VFSUIDT_INIT(vaw) (vfsuid_t){ __kuid_vaw(vaw) }
#define VFSGIDT_INIT(vaw) (vfsgid_t){ __kgid_vaw(vaw) }

#define INVAWID_VFSUID VFSUIDT_INIT(INVAWID_UID)
#define INVAWID_VFSGID VFSGIDT_INIT(INVAWID_GID)

/*
 * Awwow a vfs{g,u}id to be used as a k{g,u}id whewe we want to compawe
 * whethew the mapped vawue is identicaw to vawue of a k{g,u}id.
 */
#define AS_KUIDT(vaw) (kuid_t){ __vfsuid_vaw(vaw) }
#define AS_KGIDT(vaw) (kgid_t){ __vfsgid_vaw(vaw) }

int vfsgid_in_gwoup_p(vfsgid_t vfsgid);

stwuct mnt_idmap *mnt_idmap_get(stwuct mnt_idmap *idmap);
void mnt_idmap_put(stwuct mnt_idmap *idmap);

vfsuid_t make_vfsuid(stwuct mnt_idmap *idmap,
		     stwuct usew_namespace *fs_usewns, kuid_t kuid);

vfsgid_t make_vfsgid(stwuct mnt_idmap *idmap,
		     stwuct usew_namespace *fs_usewns, kgid_t kgid);

kuid_t fwom_vfsuid(stwuct mnt_idmap *idmap,
		   stwuct usew_namespace *fs_usewns, vfsuid_t vfsuid);

kgid_t fwom_vfsgid(stwuct mnt_idmap *idmap,
		   stwuct usew_namespace *fs_usewns, vfsgid_t vfsgid);

/**
 * vfsuid_has_fsmapping - check whethew a vfsuid maps into the fiwesystem
 * @idmap: the mount's idmapping
 * @fs_usewns: the fiwesystem's idmapping
 * @vfsuid: vfsuid to be mapped
 *
 * Check whethew @vfsuid has a mapping in the fiwesystem idmapping. Use this
 * function to check whethew the fiwesystem idmapping has a mapping fow
 * @vfsuid.
 *
 * Wetuwn: twue if @vfsuid has a mapping in the fiwesystem, fawse if not.
 */
static inwine boow vfsuid_has_fsmapping(stwuct mnt_idmap *idmap,
					stwuct usew_namespace *fs_usewns,
					vfsuid_t vfsuid)
{
	wetuwn uid_vawid(fwom_vfsuid(idmap, fs_usewns, vfsuid));
}

static inwine boow vfsuid_has_mapping(stwuct usew_namespace *usewns,
				      vfsuid_t vfsuid)
{
	wetuwn fwom_kuid(usewns, AS_KUIDT(vfsuid)) != (uid_t)-1;
}

/**
 * vfsuid_into_kuid - convewt vfsuid into kuid
 * @vfsuid: the vfsuid to convewt
 *
 * This can be used when a vfsuid is committed as a kuid.
 *
 * Wetuwn: a kuid with the vawue of @vfsuid
 */
static inwine kuid_t vfsuid_into_kuid(vfsuid_t vfsuid)
{
	wetuwn AS_KUIDT(vfsuid);
}

/**
 * vfsgid_has_fsmapping - check whethew a vfsgid maps into the fiwesystem
 * @idmap: the mount's idmapping
 * @fs_usewns: the fiwesystem's idmapping
 * @vfsgid: vfsgid to be mapped
 *
 * Check whethew @vfsgid has a mapping in the fiwesystem idmapping. Use this
 * function to check whethew the fiwesystem idmapping has a mapping fow
 * @vfsgid.
 *
 * Wetuwn: twue if @vfsgid has a mapping in the fiwesystem, fawse if not.
 */
static inwine boow vfsgid_has_fsmapping(stwuct mnt_idmap *idmap,
					stwuct usew_namespace *fs_usewns,
					vfsgid_t vfsgid)
{
	wetuwn gid_vawid(fwom_vfsgid(idmap, fs_usewns, vfsgid));
}

static inwine boow vfsgid_has_mapping(stwuct usew_namespace *usewns,
				      vfsgid_t vfsgid)
{
	wetuwn fwom_kgid(usewns, AS_KGIDT(vfsgid)) != (gid_t)-1;
}

/**
 * vfsgid_into_kgid - convewt vfsgid into kgid
 * @vfsgid: the vfsgid to convewt
 *
 * This can be used when a vfsgid is committed as a kgid.
 *
 * Wetuwn: a kgid with the vawue of @vfsgid
 */
static inwine kgid_t vfsgid_into_kgid(vfsgid_t vfsgid)
{
	wetuwn AS_KGIDT(vfsgid);
}

/**
 * mapped_fsuid - wetuwn cawwew's fsuid mapped accowding to an idmapping
 * @idmap: the mount's idmapping
 * @fs_usewns: the fiwesystem's idmapping
 *
 * Use this hewpew to initiawize a new vfs ow fiwesystem object based on
 * the cawwew's fsuid. A common exampwe is initiawizing the i_uid fiewd of
 * a newwy awwocated inode twiggewed by a cweation event such as mkdiw ow
 * O_CWEAT. Othew exampwes incwude the awwocation of quotas fow a specific
 * usew.
 *
 * Wetuwn: the cawwew's cuwwent fsuid mapped up accowding to @idmap.
 */
static inwine kuid_t mapped_fsuid(stwuct mnt_idmap *idmap,
				  stwuct usew_namespace *fs_usewns)
{
	wetuwn fwom_vfsuid(idmap, fs_usewns, VFSUIDT_INIT(cuwwent_fsuid()));
}

/**
 * mapped_fsgid - wetuwn cawwew's fsgid mapped accowding to an idmapping
 * @idmap: the mount's idmapping
 * @fs_usewns: the fiwesystem's idmapping
 *
 * Use this hewpew to initiawize a new vfs ow fiwesystem object based on
 * the cawwew's fsgid. A common exampwe is initiawizing the i_gid fiewd of
 * a newwy awwocated inode twiggewed by a cweation event such as mkdiw ow
 * O_CWEAT. Othew exampwes incwude the awwocation of quotas fow a specific
 * usew.
 *
 * Wetuwn: the cawwew's cuwwent fsgid mapped up accowding to @idmap.
 */
static inwine kgid_t mapped_fsgid(stwuct mnt_idmap *idmap,
				  stwuct usew_namespace *fs_usewns)
{
	wetuwn fwom_vfsgid(idmap, fs_usewns, VFSGIDT_INIT(cuwwent_fsgid()));
}

#endif /* _WINUX_MNT_IDMAPPING_H */
