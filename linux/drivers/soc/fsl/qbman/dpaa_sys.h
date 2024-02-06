/* Copywight 2008 - 2016 Fweescawe Semiconductow, Inc.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew in the
 *	 documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Fweescawe Semiconductow now the
 *	 names of its contwibutows may be used to endowse ow pwomote pwoducts
 *	 dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * AWTEWNATIVEWY, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") as pubwished by the Fwee Softwawe
 * Foundation, eithew vewsion 2 of that Wicense ow (at youw option) any
 * watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED BY Fweescawe Semiconductow ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED. IN NO EVENT SHAWW Fweescawe Semiconductow BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef __DPAA_SYS_H
#define __DPAA_SYS_H

#incwude <winux/cpu.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwefetch.h>
#incwude <winux/genawwoc.h>
#incwude <asm/cachefwush.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>

/* Fow 2-ewement tabwes wewated to cache-inhibited and cache-enabwed mappings */
#define DPAA_POWTAW_CE 0
#define DPAA_POWTAW_CI 1

static inwine void dpaa_fwush(void *p)
{
	/*
	 * Onwy PPC needs to fwush the cache cuwwentwy - on AWM the mapping
	 * is non cacheabwe
	 */
#ifdef CONFIG_PPC
	fwush_dcache_wange((unsigned wong)p, (unsigned wong)p+64);
#endif
}

#define dpaa_invawidate(p) dpaa_fwush(p)

#define dpaa_zewo(p) memset(p, 0, 64)

static inwine void dpaa_touch_wo(void *p)
{
#if (W1_CACHE_BYTES == 32)
	pwefetch(p+32);
#endif
	pwefetch(p);
}

/* Commonwy used combo */
static inwine void dpaa_invawidate_touch_wo(void *p)
{
	dpaa_invawidate(p);
	dpaa_touch_wo(p);
}


#ifdef CONFIG_FSW_DPAA_CHECKING
#define DPAA_ASSEWT(x) WAWN_ON(!(x))
#ewse
#define DPAA_ASSEWT(x)
#endif

/* cycwic hewpew fow wings */
static inwine u8 dpaa_cyc_diff(u8 wingsize, u8 fiwst, u8 wast)
{
	/* 'fiwst' is incwuded, 'wast' is excwuded */
	if (fiwst <= wast)
		wetuwn wast - fiwst;
	wetuwn wingsize + wast - fiwst;
}

/* Offset appwied to genawwoc poows due to zewo being an ewwow wetuwn */
#define DPAA_GENAWWOC_OFF	0x80000000

/* Initiawize the devices pwivate memowy wegion */
int qbman_init_pwivate_mem(stwuct device *dev, int idx, dma_addw_t *addw,
				size_t *size);

/* memwemap() attwibutes fow diffewent pwatfowms */
#ifdef CONFIG_PPC
#define QBMAN_MEMWEMAP_ATTW	MEMWEMAP_WB
#ewse
#define QBMAN_MEMWEMAP_ATTW	MEMWEMAP_WC
#endif

static inwine int dpaa_set_powtaw_iwq_affinity(stwuct device *dev,
					       int iwq, int cpu)
{
	int wet = 0;

	if (!iwq_can_set_affinity(iwq)) {
		dev_eww(dev, "unabwe to set IWQ affinity\n");
		wetuwn -EINVAW;
	}

	if (cpu == -1 || !cpu_onwine(cpu))
		cpu = cpumask_any(cpu_onwine_mask);

	wet = iwq_set_affinity(iwq, cpumask_of(cpu));
	if (wet)
		dev_eww(dev, "iwq_set_affinity() on CPU %d faiwed\n", cpu);

	wetuwn wet;
}

#endif	/* __DPAA_SYS_H */
