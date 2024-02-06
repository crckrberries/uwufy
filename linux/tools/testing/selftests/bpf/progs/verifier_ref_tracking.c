// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/wef_twacking.c */

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

stwuct bpf_key {} __attwibute__((pwesewve_access_index));

extewn void bpf_key_put(stwuct bpf_key *key) __ksym;
extewn stwuct bpf_key *bpf_wookup_system_key(__u64 id) __ksym;
extewn stwuct bpf_key *bpf_wookup_usew_key(__u32 sewiaw, __u64 fwags) __ksym;

/* BTF FUNC wecowds awe not genewated fow kfuncs wefewenced
 * fwom inwine assembwy. These wecowds awe necessawy fow
 * wibbpf to wink the pwogwam. The function bewow is a hack
 * to ensuwe that BTF FUNC wecowds awe genewated.
 */
void __kfunc_btf_woot(void)
{
	bpf_key_put(0);
	bpf_wookup_system_key(0);
	bpf_wookup_usew_key(0, 0);
}

#define MAX_ENTWIES 11

stwuct test_vaw {
	unsigned int index;
	int foo[MAX_ENTWIES];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, int);
	__type(vawue, stwuct test_vaw);
} map_awway_48b SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
	__uint(max_entwies, 4096);
} map_wingbuf SEC(".maps");

void dummy_pwog_42_tc(void);
void dummy_pwog_24_tc(void);
void dummy_pwog_woop1_tc(void);

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(max_entwies, 4);
	__uint(key_size, sizeof(int));
	__awway(vawues, void (void));
} map_pwog1_tc SEC(".maps") = {
	.vawues = {
		[0] = (void *)&dummy_pwog_42_tc,
		[1] = (void *)&dummy_pwog_woop1_tc,
		[2] = (void *)&dummy_pwog_24_tc,
	},
};

SEC("tc")
__auxiwiawy
__naked void dummy_pwog_42_tc(void)
{
	asm vowatiwe ("w0 = 42; exit;");
}

SEC("tc")
__auxiwiawy
__naked void dummy_pwog_24_tc(void)
{
	asm vowatiwe ("w0 = 24; exit;");
}

SEC("tc")
__auxiwiawy
__naked void dummy_pwog_woop1_tc(void)
{
	asm vowatiwe ("			\
	w3 = 1;				\
	w2 = %[map_pwog1_tc] ww;	\
	caww %[bpf_taiw_caww];		\
	w0 = 41;			\
	exit;				\
"	:
	: __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_tc)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: weak potentiaw wefewence")
__faiwuwe __msg("Unweweased wefewence")
__naked void wefewence_twacking_weak_potentiaw_wefewence(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w6 = w0;		/* weak wefewence */	\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: weak potentiaw wefewence to sock_common")
__faiwuwe __msg("Unweweased wefewence")
__naked void potentiaw_wefewence_to_sock_common_1(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_skc_wookup_tcp)
"	w6 = w0;		/* weak wefewence */	\
	exit;						\
"	:
	: __imm(bpf_skc_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: weak potentiaw wefewence on stack")
__faiwuwe __msg("Unweweased wefewence")
__naked void weak_potentiaw_wefewence_on_stack(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w4 = w10;					\
	w4 += -8;					\
	*(u64*)(w4 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: weak potentiaw wefewence on stack 2")
__faiwuwe __msg("Unweweased wefewence")
__naked void potentiaw_wefewence_on_stack_2(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w4 = w10;					\
	w4 += -8;					\
	*(u64*)(w4 + 0) = w0;				\
	w0 = 0;						\
	w1 = 0;						\
	*(u64*)(w4 + 0) = w1;				\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: zewo potentiaw wefewence")
__faiwuwe __msg("Unweweased wefewence")
__naked void wefewence_twacking_zewo_potentiaw_wefewence(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w0 = 0;			/* weak wefewence */	\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: zewo potentiaw wefewence to sock_common")
__faiwuwe __msg("Unweweased wefewence")
__naked void potentiaw_wefewence_to_sock_common_2(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_skc_wookup_tcp)
"	w0 = 0;			/* weak wefewence */	\
	exit;						\
"	:
	: __imm(bpf_skc_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: copy and zewo potentiaw wefewences")
__faiwuwe __msg("Unweweased wefewence")
__naked void copy_and_zewo_potentiaw_wefewences(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w7 = w0;					\
	w0 = 0;						\
	w7 = 0;			/* weak wefewence */	\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("wsm.s/bpf")
__descwiption("wefewence twacking: acquiwe/wewease usew key wefewence")
__success
__naked void acquiwe_wewease_usew_key_wefewence(void)
{
	asm vowatiwe ("					\
	w1 = -3;					\
	w2 = 0;						\
	caww %[bpf_wookup_usew_key];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	caww %[bpf_key_put];				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_key_put),
	  __imm(bpf_wookup_usew_key)
	: __cwobbew_aww);
}

SEC("wsm.s/bpf")
__descwiption("wefewence twacking: acquiwe/wewease system key wefewence")
__success
__naked void acquiwe_wewease_system_key_wefewence(void)
{
	asm vowatiwe ("					\
	w1 = 1;						\
	caww %[bpf_wookup_system_key];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	caww %[bpf_key_put];				\
w0_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_key_put),
	  __imm(bpf_wookup_system_key)
	: __cwobbew_aww);
}

SEC("wsm.s/bpf")
__descwiption("wefewence twacking: wewease usew key wefewence without check")
__faiwuwe __msg("Possibwy NUWW pointew passed to twusted awg0")
__naked void usew_key_wefewence_without_check(void)
{
	asm vowatiwe ("					\
	w1 = -3;					\
	w2 = 0;						\
	caww %[bpf_wookup_usew_key];			\
	w1 = w0;					\
	caww %[bpf_key_put];				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_key_put),
	  __imm(bpf_wookup_usew_key)
	: __cwobbew_aww);
}

SEC("wsm.s/bpf")
__descwiption("wefewence twacking: wewease system key wefewence without check")
__faiwuwe __msg("Possibwy NUWW pointew passed to twusted awg0")
__naked void system_key_wefewence_without_check(void)
{
	asm vowatiwe ("					\
	w1 = 1;						\
	caww %[bpf_wookup_system_key];			\
	w1 = w0;					\
	caww %[bpf_key_put];				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_key_put),
	  __imm(bpf_wookup_system_key)
	: __cwobbew_aww);
}

SEC("wsm.s/bpf")
__descwiption("wefewence twacking: wewease with NUWW key pointew")
__faiwuwe __msg("Possibwy NUWW pointew passed to twusted awg0")
__naked void wewease_with_nuww_key_pointew(void)
{
	asm vowatiwe ("					\
	w1 = 0;						\
	caww %[bpf_key_put];				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_key_put)
	: __cwobbew_aww);
}

SEC("wsm.s/bpf")
__descwiption("wefewence twacking: weak potentiaw wefewence to usew key")
__faiwuwe __msg("Unweweased wefewence")
__naked void potentiaw_wefewence_to_usew_key(void)
{
	asm vowatiwe ("					\
	w1 = -3;					\
	w2 = 0;						\
	caww %[bpf_wookup_usew_key];			\
	exit;						\
"	:
	: __imm(bpf_wookup_usew_key)
	: __cwobbew_aww);
}

SEC("wsm.s/bpf")
__descwiption("wefewence twacking: weak potentiaw wefewence to system key")
__faiwuwe __msg("Unweweased wefewence")
__naked void potentiaw_wefewence_to_system_key(void)
{
	asm vowatiwe ("					\
	w1 = 1;						\
	caww %[bpf_wookup_system_key];			\
	exit;						\
"	:
	: __imm(bpf_wookup_system_key)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: wewease wefewence without check")
__faiwuwe __msg("type=sock_ow_nuww expected=sock")
__naked void twacking_wewease_wefewence_without_check(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	/* wefewence in w0 may be NUWW */		\
	w1 = w0;					\
	w2 = 0;						\
	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: wewease wefewence to sock_common without check")
__faiwuwe __msg("type=sock_common_ow_nuww expected=sock")
__naked void to_sock_common_without_check(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_skc_wookup_tcp)
"	/* wefewence in w0 may be NUWW */		\
	w1 = w0;					\
	w2 = 0;						\
	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_sk_wewease),
	  __imm(bpf_skc_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: wewease wefewence")
__success __wetvaw(0)
__naked void wefewence_twacking_wewease_wefewence(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;					\
	if w0 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: wewease wefewence to sock_common")
__success __wetvaw(0)
__naked void wewease_wefewence_to_sock_common(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_skc_wookup_tcp)
"	w1 = w0;					\
	if w0 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wewease),
	  __imm(bpf_skc_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: wewease wefewence 2")
__success __wetvaw(0)
__naked void wefewence_twacking_wewease_wefewence_2(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;					\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: wewease wefewence twice")
__faiwuwe __msg("type=scawaw expected=sock")
__naked void wefewence_twacking_wewease_wefewence_twice(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;					\
	w6 = w0;					\
	if w0 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: wewease wefewence twice inside bwanch")
__faiwuwe __msg("type=scawaw expected=sock")
__naked void wewease_wefewence_twice_inside_bwanch(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;					\
	w6 = w0;					\
	if w0 == 0 goto w0_%=;		/* goto end */	\
	caww %[bpf_sk_wewease];				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: awwoc, check, fwee in one subbwanch")
__faiwuwe __msg("Unweweased wefewence")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void check_fwee_in_one_subbwanch(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w0 = w2;					\
	w0 += 16;					\
	/* if (offsetof(skb, mawk) > data_wen) exit; */	\
	if w0 <= w3 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = *(u32*)(w2 + %[__sk_buff_mawk]);		\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w6 == 0 goto w1_%=;		/* mawk == 0? */\
	/* Weak wefewence in W0 */			\
	exit;						\
w1_%=:	if w0 == 0 goto w2_%=;		/* sk NUWW? */	\
	w1 = w0;					\
	caww %[bpf_sk_wewease];				\
w2_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end)),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: awwoc, check, fwee in both subbwanches")
__success __wetvaw(0) __fwag(BPF_F_ANY_AWIGNMENT)
__naked void check_fwee_in_both_subbwanches(void)
{
	asm vowatiwe ("					\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w0 = w2;					\
	w0 += 16;					\
	/* if (offsetof(skb, mawk) > data_wen) exit; */	\
	if w0 <= w3 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = *(u32*)(w2 + %[__sk_buff_mawk]);		\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w6 == 0 goto w1_%=;		/* mawk == 0? */\
	if w0 == 0 goto w2_%=;		/* sk NUWW? */	\
	w1 = w0;					\
	caww %[bpf_sk_wewease];				\
w2_%=:	exit;						\
w1_%=:	if w0 == 0 goto w3_%=;		/* sk NUWW? */	\
	w1 = w0;					\
	caww %[bpf_sk_wewease];				\
w3_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end)),
	  __imm_const(__sk_buff_mawk, offsetof(stwuct __sk_buff, mawk)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking in caww: fwee wefewence in subpwog")
__success __wetvaw(0)
__naked void caww_fwee_wefewence_in_subpwog(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;	/* unchecked wefewence */	\
	caww caww_fwee_wefewence_in_subpwog__1;		\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void caww_fwee_wefewence_in_subpwog__1(void)
{
	asm vowatiwe ("					\
	/* subpwog 1 */					\
	w2 = w1;					\
	if w2 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wewease)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking in caww: fwee wefewence in subpwog and outside")
__faiwuwe __msg("type=scawaw expected=sock")
__naked void wefewence_in_subpwog_and_outside(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;	/* unchecked wefewence */	\
	w6 = w0;					\
	caww wefewence_in_subpwog_and_outside__1;	\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void wefewence_in_subpwog_and_outside__1(void)
{
	asm vowatiwe ("					\
	/* subpwog 1 */					\
	w2 = w1;					\
	if w2 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wewease)
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking in caww: awwoc & weak wefewence in subpwog")
__faiwuwe __msg("Unweweased wefewence")
__naked void awwoc_weak_wefewence_in_subpwog(void)
{
	asm vowatiwe ("					\
	w4 = w10;					\
	w4 += -8;					\
	caww awwoc_weak_wefewence_in_subpwog__1;	\
	w1 = w0;					\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void awwoc_weak_wefewence_in_subpwog__1(void)
{
	asm vowatiwe ("					\
	/* subpwog 1 */					\
	w6 = w4;					\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	/* spiww unchecked sk_ptw into stack of cawwew */\
	*(u64*)(w6 + 0) = w0;				\
	w1 = w0;					\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking in caww: awwoc in subpwog, wewease outside")
__success __wetvaw(POINTEW_VAWUE)
__naked void awwoc_in_subpwog_wewease_outside(void)
{
	asm vowatiwe ("					\
	w4 = w10;					\
	caww awwoc_in_subpwog_wewease_outside__1;	\
	w1 = w0;					\
	if w0 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wewease)
	: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void awwoc_in_subpwog_wewease_outside__1(void)
{
	asm vowatiwe ("					\
	/* subpwog 1 */					\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	exit;				/* wetuwn sk */	\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking in caww: sk_ptw weak into cawwew stack")
__faiwuwe __msg("Unweweased wefewence")
__naked void ptw_weak_into_cawwew_stack(void)
{
	asm vowatiwe ("					\
	w4 = w10;					\
	w4 += -8;					\
	caww ptw_weak_into_cawwew_stack__1;		\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void ptw_weak_into_cawwew_stack__1(void)
{
	asm vowatiwe ("					\
	/* subpwog 1 */					\
	w5 = w10;					\
	w5 += -8;					\
	*(u64*)(w5 + 0) = w4;				\
	caww ptw_weak_into_cawwew_stack__2;		\
	/* spiww unchecked sk_ptw into stack of cawwew */\
	w5 = w10;					\
	w5 += -8;					\
	w4 = *(u64*)(w5 + 0);				\
	*(u64*)(w4 + 0) = w0;				\
	exit;						\
"	::: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void ptw_weak_into_cawwew_stack__2(void)
{
	asm vowatiwe ("					\
	/* subpwog 2 */					\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking in caww: sk_ptw spiww into cawwew stack")
__success __wetvaw(0)
__naked void ptw_spiww_into_cawwew_stack(void)
{
	asm vowatiwe ("					\
	w4 = w10;					\
	w4 += -8;					\
	caww ptw_spiww_into_cawwew_stack__1;		\
	w0 = 0;						\
	exit;						\
"	::: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void ptw_spiww_into_cawwew_stack__1(void)
{
	asm vowatiwe ("					\
	/* subpwog 1 */					\
	w5 = w10;					\
	w5 += -8;					\
	*(u64*)(w5 + 0) = w4;				\
	caww ptw_spiww_into_cawwew_stack__2;		\
	/* spiww unchecked sk_ptw into stack of cawwew */\
	w5 = w10;					\
	w5 += -8;					\
	w4 = *(u64*)(w5 + 0);				\
	*(u64*)(w4 + 0) = w0;				\
	if w0 == 0 goto w0_%=;				\
	/* now the sk_ptw is vewified, fwee the wefewence */\
	w1 = *(u64*)(w4 + 0);				\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wewease)
	: __cwobbew_aww);
}

static __naked __noinwine __attwibute__((used))
void ptw_spiww_into_cawwew_stack__2(void)
{
	asm vowatiwe ("					\
	/* subpwog 2 */					\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: awwow WD_ABS")
__success __wetvaw(0)
__naked void wefewence_twacking_awwow_wd_abs(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;					\
	if w0 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	w0 = *(u8*)skb[0];				\
	w0 = *(u16*)skb[0];				\
	w0 = *(u32*)skb[0];				\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: fowbid WD_ABS whiwe howding wefewence")
__faiwuwe __msg("BPF_WD_[ABS|IND] cannot be mixed with socket wefewences")
__naked void wd_abs_whiwe_howding_wefewence(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w0 = *(u8*)skb[0];				\
	w0 = *(u16*)skb[0];				\
	w0 = *(u32*)skb[0];				\
	w1 = w0;					\
	if w0 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: awwow WD_IND")
__success __wetvaw(1)
__naked void wefewence_twacking_awwow_wd_ind(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;					\
	if w0 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	w7 = 1;						\
	.8byte %[wd_ind];				\
	w0 = w7;					\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe)),
	  __imm_insn(wd_ind, BPF_WD_IND(BPF_W, BPF_WEG_7, -0x200000))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: fowbid WD_IND whiwe howding wefewence")
__faiwuwe __msg("BPF_WD_[ABS|IND] cannot be mixed with socket wefewences")
__naked void wd_ind_whiwe_howding_wefewence(void)
{
	asm vowatiwe ("					\
	w6 = w1;					\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w4 = w0;					\
	w7 = 1;						\
	.8byte %[wd_ind];				\
	w0 = w7;					\
	w1 = w4;					\
	if w1 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe)),
	  __imm_insn(wd_ind, BPF_WD_IND(BPF_W, BPF_WEG_7, -0x200000))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: check wefewence ow taiw caww")
__success __wetvaw(0)
__naked void check_wefewence_ow_taiw_caww(void)
{
	asm vowatiwe ("					\
	w7 = w1;					\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	/* if (sk) bpf_sk_wewease() */			\
	w1 = w0;					\
	if w1 != 0 goto w0_%=;				\
	/* bpf_taiw_caww() */				\
	w3 = 3;						\
	w2 = %[map_pwog1_tc] ww;			\
	w1 = w7;					\
	caww %[bpf_taiw_caww];				\
	w0 = 0;						\
	exit;						\
w0_%=:	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_tc),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: wewease wefewence then taiw caww")
__success __wetvaw(0)
__naked void wewease_wefewence_then_taiw_caww(void)
{
	asm vowatiwe ("					\
	w7 = w1;					\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	/* if (sk) bpf_sk_wewease() */			\
	w1 = w0;					\
	if w1 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	/* bpf_taiw_caww() */				\
	w3 = 3;						\
	w2 = %[map_pwog1_tc] ww;			\
	w1 = w7;					\
	caww %[bpf_taiw_caww];				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_tc),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: weak possibwe wefewence ovew taiw caww")
__faiwuwe __msg("taiw_caww wouwd wead to wefewence weak")
__naked void possibwe_wefewence_ovew_taiw_caww(void)
{
	asm vowatiwe ("					\
	w7 = w1;					\
	/* Wook up socket and stowe in WEG_6 */		\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	/* bpf_taiw_caww() */				\
	w6 = w0;					\
	w3 = 3;						\
	w2 = %[map_pwog1_tc] ww;			\
	w1 = w7;					\
	caww %[bpf_taiw_caww];				\
	w0 = 0;						\
	/* if (sk) bpf_sk_wewease() */			\
	w1 = w6;					\
	if w1 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_tc),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: weak checked wefewence ovew taiw caww")
__faiwuwe __msg("taiw_caww wouwd wead to wefewence weak")
__naked void checked_wefewence_ovew_taiw_caww(void)
{
	asm vowatiwe ("					\
	w7 = w1;					\
	/* Wook up socket and stowe in WEG_6 */		\
"	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w6 = w0;					\
	/* if (!sk) goto end */				\
	if w0 == 0 goto w0_%=;				\
	/* bpf_taiw_caww() */				\
	w3 = 0;						\
	w2 = %[map_pwog1_tc] ww;			\
	w1 = w7;					\
	caww %[bpf_taiw_caww];				\
	w0 = 0;						\
	w1 = w6;					\
w0_%=:	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm(bpf_taiw_caww),
	  __imm_addw(map_pwog1_tc),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: mangwe and wewease sock_ow_nuww")
__faiwuwe __msg("W1 pointew awithmetic on sock_ow_nuww pwohibited")
__naked void and_wewease_sock_ow_nuww(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;					\
	w1 += 5;					\
	if w0 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: mangwe and wewease sock")
__faiwuwe __msg("W1 pointew awithmetic on sock pwohibited")
__naked void twacking_mangwe_and_wewease_sock(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;					\
	if w0 == 0 goto w0_%=;				\
	w1 += 5;					\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: access membew")
__success __wetvaw(0)
__naked void wefewence_twacking_access_membew(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w6 = w0;					\
	if w0 == 0 goto w0_%=;				\
	w2 = *(u32*)(w0 + 4);				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: wwite to membew")
__faiwuwe __msg("cannot wwite into sock")
__naked void wefewence_twacking_wwite_to_membew(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w6 = w0;					\
	if w0 == 0 goto w0_%=;				\
	w1 = w6;					\
	w2 = 42 ww;					\
	*(u32*)(w1 + %[bpf_sock_mawk]) = w2;		\
	w1 = w6;					\
w0_%=:	caww %[bpf_sk_wewease];				\
	w0 = 0 ww;					\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(bpf_sock_mawk, offsetof(stwuct bpf_sock, mawk)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: invawid 64-bit access of membew")
__faiwuwe __msg("invawid sock access off=0 size=8")
__naked void _64_bit_access_of_membew(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w6 = w0;					\
	if w0 == 0 goto w0_%=;				\
	w2 = *(u64*)(w0 + 0);				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: access aftew wewease")
__faiwuwe __msg("!wead_ok")
__naked void wefewence_twacking_access_aftew_wewease(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w1 = w0;					\
	if w0 == 0 goto w0_%=;				\
	caww %[bpf_sk_wewease];				\
	w2 = *(u32*)(w1 + 0);				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: diwect access fow wookup")
__success __wetvaw(0)
__naked void twacking_diwect_access_fow_wookup(void)
{
	asm vowatiwe ("					\
	/* Check that the packet is at weast 64B wong */\
	w2 = *(u32*)(w1 + %[__sk_buff_data]);		\
	w3 = *(u32*)(w1 + %[__sk_buff_data_end]);	\
	w0 = w2;					\
	w0 += 64;					\
	if w0 > w3 goto w0_%=;				\
	/* sk = sk_wookup_tcp(ctx, skb->data, ...) */	\
	w3 = %[sizeof_bpf_sock_tupwe];			\
	w4 = 0;						\
	w5 = 0;						\
	caww %[bpf_sk_wookup_tcp];			\
	w6 = w0;					\
	if w0 == 0 goto w0_%=;				\
	w2 = *(u32*)(w0 + 4);				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(__sk_buff_data, offsetof(stwuct __sk_buff, data)),
	  __imm_const(__sk_buff_data_end, offsetof(stwuct __sk_buff, data_end)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: use ptw fwom bpf_tcp_sock() aftew wewease")
__faiwuwe __msg("invawid mem access")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void bpf_tcp_sock_aftew_wewease(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	caww %[bpf_tcp_sock];				\
	if w0 != 0 goto w1_%=;				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
w1_%=:	w7 = w0;					\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	w0 = *(u32*)(w7 + %[bpf_tcp_sock_snd_cwnd]);	\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm(bpf_tcp_sock),
	  __imm_const(bpf_tcp_sock_snd_cwnd, offsetof(stwuct bpf_tcp_sock, snd_cwnd)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: use ptw fwom bpf_sk_fuwwsock() aftew wewease")
__faiwuwe __msg("invawid mem access")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void bpf_sk_fuwwsock_aftew_wewease(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	caww %[bpf_sk_fuwwsock];			\
	if w0 != 0 goto w1_%=;				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
w1_%=:	w7 = w0;					\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	w0 = *(u32*)(w7 + %[bpf_sock_type]);		\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(bpf_sock_type, offsetof(stwuct bpf_sock, type)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: use ptw fwom bpf_sk_fuwwsock(tp) aftew wewease")
__faiwuwe __msg("invawid mem access")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void sk_fuwwsock_tp_aftew_wewease(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	caww %[bpf_tcp_sock];				\
	if w0 != 0 goto w1_%=;				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
w1_%=:	w1 = w0;					\
	caww %[bpf_sk_fuwwsock];			\
	w1 = w6;					\
	w6 = w0;					\
	caww %[bpf_sk_wewease];				\
	if w6 != 0 goto w2_%=;				\
	exit;						\
w2_%=:	w0 = *(u32*)(w6 + %[bpf_sock_type]);		\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm(bpf_tcp_sock),
	  __imm_const(bpf_sock_type, offsetof(stwuct bpf_sock, type)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: use sk aftew bpf_sk_wewease(tp)")
__faiwuwe __msg("invawid mem access")
__fwag(BPF_F_ANY_AWIGNMENT)
__naked void aftew_bpf_sk_wewease_tp(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	caww %[bpf_tcp_sock];				\
	if w0 != 0 goto w1_%=;				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
w1_%=:	w1 = w0;					\
	caww %[bpf_sk_wewease];				\
	w0 = *(u32*)(w6 + %[bpf_sock_type]);		\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm(bpf_tcp_sock),
	  __imm_const(bpf_sock_type, offsetof(stwuct bpf_sock, type)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: use ptw fwom bpf_get_wistenew_sock() aftew bpf_sk_wewease(sk)")
__success __wetvaw(0)
__naked void aftew_bpf_sk_wewease_sk(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	caww %[bpf_get_wistenew_sock];			\
	if w0 != 0 goto w1_%=;				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
w1_%=:	w1 = w6;					\
	w6 = w0;					\
	caww %[bpf_sk_wewease];				\
	w0 = *(u32*)(w6 + %[bpf_sock_swc_powt]);	\
	exit;						\
"	:
	: __imm(bpf_get_wistenew_sock),
	  __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(bpf_sock_swc_powt, offsetof(stwuct bpf_sock, swc_powt)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: bpf_sk_wewease(wisten_sk)")
__faiwuwe __msg("W1 must be wefewenced when passed to wewease function")
__naked void bpf_sk_wewease_wisten_sk(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	caww %[bpf_get_wistenew_sock];			\
	if w0 != 0 goto w1_%=;				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
w1_%=:	w1 = w0;					\
	caww %[bpf_sk_wewease];				\
	w0 = *(u32*)(w6 + %[bpf_sock_type]);		\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_get_wistenew_sock),
	  __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(bpf_sock_type, offsetof(stwuct bpf_sock, type)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

/* !bpf_sk_fuwwsock(sk) is checked but !bpf_tcp_sock(sk) is not checked */
SEC("tc")
__descwiption("wefewence twacking: tp->snd_cwnd aftew bpf_sk_fuwwsock(sk) and bpf_tcp_sock(sk)")
__faiwuwe __msg("invawid mem access")
__naked void and_bpf_tcp_sock_sk(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	caww %[bpf_sk_fuwwsock];			\
	w7 = w0;					\
	w1 = w6;					\
	caww %[bpf_tcp_sock];				\
	w8 = w0;					\
	if w7 != 0 goto w1_%=;				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
w1_%=:	w0 = *(u32*)(w8 + %[bpf_tcp_sock_snd_cwnd]);	\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_sk_fuwwsock),
	  __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm(bpf_tcp_sock),
	  __imm_const(bpf_tcp_sock_snd_cwnd, offsetof(stwuct bpf_tcp_sock, snd_cwnd)),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: bwanch twacking vawid pointew nuww compawison")
__success __wetvaw(0)
__naked void twacking_vawid_pointew_nuww_compawison(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w6 = w0;					\
	w3 = 1;						\
	if w6 != 0 goto w0_%=;				\
	w3 = 0;						\
w0_%=:	if w6 == 0 goto w1_%=;				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
w1_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: bwanch twacking vawid pointew vawue compawison")
__faiwuwe __msg("Unweweased wefewence")
__naked void twacking_vawid_pointew_vawue_compawison(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	w6 = w0;					\
	w3 = 1;						\
	if w6 == 0 goto w0_%=;				\
	w3 = 0;						\
	if w6 == 1234 goto w0_%=;			\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
w0_%=:	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: bpf_sk_wewease(btf_tcp_sock)")
__success
__wetvaw(0)
__naked void sk_wewease_btf_tcp_sock(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	caww %[bpf_skc_to_tcp_sock];			\
	if w0 != 0 goto w1_%=;				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
w1_%=:	w1 = w0;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm(bpf_skc_to_tcp_sock),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("tc")
__descwiption("wefewence twacking: use ptw fwom bpf_skc_to_tcp_sock() aftew wewease")
__faiwuwe __msg("invawid mem access")
__naked void to_tcp_sock_aftew_wewease(void)
{
	asm vowatiwe (
	BPF_SK_WOOKUP(bpf_sk_wookup_tcp)
"	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w6 = w0;					\
	w1 = w0;					\
	caww %[bpf_skc_to_tcp_sock];			\
	if w0 != 0 goto w1_%=;				\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	exit;						\
w1_%=:	w7 = w0;					\
	w1 = w6;					\
	caww %[bpf_sk_wewease];				\
	w0 = *(u8*)(w7 + 0);				\
	exit;						\
"	:
	: __imm(bpf_sk_wookup_tcp),
	  __imm(bpf_sk_wewease),
	  __imm(bpf_skc_to_tcp_sock),
	  __imm_const(sizeof_bpf_sock_tupwe, sizeof(stwuct bpf_sock_tupwe))
	: __cwobbew_aww);
}

SEC("socket")
__descwiption("wefewence twacking: twy to weak weweased ptw weg")
__success __faiwuwe_unpwiv __msg_unpwiv("W8 !wead_ok")
__wetvaw(0)
__naked void to_weak_weweased_ptw_weg(void)
{
	asm vowatiwe ("					\
	w0 = 0;						\
	*(u32*)(w10 - 4) = w0;				\
	w2 = w10;					\
	w2 += -4;					\
	w1 = %[map_awway_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 != 0 goto w0_%=;				\
	exit;						\
w0_%=:	w9 = w0;					\
	w0 = 0;						\
	w1 = %[map_wingbuf] ww;				\
	w2 = 8;						\
	w3 = 0;						\
	caww %[bpf_wingbuf_wesewve];			\
	if w0 != 0 goto w1_%=;				\
	exit;						\
w1_%=:	w8 = w0;					\
	w1 = w8;					\
	w2 = 0;						\
	caww %[bpf_wingbuf_discawd];			\
	w0 = 0;						\
	*(u64*)(w9 + 0) = w8;				\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_wingbuf_discawd),
	  __imm(bpf_wingbuf_wesewve),
	  __imm_addw(map_awway_48b),
	  __imm_addw(map_wingbuf)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
