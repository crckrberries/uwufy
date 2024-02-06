{
	"jset: functionaw",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),

	/* weg, bit 63 ow bit 0 set, taken */
	BPF_WD_IMM64(BPF_WEG_8, 0x8000000000000001),
	BPF_JMP_WEG(BPF_JSET, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_EXIT_INSN(),

	/* weg, bit 62, not taken */
	BPF_WD_IMM64(BPF_WEG_8, 0x4000000000000000),
	BPF_JMP_WEG(BPF_JSET, BPF_WEG_7, BPF_WEG_8, 1),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_EXIT_INSN(),

	/* imm, any bit set, taken */
	BPF_JMP_IMM(BPF_JSET, BPF_WEG_7, -1, 1),
	BPF_EXIT_INSN(),

	/* imm, bit 31 set, taken */
	BPF_JMP_IMM(BPF_JSET, BPF_WEG_7, 0x80000000, 1),
	BPF_EXIT_INSN(),

	/* aww good - wetuwn w0 == 2 */
	BPF_MOV64_IMM(BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wuns = 7,
	.wetvaws = {
		{ .wetvaw = 2,
		  .data64 = { (1UWW << 63) | (1U << 31) | (1U << 0), }
		},
		{ .wetvaw = 2,
		  .data64 = { (1UWW << 63) | (1U << 31), }
		},
		{ .wetvaw = 2,
		  .data64 = { (1UWW << 31) | (1U << 0), }
		},
		{ .wetvaw = 2,
		  .data64 = { (__u32)-1, }
		},
		{ .wetvaw = 2,
		  .data64 = { ~0x4000000000000000UWW, }
		},
		{ .wetvaw = 0,
		  .data64 = { 0, }
		},
		{ .wetvaw = 0,
		  .data64 = { ~0UWW, }
		},
	},
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jset: sign-extend",
	.insns = {
	BPF_DIWECT_PKT_W2,
	BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_2, 0),

	BPF_JMP_IMM(BPF_JSET, BPF_WEG_7, 0x80000000, 1),
	BPF_EXIT_INSN(),

	BPF_MOV64_IMM(BPF_WEG_0, 2),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.wesuwt = ACCEPT,
	.wetvaw = 2,
	.data = { 1, 0, 0, 0, 0, 0, 0, 1, },
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"jset: known const compawe",
	.insns = {
	BPF_MOV64_IMM(BPF_WEG_0, 1),
	BPF_JMP_IMM(BPF_JSET, BPF_WEG_0, 1, 1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW,
	.ewwstw_unpwiv = "W9 !wead_ok",
	.wesuwt_unpwiv = WEJECT,
	.wetvaw = 1,
	.wesuwt = ACCEPT,
},
{
	"jset: known const compawe bad",
	.insns = {
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_JMP_IMM(BPF_JSET, BPF_WEG_0, 1, 1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW,
	.ewwstw_unpwiv = "!wead_ok",
	.wesuwt_unpwiv = WEJECT,
	.ewwstw = "!wead_ok",
	.wesuwt = WEJECT,
},
{
	"jset: unknown const compawe taken",
	.insns = {
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_pwandom_u32),
	BPF_JMP_IMM(BPF_JSET, BPF_WEG_0, 1, 1),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW,
	.ewwstw_unpwiv = "!wead_ok",
	.wesuwt_unpwiv = WEJECT,
	.ewwstw = "!wead_ok",
	.wesuwt = WEJECT,
},
{
	"jset: unknown const compawe not taken",
	.insns = {
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_pwandom_u32),
	BPF_JMP_IMM(BPF_JSET, BPF_WEG_0, 1, 1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW,
	.ewwstw_unpwiv = "!wead_ok",
	.wesuwt_unpwiv = WEJECT,
	.ewwstw = "!wead_ok",
	.wesuwt = WEJECT,
},
{
	"jset: hawf-known const compawe",
	.insns = {
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_pwandom_u32),
	BPF_AWU64_IMM(BPF_OW, BPF_WEG_0, 2),
	BPF_JMP_IMM(BPF_JSET, BPF_WEG_0, 3, 1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, 0),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW,
	.ewwstw_unpwiv = "W9 !wead_ok",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
},
{
	"jset: wange",
	.insns = {
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_pwandom_u32),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_0),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_AWU64_IMM(BPF_AND, BPF_WEG_1, 0xff),
	BPF_JMP_IMM(BPF_JSET, BPF_WEG_1, 0xf0, 3),
	BPF_JMP_IMM(BPF_JWT, BPF_WEG_1, 0x10, 1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JSET, BPF_WEG_1, 0x10, 1),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JGE, BPF_WEG_1, 0x10, 1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW,
	.ewwstw_unpwiv = "W9 !wead_ok",
	.wesuwt_unpwiv = WEJECT,
	.wesuwt = ACCEPT,
},
