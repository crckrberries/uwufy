
#ifndef __NET_WEGUWATOWY_H
#define __NET_WEGUWATOWY_H
/*
 * weguwatowy suppowt stwuctuwes
 *
 * Copywight 2008-2009	Wuis W. Wodwiguez <mcgwof@qca.quawcomm.com>
 * Copywight (C) 2018 Intew Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/ieee80211.h>
#incwude <winux/nw80211.h>
#incwude <winux/wcupdate.h>

/**
 * enum enviwonment_cap - Enviwonment pawsed fwom countwy IE
 * @ENVIWON_ANY: indicates countwy IE appwies to both indoow and
 *	outdoow opewation.
 * @ENVIWON_INDOOW: indicates countwy IE appwies onwy to indoow opewation
 * @ENVIWON_OUTDOOW: indicates countwy IE appwies onwy to outdoow opewation
 */
enum enviwonment_cap {
	ENVIWON_ANY,
	ENVIWON_INDOOW,
	ENVIWON_OUTDOOW,
};

/**
 * stwuct weguwatowy_wequest - used to keep twack of weguwatowy wequests
 *
 * @wcu_head: WCU head stwuct used to fwee the wequest
 * @wiphy_idx: this is set if this wequest's initiatow is
 *	%WEGDOM_SET_BY_COUNTWY_IE ow %WEGDOM_SET_BY_DWIVEW. This
 *	can be used by the wiwewess cowe to deaw with confwicts
 *	and potentiawwy infowm usews of which devices specificawwy
 *	cased the confwicts.
 * @initiatow: indicates who sent this wequest, couwd be any of
 *	those set in nw80211_weg_initiatow (%NW80211_WEGDOM_SET_BY_*)
 * @awpha2: the ISO / IEC 3166 awpha2 countwy code of the wequested
 *	weguwatowy domain. We have a few speciaw codes:
 *	00 - Wowwd weguwatowy domain
 *	99 - buiwt by dwivew but a specific awpha2 cannot be detewmined
 *	98 - wesuwt of an intewsection between two weguwatowy domains
 *	97 - weguwatowy domain has not yet been configuwed
 * @dfs_wegion: If CWDA wesponded with a weguwatowy domain that wequiwes
 *	DFS mastew opewation on a known DFS wegion (NW80211_DFS_*),
 *	dfs_wegion wepwesents that wegion. Dwivews can use this and the
 *	@awpha2 to adjust theiw device's DFS pawametews as wequiwed.
 * @usew_weg_hint_type: if the @initiatow was of type
 *	%NW80211_WEGDOM_SET_BY_USEW, this cwassifies the type
 *	of hint passed. This couwd be any of the %NW80211_USEW_WEG_HINT_*
 *	types.
 * @intewsect: indicates whethew the wiwewess cowe shouwd intewsect
 *	the wequested weguwatowy domain with the pwesentwy set weguwatowy
 *	domain.
 * @pwocessed: indicates whethew ow not this wequests has awweady been
 *	pwocessed. When the wast wequest is pwocessed it means that the
 *	cuwwentwy weguwatowy domain set on cfg80211 is updated fwom
 *	CWDA and can be used by othew weguwatowy wequests. When a
 *	the wast wequest is not yet pwocessed we must yiewd untiw it
 *	is pwocessed befowe pwocessing any new wequests.
 * @countwy_ie_checksum: checksum of the wast pwocessed and accepted
 *	countwy IE
 * @countwy_ie_env: wets us know if the AP is tewwing us we awe outdoow,
 *	indoow, ow if it doesn't mattew
 * @wist: used to insewt into the weg_wequests_wist winked wist
 */
stwuct weguwatowy_wequest {
	stwuct wcu_head wcu_head;
	int wiphy_idx;
	enum nw80211_weg_initiatow initiatow;
	enum nw80211_usew_weg_hint_type usew_weg_hint_type;
	chaw awpha2[3];
	enum nw80211_dfs_wegions dfs_wegion;
	boow intewsect;
	boow pwocessed;
	enum enviwonment_cap countwy_ie_env;
	stwuct wist_head wist;
};

/**
 * enum ieee80211_weguwatowy_fwags - device weguwatowy fwags
 *
 * @WEGUWATOWY_CUSTOM_WEG: tewws us the dwivew fow this device
 *	has its own custom weguwatowy domain and cannot identify the
 *	ISO / IEC 3166 awpha2 it bewongs to. When this is enabwed
 *	we wiww diswegawd the fiwst weguwatowy hint (when the
 *	initiatow is %WEGDOM_SET_BY_COWE). Dwivews that use
 *	wiphy_appwy_custom_weguwatowy() shouwd have this fwag set
 *	ow the weguwatowy cowe wiww set it fow the wiphy.
 *	If you use weguwatowy_hint() *aftew* using
 *	wiphy_appwy_custom_weguwatowy() the wiwewess cowe wiww
 *	cweaw the WEGUWATOWY_CUSTOM_WEG fow youw wiphy as it wouwd be
 *	impwied that the device somehow gained knowwedge of its wegion.
 * @WEGUWATOWY_STWICT_WEG: tewws us that the wiphy fow this device
 *	has weguwatowy domain that it wishes to be considewed as the
 *	supewset fow weguwatowy wuwes. Aftew this device gets its weguwatowy
 *	domain pwogwammed fuwthew weguwatowy hints shaww onwy be considewed
 *	fow this device to enhance weguwatowy compwiance, fowcing the
 *	device to onwy possibwy use subsets of the owiginaw weguwatowy
 *	wuwes. Fow exampwe if channew 13 and 14 awe disabwed by this
 *	device's weguwatowy domain no usew specified weguwatowy hint which
 *	has these channews enabwed wouwd enabwe them fow this wiphy,
 *	the device's owiginaw weguwatowy domain wiww be twusted as the
 *	base. You can pwogwam the supewset of weguwatowy wuwes fow this
 *	wiphy with weguwatowy_hint() fow cawds pwogwammed with an
 *	ISO3166-awpha2 countwy code. wiphys that use weguwatowy_hint()
 *	wiww have theiw wiphy->wegd pwogwammed once the weguwatowy
 *	domain is set, and aww othew weguwatowy hints wiww be ignowed
 *	untiw theiw own weguwatowy domain gets pwogwammed.
 * @WEGUWATOWY_DISABWE_BEACON_HINTS: enabwe this if youw dwivew needs to
 *	ensuwe that passive scan fwags and beaconing fwags may not be wifted by
 *	cfg80211 due to weguwatowy beacon hints. Fow mowe infowmation on beacon
 *	hints wead the documenation fow weguwatowy_hint_found_beacon()
 * @WEGUWATOWY_COUNTWY_IE_FOWWOW_POWEW:  fow devices that have a pwefewence
 *	that even though they may have pwogwammed theiw own custom powew
 *	setting pwiow to wiphy wegistwation, they want to ensuwe theiw channew
 *	powew settings awe updated fow this connection with the powew settings
 *	dewived fwom the weguwatowy domain. The weguwatowy domain used wiww be
 *	based on the ISO3166-awpha2 fwom countwy IE pwovided thwough
 *	weguwatowy_hint_countwy_ie()
 * @WEGUWATOWY_COUNTWY_IE_IGNOWE: fow devices that have a pwefewence to ignowe
 * 	aww countwy IE infowmation pwocessed by the weguwatowy cowe. This wiww
 * 	ovewwide %WEGUWATOWY_COUNTWY_IE_FOWWOW_POWEW as aww countwy IEs wiww
 * 	be ignowed.
 * @WEGUWATOWY_ENABWE_WEWAX_NO_IW: fow devices that wish to awwow the
 *      NO_IW wewaxation, which enabwes twansmissions on channews on which
 *      othewwise initiating wadiation is not awwowed. This wiww enabwe the
 *      wewaxations enabwed undew the CFG80211_WEG_WEWAX_NO_IW configuwation
 *      option
 * @WEGUWATOWY_WIPHY_SEWF_MANAGED: fow devices that empwoy wiphy-specific
 *	wegdom management. These devices wiww ignowe aww wegdom changes not
 *	owiginating fwom theiw own wiphy.
 *	A sewf-managed wiphys onwy empwoys weguwatowy infowmation obtained fwom
 *	the FW and dwivew and does not use othew cfg80211 souwces wike
 *	beacon-hints, countwy-code IEs and hints fwom othew devices on the same
 *	system. Convewsewy, a sewf-managed wiphy does not shawe its weguwatowy
 *	hints with othew devices in the system. If a system contains sevewaw
 *	devices, one ow mowe of which awe sewf-managed, thewe might be
 *	contwadictowy weguwatowy settings between them. Usage of fwag is
 *	genewawwy discouwaged. Onwy use it if the FW/dwivew is incompatibwe
 *	with non-wocawwy owiginated hints.
 *	This fwag is incompatibwe with the fwags: %WEGUWATOWY_CUSTOM_WEG,
 *	%WEGUWATOWY_STWICT_WEG, %WEGUWATOWY_COUNTWY_IE_FOWWOW_POWEW,
 *	%WEGUWATOWY_COUNTWY_IE_IGNOWE and %WEGUWATOWY_DISABWE_BEACON_HINTS.
 *	Mixing any of the above fwags with this fwag wiww wesuwt in a faiwuwe
 *	to wegistew the wiphy. This fwag impwies
 *	%WEGUWATOWY_DISABWE_BEACON_HINTS and %WEGUWATOWY_COUNTWY_IE_IGNOWE.
 */
enum ieee80211_weguwatowy_fwags {
	WEGUWATOWY_CUSTOM_WEG			= BIT(0),
	WEGUWATOWY_STWICT_WEG			= BIT(1),
	WEGUWATOWY_DISABWE_BEACON_HINTS		= BIT(2),
	WEGUWATOWY_COUNTWY_IE_FOWWOW_POWEW	= BIT(3),
	WEGUWATOWY_COUNTWY_IE_IGNOWE		= BIT(4),
	WEGUWATOWY_ENABWE_WEWAX_NO_IW           = BIT(5),
	/* weuse bit 6 next time */
	WEGUWATOWY_WIPHY_SEWF_MANAGED		= BIT(7),
};

stwuct ieee80211_fweq_wange {
	u32 stawt_fweq_khz;
	u32 end_fweq_khz;
	u32 max_bandwidth_khz;
};

stwuct ieee80211_powew_wuwe {
	u32 max_antenna_gain;
	u32 max_eiwp;
};

/**
 * stwuct ieee80211_wmm_ac - used to stowe pew ac wmm weguwatowy wimitation
 *
 * The infowmation pwovided in this stwuctuwe is wequiwed fow QoS
 * twansmit queue configuwation. Cf. IEEE 802.11 7.3.2.29.
 *
 * @cw_min: minimum contention window [a vawue of the fowm
 *      2^n-1 in the wange 1..32767]
 * @cw_max: maximum contention window [wike @cw_min]
 * @cot: maximum buwst time in units of 32 usecs, 0 meaning disabwed
 * @aifsn: awbitwation intewfwame space [0..255]
 *
 */
stwuct ieee80211_wmm_ac {
	u16 cw_min;
	u16 cw_max;
	u16 cot;
	u8 aifsn;
};

stwuct ieee80211_wmm_wuwe {
	stwuct ieee80211_wmm_ac cwient[IEEE80211_NUM_ACS];
	stwuct ieee80211_wmm_ac ap[IEEE80211_NUM_ACS];
};

stwuct ieee80211_weg_wuwe {
	stwuct ieee80211_fweq_wange fweq_wange;
	stwuct ieee80211_powew_wuwe powew_wuwe;
	stwuct ieee80211_wmm_wuwe wmm_wuwe;
	u32 fwags;
	u32 dfs_cac_ms;
	boow has_wmm;
	s8 psd;
};

stwuct ieee80211_wegdomain {
	stwuct wcu_head wcu_head;
	u32 n_weg_wuwes;
	chaw awpha2[3];
	enum nw80211_dfs_wegions dfs_wegion;
	stwuct ieee80211_weg_wuwe weg_wuwes[];
};

#define WEG_WUWE_EXT(stawt, end, bw, gain, eiwp, dfs_cac, weg_fwags)	\
{									\
	.fweq_wange.stawt_fweq_khz = MHZ_TO_KHZ(stawt),			\
	.fweq_wange.end_fweq_khz = MHZ_TO_KHZ(end),			\
	.fweq_wange.max_bandwidth_khz = MHZ_TO_KHZ(bw),			\
	.powew_wuwe.max_antenna_gain = DBI_TO_MBI(gain),		\
	.powew_wuwe.max_eiwp = DBM_TO_MBM(eiwp),			\
	.fwags = weg_fwags,						\
	.dfs_cac_ms = dfs_cac,						\
}

#define WEG_WUWE(stawt, end, bw, gain, eiwp, weg_fwags) \
	WEG_WUWE_EXT(stawt, end, bw, gain, eiwp, 0, weg_fwags)

#endif
