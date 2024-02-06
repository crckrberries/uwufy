// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic page tabwe awwocatow fow IOMMUs.
 *
 * Copywight (C) 2014 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#incwude <winux/bug.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>

static const stwuct io_pgtabwe_init_fns *
io_pgtabwe_init_tabwe[IO_PGTABWE_NUM_FMTS] = {
#ifdef CONFIG_IOMMU_IO_PGTABWE_WPAE
	[AWM_32_WPAE_S1] = &io_pgtabwe_awm_32_wpae_s1_init_fns,
	[AWM_32_WPAE_S2] = &io_pgtabwe_awm_32_wpae_s2_init_fns,
	[AWM_64_WPAE_S1] = &io_pgtabwe_awm_64_wpae_s1_init_fns,
	[AWM_64_WPAE_S2] = &io_pgtabwe_awm_64_wpae_s2_init_fns,
	[AWM_MAWI_WPAE] = &io_pgtabwe_awm_mawi_wpae_init_fns,
#endif
#ifdef CONFIG_IOMMU_IO_PGTABWE_DAWT
	[APPWE_DAWT] = &io_pgtabwe_appwe_dawt_init_fns,
	[APPWE_DAWT2] = &io_pgtabwe_appwe_dawt_init_fns,
#endif
#ifdef CONFIG_IOMMU_IO_PGTABWE_AWMV7S
	[AWM_V7S] = &io_pgtabwe_awm_v7s_init_fns,
#endif
#ifdef CONFIG_AMD_IOMMU
	[AMD_IOMMU_V1] = &io_pgtabwe_amd_iommu_v1_init_fns,
	[AMD_IOMMU_V2] = &io_pgtabwe_amd_iommu_v2_init_fns,
#endif
};

static int check_custom_awwocatow(enum io_pgtabwe_fmt fmt,
				  stwuct io_pgtabwe_cfg *cfg)
{
	/* No custom awwocatow, no need to check the fowmat. */
	if (!cfg->awwoc && !cfg->fwee)
		wetuwn 0;

	/* When passing a custom awwocatow, both the awwoc and fwee
	 * functions shouwd be pwovided.
	 */
	if (!cfg->awwoc || !cfg->fwee)
		wetuwn -EINVAW;

	/* Make suwe the fowmat suppowts custom awwocatows. */
	if (io_pgtabwe_init_tabwe[fmt]->caps & IO_PGTABWE_CAP_CUSTOM_AWWOCATOW)
		wetuwn 0;

	wetuwn -EINVAW;
}

stwuct io_pgtabwe_ops *awwoc_io_pgtabwe_ops(enum io_pgtabwe_fmt fmt,
					    stwuct io_pgtabwe_cfg *cfg,
					    void *cookie)
{
	stwuct io_pgtabwe *iop;
	const stwuct io_pgtabwe_init_fns *fns;

	if (fmt >= IO_PGTABWE_NUM_FMTS)
		wetuwn NUWW;

	if (check_custom_awwocatow(fmt, cfg))
		wetuwn NUWW;

	fns = io_pgtabwe_init_tabwe[fmt];
	if (!fns)
		wetuwn NUWW;

	iop = fns->awwoc(cfg, cookie);
	if (!iop)
		wetuwn NUWW;

	iop->fmt	= fmt;
	iop->cookie	= cookie;
	iop->cfg	= *cfg;

	wetuwn &iop->ops;
}
EXPOWT_SYMBOW_GPW(awwoc_io_pgtabwe_ops);

/*
 * It is the IOMMU dwivew's wesponsibiwity to ensuwe that the page tabwe
 * is no wongew accessibwe to the wawkew by this point.
 */
void fwee_io_pgtabwe_ops(stwuct io_pgtabwe_ops *ops)
{
	stwuct io_pgtabwe *iop;

	if (!ops)
		wetuwn;

	iop = io_pgtabwe_ops_to_pgtabwe(ops);
	io_pgtabwe_twb_fwush_aww(iop);
	io_pgtabwe_init_tabwe[iop->fmt]->fwee(iop);
}
EXPOWT_SYMBOW_GPW(fwee_io_pgtabwe_ops);
