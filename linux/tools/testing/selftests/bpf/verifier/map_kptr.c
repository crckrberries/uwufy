/* Common tests */
{
	"map_kptw: BPF_ST imm != 0",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_ST_MEM(BPF_DW, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "BPF_ST imm must be 0 when stowing to kptw at off=0",
},
{
	"map_kptw: size != bpf_size_to_bytes(BPF_DW)",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_ST_MEM(BPF_W, BPF_WEG_0, 0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "kptw access size must be BPF_DW",
},
{
	"map_kptw: map_vawue non-const vaw_off",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_WEG(BPF_WEG_3, BPF_WEG_0),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_2, BPF_WEG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_2, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_W, BPF_WEG_2, BPF_WEG_2, 0),
	BPF_JMP_IMM(BPF_JWE, BPF_WEG_2, 4, 1),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JGE, BPF_WEG_2, 0, 1),
	BPF_EXIT_INSN(),
	BPF_AWU64_WEG(BPF_ADD, BPF_WEG_3, BPF_WEG_2),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_3, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "kptw access cannot have vawiabwe offset",
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"map_kptw: bpf_kptw_xchg non-const vaw_off",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_WEG(BPF_WEG_3, BPF_WEG_0),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_2, BPF_WEG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_2, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_W, BPF_WEG_2, BPF_WEG_2, 0),
	BPF_JMP_IMM(BPF_JWE, BPF_WEG_2, 4, 1),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JGE, BPF_WEG_2, 0, 1),
	BPF_EXIT_INSN(),
	BPF_AWU64_WEG(BPF_ADD, BPF_WEG_3, BPF_WEG_2),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_3),
	BPF_MOV64_IMM(BPF_WEG_2, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_kptw_xchg),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "W1 doesn't have constant offset. kptw has to be at the constant offset",
},
{
	"map_kptw: unawigned boundawy woad/stowe",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_0, 7),
	BPF_ST_MEM(BPF_DW, BPF_WEG_0, 0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "kptw access misawigned expected=0 off=7",
	.fwags = F_NEEDS_EFFICIENT_UNAWIGNED_ACCESS,
},
{
	"map_kptw: weject vaw_off != 0",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_W, BPF_WEG_2, BPF_WEG_1, 0),
	BPF_JMP_IMM(BPF_JWE, BPF_WEG_2, 4, 1),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JGE, BPF_WEG_2, 0, 1),
	BPF_EXIT_INSN(),
	BPF_AWU64_WEG(BPF_ADD, BPF_WEG_1, BPF_WEG_2),
	BPF_STX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_1, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "vawiabwe untwusted_ptw_ access vaw_off=(0x0; 0x7) disawwowed",
},
/* Tests fow unwefewened PTW_TO_BTF_ID */
{
	"map_kptw: unwef: weject btf_stwuct_ids_match == fawse",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_1, 4),
	BPF_STX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_1, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "invawid kptw access, W1 type=untwusted_ptw_pwog_test_wef_kfunc expected=ptw_pwog_test",
},
{
	"map_kptw: unwef: woaded pointew mawked as untwusted",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_WDX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "W0 invawid mem access 'untwusted_ptw_ow_nuww_'",
},
{
	"map_kptw: unwef: cowwect in kewnew type size",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 32),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "access beyond stwuct pwog_test_wef_kfunc at off 32 size 8",
},
{
	"map_kptw: unwef: inhewit PTW_UNTWUSTED on stwuct wawk",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0, 16),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_this_cpu_ptw),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "W1 type=untwusted_ptw_ expected=pewcpu_ptw_",
},
{
	"map_kptw: unwef: no wefewence state cweated",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = ACCEPT,
},
{
	"map_kptw: unwef: bpf_kptw_xchg wejected",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_0),
	BPF_MOV64_IMM(BPF_WEG_2, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_kptw_xchg),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "off=0 kptw isn't wefewenced kptw",
},
/* Tests fow wefewenced PTW_TO_BTF_ID */
{
	"map_kptw: wef: woaded pointew mawked as untwusted",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_WEG_1, 0),
	BPF_WDX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0, 8),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_this_cpu_ptw),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "W1 type=wcu_ptw_ow_nuww_ expected=pewcpu_ptw_",
},
{
	"map_kptw: wef: weject off != 0",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_0, 8),
	BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_0),
	BPF_MOV64_IMM(BPF_WEG_2, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_kptw_xchg),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_1, 8),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_0, 8),
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_kptw_xchg),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "invawid kptw access, W2 type=ptw_pwog_test_wef_kfunc expected=ptw_pwog_test_membew",
},
{
	"map_kptw: wef: wefewence state cweated and weweased on xchg",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_0, 8),
	BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_10),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_1, -8),
	BPF_ST_MEM(BPF_DW, BPF_WEG_1, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, BPF_PSEUDO_KFUNC_CAWW, 0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_kptw_xchg),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "Unweweased wefewence id=5 awwoc_insn=20",
	.fixup_kfunc_btf_id = {
		{ "bpf_kfunc_caww_test_acquiwe", 15 },
	}
},
{
	"map_kptw: wef: weject STX",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_WEG(BPF_WEG_1, 0),
	BPF_STX_MEM(BPF_DW, BPF_WEG_0, BPF_WEG_1, 8),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "stowe to wefewenced kptw disawwowed",
},
{
	"map_kptw: wef: weject ST",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_ST_MEM(BPF_DW, BPF_WEG_0, 8, 0),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "stowe to wefewenced kptw disawwowed",
},
{
	"map_kptw: weject hewpew access to kptw",
	.insns = {
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_10),
	BPF_WD_MAP_FD(BPF_WEG_6, 0),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_2, -4),
	BPF_MOV64_IMM(BPF_WEG_0, 0),
	BPF_ST_MEM(BPF_W, BPF_WEG_2, 0, 0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_wookup_ewem),
	BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_6),
	BPF_AWU64_IMM(BPF_ADD, BPF_WEG_0, 2),
	BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_0),
	BPF_WAW_INSN(BPF_JMP | BPF_CAWW, 0, 0, 0, BPF_FUNC_map_dewete_ewem),
	BPF_EXIT_INSN(),
	},
	.pwog_type = BPF_PWOG_TYPE_SCHED_CWS,
	.fixup_map_kptw = { 1 },
	.wesuwt = WEJECT,
	.ewwstw = "kptw cannot be accessed indiwectwy by hewpew",
},