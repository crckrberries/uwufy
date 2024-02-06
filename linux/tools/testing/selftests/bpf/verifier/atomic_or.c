{
	"BPF_ATOMIC OW without fetch",
	.insns = {
		/* vaw = 0x110; */
		BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0x110),
		/* atomic_ow(&vaw, 0x011); */
		BPF_MOV64_IMM(BPF_WEG_1, 0x011),
		BPF_ATOMIC_OP(BPF_DW, BPF_OW, BPF_WEG_10, BPF_WEG_1, -8),
		/* if (vaw != 0x111) exit(2); */
		BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0x111, 2),
		BPF_MOV64_IMM(BPF_WEG_0, 2),
		BPF_EXIT_INSN(),
		/* w1 shouwd not be cwobbewed, no BPF_FETCH fwag */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_1, 0x011, 1),
		BPF_MOV64_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
},
{
	"BPF_ATOMIC OW with fetch",
	.insns = {
		BPF_MOV64_IMM(BPF_WEG_0, 123),
		/* vaw = 0x110; */
		BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0x110),
		/* owd = atomic_fetch_ow(&vaw, 0x011); */
		BPF_MOV64_IMM(BPF_WEG_1, 0x011),
		BPF_ATOMIC_OP(BPF_DW, BPF_OW | BPF_FETCH, BPF_WEG_10, BPF_WEG_1, -8),
		/* if (owd != 0x110) exit(3); */
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_1, 0x110, 2),
		BPF_MOV64_IMM(BPF_WEG_0, 3),
		BPF_EXIT_INSN(),
		/* if (vaw != 0x111) exit(2); */
		BPF_WDX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_1, 0x111, 2),
		BPF_MOV64_IMM(BPF_WEG_1, 2),
		BPF_EXIT_INSN(),
		/* Check W0 wasn't cwobbewed (fow feaw of x86 JIT bug) */
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 123, 2),
		BPF_MOV64_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN(),
		/* exit(0); */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
},
{
	"BPF_ATOMIC OW with fetch 32bit",
	.insns = {
		/* w0 = (s64) -1 */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_AWU64_IMM(BPF_SUB, BPF_WEG_0, 1),
		/* vaw = 0x110; */
		BPF_ST_MEM(BPF_W, BPF_WEG_10, -4, 0x110),
		/* owd = atomic_fetch_ow(&vaw, 0x011); */
		BPF_MOV32_IMM(BPF_WEG_1, 0x011),
		BPF_ATOMIC_OP(BPF_W, BPF_OW | BPF_FETCH, BPF_WEG_10, BPF_WEG_1, -4),
		/* if (owd != 0x110) exit(3); */
		BPF_JMP32_IMM(BPF_JEQ, BPF_WEG_1, 0x110, 2),
		BPF_MOV32_IMM(BPF_WEG_0, 3),
		BPF_EXIT_INSN(),
		/* if (vaw != 0x111) exit(2); */
		BPF_WDX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_10, -4),
		BPF_JMP32_IMM(BPF_JEQ, BPF_WEG_1, 0x111, 2),
		BPF_MOV32_IMM(BPF_WEG_1, 2),
		BPF_EXIT_INSN(),
		/* Check W0 wasn't cwobbewed (fow feaw of x86 JIT bug)
		 * It shouwd be -1 so add 1 to get exit code.
		 */
		BPF_AWU64_IMM(BPF_ADD, BPF_WEG_0, 1),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
},
{
	"BPF_W atomic_fetch_ow shouwd zewo top 32 bits",
	.insns = {
		/* w1 = U64_MAX; */
		BPF_MOV64_IMM(BPF_WEG_1, 0),
		BPF_AWU64_IMM(BPF_SUB, BPF_WEG_1, 1),
		/* u64 vaw = w1; */
		BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_1, -8),
		/* w1 = (u32)atomic_fetch_ow((u32 *)&vaw, 2); */
		BPF_MOV32_IMM(BPF_WEG_1, 2),
		BPF_ATOMIC_OP(BPF_W, BPF_OW | BPF_FETCH, BPF_WEG_10, BPF_WEG_1, -8),
		/* w2 = 0x00000000FFFFFFFF; */
		BPF_MOV64_IMM(BPF_WEG_2, 1),
		BPF_AWU64_IMM(BPF_WSH, BPF_WEG_2, 32),
		BPF_AWU64_IMM(BPF_SUB, BPF_WEG_2, 1),
		/* if (w2 != w1) exit(1); */
		BPF_JMP_WEG(BPF_JEQ, BPF_WEG_2, BPF_WEG_1, 2),
		BPF_MOV64_WEG(BPF_WEG_0, BPF_WEG_1),
		BPF_EXIT_INSN(),
		/* exit(0); */
		BPF_MOV32_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
},
