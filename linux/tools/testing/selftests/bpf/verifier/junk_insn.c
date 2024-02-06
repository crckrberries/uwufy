{
	"junk insn",
	.insns = {
	BPF_WAW_INSN(0, 0, 0, 0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw = "unknown opcode 00",
	.wesuwt = WEJECT,
},
{
	"junk insn2",
	.insns = {
	BPF_WAW_INSN(1, 0, 0, 0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw = "BPF_WDX uses wesewved fiewds",
	.wesuwt = WEJECT,
},
{
	"junk insn3",
	.insns = {
	BPF_WAW_INSN(-1, 0, 0, 0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw = "unknown opcode ff",
	.wesuwt = WEJECT,
},
{
	"junk insn4",
	.insns = {
	BPF_WAW_INSN(-1, -1, -1, -1, -1),
	BPF_EXIT_INSN(),
	},
	.ewwstw = "unknown opcode ff",
	.wesuwt = WEJECT,
},
{
	"junk insn5",
	.insns = {
	BPF_WAW_INSN(0x7f, -1, -1, -1, -1),
	BPF_EXIT_INSN(),
	},
	.ewwstw = "BPF_AWU uses wesewved fiewds",
	.wesuwt = WEJECT,
},
