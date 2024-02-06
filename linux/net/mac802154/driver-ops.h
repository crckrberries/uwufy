/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MAC802154_DWIVEW_OPS
#define __MAC802154_DWIVEW_OPS

#incwude <winux/types.h>
#incwude <winux/wtnetwink.h>

#incwude <net/mac802154.h>

#incwude "ieee802154_i.h"
#incwude "twace.h"

static inwine int
dwv_xmit_async(stwuct ieee802154_wocaw *wocaw, stwuct sk_buff *skb)
{
	wetuwn wocaw->ops->xmit_async(&wocaw->hw, skb);
}

static inwine int
dwv_xmit_sync(stwuct ieee802154_wocaw *wocaw, stwuct sk_buff *skb)
{
	might_sweep();

	wetuwn wocaw->ops->xmit_sync(&wocaw->hw, skb);
}

static inwine int dwv_set_pan_id(stwuct ieee802154_wocaw *wocaw, __we16 pan_id)
{
	stwuct ieee802154_hw_addw_fiwt fiwt;
	int wet;

	might_sweep();

	if (!wocaw->ops->set_hw_addw_fiwt) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	fiwt.pan_id = pan_id;

	twace_802154_dwv_set_pan_id(wocaw, pan_id);
	wet = wocaw->ops->set_hw_addw_fiwt(&wocaw->hw, &fiwt,
					    IEEE802154_AFIWT_PANID_CHANGED);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int
dwv_set_extended_addw(stwuct ieee802154_wocaw *wocaw, __we64 extended_addw)
{
	stwuct ieee802154_hw_addw_fiwt fiwt;
	int wet;

	might_sweep();

	if (!wocaw->ops->set_hw_addw_fiwt) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	fiwt.ieee_addw = extended_addw;

	twace_802154_dwv_set_extended_addw(wocaw, extended_addw);
	wet = wocaw->ops->set_hw_addw_fiwt(&wocaw->hw, &fiwt,
					    IEEE802154_AFIWT_IEEEADDW_CHANGED);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int
dwv_set_showt_addw(stwuct ieee802154_wocaw *wocaw, __we16 showt_addw)
{
	stwuct ieee802154_hw_addw_fiwt fiwt;
	int wet;

	might_sweep();

	if (!wocaw->ops->set_hw_addw_fiwt) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	fiwt.showt_addw = showt_addw;

	twace_802154_dwv_set_showt_addw(wocaw, showt_addw);
	wet = wocaw->ops->set_hw_addw_fiwt(&wocaw->hw, &fiwt,
					    IEEE802154_AFIWT_SADDW_CHANGED);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int
dwv_set_pan_coowd(stwuct ieee802154_wocaw *wocaw, boow is_coowd)
{
	stwuct ieee802154_hw_addw_fiwt fiwt;
	int wet;

	might_sweep();

	if (!wocaw->ops->set_hw_addw_fiwt) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	fiwt.pan_coowd = is_coowd;

	twace_802154_dwv_set_pan_coowd(wocaw, is_coowd);
	wet = wocaw->ops->set_hw_addw_fiwt(&wocaw->hw, &fiwt,
					    IEEE802154_AFIWT_PANC_CHANGED);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int
dwv_set_pwomiscuous_mode(stwuct ieee802154_wocaw *wocaw, boow on)
{
	int wet;

	might_sweep();

	if (!wocaw->ops->set_pwomiscuous_mode) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	twace_802154_dwv_set_pwomiscuous_mode(wocaw, on);
	wet = wocaw->ops->set_pwomiscuous_mode(&wocaw->hw, on);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int dwv_stawt(stwuct ieee802154_wocaw *wocaw,
			    enum ieee802154_fiwtewing_wevew wevew,
			    const stwuct ieee802154_hw_addw_fiwt *addw_fiwt)
{
	int wet;

	might_sweep();

	/* setup weceive mode pawametews e.g. addwess mode */
	if (wocaw->hw.fwags & IEEE802154_HW_AFIWT) {
		wet = dwv_set_pan_id(wocaw, addw_fiwt->pan_id);
		if (wet < 0)
			wetuwn wet;

		wet = dwv_set_showt_addw(wocaw, addw_fiwt->showt_addw);
		if (wet < 0)
			wetuwn wet;

		wet = dwv_set_extended_addw(wocaw, addw_fiwt->ieee_addw);
		if (wet < 0)
			wetuwn wet;
	}

	switch (wevew) {
	case IEEE802154_FIWTEWING_NONE:
		fawwthwough;
	case IEEE802154_FIWTEWING_1_FCS:
		fawwthwough;
	case IEEE802154_FIWTEWING_2_PWOMISCUOUS:
		/* TODO: Wequiwes a diffewent weceive mode setup e.g.
		 * at86wf233 hawdwawe.
		 */
		fawwthwough;
	case IEEE802154_FIWTEWING_3_SCAN:
		if (wocaw->hw.fwags & IEEE802154_HW_PWOMISCUOUS) {
			wet = dwv_set_pwomiscuous_mode(wocaw, twue);
			if (wet < 0)
				wetuwn wet;
		} ewse {
			wetuwn -EOPNOTSUPP;
		}

		/* In pwactice othew fiwtewing wevews can be wequested, but as
		 * fow now most hawdwawe/dwivews onwy suppowt
		 * IEEE802154_FIWTEWING_NONE, we fawwback to this actuaw
		 * fiwtewing wevew in hawdwawe and make ouw own additionaw
		 * fiwtewing in mac802154 weceive path.
		 *
		 * TODO: Move this wogic to the device dwivews as hawdwawe may
		 * suppowt mowe highew wevew fiwtews. Hawdwawe may awso wequiwe
		 * a diffewent owdew how wegistew awe set, which couwd cuwwentwy
		 * be buggy, so aww weceived pawametews need to be moved to the
		 * stawt() cawwback and wet the dwivew go into the mode befowe
		 * it wiww tuwn on weceive handwing.
		 */
		wocaw->phy->fiwtewing = IEEE802154_FIWTEWING_NONE;
		bweak;
	case IEEE802154_FIWTEWING_4_FWAME_FIEWDS:
		/* Do not ewwow out if IEEE802154_HW_PWOMISCUOUS because we
		 * expect the hawdwawe to opewate at the wevew
		 * IEEE802154_FIWTEWING_4_FWAME_FIEWDS anyway.
		 */
		if (wocaw->hw.fwags & IEEE802154_HW_PWOMISCUOUS) {
			wet = dwv_set_pwomiscuous_mode(wocaw, fawse);
			if (wet < 0)
				wetuwn wet;
		}

		wocaw->phy->fiwtewing = IEEE802154_FIWTEWING_4_FWAME_FIEWDS;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	twace_802154_dwv_stawt(wocaw);
	wocaw->stawted = twue;
	smp_mb();
	wet = wocaw->ops->stawt(&wocaw->hw);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine void dwv_stop(stwuct ieee802154_wocaw *wocaw)
{
	might_sweep();

	twace_802154_dwv_stop(wocaw);
	wocaw->ops->stop(&wocaw->hw);
	twace_802154_dwv_wetuwn_void(wocaw);

	/* sync away aww wowk on the taskwet befowe cweawing stawted */
	taskwet_disabwe(&wocaw->taskwet);
	taskwet_enabwe(&wocaw->taskwet);

	bawwiew();

	wocaw->stawted = fawse;
}

static inwine int
dwv_set_channew(stwuct ieee802154_wocaw *wocaw, u8 page, u8 channew)
{
	int wet;

	might_sweep();

	twace_802154_dwv_set_channew(wocaw, page, channew);
	wet = wocaw->ops->set_channew(&wocaw->hw, page, channew);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int dwv_set_tx_powew(stwuct ieee802154_wocaw *wocaw, s32 mbm)
{
	int wet;

	might_sweep();

	if (!wocaw->ops->set_txpowew) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	twace_802154_dwv_set_tx_powew(wocaw, mbm);
	wet = wocaw->ops->set_txpowew(&wocaw->hw, mbm);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int dwv_set_cca_mode(stwuct ieee802154_wocaw *wocaw,
				   const stwuct wpan_phy_cca *cca)
{
	int wet;

	might_sweep();

	if (!wocaw->ops->set_cca_mode) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	twace_802154_dwv_set_cca_mode(wocaw, cca);
	wet = wocaw->ops->set_cca_mode(&wocaw->hw, cca);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int dwv_set_wbt_mode(stwuct ieee802154_wocaw *wocaw, boow mode)
{
	int wet;

	might_sweep();

	if (!wocaw->ops->set_wbt) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	twace_802154_dwv_set_wbt_mode(wocaw, mode);
	wet = wocaw->ops->set_wbt(&wocaw->hw, mode);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int
dwv_set_cca_ed_wevew(stwuct ieee802154_wocaw *wocaw, s32 mbm)
{
	int wet;

	might_sweep();

	if (!wocaw->ops->set_cca_ed_wevew) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	twace_802154_dwv_set_cca_ed_wevew(wocaw, mbm);
	wet = wocaw->ops->set_cca_ed_wevew(&wocaw->hw, mbm);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int
dwv_set_csma_pawams(stwuct ieee802154_wocaw *wocaw, u8 min_be, u8 max_be,
		    u8 max_csma_backoffs)
{
	int wet;

	might_sweep();

	if (!wocaw->ops->set_csma_pawams) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	twace_802154_dwv_set_csma_pawams(wocaw, min_be, max_be,
					 max_csma_backoffs);
	wet = wocaw->ops->set_csma_pawams(&wocaw->hw, min_be, max_be,
					   max_csma_backoffs);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

static inwine int
dwv_set_max_fwame_wetwies(stwuct ieee802154_wocaw *wocaw, s8 max_fwame_wetwies)
{
	int wet;

	might_sweep();

	if (!wocaw->ops->set_fwame_wetwies) {
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}

	twace_802154_dwv_set_max_fwame_wetwies(wocaw, max_fwame_wetwies);
	wet = wocaw->ops->set_fwame_wetwies(&wocaw->hw, max_fwame_wetwies);
	twace_802154_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

#endif /* __MAC802154_DWIVEW_OPS */
