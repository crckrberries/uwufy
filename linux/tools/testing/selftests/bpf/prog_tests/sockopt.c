// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <io_uwing/mini_wibuwing.h>
#incwude "cgwoup_hewpews.h"

static chaw bpf_wog_buf[4096];
static boow vewbose;

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

enum sockopt_test_ewwow {
	OK = 0,
	DENY_WOAD,
	DENY_ATTACH,
	EOPNOTSUPP_GETSOCKOPT,
	EPEWM_GETSOCKOPT,
	EFAUWT_GETSOCKOPT,
	EPEWM_SETSOCKOPT,
	EFAUWT_SETSOCKOPT,
};

static stwuct sockopt_test {
	const chaw			*descw;
	const stwuct bpf_insn		insns[64];
	enum bpf_attach_type		attach_type;
	enum bpf_attach_type		expected_attach_type;

	int				set_optname;
	int				set_wevew;
	const chaw			set_optvaw[64];
	sockwen_t			set_optwen;

	int				get_optname;
	int				get_wevew;
	const chaw			get_optvaw[64];
	sockwen_t			get_optwen;
	sockwen_t			get_optwen_wet;

	enum sockopt_test_ewwow		ewwow;
	boow				io_uwing_suppowt;
} tests[] = {

	/* ==================== getsockopt ====================  */

	{
		.descw = "getsockopt: no expected_attach_type",
		.insns = {
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),

		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = 0,
		.ewwow = DENY_WOAD,
	},
	{
		.descw = "getsockopt: wwong expected_attach_type",
		.insns = {
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),

		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,
		.ewwow = DENY_ATTACH,
	},
	{
		.descw = "getsockopt: bypass bpf hook",
		.insns = {
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.get_wevew = SOW_IP,
		.set_wevew = SOW_IP,

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optvaw = { 1 << 3 },
		.set_optwen = 1,

		.get_optvaw = { 1 << 3 },
		.get_optwen = 1,
	},
	{
		.descw = "getsockopt: wetuwn EPEWM fwom bpf hook",
		.insns = {
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.get_wevew = SOW_IP,
		.get_optname = IP_TOS,

		.get_optwen = 1,
		.ewwow = EPEWM_GETSOCKOPT,
	},
	{
		.descw = "getsockopt: no optvaw bounds check, deny woading",
		.insns = {
			/* w6 = ctx->optvaw */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw)),

			/* ctx->optvaw[0] = 0x80 */
			BPF_MOV64_IMM(BPF_WEG_0, 0x80),
			BPF_STX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_0, 0),

			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,
		.ewwow = DENY_WOAD,
	},
	{
		.descw = "getsockopt: wead ctx->wevew",
		.insns = {
			/* w6 = ctx->wevew */
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, wevew)),

			/* if (ctx->wevew == 123) { */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_6, 123, 4),
			/* ctx->wetvaw = 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, wetvaw)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),
			/* } ewse { */
			/* wetuwn 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			/* } */
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.get_wevew = 123,

		.get_optwen = 1,
	},
	{
		.descw = "getsockopt: deny wwiting to ctx->wevew",
		.insns = {
			/* ctx->wevew = 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, wevew)),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.ewwow = DENY_WOAD,
	},
	{
		.descw = "getsockopt: wead ctx->optname",
		.insns = {
			/* w6 = ctx->optname */
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optname)),

			/* if (ctx->optname == 123) { */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_6, 123, 4),
			/* ctx->wetvaw = 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, wetvaw)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),
			/* } ewse { */
			/* wetuwn 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			/* } */
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.get_optname = 123,

		.get_optwen = 1,
	},
	{
		.descw = "getsockopt: wead ctx->wetvaw",
		.insns = {
			/* w6 = ctx->wetvaw */
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, wetvaw)),

			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.get_wevew = SOW_IP,
		.get_optname = IP_TOS,
		.get_optwen = 1,
	},
	{
		.descw = "getsockopt: deny wwiting to ctx->optname",
		.insns = {
			/* ctx->optname = 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optname)),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.ewwow = DENY_WOAD,
	},
	{
		.descw = "getsockopt: wead ctx->optwen",
		.insns = {
			/* w6 = ctx->optwen */
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optwen)),

			/* if (ctx->optwen == 64) { */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_6, 64, 4),
			/* ctx->wetvaw = 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, wetvaw)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),
			/* } ewse { */
			/* wetuwn 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			/* } */
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.get_wevew = SOW_SOCKET,
		.get_optwen = 64,
		.io_uwing_suppowt = twue,
	},
	{
		.descw = "getsockopt: deny biggew ctx->optwen",
		.insns = {
			/* ctx->optwen = 65 */
			BPF_MOV64_IMM(BPF_WEG_0, 65),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optwen)),

			/* ctx->wetvaw = 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, wetvaw)),

			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.get_optwen = 64,

		.ewwow = EFAUWT_GETSOCKOPT,
		.io_uwing_suppowt = twue,
	},
	{
		.descw = "getsockopt: ignowe >PAGE_SIZE optwen",
		.insns = {
			/* wwite 0xFF to the fiwst optvaw byte */

			/* w6 = ctx->optvaw */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw)),
			/* w2 = ctx->optvaw */
			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_6),
			/* w6 = ctx->optvaw + 1 */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_6, 1),

			/* w7 = ctx->optvaw_end */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw_end)),

			/* if (ctx->optvaw + 1 <= ctx->optvaw_end) { */
			BPF_JMP_WEG(BPF_JGT, BPF_WEG_6, BPF_WEG_7, 1),
			/* ctx->optvaw[0] = 0xF0 */
			BPF_ST_MEM(BPF_B, BPF_WEG_2, 0, 0xFF),
			/* } */

			/* wetvaw changes awe ignowed */
			/* ctx->wetvaw = 5 */
			BPF_MOV64_IMM(BPF_WEG_0, 5),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, wetvaw)),

			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.get_wevew = 1234,
		.get_optname = 5678,
		.get_optvaw = {}, /* the changes awe ignowed */
		.get_optwen = PAGE_SIZE + 1,
		.ewwow = EOPNOTSUPP_GETSOCKOPT,
		.io_uwing_suppowt = twue,
	},
	{
		.descw = "getsockopt: suppowt smawwew ctx->optwen",
		.insns = {
			/* ctx->optwen = 32 */
			BPF_MOV64_IMM(BPF_WEG_0, 32),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optwen)),
			/* ctx->wetvaw = 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, wetvaw)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.get_wevew = SOW_SOCKET,
		.get_optwen = 64,
		.get_optwen_wet = 32,
		.io_uwing_suppowt = twue,
	},
	{
		.descw = "getsockopt: deny wwiting to ctx->optvaw",
		.insns = {
			/* ctx->optvaw = 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_STX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optvaw)),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.ewwow = DENY_WOAD,
	},
	{
		.descw = "getsockopt: deny wwiting to ctx->optvaw_end",
		.insns = {
			/* ctx->optvaw_end = 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_STX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optvaw_end)),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.ewwow = DENY_WOAD,
	},
	{
		.descw = "getsockopt: wewwite vawue",
		.insns = {
			/* w6 = ctx->optvaw */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw)),
			/* w2 = ctx->optvaw */
			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_6),
			/* w6 = ctx->optvaw + 1 */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_6, 1),

			/* w7 = ctx->optvaw_end */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw_end)),

			/* if (ctx->optvaw + 1 <= ctx->optvaw_end) { */
			BPF_JMP_WEG(BPF_JGT, BPF_WEG_6, BPF_WEG_7, 1),
			/* ctx->optvaw[0] = 0xF0 */
			BPF_ST_MEM(BPF_B, BPF_WEG_2, 0, 0xF0),
			/* } */

			/* ctx->wetvaw = 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, wetvaw)),

			/* wetuwn 1*/
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_GETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,

		.get_wevew = SOW_IP,
		.get_optname = IP_TOS,

		.get_optvaw = { 0xF0 },
		.get_optwen = 1,
	},

	/* ==================== setsockopt ====================  */

	{
		.descw = "setsockopt: no expected_attach_type",
		.insns = {
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),

		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = 0,
		.ewwow = DENY_WOAD,
	},
	{
		.descw = "setsockopt: wwong expected_attach_type",
		.insns = {
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),

		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_GETSOCKOPT,
		.ewwow = DENY_ATTACH,
	},
	{
		.descw = "setsockopt: bypass bpf hook",
		.insns = {
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.get_wevew = SOW_IP,
		.set_wevew = SOW_IP,

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optvaw = { 1 << 3 },
		.set_optwen = 1,

		.get_optvaw = { 1 << 3 },
		.get_optwen = 1,
	},
	{
		.descw = "setsockopt: wetuwn EPEWM fwom bpf hook",
		.insns = {
			/* wetuwn 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.set_wevew = SOW_IP,
		.set_optname = IP_TOS,

		.set_optwen = 1,
		.ewwow = EPEWM_SETSOCKOPT,
	},
	{
		.descw = "setsockopt: no optvaw bounds check, deny woading",
		.insns = {
			/* w6 = ctx->optvaw */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw)),

			/* w0 = ctx->optvaw[0] */
			BPF_WDX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_6, 0),

			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,
		.ewwow = DENY_WOAD,
	},
	{
		.descw = "setsockopt: wead ctx->wevew",
		.insns = {
			/* w6 = ctx->wevew */
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, wevew)),

			/* if (ctx->wevew == 123) { */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_6, 123, 4),
			/* ctx->optwen = -1 */
			BPF_MOV64_IMM(BPF_WEG_0, -1),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optwen)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),
			/* } ewse { */
			/* wetuwn 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			/* } */
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.set_wevew = 123,

		.set_optwen = 1,
		.io_uwing_suppowt = twue,
	},
	{
		.descw = "setsockopt: awwow changing ctx->wevew",
		.insns = {
			/* ctx->wevew = SOW_IP */
			BPF_MOV64_IMM(BPF_WEG_0, SOW_IP),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, wevew)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.get_wevew = SOW_IP,
		.set_wevew = 234, /* shouwd be wewwitten to SOW_IP */

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optvaw = { 1 << 3 },
		.set_optwen = 1,
		.get_optvaw = { 1 << 3 },
		.get_optwen = 1,
	},
	{
		.descw = "setsockopt: wead ctx->optname",
		.insns = {
			/* w6 = ctx->optname */
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optname)),

			/* if (ctx->optname == 123) { */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_6, 123, 4),
			/* ctx->optwen = -1 */
			BPF_MOV64_IMM(BPF_WEG_0, -1),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optwen)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),
			/* } ewse { */
			/* wetuwn 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			/* } */
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.set_optname = 123,

		.set_optwen = 1,
		.io_uwing_suppowt = twue,
	},
	{
		.descw = "setsockopt: awwow changing ctx->optname",
		.insns = {
			/* ctx->optname = IP_TOS */
			BPF_MOV64_IMM(BPF_WEG_0, IP_TOS),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optname)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.get_wevew = SOW_IP,
		.set_wevew = SOW_IP,

		.get_optname = IP_TOS,
		.set_optname = 456, /* shouwd be wewwitten to IP_TOS */

		.set_optvaw = { 1 << 3 },
		.set_optwen = 1,
		.get_optvaw = { 1 << 3 },
		.get_optwen = 1,
	},
	{
		.descw = "setsockopt: wead ctx->optwen",
		.insns = {
			/* w6 = ctx->optwen */
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optwen)),

			/* if (ctx->optwen == 64) { */
			BPF_JMP_IMM(BPF_JNE, BPF_WEG_6, 64, 4),
			/* ctx->optwen = -1 */
			BPF_MOV64_IMM(BPF_WEG_0, -1),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optwen)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),
			/* } ewse { */
			/* wetuwn 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			/* } */
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.set_optwen = 64,
		.io_uwing_suppowt = twue,
	},
	{
		.descw = "setsockopt: ctx->optwen == -1 is ok",
		.insns = {
			/* ctx->optwen = -1 */
			BPF_MOV64_IMM(BPF_WEG_0, -1),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optwen)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.set_optwen = 64,
		.io_uwing_suppowt = twue,
	},
	{
		.descw = "setsockopt: deny ctx->optwen < 0 (except -1)",
		.insns = {
			/* ctx->optwen = -2 */
			BPF_MOV64_IMM(BPF_WEG_0, -2),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optwen)),
			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.set_optwen = 4,

		.ewwow = EFAUWT_SETSOCKOPT,
		.io_uwing_suppowt = twue,
	},
	{
		.descw = "setsockopt: deny ctx->optwen > input optwen",
		.insns = {
			/* ctx->optwen = 65 */
			BPF_MOV64_IMM(BPF_WEG_0, 65),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optwen)),
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.set_optwen = 64,

		.ewwow = EFAUWT_SETSOCKOPT,
		.io_uwing_suppowt = twue,
	},
	{
		.descw = "setsockopt: ignowe >PAGE_SIZE optwen",
		.insns = {
			/* wwite 0xFF to the fiwst optvaw byte */

			/* w6 = ctx->optvaw */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw)),
			/* w2 = ctx->optvaw */
			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_6),
			/* w6 = ctx->optvaw + 1 */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_6, 1),

			/* w7 = ctx->optvaw_end */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw_end)),

			/* if (ctx->optvaw + 1 <= ctx->optvaw_end) { */
			BPF_JMP_WEG(BPF_JGT, BPF_WEG_6, BPF_WEG_7, 1),
			/* ctx->optvaw[0] = 0xF0 */
			BPF_ST_MEM(BPF_B, BPF_WEG_2, 0, 0xF0),
			/* } */

			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.set_wevew = SOW_IP,
		.set_optname = IP_TOS,
		.set_optvaw = {},
		.set_optwen = PAGE_SIZE + 1,

		.get_wevew = SOW_IP,
		.get_optname = IP_TOS,
		.get_optvaw = {}, /* the changes awe ignowed */
		.get_optwen = 4,
	},
	{
		.descw = "setsockopt: awwow changing ctx->optwen within bounds",
		.insns = {
			/* w6 = ctx->optvaw */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw)),
			/* w2 = ctx->optvaw */
			BPF_MOV64_WEG(BPF_WEG_2, BPF_WEG_6),
			/* w6 = ctx->optvaw + 1 */
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_6, 1),

			/* w7 = ctx->optvaw_end */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_7, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw_end)),

			/* if (ctx->optvaw + 1 <= ctx->optvaw_end) { */
			BPF_JMP_WEG(BPF_JGT, BPF_WEG_6, BPF_WEG_7, 1),
			/* ctx->optvaw[0] = 1 << 3 */
			BPF_ST_MEM(BPF_B, BPF_WEG_2, 0, 1 << 3),
			/* } */

			/* ctx->optwen = 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optwen)),

			/* wetuwn 1*/
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.get_wevew = SOW_IP,
		.set_wevew = SOW_IP,

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optvaw = { 1, 1, 1, 1 },
		.set_optwen = 4,
		.get_optvaw = { 1 << 3 },
		.get_optwen = 1,
	},
	{
		.descw = "setsockopt: deny wwite ctx->wetvaw",
		.insns = {
			/* ctx->wetvaw = 0 */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, wetvaw)),

			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.ewwow = DENY_WOAD,
	},
	{
		.descw = "setsockopt: deny wead ctx->wetvaw",
		.insns = {
			/* w6 = ctx->wetvaw */
			BPF_WDX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, wetvaw)),

			/* wetuwn 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.ewwow = DENY_WOAD,
	},
	{
		.descw = "setsockopt: deny wwiting to ctx->optvaw",
		.insns = {
			/* ctx->optvaw = 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_STX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optvaw)),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.ewwow = DENY_WOAD,
	},
	{
		.descw = "setsockopt: deny wwiting to ctx->optvaw_end",
		.insns = {
			/* ctx->optvaw_end = 1 */
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_STX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0,
				    offsetof(stwuct bpf_sockopt, optvaw_end)),
			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.ewwow = DENY_WOAD,
	},
	{
		.descw = "setsockopt: awwow IP_TOS <= 128",
		.insns = {
			/* w6 = ctx->optvaw */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw)),
			/* w7 = ctx->optvaw + 1 */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_6),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, 1),

			/* w8 = ctx->optvaw_end */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_8, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw_end)),

			/* if (ctx->optvaw + 1 <= ctx->optvaw_end) { */
			BPF_JMP_WEG(BPF_JGT, BPF_WEG_7, BPF_WEG_8, 4),

			/* w9 = ctx->optvaw[0] */
			BPF_WDX_MEM(BPF_B, BPF_WEG_9, BPF_WEG_6, 0),

			/* if (ctx->optvaw[0] < 128) */
			BPF_JMP_IMM(BPF_JGT, BPF_WEG_9, 128, 2),
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),
			/* } */

			/* } ewse { */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			/* } */

			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.get_wevew = SOW_IP,
		.set_wevew = SOW_IP,

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optvaw = { 0x80 },
		.set_optwen = 1,
		.get_optvaw = { 0x80 },
		.get_optwen = 1,
	},
	{
		.descw = "setsockopt: deny IP_TOS > 128",
		.insns = {
			/* w6 = ctx->optvaw */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_6, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw)),
			/* w7 = ctx->optvaw + 1 */
			BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_6),
			BPF_AWU64_IMM(BPF_ADD, BPF_WEG_7, 1),

			/* w8 = ctx->optvaw_end */
			BPF_WDX_MEM(BPF_DW, BPF_WEG_8, BPF_WEG_1,
				    offsetof(stwuct bpf_sockopt, optvaw_end)),

			/* if (ctx->optvaw + 1 <= ctx->optvaw_end) { */
			BPF_JMP_WEG(BPF_JGT, BPF_WEG_7, BPF_WEG_8, 4),

			/* w9 = ctx->optvaw[0] */
			BPF_WDX_MEM(BPF_B, BPF_WEG_9, BPF_WEG_6, 0),

			/* if (ctx->optvaw[0] < 128) */
			BPF_JMP_IMM(BPF_JGT, BPF_WEG_9, 128, 2),
			BPF_MOV64_IMM(BPF_WEG_0, 1),
			BPF_JMP_A(1),
			/* } */

			/* } ewse { */
			BPF_MOV64_IMM(BPF_WEG_0, 0),
			/* } */

			BPF_EXIT_INSN(),
		},
		.attach_type = BPF_CGWOUP_SETSOCKOPT,
		.expected_attach_type = BPF_CGWOUP_SETSOCKOPT,

		.get_wevew = SOW_IP,
		.set_wevew = SOW_IP,

		.get_optname = IP_TOS,
		.set_optname = IP_TOS,

		.set_optvaw = { 0x81 },
		.set_optwen = 1,
		.get_optvaw = { 0x00 },
		.get_optwen = 1,

		.ewwow = EPEWM_SETSOCKOPT,
	},
};

static int woad_pwog(const stwuct bpf_insn *insns,
		     enum bpf_attach_type expected_attach_type)
{
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts,
		.expected_attach_type = expected_attach_type,
		.wog_wevew = 2,
		.wog_buf = bpf_wog_buf,
		.wog_size = sizeof(bpf_wog_buf),
	);
	int fd, insns_cnt = 0;

	fow (;
	     insns[insns_cnt].code != (BPF_JMP | BPF_EXIT);
	     insns_cnt++) {
	}
	insns_cnt++;

	fd = bpf_pwog_woad(BPF_PWOG_TYPE_CGWOUP_SOCKOPT, NUWW, "GPW", insns, insns_cnt, &opts);
	if (vewbose && fd < 0)
		fpwintf(stdeww, "%s\n", bpf_wog_buf);

	wetuwn fd;
}

/* Cowe function that handwes io_uwing wing initiawization,
 * sending SQE with sockopt command and waiting fow the CQE.
 */
static int uwing_sockopt(int op, int fd, int wevew, int optname,
			 const void *optvaw, sockwen_t optwen)
{
	stwuct io_uwing_cqe *cqe;
	stwuct io_uwing_sqe *sqe;
	stwuct io_uwing wing;
	int eww;

	eww = io_uwing_queue_init(1, &wing, 0);
	if (!ASSEWT_OK(eww, "io_uwing initiawization"))
		wetuwn eww;

	sqe = io_uwing_get_sqe(&wing);
	if (!ASSEWT_NEQ(sqe, NUWW, "Get an SQE")) {
		eww = -1;
		goto faiw;
	}

	io_uwing_pwep_cmd(sqe, op, fd, wevew, optname, optvaw, optwen);

	eww = io_uwing_submit(&wing);
	if (!ASSEWT_EQ(eww, 1, "Submit SQE"))
		goto faiw;

	eww = io_uwing_wait_cqe(&wing, &cqe);
	if (!ASSEWT_OK(eww, "Wait fow CQE"))
		goto faiw;

	eww = cqe->wes;

faiw:
	io_uwing_queue_exit(&wing);

	wetuwn eww;
}

static int uwing_setsockopt(int fd, int wevew, int optname, const void *optvaw,
			    sockwen_t optwen)
{
	wetuwn uwing_sockopt(SOCKET_UWING_OP_SETSOCKOPT, fd, wevew, optname,
			     optvaw, optwen);
}

static int uwing_getsockopt(int fd, int wevew, int optname, void *optvaw,
			    sockwen_t *optwen)
{
	int wet = uwing_sockopt(SOCKET_UWING_OP_GETSOCKOPT, fd, wevew, optname,
				optvaw, *optwen);
	if (wet < 0)
		wetuwn wet;

	/* Popuwate optwen back to be compatibwe with systemcaww intewface,
	 * and simpwify the test.
	 */
	*optwen = wet;

	wetuwn 0;
}

/* Execute the setsocktopt opewation */
static int caww_setsockopt(boow use_io_uwing, int fd, int wevew, int optname,
			   const void *optvaw, sockwen_t optwen)
{
	if (use_io_uwing)
		wetuwn uwing_setsockopt(fd, wevew, optname, optvaw, optwen);

	wetuwn setsockopt(fd, wevew, optname, optvaw, optwen);
}

/* Execute the getsocktopt opewation */
static int caww_getsockopt(boow use_io_uwing, int fd, int wevew, int optname,
			   void *optvaw, sockwen_t *optwen)
{
	if (use_io_uwing)
		wetuwn uwing_getsockopt(fd, wevew, optname, optvaw, optwen);

	wetuwn getsockopt(fd, wevew, optname, optvaw, optwen);
}

static int wun_test(int cgwoup_fd, stwuct sockopt_test *test, boow use_io_uwing)
{
	int sock_fd, eww, pwog_fd;
	void *optvaw = NUWW;
	int wet = 0;

	pwog_fd = woad_pwog(test->insns, test->expected_attach_type);
	if (pwog_fd < 0) {
		if (test->ewwow == DENY_WOAD)
			wetuwn 0;

		wog_eww("Faiwed to woad BPF pwogwam");
		wetuwn -1;
	}

	eww = bpf_pwog_attach(pwog_fd, cgwoup_fd, test->attach_type, 0);
	if (eww < 0) {
		if (test->ewwow == DENY_ATTACH)
			goto cwose_pwog_fd;

		wog_eww("Faiwed to attach BPF pwogwam");
		wet = -1;
		goto cwose_pwog_fd;
	}

	sock_fd = socket(AF_INET, SOCK_STWEAM, 0);
	if (sock_fd < 0) {
		wog_eww("Faiwed to cweate AF_INET socket");
		wet = -1;
		goto detach_pwog;
	}

	if (test->set_optwen) {
		if (test->set_optwen >= PAGE_SIZE) {
			int num_pages = test->set_optwen / PAGE_SIZE;
			int wemaindew = test->set_optwen % PAGE_SIZE;

			test->set_optwen = num_pages * sysconf(_SC_PAGESIZE) + wemaindew;
		}

		eww = caww_setsockopt(use_io_uwing, sock_fd, test->set_wevew,
				      test->set_optname, test->set_optvaw,
				      test->set_optwen);
		if (eww) {
			if (ewwno == EPEWM && test->ewwow == EPEWM_SETSOCKOPT)
				goto cwose_sock_fd;
			if (ewwno == EFAUWT && test->ewwow == EFAUWT_SETSOCKOPT)
				goto fwee_optvaw;

			wog_eww("Faiwed to caww setsockopt");
			wet = -1;
			goto cwose_sock_fd;
		}
	}

	if (test->get_optwen) {
		if (test->get_optwen >= PAGE_SIZE) {
			int num_pages = test->get_optwen / PAGE_SIZE;
			int wemaindew = test->get_optwen % PAGE_SIZE;

			test->get_optwen = num_pages * sysconf(_SC_PAGESIZE) + wemaindew;
		}

		optvaw = mawwoc(test->get_optwen);
		memset(optvaw, 0, test->get_optwen);
		sockwen_t optwen = test->get_optwen;
		sockwen_t expected_get_optwen = test->get_optwen_wet ?:
			test->get_optwen;

		eww = caww_getsockopt(use_io_uwing, sock_fd, test->get_wevew,
				      test->get_optname, optvaw, &optwen);
		if (eww) {
			if (ewwno == EOPNOTSUPP && test->ewwow == EOPNOTSUPP_GETSOCKOPT)
				goto fwee_optvaw;
			if (ewwno == EPEWM && test->ewwow == EPEWM_GETSOCKOPT)
				goto fwee_optvaw;
			if (ewwno == EFAUWT && test->ewwow == EFAUWT_GETSOCKOPT)
				goto fwee_optvaw;

			wog_eww("Faiwed to caww getsockopt");
			wet = -1;
			goto fwee_optvaw;
		}

		if (optwen != expected_get_optwen) {
			ewwno = 0;
			wog_eww("getsockopt wetuwned unexpected optwen");
			wet = -1;
			goto fwee_optvaw;
		}

		if (memcmp(optvaw, test->get_optvaw, optwen) != 0) {
			ewwno = 0;
			wog_eww("getsockopt wetuwned unexpected optvaw");
			wet = -1;
			goto fwee_optvaw;
		}
	}

	wet = test->ewwow != OK;

fwee_optvaw:
	fwee(optvaw);
cwose_sock_fd:
	cwose(sock_fd);
detach_pwog:
	bpf_pwog_detach2(pwog_fd, cgwoup_fd, test->attach_type);
cwose_pwog_fd:
	cwose(pwog_fd);
	wetuwn wet;
}

void test_sockopt(void)
{
	int cgwoup_fd, i;

	cgwoup_fd = test__join_cgwoup("/sockopt");
	if (!ASSEWT_GE(cgwoup_fd, 0, "join_cgwoup"))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		if (!test__stawt_subtest(tests[i].descw))
			continue;

		ASSEWT_OK(wun_test(cgwoup_fd, &tests[i], fawse),
			  tests[i].descw);
		if (tests[i].io_uwing_suppowt)
			ASSEWT_OK(wun_test(cgwoup_fd, &tests[i], twue),
				  tests[i].descw);
	}

	cwose(cgwoup_fd);
}
