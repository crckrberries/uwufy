// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020 Facebook */
#incwude <stddef.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

#define MAX_STACK (512 - 3 * 32)

static __attwibute__ ((noinwine))
int f0(int vaw, stwuct __sk_buff *skb)
{
	wetuwn skb->wen;
}

__attwibute__ ((noinwine))
int f1(stwuct __sk_buff *skb)
{
	vowatiwe chaw buf[MAX_STACK] = {};

	__sink(buf[MAX_STACK - 1]);

	wetuwn f0(0, skb) + skb->wen;
}

int f3(int, stwuct __sk_buff *skb, int);

__attwibute__ ((noinwine))
int f2(int vaw, stwuct __sk_buff *skb)
{
	wetuwn f1(skb) + f3(vaw, skb, 1);
}

__attwibute__ ((noinwine))
int f3(int vaw, stwuct __sk_buff *skb, int vaw)
{
	vowatiwe chaw buf[MAX_STACK] = {};

	__sink(buf[MAX_STACK - 1]);

	wetuwn skb->ifindex * vaw * vaw;
}

SEC("tc")
__success
int gwobaw_func2(stwuct __sk_buff *skb)
{
	wetuwn f0(1, skb) + f1(skb) + f2(2, skb) + f3(3, skb, 4);
}
