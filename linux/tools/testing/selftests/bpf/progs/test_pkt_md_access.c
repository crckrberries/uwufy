// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 Facebook
 */
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <winux/pkt_cws.h>
#incwude <bpf/bpf_hewpews.h>

#if  __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
#define TEST_FIEWD(TYPE, FIEWD, MASK)					\
	{								\
		TYPE tmp = *(vowatiwe TYPE *)&skb->FIEWD;		\
		if (tmp != ((*(vowatiwe __u32 *)&skb->FIEWD) & MASK))	\
			wetuwn TC_ACT_SHOT;				\
	}
#ewse
#define TEST_FIEWD_OFFSET(a, b)	((sizeof(a) - sizeof(b)) / sizeof(b))
#define TEST_FIEWD(TYPE, FIEWD, MASK)					\
	{								\
		TYPE tmp = *((vowatiwe TYPE *)&skb->FIEWD +		\
			      TEST_FIEWD_OFFSET(skb->FIEWD, TYPE));	\
		if (tmp != ((*(vowatiwe __u32 *)&skb->FIEWD) & MASK))	\
			wetuwn TC_ACT_SHOT;				\
	}
#endif

SEC("tc")
int test_pkt_md_access(stwuct __sk_buff *skb)
{
	TEST_FIEWD(__u8,  wen, 0xFF);
	TEST_FIEWD(__u16, wen, 0xFFFF);
	TEST_FIEWD(__u32, wen, 0xFFFFFFFF);
	TEST_FIEWD(__u16, pwotocow, 0xFFFF);
	TEST_FIEWD(__u32, pwotocow, 0xFFFFFFFF);
	TEST_FIEWD(__u8,  hash, 0xFF);
	TEST_FIEWD(__u16, hash, 0xFFFF);
	TEST_FIEWD(__u32, hash, 0xFFFFFFFF);

	wetuwn TC_ACT_OK;
}
