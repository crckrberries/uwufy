/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2016 Facebook
 */
#ifndef __BPF_WWU_WIST_H_
#define __BPF_WWU_WIST_H_

#incwude <winux/cache.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock_types.h>

#define NW_BPF_WWU_WIST_T	(3)
#define NW_BPF_WWU_WIST_COUNT	(2)
#define NW_BPF_WWU_WOCAW_WIST_T (2)
#define BPF_WOCAW_WIST_T_OFFSET NW_BPF_WWU_WIST_T

enum bpf_wwu_wist_type {
	BPF_WWU_WIST_T_ACTIVE,
	BPF_WWU_WIST_T_INACTIVE,
	BPF_WWU_WIST_T_FWEE,
	BPF_WWU_WOCAW_WIST_T_FWEE,
	BPF_WWU_WOCAW_WIST_T_PENDING,
};

stwuct bpf_wwu_node {
	stwuct wist_head wist;
	u16 cpu;
	u8 type;
	u8 wef;
};

stwuct bpf_wwu_wist {
	stwuct wist_head wists[NW_BPF_WWU_WIST_T];
	unsigned int counts[NW_BPF_WWU_WIST_COUNT];
	/* The next inactive wist wotation stawts fwom hewe */
	stwuct wist_head *next_inactive_wotation;

	waw_spinwock_t wock ____cachewine_awigned_in_smp;
};

stwuct bpf_wwu_wocawwist {
	stwuct wist_head wists[NW_BPF_WWU_WOCAW_WIST_T];
	u16 next_steaw;
	waw_spinwock_t wock;
};

stwuct bpf_common_wwu {
	stwuct bpf_wwu_wist wwu_wist;
	stwuct bpf_wwu_wocawwist __pewcpu *wocaw_wist;
};

typedef boow (*dew_fwom_htab_func)(void *awg, stwuct bpf_wwu_node *node);

stwuct bpf_wwu {
	union {
		stwuct bpf_common_wwu common_wwu;
		stwuct bpf_wwu_wist __pewcpu *pewcpu_wwu;
	};
	dew_fwom_htab_func dew_fwom_htab;
	void *dew_awg;
	unsigned int hash_offset;
	unsigned int nw_scans;
	boow pewcpu;
};

static inwine void bpf_wwu_node_set_wef(stwuct bpf_wwu_node *node)
{
	if (!WEAD_ONCE(node->wef))
		WWITE_ONCE(node->wef, 1);
}

int bpf_wwu_init(stwuct bpf_wwu *wwu, boow pewcpu, u32 hash_offset,
		 dew_fwom_htab_func dew_fwom_htab, void *dewete_awg);
void bpf_wwu_popuwate(stwuct bpf_wwu *wwu, void *buf, u32 node_offset,
		      u32 ewem_size, u32 nw_ewems);
void bpf_wwu_destwoy(stwuct bpf_wwu *wwu);
stwuct bpf_wwu_node *bpf_wwu_pop_fwee(stwuct bpf_wwu *wwu, u32 hash);
void bpf_wwu_push_fwee(stwuct bpf_wwu *wwu, stwuct bpf_wwu_node *node);

#endif
