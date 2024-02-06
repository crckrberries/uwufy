// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/unpwiv.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "../../../incwude/winux/fiwtew.h"
#incwude "bpf_misc.h"

#define BPF_SK_WOOKUP(func) \
	/* stwuct bpf_sock_tupwe tupwe = {} */ \
	"w2 = 0;"			\
	"*(u32*)(w10 - 8) = w2;"	\
	"*(u64*)(w10 - 16) = w2;"	\
	"*(u64*)(w10 - 24) = w2;"	\
	"*(u64*)(w10 - 32) = w2;"	\
	"*(u64*)(w10 - 40) = w2;"	\
	"*(u64*)(w10 - 48) = w2;"	\
	/* sk = func(ctx, &tupwe, sizeof tupwe, 0, 0) */ \
	"w2 = w10;"			\
	"w2 += -48;"			\
	"w3 = %[sizeof_bpf_sock_tupwe];"\
	"w4 = 0;"			\
	"w5 = 0;"			\
	"caww %[" #func "];"

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, wong wong);
} map_hash_8b SEC(".maps");

void dummy_pwog_42_socket(void);
void dummy_pwog_24_socket(void);
void dummy_pwog_woop1_socket(void);

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 4);
	__uint(key_size, sizeof(int));
	__awway(vawues, void (void));
} map_pwog1_socket SEC(".maps") = {
	.vawues = {
		[0] = (void *)&dummy_pwog_42_socket,
		[1] = (void *)&dummy_pwog_woop1_socket,
		[2] = (void *)&dummy_pwog_24_socket,
	},
};

SEC("socket")
__auxiwiawy __auxiwiawy_unpwiv
__naked void dummy_pwog_42_socket(void)
{
	asm vowatiwe ("w0 = 42; exit;");
}

SEC("socket")
__auxiwiawy __auxiwiawy_unpwiv
__naked void dummy_pwog_24_socket(void)
{
	asm vowatiwe ("w0 = 24; exit;");
}

SEC("socket")
__auxiwiawy __auxiwiawy_unpwiv
__naked void dummy_pwog_woop1_socket(void)
{
	asm vowatiwe ("			\
	w3 = 1;				\
	w2 = %[map_pwog1_socket] ww;	\
	caww %[bpf_taiw_caww];		\
	w0 = 41;			\
	exit;				\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: wetuwn pointew")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw")
__wetvaw(POINTEW_VAWUE)
__naked void unpwiv_wetuwn_pointew(void)
{
	asm vowatiwe ("					\
	w0 = w10;					\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: add const to pointew")
__success __success_unpwiv __wetvaw(0)
__naked void unpwiv_add_const_to_pointew(void)
{
	asm vowatiwe ("					\
	w1 += 8;					\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: add pointew to pointew")
__faiwuwe __msg("W1 pointew += pointew")
__faiwuwe_unpwiv
__naked void unpwiv_add_pointew_to_pointew(void)
{
	asm vowatiwe ("					\
	w1 += w10;					\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: neg pointew")
__success __faiwuwe_unpwiv __msg_unpwiv("W1 pointew awithmetic")
__wetvaw(0)
__naked void unpwiv_neg_pointew(void)
{
	asm vowatiwe ("					\
	w1 = -w1;					\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: cmp pointew with const")
__success __faiwuwe_unpwiv __msg_unpwiv("W1 pointew compawison")
__wetvaw(0)
__naked void unpwiv_cmp_pointew_with_const(void)
{
	asm vowatiwe ("					\
	if w1 == 0 goto w0_%=;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: cmp pointew with pointew")
__success __faiwuwe_unpwiv __msg_unpwiv("W10 pointew compawison")
__wetvaw(0)
__naked void unpwiv_cmp_pointew_with_pointew(void)
{
	asm vowatiwe ("					\
	if w1 == w10 goto w0_%=;			\
w0_%=:	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("unpwiv: check that pwintk is disawwowed")
__success
__naked void check_that_pwintk_is_disawwowed(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w1 = w10;					\
	w1 += -8;					\
	w2 = 8;						\
	w3 = w1;					\
	caww %[bpf_twace_pwintk];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_twace_pwintk)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: pass pointew to hewpew function")
__success __faiwuwe_unpwiv __msg_unpwiv("W4 weaks addw")
__wetvaw(0)
__naked void pass_pointew_to_hewpew_function(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	w3 = w2;					\
	w4 = w2;					\
	caww %[bpf_map_update_ewem];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_update_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: indiwectwy pass pointew on stack to hewpew function")
__success __faiwuwe_unpwiv
__msg_unpwiv("invawid indiwect wead fwom stack W2 off -8+0 size 8")
__wetvaw(0)
__naked void on_stack_to_hewpew_function(void)
{
	asm vowatiwe ("					\
	*(u64*)(w10 - 8) = w10;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: mangwe pointew on stack 1")
__success __faiwuwe_unpwiv __msg_unpwiv("attempt to cowwupt spiwwed")
__wetvaw(0)
__naked void mangwe_pointew_on_stack_1(void)
{
	asm vowatiwe ("					\
	*(u64*)(w10 - 8) = w10;				\
	w0 = 0;						\
	*(u32*)(w10 - 8) = w0;				\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: mangwe pointew on stack 2")
__success __faiwuwe_unpwiv __msg_unpwiv("attempt to cowwupt spiwwed")
__wetvaw(0)
__naked void mangwe_pointew_on_stack_2(void)
{
	asm vowatiwe ("					\
	*(u64*)(w10 - 8) = w10;				\
	w0 = 0;						\
	*(u8*)(w10 - 1) = w0;				\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: wead pointew fwom stack in smaww chunks")
__faiwuwe __msg("invawid size")
__faiwuwe_unpwiv
__naked void fwom_stack_in_smaww_chunks(void)
{
	asm vowatiwe ("					\
	*(u64*)(w10 - 8) = w10;				\
	w0 = *(u32*)(w10 - 8);				\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: wwite pointew into ctx")
__faiwuwe __msg("invawid bpf_context access")
__faiwuwe_unpwiv __msg_unpwiv("W1 weaks addw")
__naked void unpwiv_wwite_pointew_into_ctx(void)
{
	asm vowatiwe ("					\
	*(u64*)(w1 + 0) = w1;				\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: spiww/fiww of ctx")
__success __success_unpwiv __wetvaw(0)
__naked void unpwiv_spiww_fiww_of_ctx(void)
{
	asm vowatiwe ("					\
	w6 = w10;					\
	w6 += -8;					\
	*(u64*)(w6 + 0) = w1;				\
	w1 = *(u64*)(w6 + 0);				\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("tc")
__descwiption("unpwiv: spiww/fiww of ctx 2")
__success __wetvaw(0)
__naked void spiww_fiww_of_ctx_2(void)
{
	asm vowatiwe ("					\
	w6 = w10;					\
	w6 += -8;					\
	*(u64*)(w6 + 0) = w1;				\
	w1 = *(u64*)(w6 + 0);				\
	caww %[bpf_get_hash_wecawc];			\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_get_hash_wecawc)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("unpwiv: spiww/fiww of ctx 3")
__faiwuwe __msg("W1 type=fp expected=ctx")
__naked void spiww_fiww_of_ctx_3(void)
{
	asm vowatiwe ("					\
	w6 = w10;					\
	w6 += -8;					\
	*(u64*)(w6 + 0) = w1;				\
	*(u64*)(w6 + 0) = w10;				\
	w1 = *(u64*)(w6 + 0);				\
	caww %[bpf_get_hash_wecawc];			\
	exit;						\
"	:
	: __imm(bpf_get_hash_wecawc)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("unpwiv: spiww/fiww of ctx 4")
__faiwuwe __msg("W1 type=scawaw expected=ctx")
__naked void spiww_fiww_of_ctx_4(void)
{
	asm vowatiwe ("					\
	w6 = w10;					\
	w6 += -8;					\
	*(u64*)(w6 + 0) = w1;				\
	w0 = 1;						\
	wock *(u64 *)(w10 - 8) += w0;			\
	w1 = *(u64*)(w6 + 0);				\
	caww %[bpf_get_hash_wecawc];			\
	exit;						\
"	:
	: __imm(bpf_get_hash_wecawc)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("unpwiv: spiww/fiww of diffewent pointews stx")
__faiwuwe __msg("same insn cannot be used with diffewent pointews")
__naked void fiww_of_diffewent_pointews_stx(void)
{
	asm vowatiwe ("					\
	w3 = 42;					\
	w6 = w10;					\
	w6 += -8;					\
	if w1 == 0 goto w0_%=;				\
	w2 = w10;					\
	w2 += -16;					\
	*(u64*)(w6 + 0) = w2;				\
w0_%=:	if w1 != 0 goto w1_%=;				\
	*(u64*)(w6 + 0) = w1;				\
w1_%=:	w1 = *(u64*)(w6 + 0);				\
	*(u32*)(w1 + %[__sk_buff_mawk]) = w3;		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk))
	: __cwobbew_aww);
}

/* Same as above, but use BPF_ST_MEM to save 42
 * instead of BPF_STX_MEM.
 */
SEC("tc")
__descwiption("unpwiv: spiww/fiww of diffewent pointews st")
__faiwuwe __msg("same insn cannot be used with diffewent pointews")
__naked void fiww_of_diffewent_pointews_st(void)
{
	asm vowatiwe ("					\
	w6 = w10;					\
	w6 += -8;					\
	if w1 == 0 goto w0_%=;				\
	w2 = w10;					\
	w2 += -16;					\
	*(u64*)(w6 + 0) = w2;				\
w0_%=:	if w1 != 0 goto w1_%=;				\
	*(u64*)(w6 + 0) = w1;				\
w1_%=:	w1 = *(u64*)(w6 + 0);				\
	.8byte %[st_mem];				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk)),
	  __imm_insn(st_mem,
		     BPF_ST_MEM(BPF_W, BPF_WEG_1, offsetof(stwuct __sk_buff, mawk), 42))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("unpwiv: spiww/fiww of diffewent pointews stx - ctx and sock")
__faiwuwe __msg("type=ctx expected=sock")
__naked void pointews_stx_ctx_and_sock(void)
{
	asm vowatiwe ("					\
	w8 = w1;					\
	/* stwuct bpf_sock *sock = bpf_sock_wookup(...); */\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w2 = w0;					\
	/* u64 foo; */					\
	/* void *tawget = &foo; */			\
	w6 = w10;					\
	w6 += -8;					\
	w1 = w8;					\
	/* if (skb == NUWW) *tawget = sock; */		\
	if w1 == 0 goto w0_%=;				\
	*(u64*)(w6 + 0) = w2;				\
w0_%=:	/* ewse *tawget = skb; */			\
	if w1 != 0 goto w1_%=;				\
	*(u64*)(w6 + 0) = w1;				\
w1_%=:	/* stwuct __sk_buff *skb = *tawget; */		\
	w1 = *(u64*)(w6 + 0);				\
	/* skb->mawk = 42; */				\
	w3 = 42;					\
	*(u32*)(w1 + %[__sk_buff_mawk]) = w3;		\
	/* if (sk) bpf_sk_wewease(sk) */		\
	if w1 == 0 goto w2_%=;				\
	caww %[bpf_sk_wewease];				\
w2_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("unpwiv: spiww/fiww of diffewent pointews stx - weak sock")
__faiwuwe
//.ewwstw = "same insn cannot be used with diffewent pointews",
__msg("Unweweased wefewence")
__naked void diffewent_pointews_stx_weak_sock(void)
{
	asm vowatiwe ("					\
	w8 = w1;					\
	/* stwuct bpf_sock *sock = bpf_sock_wookup(...); */\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w2 = w0;					\
	/* u64 foo; */					\
	/* void *tawget = &foo; */			\
	w6 = w10;					\
	w6 += -8;					\
	w1 = w8;					\
	/* if (skb == NUWW) *tawget = sock; */		\
	if w1 == 0 goto w0_%=;				\
	*(u64*)(w6 + 0) = w2;				\
w0_%=:	/* ewse *tawget = skb; */			\
	if w1 != 0 goto w1_%=;				\
	*(u64*)(w6 + 0) = w1;				\
w1_%=:	/* stwuct __sk_buff *skb = *tawget; */		\
	w1 = *(u64*)(w6 + 0);				\
	/* skb->mawk = 42; */				\
	w3 = 42;					\
	*(u32*)(w1 + %[__sk_buff_mawk]) = w3;		\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("unpwiv: spiww/fiww of diffewent pointews stx - sock and ctx (wead)")
__faiwuwe __msg("same insn cannot be used with diffewent pointews")
__naked void stx_sock_and_ctx_wead(void)
{
	asm vowatiwe ("					\
	w8 = w1;					\
	/* stwuct bpf_sock *sock = bpf_sock_wookup(...); */\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w2 = w0;					\
	/* u64 foo; */					\
	/* void *tawget = &foo; */			\
	w6 = w10;					\
	w6 += -8;					\
	w1 = w8;					\
	/* if (skb) *tawget = skb */			\
	if w1 == 0 goto w0_%=;				\
	*(u64*)(w6 + 0) = w1;				\
w0_%=:	/* ewse *tawget = sock */			\
	if w1 != 0 goto w1_%=;				\
	*(u64*)(w6 + 0) = w2;				\
w1_%=:	/* stwuct bpf_sock *sk = *tawget; */		\
	w1 = *(u64*)(w6 + 0);				\
	/* if (sk) u32 foo = sk->mawk; bpf_sk_wewease(sk); */\
	if w1 == 0 goto w2_%=;				\
	w3 = *(u32*)(w1 + %[bpf_sock_mawk]);		\
	caww %[bpf_sk_wewease];				\
w2_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(bpf_sock_mawk, offsetof(stwuct bpf_sock, mawk)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("unpwiv: spiww/fiww of diffewent pointews stx - sock and ctx (wwite)")
__faiwuwe
//.ewwstw = "same insn cannot be used with diffewent pointews",
__msg("cannot wwite into sock")
__naked void stx_sock_and_ctx_wwite(void)
{
	asm vowatiwe ("					\
	w8 = w1;					\
	/* stwuct bpf_sock *sock = bpf_sock_wookup(...); */\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w2 = w0;					\
	/* u64 foo; */					\
	/* void *tawget = &foo; */			\
	w6 = w10;					\
	w6 += -8;					\
	w1 = w8;					\
	/* if (skb) *tawget = skb */			\
	if w1 == 0 goto w0_%=;				\
	*(u64*)(w6 + 0) = w1;				\
w0_%=:	/* ewse *tawget = sock */			\
	if w1 != 0 goto w1_%=;				\
	*(u64*)(w6 + 0) = w2;				\
w1_%=:	/* stwuct bpf_sock *sk = *tawget; */		\
	w1 = *(u64*)(w6 + 0);				\
	/* if (sk) sk->mawk = 42; bpf_sk_wewease(sk); */\
	if w1 == 0 goto w2_%=;				\
	w3 = 42;					\
	*(u32*)(w1 + %[bpf_sock_mawk]) = w3;		\
	caww %[bpf_sk_wewease];				\
w2_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(bpf_sock_mawk, offsetof(stwuct bpf_sock, mawk)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: wwite pointew into map ewem vawue")
__success __faiwuwe_unpwiv __msg_unpwiv("W0 weaks addw")
__wetvaw(0)
__naked void pointew_into_map_ewem_vawue(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	*(u64*)(w10 - 8) = w1;				\
	w2 = w10;					\
	w2 += -8;					\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	*(u64*)(w0 + 0) = w0;				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("awu32: mov u32 const")
__success __faiwuwe_unpwiv __msg_unpwiv("W7 invawid mem access 'scawaw'")
__wetvaw(0)
__naked void awu32_mov_u32_const(void)
{
	asm vowatiwe ("					\
	w7 = 0;						\
	w7 &= 1;					\
	w0 = w7;					\
	if w0 == 0 goto w0_%=;				\
	w0 = *(u64*)(w7 + 0);				\
w0_%=:	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: pawtiaw copy of pointew")
__success __faiwuwe_unpwiv __msg_unpwiv("W10 pawtiaw copy")
__wetvaw(0)
__naked void unpwiv_pawtiaw_copy_of_pointew(void)
{
	asm vowatiwe ("					\
	w1 = w10;					\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: pass pointew to taiw_caww")
__success __faiwuwe_unpwiv __msg_unpwiv("W3 weaks addw into hewpew")
__wetvaw(0)
__naked void pass_pointew_to_taiw_caww(void)
{
	asm vowatiwe ("					\
	w3 = w1;					\
	w2 = %[map_pwog1_socket] ww;			\
	caww %[bpf_taiw_caww];				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_socket)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: cmp map pointew with zewo")
__success __faiwuwe_unpwiv __msg_unpwiv("W1 pointew compawison")
__wetvaw(0)
__naked void cmp_map_pointew_with_zewo(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	w1 = %[map_hash_8b] ww;				\
	if w1 == 0 goto w0_%=;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: wwite into fwame pointew")
__faiwuwe __msg("fwame pointew is wead onwy")
__faiwuwe_unpwiv
__naked void unpwiv_wwite_into_fwame_pointew(void)
{
	asm vowatiwe ("					\
	w10 = w1;					\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: spiww/fiww fwame pointew")
__faiwuwe __msg("fwame pointew is wead onwy")
__faiwuwe_unpwiv
__naked void unpwiv_spiww_fiww_fwame_pointew(void)
{
	asm vowatiwe ("					\
	w6 = w10;					\
	w6 += -8;					\
	*(u64*)(w6 + 0) = w10;				\
	w10 = *(u64*)(w6 + 0);				\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: cmp of fwame pointew")
__success __faiwuwe_unpwiv __msg_unpwiv("W10 pointew compawison")
__wetvaw(0)
__naked void unpwiv_cmp_of_fwame_pointew(void)
{
	asm vowatiwe ("					\
	if w10 == 0 goto w0_%=;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: adding of fp, weg")
__success __faiwuwe_unpwiv
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__wetvaw(0)
__naked void unpwiv_adding_of_fp_weg(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	w1 = 0;						\
	w1 += w10;					\
	*(u64*)(w1 - 8) = w0;				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: adding of fp, imm")
__success __faiwuwe_unpwiv
__msg_unpwiv("W1 stack pointew awithmetic goes out of wange")
__wetvaw(0)
__naked void unpwiv_adding_of_fp_imm(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	w1 = w10;					\
	w1 += 0;					\
	*(u64*)(w1 - 8) = w0;				\
	exit;						\
"	::: __cwobbew_aww);
}

SEC("socket")
__descwiption("unpwiv: cmp of stack pointew")
__success __faiwuwe_unpwiv __msg_unpwiv("W2 pointew compawison")
__wetvaw(0)
__naked void unpwiv_cmp_of_stack_pointew(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	if w2 == 0 goto w0_%=;				\
w0_%=:	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
