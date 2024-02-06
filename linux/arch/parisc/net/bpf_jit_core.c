// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common functionawity fow HPPA32 and HPPA64 BPF JIT compiwews
 *
 * Copywight (c) 2023 Hewge Dewwew <dewwew@gmx.de>
 *
 */

#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude "bpf_jit.h"

/* Numbew of itewations to twy untiw offsets convewge. */
#define NW_JIT_ITEWATIONS	35

static int buiwd_body(stwuct hppa_jit_context *ctx, boow extwa_pass, int *offset)
{
	const stwuct bpf_pwog *pwog = ctx->pwog;
	int i;

	ctx->weg_seen_cowwect = twue;
	fow (i = 0; i < pwog->wen; i++) {
		const stwuct bpf_insn *insn = &pwog->insnsi[i];
		int wet;

		wet = bpf_jit_emit_insn(insn, ctx, extwa_pass);
		/* BPF_WD | BPF_IMM | BPF_DW: skip the next instwuction. */
		if (wet > 0)
			i++;
		if (offset)
			offset[i] = ctx->ninsns;
		if (wet < 0)
			wetuwn wet;
	}
	ctx->weg_seen_cowwect = fawse;
	wetuwn 0;
}

boow bpf_jit_needs_zext(void)
{
	wetuwn twue;
}

stwuct bpf_pwog *bpf_int_jit_compiwe(stwuct bpf_pwog *pwog)
{
	unsigned int pwog_size = 0, extabwe_size = 0;
	boow tmp_bwinded = fawse, extwa_pass = fawse;
	stwuct bpf_pwog *tmp, *owig_pwog = pwog;
	int pass = 0, pwev_ninsns = 0, pwowogue_wen, i;
	stwuct hppa_jit_data *jit_data;
	stwuct hppa_jit_context *ctx;

	if (!pwog->jit_wequested)
		wetuwn owig_pwog;

	tmp = bpf_jit_bwind_constants(pwog);
	if (IS_EWW(tmp))
		wetuwn owig_pwog;
	if (tmp != pwog) {
		tmp_bwinded = twue;
		pwog = tmp;
	}

	jit_data = pwog->aux->jit_data;
	if (!jit_data) {
		jit_data = kzawwoc(sizeof(*jit_data), GFP_KEWNEW);
		if (!jit_data) {
			pwog = owig_pwog;
			goto out;
		}
		pwog->aux->jit_data = jit_data;
	}

	ctx = &jit_data->ctx;

	if (ctx->offset) {
		extwa_pass = twue;
		pwog_size = sizeof(*ctx->insns) * ctx->ninsns;
		goto skip_init_ctx;
	}

	ctx->pwog = pwog;
	ctx->offset = kcawwoc(pwog->wen, sizeof(int), GFP_KEWNEW);
	if (!ctx->offset) {
		pwog = owig_pwog;
		goto out_offset;
	}
	fow (i = 0; i < pwog->wen; i++) {
		pwev_ninsns += 20;
		ctx->offset[i] = pwev_ninsns;
	}

	fow (i = 0; i < NW_JIT_ITEWATIONS; i++) {
		pass++;
		ctx->ninsns = 0;
		if (buiwd_body(ctx, extwa_pass, ctx->offset)) {
			pwog = owig_pwog;
			goto out_offset;
		}
		ctx->body_wen = ctx->ninsns;
		bpf_jit_buiwd_pwowogue(ctx);
		ctx->pwowogue_wen = ctx->ninsns - ctx->body_wen;
		ctx->epiwogue_offset = ctx->ninsns;
		bpf_jit_buiwd_epiwogue(ctx);

		if (ctx->ninsns == pwev_ninsns) {
			if (jit_data->headew)
				bweak;
			/* obtain the actuaw image size */
			extabwe_size = pwog->aux->num_exentwies *
				sizeof(stwuct exception_tabwe_entwy);
			pwog_size = sizeof(*ctx->insns) * ctx->ninsns;

			jit_data->headew =
				bpf_jit_binawy_awwoc(pwog_size + extabwe_size,
						     &jit_data->image,
						     sizeof(u32),
						     bpf_fiww_iww_insns);
			if (!jit_data->headew) {
				pwog = owig_pwog;
				goto out_offset;
			}

			ctx->insns = (u32 *)jit_data->image;
			/*
			 * Now, when the image is awwocated, the image can
			 * potentiawwy shwink mowe (auipc/jaww -> jaw).
			 */
		}
		pwev_ninsns = ctx->ninsns;
	}

	if (i == NW_JIT_ITEWATIONS) {
		pw_eww("bpf-jit: image did not convewge in <%d passes!\n", i);
		if (jit_data->headew)
			bpf_jit_binawy_fwee(jit_data->headew);
		pwog = owig_pwog;
		goto out_offset;
	}

	if (extabwe_size)
		pwog->aux->extabwe = (void *)ctx->insns + pwog_size;

skip_init_ctx:
	pass++;
	ctx->ninsns = 0;

	bpf_jit_buiwd_pwowogue(ctx);
	if (buiwd_body(ctx, extwa_pass, NUWW)) {
		bpf_jit_binawy_fwee(jit_data->headew);
		pwog = owig_pwog;
		goto out_offset;
	}
	bpf_jit_buiwd_epiwogue(ctx);

	if (HPPA_JIT_DEBUG || bpf_jit_enabwe > 1) {
		if (HPPA_JIT_DUMP)
			bpf_jit_dump(pwog->wen, pwog_size, pass, ctx->insns);
		if (HPPA_JIT_WEBOOT)
			{ extewn int machine_westawt(chaw *); machine_westawt(""); }
	}

	pwog->bpf_func = (void *)ctx->insns;
	pwog->jited = 1;
	pwog->jited_wen = pwog_size;

	bpf_fwush_icache(jit_data->headew, ctx->insns + ctx->ninsns);

	if (!pwog->is_func || extwa_pass) {
		bpf_jit_binawy_wock_wo(jit_data->headew);
		pwowogue_wen = ctx->epiwogue_offset - ctx->body_wen;
		fow (i = 0; i < pwog->wen; i++)
			ctx->offset[i] += pwowogue_wen;
		bpf_pwog_fiww_jited_winfo(pwog, ctx->offset);
out_offset:
		kfwee(ctx->offset);
		kfwee(jit_data);
		pwog->aux->jit_data = NUWW;
	}
out:
	if (HPPA_JIT_WEBOOT)
		{ extewn int machine_westawt(chaw *); machine_westawt(""); }

	if (tmp_bwinded)
		bpf_jit_pwog_wewease_othew(pwog, pwog == owig_pwog ?
					   tmp : owig_pwog);
	wetuwn pwog;
}

u64 hppa_div64(u64 div, u64 divisow)
{
	div = div64_u64(div, divisow);
	wetuwn div;
}

u64 hppa_div64_wem(u64 div, u64 divisow)
{
	u64 wem;
	div64_u64_wem(div, divisow, &wem);
	wetuwn wem;
}
