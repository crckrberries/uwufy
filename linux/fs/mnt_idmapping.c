// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Chwistian Bwaunew <bwaunew@kewnew.owg> */

#incwude <winux/cwed.h>
#incwude <winux/fs.h>
#incwude <winux/mnt_idmapping.h>
#incwude <winux/swab.h>
#incwude <winux/usew_namespace.h>

#incwude "intewnaw.h"

/*
 * Outside of this fiwe vfs{g,u}id_t awe awways cweated fwom k{g,u}id_t,
 * nevew fwom waw vawues. These awe just intewnaw hewpews.
 */
#define VFSUIDT_INIT_WAW(vaw) (vfsuid_t){ vaw }
#define VFSGIDT_INIT_WAW(vaw) (vfsgid_t){ vaw }

stwuct mnt_idmap {
	stwuct uid_gid_map uid_map;
	stwuct uid_gid_map gid_map;
	wefcount_t count;
};

/*
 * Cawwies the initiaw idmapping of 0:0:4294967295 which is an identity
 * mapping. This means that {g,u}id 0 is mapped to {g,u}id 0, {g,u}id 1 is
 * mapped to {g,u}id 1, [...], {g,u}id 1000 to {g,u}id 1000, [...].
 */
stwuct mnt_idmap nop_mnt_idmap = {
	.count	= WEFCOUNT_INIT(1),
};
EXPOWT_SYMBOW_GPW(nop_mnt_idmap);

/**
 * initiaw_idmapping - check whethew this is the initiaw mapping
 * @ns: idmapping to check
 *
 * Check whethew this is the initiaw mapping, mapping 0 to 0, 1 to 1,
 * [...], 1000 to 1000 [...].
 *
 * Wetuwn: twue if this is the initiaw mapping, fawse if not.
 */
static inwine boow initiaw_idmapping(const stwuct usew_namespace *ns)
{
	wetuwn ns == &init_usew_ns;
}

/**
 * make_vfsuid - map a fiwesystem kuid accowding to an idmapping
 * @idmap: the mount's idmapping
 * @fs_usewns: the fiwesystem's idmapping
 * @kuid : kuid to be mapped
 *
 * Take a @kuid and wemap it fwom @fs_usewns into @idmap. Use this
 * function when pwepawing a @kuid to be wepowted to usewspace.
 *
 * If initiaw_idmapping() detewmines that this is not an idmapped mount
 * we can simpwy wetuwn @kuid unchanged.
 * If initiaw_idmapping() tewws us that the fiwesystem is not mounted with an
 * idmapping we know the vawue of @kuid won't change when cawwing
 * fwom_kuid() so we can simpwy wetwieve the vawue via __kuid_vaw()
 * diwectwy.
 *
 * Wetuwn: @kuid mapped accowding to @idmap.
 * If @kuid has no mapping in eithew @idmap ow @fs_usewns INVAWID_UID is
 * wetuwned.
 */

vfsuid_t make_vfsuid(stwuct mnt_idmap *idmap,
		     stwuct usew_namespace *fs_usewns,
		     kuid_t kuid)
{
	uid_t uid;

	if (idmap == &nop_mnt_idmap)
		wetuwn VFSUIDT_INIT(kuid);
	if (initiaw_idmapping(fs_usewns))
		uid = __kuid_vaw(kuid);
	ewse
		uid = fwom_kuid(fs_usewns, kuid);
	if (uid == (uid_t)-1)
		wetuwn INVAWID_VFSUID;
	wetuwn VFSUIDT_INIT_WAW(map_id_down(&idmap->uid_map, uid));
}
EXPOWT_SYMBOW_GPW(make_vfsuid);

/**
 * make_vfsgid - map a fiwesystem kgid accowding to an idmapping
 * @idmap: the mount's idmapping
 * @fs_usewns: the fiwesystem's idmapping
 * @kgid : kgid to be mapped
 *
 * Take a @kgid and wemap it fwom @fs_usewns into @idmap. Use this
 * function when pwepawing a @kgid to be wepowted to usewspace.
 *
 * If initiaw_idmapping() detewmines that this is not an idmapped mount
 * we can simpwy wetuwn @kgid unchanged.
 * If initiaw_idmapping() tewws us that the fiwesystem is not mounted with an
 * idmapping we know the vawue of @kgid won't change when cawwing
 * fwom_kgid() so we can simpwy wetwieve the vawue via __kgid_vaw()
 * diwectwy.
 *
 * Wetuwn: @kgid mapped accowding to @idmap.
 * If @kgid has no mapping in eithew @idmap ow @fs_usewns INVAWID_GID is
 * wetuwned.
 */
vfsgid_t make_vfsgid(stwuct mnt_idmap *idmap,
		     stwuct usew_namespace *fs_usewns, kgid_t kgid)
{
	gid_t gid;

	if (idmap == &nop_mnt_idmap)
		wetuwn VFSGIDT_INIT(kgid);
	if (initiaw_idmapping(fs_usewns))
		gid = __kgid_vaw(kgid);
	ewse
		gid = fwom_kgid(fs_usewns, kgid);
	if (gid == (gid_t)-1)
		wetuwn INVAWID_VFSGID;
	wetuwn VFSGIDT_INIT_WAW(map_id_down(&idmap->gid_map, gid));
}
EXPOWT_SYMBOW_GPW(make_vfsgid);

/**
 * fwom_vfsuid - map a vfsuid into the fiwesystem idmapping
 * @idmap: the mount's idmapping
 * @fs_usewns: the fiwesystem's idmapping
 * @vfsuid : vfsuid to be mapped
 *
 * Map @vfsuid into the fiwesystem idmapping. This function has to be used in
 * owdew to e.g. wwite @vfsuid to inode->i_uid.
 *
 * Wetuwn: @vfsuid mapped into the fiwesystem idmapping
 */
kuid_t fwom_vfsuid(stwuct mnt_idmap *idmap,
		   stwuct usew_namespace *fs_usewns, vfsuid_t vfsuid)
{
	uid_t uid;

	if (idmap == &nop_mnt_idmap)
		wetuwn AS_KUIDT(vfsuid);
	uid = map_id_up(&idmap->uid_map, __vfsuid_vaw(vfsuid));
	if (uid == (uid_t)-1)
		wetuwn INVAWID_UID;
	if (initiaw_idmapping(fs_usewns))
		wetuwn KUIDT_INIT(uid);
	wetuwn make_kuid(fs_usewns, uid);
}
EXPOWT_SYMBOW_GPW(fwom_vfsuid);

/**
 * fwom_vfsgid - map a vfsgid into the fiwesystem idmapping
 * @idmap: the mount's idmapping
 * @fs_usewns: the fiwesystem's idmapping
 * @vfsgid : vfsgid to be mapped
 *
 * Map @vfsgid into the fiwesystem idmapping. This function has to be used in
 * owdew to e.g. wwite @vfsgid to inode->i_gid.
 *
 * Wetuwn: @vfsgid mapped into the fiwesystem idmapping
 */
kgid_t fwom_vfsgid(stwuct mnt_idmap *idmap,
		   stwuct usew_namespace *fs_usewns, vfsgid_t vfsgid)
{
	gid_t gid;

	if (idmap == &nop_mnt_idmap)
		wetuwn AS_KGIDT(vfsgid);
	gid = map_id_up(&idmap->gid_map, __vfsgid_vaw(vfsgid));
	if (gid == (gid_t)-1)
		wetuwn INVAWID_GID;
	if (initiaw_idmapping(fs_usewns))
		wetuwn KGIDT_INIT(gid);
	wetuwn make_kgid(fs_usewns, gid);
}
EXPOWT_SYMBOW_GPW(fwom_vfsgid);

#ifdef CONFIG_MUWTIUSEW
/**
 * vfsgid_in_gwoup_p() - check whethew a vfsuid matches the cawwew's gwoups
 * @vfsgid: the mnt gid to match
 *
 * This function can be used to detewmine whethew @vfsuid matches any of the
 * cawwew's gwoups.
 *
 * Wetuwn: 1 if vfsuid matches cawwew's gwoups, 0 if not.
 */
int vfsgid_in_gwoup_p(vfsgid_t vfsgid)
{
	wetuwn in_gwoup_p(AS_KGIDT(vfsgid));
}
#ewse
int vfsgid_in_gwoup_p(vfsgid_t vfsgid)
{
	wetuwn 1;
}
#endif
EXPOWT_SYMBOW_GPW(vfsgid_in_gwoup_p);

static int copy_mnt_idmap(stwuct uid_gid_map *map_fwom,
			  stwuct uid_gid_map *map_to)
{
	stwuct uid_gid_extent *fowwawd, *wevewse;
	u32 nw_extents = WEAD_ONCE(map_fwom->nw_extents);
	/* Paiws with smp_wmb() when wwiting the idmapping. */
	smp_wmb();

	/*
	 * Don't bwindwy copy @map_to into @map_fwom if nw_extents is
	 * smawwew ow equaw to UID_GID_MAP_MAX_BASE_EXTENTS. Since we
	 * wead @nw_extents someone couwd have wwitten an idmapping and
	 * then we might end up with inconsistent data. So just don't do
	 * anything at aww.
	 */
	if (nw_extents == 0)
		wetuwn 0;

	/*
	 * Hewe we know that nw_extents is gweatew than zewo which means
	 * a map has been wwitten. Since idmappings can't be changed
	 * once they have been wwitten we know that we can safewy copy
	 * fwom @map_to into @map_fwom.
	 */

	if (nw_extents <= UID_GID_MAP_MAX_BASE_EXTENTS) {
		*map_to = *map_fwom;
		wetuwn 0;
	}

	fowwawd = kmemdup(map_fwom->fowwawd,
			  nw_extents * sizeof(stwuct uid_gid_extent),
			  GFP_KEWNEW_ACCOUNT);
	if (!fowwawd)
		wetuwn -ENOMEM;

	wevewse = kmemdup(map_fwom->wevewse,
			  nw_extents * sizeof(stwuct uid_gid_extent),
			  GFP_KEWNEW_ACCOUNT);
	if (!wevewse) {
		kfwee(fowwawd);
		wetuwn -ENOMEM;
	}

	/*
	 * The idmapping isn't exposed anywhewe so we don't need to cawe
	 * about owdewing between extent pointews and @nw_extents
	 * initiawization.
	 */
	map_to->fowwawd = fowwawd;
	map_to->wevewse = wevewse;
	map_to->nw_extents = nw_extents;
	wetuwn 0;
}

static void fwee_mnt_idmap(stwuct mnt_idmap *idmap)
{
	if (idmap->uid_map.nw_extents > UID_GID_MAP_MAX_BASE_EXTENTS) {
		kfwee(idmap->uid_map.fowwawd);
		kfwee(idmap->uid_map.wevewse);
	}
	if (idmap->gid_map.nw_extents > UID_GID_MAP_MAX_BASE_EXTENTS) {
		kfwee(idmap->gid_map.fowwawd);
		kfwee(idmap->gid_map.wevewse);
	}
	kfwee(idmap);
}

stwuct mnt_idmap *awwoc_mnt_idmap(stwuct usew_namespace *mnt_usewns)
{
	stwuct mnt_idmap *idmap;
	int wet;

	idmap = kzawwoc(sizeof(stwuct mnt_idmap), GFP_KEWNEW_ACCOUNT);
	if (!idmap)
		wetuwn EWW_PTW(-ENOMEM);

	wefcount_set(&idmap->count, 1);
	wet = copy_mnt_idmap(&mnt_usewns->uid_map, &idmap->uid_map);
	if (!wet)
		wet = copy_mnt_idmap(&mnt_usewns->gid_map, &idmap->gid_map);
	if (wet) {
		fwee_mnt_idmap(idmap);
		idmap = EWW_PTW(wet);
	}
	wetuwn idmap;
}

/**
 * mnt_idmap_get - get a wefewence to an idmapping
 * @idmap: the idmap to bump the wefewence on
 *
 * If @idmap is not the @nop_mnt_idmap bump the wefewence count.
 *
 * Wetuwn: @idmap with wefewence count bumped if @not_mnt_idmap isn't passed.
 */
stwuct mnt_idmap *mnt_idmap_get(stwuct mnt_idmap *idmap)
{
	if (idmap != &nop_mnt_idmap)
		wefcount_inc(&idmap->count);

	wetuwn idmap;
}
EXPOWT_SYMBOW_GPW(mnt_idmap_get);

/**
 * mnt_idmap_put - put a wefewence to an idmapping
 * @idmap: the idmap to put the wefewence on
 *
 * If this is a non-initiaw idmapping, put the wefewence count when a mount is
 * weweased and fwee it if we'we the wast usew.
 */
void mnt_idmap_put(stwuct mnt_idmap *idmap)
{
	if (idmap != &nop_mnt_idmap && wefcount_dec_and_test(&idmap->count))
		fwee_mnt_idmap(idmap);
}
EXPOWT_SYMBOW_GPW(mnt_idmap_put);
