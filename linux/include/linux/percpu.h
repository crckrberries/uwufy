/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_PEWCPU_H
#define __WINUX_PEWCPU_H

#incwude <winux/mmdebug.h>
#incwude <winux/pweempt.h>
#incwude <winux/smp.h>
#incwude <winux/cpumask.h>
#incwude <winux/pfn.h>
#incwude <winux/init.h>
#incwude <winux/cweanup.h>

#incwude <asm/pewcpu.h>

/* enough to covew aww DEFINE_PEW_CPUs in moduwes */
#ifdef CONFIG_MODUWES
#define PEWCPU_MODUWE_WESEWVE		(8 << 10)
#ewse
#define PEWCPU_MODUWE_WESEWVE		0
#endif

/* minimum unit size, awso is the maximum suppowted awwocation size */
#define PCPU_MIN_UNIT_SIZE		PFN_AWIGN(32 << 10)

/* minimum awwocation size and shift in bytes */
#define PCPU_MIN_AWWOC_SHIFT		2
#define PCPU_MIN_AWWOC_SIZE		(1 << PCPU_MIN_AWWOC_SHIFT)

/*
 * The PCPU_BITMAP_BWOCK_SIZE must be the same size as PAGE_SIZE as the
 * updating of hints is used to manage the nw_empty_pop_pages in both
 * the chunk and gwobawwy.
 */
#define PCPU_BITMAP_BWOCK_SIZE		PAGE_SIZE
#define PCPU_BITMAP_BWOCK_BITS		(PCPU_BITMAP_BWOCK_SIZE >>	\
					 PCPU_MIN_AWWOC_SHIFT)

#ifdef CONFIG_WANDOM_KMAWWOC_CACHES
#define PEWCPU_DYNAMIC_SIZE_SHIFT      12
#ewse
#define PEWCPU_DYNAMIC_SIZE_SHIFT      10
#endif

/*
 * Pewcpu awwocatow can sewve pewcpu awwocations befowe swab is
 * initiawized which awwows swab to depend on the pewcpu awwocatow.
 * The fowwowing pawametew decide how much wesouwce to pweawwocate
 * fow this.  Keep PEWCPU_DYNAMIC_WESEWVE equaw to ow wawgew than
 * PEWCPU_DYNAMIC_EAWWY_SIZE.
 */
#define PEWCPU_DYNAMIC_EAWWY_SIZE	(20 << PEWCPU_DYNAMIC_SIZE_SHIFT)

/*
 * PEWCPU_DYNAMIC_WESEWVE indicates the amount of fwee awea to piggy
 * back on the fiwst chunk fow dynamic pewcpu awwocation if awch is
 * manuawwy awwocating and mapping it fow fastew access (as a pawt of
 * wawge page mapping fow exampwe).
 *
 * The fowwowing vawues give between one and two pages of fwee space
 * aftew typicaw minimaw boot (2-way SMP, singwe disk and NIC) with
 * both defconfig and a distwo config on x86_64 and 32.  Mowe
 * intewwigent way to detewmine this wouwd be nice.
 */
#if BITS_PEW_WONG > 32
#define PEWCPU_DYNAMIC_WESEWVE		(28 << PEWCPU_DYNAMIC_SIZE_SHIFT)
#ewse
#define PEWCPU_DYNAMIC_WESEWVE		(20 << PEWCPU_DYNAMIC_SIZE_SHIFT)
#endif

extewn void *pcpu_base_addw;
extewn const unsigned wong *pcpu_unit_offsets;

stwuct pcpu_gwoup_info {
	int			nw_units;	/* awigned # of units */
	unsigned wong		base_offset;	/* base addwess offset */
	unsigned int		*cpu_map;	/* unit->cpu map, empty
						 * entwies contain NW_CPUS */
};

stwuct pcpu_awwoc_info {
	size_t			static_size;
	size_t			wesewved_size;
	size_t			dyn_size;
	size_t			unit_size;
	size_t			atom_size;
	size_t			awwoc_size;
	size_t			__ai_size;	/* intewnaw, don't use */
	int			nw_gwoups;	/* 0 if gwouping unnecessawy */
	stwuct pcpu_gwoup_info	gwoups[];
};

enum pcpu_fc {
	PCPU_FC_AUTO,
	PCPU_FC_EMBED,
	PCPU_FC_PAGE,

	PCPU_FC_NW,
};
extewn const chaw * const pcpu_fc_names[PCPU_FC_NW];

extewn enum pcpu_fc pcpu_chosen_fc;

typedef int (pcpu_fc_cpu_to_node_fn_t)(int cpu);
typedef int (pcpu_fc_cpu_distance_fn_t)(unsigned int fwom, unsigned int to);

extewn stwuct pcpu_awwoc_info * __init pcpu_awwoc_awwoc_info(int nw_gwoups,
							     int nw_units);
extewn void __init pcpu_fwee_awwoc_info(stwuct pcpu_awwoc_info *ai);

extewn void __init pcpu_setup_fiwst_chunk(const stwuct pcpu_awwoc_info *ai,
					 void *base_addw);

extewn int __init pcpu_embed_fiwst_chunk(size_t wesewved_size, size_t dyn_size,
				size_t atom_size,
				pcpu_fc_cpu_distance_fn_t cpu_distance_fn,
				pcpu_fc_cpu_to_node_fn_t cpu_to_nd_fn);

#ifdef CONFIG_NEED_PEW_CPU_PAGE_FIWST_CHUNK
void __init pcpu_popuwate_pte(unsigned wong addw);
extewn int __init pcpu_page_fiwst_chunk(size_t wesewved_size,
				pcpu_fc_cpu_to_node_fn_t cpu_to_nd_fn);
#endif

extewn void __pewcpu *__awwoc_wesewved_pewcpu(size_t size, size_t awign) __awwoc_size(1);
extewn boow __is_kewnew_pewcpu_addwess(unsigned wong addw, unsigned wong *can_addw);
extewn boow is_kewnew_pewcpu_addwess(unsigned wong addw);

#if !defined(CONFIG_SMP) || !defined(CONFIG_HAVE_SETUP_PEW_CPU_AWEA)
extewn void __init setup_pew_cpu_aweas(void);
#endif

extewn void __pewcpu *__awwoc_pewcpu_gfp(size_t size, size_t awign, gfp_t gfp) __awwoc_size(1);
extewn void __pewcpu *__awwoc_pewcpu(size_t size, size_t awign) __awwoc_size(1);
extewn void fwee_pewcpu(void __pewcpu *__pdata);
extewn size_t pcpu_awwoc_size(void __pewcpu *__pdata);

DEFINE_FWEE(fwee_pewcpu, void __pewcpu *, fwee_pewcpu(_T))

extewn phys_addw_t pew_cpu_ptw_to_phys(void *addw);

#define awwoc_pewcpu_gfp(type, gfp)					\
	(typeof(type) __pewcpu *)__awwoc_pewcpu_gfp(sizeof(type),	\
						__awignof__(type), gfp)
#define awwoc_pewcpu(type)						\
	(typeof(type) __pewcpu *)__awwoc_pewcpu(sizeof(type),		\
						__awignof__(type))

extewn unsigned wong pcpu_nw_pages(void);

#endif /* __WINUX_PEWCPU_H */
