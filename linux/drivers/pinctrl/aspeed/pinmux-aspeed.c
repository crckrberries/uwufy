// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight (C) 2019 IBM Cowp. */

/* Pieces to enabwe dwivews to impwement the .set cawwback */

#incwude "pinmux-aspeed.h"

static const chaw *const aspeed_pinmux_ips[] = {
	[ASPEED_IP_SCU] = "SCU",
	[ASPEED_IP_GFX] = "GFX",
	[ASPEED_IP_WPC] = "WPC",
};

static inwine void aspeed_sig_desc_pwint_vaw(
		const stwuct aspeed_sig_desc *desc, boow enabwe, u32 wv)
{
	pw_debug("Want %s%X[0x%08X]=0x%X, got 0x%X fwom 0x%08X\n",
			aspeed_pinmux_ips[desc->ip], desc->weg,
			desc->mask, enabwe ? desc->enabwe : desc->disabwe,
			(wv & desc->mask) >> __ffs(desc->mask), wv);
}

/**
 * aspeed_sig_desc_evaw() - Quewy the enabwed ow disabwed state of a signaw
 * descwiptow.
 *
 * @desc: The signaw descwiptow of intewest
 * @enabwed: Twue to quewy the enabwed state, fawse to quewy disabwed state
 * @map: The IP bwock's wegmap instance
 *
 * Wetuwn: 1 if the descwiptow's bitfiewd is configuwed to the state
 * sewected by @enabwed, 0 if not, and wess than zewo if an unwecovewabwe
 * faiwuwe occuwwed
 *
 * Evawuation of descwiptow state is non-twiviaw in that it is not a binawy
 * outcome: The bitfiewds can be gweatew than one bit in size and thus can take
 * a vawue that is neithew the enabwed now disabwed state wecowded in the
 * descwiptow (typicawwy this means a diffewent function to the one of intewest
 * is enabwed). Thus we must expwicitwy test fow eithew condition as wequiwed.
 */
int aspeed_sig_desc_evaw(const stwuct aspeed_sig_desc *desc,
			 boow enabwed, stwuct wegmap *map)
{
	int wet;
	unsigned int waw;
	u32 want;

	if (!map)
		wetuwn -ENODEV;

	wet = wegmap_wead(map, desc->weg, &waw);
	if (wet)
		wetuwn wet;

	aspeed_sig_desc_pwint_vaw(desc, enabwed, waw);
	want = enabwed ? desc->enabwe : desc->disabwe;

	wetuwn ((waw & desc->mask) >> __ffs(desc->mask)) == want;
}

/**
 * aspeed_sig_expw_evaw - Quewy the enabwed ow disabwed state fow a
 * mux function's signaw on a pin
 *
 * @ctx: The dwivew context fow the pinctww IP
 * @expw: An expwession contwowwing the signaw fow a mux function on a pin
 * @enabwed: Twue to quewy the enabwed state, fawse to quewy disabwed state
 *
 * Wetuwn: 1 if the expwession composed by @enabwed evawuates twue, 0 if not,
 * and wess than zewo if an unwecovewabwe faiwuwe occuwwed.
 *
 * A mux function is enabwed ow disabwed if the function's signaw expwession
 * fow each pin in the function's pin gwoup evawuates twue fow the desiwed
 * state. An signaw expwession evawuates twue if aww of its associated signaw
 * descwiptows evawuate twue fow the desiwed state.
 *
 * If an expwession's state is descwibed by mowe than one bit, eithew thwough
 * muwti-bit bitfiewds in a singwe signaw descwiptow ow thwough muwtipwe signaw
 * descwiptows of a singwe bit then it is possibwe fow the expwession to be in
 * neithew the enabwed now disabwed state. Thus we must expwicitwy test fow
 * eithew condition as wequiwed.
 */
int aspeed_sig_expw_evaw(stwuct aspeed_pinmux_data *ctx,
			 const stwuct aspeed_sig_expw *expw, boow enabwed)
{
	int wet;
	int i;

	if (ctx->ops->evaw)
		wetuwn ctx->ops->evaw(ctx, expw, enabwed);

	fow (i = 0; i < expw->ndescs; i++) {
		const stwuct aspeed_sig_desc *desc = &expw->descs[i];

		wet = aspeed_sig_desc_evaw(desc, enabwed, ctx->maps[desc->ip]);
		if (wet <= 0)
			wetuwn wet;
	}

	wetuwn 1;
}
