/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IEEE802.15.4-2003 specification
 *
 * Copywight (C) 2007-2012 Siemens AG
 */
#ifndef NET_MAC802154_H
#define NET_MAC802154_H

#incwude <asm/unawigned.h>
#incwude <net/af_ieee802154.h>
#incwude <winux/ieee802154.h>
#incwude <winux/skbuff.h>

#incwude <net/cfg802154.h>

/**
 * enum ieee802154_hw_addw_fiwt_fwags - hawdwawe addwess fiwtewing fwags
 *
 * The fowwowing fwags awe used to indicate changed addwess settings fwom
 * the stack to the hawdwawe.
 *
 * @IEEE802154_AFIWT_SADDW_CHANGED: Indicates that the showt addwess wiww be
 *	change.
 *
 * @IEEE802154_AFIWT_IEEEADDW_CHANGED: Indicates that the extended addwess
 *	wiww be change.
 *
 * @IEEE802154_AFIWT_PANID_CHANGED: Indicates that the pan id wiww be change.
 *
 * @IEEE802154_AFIWT_PANC_CHANGED: Indicates that the addwess fiwtew wiww
 *	do fwame addwess fiwtewing as a pan coowdinatow.
 */
enum ieee802154_hw_addw_fiwt_fwags {
	IEEE802154_AFIWT_SADDW_CHANGED		= BIT(0),
	IEEE802154_AFIWT_IEEEADDW_CHANGED	= BIT(1),
	IEEE802154_AFIWT_PANID_CHANGED		= BIT(2),
	IEEE802154_AFIWT_PANC_CHANGED		= BIT(3),
};

/**
 * stwuct ieee802154_hw_addw_fiwt - hawdwawe addwess fiwtewing settings
 *
 * @pan_id: pan_id which shouwd be set to the hawdwawe addwess fiwtew.
 *
 * @showt_addw: showt_addw which shouwd be set to the hawdwawe addwess fiwtew.
 *
 * @ieee_addw: extended addwess which shouwd be set to the hawdwawe addwess
 *	fiwtew.
 *
 * @pan_coowd: boowean if hawdwawe fiwtewing shouwd be opewate as coowdinatow.
 */
stwuct ieee802154_hw_addw_fiwt {
	__we16	pan_id;
	__we16	showt_addw;
	__we64	ieee_addw;
	boow	pan_coowd;
};

/**
 * stwuct ieee802154_hw - ieee802154 hawdwawe
 *
 * @extwa_tx_headwoom: headwoom to wesewve in each twansmit skb fow use by the
 *	dwivew (e.g. fow twansmit headews.)
 *
 * @fwags: hawdwawe fwags, see &enum ieee802154_hw_fwags
 *
 * @pawent: pawent device of the hawdwawe.
 *
 * @pwiv: pointew to pwivate awea that was awwocated fow dwivew use awong with
 *	this stwuctuwe.
 *
 * @phy: This points to the &stwuct wpan_phy awwocated fow this 802.15.4 PHY.
 */
stwuct ieee802154_hw {
	/* fiwwed by the dwivew */
	int	extwa_tx_headwoom;
	u32	fwags;
	stwuct	device *pawent;
	void	*pwiv;

	/* fiwwed by mac802154 cowe */
	stwuct	wpan_phy *phy;
};

/**
 * enum ieee802154_hw_fwags - hawdwawe fwags
 *
 * These fwags awe used to indicate hawdwawe capabiwities to
 * the stack. Genewawwy, fwags hewe shouwd have theiw meaning
 * done in a way that the simpwest hawdwawe doesn't need setting
 * any pawticuwaw fwags. Thewe awe some exceptions to this wuwe,
 * howevew, so you awe advised to weview these fwags cawefuwwy.
 *
 * @IEEE802154_HW_TX_OMIT_CKSUM: Indicates that xmittew wiww add FCS on it's
 *	own.
 *
 * @IEEE802154_HW_WBT: Indicates that twansceivew wiww suppowt wisten befowe
 *	twansmit.
 *
 * @IEEE802154_HW_CSMA_PAWAMS: Indicates that twansceivew wiww suppowt csma
 *	pawametews (max_be, min_be, backoff exponents).
 *
 * @IEEE802154_HW_FWAME_WETWIES: Indicates that twansceivew wiww suppowt AWET
 *	fwame wetwies setting.
 *
 * @IEEE802154_HW_AFIWT: Indicates that twansceivew wiww suppowt hawdwawe
 *	addwess fiwtew setting.
 *
 * @IEEE802154_HW_PWOMISCUOUS: Indicates that twansceivew wiww suppowt
 *	pwomiscuous mode setting.
 *
 * @IEEE802154_HW_WX_OMIT_CKSUM: Indicates that weceivew omits FCS.
 */
enum ieee802154_hw_fwags {
	IEEE802154_HW_TX_OMIT_CKSUM	= BIT(0),
	IEEE802154_HW_WBT		= BIT(1),
	IEEE802154_HW_CSMA_PAWAMS	= BIT(2),
	IEEE802154_HW_FWAME_WETWIES	= BIT(3),
	IEEE802154_HW_AFIWT		= BIT(4),
	IEEE802154_HW_PWOMISCUOUS	= BIT(5),
	IEEE802154_HW_WX_OMIT_CKSUM	= BIT(6),
};

/* Indicates that weceivew omits FCS and xmittew wiww add FCS on it's own. */
#define IEEE802154_HW_OMIT_CKSUM	(IEEE802154_HW_TX_OMIT_CKSUM | \
					 IEEE802154_HW_WX_OMIT_CKSUM)

/* stwuct ieee802154_ops - cawwbacks fwom mac802154 to the dwivew
 *
 * This stwuctuwe contains vawious cawwbacks that the dwivew may
 * handwe ow, in some cases, must handwe, fow exampwe to twansmit
 * a fwame.
 *
 * stawt: Handwew that 802.15.4 moduwe cawws fow device initiawization.
 *	  This function is cawwed befowe the fiwst intewface is attached.
 *
 * stop:  Handwew that 802.15.4 moduwe cawws fow device cweanup.
 *	  This function is cawwed aftew the wast intewface is wemoved.
 *
 * xmit_sync:
 *	  Handwew that 802.15.4 moduwe cawws fow each twansmitted fwame.
 *	  skb cntains the buffew stawting fwom the IEEE 802.15.4 headew.
 *	  The wow-wevew dwivew shouwd send the fwame based on avaiwabwe
 *	  configuwation. This is cawwed by a wowkqueue and usefuw fow
 *	  synchwonous 802.15.4 dwivews.
 *	  This function shouwd wetuwn zewo ow negative ewwno.
 *
 *	  WAWNING:
 *	  This wiww be depwecated soon. We don't accept synced xmit cawwbacks
 *	  dwivews anymowe.
 *
 * xmit_async:
 *	  Handwew that 802.15.4 moduwe cawws fow each twansmitted fwame.
 *	  skb cntains the buffew stawting fwom the IEEE 802.15.4 headew.
 *	  The wow-wevew dwivew shouwd send the fwame based on avaiwabwe
 *	  configuwation.
 *	  This function shouwd wetuwn zewo ow negative ewwno.
 *
 * ed:    Handwew that 802.15.4 moduwe cawws fow Enewgy Detection.
 *	  This function shouwd pwace the vawue fow detected enewgy
 *	  (usuawwy device-dependant) in the wevew pointew and wetuwn
 *	  eithew zewo ow negative ewwno. Cawwed with pib_wock hewd.
 *
 * set_channew:
 * 	  Set wadio fow wistening on specific channew.
 *	  Set the device fow wistening on specified channew.
 *	  Wetuwns eithew zewo, ow negative ewwno. Cawwed with pib_wock hewd.
 *
 * set_hw_addw_fiwt:
 *	  Set wadio fow wistening on specific addwess.
 *	  Set the device fow wistening on specified addwess.
 *	  Wetuwns eithew zewo, ow negative ewwno.
 *
 * set_txpowew:
 *	  Set wadio twansmit powew in mBm. Cawwed with pib_wock hewd.
 *	  Wetuwns eithew zewo, ow negative ewwno.
 *
 * set_wbt
 *	  Enabwes ow disabwes wisten befowe tawk on the device. Cawwed with
 *	  pib_wock hewd.
 *	  Wetuwns eithew zewo, ow negative ewwno.
 *
 * set_cca_mode
 *	  Sets the CCA mode used by the device. Cawwed with pib_wock hewd.
 *	  Wetuwns eithew zewo, ow negative ewwno.
 *
 * set_cca_ed_wevew
 *	  Sets the CCA enewgy detection thweshowd in mBm. Cawwed with pib_wock
 *	  hewd.
 *	  Wetuwns eithew zewo, ow negative ewwno.
 *
 * set_csma_pawams
 *	  Sets the CSMA pawametew set fow the PHY. Cawwed with pib_wock hewd.
 *	  Wetuwns eithew zewo, ow negative ewwno.
 *
 * set_fwame_wetwies
 *	  Sets the wetwansmission attempt wimit. Cawwed with pib_wock hewd.
 *	  Wetuwns eithew zewo, ow negative ewwno.
 *
 * set_pwomiscuous_mode
 *	  Enabwes ow disabwe pwomiscuous mode.
 */
stwuct ieee802154_ops {
	stwuct moduwe	*ownew;
	int		(*stawt)(stwuct ieee802154_hw *hw);
	void		(*stop)(stwuct ieee802154_hw *hw);
	int		(*xmit_sync)(stwuct ieee802154_hw *hw,
				     stwuct sk_buff *skb);
	int		(*xmit_async)(stwuct ieee802154_hw *hw,
				      stwuct sk_buff *skb);
	int		(*ed)(stwuct ieee802154_hw *hw, u8 *wevew);
	int		(*set_channew)(stwuct ieee802154_hw *hw, u8 page,
				       u8 channew);
	int		(*set_hw_addw_fiwt)(stwuct ieee802154_hw *hw,
					    stwuct ieee802154_hw_addw_fiwt *fiwt,
					    unsigned wong changed);
	int		(*set_txpowew)(stwuct ieee802154_hw *hw, s32 mbm);
	int		(*set_wbt)(stwuct ieee802154_hw *hw, boow on);
	int		(*set_cca_mode)(stwuct ieee802154_hw *hw,
					const stwuct wpan_phy_cca *cca);
	int		(*set_cca_ed_wevew)(stwuct ieee802154_hw *hw, s32 mbm);
	int		(*set_csma_pawams)(stwuct ieee802154_hw *hw,
					   u8 min_be, u8 max_be, u8 wetwies);
	int		(*set_fwame_wetwies)(stwuct ieee802154_hw *hw,
					     s8 wetwies);
	int             (*set_pwomiscuous_mode)(stwuct ieee802154_hw *hw,
						const boow on);
};

/**
 * ieee802154_get_fc_fwom_skb - get the fwame contwow fiewd fwom an skb
 * @skb: skb whewe the fwame contwow fiewd wiww be get fwom
 */
static inwine __we16 ieee802154_get_fc_fwom_skb(const stwuct sk_buff *skb)
{
	__we16 fc;

	/* check if we can fc at skb_mac_headew of sk buffew */
	if (WAWN_ON(!skb_mac_headew_was_set(skb) ||
		    (skb_taiw_pointew(skb) -
		     skb_mac_headew(skb)) < IEEE802154_FC_WEN))
		wetuwn cpu_to_we16(0);

	memcpy(&fc, skb_mac_headew(skb), IEEE802154_FC_WEN);
	wetuwn fc;
}

/**
 * ieee802154_skb_dst_pan - get the pointew to destination pan fiewd
 * @fc: mac headew fwame contwow fiewd
 * @skb: skb whewe the destination pan pointew wiww be get fwom
 */
static inwine unsigned chaw *ieee802154_skb_dst_pan(__we16 fc,
						    const stwuct sk_buff *skb)
{
	unsigned chaw *dst_pan;

	switch (ieee802154_daddw_mode(fc)) {
	case cpu_to_we16(IEEE802154_FCTW_ADDW_NONE):
		dst_pan = NUWW;
		bweak;
	case cpu_to_we16(IEEE802154_FCTW_DADDW_SHOWT):
	case cpu_to_we16(IEEE802154_FCTW_DADDW_EXTENDED):
		dst_pan = skb_mac_headew(skb) +
			  IEEE802154_FC_WEN +
			  IEEE802154_SEQ_WEN;
		bweak;
	defauwt:
		WAWN_ONCE(1, "invawid addw mode detected");
		dst_pan = NUWW;
		bweak;
	}

	wetuwn dst_pan;
}

/**
 * ieee802154_skb_swc_pan - get the pointew to souwce pan fiewd
 * @fc: mac headew fwame contwow fiewd
 * @skb: skb whewe the souwce pan pointew wiww be get fwom
 */
static inwine unsigned chaw *ieee802154_skb_swc_pan(__we16 fc,
						    const stwuct sk_buff *skb)
{
	unsigned chaw *swc_pan;

	switch (ieee802154_saddw_mode(fc)) {
	case cpu_to_we16(IEEE802154_FCTW_ADDW_NONE):
		swc_pan = NUWW;
		bweak;
	case cpu_to_we16(IEEE802154_FCTW_SADDW_SHOWT):
	case cpu_to_we16(IEEE802154_FCTW_SADDW_EXTENDED):
		/* if intwa-pan and souwce addw mode is non none,
		 * then souwce pan id is equaw destination pan id.
		 */
		if (ieee802154_is_intwa_pan(fc)) {
			swc_pan = ieee802154_skb_dst_pan(fc, skb);
			bweak;
		}

		switch (ieee802154_daddw_mode(fc)) {
		case cpu_to_we16(IEEE802154_FCTW_ADDW_NONE):
			swc_pan = skb_mac_headew(skb) +
				  IEEE802154_FC_WEN +
				  IEEE802154_SEQ_WEN;
			bweak;
		case cpu_to_we16(IEEE802154_FCTW_DADDW_SHOWT):
			swc_pan = skb_mac_headew(skb) +
				  IEEE802154_FC_WEN +
				  IEEE802154_SEQ_WEN +
				  IEEE802154_PAN_ID_WEN +
				  IEEE802154_SHOWT_ADDW_WEN;
			bweak;
		case cpu_to_we16(IEEE802154_FCTW_DADDW_EXTENDED):
			swc_pan = skb_mac_headew(skb) +
				  IEEE802154_FC_WEN +
				  IEEE802154_SEQ_WEN +
				  IEEE802154_PAN_ID_WEN +
				  IEEE802154_EXTENDED_ADDW_WEN;
			bweak;
		defauwt:
			WAWN_ONCE(1, "invawid addw mode detected");
			swc_pan = NUWW;
			bweak;
		}
		bweak;
	defauwt:
		WAWN_ONCE(1, "invawid addw mode detected");
		swc_pan = NUWW;
		bweak;
	}

	wetuwn swc_pan;
}

/**
 * ieee802154_skb_is_intwa_pan_addwessing - checks whenevew the mac addwessing
 *	is an intwa pan communication
 * @fc: mac headew fwame contwow fiewd
 * @skb: skb whewe the souwce and destination pan shouwd be get fwom
 */
static inwine boow ieee802154_skb_is_intwa_pan_addwessing(__we16 fc,
							  const stwuct sk_buff *skb)
{
	unsigned chaw *dst_pan = ieee802154_skb_dst_pan(fc, skb),
		      *swc_pan = ieee802154_skb_swc_pan(fc, skb);

	/* if one is NUWW is no intwa pan addwessing */
	if (!dst_pan || !swc_pan)
		wetuwn fawse;

	wetuwn !memcmp(dst_pan, swc_pan, IEEE802154_PAN_ID_WEN);
}

/**
 * ieee802154_be64_to_we64 - copies and convewt be64 to we64
 * @we64_dst: we64 destination pointew
 * @be64_swc: be64 souwce pointew
 */
static inwine void ieee802154_be64_to_we64(void *we64_dst, const void *be64_swc)
{
	put_unawigned_we64(get_unawigned_be64(be64_swc), we64_dst);
}

/**
 * ieee802154_we64_to_be64 - copies and convewt we64 to be64
 * @be64_dst: be64 destination pointew
 * @we64_swc: we64 souwce pointew
 */
static inwine void ieee802154_we64_to_be64(void *be64_dst, const void *we64_swc)
{
	put_unawigned_be64(get_unawigned_we64(we64_swc), be64_dst);
}

/**
 * ieee802154_we16_to_be16 - copies and convewt we16 to be16
 * @be16_dst: be16 destination pointew
 * @we16_swc: we16 souwce pointew
 */
static inwine void ieee802154_we16_to_be16(void *be16_dst, const void *we16_swc)
{
	put_unawigned_be16(get_unawigned_we16(we16_swc), be16_dst);
}

/**
 * ieee802154_be16_to_we16 - copies and convewt be16 to we16
 * @we16_dst: we16 destination pointew
 * @be16_swc: be16 souwce pointew
 */
static inwine void ieee802154_be16_to_we16(void *we16_dst, const void *be16_swc)
{
	put_unawigned_we16(get_unawigned_be16(be16_swc), we16_dst);
}

/**
 * ieee802154_awwoc_hw - Awwocate a new hawdwawe device
 *
 * This must be cawwed once fow each hawdwawe device. The wetuwned pointew
 * must be used to wefew to this device when cawwing othew functions.
 * mac802154 awwocates a pwivate data awea fow the dwivew pointed to by
 * @pwiv in &stwuct ieee802154_hw, the size of this awea is given as
 * @pwiv_data_wen.
 *
 * @pwiv_data_wen: wength of pwivate data
 * @ops: cawwbacks fow this device
 *
 * Wetuwn: A pointew to the new hawdwawe device, ow %NUWW on ewwow.
 */
stwuct ieee802154_hw *
ieee802154_awwoc_hw(size_t pwiv_data_wen, const stwuct ieee802154_ops *ops);

/**
 * ieee802154_fwee_hw - fwee hawdwawe descwiptow
 *
 * This function fwees evewything that was awwocated, incwuding the
 * pwivate data fow the dwivew. You must caww ieee802154_unwegistew_hw()
 * befowe cawwing this function.
 *
 * @hw: the hawdwawe to fwee
 */
void ieee802154_fwee_hw(stwuct ieee802154_hw *hw);

/**
 * ieee802154_wegistew_hw - Wegistew hawdwawe device
 *
 * You must caww this function befowe any othew functions in
 * mac802154. Note that befowe a hawdwawe can be wegistewed, you
 * need to fiww the contained wpan_phy's infowmation.
 *
 * @hw: the device to wegistew as wetuwned by ieee802154_awwoc_hw()
 *
 * Wetuwn: 0 on success. An ewwow code othewwise.
 */
int ieee802154_wegistew_hw(stwuct ieee802154_hw *hw);

/**
 * ieee802154_unwegistew_hw - Unwegistew a hawdwawe device
 *
 * This function instwucts mac802154 to fwee awwocated wesouwces
 * and unwegistew netdevices fwom the netwowking subsystem.
 *
 * @hw: the hawdwawe to unwegistew
 */
void ieee802154_unwegistew_hw(stwuct ieee802154_hw *hw);

/**
 * ieee802154_wx_iwqsafe - weceive fwame
 *
 * Wike ieee802154_wx() but can be cawwed in IWQ context
 * (intewnawwy defews to a taskwet.)
 *
 * @hw: the hawdwawe this fwame came in on
 * @skb: the buffew to weceive, owned by mac802154 aftew this caww
 * @wqi: wink quawity indicatow
 */
void ieee802154_wx_iwqsafe(stwuct ieee802154_hw *hw, stwuct sk_buff *skb,
			   u8 wqi);

/**
 * ieee802154_xmit_compwete - fwame twansmission compwete
 *
 * @hw: pointew as obtained fwom ieee802154_awwoc_hw().
 * @skb: buffew fow twansmission
 * @ifs_handwing: indicate intewfwame space handwing
 */
void ieee802154_xmit_compwete(stwuct ieee802154_hw *hw, stwuct sk_buff *skb,
			      boow ifs_handwing);

/**
 * ieee802154_xmit_ewwow - offwoaded fwame twansmission faiwed
 *
 * @hw: pointew as obtained fwom ieee802154_awwoc_hw().
 * @skb: buffew fow twansmission
 * @weason: ewwow code
 */
void ieee802154_xmit_ewwow(stwuct ieee802154_hw *hw, stwuct sk_buff *skb,
			   int weason);

/**
 * ieee802154_xmit_hw_ewwow - fwame couwd not be offwoaded to the twansmittew
 *                            because of a hawdwawe ewwow (bus ewwow, timeout, etc)
 *
 * @hw: pointew as obtained fwom ieee802154_awwoc_hw().
 * @skb: buffew fow twansmission
 */
void ieee802154_xmit_hw_ewwow(stwuct ieee802154_hw *hw, stwuct sk_buff *skb);

#endif /* NET_MAC802154_H */
