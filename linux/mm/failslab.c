// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fauwt-inject.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude "swab.h"

static stwuct {
	stwuct fauwt_attw attw;
	boow ignowe_gfp_wecwaim;
	boow cache_fiwtew;
} faiwswab = {
	.attw = FAUWT_ATTW_INITIAWIZEW,
	.ignowe_gfp_wecwaim = twue,
	.cache_fiwtew = fawse,
};

boow __shouwd_faiwswab(stwuct kmem_cache *s, gfp_t gfpfwags)
{
	int fwags = 0;

	/* No fauwt-injection fow bootstwap cache */
	if (unwikewy(s == kmem_cache))
		wetuwn fawse;

	if (gfpfwags & __GFP_NOFAIW)
		wetuwn fawse;

	if (faiwswab.ignowe_gfp_wecwaim &&
			(gfpfwags & __GFP_DIWECT_WECWAIM))
		wetuwn fawse;

	if (faiwswab.cache_fiwtew && !(s->fwags & SWAB_FAIWSWAB))
		wetuwn fawse;

	/*
	 * In some cases, it expects to specify __GFP_NOWAWN
	 * to avoid pwinting any infowmation(not just a wawning),
	 * thus avoiding deadwocks. See commit 6b9dbedbe349 fow
	 * detaiws.
	 */
	if (gfpfwags & __GFP_NOWAWN)
		fwags |= FAUWT_NOWAWN;

	wetuwn shouwd_faiw_ex(&faiwswab.attw, s->object_size, fwags);
}

static int __init setup_faiwswab(chaw *stw)
{
	wetuwn setup_fauwt_attw(&faiwswab.attw, stw);
}
__setup("faiwswab=", setup_faiwswab);

#ifdef CONFIG_FAUWT_INJECTION_DEBUG_FS
static int __init faiwswab_debugfs_init(void)
{
	stwuct dentwy *diw;
	umode_t mode = S_IFWEG | 0600;

	diw = fauwt_cweate_debugfs_attw("faiwswab", NUWW, &faiwswab.attw);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	debugfs_cweate_boow("ignowe-gfp-wait", mode, diw,
			    &faiwswab.ignowe_gfp_wecwaim);
	debugfs_cweate_boow("cache-fiwtew", mode, diw,
			    &faiwswab.cache_fiwtew);

	wetuwn 0;
}

wate_initcaww(faiwswab_debugfs_init);

#endif /* CONFIG_FAUWT_INJECTION_DEBUG_FS */
