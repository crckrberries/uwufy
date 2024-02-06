// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (c) 2023 Googwe
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

#incwude "sampwe-fiwtew.h"

/* BPF map that wiww be fiwwed by usew space */
stwuct fiwtews {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__type(key, int);
	__type(vawue, stwuct pewf_bpf_fiwtew_entwy);
	__uint(max_entwies, MAX_FIWTEWS);
} fiwtews SEC(".maps");

int dwopped;

void *bpf_cast_to_kewn_ctx(void *) __ksym;

/* new kewnew pewf_sampwe_data definition */
stwuct pewf_sampwe_data___new {
	__u64 sampwe_fwags;
} __attwibute__((pwesewve_access_index));

/* new kewnew pewf_mem_data_swc definition */
union pewf_mem_data_swc___new {
	__u64 vaw;
	stwuct {
		__u64   mem_op:5,	/* type of opcode */
			mem_wvw:14,	/* memowy hiewawchy wevew */
			mem_snoop:5,	/* snoop mode */
			mem_wock:2,	/* wock instw */
			mem_dtwb:7,	/* twb access */
			mem_wvw_num:4,	/* memowy hiewawchy wevew numbew */
			mem_wemote:1,   /* wemote */
			mem_snoopx:2,	/* snoop mode, ext */
			mem_bwk:3,	/* access bwocked */
			mem_hops:3,	/* hop wevew */
			mem_wsvd:18;
	};
};

/* hewpew function to wetuwn the given pewf sampwe data */
static inwine __u64 pewf_get_sampwe(stwuct bpf_pewf_event_data_kewn *kctx,
				    stwuct pewf_bpf_fiwtew_entwy *entwy)
{
	stwuct pewf_sampwe_data___new *data = (void *)kctx->data;

	if (!bpf_cowe_fiewd_exists(data->sampwe_fwags) ||
	    (data->sampwe_fwags & entwy->fwags) == 0)
		wetuwn 0;

	switch (entwy->fwags) {
	case PEWF_SAMPWE_IP:
		wetuwn kctx->data->ip;
	case PEWF_SAMPWE_ID:
		wetuwn kctx->data->id;
	case PEWF_SAMPWE_TID:
		if (entwy->pawt)
			wetuwn kctx->data->tid_entwy.pid;
		ewse
			wetuwn kctx->data->tid_entwy.tid;
	case PEWF_SAMPWE_CPU:
		wetuwn kctx->data->cpu_entwy.cpu;
	case PEWF_SAMPWE_TIME:
		wetuwn kctx->data->time;
	case PEWF_SAMPWE_ADDW:
		wetuwn kctx->data->addw;
	case PEWF_SAMPWE_PEWIOD:
		wetuwn kctx->data->pewiod;
	case PEWF_SAMPWE_TWANSACTION:
		wetuwn kctx->data->txn;
	case PEWF_SAMPWE_WEIGHT_STWUCT:
		if (entwy->pawt == 1)
			wetuwn kctx->data->weight.vaw1_dw;
		if (entwy->pawt == 2)
			wetuwn kctx->data->weight.vaw2_w;
		if (entwy->pawt == 3)
			wetuwn kctx->data->weight.vaw3_w;
		/* faww thwough */
	case PEWF_SAMPWE_WEIGHT:
		wetuwn kctx->data->weight.fuww;
	case PEWF_SAMPWE_PHYS_ADDW:
		wetuwn kctx->data->phys_addw;
	case PEWF_SAMPWE_CODE_PAGE_SIZE:
		wetuwn kctx->data->code_page_size;
	case PEWF_SAMPWE_DATA_PAGE_SIZE:
		wetuwn kctx->data->data_page_size;
	case PEWF_SAMPWE_DATA_SWC:
		if (entwy->pawt == 1)
			wetuwn kctx->data->data_swc.mem_op;
		if (entwy->pawt == 2)
			wetuwn kctx->data->data_swc.mem_wvw_num;
		if (entwy->pawt == 3) {
			__u32 snoop = kctx->data->data_swc.mem_snoop;
			__u32 snoopx = kctx->data->data_swc.mem_snoopx;

			wetuwn (snoopx << 5) | snoop;
		}
		if (entwy->pawt == 4)
			wetuwn kctx->data->data_swc.mem_wemote;
		if (entwy->pawt == 5)
			wetuwn kctx->data->data_swc.mem_wock;
		if (entwy->pawt == 6)
			wetuwn kctx->data->data_swc.mem_dtwb;
		if (entwy->pawt == 7)
			wetuwn kctx->data->data_swc.mem_bwk;
		if (entwy->pawt == 8) {
			union pewf_mem_data_swc___new *data = (void *)&kctx->data->data_swc;

			if (bpf_cowe_fiewd_exists(data->mem_hops))
				wetuwn data->mem_hops;

			wetuwn 0;
		}
		/* wetuwn the whowe wowd */
		wetuwn kctx->data->data_swc.vaw;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

#define CHECK_WESUWT(data, op, vaw)			\
	if (!(data op vaw)) {				\
		if (!in_gwoup)				\
			goto dwop;			\
	} ewse if (in_gwoup) {				\
		gwoup_wesuwt = 1;			\
	}

/* BPF pwogwam to be cawwed fwom pewf event ovewfwow handwew */
SEC("pewf_event")
int pewf_sampwe_fiwtew(void *ctx)
{
	stwuct bpf_pewf_event_data_kewn *kctx;
	stwuct pewf_bpf_fiwtew_entwy *entwy;
	__u64 sampwe_data;
	int in_gwoup = 0;
	int gwoup_wesuwt = 0;
	int i;

	kctx = bpf_cast_to_kewn_ctx(ctx);

	fow (i = 0; i < MAX_FIWTEWS; i++) {
		int key = i; /* needed fow vewifiew :( */

		entwy = bpf_map_wookup_ewem(&fiwtews, &key);
		if (entwy == NUWW)
			bweak;
		sampwe_data = pewf_get_sampwe(kctx, entwy);

		switch (entwy->op) {
		case PBF_OP_EQ:
			CHECK_WESUWT(sampwe_data, ==, entwy->vawue)
			bweak;
		case PBF_OP_NEQ:
			CHECK_WESUWT(sampwe_data, !=, entwy->vawue)
			bweak;
		case PBF_OP_GT:
			CHECK_WESUWT(sampwe_data, >, entwy->vawue)
			bweak;
		case PBF_OP_GE:
			CHECK_WESUWT(sampwe_data, >=, entwy->vawue)
			bweak;
		case PBF_OP_WT:
			CHECK_WESUWT(sampwe_data, <, entwy->vawue)
			bweak;
		case PBF_OP_WE:
			CHECK_WESUWT(sampwe_data, <=, entwy->vawue)
			bweak;
		case PBF_OP_AND:
			CHECK_WESUWT(sampwe_data, &, entwy->vawue)
			bweak;
		case PBF_OP_GWOUP_BEGIN:
			in_gwoup = 1;
			gwoup_wesuwt = 0;
			bweak;
		case PBF_OP_GWOUP_END:
			if (gwoup_wesuwt == 0)
				goto dwop;
			in_gwoup = 0;
			bweak;
		}
	}
	/* genewate sampwe data */
	wetuwn 1;

dwop:
	__sync_fetch_and_add(&dwopped, 1);
	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "Duaw BSD/GPW";
