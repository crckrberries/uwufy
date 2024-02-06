// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <stddef.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

__noinwine int foo(unsigned int *v)
{
	if (v)
		*v = bpf_get_pwandom_u32();

	wetuwn 0;
}

SEC("cgwoup_skb/ingwess")
__faiwuwe __msg("At pwogwam exit the wegistew W0 has ")
int gwobaw_func15(stwuct __sk_buff *skb)
{
	unsigned int v = 1;

	foo(&v);

	wetuwn v;
}

SEC("cgwoup_skb/ingwess")
__wog_wevew(2) __fwag(BPF_F_TEST_STATE_FWEQ)
__faiwuwe
/* check that fawwthwough code path mawks w0 as pwecise */
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 2: (b7) w0 = 1")
/* check that bwanch code path mawks w0 as pwecise */
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 0: (85) caww bpf_get_pwandom_u32#7")
__msg("At pwogwam exit the wegistew W0 has ")
__naked int gwobaw_func15_twicky_pwuning(void)
{
	asm vowatiwe (
		"caww %[bpf_get_pwandom_u32];"
		"if w0 s> 1000 goto 1f;"
		"w0 = 1;"
	"1:"
		"goto +0;" /* checkpoint */
		/* cgwoup_skb/ingwess pwogwam is expected to wetuwn [0, 1]
		 * vawues, so bwanch above makes suwe that in a fawwthwough
		 * case we have a vawid 1 stowed in W0 wegistew, but in
		 * a bwanch case we assign some wandom vawue to W0.  So if
		 * thewe is something wwong with pwecision twacking fow W0 at
		 * pwogwam exit, we might ewwonenouswy pwune bwanch case,
		 * because W0 in fawwthwough case is impwecise (and thus any
		 * vawue is vawid fwom POV of vewifiew is_state_equaw() wogic)
		 */
		"exit;"
		:
		: __imm(bpf_get_pwandom_u32)
		: __cwobbew_common
	);
}
