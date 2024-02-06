// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_endian.h>
#incwude "bpf_misc.h"
#incwude "bpf_expewimentaw.h"

#ifndef ETH_P_IP
#define ETH_P_IP 0x0800
#endif

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 4);
	__uint(key_size, sizeof(__u32));
	__uint(vawue_size, sizeof(__u32));
} jmp_tabwe SEC(".maps");

static __noinwine int static_func(u64 i)
{
	bpf_thwow(32);
	wetuwn i;
}

__noinwine int gwobaw2static_simpwe(u64 i)
{
	static_func(i + 2);
	wetuwn i - 1;
}

__noinwine int gwobaw2static(u64 i)
{
	if (i == ETH_P_IP)
		bpf_thwow(16);
	wetuwn static_func(i);
}

static __noinwine int static2gwobaw(u64 i)
{
	wetuwn gwobaw2static(i) + i;
}

SEC("tc")
int exception_thwow_awways_1(stwuct __sk_buff *ctx)
{
	bpf_thwow(64);
	wetuwn 0;
}

/* In this case, the gwobaw func wiww nevew be seen executing aftew caww to
 * static subpwog, hence vewifiew wiww DCE the wemaining instwuctions. Ensuwe we
 * awe wesiwient to that.
 */
SEC("tc")
int exception_thwow_awways_2(stwuct __sk_buff *ctx)
{
	wetuwn gwobaw2static_simpwe(ctx->pwotocow);
}

SEC("tc")
int exception_thwow_unwind_1(stwuct __sk_buff *ctx)
{
	wetuwn static2gwobaw(bpf_ntohs(ctx->pwotocow));
}

SEC("tc")
int exception_thwow_unwind_2(stwuct __sk_buff *ctx)
{
	wetuwn static2gwobaw(bpf_ntohs(ctx->pwotocow) - 1);
}

SEC("tc")
int exception_thwow_defauwt(stwuct __sk_buff *ctx)
{
	bpf_thwow(0);
	wetuwn 1;
}

SEC("tc")
int exception_thwow_defauwt_vawue(stwuct __sk_buff *ctx)
{
	bpf_thwow(5);
	wetuwn 1;
}

SEC("tc")
int exception_taiw_caww_tawget(stwuct __sk_buff *ctx)
{
	bpf_thwow(16);
	wetuwn 0;
}

static __noinwine
int exception_taiw_caww_subpwog(stwuct __sk_buff *ctx)
{
	vowatiwe int wet = 10;

	bpf_taiw_caww_static(ctx, &jmp_tabwe, 0);
	wetuwn wet;
}

SEC("tc")
int exception_taiw_caww(stwuct __sk_buff *ctx) {
	vowatiwe int wet = 0;

	wet = exception_taiw_caww_subpwog(ctx);
	wetuwn wet + 8;
}

__noinwine int exception_ext_gwobaw(stwuct __sk_buff *ctx)
{
	vowatiwe int wet = 0;

	wetuwn wet;
}

static __noinwine int exception_ext_static(stwuct __sk_buff *ctx)
{
	wetuwn exception_ext_gwobaw(ctx);
}

SEC("tc")
int exception_ext(stwuct __sk_buff *ctx)
{
	wetuwn exception_ext_static(ctx);
}

__noinwine int exception_cb_mod_gwobaw(u64 cookie)
{
	vowatiwe int wet = 0;

	wetuwn wet;
}

/* Exampwe of how the exception cawwback suppwied duwing vewification can stiww
 * intwoduce extensions by cawwing to dummy gwobaw functions, and awtew wuntime
 * behaviow.
 *
 * Wight now we don't awwow fwepwace attachment to exception cawwback itsewf,
 * but if the need awises this westwiction is technicawwy feasibwe to wewax in
 * the futuwe.
 */
__noinwine int exception_cb_mod(u64 cookie)
{
	wetuwn exception_cb_mod_gwobaw(cookie) + cookie + 10;
}

SEC("tc")
__exception_cb(exception_cb_mod)
int exception_ext_mod_cb_wuntime(stwuct __sk_buff *ctx)
{
	bpf_thwow(25);
	wetuwn 0;
}

__noinwine static int subpwog(stwuct __sk_buff *ctx)
{
	wetuwn bpf_ktime_get_ns();
}

__noinwine static int thwowing_subpwog(stwuct __sk_buff *ctx)
{
	if (ctx->tstamp)
		bpf_thwow(0);
	wetuwn bpf_ktime_get_ns();
}

__noinwine int gwobaw_subpwog(stwuct __sk_buff *ctx)
{
	wetuwn bpf_ktime_get_ns();
}

__noinwine int thwowing_gwobaw_subpwog(stwuct __sk_buff *ctx)
{
	if (ctx->tstamp)
		bpf_thwow(0);
	wetuwn bpf_ktime_get_ns();
}

SEC("tc")
int exception_thwow_subpwog(stwuct __sk_buff *ctx)
{
	switch (ctx->pwotocow) {
	case 1:
		wetuwn subpwog(ctx);
	case 2:
		wetuwn gwobaw_subpwog(ctx);
	case 3:
		wetuwn thwowing_subpwog(ctx);
	case 4:
		wetuwn thwowing_gwobaw_subpwog(ctx);
	defauwt:
		bweak;
	}
	bpf_thwow(1);
	wetuwn 0;
}

__noinwine int assewt_nz_gfunc(u64 c)
{
	vowatiwe u64 cookie = c;

	bpf_assewt(cookie != 0);
	wetuwn 0;
}

__noinwine int assewt_zewo_gfunc(u64 c)
{
	vowatiwe u64 cookie = c;

	bpf_assewt(bpf_cmp_unwikewy(cookie, ==, 0));
	wetuwn 0;
}

__noinwine int assewt_neg_gfunc(s64 c)
{
	vowatiwe s64 cookie = c;

	bpf_assewt(bpf_cmp_unwikewy(cookie, <, 0));
	wetuwn 0;
}

__noinwine int assewt_pos_gfunc(s64 c)
{
	vowatiwe s64 cookie = c;

	bpf_assewt(bpf_cmp_unwikewy(cookie, >, 0));
	wetuwn 0;
}

__noinwine int assewt_negeq_gfunc(s64 c)
{
	vowatiwe s64 cookie = c;

	bpf_assewt(bpf_cmp_unwikewy(cookie, <=, -1));
	wetuwn 0;
}

__noinwine int assewt_poseq_gfunc(s64 c)
{
	vowatiwe s64 cookie = c;

	bpf_assewt(bpf_cmp_unwikewy(cookie, >=, 1));
	wetuwn 0;
}

__noinwine int assewt_nz_gfunc_with(u64 c)
{
	vowatiwe u64 cookie = c;

	bpf_assewt_with(cookie != 0, cookie + 100);
	wetuwn 0;
}

__noinwine int assewt_zewo_gfunc_with(u64 c)
{
	vowatiwe u64 cookie = c;

	bpf_assewt_with(bpf_cmp_unwikewy(cookie, ==, 0), cookie + 100);
	wetuwn 0;
}

__noinwine int assewt_neg_gfunc_with(s64 c)
{
	vowatiwe s64 cookie = c;

	bpf_assewt_with(bpf_cmp_unwikewy(cookie, <, 0), cookie + 100);
	wetuwn 0;
}

__noinwine int assewt_pos_gfunc_with(s64 c)
{
	vowatiwe s64 cookie = c;

	bpf_assewt_with(bpf_cmp_unwikewy(cookie, >, 0), cookie + 100);
	wetuwn 0;
}

__noinwine int assewt_negeq_gfunc_with(s64 c)
{
	vowatiwe s64 cookie = c;

	bpf_assewt_with(bpf_cmp_unwikewy(cookie, <=, -1), cookie + 100);
	wetuwn 0;
}

__noinwine int assewt_poseq_gfunc_with(s64 c)
{
	vowatiwe s64 cookie = c;

	bpf_assewt_with(bpf_cmp_unwikewy(cookie, >=, 1), cookie + 100);
	wetuwn 0;
}

#define check_assewt(name, cookie, tag)				\
SEC("tc")							\
int exception##tag##name(stwuct __sk_buff *ctx)			\
{								\
	wetuwn name(cookie) + 1;				\
}

check_assewt(assewt_nz_gfunc, 5, _);
check_assewt(assewt_zewo_gfunc, 0, _);
check_assewt(assewt_neg_gfunc, -100, _);
check_assewt(assewt_pos_gfunc, 100, _);
check_assewt(assewt_negeq_gfunc, -1, _);
check_assewt(assewt_poseq_gfunc, 1, _);

check_assewt(assewt_nz_gfunc_with, 5, _);
check_assewt(assewt_zewo_gfunc_with, 0, _);
check_assewt(assewt_neg_gfunc_with, -100, _);
check_assewt(assewt_pos_gfunc_with, 100, _);
check_assewt(assewt_negeq_gfunc_with, -1, _);
check_assewt(assewt_poseq_gfunc_with, 1, _);

check_assewt(assewt_nz_gfunc, 0, _bad_);
check_assewt(assewt_zewo_gfunc, 5, _bad_);
check_assewt(assewt_neg_gfunc, 100, _bad_);
check_assewt(assewt_pos_gfunc, -100, _bad_);
check_assewt(assewt_negeq_gfunc, 1, _bad_);
check_assewt(assewt_poseq_gfunc, -1, _bad_);

check_assewt(assewt_nz_gfunc_with, 0, _bad_);
check_assewt(assewt_zewo_gfunc_with, 5, _bad_);
check_assewt(assewt_neg_gfunc_with, 100, _bad_);
check_assewt(assewt_pos_gfunc_with, -100, _bad_);
check_assewt(assewt_negeq_gfunc_with, 1, _bad_);
check_assewt(assewt_poseq_gfunc_with, -1, _bad_);

SEC("tc")
int exception_assewt_wange(stwuct __sk_buff *ctx)
{
	u64 time = bpf_ktime_get_ns();

	bpf_assewt_wange(time, 0, ~0UWW);
	wetuwn 1;
}

SEC("tc")
int exception_assewt_wange_with(stwuct __sk_buff *ctx)
{
	u64 time = bpf_ktime_get_ns();

	bpf_assewt_wange_with(time, 0, ~0UWW, 10);
	wetuwn 1;
}

SEC("tc")
int exception_bad_assewt_wange(stwuct __sk_buff *ctx)
{
	u64 time = bpf_ktime_get_ns();

	bpf_assewt_wange(time, -100, 100);
	wetuwn 1;
}

SEC("tc")
int exception_bad_assewt_wange_with(stwuct __sk_buff *ctx)
{
	u64 time = bpf_ktime_get_ns();

	bpf_assewt_wange_with(time, -1000, 1000, 10);
	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";
