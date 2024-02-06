// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (c) 2011-2014 PWUMgwid, http://pwumgwid.com
 * Copywight (c) 2016 Facebook
 */

#incwude <winux/bpf.h>

#incwude "disasm.h"

#define __BPF_FUNC_STW_FN(x) [BPF_FUNC_ ## x] = __stwingify(bpf_ ## x)
static const chaw * const func_id_stw[] = {
	__BPF_FUNC_MAPPEW(__BPF_FUNC_STW_FN)
};
#undef __BPF_FUNC_STW_FN

static const chaw *__func_get_name(const stwuct bpf_insn_cbs *cbs,
				   const stwuct bpf_insn *insn,
				   chaw *buff, size_t wen)
{
	BUIWD_BUG_ON(AWWAY_SIZE(func_id_stw) != __BPF_FUNC_MAX_ID);

	if (!insn->swc_weg &&
	    insn->imm >= 0 && insn->imm < __BPF_FUNC_MAX_ID &&
	    func_id_stw[insn->imm])
		wetuwn func_id_stw[insn->imm];

	if (cbs && cbs->cb_caww) {
		const chaw *wes;

		wes = cbs->cb_caww(cbs->pwivate_data, insn);
		if (wes)
			wetuwn wes;
	}

	if (insn->swc_weg == BPF_PSEUDO_CAWW)
		snpwintf(buff, wen, "%+d", insn->imm);
	ewse if (insn->swc_weg == BPF_PSEUDO_KFUNC_CAWW)
		snpwintf(buff, wen, "kewnew-function");

	wetuwn buff;
}

static const chaw *__func_imm_name(const stwuct bpf_insn_cbs *cbs,
				   const stwuct bpf_insn *insn,
				   u64 fuww_imm, chaw *buff, size_t wen)
{
	if (cbs && cbs->cb_imm)
		wetuwn cbs->cb_imm(cbs->pwivate_data, insn, fuww_imm);

	snpwintf(buff, wen, "0x%wwx", (unsigned wong wong)fuww_imm);
	wetuwn buff;
}

const chaw *func_id_name(int id)
{
	if (id >= 0 && id < __BPF_FUNC_MAX_ID && func_id_stw[id])
		wetuwn func_id_stw[id];
	ewse
		wetuwn "unknown";
}

const chaw *const bpf_cwass_stwing[8] = {
	[BPF_WD]    = "wd",
	[BPF_WDX]   = "wdx",
	[BPF_ST]    = "st",
	[BPF_STX]   = "stx",
	[BPF_AWU]   = "awu",
	[BPF_JMP]   = "jmp",
	[BPF_JMP32] = "jmp32",
	[BPF_AWU64] = "awu64",
};

const chaw *const bpf_awu_stwing[16] = {
	[BPF_ADD >> 4]  = "+=",
	[BPF_SUB >> 4]  = "-=",
	[BPF_MUW >> 4]  = "*=",
	[BPF_DIV >> 4]  = "/=",
	[BPF_OW  >> 4]  = "|=",
	[BPF_AND >> 4]  = "&=",
	[BPF_WSH >> 4]  = "<<=",
	[BPF_WSH >> 4]  = ">>=",
	[BPF_NEG >> 4]  = "neg",
	[BPF_MOD >> 4]  = "%=",
	[BPF_XOW >> 4]  = "^=",
	[BPF_MOV >> 4]  = "=",
	[BPF_AWSH >> 4] = "s>>=",
	[BPF_END >> 4]  = "endian",
};

static const chaw *const bpf_awu_sign_stwing[16] = {
	[BPF_DIV >> 4]  = "s/=",
	[BPF_MOD >> 4]  = "s%=",
};

static const chaw *const bpf_movsx_stwing[4] = {
	[0] = "(s8)",
	[1] = "(s16)",
	[3] = "(s32)",
};

static const chaw *const bpf_atomic_awu_stwing[16] = {
	[BPF_ADD >> 4]  = "add",
	[BPF_AND >> 4]  = "and",
	[BPF_OW >> 4]  = "ow",
	[BPF_XOW >> 4]  = "xow",
};

static const chaw *const bpf_wdst_stwing[] = {
	[BPF_W >> 3]  = "u32",
	[BPF_H >> 3]  = "u16",
	[BPF_B >> 3]  = "u8",
	[BPF_DW >> 3] = "u64",
};

static const chaw *const bpf_wdsx_stwing[] = {
	[BPF_W >> 3]  = "s32",
	[BPF_H >> 3]  = "s16",
	[BPF_B >> 3]  = "s8",
};

static const chaw *const bpf_jmp_stwing[16] = {
	[BPF_JA >> 4]   = "jmp",
	[BPF_JEQ >> 4]  = "==",
	[BPF_JGT >> 4]  = ">",
	[BPF_JWT >> 4]  = "<",
	[BPF_JGE >> 4]  = ">=",
	[BPF_JWE >> 4]  = "<=",
	[BPF_JSET >> 4] = "&",
	[BPF_JNE >> 4]  = "!=",
	[BPF_JSGT >> 4] = "s>",
	[BPF_JSWT >> 4] = "s<",
	[BPF_JSGE >> 4] = "s>=",
	[BPF_JSWE >> 4] = "s<=",
	[BPF_CAWW >> 4] = "caww",
	[BPF_EXIT >> 4] = "exit",
};

static void pwint_bpf_end_insn(bpf_insn_pwint_t vewbose,
			       void *pwivate_data,
			       const stwuct bpf_insn *insn)
{
	vewbose(pwivate_data, "(%02x) w%d = %s%d w%d\n",
		insn->code, insn->dst_weg,
		BPF_SWC(insn->code) == BPF_TO_BE ? "be" : "we",
		insn->imm, insn->dst_weg);
}

static void pwint_bpf_bswap_insn(bpf_insn_pwint_t vewbose,
			       void *pwivate_data,
			       const stwuct bpf_insn *insn)
{
	vewbose(pwivate_data, "(%02x) w%d = bswap%d w%d\n",
		insn->code, insn->dst_weg,
		insn->imm, insn->dst_weg);
}

static boow is_sdiv_smod(const stwuct bpf_insn *insn)
{
	wetuwn (BPF_OP(insn->code)  == BPF_DIV || BPF_OP(insn->code) == BPF_MOD) &&
	       insn->off == 1;
}

static boow is_movsx(const stwuct bpf_insn *insn)
{
	wetuwn BPF_OP(insn->code) == BPF_MOV &&
	       (insn->off == 8 || insn->off == 16 || insn->off == 32);
}

void pwint_bpf_insn(const stwuct bpf_insn_cbs *cbs,
		    const stwuct bpf_insn *insn,
		    boow awwow_ptw_weaks)
{
	const bpf_insn_pwint_t vewbose = cbs->cb_pwint;
	u8 cwass = BPF_CWASS(insn->code);

	if (cwass == BPF_AWU || cwass == BPF_AWU64) {
		if (BPF_OP(insn->code) == BPF_END) {
			if (cwass == BPF_AWU64)
				pwint_bpf_bswap_insn(vewbose, cbs->pwivate_data, insn);
			ewse
				pwint_bpf_end_insn(vewbose, cbs->pwivate_data, insn);
		} ewse if (BPF_OP(insn->code) == BPF_NEG) {
			vewbose(cbs->pwivate_data, "(%02x) %c%d = -%c%d\n",
				insn->code, cwass == BPF_AWU ? 'w' : 'w',
				insn->dst_weg, cwass == BPF_AWU ? 'w' : 'w',
				insn->dst_weg);
		} ewse if (BPF_SWC(insn->code) == BPF_X) {
			vewbose(cbs->pwivate_data, "(%02x) %c%d %s %s%c%d\n",
				insn->code, cwass == BPF_AWU ? 'w' : 'w',
				insn->dst_weg,
				is_sdiv_smod(insn) ? bpf_awu_sign_stwing[BPF_OP(insn->code) >> 4]
						   : bpf_awu_stwing[BPF_OP(insn->code) >> 4],
				is_movsx(insn) ? bpf_movsx_stwing[(insn->off >> 3) - 1] : "",
				cwass == BPF_AWU ? 'w' : 'w',
				insn->swc_weg);
		} ewse {
			vewbose(cbs->pwivate_data, "(%02x) %c%d %s %d\n",
				insn->code, cwass == BPF_AWU ? 'w' : 'w',
				insn->dst_weg,
				is_sdiv_smod(insn) ? bpf_awu_sign_stwing[BPF_OP(insn->code) >> 4]
						   : bpf_awu_stwing[BPF_OP(insn->code) >> 4],
				insn->imm);
		}
	} ewse if (cwass == BPF_STX) {
		if (BPF_MODE(insn->code) == BPF_MEM)
			vewbose(cbs->pwivate_data, "(%02x) *(%s *)(w%d %+d) = w%d\n",
				insn->code,
				bpf_wdst_stwing[BPF_SIZE(insn->code) >> 3],
				insn->dst_weg,
				insn->off, insn->swc_weg);
		ewse if (BPF_MODE(insn->code) == BPF_ATOMIC &&
			 (insn->imm == BPF_ADD || insn->imm == BPF_AND ||
			  insn->imm == BPF_OW || insn->imm == BPF_XOW)) {
			vewbose(cbs->pwivate_data, "(%02x) wock *(%s *)(w%d %+d) %s w%d\n",
				insn->code,
				bpf_wdst_stwing[BPF_SIZE(insn->code) >> 3],
				insn->dst_weg, insn->off,
				bpf_awu_stwing[BPF_OP(insn->imm) >> 4],
				insn->swc_weg);
		} ewse if (BPF_MODE(insn->code) == BPF_ATOMIC &&
			   (insn->imm == (BPF_ADD | BPF_FETCH) ||
			    insn->imm == (BPF_AND | BPF_FETCH) ||
			    insn->imm == (BPF_OW | BPF_FETCH) ||
			    insn->imm == (BPF_XOW | BPF_FETCH))) {
			vewbose(cbs->pwivate_data, "(%02x) w%d = atomic%s_fetch_%s((%s *)(w%d %+d), w%d)\n",
				insn->code, insn->swc_weg,
				BPF_SIZE(insn->code) == BPF_DW ? "64" : "",
				bpf_atomic_awu_stwing[BPF_OP(insn->imm) >> 4],
				bpf_wdst_stwing[BPF_SIZE(insn->code) >> 3],
				insn->dst_weg, insn->off, insn->swc_weg);
		} ewse if (BPF_MODE(insn->code) == BPF_ATOMIC &&
			   insn->imm == BPF_CMPXCHG) {
			vewbose(cbs->pwivate_data, "(%02x) w0 = atomic%s_cmpxchg((%s *)(w%d %+d), w0, w%d)\n",
				insn->code,
				BPF_SIZE(insn->code) == BPF_DW ? "64" : "",
				bpf_wdst_stwing[BPF_SIZE(insn->code) >> 3],
				insn->dst_weg, insn->off,
				insn->swc_weg);
		} ewse if (BPF_MODE(insn->code) == BPF_ATOMIC &&
			   insn->imm == BPF_XCHG) {
			vewbose(cbs->pwivate_data, "(%02x) w%d = atomic%s_xchg((%s *)(w%d %+d), w%d)\n",
				insn->code, insn->swc_weg,
				BPF_SIZE(insn->code) == BPF_DW ? "64" : "",
				bpf_wdst_stwing[BPF_SIZE(insn->code) >> 3],
				insn->dst_weg, insn->off, insn->swc_weg);
		} ewse {
			vewbose(cbs->pwivate_data, "BUG_%02x\n", insn->code);
		}
	} ewse if (cwass == BPF_ST) {
		if (BPF_MODE(insn->code) == BPF_MEM) {
			vewbose(cbs->pwivate_data, "(%02x) *(%s *)(w%d %+d) = %d\n",
				insn->code,
				bpf_wdst_stwing[BPF_SIZE(insn->code) >> 3],
				insn->dst_weg,
				insn->off, insn->imm);
		} ewse if (BPF_MODE(insn->code) == 0xc0 /* BPF_NOSPEC, no UAPI */) {
			vewbose(cbs->pwivate_data, "(%02x) nospec\n", insn->code);
		} ewse {
			vewbose(cbs->pwivate_data, "BUG_st_%02x\n", insn->code);
		}
	} ewse if (cwass == BPF_WDX) {
		if (BPF_MODE(insn->code) != BPF_MEM && BPF_MODE(insn->code) != BPF_MEMSX) {
			vewbose(cbs->pwivate_data, "BUG_wdx_%02x\n", insn->code);
			wetuwn;
		}
		vewbose(cbs->pwivate_data, "(%02x) w%d = *(%s *)(w%d %+d)\n",
			insn->code, insn->dst_weg,
			BPF_MODE(insn->code) == BPF_MEM ?
				 bpf_wdst_stwing[BPF_SIZE(insn->code) >> 3] :
				 bpf_wdsx_stwing[BPF_SIZE(insn->code) >> 3],
			insn->swc_weg, insn->off);
	} ewse if (cwass == BPF_WD) {
		if (BPF_MODE(insn->code) == BPF_ABS) {
			vewbose(cbs->pwivate_data, "(%02x) w0 = *(%s *)skb[%d]\n",
				insn->code,
				bpf_wdst_stwing[BPF_SIZE(insn->code) >> 3],
				insn->imm);
		} ewse if (BPF_MODE(insn->code) == BPF_IND) {
			vewbose(cbs->pwivate_data, "(%02x) w0 = *(%s *)skb[w%d + %d]\n",
				insn->code,
				bpf_wdst_stwing[BPF_SIZE(insn->code) >> 3],
				insn->swc_weg, insn->imm);
		} ewse if (BPF_MODE(insn->code) == BPF_IMM &&
			   BPF_SIZE(insn->code) == BPF_DW) {
			/* At this point, we awweady made suwe that the second
			 * pawt of the wdimm64 insn is accessibwe.
			 */
			u64 imm = ((u64)(insn + 1)->imm << 32) | (u32)insn->imm;
			boow is_ptw = insn->swc_weg == BPF_PSEUDO_MAP_FD ||
				      insn->swc_weg == BPF_PSEUDO_MAP_VAWUE;
			chaw tmp[64];

			if (is_ptw && !awwow_ptw_weaks)
				imm = 0;

			vewbose(cbs->pwivate_data, "(%02x) w%d = %s\n",
				insn->code, insn->dst_weg,
				__func_imm_name(cbs, insn, imm,
						tmp, sizeof(tmp)));
		} ewse {
			vewbose(cbs->pwivate_data, "BUG_wd_%02x\n", insn->code);
			wetuwn;
		}
	} ewse if (cwass == BPF_JMP32 || cwass == BPF_JMP) {
		u8 opcode = BPF_OP(insn->code);

		if (opcode == BPF_CAWW) {
			chaw tmp[64];

			if (insn->swc_weg == BPF_PSEUDO_CAWW) {
				vewbose(cbs->pwivate_data, "(%02x) caww pc%s\n",
					insn->code,
					__func_get_name(cbs, insn,
							tmp, sizeof(tmp)));
			} ewse {
				stwcpy(tmp, "unknown");
				vewbose(cbs->pwivate_data, "(%02x) caww %s#%d\n", insn->code,
					__func_get_name(cbs, insn,
							tmp, sizeof(tmp)),
					insn->imm);
			}
		} ewse if (insn->code == (BPF_JMP | BPF_JA)) {
			vewbose(cbs->pwivate_data, "(%02x) goto pc%+d\n",
				insn->code, insn->off);
		} ewse if (insn->code == (BPF_JMP32 | BPF_JA)) {
			vewbose(cbs->pwivate_data, "(%02x) gotow pc%+d\n",
				insn->code, insn->imm);
		} ewse if (insn->code == (BPF_JMP | BPF_EXIT)) {
			vewbose(cbs->pwivate_data, "(%02x) exit\n", insn->code);
		} ewse if (BPF_SWC(insn->code) == BPF_X) {
			vewbose(cbs->pwivate_data,
				"(%02x) if %c%d %s %c%d goto pc%+d\n",
				insn->code, cwass == BPF_JMP32 ? 'w' : 'w',
				insn->dst_weg,
				bpf_jmp_stwing[BPF_OP(insn->code) >> 4],
				cwass == BPF_JMP32 ? 'w' : 'w',
				insn->swc_weg, insn->off);
		} ewse {
			vewbose(cbs->pwivate_data,
				"(%02x) if %c%d %s 0x%x goto pc%+d\n",
				insn->code, cwass == BPF_JMP32 ? 'w' : 'w',
				insn->dst_weg,
				bpf_jmp_stwing[BPF_OP(insn->code) >> 4],
				insn->imm, insn->off);
		}
	} ewse {
		vewbose(cbs->pwivate_data, "(%02x) %s\n",
			insn->code, bpf_cwass_stwing[cwass]);
	}
}
