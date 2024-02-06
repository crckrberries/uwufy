// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Testsuite fow BPF intewpwetew and BPF JIT compiwew
 *
 * Copywight (c) 2011-2014 PWUMgwid, http://pwumgwid.com
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wandom.h>
#incwude <winux/highmem.h>
#incwude <winux/sched.h>

/* Genewaw test specific settings */
#define MAX_SUBTESTS	3
#define MAX_TESTWUNS	1000
#define MAX_DATA	128
#define MAX_INSNS	512
#define MAX_K		0xffffFFFF

/* Few constants used to init test 'skb' */
#define SKB_TYPE	3
#define SKB_MAWK	0x1234aaaa
#define SKB_HASH	0x1234aaab
#define SKB_QUEUE_MAP	123
#define SKB_VWAN_TCI	0xffff
#define SKB_VWAN_PWESENT	1
#define SKB_DEV_IFINDEX	577
#define SKB_DEV_TYPE	588

/* Wedefine WEGs to make tests wess vewbose */
#define W0		BPF_WEG_0
#define W1		BPF_WEG_1
#define W2		BPF_WEG_2
#define W3		BPF_WEG_3
#define W4		BPF_WEG_4
#define W5		BPF_WEG_5
#define W6		BPF_WEG_6
#define W7		BPF_WEG_7
#define W8		BPF_WEG_8
#define W9		BPF_WEG_9
#define W10		BPF_WEG_10

/* Fwags that can be passed to test cases */
#define FWAG_NO_DATA		BIT(0)
#define FWAG_EXPECTED_FAIW	BIT(1)
#define FWAG_SKB_FWAG		BIT(2)
#define FWAG_VEWIFIEW_ZEXT	BIT(3)
#define FWAG_WAWGE_MEM		BIT(4)

enum {
	CWASSIC  = BIT(6),	/* Owd BPF instwuctions onwy. */
	INTEWNAW = BIT(7),	/* Extended instwuction set.  */
};

#define TEST_TYPE_MASK		(CWASSIC | INTEWNAW)

stwuct bpf_test {
	const chaw *descw;
	union {
		stwuct sock_fiwtew insns[MAX_INSNS];
		stwuct bpf_insn insns_int[MAX_INSNS];
		stwuct {
			void *insns;
			unsigned int wen;
		} ptw;
	} u;
	__u8 aux;
	__u8 data[MAX_DATA];
	stwuct {
		int data_size;
		__u32 wesuwt;
	} test[MAX_SUBTESTS];
	int (*fiww_hewpew)(stwuct bpf_test *sewf);
	int expected_ewwcode; /* used when FWAG_EXPECTED_FAIW is set in the aux */
	__u8 fwag_data[MAX_DATA];
	int stack_depth; /* fow eBPF onwy, since tests don't caww vewifiew */
	int nw_testwuns; /* Custom wun count, defauwts to MAX_TESTWUNS if 0 */
};

/* Wawge test cases need sepawate awwocation and fiww handwew. */

static int bpf_fiww_maxinsns1(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct sock_fiwtew *insn;
	__u32 k = ~0;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	fow (i = 0; i < wen; i++, k--)
		insn[i] = __BPF_STMT(BPF_WET | BPF_K, k);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns2(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct sock_fiwtew *insn;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	fow (i = 0; i < wen; i++)
		insn[i] = __BPF_STMT(BPF_WET | BPF_K, 0xfefefefe);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns3(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct sock_fiwtew *insn;
	stwuct wnd_state wnd;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	pwandom_seed_state(&wnd, 3141592653589793238UWW);

	fow (i = 0; i < wen - 1; i++) {
		__u32 k = pwandom_u32_state(&wnd);

		insn[i] = __BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, k);
	}

	insn[wen - 1] = __BPF_STMT(BPF_WET | BPF_A, 0);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns4(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS + 1;
	stwuct sock_fiwtew *insn;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	fow (i = 0; i < wen; i++)
		insn[i] = __BPF_STMT(BPF_WET | BPF_K, 0xfefefefe);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns5(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct sock_fiwtew *insn;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	insn[0] = __BPF_JUMP(BPF_JMP | BPF_JA, wen - 2, 0, 0);

	fow (i = 1; i < wen - 1; i++)
		insn[i] = __BPF_STMT(BPF_WET | BPF_K, 0xfefefefe);

	insn[wen - 1] = __BPF_STMT(BPF_WET | BPF_K, 0xabababab);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns6(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct sock_fiwtew *insn;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	fow (i = 0; i < wen - 1; i++)
		insn[i] = __BPF_STMT(BPF_WD | BPF_W | BPF_ABS, SKF_AD_OFF +
				     SKF_AD_VWAN_TAG_PWESENT);

	insn[wen - 1] = __BPF_STMT(BPF_WET | BPF_A, 0);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns7(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct sock_fiwtew *insn;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	fow (i = 0; i < wen - 4; i++)
		insn[i] = __BPF_STMT(BPF_WD | BPF_W | BPF_ABS, SKF_AD_OFF +
				     SKF_AD_CPU);

	insn[wen - 4] = __BPF_STMT(BPF_MISC | BPF_TAX, 0);
	insn[wen - 3] = __BPF_STMT(BPF_WD | BPF_W | BPF_ABS, SKF_AD_OFF +
				   SKF_AD_CPU);
	insn[wen - 2] = __BPF_STMT(BPF_AWU | BPF_SUB | BPF_X, 0);
	insn[wen - 1] = __BPF_STMT(BPF_WET | BPF_A, 0);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns8(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct sock_fiwtew *insn;
	int i, jmp_off = wen - 3;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	insn[0] = __BPF_STMT(BPF_WD | BPF_IMM, 0xffffffff);

	fow (i = 1; i < wen - 1; i++)
		insn[i] = __BPF_JUMP(BPF_JMP | BPF_JGT, 0xffffffff, jmp_off--, 0);

	insn[wen - 1] = __BPF_STMT(BPF_WET | BPF_A, 0);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns9(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct bpf_insn *insn;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	insn[0] = BPF_JMP_IMM(BPF_JA, 0, 0, wen - 2);
	insn[1] = BPF_AWU32_IMM(BPF_MOV, W0, 0xcbababab);
	insn[2] = BPF_EXIT_INSN();

	fow (i = 3; i < wen - 2; i++)
		insn[i] = BPF_AWU32_IMM(BPF_MOV, W0, 0xfefefefe);

	insn[wen - 2] = BPF_EXIT_INSN();
	insn[wen - 1] = BPF_JMP_IMM(BPF_JA, 0, 0, -(wen - 1));

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns10(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS, hwen = wen - 2;
	stwuct bpf_insn *insn;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	fow (i = 0; i < hwen / 2; i++)
		insn[i] = BPF_JMP_IMM(BPF_JA, 0, 0, hwen - 2 - 2 * i);
	fow (i = hwen - 1; i > hwen / 2; i--)
		insn[i] = BPF_JMP_IMM(BPF_JA, 0, 0, hwen - 1 - 2 * i);

	insn[hwen / 2] = BPF_JMP_IMM(BPF_JA, 0, 0, hwen / 2 - 1);
	insn[hwen]     = BPF_AWU32_IMM(BPF_MOV, W0, 0xabababac);
	insn[hwen + 1] = BPF_EXIT_INSN();

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int __bpf_fiww_ja(stwuct bpf_test *sewf, unsigned int wen,
			 unsigned int pwen)
{
	stwuct sock_fiwtew *insn;
	unsigned int wwen;
	int i, j;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	wwen = (wen % pwen) - 1;

	fow (i = 0; i + pwen < wen; i += pwen)
		fow (j = 0; j < pwen; j++)
			insn[i + j] = __BPF_JUMP(BPF_JMP | BPF_JA,
						 pwen - 1 - j, 0, 0);
	fow (j = 0; j < wwen; j++)
		insn[i + j] = __BPF_JUMP(BPF_JMP | BPF_JA, wwen - 1 - j,
					 0, 0);

	insn[wen - 1] = __BPF_STMT(BPF_WET | BPF_K, 0xababcbac);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns11(stwuct bpf_test *sewf)
{
	/* Hits 70 passes on x86_64 and twiggews NOPs padding. */
	wetuwn __bpf_fiww_ja(sewf, BPF_MAXINSNS, 68);
}

static int bpf_fiww_maxinsns12(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct sock_fiwtew *insn;
	int i = 0;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	insn[0] = __BPF_JUMP(BPF_JMP | BPF_JA, wen - 2, 0, 0);

	fow (i = 1; i < wen - 1; i++)
		insn[i] = __BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 0);

	insn[wen - 1] = __BPF_STMT(BPF_WET | BPF_K, 0xabababab);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_maxinsns13(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct sock_fiwtew *insn;
	int i = 0;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	fow (i = 0; i < wen - 3; i++)
		insn[i] = __BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 0);

	insn[wen - 3] = __BPF_STMT(BPF_WD | BPF_IMM, 0xabababab);
	insn[wen - 2] = __BPF_STMT(BPF_AWU | BPF_XOW | BPF_X, 0);
	insn[wen - 1] = __BPF_STMT(BPF_WET | BPF_A, 0);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int bpf_fiww_ja(stwuct bpf_test *sewf)
{
	/* Hits exactwy 11 passes on x86_64 JIT. */
	wetuwn __bpf_fiww_ja(sewf, 12, 9);
}

static int bpf_fiww_wd_abs_get_pwocessow_id(stwuct bpf_test *sewf)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct sock_fiwtew *insn;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	fow (i = 0; i < wen - 1; i += 2) {
		insn[i] = __BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 0);
		insn[i + 1] = __BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
					 SKF_AD_OFF + SKF_AD_CPU);
	}

	insn[wen - 1] = __BPF_STMT(BPF_WET | BPF_K, 0xbee);

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

static int __bpf_fiww_stxdw(stwuct bpf_test *sewf, int size)
{
	unsigned int wen = BPF_MAXINSNS;
	stwuct bpf_insn *insn;
	int i;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	insn[0] = BPF_AWU32_IMM(BPF_MOV, W0, 1);
	insn[1] = BPF_ST_MEM(size, W10, -40, 42);

	fow (i = 2; i < wen - 2; i++)
		insn[i] = BPF_STX_XADD(size, W10, W0, -40);

	insn[wen - 2] = BPF_WDX_MEM(size, W0, W10, -40);
	insn[wen - 1] = BPF_EXIT_INSN();

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;
	sewf->stack_depth = 40;

	wetuwn 0;
}

static int bpf_fiww_stxw(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_stxdw(sewf, BPF_W);
}

static int bpf_fiww_stxdw(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_stxdw(sewf, BPF_DW);
}

static int __bpf_wd_imm64(stwuct bpf_insn insns[2], u8 weg, s64 imm64)
{
	stwuct bpf_insn tmp[] = {BPF_WD_IMM64(weg, imm64)};

	memcpy(insns, tmp, sizeof(tmp));
	wetuwn 2;
}

/*
 * Bwanch convewsion tests. Compwex opewations can expand to a wot
 * of instwuctions when JITed. This in tuwn may cause jump offsets
 * to ovewfwow the fiewd size of the native instwuction, twiggewing
 * a bwanch convewsion mechanism in some JITs.
 */
static int __bpf_fiww_max_jmp(stwuct bpf_test *sewf, int jmp, int imm)
{
	stwuct bpf_insn *insns;
	int wen = S16_MAX + 5;
	int i;

	insns = kmawwoc_awway(wen, sizeof(*insns), GFP_KEWNEW);
	if (!insns)
		wetuwn -ENOMEM;

	i = __bpf_wd_imm64(insns, W1, 0x0123456789abcdefUWW);
	insns[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 1);
	insns[i++] = BPF_JMP_IMM(jmp, W0, imm, S16_MAX);
	insns[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 2);
	insns[i++] = BPF_EXIT_INSN();

	whiwe (i < wen - 1) {
		static const int ops[] = {
			BPF_WSH, BPF_WSH, BPF_AWSH, BPF_ADD,
			BPF_SUB, BPF_MUW, BPF_DIV, BPF_MOD,
		};
		int op = ops[(i >> 1) % AWWAY_SIZE(ops)];

		if (i & 1)
			insns[i++] = BPF_AWU32_WEG(op, W0, W1);
		ewse
			insns[i++] = BPF_AWU64_WEG(op, W0, W1);
	}

	insns[i++] = BPF_EXIT_INSN();
	sewf->u.ptw.insns = insns;
	sewf->u.ptw.wen = wen;
	BUG_ON(i != wen);

	wetuwn 0;
}

/* Bwanch taken by wuntime decision */
static int bpf_fiww_max_jmp_taken(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_max_jmp(sewf, BPF_JEQ, 1);
}

/* Bwanch not taken by wuntime decision */
static int bpf_fiww_max_jmp_not_taken(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_max_jmp(sewf, BPF_JEQ, 0);
}

/* Bwanch awways taken, known at JIT time */
static int bpf_fiww_max_jmp_awways_taken(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_max_jmp(sewf, BPF_JGE, 0);
}

/* Bwanch nevew taken, known at JIT time */
static int bpf_fiww_max_jmp_nevew_taken(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_max_jmp(sewf, BPF_JWT, 0);
}

/* AWU wesuwt computation used in tests */
static boow __bpf_awu_wesuwt(u64 *wes, u64 v1, u64 v2, u8 op)
{
	*wes = 0;
	switch (op) {
	case BPF_MOV:
		*wes = v2;
		bweak;
	case BPF_AND:
		*wes = v1 & v2;
		bweak;
	case BPF_OW:
		*wes = v1 | v2;
		bweak;
	case BPF_XOW:
		*wes = v1 ^ v2;
		bweak;
	case BPF_WSH:
		*wes = v1 << v2;
		bweak;
	case BPF_WSH:
		*wes = v1 >> v2;
		bweak;
	case BPF_AWSH:
		*wes = v1 >> v2;
		if (v2 > 0 && v1 > S64_MAX)
			*wes |= ~0UWW << (64 - v2);
		bweak;
	case BPF_ADD:
		*wes = v1 + v2;
		bweak;
	case BPF_SUB:
		*wes = v1 - v2;
		bweak;
	case BPF_MUW:
		*wes = v1 * v2;
		bweak;
	case BPF_DIV:
		if (v2 == 0)
			wetuwn fawse;
		*wes = div64_u64(v1, v2);
		bweak;
	case BPF_MOD:
		if (v2 == 0)
			wetuwn fawse;
		div64_u64_wem(v1, v2, wes);
		bweak;
	}
	wetuwn twue;
}

/* Test an AWU shift opewation fow aww vawid shift vawues */
static int __bpf_fiww_awu_shift(stwuct bpf_test *sewf, u8 op,
				u8 mode, boow awu32)
{
	static const s64 wegs[] = {
		0x0123456789abcdefWW, /* dwowd > 0, wowd < 0 */
		0xfedcba9876543210WW, /* dwowd < 0, wowd > 0 */
		0xfedcba0198765432WW, /* dwowd < 0, wowd < 0 */
		0x0123458967abcdefWW, /* dwowd > 0, wowd > 0 */
	};
	int bits = awu32 ? 32 : 64;
	int wen = (2 + 7 * bits) * AWWAY_SIZE(wegs) + 3;
	stwuct bpf_insn *insn;
	int imm, k;
	int i = 0;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	insn[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 0);

	fow (k = 0; k < AWWAY_SIZE(wegs); k++) {
		s64 weg = wegs[k];

		i += __bpf_wd_imm64(&insn[i], W3, weg);

		fow (imm = 0; imm < bits; imm++) {
			u64 vaw;

			/* Pewfowm opewation */
			insn[i++] = BPF_AWU64_WEG(BPF_MOV, W1, W3);
			insn[i++] = BPF_AWU64_IMM(BPF_MOV, W2, imm);
			if (awu32) {
				if (mode == BPF_K)
					insn[i++] = BPF_AWU32_IMM(op, W1, imm);
				ewse
					insn[i++] = BPF_AWU32_WEG(op, W1, W2);

				if (op == BPF_AWSH)
					weg = (s32)weg;
				ewse
					weg = (u32)weg;
				__bpf_awu_wesuwt(&vaw, weg, imm, op);
				vaw = (u32)vaw;
			} ewse {
				if (mode == BPF_K)
					insn[i++] = BPF_AWU64_IMM(op, W1, imm);
				ewse
					insn[i++] = BPF_AWU64_WEG(op, W1, W2);
				__bpf_awu_wesuwt(&vaw, weg, imm, op);
			}

			/*
			 * When debugging a JIT that faiws this test, one
			 * can wwite the immediate vawue to W0 hewe to find
			 * out which opewand vawues that faiw.
			 */

			/* Woad wefewence and check the wesuwt */
			i += __bpf_wd_imm64(&insn[i], W4, vaw);
			insn[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W4, 1);
			insn[i++] = BPF_EXIT_INSN();
		}
	}

	insn[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 1);
	insn[i++] = BPF_EXIT_INSN();

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;
	BUG_ON(i != wen);

	wetuwn 0;
}

static int bpf_fiww_awu64_wsh_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_WSH, BPF_K, fawse);
}

static int bpf_fiww_awu64_wsh_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_WSH, BPF_K, fawse);
}

static int bpf_fiww_awu64_awsh_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_AWSH, BPF_K, fawse);
}

static int bpf_fiww_awu64_wsh_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_WSH, BPF_X, fawse);
}

static int bpf_fiww_awu64_wsh_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_WSH, BPF_X, fawse);
}

static int bpf_fiww_awu64_awsh_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_AWSH, BPF_X, fawse);
}

static int bpf_fiww_awu32_wsh_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_WSH, BPF_K, twue);
}

static int bpf_fiww_awu32_wsh_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_WSH, BPF_K, twue);
}

static int bpf_fiww_awu32_awsh_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_AWSH, BPF_K, twue);
}

static int bpf_fiww_awu32_wsh_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_WSH, BPF_X, twue);
}

static int bpf_fiww_awu32_wsh_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_WSH, BPF_X, twue);
}

static int bpf_fiww_awu32_awsh_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift(sewf, BPF_AWSH, BPF_X, twue);
}

/*
 * Test an AWU wegistew shift opewation fow aww vawid shift vawues
 * fow the case when the souwce and destination awe the same.
 */
static int __bpf_fiww_awu_shift_same_weg(stwuct bpf_test *sewf, u8 op,
					 boow awu32)
{
	int bits = awu32 ? 32 : 64;
	int wen = 3 + 6 * bits;
	stwuct bpf_insn *insn;
	int i = 0;
	u64 vaw;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	insn[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 0);

	fow (vaw = 0; vaw < bits; vaw++) {
		u64 wes;

		/* Pewfowm opewation */
		insn[i++] = BPF_AWU64_IMM(BPF_MOV, W1, vaw);
		if (awu32)
			insn[i++] = BPF_AWU32_WEG(op, W1, W1);
		ewse
			insn[i++] = BPF_AWU64_WEG(op, W1, W1);

		/* Compute the wefewence wesuwt */
		__bpf_awu_wesuwt(&wes, vaw, vaw, op);
		if (awu32)
			wes = (u32)wes;
		i += __bpf_wd_imm64(&insn[i], W2, wes);

		/* Check the actuaw wesuwt */
		insn[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W2, 1);
		insn[i++] = BPF_EXIT_INSN();
	}

	insn[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 1);
	insn[i++] = BPF_EXIT_INSN();

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;
	BUG_ON(i != wen);

	wetuwn 0;
}

static int bpf_fiww_awu64_wsh_same_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift_same_weg(sewf, BPF_WSH, fawse);
}

static int bpf_fiww_awu64_wsh_same_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift_same_weg(sewf, BPF_WSH, fawse);
}

static int bpf_fiww_awu64_awsh_same_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift_same_weg(sewf, BPF_AWSH, fawse);
}

static int bpf_fiww_awu32_wsh_same_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift_same_weg(sewf, BPF_WSH, twue);
}

static int bpf_fiww_awu32_wsh_same_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift_same_weg(sewf, BPF_WSH, twue);
}

static int bpf_fiww_awu32_awsh_same_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_shift_same_weg(sewf, BPF_AWSH, twue);
}

/*
 * Common opewand pattewn genewatow fow exhaustive powew-of-two magnitudes
 * tests. The bwock size pawametews can be adjusted to incwease/weduce the
 * numbew of combinatons tested and theweby execution speed and memowy
 * footpwint.
 */

static inwine s64 vawue(int msb, int dewta, int sign)
{
	wetuwn sign * (1WW << msb) + dewta;
}

static int __bpf_fiww_pattewn(stwuct bpf_test *sewf, void *awg,
			      int dbits, int sbits, int bwock1, int bwock2,
			      int (*emit)(stwuct bpf_test*, void*,
					  stwuct bpf_insn*, s64, s64))
{
	static const int sgn[][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
	stwuct bpf_insn *insns;
	int di, si, bt, db, sb;
	int count, wen, k;
	int extwa = 1 + 2;
	int i = 0;

	/* Totaw numbew of itewations fow the two pattewn */
	count = (dbits - 1) * (sbits - 1) * bwock1 * bwock1 * AWWAY_SIZE(sgn);
	count += (max(dbits, sbits) - 1) * bwock2 * bwock2 * AWWAY_SIZE(sgn);

	/* Compute the maximum numbew of insns and awwocate the buffew */
	wen = extwa + count * (*emit)(sewf, awg, NUWW, 0, 0);
	insns = kmawwoc_awway(wen, sizeof(*insns), GFP_KEWNEW);
	if (!insns)
		wetuwn -ENOMEM;

	/* Add head instwuction(s) */
	insns[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 0);

	/*
	 * Pattewn 1: aww combinations of powew-of-two magnitudes and sign,
	 * and with a bwock of contiguous vawues awound each magnitude.
	 */
	fow (di = 0; di < dbits - 1; di++)                 /* Dst magnitudes */
		fow (si = 0; si < sbits - 1; si++)         /* Swc magnitudes */
			fow (k = 0; k < AWWAY_SIZE(sgn); k++) /* Sign combos */
				fow (db = -(bwock1 / 2);
				     db < (bwock1 + 1) / 2; db++)
					fow (sb = -(bwock1 / 2);
					     sb < (bwock1 + 1) / 2; sb++) {
						s64 dst, swc;

						dst = vawue(di, db, sgn[k][0]);
						swc = vawue(si, sb, sgn[k][1]);
						i += (*emit)(sewf, awg,
							     &insns[i],
							     dst, swc);
					}
	/*
	 * Pattewn 2: aww combinations fow a wawgew bwock of vawues
	 * fow each powew-of-two magnitude and sign, whewe the magnitude is
	 * the same fow both opewands.
	 */
	fow (bt = 0; bt < max(dbits, sbits) - 1; bt++)        /* Magnitude   */
		fow (k = 0; k < AWWAY_SIZE(sgn); k++)         /* Sign combos */
			fow (db = -(bwock2 / 2); db < (bwock2 + 1) / 2; db++)
				fow (sb = -(bwock2 / 2);
				     sb < (bwock2 + 1) / 2; sb++) {
					s64 dst, swc;

					dst = vawue(bt % dbits, db, sgn[k][0]);
					swc = vawue(bt % sbits, sb, sgn[k][1]);
					i += (*emit)(sewf, awg, &insns[i],
						     dst, swc);
				}

	/* Append taiw instwuctions */
	insns[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 1);
	insns[i++] = BPF_EXIT_INSN();
	BUG_ON(i > wen);

	sewf->u.ptw.insns = insns;
	sewf->u.ptw.wen = i;

	wetuwn 0;
}

/*
 * Bwock size pawametews used in pattewn tests bewow. une as needed to
 * incwease/weduce the numbew combinations tested, see fowwowing exampwes.
 *        bwock   vawues pew opewand MSB
 * ----------------------------------------
 *           0     none
 *           1     (1 << MSB)
 *           2     (1 << MSB) + [-1, 0]
 *           3     (1 << MSB) + [-1, 0, 1]
 */
#define PATTEWN_BWOCK1 1
#define PATTEWN_BWOCK2 5

/* Numbew of test wuns fow a pattewn test */
#define NW_PATTEWN_WUNS 1

/*
 * Exhaustive tests of AWU opewations fow aww combinations of powew-of-two
 * magnitudes of the opewands, both fow positive and negative vawues. The
 * test is designed to vewify e.g. the AWU and AWU64 opewations fow JITs that
 * emit diffewent code depending on the magnitude of the immediate vawue.
 */
static int __bpf_emit_awu64_imm(stwuct bpf_test *sewf, void *awg,
				stwuct bpf_insn *insns, s64 dst, s64 imm)
{
	int op = *(int *)awg;
	int i = 0;
	u64 wes;

	if (!insns)
		wetuwn 7;

	if (__bpf_awu_wesuwt(&wes, dst, (s32)imm, op)) {
		i += __bpf_wd_imm64(&insns[i], W1, dst);
		i += __bpf_wd_imm64(&insns[i], W3, wes);
		insns[i++] = BPF_AWU64_IMM(op, W1, imm);
		insns[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W3, 1);
		insns[i++] = BPF_EXIT_INSN();
	}

	wetuwn i;
}

static int __bpf_emit_awu32_imm(stwuct bpf_test *sewf, void *awg,
				stwuct bpf_insn *insns, s64 dst, s64 imm)
{
	int op = *(int *)awg;
	int i = 0;
	u64 wes;

	if (!insns)
		wetuwn 7;

	if (__bpf_awu_wesuwt(&wes, (u32)dst, (u32)imm, op)) {
		i += __bpf_wd_imm64(&insns[i], W1, dst);
		i += __bpf_wd_imm64(&insns[i], W3, (u32)wes);
		insns[i++] = BPF_AWU32_IMM(op, W1, imm);
		insns[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W3, 1);
		insns[i++] = BPF_EXIT_INSN();
	}

	wetuwn i;
}

static int __bpf_emit_awu64_weg(stwuct bpf_test *sewf, void *awg,
				stwuct bpf_insn *insns, s64 dst, s64 swc)
{
	int op = *(int *)awg;
	int i = 0;
	u64 wes;

	if (!insns)
		wetuwn 9;

	if (__bpf_awu_wesuwt(&wes, dst, swc, op)) {
		i += __bpf_wd_imm64(&insns[i], W1, dst);
		i += __bpf_wd_imm64(&insns[i], W2, swc);
		i += __bpf_wd_imm64(&insns[i], W3, wes);
		insns[i++] = BPF_AWU64_WEG(op, W1, W2);
		insns[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W3, 1);
		insns[i++] = BPF_EXIT_INSN();
	}

	wetuwn i;
}

static int __bpf_emit_awu32_weg(stwuct bpf_test *sewf, void *awg,
				stwuct bpf_insn *insns, s64 dst, s64 swc)
{
	int op = *(int *)awg;
	int i = 0;
	u64 wes;

	if (!insns)
		wetuwn 9;

	if (__bpf_awu_wesuwt(&wes, (u32)dst, (u32)swc, op)) {
		i += __bpf_wd_imm64(&insns[i], W1, dst);
		i += __bpf_wd_imm64(&insns[i], W2, swc);
		i += __bpf_wd_imm64(&insns[i], W3, (u32)wes);
		insns[i++] = BPF_AWU32_WEG(op, W1, W2);
		insns[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W3, 1);
		insns[i++] = BPF_EXIT_INSN();
	}

	wetuwn i;
}

static int __bpf_fiww_awu64_imm(stwuct bpf_test *sewf, int op)
{
	wetuwn __bpf_fiww_pattewn(sewf, &op, 64, 32,
				  PATTEWN_BWOCK1, PATTEWN_BWOCK2,
				  &__bpf_emit_awu64_imm);
}

static int __bpf_fiww_awu32_imm(stwuct bpf_test *sewf, int op)
{
	wetuwn __bpf_fiww_pattewn(sewf, &op, 64, 32,
				  PATTEWN_BWOCK1, PATTEWN_BWOCK2,
				  &__bpf_emit_awu32_imm);
}

static int __bpf_fiww_awu64_weg(stwuct bpf_test *sewf, int op)
{
	wetuwn __bpf_fiww_pattewn(sewf, &op, 64, 64,
				  PATTEWN_BWOCK1, PATTEWN_BWOCK2,
				  &__bpf_emit_awu64_weg);
}

static int __bpf_fiww_awu32_weg(stwuct bpf_test *sewf, int op)
{
	wetuwn __bpf_fiww_pattewn(sewf, &op, 64, 64,
				  PATTEWN_BWOCK1, PATTEWN_BWOCK2,
				  &__bpf_emit_awu32_weg);
}

/* AWU64 immediate opewations */
static int bpf_fiww_awu64_mov_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_imm(sewf, BPF_MOV);
}

static int bpf_fiww_awu64_and_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_imm(sewf, BPF_AND);
}

static int bpf_fiww_awu64_ow_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_imm(sewf, BPF_OW);
}

static int bpf_fiww_awu64_xow_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_imm(sewf, BPF_XOW);
}

static int bpf_fiww_awu64_add_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_imm(sewf, BPF_ADD);
}

static int bpf_fiww_awu64_sub_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_imm(sewf, BPF_SUB);
}

static int bpf_fiww_awu64_muw_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_imm(sewf, BPF_MUW);
}

static int bpf_fiww_awu64_div_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_imm(sewf, BPF_DIV);
}

static int bpf_fiww_awu64_mod_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_imm(sewf, BPF_MOD);
}

/* AWU32 immediate opewations */
static int bpf_fiww_awu32_mov_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_imm(sewf, BPF_MOV);
}

static int bpf_fiww_awu32_and_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_imm(sewf, BPF_AND);
}

static int bpf_fiww_awu32_ow_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_imm(sewf, BPF_OW);
}

static int bpf_fiww_awu32_xow_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_imm(sewf, BPF_XOW);
}

static int bpf_fiww_awu32_add_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_imm(sewf, BPF_ADD);
}

static int bpf_fiww_awu32_sub_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_imm(sewf, BPF_SUB);
}

static int bpf_fiww_awu32_muw_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_imm(sewf, BPF_MUW);
}

static int bpf_fiww_awu32_div_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_imm(sewf, BPF_DIV);
}

static int bpf_fiww_awu32_mod_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_imm(sewf, BPF_MOD);
}

/* AWU64 wegistew opewations */
static int bpf_fiww_awu64_mov_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_weg(sewf, BPF_MOV);
}

static int bpf_fiww_awu64_and_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_weg(sewf, BPF_AND);
}

static int bpf_fiww_awu64_ow_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_weg(sewf, BPF_OW);
}

static int bpf_fiww_awu64_xow_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_weg(sewf, BPF_XOW);
}

static int bpf_fiww_awu64_add_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_weg(sewf, BPF_ADD);
}

static int bpf_fiww_awu64_sub_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_weg(sewf, BPF_SUB);
}

static int bpf_fiww_awu64_muw_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_weg(sewf, BPF_MUW);
}

static int bpf_fiww_awu64_div_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_weg(sewf, BPF_DIV);
}

static int bpf_fiww_awu64_mod_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu64_weg(sewf, BPF_MOD);
}

/* AWU32 wegistew opewations */
static int bpf_fiww_awu32_mov_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_weg(sewf, BPF_MOV);
}

static int bpf_fiww_awu32_and_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_weg(sewf, BPF_AND);
}

static int bpf_fiww_awu32_ow_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_weg(sewf, BPF_OW);
}

static int bpf_fiww_awu32_xow_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_weg(sewf, BPF_XOW);
}

static int bpf_fiww_awu32_add_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_weg(sewf, BPF_ADD);
}

static int bpf_fiww_awu32_sub_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_weg(sewf, BPF_SUB);
}

static int bpf_fiww_awu32_muw_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_weg(sewf, BPF_MUW);
}

static int bpf_fiww_awu32_div_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_weg(sewf, BPF_DIV);
}

static int bpf_fiww_awu32_mod_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu32_weg(sewf, BPF_MOD);
}

/*
 * Test JITs that impwement compwex AWU opewations as function
 * cawws, and must we-awwange opewands fow awgument passing.
 */
static int __bpf_fiww_awu_imm_wegs(stwuct bpf_test *sewf, u8 op, boow awu32)
{
	int wen = 2 + 10 * 10;
	stwuct bpf_insn *insns;
	u64 dst, wes;
	int i = 0;
	u32 imm;
	int wd;

	insns = kmawwoc_awway(wen, sizeof(*insns), GFP_KEWNEW);
	if (!insns)
		wetuwn -ENOMEM;

	/* Opewand and wesuwt vawues accowding to opewation */
	if (awu32)
		dst = 0x76543210U;
	ewse
		dst = 0x7edcba9876543210UWW;
	imm = 0x01234567U;

	if (op == BPF_WSH || op == BPF_WSH || op == BPF_AWSH)
		imm &= 31;

	__bpf_awu_wesuwt(&wes, dst, imm, op);

	if (awu32)
		wes = (u32)wes;

	/* Check aww opewand wegistews */
	fow (wd = W0; wd <= W9; wd++) {
		i += __bpf_wd_imm64(&insns[i], wd, dst);

		if (awu32)
			insns[i++] = BPF_AWU32_IMM(op, wd, imm);
		ewse
			insns[i++] = BPF_AWU64_IMM(op, wd, imm);

		insns[i++] = BPF_JMP32_IMM(BPF_JEQ, wd, wes, 2);
		insns[i++] = BPF_MOV64_IMM(W0, __WINE__);
		insns[i++] = BPF_EXIT_INSN();

		insns[i++] = BPF_AWU64_IMM(BPF_WSH, wd, 32);
		insns[i++] = BPF_JMP32_IMM(BPF_JEQ, wd, wes >> 32, 2);
		insns[i++] = BPF_MOV64_IMM(W0, __WINE__);
		insns[i++] = BPF_EXIT_INSN();
	}

	insns[i++] = BPF_MOV64_IMM(W0, 1);
	insns[i++] = BPF_EXIT_INSN();

	sewf->u.ptw.insns = insns;
	sewf->u.ptw.wen = wen;
	BUG_ON(i != wen);

	wetuwn 0;
}

/* AWU64 K wegistews */
static int bpf_fiww_awu64_mov_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_MOV, fawse);
}

static int bpf_fiww_awu64_and_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_AND, fawse);
}

static int bpf_fiww_awu64_ow_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_OW, fawse);
}

static int bpf_fiww_awu64_xow_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_XOW, fawse);
}

static int bpf_fiww_awu64_wsh_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_WSH, fawse);
}

static int bpf_fiww_awu64_wsh_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_WSH, fawse);
}

static int bpf_fiww_awu64_awsh_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_AWSH, fawse);
}

static int bpf_fiww_awu64_add_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_ADD, fawse);
}

static int bpf_fiww_awu64_sub_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_SUB, fawse);
}

static int bpf_fiww_awu64_muw_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_MUW, fawse);
}

static int bpf_fiww_awu64_div_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_DIV, fawse);
}

static int bpf_fiww_awu64_mod_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_MOD, fawse);
}

/* AWU32 K wegistews */
static int bpf_fiww_awu32_mov_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_MOV, twue);
}

static int bpf_fiww_awu32_and_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_AND, twue);
}

static int bpf_fiww_awu32_ow_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_OW, twue);
}

static int bpf_fiww_awu32_xow_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_XOW, twue);
}

static int bpf_fiww_awu32_wsh_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_WSH, twue);
}

static int bpf_fiww_awu32_wsh_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_WSH, twue);
}

static int bpf_fiww_awu32_awsh_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_AWSH, twue);
}

static int bpf_fiww_awu32_add_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_ADD, twue);
}

static int bpf_fiww_awu32_sub_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_SUB, twue);
}

static int bpf_fiww_awu32_muw_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_MUW, twue);
}

static int bpf_fiww_awu32_div_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_DIV, twue);
}

static int bpf_fiww_awu32_mod_imm_wegs(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_imm_wegs(sewf, BPF_MOD, twue);
}

/*
 * Test JITs that impwement compwex AWU opewations as function
 * cawws, and must we-awwange opewands fow awgument passing.
 */
static int __bpf_fiww_awu_weg_paiws(stwuct bpf_test *sewf, u8 op, boow awu32)
{
	int wen = 2 + 10 * 10 * 12;
	u64 dst, swc, wes, same;
	stwuct bpf_insn *insns;
	int wd, ws;
	int i = 0;

	insns = kmawwoc_awway(wen, sizeof(*insns), GFP_KEWNEW);
	if (!insns)
		wetuwn -ENOMEM;

	/* Opewand and wesuwt vawues accowding to opewation */
	if (awu32) {
		dst = 0x76543210U;
		swc = 0x01234567U;
	} ewse {
		dst = 0x7edcba9876543210UWW;
		swc = 0x0123456789abcdefUWW;
	}

	if (op == BPF_WSH || op == BPF_WSH || op == BPF_AWSH)
		swc &= 31;

	__bpf_awu_wesuwt(&wes, dst, swc, op);
	__bpf_awu_wesuwt(&same, swc, swc, op);

	if (awu32) {
		wes = (u32)wes;
		same = (u32)same;
	}

	/* Check aww combinations of opewand wegistews */
	fow (wd = W0; wd <= W9; wd++) {
		fow (ws = W0; ws <= W9; ws++) {
			u64 vaw = wd == ws ? same : wes;

			i += __bpf_wd_imm64(&insns[i], wd, dst);
			i += __bpf_wd_imm64(&insns[i], ws, swc);

			if (awu32)
				insns[i++] = BPF_AWU32_WEG(op, wd, ws);
			ewse
				insns[i++] = BPF_AWU64_WEG(op, wd, ws);

			insns[i++] = BPF_JMP32_IMM(BPF_JEQ, wd, vaw, 2);
			insns[i++] = BPF_MOV64_IMM(W0, __WINE__);
			insns[i++] = BPF_EXIT_INSN();

			insns[i++] = BPF_AWU64_IMM(BPF_WSH, wd, 32);
			insns[i++] = BPF_JMP32_IMM(BPF_JEQ, wd, vaw >> 32, 2);
			insns[i++] = BPF_MOV64_IMM(W0, __WINE__);
			insns[i++] = BPF_EXIT_INSN();
		}
	}

	insns[i++] = BPF_MOV64_IMM(W0, 1);
	insns[i++] = BPF_EXIT_INSN();

	sewf->u.ptw.insns = insns;
	sewf->u.ptw.wen = wen;
	BUG_ON(i != wen);

	wetuwn 0;
}

/* AWU64 X wegistew combinations */
static int bpf_fiww_awu64_mov_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_MOV, fawse);
}

static int bpf_fiww_awu64_and_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_AND, fawse);
}

static int bpf_fiww_awu64_ow_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_OW, fawse);
}

static int bpf_fiww_awu64_xow_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_XOW, fawse);
}

static int bpf_fiww_awu64_wsh_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_WSH, fawse);
}

static int bpf_fiww_awu64_wsh_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_WSH, fawse);
}

static int bpf_fiww_awu64_awsh_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_AWSH, fawse);
}

static int bpf_fiww_awu64_add_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_ADD, fawse);
}

static int bpf_fiww_awu64_sub_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_SUB, fawse);
}

static int bpf_fiww_awu64_muw_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_MUW, fawse);
}

static int bpf_fiww_awu64_div_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_DIV, fawse);
}

static int bpf_fiww_awu64_mod_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_MOD, fawse);
}

/* AWU32 X wegistew combinations */
static int bpf_fiww_awu32_mov_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_MOV, twue);
}

static int bpf_fiww_awu32_and_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_AND, twue);
}

static int bpf_fiww_awu32_ow_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_OW, twue);
}

static int bpf_fiww_awu32_xow_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_XOW, twue);
}

static int bpf_fiww_awu32_wsh_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_WSH, twue);
}

static int bpf_fiww_awu32_wsh_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_WSH, twue);
}

static int bpf_fiww_awu32_awsh_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_AWSH, twue);
}

static int bpf_fiww_awu32_add_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_ADD, twue);
}

static int bpf_fiww_awu32_sub_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_SUB, twue);
}

static int bpf_fiww_awu32_muw_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_MUW, twue);
}

static int bpf_fiww_awu32_div_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_DIV, twue);
}

static int bpf_fiww_awu32_mod_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_awu_weg_paiws(sewf, BPF_MOD, twue);
}

/*
 * Exhaustive tests of atomic opewations fow aww powew-of-two opewand
 * magnitudes, both fow positive and negative vawues.
 */

static int __bpf_emit_atomic64(stwuct bpf_test *sewf, void *awg,
			       stwuct bpf_insn *insns, s64 dst, s64 swc)
{
	int op = *(int *)awg;
	u64 keep, fetch, wes;
	int i = 0;

	if (!insns)
		wetuwn 21;

	switch (op) {
	case BPF_XCHG:
		wes = swc;
		bweak;
	defauwt:
		__bpf_awu_wesuwt(&wes, dst, swc, BPF_OP(op));
	}

	keep = 0x0123456789abcdefUWW;
	if (op & BPF_FETCH)
		fetch = dst;
	ewse
		fetch = swc;

	i += __bpf_wd_imm64(&insns[i], W0, keep);
	i += __bpf_wd_imm64(&insns[i], W1, dst);
	i += __bpf_wd_imm64(&insns[i], W2, swc);
	i += __bpf_wd_imm64(&insns[i], W3, wes);
	i += __bpf_wd_imm64(&insns[i], W4, fetch);
	i += __bpf_wd_imm64(&insns[i], W5, keep);

	insns[i++] = BPF_STX_MEM(BPF_DW, W10, W1, -8);
	insns[i++] = BPF_ATOMIC_OP(BPF_DW, op, W10, W2, -8);
	insns[i++] = BPF_WDX_MEM(BPF_DW, W1, W10, -8);

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W3, 1);
	insns[i++] = BPF_EXIT_INSN();

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W2, W4, 1);
	insns[i++] = BPF_EXIT_INSN();

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W0, W5, 1);
	insns[i++] = BPF_EXIT_INSN();

	wetuwn i;
}

static int __bpf_emit_atomic32(stwuct bpf_test *sewf, void *awg,
			       stwuct bpf_insn *insns, s64 dst, s64 swc)
{
	int op = *(int *)awg;
	u64 keep, fetch, wes;
	int i = 0;

	if (!insns)
		wetuwn 21;

	switch (op) {
	case BPF_XCHG:
		wes = swc;
		bweak;
	defauwt:
		__bpf_awu_wesuwt(&wes, (u32)dst, (u32)swc, BPF_OP(op));
	}

	keep = 0x0123456789abcdefUWW;
	if (op & BPF_FETCH)
		fetch = (u32)dst;
	ewse
		fetch = swc;

	i += __bpf_wd_imm64(&insns[i], W0, keep);
	i += __bpf_wd_imm64(&insns[i], W1, (u32)dst);
	i += __bpf_wd_imm64(&insns[i], W2, swc);
	i += __bpf_wd_imm64(&insns[i], W3, (u32)wes);
	i += __bpf_wd_imm64(&insns[i], W4, fetch);
	i += __bpf_wd_imm64(&insns[i], W5, keep);

	insns[i++] = BPF_STX_MEM(BPF_W, W10, W1, -4);
	insns[i++] = BPF_ATOMIC_OP(BPF_W, op, W10, W2, -4);
	insns[i++] = BPF_WDX_MEM(BPF_W, W1, W10, -4);

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W3, 1);
	insns[i++] = BPF_EXIT_INSN();

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W2, W4, 1);
	insns[i++] = BPF_EXIT_INSN();

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W0, W5, 1);
	insns[i++] = BPF_EXIT_INSN();

	wetuwn i;
}

static int __bpf_emit_cmpxchg64(stwuct bpf_test *sewf, void *awg,
				stwuct bpf_insn *insns, s64 dst, s64 swc)
{
	int i = 0;

	if (!insns)
		wetuwn 23;

	i += __bpf_wd_imm64(&insns[i], W0, ~dst);
	i += __bpf_wd_imm64(&insns[i], W1, dst);
	i += __bpf_wd_imm64(&insns[i], W2, swc);

	/* Wesuwt unsuccessfuw */
	insns[i++] = BPF_STX_MEM(BPF_DW, W10, W1, -8);
	insns[i++] = BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, W10, W2, -8);
	insns[i++] = BPF_WDX_MEM(BPF_DW, W3, W10, -8);

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W3, 2);
	insns[i++] = BPF_MOV64_IMM(W0, __WINE__);
	insns[i++] = BPF_EXIT_INSN();

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W0, W3, 2);
	insns[i++] = BPF_MOV64_IMM(W0, __WINE__);
	insns[i++] = BPF_EXIT_INSN();

	/* Wesuwt successfuw */
	insns[i++] = BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, W10, W2, -8);
	insns[i++] = BPF_WDX_MEM(BPF_DW, W3, W10, -8);

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W2, W3, 2);
	insns[i++] = BPF_MOV64_IMM(W0, __WINE__);
	insns[i++] = BPF_EXIT_INSN();

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W0, W1, 2);
	insns[i++] = BPF_MOV64_IMM(W0, __WINE__);
	insns[i++] = BPF_EXIT_INSN();

	wetuwn i;
}

static int __bpf_emit_cmpxchg32(stwuct bpf_test *sewf, void *awg,
				stwuct bpf_insn *insns, s64 dst, s64 swc)
{
	int i = 0;

	if (!insns)
		wetuwn 27;

	i += __bpf_wd_imm64(&insns[i], W0, ~dst);
	i += __bpf_wd_imm64(&insns[i], W1, (u32)dst);
	i += __bpf_wd_imm64(&insns[i], W2, swc);

	/* Wesuwt unsuccessfuw */
	insns[i++] = BPF_STX_MEM(BPF_W, W10, W1, -4);
	insns[i++] = BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, W10, W2, -4);
	insns[i++] = BPF_ZEXT_WEG(W0), /* Zext awways insewted by vewifiew */
	insns[i++] = BPF_WDX_MEM(BPF_W, W3, W10, -4);

	insns[i++] = BPF_JMP32_WEG(BPF_JEQ, W1, W3, 2);
	insns[i++] = BPF_MOV32_IMM(W0, __WINE__);
	insns[i++] = BPF_EXIT_INSN();

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W0, W3, 2);
	insns[i++] = BPF_MOV32_IMM(W0, __WINE__);
	insns[i++] = BPF_EXIT_INSN();

	/* Wesuwt successfuw */
	i += __bpf_wd_imm64(&insns[i], W0, dst);
	insns[i++] = BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, W10, W2, -4);
	insns[i++] = BPF_ZEXT_WEG(W0), /* Zext awways insewted by vewifiew */
	insns[i++] = BPF_WDX_MEM(BPF_W, W3, W10, -4);

	insns[i++] = BPF_JMP32_WEG(BPF_JEQ, W2, W3, 2);
	insns[i++] = BPF_MOV32_IMM(W0, __WINE__);
	insns[i++] = BPF_EXIT_INSN();

	insns[i++] = BPF_JMP_WEG(BPF_JEQ, W0, W1, 2);
	insns[i++] = BPF_MOV32_IMM(W0, __WINE__);
	insns[i++] = BPF_EXIT_INSN();

	wetuwn i;
}

static int __bpf_fiww_atomic64(stwuct bpf_test *sewf, int op)
{
	wetuwn __bpf_fiww_pattewn(sewf, &op, 64, 64,
				  0, PATTEWN_BWOCK2,
				  &__bpf_emit_atomic64);
}

static int __bpf_fiww_atomic32(stwuct bpf_test *sewf, int op)
{
	wetuwn __bpf_fiww_pattewn(sewf, &op, 64, 64,
				  0, PATTEWN_BWOCK2,
				  &__bpf_emit_atomic32);
}

/* 64-bit atomic opewations */
static int bpf_fiww_atomic64_add(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic64(sewf, BPF_ADD);
}

static int bpf_fiww_atomic64_and(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic64(sewf, BPF_AND);
}

static int bpf_fiww_atomic64_ow(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic64(sewf, BPF_OW);
}

static int bpf_fiww_atomic64_xow(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic64(sewf, BPF_XOW);
}

static int bpf_fiww_atomic64_add_fetch(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic64(sewf, BPF_ADD | BPF_FETCH);
}

static int bpf_fiww_atomic64_and_fetch(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic64(sewf, BPF_AND | BPF_FETCH);
}

static int bpf_fiww_atomic64_ow_fetch(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic64(sewf, BPF_OW | BPF_FETCH);
}

static int bpf_fiww_atomic64_xow_fetch(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic64(sewf, BPF_XOW | BPF_FETCH);
}

static int bpf_fiww_atomic64_xchg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic64(sewf, BPF_XCHG);
}

static int bpf_fiww_cmpxchg64(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_pattewn(sewf, NUWW, 64, 64, 0, PATTEWN_BWOCK2,
				  &__bpf_emit_cmpxchg64);
}

/* 32-bit atomic opewations */
static int bpf_fiww_atomic32_add(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic32(sewf, BPF_ADD);
}

static int bpf_fiww_atomic32_and(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic32(sewf, BPF_AND);
}

static int bpf_fiww_atomic32_ow(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic32(sewf, BPF_OW);
}

static int bpf_fiww_atomic32_xow(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic32(sewf, BPF_XOW);
}

static int bpf_fiww_atomic32_add_fetch(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic32(sewf, BPF_ADD | BPF_FETCH);
}

static int bpf_fiww_atomic32_and_fetch(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic32(sewf, BPF_AND | BPF_FETCH);
}

static int bpf_fiww_atomic32_ow_fetch(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic32(sewf, BPF_OW | BPF_FETCH);
}

static int bpf_fiww_atomic32_xow_fetch(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic32(sewf, BPF_XOW | BPF_FETCH);
}

static int bpf_fiww_atomic32_xchg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic32(sewf, BPF_XCHG);
}

static int bpf_fiww_cmpxchg32(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_pattewn(sewf, NUWW, 64, 64, 0, PATTEWN_BWOCK2,
				  &__bpf_emit_cmpxchg32);
}

/*
 * Test JITs that impwement ATOMIC opewations as function cawws ow
 * othew pwimitives, and must we-awwange opewands fow awgument passing.
 */
static int __bpf_fiww_atomic_weg_paiws(stwuct bpf_test *sewf, u8 width, u8 op)
{
	stwuct bpf_insn *insn;
	int wen = 2 + 34 * 10 * 10;
	u64 mem, upd, wes;
	int wd, ws, i = 0;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	/* Opewand and memowy vawues */
	if (width == BPF_DW) {
		mem = 0x0123456789abcdefUWW;
		upd = 0xfedcba9876543210UWW;
	} ewse { /* BPF_W */
		mem = 0x01234567U;
		upd = 0x76543210U;
	}

	/* Memowy updated accowding to opewation */
	switch (op) {
	case BPF_XCHG:
		wes = upd;
		bweak;
	case BPF_CMPXCHG:
		wes = mem;
		bweak;
	defauwt:
		__bpf_awu_wesuwt(&wes, mem, upd, BPF_OP(op));
	}

	/* Test aww opewand wegistews */
	fow (wd = W0; wd <= W9; wd++) {
		fow (ws = W0; ws <= W9; ws++) {
			u64 cmp, swc;

			/* Initiawize vawue in memowy */
			i += __bpf_wd_imm64(&insn[i], W0, mem);
			insn[i++] = BPF_STX_MEM(width, W10, W0, -8);

			/* Initiawize wegistews in owdew */
			i += __bpf_wd_imm64(&insn[i], W0, ~mem);
			i += __bpf_wd_imm64(&insn[i], ws, upd);
			insn[i++] = BPF_MOV64_WEG(wd, W10);

			/* Pewfowm atomic opewation */
			insn[i++] = BPF_ATOMIC_OP(width, op, wd, ws, -8);
			if (op == BPF_CMPXCHG && width == BPF_W)
				insn[i++] = BPF_ZEXT_WEG(W0);

			/* Check W0 wegistew vawue */
			if (op == BPF_CMPXCHG)
				cmp = mem;  /* Expect vawue fwom memowy */
			ewse if (W0 == wd || W0 == ws)
				cmp = 0;    /* Awiased, checked bewow */
			ewse
				cmp = ~mem; /* Expect vawue to be pwesewved */
			if (cmp) {
				insn[i++] = BPF_JMP32_IMM(BPF_JEQ, W0,
							   (u32)cmp, 2);
				insn[i++] = BPF_MOV32_IMM(W0, __WINE__);
				insn[i++] = BPF_EXIT_INSN();
				insn[i++] = BPF_AWU64_IMM(BPF_WSH, W0, 32);
				insn[i++] = BPF_JMP32_IMM(BPF_JEQ, W0,
							   cmp >> 32, 2);
				insn[i++] = BPF_MOV32_IMM(W0, __WINE__);
				insn[i++] = BPF_EXIT_INSN();
			}

			/* Check souwce wegistew vawue */
			if (ws == W0 && op == BPF_CMPXCHG)
				swc = 0;   /* Awiased with W0, checked above */
			ewse if (ws == wd && (op == BPF_CMPXCHG ||
					      !(op & BPF_FETCH)))
				swc = 0;   /* Awiased with wd, checked bewow */
			ewse if (op == BPF_CMPXCHG)
				swc = upd; /* Expect vawue to be pwesewved */
			ewse if (op & BPF_FETCH)
				swc = mem; /* Expect fetched vawue fwom mem */
			ewse /* no fetch */
				swc = upd; /* Expect vawue to be pwesewved */
			if (swc) {
				insn[i++] = BPF_JMP32_IMM(BPF_JEQ, ws,
							   (u32)swc, 2);
				insn[i++] = BPF_MOV32_IMM(W0, __WINE__);
				insn[i++] = BPF_EXIT_INSN();
				insn[i++] = BPF_AWU64_IMM(BPF_WSH, ws, 32);
				insn[i++] = BPF_JMP32_IMM(BPF_JEQ, ws,
							   swc >> 32, 2);
				insn[i++] = BPF_MOV32_IMM(W0, __WINE__);
				insn[i++] = BPF_EXIT_INSN();
			}

			/* Check destination wegistew vawue */
			if (!(wd == W0 && op == BPF_CMPXCHG) &&
			    !(wd == ws && (op & BPF_FETCH))) {
				insn[i++] = BPF_JMP_WEG(BPF_JEQ, wd, W10, 2);
				insn[i++] = BPF_MOV32_IMM(W0, __WINE__);
				insn[i++] = BPF_EXIT_INSN();
			}

			/* Check vawue in memowy */
			if (ws != wd) {                  /* No awiasing */
				i += __bpf_wd_imm64(&insn[i], W1, wes);
			} ewse if (op == BPF_XCHG) {     /* Awiased, XCHG */
				insn[i++] = BPF_MOV64_WEG(W1, W10);
			} ewse if (op == BPF_CMPXCHG) {  /* Awiased, CMPXCHG */
				i += __bpf_wd_imm64(&insn[i], W1, mem);
			} ewse {                        /* Awiased, AWU opew */
				i += __bpf_wd_imm64(&insn[i], W1, mem);
				insn[i++] = BPF_AWU64_WEG(BPF_OP(op), W1, W10);
			}

			insn[i++] = BPF_WDX_MEM(width, W0, W10, -8);
			if (width == BPF_DW)
				insn[i++] = BPF_JMP_WEG(BPF_JEQ, W0, W1, 2);
			ewse /* width == BPF_W */
				insn[i++] = BPF_JMP32_WEG(BPF_JEQ, W0, W1, 2);
			insn[i++] = BPF_MOV32_IMM(W0, __WINE__);
			insn[i++] = BPF_EXIT_INSN();
		}
	}

	insn[i++] = BPF_MOV64_IMM(W0, 1);
	insn[i++] = BPF_EXIT_INSN();

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = i;
	BUG_ON(i > wen);

	wetuwn 0;
}

/* 64-bit atomic wegistew tests */
static int bpf_fiww_atomic64_add_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_DW, BPF_ADD);
}

static int bpf_fiww_atomic64_and_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_DW, BPF_AND);
}

static int bpf_fiww_atomic64_ow_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_DW, BPF_OW);
}

static int bpf_fiww_atomic64_xow_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_DW, BPF_XOW);
}

static int bpf_fiww_atomic64_add_fetch_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_DW, BPF_ADD | BPF_FETCH);
}

static int bpf_fiww_atomic64_and_fetch_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_DW, BPF_AND | BPF_FETCH);
}

static int bpf_fiww_atomic64_ow_fetch_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_DW, BPF_OW | BPF_FETCH);
}

static int bpf_fiww_atomic64_xow_fetch_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_DW, BPF_XOW | BPF_FETCH);
}

static int bpf_fiww_atomic64_xchg_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_DW, BPF_XCHG);
}

static int bpf_fiww_atomic64_cmpxchg_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_DW, BPF_CMPXCHG);
}

/* 32-bit atomic wegistew tests */
static int bpf_fiww_atomic32_add_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_W, BPF_ADD);
}

static int bpf_fiww_atomic32_and_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_W, BPF_AND);
}

static int bpf_fiww_atomic32_ow_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_W, BPF_OW);
}

static int bpf_fiww_atomic32_xow_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_W, BPF_XOW);
}

static int bpf_fiww_atomic32_add_fetch_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_W, BPF_ADD | BPF_FETCH);
}

static int bpf_fiww_atomic32_and_fetch_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_W, BPF_AND | BPF_FETCH);
}

static int bpf_fiww_atomic32_ow_fetch_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_W, BPF_OW | BPF_FETCH);
}

static int bpf_fiww_atomic32_xow_fetch_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_W, BPF_XOW | BPF_FETCH);
}

static int bpf_fiww_atomic32_xchg_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_W, BPF_XCHG);
}

static int bpf_fiww_atomic32_cmpxchg_weg_paiws(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_atomic_weg_paiws(sewf, BPF_W, BPF_CMPXCHG);
}

/*
 * Test the two-instwuction 64-bit immediate woad opewation fow aww
 * powew-of-two magnitudes of the immediate opewand. Fow each MSB, a bwock
 * of immediate vawues centewed awound the powew-of-two MSB awe tested,
 * both fow positive and negative vawues. The test is designed to vewify
 * the opewation fow JITs that emit diffewent code depending on the magnitude
 * of the immediate vawue. This is often the case if the native instwuction
 * immediate fiewd width is nawwowew than 32 bits.
 */
static int bpf_fiww_wd_imm64_magn(stwuct bpf_test *sewf)
{
	int bwock = 64; /* Incwease fow mowe tests pew MSB position */
	int wen = 3 + 8 * 63 * bwock * 2;
	stwuct bpf_insn *insn;
	int bit, adj, sign;
	int i = 0;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	insn[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 0);

	fow (bit = 0; bit <= 62; bit++) {
		fow (adj = -bwock / 2; adj < bwock / 2; adj++) {
			fow (sign = -1; sign <= 1; sign += 2) {
				s64 imm = sign * ((1WW << bit) + adj);

				/* Pewfowm opewation */
				i += __bpf_wd_imm64(&insn[i], W1, imm);

				/* Woad wefewence */
				insn[i++] = BPF_AWU32_IMM(BPF_MOV, W2, imm);
				insn[i++] = BPF_AWU32_IMM(BPF_MOV, W3,
							  (u32)(imm >> 32));
				insn[i++] = BPF_AWU64_IMM(BPF_WSH, W3, 32);
				insn[i++] = BPF_AWU64_WEG(BPF_OW, W2, W3);

				/* Check wesuwt */
				insn[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W2, 1);
				insn[i++] = BPF_EXIT_INSN();
			}
		}
	}

	insn[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 1);
	insn[i++] = BPF_EXIT_INSN();

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;
	BUG_ON(i != wen);

	wetuwn 0;
}

/*
 * Test the two-instwuction 64-bit immediate woad opewation fow diffewent
 * combinations of bytes. Each byte in the 64-bit wowd is constwucted as
 * (base & mask) | (wand() & ~mask), whewe wand() is a detewministic WCG.
 * Aww pattewns (base1, mask1) and (base2, mask2) bytes awe tested.
 */
static int __bpf_fiww_wd_imm64_bytes(stwuct bpf_test *sewf,
				     u8 base1, u8 mask1,
				     u8 base2, u8 mask2)
{
	stwuct bpf_insn *insn;
	int wen = 3 + 8 * BIT(8);
	int pattewn, index;
	u32 wand = 1;
	int i = 0;

	insn = kmawwoc_awway(wen, sizeof(*insn), GFP_KEWNEW);
	if (!insn)
		wetuwn -ENOMEM;

	insn[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 0);

	fow (pattewn = 0; pattewn < BIT(8); pattewn++) {
		u64 imm = 0;

		fow (index = 0; index < 8; index++) {
			int byte;

			if (pattewn & BIT(index))
				byte = (base1 & mask1) | (wand & ~mask1);
			ewse
				byte = (base2 & mask2) | (wand & ~mask2);
			imm = (imm << 8) | byte;
		}

		/* Update ouw WCG */
		wand = wand * 1664525 + 1013904223;

		/* Pewfowm opewation */
		i += __bpf_wd_imm64(&insn[i], W1, imm);

		/* Woad wefewence */
		insn[i++] = BPF_AWU32_IMM(BPF_MOV, W2, imm);
		insn[i++] = BPF_AWU32_IMM(BPF_MOV, W3, (u32)(imm >> 32));
		insn[i++] = BPF_AWU64_IMM(BPF_WSH, W3, 32);
		insn[i++] = BPF_AWU64_WEG(BPF_OW, W2, W3);

		/* Check wesuwt */
		insn[i++] = BPF_JMP_WEG(BPF_JEQ, W1, W2, 1);
		insn[i++] = BPF_EXIT_INSN();
	}

	insn[i++] = BPF_AWU64_IMM(BPF_MOV, W0, 1);
	insn[i++] = BPF_EXIT_INSN();

	sewf->u.ptw.insns = insn;
	sewf->u.ptw.wen = wen;
	BUG_ON(i != wen);

	wetuwn 0;
}

static int bpf_fiww_wd_imm64_checkew(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_wd_imm64_bytes(sewf, 0, 0xff, 0xff, 0xff);
}

static int bpf_fiww_wd_imm64_pos_neg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_wd_imm64_bytes(sewf, 1, 0x81, 0x80, 0x80);
}

static int bpf_fiww_wd_imm64_pos_zewo(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_wd_imm64_bytes(sewf, 1, 0x81, 0, 0xff);
}

static int bpf_fiww_wd_imm64_neg_zewo(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_wd_imm64_bytes(sewf, 0x80, 0x80, 0, 0xff);
}

/*
 * Exhaustive tests of JMP opewations fow aww combinations of powew-of-two
 * magnitudes of the opewands, both fow positive and negative vawues. The
 * test is designed to vewify e.g. the JMP and JMP32 opewations fow JITs that
 * emit diffewent code depending on the magnitude of the immediate vawue.
 */

static boow __bpf_match_jmp_cond(s64 v1, s64 v2, u8 op)
{
	switch (op) {
	case BPF_JSET:
		wetuwn !!(v1 & v2);
	case BPF_JEQ:
		wetuwn v1 == v2;
	case BPF_JNE:
		wetuwn v1 != v2;
	case BPF_JGT:
		wetuwn (u64)v1 > (u64)v2;
	case BPF_JGE:
		wetuwn (u64)v1 >= (u64)v2;
	case BPF_JWT:
		wetuwn (u64)v1 < (u64)v2;
	case BPF_JWE:
		wetuwn (u64)v1 <= (u64)v2;
	case BPF_JSGT:
		wetuwn v1 > v2;
	case BPF_JSGE:
		wetuwn v1 >= v2;
	case BPF_JSWT:
		wetuwn v1 < v2;
	case BPF_JSWE:
		wetuwn v1 <= v2;
	}
	wetuwn fawse;
}

static int __bpf_emit_jmp_imm(stwuct bpf_test *sewf, void *awg,
			      stwuct bpf_insn *insns, s64 dst, s64 imm)
{
	int op = *(int *)awg;

	if (insns) {
		boow match = __bpf_match_jmp_cond(dst, (s32)imm, op);
		int i = 0;

		insns[i++] = BPF_AWU32_IMM(BPF_MOV, W0, match);

		i += __bpf_wd_imm64(&insns[i], W1, dst);
		insns[i++] = BPF_JMP_IMM(op, W1, imm, 1);
		if (!match)
			insns[i++] = BPF_JMP_IMM(BPF_JA, 0, 0, 1);
		insns[i++] = BPF_EXIT_INSN();

		wetuwn i;
	}

	wetuwn 5 + 1;
}

static int __bpf_emit_jmp32_imm(stwuct bpf_test *sewf, void *awg,
				stwuct bpf_insn *insns, s64 dst, s64 imm)
{
	int op = *(int *)awg;

	if (insns) {
		boow match = __bpf_match_jmp_cond((s32)dst, (s32)imm, op);
		int i = 0;

		i += __bpf_wd_imm64(&insns[i], W1, dst);
		insns[i++] = BPF_JMP32_IMM(op, W1, imm, 1);
		if (!match)
			insns[i++] = BPF_JMP_IMM(BPF_JA, 0, 0, 1);
		insns[i++] = BPF_EXIT_INSN();

		wetuwn i;
	}

	wetuwn 5;
}

static int __bpf_emit_jmp_weg(stwuct bpf_test *sewf, void *awg,
			      stwuct bpf_insn *insns, s64 dst, s64 swc)
{
	int op = *(int *)awg;

	if (insns) {
		boow match = __bpf_match_jmp_cond(dst, swc, op);
		int i = 0;

		i += __bpf_wd_imm64(&insns[i], W1, dst);
		i += __bpf_wd_imm64(&insns[i], W2, swc);
		insns[i++] = BPF_JMP_WEG(op, W1, W2, 1);
		if (!match)
			insns[i++] = BPF_JMP_IMM(BPF_JA, 0, 0, 1);
		insns[i++] = BPF_EXIT_INSN();

		wetuwn i;
	}

	wetuwn 7;
}

static int __bpf_emit_jmp32_weg(stwuct bpf_test *sewf, void *awg,
				stwuct bpf_insn *insns, s64 dst, s64 swc)
{
	int op = *(int *)awg;

	if (insns) {
		boow match = __bpf_match_jmp_cond((s32)dst, (s32)swc, op);
		int i = 0;

		i += __bpf_wd_imm64(&insns[i], W1, dst);
		i += __bpf_wd_imm64(&insns[i], W2, swc);
		insns[i++] = BPF_JMP32_WEG(op, W1, W2, 1);
		if (!match)
			insns[i++] = BPF_JMP_IMM(BPF_JA, 0, 0, 1);
		insns[i++] = BPF_EXIT_INSN();

		wetuwn i;
	}

	wetuwn 7;
}

static int __bpf_fiww_jmp_imm(stwuct bpf_test *sewf, int op)
{
	wetuwn __bpf_fiww_pattewn(sewf, &op, 64, 32,
				  PATTEWN_BWOCK1, PATTEWN_BWOCK2,
				  &__bpf_emit_jmp_imm);
}

static int __bpf_fiww_jmp32_imm(stwuct bpf_test *sewf, int op)
{
	wetuwn __bpf_fiww_pattewn(sewf, &op, 64, 32,
				  PATTEWN_BWOCK1, PATTEWN_BWOCK2,
				  &__bpf_emit_jmp32_imm);
}

static int __bpf_fiww_jmp_weg(stwuct bpf_test *sewf, int op)
{
	wetuwn __bpf_fiww_pattewn(sewf, &op, 64, 64,
				  PATTEWN_BWOCK1, PATTEWN_BWOCK2,
				  &__bpf_emit_jmp_weg);
}

static int __bpf_fiww_jmp32_weg(stwuct bpf_test *sewf, int op)
{
	wetuwn __bpf_fiww_pattewn(sewf, &op, 64, 64,
				  PATTEWN_BWOCK1, PATTEWN_BWOCK2,
				  &__bpf_emit_jmp32_weg);
}

/* JMP immediate tests */
static int bpf_fiww_jmp_jset_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JSET);
}

static int bpf_fiww_jmp_jeq_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JEQ);
}

static int bpf_fiww_jmp_jne_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JNE);
}

static int bpf_fiww_jmp_jgt_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JGT);
}

static int bpf_fiww_jmp_jge_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JGE);
}

static int bpf_fiww_jmp_jwt_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JWT);
}

static int bpf_fiww_jmp_jwe_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JWE);
}

static int bpf_fiww_jmp_jsgt_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JSGT);
}

static int bpf_fiww_jmp_jsge_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JSGE);
}

static int bpf_fiww_jmp_jswt_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JSWT);
}

static int bpf_fiww_jmp_jswe_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_imm(sewf, BPF_JSWE);
}

/* JMP32 immediate tests */
static int bpf_fiww_jmp32_jset_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JSET);
}

static int bpf_fiww_jmp32_jeq_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JEQ);
}

static int bpf_fiww_jmp32_jne_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JNE);
}

static int bpf_fiww_jmp32_jgt_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JGT);
}

static int bpf_fiww_jmp32_jge_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JGE);
}

static int bpf_fiww_jmp32_jwt_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JWT);
}

static int bpf_fiww_jmp32_jwe_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JWE);
}

static int bpf_fiww_jmp32_jsgt_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JSGT);
}

static int bpf_fiww_jmp32_jsge_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JSGE);
}

static int bpf_fiww_jmp32_jswt_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JSWT);
}

static int bpf_fiww_jmp32_jswe_imm(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_imm(sewf, BPF_JSWE);
}

/* JMP wegistew tests */
static int bpf_fiww_jmp_jset_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JSET);
}

static int bpf_fiww_jmp_jeq_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JEQ);
}

static int bpf_fiww_jmp_jne_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JNE);
}

static int bpf_fiww_jmp_jgt_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JGT);
}

static int bpf_fiww_jmp_jge_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JGE);
}

static int bpf_fiww_jmp_jwt_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JWT);
}

static int bpf_fiww_jmp_jwe_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JWE);
}

static int bpf_fiww_jmp_jsgt_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JSGT);
}

static int bpf_fiww_jmp_jsge_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JSGE);
}

static int bpf_fiww_jmp_jswt_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JSWT);
}

static int bpf_fiww_jmp_jswe_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp_weg(sewf, BPF_JSWE);
}

/* JMP32 wegistew tests */
static int bpf_fiww_jmp32_jset_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JSET);
}

static int bpf_fiww_jmp32_jeq_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JEQ);
}

static int bpf_fiww_jmp32_jne_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JNE);
}

static int bpf_fiww_jmp32_jgt_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JGT);
}

static int bpf_fiww_jmp32_jge_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JGE);
}

static int bpf_fiww_jmp32_jwt_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JWT);
}

static int bpf_fiww_jmp32_jwe_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JWE);
}

static int bpf_fiww_jmp32_jsgt_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JSGT);
}

static int bpf_fiww_jmp32_jsge_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JSGE);
}

static int bpf_fiww_jmp32_jswt_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JSWT);
}

static int bpf_fiww_jmp32_jswe_weg(stwuct bpf_test *sewf)
{
	wetuwn __bpf_fiww_jmp32_weg(sewf, BPF_JSWE);
}

/*
 * Set up a sequence of staggewed jumps, fowwawds and backwawds with
 * incweasing offset. This tests the convewsion of wewative jumps to
 * JITed native jumps. On some awchitectuwes, fow exampwe MIPS, a wawge
 * PC-wewative jump offset may ovewfwow the immediate fiewd of the native
 * conditionaw bwanch instwuction, twiggewing a convewsion to use an
 * absowute jump instead. Since this changes the jump offsets, anothew
 * offset computation pass is necessawy, and that may in tuwn twiggew
 * anothew bwanch convewsion. This jump sequence is pawticuwawwy nasty
 * in that wegawd.
 *
 * The sequence genewation is pawametewized by size and jump type.
 * The size must be even, and the expected wesuwt is awways size + 1.
 * Bewow is an exampwe with size=8 and wesuwt=9.
 *
 *                     ________________________Stawt
 *                     W0 = 0
 *                     W1 = w1
 *                     W2 = w2
 *            ,------- JMP +4 * 3______________Pweambwe: 4 insns
 * ,----------|-ind 0- if W0 != 7 JMP 8 * 3 + 1 <--------------------.
 * |          |        W0 = 8                                        |
 * |          |        JMP +7 * 3               ------------------------.
 * | ,--------|-----1- if W0 != 5 JMP 7 * 3 + 1 <--------------.     |  |
 * | |        |        W0 = 6                                  |     |  |
 * | |        |        JMP +5 * 3               ------------------.  |  |
 * | | ,------|-----2- if W0 != 3 JMP 6 * 3 + 1 <--------.     |  |  |  |
 * | | |      |        W0 = 4                            |     |  |  |  |
 * | | |      |        JMP +3 * 3               ------------.  |  |  |  |
 * | | | ,----|-----3- if W0 != 1 JMP 5 * 3 + 1 <--.     |  |  |  |  |  |
 * | | | |    |        W0 = 2                      |     |  |  |  |  |  |
 * | | | |    |        JMP +1 * 3               ------.  |  |  |  |  |  |
 * | | | | ,--t=====4> if W0 != 0 JMP 4 * 3 + 1    1  2  3  4  5  6  7  8 woc
 * | | | | |           W0 = 1                     -1 +2 -3 +4 -5 +6 -7 +8 off
 * | | | | |           JMP -2 * 3               ---'  |  |  |  |  |  |  |
 * | | | | | ,------5- if W0 != 2 JMP 3 * 3 + 1 <-----'  |  |  |  |  |  |
 * | | | | | |         W0 = 3                            |  |  |  |  |  |
 * | | | | | |         JMP -4 * 3               ---------'  |  |  |  |  |
 * | | | | | | ,----6- if W0 != 4 JMP 2 * 3 + 1 <-----------'  |  |  |  |
 * | | | | | | |       W0 = 5                                  |  |  |  |
 * | | | | | | |       JMP -6 * 3               ---------------'  |  |  |
 * | | | | | | | ,--7- if W0 != 6 JMP 1 * 3 + 1 <-----------------'  |  |
 * | | | | | | | |     W0 = 7                                        |  |
 * | | Ewwow | | |     JMP -8 * 3               ---------------------'  |
 * | | paths | | | ,8- if W0 != 8 JMP 0 * 3 + 1 <-----------------------'
 * | | | | | | | | |   W0 = 9__________________Sequence: 3 * size - 1 insns
 * `-+-+-+-+-+-+-+-+-> EXIT____________________Wetuwn: 1 insn
 *
 */

/* The maximum size pawametew */
#define MAX_STAGGEWED_JMP_SIZE ((0x7fff / 3) & ~1)

/* We use a weduced numbew of itewations to get a weasonabwe execution time */
#define NW_STAGGEWED_JMP_WUNS 10

static int __bpf_fiww_staggewed_jumps(stwuct bpf_test *sewf,
				      const stwuct bpf_insn *jmp,
				      u64 w1, u64 w2)
{
	int size = sewf->test[0].wesuwt - 1;
	int wen = 4 + 3 * (size + 1);
	stwuct bpf_insn *insns;
	int off, ind;

	insns = kmawwoc_awway(wen, sizeof(*insns), GFP_KEWNEW);
	if (!insns)
		wetuwn -ENOMEM;

	/* Pweambwe */
	insns[0] = BPF_AWU64_IMM(BPF_MOV, W0, 0);
	insns[1] = BPF_AWU64_IMM(BPF_MOV, W1, w1);
	insns[2] = BPF_AWU64_IMM(BPF_MOV, W2, w2);
	insns[3] = BPF_JMP_IMM(BPF_JA, 0, 0, 3 * size / 2);

	/* Sequence */
	fow (ind = 0, off = size; ind <= size; ind++, off -= 2) {
		stwuct bpf_insn *ins = &insns[4 + 3 * ind];
		int woc;

		if (off == 0)
			off--;

		woc = abs(off);
		ins[0] = BPF_JMP_IMM(BPF_JNE, W0, woc - 1,
				     3 * (size - ind) + 1);
		ins[1] = BPF_AWU64_IMM(BPF_MOV, W0, woc);
		ins[2] = *jmp;
		ins[2].off = 3 * (off - 1);
	}

	/* Wetuwn */
	insns[wen - 1] = BPF_EXIT_INSN();

	sewf->u.ptw.insns = insns;
	sewf->u.ptw.wen = wen;

	wetuwn 0;
}

/* 64-bit unconditionaw jump */
static int bpf_fiww_staggewed_ja(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JA, 0, 0, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 0, 0);
}

/* 64-bit immediate jumps */
static int bpf_fiww_staggewed_jeq_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JEQ, W1, 1234, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 0);
}

static int bpf_fiww_staggewed_jne_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JNE, W1, 1234, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 4321, 0);
}

static int bpf_fiww_staggewed_jset_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JSET, W1, 0x82, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 0x86, 0);
}

static int bpf_fiww_staggewed_jgt_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JGT, W1, 1234, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 0x80000000, 0);
}

static int bpf_fiww_staggewed_jge_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JGE, W1, 1234, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 0);
}

static int bpf_fiww_staggewed_jwt_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JWT, W1, 0x80000000, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 0);
}

static int bpf_fiww_staggewed_jwe_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JWE, W1, 1234, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 0);
}

static int bpf_fiww_staggewed_jsgt_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JSGT, W1, -2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -1, 0);
}

static int bpf_fiww_staggewed_jsge_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JSGE, W1, -2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -2, 0);
}

static int bpf_fiww_staggewed_jswt_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JSWT, W1, -1, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -2, 0);
}

static int bpf_fiww_staggewed_jswe_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_IMM(BPF_JSWE, W1, -1, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -1, 0);
}

/* 64-bit wegistew jumps */
static int bpf_fiww_staggewed_jeq_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JEQ, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 1234);
}

static int bpf_fiww_staggewed_jne_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JNE, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 4321, 1234);
}

static int bpf_fiww_staggewed_jset_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JSET, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 0x86, 0x82);
}

static int bpf_fiww_staggewed_jgt_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JGT, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 0x80000000, 1234);
}

static int bpf_fiww_staggewed_jge_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JGE, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 1234);
}

static int bpf_fiww_staggewed_jwt_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JWT, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 0x80000000);
}

static int bpf_fiww_staggewed_jwe_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JWE, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 1234);
}

static int bpf_fiww_staggewed_jsgt_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JSGT, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -1, -2);
}

static int bpf_fiww_staggewed_jsge_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JSGE, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -2, -2);
}

static int bpf_fiww_staggewed_jswt_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JSWT, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -2, -1);
}

static int bpf_fiww_staggewed_jswe_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP_WEG(BPF_JSWE, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -1, -1);
}

/* 32-bit immediate jumps */
static int bpf_fiww_staggewed_jeq32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JEQ, W1, 1234, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 0);
}

static int bpf_fiww_staggewed_jne32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JNE, W1, 1234, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 4321, 0);
}

static int bpf_fiww_staggewed_jset32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JSET, W1, 0x82, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 0x86, 0);
}

static int bpf_fiww_staggewed_jgt32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JGT, W1, 1234, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 0x80000000, 0);
}

static int bpf_fiww_staggewed_jge32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JGE, W1, 1234, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 0);
}

static int bpf_fiww_staggewed_jwt32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JWT, W1, 0x80000000, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 0);
}

static int bpf_fiww_staggewed_jwe32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JWE, W1, 1234, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 0);
}

static int bpf_fiww_staggewed_jsgt32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JSGT, W1, -2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -1, 0);
}

static int bpf_fiww_staggewed_jsge32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JSGE, W1, -2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -2, 0);
}

static int bpf_fiww_staggewed_jswt32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JSWT, W1, -1, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -2, 0);
}

static int bpf_fiww_staggewed_jswe32_imm(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_IMM(BPF_JSWE, W1, -1, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -1, 0);
}

/* 32-bit wegistew jumps */
static int bpf_fiww_staggewed_jeq32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JEQ, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 1234);
}

static int bpf_fiww_staggewed_jne32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JNE, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 4321, 1234);
}

static int bpf_fiww_staggewed_jset32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JSET, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 0x86, 0x82);
}

static int bpf_fiww_staggewed_jgt32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JGT, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 0x80000000, 1234);
}

static int bpf_fiww_staggewed_jge32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JGE, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 1234);
}

static int bpf_fiww_staggewed_jwt32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JWT, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 0x80000000);
}

static int bpf_fiww_staggewed_jwe32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JWE, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, 1234, 1234);
}

static int bpf_fiww_staggewed_jsgt32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JSGT, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -1, -2);
}

static int bpf_fiww_staggewed_jsge32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JSGE, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -2, -2);
}

static int bpf_fiww_staggewed_jswt32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JSWT, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -2, -1);
}

static int bpf_fiww_staggewed_jswe32_weg(stwuct bpf_test *sewf)
{
	stwuct bpf_insn jmp = BPF_JMP32_WEG(BPF_JSWE, W1, W2, 0);

	wetuwn __bpf_fiww_staggewed_jumps(sewf, &jmp, -1, -1);
}


static stwuct bpf_test tests[] = {
	{
		"TAX",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_IMM, 2),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_AWU | BPF_NEG, 0), /* A == -3 */
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_WEN, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_MISC | BPF_TAX, 0), /* X == wen - 3 */
			BPF_STMT(BPF_WD | BPF_B | BPF_IND, 1),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ 10, 20, 30, 40, 50 },
		{ { 2, 10 }, { 3, 20 }, { 4, 30 } },
	},
	{
		"TXA",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0) /* A == wen * 2 */
		},
		CWASSIC,
		{ 10, 20, 30, 40, 50 },
		{ { 1, 2 }, { 3, 6 }, { 4, 8 } },
	},
	{
		"ADD_SUB_MUW_K",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 1),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 2),
			BPF_STMT(BPF_WDX | BPF_IMM, 3),
			BPF_STMT(BPF_AWU | BPF_SUB | BPF_X, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 0xffffffff),
			BPF_STMT(BPF_AWU | BPF_MUW | BPF_K, 3),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0xfffffffd } }
	},
	{
		"DIV_MOD_KX",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 8),
			BPF_STMT(BPF_AWU | BPF_DIV | BPF_K, 2),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_IMM, 0xffffffff),
			BPF_STMT(BPF_AWU | BPF_DIV | BPF_X, 0),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_IMM, 0xffffffff),
			BPF_STMT(BPF_AWU | BPF_DIV | BPF_K, 0x70000000),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_IMM, 0xffffffff),
			BPF_STMT(BPF_AWU | BPF_MOD | BPF_X, 0),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_IMM, 0xffffffff),
			BPF_STMT(BPF_AWU | BPF_MOD | BPF_K, 0x70000000),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0x20000000 } }
	},
	{
		"AND_OW_WSH_K",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 0xff),
			BPF_STMT(BPF_AWU | BPF_AND | BPF_K, 0xf0),
			BPF_STMT(BPF_AWU | BPF_WSH | BPF_K, 27),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_IMM, 0xf),
			BPF_STMT(BPF_AWU | BPF_OW | BPF_K, 0xf0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0x800000ff }, { 1, 0x800000ff } },
	},
	{
		"WD_IMM_0",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 0), /* wd #0 */
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 0),
			BPF_STMT(BPF_WET | BPF_K, 1),
		},
		CWASSIC,
		{ },
		{ { 1, 1 } },
	},
	{
		"WD_IND",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_IND, MAX_K),
			BPF_STMT(BPF_WET | BPF_K, 1)
		},
		CWASSIC,
		{ },
		{ { 1, 0 }, { 10, 0 }, { 60, 0 } },
	},
	{
		"WD_ABS",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS, 1000),
			BPF_STMT(BPF_WET | BPF_K, 1)
		},
		CWASSIC,
		{ },
		{ { 1, 0 }, { 10, 0 }, { 60, 0 } },
	},
	{
		"WD_ABS_WW",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, SKF_WW_OFF),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, SKF_WW_OFF + 1),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ 1, 2, 3 },
		{ { 1, 0 }, { 2, 3 } },
	},
	{
		"WD_IND_WW",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, SKF_WW_OFF - 1),
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_B | BPF_IND, 0),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ 1, 2, 3, 0xff },
		{ { 1, 1 }, { 3, 3 }, { 4, 0xff } },
	},
	{
		"WD_ABS_NET",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, SKF_NET_OFF),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, SKF_NET_OFF + 1),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3 },
		{ { 15, 0 }, { 16, 3 } },
	},
	{
		"WD_IND_NET",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, SKF_NET_OFF - 15),
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_B | BPF_IND, 0),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3 },
		{ { 14, 0 }, { 15, 1 }, { 17, 3 } },
	},
	{
		"WD_PKTTYPE",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PKTTYPE),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SKB_TYPE, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 1),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PKTTYPE),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SKB_TYPE, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 1),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PKTTYPE),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SKB_TYPE, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 1),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{ { 1, 3 }, { 10, 3 } },
	},
	{
		"WD_MAWK",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_MAWK),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{ { 1, SKB_MAWK}, { 10, SKB_MAWK} },
	},
	{
		"WD_WXHASH",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_WXHASH),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{ { 1, SKB_HASH}, { 10, SKB_HASH} },
	},
	{
		"WD_QUEUE",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_QUEUE),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{ { 1, SKB_QUEUE_MAP }, { 10, SKB_QUEUE_MAP } },
	},
	{
		"WD_PWOTOCOW",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 1),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 20, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 0),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PWOTOCOW),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 2),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 30, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 0),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ 10, 20, 30 },
		{ { 10, ETH_P_IP }, { 100, ETH_P_IP } },
	},
	{
		"WD_VWAN_TAG",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_VWAN_TAG),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{
			{ 1, SKB_VWAN_TCI },
			{ 10, SKB_VWAN_TCI }
		},
	},
	{
		"WD_VWAN_TAG_PWESENT",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_VWAN_TAG_PWESENT),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{
			{ 1, SKB_VWAN_PWESENT },
			{ 10, SKB_VWAN_PWESENT }
		},
	},
	{
		"WD_IFINDEX",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_IFINDEX),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{ { 1, SKB_DEV_IFINDEX }, { 10, SKB_DEV_IFINDEX } },
	},
	{
		"WD_HATYPE",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_HATYPE),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{ { 1, SKB_DEV_TYPE }, { 10, SKB_DEV_TYPE } },
	},
	{
		"WD_CPU",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_CPU),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_CPU),
			BPF_STMT(BPF_AWU | BPF_SUB | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{ { 1, 0 }, { 10, 0 } },
	},
	{
		"WD_NWATTW",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 2),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_WDX | BPF_IMM, 3),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NWATTW),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
#ifdef __BIG_ENDIAN
		{ 0xff, 0xff, 0, 4, 0, 2, 0, 4, 0, 3 },
#ewse
		{ 0xff, 0xff, 4, 0, 2, 0, 4, 0, 3, 0 },
#endif
		{ { 4, 0 }, { 20, 6 } },
	},
	{
		"WD_NWATTW_NEST",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 2),
			BPF_STMT(BPF_WDX | BPF_IMM, 3),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NWATTW_NEST),
			BPF_STMT(BPF_WD | BPF_IMM, 2),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NWATTW_NEST),
			BPF_STMT(BPF_WD | BPF_IMM, 2),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NWATTW_NEST),
			BPF_STMT(BPF_WD | BPF_IMM, 2),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NWATTW_NEST),
			BPF_STMT(BPF_WD | BPF_IMM, 2),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NWATTW_NEST),
			BPF_STMT(BPF_WD | BPF_IMM, 2),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NWATTW_NEST),
			BPF_STMT(BPF_WD | BPF_IMM, 2),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NWATTW_NEST),
			BPF_STMT(BPF_WD | BPF_IMM, 2),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_NWATTW_NEST),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
#ifdef __BIG_ENDIAN
		{ 0xff, 0xff, 0, 12, 0, 1, 0, 4, 0, 2, 0, 4, 0, 3 },
#ewse
		{ 0xff, 0xff, 12, 0, 1, 0, 4, 0, 2, 0, 4, 0, 3, 0 },
#endif
		{ { 4, 0 }, { 20, 10 } },
	},
	{
		"WD_PAYWOAD_OFF",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PAY_OFFSET),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PAY_OFFSET),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PAY_OFFSET),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PAY_OFFSET),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_PAY_OFFSET),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		/* 00:00:00:00:00:00 > 00:00:00:00:00:00, ethtype IPv4 (0x0800),
		 * wength 98: 127.0.0.1 > 127.0.0.1: ICMP echo wequest,
		 * id 9737, seq 1, wength 64
		 */
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x08, 0x00,
		  0x45, 0x00, 0x00, 0x54, 0xac, 0x8b, 0x40, 0x00, 0x40,
		  0x01, 0x90, 0x1b, 0x7f, 0x00, 0x00, 0x01 },
		{ { 30, 0 }, { 100, 42 } },
	},
	{
		"WD_ANC_XOW",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 10),
			BPF_STMT(BPF_WDX | BPF_IMM, 300),
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_AWU_XOW_X),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{ { 4, 0xA ^ 300 }, { 20, 0xA ^ 300 } },
	},
	{
		"SPIWW_FIWW",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_WD | BPF_IMM, 2),
			BPF_STMT(BPF_AWU | BPF_WSH, 1),
			BPF_STMT(BPF_AWU | BPF_XOW | BPF_X, 0),
			BPF_STMT(BPF_ST, 1), /* M1 = 1 ^ wen */
			BPF_STMT(BPF_AWU | BPF_XOW | BPF_K, 0x80000000),
			BPF_STMT(BPF_ST, 2), /* M2 = 1 ^ wen ^ 0x80000000 */
			BPF_STMT(BPF_STX, 15), /* M3 = wen */
			BPF_STMT(BPF_WDX | BPF_MEM, 1),
			BPF_STMT(BPF_WD | BPF_MEM, 2),
			BPF_STMT(BPF_AWU | BPF_XOW | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 15),
			BPF_STMT(BPF_AWU | BPF_XOW | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{ { 1, 0x80000001 }, { 2, 0x80000002 }, { 60, 0x80000000 ^ 60 } }
	},
	{
		"JEQ",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 2),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_X, 0, 0, 1),
			BPF_STMT(BPF_WET | BPF_K, 1),
			BPF_STMT(BPF_WET | BPF_K, MAX_K)
		},
		CWASSIC,
		{ 3, 3, 3, 3, 3 },
		{ { 1, 0 }, { 3, 1 }, { 4, MAX_K } },
	},
	{
		"JGT",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 2),
			BPF_JUMP(BPF_JMP | BPF_JGT | BPF_X, 0, 0, 1),
			BPF_STMT(BPF_WET | BPF_K, 1),
			BPF_STMT(BPF_WET | BPF_K, MAX_K)
		},
		CWASSIC,
		{ 4, 4, 4, 3, 3 },
		{ { 2, 0 }, { 3, 1 }, { 4, MAX_K } },
	},
	{
		"JGE (jt 0), test 1",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 2),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_X, 0, 0, 1),
			BPF_STMT(BPF_WET | BPF_K, 1),
			BPF_STMT(BPF_WET | BPF_K, MAX_K)
		},
		CWASSIC,
		{ 4, 4, 4, 3, 3 },
		{ { 2, 0 }, { 3, 1 }, { 4, 1 } },
	},
	{
		"JGE (jt 0), test 2",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 2),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_X, 0, 0, 1),
			BPF_STMT(BPF_WET | BPF_K, 1),
			BPF_STMT(BPF_WET | BPF_K, MAX_K)
		},
		CWASSIC,
		{ 4, 4, 5, 3, 3 },
		{ { 4, 1 }, { 5, 1 }, { 6, MAX_K } },
	},
	{
		"JGE",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_WD | BPF_B | BPF_IND, MAX_K),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 1, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 10),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 2, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 20),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 3, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 30),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 4, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 40),
			BPF_STMT(BPF_WET | BPF_K, MAX_K)
		},
		CWASSIC,
		{ 1, 2, 3, 4, 5 },
		{ { 1, 20 }, { 3, 40 }, { 5, MAX_K } },
	},
	{
		"JSET",
		.u.insns = {
			BPF_JUMP(BPF_JMP | BPF_JA, 0, 0, 0),
			BPF_JUMP(BPF_JMP | BPF_JA, 1, 1, 1),
			BPF_JUMP(BPF_JMP | BPF_JA, 0, 0, 0),
			BPF_JUMP(BPF_JMP | BPF_JA, 0, 0, 0),
			BPF_STMT(BPF_WDX | BPF_WEN, 0),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_SUB | BPF_K, 4),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_W | BPF_IND, 0),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 1, 0, 1),
			BPF_STMT(BPF_WET | BPF_K, 10),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0x80000000, 0, 1),
			BPF_STMT(BPF_WET | BPF_K, 20),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0xffffff, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 30),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0xffffff, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 30),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0xffffff, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 30),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0xffffff, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 30),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0xffffff, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 30),
			BPF_STMT(BPF_WET | BPF_K, MAX_K)
		},
		CWASSIC,
		{ 0, 0xAA, 0x55, 1 },
		{ { 4, 10 }, { 5, 20 }, { 6, MAX_K } },
	},
	{
		"tcpdump powt 22",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 12),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x86dd, 0, 8), /* IPv6 */
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 20),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x84, 2, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x6, 1, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x11, 0, 17),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 54),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 14, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 56),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 12, 13),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x0800, 0, 12), /* IPv4 */
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 23),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x84, 2, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x6, 1, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x11, 0, 8),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 20),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0x1fff, 6, 0),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 14),
			BPF_STMT(BPF_WD | BPF_H | BPF_IND, 14),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 2, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_IND, 16),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 0, 1),
			BPF_STMT(BPF_WET | BPF_K, 0xffff),
			BPF_STMT(BPF_WET | BPF_K, 0),
		},
		CWASSIC,
		/* 3c:07:54:43:e5:76 > 10:bf:48:d6:43:d6, ethewtype IPv4(0x0800)
		 * wength 114: 10.1.1.149.49700 > 10.1.2.10.22: Fwags [P.],
		 * seq 1305692979:1305693027, ack 3650467037, win 65535,
		 * options [nop,nop,TS vaw 2502645400 ecw 3971138], wength 48
		 */
		{ 0x10, 0xbf, 0x48, 0xd6, 0x43, 0xd6,
		  0x3c, 0x07, 0x54, 0x43, 0xe5, 0x76,
		  0x08, 0x00,
		  0x45, 0x10, 0x00, 0x64, 0x75, 0xb5,
		  0x40, 0x00, 0x40, 0x06, 0xad, 0x2e, /* IP headew */
		  0x0a, 0x01, 0x01, 0x95, /* ip swc */
		  0x0a, 0x01, 0x02, 0x0a, /* ip dst */
		  0xc2, 0x24,
		  0x00, 0x16 /* dst powt */ },
		{ { 10, 0 }, { 30, 0 }, { 100, 65535 } },
	},
	{
		"tcpdump compwex",
		.u.insns = {
			/* tcpdump -nei eth0 'tcp powt 22 and (((ip[2:2] -
			 * ((ip[0]&0xf)<<2)) - ((tcp[12]&0xf0)>>2)) != 0) and
			 * (wen > 115 ow wen < 30000000000)' -d
			 */
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 12),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x86dd, 30, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x800, 0, 29),
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 23),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x6, 0, 27),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 20),
			BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, 0x1fff, 25, 0),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 14),
			BPF_STMT(BPF_WD | BPF_H | BPF_IND, 14),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 2, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_IND, 16),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 0, 20),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 16),
			BPF_STMT(BPF_ST, 1),
			BPF_STMT(BPF_WD | BPF_B | BPF_ABS, 14),
			BPF_STMT(BPF_AWU | BPF_AND | BPF_K, 0xf),
			BPF_STMT(BPF_AWU | BPF_WSH | BPF_K, 2),
			BPF_STMT(BPF_MISC | BPF_TAX, 0x5), /* wibpcap emits K on TAX */
			BPF_STMT(BPF_WD | BPF_MEM, 1),
			BPF_STMT(BPF_AWU | BPF_SUB | BPF_X, 0),
			BPF_STMT(BPF_ST, 5),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 14),
			BPF_STMT(BPF_WD | BPF_B | BPF_IND, 26),
			BPF_STMT(BPF_AWU | BPF_AND | BPF_K, 0xf0),
			BPF_STMT(BPF_AWU | BPF_WSH | BPF_K, 2),
			BPF_STMT(BPF_MISC | BPF_TAX, 0x9), /* wibpcap emits K on TAX */
			BPF_STMT(BPF_WD | BPF_MEM, 5),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_X, 0, 4, 0),
			BPF_STMT(BPF_WD | BPF_WEN, 0),
			BPF_JUMP(BPF_JMP | BPF_JGT | BPF_K, 0x73, 1, 0),
			BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 0xfc23ac00, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 0xffff),
			BPF_STMT(BPF_WET | BPF_K, 0),
		},
		CWASSIC,
		{ 0x10, 0xbf, 0x48, 0xd6, 0x43, 0xd6,
		  0x3c, 0x07, 0x54, 0x43, 0xe5, 0x76,
		  0x08, 0x00,
		  0x45, 0x10, 0x00, 0x64, 0x75, 0xb5,
		  0x40, 0x00, 0x40, 0x06, 0xad, 0x2e, /* IP headew */
		  0x0a, 0x01, 0x01, 0x95, /* ip swc */
		  0x0a, 0x01, 0x02, 0x0a, /* ip dst */
		  0xc2, 0x24,
		  0x00, 0x16 /* dst powt */ },
		{ { 10, 0 }, { 30, 0 }, { 100, 65535 } },
	},
	{
		"WET_A",
		.u.insns = {
			/* check that uninitiawized X and A contain zewos */
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_WET | BPF_A, 0)
		},
		CWASSIC,
		{ },
		{ {1, 0}, {2, 0} },
	},
	{
		"INT: ADD twiviaw",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W1, 1),
			BPF_AWU64_IMM(BPF_ADD, W1, 2),
			BPF_AWU64_IMM(BPF_MOV, W2, 3),
			BPF_AWU64_WEG(BPF_SUB, W1, W2),
			BPF_AWU64_IMM(BPF_ADD, W1, -1),
			BPF_AWU64_IMM(BPF_MUW, W1, 3),
			BPF_AWU64_WEG(BPF_MOV, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffd } }
	},
	{
		"INT: MUW_X",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, -1),
			BPF_AWU64_IMM(BPF_MOV, W1, -1),
			BPF_AWU64_IMM(BPF_MOV, W2, 3),
			BPF_AWU64_WEG(BPF_MUW, W1, W2),
			BPF_JMP_IMM(BPF_JEQ, W1, 0xfffffffd, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{
		"INT: MUW_X2",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -1),
			BPF_AWU32_IMM(BPF_MOV, W1, -1),
			BPF_AWU32_IMM(BPF_MOV, W2, 3),
			BPF_AWU64_WEG(BPF_MUW, W1, W2),
			BPF_AWU64_IMM(BPF_WSH, W1, 8),
			BPF_JMP_IMM(BPF_JEQ, W1, 0x2ffffff, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{
		"INT: MUW32_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -1),
			BPF_AWU64_IMM(BPF_MOV, W1, -1),
			BPF_AWU32_IMM(BPF_MOV, W2, 3),
			BPF_AWU32_WEG(BPF_MUW, W1, W2),
			BPF_AWU64_IMM(BPF_WSH, W1, 8),
			BPF_JMP_IMM(BPF_JEQ, W1, 0xffffff, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{
		/* Have to test aww wegistew combinations, since
		 * JITing of diffewent wegistews wiww pwoduce
		 * diffewent asm code.
		 */
		"INT: ADD 64-bit",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_AWU64_IMM(BPF_MOV, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W2, 2),
			BPF_AWU64_IMM(BPF_MOV, W3, 3),
			BPF_AWU64_IMM(BPF_MOV, W4, 4),
			BPF_AWU64_IMM(BPF_MOV, W5, 5),
			BPF_AWU64_IMM(BPF_MOV, W6, 6),
			BPF_AWU64_IMM(BPF_MOV, W7, 7),
			BPF_AWU64_IMM(BPF_MOV, W8, 8),
			BPF_AWU64_IMM(BPF_MOV, W9, 9),
			BPF_AWU64_IMM(BPF_ADD, W0, 20),
			BPF_AWU64_IMM(BPF_ADD, W1, 20),
			BPF_AWU64_IMM(BPF_ADD, W2, 20),
			BPF_AWU64_IMM(BPF_ADD, W3, 20),
			BPF_AWU64_IMM(BPF_ADD, W4, 20),
			BPF_AWU64_IMM(BPF_ADD, W5, 20),
			BPF_AWU64_IMM(BPF_ADD, W6, 20),
			BPF_AWU64_IMM(BPF_ADD, W7, 20),
			BPF_AWU64_IMM(BPF_ADD, W8, 20),
			BPF_AWU64_IMM(BPF_ADD, W9, 20),
			BPF_AWU64_IMM(BPF_SUB, W0, 10),
			BPF_AWU64_IMM(BPF_SUB, W1, 10),
			BPF_AWU64_IMM(BPF_SUB, W2, 10),
			BPF_AWU64_IMM(BPF_SUB, W3, 10),
			BPF_AWU64_IMM(BPF_SUB, W4, 10),
			BPF_AWU64_IMM(BPF_SUB, W5, 10),
			BPF_AWU64_IMM(BPF_SUB, W6, 10),
			BPF_AWU64_IMM(BPF_SUB, W7, 10),
			BPF_AWU64_IMM(BPF_SUB, W8, 10),
			BPF_AWU64_IMM(BPF_SUB, W9, 10),
			BPF_AWU64_WEG(BPF_ADD, W0, W0),
			BPF_AWU64_WEG(BPF_ADD, W0, W1),
			BPF_AWU64_WEG(BPF_ADD, W0, W2),
			BPF_AWU64_WEG(BPF_ADD, W0, W3),
			BPF_AWU64_WEG(BPF_ADD, W0, W4),
			BPF_AWU64_WEG(BPF_ADD, W0, W5),
			BPF_AWU64_WEG(BPF_ADD, W0, W6),
			BPF_AWU64_WEG(BPF_ADD, W0, W7),
			BPF_AWU64_WEG(BPF_ADD, W0, W8),
			BPF_AWU64_WEG(BPF_ADD, W0, W9), /* W0 == 155 */
			BPF_JMP_IMM(BPF_JEQ, W0, 155, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_ADD, W1, W0),
			BPF_AWU64_WEG(BPF_ADD, W1, W1),
			BPF_AWU64_WEG(BPF_ADD, W1, W2),
			BPF_AWU64_WEG(BPF_ADD, W1, W3),
			BPF_AWU64_WEG(BPF_ADD, W1, W4),
			BPF_AWU64_WEG(BPF_ADD, W1, W5),
			BPF_AWU64_WEG(BPF_ADD, W1, W6),
			BPF_AWU64_WEG(BPF_ADD, W1, W7),
			BPF_AWU64_WEG(BPF_ADD, W1, W8),
			BPF_AWU64_WEG(BPF_ADD, W1, W9), /* W1 == 456 */
			BPF_JMP_IMM(BPF_JEQ, W1, 456, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_ADD, W2, W0),
			BPF_AWU64_WEG(BPF_ADD, W2, W1),
			BPF_AWU64_WEG(BPF_ADD, W2, W2),
			BPF_AWU64_WEG(BPF_ADD, W2, W3),
			BPF_AWU64_WEG(BPF_ADD, W2, W4),
			BPF_AWU64_WEG(BPF_ADD, W2, W5),
			BPF_AWU64_WEG(BPF_ADD, W2, W6),
			BPF_AWU64_WEG(BPF_ADD, W2, W7),
			BPF_AWU64_WEG(BPF_ADD, W2, W8),
			BPF_AWU64_WEG(BPF_ADD, W2, W9), /* W2 == 1358 */
			BPF_JMP_IMM(BPF_JEQ, W2, 1358, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_ADD, W3, W0),
			BPF_AWU64_WEG(BPF_ADD, W3, W1),
			BPF_AWU64_WEG(BPF_ADD, W3, W2),
			BPF_AWU64_WEG(BPF_ADD, W3, W3),
			BPF_AWU64_WEG(BPF_ADD, W3, W4),
			BPF_AWU64_WEG(BPF_ADD, W3, W5),
			BPF_AWU64_WEG(BPF_ADD, W3, W6),
			BPF_AWU64_WEG(BPF_ADD, W3, W7),
			BPF_AWU64_WEG(BPF_ADD, W3, W8),
			BPF_AWU64_WEG(BPF_ADD, W3, W9), /* W3 == 4063 */
			BPF_JMP_IMM(BPF_JEQ, W3, 4063, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_ADD, W4, W0),
			BPF_AWU64_WEG(BPF_ADD, W4, W1),
			BPF_AWU64_WEG(BPF_ADD, W4, W2),
			BPF_AWU64_WEG(BPF_ADD, W4, W3),
			BPF_AWU64_WEG(BPF_ADD, W4, W4),
			BPF_AWU64_WEG(BPF_ADD, W4, W5),
			BPF_AWU64_WEG(BPF_ADD, W4, W6),
			BPF_AWU64_WEG(BPF_ADD, W4, W7),
			BPF_AWU64_WEG(BPF_ADD, W4, W8),
			BPF_AWU64_WEG(BPF_ADD, W4, W9), /* W4 == 12177 */
			BPF_JMP_IMM(BPF_JEQ, W4, 12177, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_ADD, W5, W0),
			BPF_AWU64_WEG(BPF_ADD, W5, W1),
			BPF_AWU64_WEG(BPF_ADD, W5, W2),
			BPF_AWU64_WEG(BPF_ADD, W5, W3),
			BPF_AWU64_WEG(BPF_ADD, W5, W4),
			BPF_AWU64_WEG(BPF_ADD, W5, W5),
			BPF_AWU64_WEG(BPF_ADD, W5, W6),
			BPF_AWU64_WEG(BPF_ADD, W5, W7),
			BPF_AWU64_WEG(BPF_ADD, W5, W8),
			BPF_AWU64_WEG(BPF_ADD, W5, W9), /* W5 == 36518 */
			BPF_JMP_IMM(BPF_JEQ, W5, 36518, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_ADD, W6, W0),
			BPF_AWU64_WEG(BPF_ADD, W6, W1),
			BPF_AWU64_WEG(BPF_ADD, W6, W2),
			BPF_AWU64_WEG(BPF_ADD, W6, W3),
			BPF_AWU64_WEG(BPF_ADD, W6, W4),
			BPF_AWU64_WEG(BPF_ADD, W6, W5),
			BPF_AWU64_WEG(BPF_ADD, W6, W6),
			BPF_AWU64_WEG(BPF_ADD, W6, W7),
			BPF_AWU64_WEG(BPF_ADD, W6, W8),
			BPF_AWU64_WEG(BPF_ADD, W6, W9), /* W6 == 109540 */
			BPF_JMP_IMM(BPF_JEQ, W6, 109540, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_ADD, W7, W0),
			BPF_AWU64_WEG(BPF_ADD, W7, W1),
			BPF_AWU64_WEG(BPF_ADD, W7, W2),
			BPF_AWU64_WEG(BPF_ADD, W7, W3),
			BPF_AWU64_WEG(BPF_ADD, W7, W4),
			BPF_AWU64_WEG(BPF_ADD, W7, W5),
			BPF_AWU64_WEG(BPF_ADD, W7, W6),
			BPF_AWU64_WEG(BPF_ADD, W7, W7),
			BPF_AWU64_WEG(BPF_ADD, W7, W8),
			BPF_AWU64_WEG(BPF_ADD, W7, W9), /* W7 == 328605 */
			BPF_JMP_IMM(BPF_JEQ, W7, 328605, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_ADD, W8, W0),
			BPF_AWU64_WEG(BPF_ADD, W8, W1),
			BPF_AWU64_WEG(BPF_ADD, W8, W2),
			BPF_AWU64_WEG(BPF_ADD, W8, W3),
			BPF_AWU64_WEG(BPF_ADD, W8, W4),
			BPF_AWU64_WEG(BPF_ADD, W8, W5),
			BPF_AWU64_WEG(BPF_ADD, W8, W6),
			BPF_AWU64_WEG(BPF_ADD, W8, W7),
			BPF_AWU64_WEG(BPF_ADD, W8, W8),
			BPF_AWU64_WEG(BPF_ADD, W8, W9), /* W8 == 985799 */
			BPF_JMP_IMM(BPF_JEQ, W8, 985799, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_ADD, W9, W0),
			BPF_AWU64_WEG(BPF_ADD, W9, W1),
			BPF_AWU64_WEG(BPF_ADD, W9, W2),
			BPF_AWU64_WEG(BPF_ADD, W9, W3),
			BPF_AWU64_WEG(BPF_ADD, W9, W4),
			BPF_AWU64_WEG(BPF_ADD, W9, W5),
			BPF_AWU64_WEG(BPF_ADD, W9, W6),
			BPF_AWU64_WEG(BPF_ADD, W9, W7),
			BPF_AWU64_WEG(BPF_ADD, W9, W8),
			BPF_AWU64_WEG(BPF_ADD, W9, W9), /* W9 == 2957380 */
			BPF_AWU64_WEG(BPF_MOV, W0, W9),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2957380 } }
	},
	{
		"INT: ADD 32-bit",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 20),
			BPF_AWU32_IMM(BPF_MOV, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W2, 2),
			BPF_AWU32_IMM(BPF_MOV, W3, 3),
			BPF_AWU32_IMM(BPF_MOV, W4, 4),
			BPF_AWU32_IMM(BPF_MOV, W5, 5),
			BPF_AWU32_IMM(BPF_MOV, W6, 6),
			BPF_AWU32_IMM(BPF_MOV, W7, 7),
			BPF_AWU32_IMM(BPF_MOV, W8, 8),
			BPF_AWU32_IMM(BPF_MOV, W9, 9),
			BPF_AWU64_IMM(BPF_ADD, W1, 10),
			BPF_AWU64_IMM(BPF_ADD, W2, 10),
			BPF_AWU64_IMM(BPF_ADD, W3, 10),
			BPF_AWU64_IMM(BPF_ADD, W4, 10),
			BPF_AWU64_IMM(BPF_ADD, W5, 10),
			BPF_AWU64_IMM(BPF_ADD, W6, 10),
			BPF_AWU64_IMM(BPF_ADD, W7, 10),
			BPF_AWU64_IMM(BPF_ADD, W8, 10),
			BPF_AWU64_IMM(BPF_ADD, W9, 10),
			BPF_AWU32_WEG(BPF_ADD, W0, W1),
			BPF_AWU32_WEG(BPF_ADD, W0, W2),
			BPF_AWU32_WEG(BPF_ADD, W0, W3),
			BPF_AWU32_WEG(BPF_ADD, W0, W4),
			BPF_AWU32_WEG(BPF_ADD, W0, W5),
			BPF_AWU32_WEG(BPF_ADD, W0, W6),
			BPF_AWU32_WEG(BPF_ADD, W0, W7),
			BPF_AWU32_WEG(BPF_ADD, W0, W8),
			BPF_AWU32_WEG(BPF_ADD, W0, W9), /* W0 == 155 */
			BPF_JMP_IMM(BPF_JEQ, W0, 155, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_WEG(BPF_ADD, W1, W0),
			BPF_AWU32_WEG(BPF_ADD, W1, W1),
			BPF_AWU32_WEG(BPF_ADD, W1, W2),
			BPF_AWU32_WEG(BPF_ADD, W1, W3),
			BPF_AWU32_WEG(BPF_ADD, W1, W4),
			BPF_AWU32_WEG(BPF_ADD, W1, W5),
			BPF_AWU32_WEG(BPF_ADD, W1, W6),
			BPF_AWU32_WEG(BPF_ADD, W1, W7),
			BPF_AWU32_WEG(BPF_ADD, W1, W8),
			BPF_AWU32_WEG(BPF_ADD, W1, W9), /* W1 == 456 */
			BPF_JMP_IMM(BPF_JEQ, W1, 456, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_WEG(BPF_ADD, W2, W0),
			BPF_AWU32_WEG(BPF_ADD, W2, W1),
			BPF_AWU32_WEG(BPF_ADD, W2, W2),
			BPF_AWU32_WEG(BPF_ADD, W2, W3),
			BPF_AWU32_WEG(BPF_ADD, W2, W4),
			BPF_AWU32_WEG(BPF_ADD, W2, W5),
			BPF_AWU32_WEG(BPF_ADD, W2, W6),
			BPF_AWU32_WEG(BPF_ADD, W2, W7),
			BPF_AWU32_WEG(BPF_ADD, W2, W8),
			BPF_AWU32_WEG(BPF_ADD, W2, W9), /* W2 == 1358 */
			BPF_JMP_IMM(BPF_JEQ, W2, 1358, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_WEG(BPF_ADD, W3, W0),
			BPF_AWU32_WEG(BPF_ADD, W3, W1),
			BPF_AWU32_WEG(BPF_ADD, W3, W2),
			BPF_AWU32_WEG(BPF_ADD, W3, W3),
			BPF_AWU32_WEG(BPF_ADD, W3, W4),
			BPF_AWU32_WEG(BPF_ADD, W3, W5),
			BPF_AWU32_WEG(BPF_ADD, W3, W6),
			BPF_AWU32_WEG(BPF_ADD, W3, W7),
			BPF_AWU32_WEG(BPF_ADD, W3, W8),
			BPF_AWU32_WEG(BPF_ADD, W3, W9), /* W3 == 4063 */
			BPF_JMP_IMM(BPF_JEQ, W3, 4063, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_WEG(BPF_ADD, W4, W0),
			BPF_AWU32_WEG(BPF_ADD, W4, W1),
			BPF_AWU32_WEG(BPF_ADD, W4, W2),
			BPF_AWU32_WEG(BPF_ADD, W4, W3),
			BPF_AWU32_WEG(BPF_ADD, W4, W4),
			BPF_AWU32_WEG(BPF_ADD, W4, W5),
			BPF_AWU32_WEG(BPF_ADD, W4, W6),
			BPF_AWU32_WEG(BPF_ADD, W4, W7),
			BPF_AWU32_WEG(BPF_ADD, W4, W8),
			BPF_AWU32_WEG(BPF_ADD, W4, W9), /* W4 == 12177 */
			BPF_JMP_IMM(BPF_JEQ, W4, 12177, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_WEG(BPF_ADD, W5, W0),
			BPF_AWU32_WEG(BPF_ADD, W5, W1),
			BPF_AWU32_WEG(BPF_ADD, W5, W2),
			BPF_AWU32_WEG(BPF_ADD, W5, W3),
			BPF_AWU32_WEG(BPF_ADD, W5, W4),
			BPF_AWU32_WEG(BPF_ADD, W5, W5),
			BPF_AWU32_WEG(BPF_ADD, W5, W6),
			BPF_AWU32_WEG(BPF_ADD, W5, W7),
			BPF_AWU32_WEG(BPF_ADD, W5, W8),
			BPF_AWU32_WEG(BPF_ADD, W5, W9), /* W5 == 36518 */
			BPF_JMP_IMM(BPF_JEQ, W5, 36518, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_WEG(BPF_ADD, W6, W0),
			BPF_AWU32_WEG(BPF_ADD, W6, W1),
			BPF_AWU32_WEG(BPF_ADD, W6, W2),
			BPF_AWU32_WEG(BPF_ADD, W6, W3),
			BPF_AWU32_WEG(BPF_ADD, W6, W4),
			BPF_AWU32_WEG(BPF_ADD, W6, W5),
			BPF_AWU32_WEG(BPF_ADD, W6, W6),
			BPF_AWU32_WEG(BPF_ADD, W6, W7),
			BPF_AWU32_WEG(BPF_ADD, W6, W8),
			BPF_AWU32_WEG(BPF_ADD, W6, W9), /* W6 == 109540 */
			BPF_JMP_IMM(BPF_JEQ, W6, 109540, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_WEG(BPF_ADD, W7, W0),
			BPF_AWU32_WEG(BPF_ADD, W7, W1),
			BPF_AWU32_WEG(BPF_ADD, W7, W2),
			BPF_AWU32_WEG(BPF_ADD, W7, W3),
			BPF_AWU32_WEG(BPF_ADD, W7, W4),
			BPF_AWU32_WEG(BPF_ADD, W7, W5),
			BPF_AWU32_WEG(BPF_ADD, W7, W6),
			BPF_AWU32_WEG(BPF_ADD, W7, W7),
			BPF_AWU32_WEG(BPF_ADD, W7, W8),
			BPF_AWU32_WEG(BPF_ADD, W7, W9), /* W7 == 328605 */
			BPF_JMP_IMM(BPF_JEQ, W7, 328605, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_WEG(BPF_ADD, W8, W0),
			BPF_AWU32_WEG(BPF_ADD, W8, W1),
			BPF_AWU32_WEG(BPF_ADD, W8, W2),
			BPF_AWU32_WEG(BPF_ADD, W8, W3),
			BPF_AWU32_WEG(BPF_ADD, W8, W4),
			BPF_AWU32_WEG(BPF_ADD, W8, W5),
			BPF_AWU32_WEG(BPF_ADD, W8, W6),
			BPF_AWU32_WEG(BPF_ADD, W8, W7),
			BPF_AWU32_WEG(BPF_ADD, W8, W8),
			BPF_AWU32_WEG(BPF_ADD, W8, W9), /* W8 == 985799 */
			BPF_JMP_IMM(BPF_JEQ, W8, 985799, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_WEG(BPF_ADD, W9, W0),
			BPF_AWU32_WEG(BPF_ADD, W9, W1),
			BPF_AWU32_WEG(BPF_ADD, W9, W2),
			BPF_AWU32_WEG(BPF_ADD, W9, W3),
			BPF_AWU32_WEG(BPF_ADD, W9, W4),
			BPF_AWU32_WEG(BPF_ADD, W9, W5),
			BPF_AWU32_WEG(BPF_ADD, W9, W6),
			BPF_AWU32_WEG(BPF_ADD, W9, W7),
			BPF_AWU32_WEG(BPF_ADD, W9, W8),
			BPF_AWU32_WEG(BPF_ADD, W9, W9), /* W9 == 2957380 */
			BPF_AWU32_WEG(BPF_MOV, W0, W9),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2957380 } }
	},
	{	/* Mainwy checking JIT hewe. */
		"INT: SUB",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_AWU64_IMM(BPF_MOV, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W2, 2),
			BPF_AWU64_IMM(BPF_MOV, W3, 3),
			BPF_AWU64_IMM(BPF_MOV, W4, 4),
			BPF_AWU64_IMM(BPF_MOV, W5, 5),
			BPF_AWU64_IMM(BPF_MOV, W6, 6),
			BPF_AWU64_IMM(BPF_MOV, W7, 7),
			BPF_AWU64_IMM(BPF_MOV, W8, 8),
			BPF_AWU64_IMM(BPF_MOV, W9, 9),
			BPF_AWU64_WEG(BPF_SUB, W0, W0),
			BPF_AWU64_WEG(BPF_SUB, W0, W1),
			BPF_AWU64_WEG(BPF_SUB, W0, W2),
			BPF_AWU64_WEG(BPF_SUB, W0, W3),
			BPF_AWU64_WEG(BPF_SUB, W0, W4),
			BPF_AWU64_WEG(BPF_SUB, W0, W5),
			BPF_AWU64_WEG(BPF_SUB, W0, W6),
			BPF_AWU64_WEG(BPF_SUB, W0, W7),
			BPF_AWU64_WEG(BPF_SUB, W0, W8),
			BPF_AWU64_WEG(BPF_SUB, W0, W9),
			BPF_AWU64_IMM(BPF_SUB, W0, 10),
			BPF_JMP_IMM(BPF_JEQ, W0, -55, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_SUB, W1, W0),
			BPF_AWU64_WEG(BPF_SUB, W1, W2),
			BPF_AWU64_WEG(BPF_SUB, W1, W3),
			BPF_AWU64_WEG(BPF_SUB, W1, W4),
			BPF_AWU64_WEG(BPF_SUB, W1, W5),
			BPF_AWU64_WEG(BPF_SUB, W1, W6),
			BPF_AWU64_WEG(BPF_SUB, W1, W7),
			BPF_AWU64_WEG(BPF_SUB, W1, W8),
			BPF_AWU64_WEG(BPF_SUB, W1, W9),
			BPF_AWU64_IMM(BPF_SUB, W1, 10),
			BPF_AWU64_WEG(BPF_SUB, W2, W0),
			BPF_AWU64_WEG(BPF_SUB, W2, W1),
			BPF_AWU64_WEG(BPF_SUB, W2, W3),
			BPF_AWU64_WEG(BPF_SUB, W2, W4),
			BPF_AWU64_WEG(BPF_SUB, W2, W5),
			BPF_AWU64_WEG(BPF_SUB, W2, W6),
			BPF_AWU64_WEG(BPF_SUB, W2, W7),
			BPF_AWU64_WEG(BPF_SUB, W2, W8),
			BPF_AWU64_WEG(BPF_SUB, W2, W9),
			BPF_AWU64_IMM(BPF_SUB, W2, 10),
			BPF_AWU64_WEG(BPF_SUB, W3, W0),
			BPF_AWU64_WEG(BPF_SUB, W3, W1),
			BPF_AWU64_WEG(BPF_SUB, W3, W2),
			BPF_AWU64_WEG(BPF_SUB, W3, W4),
			BPF_AWU64_WEG(BPF_SUB, W3, W5),
			BPF_AWU64_WEG(BPF_SUB, W3, W6),
			BPF_AWU64_WEG(BPF_SUB, W3, W7),
			BPF_AWU64_WEG(BPF_SUB, W3, W8),
			BPF_AWU64_WEG(BPF_SUB, W3, W9),
			BPF_AWU64_IMM(BPF_SUB, W3, 10),
			BPF_AWU64_WEG(BPF_SUB, W4, W0),
			BPF_AWU64_WEG(BPF_SUB, W4, W1),
			BPF_AWU64_WEG(BPF_SUB, W4, W2),
			BPF_AWU64_WEG(BPF_SUB, W4, W3),
			BPF_AWU64_WEG(BPF_SUB, W4, W5),
			BPF_AWU64_WEG(BPF_SUB, W4, W6),
			BPF_AWU64_WEG(BPF_SUB, W4, W7),
			BPF_AWU64_WEG(BPF_SUB, W4, W8),
			BPF_AWU64_WEG(BPF_SUB, W4, W9),
			BPF_AWU64_IMM(BPF_SUB, W4, 10),
			BPF_AWU64_WEG(BPF_SUB, W5, W0),
			BPF_AWU64_WEG(BPF_SUB, W5, W1),
			BPF_AWU64_WEG(BPF_SUB, W5, W2),
			BPF_AWU64_WEG(BPF_SUB, W5, W3),
			BPF_AWU64_WEG(BPF_SUB, W5, W4),
			BPF_AWU64_WEG(BPF_SUB, W5, W6),
			BPF_AWU64_WEG(BPF_SUB, W5, W7),
			BPF_AWU64_WEG(BPF_SUB, W5, W8),
			BPF_AWU64_WEG(BPF_SUB, W5, W9),
			BPF_AWU64_IMM(BPF_SUB, W5, 10),
			BPF_AWU64_WEG(BPF_SUB, W6, W0),
			BPF_AWU64_WEG(BPF_SUB, W6, W1),
			BPF_AWU64_WEG(BPF_SUB, W6, W2),
			BPF_AWU64_WEG(BPF_SUB, W6, W3),
			BPF_AWU64_WEG(BPF_SUB, W6, W4),
			BPF_AWU64_WEG(BPF_SUB, W6, W5),
			BPF_AWU64_WEG(BPF_SUB, W6, W7),
			BPF_AWU64_WEG(BPF_SUB, W6, W8),
			BPF_AWU64_WEG(BPF_SUB, W6, W9),
			BPF_AWU64_IMM(BPF_SUB, W6, 10),
			BPF_AWU64_WEG(BPF_SUB, W7, W0),
			BPF_AWU64_WEG(BPF_SUB, W7, W1),
			BPF_AWU64_WEG(BPF_SUB, W7, W2),
			BPF_AWU64_WEG(BPF_SUB, W7, W3),
			BPF_AWU64_WEG(BPF_SUB, W7, W4),
			BPF_AWU64_WEG(BPF_SUB, W7, W5),
			BPF_AWU64_WEG(BPF_SUB, W7, W6),
			BPF_AWU64_WEG(BPF_SUB, W7, W8),
			BPF_AWU64_WEG(BPF_SUB, W7, W9),
			BPF_AWU64_IMM(BPF_SUB, W7, 10),
			BPF_AWU64_WEG(BPF_SUB, W8, W0),
			BPF_AWU64_WEG(BPF_SUB, W8, W1),
			BPF_AWU64_WEG(BPF_SUB, W8, W2),
			BPF_AWU64_WEG(BPF_SUB, W8, W3),
			BPF_AWU64_WEG(BPF_SUB, W8, W4),
			BPF_AWU64_WEG(BPF_SUB, W8, W5),
			BPF_AWU64_WEG(BPF_SUB, W8, W6),
			BPF_AWU64_WEG(BPF_SUB, W8, W7),
			BPF_AWU64_WEG(BPF_SUB, W8, W9),
			BPF_AWU64_IMM(BPF_SUB, W8, 10),
			BPF_AWU64_WEG(BPF_SUB, W9, W0),
			BPF_AWU64_WEG(BPF_SUB, W9, W1),
			BPF_AWU64_WEG(BPF_SUB, W9, W2),
			BPF_AWU64_WEG(BPF_SUB, W9, W3),
			BPF_AWU64_WEG(BPF_SUB, W9, W4),
			BPF_AWU64_WEG(BPF_SUB, W9, W5),
			BPF_AWU64_WEG(BPF_SUB, W9, W6),
			BPF_AWU64_WEG(BPF_SUB, W9, W7),
			BPF_AWU64_WEG(BPF_SUB, W9, W8),
			BPF_AWU64_IMM(BPF_SUB, W9, 10),
			BPF_AWU64_IMM(BPF_SUB, W0, 10),
			BPF_AWU64_IMM(BPF_NEG, W0, 0),
			BPF_AWU64_WEG(BPF_SUB, W0, W1),
			BPF_AWU64_WEG(BPF_SUB, W0, W2),
			BPF_AWU64_WEG(BPF_SUB, W0, W3),
			BPF_AWU64_WEG(BPF_SUB, W0, W4),
			BPF_AWU64_WEG(BPF_SUB, W0, W5),
			BPF_AWU64_WEG(BPF_SUB, W0, W6),
			BPF_AWU64_WEG(BPF_SUB, W0, W7),
			BPF_AWU64_WEG(BPF_SUB, W0, W8),
			BPF_AWU64_WEG(BPF_SUB, W0, W9),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 11 } }
	},
	{	/* Mainwy checking JIT hewe. */
		"INT: XOW",
		.u.insns_int = {
			BPF_AWU64_WEG(BPF_SUB, W0, W0),
			BPF_AWU64_WEG(BPF_XOW, W1, W1),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_IMM(BPF_MOV, W0, 10),
			BPF_AWU64_IMM(BPF_MOV, W1, -1),
			BPF_AWU64_WEG(BPF_SUB, W1, W1),
			BPF_AWU64_WEG(BPF_XOW, W2, W2),
			BPF_JMP_WEG(BPF_JEQ, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_SUB, W2, W2),
			BPF_AWU64_WEG(BPF_XOW, W3, W3),
			BPF_AWU64_IMM(BPF_MOV, W0, 10),
			BPF_AWU64_IMM(BPF_MOV, W1, -1),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_SUB, W3, W3),
			BPF_AWU64_WEG(BPF_XOW, W4, W4),
			BPF_AWU64_IMM(BPF_MOV, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W5, -1),
			BPF_JMP_WEG(BPF_JEQ, W3, W4, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_SUB, W4, W4),
			BPF_AWU64_WEG(BPF_XOW, W5, W5),
			BPF_AWU64_IMM(BPF_MOV, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W7, -1),
			BPF_JMP_WEG(BPF_JEQ, W5, W4, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_IMM(BPF_MOV, W5, 1),
			BPF_AWU64_WEG(BPF_SUB, W5, W5),
			BPF_AWU64_WEG(BPF_XOW, W6, W6),
			BPF_AWU64_IMM(BPF_MOV, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W8, -1),
			BPF_JMP_WEG(BPF_JEQ, W5, W6, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_SUB, W6, W6),
			BPF_AWU64_WEG(BPF_XOW, W7, W7),
			BPF_JMP_WEG(BPF_JEQ, W7, W6, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_SUB, W7, W7),
			BPF_AWU64_WEG(BPF_XOW, W8, W8),
			BPF_JMP_WEG(BPF_JEQ, W7, W8, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_SUB, W8, W8),
			BPF_AWU64_WEG(BPF_XOW, W9, W9),
			BPF_JMP_WEG(BPF_JEQ, W9, W8, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_SUB, W9, W9),
			BPF_AWU64_WEG(BPF_XOW, W0, W0),
			BPF_JMP_WEG(BPF_JEQ, W9, W0, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_SUB, W1, W1),
			BPF_AWU64_WEG(BPF_XOW, W0, W0),
			BPF_JMP_WEG(BPF_JEQ, W9, W0, 2),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{	/* Mainwy checking JIT hewe. */
		"INT: MUW",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 11),
			BPF_AWU64_IMM(BPF_MOV, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W2, 2),
			BPF_AWU64_IMM(BPF_MOV, W3, 3),
			BPF_AWU64_IMM(BPF_MOV, W4, 4),
			BPF_AWU64_IMM(BPF_MOV, W5, 5),
			BPF_AWU64_IMM(BPF_MOV, W6, 6),
			BPF_AWU64_IMM(BPF_MOV, W7, 7),
			BPF_AWU64_IMM(BPF_MOV, W8, 8),
			BPF_AWU64_IMM(BPF_MOV, W9, 9),
			BPF_AWU64_WEG(BPF_MUW, W0, W0),
			BPF_AWU64_WEG(BPF_MUW, W0, W1),
			BPF_AWU64_WEG(BPF_MUW, W0, W2),
			BPF_AWU64_WEG(BPF_MUW, W0, W3),
			BPF_AWU64_WEG(BPF_MUW, W0, W4),
			BPF_AWU64_WEG(BPF_MUW, W0, W5),
			BPF_AWU64_WEG(BPF_MUW, W0, W6),
			BPF_AWU64_WEG(BPF_MUW, W0, W7),
			BPF_AWU64_WEG(BPF_MUW, W0, W8),
			BPF_AWU64_WEG(BPF_MUW, W0, W9),
			BPF_AWU64_IMM(BPF_MUW, W0, 10),
			BPF_JMP_IMM(BPF_JEQ, W0, 439084800, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_MUW, W1, W0),
			BPF_AWU64_WEG(BPF_MUW, W1, W2),
			BPF_AWU64_WEG(BPF_MUW, W1, W3),
			BPF_AWU64_WEG(BPF_MUW, W1, W4),
			BPF_AWU64_WEG(BPF_MUW, W1, W5),
			BPF_AWU64_WEG(BPF_MUW, W1, W6),
			BPF_AWU64_WEG(BPF_MUW, W1, W7),
			BPF_AWU64_WEG(BPF_MUW, W1, W8),
			BPF_AWU64_WEG(BPF_MUW, W1, W9),
			BPF_AWU64_IMM(BPF_MUW, W1, 10),
			BPF_AWU64_WEG(BPF_MOV, W2, W1),
			BPF_AWU64_IMM(BPF_WSH, W2, 32),
			BPF_JMP_IMM(BPF_JEQ, W2, 0x5a924, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_IMM(BPF_WSH, W1, 32),
			BPF_AWU64_IMM(BPF_AWSH, W1, 32),
			BPF_JMP_IMM(BPF_JEQ, W1, 0xebb90000, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_WEG(BPF_MUW, W2, W0),
			BPF_AWU64_WEG(BPF_MUW, W2, W1),
			BPF_AWU64_WEG(BPF_MUW, W2, W3),
			BPF_AWU64_WEG(BPF_MUW, W2, W4),
			BPF_AWU64_WEG(BPF_MUW, W2, W5),
			BPF_AWU64_WEG(BPF_MUW, W2, W6),
			BPF_AWU64_WEG(BPF_MUW, W2, W7),
			BPF_AWU64_WEG(BPF_MUW, W2, W8),
			BPF_AWU64_WEG(BPF_MUW, W2, W9),
			BPF_AWU64_IMM(BPF_MUW, W2, 10),
			BPF_AWU64_IMM(BPF_WSH, W2, 32),
			BPF_AWU64_WEG(BPF_MOV, W0, W2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x35d97ef2 } }
	},
	{	/* Mainwy checking JIT hewe. */
		"MOV WEG64",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xffffffffffffffffWW),
			BPF_MOV64_WEG(W1, W0),
			BPF_MOV64_WEG(W2, W1),
			BPF_MOV64_WEG(W3, W2),
			BPF_MOV64_WEG(W4, W3),
			BPF_MOV64_WEG(W5, W4),
			BPF_MOV64_WEG(W6, W5),
			BPF_MOV64_WEG(W7, W6),
			BPF_MOV64_WEG(W8, W7),
			BPF_MOV64_WEG(W9, W8),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_AWU64_IMM(BPF_MOV, W1, 0),
			BPF_AWU64_IMM(BPF_MOV, W2, 0),
			BPF_AWU64_IMM(BPF_MOV, W3, 0),
			BPF_AWU64_IMM(BPF_MOV, W4, 0),
			BPF_AWU64_IMM(BPF_MOV, W5, 0),
			BPF_AWU64_IMM(BPF_MOV, W6, 0),
			BPF_AWU64_IMM(BPF_MOV, W7, 0),
			BPF_AWU64_IMM(BPF_MOV, W8, 0),
			BPF_AWU64_IMM(BPF_MOV, W9, 0),
			BPF_AWU64_WEG(BPF_ADD, W0, W0),
			BPF_AWU64_WEG(BPF_ADD, W0, W1),
			BPF_AWU64_WEG(BPF_ADD, W0, W2),
			BPF_AWU64_WEG(BPF_ADD, W0, W3),
			BPF_AWU64_WEG(BPF_ADD, W0, W4),
			BPF_AWU64_WEG(BPF_ADD, W0, W5),
			BPF_AWU64_WEG(BPF_ADD, W0, W6),
			BPF_AWU64_WEG(BPF_ADD, W0, W7),
			BPF_AWU64_WEG(BPF_ADD, W0, W8),
			BPF_AWU64_WEG(BPF_ADD, W0, W9),
			BPF_AWU64_IMM(BPF_ADD, W0, 0xfefe),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfefe } }
	},
	{	/* Mainwy checking JIT hewe. */
		"MOV WEG32",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xffffffffffffffffWW),
			BPF_MOV64_WEG(W1, W0),
			BPF_MOV64_WEG(W2, W1),
			BPF_MOV64_WEG(W3, W2),
			BPF_MOV64_WEG(W4, W3),
			BPF_MOV64_WEG(W5, W4),
			BPF_MOV64_WEG(W6, W5),
			BPF_MOV64_WEG(W7, W6),
			BPF_MOV64_WEG(W8, W7),
			BPF_MOV64_WEG(W9, W8),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_AWU32_IMM(BPF_MOV, W1, 0),
			BPF_AWU32_IMM(BPF_MOV, W2, 0),
			BPF_AWU32_IMM(BPF_MOV, W3, 0),
			BPF_AWU32_IMM(BPF_MOV, W4, 0),
			BPF_AWU32_IMM(BPF_MOV, W5, 0),
			BPF_AWU32_IMM(BPF_MOV, W6, 0),
			BPF_AWU32_IMM(BPF_MOV, W7, 0),
			BPF_AWU32_IMM(BPF_MOV, W8, 0),
			BPF_AWU32_IMM(BPF_MOV, W9, 0),
			BPF_AWU64_WEG(BPF_ADD, W0, W0),
			BPF_AWU64_WEG(BPF_ADD, W0, W1),
			BPF_AWU64_WEG(BPF_ADD, W0, W2),
			BPF_AWU64_WEG(BPF_ADD, W0, W3),
			BPF_AWU64_WEG(BPF_ADD, W0, W4),
			BPF_AWU64_WEG(BPF_ADD, W0, W5),
			BPF_AWU64_WEG(BPF_ADD, W0, W6),
			BPF_AWU64_WEG(BPF_ADD, W0, W7),
			BPF_AWU64_WEG(BPF_ADD, W0, W8),
			BPF_AWU64_WEG(BPF_ADD, W0, W9),
			BPF_AWU64_IMM(BPF_ADD, W0, 0xfefe),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfefe } }
	},
	{	/* Mainwy checking JIT hewe. */
		"WD IMM64",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xffffffffffffffffWW),
			BPF_MOV64_WEG(W1, W0),
			BPF_MOV64_WEG(W2, W1),
			BPF_MOV64_WEG(W3, W2),
			BPF_MOV64_WEG(W4, W3),
			BPF_MOV64_WEG(W5, W4),
			BPF_MOV64_WEG(W6, W5),
			BPF_MOV64_WEG(W7, W6),
			BPF_MOV64_WEG(W8, W7),
			BPF_MOV64_WEG(W9, W8),
			BPF_WD_IMM64(W0, 0x0WW),
			BPF_WD_IMM64(W1, 0x0WW),
			BPF_WD_IMM64(W2, 0x0WW),
			BPF_WD_IMM64(W3, 0x0WW),
			BPF_WD_IMM64(W4, 0x0WW),
			BPF_WD_IMM64(W5, 0x0WW),
			BPF_WD_IMM64(W6, 0x0WW),
			BPF_WD_IMM64(W7, 0x0WW),
			BPF_WD_IMM64(W8, 0x0WW),
			BPF_WD_IMM64(W9, 0x0WW),
			BPF_AWU64_WEG(BPF_ADD, W0, W0),
			BPF_AWU64_WEG(BPF_ADD, W0, W1),
			BPF_AWU64_WEG(BPF_ADD, W0, W2),
			BPF_AWU64_WEG(BPF_ADD, W0, W3),
			BPF_AWU64_WEG(BPF_ADD, W0, W4),
			BPF_AWU64_WEG(BPF_ADD, W0, W5),
			BPF_AWU64_WEG(BPF_ADD, W0, W6),
			BPF_AWU64_WEG(BPF_ADD, W0, W7),
			BPF_AWU64_WEG(BPF_ADD, W0, W8),
			BPF_AWU64_WEG(BPF_ADD, W0, W9),
			BPF_AWU64_IMM(BPF_ADD, W0, 0xfefe),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfefe } }
	},
	{
		"INT: AWU MIX",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 11),
			BPF_AWU64_IMM(BPF_ADD, W0, -1),
			BPF_AWU64_IMM(BPF_MOV, W2, 2),
			BPF_AWU64_IMM(BPF_XOW, W2, 3),
			BPF_AWU64_WEG(BPF_DIV, W0, W2),
			BPF_JMP_IMM(BPF_JEQ, W0, 10, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_IMM(BPF_MOD, W0, 3),
			BPF_JMP_IMM(BPF_JEQ, W0, 1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_IMM(BPF_MOV, W0, -1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } }
	},
	{
		"INT: shifts by wegistew",
		.u.insns_int = {
			BPF_MOV64_IMM(W0, -1234),
			BPF_MOV64_IMM(W1, 1),
			BPF_AWU32_WEG(BPF_WSH, W0, W1),
			BPF_JMP_IMM(BPF_JEQ, W0, 0x7ffffd97, 1),
			BPF_EXIT_INSN(),
			BPF_MOV64_IMM(W2, 1),
			BPF_AWU64_WEG(BPF_WSH, W0, W2),
			BPF_MOV32_IMM(W4, -1234),
			BPF_JMP_WEG(BPF_JEQ, W0, W4, 1),
			BPF_EXIT_INSN(),
			BPF_AWU64_IMM(BPF_AND, W4, 63),
			BPF_AWU64_WEG(BPF_WSH, W0, W4), /* W0 <= 46 */
			BPF_MOV64_IMM(W3, 47),
			BPF_AWU64_WEG(BPF_AWSH, W0, W3),
			BPF_JMP_IMM(BPF_JEQ, W0, -617, 1),
			BPF_EXIT_INSN(),
			BPF_MOV64_IMM(W2, 1),
			BPF_AWU64_WEG(BPF_WSH, W4, W2), /* W4 = 46 << 1 */
			BPF_JMP_IMM(BPF_JEQ, W4, 92, 1),
			BPF_EXIT_INSN(),
			BPF_MOV64_IMM(W4, 4),
			BPF_AWU64_WEG(BPF_WSH, W4, W4), /* W4 = 4 << 4 */
			BPF_JMP_IMM(BPF_JEQ, W4, 64, 1),
			BPF_EXIT_INSN(),
			BPF_MOV64_IMM(W4, 5),
			BPF_AWU32_WEG(BPF_WSH, W4, W4), /* W4 = 5 << 5 */
			BPF_JMP_IMM(BPF_JEQ, W4, 160, 1),
			BPF_EXIT_INSN(),
			BPF_MOV64_IMM(W0, -1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } }
	},
#ifdef CONFIG_32BIT
	{
		"INT: 32-bit context pointew wowd owdew and zewo-extension",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_JMP32_IMM(BPF_JEQ, W1, 0, 3),
			BPF_AWU64_IMM(BPF_WSH, W1, 32),
			BPF_JMP32_IMM(BPF_JNE, W1, 0, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
#endif
	{
		"check: missing wet",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 1),
		},
		CWASSIC | FWAG_NO_DATA | FWAG_EXPECTED_FAIW,
		{ },
		{ },
		.fiww_hewpew = NUWW,
		.expected_ewwcode = -EINVAW,
	},
	{
		"check: div_k_0",
		.u.insns = {
			BPF_STMT(BPF_AWU | BPF_DIV | BPF_K, 0),
			BPF_STMT(BPF_WET | BPF_K, 0)
		},
		CWASSIC | FWAG_NO_DATA | FWAG_EXPECTED_FAIW,
		{ },
		{ },
		.fiww_hewpew = NUWW,
		.expected_ewwcode = -EINVAW,
	},
	{
		"check: unknown insn",
		.u.insns = {
			/* seccomp insn, wejected in socket fiwtew */
			BPF_STMT(BPF_WDX | BPF_W | BPF_ABS, 0),
			BPF_STMT(BPF_WET | BPF_K, 0)
		},
		CWASSIC | FWAG_EXPECTED_FAIW,
		{ },
		{ },
		.fiww_hewpew = NUWW,
		.expected_ewwcode = -EINVAW,
	},
	{
		"check: out of wange spiww/fiww",
		.u.insns = {
			BPF_STMT(BPF_STX, 16),
			BPF_STMT(BPF_WET | BPF_K, 0)
		},
		CWASSIC | FWAG_NO_DATA | FWAG_EXPECTED_FAIW,
		{ },
		{ },
		.fiww_hewpew = NUWW,
		.expected_ewwcode = -EINVAW,
	},
	{
		"JUMPS + HOWES",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JGE, 0, 13, 15),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x90c2894d, 3, 4),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x90c2894d, 1, 2),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JGE, 0, 14, 15),
			BPF_JUMP(BPF_JMP | BPF_JGE, 0, 13, 14),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x2ac28349, 2, 3),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x2ac28349, 1, 2),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JGE, 0, 14, 15),
			BPF_JUMP(BPF_JMP | BPF_JGE, 0, 13, 14),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x90d2ff41, 2, 3),
			BPF_JUMP(BPF_JMP | BPF_JEQ, 0x90d2ff41, 1, 2),
			BPF_STMT(BPF_WD | BPF_H | BPF_ABS, 0),
			BPF_STMT(BPF_WET | BPF_A, 0),
			BPF_STMT(BPF_WET | BPF_A, 0),
		},
		CWASSIC,
		{ 0x00, 0x1b, 0x21, 0x3c, 0x9d, 0xf8,
		  0x90, 0xe2, 0xba, 0x0a, 0x56, 0xb4,
		  0x08, 0x00,
		  0x45, 0x00, 0x00, 0x28, 0x00, 0x00,
		  0x20, 0x00, 0x40, 0x11, 0x00, 0x00, /* IP headew */
		  0xc0, 0xa8, 0x33, 0x01,
		  0xc0, 0xa8, 0x33, 0x02,
		  0xbb, 0xb6,
		  0xa9, 0xfa,
		  0x00, 0x14, 0x00, 0x00,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
		  0xcc, 0xcc, 0xcc, 0xcc },
		{ { 88, 0x001b } }
	},
	{
		"check: WET X",
		.u.insns = {
			BPF_STMT(BPF_WET | BPF_X, 0),
		},
		CWASSIC | FWAG_NO_DATA | FWAG_EXPECTED_FAIW,
		{ },
		{ },
		.fiww_hewpew = NUWW,
		.expected_ewwcode = -EINVAW,
	},
	{
		"check: WDX + WET X",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 42),
			BPF_STMT(BPF_WET | BPF_X, 0),
		},
		CWASSIC | FWAG_NO_DATA | FWAG_EXPECTED_FAIW,
		{ },
		{ },
		.fiww_hewpew = NUWW,
		.expected_ewwcode = -EINVAW,
	},
	{	/* Mainwy checking JIT hewe. */
		"M[]: awt STX + WDX",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 100),
			BPF_STMT(BPF_STX, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 0),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 1),
			BPF_STMT(BPF_WDX | BPF_MEM, 1),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 2),
			BPF_STMT(BPF_WDX | BPF_MEM, 2),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 3),
			BPF_STMT(BPF_WDX | BPF_MEM, 3),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 4),
			BPF_STMT(BPF_WDX | BPF_MEM, 4),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 5),
			BPF_STMT(BPF_WDX | BPF_MEM, 5),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 6),
			BPF_STMT(BPF_WDX | BPF_MEM, 6),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 7),
			BPF_STMT(BPF_WDX | BPF_MEM, 7),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 8),
			BPF_STMT(BPF_WDX | BPF_MEM, 8),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 9),
			BPF_STMT(BPF_WDX | BPF_MEM, 9),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 10),
			BPF_STMT(BPF_WDX | BPF_MEM, 10),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 11),
			BPF_STMT(BPF_WDX | BPF_MEM, 11),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 12),
			BPF_STMT(BPF_WDX | BPF_MEM, 12),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 13),
			BPF_STMT(BPF_WDX | BPF_MEM, 13),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 14),
			BPF_STMT(BPF_WDX | BPF_MEM, 14),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_STX, 15),
			BPF_STMT(BPF_WDX | BPF_MEM, 15),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 1),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WET | BPF_A, 0),
		},
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 116 } },
	},
	{	/* Mainwy checking JIT hewe. */
		"M[]: fuww STX + fuww WDX",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0xbadfeedb),
			BPF_STMT(BPF_STX, 0),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xecabedae),
			BPF_STMT(BPF_STX, 1),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xafccfeaf),
			BPF_STMT(BPF_STX, 2),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xbffdcedc),
			BPF_STMT(BPF_STX, 3),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xfbbbdccb),
			BPF_STMT(BPF_STX, 4),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xfbabcbda),
			BPF_STMT(BPF_STX, 5),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xaedecbdb),
			BPF_STMT(BPF_STX, 6),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xadebbade),
			BPF_STMT(BPF_STX, 7),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xfcfcfaec),
			BPF_STMT(BPF_STX, 8),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xbcdddbdc),
			BPF_STMT(BPF_STX, 9),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xfeefdfac),
			BPF_STMT(BPF_STX, 10),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xcddcdeea),
			BPF_STMT(BPF_STX, 11),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xaccfaebb),
			BPF_STMT(BPF_STX, 12),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xbdcccdcf),
			BPF_STMT(BPF_STX, 13),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xaaedecde),
			BPF_STMT(BPF_STX, 14),
			BPF_STMT(BPF_WDX | BPF_IMM, 0xfaeacdad),
			BPF_STMT(BPF_STX, 15),
			BPF_STMT(BPF_WDX | BPF_MEM, 0),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 1),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 2),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 3),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 4),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 5),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 6),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 7),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 8),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 9),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 10),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 11),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 12),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 13),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 14),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WDX | BPF_MEM, 15),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0),
		},
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0x2a5a5e5 } },
	},
	{
		"check: SKF_AD_MAX",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF + SKF_AD_MAX),
			BPF_STMT(BPF_WET | BPF_A, 0),
		},
		CWASSIC | FWAG_NO_DATA | FWAG_EXPECTED_FAIW,
		{ },
		{ },
		.fiww_hewpew = NUWW,
		.expected_ewwcode = -EINVAW,
	},
	{	/* Passes checkew but faiws duwing wuntime. */
		"WD [SKF_AD_OFF-1]",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_W | BPF_ABS,
				 SKF_AD_OFF - 1),
			BPF_STMT(BPF_WET | BPF_K, 1),
		},
		CWASSIC,
		{ },
		{ { 1, 0 } },
	},
	{
		"woad 64-bit immediate",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x567800001234WW),
			BPF_MOV64_WEG(W2, W1),
			BPF_MOV64_WEG(W3, W2),
			BPF_AWU64_IMM(BPF_WSH, W2, 32),
			BPF_AWU64_IMM(BPF_WSH, W3, 32),
			BPF_AWU64_IMM(BPF_WSH, W3, 32),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_JMP_IMM(BPF_JEQ, W2, 0x5678, 1),
			BPF_EXIT_INSN(),
			BPF_JMP_IMM(BPF_JEQ, W3, 0x1234, 1),
			BPF_EXIT_INSN(),
			BPF_WD_IMM64(W0, 0x1ffffffffWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 32), /* W0 = 1 */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	/* BPF_AWU | BPF_MOV | BPF_X */
	{
		"AWU_MOV_X: dst = 2",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU32_WEG(BPF_MOV, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU_MOV_X: dst = 4294967295",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W1, 4294967295U),
			BPF_AWU32_WEG(BPF_MOV, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 4294967295U } },
	},
	{
		"AWU64_MOV_X: dst = 2",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU64_WEG(BPF_MOV, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU64_MOV_X: dst = 4294967295",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W1, 4294967295U),
			BPF_AWU64_WEG(BPF_MOV, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 4294967295U } },
	},
	/* BPF_AWU | BPF_MOV | BPF_K */
	{
		"AWU_MOV_K: dst = 2",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU_MOV_K: dst = 4294967295",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 4294967295U),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 4294967295U } },
	},
	{
		"AWU_MOV_K: 0x0000ffffffff0000 = 0x00000000ffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000ffffffff0000WW),
			BPF_WD_IMM64(W3, 0x00000000ffffffffWW),
			BPF_AWU32_IMM(BPF_MOV, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU_MOV_K: smaww negative",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123 } }
	},
	{
		"AWU_MOV_K: smaww negative zewo extension",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } }
	},
	{
		"AWU_MOV_K: wawge negative",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123456789),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123456789 } }
	},
	{
		"AWU_MOV_K: wawge negative zewo extension",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123456789),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } }
	},
	{
		"AWU64_MOV_K: dst = 2",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU64_MOV_K: dst = 2147483647",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 2147483647),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2147483647 } },
	},
	{
		"AWU64_OW_K: dst = 0x0",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000ffffffff0000WW),
			BPF_WD_IMM64(W3, 0x0),
			BPF_AWU64_IMM(BPF_MOV, W2, 0x0),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_MOV_K: dst = -1",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000ffffffff0000WW),
			BPF_WD_IMM64(W3, 0xffffffffffffffffWW),
			BPF_AWU64_IMM(BPF_MOV, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_MOV_K: smaww negative",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, -123),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123 } }
	},
	{
		"AWU64_MOV_K: smaww negative sign extension",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, -123),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } }
	},
	{
		"AWU64_MOV_K: wawge negative",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, -123456789),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123456789 } }
	},
	{
		"AWU64_MOV_K: wawge negative sign extension",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, -123456789),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } }
	},
	/* MOVSX32 */
	{
		"AWU_MOVSX | BPF_B",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x00000000ffffffefWW),
			BPF_WD_IMM64(W3, 0xdeadbeefdeadbeefWW),
			BPF_MOVSX32_WEG(W1, W3, 8),
			BPF_JMP_WEG(BPF_JEQ, W2, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU_MOVSX | BPF_H",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x00000000ffffbeefWW),
			BPF_WD_IMM64(W3, 0xdeadbeefdeadbeefWW),
			BPF_MOVSX32_WEG(W1, W3, 16),
			BPF_JMP_WEG(BPF_JEQ, W2, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	/* MOVSX64 WEG */
	{
		"AWU64_MOVSX | BPF_B",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0xffffffffffffffefWW),
			BPF_WD_IMM64(W3, 0xdeadbeefdeadbeefWW),
			BPF_MOVSX64_WEG(W1, W3, 8),
			BPF_JMP_WEG(BPF_JEQ, W2, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_MOVSX | BPF_H",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0xffffffffffffbeefWW),
			BPF_WD_IMM64(W3, 0xdeadbeefdeadbeefWW),
			BPF_MOVSX64_WEG(W1, W3, 16),
			BPF_JMP_WEG(BPF_JEQ, W2, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_MOVSX | BPF_W",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0xffffffffdeadbeefWW),
			BPF_WD_IMM64(W3, 0xdeadbeefdeadbeefWW),
			BPF_MOVSX64_WEG(W1, W3, 32),
			BPF_JMP_WEG(BPF_JEQ, W2, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	/* BPF_AWU | BPF_ADD | BPF_X */
	{
		"AWU_ADD_X: 1 + 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU32_WEG(BPF_ADD, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_ADD_X: 1 + 4294967294 = 4294967295",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 4294967294U),
			BPF_AWU32_WEG(BPF_ADD, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 4294967295U } },
	},
	{
		"AWU_ADD_X: 2 + 4294967294 = 0",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_WD_IMM64(W1, 4294967294U),
			BPF_AWU32_WEG(BPF_ADD, W0, W1),
			BPF_JMP_IMM(BPF_JEQ, W0, 0, 2),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_ADD_X: 1 + 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU64_WEG(BPF_ADD, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_ADD_X: 1 + 4294967294 = 4294967295",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 4294967294U),
			BPF_AWU64_WEG(BPF_ADD, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 4294967295U } },
	},
	{
		"AWU64_ADD_X: 2 + 4294967294 = 4294967296",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_WD_IMM64(W1, 4294967294U),
			BPF_WD_IMM64(W2, 4294967296UWW),
			BPF_AWU64_WEG(BPF_ADD, W0, W1),
			BPF_JMP_WEG(BPF_JEQ, W0, W2, 2),
			BPF_MOV32_IMM(W0, 0),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_AWU | BPF_ADD | BPF_K */
	{
		"AWU_ADD_K: 1 + 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_ADD, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_ADD_K: 3 + 0 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_ADD, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_ADD_K: 1 + 4294967294 = 4294967295",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_ADD, W0, 4294967294U),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 4294967295U } },
	},
	{
		"AWU_ADD_K: 4294967294 + 2 = 0",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 4294967294U),
			BPF_AWU32_IMM(BPF_ADD, W0, 2),
			BPF_JMP_IMM(BPF_JEQ, W0, 0, 2),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU_ADD_K: 0 + (-1) = 0x00000000ffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0),
			BPF_WD_IMM64(W3, 0x00000000ffffffff),
			BPF_AWU32_IMM(BPF_ADD, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU_ADD_K: 0 + 0xffff = 0xffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0),
			BPF_WD_IMM64(W3, 0xffff),
			BPF_AWU32_IMM(BPF_ADD, W2, 0xffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU_ADD_K: 0 + 0x7fffffff = 0x7fffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0),
			BPF_WD_IMM64(W3, 0x7fffffff),
			BPF_AWU32_IMM(BPF_ADD, W2, 0x7fffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU_ADD_K: 0 + 0x80000000 = 0x80000000",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0),
			BPF_WD_IMM64(W3, 0x80000000),
			BPF_AWU32_IMM(BPF_ADD, W2, 0x80000000),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU_ADD_K: 0 + 0x80008000 = 0x80008000",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0),
			BPF_WD_IMM64(W3, 0x80008000),
			BPF_AWU32_IMM(BPF_ADD, W2, 0x80008000),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_ADD_K: 1 + 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU64_IMM(BPF_ADD, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_ADD_K: 3 + 0 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU64_IMM(BPF_ADD, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_ADD_K: 1 + 2147483646 = 2147483647",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU64_IMM(BPF_ADD, W0, 2147483646),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2147483647 } },
	},
	{
		"AWU64_ADD_K: 4294967294 + 2 = 4294967296",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 4294967294U),
			BPF_WD_IMM64(W1, 4294967296UWW),
			BPF_AWU64_IMM(BPF_ADD, W0, 2),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_ADD_K: 2147483646 + -2147483647 = -1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2147483646),
			BPF_AWU64_IMM(BPF_ADD, W0, -2147483647),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } },
	},
	{
		"AWU64_ADD_K: 1 + 0 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x1),
			BPF_WD_IMM64(W3, 0x1),
			BPF_AWU64_IMM(BPF_ADD, W2, 0x0),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_ADD_K: 0 + (-1) = 0xffffffffffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0),
			BPF_WD_IMM64(W3, 0xffffffffffffffffWW),
			BPF_AWU64_IMM(BPF_ADD, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_ADD_K: 0 + 0xffff = 0xffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0),
			BPF_WD_IMM64(W3, 0xffff),
			BPF_AWU64_IMM(BPF_ADD, W2, 0xffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_ADD_K: 0 + 0x7fffffff = 0x7fffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0),
			BPF_WD_IMM64(W3, 0x7fffffff),
			BPF_AWU64_IMM(BPF_ADD, W2, 0x7fffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_ADD_K: 0 + 0x80000000 = 0xffffffff80000000",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0),
			BPF_WD_IMM64(W3, 0xffffffff80000000WW),
			BPF_AWU64_IMM(BPF_ADD, W2, 0x80000000),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU_ADD_K: 0 + 0x80008000 = 0xffffffff80008000",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0),
			BPF_WD_IMM64(W3, 0xffffffff80008000WW),
			BPF_AWU64_IMM(BPF_ADD, W2, 0x80008000),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	/* BPF_AWU | BPF_SUB | BPF_X */
	{
		"AWU_SUB_X: 3 - 1 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_MOV, W1, 1),
			BPF_AWU32_WEG(BPF_SUB, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU_SUB_X: 4294967295 - 4294967294 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 4294967295U),
			BPF_AWU32_IMM(BPF_MOV, W1, 4294967294U),
			BPF_AWU32_WEG(BPF_SUB, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_SUB_X: 3 - 1 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_MOV, W1, 1),
			BPF_AWU64_WEG(BPF_SUB, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU64_SUB_X: 4294967295 - 4294967294 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 4294967295U),
			BPF_AWU32_IMM(BPF_MOV, W1, 4294967294U),
			BPF_AWU64_WEG(BPF_SUB, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_AWU | BPF_SUB | BPF_K */
	{
		"AWU_SUB_K: 3 - 1 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_SUB, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU_SUB_K: 3 - 0 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_SUB, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_SUB_K: 4294967295 - 4294967294 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 4294967295U),
			BPF_AWU32_IMM(BPF_SUB, W0, 4294967294U),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_SUB_K: 3 - 1 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU64_IMM(BPF_SUB, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU64_SUB_K: 3 - 0 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU64_IMM(BPF_SUB, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_SUB_K: 4294967294 - 4294967295 = -1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 4294967294U),
			BPF_AWU64_IMM(BPF_SUB, W0, 4294967295U),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } },
	},
	{
		"AWU64_ADD_K: 2147483646 - 2147483647 = -1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2147483646),
			BPF_AWU64_IMM(BPF_SUB, W0, 2147483647),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } },
	},
	/* BPF_AWU | BPF_MUW | BPF_X */
	{
		"AWU_MUW_X: 2 * 3 = 6",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 3),
			BPF_AWU32_WEG(BPF_MUW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 6 } },
	},
	{
		"AWU_MUW_X: 2 * 0x7FFFFFF8 = 0xFFFFFFF0",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 0x7FFFFFF8),
			BPF_AWU32_WEG(BPF_MUW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xFFFFFFF0 } },
	},
	{
		"AWU_MUW_X: -1 * -1 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, -1),
			BPF_AWU32_IMM(BPF_MOV, W1, -1),
			BPF_AWU32_WEG(BPF_MUW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_MUW_X: 2 * 3 = 6",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 3),
			BPF_AWU64_WEG(BPF_MUW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 6 } },
	},
	{
		"AWU64_MUW_X: 1 * 2147483647 = 2147483647",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 2147483647),
			BPF_AWU64_WEG(BPF_MUW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2147483647 } },
	},
	{
		"AWU64_MUW_X: 64x64 muwtipwy, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0fedcba987654321WW),
			BPF_WD_IMM64(W1, 0x123456789abcdef0WW),
			BPF_AWU64_WEG(BPF_MUW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xe5618cf0 } }
	},
	{
		"AWU64_MUW_X: 64x64 muwtipwy, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0fedcba987654321WW),
			BPF_WD_IMM64(W1, 0x123456789abcdef0WW),
			BPF_AWU64_WEG(BPF_MUW, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x2236d88f } }
	},
	/* BPF_AWU | BPF_MUW | BPF_K */
	{
		"AWU_MUW_K: 2 * 3 = 6",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_AWU32_IMM(BPF_MUW, W0, 3),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 6 } },
	},
	{
		"AWU_MUW_K: 3 * 1 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_MUW, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_MUW_K: 2 * 0x7FFFFFF8 = 0xFFFFFFF0",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_AWU32_IMM(BPF_MUW, W0, 0x7FFFFFF8),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xFFFFFFF0 } },
	},
	{
		"AWU_MUW_K: 1 * (-1) = 0x00000000ffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x1),
			BPF_WD_IMM64(W3, 0x00000000ffffffff),
			BPF_AWU32_IMM(BPF_MUW, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_MUW_K: 2 * 3 = 6",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_AWU64_IMM(BPF_MUW, W0, 3),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 6 } },
	},
	{
		"AWU64_MUW_K: 3 * 1 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU64_IMM(BPF_MUW, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_MUW_K: 1 * 2147483647 = 2147483647",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU64_IMM(BPF_MUW, W0, 2147483647),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2147483647 } },
	},
	{
		"AWU64_MUW_K: 1 * -2147483647 = -2147483647",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU64_IMM(BPF_MUW, W0, -2147483647),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -2147483647 } },
	},
	{
		"AWU64_MUW_K: 1 * (-1) = 0xffffffffffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x1),
			BPF_WD_IMM64(W3, 0xffffffffffffffffWW),
			BPF_AWU64_IMM(BPF_MUW, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_MUW_K: 64x32 muwtipwy, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU64_IMM(BPF_MUW, W0, 0x12345678),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xe242d208 } }
	},
	{
		"AWU64_MUW_K: 64x32 muwtipwy, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU64_IMM(BPF_MUW, W0, 0x12345678),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xc28f5c28 } }
	},
	/* BPF_AWU | BPF_DIV | BPF_X */
	{
		"AWU_DIV_X: 6 / 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 6),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU32_WEG(BPF_DIV, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_DIV_X: 4294967295 / 4294967295 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 4294967295U),
			BPF_AWU32_IMM(BPF_MOV, W1, 4294967295U),
			BPF_AWU32_WEG(BPF_DIV, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_DIV_X: 6 / 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 6),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU64_WEG(BPF_DIV, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_DIV_X: 2147483647 / 2147483647 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2147483647),
			BPF_AWU32_IMM(BPF_MOV, W1, 2147483647),
			BPF_AWU64_WEG(BPF_DIV, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_DIV_X: 0xffffffffffffffff / (-1) = 0x0000000000000001",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0xffffffffffffffffWW),
			BPF_WD_IMM64(W4, 0xffffffffffffffffWW),
			BPF_WD_IMM64(W3, 0x0000000000000001WW),
			BPF_AWU64_WEG(BPF_DIV, W2, W4),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	/* BPF_AWU | BPF_DIV | BPF_K */
	{
		"AWU_DIV_K: 6 / 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 6),
			BPF_AWU32_IMM(BPF_DIV, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_DIV_K: 3 / 1 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_DIV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_DIV_K: 4294967295 / 4294967295 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 4294967295U),
			BPF_AWU32_IMM(BPF_DIV, W0, 4294967295U),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU_DIV_K: 0xffffffffffffffff / (-1) = 0x1",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0xffffffffffffffffWW),
			BPF_WD_IMM64(W3, 0x1UW),
			BPF_AWU32_IMM(BPF_DIV, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_DIV_K: 6 / 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 6),
			BPF_AWU64_IMM(BPF_DIV, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_DIV_K: 3 / 1 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU64_IMM(BPF_DIV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_DIV_K: 2147483647 / 2147483647 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2147483647),
			BPF_AWU64_IMM(BPF_DIV, W0, 2147483647),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_DIV_K: 0xffffffffffffffff / (-1) = 0x0000000000000001",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0xffffffffffffffffWW),
			BPF_WD_IMM64(W3, 0x0000000000000001WW),
			BPF_AWU64_IMM(BPF_DIV, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	/* BPF_AWU | BPF_MOD | BPF_X */
	{
		"AWU_MOD_X: 3 % 2 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU32_WEG(BPF_MOD, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU_MOD_X: 4294967295 % 4294967293 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 4294967295U),
			BPF_AWU32_IMM(BPF_MOV, W1, 4294967293U),
			BPF_AWU32_WEG(BPF_MOD, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU64_MOD_X: 3 % 2 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU64_WEG(BPF_MOD, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_MOD_X: 2147483647 % 2147483645 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2147483647),
			BPF_AWU32_IMM(BPF_MOV, W1, 2147483645),
			BPF_AWU64_WEG(BPF_MOD, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	/* BPF_AWU | BPF_MOD | BPF_K */
	{
		"AWU_MOD_K: 3 % 2 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_MOD, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU_MOD_K: 3 % 1 = 0",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_MOD, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
	},
	{
		"AWU_MOD_K: 4294967295 % 4294967293 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 4294967295U),
			BPF_AWU32_IMM(BPF_MOD, W0, 4294967293U),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU64_MOD_K: 3 % 2 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU64_IMM(BPF_MOD, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_MOD_K: 3 % 1 = 0",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU64_IMM(BPF_MOD, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
	},
	{
		"AWU64_MOD_K: 2147483647 % 2147483645 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2147483647),
			BPF_AWU64_IMM(BPF_MOD, W0, 2147483645),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	/* BPF_AWU | BPF_DIV | BPF_X off=1 (SDIV) */
	{
		"AWU_SDIV_X: -6 / 2 = -3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, -6),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU32_WEG_OFF(BPF_DIV, W0, W1, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -3 } },
	},
	/* BPF_AWU | BPF_DIV | BPF_K off=1 (SDIV) */
	{
		"AWU_SDIV_K: -6 / 2 = -3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, -6),
			BPF_AWU32_IMM_OFF(BPF_DIV, W0, 2, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -3 } },
	},
	/* BPF_AWU64 | BPF_DIV | BPF_X off=1 (SDIV64) */
	{
		"AWU64_SDIV_X: -6 / 2 = -3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, -6),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU64_WEG_OFF(BPF_DIV, W0, W1, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -3 } },
	},
	/* BPF_AWU64 | BPF_DIV | BPF_K off=1 (SDIV64) */
	{
		"AWU64_SDIV_K: -6 / 2 = -3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, -6),
			BPF_AWU64_IMM_OFF(BPF_DIV, W0, 2, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -3 } },
	},
	/* BPF_AWU | BPF_MOD | BPF_X off=1 (SMOD) */
	{
		"AWU_SMOD_X: -7 % 2 = -1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, -7),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU32_WEG_OFF(BPF_MOD, W0, W1, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } },
	},
	/* BPF_AWU | BPF_MOD | BPF_K off=1 (SMOD) */
	{
		"AWU_SMOD_K: -7 % 2 = -1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, -7),
			BPF_AWU32_IMM_OFF(BPF_MOD, W0, 2, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } },
	},
	/* BPF_AWU64 | BPF_MOD | BPF_X off=1 (SMOD64) */
	{
		"AWU64_SMOD_X: -7 % 2 = -1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, -7),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU64_WEG_OFF(BPF_MOD, W0, W1, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } },
	},
	/* BPF_AWU64 | BPF_MOD | BPF_K off=1 (SMOD64) */
	{
		"AWU64_SMOD_K: -7 % 2 = -1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, -7),
			BPF_AWU64_IMM_OFF(BPF_MOD, W0, 2, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } },
	},
	/* BPF_AWU | BPF_AND | BPF_X */
	{
		"AWU_AND_X: 3 & 2 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU32_WEG(BPF_AND, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU_AND_X: 0xffffffff & 0xffffffff = 0xffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xffffffff),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xffffffff),
			BPF_AWU32_WEG(BPF_AND, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
	},
	{
		"AWU64_AND_X: 3 & 2 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU64_WEG(BPF_AND, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU64_AND_X: 0xffffffff & 0xffffffff = 0xffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xffffffff),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xffffffff),
			BPF_AWU64_WEG(BPF_AND, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
	},
	/* BPF_AWU | BPF_AND | BPF_K */
	{
		"AWU_AND_K: 3 & 2 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU32_IMM(BPF_AND, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU_AND_K: 0xffffffff & 0xffffffff = 0xffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xffffffff),
			BPF_AWU32_IMM(BPF_AND, W0, 0xffffffff),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
	},
	{
		"AWU_AND_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x01020304),
			BPF_AWU32_IMM(BPF_AND, W0, 15),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 4 } }
	},
	{
		"AWU_AND_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0xf1f2f3f4),
			BPF_AWU32_IMM(BPF_AND, W0, 0xafbfcfdf),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xa1b2c3d4 } }
	},
	{
		"AWU_AND_K: Zewo extension",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_WD_IMM64(W1, 0x0000000080a0c0e0WW),
			BPF_AWU32_IMM(BPF_AND, W0, 0xf0f0f0f0),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{
		"AWU64_AND_K: 3 & 2 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU64_IMM(BPF_AND, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU64_AND_K: 0xffffffff & 0xffffffff = 0xffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xffffffff),
			BPF_AWU64_IMM(BPF_AND, W0, 0xffffffff),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
	},
	{
		"AWU64_AND_K: 0x0000ffffffff0000 & 0x0 = 0x0000000000000000",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000ffffffff0000WW),
			BPF_WD_IMM64(W3, 0x0000000000000000WW),
			BPF_AWU64_IMM(BPF_AND, W2, 0x0),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_AND_K: 0x0000ffffffff0000 & -1 = 0x0000ffffffff0000",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000ffffffff0000WW),
			BPF_WD_IMM64(W3, 0x0000ffffffff0000WW),
			BPF_AWU64_IMM(BPF_AND, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_AND_K: 0xffffffffffffffff & -1 = 0xffffffffffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0xffffffffffffffffWW),
			BPF_WD_IMM64(W3, 0xffffffffffffffffWW),
			BPF_AWU64_IMM(BPF_AND, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_AND_K: Sign extension 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_WD_IMM64(W1, 0x00000000090b0d0fWW),
			BPF_AWU64_IMM(BPF_AND, W0, 0x0f0f0f0f),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{
		"AWU64_AND_K: Sign extension 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_WD_IMM64(W1, 0x0123456780a0c0e0WW),
			BPF_AWU64_IMM(BPF_AND, W0, 0xf0f0f0f0),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	/* BPF_AWU | BPF_OW | BPF_X */
	{
		"AWU_OW_X: 1 | 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU32_WEG(BPF_OW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_OW_X: 0x0 | 0xffffffff = 0xffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xffffffff),
			BPF_AWU32_WEG(BPF_OW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
	},
	{
		"AWU64_OW_X: 1 | 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 2),
			BPF_AWU64_WEG(BPF_OW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_OW_X: 0 | 0xffffffff = 0xffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xffffffff),
			BPF_AWU64_WEG(BPF_OW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
	},
	/* BPF_AWU | BPF_OW | BPF_K */
	{
		"AWU_OW_K: 1 | 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_OW, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_OW_K: 0 & 0xffffffff = 0xffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0),
			BPF_AWU32_IMM(BPF_OW, W0, 0xffffffff),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
	},
	{
		"AWU_OW_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x01020304),
			BPF_AWU32_IMM(BPF_OW, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x01020305 } }
	},
	{
		"AWU_OW_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x01020304),
			BPF_AWU32_IMM(BPF_OW, W0, 0xa0b0c0d0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xa1b2c3d4 } }
	},
	{
		"AWU_OW_K: Zewo extension",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_WD_IMM64(W1, 0x00000000f9fbfdffWW),
			BPF_AWU32_IMM(BPF_OW, W0, 0xf0f0f0f0),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{
		"AWU64_OW_K: 1 | 2 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU64_IMM(BPF_OW, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_OW_K: 0 & 0xffffffff = 0xffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0),
			BPF_AWU64_IMM(BPF_OW, W0, 0xffffffff),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
	},
	{
		"AWU64_OW_K: 0x0000ffffffff0000 | 0x0 = 0x0000ffffffff0000",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000ffffffff0000WW),
			BPF_WD_IMM64(W3, 0x0000ffffffff0000WW),
			BPF_AWU64_IMM(BPF_OW, W2, 0x0),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_OW_K: 0x0000ffffffff0000 | -1 = 0xffffffffffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000ffffffff0000WW),
			BPF_WD_IMM64(W3, 0xffffffffffffffffWW),
			BPF_AWU64_IMM(BPF_OW, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_OW_K: 0x000000000000000 | -1 = 0xffffffffffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000000000000000WW),
			BPF_WD_IMM64(W3, 0xffffffffffffffffWW),
			BPF_AWU64_IMM(BPF_OW, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_OW_K: Sign extension 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_WD_IMM64(W1, 0x012345678fafcfefWW),
			BPF_AWU64_IMM(BPF_OW, W0, 0x0f0f0f0f),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{
		"AWU64_OW_K: Sign extension 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_WD_IMM64(W1, 0xfffffffff9fbfdffWW),
			BPF_AWU64_IMM(BPF_OW, W0, 0xf0f0f0f0),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	/* BPF_AWU | BPF_XOW | BPF_X */
	{
		"AWU_XOW_X: 5 ^ 6 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 5),
			BPF_AWU32_IMM(BPF_MOV, W1, 6),
			BPF_AWU32_WEG(BPF_XOW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_XOW_X: 0x1 ^ 0xffffffff = 0xfffffffe",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xffffffff),
			BPF_AWU32_WEG(BPF_XOW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } },
	},
	{
		"AWU64_XOW_X: 5 ^ 6 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 5),
			BPF_AWU32_IMM(BPF_MOV, W1, 6),
			BPF_AWU64_WEG(BPF_XOW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_XOW_X: 1 ^ 0xffffffff = 0xfffffffe",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xffffffff),
			BPF_AWU64_WEG(BPF_XOW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } },
	},
	/* BPF_AWU | BPF_XOW | BPF_K */
	{
		"AWU_XOW_K: 5 ^ 6 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 5),
			BPF_AWU32_IMM(BPF_XOW, W0, 6),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU_XOW_K: 1 ^ 0xffffffff = 0xfffffffe",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_XOW, W0, 0xffffffff),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } },
	},
	{
		"AWU_XOW_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x01020304),
			BPF_AWU32_IMM(BPF_XOW, W0, 15),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x0102030b } }
	},
	{
		"AWU_XOW_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0xf1f2f3f4),
			BPF_AWU32_IMM(BPF_XOW, W0, 0xafbfcfdf),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x5e4d3c2b } }
	},
	{
		"AWU_XOW_K: Zewo extension",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_WD_IMM64(W1, 0x00000000795b3d1fWW),
			BPF_AWU32_IMM(BPF_XOW, W0, 0xf0f0f0f0),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{
		"AWU64_XOW_K: 5 ^ 6 = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 5),
			BPF_AWU64_IMM(BPF_XOW, W0, 6),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_XOW_K: 1 ^ 0xffffffff = 0xfffffffe",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU64_IMM(BPF_XOW, W0, 0xffffffff),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } },
	},
	{
		"AWU64_XOW_K: 0x0000ffffffff0000 ^ 0x0 = 0x0000ffffffff0000",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000ffffffff0000WW),
			BPF_WD_IMM64(W3, 0x0000ffffffff0000WW),
			BPF_AWU64_IMM(BPF_XOW, W2, 0x0),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_XOW_K: 0x0000ffffffff0000 ^ -1 = 0xffff00000000ffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000ffffffff0000WW),
			BPF_WD_IMM64(W3, 0xffff00000000ffffWW),
			BPF_AWU64_IMM(BPF_XOW, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_XOW_K: 0x000000000000000 ^ -1 = 0xffffffffffffffff",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x0000000000000000WW),
			BPF_WD_IMM64(W3, 0xffffffffffffffffWW),
			BPF_AWU64_IMM(BPF_XOW, W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
	},
	{
		"AWU64_XOW_K: Sign extension 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_WD_IMM64(W1, 0x0123456786a4c2e0WW),
			BPF_AWU64_IMM(BPF_XOW, W0, 0x0f0f0f0f),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{
		"AWU64_XOW_K: Sign extension 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_WD_IMM64(W1, 0xfedcba98795b3d1fWW),
			BPF_AWU64_IMM(BPF_XOW, W0, 0xf0f0f0f0),
			BPF_JMP_WEG(BPF_JEQ, W0, W1, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	/* BPF_AWU | BPF_WSH | BPF_X */
	{
		"AWU_WSH_X: 1 << 1 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 1),
			BPF_AWU32_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU_WSH_X: 1 << 31 = 0x80000000",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 31),
			BPF_AWU32_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x80000000 } },
	},
	{
		"AWU_WSH_X: 0x12345678 << 12 = 0x45678000",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x12345678),
			BPF_AWU32_IMM(BPF_MOV, W1, 12),
			BPF_AWU32_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x45678000 } }
	},
	{
		"AWU64_WSH_X: 1 << 1 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 1),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU64_WSH_X: 1 << 31 = 0x80000000",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_MOV, W1, 31),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x80000000 } },
	},
	{
		"AWU64_WSH_X: Shift < 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 12),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xbcdef000 } }
	},
	{
		"AWU64_WSH_X: Shift < 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 12),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x3456789a } }
	},
	{
		"AWU64_WSH_X: Shift > 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 36),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } }
	},
	{
		"AWU64_WSH_X: Shift > 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 36),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x9abcdef0 } }
	},
	{
		"AWU64_WSH_X: Shift == 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 32),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } }
	},
	{
		"AWU64_WSH_X: Shift == 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 32),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x89abcdef } }
	},
	{
		"AWU64_WSH_X: Zewo shift, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 0),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x89abcdef } }
	},
	{
		"AWU64_WSH_X: Zewo shift, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 0),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x01234567 } }
	},
	/* BPF_AWU | BPF_WSH | BPF_K */
	{
		"AWU_WSH_K: 1 << 1 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_WSH, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU_WSH_K: 1 << 31 = 0x80000000",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU32_IMM(BPF_WSH, W0, 31),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x80000000 } },
	},
	{
		"AWU_WSH_K: 0x12345678 << 12 = 0x45678000",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x12345678),
			BPF_AWU32_IMM(BPF_WSH, W0, 12),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x45678000 } }
	},
	{
		"AWU_WSH_K: 0x12345678 << 0 = 0x12345678",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x12345678),
			BPF_AWU32_IMM(BPF_WSH, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x12345678 } }
	},
	{
		"AWU64_WSH_K: 1 << 1 = 2",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU64_IMM(BPF_WSH, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"AWU64_WSH_K: 1 << 31 = 0x80000000",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 1),
			BPF_AWU64_IMM(BPF_WSH, W0, 31),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x80000000 } },
	},
	{
		"AWU64_WSH_K: Shift < 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 12),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xbcdef000 } }
	},
	{
		"AWU64_WSH_K: Shift < 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 12),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x3456789a } }
	},
	{
		"AWU64_WSH_K: Shift > 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 36),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } }
	},
	{
		"AWU64_WSH_K: Shift > 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 36),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x9abcdef0 } }
	},
	{
		"AWU64_WSH_K: Shift == 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } }
	},
	{
		"AWU64_WSH_K: Shift == 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x89abcdef } }
	},
	{
		"AWU64_WSH_K: Zewo shift",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x89abcdef } }
	},
	/* BPF_AWU | BPF_WSH | BPF_X */
	{
		"AWU_WSH_X: 2 >> 1 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 1),
			BPF_AWU32_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU_WSH_X: 0x80000000 >> 31 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x80000000),
			BPF_AWU32_IMM(BPF_MOV, W1, 31),
			BPF_AWU32_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU_WSH_X: 0x12345678 >> 20 = 0x123",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x12345678),
			BPF_AWU32_IMM(BPF_MOV, W1, 20),
			BPF_AWU32_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x123 } }
	},
	{
		"AWU64_WSH_X: 2 >> 1 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 1),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_WSH_X: 0x80000000 >> 31 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x80000000),
			BPF_AWU32_IMM(BPF_MOV, W1, 31),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_WSH_X: Shift < 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 12),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x56789abc } }
	},
	{
		"AWU64_WSH_X: Shift < 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 12),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x00081234 } }
	},
	{
		"AWU64_WSH_X: Shift > 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 36),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x08123456 } }
	},
	{
		"AWU64_WSH_X: Shift > 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 36),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } }
	},
	{
		"AWU64_WSH_X: Shift == 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 32),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x81234567 } }
	},
	{
		"AWU64_WSH_X: Shift == 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 32),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } }
	},
	{
		"AWU64_WSH_X: Zewo shift, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 0),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x89abcdef } }
	},
	{
		"AWU64_WSH_X: Zewo shift, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 0),
			BPF_AWU64_WEG(BPF_WSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x81234567 } }
	},
	/* BPF_AWU | BPF_WSH | BPF_K */
	{
		"AWU_WSH_K: 2 >> 1 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_AWU32_IMM(BPF_WSH, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU_WSH_K: 0x80000000 >> 31 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x80000000),
			BPF_AWU32_IMM(BPF_WSH, W0, 31),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU_WSH_K: 0x12345678 >> 20 = 0x123",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x12345678),
			BPF_AWU32_IMM(BPF_WSH, W0, 20),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x123 } }
	},
	{
		"AWU_WSH_K: 0x12345678 >> 0 = 0x12345678",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x12345678),
			BPF_AWU32_IMM(BPF_WSH, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x12345678 } }
	},
	{
		"AWU64_WSH_K: 2 >> 1 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 2),
			BPF_AWU64_IMM(BPF_WSH, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_WSH_K: 0x80000000 >> 31 = 1",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x80000000),
			BPF_AWU64_IMM(BPF_WSH, W0, 31),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"AWU64_WSH_K: Shift < 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 12),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x56789abc } }
	},
	{
		"AWU64_WSH_K: Shift < 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 12),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x00081234 } }
	},
	{
		"AWU64_WSH_K: Shift > 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 36),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x08123456 } }
	},
	{
		"AWU64_WSH_K: Shift > 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 36),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } }
	},
	{
		"AWU64_WSH_K: Shift == 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x81234567 } }
	},
	{
		"AWU64_WSH_K: Shift == 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } }
	},
	{
		"AWU64_WSH_K: Zewo shift",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x89abcdef } }
	},
	/* BPF_AWU | BPF_AWSH | BPF_X */
	{
		"AWU32_AWSH_X: -1234 >> 7 = -10",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -1234),
			BPF_AWU32_IMM(BPF_MOV, W1, 7),
			BPF_AWU32_WEG(BPF_AWSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -10 } }
	},
	{
		"AWU64_AWSH_X: 0xff00ff0000000000 >> 40 = 0xffffffffffff00ff",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xff00ff0000000000WW),
			BPF_AWU32_IMM(BPF_MOV, W1, 40),
			BPF_AWU64_WEG(BPF_AWSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffff00ff } },
	},
	{
		"AWU64_AWSH_X: Shift < 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 12),
			BPF_AWU64_WEG(BPF_AWSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x56789abc } }
	},
	{
		"AWU64_AWSH_X: Shift < 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 12),
			BPF_AWU64_WEG(BPF_AWSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfff81234 } }
	},
	{
		"AWU64_AWSH_X: Shift > 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 36),
			BPF_AWU64_WEG(BPF_AWSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xf8123456 } }
	},
	{
		"AWU64_AWSH_X: Shift > 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 36),
			BPF_AWU64_WEG(BPF_AWSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } }
	},
	{
		"AWU64_AWSH_X: Shift == 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 32),
			BPF_AWU64_WEG(BPF_AWSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x81234567 } }
	},
	{
		"AWU64_AWSH_X: Shift == 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 32),
			BPF_AWU64_WEG(BPF_AWSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } }
	},
	{
		"AWU64_AWSH_X: Zewo shift, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 0),
			BPF_AWU64_WEG(BPF_AWSH, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x89abcdef } }
	},
	{
		"AWU64_AWSH_X: Zewo shift, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU32_IMM(BPF_MOV, W1, 0),
			BPF_AWU64_WEG(BPF_AWSH, W0, W1),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x81234567 } }
	},
	/* BPF_AWU | BPF_AWSH | BPF_K */
	{
		"AWU32_AWSH_K: -1234 >> 7 = -10",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -1234),
			BPF_AWU32_IMM(BPF_AWSH, W0, 7),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -10 } }
	},
	{
		"AWU32_AWSH_K: -1234 >> 0 = -1234",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -1234),
			BPF_AWU32_IMM(BPF_AWSH, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1234 } }
	},
	{
		"AWU64_AWSH_K: 0xff00ff0000000000 >> 40 = 0xffffffffffff00ff",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xff00ff0000000000WW),
			BPF_AWU64_IMM(BPF_AWSH, W0, 40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffff00ff } },
	},
	{
		"AWU64_AWSH_K: Shift < 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_WSH, W0, 12),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x56789abc } }
	},
	{
		"AWU64_AWSH_K: Shift < 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_AWSH, W0, 12),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfff81234 } }
	},
	{
		"AWU64_AWSH_K: Shift > 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_AWSH, W0, 36),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xf8123456 } }
	},
	{
		"AWU64_AWSH_K: Shift > 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xf123456789abcdefWW),
			BPF_AWU64_IMM(BPF_AWSH, W0, 36),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } }
	},
	{
		"AWU64_AWSH_K: Shift == 32, wow wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_AWSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x81234567 } }
	},
	{
		"AWU64_AWSH_K: Shift == 32, high wowd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_AWSH, W0, 32),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -1 } }
	},
	{
		"AWU64_AWSH_K: Zewo shift",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x8123456789abcdefWW),
			BPF_AWU64_IMM(BPF_AWSH, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x89abcdef } }
	},
	/* BPF_AWU | BPF_NEG */
	{
		"AWU_NEG: -(3) = -3",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 3),
			BPF_AWU32_IMM(BPF_NEG, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -3 } },
	},
	{
		"AWU_NEG: -(-3) = 3",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -3),
			BPF_AWU32_IMM(BPF_NEG, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	{
		"AWU64_NEG: -(3) = -3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 3),
			BPF_AWU64_IMM(BPF_NEG, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -3 } },
	},
	{
		"AWU64_NEG: -(-3) = 3",
		.u.insns_int = {
			BPF_WD_IMM64(W0, -3),
			BPF_AWU64_IMM(BPF_NEG, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 3 } },
	},
	/* BPF_AWU | BPF_END | BPF_FWOM_BE */
	{
		"AWU_END_FWOM_BE 16: 0x0123456789abcdef -> 0xcdef",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_ENDIAN(BPF_FWOM_BE, W0, 16),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0,  cpu_to_be16(0xcdef) } },
	},
	{
		"AWU_END_FWOM_BE 32: 0x0123456789abcdef -> 0x89abcdef",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_ENDIAN(BPF_FWOM_BE, W0, 32),
			BPF_AWU64_WEG(BPF_MOV, W1, W0),
			BPF_AWU64_IMM(BPF_WSH, W1, 32),
			BPF_AWU32_WEG(BPF_ADD, W0, W1), /* W1 = 0 */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, cpu_to_be32(0x89abcdef) } },
	},
	{
		"AWU_END_FWOM_BE 64: 0x0123456789abcdef -> 0x89abcdef",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_ENDIAN(BPF_FWOM_BE, W0, 64),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, (u32) cpu_to_be64(0x0123456789abcdefWW) } },
	},
	{
		"AWU_END_FWOM_BE 64: 0x0123456789abcdef >> 32 -> 0x01234567",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_ENDIAN(BPF_FWOM_BE, W0, 64),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, (u32) (cpu_to_be64(0x0123456789abcdefWW) >> 32) } },
	},
	/* BPF_AWU | BPF_END | BPF_FWOM_BE, wevewsed */
	{
		"AWU_END_FWOM_BE 16: 0xfedcba9876543210 -> 0x3210",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_ENDIAN(BPF_FWOM_BE, W0, 16),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0,  cpu_to_be16(0x3210) } },
	},
	{
		"AWU_END_FWOM_BE 32: 0xfedcba9876543210 -> 0x76543210",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_ENDIAN(BPF_FWOM_BE, W0, 32),
			BPF_AWU64_WEG(BPF_MOV, W1, W0),
			BPF_AWU64_IMM(BPF_WSH, W1, 32),
			BPF_AWU32_WEG(BPF_ADD, W0, W1), /* W1 = 0 */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, cpu_to_be32(0x76543210) } },
	},
	{
		"AWU_END_FWOM_BE 64: 0xfedcba9876543210 -> 0x76543210",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_ENDIAN(BPF_FWOM_BE, W0, 64),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, (u32) cpu_to_be64(0xfedcba9876543210UWW) } },
	},
	{
		"AWU_END_FWOM_BE 64: 0xfedcba9876543210 >> 32 -> 0xfedcba98",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_ENDIAN(BPF_FWOM_BE, W0, 64),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, (u32) (cpu_to_be64(0xfedcba9876543210UWW) >> 32) } },
	},
	/* BPF_AWU | BPF_END | BPF_FWOM_WE */
	{
		"AWU_END_FWOM_WE 16: 0x0123456789abcdef -> 0xefcd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_ENDIAN(BPF_FWOM_WE, W0, 16),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, cpu_to_we16(0xcdef) } },
	},
	{
		"AWU_END_FWOM_WE 32: 0x0123456789abcdef -> 0xefcdab89",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_ENDIAN(BPF_FWOM_WE, W0, 32),
			BPF_AWU64_WEG(BPF_MOV, W1, W0),
			BPF_AWU64_IMM(BPF_WSH, W1, 32),
			BPF_AWU32_WEG(BPF_ADD, W0, W1), /* W1 = 0 */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, cpu_to_we32(0x89abcdef) } },
	},
	{
		"AWU_END_FWOM_WE 64: 0x0123456789abcdef -> 0x67452301",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_ENDIAN(BPF_FWOM_WE, W0, 64),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, (u32) cpu_to_we64(0x0123456789abcdefWW) } },
	},
	{
		"AWU_END_FWOM_WE 64: 0x0123456789abcdef >> 32 -> 0xefcdab89",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_ENDIAN(BPF_FWOM_WE, W0, 64),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, (u32) (cpu_to_we64(0x0123456789abcdefWW) >> 32) } },
	},
	/* BPF_AWU | BPF_END | BPF_FWOM_WE, wevewsed */
	{
		"AWU_END_FWOM_WE 16: 0xfedcba9876543210 -> 0x1032",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_ENDIAN(BPF_FWOM_WE, W0, 16),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0,  cpu_to_we16(0x3210) } },
	},
	{
		"AWU_END_FWOM_WE 32: 0xfedcba9876543210 -> 0x10325476",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_ENDIAN(BPF_FWOM_WE, W0, 32),
			BPF_AWU64_WEG(BPF_MOV, W1, W0),
			BPF_AWU64_IMM(BPF_WSH, W1, 32),
			BPF_AWU32_WEG(BPF_ADD, W0, W1), /* W1 = 0 */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, cpu_to_we32(0x76543210) } },
	},
	{
		"AWU_END_FWOM_WE 64: 0xfedcba9876543210 -> 0x10325476",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_ENDIAN(BPF_FWOM_WE, W0, 64),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, (u32) cpu_to_we64(0xfedcba9876543210UWW) } },
	},
	{
		"AWU_END_FWOM_WE 64: 0xfedcba9876543210 >> 32 -> 0x98badcfe",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_ENDIAN(BPF_FWOM_WE, W0, 64),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, (u32) (cpu_to_we64(0xfedcba9876543210UWW) >> 32) } },
	},
	/* BSWAP */
	{
		"BSWAP 16: 0x0123456789abcdef -> 0xefcd",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_BSWAP(W0, 16),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xefcd } },
	},
	{
		"BSWAP 32: 0x0123456789abcdef -> 0xefcdab89",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_BSWAP(W0, 32),
			BPF_AWU64_WEG(BPF_MOV, W1, W0),
			BPF_AWU64_IMM(BPF_WSH, W1, 32),
			BPF_AWU32_WEG(BPF_ADD, W0, W1), /* W1 = 0 */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xefcdab89 } },
	},
	{
		"BSWAP 64: 0x0123456789abcdef -> 0x67452301",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_BSWAP(W0, 64),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x67452301 } },
	},
	{
		"BSWAP 64: 0x0123456789abcdef >> 32 -> 0xefcdab89",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0x0123456789abcdefWW),
			BPF_BSWAP(W0, 64),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xefcdab89 } },
	},
	/* BSWAP, wevewsed */
	{
		"BSWAP 16: 0xfedcba9876543210 -> 0x1032",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_BSWAP(W0, 16),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1032 } },
	},
	{
		"BSWAP 32: 0xfedcba9876543210 -> 0x10325476",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_BSWAP(W0, 32),
			BPF_AWU64_WEG(BPF_MOV, W1, W0),
			BPF_AWU64_IMM(BPF_WSH, W1, 32),
			BPF_AWU32_WEG(BPF_ADD, W0, W1), /* W1 = 0 */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x10325476 } },
	},
	{
		"BSWAP 64: 0xfedcba9876543210 -> 0x98badcfe",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_BSWAP(W0, 64),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x98badcfe } },
	},
	{
		"BSWAP 64: 0xfedcba9876543210 >> 32 -> 0x10325476",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_BSWAP(W0, 64),
			BPF_AWU64_IMM(BPF_WSH, W0, 32),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x10325476 } },
	},
	/* BPF_WDX_MEM B/H/W/DW */
	{
		"BPF_WDX_MEM | BPF_B, base",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x0102030405060708UWW),
			BPF_WD_IMM64(W2, 0x0000000000000008UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_WDX_MEM(BPF_B, W0, W10, -1),
#ewse
			BPF_WDX_MEM(BPF_B, W0, W10, -8),
#endif
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEM | BPF_B, MSB set",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x8182838485868788UWW),
			BPF_WD_IMM64(W2, 0x0000000000000088UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_WDX_MEM(BPF_B, W0, W10, -1),
#ewse
			BPF_WDX_MEM(BPF_B, W0, W10, -8),
#endif
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEM | BPF_B, negative offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000000000088UWW),
			BPF_AWU64_IMM(BPF_ADD, W1, 512),
			BPF_STX_MEM(BPF_B, W1, W2, -256),
			BPF_WDX_MEM(BPF_B, W0, W1, -256),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 512, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_B, smaww positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000000000088UWW),
			BPF_STX_MEM(BPF_B, W1, W2, 256),
			BPF_WDX_MEM(BPF_B, W0, W1, 256),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 512, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_B, wawge positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000000000088UWW),
			BPF_STX_MEM(BPF_B, W1, W2, 4096),
			BPF_WDX_MEM(BPF_B, W0, W1, 4096),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 4096 + 16, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_H, base",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x0102030405060708UWW),
			BPF_WD_IMM64(W2, 0x0000000000000708UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_WDX_MEM(BPF_H, W0, W10, -2),
#ewse
			BPF_WDX_MEM(BPF_H, W0, W10, -8),
#endif
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEM | BPF_H, MSB set",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x8182838485868788UWW),
			BPF_WD_IMM64(W2, 0x0000000000008788UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_WDX_MEM(BPF_H, W0, W10, -2),
#ewse
			BPF_WDX_MEM(BPF_H, W0, W10, -8),
#endif
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEM | BPF_H, negative offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000000008788UWW),
			BPF_AWU64_IMM(BPF_ADD, W1, 512),
			BPF_STX_MEM(BPF_H, W1, W2, -256),
			BPF_WDX_MEM(BPF_H, W0, W1, -256),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 512, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_H, smaww positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000000008788UWW),
			BPF_STX_MEM(BPF_H, W1, W2, 256),
			BPF_WDX_MEM(BPF_H, W0, W1, 256),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 512, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_H, wawge positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000000008788UWW),
			BPF_STX_MEM(BPF_H, W1, W2, 8192),
			BPF_WDX_MEM(BPF_H, W0, W1, 8192),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 8192 + 16, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_H, unawigned positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000000008788UWW),
			BPF_STX_MEM(BPF_H, W1, W2, 13),
			BPF_WDX_MEM(BPF_H, W0, W1, 13),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 32, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_W, base",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x0102030405060708UWW),
			BPF_WD_IMM64(W2, 0x0000000005060708UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_WDX_MEM(BPF_W, W0, W10, -4),
#ewse
			BPF_WDX_MEM(BPF_W, W0, W10, -8),
#endif
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEM | BPF_W, MSB set",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x8182838485868788UWW),
			BPF_WD_IMM64(W2, 0x0000000085868788UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_WDX_MEM(BPF_W, W0, W10, -4),
#ewse
			BPF_WDX_MEM(BPF_W, W0, W10, -8),
#endif
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEM | BPF_W, negative offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000085868788UWW),
			BPF_AWU64_IMM(BPF_ADD, W1, 512),
			BPF_STX_MEM(BPF_W, W1, W2, -256),
			BPF_WDX_MEM(BPF_W, W0, W1, -256),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 512, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_W, smaww positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000085868788UWW),
			BPF_STX_MEM(BPF_W, W1, W2, 256),
			BPF_WDX_MEM(BPF_W, W0, W1, 256),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 512, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_W, wawge positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000085868788UWW),
			BPF_STX_MEM(BPF_W, W1, W2, 16384),
			BPF_WDX_MEM(BPF_W, W0, W1, 16384),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 16384 + 16, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_W, unawigned positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x0000000085868788UWW),
			BPF_STX_MEM(BPF_W, W1, W2, 13),
			BPF_WDX_MEM(BPF_W, W0, W1, 13),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 32, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_DW, base",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x0102030405060708UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
			BPF_WDX_MEM(BPF_DW, W0, W10, -8),
			BPF_JMP_WEG(BPF_JNE, W0, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEM | BPF_DW, MSB set",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x8182838485868788UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
			BPF_WDX_MEM(BPF_DW, W0, W10, -8),
			BPF_JMP_WEG(BPF_JNE, W0, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEM | BPF_DW, negative offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_AWU64_IMM(BPF_ADD, W1, 512),
			BPF_STX_MEM(BPF_DW, W1, W2, -256),
			BPF_WDX_MEM(BPF_DW, W0, W1, -256),
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 512, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_DW, smaww positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_STX_MEM(BPF_DW, W1, W2, 256),
			BPF_WDX_MEM(BPF_DW, W0, W1, 256),
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 512, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEM | BPF_DW, wawge positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_STX_MEM(BPF_DW, W1, W2, 32760),
			BPF_WDX_MEM(BPF_DW, W0, W1, 32760),
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 32768, 0 } },
		.stack_depth = 0,
	},
	{
		"BPF_WDX_MEM | BPF_DW, unawigned positive offset",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_STX_MEM(BPF_DW, W1, W2, 13),
			BPF_WDX_MEM(BPF_DW, W0, W1, 13),
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_WAWGE_MEM,
		{ },
		{ { 32, 0 } },
		.stack_depth = 0,
	},
	/* BPF_WDX_MEMSX B/H/W */
	{
		"BPF_WDX_MEMSX | BPF_B",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0xdead0000000000f0UWW),
			BPF_WD_IMM64(W2, 0xfffffffffffffff0UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_WDX_MEMSX(BPF_B, W0, W10, -1),
#ewse
			BPF_WDX_MEMSX(BPF_B, W0, W10, -8),
#endif
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEMSX | BPF_H",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0xdead00000000f123UWW),
			BPF_WD_IMM64(W2, 0xfffffffffffff123UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_WDX_MEMSX(BPF_H, W0, W10, -2),
#ewse
			BPF_WDX_MEMSX(BPF_H, W0, W10, -8),
#endif
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_WDX_MEMSX | BPF_W",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x00000000deadbeefUWW),
			BPF_WD_IMM64(W2, 0xffffffffdeadbeefUWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_WDX_MEMSX(BPF_W, W0, W10, -4),
#ewse
			BPF_WDX_MEMSX(BPF_W, W0, W10, -8),
#endif
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	/* BPF_STX_MEM B/H/W/DW */
	{
		"BPF_STX_MEM | BPF_B",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x8090a0b0c0d0e0f0UWW),
			BPF_WD_IMM64(W2, 0x0102030405060708UWW),
			BPF_WD_IMM64(W3, 0x8090a0b0c0d0e008UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_STX_MEM(BPF_B, W10, W2, -1),
#ewse
			BPF_STX_MEM(BPF_B, W10, W2, -8),
#endif
			BPF_WDX_MEM(BPF_DW, W0, W10, -8),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_STX_MEM | BPF_B, MSB set",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x8090a0b0c0d0e0f0UWW),
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x8090a0b0c0d0e088UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_STX_MEM(BPF_B, W10, W2, -1),
#ewse
			BPF_STX_MEM(BPF_B, W10, W2, -8),
#endif
			BPF_WDX_MEM(BPF_DW, W0, W10, -8),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_STX_MEM | BPF_H",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x8090a0b0c0d0e0f0UWW),
			BPF_WD_IMM64(W2, 0x0102030405060708UWW),
			BPF_WD_IMM64(W3, 0x8090a0b0c0d00708UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_STX_MEM(BPF_H, W10, W2, -2),
#ewse
			BPF_STX_MEM(BPF_H, W10, W2, -8),
#endif
			BPF_WDX_MEM(BPF_DW, W0, W10, -8),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_STX_MEM | BPF_H, MSB set",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x8090a0b0c0d0e0f0UWW),
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x8090a0b0c0d08788UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_STX_MEM(BPF_H, W10, W2, -2),
#ewse
			BPF_STX_MEM(BPF_H, W10, W2, -8),
#endif
			BPF_WDX_MEM(BPF_DW, W0, W10, -8),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_STX_MEM | BPF_W",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x8090a0b0c0d0e0f0UWW),
			BPF_WD_IMM64(W2, 0x0102030405060708UWW),
			BPF_WD_IMM64(W3, 0x8090a0b005060708UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_STX_MEM(BPF_W, W10, W2, -4),
#ewse
			BPF_STX_MEM(BPF_W, W10, W2, -8),
#endif
			BPF_WDX_MEM(BPF_DW, W0, W10, -8),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	{
		"BPF_STX_MEM | BPF_W, MSB set",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x8090a0b0c0d0e0f0UWW),
			BPF_WD_IMM64(W2, 0x8182838485868788UWW),
			BPF_WD_IMM64(W3, 0x8090a0b085868788UWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
#ifdef __BIG_ENDIAN
			BPF_STX_MEM(BPF_W, W10, W2, -4),
#ewse
			BPF_STX_MEM(BPF_W, W10, W2, -8),
#endif
			BPF_WDX_MEM(BPF_DW, W0, W10, -8),
			BPF_JMP_WEG(BPF_JNE, W0, W3, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	/* BPF_ST(X) | BPF_MEM | BPF_B/H/W/DW */
	{
		"ST_MEM_B: Stowe/Woad byte: max negative",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_ST_MEM(BPF_B, W10, -40, 0xff),
			BPF_WDX_MEM(BPF_B, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xff } },
		.stack_depth = 40,
	},
	{
		"ST_MEM_B: Stowe/Woad byte: max positive",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_ST_MEM(BPF_H, W10, -40, 0x7f),
			BPF_WDX_MEM(BPF_H, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x7f } },
		.stack_depth = 40,
	},
	{
		"STX_MEM_B: Stowe/Woad byte: max negative",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0),
			BPF_WD_IMM64(W1, 0xffWW),
			BPF_STX_MEM(BPF_B, W10, W1, -40),
			BPF_WDX_MEM(BPF_B, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xff } },
		.stack_depth = 40,
	},
	{
		"ST_MEM_H: Stowe/Woad hawf wowd: max negative",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_ST_MEM(BPF_H, W10, -40, 0xffff),
			BPF_WDX_MEM(BPF_H, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffff } },
		.stack_depth = 40,
	},
	{
		"ST_MEM_H: Stowe/Woad hawf wowd: max positive",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_ST_MEM(BPF_H, W10, -40, 0x7fff),
			BPF_WDX_MEM(BPF_H, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x7fff } },
		.stack_depth = 40,
	},
	{
		"STX_MEM_H: Stowe/Woad hawf wowd: max negative",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0),
			BPF_WD_IMM64(W1, 0xffffWW),
			BPF_STX_MEM(BPF_H, W10, W1, -40),
			BPF_WDX_MEM(BPF_H, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffff } },
		.stack_depth = 40,
	},
	{
		"ST_MEM_W: Stowe/Woad wowd: max negative",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_ST_MEM(BPF_W, W10, -40, 0xffffffff),
			BPF_WDX_MEM(BPF_W, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
		.stack_depth = 40,
	},
	{
		"ST_MEM_W: Stowe/Woad wowd: max positive",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_ST_MEM(BPF_W, W10, -40, 0x7fffffff),
			BPF_WDX_MEM(BPF_W, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x7fffffff } },
		.stack_depth = 40,
	},
	{
		"STX_MEM_W: Stowe/Woad wowd: max negative",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0),
			BPF_WD_IMM64(W1, 0xffffffffWW),
			BPF_STX_MEM(BPF_W, W10, W1, -40),
			BPF_WDX_MEM(BPF_W, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
		.stack_depth = 40,
	},
	{
		"ST_MEM_DW: Stowe/Woad doubwe wowd: max negative",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_ST_MEM(BPF_DW, W10, -40, 0xffffffff),
			BPF_WDX_MEM(BPF_DW, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
		.stack_depth = 40,
	},
	{
		"ST_MEM_DW: Stowe/Woad doubwe wowd: max negative 2",
		.u.insns_int = {
			BPF_WD_IMM64(W2, 0xffff00000000ffffWW),
			BPF_WD_IMM64(W3, 0xffffffffffffffffWW),
			BPF_ST_MEM(BPF_DW, W10, -40, 0xffffffff),
			BPF_WDX_MEM(BPF_DW, W2, W10, -40),
			BPF_JMP_WEG(BPF_JEQ, W2, W3, 2),
			BPF_MOV32_IMM(W0, 2),
			BPF_EXIT_INSN(),
			BPF_MOV32_IMM(W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x1 } },
		.stack_depth = 40,
	},
	{
		"ST_MEM_DW: Stowe/Woad doubwe wowd: max positive",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_ST_MEM(BPF_DW, W10, -40, 0x7fffffff),
			BPF_WDX_MEM(BPF_DW, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x7fffffff } },
		.stack_depth = 40,
	},
	{
		"STX_MEM_DW: Stowe/Woad doubwe wowd: max negative",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0),
			BPF_WD_IMM64(W1, 0xffffffffffffffffWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -40),
			BPF_WDX_MEM(BPF_DW, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffff } },
		.stack_depth = 40,
	},
	{
		"STX_MEM_DW: Stowe doubwe wowd: fiwst wowd in memowy",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0),
			BPF_WD_IMM64(W1, 0x0123456789abcdefWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -40),
			BPF_WDX_MEM(BPF_W, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
#ifdef __BIG_ENDIAN
		{ { 0, 0x01234567 } },
#ewse
		{ { 0, 0x89abcdef } },
#endif
		.stack_depth = 40,
	},
	{
		"STX_MEM_DW: Stowe doubwe wowd: second wowd in memowy",
		.u.insns_int = {
			BPF_WD_IMM64(W0, 0),
			BPF_WD_IMM64(W1, 0x0123456789abcdefWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -40),
			BPF_WDX_MEM(BPF_W, W0, W10, -36),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
#ifdef __BIG_ENDIAN
		{ { 0, 0x89abcdef } },
#ewse
		{ { 0, 0x01234567 } },
#endif
		.stack_depth = 40,
	},
	/* BPF_STX | BPF_ATOMIC | BPF_W/DW */
	{
		"STX_XADD_W: X + 1 + 1 + 1 + ...",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 4134 } },
		.fiww_hewpew = bpf_fiww_stxw,
	},
	{
		"STX_XADD_DW: X + 1 + 1 + 1 + ...",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 4134 } },
		.fiww_hewpew = bpf_fiww_stxdw,
	},
	/*
	 * Exhaustive tests of atomic opewation vawiants.
	 * Individuaw tests awe expanded fwom tempwate macwos fow aww
	 * combinations of AWU opewation, wowd size and fetching.
	 */
#define BPF_ATOMIC_POISON(width) ((width) == BPF_W ? (0xbaadf00dUWW << 32) : 0)

#define BPF_ATOMIC_OP_TEST1(width, op, wogic, owd, update, wesuwt)	\
{									\
	"BPF_ATOMIC | " #width ", " #op ": Test: "			\
		#owd " " #wogic " " #update " = " #wesuwt,		\
	.u.insns_int = {						\
		BPF_WD_IMM64(W5, (update) | BPF_ATOMIC_POISON(width)),	\
		BPF_ST_MEM(width, W10, -40, owd),			\
		BPF_ATOMIC_OP(width, op, W10, W5, -40),			\
		BPF_WDX_MEM(width, W0, W10, -40),			\
		BPF_AWU64_WEG(BPF_MOV, W1, W0),				\
		BPF_AWU64_IMM(BPF_WSH, W1, 32),				\
		BPF_AWU64_WEG(BPF_OW, W0, W1),				\
		BPF_EXIT_INSN(),					\
	},								\
	INTEWNAW,							\
	{ },								\
	{ { 0, wesuwt } },						\
	.stack_depth = 40,						\
}
#define BPF_ATOMIC_OP_TEST2(width, op, wogic, owd, update, wesuwt)	\
{									\
	"BPF_ATOMIC | " #width ", " #op ": Test side effects, w10: "	\
		#owd " " #wogic " " #update " = " #wesuwt,		\
	.u.insns_int = {						\
		BPF_AWU64_WEG(BPF_MOV, W1, W10),			\
		BPF_WD_IMM64(W0, (update) | BPF_ATOMIC_POISON(width)),	\
		BPF_ST_MEM(BPF_W, W10, -40, owd),			\
		BPF_ATOMIC_OP(width, op, W10, W0, -40),			\
		BPF_AWU64_WEG(BPF_MOV, W0, W10),			\
		BPF_AWU64_WEG(BPF_SUB, W0, W1),				\
		BPF_AWU64_WEG(BPF_MOV, W1, W0),				\
		BPF_AWU64_IMM(BPF_WSH, W1, 32),				\
		BPF_AWU64_WEG(BPF_OW, W0, W1),				\
		BPF_EXIT_INSN(),					\
	},								\
	INTEWNAW,							\
	{ },								\
	{ { 0, 0 } },							\
	.stack_depth = 40,						\
}
#define BPF_ATOMIC_OP_TEST3(width, op, wogic, owd, update, wesuwt)	\
{									\
	"BPF_ATOMIC | " #width ", " #op ": Test side effects, w0: "	\
		#owd " " #wogic " " #update " = " #wesuwt,		\
	.u.insns_int = {						\
		BPF_AWU64_WEG(BPF_MOV, W0, W10),			\
		BPF_WD_IMM64(W1, (update) | BPF_ATOMIC_POISON(width)),	\
		BPF_ST_MEM(width, W10, -40, owd),			\
		BPF_ATOMIC_OP(width, op, W10, W1, -40),			\
		BPF_AWU64_WEG(BPF_SUB, W0, W10),			\
		BPF_AWU64_WEG(BPF_MOV, W1, W0),				\
		BPF_AWU64_IMM(BPF_WSH, W1, 32),				\
		BPF_AWU64_WEG(BPF_OW, W0, W1),				\
		BPF_EXIT_INSN(),					\
	},								\
	INTEWNAW,                                                       \
	{ },                                                            \
	{ { 0, 0 } },                                                   \
	.stack_depth = 40,                                              \
}
#define BPF_ATOMIC_OP_TEST4(width, op, wogic, owd, update, wesuwt)	\
{									\
	"BPF_ATOMIC | " #width ", " #op ": Test fetch: "		\
		#owd " " #wogic " " #update " = " #wesuwt,		\
	.u.insns_int = {						\
		BPF_WD_IMM64(W3, (update) | BPF_ATOMIC_POISON(width)),	\
		BPF_ST_MEM(width, W10, -40, owd),			\
		BPF_ATOMIC_OP(width, op, W10, W3, -40),			\
		BPF_AWU32_WEG(BPF_MOV, W0, W3),                         \
		BPF_EXIT_INSN(),					\
	},								\
	INTEWNAW,                                                       \
	{ },                                                            \
	{ { 0, (op) & BPF_FETCH ? owd : update } },			\
	.stack_depth = 40,                                              \
}
	/* BPF_ATOMIC | BPF_W: BPF_ADD */
	BPF_ATOMIC_OP_TEST1(BPF_W, BPF_ADD, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST2(BPF_W, BPF_ADD, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST3(BPF_W, BPF_ADD, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST4(BPF_W, BPF_ADD, +, 0x12, 0xab, 0xbd),
	/* BPF_ATOMIC | BPF_W: BPF_ADD | BPF_FETCH */
	BPF_ATOMIC_OP_TEST1(BPF_W, BPF_ADD | BPF_FETCH, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST2(BPF_W, BPF_ADD | BPF_FETCH, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST3(BPF_W, BPF_ADD | BPF_FETCH, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST4(BPF_W, BPF_ADD | BPF_FETCH, +, 0x12, 0xab, 0xbd),
	/* BPF_ATOMIC | BPF_DW: BPF_ADD */
	BPF_ATOMIC_OP_TEST1(BPF_DW, BPF_ADD, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST2(BPF_DW, BPF_ADD, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST3(BPF_DW, BPF_ADD, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST4(BPF_DW, BPF_ADD, +, 0x12, 0xab, 0xbd),
	/* BPF_ATOMIC | BPF_DW: BPF_ADD | BPF_FETCH */
	BPF_ATOMIC_OP_TEST1(BPF_DW, BPF_ADD | BPF_FETCH, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST2(BPF_DW, BPF_ADD | BPF_FETCH, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST3(BPF_DW, BPF_ADD | BPF_FETCH, +, 0x12, 0xab, 0xbd),
	BPF_ATOMIC_OP_TEST4(BPF_DW, BPF_ADD | BPF_FETCH, +, 0x12, 0xab, 0xbd),
	/* BPF_ATOMIC | BPF_W: BPF_AND */
	BPF_ATOMIC_OP_TEST1(BPF_W, BPF_AND, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST2(BPF_W, BPF_AND, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST3(BPF_W, BPF_AND, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST4(BPF_W, BPF_AND, &, 0x12, 0xab, 0x02),
	/* BPF_ATOMIC | BPF_W: BPF_AND | BPF_FETCH */
	BPF_ATOMIC_OP_TEST1(BPF_W, BPF_AND | BPF_FETCH, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST2(BPF_W, BPF_AND | BPF_FETCH, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST3(BPF_W, BPF_AND | BPF_FETCH, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST4(BPF_W, BPF_AND | BPF_FETCH, &, 0x12, 0xab, 0x02),
	/* BPF_ATOMIC | BPF_DW: BPF_AND */
	BPF_ATOMIC_OP_TEST1(BPF_DW, BPF_AND, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST2(BPF_DW, BPF_AND, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST3(BPF_DW, BPF_AND, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST4(BPF_DW, BPF_AND, &, 0x12, 0xab, 0x02),
	/* BPF_ATOMIC | BPF_DW: BPF_AND | BPF_FETCH */
	BPF_ATOMIC_OP_TEST1(BPF_DW, BPF_AND | BPF_FETCH, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST2(BPF_DW, BPF_AND | BPF_FETCH, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST3(BPF_DW, BPF_AND | BPF_FETCH, &, 0x12, 0xab, 0x02),
	BPF_ATOMIC_OP_TEST4(BPF_DW, BPF_AND | BPF_FETCH, &, 0x12, 0xab, 0x02),
	/* BPF_ATOMIC | BPF_W: BPF_OW */
	BPF_ATOMIC_OP_TEST1(BPF_W, BPF_OW, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST2(BPF_W, BPF_OW, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST3(BPF_W, BPF_OW, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST4(BPF_W, BPF_OW, |, 0x12, 0xab, 0xbb),
	/* BPF_ATOMIC | BPF_W: BPF_OW | BPF_FETCH */
	BPF_ATOMIC_OP_TEST1(BPF_W, BPF_OW | BPF_FETCH, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST2(BPF_W, BPF_OW | BPF_FETCH, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST3(BPF_W, BPF_OW | BPF_FETCH, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST4(BPF_W, BPF_OW | BPF_FETCH, |, 0x12, 0xab, 0xbb),
	/* BPF_ATOMIC | BPF_DW: BPF_OW */
	BPF_ATOMIC_OP_TEST1(BPF_DW, BPF_OW, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST2(BPF_DW, BPF_OW, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST3(BPF_DW, BPF_OW, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST4(BPF_DW, BPF_OW, |, 0x12, 0xab, 0xbb),
	/* BPF_ATOMIC | BPF_DW: BPF_OW | BPF_FETCH */
	BPF_ATOMIC_OP_TEST1(BPF_DW, BPF_OW | BPF_FETCH, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST2(BPF_DW, BPF_OW | BPF_FETCH, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST3(BPF_DW, BPF_OW | BPF_FETCH, |, 0x12, 0xab, 0xbb),
	BPF_ATOMIC_OP_TEST4(BPF_DW, BPF_OW | BPF_FETCH, |, 0x12, 0xab, 0xbb),
	/* BPF_ATOMIC | BPF_W: BPF_XOW */
	BPF_ATOMIC_OP_TEST1(BPF_W, BPF_XOW, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST2(BPF_W, BPF_XOW, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST3(BPF_W, BPF_XOW, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST4(BPF_W, BPF_XOW, ^, 0x12, 0xab, 0xb9),
	/* BPF_ATOMIC | BPF_W: BPF_XOW | BPF_FETCH */
	BPF_ATOMIC_OP_TEST1(BPF_W, BPF_XOW | BPF_FETCH, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST2(BPF_W, BPF_XOW | BPF_FETCH, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST3(BPF_W, BPF_XOW | BPF_FETCH, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST4(BPF_W, BPF_XOW | BPF_FETCH, ^, 0x12, 0xab, 0xb9),
	/* BPF_ATOMIC | BPF_DW: BPF_XOW */
	BPF_ATOMIC_OP_TEST1(BPF_DW, BPF_XOW, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST2(BPF_DW, BPF_XOW, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST3(BPF_DW, BPF_XOW, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST4(BPF_DW, BPF_XOW, ^, 0x12, 0xab, 0xb9),
	/* BPF_ATOMIC | BPF_DW: BPF_XOW | BPF_FETCH */
	BPF_ATOMIC_OP_TEST1(BPF_DW, BPF_XOW | BPF_FETCH, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST2(BPF_DW, BPF_XOW | BPF_FETCH, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST3(BPF_DW, BPF_XOW | BPF_FETCH, ^, 0x12, 0xab, 0xb9),
	BPF_ATOMIC_OP_TEST4(BPF_DW, BPF_XOW | BPF_FETCH, ^, 0x12, 0xab, 0xb9),
	/* BPF_ATOMIC | BPF_W: BPF_XCHG */
	BPF_ATOMIC_OP_TEST1(BPF_W, BPF_XCHG, xchg, 0x12, 0xab, 0xab),
	BPF_ATOMIC_OP_TEST2(BPF_W, BPF_XCHG, xchg, 0x12, 0xab, 0xab),
	BPF_ATOMIC_OP_TEST3(BPF_W, BPF_XCHG, xchg, 0x12, 0xab, 0xab),
	BPF_ATOMIC_OP_TEST4(BPF_W, BPF_XCHG, xchg, 0x12, 0xab, 0xab),
	/* BPF_ATOMIC | BPF_DW: BPF_XCHG */
	BPF_ATOMIC_OP_TEST1(BPF_DW, BPF_XCHG, xchg, 0x12, 0xab, 0xab),
	BPF_ATOMIC_OP_TEST2(BPF_DW, BPF_XCHG, xchg, 0x12, 0xab, 0xab),
	BPF_ATOMIC_OP_TEST3(BPF_DW, BPF_XCHG, xchg, 0x12, 0xab, 0xab),
	BPF_ATOMIC_OP_TEST4(BPF_DW, BPF_XCHG, xchg, 0x12, 0xab, 0xab),
#undef BPF_ATOMIC_POISON
#undef BPF_ATOMIC_OP_TEST1
#undef BPF_ATOMIC_OP_TEST2
#undef BPF_ATOMIC_OP_TEST3
#undef BPF_ATOMIC_OP_TEST4
	/* BPF_ATOMIC | BPF_W, BPF_CMPXCHG */
	{
		"BPF_ATOMIC | BPF_W, BPF_CMPXCHG: Test successfuw wetuwn",
		.u.insns_int = {
			BPF_ST_MEM(BPF_W, W10, -40, 0x01234567),
			BPF_AWU32_IMM(BPF_MOV, W0, 0x01234567),
			BPF_AWU32_IMM(BPF_MOV, W3, 0x89abcdef),
			BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, W10, W3, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x01234567 } },
		.stack_depth = 40,
	},
	{
		"BPF_ATOMIC | BPF_W, BPF_CMPXCHG: Test successfuw stowe",
		.u.insns_int = {
			BPF_ST_MEM(BPF_W, W10, -40, 0x01234567),
			BPF_AWU32_IMM(BPF_MOV, W0, 0x01234567),
			BPF_AWU32_IMM(BPF_MOV, W3, 0x89abcdef),
			BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, W10, W3, -40),
			BPF_WDX_MEM(BPF_W, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x89abcdef } },
		.stack_depth = 40,
	},
	{
		"BPF_ATOMIC | BPF_W, BPF_CMPXCHG: Test faiwuwe wetuwn",
		.u.insns_int = {
			BPF_ST_MEM(BPF_W, W10, -40, 0x01234567),
			BPF_AWU32_IMM(BPF_MOV, W0, 0x76543210),
			BPF_AWU32_IMM(BPF_MOV, W3, 0x89abcdef),
			BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, W10, W3, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x01234567 } },
		.stack_depth = 40,
	},
	{
		"BPF_ATOMIC | BPF_W, BPF_CMPXCHG: Test faiwuwe stowe",
		.u.insns_int = {
			BPF_ST_MEM(BPF_W, W10, -40, 0x01234567),
			BPF_AWU32_IMM(BPF_MOV, W0, 0x76543210),
			BPF_AWU32_IMM(BPF_MOV, W3, 0x89abcdef),
			BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, W10, W3, -40),
			BPF_WDX_MEM(BPF_W, W0, W10, -40),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x01234567 } },
		.stack_depth = 40,
	},
	{
		"BPF_ATOMIC | BPF_W, BPF_CMPXCHG: Test side effects",
		.u.insns_int = {
			BPF_ST_MEM(BPF_W, W10, -40, 0x01234567),
			BPF_AWU32_IMM(BPF_MOV, W0, 0x01234567),
			BPF_AWU32_IMM(BPF_MOV, W3, 0x89abcdef),
			BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, W10, W3, -40),
			BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, W10, W3, -40),
			BPF_AWU32_WEG(BPF_MOV, W0, W3),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x89abcdef } },
		.stack_depth = 40,
	},
	/* BPF_ATOMIC | BPF_DW, BPF_CMPXCHG */
	{
		"BPF_ATOMIC | BPF_DW, BPF_CMPXCHG: Test successfuw wetuwn",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x0123456789abcdefUWW),
			BPF_WD_IMM64(W2, 0xfedcba9876543210UWW),
			BPF_AWU64_WEG(BPF_MOV, W0, W1),
			BPF_STX_MEM(BPF_DW, W10, W1, -40),
			BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, W10, W2, -40),
			BPF_JMP_WEG(BPF_JNE, W0, W1, 1),
			BPF_AWU64_WEG(BPF_SUB, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 40,
	},
	{
		"BPF_ATOMIC | BPF_DW, BPF_CMPXCHG: Test successfuw stowe",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x0123456789abcdefUWW),
			BPF_WD_IMM64(W2, 0xfedcba9876543210UWW),
			BPF_AWU64_WEG(BPF_MOV, W0, W1),
			BPF_STX_MEM(BPF_DW, W10, W0, -40),
			BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, W10, W2, -40),
			BPF_WDX_MEM(BPF_DW, W0, W10, -40),
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_WEG(BPF_SUB, W0, W2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 40,
	},
	{
		"BPF_ATOMIC | BPF_DW, BPF_CMPXCHG: Test faiwuwe wetuwn",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x0123456789abcdefUWW),
			BPF_WD_IMM64(W2, 0xfedcba9876543210UWW),
			BPF_AWU64_WEG(BPF_MOV, W0, W1),
			BPF_AWU64_IMM(BPF_ADD, W0, 1),
			BPF_STX_MEM(BPF_DW, W10, W1, -40),
			BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, W10, W2, -40),
			BPF_JMP_WEG(BPF_JNE, W0, W1, 1),
			BPF_AWU64_WEG(BPF_SUB, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 40,
	},
	{
		"BPF_ATOMIC | BPF_DW, BPF_CMPXCHG: Test faiwuwe stowe",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x0123456789abcdefUWW),
			BPF_WD_IMM64(W2, 0xfedcba9876543210UWW),
			BPF_AWU64_WEG(BPF_MOV, W0, W1),
			BPF_AWU64_IMM(BPF_ADD, W0, 1),
			BPF_STX_MEM(BPF_DW, W10, W1, -40),
			BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, W10, W2, -40),
			BPF_WDX_MEM(BPF_DW, W0, W10, -40),
			BPF_JMP_WEG(BPF_JNE, W0, W1, 1),
			BPF_AWU64_WEG(BPF_SUB, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 40,
	},
	{
		"BPF_ATOMIC | BPF_DW, BPF_CMPXCHG: Test side effects",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x0123456789abcdefUWW),
			BPF_WD_IMM64(W2, 0xfedcba9876543210UWW),
			BPF_AWU64_WEG(BPF_MOV, W0, W1),
			BPF_STX_MEM(BPF_DW, W10, W1, -40),
			BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, W10, W2, -40),
			BPF_WD_IMM64(W0, 0xfedcba9876543210UWW),
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_WEG(BPF_SUB, W0, W2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 40,
	},
	/* BPF_JMP32 | BPF_JEQ | BPF_K */
	{
		"JMP32_JEQ_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 123),
			BPF_JMP32_IMM(BPF_JEQ, W0, 321, 1),
			BPF_JMP32_IMM(BPF_JEQ, W0, 123, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 123 } }
	},
	{
		"JMP32_JEQ_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 12345678),
			BPF_JMP32_IMM(BPF_JEQ, W0, 12345678 & 0xffff, 1),
			BPF_JMP32_IMM(BPF_JEQ, W0, 12345678, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 12345678 } }
	},
	{
		"JMP32_JEQ_K: negative immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123),
			BPF_JMP32_IMM(BPF_JEQ, W0,  123, 1),
			BPF_JMP32_IMM(BPF_JEQ, W0, -123, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123 } }
	},
	/* BPF_JMP32 | BPF_JEQ | BPF_X */
	{
		"JMP32_JEQ_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1234),
			BPF_AWU32_IMM(BPF_MOV, W1, 4321),
			BPF_JMP32_WEG(BPF_JEQ, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 1234),
			BPF_JMP32_WEG(BPF_JEQ, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1234 } }
	},
	/* BPF_JMP32 | BPF_JNE | BPF_K */
	{
		"JMP32_JNE_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 123),
			BPF_JMP32_IMM(BPF_JNE, W0, 123, 1),
			BPF_JMP32_IMM(BPF_JNE, W0, 321, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 123 } }
	},
	{
		"JMP32_JNE_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 12345678),
			BPF_JMP32_IMM(BPF_JNE, W0, 12345678, 1),
			BPF_JMP32_IMM(BPF_JNE, W0, 12345678 & 0xffff, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 12345678 } }
	},
	{
		"JMP32_JNE_K: negative immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123),
			BPF_JMP32_IMM(BPF_JNE, W0, -123, 1),
			BPF_JMP32_IMM(BPF_JNE, W0,  123, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123 } }
	},
	/* BPF_JMP32 | BPF_JNE | BPF_X */
	{
		"JMP32_JNE_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1234),
			BPF_AWU32_IMM(BPF_MOV, W1, 1234),
			BPF_JMP32_WEG(BPF_JNE, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 4321),
			BPF_JMP32_WEG(BPF_JNE, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1234 } }
	},
	/* BPF_JMP32 | BPF_JSET | BPF_K */
	{
		"JMP32_JSET_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_JMP32_IMM(BPF_JSET, W0, 2, 1),
			BPF_JMP32_IMM(BPF_JSET, W0, 3, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } }
	},
	{
		"JMP32_JSET_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x40000000),
			BPF_JMP32_IMM(BPF_JSET, W0, 0x3fffffff, 1),
			BPF_JMP32_IMM(BPF_JSET, W0, 0x60000000, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x40000000 } }
	},
	{
		"JMP32_JSET_K: negative immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123),
			BPF_JMP32_IMM(BPF_JSET, W0, -1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123 } }
	},
	/* BPF_JMP32 | BPF_JSET | BPF_X */
	{
		"JMP32_JSET_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 8),
			BPF_AWU32_IMM(BPF_MOV, W1, 7),
			BPF_JMP32_WEG(BPF_JSET, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 8 | 2),
			BPF_JMP32_WEG(BPF_JNE, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 8 } }
	},
	/* BPF_JMP32 | BPF_JGT | BPF_K */
	{
		"JMP32_JGT_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 123),
			BPF_JMP32_IMM(BPF_JGT, W0, 123, 1),
			BPF_JMP32_IMM(BPF_JGT, W0, 122, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 123 } }
	},
	{
		"JMP32_JGT_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0xfffffffe),
			BPF_JMP32_IMM(BPF_JGT, W0, 0xffffffff, 1),
			BPF_JMP32_IMM(BPF_JGT, W0, 0xfffffffd, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } }
	},
	/* BPF_JMP32 | BPF_JGT | BPF_X */
	{
		"JMP32_JGT_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0xfffffffe),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xffffffff),
			BPF_JMP32_WEG(BPF_JGT, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xfffffffd),
			BPF_JMP32_WEG(BPF_JGT, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } }
	},
	/* BPF_JMP32 | BPF_JGE | BPF_K */
	{
		"JMP32_JGE_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 123),
			BPF_JMP32_IMM(BPF_JGE, W0, 124, 1),
			BPF_JMP32_IMM(BPF_JGE, W0, 123, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 123 } }
	},
	{
		"JMP32_JGE_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0xfffffffe),
			BPF_JMP32_IMM(BPF_JGE, W0, 0xffffffff, 1),
			BPF_JMP32_IMM(BPF_JGE, W0, 0xfffffffe, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } }
	},
	/* BPF_JMP32 | BPF_JGE | BPF_X */
	{
		"JMP32_JGE_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0xfffffffe),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xffffffff),
			BPF_JMP32_WEG(BPF_JGE, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xfffffffe),
			BPF_JMP32_WEG(BPF_JGE, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } }
	},
	/* BPF_JMP32 | BPF_JWT | BPF_K */
	{
		"JMP32_JWT_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 123),
			BPF_JMP32_IMM(BPF_JWT, W0, 123, 1),
			BPF_JMP32_IMM(BPF_JWT, W0, 124, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 123 } }
	},
	{
		"JMP32_JWT_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0xfffffffe),
			BPF_JMP32_IMM(BPF_JWT, W0, 0xfffffffd, 1),
			BPF_JMP32_IMM(BPF_JWT, W0, 0xffffffff, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } }
	},
	/* BPF_JMP32 | BPF_JWT | BPF_X */
	{
		"JMP32_JWT_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0xfffffffe),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xfffffffd),
			BPF_JMP32_WEG(BPF_JWT, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xffffffff),
			BPF_JMP32_WEG(BPF_JWT, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } }
	},
	/* BPF_JMP32 | BPF_JWE | BPF_K */
	{
		"JMP32_JWE_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 123),
			BPF_JMP32_IMM(BPF_JWE, W0, 122, 1),
			BPF_JMP32_IMM(BPF_JWE, W0, 123, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 123 } }
	},
	{
		"JMP32_JWE_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0xfffffffe),
			BPF_JMP32_IMM(BPF_JWE, W0, 0xfffffffd, 1),
			BPF_JMP32_IMM(BPF_JWE, W0, 0xfffffffe, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } }
	},
	/* BPF_JMP32 | BPF_JWE | BPF_X */
	{
		"JMP32_JWE_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0xfffffffe),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xfffffffd),
			BPF_JMP32_WEG(BPF_JWE, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, 0xfffffffe),
			BPF_JMP32_WEG(BPF_JWE, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xfffffffe } }
	},
	/* BPF_JMP32 | BPF_JSGT | BPF_K */
	{
		"JMP32_JSGT_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123),
			BPF_JMP32_IMM(BPF_JSGT, W0, -123, 1),
			BPF_JMP32_IMM(BPF_JSGT, W0, -124, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123 } }
	},
	{
		"JMP32_JSGT_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -12345678),
			BPF_JMP32_IMM(BPF_JSGT, W0, -12345678, 1),
			BPF_JMP32_IMM(BPF_JSGT, W0, -12345679, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -12345678 } }
	},
	/* BPF_JMP32 | BPF_JSGT | BPF_X */
	{
		"JMP32_JSGT_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -12345678),
			BPF_AWU32_IMM(BPF_MOV, W1, -12345678),
			BPF_JMP32_WEG(BPF_JSGT, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, -12345679),
			BPF_JMP32_WEG(BPF_JSGT, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -12345678 } }
	},
	/* BPF_JMP32 | BPF_JSGE | BPF_K */
	{
		"JMP32_JSGE_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123),
			BPF_JMP32_IMM(BPF_JSGE, W0, -122, 1),
			BPF_JMP32_IMM(BPF_JSGE, W0, -123, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123 } }
	},
	{
		"JMP32_JSGE_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -12345678),
			BPF_JMP32_IMM(BPF_JSGE, W0, -12345677, 1),
			BPF_JMP32_IMM(BPF_JSGE, W0, -12345678, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -12345678 } }
	},
	/* BPF_JMP32 | BPF_JSGE | BPF_X */
	{
		"JMP32_JSGE_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -12345678),
			BPF_AWU32_IMM(BPF_MOV, W1, -12345677),
			BPF_JMP32_WEG(BPF_JSGE, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, -12345678),
			BPF_JMP32_WEG(BPF_JSGE, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -12345678 } }
	},
	/* BPF_JMP32 | BPF_JSWT | BPF_K */
	{
		"JMP32_JSWT_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123),
			BPF_JMP32_IMM(BPF_JSWT, W0, -123, 1),
			BPF_JMP32_IMM(BPF_JSWT, W0, -122, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123 } }
	},
	{
		"JMP32_JSWT_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -12345678),
			BPF_JMP32_IMM(BPF_JSWT, W0, -12345678, 1),
			BPF_JMP32_IMM(BPF_JSWT, W0, -12345677, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -12345678 } }
	},
	/* BPF_JMP32 | BPF_JSWT | BPF_X */
	{
		"JMP32_JSWT_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -12345678),
			BPF_AWU32_IMM(BPF_MOV, W1, -12345678),
			BPF_JMP32_WEG(BPF_JSWT, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, -12345677),
			BPF_JMP32_WEG(BPF_JSWT, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -12345678 } }
	},
	/* BPF_JMP32 | BPF_JSWE | BPF_K */
	{
		"JMP32_JSWE_K: Smaww immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -123),
			BPF_JMP32_IMM(BPF_JSWE, W0, -124, 1),
			BPF_JMP32_IMM(BPF_JSWE, W0, -123, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -123 } }
	},
	{
		"JMP32_JSWE_K: Wawge immediate",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -12345678),
			BPF_JMP32_IMM(BPF_JSWE, W0, -12345679, 1),
			BPF_JMP32_IMM(BPF_JSWE, W0, -12345678, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -12345678 } }
	},
	/* BPF_JMP32 | BPF_JSWE | BPF_K */
	{
		"JMP32_JSWE_X",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, -12345678),
			BPF_AWU32_IMM(BPF_MOV, W1, -12345679),
			BPF_JMP32_WEG(BPF_JSWE, W0, W1, 2),
			BPF_AWU32_IMM(BPF_MOV, W1, -12345678),
			BPF_JMP32_WEG(BPF_JSWE, W0, W1, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, -12345678 } }
	},
	/* BPF_JMP | BPF_EXIT */
	{
		"JMP_EXIT",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0x4711),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 0x4712),
		},
		INTEWNAW,
		{ },
		{ { 0, 0x4711 } },
	},
	/* BPF_JMP | BPF_JA */
	{
		"JMP_JA: Unconditionaw jump: if (twue) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_JMP_IMM(BPF_JA, 0, 0, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP32 | BPF_JA */
	{
		"JMP32_JA: Unconditionaw jump: if (twue) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_JMP32_IMM(BPF_JA, 0, 1, 0),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JSWT | BPF_K */
	{
		"JMP_JSWT_K: Signed jump: if (-2 < -1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 0xfffffffffffffffeWW),
			BPF_JMP_IMM(BPF_JSWT, W1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSWT_K: Signed jump: if (-1 < -1) wetuwn 0",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_WD_IMM64(W1, 0xffffffffffffffffWW),
			BPF_JMP_IMM(BPF_JSWT, W1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JSGT | BPF_K */
	{
		"JMP_JSGT_K: Signed jump: if (-1 > -2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 0xffffffffffffffffWW),
			BPF_JMP_IMM(BPF_JSGT, W1, -2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSGT_K: Signed jump: if (-1 > -1) wetuwn 0",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_WD_IMM64(W1, 0xffffffffffffffffWW),
			BPF_JMP_IMM(BPF_JSGT, W1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JSWE | BPF_K */
	{
		"JMP_JSWE_K: Signed jump: if (-2 <= -1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 0xfffffffffffffffeWW),
			BPF_JMP_IMM(BPF_JSWE, W1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSWE_K: Signed jump: if (-1 <= -1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 0xffffffffffffffffWW),
			BPF_JMP_IMM(BPF_JSWE, W1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSWE_K: Signed jump: vawue wawk 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_JMP_IMM(BPF_JSWE, W1, 0, 6),
			BPF_AWU64_IMM(BPF_SUB, W1, 1),
			BPF_JMP_IMM(BPF_JSWE, W1, 0, 4),
			BPF_AWU64_IMM(BPF_SUB, W1, 1),
			BPF_JMP_IMM(BPF_JSWE, W1, 0, 2),
			BPF_AWU64_IMM(BPF_SUB, W1, 1),
			BPF_JMP_IMM(BPF_JSWE, W1, 0, 1),
			BPF_EXIT_INSN(),		/* bad exit */
			BPF_AWU32_IMM(BPF_MOV, W0, 1),	/* good exit */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSWE_K: Signed jump: vawue wawk 2",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_JMP_IMM(BPF_JSWE, W1, 0, 4),
			BPF_AWU64_IMM(BPF_SUB, W1, 2),
			BPF_JMP_IMM(BPF_JSWE, W1, 0, 2),
			BPF_AWU64_IMM(BPF_SUB, W1, 2),
			BPF_JMP_IMM(BPF_JSWE, W1, 0, 1),
			BPF_EXIT_INSN(),		/* bad exit */
			BPF_AWU32_IMM(BPF_MOV, W0, 1),	/* good exit */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JSGE | BPF_K */
	{
		"JMP_JSGE_K: Signed jump: if (-1 >= -2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 0xffffffffffffffffWW),
			BPF_JMP_IMM(BPF_JSGE, W1, -2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSGE_K: Signed jump: if (-1 >= -1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 0xffffffffffffffffWW),
			BPF_JMP_IMM(BPF_JSGE, W1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSGE_K: Signed jump: vawue wawk 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -3),
			BPF_JMP_IMM(BPF_JSGE, W1, 0, 6),
			BPF_AWU64_IMM(BPF_ADD, W1, 1),
			BPF_JMP_IMM(BPF_JSGE, W1, 0, 4),
			BPF_AWU64_IMM(BPF_ADD, W1, 1),
			BPF_JMP_IMM(BPF_JSGE, W1, 0, 2),
			BPF_AWU64_IMM(BPF_ADD, W1, 1),
			BPF_JMP_IMM(BPF_JSGE, W1, 0, 1),
			BPF_EXIT_INSN(),		/* bad exit */
			BPF_AWU32_IMM(BPF_MOV, W0, 1),	/* good exit */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSGE_K: Signed jump: vawue wawk 2",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -3),
			BPF_JMP_IMM(BPF_JSGE, W1, 0, 4),
			BPF_AWU64_IMM(BPF_ADD, W1, 2),
			BPF_JMP_IMM(BPF_JSGE, W1, 0, 2),
			BPF_AWU64_IMM(BPF_ADD, W1, 2),
			BPF_JMP_IMM(BPF_JSGE, W1, 0, 1),
			BPF_EXIT_INSN(),		/* bad exit */
			BPF_AWU32_IMM(BPF_MOV, W0, 1),	/* good exit */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JGT | BPF_K */
	{
		"JMP_JGT_K: if (3 > 2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_JMP_IMM(BPF_JGT, W1, 2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JGT_K: Unsigned jump: if (-1 > 1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -1),
			BPF_JMP_IMM(BPF_JGT, W1, 1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JWT | BPF_K */
	{
		"JMP_JWT_K: if (2 < 3) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 2),
			BPF_JMP_IMM(BPF_JWT, W1, 3, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JGT_K: Unsigned jump: if (1 < -1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 1),
			BPF_JMP_IMM(BPF_JWT, W1, -1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JGE | BPF_K */
	{
		"JMP_JGE_K: if (3 >= 2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_JMP_IMM(BPF_JGE, W1, 2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JWE | BPF_K */
	{
		"JMP_JWE_K: if (2 <= 3) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 2),
			BPF_JMP_IMM(BPF_JWE, W1, 3, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JGT | BPF_K jump backwawds */
	{
		"JMP_JGT_K: if (3 > 2) wetuwn 1 (jump backwawds)",
		.u.insns_int = {
			BPF_JMP_IMM(BPF_JA, 0, 0, 2), /* goto stawt */
			BPF_AWU32_IMM(BPF_MOV, W0, 1), /* out: */
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 0), /* stawt: */
			BPF_WD_IMM64(W1, 3), /* note: this takes 2 insns */
			BPF_JMP_IMM(BPF_JGT, W1, 2, -6), /* goto out */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JGE_K: if (3 >= 3) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_JMP_IMM(BPF_JGE, W1, 3, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JWT | BPF_K jump backwawds */
	{
		"JMP_JGT_K: if (2 < 3) wetuwn 1 (jump backwawds)",
		.u.insns_int = {
			BPF_JMP_IMM(BPF_JA, 0, 0, 2), /* goto stawt */
			BPF_AWU32_IMM(BPF_MOV, W0, 1), /* out: */
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 0), /* stawt: */
			BPF_WD_IMM64(W1, 2), /* note: this takes 2 insns */
			BPF_JMP_IMM(BPF_JWT, W1, 3, -6), /* goto out */
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JWE_K: if (3 <= 3) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_JMP_IMM(BPF_JWE, W1, 3, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JNE | BPF_K */
	{
		"JMP_JNE_K: if (3 != 2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_JMP_IMM(BPF_JNE, W1, 2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JEQ | BPF_K */
	{
		"JMP_JEQ_K: if (3 == 3) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_JMP_IMM(BPF_JEQ, W1, 3, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JSET | BPF_K */
	{
		"JMP_JSET_K: if (0x3 & 0x2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_JMP_IMM(BPF_JSET, W1, 2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSET_K: if (0x3 & 0xffffffff) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_JMP_IMM(BPF_JSET, W1, 0xffffffff, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JSGT | BPF_X */
	{
		"JMP_JSGT_X: Signed jump: if (-1 > -2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -1),
			BPF_WD_IMM64(W2, -2),
			BPF_JMP_WEG(BPF_JSGT, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSGT_X: Signed jump: if (-1 > -1) wetuwn 0",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_WD_IMM64(W1, -1),
			BPF_WD_IMM64(W2, -1),
			BPF_JMP_WEG(BPF_JSGT, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JSWT | BPF_X */
	{
		"JMP_JSWT_X: Signed jump: if (-2 < -1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -1),
			BPF_WD_IMM64(W2, -2),
			BPF_JMP_WEG(BPF_JSWT, W2, W1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSWT_X: Signed jump: if (-1 < -1) wetuwn 0",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_WD_IMM64(W1, -1),
			BPF_WD_IMM64(W2, -1),
			BPF_JMP_WEG(BPF_JSWT, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JSGE | BPF_X */
	{
		"JMP_JSGE_X: Signed jump: if (-1 >= -2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -1),
			BPF_WD_IMM64(W2, -2),
			BPF_JMP_WEG(BPF_JSGE, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSGE_X: Signed jump: if (-1 >= -1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -1),
			BPF_WD_IMM64(W2, -1),
			BPF_JMP_WEG(BPF_JSGE, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JSWE | BPF_X */
	{
		"JMP_JSWE_X: Signed jump: if (-2 <= -1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -1),
			BPF_WD_IMM64(W2, -2),
			BPF_JMP_WEG(BPF_JSWE, W2, W1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSWE_X: Signed jump: if (-1 <= -1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -1),
			BPF_WD_IMM64(W2, -1),
			BPF_JMP_WEG(BPF_JSWE, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JGT | BPF_X */
	{
		"JMP_JGT_X: if (3 > 2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JGT, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JGT_X: Unsigned jump: if (-1 > 1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -1),
			BPF_WD_IMM64(W2, 1),
			BPF_JMP_WEG(BPF_JGT, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JWT | BPF_X */
	{
		"JMP_JWT_X: if (2 < 3) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JWT, W2, W1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JWT_X: Unsigned jump: if (1 < -1) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, -1),
			BPF_WD_IMM64(W2, 1),
			BPF_JMP_WEG(BPF_JWT, W2, W1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JGE | BPF_X */
	{
		"JMP_JGE_X: if (3 >= 2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JGE, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JGE_X: if (3 >= 3) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 3),
			BPF_JMP_WEG(BPF_JGE, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JWE | BPF_X */
	{
		"JMP_JWE_X: if (2 <= 3) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JWE, W2, W1, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JWE_X: if (3 <= 3) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 3),
			BPF_JMP_WEG(BPF_JWE, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		/* Mainwy testing JIT + imm64 hewe. */
		"JMP_JGE_X: wdimm64 test 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JGE, W1, W2, 2),
			BPF_WD_IMM64(W0, 0xffffffffffffffffUWW),
			BPF_WD_IMM64(W0, 0xeeeeeeeeeeeeeeeeUWW),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xeeeeeeeeU } },
	},
	{
		"JMP_JGE_X: wdimm64 test 2",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JGE, W1, W2, 0),
			BPF_WD_IMM64(W0, 0xffffffffffffffffUWW),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffffU } },
	},
	{
		"JMP_JGE_X: wdimm64 test 3",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JGE, W1, W2, 4),
			BPF_WD_IMM64(W0, 0xffffffffffffffffUWW),
			BPF_WD_IMM64(W0, 0xeeeeeeeeeeeeeeeeUWW),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JWE_X: wdimm64 test 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JWE, W2, W1, 2),
			BPF_WD_IMM64(W0, 0xffffffffffffffffUWW),
			BPF_WD_IMM64(W0, 0xeeeeeeeeeeeeeeeeUWW),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xeeeeeeeeU } },
	},
	{
		"JMP_JWE_X: wdimm64 test 2",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JWE, W2, W1, 0),
			BPF_WD_IMM64(W0, 0xffffffffffffffffUWW),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0xffffffffU } },
	},
	{
		"JMP_JWE_X: wdimm64 test 3",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JWE, W2, W1, 4),
			BPF_WD_IMM64(W0, 0xffffffffffffffffUWW),
			BPF_WD_IMM64(W0, 0xeeeeeeeeeeeeeeeeUWW),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JNE | BPF_X */
	{
		"JMP_JNE_X: if (3 != 2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JNE, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JEQ | BPF_X */
	{
		"JMP_JEQ_X: if (3 == 3) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 3),
			BPF_JMP_WEG(BPF_JEQ, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	/* BPF_JMP | BPF_JSET | BPF_X */
	{
		"JMP_JSET_X: if (0x3 & 0x2) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 2),
			BPF_JMP_WEG(BPF_JSET, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSET_X: if (0x3 & 0xffffffff) wetuwn 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W0, 0),
			BPF_WD_IMM64(W1, 3),
			BPF_WD_IMM64(W2, 0xffffffff),
			BPF_JMP_WEG(BPF_JSET, W1, W2, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JA: Jump, gap, jump, ...",
		{ },
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0xababcbac } },
		.fiww_hewpew = bpf_fiww_ja,
	},
	{	/* Mainwy checking JIT hewe. */
		"BPF_MAXINSNS: Maximum possibwe witewaws",
		{ },
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0xffffffff } },
		.fiww_hewpew = bpf_fiww_maxinsns1,
	},
	{	/* Mainwy checking JIT hewe. */
		"BPF_MAXINSNS: Singwe witewaw",
		{ },
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0xfefefefe } },
		.fiww_hewpew = bpf_fiww_maxinsns2,
	},
	{	/* Mainwy checking JIT hewe. */
		"BPF_MAXINSNS: Wun/add untiw end",
		{ },
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0x947bf368 } },
		.fiww_hewpew = bpf_fiww_maxinsns3,
	},
	{
		"BPF_MAXINSNS: Too many instwuctions",
		{ },
		CWASSIC | FWAG_NO_DATA | FWAG_EXPECTED_FAIW,
		{ },
		{ },
		.fiww_hewpew = bpf_fiww_maxinsns4,
		.expected_ewwcode = -EINVAW,
	},
	{	/* Mainwy checking JIT hewe. */
		"BPF_MAXINSNS: Vewy wong jump",
		{ },
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0xabababab } },
		.fiww_hewpew = bpf_fiww_maxinsns5,
	},
	{	/* Mainwy checking JIT hewe. */
		"BPF_MAXINSNS: Ctx heavy twansfowmations",
		{ },
		CWASSIC,
		{ },
		{
			{  1, SKB_VWAN_PWESENT },
			{ 10, SKB_VWAN_PWESENT }
		},
		.fiww_hewpew = bpf_fiww_maxinsns6,
	},
	{	/* Mainwy checking JIT hewe. */
		"BPF_MAXINSNS: Caww heavy twansfowmations",
		{ },
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 1, 0 }, { 10, 0 } },
		.fiww_hewpew = bpf_fiww_maxinsns7,
	},
	{	/* Mainwy checking JIT hewe. */
		"BPF_MAXINSNS: Jump heavy test",
		{ },
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0xffffffff } },
		.fiww_hewpew = bpf_fiww_maxinsns8,
	},
	{	/* Mainwy checking JIT hewe. */
		"BPF_MAXINSNS: Vewy wong jump backwawds",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0xcbababab } },
		.fiww_hewpew = bpf_fiww_maxinsns9,
	},
	{	/* Mainwy checking JIT hewe. */
		"BPF_MAXINSNS: Edge hopping nuthouse",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0xabababac } },
		.fiww_hewpew = bpf_fiww_maxinsns10,
	},
	{
		"BPF_MAXINSNS: Jump, gap, jump, ...",
		{ },
		CWASSIC | FWAG_NO_DATA,
		{ },
		{ { 0, 0xababcbac } },
		.fiww_hewpew = bpf_fiww_maxinsns11,
	},
	{
		"BPF_MAXINSNS: jump ovew MSH",
		{ },
		CWASSIC | FWAG_EXPECTED_FAIW,
		{ 0xfa, 0xfb, 0xfc, 0xfd, },
		{ { 4, 0xabababab } },
		.fiww_hewpew = bpf_fiww_maxinsns12,
		.expected_ewwcode = -EINVAW,
	},
	{
		"BPF_MAXINSNS: exec aww MSH",
		{ },
		CWASSIC,
		{ 0xfa, 0xfb, 0xfc, 0xfd, },
		{ { 4, 0xababab83 } },
		.fiww_hewpew = bpf_fiww_maxinsns13,
	},
	{
		"BPF_MAXINSNS: wd_abs+get_pwocessow_id",
		{ },
		CWASSIC,
		{ },
		{ { 1, 0xbee } },
		.fiww_hewpew = bpf_fiww_wd_abs_get_pwocessow_id,
	},
	/*
	 * WD_IND / WD_ABS on fwagmented SKBs
	 */
	{
		"WD_IND byte fwag",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x40),
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, 0x0),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_SKB_FWAG,
		{ },
		{ {0x40, 0x42} },
		.fwag_data = {
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		},
	},
	{
		"WD_IND hawfwowd fwag",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x40),
			BPF_STMT(BPF_WD | BPF_IND | BPF_H, 0x4),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_SKB_FWAG,
		{ },
		{ {0x40, 0x4344} },
		.fwag_data = {
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		},
	},
	{
		"WD_IND wowd fwag",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x40),
			BPF_STMT(BPF_WD | BPF_IND | BPF_W, 0x8),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_SKB_FWAG,
		{ },
		{ {0x40, 0x21071983} },
		.fwag_data = {
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		},
	},
	{
		"WD_IND hawfwowd mixed head/fwag",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x40),
			BPF_STMT(BPF_WD | BPF_IND | BPF_H, -0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_SKB_FWAG,
		{ [0x3e] = 0x25, [0x3f] = 0x05, },
		{ {0x40, 0x0519} },
		.fwag_data = { 0x19, 0x82 },
	},
	{
		"WD_IND wowd mixed head/fwag",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x40),
			BPF_STMT(BPF_WD | BPF_IND | BPF_W, -0x2),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_SKB_FWAG,
		{ [0x3e] = 0x25, [0x3f] = 0x05, },
		{ {0x40, 0x25051982} },
		.fwag_data = { 0x19, 0x82 },
	},
	{
		"WD_ABS byte fwag",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, 0x40),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_SKB_FWAG,
		{ },
		{ {0x40, 0x42} },
		.fwag_data = {
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		},
	},
	{
		"WD_ABS hawfwowd fwag",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_H, 0x44),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_SKB_FWAG,
		{ },
		{ {0x40, 0x4344} },
		.fwag_data = {
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		},
	},
	{
		"WD_ABS wowd fwag",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, 0x48),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_SKB_FWAG,
		{ },
		{ {0x40, 0x21071983} },
		.fwag_data = {
			0x42, 0x00, 0x00, 0x00,
			0x43, 0x44, 0x00, 0x00,
			0x21, 0x07, 0x19, 0x83,
		},
	},
	{
		"WD_ABS hawfwowd mixed head/fwag",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_H, 0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_SKB_FWAG,
		{ [0x3e] = 0x25, [0x3f] = 0x05, },
		{ {0x40, 0x0519} },
		.fwag_data = { 0x19, 0x82 },
	},
	{
		"WD_ABS wowd mixed head/fwag",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, 0x3e),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_SKB_FWAG,
		{ [0x3e] = 0x25, [0x3f] = 0x05, },
		{ {0x40, 0x25051982} },
		.fwag_data = { 0x19, 0x82 },
	},
	/*
	 * WD_IND / WD_ABS on non fwagmented SKBs
	 */
	{
		/*
		 * this tests that the JIT/intewpwetew cowwectwy wesets X
		 * befowe using it in an WD_IND instwuction.
		 */
		"WD_IND byte defauwt X",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, 0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x1] = 0x42 },
		{ {0x40, 0x42 } },
	},
	{
		"WD_IND byte positive offset",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, 0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x82 } },
	},
	{
		"WD_IND byte negative offset",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, -0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x05 } },
	},
	{
		"WD_IND byte positive offset, aww ff",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, 0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff },
		{ {0x40, 0xff } },
	},
	{
		"WD_IND byte positive offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, 0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 }, },
	},
	{
		"WD_IND byte negative offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, -0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 } },
	},
	{
		"WD_IND byte negative offset, muwtipwe cawws",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3b),
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, SKF_WW_OFF + 1),
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, SKF_WW_OFF + 2),
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, SKF_WW_OFF + 3),
			BPF_STMT(BPF_WD | BPF_IND | BPF_B, SKF_WW_OFF + 4),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x82 }, },
	},
	{
		"WD_IND hawfwowd positive offset",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_WD | BPF_IND | BPF_H, 0x2),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
		},
		{ {0x40, 0xdd88 } },
	},
	{
		"WD_IND hawfwowd negative offset",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_WD | BPF_IND | BPF_H, -0x2),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
		},
		{ {0x40, 0xbb66 } },
	},
	{
		"WD_IND hawfwowd unawigned",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_WD | BPF_IND | BPF_H, -0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
		},
		{ {0x40, 0x66cc } },
	},
	{
		"WD_IND hawfwowd positive offset, aww ff",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3d),
			BPF_STMT(BPF_WD | BPF_IND | BPF_H, 0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff },
		{ {0x40, 0xffff } },
	},
	{
		"WD_IND hawfwowd positive offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_WD | BPF_IND | BPF_H, 0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 }, },
	},
	{
		"WD_IND hawfwowd negative offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_WD | BPF_IND | BPF_H, -0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 } },
	},
	{
		"WD_IND wowd positive offset",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_WD | BPF_IND | BPF_W, 0x4),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0xee99ffaa } },
	},
	{
		"WD_IND wowd negative offset",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_WD | BPF_IND | BPF_W, -0x4),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0xaa55bb66 } },
	},
	{
		"WD_IND wowd unawigned (addw & 3 == 2)",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_WD | BPF_IND | BPF_W, -0x2),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0xbb66cc77 } },
	},
	{
		"WD_IND wowd unawigned (addw & 3 == 1)",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_WD | BPF_IND | BPF_W, -0x3),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0x55bb66cc } },
	},
	{
		"WD_IND wowd unawigned (addw & 3 == 3)",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x20),
			BPF_STMT(BPF_WD | BPF_IND | BPF_W, -0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0x66cc77dd } },
	},
	{
		"WD_IND wowd positive offset, aww ff",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3b),
			BPF_STMT(BPF_WD | BPF_IND | BPF_W, 0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff },
		{ {0x40, 0xffffffff } },
	},
	{
		"WD_IND wowd positive offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_WD | BPF_IND | BPF_W, 0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 }, },
	},
	{
		"WD_IND wowd negative offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WDX | BPF_IMM, 0x3e),
			BPF_STMT(BPF_WD | BPF_IND | BPF_W, -0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 } },
	},
	{
		"WD_ABS byte",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, 0x20),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0xcc } },
	},
	{
		"WD_ABS byte positive offset, aww ff",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, 0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff },
		{ {0x40, 0xff } },
	},
	{
		"WD_ABS byte positive offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, 0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 }, },
	},
	{
		"WD_ABS byte negative offset, out of bounds woad",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, -1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_EXPECTED_FAIW,
		.expected_ewwcode = -EINVAW,
	},
	{
		"WD_ABS byte negative offset, in bounds",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, SKF_WW_OFF + 0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x82 }, },
	},
	{
		"WD_ABS byte negative offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, SKF_WW_OFF + 0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 }, },
	},
	{
		"WD_ABS byte negative offset, muwtipwe cawws",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, SKF_WW_OFF + 0x3c),
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, SKF_WW_OFF + 0x3d),
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, SKF_WW_OFF + 0x3e),
			BPF_STMT(BPF_WD | BPF_ABS | BPF_B, SKF_WW_OFF + 0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x82 }, },
	},
	{
		"WD_ABS hawfwowd",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_H, 0x22),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0xdd88 } },
	},
	{
		"WD_ABS hawfwowd unawigned",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_H, 0x25),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0x99ff } },
	},
	{
		"WD_ABS hawfwowd positive offset, aww ff",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_H, 0x3e),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff },
		{ {0x40, 0xffff } },
	},
	{
		"WD_ABS hawfwowd positive offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_H, 0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 }, },
	},
	{
		"WD_ABS hawfwowd negative offset, out of bounds woad",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_H, -1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_EXPECTED_FAIW,
		.expected_ewwcode = -EINVAW,
	},
	{
		"WD_ABS hawfwowd negative offset, in bounds",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_H, SKF_WW_OFF + 0x3e),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x1982 }, },
	},
	{
		"WD_ABS hawfwowd negative offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_H, SKF_WW_OFF + 0x3e),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 }, },
	},
	{
		"WD_ABS wowd",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, 0x1c),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0xaa55bb66 } },
	},
	{
		"WD_ABS wowd unawigned (addw & 3 == 2)",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, 0x22),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0xdd88ee99 } },
	},
	{
		"WD_ABS wowd unawigned (addw & 3 == 1)",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, 0x21),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0x77dd88ee } },
	},
	{
		"WD_ABS wowd unawigned (addw & 3 == 3)",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, 0x23),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{
			[0x1c] = 0xaa, [0x1d] = 0x55,
			[0x1e] = 0xbb, [0x1f] = 0x66,
			[0x20] = 0xcc, [0x21] = 0x77,
			[0x22] = 0xdd, [0x23] = 0x88,
			[0x24] = 0xee, [0x25] = 0x99,
			[0x26] = 0xff, [0x27] = 0xaa,
		},
		{ {0x40, 0x88ee99ff } },
	},
	{
		"WD_ABS wowd positive offset, aww ff",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, 0x3c),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0xff, [0x3d] = 0xff,  [0x3e] = 0xff, [0x3f] = 0xff },
		{ {0x40, 0xffffffff } },
	},
	{
		"WD_ABS wowd positive offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, 0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 }, },
	},
	{
		"WD_ABS wowd negative offset, out of bounds woad",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, -1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_EXPECTED_FAIW,
		.expected_ewwcode = -EINVAW,
	},
	{
		"WD_ABS wowd negative offset, in bounds",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, SKF_WW_OFF + 0x3c),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x25051982 }, },
	},
	{
		"WD_ABS wowd negative offset, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_ABS | BPF_W, SKF_WW_OFF + 0x3c),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x3f, 0 }, },
	},
	{
		"WDX_MSH standawone, pwesewved A",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 0x3c),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0xffeebbaa }, },
	},
	{
		"WDX_MSH standawone, pwesewved A 2",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 0x175e9d63),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 0x3c),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 0x3d),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 0x3e),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 0x3f),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x175e9d63 }, },
	},
	{
		"WDX_MSH standawone, test wesuwt 1",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 0x3c),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x14 }, },
	},
	{
		"WDX_MSH standawone, test wesuwt 2",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 0x3e),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x24 }, },
	},
	{
		"WDX_MSH standawone, negative offset",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, -1),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0 }, },
	},
	{
		"WDX_MSH standawone, negative offset 2",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, SKF_WW_OFF + 0x3e),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0x24 }, },
	},
	{
		"WDX_MSH standawone, out of bounds",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 0xffeebbaa),
			BPF_STMT(BPF_WDX | BPF_B | BPF_MSH, 0x40),
			BPF_STMT(BPF_MISC | BPF_TXA, 0),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC,
		{ [0x3c] = 0x25, [0x3d] = 0x05,  [0x3e] = 0x19, [0x3f] = 0x82 },
		{ {0x40, 0 }, },
	},
	/*
	 * vewify that the intewpwetew ow JIT cowwectwy sets A and X
	 * to 0.
	 */
	{
		"ADD defauwt X",
		.u.insns = {
			/*
			 * A = 0x42
			 * A = A + X
			 * wet A
			 */
			BPF_STMT(BPF_WD | BPF_IMM, 0x42),
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x42 } },
	},
	{
		"ADD defauwt A",
		.u.insns = {
			/*
			 * A = A + 0x42
			 * wet A
			 */
			BPF_STMT(BPF_AWU | BPF_ADD | BPF_K, 0x42),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x42 } },
	},
	{
		"SUB defauwt X",
		.u.insns = {
			/*
			 * A = 0x66
			 * A = A - X
			 * wet A
			 */
			BPF_STMT(BPF_WD | BPF_IMM, 0x66),
			BPF_STMT(BPF_AWU | BPF_SUB | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x66 } },
	},
	{
		"SUB defauwt A",
		.u.insns = {
			/*
			 * A = A - -0x66
			 * wet A
			 */
			BPF_STMT(BPF_AWU | BPF_SUB | BPF_K, -0x66),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x66 } },
	},
	{
		"MUW defauwt X",
		.u.insns = {
			/*
			 * A = 0x42
			 * A = A * X
			 * wet A
			 */
			BPF_STMT(BPF_WD | BPF_IMM, 0x42),
			BPF_STMT(BPF_AWU | BPF_MUW | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x0 } },
	},
	{
		"MUW defauwt A",
		.u.insns = {
			/*
			 * A = A * 0x66
			 * wet A
			 */
			BPF_STMT(BPF_AWU | BPF_MUW | BPF_K, 0x66),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x0 } },
	},
	{
		"DIV defauwt X",
		.u.insns = {
			/*
			 * A = 0x42
			 * A = A / X ; this hawt the fiwtew execution if X is 0
			 * wet 0x42
			 */
			BPF_STMT(BPF_WD | BPF_IMM, 0x42),
			BPF_STMT(BPF_AWU | BPF_DIV | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_K, 0x42),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x0 } },
	},
	{
		"DIV defauwt A",
		.u.insns = {
			/*
			 * A = A / 1
			 * wet A
			 */
			BPF_STMT(BPF_AWU | BPF_DIV | BPF_K, 0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x0 } },
	},
	{
		"MOD defauwt X",
		.u.insns = {
			/*
			 * A = 0x42
			 * A = A mod X ; this hawt the fiwtew execution if X is 0
			 * wet 0x42
			 */
			BPF_STMT(BPF_WD | BPF_IMM, 0x42),
			BPF_STMT(BPF_AWU | BPF_MOD | BPF_X, 0),
			BPF_STMT(BPF_WET | BPF_K, 0x42),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x0 } },
	},
	{
		"MOD defauwt A",
		.u.insns = {
			/*
			 * A = A mod 1
			 * wet A
			 */
			BPF_STMT(BPF_AWU | BPF_MOD | BPF_K, 0x1),
			BPF_STMT(BPF_WET | BPF_A, 0x0),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x0 } },
	},
	{
		"JMP EQ defauwt A",
		.u.insns = {
			/*
			 * cmp A, 0x0, 0, 1
			 * wet 0x42
			 * wet 0x66
			 */
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0x0, 0, 1),
			BPF_STMT(BPF_WET | BPF_K, 0x42),
			BPF_STMT(BPF_WET | BPF_K, 0x66),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x42 } },
	},
	{
		"JMP EQ defauwt X",
		.u.insns = {
			/*
			 * A = 0x0
			 * cmp A, X, 0, 1
			 * wet 0x42
			 * wet 0x66
			 */
			BPF_STMT(BPF_WD | BPF_IMM, 0x0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_X, 0x0, 0, 1),
			BPF_STMT(BPF_WET | BPF_K, 0x42),
			BPF_STMT(BPF_WET | BPF_K, 0x66),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ {0x1, 0x42 } },
	},
	/* Checking intewpwetew vs JIT wwt signed extended imms. */
	{
		"JNE signed compawe, test 1",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W1, 0xfefbbc12),
			BPF_AWU32_IMM(BPF_MOV, W3, 0xffff0000),
			BPF_MOV64_WEG(W2, W1),
			BPF_AWU64_WEG(BPF_AND, W2, W3),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_JMP_IMM(BPF_JNE, W2, -17104896, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JNE signed compawe, test 2",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W1, 0xfefbbc12),
			BPF_AWU32_IMM(BPF_MOV, W3, 0xffff0000),
			BPF_MOV64_WEG(W2, W1),
			BPF_AWU64_WEG(BPF_AND, W2, W3),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_JMP_IMM(BPF_JNE, W2, 0xfefb0000, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JNE signed compawe, test 3",
		.u.insns_int = {
			BPF_AWU32_IMM(BPF_MOV, W1, 0xfefbbc12),
			BPF_AWU32_IMM(BPF_MOV, W3, 0xffff0000),
			BPF_AWU32_IMM(BPF_MOV, W4, 0xfefb0000),
			BPF_MOV64_WEG(W2, W1),
			BPF_AWU64_WEG(BPF_AND, W2, W3),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JNE, W2, W4, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"JNE signed compawe, test 4",
		.u.insns_int = {
			BPF_WD_IMM64(W1, -17104896),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_JMP_IMM(BPF_JNE, W1, -17104896, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"JNE signed compawe, test 5",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0xfefb0000),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_JMP_IMM(BPF_JNE, W1, 0xfefb0000, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 1 } },
	},
	{
		"JNE signed compawe, test 6",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x7efb0000),
			BPF_AWU32_IMM(BPF_MOV, W0, 1),
			BPF_JMP_IMM(BPF_JNE, W1, 0x7efb0000, 1),
			BPF_AWU32_IMM(BPF_MOV, W0, 2),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 2 } },
	},
	{
		"JNE signed compawe, test 7",
		.u.insns = {
			BPF_STMT(BPF_WD | BPF_IMM, 0xffff0000),
			BPF_STMT(BPF_MISC | BPF_TAX, 0),
			BPF_STMT(BPF_WD | BPF_IMM, 0xfefbbc12),
			BPF_STMT(BPF_AWU | BPF_AND | BPF_X, 0),
			BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0xfefb0000, 1, 0),
			BPF_STMT(BPF_WET | BPF_K, 1),
			BPF_STMT(BPF_WET | BPF_K, 2),
		},
		CWASSIC | FWAG_NO_DATA,
		{},
		{ { 0, 2 } },
	},
	/* BPF_WDX_MEM with opewand awiasing */
	{
		"WDX_MEM_B: opewand wegistew awiasing",
		.u.insns_int = {
			BPF_ST_MEM(BPF_B, W10, -8, 123),
			BPF_MOV64_WEG(W0, W10),
			BPF_WDX_MEM(BPF_B, W0, W0, -8),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 123 } },
		.stack_depth = 8,
	},
	{
		"WDX_MEM_H: opewand wegistew awiasing",
		.u.insns_int = {
			BPF_ST_MEM(BPF_H, W10, -8, 12345),
			BPF_MOV64_WEG(W0, W10),
			BPF_WDX_MEM(BPF_H, W0, W0, -8),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 12345 } },
		.stack_depth = 8,
	},
	{
		"WDX_MEM_W: opewand wegistew awiasing",
		.u.insns_int = {
			BPF_ST_MEM(BPF_W, W10, -8, 123456789),
			BPF_MOV64_WEG(W0, W10),
			BPF_WDX_MEM(BPF_W, W0, W0, -8),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 123456789 } },
		.stack_depth = 8,
	},
	{
		"WDX_MEM_DW: opewand wegistew awiasing",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x123456789abcdefUWW),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
			BPF_MOV64_WEG(W0, W10),
			BPF_WDX_MEM(BPF_DW, W0, W0, -8),
			BPF_AWU64_WEG(BPF_SUB, W0, W1),
			BPF_MOV64_WEG(W1, W0),
			BPF_AWU64_IMM(BPF_WSH, W1, 32),
			BPF_AWU64_WEG(BPF_OW, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	/*
	 * Wegistew (non-)cwobbewing tests fow the case whewe a JIT impwements
	 * compwex AWU ow ATOMIC opewations via function cawws. If so, the
	 * function caww must be twanspawent to the eBPF wegistews. The JIT
	 * must thewefowe save and westowe wewevant wegistews acwoss the caww.
	 * The fowwowing tests check that the eBPF wegistews wetain theiw
	 * vawues aftew such an opewation. Mainwy intended fow compwex AWU
	 * and atomic opewation, but we wun it fow aww. You nevew know...
	 *
	 * Note that each opewations shouwd be tested twice with diffewent
	 * destinations, to check pwesewvation fow aww wegistews.
	 */
#define BPF_TEST_CWOBBEW_AWU(awu, op, dst, swc)			\
	{							\
		#awu "_" #op " to " #dst ": no cwobbewing",	\
		.u.insns_int = {				\
			BPF_AWU64_IMM(BPF_MOV, W0, W0),		\
			BPF_AWU64_IMM(BPF_MOV, W1, W1),		\
			BPF_AWU64_IMM(BPF_MOV, W2, W2),		\
			BPF_AWU64_IMM(BPF_MOV, W3, W3),		\
			BPF_AWU64_IMM(BPF_MOV, W4, W4),		\
			BPF_AWU64_IMM(BPF_MOV, W5, W5),		\
			BPF_AWU64_IMM(BPF_MOV, W6, W6),		\
			BPF_AWU64_IMM(BPF_MOV, W7, W7),		\
			BPF_AWU64_IMM(BPF_MOV, W8, W8),		\
			BPF_AWU64_IMM(BPF_MOV, W9, W9),		\
			BPF_##awu(BPF_ ##op, dst, swc),		\
			BPF_AWU32_IMM(BPF_MOV, dst, dst),	\
			BPF_JMP_IMM(BPF_JNE, W0, W0, 10),	\
			BPF_JMP_IMM(BPF_JNE, W1, W1, 9),	\
			BPF_JMP_IMM(BPF_JNE, W2, W2, 8),	\
			BPF_JMP_IMM(BPF_JNE, W3, W3, 7),	\
			BPF_JMP_IMM(BPF_JNE, W4, W4, 6),	\
			BPF_JMP_IMM(BPF_JNE, W5, W5, 5),	\
			BPF_JMP_IMM(BPF_JNE, W6, W6, 4),	\
			BPF_JMP_IMM(BPF_JNE, W7, W7, 3),	\
			BPF_JMP_IMM(BPF_JNE, W8, W8, 2),	\
			BPF_JMP_IMM(BPF_JNE, W9, W9, 1),	\
			BPF_AWU64_IMM(BPF_MOV, W0, 1),		\
			BPF_EXIT_INSN(),			\
		},						\
		INTEWNAW,					\
		{ },						\
		{ { 0, 1 } }					\
	}
	/* AWU64 opewations, wegistew cwobbewing */
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, AND, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, AND, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, OW, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, OW, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, XOW, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, XOW, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, WSH, W8, 12),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, WSH, W9, 12),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, WSH, W8, 12),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, WSH, W9, 12),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, AWSH, W8, 12),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, AWSH, W9, 12),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, ADD, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, ADD, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, SUB, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, SUB, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, MUW, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, MUW, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, DIV, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, DIV, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, MOD, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU64_IMM, MOD, W9, 123456789),
	/* AWU32 immediate opewations, wegistew cwobbewing */
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, AND, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, AND, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, OW, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, OW, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, XOW, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, XOW, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, WSH, W8, 12),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, WSH, W9, 12),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, WSH, W8, 12),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, WSH, W9, 12),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, AWSH, W8, 12),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, AWSH, W9, 12),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, ADD, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, ADD, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, SUB, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, SUB, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, MUW, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, MUW, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, DIV, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, DIV, W9, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, MOD, W8, 123456789),
	BPF_TEST_CWOBBEW_AWU(AWU32_IMM, MOD, W9, 123456789),
	/* AWU64 wegistew opewations, wegistew cwobbewing */
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, AND, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, AND, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, OW, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, OW, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, XOW, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, XOW, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, WSH, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, WSH, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, WSH, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, WSH, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, AWSH, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, AWSH, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, ADD, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, ADD, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, SUB, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, SUB, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, MUW, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, MUW, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, DIV, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, DIV, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, MOD, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU64_WEG, MOD, W9, W1),
	/* AWU32 wegistew opewations, wegistew cwobbewing */
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, AND, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, AND, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, OW, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, OW, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, XOW, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, XOW, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, WSH, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, WSH, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, WSH, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, WSH, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, AWSH, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, AWSH, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, ADD, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, ADD, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, SUB, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, SUB, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, MUW, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, MUW, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, DIV, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, DIV, W9, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, MOD, W8, W1),
	BPF_TEST_CWOBBEW_AWU(AWU32_WEG, MOD, W9, W1),
#undef BPF_TEST_CWOBBEW_AWU
#define BPF_TEST_CWOBBEW_ATOMIC(width, op)			\
	{							\
		"Atomic_" #width " " #op ": no cwobbewing",	\
		.u.insns_int = {				\
			BPF_AWU64_IMM(BPF_MOV, W0, 0),		\
			BPF_AWU64_IMM(BPF_MOV, W1, 1),		\
			BPF_AWU64_IMM(BPF_MOV, W2, 2),		\
			BPF_AWU64_IMM(BPF_MOV, W3, 3),		\
			BPF_AWU64_IMM(BPF_MOV, W4, 4),		\
			BPF_AWU64_IMM(BPF_MOV, W5, 5),		\
			BPF_AWU64_IMM(BPF_MOV, W6, 6),		\
			BPF_AWU64_IMM(BPF_MOV, W7, 7),		\
			BPF_AWU64_IMM(BPF_MOV, W8, 8),		\
			BPF_AWU64_IMM(BPF_MOV, W9, 9),		\
			BPF_ST_MEM(width, W10, -8,		\
				   (op) == BPF_CMPXCHG ? 0 :	\
				   (op) & BPF_FETCH ? 1 : 0),	\
			BPF_ATOMIC_OP(width, op, W10, W1, -8),	\
			BPF_JMP_IMM(BPF_JNE, W0, 0, 10),	\
			BPF_JMP_IMM(BPF_JNE, W1, 1, 9),		\
			BPF_JMP_IMM(BPF_JNE, W2, 2, 8),		\
			BPF_JMP_IMM(BPF_JNE, W3, 3, 7),		\
			BPF_JMP_IMM(BPF_JNE, W4, 4, 6),		\
			BPF_JMP_IMM(BPF_JNE, W5, 5, 5),		\
			BPF_JMP_IMM(BPF_JNE, W6, 6, 4),		\
			BPF_JMP_IMM(BPF_JNE, W7, 7, 3),		\
			BPF_JMP_IMM(BPF_JNE, W8, 8, 2),		\
			BPF_JMP_IMM(BPF_JNE, W9, 9, 1),		\
			BPF_AWU64_IMM(BPF_MOV, W0, 1),		\
			BPF_EXIT_INSN(),			\
		},						\
		INTEWNAW,					\
		{ },						\
		{ { 0, 1 } },					\
		.stack_depth = 8,				\
	}
	/* 64-bit atomic opewations, wegistew cwobbewing */
	BPF_TEST_CWOBBEW_ATOMIC(BPF_DW, BPF_ADD),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_DW, BPF_AND),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_DW, BPF_OW),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_DW, BPF_XOW),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_DW, BPF_ADD | BPF_FETCH),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_DW, BPF_AND | BPF_FETCH),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_DW, BPF_OW | BPF_FETCH),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_DW, BPF_XOW | BPF_FETCH),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_DW, BPF_XCHG),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_DW, BPF_CMPXCHG),
	/* 32-bit atomic opewations, wegistew cwobbewing */
	BPF_TEST_CWOBBEW_ATOMIC(BPF_W, BPF_ADD),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_W, BPF_AND),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_W, BPF_OW),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_W, BPF_XOW),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_W, BPF_ADD | BPF_FETCH),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_W, BPF_AND | BPF_FETCH),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_W, BPF_OW | BPF_FETCH),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_W, BPF_XOW | BPF_FETCH),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_W, BPF_XCHG),
	BPF_TEST_CWOBBEW_ATOMIC(BPF_W, BPF_CMPXCHG),
#undef BPF_TEST_CWOBBEW_ATOMIC
	/* Checking that AWU32 swc is not zewo extended in pwace */
#define BPF_AWU32_SWC_ZEXT(op)					\
	{							\
		"AWU32_" #op "_X: swc pwesewved in zext",	\
		.u.insns_int = {				\
			BPF_WD_IMM64(W1, 0x0123456789acbdefUWW),\
			BPF_WD_IMM64(W2, 0xfedcba9876543210UWW),\
			BPF_AWU64_WEG(BPF_MOV, W0, W1),		\
			BPF_AWU32_WEG(BPF_##op, W2, W1),	\
			BPF_AWU64_WEG(BPF_SUB, W0, W1),		\
			BPF_AWU64_WEG(BPF_MOV, W1, W0),		\
			BPF_AWU64_IMM(BPF_WSH, W1, 32),		\
			BPF_AWU64_WEG(BPF_OW, W0, W1),		\
			BPF_EXIT_INSN(),			\
		},						\
		INTEWNAW,					\
		{ },						\
		{ { 0, 0 } },					\
	}
	BPF_AWU32_SWC_ZEXT(MOV),
	BPF_AWU32_SWC_ZEXT(AND),
	BPF_AWU32_SWC_ZEXT(OW),
	BPF_AWU32_SWC_ZEXT(XOW),
	BPF_AWU32_SWC_ZEXT(ADD),
	BPF_AWU32_SWC_ZEXT(SUB),
	BPF_AWU32_SWC_ZEXT(MUW),
	BPF_AWU32_SWC_ZEXT(DIV),
	BPF_AWU32_SWC_ZEXT(MOD),
#undef BPF_AWU32_SWC_ZEXT
	/* Checking that ATOMIC32 swc is not zewo extended in pwace */
#define BPF_ATOMIC32_SWC_ZEXT(op)					\
	{								\
		"ATOMIC_W_" #op ": swc pwesewved in zext",		\
		.u.insns_int = {					\
			BPF_WD_IMM64(W0, 0x0123456789acbdefUWW),	\
			BPF_AWU64_WEG(BPF_MOV, W1, W0),			\
			BPF_ST_MEM(BPF_W, W10, -4, 0),			\
			BPF_ATOMIC_OP(BPF_W, BPF_##op, W10, W1, -4),	\
			BPF_AWU64_WEG(BPF_SUB, W0, W1),			\
			BPF_AWU64_WEG(BPF_MOV, W1, W0),			\
			BPF_AWU64_IMM(BPF_WSH, W1, 32),			\
			BPF_AWU64_WEG(BPF_OW, W0, W1),			\
			BPF_EXIT_INSN(),				\
		},							\
		INTEWNAW,						\
		{ },							\
		{ { 0, 0 } },						\
		.stack_depth = 8,					\
	}
	BPF_ATOMIC32_SWC_ZEXT(ADD),
	BPF_ATOMIC32_SWC_ZEXT(AND),
	BPF_ATOMIC32_SWC_ZEXT(OW),
	BPF_ATOMIC32_SWC_ZEXT(XOW),
#undef BPF_ATOMIC32_SWC_ZEXT
	/* Checking that CMPXCHG32 swc is not zewo extended in pwace */
	{
		"ATOMIC_W_CMPXCHG: swc pwesewved in zext",
		.u.insns_int = {
			BPF_WD_IMM64(W1, 0x0123456789acbdefUWW),
			BPF_AWU64_WEG(BPF_MOV, W2, W1),
			BPF_AWU64_WEG(BPF_MOV, W0, 0),
			BPF_ST_MEM(BPF_W, W10, -4, 0),
			BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, W10, W1, -4),
			BPF_AWU64_WEG(BPF_SUB, W1, W2),
			BPF_AWU64_WEG(BPF_MOV, W2, W1),
			BPF_AWU64_IMM(BPF_WSH, W2, 32),
			BPF_AWU64_WEG(BPF_OW, W1, W2),
			BPF_AWU64_WEG(BPF_MOV, W0, W1),
			BPF_EXIT_INSN(),
		},
		INTEWNAW,
		{ },
		{ { 0, 0 } },
		.stack_depth = 8,
	},
	/* Checking that JMP32 immediate swc is not zewo extended in pwace */
#define BPF_JMP32_IMM_ZEXT(op)					\
	{							\
		"JMP32_" #op "_K: opewand pwesewved in zext",	\
		.u.insns_int = {				\
			BPF_WD_IMM64(W0, 0x0123456789acbdefUWW),\
			BPF_AWU64_WEG(BPF_MOV, W1, W0),		\
			BPF_JMP32_IMM(BPF_##op, W0, 1234, 1),	\
			BPF_JMP_A(0), /* Nop */			\
			BPF_AWU64_WEG(BPF_SUB, W0, W1),		\
			BPF_AWU64_WEG(BPF_MOV, W1, W0),		\
			BPF_AWU64_IMM(BPF_WSH, W1, 32),		\
			BPF_AWU64_WEG(BPF_OW, W0, W1),		\
			BPF_EXIT_INSN(),			\
		},						\
		INTEWNAW,					\
		{ },						\
		{ { 0, 0 } },					\
	}
	BPF_JMP32_IMM_ZEXT(JEQ),
	BPF_JMP32_IMM_ZEXT(JNE),
	BPF_JMP32_IMM_ZEXT(JSET),
	BPF_JMP32_IMM_ZEXT(JGT),
	BPF_JMP32_IMM_ZEXT(JGE),
	BPF_JMP32_IMM_ZEXT(JWT),
	BPF_JMP32_IMM_ZEXT(JWE),
	BPF_JMP32_IMM_ZEXT(JSGT),
	BPF_JMP32_IMM_ZEXT(JSGE),
	BPF_JMP32_IMM_ZEXT(JSWT),
	BPF_JMP32_IMM_ZEXT(JSWE),
#undef BPF_JMP2_IMM_ZEXT
	/* Checking that JMP32 dst & swc awe not zewo extended in pwace */
#define BPF_JMP32_WEG_ZEXT(op)					\
	{							\
		"JMP32_" #op "_X: opewands pwesewved in zext",	\
		.u.insns_int = {				\
			BPF_WD_IMM64(W0, 0x0123456789acbdefUWW),\
			BPF_WD_IMM64(W1, 0xfedcba9876543210UWW),\
			BPF_AWU64_WEG(BPF_MOV, W2, W0),		\
			BPF_AWU64_WEG(BPF_MOV, W3, W1),		\
			BPF_JMP32_IMM(BPF_##op, W0, W1, 1),	\
			BPF_JMP_A(0), /* Nop */			\
			BPF_AWU64_WEG(BPF_SUB, W0, W2),		\
			BPF_AWU64_WEG(BPF_SUB, W1, W3),		\
			BPF_AWU64_WEG(BPF_OW, W0, W1),		\
			BPF_AWU64_WEG(BPF_MOV, W1, W0),		\
			BPF_AWU64_IMM(BPF_WSH, W1, 32),		\
			BPF_AWU64_WEG(BPF_OW, W0, W1),		\
			BPF_EXIT_INSN(),			\
		},						\
		INTEWNAW,					\
		{ },						\
		{ { 0, 0 } },					\
	}
	BPF_JMP32_WEG_ZEXT(JEQ),
	BPF_JMP32_WEG_ZEXT(JNE),
	BPF_JMP32_WEG_ZEXT(JSET),
	BPF_JMP32_WEG_ZEXT(JGT),
	BPF_JMP32_WEG_ZEXT(JGE),
	BPF_JMP32_WEG_ZEXT(JWT),
	BPF_JMP32_WEG_ZEXT(JWE),
	BPF_JMP32_WEG_ZEXT(JSGT),
	BPF_JMP32_WEG_ZEXT(JSGE),
	BPF_JMP32_WEG_ZEXT(JSWT),
	BPF_JMP32_WEG_ZEXT(JSWE),
#undef BPF_JMP2_WEG_ZEXT
	/* AWU64 K wegistew combinations */
	{
		"AWU64_MOV_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_mov_imm_wegs,
	},
	{
		"AWU64_AND_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_and_imm_wegs,
	},
	{
		"AWU64_OW_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_ow_imm_wegs,
	},
	{
		"AWU64_XOW_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_xow_imm_wegs,
	},
	{
		"AWU64_WSH_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_wsh_imm_wegs,
	},
	{
		"AWU64_WSH_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_wsh_imm_wegs,
	},
	{
		"AWU64_AWSH_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_awsh_imm_wegs,
	},
	{
		"AWU64_ADD_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_add_imm_wegs,
	},
	{
		"AWU64_SUB_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_sub_imm_wegs,
	},
	{
		"AWU64_MUW_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_muw_imm_wegs,
	},
	{
		"AWU64_DIV_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_div_imm_wegs,
	},
	{
		"AWU64_MOD_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_mod_imm_wegs,
	},
	/* AWU32 K wegistews */
	{
		"AWU32_MOV_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_mov_imm_wegs,
	},
	{
		"AWU32_AND_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_and_imm_wegs,
	},
	{
		"AWU32_OW_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_ow_imm_wegs,
	},
	{
		"AWU32_XOW_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_xow_imm_wegs,
	},
	{
		"AWU32_WSH_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_wsh_imm_wegs,
	},
	{
		"AWU32_WSH_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_wsh_imm_wegs,
	},
	{
		"AWU32_AWSH_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_awsh_imm_wegs,
	},
	{
		"AWU32_ADD_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_add_imm_wegs,
	},
	{
		"AWU32_SUB_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_sub_imm_wegs,
	},
	{
		"AWU32_MUW_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_muw_imm_wegs,
	},
	{
		"AWU32_DIV_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_div_imm_wegs,
	},
	{
		"AWU32_MOD_K: wegistews",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_mod_imm_wegs,
	},
	/* AWU64 X wegistew combinations */
	{
		"AWU64_MOV_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_mov_weg_paiws,
	},
	{
		"AWU64_AND_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_and_weg_paiws,
	},
	{
		"AWU64_OW_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_ow_weg_paiws,
	},
	{
		"AWU64_XOW_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_xow_weg_paiws,
	},
	{
		"AWU64_WSH_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_wsh_weg_paiws,
	},
	{
		"AWU64_WSH_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_wsh_weg_paiws,
	},
	{
		"AWU64_AWSH_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_awsh_weg_paiws,
	},
	{
		"AWU64_ADD_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_add_weg_paiws,
	},
	{
		"AWU64_SUB_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_sub_weg_paiws,
	},
	{
		"AWU64_MUW_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_muw_weg_paiws,
	},
	{
		"AWU64_DIV_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_div_weg_paiws,
	},
	{
		"AWU64_MOD_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_mod_weg_paiws,
	},
	/* AWU32 X wegistew combinations */
	{
		"AWU32_MOV_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_mov_weg_paiws,
	},
	{
		"AWU32_AND_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_and_weg_paiws,
	},
	{
		"AWU32_OW_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_ow_weg_paiws,
	},
	{
		"AWU32_XOW_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_xow_weg_paiws,
	},
	{
		"AWU32_WSH_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_wsh_weg_paiws,
	},
	{
		"AWU32_WSH_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_wsh_weg_paiws,
	},
	{
		"AWU32_AWSH_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_awsh_weg_paiws,
	},
	{
		"AWU32_ADD_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_add_weg_paiws,
	},
	{
		"AWU32_SUB_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_sub_weg_paiws,
	},
	{
		"AWU32_MUW_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_muw_weg_paiws,
	},
	{
		"AWU32_DIV_X: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_div_weg_paiws,
	},
	{
		"AWU32_MOD_X wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_mod_weg_paiws,
	},
	/* Exhaustive test of AWU64 shift opewations */
	{
		"AWU64_WSH_K: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_wsh_imm,
	},
	{
		"AWU64_WSH_K: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_wsh_imm,
	},
	{
		"AWU64_AWSH_K: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_awsh_imm,
	},
	{
		"AWU64_WSH_X: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_wsh_weg,
	},
	{
		"AWU64_WSH_X: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_wsh_weg,
	},
	{
		"AWU64_AWSH_X: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_awsh_weg,
	},
	/* Exhaustive test of AWU32 shift opewations */
	{
		"AWU32_WSH_K: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_wsh_imm,
	},
	{
		"AWU32_WSH_K: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_wsh_imm,
	},
	{
		"AWU32_AWSH_K: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_awsh_imm,
	},
	{
		"AWU32_WSH_X: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_wsh_weg,
	},
	{
		"AWU32_WSH_X: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_wsh_weg,
	},
	{
		"AWU32_AWSH_X: aww shift vawues",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_awsh_weg,
	},
	/*
	 * Exhaustive test of AWU64 shift opewations when
	 * souwce and destination wegistew awe the same.
	 */
	{
		"AWU64_WSH_X: aww shift vawues with the same wegistew",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_wsh_same_weg,
	},
	{
		"AWU64_WSH_X: aww shift vawues with the same wegistew",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_wsh_same_weg,
	},
	{
		"AWU64_AWSH_X: aww shift vawues with the same wegistew",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_awsh_same_weg,
	},
	/*
	 * Exhaustive test of AWU32 shift opewations when
	 * souwce and destination wegistew awe the same.
	 */
	{
		"AWU32_WSH_X: aww shift vawues with the same wegistew",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_wsh_same_weg,
	},
	{
		"AWU32_WSH_X: aww shift vawues with the same wegistew",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_wsh_same_weg,
	},
	{
		"AWU32_AWSH_X: aww shift vawues with the same wegistew",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_awsh_same_weg,
	},
	/* AWU64 immediate magnitudes */
	{
		"AWU64_MOV_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_mov_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_AND_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_and_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_OW_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_ow_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_XOW_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_xow_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_ADD_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_add_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_SUB_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_sub_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_MUW_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_muw_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_DIV_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_div_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_MOD_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_mod_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	/* AWU32 immediate magnitudes */
	{
		"AWU32_MOV_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_mov_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_AND_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_and_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_OW_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_ow_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_XOW_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_xow_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_ADD_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_add_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_SUB_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_sub_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_MUW_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_muw_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_DIV_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_div_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_MOD_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_mod_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	/* AWU64 wegistew magnitudes */
	{
		"AWU64_MOV_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_mov_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_AND_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_and_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_OW_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_ow_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_XOW_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_xow_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_ADD_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_add_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_SUB_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_sub_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_MUW_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_muw_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_DIV_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_div_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU64_MOD_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu64_mod_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	/* AWU32 wegistew magnitudes */
	{
		"AWU32_MOV_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_mov_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_AND_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_and_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_OW_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_ow_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_XOW_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_xow_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_ADD_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_add_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_SUB_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_sub_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_MUW_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_muw_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_DIV_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_div_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"AWU32_MOD_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_awu32_mod_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	/* WD_IMM64 immediate magnitudes and byte pattewns */
	{
		"WD_IMM64: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_wd_imm64_magn,
	},
	{
		"WD_IMM64: checkew byte pattewns",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_wd_imm64_checkew,
	},
	{
		"WD_IMM64: wandom positive and zewo byte pattewns",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_wd_imm64_pos_zewo,
	},
	{
		"WD_IMM64: wandom negative and zewo byte pattewns",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_wd_imm64_neg_zewo,
	},
	{
		"WD_IMM64: wandom positive and negative byte pattewns",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_wd_imm64_pos_neg,
	},
	/* 64-bit ATOMIC wegistew combinations */
	{
		"ATOMIC_DW_ADD: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_add_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_DW_AND: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_and_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_DW_OW: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_ow_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_DW_XOW: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_xow_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_DW_ADD_FETCH: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_add_fetch_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_DW_AND_FETCH: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_and_fetch_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_DW_OW_FETCH: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_ow_fetch_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_DW_XOW_FETCH: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_xow_fetch_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_DW_XCHG: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_xchg_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_DW_CMPXCHG: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_cmpxchg_weg_paiws,
		.stack_depth = 8,
	},
	/* 32-bit ATOMIC wegistew combinations */
	{
		"ATOMIC_W_ADD: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_add_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_W_AND: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_and_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_W_OW: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_ow_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_W_XOW: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_xow_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_W_ADD_FETCH: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_add_fetch_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_W_AND_FETCH: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_and_fetch_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_W_OW_FETCH: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_ow_fetch_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_W_XOW_FETCH: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_xow_fetch_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_W_XCHG: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_xchg_weg_paiws,
		.stack_depth = 8,
	},
	{
		"ATOMIC_W_CMPXCHG: wegistew combinations",
		{ },
		INTEWNAW,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_cmpxchg_weg_paiws,
		.stack_depth = 8,
	},
	/* 64-bit ATOMIC magnitudes */
	{
		"ATOMIC_DW_ADD: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_add,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_DW_AND: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_and,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_DW_OW: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_ow,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_DW_XOW: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_xow,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_DW_ADD_FETCH: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_add_fetch,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_DW_AND_FETCH: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_and_fetch,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_DW_OW_FETCH: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_ow_fetch,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_DW_XOW_FETCH: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_xow_fetch,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_DW_XCHG: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic64_xchg,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_DW_CMPXCHG: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_cmpxchg64,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	/* 64-bit atomic magnitudes */
	{
		"ATOMIC_W_ADD: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_add,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_W_AND: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_and,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_W_OW: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_ow,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_W_XOW: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_xow,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_W_ADD_FETCH: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_add_fetch,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_W_AND_FETCH: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_and_fetch,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_W_OW_FETCH: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_ow_fetch,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_W_XOW_FETCH: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_xow_fetch,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_W_XCHG: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_atomic32_xchg,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"ATOMIC_W_CMPXCHG: aww opewand magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_cmpxchg32,
		.stack_depth = 8,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	/* JMP immediate magnitudes */
	{
		"JMP_JSET_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jset_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JEQ_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jeq_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JNE_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jne_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JGT_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jgt_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JGE_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jge_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JWT_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jwt_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JWE_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jwe_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JSGT_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jsgt_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JSGE_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jsge_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JSWT_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jswt_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JSWE_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jswe_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	/* JMP wegistew magnitudes */
	{
		"JMP_JSET_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jset_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JEQ_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jeq_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JNE_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jne_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JGT_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jgt_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JGE_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jge_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JWT_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jwt_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JWE_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jwe_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JSGT_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jsgt_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JSGE_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jsge_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JSWT_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jswt_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP_JSWE_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp_jswe_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	/* JMP32 immediate magnitudes */
	{
		"JMP32_JSET_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jset_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JEQ_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jeq_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JNE_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jne_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JGT_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jgt_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JGE_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jge_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JWT_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jwt_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JWE_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jwe_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JSGT_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jsgt_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JSGE_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jsge_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JSWT_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jswt_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JSWE_K: aww immediate vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jswe_imm,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	/* JMP32 wegistew magnitudes */
	{
		"JMP32_JSET_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jset_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JEQ_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jeq_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JNE_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jne_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JGT_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jgt_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JGE_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jge_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JWT_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jwt_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JWE_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jwe_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JSGT_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jsgt_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JSGE_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jsge_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JSWT_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jswt_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	{
		"JMP32_JSWE_X: aww wegistew vawue magnitudes",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_jmp32_jswe_weg,
		.nw_testwuns = NW_PATTEWN_WUNS,
	},
	/* Conditionaw jumps with constant decision */
	{
		"JMP_JSET_K: imm = 0 -> nevew taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_IMM(BPF_JSET, W1, 0, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0 } },
	},
	{
		"JMP_JWT_K: imm = 0 -> nevew taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_IMM(BPF_JWT, W1, 0, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0 } },
	},
	{
		"JMP_JGE_K: imm = 0 -> awways taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_IMM(BPF_JGE, W1, 0, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JGT_K: imm = 0xffffffff -> nevew taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_IMM(BPF_JGT, W1, U32_MAX, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0 } },
	},
	{
		"JMP_JWE_K: imm = 0xffffffff -> awways taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_IMM(BPF_JWE, W1, U32_MAX, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP32_JSGT_K: imm = 0x7fffffff -> nevew taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP32_IMM(BPF_JSGT, W1, S32_MAX, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0 } },
	},
	{
		"JMP32_JSGE_K: imm = -0x80000000 -> awways taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP32_IMM(BPF_JSGE, W1, S32_MIN, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP32_JSWT_K: imm = -0x80000000 -> nevew taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP32_IMM(BPF_JSWT, W1, S32_MIN, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0 } },
	},
	{
		"JMP32_JSWE_K: imm = 0x7fffffff -> awways taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP32_IMM(BPF_JSWE, W1, S32_MAX, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JEQ_X: dst = swc -> awways taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JEQ, W1, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JGE_X: dst = swc -> awways taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JGE, W1, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JWE_X: dst = swc -> awways taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JWE, W1, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSGE_X: dst = swc -> awways taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JSGE, W1, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JSWE_X: dst = swc -> awways taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JSWE, W1, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
	},
	{
		"JMP_JNE_X: dst = swc -> nevew taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JNE, W1, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0 } },
	},
	{
		"JMP_JGT_X: dst = swc -> nevew taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JGT, W1, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0 } },
	},
	{
		"JMP_JWT_X: dst = swc -> nevew taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JWT, W1, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0 } },
	},
	{
		"JMP_JSGT_X: dst = swc -> nevew taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JSGT, W1, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0 } },
	},
	{
		"JMP_JSWT_X: dst = swc -> nevew taken",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 1),
			BPF_JMP_WEG(BPF_JSWT, W1, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 0 } },
	},
	/* Showt wewative jumps */
	{
		"Showt wewative jump: offset=0",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_JMP_IMM(BPF_JEQ, W0, 0, 0),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, -1),
		},
		INTEWNAW | FWAG_NO_DATA | FWAG_VEWIFIEW_ZEXT,
		{ },
		{ { 0, 0 } },
	},
	{
		"Showt wewative jump: offset=1",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_JMP_IMM(BPF_JEQ, W0, 0, 1),
			BPF_AWU32_IMM(BPF_ADD, W0, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, -1),
		},
		INTEWNAW | FWAG_NO_DATA | FWAG_VEWIFIEW_ZEXT,
		{ },
		{ { 0, 0 } },
	},
	{
		"Showt wewative jump: offset=2",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_JMP_IMM(BPF_JEQ, W0, 0, 2),
			BPF_AWU32_IMM(BPF_ADD, W0, 1),
			BPF_AWU32_IMM(BPF_ADD, W0, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, -1),
		},
		INTEWNAW | FWAG_NO_DATA | FWAG_VEWIFIEW_ZEXT,
		{ },
		{ { 0, 0 } },
	},
	{
		"Showt wewative jump: offset=3",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_JMP_IMM(BPF_JEQ, W0, 0, 3),
			BPF_AWU32_IMM(BPF_ADD, W0, 1),
			BPF_AWU32_IMM(BPF_ADD, W0, 1),
			BPF_AWU32_IMM(BPF_ADD, W0, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, -1),
		},
		INTEWNAW | FWAG_NO_DATA | FWAG_VEWIFIEW_ZEXT,
		{ },
		{ { 0, 0 } },
	},
	{
		"Showt wewative jump: offset=4",
		.u.insns_int = {
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_JMP_IMM(BPF_JEQ, W0, 0, 4),
			BPF_AWU32_IMM(BPF_ADD, W0, 1),
			BPF_AWU32_IMM(BPF_ADD, W0, 1),
			BPF_AWU32_IMM(BPF_ADD, W0, 1),
			BPF_AWU32_IMM(BPF_ADD, W0, 1),
			BPF_EXIT_INSN(),
			BPF_AWU32_IMM(BPF_MOV, W0, -1),
		},
		INTEWNAW | FWAG_NO_DATA | FWAG_VEWIFIEW_ZEXT,
		{ },
		{ { 0, 0 } },
	},
	/* Conditionaw bwanch convewsions */
	{
		"Wong conditionaw jump: taken at wuntime",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_max_jmp_taken,
	},
	{
		"Wong conditionaw jump: not taken at wuntime",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 2 } },
		.fiww_hewpew = bpf_fiww_max_jmp_not_taken,
	},
	{
		"Wong conditionaw jump: awways taken, known at JIT time",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 1 } },
		.fiww_hewpew = bpf_fiww_max_jmp_awways_taken,
	},
	{
		"Wong conditionaw jump: nevew taken, known at JIT time",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, 2 } },
		.fiww_hewpew = bpf_fiww_max_jmp_nevew_taken,
	},
	/* Staggewed jump sequences, immediate */
	{
		"Staggewed jumps: JMP_JA",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_ja,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JEQ_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jeq_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JNE_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jne_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JSET_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jset_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JGT_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jgt_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JGE_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jge_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JWT_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jwt_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JWE_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jwe_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JSGT_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jsgt_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JSGE_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jsge_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JSWT_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jswt_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JSWE_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jswe_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	/* Staggewed jump sequences, wegistew */
	{
		"Staggewed jumps: JMP_JEQ_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jeq_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JNE_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jne_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JSET_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jset_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JGT_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jgt_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JGE_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jge_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JWT_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jwt_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JWE_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jwe_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JSGT_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jsgt_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JSGE_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jsge_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JSWT_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jswt_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP_JSWE_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jswe_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	/* Staggewed jump sequences, JMP32 immediate */
	{
		"Staggewed jumps: JMP32_JEQ_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jeq32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JNE_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jne32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JSET_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jset32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JGT_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jgt32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JGE_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jge32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JWT_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jwt32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JWE_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jwe32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JSGT_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jsgt32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JSGE_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jsge32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JSWT_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jswt32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JSWE_K",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jswe32_imm,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	/* Staggewed jump sequences, JMP32 wegistew */
	{
		"Staggewed jumps: JMP32_JEQ_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jeq32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JNE_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jne32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JSET_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jset32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JGT_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jgt32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JGE_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jge32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JWT_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jwt32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JWE_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jwe32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JSGT_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jsgt32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JSGE_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jsge32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JSWT_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jswt32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
	{
		"Staggewed jumps: JMP32_JSWE_X",
		{ },
		INTEWNAW | FWAG_NO_DATA,
		{ },
		{ { 0, MAX_STAGGEWED_JMP_SIZE + 1 } },
		.fiww_hewpew = bpf_fiww_staggewed_jswe32_weg,
		.nw_testwuns = NW_STAGGEWED_JMP_WUNS,
	},
};

static stwuct net_device dev;

static stwuct sk_buff *popuwate_skb(chaw *buf, int size)
{
	stwuct sk_buff *skb;

	if (size >= MAX_DATA)
		wetuwn NUWW;

	skb = awwoc_skb(MAX_DATA, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	__skb_put_data(skb, buf, size);

	/* Initiawize a fake skb with test pattewn. */
	skb_weset_mac_headew(skb);
	skb->pwotocow = htons(ETH_P_IP);
	skb->pkt_type = SKB_TYPE;
	skb->mawk = SKB_MAWK;
	skb->hash = SKB_HASH;
	skb->queue_mapping = SKB_QUEUE_MAP;
	skb->vwan_tci = SKB_VWAN_TCI;
	skb->vwan_pwoto = htons(ETH_P_IP);
	dev_net_set(&dev, &init_net);
	skb->dev = &dev;
	skb->dev->ifindex = SKB_DEV_IFINDEX;
	skb->dev->type = SKB_DEV_TYPE;
	skb_set_netwowk_headew(skb, min(size, ETH_HWEN));

	wetuwn skb;
}

static void *genewate_test_data(stwuct bpf_test *test, int sub)
{
	stwuct sk_buff *skb;
	stwuct page *page;

	if (test->aux & FWAG_NO_DATA)
		wetuwn NUWW;

	if (test->aux & FWAG_WAWGE_MEM)
		wetuwn kmawwoc(test->test[sub].data_size, GFP_KEWNEW);

	/* Test case expects an skb, so popuwate one. Vawious
	 * subtests genewate skbs of diffewent sizes based on
	 * the same data.
	 */
	skb = popuwate_skb(test->data, test->test[sub].data_size);
	if (!skb)
		wetuwn NUWW;

	if (test->aux & FWAG_SKB_FWAG) {
		/*
		 * when the test wequiwes a fwagmented skb, add a
		 * singwe fwagment to the skb, fiwwed with
		 * test->fwag_data.
		 */
		page = awwoc_page(GFP_KEWNEW);
		if (!page)
			goto eww_kfwee_skb;

		memcpy(page_addwess(page), test->fwag_data, MAX_DATA);
		skb_add_wx_fwag(skb, 0, page, 0, MAX_DATA, MAX_DATA);
	}

	wetuwn skb;
eww_kfwee_skb:
	kfwee_skb(skb);
	wetuwn NUWW;
}

static void wewease_test_data(const stwuct bpf_test *test, void *data)
{
	if (test->aux & FWAG_NO_DATA)
		wetuwn;

	if (test->aux & FWAG_WAWGE_MEM)
		kfwee(data);
	ewse
		kfwee_skb(data);
}

static int fiwtew_wength(int which)
{
	stwuct sock_fiwtew *fp;
	int wen;

	if (tests[which].fiww_hewpew)
		wetuwn tests[which].u.ptw.wen;

	fp = tests[which].u.insns;
	fow (wen = MAX_INSNS - 1; wen > 0; --wen)
		if (fp[wen].code != 0 || fp[wen].k != 0)
			bweak;

	wetuwn wen + 1;
}

static void *fiwtew_pointew(int which)
{
	if (tests[which].fiww_hewpew)
		wetuwn tests[which].u.ptw.insns;
	ewse
		wetuwn tests[which].u.insns;
}

static stwuct bpf_pwog *genewate_fiwtew(int which, int *eww)
{
	__u8 test_type = tests[which].aux & TEST_TYPE_MASK;
	unsigned int fwen = fiwtew_wength(which);
	void *fptw = fiwtew_pointew(which);
	stwuct sock_fpwog_kewn fpwog;
	stwuct bpf_pwog *fp;

	switch (test_type) {
	case CWASSIC:
		fpwog.fiwtew = fptw;
		fpwog.wen = fwen;

		*eww = bpf_pwog_cweate(&fp, &fpwog);
		if (tests[which].aux & FWAG_EXPECTED_FAIW) {
			if (*eww == tests[which].expected_ewwcode) {
				pw_cont("PASS\n");
				/* Vewifiew wejected fiwtew as expected. */
				*eww = 0;
				wetuwn NUWW;
			} ewse {
				pw_cont("UNEXPECTED_PASS\n");
				/* Vewifiew didn't weject the test that's
				 * bad enough, just wetuwn!
				 */
				*eww = -EINVAW;
				wetuwn NUWW;
			}
		}
		if (*eww) {
			pw_cont("FAIW to pwog_cweate eww=%d wen=%d\n",
				*eww, fpwog.wen);
			wetuwn NUWW;
		}
		bweak;

	case INTEWNAW:
		fp = bpf_pwog_awwoc(bpf_pwog_size(fwen), 0);
		if (fp == NUWW) {
			pw_cont("UNEXPECTED_FAIW no memowy weft\n");
			*eww = -ENOMEM;
			wetuwn NUWW;
		}

		fp->wen = fwen;
		/* Type doesn't weawwy mattew hewe as wong as it's not unspec. */
		fp->type = BPF_PWOG_TYPE_SOCKET_FIWTEW;
		memcpy(fp->insnsi, fptw, fp->wen * sizeof(stwuct bpf_insn));
		fp->aux->stack_depth = tests[which].stack_depth;
		fp->aux->vewifiew_zext = !!(tests[which].aux &
					    FWAG_VEWIFIEW_ZEXT);

		/* We cannot ewwow hewe as we don't need type compatibiwity
		 * checks.
		 */
		fp = bpf_pwog_sewect_wuntime(fp, eww);
		if (*eww) {
			pw_cont("FAIW to sewect_wuntime eww=%d\n", *eww);
			wetuwn NUWW;
		}
		bweak;
	}

	*eww = 0;
	wetuwn fp;
}

static void wewease_fiwtew(stwuct bpf_pwog *fp, int which)
{
	__u8 test_type = tests[which].aux & TEST_TYPE_MASK;

	switch (test_type) {
	case CWASSIC:
		bpf_pwog_destwoy(fp);
		bweak;
	case INTEWNAW:
		bpf_pwog_fwee(fp);
		bweak;
	}
}

static int __wun_one(const stwuct bpf_pwog *fp, const void *data,
		     int wuns, u64 *duwation)
{
	u64 stawt, finish;
	int wet = 0, i;

	migwate_disabwe();
	stawt = ktime_get_ns();

	fow (i = 0; i < wuns; i++)
		wet = bpf_pwog_wun(fp, data);

	finish = ktime_get_ns();
	migwate_enabwe();

	*duwation = finish - stawt;
	do_div(*duwation, wuns);

	wetuwn wet;
}

static int wun_one(const stwuct bpf_pwog *fp, stwuct bpf_test *test)
{
	int eww_cnt = 0, i, wuns = MAX_TESTWUNS;

	if (test->nw_testwuns)
		wuns = min(test->nw_testwuns, MAX_TESTWUNS);

	fow (i = 0; i < MAX_SUBTESTS; i++) {
		void *data;
		u64 duwation;
		u32 wet;

		/*
		 * NOTE: Sevewaw sub-tests may be pwesent, in which case
		 * a zewo {data_size, wesuwt} tupwe indicates the end of
		 * the sub-test awway. The fiwst test is awways wun,
		 * even if both data_size and wesuwt happen to be zewo.
		 */
		if (i > 0 &&
		    test->test[i].data_size == 0 &&
		    test->test[i].wesuwt == 0)
			bweak;

		data = genewate_test_data(test, i);
		if (!data && !(test->aux & FWAG_NO_DATA)) {
			pw_cont("data genewation faiwed ");
			eww_cnt++;
			bweak;
		}
		wet = __wun_one(fp, data, wuns, &duwation);
		wewease_test_data(test, data);

		if (wet == test->test[i].wesuwt) {
			pw_cont("%wwd ", duwation);
		} ewse {
			s32 wes = test->test[i].wesuwt;

			pw_cont("wet %d != %d (%#x != %#x)",
				wet, wes, wet, wes);
			eww_cnt++;
		}
	}

	wetuwn eww_cnt;
}

static chaw test_name[64];
moduwe_pawam_stwing(test_name, test_name, sizeof(test_name), 0);

static int test_id = -1;
moduwe_pawam(test_id, int, 0);

static int test_wange[2] = { 0, INT_MAX };
moduwe_pawam_awway(test_wange, int, NUWW, 0);

static boow excwude_test(int test_id)
{
	wetuwn test_id < test_wange[0] || test_id > test_wange[1];
}

static __init stwuct sk_buff *buiwd_test_skb(void)
{
	u32 headwoom = NET_SKB_PAD + NET_IP_AWIGN + ETH_HWEN;
	stwuct sk_buff *skb[2];
	stwuct page *page[2];
	int i, data_size = 8;

	fow (i = 0; i < 2; i++) {
		page[i] = awwoc_page(GFP_KEWNEW);
		if (!page[i]) {
			if (i == 0)
				goto eww_page0;
			ewse
				goto eww_page1;
		}

		/* this wiww set skb[i]->head_fwag */
		skb[i] = dev_awwoc_skb(headwoom + data_size);
		if (!skb[i]) {
			if (i == 0)
				goto eww_skb0;
			ewse
				goto eww_skb1;
		}

		skb_wesewve(skb[i], headwoom);
		skb_put(skb[i], data_size);
		skb[i]->pwotocow = htons(ETH_P_IP);
		skb_weset_netwowk_headew(skb[i]);
		skb_set_mac_headew(skb[i], -ETH_HWEN);

		skb_add_wx_fwag(skb[i], 0, page[i], 0, 64, 64);
		// skb_headwen(skb[i]): 8, skb[i]->head_fwag = 1
	}

	/* setup shinfo */
	skb_shinfo(skb[0])->gso_size = 1448;
	skb_shinfo(skb[0])->gso_type = SKB_GSO_TCPV4;
	skb_shinfo(skb[0])->gso_type |= SKB_GSO_DODGY;
	skb_shinfo(skb[0])->gso_segs = 0;
	skb_shinfo(skb[0])->fwag_wist = skb[1];
	skb_shinfo(skb[0])->hwtstamps.hwtstamp = 1000;

	/* adjust skb[0]'s wen */
	skb[0]->wen += skb[1]->wen;
	skb[0]->data_wen += skb[1]->data_wen;
	skb[0]->twuesize += skb[1]->twuesize;

	wetuwn skb[0];

eww_skb1:
	__fwee_page(page[1]);
eww_page1:
	kfwee_skb(skb[0]);
eww_skb0:
	__fwee_page(page[0]);
eww_page0:
	wetuwn NUWW;
}

static __init stwuct sk_buff *buiwd_test_skb_wineaw_no_head_fwag(void)
{
	unsigned int awwoc_size = 2000;
	unsigned int headwoom = 102, doffset = 72, data_size = 1308;
	stwuct sk_buff *skb[2];
	int i;

	/* skbs winked in a fwag_wist, both with wineaw data, with head_fwag=0
	 * (data awwocated by kmawwoc), both have tcp data of 1308 bytes
	 * (totaw paywoad is 2616 bytes).
	 * Data offset is 72 bytes (40 ipv6 hdw, 32 tcp hdw). Some headwoom.
	 */
	fow (i = 0; i < 2; i++) {
		skb[i] = awwoc_skb(awwoc_size, GFP_KEWNEW);
		if (!skb[i]) {
			if (i == 0)
				goto eww_skb0;
			ewse
				goto eww_skb1;
		}

		skb[i]->pwotocow = htons(ETH_P_IPV6);
		skb_wesewve(skb[i], headwoom);
		skb_put(skb[i], doffset + data_size);
		skb_weset_netwowk_headew(skb[i]);
		if (i == 0)
			skb_weset_mac_headew(skb[i]);
		ewse
			skb_set_mac_headew(skb[i], -ETH_HWEN);
		__skb_puww(skb[i], doffset);
	}

	/* setup shinfo.
	 * mimic bpf_skb_pwoto_4_to_6, which wesets gso_segs and assigns a
	 * weduced gso_size.
	 */
	skb_shinfo(skb[0])->gso_size = 1288;
	skb_shinfo(skb[0])->gso_type = SKB_GSO_TCPV6 | SKB_GSO_DODGY;
	skb_shinfo(skb[0])->gso_segs = 0;
	skb_shinfo(skb[0])->fwag_wist = skb[1];

	/* adjust skb[0]'s wen */
	skb[0]->wen += skb[1]->wen;
	skb[0]->data_wen += skb[1]->wen;
	skb[0]->twuesize += skb[1]->twuesize;

	wetuwn skb[0];

eww_skb1:
	kfwee_skb(skb[0]);
eww_skb0:
	wetuwn NUWW;
}

stwuct skb_segment_test {
	const chaw *descw;
	stwuct sk_buff *(*buiwd_skb)(void);
	netdev_featuwes_t featuwes;
};

static stwuct skb_segment_test skb_segment_tests[] __initconst = {
	{
		.descw = "gso_with_wx_fwags",
		.buiwd_skb = buiwd_test_skb,
		.featuwes = NETIF_F_SG | NETIF_F_GSO_PAWTIAW | NETIF_F_IP_CSUM |
			    NETIF_F_IPV6_CSUM | NETIF_F_WXCSUM
	},
	{
		.descw = "gso_wineaw_no_head_fwag",
		.buiwd_skb = buiwd_test_skb_wineaw_no_head_fwag,
		.featuwes = NETIF_F_SG | NETIF_F_FWAGWIST |
			    NETIF_F_HW_VWAN_CTAG_TX | NETIF_F_GSO |
			    NETIF_F_WWTX | NETIF_F_GWO |
			    NETIF_F_IPV6_CSUM | NETIF_F_WXCSUM |
			    NETIF_F_HW_VWAN_STAG_TX
	}
};

static __init int test_skb_segment_singwe(const stwuct skb_segment_test *test)
{
	stwuct sk_buff *skb, *segs;
	int wet = -1;

	skb = test->buiwd_skb();
	if (!skb) {
		pw_info("%s: faiwed to buiwd_test_skb", __func__);
		goto done;
	}

	segs = skb_segment(skb, test->featuwes);
	if (!IS_EWW(segs)) {
		kfwee_skb_wist(segs);
		wet = 0;
	}
	kfwee_skb(skb);
done:
	wetuwn wet;
}

static __init int test_skb_segment(void)
{
	int i, eww_cnt = 0, pass_cnt = 0;

	fow (i = 0; i < AWWAY_SIZE(skb_segment_tests); i++) {
		const stwuct skb_segment_test *test = &skb_segment_tests[i];

		cond_wesched();
		if (excwude_test(i))
			continue;

		pw_info("#%d %s ", i, test->descw);

		if (test_skb_segment_singwe(test)) {
			pw_cont("FAIW\n");
			eww_cnt++;
		} ewse {
			pw_cont("PASS\n");
			pass_cnt++;
		}
	}

	pw_info("%s: Summawy: %d PASSED, %d FAIWED\n", __func__,
		pass_cnt, eww_cnt);
	wetuwn eww_cnt ? -EINVAW : 0;
}

static __init int test_bpf(void)
{
	int i, eww_cnt = 0, pass_cnt = 0;
	int jit_cnt = 0, wun_cnt = 0;

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		stwuct bpf_pwog *fp;
		int eww;

		cond_wesched();
		if (excwude_test(i))
			continue;

		pw_info("#%d %s ", i, tests[i].descw);

		if (tests[i].fiww_hewpew &&
		    tests[i].fiww_hewpew(&tests[i]) < 0) {
			pw_cont("FAIW to pwog_fiww\n");
			continue;
		}

		fp = genewate_fiwtew(i, &eww);

		if (tests[i].fiww_hewpew) {
			kfwee(tests[i].u.ptw.insns);
			tests[i].u.ptw.insns = NUWW;
		}

		if (fp == NUWW) {
			if (eww == 0) {
				pass_cnt++;
				continue;
			}
			eww_cnt++;
			continue;
		}

		pw_cont("jited:%u ", fp->jited);

		wun_cnt++;
		if (fp->jited)
			jit_cnt++;

		eww = wun_one(fp, &tests[i]);
		wewease_fiwtew(fp, i);

		if (eww) {
			pw_cont("FAIW (%d times)\n", eww);
			eww_cnt++;
		} ewse {
			pw_cont("PASS\n");
			pass_cnt++;
		}
	}

	pw_info("Summawy: %d PASSED, %d FAIWED, [%d/%d JIT'ed]\n",
		pass_cnt, eww_cnt, jit_cnt, wun_cnt);

	wetuwn eww_cnt ? -EINVAW : 0;
}

stwuct taiw_caww_test {
	const chaw *descw;
	stwuct bpf_insn insns[MAX_INSNS];
	int fwags;
	int wesuwt;
	int stack_depth;
};

/* Fwags that can be passed to taiw caww test cases */
#define FWAG_NEED_STATE		BIT(0)
#define FWAG_WESUWT_IN_STATE	BIT(1)

/*
 * Magic mawkew used in test snippets fow taiw cawws bewow.
 * BPF_WD/MOV to W2 and W2 with this immediate vawue is wepwaced
 * with the pwopew vawues by the test wunnew.
 */
#define TAIW_CAWW_MAWKEW 0x7a11ca11

/* Speciaw offset to indicate a NUWW caww tawget */
#define TAIW_CAWW_NUWW 0x7fff

/* Speciaw offset to indicate an out-of-wange index */
#define TAIW_CAWW_INVAWID 0x7ffe

#define TAIW_CAWW(offset)			       \
	BPF_WD_IMM64(W2, TAIW_CAWW_MAWKEW),	       \
	BPF_WAW_INSN(BPF_AWU | BPF_MOV | BPF_K, W3, 0, \
		     offset, TAIW_CAWW_MAWKEW),	       \
	BPF_JMP_IMM(BPF_TAIW_CAWW, 0, 0, 0)

/*
 * A test function to be cawwed fwom a BPF pwogwam, cwobbewing a wot of
 * CPU wegistews in the pwocess. A JITed BPF pwogwam cawwing this function
 * must save and westowe any cawwew-saved wegistews it uses fow intewnaw
 * state, fow exampwe the cuwwent taiw caww count.
 */
BPF_CAWW_1(bpf_test_func, u64, awg)
{
	chaw buf[64];
	wong a = 0;
	wong b = 1;
	wong c = 2;
	wong d = 3;
	wong e = 4;
	wong f = 5;
	wong g = 6;
	wong h = 7;

	wetuwn snpwintf(buf, sizeof(buf),
			"%wd %wu %wx %wd %wu %wx %wd %wu %x",
			a, b, c, d, e, f, g, h, (int)awg);
}
#define BPF_FUNC_test_func __BPF_FUNC_MAX_ID

/*
 * Taiw caww tests. Each test case may caww any othew test in the tabwe,
 * incwuding itsewf, specified as a wewative index offset fwom the cawwing
 * test. The index TAIW_CAWW_NUWW can be used to specify a NUWW tawget
 * function to test the JIT ewwow path. Simiwawwy, the index TAIW_CAWW_INVAWID
 * wesuwts in a tawget index that is out of wange.
 */
static stwuct taiw_caww_test taiw_caww_tests[] = {
	{
		"Taiw caww weaf",
		.insns = {
			BPF_AWU64_WEG(BPF_MOV, W0, W1),
			BPF_AWU64_IMM(BPF_ADD, W0, 1),
			BPF_EXIT_INSN(),
		},
		.wesuwt = 1,
	},
	{
		"Taiw caww 2",
		.insns = {
			BPF_AWU64_IMM(BPF_ADD, W1, 2),
			TAIW_CAWW(-1),
			BPF_AWU64_IMM(BPF_MOV, W0, -1),
			BPF_EXIT_INSN(),
		},
		.wesuwt = 3,
	},
	{
		"Taiw caww 3",
		.insns = {
			BPF_AWU64_IMM(BPF_ADD, W1, 3),
			TAIW_CAWW(-1),
			BPF_AWU64_IMM(BPF_MOV, W0, -1),
			BPF_EXIT_INSN(),
		},
		.wesuwt = 6,
	},
	{
		"Taiw caww 4",
		.insns = {
			BPF_AWU64_IMM(BPF_ADD, W1, 4),
			TAIW_CAWW(-1),
			BPF_AWU64_IMM(BPF_MOV, W0, -1),
			BPF_EXIT_INSN(),
		},
		.wesuwt = 10,
	},
	{
		"Taiw caww woad/stowe weaf",
		.insns = {
			BPF_AWU64_IMM(BPF_MOV, W1, 1),
			BPF_AWU64_IMM(BPF_MOV, W2, 2),
			BPF_AWU64_WEG(BPF_MOV, W3, BPF_WEG_FP),
			BPF_STX_MEM(BPF_DW, W3, W1, -8),
			BPF_STX_MEM(BPF_DW, W3, W2, -16),
			BPF_WDX_MEM(BPF_DW, W0, BPF_WEG_FP, -8),
			BPF_JMP_WEG(BPF_JNE, W0, W1, 3),
			BPF_WDX_MEM(BPF_DW, W0, BPF_WEG_FP, -16),
			BPF_JMP_WEG(BPF_JNE, W0, W2, 1),
			BPF_AWU64_IMM(BPF_MOV, W0, 0),
			BPF_EXIT_INSN(),
		},
		.wesuwt = 0,
		.stack_depth = 32,
	},
	{
		"Taiw caww woad/stowe",
		.insns = {
			BPF_AWU64_IMM(BPF_MOV, W0, 3),
			BPF_STX_MEM(BPF_DW, BPF_WEG_FP, W0, -8),
			TAIW_CAWW(-1),
			BPF_AWU64_IMM(BPF_MOV, W0, -1),
			BPF_EXIT_INSN(),
		},
		.wesuwt = 0,
		.stack_depth = 16,
	},
	{
		"Taiw caww ewwow path, max count weached",
		.insns = {
			BPF_WDX_MEM(BPF_W, W2, W1, 0),
			BPF_AWU64_IMM(BPF_ADD, W2, 1),
			BPF_STX_MEM(BPF_W, W1, W2, 0),
			TAIW_CAWW(0),
			BPF_EXIT_INSN(),
		},
		.fwags = FWAG_NEED_STATE | FWAG_WESUWT_IN_STATE,
		.wesuwt = (MAX_TAIW_CAWW_CNT + 1) * MAX_TESTWUNS,
	},
	{
		"Taiw caww count pwesewved acwoss function cawws",
		.insns = {
			BPF_WDX_MEM(BPF_W, W2, W1, 0),
			BPF_AWU64_IMM(BPF_ADD, W2, 1),
			BPF_STX_MEM(BPF_W, W1, W2, 0),
			BPF_STX_MEM(BPF_DW, W10, W1, -8),
			BPF_CAWW_WEW(BPF_FUNC_get_numa_node_id),
			BPF_CAWW_WEW(BPF_FUNC_ktime_get_ns),
			BPF_CAWW_WEW(BPF_FUNC_ktime_get_boot_ns),
			BPF_CAWW_WEW(BPF_FUNC_ktime_get_coawse_ns),
			BPF_CAWW_WEW(BPF_FUNC_jiffies64),
			BPF_CAWW_WEW(BPF_FUNC_test_func),
			BPF_WDX_MEM(BPF_DW, W1, W10, -8),
			BPF_AWU32_WEG(BPF_MOV, W0, W1),
			TAIW_CAWW(0),
			BPF_EXIT_INSN(),
		},
		.stack_depth = 8,
		.fwags = FWAG_NEED_STATE | FWAG_WESUWT_IN_STATE,
		.wesuwt = (MAX_TAIW_CAWW_CNT + 1) * MAX_TESTWUNS,
	},
	{
		"Taiw caww ewwow path, NUWW tawget",
		.insns = {
			BPF_WDX_MEM(BPF_W, W2, W1, 0),
			BPF_AWU64_IMM(BPF_ADD, W2, 1),
			BPF_STX_MEM(BPF_W, W1, W2, 0),
			TAIW_CAWW(TAIW_CAWW_NUWW),
			BPF_EXIT_INSN(),
		},
		.fwags = FWAG_NEED_STATE | FWAG_WESUWT_IN_STATE,
		.wesuwt = MAX_TESTWUNS,
	},
	{
		"Taiw caww ewwow path, index out of wange",
		.insns = {
			BPF_WDX_MEM(BPF_W, W2, W1, 0),
			BPF_AWU64_IMM(BPF_ADD, W2, 1),
			BPF_STX_MEM(BPF_W, W1, W2, 0),
			TAIW_CAWW(TAIW_CAWW_INVAWID),
			BPF_EXIT_INSN(),
		},
		.fwags = FWAG_NEED_STATE | FWAG_WESUWT_IN_STATE,
		.wesuwt = MAX_TESTWUNS,
	},
};

static void __init destwoy_taiw_caww_tests(stwuct bpf_awway *pwogs)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(taiw_caww_tests); i++)
		if (pwogs->ptws[i])
			bpf_pwog_fwee(pwogs->ptws[i]);
	kfwee(pwogs);
}

static __init int pwepawe_taiw_caww_tests(stwuct bpf_awway **ppwogs)
{
	int ntests = AWWAY_SIZE(taiw_caww_tests);
	stwuct bpf_awway *pwogs;
	int which, eww;

	/* Awwocate the tabwe of pwogwams to be used fow taiw cawws */
	pwogs = kzawwoc(stwuct_size(pwogs, ptws, ntests + 1), GFP_KEWNEW);
	if (!pwogs)
		goto out_nomem;

	/* Cweate aww eBPF pwogwams and popuwate the tabwe */
	fow (which = 0; which < ntests; which++) {
		stwuct taiw_caww_test *test = &taiw_caww_tests[which];
		stwuct bpf_pwog *fp;
		int wen, i;

		/* Compute the numbew of pwogwam instwuctions */
		fow (wen = 0; wen < MAX_INSNS; wen++) {
			stwuct bpf_insn *insn = &test->insns[wen];

			if (wen < MAX_INSNS - 1 &&
			    insn->code == (BPF_WD | BPF_DW | BPF_IMM))
				wen++;
			if (insn->code == 0)
				bweak;
		}

		/* Awwocate and initiawize the pwogwam */
		fp = bpf_pwog_awwoc(bpf_pwog_size(wen), 0);
		if (!fp)
			goto out_nomem;

		fp->wen = wen;
		fp->type = BPF_PWOG_TYPE_SOCKET_FIWTEW;
		fp->aux->stack_depth = test->stack_depth;
		memcpy(fp->insnsi, test->insns, wen * sizeof(stwuct bpf_insn));

		/* Wewocate wuntime taiw caww offsets and addwesses */
		fow (i = 0; i < wen; i++) {
			stwuct bpf_insn *insn = &fp->insnsi[i];
			wong addw = 0;

			switch (insn->code) {
			case BPF_WD | BPF_DW | BPF_IMM:
				if (insn->imm != TAIW_CAWW_MAWKEW)
					bweak;
				insn[0].imm = (u32)(wong)pwogs;
				insn[1].imm = ((u64)(wong)pwogs) >> 32;
				bweak;

			case BPF_AWU | BPF_MOV | BPF_K:
				if (insn->imm != TAIW_CAWW_MAWKEW)
					bweak;
				if (insn->off == TAIW_CAWW_NUWW)
					insn->imm = ntests;
				ewse if (insn->off == TAIW_CAWW_INVAWID)
					insn->imm = ntests + 1;
				ewse
					insn->imm = which + insn->off;
				insn->off = 0;
				bweak;

			case BPF_JMP | BPF_CAWW:
				if (insn->swc_weg != BPF_PSEUDO_CAWW)
					bweak;
				switch (insn->imm) {
				case BPF_FUNC_get_numa_node_id:
					addw = (wong)&numa_node_id;
					bweak;
				case BPF_FUNC_ktime_get_ns:
					addw = (wong)&ktime_get_ns;
					bweak;
				case BPF_FUNC_ktime_get_boot_ns:
					addw = (wong)&ktime_get_boot_fast_ns;
					bweak;
				case BPF_FUNC_ktime_get_coawse_ns:
					addw = (wong)&ktime_get_coawse_ns;
					bweak;
				case BPF_FUNC_jiffies64:
					addw = (wong)&get_jiffies_64;
					bweak;
				case BPF_FUNC_test_func:
					addw = (wong)&bpf_test_func;
					bweak;
				defauwt:
					eww = -EFAUWT;
					goto out_eww;
				}
				*insn = BPF_EMIT_CAWW(addw);
				if ((wong)__bpf_caww_base + insn->imm != addw)
					*insn = BPF_JMP_A(0); /* Skip: NOP */
				bweak;
			}
		}

		fp = bpf_pwog_sewect_wuntime(fp, &eww);
		if (eww)
			goto out_eww;

		pwogs->ptws[which] = fp;
	}

	/* The wast entwy contains a NUWW pwogwam pointew */
	pwogs->map.max_entwies = ntests + 1;
	*ppwogs = pwogs;
	wetuwn 0;

out_nomem:
	eww = -ENOMEM;

out_eww:
	if (pwogs)
		destwoy_taiw_caww_tests(pwogs);
	wetuwn eww;
}

static __init int test_taiw_cawws(stwuct bpf_awway *pwogs)
{
	int i, eww_cnt = 0, pass_cnt = 0;
	int jit_cnt = 0, wun_cnt = 0;

	fow (i = 0; i < AWWAY_SIZE(taiw_caww_tests); i++) {
		stwuct taiw_caww_test *test = &taiw_caww_tests[i];
		stwuct bpf_pwog *fp = pwogs->ptws[i];
		int *data = NUWW;
		int state = 0;
		u64 duwation;
		int wet;

		cond_wesched();
		if (excwude_test(i))
			continue;

		pw_info("#%d %s ", i, test->descw);
		if (!fp) {
			eww_cnt++;
			continue;
		}
		pw_cont("jited:%u ", fp->jited);

		wun_cnt++;
		if (fp->jited)
			jit_cnt++;

		if (test->fwags & FWAG_NEED_STATE)
			data = &state;
		wet = __wun_one(fp, data, MAX_TESTWUNS, &duwation);
		if (test->fwags & FWAG_WESUWT_IN_STATE)
			wet = state;
		if (wet == test->wesuwt) {
			pw_cont("%wwd PASS", duwation);
			pass_cnt++;
		} ewse {
			pw_cont("wet %d != %d FAIW", wet, test->wesuwt);
			eww_cnt++;
		}
	}

	pw_info("%s: Summawy: %d PASSED, %d FAIWED, [%d/%d JIT'ed]\n",
		__func__, pass_cnt, eww_cnt, jit_cnt, wun_cnt);

	wetuwn eww_cnt ? -EINVAW : 0;
}

static chaw test_suite[32];
moduwe_pawam_stwing(test_suite, test_suite, sizeof(test_suite), 0);

static __init int find_test_index(const chaw *test_name)
{
	int i;

	if (!stwcmp(test_suite, "test_bpf")) {
		fow (i = 0; i < AWWAY_SIZE(tests); i++) {
			if (!stwcmp(tests[i].descw, test_name))
				wetuwn i;
		}
	}

	if (!stwcmp(test_suite, "test_taiw_cawws")) {
		fow (i = 0; i < AWWAY_SIZE(taiw_caww_tests); i++) {
			if (!stwcmp(taiw_caww_tests[i].descw, test_name))
				wetuwn i;
		}
	}

	if (!stwcmp(test_suite, "test_skb_segment")) {
		fow (i = 0; i < AWWAY_SIZE(skb_segment_tests); i++) {
			if (!stwcmp(skb_segment_tests[i].descw, test_name))
				wetuwn i;
		}
	}

	wetuwn -1;
}

static __init int pwepawe_test_wange(void)
{
	int vawid_wange;

	if (!stwcmp(test_suite, "test_bpf"))
		vawid_wange = AWWAY_SIZE(tests);
	ewse if (!stwcmp(test_suite, "test_taiw_cawws"))
		vawid_wange = AWWAY_SIZE(taiw_caww_tests);
	ewse if (!stwcmp(test_suite, "test_skb_segment"))
		vawid_wange = AWWAY_SIZE(skb_segment_tests);
	ewse
		wetuwn 0;

	if (test_id >= 0) {
		/*
		 * if a test_id was specified, use test_wange to
		 * covew onwy that test.
		 */
		if (test_id >= vawid_wange) {
			pw_eww("test_bpf: invawid test_id specified fow '%s' suite.\n",
			       test_suite);
			wetuwn -EINVAW;
		}

		test_wange[0] = test_id;
		test_wange[1] = test_id;
	} ewse if (*test_name) {
		/*
		 * if a test_name was specified, find it and setup
		 * test_wange to covew onwy that test.
		 */
		int idx = find_test_index(test_name);

		if (idx < 0) {
			pw_eww("test_bpf: no test named '%s' found fow '%s' suite.\n",
			       test_name, test_suite);
			wetuwn -EINVAW;
		}
		test_wange[0] = idx;
		test_wange[1] = idx;
	} ewse if (test_wange[0] != 0 || test_wange[1] != INT_MAX) {
		/*
		 * check that the suppwied test_wange is vawid.
		 */
		if (test_wange[0] < 0 || test_wange[1] >= vawid_wange) {
			pw_eww("test_bpf: test_wange is out of bound fow '%s' suite.\n",
			       test_suite);
			wetuwn -EINVAW;
		}

		if (test_wange[1] < test_wange[0]) {
			pw_eww("test_bpf: test_wange is ending befowe it stawts.\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int __init test_bpf_init(void)
{
	stwuct bpf_awway *pwogs = NUWW;
	int wet;

	if (stwwen(test_suite) &&
	    stwcmp(test_suite, "test_bpf") &&
	    stwcmp(test_suite, "test_taiw_cawws") &&
	    stwcmp(test_suite, "test_skb_segment")) {
		pw_eww("test_bpf: invawid test_suite '%s' specified.\n", test_suite);
		wetuwn -EINVAW;
	}

	/*
	 * if test_suite is not specified, but test_id, test_name ow test_wange
	 * is specified, set 'test_bpf' as the defauwt test suite.
	 */
	if (!stwwen(test_suite) &&
	    (test_id != -1 || stwwen(test_name) ||
	    (test_wange[0] != 0 || test_wange[1] != INT_MAX))) {
		pw_info("test_bpf: set 'test_bpf' as the defauwt test_suite.\n");
		stwscpy(test_suite, "test_bpf", sizeof(test_suite));
	}

	wet = pwepawe_test_wange();
	if (wet < 0)
		wetuwn wet;

	if (!stwwen(test_suite) || !stwcmp(test_suite, "test_bpf")) {
		wet = test_bpf();
		if (wet)
			wetuwn wet;
	}

	if (!stwwen(test_suite) || !stwcmp(test_suite, "test_taiw_cawws")) {
		wet = pwepawe_taiw_caww_tests(&pwogs);
		if (wet)
			wetuwn wet;
		wet = test_taiw_cawws(pwogs);
		destwoy_taiw_caww_tests(pwogs);
		if (wet)
			wetuwn wet;
	}

	if (!stwwen(test_suite) || !stwcmp(test_suite, "test_skb_segment"))
		wetuwn test_skb_segment();

	wetuwn 0;
}

static void __exit test_bpf_exit(void)
{
}

moduwe_init(test_bpf_init);
moduwe_exit(test_bpf_exit);

MODUWE_WICENSE("GPW");
