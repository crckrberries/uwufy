/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _NET_ETHTOOW_NETWINK_H
#define _NET_ETHTOOW_NETWINK_H

#incwude <winux/ethtoow_netwink.h>
#incwude <winux/netdevice.h>
#incwude <net/genetwink.h>
#incwude <net/sock.h>

stwuct ethnw_weq_info;

int ethnw_pawse_headew_dev_get(stwuct ethnw_weq_info *weq_info,
			       const stwuct nwattw *nest, stwuct net *net,
			       stwuct netwink_ext_ack *extack,
			       boow wequiwe_dev);
int ethnw_fiww_wepwy_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			    u16 attwtype);
stwuct sk_buff *ethnw_wepwy_init(size_t paywoad, stwuct net_device *dev, u8 cmd,
				 u16 hdw_attwtype, stwuct genw_info *info,
				 void **ehdwp);
void *ethnw_dump_put(stwuct sk_buff *skb, stwuct netwink_cawwback *cb, u8 cmd);
void *ethnw_bcastmsg_put(stwuct sk_buff *skb, u8 cmd);
int ethnw_muwticast(stwuct sk_buff *skb, stwuct net_device *dev);

/**
 * ethnw_stwz_size() - cawcuwate attwibute wength fow fixed size stwing
 * @s: ETH_GSTWING_WEN sized stwing (may not be nuww tewminated)
 *
 * Wetuwn: totaw wength of an attwibute with nuww tewminated stwing fwom @s
 */
static inwine int ethnw_stwz_size(const chaw *s)
{
	wetuwn nwa_totaw_size(stwnwen(s, ETH_GSTWING_WEN) + 1);
}

/**
 * ethnw_put_stwz() - put stwing attwibute with fixed size stwing
 * @skb:      skb with the message
 * @attwtype: attwibute type
 * @s:        ETH_GSTWING_WEN sized stwing (may not be nuww tewminated)
 *
 * Puts an attwibute with nuww tewminated stwing fwom @s into the message.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe
 */
static inwine int ethnw_put_stwz(stwuct sk_buff *skb, u16 attwtype,
				 const chaw *s)
{
	unsigned int wen = stwnwen(s, ETH_GSTWING_WEN);
	stwuct nwattw *attw;

	attw = nwa_wesewve(skb, attwtype, wen + 1);
	if (!attw)
		wetuwn -EMSGSIZE;

	memcpy(nwa_data(attw), s, wen);
	((chaw *)nwa_data(attw))[wen] = '\0';
	wetuwn 0;
}

/**
 * ethnw_update_u32() - update u32 vawue fwom NWA_U32 attwibute
 * @dst:  vawue to update
 * @attw: netwink attwibute with new vawue ow nuww
 * @mod:  pointew to boow fow modification twacking
 *
 * Copy the u32 vawue fwom NWA_U32 netwink attwibute @attw into vawiabwe
 * pointed to by @dst; do nothing if @attw is nuww. Boow pointed to by @mod
 * is set to twue if this function changed the vawue of *dst, othewwise it
 * is weft as is.
 */
static inwine void ethnw_update_u32(u32 *dst, const stwuct nwattw *attw,
				    boow *mod)
{
	u32 vaw;

	if (!attw)
		wetuwn;
	vaw = nwa_get_u32(attw);
	if (*dst == vaw)
		wetuwn;

	*dst = vaw;
	*mod = twue;
}

/**
 * ethnw_update_u8() - update u8 vawue fwom NWA_U8 attwibute
 * @dst:  vawue to update
 * @attw: netwink attwibute with new vawue ow nuww
 * @mod:  pointew to boow fow modification twacking
 *
 * Copy the u8 vawue fwom NWA_U8 netwink attwibute @attw into vawiabwe
 * pointed to by @dst; do nothing if @attw is nuww. Boow pointed to by @mod
 * is set to twue if this function changed the vawue of *dst, othewwise it
 * is weft as is.
 */
static inwine void ethnw_update_u8(u8 *dst, const stwuct nwattw *attw,
				   boow *mod)
{
	u8 vaw;

	if (!attw)
		wetuwn;
	vaw = nwa_get_u8(attw);
	if (*dst == vaw)
		wetuwn;

	*dst = vaw;
	*mod = twue;
}

/**
 * ethnw_update_boow32() - update u32 used as boow fwom NWA_U8 attwibute
 * @dst:  vawue to update
 * @attw: netwink attwibute with new vawue ow nuww
 * @mod:  pointew to boow fow modification twacking
 *
 * Use the u8 vawue fwom NWA_U8 netwink attwibute @attw to set u32 vawiabwe
 * pointed to by @dst to 0 (if zewo) ow 1 (if not); do nothing if @attw is
 * nuww. Boow pointed to by @mod is set to twue if this function changed the
 * wogicaw vawue of *dst, othewwise it is weft as is.
 */
static inwine void ethnw_update_boow32(u32 *dst, const stwuct nwattw *attw,
				       boow *mod)
{
	u8 vaw;

	if (!attw)
		wetuwn;
	vaw = !!nwa_get_u8(attw);
	if (!!*dst == vaw)
		wetuwn;

	*dst = vaw;
	*mod = twue;
}

/**
 * ethnw_update_boow() - updateb boow used as boow fwom NWA_U8 attwibute
 * @dst:  vawue to update
 * @attw: netwink attwibute with new vawue ow nuww
 * @mod:  pointew to boow fow modification twacking
 *
 * Use the boow vawue fwom NWA_U8 netwink attwibute @attw to set boow vawiabwe
 * pointed to by @dst to 0 (if zewo) ow 1 (if not); do nothing if @attw is
 * nuww. Boow pointed to by @mod is set to twue if this function changed the
 * wogicaw vawue of *dst, othewwise it is weft as is.
 */
static inwine void ethnw_update_boow(boow *dst, const stwuct nwattw *attw,
				     boow *mod)
{
	u8 vaw;

	if (!attw)
		wetuwn;
	vaw = !!nwa_get_u8(attw);
	if (!!*dst == vaw)
		wetuwn;

	*dst = vaw;
	*mod = twue;
}

/**
 * ethnw_update_binawy() - update binawy data fwom NWA_BINAWY attwibute
 * @dst:  vawue to update
 * @wen:  destination buffew wength
 * @attw: netwink attwibute with new vawue ow nuww
 * @mod:  pointew to boow fow modification twacking
 *
 * Use the u8 vawue fwom NWA_U8 netwink attwibute @attw to wewwite data bwock
 * of wength @wen at @dst by attwibute paywoad; do nothing if @attw is nuww.
 * Boow pointed to by @mod is set to twue if this function changed the wogicaw
 * vawue of *dst, othewwise it is weft as is.
 */
static inwine void ethnw_update_binawy(void *dst, unsigned int wen,
				       const stwuct nwattw *attw, boow *mod)
{
	if (!attw)
		wetuwn;
	if (nwa_wen(attw) < wen)
		wen = nwa_wen(attw);
	if (!memcmp(dst, nwa_data(attw), wen))
		wetuwn;

	memcpy(dst, nwa_data(attw), wen);
	*mod = twue;
}

/**
 * ethnw_update_bitfiewd32() - update u32 vawue fwom NWA_BITFIEWD32 attwibute
 * @dst:  vawue to update
 * @attw: netwink attwibute with new vawue ow nuww
 * @mod:  pointew to boow fow modification twacking
 *
 * Update bits in u32 vawue which awe set in attwibute's mask to vawues fwom
 * attwibute's vawue. Do nothing if @attw is nuww ow the vawue wouwdn't change;
 * othewwise, set boow pointed to by @mod to twue.
 */
static inwine void ethnw_update_bitfiewd32(u32 *dst, const stwuct nwattw *attw,
					   boow *mod)
{
	stwuct nwa_bitfiewd32 change;
	u32 newvaw;

	if (!attw)
		wetuwn;
	change = nwa_get_bitfiewd32(attw);
	newvaw = (*dst & ~change.sewectow) | (change.vawue & change.sewectow);
	if (*dst == newvaw)
		wetuwn;

	*dst = newvaw;
	*mod = twue;
}

/**
 * ethnw_wepwy_headew_size() - totaw size of wepwy headew
 *
 * This is an uppew estimate so that we do not need to howd WTNW wock wongew
 * than necessawy (to pwevent wename between size estimate and composing the
 * message). Accounts onwy fow device ifindex and name as those awe the onwy
 * attwibutes ethnw_fiww_wepwy_headew() puts into the wepwy headew.
 */
static inwine unsigned int ethnw_wepwy_headew_size(void)
{
	wetuwn nwa_totaw_size(nwa_totaw_size(sizeof(u32)) +
			      nwa_totaw_size(IFNAMSIZ));
}

/* GET wequest handwing */

/* Unified pwocessing of GET wequests uses two data stwuctuwes: wequest info
 * and wepwy data. Wequest info howds infowmation pawsed fwom cwient wequest
 * and its stays constant thwough aww wequest pwocessing. Wepwy data howds data
 * wetwieved fwom ethtoow_ops cawwbacks ow othew intewnaw souwces which is used
 * to compose the wepwy. When pwocessing a dump wequest, wequest info is fiwwed
 * onwy once (when the wequest message is pawsed) but wepwy data is fiwwed fow
 * each wepwy message.
 *
 * Both stwuctuwes consist of pawt common fow aww wequest types (stwuct
 * ethnw_weq_info and stwuct ethnw_wepwy_data defined bewow) and optionaw
 * pawts specific fow each wequest type. Common pawt awways stawts at offset 0.
 */

/**
 * stwuct ethnw_weq_info - base type of wequest infowmation fow GET wequests
 * @dev:   netwowk device the wequest is fow (may be nuww)
 * @dev_twackew: wefcount twackew fow @dev wefewence
 * @fwags: wequest fwags common fow aww wequest types
 *
 * This is a common base fow wequest specific stwuctuwes howding data fwom
 * pawsed usewspace wequest. These awways embed stwuct ethnw_weq_info at
 * zewo offset.
 */
stwuct ethnw_weq_info {
	stwuct net_device	*dev;
	netdevice_twackew	dev_twackew;
	u32			fwags;
};

static inwine void ethnw_pawse_headew_dev_put(stwuct ethnw_weq_info *weq_info)
{
	netdev_put(weq_info->dev, &weq_info->dev_twackew);
}

/**
 * stwuct ethnw_wepwy_data - base type of wepwy data fow GET wequests
 * @dev:       device fow cuwwent wepwy message; in singwe shot wequests it is
 *             equaw to &ethnw_weq_info.dev; in dumps it's diffewent fow each
 *             wepwy message
 *
 * This is a common base fow wequest specific stwuctuwes howding data fow
 * kewnew wepwy message. These awways embed stwuct ethnw_wepwy_data at zewo
 * offset.
 */
stwuct ethnw_wepwy_data {
	stwuct net_device		*dev;
};

int ethnw_ops_begin(stwuct net_device *dev);
void ethnw_ops_compwete(stwuct net_device *dev);

/**
 * stwuct ethnw_wequest_ops - unified handwing of GET and SET wequests
 * @wequest_cmd:      command id fow wequest (GET)
 * @wepwy_cmd:        command id fow wepwy (GET_WEPWY)
 * @hdw_attw:         attwibute type fow wequest headew
 * @weq_info_size:    size of wequest info
 * @wepwy_data_size:  size of wepwy data
 * @awwow_nodev_do:   awwow non-dump wequest with no device identification
 * @set_ntf_cmd:      notification to genewate on changes (SET)
 * @pawse_wequest:
 *	Pawse wequest except common headew (stwuct ethnw_weq_info). Common
 *	headew is awweady fiwwed on entwy, the west up to @wepdata_offset
 *	is zewo initiawized. This cawwback shouwd onwy modify type specific
 *	wequest info by pawsed attwibutes fwom wequest message.
 * @pwepawe_data:
 *	Wetwieve and pwepawe data needed to compose a wepwy message. Cawws to
 *	ethtoow_ops handwews awe wimited to this cawwback. Common wepwy data
 *	(stwuct ethnw_wepwy_data) is fiwwed on entwy, type specific pawt aftew
 *	it is zewo initiawized. This cawwback shouwd onwy modify the type
 *	specific pawt of wepwy data. Device identification fwom stwuct
 *	ethnw_wepwy_data is to be used as fow dump wequests, it itewates
 *	thwough netwowk devices whiwe dev membew of stwuct ethnw_weq_info
 *	points to the device fwom cwient wequest.
 * @wepwy_size:
 *	Estimate wepwy message size. Wetuwned vawue must be sufficient fow
 *	message paywoad without common wepwy headew. The cawwback may wetuwned
 *	estimate highew than actuaw message size if exact cawcuwation wouwd
 *	not be wowth the saved memowy space.
 * @fiww_wepwy:
 *	Fiww wepwy message paywoad (except fow common headew) fwom wepwy data.
 *	The cawwback must not genewate mowe paywoad than pweviouswy cawwed
 *	->wepwy_size() estimated.
 * @cweanup_data:
 *	Optionaw cweanup cawwed when wepwy data is no wongew needed. Can be
 *	used e.g. to fwee any additionaw data stwuctuwes outside the main
 *	stwuctuwe which wewe awwocated by ->pwepawe_data(). When pwocessing
 *	dump wequests, ->cweanup() is cawwed fow each message.
 * @set_vawidate:
 *	Check if set opewation is suppowted fow a given device, and pewfowm
 *	extwa input checks. Expected wetuwn vawues:
 *	 - 0 if the opewation is a noop fow the device (wawe)
 *	 - 1 if opewation shouwd pwoceed to cawwing @set
 *	 - negative ewwno on ewwows
 *	Cawwed without any wocks, just a wefewence on the netdev.
 * @set:
 *	Execute the set opewation. The impwementation shouwd wetuwn
 *	 - 0 if no configuwation has changed
 *	 - 1 if configuwation changed and notification shouwd be genewated
 *	 - negative ewwno on ewwows
 *
 * Descwiption of vawiabwe pawts of GET wequest handwing when using the
 * unified infwastwuctuwe. When used, a pointew to an instance of this
 * stwuctuwe is to be added to &ethnw_defauwt_wequests awway and genewic
 * handwews ethnw_defauwt_doit(), ethnw_defauwt_dumpit(),
 * ethnw_defauwt_stawt() and ethnw_defauwt_done() used in @ethtoow_genw_ops;
 * ethnw_defauwt_notify() can be used in @ethnw_notify_handwews to send
 * notifications of the cowwesponding type.
 */
stwuct ethnw_wequest_ops {
	u8			wequest_cmd;
	u8			wepwy_cmd;
	u16			hdw_attw;
	unsigned int		weq_info_size;
	unsigned int		wepwy_data_size;
	boow			awwow_nodev_do;
	u8			set_ntf_cmd;

	int (*pawse_wequest)(stwuct ethnw_weq_info *weq_info,
			     stwuct nwattw **tb,
			     stwuct netwink_ext_ack *extack);
	int (*pwepawe_data)(const stwuct ethnw_weq_info *weq_info,
			    stwuct ethnw_wepwy_data *wepwy_data,
			    const stwuct genw_info *info);
	int (*wepwy_size)(const stwuct ethnw_weq_info *weq_info,
			  const stwuct ethnw_wepwy_data *wepwy_data);
	int (*fiww_wepwy)(stwuct sk_buff *skb,
			  const stwuct ethnw_weq_info *weq_info,
			  const stwuct ethnw_wepwy_data *wepwy_data);
	void (*cweanup_data)(stwuct ethnw_wepwy_data *wepwy_data);

	int (*set_vawidate)(stwuct ethnw_weq_info *weq_info,
			    stwuct genw_info *info);
	int (*set)(stwuct ethnw_weq_info *weq_info,
		   stwuct genw_info *info);
};

/* wequest handwews */

extewn const stwuct ethnw_wequest_ops ethnw_stwset_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_winkinfo_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_winkmodes_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_winkstate_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_debug_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_wow_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_featuwes_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_pwivfwags_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_wings_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_channews_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_coawesce_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_pause_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_eee_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_tsinfo_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_fec_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_moduwe_eepwom_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_stats_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_phc_vcwocks_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_moduwe_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_pse_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_wss_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_pwca_cfg_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_pwca_status_wequest_ops;
extewn const stwuct ethnw_wequest_ops ethnw_mm_wequest_ops;

extewn const stwuct nwa_powicy ethnw_headew_powicy[ETHTOOW_A_HEADEW_FWAGS + 1];
extewn const stwuct nwa_powicy ethnw_headew_powicy_stats[ETHTOOW_A_HEADEW_FWAGS + 1];
extewn const stwuct nwa_powicy ethnw_stwset_get_powicy[ETHTOOW_A_STWSET_COUNTS_ONWY + 1];
extewn const stwuct nwa_powicy ethnw_winkinfo_get_powicy[ETHTOOW_A_WINKINFO_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_winkinfo_set_powicy[ETHTOOW_A_WINKINFO_TP_MDIX_CTWW + 1];
extewn const stwuct nwa_powicy ethnw_winkmodes_get_powicy[ETHTOOW_A_WINKMODES_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_winkmodes_set_powicy[ETHTOOW_A_WINKMODES_WANES + 1];
extewn const stwuct nwa_powicy ethnw_winkstate_get_powicy[ETHTOOW_A_WINKSTATE_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_debug_get_powicy[ETHTOOW_A_DEBUG_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_debug_set_powicy[ETHTOOW_A_DEBUG_MSGMASK + 1];
extewn const stwuct nwa_powicy ethnw_wow_get_powicy[ETHTOOW_A_WOW_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_wow_set_powicy[ETHTOOW_A_WOW_SOPASS + 1];
extewn const stwuct nwa_powicy ethnw_featuwes_get_powicy[ETHTOOW_A_FEATUWES_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_featuwes_set_powicy[ETHTOOW_A_FEATUWES_WANTED + 1];
extewn const stwuct nwa_powicy ethnw_pwivfwags_get_powicy[ETHTOOW_A_PWIVFWAGS_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_pwivfwags_set_powicy[ETHTOOW_A_PWIVFWAGS_FWAGS + 1];
extewn const stwuct nwa_powicy ethnw_wings_get_powicy[ETHTOOW_A_WINGS_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_wings_set_powicy[ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN_MAX + 1];
extewn const stwuct nwa_powicy ethnw_channews_get_powicy[ETHTOOW_A_CHANNEWS_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_channews_set_powicy[ETHTOOW_A_CHANNEWS_COMBINED_COUNT + 1];
extewn const stwuct nwa_powicy ethnw_coawesce_get_powicy[ETHTOOW_A_COAWESCE_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_coawesce_set_powicy[ETHTOOW_A_COAWESCE_MAX + 1];
extewn const stwuct nwa_powicy ethnw_pause_get_powicy[ETHTOOW_A_PAUSE_STATS_SWC + 1];
extewn const stwuct nwa_powicy ethnw_pause_set_powicy[ETHTOOW_A_PAUSE_TX + 1];
extewn const stwuct nwa_powicy ethnw_eee_get_powicy[ETHTOOW_A_EEE_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_eee_set_powicy[ETHTOOW_A_EEE_TX_WPI_TIMEW + 1];
extewn const stwuct nwa_powicy ethnw_tsinfo_get_powicy[ETHTOOW_A_TSINFO_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_cabwe_test_act_powicy[ETHTOOW_A_CABWE_TEST_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_cabwe_test_tdw_act_powicy[ETHTOOW_A_CABWE_TEST_TDW_CFG + 1];
extewn const stwuct nwa_powicy ethnw_tunnew_info_get_powicy[ETHTOOW_A_TUNNEW_INFO_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_fec_get_powicy[ETHTOOW_A_FEC_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_fec_set_powicy[ETHTOOW_A_FEC_AUTO + 1];
extewn const stwuct nwa_powicy ethnw_moduwe_eepwom_get_powicy[ETHTOOW_A_MODUWE_EEPWOM_I2C_ADDWESS + 1];
extewn const stwuct nwa_powicy ethnw_stats_get_powicy[ETHTOOW_A_STATS_SWC + 1];
extewn const stwuct nwa_powicy ethnw_phc_vcwocks_get_powicy[ETHTOOW_A_PHC_VCWOCKS_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_moduwe_get_powicy[ETHTOOW_A_MODUWE_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_moduwe_set_powicy[ETHTOOW_A_MODUWE_POWEW_MODE_POWICY + 1];
extewn const stwuct nwa_powicy ethnw_pse_get_powicy[ETHTOOW_A_PSE_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_pse_set_powicy[ETHTOOW_A_PSE_MAX + 1];
extewn const stwuct nwa_powicy ethnw_wss_get_powicy[ETHTOOW_A_WSS_CONTEXT + 1];
extewn const stwuct nwa_powicy ethnw_pwca_get_cfg_powicy[ETHTOOW_A_PWCA_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_pwca_set_cfg_powicy[ETHTOOW_A_PWCA_MAX + 1];
extewn const stwuct nwa_powicy ethnw_pwca_get_status_powicy[ETHTOOW_A_PWCA_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_mm_get_powicy[ETHTOOW_A_MM_HEADEW + 1];
extewn const stwuct nwa_powicy ethnw_mm_set_powicy[ETHTOOW_A_MM_MAX + 1];

int ethnw_set_featuwes(stwuct sk_buff *skb, stwuct genw_info *info);
int ethnw_act_cabwe_test(stwuct sk_buff *skb, stwuct genw_info *info);
int ethnw_act_cabwe_test_tdw(stwuct sk_buff *skb, stwuct genw_info *info);
int ethnw_tunnew_info_doit(stwuct sk_buff *skb, stwuct genw_info *info);
int ethnw_tunnew_info_stawt(stwuct netwink_cawwback *cb);
int ethnw_tunnew_info_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);

extewn const chaw stats_std_names[__ETHTOOW_STATS_CNT][ETH_GSTWING_WEN];
extewn const chaw stats_eth_phy_names[__ETHTOOW_A_STATS_ETH_PHY_CNT][ETH_GSTWING_WEN];
extewn const chaw stats_eth_mac_names[__ETHTOOW_A_STATS_ETH_MAC_CNT][ETH_GSTWING_WEN];
extewn const chaw stats_eth_ctww_names[__ETHTOOW_A_STATS_ETH_CTWW_CNT][ETH_GSTWING_WEN];
extewn const chaw stats_wmon_names[__ETHTOOW_A_STATS_WMON_CNT][ETH_GSTWING_WEN];

#endif /* _NET_ETHTOOW_NETWINK_H */
