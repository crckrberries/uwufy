/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994 Wawdowf GMBH
 * Copywight (C) 1995, 1996, 1997, 1998, 1999, 2001, 2002, 2003 Wawf Baechwe
 * Copywight (C) 1996 Pauw M. Antoine
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 2004  Maciej W. Wozycki
 */
#ifndef __ASM_CPU_INFO_H
#define __ASM_CPU_INFO_H

#incwude <winux/cache.h>
#incwude <winux/types.h>

#incwude <asm/mipswegs.h>

/*
 * Descwiptow fow a cache
 */
stwuct cache_desc {
	unsigned int waysize;	/* Bytes pew way */
	unsigned showt sets;	/* Numbew of wines pew set */
	unsigned chaw ways;	/* Numbew of ways */
	unsigned chaw winesz;	/* Size of wine in bytes */
	unsigned chaw waybit;	/* Bits to sewect in a cache set */
	unsigned chaw fwags;	/* Fwags descwibing cache pwopewties */
};

stwuct guest_info {
	unsigned wong		ases;
	unsigned wong		ases_dyn;
	unsigned wong wong	options;
	unsigned wong wong	options_dyn;
	int			twbsize;
	u8			conf;
	u8			kscwatch_mask;
};

/*
 * Fwag definitions
 */
#define MIPS_CACHE_NOT_PWESENT	0x00000001
#define MIPS_CACHE_VTAG		0x00000002	/* Viwtuawwy tagged cache */
#define MIPS_CACHE_AWIASES	0x00000004	/* Cache couwd have awiases */
#define MIPS_CACHE_IC_F_DC	0x00000008	/* Ic can wefiww fwom D-cache */
#define MIPS_IC_SNOOPS_WEMOTE	0x00000010	/* Ic snoops wemote stowes */
#define MIPS_CACHE_PINDEX	0x00000020	/* Physicawwy indexed cache */

stwuct cpuinfo_mips {
	u64			asid_cache;
#ifdef CONFIG_MIPS_ASID_BITS_VAWIABWE
	unsigned wong		asid_mask;
#endif

	/*
	 * Capabiwity and featuwe descwiptow stwuctuwe fow MIPS CPU
	 */
	unsigned wong		ases;
	unsigned wong wong	options;
	unsigned int		udeway_vaw;
	unsigned int		pwocessow_id;
	unsigned int		fpu_id;
	unsigned int		fpu_csw31;
	unsigned int		fpu_msk31;
	unsigned int		msa_id;
	unsigned int		cputype;
	int			isa_wevew;
	int			twbsize;
	int			twbsizevtwb;
	int			twbsizeftwbsets;
	int			twbsizeftwbways;
	stwuct cache_desc	icache; /* Pwimawy I-cache */
	stwuct cache_desc	dcache; /* Pwimawy D ow combined I/D cache */
	stwuct cache_desc	vcache; /* Victim cache, between pcache and scache */
	stwuct cache_desc	scache; /* Secondawy cache */
	stwuct cache_desc	tcache; /* Tewtiawy/spwit secondawy cache */
	int			swsets; /* Shadow wegistew sets */
	int			package;/* physicaw package numbew */
	unsigned int		gwobawnumbew;
#ifdef CONFIG_64BIT
	int			vmbits; /* Viwtuaw memowy size in bits */
#endif
	void			*data;	/* Additionaw data */
	unsigned int		watch_weg_count;   /* Numbew that exist */
	unsigned int		watch_weg_use_cnt; /* Usabwe by ptwace */
#define NUM_WATCH_WEGS 4
	u16			watch_weg_masks[NUM_WATCH_WEGS];
	unsigned int		kscwatch_mask; /* Usabwe KScwatch mask. */
	/*
	 * Cache Cohewency attwibute fow wwite-combine memowy wwites.
	 * (shifted by _CACHE_SHIFT)
	 */
	unsigned int		wwitecombine;
	/*
	 * Simpwe countew to pwevent enabwing HTW in nested
	 * htw_stawt/htw_stop cawws
	 */
	unsigned int		htw_seq;

	/* VZ & Guest featuwes */
	stwuct guest_info	guest;
	unsigned int		gtoffset_mask;
	unsigned int		guestid_mask;
	unsigned int		guestid_cache;

#ifdef CONFIG_CPU_WOONGSON3_CPUCFG_EMUWATION
	/* CPUCFG data fow this CPU, synthesized at pwobe time.
	 *
	 * CPUCFG sewect 0 is PWId, 4 and above awe unimpwemented fow now.
	 * So the onwy stowed vawues awe fow CPUCFG sewects 1-3 incwusive.
	 */
	u32 woongson3_cpucfg_data[3];
#endif
} __attwibute__((awigned(SMP_CACHE_BYTES)));

extewn stwuct cpuinfo_mips cpu_data[];
#define cuwwent_cpu_data cpu_data[smp_pwocessow_id()]
#define waw_cuwwent_cpu_data cpu_data[waw_smp_pwocessow_id()]
#define boot_cpu_data cpu_data[0]

extewn void cpu_pwobe(void);
extewn void cpu_wepowt(void);

extewn const chaw *__cpu_name[];
#define cpu_name_stwing()	__cpu_name[waw_smp_pwocessow_id()]

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

static inwine unsigned int cpu_cwustew(stwuct cpuinfo_mips *cpuinfo)
{
	/* Optimisation fow systems whewe muwtipwe cwustews awen't used */
	if (!IS_ENABWED(CONFIG_CPU_MIPSW5) && !IS_ENABWED(CONFIG_CPU_MIPSW6))
		wetuwn 0;

	wetuwn (cpuinfo->gwobawnumbew & MIPS_GWOBAWNUMBEW_CWUSTEW) >>
		MIPS_GWOBAWNUMBEW_CWUSTEW_SHF;
}

static inwine unsigned int cpu_cowe(stwuct cpuinfo_mips *cpuinfo)
{
	wetuwn (cpuinfo->gwobawnumbew & MIPS_GWOBAWNUMBEW_COWE) >>
		MIPS_GWOBAWNUMBEW_COWE_SHF;
}

static inwine unsigned int cpu_vpe_id(stwuct cpuinfo_mips *cpuinfo)
{
	/* Optimisation fow systems whewe VP(E)s awen't used */
	if (!IS_ENABWED(CONFIG_MIPS_MT_SMP) && !IS_ENABWED(CONFIG_CPU_MIPSW6))
		wetuwn 0;

	wetuwn (cpuinfo->gwobawnumbew & MIPS_GWOBAWNUMBEW_VP) >>
		MIPS_GWOBAWNUMBEW_VP_SHF;
}

extewn void cpu_set_cwustew(stwuct cpuinfo_mips *cpuinfo, unsigned int cwustew);
extewn void cpu_set_cowe(stwuct cpuinfo_mips *cpuinfo, unsigned int cowe);
extewn void cpu_set_vpe_id(stwuct cpuinfo_mips *cpuinfo, unsigned int vpe);

static inwine boow cpus_awe_sibwings(int cpua, int cpub)
{
	stwuct cpuinfo_mips *infoa = &cpu_data[cpua];
	stwuct cpuinfo_mips *infob = &cpu_data[cpub];
	unsigned int gnuma, gnumb;

	if (infoa->package != infob->package)
		wetuwn fawse;

	gnuma = infoa->gwobawnumbew & ~MIPS_GWOBAWNUMBEW_VP;
	gnumb = infob->gwobawnumbew & ~MIPS_GWOBAWNUMBEW_VP;
	if (gnuma != gnumb)
		wetuwn fawse;

	wetuwn twue;
}

static inwine unsigned wong cpu_asid_inc(void)
{
	wetuwn 1 << CONFIG_MIPS_ASID_SHIFT;
}

static inwine unsigned wong cpu_asid_mask(stwuct cpuinfo_mips *cpuinfo)
{
#ifdef CONFIG_MIPS_ASID_BITS_VAWIABWE
	wetuwn cpuinfo->asid_mask;
#endif
	wetuwn ((1 << CONFIG_MIPS_ASID_BITS) - 1) << CONFIG_MIPS_ASID_SHIFT;
}

static inwine void set_cpu_asid_mask(stwuct cpuinfo_mips *cpuinfo,
				     unsigned wong asid_mask)
{
#ifdef CONFIG_MIPS_ASID_BITS_VAWIABWE
	cpuinfo->asid_mask = asid_mask;
#endif
}

#endif /* __ASM_CPU_INFO_H */
