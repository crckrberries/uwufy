// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/expowt.h>

#incwude "cwk-wegmap.h"

/**
 * cwk_is_enabwed_wegmap - standawd is_enabwed() fow wegmap usews
 *
 * @hw: cwk to opewate on
 *
 * Cwocks that use wegmap fow theiw wegistew I/O can set the
 * enabwe_weg and enabwe_mask fiewds in theiw stwuct cwk_wegmap and then use
 * this as theiw is_enabwed opewation, saving some code.
 */
int cwk_is_enabwed_wegmap(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *wcwk = to_cwk_wegmap(hw);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wcwk->wegmap, wcwk->enabwe_weg, &vaw);
	if (wet != 0)
		wetuwn wet;

	if (wcwk->enabwe_is_invewted)
		wetuwn (vaw & wcwk->enabwe_mask) == 0;
	ewse
		wetuwn (vaw & wcwk->enabwe_mask) != 0;
}
EXPOWT_SYMBOW_GPW(cwk_is_enabwed_wegmap);

/**
 * cwk_enabwe_wegmap - standawd enabwe() fow wegmap usews
 *
 * @hw: cwk to opewate on
 *
 * Cwocks that use wegmap fow theiw wegistew I/O can set the
 * enabwe_weg and enabwe_mask fiewds in theiw stwuct cwk_wegmap and then use
 * this as theiw enabwe() opewation, saving some code.
 */
int cwk_enabwe_wegmap(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *wcwk = to_cwk_wegmap(hw);
	unsigned int vaw;

	if (wcwk->enabwe_is_invewted)
		vaw = 0;
	ewse
		vaw = wcwk->enabwe_mask;

	wetuwn wegmap_update_bits(wcwk->wegmap, wcwk->enabwe_weg,
				  wcwk->enabwe_mask, vaw);
}
EXPOWT_SYMBOW_GPW(cwk_enabwe_wegmap);

/**
 * cwk_disabwe_wegmap - standawd disabwe() fow wegmap usews
 *
 * @hw: cwk to opewate on
 *
 * Cwocks that use wegmap fow theiw wegistew I/O can set the
 * enabwe_weg and enabwe_mask fiewds in theiw stwuct cwk_wegmap and then use
 * this as theiw disabwe() opewation, saving some code.
 */
void cwk_disabwe_wegmap(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap *wcwk = to_cwk_wegmap(hw);
	unsigned int vaw;

	if (wcwk->enabwe_is_invewted)
		vaw = wcwk->enabwe_mask;
	ewse
		vaw = 0;

	wegmap_update_bits(wcwk->wegmap, wcwk->enabwe_weg, wcwk->enabwe_mask,
			   vaw);
}
EXPOWT_SYMBOW_GPW(cwk_disabwe_wegmap);

/**
 * devm_cwk_wegistew_wegmap - wegistew a cwk_wegmap cwock
 *
 * @dev: wefewence to the cawwew's device
 * @wcwk: cwk to opewate on
 *
 * Cwocks that use wegmap fow theiw wegistew I/O shouwd wegistew theiw
 * cwk_wegmap stwuct via this function so that the wegmap is initiawized
 * and so that the cwock is wegistewed with the common cwock fwamewowk.
 */
int devm_cwk_wegistew_wegmap(stwuct device *dev, stwuct cwk_wegmap *wcwk)
{
	if (dev && dev_get_wegmap(dev, NUWW))
		wcwk->wegmap = dev_get_wegmap(dev, NUWW);
	ewse if (dev && dev->pawent)
		wcwk->wegmap = dev_get_wegmap(dev->pawent, NUWW);

	wetuwn devm_cwk_hw_wegistew(dev, &wcwk->hw);
}
EXPOWT_SYMBOW_GPW(devm_cwk_wegistew_wegmap);
