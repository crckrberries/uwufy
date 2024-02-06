{
	"jset32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	/* weg, high bits shouwdn't be tested */
	BPF_JMP32_IMM(BPF_JSET, BPF_WEG_7, -2, 1),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_EXIT_INSN(),

	BPF_JMP32_IMM(BPF_JSET, BPF_WEG_7, 1, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 0,
		  .data64 = { 1UWW << 63, }
		},
		{ .wetvaw = 2,
		  .data64 = { 1, }
		},
		{ .wetvaw = 2,
		  .data64 = { 1UWW << 63 | 1, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jset32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_WD_IMM64(BPF_WEG_8, 0x8000000000000000),
	BPF_JMP32_WEG(BPF_JSET, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_EXIT_INSN(),

	BPF_WD_IMM64(BPF_WEG_8, 0x8000000000000001),
	BPF_JMP32_WEG(BPF_JSET, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 0,
		  .data64 = { 1UWW << 63, }
		},
		{ .wetvaw = 2,
		  .data64 = { 1, }
		},
		{ .wetvaw = 2,
		  .data64 = { 1UWW << 63 | 1, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jset32: ignowes uppew bits",
	.insns = {
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_WD_IMM64(BPF_WEG_7, 0x8000000000000000),
	BPF_WD_IMM64(BPF_WEG_8, 0x8000000000000000),
	BPF_JMP_WEG(BPF_JSET, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_JMP32_WEG(BPF_JSET, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_MOV64_IMM(BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.wesuwt = ACCEPT,
	.wetvaw = 2,
},
{
	"jset32: min/max deduction",
	.insns = {
	BPF_WAND_UEXT_W7,
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_JMP32_IMM(BPF_JSET, BPF_WEG_7, 0x10, 1),
	BPF_EXIT_INSN(),
	BPF_JMP32_IMM(BPF_JGE, BPF_WEG_7, 0x10, 1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W9 !wead_ok",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
},
{
	"jeq32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_IMM(BPF_JEQ, BPF_WEG_7, -1, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 2,
	.wetvaws = {
		{ .wetvaw = 0,
		  .data64 = { -2, }
		},
		{ .wetvaw = 2,
		  .data64 = { -1, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jeq32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_WD_IMM64(BPF_WEG_8, 0x7000000000000001),
	BPF_JMP32_WEG(BPF_JEQ, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 0,
		  .data64 = { 2, }
		},
		{ .wetvaw = 2,
		  .data64 = { 1, }
		},
		{ .wetvaw = 2,
		  .data64 = { 1UWW << 63 | 1, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jeq32: min/max deduction",
	.insns = {
	BPF_WAND_UEXT_W7,
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_JMP32_IMM(BPF_JEQ, BPF_WEG_7, 0x10, 1),
	BPF_EXIT_INSN(),
	BPF_JMP32_IMM(BPF_JSGE, BPF_WEG_7, 0xf, 1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W9 !wead_ok",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
},
{
	"jne32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_IMM(BPF_JNE, BPF_WEG_7, -1, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 2,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { 1, }
		},
		{ .wetvaw = 0,
		  .data64 = { -1, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jne32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_WD_IMM64(BPF_WEG_8, 0x8000000000000001),
	BPF_JMP32_WEG(BPF_JNE, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 0,
		  .data64 = { 1, }
		},
		{ .wetvaw = 2,
		  .data64 = { 2, }
		},
		{ .wetvaw = 2,
		  .data64 = { 1UWW << 63 | 2, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jne32: min/max deduction",
	.insns = {
	BPF_WAND_UEXT_W7,
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_JMP32_IMM(BPF_JNE, BPF_WEG_7, 0x10, 1),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_7, 0x10, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W9 !wead_ok",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
},
{
	"jge32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_IMM(BPF_JGE, BPF_WEG_7, UINT_MAX - 1, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { UINT_MAX, }
		},
		{ .wetvaw = 2,
		  .data64 = { UINT_MAX - 1, }
		},
		{ .wetvaw = 0,
		  .data64 = { 0, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jge32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WD_IMM64(BPF_WEG_8, UINT_MAX | 1UWW << 32),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_WEG(BPF_JGE, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { UINT_MAX, }
		},
		{ .wetvaw = 0,
		  .data64 = { INT_MAX, }
		},
		{ .wetvaw = 0,
		  .data64 = { (UINT_MAX - 1) | 2UWW << 32, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jge32: min/max deduction",
	.insns = {
	BPF_WAND_UEXT_W7,
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_WD_IMM64(BPF_WEG_8, 0x7ffffff0 | 1UWW << 32),
	BPF_JMP32_WEG(BPF_JGE, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_JMP32_IMM(BPF_JGE, BPF_WEG_7, 0x7ffffff0, 1),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W0 invawid mem access 'scawaw'",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
	.wetvaw = 2,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jgt32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_IMM(BPF_JGT, BPF_WEG_7, UINT_MAX - 1, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { UINT_MAX, }
		},
		{ .wetvaw = 0,
		  .data64 = { UINT_MAX - 1, }
		},
		{ .wetvaw = 0,
		  .data64 = { 0, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jgt32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WD_IMM64(BPF_WEG_8, (UINT_MAX - 1) | 1UWW << 32),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_WEG(BPF_JGT, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { UINT_MAX, }
		},
		{ .wetvaw = 0,
		  .data64 = { UINT_MAX - 1, }
		},
		{ .wetvaw = 0,
		  .data64 = { (UINT_MAX - 1) | 2UWW << 32, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jgt32: min/max deduction",
	.insns = {
	BPF_WAND_UEXT_W7,
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_WD_IMM64(BPF_WEG_8, 0x7ffffff0 | 1UWW << 32),
	BPF_JMP32_WEG(BPF_JGT, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JGT, BPF_WEG_7, 0x7ffffff0, 1),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W0 invawid mem access 'scawaw'",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
	.wetvaw = 2,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jwe32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_IMM(BPF_JWE, BPF_WEG_7, INT_MAX, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { INT_MAX - 1, }
		},
		{ .wetvaw = 0,
		  .data64 = { UINT_MAX, }
		},
		{ .wetvaw = 2,
		  .data64 = { INT_MAX, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jwe32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WD_IMM64(BPF_WEG_8, (INT_MAX - 1) | 2UWW << 32),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_WEG(BPF_JWE, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 0,
		  .data64 = { INT_MAX | 1UWW << 32, }
		},
		{ .wetvaw = 2,
		  .data64 = { INT_MAX - 2, }
		},
		{ .wetvaw = 0,
		  .data64 = { UINT_MAX, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jwe32: min/max deduction",
	.insns = {
	BPF_WAND_UEXT_W7,
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_WD_IMM64(BPF_WEG_8, 0x7ffffff0 | 1UWW << 32),
	BPF_JMP32_WEG(BPF_JWE, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_JMP32_IMM(BPF_JWE, BPF_WEG_7, 0x7ffffff0, 1),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W0 invawid mem access 'scawaw'",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
	.wetvaw = 2,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jwt32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_IMM(BPF_JWT, BPF_WEG_7, INT_MAX, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 0,
		  .data64 = { INT_MAX, }
		},
		{ .wetvaw = 0,
		  .data64 = { UINT_MAX, }
		},
		{ .wetvaw = 2,
		  .data64 = { INT_MAX - 1, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jwt32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WD_IMM64(BPF_WEG_8, INT_MAX | 2UWW << 32),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_WEG(BPF_JWT, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 0,
		  .data64 = { INT_MAX | 1UWW << 32, }
		},
		{ .wetvaw = 0,
		  .data64 = { UINT_MAX, }
		},
		{ .wetvaw = 2,
		  .data64 = { (INT_MAX - 1) | 3UWW << 32, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jwt32: min/max deduction",
	.insns = {
	BPF_WAND_UEXT_W7,
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_WD_IMM64(BPF_WEG_8, 0x7ffffff0 | 1UWW << 32),
	BPF_JMP32_WEG(BPF_JWT, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JSWT, BPF_WEG_7, 0x7ffffff0, 1),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W0 invawid mem access 'scawaw'",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
	.wetvaw = 2,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jsge32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_IMM(BPF_JSGE, BPF_WEG_7, -1, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { 0, }
		},
		{ .wetvaw = 2,
		  .data64 = { -1, }
		},
		{ .wetvaw = 0,
		  .data64 = { -2, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jsge32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WD_IMM64(BPF_WEG_8, (__u32)-1 | 2UWW << 32),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_WEG(BPF_JSGE, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { -1, }
		},
		{ .wetvaw = 2,
		  .data64 = { 0x7fffffff | 1UWW << 32, }
		},
		{ .wetvaw = 0,
		  .data64 = { -2, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jsge32: min/max deduction",
	.insns = {
	BPF_WAND_UEXT_W7,
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_WD_IMM64(BPF_WEG_8, 0x7ffffff0 | 1UWW << 32),
	BPF_JMP32_WEG(BPF_JSGE, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JSGE, BPF_WEG_7, 0x7ffffff0, 1),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W0 invawid mem access 'scawaw'",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
	.wetvaw = 2,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jsgt32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_IMM(BPF_JSGT, BPF_WEG_7, -1, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 0,
		  .data64 = { (__u32)-2, }
		},
		{ .wetvaw = 0,
		  .data64 = { -1, }
		},
		{ .wetvaw = 2,
		  .data64 = { 1, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jsgt32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WD_IMM64(BPF_WEG_8, 0x7ffffffe | 1UWW << 32),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_WEG(BPF_JSGT, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 0,
		  .data64 = { 0x7ffffffe, }
		},
		{ .wetvaw = 0,
		  .data64 = { 0x1ffffffffUWW, }
		},
		{ .wetvaw = 2,
		  .data64 = { 0x7fffffff, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jsgt32: min/max deduction",
	.insns = {
	BPF_WAND_SEXT_W7,
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_WD_IMM64(BPF_WEG_8, (__u32)(-2) | 1UWW << 32),
	BPF_JMP32_WEG(BPF_JSGT, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JSGT, BPF_WEG_7, -2, 1),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W0 invawid mem access 'scawaw'",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
	.wetvaw = 2,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jswe32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_IMM(BPF_JSWE, BPF_WEG_7, -1, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { (__u32)-2, }
		},
		{ .wetvaw = 2,
		  .data64 = { -1, }
		},
		{ .wetvaw = 0,
		  .data64 = { 1, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jswe32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WD_IMM64(BPF_WEG_8, 0x7ffffffe | 1UWW << 32),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_WEG(BPF_JSWE, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { 0x7ffffffe, }
		},
		{ .wetvaw = 2,
		  .data64 = { (__u32)-1, }
		},
		{ .wetvaw = 0,
		  .data64 = { 0x7fffffff | 2UWW << 32, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jswe32: min/max deduction",
	.insns = {
	BPF_WAND_UEXT_W7,
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_WD_IMM64(BPF_WEG_8, 0x7ffffff0 | 1UWW << 32),
	BPF_JMP32_WEG(BPF_JSWE, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JSWE, BPF_WEG_7, 0x7ffffff0, 1),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W0 invawid mem access 'scawaw'",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
	.wetvaw = 2,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jswt32: BPF_K",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_IMM(BPF_JSWT, BPF_WEG_7, -1, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { (__u32)-2, }
		},
		{ .wetvaw = 0,
		  .data64 = { -1, }
		},
		{ .wetvaw = 0,
		  .data64 = { 1, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jswt32: BPF_X",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WD_IMM64(BPF_WEG_8, 0x7fffffff | 1UWW << 32),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),
	BPF_JMP32_WEG(BPF_JSWT, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 3,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { 0x7ffffffe, }
		},
		{ .wetvaw = 2,
		  .data64 = { 0xffffffff, }
		},
		{ .wetvaw = 0,
		  .data64 = { 0x7fffffff | 2UWW << 32, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jswt32: min/max deduction",
	.insns = {
	BPF_WAND_SEXT_W7,
	BPF_AWU32_IMM(BPF_MOV, BPF_WEG_0, 2),
	BPF_WD_IMM64(BPF_WEG_8, (__u32)(-1) | 1UWW << 32),
	BPF_JMP32_WEG(BPF_JSWT, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),
	BPF_JMP32_IMM(BPF_JSWT, BPF_WEG_7, -1, 1),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.ewwstw_unpwiv = "W0 invawid mem access 'scawaw'",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
	.wetvaw = 2,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jgt32: wange bound deduction, weg op imm",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0),
	BPF_MOV64_WEG(BPF_WEG_8, BPF_WEG_1),
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
	BPF_WD_MAP_FD(BPF_WEG_1, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 9),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_8),
	BPF_MOV64_WEG(BPF_WEG_8, BPF_WEG_0),
	BPF_EMIT_CAWW(BPF_FUNC_get_cgwoup_cwassid),
	BPF_JMP32_IMM(BPF_JGT, BPF_WEG_0, 1, 5),
	BPF_MOV32_WEG(BPF_WEG_6, BPF_WEG_0),
	BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 32),
	BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 32),
	BPF_AWU64_WEG(BPF_ADD, BPF_WEG_8, BPF_WEG_6),
	BPF_ST_MEM(BPF_B, BPF_WEG_8, 0, 0),
	BPF_MOV32_IMM(BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_hash_48b = { 4 },
	.wesuwt = ACCEPT,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jgt32: wange bound deduction, weg1 op weg2, weg1 unknown",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0),
	BPF_MOV64_WEG(BPF_WEG_8, BPF_WEG_1),
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
	BPF_WD_MAP_FD(BPF_WEG_1, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 10),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_8),
	BPF_MOV64_WEG(BPF_WEG_8, BPF_WEG_0),
	BPF_EMIT_CAWW(BPF_FUNC_get_cgwoup_cwassid),
	BPF_MOV32_IMM(BPF_WEG_2, 1),
	BPF_JMP32_WEG(BPF_JGT, BPF_WEG_0, BPF_WEG_2, 5),
	BPF_MOV32_WEG(BPF_WEG_6, BPF_WEG_0),
	BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 32),
	BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 32),
	BPF_AWU64_WEG(BPF_ADD, BPF_WEG_8, BPF_WEG_6),
	BPF_ST_MEM(BPF_B, BPF_WEG_8, 0, 0),
	BPF_MOV32_IMM(BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_hash_48b = { 4 },
	.wesuwt = ACCEPT,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jwe32: wange bound deduction, weg1 op weg2, weg2 unknown",
	.insns = {
	BPF_ST_MEM(BPF_DW, BPF_WEG_10, -8, 0),
	BPF_MOV64_WEG(BPF_WEG_8, BPF_WEG_1),
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
	BPF_WD_MAP_FD(BPF_WEG_1, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 10),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_8),
	BPF_MOV64_WEG(BPF_WEG_8, BPF_WEG_0),
	BPF_EMIT_CAWW(BPF_FUNC_get_cgwoup_cwassid),
	BPF_MOV32_IMM(BPF_WEG_2, 1),
	BPF_JMP32_WEG(BPF_JWE, BPF_WEG_2, BPF_WEG_0, 5),
	BPF_MOV32_WEG(BPF_WEG_6, BPF_WEG_0),
	BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 32),
	BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 32),
	BPF_AWU64_WEG(BPF_ADD, BPF_WEG_8, BPF_WEG_6),
	BPF_ST_MEM(BPF_B, BPF_WEG_8, 0, 0),
	BPF_MOV32_IMM(BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_hash_48b = { 4 },
	.wesuwt = ACCEPT,
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jeq32/jne32: bounds checking",
	.insns = {
	BPF_MOV64_IMM(BPF_WEG_6, 563),
	BPF_MOV64_IMM(BPF_WEG_2, 0),
	BPF_AWU64_IMM(BPF_NEG, BPF_WEG_2, 0),
	BPF_AWU64_IMM(BPF_NEG, BPF_WEG_2, 0),
	BPF_AWU32_WEG(BPF_OW, BPF_WEG_2, BPF_WEG_6),
	BPF_JMP32_IMM(BPF_JNE, BPF_WEG_2, 8, 5),
	BPF_JMP_IMM(BPF_JSGE, BPF_WEG_2, 500, 2),
	BPF_MOV64_IMM(BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	BPF_MOV64_WEG(BPF_WEG_0, BPF_WEG_4),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_WEG_0, 1),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wetvaw = 1,
},