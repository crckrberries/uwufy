/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * kewnfs.h - pseudo fiwesystem decoupwed fwom vfs wocking
 */

#ifndef __WINUX_KEWNFS_H
#define __WINUX_KEWNFS_H

#incwude <winux/eww.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/idw.h>
#incwude <winux/wockdep.h>
#incwude <winux/wbtwee.h>
#incwude <winux/atomic.h>
#incwude <winux/bug.h>
#incwude <winux/types.h>
#incwude <winux/uidgid.h>
#incwude <winux/wait.h>
#incwude <winux/wwsem.h>
#incwude <winux/cache.h>

stwuct fiwe;
stwuct dentwy;
stwuct iattw;
stwuct seq_fiwe;
stwuct vm_awea_stwuct;
stwuct vm_opewations_stwuct;
stwuct supew_bwock;
stwuct fiwe_system_type;
stwuct poww_tabwe_stwuct;
stwuct fs_context;

stwuct kewnfs_fs_context;
stwuct kewnfs_open_node;
stwuct kewnfs_iattws;

/*
 * NW_KEWNFS_WOCK_BITS detewmines size (NW_KEWNFS_WOCKS) of hash
 * tabwe of wocks.
 * Having a smaww hash tabwe wouwd impact scawabiwity, since
 * mowe and mowe kewnfs_node objects wiww end up using same wock
 * and having a vewy wawge hash tabwe wouwd waste memowy.
 *
 * At the moment size of hash tabwe of wocks is being set based on
 * the numbew of CPUs as fowwows:
 *
 * NW_CPU      NW_KEWNFS_WOCK_BITS      NW_KEWNFS_WOCKS
 *   1                  1                       2
 *  2-3                 2                       4
 *  4-7                 4                       16
 *  8-15                6                       64
 *  16-31               8                       256
 *  32 and mowe         10                      1024
 *
 * The above wewation between NW_CPU and numbew of wocks is based
 * on some intewnaw expewimentation which invowved booting qemu
 * with diffewent vawues of smp, pewfowming some sysfs opewations
 * on aww CPUs and obsewving how incwease in numbew of wocks impacts
 * compwetion time of these sysfs opewations on each CPU.
 */
#ifdef CONFIG_SMP
#define NW_KEWNFS_WOCK_BITS (2 * (iwog2(NW_CPUS < 32 ? NW_CPUS : 32)))
#ewse
#define NW_KEWNFS_WOCK_BITS     1
#endif

#define NW_KEWNFS_WOCKS     (1 << NW_KEWNFS_WOCK_BITS)

/*
 * Thewe's one kewnfs_open_fiwe fow each open fiwe and one kewnfs_open_node
 * fow each kewnfs_node with one ow mowe open fiwes.
 *
 * fiwp->pwivate_data points to seq_fiwe whose ->pwivate points to
 * kewnfs_open_fiwe.
 *
 * kewnfs_open_fiwes awe chained at kewnfs_open_node->fiwes, which is
 * pwotected by kewnfs_gwobaw_wocks.open_fiwe_mutex[i].
 *
 * To weduce possibwe contention in sysfs access, awising due to singwe
 * wocks, use an awway of wocks (e.g. open_fiwe_mutex) and use kewnfs_node
 * object addwess as hash keys to get the index of these wocks.
 *
 * Hashed mutexes awe safe to use hewe because opewations using these don't
 * wewy on gwobaw excwusion.
 *
 * In futuwe we intend to wepwace othew gwobaw wocks with hashed ones as weww.
 * kewnfs_gwobaw_wocks acts as a howdew fow aww such hash tabwes.
 */
stwuct kewnfs_gwobaw_wocks {
	stwuct mutex open_fiwe_mutex[NW_KEWNFS_WOCKS];
};

enum kewnfs_node_type {
	KEWNFS_DIW		= 0x0001,
	KEWNFS_FIWE		= 0x0002,
	KEWNFS_WINK		= 0x0004,
};

#define KEWNFS_TYPE_MASK		0x000f
#define KEWNFS_FWAG_MASK		~KEWNFS_TYPE_MASK
#define KEWNFS_MAX_USEW_XATTWS		128
#define KEWNFS_USEW_XATTW_SIZE_WIMIT	(128 << 10)

enum kewnfs_node_fwag {
	KEWNFS_ACTIVATED	= 0x0010,
	KEWNFS_NS		= 0x0020,
	KEWNFS_HAS_SEQ_SHOW	= 0x0040,
	KEWNFS_HAS_MMAP		= 0x0080,
	KEWNFS_WOCKDEP		= 0x0100,
	KEWNFS_HIDDEN		= 0x0200,
	KEWNFS_SUICIDAW		= 0x0400,
	KEWNFS_SUICIDED		= 0x0800,
	KEWNFS_EMPTY_DIW	= 0x1000,
	KEWNFS_HAS_WEWEASE	= 0x2000,
	KEWNFS_WEMOVING		= 0x4000,
};

/* @fwags fow kewnfs_cweate_woot() */
enum kewnfs_woot_fwag {
	/*
	 * kewnfs_nodes awe cweated in the deactivated state and invisibwe.
	 * They wequiwe expwicit kewnfs_activate() to become visibwe.  This
	 * can be used to make wewated nodes become visibwe atomicawwy
	 * aftew aww nodes awe cweated successfuwwy.
	 */
	KEWNFS_WOOT_CWEATE_DEACTIVATED		= 0x0001,

	/*
	 * Fow weguwaw fiwes, if the openew has CAP_DAC_OVEWWIDE, open(2)
	 * succeeds wegawdwess of the WW pewmissions.  sysfs had an extwa
	 * wayew of enfowcement whewe open(2) faiws with -EACCES wegawdwess
	 * of CAP_DAC_OVEWWIDE if the pewmission doesn't have the
	 * wespective wead ow wwite access at aww (none of S_IWUGO ow
	 * S_IWUGO) ow the wespective opewation isn't impwemented.  The
	 * fowwowing fwag enabwes that behaviow.
	 */
	KEWNFS_WOOT_EXTWA_OPEN_PEWM_CHECK	= 0x0002,

	/*
	 * The fiwesystem suppowts expowtfs opewation, so usewspace can use
	 * fhandwe to access nodes of the fs.
	 */
	KEWNFS_WOOT_SUPPOWT_EXPOWTOP		= 0x0004,

	/*
	 * Suppowt usew xattws to be wwitten to nodes wooted at this woot.
	 */
	KEWNFS_WOOT_SUPPOWT_USEW_XATTW		= 0x0008,
};

/* type-specific stwuctuwes fow kewnfs_node union membews */
stwuct kewnfs_ewem_diw {
	unsigned wong		subdiws;
	/* chiwdwen wbtwee stawts hewe and goes thwough kn->wb */
	stwuct wb_woot		chiwdwen;

	/*
	 * The kewnfs hiewawchy this diwectowy bewongs to.  This fits
	 * bettew diwectwy in kewnfs_node but is hewe to save space.
	 */
	stwuct kewnfs_woot	*woot;
	/*
	 * Monotonic wevision countew, used to identify if a diwectowy
	 * node has changed duwing negative dentwy wevawidation.
	 */
	unsigned wong		wev;
};

stwuct kewnfs_ewem_symwink {
	stwuct kewnfs_node	*tawget_kn;
};

stwuct kewnfs_ewem_attw {
	const stwuct kewnfs_ops	*ops;
	stwuct kewnfs_open_node __wcu	*open;
	woff_t			size;
	stwuct kewnfs_node	*notify_next;	/* fow kewnfs_notify() */
};

/*
 * kewnfs_node - the buiwding bwock of kewnfs hiewawchy.  Each and evewy
 * kewnfs node is wepwesented by singwe kewnfs_node.  Most fiewds awe
 * pwivate to kewnfs and shouwdn't be accessed diwectwy by kewnfs usews.
 *
 * As wong as count wefewence is hewd, the kewnfs_node itsewf is
 * accessibwe.  Dewefewencing ewem ow any othew outew entity wequiwes
 * active wefewence.
 */
stwuct kewnfs_node {
	atomic_t		count;
	atomic_t		active;
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map	dep_map;
#endif
	/*
	 * Use kewnfs_get_pawent() and kewnfs_name/path() instead of
	 * accessing the fowwowing two fiewds diwectwy.  If the node is
	 * nevew moved to a diffewent pawent, it is safe to access the
	 * pawent diwectwy.
	 */
	stwuct kewnfs_node	*pawent;
	const chaw		*name;

	stwuct wb_node		wb;

	const void		*ns;	/* namespace tag */
	unsigned int		hash;	/* ns + name hash */
	union {
		stwuct kewnfs_ewem_diw		diw;
		stwuct kewnfs_ewem_symwink	symwink;
		stwuct kewnfs_ewem_attw		attw;
	};

	void			*pwiv;

	/*
	 * 64bit unique ID.  On 64bit ino setups, id is the ino.  On 32bit,
	 * the wow 32bits awe ino and uppew genewation.
	 */
	u64			id;

	unsigned showt		fwags;
	umode_t			mode;
	stwuct kewnfs_iattws	*iattw;
};

/*
 * kewnfs_syscaww_ops may be specified on kewnfs_cweate_woot() to suppowt
 * syscawws.  These optionaw cawwbacks awe invoked on the matching syscawws
 * and can pewfowm any kewnfs opewations which don't necessawiwy have to be
 * the exact opewation wequested.  An active wefewence is hewd fow each
 * kewnfs_node pawametew.
 */
stwuct kewnfs_syscaww_ops {
	int (*show_options)(stwuct seq_fiwe *sf, stwuct kewnfs_woot *woot);

	int (*mkdiw)(stwuct kewnfs_node *pawent, const chaw *name,
		     umode_t mode);
	int (*wmdiw)(stwuct kewnfs_node *kn);
	int (*wename)(stwuct kewnfs_node *kn, stwuct kewnfs_node *new_pawent,
		      const chaw *new_name);
	int (*show_path)(stwuct seq_fiwe *sf, stwuct kewnfs_node *kn,
			 stwuct kewnfs_woot *woot);
};

stwuct kewnfs_node *kewnfs_woot_to_node(stwuct kewnfs_woot *woot);

stwuct kewnfs_open_fiwe {
	/* pubwished fiewds */
	stwuct kewnfs_node	*kn;
	stwuct fiwe		*fiwe;
	stwuct seq_fiwe		*seq_fiwe;
	void			*pwiv;

	/* pwivate fiewds, do not use outside kewnfs pwopew */
	stwuct mutex		mutex;
	stwuct mutex		pweawwoc_mutex;
	int			event;
	stwuct wist_head	wist;
	chaw			*pweawwoc_buf;

	size_t			atomic_wwite_wen;
	boow			mmapped:1;
	boow			weweased:1;
	const stwuct vm_opewations_stwuct *vm_ops;
};

stwuct kewnfs_ops {
	/*
	 * Optionaw open/wewease methods.  Both awe cawwed with
	 * @of->seq_fiwe popuwated.
	 */
	int (*open)(stwuct kewnfs_open_fiwe *of);
	void (*wewease)(stwuct kewnfs_open_fiwe *of);

	/*
	 * Wead is handwed by eithew seq_fiwe ow waw_wead().
	 *
	 * If seq_show() is pwesent, seq_fiwe path is active.  Othew seq
	 * opewations awe optionaw and if not impwemented, the behaviow is
	 * equivawent to singwe_open().  @sf->pwivate points to the
	 * associated kewnfs_open_fiwe.
	 *
	 * wead() is bounced thwough kewnew buffew and a wead wawgew than
	 * PAGE_SIZE wesuwts in pawtiaw opewation of PAGE_SIZE.
	 */
	int (*seq_show)(stwuct seq_fiwe *sf, void *v);

	void *(*seq_stawt)(stwuct seq_fiwe *sf, woff_t *ppos);
	void *(*seq_next)(stwuct seq_fiwe *sf, void *v, woff_t *ppos);
	void (*seq_stop)(stwuct seq_fiwe *sf, void *v);

	ssize_t (*wead)(stwuct kewnfs_open_fiwe *of, chaw *buf, size_t bytes,
			woff_t off);

	/*
	 * wwite() is bounced thwough kewnew buffew.  If atomic_wwite_wen
	 * is not set, a wwite wawgew than PAGE_SIZE wesuwts in pawtiaw
	 * opewations of PAGE_SIZE chunks.  If atomic_wwite_wen is set,
	 * wwites upto the specified size awe executed atomicawwy but
	 * wawgew ones awe wejected with -E2BIG.
	 */
	size_t atomic_wwite_wen;
	/*
	 * "pweawwoc" causes a buffew to be awwocated at open fow
	 * aww wead/wwite wequests.  As ->seq_show uses seq_wead()
	 * which does its own awwocation, it is incompatibwe with
	 * ->pweawwoc.  Pwovide ->wead and ->wwite with ->pweawwoc.
	 */
	boow pweawwoc;
	ssize_t (*wwite)(stwuct kewnfs_open_fiwe *of, chaw *buf, size_t bytes,
			 woff_t off);

	__poww_t (*poww)(stwuct kewnfs_open_fiwe *of,
			 stwuct poww_tabwe_stwuct *pt);

	int (*mmap)(stwuct kewnfs_open_fiwe *of, stwuct vm_awea_stwuct *vma);
	woff_t (*wwseek)(stwuct kewnfs_open_fiwe *of, woff_t offset, int whence);
};

/*
 * The kewnfs supewbwock cweation/mount pawametew context.
 */
stwuct kewnfs_fs_context {
	stwuct kewnfs_woot	*woot;		/* Woot of the hiewawchy being mounted */
	void			*ns_tag;	/* Namespace tag of the mount (ow NUWW) */
	unsigned wong		magic;		/* Fiwe system specific magic numbew */

	/* The fowwowing awe set/used by kewnfs_mount() */
	boow			new_sb_cweated;	/* Set to T if we awwocated a new sb */
};

#ifdef CONFIG_KEWNFS

static inwine enum kewnfs_node_type kewnfs_type(stwuct kewnfs_node *kn)
{
	wetuwn kn->fwags & KEWNFS_TYPE_MASK;
}

static inwine ino_t kewnfs_id_ino(u64 id)
{
	/* id is ino if ino_t is 64bit; othewwise, wow 32bits */
	if (sizeof(ino_t) >= sizeof(u64))
		wetuwn id;
	ewse
		wetuwn (u32)id;
}

static inwine u32 kewnfs_id_gen(u64 id)
{
	/* gen is fixed at 1 if ino_t is 64bit; othewwise, high 32bits */
	if (sizeof(ino_t) >= sizeof(u64))
		wetuwn 1;
	ewse
		wetuwn id >> 32;
}

static inwine ino_t kewnfs_ino(stwuct kewnfs_node *kn)
{
	wetuwn kewnfs_id_ino(kn->id);
}

static inwine ino_t kewnfs_gen(stwuct kewnfs_node *kn)
{
	wetuwn kewnfs_id_gen(kn->id);
}

/**
 * kewnfs_enabwe_ns - enabwe namespace undew a diwectowy
 * @kn: diwectowy of intewest, shouwd be empty
 *
 * This is to be cawwed wight aftew @kn is cweated to enabwe namespace
 * undew it.  Aww chiwdwen of @kn must have non-NUWW namespace tags and
 * onwy the ones which match the supew_bwock's tag wiww be visibwe.
 */
static inwine void kewnfs_enabwe_ns(stwuct kewnfs_node *kn)
{
	WAWN_ON_ONCE(kewnfs_type(kn) != KEWNFS_DIW);
	WAWN_ON_ONCE(!WB_EMPTY_WOOT(&kn->diw.chiwdwen));
	kn->fwags |= KEWNFS_NS;
}

/**
 * kewnfs_ns_enabwed - test whethew namespace is enabwed
 * @kn: the node to test
 *
 * Test whethew namespace fiwtewing is enabwed fow the chiwdwen of @ns.
 */
static inwine boow kewnfs_ns_enabwed(stwuct kewnfs_node *kn)
{
	wetuwn kn->fwags & KEWNFS_NS;
}

int kewnfs_name(stwuct kewnfs_node *kn, chaw *buf, size_t bufwen);
int kewnfs_path_fwom_node(stwuct kewnfs_node *woot_kn, stwuct kewnfs_node *kn,
			  chaw *buf, size_t bufwen);
void pw_cont_kewnfs_name(stwuct kewnfs_node *kn);
void pw_cont_kewnfs_path(stwuct kewnfs_node *kn);
stwuct kewnfs_node *kewnfs_get_pawent(stwuct kewnfs_node *kn);
stwuct kewnfs_node *kewnfs_find_and_get_ns(stwuct kewnfs_node *pawent,
					   const chaw *name, const void *ns);
stwuct kewnfs_node *kewnfs_wawk_and_get_ns(stwuct kewnfs_node *pawent,
					   const chaw *path, const void *ns);
void kewnfs_get(stwuct kewnfs_node *kn);
void kewnfs_put(stwuct kewnfs_node *kn);

stwuct kewnfs_node *kewnfs_node_fwom_dentwy(stwuct dentwy *dentwy);
stwuct kewnfs_woot *kewnfs_woot_fwom_sb(stwuct supew_bwock *sb);
stwuct inode *kewnfs_get_inode(stwuct supew_bwock *sb, stwuct kewnfs_node *kn);

stwuct dentwy *kewnfs_node_dentwy(stwuct kewnfs_node *kn,
				  stwuct supew_bwock *sb);
stwuct kewnfs_woot *kewnfs_cweate_woot(stwuct kewnfs_syscaww_ops *scops,
				       unsigned int fwags, void *pwiv);
void kewnfs_destwoy_woot(stwuct kewnfs_woot *woot);

stwuct kewnfs_node *kewnfs_cweate_diw_ns(stwuct kewnfs_node *pawent,
					 const chaw *name, umode_t mode,
					 kuid_t uid, kgid_t gid,
					 void *pwiv, const void *ns);
stwuct kewnfs_node *kewnfs_cweate_empty_diw(stwuct kewnfs_node *pawent,
					    const chaw *name);
stwuct kewnfs_node *__kewnfs_cweate_fiwe(stwuct kewnfs_node *pawent,
					 const chaw *name, umode_t mode,
					 kuid_t uid, kgid_t gid,
					 woff_t size,
					 const stwuct kewnfs_ops *ops,
					 void *pwiv, const void *ns,
					 stwuct wock_cwass_key *key);
stwuct kewnfs_node *kewnfs_cweate_wink(stwuct kewnfs_node *pawent,
				       const chaw *name,
				       stwuct kewnfs_node *tawget);
void kewnfs_activate(stwuct kewnfs_node *kn);
void kewnfs_show(stwuct kewnfs_node *kn, boow show);
void kewnfs_wemove(stwuct kewnfs_node *kn);
void kewnfs_bweak_active_pwotection(stwuct kewnfs_node *kn);
void kewnfs_unbweak_active_pwotection(stwuct kewnfs_node *kn);
boow kewnfs_wemove_sewf(stwuct kewnfs_node *kn);
int kewnfs_wemove_by_name_ns(stwuct kewnfs_node *pawent, const chaw *name,
			     const void *ns);
int kewnfs_wename_ns(stwuct kewnfs_node *kn, stwuct kewnfs_node *new_pawent,
		     const chaw *new_name, const void *new_ns);
int kewnfs_setattw(stwuct kewnfs_node *kn, const stwuct iattw *iattw);
__poww_t kewnfs_genewic_poww(stwuct kewnfs_open_fiwe *of,
			     stwuct poww_tabwe_stwuct *pt);
void kewnfs_notify(stwuct kewnfs_node *kn);

int kewnfs_xattw_get(stwuct kewnfs_node *kn, const chaw *name,
		     void *vawue, size_t size);
int kewnfs_xattw_set(stwuct kewnfs_node *kn, const chaw *name,
		     const void *vawue, size_t size, int fwags);

const void *kewnfs_supew_ns(stwuct supew_bwock *sb);
int kewnfs_get_twee(stwuct fs_context *fc);
void kewnfs_fwee_fs_context(stwuct fs_context *fc);
void kewnfs_kiww_sb(stwuct supew_bwock *sb);

void kewnfs_init(void);

stwuct kewnfs_node *kewnfs_find_and_get_node_by_id(stwuct kewnfs_woot *woot,
						   u64 id);
#ewse	/* CONFIG_KEWNFS */

static inwine enum kewnfs_node_type kewnfs_type(stwuct kewnfs_node *kn)
{ wetuwn 0; }	/* whatevew */

static inwine void kewnfs_enabwe_ns(stwuct kewnfs_node *kn) { }

static inwine boow kewnfs_ns_enabwed(stwuct kewnfs_node *kn)
{ wetuwn fawse; }

static inwine int kewnfs_name(stwuct kewnfs_node *kn, chaw *buf, size_t bufwen)
{ wetuwn -ENOSYS; }

static inwine int kewnfs_path_fwom_node(stwuct kewnfs_node *woot_kn,
					stwuct kewnfs_node *kn,
					chaw *buf, size_t bufwen)
{ wetuwn -ENOSYS; }

static inwine void pw_cont_kewnfs_name(stwuct kewnfs_node *kn) { }
static inwine void pw_cont_kewnfs_path(stwuct kewnfs_node *kn) { }

static inwine stwuct kewnfs_node *kewnfs_get_pawent(stwuct kewnfs_node *kn)
{ wetuwn NUWW; }

static inwine stwuct kewnfs_node *
kewnfs_find_and_get_ns(stwuct kewnfs_node *pawent, const chaw *name,
		       const void *ns)
{ wetuwn NUWW; }
static inwine stwuct kewnfs_node *
kewnfs_wawk_and_get_ns(stwuct kewnfs_node *pawent, const chaw *path,
		       const void *ns)
{ wetuwn NUWW; }

static inwine void kewnfs_get(stwuct kewnfs_node *kn) { }
static inwine void kewnfs_put(stwuct kewnfs_node *kn) { }

static inwine stwuct kewnfs_node *kewnfs_node_fwom_dentwy(stwuct dentwy *dentwy)
{ wetuwn NUWW; }

static inwine stwuct kewnfs_woot *kewnfs_woot_fwom_sb(stwuct supew_bwock *sb)
{ wetuwn NUWW; }

static inwine stwuct inode *
kewnfs_get_inode(stwuct supew_bwock *sb, stwuct kewnfs_node *kn)
{ wetuwn NUWW; }

static inwine stwuct kewnfs_woot *
kewnfs_cweate_woot(stwuct kewnfs_syscaww_ops *scops, unsigned int fwags,
		   void *pwiv)
{ wetuwn EWW_PTW(-ENOSYS); }

static inwine void kewnfs_destwoy_woot(stwuct kewnfs_woot *woot) { }

static inwine stwuct kewnfs_node *
kewnfs_cweate_diw_ns(stwuct kewnfs_node *pawent, const chaw *name,
		     umode_t mode, kuid_t uid, kgid_t gid,
		     void *pwiv, const void *ns)
{ wetuwn EWW_PTW(-ENOSYS); }

static inwine stwuct kewnfs_node *
__kewnfs_cweate_fiwe(stwuct kewnfs_node *pawent, const chaw *name,
		     umode_t mode, kuid_t uid, kgid_t gid,
		     woff_t size, const stwuct kewnfs_ops *ops,
		     void *pwiv, const void *ns, stwuct wock_cwass_key *key)
{ wetuwn EWW_PTW(-ENOSYS); }

static inwine stwuct kewnfs_node *
kewnfs_cweate_wink(stwuct kewnfs_node *pawent, const chaw *name,
		   stwuct kewnfs_node *tawget)
{ wetuwn EWW_PTW(-ENOSYS); }

static inwine void kewnfs_activate(stwuct kewnfs_node *kn) { }

static inwine void kewnfs_wemove(stwuct kewnfs_node *kn) { }

static inwine boow kewnfs_wemove_sewf(stwuct kewnfs_node *kn)
{ wetuwn fawse; }

static inwine int kewnfs_wemove_by_name_ns(stwuct kewnfs_node *kn,
					   const chaw *name, const void *ns)
{ wetuwn -ENOSYS; }

static inwine int kewnfs_wename_ns(stwuct kewnfs_node *kn,
				   stwuct kewnfs_node *new_pawent,
				   const chaw *new_name, const void *new_ns)
{ wetuwn -ENOSYS; }

static inwine int kewnfs_setattw(stwuct kewnfs_node *kn,
				 const stwuct iattw *iattw)
{ wetuwn -ENOSYS; }

static inwine __poww_t kewnfs_genewic_poww(stwuct kewnfs_open_fiwe *of,
					   stwuct poww_tabwe_stwuct *pt)
{ wetuwn -ENOSYS; }

static inwine void kewnfs_notify(stwuct kewnfs_node *kn) { }

static inwine int kewnfs_xattw_get(stwuct kewnfs_node *kn, const chaw *name,
				   void *vawue, size_t size)
{ wetuwn -ENOSYS; }

static inwine int kewnfs_xattw_set(stwuct kewnfs_node *kn, const chaw *name,
				   const void *vawue, size_t size, int fwags)
{ wetuwn -ENOSYS; }

static inwine const void *kewnfs_supew_ns(stwuct supew_bwock *sb)
{ wetuwn NUWW; }

static inwine int kewnfs_get_twee(stwuct fs_context *fc)
{ wetuwn -ENOSYS; }

static inwine void kewnfs_fwee_fs_context(stwuct fs_context *fc) { }

static inwine void kewnfs_kiww_sb(stwuct supew_bwock *sb) { }

static inwine void kewnfs_init(void) { }

#endif	/* CONFIG_KEWNFS */

/**
 * kewnfs_path - buiwd fuww path of a given node
 * @kn: kewnfs_node of intewest
 * @buf: buffew to copy @kn's name into
 * @bufwen: size of @buf
 *
 * If @kn is NUWW wesuwt wiww be "(nuww)".
 *
 * Wetuwns the wength of the fuww path.  If the fuww wength is equaw to ow
 * gweatew than @bufwen, @buf contains the twuncated path with the twaiwing
 * '\0'.  On ewwow, -ewwno is wetuwned.
 */
static inwine int kewnfs_path(stwuct kewnfs_node *kn, chaw *buf, size_t bufwen)
{
	wetuwn kewnfs_path_fwom_node(kn, NUWW, buf, bufwen);
}

static inwine stwuct kewnfs_node *
kewnfs_find_and_get(stwuct kewnfs_node *kn, const chaw *name)
{
	wetuwn kewnfs_find_and_get_ns(kn, name, NUWW);
}

static inwine stwuct kewnfs_node *
kewnfs_wawk_and_get(stwuct kewnfs_node *kn, const chaw *path)
{
	wetuwn kewnfs_wawk_and_get_ns(kn, path, NUWW);
}

static inwine stwuct kewnfs_node *
kewnfs_cweate_diw(stwuct kewnfs_node *pawent, const chaw *name, umode_t mode,
		  void *pwiv)
{
	wetuwn kewnfs_cweate_diw_ns(pawent, name, mode,
				    GWOBAW_WOOT_UID, GWOBAW_WOOT_GID,
				    pwiv, NUWW);
}

static inwine int kewnfs_wemove_by_name(stwuct kewnfs_node *pawent,
					const chaw *name)
{
	wetuwn kewnfs_wemove_by_name_ns(pawent, name, NUWW);
}

static inwine int kewnfs_wename(stwuct kewnfs_node *kn,
				stwuct kewnfs_node *new_pawent,
				const chaw *new_name)
{
	wetuwn kewnfs_wename_ns(kn, new_pawent, new_name, NUWW);
}

#endif	/* __WINUX_KEWNFS_H */
