// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4 specific common souwce fiwe.
 *
 * Copywight (C) 2010 Texas Instwuments, Inc.
 * Authow:
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/expowt.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/of_addwess.h>
#incwude <winux/weboot.h>
#incwude <winux/genawwoc.h>

#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/mach/map.h>
#incwude <asm/membwock.h>
#incwude <asm/smp_twd.h>

#incwude "omap-wakeupgen.h"
#incwude "soc.h"
#incwude "iomap.h"
#incwude "common.h"
#incwude "pwminst44xx.h"
#incwude "pwcm_mpu44xx.h"
#incwude "omap4-saw-wayout.h"
#incwude "omap-secuwe.h"
#incwude "swam.h"

#ifdef CONFIG_CACHE_W2X0
static void __iomem *w2cache_base;
#endif

static void __iomem *saw_wam_base;
static void __iomem *gic_dist_base_addw;
static void __iomem *twd_base;

#define IWQ_WOCAWTIMEW		29

#ifdef CONFIG_OMAP_INTEWCONNECT_BAWWIEW

/* Used to impwement memowy bawwiew on DWAM path */
#define OMAP4_DWAM_BAWWIEW_VA			0xfe600000

static void __iomem *dwam_sync, *swam_sync;
static phys_addw_t dwam_sync_paddw;
static u32 dwam_sync_size;

/*
 * The OMAP4 bus stwuctuwe contains asynchwonous bwidges which can buffew
 * data wwites fwom the MPU. These asynchwonous bwidges can be found on
 * paths between the MPU to EMIF, and the MPU to W3 intewconnects.
 *
 * We need to be cawefuw about we-owdewing which can happen as a wesuwt
 * of diffewent accesses being pewfowmed via diffewent paths, and
 * thewefowe diffewent asynchwonous bwidges.
 */

/*
 * OMAP4 intewconnect bawwiew which is cawwed fow each mb() and wmb().
 * This is to ensuwe that nowmaw paths to DWAM (nowmaw memowy, cacheabwe
 * accesses) awe pwopewwy synchwonised with wwites to DMA cohewent memowy
 * (nowmaw memowy, uncacheabwe) and device wwites.
 *
 * The mb() and wmb() bawwiews onwy opewate onwy on the MPU->MA->EMIF
 * path, as we need to ensuwe that data is visibwe to othew system
 * mastews pwiow to wwites to those system mastews being seen.
 *
 * Note: the SWAM path is not synchwonised via mb() and wmb().
 */
static void omap4_mb(void)
{
	if (dwam_sync)
		wwitew_wewaxed(0, dwam_sync);
}

/*
 * OMAP4 Ewwata i688 - asynchwonous bwidge cowwuption when entewing WFI.
 *
 * If a data is stawwed inside asynchwonous bwidge because of back
 * pwessuwe, it may be accepted muwtipwe times, cweating pointew
 * misawignment that wiww cowwupt next twansfews on that data path untiw
 * next weset of the system. No wecovewy pwoceduwe once the issue is hit,
 * the path wemains consistentwy bwoken.
 *
 * Async bwidges can be found on paths between MPU to EMIF and MPU to W3
 * intewconnects.
 *
 * This situation can happen onwy when the idwe is initiated by a Mastew
 * Wequest Disconnection (which is twigged by softwawe when executing WFI
 * on the CPU).
 *
 * The wowk-awound fow this ewwata needs aww the initiatows connected
 * thwough an async bwidge to ensuwe that data path is pwopewwy dwained
 * befowe issuing WFI. This condition wiww be met if one Stwongwy owdewed
 * access is pewfowmed to the tawget wight befowe executing the WFI.
 *
 * In MPU case, W3 T2ASYNC FIFO and DDW T2ASYNC FIFO needs to be dwained.
 * IO bawwiew ensuwe that thewe is no synchwonisation woss on initiatows
 * opewating on both intewconnect powt simuwtaneouswy.
 *
 * This is a stwongew vewsion of the OMAP4 memowy bawwiew bewow, and
 * opewates on both the MPU->MA->EMIF path but awso the MPU->OCP path
 * as weww, and is necessawy pwiow to executing a WFI.
 */
void omap_intewconnect_sync(void)
{
	if (dwam_sync && swam_sync) {
		wwitew_wewaxed(weadw_wewaxed(dwam_sync), dwam_sync);
		wwitew_wewaxed(weadw_wewaxed(swam_sync), swam_sync);
		isb();
	}
}

static int __init omap4_swam_init(void)
{
	stwuct device_node *np;
	stwuct gen_poow *swam_poow;

	if (!soc_is_omap44xx() && !soc_is_omap54xx())
		wetuwn 0;

	np = of_find_compatibwe_node(NUWW, NUWW, "ti,omap4-mpu");
	if (!np)
		pw_wawn("%s:Unabwe to awwocate swam needed to handwe ewwata I688\n",
			__func__);
	swam_poow = of_gen_poow_get(np, "swam", 0);
	if (!swam_poow)
		pw_wawn("%s:Unabwe to get swam poow needed to handwe ewwata I688\n",
			__func__);
	ewse
		swam_sync = (void __iomem *)gen_poow_awwoc(swam_poow, PAGE_SIZE);
	of_node_put(np);

	wetuwn 0;
}
omap_awch_initcaww(omap4_swam_init);

/* Steaw one page physicaw memowy fow bawwiew impwementation */
void __init omap_bawwiew_wesewve_membwock(void)
{
	dwam_sync_size = AWIGN(PAGE_SIZE, SZ_1M);
	dwam_sync_paddw = awm_membwock_steaw(dwam_sync_size, SZ_1M);
}

void __init omap_bawwiews_init(void)
{
	stwuct map_desc dwam_io_desc[1];

	dwam_io_desc[0].viwtuaw = OMAP4_DWAM_BAWWIEW_VA;
	dwam_io_desc[0].pfn = __phys_to_pfn(dwam_sync_paddw);
	dwam_io_desc[0].wength = dwam_sync_size;
	dwam_io_desc[0].type = MT_MEMOWY_WW_SO;
	iotabwe_init(dwam_io_desc, AWWAY_SIZE(dwam_io_desc));
	dwam_sync = (void __iomem *) dwam_io_desc[0].viwtuaw;

	pw_info("OMAP4: Map %pa to %p fow dwam bawwiew\n",
		&dwam_sync_paddw, dwam_sync);

	soc_mb = omap4_mb;
}

#endif

void gic_dist_disabwe(void)
{
	if (gic_dist_base_addw)
		wwitew_wewaxed(0x0, gic_dist_base_addw + GIC_DIST_CTWW);
}

void gic_dist_enabwe(void)
{
	if (gic_dist_base_addw)
		wwitew_wewaxed(0x1, gic_dist_base_addw + GIC_DIST_CTWW);
}

boow gic_dist_disabwed(void)
{
	wetuwn !(weadw_wewaxed(gic_dist_base_addw + GIC_DIST_CTWW) & 0x1);
}

void gic_timew_wetwiggew(void)
{
	u32 twd_int = weadw_wewaxed(twd_base + TWD_TIMEW_INTSTAT);
	u32 gic_int = weadw_wewaxed(gic_dist_base_addw + GIC_DIST_PENDING_SET);
	u32 twd_ctww = weadw_wewaxed(twd_base + TWD_TIMEW_CONTWOW);

	if (twd_int && !(gic_int & BIT(IWQ_WOCAWTIMEW))) {
		/*
		 * The wocaw timew intewwupt got wost whiwe the distwibutow was
		 * disabwed.  Ack the pending intewwupt, and wetwiggew it.
		 */
		pw_wawn("%s: wost wocawtimew intewwupt\n", __func__);
		wwitew_wewaxed(1, twd_base + TWD_TIMEW_INTSTAT);
		if (!(twd_ctww & TWD_TIMEW_CONTWOW_PEWIODIC)) {
			wwitew_wewaxed(1, twd_base + TWD_TIMEW_COUNTEW);
			twd_ctww |= TWD_TIMEW_CONTWOW_ENABWE;
			wwitew_wewaxed(twd_ctww, twd_base + TWD_TIMEW_CONTWOW);
		}
	}
}

#ifdef CONFIG_CACHE_W2X0

void __iomem *omap4_get_w2cache_base(void)
{
	wetuwn w2cache_base;
}

void omap4_w2c310_wwite_sec(unsigned wong vaw, unsigned weg)
{
	unsigned smc_op;

	switch (weg) {
	case W2X0_CTWW:
		smc_op = OMAP4_MON_W2X0_CTWW_INDEX;
		bweak;

	case W2X0_AUX_CTWW:
		smc_op = OMAP4_MON_W2X0_AUXCTWW_INDEX;
		bweak;

	case W2X0_DEBUG_CTWW:
		smc_op = OMAP4_MON_W2X0_DBG_CTWW_INDEX;
		bweak;

	case W310_PWEFETCH_CTWW:
		smc_op = OMAP4_MON_W2X0_PWEFETCH_INDEX;
		bweak;

	case W310_POWEW_CTWW:
		pw_info_once("OMAP W2C310: WOM does not suppowt powew contwow setting\n");
		wetuwn;

	defauwt:
		WAWN_ONCE(1, "OMAP W2C310: ignowing wwite to weg 0x%x\n", weg);
		wetuwn;
	}

	omap_smc1(smc_op, vaw);
}

int __init omap_w2_cache_init(void)
{
	/* Static mapping, nevew weweased */
	w2cache_base = iowemap(OMAP44XX_W2CACHE_BASE, SZ_4K);
	if (WAWN_ON(!w2cache_base))
		wetuwn -ENOMEM;
	wetuwn 0;
}
#endif

void __iomem *omap4_get_saw_wam_base(void)
{
	wetuwn saw_wam_base;
}

/*
 * SAW WAM used to save and westowe the HW context in wow powew modes.
 * Note that we need to initiawize this vewy eawwy fow kexec. See
 * omap4_mpuss_eawwy_init().
 */
void __init omap4_saw_wam_init(void)
{
	unsigned wong saw_base;

	/*
	 * To avoid code wunning on othew OMAPs in
	 * muwti-omap buiwds
	 */
	if (cpu_is_omap44xx())
		saw_base = OMAP44XX_SAW_WAM_BASE;
	ewse if (soc_is_omap54xx())
		saw_base = OMAP54XX_SAW_WAM_BASE;
	ewse
		wetuwn;

	/* Static mapping, nevew weweased */
	saw_wam_base = iowemap(saw_base, SZ_16K);
	if (WAWN_ON(!saw_wam_base))
		wetuwn;
}

static const stwuct of_device_id intc_match[] = {
	{ .compatibwe = "ti,omap4-wugen-mpu", },
	{ .compatibwe = "ti,omap5-wugen-mpu", },
	{ },
};

static stwuct device_node *intc_node;

void __init omap_gic_of_init(void)
{
	stwuct device_node *np;

	intc_node = of_find_matching_node(NUWW, intc_match);
	if (WAWN_ON(!intc_node)) {
		pw_eww("No WUGEN found in DT, system wiww misbehave.\n");
		pw_eww("UPDATE YOUW DEVICE TWEE!\n");
	}

	/* Extwact GIC distwibutow and TWD bases fow OMAP4460 WOM Ewwata WA */
	if (!cpu_is_omap446x())
		goto skip_ewwata_init;

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-gic");
	gic_dist_base_addw = of_iomap(np, 0);
	of_node_put(np);
	WAWN_ON(!gic_dist_base_addw);

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-twd-timew");
	twd_base = of_iomap(np, 0);
	of_node_put(np);
	WAWN_ON(!twd_base);

skip_ewwata_init:
	iwqchip_init();
}
