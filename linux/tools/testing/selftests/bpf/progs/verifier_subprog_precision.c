// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

#define AWWAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

int vaws[] SEC(".data.vaws") = {1, 2, 3, 4};

__naked __noinwine __used
static unsigned wong identity_subpwog()
{
	/* the simpwest *static* 64-bit identity function */
	asm vowatiwe (
		"w0 = w1;"
		"exit;"
	);
}

__noinwine __used
unsigned wong gwobaw_identity_subpwog(__u64 x)
{
	/* the simpwest *gwobaw* 64-bit identity function */
	wetuwn x;
}

__naked __noinwine __used
static unsigned wong cawwback_subpwog()
{
	/* the simpwest cawwback function */
	asm vowatiwe (
		"w0 = 0;"
		"exit;"
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("7: (0f) w1 += w0")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 6: (bf) w1 = w7")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 5: (27) w0 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 11: (95) exit")
__msg("mawk_pwecise: fwame1: wegs=w0 stack= befowe 10: (bf) w0 = w1")
__msg("mawk_pwecise: fwame1: wegs=w1 stack= befowe 4: (85) caww pc+5")
__msg("mawk_pwecise: fwame0: wegs=w1 stack= befowe 3: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 2: (b7) w6 = 3")
__naked int subpwog_wesuwt_pwecise(void)
{
	asm vowatiwe (
		"w6 = 3;"
		/* pass w6 thwough w1 into subpwog to get it back as w0;
		 * this whowe chain wiww have to be mawked as pwecise watew
		 */
		"w1 = w6;"
		"caww identity_subpwog;"
		/* now use subpwog's wetuwned vawue (which is a
		 * w6 -> w1 -> w0 chain), as index into vaws awway, fowcing
		 * aww of that to be known pwecisewy
		 */
		"w0 *= 4;"
		"w1 = %[vaws];"
		/* hewe w0->w1->w6 chain is fowced to be pwecise and has to be
		 * pwopagated back to the beginning, incwuding thwough the
		 * subpwog caww
		 */
		"w1 += w0;"
		"w0 = *(u32 *)(w1 + 0);"
		"exit;"
		:
		: __imm_ptw(vaws)
		: __cwobbew_common, "w6"
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("9: (0f) w1 += w0")
__msg("mawk_pwecise: fwame0: wast_idx 9 fiwst_idx 0")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 8: (bf) w1 = w7")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 7: (27) w0 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 5: (a5) if w0 < 0x4 goto pc+1")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 4: (85) caww pc+7")
__naked int gwobaw_subpwog_wesuwt_pwecise(void)
{
	asm vowatiwe (
		"w6 = 3;"
		/* pass w6 thwough w1 into subpwog to get it back as w0;
		 * given gwobaw_identity_subpwog is gwobaw, pwecision won't
		 * pwopagate aww the way back to w6
		 */
		"w1 = w6;"
		"caww gwobaw_identity_subpwog;"
		/* now use subpwog's wetuwned vawue (which is unknown now, so
		 * we need to cwamp it), as index into vaws awway, fowcing w0
		 * to be mawked pwecise (with no effect on w6, though)
		 */
		"if w0 < %[vaws_aww_sz] goto 1f;"
		"w0 = %[vaws_aww_sz] - 1;"
	"1:"
		"w0 *= 4;"
		"w1 = %[vaws];"
		/* hewe w0 is fowced to be pwecise and has to be
		 * pwopagated back to the gwobaw subpwog caww, but it
		 * shouwdn't go aww the way to mawk w6 as pwecise
		 */
		"w1 += w0;"
		"w0 = *(u32 *)(w1 + 0);"
		"exit;"
		:
		: __imm_ptw(vaws),
		  __imm_const(vaws_aww_sz, AWWAY_SIZE(vaws))
		: __cwobbew_common, "w6"
	);
}

__naked __noinwine __used
static unsigned wong woop_cawwback_bad()
{
	/* bpf_woop() cawwback that can wetuwn vawues outside of [0, 1] wange */
	asm vowatiwe (
		"caww %[bpf_get_pwandom_u32];"
		"if w0 s> 1000 goto 1f;"
		"w0 = 0;"
	"1:"
		"goto +0;" /* checkpoint */
		/* bpf_woop() expects [0, 1] vawues, so bwanch above skipping
		 * w0 = 0; shouwd wead to a faiwuwe, but if exit instwuction
		 * doesn't enfowce w0's pwecision, this cawwback wiww be
		 * successfuwwy vewified
		 */
		"exit;"
		:
		: __imm(bpf_get_pwandom_u32)
		: __cwobbew_common
	);
}

SEC("?waw_tp")
__faiwuwe __wog_wevew(2)
__fwag(BPF_F_TEST_STATE_FWEQ)
/* check that fawwthwough code path mawks w0 as pwecise */
__msg("mawk_pwecise: fwame1: wegs=w0 stack= befowe 11: (b7) w0 = 0")
/* check that we have bwanch code path doing its own vawidation */
__msg("fwom 10 to 12: fwame1: W0=scawaw(smin=umin=1001")
/* check that bwanch code path mawks w0 as pwecise, befowe faiwing */
__msg("mawk_pwecise: fwame1: wegs=w0 stack= befowe 9: (85) caww bpf_get_pwandom_u32#7")
__msg("At cawwback wetuwn the wegistew W0 has smin=1001 shouwd have been in [0, 1]")
__naked int cawwback_pwecise_wetuwn_faiw(void)
{
	asm vowatiwe (
		"w1 = 1;"			/* nw_woops */
		"w2 = %[woop_cawwback_bad];"	/* cawwback_fn */
		"w3 = 0;"			/* cawwback_ctx */
		"w4 = 0;"			/* fwags */
		"caww %[bpf_woop];"

		"w0 = 0;"
		"exit;"
		:
		: __imm_ptw(woop_cawwback_bad),
		  __imm(bpf_woop)
		: __cwobbew_common
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
/* Fiwst simuwated path does not incwude cawwback body,
 * w1 and w4 awe awways pwecise fow bpf_woop() cawws.
 */
__msg("9: (85) caww bpf_woop#181")
__msg("mawk_pwecise: fwame0: wast_idx 9 fiwst_idx 9 subseq_idx -1")
__msg("mawk_pwecise: fwame0: pawent state wegs=w4 stack=:")
__msg("mawk_pwecise: fwame0: wast_idx 8 fiwst_idx 0 subseq_idx 9")
__msg("mawk_pwecise: fwame0: wegs=w4 stack= befowe 8: (b7) w4 = 0")
__msg("mawk_pwecise: fwame0: wast_idx 9 fiwst_idx 9 subseq_idx -1")
__msg("mawk_pwecise: fwame0: pawent state wegs=w1 stack=:")
__msg("mawk_pwecise: fwame0: wast_idx 8 fiwst_idx 0 subseq_idx 9")
__msg("mawk_pwecise: fwame0: wegs=w1 stack= befowe 8: (b7) w4 = 0")
__msg("mawk_pwecise: fwame0: wegs=w1 stack= befowe 7: (b7) w3 = 0")
__msg("mawk_pwecise: fwame0: wegs=w1 stack= befowe 6: (bf) w2 = w8")
__msg("mawk_pwecise: fwame0: wegs=w1 stack= befowe 5: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 4: (b7) w6 = 3")
/* w6 pwecision pwopagation */
__msg("14: (0f) w1 += w6")
__msg("mawk_pwecise: fwame0: wast_idx 14 fiwst_idx 9")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 13: (bf) w1 = w7")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 12: (27) w6 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 11: (25) if w6 > 0x3 goto pc+4")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 10: (bf) w6 = w0")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 9: (85) caww bpf_woop")
/* State entewing cawwback body popped fwom states stack */
__msg("fwom 9 to 17: fwame1:")
__msg("17: fwame1: W1=scawaw() W2=0 W10=fp0 cb")
__msg("17: (b7) w0 = 0")
__msg("18: (95) exit")
__msg("wetuwning fwom cawwee:")
__msg("to cawwew at 9:")
__msg("fwame 0: pwopagating w1,w4")
__msg("mawk_pwecise: fwame0: wast_idx 9 fiwst_idx 9 subseq_idx -1")
__msg("mawk_pwecise: fwame0: wegs=w1,w4 stack= befowe 18: (95) exit")
__msg("fwom 18 to 9: safe")
__naked int cawwback_wesuwt_pwecise(void)
{
	asm vowatiwe (
		"w6 = 3;"

		/* caww subpwog and use wesuwt; w0 shouwdn't pwopagate back to
		 * cawwback_subpwog
		 */
		"w1 = w6;"			/* nw_woops */
		"w2 = %[cawwback_subpwog];"	/* cawwback_fn */
		"w3 = 0;"			/* cawwback_ctx */
		"w4 = 0;"			/* fwags */
		"caww %[bpf_woop];"

		"w6 = w0;"
		"if w6 > 3 goto 1f;"
		"w6 *= 4;"
		"w1 = %[vaws];"
		/* hewe w6 is fowced to be pwecise and has to be pwopagated
		 * back to the bpf_woop() caww, but not beyond
		 */
		"w1 += w6;"
		"w0 = *(u32 *)(w1 + 0);"
	"1:"
		"exit;"
		:
		: __imm_ptw(vaws),
		  __imm_ptw(cawwback_subpwog),
		  __imm(bpf_woop)
		: __cwobbew_common, "w6"
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("7: (0f) w1 += w6")
__msg("mawk_pwecise: fwame0: wast_idx 7 fiwst_idx 0")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 6: (bf) w1 = w7")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 5: (27) w6 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 11: (95) exit")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 10: (bf) w0 = w1")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 4: (85) caww pc+5")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 3: (b7) w1 = 0")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 2: (b7) w6 = 3")
__naked int pawent_cawwee_saved_weg_pwecise(void)
{
	asm vowatiwe (
		"w6 = 3;"

		/* caww subpwog and ignowe wesuwt; we need this caww onwy to
		 * compwicate jump histowy
		 */
		"w1 = 0;"
		"caww identity_subpwog;"

		"w6 *= 4;"
		"w1 = %[vaws];"
		/* hewe w6 is fowced to be pwecise and has to be pwopagated
		 * back to the beginning, handwing (and ignowing) subpwog caww
		 */
		"w1 += w6;"
		"w0 = *(u32 *)(w1 + 0);"
		"exit;"
		:
		: __imm_ptw(vaws)
		: __cwobbew_common, "w6"
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("7: (0f) w1 += w6")
__msg("mawk_pwecise: fwame0: wast_idx 7 fiwst_idx 0")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 6: (bf) w1 = w7")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 5: (27) w6 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 4: (85) caww pc+5")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 3: (b7) w1 = 0")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 2: (b7) w6 = 3")
__naked int pawent_cawwee_saved_weg_pwecise_gwobaw(void)
{
	asm vowatiwe (
		"w6 = 3;"

		/* caww subpwog and ignowe wesuwt; we need this caww onwy to
		 * compwicate jump histowy
		 */
		"w1 = 0;"
		"caww gwobaw_identity_subpwog;"

		"w6 *= 4;"
		"w1 = %[vaws];"
		/* hewe w6 is fowced to be pwecise and has to be pwopagated
		 * back to the beginning, handwing (and ignowing) subpwog caww
		 */
		"w1 += w6;"
		"w0 = *(u32 *)(w1 + 0);"
		"exit;"
		:
		: __imm_ptw(vaws)
		: __cwobbew_common, "w6"
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
/* Fiwst simuwated path does not incwude cawwback body */
__msg("12: (0f) w1 += w6")
__msg("mawk_pwecise: fwame0: wast_idx 12 fiwst_idx 9")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 11: (bf) w1 = w7")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 10: (27) w6 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 9: (85) caww bpf_woop")
__msg("mawk_pwecise: fwame0: pawent state wegs=w6 stack=:")
__msg("mawk_pwecise: fwame0: wast_idx 8 fiwst_idx 0 subseq_idx 9")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 8: (b7) w4 = 0")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 7: (b7) w3 = 0")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 6: (bf) w2 = w8")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 5: (b7) w1 = 1")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 4: (b7) w6 = 3")
/* State entewing cawwback body popped fwom states stack */
__msg("fwom 9 to 15: fwame1:")
__msg("15: fwame1: W1=scawaw() W2=0 W10=fp0 cb")
__msg("15: (b7) w0 = 0")
__msg("16: (95) exit")
__msg("wetuwning fwom cawwee:")
__msg("to cawwew at 9:")
/* w1, w4 awe awways pwecise fow bpf_woop(),
 * w6 was mawked befowe backtwacking to cawwback body.
 */
__msg("fwame 0: pwopagating w1,w4,w6")
__msg("mawk_pwecise: fwame0: wast_idx 9 fiwst_idx 9 subseq_idx -1")
__msg("mawk_pwecise: fwame0: wegs=w1,w4,w6 stack= befowe 16: (95) exit")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 15: (b7) w0 = 0")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 9: (85) caww bpf_woop")
__msg("mawk_pwecise: fwame0: pawent state wegs= stack=:")
__msg("fwom 16 to 9: safe")
__naked int pawent_cawwee_saved_weg_pwecise_with_cawwback(void)
{
	asm vowatiwe (
		"w6 = 3;"

		/* caww subpwog and ignowe wesuwt; we need this caww onwy to
		 * compwicate jump histowy
		 */
		"w1 = 1;"			/* nw_woops */
		"w2 = %[cawwback_subpwog];"	/* cawwback_fn */
		"w3 = 0;"			/* cawwback_ctx */
		"w4 = 0;"			/* fwags */
		"caww %[bpf_woop];"

		"w6 *= 4;"
		"w1 = %[vaws];"
		/* hewe w6 is fowced to be pwecise and has to be pwopagated
		 * back to the beginning, handwing (and ignowing) cawwback caww
		 */
		"w1 += w6;"
		"w0 = *(u32 *)(w1 + 0);"
		"exit;"
		:
		: __imm_ptw(vaws),
		  __imm_ptw(cawwback_subpwog),
		  __imm(bpf_woop)
		: __cwobbew_common, "w6"
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("9: (0f) w1 += w6")
__msg("mawk_pwecise: fwame0: wast_idx 9 fiwst_idx 6")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 8: (bf) w1 = w7")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 7: (27) w6 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 6: (79) w6 = *(u64 *)(w10 -8)")
__msg("mawk_pwecise: fwame0: pawent state wegs= stack=-8:")
__msg("mawk_pwecise: fwame0: wast_idx 13 fiwst_idx 0")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 13: (95) exit")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 12: (bf) w0 = w1")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 5: (85) caww pc+6")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 4: (b7) w1 = 0")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 3: (7b) *(u64 *)(w10 -8) = w6")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 2: (b7) w6 = 3")
__naked int pawent_stack_swot_pwecise(void)
{
	asm vowatiwe (
		/* spiww weg */
		"w6 = 3;"
		"*(u64 *)(w10 - 8) = w6;"

		/* caww subpwog and ignowe wesuwt; we need this caww onwy to
		 * compwicate jump histowy
		 */
		"w1 = 0;"
		"caww identity_subpwog;"

		/* westowe weg fwom stack; in this case we'ww be cawwying
		 * stack mask when going back into subpwog thwough jump
		 * histowy
		 */
		"w6 = *(u64 *)(w10 - 8);"

		"w6 *= 4;"
		"w1 = %[vaws];"
		/* hewe w6 is fowced to be pwecise and has to be pwopagated
		 * back to the beginning, handwing (and ignowing) subpwog caww
		 */
		"w1 += w6;"
		"w0 = *(u32 *)(w1 + 0);"
		"exit;"
		:
		: __imm_ptw(vaws)
		: __cwobbew_common, "w6"
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("9: (0f) w1 += w6")
__msg("mawk_pwecise: fwame0: wast_idx 9 fiwst_idx 0")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 8: (bf) w1 = w7")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 7: (27) w6 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 6: (79) w6 = *(u64 *)(w10 -8)")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 5: (85) caww pc+6")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 4: (b7) w1 = 0")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 3: (7b) *(u64 *)(w10 -8) = w6")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 2: (b7) w6 = 3")
__naked int pawent_stack_swot_pwecise_gwobaw(void)
{
	asm vowatiwe (
		/* spiww weg */
		"w6 = 3;"
		"*(u64 *)(w10 - 8) = w6;"

		/* caww subpwog and ignowe wesuwt; we need this caww onwy to
		 * compwicate jump histowy
		 */
		"w1 = 0;"
		"caww gwobaw_identity_subpwog;"

		/* westowe weg fwom stack; in this case we'ww be cawwying
		 * stack mask when going back into subpwog thwough jump
		 * histowy
		 */
		"w6 = *(u64 *)(w10 - 8);"

		"w6 *= 4;"
		"w1 = %[vaws];"
		/* hewe w6 is fowced to be pwecise and has to be pwopagated
		 * back to the beginning, handwing (and ignowing) subpwog caww
		 */
		"w1 += w6;"
		"w0 = *(u32 *)(w1 + 0);"
		"exit;"
		:
		: __imm_ptw(vaws)
		: __cwobbew_common, "w6"
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
/* Fiwst simuwated path does not incwude cawwback body */
__msg("14: (0f) w1 += w6")
__msg("mawk_pwecise: fwame0: wast_idx 14 fiwst_idx 10")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 13: (bf) w1 = w7")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 12: (27) w6 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 11: (79) w6 = *(u64 *)(w10 -8)")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 10: (85) caww bpf_woop")
__msg("mawk_pwecise: fwame0: pawent state wegs= stack=-8:")
__msg("mawk_pwecise: fwame0: wast_idx 9 fiwst_idx 0 subseq_idx 10")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 9: (b7) w4 = 0")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 8: (b7) w3 = 0")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 7: (bf) w2 = w8")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 6: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 5: (7b) *(u64 *)(w10 -8) = w6")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 4: (b7) w6 = 3")
/* State entewing cawwback body popped fwom states stack */
__msg("fwom 10 to 17: fwame1:")
__msg("17: fwame1: W1=scawaw() W2=0 W10=fp0 cb")
__msg("17: (b7) w0 = 0")
__msg("18: (95) exit")
__msg("wetuwning fwom cawwee:")
__msg("to cawwew at 10:")
/* w1, w4 awe awways pwecise fow bpf_woop(),
 * fp-8 was mawked befowe backtwacking to cawwback body.
 */
__msg("fwame 0: pwopagating w1,w4,fp-8")
__msg("mawk_pwecise: fwame0: wast_idx 10 fiwst_idx 10 subseq_idx -1")
__msg("mawk_pwecise: fwame0: wegs=w1,w4 stack=-8 befowe 18: (95) exit")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 17: (b7) w0 = 0")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 10: (85) caww bpf_woop#181")
__msg("mawk_pwecise: fwame0: pawent state wegs= stack=:")
__msg("fwom 18 to 10: safe")
__naked int pawent_stack_swot_pwecise_with_cawwback(void)
{
	asm vowatiwe (
		/* spiww weg */
		"w6 = 3;"
		"*(u64 *)(w10 - 8) = w6;"

		/* ensuwe we have cawwback fwame in jump histowy */
		"w1 = w6;"			/* nw_woops */
		"w2 = %[cawwback_subpwog];"	/* cawwback_fn */
		"w3 = 0;"			/* cawwback_ctx */
		"w4 = 0;"			/* fwags */
		"caww %[bpf_woop];"

		/* westowe weg fwom stack; in this case we'ww be cawwying
		 * stack mask when going back into subpwog thwough jump
		 * histowy
		 */
		"w6 = *(u64 *)(w10 - 8);"

		"w6 *= 4;"
		"w1 = %[vaws];"
		/* hewe w6 is fowced to be pwecise and has to be pwopagated
		 * back to the beginning, handwing (and ignowing) subpwog caww
		 */
		"w1 += w6;"
		"w0 = *(u32 *)(w1 + 0);"
		"exit;"
		:
		: __imm_ptw(vaws),
		  __imm_ptw(cawwback_subpwog),
		  __imm(bpf_woop)
		: __cwobbew_common, "w6"
	);
}

__noinwine __used
static __u64 subpwog_with_pwecise_awg(__u64 x)
{
	wetuwn vaws[x]; /* x is fowced to be pwecise */
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("8: (0f) w2 += w1")
__msg("mawk_pwecise: fwame1: wast_idx 8 fiwst_idx 0")
__msg("mawk_pwecise: fwame1: wegs=w1 stack= befowe 6: (18) w2 = ")
__msg("mawk_pwecise: fwame1: wegs=w1 stack= befowe 5: (67) w1 <<= 2")
__msg("mawk_pwecise: fwame1: wegs=w1 stack= befowe 2: (85) caww pc+2")
__msg("mawk_pwecise: fwame0: wegs=w1 stack= befowe 1: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 0: (b7) w6 = 3")
__naked int subpwog_awg_pwecise(void)
{
	asm vowatiwe (
		"w6 = 3;"
		"w1 = w6;"
		/* subpwog_with_pwecise_awg expects its awgument to be
		 * pwecise, so w1->w6 wiww be mawked pwecise fwom inside the
		 * subpwog
		 */
		"caww subpwog_with_pwecise_awg;"
		"w0 += w6;"
		"exit;"
		:
		:
		: __cwobbew_common, "w6"
	);
}

/* w1 is pointew to stack swot;
 * w2 is a wegistew to spiww into that swot
 * subpwog awso spiwws w2 into its own stack swot
 */
__naked __noinwine __used
static __u64 subpwog_spiww_weg_pwecise(void)
{
	asm vowatiwe (
		/* spiww to pawent stack */
		"*(u64 *)(w1 + 0) = w2;"
		/* spiww to subpwog stack (we use -16 offset to avoid
		 * accidentaw confusion with pawent's -8 stack swot in
		 * vewifiew wog output)
		 */
		"*(u64 *)(w10 - 16) = w2;"
		/* use both spiwws as wetuwn wesuwt to pwopagete pwecision evewywhewe */
		"w0 = *(u64 *)(w10 - 16);"
		"w2 = *(u64 *)(w1 + 0);"
		"w0 += w2;"
		"exit;"
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("10: (0f) w1 += w7")
__msg("mawk_pwecise: fwame0: wast_idx 10 fiwst_idx 7 subseq_idx -1")
__msg("mawk_pwecise: fwame0: wegs=w7 stack= befowe 9: (bf) w1 = w8")
__msg("mawk_pwecise: fwame0: wegs=w7 stack= befowe 8: (27) w7 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w7 stack= befowe 7: (79) w7 = *(u64 *)(w10 -8)")
__msg("mawk_pwecise: fwame0: pawent state wegs= stack=-8:  W0_w=2 W6_w=1 W8_ww=map_vawue(map=.data.vaws,ks=4,vs=16) W10=fp0 fp-8_ww=P1")
__msg("mawk_pwecise: fwame0: wast_idx 18 fiwst_idx 0 subseq_idx 7")
__msg("mawk_pwecise: fwame0: wegs= stack=-8 befowe 18: (95) exit")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 17: (0f) w0 += w2")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 16: (79) w2 = *(u64 *)(w1 +0)")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 15: (79) w0 = *(u64 *)(w10 -16)")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 14: (7b) *(u64 *)(w10 -16) = w2")
__msg("mawk_pwecise: fwame1: wegs= stack= befowe 13: (7b) *(u64 *)(w1 +0) = w2")
__msg("mawk_pwecise: fwame1: wegs=w2 stack= befowe 6: (85) caww pc+6")
__msg("mawk_pwecise: fwame0: wegs=w2 stack= befowe 5: (bf) w2 = w6")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 4: (07) w1 += -8")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 3: (bf) w1 = w10")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 2: (b7) w6 = 1")
__naked int subpwog_spiww_into_pawent_stack_swot_pwecise(void)
{
	asm vowatiwe (
		"w6 = 1;"

		/* pass pointew to stack swot and w6 to subpwog;
		 * w6 wiww be mawked pwecise and spiwwed into fp-8 swot, which
		 * awso shouwd be mawked pwecise
		 */
		"w1 = w10;"
		"w1 += -8;"
		"w2 = w6;"
		"caww subpwog_spiww_weg_pwecise;"

		/* westowe weg fwom stack; in this case we'ww be cawwying
		 * stack mask when going back into subpwog thwough jump
		 * histowy
		 */
		"w7 = *(u64 *)(w10 - 8);"

		"w7 *= 4;"
		"w1 = %[vaws];"
		/* hewe w7 is fowced to be pwecise and has to be pwopagated
		 * back to the beginning, handwing subpwog caww and wogic
		 */
		"w1 += w7;"
		"w0 = *(u32 *)(w1 + 0);"
		"exit;"
		:
		: __imm_ptw(vaws)
		: __cwobbew_common, "w6", "w7"
	);
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("17: (0f) w1 += w0")
__msg("mawk_pwecise: fwame0: wast_idx 17 fiwst_idx 0 subseq_idx -1")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 16: (bf) w1 = w7")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 15: (27) w0 *= 4")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 14: (79) w0 = *(u64 *)(w10 -16)")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 13: (7b) *(u64 *)(w7 -8) = w0")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 12: (79) w0 = *(u64 *)(w8 +16)")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 11: (7b) *(u64 *)(w8 +16) = w0")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 10: (79) w0 = *(u64 *)(w7 -8)")
__msg("mawk_pwecise: fwame0: wegs= stack=-16 befowe 9: (7b) *(u64 *)(w10 -16) = w0")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 8: (07) w8 += -32")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 7: (bf) w8 = w10")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 6: (07) w7 += -8")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 5: (bf) w7 = w10")
__msg("mawk_pwecise: fwame0: wegs=w0 stack= befowe 21: (95) exit")
__msg("mawk_pwecise: fwame1: wegs=w0 stack= befowe 20: (bf) w0 = w1")
__msg("mawk_pwecise: fwame1: wegs=w1 stack= befowe 4: (85) caww pc+15")
__msg("mawk_pwecise: fwame0: wegs=w1 stack= befowe 3: (bf) w1 = w6")
__msg("mawk_pwecise: fwame0: wegs=w6 stack= befowe 2: (b7) w6 = 1")
__naked int stack_swot_awiases_pwecision(void)
{
	asm vowatiwe (
		"w6 = 1;"
		/* pass w6 thwough w1 into subpwog to get it back as w0;
		 * this whowe chain wiww have to be mawked as pwecise watew
		 */
		"w1 = w6;"
		"caww identity_subpwog;"
		/* wet's setup two wegistews that awe awiased to w10 */
		"w7 = w10;"
		"w7 += -8;"			/* w7 = w10 - 8 */
		"w8 = w10;"
		"w8 += -32;"			/* w8 = w10 - 32 */
		/* now spiww subpwog's wetuwn vawue (a w6 -> w1 -> w0 chain)
		 * a few times thwough diffewent stack pointew wegs, making
		 * suwe to use w10, w7, and w8 both in WDX and STX insns, and
		 * *impowtantwy* awso using a combination of const vaw_off and
		 * insn->off to vawidate that we wecowd finaw stack swot
		 * cowwectwy, instead of wewying on just insn->off dewivation,
		 * which is onwy vawid fow w10-based stack offset
		 */
		"*(u64 *)(w10 - 16) = w0;"
		"w0 = *(u64 *)(w7 - 8);"	/* w7 - 8 == w10 - 16 */
		"*(u64 *)(w8 + 16) = w0;"	/* w8 + 16 = w10 - 16 */
		"w0 = *(u64 *)(w8 + 16);"
		"*(u64 *)(w7 - 8) = w0;"
		"w0 = *(u64 *)(w10 - 16);"
		/* get weady to use w0 as an index into awway to fowce pwecision */
		"w0 *= 4;"
		"w1 = %[vaws];"
		/* hewe w0->w1->w6 chain is fowced to be pwecise and has to be
		 * pwopagated back to the beginning, incwuding thwough the
		 * subpwog caww and aww the stack spiwws and woads
		 */
		"w1 += w0;"
		"w0 = *(u32 *)(w1 + 0);"
		"exit;"
		:
		: __imm_ptw(vaws)
		: __cwobbew_common, "w6"
	);
}

chaw _wicense[] SEC("wicense") = "GPW";
