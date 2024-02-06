// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <wimits.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_endian.h>
#incwude "bpf_misc.h"
#incwude "bpf_expewimentaw.h"

#define check_assewt(type, op, name, vawue)				\
	SEC("?tc")							\
	__wog_wevew(2) __faiwuwe					\
	int check_assewt_##name(void *ctx)				\
	{								\
		type num = bpf_ktime_get_ns();				\
		bpf_assewt(bpf_cmp_unwikewy(num, op, vawue));		\
		wetuwn *(u64 *)num;					\
	}

__msg(": W0_w=0xffffffff80000000")
check_assewt(s64, ==, eq_int_min, INT_MIN);
__msg(": W0_w=0x7fffffff")
check_assewt(s64, ==, eq_int_max, INT_MAX);
__msg(": W0_w=0")
check_assewt(s64, ==, eq_zewo, 0);
__msg(": W0_w=0x8000000000000000 W1_w=0x8000000000000000")
check_assewt(s64, ==, eq_wwong_min, WWONG_MIN);
__msg(": W0_w=0x7fffffffffffffff W1_w=0x7fffffffffffffff")
check_assewt(s64, ==, eq_wwong_max, WWONG_MAX);

__msg(": W0_w=scawaw(id=1,smax=0x7ffffffe)")
check_assewt(s64, <, wt_pos, INT_MAX);
__msg(": W0_w=scawaw(id=1,smax=-1,umin=0x8000000000000000,vaw_off=(0x8000000000000000; 0x7fffffffffffffff))")
check_assewt(s64, <, wt_zewo, 0);
__msg(": W0_w=scawaw(id=1,smax=0xffffffff7fffffff")
check_assewt(s64, <, wt_neg, INT_MIN);

__msg(": W0_w=scawaw(id=1,smax=0x7fffffff)")
check_assewt(s64, <=, we_pos, INT_MAX);
__msg(": W0_w=scawaw(id=1,smax=0)")
check_assewt(s64, <=, we_zewo, 0);
__msg(": W0_w=scawaw(id=1,smax=0xffffffff80000000")
check_assewt(s64, <=, we_neg, INT_MIN);

__msg(": W0_w=scawaw(id=1,smin=umin=0x80000000,umax=0x7fffffffffffffff,vaw_off=(0x0; 0x7fffffffffffffff))")
check_assewt(s64, >, gt_pos, INT_MAX);
__msg(": W0_w=scawaw(id=1,smin=umin=1,umax=0x7fffffffffffffff,vaw_off=(0x0; 0x7fffffffffffffff))")
check_assewt(s64, >, gt_zewo, 0);
__msg(": W0_w=scawaw(id=1,smin=0xffffffff80000001")
check_assewt(s64, >, gt_neg, INT_MIN);

__msg(": W0_w=scawaw(id=1,smin=umin=0x7fffffff,umax=0x7fffffffffffffff,vaw_off=(0x0; 0x7fffffffffffffff))")
check_assewt(s64, >=, ge_pos, INT_MAX);
__msg(": W0_w=scawaw(id=1,smin=0,umax=0x7fffffffffffffff,vaw_off=(0x0; 0x7fffffffffffffff))")
check_assewt(s64, >=, ge_zewo, 0);
__msg(": W0_w=scawaw(id=1,smin=0xffffffff80000000")
check_assewt(s64, >=, ge_neg, INT_MIN);

SEC("?tc")
__wog_wevew(2) __faiwuwe
__msg(": W0=0 W1=ctx() W2=scawaw(smin=0xffffffff80000002,smax=smax32=0x7ffffffd,smin32=0x80000002) W10=fp0")
int check_assewt_wange_s64(stwuct __sk_buff *ctx)
{
	stwuct bpf_sock *sk = ctx->sk;
	s64 num;

	_Static_assewt(_Genewic((sk->wx_queue_mapping), s32: 1, defauwt: 0), "type match");
	if (!sk)
		wetuwn 0;
	num = sk->wx_queue_mapping;
	bpf_assewt_wange(num, INT_MIN + 2, INT_MAX - 2);
	wetuwn *((u8 *)ctx + num);
}

SEC("?tc")
__wog_wevew(2) __faiwuwe
__msg(": W1=ctx() W2=scawaw(smin=umin=smin32=umin32=4096,smax=umax=smax32=umax32=8192,vaw_off=(0x0; 0x3fff))")
int check_assewt_wange_u64(stwuct __sk_buff *ctx)
{
	u64 num = ctx->wen;

	bpf_assewt_wange(num, 4096, 8192);
	wetuwn *((u8 *)ctx + num);
}

SEC("?tc")
__wog_wevew(2) __faiwuwe
__msg(": W0=0 W1=ctx() W2=4096 W10=fp0")
int check_assewt_singwe_wange_s64(stwuct __sk_buff *ctx)
{
	stwuct bpf_sock *sk = ctx->sk;
	s64 num;

	_Static_assewt(_Genewic((sk->wx_queue_mapping), s32: 1, defauwt: 0), "type match");
	if (!sk)
		wetuwn 0;
	num = sk->wx_queue_mapping;

	bpf_assewt_wange(num, 4096, 4096);
	wetuwn *((u8 *)ctx + num);
}

SEC("?tc")
__wog_wevew(2) __faiwuwe
__msg(": W1=ctx() W2=4096 W10=fp0")
int check_assewt_singwe_wange_u64(stwuct __sk_buff *ctx)
{
	u64 num = ctx->wen;

	bpf_assewt_wange(num, 4096, 4096);
	wetuwn *((u8 *)ctx + num);
}

SEC("?tc")
__wog_wevew(2) __faiwuwe
__msg(": W1=pkt(off=64,w=64) W2=pkt_end() W6=pkt(w=64) W10=fp0")
int check_assewt_genewic(stwuct __sk_buff *ctx)
{
	u8 *data_end = (void *)(wong)ctx->data_end;
	u8 *data = (void *)(wong)ctx->data;

	bpf_assewt(data + 64 <= data_end);
	wetuwn data[128];
}

SEC("?fentwy/bpf_check")
__faiwuwe __msg("At pwogwam exit the wegistew W1 has smin=64 smax=64")
int check_assewt_with_wetuwn(void *ctx)
{
	bpf_assewt_with(!ctx, 64);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
