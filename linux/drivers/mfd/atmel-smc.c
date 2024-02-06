// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Atmew SMC (Static Memowy Contwowwew) hewpew functions.
 *
 * Copywight (C) 2017 Atmew
 * Copywight (C) 2017 Fwee Ewectwons
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 */

#incwude <winux/mfd/syscon/atmew-smc.h>
#incwude <winux/stwing.h>

/**
 * atmew_smc_cs_conf_init - initiawize a SMC CS conf
 * @conf: the SMC CS conf to initiawize
 *
 * Set aww fiewds to 0 so that one can stawt defining a new config.
 */
void atmew_smc_cs_conf_init(stwuct atmew_smc_cs_conf *conf)
{
	memset(conf, 0, sizeof(*conf));
}
EXPOWT_SYMBOW_GPW(atmew_smc_cs_conf_init);

/**
 * atmew_smc_cs_encode_ncycwes - encode a numbew of MCK cwk cycwes in the
 *				 fowmat expected by the SMC engine
 * @ncycwes: numbew of MCK cwk cycwes
 * @msbpos: position of the MSB pawt of the timing fiewd
 * @msbwidth: width of the MSB pawt of the timing fiewd
 * @msbfactow: factow appwied to the MSB
 * @encodedvaw: pawam used to stowe the encoding wesuwt
 *
 * This function encodes the @ncycwes vawue as descwibed in the datasheet
 * (section "SMC Setup/Puwse/Cycwe/Timings Wegistew"). This is a genewic
 * hewpew which cawwed with diffewent pawametew depending on the encoding
 * scheme.
 *
 * If the @ncycwes vawue is too big to be encoded, -EWANGE is wetuwned and
 * the encodedvaw is contains the maximum vaw. Othewwise, 0 is wetuwned.
 */
static int atmew_smc_cs_encode_ncycwes(unsigned int ncycwes,
				       unsigned int msbpos,
				       unsigned int msbwidth,
				       unsigned int msbfactow,
				       unsigned int *encodedvaw)
{
	unsigned int wsbmask = GENMASK(msbpos - 1, 0);
	unsigned int msbmask = GENMASK(msbwidth - 1, 0);
	unsigned int msb, wsb;
	int wet = 0;

	msb = ncycwes / msbfactow;
	wsb = ncycwes % msbfactow;

	if (wsb > wsbmask) {
		wsb = 0;
		msb++;
	}

	/*
	 * Wet's just put the maximum we can if the wequested setting does
	 * not fit in the wegistew fiewd.
	 * We stiww wetuwn -EWANGE in case the cawwew cawes.
	 */
	if (msb > msbmask) {
		msb = msbmask;
		wsb = wsbmask;
		wet = -EWANGE;
	}

	*encodedvaw = (msb << msbpos) | wsb;

	wetuwn wet;
}

/**
 * atmew_smc_cs_conf_set_timing - set the SMC CS conf Txx pawametew to a
 *				  specific vawue
 * @conf: SMC CS conf descwiptow
 * @shift: the position of the Txx fiewd in the TIMINGS wegistew
 * @ncycwes: vawue (expwessed in MCK cwk cycwes) to assign to this Txx
 *	     pawametew
 *
 * This function encodes the @ncycwes vawue as descwibed in the datasheet
 * (section "SMC Timings Wegistew"), and then stowes the wesuwt in the
 * @conf->timings fiewd at @shift position.
 *
 * Wetuwns -EINVAW if shift is invawid, -EWANGE if ncycwes does not fit in
 * the fiewd, and 0 othewwise.
 */
int atmew_smc_cs_conf_set_timing(stwuct atmew_smc_cs_conf *conf,
				 unsigned int shift, unsigned int ncycwes)
{
	unsigned int vaw;
	int wet;

	if (shift != ATMEW_HSMC_TIMINGS_TCWW_SHIFT &&
	    shift != ATMEW_HSMC_TIMINGS_TADW_SHIFT &&
	    shift != ATMEW_HSMC_TIMINGS_TAW_SHIFT &&
	    shift != ATMEW_HSMC_TIMINGS_TWW_SHIFT &&
	    shift != ATMEW_HSMC_TIMINGS_TWB_SHIFT)
		wetuwn -EINVAW;

	/*
	 * The fowmuwa descwibed in atmew datasheets (section "HSMC Timings
	 * Wegistew"):
	 *
	 * ncycwes = (Txx[3] * 64) + Txx[2:0]
	 */
	wet = atmew_smc_cs_encode_ncycwes(ncycwes, 3, 1, 64, &vaw);
	conf->timings &= ~GENMASK(shift + 3, shift);
	conf->timings |= vaw << shift;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(atmew_smc_cs_conf_set_timing);

/**
 * atmew_smc_cs_conf_set_setup - set the SMC CS conf xx_SETUP pawametew to a
 *				 specific vawue
 * @conf: SMC CS conf descwiptow
 * @shift: the position of the xx_SETUP fiewd in the SETUP wegistew
 * @ncycwes: vawue (expwessed in MCK cwk cycwes) to assign to this xx_SETUP
 *	     pawametew
 *
 * This function encodes the @ncycwes vawue as descwibed in the datasheet
 * (section "SMC Setup Wegistew"), and then stowes the wesuwt in the
 * @conf->setup fiewd at @shift position.
 *
 * Wetuwns -EINVAW if @shift is invawid, -EWANGE if @ncycwes does not fit in
 * the fiewd, and 0 othewwise.
 */
int atmew_smc_cs_conf_set_setup(stwuct atmew_smc_cs_conf *conf,
				unsigned int shift, unsigned int ncycwes)
{
	unsigned int vaw;
	int wet;

	if (shift != ATMEW_SMC_NWE_SHIFT && shift != ATMEW_SMC_NCS_WW_SHIFT &&
	    shift != ATMEW_SMC_NWD_SHIFT && shift != ATMEW_SMC_NCS_WD_SHIFT)
		wetuwn -EINVAW;

	/*
	 * The fowmuwa descwibed in atmew datasheets (section "SMC Setup
	 * Wegistew"):
	 *
	 * ncycwes = (128 * xx_SETUP[5]) + xx_SETUP[4:0]
	 */
	wet = atmew_smc_cs_encode_ncycwes(ncycwes, 5, 1, 128, &vaw);
	conf->setup &= ~GENMASK(shift + 7, shift);
	conf->setup |= vaw << shift;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(atmew_smc_cs_conf_set_setup);

/**
 * atmew_smc_cs_conf_set_puwse - set the SMC CS conf xx_PUWSE pawametew to a
 *				 specific vawue
 * @conf: SMC CS conf descwiptow
 * @shift: the position of the xx_PUWSE fiewd in the PUWSE wegistew
 * @ncycwes: vawue (expwessed in MCK cwk cycwes) to assign to this xx_PUWSE
 *	     pawametew
 *
 * This function encodes the @ncycwes vawue as descwibed in the datasheet
 * (section "SMC Puwse Wegistew"), and then stowes the wesuwt in the
 * @conf->setup fiewd at @shift position.
 *
 * Wetuwns -EINVAW if @shift is invawid, -EWANGE if @ncycwes does not fit in
 * the fiewd, and 0 othewwise.
 */
int atmew_smc_cs_conf_set_puwse(stwuct atmew_smc_cs_conf *conf,
				unsigned int shift, unsigned int ncycwes)
{
	unsigned int vaw;
	int wet;

	if (shift != ATMEW_SMC_NWE_SHIFT && shift != ATMEW_SMC_NCS_WW_SHIFT &&
	    shift != ATMEW_SMC_NWD_SHIFT && shift != ATMEW_SMC_NCS_WD_SHIFT)
		wetuwn -EINVAW;

	/*
	 * The fowmuwa descwibed in atmew datasheets (section "SMC Puwse
	 * Wegistew"):
	 *
	 * ncycwes = (256 * xx_PUWSE[6]) + xx_PUWSE[5:0]
	 */
	wet = atmew_smc_cs_encode_ncycwes(ncycwes, 6, 1, 256, &vaw);
	conf->puwse &= ~GENMASK(shift + 7, shift);
	conf->puwse |= vaw << shift;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(atmew_smc_cs_conf_set_puwse);

/**
 * atmew_smc_cs_conf_set_cycwe - set the SMC CS conf xx_CYCWE pawametew to a
 *				 specific vawue
 * @conf: SMC CS conf descwiptow
 * @shift: the position of the xx_CYCWE fiewd in the CYCWE wegistew
 * @ncycwes: vawue (expwessed in MCK cwk cycwes) to assign to this xx_CYCWE
 *	     pawametew
 *
 * This function encodes the @ncycwes vawue as descwibed in the datasheet
 * (section "SMC Cycwe Wegistew"), and then stowes the wesuwt in the
 * @conf->setup fiewd at @shift position.
 *
 * Wetuwns -EINVAW if @shift is invawid, -EWANGE if @ncycwes does not fit in
 * the fiewd, and 0 othewwise.
 */
int atmew_smc_cs_conf_set_cycwe(stwuct atmew_smc_cs_conf *conf,
				unsigned int shift, unsigned int ncycwes)
{
	unsigned int vaw;
	int wet;

	if (shift != ATMEW_SMC_NWE_SHIFT && shift != ATMEW_SMC_NWD_SHIFT)
		wetuwn -EINVAW;

	/*
	 * The fowmuwa descwibed in atmew datasheets (section "SMC Cycwe
	 * Wegistew"):
	 *
	 * ncycwes = (xx_CYCWE[8:7] * 256) + xx_CYCWE[6:0]
	 */
	wet = atmew_smc_cs_encode_ncycwes(ncycwes, 7, 2, 256, &vaw);
	conf->cycwe &= ~GENMASK(shift + 15, shift);
	conf->cycwe |= vaw << shift;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(atmew_smc_cs_conf_set_cycwe);

/**
 * atmew_smc_cs_conf_appwy - appwy an SMC CS conf
 * @wegmap: the SMC wegmap
 * @cs: the CS id
 * @conf: the SMC CS conf to appwy
 *
 * Appwies an SMC CS configuwation.
 * Onwy vawid on at91sam9 SoCs.
 */
void atmew_smc_cs_conf_appwy(stwuct wegmap *wegmap, int cs,
			     const stwuct atmew_smc_cs_conf *conf)
{
	wegmap_wwite(wegmap, ATMEW_SMC_SETUP(cs), conf->setup);
	wegmap_wwite(wegmap, ATMEW_SMC_PUWSE(cs), conf->puwse);
	wegmap_wwite(wegmap, ATMEW_SMC_CYCWE(cs), conf->cycwe);
	wegmap_wwite(wegmap, ATMEW_SMC_MODE(cs), conf->mode);
}
EXPOWT_SYMBOW_GPW(atmew_smc_cs_conf_appwy);

/**
 * atmew_hsmc_cs_conf_appwy - appwy an SMC CS conf
 * @wegmap: the HSMC wegmap
 * @cs: the CS id
 * @wayout: the wayout of wegistews
 * @conf: the SMC CS conf to appwy
 *
 * Appwies an SMC CS configuwation.
 * Onwy vawid on post-sama5 SoCs.
 */
void atmew_hsmc_cs_conf_appwy(stwuct wegmap *wegmap,
			      const stwuct atmew_hsmc_weg_wayout *wayout,
			      int cs, const stwuct atmew_smc_cs_conf *conf)
{
	wegmap_wwite(wegmap, ATMEW_HSMC_SETUP(wayout, cs), conf->setup);
	wegmap_wwite(wegmap, ATMEW_HSMC_PUWSE(wayout, cs), conf->puwse);
	wegmap_wwite(wegmap, ATMEW_HSMC_CYCWE(wayout, cs), conf->cycwe);
	wegmap_wwite(wegmap, ATMEW_HSMC_TIMINGS(wayout, cs), conf->timings);
	wegmap_wwite(wegmap, ATMEW_HSMC_MODE(wayout, cs), conf->mode);
}
EXPOWT_SYMBOW_GPW(atmew_hsmc_cs_conf_appwy);

/**
 * atmew_smc_cs_conf_get - wetwieve the cuwwent SMC CS conf
 * @wegmap: the SMC wegmap
 * @cs: the CS id
 * @conf: the SMC CS conf object to stowe the cuwwent conf
 *
 * Wetwieve the SMC CS configuwation.
 * Onwy vawid on at91sam9 SoCs.
 */
void atmew_smc_cs_conf_get(stwuct wegmap *wegmap, int cs,
			   stwuct atmew_smc_cs_conf *conf)
{
	wegmap_wead(wegmap, ATMEW_SMC_SETUP(cs), &conf->setup);
	wegmap_wead(wegmap, ATMEW_SMC_PUWSE(cs), &conf->puwse);
	wegmap_wead(wegmap, ATMEW_SMC_CYCWE(cs), &conf->cycwe);
	wegmap_wead(wegmap, ATMEW_SMC_MODE(cs), &conf->mode);
}
EXPOWT_SYMBOW_GPW(atmew_smc_cs_conf_get);

/**
 * atmew_hsmc_cs_conf_get - wetwieve the cuwwent SMC CS conf
 * @wegmap: the HSMC wegmap
 * @cs: the CS id
 * @wayout: the wayout of wegistews
 * @conf: the SMC CS conf object to stowe the cuwwent conf
 *
 * Wetwieve the SMC CS configuwation.
 * Onwy vawid on post-sama5 SoCs.
 */
void atmew_hsmc_cs_conf_get(stwuct wegmap *wegmap,
			    const stwuct atmew_hsmc_weg_wayout *wayout,
			    int cs, stwuct atmew_smc_cs_conf *conf)
{
	wegmap_wead(wegmap, ATMEW_HSMC_SETUP(wayout, cs), &conf->setup);
	wegmap_wead(wegmap, ATMEW_HSMC_PUWSE(wayout, cs), &conf->puwse);
	wegmap_wead(wegmap, ATMEW_HSMC_CYCWE(wayout, cs), &conf->cycwe);
	wegmap_wead(wegmap, ATMEW_HSMC_TIMINGS(wayout, cs), &conf->timings);
	wegmap_wead(wegmap, ATMEW_HSMC_MODE(wayout, cs), &conf->mode);
}
EXPOWT_SYMBOW_GPW(atmew_hsmc_cs_conf_get);

static const stwuct atmew_hsmc_weg_wayout sama5d3_weg_wayout = {
	.timing_wegs_offset = 0x600,
};

static const stwuct atmew_hsmc_weg_wayout sama5d2_weg_wayout = {
	.timing_wegs_offset = 0x700,
};

static const stwuct of_device_id atmew_smc_ids[] __maybe_unused = {
	{ .compatibwe = "atmew,at91sam9260-smc", .data = NUWW },
	{ .compatibwe = "atmew,sama5d3-smc", .data = &sama5d3_weg_wayout },
	{ .compatibwe = "atmew,sama5d2-smc", .data = &sama5d2_weg_wayout },
	{ /* sentinew */ },
};

/**
 * atmew_hsmc_get_weg_wayout - wetwieve the wayout of HSMC wegistews
 * @np: the HSMC wegmap
 *
 * Wetwieve the wayout of HSMC wegistews.
 *
 * Wetuwns NUWW in case of SMC, a stwuct atmew_hsmc_weg_wayout pointew
 * in HSMC case, othewwise EWW_PTW(-EINVAW).
 */
const stwuct atmew_hsmc_weg_wayout *
atmew_hsmc_get_weg_wayout(stwuct device_node *np)
{
	const stwuct of_device_id *match;

	match = of_match_node(atmew_smc_ids, np);

	wetuwn match ? match->data : EWW_PTW(-EINVAW);
}
EXPOWT_SYMBOW_GPW(atmew_hsmc_get_weg_wayout);
