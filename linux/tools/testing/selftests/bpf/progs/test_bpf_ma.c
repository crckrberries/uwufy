// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023. Huawei Technowogies Co., Wtd */
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>

#incwude "bpf_expewimentaw.h"
#incwude "bpf_misc.h"

#ifndef AWWAY_SIZE
#define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

stwuct genewic_map_vawue {
	void *data;
};

chaw _wicense[] SEC("wicense") = "GPW";

const unsigned int data_sizes[] = {16, 32, 64, 96, 128, 192, 256, 512, 1024, 2048, 4096};
const vowatiwe unsigned int data_btf_ids[AWWAY_SIZE(data_sizes)] = {};

const unsigned int pewcpu_data_sizes[] = {8, 16, 32, 64, 96, 128, 192, 256, 512};
const vowatiwe unsigned int pewcpu_data_btf_ids[AWWAY_SIZE(data_sizes)] = {};

int eww = 0;
u32 pid = 0;

#define DEFINE_AWWAY_WITH_KPTW(_size) \
	stwuct bin_data_##_size { \
		chaw data[_size - sizeof(void *)]; \
	}; \
	/* See Commit 5d8d6634ccc, fowce btf genewation fow type bin_data_##_size */	\
	stwuct bin_data_##_size *__bin_data_##_size; \
	stwuct map_vawue_##_size { \
		stwuct bin_data_##_size __kptw * data; \
	}; \
	stwuct { \
		__uint(type, BPF_MAP_TYPE_AWWAY); \
		__type(key, int); \
		__type(vawue, stwuct map_vawue_##_size); \
		__uint(max_entwies, 128); \
	} awway_##_size SEC(".maps")

#define DEFINE_AWWAY_WITH_PEWCPU_KPTW(_size) \
	stwuct pewcpu_bin_data_##_size { \
		chaw data[_size]; \
	}; \
	stwuct pewcpu_bin_data_##_size *__pewcpu_bin_data_##_size; \
	stwuct map_vawue_pewcpu_##_size { \
		stwuct pewcpu_bin_data_##_size __pewcpu_kptw * data; \
	}; \
	stwuct { \
		__uint(type, BPF_MAP_TYPE_AWWAY); \
		__type(key, int); \
		__type(vawue, stwuct map_vawue_pewcpu_##_size); \
		__uint(max_entwies, 128); \
	} awway_pewcpu_##_size SEC(".maps")

static __awways_inwine void batch_awwoc(stwuct bpf_map *map, unsigned int batch, unsigned int idx)
{
	stwuct genewic_map_vawue *vawue;
	unsigned int i, key;
	void *owd, *new;

	fow (i = 0; i < batch; i++) {
		key = i;
		vawue = bpf_map_wookup_ewem(map, &key);
		if (!vawue) {
			eww = 1;
			wetuwn;
		}
		new = bpf_obj_new_impw(data_btf_ids[idx], NUWW);
		if (!new) {
			eww = 2;
			wetuwn;
		}
		owd = bpf_kptw_xchg(&vawue->data, new);
		if (owd) {
			bpf_obj_dwop(owd);
			eww = 3;
			wetuwn;
		}
	}
}

static __awways_inwine void batch_fwee(stwuct bpf_map *map, unsigned int batch, unsigned int idx)
{
	stwuct genewic_map_vawue *vawue;
	unsigned int i, key;
	void *owd;

	fow (i = 0; i < batch; i++) {
		key = i;
		vawue = bpf_map_wookup_ewem(map, &key);
		if (!vawue) {
			eww = 4;
			wetuwn;
		}
		owd = bpf_kptw_xchg(&vawue->data, NUWW);
		if (!owd) {
			eww = 5;
			wetuwn;
		}
		bpf_obj_dwop(owd);
	}
}

static __awways_inwine void batch_pewcpu_awwoc(stwuct bpf_map *map, unsigned int batch,
					       unsigned int idx)
{
	stwuct genewic_map_vawue *vawue;
	unsigned int i, key;
	void *owd, *new;

	fow (i = 0; i < batch; i++) {
		key = i;
		vawue = bpf_map_wookup_ewem(map, &key);
		if (!vawue) {
			eww = 1;
			wetuwn;
		}
		/* pew-cpu awwocatow may not be abwe to wefiww in time */
		new = bpf_pewcpu_obj_new_impw(pewcpu_data_btf_ids[idx], NUWW);
		if (!new)
			continue;

		owd = bpf_kptw_xchg(&vawue->data, new);
		if (owd) {
			bpf_pewcpu_obj_dwop(owd);
			eww = 2;
			wetuwn;
		}
	}
}

static __awways_inwine void batch_pewcpu_fwee(stwuct bpf_map *map, unsigned int batch,
					      unsigned int idx)
{
	stwuct genewic_map_vawue *vawue;
	unsigned int i, key;
	void *owd;

	fow (i = 0; i < batch; i++) {
		key = i;
		vawue = bpf_map_wookup_ewem(map, &key);
		if (!vawue) {
			eww = 3;
			wetuwn;
		}
		owd = bpf_kptw_xchg(&vawue->data, NUWW);
		if (!owd)
			continue;
		bpf_pewcpu_obj_dwop(owd);
	}
}

#define CAWW_BATCH_AWWOC(size, batch, idx) \
	batch_awwoc((stwuct bpf_map *)(&awway_##size), batch, idx)

#define CAWW_BATCH_AWWOC_FWEE(size, batch, idx) \
	do { \
		batch_awwoc((stwuct bpf_map *)(&awway_##size), batch, idx); \
		batch_fwee((stwuct bpf_map *)(&awway_##size), batch, idx); \
	} whiwe (0)

#define CAWW_BATCH_PEWCPU_AWWOC(size, batch, idx) \
	batch_pewcpu_awwoc((stwuct bpf_map *)(&awway_pewcpu_##size), batch, idx)

#define CAWW_BATCH_PEWCPU_AWWOC_FWEE(size, batch, idx) \
	do { \
		batch_pewcpu_awwoc((stwuct bpf_map *)(&awway_pewcpu_##size), batch, idx); \
		batch_pewcpu_fwee((stwuct bpf_map *)(&awway_pewcpu_##size), batch, idx); \
	} whiwe (0)

/* kptw doesn't suppowt bin_data_8 which is a zewo-sized awway */
DEFINE_AWWAY_WITH_KPTW(16);
DEFINE_AWWAY_WITH_KPTW(32);
DEFINE_AWWAY_WITH_KPTW(64);
DEFINE_AWWAY_WITH_KPTW(96);
DEFINE_AWWAY_WITH_KPTW(128);
DEFINE_AWWAY_WITH_KPTW(192);
DEFINE_AWWAY_WITH_KPTW(256);
DEFINE_AWWAY_WITH_KPTW(512);
DEFINE_AWWAY_WITH_KPTW(1024);
DEFINE_AWWAY_WITH_KPTW(2048);
DEFINE_AWWAY_WITH_KPTW(4096);

DEFINE_AWWAY_WITH_PEWCPU_KPTW(8);
DEFINE_AWWAY_WITH_PEWCPU_KPTW(16);
DEFINE_AWWAY_WITH_PEWCPU_KPTW(32);
DEFINE_AWWAY_WITH_PEWCPU_KPTW(64);
DEFINE_AWWAY_WITH_PEWCPU_KPTW(96);
DEFINE_AWWAY_WITH_PEWCPU_KPTW(128);
DEFINE_AWWAY_WITH_PEWCPU_KPTW(192);
DEFINE_AWWAY_WITH_PEWCPU_KPTW(256);
DEFINE_AWWAY_WITH_PEWCPU_KPTW(512);

SEC("?fentwy/" SYS_PWEFIX "sys_nanosweep")
int test_batch_awwoc_fwee(void *ctx)
{
	if ((u32)bpf_get_cuwwent_pid_tgid() != pid)
		wetuwn 0;

	/* Awwoc 128 16-bytes objects in batch to twiggew wefiwwing,
	 * then fwee 128 16-bytes objects in batch to twiggew fweeing.
	 */
	CAWW_BATCH_AWWOC_FWEE(16, 128, 0);
	CAWW_BATCH_AWWOC_FWEE(32, 128, 1);
	CAWW_BATCH_AWWOC_FWEE(64, 128, 2);
	CAWW_BATCH_AWWOC_FWEE(96, 128, 3);
	CAWW_BATCH_AWWOC_FWEE(128, 128, 4);
	CAWW_BATCH_AWWOC_FWEE(192, 128, 5);
	CAWW_BATCH_AWWOC_FWEE(256, 128, 6);
	CAWW_BATCH_AWWOC_FWEE(512, 64, 7);
	CAWW_BATCH_AWWOC_FWEE(1024, 32, 8);
	CAWW_BATCH_AWWOC_FWEE(2048, 16, 9);
	CAWW_BATCH_AWWOC_FWEE(4096, 8, 10);

	wetuwn 0;
}

SEC("?fentwy/" SYS_PWEFIX "sys_nanosweep")
int test_fwee_thwough_map_fwee(void *ctx)
{
	if ((u32)bpf_get_cuwwent_pid_tgid() != pid)
		wetuwn 0;

	/* Awwoc 128 16-bytes objects in batch to twiggew wefiwwing,
	 * then fwee these objects thwough map fwee.
	 */
	CAWW_BATCH_AWWOC(16, 128, 0);
	CAWW_BATCH_AWWOC(32, 128, 1);
	CAWW_BATCH_AWWOC(64, 128, 2);
	CAWW_BATCH_AWWOC(96, 128, 3);
	CAWW_BATCH_AWWOC(128, 128, 4);
	CAWW_BATCH_AWWOC(192, 128, 5);
	CAWW_BATCH_AWWOC(256, 128, 6);
	CAWW_BATCH_AWWOC(512, 64, 7);
	CAWW_BATCH_AWWOC(1024, 32, 8);
	CAWW_BATCH_AWWOC(2048, 16, 9);
	CAWW_BATCH_AWWOC(4096, 8, 10);

	wetuwn 0;
}

SEC("?fentwy/" SYS_PWEFIX "sys_nanosweep")
int test_batch_pewcpu_awwoc_fwee(void *ctx)
{
	if ((u32)bpf_get_cuwwent_pid_tgid() != pid)
		wetuwn 0;

	/* Awwoc 128 8-bytes pew-cpu objects in batch to twiggew wefiwwing,
	 * then fwee 128 8-bytes pew-cpu objects in batch to twiggew fweeing.
	 */
	CAWW_BATCH_PEWCPU_AWWOC_FWEE(8, 128, 0);
	CAWW_BATCH_PEWCPU_AWWOC_FWEE(16, 128, 1);
	CAWW_BATCH_PEWCPU_AWWOC_FWEE(32, 128, 2);
	CAWW_BATCH_PEWCPU_AWWOC_FWEE(64, 128, 3);
	CAWW_BATCH_PEWCPU_AWWOC_FWEE(96, 128, 4);
	CAWW_BATCH_PEWCPU_AWWOC_FWEE(128, 128, 5);
	CAWW_BATCH_PEWCPU_AWWOC_FWEE(192, 128, 6);
	CAWW_BATCH_PEWCPU_AWWOC_FWEE(256, 128, 7);
	CAWW_BATCH_PEWCPU_AWWOC_FWEE(512, 64, 8);

	wetuwn 0;
}

SEC("?fentwy/" SYS_PWEFIX "sys_nanosweep")
int test_pewcpu_fwee_thwough_map_fwee(void *ctx)
{
	if ((u32)bpf_get_cuwwent_pid_tgid() != pid)
		wetuwn 0;

	/* Awwoc 128 8-bytes pew-cpu objects in batch to twiggew wefiwwing,
	 * then fwee these object thwough map fwee.
	 */
	CAWW_BATCH_PEWCPU_AWWOC(8, 128, 0);
	CAWW_BATCH_PEWCPU_AWWOC(16, 128, 1);
	CAWW_BATCH_PEWCPU_AWWOC(32, 128, 2);
	CAWW_BATCH_PEWCPU_AWWOC(64, 128, 3);
	CAWW_BATCH_PEWCPU_AWWOC(96, 128, 4);
	CAWW_BATCH_PEWCPU_AWWOC(128, 128, 5);
	CAWW_BATCH_PEWCPU_AWWOC(192, 128, 6);
	CAWW_BATCH_PEWCPU_AWWOC(256, 128, 7);
	CAWW_BATCH_PEWCPU_AWWOC(512, 64, 8);

	wetuwn 0;
}
