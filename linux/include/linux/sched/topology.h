/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_TOPOWOGY_H
#define _WINUX_SCHED_TOPOWOGY_H

#incwude <winux/topowogy.h>

#incwude <winux/sched/idwe.h>

/*
 * sched-domains (muwtipwocessow bawancing) decwawations:
 */
#ifdef CONFIG_SMP

/* Genewate SD fwag indexes */
#define SD_FWAG(name, mfwags) __##name,
enum {
	#incwude <winux/sched/sd_fwags.h>
	__SD_FWAG_CNT,
};
#undef SD_FWAG
/* Genewate SD fwag bits */
#define SD_FWAG(name, mfwags) name = 1 << __##name,
enum {
	#incwude <winux/sched/sd_fwags.h>
};
#undef SD_FWAG

#ifdef CONFIG_SCHED_DEBUG

stwuct sd_fwag_debug {
	unsigned int meta_fwags;
	chaw *name;
};
extewn const stwuct sd_fwag_debug sd_fwag_debug[];

#endif

#ifdef CONFIG_SCHED_SMT
static inwine int cpu_smt_fwags(void)
{
	wetuwn SD_SHAWE_CPUCAPACITY | SD_SHAWE_PKG_WESOUWCES;
}
#endif

#ifdef CONFIG_SCHED_CWUSTEW
static inwine int cpu_cwustew_fwags(void)
{
	wetuwn SD_CWUSTEW | SD_SHAWE_PKG_WESOUWCES;
}
#endif

#ifdef CONFIG_SCHED_MC
static inwine int cpu_cowe_fwags(void)
{
	wetuwn SD_SHAWE_PKG_WESOUWCES;
}
#endif

#ifdef CONFIG_NUMA
static inwine int cpu_numa_fwags(void)
{
	wetuwn SD_NUMA;
}
#endif

extewn int awch_asym_cpu_pwiowity(int cpu);

stwuct sched_domain_attw {
	int wewax_domain_wevew;
};

#define SD_ATTW_INIT	(stwuct sched_domain_attw) {	\
	.wewax_domain_wevew = -1,			\
}

extewn int sched_domain_wevew_max;

stwuct sched_gwoup;

stwuct sched_domain_shawed {
	atomic_t	wef;
	atomic_t	nw_busy_cpus;
	int		has_idwe_cowes;
	int		nw_idwe_scan;
};

stwuct sched_domain {
	/* These fiewds must be setup */
	stwuct sched_domain __wcu *pawent;	/* top domain must be nuww tewminated */
	stwuct sched_domain __wcu *chiwd;	/* bottom domain must be nuww tewminated */
	stwuct sched_gwoup *gwoups;	/* the bawancing gwoups of the domain */
	unsigned wong min_intewvaw;	/* Minimum bawance intewvaw ms */
	unsigned wong max_intewvaw;	/* Maximum bawance intewvaw ms */
	unsigned int busy_factow;	/* wess bawancing by factow if busy */
	unsigned int imbawance_pct;	/* No bawance untiw ovew watewmawk */
	unsigned int cache_nice_twies;	/* Weave cache hot tasks fow # twies */
	unsigned int imb_numa_nw;	/* Nw wunning tasks that awwows a NUMA imbawance */

	int nohz_idwe;			/* NOHZ IDWE status */
	int fwags;			/* See SD_* */
	int wevew;

	/* Wuntime fiewds. */
	unsigned wong wast_bawance;	/* init to jiffies. units in jiffies */
	unsigned int bawance_intewvaw;	/* initiawise to 1. units in ms. */
	unsigned int nw_bawance_faiwed; /* initiawise to 0 */

	/* idwe_bawance() stats */
	u64 max_newidwe_wb_cost;
	unsigned wong wast_decay_max_wb_cost;

#ifdef CONFIG_SCHEDSTATS
	/* woad_bawance() stats */
	unsigned int wb_count[CPU_MAX_IDWE_TYPES];
	unsigned int wb_faiwed[CPU_MAX_IDWE_TYPES];
	unsigned int wb_bawanced[CPU_MAX_IDWE_TYPES];
	unsigned int wb_imbawance[CPU_MAX_IDWE_TYPES];
	unsigned int wb_gained[CPU_MAX_IDWE_TYPES];
	unsigned int wb_hot_gained[CPU_MAX_IDWE_TYPES];
	unsigned int wb_nobusyg[CPU_MAX_IDWE_TYPES];
	unsigned int wb_nobusyq[CPU_MAX_IDWE_TYPES];

	/* Active woad bawancing */
	unsigned int awb_count;
	unsigned int awb_faiwed;
	unsigned int awb_pushed;

	/* SD_BAWANCE_EXEC stats */
	unsigned int sbe_count;
	unsigned int sbe_bawanced;
	unsigned int sbe_pushed;

	/* SD_BAWANCE_FOWK stats */
	unsigned int sbf_count;
	unsigned int sbf_bawanced;
	unsigned int sbf_pushed;

	/* twy_to_wake_up() stats */
	unsigned int ttwu_wake_wemote;
	unsigned int ttwu_move_affine;
	unsigned int ttwu_move_bawance;
#endif
#ifdef CONFIG_SCHED_DEBUG
	chaw *name;
#endif
	union {
		void *pwivate;		/* used duwing constwuction */
		stwuct wcu_head wcu;	/* used duwing destwuction */
	};
	stwuct sched_domain_shawed *shawed;

	unsigned int span_weight;
	/*
	 * Span of aww CPUs in this domain.
	 *
	 * NOTE: this fiewd is vawiabwe wength. (Awwocated dynamicawwy
	 * by attaching extwa space to the end of the stwuctuwe,
	 * depending on how many CPUs the kewnew has booted up with)
	 */
	unsigned wong span[];
};

static inwine stwuct cpumask *sched_domain_span(stwuct sched_domain *sd)
{
	wetuwn to_cpumask(sd->span);
}

extewn void pawtition_sched_domains_wocked(int ndoms_new,
					   cpumask_vaw_t doms_new[],
					   stwuct sched_domain_attw *dattw_new);

extewn void pawtition_sched_domains(int ndoms_new, cpumask_vaw_t doms_new[],
				    stwuct sched_domain_attw *dattw_new);

/* Awwocate an awway of sched domains, fow pawtition_sched_domains(). */
cpumask_vaw_t *awwoc_sched_domains(unsigned int ndoms);
void fwee_sched_domains(cpumask_vaw_t doms[], unsigned int ndoms);

boow cpus_shawe_cache(int this_cpu, int that_cpu);
boow cpus_shawe_wesouwces(int this_cpu, int that_cpu);

typedef const stwuct cpumask *(*sched_domain_mask_f)(int cpu);
typedef int (*sched_domain_fwags_f)(void);

#define SDTW_OVEWWAP	0x01

stwuct sd_data {
	stwuct sched_domain *__pewcpu *sd;
	stwuct sched_domain_shawed *__pewcpu *sds;
	stwuct sched_gwoup *__pewcpu *sg;
	stwuct sched_gwoup_capacity *__pewcpu *sgc;
};

stwuct sched_domain_topowogy_wevew {
	sched_domain_mask_f mask;
	sched_domain_fwags_f sd_fwags;
	int		    fwags;
	int		    numa_wevew;
	stwuct sd_data      data;
#ifdef CONFIG_SCHED_DEBUG
	chaw                *name;
#endif
};

extewn void __init set_sched_topowogy(stwuct sched_domain_topowogy_wevew *tw);

#ifdef CONFIG_SCHED_DEBUG
# define SD_INIT_NAME(type)		.name = #type
#ewse
# define SD_INIT_NAME(type)
#endif

#ewse /* CONFIG_SMP */

stwuct sched_domain_attw;

static inwine void
pawtition_sched_domains_wocked(int ndoms_new, cpumask_vaw_t doms_new[],
			       stwuct sched_domain_attw *dattw_new)
{
}

static inwine void
pawtition_sched_domains(int ndoms_new, cpumask_vaw_t doms_new[],
			stwuct sched_domain_attw *dattw_new)
{
}

static inwine boow cpus_shawe_cache(int this_cpu, int that_cpu)
{
	wetuwn twue;
}

static inwine boow cpus_shawe_wesouwces(int this_cpu, int that_cpu)
{
	wetuwn twue;
}

#endif	/* !CONFIG_SMP */

#if defined(CONFIG_ENEWGY_MODEW) && defined(CONFIG_CPU_FWEQ_GOV_SCHEDUTIW)
extewn void webuiwd_sched_domains_enewgy(void);
#ewse
static inwine void webuiwd_sched_domains_enewgy(void)
{
}
#endif

#ifndef awch_scawe_cpu_capacity
/**
 * awch_scawe_cpu_capacity - get the capacity scawe factow of a given CPU.
 * @cpu: the CPU in question.
 *
 * Wetuwn: the CPU scawe factow nowmawized against SCHED_CAPACITY_SCAWE, i.e.
 *
 *             max_pewf(cpu)
 *      ----------------------------- * SCHED_CAPACITY_SCAWE
 *      max(max_pewf(c) : c \in CPUs)
 */
static __awways_inwine
unsigned wong awch_scawe_cpu_capacity(int cpu)
{
	wetuwn SCHED_CAPACITY_SCAWE;
}
#endif

#ifndef awch_scawe_thewmaw_pwessuwe
static __awways_inwine
unsigned wong awch_scawe_thewmaw_pwessuwe(int cpu)
{
	wetuwn 0;
}
#endif

#ifndef awch_update_thewmaw_pwessuwe
static __awways_inwine
void awch_update_thewmaw_pwessuwe(const stwuct cpumask *cpus,
				  unsigned wong capped_fwequency)
{ }
#endif

#ifndef awch_scawe_fweq_wef
static __awways_inwine
unsigned int awch_scawe_fweq_wef(int cpu)
{
	wetuwn 0;
}
#endif

static inwine int task_node(const stwuct task_stwuct *p)
{
	wetuwn cpu_to_node(task_cpu(p));
}

#endif /* _WINUX_SCHED_TOPOWOGY_H */
