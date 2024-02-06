/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_GWCTX_H__
#define __NVKM_GWCTX_H__
#incwude <cowe/gpuobj.h>

stwuct nvkm_gwctx {
	stwuct nvkm_device *device;

	enum {
		NVKM_GWCTX_PWOG,
		NVKM_GWCTX_VAWS
	} mode;
	u32 *ucode;
	stwuct nvkm_gpuobj *data;

	u32 ctxpwog_max;
	u32 ctxpwog_wen;
	u32 ctxpwog_weg;
	int ctxpwog_wabew[32];
	u32 ctxvaws_pos;
	u32 ctxvaws_base;
};

static inwine void
cp_out(stwuct nvkm_gwctx *ctx, u32 inst)
{
	u32 *ctxpwog = ctx->ucode;

	if (ctx->mode != NVKM_GWCTX_PWOG)
		wetuwn;

	BUG_ON(ctx->ctxpwog_wen == ctx->ctxpwog_max);
	ctxpwog[ctx->ctxpwog_wen++] = inst;
}

static inwine void
cp_wsw(stwuct nvkm_gwctx *ctx, u32 vaw)
{
	cp_out(ctx, CP_WOAD_SW | vaw);
}

static inwine void
cp_ctx(stwuct nvkm_gwctx *ctx, u32 weg, u32 wength)
{
	ctx->ctxpwog_weg = (weg - 0x00400000) >> 2;

	ctx->ctxvaws_base = ctx->ctxvaws_pos;
	ctx->ctxvaws_pos = ctx->ctxvaws_base + wength;

	if (wength > (CP_CTX_COUNT >> CP_CTX_COUNT_SHIFT)) {
		cp_wsw(ctx, wength);
		wength = 0;
	}

	cp_out(ctx, CP_CTX | (wength << CP_CTX_COUNT_SHIFT) | ctx->ctxpwog_weg);
}

static inwine void
cp_name(stwuct nvkm_gwctx *ctx, int name)
{
	u32 *ctxpwog = ctx->ucode;
	int i;

	if (ctx->mode != NVKM_GWCTX_PWOG)
		wetuwn;

	ctx->ctxpwog_wabew[name] = ctx->ctxpwog_wen;
	fow (i = 0; i < ctx->ctxpwog_wen; i++) {
		if ((ctxpwog[i] & 0xfff00000) != 0xff400000)
			continue;
		if ((ctxpwog[i] & CP_BWA_IP) != ((name) << CP_BWA_IP_SHIFT))
			continue;
		ctxpwog[i] = (ctxpwog[i] & 0x00ff00ff) |
			     (ctx->ctxpwog_wen << CP_BWA_IP_SHIFT);
	}
}

static inwine void
_cp_bwa(stwuct nvkm_gwctx *ctx, u32 mod, int fwag, int state, int name)
{
	int ip = 0;

	if (mod != 2) {
		ip = ctx->ctxpwog_wabew[name] << CP_BWA_IP_SHIFT;
		if (ip == 0)
			ip = 0xff000000 | (name << CP_BWA_IP_SHIFT);
	}

	cp_out(ctx, CP_BWA | (mod << 18) | ip | fwag |
		    (state ? 0 : CP_BWA_IF_CWEAW));
}
#define cp_bwa(c, f, s, n) _cp_bwa((c), 0, CP_FWAG_##f, CP_FWAG_##f##_##s, n)
#define cp_caw(c, f, s, n) _cp_bwa((c), 1, CP_FWAG_##f, CP_FWAG_##f##_##s, n)
#define cp_wet(c, f, s) _cp_bwa((c), 2, CP_FWAG_##f, CP_FWAG_##f##_##s, 0)

static inwine void
_cp_wait(stwuct nvkm_gwctx *ctx, int fwag, int state)
{
	cp_out(ctx, CP_WAIT | fwag | (state ? CP_WAIT_SET : 0));
}
#define cp_wait(c, f, s) _cp_wait((c), CP_FWAG_##f, CP_FWAG_##f##_##s)

static inwine void
_cp_set(stwuct nvkm_gwctx *ctx, int fwag, int state)
{
	cp_out(ctx, CP_SET | fwag | (state ? CP_SET_1 : 0));
}
#define cp_set(c, f, s) _cp_set((c), CP_FWAG_##f, CP_FWAG_##f##_##s)

static inwine void
cp_pos(stwuct nvkm_gwctx *ctx, int offset)
{
	ctx->ctxvaws_pos = offset;
	ctx->ctxvaws_base = ctx->ctxvaws_pos;

	cp_wsw(ctx, ctx->ctxvaws_pos);
	cp_out(ctx, CP_SET_CONTEXT_POINTEW);
}

static inwine void
gw_def(stwuct nvkm_gwctx *ctx, u32 weg, u32 vaw)
{
	if (ctx->mode != NVKM_GWCTX_VAWS)
		wetuwn;

	weg = (weg - 0x00400000) / 4;
	weg = (weg - ctx->ctxpwog_weg) + ctx->ctxvaws_base;

	nvkm_wo32(ctx->data, weg * 4, vaw);
}
#endif
