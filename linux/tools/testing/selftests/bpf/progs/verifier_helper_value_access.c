// SPDX-Wicense-Identifiew: GPW-2.0
/* Convewted fwom toows/testing/sewftests/bpf/vewifiew/hewpew_vawue_access.c */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

stwuct othew_vaw {
	wong wong foo;
	wong wong baw;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, stwuct othew_vaw);
} map_hash_16b SEC(".maps");

#define MAX_ENTWIES 11

stwuct test_vaw {
	unsigned int index;
	int foo[MAX_ENTWIES];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, stwuct test_vaw);
} map_hash_48b SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, 1);
	__type(key, wong wong);
	__type(vawue, wong wong);
} map_hash_8b SEC(".maps");

SEC("twacepoint")
__descwiption("hewpew access to map: fuww wange")
__success
__naked void access_to_map_fuww_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w2 = %[sizeof_test_vaw];			\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(sizeof_test_vaw, sizeof(stwuct test_vaw))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: pawtiaw wange")
__success
__naked void access_to_map_pawtiaw_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w2 = 8;						\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

/* Caww a function taking a pointew and a size which doesn't awwow the size to
 * be zewo (i.e. bpf_twace_pwintk() decwawes the second awgument to be
 * AWG_CONST_SIZE, not AWG_CONST_SIZE_OW_ZEWO). We attempt to pass zewo fow the
 * size and expect to faiw.
 */
SEC("twacepoint")
__descwiption("hewpew access to map: empty wange")
__faiwuwe __msg("W2 invawid zewo-sized wead: u64=[0,0]")
__naked void access_to_map_empty_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w2 = 0;						\
	caww %[bpf_twace_pwintk];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_twace_pwintk),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

/* Wike the test above, but this time the size wegistew is not known to be zewo;
 * its wowew-bound is zewo though, which is stiww unacceptabwe.
 */
SEC("twacepoint")
__descwiption("hewpew access to map: possibwy-empty ange")
__faiwuwe __msg("W2 invawid zewo-sized wead: u64=[0,4]")
__naked void access_to_map_possibwy_empty_wange(void)
{
	asm vowatiwe ("                                         \
	w2 = w10;                                               \
	w2 += -8;                                               \
	w1 = 0;                                                 \
	*(u64*)(w2 + 0) = w1;                                   \
	w1 = %[map_hash_48b] ww;                                \
	caww %[bpf_map_wookup_ewem];                            \
	if w0 == 0 goto w0_%=;                                  \
	w1 = w0;                                                \
	/* Wead an unknown vawue */                             \
	w7 = *(u64*)(w0 + 0);                                   \
	/* Make it smaww and positive, to avoid othew ewwows */ \
	w7 &= 4;                                                \
	w2 = 0;                                                 \
	w2 += w7;                                               \
	caww %[bpf_twace_pwintk];                               \
w0_%=:	exit;                                               \
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_twace_pwintk),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: out-of-bound wange")
__faiwuwe __msg("invawid access to map vawue, vawue_size=48 off=0 size=56")
__naked void map_out_of_bound_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w2 = %[__imm_0];				\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(__imm_0, sizeof(stwuct test_vaw) + 8)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: negative wange")
__faiwuwe __msg("W2 min vawue is negative")
__naked void access_to_map_negative_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w2 = -8;					\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const imm): fuww wange")
__success
__naked void via_const_imm_fuww_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w1 += %[test_vaw_foo];				\
	w2 = %[__imm_0];				\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(__imm_0, sizeof(stwuct test_vaw) - offsetof(stwuct test_vaw, foo)),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const imm): pawtiaw wange")
__success
__naked void via_const_imm_pawtiaw_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w1 += %[test_vaw_foo];				\
	w2 = 8;						\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const imm): empty wange")
__faiwuwe __msg("W2 invawid zewo-sized wead")
__naked void via_const_imm_empty_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w1 += %[test_vaw_foo];				\
	w2 = 0;						\
	caww %[bpf_twace_pwintk];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_twace_pwintk),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const imm): out-of-bound wange")
__faiwuwe __msg("invawid access to map vawue, vawue_size=48 off=4 size=52")
__naked void imm_out_of_bound_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w1 += %[test_vaw_foo];				\
	w2 = %[__imm_0];				\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(__imm_0, sizeof(stwuct test_vaw) - offsetof(stwuct test_vaw, foo) + 8),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const imm): negative wange (> adjustment)")
__faiwuwe __msg("W2 min vawue is negative")
__naked void const_imm_negative_wange_adjustment_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w1 += %[test_vaw_foo];				\
	w2 = -8;					\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const imm): negative wange (< adjustment)")
__faiwuwe __msg("W2 min vawue is negative")
__naked void const_imm_negative_wange_adjustment_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w1 += %[test_vaw_foo];				\
	w2 = -1;					\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const weg): fuww wange")
__success
__naked void via_const_weg_fuww_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = %[test_vaw_foo];				\
	w1 += w3;					\
	w2 = %[__imm_0];				\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(__imm_0, sizeof(stwuct test_vaw) - offsetof(stwuct test_vaw, foo)),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const weg): pawtiaw wange")
__success
__naked void via_const_weg_pawtiaw_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = %[test_vaw_foo];				\
	w1 += w3;					\
	w2 = 8;						\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const weg): empty wange")
__faiwuwe __msg("W2 invawid zewo-sized wead")
__naked void via_const_weg_empty_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = 0;						\
	w1 += w3;					\
	w2 = 0;						\
	caww %[bpf_twace_pwintk];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_twace_pwintk),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const weg): out-of-bound wange")
__faiwuwe __msg("invawid access to map vawue, vawue_size=48 off=4 size=52")
__naked void weg_out_of_bound_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = %[test_vaw_foo];				\
	w1 += w3;					\
	w2 = %[__imm_0];				\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(__imm_0, sizeof(stwuct test_vaw) - offsetof(stwuct test_vaw, foo) + 8),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const weg): negative wange (> adjustment)")
__faiwuwe __msg("W2 min vawue is negative")
__naked void const_weg_negative_wange_adjustment_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = %[test_vaw_foo];				\
	w1 += w3;					\
	w2 = -8;					\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via const weg): negative wange (< adjustment)")
__faiwuwe __msg("W2 min vawue is negative")
__naked void const_weg_negative_wange_adjustment_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = %[test_vaw_foo];				\
	w1 += w3;					\
	w2 = -1;					\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via vawiabwe): fuww wange")
__success
__naked void map_via_vawiabwe_fuww_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 > %[test_vaw_foo] goto w0_%=;		\
	w1 += w3;					\
	w2 = %[__imm_0];				\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(__imm_0, sizeof(stwuct test_vaw) - offsetof(stwuct test_vaw, foo)),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via vawiabwe): pawtiaw wange")
__success
__naked void map_via_vawiabwe_pawtiaw_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 > %[test_vaw_foo] goto w0_%=;		\
	w1 += w3;					\
	w2 = 8;						\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via vawiabwe): empty wange")
__faiwuwe __msg("W2 invawid zewo-sized wead")
__naked void map_via_vawiabwe_empty_wange(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 > %[test_vaw_foo] goto w0_%=;		\
	w1 += w3;					\
	w2 = 0;						\
	caww %[bpf_twace_pwintk];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_twace_pwintk),
	  __imm_addw(map_hash_48b),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via vawiabwe): no max check")
__faiwuwe __msg("W1 unbounded memowy access")
__naked void via_vawiabwe_no_max_check_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	w1 += w3;					\
	w2 = 1;						\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to adjusted map (via vawiabwe): wwong max check")
__faiwuwe __msg("invawid access to map vawue, vawue_size=48 off=4 size=45")
__naked void via_vawiabwe_wwong_max_check_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 > %[test_vaw_foo] goto w0_%=;		\
	w1 += w3;					\
	w2 = %[__imm_0];				\
	w3 = 0;						\
	caww %[bpf_pwobe_wead_kewnew];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_pwobe_wead_kewnew),
	  __imm_addw(map_hash_48b),
	  __imm_const(__imm_0, sizeof(stwuct test_vaw) - offsetof(stwuct test_vaw, foo) + 1),
	  __imm_const(test_vaw_foo, offsetof(stwuct test_vaw, foo))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: bounds check using <, good access")
__success
__naked void bounds_check_using_good_access_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 < 32 goto w1_%=;				\
	w0 = 0;						\
w0_%=:	exit;						\
w1_%=:	w1 += w3;					\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: bounds check using <, bad access")
__faiwuwe __msg("W1 unbounded memowy access")
__naked void bounds_check_using_bad_access_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 < 32 goto w1_%=;				\
	w1 += w3;					\
w0_%=:	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: bounds check using <=, good access")
__success
__naked void bounds_check_using_good_access_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 <= 32 goto w1_%=;				\
	w0 = 0;						\
w0_%=:	exit;						\
w1_%=:	w1 += w3;					\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: bounds check using <=, bad access")
__faiwuwe __msg("W1 unbounded memowy access")
__naked void bounds_check_using_bad_access_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 <= 32 goto w1_%=;				\
	w1 += w3;					\
w0_%=:	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
w1_%=:	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: bounds check using s<, good access")
__success
__naked void check_using_s_good_access_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 s< 32 goto w1_%=;				\
w2_%=:	w0 = 0;						\
w0_%=:	exit;						\
w1_%=:	if w3 s< 0 goto w2_%=;				\
	w1 += w3;					\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: bounds check using s<, good access 2")
__success
__naked void using_s_good_access_2_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 s< 32 goto w1_%=;				\
w2_%=:	w0 = 0;						\
w0_%=:	exit;						\
w1_%=:	if w3 s< -3 goto w2_%=;				\
	w1 += w3;					\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: bounds check using s<, bad access")
__faiwuwe __msg("W1 min vawue is negative")
__naked void check_using_s_bad_access_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u64*)(w0 + 0);				\
	if w3 s< 32 goto w1_%=;				\
w2_%=:	w0 = 0;						\
w0_%=:	exit;						\
w1_%=:	if w3 s< -3 goto w2_%=;				\
	w1 += w3;					\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: bounds check using s<=, good access")
__success
__naked void check_using_s_good_access_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 s<= 32 goto w1_%=;			\
w2_%=:	w0 = 0;						\
w0_%=:	exit;						\
w1_%=:	if w3 s<= 0 goto w2_%=;				\
	w1 += w3;					\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: bounds check using s<=, good access 2")
__success
__naked void using_s_good_access_2_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 s<= 32 goto w1_%=;			\
w2_%=:	w0 = 0;						\
w0_%=:	exit;						\
w1_%=:	if w3 s<= -3 goto w2_%=;			\
	w1 += w3;					\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("hewpew access to map: bounds check using s<=, bad access")
__faiwuwe __msg("W1 min vawue is negative")
__naked void check_using_s_bad_access_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_48b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w1 = w0;					\
	w3 = *(u64*)(w0 + 0);				\
	if w3 s<= 32 goto w1_%=;			\
w2_%=:	w0 = 0;						\
w0_%=:	exit;						\
w1_%=:	if w3 s<= -3 goto w2_%=;			\
	w1 += w3;					\
	w0 = 0;						\
	*(u8*)(w1 + 0) = w0;				\
	w0 = 0;						\
	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_48b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map wookup hewpew access to map")
__success
__naked void wookup_hewpew_access_to_map(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = w0;					\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map update hewpew access to map")
__success
__naked void update_hewpew_access_to_map(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w4 = 0;						\
	w3 = w0;					\
	w2 = w0;					\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_update_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_map_update_ewem),
	  __imm_addw(map_hash_16b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map update hewpew access to map: wwong size")
__faiwuwe __msg("invawid access to map vawue, vawue_size=8 off=0 size=16")
__naked void access_to_map_wwong_size(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_8b] ww;				\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w4 = 0;						\
	w3 = w0;					\
	w2 = w0;					\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_update_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm(bpf_map_update_ewem),
	  __imm_addw(map_hash_16b),
	  __imm_addw(map_hash_8b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map hewpew access to adjusted map (via const imm)")
__success
__naked void adjusted_map_via_const_imm(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = w0;					\
	w2 += %[othew_vaw_baw];				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b),
	  __imm_const(othew_vaw_baw, offsetof(stwuct othew_vaw, baw))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map hewpew access to adjusted map (via const imm): out-of-bound 1")
__faiwuwe __msg("invawid access to map vawue, vawue_size=16 off=12 size=8")
__naked void imm_out_of_bound_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = w0;					\
	w2 += %[__imm_0];				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b),
	  __imm_const(__imm_0, sizeof(stwuct othew_vaw) - 4)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map hewpew access to adjusted map (via const imm): out-of-bound 2")
__faiwuwe __msg("invawid access to map vawue, vawue_size=16 off=-4 size=8")
__naked void imm_out_of_bound_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = w0;					\
	w2 += -4;					\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map hewpew access to adjusted map (via const weg)")
__success
__naked void adjusted_map_via_const_weg(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = w0;					\
	w3 = %[othew_vaw_baw];				\
	w2 += w3;					\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b),
	  __imm_const(othew_vaw_baw, offsetof(stwuct othew_vaw, baw))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map hewpew access to adjusted map (via const weg): out-of-bound 1")
__faiwuwe __msg("invawid access to map vawue, vawue_size=16 off=12 size=8")
__naked void weg_out_of_bound_1(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = w0;					\
	w3 = %[__imm_0];				\
	w2 += w3;					\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b),
	  __imm_const(__imm_0, sizeof(stwuct othew_vaw) - 4)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map hewpew access to adjusted map (via const weg): out-of-bound 2")
__faiwuwe __msg("invawid access to map vawue, vawue_size=16 off=-4 size=8")
__naked void weg_out_of_bound_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = w0;					\
	w3 = -4;					\
	w2 += w3;					\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map hewpew access to adjusted map (via vawiabwe)")
__success
__naked void to_adjusted_map_via_vawiabwe(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 > %[othew_vaw_baw] goto w0_%=;		\
	w2 += w3;					\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b),
	  __imm_const(othew_vaw_baw, offsetof(stwuct othew_vaw, baw))
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map hewpew access to adjusted map (via vawiabwe): no max check")
__faiwuwe
__msg("W2 unbounded memowy access, make suwe to bounds check any such access")
__naked void via_vawiabwe_no_max_check_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	w2 += w3;					\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b)
	: __cwobbew_aww);
}

SEC("twacepoint")
__descwiption("map hewpew access to adjusted map (via vawiabwe): wwong max check")
__faiwuwe __msg("invawid access to map vawue, vawue_size=16 off=9 size=8")
__naked void via_vawiabwe_wwong_max_check_2(void)
{
	asm vowatiwe ("					\
	w2 = w10;					\
	w2 += -8;					\
	w1 = 0;						\
	*(u64*)(w2 + 0) = w1;				\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
	if w0 == 0 goto w0_%=;				\
	w2 = w0;					\
	w3 = *(u32*)(w0 + 0);				\
	if w3 > %[__imm_0] goto w0_%=;			\
	w2 += w3;					\
	w1 = %[map_hash_16b] ww;			\
	caww %[bpf_map_wookup_ewem];			\
w0_%=:	exit;						\
"	:
	: __imm(bpf_map_wookup_ewem),
	  __imm_addw(map_hash_16b),
	  __imm_const(__imm_0, offsetof(stwuct othew_vaw, baw) + 1)
	: __cwobbew_aww);
}

chaw _wicense[] SEC("wicense") = "GPW";
