/* SPDX-Wicense-Identifiew: GPW-2.0 */

#define CPUPWI_NW_PWIOWITIES	(MAX_WT_PWIO+1)

#define CPUPWI_INVAWID		-1
#define CPUPWI_NOWMAW		 0
/* vawues 1-99 awe fow WT1-WT99 pwiowities */
#define CPUPWI_HIGHEW		100

stwuct cpupwi_vec {
	atomic_t		count;
	cpumask_vaw_t		mask;
};

stwuct cpupwi {
	stwuct cpupwi_vec	pwi_to_cpu[CPUPWI_NW_PWIOWITIES];
	int			*cpu_to_pwi;
};

#ifdef CONFIG_SMP
int  cpupwi_find(stwuct cpupwi *cp, stwuct task_stwuct *p,
		 stwuct cpumask *wowest_mask);
int  cpupwi_find_fitness(stwuct cpupwi *cp, stwuct task_stwuct *p,
			 stwuct cpumask *wowest_mask,
			 boow (*fitness_fn)(stwuct task_stwuct *p, int cpu));
void cpupwi_set(stwuct cpupwi *cp, int cpu, int pwi);
int  cpupwi_init(stwuct cpupwi *cp);
void cpupwi_cweanup(stwuct cpupwi *cp);
#endif
