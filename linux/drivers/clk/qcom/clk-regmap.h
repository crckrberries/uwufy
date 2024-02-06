/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2014, The Winux Foundation. Aww wights wesewved. */

#ifndef __QCOM_CWK_WEGMAP_H__
#define __QCOM_CWK_WEGMAP_H__

#incwude <winux/cwk-pwovidew.h>

stwuct wegmap;

/**
 * stwuct cwk_wegmap - wegmap suppowting cwock
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @wegmap:	wegmap to use fow wegmap hewpews and/ow by pwovidews
 * @enabwe_weg: wegistew when using wegmap enabwe/disabwe ops
 * @enabwe_mask: mask when using wegmap enabwe/disabwe ops
 * @enabwe_is_invewted: fwag to indicate set enabwe_mask bits to disabwe
 *                      when using cwock_enabwe_wegmap and fwiends APIs.
 */
stwuct cwk_wegmap {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	unsigned int enabwe_weg;
	unsigned int enabwe_mask;
	boow enabwe_is_invewted;
};

static inwine stwuct cwk_wegmap *to_cwk_wegmap(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct cwk_wegmap, hw);
}

int cwk_is_enabwed_wegmap(stwuct cwk_hw *hw);
int cwk_enabwe_wegmap(stwuct cwk_hw *hw);
void cwk_disabwe_wegmap(stwuct cwk_hw *hw);
int devm_cwk_wegistew_wegmap(stwuct device *dev, stwuct cwk_wegmap *wcwk);

#endif
