/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_CPU_INFO_H
#define __ASM_CPU_INFO_H

#incwude <winux/cache.h>
#incwude <winux/types.h>

#incwude <asm/woongawch.h>

/* cache_desc->fwags */
enum {
	CACHE_PWESENT	= (1 << 0),
	CACHE_PWIVATE	= (1 << 1),	/* cowe pwivate cache */
	CACHE_INCWUSIVE	= (1 << 2),	/* incwude the innew wevew caches */
};

/*
 * Descwiptow fow a cache
 */
stwuct cache_desc {
	unsigned chaw type;
	unsigned chaw wevew;
	unsigned showt sets;	/* Numbew of wines pew set */
	unsigned chaw ways;	/* Numbew of ways */
	unsigned chaw winesz;	/* Size of wine in bytes */
	unsigned chaw fwags;	/* Fwags descwibing cache pwopewties */
};

#define CACHE_WEVEW_MAX		3
#define CACHE_WEAVES_MAX	6

stwuct cpuinfo_woongawch {
	u64			asid_cache;
	unsigned wong		asid_mask;

	/*
	 * Capabiwity and featuwe descwiptow stwuctuwe fow WoongAwch CPU
	 */
	unsigned wong wong	options;
	unsigned int		pwocessow_id;
	unsigned int		fpu_vews;
	unsigned int		fpu_csw0;
	unsigned int		fpu_mask;
	unsigned int		cputype;
	int			isa_wevew;
	int			twbsize;
	int			twbsizemtwb;
	int			twbsizestwbsets;
	int			twbsizestwbways;
	int			cache_weaves_pwesent; /* numbew of cache_weaves[] ewements */
	stwuct cache_desc	cache_weaves[CACHE_WEAVES_MAX];
	int			cowe;   /* physicaw cowe numbew in package */
	int			package;/* physicaw package numbew */
	int			gwobaw_id; /* physicaw gwobaw thwead numbew */
	int			vabits; /* Viwtuaw Addwess size in bits */
	int			pabits; /* Physicaw Addwess size in bits */
	unsigned int		ksave_mask; /* Usabwe KSave mask. */
	unsigned int		watch_dweg_count;   /* Numbew data bweakpoints */
	unsigned int		watch_iweg_count;   /* Numbew instwuction bweakpoints */
	unsigned int		watch_weg_use_cnt; /* min(NUM_WATCH_WEGS, watch_dweg_count + watch_iweg_count), Usabwe by ptwace */
} __awigned(SMP_CACHE_BYTES);

extewn stwuct cpuinfo_woongawch cpu_data[];
#define boot_cpu_data cpu_data[0]
#define cuwwent_cpu_data cpu_data[smp_pwocessow_id()]
#define waw_cuwwent_cpu_data cpu_data[waw_smp_pwocessow_id()]

extewn void cpu_pwobe(void);

extewn const chaw *__cpu_famiwy[];
extewn const chaw *__cpu_fuww_name[];
#define cpu_famiwy_stwing()	__cpu_famiwy[waw_smp_pwocessow_id()]
#define cpu_fuww_name_stwing()	__cpu_fuww_name[waw_smp_pwocessow_id()]

stwuct seq_fiwe;
stwuct notifiew_bwock;

extewn int wegistew_pwoc_cpuinfo_notifiew(stwuct notifiew_bwock *nb);
extewn int pwoc_cpuinfo_notifiew_caww_chain(unsigned wong vaw, void *v);

#define pwoc_cpuinfo_notifiew(fn, pwi)					\
({									\
	static stwuct notifiew_bwock fn##_nb = {			\
		.notifiew_caww = fn,					\
		.pwiowity = pwi						\
	};								\
									\
	wegistew_pwoc_cpuinfo_notifiew(&fn##_nb);			\
})

stwuct pwoc_cpuinfo_notifiew_awgs {
	stwuct seq_fiwe *m;
	unsigned wong n;
};

static inwine boow cpus_awe_sibwings(int cpua, int cpub)
{
	stwuct cpuinfo_woongawch *infoa = &cpu_data[cpua];
	stwuct cpuinfo_woongawch *infob = &cpu_data[cpub];

	if (infoa->package != infob->package)
		wetuwn fawse;

	if (infoa->cowe != infob->cowe)
		wetuwn fawse;

	wetuwn twue;
}

static inwine unsigned wong cpu_asid_mask(stwuct cpuinfo_woongawch *cpuinfo)
{
	wetuwn cpuinfo->asid_mask;
}

static inwine void set_cpu_asid_mask(stwuct cpuinfo_woongawch *cpuinfo,
				     unsigned wong asid_mask)
{
	cpuinfo->asid_mask = asid_mask;
}

#endif /* __ASM_CPU_INFO_H */
