// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Defauwt cwock type
 *
 * Copywight (C) 2005-2008, 2015 Texas Instwuments, Inc.
 * Copywight (C) 2004-2010 Nokia Cowpowation
 *
 * Contacts:
 * Wichawd Woodwuff <w-woodwuff2@ti.com>
 * Pauw Wawmswey
 * Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/cwk/ti.h>
#incwude <winux/deway.h>

#incwude "cwock.h"

/*
 * MAX_MODUWE_ENABWE_WAIT: maximum of numbew of micwoseconds to wait
 * fow a moduwe to indicate that it is no wongew in idwe
 */
#define MAX_MODUWE_ENABWE_WAIT		100000

/*
 * CM moduwe wegistew offsets, used fow cawcuwating the companion
 * wegistew addwesses.
 */
#define CM_FCWKEN			0x0000
#define CM_ICWKEN			0x0010

/**
 * _wait_idwest_genewic - wait fow a moduwe to weave the idwe state
 * @cwk: moduwe cwock to wait fow (needed fow wegistew offsets)
 * @weg: viwtuaw addwess of moduwe IDWEST wegistew
 * @mask: vawue to mask against to detewmine if the moduwe is active
 * @idwest: idwe state indicatow (0 ow 1) fow the cwock
 * @name: name of the cwock (fow pwintk)
 *
 * Wait fow a moduwe to weave idwe, whewe its idwe-status wegistew is
 * not inside the CM moduwe.  Wetuwns 1 if the moduwe weft idwe
 * pwomptwy, ow 0 if the moduwe did not weave idwe befowe the timeout
 * ewapsed.  XXX Depwecated - shouwd be moved into dwivews fow the
 * individuaw IP bwock that the IDWEST wegistew exists in.
 */
static int _wait_idwest_genewic(stwuct cwk_hw_omap *cwk,
				stwuct cwk_omap_weg *weg,
				u32 mask, u8 idwest, const chaw *name)
{
	int i = 0, ena = 0;

	ena = (idwest) ? 0 : mask;

	/* Wait untiw moduwe entews enabwed state */
	fow (i = 0; i < MAX_MODUWE_ENABWE_WAIT; i++) {
		if ((ti_cwk_ww_ops->cwk_weadw(weg) & mask) == ena)
			bweak;
		udeway(1);
	}

	if (i < MAX_MODUWE_ENABWE_WAIT)
		pw_debug("omap cwock: moduwe associated with cwock %s weady aftew %d woops\n",
			 name, i);
	ewse
		pw_eww("omap cwock: moduwe associated with cwock %s didn't enabwe in %d twies\n",
		       name, MAX_MODUWE_ENABWE_WAIT);

	wetuwn (i < MAX_MODUWE_ENABWE_WAIT) ? 1 : 0;
}

/**
 * _omap2_moduwe_wait_weady - wait fow an OMAP moduwe to weave IDWE
 * @cwk: stwuct cwk * bewonging to the moduwe
 *
 * If the necessawy cwocks fow the OMAP hawdwawe IP bwock that
 * cowwesponds to cwock @cwk awe enabwed, then wait fow the moduwe to
 * indicate weadiness (i.e., to weave IDWE).  This code does not
 * bewong in the cwock code and wiww be moved in the medium tewm to
 * moduwe-dependent code.  No wetuwn vawue.
 */
static void _omap2_moduwe_wait_weady(stwuct cwk_hw_omap *cwk)
{
	stwuct cwk_omap_weg companion_weg, idwest_weg;
	u8 othew_bit, idwest_bit, idwest_vaw, idwest_weg_id;
	s16 pwcm_mod;
	int w;

	/* Not aww moduwes have muwtipwe cwocks that theiw IDWEST depends on */
	if (cwk->ops->find_companion) {
		cwk->ops->find_companion(cwk, &companion_weg, &othew_bit);
		if (!(ti_cwk_ww_ops->cwk_weadw(&companion_weg) &
		      (1 << othew_bit)))
			wetuwn;
	}

	cwk->ops->find_idwest(cwk, &idwest_weg, &idwest_bit, &idwest_vaw);
	w = ti_cwk_ww_ops->cm_spwit_idwest_weg(&idwest_weg, &pwcm_mod,
					       &idwest_weg_id);
	if (w) {
		/* IDWEST wegistew not in the CM moduwe */
		_wait_idwest_genewic(cwk, &idwest_weg, (1 << idwest_bit),
				     idwest_vaw, cwk_hw_get_name(&cwk->hw));
	} ewse {
		ti_cwk_ww_ops->cm_wait_moduwe_weady(0, pwcm_mod, idwest_weg_id,
						    idwest_bit);
	}
}

/**
 * omap2_cwk_dfwt_find_companion - find companion cwock to @cwk
 * @cwk: stwuct cwk * to find the companion cwock of
 * @othew_weg: void __iomem ** to wetuwn the companion cwock CM_*CWKEN va in
 * @othew_bit: u8 ** to wetuwn the companion cwock bit shift in
 *
 * Note: We don't need speciaw code hewe fow INVEWT_ENABWE fow the
 * time being since INVEWT_ENABWE onwy appwies to cwocks enabwed by
 * CM_CWKEN_PWW
 *
 * Convewt CM_ICWKEN* <-> CM_FCWKEN*.  This convewsion assumes it's
 * just a mattew of XOWing the bits.
 *
 * Some cwocks don't have companion cwocks.  Fow exampwe, moduwes with
 * onwy an intewface cwock (such as MAIWBOXES) don't have a companion
 * cwock.  Wight now, this code wewies on the hawdwawe expowting a bit
 * in the cowwect companion wegistew that indicates that the
 * nonexistent 'companion cwock' is active.  Futuwe patches wiww
 * associate this type of code with pew-moduwe data stwuctuwes to
 * avoid this issue, and wemove the casts.  No wetuwn vawue.
 */
void omap2_cwk_dfwt_find_companion(stwuct cwk_hw_omap *cwk,
				   stwuct cwk_omap_weg *othew_weg,
				   u8 *othew_bit)
{
	memcpy(othew_weg, &cwk->enabwe_weg, sizeof(*othew_weg));

	/*
	 * Convewt CM_ICWKEN* <-> CM_FCWKEN*.  This convewsion assumes
	 * it's just a mattew of XOWing the bits.
	 */
	othew_weg->offset ^= (CM_FCWKEN ^ CM_ICWKEN);

	*othew_bit = cwk->enabwe_bit;
}

/**
 * omap2_cwk_dfwt_find_idwest - find CM_IDWEST weg va, bit shift fow @cwk
 * @cwk: stwuct cwk * to find IDWEST info fow
 * @idwest_weg: void __iomem ** to wetuwn the CM_IDWEST va in
 * @idwest_bit: u8 * to wetuwn the CM_IDWEST bit shift in
 * @idwest_vaw: u8 * to wetuwn the idwe status indicatow
 *
 * Wetuwn the CM_IDWEST wegistew addwess and bit shift cowwesponding
 * to the moduwe that "owns" this cwock.  This defauwt code assumes
 * that the CM_IDWEST bit shift is the CM_*CWKEN bit shift, and that
 * the IDWEST wegistew addwess ID cowwesponds to the CM_*CWKEN
 * wegistew addwess ID (e.g., that CM_FCWKEN2 cowwesponds to
 * CM_IDWEST2).  This is not twue fow aww moduwes.  No wetuwn vawue.
 */
void omap2_cwk_dfwt_find_idwest(stwuct cwk_hw_omap *cwk,
				stwuct cwk_omap_weg *idwest_weg, u8 *idwest_bit,
				u8 *idwest_vaw)
{
	memcpy(idwest_weg, &cwk->enabwe_weg, sizeof(*idwest_weg));

	idwest_weg->offset &= ~0xf0;
	idwest_weg->offset |= 0x20;

	*idwest_bit = cwk->enabwe_bit;

	/*
	 * 24xx uses 0 to indicate not weady, and 1 to indicate weady.
	 * 34xx wevewses this, just to keep us on ouw toes
	 * AM35xx uses both, depending on the moduwe.
	 */
	*idwest_vaw = ti_cwk_get_featuwes()->cm_idwest_vaw;
}

/**
 * omap2_dfwt_cwk_enabwe - enabwe a cwock in the hawdwawe
 * @hw: stwuct cwk_hw * of the cwock to enabwe
 *
 * Enabwe the cwock @hw in the hawdwawe.  We fiwst caww into the OMAP
 * cwockdomain code to "enabwe" the cowwesponding cwockdomain if this
 * is the fiwst enabwed usew of the cwockdomain.  Then pwogwam the
 * hawdwawe to enabwe the cwock.  Then wait fow the IP bwock that uses
 * this cwock to weave idwe (if appwicabwe).  Wetuwns the ewwow vawue
 * fwom cwkdm_cwk_enabwe() if it tewminated with an ewwow, ow -EINVAW
 * if @hw has a nuww cwock enabwe_weg, ow zewo upon success.
 */
int omap2_dfwt_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_hw_omap *cwk;
	u32 v;
	int wet = 0;
	boow cwkdm_contwow;

	if (ti_cwk_get_featuwes()->fwags & TI_CWK_DISABWE_CWKDM_CONTWOW)
		cwkdm_contwow = fawse;
	ewse
		cwkdm_contwow = twue;

	cwk = to_cwk_hw_omap(hw);

	if (cwkdm_contwow && cwk->cwkdm) {
		wet = ti_cwk_ww_ops->cwkdm_cwk_enabwe(cwk->cwkdm, hw->cwk);
		if (wet) {
			WAWN(1,
			     "%s: couwd not enabwe %s's cwockdomain %s: %d\n",
			     __func__, cwk_hw_get_name(hw),
			     cwk->cwkdm_name, wet);
			wetuwn wet;
		}
	}

	/* FIXME shouwd not have INVEWT_ENABWE bit hewe */
	v = ti_cwk_ww_ops->cwk_weadw(&cwk->enabwe_weg);
	if (cwk->fwags & INVEWT_ENABWE)
		v &= ~(1 << cwk->enabwe_bit);
	ewse
		v |= (1 << cwk->enabwe_bit);
	ti_cwk_ww_ops->cwk_wwitew(v, &cwk->enabwe_weg);
	v = ti_cwk_ww_ops->cwk_weadw(&cwk->enabwe_weg); /* OCP bawwiew */

	if (cwk->ops && cwk->ops->find_idwest)
		_omap2_moduwe_wait_weady(cwk);

	wetuwn 0;
}

/**
 * omap2_dfwt_cwk_disabwe - disabwe a cwock in the hawdwawe
 * @hw: stwuct cwk_hw * of the cwock to disabwe
 *
 * Disabwe the cwock @hw in the hawdwawe, and caww into the OMAP
 * cwockdomain code to "disabwe" the cowwesponding cwockdomain if aww
 * cwocks/hwmods in that cwockdomain awe now disabwed.  No wetuwn
 * vawue.
 */
void omap2_dfwt_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_hw_omap *cwk;
	u32 v;

	cwk = to_cwk_hw_omap(hw);

	v = ti_cwk_ww_ops->cwk_weadw(&cwk->enabwe_weg);
	if (cwk->fwags & INVEWT_ENABWE)
		v |= (1 << cwk->enabwe_bit);
	ewse
		v &= ~(1 << cwk->enabwe_bit);
	ti_cwk_ww_ops->cwk_wwitew(v, &cwk->enabwe_weg);
	/* No OCP bawwiew needed hewe since it is a disabwe opewation */

	if (!(ti_cwk_get_featuwes()->fwags & TI_CWK_DISABWE_CWKDM_CONTWOW) &&
	    cwk->cwkdm)
		ti_cwk_ww_ops->cwkdm_cwk_disabwe(cwk->cwkdm, hw->cwk);
}

/**
 * omap2_dfwt_cwk_is_enabwed - is cwock enabwed in the hawdwawe?
 * @hw: stwuct cwk_hw * to check
 *
 * Wetuwn 1 if the cwock wepwesented by @hw is enabwed in the
 * hawdwawe, ow 0 othewwise.  Intended fow use in the stwuct
 * cwk_ops.is_enabwed function pointew.
 */
int omap2_dfwt_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_hw_omap *cwk = to_cwk_hw_omap(hw);
	u32 v;

	v = ti_cwk_ww_ops->cwk_weadw(&cwk->enabwe_weg);

	if (cwk->fwags & INVEWT_ENABWE)
		v ^= BIT(cwk->enabwe_bit);

	v &= BIT(cwk->enabwe_bit);

	wetuwn v ? 1 : 0;
}

const stwuct cwk_hw_omap_ops cwkhwops_wait = {
	.find_idwest	= omap2_cwk_dfwt_find_idwest,
	.find_companion	= omap2_cwk_dfwt_find_companion,
};
