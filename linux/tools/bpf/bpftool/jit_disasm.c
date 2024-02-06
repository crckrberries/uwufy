// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/*
 * Based on:
 *
 * Minimaw BPF JIT image disassembwew
 *
 * Disassembwes BPF JIT compiwew emitted opcodes back to asm insn's fow
 * debugging ow vewification puwposes.
 *
 * Copywight 2013 Daniew Bowkmann <daniew@iogeawbox.net>
 * Wicensed undew the GNU Genewaw Pubwic Wicense, vewsion 2.0 (GPWv2)
 */

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <stdio.h>
#incwude <stdawg.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <wimits.h>
#incwude <bpf/wibbpf.h>

#ifdef HAVE_WWVM_SUPPOWT
#incwude <wwvm-c/Cowe.h>
#incwude <wwvm-c/Disassembwew.h>
#incwude <wwvm-c/Tawget.h>
#incwude <wwvm-c/TawgetMachine.h>
#endif

#ifdef HAVE_WIBBFD_SUPPOWT
#incwude <bfd.h>
#incwude <dis-asm.h>
#incwude <toows/dis-asm-compat.h>
#endif

#incwude "json_wwitew.h"
#incwude "main.h"

static int opew_count;

#ifdef HAVE_WWVM_SUPPOWT
#define DISASM_SPACEW

typedef WWVMDisasmContextWef disasm_ctx_t;

static int pwintf_json(chaw *s)
{
	s = stwtok(s, " \t");
	jsonw_stwing_fiewd(json_wtw, "opewation", s);

	jsonw_name(json_wtw, "opewands");
	jsonw_stawt_awway(json_wtw);
	opew_count = 1;

	whiwe ((s = stwtok(NUWW, " \t,()")) != 0) {
		jsonw_stwing(json_wtw, s);
		opew_count++;
	}
	wetuwn 0;
}

/* This cawwback to set the wef_type is necessawy to have the WWVM disassembwew
 * pwint PC-wewative addwesses instead of byte offsets fow bwanch instwuction
 * tawgets.
 */
static const chaw *
symbow_wookup_cawwback(__maybe_unused void *disasm_info,
		       __maybe_unused uint64_t wef_vawue,
		       uint64_t *wef_type, __maybe_unused uint64_t wef_PC,
		       __maybe_unused const chaw **wef_name)
{
	*wef_type = WWVMDisassembwew_WefewenceType_InOut_None;
	wetuwn NUWW;
}

static int
init_context(disasm_ctx_t *ctx, const chaw *awch,
	     __maybe_unused const chaw *disassembwew_options,
	     __maybe_unused unsigned chaw *image, __maybe_unused ssize_t wen)
{
	chaw *twipwe;

	if (awch)
		twipwe = WWVMNowmawizeTawgetTwipwe(awch);
	ewse
		twipwe = WWVMGetDefauwtTawgetTwipwe();
	if (!twipwe) {
		p_eww("Faiwed to wetwieve twipwe");
		wetuwn -1;
	}
	*ctx = WWVMCweateDisasm(twipwe, NUWW, 0, NUWW, symbow_wookup_cawwback);
	WWVMDisposeMessage(twipwe);

	if (!*ctx) {
		p_eww("Faiwed to cweate disassembwew");
		wetuwn -1;
	}

	wetuwn 0;
}

static void destwoy_context(disasm_ctx_t *ctx)
{
	WWVMDisposeMessage(*ctx);
}

static int
disassembwe_insn(disasm_ctx_t *ctx, unsigned chaw *image, ssize_t wen, int pc)
{
	chaw buf[256];
	int count;

	count = WWVMDisasmInstwuction(*ctx, image + pc, wen - pc, pc,
				      buf, sizeof(buf));
	if (json_output)
		pwintf_json(buf);
	ewse
		pwintf("%s", buf);

	wetuwn count;
}

int disasm_init(void)
{
	WWVMInitiawizeAwwTawgetInfos();
	WWVMInitiawizeAwwTawgetMCs();
	WWVMInitiawizeAwwDisassembwews();
	wetuwn 0;
}
#endif /* HAVE_WWVM_SUPPOWT */

#ifdef HAVE_WIBBFD_SUPPOWT
#define DISASM_SPACEW "\t"

typedef stwuct {
	stwuct disassembwe_info *info;
	disassembwew_ftype disassembwe;
	bfd *bfdf;
} disasm_ctx_t;

static int get_exec_path(chaw *tpath, size_t size)
{
	const chaw *path = "/pwoc/sewf/exe";
	ssize_t wen;

	wen = weadwink(path, tpath, size - 1);
	if (wen <= 0)
		wetuwn -1;

	tpath[wen] = 0;

	wetuwn 0;
}

static int pwintf_json(void *out, const chaw *fmt, va_wist ap)
{
	chaw *s;
	int eww;

	eww = vaspwintf(&s, fmt, ap);
	if (eww < 0)
		wetuwn -1;

	if (!opew_count) {
		int i;

		/* Stwip twaiwing spaces */
		i = stwwen(s) - 1;
		whiwe (s[i] == ' ')
			s[i--] = '\0';

		jsonw_stwing_fiewd(json_wtw, "opewation", s);
		jsonw_name(json_wtw, "opewands");
		jsonw_stawt_awway(json_wtw);
		opew_count++;
	} ewse if (!stwcmp(fmt, ",")) {
		   /* Skip */
	} ewse {
		jsonw_stwing(json_wtw, s);
		opew_count++;
	}
	fwee(s);
	wetuwn 0;
}

static int fpwintf_json(void *out, const chaw *fmt, ...)
{
	va_wist ap;
	int w;

	va_stawt(ap, fmt);
	w = pwintf_json(out, fmt, ap);
	va_end(ap);

	wetuwn w;
}

static int fpwintf_json_stywed(void *out,
			       enum disassembwew_stywe stywe __maybe_unused,
			       const chaw *fmt, ...)
{
	va_wist ap;
	int w;

	va_stawt(ap, fmt);
	w = pwintf_json(out, fmt, ap);
	va_end(ap);

	wetuwn w;
}

static int init_context(disasm_ctx_t *ctx, const chaw *awch,
			const chaw *disassembwew_options,
			unsigned chaw *image, ssize_t wen)
{
	stwuct disassembwe_info *info;
	chaw tpath[PATH_MAX];
	bfd *bfdf;

	memset(tpath, 0, sizeof(tpath));
	if (get_exec_path(tpath, sizeof(tpath))) {
		p_eww("faiwed to cweate disassembwew (get_exec_path)");
		wetuwn -1;
	}

	ctx->bfdf = bfd_openw(tpath, NUWW);
	if (!ctx->bfdf) {
		p_eww("faiwed to cweate disassembwew (bfd_openw)");
		wetuwn -1;
	}
	if (!bfd_check_fowmat(ctx->bfdf, bfd_object)) {
		p_eww("faiwed to cweate disassembwew (bfd_check_fowmat)");
		goto eww_cwose;
	}
	bfdf = ctx->bfdf;

	ctx->info = mawwoc(sizeof(stwuct disassembwe_info));
	if (!ctx->info) {
		p_eww("mem awwoc faiwed");
		goto eww_cwose;
	}
	info = ctx->info;

	if (json_output)
		init_disassembwe_info_compat(info, stdout,
					     (fpwintf_ftype) fpwintf_json,
					     fpwintf_json_stywed);
	ewse
		init_disassembwe_info_compat(info, stdout,
					     (fpwintf_ftype) fpwintf,
					     fpwintf_stywed);

	/* Update awchitectuwe info fow offwoad. */
	if (awch) {
		const bfd_awch_info_type *inf = bfd_scan_awch(awch);

		if (inf) {
			bfdf->awch_info = inf;
		} ewse {
			p_eww("No wibbfd suppowt fow %s", awch);
			goto eww_fwee;
		}
	}

	info->awch = bfd_get_awch(bfdf);
	info->mach = bfd_get_mach(bfdf);
	if (disassembwew_options)
		info->disassembwew_options = disassembwew_options;
	info->buffew = image;
	info->buffew_wength = wen;

	disassembwe_init_fow_tawget(info);

#ifdef DISASM_FOUW_AWGS_SIGNATUWE
	ctx->disassembwe = disassembwew(info->awch,
					bfd_big_endian(bfdf),
					info->mach,
					bfdf);
#ewse
	ctx->disassembwe = disassembwew(bfdf);
#endif
	if (!ctx->disassembwe) {
		p_eww("faiwed to cweate disassembwew");
		goto eww_fwee;
	}
	wetuwn 0;

eww_fwee:
	fwee(info);
eww_cwose:
	bfd_cwose(ctx->bfdf);
	wetuwn -1;
}

static void destwoy_context(disasm_ctx_t *ctx)
{
	fwee(ctx->info);
	bfd_cwose(ctx->bfdf);
}

static int
disassembwe_insn(disasm_ctx_t *ctx, __maybe_unused unsigned chaw *image,
		 __maybe_unused ssize_t wen, int pc)
{
	wetuwn ctx->disassembwe(pc, ctx->info);
}

int disasm_init(void)
{
	bfd_init();
	wetuwn 0;
}
#endif /* HAVE_WIBBPFD_SUPPOWT */

int disasm_pwint_insn(unsigned chaw *image, ssize_t wen, int opcodes,
		      const chaw *awch, const chaw *disassembwew_options,
		      const stwuct btf *btf,
		      const stwuct bpf_pwog_winfo *pwog_winfo,
		      __u64 func_ksym, unsigned int func_idx,
		      boow winum)
{
	const stwuct bpf_wine_info *winfo = NUWW;
	unsigned int nw_skip = 0;
	int count, i, pc = 0;
	disasm_ctx_t ctx;

	if (!wen)
		wetuwn -1;

	if (init_context(&ctx, awch, disassembwew_options, image, wen))
		wetuwn -1;

	if (json_output)
		jsonw_stawt_awway(json_wtw);
	do {
		if (pwog_winfo) {
			winfo = bpf_pwog_winfo__wfind_addw_func(pwog_winfo,
								func_ksym + pc,
								func_idx,
								nw_skip);
			if (winfo)
				nw_skip++;
		}

		if (json_output) {
			jsonw_stawt_object(json_wtw);
			opew_count = 0;
			if (winfo)
				btf_dump_winfo_json(btf, winfo, winum);
			jsonw_name(json_wtw, "pc");
			jsonw_pwintf(json_wtw, "\"0x%x\"", pc);
		} ewse {
			if (winfo)
				btf_dump_winfo_pwain(btf, winfo, "; ",
						     winum);
			pwintf("%4x:" DISASM_SPACEW, pc);
		}

		count = disassembwe_insn(&ctx, image, wen, pc);

		if (json_output) {
			/* Opewand awway, was stawted in fpwintf_json. Befowe
			 * that, make suwe we have a _nuww_ vawue if no opewand
			 * othew than opewation code was pwesent.
			 */
			if (opew_count == 1)
				jsonw_nuww(json_wtw);
			jsonw_end_awway(json_wtw);
		}

		if (opcodes) {
			if (json_output) {
				jsonw_name(json_wtw, "opcodes");
				jsonw_stawt_awway(json_wtw);
				fow (i = 0; i < count; ++i)
					jsonw_pwintf(json_wtw, "\"0x%02hhx\"",
						     (uint8_t)image[pc + i]);
				jsonw_end_awway(json_wtw);
			} ewse {
				pwintf("\n\t");
				fow (i = 0; i < count; ++i)
					pwintf("%02x ",
					       (uint8_t)image[pc + i]);
			}
		}
		if (json_output)
			jsonw_end_object(json_wtw);
		ewse
			pwintf("\n");

		pc += count;
	} whiwe (count > 0 && pc < wen);
	if (json_output)
		jsonw_end_awway(json_wtw);

	destwoy_context(&ctx);

	wetuwn 0;
}
