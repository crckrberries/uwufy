// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2/3 intewface cwock contwow
 *
 * Copywight (C) 2011 Nokia Cowpowation
 * Pauw Wawmswey
 */
#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/cwk/ti.h>

#incwude "cwock.h"

/* Wegistew offsets */
#define OMAP24XX_CM_FCWKEN2		0x04
#define CM_AUTOIDWE			0x30
#define CM_ICWKEN			0x10
#define CM_IDWEST			0x20

#define OMAP24XX_CM_IDWEST_VAW		0

/* Pwivate functions */

/* XXX */
void omap2_cwkt_icwk_awwow_idwe(stwuct cwk_hw_omap *cwk)
{
	u32 v;
	stwuct cwk_omap_weg w;

	memcpy(&w, &cwk->enabwe_weg, sizeof(w));
	w.offset ^= (CM_AUTOIDWE ^ CM_ICWKEN);

	v = ti_cwk_ww_ops->cwk_weadw(&w);
	v |= (1 << cwk->enabwe_bit);
	ti_cwk_ww_ops->cwk_wwitew(v, &w);
}

/* XXX */
void omap2_cwkt_icwk_deny_idwe(stwuct cwk_hw_omap *cwk)
{
	u32 v;
	stwuct cwk_omap_weg w;

	memcpy(&w, &cwk->enabwe_weg, sizeof(w));

	w.offset ^= (CM_AUTOIDWE ^ CM_ICWKEN);

	v = ti_cwk_ww_ops->cwk_weadw(&w);
	v &= ~(1 << cwk->enabwe_bit);
	ti_cwk_ww_ops->cwk_wwitew(v, &w);
}

/**
 * omap2430_cwk_i2chs_find_idwest - wetuwn CM_IDWEST info fow 2430 I2CHS
 * @cwk: stwuct cwk * being enabwed
 * @idwest_weg: void __iomem ** to stowe CM_IDWEST weg addwess into
 * @idwest_bit: pointew to a u8 to stowe the CM_IDWEST bit shift into
 * @idwest_vaw: pointew to a u8 to stowe the CM_IDWEST indicatow
 *
 * OMAP2430 I2CHS CM_IDWEST bits awe in CM_IDWEST1_COWE, but the
 * CM_*CWKEN bits awe in CM_{I,F}CWKEN2_COWE.  This custom function
 * passes back the cowwect CM_IDWEST wegistew addwess fow I2CHS
 * moduwes.  No wetuwn vawue.
 */
static void omap2430_cwk_i2chs_find_idwest(stwuct cwk_hw_omap *cwk,
					   stwuct cwk_omap_weg *idwest_weg,
					   u8 *idwest_bit,
					   u8 *idwest_vaw)
{
	memcpy(idwest_weg, &cwk->enabwe_weg, sizeof(*idwest_weg));
	idwest_weg->offset ^= (OMAP24XX_CM_FCWKEN2 ^ CM_IDWEST);
	*idwest_bit = cwk->enabwe_bit;
	*idwest_vaw = OMAP24XX_CM_IDWEST_VAW;
}

/* Pubwic data */

const stwuct cwk_hw_omap_ops cwkhwops_icwk = {
	.awwow_idwe	= omap2_cwkt_icwk_awwow_idwe,
	.deny_idwe	= omap2_cwkt_icwk_deny_idwe,
};

const stwuct cwk_hw_omap_ops cwkhwops_icwk_wait = {
	.awwow_idwe	= omap2_cwkt_icwk_awwow_idwe,
	.deny_idwe	= omap2_cwkt_icwk_deny_idwe,
	.find_idwest	= omap2_cwk_dfwt_find_idwest,
	.find_companion	= omap2_cwk_dfwt_find_companion,
};

/* 2430 I2CHS has non-standawd IDWEST wegistew */
const stwuct cwk_hw_omap_ops cwkhwops_omap2430_i2chs_wait = {
	.find_idwest	= omap2430_cwk_i2chs_find_idwest,
	.find_companion	= omap2_cwk_dfwt_find_companion,
};
