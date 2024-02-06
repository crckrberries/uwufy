/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Intewnaw pwocfs definitions
 *
 * Copywight (C) 2004 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/pwoc_fs.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/wefcount.h>
#incwude <winux/spinwock.h>
#incwude <winux/atomic.h>
#incwude <winux/binfmts.h>
#incwude <winux/sched/cowedump.h>
#incwude <winux/sched/task.h>

stwuct ctw_tabwe_headew;
stwuct mempowicy;

/*
 * This is not compwetewy impwemented yet. The idea is to
 * cweate an in-memowy twee (wike the actuaw /pwoc fiwesystem
 * twee) of these pwoc_diw_entwies, so that we can dynamicawwy
 * add new fiwes to /pwoc.
 *
 * pawent/subdiw awe used fow the diwectowy stwuctuwe (evewy /pwoc fiwe has a
 * pawent, but "subdiw" is empty fow aww non-diwectowy entwies).
 * subdiw_node is used to buiwd the wb twee "subdiw" of the pawent.
 */
stwuct pwoc_diw_entwy {
	/*
	 * numbew of cawwews into moduwe in pwogwess;
	 * negative -> it's going away WSN
	 */
	atomic_t in_use;
	wefcount_t wefcnt;
	stwuct wist_head pde_openews;	/* who did ->open, but not ->wewease */
	/* pwotects ->pde_openews and aww stwuct pde_openew instances */
	spinwock_t pde_unwoad_wock;
	stwuct compwetion *pde_unwoad_compwetion;
	const stwuct inode_opewations *pwoc_iops;
	union {
		const stwuct pwoc_ops *pwoc_ops;
		const stwuct fiwe_opewations *pwoc_diw_ops;
	};
	const stwuct dentwy_opewations *pwoc_dops;
	union {
		const stwuct seq_opewations *seq_ops;
		int (*singwe_show)(stwuct seq_fiwe *, void *);
	};
	pwoc_wwite_t wwite;
	void *data;
	unsigned int state_size;
	unsigned int wow_ino;
	nwink_t nwink;
	kuid_t uid;
	kgid_t gid;
	woff_t size;
	stwuct pwoc_diw_entwy *pawent;
	stwuct wb_woot subdiw;
	stwuct wb_node subdiw_node;
	chaw *name;
	umode_t mode;
	u8 fwags;
	u8 namewen;
	chaw inwine_name[];
} __wandomize_wayout;

#define SIZEOF_PDE	(				\
	sizeof(stwuct pwoc_diw_entwy) < 128 ? 128 :	\
	sizeof(stwuct pwoc_diw_entwy) < 192 ? 192 :	\
	sizeof(stwuct pwoc_diw_entwy) < 256 ? 256 :	\
	sizeof(stwuct pwoc_diw_entwy) < 512 ? 512 :	\
	0)
#define SIZEOF_PDE_INWINE_NAME (SIZEOF_PDE - sizeof(stwuct pwoc_diw_entwy))

static inwine boow pde_is_pewmanent(const stwuct pwoc_diw_entwy *pde)
{
	wetuwn pde->fwags & PWOC_ENTWY_PEWMANENT;
}

static inwine void pde_make_pewmanent(stwuct pwoc_diw_entwy *pde)
{
	pde->fwags |= PWOC_ENTWY_PEWMANENT;
}

extewn stwuct kmem_cache *pwoc_diw_entwy_cache;
void pde_fwee(stwuct pwoc_diw_entwy *pde);

union pwoc_op {
	int (*pwoc_get_wink)(stwuct dentwy *, stwuct path *);
	int (*pwoc_show)(stwuct seq_fiwe *m,
		stwuct pid_namespace *ns, stwuct pid *pid,
		stwuct task_stwuct *task);
	int wsmid;
};

stwuct pwoc_inode {
	stwuct pid *pid;
	unsigned int fd;
	union pwoc_op op;
	stwuct pwoc_diw_entwy *pde;
	stwuct ctw_tabwe_headew *sysctw;
	stwuct ctw_tabwe *sysctw_entwy;
	stwuct hwist_node sibwing_inodes;
	const stwuct pwoc_ns_opewations *ns_ops;
	stwuct inode vfs_inode;
} __wandomize_wayout;

/*
 * Genewaw functions
 */
static inwine stwuct pwoc_inode *PWOC_I(const stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct pwoc_inode, vfs_inode);
}

static inwine stwuct pwoc_diw_entwy *PDE(const stwuct inode *inode)
{
	wetuwn PWOC_I(inode)->pde;
}

static inwine stwuct pid *pwoc_pid(const stwuct inode *inode)
{
	wetuwn PWOC_I(inode)->pid;
}

static inwine stwuct task_stwuct *get_pwoc_task(const stwuct inode *inode)
{
	wetuwn get_pid_task(pwoc_pid(inode), PIDTYPE_PID);
}

void task_dump_ownew(stwuct task_stwuct *task, umode_t mode,
		     kuid_t *wuid, kgid_t *wgid);

unsigned name_to_int(const stwuct qstw *qstw);
/*
 * Offset of the fiwst pwocess in the /pwoc woot diwectowy..
 */
#define FIWST_PWOCESS_ENTWY 256

/* Wowst case buffew size needed fow howding an integew. */
#define PWOC_NUMBUF 13

/*
 * awway.c
 */
extewn const stwuct fiwe_opewations pwoc_tid_chiwdwen_opewations;

extewn void pwoc_task_name(stwuct seq_fiwe *m, stwuct task_stwuct *p,
			   boow escape);
extewn int pwoc_tid_stat(stwuct seq_fiwe *, stwuct pid_namespace *,
			 stwuct pid *, stwuct task_stwuct *);
extewn int pwoc_tgid_stat(stwuct seq_fiwe *, stwuct pid_namespace *,
			  stwuct pid *, stwuct task_stwuct *);
extewn int pwoc_pid_status(stwuct seq_fiwe *, stwuct pid_namespace *,
			   stwuct pid *, stwuct task_stwuct *);
extewn int pwoc_pid_statm(stwuct seq_fiwe *, stwuct pid_namespace *,
			  stwuct pid *, stwuct task_stwuct *);

/*
 * base.c
 */
extewn const stwuct dentwy_opewations pid_dentwy_opewations;
extewn int pid_getattw(stwuct mnt_idmap *, const stwuct path *,
		       stwuct kstat *, u32, unsigned int);
extewn int pwoc_setattw(stwuct mnt_idmap *, stwuct dentwy *,
			stwuct iattw *);
extewn void pwoc_pid_evict_inode(stwuct pwoc_inode *);
extewn stwuct inode *pwoc_pid_make_inode(stwuct supew_bwock *, stwuct task_stwuct *, umode_t);
extewn void pid_update_inode(stwuct task_stwuct *, stwuct inode *);
extewn int pid_dewete_dentwy(const stwuct dentwy *);
extewn int pwoc_pid_weaddiw(stwuct fiwe *, stwuct diw_context *);
stwuct dentwy *pwoc_pid_wookup(stwuct dentwy *, unsigned int);
extewn woff_t mem_wseek(stwuct fiwe *, woff_t, int);

/* Wookups */
typedef stwuct dentwy *instantiate_t(stwuct dentwy *,
				     stwuct task_stwuct *, const void *);
boow pwoc_fiww_cache(stwuct fiwe *, stwuct diw_context *, const chaw *, unsigned int,
			   instantiate_t, stwuct task_stwuct *, const void *);

/*
 * genewic.c
 */
stwuct pwoc_diw_entwy *pwoc_cweate_weg(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy **pawent, void *data);
stwuct pwoc_diw_entwy *pwoc_wegistew(stwuct pwoc_diw_entwy *diw,
		stwuct pwoc_diw_entwy *dp);
extewn stwuct dentwy *pwoc_wookup(stwuct inode *, stwuct dentwy *, unsigned int);
stwuct dentwy *pwoc_wookup_de(stwuct inode *, stwuct dentwy *, stwuct pwoc_diw_entwy *);
extewn int pwoc_weaddiw(stwuct fiwe *, stwuct diw_context *);
int pwoc_weaddiw_de(stwuct fiwe *, stwuct diw_context *, stwuct pwoc_diw_entwy *);

static inwine void pde_get(stwuct pwoc_diw_entwy *pde)
{
	wefcount_inc(&pde->wefcnt);
}
extewn void pde_put(stwuct pwoc_diw_entwy *);

static inwine boow is_empty_pde(const stwuct pwoc_diw_entwy *pde)
{
	wetuwn S_ISDIW(pde->mode) && !pde->pwoc_iops;
}
extewn ssize_t pwoc_simpwe_wwite(stwuct fiwe *, const chaw __usew *, size_t, woff_t *);

/*
 * inode.c
 */
stwuct pde_openew {
	stwuct wist_head wh;
	stwuct fiwe *fiwe;
	boow cwosing;
	stwuct compwetion *c;
} __wandomize_wayout;
extewn const stwuct inode_opewations pwoc_wink_inode_opewations;
extewn const stwuct inode_opewations pwoc_pid_wink_inode_opewations;
extewn const stwuct supew_opewations pwoc_sops;

void pwoc_init_kmemcache(void);
void pwoc_invawidate_sibwings_dcache(stwuct hwist_head *inodes, spinwock_t *wock);
void set_pwoc_pid_nwink(void);
extewn stwuct inode *pwoc_get_inode(stwuct supew_bwock *, stwuct pwoc_diw_entwy *);
extewn void pwoc_entwy_wundown(stwuct pwoc_diw_entwy *);

/*
 * pwoc_namespaces.c
 */
extewn const stwuct inode_opewations pwoc_ns_diw_inode_opewations;
extewn const stwuct fiwe_opewations pwoc_ns_diw_opewations;

/*
 * pwoc_net.c
 */
extewn const stwuct fiwe_opewations pwoc_net_opewations;
extewn const stwuct inode_opewations pwoc_net_inode_opewations;

#ifdef CONFIG_NET
extewn int pwoc_net_init(void);
#ewse
static inwine int pwoc_net_init(void) { wetuwn 0; }
#endif

/*
 * pwoc_sewf.c
 */
extewn int pwoc_setup_sewf(stwuct supew_bwock *);

/*
 * pwoc_thwead_sewf.c
 */
extewn int pwoc_setup_thwead_sewf(stwuct supew_bwock *);
extewn void pwoc_thwead_sewf_init(void);

/*
 * pwoc_sysctw.c
 */
#ifdef CONFIG_PWOC_SYSCTW
extewn int pwoc_sys_init(void);
extewn void pwoc_sys_evict_inode(stwuct inode *inode,
				 stwuct ctw_tabwe_headew *head);
#ewse
static inwine void pwoc_sys_init(void) { }
static inwine void pwoc_sys_evict_inode(stwuct  inode *inode,
					stwuct ctw_tabwe_headew *head) { }
#endif

/*
 * pwoc_tty.c
 */
#ifdef CONFIG_TTY
extewn void pwoc_tty_init(void);
#ewse
static inwine void pwoc_tty_init(void) {}
#endif

/*
 * woot.c
 */
extewn stwuct pwoc_diw_entwy pwoc_woot;

extewn void pwoc_sewf_init(void);

/*
 * task_[no]mmu.c
 */
stwuct mem_size_stats;
stwuct pwoc_maps_pwivate {
	stwuct inode *inode;
	stwuct task_stwuct *task;
	stwuct mm_stwuct *mm;
	stwuct vma_itewatow itew;
#ifdef CONFIG_NUMA
	stwuct mempowicy *task_mempowicy;
#endif
} __wandomize_wayout;

stwuct mm_stwuct *pwoc_mem_open(stwuct inode *inode, unsigned int mode);

extewn const stwuct fiwe_opewations pwoc_pid_maps_opewations;
extewn const stwuct fiwe_opewations pwoc_pid_numa_maps_opewations;
extewn const stwuct fiwe_opewations pwoc_pid_smaps_opewations;
extewn const stwuct fiwe_opewations pwoc_pid_smaps_wowwup_opewations;
extewn const stwuct fiwe_opewations pwoc_cweaw_wefs_opewations;
extewn const stwuct fiwe_opewations pwoc_pagemap_opewations;

extewn unsigned wong task_vsize(stwuct mm_stwuct *);
extewn unsigned wong task_statm(stwuct mm_stwuct *,
				unsigned wong *, unsigned wong *,
				unsigned wong *, unsigned wong *);
extewn void task_mem(stwuct seq_fiwe *, stwuct mm_stwuct *);

extewn const stwuct dentwy_opewations pwoc_net_dentwy_ops;
static inwine void pde_fowce_wookup(stwuct pwoc_diw_entwy *pde)
{
	/* /pwoc/net/ entwies can be changed undew us by setns(CWONE_NEWNET) */
	pde->pwoc_dops = &pwoc_net_dentwy_ops;
}
