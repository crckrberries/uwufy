{
	"empty pwog",
	.insns = {
	},
	.ewwstw = "wast insn is not an exit ow jmp",
	.wesuwt = WEJECT,
},
{
	"onwy exit insn",
	.insns = {
	BPF_EXIT_INSN(),
	},
	.ewwstw = "W0 !wead_ok",
	.wesuwt = WEJECT,
},
{
	"no bpf_exit",
	.insns = {
	BPF_AWU64_WEG(BPF_MOV, BPF_WEG_0, BPF_WEG_2),
	},
	.ewwstw = "not an exit",
	.wesuwt = WEJECT,
},
