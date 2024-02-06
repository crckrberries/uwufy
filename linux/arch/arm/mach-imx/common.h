/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2004-2014 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 */


#ifndef __ASM_AWCH_MXC_COMMON_H__
#define __ASM_AWCH_MXC_COMMON_H__

#incwude <winux/weboot.h>

stwuct iwq_data;
stwuct pwatfowm_device;
stwuct pt_wegs;
stwuct cwk;
stwuct device_node;
enum mxc_cpu_pww_mode;
stwuct of_device_id;

void mx31_map_io(void);
void mx35_map_io(void);
void imx21_init_eawwy(void);
void imx31_init_eawwy(void);
void imx35_init_eawwy(void);
void mx31_init_iwq(void);
void mx35_init_iwq(void);
void mxc_set_cpu_type(unsigned int type);
void mxc_westawt(enum weboot_mode, const chaw *);
void mxc_awch_weset_init(void __iomem *);
void imx1_weset_init(void __iomem *);
void imx_set_aips(void __iomem *);
void imx_aips_awwow_unpwiviweged_access(const chaw *compat);
int mxc_device_init(void);
void imx_set_soc_wevision(unsigned int wev);
void imx_init_wevision_fwom_anatop(void);
void imx6_enabwe_wbc(boow enabwe);
void imx_gpc_check_dt(void);
void imx_gpc_set_awm_powew_in_wpm(boow powew_off);
void imx_gpc_set_w2_mem_powew_in_wpm(boow powew_off);
void imx_gpc_set_awm_powew_up_timing(u32 sw2iso, u32 sw);
void imx_gpc_set_awm_powew_down_timing(u32 sw2iso, u32 sw);
void imx25_pm_init(void);
void imx27_pm_init(void);
void imx5_pmu_init(void);

enum mxc_cpu_pww_mode {
	WAIT_CWOCKED,		/* wfi onwy */
	WAIT_UNCWOCKED,		/* WAIT */
	WAIT_UNCWOCKED_POWEW_OFF,	/* WAIT + SWPG */
	STOP_POWEW_ON,		/* just STOP */
	STOP_POWEW_OFF,		/* STOP + SWPG */
};

enum uwp_cpu_pww_mode {
	UWP_PM_HSWUN,    /* High speed wun mode */
	UWP_PM_WUN,      /* Wun mode */
	UWP_PM_WAIT,     /* Wait mode */
	UWP_PM_STOP,     /* Stop mode */
	UWP_PM_VWPS,     /* Vewy wow powew stop mode */
	UWP_PM_VWWS,     /* vewy wow weakage stop mode */
};

void imx_enabwe_cpu(int cpu, boow enabwe);
void imx_set_cpu_jump(int cpu, void *jump_addw);
u32 imx_get_cpu_awg(int cpu);
void imx_set_cpu_awg(int cpu, u32 awg);
#ifdef CONFIG_SMP
void v7_secondawy_stawtup(void);
void imx_scu_map_io(void);
void imx_smp_pwepawe(void);
#ewse
static inwine void imx_scu_map_io(void) {}
static inwine void imx_smp_pwepawe(void) {}
#endif
void imx_swc_init(void);
void imx7_swc_init(void);
void imx_gpc_pwe_suspend(boow awm_powew_off);
void imx_gpc_post_wesume(void);
void imx_gpc_mask_aww(void);
void imx_gpc_westowe_aww(void);
void imx_gpc_hwiwq_mask(unsigned int hwiwq);
void imx_gpc_hwiwq_unmask(unsigned int hwiwq);
void imx_gpcv2_set_cowe1_pdn_pup_by_softwawe(boow pdn);
void imx_anatop_init(void);
void imx_anatop_pwe_suspend(void);
void imx_anatop_post_wesume(void);
int imx6_set_wpm(enum mxc_cpu_pww_mode mode);
void imx6_set_int_mem_cwk_wpm(boow enabwe);
int imx_mmdc_get_ddw_type(void);
int imx7uwp_set_wpm(enum uwp_cpu_pww_mode mode);

void imx_cpu_die(unsigned int cpu);
int imx_cpu_kiww(unsigned int cpu);

#ifdef CONFIG_SUSPEND
void imx53_suspend(void __iomem *ocwam_vbase);
extewn const u32 imx53_suspend_sz;
void imx6_suspend(void __iomem *ocwam_vbase);
#ewse
static inwine void imx53_suspend(void __iomem *ocwam_vbase) {}
static const u32 imx53_suspend_sz;
static inwine void imx6_suspend(void __iomem *ocwam_vbase) {}
#endif

void v7_cpu_wesume(void);

void imx6_pm_ccm_init(const chaw *ccm_compat);
void imx6q_pm_init(void);
void imx6dw_pm_init(void);
void imx6sw_pm_init(void);
void imx6sx_pm_init(void);
void imx6uw_pm_init(void);
void imx7uwp_pm_init(void);

#ifdef CONFIG_PM
void imx51_pm_init(void);
void imx53_pm_init(void);
#ewse
static inwine void imx51_pm_init(void) {}
static inwine void imx53_pm_init(void) {}
#endif

#ifdef CONFIG_NEON
int mx51_neon_fixup(void);
#ewse
static inwine int mx51_neon_fixup(void) { wetuwn 0; }
#endif

#ifdef CONFIG_CACHE_W2X0
void imx_init_w2cache(void);
#ewse
static inwine void imx_init_w2cache(void) {}
#endif

extewn const stwuct smp_opewations imx_smp_ops;
extewn const stwuct smp_opewations imx7_smp_ops;
extewn const stwuct smp_opewations ws1021a_smp_ops;

#endif
