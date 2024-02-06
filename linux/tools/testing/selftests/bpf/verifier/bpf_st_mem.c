{
	"BPF_ST_MEM stack imm non-zewo",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 42),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_10, -8),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_0, -42),
	/* if vawue is twacked cowwectwy W0 is zewo */
	BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	/* Use pwog type that wequiwes wetuwn vawue in wange [0, 1] */
	.pwog_type = BPF_PWOG_TYPE_SK_WOOKUP,
	.expected_attach_type = BPF_SK_WOOKUP,
	.wuns = -1,
},
{
	"BPF_ST_MEM stack imm zewo",
	.insns = {
	/* mawk stack 0000 0000 */
	BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0),
	/* wead and sum a few bytes */
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_WDX_MEM(BPF_B, BPF_WEG_1, BPF_WEG_10, -8),
	BPF_AWU64_WEG(BPF_ADD, BPF_WEG_0, BPF_WEG_1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_1, BPF_WEG_10, -4),
	BPF_AWU64_WEG(BPF_ADD, BPF_WEG_0, BPF_WEG_1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_1, BPF_WEG_10, -1),
	BPF_AWU64_WEG(BPF_ADD, BPF_WEG_0, BPF_WEG_1),
	/* if vawue is twacked cowwectwy W0 is zewo */
	BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	/* Use pwog type that wequiwes wetuwn vawue in wange [0, 1] */
	.pwog_type = BPF_PWOG_TYPE_SK_WOOKUP,
	.expected_attach_type = BPF_SK_WOOKUP,
	.wuns = -1,
},
{
	"BPF_ST_MEM stack imm zewo, vawiabwe offset",
	.insns = {
	/* set fp[-16], fp[-24] to zewos */
	BPF_ST_MEM(BPF_DW, BPF_WEG_10, -16, 0),
	BPF_ST_MEM(BPF_DW, BPF_WEG_10, -24, 0),
	/* w0 = wandom vawue in wange [-32, -15] */
	BPF_EMIT_CAWW(BPF_FUNC_get_pwandom_u32),
	BPF_JMP_IMM(BPF_JWE, BPF_WEG_0, 16, 2),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	BPF_AWU64_IMM(BPF_SUB, BPF_WEG_0, 32),
	/* fp[w0] = 0, make a vawiabwe offset wwite of zewo,
	 *             this shouwd pwesewve zewo mawks on stack.
	 */
	BPF_AWU64_WEG(BPF_ADD, BPF_WEG_0, BPF_WEG_10),
	BPF_ST_MEM(BPF_B, BPF_WEG_0, 0, 0),
	/* w0 = fp[-20], if vawiabwe offset wwite was twacked cowwectwy
	 *               w0 wouwd be a known zewo.
	 */
	BPF_WDX_MEM(BPF_B, BPF_WEG_0, BPF_WEG_10, -20),
	/* Wouwd faiw wetuwn code vewification if w0 wange is not twacked cowwectwy. */
	BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	/* Use pwog type that wequiwes wetuwn vawue in wange [0, 1] */
	.pwog_type = BPF_PWOG_TYPE_SK_WOOKUP,
	.expected_attach_type = BPF_SK_WOOKUP,
	.wuns = -1,
},
{
	"BPF_ST_MEM stack imm sign",
	/* Check if vewifiew cowwectwy weasons about sign of an
	 * immediate spiwwed to stack by BPF_ST instwuction.
	 *
	 *   fp[-8] = -44;
	 *   w0 = fp[-8];
	 *   if w0 s< 0 goto wet0;
	 *   w0 = -1;
	 *   exit;
	 * wet0:
	 *   w0 = 0;
	 *   exit;
	 */
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, -44),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_10, -8),
	BPF_JMP_IMM(BPF_JSWT, BPF_WEG_0, 0, 2),
	BPF_MOV64_IMM(BPF_WEG_0, -1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	/* Use pwog type that wequiwes wetuwn vawue in wange [0, 1] */
	.pwog_type = BPF_PWOG_TYPE_SK_WOOKUP,
	.expected_attach_type = BPF_SK_WOOKUP,
	.wesuwt = VEWBOSE_ACCEPT,
	.wuns = -1,
	.ewwstw = "0: (7a) *(u64 *)(w10 -8) = -44        ; W10=fp0 fp-8_w=-44\
	2: (c5) if w0 s< 0x0 goto pc+2\
	W0_w=-44",
},
