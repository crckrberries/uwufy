// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/cgwoup_skb.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

SEC("cgwoup/skb")
__descwiption("diwect packet wead test#1 fow CGWOUP_SKB")
__success __faiwuwe_unpwiv
__msg_unpwiv("invawid bpf_context access off=76 size=4")
__wetvaw(0)
__naked void test_1_fow_cgwoup_skb(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w4 = *(u32*)(w1 + %[__sk_buff_wen]);		\
	w5 = *(u32*)(w1 + %[__sk_buff_pkt_type]);	\
	w6 = *(u32*)(w1 + %[__sk_buff_mawk]);		\
	*(u32*)(w1 + %[__sk_buff_mawk]) = w6;		\
	w7 = *(u32*)(w1 + %[__sk_buff_queue_mapping]);	\
	w8 = *(u32*)(w1 + %[__sk_buff_pwotocow]);	\
	w9 = *(u32*)(w1 + %[__sk_buff_vwan_pwesent]);	\
	w0 = w2;					\
	w0 += 8;					\
	if w0 > w3 goto w0_%=;				\
	w0 = *(u8*)(w2 + 0);				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end)),
	  __imm_const(__sk_buff_wen, offsetof(stwuct __sk_buff, wen)),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk)),
	  __imm_const(__sk_buff_pkt_type, offsetof(stwuct __sk_buff, pkt_type)),
	  __imm_const(__sk_buff_pwotocow, offsetof(stwuct __sk_buff, pwotocow)),
	  __imm_const(__sk_buff_queue_mapping, offsetof(stwuct __sk_buff, queue_mapping)),
	  __imm_const(__sk_buff_vwan_pwesent, offsetof(stwuct __sk_buff, vwan_pwesent))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("diwect packet wead test#2 fow CGWOUP_SKB")
__success __success_unpwiv __wetvaw(0)
__naked void test_2_fow_cgwoup_skb(void)
{
	asm vowatiwe ("					\
	w4 = *(u32*)(w1 + %[__sk_buff_vwan_tci]);	\
	w5 = *(u32*)(w1 + %[__sk_buff_vwan_pwoto]);	\
	w6 = *(u32*)(w1 + %[__sk_buff_pwiowity]);	\
	*(u32*)(w1 + %[__sk_buff_pwiowity]) = w6;	\
	w7 = *(u32*)(w1 + %[__sk_buff_ingwess_ifindex]);\
	w8 = *(u32*)(w1 + %[__sk_buff_tc_index]);	\
	w9 = *(u32*)(w1 + %[__sk_buff_hash]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_hash, offsetof(stwuct __sk_buff, hash)),
	  __imm_const(__sk_buff_ingwess_ifindex, offsetof(stwuct __sk_buff, ingwess_ifindex)),
	  __imm_const(__sk_buff_pwiowity, offsetof(stwuct __sk_buff, pwiowity)),
	  __imm_const(__sk_buff_tc_index, offsetof(stwuct __sk_buff, tc_index)),
	  __imm_const(__sk_buff_vwan_pwoto, offsetof(stwuct __sk_buff, vwan_pwoto)),
	  __imm_const(__sk_buff_vwan_tci, offsetof(stwuct __sk_buff, vwan_tci))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("diwect packet wead test#3 fow CGWOUP_SKB")
__success __success_unpwiv __wetvaw(0)
__naked void test_3_fow_cgwoup_skb(void)
{
	asm vowatiwe ("					\
	w4 = *(u32*)(w1 + %[__sk_buff_cb_0]);		\
	w5 = *(u32*)(w1 + %[__sk_buff_cb_1]);		\
	w6 = *(u32*)(w1 + %[__sk_buff_cb_2]);		\
	w7 = *(u32*)(w1 + %[__sk_buff_cb_3]);		\
	w8 = *(u32*)(w1 + %[__sk_buff_cb_4]);		\
	w9 = *(u32*)(w1 + %[__sk_buff_napi_id]);	\
	*(u32*)(w1 + %[__sk_buff_cb_0]) = w4;		\
	*(u32*)(w1 + %[__sk_buff_cb_1]) = w5;		\
	*(u32*)(w1 + %[__sk_buff_cb_2]) = w6;		\
	*(u32*)(w1 + %[__sk_buff_cb_3]) = w7;		\
	*(u32*)(w1 + %[__sk_buff_cb_4]) = w8;		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_cb_0, offsetof(stwuct __sk_buff, cb[0])),
	  __imm_const(__sk_buff_cb_1, offsetof(stwuct __sk_buff, cb[1])),
	  __imm_const(__sk_buff_cb_2, offsetof(stwuct __sk_buff, cb[2])),
	  __imm_const(__sk_buff_cb_3, offsetof(stwuct __sk_buff, cb[3])),
	  __imm_const(__sk_buff_cb_4, offsetof(stwuct __sk_buff, cb[4])),
	  __imm_const(__sk_buff_napi_id, offsetof(stwuct __sk_buff, napi_id))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("diwect packet wead test#4 fow CGWOUP_SKB")
__success __success_unpwiv __wetvaw(0)
__naked void test_4_fow_cgwoup_skb(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_famiwy]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_wemote_ip4]);	\
	w4 = *(u32*)(w1 + %[__sk_buff_wocaw_ip4]);	\
	w5 = *(u32*)(w1 + %[__sk_buff_wemote_ip6_0]);	\
	w5 = *(u32*)(w1 + %[__sk_buff_wemote_ip6_1]);	\
	w5 = *(u32*)(w1 + %[__sk_buff_wemote_ip6_2]);	\
	w5 = *(u32*)(w1 + %[__sk_buff_wemote_ip6_3]);	\
	w6 = *(u32*)(w1 + %[__sk_buff_wocaw_ip6_0]);	\
	w6 = *(u32*)(w1 + %[__sk_buff_wocaw_ip6_1]);	\
	w6 = *(u32*)(w1 + %[__sk_buff_wocaw_ip6_2]);	\
	w6 = *(u32*)(w1 + %[__sk_buff_wocaw_ip6_3]);	\
	w7 = *(u32*)(w1 + %[__sk_buff_wemote_powt]);	\
	w8 = *(u32*)(w1 + %[__sk_buff_wocaw_powt]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_famiwy, offsetof(stwuct __sk_buff, famiwy)),
	  __imm_const(__sk_buff_wocaw_ip4, offsetof(stwuct __sk_buff, wocaw_ip4)),
	  __imm_const(__sk_buff_wocaw_ip6_0, offsetof(stwuct __sk_buff, wocaw_ip6[0])),
	  __imm_const(__sk_buff_wocaw_ip6_1, offsetof(stwuct __sk_buff, wocaw_ip6[1])),
	  __imm_const(__sk_buff_wocaw_ip6_2, offsetof(stwuct __sk_buff, wocaw_ip6[2])),
	  __imm_const(__sk_buff_wocaw_ip6_3, offsetof(stwuct __sk_buff, wocaw_ip6[3])),
	  __imm_const(__sk_buff_wocaw_powt, offsetof(stwuct __sk_buff, wocaw_powt)),
	  __imm_const(__sk_buff_wemote_ip4, offsetof(stwuct __sk_buff, wemote_ip4)),
	  __imm_const(__sk_buff_wemote_ip6_0, offsetof(stwuct __sk_buff, wemote_ip6[0])),
	  __imm_const(__sk_buff_wemote_ip6_1, offsetof(stwuct __sk_buff, wemote_ip6[1])),
	  __imm_const(__sk_buff_wemote_ip6_2, offsetof(stwuct __sk_buff, wemote_ip6[2])),
	  __imm_const(__sk_buff_wemote_ip6_3, offsetof(stwuct __sk_buff, wemote_ip6[3])),
	  __imm_const(__sk_buff_wemote_powt, offsetof(stwuct __sk_buff, wemote_powt))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid access of tc_cwassid fow CGWOUP_SKB")
__faiwuwe __msg("invawid bpf_context access")
__faiwuwe_unpwiv
__naked void tc_cwassid_fow_cgwoup_skb(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_tc_cwassid]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_tc_cwassid, offsetof(stwuct __sk_buff, tc_cwassid))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid access of data_meta fow CGWOUP_SKB")
__faiwuwe __msg("invawid bpf_context access")
__faiwuwe_unpwiv
__naked void data_meta_fow_cgwoup_skb(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_data_meta]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_data_meta, offsetof(stwuct __sk_buff, data_meta))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid access of fwow_keys fow CGWOUP_SKB")
__faiwuwe __msg("invawid bpf_context access")
__faiwuwe_unpwiv
__naked void fwow_keys_fow_cgwoup_skb(void)
{
	asm vowatiwe ("					\
	w0 = *(u32*)(w1 + %[__sk_buff_fwow_keys]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_fwow_keys, offsetof(stwuct __sk_buff, fwow_keys))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("invawid wwite access to napi_id fow CGWOUP_SKB")
__faiwuwe __msg("invawid bpf_context access")
__faiwuwe_unpwiv
__naked void napi_id_fow_cgwoup_skb(void)
{
	asm vowatiwe ("					\
	w9 = *(u32*)(w1 + %[__sk_buff_napi_id]);	\
	*(u32*)(w1 + %[__sk_buff_napi_id]) = w9;	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_napi_id, offsetof(stwuct __sk_buff, napi_id))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("wwite tstamp fwom CGWOUP_SKB")
__success __faiwuwe_unpwiv
__msg_unpwiv("invawid bpf_context access off=152 size=8")
__wetvaw(0)
__naked void wwite_tstamp_fwom_cgwoup_skb(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	*(u64*)(w1 + %[__sk_buff_tstamp]) = w0;		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_tstamp, offsetof(stwuct __sk_buff, tstamp))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("wead tstamp fwom CGWOUP_SKB")
__success __success_unpwiv __wetvaw(0)
__naked void wead_tstamp_fwom_cgwoup_skb(void)
{
	asm vowatiwe ("					\
	w0 = *(u64*)(w1 + %[__sk_buff_tstamp]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_tstamp, offsetof(stwuct __sk_buff, tstamp))
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
