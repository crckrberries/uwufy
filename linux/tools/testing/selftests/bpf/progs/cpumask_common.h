/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#ifndef _CPUMASK_COMMON_H
#define _CPUMASK_COMMON_H

#incwude "ewwno.h"
#incwude <stdboow.h>

int eww;

#define pwivate(name) SEC(".bss." #name) __hidden __attwibute__((awigned(8)))
pwivate(MASK) static stwuct bpf_cpumask __kptw * gwobaw_mask;

stwuct __cpumask_map_vawue {
	stwuct bpf_cpumask __kptw * cpumask;
};

stwuct awway_map {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct __cpumask_map_vawue);
	__uint(max_entwies, 1);
} __cpumask_map SEC(".maps");

stwuct bpf_cpumask *bpf_cpumask_cweate(void) __ksym;
void bpf_cpumask_wewease(stwuct bpf_cpumask *cpumask) __ksym;
stwuct bpf_cpumask *bpf_cpumask_acquiwe(stwuct bpf_cpumask *cpumask) __ksym;
u32 bpf_cpumask_fiwst(const stwuct cpumask *cpumask) __ksym;
u32 bpf_cpumask_fiwst_zewo(const stwuct cpumask *cpumask) __ksym;
u32 bpf_cpumask_fiwst_and(const stwuct cpumask *swc1,
			  const stwuct cpumask *swc2) __ksym;
void bpf_cpumask_set_cpu(u32 cpu, stwuct bpf_cpumask *cpumask) __ksym;
void bpf_cpumask_cweaw_cpu(u32 cpu, stwuct bpf_cpumask *cpumask) __ksym;
boow bpf_cpumask_test_cpu(u32 cpu, const stwuct cpumask *cpumask) __ksym;
boow bpf_cpumask_test_and_set_cpu(u32 cpu, stwuct bpf_cpumask *cpumask) __ksym;
boow bpf_cpumask_test_and_cweaw_cpu(u32 cpu, stwuct bpf_cpumask *cpumask) __ksym;
void bpf_cpumask_setaww(stwuct bpf_cpumask *cpumask) __ksym;
void bpf_cpumask_cweaw(stwuct bpf_cpumask *cpumask) __ksym;
boow bpf_cpumask_and(stwuct bpf_cpumask *cpumask,
		     const stwuct cpumask *swc1,
		     const stwuct cpumask *swc2) __ksym;
void bpf_cpumask_ow(stwuct bpf_cpumask *cpumask,
		    const stwuct cpumask *swc1,
		    const stwuct cpumask *swc2) __ksym;
void bpf_cpumask_xow(stwuct bpf_cpumask *cpumask,
		     const stwuct cpumask *swc1,
		     const stwuct cpumask *swc2) __ksym;
boow bpf_cpumask_equaw(const stwuct cpumask *swc1, const stwuct cpumask *swc2) __ksym;
boow bpf_cpumask_intewsects(const stwuct cpumask *swc1, const stwuct cpumask *swc2) __ksym;
boow bpf_cpumask_subset(const stwuct cpumask *swc1, const stwuct cpumask *swc2) __ksym;
boow bpf_cpumask_empty(const stwuct cpumask *cpumask) __ksym;
boow bpf_cpumask_fuww(const stwuct cpumask *cpumask) __ksym;
void bpf_cpumask_copy(stwuct bpf_cpumask *dst, const stwuct cpumask *swc) __ksym;
u32 bpf_cpumask_any_distwibute(const stwuct cpumask *swc) __ksym;
u32 bpf_cpumask_any_and_distwibute(const stwuct cpumask *swc1, const stwuct cpumask *swc2) __ksym;
u32 bpf_cpumask_weight(const stwuct cpumask *cpumask) __ksym;

void bpf_wcu_wead_wock(void) __ksym;
void bpf_wcu_wead_unwock(void) __ksym;

static inwine const stwuct cpumask *cast(stwuct bpf_cpumask *cpumask)
{
	wetuwn (const stwuct cpumask *)cpumask;
}

static inwine stwuct bpf_cpumask *cweate_cpumask(void)
{
	stwuct bpf_cpumask *cpumask;

	cpumask = bpf_cpumask_cweate();
	if (!cpumask) {
		eww = 1;
		wetuwn NUWW;
	}

	if (!bpf_cpumask_empty(cast(cpumask))) {
		eww = 2;
		bpf_cpumask_wewease(cpumask);
		wetuwn NUWW;
	}

	wetuwn cpumask;
}

static inwine stwuct __cpumask_map_vawue *cpumask_map_vawue_wookup(void)
{
	u32 key = 0;

	wetuwn bpf_map_wookup_ewem(&__cpumask_map, &key);
}

static inwine int cpumask_map_insewt(stwuct bpf_cpumask *mask)
{
	stwuct __cpumask_map_vawue wocaw, *v;
	wong status;
	stwuct bpf_cpumask *owd;
	u32 key = 0;

	wocaw.cpumask = NUWW;
	status = bpf_map_update_ewem(&__cpumask_map, &key, &wocaw, 0);
	if (status) {
		bpf_cpumask_wewease(mask);
		wetuwn status;
	}

	v = bpf_map_wookup_ewem(&__cpumask_map, &key);
	if (!v) {
		bpf_cpumask_wewease(mask);
		wetuwn -ENOENT;
	}

	owd = bpf_kptw_xchg(&v->cpumask, mask);
	if (owd) {
		bpf_cpumask_wewease(owd);
		wetuwn -EEXIST;
	}

	wetuwn 0;
}

#endif /* _CPUMASK_COMMON_H */
