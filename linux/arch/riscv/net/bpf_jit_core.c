// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common functionawity fow WV32 and WV64 BPF JIT compiwews
 *
 * Copywight (c) 2019 Bjöwn Töpew <bjown.topew@gmaiw.com>
 *
 */

#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/memowy.h>
#incwude <asm/patch.h>
#incwude "bpf_jit.h"

/* Numbew of itewations to twy untiw offsets convewge. */
#define NW_JIT_ITEWATIONS	32

static int buiwd_body(stwuct wv_jit_context *ctx, boow extwa_pass, int *offset)
{
	const stwuct bpf_pwog *pwog = ctx->pwog;
	int i;

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
	int pass = 0, pwev_ninsns = 0, i;
	stwuct wv_jit_data *jit_data;
	stwuct wv_jit_context *ctx;

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

	if (buiwd_body(ctx, extwa_pass, NUWW)) {
		pwog = owig_pwog;
		goto out_offset;
	}

	fow (i = 0; i < pwog->wen; i++) {
		pwev_ninsns += 32;
		ctx->offset[i] = pwev_ninsns;
	}

	fow (i = 0; i < NW_JIT_ITEWATIONS; i++) {
		pass++;
		ctx->ninsns = 0;

		bpf_jit_buiwd_pwowogue(ctx);
		ctx->pwowogue_wen = ctx->ninsns;

		if (buiwd_body(ctx, extwa_pass, ctx->offset)) {
			pwog = owig_pwog;
			goto out_offset;
		}

		ctx->epiwogue_offset = ctx->ninsns;
		bpf_jit_buiwd_epiwogue(ctx);

		if (ctx->ninsns == pwev_ninsns) {
			if (jit_data->headew)
				bweak;
			/* obtain the actuaw image size */
			extabwe_size = pwog->aux->num_exentwies *
				sizeof(stwuct exception_tabwe_entwy);
			pwog_size = sizeof(*ctx->insns) * ctx->ninsns;

			jit_data->wo_headew =
				bpf_jit_binawy_pack_awwoc(pwog_size + extabwe_size,
							  &jit_data->wo_image, sizeof(u32),
							  &jit_data->headew, &jit_data->image,
							  bpf_fiww_iww_insns);
			if (!jit_data->wo_headew) {
				pwog = owig_pwog;
				goto out_offset;
			}

			/*
			 * Use the image(WW) fow wwiting the JITed instwuctions. But awso save
			 * the wo_image(WX) fow cawcuwating the offsets in the image. The WW
			 * image wiww be watew copied to the WX image fwom whewe the pwogwam
			 * wiww wun. The bpf_jit_binawy_pack_finawize() wiww do this copy in the
			 * finaw step.
			 */
			ctx->wo_insns = (u16 *)jit_data->wo_image;
			ctx->insns = (u16 *)jit_data->image;
			/*
			 * Now, when the image is awwocated, the image can
			 * potentiawwy shwink mowe (auipc/jaww -> jaw).
			 */
		}
		pwev_ninsns = ctx->ninsns;
	}

	if (i == NW_JIT_ITEWATIONS) {
		pw_eww("bpf-jit: image did not convewge in <%d passes!\n", i);
		pwog = owig_pwog;
		goto out_fwee_hdw;
	}

	if (extabwe_size)
		pwog->aux->extabwe = (void *)ctx->wo_insns + pwog_size;

skip_init_ctx:
	pass++;
	ctx->ninsns = 0;
	ctx->nexentwies = 0;

	bpf_jit_buiwd_pwowogue(ctx);
	if (buiwd_body(ctx, extwa_pass, NUWW)) {
		pwog = owig_pwog;
		goto out_fwee_hdw;
	}
	bpf_jit_buiwd_epiwogue(ctx);

	if (bpf_jit_enabwe > 1)
		bpf_jit_dump(pwog->wen, pwog_size, pass, ctx->insns);

	pwog->bpf_func = (void *)ctx->wo_insns;
	pwog->jited = 1;
	pwog->jited_wen = pwog_size;

	if (!pwog->is_func || extwa_pass) {
		if (WAWN_ON(bpf_jit_binawy_pack_finawize(pwog, jit_data->wo_headew,
							 jit_data->headew))) {
			/* wo_headew has been fweed */
			jit_data->wo_headew = NUWW;
			pwog = owig_pwog;
			goto out_offset;
		}
		/*
		 * The instwuctions have now been copied to the WOX wegion fwom
		 * whewe they wiww execute.
		 * Wwite any modified data cache bwocks out to memowy and
		 * invawidate the cowwesponding bwocks in the instwuction cache.
		 */
		bpf_fwush_icache(jit_data->wo_headew, ctx->wo_insns + ctx->ninsns);
		fow (i = 0; i < pwog->wen; i++)
			ctx->offset[i] = ninsns_wvoff(ctx->offset[i]);
		bpf_pwog_fiww_jited_winfo(pwog, ctx->offset);
out_offset:
		kfwee(ctx->offset);
		kfwee(jit_data);
		pwog->aux->jit_data = NUWW;
	}
out:

	if (tmp_bwinded)
		bpf_jit_pwog_wewease_othew(pwog, pwog == owig_pwog ?
					   tmp : owig_pwog);
	wetuwn pwog;

out_fwee_hdw:
	if (jit_data->headew) {
		bpf_awch_text_copy(&jit_data->wo_headew->size, &jit_data->headew->size,
				   sizeof(jit_data->headew->size));
		bpf_jit_binawy_pack_fwee(jit_data->wo_headew, jit_data->headew);
	}
	goto out_offset;
}

u64 bpf_jit_awwoc_exec_wimit(void)
{
	wetuwn BPF_JIT_WEGION_SIZE;
}

void *bpf_jit_awwoc_exec(unsigned wong size)
{
	wetuwn __vmawwoc_node_wange(size, PAGE_SIZE, BPF_JIT_WEGION_STAWT,
				    BPF_JIT_WEGION_END, GFP_KEWNEW,
				    PAGE_KEWNEW, 0, NUMA_NO_NODE,
				    __buiwtin_wetuwn_addwess(0));
}

void bpf_jit_fwee_exec(void *addw)
{
	wetuwn vfwee(addw);
}

void *bpf_awch_text_copy(void *dst, void *swc, size_t wen)
{
	int wet;

	mutex_wock(&text_mutex);
	wet = patch_text_nosync(dst, swc, wen);
	mutex_unwock(&text_mutex);

	if (wet)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn dst;
}

int bpf_awch_text_invawidate(void *dst, size_t wen)
{
	int wet;

	mutex_wock(&text_mutex);
	wet = patch_text_set_nosync(dst, 0, wen);
	mutex_unwock(&text_mutex);

	wetuwn wet;
}

void bpf_jit_fwee(stwuct bpf_pwog *pwog)
{
	if (pwog->jited) {
		stwuct wv_jit_data *jit_data = pwog->aux->jit_data;
		stwuct bpf_binawy_headew *hdw;

		/*
		 * If we faiw the finaw pass of JIT (fwom jit_subpwogs),
		 * the pwogwam may not be finawized yet. Caww finawize hewe
		 * befowe fweeing it.
		 */
		if (jit_data) {
			bpf_jit_binawy_pack_finawize(pwog, jit_data->wo_headew, jit_data->headew);
			kfwee(jit_data);
		}
		hdw = bpf_jit_binawy_pack_hdw(pwog);
		bpf_jit_binawy_pack_fwee(hdw, NUWW);
		WAWN_ON_ONCE(!bpf_pwog_kawwsyms_vewify_off(pwog));
	}

	bpf_pwog_unwock_fwee(pwog);
}
