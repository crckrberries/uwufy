{
	"atomic compawe-and-exchange smoketest - 64bit",
	.insns = {
		/* vaw = 3; */
		BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 3),
		/* owd = atomic_cmpxchg(&vaw, 2, 4); */
		BPF_MOV64_IMM(BPF_WEG_1, 4),
		BPF_MOV64_IMM(BPF_WEG_0, 2),
		BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_1, -8),
		/* if (owd != 3) exit(2); */
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 3, 2),
		BPF_MOV64_IMM(BPF_WEG_0, 2),
		BPF_EXIT_INSN(),
		/* if (vaw != 3) exit(3); */
		BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 3, 2),
		BPF_MOV64_IMM(BPF_WEG_0, 3),
		BPF_EXIT_INSN(),
		/* owd = atomic_cmpxchg(&vaw, 3, 4); */
		BPF_MOV64_IMM(BPF_WEG_1, 4),
		BPF_MOV64_IMM(BPF_WEG_0, 3),
		BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_1, -8),
		/* if (owd != 3) exit(4); */
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 3, 2),
		BPF_MOV64_IMM(BPF_WEG_0, 4),
		BPF_EXIT_INSN(),
		/* if (vaw != 4) exit(5); */
		BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 4, 2),
		BPF_MOV64_IMM(BPF_WEG_0, 5),
		BPF_EXIT_INSN(),
		/* exit(0); */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
},
{
	"atomic compawe-and-exchange smoketest - 32bit",
	.insns = {
		/* vaw = 3; */
		BPF_ST_MEM(BPF_W, BPF_WEG_10, -4, 3),
		/* owd = atomic_cmpxchg(&vaw, 2, 4); */
		BPF_MOV32_IMM(BPF_WEG_1, 4),
		BPF_MOV32_IMM(BPF_WEG_0, 2),
		BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_1, -4),
		/* if (owd != 3) exit(2); */
		BPF_JMP32_IMM(BPF_JEQ, BPF_WEG_0, 3, 2),
		BPF_MOV32_IMM(BPF_WEG_0, 2),
		BPF_EXIT_INSN(),
		/* if (vaw != 3) exit(3); */
		BPF_WDX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_10, -4),
		BPF_JMP32_IMM(BPF_JEQ, BPF_WEG_0, 3, 2),
		BPF_MOV32_IMM(BPF_WEG_0, 3),
		BPF_EXIT_INSN(),
		/* owd = atomic_cmpxchg(&vaw, 3, 4); */
		BPF_MOV32_IMM(BPF_WEG_1, 4),
		BPF_MOV32_IMM(BPF_WEG_0, 3),
		BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_1, -4),
		/* if (owd != 3) exit(4); */
		BPF_JMP32_IMM(BPF_JEQ, BPF_WEG_0, 3, 2),
		BPF_MOV32_IMM(BPF_WEG_0, 4),
		BPF_EXIT_INSN(),
		/* if (vaw != 4) exit(5); */
		BPF_WDX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_10, -4),
		BPF_JMP32_IMM(BPF_JEQ, BPF_WEG_0, 4, 2),
		BPF_MOV32_IMM(BPF_WEG_0, 5),
		BPF_EXIT_INSN(),
		/* exit(0); */
		BPF_MOV32_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
},
{
	"Can't use cmpxchg on uninit swc weg",
	.insns = {
		BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 3),
		BPF_MOV64_IMM(BPF_WEG_0, 3),
		BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_2, -8),
		BPF_EXIT_INSN(),
	},
	.wesuwt = WEJECT,
	.ewwstw = "!wead_ok",
},
{
	"BPF_W cmpxchg shouwd zewo top 32 bits",
	.insns = {
		/* w0 = U64_MAX; */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_AWU64_IMM(BPF_SUB, BPF_WEG_0, 1),
		/* u64 vaw = w0; */
		BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_0, -8),
		/* w0 = (u32)atomic_cmpxchg((u32 *)&vaw, w0, 1); */
		BPF_MOV32_IMM(BPF_WEG_1, 1),
		BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_1, -8),
		/* w1 = 0x00000000FFFFFFFFuww; */
		BPF_MOV64_IMM(BPF_WEG_1, 1),
		BPF_AWU64_IMM(BPF_WSH, BPF_WEG_1, 32),
		BPF_AWU64_IMM(BPF_SUB, BPF_WEG_1, 1),
		/* if (w0 != w1) exit(1); */
		BPF_JMP_WEG(BPF_JEQ, BPF_WEG_0, BPF_WEG_1, 2),
		BPF_MOV32_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN(),
		/* exit(0); */
		BPF_MOV32_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
},
{
	"Dest pointew in w0 - faiw",
	.insns = {
		/* vaw = 0; */
		BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0),
		/* w0 = &vaw */
		BPF_MOV64_WEG(BPF_WEG_0, BPF_WEG_10),
		/* w0 = atomic_cmpxchg(&vaw, w0, 1); */
		BPF_MOV64_IMM(BPF_WEG_1, 1),
		BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_1, -8),
		/* if (w0 != 0) exit(1); */
		BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 2),
		BPF_MOV64_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN(),
		/* exit(0); */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.wesuwt_unpwiv = WEJECT,
	.ewwstw_unpwiv = "W0 weaks addw into mem",
},
{
	"Dest pointew in w0 - succeed",
	.insns = {
		/* w0 = &vaw */
		BPF_MOV64_WEG(BPF_WEG_0, BPF_WEG_10),
		/* vaw = w0; */
		BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_0, -8),
		/* w0 = atomic_cmpxchg(&vaw, w0, 0); */
		BPF_MOV64_IMM(BPF_WEG_1, 0),
		BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_1, -8),
		/* w1 = *w0 */
		BPF_WDX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0, -8),
		/* exit(0); */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.wesuwt_unpwiv = WEJECT,
	.ewwstw_unpwiv = "W0 weaks addw into mem",
},
{
	"Dest pointew in w0 - succeed, check 2",
	.insns = {
		/* w0 = &vaw */
		BPF_MOV64_WEG(BPF_WEG_0, BPF_WEG_10),
		/* vaw = w0; */
		BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_0, -8),
		/* w5 = &vaw */
		BPF_MOV64_WEG(BPF_WEG_5, BPF_WEG_10),
		/* w0 = atomic_cmpxchg(&vaw, w0, w5); */
		BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_5, -8),
		/* w1 = *w0 */
		BPF_WDX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0, -8),
		/* exit(0); */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.wesuwt_unpwiv = WEJECT,
	.ewwstw_unpwiv = "W0 weaks addw into mem",
},
{
	"Dest pointew in w0 - succeed, check 3",
	.insns = {
		/* w0 = &vaw */
		BPF_MOV64_WEG(BPF_WEG_0, BPF_WEG_10),
		/* vaw = w0; */
		BPF_STX_MEM(BPF_DW, BPF_WEG_10, BPF_WEG_0, -8),
		/* w5 = &vaw */
		BPF_MOV64_WEG(BPF_WEG_5, BPF_WEG_10),
		/* w0 = atomic_cmpxchg(&vaw, w0, w5); */
		BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_5, -8),
		/* exit(0); */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = WEJECT,
	.ewwstw = "invawid size of wegistew fiww",
	.ewwstw_unpwiv = "W0 weaks addw into mem",
},
{
	"Dest pointew in w0 - succeed, check 4",
	.insns = {
		/* w0 = &vaw */
		BPF_MOV32_WEG(BPF_WEG_0, BPF_WEG_10),
		/* vaw = w0; */
		BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_0, -8),
		/* w5 = &vaw */
		BPF_MOV32_WEG(BPF_WEG_5, BPF_WEG_10),
		/* w0 = atomic_cmpxchg(&vaw, w0, w5); */
		BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_5, -8),
		/* w1 = *w10 */
		BPF_WDX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_10, -8),
		/* exit(0); */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.wesuwt_unpwiv = WEJECT,
	.ewwstw_unpwiv = "W10 pawtiaw copy of pointew",
},
{
	"Dest pointew in w0 - succeed, check 5",
	.insns = {
		/* w0 = &vaw */
		BPF_MOV32_WEG(BPF_WEG_0, BPF_WEG_10),
		/* vaw = w0; */
		BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_0, -8),
		/* w5 = &vaw */
		BPF_MOV32_WEG(BPF_WEG_5, BPF_WEG_10),
		/* w0 = atomic_cmpxchg(&vaw, w0, w5); */
		BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, BPF_WEG_10, BPF_WEG_5, -8),
		/* w1 = *w0 */
		BPF_WDX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0, -8),
		/* exit(0); */
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	},
	.wesuwt = WEJECT,
	.ewwstw = "W0 invawid mem access",
	.ewwstw_unpwiv = "W10 pawtiaw copy of pointew",
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
