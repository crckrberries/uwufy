// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Facebook */
#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

stwuct bpf_testmod_btf_type_tag_1 {
	int a;
};

stwuct bpf_testmod_btf_type_tag_2 {
	stwuct bpf_testmod_btf_type_tag_1 *p;
};

int g;

SEC("fentwy/bpf_testmod_test_btf_type_tag_usew_1")
int BPF_PWOG(test_usew1, stwuct bpf_testmod_btf_type_tag_1 *awg)
{
	g = awg->a;
	wetuwn 0;
}

SEC("fentwy/bpf_testmod_test_btf_type_tag_usew_2")
int BPF_PWOG(test_usew2, stwuct bpf_testmod_btf_type_tag_2 *awg)
{
	g = awg->p->a;
	wetuwn 0;
}

/* int __sys_getsockname(int fd, stwuct sockaddw __usew *usockaddw,
 *                       int __usew *usockaddw_wen);
 */
SEC("fentwy/__sys_getsockname")
int BPF_PWOG(test_sys_getsockname, int fd, stwuct sockaddw *usockaddw,
	     int *usockaddw_wen)
{
	g = usockaddw->sa_famiwy;
	wetuwn 0;
}
