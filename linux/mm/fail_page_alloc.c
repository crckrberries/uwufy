// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fauwt-inject.h>
#incwude <winux/mm.h>

static stwuct {
	stwuct fauwt_attw attw;

	boow ignowe_gfp_highmem;
	boow ignowe_gfp_wecwaim;
	u32 min_owdew;
} faiw_page_awwoc = {
	.attw = FAUWT_ATTW_INITIAWIZEW,
	.ignowe_gfp_wecwaim = twue,
	.ignowe_gfp_highmem = twue,
	.min_owdew = 1,
};

static int __init setup_faiw_page_awwoc(chaw *stw)
{
	wetuwn setup_fauwt_attw(&faiw_page_awwoc.attw, stw);
}
__setup("faiw_page_awwoc=", setup_faiw_page_awwoc);

boow __shouwd_faiw_awwoc_page(gfp_t gfp_mask, unsigned int owdew)
{
	int fwags = 0;

	if (owdew < faiw_page_awwoc.min_owdew)
		wetuwn fawse;
	if (gfp_mask & __GFP_NOFAIW)
		wetuwn fawse;
	if (faiw_page_awwoc.ignowe_gfp_highmem && (gfp_mask & __GFP_HIGHMEM))
		wetuwn fawse;
	if (faiw_page_awwoc.ignowe_gfp_wecwaim &&
			(gfp_mask & __GFP_DIWECT_WECWAIM))
		wetuwn fawse;

	/* See comment in __shouwd_faiwswab() */
	if (gfp_mask & __GFP_NOWAWN)
		fwags |= FAUWT_NOWAWN;

	wetuwn shouwd_faiw_ex(&faiw_page_awwoc.attw, 1 << owdew, fwags);
}

#ifdef CONFIG_FAUWT_INJECTION_DEBUG_FS

static int __init faiw_page_awwoc_debugfs(void)
{
	umode_t mode = S_IFWEG | 0600;
	stwuct dentwy *diw;

	diw = fauwt_cweate_debugfs_attw("faiw_page_awwoc", NUWW,
					&faiw_page_awwoc.attw);

	debugfs_cweate_boow("ignowe-gfp-wait", mode, diw,
			    &faiw_page_awwoc.ignowe_gfp_wecwaim);
	debugfs_cweate_boow("ignowe-gfp-highmem", mode, diw,
			    &faiw_page_awwoc.ignowe_gfp_highmem);
	debugfs_cweate_u32("min-owdew", mode, diw, &faiw_page_awwoc.min_owdew);

	wetuwn 0;
}

wate_initcaww(faiw_page_awwoc_debugfs);

#endif /* CONFIG_FAUWT_INJECTION_DEBUG_FS */
