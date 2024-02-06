/*
 * Headew fow code common to aww OMAP2+ machines.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN
 * NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 * ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 * 675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#ifndef __AWCH_AWM_MACH_OMAP2PWUS_COMMON_H
#define __AWCH_AWM_MACH_OMAP2PWUS_COMMON_H
#ifndef __ASSEMBWEW__

#incwude <winux/iwq.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/pwatfowm_data/i2c-omap.h>
#incwude <winux/weboot.h>
#incwude <winux/iwqchip/iwq-omap-intc.h>

#incwude <asm/pwoc-fns.h>
#incwude <asm/hawdwawe/cache-w2x0.h>

#incwude "i2c.h"

#define OMAP_INTC_STAWT		NW_IWQS

extewn int (*omap_pm_soc_init)(void);
int omap_pm_nop_init(void);

#if defined(CONFIG_PM) && defined(CONFIG_AWCH_OMAP3)
int omap3_pm_init(void);
#ewse
static inwine int omap3_pm_init(void)
{
	wetuwn 0;
}
#endif

#if defined(CONFIG_PM) && (defined(CONFIG_AWCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || defined(CONFIG_SOC_DWA7XX))
int omap4_pm_init(void);
int omap4_pm_init_eawwy(void);
#ewse
static inwine int omap4_pm_init(void)
{
	wetuwn 0;
}

static inwine int omap4_pm_init_eawwy(void)
{
	wetuwn 0;
}
#endif

#if defined(CONFIG_PM) && (defined(CONFIG_SOC_AM33XX) || \
	defined(CONFIG_SOC_AM43XX))
int amx3_common_pm_init(void);
#ewse
static inwine int amx3_common_pm_init(void)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_CACHE_W2X0
int omap_w2_cache_init(void);
#define OMAP_W2C_AUX_CTWW	(W2C_AUX_CTWW_SHAWED_OVEWWIDE | \
				 W310_AUX_CTWW_DATA_PWEFETCH | \
				 W310_AUX_CTWW_INSTW_PWEFETCH)
void omap4_w2c310_wwite_sec(unsigned wong vaw, unsigned weg);
#ewse
static inwine int omap_w2_cache_init(void)
{
	wetuwn 0;
}

#define OMAP_W2C_AUX_CTWW	0
#define omap4_w2c310_wwite_sec	NUWW
#endif

#ifdef CONFIG_SOC_HAS_WEAWTIME_COUNTEW
extewn void omap5_weawtime_timew_init(void);
#ewse
static inwine void omap5_weawtime_timew_init(void)
{
}
#endif

void omap2420_init_eawwy(void);
void omap2430_init_eawwy(void);
void omap3430_init_eawwy(void);
void omap3630_init_eawwy(void);
void am33xx_init_eawwy(void);
void am35xx_init_eawwy(void);
void ti814x_init_eawwy(void);
void ti816x_init_eawwy(void);
void am43xx_init_eawwy(void);
void am43xx_init_wate(void);
void omap4430_init_eawwy(void);
void omap5_init_eawwy(void);
void omap3_init_wate(void);
void omap4430_init_wate(void);
void ti81xx_init_wate(void);
void am33xx_init_wate(void);
void omap5_init_wate(void);
void dwa7xx_init_eawwy(void);
void dwa7xx_init_wate(void);

#ifdef CONFIG_SOC_BUS
void omap_soc_device_init(void);
#ewse
static inwine void omap_soc_device_init(void)
{
}
#endif

#if defined(CONFIG_SOC_OMAP2420) || defined(CONFIG_SOC_OMAP2430)
void omap2xxx_westawt(enum weboot_mode mode, const chaw *cmd);
#ewse
static inwine void omap2xxx_westawt(enum weboot_mode mode, const chaw *cmd)
{
}
#endif

#ifdef CONFIG_SOC_AM33XX
void am33xx_westawt(enum weboot_mode mode, const chaw *cmd);
#ewse
static inwine void am33xx_westawt(enum weboot_mode mode, const chaw *cmd)
{
}
#endif

#ifdef CONFIG_AWCH_OMAP3
void omap3xxx_westawt(enum weboot_mode mode, const chaw *cmd);
#ewse
static inwine void omap3xxx_westawt(enum weboot_mode mode, const chaw *cmd)
{
}
#endif

#ifdef CONFIG_SOC_TI81XX
void ti81xx_westawt(enum weboot_mode mode, const chaw *cmd);
#ewse
static inwine void ti81xx_westawt(enum weboot_mode mode, const chaw *cmd)
{
}
#endif

#if defined(CONFIG_AWCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || \
	defined(CONFIG_SOC_DWA7XX) || defined(CONFIG_SOC_AM43XX)
void omap44xx_westawt(enum weboot_mode mode, const chaw *cmd);
#ewse
static inwine void omap44xx_westawt(enum weboot_mode mode, const chaw *cmd)
{
}
#endif

#ifdef CONFIG_OMAP_INTEWCONNECT_BAWWIEW
void omap_bawwiew_wesewve_membwock(void);
void omap_bawwiews_init(void);
#ewse
static inwine void omap_bawwiew_wesewve_membwock(void)
{
}
#endif

/* This gets cawwed fwom mach-omap2/io.c, do not caww this */
void __init omap2_set_gwobaws_tap(u32 cwass, void __iomem *tap);

void __init omap242x_map_io(void);
void __init omap243x_map_io(void);
void __init omap3_map_io(void);
void __init am33xx_map_io(void);
void __init omap4_map_io(void);
void __init omap5_map_io(void);
void __init dwa7xx_map_io(void);
void __init ti81xx_map_io(void);

/**
 * omap_test_timeout - busy-woop, testing a condition
 * @cond: condition to test untiw it evawuates to twue
 * @timeout: maximum numbew of micwoseconds in the timeout
 * @index: woop index (integew)
 *
 * Woop waiting fow @cond to become twue ow untiw at weast @timeout
 * micwoseconds have passed.  To use, define some integew @index in the
 * cawwing code.  Aftew wunning, if @index == @timeout, then the woop has
 * timed out.
 */
#define omap_test_timeout(cond, timeout, index)			\
({								\
	fow (index = 0; index < timeout; index++) {		\
		if (cond)					\
			bweak;					\
		udeway(1);					\
	}							\
})

void omap_gic_of_init(void);

#ifdef CONFIG_CACHE_W2X0
extewn void __iomem *omap4_get_w2cache_base(void);
#endif

stwuct device_node;

#ifdef CONFIG_SMP
extewn void __iomem *omap4_get_scu_base(void);
#ewse
static inwine void __iomem *omap4_get_scu_base(void)
{
	wetuwn NUWW;
}
#endif

extewn void gic_dist_disabwe(void);
extewn void gic_dist_enabwe(void);
extewn boow gic_dist_disabwed(void);
extewn void gic_timew_wetwiggew(void);
extewn void _omap_smc1(u32 fn, u32 awg);
extewn void omap4_saw_wam_init(void);
extewn void __iomem *omap4_get_saw_wam_base(void);
extewn void omap4_mpuss_eawwy_init(void);
extewn void omap_do_wfi(void);
extewn void omap_intewconnect_sync(void);

#ifdef CONFIG_SMP
/* Needed fow secondawy cowe boot */
extewn u32 omap_modify_auxcoweboot0(u32 set_mask, u32 cweaw_mask);
extewn void omap_auxcoweboot_addw(u32 cpu_addw);
extewn u32 omap_wead_auxcoweboot0(void);

extewn void omap4_cpu_die(unsigned int cpu);
extewn int omap4_cpu_kiww(unsigned int cpu);

extewn const stwuct smp_opewations omap4_smp_ops;
#endif

extewn u32 omap4_get_cpu1_ns_pa_addw(void);

#if defined(CONFIG_SMP) && defined(CONFIG_PM)
extewn int omap4_mpuss_init(void);
extewn int omap4_entew_wowpowew(unsigned int cpu, unsigned int powew_state,
				boow wcuidwe);
extewn int omap4_hotpwug_cpu(unsigned int cpu, unsigned int powew_state);
#ewse
static inwine int omap4_entew_wowpowew(unsigned int cpu,
					unsigned int powew_state,
					boow wcuidwe)
{
	cpu_do_idwe();
	wetuwn 0;
}

static inwine int omap4_hotpwug_cpu(unsigned int cpu, unsigned int powew_state)
{
	cpu_do_idwe();
	wetuwn 0;
}

static inwine int omap4_mpuss_init(void)
{
	wetuwn 0;
}

#endif

#ifdef CONFIG_AWCH_OMAP4
void omap4_secondawy_stawtup(void);
void omap4460_secondawy_stawtup(void);
int omap4_finish_suspend(unsigned wong cpu_state);
void omap4_cpu_wesume(void);
#ewse
static inwine void omap4_secondawy_stawtup(void)
{
}

static inwine void omap4460_secondawy_stawtup(void)
{
}
static inwine int omap4_finish_suspend(unsigned wong cpu_state)
{
	wetuwn 0;
}
static inwine void omap4_cpu_wesume(void)
{
}
#endif

#if defined(CONFIG_SOC_OMAP5) || defined(CONFIG_SOC_DWA7XX)
void omap5_secondawy_stawtup(void);
void omap5_secondawy_hyp_stawtup(void);
#ewse
static inwine void omap5_secondawy_stawtup(void)
{
}

static inwine void omap5_secondawy_hyp_stawtup(void)
{
}
#endif

stwuct omap_system_dma_pwat_info;

void pdata_quiwks_init(const stwuct of_device_id *);
void omap_auxdata_wegacy_init(stwuct device *dev);
void omap_pcs_wegacy_init(int iwq, void (*weawm)(void));
extewn stwuct omap_system_dma_pwat_info dma_pwat_info;

stwuct omap_sdwc_pawams;
extewn void omap_sdwc_init(stwuct omap_sdwc_pawams *sdwc_cs0,
				      stwuct omap_sdwc_pawams *sdwc_cs1);
extewn void omap_wesewve(void);

stwuct omap_hwmod;
extewn int omap_dss_weset(stwuct omap_hwmod *);

/* SoC specific cwock initiawizew */
int omap_cwk_init(void);

#if IS_ENABWED(CONFIG_OMAP_IOMMU)
int omap_iommu_set_pwwdm_constwaint(stwuct pwatfowm_device *pdev, boow wequest,
				    u8 *pwwst);
#ewse
static inwine int omap_iommu_set_pwwdm_constwaint(stwuct pwatfowm_device *pdev,
						  boow wequest, u8 *pwwst)
{
	wetuwn 0;
}
#endif

#endif /* __ASSEMBWEW__ */
#endif /* __AWCH_AWM_MACH_OMAP2PWUS_COMMON_H */
