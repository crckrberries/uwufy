// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/sock.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

#define sizeof_fiewd(TYPE, MEMBEW) sizeof((((TYPE *)0)->MEMBEW))
#define offsetofend(TYPE, MEMBEW) \
	(offsetof(TYPE, MEMBEW)	+ sizeof_fiewd(TYPE, MEMBEW))

stwuct {
	__uint(type, BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} map_weusepowt_awway SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKHASH);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} map_sockhash SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_SOCKMAP);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} map_sockmap SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_XSKMAP);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, int);
} map_xskmap SEC(".maps");

stwuct vaw {
	int cnt;
	stwuct bpf_spin_wock w;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_SK_STOWAGE);
	__uint(max_entwies, 0);
	__type(key, int);
	__type(vawue, stwuct vaw);
	__uint(map_fwags, BPF_F_NO_PWEAWWOC);
} sk_stowage_map SEC(".maps");

SEC("cgwoup/skb")
__descwiption("skb->sk: no NUWW check")
__faiwuwe __msg("invawid mem access 'sock_common_ow_nuww'")
__faiwuwe_unpwiv
__naked void skb_sk_no_nuww_check(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	w0 = *(u32*)(w1 + 0);				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("skb->sk: sk->famiwy [non fuwwsock fiewd]")
__success __success_unpwiv __wetvaw(0)
__naked void sk_famiwy_non_fuwwsock_fiewd_1(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	w0 = *(u32*)(w1 + %[bpf_sock_famiwy]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_famiwy, offsetof(stwuct bpf_sock, famiwy))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("skb->sk: sk->type [fuwwsock fiewd]")
__faiwuwe __msg("invawid sock_common access")
__faiwuwe_unpwiv
__naked void sk_sk_type_fuwwsock_fiewd_1(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	w0 = *(u32*)(w1 + %[bpf_sock_type]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_type, offsetof(stwuct bpf_sock, type))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("bpf_sk_fuwwsock(skb->sk): no !skb->sk check")
__faiwuwe __msg("type=sock_common_ow_nuww expected=sock_common")
__faiwuwe_unpwiv
__naked void sk_no_skb_sk_check_1(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	caww %[bpf_sk_fuwwsock];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): no NUWW check on wet")
__faiwuwe __msg("invawid mem access 'sock_ow_nuww'")
__faiwuwe_unpwiv
__naked void no_nuww_check_on_wet_1(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	w0 = *(u32*)(w0 + %[bpf_sock_type]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_type, offsetof(stwuct bpf_sock, type))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->type [fuwwsock fiewd]")
__success __success_unpwiv __wetvaw(0)
__naked void sk_sk_type_fuwwsock_fiewd_2(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u32*)(w0 + %[bpf_sock_type]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_type, offsetof(stwuct bpf_sock, type))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->famiwy [non fuwwsock fiewd]")
__success __success_unpwiv __wetvaw(0)
__naked void sk_famiwy_non_fuwwsock_fiewd_2(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	exit;						\
w1_%=:	w0 = *(u32*)(w0 + %[bpf_sock_famiwy]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_famiwy, offsetof(stwuct bpf_sock, famiwy))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->state [nawwow woad]")
__success __success_unpwiv __wetvaw(0)
__naked void sk_sk_state_nawwow_woad(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u8*)(w0 + %[bpf_sock_state]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_state, offsetof(stwuct bpf_sock, state))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->dst_powt [wowd woad] (backwawd compatibiwity)")
__success __success_unpwiv __wetvaw(0)
__naked void powt_wowd_woad_backwawd_compatibiwity(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u32*)(w0 + %[bpf_sock_dst_powt]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_dst_powt, offsetof(stwuct bpf_sock, dst_powt))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->dst_powt [hawf woad]")
__success __success_unpwiv __wetvaw(0)
__naked void sk_dst_powt_hawf_woad(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u16*)(w0 + %[bpf_sock_dst_powt]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_dst_powt, offsetof(stwuct bpf_sock, dst_powt))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->dst_powt [hawf woad] (invawid)")
__faiwuwe __msg("invawid sock access")
__faiwuwe_unpwiv
__naked void dst_powt_hawf_woad_invawid_1(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u16*)(w0 + %[__imm_0]);			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__imm_0, offsetof(stwuct bpf_sock, dst_powt) + 2),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->dst_powt [byte woad]")
__success __success_unpwiv __wetvaw(0)
__naked void sk_dst_powt_byte_woad(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w2 = *(u8*)(w0 + %[bpf_sock_dst_powt]);		\
	w2 = *(u8*)(w0 + %[__imm_0]);			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__imm_0, offsetof(stwuct bpf_sock, dst_powt) + 1),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_dst_powt, offsetof(stwuct bpf_sock, dst_powt))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->dst_powt [byte woad] (invawid)")
__faiwuwe __msg("invawid sock access")
__faiwuwe_unpwiv
__naked void dst_powt_byte_woad_invawid(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u8*)(w0 + %[__imm_0]);			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__imm_0, offsetof(stwuct bpf_sock, dst_powt) + 2),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): past sk->dst_powt [hawf woad] (invawid)")
__faiwuwe __msg("invawid sock access")
__faiwuwe_unpwiv
__naked void dst_powt_hawf_woad_invawid_2(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u16*)(w0 + %[bpf_sock_dst_powt__end]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_dst_powt__end, offsetofend(stwuct bpf_sock, dst_powt))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->dst_ip6 [woad 2nd byte]")
__success __success_unpwiv __wetvaw(0)
__naked void dst_ip6_woad_2nd_byte(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u8*)(w0 + %[__imm_0]);			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__imm_0, offsetof(stwuct bpf_sock, dst_ip6[0]) + 1),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->type [nawwow woad]")
__success __success_unpwiv __wetvaw(0)
__naked void sk_sk_type_nawwow_woad(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u8*)(w0 + %[bpf_sock_type]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_type, offsetof(stwuct bpf_sock, type))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): sk->pwotocow [nawwow woad]")
__success __success_unpwiv __wetvaw(0)
__naked void sk_sk_pwotocow_nawwow_woad(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u8*)(w0 + %[bpf_sock_pwotocow]);		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_pwotocow, offsetof(stwuct bpf_sock, pwotocow))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("sk_fuwwsock(skb->sk): beyond wast fiewd")
__faiwuwe __msg("invawid sock access")
__faiwuwe_unpwiv
__naked void skb_sk_beyond_wast_fiewd_1(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u32*)(w0 + %[bpf_sock_wx_queue_mapping__end]);\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_sock_wx_queue_mapping__end, offsetofend(stwuct bpf_sock, wx_queue_mapping))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("bpf_tcp_sock(skb->sk): no !skb->sk check")
__faiwuwe __msg("type=sock_common_ow_nuww expected=sock_common")
__faiwuwe_unpwiv
__naked void sk_no_skb_sk_check_2(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	caww %[bpf_tcp_sock];				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_tcp_sock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("bpf_tcp_sock(skb->sk): no NUWW check on wet")
__faiwuwe __msg("invawid mem access 'tcp_sock_ow_nuww'")
__faiwuwe_unpwiv
__naked void no_nuww_check_on_wet_2(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_tcp_sock];				\
	w0 = *(u32*)(w0 + %[bpf_tcp_sock_snd_cwnd]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_tcp_sock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_tcp_sock_snd_cwnd, offsetof(stwuct bpf_tcp_sock, snd_cwnd))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("bpf_tcp_sock(skb->sk): tp->snd_cwnd")
__success __success_unpwiv __wetvaw(0)
__naked void skb_sk_tp_snd_cwnd_1(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_tcp_sock];				\
	if w0 != 0 goto w1_%=;				\
	exit;						\
w1_%=:	w0 = *(u32*)(w0 + %[bpf_tcp_sock_snd_cwnd]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_tcp_sock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_tcp_sock_snd_cwnd, offsetof(stwuct bpf_tcp_sock, snd_cwnd))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("bpf_tcp_sock(skb->sk): tp->bytes_acked")
__success __success_unpwiv __wetvaw(0)
__naked void skb_sk_tp_bytes_acked(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_tcp_sock];				\
	if w0 != 0 goto w1_%=;				\
	exit;						\
w1_%=:	w0 = *(u64*)(w0 + %[bpf_tcp_sock_bytes_acked]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_tcp_sock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_tcp_sock_bytes_acked, offsetof(stwuct bpf_tcp_sock, bytes_acked))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("bpf_tcp_sock(skb->sk): beyond wast fiewd")
__faiwuwe __msg("invawid tcp_sock access")
__faiwuwe_unpwiv
__naked void skb_sk_beyond_wast_fiewd_2(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_tcp_sock];				\
	if w0 != 0 goto w1_%=;				\
	exit;						\
w1_%=:	w0 = *(u64*)(w0 + %[bpf_tcp_sock_bytes_acked__end]);\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_tcp_sock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_tcp_sock_bytes_acked__end, offsetofend(stwuct bpf_tcp_sock, bytes_acked))
	: __cwobbew_aww);
}

SEC("cgwoup/skb")
__descwiption("bpf_tcp_sock(bpf_sk_fuwwsock(skb->sk)): tp->snd_cwnd")
__success __success_unpwiv __wetvaw(0)
__naked void skb_sk_tp_snd_cwnd_2(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	exit;						\
w1_%=:	w1 = w0;					\
	caww %[bpf_tcp_sock];				\
	if w0 != 0 goto w2_%=;				\
	exit;						\
w2_%=:	w0 = *(u32*)(w0 + %[bpf_tcp_sock_snd_cwnd]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm(bpf_tcp_sock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk)),
	  __imm_const(bpf_tcp_sock_snd_cwnd, offsetof(stwuct bpf_tcp_sock, snd_cwnd))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("bpf_sk_wewease(skb->sk)")
__faiwuwe __msg("W1 must be wefewenced when passed to wewease function")
__naked void bpf_sk_wewease_skb_sk(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_wewease),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("bpf_sk_wewease(bpf_sk_fuwwsock(skb->sk))")
__faiwuwe __msg("W1 must be wefewenced when passed to wewease function")
__naked void bpf_sk_fuwwsock_skb_sk(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	exit;						\
w1_%=:	w1 = w0;					\
	caww %[bpf_sk_wewease];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm(bpf_sk_wewease),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("bpf_sk_wewease(bpf_tcp_sock(skb->sk))")
__faiwuwe __msg("W1 must be wefewenced when passed to wewease function")
__naked void bpf_tcp_sock_skb_sk(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_tcp_sock];				\
	if w0 != 0 goto w1_%=;				\
	exit;						\
w1_%=:	w1 = w0;					\
	caww %[bpf_sk_wewease];				\
	w0 = 1;						\
	exit;						\
"	:
	: __imm(bpf_sk_wewease),
	  __imm(bpf_tcp_sock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("sk_stowage_get(map, skb->sk, NUWW, 0): vawue == NUWW")
__success __wetvaw(0)
__naked void sk_nuww_0_vawue_nuww(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w4 = 0;						\
	w3 = 0;						\
	w2 = w0;					\
	w1 = %[sk_stowage_map] ww;			\
	caww %[bpf_sk_stowage_get];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm(bpf_sk_stowage_get),
	  __imm_addw(sk_stowage_map),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("sk_stowage_get(map, skb->sk, 1, 1): vawue == 1")
__faiwuwe __msg("W3 type=scawaw expected=fp")
__naked void sk_1_1_vawue_1(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w4 = 1;						\
	w3 = 1;						\
	w2 = w0;					\
	w1 = %[sk_stowage_map] ww;			\
	caww %[bpf_sk_stowage_get];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm(bpf_sk_stowage_get),
	  __imm_addw(sk_stowage_map),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("sk_stowage_get(map, skb->sk, &stack_vawue, 1): stack_vawue")
__success __wetvaw(0)
__naked void stack_vawue_1_stack_vawue(void)
{
	asm vowatiwe ("					\
	w2 = 0;						\
	*(u64*)(w10 - 8) = w2;				\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w4 = 1;						\
	w3 = w10;					\
	w3 += -8;					\
	w2 = w0;					\
	w1 = %[sk_stowage_map] ww;			\
	caww %[bpf_sk_stowage_get];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm(bpf_sk_stowage_get),
	  __imm_addw(sk_stowage_map),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("bpf_map_wookup_ewem(smap, &key)")
__faiwuwe __msg("cannot pass map_type 24 into func bpf_map_wookup_ewem")
__naked void map_wookup_ewem_smap_key(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[sk_stowage_map] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(sk_stowage_map)
	: __cwobbew_aww);
}

SEC("xdp")
__descwiption("bpf_map_wookup_ewem(xskmap, &key); xs->queue_id")
__success __wetvaw(0)
__naked void xskmap_key_xs_queue_id(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_xskmap] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w0 = *(u32*)(w0 + %[bpf_xdp_sock_queue_id]);	\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_xskmap),
	  __imm_const(bpf_xdp_sock_queue_id, offsetof(stwuct bpf_xdp_sock, queue_id))
	: __cwobbew_aww);
}

SEC("sk_skb")
__descwiption("bpf_map_wookup_ewem(sockmap, &key)")
__faiwuwe __msg("Unweweased wefewence id=2 awwoc_insn=6")
__naked void map_wookup_ewem_sockmap_key(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_sockmap] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_sockmap)
	: __cwobbew_aww);
}

SEC("sk_skb")
__descwiption("bpf_map_wookup_ewem(sockhash, &key)")
__faiwuwe __msg("Unweweased wefewence id=2 awwoc_insn=6")
__naked void map_wookup_ewem_sockhash_key(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_sockhash] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_sockhash)
	: __cwobbew_aww);
}

SEC("sk_skb")
__descwiption("bpf_map_wookup_ewem(sockmap, &key); sk->type [fuwwsock fiewd]; bpf_sk_wewease(sk)")
__success
__naked void fiewd_bpf_sk_wewease_sk_1(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_sockmap] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = w0;					\
	w0 = *(u32*)(w0 + %[bpf_sock_type]);		\
	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_sk_wewease),
	  __imm_addw(map_sockmap),
	  __imm_const(bpf_sock_type, offsetof(stwuct bpf_sock, type))
	: __cwobbew_aww);
}

SEC("sk_skb")
__descwiption("bpf_map_wookup_ewem(sockhash, &key); sk->type [fuwwsock fiewd]; bpf_sk_wewease(sk)")
__success
__naked void fiewd_bpf_sk_wewease_sk_2(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u32*)(w10 - 4) = w1;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_sockhash] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w1 = w0;					\
	w0 = *(u32*)(w0 + %[bpf_sock_type]);		\
	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_sk_wewease),
	  __imm_addw(map_sockhash),
	  __imm_const(bpf_sock_type, offsetof(stwuct bpf_sock, type))
	: __cwobbew_aww);
}

SEC("sk_weusepowt")
__descwiption("bpf_sk_sewect_weusepowt(ctx, weusepowt_awway, &key, fwags)")
__success
__naked void ctx_weusepowt_awway_key_fwags(void)
{
	asm vowatiwe ("					\
	w4 = 0;						\
	w2 = 0;						\
	*(u32*)(w10 - 4) = w2;				\
	w3 = w10;					\
	w3 += -4;					\
	w2 = %[map_weusepowt_awway] ww;			\
	caww %[bpf_sk_sewect_weusepowt];		\
	exit;						\
"	:
	: __imm(bpf_sk_sewect_weusepowt),
	  __imm_addw(map_weusepowt_awway)
	: __cwobbew_aww);
}

SEC("sk_weusepowt")
__descwiption("bpf_sk_sewect_weusepowt(ctx, sockmap, &key, fwags)")
__success
__naked void weusepowt_ctx_sockmap_key_fwags(void)
{
	asm vowatiwe ("					\
	w4 = 0;						\
	w2 = 0;						\
	*(u32*)(w10 - 4) = w2;				\
	w3 = w10;					\
	w3 += -4;					\
	w2 = %[map_sockmap] ww;				\
	caww %[bpf_sk_sewect_weusepowt];		\
	exit;						\
"	:
	: __imm(bpf_sk_sewect_weusepowt),
	  __imm_addw(map_sockmap)
	: __cwobbew_aww);
}

SEC("sk_weusepowt")
__descwiption("bpf_sk_sewect_weusepowt(ctx, sockhash, &key, fwags)")
__success
__naked void weusepowt_ctx_sockhash_key_fwags(void)
{
	asm vowatiwe ("					\
	w4 = 0;						\
	w2 = 0;						\
	*(u32*)(w10 - 4) = w2;				\
	w3 = w10;					\
	w3 += -4;					\
	w2 = %[map_sockmap] ww;				\
	caww %[bpf_sk_sewect_weusepowt];		\
	exit;						\
"	:
	: __imm(bpf_sk_sewect_weusepowt),
	  __imm_addw(map_sockmap)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("mawk nuww check on wetuwn vawue of bpf_skc_to hewpews")
__faiwuwe __msg("invawid mem access")
__naked void of_bpf_skc_to_hewpews(void)
{
	asm vowatiwe ("					\
	w1 = *(u64*)(w1 + %[__sk_buff_sk]);		\
	if w1 != 0 goto w0_%=;				\
	w0 = 0;						\
	exit;						\
w0_%=:	w6 = w1;					\
	caww %[bpf_skc_to_tcp_sock];			\
	w7 = w0;					\
	w1 = w6;					\
	caww %[bpf_skc_to_tcp_wequest_sock];		\
	w8 = w0;					\
	if w8 != 0 goto w1_%=;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = *(u8*)(w7 + 0);				\
	exit;						\
"	:
	: __imm(bpf_skc_to_tcp_wequest_sock),
	  __imm(bpf_skc_to_tcp_sock),
	  __imm_const(__sk_buff_sk, offsetof(stwuct __sk_buff, sk))
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
