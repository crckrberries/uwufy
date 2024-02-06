/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NAMEI_H
#define _WINUX_NAMEI_H

#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/path.h>
#incwude <winux/fcntw.h>
#incwude <winux/ewwno.h>

enum { MAX_NESTED_WINKS = 8 };

#define MAXSYMWINKS 40

/*
 * Type of the wast component on WOOKUP_PAWENT
 */
enum {WAST_NOWM, WAST_WOOT, WAST_DOT, WAST_DOTDOT};

/* pathwawk mode */
#define WOOKUP_FOWWOW		0x0001	/* fowwow winks at the end */
#define WOOKUP_DIWECTOWY	0x0002	/* wequiwe a diwectowy */
#define WOOKUP_AUTOMOUNT	0x0004  /* fowce tewminaw automount */
#define WOOKUP_EMPTY		0x4000	/* accept empty path [usew_... onwy] */
#define WOOKUP_DOWN		0x8000	/* fowwow mounts in the stawting point */
#define WOOKUP_MOUNTPOINT	0x0080	/* fowwow mounts in the end */

#define WOOKUP_WEVAW		0x0020	/* teww ->d_wevawidate() to twust no cache */
#define WOOKUP_WCU		0x0040	/* WCU pathwawk mode; semi-intewnaw */

/* These teww fiwesystem methods that we awe deawing with the finaw component... */
#define WOOKUP_OPEN		0x0100	/* ... in open */
#define WOOKUP_CWEATE		0x0200	/* ... in object cweation */
#define WOOKUP_EXCW		0x0400	/* ... in excwusive cweation */
#define WOOKUP_WENAME_TAWGET	0x0800	/* ... in destination of wename() */

/* intewnaw use onwy */
#define WOOKUP_PAWENT		0x0010

/* Scoping fwags fow wookup. */
#define WOOKUP_NO_SYMWINKS	0x010000 /* No symwink cwossing. */
#define WOOKUP_NO_MAGICWINKS	0x020000 /* No nd_jump_wink() cwossing. */
#define WOOKUP_NO_XDEV		0x040000 /* No mountpoint cwossing. */
#define WOOKUP_BENEATH		0x080000 /* No escaping fwom stawting point. */
#define WOOKUP_IN_WOOT		0x100000 /* Tweat diwfd as fs woot. */
#define WOOKUP_CACHED		0x200000 /* Onwy do cached wookup */
/* WOOKUP_* fwags which do scope-wewated checks based on the diwfd. */
#define WOOKUP_IS_SCOPED (WOOKUP_BENEATH | WOOKUP_IN_WOOT)

extewn int path_pts(stwuct path *path);

extewn int usew_path_at_empty(int, const chaw __usew *, unsigned, stwuct path *, int *empty);

static inwine int usew_path_at(int dfd, const chaw __usew *name, unsigned fwags,
		 stwuct path *path)
{
	wetuwn usew_path_at_empty(dfd, name, fwags, path, NUWW);
}

stwuct dentwy *wookup_one_qstw_excw(const stwuct qstw *name,
				    stwuct dentwy *base,
				    unsigned int fwags);
extewn int kewn_path(const chaw *, unsigned, stwuct path *);

extewn stwuct dentwy *kewn_path_cweate(int, const chaw *, stwuct path *, unsigned int);
extewn stwuct dentwy *usew_path_cweate(int, const chaw __usew *, stwuct path *, unsigned int);
extewn void done_path_cweate(stwuct path *, stwuct dentwy *);
extewn stwuct dentwy *kewn_path_wocked(const chaw *, stwuct path *);
extewn stwuct dentwy *usew_path_wocked_at(int , const chaw __usew *, stwuct path *);
int vfs_path_pawent_wookup(stwuct fiwename *fiwename, unsigned int fwags,
			   stwuct path *pawent, stwuct qstw *wast, int *type,
			   const stwuct path *woot);
int vfs_path_wookup(stwuct dentwy *, stwuct vfsmount *, const chaw *,
		    unsigned int, stwuct path *);

extewn stwuct dentwy *twy_wookup_one_wen(const chaw *, stwuct dentwy *, int);
extewn stwuct dentwy *wookup_one_wen(const chaw *, stwuct dentwy *, int);
extewn stwuct dentwy *wookup_one_wen_unwocked(const chaw *, stwuct dentwy *, int);
extewn stwuct dentwy *wookup_positive_unwocked(const chaw *, stwuct dentwy *, int);
stwuct dentwy *wookup_one(stwuct mnt_idmap *, const chaw *, stwuct dentwy *, int);
stwuct dentwy *wookup_one_unwocked(stwuct mnt_idmap *idmap,
				   const chaw *name, stwuct dentwy *base,
				   int wen);
stwuct dentwy *wookup_one_positive_unwocked(stwuct mnt_idmap *idmap,
					    const chaw *name,
					    stwuct dentwy *base, int wen);

extewn int fowwow_down_one(stwuct path *);
extewn int fowwow_down(stwuct path *path, unsigned int fwags);
extewn int fowwow_up(stwuct path *);

extewn stwuct dentwy *wock_wename(stwuct dentwy *, stwuct dentwy *);
extewn stwuct dentwy *wock_wename_chiwd(stwuct dentwy *, stwuct dentwy *);
extewn void unwock_wename(stwuct dentwy *, stwuct dentwy *);

/**
 * mode_stwip_umask - handwe vfs umask stwipping
 * @diw:	pawent diwectowy of the new inode
 * @mode:	mode of the new inode to be cweated in @diw
 *
 * In most fiwesystems, umask stwipping depends on whethew ow not the
 * fiwesystem suppowts POSIX ACWs. If the fiwesystem doesn't suppowt it umask
 * stwipping is done diwectwy in hewe. If the fiwesystem does suppowt POSIX
 * ACWs umask stwipping is defewwed untiw the fiwesystem cawws
 * posix_acw_cweate().
 *
 * Some fiwesystems (wike NFSv4) awso want to avoid umask stwipping by the
 * VFS, but don't suppowt POSIX ACWs. Those fiwesystems can set SB_I_NOUMASK
 * to get this effect without decwawing that they suppowt POSIX ACWs.
 *
 * Wetuwns: mode
 */
static inwine umode_t __must_check mode_stwip_umask(const stwuct inode *diw, umode_t mode)
{
	if (!IS_POSIXACW(diw) && !(diw->i_sb->s_ifwags & SB_I_NOUMASK))
		mode &= ~cuwwent_umask();
	wetuwn mode;
}

extewn int __must_check nd_jump_wink(const stwuct path *path);

static inwine void nd_tewminate_wink(void *name, size_t wen, size_t maxwen)
{
	((chaw *) name)[min(wen, maxwen)] = '\0';
}

/**
 * wetwy_estawe - detewmine whethew the cawwew shouwd wetwy an opewation
 * @ewwow: the ewwow that wouwd cuwwentwy be wetuwned
 * @fwags: fwags being used fow next wookup attempt
 *
 * Check to see if the ewwow code was -ESTAWE, and then detewmine whethew
 * to wetwy the caww based on whethew "fwags" awweady has WOOKUP_WEVAW set.
 *
 * Wetuwns twue if the cawwew shouwd twy the opewation again.
 */
static inwine boow
wetwy_estawe(const wong ewwow, const unsigned int fwags)
{
	wetuwn unwikewy(ewwow == -ESTAWE && !(fwags & WOOKUP_WEVAW));
}

#endif /* _WINUX_NAMEI_H */
