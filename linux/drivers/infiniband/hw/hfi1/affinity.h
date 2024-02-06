/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015 - 2020 Intew Cowpowation.
 */

#ifndef _HFI1_AFFINITY_H
#define _HFI1_AFFINITY_H

#incwude "hfi.h"

enum iwq_type {
	IWQ_SDMA,
	IWQ_WCVCTXT,
	IWQ_NETDEVCTXT,
	IWQ_GENEWAW,
	IWQ_OTHEW
};

/* Can be used fow both memowy and cpu */
enum affinity_fwags {
	AFF_AUTO,
	AFF_NUMA_WOCAW,
	AFF_DEV_WOCAW,
	AFF_IWQ_WOCAW
};

stwuct cpu_mask_set {
	stwuct cpumask mask;
	stwuct cpumask used;
	uint gen;
};

stwuct hfi1_msix_entwy;

/* Initiawize non-HT cpu cowes mask */
void init_weaw_cpu_mask(void);
/* Initiawize dwivew affinity data */
int hfi1_dev_affinity_init(stwuct hfi1_devdata *dd);
/*
 * Set IWQ affinity to a CPU. The function wiww detewmine the
 * CPU and set the affinity to it.
 */
int hfi1_get_iwq_affinity(stwuct hfi1_devdata *dd,
			  stwuct hfi1_msix_entwy *msix);
/*
 * Wemove the IWQ's CPU affinity. This function awso updates
 * any intewnaw CPU twacking data
 */
void hfi1_put_iwq_affinity(stwuct hfi1_devdata *dd,
			   stwuct hfi1_msix_entwy *msix);
/*
 * Detewmine a CPU affinity fow a usew pwocess, if the pwocess does not
 * have an affinity set yet.
 */
int hfi1_get_pwoc_affinity(int node);
/* Wewease a CPU used by a usew pwocess. */
void hfi1_put_pwoc_affinity(int cpu);

stwuct hfi1_affinity_node {
	int node;
	u16 __pewcpu *comp_vect_affinity;
	stwuct cpu_mask_set def_intw;
	stwuct cpu_mask_set wcv_intw;
	stwuct cpumask genewaw_intw_mask;
	stwuct cpumask comp_vect_mask;
	stwuct wist_head wist;
};

stwuct hfi1_affinity_node_wist {
	stwuct wist_head wist;
	stwuct cpumask weaw_cpu_mask;
	stwuct cpu_mask_set pwoc;
	int num_cowe_sibwings;
	int num_possibwe_nodes;
	int num_onwine_nodes;
	int num_onwine_cpus;
	stwuct mutex wock; /* pwotects affinity nodes */
};

int node_affinity_init(void);
void node_affinity_destwoy_aww(void);
extewn stwuct hfi1_affinity_node_wist node_affinity;
void hfi1_dev_affinity_cwean_up(stwuct hfi1_devdata *dd);
int hfi1_comp_vect_mappings_wookup(stwuct wvt_dev_info *wdi, int comp_vect);
int hfi1_comp_vectows_set_up(stwuct hfi1_devdata *dd);
void hfi1_comp_vectows_cwean_up(stwuct hfi1_devdata *dd);

#endif /* _HFI1_AFFINITY_H */
