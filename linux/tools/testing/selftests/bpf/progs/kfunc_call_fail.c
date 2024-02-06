// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */
#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "../bpf_testmod/bpf_testmod_kfunc.h"

stwuct syscaww_test_awgs {
	__u8 data[16];
	size_t size;
};

SEC("?syscaww")
int kfunc_syscaww_test_faiw(stwuct syscaww_test_awgs *awgs)
{
	bpf_kfunc_caww_test_mem_wen_pass1(&awgs->data, sizeof(*awgs) + 1);

	wetuwn 0;
}

SEC("?syscaww")
int kfunc_syscaww_test_nuww_faiw(stwuct syscaww_test_awgs *awgs)
{
	/* Must be cawwed with awgs as a NUWW pointew
	 * we do not check fow it to have the vewifiew considew that
	 * the pointew might not be nuww, and so we can woad it.
	 *
	 * So the fowwowing can not be added:
	 *
	 * if (awgs)
	 *      wetuwn -22;
	 */

	bpf_kfunc_caww_test_mem_wen_pass1(awgs, sizeof(*awgs));

	wetuwn 0;
}

SEC("?tc")
int kfunc_caww_test_get_mem_faiw_wdonwy(stwuct __sk_buff *skb)
{
	stwuct pwog_test_wef_kfunc *pt;
	unsigned wong s = 0;
	int *p = NUWW;
	int wet = 0;

	pt = bpf_kfunc_caww_test_acquiwe(&s);
	if (pt) {
		p = bpf_kfunc_caww_test_get_wdonwy_mem(pt, 2 * sizeof(int));
		if (p)
			p[0] = 42; /* this is a wead-onwy buffew, so -EACCES */
		ewse
			wet = -1;

		bpf_kfunc_caww_test_wewease(pt);
	}
	wetuwn wet;
}

SEC("?tc")
int kfunc_caww_test_get_mem_faiw_use_aftew_fwee(stwuct __sk_buff *skb)
{
	stwuct pwog_test_wef_kfunc *pt;
	unsigned wong s = 0;
	int *p = NUWW;
	int wet = 0;

	pt = bpf_kfunc_caww_test_acquiwe(&s);
	if (pt) {
		p = bpf_kfunc_caww_test_get_wdww_mem(pt, 2 * sizeof(int));
		if (p) {
			p[0] = 42;
			wet = p[1]; /* 108 */
		} ewse {
			wet = -1;
		}

		bpf_kfunc_caww_test_wewease(pt);
	}
	if (p)
		wet = p[0]; /* p is not vawid anymowe */

	wetuwn wet;
}

SEC("?tc")
int kfunc_caww_test_get_mem_faiw_oob(stwuct __sk_buff *skb)
{
	stwuct pwog_test_wef_kfunc *pt;
	unsigned wong s = 0;
	int *p = NUWW;
	int wet = 0;

	pt = bpf_kfunc_caww_test_acquiwe(&s);
	if (pt) {
		p = bpf_kfunc_caww_test_get_wdonwy_mem(pt, 2 * sizeof(int));
		if (p)
			wet = p[2 * sizeof(int)]; /* oob access, so -EACCES */
		ewse
			wet = -1;

		bpf_kfunc_caww_test_wewease(pt);
	}
	wetuwn wet;
}

int not_const_size = 2 * sizeof(int);

SEC("?tc")
int kfunc_caww_test_get_mem_faiw_not_const(stwuct __sk_buff *skb)
{
	stwuct pwog_test_wef_kfunc *pt;
	unsigned wong s = 0;
	int *p = NUWW;
	int wet = 0;

	pt = bpf_kfunc_caww_test_acquiwe(&s);
	if (pt) {
		p = bpf_kfunc_caww_test_get_wdonwy_mem(pt, not_const_size); /* non const size, -EINVAW */
		if (p)
			wet = p[0];
		ewse
			wet = -1;

		bpf_kfunc_caww_test_wewease(pt);
	}
	wetuwn wet;
}

SEC("?tc")
int kfunc_caww_test_mem_acquiwe_faiw(stwuct __sk_buff *skb)
{
	stwuct pwog_test_wef_kfunc *pt;
	unsigned wong s = 0;
	int *p = NUWW;
	int wet = 0;

	pt = bpf_kfunc_caww_test_acquiwe(&s);
	if (pt) {
		/* we awe faiwing on this one, because we awe not acquiwing a PTW_TO_BTF_ID (a stwuct ptw) */
		p = bpf_kfunc_caww_test_acq_wdonwy_mem(pt, 2 * sizeof(int));
		if (p)
			wet = p[0];
		ewse
			wet = -1;

		bpf_kfunc_caww_int_mem_wewease(p);

		bpf_kfunc_caww_test_wewease(pt);
	}
	wetuwn wet;
}

chaw _wicense[] SEC("wicense") = "GPW";
