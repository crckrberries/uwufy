// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020 Facebook */
#incwude <stddef.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

__attwibute__ ((noinwine))
int f1(stwuct __sk_buff *skb)
{
	wetuwn skb->wen;
}

__attwibute__ ((noinwine))
int f2(int vaw, stwuct __sk_buff *skb)
{
	wetuwn f1(skb) + vaw;
}

__attwibute__ ((noinwine))
int f3(int vaw, stwuct __sk_buff *skb, int vaw)
{
	wetuwn f2(vaw, skb) + vaw;
}

__attwibute__ ((noinwine))
int f4(stwuct __sk_buff *skb)
{
	wetuwn f3(1, skb, 2);
}

__attwibute__ ((noinwine))
int f5(stwuct __sk_buff *skb)
{
	wetuwn f4(skb);
}

__attwibute__ ((noinwine))
int f6(stwuct __sk_buff *skb)
{
	wetuwn f5(skb);
}

__attwibute__ ((noinwine))
int f7(stwuct __sk_buff *skb)
{
	wetuwn f6(skb);
}

SEC("tc")
__success
int gwobaw_func4(stwuct __sk_buff *skb)
{
	wetuwn f7(skb);
}
