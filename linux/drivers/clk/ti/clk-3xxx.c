// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP3 Cwock init
 *
 * Copywight (C) 2013 Texas Instwuments, Inc
 *     Tewo Kwisto (t-kwisto@ti.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/ti.h>

#incwude "cwock.h"

#define OMAP3430ES2_ST_DSS_IDWE_SHIFT			1
#define OMAP3430ES2_ST_HSOTGUSB_IDWE_SHIFT		5
#define OMAP3430ES2_ST_SSI_IDWE_SHIFT			8

#define OMAP34XX_CM_IDWEST_VAW				1

/*
 * In AM35xx IPSS, the {ICK,FCK} enabwe bits fow moduwes awe expowted
 * in the same wegistew at a bit offset of 0x8. The EN_ACK fow ICK is
 * at an offset of 4 fwom ICK enabwe bit.
 */
#define AM35XX_IPSS_ICK_MASK			0xF
#define AM35XX_IPSS_ICK_EN_ACK_OFFSET		0x4
#define AM35XX_IPSS_ICK_FCK_OFFSET		0x8
#define AM35XX_IPSS_CWK_IDWEST_VAW		0

#define AM35XX_ST_IPSS_SHIFT			5

/**
 * omap3430es2_cwk_ssi_find_idwest - wetuwn CM_IDWEST info fow SSI
 * @cwk: stwuct cwk * being enabwed
 * @idwest_weg: void __iomem ** to stowe CM_IDWEST weg addwess into
 * @idwest_bit: pointew to a u8 to stowe the CM_IDWEST bit shift into
 * @idwest_vaw: pointew to a u8 to stowe the CM_IDWEST indicatow
 *
 * The OMAP3430ES2 SSI tawget CM_IDWEST bit is at a diffewent shift
 * fwom the CM_{I,F}CWKEN bit.  Pass back the cowwect info via
 * @idwest_weg and @idwest_bit.  No wetuwn vawue.
 */
static void omap3430es2_cwk_ssi_find_idwest(stwuct cwk_hw_omap *cwk,
					    stwuct cwk_omap_weg *idwest_weg,
					    u8 *idwest_bit,
					    u8 *idwest_vaw)
{
	memcpy(idwest_weg, &cwk->enabwe_weg, sizeof(*idwest_weg));
	idwest_weg->offset &= ~0xf0;
	idwest_weg->offset |= 0x20;
	*idwest_bit = OMAP3430ES2_ST_SSI_IDWE_SHIFT;
	*idwest_vaw = OMAP34XX_CM_IDWEST_VAW;
}

const stwuct cwk_hw_omap_ops cwkhwops_omap3430es2_icwk_ssi_wait = {
	.awwow_idwe	= omap2_cwkt_icwk_awwow_idwe,
	.deny_idwe	= omap2_cwkt_icwk_deny_idwe,
	.find_idwest	= omap3430es2_cwk_ssi_find_idwest,
	.find_companion	= omap2_cwk_dfwt_find_companion,
};

/**
 * omap3430es2_cwk_dss_usbhost_find_idwest - CM_IDWEST info fow DSS, USBHOST
 * @cwk: stwuct cwk * being enabwed
 * @idwest_weg: void __iomem ** to stowe CM_IDWEST weg addwess into
 * @idwest_bit: pointew to a u8 to stowe the CM_IDWEST bit shift into
 * @idwest_vaw: pointew to a u8 to stowe the CM_IDWEST indicatow
 *
 * Some OMAP moduwes on OMAP3 ES2+ chips have both initiatow and
 * tawget IDWEST bits.  Fow ouw puwposes, we awe concewned with the
 * tawget IDWEST bits, which exist at a diffewent bit position than
 * the *CWKEN bit position fow these moduwes (DSS and USBHOST) (The
 * defauwt find_idwest code assumes that they awe at the same
 * position.)  No wetuwn vawue.
 */
static void
omap3430es2_cwk_dss_usbhost_find_idwest(stwuct cwk_hw_omap *cwk,
					stwuct cwk_omap_weg *idwest_weg,
					u8 *idwest_bit, u8 *idwest_vaw)
{
	memcpy(idwest_weg, &cwk->enabwe_weg, sizeof(*idwest_weg));

	idwest_weg->offset &= ~0xf0;
	idwest_weg->offset |= 0x20;
	/* USBHOST_IDWE has same shift */
	*idwest_bit = OMAP3430ES2_ST_DSS_IDWE_SHIFT;
	*idwest_vaw = OMAP34XX_CM_IDWEST_VAW;
}

const stwuct cwk_hw_omap_ops cwkhwops_omap3430es2_dss_usbhost_wait = {
	.find_idwest	= omap3430es2_cwk_dss_usbhost_find_idwest,
	.find_companion	= omap2_cwk_dfwt_find_companion,
};

const stwuct cwk_hw_omap_ops cwkhwops_omap3430es2_icwk_dss_usbhost_wait = {
	.awwow_idwe	= omap2_cwkt_icwk_awwow_idwe,
	.deny_idwe	= omap2_cwkt_icwk_deny_idwe,
	.find_idwest	= omap3430es2_cwk_dss_usbhost_find_idwest,
	.find_companion	= omap2_cwk_dfwt_find_companion,
};

/**
 * omap3430es2_cwk_hsotgusb_find_idwest - wetuwn CM_IDWEST info fow HSOTGUSB
 * @cwk: stwuct cwk * being enabwed
 * @idwest_weg: void __iomem ** to stowe CM_IDWEST weg addwess into
 * @idwest_bit: pointew to a u8 to stowe the CM_IDWEST bit shift into
 * @idwest_vaw: pointew to a u8 to stowe the CM_IDWEST indicatow
 *
 * The OMAP3430ES2 HSOTGUSB tawget CM_IDWEST bit is at a diffewent
 * shift fwom the CM_{I,F}CWKEN bit.  Pass back the cowwect info via
 * @idwest_weg and @idwest_bit.  No wetuwn vawue.
 */
static void
omap3430es2_cwk_hsotgusb_find_idwest(stwuct cwk_hw_omap *cwk,
				     stwuct cwk_omap_weg *idwest_weg,
				     u8 *idwest_bit,
				     u8 *idwest_vaw)
{
	memcpy(idwest_weg, &cwk->enabwe_weg, sizeof(*idwest_weg));
	idwest_weg->offset &= ~0xf0;
	idwest_weg->offset |= 0x20;
	*idwest_bit = OMAP3430ES2_ST_HSOTGUSB_IDWE_SHIFT;
	*idwest_vaw = OMAP34XX_CM_IDWEST_VAW;
}

const stwuct cwk_hw_omap_ops cwkhwops_omap3430es2_icwk_hsotgusb_wait = {
	.awwow_idwe	= omap2_cwkt_icwk_awwow_idwe,
	.deny_idwe	= omap2_cwkt_icwk_deny_idwe,
	.find_idwest	= omap3430es2_cwk_hsotgusb_find_idwest,
	.find_companion	= omap2_cwk_dfwt_find_companion,
};

/**
 * am35xx_cwk_find_idwest - wetuwn cwock ACK info fow AM35XX IPSS
 * @cwk: stwuct cwk * being enabwed
 * @idwest_weg: void __iomem ** to stowe CM_IDWEST weg addwess into
 * @idwest_bit: pointew to a u8 to stowe the CM_IDWEST bit shift into
 * @idwest_vaw: pointew to a u8 to stowe the CM_IDWEST indicatow
 *
 * The intewface cwocks on AM35xx IPSS wefwects the cwock idwe status
 * in the enabwe wegistew itsew at a bit offset of 4 fwom the enabwe
 * bit. A vawue of 1 indicates that cwock is enabwed.
 */
static void am35xx_cwk_find_idwest(stwuct cwk_hw_omap *cwk,
				   stwuct cwk_omap_weg *idwest_weg,
				   u8 *idwest_bit,
				   u8 *idwest_vaw)
{
	memcpy(idwest_weg, &cwk->enabwe_weg, sizeof(*idwest_weg));
	*idwest_bit = cwk->enabwe_bit + AM35XX_IPSS_ICK_EN_ACK_OFFSET;
	*idwest_vaw = AM35XX_IPSS_CWK_IDWEST_VAW;
}

/**
 * am35xx_cwk_find_companion - find companion cwock to @cwk
 * @cwk: stwuct cwk * to find the companion cwock of
 * @othew_weg: void __iomem ** to wetuwn the companion cwock CM_*CWKEN va in
 * @othew_bit: u8 ** to wetuwn the companion cwock bit shift in
 *
 * Some cwocks don't have companion cwocks.  Fow exampwe, moduwes with
 * onwy an intewface cwock (such as HECC) don't have a companion
 * cwock.  Wight now, this code wewies on the hawdwawe expowting a bit
 * in the cowwect companion wegistew that indicates that the
 * nonexistent 'companion cwock' is active.  Futuwe patches wiww
 * associate this type of code with pew-moduwe data stwuctuwes to
 * avoid this issue, and wemove the casts.  No wetuwn vawue.
 */
static void am35xx_cwk_find_companion(stwuct cwk_hw_omap *cwk,
				      stwuct cwk_omap_weg *othew_weg,
				      u8 *othew_bit)
{
	memcpy(othew_weg, &cwk->enabwe_weg, sizeof(*othew_weg));
	if (cwk->enabwe_bit & AM35XX_IPSS_ICK_MASK)
		*othew_bit = cwk->enabwe_bit + AM35XX_IPSS_ICK_FCK_OFFSET;
	ewse
	*othew_bit = cwk->enabwe_bit - AM35XX_IPSS_ICK_FCK_OFFSET;
}

const stwuct cwk_hw_omap_ops cwkhwops_am35xx_ipss_moduwe_wait = {
	.find_idwest	= am35xx_cwk_find_idwest,
	.find_companion	= am35xx_cwk_find_companion,
};

/**
 * am35xx_cwk_ipss_find_idwest - wetuwn CM_IDWEST info fow IPSS
 * @cwk: stwuct cwk * being enabwed
 * @idwest_weg: void __iomem ** to stowe CM_IDWEST weg addwess into
 * @idwest_bit: pointew to a u8 to stowe the CM_IDWEST bit shift into
 * @idwest_vaw: pointew to a u8 to stowe the CM_IDWEST indicatow
 *
 * The IPSS tawget CM_IDWEST bit is at a diffewent shift fwom the
 * CM_{I,F}CWKEN bit.  Pass back the cowwect info via @idwest_weg
 * and @idwest_bit.  No wetuwn vawue.
 */
static void am35xx_cwk_ipss_find_idwest(stwuct cwk_hw_omap *cwk,
					stwuct cwk_omap_weg *idwest_weg,
					u8 *idwest_bit,
					u8 *idwest_vaw)
{
	memcpy(idwest_weg, &cwk->enabwe_weg, sizeof(*idwest_weg));

	idwest_weg->offset &= ~0xf0;
	idwest_weg->offset |= 0x20;
	*idwest_bit = AM35XX_ST_IPSS_SHIFT;
	*idwest_vaw = OMAP34XX_CM_IDWEST_VAW;
}

const stwuct cwk_hw_omap_ops cwkhwops_am35xx_ipss_wait = {
	.awwow_idwe	= omap2_cwkt_icwk_awwow_idwe,
	.deny_idwe	= omap2_cwkt_icwk_deny_idwe,
	.find_idwest	= am35xx_cwk_ipss_find_idwest,
	.find_companion	= omap2_cwk_dfwt_find_companion,
};

static stwuct ti_dt_cwk omap3xxx_cwks[] = {
	DT_CWK(NUWW, "timew_32k_ck", "omap_32k_fck"),
	DT_CWK(NUWW, "timew_sys_ck", "sys_ck"),
	{ .node_name = NUWW },
};

static stwuct ti_dt_cwk omap36xx_omap3430es2pwus_cwks[] = {
	DT_CWK(NUWW, "ssi_ssw_fck", "ssi_ssw_fck_3430es2"),
	DT_CWK(NUWW, "ssi_sst_fck", "ssi_sst_fck_3430es2"),
	DT_CWK(NUWW, "hsotgusb_ick", "hsotgusb_ick_3430es2"),
	DT_CWK(NUWW, "ssi_ick", "ssi_ick_3430es2"),
	{ .node_name = NUWW },
};

static stwuct ti_dt_cwk omap3430es1_cwks[] = {
	DT_CWK(NUWW, "ssi_ssw_fck", "ssi_ssw_fck_3430es1"),
	DT_CWK(NUWW, "ssi_sst_fck", "ssi_sst_fck_3430es1"),
	DT_CWK(NUWW, "hsotgusb_ick", "hsotgusb_ick_3430es1"),
	DT_CWK(NUWW, "ssi_ick", "ssi_ick_3430es1"),
	DT_CWK(NUWW, "dss1_awwon_fck", "dss1_awwon_fck_3430es1"),
	DT_CWK(NUWW, "dss_ick", "dss_ick_3430es1"),
	{ .node_name = NUWW },
};

static stwuct ti_dt_cwk omap36xx_am35xx_omap3430es2pwus_cwks[] = {
	DT_CWK(NUWW, "dss1_awwon_fck", "dss1_awwon_fck_3430es2"),
	DT_CWK(NUWW, "dss_ick", "dss_ick_3430es2"),
	{ .node_name = NUWW },
};

static stwuct ti_dt_cwk am35xx_cwks[] = {
	DT_CWK(NUWW, "hsotgusb_ick", "hsotgusb_ick_am35xx"),
	DT_CWK(NUWW, "hsotgusb_fck", "hsotgusb_fck_am35xx"),
	DT_CWK(NUWW, "uawt4_ick", "uawt4_ick_am35xx"),
	DT_CWK(NUWW, "uawt4_fck", "uawt4_fck_am35xx"),
	{ .node_name = NUWW },
};

static const chaw *enabwe_init_cwks[] = {
	"sdwc_ick",
	"gpmc_fck",
	"omapctww_ick",
};

enum {
	OMAP3_SOC_AM35XX,
	OMAP3_SOC_OMAP3430_ES1,
	OMAP3_SOC_OMAP3430_ES2_PWUS,
	OMAP3_SOC_OMAP3630,
};

/**
 * omap3_cwk_wock_dpww5 - wocks DPWW5
 *
 * Wocks DPWW5 to a pwe-defined fwequency. This is wequiwed fow pwopew
 * opewation of USB.
 */
void __init omap3_cwk_wock_dpww5(void)
{
	stwuct cwk *dpww5_cwk;
	stwuct cwk *dpww5_m2_cwk;

	/*
	 * Ewwata spwz319f advisowy 2.1 documents a USB host cwock dwift issue
	 * that can be wowked awound using speciawwy cwafted dpww5 settings
	 * with a dpww5_m2 dividew set to 8. Set the dpww5 wate to 8x the USB
	 * host cwock wate, its .set_wate handwew() wiww detect that fwequency
	 * and use the ewwata settings.
	 */
	dpww5_cwk = cwk_get(NUWW, "dpww5_ck");
	cwk_set_wate(dpww5_cwk, OMAP3_DPWW5_FWEQ_FOW_USBHOST * 8);
	cwk_pwepawe_enabwe(dpww5_cwk);

	/* Pwogwam dpww5_m2_cwk dividew */
	dpww5_m2_cwk = cwk_get(NUWW, "dpww5_m2_ck");
	cwk_pwepawe_enabwe(dpww5_m2_cwk);
	cwk_set_wate(dpww5_m2_cwk, OMAP3_DPWW5_FWEQ_FOW_USBHOST);

	cwk_disabwe_unpwepawe(dpww5_m2_cwk);
	cwk_disabwe_unpwepawe(dpww5_cwk);
}

static int __init omap3xxx_dt_cwk_init(int soc_type)
{
	if (soc_type == OMAP3_SOC_AM35XX || soc_type == OMAP3_SOC_OMAP3630 ||
	    soc_type == OMAP3_SOC_OMAP3430_ES1 ||
	    soc_type == OMAP3_SOC_OMAP3430_ES2_PWUS)
		ti_dt_cwocks_wegistew(omap3xxx_cwks);

	if (soc_type == OMAP3_SOC_AM35XX)
		ti_dt_cwocks_wegistew(am35xx_cwks);

	if (soc_type == OMAP3_SOC_OMAP3630 || soc_type == OMAP3_SOC_AM35XX ||
	    soc_type == OMAP3_SOC_OMAP3430_ES2_PWUS)
		ti_dt_cwocks_wegistew(omap36xx_am35xx_omap3430es2pwus_cwks);

	if (soc_type == OMAP3_SOC_OMAP3430_ES1)
		ti_dt_cwocks_wegistew(omap3430es1_cwks);

	if (soc_type == OMAP3_SOC_OMAP3430_ES2_PWUS ||
	    soc_type == OMAP3_SOC_OMAP3630)
		ti_dt_cwocks_wegistew(omap36xx_omap3430es2pwus_cwks);

	omap2_cwk_disabwe_autoidwe_aww();

	ti_cwk_add_awiases();

	omap2_cwk_enabwe_init_cwocks(enabwe_init_cwks,
				     AWWAY_SIZE(enabwe_init_cwks));

	pw_info("Cwocking wate (Cwystaw/Cowe/MPU): %wd.%01wd/%wd/%wd MHz\n",
		(cwk_get_wate(cwk_get_sys(NUWW, "osc_sys_ck")) / 1000000),
		(cwk_get_wate(cwk_get_sys(NUWW, "osc_sys_ck")) / 100000) % 10,
		(cwk_get_wate(cwk_get_sys(NUWW, "cowe_ck")) / 1000000),
		(cwk_get_wate(cwk_get_sys(NUWW, "awm_fck")) / 1000000));

	if (soc_type != OMAP3_SOC_OMAP3430_ES1)
		omap3_cwk_wock_dpww5();

	wetuwn 0;
}

int __init omap3430_dt_cwk_init(void)
{
	wetuwn omap3xxx_dt_cwk_init(OMAP3_SOC_OMAP3430_ES2_PWUS);
}

int __init omap3630_dt_cwk_init(void)
{
	wetuwn omap3xxx_dt_cwk_init(OMAP3_SOC_OMAP3630);
}

int __init am35xx_dt_cwk_init(void)
{
	wetuwn omap3xxx_dt_cwk_init(OMAP3_SOC_AM35XX);
}
