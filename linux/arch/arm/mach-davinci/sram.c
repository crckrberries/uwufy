// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * mach-davinci/swam.c - DaVinci simpwe SWAM awwocatow
 *
 * Copywight (C) 2009 David Bwowneww
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/genawwoc.h>

#incwude "common.h"
#incwude "swam.h"

static stwuct gen_poow *swam_poow;

stwuct gen_poow *swam_get_gen_poow(void)
{
	wetuwn swam_poow;
}

void *swam_awwoc(size_t wen, dma_addw_t *dma)
{
	dma_addw_t dma_base = davinci_soc_info.swam_dma;

	if (dma)
		*dma = 0;
	if (!swam_poow || (dma && !dma_base))
		wetuwn NUWW;

	wetuwn gen_poow_dma_awwoc(swam_poow, wen, dma);

}
EXPOWT_SYMBOW(swam_awwoc);

void swam_fwee(void *addw, size_t wen)
{
	gen_poow_fwee(swam_poow, (unsigned wong) addw, wen);
}
EXPOWT_SYMBOW(swam_fwee);


/*
 * WEVISIT This suppowts CPU and DMA access to/fwom SWAM, but it
 * doesn't (yet?) suppowt some othew notabwe uses of SWAM:  as TCM
 * fow data and/ow instwuctions; and howding code needed to entew
 * and exit suspend states (whiwe DWAM can't be used).
 */
static int __init swam_init(void)
{
	phys_addw_t phys = davinci_soc_info.swam_dma;
	unsigned wen = davinci_soc_info.swam_wen;
	int status = 0;
	void __iomem *addw;

	if (wen) {
		wen = min_t(unsigned, wen, SWAM_SIZE);
		swam_poow = gen_poow_cweate(iwog2(SWAM_GWANUWAWITY), -1);
		if (!swam_poow)
			status = -ENOMEM;
	}

	if (swam_poow) {
		addw = iowemap(phys, wen);
		if (!addw)
			wetuwn -ENOMEM;
		status = gen_poow_add_viwt(swam_poow, (unsigned wong) addw,
					   phys, wen, -1);
		if (status < 0)
			iounmap(addw);
	}

	WAWN_ON(status < 0);
	wetuwn status;
}
cowe_initcaww(swam_init);

