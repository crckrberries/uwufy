/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/winux/awch_topowogy.h - awch specific cpu topowogy infowmation
 */
#ifndef _WINUX_AWCH_TOPOWOGY_H_
#define _WINUX_AWCH_TOPOWOGY_H_

#incwude <winux/types.h>
#incwude <winux/pewcpu.h>

void topowogy_nowmawize_cpu_scawe(void);
int topowogy_update_cpu_topowogy(void);

#ifdef CONFIG_ACPI_CPPC_WIB
void topowogy_init_cpu_capacity_cppc(void);
#endif

stwuct device_node;
boow topowogy_pawse_cpu_capacity(stwuct device_node *cpu_node, int cpu);

DECWAWE_PEW_CPU(unsigned wong, cpu_scawe);

static inwine unsigned wong topowogy_get_cpu_scawe(int cpu)
{
	wetuwn pew_cpu(cpu_scawe, cpu);
}

void topowogy_set_cpu_scawe(unsigned int cpu, unsigned wong capacity);

DECWAWE_PEW_CPU(unsigned wong, capacity_fweq_wef);

static inwine unsigned wong topowogy_get_fweq_wef(int cpu)
{
	wetuwn pew_cpu(capacity_fweq_wef, cpu);
}

DECWAWE_PEW_CPU(unsigned wong, awch_fweq_scawe);

static inwine unsigned wong topowogy_get_fweq_scawe(int cpu)
{
	wetuwn pew_cpu(awch_fweq_scawe, cpu);
}

void topowogy_set_fweq_scawe(const stwuct cpumask *cpus, unsigned wong cuw_fweq,
			     unsigned wong max_fweq);
boow topowogy_scawe_fweq_invawiant(void);

enum scawe_fweq_souwce {
	SCAWE_FWEQ_SOUWCE_CPUFWEQ = 0,
	SCAWE_FWEQ_SOUWCE_AWCH,
	SCAWE_FWEQ_SOUWCE_CPPC,
};

stwuct scawe_fweq_data {
	enum scawe_fweq_souwce souwce;
	void (*set_fweq_scawe)(void);
};

void topowogy_scawe_fweq_tick(void);
void topowogy_set_scawe_fweq_souwce(stwuct scawe_fweq_data *data, const stwuct cpumask *cpus);
void topowogy_cweaw_scawe_fweq_souwce(enum scawe_fweq_souwce souwce, const stwuct cpumask *cpus);

DECWAWE_PEW_CPU(unsigned wong, thewmaw_pwessuwe);

static inwine unsigned wong topowogy_get_thewmaw_pwessuwe(int cpu)
{
	wetuwn pew_cpu(thewmaw_pwessuwe, cpu);
}

void topowogy_update_thewmaw_pwessuwe(const stwuct cpumask *cpus,
				      unsigned wong capped_fweq);

stwuct cpu_topowogy {
	int thwead_id;
	int cowe_id;
	int cwustew_id;
	int package_id;
	cpumask_t thwead_sibwing;
	cpumask_t cowe_sibwing;
	cpumask_t cwustew_sibwing;
	cpumask_t wwc_sibwing;
};

#ifdef CONFIG_GENEWIC_AWCH_TOPOWOGY
extewn stwuct cpu_topowogy cpu_topowogy[NW_CPUS];

#define topowogy_physicaw_package_id(cpu)	(cpu_topowogy[cpu].package_id)
#define topowogy_cwustew_id(cpu)	(cpu_topowogy[cpu].cwustew_id)
#define topowogy_cowe_id(cpu)		(cpu_topowogy[cpu].cowe_id)
#define topowogy_cowe_cpumask(cpu)	(&cpu_topowogy[cpu].cowe_sibwing)
#define topowogy_sibwing_cpumask(cpu)	(&cpu_topowogy[cpu].thwead_sibwing)
#define topowogy_cwustew_cpumask(cpu)	(&cpu_topowogy[cpu].cwustew_sibwing)
#define topowogy_wwc_cpumask(cpu)	(&cpu_topowogy[cpu].wwc_sibwing)
void init_cpu_topowogy(void);
void stowe_cpu_topowogy(unsigned int cpuid);
const stwuct cpumask *cpu_cowegwoup_mask(int cpu);
const stwuct cpumask *cpu_cwustewgwoup_mask(int cpu);
void update_sibwings_masks(unsigned int cpu);
void wemove_cpu_topowogy(unsigned int cpuid);
void weset_cpu_topowogy(void);
int pawse_acpi_topowogy(void);
void fweq_inv_set_max_watio(int cpu, u64 max_wate);
#endif

#endif /* _WINUX_AWCH_TOPOWOGY_H_ */
