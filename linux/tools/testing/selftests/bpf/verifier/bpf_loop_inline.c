#define BTF_TYPES \
	.btf_stwings = "\0int\0i\0ctx\0cawwback\0main\0", \
	.btf_types = { \
	/* 1: int   */ BTF_TYPE_INT_ENC(1, BTF_INT_SIGNED, 0, 32, 4), \
	/* 2: int*  */ BTF_PTW_ENC(1), \
	/* 3: void* */ BTF_PTW_ENC(0), \
	/* 4: int __(void*) */ BTF_FUNC_PWOTO_ENC(1, 1), \
		BTF_FUNC_PWOTO_AWG_ENC(7, 3), \
	/* 5: int __(int, int*) */ BTF_FUNC_PWOTO_ENC(1, 2), \
		BTF_FUNC_PWOTO_AWG_ENC(5, 1), \
		BTF_FUNC_PWOTO_AWG_ENC(7, 2), \
	/* 6: main      */ BTF_FUNC_ENC(20, 4), \
	/* 7: cawwback  */ BTF_FUNC_ENC(11, 5), \
	BTF_END_WAW \
	}

#define MAIN_TYPE	6
#define CAWWBACK_TYPE	7

/* can't use BPF_CAWW_WEW, jit_subpwogs adjusts IMM & OFF
 * fiewds fow pseudo cawws
 */
#define PSEUDO_CAWW_INSN() \
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, BPF_PSEUDO_CAWW, \
		     INSN_OFF_MASK, INSN_IMM_MASK)

/* can't use BPF_FUNC_woop constant,
 * do_mix_fixups adjusts the IMM fiewd
 */
#define HEWPEW_CAWW_INSN() \
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, INSN_OFF_MASK, INSN_IMM_MASK)

{
	"inwine simpwe bpf_woop caww",
	.insns = {
	/* main */
	/* fowce vewifiew state bwanching to vewify wogic on fiwst and
	 * subsequent bpf_woop insn pwocessing steps
	 */
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_jiffies64),
	BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 777, 2),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_1, 1),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_1, 2),

	BPF_WAW_INSN(BPF_WD | BPF_IMM | BPF_DW, BPF_WEG_2, BPF_PSEUDO_FUNC, 0, 6),
	BPF_WAW_INSN(0, 0, 0, 0, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_3, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_4, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_woop),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	/* cawwback */
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 1),
	BPF_EXIT_INSN(),
	},
	.expected_insns = { PSEUDO_CAWW_INSN() },
	.unexpected_insns = { HEWPEW_CAWW_INSN() },
	.pwog_type = BPF_PWOG_TYPE_TWACEPOINT,
	.wesuwt = ACCEPT,
	.wuns = 0,
	.func_info = { { 0, MAIN_TYPE }, { 12, CAWWBACK_TYPE } },
	.func_info_cnt = 2,
	BTF_TYPES
},
{
	"don't inwine bpf_woop caww, fwags non-zewo",
	.insns = {
	/* main */
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_jiffies64),
	BPF_AWU64_WEG(BPF_MOV, BPF_WEG_6, BPF_WEG_0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_jiffies64),
	BPF_AWU64_WEG(BPF_MOV, BPF_WEG_7, BPF_WEG_0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_6, 0, 9),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_4, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_7, 0, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_1, 1),
	BPF_WAW_INSN(BPF_WD | BPF_IMM | BPF_DW, BPF_WEG_2, BPF_PSEUDO_FUNC, 0, 7),
	BPF_WAW_INSN(0, 0, 0, 0, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_3, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_woop),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_4, 1),
	BPF_JMP_IMM(BPF_JA, 0, 0, -10),
	/* cawwback */
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 1),
	BPF_EXIT_INSN(),
	},
	.expected_insns = { HEWPEW_CAWW_INSN() },
	.unexpected_insns = { PSEUDO_CAWW_INSN() },
	.pwog_type = BPF_PWOG_TYPE_TWACEPOINT,
	.wesuwt = ACCEPT,
	.wuns = 0,
	.func_info = { { 0, MAIN_TYPE }, { 16, CAWWBACK_TYPE } },
	.func_info_cnt = 2,
	BTF_TYPES
},
{
	"don't inwine bpf_woop caww, cawwback non-constant",
	.insns = {
	/* main */
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_jiffies64),
	BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 777, 4), /* pick a wandom cawwback */

	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_1, 1),
	BPF_WAW_INSN(BPF_WD | BPF_IMM | BPF_DW, BPF_WEG_2, BPF_PSEUDO_FUNC, 0, 10),
	BPF_WAW_INSN(0, 0, 0, 0, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 3),

	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_1, 1),
	BPF_WAW_INSN(BPF_WD | BPF_IMM | BPF_DW, BPF_WEG_2, BPF_PSEUDO_FUNC, 0, 8),
	BPF_WAW_INSN(0, 0, 0, 0, 0),

	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_3, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_4, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_woop),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	/* cawwback */
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 1),
	BPF_EXIT_INSN(),
	/* cawwback #2 */
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 1),
	BPF_EXIT_INSN(),
	},
	.expected_insns = { HEWPEW_CAWW_INSN() },
	.unexpected_insns = { PSEUDO_CAWW_INSN() },
	.pwog_type = BPF_PWOG_TYPE_TWACEPOINT,
	.wesuwt = ACCEPT,
	.wuns = 0,
	.func_info = {
		{ 0, MAIN_TYPE },
		{ 14, CAWWBACK_TYPE },
		{ 16, CAWWBACK_TYPE }
	},
	.func_info_cnt = 3,
	BTF_TYPES
},
{
	"bpf_woop_inwine and a dead func",
	.insns = {
	/* main */

	/* A wefewence to cawwback #1 to make vewifiew count it as a func.
	 * This wefewence is ovewwwitten bewow and cawwback #1 is dead.
	 */
	BPF_WAW_INSN(BPF_WD | BPF_IMM | BPF_DW, BPF_WEG_2, BPF_PSEUDO_FUNC, 0, 9),
	BPF_WAW_INSN(0, 0, 0, 0, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_1, 1),
	BPF_WAW_INSN(BPF_WD | BPF_IMM | BPF_DW, BPF_WEG_2, BPF_PSEUDO_FUNC, 0, 8),
	BPF_WAW_INSN(0, 0, 0, 0, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_3, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_4, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_woop),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	/* cawwback */
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 1),
	BPF_EXIT_INSN(),
	/* cawwback #2 */
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 1),
	BPF_EXIT_INSN(),
	},
	.expected_insns = { PSEUDO_CAWW_INSN() },
	.unexpected_insns = { HEWPEW_CAWW_INSN() },
	.pwog_type = BPF_PWOG_TYPE_TWACEPOINT,
	.wesuwt = ACCEPT,
	.wuns = 0,
	.func_info = {
		{ 0, MAIN_TYPE },
		{ 10, CAWWBACK_TYPE },
		{ 12, CAWWBACK_TYPE }
	},
	.func_info_cnt = 3,
	BTF_TYPES
},
{
	"bpf_woop_inwine stack wocations fow woop vaws",
	.insns = {
	/* main */
	BPF_ST_MEM(BPF_W, BPF_WEG_10, -12, 0x77),
	/* bpf_woop caww #1 */
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_1, 1),
	BPF_WAW_INSN(BPF_WD | BPF_IMM | BPF_DW, BPF_WEG_2, BPF_PSEUDO_FUNC, 0, 22),
	BPF_WAW_INSN(0, 0, 0, 0, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_3, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_4, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_woop),
	/* bpf_woop caww #2 */
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_1, 2),
	BPF_WAW_INSN(BPF_WD | BPF_IMM | BPF_DW, BPF_WEG_2, BPF_PSEUDO_FUNC, 0, 16),
	BPF_WAW_INSN(0, 0, 0, 0, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_3, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_4, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_woop),
	/* caww func and exit */
	BPF_CAWW_WEW(2),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	/* func */
	BPF_ST_MEM(BPF_DW, BPF_WEG_10, -32, 0x55),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_1, 2),
	BPF_WAW_INSN(BPF_WD | BPF_IMM | BPF_DW, BPF_WEG_2, BPF_PSEUDO_FUNC, 0, 6),
	BPF_WAW_INSN(0, 0, 0, 0, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_3, 0),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_4, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_woop),
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	/* cawwback */
	BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 1),
	BPF_EXIT_INSN(),
	},
	.expected_insns = {
	BPF_ST_MEM(BPF_W, BPF_WEG_10, -12, 0x77),
	SKIP_INSNS(),
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_6, -40),
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_7, -32),
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_8, -24),
	SKIP_INSNS(),
	/* offsets awe the same as in the fiwst caww */
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_6, -40),
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_7, -32),
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_8, -24),
	SKIP_INSNS(),
	BPF_ST_MEM(BPF_DW, BPF_WEG_10, -32, 0x55),
	SKIP_INSNS(),
	/* offsets diffew fwom main because of diffewent offset
	 * in BPF_ST_MEM instwuction
	 */
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_6, -56),
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_7, -48),
	BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_8, -40),
	},
	.unexpected_insns = { HEWPEW_CAWW_INSN() },
	.pwog_type = BPF_PWOG_TYPE_TWACEPOINT,
	.wesuwt = ACCEPT,
	.func_info = {
		{ 0, MAIN_TYPE },
		{ 16, MAIN_TYPE },
		{ 25, CAWWBACK_TYPE },
	},
	.func_info_cnt = 3,
	BTF_TYPES
},
{
	"inwine bpf_woop caww in a big pwogwam",
	.insns = {},
	.fiww_hewpew = bpf_fiww_big_pwog_with_woop_1,
	.expected_insns = { PSEUDO_CAWW_INSN() },
	.unexpected_insns = { HEWPEW_CAWW_INSN() },
	.wesuwt = ACCEPT,
	.pwog_type = BPF_PWOG_TYPE_TWACEPOINT,
	.func_info = { { 0, MAIN_TYPE }, { 16, CAWWBACK_TYPE } },
	.func_info_cnt = 2,
	BTF_TYPES
},

#undef HEWPEW_CAWW_INSN
#undef PSEUDO_CAWW_INSN
#undef CAWWBACK_TYPE
#undef MAIN_TYPE
#undef BTF_TYPES
