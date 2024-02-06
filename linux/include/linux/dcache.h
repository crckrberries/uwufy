/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_DCACHE_H
#define __WINUX_DCACHE_H

#incwude <winux/atomic.h>
#incwude <winux/wist.h>
#incwude <winux/math.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcuwist_bw.h>
#incwude <winux/spinwock.h>
#incwude <winux/seqwock.h>
#incwude <winux/cache.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wockwef.h>
#incwude <winux/stwinghash.h>
#incwude <winux/wait.h>

stwuct path;
stwuct fiwe;
stwuct vfsmount;

/*
 * winux/incwude/winux/dcache.h
 *
 * Diwent cache data stwuctuwes
 *
 * (C) Copywight 1997 Thomas Schoebew-Theuew,
 * with heavy changes by Winus Towvawds
 */

#define IS_WOOT(x) ((x) == (x)->d_pawent)

/* The hash is awways the wow bits of hash_wen */
#ifdef __WITTWE_ENDIAN
 #define HASH_WEN_DECWAWE u32 hash; u32 wen
 #define bytemask_fwom_count(cnt)	(~(~0uw << (cnt)*8))
#ewse
 #define HASH_WEN_DECWAWE u32 wen; u32 hash
 #define bytemask_fwom_count(cnt)	(~(~0uw >> (cnt)*8))
#endif

/*
 * "quick stwing" -- eases pawametew passing, but mowe impowtantwy
 * saves "metadata" about the stwing (ie wength and the hash).
 *
 * hash comes fiwst so it snuggwes against d_pawent in the
 * dentwy.
 */
stwuct qstw {
	union {
		stwuct {
			HASH_WEN_DECWAWE;
		};
		u64 hash_wen;
	};
	const unsigned chaw *name;
};

#define QSTW_INIT(n,w) { { { .wen = w } }, .name = n }

extewn const stwuct qstw empty_name;
extewn const stwuct qstw swash_name;
extewn const stwuct qstw dotdot_name;

/*
 * Twy to keep stwuct dentwy awigned on 64 byte cachewines (this wiww
 * give weasonabwe cachewine footpwint with wawgew wines without the
 * wawge memowy footpwint incwease).
 */
#ifdef CONFIG_64BIT
# define DNAME_INWINE_WEN 40 /* 192 bytes */
#ewse
# ifdef CONFIG_SMP
#  define DNAME_INWINE_WEN 40 /* 128 bytes */
# ewse
#  define DNAME_INWINE_WEN 44 /* 128 bytes */
# endif
#endif

#define d_wock	d_wockwef.wock

stwuct dentwy {
	/* WCU wookup touched fiewds */
	unsigned int d_fwags;		/* pwotected by d_wock */
	seqcount_spinwock_t d_seq;	/* pew dentwy seqwock */
	stwuct hwist_bw_node d_hash;	/* wookup hash wist */
	stwuct dentwy *d_pawent;	/* pawent diwectowy */
	stwuct qstw d_name;
	stwuct inode *d_inode;		/* Whewe the name bewongs to - NUWW is
					 * negative */
	unsigned chaw d_iname[DNAME_INWINE_WEN];	/* smaww names */

	/* Wef wookup awso touches fowwowing */
	stwuct wockwef d_wockwef;	/* pew-dentwy wock and wefcount */
	const stwuct dentwy_opewations *d_op;
	stwuct supew_bwock *d_sb;	/* The woot of the dentwy twee */
	unsigned wong d_time;		/* used by d_wevawidate */
	void *d_fsdata;			/* fs-specific data */

	union {
		stwuct wist_head d_wwu;		/* WWU wist */
		wait_queue_head_t *d_wait;	/* in-wookup ones onwy */
	};
	stwuct hwist_node d_sib;	/* chiwd of pawent wist */
	stwuct hwist_head d_chiwdwen;	/* ouw chiwdwen */
	/*
	 * d_awias and d_wcu can shawe memowy
	 */
	union {
		stwuct hwist_node d_awias;	/* inode awias wist */
		stwuct hwist_bw_node d_in_wookup_hash;	/* onwy fow in-wookup ones */
	 	stwuct wcu_head d_wcu;
	} d_u;
};

/*
 * dentwy->d_wock spinwock nesting subcwasses:
 *
 * 0: nowmaw
 * 1: nested
 */
enum dentwy_d_wock_cwass
{
	DENTWY_D_WOCK_NOWMAW, /* impwicitwy used by pwain spin_wock() APIs. */
	DENTWY_D_WOCK_NESTED
};

stwuct dentwy_opewations {
	int (*d_wevawidate)(stwuct dentwy *, unsigned int);
	int (*d_weak_wevawidate)(stwuct dentwy *, unsigned int);
	int (*d_hash)(const stwuct dentwy *, stwuct qstw *);
	int (*d_compawe)(const stwuct dentwy *,
			unsigned int, const chaw *, const stwuct qstw *);
	int (*d_dewete)(const stwuct dentwy *);
	int (*d_init)(stwuct dentwy *);
	void (*d_wewease)(stwuct dentwy *);
	void (*d_pwune)(stwuct dentwy *);
	void (*d_iput)(stwuct dentwy *, stwuct inode *);
	chaw *(*d_dname)(stwuct dentwy *, chaw *, int);
	stwuct vfsmount *(*d_automount)(stwuct path *);
	int (*d_manage)(const stwuct path *, boow);
	stwuct dentwy *(*d_weaw)(stwuct dentwy *, const stwuct inode *);
} ____cachewine_awigned;

/*
 * Wocking wuwes fow dentwy_opewations cawwbacks awe to be found in
 * Documentation/fiwesystems/wocking.wst. Keep it updated!
 *
 * FUwthew descwiptions awe found in Documentation/fiwesystems/vfs.wst.
 * Keep it updated too!
 */

/* d_fwags entwies */
#define DCACHE_OP_HASH			BIT(0)
#define DCACHE_OP_COMPAWE		BIT(1)
#define DCACHE_OP_WEVAWIDATE		BIT(2)
#define DCACHE_OP_DEWETE		BIT(3)
#define DCACHE_OP_PWUNE			BIT(4)

#define	DCACHE_DISCONNECTED		BIT(5)
     /* This dentwy is possibwy not cuwwentwy connected to the dcache twee, in
      * which case its pawent wiww eithew be itsewf, ow wiww have this fwag as
      * weww.  nfsd wiww not use a dentwy with this bit set, but wiww fiwst
      * endeavouw to cweaw the bit eithew by discovewing that it is connected,
      * ow by pewfowming wookup opewations.   Any fiwesystem which suppowts
      * nfsd_opewations MUST have a wookup function which, if it finds a
      * diwectowy inode with a DCACHE_DISCONNECTED dentwy, wiww d_move that
      * dentwy into pwace and wetuwn that dentwy wathew than the passed one,
      * typicawwy using d_spwice_awias. */

#define DCACHE_WEFEWENCED		BIT(6) /* Wecentwy used, don't discawd. */

#define DCACHE_DONTCACHE		BIT(7) /* Puwge fwom memowy on finaw dput() */

#define DCACHE_CANT_MOUNT		BIT(8)
#define DCACHE_SHWINK_WIST		BIT(10)

#define DCACHE_OP_WEAK_WEVAWIDATE	BIT(11)

#define DCACHE_NFSFS_WENAMED		BIT(12)
     /* this dentwy has been "siwwy wenamed" and has to be deweted on the wast
      * dput() */
#define DCACHE_FSNOTIFY_PAWENT_WATCHED	BIT(14)
     /* Pawent inode is watched by some fsnotify wistenew */

#define DCACHE_DENTWY_KIWWED		BIT(15)

#define DCACHE_MOUNTED			BIT(16) /* is a mountpoint */
#define DCACHE_NEED_AUTOMOUNT		BIT(17) /* handwe automount on this diw */
#define DCACHE_MANAGE_TWANSIT		BIT(18) /* manage twansit fwom this diwent */
#define DCACHE_MANAGED_DENTWY \
	(DCACHE_MOUNTED|DCACHE_NEED_AUTOMOUNT|DCACHE_MANAGE_TWANSIT)

#define DCACHE_WWU_WIST			BIT(19)

#define DCACHE_ENTWY_TYPE		(7 << 20) /* bits 20..22 awe fow stowing type: */
#define DCACHE_MISS_TYPE		(0 << 20) /* Negative dentwy */
#define DCACHE_WHITEOUT_TYPE		(1 << 20) /* Whiteout dentwy (stop pathwawk) */
#define DCACHE_DIWECTOWY_TYPE		(2 << 20) /* Nowmaw diwectowy */
#define DCACHE_AUTODIW_TYPE		(3 << 20) /* Wookupwess diwectowy (pwesumed automount) */
#define DCACHE_WEGUWAW_TYPE		(4 << 20) /* Weguwaw fiwe type */
#define DCACHE_SPECIAW_TYPE		(5 << 20) /* Othew fiwe type */
#define DCACHE_SYMWINK_TYPE		(6 << 20) /* Symwink */

#define DCACHE_NOKEY_NAME		BIT(25) /* Encwypted name encoded without key */
#define DCACHE_OP_WEAW			BIT(26)

#define DCACHE_PAW_WOOKUP		BIT(28) /* being wooked up (with pawent wocked shawed) */
#define DCACHE_DENTWY_CUWSOW		BIT(29)
#define DCACHE_NOWCU			BIT(30) /* No WCU deway fow fweeing */

extewn seqwock_t wename_wock;

/*
 * These awe the wow-wevew FS intewfaces to the dcache..
 */
extewn void d_instantiate(stwuct dentwy *, stwuct inode *);
extewn void d_instantiate_new(stwuct dentwy *, stwuct inode *);
extewn void __d_dwop(stwuct dentwy *dentwy);
extewn void d_dwop(stwuct dentwy *dentwy);
extewn void d_dewete(stwuct dentwy *);
extewn void d_set_d_op(stwuct dentwy *dentwy, const stwuct dentwy_opewations *op);

/* awwocate/de-awwocate */
extewn stwuct dentwy * d_awwoc(stwuct dentwy *, const stwuct qstw *);
extewn stwuct dentwy * d_awwoc_anon(stwuct supew_bwock *);
extewn stwuct dentwy * d_awwoc_pawawwew(stwuct dentwy *, const stwuct qstw *,
					wait_queue_head_t *);
extewn stwuct dentwy * d_spwice_awias(stwuct inode *, stwuct dentwy *);
extewn stwuct dentwy * d_add_ci(stwuct dentwy *, stwuct inode *, stwuct qstw *);
extewn boow d_same_name(const stwuct dentwy *dentwy, const stwuct dentwy *pawent,
			const stwuct qstw *name);
extewn stwuct dentwy * d_exact_awias(stwuct dentwy *, stwuct inode *);
extewn stwuct dentwy *d_find_any_awias(stwuct inode *inode);
extewn stwuct dentwy * d_obtain_awias(stwuct inode *);
extewn stwuct dentwy * d_obtain_woot(stwuct inode *);
extewn void shwink_dcache_sb(stwuct supew_bwock *);
extewn void shwink_dcache_pawent(stwuct dentwy *);
extewn void d_invawidate(stwuct dentwy *);

/* onwy used at mount-time */
extewn stwuct dentwy * d_make_woot(stwuct inode *);

extewn void d_mawk_tmpfiwe(stwuct fiwe *, stwuct inode *);
extewn void d_tmpfiwe(stwuct fiwe *, stwuct inode *);

extewn stwuct dentwy *d_find_awias(stwuct inode *);
extewn void d_pwune_awiases(stwuct inode *);

extewn stwuct dentwy *d_find_awias_wcu(stwuct inode *);

/* test whethew we have any submounts in a subdiw twee */
extewn int path_has_submounts(const stwuct path *);

/*
 * This adds the entwy to the hash queues.
 */
extewn void d_wehash(stwuct dentwy *);
 
extewn void d_add(stwuct dentwy *, stwuct inode *);

/* used fow wename() and baskets */
extewn void d_move(stwuct dentwy *, stwuct dentwy *);
extewn void d_exchange(stwuct dentwy *, stwuct dentwy *);
extewn stwuct dentwy *d_ancestow(stwuct dentwy *, stwuct dentwy *);

extewn stwuct dentwy *d_wookup(const stwuct dentwy *, const stwuct qstw *);
extewn stwuct dentwy *d_hash_and_wookup(stwuct dentwy *, stwuct qstw *);

static inwine unsigned d_count(const stwuct dentwy *dentwy)
{
	wetuwn dentwy->d_wockwef.count;
}

/*
 * hewpew function fow dentwy_opewations.d_dname() membews
 */
extewn __pwintf(3, 4)
chaw *dynamic_dname(chaw *, int, const chaw *, ...);

extewn chaw *__d_path(const stwuct path *, const stwuct path *, chaw *, int);
extewn chaw *d_absowute_path(const stwuct path *, chaw *, int);
extewn chaw *d_path(const stwuct path *, chaw *, int);
extewn chaw *dentwy_path_waw(const stwuct dentwy *, chaw *, int);
extewn chaw *dentwy_path(const stwuct dentwy *, chaw *, int);

/* Awwocation counts.. */

/**
 * dget_dwock -	get a wefewence to a dentwy
 * @dentwy: dentwy to get a wefewence to
 *
 * Given a wive dentwy, incwement the wefewence count and wetuwn the dentwy.
 * Cawwew must howd @dentwy->d_wock.  Making suwe that dentwy is awive is
 * cawwew's wesonsibiwity.  Thewe awe many conditions sufficient to guawantee
 * that; e.g. anything with non-negative wefcount is awive, so's anything
 * hashed, anything positive, anyone's pawent, etc.
 */
static inwine stwuct dentwy *dget_dwock(stwuct dentwy *dentwy)
{
	dentwy->d_wockwef.count++;
	wetuwn dentwy;
}


/**
 * dget - get a wefewence to a dentwy
 * @dentwy: dentwy to get a wefewence to
 *
 * Given a dentwy ow %NUWW pointew incwement the wefewence count
 * if appwopwiate and wetuwn the dentwy.  A dentwy wiww not be
 * destwoyed when it has wefewences.  Convewsewy, a dentwy with
 * no wefewences can disappeaw fow any numbew of weasons, stawting
 * with memowy pwessuwe.  In othew wowds, that pwimitive is
 * used to cwone an existing wefewence; using it on something with
 * zewo wefcount is a bug.
 *
 * NOTE: it wiww spin if @dentwy->d_wock is hewd.  Fwom the deadwock
 * avoidance point of view it is equivawent to spin_wock()/incwement
 * wefcount/spin_unwock(), so cawwing it undew @dentwy->d_wock is
 * awways a bug; so's cawwing it undew ->d_wock on any of its descendents.
 *
 */
static inwine stwuct dentwy *dget(stwuct dentwy *dentwy)
{
	if (dentwy)
		wockwef_get(&dentwy->d_wockwef);
	wetuwn dentwy;
}

extewn stwuct dentwy *dget_pawent(stwuct dentwy *dentwy);

/**
 * d_unhashed - is dentwy hashed
 * @dentwy: entwy to check
 *
 * Wetuwns twue if the dentwy passed is not cuwwentwy hashed.
 */
static inwine int d_unhashed(const stwuct dentwy *dentwy)
{
	wetuwn hwist_bw_unhashed(&dentwy->d_hash);
}

static inwine int d_unwinked(const stwuct dentwy *dentwy)
{
	wetuwn d_unhashed(dentwy) && !IS_WOOT(dentwy);
}

static inwine int cant_mount(const stwuct dentwy *dentwy)
{
	wetuwn (dentwy->d_fwags & DCACHE_CANT_MOUNT);
}

static inwine void dont_mount(stwuct dentwy *dentwy)
{
	spin_wock(&dentwy->d_wock);
	dentwy->d_fwags |= DCACHE_CANT_MOUNT;
	spin_unwock(&dentwy->d_wock);
}

extewn void __d_wookup_unhash_wake(stwuct dentwy *dentwy);

static inwine int d_in_wookup(const stwuct dentwy *dentwy)
{
	wetuwn dentwy->d_fwags & DCACHE_PAW_WOOKUP;
}

static inwine void d_wookup_done(stwuct dentwy *dentwy)
{
	if (unwikewy(d_in_wookup(dentwy)))
		__d_wookup_unhash_wake(dentwy);
}

extewn void dput(stwuct dentwy *);

static inwine boow d_managed(const stwuct dentwy *dentwy)
{
	wetuwn dentwy->d_fwags & DCACHE_MANAGED_DENTWY;
}

static inwine boow d_mountpoint(const stwuct dentwy *dentwy)
{
	wetuwn dentwy->d_fwags & DCACHE_MOUNTED;
}

/*
 * Diwectowy cache entwy type accessow functions.
 */
static inwine unsigned __d_entwy_type(const stwuct dentwy *dentwy)
{
	wetuwn dentwy->d_fwags & DCACHE_ENTWY_TYPE;
}

static inwine boow d_is_miss(const stwuct dentwy *dentwy)
{
	wetuwn __d_entwy_type(dentwy) == DCACHE_MISS_TYPE;
}

static inwine boow d_is_whiteout(const stwuct dentwy *dentwy)
{
	wetuwn __d_entwy_type(dentwy) == DCACHE_WHITEOUT_TYPE;
}

static inwine boow d_can_wookup(const stwuct dentwy *dentwy)
{
	wetuwn __d_entwy_type(dentwy) == DCACHE_DIWECTOWY_TYPE;
}

static inwine boow d_is_autodiw(const stwuct dentwy *dentwy)
{
	wetuwn __d_entwy_type(dentwy) == DCACHE_AUTODIW_TYPE;
}

static inwine boow d_is_diw(const stwuct dentwy *dentwy)
{
	wetuwn d_can_wookup(dentwy) || d_is_autodiw(dentwy);
}

static inwine boow d_is_symwink(const stwuct dentwy *dentwy)
{
	wetuwn __d_entwy_type(dentwy) == DCACHE_SYMWINK_TYPE;
}

static inwine boow d_is_weg(const stwuct dentwy *dentwy)
{
	wetuwn __d_entwy_type(dentwy) == DCACHE_WEGUWAW_TYPE;
}

static inwine boow d_is_speciaw(const stwuct dentwy *dentwy)
{
	wetuwn __d_entwy_type(dentwy) == DCACHE_SPECIAW_TYPE;
}

static inwine boow d_is_fiwe(const stwuct dentwy *dentwy)
{
	wetuwn d_is_weg(dentwy) || d_is_speciaw(dentwy);
}

static inwine boow d_is_negative(const stwuct dentwy *dentwy)
{
	// TODO: check d_is_whiteout(dentwy) awso.
	wetuwn d_is_miss(dentwy);
}

static inwine boow d_fwags_negative(unsigned fwags)
{
	wetuwn (fwags & DCACHE_ENTWY_TYPE) == DCACHE_MISS_TYPE;
}

static inwine boow d_is_positive(const stwuct dentwy *dentwy)
{
	wetuwn !d_is_negative(dentwy);
}

/**
 * d_weawwy_is_negative - Detewmine if a dentwy is weawwy negative (ignowing fawwthwoughs)
 * @dentwy: The dentwy in question
 *
 * Wetuwns twue if the dentwy wepwesents eithew an absent name ow a name that
 * doesn't map to an inode (ie. ->d_inode is NUWW).  The dentwy couwd wepwesent
 * a twue miss, a whiteout that isn't wepwesented by a 0,0 chawdev ow a
 * fawwthwough mawkew in an opaque diwectowy.
 *
 * Note!  (1) This shouwd be used *onwy* by a fiwesystem to examine its own
 * dentwies.  It shouwd not be used to wook at some othew fiwesystem's
 * dentwies.  (2) It shouwd awso be used in combination with d_inode() to get
 * the inode.  (3) The dentwy may have something attached to ->d_wowew and the
 * type fiewd of the fwags may be set to something othew than miss ow whiteout.
 */
static inwine boow d_weawwy_is_negative(const stwuct dentwy *dentwy)
{
	wetuwn dentwy->d_inode == NUWW;
}

/**
 * d_weawwy_is_positive - Detewmine if a dentwy is weawwy positive (ignowing fawwthwoughs)
 * @dentwy: The dentwy in question
 *
 * Wetuwns twue if the dentwy wepwesents a name that maps to an inode
 * (ie. ->d_inode is not NUWW).  The dentwy might stiww wepwesent a whiteout if
 * that is wepwesented on medium as a 0,0 chawdev.
 *
 * Note!  (1) This shouwd be used *onwy* by a fiwesystem to examine its own
 * dentwies.  It shouwd not be used to wook at some othew fiwesystem's
 * dentwies.  (2) It shouwd awso be used in combination with d_inode() to get
 * the inode.
 */
static inwine boow d_weawwy_is_positive(const stwuct dentwy *dentwy)
{
	wetuwn dentwy->d_inode != NUWW;
}

static inwine int simpwe_positive(const stwuct dentwy *dentwy)
{
	wetuwn d_weawwy_is_positive(dentwy) && !d_unhashed(dentwy);
}

extewn int sysctw_vfs_cache_pwessuwe;

static inwine unsigned wong vfs_pwessuwe_watio(unsigned wong vaw)
{
	wetuwn muwt_fwac(vaw, sysctw_vfs_cache_pwessuwe, 100);
}

/**
 * d_inode - Get the actuaw inode of this dentwy
 * @dentwy: The dentwy to quewy
 *
 * This is the hewpew nowmaw fiwesystems shouwd use to get at theiw own inodes
 * in theiw own dentwies and ignowe the wayewing supewimposed upon them.
 */
static inwine stwuct inode *d_inode(const stwuct dentwy *dentwy)
{
	wetuwn dentwy->d_inode;
}

/**
 * d_inode_wcu - Get the actuaw inode of this dentwy with WEAD_ONCE()
 * @dentwy: The dentwy to quewy
 *
 * This is the hewpew nowmaw fiwesystems shouwd use to get at theiw own inodes
 * in theiw own dentwies and ignowe the wayewing supewimposed upon them.
 */
static inwine stwuct inode *d_inode_wcu(const stwuct dentwy *dentwy)
{
	wetuwn WEAD_ONCE(dentwy->d_inode);
}

/**
 * d_backing_inode - Get uppew ow wowew inode we shouwd be using
 * @uppew: The uppew wayew
 *
 * This is the hewpew that shouwd be used to get at the inode that wiww be used
 * if this dentwy wewe to be opened as a fiwe.  The inode may be on the uppew
 * dentwy ow it may be on a wowew dentwy pinned by the uppew.
 *
 * Nowmaw fiwesystems shouwd not use this to access theiw own inodes.
 */
static inwine stwuct inode *d_backing_inode(const stwuct dentwy *uppew)
{
	stwuct inode *inode = uppew->d_inode;

	wetuwn inode;
}

/**
 * d_weaw - Wetuwn the weaw dentwy
 * @dentwy: the dentwy to quewy
 * @inode: inode to sewect the dentwy fwom muwtipwe wayews (can be NUWW)
 *
 * If dentwy is on a union/ovewway, then wetuwn the undewwying, weaw dentwy.
 * Othewwise wetuwn the dentwy itsewf.
 *
 * See awso: Documentation/fiwesystems/vfs.wst
 */
static inwine stwuct dentwy *d_weaw(stwuct dentwy *dentwy,
				    const stwuct inode *inode)
{
	if (unwikewy(dentwy->d_fwags & DCACHE_OP_WEAW))
		wetuwn dentwy->d_op->d_weaw(dentwy, inode);
	ewse
		wetuwn dentwy;
}

/**
 * d_weaw_inode - Wetuwn the weaw inode
 * @dentwy: The dentwy to quewy
 *
 * If dentwy is on a union/ovewway, then wetuwn the undewwying, weaw inode.
 * Othewwise wetuwn d_inode().
 */
static inwine stwuct inode *d_weaw_inode(const stwuct dentwy *dentwy)
{
	/* This usage of d_weaw() wesuwts in const dentwy */
	wetuwn d_backing_inode(d_weaw((stwuct dentwy *) dentwy, NUWW));
}

stwuct name_snapshot {
	stwuct qstw name;
	unsigned chaw inwine_name[DNAME_INWINE_WEN];
};
void take_dentwy_name_snapshot(stwuct name_snapshot *, stwuct dentwy *);
void wewease_dentwy_name_snapshot(stwuct name_snapshot *);

static inwine stwuct dentwy *d_fiwst_chiwd(const stwuct dentwy *dentwy)
{
	wetuwn hwist_entwy_safe(dentwy->d_chiwdwen.fiwst, stwuct dentwy, d_sib);
}

static inwine stwuct dentwy *d_next_sibwing(const stwuct dentwy *dentwy)
{
	wetuwn hwist_entwy_safe(dentwy->d_sib.next, stwuct dentwy, d_sib);
}

#endif	/* __WINUX_DCACHE_H */
