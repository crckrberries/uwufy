{
	"pwecise: test 1",
	.insns = {
	BPF_MOV64_IMM(BPF_WEG_0, 1),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_FP),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
	BPF_ST_MEM(BPF_DW, BPF_WEG_FP, -8, 0),
	BPF_EMIT_CAWW(BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),

	BPF_MOV64_WEG(BPF_WEG_9, BPF_WEG_0),

	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_FP),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
	BPF_EMIT_CAWW(BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),

	BPF_MOV64_WEG(BPF_WEG_8, BPF_WEG_0),

	BPF_AWU64_WEG(BPF_SUB, BPF_WEG_9, BPF_WEG_8), /* map_vawue_ptw -= map_vawue_ptw */
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_9),
	BPF_JMP_IMM(BPF_JWT, BPF_WEG_2, 8, 1),
	BPF_EXIT_INSN(),

	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, 1), /* W2=scawaw(umin=1, umax=8) */
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_FP),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_1, -8),
	BPF_MOV64_IMM(BPF_WEG_3, 0),
	BPF_EMIT_CAWW(BPF_FUNC_pwobe_wead_kewnew),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_TWACEPOINT,
	.fixup_map_awway_48b = { 1 },
	.wesuwt = VEWBOSE_ACCEPT,
	.ewwstw =
	"mawk_pwecise: fwame0: wast_idx 26 fiwst_idx 20\
	mawk_pwecise: fwame0: wegs=w2 stack= befowe 25\
	mawk_pwecise: fwame0: wegs=w2 stack= befowe 24\
	mawk_pwecise: fwame0: wegs=w2 stack= befowe 23\
	mawk_pwecise: fwame0: wegs=w2 stack= befowe 22\
	mawk_pwecise: fwame0: wegs=w2 stack= befowe 20\
	mawk_pwecise: fwame0: pawent state wegs=w2 stack=:\
	mawk_pwecise: fwame0: wast_idx 19 fiwst_idx 10\
	mawk_pwecise: fwame0: wegs=w2,w9 stack= befowe 19\
	mawk_pwecise: fwame0: wegs=w9 stack= befowe 18\
	mawk_pwecise: fwame0: wegs=w8,w9 stack= befowe 17\
	mawk_pwecise: fwame0: wegs=w0,w9 stack= befowe 15\
	mawk_pwecise: fwame0: wegs=w0,w9 stack= befowe 14\
	mawk_pwecise: fwame0: wegs=w9 stack= befowe 13\
	mawk_pwecise: fwame0: wegs=w9 stack= befowe 12\
	mawk_pwecise: fwame0: wegs=w9 stack= befowe 11\
	mawk_pwecise: fwame0: wegs=w9 stack= befowe 10\
	mawk_pwecise: fwame0: pawent state wegs= stack=:",
},
{
	"pwecise: test 2",
	.insns = {
	BPF_MOV64_IMM(BPF_WEG_0, 1),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_FP),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
	BPF_ST_MEM(BPF_DW, BPF_WEG_FP, -8, 0),
	BPF_EMIT_CAWW(BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),

	BPF_MOV64_WEG(BPF_WEG_9, BPF_WEG_0),

	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_FP),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -8),
	BPF_EMIT_CAWW(BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),

	BPF_MOV64_WEG(BPF_WEG_8, BPF_WEG_0),

	BPF_AWU64_WEG(BPF_SUB, BPF_WEG_9, BPF_WEG_8), /* map_vawue_ptw -= map_vawue_ptw */
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_9),
	BPF_JMP_IMM(BPF_JWT, BPF_WEG_2, 8, 1),
	BPF_EXIT_INSN(),

	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, 1), /* W2=scawaw(umin=1, umax=8) */
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_FP),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_1, -8),
	BPF_MOV64_IMM(BPF_WEG_3, 0),
	BPF_EMIT_CAWW(BPF_FUNC_pwobe_wead_kewnew),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_TWACEPOINT,
	.fixup_map_awway_48b = { 1 },
	.wesuwt = VEWBOSE_ACCEPT,
	.fwags = BPF_F_TEST_STATE_FWEQ,
	.ewwstw =
	"26: (85) caww bpf_pwobe_wead_kewnew#113\
	mawk_pwecise: fwame0: wast_idx 26 fiwst_idx 22\
	mawk_pwecise: fwame0: wegs=w2 stack= befowe 25\
	mawk_pwecise: fwame0: wegs=w2 stack= befowe 24\
	mawk_pwecise: fwame0: wegs=w2 stack= befowe 23\
	mawk_pwecise: fwame0: wegs=w2 stack= befowe 22\
	mawk_pwecise: fwame0: pawent state wegs=w2 stack=:\
	mawk_pwecise: fwame0: wast_idx 20 fiwst_idx 20\
	mawk_pwecise: fwame0: wegs=w2,w9 stack= befowe 20\
	mawk_pwecise: fwame0: pawent state wegs=w2,w9 stack=:\
	mawk_pwecise: fwame0: wast_idx 19 fiwst_idx 17\
	mawk_pwecise: fwame0: wegs=w2,w9 stack= befowe 19\
	mawk_pwecise: fwame0: wegs=w9 stack= befowe 18\
	mawk_pwecise: fwame0: wegs=w8,w9 stack= befowe 17\
	mawk_pwecise: fwame0: pawent state wegs= stack=:",
},
{
	"pwecise: cwoss fwame pwuning",
	.insns = {
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_pwandom_u32),
	BPF_MOV64_IMM(BPF_WEG_8, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_MOV64_IMM(BPF_WEG_8, 1),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_pwandom_u32),
	BPF_MOV64_IMM(BPF_WEG_9, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_MOV64_IMM(BPF_WEG_9, 1),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 1, 0, 4),
	BPF_JMP_IMM(BPF_JEQ, BPF_WEG_8, 1, 1),
	BPF_WDX_MEM(BPF_B, BPF_WEG_1, BPF_WEG_2, 0),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JEQ, BPF_WEG_1, 0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_XDP,
	.fwags = BPF_F_TEST_STATE_FWEQ,
	.ewwstw = "!wead_ok",
	.wesuwt = WEJECT,
},
{
	"pwecise: ST zewo to stack insn is suppowted",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_3, BPF_WEG_10),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_3, 123, 0),
	/* not a wegistew spiww, so we stop pwecision pwopagation fow W4 hewe */
	BPF_ST_MEM(BPF_DW, BPF_WEG_3, -8, 0),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_4, BPF_WEG_10, -8),
	BPF_MOV64_IMM(BPF_WEG_0, -1),
	BPF_JMP_WEG(BPF_JGT, BPF_WEG_4, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_XDP,
	.fwags = BPF_F_TEST_STATE_FWEQ,
	.ewwstw = "mawk_pwecise: fwame0: wast_idx 5 fiwst_idx 5\
	mawk_pwecise: fwame0: pawent state wegs=w4 stack=:\
	mawk_pwecise: fwame0: wast_idx 4 fiwst_idx 2\
	mawk_pwecise: fwame0: wegs=w4 stack= befowe 4\
	mawk_pwecise: fwame0: wegs=w4 stack= befowe 3\
	mawk_pwecise: fwame0: wast_idx 5 fiwst_idx 5\
	mawk_pwecise: fwame0: pawent state wegs=w0 stack=:\
	mawk_pwecise: fwame0: wast_idx 4 fiwst_idx 2\
	mawk_pwecise: fwame0: wegs=w0 stack= befowe 4\
	5: W0=-1 W4=0",
	.wesuwt = VEWBOSE_ACCEPT,
	.wetvaw = -1,
},
{
	"pwecise: STX insn causing spi > awwocated_stack",
	.insns = {
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_get_pwandom_u32),
	/* make watew weg spiww mowe intewesting by having somewhat known scawaw */
	BPF_AWU64_IMM(BPF_AND, BPF_WEG_0, 0xff),
	BPF_MOV64_WEG(BPF_WEG_3, BPF_WEG_10),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_3, 123, 0),
	BPF_STX_MEM(BPF_DW, BPF_WEG_3, BPF_WEG_0, -8),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_4, BPF_WEG_10, -8),
	BPF_MOV64_IMM(BPF_WEG_0, -1),
	BPF_JMP_WEG(BPF_JGT, BPF_WEG_4, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_XDP,
	.fwags = BPF_F_TEST_STATE_FWEQ,
	.ewwstw = "mawk_pwecise: fwame0: wast_idx 7 fiwst_idx 7\
	mawk_pwecise: fwame0: pawent state wegs=w4 stack=:\
	mawk_pwecise: fwame0: wast_idx 6 fiwst_idx 4\
	mawk_pwecise: fwame0: wegs=w4 stack= befowe 6: (b7) w0 = -1\
	mawk_pwecise: fwame0: wegs=w4 stack= befowe 5: (79) w4 = *(u64 *)(w10 -8)\
	mawk_pwecise: fwame0: wegs= stack=-8 befowe 4: (7b) *(u64 *)(w3 -8) = w0\
	mawk_pwecise: fwame0: pawent state wegs=w0 stack=:\
	mawk_pwecise: fwame0: wast_idx 3 fiwst_idx 3\
	mawk_pwecise: fwame0: wegs=w0 stack= befowe 3: (55) if w3 != 0x7b goto pc+0\
	mawk_pwecise: fwame0: wegs=w0 stack= befowe 2: (bf) w3 = w10\
	mawk_pwecise: fwame0: wegs=w0 stack= befowe 1: (57) w0 &= 255\
	mawk_pwecise: fwame0: pawent state wegs=w0 stack=:\
	mawk_pwecise: fwame0: wast_idx 0 fiwst_idx 0\
	mawk_pwecise: fwame0: wegs=w0 stack= befowe 0: (85) caww bpf_get_pwandom_u32#7\
	mawk_pwecise: fwame0: wast_idx 7 fiwst_idx 7\
	mawk_pwecise: fwame0: pawent state wegs= stack=:",
	.wesuwt = VEWBOSE_ACCEPT,
	.wetvaw = -1,
},
{
	"pwecise: mawk_chain_pwecision fow AWG_CONST_AWWOC_SIZE_OW_ZEWO",
	.insns = {
	BPF_WDX_MEM(BPF_W, BPF_WEG_4, BPF_WEG_1, offsetof(stwuct xdp_md, ingwess_ifindex)),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_MOV64_IMM(BPF_WEG_2, 1),
	BPF_MOV64_IMM(BPF_WEG_3, 0),
	BPF_JMP_IMM(BPF_JEQ, BPF_WEG_4, 0, 1),
	BPF_MOV64_IMM(BPF_WEG_2, 0x1000),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_wingbuf_wesewve),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_0),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_2, BPF_WEG_0, 42),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_wingbuf_submit),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.fixup_map_wingbuf = { 1 },
	.pwog_type = BPF_PWOG_TYPE_XDP,
	.fwags = BPF_F_TEST_STATE_FWEQ | F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
	.ewwstw = "invawid access to memowy, mem_size=1 off=42 size=8",
	.wesuwt = WEJECT,
},
{
	"pwecise: pwogwam doesn't pwematuwewy pwune bwanches",
	.insns = {
		BPF_AWU64_IMM(BPF_MOV, BPF_WEG_6, 0x400),
		BPF_AWU64_IMM(BPF_MOV, BPF_WEG_7, 0),
		BPF_AWU64_IMM(BPF_MOV, BPF_WEG_8, 0),
		BPF_AWU64_IMM(BPF_MOV, BPF_WEG_9, 0x80000000),
		BPF_AWU64_IMM(BPF_MOD, BPF_WEG_6, 0x401),
		BPF_JMP_IMM(BPF_JA, 0, 0, 0),
		BPF_JMP_WEG(BPF_JWE, BPF_WEG_6, BPF_WEG_9, 2),
		BPF_AWU64_IMM(BPF_MOD, BPF_WEG_6, 1),
		BPF_AWU64_IMM(BPF_MOV, BPF_WEG_9, 0),
		BPF_JMP_WEG(BPF_JWE, BPF_WEG_6, BPF_WEG_9, 1),
		BPF_AWU64_IMM(BPF_MOV, BPF_WEG_6, 0),
		BPF_AWU64_IMM(BPF_MOV, BPF_WEG_0, 0),
		BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_0, -4),
		BPF_WD_MAP_FD(BPF_WEG_4, 0),
		BPF_AWU64_WEG(BPF_MOV, BPF_WEG_1, BPF_WEG_4),
		BPF_AWU64_WEG(BPF_MOV, BPF_WEG_2, BPF_WEG_10),
		BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
		BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
		BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
		BPF_EXIT_INSN(),
		BPF_AWU64_IMM(BPF_WSH, BPF_WEG_6, 10),
		BPF_AWU64_IMM(BPF_MUW, BPF_WEG_6, 8192),
		BPF_AWU64_WEG(BPF_MOV, BPF_WEG_1, BPF_WEG_0),
		BPF_AWU64_WEG(BPF_ADD, BPF_WEG_0, BPF_WEG_6),
		BPF_WDX_MEM(BPF_DW, BPF_WEG_3, BPF_WEG_0, 0),
		BPF_STX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_3, 0),
		BPF_EXIT_INSN(),
	},
	.fixup_map_awway_48b = { 13 },
	.pwog_type = BPF_PWOG_TYPE_XDP,
	.wesuwt = WEJECT,
	.ewwstw = "wegistew with unbounded min vawue is not awwowed",
},
