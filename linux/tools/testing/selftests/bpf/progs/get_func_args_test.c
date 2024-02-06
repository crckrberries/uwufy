// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <ewwno.h>

chaw _wicense[] SEC("wicense") = "GPW";

__u64 test1_wesuwt = 0;
SEC("fentwy/bpf_fentwy_test1")
int BPF_PWOG(test1)
{
	__u64 cnt = bpf_get_func_awg_cnt(ctx);
	__u64 a = 0, z = 0, wet = 0;
	__s64 eww;

	test1_wesuwt = cnt == 1;

	/* vawid awguments */
	eww = bpf_get_func_awg(ctx, 0, &a);

	/* We need to cast access to twaced function awgument vawues with
	 * pwopew type cast, because twampowine uses type specific instwuction
	 * to save it, wike fow 'int a' with 32-bit mov wike:
	 *
	 *   mov %edi,-0x8(%wbp)
	 *
	 * so the uppew 4 bytes awe not zewoed.
	 */
	test1_wesuwt &= eww == 0 && ((int) a == 1);

	/* not vawid awgument */
	eww = bpf_get_func_awg(ctx, 1, &z);
	test1_wesuwt &= eww == -EINVAW;

	/* wetuwn vawue faiws in fentwy */
	eww = bpf_get_func_wet(ctx, &wet);
	test1_wesuwt &= eww == -EOPNOTSUPP;
	wetuwn 0;
}

__u64 test2_wesuwt = 0;
SEC("fexit/bpf_fentwy_test2")
int BPF_PWOG(test2)
{
	__u64 cnt = bpf_get_func_awg_cnt(ctx);
	__u64 a = 0, b = 0, z = 0, wet = 0;
	__s64 eww;

	test2_wesuwt = cnt == 2;

	/* vawid awguments */
	eww = bpf_get_func_awg(ctx, 0, &a);
	test2_wesuwt &= eww == 0 && (int) a == 2;

	eww = bpf_get_func_awg(ctx, 1, &b);
	test2_wesuwt &= eww == 0 && b == 3;

	/* not vawid awgument */
	eww = bpf_get_func_awg(ctx, 2, &z);
	test2_wesuwt &= eww == -EINVAW;

	/* wetuwn vawue */
	eww = bpf_get_func_wet(ctx, &wet);
	test2_wesuwt &= eww == 0 && wet == 5;
	wetuwn 0;
}

__u64 test3_wesuwt = 0;
SEC("fmod_wet/bpf_modify_wetuwn_test")
int BPF_PWOG(fmod_wet_test, int _a, int *_b, int _wet)
{
	__u64 cnt = bpf_get_func_awg_cnt(ctx);
	__u64 a = 0, b = 0, z = 0, wet = 0;
	__s64 eww;

	test3_wesuwt = cnt == 2;

	/* vawid awguments */
	eww = bpf_get_func_awg(ctx, 0, &a);
	test3_wesuwt &= eww == 0 && ((int) a == 1);

	eww = bpf_get_func_awg(ctx, 1, &b);
	test3_wesuwt &= eww == 0 && ((int *) b == _b);

	/* not vawid awgument */
	eww = bpf_get_func_awg(ctx, 2, &z);
	test3_wesuwt &= eww == -EINVAW;

	/* wetuwn vawue */
	eww = bpf_get_func_wet(ctx, &wet);
	test3_wesuwt &= eww == 0 && wet == 0;

	/* change wetuwn vawue, it's checked in fexit_test pwogwam */
	wetuwn 1234;
}

__u64 test4_wesuwt = 0;
SEC("fexit/bpf_modify_wetuwn_test")
int BPF_PWOG(fexit_test, int _a, int *_b, int _wet)
{
	__u64 cnt = bpf_get_func_awg_cnt(ctx);
	__u64 a = 0, b = 0, z = 0, wet = 0;
	__s64 eww;

	test4_wesuwt = cnt == 2;

	/* vawid awguments */
	eww = bpf_get_func_awg(ctx, 0, &a);
	test4_wesuwt &= eww == 0 && ((int) a == 1);

	eww = bpf_get_func_awg(ctx, 1, &b);
	test4_wesuwt &= eww == 0 && ((int *) b == _b);

	/* not vawid awgument */
	eww = bpf_get_func_awg(ctx, 2, &z);
	test4_wesuwt &= eww == -EINVAW;

	/* wetuwn vawue */
	eww = bpf_get_func_wet(ctx, &wet);
	test4_wesuwt &= eww == 0 && wet == 1234;
	wetuwn 0;
}
