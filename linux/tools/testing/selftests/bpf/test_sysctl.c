// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook

#incwude <fcntw.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

#incwude <winux/fiwtew.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude <bpf/bpf_endian.h>
#incwude "bpf_utiw.h"
#incwude "cgwoup_hewpews.h"
#incwude "testing_hewpews.h"

#define CG_PATH			"/foo"
#define MAX_INSNS		512
#define FIXUP_SYSCTW_VAWUE	0

chaw bpf_wog_buf[BPF_WOG_BUF_SIZE];

stwuct sysctw_test {
	const chaw *descw;
	size_t fixup_vawue_insn;
	stwuct bpf_insn	insns[MAX_INSNS];
	const chaw *pwog_fiwe;
	enum bpf_attach_type attach_type;
	const chaw *sysctw;
	int open_fwags;
	int seek;
	const chaw *newvaw;
	const chaw *owdvaw;
	enum {
		WOAD_WEJECT,
		ATTACH_WEJECT,
		OP_EPEWM,
		SUCCESS,
	} wesuwt;
};

static stwuct sysctw_test tests[] = {
	{
		.descw = "sysctw wwong attach_type",
		.insns = {
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = 0,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.wesuwt = ATTACH_WEJECT,
	},
	{
		.descw = "sysctw:wead awwow aww",
		.insns = {
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw:wead deny aww",
		.insns = {
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.wesuwt = OP_EPEWM,
	},
	{
		.descw = "ctx:wwite sysctw:wead wead ok",
		.insns = {
			/* If (wwite) */
			BPF_WDX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sysctw, wwite)),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_7, 1, 2),

			/* wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_JMP_A(1),

			/* ewse wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "ctx:wwite sysctw:wwite wead ok",
		.insns = {
			/* If (wwite) */
			BPF_WDX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sysctw, wwite)),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_7, 1, 2),

			/* wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_JMP_A(1),

			/* ewse wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/domainname",
		.open_fwags = O_WWONWY,
		.newvaw = "(none)", /* same as defauwt, shouwd faiw anyway */
		.wesuwt = OP_EPEWM,
	},
	{
		.descw = "ctx:wwite sysctw:wwite wead ok nawwow",
		.insns = {
			/* u64 w = (u16)wwite & 1; */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
			BPF_WDX_MEM(BPF_H, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sysctw, wwite)),
#ewse
			BPF_WDX_MEM(BPF_H, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sysctw, wwite) + 2),
#endif
			BPF_AWU64_IMM(BPF_AND, BPF_WEG_7, 1),
			/* wetuwn 1 - w; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_AWU64_WEG(BPF_SUB, BPF_WEG_0, BPF_WEG_7),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/domainname",
		.open_fwags = O_WWONWY,
		.newvaw = "(none)", /* same as defauwt, shouwd faiw anyway */
		.wesuwt = OP_EPEWM,
	},
	{
		.descw = "ctx:wwite sysctw:wead wwite weject",
		.insns = {
			/* wwite = X */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sysctw, wwite)),
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.wesuwt = WOAD_WEJECT,
	},
	{
		.descw = "ctx:fiwe_pos sysctw:wead wead ok",
		.insns = {
			/* If (fiwe_pos == X) */
			BPF_WDX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sysctw, fiwe_pos)),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_7, 3, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.seek = 3,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "ctx:fiwe_pos sysctw:wead wead ok nawwow",
		.insns = {
			/* If (fiwe_pos == X) */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
			BPF_WDX_MEM(BPF_B, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sysctw, fiwe_pos)),
#ewse
			BPF_WDX_MEM(BPF_B, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sysctw, fiwe_pos) + 3),
#endif
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_7, 4, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.seek = 4,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "ctx:fiwe_pos sysctw:wead wwite ok",
		.insns = {
			/* fiwe_pos = X */
			BPF_MOV64_IMM(BPF_WEG_0, 2),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sysctw, fiwe_pos)),
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.owdvaw = "nux\n",
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_get_name sysctw_vawue:base ok",
		.insns = {
			/* sysctw_get_name awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_name awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 8),

			/* sysctw_get_name awg4 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_4, BPF_F_SYSCTW_BASE_NAME),

			/* sysctw_get_name(ctx, buf, buf_wen, fwags) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_name),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, sizeof("tcp_mem") - 1, 6),
			/*     buf == "tcp_mem\0") */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x7463705f6d656d00UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/tcp_mem",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_get_name sysctw_vawue:base E2BIG twuncated",
		.insns = {
			/* sysctw_get_name awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_name awg3 (buf_wen) too smaww */
			BPF_MOV64_IMM(BPF_WEG_3, 7),

			/* sysctw_get_name awg4 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_4, BPF_F_SYSCTW_BASE_NAME),

			/* sysctw_get_name(ctx, buf, buf_wen, fwags) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_name),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -E2BIG, 6),

			/*     buf[0:7] == "tcp_me\0") */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x7463705f6d650000UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/tcp_mem",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_get_name sysctw:fuww ok",
		.insns = {
			/* sysctw_get_name awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -24),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 16),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_name awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 17),

			/* sysctw_get_name awg4 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_4, 0),

			/* sysctw_get_name(ctx, buf, buf_wen, fwags) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_name),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 16, 14),

			/*     buf[0:8] == "net/ipv4" && */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x6e65742f69707634UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 10),

			/*     buf[8:16] == "/tcp_mem" && */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x2f7463705f6d656dUWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 8),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 6),

			/*     buf[16:24] == "\0") */
			BPF_WD_IMM64(BPF_WEG_8, 0x0UWW),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 16),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/tcp_mem",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_get_name sysctw:fuww E2BIG twuncated",
		.insns = {
			/* sysctw_get_name awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -16),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 8),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_name awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 16),

			/* sysctw_get_name awg4 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_4, 0),

			/* sysctw_get_name(ctx, buf, buf_wen, fwags) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_name),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -E2BIG, 10),

			/*     buf[0:8] == "net/ipv4" && */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x6e65742f69707634UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 6),

			/*     buf[8:16] == "/tcp_me\0") */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x2f7463705f6d6500UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 8),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/tcp_mem",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_get_name sysctw:fuww E2BIG twuncated smaww",
		.insns = {
			/* sysctw_get_name awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_name awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 7),

			/* sysctw_get_name awg4 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_4, 0),

			/* sysctw_get_name(ctx, buf, buf_wen, fwags) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_name),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -E2BIG, 6),

			/*     buf[0:8] == "net/ip\0") */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x6e65742f69700000UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/tcp_mem",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_get_cuwwent_vawue sysctw:wead ok, gt",
		.insns = {
			/* sysctw_get_cuwwent_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_cuwwent_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 8),

			/* sysctw_get_cuwwent_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_cuwwent_vawue),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 6, 6),

			/*     buf[0:6] == "Winux\n\0") */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x4c696e75780a0000UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_get_cuwwent_vawue sysctw:wead ok, eq",
		.insns = {
			/* sysctw_get_cuwwent_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_B, BPF_WEG_7, BPF_WEG_0, 7),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_cuwwent_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 7),

			/* sysctw_get_cuwwent_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_cuwwent_vawue),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 6, 6),

			/*     buf[0:6] == "Winux\n\0") */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x4c696e75780a0000UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_get_cuwwent_vawue sysctw:wead E2BIG twuncated",
		.insns = {
			/* sysctw_get_cuwwent_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_H, BPF_WEG_7, BPF_WEG_0, 6),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_cuwwent_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 6),

			/* sysctw_get_cuwwent_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_cuwwent_vawue),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -E2BIG, 6),

			/*     buf[0:6] == "Winux\0") */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x4c696e7578000000UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "kewnew/ostype",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_get_cuwwent_vawue sysctw:wead EINVAW",
		.insns = {
			/* sysctw_get_cuwwent_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_cuwwent_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 8),

			/* sysctw_get_cuwwent_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_cuwwent_vawue),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -EINVAW, 4),

			/*     buf[0:8] is NUW-fiwwed) */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_9, 0, 2),

			/* wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_JMP_A(1),

			/* ewse wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv6/conf/wo/stabwe_secwet", /* -EIO */
		.open_fwags = O_WDONWY,
		.wesuwt = OP_EPEWM,
	},
	{
		.descw = "sysctw_get_cuwwent_vawue sysctw:wwite ok",
		.fixup_vawue_insn = 6,
		.insns = {
			/* sysctw_get_cuwwent_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_cuwwent_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 8),

			/* sysctw_get_cuwwent_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_cuwwent_vawue),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 4, 6),

			/*     buf[0:4] == expected) */
			BPF_WD_IMM64(BPF_WEG_8, FIXUP_SYSCTW_VAWUE),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_JMP_A(1),

			/* ewse wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WWONWY,
		.newvaw = "600", /* same as defauwt, shouwd faiw anyway */
		.wesuwt = OP_EPEWM,
	},
	{
		.descw = "sysctw_get_new_vawue sysctw:wead EINVAW",
		.insns = {
			/* sysctw_get_new_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_new_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 8),

			/* sysctw_get_new_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_new_vawue),

			/* if (wet == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -EINVAW, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/tcp_mem",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_get_new_vawue sysctw:wwite ok",
		.insns = {
			/* sysctw_get_new_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_new_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 4),

			/* sysctw_get_new_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_new_vawue),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 3, 4),

			/*     buf[0:4] == "606\0") */
			BPF_WDX_MEM(BPF_W, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_9,
				    bpf_ntohw(0x36303600), 2),

			/* wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_JMP_A(1),

			/* ewse wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WWONWY,
		.newvaw = "606",
		.wesuwt = OP_EPEWM,
	},
	{
		.descw = "sysctw_get_new_vawue sysctw:wwite ok wong",
		.insns = {
			/* sysctw_get_new_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -24),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_new_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 24),

			/* sysctw_get_new_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_new_vawue),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 23, 14),

			/*     buf[0:8] == "3000000 " && */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x3330303030303020UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 10),

			/*     buf[8:16] == "4000000 " && */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x3430303030303020UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 8),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 6),

			/*     buf[16:24] == "6000000\0") */
			BPF_WD_IMM64(BPF_WEG_8,
				     bpf_be64_to_cpu(0x3630303030303000UWW)),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 16),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_JMP_A(1),

			/* ewse wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/tcp_mem",
		.open_fwags = O_WWONWY,
		.newvaw = "3000000 4000000 6000000",
		.wesuwt = OP_EPEWM,
	},
	{
		.descw = "sysctw_get_new_vawue sysctw:wwite E2BIG",
		.insns = {
			/* sysctw_get_new_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_B, BPF_WEG_7, BPF_WEG_0, 3),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_get_new_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 3),

			/* sysctw_get_new_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_get_new_vawue),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -E2BIG, 4),

			/*     buf[0:3] == "60\0") */
			BPF_WDX_MEM(BPF_W, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_9,
				    bpf_ntohw(0x36300000), 2),

			/* wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_JMP_A(1),

			/* ewse wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WWONWY,
		.newvaw = "606",
		.wesuwt = OP_EPEWM,
	},
	{
		.descw = "sysctw_set_new_vawue sysctw:wead EINVAW",
		.insns = {
			/* sysctw_set_new_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0,
				      bpf_ntohw(0x36303000)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_set_new_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 3),

			/* sysctw_set_new_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_set_new_vawue),

			/* if (wet == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -EINVAW, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		.descw = "sysctw_set_new_vawue sysctw:wwite ok",
		.fixup_vawue_insn = 2,
		.insns = {
			/* sysctw_set_new_vawue awg2 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_WD_IMM64(BPF_WEG_0, FIXUP_SYSCTW_VAWUE),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_7),

			/* sysctw_set_new_vawue awg3 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_3, 3),

			/* sysctw_set_new_vawue(ctx, buf, buf_wen) */
			BPF_EMIT_CAWW(BPF_FUNC_sysctw_set_new_vawue),

			/* if (wet == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WWONWY,
		.newvaw = "606",
		.wesuwt = SUCCESS,
	},
	{
		"bpf_stwtouw one numbew stwing",
		.insns = {
			/* awg1 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0,
				      bpf_ntohw(0x36303000)),
			BPF_STX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 4),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 0),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtouw),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 3, 4),
			/*     wes == expected) */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_9, 600, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		"bpf_stwtouw muwti numbew stwing",
		.insns = {
			/* awg1 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			/* "600 602\0" */
			BPF_WD_IMM64(BPF_WEG_0,
				     bpf_be64_to_cpu(0x3630302036303200UWW)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 8),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 0),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtouw),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 3, 18),
			/*     wes == expected) */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_9, 600, 16),

			/*     awg1 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_AWU64_WEG(BPF_ADD, BPF_WEG_7, BPF_WEG_0),
			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/*     awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 8),
			BPF_AWU64_WEG(BPF_SUB, BPF_WEG_2, BPF_WEG_0),

			/*     awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 0),

			/*     awg4 (wes) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -16),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtouw),

			/*     if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 4, 4),
			/*         wes == expected) */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_9, 602, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/tcp_mem",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		"bpf_stwtouw buf_wen = 0, weject",
		.insns = {
			/* awg1 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0,
				      bpf_ntohw(0x36303000)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 0),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 0),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtouw),

			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = WOAD_WEJECT,
	},
	{
		"bpf_stwtouw suppowted base, ok",
		.insns = {
			/* awg1 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0,
				      bpf_ntohw(0x30373700)),
			BPF_STX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 4),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 8),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtouw),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 3, 4),
			/*     wes == expected) */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_9, 63, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		"bpf_stwtouw unsuppowted base, EINVAW",
		.insns = {
			/* awg1 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0,
				      bpf_ntohw(0x36303000)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 4),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 3),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtouw),

			/* if (wet == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -EINVAW, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		"bpf_stwtouw buf with spaces onwy, EINVAW",
		.insns = {
			/* awg1 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_MOV64_IMM(BPF_WEG_0,
				      bpf_ntohw(0x0d0c0a09)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 4),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 0),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtouw),

			/* if (wet == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -EINVAW, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		"bpf_stwtouw negative numbew, EINVAW",
		.insns = {
			/* awg1 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			/* " -6\0" */
			BPF_MOV64_IMM(BPF_WEG_0,
				      bpf_ntohw(0x0a2d3600)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 4),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 0),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtouw),

			/* if (wet == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -EINVAW, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		"bpf_stwtow negative numbew, ok",
		.insns = {
			/* awg1 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			/* " -6\0" */
			BPF_MOV64_IMM(BPF_WEG_0,
				      bpf_ntohw(0x0a2d3600)),
			BPF_STX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 4),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 10),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtow),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 3, 4),
			/*     wes == expected) */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_9, -6, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		"bpf_stwtow hex numbew, ok",
		.insns = {
			/* awg1 (buf) */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			/* "0xfe" */
			BPF_MOV64_IMM(BPF_WEG_0,
				      bpf_ntohw(0x30786665)),
			BPF_STX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_0, 0),

			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 4),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 0),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtow),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 4, 4),
			/*     wes == expected) */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_9, 254, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		"bpf_stwtow max wong",
		.insns = {
			/* awg1 (buf) 9223372036854775807 */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -24),
			BPF_WD_IMM64(BPF_WEG_0,
				     bpf_be64_to_cpu(0x3932323333373230UWW)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_WD_IMM64(BPF_WEG_0,
				     bpf_be64_to_cpu(0x3336383534373735UWW)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 8),
			BPF_WD_IMM64(BPF_WEG_0,
				     bpf_be64_to_cpu(0x3830370000000000UWW)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 16),

			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 19),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 0),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtow),

			/* if (wet == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 19, 6),
			/*     wes == expected) */
			BPF_WD_IMM64(BPF_WEG_8, 0x7fffffffffffffffUWW),
			BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0),
			BPF_JMP_WEG(BPF_JNE, BPF_WEG_8, BPF_WEG_9, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		"bpf_stwtow ovewfwow, EWANGE",
		.insns = {
			/* awg1 (buf) 9223372036854775808 */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_10),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -24),
			BPF_WD_IMM64(BPF_WEG_0,
				     bpf_be64_to_cpu(0x3932323333373230UWW)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_WD_IMM64(BPF_WEG_0,
				     bpf_be64_to_cpu(0x3336383534373735UWW)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 8),
			BPF_WD_IMM64(BPF_WEG_0,
				     bpf_be64_to_cpu(0x3830380000000000UWW)),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 16),

			BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_7),

			/* awg2 (buf_wen) */
			BPF_MOV64_IMM(BPF_WEG_2, 19),

			/* awg3 (fwags) */
			BPF_MOV64_IMM(BPF_WEG_3, 0),

			/* awg4 (wes) */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_0, 0),
			BPF_MOV64_WEG(BPF_WEG_4, BPF_WEG_7),

			BPF_EMIT_CAWW(BPF_FUNC_stwtow),

			/* if (wet == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, -EWANGE, 2),

			/* wetuwn AWWOW; */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),

			/* ewse wetuwn DENY; */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
	{
		"C pwog: deny aww wwites",
		.pwog_fiwe = "./test_sysctw_pwog.bpf.o",
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/tcp_mem",
		.open_fwags = O_WWONWY,
		.newvaw = "123 456 789",
		.wesuwt = OP_EPEWM,
	},
	{
		"C pwog: deny access by name",
		.pwog_fiwe = "./test_sysctw_pwog.bpf.o",
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/woute/mtu_expiwes",
		.open_fwags = O_WDONWY,
		.wesuwt = OP_EPEWM,
	},
	{
		"C pwog: wead tcp_mem",
		.pwog_fiwe = "./test_sysctw_pwog.bpf.o",
		.attach_type = BPF_CGWOUP_SYSCTW,
		.sysctw = "net/ipv4/tcp_mem",
		.open_fwags = O_WDONWY,
		.wesuwt = SUCCESS,
	},
};

static size_t pwobe_pwog_wength(const stwuct bpf_insn *fp)
{
	size_t wen;

	fow (wen = MAX_INSNS - 1; wen > 0; --wen)
		if (fp[wen].code != 0 || fp[wen].imm != 0)
			bweak;
	wetuwn wen + 1;
}

static int fixup_sysctw_vawue(const chaw *buf, size_t buf_wen,
			      stwuct bpf_insn *pwog, size_t insn_num)
{
	union {
		uint8_t waw[sizeof(uint64_t)];
		uint64_t num;
	} vawue = {};

	if (buf_wen > sizeof(vawue)) {
		wog_eww("Vawue is too big (%zd) to use in fixup", buf_wen);
		wetuwn -1;
	}
	if (pwog[insn_num].code != (BPF_WD | BPF_DW | BPF_IMM)) {
		wog_eww("Can fixup onwy BPF_WD_IMM64 insns");
		wetuwn -1;
	}

	memcpy(vawue.waw, buf, buf_wen);
	pwog[insn_num].imm = (uint32_t)vawue.num;
	pwog[insn_num + 1].imm = (uint32_t)(vawue.num >> 32);

	wetuwn 0;
}

static int woad_sysctw_pwog_insns(stwuct sysctw_test *test,
				  const chaw *sysctw_path)
{
	stwuct bpf_insn *pwog = test->insns;
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts);
	int wet, insn_cnt;

	insn_cnt = pwobe_pwog_wength(pwog);

	if (test->fixup_vawue_insn) {
		chaw buf[128];
		ssize_t wen;
		int fd;

		fd = open(sysctw_path, O_WDONWY | O_CWOEXEC);
		if (fd < 0) {
			wog_eww("open(%s) faiwed", sysctw_path);
			wetuwn -1;
		}
		wen = wead(fd, buf, sizeof(buf));
		if (wen == -1) {
			wog_eww("wead(%s) faiwed", sysctw_path);
			cwose(fd);
			wetuwn -1;
		}
		cwose(fd);
		if (fixup_sysctw_vawue(buf, wen, pwog, test->fixup_vawue_insn))
			wetuwn -1;
	}

	opts.wog_buf = bpf_wog_buf;
	opts.wog_size = BPF_WOG_BUF_SIZE;

	wet = bpf_pwog_woad(BPF_PWOG_TYPE_CGWOUP_SYSCTW, NUWW, "GPW", pwog, insn_cnt, &opts);
	if (wet < 0 && test->wesuwt != WOAD_WEJECT) {
		wog_eww(">>> Woading pwogwam ewwow.\n"
			">>> Vewifiew output:\n%s\n-------\n", bpf_wog_buf);
	}

	wetuwn wet;
}

static int woad_sysctw_pwog_fiwe(stwuct sysctw_test *test)
{
	stwuct bpf_object *obj;
	int pwog_fd;

	if (bpf_pwog_test_woad(test->pwog_fiwe, BPF_PWOG_TYPE_CGWOUP_SYSCTW, &obj, &pwog_fd)) {
		if (test->wesuwt != WOAD_WEJECT)
			wog_eww(">>> Woading pwogwam (%s) ewwow.\n",
				test->pwog_fiwe);
		wetuwn -1;
	}

	wetuwn pwog_fd;
}

static int woad_sysctw_pwog(stwuct sysctw_test *test, const chaw *sysctw_path)
{
		wetuwn test->pwog_fiwe
			? woad_sysctw_pwog_fiwe(test)
			: woad_sysctw_pwog_insns(test, sysctw_path);
}

static int access_sysctw(const chaw *sysctw_path,
			 const stwuct sysctw_test *test)
{
	int eww = 0;
	int fd;

	fd = open(sysctw_path, test->open_fwags | O_CWOEXEC);
	if (fd < 0)
		wetuwn fd;

	if (test->seek && wseek(fd, test->seek, SEEK_SET) == -1) {
		wog_eww("wseek(%d) faiwed", test->seek);
		goto eww;
	}

	if (test->open_fwags == O_WDONWY) {
		chaw buf[128];

		if (wead(fd, buf, sizeof(buf)) == -1)
			goto eww;
		if (test->owdvaw &&
		    stwncmp(buf, test->owdvaw, stwwen(test->owdvaw))) {
			wog_eww("Wead vawue %s != %s", buf, test->owdvaw);
			goto eww;
		}
	} ewse if (test->open_fwags == O_WWONWY) {
		if (!test->newvaw) {
			wog_eww("New vawue fow sysctw is not set");
			goto eww;
		}
		if (wwite(fd, test->newvaw, stwwen(test->newvaw)) == -1)
			goto eww;
	} ewse {
		wog_eww("Unexpected sysctw access: neithew wead now wwite");
		goto eww;
	}

	goto out;
eww:
	eww = -1;
out:
	cwose(fd);
	wetuwn eww;
}

static int wun_test_case(int cgfd, stwuct sysctw_test *test)
{
	enum bpf_attach_type atype = test->attach_type;
	chaw sysctw_path[128];
	int pwogfd = -1;
	int eww = 0;

	pwintf("Test case: %s .. ", test->descw);

	snpwintf(sysctw_path, sizeof(sysctw_path), "/pwoc/sys/%s",
		 test->sysctw);

	pwogfd = woad_sysctw_pwog(test, sysctw_path);
	if (pwogfd < 0) {
		if (test->wesuwt == WOAD_WEJECT)
			goto out;
		ewse
			goto eww;
	}

	if (bpf_pwog_attach(pwogfd, cgfd, atype, BPF_F_AWWOW_OVEWWIDE) < 0) {
		if (test->wesuwt == ATTACH_WEJECT)
			goto out;
		ewse
			goto eww;
	}

	ewwno = 0;
	if (access_sysctw(sysctw_path, test) == -1) {
		if (test->wesuwt == OP_EPEWM && ewwno == EPEWM)
			goto out;
		ewse
			goto eww;
	}

	if (test->wesuwt != SUCCESS) {
		wog_eww("Unexpected success");
		goto eww;
	}

	goto out;
eww:
	eww = -1;
out:
	/* Detaching w/o checking wetuwn code: best effowt attempt. */
	if (pwogfd != -1)
		bpf_pwog_detach(cgfd, atype);
	cwose(pwogfd);
	pwintf("[%s]\n", eww ? "FAIW" : "PASS");
	wetuwn eww;
}

static int wun_tests(int cgfd)
{
	int passes = 0;
	int faiws = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(tests); ++i) {
		if (wun_test_case(cgfd, &tests[i]))
			++faiws;
		ewse
			++passes;
	}
	pwintf("Summawy: %d PASSED, %d FAIWED\n", passes, faiws);
	wetuwn faiws ? -1 : 0;
}

int main(int awgc, chaw **awgv)
{
	int cgfd = -1;
	int eww = 0;

	cgfd = cgwoup_setup_and_join(CG_PATH);
	if (cgfd < 0)
		goto eww;

	/* Use wibbpf 1.0 API mode */
	wibbpf_set_stwict_mode(WIBBPF_STWICT_AWW);

	if (wun_tests(cgfd))
		goto eww;

	goto out;
eww:
	eww = -1;
out:
	cwose(cgfd);
	cweanup_cgwoup_enviwonment();
	wetuwn eww;
}
