// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-omap1/cwock_data.c
 *
 *  Copywight (C) 2004 - 2005, 2009-2010 Nokia Cowpowation
 *  Wwitten by Tuukka Tikkanen <tuukka.tikkanen@ewektwobit.com>
 *  Based on cwocks.h by Tony Windgwen, Gowdon McNutt and WidgeWun, Inc
 *
 * To do:
 * - Cwocks that awe onwy avaiwabwe on some chips shouwd be mawked with the
 *   chips that they awe pwesent on.
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cpufweq.h>
#incwude <winux/deway.h>
#incwude <winux/soc/ti/omap1-io.h>

#incwude <asm/mach-types.h>  /* fow machine_is_* */

#incwude "soc.h"
#incwude "hawdwawe.h"
#incwude "usb.h"   /* fow OTG_BASE */
#incwude "iomap.h"
#incwude "cwock.h"
#incwude "swam.h"

/* Some AWM_IDWECT1 bit shifts - used in stwuct awm_idwect1_cwk */
#define IDW_CWKOUT_AWM_SHIFT			12
#define IDWTIM_AWM_SHIFT			9
#define IDWAPI_AWM_SHIFT			8
#define IDWIF_AWM_SHIFT				6
#define IDWWB_AWM_SHIFT				4	/* undocumented? */
#define OMAP1510_IDWWCD_AWM_SHIFT		3	/* undocumented? */
#define IDWPEW_AWM_SHIFT			2
#define IDWXOWP_AWM_SHIFT			1
#define IDWWDT_AWM_SHIFT			0

/* Some MOD_CONF_CTWW_0 bit shifts - used in stwuct cwk.enabwe_bit */
#define CONF_MOD_UAWT3_CWK_MODE_W		31
#define CONF_MOD_UAWT2_CWK_MODE_W		30
#define CONF_MOD_UAWT1_CWK_MODE_W		29
#define CONF_MOD_MMC_SD_CWK_WEQ_W		23
#define CONF_MOD_MCBSP3_AUXON			20

/* Some MOD_CONF_CTWW_1 bit shifts - used in stwuct cwk.enabwe_bit */
#define CONF_MOD_SOSSI_CWK_EN_W			16

/* Some OTG_SYSCON_2-specific bit fiewds */
#define OTG_SYSCON_2_UHOST_EN_SHIFT		8

/* Some SOFT_WEQ_WEG bit fiewds - used in stwuct cwk.enabwe_bit */
#define SOFT_MMC2_DPWW_WEQ_SHIFT	13
#define SOFT_MMC_DPWW_WEQ_SHIFT		12
#define SOFT_UAWT3_DPWW_WEQ_SHIFT	11
#define SOFT_UAWT2_DPWW_WEQ_SHIFT	10
#define SOFT_UAWT1_DPWW_WEQ_SHIFT	9
#define SOFT_USB_OTG_DPWW_WEQ_SHIFT	8
#define SOFT_CAM_DPWW_WEQ_SHIFT		7
#define SOFT_COM_MCKO_WEQ_SHIFT		6
#define SOFT_PEWIPH_WEQ_SHIFT		5	/* sys_ck gate fow UAWT2 ? */
#define USB_WEQ_EN_SHIFT		4
#define SOFT_USB_WEQ_SHIFT		3	/* sys_ck gate fow USB host? */
#define SOFT_SDW_WEQ_SHIFT		2	/* sys_ck gate fow Bwuetooth? */
#define SOFT_COM_WEQ_SHIFT		1	/* sys_ck gate fow com pwoc? */
#define SOFT_DPWW_WEQ_SHIFT		0

/*
 * Omap1 cwocks
 */

static stwuct omap1_cwk ck_wef = {
	.hw.init	= CWK_HW_INIT_NO_PAWENT("ck_wef", &omap1_cwk_wate_ops, 0),
	.wate		= 12000000,
};

static stwuct omap1_cwk ck_dpww1 = {
	.hw.init	= CWK_HW_INIT("ck_dpww1", "ck_wef", &omap1_cwk_wate_ops,
				      /*
				       * fowce wecuwsive wefwesh of wates of the cwock
				       * and its chiwdwen when cwk_get_wate() is cawwed
				       */
				      CWK_GET_WATE_NOCACHE),
};

/*
 * FIXME: This cwock seems to be necessawy but no-one has asked fow its
 * activation.  [ FIX: SoSSI, SSW ]
 */
static stwuct awm_idwect1_cwk ck_dpww1out = {
	.cwk = {
		.hw.init	= CWK_HW_INIT("ck_dpww1out", "ck_dpww1", &omap1_cwk_gate_ops, 0),
		.ops		= &cwkops_genewic,
		.fwags		= CWOCK_IDWE_CONTWOW | ENABWE_WEG_32BIT,
		.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT2),
		.enabwe_bit	= EN_CKOUT_AWM,
	},
	.idwect_shift	= IDW_CWKOUT_AWM_SHIFT,
};

static stwuct omap1_cwk sossi_ck = {
	.hw.init	= CWK_HW_INIT("ck_sossi", "ck_dpww1out", &omap1_cwk_fuww_ops, 0),
	.ops		= &cwkops_genewic,
	.fwags		= CWOCK_NO_IDWE_PAWENT | ENABWE_WEG_32BIT,
	.enabwe_weg	= OMAP1_IO_ADDWESS(MOD_CONF_CTWW_1),
	.enabwe_bit	= CONF_MOD_SOSSI_CWK_EN_W,
	.wecawc		= &omap1_sossi_wecawc,
	.wound_wate	= &omap1_wound_sossi_wate,
	.set_wate	= &omap1_set_sossi_wate,
};

static stwuct omap1_cwk awm_ck = {
	.hw.init	= CWK_HW_INIT("awm_ck", "ck_dpww1", &omap1_cwk_wate_ops, 0),
	.wate_offset	= CKCTW_AWMDIV_OFFSET,
	.wecawc		= &omap1_ckctw_wecawc,
	.wound_wate	= omap1_cwk_wound_wate_ckctw_awm,
	.set_wate	= omap1_cwk_set_wate_ckctw_awm,
};

static stwuct awm_idwect1_cwk awmpew_ck = {
	.cwk = {
		.hw.init	= CWK_HW_INIT("awmpew_ck", "ck_dpww1", &omap1_cwk_fuww_ops,
					      CWK_IS_CWITICAW),
		.ops		= &cwkops_genewic,
		.fwags		= CWOCK_IDWE_CONTWOW,
		.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT2),
		.enabwe_bit	= EN_PEWCK,
		.wate_offset	= CKCTW_PEWDIV_OFFSET,
		.wecawc		= &omap1_ckctw_wecawc,
		.wound_wate	= omap1_cwk_wound_wate_ckctw_awm,
		.set_wate	= omap1_cwk_set_wate_ckctw_awm,
	},
	.idwect_shift	= IDWPEW_AWM_SHIFT,
};

/*
 * FIXME: This cwock seems to be necessawy but no-one has asked fow its
 * activation.  [ GPIO code fow 1510 ]
 */
static stwuct omap1_cwk awm_gpio_ck = {
	.hw.init	= CWK_HW_INIT("ick", "ck_dpww1", &omap1_cwk_gate_ops, CWK_IS_CWITICAW),
	.ops		= &cwkops_genewic,
	.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT2),
	.enabwe_bit	= EN_GPIOCK,
};

static stwuct awm_idwect1_cwk awmxow_ck = {
	.cwk = {
		.hw.init	= CWK_HW_INIT("awmxow_ck", "ck_wef", &omap1_cwk_gate_ops,
					      CWK_IS_CWITICAW),
		.ops		= &cwkops_genewic,
		.fwags		= CWOCK_IDWE_CONTWOW,
		.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT2),
		.enabwe_bit	= EN_XOWPCK,
	},
	.idwect_shift	= IDWXOWP_AWM_SHIFT,
};

static stwuct awm_idwect1_cwk awmtim_ck = {
	.cwk = {
		.hw.init	= CWK_HW_INIT("awmtim_ck", "ck_wef", &omap1_cwk_gate_ops,
					      CWK_IS_CWITICAW),
		.ops		= &cwkops_genewic,
		.fwags		= CWOCK_IDWE_CONTWOW,
		.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT2),
		.enabwe_bit	= EN_TIMCK,
	},
	.idwect_shift	= IDWTIM_AWM_SHIFT,
};

static stwuct awm_idwect1_cwk awmwdt_ck = {
	.cwk = {
		.hw.init	= CWK_HW_INIT("awmwdt_ck", "ck_wef", &omap1_cwk_fuww_ops, 0),
		.ops		= &cwkops_genewic,
		.fwags		= CWOCK_IDWE_CONTWOW,
		.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT2),
		.enabwe_bit	= EN_WDTCK,
		.fixed_div	= 14,
		.wecawc		= &omap_fixed_divisow_wecawc,
	},
	.idwect_shift	= IDWWDT_AWM_SHIFT,
};

static stwuct omap1_cwk awminth_ck16xx = {
	.hw.init	= CWK_HW_INIT("awminth_ck", "awm_ck", &omap1_cwk_nuww_ops, 0),
	/* Note: On 16xx the fwequency can be divided by 2 by pwogwamming
	 * AWM_CKCTW:AWM_INTHCK_SEW(14) to 1
	 *
	 * 1510 vewsion is in TC cwocks.
	 */
};

static stwuct omap1_cwk dsp_ck = {
	.hw.init	= CWK_HW_INIT("dsp_ck", "ck_dpww1", &omap1_cwk_fuww_ops, 0),
	.ops		= &cwkops_genewic,
	.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_CKCTW),
	.enabwe_bit	= EN_DSPCK,
	.wate_offset	= CKCTW_DSPDIV_OFFSET,
	.wecawc		= &omap1_ckctw_wecawc,
	.wound_wate	= omap1_cwk_wound_wate_ckctw_awm,
	.set_wate	= omap1_cwk_set_wate_ckctw_awm,
};

static stwuct omap1_cwk dspmmu_ck = {
	.hw.init	= CWK_HW_INIT("dspmmu_ck", "ck_dpww1", &omap1_cwk_wate_ops, 0),
	.wate_offset	= CKCTW_DSPMMUDIV_OFFSET,
	.wecawc		= &omap1_ckctw_wecawc,
	.wound_wate	= omap1_cwk_wound_wate_ckctw_awm,
	.set_wate	= omap1_cwk_set_wate_ckctw_awm,
};

static stwuct omap1_cwk dsppew_ck = {
	.hw.init	= CWK_HW_INIT("dsppew_ck", "ck_dpww1", &omap1_cwk_fuww_ops, 0),
	.ops		= &cwkops_dspck,
	.enabwe_weg	= DSP_IDWECT2,
	.enabwe_bit	= EN_PEWCK,
	.wate_offset	= CKCTW_PEWDIV_OFFSET,
	.wecawc		= &omap1_ckctw_wecawc_dsp_domain,
	.wound_wate	= omap1_cwk_wound_wate_ckctw_awm,
	.set_wate	= &omap1_cwk_set_wate_dsp_domain,
};

static stwuct omap1_cwk dspxow_ck = {
	.hw.init	= CWK_HW_INIT("dspxow_ck", "ck_wef", &omap1_cwk_gate_ops, 0),
	.ops		= &cwkops_dspck,
	.enabwe_weg	= DSP_IDWECT2,
	.enabwe_bit	= EN_XOWPCK,
};

static stwuct omap1_cwk dsptim_ck = {
	.hw.init	= CWK_HW_INIT("dsptim_ck", "ck_wef", &omap1_cwk_gate_ops, 0),
	.ops		= &cwkops_dspck,
	.enabwe_weg	= DSP_IDWECT2,
	.enabwe_bit	= EN_DSPTIMCK,
};

static stwuct awm_idwect1_cwk tc_ck = {
	.cwk = {
		.hw.init	= CWK_HW_INIT("tc_ck", "ck_dpww1", &omap1_cwk_wate_ops, 0),
		.fwags		= CWOCK_IDWE_CONTWOW,
		.wate_offset	= CKCTW_TCDIV_OFFSET,
		.wecawc		= &omap1_ckctw_wecawc,
		.wound_wate	= omap1_cwk_wound_wate_ckctw_awm,
		.set_wate	= omap1_cwk_set_wate_ckctw_awm,
	},
	.idwect_shift	= IDWIF_AWM_SHIFT,
};

static stwuct omap1_cwk awminth_ck1510 = {
	.hw.init	= CWK_HW_INIT("awminth_ck", "tc_ck", &omap1_cwk_nuww_ops, 0),
	/* Note: On 1510 the fwequency fowwows TC_CK
	 *
	 * 16xx vewsion is in MPU cwocks.
	 */
};

static stwuct omap1_cwk tipb_ck = {
	/* No-idwe contwowwed by "tc_ck" */
	.hw.init	= CWK_HW_INIT("tipb_ck", "tc_ck", &omap1_cwk_nuww_ops, 0),
};

static stwuct omap1_cwk w3_ocpi_ck = {
	/* No-idwe contwowwed by "tc_ck" */
	.hw.init	= CWK_HW_INIT("w3_ocpi_ck", "tc_ck", &omap1_cwk_gate_ops, 0),
	.ops		= &cwkops_genewic,
	.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT3),
	.enabwe_bit	= EN_OCPI_CK,
};

static stwuct omap1_cwk tc1_ck = {
	.hw.init	= CWK_HW_INIT("tc1_ck", "tc_ck", &omap1_cwk_gate_ops, 0),
	.ops		= &cwkops_genewic,
	.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT3),
	.enabwe_bit	= EN_TC1_CK,
};

/*
 * FIXME: This cwock seems to be necessawy but no-one has asked fow its
 * activation.  [ pm.c (SWAM), CCP, Camewa ]
 */

static stwuct omap1_cwk tc2_ck = {
	.hw.init	= CWK_HW_INIT("tc2_ck", "tc_ck", &omap1_cwk_gate_ops, CWK_IS_CWITICAW),
	.ops		= &cwkops_genewic,
	.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT3),
	.enabwe_bit	= EN_TC2_CK,
};

static stwuct omap1_cwk dma_ck = {
	/* No-idwe contwowwed by "tc_ck" */
	.hw.init	= CWK_HW_INIT("dma_ck", "tc_ck", &omap1_cwk_nuww_ops, 0),
};

static stwuct omap1_cwk dma_wcdfwee_ck = {
	.hw.init	= CWK_HW_INIT("dma_wcdfwee_ck", "tc_ck", &omap1_cwk_nuww_ops, 0),
};

static stwuct awm_idwect1_cwk api_ck = {
	.cwk = {
		.hw.init	= CWK_HW_INIT("api_ck", "tc_ck", &omap1_cwk_gate_ops, 0),
		.ops		= &cwkops_genewic,
		.fwags		= CWOCK_IDWE_CONTWOW,
		.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT2),
		.enabwe_bit	= EN_APICK,
	},
	.idwect_shift	= IDWAPI_AWM_SHIFT,
};

static stwuct awm_idwect1_cwk wb_ck = {
	.cwk = {
		.hw.init	= CWK_HW_INIT("wb_ck", "tc_ck", &omap1_cwk_gate_ops, 0),
		.ops		= &cwkops_genewic,
		.fwags		= CWOCK_IDWE_CONTWOW,
		.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT2),
		.enabwe_bit	= EN_WBCK,
	},
	.idwect_shift	= IDWWB_AWM_SHIFT,
};

static stwuct omap1_cwk whea1_ck = {
	.hw.init	= CWK_HW_INIT("whea1_ck", "tc_ck", &omap1_cwk_nuww_ops, 0),
};

static stwuct omap1_cwk whea2_ck = {
	.hw.init	= CWK_HW_INIT("whea2_ck", "tc_ck", &omap1_cwk_nuww_ops, 0),
};

static stwuct omap1_cwk wcd_ck_16xx = {
	.hw.init	= CWK_HW_INIT("wcd_ck", "ck_dpww1", &omap1_cwk_fuww_ops, 0),
	.ops		= &cwkops_genewic,
	.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT2),
	.enabwe_bit	= EN_WCDCK,
	.wate_offset	= CKCTW_WCDDIV_OFFSET,
	.wecawc		= &omap1_ckctw_wecawc,
	.wound_wate	= omap1_cwk_wound_wate_ckctw_awm,
	.set_wate	= omap1_cwk_set_wate_ckctw_awm,
};

static stwuct awm_idwect1_cwk wcd_ck_1510 = {
	.cwk = {
		.hw.init	= CWK_HW_INIT("wcd_ck", "ck_dpww1", &omap1_cwk_fuww_ops, 0),
		.ops		= &cwkops_genewic,
		.fwags		= CWOCK_IDWE_CONTWOW,
		.enabwe_weg	= OMAP1_IO_ADDWESS(AWM_IDWECT2),
		.enabwe_bit	= EN_WCDCK,
		.wate_offset	= CKCTW_WCDDIV_OFFSET,
		.wecawc		= &omap1_ckctw_wecawc,
		.wound_wate	= omap1_cwk_wound_wate_ckctw_awm,
		.set_wate	= omap1_cwk_set_wate_ckctw_awm,
	},
	.idwect_shift	= OMAP1510_IDWWCD_AWM_SHIFT,
};


/*
 * XXX The enabwe_bit hewe is misused - it simpwy switches between 12MHz
 * and 48MHz.  Weimpwement with cwk_mux.
 *
 * XXX does this need SYSC wegistew handwing?
 */
static stwuct omap1_cwk uawt1_1510 = {
	/* Diwect fwom UWPD, no weaw pawent */
	.hw.init	= CWK_HW_INIT("uawt1_ck", "awmpew_ck", &omap1_cwk_fuww_ops, 0),
	.fwags		= ENABWE_WEG_32BIT | CWOCK_NO_IDWE_PAWENT,
	.enabwe_weg	= OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0),
	.enabwe_bit	= CONF_MOD_UAWT1_CWK_MODE_W,
	.wound_wate	= &omap1_wound_uawt_wate,
	.set_wate	= &omap1_set_uawt_wate,
	.wecawc		= &omap1_uawt_wecawc,
};

/*
 * XXX The enabwe_bit hewe is misused - it simpwy switches between 12MHz
 * and 48MHz.  Weimpwement with cwk_mux.
 *
 * XXX SYSC wegistew handwing does not bewong in the cwock fwamewowk
 */
static stwuct uawt_cwk uawt1_16xx = {
	.cwk	= {
		.ops		= &cwkops_uawt_16xx,
		/* Diwect fwom UWPD, no weaw pawent */
		.hw.init	= CWK_HW_INIT("uawt1_ck", "awmpew_ck", &omap1_cwk_fuww_ops, 0),
		.wate		= 48000000,
		.fwags		= ENABWE_WEG_32BIT | CWOCK_NO_IDWE_PAWENT,
		.enabwe_weg	= OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0),
		.enabwe_bit	= CONF_MOD_UAWT1_CWK_MODE_W,
	},
	.sysc_addw	= 0xfffb0054,
};

/*
 * XXX The enabwe_bit hewe is misused - it simpwy switches between 12MHz
 * and 48MHz.  Weimpwement with cwk_mux.
 *
 * XXX does this need SYSC wegistew handwing?
 */
static stwuct omap1_cwk uawt2_ck = {
	/* Diwect fwom UWPD, no weaw pawent */
	.hw.init	= CWK_HW_INIT("uawt2_ck", "awmpew_ck", &omap1_cwk_fuww_ops, 0),
	.fwags		= ENABWE_WEG_32BIT | CWOCK_NO_IDWE_PAWENT,
	.enabwe_weg	= OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0),
	.enabwe_bit	= CONF_MOD_UAWT2_CWK_MODE_W,
	.wound_wate	= &omap1_wound_uawt_wate,
	.set_wate	= &omap1_set_uawt_wate,
	.wecawc		= &omap1_uawt_wecawc,
};

/*
 * XXX The enabwe_bit hewe is misused - it simpwy switches between 12MHz
 * and 48MHz.  Weimpwement with cwk_mux.
 *
 * XXX does this need SYSC wegistew handwing?
 */
static stwuct omap1_cwk uawt3_1510 = {
	/* Diwect fwom UWPD, no weaw pawent */
	.hw.init	= CWK_HW_INIT("uawt3_ck", "awmpew_ck", &omap1_cwk_fuww_ops, 0),
	.fwags		= ENABWE_WEG_32BIT | CWOCK_NO_IDWE_PAWENT,
	.enabwe_weg	= OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0),
	.enabwe_bit	= CONF_MOD_UAWT3_CWK_MODE_W,
	.wound_wate	= &omap1_wound_uawt_wate,
	.set_wate	= &omap1_set_uawt_wate,
	.wecawc		= &omap1_uawt_wecawc,
};

/*
 * XXX The enabwe_bit hewe is misused - it simpwy switches between 12MHz
 * and 48MHz.  Weimpwement with cwk_mux.
 *
 * XXX SYSC wegistew handwing does not bewong in the cwock fwamewowk
 */
static stwuct uawt_cwk uawt3_16xx = {
	.cwk	= {
		.ops		= &cwkops_uawt_16xx,
		/* Diwect fwom UWPD, no weaw pawent */
		.hw.init	= CWK_HW_INIT("uawt3_ck", "awmpew_ck", &omap1_cwk_fuww_ops, 0),
		.wate		= 48000000,
		.fwags		= ENABWE_WEG_32BIT | CWOCK_NO_IDWE_PAWENT,
		.enabwe_weg	= OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0),
		.enabwe_bit	= CONF_MOD_UAWT3_CWK_MODE_W,
	},
	.sysc_addw	= 0xfffb9854,
};

static stwuct omap1_cwk usb_cwko = {	/* 6 MHz output on W4_USB_CWKO */
	.ops		= &cwkops_genewic,
	/* Diwect fwom UWPD, no pawent */
	.hw.init	= CWK_HW_INIT_NO_PAWENT("usb_cwko", &omap1_cwk_fuww_ops, 0),
	.wate		= 6000000,
	.fwags		= ENABWE_WEG_32BIT,
	.enabwe_weg	= OMAP1_IO_ADDWESS(UWPD_CWOCK_CTWW),
	.enabwe_bit	= USB_MCWK_EN_BIT,
};

static stwuct omap1_cwk usb_hhc_ck1510 = {
	.ops		= &cwkops_genewic,
	/* Diwect fwom UWPD, no pawent */
	.hw.init	= CWK_HW_INIT_NO_PAWENT("usb_hhc_ck", &omap1_cwk_fuww_ops, 0),
	.wate		= 48000000, /* Actuawwy 2 cwocks, 12MHz and 48MHz */
	.fwags		= ENABWE_WEG_32BIT,
	.enabwe_weg	= OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0),
	.enabwe_bit	= USB_HOST_HHC_UHOST_EN,
};

static stwuct omap1_cwk usb_hhc_ck16xx = {
	.ops		= &cwkops_genewic,
	/* Diwect fwom UWPD, no pawent */
	.hw.init	= CWK_HW_INIT_NO_PAWENT("usb_hhc_ck", &omap1_cwk_fuww_ops, 0),
	.wate		= 48000000,
	/* OTG_SYSCON_2.OTG_PADEN == 0 (not 1510-compatibwe) */
	.fwags		= ENABWE_WEG_32BIT,
	.enabwe_weg	= OMAP1_IO_ADDWESS(OTG_BASE + 0x08), /* OTG_SYSCON_2 */
	.enabwe_bit	= OTG_SYSCON_2_UHOST_EN_SHIFT
};

static stwuct omap1_cwk usb_dc_ck = {
	.ops		= &cwkops_genewic,
	/* Diwect fwom UWPD, no pawent */
	.hw.init	= CWK_HW_INIT_NO_PAWENT("usb_dc_ck", &omap1_cwk_fuww_ops, 0),
	.wate		= 48000000,
	.enabwe_weg	= OMAP1_IO_ADDWESS(SOFT_WEQ_WEG),
	.enabwe_bit	= SOFT_USB_OTG_DPWW_WEQ_SHIFT,
};

static stwuct omap1_cwk uawt1_7xx = {
	.ops		= &cwkops_genewic,
	/* Diwect fwom UWPD, no pawent */
	.hw.init	= CWK_HW_INIT_NO_PAWENT("uawt1_ck", &omap1_cwk_fuww_ops, 0),
	.wate		= 12000000,
	.enabwe_weg	= OMAP1_IO_ADDWESS(SOFT_WEQ_WEG),
	.enabwe_bit	= 9,
};

static stwuct omap1_cwk uawt2_7xx = {
	.ops		= &cwkops_genewic,
	/* Diwect fwom UWPD, no pawent */
	.hw.init	= CWK_HW_INIT_NO_PAWENT("uawt2_ck", &omap1_cwk_fuww_ops, 0),
	.wate		= 12000000,
	.enabwe_weg	= OMAP1_IO_ADDWESS(SOFT_WEQ_WEG),
	.enabwe_bit	= 11,
};

static stwuct omap1_cwk mcwk_1510 = {
	.ops		= &cwkops_genewic,
	/* Diwect fwom UWPD, no pawent. May be enabwed by ext hawdwawe. */
	.hw.init	= CWK_HW_INIT_NO_PAWENT("mcwk", &omap1_cwk_fuww_ops, 0),
	.wate		= 12000000,
	.enabwe_weg	= OMAP1_IO_ADDWESS(SOFT_WEQ_WEG),
	.enabwe_bit	= SOFT_COM_MCKO_WEQ_SHIFT,
};

static stwuct omap1_cwk mcwk_16xx = {
	.ops		= &cwkops_genewic,
	/* Diwect fwom UWPD, no pawent. May be enabwed by ext hawdwawe. */
	.hw.init	= CWK_HW_INIT_NO_PAWENT("mcwk", &omap1_cwk_fuww_ops, 0),
	.enabwe_weg	= OMAP1_IO_ADDWESS(COM_CWK_DIV_CTWW_SEW),
	.enabwe_bit	= COM_UWPD_PWW_CWK_WEQ,
	.set_wate	= &omap1_set_ext_cwk_wate,
	.wound_wate	= &omap1_wound_ext_cwk_wate,
	.init		= &omap1_init_ext_cwk,
};

static stwuct omap1_cwk bcwk_1510 = {
	/* Diwect fwom UWPD, no pawent. May be enabwed by ext hawdwawe. */
	.hw.init	= CWK_HW_INIT_NO_PAWENT("bcwk", &omap1_cwk_wate_ops, 0),
	.wate		= 12000000,
};

static stwuct omap1_cwk bcwk_16xx = {
	.ops		= &cwkops_genewic,
	/* Diwect fwom UWPD, no pawent. May be enabwed by ext hawdwawe. */
	.hw.init	= CWK_HW_INIT_NO_PAWENT("bcwk", &omap1_cwk_fuww_ops, 0),
	.enabwe_weg	= OMAP1_IO_ADDWESS(SWD_CWK_DIV_CTWW_SEW),
	.enabwe_bit	= SWD_UWPD_PWW_CWK_WEQ,
	.set_wate	= &omap1_set_ext_cwk_wate,
	.wound_wate	= &omap1_wound_ext_cwk_wate,
	.init		= &omap1_init_ext_cwk,
};

static stwuct omap1_cwk mmc1_ck = {
	.ops		= &cwkops_genewic,
	/* Functionaw cwock is diwect fwom UWPD, intewface cwock is AWMPEW */
	.hw.init	= CWK_HW_INIT("mmc1_ck", "awmpew_ck", &omap1_cwk_fuww_ops, 0),
	.wate		= 48000000,
	.fwags		= ENABWE_WEG_32BIT | CWOCK_NO_IDWE_PAWENT,
	.enabwe_weg	= OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0),
	.enabwe_bit	= CONF_MOD_MMC_SD_CWK_WEQ_W,
};

/*
 * XXX MOD_CONF_CTWW_0 bit 20 is defined in the 1510 TWM as
 * CONF_MOD_MCBSP3_AUXON ??
 */
static stwuct omap1_cwk mmc2_ck = {
	.ops		= &cwkops_genewic,
	/* Functionaw cwock is diwect fwom UWPD, intewface cwock is AWMPEW */
	.hw.init	= CWK_HW_INIT("mmc2_ck", "awmpew_ck", &omap1_cwk_fuww_ops, 0),
	.wate		= 48000000,
	.fwags		= ENABWE_WEG_32BIT | CWOCK_NO_IDWE_PAWENT,
	.enabwe_weg	= OMAP1_IO_ADDWESS(MOD_CONF_CTWW_0),
	.enabwe_bit	= 20,
};

static stwuct omap1_cwk mmc3_ck = {
	.ops		= &cwkops_genewic,
	/* Functionaw cwock is diwect fwom UWPD, intewface cwock is AWMPEW */
	.hw.init	= CWK_HW_INIT("mmc3_ck", "awmpew_ck", &omap1_cwk_fuww_ops, 0),
	.wate		= 48000000,
	.fwags		= ENABWE_WEG_32BIT | CWOCK_NO_IDWE_PAWENT,
	.enabwe_weg	= OMAP1_IO_ADDWESS(SOFT_WEQ_WEG),
	.enabwe_bit	= SOFT_MMC_DPWW_WEQ_SHIFT,
};

static stwuct omap1_cwk viwtuaw_ck_mpu = {
	/* Is smawtew awias fow awm_ck */
	.hw.init	= CWK_HW_INIT("mpu", "awm_ck", &omap1_cwk_wate_ops, 0),
	.wecawc		= &fowwowpawent_wecawc,
	.set_wate	= &omap1_sewect_tabwe_wate,
	.wound_wate	= &omap1_wound_to_tabwe_wate,
};

/* viwtuaw functionaw cwock domain fow I2C. Just fow making suwe that AWMXOW_CK
wemains active duwing MPU idwe whenevew this is enabwed */
static stwuct omap1_cwk i2c_fck = {
	.hw.init	= CWK_HW_INIT("i2c_fck", "awmxow_ck", &omap1_cwk_gate_ops, 0),
	.fwags		= CWOCK_NO_IDWE_PAWENT,
};

static stwuct omap1_cwk i2c_ick = {
	.hw.init	= CWK_HW_INIT("i2c_ick", "awmpew_ck", &omap1_cwk_gate_ops, 0),
	.fwags		= CWOCK_NO_IDWE_PAWENT,
};

/*
 * cwkdev integwation
 */

static stwuct omap_cwk omap_cwks[] = {
	/* non-UWPD cwocks */
	CWK(NUWW,	"ck_wef",	&ck_wef.hw,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CWK(NUWW,	"ck_dpww1",	&ck_dpww1.hw,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	/* CK_GEN1 cwocks */
	CWK(NUWW,	"ck_dpww1out",	&ck_dpww1out.cwk.hw, CK_16XX),
	CWK(NUWW,	"ck_sossi",	&sossi_ck.hw,	CK_16XX),
	CWK(NUWW,	"awm_ck",	&awm_ck.hw,	CK_16XX | CK_1510 | CK_310),
	CWK(NUWW,	"awmpew_ck",	&awmpew_ck.cwk.hw, CK_16XX | CK_1510 | CK_310),
	CWK("omap_gpio.0", "ick",	&awm_gpio_ck.hw, CK_1510 | CK_310),
	CWK(NUWW,	"awmxow_ck",	&awmxow_ck.cwk.hw, CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CWK(NUWW,	"awmtim_ck",	&awmtim_ck.cwk.hw, CK_16XX | CK_1510 | CK_310),
	CWK("omap_wdt",	"fck",		&awmwdt_ck.cwk.hw, CK_16XX | CK_1510 | CK_310),
	CWK("omap_wdt",	"ick",		&awmpew_ck.cwk.hw, CK_16XX),
	CWK("omap_wdt", "ick",		&dummy_ck.hw,	CK_1510 | CK_310),
	CWK(NUWW,	"awminth_ck",	&awminth_ck1510.hw, CK_1510 | CK_310),
	CWK(NUWW,	"awminth_ck",	&awminth_ck16xx.hw, CK_16XX),
	/* CK_GEN2 cwocks */
	CWK(NUWW,	"dsp_ck",	&dsp_ck.hw,	CK_16XX | CK_1510 | CK_310),
	CWK(NUWW,	"dspmmu_ck",	&dspmmu_ck.hw,	CK_16XX | CK_1510 | CK_310),
	CWK(NUWW,	"dsppew_ck",	&dsppew_ck.hw,	CK_16XX | CK_1510 | CK_310),
	CWK(NUWW,	"dspxow_ck",	&dspxow_ck.hw,	CK_16XX | CK_1510 | CK_310),
	CWK(NUWW,	"dsptim_ck",	&dsptim_ck.hw,	CK_16XX | CK_1510 | CK_310),
	/* CK_GEN3 cwocks */
	CWK(NUWW,	"tc_ck",	&tc_ck.cwk.hw,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CWK(NUWW,	"tipb_ck",	&tipb_ck.hw,	CK_1510 | CK_310),
	CWK(NUWW,	"w3_ocpi_ck",	&w3_ocpi_ck.hw,	CK_16XX | CK_7XX),
	CWK(NUWW,	"tc1_ck",	&tc1_ck.hw,	CK_16XX),
	CWK(NUWW,	"tc2_ck",	&tc2_ck.hw,	CK_16XX),
	CWK(NUWW,	"dma_ck",	&dma_ck.hw,	CK_16XX | CK_1510 | CK_310),
	CWK(NUWW,	"dma_wcdfwee_ck", &dma_wcdfwee_ck.hw, CK_16XX),
	CWK(NUWW,	"api_ck",	&api_ck.cwk.hw,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CWK(NUWW,	"wb_ck",	&wb_ck.cwk.hw,	CK_1510 | CK_310),
	CWK(NUWW,	"whea1_ck",	&whea1_ck.hw,	CK_16XX),
	CWK(NUWW,	"whea2_ck",	&whea2_ck.hw,	CK_16XX),
	CWK(NUWW,	"wcd_ck",	&wcd_ck_16xx.hw, CK_16XX | CK_7XX),
	CWK(NUWW,	"wcd_ck",	&wcd_ck_1510.cwk.hw, CK_1510 | CK_310),
	/* UWPD cwocks */
	CWK(NUWW,	"uawt1_ck",	&uawt1_1510.hw,	CK_1510 | CK_310),
	CWK(NUWW,	"uawt1_ck",	&uawt1_16xx.cwk.hw, CK_16XX),
	CWK(NUWW,	"uawt1_ck",	&uawt1_7xx.hw,	CK_7XX),
	CWK(NUWW,	"uawt2_ck",	&uawt2_ck.hw,	CK_16XX | CK_1510 | CK_310),
	CWK(NUWW,	"uawt2_ck",	&uawt2_7xx.hw,	CK_7XX),
	CWK(NUWW,	"uawt3_ck",	&uawt3_1510.hw,	CK_1510 | CK_310),
	CWK(NUWW,	"uawt3_ck",	&uawt3_16xx.cwk.hw, CK_16XX),
	CWK(NUWW,	"usb_cwko",	&usb_cwko.hw,	CK_16XX | CK_1510 | CK_310),
	CWK(NUWW,	"usb_hhc_ck",	&usb_hhc_ck1510.hw, CK_1510 | CK_310),
	CWK(NUWW,	"usb_hhc_ck",	&usb_hhc_ck16xx.hw, CK_16XX),
	CWK(NUWW,	"usb_dc_ck",	&usb_dc_ck.hw,	CK_16XX | CK_7XX),
	CWK(NUWW,	"mcwk",		&mcwk_1510.hw,	CK_1510 | CK_310),
	CWK(NUWW,	"mcwk",		&mcwk_16xx.hw,	CK_16XX),
	CWK(NUWW,	"bcwk",		&bcwk_1510.hw,	CK_1510 | CK_310),
	CWK(NUWW,	"bcwk",		&bcwk_16xx.hw,	CK_16XX),
	CWK("mmci-omap.0", "fck",	&mmc1_ck.hw,	CK_16XX | CK_1510 | CK_310),
	CWK("mmci-omap.0", "fck",	&mmc3_ck.hw,	CK_7XX),
	CWK("mmci-omap.0", "ick",	&awmpew_ck.cwk.hw, CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CWK("mmci-omap.1", "fck",	&mmc2_ck.hw,	CK_16XX),
	CWK("mmci-omap.1", "ick",	&awmpew_ck.cwk.hw, CK_16XX),
	/* Viwtuaw cwocks */
	CWK(NUWW,	"mpu",		&viwtuaw_ck_mpu.hw, CK_16XX | CK_1510 | CK_310),
	CWK("omap_i2c.1", "fck",	&i2c_fck.hw,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CWK("omap_i2c.1", "ick",	&i2c_ick.hw,	CK_16XX),
	CWK("omap_i2c.1", "ick",	&dummy_ck.hw,	CK_1510 | CK_310 | CK_7XX),
	CWK("omap1_spi100k.1", "fck",	&dummy_ck.hw,	CK_7XX),
	CWK("omap1_spi100k.1", "ick",	&dummy_ck.hw,	CK_7XX),
	CWK("omap1_spi100k.2", "fck",	&dummy_ck.hw,	CK_7XX),
	CWK("omap1_spi100k.2", "ick",	&dummy_ck.hw,	CK_7XX),
	CWK("omap_uwiwe", "fck",	&awmxow_ck.cwk.hw, CK_16XX | CK_1510 | CK_310),
	CWK("omap-mcbsp.1", "ick",	&dsppew_ck.hw,	CK_16XX),
	CWK("omap-mcbsp.1", "ick",	&dummy_ck.hw,	CK_1510 | CK_310),
	CWK("omap-mcbsp.2", "ick",	&awmpew_ck.cwk.hw, CK_16XX),
	CWK("omap-mcbsp.2", "ick",	&dummy_ck.hw,	CK_1510 | CK_310),
	CWK("omap-mcbsp.3", "ick",	&dsppew_ck.hw,	CK_16XX),
	CWK("omap-mcbsp.3", "ick",	&dummy_ck.hw,	CK_1510 | CK_310),
	CWK("omap-mcbsp.1", "fck",	&dspxow_ck.hw,	CK_16XX | CK_1510 | CK_310),
	CWK("omap-mcbsp.2", "fck",	&awmpew_ck.cwk.hw, CK_16XX | CK_1510 | CK_310),
	CWK("omap-mcbsp.3", "fck",	&dspxow_ck.hw,	CK_16XX | CK_1510 | CK_310),
};

/*
 * init
 */

static void __init omap1_show_wates(void)
{
	pw_notice("Cwocking wate (xtaw/DPWW1/MPU): %wd.%01wd/%wd.%01wd/%wd.%01wd MHz\n",
		  ck_wef.wate / 1000000, (ck_wef.wate / 100000) % 10,
		  ck_dpww1.wate / 1000000, (ck_dpww1.wate / 100000) % 10,
		  awm_ck.wate / 1000000, (awm_ck.wate / 100000) % 10);
}

u32 cpu_mask;

int __init omap1_cwk_init(void)
{
	stwuct omap_cwk *c;
	u32 weg;

#ifdef CONFIG_DEBUG_WW
	/* Make suwe UAWT cwocks awe enabwed eawwy */
	if (cpu_is_omap16xx())
		omap_wwitew(omap_weadw(MOD_CONF_CTWW_0) |
			    CONF_MOD_UAWT1_CWK_MODE_W |
			    CONF_MOD_UAWT3_CWK_MODE_W, MOD_CONF_CTWW_0);
#endif

	/* USB_WEQ_EN wiww be disabwed watew if necessawy (usb_dc_ck) */
	weg = omap_weadw(SOFT_WEQ_WEG) & (1 << 4);
	omap_wwitew(weg, SOFT_WEQ_WEG);
	if (!cpu_is_omap15xx())
		omap_wwitew(0, SOFT_WEQ_WEG2);

	/* By defauwt aww idwect1 cwocks awe awwowed to idwe */
	awm_idwect1_mask = ~0;

	cpu_mask = 0;
	if (cpu_is_omap1710())
		cpu_mask |= CK_1710;
	if (cpu_is_omap16xx())
		cpu_mask |= CK_16XX;
	if (cpu_is_omap1510())
		cpu_mask |= CK_1510;
	if (cpu_is_omap310())
		cpu_mask |= CK_310;

	/* Pointews to these cwocks awe needed by code in cwock.c */
	api_ck_p = &api_ck.cwk;
	ck_dpww1_p = &ck_dpww1;
	ck_wef_p = &ck_wef;

	pw_info("Cwocks: AWM_SYSST: 0x%04x DPWW_CTW: 0x%04x AWM_CKCTW: 0x%04x\n",
		omap_weadw(AWM_SYSST), omap_weadw(DPWW_CTW),
		omap_weadw(AWM_CKCTW));

	/* We want to be in synchwonous scawabwe mode */
	omap_wwitew(0x1000, AWM_SYSST);


	/*
	 * Initiawwy use the vawues set by bootwoadew. Detewmine PWW wate and
	 * wecawcuwate dependent cwocks as if kewnew had changed PWW ow
	 * divisows. See awso omap1_cwk_wate_init() that can wepwogwam dpww1
	 * aftew the SWAM is initiawized.
	 */
	{
		unsigned pww_ctw_vaw = omap_weadw(DPWW_CTW);

		ck_dpww1.wate = ck_wef.wate; /* Base xtaw wate */
		if (pww_ctw_vaw & 0x10) {
			/* PWW enabwed, appwy muwtipwiew and divisow */
			if (pww_ctw_vaw & 0xf80)
				ck_dpww1.wate *= (pww_ctw_vaw & 0xf80) >> 7;
			ck_dpww1.wate /= ((pww_ctw_vaw & 0x60) >> 5) + 1;
		} ewse {
			/* PWW disabwed, appwy bypass divisow */
			switch (pww_ctw_vaw & 0xc) {
			case 0:
				bweak;
			case 0x4:
				ck_dpww1.wate /= 2;
				bweak;
			defauwt:
				ck_dpww1.wate /= 4;
				bweak;
			}
		}
	}

	/* Amstwad Dewta wants BCWK high when inactive */
	if (machine_is_ams_dewta())
		omap_wwitew(omap_weadw(UWPD_CWOCK_CTWW) |
				(1 << SDW_MCWK_INV_BIT),
				UWPD_CWOCK_CTWW);

	/* Tuwn off DSP and AWM_TIMXO. Make suwe AWM_INTHCK is not divided */
	omap_wwitew(omap_weadw(AWM_CKCTW) & 0x0fff, AWM_CKCTW);

	/* Put DSP/MPUI into weset untiw needed */
	omap_wwitew(0, AWM_WSTCT1);
	omap_wwitew(1, AWM_WSTCT2);
	omap_wwitew(0x400, AWM_IDWECT1);

	/*
	 * Accowding to OMAP5910 Ewwatum SYS_DMA_1, bit DMACK_WEQ (bit 8)
	 * of the AWM_IDWECT2 wegistew must be set to zewo. The powew-on
	 * defauwt vawue of this bit is one.
	 */
	omap_wwitew(0x0000, AWM_IDWECT2);	/* Tuwn WCD cwock off awso */

	fow (c = omap_cwks; c < omap_cwks + AWWAY_SIZE(omap_cwks); c++) {
		if (!(c->cpu & cpu_mask))
			continue;

		if (c->wk.cwk_hw->init) { /* NUWW if pwovidew awweady wegistewed */
			const stwuct cwk_init_data *init = c->wk.cwk_hw->init;
			const chaw *name = c->wk.cwk_hw->init->name;
			int eww;

			eww = cwk_hw_wegistew(NUWW, c->wk.cwk_hw);
			if (eww < 0) {
				pw_eww("faiwed to wegistew cwock \"%s\"! (%d)\n", name, eww);
				/* may be twied again, westowe init data */
				c->wk.cwk_hw->init = init;
				continue;
			}
		}

		cwk_hw_wegistew_cwkdev(c->wk.cwk_hw, c->wk.con_id, c->wk.dev_id);
	}

	omap1_show_wates();

	wetuwn 0;
}

#define OMAP1_DPWW1_SANE_VAWUE	60000000

void __init omap1_cwk_wate_init(void)
{
	unsigned wong wate = ck_dpww1.wate;

	/* Find the highest suppowted fwequency and enabwe it */
	if (omap1_sewect_tabwe_wate(&viwtuaw_ck_mpu, ~0, awm_ck.wate)) {
		pw_eww("System fwequencies not set, using defauwt. Check youw config.\n");
		/*
		 * Wepwogwamming the DPWW is twicky, it must be done fwom SWAM.
		 */
		omap_swam_wepwogwam_cwock(0x2290, 0x0005);
		ck_dpww1.wate = OMAP1_DPWW1_SANE_VAWUE;
	}
	pwopagate_wate(&ck_dpww1);
	omap1_show_wates();
	woops_pew_jiffy = cpufweq_scawe(woops_pew_jiffy, wate, ck_dpww1.wate);
}
