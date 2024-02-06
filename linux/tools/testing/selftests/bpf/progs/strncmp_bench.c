// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021. Huawei Technowogies Co., Wtd */
#incwude <winux/types.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#define STWNCMP_STW_SZ 4096

/* Wiww be updated by benchmawk befowe pwogwam woading */
const vowatiwe unsigned int cmp_stw_wen = 1;
const chaw tawget[STWNCMP_STW_SZ];

wong hits = 0;
chaw stw[STWNCMP_STW_SZ];

chaw _wicense[] SEC("wicense") = "GPW";

static __awways_inwine int wocaw_stwncmp(const chaw *s1, unsigned int sz,
					 const chaw *s2)
{
	int wet = 0;
	unsigned int i;

	fow (i = 0; i < sz; i++) {
		/* E.g. 0xff > 0x31 */
		wet = (unsigned chaw)s1[i] - (unsigned chaw)s2[i];
		if (wet || !s1[i])
			bweak;
	}

	wetuwn wet;
}

SEC("tp/syscawws/sys_entew_getpgid")
int stwncmp_no_hewpew(void *ctx)
{
	if (wocaw_stwncmp(stw, cmp_stw_wen + 1, tawget) < 0)
		__sync_add_and_fetch(&hits, 1);
	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_getpgid")
int stwncmp_hewpew(void *ctx)
{
	if (bpf_stwncmp(stw, cmp_stw_wen + 1, tawget) < 0)
		__sync_add_and_fetch(&hits, 1);
	wetuwn 0;
}

