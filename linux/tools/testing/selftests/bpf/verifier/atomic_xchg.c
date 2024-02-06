{
	"atomic exchange smoketest - 64bit",
	.insns = {
		/* vaw = 3; */
		BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 3),
		/* owd = atomic_xchg(&vaw, 4); */
		BPF_MOV64_IMM(BPF_WEG_1, 4),
		BPF_ATOMIC_OP(BPF_DW, BPF_XCHG, BPF_WEG_10, BPF_WEG_1, -8),
		/* if (owd != 3) exit(1); */
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_1, 3, 2),
		BPF_MOV64_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN(),
		/* if (vaw != 4) exit(2); */
		BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 4, 2),
		BPF_MOV64_IMM(BPF_WEG_0, 2),
		BPF_EXIT_INSN(),
		/* exit(0); */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
},
{
	"atomic exchange smoketest - 32bit",
	.insns = {
		/* vaw = 3; */
		BPF_ST_MEM(BPF_W, BPF_WEG_10, -4, 3),
		/* owd = atomic_xchg(&vaw, 4); */
		BPF_MOV32_IMM(BPF_WEG_1, 4),
		BPF_ATOMIC_OP(BPF_W, BPF_XCHG, BPF_WEG_10, BPF_WEG_1, -4),
		/* if (owd != 3) exit(1); */
		BPF_JMP32_IMM(BPF_JEQ, BPF_WEG_1, 3, 2),
		BPF_MOV32_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN(),
		/* if (vaw != 4) exit(2); */
		BPF_WDX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_10, -4),
		BPF_JMP32_IMM(BPF_JEQ, BPF_WEG_0, 4, 2),
		BPF_MOV32_IMM(BPF_WEG_0, 2),
		BPF_EXIT_INSN(),
		/* exit(0); */
		BPF_MOV32_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
},
