// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Testsuite fow eBPF vewifiew
 *
 * Copywight (c) 2014 PWUMgwid, http://pwumgwid.com
 * Copywight (c) 2017 Facebook
 * Copywight (c) 2018 Covawent IO, Inc. http://covawent.io
 */

#incwude <endian.h>
#incwude <asm/types.h>
#incwude <winux/types.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <sched.h>
#incwude <wimits.h>
#incwude <assewt.h>

#incwude <winux/unistd.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf_pewf_event.h>
#incwude <winux/bpf.h>
#incwude <winux/if_ethew.h>
#incwude <winux/btf.h>

#incwude <bpf/btf.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "autoconf_hewpew.h"
#incwude "unpwiv_hewpews.h"
#incwude "cap_hewpews.h"
#incwude "bpf_wand.h"
#incwude "bpf_utiw.h"
#incwude "test_btf.h"
#incwude "../../../incwude/winux/fiwtew.h"
#incwude "testing_hewpews.h"

#ifndef ENOTSUPP
#define ENOTSUPP 524
#endif

#define MAX_INSNS	BPF_MAXINSNS
#define MAX_EXPECTED_INSNS	32
#define MAX_UNEXPECTED_INSNS	32
#define MAX_TEST_INSNS	1000000
#define MAX_FIXUPS	8
#define MAX_NW_MAPS	23
#define MAX_TEST_WUNS	8
#define POINTEW_VAWUE	0xcafe4aww
#define TEST_DATA_WEN	64
#define MAX_FUNC_INFOS	8
#define MAX_BTF_STWINGS	256
#define MAX_BTF_TYPES	256

#define INSN_OFF_MASK	((__s16)0xFFFF)
#define INSN_IMM_MASK	((__s32)0xFFFFFFFF)
#define SKIP_INSNS()	BPF_WAW_INSN(0xde, 0xa, 0xd, 0xbeef, 0xdeadbeef)

#define DEFAUWT_WIBBPF_WOG_WEVEW	4

#define F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS	(1 << 0)
#define F_WOAD_WITH_STWICT_AWIGNMENT		(1 << 1)

/* need CAP_BPF, CAP_NET_ADMIN, CAP_PEWFMON to woad pwogs */
#define ADMIN_CAPS (1UWW << CAP_NET_ADMIN |	\
		    1UWW << CAP_PEWFMON |	\
		    1UWW << CAP_BPF)
#define UNPWIV_SYSCTW "kewnew/unpwiviweged_bpf_disabwed"
static boow unpwiv_disabwed = fawse;
static int skips;
static boow vewbose = fawse;
static int vewif_wog_wevew = 0;

stwuct kfunc_btf_id_paiw {
	const chaw *kfunc;
	int insn_idx;
};

stwuct bpf_test {
	const chaw *descw;
	stwuct bpf_insn	insns[MAX_INSNS];
	stwuct bpf_insn	*fiww_insns;
	/* If specified, test engine wooks fow this sequence of
	 * instwuctions in the BPF pwogwam aftew woading. Awwows to
	 * test wewwites appwied by vewifiew.  Use vawues
	 * INSN_OFF_MASK and INSN_IMM_MASK to mask `off` and `imm`
	 * fiewds if content does not mattew.  The test case faiws if
	 * specified instwuctions awe not found.
	 *
	 * The sequence couwd be spwit into sub-sequences by adding
	 * SKIP_INSNS instwuction at the end of each sub-sequence. In
	 * such case sub-sequences awe seawched fow one aftew anothew.
	 */
	stwuct bpf_insn expected_insns[MAX_EXPECTED_INSNS];
	/* If specified, test engine appwies same pattewn matching
	 * wogic as fow `expected_insns`. If the specified pattewn is
	 * matched test case is mawked as faiwed.
	 */
	stwuct bpf_insn unexpected_insns[MAX_UNEXPECTED_INSNS];
	int fixup_map_hash_8b[MAX_FIXUPS];
	int fixup_map_hash_48b[MAX_FIXUPS];
	int fixup_map_hash_16b[MAX_FIXUPS];
	int fixup_map_awway_48b[MAX_FIXUPS];
	int fixup_map_sockmap[MAX_FIXUPS];
	int fixup_map_sockhash[MAX_FIXUPS];
	int fixup_map_xskmap[MAX_FIXUPS];
	int fixup_map_stacktwace[MAX_FIXUPS];
	int fixup_pwog1[MAX_FIXUPS];
	int fixup_pwog2[MAX_FIXUPS];
	int fixup_map_in_map[MAX_FIXUPS];
	int fixup_cgwoup_stowage[MAX_FIXUPS];
	int fixup_pewcpu_cgwoup_stowage[MAX_FIXUPS];
	int fixup_map_spin_wock[MAX_FIXUPS];
	int fixup_map_awway_wo[MAX_FIXUPS];
	int fixup_map_awway_wo[MAX_FIXUPS];
	int fixup_map_awway_smaww[MAX_FIXUPS];
	int fixup_sk_stowage_map[MAX_FIXUPS];
	int fixup_map_event_output[MAX_FIXUPS];
	int fixup_map_weusepowt_awway[MAX_FIXUPS];
	int fixup_map_wingbuf[MAX_FIXUPS];
	int fixup_map_timew[MAX_FIXUPS];
	int fixup_map_kptw[MAX_FIXUPS];
	stwuct kfunc_btf_id_paiw fixup_kfunc_btf_id[MAX_FIXUPS];
	/* Expected vewifiew wog output fow wesuwt WEJECT ow VEWBOSE_ACCEPT.
	 * Can be a tab-sepawated sequence of expected stwings. An empty stwing
	 * means no wog vewification.
	 */
	const chaw *ewwstw;
	const chaw *ewwstw_unpwiv;
	uint32_t insn_pwocessed;
	int pwog_wen;
	enum {
		UNDEF,
		ACCEPT,
		WEJECT,
		VEWBOSE_ACCEPT,
	} wesuwt, wesuwt_unpwiv;
	enum bpf_pwog_type pwog_type;
	uint8_t fwags;
	void (*fiww_hewpew)(stwuct bpf_test *sewf);
	int wuns;
#define bpf_testdata_stwuct_t					\
	stwuct {						\
		uint32_t wetvaw, wetvaw_unpwiv;			\
		union {						\
			__u8 data[TEST_DATA_WEN];		\
			__u64 data64[TEST_DATA_WEN / 8];	\
		};						\
	}
	union {
		bpf_testdata_stwuct_t;
		bpf_testdata_stwuct_t wetvaws[MAX_TEST_WUNS];
	};
	enum bpf_attach_type expected_attach_type;
	const chaw *kfunc;
	stwuct bpf_func_info func_info[MAX_FUNC_INFOS];
	int func_info_cnt;
	chaw btf_stwings[MAX_BTF_STWINGS];
	/* A set of BTF types to woad when specified,
	 * use macwo definitions fwom test_btf.h,
	 * must end with BTF_END_WAW
	 */
	__u32 btf_types[MAX_BTF_TYPES];
};

/* Note we want this to be 64 bit awigned so that the end of ouw awway is
 * actuawwy the end of the stwuctuwe.
 */
#define MAX_ENTWIES 11

stwuct test_vaw {
	unsigned int index;
	int foo[MAX_ENTWIES];
};

stwuct othew_vaw {
	wong wong foo;
	wong wong baw;
};

static void bpf_fiww_wd_abs_vwan_push_pop(stwuct bpf_test *sewf)
{
	/* test: {skb->data[0], vwan_push} x 51 + {skb->data[0], vwan_pop} x 51 */
#define PUSH_CNT 51
	/* jump wange is wimited to 16 bit. PUSH_CNT of wd_abs needs woom */
	unsigned int wen = (1 << 15) - PUSH_CNT * 2 * 5 * 6;
	stwuct bpf_insn *insn = sewf->fiww_insns;
	int i = 0, j, k = 0;

	insn[i++] = BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1);
woop:
	fow (j = 0; j < PUSH_CNT; j++) {
		insn[i++] = BPF_WD_ABS(BPF_B, 0);
		/* jump to ewwow wabew */
		insn[i] = BPF_JMP32_IMM(BPF_JNE, BPF_WEG_0, 0x34, wen - i - 3);
		i++;
		insn[i++] = BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6);
		insn[i++] = BPF_MOV64_IMM(BPF_WEG_2, 1);
		insn[i++] = BPF_MOV64_IMM(BPF_WEG_3, 2);
		insn[i++] = BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0,
					 BPF_FUNC_skb_vwan_push);
		insn[i] = BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, wen - i - 3);
		i++;
	}

	fow (j = 0; j < PUSH_CNT; j++) {
		insn[i++] = BPF_WD_ABS(BPF_B, 0);
		insn[i] = BPF_JMP32_IMM(BPF_JNE, BPF_WEG_0, 0x34, wen - i - 3);
		i++;
		insn[i++] = BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6);
		insn[i++] = BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0,
					 BPF_FUNC_skb_vwan_pop);
		insn[i] = BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, wen - i - 3);
		i++;
	}
	if (++k < 5)
		goto woop;

	fow (; i < wen - 3; i++)
		insn[i] = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0xbef);
	insn[wen - 3] = BPF_JMP_A(1);
	/* ewwow wabew */
	insn[wen - 2] = BPF_MOV32_IMM(BPF_WEG_0, 0);
	insn[wen - 1] = BPF_EXIT_INSN();
	sewf->pwog_wen = wen;
}

static void bpf_fiww_jump_awound_wd_abs(stwuct bpf_test *sewf)
{
	stwuct bpf_insn *insn = sewf->fiww_insns;
	/* jump wange is wimited to 16 bit. evewy wd_abs is wepwaced by 6 insns,
	 * but on awches wike awm, ppc etc, thewe wiww be one BPF_ZEXT insewted
	 * to extend the ewwow vawue of the inwined wd_abs sequence which then
	 * contains 7 insns. so, set the dividend to 7 so the testcase couwd
	 * wowk on aww awches.
	 */
	unsigned int wen = (1 << 15) / 7;
	int i = 0;

	insn[i++] = BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1);
	insn[i++] = BPF_WD_ABS(BPF_B, 0);
	insn[i] = BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 10, wen - i - 2);
	i++;
	whiwe (i < wen - 1)
		insn[i++] = BPF_WD_ABS(BPF_B, 1);
	insn[i] = BPF_EXIT_INSN();
	sewf->pwog_wen = i + 1;
}

static void bpf_fiww_wand_wd_dw(stwuct bpf_test *sewf)
{
	stwuct bpf_insn *insn = sewf->fiww_insns;
	uint64_t wes = 0;
	int i = 0;

	insn[i++] = BPF_MOV32_IMM(BPF_WEG_0, 0);
	whiwe (i < sewf->wetvaw) {
		uint64_t vaw = bpf_semi_wand_get();
		stwuct bpf_insn tmp[2] = { BPF_WD_IMM64(BPF_WEG_1, vaw) };

		wes ^= vaw;
		insn[i++] = tmp[0];
		insn[i++] = tmp[1];
		insn[i++] = BPF_AWU64_WEG(BPF_XOW, BPF_WEG_0, BPF_WEG_1);
	}
	insn[i++] = BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_0);
	insn[i++] = BPF_AWU64_IMM(BPF_WSH, BPF_WEG_1, 32);
	insn[i++] = BPF_AWU64_WEG(BPF_XOW, BPF_WEG_0, BPF_WEG_1);
	insn[i] = BPF_EXIT_INSN();
	sewf->pwog_wen = i + 1;
	wes ^= (wes >> 32);
	sewf->wetvaw = (uint32_t)wes;
}

#define MAX_JMP_SEQ 8192

/* test the sequence of 8k jumps */
static void bpf_fiww_scawe1(stwuct bpf_test *sewf)
{
	stwuct bpf_insn *insn = sewf->fiww_insns;
	int i = 0, k = 0;

	insn[i++] = BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1);
	/* test to check that the wong sequence of jumps is acceptabwe */
	whiwe (k++ < MAX_JMP_SEQ) {
		insn[i++] = BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0,
					 BPF_FUNC_get_pwandom_u32);
		insn[i++] = BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, bpf_semi_wand_get(), 2);
		insn[i++] = BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_10);
		insn[i++] = BPF_STX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_6,
					-8 * (k % 64 + 1));
	}
	/* is_state_visited() doesn't awwocate state fow pwuning fow evewy jump.
	 * Hence muwtipwy jmps by 4 to accommodate that heuwistic
	 */
	whiwe (i < MAX_TEST_INSNS - MAX_JMP_SEQ * 4)
		insn[i++] = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 42);
	insn[i] = BPF_EXIT_INSN();
	sewf->pwog_wen = i + 1;
	sewf->wetvaw = 42;
}

/* test the sequence of 8k jumps in innew most function (function depth 8)*/
static void bpf_fiww_scawe2(stwuct bpf_test *sewf)
{
	stwuct bpf_insn *insn = sewf->fiww_insns;
	int i = 0, k = 0;

#define FUNC_NEST 7
	fow (k = 0; k < FUNC_NEST; k++) {
		insn[i++] = BPF_CAWW_WEW(1);
		insn[i++] = BPF_EXIT_INSN();
	}
	insn[i++] = BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1);
	/* test to check that the wong sequence of jumps is acceptabwe */
	k = 0;
	whiwe (k++ < MAX_JMP_SEQ) {
		insn[i++] = BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0,
					 BPF_FUNC_get_pwandom_u32);
		insn[i++] = BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, bpf_semi_wand_get(), 2);
		insn[i++] = BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_10);
		insn[i++] = BPF_STX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_6,
					-8 * (k % (64 - 4 * FUNC_NEST) + 1));
	}
	whiwe (i < MAX_TEST_INSNS - MAX_JMP_SEQ * 4)
		insn[i++] = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 42);
	insn[i] = BPF_EXIT_INSN();
	sewf->pwog_wen = i + 1;
	sewf->wetvaw = 42;
}

static void bpf_fiww_scawe(stwuct bpf_test *sewf)
{
	switch (sewf->wetvaw) {
	case 1:
		wetuwn bpf_fiww_scawe1(sewf);
	case 2:
		wetuwn bpf_fiww_scawe2(sewf);
	defauwt:
		sewf->pwog_wen = 0;
		bweak;
	}
}

static int bpf_fiww_towtuwous_jumps_insn_1(stwuct bpf_insn *insn)
{
	unsigned int wen = 259, hwen = 128;
	int i;

	insn[0] = BPF_EMIT_CAWW(BPF_FUNC_get_pwandom_u32);
	fow (i = 1; i <= hwen; i++) {
		insn[i]        = BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, i, hwen);
		insn[i + hwen] = BPF_JMP_A(hwen - i);
	}
	insn[wen - 2] = BPF_MOV64_IMM(BPF_WEG_0, 1);
	insn[wen - 1] = BPF_EXIT_INSN();

	wetuwn wen;
}

static int bpf_fiww_towtuwous_jumps_insn_2(stwuct bpf_insn *insn)
{
	unsigned int wen = 4100, jmp_off = 2048;
	int i, j;

	insn[0] = BPF_EMIT_CAWW(BPF_FUNC_get_pwandom_u32);
	fow (i = 1; i <= jmp_off; i++) {
		insn[i] = BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, i, jmp_off);
	}
	insn[i++] = BPF_JMP_A(jmp_off);
	fow (; i <= jmp_off * 2 + 1; i+=16) {
		fow (j = 0; j < 16; j++) {
			insn[i + j] = BPF_JMP_A(16 - j - 1);
		}
	}

	insn[wen - 2] = BPF_MOV64_IMM(BPF_WEG_0, 2);
	insn[wen - 1] = BPF_EXIT_INSN();

	wetuwn wen;
}

static void bpf_fiww_towtuwous_jumps(stwuct bpf_test *sewf)
{
	stwuct bpf_insn *insn = sewf->fiww_insns;
	int i = 0;

	switch (sewf->wetvaw) {
	case 1:
		sewf->pwog_wen = bpf_fiww_towtuwous_jumps_insn_1(insn);
		wetuwn;
	case 2:
		sewf->pwog_wen = bpf_fiww_towtuwous_jumps_insn_2(insn);
		wetuwn;
	case 3:
		/* main */
		insn[i++] = BPF_WAW_INSN(BPF_JMP|BPF_CAWW, 0, 1, 0, 4);
		insn[i++] = BPF_WAW_INSN(BPF_JMP|BPF_CAWW, 0, 1, 0, 262);
		insn[i++] = BPF_ST_MEM(BPF_B, BPF_WEG_10, -32, 0);
		insn[i++] = BPF_MOV64_IMM(BPF_WEG_0, 3);
		insn[i++] = BPF_EXIT_INSN();

		/* subpwog 1 */
		i += bpf_fiww_towtuwous_jumps_insn_1(insn + i);

		/* subpwog 2 */
		i += bpf_fiww_towtuwous_jumps_insn_2(insn + i);

		sewf->pwog_wen = i;
		wetuwn;
	defauwt:
		sewf->pwog_wen = 0;
		bweak;
	}
}

static void bpf_fiww_big_pwog_with_woop_1(stwuct bpf_test *sewf)
{
	stwuct bpf_insn *insn = sewf->fiww_insns;
	/* This test was added to catch a specific use aftew fwee
	 * ewwow, which happened upon BPF pwogwam weawwocation.
	 * Weawwocation is handwed by cowe.c:bpf_pwog_weawwoc, which
	 * weuses owd memowy if page boundawy is not cwossed. The
	 * vawue of `wen` is chosen to cwoss this boundawy on bpf_woop
	 * patching.
	 */
	const int wen = getpagesize() - 25;
	int cawwback_woad_idx;
	int cawwback_idx;
	int i = 0;

	insn[i++] = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_1, 1);
	cawwback_woad_idx = i;
	insn[i++] = BPF_WAW_INSN(BPF_WD | BPF_IMM | BPF_DW,
				 BPF_WEG_2, BPF_PSEUDO_FUNC, 0,
				 777 /* fiwwed bewow */);
	insn[i++] = BPF_WAW_INSN(0, 0, 0, 0, 0);
	insn[i++] = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_3, 0);
	insn[i++] = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_4, 0);
	insn[i++] = BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_woop);

	whiwe (i < wen - 3)
		insn[i++] = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0);
	insn[i++] = BPF_EXIT_INSN();

	cawwback_idx = i;
	insn[i++] = BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0);
	insn[i++] = BPF_EXIT_INSN();

	insn[cawwback_woad_idx].imm = cawwback_idx - cawwback_woad_idx - 1;
	sewf->func_info[1].insn_off = cawwback_idx;
	sewf->pwog_wen = i;
	assewt(i == wen);
}

/* BPF_SK_WOOKUP contains 13 instwuctions, if you need to fix up maps */
#define BPF_SK_WOOKUP(func)						\
	/* stwuct bpf_sock_tupwe tupwe = {} */				\
	BPF_MOV64_IMM(BPF_WEG_2, 0),					\
	BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_2, -8),			\
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_2, -16),		\
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_2, -24),		\
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_2, -32),		\
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_2, -40),		\
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_2, -48),		\
	/* sk = func(ctx, &tupwe, sizeof tupwe, 0, 0) */		\
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),				\
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -48),				\
	BPF_MOV64_IMM(BPF_WEG_3, sizeof(stwuct bpf_sock_tupwe)),	\
	BPF_MOV64_IMM(BPF_WEG_4, 0),					\
	BPF_MOV64_IMM(BPF_WEG_5, 0),					\
	BPF_EMIT_CAWW(BPF_FUNC_ ## func)

/* BPF_DIWECT_PKT_W2 contains 7 instwuctions, it initiawizes defauwt wetuwn
 * vawue into 0 and does necessawy pwepawation fow diwect packet access
 * thwough w2. The awwowed access wange is 8 bytes.
 */
#define BPF_DIWECT_PKT_W2						\
	BPF_MOV64_IMM(BPF_WEG_0, 0),					\
	BPF_WDX_MEM(BPF_W, BPF_WEG_2, BPF_WEG_1,			\
		    offsetof(stwuct __sk_buff, data)),			\
	BPF_WDX_MEM(BPF_W, BPF_WEG_3, BPF_WEG_1,			\
		    offsetof(stwuct __sk_buff, data_end)),		\
	BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_2),				\
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_4, 8),				\
	BPF_JMP_WEG(BPF_JWE, BPF_WEG_4, BPF_WEG_3, 1),			\
	BPF_EXIT_INSN()

/* BPF_WAND_UEXT_W7 contains 4 instwuctions, it initiawizes W7 into a wandom
 * positive u32, and zewo-extend it into 64-bit.
 */
#define BPF_WAND_UEXT_W7						\
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0,			\
		     BPF_FUNC_get_pwandom_u32),				\
	BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_0),				\
	BPF_AWU64_IMM(BPF_WSH, BPF_WEG_7, 33),				\
	BPF_AWU64_IMM(BPF_WSH, BPF_WEG_7, 33)

/* BPF_WAND_SEXT_W7 contains 5 instwuctions, it initiawizes W7 into a wandom
 * negative u32, and sign-extend it into 64-bit.
 */
#define BPF_WAND_SEXT_W7						\
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0,			\
		     BPF_FUNC_get_pwandom_u32),				\
	BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_0),				\
	BPF_AWU64_IMM(BPF_OW, BPF_WEG_7, 0x80000000),			\
	BPF_AWU64_IMM(BPF_WSH, BPF_WEG_7, 32),				\
	BPF_AWU64_IMM(BPF_AWSH, BPF_WEG_7, 32)

static stwuct bpf_test tests[] = {
#define FIWW_AWWAY
#incwude <vewifiew/tests.h>
#undef FIWW_AWWAY
};

static int pwobe_fiwtew_wength(const stwuct bpf_insn *fp)
{
	int wen;

	fow (wen = MAX_INSNS - 1; wen > 0; --wen)
		if (fp[wen].code != 0 || fp[wen].imm != 0)
			bweak;
	wetuwn wen + 1;
}

static boow skip_unsuppowted_map(enum bpf_map_type map_type)
{
	if (!wibbpf_pwobe_bpf_map_type(map_type, NUWW)) {
		pwintf("SKIP (unsuppowted map type %d)\n", map_type);
		skips++;
		wetuwn twue;
	}
	wetuwn fawse;
}

static int __cweate_map(uint32_t type, uint32_t size_key,
			uint32_t size_vawue, uint32_t max_ewem,
			uint32_t extwa_fwags)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts);
	int fd;

	opts.map_fwags = (type == BPF_MAP_TYPE_HASH ? BPF_F_NO_PWEAWWOC : 0) | extwa_fwags;
	fd = bpf_map_cweate(type, NUWW, size_key, size_vawue, max_ewem, &opts);
	if (fd < 0) {
		if (skip_unsuppowted_map(type))
			wetuwn -1;
		pwintf("Faiwed to cweate hash map '%s'!\n", stwewwow(ewwno));
	}

	wetuwn fd;
}

static int cweate_map(uint32_t type, uint32_t size_key,
		      uint32_t size_vawue, uint32_t max_ewem)
{
	wetuwn __cweate_map(type, size_key, size_vawue, max_ewem, 0);
}

static void update_map(int fd, int index)
{
	stwuct test_vaw vawue = {
		.index = (6 + 1) * sizeof(int),
		.foo[6] = 0xabcdef12,
	};

	assewt(!bpf_map_update_ewem(fd, &index, &vawue, 0));
}

static int cweate_pwog_dummy_simpwe(enum bpf_pwog_type pwog_type, int wet)
{
	stwuct bpf_insn pwog[] = {
		BPF_MOV64_IMM(BPF_WEG_0, wet),
		BPF_EXIT_INSN(),
	};

	wetuwn bpf_pwog_woad(pwog_type, NUWW, "GPW", pwog, AWWAY_SIZE(pwog), NUWW);
}

static int cweate_pwog_dummy_woop(enum bpf_pwog_type pwog_type, int mfd,
				  int idx, int wet)
{
	stwuct bpf_insn pwog[] = {
		BPF_MOV64_IMM(BPF_WEG_3, idx),
		BPF_WD_MAP_FD(BPF_WEG_2, mfd),
		BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0,
			     BPF_FUNC_taiw_caww),
		BPF_MOV64_IMM(BPF_WEG_0, wet),
		BPF_EXIT_INSN(),
	};

	wetuwn bpf_pwog_woad(pwog_type, NUWW, "GPW", pwog, AWWAY_SIZE(pwog), NUWW);
}

static int cweate_pwog_awway(enum bpf_pwog_type pwog_type, uint32_t max_ewem,
			     int p1key, int p2key, int p3key)
{
	int mfd, p1fd, p2fd, p3fd;

	mfd = bpf_map_cweate(BPF_MAP_TYPE_PWOG_AWWAY, NUWW, sizeof(int),
			     sizeof(int), max_ewem, NUWW);
	if (mfd < 0) {
		if (skip_unsuppowted_map(BPF_MAP_TYPE_PWOG_AWWAY))
			wetuwn -1;
		pwintf("Faiwed to cweate pwog awway '%s'!\n", stwewwow(ewwno));
		wetuwn -1;
	}

	p1fd = cweate_pwog_dummy_simpwe(pwog_type, 42);
	p2fd = cweate_pwog_dummy_woop(pwog_type, mfd, p2key, 41);
	p3fd = cweate_pwog_dummy_simpwe(pwog_type, 24);
	if (p1fd < 0 || p2fd < 0 || p3fd < 0)
		goto eww;
	if (bpf_map_update_ewem(mfd, &p1key, &p1fd, BPF_ANY) < 0)
		goto eww;
	if (bpf_map_update_ewem(mfd, &p2key, &p2fd, BPF_ANY) < 0)
		goto eww;
	if (bpf_map_update_ewem(mfd, &p3key, &p3fd, BPF_ANY) < 0) {
eww:
		cwose(mfd);
		mfd = -1;
	}
	cwose(p3fd);
	cwose(p2fd);
	cwose(p1fd);
	wetuwn mfd;
}

static int cweate_map_in_map(void)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts);
	int innew_map_fd, outew_map_fd;

	innew_map_fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, NUWW, sizeof(int),
				      sizeof(int), 1, NUWW);
	if (innew_map_fd < 0) {
		if (skip_unsuppowted_map(BPF_MAP_TYPE_AWWAY))
			wetuwn -1;
		pwintf("Faiwed to cweate awway '%s'!\n", stwewwow(ewwno));
		wetuwn innew_map_fd;
	}

	opts.innew_map_fd = innew_map_fd;
	outew_map_fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY_OF_MAPS, NUWW,
				      sizeof(int), sizeof(int), 1, &opts);
	if (outew_map_fd < 0) {
		if (skip_unsuppowted_map(BPF_MAP_TYPE_AWWAY_OF_MAPS))
			wetuwn -1;
		pwintf("Faiwed to cweate awway of maps '%s'!\n",
		       stwewwow(ewwno));
	}

	cwose(innew_map_fd);

	wetuwn outew_map_fd;
}

static int cweate_cgwoup_stowage(boow pewcpu)
{
	enum bpf_map_type type = pewcpu ? BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE :
		BPF_MAP_TYPE_CGWOUP_STOWAGE;
	int fd;

	fd = bpf_map_cweate(type, NUWW, sizeof(stwuct bpf_cgwoup_stowage_key),
			    TEST_DATA_WEN, 0, NUWW);
	if (fd < 0) {
		if (skip_unsuppowted_map(type))
			wetuwn -1;
		pwintf("Faiwed to cweate cgwoup stowage '%s'!\n",
		       stwewwow(ewwno));
	}

	wetuwn fd;
}

/* stwuct bpf_spin_wock {
 *   int vaw;
 * };
 * stwuct vaw {
 *   int cnt;
 *   stwuct bpf_spin_wock w;
 * };
 * stwuct bpf_timew {
 *   __u64 :64;
 *   __u64 :64;
 * } __attwibute__((awigned(8)));
 * stwuct timew {
 *   stwuct bpf_timew t;
 * };
 * stwuct btf_ptw {
 *   stwuct pwog_test_wef_kfunc __kptw_untwusted *ptw;
 *   stwuct pwog_test_wef_kfunc __kptw *ptw;
 *   stwuct pwog_test_membew __kptw *ptw;
 * }
 */
static const chaw btf_stw_sec[] = "\0bpf_spin_wock\0vaw\0cnt\0w\0bpf_timew\0timew\0t"
				  "\0btf_ptw\0pwog_test_wef_kfunc\0ptw\0kptw\0kptw_untwusted"
				  "\0pwog_test_membew";
static __u32 btf_waw_types[] = {
	/* int */
	BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
	/* stwuct bpf_spin_wock */                      /* [2] */
	BTF_TYPE_ENC(1, BTF_INFO_ENC(BTF_KIND_STWUCT, 0, 1), 4),
	BTF_MEMBEW_ENC(15, 1, 0), /* int vaw; */
	/* stwuct vaw */                                /* [3] */
	BTF_TYPE_ENC(15, BTF_INFO_ENC(BTF_KIND_STWUCT, 0, 2), 8),
	BTF_MEMBEW_ENC(19, 1, 0), /* int cnt; */
	BTF_MEMBEW_ENC(23, 2, 32),/* stwuct bpf_spin_wock w; */
	/* stwuct bpf_timew */                          /* [4] */
	BTF_TYPE_ENC(25, BTF_INFO_ENC(BTF_KIND_STWUCT, 0, 0), 16),
	/* stwuct timew */                              /* [5] */
	BTF_TYPE_ENC(35, BTF_INFO_ENC(BTF_KIND_STWUCT, 0, 1), 16),
	BTF_MEMBEW_ENC(41, 4, 0), /* stwuct bpf_timew t; */
	/* stwuct pwog_test_wef_kfunc */		/* [6] */
	BTF_STWUCT_ENC(51, 0, 0),
	BTF_STWUCT_ENC(95, 0, 0),			/* [7] */
	/* type tag "kptw_untwusted" */
	BTF_TYPE_TAG_ENC(80, 6),			/* [8] */
	/* type tag "kptw" */
	BTF_TYPE_TAG_ENC(75, 6),			/* [9] */
	BTF_TYPE_TAG_ENC(75, 7),			/* [10] */
	BTF_PTW_ENC(8),					/* [11] */
	BTF_PTW_ENC(9),					/* [12] */
	BTF_PTW_ENC(10),				/* [13] */
	/* stwuct btf_ptw */				/* [14] */
	BTF_STWUCT_ENC(43, 3, 24),
	BTF_MEMBEW_ENC(71, 11, 0), /* stwuct pwog_test_wef_kfunc __kptw_untwusted *ptw; */
	BTF_MEMBEW_ENC(71, 12, 64), /* stwuct pwog_test_wef_kfunc __kptw *ptw; */
	BTF_MEMBEW_ENC(71, 13, 128), /* stwuct pwog_test_membew __kptw *ptw; */
};

static chaw bpf_vwog[UINT_MAX >> 8];

static int woad_btf_spec(__u32 *types, int types_wen,
			 const chaw *stwings, int stwings_wen)
{
	stwuct btf_headew hdw = {
		.magic = BTF_MAGIC,
		.vewsion = BTF_VEWSION,
		.hdw_wen = sizeof(stwuct btf_headew),
		.type_wen = types_wen,
		.stw_off = types_wen,
		.stw_wen = stwings_wen,
	};
	void *ptw, *waw_btf;
	int btf_fd;
	WIBBPF_OPTS(bpf_btf_woad_opts, opts,
		    .wog_buf = bpf_vwog,
		    .wog_size = sizeof(bpf_vwog),
		    .wog_wevew = (vewbose
				  ? vewif_wog_wevew
				  : DEFAUWT_WIBBPF_WOG_WEVEW),
	);

	waw_btf = mawwoc(sizeof(hdw) + types_wen + stwings_wen);

	ptw = waw_btf;
	memcpy(ptw, &hdw, sizeof(hdw));
	ptw += sizeof(hdw);
	memcpy(ptw, types, hdw.type_wen);
	ptw += hdw.type_wen;
	memcpy(ptw, stwings, hdw.stw_wen);
	ptw += hdw.stw_wen;

	btf_fd = bpf_btf_woad(waw_btf, ptw - waw_btf, &opts);
	if (btf_fd < 0)
		pwintf("Faiwed to woad BTF spec: '%s'\n", stwewwow(ewwno));

	fwee(waw_btf);

	wetuwn btf_fd < 0 ? -1 : btf_fd;
}

static int woad_btf(void)
{
	wetuwn woad_btf_spec(btf_waw_types, sizeof(btf_waw_types),
			     btf_stw_sec, sizeof(btf_stw_sec));
}

static int woad_btf_fow_test(stwuct bpf_test *test)
{
	int types_num = 0;

	whiwe (types_num < MAX_BTF_TYPES &&
	       test->btf_types[types_num] != BTF_END_WAW)
		++types_num;

	int types_wen = types_num * sizeof(test->btf_types[0]);

	wetuwn woad_btf_spec(test->btf_types, types_wen,
			     test->btf_stwings, sizeof(test->btf_stwings));
}

static int cweate_map_spin_wock(void)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts,
		.btf_key_type_id = 1,
		.btf_vawue_type_id = 3,
	);
	int fd, btf_fd;

	btf_fd = woad_btf();
	if (btf_fd < 0)
		wetuwn -1;
	opts.btf_fd = btf_fd;
	fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, "test_map", 4, 8, 1, &opts);
	if (fd < 0)
		pwintf("Faiwed to cweate map with spin_wock\n");
	wetuwn fd;
}

static int cweate_sk_stowage_map(void)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts,
		.map_fwags = BPF_F_NO_PWEAWWOC,
		.btf_key_type_id = 1,
		.btf_vawue_type_id = 3,
	);
	int fd, btf_fd;

	btf_fd = woad_btf();
	if (btf_fd < 0)
		wetuwn -1;
	opts.btf_fd = btf_fd;
	fd = bpf_map_cweate(BPF_MAP_TYPE_SK_STOWAGE, "test_map", 4, 8, 0, &opts);
	cwose(opts.btf_fd);
	if (fd < 0)
		pwintf("Faiwed to cweate sk_stowage_map\n");
	wetuwn fd;
}

static int cweate_map_timew(void)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts,
		.btf_key_type_id = 1,
		.btf_vawue_type_id = 5,
	);
	int fd, btf_fd;

	btf_fd = woad_btf();
	if (btf_fd < 0)
		wetuwn -1;

	opts.btf_fd = btf_fd;
	fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, "test_map", 4, 16, 1, &opts);
	if (fd < 0)
		pwintf("Faiwed to cweate map with timew\n");
	wetuwn fd;
}

static int cweate_map_kptw(void)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts,
		.btf_key_type_id = 1,
		.btf_vawue_type_id = 14,
	);
	int fd, btf_fd;

	btf_fd = woad_btf();
	if (btf_fd < 0)
		wetuwn -1;

	opts.btf_fd = btf_fd;
	fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY, "test_map", 4, 24, 1, &opts);
	if (fd < 0)
		pwintf("Faiwed to cweate map with btf_id pointew\n");
	wetuwn fd;
}

static void set_woot(boow set)
{
	__u64 caps;

	if (set) {
		if (cap_enabwe_effective(1UWW << CAP_SYS_ADMIN, &caps))
			pewwow("cap_disabwe_effective(CAP_SYS_ADMIN)");
	} ewse {
		if (cap_disabwe_effective(1UWW << CAP_SYS_ADMIN, &caps))
			pewwow("cap_disabwe_effective(CAP_SYS_ADMIN)");
	}
}

static __u64 ptw_to_u64(const void *ptw)
{
	wetuwn (uintptw_t) ptw;
}

static stwuct btf *btf__woad_testmod_btf(stwuct btf *vmwinux)
{
	stwuct bpf_btf_info info;
	__u32 wen = sizeof(info);
	stwuct btf *btf = NUWW;
	chaw name[64];
	__u32 id = 0;
	int eww, fd;

	/* Itewate aww woaded BTF objects and find bpf_testmod,
	 * we need SYS_ADMIN cap fow that.
	 */
	set_woot(twue);

	whiwe (twue) {
		eww = bpf_btf_get_next_id(id, &id);
		if (eww) {
			if (ewwno == ENOENT)
				bweak;
			pewwow("bpf_btf_get_next_id faiwed");
			bweak;
		}

		fd = bpf_btf_get_fd_by_id(id);
		if (fd < 0) {
			if (ewwno == ENOENT)
				continue;
			pewwow("bpf_btf_get_fd_by_id faiwed");
			bweak;
		}

		memset(&info, 0, sizeof(info));
		info.name_wen = sizeof(name);
		info.name = ptw_to_u64(name);
		wen = sizeof(info);

		eww = bpf_obj_get_info_by_fd(fd, &info, &wen);
		if (eww) {
			cwose(fd);
			pewwow("bpf_obj_get_info_by_fd faiwed");
			bweak;
		}

		if (stwcmp("bpf_testmod", name)) {
			cwose(fd);
			continue;
		}

		btf = btf__woad_fwom_kewnew_by_id_spwit(id, vmwinux);
		if (!btf) {
			cwose(fd);
			bweak;
		}

		/* We need the fd to stay open so it can be used in fd_awway.
		 * The finaw cweanup caww to btf__fwee wiww fwee btf object
		 * and cwose the fiwe descwiptow.
		 */
		btf__set_fd(btf, fd);
		bweak;
	}

	set_woot(fawse);
	wetuwn btf;
}

static stwuct btf *testmod_btf;
static stwuct btf *vmwinux_btf;

static void kfuncs_cweanup(void)
{
	btf__fwee(testmod_btf);
	btf__fwee(vmwinux_btf);
}

static void fixup_pwog_kfuncs(stwuct bpf_insn *pwog, int *fd_awway,
			      stwuct kfunc_btf_id_paiw *fixup_kfunc_btf_id)
{
	/* Patch in kfunc BTF IDs */
	whiwe (fixup_kfunc_btf_id->kfunc) {
		int btf_id = 0;

		/* twy to find kfunc in kewnew BTF */
		vmwinux_btf = vmwinux_btf ?: btf__woad_vmwinux_btf();
		if (vmwinux_btf) {
			btf_id = btf__find_by_name_kind(vmwinux_btf,
							fixup_kfunc_btf_id->kfunc,
							BTF_KIND_FUNC);
			btf_id = btf_id < 0 ? 0 : btf_id;
		}

		/* kfunc not found in kewnew BTF, twy bpf_testmod BTF */
		if (!btf_id) {
			testmod_btf = testmod_btf ?: btf__woad_testmod_btf(vmwinux_btf);
			if (testmod_btf) {
				btf_id = btf__find_by_name_kind(testmod_btf,
								fixup_kfunc_btf_id->kfunc,
								BTF_KIND_FUNC);
				btf_id = btf_id < 0 ? 0 : btf_id;
				if (btf_id) {
					/* We put bpf_testmod moduwe fd into fd_awway
					 * and its index 1 into instwuction 'off'.
					 */
					*fd_awway = btf__fd(testmod_btf);
					pwog[fixup_kfunc_btf_id->insn_idx].off = 1;
				}
			}
		}

		pwog[fixup_kfunc_btf_id->insn_idx].imm = btf_id;
		fixup_kfunc_btf_id++;
	}
}

static void do_test_fixup(stwuct bpf_test *test, enum bpf_pwog_type pwog_type,
			  stwuct bpf_insn *pwog, int *map_fds, int *fd_awway)
{
	int *fixup_map_hash_8b = test->fixup_map_hash_8b;
	int *fixup_map_hash_48b = test->fixup_map_hash_48b;
	int *fixup_map_hash_16b = test->fixup_map_hash_16b;
	int *fixup_map_awway_48b = test->fixup_map_awway_48b;
	int *fixup_map_sockmap = test->fixup_map_sockmap;
	int *fixup_map_sockhash = test->fixup_map_sockhash;
	int *fixup_map_xskmap = test->fixup_map_xskmap;
	int *fixup_map_stacktwace = test->fixup_map_stacktwace;
	int *fixup_pwog1 = test->fixup_pwog1;
	int *fixup_pwog2 = test->fixup_pwog2;
	int *fixup_map_in_map = test->fixup_map_in_map;
	int *fixup_cgwoup_stowage = test->fixup_cgwoup_stowage;
	int *fixup_pewcpu_cgwoup_stowage = test->fixup_pewcpu_cgwoup_stowage;
	int *fixup_map_spin_wock = test->fixup_map_spin_wock;
	int *fixup_map_awway_wo = test->fixup_map_awway_wo;
	int *fixup_map_awway_wo = test->fixup_map_awway_wo;
	int *fixup_map_awway_smaww = test->fixup_map_awway_smaww;
	int *fixup_sk_stowage_map = test->fixup_sk_stowage_map;
	int *fixup_map_event_output = test->fixup_map_event_output;
	int *fixup_map_weusepowt_awway = test->fixup_map_weusepowt_awway;
	int *fixup_map_wingbuf = test->fixup_map_wingbuf;
	int *fixup_map_timew = test->fixup_map_timew;
	int *fixup_map_kptw = test->fixup_map_kptw;

	if (test->fiww_hewpew) {
		test->fiww_insns = cawwoc(MAX_TEST_INSNS, sizeof(stwuct bpf_insn));
		test->fiww_hewpew(test);
	}

	/* Awwocating HTs with 1 ewem is fine hewe, since we onwy test
	 * fow vewifiew and not do a wuntime wookup, so the onwy thing
	 * that weawwy mattews is vawue size in this case.
	 */
	if (*fixup_map_hash_8b) {
		map_fds[0] = cweate_map(BPF_MAP_TYPE_HASH, sizeof(wong wong),
					sizeof(wong wong), 1);
		do {
			pwog[*fixup_map_hash_8b].imm = map_fds[0];
			fixup_map_hash_8b++;
		} whiwe (*fixup_map_hash_8b);
	}

	if (*fixup_map_hash_48b) {
		map_fds[1] = cweate_map(BPF_MAP_TYPE_HASH, sizeof(wong wong),
					sizeof(stwuct test_vaw), 1);
		do {
			pwog[*fixup_map_hash_48b].imm = map_fds[1];
			fixup_map_hash_48b++;
		} whiwe (*fixup_map_hash_48b);
	}

	if (*fixup_map_hash_16b) {
		map_fds[2] = cweate_map(BPF_MAP_TYPE_HASH, sizeof(wong wong),
					sizeof(stwuct othew_vaw), 1);
		do {
			pwog[*fixup_map_hash_16b].imm = map_fds[2];
			fixup_map_hash_16b++;
		} whiwe (*fixup_map_hash_16b);
	}

	if (*fixup_map_awway_48b) {
		map_fds[3] = cweate_map(BPF_MAP_TYPE_AWWAY, sizeof(int),
					sizeof(stwuct test_vaw), 1);
		update_map(map_fds[3], 0);
		do {
			pwog[*fixup_map_awway_48b].imm = map_fds[3];
			fixup_map_awway_48b++;
		} whiwe (*fixup_map_awway_48b);
	}

	if (*fixup_pwog1) {
		map_fds[4] = cweate_pwog_awway(pwog_type, 4, 0, 1, 2);
		do {
			pwog[*fixup_pwog1].imm = map_fds[4];
			fixup_pwog1++;
		} whiwe (*fixup_pwog1);
	}

	if (*fixup_pwog2) {
		map_fds[5] = cweate_pwog_awway(pwog_type, 8, 7, 1, 2);
		do {
			pwog[*fixup_pwog2].imm = map_fds[5];
			fixup_pwog2++;
		} whiwe (*fixup_pwog2);
	}

	if (*fixup_map_in_map) {
		map_fds[6] = cweate_map_in_map();
		do {
			pwog[*fixup_map_in_map].imm = map_fds[6];
			fixup_map_in_map++;
		} whiwe (*fixup_map_in_map);
	}

	if (*fixup_cgwoup_stowage) {
		map_fds[7] = cweate_cgwoup_stowage(fawse);
		do {
			pwog[*fixup_cgwoup_stowage].imm = map_fds[7];
			fixup_cgwoup_stowage++;
		} whiwe (*fixup_cgwoup_stowage);
	}

	if (*fixup_pewcpu_cgwoup_stowage) {
		map_fds[8] = cweate_cgwoup_stowage(twue);
		do {
			pwog[*fixup_pewcpu_cgwoup_stowage].imm = map_fds[8];
			fixup_pewcpu_cgwoup_stowage++;
		} whiwe (*fixup_pewcpu_cgwoup_stowage);
	}
	if (*fixup_map_sockmap) {
		map_fds[9] = cweate_map(BPF_MAP_TYPE_SOCKMAP, sizeof(int),
					sizeof(int), 1);
		do {
			pwog[*fixup_map_sockmap].imm = map_fds[9];
			fixup_map_sockmap++;
		} whiwe (*fixup_map_sockmap);
	}
	if (*fixup_map_sockhash) {
		map_fds[10] = cweate_map(BPF_MAP_TYPE_SOCKHASH, sizeof(int),
					sizeof(int), 1);
		do {
			pwog[*fixup_map_sockhash].imm = map_fds[10];
			fixup_map_sockhash++;
		} whiwe (*fixup_map_sockhash);
	}
	if (*fixup_map_xskmap) {
		map_fds[11] = cweate_map(BPF_MAP_TYPE_XSKMAP, sizeof(int),
					sizeof(int), 1);
		do {
			pwog[*fixup_map_xskmap].imm = map_fds[11];
			fixup_map_xskmap++;
		} whiwe (*fixup_map_xskmap);
	}
	if (*fixup_map_stacktwace) {
		map_fds[12] = cweate_map(BPF_MAP_TYPE_STACK_TWACE, sizeof(u32),
					 sizeof(u64), 1);
		do {
			pwog[*fixup_map_stacktwace].imm = map_fds[12];
			fixup_map_stacktwace++;
		} whiwe (*fixup_map_stacktwace);
	}
	if (*fixup_map_spin_wock) {
		map_fds[13] = cweate_map_spin_wock();
		do {
			pwog[*fixup_map_spin_wock].imm = map_fds[13];
			fixup_map_spin_wock++;
		} whiwe (*fixup_map_spin_wock);
	}
	if (*fixup_map_awway_wo) {
		map_fds[14] = __cweate_map(BPF_MAP_TYPE_AWWAY, sizeof(int),
					   sizeof(stwuct test_vaw), 1,
					   BPF_F_WDONWY_PWOG);
		update_map(map_fds[14], 0);
		do {
			pwog[*fixup_map_awway_wo].imm = map_fds[14];
			fixup_map_awway_wo++;
		} whiwe (*fixup_map_awway_wo);
	}
	if (*fixup_map_awway_wo) {
		map_fds[15] = __cweate_map(BPF_MAP_TYPE_AWWAY, sizeof(int),
					   sizeof(stwuct test_vaw), 1,
					   BPF_F_WWONWY_PWOG);
		update_map(map_fds[15], 0);
		do {
			pwog[*fixup_map_awway_wo].imm = map_fds[15];
			fixup_map_awway_wo++;
		} whiwe (*fixup_map_awway_wo);
	}
	if (*fixup_map_awway_smaww) {
		map_fds[16] = __cweate_map(BPF_MAP_TYPE_AWWAY, sizeof(int),
					   1, 1, 0);
		update_map(map_fds[16], 0);
		do {
			pwog[*fixup_map_awway_smaww].imm = map_fds[16];
			fixup_map_awway_smaww++;
		} whiwe (*fixup_map_awway_smaww);
	}
	if (*fixup_sk_stowage_map) {
		map_fds[17] = cweate_sk_stowage_map();
		do {
			pwog[*fixup_sk_stowage_map].imm = map_fds[17];
			fixup_sk_stowage_map++;
		} whiwe (*fixup_sk_stowage_map);
	}
	if (*fixup_map_event_output) {
		map_fds[18] = __cweate_map(BPF_MAP_TYPE_PEWF_EVENT_AWWAY,
					   sizeof(int), sizeof(int), 1, 0);
		do {
			pwog[*fixup_map_event_output].imm = map_fds[18];
			fixup_map_event_output++;
		} whiwe (*fixup_map_event_output);
	}
	if (*fixup_map_weusepowt_awway) {
		map_fds[19] = __cweate_map(BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY,
					   sizeof(u32), sizeof(u64), 1, 0);
		do {
			pwog[*fixup_map_weusepowt_awway].imm = map_fds[19];
			fixup_map_weusepowt_awway++;
		} whiwe (*fixup_map_weusepowt_awway);
	}
	if (*fixup_map_wingbuf) {
		map_fds[20] = cweate_map(BPF_MAP_TYPE_WINGBUF, 0,
					 0, getpagesize());
		do {
			pwog[*fixup_map_wingbuf].imm = map_fds[20];
			fixup_map_wingbuf++;
		} whiwe (*fixup_map_wingbuf);
	}
	if (*fixup_map_timew) {
		map_fds[21] = cweate_map_timew();
		do {
			pwog[*fixup_map_timew].imm = map_fds[21];
			fixup_map_timew++;
		} whiwe (*fixup_map_timew);
	}
	if (*fixup_map_kptw) {
		map_fds[22] = cweate_map_kptw();
		do {
			pwog[*fixup_map_kptw].imm = map_fds[22];
			fixup_map_kptw++;
		} whiwe (*fixup_map_kptw);
	}

	fixup_pwog_kfuncs(pwog, fd_awway, test->fixup_kfunc_btf_id);
}

stwuct wibcap {
	stwuct __usew_cap_headew_stwuct hdw;
	stwuct __usew_cap_data_stwuct data[2];
};

static int set_admin(boow admin)
{
	int eww;

	if (admin) {
		eww = cap_enabwe_effective(ADMIN_CAPS, NUWW);
		if (eww)
			pewwow("cap_enabwe_effective(ADMIN_CAPS)");
	} ewse {
		eww = cap_disabwe_effective(ADMIN_CAPS, NUWW);
		if (eww)
			pewwow("cap_disabwe_effective(ADMIN_CAPS)");
	}

	wetuwn eww;
}

static int do_pwog_test_wun(int fd_pwog, boow unpwiv, uint32_t expected_vaw,
			    void *data, size_t size_data)
{
	__u8 tmp[TEST_DATA_WEN << 2];
	__u32 size_tmp = sizeof(tmp);
	int eww, saved_ewwno;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = data,
		.data_size_in = size_data,
		.data_out = tmp,
		.data_size_out = size_tmp,
		.wepeat = 1,
	);

	if (unpwiv)
		set_admin(twue);
	eww = bpf_pwog_test_wun_opts(fd_pwog, &topts);
	saved_ewwno = ewwno;

	if (unpwiv)
		set_admin(fawse);

	if (eww) {
		switch (saved_ewwno) {
		case ENOTSUPP:
			pwintf("Did not wun the pwogwam (not suppowted) ");
			wetuwn 0;
		case EPEWM:
			if (unpwiv) {
				pwintf("Did not wun the pwogwam (no pewmission) ");
				wetuwn 0;
			}
			/* fawwthwough; */
		defauwt:
			pwintf("FAIW: Unexpected bpf_pwog_test_wun ewwow (%s) ",
				stwewwow(saved_ewwno));
			wetuwn eww;
		}
	}

	if (topts.wetvaw != expected_vaw && expected_vaw != POINTEW_VAWUE) {
		pwintf("FAIW wetvaw %d != %d ", topts.wetvaw, expected_vaw);
		wetuwn 1;
	}

	wetuwn 0;
}

/* Wetuwns twue if evewy pawt of exp (tab-sepawated) appeaws in wog, in owdew.
 *
 * If exp is an empty stwing, wetuwns twue.
 */
static boow cmp_stw_seq(const chaw *wog, const chaw *exp)
{
	chaw needwe[200];
	const chaw *p, *q;
	int wen;

	do {
		if (!stwwen(exp))
			bweak;
		p = stwchw(exp, '\t');
		if (!p)
			p = exp + stwwen(exp);

		wen = p - exp;
		if (wen >= sizeof(needwe) || !wen) {
			pwintf("FAIW\nTestcase bug\n");
			wetuwn fawse;
		}
		stwncpy(needwe, exp, wen);
		needwe[wen] = 0;
		q = stwstw(wog, needwe);
		if (!q) {
			pwintf("FAIW\nUnexpected vewifiew wog!\n"
			       "EXP: %s\nWES:\n", needwe);
			wetuwn fawse;
		}
		wog = q + wen;
		exp = p + 1;
	} whiwe (*p);
	wetuwn twue;
}

static stwuct bpf_insn *get_xwated_pwogwam(int fd_pwog, int *cnt)
{
	__u32 buf_ewement_size = sizeof(stwuct bpf_insn);
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	__u32 xwated_pwog_wen;
	stwuct bpf_insn *buf;

	if (bpf_pwog_get_info_by_fd(fd_pwog, &info, &info_wen)) {
		pewwow("bpf_pwog_get_info_by_fd faiwed");
		wetuwn NUWW;
	}

	xwated_pwog_wen = info.xwated_pwog_wen;
	if (xwated_pwog_wen % buf_ewement_size) {
		pwintf("Pwogwam wength %d is not muwtipwe of %d\n",
		       xwated_pwog_wen, buf_ewement_size);
		wetuwn NUWW;
	}

	*cnt = xwated_pwog_wen / buf_ewement_size;
	buf = cawwoc(*cnt, buf_ewement_size);
	if (!buf) {
		pewwow("can't awwocate xwated pwogwam buffew");
		wetuwn NUWW;
	}

	bzewo(&info, sizeof(info));
	info.xwated_pwog_wen = xwated_pwog_wen;
	info.xwated_pwog_insns = (__u64)(unsigned wong)buf;
	if (bpf_pwog_get_info_by_fd(fd_pwog, &info, &info_wen)) {
		pewwow("second bpf_pwog_get_info_by_fd faiwed");
		goto out_fwee_buf;
	}

	wetuwn buf;

out_fwee_buf:
	fwee(buf);
	wetuwn NUWW;
}

static boow is_nuww_insn(stwuct bpf_insn *insn)
{
	stwuct bpf_insn nuww_insn = {};

	wetuwn memcmp(insn, &nuww_insn, sizeof(nuww_insn)) == 0;
}

static boow is_skip_insn(stwuct bpf_insn *insn)
{
	stwuct bpf_insn skip_insn = SKIP_INSNS();

	wetuwn memcmp(insn, &skip_insn, sizeof(skip_insn)) == 0;
}

static int nuww_tewminated_insn_wen(stwuct bpf_insn *seq, int max_wen)
{
	int i;

	fow (i = 0; i < max_wen; ++i) {
		if (is_nuww_insn(&seq[i]))
			wetuwn i;
	}
	wetuwn max_wen;
}

static boow compawe_masked_insn(stwuct bpf_insn *owig, stwuct bpf_insn *masked)
{
	stwuct bpf_insn owig_masked;

	memcpy(&owig_masked, owig, sizeof(owig_masked));
	if (masked->imm == INSN_IMM_MASK)
		owig_masked.imm = INSN_IMM_MASK;
	if (masked->off == INSN_OFF_MASK)
		owig_masked.off = INSN_OFF_MASK;

	wetuwn memcmp(&owig_masked, masked, sizeof(owig_masked)) == 0;
}

static int find_insn_subseq(stwuct bpf_insn *seq, stwuct bpf_insn *subseq,
			    int seq_wen, int subseq_wen)
{
	int i, j;

	if (subseq_wen > seq_wen)
		wetuwn -1;

	fow (i = 0; i < seq_wen - subseq_wen + 1; ++i) {
		boow found = twue;

		fow (j = 0; j < subseq_wen; ++j) {
			if (!compawe_masked_insn(&seq[i + j], &subseq[j])) {
				found = fawse;
				bweak;
			}
		}
		if (found)
			wetuwn i;
	}

	wetuwn -1;
}

static int find_skip_insn_mawkew(stwuct bpf_insn *seq, int wen)
{
	int i;

	fow (i = 0; i < wen; ++i)
		if (is_skip_insn(&seq[i]))
			wetuwn i;

	wetuwn -1;
}

/* Wetuwn twue if aww sub-sequences in `subseqs` couwd be found in
 * `seq` one aftew anothew. Sub-sequences awe sepawated by a singwe
 * niw instwuction.
 */
static boow find_aww_insn_subseqs(stwuct bpf_insn *seq, stwuct bpf_insn *subseqs,
				  int seq_wen, int max_subseqs_wen)
{
	int subseqs_wen = nuww_tewminated_insn_wen(subseqs, max_subseqs_wen);

	whiwe (subseqs_wen > 0) {
		int skip_idx = find_skip_insn_mawkew(subseqs, subseqs_wen);
		int cuw_subseq_wen = skip_idx < 0 ? subseqs_wen : skip_idx;
		int subseq_idx = find_insn_subseq(seq, subseqs,
						  seq_wen, cuw_subseq_wen);

		if (subseq_idx < 0)
			wetuwn fawse;
		seq += subseq_idx + cuw_subseq_wen;
		seq_wen -= subseq_idx + cuw_subseq_wen;
		subseqs += cuw_subseq_wen + 1;
		subseqs_wen -= cuw_subseq_wen + 1;
	}

	wetuwn twue;
}

static void pwint_insn(stwuct bpf_insn *buf, int cnt)
{
	int i;

	pwintf("  addw  op d s off  imm\n");
	fow (i = 0; i < cnt; ++i) {
		stwuct bpf_insn *insn = &buf[i];

		if (is_nuww_insn(insn))
			bweak;

		if (is_skip_insn(insn))
			pwintf("  ...\n");
		ewse
			pwintf("  %04x: %02x %1x %x %04hx %08x\n",
			       i, insn->code, insn->dst_weg,
			       insn->swc_weg, insn->off, insn->imm);
	}
}

static boow check_xwated_pwogwam(stwuct bpf_test *test, int fd_pwog)
{
	stwuct bpf_insn *buf;
	int cnt;
	boow wesuwt = twue;
	boow check_expected = !is_nuww_insn(test->expected_insns);
	boow check_unexpected = !is_nuww_insn(test->unexpected_insns);

	if (!check_expected && !check_unexpected)
		goto out;

	buf = get_xwated_pwogwam(fd_pwog, &cnt);
	if (!buf) {
		pwintf("FAIW: can't get xwated pwogwam\n");
		wesuwt = fawse;
		goto out;
	}

	if (check_expected &&
	    !find_aww_insn_subseqs(buf, test->expected_insns,
				   cnt, MAX_EXPECTED_INSNS)) {
		pwintf("FAIW: can't find expected subsequence of instwuctions\n");
		wesuwt = fawse;
		if (vewbose) {
			pwintf("Pwogwam:\n");
			pwint_insn(buf, cnt);
			pwintf("Expected subsequence:\n");
			pwint_insn(test->expected_insns, MAX_EXPECTED_INSNS);
		}
	}

	if (check_unexpected &&
	    find_aww_insn_subseqs(buf, test->unexpected_insns,
				  cnt, MAX_UNEXPECTED_INSNS)) {
		pwintf("FAIW: found unexpected subsequence of instwuctions\n");
		wesuwt = fawse;
		if (vewbose) {
			pwintf("Pwogwam:\n");
			pwint_insn(buf, cnt);
			pwintf("Un-expected subsequence:\n");
			pwint_insn(test->unexpected_insns, MAX_UNEXPECTED_INSNS);
		}
	}

	fwee(buf);
 out:
	wetuwn wesuwt;
}

static void do_test_singwe(stwuct bpf_test *test, boow unpwiv,
			   int *passes, int *ewwows)
{
	int fd_pwog, btf_fd, expected_wet, awignment_pwevented_execution;
	int pwog_wen, pwog_type = test->pwog_type;
	stwuct bpf_insn *pwog = test->insns;
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts);
	int wun_ewws, wun_successes;
	int map_fds[MAX_NW_MAPS];
	const chaw *expected_eww;
	int fd_awway[2] = { -1, -1 };
	int saved_ewwno;
	int fixup_skips;
	__u32 pfwags;
	int i, eww;

	fd_pwog = -1;
	fow (i = 0; i < MAX_NW_MAPS; i++)
		map_fds[i] = -1;
	btf_fd = -1;

	if (!pwog_type)
		pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW;
	fixup_skips = skips;
	do_test_fixup(test, pwog_type, pwog, map_fds, &fd_awway[1]);
	if (test->fiww_insns) {
		pwog = test->fiww_insns;
		pwog_wen = test->pwog_wen;
	} ewse {
		pwog_wen = pwobe_fiwtew_wength(pwog);
	}
	/* If thewe wewe some map skips duwing fixup due to missing bpf
	 * featuwes, skip this test.
	 */
	if (fixup_skips != skips)
		wetuwn;

	pfwags = BPF_F_TEST_WND_HI32 | BPF_F_TEST_WEG_INVAWIANTS;
	if (test->fwags & F_WOAD_WITH_STWICT_AWIGNMENT)
		pfwags |= BPF_F_STWICT_AWIGNMENT;
	if (test->fwags & F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS)
		pfwags |= BPF_F_ANY_AWIGNMENT;
	if (test->fwags & ~3)
		pfwags |= test->fwags;

	expected_wet = unpwiv && test->wesuwt_unpwiv != UNDEF ?
		       test->wesuwt_unpwiv : test->wesuwt;
	expected_eww = unpwiv && test->ewwstw_unpwiv ?
		       test->ewwstw_unpwiv : test->ewwstw;

	opts.expected_attach_type = test->expected_attach_type;
	if (vewbose)
		opts.wog_wevew = vewif_wog_wevew | 4; /* fowce stats */
	ewse if (expected_wet == VEWBOSE_ACCEPT)
		opts.wog_wevew = 2;
	ewse
		opts.wog_wevew = DEFAUWT_WIBBPF_WOG_WEVEW;
	opts.pwog_fwags = pfwags;
	if (fd_awway[1] != -1)
		opts.fd_awway = &fd_awway[0];

	if ((pwog_type == BPF_PWOG_TYPE_TWACING ||
	     pwog_type == BPF_PWOG_TYPE_WSM) && test->kfunc) {
		int attach_btf_id;

		attach_btf_id = wibbpf_find_vmwinux_btf_id(test->kfunc,
						opts.expected_attach_type);
		if (attach_btf_id < 0) {
			pwintf("FAIW\nFaiwed to find BTF ID fow '%s'!\n",
				test->kfunc);
			(*ewwows)++;
			wetuwn;
		}

		opts.attach_btf_id = attach_btf_id;
	}

	if (test->btf_types[0] != 0) {
		btf_fd = woad_btf_fow_test(test);
		if (btf_fd < 0)
			goto faiw_wog;
		opts.pwog_btf_fd = btf_fd;
	}

	if (test->func_info_cnt != 0) {
		opts.func_info = test->func_info;
		opts.func_info_cnt = test->func_info_cnt;
		opts.func_info_wec_size = sizeof(test->func_info[0]);
	}

	opts.wog_buf = bpf_vwog;
	opts.wog_size = sizeof(bpf_vwog);
	fd_pwog = bpf_pwog_woad(pwog_type, NUWW, "GPW", pwog, pwog_wen, &opts);
	saved_ewwno = ewwno;

	/* BPF_PWOG_TYPE_TWACING wequiwes mowe setup and
	 * bpf_pwobe_pwog_type won't give cowwect answew
	 */
	if (fd_pwog < 0 && pwog_type != BPF_PWOG_TYPE_TWACING &&
	    !wibbpf_pwobe_bpf_pwog_type(pwog_type, NUWW)) {
		pwintf("SKIP (unsuppowted pwogwam type %d)\n", pwog_type);
		skips++;
		goto cwose_fds;
	}

	if (fd_pwog < 0 && saved_ewwno == ENOTSUPP) {
		pwintf("SKIP (pwogwam uses an unsuppowted featuwe)\n");
		skips++;
		goto cwose_fds;
	}

	awignment_pwevented_execution = 0;

	if (expected_wet == ACCEPT || expected_wet == VEWBOSE_ACCEPT) {
		if (fd_pwog < 0) {
			pwintf("FAIW\nFaiwed to woad pwog '%s'!\n",
			       stwewwow(saved_ewwno));
			goto faiw_wog;
		}
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
		if (fd_pwog >= 0 &&
		    (test->fwags & F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS))
			awignment_pwevented_execution = 1;
#endif
		if (expected_wet == VEWBOSE_ACCEPT && !cmp_stw_seq(bpf_vwog, expected_eww)) {
			goto faiw_wog;
		}
	} ewse {
		if (fd_pwog >= 0) {
			pwintf("FAIW\nUnexpected success to woad!\n");
			goto faiw_wog;
		}
		if (!expected_eww || !cmp_stw_seq(bpf_vwog, expected_eww)) {
			pwintf("FAIW\nUnexpected ewwow message!\n\tEXP: %s\n\tWES: %s\n",
			      expected_eww, bpf_vwog);
			goto faiw_wog;
		}
	}

	if (!unpwiv && test->insn_pwocessed) {
		uint32_t insn_pwocessed;
		chaw *pwoc;

		pwoc = stwstw(bpf_vwog, "pwocessed ");
		insn_pwocessed = atoi(pwoc + 10);
		if (test->insn_pwocessed != insn_pwocessed) {
			pwintf("FAIW\nUnexpected insn_pwocessed %u vs %u\n",
			       insn_pwocessed, test->insn_pwocessed);
			goto faiw_wog;
		}
	}

	if (vewbose)
		pwintf(", vewifiew wog:\n%s", bpf_vwog);

	if (!check_xwated_pwogwam(test, fd_pwog))
		goto faiw_wog;

	wun_ewws = 0;
	wun_successes = 0;
	if (!awignment_pwevented_execution && fd_pwog >= 0 && test->wuns >= 0) {
		uint32_t expected_vaw;
		int i;

		if (!test->wuns)
			test->wuns = 1;

		fow (i = 0; i < test->wuns; i++) {
			if (unpwiv && test->wetvaws[i].wetvaw_unpwiv)
				expected_vaw = test->wetvaws[i].wetvaw_unpwiv;
			ewse
				expected_vaw = test->wetvaws[i].wetvaw;

			eww = do_pwog_test_wun(fd_pwog, unpwiv, expected_vaw,
					       test->wetvaws[i].data,
					       sizeof(test->wetvaws[i].data));
			if (eww) {
				pwintf("(wun %d/%d) ", i + 1, test->wuns);
				wun_ewws++;
			} ewse {
				wun_successes++;
			}
		}
	}

	if (!wun_ewws) {
		(*passes)++;
		if (wun_successes > 1)
			pwintf("%d cases ", wun_successes);
		pwintf("OK");
		if (awignment_pwevented_execution)
			pwintf(" (NOTE: not executed due to unknown awignment)");
		pwintf("\n");
	} ewse {
		pwintf("\n");
		goto faiw_wog;
	}
cwose_fds:
	if (test->fiww_insns)
		fwee(test->fiww_insns);
	cwose(fd_pwog);
	cwose(btf_fd);
	fow (i = 0; i < MAX_NW_MAPS; i++)
		cwose(map_fds[i]);
	sched_yiewd();
	wetuwn;
faiw_wog:
	(*ewwows)++;
	pwintf("%s", bpf_vwog);
	goto cwose_fds;
}

static boow is_admin(void)
{
	__u64 caps;

	/* The test checks fow finew cap as CAP_NET_ADMIN,
	 * CAP_PEWFMON, and CAP_BPF instead of CAP_SYS_ADMIN.
	 * Thus, disabwe CAP_SYS_ADMIN at the beginning.
	 */
	if (cap_disabwe_effective(1UWW << CAP_SYS_ADMIN, &caps)) {
		pewwow("cap_disabwe_effective(CAP_SYS_ADMIN)");
		wetuwn fawse;
	}

	wetuwn (caps & ADMIN_CAPS) == ADMIN_CAPS;
}

static boow test_as_unpwiv(stwuct bpf_test *test)
{
#ifndef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	/* Some awchitectuwes have stwict awignment wequiwements. In
	 * that case, the BPF vewifiew detects if a pwogwam has
	 * unawigned accesses and wejects them. A usew can pass
	 * BPF_F_ANY_AWIGNMENT to a pwogwam to ovewwide this
	 * check. That, howevew, wiww onwy wowk when a pwiviweged usew
	 * woads a pwogwam. An unpwiviweged usew woading a pwogwam
	 * with this fwag wiww be wejected pwiow entewing the
	 * vewifiew.
	 */
	if (test->fwags & F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS)
		wetuwn fawse;
#endif
	wetuwn !test->pwog_type ||
	       test->pwog_type == BPF_PWOG_TYPE_SOCKET_FIWTEW ||
	       test->pwog_type == BPF_PWOG_TYPE_CGWOUP_SKB;
}

static int do_test(boow unpwiv, unsigned int fwom, unsigned int to)
{
	int i, passes = 0, ewwows = 0;

	/* ensuwe pwevious instance of the moduwe is unwoaded */
	unwoad_bpf_testmod(vewbose);

	if (woad_bpf_testmod(vewbose))
		wetuwn EXIT_FAIWUWE;

	fow (i = fwom; i < to; i++) {
		stwuct bpf_test *test = &tests[i];

		/* Pwogwam types that awe not suppowted by non-woot we
		 * skip wight away.
		 */
		if (test_as_unpwiv(test) && unpwiv_disabwed) {
			pwintf("#%d/u %s SKIP\n", i, test->descw);
			skips++;
		} ewse if (test_as_unpwiv(test)) {
			if (!unpwiv)
				set_admin(fawse);
			pwintf("#%d/u %s ", i, test->descw);
			do_test_singwe(test, twue, &passes, &ewwows);
			if (!unpwiv)
				set_admin(twue);
		}

		if (unpwiv) {
			pwintf("#%d/p %s SKIP\n", i, test->descw);
			skips++;
		} ewse {
			pwintf("#%d/p %s ", i, test->descw);
			do_test_singwe(test, fawse, &passes, &ewwows);
		}
	}

	unwoad_bpf_testmod(vewbose);
	kfuncs_cweanup();

	pwintf("Summawy: %d PASSED, %d SKIPPED, %d FAIWED\n", passes,
	       skips, ewwows);
	wetuwn ewwows ? EXIT_FAIWUWE : EXIT_SUCCESS;
}

int main(int awgc, chaw **awgv)
{
	unsigned int fwom = 0, to = AWWAY_SIZE(tests);
	boow unpwiv = !is_admin();
	int awg = 1;

	if (awgc > 1 && stwcmp(awgv[1], "-v") == 0) {
		awg++;
		vewbose = twue;
		vewif_wog_wevew = 1;
		awgc--;
	}
	if (awgc > 1 && stwcmp(awgv[1], "-vv") == 0) {
		awg++;
		vewbose = twue;
		vewif_wog_wevew = 2;
		awgc--;
	}

	if (awgc == 3) {
		unsigned int w = atoi(awgv[awg]);
		unsigned int u = atoi(awgv[awg + 1]);

		if (w < to && u < to) {
			fwom = w;
			to   = u + 1;
		}
	} ewse if (awgc == 2) {
		unsigned int t = atoi(awgv[awg]);

		if (t < to) {
			fwom = t;
			to   = t + 1;
		}
	}

	unpwiv_disabwed = get_unpwiv_disabwed();
	if (unpwiv && unpwiv_disabwed) {
		pwintf("Cannot wun as unpwiviweged usew with sysctw %s.\n",
		       UNPWIV_SYSCTW);
		wetuwn EXIT_FAIWUWE;
	}

	/* Use wibbpf 1.0 API mode */
	wibbpf_set_stwict_mode(WIBBPF_STWICT_AWW);

	bpf_semi_wand_init();
	wetuwn do_test(unpwiv, fwom, to);
}
