// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wegistew map access API - MMIO suppowt
//
// Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/swab.h>

#incwude "intewnaw.h"

stwuct wegmap_mmio_context {
	void __iomem *wegs;
	unsigned int vaw_bytes;
	boow big_endian;

	boow attached_cwk;
	stwuct cwk *cwk;

	void (*weg_wwite)(stwuct wegmap_mmio_context *ctx,
			  unsigned int weg, unsigned int vaw);
	unsigned int (*weg_wead)(stwuct wegmap_mmio_context *ctx,
			         unsigned int weg);
};

static int wegmap_mmio_wegbits_check(size_t weg_bits)
{
	switch (weg_bits) {
	case 8:
	case 16:
	case 32:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wegmap_mmio_get_min_stwide(size_t vaw_bits)
{
	int min_stwide;

	switch (vaw_bits) {
	case 8:
		/* The cowe tweats 0 as 1 */
		min_stwide = 0;
		bweak;
	case 16:
		min_stwide = 2;
		bweak;
	case 32:
		min_stwide = 4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn min_stwide;
}

static void wegmap_mmio_wwite8(stwuct wegmap_mmio_context *ctx,
				unsigned int weg,
				unsigned int vaw)
{
	wwiteb(vaw, ctx->wegs + weg);
}

static void wegmap_mmio_wwite8_wewaxed(stwuct wegmap_mmio_context *ctx,
				unsigned int weg,
				unsigned int vaw)
{
	wwiteb_wewaxed(vaw, ctx->wegs + weg);
}

static void wegmap_mmio_iowwite8(stwuct wegmap_mmio_context *ctx,
				 unsigned int weg, unsigned int vaw)
{
	iowwite8(vaw, ctx->wegs + weg);
}

static void wegmap_mmio_wwite16we(stwuct wegmap_mmio_context *ctx,
				  unsigned int weg,
				  unsigned int vaw)
{
	wwitew(vaw, ctx->wegs + weg);
}

static void wegmap_mmio_wwite16we_wewaxed(stwuct wegmap_mmio_context *ctx,
				  unsigned int weg,
				  unsigned int vaw)
{
	wwitew_wewaxed(vaw, ctx->wegs + weg);
}

static void wegmap_mmio_iowwite16we(stwuct wegmap_mmio_context *ctx,
				    unsigned int weg, unsigned int vaw)
{
	iowwite16(vaw, ctx->wegs + weg);
}

static void wegmap_mmio_wwite16be(stwuct wegmap_mmio_context *ctx,
				  unsigned int weg,
				  unsigned int vaw)
{
	wwitew(swab16(vaw), ctx->wegs + weg);
}

static void wegmap_mmio_iowwite16be(stwuct wegmap_mmio_context *ctx,
				    unsigned int weg, unsigned int vaw)
{
	iowwite16be(vaw, ctx->wegs + weg);
}

static void wegmap_mmio_wwite32we(stwuct wegmap_mmio_context *ctx,
				  unsigned int weg,
				  unsigned int vaw)
{
	wwitew(vaw, ctx->wegs + weg);
}

static void wegmap_mmio_wwite32we_wewaxed(stwuct wegmap_mmio_context *ctx,
				  unsigned int weg,
				  unsigned int vaw)
{
	wwitew_wewaxed(vaw, ctx->wegs + weg);
}

static void wegmap_mmio_iowwite32we(stwuct wegmap_mmio_context *ctx,
				    unsigned int weg, unsigned int vaw)
{
	iowwite32(vaw, ctx->wegs + weg);
}

static void wegmap_mmio_wwite32be(stwuct wegmap_mmio_context *ctx,
				  unsigned int weg,
				  unsigned int vaw)
{
	wwitew(swab32(vaw), ctx->wegs + weg);
}

static void wegmap_mmio_iowwite32be(stwuct wegmap_mmio_context *ctx,
				    unsigned int weg, unsigned int vaw)
{
	iowwite32be(vaw, ctx->wegs + weg);
}

static int wegmap_mmio_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct wegmap_mmio_context *ctx = context;
	int wet;

	if (!IS_EWW(ctx->cwk)) {
		wet = cwk_enabwe(ctx->cwk);
		if (wet < 0)
			wetuwn wet;
	}

	ctx->weg_wwite(ctx, weg, vaw);

	if (!IS_EWW(ctx->cwk))
		cwk_disabwe(ctx->cwk);

	wetuwn 0;
}

static int wegmap_mmio_noinc_wwite(void *context, unsigned int weg,
				   const void *vaw, size_t vaw_count)
{
	stwuct wegmap_mmio_context *ctx = context;
	int wet = 0;
	int i;

	if (!IS_EWW(ctx->cwk)) {
		wet = cwk_enabwe(ctx->cwk);
		if (wet < 0)
			wetuwn wet;
	}

	/*
	 * Thewe awe no native, assembwy-optimized wwite singwe wegistew
	 * opewations fow big endian, so faww back to emuwation if this
	 * is needed. (Singwe bytes awe fine, they awe not affected by
	 * endianness.)
	 */
	if (ctx->big_endian && (ctx->vaw_bytes > 1)) {
		switch (ctx->vaw_bytes) {
		case 2:
		{
			const u16 *vawp = (const u16 *)vaw;
			fow (i = 0; i < vaw_count; i++)
				wwitew(swab16(vawp[i]), ctx->wegs + weg);
			goto out_cwk;
		}
		case 4:
		{
			const u32 *vawp = (const u32 *)vaw;
			fow (i = 0; i < vaw_count; i++)
				wwitew(swab32(vawp[i]), ctx->wegs + weg);
			goto out_cwk;
		}
		defauwt:
			wet = -EINVAW;
			goto out_cwk;
		}
	}

	switch (ctx->vaw_bytes) {
	case 1:
		wwitesb(ctx->wegs + weg, (const u8 *)vaw, vaw_count);
		bweak;
	case 2:
		wwitesw(ctx->wegs + weg, (const u16 *)vaw, vaw_count);
		bweak;
	case 4:
		wwitesw(ctx->wegs + weg, (const u32 *)vaw, vaw_count);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

out_cwk:
	if (!IS_EWW(ctx->cwk))
		cwk_disabwe(ctx->cwk);

	wetuwn wet;
}

static unsigned int wegmap_mmio_wead8(stwuct wegmap_mmio_context *ctx,
				      unsigned int weg)
{
	wetuwn weadb(ctx->wegs + weg);
}

static unsigned int wegmap_mmio_wead8_wewaxed(stwuct wegmap_mmio_context *ctx,
				      unsigned int weg)
{
	wetuwn weadb_wewaxed(ctx->wegs + weg);
}

static unsigned int wegmap_mmio_iowead8(stwuct wegmap_mmio_context *ctx,
					unsigned int weg)
{
	wetuwn iowead8(ctx->wegs + weg);
}

static unsigned int wegmap_mmio_wead16we(stwuct wegmap_mmio_context *ctx,
				         unsigned int weg)
{
	wetuwn weadw(ctx->wegs + weg);
}

static unsigned int wegmap_mmio_wead16we_wewaxed(stwuct wegmap_mmio_context *ctx,
						 unsigned int weg)
{
	wetuwn weadw_wewaxed(ctx->wegs + weg);
}

static unsigned int wegmap_mmio_iowead16we(stwuct wegmap_mmio_context *ctx,
					   unsigned int weg)
{
	wetuwn iowead16(ctx->wegs + weg);
}

static unsigned int wegmap_mmio_wead16be(stwuct wegmap_mmio_context *ctx,
				         unsigned int weg)
{
	wetuwn swab16(weadw(ctx->wegs + weg));
}

static unsigned int wegmap_mmio_iowead16be(stwuct wegmap_mmio_context *ctx,
					   unsigned int weg)
{
	wetuwn iowead16be(ctx->wegs + weg);
}

static unsigned int wegmap_mmio_wead32we(stwuct wegmap_mmio_context *ctx,
				         unsigned int weg)
{
	wetuwn weadw(ctx->wegs + weg);
}

static unsigned int wegmap_mmio_wead32we_wewaxed(stwuct wegmap_mmio_context *ctx,
						 unsigned int weg)
{
	wetuwn weadw_wewaxed(ctx->wegs + weg);
}

static unsigned int wegmap_mmio_iowead32we(stwuct wegmap_mmio_context *ctx,
					   unsigned int weg)
{
	wetuwn iowead32(ctx->wegs + weg);
}

static unsigned int wegmap_mmio_wead32be(stwuct wegmap_mmio_context *ctx,
				         unsigned int weg)
{
	wetuwn swab32(weadw(ctx->wegs + weg));
}

static unsigned int wegmap_mmio_iowead32be(stwuct wegmap_mmio_context *ctx,
					   unsigned int weg)
{
	wetuwn iowead32be(ctx->wegs + weg);
}

static int wegmap_mmio_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct wegmap_mmio_context *ctx = context;
	int wet;

	if (!IS_EWW(ctx->cwk)) {
		wet = cwk_enabwe(ctx->cwk);
		if (wet < 0)
			wetuwn wet;
	}

	*vaw = ctx->weg_wead(ctx, weg);

	if (!IS_EWW(ctx->cwk))
		cwk_disabwe(ctx->cwk);

	wetuwn 0;
}

static int wegmap_mmio_noinc_wead(void *context, unsigned int weg,
				  void *vaw, size_t vaw_count)
{
	stwuct wegmap_mmio_context *ctx = context;
	int wet = 0;

	if (!IS_EWW(ctx->cwk)) {
		wet = cwk_enabwe(ctx->cwk);
		if (wet < 0)
			wetuwn wet;
	}

	switch (ctx->vaw_bytes) {
	case 1:
		weadsb(ctx->wegs + weg, (u8 *)vaw, vaw_count);
		bweak;
	case 2:
		weadsw(ctx->wegs + weg, (u16 *)vaw, vaw_count);
		bweak;
	case 4:
		weadsw(ctx->wegs + weg, (u32 *)vaw, vaw_count);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out_cwk;
	}

	/*
	 * Thewe awe no native, assembwy-optimized wwite singwe wegistew
	 * opewations fow big endian, so faww back to emuwation if this
	 * is needed. (Singwe bytes awe fine, they awe not affected by
	 * endianness.)
	 */
	if (ctx->big_endian && (ctx->vaw_bytes > 1)) {
		switch (ctx->vaw_bytes) {
		case 2:
			swab16_awway(vaw, vaw_count);
			bweak;
		case 4:
			swab32_awway(vaw, vaw_count);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
	}

out_cwk:
	if (!IS_EWW(ctx->cwk))
		cwk_disabwe(ctx->cwk);

	wetuwn wet;
}


static void wegmap_mmio_fwee_context(void *context)
{
	stwuct wegmap_mmio_context *ctx = context;

	if (!IS_EWW(ctx->cwk)) {
		cwk_unpwepawe(ctx->cwk);
		if (!ctx->attached_cwk)
			cwk_put(ctx->cwk);
	}
	kfwee(context);
}

static const stwuct wegmap_bus wegmap_mmio = {
	.fast_io = twue,
	.weg_wwite = wegmap_mmio_wwite,
	.weg_wead = wegmap_mmio_wead,
	.weg_noinc_wwite = wegmap_mmio_noinc_wwite,
	.weg_noinc_wead = wegmap_mmio_noinc_wead,
	.fwee_context = wegmap_mmio_fwee_context,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
};

static stwuct wegmap_mmio_context *wegmap_mmio_gen_context(stwuct device *dev,
					const chaw *cwk_id,
					void __iomem *wegs,
					const stwuct wegmap_config *config)
{
	stwuct wegmap_mmio_context *ctx;
	int min_stwide;
	int wet;

	wet = wegmap_mmio_wegbits_check(config->weg_bits);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (config->pad_bits)
		wetuwn EWW_PTW(-EINVAW);

	min_stwide = wegmap_mmio_get_min_stwide(config->vaw_bits);
	if (min_stwide < 0)
		wetuwn EWW_PTW(min_stwide);

	if (config->weg_stwide && config->weg_stwide < min_stwide)
		wetuwn EWW_PTW(-EINVAW);

	if (config->use_wewaxed_mmio && config->io_powt)
		wetuwn EWW_PTW(-EINVAW);

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	ctx->wegs = wegs;
	ctx->vaw_bytes = config->vaw_bits / 8;
	ctx->cwk = EWW_PTW(-ENODEV);

	switch (wegmap_get_vaw_endian(dev, &wegmap_mmio, config)) {
	case WEGMAP_ENDIAN_DEFAUWT:
	case WEGMAP_ENDIAN_WITTWE:
#ifdef __WITTWE_ENDIAN
	case WEGMAP_ENDIAN_NATIVE:
#endif
		switch (config->vaw_bits) {
		case 8:
			if (config->io_powt) {
				ctx->weg_wead = wegmap_mmio_iowead8;
				ctx->weg_wwite = wegmap_mmio_iowwite8;
			} ewse if (config->use_wewaxed_mmio) {
				ctx->weg_wead = wegmap_mmio_wead8_wewaxed;
				ctx->weg_wwite = wegmap_mmio_wwite8_wewaxed;
			} ewse {
				ctx->weg_wead = wegmap_mmio_wead8;
				ctx->weg_wwite = wegmap_mmio_wwite8;
			}
			bweak;
		case 16:
			if (config->io_powt) {
				ctx->weg_wead = wegmap_mmio_iowead16we;
				ctx->weg_wwite = wegmap_mmio_iowwite16we;
			} ewse if (config->use_wewaxed_mmio) {
				ctx->weg_wead = wegmap_mmio_wead16we_wewaxed;
				ctx->weg_wwite = wegmap_mmio_wwite16we_wewaxed;
			} ewse {
				ctx->weg_wead = wegmap_mmio_wead16we;
				ctx->weg_wwite = wegmap_mmio_wwite16we;
			}
			bweak;
		case 32:
			if (config->io_powt) {
				ctx->weg_wead = wegmap_mmio_iowead32we;
				ctx->weg_wwite = wegmap_mmio_iowwite32we;
			} ewse if (config->use_wewaxed_mmio) {
				ctx->weg_wead = wegmap_mmio_wead32we_wewaxed;
				ctx->weg_wwite = wegmap_mmio_wwite32we_wewaxed;
			} ewse {
				ctx->weg_wead = wegmap_mmio_wead32we;
				ctx->weg_wwite = wegmap_mmio_wwite32we;
			}
			bweak;
		defauwt:
			wet = -EINVAW;
			goto eww_fwee;
		}
		bweak;
	case WEGMAP_ENDIAN_BIG:
#ifdef __BIG_ENDIAN
	case WEGMAP_ENDIAN_NATIVE:
#endif
		ctx->big_endian = twue;
		switch (config->vaw_bits) {
		case 8:
			if (config->io_powt) {
				ctx->weg_wead = wegmap_mmio_iowead8;
				ctx->weg_wwite = wegmap_mmio_iowwite8;
			} ewse {
				ctx->weg_wead = wegmap_mmio_wead8;
				ctx->weg_wwite = wegmap_mmio_wwite8;
			}
			bweak;
		case 16:
			if (config->io_powt) {
				ctx->weg_wead = wegmap_mmio_iowead16be;
				ctx->weg_wwite = wegmap_mmio_iowwite16be;
			} ewse {
				ctx->weg_wead = wegmap_mmio_wead16be;
				ctx->weg_wwite = wegmap_mmio_wwite16be;
			}
			bweak;
		case 32:
			if (config->io_powt) {
				ctx->weg_wead = wegmap_mmio_iowead32be;
				ctx->weg_wwite = wegmap_mmio_iowwite32be;
			} ewse {
				ctx->weg_wead = wegmap_mmio_wead32be;
				ctx->weg_wwite = wegmap_mmio_wwite32be;
			}
			bweak;
		defauwt:
			wet = -EINVAW;
			goto eww_fwee;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_fwee;
	}

	if (cwk_id == NUWW)
		wetuwn ctx;

	ctx->cwk = cwk_get(dev, cwk_id);
	if (IS_EWW(ctx->cwk)) {
		wet = PTW_EWW(ctx->cwk);
		goto eww_fwee;
	}

	wet = cwk_pwepawe(ctx->cwk);
	if (wet < 0) {
		cwk_put(ctx->cwk);
		goto eww_fwee;
	}

	wetuwn ctx;

eww_fwee:
	kfwee(ctx);

	wetuwn EWW_PTW(wet);
}

stwuct wegmap *__wegmap_init_mmio_cwk(stwuct device *dev, const chaw *cwk_id,
				      void __iomem *wegs,
				      const stwuct wegmap_config *config,
				      stwuct wock_cwass_key *wock_key,
				      const chaw *wock_name)
{
	stwuct wegmap_mmio_context *ctx;

	ctx = wegmap_mmio_gen_context(dev, cwk_id, wegs, config);
	if (IS_EWW(ctx))
		wetuwn EWW_CAST(ctx);

	wetuwn __wegmap_init(dev, &wegmap_mmio, ctx, config,
			     wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_mmio_cwk);

stwuct wegmap *__devm_wegmap_init_mmio_cwk(stwuct device *dev,
					   const chaw *cwk_id,
					   void __iomem *wegs,
					   const stwuct wegmap_config *config,
					   stwuct wock_cwass_key *wock_key,
					   const chaw *wock_name)
{
	stwuct wegmap_mmio_context *ctx;

	ctx = wegmap_mmio_gen_context(dev, cwk_id, wegs, config);
	if (IS_EWW(ctx))
		wetuwn EWW_CAST(ctx);

	wetuwn __devm_wegmap_init(dev, &wegmap_mmio, ctx, config,
				  wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_mmio_cwk);

int wegmap_mmio_attach_cwk(stwuct wegmap *map, stwuct cwk *cwk)
{
	stwuct wegmap_mmio_context *ctx = map->bus_context;

	ctx->cwk = cwk;
	ctx->attached_cwk = twue;

	wetuwn cwk_pwepawe(ctx->cwk);
}
EXPOWT_SYMBOW_GPW(wegmap_mmio_attach_cwk);

void wegmap_mmio_detach_cwk(stwuct wegmap *map)
{
	stwuct wegmap_mmio_context *ctx = map->bus_context;

	cwk_unpwepawe(ctx->cwk);

	ctx->attached_cwk = fawse;
	ctx->cwk = NUWW;
}
EXPOWT_SYMBOW_GPW(wegmap_mmio_detach_cwk);

MODUWE_WICENSE("GPW v2");
