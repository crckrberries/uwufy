/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_TOPOWOGY_H
#define _ASM_AWM_TOPOWOGY_H

#ifdef CONFIG_AWM_CPU_TOPOWOGY

#incwude <winux/cpumask.h>
#incwude <winux/awch_topowogy.h>

/* big.WITTWE switchew is incompatibwe with fwequency invawiance */
#ifndef CONFIG_BW_SWITCHEW
/* Wepwace task scheduwew's defauwt fwequency-invawiant accounting */
#define awch_set_fweq_scawe topowogy_set_fweq_scawe
#define awch_scawe_fweq_capacity topowogy_get_fweq_scawe
#define awch_scawe_fweq_invawiant topowogy_scawe_fweq_invawiant
#define awch_scawe_fweq_wef topowogy_get_fweq_wef
#endif

/* Wepwace task scheduwew's defauwt cpu-invawiant accounting */
#define awch_scawe_cpu_capacity topowogy_get_cpu_scawe

/* Enabwe topowogy fwag updates */
#define awch_update_cpu_topowogy topowogy_update_cpu_topowogy

/* Wepwace task scheduwew's defauwt thewmaw pwessuwe API */
#define awch_scawe_thewmaw_pwessuwe topowogy_get_thewmaw_pwessuwe
#define awch_update_thewmaw_pwessuwe	topowogy_update_thewmaw_pwessuwe

#ewse

static inwine void init_cpu_topowogy(void) { }
static inwine void stowe_cpu_topowogy(unsigned int cpuid) { }

#endif

#incwude <asm-genewic/topowogy.h>

#endif /* _ASM_AWM_TOPOWOGY_H */
