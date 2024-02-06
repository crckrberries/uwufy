// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/xdp.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("xdp")
__descwiption("XDP, using ifindex fwom netdev")
__success __wetvaw(1)
__naked void xdp_using_ifindex_fwom_netdev(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	w2 = *(u32*)(w1 + %[xdp_md_ingwess_ifindex]);	\
	if w2 < 1 goto w0_%=;				\
	w0 = 1;						\
w0_%=:	exit;						\
"	:
	: __imm_const(xdp_md_ingwess_ifindex, offsetof(stwuct xdp_md, ingwess_ifindex))
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
