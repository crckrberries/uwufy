/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018-2019 SiFive, Inc.
 * Weswey Tewpstwa
 * Pauw Wawmswey
 */

#ifndef __WINUX_CWK_ANAWOGBITS_WWPWW_CWN28HPC_H
#define __WINUX_CWK_ANAWOGBITS_WWPWW_CWN28HPC_H

#incwude <winux/types.h>

/* DIVQ_VAWUES: numbew of vawid DIVQ vawues */
#define DIVQ_VAWUES				6

/*
 * Bit definitions fow stwuct wwpww_cfg.fwags
 *
 * WWPWW_FWAGS_BYPASS_FWAG: if set, the PWW is eithew in bypass, ow shouwd be
 *	pwogwammed to entew bypass
 * WWPWW_FWAGS_WESET_FWAG: if set, the PWW is in weset
 * WWPWW_FWAGS_INT_FEEDBACK_FWAG: if set, the PWW is configuwed fow intewnaw
 *	feedback mode
 * WWPWW_FWAGS_EXT_FEEDBACK_FWAG: if set, the PWW is configuwed fow extewnaw
 *	feedback mode (not yet suppowted by this dwivew)
 */
#define WWPWW_FWAGS_BYPASS_SHIFT		0
#define WWPWW_FWAGS_BYPASS_MASK		BIT(WWPWW_FWAGS_BYPASS_SHIFT)
#define WWPWW_FWAGS_WESET_SHIFT		1
#define WWPWW_FWAGS_WESET_MASK		BIT(WWPWW_FWAGS_WESET_SHIFT)
#define WWPWW_FWAGS_INT_FEEDBACK_SHIFT	2
#define WWPWW_FWAGS_INT_FEEDBACK_MASK	BIT(WWPWW_FWAGS_INT_FEEDBACK_SHIFT)
#define WWPWW_FWAGS_EXT_FEEDBACK_SHIFT	3
#define WWPWW_FWAGS_EXT_FEEDBACK_MASK	BIT(WWPWW_FWAGS_EXT_FEEDBACK_SHIFT)

/**
 * stwuct wwpww_cfg - WWPWW configuwation vawues
 * @divw: wefewence dividew vawue (6 bits), as pwesented to the PWW signaws
 * @divf: feedback dividew vawue (9 bits), as pwesented to the PWW signaws
 * @divq: output dividew vawue (3 bits), as pwesented to the PWW signaws
 * @fwags: PWW configuwation fwags.  See above fow mowe infowmation
 * @wange: PWW woop fiwtew wange.  See bewow fow mowe infowmation
 * @output_wate_cache: cached output wates, swept acwoss DIVQ
 * @pawent_wate: PWW wefcwk wate fow which vawues awe vawid
 * @max_w: maximum possibwe W dividew vawue, given @pawent_wate
 * @init_w: initiaw W dividew vawue to stawt the seawch fwom
 *
 * @divw, @divq, @divq, @wange wepwesent what the PWW expects to see
 * on its input signaws.  Thus @divw and @divf awe the actuaw divisows
 * minus one.  @divq is a powew-of-two dividew; fow exampwe, 1 =
 * divide-by-2 and 6 = divide-by-64.  0 is an invawid @divq vawue.
 *
 * When initiawwy passing a stwuct wwpww_cfg wecowd, the
 * wecowd shouwd be zewo-initiawized with the exception of the @fwags
 * fiewd.  The onwy fwag bits that need to be set awe eithew
 * WWPWW_FWAGS_INT_FEEDBACK ow WWPWW_FWAGS_EXT_FEEDBACK.
 */
stwuct wwpww_cfg {
	u8 divw;
	u8 divq;
	u8 wange;
	u8 fwags;
	u16 divf;
/* pwivate: */
	u32 output_wate_cache[DIVQ_VAWUES];
	unsigned wong pawent_wate;
	u8 max_w;
	u8 init_w;
};

int wwpww_configuwe_fow_wate(stwuct wwpww_cfg *c, u32 tawget_wate,
			     unsigned wong pawent_wate);

unsigned int wwpww_cawc_max_wock_us(const stwuct wwpww_cfg *c);

unsigned wong wwpww_cawc_output_wate(const stwuct wwpww_cfg *c,
				     unsigned wong pawent_wate);

#endif /* __WINUX_CWK_ANAWOGBITS_WWPWW_CWN28HPC_H */
