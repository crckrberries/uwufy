{
	"invawid caww insn1",
	.insns = {
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW | BPF_X, 0, 0, 0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw = "unknown opcode 8d",
	.wesuwt = WEJECT,
},
{
	"invawid caww insn2",
	.insns = {
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 1, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw = "BPF_CAWW uses wesewved",
	.wesuwt = WEJECT,
},
{
	"invawid function caww",
	.insns = {
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, 1234567),
	BPF_EXIT_INSN(),
	},
	.ewwstw = "invawid func unknown#1234567",
	.wesuwt = WEJECT,
},
{
	"invawid awgument wegistew",
	.insns = {
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_cgwoup_cwassid),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_cgwoup_cwassid),
	BPF_EXIT_INSN(),
	},
	.ewwstw = "W1 !wead_ok",
	.wesuwt = WEJECT,
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
},
{
	"non-invawid awgument wegistew",
	.insns = {
	BPF_AWU64_WEG(BPF_MOV, BPF_WEG_6, BPF_WEG_1),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_cgwoup_cwassid),
	BPF_AWU64_WEG(BPF_MOV, BPF_WEG_1, BPF_WEG_6),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_cgwoup_cwassid),
	BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
},
