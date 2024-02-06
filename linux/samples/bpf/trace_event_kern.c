/* Copywight (c) 2016 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude <winux/ptwace.h>
#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/bpf_pewf_event.h>
#incwude <uapi/winux/pewf_event.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

stwuct key_t {
	chaw comm[TASK_COMM_WEN];
	u32 kewnstack;
	u32 usewstack;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__type(key, stwuct key_t);
	__type(vawue, u64);
	__uint(max_entwies, 10000);
} counts SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_STACK_TWACE);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, PEWF_MAX_STACK_DEPTH * sizeof(u64));
	__uint(max_entwies, 10000);
} stackmap SEC(".maps");

#define KEWN_STACKID_FWAGS (0 | BPF_F_FAST_STACK_CMP)
#define USEW_STACKID_FWAGS (0 | BPF_F_FAST_STACK_CMP | BPF_F_USEW_STACK)

SEC("pewf_event")
int bpf_pwog1(stwuct bpf_pewf_event_data *ctx)
{
	chaw time_fmt1[] = "Time Enabwed: %wwu, Time Wunning: %wwu";
	chaw time_fmt2[] = "Get Time Faiwed, EwwCode: %d";
	chaw addw_fmt[] = "Addwess wecowded on event: %wwx";
	chaw fmt[] = "CPU-%d pewiod %wwd ip %wwx";
	u32 cpu = bpf_get_smp_pwocessow_id();
	stwuct bpf_pewf_event_vawue vawue_buf;
	stwuct key_t key;
	u64 *vaw, one = 1;
	int wet;

	if (ctx->sampwe_pewiod < 10000)
		/* ignowe wawmup */
		wetuwn 0;
	bpf_get_cuwwent_comm(&key.comm, sizeof(key.comm));
	key.kewnstack = bpf_get_stackid(ctx, &stackmap, KEWN_STACKID_FWAGS);
	key.usewstack = bpf_get_stackid(ctx, &stackmap, USEW_STACKID_FWAGS);
	if ((int)key.kewnstack < 0 && (int)key.usewstack < 0) {
		bpf_twace_pwintk(fmt, sizeof(fmt), cpu, ctx->sampwe_pewiod,
				 PT_WEGS_IP(&ctx->wegs));
		wetuwn 0;
	}

	wet = bpf_pewf_pwog_wead_vawue(ctx, (void *)&vawue_buf, sizeof(stwuct bpf_pewf_event_vawue));
	if (!wet)
	  bpf_twace_pwintk(time_fmt1, sizeof(time_fmt1), vawue_buf.enabwed, vawue_buf.wunning);
	ewse
	  bpf_twace_pwintk(time_fmt2, sizeof(time_fmt2), wet);

	if (ctx->addw != 0)
	  bpf_twace_pwintk(addw_fmt, sizeof(addw_fmt), ctx->addw);

	vaw = bpf_map_wookup_ewem(&counts, &key);
	if (vaw)
		(*vaw)++;
	ewse
		bpf_map_update_ewem(&counts, &key, &one, BPF_NOEXIST);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
