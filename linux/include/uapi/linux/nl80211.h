#ifndef __WINUX_NW80211_H
#define __WINUX_NW80211_H
/*
 * 802.11 netwink intewface pubwic headew
 *
 * Copywight 2006-2010 Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2008 Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2008 Wuis Cawwos Cobo <wuisca@cozybit.com>
 * Copywight 2008 Michaew Buesch <m@bues.ch>
 * Copywight 2008, 2009 Wuis W. Wodwiguez <wwodwiguez@athewos.com>
 * Copywight 2008 Jouni Mawinen <jouni.mawinen@athewos.com>
 * Copywight 2008 Cowin McCabe <cowin@cozybit.com>
 * Copywight 2015-2017	Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
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
 *
 */

/*
 * This headew fiwe defines the usewspace API to the wiwewess stack. Pwease
 * be cawefuw not to bweak things - i.e. don't move anything awound ow so
 * unwess you can demonstwate that it bweaks neithew API now ABI.
 *
 * Additions to the API shouwd be accompanied by actuaw impwementations in
 * an upstweam dwivew, so that exampwe impwementations exist in case thewe
 * awe evew concewns about the pwecise semantics of the API ow changes awe
 * needed, and to ensuwe that code fow dead (no wongew impwemented) API
 * can actuawwy be identified and wemoved.
 * Nonethewess, semantics shouwd awso be documented cawefuwwy in this fiwe.
 */

#incwude <winux/types.h>

#define NW80211_GENW_NAME "nw80211"

#define NW80211_MUWTICAST_GWOUP_CONFIG		"config"
#define NW80211_MUWTICAST_GWOUP_SCAN		"scan"
#define NW80211_MUWTICAST_GWOUP_WEG		"weguwatowy"
#define NW80211_MUWTICAST_GWOUP_MWME		"mwme"
#define NW80211_MUWTICAST_GWOUP_VENDOW		"vendow"
#define NW80211_MUWTICAST_GWOUP_NAN		"nan"
#define NW80211_MUWTICAST_GWOUP_TESTMODE	"testmode"

#define NW80211_EDMG_BW_CONFIG_MIN	4
#define NW80211_EDMG_BW_CONFIG_MAX	15
#define NW80211_EDMG_CHANNEWS_MIN	1
#define NW80211_EDMG_CHANNEWS_MAX	0x3c /* 0b00111100 */

/**
 * DOC: Station handwing
 *
 * Stations awe added pew intewface, but a speciaw case exists with VWAN
 * intewfaces. When a station is bound to an AP intewface, it may be moved
 * into a VWAN identified by a VWAN intewface index (%NW80211_ATTW_STA_VWAN).
 * The station is stiww assumed to bewong to the AP intewface it was added
 * to.
 *
 * Station handwing vawies pew intewface type and depending on the dwivew's
 * capabiwities.
 *
 * Fow dwivews suppowting TDWS with extewnaw setup (WIPHY_FWAG_SUPPOWTS_TDWS
 * and WIPHY_FWAG_TDWS_EXTEWNAW_SETUP), the station wifetime is as fowwows:
 *  - a setup station entwy is added, not yet authowized, without any wate
 *    ow capabiwity infowmation; this just exists to avoid wace conditions
 *  - when the TDWS setup is done, a singwe NW80211_CMD_SET_STATION is vawid
 *    to add wate and capabiwity infowmation to the station and at the same
 *    time mawk it authowized.
 *  - %NW80211_TDWS_ENABWE_WINK is then used
 *  - aftew this, the onwy vawid opewation is to wemove it by teawing down
 *    the TDWS wink (%NW80211_TDWS_DISABWE_WINK)
 *
 * TODO: need mowe info fow othew intewface types
 */

/**
 * DOC: Fwame twansmission/wegistwation suppowt
 *
 * Fwame twansmission and wegistwation suppowt exists to awwow usewspace
 * management entities such as wpa_suppwicant to weact to management fwames
 * that awe not being handwed by the kewnew. This incwudes, fow exampwe,
 * cewtain cwasses of action fwames that cannot be handwed in the kewnew
 * fow vawious weasons.
 *
 * Fwame wegistwation is done on a pew-intewface basis and wegistwations
 * cannot be wemoved othew than by cwosing the socket. It is possibwe to
 * specify a wegistwation fiwtew to wegistew, fow exampwe, onwy fow a
 * cewtain type of action fwame. In pawticuwaw with action fwames, those
 * that usewspace wegistews fow wiww not be wetuwned as unhandwed by the
 * dwivew, so that the wegistewed appwication has to take wesponsibiwity
 * fow doing that.
 *
 * The type of fwame that can be wegistewed fow is awso dependent on the
 * dwivew and intewface type. The fwame types awe advewtised in wiphy
 * attwibutes so appwications know what to expect.
 *
 * NOTE: When an intewface changes type whiwe wegistwations awe active,
 *       these wegistwations awe ignowed untiw the intewface type is
 *       changed again. This means that changing the intewface type can
 *       wead to a situation that couwdn't othewwise be pwoduced, but
 *       any such wegistwations wiww be dowmant in the sense that they
 *       wiww not be sewviced, i.e. they wiww not weceive any fwames.
 *
 * Fwame twansmission awwows usewspace to send fow exampwe the wequiwed
 * wesponses to action fwames. It is subject to some sanity checking,
 * but many fwames can be twansmitted. When a fwame is twansmitted, its
 * status is indicated to the sending socket.
 *
 * Fow mowe technicaw detaiws, see the cowwesponding command descwiptions
 * bewow.
 */

/**
 * DOC: Viwtuaw intewface / concuwwency capabiwities
 *
 * Some devices awe abwe to opewate with viwtuaw MACs; they can have
 * mowe than one viwtuaw intewface. The capabiwity handwing fow this
 * is a bit compwex though, as thewe may be a numbew of westwictions
 * on the types of concuwwency that awe suppowted.
 *
 * To stawt with, each device suppowts the intewface types wisted in
 * the %NW80211_ATTW_SUPPOWTED_IFTYPES attwibute, but by wisting the
 * types thewe no concuwwency is impwied.
 *
 * Once concuwwency is desiwed, mowe attwibutes must be obsewved:
 * To stawt with, since some intewface types awe puwewy managed in
 * softwawe, wike the AP-VWAN type in mac80211 fow exampwe, thewe's
 * an additionaw wist of these; they can be added at any time and
 * awe onwy westwicted by some semantic westwictions (e.g. AP-VWAN
 * cannot be added without a cowwesponding AP intewface). This wist
 * is expowted in the %NW80211_ATTW_SOFTWAWE_IFTYPES attwibute.
 *
 * Fuwthew, the wist of suppowted combinations is expowted. This is
 * in the %NW80211_ATTW_INTEWFACE_COMBINATIONS attwibute. Basicawwy,
 * it expowts a wist of "gwoups", and at any point in time the
 * intewfaces that awe cuwwentwy active must faww into any one of
 * the advewtised gwoups. Within each gwoup, thewe awe westwictions
 * on the numbew of intewfaces of diffewent types that awe suppowted
 * and awso the numbew of diffewent channews, awong with potentiawwy
 * some othew westwictions. See &enum nw80211_if_combination_attws.
 *
 * Aww togethew, these attwibutes define the concuwwency of viwtuaw
 * intewfaces that a given device suppowts.
 */

/**
 * DOC: packet coawesce suppowt
 *
 * In most cases, host that weceives IPv4 and IPv6 muwticast/bwoadcast
 * packets does not do anything with these packets. Thewefowe the
 * weception of these unwanted packets causes unnecessawy pwocessing
 * and powew consumption.
 *
 * Packet coawesce featuwe hewps to weduce numbew of weceived intewwupts
 * to host by buffewing these packets in fiwmwawe/hawdwawe fow some
 * pwedefined time. Weceived intewwupt wiww be genewated when one of the
 * fowwowing events occuws.
 * a) Expiwation of hawdwawe timew whose expiwation time is set to maximum
 * coawescing deway of matching coawesce wuwe.
 * b) Coawescing buffew in hawdwawe weaches its wimit.
 * c) Packet doesn't match any of the configuwed coawesce wuwes.
 *
 * Usew needs to configuwe fowwowing pawametews fow cweating a coawesce
 * wuwe.
 * a) Maximum coawescing deway
 * b) Wist of packet pattewns which needs to be matched
 * c) Condition fow coawescence: pattewn 'match' ow 'no match'
 * Muwtipwe such wuwes can be cweated.
 */

/**
 * DOC: WPA/WPA2 EAPOW handshake offwoad
 *
 * By setting @NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_STA_PSK fwag dwivews
 * can indicate they suppowt offwoading EAPOW handshakes fow WPA/WPA2
 * pweshawed key authentication in station mode. In %NW80211_CMD_CONNECT
 * the pweshawed key shouwd be specified using %NW80211_ATTW_PMK. Dwivews
 * suppowting this offwoad may weject the %NW80211_CMD_CONNECT when no
 * pweshawed key matewiaw is pwovided, fow exampwe when that dwivew does
 * not suppowt setting the tempowaw keys thwough %NW80211_CMD_NEW_KEY.
 *
 * Simiwawwy @NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_STA_1X fwag can be
 * set by dwivews indicating offwoad suppowt of the PTK/GTK EAPOW
 * handshakes duwing 802.1X authentication in station mode. In owdew to
 * use the offwoad the %NW80211_CMD_CONNECT shouwd have
 * %NW80211_ATTW_WANT_1X_4WAY_HS attwibute fwag. Dwivews suppowting this
 * offwoad may weject the %NW80211_CMD_CONNECT when the attwibute fwag is
 * not pwesent.
 *
 * By setting @NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_AP_PSK fwag dwivews
 * can indicate they suppowt offwoading EAPOW handshakes fow WPA/WPA2
 * pweshawed key authentication in AP mode. In %NW80211_CMD_STAWT_AP
 * the pweshawed key shouwd be specified using %NW80211_ATTW_PMK. Dwivews
 * suppowting this offwoad may weject the %NW80211_CMD_STAWT_AP when no
 * pweshawed key matewiaw is pwovided, fow exampwe when that dwivew does
 * not suppowt setting the tempowaw keys thwough %NW80211_CMD_NEW_KEY.
 *
 * Fow 802.1X the PMK ow PMK-W0 awe set by pwoviding %NW80211_ATTW_PMK
 * using %NW80211_CMD_SET_PMK. Fow offwoaded FT suppowt awso
 * %NW80211_ATTW_PMKW0_NAME must be pwovided.
 */

/**
 * DOC: FIWS shawed key authentication offwoad
 *
 * FIWS shawed key authentication offwoad can be advewtised by dwivews by
 * setting @NW80211_EXT_FEATUWE_FIWS_SK_OFFWOAD fwag. The dwivews that suppowt
 * FIWS shawed key authentication offwoad shouwd be abwe to constwuct the
 * authentication and association fwames fow FIWS shawed key authentication and
 * eventuawwy do a key dewivation as pew IEEE 802.11ai. The bewow additionaw
 * pawametews shouwd be given to dwivew in %NW80211_CMD_CONNECT and/ow in
 * %NW80211_CMD_UPDATE_CONNECT_PAWAMS.
 *	%NW80211_ATTW_FIWS_EWP_USEWNAME - used to constwuct keyname_nai
 *	%NW80211_ATTW_FIWS_EWP_WEAWM - used to constwuct keyname_nai
 *	%NW80211_ATTW_FIWS_EWP_NEXT_SEQ_NUM - used to constwuct ewp message
 *	%NW80211_ATTW_FIWS_EWP_WWK - used to genewate the wIK and wMSK
 * wIK shouwd be used to genewate an authentication tag on the EWP message and
 * wMSK shouwd be used to dewive a PMKSA.
 * wIK, wMSK shouwd be genewated and keyname_nai, sequence numbew shouwd be used
 * as specified in IETF WFC 6696.
 *
 * When FIWS shawed key authentication is compweted, dwivew needs to pwovide the
 * bewow additionaw pawametews to usewspace, which can be eithew aftew setting
 * up a connection ow aftew woaming.
 *	%NW80211_ATTW_FIWS_KEK - used fow key wenewaw
 *	%NW80211_ATTW_FIWS_EWP_NEXT_SEQ_NUM - used in fuwthew EAP-WP exchanges
 *	%NW80211_ATTW_PMKID - used to identify the PMKSA used/genewated
 *	%Nw80211_ATTW_PMK - used to update PMKSA cache in usewspace
 * The PMKSA can be maintained in usewspace pewsistentwy so that it can be used
 * watew aftew weboots ow wifi tuwn off/on awso.
 *
 * %NW80211_ATTW_FIWS_CACHE_ID is the cache identifiew advewtised by a FIWS
 * capabwe AP suppowting PMK caching. It specifies the scope within which the
 * PMKSAs awe cached in an ESS. %NW80211_CMD_SET_PMKSA and
 * %NW80211_CMD_DEW_PMKSA awe enhanced to awwow suppowt fow PMKSA caching based
 * on FIWS cache identifiew. Additionawwy %NW80211_ATTW_PMK is used with
 * %NW80211_SET_PMKSA to specify the PMK cowwesponding to a PMKSA fow dwivew to
 * use in a FIWS shawed key connection with PMKSA caching.
 */

/**
 * DOC: SAE authentication offwoad
 *
 * By setting @NW80211_EXT_FEATUWE_SAE_OFFWOAD fwag dwivews can indicate they
 * suppowt offwoading SAE authentication fow WPA3-Pewsonaw netwowks in station
 * mode. Simiwawwy @NW80211_EXT_FEATUWE_SAE_OFFWOAD_AP fwag can be set by
 * dwivews indicating the offwoad suppowt in AP mode.
 *
 * The passwowd fow SAE shouwd be specified using %NW80211_ATTW_SAE_PASSWOWD in
 * %NW80211_CMD_CONNECT and %NW80211_CMD_STAWT_AP fow station and AP mode
 * wespectivewy.
 */

/**
 * DOC: VWAN offwoad suppowt fow setting gwoup keys and binding STAs to VWANs
 *
 * By setting @NW80211_EXT_FEATUWE_VWAN_OFFWOAD fwag dwivews can indicate they
 * suppowt offwoading VWAN functionawity in a mannew whewe the dwivew exposes a
 * singwe netdev that uses VWAN tagged fwames and sepawate VWAN-specific netdevs
 * can then be added using WTM_NEWWINK/IFWA_VWAN_ID simiwawwy to the Ethewnet
 * case. Fwames weceived fwom stations that awe not assigned to any VWAN awe
 * dewivewed on the main netdev and fwames to such stations can be sent thwough
 * that main netdev.
 *
 * %NW80211_CMD_NEW_KEY (fow gwoup keys), %NW80211_CMD_NEW_STATION, and
 * %NW80211_CMD_SET_STATION wiww optionawwy specify vwan_id using
 * %NW80211_ATTW_VWAN_ID.
 */

/**
 * DOC: TID configuwation
 *
 * TID config suppowt can be checked in the %NW80211_ATTW_TID_CONFIG
 * attwibute given in wiphy capabiwities.
 *
 * The necessawy configuwation pawametews awe mentioned in
 * &enum nw80211_tid_config_attw and it wiww be passed to the
 * %NW80211_CMD_SET_TID_CONFIG command in %NW80211_ATTW_TID_CONFIG.
 *
 * If the configuwation needs to be appwied fow specific peew then the MAC
 * addwess of the peew needs to be passed in %NW80211_ATTW_MAC, othewwise the
 * configuwation wiww be appwied fow aww the connected peews in the vif except
 * any peews that have peew-specific configuwation fow the TID by defauwt; if
 * the %NW80211_TID_CONFIG_ATTW_OVEWWIDE fwag is set, peew-specific vawues
 * wiww be ovewwwitten.
 *
 * Aww this configuwation is vawid onwy fow STA's cuwwent connection,
 * i.e., the configuwation wiww be weset to defauwt when the STA connects back
 * aftew disconnection/woaming, and this configuwation wiww be cweawed when
 * the intewface goes down.
 */

/**
 * DOC: FIWS shawed key cwypto offwoad
 *
 * This featuwe is appwicabwe to dwivews wunning in AP mode.
 *
 * FIWS shawed key cwypto offwoad can be advewtised by dwivews by setting
 * @NW80211_EXT_FEATUWE_FIWS_CWYPTO_OFFWOAD fwag. The dwivews that suppowt
 * FIWS shawed key cwypto offwoad shouwd be abwe to encwypt and decwypt
 * association fwames fow FIWS shawed key authentication as pew IEEE 802.11ai.
 * With this capabiwity, fow FIWS key dewivation, dwivews depend on usewspace.
 *
 * Aftew FIWS key dewivation, usewspace shawes the FIWS AAD detaiws with the
 * dwivew and the dwivew stowes the same to use in decwyption of association
 * wequest and in encwyption of association wesponse. The bewow pawametews
 * shouwd be given to the dwivew in %NW80211_CMD_SET_FIWS_AAD.
 *	%NW80211_ATTW_MAC - STA MAC addwess, used fow stowing FIWS AAD pew STA
 *	%NW80211_ATTW_FIWS_KEK - Used fow encwyption ow decwyption
 *	%NW80211_ATTW_FIWS_NONCES - Used fow encwyption ow decwyption
 *			(STA Nonce 16 bytes fowwowed by AP Nonce 16 bytes)
 *
 * Once the association is done, the dwivew cweans the FIWS AAD data.
 */

/**
 * DOC: Muwti-Wink Opewation
 *
 * In Muwti-Wink Opewation, a connection between two MWDs utiwizes muwtipwe
 * winks. To use this in nw80211, vawious commands and wesponses now need
 * to ow wiww incwude the new %NW80211_ATTW_MWO_WINKS attwibute.
 * Additionawwy, vawious commands that need to opewate on a specific wink
 * now need to be given the %NW80211_ATTW_MWO_WINK_ID attwibute, e.g. to
 * use %NW80211_CMD_STAWT_AP ow simiwaw functions.
 */

/**
 * DOC: OWE DH IE handwing offwoad
 *
 * By setting @NW80211_EXT_FEATUWE_OWE_OFFWOAD fwag, dwivews can indicate
 * kewnew/appwication space to avoid DH IE handwing. When this fwag is
 * advewtised, the dwivew/device wiww take cawe of DH IE incwusion and
 * pwocessing of peew DH IE to genewate PMK.
 */

/**
 * enum nw80211_commands - suppowted nw80211 commands
 *
 * @NW80211_CMD_UNSPEC: unspecified command to catch ewwows
 *
 * @NW80211_CMD_GET_WIPHY: wequest infowmation about a wiphy ow dump wequest
 *	to get a wist of aww pwesent wiphys.
 * @NW80211_CMD_SET_WIPHY: set wiphy pawametews, needs %NW80211_ATTW_WIPHY ow
 *	%NW80211_ATTW_IFINDEX; can be used to set %NW80211_ATTW_WIPHY_NAME,
 *	%NW80211_ATTW_WIPHY_TXQ_PAWAMS, %NW80211_ATTW_WIPHY_FWEQ,
 *	%NW80211_ATTW_WIPHY_FWEQ_OFFSET (and the attwibutes detewmining the
 *	channew width; this is used fow setting monitow mode channew),
 *	%NW80211_ATTW_WIPHY_WETWY_SHOWT, %NW80211_ATTW_WIPHY_WETWY_WONG,
 *	%NW80211_ATTW_WIPHY_FWAG_THWESHOWD, and/ow
 *	%NW80211_ATTW_WIPHY_WTS_THWESHOWD.  Howevew, fow setting the channew,
 *	see %NW80211_CMD_SET_CHANNEW instead, the suppowt hewe is fow backwawd
 *	compatibiwity onwy.
 * @NW80211_CMD_NEW_WIPHY: Newwy cweated wiphy, wesponse to get wequest
 *	ow wename notification. Has attwibutes %NW80211_ATTW_WIPHY and
 *	%NW80211_ATTW_WIPHY_NAME.
 * @NW80211_CMD_DEW_WIPHY: Wiphy deweted. Has attwibutes
 *	%NW80211_ATTW_WIPHY and %NW80211_ATTW_WIPHY_NAME.
 *
 * @NW80211_CMD_GET_INTEWFACE: Wequest an intewface's configuwation;
 *	eithew a dump wequest fow aww intewfaces ow a specific get with a
 *	singwe %NW80211_ATTW_IFINDEX is suppowted.
 * @NW80211_CMD_SET_INTEWFACE: Set type of a viwtuaw intewface, wequiwes
 *	%NW80211_ATTW_IFINDEX and %NW80211_ATTW_IFTYPE.
 * @NW80211_CMD_NEW_INTEWFACE: Newwy cweated viwtuaw intewface ow wesponse
 *	to %NW80211_CMD_GET_INTEWFACE. Has %NW80211_ATTW_IFINDEX,
 *	%NW80211_ATTW_WIPHY and %NW80211_ATTW_IFTYPE attwibutes. Can awso
 *	be sent fwom usewspace to wequest cweation of a new viwtuaw intewface,
 *	then wequiwes attwibutes %NW80211_ATTW_WIPHY, %NW80211_ATTW_IFTYPE and
 *	%NW80211_ATTW_IFNAME.
 * @NW80211_CMD_DEW_INTEWFACE: Viwtuaw intewface was deweted, has attwibutes
 *	%NW80211_ATTW_IFINDEX and %NW80211_ATTW_WIPHY. Can awso be sent fwom
 *	usewspace to wequest dewetion of a viwtuaw intewface, then wequiwes
 *	attwibute %NW80211_ATTW_IFINDEX. If muwtipwe BSSID advewtisements awe
 *	enabwed using %NW80211_ATTW_MBSSID_CONFIG, %NW80211_ATTW_MBSSID_EWEMS,
 *	and if this command is used fow the twansmitting intewface, then aww
 *	the non-twansmitting intewfaces awe deweted as weww.
 *
 * @NW80211_CMD_GET_KEY: Get sequence countew infowmation fow a key specified
 *	by %NW80211_ATTW_KEY_IDX and/ow %NW80211_ATTW_MAC. %NW80211_ATTW_MAC
 *	wepwesents peew's MWD addwess fow MWO paiwwise key. Fow MWO gwoup key,
 *	the wink is identified by %NW80211_ATTW_MWO_WINK_ID.
 * @NW80211_CMD_SET_KEY: Set key attwibutes %NW80211_ATTW_KEY_DEFAUWT,
 *	%NW80211_ATTW_KEY_DEFAUWT_MGMT, ow %NW80211_ATTW_KEY_THWESHOWD.
 *	Fow MWO connection, the wink to set defauwt key is identified by
 *	%NW80211_ATTW_MWO_WINK_ID.
 * @NW80211_CMD_NEW_KEY: add a key with given %NW80211_ATTW_KEY_DATA,
 *	%NW80211_ATTW_KEY_IDX, %NW80211_ATTW_MAC, %NW80211_ATTW_KEY_CIPHEW,
 *	and %NW80211_ATTW_KEY_SEQ attwibutes. %NW80211_ATTW_MAC wepwesents
 *	peew's MWD addwess fow MWO paiwwise key. The wink to add MWO
 *	gwoup key is identified by %NW80211_ATTW_MWO_WINK_ID.
 * @NW80211_CMD_DEW_KEY: dewete a key identified by %NW80211_ATTW_KEY_IDX
 *	ow %NW80211_ATTW_MAC. %NW80211_ATTW_MAC wepwesents peew's MWD addwess
 *	fow MWO paiwwise key. The wink to dewete gwoup key is identified by
 *	%NW80211_ATTW_MWO_WINK_ID.
 *
 * @NW80211_CMD_GET_BEACON: (not used)
 * @NW80211_CMD_SET_BEACON: change the beacon on an access point intewface
 *	using the %NW80211_ATTW_BEACON_HEAD and %NW80211_ATTW_BEACON_TAIW
 *	attwibutes. Fow dwivews that genewate the beacon and pwobe wesponses
 *	intewnawwy, the fowwowing attwibutes must be pwovided: %NW80211_ATTW_IE,
 *	%NW80211_ATTW_IE_PWOBE_WESP and %NW80211_ATTW_IE_ASSOC_WESP.
 * @NW80211_CMD_STAWT_AP: Stawt AP opewation on an AP intewface, pawametews
 *	awe wike fow %NW80211_CMD_SET_BEACON, and additionawwy pawametews that
 *	do not change awe used, these incwude %NW80211_ATTW_BEACON_INTEWVAW,
 *	%NW80211_ATTW_DTIM_PEWIOD, %NW80211_ATTW_SSID,
 *	%NW80211_ATTW_HIDDEN_SSID, %NW80211_ATTW_CIPHEWS_PAIWWISE,
 *	%NW80211_ATTW_CIPHEW_GWOUP, %NW80211_ATTW_WPA_VEWSIONS,
 *	%NW80211_ATTW_AKM_SUITES, %NW80211_ATTW_PWIVACY,
 *	%NW80211_ATTW_AUTH_TYPE, %NW80211_ATTW_INACTIVITY_TIMEOUT,
 *	%NW80211_ATTW_ACW_POWICY and %NW80211_ATTW_MAC_ADDWS.
 *	The channew to use can be set on the intewface ow be given using the
 *	%NW80211_ATTW_WIPHY_FWEQ and %NW80211_ATTW_WIPHY_FWEQ_OFFSET, and the
 *	attwibutes detewmining channew width.
 * @NW80211_CMD_NEW_BEACON: owd awias fow %NW80211_CMD_STAWT_AP
 * @NW80211_CMD_STOP_AP: Stop AP opewation on the given intewface
 * @NW80211_CMD_DEW_BEACON: owd awias fow %NW80211_CMD_STOP_AP
 *
 * @NW80211_CMD_GET_STATION: Get station attwibutes fow station identified by
 *	%NW80211_ATTW_MAC on the intewface identified by %NW80211_ATTW_IFINDEX.
 * @NW80211_CMD_SET_STATION: Set station attwibutes fow station identified by
 *	%NW80211_ATTW_MAC on the intewface identified by %NW80211_ATTW_IFINDEX.
 * @NW80211_CMD_NEW_STATION: Add a station with given attwibutes to the
 *	intewface identified by %NW80211_ATTW_IFINDEX.
 * @NW80211_CMD_DEW_STATION: Wemove a station identified by %NW80211_ATTW_MAC
 *	ow, if no MAC addwess given, aww stations, on the intewface identified
 *	by %NW80211_ATTW_IFINDEX. Fow MWD station, MWD addwess is used in
 *	%NW80211_ATTW_MAC. %NW80211_ATTW_MGMT_SUBTYPE and
 *	%NW80211_ATTW_WEASON_CODE can optionawwy be used to specify which type
 *	of disconnection indication shouwd be sent to the station
 *	(Deauthentication ow Disassociation fwame and weason code fow that
 *	fwame).
 *
 * @NW80211_CMD_GET_MPATH: Get mesh path attwibutes fow mesh path to
 * 	destination %NW80211_ATTW_MAC on the intewface identified by
 * 	%NW80211_ATTW_IFINDEX.
 * @NW80211_CMD_SET_MPATH:  Set mesh path attwibutes fow mesh path to
 * 	destination %NW80211_ATTW_MAC on the intewface identified by
 * 	%NW80211_ATTW_IFINDEX.
 * @NW80211_CMD_NEW_MPATH: Cweate a new mesh path fow the destination given by
 *	%NW80211_ATTW_MAC via %NW80211_ATTW_MPATH_NEXT_HOP.
 * @NW80211_CMD_DEW_MPATH: Dewete a mesh path to the destination given by
 *	%NW80211_ATTW_MAC.
 * @NW80211_CMD_NEW_PATH: Add a mesh path with given attwibutes to the
 *	intewface identified by %NW80211_ATTW_IFINDEX.
 * @NW80211_CMD_DEW_PATH: Wemove a mesh path identified by %NW80211_ATTW_MAC
 *	ow, if no MAC addwess given, aww mesh paths, on the intewface identified
 *	by %NW80211_ATTW_IFINDEX.
 * @NW80211_CMD_SET_BSS: Set BSS attwibutes fow BSS identified by
 *	%NW80211_ATTW_IFINDEX.
 *
 * @NW80211_CMD_GET_WEG: ask the wiwewess cowe to send us its cuwwentwy set
 *	weguwatowy domain. If %NW80211_ATTW_WIPHY is specified and the device
 *	has a pwivate weguwatowy domain, it wiww be wetuwned. Othewwise, the
 *	gwobaw wegdomain wiww be wetuwned.
 *	A device wiww have a pwivate weguwatowy domain if it uses the
 *	weguwatowy_hint() API. Even when a pwivate wegdomain is used the channew
 *	infowmation wiww stiww be mended accowding to fuwthew hints fwom
 *	the weguwatowy cowe to hewp with compwiance. A dump vewsion of this API
 *	is now avaiwabwe which wiww wetuwns the gwobaw wegdomain as weww as
 *	aww pwivate wegdomains of pwesent wiphys (fow those that have it).
 *	If a wiphy is sewf-managed (%NW80211_ATTW_WIPHY_SEWF_MANAGED_WEG), then
 *	its pwivate wegdomain is the onwy vawid one fow it. The weguwatowy
 *	cowe is not used to hewp with compwiance in this case.
 * @NW80211_CMD_SET_WEG: Set cuwwent weguwatowy domain. CWDA sends this command
 *	aftew being quewied by the kewnew. CWDA wepwies by sending a weguwatowy
 *	domain stwuctuwe which consists of %NW80211_ATTW_WEG_AWPHA set to ouw
 *	cuwwent awpha2 if it found a match. It awso pwovides
 * 	NW80211_ATTW_WEG_WUWE_FWAGS, and a set of weguwatowy wuwes. Each
 * 	weguwatowy wuwe is a nested set of attwibutes  given by
 * 	%NW80211_ATTW_WEG_WUWE_FWEQ_[STAWT|END] and
 * 	%NW80211_ATTW_FWEQ_WANGE_MAX_BW with an attached powew wuwe given by
 * 	%NW80211_ATTW_WEG_WUWE_POWEW_MAX_ANT_GAIN and
 * 	%NW80211_ATTW_WEG_WUWE_POWEW_MAX_EIWP.
 * @NW80211_CMD_WEQ_SET_WEG: ask the wiwewess cowe to set the weguwatowy domain
 * 	to the specified ISO/IEC 3166-1 awpha2 countwy code. The cowe wiww
 * 	stowe this as a vawid wequest and then quewy usewspace fow it.
 *
 * @NW80211_CMD_GET_MESH_CONFIG: Get mesh netwowking pwopewties fow the
 *	intewface identified by %NW80211_ATTW_IFINDEX
 *
 * @NW80211_CMD_SET_MESH_CONFIG: Set mesh netwowking pwopewties fow the
 *      intewface identified by %NW80211_ATTW_IFINDEX
 *
 * @NW80211_CMD_SET_MGMT_EXTWA_IE: Set extwa IEs fow management fwames. The
 *	intewface is identified with %NW80211_ATTW_IFINDEX and the management
 *	fwame subtype with %NW80211_ATTW_MGMT_SUBTYPE. The extwa IE data to be
 *	added to the end of the specified management fwame is specified with
 *	%NW80211_ATTW_IE. If the command succeeds, the wequested data wiww be
 *	added to aww specified management fwames genewated by
 *	kewnew/fiwmwawe/dwivew.
 *	Note: This command has been wemoved and it is onwy wesewved at this
 *	point to avoid we-using existing command numbew. The functionawity this
 *	command was pwanned fow has been pwovided with cweanew design with the
 *	option to specify additionaw IEs in NW80211_CMD_TWIGGEW_SCAN,
 *	NW80211_CMD_AUTHENTICATE, NW80211_CMD_ASSOCIATE,
 *	NW80211_CMD_DEAUTHENTICATE, and NW80211_CMD_DISASSOCIATE.
 *
 * @NW80211_CMD_GET_SCAN: get scan wesuwts
 * @NW80211_CMD_TWIGGEW_SCAN: twiggew a new scan with the given pawametews
 *	%NW80211_ATTW_TX_NO_CCK_WATE is used to decide whethew to send the
 *	pwobe wequests at CCK wate ow not. %NW80211_ATTW_BSSID can be used to
 *	specify a BSSID to scan fow; if not incwuded, the wiwdcawd BSSID wiww
 *	be used.
 * @NW80211_CMD_NEW_SCAN_WESUWTS: scan notification (as a wepwy to
 *	NW80211_CMD_GET_SCAN and on the "scan" muwticast gwoup)
 * @NW80211_CMD_SCAN_ABOWTED: scan was abowted, fow unspecified weasons,
 *	pawtiaw scan wesuwts may be avaiwabwe
 *
 * @NW80211_CMD_STAWT_SCHED_SCAN: stawt a scheduwed scan at cewtain
 *	intewvaws and cewtain numbew of cycwes, as specified by
 *	%NW80211_ATTW_SCHED_SCAN_PWANS. If %NW80211_ATTW_SCHED_SCAN_PWANS is
 *	not specified and onwy %NW80211_ATTW_SCHED_SCAN_INTEWVAW is specified,
 *	scheduwed scan wiww wun in an infinite woop with the specified intewvaw.
 *	These attwibutes awe mutuawwy excwusive,
 *	i.e. NW80211_ATTW_SCHED_SCAN_INTEWVAW must not be passed if
 *	NW80211_ATTW_SCHED_SCAN_PWANS is defined.
 *	If fow some weason scheduwed scan is abowted by the dwivew, aww scan
 *	pwans awe cancewed (incwuding scan pwans that did not stawt yet).
 *	Wike with nowmaw scans, if SSIDs (%NW80211_ATTW_SCAN_SSIDS)
 *	awe passed, they awe used in the pwobe wequests.  Fow
 *	bwoadcast, a bwoadcast SSID must be passed (ie. an empty
 *	stwing).  If no SSID is passed, no pwobe wequests awe sent and
 *	a passive scan is pewfowmed.  %NW80211_ATTW_SCAN_FWEQUENCIES,
 *	if passed, define which channews shouwd be scanned; if not
 *	passed, aww channews awwowed fow the cuwwent weguwatowy domain
 *	awe used.  Extwa IEs can awso be passed fwom the usewspace by
 *	using the %NW80211_ATTW_IE attwibute.  The fiwst cycwe of the
 *	scheduwed scan can be dewayed by %NW80211_ATTW_SCHED_SCAN_DEWAY
 *	is suppwied. If the device suppowts muwtipwe concuwwent scheduwed
 *	scans, it wiww awwow such when the cawwew pwovides the fwag attwibute
 *	%NW80211_ATTW_SCHED_SCAN_MUWTI to indicate usew-space suppowt fow it.
 * @NW80211_CMD_STOP_SCHED_SCAN: stop a scheduwed scan. Wetuwns -ENOENT if
 *	scheduwed scan is not wunning. The cawwew may assume that as soon
 *	as the caww wetuwns, it is safe to stawt a new scheduwed scan again.
 * @NW80211_CMD_SCHED_SCAN_WESUWTS: indicates that thewe awe scheduwed scan
 *	wesuwts avaiwabwe.
 * @NW80211_CMD_SCHED_SCAN_STOPPED: indicates that the scheduwed scan has
 *	stopped.  The dwivew may issue this event at any time duwing a
 *	scheduwed scan.  One weason fow stopping the scan is if the hawdwawe
 *	does not suppowt stawting an association ow a nowmaw scan whiwe wunning
 *	a scheduwed scan.  This event is awso sent when the
 *	%NW80211_CMD_STOP_SCHED_SCAN command is weceived ow when the intewface
 *	is bwought down whiwe a scheduwed scan was wunning.
 *
 * @NW80211_CMD_GET_SUWVEY: get suwvey wesuwts, e.g. channew occupation
 *      ow noise wevew
 * @NW80211_CMD_NEW_SUWVEY_WESUWTS: suwvey data notification (as a wepwy to
 *	NW80211_CMD_GET_SUWVEY and on the "scan" muwticast gwoup)
 *
 * @NW80211_CMD_SET_PMKSA: Add a PMKSA cache entwy using %NW80211_ATTW_MAC
 *	(fow the BSSID), %NW80211_ATTW_PMKID, and optionawwy %NW80211_ATTW_PMK
 *	(PMK is used fow PTKSA dewivation in case of FIWS shawed key offwoad) ow
 *	using %NW80211_ATTW_SSID, %NW80211_ATTW_FIWS_CACHE_ID,
 *	%NW80211_ATTW_PMKID, and %NW80211_ATTW_PMK in case of FIWS
 *	authentication whewe %NW80211_ATTW_FIWS_CACHE_ID is the identifiew
 *	advewtised by a FIWS capabwe AP identifying the scope of PMKSA in an
 *	ESS.
 * @NW80211_CMD_DEW_PMKSA: Dewete a PMKSA cache entwy, using %NW80211_ATTW_MAC
 *	(fow the BSSID) and %NW80211_ATTW_PMKID ow using %NW80211_ATTW_SSID,
 *	%NW80211_ATTW_FIWS_CACHE_ID, and %NW80211_ATTW_PMKID in case of FIWS
 *	authentication. Additionawwy in case of SAE offwoad and OWE offwoads
 *	PMKSA entwy can be deweted using %NW80211_ATTW_SSID.
 * @NW80211_CMD_FWUSH_PMKSA: Fwush aww PMKSA cache entwies.
 *
 * @NW80211_CMD_WEG_CHANGE: indicates to usewspace the weguwatowy domain
 * 	has been changed and pwovides detaiws of the wequest infowmation
 * 	that caused the change such as who initiated the weguwatowy wequest
 * 	(%NW80211_ATTW_WEG_INITIATOW), the wiphy_idx
 * 	(%NW80211_ATTW_WEG_AWPHA2) on which the wequest was made fwom if
 * 	the initiatow was %NW80211_WEGDOM_SET_BY_COUNTWY_IE ow
 * 	%NW80211_WEGDOM_SET_BY_DWIVEW, the type of weguwatowy domain
 * 	set (%NW80211_ATTW_WEG_TYPE), if the type of weguwatowy domain is
 * 	%NW80211_WEG_TYPE_COUNTWY the awpha2 to which we have moved on
 * 	to (%NW80211_ATTW_WEG_AWPHA2).
 * @NW80211_CMD_WEG_BEACON_HINT: indicates to usewspace that an AP beacon
 * 	has been found whiwe wowwd woaming thus enabwing active scan ow
 * 	any mode of opewation that initiates TX (beacons) on a channew
 * 	whewe we wouwd not have been abwe to do eithew befowe. As an exampwe
 * 	if you awe wowwd woaming (weguwatowy domain set to wowwd ow if youw
 * 	dwivew is using a custom wowwd woaming weguwatowy domain) and whiwe
 * 	doing a passive scan on the 5 GHz band you find an AP thewe (if not
 * 	on a DFS channew) you wiww now be abwe to activewy scan fow that AP
 * 	ow use AP mode on youw cawd on that same channew. Note that this wiww
 * 	nevew be used fow channews 1-11 on the 2 GHz band as they awe awways
 * 	enabwed wowwd wide. This beacon hint is onwy sent if youw device had
 * 	eithew disabwed active scanning ow beaconing on a channew. We send to
 * 	usewspace the wiphy on which we wemoved a westwiction fwom
 * 	(%NW80211_ATTW_WIPHY) and the channew on which this occuwwed
 * 	befowe (%NW80211_ATTW_FWEQ_BEFOWE) and aftew (%NW80211_ATTW_FWEQ_AFTEW)
 * 	the beacon hint was pwocessed.
 *
 * @NW80211_CMD_AUTHENTICATE: authentication wequest and notification.
 *	This command is used both as a command (wequest to authenticate) and
 *	as an event on the "mwme" muwticast gwoup indicating compwetion of the
 *	authentication pwocess.
 *	When used as a command, %NW80211_ATTW_IFINDEX is used to identify the
 *	intewface. %NW80211_ATTW_MAC is used to specify PeewSTAAddwess (and
 *	BSSID in case of station mode). %NW80211_ATTW_SSID is used to specify
 *	the SSID (mainwy fow association, but is incwuded in authentication
 *	wequest, too, to hewp BSS sewection. %NW80211_ATTW_WIPHY_FWEQ +
 *	%NW80211_ATTW_WIPHY_FWEQ_OFFSET is used to specify the fwequency of the
 *	channew in MHz. %NW80211_ATTW_AUTH_TYPE is used to specify the
 *	authentication type. %NW80211_ATTW_IE is used to define IEs
 *	(VendowSpecificInfo, but awso incwuding WSN IE and FT IEs) to be added
 *	to the fwame.
 *	When used as an event, this wepowts weception of an Authentication
 *	fwame in station and IBSS modes when the wocaw MWME pwocessed the
 *	fwame, i.e., it was fow the wocaw STA and was weceived in cowwect
 *	state. This is simiwaw to MWME-AUTHENTICATE.confiwm pwimitive in the
 *	MWME SAP intewface (kewnew pwoviding MWME, usewspace SME). The
 *	incwuded %NW80211_ATTW_FWAME attwibute contains the management fwame
 *	(incwuding both the headew and fwame body, but not FCS). This event is
 *	awso used to indicate if the authentication attempt timed out. In that
 *	case the %NW80211_ATTW_FWAME attwibute is wepwaced with a
 *	%NW80211_ATTW_TIMED_OUT fwag (and %NW80211_ATTW_MAC to indicate which
 *	pending authentication timed out).
 * @NW80211_CMD_ASSOCIATE: association wequest and notification; wike
 *	NW80211_CMD_AUTHENTICATE but fow Association and Weassociation
 *	(simiwaw to MWME-ASSOCIATE.wequest, MWME-WEASSOCIATE.wequest,
 *	MWME-ASSOCIATE.confiwm ow MWME-WEASSOCIATE.confiwm pwimitives). The
 *	%NW80211_ATTW_PWEV_BSSID attwibute is used to specify whethew the
 *	wequest is fow the initiaw association to an ESS (that attwibute not
 *	incwuded) ow fow weassociation within the ESS (that attwibute is
 *	incwuded).
 * @NW80211_CMD_DEAUTHENTICATE: deauthentication wequest and notification; wike
 *	NW80211_CMD_AUTHENTICATE but fow Deauthentication fwames (simiwaw to
 *	MWME-DEAUTHENTICATION.wequest and MWME-DEAUTHENTICATE.indication
 *	pwimitives).
 * @NW80211_CMD_DISASSOCIATE: disassociation wequest and notification; wike
 *	NW80211_CMD_AUTHENTICATE but fow Disassociation fwames (simiwaw to
 *	MWME-DISASSOCIATE.wequest and MWME-DISASSOCIATE.indication pwimitives).
 *
 * @NW80211_CMD_MICHAEW_MIC_FAIWUWE: notification of a wocawwy detected Michaew
 *	MIC (pawt of TKIP) faiwuwe; sent on the "mwme" muwticast gwoup; the
 *	event incwudes %NW80211_ATTW_MAC to descwibe the souwce MAC addwess of
 *	the fwame with invawid MIC, %NW80211_ATTW_KEY_TYPE to show the key
 *	type, %NW80211_ATTW_KEY_IDX to indicate the key identifiew, and
 *	%NW80211_ATTW_KEY_SEQ to indicate the TSC vawue of the fwame; this
 *	event matches with MWME-MICHAEWMICFAIWUWE.indication() pwimitive
 *
 * @NW80211_CMD_JOIN_IBSS: Join a new IBSS -- given at weast an SSID and a
 *	FWEQ attwibute (fow the initiaw fwequency if no peew can be found)
 *	and optionawwy a MAC (as BSSID) and FWEQ_FIXED attwibute if those
 *	shouwd be fixed wathew than automaticawwy detewmined. Can onwy be
 *	executed on a netwowk intewface that is UP, and fixed BSSID/FWEQ
 *	may be wejected. Anothew optionaw pawametew is the beacon intewvaw,
 *	given in the %NW80211_ATTW_BEACON_INTEWVAW attwibute, which if not
 *	given defauwts to 100 TU (102.4ms).
 * @NW80211_CMD_WEAVE_IBSS: Weave the IBSS -- no speciaw awguments, the IBSS is
 *	detewmined by the netwowk intewface.
 *
 * @NW80211_CMD_TESTMODE: testmode command, takes a wiphy (ow ifindex) attwibute
 *	to identify the device, and the TESTDATA bwob attwibute to pass thwough
 *	to the dwivew.
 *
 * @NW80211_CMD_CONNECT: connection wequest and notification; this command
 *	wequests to connect to a specified netwowk but without sepawating
 *	auth and assoc steps. Fow this, you need to specify the SSID in a
 *	%NW80211_ATTW_SSID attwibute, and can optionawwy specify the association
 *	IEs in %NW80211_ATTW_IE, %NW80211_ATTW_AUTH_TYPE,
 *	%NW80211_ATTW_USE_MFP, %NW80211_ATTW_MAC, %NW80211_ATTW_WIPHY_FWEQ,
 *	%NW80211_ATTW_WIPHY_FWEQ_OFFSET, %NW80211_ATTW_CONTWOW_POWT,
 *	%NW80211_ATTW_CONTWOW_POWT_ETHEWTYPE,
 *	%NW80211_ATTW_CONTWOW_POWT_NO_ENCWYPT,
 *	%NW80211_ATTW_CONTWOW_POWT_OVEW_NW80211, %NW80211_ATTW_MAC_HINT, and
 *	%NW80211_ATTW_WIPHY_FWEQ_HINT.
 *	If incwuded, %NW80211_ATTW_MAC and %NW80211_ATTW_WIPHY_FWEQ awe
 *	westwictions on BSS sewection, i.e., they effectivewy pwevent woaming
 *	within the ESS. %NW80211_ATTW_MAC_HINT and %NW80211_ATTW_WIPHY_FWEQ_HINT
 *	can be incwuded to pwovide a wecommendation of the initiaw BSS whiwe
 *	awwowing the dwivew to woam to othew BSSes within the ESS and awso to
 *	ignowe this wecommendation if the indicated BSS is not ideaw. Onwy one
 *	set of BSSID,fwequency pawametews is used (i.e., eithew the enfowcing
 *	%NW80211_ATTW_MAC,%NW80211_ATTW_WIPHY_FWEQ ow the wess stwict
 *	%NW80211_ATTW_MAC_HINT and %NW80211_ATTW_WIPHY_FWEQ_HINT).
 *	Dwivew shaww not modify the IEs specified thwough %NW80211_ATTW_IE if
 *	%NW80211_ATTW_MAC is incwuded. Howevew, if %NW80211_ATTW_MAC_HINT is
 *	incwuded, these IEs thwough %NW80211_ATTW_IE awe specified by the usew
 *	space based on the best possibwe BSS sewected. Thus, if the dwivew ends
 *	up sewecting a diffewent BSS, it can modify these IEs accowdingwy (e.g.
 *	usewspace asks the dwivew to pewfowm PMKSA caching with BSS1 and the
 *	dwivew ends up sewecting BSS2 with diffewent PMKSA cache entwy; WSNIE
 *	has to get updated with the apt PMKID).
 *	%NW80211_ATTW_PWEV_BSSID can be used to wequest a weassociation within
 *	the ESS in case the device is awweady associated and an association with
 *	a diffewent BSS is desiwed.
 *	Backgwound scan pewiod can optionawwy be
 *	specified in %NW80211_ATTW_BG_SCAN_PEWIOD,
 *	if not specified defauwt backgwound scan configuwation
 *	in dwivew is used and if pewiod vawue is 0, bg scan wiww be disabwed.
 *	This attwibute is ignowed if dwivew does not suppowt woam scan.
 *	It is awso sent as an event, with the BSSID and wesponse IEs when the
 *	connection is estabwished ow faiwed to be estabwished. This can be
 *	detewmined by the %NW80211_ATTW_STATUS_CODE attwibute (0 = success,
 *	non-zewo = faiwuwe). If %NW80211_ATTW_TIMED_OUT is incwuded in the
 *	event, the connection attempt faiwed due to not being abwe to initiate
 *	authentication/association ow not weceiving a wesponse fwom the AP.
 *	Non-zewo %NW80211_ATTW_STATUS_CODE vawue is indicated in that case as
 *	weww to wemain backwawds compatibwe.
 * @NW80211_CMD_WOAM: Notification indicating the cawd/dwivew woamed by itsewf.
 *	When a secuwity association was estabwished on an 802.1X netwowk using
 *	fast twansition, this event shouwd be fowwowed by an
 *	%NW80211_CMD_POWT_AUTHOWIZED event.
 *	Fowwowing a %NW80211_CMD_WOAM event usewspace can issue
 *	%NW80211_CMD_GET_SCAN in owdew to obtain the scan infowmation fow the
 *	new BSS the cawd/dwivew woamed to.
 * @NW80211_CMD_DISCONNECT: dwop a given connection; awso used to notify
 *	usewspace that a connection was dwopped by the AP ow due to othew
 *	weasons, fow this the %NW80211_ATTW_DISCONNECTED_BY_AP and
 *	%NW80211_ATTW_WEASON_CODE attwibutes awe used.
 *
 * @NW80211_CMD_SET_WIPHY_NETNS: Set a wiphy's netns. Note that aww devices
 *	associated with this wiphy must be down and wiww fowwow.
 *
 * @NW80211_CMD_WEMAIN_ON_CHANNEW: Wequest to wemain awake on the specified
 *	channew fow the specified amount of time. This can be used to do
 *	off-channew opewations wike twansmit a Pubwic Action fwame and wait fow
 *	a wesponse whiwe being associated to an AP on anothew channew.
 *	%NW80211_ATTW_IFINDEX is used to specify which intewface (and thus
 *	wadio) is used. %NW80211_ATTW_WIPHY_FWEQ is used to specify the
 *	fwequency fow the opewation.
 *	%NW80211_ATTW_DUWATION is used to specify the duwation in miwwiseconds
 *	to wemain on the channew. This command is awso used as an event to
 *	notify when the wequested duwation stawts (it may take a whiwe fow the
 *	dwivew to scheduwe this time due to othew concuwwent needs fow the
 *	wadio).
 *	When cawwed, this opewation wetuwns a cookie (%NW80211_ATTW_COOKIE)
 *	that wiww be incwuded with any events pewtaining to this wequest;
 *	the cookie is awso used to cancew the wequest.
 * @NW80211_CMD_CANCEW_WEMAIN_ON_CHANNEW: This command can be used to cancew a
 *	pending wemain-on-channew duwation if the desiwed opewation has been
 *	compweted pwiow to expiwation of the owiginawwy wequested duwation.
 *	%NW80211_ATTW_WIPHY ow %NW80211_ATTW_IFINDEX is used to specify the
 *	wadio. The %NW80211_ATTW_COOKIE attwibute must be given as weww to
 *	uniquewy identify the wequest.
 *	This command is awso used as an event to notify when a wequested
 *	wemain-on-channew duwation has expiwed.
 *
 * @NW80211_CMD_SET_TX_BITWATE_MASK: Set the mask of wates to be used in TX
 *	wate sewection. %NW80211_ATTW_IFINDEX is used to specify the intewface
 *	and @NW80211_ATTW_TX_WATES the set of awwowed wates.
 *
 * @NW80211_CMD_WEGISTEW_FWAME: Wegistew fow weceiving cewtain mgmt fwames
 *	(via @NW80211_CMD_FWAME) fow pwocessing in usewspace. This command
 *	wequiwes an intewface index, a fwame type attwibute (optionaw fow
 *	backwawd compatibiwity weasons, if not given assumes action fwames)
 *	and a match attwibute containing the fiwst few bytes of the fwame
 *	that shouwd match, e.g. a singwe byte fow onwy a categowy match ow
 *	fouw bytes fow vendow fwames incwuding the OUI. The wegistwation
 *	cannot be dwopped, but is wemoved automaticawwy when the netwink
 *	socket is cwosed. Muwtipwe wegistwations can be made.
 *	The %NW80211_ATTW_WECEIVE_MUWTICAST fwag attwibute can be given if
 *	%NW80211_EXT_FEATUWE_MUWTICAST_WEGISTWATIONS is avaiwabwe, in which
 *	case the wegistwation can awso be modified to incwude/excwude the
 *	fwag, wathew than wequiwing unwegistwation to change it.
 * @NW80211_CMD_WEGISTEW_ACTION: Awias fow @NW80211_CMD_WEGISTEW_FWAME fow
 *	backwawd compatibiwity
 * @NW80211_CMD_FWAME: Management fwame TX wequest and WX notification. This
 *	command is used both as a wequest to twansmit a management fwame and
 *	as an event indicating weception of a fwame that was not pwocessed in
 *	kewnew code, but is fow us (i.e., which may need to be pwocessed in a
 *	usew space appwication). %NW80211_ATTW_FWAME is used to specify the
 *	fwame contents (incwuding headew). %NW80211_ATTW_WIPHY_FWEQ is used
 *	to indicate on which channew the fwame is to be twansmitted ow was
 *	weceived. If this channew is not the cuwwent channew (wemain-on-channew
 *	ow the opewationaw channew) the device wiww switch to the given channew
 *	and twansmit the fwame, optionawwy waiting fow a wesponse fow the time
 *	specified using %NW80211_ATTW_DUWATION. When cawwed, this opewation
 *	wetuwns a cookie (%NW80211_ATTW_COOKIE) that wiww be incwuded with the
 *	TX status event pewtaining to the TX wequest.
 *	%NW80211_ATTW_TX_NO_CCK_WATE is used to decide whethew to send the
 *	management fwames at CCK wate ow not in 2GHz band.
 *	%NW80211_ATTW_CSA_C_OFFSETS_TX is an awway of offsets to CSA
 *	countews which wiww be updated to the cuwwent vawue. This attwibute
 *	is used duwing CSA pewiod.
 *	Fow TX on an MWD, the fwequency can be omitted and the wink ID be
 *	specified, ow if twansmitting to a known peew MWD (with MWD addwesses
 *	in the fwame) both can be omitted and the wink wiww be sewected by
 *	wowew wayews.
 *	Fow WX notification, %NW80211_ATTW_WX_HW_TIMESTAMP may be incwuded to
 *	indicate the fwame WX timestamp and %NW80211_ATTW_TX_HW_TIMESTAMP may
 *	be incwuded to indicate the ack TX timestamp.
 * @NW80211_CMD_FWAME_WAIT_CANCEW: When an off-channew TX was wequested, this
 *	command may be used with the cowwesponding cookie to cancew the wait
 *	time if it is known that it is no wongew necessawy.  This command is
 *	awso sent as an event whenevew the dwivew has compweted the off-channew
 *	wait time.
 * @NW80211_CMD_ACTION: Awias fow @NW80211_CMD_FWAME fow backwawd compatibiwity.
 * @NW80211_CMD_FWAME_TX_STATUS: Wepowt TX status of a management fwame
 *	twansmitted with %NW80211_CMD_FWAME. %NW80211_ATTW_COOKIE identifies
 *	the TX command and %NW80211_ATTW_FWAME incwudes the contents of the
 *	fwame. %NW80211_ATTW_ACK fwag is incwuded if the wecipient acknowwedged
 *	the fwame. %NW80211_ATTW_TX_HW_TIMESTAMP may be incwuded to indicate the
 *	tx timestamp and %NW80211_ATTW_WX_HW_TIMESTAMP may be incwuded to
 *	indicate the ack WX timestamp.
 * @NW80211_CMD_ACTION_TX_STATUS: Awias fow @NW80211_CMD_FWAME_TX_STATUS fow
 *	backwawd compatibiwity.
 *
 * @NW80211_CMD_SET_POWEW_SAVE: Set powewsave, using %NW80211_ATTW_PS_STATE
 * @NW80211_CMD_GET_POWEW_SAVE: Get powewsave status in %NW80211_ATTW_PS_STATE
 *
 * @NW80211_CMD_SET_CQM: Connection quawity monitow configuwation. This command
 *	is used to configuwe connection quawity monitowing notification twiggew
 *	wevews.
 * @NW80211_CMD_NOTIFY_CQM: Connection quawity monitow notification. This
 *	command is used as an event to indicate the that a twiggew wevew was
 *	weached.
 * @NW80211_CMD_SET_CHANNEW: Set the channew (using %NW80211_ATTW_WIPHY_FWEQ
 *	and the attwibutes detewmining channew width) the given intewface
 *	(identified by %NW80211_ATTW_IFINDEX) shaww opewate on.
 *	In case muwtipwe channews awe suppowted by the device, the mechanism
 *	with which it switches channews is impwementation-defined.
 *	When a monitow intewface is given, it can onwy switch channew whiwe
 *	no othew intewfaces awe opewating to avoid distuwbing the opewation
 *	of any othew intewfaces, and othew intewfaces wiww again take
 *	pwecedence when they awe used.
 *
 * @NW80211_CMD_SET_WDS_PEEW: Set the MAC addwess of the peew on a WDS intewface
 *	(no wongew suppowted).
 *
 * @NW80211_CMD_SET_MUWTICAST_TO_UNICAST: Configuwe if this AP shouwd pewfowm
 *	muwticast to unicast convewsion. When enabwed, aww muwticast packets
 *	with ethewtype AWP, IPv4 ow IPv6 (possibwy within an 802.1Q headew)
 *	wiww be sent out to each station once with the destination (muwticast)
 *	MAC addwess wepwaced by the station's MAC addwess. Note that this may
 *	bweak cewtain expectations of the weceivew, e.g. the abiwity to dwop
 *	unicast IP packets encapsuwated in muwticast W2 fwames, ow the abiwity
 *	to not send destination unweachabwe messages in such cases.
 *	This can onwy be toggwed pew BSS. Configuwe this on an intewface of
 *	type %NW80211_IFTYPE_AP. It appwies to aww its VWAN intewfaces
 *	(%NW80211_IFTYPE_AP_VWAN), except fow those in 4addw (WDS) mode.
 *	If %NW80211_ATTW_MUWTICAST_TO_UNICAST_ENABWED is not pwesent with this
 *	command, the featuwe is disabwed.
 *
 * @NW80211_CMD_JOIN_MESH: Join a mesh. The mesh ID must be given, and initiaw
 *	mesh config pawametews may be given.
 * @NW80211_CMD_WEAVE_MESH: Weave the mesh netwowk -- no speciaw awguments, the
 *	netwowk is detewmined by the netwowk intewface.
 *
 * @NW80211_CMD_UNPWOT_DEAUTHENTICATE: Unpwotected deauthentication fwame
 *	notification. This event is used to indicate that an unpwotected
 *	deauthentication fwame was dwopped when MFP is in use.
 * @NW80211_CMD_UNPWOT_DISASSOCIATE: Unpwotected disassociation fwame
 *	notification. This event is used to indicate that an unpwotected
 *	disassociation fwame was dwopped when MFP is in use.
 *
 * @NW80211_CMD_NEW_PEEW_CANDIDATE: Notification on the weception of a
 *      beacon ow pwobe wesponse fwom a compatibwe mesh peew.  This is onwy
 *      sent whiwe no station infowmation (sta_info) exists fow the new peew
 *      candidate and when @NW80211_MESH_SETUP_USEWSPACE_AUTH,
 *      @NW80211_MESH_SETUP_USEWSPACE_AMPE, ow
 *      @NW80211_MESH_SETUP_USEWSPACE_MPM is set.  On weception of this
 *      notification, usewspace may decide to cweate a new station
 *      (@NW80211_CMD_NEW_STATION).  To stop this notification fwom
 *      weoccuwwing, the usewspace authentication daemon may want to cweate the
 *      new station with the AUTHENTICATED fwag unset and maybe change it watew
 *      depending on the authentication wesuwt.
 *
 * @NW80211_CMD_GET_WOWWAN: get Wake-on-Wiwewess-WAN (WoWWAN) settings.
 * @NW80211_CMD_SET_WOWWAN: set Wake-on-Wiwewess-WAN (WoWWAN) settings.
 *	Since wiwewess is mowe compwex than wiwed ethewnet, it suppowts
 *	vawious twiggews. These twiggews can be configuwed thwough this
 *	command with the %NW80211_ATTW_WOWWAN_TWIGGEWS attwibute. Fow
 *	mowe backgwound infowmation, see
 *	https://wiwewess.wiki.kewnew.owg/en/usews/Documentation/WoWWAN.
 *	The @NW80211_CMD_SET_WOWWAN command can awso be used as a notification
 *	fwom the dwivew wepowting the wakeup weason. In this case, the
 *	@NW80211_ATTW_WOWWAN_TWIGGEWS attwibute wiww contain the weason
 *	fow the wakeup, if it was caused by wiwewess. If it is not pwesent
 *	in the wakeup notification, the wiwewess device didn't cause the
 *	wakeup but wepowts that it was woken up.
 *
 * @NW80211_CMD_SET_WEKEY_OFFWOAD: This command is used give the dwivew
 *	the necessawy infowmation fow suppowting GTK wekey offwoad. This
 *	featuwe is typicawwy used duwing WoWWAN. The configuwation data
 *	is contained in %NW80211_ATTW_WEKEY_DATA (which is nested and
 *	contains the data in sub-attwibutes). Aftew wekeying happened,
 *	this command may awso be sent by the dwivew as an MWME event to
 *	infowm usewspace of the new wepway countew.
 *
 * @NW80211_CMD_PMKSA_CANDIDATE: This is used as an event to infowm usewspace
 *	of PMKSA caching candidates.
 *
 * @NW80211_CMD_TDWS_OPEW: Pewfowm a high-wevew TDWS command (e.g. wink setup).
 *	In addition, this can be used as an event to wequest usewspace to take
 *	actions on TDWS winks (set up a new wink ow teaw down an existing one).
 *	In such events, %NW80211_ATTW_TDWS_OPEWATION indicates the wequested
 *	opewation, %NW80211_ATTW_MAC contains the peew MAC addwess, and
 *	%NW80211_ATTW_WEASON_CODE the weason code to be used (onwy with
 *	%NW80211_TDWS_TEAWDOWN).
 * @NW80211_CMD_TDWS_MGMT: Send a TDWS management fwame. The
 *	%NW80211_ATTW_TDWS_ACTION attwibute detewmines the type of fwame to be
 *	sent. Pubwic Action codes (802.11-2012 8.1.5.1) wiww be sent as
 *	802.11 management fwames, whiwe TDWS action codes (802.11-2012
 *	8.5.13.1) wiww be encapsuwated and sent as data fwames. The cuwwentwy
 *	suppowted Pubwic Action code is %WWAN_PUB_ACTION_TDWS_DISCOVEW_WES
 *	and the cuwwentwy suppowted TDWS actions codes awe given in
 *	&enum ieee80211_tdws_actioncode.
 *
 * @NW80211_CMD_UNEXPECTED_FWAME: Used by an appwication contwowwing an AP
 *	(ow GO) intewface (i.e. hostapd) to ask fow unexpected fwames to
 *	impwement sending deauth to stations that send unexpected cwass 3
 *	fwames. Awso used as the event sent by the kewnew when such a fwame
 *	is weceived.
 *	Fow the event, the %NW80211_ATTW_MAC attwibute cawwies the TA and
 *	othew attwibutes wike the intewface index awe pwesent.
 *	If used as the command it must have an intewface index and you can
 *	onwy unsubscwibe fwom the event by cwosing the socket. Subscwiption
 *	is awso fow %NW80211_CMD_UNEXPECTED_4ADDW_FWAME events.
 *
 * @NW80211_CMD_UNEXPECTED_4ADDW_FWAME: Sent as an event indicating that the
 *	associated station identified by %NW80211_ATTW_MAC sent a 4addw fwame
 *	and wasn't awweady in a 4-addw VWAN. The event wiww be sent simiwawwy
 *	to the %NW80211_CMD_UNEXPECTED_FWAME event, to the same wistenew.
 *
 * @NW80211_CMD_PWOBE_CWIENT: Pwobe an associated station on an AP intewface
 *	by sending a nuww data fwame to it and wepowting when the fwame is
 *	acknowwedged. This is used to awwow timing out inactive cwients. Uses
 *	%NW80211_ATTW_IFINDEX and %NW80211_ATTW_MAC. The command wetuwns a
 *	diwect wepwy with an %NW80211_ATTW_COOKIE that is watew used to match
 *	up the event with the wequest. The event incwudes the same data and
 *	has %NW80211_ATTW_ACK set if the fwame was ACKed.
 *
 * @NW80211_CMD_WEGISTEW_BEACONS: Wegistew this socket to weceive beacons fwom
 *	othew BSSes when any intewfaces awe in AP mode. This hewps impwement
 *	OWBC handwing in hostapd. Beacons awe wepowted in %NW80211_CMD_FWAME
 *	messages. Note that pew PHY onwy one appwication may wegistew.
 *
 * @NW80211_CMD_SET_NOACK_MAP: sets a bitmap fow the individuaw TIDs whethew
 *      No Acknowwedgement Powicy shouwd be appwied.
 *
 * @NW80211_CMD_CH_SWITCH_NOTIFY: An AP ow GO may decide to switch channews
 *	independentwy of the usewspace SME, send this event indicating
 *	%NW80211_ATTW_IFINDEX is now on %NW80211_ATTW_WIPHY_FWEQ and the
 *	attwibutes detewmining channew width.  This indication may awso be
 *	sent when a wemotewy-initiated switch (e.g., when a STA weceives a CSA
 *	fwom the wemote AP) is compweted;
 *
 * @NW80211_CMD_CH_SWITCH_STAWTED_NOTIFY: Notify that a channew switch
 *	has been stawted on an intewface, wegawdwess of the initiatow
 *	(ie. whethew it was wequested fwom a wemote device ow
 *	initiated on ouw own).  It indicates that
 *	%NW80211_ATTW_IFINDEX wiww be on %NW80211_ATTW_WIPHY_FWEQ
 *	aftew %NW80211_ATTW_CH_SWITCH_COUNT TBTT's.  The usewspace may
 *	decide to weact to this indication by wequesting othew
 *	intewfaces to change channew as weww.
 *
 * @NW80211_CMD_STAWT_P2P_DEVICE: Stawt the given P2P Device, identified by
 *	its %NW80211_ATTW_WDEV identifiew. It must have been cweated with
 *	%NW80211_CMD_NEW_INTEWFACE pweviouswy. Aftew it has been stawted, the
 *	P2P Device can be used fow P2P opewations, e.g. wemain-on-channew and
 *	pubwic action fwame TX.
 * @NW80211_CMD_STOP_P2P_DEVICE: Stop the given P2P Device, identified by
 *	its %NW80211_ATTW_WDEV identifiew.
 *
 * @NW80211_CMD_CONN_FAIWED: connection wequest to an AP faiwed; used to
 *	notify usewspace that AP has wejected the connection wequest fwom a
 *	station, due to pawticuwaw weason. %NW80211_ATTW_CONN_FAIWED_WEASON
 *	is used fow this.
 *
 * @NW80211_CMD_SET_MCAST_WATE: Change the wate used to send muwticast fwames
 *	fow IBSS ow MESH vif.
 *
 * @NW80211_CMD_SET_MAC_ACW: sets ACW fow MAC addwess based access contwow.
 *	This is to be used with the dwivews advewtising the suppowt of MAC
 *	addwess based access contwow. Wist of MAC addwesses is passed in
 *	%NW80211_ATTW_MAC_ADDWS and ACW powicy is passed in
 *	%NW80211_ATTW_ACW_POWICY. Dwivew wiww enabwe ACW with this wist, if it
 *	is not awweady done. The new wist wiww wepwace any existing wist. Dwivew
 *	wiww cweaw its ACW when the wist of MAC addwesses passed is empty. This
 *	command is used in AP/P2P GO mode. Dwivew has to make suwe to cweaw its
 *	ACW wist duwing %NW80211_CMD_STOP_AP.
 *
 * @NW80211_CMD_WADAW_DETECT: Stawt a Channew avaiwabiwity check (CAC). Once
 *	a wadaw is detected ow the channew avaiwabiwity scan (CAC) has finished
 *	ow was abowted, ow a wadaw was detected, usewmode wiww be notified with
 *	this event. This command is awso used to notify usewspace about wadaws
 *	whiwe opewating on this channew.
 *	%NW80211_ATTW_WADAW_EVENT is used to infowm about the type of the
 *	event.
 *
 * @NW80211_CMD_GET_PWOTOCOW_FEATUWES: Get gwobaw nw80211 pwotocow featuwes,
 *	i.e. featuwes fow the nw80211 pwotocow wathew than device featuwes.
 *	Wetuwns the featuwes in the %NW80211_ATTW_PWOTOCOW_FEATUWES bitmap.
 *
 * @NW80211_CMD_UPDATE_FT_IES: Pass down the most up-to-date Fast Twansition
 *	Infowmation Ewement to the WWAN dwivew
 *
 * @NW80211_CMD_FT_EVENT: Send a Fast twansition event fwom the WWAN dwivew
 *	to the suppwicant. This wiww cawwy the tawget AP's MAC addwess awong
 *	with the wewevant Infowmation Ewements. This event is used to wepowt
 *	weceived FT IEs (MDIE, FTIE, WSN IE, TIE, WICIE).
 *
 * @NW80211_CMD_CWIT_PWOTOCOW_STAWT: Indicates usew-space wiww stawt wunning
 *	a cwiticaw pwotocow that needs mowe wewiabiwity in the connection to
 *	compwete.
 *
 * @NW80211_CMD_CWIT_PWOTOCOW_STOP: Indicates the connection wewiabiwity can
 *	wetuwn back to nowmaw.
 *
 * @NW80211_CMD_GET_COAWESCE: Get cuwwentwy suppowted coawesce wuwes.
 * @NW80211_CMD_SET_COAWESCE: Configuwe coawesce wuwes ow cweaw existing wuwes.
 *
 * @NW80211_CMD_CHANNEW_SWITCH: Pewfowm a channew switch by announcing the
 *	new channew infowmation (Channew Switch Announcement - CSA)
 *	in the beacon fow some time (as defined in the
 *	%NW80211_ATTW_CH_SWITCH_COUNT pawametew) and then change to the
 *	new channew. Usewspace pwovides the new channew infowmation (using
 *	%NW80211_ATTW_WIPHY_FWEQ and the attwibutes detewmining channew
 *	width). %NW80211_ATTW_CH_SWITCH_BWOCK_TX may be suppwied to infowm
 *	othew station that twansmission must be bwocked untiw the channew
 *	switch is compwete.
 *
 * @NW80211_CMD_VENDOW: Vendow-specified command/event. The command is specified
 *	by the %NW80211_ATTW_VENDOW_ID attwibute and a sub-command in
 *	%NW80211_ATTW_VENDOW_SUBCMD. Pawametew(s) can be twanspowted in
 *	%NW80211_ATTW_VENDOW_DATA.
 *	Fow featuwe advewtisement, the %NW80211_ATTW_VENDOW_DATA attwibute is
 *	used in the wiphy data as a nested attwibute containing descwiptions
 *	(&stwuct nw80211_vendow_cmd_info) of the suppowted vendow commands.
 *	This may awso be sent as an event with the same attwibutes.
 *
 * @NW80211_CMD_SET_QOS_MAP: Set Intewwowking QoS mapping fow IP DSCP vawues.
 *	The QoS mapping infowmation is incwuded in %NW80211_ATTW_QOS_MAP. If
 *	that attwibute is not incwuded, QoS mapping is disabwed. Since this
 *	QoS mapping is wewevant fow IP packets, it is onwy vawid duwing an
 *	association. This is cweawed on disassociation and AP westawt.
 *
 * @NW80211_CMD_ADD_TX_TS: Ask the kewnew to add a twaffic stweam fow the given
 *	%NW80211_ATTW_TSID and %NW80211_ATTW_MAC with %NW80211_ATTW_USEW_PWIO
 *	and %NW80211_ATTW_ADMITTED_TIME pawametews.
 *	Note that the action fwame handshake with the AP shaww be handwed by
 *	usewspace via the nowmaw management WX/TX fwamewowk, this onwy sets
 *	up the TX TS in the dwivew/device.
 *	If the admitted time attwibute is not added then the wequest just checks
 *	if a subsequent setup couwd be successfuw, the intent is to use this to
 *	avoid setting up a session with the AP when wocaw westwictions wouwd
 *	make that impossibwe. Howevew, the subsequent "weaw" setup may stiww
 *	faiw even if the check was successfuw.
 * @NW80211_CMD_DEW_TX_TS: Wemove an existing TS with the %NW80211_ATTW_TSID
 *	and %NW80211_ATTW_MAC pawametews. It isn't necessawy to caww this
 *	befowe wemoving a station entwy entiwewy, ow befowe disassociating
 *	ow simiwaw, cweanup wiww happen in the dwivew/device in this case.
 *
 * @NW80211_CMD_GET_MPP: Get mesh path attwibutes fow mesh pwoxy path to
 *	destination %NW80211_ATTW_MAC on the intewface identified by
 *	%NW80211_ATTW_IFINDEX.
 *
 * @NW80211_CMD_JOIN_OCB: Join the OCB netwowk. The centew fwequency and
 *	bandwidth of a channew must be given.
 * @NW80211_CMD_WEAVE_OCB: Weave the OCB netwowk -- no speciaw awguments, the
 *	netwowk is detewmined by the netwowk intewface.
 *
 * @NW80211_CMD_TDWS_CHANNEW_SWITCH: Stawt channew-switching with a TDWS peew,
 *	identified by the %NW80211_ATTW_MAC pawametew. A tawget channew is
 *	pwovided via %NW80211_ATTW_WIPHY_FWEQ and othew attwibutes detewmining
 *	channew width/type. The tawget opewating cwass is given via
 *	%NW80211_ATTW_OPEW_CWASS.
 *	The dwivew is wesponsibwe fow continuawwy initiating channew-switching
 *	opewations and wetuwning to the base channew fow communication with the
 *	AP.
 * @NW80211_CMD_TDWS_CANCEW_CHANNEW_SWITCH: Stop channew-switching with a TDWS
 *	peew given by %NW80211_ATTW_MAC. Both peews must be on the base channew
 *	when this command compwetes.
 *
 * @NW80211_CMD_WIPHY_WEG_CHANGE: Simiwaw to %NW80211_CMD_WEG_CHANGE, but used
 *	as an event to indicate changes fow devices with wiphy-specific wegdom
 *	management.
 *
 * @NW80211_CMD_ABOWT_SCAN: Stop an ongoing scan. Wetuwns -ENOENT if a scan is
 *	not wunning. The dwivew indicates the status of the scan thwough
 *	cfg80211_scan_done().
 *
 * @NW80211_CMD_STAWT_NAN: Stawt NAN opewation, identified by its
 *	%NW80211_ATTW_WDEV intewface. This intewface must have been
 *	pweviouswy cweated with %NW80211_CMD_NEW_INTEWFACE. Aftew it
 *	has been stawted, the NAN intewface wiww cweate ow join a
 *	cwustew. This command must have a vawid
 *	%NW80211_ATTW_NAN_MASTEW_PWEF attwibute and optionaw
 *	%NW80211_ATTW_BANDS attwibutes.  If %NW80211_ATTW_BANDS is
 *	omitted ow set to 0, it means don't-cawe and the device wiww
 *	decide what to use.  Aftew this command NAN functions can be
 *	added.
 * @NW80211_CMD_STOP_NAN: Stop the NAN opewation, identified by
 *	its %NW80211_ATTW_WDEV intewface.
 * @NW80211_CMD_ADD_NAN_FUNCTION: Add a NAN function. The function is defined
 *	with %NW80211_ATTW_NAN_FUNC nested attwibute. When cawwed, this
 *	opewation wetuwns the stwictwy positive and unique instance id
 *	(%NW80211_ATTW_NAN_FUNC_INST_ID) and a cookie (%NW80211_ATTW_COOKIE)
 *	of the function upon success.
 *	Since instance ID's can be we-used, this cookie is the wight
 *	way to identify the function. This wiww avoid waces when a tewmination
 *	event is handwed by the usew space aftew it has awweady added a new
 *	function that got the same instance id fwom the kewnew as the one
 *	which just tewminated.
 *	This cookie may be used in NAN events even befowe the command
 *	wetuwns, so usewspace shouwdn't pwocess NAN events untiw it pwocesses
 *	the wesponse to this command.
 *	Wook at %NW80211_ATTW_SOCKET_OWNEW as weww.
 * @NW80211_CMD_DEW_NAN_FUNCTION: Dewete a NAN function by cookie.
 *	This command is awso used as a notification sent when a NAN function is
 *	tewminated. This wiww contain a %NW80211_ATTW_NAN_FUNC_INST_ID
 *	and %NW80211_ATTW_COOKIE attwibutes.
 * @NW80211_CMD_CHANGE_NAN_CONFIG: Change cuwwent NAN
 *	configuwation. NAN must be opewationaw (%NW80211_CMD_STAWT_NAN
 *	was executed).  It must contain at weast one of the fowwowing
 *	attwibutes: %NW80211_ATTW_NAN_MASTEW_PWEF,
 *	%NW80211_ATTW_BANDS.  If %NW80211_ATTW_BANDS is omitted, the
 *	cuwwent configuwation is not changed.  If it is pwesent but
 *	set to zewo, the configuwation is changed to don't-cawe
 *	(i.e. the device can decide what to do).
 * @NW80211_CMD_NAN_FUNC_MATCH: Notification sent when a match is wepowted.
 *	This wiww contain a %NW80211_ATTW_NAN_MATCH nested attwibute and
 *	%NW80211_ATTW_COOKIE.
 *
 * @NW80211_CMD_UPDATE_CONNECT_PAWAMS: Update one ow mowe connect pawametews
 *	fow subsequent woaming cases if the dwivew ow fiwmwawe uses intewnaw
 *	BSS sewection. This command can be issued onwy whiwe connected and it
 *	does not wesuwt in a change fow the cuwwent association. Cuwwentwy,
 *	onwy the %NW80211_ATTW_IE data is used and updated with this command.
 *
 * @NW80211_CMD_SET_PMK: Fow offwoaded 4-Way handshake, set the PMK ow PMK-W0
 *	fow the given authenticatow addwess (specified with %NW80211_ATTW_MAC).
 *	When %NW80211_ATTW_PMKW0_NAME is set, %NW80211_ATTW_PMK specifies the
 *	PMK-W0, othewwise it specifies the PMK.
 * @NW80211_CMD_DEW_PMK: Fow offwoaded 4-Way handshake, dewete the pweviouswy
 *	configuwed PMK fow the authenticatow addwess identified by
 *	%NW80211_ATTW_MAC.
 * @NW80211_CMD_POWT_AUTHOWIZED: An event that indicates powt is authowized and
 *	open fow weguwaw data twaffic. Fow STA/P2P-cwient, this event is sent
 *	with AP MAC addwess and fow AP/P2P-GO, the event cawwies the STA/P2P-
 *	cwient MAC addwess.
 *	Dwivews that suppowt 4 way handshake offwoad shouwd send this event fow
 *	STA/P2P-cwient aftew successfuw 4-way HS ow aftew 802.1X FT fowwowing
 *	NW80211_CMD_CONNECT ow NW80211_CMD_WOAM. Dwivews using AP/P2P-GO 4-way
 *	handshake offwoad shouwd send this event on successfuw compwetion of
 *	4-way handshake with the peew (STA/P2P-cwient).
 * @NW80211_CMD_CONTWOW_POWT_FWAME: Contwow Powt (e.g. PAE) fwame TX wequest
 *	and WX notification.  This command is used both as a wequest to twansmit
 *	a contwow powt fwame and as a notification that a contwow powt fwame
 *	has been weceived. %NW80211_ATTW_FWAME is used to specify the
 *	fwame contents.  The fwame is the waw EAPoW data, without ethewnet ow
 *	802.11 headews.
 *	Fow an MWD twansmittew, the %NW80211_ATTW_MWO_WINK_ID may be given and
 *	its effect wiww depend on the destination: If the destination is known
 *	to be an MWD, this wiww be used as a hint to sewect the wink to twansmit
 *	the fwame on. If the destination is not an MWD, this wiww sewect both
 *	the wink to twansmit on and the souwce addwess wiww be set to the wink
 *	addwess of that wink.
 *	When used as an event indication %NW80211_ATTW_CONTWOW_POWT_ETHEWTYPE,
 *	%NW80211_ATTW_CONTWOW_POWT_NO_ENCWYPT and %NW80211_ATTW_MAC awe added
 *	indicating the pwotocow type of the weceived fwame; whethew the fwame
 *	was weceived unencwypted and the MAC addwess of the peew wespectivewy.
 *
 * @NW80211_CMD_WEWOAD_WEGDB: Wequest that the wegdb fiwmwawe fiwe is wewoaded.
 *
 * @NW80211_CMD_EXTEWNAW_AUTH: This intewface is excwusivewy defined fow host
 *	dwivews that do not define sepawate commands fow authentication and
 *	association, but wewy on usew space fow the authentication to happen.
 *	This intewface acts both as the event wequest (dwivew to usew space)
 *	to twiggew the authentication and command wesponse (usewspace to
 *	dwivew) to indicate the authentication status.
 *
 *	Usew space uses the %NW80211_CMD_CONNECT command to the host dwivew to
 *	twiggew a connection. The host dwivew sewects a BSS and fuwthew uses
 *	this intewface to offwoad onwy the authentication pawt to the usew
 *	space. Authentication fwames awe passed between the dwivew and usew
 *	space thwough the %NW80211_CMD_FWAME intewface. Host dwivew pwoceeds
 *	fuwthew with the association aftew getting successfuw authentication
 *	status. Usew space indicates the authentication status thwough
 *	%NW80211_ATTW_STATUS_CODE attwibute in %NW80211_CMD_EXTEWNAW_AUTH
 *	command intewface.
 *
 *	Host dwivew sends MWD addwess of the AP with %NW80211_ATTW_MWD_ADDW in
 *	%NW80211_CMD_EXTEWNAW_AUTH event to indicate usew space to enabwe MWO
 *	duwing the authentication offwoad in STA mode whiwe connecting to MWD
 *	APs. Host dwivew shouwd check %NW80211_ATTW_MWO_SUPPOWT fwag capabiwity
 *	in %NW80211_CMD_CONNECT to know whethew the usew space suppowts enabwing
 *	MWO duwing the authentication offwoad ow not.
 *	Usew space shouwd enabwe MWO duwing the authentication onwy when it
 *	weceives the AP MWD addwess in authentication offwoad wequest. Usew
 *	space shouwdn't enabwe MWO when the authentication offwoad wequest
 *	doesn't indicate the AP MWD addwess even if the AP is MWO capabwe.
 *	Usew space shouwd use %NW80211_ATTW_MWD_ADDW as peew's MWD addwess and
 *	intewface addwess identified by %NW80211_ATTW_IFINDEX as sewf MWD
 *	addwess. Usew space and host dwivew to use MWD addwesses in WA, TA and
 *	BSSID fiewds of the fwames between them, and host dwivew twanswates the
 *	MWD addwesses to/fwom wink addwesses based on the wink chosen fow the
 *	authentication.
 *
 *	Host dwivew wepowts this status on an authentication faiwuwe to the
 *	usew space thwough the connect wesuwt as the usew space wouwd have
 *	initiated the connection thwough the connect wequest.
 *
 * @NW80211_CMD_STA_OPMODE_CHANGED: An event that notify station's
 *	ht opmode ow vht opmode changes using any of %NW80211_ATTW_SMPS_MODE,
 *	%NW80211_ATTW_CHANNEW_WIDTH,%NW80211_ATTW_NSS attwibutes with its
 *	addwess(specified in %NW80211_ATTW_MAC).
 *
 * @NW80211_CMD_GET_FTM_WESPONDEW_STATS: Wetwieve FTM wespondew statistics, in
 *	the %NW80211_ATTW_FTM_WESPONDEW_STATS attwibute.
 *
 * @NW80211_CMD_PEEW_MEASUWEMENT_STAWT: stawt a (set of) peew measuwement(s)
 *	with the given pawametews, which awe encapsuwated in the nested
 *	%NW80211_ATTW_PEEW_MEASUWEMENTS attwibute. Optionawwy, MAC addwess
 *	wandomization may be enabwed and configuwed by specifying the
 *	%NW80211_ATTW_MAC and %NW80211_ATTW_MAC_MASK attwibutes.
 *	If a timeout is wequested, use the %NW80211_ATTW_TIMEOUT attwibute.
 *	A u64 cookie fow fuwthew %NW80211_ATTW_COOKIE use is wetuwned in
 *	the netwink extended ack message.
 *
 *	To cancew a measuwement, cwose the socket that wequested it.
 *
 *	Measuwement wesuwts awe wepowted to the socket that wequested the
 *	measuwement using @NW80211_CMD_PEEW_MEASUWEMENT_WESUWT when they
 *	become avaiwabwe, so appwications must ensuwe a wawge enough socket
 *	buffew size.
 *
 *	Depending on dwivew suppowt it may ow may not be possibwe to stawt
 *	muwtipwe concuwwent measuwements.
 * @NW80211_CMD_PEEW_MEASUWEMENT_WESUWT: This command numbew is used fow the
 *	wesuwt notification fwom the dwivew to the wequesting socket.
 * @NW80211_CMD_PEEW_MEASUWEMENT_COMPWETE: Notification onwy, indicating that
 *	the measuwement compweted, using the measuwement cookie
 *	(%NW80211_ATTW_COOKIE).
 *
 * @NW80211_CMD_NOTIFY_WADAW: Notify the kewnew that a wadaw signaw was
 *	detected and wepowted by a neighbowing device on the channew
 *	indicated by %NW80211_ATTW_WIPHY_FWEQ and othew attwibutes
 *	detewmining the width and type.
 *
 * @NW80211_CMD_UPDATE_OWE_INFO: This intewface awwows the host dwivew to
 *	offwoad OWE pwocessing to usew space. This intends to suppowt
 *	OWE AKM by the host dwivews that impwement SME but wewy
 *	on the usew space fow the cwyptogwaphic/DH IE pwocessing in AP mode.
 *
 * @NW80211_CMD_PWOBE_MESH_WINK: The wequiwement fow mesh wink metwic
 *	wefweshing, is that fwom one mesh point we be abwe to send some data
 *	fwames to othew mesh points which awe not cuwwentwy sewected as a
 *	pwimawy twaffic path, but which awe onwy 1 hop away. The absence of
 *	the pwimawy path to the chosen node makes it necessawy to appwy some
 *	fowm of mawking on a chosen packet stweam so that the packets can be
 *	pwopewwy steewed to the sewected node fow testing, and not by the
 *	weguwaw mesh path wookup. Fuwthew, the packets must be of type data
 *	so that the wate contwow (often embedded in fiwmwawe) is used fow
 *	wate sewection.
 *
 *	Hewe attwibute %NW80211_ATTW_MAC is used to specify connected mesh
 *	peew MAC addwess and %NW80211_ATTW_FWAME is used to specify the fwame
 *	content. The fwame is ethewnet data.
 *
 * @NW80211_CMD_SET_TID_CONFIG: Data fwame TID specific configuwation
 *	is passed using %NW80211_ATTW_TID_CONFIG attwibute.
 *
 * @NW80211_CMD_UNPWOT_BEACON: Unpwotected ow incowwectwy pwotected Beacon
 *	fwame. This event is used to indicate that a weceived Beacon fwame was
 *	dwopped because it did not incwude a vawid MME MIC whiwe beacon
 *	pwotection was enabwed (BIGTK configuwed in station mode).
 *
 * @NW80211_CMD_CONTWOW_POWT_FWAME_TX_STATUS: Wepowt TX status of a contwow
 *	powt fwame twansmitted with %NW80211_CMD_CONTWOW_POWT_FWAME.
 *	%NW80211_ATTW_COOKIE identifies the TX command and %NW80211_ATTW_FWAME
 *	incwudes the contents of the fwame. %NW80211_ATTW_ACK fwag is incwuded
 *	if the wecipient acknowwedged the fwame.
 *
 * @NW80211_CMD_SET_SAW_SPECS: SAW powew wimitation configuwation is
 *	passed using %NW80211_ATTW_SAW_SPEC. %NW80211_ATTW_WIPHY is used to
 *	specify the wiphy index to be appwied to.
 *
 * @NW80211_CMD_OBSS_COWOW_COWWISION: This notification is sent out whenevew
 *	mac80211/dwv detects a bss cowow cowwision.
 *
 * @NW80211_CMD_COWOW_CHANGE_WEQUEST: This command is used to indicate that
 *	usewspace wants to change the BSS cowow.
 *
 * @NW80211_CMD_COWOW_CHANGE_STAWTED: Notify usewwand, that a cowow change has
 *	stawted
 *
 * @NW80211_CMD_COWOW_CHANGE_ABOWTED: Notify usewwand, that the cowow change has
 *	been abowted
 *
 * @NW80211_CMD_COWOW_CHANGE_COMPWETED: Notify usewwand that the cowow change
 *	has compweted
 *
 * @NW80211_CMD_SET_FIWS_AAD: Set FIWS AAD data to the dwivew using -
 *	&NW80211_ATTW_MAC - fow STA MAC addwess
 *	&NW80211_ATTW_FIWS_KEK - fow KEK
 *	&NW80211_ATTW_FIWS_NONCES - fow FIWS Nonces
 *		(STA Nonce 16 bytes fowwowed by AP Nonce 16 bytes)
 *
 * @NW80211_CMD_ASSOC_COMEBACK: notification about an association
 *      tempowaw wejection with comeback. The event incwudes %NW80211_ATTW_MAC
 *      to descwibe the BSSID addwess of the AP and %NW80211_ATTW_TIMEOUT to
 *      specify the timeout vawue.
 *
 * @NW80211_CMD_ADD_WINK: Add a new wink to an intewface. The
 *	%NW80211_ATTW_MWO_WINK_ID attwibute is used fow the new wink.
 * @NW80211_CMD_WEMOVE_WINK: Wemove a wink fwom an intewface. This may come
 *	without %NW80211_ATTW_MWO_WINK_ID as an easy way to wemove aww winks
 *	in pwepawation fow e.g. woaming to a weguwaw (non-MWO) AP.
 *
 * @NW80211_CMD_ADD_WINK_STA: Add a wink to an MWD station
 * @NW80211_CMD_MODIFY_WINK_STA: Modify a wink of an MWD station
 * @NW80211_CMD_WEMOVE_WINK_STA: Wemove a wink of an MWD station
 *
 * @NW80211_CMD_SET_HW_TIMESTAMP: Enabwe/disabwe HW timestamping of Timing
 *	measuwement and Fine timing measuwement fwames. If %NW80211_ATTW_MAC
 *	is incwuded, enabwe/disabwe HW timestamping onwy fow fwames to/fwom the
 *	specified MAC addwess. Othewwise enabwe/disabwe HW timestamping fow
 *	aww TM/FTM fwames (incwuding ones that wewe enabwed with specific MAC
 *	addwess). If %NW80211_ATTW_HW_TIMESTAMP_ENABWED is not incwuded, disabwe
 *	HW timestamping.
 *	The numbew of peews that HW timestamping can be enabwed fow concuwwentwy
 *	is indicated by %NW80211_ATTW_MAX_HW_TIMESTAMP_PEEWS.
 *
 * @NW80211_CMD_WINKS_WEMOVED: Notify usewspace about the wemovaw of STA MWD
 *	setup winks due to AP MWD wemoving the cowwesponding affiwiated APs with
 *	Muwti-Wink weconfiguwation. %NW80211_ATTW_MWO_WINKS is used to pwovide
 *	infowmation about the wemoved STA MWD setup winks.
 *
 * @NW80211_CMD_SET_TID_TO_WINK_MAPPING: Set the TID to Wink Mapping fow a
 *      non-AP MWD station. The %NW80211_ATTW_MWO_TTWM_DWINK and
 *      %NW80211_ATTW_MWO_TTWM_UWINK attwibutes awe used to specify the
 *      TID to Wink mapping fow downwink/upwink twaffic.
 *
 * @NW80211_CMD_MAX: highest used command numbew
 * @__NW80211_CMD_AFTEW_WAST: intewnaw use
 */
enum nw80211_commands {
/* don't change the owdew ow add anything between, this is ABI! */
	NW80211_CMD_UNSPEC,

	NW80211_CMD_GET_WIPHY,		/* can dump */
	NW80211_CMD_SET_WIPHY,
	NW80211_CMD_NEW_WIPHY,
	NW80211_CMD_DEW_WIPHY,

	NW80211_CMD_GET_INTEWFACE,	/* can dump */
	NW80211_CMD_SET_INTEWFACE,
	NW80211_CMD_NEW_INTEWFACE,
	NW80211_CMD_DEW_INTEWFACE,

	NW80211_CMD_GET_KEY,
	NW80211_CMD_SET_KEY,
	NW80211_CMD_NEW_KEY,
	NW80211_CMD_DEW_KEY,

	NW80211_CMD_GET_BEACON,
	NW80211_CMD_SET_BEACON,
	NW80211_CMD_STAWT_AP,
	NW80211_CMD_NEW_BEACON = NW80211_CMD_STAWT_AP,
	NW80211_CMD_STOP_AP,
	NW80211_CMD_DEW_BEACON = NW80211_CMD_STOP_AP,

	NW80211_CMD_GET_STATION,
	NW80211_CMD_SET_STATION,
	NW80211_CMD_NEW_STATION,
	NW80211_CMD_DEW_STATION,

	NW80211_CMD_GET_MPATH,
	NW80211_CMD_SET_MPATH,
	NW80211_CMD_NEW_MPATH,
	NW80211_CMD_DEW_MPATH,

	NW80211_CMD_SET_BSS,

	NW80211_CMD_SET_WEG,
	NW80211_CMD_WEQ_SET_WEG,

	NW80211_CMD_GET_MESH_CONFIG,
	NW80211_CMD_SET_MESH_CONFIG,

	NW80211_CMD_SET_MGMT_EXTWA_IE /* wesewved; not used */,

	NW80211_CMD_GET_WEG,

	NW80211_CMD_GET_SCAN,
	NW80211_CMD_TWIGGEW_SCAN,
	NW80211_CMD_NEW_SCAN_WESUWTS,
	NW80211_CMD_SCAN_ABOWTED,

	NW80211_CMD_WEG_CHANGE,

	NW80211_CMD_AUTHENTICATE,
	NW80211_CMD_ASSOCIATE,
	NW80211_CMD_DEAUTHENTICATE,
	NW80211_CMD_DISASSOCIATE,

	NW80211_CMD_MICHAEW_MIC_FAIWUWE,

	NW80211_CMD_WEG_BEACON_HINT,

	NW80211_CMD_JOIN_IBSS,
	NW80211_CMD_WEAVE_IBSS,

	NW80211_CMD_TESTMODE,

	NW80211_CMD_CONNECT,
	NW80211_CMD_WOAM,
	NW80211_CMD_DISCONNECT,

	NW80211_CMD_SET_WIPHY_NETNS,

	NW80211_CMD_GET_SUWVEY,
	NW80211_CMD_NEW_SUWVEY_WESUWTS,

	NW80211_CMD_SET_PMKSA,
	NW80211_CMD_DEW_PMKSA,
	NW80211_CMD_FWUSH_PMKSA,

	NW80211_CMD_WEMAIN_ON_CHANNEW,
	NW80211_CMD_CANCEW_WEMAIN_ON_CHANNEW,

	NW80211_CMD_SET_TX_BITWATE_MASK,

	NW80211_CMD_WEGISTEW_FWAME,
	NW80211_CMD_WEGISTEW_ACTION = NW80211_CMD_WEGISTEW_FWAME,
	NW80211_CMD_FWAME,
	NW80211_CMD_ACTION = NW80211_CMD_FWAME,
	NW80211_CMD_FWAME_TX_STATUS,
	NW80211_CMD_ACTION_TX_STATUS = NW80211_CMD_FWAME_TX_STATUS,

	NW80211_CMD_SET_POWEW_SAVE,
	NW80211_CMD_GET_POWEW_SAVE,

	NW80211_CMD_SET_CQM,
	NW80211_CMD_NOTIFY_CQM,

	NW80211_CMD_SET_CHANNEW,
	NW80211_CMD_SET_WDS_PEEW,

	NW80211_CMD_FWAME_WAIT_CANCEW,

	NW80211_CMD_JOIN_MESH,
	NW80211_CMD_WEAVE_MESH,

	NW80211_CMD_UNPWOT_DEAUTHENTICATE,
	NW80211_CMD_UNPWOT_DISASSOCIATE,

	NW80211_CMD_NEW_PEEW_CANDIDATE,

	NW80211_CMD_GET_WOWWAN,
	NW80211_CMD_SET_WOWWAN,

	NW80211_CMD_STAWT_SCHED_SCAN,
	NW80211_CMD_STOP_SCHED_SCAN,
	NW80211_CMD_SCHED_SCAN_WESUWTS,
	NW80211_CMD_SCHED_SCAN_STOPPED,

	NW80211_CMD_SET_WEKEY_OFFWOAD,

	NW80211_CMD_PMKSA_CANDIDATE,

	NW80211_CMD_TDWS_OPEW,
	NW80211_CMD_TDWS_MGMT,

	NW80211_CMD_UNEXPECTED_FWAME,

	NW80211_CMD_PWOBE_CWIENT,

	NW80211_CMD_WEGISTEW_BEACONS,

	NW80211_CMD_UNEXPECTED_4ADDW_FWAME,

	NW80211_CMD_SET_NOACK_MAP,

	NW80211_CMD_CH_SWITCH_NOTIFY,

	NW80211_CMD_STAWT_P2P_DEVICE,
	NW80211_CMD_STOP_P2P_DEVICE,

	NW80211_CMD_CONN_FAIWED,

	NW80211_CMD_SET_MCAST_WATE,

	NW80211_CMD_SET_MAC_ACW,

	NW80211_CMD_WADAW_DETECT,

	NW80211_CMD_GET_PWOTOCOW_FEATUWES,

	NW80211_CMD_UPDATE_FT_IES,
	NW80211_CMD_FT_EVENT,

	NW80211_CMD_CWIT_PWOTOCOW_STAWT,
	NW80211_CMD_CWIT_PWOTOCOW_STOP,

	NW80211_CMD_GET_COAWESCE,
	NW80211_CMD_SET_COAWESCE,

	NW80211_CMD_CHANNEW_SWITCH,

	NW80211_CMD_VENDOW,

	NW80211_CMD_SET_QOS_MAP,

	NW80211_CMD_ADD_TX_TS,
	NW80211_CMD_DEW_TX_TS,

	NW80211_CMD_GET_MPP,

	NW80211_CMD_JOIN_OCB,
	NW80211_CMD_WEAVE_OCB,

	NW80211_CMD_CH_SWITCH_STAWTED_NOTIFY,

	NW80211_CMD_TDWS_CHANNEW_SWITCH,
	NW80211_CMD_TDWS_CANCEW_CHANNEW_SWITCH,

	NW80211_CMD_WIPHY_WEG_CHANGE,

	NW80211_CMD_ABOWT_SCAN,

	NW80211_CMD_STAWT_NAN,
	NW80211_CMD_STOP_NAN,
	NW80211_CMD_ADD_NAN_FUNCTION,
	NW80211_CMD_DEW_NAN_FUNCTION,
	NW80211_CMD_CHANGE_NAN_CONFIG,
	NW80211_CMD_NAN_MATCH,

	NW80211_CMD_SET_MUWTICAST_TO_UNICAST,

	NW80211_CMD_UPDATE_CONNECT_PAWAMS,

	NW80211_CMD_SET_PMK,
	NW80211_CMD_DEW_PMK,

	NW80211_CMD_POWT_AUTHOWIZED,

	NW80211_CMD_WEWOAD_WEGDB,

	NW80211_CMD_EXTEWNAW_AUTH,

	NW80211_CMD_STA_OPMODE_CHANGED,

	NW80211_CMD_CONTWOW_POWT_FWAME,

	NW80211_CMD_GET_FTM_WESPONDEW_STATS,

	NW80211_CMD_PEEW_MEASUWEMENT_STAWT,
	NW80211_CMD_PEEW_MEASUWEMENT_WESUWT,
	NW80211_CMD_PEEW_MEASUWEMENT_COMPWETE,

	NW80211_CMD_NOTIFY_WADAW,

	NW80211_CMD_UPDATE_OWE_INFO,

	NW80211_CMD_PWOBE_MESH_WINK,

	NW80211_CMD_SET_TID_CONFIG,

	NW80211_CMD_UNPWOT_BEACON,

	NW80211_CMD_CONTWOW_POWT_FWAME_TX_STATUS,

	NW80211_CMD_SET_SAW_SPECS,

	NW80211_CMD_OBSS_COWOW_COWWISION,

	NW80211_CMD_COWOW_CHANGE_WEQUEST,

	NW80211_CMD_COWOW_CHANGE_STAWTED,
	NW80211_CMD_COWOW_CHANGE_ABOWTED,
	NW80211_CMD_COWOW_CHANGE_COMPWETED,

	NW80211_CMD_SET_FIWS_AAD,

	NW80211_CMD_ASSOC_COMEBACK,

	NW80211_CMD_ADD_WINK,
	NW80211_CMD_WEMOVE_WINK,

	NW80211_CMD_ADD_WINK_STA,
	NW80211_CMD_MODIFY_WINK_STA,
	NW80211_CMD_WEMOVE_WINK_STA,

	NW80211_CMD_SET_HW_TIMESTAMP,

	NW80211_CMD_WINKS_WEMOVED,

	NW80211_CMD_SET_TID_TO_WINK_MAPPING,

	/* add new commands above hewe */

	/* used to define NW80211_CMD_MAX bewow */
	__NW80211_CMD_AFTEW_WAST,
	NW80211_CMD_MAX = __NW80211_CMD_AFTEW_WAST - 1
};

/*
 * Awwow usew space pwogwams to use #ifdef on new commands by defining them
 * hewe
 */
#define NW80211_CMD_SET_BSS NW80211_CMD_SET_BSS
#define NW80211_CMD_SET_MGMT_EXTWA_IE NW80211_CMD_SET_MGMT_EXTWA_IE
#define NW80211_CMD_WEG_CHANGE NW80211_CMD_WEG_CHANGE
#define NW80211_CMD_AUTHENTICATE NW80211_CMD_AUTHENTICATE
#define NW80211_CMD_ASSOCIATE NW80211_CMD_ASSOCIATE
#define NW80211_CMD_DEAUTHENTICATE NW80211_CMD_DEAUTHENTICATE
#define NW80211_CMD_DISASSOCIATE NW80211_CMD_DISASSOCIATE
#define NW80211_CMD_WEG_BEACON_HINT NW80211_CMD_WEG_BEACON_HINT

#define NW80211_ATTW_FEATUWE_FWAGS NW80211_ATTW_FEATUWE_FWAGS

/* souwce-wevew API compatibiwity */
#define NW80211_CMD_GET_MESH_PAWAMS NW80211_CMD_GET_MESH_CONFIG
#define NW80211_CMD_SET_MESH_PAWAMS NW80211_CMD_SET_MESH_CONFIG
#define NW80211_MESH_SETUP_VENDOW_PATH_SEW_IE NW80211_MESH_SETUP_IE

/**
 * enum nw80211_attws - nw80211 netwink attwibutes
 *
 * @NW80211_ATTW_UNSPEC: unspecified attwibute to catch ewwows
 *
 * @NW80211_ATTW_WIPHY: index of wiphy to opewate on, cf.
 *	/sys/cwass/ieee80211/<phyname>/index
 * @NW80211_ATTW_WIPHY_NAME: wiphy name (used fow wenaming)
 * @NW80211_ATTW_WIPHY_TXQ_PAWAMS: a nested awway of TX queue pawametews
 * @NW80211_ATTW_WIPHY_FWEQ: fwequency of the sewected channew in MHz,
 *	defines the channew togethew with the (depwecated)
 *	%NW80211_ATTW_WIPHY_CHANNEW_TYPE attwibute ow the attwibutes
 *	%NW80211_ATTW_CHANNEW_WIDTH and if needed %NW80211_ATTW_CENTEW_FWEQ1
 *	and %NW80211_ATTW_CENTEW_FWEQ2
 * @NW80211_ATTW_CHANNEW_WIDTH: u32 attwibute containing one of the vawues
 *	of &enum nw80211_chan_width, descwibing the channew width. See the
 *	documentation of the enum fow mowe infowmation.
 * @NW80211_ATTW_CENTEW_FWEQ1: Centew fwequency of the fiwst pawt of the
 *	channew, used fow anything but 20 MHz bandwidth. In S1G this is the
 *	opewating channew centew fwequency.
 * @NW80211_ATTW_CENTEW_FWEQ2: Centew fwequency of the second pawt of the
 *	channew, used onwy fow 80+80 MHz bandwidth
 * @NW80211_ATTW_WIPHY_CHANNEW_TYPE: incwuded with NW80211_ATTW_WIPHY_FWEQ
 *	if HT20 ow HT40 awe to be used (i.e., HT disabwed if not incwuded):
 *	NW80211_CHAN_NO_HT = HT not awwowed (i.e., same as not incwuding
 *		this attwibute)
 *	NW80211_CHAN_HT20 = HT20 onwy
 *	NW80211_CHAN_HT40MINUS = secondawy channew is bewow the pwimawy channew
 *	NW80211_CHAN_HT40PWUS = secondawy channew is above the pwimawy channew
 *	This attwibute is now depwecated.
 * @NW80211_ATTW_WIPHY_WETWY_SHOWT: TX wetwy wimit fow fwames whose wength is
 *	wess than ow equaw to the WTS thweshowd; awwowed wange: 1..255;
 *	dot11ShowtWetwyWimit; u8
 * @NW80211_ATTW_WIPHY_WETWY_WONG: TX wetwy wimit fow fwames whose wength is
 *	gweatew than the WTS thweshowd; awwowed wange: 1..255;
 *	dot11ShowtWongWimit; u8
 * @NW80211_ATTW_WIPHY_FWAG_THWESHOWD: fwagmentation thweshowd, i.e., maximum
 *	wength in octets fow fwames; awwowed wange: 256..8000, disabwe
 *	fwagmentation with (u32)-1; dot11FwagmentationThweshowd; u32
 * @NW80211_ATTW_WIPHY_WTS_THWESHOWD: WTS thweshowd (TX fwames with wength
 *	wawgew than ow equaw to this use WTS/CTS handshake); awwowed wange:
 *	0..65536, disabwe with (u32)-1; dot11WTSThweshowd; u32
 * @NW80211_ATTW_WIPHY_COVEWAGE_CWASS: Covewage Cwass as defined by IEEE 802.11
 *	section 7.3.2.9; dot11CovewageCwass; u8
 *
 * @NW80211_ATTW_IFINDEX: netwowk intewface index of the device to opewate on
 * @NW80211_ATTW_IFNAME: netwowk intewface name
 * @NW80211_ATTW_IFTYPE: type of viwtuaw intewface, see &enum nw80211_iftype
 *
 * @NW80211_ATTW_WDEV: wiwewess device identifiew, used fow pseudo-devices
 *	that don't have a netdev (u64)
 *
 * @NW80211_ATTW_MAC: MAC addwess (vawious uses)
 *
 * @NW80211_ATTW_KEY_DATA: (tempowaw) key data; fow TKIP this consists of
 *	16 bytes encwyption key fowwowed by 8 bytes each fow TX and WX MIC
 *	keys
 * @NW80211_ATTW_KEY_IDX: key ID (u8, 0-3)
 * @NW80211_ATTW_KEY_CIPHEW: key ciphew suite (u32, as defined by IEEE 802.11
 *	section 7.3.2.25.1, e.g. 0x000FAC04)
 * @NW80211_ATTW_KEY_SEQ: twansmit key sequence numbew (IV/PN) fow TKIP and
 *	CCMP keys, each six bytes in wittwe endian
 * @NW80211_ATTW_KEY_DEFAUWT: Fwag attwibute indicating the key is defauwt key
 * @NW80211_ATTW_KEY_DEFAUWT_MGMT: Fwag attwibute indicating the key is the
 *	defauwt management key
 * @NW80211_ATTW_CIPHEW_SUITES_PAIWWISE: Fow cwypto settings fow connect ow
 *	othew commands, indicates which paiwwise ciphew suites awe used
 * @NW80211_ATTW_CIPHEW_SUITE_GWOUP: Fow cwypto settings fow connect ow
 *	othew commands, indicates which gwoup ciphew suite is used
 *
 * @NW80211_ATTW_BEACON_INTEWVAW: beacon intewvaw in TU
 * @NW80211_ATTW_DTIM_PEWIOD: DTIM pewiod fow beaconing
 * @NW80211_ATTW_BEACON_HEAD: powtion of the beacon befowe the TIM IE
 * @NW80211_ATTW_BEACON_TAIW: powtion of the beacon aftew the TIM IE
 *
 * @NW80211_ATTW_STA_AID: Association ID fow the station (u16)
 * @NW80211_ATTW_STA_FWAGS: fwags, nested ewement with NWA_FWAG attwibutes of
 *	&enum nw80211_sta_fwags (depwecated, use %NW80211_ATTW_STA_FWAGS2)
 * @NW80211_ATTW_STA_WISTEN_INTEWVAW: wisten intewvaw as defined by
 *	IEEE 802.11 7.3.1.6 (u16).
 * @NW80211_ATTW_STA_SUPPOWTED_WATES: suppowted wates, awway of suppowted
 *	wates as defined by IEEE 802.11 7.3.2.2 but without the wength
 *	westwiction (at most %NW80211_MAX_SUPP_WATES).
 * @NW80211_ATTW_STA_VWAN: intewface index of VWAN intewface to move station
 *	to, ow the AP intewface the station was owiginawwy added to.
 * @NW80211_ATTW_STA_INFO: infowmation about a station, pawt of station info
 *	given fow %NW80211_CMD_GET_STATION, nested attwibute containing
 *	info as possibwe, see &enum nw80211_sta_info.
 *
 * @NW80211_ATTW_WIPHY_BANDS: Infowmation about an opewating bands,
 *	consisting of a nested awway.
 *
 * @NW80211_ATTW_MESH_ID: mesh id (1-32 bytes).
 * @NW80211_ATTW_STA_PWINK_ACTION: action to pewfowm on the mesh peew wink
 *	(see &enum nw80211_pwink_action).
 * @NW80211_ATTW_MPATH_NEXT_HOP: MAC addwess of the next hop fow a mesh path.
 * @NW80211_ATTW_MPATH_INFO: infowmation about a mesh_path, pawt of mesh path
 * 	info given fow %NW80211_CMD_GET_MPATH, nested attwibute descwibed at
 *	&enum nw80211_mpath_info.
 *
 * @NW80211_ATTW_MNTW_FWAGS: fwags, nested ewement with NWA_FWAG attwibutes of
 *      &enum nw80211_mntw_fwags.
 *
 * @NW80211_ATTW_WEG_AWPHA2: an ISO-3166-awpha2 countwy code fow which the
 * 	cuwwent weguwatowy domain shouwd be set to ow is awweady set to.
 * 	Fow exampwe, 'CW', fow Costa Wica. This attwibute is used by the kewnew
 * 	to quewy the CWDA to wetwieve one weguwatowy domain. This attwibute can
 * 	awso be used by usewspace to quewy the kewnew fow the cuwwentwy set
 * 	weguwatowy domain. We chose an awpha2 as that is awso used by the
 * 	IEEE-802.11 countwy infowmation ewement to identify a countwy.
 * 	Usews can awso simpwy ask the wiwewess cowe to set weguwatowy domain
 * 	to a specific awpha2.
 * @NW80211_ATTW_WEG_WUWES: a nested awway of weguwatowy domain weguwatowy
 *	wuwes.
 *
 * @NW80211_ATTW_BSS_CTS_PWOT: whethew CTS pwotection is enabwed (u8, 0 ow 1)
 * @NW80211_ATTW_BSS_SHOWT_PWEAMBWE: whethew showt pweambwe is enabwed
 *	(u8, 0 ow 1)
 * @NW80211_ATTW_BSS_SHOWT_SWOT_TIME: whethew showt swot time enabwed
 *	(u8, 0 ow 1)
 * @NW80211_ATTW_BSS_BASIC_WATES: basic wates, awway of basic
 *	wates in fowmat defined by IEEE 802.11 7.3.2.2 but without the wength
 *	westwiction (at most %NW80211_MAX_SUPP_WATES).
 *
 * @NW80211_ATTW_HT_CAPABIWITY: HT Capabiwity infowmation ewement (fwom
 *	association wequest when used with NW80211_CMD_NEW_STATION)
 *
 * @NW80211_ATTW_SUPPOWTED_IFTYPES: nested attwibute containing aww
 *	suppowted intewface types, each a fwag attwibute with the numbew
 *	of the intewface mode.
 *
 * @NW80211_ATTW_MGMT_SUBTYPE: Management fwame subtype fow
 *	%NW80211_CMD_SET_MGMT_EXTWA_IE.
 *
 * @NW80211_ATTW_IE: Infowmation ewement(s) data (used, e.g., with
 *	%NW80211_CMD_SET_MGMT_EXTWA_IE).
 *
 * @NW80211_ATTW_MAX_NUM_SCAN_SSIDS: numbew of SSIDs you can scan with
 *	a singwe scan wequest, a wiphy attwibute.
 * @NW80211_ATTW_MAX_NUM_SCHED_SCAN_SSIDS: numbew of SSIDs you can
 *	scan with a singwe scheduwed scan wequest, a wiphy attwibute.
 * @NW80211_ATTW_MAX_SCAN_IE_WEN: maximum wength of infowmation ewements
 *	that can be added to a scan wequest
 * @NW80211_ATTW_MAX_SCHED_SCAN_IE_WEN: maximum wength of infowmation
 *	ewements that can be added to a scheduwed scan wequest
 * @NW80211_ATTW_MAX_MATCH_SETS: maximum numbew of sets that can be
 *	used with @NW80211_ATTW_SCHED_SCAN_MATCH, a wiphy attwibute.
 *
 * @NW80211_ATTW_SCAN_FWEQUENCIES: nested attwibute with fwequencies (in MHz)
 * @NW80211_ATTW_SCAN_SSIDS: nested attwibute with SSIDs, weave out fow passive
 *	scanning and incwude a zewo-wength SSID (wiwdcawd) fow wiwdcawd scan
 * @NW80211_ATTW_BSS: scan wesuwt BSS
 *
 * @NW80211_ATTW_WEG_INITIATOW: indicates who wequested the weguwatowy domain
 * 	cuwwentwy in effect. This couwd be any of the %NW80211_WEGDOM_SET_BY_*
 * @NW80211_ATTW_WEG_TYPE: indicates the type of the weguwatowy domain cuwwentwy
 * 	set. This can be one of the nw80211_weg_type (%NW80211_WEGDOM_TYPE_*)
 *
 * @NW80211_ATTW_SUPPOWTED_COMMANDS: wiphy attwibute that specifies
 *	an awway of command numbews (i.e. a mapping index to command numbew)
 *	that the dwivew fow the given wiphy suppowts.
 *
 * @NW80211_ATTW_FWAME: fwame data (binawy attwibute), incwuding fwame headew
 *	and body, but not FCS; used, e.g., with NW80211_CMD_AUTHENTICATE and
 *	NW80211_CMD_ASSOCIATE events
 * @NW80211_ATTW_SSID: SSID (binawy attwibute, 0..32 octets)
 * @NW80211_ATTW_AUTH_TYPE: AuthenticationType, see &enum nw80211_auth_type,
 *	wepwesented as a u32
 * @NW80211_ATTW_WEASON_CODE: WeasonCode fow %NW80211_CMD_DEAUTHENTICATE and
 *	%NW80211_CMD_DISASSOCIATE, u16
 *
 * @NW80211_ATTW_KEY_TYPE: Key Type, see &enum nw80211_key_type, wepwesented as
 *	a u32
 *
 * @NW80211_ATTW_FWEQ_BEFOWE: A channew which has suffewed a weguwatowy change
 * 	due to considewations fwom a beacon hint. This attwibute wefwects
 * 	the state of the channew _befowe_ the beacon hint pwocessing. This
 * 	attwibutes consists of a nested attwibute containing
 * 	NW80211_FWEQUENCY_ATTW_*
 * @NW80211_ATTW_FWEQ_AFTEW: A channew which has suffewed a weguwatowy change
 * 	due to considewations fwom a beacon hint. This attwibute wefwects
 * 	the state of the channew _aftew_ the beacon hint pwocessing. This
 * 	attwibutes consists of a nested attwibute containing
 * 	NW80211_FWEQUENCY_ATTW_*
 *
 * @NW80211_ATTW_CIPHEW_SUITES: a set of u32 vawues indicating the suppowted
 *	ciphew suites
 *
 * @NW80211_ATTW_FWEQ_FIXED: a fwag indicating the IBSS shouwd not twy to wook
 *	fow othew netwowks on diffewent channews
 *
 * @NW80211_ATTW_TIMED_OUT: a fwag indicating than an opewation timed out; this
 *	is used, e.g., with %NW80211_CMD_AUTHENTICATE event
 *
 * @NW80211_ATTW_USE_MFP: Whethew management fwame pwotection (IEEE 802.11w) is
 *	used fow the association (&enum nw80211_mfp, wepwesented as a u32);
 *	this attwibute can be used with %NW80211_CMD_ASSOCIATE and
 *	%NW80211_CMD_CONNECT wequests. %NW80211_MFP_OPTIONAW is not awwowed fow
 *	%NW80211_CMD_ASSOCIATE since usew space SME is expected and hence, it
 *	must have decided whethew to use management fwame pwotection ow not.
 *	Setting %NW80211_MFP_OPTIONAW with a %NW80211_CMD_CONNECT wequest wiww
 *	wet the dwivew (ow the fiwmwawe) decide whethew to use MFP ow not.
 *
 * @NW80211_ATTW_STA_FWAGS2: Attwibute containing a
 *	&stwuct nw80211_sta_fwag_update.
 *
 * @NW80211_ATTW_CONTWOW_POWT: A fwag indicating whethew usew space contwows
 *	IEEE 802.1X powt, i.e., sets/cweaws %NW80211_STA_FWAG_AUTHOWIZED, in
 *	station mode. If the fwag is incwuded in %NW80211_CMD_ASSOCIATE
 *	wequest, the dwivew wiww assume that the powt is unauthowized untiw
 *	authowized by usew space. Othewwise, powt is mawked authowized by
 *	defauwt in station mode.
 * @NW80211_ATTW_CONTWOW_POWT_ETHEWTYPE: A 16-bit vawue indicating the
 *	ethewtype that wiww be used fow key negotiation. It can be
 *	specified with the associate and connect commands. If it is not
 *	specified, the vawue defauwts to 0x888E (PAE, 802.1X). This
 *	attwibute is awso used as a fwag in the wiphy infowmation to
 *	indicate that pwotocows othew than PAE awe suppowted.
 * @NW80211_ATTW_CONTWOW_POWT_NO_ENCWYPT: When incwuded awong with
 *	%NW80211_ATTW_CONTWOW_POWT_ETHEWTYPE, indicates that the custom
 *	ethewtype fwames used fow key negotiation must not be encwypted.
 * @NW80211_ATTW_CONTWOW_POWT_OVEW_NW80211: A fwag indicating whethew contwow
 *	powt fwames (e.g. of type given in %NW80211_ATTW_CONTWOW_POWT_ETHEWTYPE)
 *	wiww be sent diwectwy to the netwowk intewface ow sent via the NW80211
 *	socket.  If this attwibute is missing, then wegacy behaviow of sending
 *	contwow powt fwames diwectwy to the netwowk intewface is used.  If the
 *	fwag is incwuded, then contwow powt fwames awe sent ovew NW80211 instead
 *	using %CMD_CONTWOW_POWT_FWAME.  If contwow powt wouting ovew NW80211 is
 *	to be used then usewspace must awso use the %NW80211_ATTW_SOCKET_OWNEW
 *	fwag. When used with %NW80211_ATTW_CONTWOW_POWT_NO_PWEAUTH, pwe-auth
 *	fwames awe not fowwawded ovew the contwow powt.
 *
 * @NW80211_ATTW_TESTDATA: Testmode data bwob, passed thwough to the dwivew.
 *	We wecommend using nested, dwivew-specific attwibutes within this.
 *
 * @NW80211_ATTW_DISCONNECTED_BY_AP: A fwag indicating that the DISCONNECT
 *	event was due to the AP disconnecting the station, and not due to
 *	a wocaw disconnect wequest.
 * @NW80211_ATTW_STATUS_CODE: StatusCode fow the %NW80211_CMD_CONNECT
 *	event (u16)
 * @NW80211_ATTW_PWIVACY: Fwag attwibute, used with connect(), indicating
 *	that pwotected APs shouwd be used. This is awso used with NEW_BEACON to
 *	indicate that the BSS is to use pwotection.
 *
 * @NW80211_ATTW_CIPHEWS_PAIWWISE: Used with CONNECT, ASSOCIATE, and NEW_BEACON
 *	to indicate which unicast key ciphews wiww be used with the connection
 *	(an awway of u32).
 * @NW80211_ATTW_CIPHEW_GWOUP: Used with CONNECT, ASSOCIATE, and NEW_BEACON to
 *	indicate which gwoup key ciphew wiww be used with the connection (a
 *	u32).
 * @NW80211_ATTW_WPA_VEWSIONS: Used with CONNECT, ASSOCIATE, and NEW_BEACON to
 *	indicate which WPA vewsion(s) the AP we want to associate with is using
 *	(a u32 with fwags fwom &enum nw80211_wpa_vewsions).
 * @NW80211_ATTW_AKM_SUITES: Used with CONNECT, ASSOCIATE, and NEW_BEACON to
 *	indicate which key management awgowithm(s) to use (an awway of u32).
 *	This attwibute is awso sent in wesponse to @NW80211_CMD_GET_WIPHY,
 *	indicating the suppowted AKM suites, intended fow specific dwivews which
 *	impwement SME and have constwaints on which AKMs awe suppowted and awso
 *	the cases whewe an AKM suppowt is offwoaded to the dwivew/fiwmwawe.
 *	If thewe is no such notification fwom the dwivew, usew space shouwd
 *	assume the dwivew suppowts aww the AKM suites.
 *
 * @NW80211_ATTW_WEQ_IE: (We)association wequest infowmation ewements as
 *	sent out by the cawd, fow WOAM and successfuw CONNECT events.
 * @NW80211_ATTW_WESP_IE: (We)association wesponse infowmation ewements as
 *	sent by peew, fow WOAM and successfuw CONNECT events.
 *
 * @NW80211_ATTW_PWEV_BSSID: pwevious BSSID, to be used in ASSOCIATE and CONNECT
 *	commands to specify a wequest to weassociate within an ESS, i.e., to use
 *	Weassociate Wequest fwame (with the vawue of this attwibute in the
 *	Cuwwent AP addwess fiewd) instead of Association Wequest fwame which is
 *	used fow the initiaw association to an ESS.
 *
 * @NW80211_ATTW_KEY: key infowmation in a nested attwibute with
 *	%NW80211_KEY_* sub-attwibutes
 * @NW80211_ATTW_KEYS: awway of keys fow static WEP keys fow connect()
 *	and join_ibss(), key infowmation is in a nested attwibute each
 *	with %NW80211_KEY_* sub-attwibutes
 *
 * @NW80211_ATTW_PID: Pwocess ID of a netwowk namespace.
 *
 * @NW80211_ATTW_GENEWATION: Used to indicate consistent snapshots fow
 *	dumps. This numbew incweases whenevew the object wist being
 *	dumped changes, and as such usewspace can vewify that it has
 *	obtained a compwete and consistent snapshot by vewifying that
 *	aww dump messages contain the same genewation numbew. If it
 *	changed then the wist changed and the dump shouwd be wepeated
 *	compwetewy fwom scwatch.
 *
 * @NW80211_ATTW_4ADDW: Use 4-addwess fwames on a viwtuaw intewface
 *
 * @NW80211_ATTW_SUWVEY_INFO: suwvey infowmation about a channew, pawt of
 *      the suwvey wesponse fow %NW80211_CMD_GET_SUWVEY, nested attwibute
 *      containing info as possibwe, see &enum suwvey_info.
 *
 * @NW80211_ATTW_PMKID: PMK matewiaw fow PMKSA caching.
 * @NW80211_ATTW_MAX_NUM_PMKIDS: maximum numbew of PMKIDs a fiwmwawe can
 *	cache, a wiphy attwibute.
 *
 * @NW80211_ATTW_DUWATION: Duwation of an opewation in miwwiseconds, u32.
 * @NW80211_ATTW_MAX_WEMAIN_ON_CHANNEW_DUWATION: Device attwibute that
 *	specifies the maximum duwation that can be wequested with the
 *	wemain-on-channew opewation, in miwwiseconds, u32.
 *
 * @NW80211_ATTW_COOKIE: Genewic 64-bit cookie to identify objects.
 *
 * @NW80211_ATTW_TX_WATES: Nested set of attwibutes
 *	(enum nw80211_tx_wate_attwibutes) descwibing TX wates pew band. The
 *	enum nw80211_band vawue is used as the index (nwa_type() of the nested
 *	data. If a band is not incwuded, it wiww be configuwed to awwow aww
 *	wates based on negotiated suppowted wates infowmation. This attwibute
 *	is used with %NW80211_CMD_SET_TX_BITWATE_MASK and with stawting AP,
 *	and joining mesh netwowks (not IBSS yet). In the watew case, it must
 *	specify just a singwe bitwate, which is to be used fow the beacon.
 *	The dwivew must awso specify suppowt fow this with the extended
 *	featuwes NW80211_EXT_FEATUWE_BEACON_WATE_WEGACY,
 *	NW80211_EXT_FEATUWE_BEACON_WATE_HT,
 *	NW80211_EXT_FEATUWE_BEACON_WATE_VHT and
 *	NW80211_EXT_FEATUWE_BEACON_WATE_HE.
 *
 * @NW80211_ATTW_FWAME_MATCH: A binawy attwibute which typicawwy must contain
 *	at weast one byte, cuwwentwy used with @NW80211_CMD_WEGISTEW_FWAME.
 * @NW80211_ATTW_FWAME_TYPE: A u16 indicating the fwame type/subtype fow the
 *	@NW80211_CMD_WEGISTEW_FWAME command.
 * @NW80211_ATTW_TX_FWAME_TYPES: wiphy capabiwity attwibute, which is a
 *	nested attwibute of %NW80211_ATTW_FWAME_TYPE attwibutes, containing
 *	infowmation about which fwame types can be twansmitted with
 *	%NW80211_CMD_FWAME.
 * @NW80211_ATTW_WX_FWAME_TYPES: wiphy capabiwity attwibute, which is a
 *	nested attwibute of %NW80211_ATTW_FWAME_TYPE attwibutes, containing
 *	infowmation about which fwame types can be wegistewed fow WX.
 *
 * @NW80211_ATTW_ACK: Fwag attwibute indicating that the fwame was
 *	acknowwedged by the wecipient.
 *
 * @NW80211_ATTW_PS_STATE: powewsave state, using &enum nw80211_ps_state vawues.
 *
 * @NW80211_ATTW_CQM: connection quawity monitow configuwation in a
 *	nested attwibute with %NW80211_ATTW_CQM_* sub-attwibutes.
 *
 * @NW80211_ATTW_WOCAW_STATE_CHANGE: Fwag attwibute to indicate that a command
 *	is wequesting a wocaw authentication/association state change without
 *	invoking actuaw management fwame exchange. This can be used with
 *	NW80211_CMD_AUTHENTICATE, NW80211_CMD_DEAUTHENTICATE,
 *	NW80211_CMD_DISASSOCIATE.
 *
 * @NW80211_ATTW_AP_ISOWATE: (AP mode) Do not fowwawd twaffic between stations
 *	connected to this BSS.
 *
 * @NW80211_ATTW_WIPHY_TX_POWEW_SETTING: Twansmit powew setting type. See
 *      &enum nw80211_tx_powew_setting fow possibwe vawues.
 * @NW80211_ATTW_WIPHY_TX_POWEW_WEVEW: Twansmit powew wevew in signed mBm units.
 *      This is used in association with @NW80211_ATTW_WIPHY_TX_POWEW_SETTING
 *      fow non-automatic settings.
 *
 * @NW80211_ATTW_SUPPOWT_IBSS_WSN: The device suppowts IBSS WSN, which mostwy
 *	means suppowt fow pew-station GTKs.
 *
 * @NW80211_ATTW_WIPHY_ANTENNA_TX: Bitmap of awwowed antennas fow twansmitting.
 *	This can be used to mask out antennas which awe not attached ow shouwd
 *	not be used fow twansmitting. If an antenna is not sewected in this
 *	bitmap the hawdwawe is not awwowed to twansmit on this antenna.
 *
 *	Each bit wepwesents one antenna, stawting with antenna 1 at the fiwst
 *	bit. Depending on which antennas awe sewected in the bitmap, 802.11n
 *	dwivews can dewive which chainmasks to use (if aww antennas bewonging to
 *	a pawticuwaw chain awe disabwed this chain shouwd be disabwed) and if
 *	a chain has divewsity antennas whethew divewsity shouwd be used ow not.
 *	HT capabiwities (STBC, TX Beamfowming, Antenna sewection) can be
 *	dewived fwom the avaiwabwe chains aftew appwying the antenna mask.
 *	Non-802.11n dwivews can dewive whethew to use divewsity ow not.
 *	Dwivews may weject configuwations ow WX/TX mask combinations they cannot
 *	suppowt by wetuwning -EINVAW.
 *
 * @NW80211_ATTW_WIPHY_ANTENNA_WX: Bitmap of awwowed antennas fow weceiving.
 *	This can be used to mask out antennas which awe not attached ow shouwd
 *	not be used fow weceiving. If an antenna is not sewected in this bitmap
 *	the hawdwawe shouwd not be configuwed to weceive on this antenna.
 *	Fow a mowe detaiwed descwiption see @NW80211_ATTW_WIPHY_ANTENNA_TX.
 *
 * @NW80211_ATTW_WIPHY_ANTENNA_AVAIW_TX: Bitmap of antennas which awe avaiwabwe
 *	fow configuwation as TX antennas via the above pawametews.
 *
 * @NW80211_ATTW_WIPHY_ANTENNA_AVAIW_WX: Bitmap of antennas which awe avaiwabwe
 *	fow configuwation as WX antennas via the above pawametews.
 *
 * @NW80211_ATTW_MCAST_WATE: Muwticast tx wate (in 100 kbps) fow IBSS
 *
 * @NW80211_ATTW_OFFCHANNEW_TX_OK: Fow management fwame TX, the fwame may be
 *	twansmitted on anothew channew when the channew given doesn't match
 *	the cuwwent channew. If the cuwwent channew doesn't match and this
 *	fwag isn't set, the fwame wiww be wejected. This is awso used as an
 *	nw80211 capabiwity fwag.
 *
 * @NW80211_ATTW_BSS_HT_OPMODE: HT opewation mode (u16)
 *
 * @NW80211_ATTW_KEY_DEFAUWT_TYPES: A nested attwibute containing fwags
 *	attwibutes, specifying what a key shouwd be set as defauwt as.
 *	See &enum nw80211_key_defauwt_types.
 *
 * @NW80211_ATTW_MESH_SETUP: Optionaw mesh setup pawametews.  These cannot be
 *	changed once the mesh is active.
 * @NW80211_ATTW_MESH_CONFIG: Mesh configuwation pawametews, a nested attwibute
 *	containing attwibutes fwom &enum nw80211_meshconf_pawams.
 * @NW80211_ATTW_SUPPOWT_MESH_AUTH: Cuwwentwy, this means the undewwying dwivew
 *	awwows auth fwames in a mesh to be passed to usewspace fow pwocessing via
 *	the @NW80211_MESH_SETUP_USEWSPACE_AUTH fwag.
 * @NW80211_ATTW_STA_PWINK_STATE: The state of a mesh peew wink as defined in
 *	&enum nw80211_pwink_state. Used when usewspace is dwiving the peew wink
 *	management state machine.  @NW80211_MESH_SETUP_USEWSPACE_AMPE ow
 *	@NW80211_MESH_SETUP_USEWSPACE_MPM must be enabwed.
 *
 * @NW80211_ATTW_WOWWAN_TWIGGEWS_SUPPOWTED: indicates, as pawt of the wiphy
 *	capabiwities, the suppowted WoWWAN twiggews
 * @NW80211_ATTW_WOWWAN_TWIGGEWS: used by %NW80211_CMD_SET_WOWWAN to
 *	indicate which WoW twiggews shouwd be enabwed. This is awso
 *	used by %NW80211_CMD_GET_WOWWAN to get the cuwwentwy enabwed WoWWAN
 *	twiggews.
 *
 * @NW80211_ATTW_SCHED_SCAN_INTEWVAW: Intewvaw between scheduwed scan
 *	cycwes, in msecs.
 *
 * @NW80211_ATTW_SCHED_SCAN_MATCH: Nested attwibute with one ow mowe
 *	sets of attwibutes to match duwing scheduwed scans.  Onwy BSSs
 *	that match any of the sets wiww be wepowted.  These awe
 *	pass-thwu fiwtew wuwes.
 *	Fow a match to succeed, the BSS must match aww attwibutes of a
 *	set.  Since not evewy hawdwawe suppowts matching aww types of
 *	attwibutes, thewe is no guawantee that the wepowted BSSs awe
 *	fuwwy compwying with the match sets and usewspace needs to be
 *	abwe to ignowe them by itsewf.
 *	Thus, the impwementation is somewhat hawdwawe-dependent, but
 *	this is onwy an optimization and the usewspace appwication
 *	needs to handwe aww the non-fiwtewed wesuwts anyway.
 *	If the match attwibutes don't make sense when combined with
 *	the vawues passed in @NW80211_ATTW_SCAN_SSIDS (eg. if an SSID
 *	is incwuded in the pwobe wequest, but the match attwibutes
 *	wiww nevew wet it go thwough), -EINVAW may be wetuwned.
 *	If omitted, no fiwtewing is done.
 *
 * @NW80211_ATTW_INTEWFACE_COMBINATIONS: Nested attwibute wisting the suppowted
 *	intewface combinations. In each nested item, it contains attwibutes
 *	defined in &enum nw80211_if_combination_attws.
 * @NW80211_ATTW_SOFTWAWE_IFTYPES: Nested attwibute (just wike
 *	%NW80211_ATTW_SUPPOWTED_IFTYPES) containing the intewface types that
 *	awe managed in softwawe: intewfaces of these types awen't subject to
 *	any westwictions in theiw numbew ow combinations.
 *
 * @NW80211_ATTW_WEKEY_DATA: nested attwibute containing the infowmation
 *	necessawy fow GTK wekeying in the device, see &enum nw80211_wekey_data.
 *
 * @NW80211_ATTW_SCAN_SUPP_WATES: wates pew to be advewtised as suppowted in scan,
 *	nested awway attwibute containing an entwy fow each band, with the entwy
 *	being a wist of suppowted wates as defined by IEEE 802.11 7.3.2.2 but
 *	without the wength westwiction (at most %NW80211_MAX_SUPP_WATES).
 *
 * @NW80211_ATTW_HIDDEN_SSID: indicates whethew SSID is to be hidden fwom Beacon
 *	and Pwobe Wesponse (when wesponse to wiwdcawd Pwobe Wequest); see
 *	&enum nw80211_hidden_ssid, wepwesented as a u32
 *
 * @NW80211_ATTW_IE_PWOBE_WESP: Infowmation ewement(s) fow Pwobe Wesponse fwame.
 *	This is used with %NW80211_CMD_NEW_BEACON and %NW80211_CMD_SET_BEACON to
 *	pwovide extwa IEs (e.g., WPS/P2P IE) into Pwobe Wesponse fwames when the
 *	dwivew (ow fiwmwawe) wepwies to Pwobe Wequest fwames.
 * @NW80211_ATTW_IE_ASSOC_WESP: Infowmation ewement(s) fow (We)Association
 *	Wesponse fwames. This is used with %NW80211_CMD_NEW_BEACON and
 *	%NW80211_CMD_SET_BEACON to pwovide extwa IEs (e.g., WPS/P2P IE) into
 *	(We)Association Wesponse fwames when the dwivew (ow fiwmwawe) wepwies to
 *	(We)Association Wequest fwames.
 *
 * @NW80211_ATTW_STA_WME: Nested attwibute containing the wme configuwation
 *	of the station, see &enum nw80211_sta_wme_attw.
 * @NW80211_ATTW_SUPPOWT_AP_UAPSD: the device suppowts uapsd when wowking
 *	as AP.
 *
 * @NW80211_ATTW_WOAM_SUPPOWT: Indicates whethew the fiwmwawe is capabwe of
 *	woaming to anothew AP in the same ESS if the signaw wevew is wow.
 *
 * @NW80211_ATTW_PMKSA_CANDIDATE: Nested attwibute containing the PMKSA caching
 *	candidate infowmation, see &enum nw80211_pmksa_candidate_attw.
 *
 * @NW80211_ATTW_TX_NO_CCK_WATE: Indicates whethew to use CCK wate ow not
 *	fow management fwames twansmission. In owdew to avoid p2p pwobe/action
 *	fwames awe being twansmitted at CCK wate in 2GHz band, the usew space
 *	appwications use this attwibute.
 *	This attwibute is used with %NW80211_CMD_TWIGGEW_SCAN and
 *	%NW80211_CMD_FWAME commands.
 *
 * @NW80211_ATTW_TDWS_ACTION: Wow wevew TDWS action code (e.g. wink setup
 *	wequest, wink setup confiwm, wink teawdown, etc.). Vawues awe
 *	descwibed in the TDWS (802.11z) specification.
 * @NW80211_ATTW_TDWS_DIAWOG_TOKEN: Non-zewo token fow uniquewy identifying a
 *	TDWS convewsation between two devices.
 * @NW80211_ATTW_TDWS_OPEWATION: High wevew TDWS opewation; see
 *	&enum nw80211_tdws_opewation, wepwesented as a u8.
 * @NW80211_ATTW_TDWS_SUPPOWT: A fwag indicating the device can opewate
 *	as a TDWS peew sta.
 * @NW80211_ATTW_TDWS_EXTEWNAW_SETUP: The TDWS discovewy/setup and teawdown
 *	pwoceduwes shouwd be pewfowmed by sending TDWS packets via
 *	%NW80211_CMD_TDWS_MGMT. Othewwise %NW80211_CMD_TDWS_OPEW shouwd be
 *	used fow asking the dwivew to pewfowm a TDWS opewation.
 *
 * @NW80211_ATTW_DEVICE_AP_SME: This u32 attwibute may be wisted fow devices
 *	that have AP suppowt to indicate that they have the AP SME integwated
 *	with suppowt fow the featuwes wisted in this attwibute, see
 *	&enum nw80211_ap_sme_featuwes.
 *
 * @NW80211_ATTW_DONT_WAIT_FOW_ACK: Used with %NW80211_CMD_FWAME, this tewws
 *	the dwivew to not wait fow an acknowwedgement. Note that due to this,
 *	it wiww awso not give a status cawwback now wetuwn a cookie. This is
 *	mostwy usefuw fow pwobe wesponses to save aiwtime.
 *
 * @NW80211_ATTW_FEATUWE_FWAGS: This u32 attwibute contains fwags fwom
 *	&enum nw80211_featuwe_fwags and is advewtised in wiphy infowmation.
 * @NW80211_ATTW_PWOBE_WESP_OFFWOAD: Indicates that the HW wesponds to pwobe
 *	wequests whiwe opewating in AP-mode.
 *	This attwibute howds a bitmap of the suppowted pwotocows fow
 *	offwoading (see &enum nw80211_pwobe_wesp_offwoad_suppowt_attw).
 *
 * @NW80211_ATTW_PWOBE_WESP: Pwobe Wesponse tempwate data. Contains the entiwe
 *	pwobe-wesponse fwame. The DA fiewd in the 802.11 headew is zewo-ed out,
 *	to be fiwwed by the FW.
 * @NW80211_ATTW_DISABWE_HT: Fowce HT capabwe intewfaces to disabwe
 *      this featuwe duwing association. This is a fwag attwibute.
 *	Cuwwentwy onwy suppowted in mac80211 dwivews.
 * @NW80211_ATTW_DISABWE_VHT: Fowce VHT capabwe intewfaces to disabwe
 *      this featuwe duwing association. This is a fwag attwibute.
 *	Cuwwentwy onwy suppowted in mac80211 dwivews.
 * @NW80211_ATTW_DISABWE_HE: Fowce HE capabwe intewfaces to disabwe
 *      this featuwe duwing association. This is a fwag attwibute.
 *	Cuwwentwy onwy suppowted in mac80211 dwivews.
 * @NW80211_ATTW_HT_CAPABIWITY_MASK: Specify which bits of the
 *      ATTW_HT_CAPABIWITY to which attention shouwd be paid.
 *      Cuwwentwy, onwy mac80211 NICs suppowt this featuwe.
 *      The vawues that may be configuwed awe:
 *       MCS wates, MAX-AMSDU, HT-20-40 and HT_CAP_SGI_40
 *       AMPDU density and AMPDU factow.
 *      Aww vawues awe tweated as suggestions and may be ignowed
 *      by the dwivew as wequiwed.  The actuaw vawues may be seen in
 *      the station debugfs ht_caps fiwe.
 *
 * @NW80211_ATTW_DFS_WEGION: wegion fow weguwatowy wuwes which this countwy
 *    abides to when initiating wadiation on DFS channews. A countwy maps
 *    to one DFS wegion.
 *
 * @NW80211_ATTW_NOACK_MAP: This u16 bitmap contains the No Ack Powicy of
 *      up to 16 TIDs.
 *
 * @NW80211_ATTW_INACTIVITY_TIMEOUT: timeout vawue in seconds, this can be
 *	used by the dwivews which has MWME in fiwmwawe and does not have suppowt
 *	to wepowt pew station tx/wx activity to fwee up the station entwy fwom
 *	the wist. This needs to be used when the dwivew advewtises the
 *	capabiwity to timeout the stations.
 *
 * @NW80211_ATTW_WX_SIGNAW_DBM: signaw stwength in dBm (as a 32-bit int);
 *	this attwibute is (depending on the dwivew capabiwities) added to
 *	weceived fwames indicated with %NW80211_CMD_FWAME.
 *
 * @NW80211_ATTW_BG_SCAN_PEWIOD: Backgwound scan pewiod in seconds
 *      ow 0 to disabwe backgwound scan.
 *
 * @NW80211_ATTW_USEW_WEG_HINT_TYPE: type of weguwatowy hint passed fwom
 *	usewspace. If unset it is assumed the hint comes diwectwy fwom
 *	a usew. If set code couwd specify exactwy what type of souwce
 *	was used to pwovide the hint. Fow the diffewent types of
 *	awwowed usew weguwatowy hints see nw80211_usew_weg_hint_type.
 *
 * @NW80211_ATTW_CONN_FAIWED_WEASON: The weason fow which AP has wejected
 *	the connection wequest fwom a station. nw80211_connect_faiwed_weason
 *	enum has diffewent weasons of connection faiwuwe.
 *
 * @NW80211_ATTW_AUTH_DATA: Fiewds and ewements in Authentication fwames.
 *	This contains the authentication fwame body (non-IE and IE data),
 *	excwuding the Authentication awgowithm numbew, i.e., stawting at the
 *	Authentication twansaction sequence numbew fiewd. It is used with
 *	authentication awgowithms that need speciaw fiewds to be added into
 *	the fwames (SAE and FIWS). Cuwwentwy, onwy the SAE cases use the
 *	initiaw two fiewds (Authentication twansaction sequence numbew and
 *	Status code). Howevew, those fiewds awe incwuded in the attwibute data
 *	fow aww authentication awgowithms to keep the attwibute definition
 *	consistent.
 *
 * @NW80211_ATTW_VHT_CAPABIWITY: VHT Capabiwity infowmation ewement (fwom
 *	association wequest when used with NW80211_CMD_NEW_STATION)
 *
 * @NW80211_ATTW_SCAN_FWAGS: scan wequest contwow fwags (u32)
 *
 * @NW80211_ATTW_P2P_CTWINDOW: P2P GO Cwient Twaffic Window (u8), used with
 *	the STAWT_AP and SET_BSS commands
 * @NW80211_ATTW_P2P_OPPPS: P2P GO oppowtunistic PS (u8), used with the
 *	STAWT_AP and SET_BSS commands. This can have the vawues 0 ow 1;
 *	if not given in STAWT_AP 0 is assumed, if not given in SET_BSS
 *	no change is made.
 *
 * @NW80211_ATTW_WOCAW_MESH_POWEW_MODE: wocaw mesh STA wink-specific powew mode
 *	defined in &enum nw80211_mesh_powew_mode.
 *
 * @NW80211_ATTW_ACW_POWICY: ACW powicy, see &enum nw80211_acw_powicy,
 *	cawwied in a u32 attwibute
 *
 * @NW80211_ATTW_MAC_ADDWS: Awway of nested MAC addwesses, used fow
 *	MAC ACW.
 *
 * @NW80211_ATTW_MAC_ACW_MAX: u32 attwibute to advewtise the maximum
 *	numbew of MAC addwesses that a device can suppowt fow MAC
 *	ACW.
 *
 * @NW80211_ATTW_WADAW_EVENT: Type of wadaw event fow notification to usewspace,
 *	contains a vawue of enum nw80211_wadaw_event (u32).
 *
 * @NW80211_ATTW_EXT_CAPA: 802.11 extended capabiwities that the kewnew dwivew
 *	has and handwes. The fowmat is the same as the IE contents. See
 *	802.11-2012 8.4.2.29 fow mowe infowmation.
 * @NW80211_ATTW_EXT_CAPA_MASK: Extended capabiwities that the kewnew dwivew
 *	has set in the %NW80211_ATTW_EXT_CAPA vawue, fow muwtibit fiewds.
 *
 * @NW80211_ATTW_STA_CAPABIWITY: Station capabiwities (u16) awe advewtised to
 *	the dwivew, e.g., to enabwe TDWS powew save (PU-APSD).
 *
 * @NW80211_ATTW_STA_EXT_CAPABIWITY: Station extended capabiwities awe
 *	advewtised to the dwivew, e.g., to enabwe TDWS off channew opewations
 *	and PU-APSD.
 *
 * @NW80211_ATTW_PWOTOCOW_FEATUWES: gwobaw nw80211 featuwe fwags, see
 *	&enum nw80211_pwotocow_featuwes, the attwibute is a u32.
 *
 * @NW80211_ATTW_SPWIT_WIPHY_DUMP: fwag attwibute, usewspace suppowts
 *	weceiving the data fow a singwe wiphy spwit acwoss muwtipwe
 *	messages, given with wiphy dump message
 *
 * @NW80211_ATTW_MDID: Mobiwity Domain Identifiew
 *
 * @NW80211_ATTW_IE_WIC: Wesouwce Infowmation Containew Infowmation
 *	Ewement
 *
 * @NW80211_ATTW_CWIT_PWOT_ID: cwiticaw pwotocow identifiew wequiwing incweased
 *	wewiabiwity, see &enum nw80211_cwit_pwoto_id (u16).
 * @NW80211_ATTW_MAX_CWIT_PWOT_DUWATION: duwation in miwwiseconds in which
 *      the connection shouwd have incweased wewiabiwity (u16).
 *
 * @NW80211_ATTW_PEEW_AID: Association ID fow the peew TDWS station (u16).
 *	This is simiwaw to @NW80211_ATTW_STA_AID but with a diffewence of being
 *	awwowed to be used with the fiwst @NW80211_CMD_SET_STATION command to
 *	update a TDWS peew STA entwy.
 *
 * @NW80211_ATTW_COAWESCE_WUWE: Coawesce wuwe infowmation.
 *
 * @NW80211_ATTW_CH_SWITCH_COUNT: u32 attwibute specifying the numbew of TBTT's
 *	untiw the channew switch event.
 * @NW80211_ATTW_CH_SWITCH_BWOCK_TX: fwag attwibute specifying that twansmission
 *	must be bwocked on the cuwwent channew (befowe the channew switch
 *	opewation). Awso incwuded in the channew switch stawted event if quiet
 *	was wequested by the AP.
 * @NW80211_ATTW_CSA_IES: Nested set of attwibutes containing the IE infowmation
 *	fow the time whiwe pewfowming a channew switch.
 * @NW80211_ATTW_CNTDWN_OFFS_BEACON: An awway of offsets (u16) to the channew
 *	switch ow cowow change countews in the beacons taiw (%NW80211_ATTW_BEACON_TAIW).
 * @NW80211_ATTW_CNTDWN_OFFS_PWESP: An awway of offsets (u16) to the channew
 *	switch ow cowow change countews in the pwobe wesponse (%NW80211_ATTW_PWOBE_WESP).
 *
 * @NW80211_ATTW_WXMGMT_FWAGS: fwags fow nw80211_send_mgmt(), u32.
 *	As specified in the &enum nw80211_wxmgmt_fwags.
 *
 * @NW80211_ATTW_STA_SUPPOWTED_CHANNEWS: awway of suppowted channews.
 *
 * @NW80211_ATTW_STA_SUPPOWTED_OPEW_CWASSES: awway of suppowted
 *      opewating cwasses.
 *
 * @NW80211_ATTW_HANDWE_DFS: A fwag indicating whethew usew space
 *	contwows DFS opewation in IBSS mode. If the fwag is incwuded in
 *	%NW80211_CMD_JOIN_IBSS wequest, the dwivew wiww awwow use of DFS
 *	channews and wepowts wadaw events to usewspace. Usewspace is wequiwed
 *	to weact to wadaw events, e.g. initiate a channew switch ow weave the
 *	IBSS netwowk.
 *
 * @NW80211_ATTW_SUPPOWT_5_MHZ: A fwag indicating that the device suppowts
 *	5 MHz channew bandwidth.
 * @NW80211_ATTW_SUPPOWT_10_MHZ: A fwag indicating that the device suppowts
 *	10 MHz channew bandwidth.
 *
 * @NW80211_ATTW_OPMODE_NOTIF: Opewating mode fiewd fwom Opewating Mode
 *	Notification Ewement based on association wequest when used with
 *	%NW80211_CMD_NEW_STATION ow %NW80211_CMD_SET_STATION (onwy when
 *	%NW80211_FEATUWE_FUWW_AP_CWIENT_STATE is suppowted, ow with TDWS);
 *	u8 attwibute.
 *
 * @NW80211_ATTW_VENDOW_ID: The vendow ID, eithew a 24-bit OUI ow, if
 *	%NW80211_VENDOW_ID_IS_WINUX is set, a speciaw Winux ID (not used yet)
 * @NW80211_ATTW_VENDOW_SUBCMD: vendow sub-command
 * @NW80211_ATTW_VENDOW_DATA: data fow the vendow command, if any; this
 *	attwibute is awso used fow vendow command featuwe advewtisement
 * @NW80211_ATTW_VENDOW_EVENTS: used fow event wist advewtising in the wiphy
 *	info, containing a nested awway of possibwe events
 *
 * @NW80211_ATTW_QOS_MAP: IP DSCP mapping fow Intewwowking QoS mapping. This
 *	data is in the fowmat defined fow the paywoad of the QoS Map Set ewement
 *	in IEEE Std 802.11-2012, 8.4.2.97.
 *
 * @NW80211_ATTW_MAC_HINT: MAC addwess wecommendation as initiaw BSS
 * @NW80211_ATTW_WIPHY_FWEQ_HINT: fwequency of the wecommended initiaw BSS
 *
 * @NW80211_ATTW_MAX_AP_ASSOC_STA: Device attwibute that indicates how many
 *	associated stations awe suppowted in AP mode (incwuding P2P GO); u32.
 *	Since dwivews may not have a fixed wimit on the maximum numbew (e.g.,
 *	othew concuwwent opewations may affect this), dwivews awe awwowed to
 *	advewtise vawues that cannot awways be met. In such cases, an attempt
 *	to add a new station entwy with @NW80211_CMD_NEW_STATION may faiw.
 *
 * @NW80211_ATTW_CSA_C_OFFSETS_TX: An awway of csa countew offsets (u16) which
 *	shouwd be updated when the fwame is twansmitted.
 * @NW80211_ATTW_MAX_CSA_COUNTEWS: U8 attwibute used to advewtise the maximum
 *	suppowted numbew of csa countews.
 *
 * @NW80211_ATTW_TDWS_PEEW_CAPABIWITY: fwags fow TDWS peew capabiwities, u32.
 *	As specified in the &enum nw80211_tdws_peew_capabiwity.
 *
 * @NW80211_ATTW_SOCKET_OWNEW: Fwag attwibute, if set duwing intewface
 *	cweation then the new intewface wiww be owned by the netwink socket
 *	that cweated it and wiww be destwoyed when the socket is cwosed.
 *	If set duwing scheduwed scan stawt then the new scan weq wiww be
 *	owned by the netwink socket that cweated it and the scheduwed scan wiww
 *	be stopped when the socket is cwosed.
 *	If set duwing configuwation of weguwatowy indoow opewation then the
 *	weguwatowy indoow configuwation wouwd be owned by the netwink socket
 *	that configuwed the indoow setting, and the indoow opewation wouwd be
 *	cweawed when the socket is cwosed.
 *	If set duwing NAN intewface cweation, the intewface wiww be destwoyed
 *	if the socket is cwosed just wike any othew intewface. Moweovew, NAN
 *	notifications wiww be sent in unicast to that socket. Without this
 *	attwibute, the notifications wiww be sent to the %NW80211_MCGWP_NAN
 *	muwticast gwoup.
 *	If set duwing %NW80211_CMD_ASSOCIATE ow %NW80211_CMD_CONNECT the
 *	station wiww deauthenticate when the socket is cwosed.
 *	If set duwing %NW80211_CMD_JOIN_IBSS the IBSS wiww be automaticawwy
 *	town down when the socket is cwosed.
 *	If set duwing %NW80211_CMD_JOIN_MESH the mesh setup wiww be
 *	automaticawwy town down when the socket is cwosed.
 *	If set duwing %NW80211_CMD_STAWT_AP the AP wiww be automaticawwy
 *	disabwed when the socket is cwosed.
 *
 * @NW80211_ATTW_TDWS_INITIATOW: fwag attwibute indicating the cuwwent end is
 *	the TDWS wink initiatow.
 *
 * @NW80211_ATTW_USE_WWM: fwag fow indicating whethew the cuwwent connection
 *	shaww suppowt Wadio Wesouwce Measuwements (11k). This attwibute can be
 *	used with %NW80211_CMD_ASSOCIATE and %NW80211_CMD_CONNECT wequests.
 *	Usew space appwications awe expected to use this fwag onwy if the
 *	undewwying device suppowts these minimaw WWM featuwes:
 *		%NW80211_FEATUWE_DS_PAWAM_SET_IE_IN_PWOBES,
 *		%NW80211_FEATUWE_QUIET,
 *	Ow, if gwobaw WWM is suppowted, see:
 *		%NW80211_EXT_FEATUWE_WWM
 *	If this fwag is used, dwivew must add the Powew Capabiwities IE to the
 *	association wequest. In addition, it must awso set the WWM capabiwity
 *	fwag in the association wequest's Capabiwity Info fiewd.
 *
 * @NW80211_ATTW_WIPHY_DYN_ACK: fwag attwibute used to enabwe ACK timeout
 *	estimation awgowithm (dynack). In owdew to activate dynack
 *	%NW80211_FEATUWE_ACKTO_ESTIMATION featuwe fwag must be set by wowew
 *	dwivews to indicate dynack capabiwity. Dynack is automaticawwy disabwed
 *	setting vawid vawue fow covewage cwass.
 *
 * @NW80211_ATTW_TSID: a TSID vawue (u8 attwibute)
 * @NW80211_ATTW_USEW_PWIO: usew pwiowity vawue (u8 attwibute)
 * @NW80211_ATTW_ADMITTED_TIME: admitted time in units of 32 micwoseconds
 *	(pew second) (u16 attwibute)
 *
 * @NW80211_ATTW_SMPS_MODE: SMPS mode to use (ap mode). see
 *	&enum nw80211_smps_mode.
 *
 * @NW80211_ATTW_OPEW_CWASS: opewating cwass
 *
 * @NW80211_ATTW_MAC_MASK: MAC addwess mask
 *
 * @NW80211_ATTW_WIPHY_SEWF_MANAGED_WEG: fwag attwibute indicating this device
 *	is sewf-managing its weguwatowy infowmation and any weguwatowy domain
 *	obtained fwom it is coming fwom the device's wiphy and not the gwobaw
 *	cfg80211 wegdomain.
 *
 * @NW80211_ATTW_EXT_FEATUWES: extended featuwe fwags contained in a byte
 *	awway. The featuwe fwags awe identified by theiw bit index (see &enum
 *	nw80211_ext_featuwe_index). The bit index is owdewed stawting at the
 *	weast-significant bit of the fiwst byte in the awway, ie. bit index 0
 *	is wocated at bit 0 of byte 0. bit index 25 wouwd be wocated at bit 1
 *	of byte 3 (u8 awway).
 *
 * @NW80211_ATTW_SUWVEY_WADIO_STATS: Wequest ovewaww wadio statistics to be
 *	wetuwned awong with othew suwvey data. If set, @NW80211_CMD_GET_SUWVEY
 *	may wetuwn a suwvey entwy without a channew indicating gwobaw wadio
 *	statistics (onwy some vawues awe vawid and make sense.)
 *	Fow devices that don't wetuwn such an entwy even then, the infowmation
 *	shouwd be contained in the wesuwt as the sum of the wespective countews
 *	ovew aww channews.
 *
 * @NW80211_ATTW_SCHED_SCAN_DEWAY: deway befowe the fiwst cycwe of a
 *	scheduwed scan is stawted.  Ow the deway befowe a WoWWAN
 *	net-detect scan is stawted, counting fwom the moment the
 *	system is suspended.  This vawue is a u32, in seconds.

 * @NW80211_ATTW_WEG_INDOOW: fwag attwibute, if set indicates that the device
 *      is opewating in an indoow enviwonment.
 *
 * @NW80211_ATTW_MAX_NUM_SCHED_SCAN_PWANS: maximum numbew of scan pwans fow
 *	scheduwed scan suppowted by the device (u32), a wiphy attwibute.
 * @NW80211_ATTW_MAX_SCAN_PWAN_INTEWVAW: maximum intewvaw (in seconds) fow
 *	a scan pwan (u32), a wiphy attwibute.
 * @NW80211_ATTW_MAX_SCAN_PWAN_ITEWATIONS: maximum numbew of itewations in
 *	a scan pwan (u32), a wiphy attwibute.
 * @NW80211_ATTW_SCHED_SCAN_PWANS: a wist of scan pwans fow scheduwed scan.
 *	Each scan pwan defines the numbew of scan itewations and the intewvaw
 *	between scans. The wast scan pwan wiww awways wun infinitewy,
 *	thus it must not specify the numbew of itewations, onwy the intewvaw
 *	between scans. The scan pwans awe executed sequentiawwy.
 *	Each scan pwan is a nested attwibute of &enum nw80211_sched_scan_pwan.
 * @NW80211_ATTW_PBSS: fwag attwibute. If set it means opewate
 *	in a PBSS. Specified in %NW80211_CMD_CONNECT to wequest
 *	connecting to a PCP, and in %NW80211_CMD_STAWT_AP to stawt
 *	a PCP instead of AP. Wewevant fow DMG netwowks onwy.
 * @NW80211_ATTW_BSS_SEWECT: nested attwibute fow dwivew suppowting the
 *	BSS sewection featuwe. When used with %NW80211_CMD_GET_WIPHY it contains
 *	attwibutes accowding &enum nw80211_bss_sewect_attw to indicate what
 *	BSS sewection behaviouws awe suppowted. When used with %NW80211_CMD_CONNECT
 *	it contains the behaviouw-specific attwibute containing the pawametews fow
 *	BSS sewection to be done by dwivew and/ow fiwmwawe.
 *
 * @NW80211_ATTW_STA_SUPPOWT_P2P_PS: whethew P2P PS mechanism suppowted
 *	ow not. u8, one of the vawues of &enum nw80211_sta_p2p_ps_status
 *
 * @NW80211_ATTW_PAD: attwibute used fow padding fow 64-bit awignment
 *
 * @NW80211_ATTW_IFTYPE_EXT_CAPA: Nested attwibute of the fowwowing attwibutes:
 *	%NW80211_ATTW_IFTYPE, %NW80211_ATTW_EXT_CAPA,
 *	%NW80211_ATTW_EXT_CAPA_MASK, to specify the extended capabiwities and
 *	othew intewface-type specific capabiwities pew intewface type. Fow MWO,
 *	%NW80211_ATTW_EMW_CAPABIWITY and %NW80211_ATTW_MWD_CAPA_AND_OPS awe
 *	pwesent.
 *
 * @NW80211_ATTW_MU_MIMO_GWOUP_DATA: awway of 24 bytes that defines a MU-MIMO
 *	gwoupID fow monitow mode.
 *	The fiwst 8 bytes awe a mask that defines the membewship in each
 *	gwoup (thewe awe 64 gwoups, gwoup 0 and 63 awe wesewved),
 *	each bit wepwesents a gwoup and set to 1 fow being a membew in
 *	that gwoup and 0 fow not being a membew.
 *	The wemaining 16 bytes define the position in each gwoup: 2 bits fow
 *	each gwoup.
 *	(smawwew gwoup numbews wepwesented on most significant bits and biggew
 *	gwoup numbews on weast significant bits.)
 *	This attwibute is used onwy if aww intewfaces awe in monitow mode.
 *	Set this attwibute in owdew to monitow packets using the given MU-MIMO
 *	gwoupID data.
 *	to tuwn off that featuwe set aww the bits of the gwoupID to zewo.
 * @NW80211_ATTW_MU_MIMO_FOWWOW_MAC_ADDW: mac addwess fow the sniffew to fowwow
 *	when using MU-MIMO aiw sniffew.
 *	to tuwn that featuwe off set an invawid mac addwess
 *	(e.g. FF:FF:FF:FF:FF:FF)
 *
 * @NW80211_ATTW_SCAN_STAWT_TIME_TSF: The time at which the scan was actuawwy
 *	stawted (u64). The time is the TSF of the BSS the intewface that
 *	wequested the scan is connected to (if avaiwabwe, othewwise this
 *	attwibute must not be incwuded).
 * @NW80211_ATTW_SCAN_STAWT_TIME_TSF_BSSID: The BSS accowding to which
 *	%NW80211_ATTW_SCAN_STAWT_TIME_TSF is set.
 * @NW80211_ATTW_MEASUWEMENT_DUWATION: measuwement duwation in TUs (u16). If
 *	%NW80211_ATTW_MEASUWEMENT_DUWATION_MANDATOWY is not set, this is the
 *	maximum measuwement duwation awwowed. This attwibute is used with
 *	measuwement wequests. It can awso be used with %NW80211_CMD_TWIGGEW_SCAN
 *	if the scan is used fow beacon wepowt wadio measuwement.
 * @NW80211_ATTW_MEASUWEMENT_DUWATION_MANDATOWY: fwag attwibute that indicates
 *	that the duwation specified with %NW80211_ATTW_MEASUWEMENT_DUWATION is
 *	mandatowy. If this fwag is not set, the duwation is the maximum duwation
 *	and the actuaw measuwement duwation may be showtew.
 *
 * @NW80211_ATTW_MESH_PEEW_AID: Association ID fow the mesh peew (u16). This is
 *	used to puww the stowed data fow mesh peew in powew save state.
 *
 * @NW80211_ATTW_NAN_MASTEW_PWEF: the mastew pwefewence to be used by
 *	%NW80211_CMD_STAWT_NAN and optionawwy with
 *	%NW80211_CMD_CHANGE_NAN_CONFIG. Its type is u8 and it can't be 0.
 *	Awso, vawues 1 and 255 awe wesewved fow cewtification puwposes and
 *	shouwd not be used duwing a nowmaw device opewation.
 * @NW80211_ATTW_BANDS: opewating bands configuwation.  This is a u32
 *	bitmask of BIT(NW80211_BAND_*) as descwibed in %enum
 *	nw80211_band.  Fow instance, fow NW80211_BAND_2GHZ, bit 0
 *	wouwd be set.  This attwibute is used with
 *	%NW80211_CMD_STAWT_NAN and %NW80211_CMD_CHANGE_NAN_CONFIG, and
 *	it is optionaw.  If no bands awe set, it means don't-cawe and
 *	the device wiww decide what to use.
 * @NW80211_ATTW_NAN_FUNC: a function that can be added to NAN. See
 *	&enum nw80211_nan_func_attwibutes fow descwiption of this nested
 *	attwibute.
 * @NW80211_ATTW_NAN_MATCH: used to wepowt a match. This is a nested attwibute.
 *	See &enum nw80211_nan_match_attwibutes.
 * @NW80211_ATTW_FIWS_KEK: KEK fow FIWS (We)Association Wequest/Wesponse fwame
 *	pwotection.
 * @NW80211_ATTW_FIWS_NONCES: Nonces (pawt of AAD) fow FIWS (We)Association
 *	Wequest/Wesponse fwame pwotection. This attwibute contains the 16 octet
 *	STA Nonce fowwowed by 16 octets of AP Nonce.
 *
 * @NW80211_ATTW_MUWTICAST_TO_UNICAST_ENABWED: Indicates whethew ow not muwticast
 *	packets shouwd be send out as unicast to aww stations (fwag attwibute).
 *
 * @NW80211_ATTW_BSSID: The BSSID of the AP. Note that %NW80211_ATTW_MAC is awso
 *	used in vawious commands/events fow specifying the BSSID.
 *
 * @NW80211_ATTW_SCHED_SCAN_WEWATIVE_WSSI: Wewative WSSI thweshowd by which
 *	othew BSSs has to be bettew ow swightwy wowse than the cuwwent
 *	connected BSS so that they get wepowted to usew space.
 *	This wiww give an oppowtunity to usewspace to considew connecting to
 *	othew matching BSSs which have bettew ow swightwy wowse WSSI than
 *	the cuwwent connected BSS by using an offwoaded opewation to avoid
 *	unnecessawy wakeups.
 *
 * @NW80211_ATTW_SCHED_SCAN_WSSI_ADJUST: When pwesent the WSSI wevew fow BSSs in
 *	the specified band is to be adjusted befowe doing
 *	%NW80211_ATTW_SCHED_SCAN_WEWATIVE_WSSI based compawison to figuwe out
 *	bettew BSSs. The attwibute vawue is a packed stwuctuwe
 *	vawue as specified by &stwuct nw80211_bss_sewect_wssi_adjust.
 *
 * @NW80211_ATTW_TIMEOUT_WEASON: The weason fow which an opewation timed out.
 *	u32 attwibute with an &enum nw80211_timeout_weason vawue. This is used,
 *	e.g., with %NW80211_CMD_CONNECT event.
 *
 * @NW80211_ATTW_FIWS_EWP_USEWNAME: EAP We-authentication Pwotocow (EWP)
 *	usewname pawt of NAI used to wefew keys wWK and wIK. This is used with
 *	%NW80211_CMD_CONNECT.
 *
 * @NW80211_ATTW_FIWS_EWP_WEAWM: EAP We-authentication Pwotocow (EWP) weawm pawt
 *	of NAI specifying the domain name of the EW sewvew. This is used with
 *	%NW80211_CMD_CONNECT.
 *
 * @NW80211_ATTW_FIWS_EWP_NEXT_SEQ_NUM: Unsigned 16-bit EWP next sequence numbew
 *	to use in EWP messages. This is used in genewating the FIWS wwapped data
 *	fow FIWS authentication and is used with %NW80211_CMD_CONNECT.
 *
 * @NW80211_ATTW_FIWS_EWP_WWK: EWP we-authentication Woot Key (wWK) fow the
 *	NAI specified by %NW80211_ATTW_FIWS_EWP_USEWNAME and
 *	%NW80211_ATTW_FIWS_EWP_WEAWM. This is used fow genewating wIK and wMSK
 *	fwom successfuw FIWS authentication and is used with
 *	%NW80211_CMD_CONNECT.
 *
 * @NW80211_ATTW_FIWS_CACHE_ID: A 2-octet identifiew advewtised by a FIWS AP
 *	identifying the scope of PMKSAs. This is used with
 *	@NW80211_CMD_SET_PMKSA and @NW80211_CMD_DEW_PMKSA.
 *
 * @NW80211_ATTW_PMK: attwibute fow passing PMK key matewiaw. Used with
 *	%NW80211_CMD_SET_PMKSA fow the PMKSA identified by %NW80211_ATTW_PMKID.
 *	Fow %NW80211_CMD_CONNECT and %NW80211_CMD_STAWT_AP it is used to pwovide
 *	PSK fow offwoading 4-way handshake fow WPA/WPA2-PSK netwowks. Fow 802.1X
 *	authentication it is used with %NW80211_CMD_SET_PMK. Fow offwoaded FT
 *	suppowt this attwibute specifies the PMK-W0 if NW80211_ATTW_PMKW0_NAME
 *	is incwuded as weww.
 *
 * @NW80211_ATTW_SCHED_SCAN_MUWTI: fwag attwibute which usew-space shaww use to
 *	indicate that it suppowts muwtipwe active scheduwed scan wequests.
 * @NW80211_ATTW_SCHED_SCAN_MAX_WEQS: indicates maximum numbew of scheduwed
 *	scan wequest that may be active fow the device (u32).
 *
 * @NW80211_ATTW_WANT_1X_4WAY_HS: fwag attwibute which usew-space can incwude
 *	in %NW80211_CMD_CONNECT to indicate that fow 802.1X authentication it
 *	wants to use the suppowted offwoad of the 4-way handshake.
 * @NW80211_ATTW_PMKW0_NAME: PMK-W0 Name fow offwoaded FT.
 * @NW80211_ATTW_POWT_AUTHOWIZED: (wesewved)
 *
 * @NW80211_ATTW_EXTEWNAW_AUTH_ACTION: Identify the wequested extewnaw
 *     authentication opewation (u32 attwibute with an
 *     &enum nw80211_extewnaw_auth_action vawue). This is used with the
 *     %NW80211_CMD_EXTEWNAW_AUTH wequest event.
 * @NW80211_ATTW_EXTEWNAW_AUTH_SUPPOWT: Fwag attwibute indicating that the usew
 *	space suppowts extewnaw authentication. This attwibute shaww be used
 *	with %NW80211_CMD_CONNECT and %NW80211_CMD_STAWT_AP wequest. The dwivew
 *	may offwoad authentication pwocessing to usew space if this capabiwity
 *	is indicated in the wespective wequests fwom the usew space. (This fwag
 *	attwibute depwecated fow %NW80211_CMD_STAWT_AP, use
 *	%NW80211_ATTW_AP_SETTINGS_FWAGS)
 *
 * @NW80211_ATTW_NSS: Station's New/updated  WX_NSS vawue notified using this
 *	u8 attwibute. This is used with %NW80211_CMD_STA_OPMODE_CHANGED.
 *
 * @NW80211_ATTW_TXQ_STATS: TXQ statistics (nested attwibute, see &enum
 *      nw80211_txq_stats)
 * @NW80211_ATTW_TXQ_WIMIT: Totaw packet wimit fow the TXQ queues fow this phy.
 *      The smawwew of this and the memowy wimit is enfowced.
 * @NW80211_ATTW_TXQ_MEMOWY_WIMIT: Totaw memowy wimit (in bytes) fow the
 *      TXQ queues fow this phy. The smawwew of this and the packet wimit is
 *      enfowced.
 * @NW80211_ATTW_TXQ_QUANTUM: TXQ scheduwew quantum (bytes). Numbew of bytes
 *      a fwow is assigned on each wound of the DWW scheduwew.
 * @NW80211_ATTW_HE_CAPABIWITY: HE Capabiwity infowmation ewement (fwom
 *	association wequest when used with NW80211_CMD_NEW_STATION). Can be set
 *	onwy if %NW80211_STA_FWAG_WME is set.
 *
 * @NW80211_ATTW_FTM_WESPONDEW: nested attwibute which usew-space can incwude
 *	in %NW80211_CMD_STAWT_AP ow %NW80211_CMD_SET_BEACON fow fine timing
 *	measuwement (FTM) wespondew functionawity and containing pawametews as
 *	possibwe, see &enum nw80211_ftm_wespondew_attw
 *
 * @NW80211_ATTW_FTM_WESPONDEW_STATS: Nested attwibute with FTM wespondew
 *	statistics, see &enum nw80211_ftm_wespondew_stats.
 *
 * @NW80211_ATTW_TIMEOUT: Timeout fow the given opewation in miwwiseconds (u32),
 *	if the attwibute is not given no timeout is wequested. Note that 0 is an
 *	invawid vawue.
 *
 * @NW80211_ATTW_PEEW_MEASUWEMENTS: peew measuwements wequest (and wesuwt)
 *	data, uses nested attwibutes specified in
 *	&enum nw80211_peew_measuwement_attws.
 *	This is awso used fow capabiwity advewtisement in the wiphy infowmation,
 *	with the appwopwiate sub-attwibutes.
 *
 * @NW80211_ATTW_AIWTIME_WEIGHT: Station's weight when scheduwed by the aiwtime
 *	scheduwew.
 *
 * @NW80211_ATTW_STA_TX_POWEW_SETTING: Twansmit powew setting type (u8) fow
 *	station associated with the AP. See &enum nw80211_tx_powew_setting fow
 *	possibwe vawues.
 * @NW80211_ATTW_STA_TX_POWEW: Twansmit powew wevew (s16) in dBm units. This
 *	awwows to set Tx powew fow a station. If this attwibute is not incwuded,
 *	the defauwt pew-intewface tx powew setting wiww be ovewwiding. Dwivew
 *	shouwd be picking up the wowest tx powew, eithew tx powew pew-intewface
 *	ow pew-station.
 *
 * @NW80211_ATTW_SAE_PASSWOWD: attwibute fow passing SAE passwowd matewiaw. It
 *	is used with %NW80211_CMD_CONNECT to pwovide passwowd fow offwoading
 *	SAE authentication fow WPA3-Pewsonaw netwowks.
 *
 * @NW80211_ATTW_TWT_WESPONDEW: Enabwe tawget wait time wespondew suppowt.
 *
 * @NW80211_ATTW_HE_OBSS_PD: nested attwibute fow OBSS Packet Detection
 *	functionawity.
 *
 * @NW80211_ATTW_WIPHY_EDMG_CHANNEWS: bitmap that indicates the 2.16 GHz
 *	channew(s) that awe awwowed to be used fow EDMG twansmissions.
 *	Defined by IEEE P802.11ay/D4.0 section 9.4.2.251. (u8 attwibute)
 * @NW80211_ATTW_WIPHY_EDMG_BW_CONFIG: Channew BW Configuwation subfiewd encodes
 *	the awwowed channew bandwidth configuwations. (u8 attwibute)
 *	Defined by IEEE P802.11ay/D4.0 section 9.4.2.251, Tabwe 13.
 *
 * @NW80211_ATTW_VWAN_ID: VWAN ID (1..4094) fow the station and VWAN gwoup key
 *	(u16).
 *
 * @NW80211_ATTW_HE_BSS_COWOW: nested attwibute fow BSS Cowow Settings.
 *
 * @NW80211_ATTW_IFTYPE_AKM_SUITES: nested awway attwibute, with each entwy
 *	using attwibutes fwom &enum nw80211_iftype_akm_attwibutes. This
 *	attwibute is sent in a wesponse to %NW80211_CMD_GET_WIPHY indicating
 *	suppowted AKM suites capabiwity pew intewface. AKMs advewtised in
 *	%NW80211_ATTW_AKM_SUITES awe defauwt capabiwities if AKM suites not
 *	advewtised fow a specific intewface type.
 *
 * @NW80211_ATTW_TID_CONFIG: TID specific configuwation in a
 *	nested attwibute with &enum nw80211_tid_config_attw sub-attwibutes;
 *	on output (in wiphy attwibutes) it contains onwy the featuwe sub-
 *	attwibutes.
 *
 * @NW80211_ATTW_CONTWOW_POWT_NO_PWEAUTH: disabwe pweauth fwame wx on contwow
 *	powt in owdew to fowwawd/weceive them as owdinawy data fwames.
 *
 * @NW80211_ATTW_PMK_WIFETIME: Maximum wifetime fow PMKSA in seconds (u32,
 *	dot11WSNAConfigPMKWeauthThweshowd; 0 is not a vawid vawue).
 *	An optionaw pawametew configuwed thwough %NW80211_CMD_SET_PMKSA.
 *	Dwivews that twiggew woaming need to know the wifetime of the
 *	configuwed PMKSA fow twiggewing the fuww vs. PMKSA caching based
 *	authentication. This timeout hewps authentication methods wike SAE,
 *	whewe PMK gets updated onwy by going thwough a fuww (new SAE)
 *	authentication instead of getting updated duwing an association fow EAP
 *	authentication. No new fuww authentication within the PMK expiwy shaww
 *	wesuwt in a disassociation at the end of the wifetime.
 *
 * @NW80211_ATTW_PMK_WEAUTH_THWESHOWD: Weauthentication thweshowd time, in
 *	tewms of pewcentage of %NW80211_ATTW_PMK_WIFETIME
 *	(u8, dot11WSNAConfigPMKWeauthThweshowd, 1..100). This is an optionaw
 *	pawametew configuwed thwough %NW80211_CMD_SET_PMKSA. Wequests the
 *	dwivew to twiggew a fuww authentication woam (without PMKSA caching)
 *	aftew the weauthentication thweshowd time, but befowe the PMK wifetime
 *	has expiwed.
 *
 *	Authentication methods wike SAE need to be abwe to genewate a new PMKSA
 *	entwy without having to fowce a disconnection aftew the PMK timeout. If
 *	no woaming occuws between the weauth thweshowd and PMK expiwation,
 *	disassociation is stiww fowced.
 * @NW80211_ATTW_WECEIVE_MUWTICAST: muwticast fwag fow the
 *	%NW80211_CMD_WEGISTEW_FWAME command, see the descwiption thewe.
 * @NW80211_ATTW_WIPHY_FWEQ_OFFSET: offset of the associated
 *	%NW80211_ATTW_WIPHY_FWEQ in positive KHz. Onwy vawid when suppwied with
 *	an %NW80211_ATTW_WIPHY_FWEQ_OFFSET.
 * @NW80211_ATTW_CENTEW_FWEQ1_OFFSET: Centew fwequency offset in KHz fow the
 *	fiwst channew segment specified in %NW80211_ATTW_CENTEW_FWEQ1.
 * @NW80211_ATTW_SCAN_FWEQ_KHZ: nested attwibute with KHz fwequencies
 *
 * @NW80211_ATTW_HE_6GHZ_CAPABIWITY: HE 6 GHz Band Capabiwity ewement (fwom
 *	association wequest when used with NW80211_CMD_NEW_STATION).
 *
 * @NW80211_ATTW_FIWS_DISCOVEWY: Optionaw pawametew to configuwe FIWS
 *	discovewy. It is a nested attwibute, see
 *	&enum nw80211_fiws_discovewy_attwibutes. Usewspace shouwd pass an empty
 *	nested attwibute to disabwe this featuwe and dewete the tempwates.
 *
 * @NW80211_ATTW_UNSOW_BCAST_PWOBE_WESP: Optionaw pawametew to configuwe
 *	unsowicited bwoadcast pwobe wesponse. It is a nested attwibute, see
 *	&enum nw80211_unsow_bcast_pwobe_wesp_attwibutes. Usewspace shouwd pass an empty
 *	nested attwibute to disabwe this featuwe and dewete the tempwates.
 *
 * @NW80211_ATTW_S1G_CAPABIWITY: S1G Capabiwity infowmation ewement (fwom
 *	association wequest when used with NW80211_CMD_NEW_STATION)
 * @NW80211_ATTW_S1G_CAPABIWITY_MASK: S1G Capabiwity Infowmation ewement
 *	ovewwide mask. Used with NW80211_ATTW_S1G_CAPABIWITY in
 *	NW80211_CMD_ASSOCIATE ow NW80211_CMD_CONNECT.
 *
 * @NW80211_ATTW_SAE_PWE: Indicates the mechanism(s) awwowed fow SAE PWE
 *	dewivation in WPA3-Pewsonaw netwowks which awe using SAE authentication.
 *	This is a u8 attwibute that encapsuwates one of the vawues fwom
 *	&enum nw80211_sae_pwe_mechanism.
 *
 * @NW80211_ATTW_SAW_SPEC: SAW powew wimitation specification when
 *	used with %NW80211_CMD_SET_SAW_SPECS. The message contains fiewds
 *	of %nw80211_saw_attws which specifies the saw type and wewated
 *	saw specs. Saw specs contains awway of %nw80211_saw_specs_attws.
 *
 * @NW80211_ATTW_WECONNECT_WEQUESTED: fwag attwibute, used with deauth and
 *	disassoc events to indicate that an immediate weconnect to the AP
 *	is desiwed.
 *
 * @NW80211_ATTW_OBSS_COWOW_BITMAP: bitmap of the u64 BSS cowows fow the
 *	%NW80211_CMD_OBSS_COWOW_COWWISION event.
 *
 * @NW80211_ATTW_COWOW_CHANGE_COUNT: u8 attwibute specifying the numbew of TBTT's
 *	untiw the cowow switch event.
 * @NW80211_ATTW_COWOW_CHANGE_COWOW: u8 attwibute specifying the cowow that we awe
 *	switching to
 * @NW80211_ATTW_COWOW_CHANGE_EWEMS: Nested set of attwibutes containing the IE
 *	infowmation fow the time whiwe pewfowming a cowow switch.
 *
 * @NW80211_ATTW_MBSSID_CONFIG: Nested attwibute fow muwtipwe BSSID
 *	advewtisements (MBSSID) pawametews in AP mode.
 *	Kewnew uses this attwibute to indicate the dwivew's suppowt fow MBSSID
 *	and enhanced muwti-BSSID advewtisements (EMA AP) to the usewspace.
 *	Usewspace shouwd use this attwibute to configuwe pew intewface MBSSID
 *	pawametews.
 *	See &enum nw80211_mbssid_config_attwibutes fow detaiws.
 *
 * @NW80211_ATTW_MBSSID_EWEMS: Nested pawametew to pass muwtipwe BSSID ewements.
 *	Mandatowy pawametew fow the twansmitting intewface to enabwe MBSSID.
 *	Optionaw fow the non-twansmitting intewfaces.
 *
 * @NW80211_ATTW_WADAW_BACKGWOUND: Configuwe dedicated offchannew chain
 *	avaiwabwe fow wadaw/CAC detection on some hw. This chain can't be used
 *	to twansmit ow weceive fwames and it is bounded to a wunning wdev.
 *	Backgwound wadaw/CAC detection awwows to avoid the CAC downtime
 *	switching on a diffewent channew duwing CAC detection on the sewected
 *	wadaw channew.
 *
 * @NW80211_ATTW_AP_SETTINGS_FWAGS: u32 attwibute contains ap settings fwags,
 *	enumewated in &enum nw80211_ap_settings_fwags. This attwibute shaww be
 *	used with %NW80211_CMD_STAWT_AP wequest.
 *
 * @NW80211_ATTW_EHT_CAPABIWITY: EHT Capabiwity infowmation ewement (fwom
 *	association wequest when used with NW80211_CMD_NEW_STATION). Can be set
 *	onwy if %NW80211_STA_FWAG_WME is set.
 *
 * @NW80211_ATTW_MWO_WINK_ID: A (u8) wink ID fow use with MWO, to be used with
 *	vawious commands that need a wink ID to opewate.
 * @NW80211_ATTW_MWO_WINKS: A nested awway of winks, each containing some
 *	pew-wink infowmation and a wink ID.
 * @NW80211_ATTW_MWD_ADDW: An MWD addwess, used with vawious commands such as
 *	authenticate/associate.
 *
 * @NW80211_ATTW_MWO_SUPPOWT: Fwag attwibute to indicate usew space suppowts MWO
 *	connection. Used with %NW80211_CMD_CONNECT. If this attwibute is not
 *	incwuded in NW80211_CMD_CONNECT dwivews must not pewfowm MWO connection.
 *
 * @NW80211_ATTW_MAX_NUM_AKM_SUITES: U16 attwibute. Indicates maximum numbew of
 *	AKM suites awwowed fow %NW80211_CMD_CONNECT, %NW80211_CMD_ASSOCIATE and
 *	%NW80211_CMD_STAWT_AP in %NW80211_CMD_GET_WIPHY wesponse. If this
 *	attwibute is not pwesent usewspace shaww considew maximum numbew of AKM
 *	suites awwowed as %NW80211_MAX_NW_AKM_SUITES which is the wegacy maximum
 *	numbew pwiow to the intwoduction of this attwibute.
 *
 * @NW80211_ATTW_EMW_CAPABIWITY: EMW Capabiwity infowmation (u16)
 * @NW80211_ATTW_MWD_CAPA_AND_OPS: MWD Capabiwities and Opewations (u16)
 *
 * @NW80211_ATTW_TX_HW_TIMESTAMP: Hawdwawe timestamp fow TX opewation in
 *	nanoseconds (u64). This is the device cwock timestamp so it wiww
 *	pwobabwy weset when the device is stopped ow the fiwmwawe is weset.
 *	When used with %NW80211_CMD_FWAME_TX_STATUS, indicates the fwame TX
 *	timestamp. When used with %NW80211_CMD_FWAME WX notification, indicates
 *	the ack TX timestamp.
 * @NW80211_ATTW_WX_HW_TIMESTAMP: Hawdwawe timestamp fow WX opewation in
 *	nanoseconds (u64). This is the device cwock timestamp so it wiww
 *	pwobabwy weset when the device is stopped ow the fiwmwawe is weset.
 *	When used with %NW80211_CMD_FWAME_TX_STATUS, indicates the ack WX
 *	timestamp. When used with %NW80211_CMD_FWAME WX notification, indicates
 *	the incoming fwame WX timestamp.
 * @NW80211_ATTW_TD_BITMAP: Twansition Disabwe bitmap, fow subsequent
 *	(we)associations.
 *
 * @NW80211_ATTW_PUNCT_BITMAP: (u32) Pweambwe punctuwing bitmap, wowest
 *	bit cowwesponds to the wowest 20 MHz channew. Each bit set to 1
 *	indicates that the sub-channew is punctuwed. Highew 16 bits awe
 *	wesewved.
 *
 * @NW80211_ATTW_MAX_HW_TIMESTAMP_PEEWS: Maximum numbew of peews that HW
 *	timestamping can be enabwed fow concuwwentwy (u16), a wiphy attwibute.
 *	A vawue of 0xffff indicates setting fow aww peews (i.e. not specifying
 *	an addwess with %NW80211_CMD_SET_HW_TIMESTAMP) is suppowted.
 * @NW80211_ATTW_HW_TIMESTAMP_ENABWED: Indicates whethew HW timestamping shouwd
 *	be enabwed ow not (fwag attwibute).
 *
 * @NW80211_ATTW_EMA_WNW_EWEMS: Optionaw nested attwibute fow
 *	weduced neighbow wepowt (WNW) ewements. This attwibute can be used
 *	onwy when NW80211_MBSSID_CONFIG_ATTW_EMA is enabwed.
 *	Usewspace is wesponsibwe fow spwitting the WNW into muwtipwe
 *	ewements such that each ewement excwudes the non-twansmitting
 *	pwofiwes awweady incwuded in the MBSSID ewement
 *	(%NW80211_ATTW_MBSSID_EWEMS) at the same index. Each EMA beacon
 *	wiww be genewated by adding MBSSID and WNW ewements at the same
 *	index. If the usewspace incwudes mowe WNW ewements than numbew of
 *	MBSSID ewements then these wiww be added in evewy EMA beacon.
 *
 * @NW80211_ATTW_MWO_WINK_DISABWED: Fwag attwibute indicating that the wink is
 *	disabwed.
 *
 * @NW80211_ATTW_BSS_DUMP_INCWUDE_USE_DATA: Incwude BSS usage data, i.e.
 *	incwude BSSes that can onwy be used in westwicted scenawios and/ow
 *	cannot be used at aww.
 *
 * @NW80211_ATTW_MWO_TTWM_DWINK: Binawy attwibute specifying the downwink TID to
 *      wink mapping. The wength is 8 * sizeof(u16). Fow each TID the wink
 *      mapping is as defined in section 9.4.2.314 (TID-To-Wink Mapping ewement)
 *      in Dwaft P802.11be_D4.0.
 * @NW80211_ATTW_MWO_TTWM_UWINK: Binawy attwibute specifying the upwink TID to
 *      wink mapping. The wength is 8 * sizeof(u16). Fow each TID the wink
 *      mapping is as defined in section 9.4.2.314 (TID-To-Wink Mapping ewement)
 *      in Dwaft P802.11be_D4.0.
 *
 * @NUM_NW80211_ATTW: totaw numbew of nw80211_attws avaiwabwe
 * @NW80211_ATTW_MAX: highest attwibute numbew cuwwentwy defined
 * @__NW80211_ATTW_AFTEW_WAST: intewnaw use
 */
enum nw80211_attws {
/* don't change the owdew ow add anything between, this is ABI! */
	NW80211_ATTW_UNSPEC,

	NW80211_ATTW_WIPHY,
	NW80211_ATTW_WIPHY_NAME,

	NW80211_ATTW_IFINDEX,
	NW80211_ATTW_IFNAME,
	NW80211_ATTW_IFTYPE,

	NW80211_ATTW_MAC,

	NW80211_ATTW_KEY_DATA,
	NW80211_ATTW_KEY_IDX,
	NW80211_ATTW_KEY_CIPHEW,
	NW80211_ATTW_KEY_SEQ,
	NW80211_ATTW_KEY_DEFAUWT,

	NW80211_ATTW_BEACON_INTEWVAW,
	NW80211_ATTW_DTIM_PEWIOD,
	NW80211_ATTW_BEACON_HEAD,
	NW80211_ATTW_BEACON_TAIW,

	NW80211_ATTW_STA_AID,
	NW80211_ATTW_STA_FWAGS,
	NW80211_ATTW_STA_WISTEN_INTEWVAW,
	NW80211_ATTW_STA_SUPPOWTED_WATES,
	NW80211_ATTW_STA_VWAN,
	NW80211_ATTW_STA_INFO,

	NW80211_ATTW_WIPHY_BANDS,

	NW80211_ATTW_MNTW_FWAGS,

	NW80211_ATTW_MESH_ID,
	NW80211_ATTW_STA_PWINK_ACTION,
	NW80211_ATTW_MPATH_NEXT_HOP,
	NW80211_ATTW_MPATH_INFO,

	NW80211_ATTW_BSS_CTS_PWOT,
	NW80211_ATTW_BSS_SHOWT_PWEAMBWE,
	NW80211_ATTW_BSS_SHOWT_SWOT_TIME,

	NW80211_ATTW_HT_CAPABIWITY,

	NW80211_ATTW_SUPPOWTED_IFTYPES,

	NW80211_ATTW_WEG_AWPHA2,
	NW80211_ATTW_WEG_WUWES,

	NW80211_ATTW_MESH_CONFIG,

	NW80211_ATTW_BSS_BASIC_WATES,

	NW80211_ATTW_WIPHY_TXQ_PAWAMS,
	NW80211_ATTW_WIPHY_FWEQ,
	NW80211_ATTW_WIPHY_CHANNEW_TYPE,

	NW80211_ATTW_KEY_DEFAUWT_MGMT,

	NW80211_ATTW_MGMT_SUBTYPE,
	NW80211_ATTW_IE,

	NW80211_ATTW_MAX_NUM_SCAN_SSIDS,

	NW80211_ATTW_SCAN_FWEQUENCIES,
	NW80211_ATTW_SCAN_SSIDS,
	NW80211_ATTW_GENEWATION, /* wepwaces owd SCAN_GENEWATION */
	NW80211_ATTW_BSS,

	NW80211_ATTW_WEG_INITIATOW,
	NW80211_ATTW_WEG_TYPE,

	NW80211_ATTW_SUPPOWTED_COMMANDS,

	NW80211_ATTW_FWAME,
	NW80211_ATTW_SSID,
	NW80211_ATTW_AUTH_TYPE,
	NW80211_ATTW_WEASON_CODE,

	NW80211_ATTW_KEY_TYPE,

	NW80211_ATTW_MAX_SCAN_IE_WEN,
	NW80211_ATTW_CIPHEW_SUITES,

	NW80211_ATTW_FWEQ_BEFOWE,
	NW80211_ATTW_FWEQ_AFTEW,

	NW80211_ATTW_FWEQ_FIXED,


	NW80211_ATTW_WIPHY_WETWY_SHOWT,
	NW80211_ATTW_WIPHY_WETWY_WONG,
	NW80211_ATTW_WIPHY_FWAG_THWESHOWD,
	NW80211_ATTW_WIPHY_WTS_THWESHOWD,

	NW80211_ATTW_TIMED_OUT,

	NW80211_ATTW_USE_MFP,

	NW80211_ATTW_STA_FWAGS2,

	NW80211_ATTW_CONTWOW_POWT,

	NW80211_ATTW_TESTDATA,

	NW80211_ATTW_PWIVACY,

	NW80211_ATTW_DISCONNECTED_BY_AP,
	NW80211_ATTW_STATUS_CODE,

	NW80211_ATTW_CIPHEW_SUITES_PAIWWISE,
	NW80211_ATTW_CIPHEW_SUITE_GWOUP,
	NW80211_ATTW_WPA_VEWSIONS,
	NW80211_ATTW_AKM_SUITES,

	NW80211_ATTW_WEQ_IE,
	NW80211_ATTW_WESP_IE,

	NW80211_ATTW_PWEV_BSSID,

	NW80211_ATTW_KEY,
	NW80211_ATTW_KEYS,

	NW80211_ATTW_PID,

	NW80211_ATTW_4ADDW,

	NW80211_ATTW_SUWVEY_INFO,

	NW80211_ATTW_PMKID,
	NW80211_ATTW_MAX_NUM_PMKIDS,

	NW80211_ATTW_DUWATION,

	NW80211_ATTW_COOKIE,

	NW80211_ATTW_WIPHY_COVEWAGE_CWASS,

	NW80211_ATTW_TX_WATES,

	NW80211_ATTW_FWAME_MATCH,

	NW80211_ATTW_ACK,

	NW80211_ATTW_PS_STATE,

	NW80211_ATTW_CQM,

	NW80211_ATTW_WOCAW_STATE_CHANGE,

	NW80211_ATTW_AP_ISOWATE,

	NW80211_ATTW_WIPHY_TX_POWEW_SETTING,
	NW80211_ATTW_WIPHY_TX_POWEW_WEVEW,

	NW80211_ATTW_TX_FWAME_TYPES,
	NW80211_ATTW_WX_FWAME_TYPES,
	NW80211_ATTW_FWAME_TYPE,

	NW80211_ATTW_CONTWOW_POWT_ETHEWTYPE,
	NW80211_ATTW_CONTWOW_POWT_NO_ENCWYPT,

	NW80211_ATTW_SUPPOWT_IBSS_WSN,

	NW80211_ATTW_WIPHY_ANTENNA_TX,
	NW80211_ATTW_WIPHY_ANTENNA_WX,

	NW80211_ATTW_MCAST_WATE,

	NW80211_ATTW_OFFCHANNEW_TX_OK,

	NW80211_ATTW_BSS_HT_OPMODE,

	NW80211_ATTW_KEY_DEFAUWT_TYPES,

	NW80211_ATTW_MAX_WEMAIN_ON_CHANNEW_DUWATION,

	NW80211_ATTW_MESH_SETUP,

	NW80211_ATTW_WIPHY_ANTENNA_AVAIW_TX,
	NW80211_ATTW_WIPHY_ANTENNA_AVAIW_WX,

	NW80211_ATTW_SUPPOWT_MESH_AUTH,
	NW80211_ATTW_STA_PWINK_STATE,

	NW80211_ATTW_WOWWAN_TWIGGEWS,
	NW80211_ATTW_WOWWAN_TWIGGEWS_SUPPOWTED,

	NW80211_ATTW_SCHED_SCAN_INTEWVAW,

	NW80211_ATTW_INTEWFACE_COMBINATIONS,
	NW80211_ATTW_SOFTWAWE_IFTYPES,

	NW80211_ATTW_WEKEY_DATA,

	NW80211_ATTW_MAX_NUM_SCHED_SCAN_SSIDS,
	NW80211_ATTW_MAX_SCHED_SCAN_IE_WEN,

	NW80211_ATTW_SCAN_SUPP_WATES,

	NW80211_ATTW_HIDDEN_SSID,

	NW80211_ATTW_IE_PWOBE_WESP,
	NW80211_ATTW_IE_ASSOC_WESP,

	NW80211_ATTW_STA_WME,
	NW80211_ATTW_SUPPOWT_AP_UAPSD,

	NW80211_ATTW_WOAM_SUPPOWT,

	NW80211_ATTW_SCHED_SCAN_MATCH,
	NW80211_ATTW_MAX_MATCH_SETS,

	NW80211_ATTW_PMKSA_CANDIDATE,

	NW80211_ATTW_TX_NO_CCK_WATE,

	NW80211_ATTW_TDWS_ACTION,
	NW80211_ATTW_TDWS_DIAWOG_TOKEN,
	NW80211_ATTW_TDWS_OPEWATION,
	NW80211_ATTW_TDWS_SUPPOWT,
	NW80211_ATTW_TDWS_EXTEWNAW_SETUP,

	NW80211_ATTW_DEVICE_AP_SME,

	NW80211_ATTW_DONT_WAIT_FOW_ACK,

	NW80211_ATTW_FEATUWE_FWAGS,

	NW80211_ATTW_PWOBE_WESP_OFFWOAD,

	NW80211_ATTW_PWOBE_WESP,

	NW80211_ATTW_DFS_WEGION,

	NW80211_ATTW_DISABWE_HT,
	NW80211_ATTW_HT_CAPABIWITY_MASK,

	NW80211_ATTW_NOACK_MAP,

	NW80211_ATTW_INACTIVITY_TIMEOUT,

	NW80211_ATTW_WX_SIGNAW_DBM,

	NW80211_ATTW_BG_SCAN_PEWIOD,

	NW80211_ATTW_WDEV,

	NW80211_ATTW_USEW_WEG_HINT_TYPE,

	NW80211_ATTW_CONN_FAIWED_WEASON,

	NW80211_ATTW_AUTH_DATA,

	NW80211_ATTW_VHT_CAPABIWITY,

	NW80211_ATTW_SCAN_FWAGS,

	NW80211_ATTW_CHANNEW_WIDTH,
	NW80211_ATTW_CENTEW_FWEQ1,
	NW80211_ATTW_CENTEW_FWEQ2,

	NW80211_ATTW_P2P_CTWINDOW,
	NW80211_ATTW_P2P_OPPPS,

	NW80211_ATTW_WOCAW_MESH_POWEW_MODE,

	NW80211_ATTW_ACW_POWICY,

	NW80211_ATTW_MAC_ADDWS,

	NW80211_ATTW_MAC_ACW_MAX,

	NW80211_ATTW_WADAW_EVENT,

	NW80211_ATTW_EXT_CAPA,
	NW80211_ATTW_EXT_CAPA_MASK,

	NW80211_ATTW_STA_CAPABIWITY,
	NW80211_ATTW_STA_EXT_CAPABIWITY,

	NW80211_ATTW_PWOTOCOW_FEATUWES,
	NW80211_ATTW_SPWIT_WIPHY_DUMP,

	NW80211_ATTW_DISABWE_VHT,
	NW80211_ATTW_VHT_CAPABIWITY_MASK,

	NW80211_ATTW_MDID,
	NW80211_ATTW_IE_WIC,

	NW80211_ATTW_CWIT_PWOT_ID,
	NW80211_ATTW_MAX_CWIT_PWOT_DUWATION,

	NW80211_ATTW_PEEW_AID,

	NW80211_ATTW_COAWESCE_WUWE,

	NW80211_ATTW_CH_SWITCH_COUNT,
	NW80211_ATTW_CH_SWITCH_BWOCK_TX,
	NW80211_ATTW_CSA_IES,
	NW80211_ATTW_CNTDWN_OFFS_BEACON,
	NW80211_ATTW_CNTDWN_OFFS_PWESP,

	NW80211_ATTW_WXMGMT_FWAGS,

	NW80211_ATTW_STA_SUPPOWTED_CHANNEWS,

	NW80211_ATTW_STA_SUPPOWTED_OPEW_CWASSES,

	NW80211_ATTW_HANDWE_DFS,

	NW80211_ATTW_SUPPOWT_5_MHZ,
	NW80211_ATTW_SUPPOWT_10_MHZ,

	NW80211_ATTW_OPMODE_NOTIF,

	NW80211_ATTW_VENDOW_ID,
	NW80211_ATTW_VENDOW_SUBCMD,
	NW80211_ATTW_VENDOW_DATA,
	NW80211_ATTW_VENDOW_EVENTS,

	NW80211_ATTW_QOS_MAP,

	NW80211_ATTW_MAC_HINT,
	NW80211_ATTW_WIPHY_FWEQ_HINT,

	NW80211_ATTW_MAX_AP_ASSOC_STA,

	NW80211_ATTW_TDWS_PEEW_CAPABIWITY,

	NW80211_ATTW_SOCKET_OWNEW,

	NW80211_ATTW_CSA_C_OFFSETS_TX,
	NW80211_ATTW_MAX_CSA_COUNTEWS,

	NW80211_ATTW_TDWS_INITIATOW,

	NW80211_ATTW_USE_WWM,

	NW80211_ATTW_WIPHY_DYN_ACK,

	NW80211_ATTW_TSID,
	NW80211_ATTW_USEW_PWIO,
	NW80211_ATTW_ADMITTED_TIME,

	NW80211_ATTW_SMPS_MODE,

	NW80211_ATTW_OPEW_CWASS,

	NW80211_ATTW_MAC_MASK,

	NW80211_ATTW_WIPHY_SEWF_MANAGED_WEG,

	NW80211_ATTW_EXT_FEATUWES,

	NW80211_ATTW_SUWVEY_WADIO_STATS,

	NW80211_ATTW_NETNS_FD,

	NW80211_ATTW_SCHED_SCAN_DEWAY,

	NW80211_ATTW_WEG_INDOOW,

	NW80211_ATTW_MAX_NUM_SCHED_SCAN_PWANS,
	NW80211_ATTW_MAX_SCAN_PWAN_INTEWVAW,
	NW80211_ATTW_MAX_SCAN_PWAN_ITEWATIONS,
	NW80211_ATTW_SCHED_SCAN_PWANS,

	NW80211_ATTW_PBSS,

	NW80211_ATTW_BSS_SEWECT,

	NW80211_ATTW_STA_SUPPOWT_P2P_PS,

	NW80211_ATTW_PAD,

	NW80211_ATTW_IFTYPE_EXT_CAPA,

	NW80211_ATTW_MU_MIMO_GWOUP_DATA,
	NW80211_ATTW_MU_MIMO_FOWWOW_MAC_ADDW,

	NW80211_ATTW_SCAN_STAWT_TIME_TSF,
	NW80211_ATTW_SCAN_STAWT_TIME_TSF_BSSID,
	NW80211_ATTW_MEASUWEMENT_DUWATION,
	NW80211_ATTW_MEASUWEMENT_DUWATION_MANDATOWY,

	NW80211_ATTW_MESH_PEEW_AID,

	NW80211_ATTW_NAN_MASTEW_PWEF,
	NW80211_ATTW_BANDS,
	NW80211_ATTW_NAN_FUNC,
	NW80211_ATTW_NAN_MATCH,

	NW80211_ATTW_FIWS_KEK,
	NW80211_ATTW_FIWS_NONCES,

	NW80211_ATTW_MUWTICAST_TO_UNICAST_ENABWED,

	NW80211_ATTW_BSSID,

	NW80211_ATTW_SCHED_SCAN_WEWATIVE_WSSI,
	NW80211_ATTW_SCHED_SCAN_WSSI_ADJUST,

	NW80211_ATTW_TIMEOUT_WEASON,

	NW80211_ATTW_FIWS_EWP_USEWNAME,
	NW80211_ATTW_FIWS_EWP_WEAWM,
	NW80211_ATTW_FIWS_EWP_NEXT_SEQ_NUM,
	NW80211_ATTW_FIWS_EWP_WWK,
	NW80211_ATTW_FIWS_CACHE_ID,

	NW80211_ATTW_PMK,

	NW80211_ATTW_SCHED_SCAN_MUWTI,
	NW80211_ATTW_SCHED_SCAN_MAX_WEQS,

	NW80211_ATTW_WANT_1X_4WAY_HS,
	NW80211_ATTW_PMKW0_NAME,
	NW80211_ATTW_POWT_AUTHOWIZED,

	NW80211_ATTW_EXTEWNAW_AUTH_ACTION,
	NW80211_ATTW_EXTEWNAW_AUTH_SUPPOWT,

	NW80211_ATTW_NSS,
	NW80211_ATTW_ACK_SIGNAW,

	NW80211_ATTW_CONTWOW_POWT_OVEW_NW80211,

	NW80211_ATTW_TXQ_STATS,
	NW80211_ATTW_TXQ_WIMIT,
	NW80211_ATTW_TXQ_MEMOWY_WIMIT,
	NW80211_ATTW_TXQ_QUANTUM,

	NW80211_ATTW_HE_CAPABIWITY,

	NW80211_ATTW_FTM_WESPONDEW,

	NW80211_ATTW_FTM_WESPONDEW_STATS,

	NW80211_ATTW_TIMEOUT,

	NW80211_ATTW_PEEW_MEASUWEMENTS,

	NW80211_ATTW_AIWTIME_WEIGHT,
	NW80211_ATTW_STA_TX_POWEW_SETTING,
	NW80211_ATTW_STA_TX_POWEW,

	NW80211_ATTW_SAE_PASSWOWD,

	NW80211_ATTW_TWT_WESPONDEW,

	NW80211_ATTW_HE_OBSS_PD,

	NW80211_ATTW_WIPHY_EDMG_CHANNEWS,
	NW80211_ATTW_WIPHY_EDMG_BW_CONFIG,

	NW80211_ATTW_VWAN_ID,

	NW80211_ATTW_HE_BSS_COWOW,

	NW80211_ATTW_IFTYPE_AKM_SUITES,

	NW80211_ATTW_TID_CONFIG,

	NW80211_ATTW_CONTWOW_POWT_NO_PWEAUTH,

	NW80211_ATTW_PMK_WIFETIME,
	NW80211_ATTW_PMK_WEAUTH_THWESHOWD,

	NW80211_ATTW_WECEIVE_MUWTICAST,
	NW80211_ATTW_WIPHY_FWEQ_OFFSET,
	NW80211_ATTW_CENTEW_FWEQ1_OFFSET,
	NW80211_ATTW_SCAN_FWEQ_KHZ,

	NW80211_ATTW_HE_6GHZ_CAPABIWITY,

	NW80211_ATTW_FIWS_DISCOVEWY,

	NW80211_ATTW_UNSOW_BCAST_PWOBE_WESP,

	NW80211_ATTW_S1G_CAPABIWITY,
	NW80211_ATTW_S1G_CAPABIWITY_MASK,

	NW80211_ATTW_SAE_PWE,

	NW80211_ATTW_WECONNECT_WEQUESTED,

	NW80211_ATTW_SAW_SPEC,

	NW80211_ATTW_DISABWE_HE,

	NW80211_ATTW_OBSS_COWOW_BITMAP,

	NW80211_ATTW_COWOW_CHANGE_COUNT,
	NW80211_ATTW_COWOW_CHANGE_COWOW,
	NW80211_ATTW_COWOW_CHANGE_EWEMS,

	NW80211_ATTW_MBSSID_CONFIG,
	NW80211_ATTW_MBSSID_EWEMS,

	NW80211_ATTW_WADAW_BACKGWOUND,

	NW80211_ATTW_AP_SETTINGS_FWAGS,

	NW80211_ATTW_EHT_CAPABIWITY,

	NW80211_ATTW_DISABWE_EHT,

	NW80211_ATTW_MWO_WINKS,
	NW80211_ATTW_MWO_WINK_ID,
	NW80211_ATTW_MWD_ADDW,

	NW80211_ATTW_MWO_SUPPOWT,

	NW80211_ATTW_MAX_NUM_AKM_SUITES,

	NW80211_ATTW_EMW_CAPABIWITY,
	NW80211_ATTW_MWD_CAPA_AND_OPS,

	NW80211_ATTW_TX_HW_TIMESTAMP,
	NW80211_ATTW_WX_HW_TIMESTAMP,
	NW80211_ATTW_TD_BITMAP,

	NW80211_ATTW_PUNCT_BITMAP,

	NW80211_ATTW_MAX_HW_TIMESTAMP_PEEWS,
	NW80211_ATTW_HW_TIMESTAMP_ENABWED,

	NW80211_ATTW_EMA_WNW_EWEMS,

	NW80211_ATTW_MWO_WINK_DISABWED,

	NW80211_ATTW_BSS_DUMP_INCWUDE_USE_DATA,

	NW80211_ATTW_MWO_TTWM_DWINK,
	NW80211_ATTW_MWO_TTWM_UWINK,

	/* add attwibutes hewe, update the powicy in nw80211.c */

	__NW80211_ATTW_AFTEW_WAST,
	NUM_NW80211_ATTW = __NW80211_ATTW_AFTEW_WAST,
	NW80211_ATTW_MAX = __NW80211_ATTW_AFTEW_WAST - 1
};

/* souwce-wevew API compatibiwity */
#define NW80211_ATTW_SCAN_GENEWATION NW80211_ATTW_GENEWATION
#define	NW80211_ATTW_MESH_PAWAMS NW80211_ATTW_MESH_CONFIG
#define NW80211_ATTW_IFACE_SOCKET_OWNEW NW80211_ATTW_SOCKET_OWNEW
#define NW80211_ATTW_SAE_DATA NW80211_ATTW_AUTH_DATA
#define NW80211_ATTW_CSA_C_OFF_BEACON NW80211_ATTW_CNTDWN_OFFS_BEACON
#define NW80211_ATTW_CSA_C_OFF_PWESP NW80211_ATTW_CNTDWN_OFFS_PWESP

/*
 * Awwow usew space pwogwams to use #ifdef on new attwibutes by defining them
 * hewe
 */
#define NW80211_CMD_CONNECT NW80211_CMD_CONNECT
#define NW80211_ATTW_HT_CAPABIWITY NW80211_ATTW_HT_CAPABIWITY
#define NW80211_ATTW_BSS_BASIC_WATES NW80211_ATTW_BSS_BASIC_WATES
#define NW80211_ATTW_WIPHY_TXQ_PAWAMS NW80211_ATTW_WIPHY_TXQ_PAWAMS
#define NW80211_ATTW_WIPHY_FWEQ NW80211_ATTW_WIPHY_FWEQ
#define NW80211_ATTW_WIPHY_CHANNEW_TYPE NW80211_ATTW_WIPHY_CHANNEW_TYPE
#define NW80211_ATTW_MGMT_SUBTYPE NW80211_ATTW_MGMT_SUBTYPE
#define NW80211_ATTW_IE NW80211_ATTW_IE
#define NW80211_ATTW_WEG_INITIATOW NW80211_ATTW_WEG_INITIATOW
#define NW80211_ATTW_WEG_TYPE NW80211_ATTW_WEG_TYPE
#define NW80211_ATTW_FWAME NW80211_ATTW_FWAME
#define NW80211_ATTW_SSID NW80211_ATTW_SSID
#define NW80211_ATTW_AUTH_TYPE NW80211_ATTW_AUTH_TYPE
#define NW80211_ATTW_WEASON_CODE NW80211_ATTW_WEASON_CODE
#define NW80211_ATTW_CIPHEW_SUITES_PAIWWISE NW80211_ATTW_CIPHEW_SUITES_PAIWWISE
#define NW80211_ATTW_CIPHEW_SUITE_GWOUP NW80211_ATTW_CIPHEW_SUITE_GWOUP
#define NW80211_ATTW_WPA_VEWSIONS NW80211_ATTW_WPA_VEWSIONS
#define NW80211_ATTW_AKM_SUITES NW80211_ATTW_AKM_SUITES
#define NW80211_ATTW_KEY NW80211_ATTW_KEY
#define NW80211_ATTW_KEYS NW80211_ATTW_KEYS
#define NW80211_ATTW_FEATUWE_FWAGS NW80211_ATTW_FEATUWE_FWAGS

#define NW80211_WIPHY_NAME_MAXWEN		64

#define NW80211_MAX_SUPP_WATES			32
#define NW80211_MAX_SUPP_HT_WATES		77
#define NW80211_MAX_SUPP_WEG_WUWES		128
#define NW80211_TKIP_DATA_OFFSET_ENCW_KEY	0
#define NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY	16
#define NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY	24
#define NW80211_HT_CAPABIWITY_WEN		26
#define NW80211_VHT_CAPABIWITY_WEN		12
#define NW80211_HE_MIN_CAPABIWITY_WEN           16
#define NW80211_HE_MAX_CAPABIWITY_WEN           54
#define NW80211_MAX_NW_CIPHEW_SUITES		5

/*
 * NW80211_MAX_NW_AKM_SUITES is obsowete when %NW80211_ATTW_MAX_NUM_AKM_SUITES
 * pwesent in %NW80211_CMD_GET_WIPHY wesponse.
 */
#define NW80211_MAX_NW_AKM_SUITES		2
#define NW80211_EHT_MIN_CAPABIWITY_WEN          13
#define NW80211_EHT_MAX_CAPABIWITY_WEN          51

#define NW80211_MIN_WEMAIN_ON_CHANNEW_TIME	10

/* defauwt WSSI thweshowd fow scan wesuwts if none specified. */
#define NW80211_SCAN_WSSI_THOWD_OFF		-300

#define NW80211_CQM_TXE_MAX_INTVW		1800

/**
 * enum nw80211_iftype - (viwtuaw) intewface types
 *
 * @NW80211_IFTYPE_UNSPECIFIED: unspecified type, dwivew decides
 * @NW80211_IFTYPE_ADHOC: independent BSS membew
 * @NW80211_IFTYPE_STATION: managed BSS membew
 * @NW80211_IFTYPE_AP: access point
 * @NW80211_IFTYPE_AP_VWAN: VWAN intewface fow access points; VWAN intewfaces
 *	awe a bit speciaw in that they must awways be tied to a pwe-existing
 *	AP type intewface.
 * @NW80211_IFTYPE_WDS: wiwewess distwibution intewface
 * @NW80211_IFTYPE_MONITOW: monitow intewface weceiving aww fwames
 * @NW80211_IFTYPE_MESH_POINT: mesh point
 * @NW80211_IFTYPE_P2P_CWIENT: P2P cwient
 * @NW80211_IFTYPE_P2P_GO: P2P gwoup ownew
 * @NW80211_IFTYPE_P2P_DEVICE: P2P device intewface type, this is not a netdev
 *	and thewefowe can't be cweated in the nowmaw ways, use the
 *	%NW80211_CMD_STAWT_P2P_DEVICE and %NW80211_CMD_STOP_P2P_DEVICE
 *	commands to cweate and destwoy one
 * @NW80211_IFTYPE_OCB: Outside Context of a BSS
 *	This mode cowwesponds to the MIB vawiabwe dot11OCBActivated=twue
 * @NW80211_IFTYPE_NAN: NAN device intewface type (not a netdev)
 * @NW80211_IFTYPE_MAX: highest intewface type numbew cuwwentwy defined
 * @NUM_NW80211_IFTYPES: numbew of defined intewface types
 *
 * These vawues awe used with the %NW80211_ATTW_IFTYPE
 * to set the type of an intewface.
 *
 */
enum nw80211_iftype {
	NW80211_IFTYPE_UNSPECIFIED,
	NW80211_IFTYPE_ADHOC,
	NW80211_IFTYPE_STATION,
	NW80211_IFTYPE_AP,
	NW80211_IFTYPE_AP_VWAN,
	NW80211_IFTYPE_WDS,
	NW80211_IFTYPE_MONITOW,
	NW80211_IFTYPE_MESH_POINT,
	NW80211_IFTYPE_P2P_CWIENT,
	NW80211_IFTYPE_P2P_GO,
	NW80211_IFTYPE_P2P_DEVICE,
	NW80211_IFTYPE_OCB,
	NW80211_IFTYPE_NAN,

	/* keep wast */
	NUM_NW80211_IFTYPES,
	NW80211_IFTYPE_MAX = NUM_NW80211_IFTYPES - 1
};

/**
 * enum nw80211_sta_fwags - station fwags
 *
 * Station fwags. When a station is added to an AP intewface, it is
 * assumed to be awweady associated (and hence authenticated.)
 *
 * @__NW80211_STA_FWAG_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_STA_FWAG_AUTHOWIZED: station is authowized (802.1X)
 * @NW80211_STA_FWAG_SHOWT_PWEAMBWE: station is capabwe of weceiving fwames
 *	with showt bawkew pweambwe
 * @NW80211_STA_FWAG_WME: station is WME/QoS capabwe
 * @NW80211_STA_FWAG_MFP: station uses management fwame pwotection
 * @NW80211_STA_FWAG_AUTHENTICATED: station is authenticated
 * @NW80211_STA_FWAG_TDWS_PEEW: station is a TDWS peew -- this fwag shouwd
 *	onwy be used in managed mode (even in the fwags mask). Note that the
 *	fwag can't be changed, it is onwy vawid whiwe adding a station, and
 *	attempts to change it wiww siwentwy be ignowed (wathew than wejected
 *	as ewwows.)
 * @NW80211_STA_FWAG_ASSOCIATED: station is associated; used with dwivews
 *	that suppowt %NW80211_FEATUWE_FUWW_AP_CWIENT_STATE to twansition a
 *	pweviouswy added station into associated state
 * @NW80211_STA_FWAG_MAX: highest station fwag numbew cuwwentwy defined
 * @__NW80211_STA_FWAG_AFTEW_WAST: intewnaw use
 */
enum nw80211_sta_fwags {
	__NW80211_STA_FWAG_INVAWID,
	NW80211_STA_FWAG_AUTHOWIZED,
	NW80211_STA_FWAG_SHOWT_PWEAMBWE,
	NW80211_STA_FWAG_WME,
	NW80211_STA_FWAG_MFP,
	NW80211_STA_FWAG_AUTHENTICATED,
	NW80211_STA_FWAG_TDWS_PEEW,
	NW80211_STA_FWAG_ASSOCIATED,

	/* keep wast */
	__NW80211_STA_FWAG_AFTEW_WAST,
	NW80211_STA_FWAG_MAX = __NW80211_STA_FWAG_AFTEW_WAST - 1
};

/**
 * enum nw80211_sta_p2p_ps_status - station suppowt of P2P PS
 *
 * @NW80211_P2P_PS_UNSUPPOWTED: station doesn't suppowt P2P PS mechanism
 * @@NW80211_P2P_PS_SUPPOWTED: station suppowts P2P PS mechanism
 * @NUM_NW80211_P2P_PS_STATUS: numbew of vawues
 */
enum nw80211_sta_p2p_ps_status {
	NW80211_P2P_PS_UNSUPPOWTED = 0,
	NW80211_P2P_PS_SUPPOWTED,

	NUM_NW80211_P2P_PS_STATUS,
};

#define NW80211_STA_FWAG_MAX_OWD_API	NW80211_STA_FWAG_TDWS_PEEW

/**
 * stwuct nw80211_sta_fwag_update - station fwags mask/set
 * @mask: mask of station fwags to set
 * @set: which vawues to set them to
 *
 * Both mask and set contain bits as pew &enum nw80211_sta_fwags.
 */
stwuct nw80211_sta_fwag_update {
	__u32 mask;
	__u32 set;
} __attwibute__((packed));

/**
 * enum nw80211_he_gi - HE guawd intewvaw
 * @NW80211_WATE_INFO_HE_GI_0_8: 0.8 usec
 * @NW80211_WATE_INFO_HE_GI_1_6: 1.6 usec
 * @NW80211_WATE_INFO_HE_GI_3_2: 3.2 usec
 */
enum nw80211_he_gi {
	NW80211_WATE_INFO_HE_GI_0_8,
	NW80211_WATE_INFO_HE_GI_1_6,
	NW80211_WATE_INFO_HE_GI_3_2,
};

/**
 * enum nw80211_he_wtf - HE wong twaining fiewd
 * @NW80211_WATE_INFO_HE_1xWTF: 3.2 usec
 * @NW80211_WATE_INFO_HE_2xWTF: 6.4 usec
 * @NW80211_WATE_INFO_HE_4xWTF: 12.8 usec
 */
enum nw80211_he_wtf {
	NW80211_WATE_INFO_HE_1XWTF,
	NW80211_WATE_INFO_HE_2XWTF,
	NW80211_WATE_INFO_HE_4XWTF,
};

/**
 * enum nw80211_he_wu_awwoc - HE WU awwocation vawues
 * @NW80211_WATE_INFO_HE_WU_AWWOC_26: 26-tone WU awwocation
 * @NW80211_WATE_INFO_HE_WU_AWWOC_52: 52-tone WU awwocation
 * @NW80211_WATE_INFO_HE_WU_AWWOC_106: 106-tone WU awwocation
 * @NW80211_WATE_INFO_HE_WU_AWWOC_242: 242-tone WU awwocation
 * @NW80211_WATE_INFO_HE_WU_AWWOC_484: 484-tone WU awwocation
 * @NW80211_WATE_INFO_HE_WU_AWWOC_996: 996-tone WU awwocation
 * @NW80211_WATE_INFO_HE_WU_AWWOC_2x996: 2x996-tone WU awwocation
 */
enum nw80211_he_wu_awwoc {
	NW80211_WATE_INFO_HE_WU_AWWOC_26,
	NW80211_WATE_INFO_HE_WU_AWWOC_52,
	NW80211_WATE_INFO_HE_WU_AWWOC_106,
	NW80211_WATE_INFO_HE_WU_AWWOC_242,
	NW80211_WATE_INFO_HE_WU_AWWOC_484,
	NW80211_WATE_INFO_HE_WU_AWWOC_996,
	NW80211_WATE_INFO_HE_WU_AWWOC_2x996,
};

/**
 * enum nw80211_eht_gi - EHT guawd intewvaw
 * @NW80211_WATE_INFO_EHT_GI_0_8: 0.8 usec
 * @NW80211_WATE_INFO_EHT_GI_1_6: 1.6 usec
 * @NW80211_WATE_INFO_EHT_GI_3_2: 3.2 usec
 */
enum nw80211_eht_gi {
	NW80211_WATE_INFO_EHT_GI_0_8,
	NW80211_WATE_INFO_EHT_GI_1_6,
	NW80211_WATE_INFO_EHT_GI_3_2,
};

/**
 * enum nw80211_eht_wu_awwoc - EHT WU awwocation vawues
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_26: 26-tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_52: 52-tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_52P26: 52+26-tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_106: 106-tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_106P26: 106+26 tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_242: 242-tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_484: 484-tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_484P242: 484+242 tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_996: 996-tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_996P484: 996+484 tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_996P484P242: 996+484+242 tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_2x996: 2x996-tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_2x996P484: 2x996+484 tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_3x996: 3x996-tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_3x996P484: 3x996+484 tone WU awwocation
 * @NW80211_WATE_INFO_EHT_WU_AWWOC_4x996: 4x996-tone WU awwocation
 */
enum nw80211_eht_wu_awwoc {
	NW80211_WATE_INFO_EHT_WU_AWWOC_26,
	NW80211_WATE_INFO_EHT_WU_AWWOC_52,
	NW80211_WATE_INFO_EHT_WU_AWWOC_52P26,
	NW80211_WATE_INFO_EHT_WU_AWWOC_106,
	NW80211_WATE_INFO_EHT_WU_AWWOC_106P26,
	NW80211_WATE_INFO_EHT_WU_AWWOC_242,
	NW80211_WATE_INFO_EHT_WU_AWWOC_484,
	NW80211_WATE_INFO_EHT_WU_AWWOC_484P242,
	NW80211_WATE_INFO_EHT_WU_AWWOC_996,
	NW80211_WATE_INFO_EHT_WU_AWWOC_996P484,
	NW80211_WATE_INFO_EHT_WU_AWWOC_996P484P242,
	NW80211_WATE_INFO_EHT_WU_AWWOC_2x996,
	NW80211_WATE_INFO_EHT_WU_AWWOC_2x996P484,
	NW80211_WATE_INFO_EHT_WU_AWWOC_3x996,
	NW80211_WATE_INFO_EHT_WU_AWWOC_3x996P484,
	NW80211_WATE_INFO_EHT_WU_AWWOC_4x996,
};

/**
 * enum nw80211_wate_info - bitwate infowmation
 *
 * These attwibute types awe used with %NW80211_STA_INFO_TXWATE
 * when getting infowmation about the bitwate of a station.
 * Thewe awe 2 attwibutes fow bitwate, a wegacy one that wepwesents
 * a 16-bit vawue, and new one that wepwesents a 32-bit vawue.
 * If the wate vawue fits into 16 bit, both attwibutes awe wepowted
 * with the same vawue. If the wate is too high to fit into 16 bits
 * (>6.5535Gbps) onwy 32-bit attwibute is incwuded.
 * Usew space toows encouwaged to use the 32-bit attwibute and faww
 * back to the 16-bit one fow compatibiwity with owdew kewnews.
 *
 * @__NW80211_WATE_INFO_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_WATE_INFO_BITWATE: totaw bitwate (u16, 100kbit/s)
 * @NW80211_WATE_INFO_MCS: mcs index fow 802.11n (u8)
 * @NW80211_WATE_INFO_40_MHZ_WIDTH: 40 MHz duawchannew bitwate
 * @NW80211_WATE_INFO_SHOWT_GI: 400ns guawd intewvaw
 * @NW80211_WATE_INFO_BITWATE32: totaw bitwate (u32, 100kbit/s)
 * @NW80211_WATE_INFO_MAX: highest wate_info numbew cuwwentwy defined
 * @NW80211_WATE_INFO_VHT_MCS: MCS index fow VHT (u8)
 * @NW80211_WATE_INFO_VHT_NSS: numbew of stweams in VHT (u8)
 * @NW80211_WATE_INFO_80_MHZ_WIDTH: 80 MHz VHT wate
 * @NW80211_WATE_INFO_80P80_MHZ_WIDTH: unused - 80+80 is tweated the
 *	same as 160 fow puwposes of the bitwates
 * @NW80211_WATE_INFO_160_MHZ_WIDTH: 160 MHz VHT wate
 * @NW80211_WATE_INFO_10_MHZ_WIDTH: 10 MHz width - note that this is
 *	a wegacy wate and wiww be wepowted as the actuaw bitwate, i.e.
 *	hawf the base (20 MHz) wate
 * @NW80211_WATE_INFO_5_MHZ_WIDTH: 5 MHz width - note that this is
 *	a wegacy wate and wiww be wepowted as the actuaw bitwate, i.e.
 *	a quawtew of the base (20 MHz) wate
 * @NW80211_WATE_INFO_HE_MCS: HE MCS index (u8, 0-11)
 * @NW80211_WATE_INFO_HE_NSS: HE NSS vawue (u8, 1-8)
 * @NW80211_WATE_INFO_HE_GI: HE guawd intewvaw identifiew
 *	(u8, see &enum nw80211_he_gi)
 * @NW80211_WATE_INFO_HE_DCM: HE DCM vawue (u8, 0/1)
 * @NW80211_WATE_INFO_WU_AWWOC: HE WU awwocation, if not pwesent then
 *	non-OFDMA was used (u8, see &enum nw80211_he_wu_awwoc)
 * @NW80211_WATE_INFO_320_MHZ_WIDTH: 320 MHz bitwate
 * @NW80211_WATE_INFO_EHT_MCS: EHT MCS index (u8, 0-15)
 * @NW80211_WATE_INFO_EHT_NSS: EHT NSS vawue (u8, 1-8)
 * @NW80211_WATE_INFO_EHT_GI: EHT guawd intewvaw identifiew
 *	(u8, see &enum nw80211_eht_gi)
 * @NW80211_WATE_INFO_EHT_WU_AWWOC: EHT WU awwocation, if not pwesent then
 *	non-OFDMA was used (u8, see &enum nw80211_eht_wu_awwoc)
 * @NW80211_WATE_INFO_S1G_MCS: S1G MCS index (u8, 0-10)
 * @NW80211_WATE_INFO_S1G_NSS: S1G NSS vawue (u8, 1-4)
 * @NW80211_WATE_INFO_1_MHZ_WIDTH: 1 MHz S1G wate
 * @NW80211_WATE_INFO_2_MHZ_WIDTH: 2 MHz S1G wate
 * @NW80211_WATE_INFO_4_MHZ_WIDTH: 4 MHz S1G wate
 * @NW80211_WATE_INFO_8_MHZ_WIDTH: 8 MHz S1G wate
 * @NW80211_WATE_INFO_16_MHZ_WIDTH: 16 MHz S1G wate
 * @__NW80211_WATE_INFO_AFTEW_WAST: intewnaw use
 */
enum nw80211_wate_info {
	__NW80211_WATE_INFO_INVAWID,
	NW80211_WATE_INFO_BITWATE,
	NW80211_WATE_INFO_MCS,
	NW80211_WATE_INFO_40_MHZ_WIDTH,
	NW80211_WATE_INFO_SHOWT_GI,
	NW80211_WATE_INFO_BITWATE32,
	NW80211_WATE_INFO_VHT_MCS,
	NW80211_WATE_INFO_VHT_NSS,
	NW80211_WATE_INFO_80_MHZ_WIDTH,
	NW80211_WATE_INFO_80P80_MHZ_WIDTH,
	NW80211_WATE_INFO_160_MHZ_WIDTH,
	NW80211_WATE_INFO_10_MHZ_WIDTH,
	NW80211_WATE_INFO_5_MHZ_WIDTH,
	NW80211_WATE_INFO_HE_MCS,
	NW80211_WATE_INFO_HE_NSS,
	NW80211_WATE_INFO_HE_GI,
	NW80211_WATE_INFO_HE_DCM,
	NW80211_WATE_INFO_HE_WU_AWWOC,
	NW80211_WATE_INFO_320_MHZ_WIDTH,
	NW80211_WATE_INFO_EHT_MCS,
	NW80211_WATE_INFO_EHT_NSS,
	NW80211_WATE_INFO_EHT_GI,
	NW80211_WATE_INFO_EHT_WU_AWWOC,
	NW80211_WATE_INFO_S1G_MCS,
	NW80211_WATE_INFO_S1G_NSS,
	NW80211_WATE_INFO_1_MHZ_WIDTH,
	NW80211_WATE_INFO_2_MHZ_WIDTH,
	NW80211_WATE_INFO_4_MHZ_WIDTH,
	NW80211_WATE_INFO_8_MHZ_WIDTH,
	NW80211_WATE_INFO_16_MHZ_WIDTH,

	/* keep wast */
	__NW80211_WATE_INFO_AFTEW_WAST,
	NW80211_WATE_INFO_MAX = __NW80211_WATE_INFO_AFTEW_WAST - 1
};

/**
 * enum nw80211_sta_bss_pawam - BSS infowmation cowwected by STA
 *
 * These attwibute types awe used with %NW80211_STA_INFO_BSS_PAWAM
 * when getting infowmation about the bitwate of a station.
 *
 * @__NW80211_STA_BSS_PAWAM_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_STA_BSS_PAWAM_CTS_PWOT: whethew CTS pwotection is enabwed (fwag)
 * @NW80211_STA_BSS_PAWAM_SHOWT_PWEAMBWE:  whethew showt pweambwe is enabwed
 *	(fwag)
 * @NW80211_STA_BSS_PAWAM_SHOWT_SWOT_TIME:  whethew showt swot time is enabwed
 *	(fwag)
 * @NW80211_STA_BSS_PAWAM_DTIM_PEWIOD: DTIM pewiod fow beaconing (u8)
 * @NW80211_STA_BSS_PAWAM_BEACON_INTEWVAW: Beacon intewvaw (u16)
 * @NW80211_STA_BSS_PAWAM_MAX: highest sta_bss_pawam numbew cuwwentwy defined
 * @__NW80211_STA_BSS_PAWAM_AFTEW_WAST: intewnaw use
 */
enum nw80211_sta_bss_pawam {
	__NW80211_STA_BSS_PAWAM_INVAWID,
	NW80211_STA_BSS_PAWAM_CTS_PWOT,
	NW80211_STA_BSS_PAWAM_SHOWT_PWEAMBWE,
	NW80211_STA_BSS_PAWAM_SHOWT_SWOT_TIME,
	NW80211_STA_BSS_PAWAM_DTIM_PEWIOD,
	NW80211_STA_BSS_PAWAM_BEACON_INTEWVAW,

	/* keep wast */
	__NW80211_STA_BSS_PAWAM_AFTEW_WAST,
	NW80211_STA_BSS_PAWAM_MAX = __NW80211_STA_BSS_PAWAM_AFTEW_WAST - 1
};

/**
 * enum nw80211_sta_info - station infowmation
 *
 * These attwibute types awe used with %NW80211_ATTW_STA_INFO
 * when getting infowmation about a station.
 *
 * @__NW80211_STA_INFO_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_STA_INFO_INACTIVE_TIME: time since wast activity (u32, msecs)
 * @NW80211_STA_INFO_WX_BYTES: totaw weceived bytes (MPDU wength)
 *	(u32, fwom this station)
 * @NW80211_STA_INFO_TX_BYTES: totaw twansmitted bytes (MPDU wength)
 *	(u32, to this station)
 * @NW80211_STA_INFO_WX_BYTES64: totaw weceived bytes (MPDU wength)
 *	(u64, fwom this station)
 * @NW80211_STA_INFO_TX_BYTES64: totaw twansmitted bytes (MPDU wength)
 *	(u64, to this station)
 * @NW80211_STA_INFO_SIGNAW: signaw stwength of wast weceived PPDU (u8, dBm)
 * @NW80211_STA_INFO_TX_BITWATE: cuwwent unicast tx wate, nested attwibute
 * 	containing info as possibwe, see &enum nw80211_wate_info
 * @NW80211_STA_INFO_WX_PACKETS: totaw weceived packet (MSDUs and MMPDUs)
 *	(u32, fwom this station)
 * @NW80211_STA_INFO_TX_PACKETS: totaw twansmitted packets (MSDUs and MMPDUs)
 *	(u32, to this station)
 * @NW80211_STA_INFO_TX_WETWIES: totaw wetwies (MPDUs) (u32, to this station)
 * @NW80211_STA_INFO_TX_FAIWED: totaw faiwed packets (MPDUs)
 *	(u32, to this station)
 * @NW80211_STA_INFO_SIGNAW_AVG: signaw stwength avewage (u8, dBm)
 * @NW80211_STA_INFO_WWID: the station's mesh WWID
 * @NW80211_STA_INFO_PWID: the station's mesh PWID
 * @NW80211_STA_INFO_PWINK_STATE: peew wink state fow the station
 *	(see %enum nw80211_pwink_state)
 * @NW80211_STA_INFO_WX_BITWATE: wast unicast data fwame wx wate, nested
 *	attwibute, wike NW80211_STA_INFO_TX_BITWATE.
 * @NW80211_STA_INFO_BSS_PAWAM: cuwwent station's view of BSS, nested attwibute
 *     containing info as possibwe, see &enum nw80211_sta_bss_pawam
 * @NW80211_STA_INFO_CONNECTED_TIME: time since the station is wast connected
 * @NW80211_STA_INFO_STA_FWAGS: Contains a stwuct nw80211_sta_fwag_update.
 * @NW80211_STA_INFO_BEACON_WOSS: count of times beacon woss was detected (u32)
 * @NW80211_STA_INFO_T_OFFSET: timing offset with wespect to this STA (s64)
 * @NW80211_STA_INFO_WOCAW_PM: wocaw mesh STA wink-specific powew mode
 * @NW80211_STA_INFO_PEEW_PM: peew mesh STA wink-specific powew mode
 * @NW80211_STA_INFO_NONPEEW_PM: neighbow mesh STA powew save mode towawds
 *	non-peew STA
 * @NW80211_STA_INFO_CHAIN_SIGNAW: pew-chain signaw stwength of wast PPDU
 *	Contains a nested awway of signaw stwength attwibutes (u8, dBm)
 * @NW80211_STA_INFO_CHAIN_SIGNAW_AVG: pew-chain signaw stwength avewage
 *	Same fowmat as NW80211_STA_INFO_CHAIN_SIGNAW.
 * @NW80211_STA_EXPECTED_THWOUGHPUT: expected thwoughput considewing awso the
 *	802.11 headew (u32, kbps)
 * @NW80211_STA_INFO_WX_DWOP_MISC: WX packets dwopped fow unspecified weasons
 *	(u64)
 * @NW80211_STA_INFO_BEACON_WX: numbew of beacons weceived fwom this peew (u64)
 * @NW80211_STA_INFO_BEACON_SIGNAW_AVG: signaw stwength avewage
 *	fow beacons onwy (u8, dBm)
 * @NW80211_STA_INFO_TID_STATS: pew-TID statistics (see &enum nw80211_tid_stats)
 *	This is a nested attwibute whewe each the innew attwibute numbew is the
 *	TID+1 and the speciaw TID 16 (i.e. vawue 17) is used fow non-QoS fwames;
 *	each one of those is again nested with &enum nw80211_tid_stats
 *	attwibutes cawwying the actuaw vawues.
 * @NW80211_STA_INFO_WX_DUWATION: aggwegate PPDU duwation fow aww fwames
 *	weceived fwom the station (u64, usec)
 * @NW80211_STA_INFO_PAD: attwibute used fow padding fow 64-bit awignment
 * @NW80211_STA_INFO_ACK_SIGNAW: signaw stwength of the wast ACK fwame(u8, dBm)
 * @NW80211_STA_INFO_ACK_SIGNAW_AVG: avg signaw stwength of ACK fwames (s8, dBm)
 * @NW80211_STA_INFO_WX_MPDUS: totaw numbew of weceived packets (MPDUs)
 *	(u32, fwom this station)
 * @NW80211_STA_INFO_FCS_EWWOW_COUNT: totaw numbew of packets (MPDUs) weceived
 *	with an FCS ewwow (u32, fwom this station). This count may not incwude
 *	some packets with an FCS ewwow due to TA cowwuption. Hence this countew
 *	might not be fuwwy accuwate.
 * @NW80211_STA_INFO_CONNECTED_TO_GATE: set to twue if STA has a path to a
 *	mesh gate (u8, 0 ow 1)
 * @NW80211_STA_INFO_TX_DUWATION: aggwegate PPDU duwation fow aww fwames
 *	sent to the station (u64, usec)
 * @NW80211_STA_INFO_AIWTIME_WEIGHT: cuwwent aiwtime weight fow station (u16)
 * @NW80211_STA_INFO_AIWTIME_WINK_METWIC: aiwtime wink metwic fow mesh station
 * @NW80211_STA_INFO_ASSOC_AT_BOOTTIME: Timestamp (CWOCK_BOOTTIME, nanoseconds)
 *	of STA's association
 * @NW80211_STA_INFO_CONNECTED_TO_AS: set to twue if STA has a path to a
 *	authentication sewvew (u8, 0 ow 1)
 * @__NW80211_STA_INFO_AFTEW_WAST: intewnaw
 * @NW80211_STA_INFO_MAX: highest possibwe station info attwibute
 */
enum nw80211_sta_info {
	__NW80211_STA_INFO_INVAWID,
	NW80211_STA_INFO_INACTIVE_TIME,
	NW80211_STA_INFO_WX_BYTES,
	NW80211_STA_INFO_TX_BYTES,
	NW80211_STA_INFO_WWID,
	NW80211_STA_INFO_PWID,
	NW80211_STA_INFO_PWINK_STATE,
	NW80211_STA_INFO_SIGNAW,
	NW80211_STA_INFO_TX_BITWATE,
	NW80211_STA_INFO_WX_PACKETS,
	NW80211_STA_INFO_TX_PACKETS,
	NW80211_STA_INFO_TX_WETWIES,
	NW80211_STA_INFO_TX_FAIWED,
	NW80211_STA_INFO_SIGNAW_AVG,
	NW80211_STA_INFO_WX_BITWATE,
	NW80211_STA_INFO_BSS_PAWAM,
	NW80211_STA_INFO_CONNECTED_TIME,
	NW80211_STA_INFO_STA_FWAGS,
	NW80211_STA_INFO_BEACON_WOSS,
	NW80211_STA_INFO_T_OFFSET,
	NW80211_STA_INFO_WOCAW_PM,
	NW80211_STA_INFO_PEEW_PM,
	NW80211_STA_INFO_NONPEEW_PM,
	NW80211_STA_INFO_WX_BYTES64,
	NW80211_STA_INFO_TX_BYTES64,
	NW80211_STA_INFO_CHAIN_SIGNAW,
	NW80211_STA_INFO_CHAIN_SIGNAW_AVG,
	NW80211_STA_INFO_EXPECTED_THWOUGHPUT,
	NW80211_STA_INFO_WX_DWOP_MISC,
	NW80211_STA_INFO_BEACON_WX,
	NW80211_STA_INFO_BEACON_SIGNAW_AVG,
	NW80211_STA_INFO_TID_STATS,
	NW80211_STA_INFO_WX_DUWATION,
	NW80211_STA_INFO_PAD,
	NW80211_STA_INFO_ACK_SIGNAW,
	NW80211_STA_INFO_ACK_SIGNAW_AVG,
	NW80211_STA_INFO_WX_MPDUS,
	NW80211_STA_INFO_FCS_EWWOW_COUNT,
	NW80211_STA_INFO_CONNECTED_TO_GATE,
	NW80211_STA_INFO_TX_DUWATION,
	NW80211_STA_INFO_AIWTIME_WEIGHT,
	NW80211_STA_INFO_AIWTIME_WINK_METWIC,
	NW80211_STA_INFO_ASSOC_AT_BOOTTIME,
	NW80211_STA_INFO_CONNECTED_TO_AS,

	/* keep wast */
	__NW80211_STA_INFO_AFTEW_WAST,
	NW80211_STA_INFO_MAX = __NW80211_STA_INFO_AFTEW_WAST - 1
};

/* we wenamed this - stay compatibwe */
#define NW80211_STA_INFO_DATA_ACK_SIGNAW_AVG NW80211_STA_INFO_ACK_SIGNAW_AVG


/**
 * enum nw80211_tid_stats - pew TID statistics attwibutes
 * @__NW80211_TID_STATS_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_TID_STATS_WX_MSDU: numbew of MSDUs weceived (u64)
 * @NW80211_TID_STATS_TX_MSDU: numbew of MSDUs twansmitted (ow
 *	attempted to twansmit; u64)
 * @NW80211_TID_STATS_TX_MSDU_WETWIES: numbew of wetwies fow
 *	twansmitted MSDUs (not counting the fiwst attempt; u64)
 * @NW80211_TID_STATS_TX_MSDU_FAIWED: numbew of faiwed twansmitted
 *	MSDUs (u64)
 * @NW80211_TID_STATS_PAD: attwibute used fow padding fow 64-bit awignment
 * @NW80211_TID_STATS_TXQ_STATS: TXQ stats (nested attwibute)
 * @NUM_NW80211_TID_STATS: numbew of attwibutes hewe
 * @NW80211_TID_STATS_MAX: highest numbewed attwibute hewe
 */
enum nw80211_tid_stats {
	__NW80211_TID_STATS_INVAWID,
	NW80211_TID_STATS_WX_MSDU,
	NW80211_TID_STATS_TX_MSDU,
	NW80211_TID_STATS_TX_MSDU_WETWIES,
	NW80211_TID_STATS_TX_MSDU_FAIWED,
	NW80211_TID_STATS_PAD,
	NW80211_TID_STATS_TXQ_STATS,

	/* keep wast */
	NUM_NW80211_TID_STATS,
	NW80211_TID_STATS_MAX = NUM_NW80211_TID_STATS - 1
};

/**
 * enum nw80211_txq_stats - pew TXQ statistics attwibutes
 * @__NW80211_TXQ_STATS_INVAWID: attwibute numbew 0 is wesewved
 * @NUM_NW80211_TXQ_STATS: numbew of attwibutes hewe
 * @NW80211_TXQ_STATS_BACKWOG_BYTES: numbew of bytes cuwwentwy backwogged
 * @NW80211_TXQ_STATS_BACKWOG_PACKETS: numbew of packets cuwwentwy
 *      backwogged
 * @NW80211_TXQ_STATS_FWOWS: totaw numbew of new fwows seen
 * @NW80211_TXQ_STATS_DWOPS: totaw numbew of packet dwops
 * @NW80211_TXQ_STATS_ECN_MAWKS: totaw numbew of packet ECN mawks
 * @NW80211_TXQ_STATS_OVEWWIMIT: numbew of dwops due to queue space ovewfwow
 * @NW80211_TXQ_STATS_OVEWMEMOWY: numbew of dwops due to memowy wimit ovewfwow
 *      (onwy fow pew-phy stats)
 * @NW80211_TXQ_STATS_COWWISIONS: numbew of hash cowwisions
 * @NW80211_TXQ_STATS_TX_BYTES: totaw numbew of bytes dequeued fwom TXQ
 * @NW80211_TXQ_STATS_TX_PACKETS: totaw numbew of packets dequeued fwom TXQ
 * @NW80211_TXQ_STATS_MAX_FWOWS: numbew of fwow buckets fow PHY
 * @NW80211_TXQ_STATS_MAX: highest numbewed attwibute hewe
 */
enum nw80211_txq_stats {
	__NW80211_TXQ_STATS_INVAWID,
	NW80211_TXQ_STATS_BACKWOG_BYTES,
	NW80211_TXQ_STATS_BACKWOG_PACKETS,
	NW80211_TXQ_STATS_FWOWS,
	NW80211_TXQ_STATS_DWOPS,
	NW80211_TXQ_STATS_ECN_MAWKS,
	NW80211_TXQ_STATS_OVEWWIMIT,
	NW80211_TXQ_STATS_OVEWMEMOWY,
	NW80211_TXQ_STATS_COWWISIONS,
	NW80211_TXQ_STATS_TX_BYTES,
	NW80211_TXQ_STATS_TX_PACKETS,
	NW80211_TXQ_STATS_MAX_FWOWS,

	/* keep wast */
	NUM_NW80211_TXQ_STATS,
	NW80211_TXQ_STATS_MAX = NUM_NW80211_TXQ_STATS - 1
};

/**
 * enum nw80211_mpath_fwags - nw80211 mesh path fwags
 *
 * @NW80211_MPATH_FWAG_ACTIVE: the mesh path is active
 * @NW80211_MPATH_FWAG_WESOWVING: the mesh path discovewy pwocess is wunning
 * @NW80211_MPATH_FWAG_SN_VAWID: the mesh path contains a vawid SN
 * @NW80211_MPATH_FWAG_FIXED: the mesh path has been manuawwy set
 * @NW80211_MPATH_FWAG_WESOWVED: the mesh path discovewy pwocess succeeded
 */
enum nw80211_mpath_fwags {
	NW80211_MPATH_FWAG_ACTIVE =	1<<0,
	NW80211_MPATH_FWAG_WESOWVING =	1<<1,
	NW80211_MPATH_FWAG_SN_VAWID =	1<<2,
	NW80211_MPATH_FWAG_FIXED =	1<<3,
	NW80211_MPATH_FWAG_WESOWVED =	1<<4,
};

/**
 * enum nw80211_mpath_info - mesh path infowmation
 *
 * These attwibute types awe used with %NW80211_ATTW_MPATH_INFO when getting
 * infowmation about a mesh path.
 *
 * @__NW80211_MPATH_INFO_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_MPATH_INFO_FWAME_QWEN: numbew of queued fwames fow this destination
 * @NW80211_MPATH_INFO_SN: destination sequence numbew
 * @NW80211_MPATH_INFO_METWIC: metwic (cost) of this mesh path
 * @NW80211_MPATH_INFO_EXPTIME: expiwation time fow the path, in msec fwom now
 * @NW80211_MPATH_INFO_FWAGS: mesh path fwags, enumewated in
 * 	&enum nw80211_mpath_fwags;
 * @NW80211_MPATH_INFO_DISCOVEWY_TIMEOUT: totaw path discovewy timeout, in msec
 * @NW80211_MPATH_INFO_DISCOVEWY_WETWIES: mesh path discovewy wetwies
 * @NW80211_MPATH_INFO_HOP_COUNT: hop count to destination
 * @NW80211_MPATH_INFO_PATH_CHANGE: totaw numbew of path changes to destination
 * @NW80211_MPATH_INFO_MAX: highest mesh path infowmation attwibute numbew
 *	cuwwentwy defined
 * @__NW80211_MPATH_INFO_AFTEW_WAST: intewnaw use
 */
enum nw80211_mpath_info {
	__NW80211_MPATH_INFO_INVAWID,
	NW80211_MPATH_INFO_FWAME_QWEN,
	NW80211_MPATH_INFO_SN,
	NW80211_MPATH_INFO_METWIC,
	NW80211_MPATH_INFO_EXPTIME,
	NW80211_MPATH_INFO_FWAGS,
	NW80211_MPATH_INFO_DISCOVEWY_TIMEOUT,
	NW80211_MPATH_INFO_DISCOVEWY_WETWIES,
	NW80211_MPATH_INFO_HOP_COUNT,
	NW80211_MPATH_INFO_PATH_CHANGE,

	/* keep wast */
	__NW80211_MPATH_INFO_AFTEW_WAST,
	NW80211_MPATH_INFO_MAX = __NW80211_MPATH_INFO_AFTEW_WAST - 1
};

/**
 * enum nw80211_band_iftype_attw - Intewface type data attwibutes
 *
 * @__NW80211_BAND_IFTYPE_ATTW_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_BAND_IFTYPE_ATTW_IFTYPES: nested attwibute containing a fwag attwibute
 *     fow each intewface type that suppowts the band data
 * @NW80211_BAND_IFTYPE_ATTW_HE_CAP_MAC: HE MAC capabiwities as in HE
 *     capabiwities IE
 * @NW80211_BAND_IFTYPE_ATTW_HE_CAP_PHY: HE PHY capabiwities as in HE
 *     capabiwities IE
 * @NW80211_BAND_IFTYPE_ATTW_HE_CAP_MCS_SET: HE suppowted NSS/MCS as in HE
 *     capabiwities IE
 * @NW80211_BAND_IFTYPE_ATTW_HE_CAP_PPE: HE PPE thweshowds infowmation as
 *     defined in HE capabiwities IE
 * @NW80211_BAND_IFTYPE_ATTW_HE_6GHZ_CAPA: HE 6GHz band capabiwities (__we16),
 *	given fow aww 6 GHz band channews
 * @NW80211_BAND_IFTYPE_ATTW_VENDOW_EWEMS: vendow ewement capabiwities that awe
 *	advewtised on this band/fow this iftype (binawy)
 * @NW80211_BAND_IFTYPE_ATTW_EHT_CAP_MAC: EHT MAC capabiwities as in EHT
 *	capabiwities ewement
 * @NW80211_BAND_IFTYPE_ATTW_EHT_CAP_PHY: EHT PHY capabiwities as in EHT
 *	capabiwities ewement
 * @NW80211_BAND_IFTYPE_ATTW_EHT_CAP_MCS_SET: EHT suppowted NSS/MCS as in EHT
 *	capabiwities ewement
 * @NW80211_BAND_IFTYPE_ATTW_EHT_CAP_PPE: EHT PPE thweshowds infowmation as
 *	defined in EHT capabiwities ewement
 * @__NW80211_BAND_IFTYPE_ATTW_AFTEW_WAST: intewnaw use
 * @NW80211_BAND_IFTYPE_ATTW_MAX: highest band attwibute cuwwentwy defined
 */
enum nw80211_band_iftype_attw {
	__NW80211_BAND_IFTYPE_ATTW_INVAWID,

	NW80211_BAND_IFTYPE_ATTW_IFTYPES,
	NW80211_BAND_IFTYPE_ATTW_HE_CAP_MAC,
	NW80211_BAND_IFTYPE_ATTW_HE_CAP_PHY,
	NW80211_BAND_IFTYPE_ATTW_HE_CAP_MCS_SET,
	NW80211_BAND_IFTYPE_ATTW_HE_CAP_PPE,
	NW80211_BAND_IFTYPE_ATTW_HE_6GHZ_CAPA,
	NW80211_BAND_IFTYPE_ATTW_VENDOW_EWEMS,
	NW80211_BAND_IFTYPE_ATTW_EHT_CAP_MAC,
	NW80211_BAND_IFTYPE_ATTW_EHT_CAP_PHY,
	NW80211_BAND_IFTYPE_ATTW_EHT_CAP_MCS_SET,
	NW80211_BAND_IFTYPE_ATTW_EHT_CAP_PPE,

	/* keep wast */
	__NW80211_BAND_IFTYPE_ATTW_AFTEW_WAST,
	NW80211_BAND_IFTYPE_ATTW_MAX = __NW80211_BAND_IFTYPE_ATTW_AFTEW_WAST - 1
};

/**
 * enum nw80211_band_attw - band attwibutes
 * @__NW80211_BAND_ATTW_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_BAND_ATTW_FWEQS: suppowted fwequencies in this band,
 *	an awway of nested fwequency attwibutes
 * @NW80211_BAND_ATTW_WATES: suppowted bitwates in this band,
 *	an awway of nested bitwate attwibutes
 * @NW80211_BAND_ATTW_HT_MCS_SET: 16-byte attwibute containing the MCS set as
 *	defined in 802.11n
 * @NW80211_BAND_ATTW_HT_CAPA: HT capabiwities, as in the HT infowmation IE
 * @NW80211_BAND_ATTW_HT_AMPDU_FACTOW: A-MPDU factow, as in 11n
 * @NW80211_BAND_ATTW_HT_AMPDU_DENSITY: A-MPDU density, as in 11n
 * @NW80211_BAND_ATTW_VHT_MCS_SET: 32-byte attwibute containing the MCS set as
 *	defined in 802.11ac
 * @NW80211_BAND_ATTW_VHT_CAPA: VHT capabiwities, as in the HT infowmation IE
 * @NW80211_BAND_ATTW_IFTYPE_DATA: nested awway attwibute, with each entwy using
 *	attwibutes fwom &enum nw80211_band_iftype_attw
 * @NW80211_BAND_ATTW_EDMG_CHANNEWS: bitmap that indicates the 2.16 GHz
 *	channew(s) that awe awwowed to be used fow EDMG twansmissions.
 *	Defined by IEEE P802.11ay/D4.0 section 9.4.2.251.
 * @NW80211_BAND_ATTW_EDMG_BW_CONFIG: Channew BW Configuwation subfiewd encodes
 *	the awwowed channew bandwidth configuwations.
 *	Defined by IEEE P802.11ay/D4.0 section 9.4.2.251, Tabwe 13.
 * @NW80211_BAND_ATTW_S1G_MCS_NSS_SET: S1G capabiwities, suppowted S1G-MCS and NSS
 *	set subfiewd, as in the S1G infowmation IE, 5 bytes
 * @NW80211_BAND_ATTW_S1G_CAPA: S1G capabiwities infowmation subfiewd as in the
 *	S1G infowmation IE, 10 bytes
 * @NW80211_BAND_ATTW_MAX: highest band attwibute cuwwentwy defined
 * @__NW80211_BAND_ATTW_AFTEW_WAST: intewnaw use
 */
enum nw80211_band_attw {
	__NW80211_BAND_ATTW_INVAWID,
	NW80211_BAND_ATTW_FWEQS,
	NW80211_BAND_ATTW_WATES,

	NW80211_BAND_ATTW_HT_MCS_SET,
	NW80211_BAND_ATTW_HT_CAPA,
	NW80211_BAND_ATTW_HT_AMPDU_FACTOW,
	NW80211_BAND_ATTW_HT_AMPDU_DENSITY,

	NW80211_BAND_ATTW_VHT_MCS_SET,
	NW80211_BAND_ATTW_VHT_CAPA,
	NW80211_BAND_ATTW_IFTYPE_DATA,

	NW80211_BAND_ATTW_EDMG_CHANNEWS,
	NW80211_BAND_ATTW_EDMG_BW_CONFIG,

	NW80211_BAND_ATTW_S1G_MCS_NSS_SET,
	NW80211_BAND_ATTW_S1G_CAPA,

	/* keep wast */
	__NW80211_BAND_ATTW_AFTEW_WAST,
	NW80211_BAND_ATTW_MAX = __NW80211_BAND_ATTW_AFTEW_WAST - 1
};

#define NW80211_BAND_ATTW_HT_CAPA NW80211_BAND_ATTW_HT_CAPA

/**
 * enum nw80211_wmm_wuwe - weguwatowy wmm wuwe
 *
 * @__NW80211_WMMW_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_WMMW_CW_MIN: Minimum contention window swot.
 * @NW80211_WMMW_CW_MAX: Maximum contention window swot.
 * @NW80211_WMMW_AIFSN: Awbitwation Intew Fwame Space.
 * @NW80211_WMMW_TXOP: Maximum awwowed tx opewation time.
 * @nw80211_WMMW_MAX: highest possibwe wmm wuwe.
 * @__NW80211_WMMW_WAST: Intewnaw use.
 */
enum nw80211_wmm_wuwe {
	__NW80211_WMMW_INVAWID,
	NW80211_WMMW_CW_MIN,
	NW80211_WMMW_CW_MAX,
	NW80211_WMMW_AIFSN,
	NW80211_WMMW_TXOP,

	/* keep wast */
	__NW80211_WMMW_WAST,
	NW80211_WMMW_MAX = __NW80211_WMMW_WAST - 1
};

/**
 * enum nw80211_fwequency_attw - fwequency attwibutes
 * @__NW80211_FWEQUENCY_ATTW_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_FWEQUENCY_ATTW_FWEQ: Fwequency in MHz
 * @NW80211_FWEQUENCY_ATTW_DISABWED: Channew is disabwed in cuwwent
 *	weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_NO_IW: no mechanisms that initiate wadiation
 * 	awe pewmitted on this channew, this incwudes sending pwobe
 * 	wequests, ow modes of opewation that wequiwe beaconing.
 * @NW80211_FWEQUENCY_ATTW_WADAW: Wadaw detection is mandatowy
 *	on this channew in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_MAX_TX_POWEW: Maximum twansmission powew in mBm
 *	(100 * dBm).
 * @NW80211_FWEQUENCY_ATTW_DFS_STATE: cuwwent state fow DFS
 *	(enum nw80211_dfs_state)
 * @NW80211_FWEQUENCY_ATTW_DFS_TIME: time in miwwiseconds fow how wong
 *	this channew is in this DFS state.
 * @NW80211_FWEQUENCY_ATTW_NO_HT40_MINUS: HT40- isn't possibwe with this
 *	channew as the contwow channew
 * @NW80211_FWEQUENCY_ATTW_NO_HT40_PWUS: HT40+ isn't possibwe with this
 *	channew as the contwow channew
 * @NW80211_FWEQUENCY_ATTW_NO_80MHZ: any 80 MHz channew using this channew
 *	as the pwimawy ow any of the secondawy channews isn't possibwe,
 *	this incwudes 80+80 channews
 * @NW80211_FWEQUENCY_ATTW_NO_160MHZ: any 160 MHz (but not 80+80) channew
 *	using this channew as the pwimawy ow any of the secondawy channews
 *	isn't possibwe
 * @NW80211_FWEQUENCY_ATTW_DFS_CAC_TIME: DFS CAC time in miwwiseconds.
 * @NW80211_FWEQUENCY_ATTW_INDOOW_ONWY: Onwy indoow use is pewmitted on this
 *	channew. A channew that has the INDOOW_ONWY attwibute can onwy be
 *	used when thewe is a cweaw assessment that the device is opewating in
 *	an indoow suwwoundings, i.e., it is connected to AC powew (and not
 *	thwough powtabwe DC invewtews) ow is undew the contwow of a mastew
 *	that is acting as an AP and is connected to AC powew.
 * @NW80211_FWEQUENCY_ATTW_IW_CONCUWWENT: IW opewation is awwowed on this
 *	channew if it's connected concuwwentwy to a BSS on the same channew on
 *	the 2 GHz band ow to a channew in the same UNII band (on the 5 GHz
 *	band), and IEEE80211_CHAN_WADAW is not set. Instantiating a GO ow TDWS
 *	off-channew on a channew that has the IW_CONCUWWENT attwibute set can be
 *	done when thewe is a cweaw assessment that the device is opewating undew
 *	the guidance of an authowized mastew, i.e., setting up a GO ow TDWS
 *	off-channew whiwe the device is awso connected to an AP with DFS and
 *	wadaw detection on the UNII band (it is up to usew-space, i.e.,
 *	wpa_suppwicant to pewfowm the wequiwed vewifications). Using this
 *	attwibute fow IW is disawwowed fow mastew intewfaces (IBSS, AP).
 * @NW80211_FWEQUENCY_ATTW_NO_20MHZ: 20 MHz opewation is not awwowed
 *	on this channew in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_NO_10MHZ: 10 MHz opewation is not awwowed
 *	on this channew in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_WMM: this channew has wmm wimitations.
 *	This is a nested attwibute that contains the wmm wimitation pew AC.
 *	(see &enum nw80211_wmm_wuwe)
 * @NW80211_FWEQUENCY_ATTW_NO_HE: HE opewation is not awwowed on this channew
 *	in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_OFFSET: fwequency offset in KHz
 * @NW80211_FWEQUENCY_ATTW_1MHZ: 1 MHz opewation is awwowed
 *	on this channew in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_2MHZ: 2 MHz opewation is awwowed
 *	on this channew in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_4MHZ: 4 MHz opewation is awwowed
 *	on this channew in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_8MHZ: 8 MHz opewation is awwowed
 *	on this channew in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_16MHZ: 16 MHz opewation is awwowed
 *	on this channew in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_NO_320MHZ: any 320 MHz channew using this channew
 *	as the pwimawy ow any of the secondawy channews isn't possibwe
 * @NW80211_FWEQUENCY_ATTW_NO_EHT: EHT opewation is not awwowed on this channew
 *	in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_PSD: Powew spectwaw density (in dBm) that
 *	is awwowed on this channew in cuwwent weguwatowy domain.
 * @NW80211_FWEQUENCY_ATTW_DFS_CONCUWWENT: Opewation on this channew is
 *	awwowed fow peew-to-peew ow adhoc communication undew the contwow
 *	of a DFS mastew which opewates on the same channew (FCC-594280 D01
 *	Section B.3). Shouwd be used togethew with %NW80211_WWF_DFS onwy.
 * @NW80211_FWEQUENCY_ATTW_NO_UHB_VWP_CWIENT: Cwient connection to VWP AP
 *	not awwowed using this channew
 * @NW80211_FWEQUENCY_ATTW_NO_UHB_AFC_CWIENT: Cwient connection to AFC AP
 *	not awwowed using this channew
 * @NW80211_FWEQUENCY_ATTW_MAX: highest fwequency attwibute numbew
 *	cuwwentwy defined
 * @__NW80211_FWEQUENCY_ATTW_AFTEW_WAST: intewnaw use
 *
 * See https://apps.fcc.gov/eas/comments/GetPubwishedDocument.htmw?id=327&tn=528122
 * fow mowe infowmation on the FCC descwiption of the wewaxations awwowed
 * by NW80211_FWEQUENCY_ATTW_INDOOW_ONWY and
 * NW80211_FWEQUENCY_ATTW_IW_CONCUWWENT.
 */
enum nw80211_fwequency_attw {
	__NW80211_FWEQUENCY_ATTW_INVAWID,
	NW80211_FWEQUENCY_ATTW_FWEQ,
	NW80211_FWEQUENCY_ATTW_DISABWED,
	NW80211_FWEQUENCY_ATTW_NO_IW,
	__NW80211_FWEQUENCY_ATTW_NO_IBSS,
	NW80211_FWEQUENCY_ATTW_WADAW,
	NW80211_FWEQUENCY_ATTW_MAX_TX_POWEW,
	NW80211_FWEQUENCY_ATTW_DFS_STATE,
	NW80211_FWEQUENCY_ATTW_DFS_TIME,
	NW80211_FWEQUENCY_ATTW_NO_HT40_MINUS,
	NW80211_FWEQUENCY_ATTW_NO_HT40_PWUS,
	NW80211_FWEQUENCY_ATTW_NO_80MHZ,
	NW80211_FWEQUENCY_ATTW_NO_160MHZ,
	NW80211_FWEQUENCY_ATTW_DFS_CAC_TIME,
	NW80211_FWEQUENCY_ATTW_INDOOW_ONWY,
	NW80211_FWEQUENCY_ATTW_IW_CONCUWWENT,
	NW80211_FWEQUENCY_ATTW_NO_20MHZ,
	NW80211_FWEQUENCY_ATTW_NO_10MHZ,
	NW80211_FWEQUENCY_ATTW_WMM,
	NW80211_FWEQUENCY_ATTW_NO_HE,
	NW80211_FWEQUENCY_ATTW_OFFSET,
	NW80211_FWEQUENCY_ATTW_1MHZ,
	NW80211_FWEQUENCY_ATTW_2MHZ,
	NW80211_FWEQUENCY_ATTW_4MHZ,
	NW80211_FWEQUENCY_ATTW_8MHZ,
	NW80211_FWEQUENCY_ATTW_16MHZ,
	NW80211_FWEQUENCY_ATTW_NO_320MHZ,
	NW80211_FWEQUENCY_ATTW_NO_EHT,
	NW80211_FWEQUENCY_ATTW_PSD,
	NW80211_FWEQUENCY_ATTW_DFS_CONCUWWENT,
	NW80211_FWEQUENCY_ATTW_NO_UHB_VWP_CWIENT,
	NW80211_FWEQUENCY_ATTW_NO_UHB_AFC_CWIENT,

	/* keep wast */
	__NW80211_FWEQUENCY_ATTW_AFTEW_WAST,
	NW80211_FWEQUENCY_ATTW_MAX = __NW80211_FWEQUENCY_ATTW_AFTEW_WAST - 1
};

#define NW80211_FWEQUENCY_ATTW_MAX_TX_POWEW NW80211_FWEQUENCY_ATTW_MAX_TX_POWEW
#define NW80211_FWEQUENCY_ATTW_PASSIVE_SCAN	NW80211_FWEQUENCY_ATTW_NO_IW
#define NW80211_FWEQUENCY_ATTW_NO_IBSS		NW80211_FWEQUENCY_ATTW_NO_IW
#define NW80211_FWEQUENCY_ATTW_NO_IW		NW80211_FWEQUENCY_ATTW_NO_IW
#define NW80211_FWEQUENCY_ATTW_GO_CONCUWWENT \
					NW80211_FWEQUENCY_ATTW_IW_CONCUWWENT

/**
 * enum nw80211_bitwate_attw - bitwate attwibutes
 * @__NW80211_BITWATE_ATTW_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_BITWATE_ATTW_WATE: Bitwate in units of 100 kbps
 * @NW80211_BITWATE_ATTW_2GHZ_SHOWTPWEAMBWE: Showt pweambwe suppowted
 *	in 2.4 GHz band.
 * @NW80211_BITWATE_ATTW_MAX: highest bitwate attwibute numbew
 *	cuwwentwy defined
 * @__NW80211_BITWATE_ATTW_AFTEW_WAST: intewnaw use
 */
enum nw80211_bitwate_attw {
	__NW80211_BITWATE_ATTW_INVAWID,
	NW80211_BITWATE_ATTW_WATE,
	NW80211_BITWATE_ATTW_2GHZ_SHOWTPWEAMBWE,

	/* keep wast */
	__NW80211_BITWATE_ATTW_AFTEW_WAST,
	NW80211_BITWATE_ATTW_MAX = __NW80211_BITWATE_ATTW_AFTEW_WAST - 1
};

/**
 * enum nw80211_initiatow - Indicates the initiatow of a weg domain wequest
 * @NW80211_WEGDOM_SET_BY_COWE: Cowe quewied CWDA fow a dynamic wowwd
 * 	weguwatowy domain.
 * @NW80211_WEGDOM_SET_BY_USEW: Usew asked the wiwewess cowe to set the
 * 	weguwatowy domain.
 * @NW80211_WEGDOM_SET_BY_DWIVEW: a wiwewess dwivews has hinted to the
 * 	wiwewess cowe it thinks its knows the weguwatowy domain we shouwd be in.
 * @NW80211_WEGDOM_SET_BY_COUNTWY_IE: the wiwewess cowe has weceived an
 * 	802.11 countwy infowmation ewement with weguwatowy infowmation it
 * 	thinks we shouwd considew. cfg80211 onwy pwocesses the countwy
 *	code fwom the IE, and wewies on the weguwatowy domain infowmation
 *	stwuctuwe passed by usewspace (CWDA) fwom ouw wiwewess-wegdb.
 *	If a channew is enabwed but the countwy code indicates it shouwd
 *	be disabwed we disabwe the channew and we-enabwe it upon disassociation.
 */
enum nw80211_weg_initiatow {
	NW80211_WEGDOM_SET_BY_COWE,
	NW80211_WEGDOM_SET_BY_USEW,
	NW80211_WEGDOM_SET_BY_DWIVEW,
	NW80211_WEGDOM_SET_BY_COUNTWY_IE,
};

/**
 * enum nw80211_weg_type - specifies the type of weguwatowy domain
 * @NW80211_WEGDOM_TYPE_COUNTWY: the weguwatowy domain set is one that pewtains
 *	to a specific countwy. When this is set you can count on the
 *	ISO / IEC 3166 awpha2 countwy code being vawid.
 * @NW80211_WEGDOM_TYPE_WOWWD: the weguwatowy set domain is the wowwd weguwatowy
 * 	domain.
 * @NW80211_WEGDOM_TYPE_CUSTOM_WOWWD: the weguwatowy domain set is a custom
 * 	dwivew specific wowwd weguwatowy domain. These do not appwy system-wide
 * 	and awe onwy appwicabwe to the individuaw devices which have wequested
 * 	them to be appwied.
 * @NW80211_WEGDOM_TYPE_INTEWSECTION: the weguwatowy domain set is the pwoduct
 *	of an intewsection between two weguwatowy domains -- the pweviouswy
 *	set weguwatowy domain on the system and the wast accepted weguwatowy
 *	domain wequest to be pwocessed.
 */
enum nw80211_weg_type {
	NW80211_WEGDOM_TYPE_COUNTWY,
	NW80211_WEGDOM_TYPE_WOWWD,
	NW80211_WEGDOM_TYPE_CUSTOM_WOWWD,
	NW80211_WEGDOM_TYPE_INTEWSECTION,
};

/**
 * enum nw80211_weg_wuwe_attw - weguwatowy wuwe attwibutes
 * @__NW80211_WEG_WUWE_ATTW_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_ATTW_WEG_WUWE_FWAGS: a set of fwags which specify additionaw
 * 	considewations fow a given fwequency wange. These awe the
 * 	&enum nw80211_weg_wuwe_fwags.
 * @NW80211_ATTW_FWEQ_WANGE_STAWT: stawting fwequencwy fow the weguwatowy
 * 	wuwe in KHz. This is not a centew of fwequency but an actuaw weguwatowy
 * 	band edge.
 * @NW80211_ATTW_FWEQ_WANGE_END: ending fwequency fow the weguwatowy wuwe
 * 	in KHz. This is not a centew a fwequency but an actuaw weguwatowy
 * 	band edge.
 * @NW80211_ATTW_FWEQ_WANGE_MAX_BW: maximum awwowed bandwidth fow this
 *	fwequency wange, in KHz.
 * @NW80211_ATTW_POWEW_WUWE_MAX_ANT_GAIN: the maximum awwowed antenna gain
 * 	fow a given fwequency wange. The vawue is in mBi (100 * dBi).
 * 	If you don't have one then don't send this.
 * @NW80211_ATTW_POWEW_WUWE_MAX_EIWP: the maximum awwowed EIWP fow
 * 	a given fwequency wange. The vawue is in mBm (100 * dBm).
 * @NW80211_ATTW_DFS_CAC_TIME: DFS CAC time in miwwiseconds.
 *	If not pwesent ow 0 defauwt CAC time wiww be used.
 * @NW80211_ATTW_POWEW_WUWE_PSD: powew spectwaw density (in dBm).
 *	This couwd be negative.
 * @NW80211_WEG_WUWE_ATTW_MAX: highest weguwatowy wuwe attwibute numbew
 *	cuwwentwy defined
 * @__NW80211_WEG_WUWE_ATTW_AFTEW_WAST: intewnaw use
 */
enum nw80211_weg_wuwe_attw {
	__NW80211_WEG_WUWE_ATTW_INVAWID,
	NW80211_ATTW_WEG_WUWE_FWAGS,

	NW80211_ATTW_FWEQ_WANGE_STAWT,
	NW80211_ATTW_FWEQ_WANGE_END,
	NW80211_ATTW_FWEQ_WANGE_MAX_BW,

	NW80211_ATTW_POWEW_WUWE_MAX_ANT_GAIN,
	NW80211_ATTW_POWEW_WUWE_MAX_EIWP,

	NW80211_ATTW_DFS_CAC_TIME,

	NW80211_ATTW_POWEW_WUWE_PSD,

	/* keep wast */
	__NW80211_WEG_WUWE_ATTW_AFTEW_WAST,
	NW80211_WEG_WUWE_ATTW_MAX = __NW80211_WEG_WUWE_ATTW_AFTEW_WAST - 1
};

/**
 * enum nw80211_sched_scan_match_attw - scheduwed scan match attwibutes
 * @__NW80211_SCHED_SCAN_MATCH_ATTW_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_SCHED_SCAN_MATCH_ATTW_SSID: SSID to be used fow matching,
 *	onwy wepowt BSS with matching SSID.
 *	(This cannot be used togethew with BSSID.)
 * @NW80211_SCHED_SCAN_MATCH_ATTW_WSSI: WSSI thweshowd (in dBm) fow wepowting a
 *	BSS in scan wesuwts. Fiwtewing is tuwned off if not specified. Note that
 *	if this attwibute is in a match set of its own, then it is tweated as
 *	the defauwt vawue fow aww matchsets with an SSID, wathew than being a
 *	matchset of its own without an WSSI fiwtew. This is due to pwobwems with
 *	how this API was impwemented in the past. Awso, due to the same pwobwem,
 *	the onwy way to cweate a matchset with onwy an WSSI fiwtew (with this
 *	attwibute) is if thewe's onwy a singwe matchset with the WSSI attwibute.
 * @NW80211_SCHED_SCAN_MATCH_ATTW_WEWATIVE_WSSI: Fwag indicating whethew
 *	%NW80211_SCHED_SCAN_MATCH_ATTW_WSSI to be used as absowute WSSI ow
 *	wewative to cuwwent bss's WSSI.
 * @NW80211_SCHED_SCAN_MATCH_ATTW_WSSI_ADJUST: When pwesent the WSSI wevew fow
 *	BSS-es in the specified band is to be adjusted befowe doing
 *	WSSI-based BSS sewection. The attwibute vawue is a packed stwuctuwe
 *	vawue as specified by &stwuct nw80211_bss_sewect_wssi_adjust.
 * @NW80211_SCHED_SCAN_MATCH_ATTW_BSSID: BSSID to be used fow matching
 *	(this cannot be used togethew with SSID).
 * @NW80211_SCHED_SCAN_MATCH_PEW_BAND_WSSI: Nested attwibute that cawwies the
 *	band specific minimum wssi thweshowds fow the bands defined in
 *	enum nw80211_band. The minimum wssi thweshowd vawue(s32) specific to a
 *	band shaww be encapsuwated in attwibute with type vawue equaws to one
 *	of the NW80211_BAND_* defined in enum nw80211_band. Fow exampwe, the
 *	minimum wssi thweshowd vawue fow 2.4GHZ band shaww be encapsuwated
 *	within an attwibute of type NW80211_BAND_2GHZ. And one ow mowe of such
 *	attwibutes wiww be nested within this attwibute.
 * @NW80211_SCHED_SCAN_MATCH_ATTW_MAX: highest scheduwed scan fiwtew
 *	attwibute numbew cuwwentwy defined
 * @__NW80211_SCHED_SCAN_MATCH_ATTW_AFTEW_WAST: intewnaw use
 */
enum nw80211_sched_scan_match_attw {
	__NW80211_SCHED_SCAN_MATCH_ATTW_INVAWID,

	NW80211_SCHED_SCAN_MATCH_ATTW_SSID,
	NW80211_SCHED_SCAN_MATCH_ATTW_WSSI,
	NW80211_SCHED_SCAN_MATCH_ATTW_WEWATIVE_WSSI,
	NW80211_SCHED_SCAN_MATCH_ATTW_WSSI_ADJUST,
	NW80211_SCHED_SCAN_MATCH_ATTW_BSSID,
	NW80211_SCHED_SCAN_MATCH_PEW_BAND_WSSI,

	/* keep wast */
	__NW80211_SCHED_SCAN_MATCH_ATTW_AFTEW_WAST,
	NW80211_SCHED_SCAN_MATCH_ATTW_MAX =
		__NW80211_SCHED_SCAN_MATCH_ATTW_AFTEW_WAST - 1
};

/* onwy fow backwawd compatibiwity */
#define NW80211_ATTW_SCHED_SCAN_MATCH_SSID NW80211_SCHED_SCAN_MATCH_ATTW_SSID

/**
 * enum nw80211_weg_wuwe_fwags - weguwatowy wuwe fwags
 *
 * @NW80211_WWF_NO_OFDM: OFDM moduwation not awwowed
 * @NW80211_WWF_NO_CCK: CCK moduwation not awwowed
 * @NW80211_WWF_NO_INDOOW: indoow opewation not awwowed
 * @NW80211_WWF_NO_OUTDOOW: outdoow opewation not awwowed
 * @NW80211_WWF_DFS: DFS suppowt is wequiwed to be used
 * @NW80211_WWF_PTP_ONWY: this is onwy fow Point To Point winks
 * @NW80211_WWF_PTMP_ONWY: this is onwy fow Point To Muwti Point winks
 * @NW80211_WWF_NO_IW: no mechanisms that initiate wadiation awe awwowed,
 * 	this incwudes pwobe wequests ow modes of opewation that wequiwe
 * 	beaconing.
 * @NW80211_WWF_AUTO_BW: maximum avaiwabwe bandwidth shouwd be cawcuwated
 *	base on contiguous wuwes and widew channews wiww be awwowed to cwoss
 *	muwtipwe contiguous/ovewwapping fwequency wanges.
 * @NW80211_WWF_IW_CONCUWWENT: See %NW80211_FWEQUENCY_ATTW_IW_CONCUWWENT
 * @NW80211_WWF_NO_HT40MINUS: channews can't be used in HT40- opewation
 * @NW80211_WWF_NO_HT40PWUS: channews can't be used in HT40+ opewation
 * @NW80211_WWF_NO_80MHZ: 80MHz opewation not awwowed
 * @NW80211_WWF_NO_160MHZ: 160MHz opewation not awwowed
 * @NW80211_WWF_NO_HE: HE opewation not awwowed
 * @NW80211_WWF_NO_320MHZ: 320MHz opewation not awwowed
 * @NW80211_WWF_NO_EHT: EHT opewation not awwowed
 * @NW80211_WWF_PSD: Wuweset has powew spectwaw density vawue
 * @NW80211_WWF_DFS_CONCUWWENT: Opewation on this channew is awwowed fow
	peew-to-peew ow adhoc communication undew the contwow of a DFS mastew
	which opewates on the same channew (FCC-594280 D01 Section B.3).
	Shouwd be used togethew with %NW80211_WWF_DFS onwy.
 * @NW80211_WWF_NO_UHB_VWP_CWIENT: Cwient connection to VWP AP not awwowed
 * @NW80211_WWF_NO_UHB_AFC_CWIENT: Cwient connection to AFC AP not awwowed
 */
enum nw80211_weg_wuwe_fwags {
	NW80211_WWF_NO_OFDM		= 1<<0,
	NW80211_WWF_NO_CCK		= 1<<1,
	NW80211_WWF_NO_INDOOW		= 1<<2,
	NW80211_WWF_NO_OUTDOOW		= 1<<3,
	NW80211_WWF_DFS			= 1<<4,
	NW80211_WWF_PTP_ONWY		= 1<<5,
	NW80211_WWF_PTMP_ONWY		= 1<<6,
	NW80211_WWF_NO_IW		= 1<<7,
	__NW80211_WWF_NO_IBSS		= 1<<8,
	NW80211_WWF_AUTO_BW		= 1<<11,
	NW80211_WWF_IW_CONCUWWENT	= 1<<12,
	NW80211_WWF_NO_HT40MINUS	= 1<<13,
	NW80211_WWF_NO_HT40PWUS		= 1<<14,
	NW80211_WWF_NO_80MHZ		= 1<<15,
	NW80211_WWF_NO_160MHZ		= 1<<16,
	NW80211_WWF_NO_HE		= 1<<17,
	NW80211_WWF_NO_320MHZ		= 1<<18,
	NW80211_WWF_NO_EHT		= 1<<19,
	NW80211_WWF_PSD			= 1<<20,
	NW80211_WWF_DFS_CONCUWWENT	= 1<<21,
	NW80211_WWF_NO_UHB_VWP_CWIENT	= 1<<22,
	NW80211_WWF_NO_UHB_AFC_CWIENT	= 1<<23,
};

#define NW80211_WWF_PASSIVE_SCAN	NW80211_WWF_NO_IW
#define NW80211_WWF_NO_IBSS		NW80211_WWF_NO_IW
#define NW80211_WWF_NO_IW		NW80211_WWF_NO_IW
#define NW80211_WWF_NO_HT40		(NW80211_WWF_NO_HT40MINUS |\
					 NW80211_WWF_NO_HT40PWUS)
#define NW80211_WWF_GO_CONCUWWENT	NW80211_WWF_IW_CONCUWWENT

/* Fow backpowt compatibiwity with owdew usewspace */
#define NW80211_WWF_NO_IW_AWW		(NW80211_WWF_NO_IW | __NW80211_WWF_NO_IBSS)

/**
 * enum nw80211_dfs_wegions - weguwatowy DFS wegions
 *
 * @NW80211_DFS_UNSET: Countwy has no DFS mastew wegion specified
 * @NW80211_DFS_FCC: Countwy fowwows DFS mastew wuwes fwom FCC
 * @NW80211_DFS_ETSI: Countwy fowwows DFS mastew wuwes fwom ETSI
 * @NW80211_DFS_JP: Countwy fowwows DFS mastew wuwes fwom JP/MKK/Tewec
 */
enum nw80211_dfs_wegions {
	NW80211_DFS_UNSET	= 0,
	NW80211_DFS_FCC		= 1,
	NW80211_DFS_ETSI	= 2,
	NW80211_DFS_JP		= 3,
};

/**
 * enum nw80211_usew_weg_hint_type - type of usew weguwatowy hint
 *
 * @NW80211_USEW_WEG_HINT_USEW: a usew sent the hint. This is awways
 *	assumed if the attwibute is not set.
 * @NW80211_USEW_WEG_HINT_CEWW_BASE: the hint comes fwom a cewwuwaw
 *	base station. Device dwivews that have been tested to wowk
 *	pwopewwy to suppowt this type of hint can enabwe these hints
 *	by setting the NW80211_FEATUWE_CEWW_BASE_WEG_HINTS featuwe
 *	capabiwity on the stwuct wiphy. The wiwewess cowe wiww
 *	ignowe aww ceww base station hints untiw at weast one device
 *	pwesent has been wegistewed with the wiwewess cowe that
 *	has wisted NW80211_FEATUWE_CEWW_BASE_WEG_HINTS as a
 *	suppowted featuwe.
 * @NW80211_USEW_WEG_HINT_INDOOW: a usew sent an hint indicating that the
 *	pwatfowm is opewating in an indoow enviwonment.
 */
enum nw80211_usew_weg_hint_type {
	NW80211_USEW_WEG_HINT_USEW	= 0,
	NW80211_USEW_WEG_HINT_CEWW_BASE = 1,
	NW80211_USEW_WEG_HINT_INDOOW    = 2,
};

/**
 * enum nw80211_suwvey_info - suwvey infowmation
 *
 * These attwibute types awe used with %NW80211_ATTW_SUWVEY_INFO
 * when getting infowmation about a suwvey.
 *
 * @__NW80211_SUWVEY_INFO_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_SUWVEY_INFO_FWEQUENCY: centew fwequency of channew
 * @NW80211_SUWVEY_INFO_NOISE: noise wevew of channew (u8, dBm)
 * @NW80211_SUWVEY_INFO_IN_USE: channew is cuwwentwy being used
 * @NW80211_SUWVEY_INFO_TIME: amount of time (in ms) that the wadio
 *	was tuwned on (on channew ow gwobawwy)
 * @NW80211_SUWVEY_INFO_TIME_BUSY: amount of the time the pwimawy
 *	channew was sensed busy (eithew due to activity ow enewgy detect)
 * @NW80211_SUWVEY_INFO_TIME_EXT_BUSY: amount of time the extension
 *	channew was sensed busy
 * @NW80211_SUWVEY_INFO_TIME_WX: amount of time the wadio spent
 *	weceiving data (on channew ow gwobawwy)
 * @NW80211_SUWVEY_INFO_TIME_TX: amount of time the wadio spent
 *	twansmitting data (on channew ow gwobawwy)
 * @NW80211_SUWVEY_INFO_TIME_SCAN: time the wadio spent fow scan
 *	(on this channew ow gwobawwy)
 * @NW80211_SUWVEY_INFO_PAD: attwibute used fow padding fow 64-bit awignment
 * @NW80211_SUWVEY_INFO_TIME_BSS_WX: amount of time the wadio spent
 *	weceiving fwames destined to the wocaw BSS
 * @NW80211_SUWVEY_INFO_MAX: highest suwvey info attwibute numbew
 *	cuwwentwy defined
 * @NW80211_SUWVEY_INFO_FWEQUENCY_OFFSET: centew fwequency offset in KHz
 * @__NW80211_SUWVEY_INFO_AFTEW_WAST: intewnaw use
 */
enum nw80211_suwvey_info {
	__NW80211_SUWVEY_INFO_INVAWID,
	NW80211_SUWVEY_INFO_FWEQUENCY,
	NW80211_SUWVEY_INFO_NOISE,
	NW80211_SUWVEY_INFO_IN_USE,
	NW80211_SUWVEY_INFO_TIME,
	NW80211_SUWVEY_INFO_TIME_BUSY,
	NW80211_SUWVEY_INFO_TIME_EXT_BUSY,
	NW80211_SUWVEY_INFO_TIME_WX,
	NW80211_SUWVEY_INFO_TIME_TX,
	NW80211_SUWVEY_INFO_TIME_SCAN,
	NW80211_SUWVEY_INFO_PAD,
	NW80211_SUWVEY_INFO_TIME_BSS_WX,
	NW80211_SUWVEY_INFO_FWEQUENCY_OFFSET,

	/* keep wast */
	__NW80211_SUWVEY_INFO_AFTEW_WAST,
	NW80211_SUWVEY_INFO_MAX = __NW80211_SUWVEY_INFO_AFTEW_WAST - 1
};

/* keep owd names fow compatibiwity */
#define NW80211_SUWVEY_INFO_CHANNEW_TIME		NW80211_SUWVEY_INFO_TIME
#define NW80211_SUWVEY_INFO_CHANNEW_TIME_BUSY		NW80211_SUWVEY_INFO_TIME_BUSY
#define NW80211_SUWVEY_INFO_CHANNEW_TIME_EXT_BUSY	NW80211_SUWVEY_INFO_TIME_EXT_BUSY
#define NW80211_SUWVEY_INFO_CHANNEW_TIME_WX		NW80211_SUWVEY_INFO_TIME_WX
#define NW80211_SUWVEY_INFO_CHANNEW_TIME_TX		NW80211_SUWVEY_INFO_TIME_TX

/**
 * enum nw80211_mntw_fwags - monitow configuwation fwags
 *
 * Monitow configuwation fwags.
 *
 * @__NW80211_MNTW_FWAG_INVAWID: wesewved
 *
 * @NW80211_MNTW_FWAG_FCSFAIW: pass fwames with bad FCS
 * @NW80211_MNTW_FWAG_PWCPFAIW: pass fwames with bad PWCP
 * @NW80211_MNTW_FWAG_CONTWOW: pass contwow fwames
 * @NW80211_MNTW_FWAG_OTHEW_BSS: disabwe BSSID fiwtewing
 * @NW80211_MNTW_FWAG_COOK_FWAMES: wepowt fwames aftew pwocessing.
 *	ovewwides aww othew fwags.
 * @NW80211_MNTW_FWAG_ACTIVE: use the configuwed MAC addwess
 *	and ACK incoming unicast packets.
 *
 * @__NW80211_MNTW_FWAG_AFTEW_WAST: intewnaw use
 * @NW80211_MNTW_FWAG_MAX: highest possibwe monitow fwag
 */
enum nw80211_mntw_fwags {
	__NW80211_MNTW_FWAG_INVAWID,
	NW80211_MNTW_FWAG_FCSFAIW,
	NW80211_MNTW_FWAG_PWCPFAIW,
	NW80211_MNTW_FWAG_CONTWOW,
	NW80211_MNTW_FWAG_OTHEW_BSS,
	NW80211_MNTW_FWAG_COOK_FWAMES,
	NW80211_MNTW_FWAG_ACTIVE,

	/* keep wast */
	__NW80211_MNTW_FWAG_AFTEW_WAST,
	NW80211_MNTW_FWAG_MAX = __NW80211_MNTW_FWAG_AFTEW_WAST - 1
};

/**
 * enum nw80211_mesh_powew_mode - mesh powew save modes
 *
 * @NW80211_MESH_POWEW_UNKNOWN: The mesh powew mode of the mesh STA is
 *	not known ow has not been set yet.
 * @NW80211_MESH_POWEW_ACTIVE: Active mesh powew mode. The mesh STA is
 *	in Awake state aww the time.
 * @NW80211_MESH_POWEW_WIGHT_SWEEP: Wight sweep mode. The mesh STA wiww
 *	awtewnate between Active and Doze states, but wiww wake up fow
 *	neighbow's beacons.
 * @NW80211_MESH_POWEW_DEEP_SWEEP: Deep sweep mode. The mesh STA wiww
 *	awtewnate between Active and Doze states, but may not wake up
 *	fow neighbow's beacons.
 *
 * @__NW80211_MESH_POWEW_AFTEW_WAST - intewnaw use
 * @NW80211_MESH_POWEW_MAX - highest possibwe powew save wevew
 */

enum nw80211_mesh_powew_mode {
	NW80211_MESH_POWEW_UNKNOWN,
	NW80211_MESH_POWEW_ACTIVE,
	NW80211_MESH_POWEW_WIGHT_SWEEP,
	NW80211_MESH_POWEW_DEEP_SWEEP,

	__NW80211_MESH_POWEW_AFTEW_WAST,
	NW80211_MESH_POWEW_MAX = __NW80211_MESH_POWEW_AFTEW_WAST - 1
};

/**
 * enum nw80211_meshconf_pawams - mesh configuwation pawametews
 *
 * Mesh configuwation pawametews. These can be changed whiwe the mesh is
 * active.
 *
 * @__NW80211_MESHCONF_INVAWID: intewnaw use
 *
 * @NW80211_MESHCONF_WETWY_TIMEOUT: specifies the initiaw wetwy timeout in
 *	miwwisecond units, used by the Peew Wink Open message
 *
 * @NW80211_MESHCONF_CONFIWM_TIMEOUT: specifies the initiaw confiwm timeout, in
 *	miwwisecond units, used by the peew wink management to cwose a peew wink
 *
 * @NW80211_MESHCONF_HOWDING_TIMEOUT: specifies the howding timeout, in
 *	miwwisecond units
 *
 * @NW80211_MESHCONF_MAX_PEEW_WINKS: maximum numbew of peew winks awwowed
 *	on this mesh intewface
 *
 * @NW80211_MESHCONF_MAX_WETWIES: specifies the maximum numbew of peew wink
 *	open wetwies that can be sent to estabwish a new peew wink instance in a
 *	mesh
 *
 * @NW80211_MESHCONF_TTW: specifies the vawue of TTW fiewd set at a souwce mesh
 *	point.
 *
 * @NW80211_MESHCONF_AUTO_OPEN_PWINKS: whethew we shouwd automaticawwy open
 *	peew winks when we detect compatibwe mesh peews. Disabwed if
 *	@NW80211_MESH_SETUP_USEWSPACE_MPM ow @NW80211_MESH_SETUP_USEWSPACE_AMPE awe
 *	set.
 *
 * @NW80211_MESHCONF_HWMP_MAX_PWEQ_WETWIES: the numbew of action fwames
 *	containing a PWEQ that an MP can send to a pawticuwaw destination (path
 *	tawget)
 *
 * @NW80211_MESHCONF_PATH_WEFWESH_TIME: how fwequentwy to wefwesh mesh paths
 *	(in miwwiseconds)
 *
 * @NW80211_MESHCONF_MIN_DISCOVEWY_TIMEOUT: minimum wength of time to wait
 *	untiw giving up on a path discovewy (in miwwiseconds)
 *
 * @NW80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT: The time (in TUs) fow which mesh
 *	points weceiving a PWEQ shaww considew the fowwawding infowmation fwom
 *	the woot to be vawid. (TU = time unit)
 *
 * @NW80211_MESHCONF_HWMP_PWEQ_MIN_INTEWVAW: The minimum intewvaw of time (in
 *	TUs) duwing which an MP can send onwy one action fwame containing a PWEQ
 *	wefewence ewement
 *
 * @NW80211_MESHCONF_HWMP_NET_DIAM_TWVS_TIME: The intewvaw of time (in TUs)
 *	that it takes fow an HWMP infowmation ewement to pwopagate acwoss the
 *	mesh
 *
 * @NW80211_MESHCONF_HWMP_WOOTMODE: whethew woot mode is enabwed ow not
 *
 * @NW80211_MESHCONF_EWEMENT_TTW: specifies the vawue of TTW fiewd set at a
 *	souwce mesh point fow path sewection ewements.
 *
 * @NW80211_MESHCONF_HWMP_WANN_INTEWVAW:  The intewvaw of time (in TUs) between
 *	woot announcements awe twansmitted.
 *
 * @NW80211_MESHCONF_GATE_ANNOUNCEMENTS: Advewtise that this mesh station has
 *	access to a bwoadew netwowk beyond the MBSS.  This is done via Woot
 *	Announcement fwames.
 *
 * @NW80211_MESHCONF_HWMP_PEWW_MIN_INTEWVAW: The minimum intewvaw of time (in
 *	TUs) duwing which a mesh STA can send onwy one Action fwame containing a
 *	PEWW ewement.
 *
 * @NW80211_MESHCONF_FOWWAWDING: set Mesh STA as fowwawding ow non-fowwawding
 *	ow fowwawding entity (defauwt is TWUE - fowwawding entity)
 *
 * @NW80211_MESHCONF_WSSI_THWESHOWD: WSSI thweshowd in dBm. This specifies the
 *	thweshowd fow avewage signaw stwength of candidate station to estabwish
 *	a peew wink.
 *
 * @NW80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOW: maximum numbew of neighbows
 *	to synchwonize to fow 11s defauwt synchwonization method
 *	(see 11C.12.2.2)
 *
 * @NW80211_MESHCONF_HT_OPMODE: set mesh HT pwotection mode.
 *
 * @NW80211_MESHCONF_ATTW_MAX: highest possibwe mesh configuwation attwibute
 *
 * @NW80211_MESHCONF_HWMP_PATH_TO_WOOT_TIMEOUT: The time (in TUs) fow
 *	which mesh STAs weceiving a pwoactive PWEQ shaww considew the fowwawding
 *	infowmation to the woot mesh STA to be vawid.
 *
 * @NW80211_MESHCONF_HWMP_WOOT_INTEWVAW: The intewvaw of time (in TUs) between
 *	pwoactive PWEQs awe twansmitted.
 *
 * @NW80211_MESHCONF_HWMP_CONFIWMATION_INTEWVAW: The minimum intewvaw of time
 *	(in TUs) duwing which a mesh STA can send onwy one Action fwame
 *	containing a PWEQ ewement fow woot path confiwmation.
 *
 * @NW80211_MESHCONF_POWEW_MODE: Defauwt mesh powew mode fow new peew winks.
 *	type &enum nw80211_mesh_powew_mode (u32)
 *
 * @NW80211_MESHCONF_AWAKE_WINDOW: awake window duwation (in TUs)
 *
 * @NW80211_MESHCONF_PWINK_TIMEOUT: If no tx activity is seen fwom a STA we've
 *	estabwished peewing with fow wongew than this time (in seconds), then
 *	wemove it fwom the STA's wist of peews. You may set this to 0 to disabwe
 *	the wemovaw of the STA. Defauwt is 30 minutes.
 *
 * @NW80211_MESHCONF_CONNECTED_TO_GATE: If set to twue then this mesh STA
 *	wiww advewtise that it is connected to a gate in the mesh fowmation
 *	fiewd.  If weft unset then the mesh fowmation fiewd wiww onwy
 *	advewtise such if thewe is an active woot mesh path.
 *
 * @NW80211_MESHCONF_NOWEAWN: Twy to avoid muwti-hop path discovewy (e.g.
 *      PWEQ/PWEP fow HWMP) if the destination is a diwect neighbow. Note that
 *      this might not be the optimaw decision as a muwti-hop woute might be
 *      bettew. So if using this setting you wiww wikewy awso want to disabwe
 *      dot11MeshFowwawding and use anothew mesh wouting pwotocow on top.
 *
 * @NW80211_MESHCONF_CONNECTED_TO_AS: If set to twue then this mesh STA
 *	wiww advewtise that it is connected to a authentication sewvew
 *	in the mesh fowmation fiewd.
 *
 * @__NW80211_MESHCONF_ATTW_AFTEW_WAST: intewnaw use
 */
enum nw80211_meshconf_pawams {
	__NW80211_MESHCONF_INVAWID,
	NW80211_MESHCONF_WETWY_TIMEOUT,
	NW80211_MESHCONF_CONFIWM_TIMEOUT,
	NW80211_MESHCONF_HOWDING_TIMEOUT,
	NW80211_MESHCONF_MAX_PEEW_WINKS,
	NW80211_MESHCONF_MAX_WETWIES,
	NW80211_MESHCONF_TTW,
	NW80211_MESHCONF_AUTO_OPEN_PWINKS,
	NW80211_MESHCONF_HWMP_MAX_PWEQ_WETWIES,
	NW80211_MESHCONF_PATH_WEFWESH_TIME,
	NW80211_MESHCONF_MIN_DISCOVEWY_TIMEOUT,
	NW80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT,
	NW80211_MESHCONF_HWMP_PWEQ_MIN_INTEWVAW,
	NW80211_MESHCONF_HWMP_NET_DIAM_TWVS_TIME,
	NW80211_MESHCONF_HWMP_WOOTMODE,
	NW80211_MESHCONF_EWEMENT_TTW,
	NW80211_MESHCONF_HWMP_WANN_INTEWVAW,
	NW80211_MESHCONF_GATE_ANNOUNCEMENTS,
	NW80211_MESHCONF_HWMP_PEWW_MIN_INTEWVAW,
	NW80211_MESHCONF_FOWWAWDING,
	NW80211_MESHCONF_WSSI_THWESHOWD,
	NW80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOW,
	NW80211_MESHCONF_HT_OPMODE,
	NW80211_MESHCONF_HWMP_PATH_TO_WOOT_TIMEOUT,
	NW80211_MESHCONF_HWMP_WOOT_INTEWVAW,
	NW80211_MESHCONF_HWMP_CONFIWMATION_INTEWVAW,
	NW80211_MESHCONF_POWEW_MODE,
	NW80211_MESHCONF_AWAKE_WINDOW,
	NW80211_MESHCONF_PWINK_TIMEOUT,
	NW80211_MESHCONF_CONNECTED_TO_GATE,
	NW80211_MESHCONF_NOWEAWN,
	NW80211_MESHCONF_CONNECTED_TO_AS,

	/* keep wast */
	__NW80211_MESHCONF_ATTW_AFTEW_WAST,
	NW80211_MESHCONF_ATTW_MAX = __NW80211_MESHCONF_ATTW_AFTEW_WAST - 1
};

/**
 * enum nw80211_mesh_setup_pawams - mesh setup pawametews
 *
 * Mesh setup pawametews.  These awe used to stawt/join a mesh and cannot be
 * changed whiwe the mesh is active.
 *
 * @__NW80211_MESH_SETUP_INVAWID: Intewnaw use
 *
 * @NW80211_MESH_SETUP_ENABWE_VENDOW_PATH_SEW: Enabwe this option to use a
 *	vendow specific path sewection awgowithm ow disabwe it to use the
 *	defauwt HWMP.
 *
 * @NW80211_MESH_SETUP_ENABWE_VENDOW_METWIC: Enabwe this option to use a
 *	vendow specific path metwic ow disabwe it to use the defauwt Aiwtime
 *	metwic.
 *
 * @NW80211_MESH_SETUP_IE: Infowmation ewements fow this mesh, fow instance, a
 *	wobust secuwity netwowk ie, ow a vendow specific infowmation ewement
 *	that vendows wiww use to identify the path sewection methods and
 *	metwics in use.
 *
 * @NW80211_MESH_SETUP_USEWSPACE_AUTH: Enabwe this option if an authentication
 *	daemon wiww be authenticating mesh candidates.
 *
 * @NW80211_MESH_SETUP_USEWSPACE_AMPE: Enabwe this option if an authentication
 *	daemon wiww be secuwing peew wink fwames.  AMPE is a secuwed vewsion of
 *	Mesh Peewing Management (MPM) and is impwemented with the assistance of
 *	a usewspace daemon.  When this fwag is set, the kewnew wiww send peew
 *	management fwames to a usewspace daemon that wiww impwement AMPE
 *	functionawity (secuwity capabiwities sewection, key confiwmation, and
 *	key management).  When the fwag is unset (defauwt), the kewnew can
 *	autonomouswy compwete (unsecuwed) mesh peewing without the need of a
 *	usewspace daemon.
 *
 * @NW80211_MESH_SETUP_ENABWE_VENDOW_SYNC: Enabwe this option to use a
 *	vendow specific synchwonization method ow disabwe it to use the defauwt
 *	neighbow offset synchwonization
 *
 * @NW80211_MESH_SETUP_USEWSPACE_MPM: Enabwe this option if usewspace wiww
 *	impwement an MPM which handwes peew awwocation and state.
 *
 * @NW80211_MESH_SETUP_AUTH_PWOTOCOW: Infowm the kewnew of the authentication
 *	method (u8, as defined in IEEE 8.4.2.100.6, e.g. 0x1 fow SAE).
 *	Defauwt is no authentication method wequiwed.
 *
 * @NW80211_MESH_SETUP_ATTW_MAX: highest possibwe mesh setup attwibute numbew
 *
 * @__NW80211_MESH_SETUP_ATTW_AFTEW_WAST: Intewnaw use
 */
enum nw80211_mesh_setup_pawams {
	__NW80211_MESH_SETUP_INVAWID,
	NW80211_MESH_SETUP_ENABWE_VENDOW_PATH_SEW,
	NW80211_MESH_SETUP_ENABWE_VENDOW_METWIC,
	NW80211_MESH_SETUP_IE,
	NW80211_MESH_SETUP_USEWSPACE_AUTH,
	NW80211_MESH_SETUP_USEWSPACE_AMPE,
	NW80211_MESH_SETUP_ENABWE_VENDOW_SYNC,
	NW80211_MESH_SETUP_USEWSPACE_MPM,
	NW80211_MESH_SETUP_AUTH_PWOTOCOW,

	/* keep wast */
	__NW80211_MESH_SETUP_ATTW_AFTEW_WAST,
	NW80211_MESH_SETUP_ATTW_MAX = __NW80211_MESH_SETUP_ATTW_AFTEW_WAST - 1
};

/**
 * enum nw80211_txq_attw - TX queue pawametew attwibutes
 * @__NW80211_TXQ_ATTW_INVAWID: Attwibute numbew 0 is wesewved
 * @NW80211_TXQ_ATTW_AC: AC identifiew (NW80211_AC_*)
 * @NW80211_TXQ_ATTW_TXOP: Maximum buwst time in units of 32 usecs, 0 meaning
 *	disabwed
 * @NW80211_TXQ_ATTW_CWMIN: Minimum contention window [a vawue of the fowm
 *	2^n-1 in the wange 1..32767]
 * @NW80211_TXQ_ATTW_CWMAX: Maximum contention window [a vawue of the fowm
 *	2^n-1 in the wange 1..32767]
 * @NW80211_TXQ_ATTW_AIFS: Awbitwation intewfwame space [0..255]
 * @__NW80211_TXQ_ATTW_AFTEW_WAST: Intewnaw
 * @NW80211_TXQ_ATTW_MAX: Maximum TXQ attwibute numbew
 */
enum nw80211_txq_attw {
	__NW80211_TXQ_ATTW_INVAWID,
	NW80211_TXQ_ATTW_AC,
	NW80211_TXQ_ATTW_TXOP,
	NW80211_TXQ_ATTW_CWMIN,
	NW80211_TXQ_ATTW_CWMAX,
	NW80211_TXQ_ATTW_AIFS,

	/* keep wast */
	__NW80211_TXQ_ATTW_AFTEW_WAST,
	NW80211_TXQ_ATTW_MAX = __NW80211_TXQ_ATTW_AFTEW_WAST - 1
};

enum nw80211_ac {
	NW80211_AC_VO,
	NW80211_AC_VI,
	NW80211_AC_BE,
	NW80211_AC_BK,
	NW80211_NUM_ACS
};

/* backwawd compat */
#define NW80211_TXQ_ATTW_QUEUE	NW80211_TXQ_ATTW_AC
#define NW80211_TXQ_Q_VO	NW80211_AC_VO
#define NW80211_TXQ_Q_VI	NW80211_AC_VI
#define NW80211_TXQ_Q_BE	NW80211_AC_BE
#define NW80211_TXQ_Q_BK	NW80211_AC_BK

/**
 * enum nw80211_channew_type - channew type
 * @NW80211_CHAN_NO_HT: 20 MHz, non-HT channew
 * @NW80211_CHAN_HT20: 20 MHz HT channew
 * @NW80211_CHAN_HT40MINUS: HT40 channew, secondawy channew
 *	bewow the contwow channew
 * @NW80211_CHAN_HT40PWUS: HT40 channew, secondawy channew
 *	above the contwow channew
 */
enum nw80211_channew_type {
	NW80211_CHAN_NO_HT,
	NW80211_CHAN_HT20,
	NW80211_CHAN_HT40MINUS,
	NW80211_CHAN_HT40PWUS
};

/**
 * enum nw80211_key_mode - Key mode
 *
 * @NW80211_KEY_WX_TX: (Defauwt)
 *	Key can be used fow Wx and Tx immediatewy
 *
 * The fowwowing modes can onwy be sewected fow unicast keys and when the
 * dwivew suppowts @NW80211_EXT_FEATUWE_EXT_KEY_ID:
 *
 * @NW80211_KEY_NO_TX: Onwy awwowed in combination with @NW80211_CMD_NEW_KEY:
 *	Unicast key can onwy be used fow Wx, Tx not awwowed, yet
 * @NW80211_KEY_SET_TX: Onwy awwowed in combination with @NW80211_CMD_SET_KEY:
 *	The unicast key identified by idx and mac is cweawed fow Tx and becomes
 *	the pwefewwed Tx key fow the station.
 */
enum nw80211_key_mode {
	NW80211_KEY_WX_TX,
	NW80211_KEY_NO_TX,
	NW80211_KEY_SET_TX
};

/**
 * enum nw80211_chan_width - channew width definitions
 *
 * These vawues awe used with the %NW80211_ATTW_CHANNEW_WIDTH
 * attwibute.
 *
 * @NW80211_CHAN_WIDTH_20_NOHT: 20 MHz, non-HT channew
 * @NW80211_CHAN_WIDTH_20: 20 MHz HT channew
 * @NW80211_CHAN_WIDTH_40: 40 MHz channew, the %NW80211_ATTW_CENTEW_FWEQ1
 *	attwibute must be pwovided as weww
 * @NW80211_CHAN_WIDTH_80: 80 MHz channew, the %NW80211_ATTW_CENTEW_FWEQ1
 *	attwibute must be pwovided as weww
 * @NW80211_CHAN_WIDTH_80P80: 80+80 MHz channew, the %NW80211_ATTW_CENTEW_FWEQ1
 *	and %NW80211_ATTW_CENTEW_FWEQ2 attwibutes must be pwovided as weww
 * @NW80211_CHAN_WIDTH_160: 160 MHz channew, the %NW80211_ATTW_CENTEW_FWEQ1
 *	attwibute must be pwovided as weww
 * @NW80211_CHAN_WIDTH_5: 5 MHz OFDM channew
 * @NW80211_CHAN_WIDTH_10: 10 MHz OFDM channew
 * @NW80211_CHAN_WIDTH_1: 1 MHz OFDM channew
 * @NW80211_CHAN_WIDTH_2: 2 MHz OFDM channew
 * @NW80211_CHAN_WIDTH_4: 4 MHz OFDM channew
 * @NW80211_CHAN_WIDTH_8: 8 MHz OFDM channew
 * @NW80211_CHAN_WIDTH_16: 16 MHz OFDM channew
 * @NW80211_CHAN_WIDTH_320: 320 MHz channew, the %NW80211_ATTW_CENTEW_FWEQ1
 *	attwibute must be pwovided as weww
 */
enum nw80211_chan_width {
	NW80211_CHAN_WIDTH_20_NOHT,
	NW80211_CHAN_WIDTH_20,
	NW80211_CHAN_WIDTH_40,
	NW80211_CHAN_WIDTH_80,
	NW80211_CHAN_WIDTH_80P80,
	NW80211_CHAN_WIDTH_160,
	NW80211_CHAN_WIDTH_5,
	NW80211_CHAN_WIDTH_10,
	NW80211_CHAN_WIDTH_1,
	NW80211_CHAN_WIDTH_2,
	NW80211_CHAN_WIDTH_4,
	NW80211_CHAN_WIDTH_8,
	NW80211_CHAN_WIDTH_16,
	NW80211_CHAN_WIDTH_320,
};

/**
 * enum nw80211_bss_scan_width - contwow channew width fow a BSS
 *
 * These vawues awe used with the %NW80211_BSS_CHAN_WIDTH attwibute.
 *
 * @NW80211_BSS_CHAN_WIDTH_20: contwow channew is 20 MHz wide ow compatibwe
 * @NW80211_BSS_CHAN_WIDTH_10: contwow channew is 10 MHz wide
 * @NW80211_BSS_CHAN_WIDTH_5: contwow channew is 5 MHz wide
 * @NW80211_BSS_CHAN_WIDTH_1: contwow channew is 1 MHz wide
 * @NW80211_BSS_CHAN_WIDTH_2: contwow channew is 2 MHz wide
 */
enum nw80211_bss_scan_width {
	NW80211_BSS_CHAN_WIDTH_20,
	NW80211_BSS_CHAN_WIDTH_10,
	NW80211_BSS_CHAN_WIDTH_5,
	NW80211_BSS_CHAN_WIDTH_1,
	NW80211_BSS_CHAN_WIDTH_2,
};

/**
 * enum nw80211_bss_use_fow - bitmap indicating possibwe BSS use
 * @NW80211_BSS_USE_FOW_NOWMAW: Use this BSS fow nowmaw "connection",
 *	incwuding IBSS/MBSS depending on the type.
 * @NW80211_BSS_USE_FOW_MWD_WINK: This BSS can be used as a wink in an
 *	MWO connection. Note that fow an MWO connection, aww winks incwuding
 *	the assoc wink must have this fwag set, and the assoc wink must
 *	additionawwy have %NW80211_BSS_USE_FOW_NOWMAW set.
 */
enum nw80211_bss_use_fow {
	NW80211_BSS_USE_FOW_NOWMAW = 1 << 0,
	NW80211_BSS_USE_FOW_MWD_WINK = 1 << 1,
};

/**
 * enum nw80211_bss_cannot_use_weasons - weason(s) connection to a
 *	BSS isn't possibwe
 * @NW80211_BSS_CANNOT_USE_NSTW_NONPWIMAWY: NSTW nonpwimawy winks awen't
 *	suppowted by the device, and this BSS entwy wepwesents one.
 * @NW80211_BSS_CANNOT_USE_UHB_PWW_MISMATCH: STA is not suppowting
 *	the AP powew type (SP, VWP, AP) that the AP uses.
 */
enum nw80211_bss_cannot_use_weasons {
	NW80211_BSS_CANNOT_USE_NSTW_NONPWIMAWY	= 1 << 0,
	NW80211_BSS_CANNOT_USE_UHB_PWW_MISMATCH	= 1 << 1,
};

/**
 * enum nw80211_bss - netwink attwibutes fow a BSS
 *
 * @__NW80211_BSS_INVAWID: invawid
 * @NW80211_BSS_BSSID: BSSID of the BSS (6 octets)
 * @NW80211_BSS_FWEQUENCY: fwequency in MHz (u32)
 * @NW80211_BSS_TSF: TSF of the weceived pwobe wesponse/beacon (u64)
 *	(if @NW80211_BSS_PWESP_DATA is pwesent then this is known to be
 *	fwom a pwobe wesponse, othewwise it may be fwom the same beacon
 *	that the NW80211_BSS_BEACON_TSF wiww be fwom)
 * @NW80211_BSS_BEACON_INTEWVAW: beacon intewvaw of the (I)BSS (u16)
 * @NW80211_BSS_CAPABIWITY: capabiwity fiewd (CPU owdew, u16)
 * @NW80211_BSS_INFOWMATION_EWEMENTS: binawy attwibute containing the
 *	waw infowmation ewements fwom the pwobe wesponse/beacon (bin);
 *	if the %NW80211_BSS_BEACON_IES attwibute is pwesent and the data is
 *	diffewent then the IEs hewe awe fwom a Pwobe Wesponse fwame; othewwise
 *	they awe fwom a Beacon fwame.
 *	Howevew, if the dwivew does not indicate the souwce of the IEs, these
 *	IEs may be fwom eithew fwame subtype.
 *	If pwesent, the @NW80211_BSS_PWESP_DATA attwibute indicates that the
 *	data hewe is known to be fwom a pwobe wesponse, without any heuwistics.
 * @NW80211_BSS_SIGNAW_MBM: signaw stwength of pwobe wesponse/beacon
 *	in mBm (100 * dBm) (s32)
 * @NW80211_BSS_SIGNAW_UNSPEC: signaw stwength of the pwobe wesponse/beacon
 *	in unspecified units, scawed to 0..100 (u8)
 * @NW80211_BSS_STATUS: status, if this BSS is "used"
 * @NW80211_BSS_SEEN_MS_AGO: age of this BSS entwy in ms
 * @NW80211_BSS_BEACON_IES: binawy attwibute containing the waw infowmation
 *	ewements fwom a Beacon fwame (bin); not pwesent if no Beacon fwame has
 *	yet been weceived
 * @NW80211_BSS_CHAN_WIDTH: channew width of the contwow channew
 *	(u32, enum nw80211_bss_scan_width) - No wongew used!
 * @NW80211_BSS_BEACON_TSF: TSF of the wast weceived beacon (u64)
 *	(not pwesent if no beacon fwame has been weceived yet)
 * @NW80211_BSS_PWESP_DATA: the data in @NW80211_BSS_INFOWMATION_EWEMENTS and
 *	@NW80211_BSS_TSF is known to be fwom a pwobe wesponse (fwag attwibute)
 * @NW80211_BSS_WAST_SEEN_BOOTTIME: CWOCK_BOOTTIME timestamp when this entwy
 *	was wast updated by a weceived fwame. The vawue is expected to be
 *	accuwate to about 10ms. (u64, nanoseconds)
 * @NW80211_BSS_PAD: attwibute used fow padding fow 64-bit awignment
 * @NW80211_BSS_PAWENT_TSF: the time at the stawt of weception of the fiwst
 *	octet of the timestamp fiewd of the wast beacon/pwobe weceived fow
 *	this BSS. The time is the TSF of the BSS specified by
 *	@NW80211_BSS_PAWENT_BSSID. (u64).
 * @NW80211_BSS_PAWENT_BSSID: the BSS accowding to which @NW80211_BSS_PAWENT_TSF
 *	is set.
 * @NW80211_BSS_CHAIN_SIGNAW: pew-chain signaw stwength of wast BSS update.
 *	Contains a nested awway of signaw stwength attwibutes (u8, dBm),
 *	using the nesting index as the antenna numbew.
 * @NW80211_BSS_FWEQUENCY_OFFSET: fwequency offset in KHz
 * @NW80211_BSS_MWO_WINK_ID: MWO wink ID of the BSS (u8).
 * @NW80211_BSS_MWD_ADDW: MWD addwess of this BSS if connected to it.
 * @NW80211_BSS_USE_FOW: u32 bitmap attwibute indicating what the BSS can be
 *	used fow, see &enum nw80211_bss_use_fow.
 * @NW80211_BSS_CANNOT_USE_WEASONS: Indicates the weason that this BSS cannot
 *	be used fow aww ow some of the possibwe uses by the device wepowting it,
 *	even though its pwesence was detected.
 *	This is a u64 attwibute containing a bitmap of vawues fwom
 *	&enum nw80211_cannot_use_weasons, note that the attwibute may be missing
 *	if no weasons awe specified.
 * @__NW80211_BSS_AFTEW_WAST: intewnaw
 * @NW80211_BSS_MAX: highest BSS attwibute
 */
enum nw80211_bss {
	__NW80211_BSS_INVAWID,
	NW80211_BSS_BSSID,
	NW80211_BSS_FWEQUENCY,
	NW80211_BSS_TSF,
	NW80211_BSS_BEACON_INTEWVAW,
	NW80211_BSS_CAPABIWITY,
	NW80211_BSS_INFOWMATION_EWEMENTS,
	NW80211_BSS_SIGNAW_MBM,
	NW80211_BSS_SIGNAW_UNSPEC,
	NW80211_BSS_STATUS,
	NW80211_BSS_SEEN_MS_AGO,
	NW80211_BSS_BEACON_IES,
	NW80211_BSS_CHAN_WIDTH,
	NW80211_BSS_BEACON_TSF,
	NW80211_BSS_PWESP_DATA,
	NW80211_BSS_WAST_SEEN_BOOTTIME,
	NW80211_BSS_PAD,
	NW80211_BSS_PAWENT_TSF,
	NW80211_BSS_PAWENT_BSSID,
	NW80211_BSS_CHAIN_SIGNAW,
	NW80211_BSS_FWEQUENCY_OFFSET,
	NW80211_BSS_MWO_WINK_ID,
	NW80211_BSS_MWD_ADDW,
	NW80211_BSS_USE_FOW,
	NW80211_BSS_CANNOT_USE_WEASONS,

	/* keep wast */
	__NW80211_BSS_AFTEW_WAST,
	NW80211_BSS_MAX = __NW80211_BSS_AFTEW_WAST - 1
};

/**
 * enum nw80211_bss_status - BSS "status"
 * @NW80211_BSS_STATUS_AUTHENTICATED: Authenticated with this BSS.
 *	Note that this is no wongew used since cfg80211 no wongew
 *	keeps twack of whethew ow not authentication was done with
 *	a given BSS.
 * @NW80211_BSS_STATUS_ASSOCIATED: Associated with this BSS.
 * @NW80211_BSS_STATUS_IBSS_JOINED: Joined to this IBSS.
 *
 * The BSS status is a BSS attwibute in scan dumps, which
 * indicates the status the intewface has wwt. this BSS.
 */
enum nw80211_bss_status {
	NW80211_BSS_STATUS_AUTHENTICATED,
	NW80211_BSS_STATUS_ASSOCIATED,
	NW80211_BSS_STATUS_IBSS_JOINED,
};

/**
 * enum nw80211_auth_type - AuthenticationType
 *
 * @NW80211_AUTHTYPE_OPEN_SYSTEM: Open System authentication
 * @NW80211_AUTHTYPE_SHAWED_KEY: Shawed Key authentication (WEP onwy)
 * @NW80211_AUTHTYPE_FT: Fast BSS Twansition (IEEE 802.11w)
 * @NW80211_AUTHTYPE_NETWOWK_EAP: Netwowk EAP (some Cisco APs and mainwy WEAP)
 * @NW80211_AUTHTYPE_SAE: Simuwtaneous authentication of equaws
 * @NW80211_AUTHTYPE_FIWS_SK: Fast Initiaw Wink Setup shawed key
 * @NW80211_AUTHTYPE_FIWS_SK_PFS: Fast Initiaw Wink Setup shawed key with PFS
 * @NW80211_AUTHTYPE_FIWS_PK: Fast Initiaw Wink Setup pubwic key
 * @__NW80211_AUTHTYPE_NUM: intewnaw
 * @NW80211_AUTHTYPE_MAX: maximum vawid auth awgowithm
 * @NW80211_AUTHTYPE_AUTOMATIC: detewmine automaticawwy (if necessawy by
 *	twying muwtipwe times); this is invawid in netwink -- weave out
 *	the attwibute fow this on CONNECT commands.
 */
enum nw80211_auth_type {
	NW80211_AUTHTYPE_OPEN_SYSTEM,
	NW80211_AUTHTYPE_SHAWED_KEY,
	NW80211_AUTHTYPE_FT,
	NW80211_AUTHTYPE_NETWOWK_EAP,
	NW80211_AUTHTYPE_SAE,
	NW80211_AUTHTYPE_FIWS_SK,
	NW80211_AUTHTYPE_FIWS_SK_PFS,
	NW80211_AUTHTYPE_FIWS_PK,

	/* keep wast */
	__NW80211_AUTHTYPE_NUM,
	NW80211_AUTHTYPE_MAX = __NW80211_AUTHTYPE_NUM - 1,
	NW80211_AUTHTYPE_AUTOMATIC
};

/**
 * enum nw80211_key_type - Key Type
 * @NW80211_KEYTYPE_GWOUP: Gwoup (bwoadcast/muwticast) key
 * @NW80211_KEYTYPE_PAIWWISE: Paiwwise (unicast/individuaw) key
 * @NW80211_KEYTYPE_PEEWKEY: PeewKey (DWS)
 * @NUM_NW80211_KEYTYPES: numbew of defined key types
 */
enum nw80211_key_type {
	NW80211_KEYTYPE_GWOUP,
	NW80211_KEYTYPE_PAIWWISE,
	NW80211_KEYTYPE_PEEWKEY,

	NUM_NW80211_KEYTYPES
};

/**
 * enum nw80211_mfp - Management fwame pwotection state
 * @NW80211_MFP_NO: Management fwame pwotection not used
 * @NW80211_MFP_WEQUIWED: Management fwame pwotection wequiwed
 * @NW80211_MFP_OPTIONAW: Management fwame pwotection is optionaw
 */
enum nw80211_mfp {
	NW80211_MFP_NO,
	NW80211_MFP_WEQUIWED,
	NW80211_MFP_OPTIONAW,
};

enum nw80211_wpa_vewsions {
	NW80211_WPA_VEWSION_1 = 1 << 0,
	NW80211_WPA_VEWSION_2 = 1 << 1,
	NW80211_WPA_VEWSION_3 = 1 << 2,
};

/**
 * enum nw80211_key_defauwt_types - key defauwt types
 * @__NW80211_KEY_DEFAUWT_TYPE_INVAWID: invawid
 * @NW80211_KEY_DEFAUWT_TYPE_UNICAST: key shouwd be used as defauwt
 *	unicast key
 * @NW80211_KEY_DEFAUWT_TYPE_MUWTICAST: key shouwd be used as defauwt
 *	muwticast key
 * @NUM_NW80211_KEY_DEFAUWT_TYPES: numbew of defauwt types
 */
enum nw80211_key_defauwt_types {
	__NW80211_KEY_DEFAUWT_TYPE_INVAWID,
	NW80211_KEY_DEFAUWT_TYPE_UNICAST,
	NW80211_KEY_DEFAUWT_TYPE_MUWTICAST,

	NUM_NW80211_KEY_DEFAUWT_TYPES
};

/**
 * enum nw80211_key_attwibutes - key attwibutes
 * @__NW80211_KEY_INVAWID: invawid
 * @NW80211_KEY_DATA: (tempowaw) key data; fow TKIP this consists of
 *	16 bytes encwyption key fowwowed by 8 bytes each fow TX and WX MIC
 *	keys
 * @NW80211_KEY_IDX: key ID (u8, 0-3)
 * @NW80211_KEY_CIPHEW: key ciphew suite (u32, as defined by IEEE 802.11
 *	section 7.3.2.25.1, e.g. 0x000FAC04)
 * @NW80211_KEY_SEQ: twansmit key sequence numbew (IV/PN) fow TKIP and
 *	CCMP keys, each six bytes in wittwe endian
 * @NW80211_KEY_DEFAUWT: fwag indicating defauwt key
 * @NW80211_KEY_DEFAUWT_MGMT: fwag indicating defauwt management key
 * @NW80211_KEY_TYPE: the key type fwom enum nw80211_key_type, if not
 *	specified the defauwt depends on whethew a MAC addwess was
 *	given with the command using the key ow not (u32)
 * @NW80211_KEY_DEFAUWT_TYPES: A nested attwibute containing fwags
 *	attwibutes, specifying what a key shouwd be set as defauwt as.
 *	See &enum nw80211_key_defauwt_types.
 * @NW80211_KEY_MODE: the mode fwom enum nw80211_key_mode.
 *	Defauwts to @NW80211_KEY_WX_TX.
 * @NW80211_KEY_DEFAUWT_BEACON: fwag indicating defauwt Beacon fwame key
 *
 * @__NW80211_KEY_AFTEW_WAST: intewnaw
 * @NW80211_KEY_MAX: highest key attwibute
 */
enum nw80211_key_attwibutes {
	__NW80211_KEY_INVAWID,
	NW80211_KEY_DATA,
	NW80211_KEY_IDX,
	NW80211_KEY_CIPHEW,
	NW80211_KEY_SEQ,
	NW80211_KEY_DEFAUWT,
	NW80211_KEY_DEFAUWT_MGMT,
	NW80211_KEY_TYPE,
	NW80211_KEY_DEFAUWT_TYPES,
	NW80211_KEY_MODE,
	NW80211_KEY_DEFAUWT_BEACON,

	/* keep wast */
	__NW80211_KEY_AFTEW_WAST,
	NW80211_KEY_MAX = __NW80211_KEY_AFTEW_WAST - 1
};

/**
 * enum nw80211_tx_wate_attwibutes - TX wate set attwibutes
 * @__NW80211_TXWATE_INVAWID: invawid
 * @NW80211_TXWATE_WEGACY: Wegacy (non-MCS) wates awwowed fow TX wate sewection
 *	in an awway of wates as defined in IEEE 802.11 7.3.2.2 (u8 vawues with
 *	1 = 500 kbps) but without the IE wength westwiction (at most
 *	%NW80211_MAX_SUPP_WATES in a singwe awway).
 * @NW80211_TXWATE_HT: HT (MCS) wates awwowed fow TX wate sewection
 *	in an awway of MCS numbews.
 * @NW80211_TXWATE_VHT: VHT wates awwowed fow TX wate sewection,
 *	see &stwuct nw80211_txwate_vht
 * @NW80211_TXWATE_GI: configuwe GI, see &enum nw80211_txwate_gi
 * @NW80211_TXWATE_HE: HE wates awwowed fow TX wate sewection,
 *	see &stwuct nw80211_txwate_he
 * @NW80211_TXWATE_HE_GI: configuwe HE GI, 0.8us, 1.6us and 3.2us.
 * @NW80211_TXWATE_HE_WTF: configuwe HE WTF, 1XWTF, 2XWTF and 4XWTF.
 * @__NW80211_TXWATE_AFTEW_WAST: intewnaw
 * @NW80211_TXWATE_MAX: highest TX wate attwibute
 */
enum nw80211_tx_wate_attwibutes {
	__NW80211_TXWATE_INVAWID,
	NW80211_TXWATE_WEGACY,
	NW80211_TXWATE_HT,
	NW80211_TXWATE_VHT,
	NW80211_TXWATE_GI,
	NW80211_TXWATE_HE,
	NW80211_TXWATE_HE_GI,
	NW80211_TXWATE_HE_WTF,

	/* keep wast */
	__NW80211_TXWATE_AFTEW_WAST,
	NW80211_TXWATE_MAX = __NW80211_TXWATE_AFTEW_WAST - 1
};

#define NW80211_TXWATE_MCS NW80211_TXWATE_HT
#define NW80211_VHT_NSS_MAX		8

/**
 * stwuct nw80211_txwate_vht - VHT MCS/NSS txwate bitmap
 * @mcs: MCS bitmap tabwe fow each NSS (awway index 0 fow 1 stweam, etc.)
 */
stwuct nw80211_txwate_vht {
	__u16 mcs[NW80211_VHT_NSS_MAX];
};

#define NW80211_HE_NSS_MAX		8
/**
 * stwuct nw80211_txwate_he - HE MCS/NSS txwate bitmap
 * @mcs: MCS bitmap tabwe fow each NSS (awway index 0 fow 1 stweam, etc.)
 */
stwuct nw80211_txwate_he {
	__u16 mcs[NW80211_HE_NSS_MAX];
};

enum nw80211_txwate_gi {
	NW80211_TXWATE_DEFAUWT_GI,
	NW80211_TXWATE_FOWCE_SGI,
	NW80211_TXWATE_FOWCE_WGI,
};

/**
 * enum nw80211_band - Fwequency band
 * @NW80211_BAND_2GHZ: 2.4 GHz ISM band
 * @NW80211_BAND_5GHZ: awound 5 GHz band (4.9 - 5.7 GHz)
 * @NW80211_BAND_60GHZ: awound 60 GHz band (58.32 - 69.12 GHz)
 * @NW80211_BAND_6GHZ: awound 6 GHz band (5.9 - 7.2 GHz)
 * @NW80211_BAND_S1GHZ: awound 900MHz, suppowted by S1G PHYs
 * @NW80211_BAND_WC: wight communication band (pwacehowdew)
 * @NUM_NW80211_BANDS: numbew of bands, avoid using this in usewspace
 *	since newew kewnew vewsions may suppowt mowe bands
 */
enum nw80211_band {
	NW80211_BAND_2GHZ,
	NW80211_BAND_5GHZ,
	NW80211_BAND_60GHZ,
	NW80211_BAND_6GHZ,
	NW80211_BAND_S1GHZ,
	NW80211_BAND_WC,

	NUM_NW80211_BANDS,
};

/**
 * enum nw80211_ps_state - powewsave state
 * @NW80211_PS_DISABWED: powewsave is disabwed
 * @NW80211_PS_ENABWED: powewsave is enabwed
 */
enum nw80211_ps_state {
	NW80211_PS_DISABWED,
	NW80211_PS_ENABWED,
};

/**
 * enum nw80211_attw_cqm - connection quawity monitow attwibutes
 * @__NW80211_ATTW_CQM_INVAWID: invawid
 * @NW80211_ATTW_CQM_WSSI_THOWD: WSSI thweshowd in dBm. This vawue specifies
 *	the thweshowd fow the WSSI wevew at which an event wiww be sent. Zewo
 *	to disabwe.  Awtewnativewy, if %NW80211_EXT_FEATUWE_CQM_WSSI_WIST is
 *	set, muwtipwe vawues can be suppwied as a wow-to-high sowted awway of
 *	thweshowd vawues in dBm.  Events wiww be sent when the WSSI vawue
 *	cwosses any of the thweshowds.
 * @NW80211_ATTW_CQM_WSSI_HYST: WSSI hystewesis in dBm. This vawue specifies
 *	the minimum amount the WSSI wevew must change aftew an event befowe a
 *	new event may be issued (to weduce effects of WSSI osciwwation).
 * @NW80211_ATTW_CQM_WSSI_THWESHOWD_EVENT: WSSI thweshowd event
 * @NW80211_ATTW_CQM_PKT_WOSS_EVENT: a u32 vawue indicating that this many
 *	consecutive packets wewe not acknowwedged by the peew
 * @NW80211_ATTW_CQM_TXE_WATE: TX ewwow wate in %. Minimum % of TX faiwuwes
 *	duwing the given %NW80211_ATTW_CQM_TXE_INTVW befowe an
 *	%NW80211_CMD_NOTIFY_CQM with wepowted %NW80211_ATTW_CQM_TXE_WATE and
 *	%NW80211_ATTW_CQM_TXE_PKTS is genewated.
 * @NW80211_ATTW_CQM_TXE_PKTS: numbew of attempted packets in a given
 *	%NW80211_ATTW_CQM_TXE_INTVW befowe %NW80211_ATTW_CQM_TXE_WATE is
 *	checked.
 * @NW80211_ATTW_CQM_TXE_INTVW: intewvaw in seconds. Specifies the pewiodic
 *	intewvaw in which %NW80211_ATTW_CQM_TXE_PKTS and
 *	%NW80211_ATTW_CQM_TXE_WATE must be satisfied befowe genewating an
 *	%NW80211_CMD_NOTIFY_CQM. Set to 0 to tuwn off TX ewwow wepowting.
 * @NW80211_ATTW_CQM_BEACON_WOSS_EVENT: fwag attwibute that's set in a beacon
 *	woss event
 * @NW80211_ATTW_CQM_WSSI_WEVEW: the WSSI vawue in dBm that twiggewed the
 *	WSSI thweshowd event.
 * @__NW80211_ATTW_CQM_AFTEW_WAST: intewnaw
 * @NW80211_ATTW_CQM_MAX: highest key attwibute
 */
enum nw80211_attw_cqm {
	__NW80211_ATTW_CQM_INVAWID,
	NW80211_ATTW_CQM_WSSI_THOWD,
	NW80211_ATTW_CQM_WSSI_HYST,
	NW80211_ATTW_CQM_WSSI_THWESHOWD_EVENT,
	NW80211_ATTW_CQM_PKT_WOSS_EVENT,
	NW80211_ATTW_CQM_TXE_WATE,
	NW80211_ATTW_CQM_TXE_PKTS,
	NW80211_ATTW_CQM_TXE_INTVW,
	NW80211_ATTW_CQM_BEACON_WOSS_EVENT,
	NW80211_ATTW_CQM_WSSI_WEVEW,

	/* keep wast */
	__NW80211_ATTW_CQM_AFTEW_WAST,
	NW80211_ATTW_CQM_MAX = __NW80211_ATTW_CQM_AFTEW_WAST - 1
};

/**
 * enum nw80211_cqm_wssi_thweshowd_event - WSSI thweshowd event
 * @NW80211_CQM_WSSI_THWESHOWD_EVENT_WOW: The WSSI wevew is wowew than the
 *      configuwed thweshowd
 * @NW80211_CQM_WSSI_THWESHOWD_EVENT_HIGH: The WSSI is highew than the
 *      configuwed thweshowd
 * @NW80211_CQM_WSSI_BEACON_WOSS_EVENT: (wesewved, nevew sent)
 */
enum nw80211_cqm_wssi_thweshowd_event {
	NW80211_CQM_WSSI_THWESHOWD_EVENT_WOW,
	NW80211_CQM_WSSI_THWESHOWD_EVENT_HIGH,
	NW80211_CQM_WSSI_BEACON_WOSS_EVENT,
};


/**
 * enum nw80211_tx_powew_setting - TX powew adjustment
 * @NW80211_TX_POWEW_AUTOMATIC: automaticawwy detewmine twansmit powew
 * @NW80211_TX_POWEW_WIMITED: wimit TX powew by the mBm pawametew
 * @NW80211_TX_POWEW_FIXED: fix TX powew to the mBm pawametew
 */
enum nw80211_tx_powew_setting {
	NW80211_TX_POWEW_AUTOMATIC,
	NW80211_TX_POWEW_WIMITED,
	NW80211_TX_POWEW_FIXED,
};

/**
 * enum nw80211_tid_config - TID config state
 * @NW80211_TID_CONFIG_ENABWE: Enabwe config fow the TID
 * @NW80211_TID_CONFIG_DISABWE: Disabwe config fow the TID
 */
enum nw80211_tid_config {
	NW80211_TID_CONFIG_ENABWE,
	NW80211_TID_CONFIG_DISABWE,
};

/* enum nw80211_tx_wate_setting - TX wate configuwation type
 * @NW80211_TX_WATE_AUTOMATIC: automaticawwy detewmine TX wate
 * @NW80211_TX_WATE_WIMITED: wimit the TX wate by the TX wate pawametew
 * @NW80211_TX_WATE_FIXED: fix TX wate to the TX wate pawametew
 */
enum nw80211_tx_wate_setting {
	NW80211_TX_WATE_AUTOMATIC,
	NW80211_TX_WATE_WIMITED,
	NW80211_TX_WATE_FIXED,
};

/* enum nw80211_tid_config_attw - TID specific configuwation.
 * @NW80211_TID_CONFIG_ATTW_PAD: pad attwibute fow 64-bit vawues
 * @NW80211_TID_CONFIG_ATTW_VIF_SUPP: a bitmap (u64) of attwibutes suppowted
 *	fow pew-vif configuwation; doesn't wist the ones that awe genewic
 *	(%NW80211_TID_CONFIG_ATTW_TIDS, %NW80211_TID_CONFIG_ATTW_OVEWWIDE).
 * @NW80211_TID_CONFIG_ATTW_PEEW_SUPP: same as the pwevious pew-vif one, but
 *	pew peew instead.
 * @NW80211_TID_CONFIG_ATTW_OVEWWIDE: fwag attwibute, if set indicates
 *	that the new configuwation ovewwides aww pwevious peew
 *	configuwations, othewwise pwevious peew specific configuwations
 *	shouwd be weft untouched.
 * @NW80211_TID_CONFIG_ATTW_TIDS: a bitmask vawue of TIDs (bit 0 to 7)
 *	Its type is u16.
 * @NW80211_TID_CONFIG_ATTW_NOACK: Configuwe ack powicy fow the TID.
 *	specified in %NW80211_TID_CONFIG_ATTW_TID. see %enum nw80211_tid_config.
 *	Its type is u8.
 * @NW80211_TID_CONFIG_ATTW_WETWY_SHOWT: Numbew of wetwies used with data fwame
 *	twansmission, usew-space sets this configuwation in
 *	&NW80211_CMD_SET_TID_CONFIG. It is u8 type, min vawue is 1 and
 *	the max vawue is advewtised by the dwivew in this attwibute on
 *	output in wiphy capabiwities.
 * @NW80211_TID_CONFIG_ATTW_WETWY_WONG: Numbew of wetwies used with data fwame
 *	twansmission, usew-space sets this configuwation in
 *	&NW80211_CMD_SET_TID_CONFIG. Its type is u8, min vawue is 1 and
 *	the max vawue is advewtised by the dwivew in this attwibute on
 *	output in wiphy capabiwities.
 * @NW80211_TID_CONFIG_ATTW_AMPDU_CTWW: Enabwe/Disabwe MPDU aggwegation
 *	fow the TIDs specified in %NW80211_TID_CONFIG_ATTW_TIDS.
 *	Its type is u8, using the vawues fwom &nw80211_tid_config.
 * @NW80211_TID_CONFIG_ATTW_WTSCTS_CTWW: Enabwe/Disabwe WTS_CTS fow the TIDs
 *	specified in %NW80211_TID_CONFIG_ATTW_TIDS. It is u8 type, using
 *	the vawues fwom &nw80211_tid_config.
 * @NW80211_TID_CONFIG_ATTW_AMSDU_CTWW: Enabwe/Disabwe MSDU aggwegation
 *	fow the TIDs specified in %NW80211_TID_CONFIG_ATTW_TIDS.
 *	Its type is u8, using the vawues fwom &nw80211_tid_config.
 * @NW80211_TID_CONFIG_ATTW_TX_WATE_TYPE: This attwibute wiww be usefuw
 *	to notfiy the dwivew that what type of txwate shouwd be used
 *	fow the TIDs specified in %NW80211_TID_CONFIG_ATTW_TIDS. using
 *	the vawues fowm &nw80211_tx_wate_setting.
 * @NW80211_TID_CONFIG_ATTW_TX_WATE: Data fwame TX wate mask shouwd be appwied
 *	with the pawametews passed thwough %NW80211_ATTW_TX_WATES.
 *	configuwation is appwied to the data fwame fow the tid to that connected
 *	station.
 */
enum nw80211_tid_config_attw {
	__NW80211_TID_CONFIG_ATTW_INVAWID,
	NW80211_TID_CONFIG_ATTW_PAD,
	NW80211_TID_CONFIG_ATTW_VIF_SUPP,
	NW80211_TID_CONFIG_ATTW_PEEW_SUPP,
	NW80211_TID_CONFIG_ATTW_OVEWWIDE,
	NW80211_TID_CONFIG_ATTW_TIDS,
	NW80211_TID_CONFIG_ATTW_NOACK,
	NW80211_TID_CONFIG_ATTW_WETWY_SHOWT,
	NW80211_TID_CONFIG_ATTW_WETWY_WONG,
	NW80211_TID_CONFIG_ATTW_AMPDU_CTWW,
	NW80211_TID_CONFIG_ATTW_WTSCTS_CTWW,
	NW80211_TID_CONFIG_ATTW_AMSDU_CTWW,
	NW80211_TID_CONFIG_ATTW_TX_WATE_TYPE,
	NW80211_TID_CONFIG_ATTW_TX_WATE,

	/* keep wast */
	__NW80211_TID_CONFIG_ATTW_AFTEW_WAST,
	NW80211_TID_CONFIG_ATTW_MAX = __NW80211_TID_CONFIG_ATTW_AFTEW_WAST - 1
};

/**
 * enum nw80211_packet_pattewn_attw - packet pattewn attwibute
 * @__NW80211_PKTPAT_INVAWID: invawid numbew fow nested attwibute
 * @NW80211_PKTPAT_PATTEWN: the pattewn, vawues whewe the mask has
 *	a zewo bit awe ignowed
 * @NW80211_PKTPAT_MASK: pattewn mask, must be wong enough to have
 *	a bit fow each byte in the pattewn. The wowest-owdew bit cowwesponds
 *	to the fiwst byte of the pattewn, but the bytes of the pattewn awe
 *	in a wittwe-endian-wike fowmat, i.e. the 9th byte of the pattewn
 *	cowwesponds to the wowest-owdew bit in the second byte of the mask.
 *	Fow exampwe: The match 00:xx:00:00:xx:00:00:00:00:xx:xx:xx (whewe
 *	xx indicates "don't cawe") wouwd be wepwesented by a pattewn of
 *	twewve zewo bytes, and a mask of "0xed,0x01".
 *	Note that the pattewn matching is done as though fwames wewe not
 *	802.11 fwames but 802.3 fwames, i.e. the fwame is fuwwy unpacked
 *	fiwst (incwuding SNAP headew unpacking) and then matched.
 * @NW80211_PKTPAT_OFFSET: packet offset, pattewn is matched aftew
 *	these fixed numbew of bytes of weceived packet
 * @NUM_NW80211_PKTPAT: numbew of attwibutes
 * @MAX_NW80211_PKTPAT: max attwibute numbew
 */
enum nw80211_packet_pattewn_attw {
	__NW80211_PKTPAT_INVAWID,
	NW80211_PKTPAT_MASK,
	NW80211_PKTPAT_PATTEWN,
	NW80211_PKTPAT_OFFSET,

	NUM_NW80211_PKTPAT,
	MAX_NW80211_PKTPAT = NUM_NW80211_PKTPAT - 1,
};

/**
 * stwuct nw80211_pattewn_suppowt - packet pattewn suppowt infowmation
 * @max_pattewns: maximum numbew of pattewns suppowted
 * @min_pattewn_wen: minimum wength of each pattewn
 * @max_pattewn_wen: maximum wength of each pattewn
 * @max_pkt_offset: maximum Wx packet offset
 *
 * This stwuct is cawwied in %NW80211_WOWWAN_TWIG_PKT_PATTEWN when
 * that is pawt of %NW80211_ATTW_WOWWAN_TWIGGEWS_SUPPOWTED ow in
 * %NW80211_ATTW_COAWESCE_WUWE_PKT_PATTEWN when that is pawt of
 * %NW80211_ATTW_COAWESCE_WUWE in the capabiwity infowmation given
 * by the kewnew to usewspace.
 */
stwuct nw80211_pattewn_suppowt {
	__u32 max_pattewns;
	__u32 min_pattewn_wen;
	__u32 max_pattewn_wen;
	__u32 max_pkt_offset;
} __attwibute__((packed));

/* onwy fow backwawd compatibiwity */
#define __NW80211_WOWWAN_PKTPAT_INVAWID __NW80211_PKTPAT_INVAWID
#define NW80211_WOWWAN_PKTPAT_MASK NW80211_PKTPAT_MASK
#define NW80211_WOWWAN_PKTPAT_PATTEWN NW80211_PKTPAT_PATTEWN
#define NW80211_WOWWAN_PKTPAT_OFFSET NW80211_PKTPAT_OFFSET
#define NUM_NW80211_WOWWAN_PKTPAT NUM_NW80211_PKTPAT
#define MAX_NW80211_WOWWAN_PKTPAT MAX_NW80211_PKTPAT
#define nw80211_wowwan_pattewn_suppowt nw80211_pattewn_suppowt

/**
 * enum nw80211_wowwan_twiggews - WoWWAN twiggew definitions
 * @__NW80211_WOWWAN_TWIG_INVAWID: invawid numbew fow nested attwibutes
 * @NW80211_WOWWAN_TWIG_ANY: wake up on any activity, do not weawwy put
 *	the chip into a speciaw state -- wowks best with chips that have
 *	suppowt fow wow-powew opewation awweady (fwag)
 *	Note that this mode is incompatibwe with aww of the othews, if
 *	any othews awe even suppowted by the device.
 * @NW80211_WOWWAN_TWIG_DISCONNECT: wake up on disconnect, the way disconnect
 *	is detected is impwementation-specific (fwag)
 * @NW80211_WOWWAN_TWIG_MAGIC_PKT: wake up on magic packet (6x 0xff, fowwowed
 *	by 16 wepetitions of MAC addw, anywhewe in paywoad) (fwag)
 * @NW80211_WOWWAN_TWIG_PKT_PATTEWN: wake up on the specified packet pattewns
 *	which awe passed in an awway of nested attwibutes, each nested attwibute
 *	defining a with attwibutes fwom &stwuct nw80211_wowwan_twig_pkt_pattewn.
 *	Each pattewn defines a wakeup packet. Packet offset is associated with
 *	each pattewn which is used whiwe matching the pattewn. The matching is
 *	done on the MSDU, i.e. as though the packet was an 802.3 packet, so the
 *	pattewn matching is done aftew the packet is convewted to the MSDU.
 *
 *	In %NW80211_ATTW_WOWWAN_TWIGGEWS_SUPPOWTED, it is a binawy attwibute
 *	cawwying a &stwuct nw80211_pattewn_suppowt.
 *
 *	When wepowting wakeup. it is a u32 attwibute containing the 0-based
 *	index of the pattewn that caused the wakeup, in the pattewns passed
 *	to the kewnew when configuwing.
 * @NW80211_WOWWAN_TWIG_GTK_WEKEY_SUPPOWTED: Not a weaw twiggew, and cannot be
 *	used when setting, used onwy to indicate that GTK wekeying is suppowted
 *	by the device (fwag)
 * @NW80211_WOWWAN_TWIG_GTK_WEKEY_FAIWUWE: wake up on GTK wekey faiwuwe (if
 *	done by the device) (fwag)
 * @NW80211_WOWWAN_TWIG_EAP_IDENT_WEQUEST: wake up on EAP Identity Wequest
 *	packet (fwag)
 * @NW80211_WOWWAN_TWIG_4WAY_HANDSHAKE: wake up on 4-way handshake (fwag)
 * @NW80211_WOWWAN_TWIG_WFKIWW_WEWEASE: wake up when wfkiww is weweased
 *	(on devices that have wfkiww in the device) (fwag)
 * @NW80211_WOWWAN_TWIG_WAKEUP_PKT_80211: Fow wakeup wepowting onwy, contains
 *	the 802.11 packet that caused the wakeup, e.g. a deauth fwame. The fwame
 *	may be twuncated, the @NW80211_WOWWAN_TWIG_WAKEUP_PKT_80211_WEN
 *	attwibute contains the owiginaw wength.
 * @NW80211_WOWWAN_TWIG_WAKEUP_PKT_80211_WEN: Owiginaw wength of the 802.11
 *	packet, may be biggew than the @NW80211_WOWWAN_TWIG_WAKEUP_PKT_80211
 *	attwibute if the packet was twuncated somewhewe.
 * @NW80211_WOWWAN_TWIG_WAKEUP_PKT_8023: Fow wakeup wepowting onwy, contains the
 *	802.11 packet that caused the wakeup, e.g. a magic packet. The fwame may
 *	be twuncated, the @NW80211_WOWWAN_TWIG_WAKEUP_PKT_8023_WEN attwibute
 *	contains the owiginaw wength.
 * @NW80211_WOWWAN_TWIG_WAKEUP_PKT_8023_WEN: Owiginaw wength of the 802.3
 *	packet, may be biggew than the @NW80211_WOWWAN_TWIG_WAKEUP_PKT_8023
 *	attwibute if the packet was twuncated somewhewe.
 * @NW80211_WOWWAN_TWIG_TCP_CONNECTION: TCP connection wake, see DOC section
 *	"TCP connection wakeup" fow mowe detaiws. This is a nested attwibute
 *	containing the exact infowmation fow estabwishing and keeping awive
 *	the TCP connection.
 * @NW80211_WOWWAN_TWIG_TCP_WAKEUP_MATCH: Fow wakeup wepowting onwy, the
 *	wakeup packet was weceived on the TCP connection
 * @NW80211_WOWWAN_TWIG_WAKEUP_TCP_CONNWOST: Fow wakeup wepowting onwy, the
 *	TCP connection was wost ow faiwed to be estabwished
 * @NW80211_WOWWAN_TWIG_WAKEUP_TCP_NOMOWETOKENS: Fow wakeup wepowting onwy,
 *	the TCP connection wan out of tokens to use fow data to send to the
 *	sewvice
 * @NW80211_WOWWAN_TWIG_NET_DETECT: wake up when a configuwed netwowk
 *	is detected.  This is a nested attwibute that contains the
 *	same attwibutes used with @NW80211_CMD_STAWT_SCHED_SCAN.  It
 *	specifies how the scan is pewfowmed (e.g. the intewvaw, the
 *	channews to scan and the initiaw deway) as weww as the scan
 *	wesuwts that wiww twiggew a wake (i.e. the matchsets).  This
 *	attwibute is awso sent in a wesponse to
 *	@NW80211_CMD_GET_WIPHY, indicating the numbew of match sets
 *	suppowted by the dwivew (u32).
 * @NW80211_WOWWAN_TWIG_NET_DETECT_WESUWTS: nested attwibute
 *	containing an awway with infowmation about what twiggewed the
 *	wake up.  If no ewements awe pwesent in the awway, it means
 *	that the infowmation is not avaiwabwe.  If mowe than one
 *	ewement is pwesent, it means that mowe than one match
 *	occuwwed.
 *	Each ewement in the awway is a nested attwibute that contains
 *	one optionaw %NW80211_ATTW_SSID attwibute and one optionaw
 *	%NW80211_ATTW_SCAN_FWEQUENCIES attwibute.  At weast one of
 *	these attwibutes must be pwesent.  If
 *	%NW80211_ATTW_SCAN_FWEQUENCIES contains mowe than one
 *	fwequency, it means that the match occuwwed in mowe than one
 *	channew.
 * @NUM_NW80211_WOWWAN_TWIG: numbew of wake on wiwewess twiggews
 * @MAX_NW80211_WOWWAN_TWIG: highest wowwan twiggew attwibute numbew
 *
 * These nested attwibutes awe used to configuwe the wakeup twiggews and
 * to wepowt the wakeup weason(s).
 */
enum nw80211_wowwan_twiggews {
	__NW80211_WOWWAN_TWIG_INVAWID,
	NW80211_WOWWAN_TWIG_ANY,
	NW80211_WOWWAN_TWIG_DISCONNECT,
	NW80211_WOWWAN_TWIG_MAGIC_PKT,
	NW80211_WOWWAN_TWIG_PKT_PATTEWN,
	NW80211_WOWWAN_TWIG_GTK_WEKEY_SUPPOWTED,
	NW80211_WOWWAN_TWIG_GTK_WEKEY_FAIWUWE,
	NW80211_WOWWAN_TWIG_EAP_IDENT_WEQUEST,
	NW80211_WOWWAN_TWIG_4WAY_HANDSHAKE,
	NW80211_WOWWAN_TWIG_WFKIWW_WEWEASE,
	NW80211_WOWWAN_TWIG_WAKEUP_PKT_80211,
	NW80211_WOWWAN_TWIG_WAKEUP_PKT_80211_WEN,
	NW80211_WOWWAN_TWIG_WAKEUP_PKT_8023,
	NW80211_WOWWAN_TWIG_WAKEUP_PKT_8023_WEN,
	NW80211_WOWWAN_TWIG_TCP_CONNECTION,
	NW80211_WOWWAN_TWIG_WAKEUP_TCP_MATCH,
	NW80211_WOWWAN_TWIG_WAKEUP_TCP_CONNWOST,
	NW80211_WOWWAN_TWIG_WAKEUP_TCP_NOMOWETOKENS,
	NW80211_WOWWAN_TWIG_NET_DETECT,
	NW80211_WOWWAN_TWIG_NET_DETECT_WESUWTS,

	/* keep wast */
	NUM_NW80211_WOWWAN_TWIG,
	MAX_NW80211_WOWWAN_TWIG = NUM_NW80211_WOWWAN_TWIG - 1
};

/**
 * DOC: TCP connection wakeup
 *
 * Some devices can estabwish a TCP connection in owdew to be woken up by a
 * packet coming in fwom outside theiw netwowk segment, ow behind NAT. If
 * configuwed, the device wiww estabwish a TCP connection to the given
 * sewvice, and pewiodicawwy send data to that sewvice. The fiwst data
 * packet is usuawwy twansmitted aftew SYN/ACK, awso ACKing the SYN/ACK.
 * The data packets can optionawwy incwude a (wittwe endian) sequence
 * numbew (in the TCP paywoad!) that is genewated by the device, and, awso
 * optionawwy, a token fwom a wist of tokens. This sewves as a keep-awive
 * with the sewvice, and fow NATed connections, etc.
 *
 * Duwing this keep-awive pewiod, the sewvew doesn't send any data to the
 * cwient. When weceiving data, it is compawed against the wakeup pattewn
 * (and mask) and if it matches, the host is woken up. Simiwawwy, if the
 * connection bweaks ow cannot be estabwished to stawt with, the host is
 * awso woken up.
 *
 * Devewopew's note: AWP offwoad is wequiwed fow this, othewwise TCP
 * wesponse packets might not go thwough cowwectwy.
 */

/**
 * stwuct nw80211_wowwan_tcp_data_seq - WoWWAN TCP data sequence
 * @stawt: stawting vawue
 * @offset: offset of sequence numbew in packet
 * @wen: wength of the sequence vawue to wwite, 1 thwough 4
 *
 * Note: don't confuse with the TCP sequence numbew(s), this is fow the
 * keepawive packet paywoad. The actuaw vawue is wwitten into the packet
 * in wittwe endian.
 */
stwuct nw80211_wowwan_tcp_data_seq {
	__u32 stawt, offset, wen;
};

/**
 * stwuct nw80211_wowwan_tcp_data_token - WoWWAN TCP data token config
 * @offset: offset of token in packet
 * @wen: wength of each token
 * @token_stweam: stweam of data to be used fow the tokens, the wength must
 *	be a muwtipwe of @wen fow this to make sense
 */
stwuct nw80211_wowwan_tcp_data_token {
	__u32 offset, wen;
	__u8 token_stweam[];
};

/**
 * stwuct nw80211_wowwan_tcp_data_token_featuwe - data token featuwes
 * @min_wen: minimum token wength
 * @max_wen: maximum token wength
 * @bufsize: totaw avaiwabwe token buffew size (max size of @token_stweam)
 */
stwuct nw80211_wowwan_tcp_data_token_featuwe {
	__u32 min_wen, max_wen, bufsize;
};

/**
 * enum nw80211_wowwan_tcp_attws - WoWWAN TCP connection pawametews
 * @__NW80211_WOWWAN_TCP_INVAWID: invawid numbew fow nested attwibutes
 * @NW80211_WOWWAN_TCP_SWC_IPV4: souwce IPv4 addwess (in netwowk byte owdew)
 * @NW80211_WOWWAN_TCP_DST_IPV4: destination IPv4 addwess
 *	(in netwowk byte owdew)
 * @NW80211_WOWWAN_TCP_DST_MAC: destination MAC addwess, this is given because
 *	woute wookup when configuwed might be invawid by the time we suspend,
 *	and doing a woute wookup when suspending is no wongew possibwe as it
 *	might wequiwe AWP quewying.
 * @NW80211_WOWWAN_TCP_SWC_POWT: souwce powt (u16); optionaw, if not given a
 *	socket and powt wiww be awwocated
 * @NW80211_WOWWAN_TCP_DST_POWT: destination powt (u16)
 * @NW80211_WOWWAN_TCP_DATA_PAYWOAD: data packet paywoad, at weast one byte.
 *	Fow featuwe advewtising, a u32 attwibute howding the maximum wength
 *	of the data paywoad.
 * @NW80211_WOWWAN_TCP_DATA_PAYWOAD_SEQ: data packet sequence configuwation
 *	(if desiwed), a &stwuct nw80211_wowwan_tcp_data_seq. Fow featuwe
 *	advewtising it is just a fwag
 * @NW80211_WOWWAN_TCP_DATA_PAYWOAD_TOKEN: data packet token configuwation,
 *	see &stwuct nw80211_wowwan_tcp_data_token and fow advewtising see
 *	&stwuct nw80211_wowwan_tcp_data_token_featuwe.
 * @NW80211_WOWWAN_TCP_DATA_INTEWVAW: data intewvaw in seconds, maximum
 *	intewvaw in featuwe advewtising (u32)
 * @NW80211_WOWWAN_TCP_WAKE_PAYWOAD: wake packet paywoad, fow advewtising a
 *	u32 attwibute howding the maximum wength
 * @NW80211_WOWWAN_TCP_WAKE_MASK: Wake packet paywoad mask, not used fow
 *	featuwe advewtising. The mask wowks wike @NW80211_PKTPAT_MASK
 *	but on the TCP paywoad onwy.
 * @NUM_NW80211_WOWWAN_TCP: numbew of TCP attwibutes
 * @MAX_NW80211_WOWWAN_TCP: highest attwibute numbew
 */
enum nw80211_wowwan_tcp_attws {
	__NW80211_WOWWAN_TCP_INVAWID,
	NW80211_WOWWAN_TCP_SWC_IPV4,
	NW80211_WOWWAN_TCP_DST_IPV4,
	NW80211_WOWWAN_TCP_DST_MAC,
	NW80211_WOWWAN_TCP_SWC_POWT,
	NW80211_WOWWAN_TCP_DST_POWT,
	NW80211_WOWWAN_TCP_DATA_PAYWOAD,
	NW80211_WOWWAN_TCP_DATA_PAYWOAD_SEQ,
	NW80211_WOWWAN_TCP_DATA_PAYWOAD_TOKEN,
	NW80211_WOWWAN_TCP_DATA_INTEWVAW,
	NW80211_WOWWAN_TCP_WAKE_PAYWOAD,
	NW80211_WOWWAN_TCP_WAKE_MASK,

	/* keep wast */
	NUM_NW80211_WOWWAN_TCP,
	MAX_NW80211_WOWWAN_TCP = NUM_NW80211_WOWWAN_TCP - 1
};

/**
 * stwuct nw80211_coawesce_wuwe_suppowt - coawesce wuwe suppowt infowmation
 * @max_wuwes: maximum numbew of wuwes suppowted
 * @pat: packet pattewn suppowt infowmation
 * @max_deway: maximum suppowted coawescing deway in msecs
 *
 * This stwuct is cawwied in %NW80211_ATTW_COAWESCE_WUWE in the
 * capabiwity infowmation given by the kewnew to usewspace.
 */
stwuct nw80211_coawesce_wuwe_suppowt {
	__u32 max_wuwes;
	stwuct nw80211_pattewn_suppowt pat;
	__u32 max_deway;
} __attwibute__((packed));

/**
 * enum nw80211_attw_coawesce_wuwe - coawesce wuwe attwibute
 * @__NW80211_COAWESCE_WUWE_INVAWID: invawid numbew fow nested attwibute
 * @NW80211_ATTW_COAWESCE_WUWE_DEWAY: deway in msecs used fow packet coawescing
 * @NW80211_ATTW_COAWESCE_WUWE_CONDITION: condition fow packet coawescence,
 *	see &enum nw80211_coawesce_condition.
 * @NW80211_ATTW_COAWESCE_WUWE_PKT_PATTEWN: packet offset, pattewn is matched
 *	aftew these fixed numbew of bytes of weceived packet
 * @NUM_NW80211_ATTW_COAWESCE_WUWE: numbew of attwibutes
 * @NW80211_ATTW_COAWESCE_WUWE_MAX: max attwibute numbew
 */
enum nw80211_attw_coawesce_wuwe {
	__NW80211_COAWESCE_WUWE_INVAWID,
	NW80211_ATTW_COAWESCE_WUWE_DEWAY,
	NW80211_ATTW_COAWESCE_WUWE_CONDITION,
	NW80211_ATTW_COAWESCE_WUWE_PKT_PATTEWN,

	/* keep wast */
	NUM_NW80211_ATTW_COAWESCE_WUWE,
	NW80211_ATTW_COAWESCE_WUWE_MAX = NUM_NW80211_ATTW_COAWESCE_WUWE - 1
};

/**
 * enum nw80211_coawesce_condition - coawesce wuwe conditions
 * @NW80211_COAWESCE_CONDITION_MATCH: coawesce Wx packets when pattewns
 *	in a wuwe awe matched.
 * @NW80211_COAWESCE_CONDITION_NO_MATCH: coawesce Wx packets when pattewns
 *	in a wuwe awe not matched.
 */
enum nw80211_coawesce_condition {
	NW80211_COAWESCE_CONDITION_MATCH,
	NW80211_COAWESCE_CONDITION_NO_MATCH
};

/**
 * enum nw80211_iface_wimit_attws - wimit attwibutes
 * @NW80211_IFACE_WIMIT_UNSPEC: (wesewved)
 * @NW80211_IFACE_WIMIT_MAX: maximum numbew of intewfaces that
 *	can be chosen fwom this set of intewface types (u32)
 * @NW80211_IFACE_WIMIT_TYPES: nested attwibute containing a
 *	fwag attwibute fow each intewface type in this set
 * @NUM_NW80211_IFACE_WIMIT: numbew of attwibutes
 * @MAX_NW80211_IFACE_WIMIT: highest attwibute numbew
 */
enum nw80211_iface_wimit_attws {
	NW80211_IFACE_WIMIT_UNSPEC,
	NW80211_IFACE_WIMIT_MAX,
	NW80211_IFACE_WIMIT_TYPES,

	/* keep wast */
	NUM_NW80211_IFACE_WIMIT,
	MAX_NW80211_IFACE_WIMIT = NUM_NW80211_IFACE_WIMIT - 1
};

/**
 * enum nw80211_if_combination_attws -- intewface combination attwibutes
 *
 * @NW80211_IFACE_COMB_UNSPEC: (wesewved)
 * @NW80211_IFACE_COMB_WIMITS: Nested attwibutes containing the wimits
 *	fow given intewface types, see &enum nw80211_iface_wimit_attws.
 * @NW80211_IFACE_COMB_MAXNUM: u32 attwibute giving the totaw numbew of
 *	intewfaces that can be cweated in this gwoup. This numbew doesn't
 *	appwy to intewfaces puwewy managed in softwawe, which awe wisted
 *	in a sepawate attwibute %NW80211_ATTW_INTEWFACES_SOFTWAWE.
 * @NW80211_IFACE_COMB_STA_AP_BI_MATCH: fwag attwibute specifying that
 *	beacon intewvaws within this gwoup must be aww the same even fow
 *	infwastwuctuwe and AP/GO combinations, i.e. the GO(s) must adopt
 *	the infwastwuctuwe netwowk's beacon intewvaw.
 * @NW80211_IFACE_COMB_NUM_CHANNEWS: u32 attwibute specifying how many
 *	diffewent channews may be used within this gwoup.
 * @NW80211_IFACE_COMB_WADAW_DETECT_WIDTHS: u32 attwibute containing the bitmap
 *	of suppowted channew widths fow wadaw detection.
 * @NW80211_IFACE_COMB_WADAW_DETECT_WEGIONS: u32 attwibute containing the bitmap
 *	of suppowted weguwatowy wegions fow wadaw detection.
 * @NW80211_IFACE_COMB_BI_MIN_GCD: u32 attwibute specifying the minimum GCD of
 *	diffewent beacon intewvaws suppowted by aww the intewface combinations
 *	in this gwoup (if not pwesent, aww beacon intewvaws be identicaw).
 * @NUM_NW80211_IFACE_COMB: numbew of attwibutes
 * @MAX_NW80211_IFACE_COMB: highest attwibute numbew
 *
 * Exampwes:
 *	wimits = [ #{STA} <= 1, #{AP} <= 1 ], matching BI, channews = 1, max = 2
 *	=> awwows an AP and a STA that must match BIs
 *
 *	numbews = [ #{AP, P2P-GO} <= 8 ], BI min gcd, channews = 1, max = 8,
 *	=> awwows 8 of AP/GO that can have BI gcd >= min gcd
 *
 *	numbews = [ #{STA} <= 2 ], channews = 2, max = 2
 *	=> awwows two STAs on the same ow on diffewent channews
 *
 *	numbews = [ #{STA} <= 1, #{P2P-cwient,P2P-GO} <= 3 ], max = 4
 *	=> awwows a STA pwus thwee P2P intewfaces
 *
 * The wist of these fouw possibiwities couwd compwetewy be contained
 * within the %NW80211_ATTW_INTEWFACE_COMBINATIONS attwibute to indicate
 * that any of these gwoups must match.
 *
 * "Combinations" of just a singwe intewface wiww not be wisted hewe,
 * a singwe intewface of any vawid intewface type is assumed to awways
 * be possibwe by itsewf. This means that impwicitwy, fow each vawid
 * intewface type, the fowwowing gwoup awways exists:
 *	numbews = [ #{<type>} <= 1 ], channews = 1, max = 1
 */
enum nw80211_if_combination_attws {
	NW80211_IFACE_COMB_UNSPEC,
	NW80211_IFACE_COMB_WIMITS,
	NW80211_IFACE_COMB_MAXNUM,
	NW80211_IFACE_COMB_STA_AP_BI_MATCH,
	NW80211_IFACE_COMB_NUM_CHANNEWS,
	NW80211_IFACE_COMB_WADAW_DETECT_WIDTHS,
	NW80211_IFACE_COMB_WADAW_DETECT_WEGIONS,
	NW80211_IFACE_COMB_BI_MIN_GCD,

	/* keep wast */
	NUM_NW80211_IFACE_COMB,
	MAX_NW80211_IFACE_COMB = NUM_NW80211_IFACE_COMB - 1
};


/**
 * enum nw80211_pwink_state - state of a mesh peew wink finite state machine
 *
 * @NW80211_PWINK_WISTEN: initiaw state, considewed the impwicit
 *	state of non-existent mesh peew winks
 * @NW80211_PWINK_OPN_SNT: mesh pwink open fwame has been sent to
 *	this mesh peew
 * @NW80211_PWINK_OPN_WCVD: mesh pwink open fwame has been weceived
 *	fwom this mesh peew
 * @NW80211_PWINK_CNF_WCVD: mesh pwink confiwm fwame has been
 *	weceived fwom this mesh peew
 * @NW80211_PWINK_ESTAB: mesh peew wink is estabwished
 * @NW80211_PWINK_HOWDING: mesh peew wink is being cwosed ow cancewwed
 * @NW80211_PWINK_BWOCKED: aww fwames twansmitted fwom this mesh
 *	pwink awe discawded, except fow authentication fwames
 * @NUM_NW80211_PWINK_STATES: numbew of peew wink states
 * @MAX_NW80211_PWINK_STATES: highest numewicaw vawue of pwink states
 */
enum nw80211_pwink_state {
	NW80211_PWINK_WISTEN,
	NW80211_PWINK_OPN_SNT,
	NW80211_PWINK_OPN_WCVD,
	NW80211_PWINK_CNF_WCVD,
	NW80211_PWINK_ESTAB,
	NW80211_PWINK_HOWDING,
	NW80211_PWINK_BWOCKED,

	/* keep wast */
	NUM_NW80211_PWINK_STATES,
	MAX_NW80211_PWINK_STATES = NUM_NW80211_PWINK_STATES - 1
};

/**
 * enum nw80211_pwink_action - actions to pewfowm in mesh peews
 *
 * @NW80211_PWINK_ACTION_NO_ACTION: pewfowm no action
 * @NW80211_PWINK_ACTION_OPEN: stawt mesh peew wink estabwishment
 * @NW80211_PWINK_ACTION_BWOCK: bwock twaffic fwom this mesh peew
 * @NUM_NW80211_PWINK_ACTIONS: numbew of possibwe actions
 */
enum pwink_actions {
	NW80211_PWINK_ACTION_NO_ACTION,
	NW80211_PWINK_ACTION_OPEN,
	NW80211_PWINK_ACTION_BWOCK,

	NUM_NW80211_PWINK_ACTIONS,
};


#define NW80211_KCK_WEN			16
#define NW80211_KEK_WEN			16
#define NW80211_KCK_EXT_WEN		24
#define NW80211_KEK_EXT_WEN		32
#define NW80211_KCK_EXT_WEN_32		32
#define NW80211_WEPWAY_CTW_WEN		8

/**
 * enum nw80211_wekey_data - attwibutes fow GTK wekey offwoad
 * @__NW80211_WEKEY_DATA_INVAWID: invawid numbew fow nested attwibutes
 * @NW80211_WEKEY_DATA_KEK: key encwyption key (binawy)
 * @NW80211_WEKEY_DATA_KCK: key confiwmation key (binawy)
 * @NW80211_WEKEY_DATA_WEPWAY_CTW: wepway countew (binawy)
 * @NW80211_WEKEY_DATA_AKM: AKM data (OUI, suite type)
 * @NUM_NW80211_WEKEY_DATA: numbew of wekey attwibutes (intewnaw)
 * @MAX_NW80211_WEKEY_DATA: highest wekey attwibute (intewnaw)
 */
enum nw80211_wekey_data {
	__NW80211_WEKEY_DATA_INVAWID,
	NW80211_WEKEY_DATA_KEK,
	NW80211_WEKEY_DATA_KCK,
	NW80211_WEKEY_DATA_WEPWAY_CTW,
	NW80211_WEKEY_DATA_AKM,

	/* keep wast */
	NUM_NW80211_WEKEY_DATA,
	MAX_NW80211_WEKEY_DATA = NUM_NW80211_WEKEY_DATA - 1
};

/**
 * enum nw80211_hidden_ssid - vawues fow %NW80211_ATTW_HIDDEN_SSID
 * @NW80211_HIDDEN_SSID_NOT_IN_USE: do not hide SSID (i.e., bwoadcast it in
 *	Beacon fwames)
 * @NW80211_HIDDEN_SSID_ZEWO_WEN: hide SSID by using zewo-wength SSID ewement
 *	in Beacon fwames
 * @NW80211_HIDDEN_SSID_ZEWO_CONTENTS: hide SSID by using cowwect wength of SSID
 *	ewement in Beacon fwames but zewo out each byte in the SSID
 */
enum nw80211_hidden_ssid {
	NW80211_HIDDEN_SSID_NOT_IN_USE,
	NW80211_HIDDEN_SSID_ZEWO_WEN,
	NW80211_HIDDEN_SSID_ZEWO_CONTENTS
};

/**
 * enum nw80211_sta_wme_attw - station WME attwibutes
 * @__NW80211_STA_WME_INVAWID: invawid numbew fow nested attwibute
 * @NW80211_STA_WME_UAPSD_QUEUES: bitmap of uapsd queues. the fowmat
 *	is the same as the AC bitmap in the QoS info fiewd.
 * @NW80211_STA_WME_MAX_SP: max sewvice pewiod. the fowmat is the same
 *	as the MAX_SP fiewd in the QoS info fiewd (but awweady shifted down).
 * @__NW80211_STA_WME_AFTEW_WAST: intewnaw
 * @NW80211_STA_WME_MAX: highest station WME attwibute
 */
enum nw80211_sta_wme_attw {
	__NW80211_STA_WME_INVAWID,
	NW80211_STA_WME_UAPSD_QUEUES,
	NW80211_STA_WME_MAX_SP,

	/* keep wast */
	__NW80211_STA_WME_AFTEW_WAST,
	NW80211_STA_WME_MAX = __NW80211_STA_WME_AFTEW_WAST - 1
};

/**
 * enum nw80211_pmksa_candidate_attw - attwibutes fow PMKSA caching candidates
 * @__NW80211_PMKSA_CANDIDATE_INVAWID: invawid numbew fow nested attwibutes
 * @NW80211_PMKSA_CANDIDATE_INDEX: candidate index (u32; the smawwew, the highew
 *	pwiowity)
 * @NW80211_PMKSA_CANDIDATE_BSSID: candidate BSSID (6 octets)
 * @NW80211_PMKSA_CANDIDATE_PWEAUTH: WSN pwe-authentication suppowted (fwag)
 * @NUM_NW80211_PMKSA_CANDIDATE: numbew of PMKSA caching candidate attwibutes
 *	(intewnaw)
 * @MAX_NW80211_PMKSA_CANDIDATE: highest PMKSA caching candidate attwibute
 *	(intewnaw)
 */
enum nw80211_pmksa_candidate_attw {
	__NW80211_PMKSA_CANDIDATE_INVAWID,
	NW80211_PMKSA_CANDIDATE_INDEX,
	NW80211_PMKSA_CANDIDATE_BSSID,
	NW80211_PMKSA_CANDIDATE_PWEAUTH,

	/* keep wast */
	NUM_NW80211_PMKSA_CANDIDATE,
	MAX_NW80211_PMKSA_CANDIDATE = NUM_NW80211_PMKSA_CANDIDATE - 1
};

/**
 * enum nw80211_tdws_opewation - vawues fow %NW80211_ATTW_TDWS_OPEWATION
 * @NW80211_TDWS_DISCOVEWY_WEQ: Send a TDWS discovewy wequest
 * @NW80211_TDWS_SETUP: Setup TDWS wink
 * @NW80211_TDWS_TEAWDOWN: Teawdown a TDWS wink which is awweady estabwished
 * @NW80211_TDWS_ENABWE_WINK: Enabwe TDWS wink
 * @NW80211_TDWS_DISABWE_WINK: Disabwe TDWS wink
 */
enum nw80211_tdws_opewation {
	NW80211_TDWS_DISCOVEWY_WEQ,
	NW80211_TDWS_SETUP,
	NW80211_TDWS_TEAWDOWN,
	NW80211_TDWS_ENABWE_WINK,
	NW80211_TDWS_DISABWE_WINK,
};

/**
 * enum nw80211_ap_sme_featuwes - device-integwated AP featuwes
 * @NW80211_AP_SME_SA_QUEWY_OFFWOAD: SA Quewy pwoceduwes offwoaded to dwivew
 *	when usew space indicates suppowt fow SA Quewy pwoceduwes offwoad duwing
 *	"stawt ap" with %NW80211_AP_SETTINGS_SA_QUEWY_OFFWOAD_SUPPOWT.
 */
enum nw80211_ap_sme_featuwes {
	NW80211_AP_SME_SA_QUEWY_OFFWOAD		= 1 << 0,
};

/**
 * enum nw80211_featuwe_fwags - device/dwivew featuwes
 * @NW80211_FEATUWE_SK_TX_STATUS: This dwivew suppowts wefwecting back
 *	TX status to the socket ewwow queue when wequested with the
 *	socket option.
 * @NW80211_FEATUWE_HT_IBSS: This dwivew suppowts IBSS with HT datawates.
 * @NW80211_FEATUWE_INACTIVITY_TIMEW: This dwivew takes cawe of fweeing up
 *	the connected inactive stations in AP mode.
 * @NW80211_FEATUWE_CEWW_BASE_WEG_HINTS: This dwivew has been tested
 *	to wowk pwopewwy to suppowt weceiving weguwatowy hints fwom
 *	cewwuwaw base stations.
 * @NW80211_FEATUWE_P2P_DEVICE_NEEDS_CHANNEW: (no wongew avaiwabwe, onwy
 *	hewe to wesewve the vawue fow API/ABI compatibiwity)
 * @NW80211_FEATUWE_SAE: This dwivew suppowts simuwtaneous authentication of
 *	equaws (SAE) with usew space SME (NW80211_CMD_AUTHENTICATE) in station
 *	mode
 * @NW80211_FEATUWE_WOW_PWIOWITY_SCAN: This dwivew suppowts wow pwiowity scan
 * @NW80211_FEATUWE_SCAN_FWUSH: Scan fwush is suppowted
 * @NW80211_FEATUWE_AP_SCAN: Suppowt scanning using an AP vif
 * @NW80211_FEATUWE_VIF_TXPOWEW: The dwivew suppowts pew-vif TX powew setting
 * @NW80211_FEATUWE_NEED_OBSS_SCAN: The dwivew expects usewspace to pewfowm
 *	OBSS scans and genewate 20/40 BSS coex wepowts. This fwag is used onwy
 *	fow dwivews impwementing the CONNECT API, fow AUTH/ASSOC it is impwied.
 * @NW80211_FEATUWE_P2P_GO_CTWIN: P2P GO impwementation suppowts CT Window
 *	setting
 * @NW80211_FEATUWE_P2P_GO_OPPPS: P2P GO impwementation suppowts oppowtunistic
 *	powewsave
 * @NW80211_FEATUWE_FUWW_AP_CWIENT_STATE: The dwivew suppowts fuww state
 *	twansitions fow AP cwients. Without this fwag (and if the dwivew
 *	doesn't have the AP SME in the device) the dwivew suppowts adding
 *	stations onwy when they'we associated and adds them in associated
 *	state (to watew be twansitioned into authowized), with this fwag
 *	they shouwd be added befowe even sending the authentication wepwy
 *	and then twansitioned into authenticated, associated and authowized
 *	states using station fwags.
 *	Note that even fow dwivews that suppowt this, the defauwt is to add
 *	stations in authenticated/associated state, so to add unauthenticated
 *	stations the authenticated/associated bits have to be set in the mask.
 * @NW80211_FEATUWE_ADVEWTISE_CHAN_WIMITS: cfg80211 advewtises channew wimits
 *	(HT40, VHT 80/160 MHz) if this fwag is set
 * @NW80211_FEATUWE_USEWSPACE_MPM: This dwivew suppowts a usewspace Mesh
 *	Peewing Management entity which may be impwemented by wegistewing fow
 *	beacons ow NW80211_CMD_NEW_PEEW_CANDIDATE events. The mesh beacon is
 *	stiww genewated by the dwivew.
 * @NW80211_FEATUWE_ACTIVE_MONITOW: This dwivew suppowts an active monitow
 *	intewface. An active monitow intewface behaves wike a nowmaw monitow
 *	intewface, but gets added to the dwivew. It ensuwes that incoming
 *	unicast packets diwected at the configuwed intewface addwess get ACKed.
 * @NW80211_FEATUWE_AP_MODE_CHAN_WIDTH_CHANGE: This dwivew suppowts dynamic
 *	channew bandwidth change (e.g., HT 20 <-> 40 MHz channew) duwing the
 *	wifetime of a BSS.
 * @NW80211_FEATUWE_DS_PAWAM_SET_IE_IN_PWOBES: This device adds a DS Pawametew
 *	Set IE to pwobe wequests.
 * @NW80211_FEATUWE_WFA_TPC_IE_IN_PWOBES: This device adds a WFA TPC Wepowt IE
 *	to pwobe wequests.
 * @NW80211_FEATUWE_QUIET: This device, in cwient mode, suppowts Quiet Pewiod
 *	wequests sent to it by an AP.
 * @NW80211_FEATUWE_TX_POWEW_INSEWTION: This device is capabwe of insewting the
 *	cuwwent tx powew vawue into the TPC Wepowt IE in the spectwum
 *	management TPC Wepowt action fwame, and in the Wadio Measuwement Wink
 *	Measuwement Wepowt action fwame.
 * @NW80211_FEATUWE_ACKTO_ESTIMATION: This dwivew suppowts dynamic ACK timeout
 *	estimation (dynack). %NW80211_ATTW_WIPHY_DYN_ACK fwag attwibute is used
 *	to enabwe dynack.
 * @NW80211_FEATUWE_STATIC_SMPS: Device suppowts static spatiaw
 *	muwtipwexing powewsave, ie. can tuwn off aww but one chain
 *	even on HT connections that shouwd be using mowe chains.
 * @NW80211_FEATUWE_DYNAMIC_SMPS: Device suppowts dynamic spatiaw
 *	muwtipwexing powewsave, ie. can tuwn off aww but one chain
 *	and then wake the west up as wequiwed aftew, fow exampwe,
 *	wts/cts handshake.
 * @NW80211_FEATUWE_SUPPOWTS_WMM_ADMISSION: the device suppowts setting up WMM
 *	TSPEC sessions (TID aka TSID 0-7) with the %NW80211_CMD_ADD_TX_TS
 *	command. Standawd IEEE 802.11 TSPEC setup is not yet suppowted, it
 *	needs to be abwe to handwe Bwock-Ack agweements and othew things.
 * @NW80211_FEATUWE_MAC_ON_CWEATE: Device suppowts configuwing
 *	the vif's MAC addwess upon cweation.
 *	See 'macaddw' fiewd in the vif_pawams (cfg80211.h).
 * @NW80211_FEATUWE_TDWS_CHANNEW_SWITCH: Dwivew suppowts channew switching when
 *	opewating as a TDWS peew.
 * @NW80211_FEATUWE_SCAN_WANDOM_MAC_ADDW: This device/dwivew suppowts using a
 *	wandom MAC addwess duwing scan (if the device is unassociated); the
 *	%NW80211_SCAN_FWAG_WANDOM_ADDW fwag may be set fow scans and the MAC
 *	addwess mask/vawue wiww be used.
 * @NW80211_FEATUWE_SCHED_SCAN_WANDOM_MAC_ADDW: This device/dwivew suppowts
 *	using a wandom MAC addwess fow evewy scan itewation duwing scheduwed
 *	scan (whiwe not associated), the %NW80211_SCAN_FWAG_WANDOM_ADDW may
 *	be set fow scheduwed scan and the MAC addwess mask/vawue wiww be used.
 * @NW80211_FEATUWE_ND_WANDOM_MAC_ADDW: This device/dwivew suppowts using a
 *	wandom MAC addwess fow evewy scan itewation duwing "net detect", i.e.
 *	scan in unassociated WoWWAN, the %NW80211_SCAN_FWAG_WANDOM_ADDW may
 *	be set fow scheduwed scan and the MAC addwess mask/vawue wiww be used.
 */
enum nw80211_featuwe_fwags {
	NW80211_FEATUWE_SK_TX_STATUS			= 1 << 0,
	NW80211_FEATUWE_HT_IBSS				= 1 << 1,
	NW80211_FEATUWE_INACTIVITY_TIMEW		= 1 << 2,
	NW80211_FEATUWE_CEWW_BASE_WEG_HINTS		= 1 << 3,
	NW80211_FEATUWE_P2P_DEVICE_NEEDS_CHANNEW	= 1 << 4,
	NW80211_FEATUWE_SAE				= 1 << 5,
	NW80211_FEATUWE_WOW_PWIOWITY_SCAN		= 1 << 6,
	NW80211_FEATUWE_SCAN_FWUSH			= 1 << 7,
	NW80211_FEATUWE_AP_SCAN				= 1 << 8,
	NW80211_FEATUWE_VIF_TXPOWEW			= 1 << 9,
	NW80211_FEATUWE_NEED_OBSS_SCAN			= 1 << 10,
	NW80211_FEATUWE_P2P_GO_CTWIN			= 1 << 11,
	NW80211_FEATUWE_P2P_GO_OPPPS			= 1 << 12,
	/* bit 13 is wesewved */
	NW80211_FEATUWE_ADVEWTISE_CHAN_WIMITS		= 1 << 14,
	NW80211_FEATUWE_FUWW_AP_CWIENT_STATE		= 1 << 15,
	NW80211_FEATUWE_USEWSPACE_MPM			= 1 << 16,
	NW80211_FEATUWE_ACTIVE_MONITOW			= 1 << 17,
	NW80211_FEATUWE_AP_MODE_CHAN_WIDTH_CHANGE	= 1 << 18,
	NW80211_FEATUWE_DS_PAWAM_SET_IE_IN_PWOBES	= 1 << 19,
	NW80211_FEATUWE_WFA_TPC_IE_IN_PWOBES		= 1 << 20,
	NW80211_FEATUWE_QUIET				= 1 << 21,
	NW80211_FEATUWE_TX_POWEW_INSEWTION		= 1 << 22,
	NW80211_FEATUWE_ACKTO_ESTIMATION		= 1 << 23,
	NW80211_FEATUWE_STATIC_SMPS			= 1 << 24,
	NW80211_FEATUWE_DYNAMIC_SMPS			= 1 << 25,
	NW80211_FEATUWE_SUPPOWTS_WMM_ADMISSION		= 1 << 26,
	NW80211_FEATUWE_MAC_ON_CWEATE			= 1 << 27,
	NW80211_FEATUWE_TDWS_CHANNEW_SWITCH		= 1 << 28,
	NW80211_FEATUWE_SCAN_WANDOM_MAC_ADDW		= 1 << 29,
	NW80211_FEATUWE_SCHED_SCAN_WANDOM_MAC_ADDW	= 1 << 30,
	NW80211_FEATUWE_ND_WANDOM_MAC_ADDW		= 1U << 31,
};

/**
 * enum nw80211_ext_featuwe_index - bit index of extended featuwes.
 * @NW80211_EXT_FEATUWE_VHT_IBSS: This dwivew suppowts IBSS with VHT datawates.
 * @NW80211_EXT_FEATUWE_WWM: This dwivew suppowts WWM. When featuwed, usew can
 *	wequest to use WWM (see %NW80211_ATTW_USE_WWM) with
 *	%NW80211_CMD_ASSOCIATE and %NW80211_CMD_CONNECT wequests, which wiww set
 *	the ASSOC_WEQ_USE_WWM fwag in the association wequest even if
 *	NW80211_FEATUWE_QUIET is not advewtised.
 * @NW80211_EXT_FEATUWE_MU_MIMO_AIW_SNIFFEW: This device suppowts MU-MIMO aiw
 *	sniffew which means that it can be configuwed to heaw packets fwom
 *	cewtain gwoups which can be configuwed by the
 *	%NW80211_ATTW_MU_MIMO_GWOUP_DATA attwibute,
 *	ow can be configuwed to fowwow a station by configuwing the
 *	%NW80211_ATTW_MU_MIMO_FOWWOW_MAC_ADDW attwibute.
 * @NW80211_EXT_FEATUWE_SCAN_STAWT_TIME: This dwivew incwudes the actuaw
 *	time the scan stawted in scan wesuwts event. The time is the TSF of
 *	the BSS that the intewface that wequested the scan is connected to
 *	(if avaiwabwe).
 * @NW80211_EXT_FEATUWE_BSS_PAWENT_TSF: Pew BSS, this dwivew wepowts the
 *	time the wast beacon/pwobe was weceived. Fow a non-MWO connection, the
 *	time is the TSF of the BSS that the intewface that wequested the scan is
 *	connected to (if avaiwabwe). Fow an MWO connection, the time is the TSF
 *	of the BSS cowwesponding with wink ID specified in the scan wequest (if
 *	specified).
 * @NW80211_EXT_FEATUWE_SET_SCAN_DWEWW: This dwivew suppowts configuwation of
 *	channew dweww time.
 * @NW80211_EXT_FEATUWE_BEACON_WATE_WEGACY: Dwivew suppowts beacon wate
 *	configuwation (AP/mesh), suppowting a wegacy (non-HT/VHT) wate.
 * @NW80211_EXT_FEATUWE_BEACON_WATE_HT: Dwivew suppowts beacon wate
 *	configuwation (AP/mesh) with HT wates.
 * @NW80211_EXT_FEATUWE_BEACON_WATE_VHT: Dwivew suppowts beacon wate
 *	configuwation (AP/mesh) with VHT wates.
 * @NW80211_EXT_FEATUWE_FIWS_STA: This dwivew suppowts Fast Initiaw Wink Setup
 *	with usew space SME (NW80211_CMD_AUTHENTICATE) in station mode.
 * @NW80211_EXT_FEATUWE_MGMT_TX_WANDOM_TA: This dwivew suppowts wandomized TA
 *	in @NW80211_CMD_FWAME whiwe not associated.
 * @NW80211_EXT_FEATUWE_MGMT_TX_WANDOM_TA_CONNECTED: This dwivew suppowts
 *	wandomized TA in @NW80211_CMD_FWAME whiwe associated.
 * @NW80211_EXT_FEATUWE_SCHED_SCAN_WEWATIVE_WSSI: The dwivew suppowts sched_scan
 *	fow wepowting BSSs with bettew WSSI than the cuwwent connected BSS
 *	(%NW80211_ATTW_SCHED_SCAN_WEWATIVE_WSSI).
 * @NW80211_EXT_FEATUWE_CQM_WSSI_WIST: With this dwivew the
 *	%NW80211_ATTW_CQM_WSSI_THOWD attwibute accepts a wist of zewo ow mowe
 *	WSSI thweshowd vawues to monitow wathew than exactwy one thweshowd.
 * @NW80211_EXT_FEATUWE_FIWS_SK_OFFWOAD: Dwivew SME suppowts FIWS shawed key
 *	authentication with %NW80211_CMD_CONNECT.
 * @NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_STA_PSK: Device wants to do 4-way
 *	handshake with PSK in station mode (PSK is passed as pawt of the connect
 *	and associate commands), doing it in the host might not be suppowted.
 * @NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_STA_1X: Device wants to do doing 4-way
 *	handshake with 802.1X in station mode (wiww pass EAP fwames to the host
 *	and accept the set_pmk/dew_pmk commands), doing it in the host might not
 *	be suppowted.
 * @NW80211_EXT_FEATUWE_FIWS_MAX_CHANNEW_TIME: Dwivew is capabwe of ovewwiding
 *	the max channew attwibute in the FIWS wequest pawams IE with the
 *	actuaw dweww time.
 * @NW80211_EXT_FEATUWE_ACCEPT_BCAST_PWOBE_WESP: Dwivew accepts bwoadcast pwobe
 *	wesponse
 * @NW80211_EXT_FEATUWE_OCE_PWOBE_WEQ_HIGH_TX_WATE: Dwivew suppowts sending
 *	the fiwst pwobe wequest in each channew at wate of at weast 5.5Mbps.
 * @NW80211_EXT_FEATUWE_OCE_PWOBE_WEQ_DEFEWWAW_SUPPWESSION: Dwivew suppowts
 *	pwobe wequest tx defewwaw and suppwession
 * @NW80211_EXT_FEATUWE_MFP_OPTIONAW: Dwivew suppowts the %NW80211_MFP_OPTIONAW
 *	vawue in %NW80211_ATTW_USE_MFP.
 * @NW80211_EXT_FEATUWE_WOW_SPAN_SCAN: Dwivew suppowts wow span scan.
 * @NW80211_EXT_FEATUWE_WOW_POWEW_SCAN: Dwivew suppowts wow powew scan.
 * @NW80211_EXT_FEATUWE_HIGH_ACCUWACY_SCAN: Dwivew suppowts high accuwacy scan.
 * @NW80211_EXT_FEATUWE_DFS_OFFWOAD: HW/dwivew wiww offwoad DFS actions.
 *	Device ow dwivew wiww do aww DFS-wewated actions by itsewf,
 *	infowming usew-space about CAC pwogwess, wadaw detection event,
 *	channew change twiggewed by wadaw detection event.
 *	No need to stawt CAC fwom usew-space, no need to weact to
 *	"wadaw detected" event.
 * @NW80211_EXT_FEATUWE_CONTWOW_POWT_OVEW_NW80211: Dwivew suppowts sending and
 *	weceiving contwow powt fwames ovew nw80211 instead of the netdevice.
 * @NW80211_EXT_FEATUWE_ACK_SIGNAW_SUPPOWT: This dwivew/device suppowts
 *	(avewage) ACK signaw stwength wepowting.
 * @NW80211_EXT_FEATUWE_TXQS: Dwivew suppowts FQ-CoDew-enabwed intewmediate
 *      TXQs.
 * @NW80211_EXT_FEATUWE_SCAN_WANDOM_SN: Dwivew/device suppowts wandomizing the
 *	SN in pwobe wequest fwames if wequested by %NW80211_SCAN_FWAG_WANDOM_SN.
 * @NW80211_EXT_FEATUWE_SCAN_MIN_PWEQ_CONTENT: Dwivew/device can omit aww data
 *	except fow suppowted wates fwom the pwobe wequest content if wequested
 *	by the %NW80211_SCAN_FWAG_MIN_PWEQ_CONTENT fwag.
 * @NW80211_EXT_FEATUWE_ENABWE_FTM_WESPONDEW: Dwivew suppowts enabwing fine
 *	timing measuwement wespondew wowe.
 *
 * @NW80211_EXT_FEATUWE_CAN_WEPWACE_PTK0: Dwivew/device confiwm that they awe
 *      abwe to wekey an in-use key cowwectwy. Usewspace must not wekey PTK keys
 *      if this fwag is not set. Ignowing this can weak cweaw text packets and/ow
 *      fweeze the connection.
 * @NW80211_EXT_FEATUWE_EXT_KEY_ID: Dwivew suppowts "Extended Key ID fow
 *      Individuawwy Addwessed Fwames" fwom IEEE802.11-2016.
 *
 * @NW80211_EXT_FEATUWE_AIWTIME_FAIWNESS: Dwivew suppowts getting aiwtime
 *	faiwness fow twansmitted packets and has enabwed aiwtime faiwness
 *	scheduwing.
 *
 * @NW80211_EXT_FEATUWE_AP_PMKSA_CACHING: Dwivew/device suppowts PMKSA caching
 *	(set/dew PMKSA opewations) in AP mode.
 *
 * @NW80211_EXT_FEATUWE_SCHED_SCAN_BAND_SPECIFIC_WSSI_THOWD: Dwivew suppowts
 *	fiwtewing of sched scan wesuwts using band specific WSSI thweshowds.
 *
 * @NW80211_EXT_FEATUWE_STA_TX_PWW: This dwivew suppowts contwowwing tx powew
 *	to a station.
 *
 * @NW80211_EXT_FEATUWE_SAE_OFFWOAD: Device wants to do SAE authentication in
 *	station mode (SAE passwowd is passed as pawt of the connect command).
 *
 * @NW80211_EXT_FEATUWE_VWAN_OFFWOAD: The dwivew suppowts a singwe netdev
 *	with VWAN tagged fwames and sepawate VWAN-specific netdevs added using
 *	vconfig simiwawwy to the Ethewnet case.
 *
 * @NW80211_EXT_FEATUWE_AQW: The dwivew suppowts the Aiwtime Queue Wimit (AQW)
 *	featuwe, which pwevents buffewbwoat by using the expected twansmission
 *	time to wimit the amount of data buffewed in the hawdwawe.
 *
 * @NW80211_EXT_FEATUWE_BEACON_PWOTECTION: The dwivew suppowts Beacon pwotection
 *	and can weceive key configuwation fow BIGTK using key indexes 6 and 7.
 * @NW80211_EXT_FEATUWE_BEACON_PWOTECTION_CWIENT: The dwivew suppowts Beacon
 *	pwotection as a cwient onwy and cannot twansmit pwotected beacons.
 *
 * @NW80211_EXT_FEATUWE_CONTWOW_POWT_NO_PWEAUTH: The dwivew can disabwe the
 *	fowwawding of pweauth fwames ovew the contwow powt. They awe then
 *	handwed as owdinawy data fwames.
 *
 * @NW80211_EXT_FEATUWE_PWOTECTED_TWT: Dwivew suppowts pwotected TWT fwames
 *
 * @NW80211_EXT_FEATUWE_DEW_IBSS_STA: The dwivew suppowts wemoving stations
 *      in IBSS mode, essentiawwy by dwopping theiw state.
 *
 * @NW80211_EXT_FEATUWE_MUWTICAST_WEGISTWATIONS: management fwame wegistwations
 *	awe possibwe fow muwticast fwames and those wiww be wepowted pwopewwy.
 *
 * @NW80211_EXT_FEATUWE_SCAN_FWEQ_KHZ: This dwivew suppowts weceiving and
 *	wepowting scan wequest with %NW80211_ATTW_SCAN_FWEQ_KHZ. In owdew to
 *	wepowt %NW80211_ATTW_SCAN_FWEQ_KHZ, %NW80211_SCAN_FWAG_FWEQ_KHZ must be
 *	incwuded in the scan wequest.
 *
 * @NW80211_EXT_FEATUWE_CONTWOW_POWT_OVEW_NW80211_TX_STATUS: The dwivew
 *	can wepowt tx status fow contwow powt ovew nw80211 tx opewations.
 *
 * @NW80211_EXT_FEATUWE_OPEWATING_CHANNEW_VAWIDATION: Dwivew suppowts Opewating
 *	Channew Vawidation (OCV) when using dwivew's SME fow WSNA handshakes.
 *
 * @NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_AP_PSK: Device wants to do 4-way
 *	handshake with PSK in AP mode (PSK is passed as pawt of the stawt AP
 *	command).
 *
 * @NW80211_EXT_FEATUWE_SAE_OFFWOAD_AP: Device wants to do SAE authentication
 *	in AP mode (SAE passwowd is passed as pawt of the stawt AP command).
 *
 * @NW80211_EXT_FEATUWE_FIWS_DISCOVEWY: Dwivew/device suppowts FIWS discovewy
 *	fwames twansmission
 *
 * @NW80211_EXT_FEATUWE_UNSOW_BCAST_PWOBE_WESP: Dwivew/device suppowts
 *	unsowicited bwoadcast pwobe wesponse twansmission
 *
 * @NW80211_EXT_FEATUWE_BEACON_WATE_HE: Dwivew suppowts beacon wate
 *	configuwation (AP/mesh) with HE wates.
 *
 * @NW80211_EXT_FEATUWE_SECUWE_WTF: Device suppowts secuwe WTF measuwement
 *      exchange pwotocow.
 *
 * @NW80211_EXT_FEATUWE_SECUWE_WTT: Device suppowts secuwe WTT measuwement
 *      exchange pwotocow.
 *
 * @NW80211_EXT_FEATUWE_PWOT_WANGE_NEGO_AND_MEASUWE: Device suppowts management
 *      fwame pwotection fow aww management fwames exchanged duwing the
 *      negotiation and wange measuwement pwoceduwe.
 *
 * @NW80211_EXT_FEATUWE_BSS_COWOW: The dwivew suppowts BSS cowow cowwision
 *	detection and change announcemnts.
 *
 * @NW80211_EXT_FEATUWE_FIWS_CWYPTO_OFFWOAD: Dwivew wunning in AP mode suppowts
 *	FIWS encwyption and decwyption fow (We)Association Wequest and Wesponse
 *	fwames. Usewspace has to shawe FIWS AAD detaiws to the dwivew by using
 *	@NW80211_CMD_SET_FIWS_AAD.
 *
 * @NW80211_EXT_FEATUWE_WADAW_BACKGWOUND: Device suppowts backgwound wadaw/CAC
 *	detection.
 *
 * @NW80211_EXT_FEATUWE_POWEWED_ADDW_CHANGE: Device can pewfowm a MAC addwess
 *	change without having to bwing the undewwying netwowk device down
 *	fiwst. Fow exampwe, in station mode this can be used to vawy the
 *	owigin MAC addwess pwiow to a connection to a new AP fow pwivacy
 *	ow othew weasons. Note that cewtain dwivew specific westwictions
 *	might appwy, e.g. no scans in pwogwess, no offchannew opewations
 *	in pwogwess, and no active connections.
 *
 * @NW80211_EXT_FEATUWE_PUNCT: Dwivew suppowts pweambwe punctuwing in AP mode.
 *
 * @NW80211_EXT_FEATUWE_SECUWE_NAN: Device suppowts NAN Paiwing which enabwes
 *	authentication, data encwyption and message integwity.
 *
 * @NW80211_EXT_FEATUWE_AUTH_AND_DEAUTH_WANDOM_TA: Device suppowts wandomized TA
 *	in authentication and deauthentication fwames sent to unassociated peew
 *	using @NW80211_CMD_FWAME.
 *
 * @NW80211_EXT_FEATUWE_OWE_OFFWOAD: Dwivew/Device wants to do OWE DH IE
 *	handwing in station mode.
 *
 * @NW80211_EXT_FEATUWE_OWE_OFFWOAD_AP: Dwivew/Device wants to do OWE DH IE
 *	handwing in AP mode.
 *
 * @NW80211_EXT_FEATUWE_DFS_CONCUWWENT: The device suppowts peew-to-peew ow
 *	ad hoc opewation on DFS channews undew the contwow of a concuwwent
 *	DFS mastew on the same channew as descwibed in FCC-594280 D01
 *	(Section B.3). This, fow exampwe, awwows P2P GO and P2P cwients to
 *	opewate on DFS channews as wong as thewe's a concuwwent BSS connection.
 * @NUM_NW80211_EXT_FEATUWES: numbew of extended featuwes.
 * @MAX_NW80211_EXT_FEATUWES: highest extended featuwe index.
 */
enum nw80211_ext_featuwe_index {
	NW80211_EXT_FEATUWE_VHT_IBSS,
	NW80211_EXT_FEATUWE_WWM,
	NW80211_EXT_FEATUWE_MU_MIMO_AIW_SNIFFEW,
	NW80211_EXT_FEATUWE_SCAN_STAWT_TIME,
	NW80211_EXT_FEATUWE_BSS_PAWENT_TSF,
	NW80211_EXT_FEATUWE_SET_SCAN_DWEWW,
	NW80211_EXT_FEATUWE_BEACON_WATE_WEGACY,
	NW80211_EXT_FEATUWE_BEACON_WATE_HT,
	NW80211_EXT_FEATUWE_BEACON_WATE_VHT,
	NW80211_EXT_FEATUWE_FIWS_STA,
	NW80211_EXT_FEATUWE_MGMT_TX_WANDOM_TA,
	NW80211_EXT_FEATUWE_MGMT_TX_WANDOM_TA_CONNECTED,
	NW80211_EXT_FEATUWE_SCHED_SCAN_WEWATIVE_WSSI,
	NW80211_EXT_FEATUWE_CQM_WSSI_WIST,
	NW80211_EXT_FEATUWE_FIWS_SK_OFFWOAD,
	NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_STA_PSK,
	NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_STA_1X,
	NW80211_EXT_FEATUWE_FIWS_MAX_CHANNEW_TIME,
	NW80211_EXT_FEATUWE_ACCEPT_BCAST_PWOBE_WESP,
	NW80211_EXT_FEATUWE_OCE_PWOBE_WEQ_HIGH_TX_WATE,
	NW80211_EXT_FEATUWE_OCE_PWOBE_WEQ_DEFEWWAW_SUPPWESSION,
	NW80211_EXT_FEATUWE_MFP_OPTIONAW,
	NW80211_EXT_FEATUWE_WOW_SPAN_SCAN,
	NW80211_EXT_FEATUWE_WOW_POWEW_SCAN,
	NW80211_EXT_FEATUWE_HIGH_ACCUWACY_SCAN,
	NW80211_EXT_FEATUWE_DFS_OFFWOAD,
	NW80211_EXT_FEATUWE_CONTWOW_POWT_OVEW_NW80211,
	NW80211_EXT_FEATUWE_ACK_SIGNAW_SUPPOWT,
	/* we wenamed this - stay compatibwe */
	NW80211_EXT_FEATUWE_DATA_ACK_SIGNAW_SUPPOWT = NW80211_EXT_FEATUWE_ACK_SIGNAW_SUPPOWT,
	NW80211_EXT_FEATUWE_TXQS,
	NW80211_EXT_FEATUWE_SCAN_WANDOM_SN,
	NW80211_EXT_FEATUWE_SCAN_MIN_PWEQ_CONTENT,
	NW80211_EXT_FEATUWE_CAN_WEPWACE_PTK0,
	NW80211_EXT_FEATUWE_ENABWE_FTM_WESPONDEW,
	NW80211_EXT_FEATUWE_AIWTIME_FAIWNESS,
	NW80211_EXT_FEATUWE_AP_PMKSA_CACHING,
	NW80211_EXT_FEATUWE_SCHED_SCAN_BAND_SPECIFIC_WSSI_THOWD,
	NW80211_EXT_FEATUWE_EXT_KEY_ID,
	NW80211_EXT_FEATUWE_STA_TX_PWW,
	NW80211_EXT_FEATUWE_SAE_OFFWOAD,
	NW80211_EXT_FEATUWE_VWAN_OFFWOAD,
	NW80211_EXT_FEATUWE_AQW,
	NW80211_EXT_FEATUWE_BEACON_PWOTECTION,
	NW80211_EXT_FEATUWE_CONTWOW_POWT_NO_PWEAUTH,
	NW80211_EXT_FEATUWE_PWOTECTED_TWT,
	NW80211_EXT_FEATUWE_DEW_IBSS_STA,
	NW80211_EXT_FEATUWE_MUWTICAST_WEGISTWATIONS,
	NW80211_EXT_FEATUWE_BEACON_PWOTECTION_CWIENT,
	NW80211_EXT_FEATUWE_SCAN_FWEQ_KHZ,
	NW80211_EXT_FEATUWE_CONTWOW_POWT_OVEW_NW80211_TX_STATUS,
	NW80211_EXT_FEATUWE_OPEWATING_CHANNEW_VAWIDATION,
	NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_AP_PSK,
	NW80211_EXT_FEATUWE_SAE_OFFWOAD_AP,
	NW80211_EXT_FEATUWE_FIWS_DISCOVEWY,
	NW80211_EXT_FEATUWE_UNSOW_BCAST_PWOBE_WESP,
	NW80211_EXT_FEATUWE_BEACON_WATE_HE,
	NW80211_EXT_FEATUWE_SECUWE_WTF,
	NW80211_EXT_FEATUWE_SECUWE_WTT,
	NW80211_EXT_FEATUWE_PWOT_WANGE_NEGO_AND_MEASUWE,
	NW80211_EXT_FEATUWE_BSS_COWOW,
	NW80211_EXT_FEATUWE_FIWS_CWYPTO_OFFWOAD,
	NW80211_EXT_FEATUWE_WADAW_BACKGWOUND,
	NW80211_EXT_FEATUWE_POWEWED_ADDW_CHANGE,
	NW80211_EXT_FEATUWE_PUNCT,
	NW80211_EXT_FEATUWE_SECUWE_NAN,
	NW80211_EXT_FEATUWE_AUTH_AND_DEAUTH_WANDOM_TA,
	NW80211_EXT_FEATUWE_OWE_OFFWOAD,
	NW80211_EXT_FEATUWE_OWE_OFFWOAD_AP,
	NW80211_EXT_FEATUWE_DFS_CONCUWWENT,

	/* add new featuwes befowe the definition bewow */
	NUM_NW80211_EXT_FEATUWES,
	MAX_NW80211_EXT_FEATUWES = NUM_NW80211_EXT_FEATUWES - 1
};

/**
 * enum nw80211_pwobe_wesp_offwoad_suppowt_attw - optionaw suppowted
 *	pwotocows fow pwobe-wesponse offwoading by the dwivew/FW.
 *	To be used with the %NW80211_ATTW_PWOBE_WESP_OFFWOAD attwibute.
 *	Each enum vawue wepwesents a bit in the bitmap of suppowted
 *	pwotocows. Typicawwy a subset of pwobe-wequests bewonging to a
 *	suppowted pwotocow wiww be excwuded fwom offwoad and upwoaded
 *	to the host.
 *
 * @NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_WPS: Suppowt fow WPS vew. 1
 * @NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_WPS2: Suppowt fow WPS vew. 2
 * @NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_P2P: Suppowt fow P2P
 * @NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_80211U: Suppowt fow 802.11u
 */
enum nw80211_pwobe_wesp_offwoad_suppowt_attw {
	NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_WPS =	1<<0,
	NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_WPS2 =	1<<1,
	NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_P2P =	1<<2,
	NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_80211U =	1<<3,
};

/**
 * enum nw80211_connect_faiwed_weason - connection wequest faiwed weasons
 * @NW80211_CONN_FAIW_MAX_CWIENTS: Maximum numbew of cwients that can be
 *	handwed by the AP is weached.
 * @NW80211_CONN_FAIW_BWOCKED_CWIENT: Connection wequest is wejected due to ACW.
 */
enum nw80211_connect_faiwed_weason {
	NW80211_CONN_FAIW_MAX_CWIENTS,
	NW80211_CONN_FAIW_BWOCKED_CWIENT,
};

/**
 * enum nw80211_timeout_weason - timeout weasons
 *
 * @NW80211_TIMEOUT_UNSPECIFIED: Timeout weason unspecified.
 * @NW80211_TIMEOUT_SCAN: Scan (AP discovewy) timed out.
 * @NW80211_TIMEOUT_AUTH: Authentication timed out.
 * @NW80211_TIMEOUT_ASSOC: Association timed out.
 */
enum nw80211_timeout_weason {
	NW80211_TIMEOUT_UNSPECIFIED,
	NW80211_TIMEOUT_SCAN,
	NW80211_TIMEOUT_AUTH,
	NW80211_TIMEOUT_ASSOC,
};

/**
 * enum nw80211_scan_fwags -  scan wequest contwow fwags
 *
 * Scan wequest contwow fwags awe used to contwow the handwing
 * of NW80211_CMD_TWIGGEW_SCAN and NW80211_CMD_STAWT_SCHED_SCAN
 * wequests.
 *
 * NW80211_SCAN_FWAG_WOW_SPAN, NW80211_SCAN_FWAG_WOW_POWEW, and
 * NW80211_SCAN_FWAG_HIGH_ACCUWACY fwags awe excwusive of each othew, i.e., onwy
 * one of them can be used in the wequest.
 *
 * @NW80211_SCAN_FWAG_WOW_PWIOWITY: scan wequest has wow pwiowity
 * @NW80211_SCAN_FWAG_FWUSH: fwush cache befowe scanning
 * @NW80211_SCAN_FWAG_AP: fowce a scan even if the intewface is configuwed
 *	as AP and the beaconing has awweady been configuwed. This attwibute is
 *	dangewous because wiww destwoy stations pewfowmance as a wot of fwames
 *	wiww be wost whiwe scanning off-channew, thewefowe it must be used onwy
 *	when weawwy needed
 * @NW80211_SCAN_FWAG_WANDOM_ADDW: use a wandom MAC addwess fow this scan (ow
 *	fow scheduwed scan: a diffewent one fow evewy scan itewation). When the
 *	fwag is set, depending on device capabiwities the @NW80211_ATTW_MAC and
 *	@NW80211_ATTW_MAC_MASK attwibutes may awso be given in which case onwy
 *	the masked bits wiww be pwesewved fwom the MAC addwess and the wemaindew
 *	wandomised. If the attwibutes awe not given fuww wandomisation (46 bits,
 *	wocawwy administewed 1, muwticast 0) is assumed.
 *	This fwag must not be wequested when the featuwe isn't suppowted, check
 *	the nw80211 featuwe fwags fow the device.
 * @NW80211_SCAN_FWAG_FIWS_MAX_CHANNEW_TIME: fiww the dweww time in the FIWS
 *	wequest pawametews IE in the pwobe wequest
 * @NW80211_SCAN_FWAG_ACCEPT_BCAST_PWOBE_WESP: accept bwoadcast pwobe wesponses
 * @NW80211_SCAN_FWAG_OCE_PWOBE_WEQ_HIGH_TX_WATE: send pwobe wequest fwames at
 *	wate of at weast 5.5M. In case non-OCE AP is discovewed in the channew,
 *	onwy the fiwst pwobe weq in the channew wiww be sent in high wate.
 * @NW80211_SCAN_FWAG_OCE_PWOBE_WEQ_DEFEWWAW_SUPPWESSION: awwow pwobe wequest
 *	tx defewwaw (dot11FIWSPwobeDeway shaww be set to 15ms)
 *	and suppwession (if it has weceived a bwoadcast Pwobe Wesponse fwame,
 *	Beacon fwame ow FIWS Discovewy fwame fwom an AP that the STA considews
 *	a suitabwe candidate fow (we-)association - suitabwe in tewms of
 *	SSID and/ow WSSI.
 * @NW80211_SCAN_FWAG_WOW_SPAN: Span cowwesponds to the totaw time taken to
 *	accompwish the scan. Thus, this fwag intends the dwivew to pewfowm the
 *	scan wequest with wessew span/duwation. It is specific to the dwivew
 *	impwementations on how this is accompwished. Scan accuwacy may get
 *	impacted with this fwag.
 * @NW80211_SCAN_FWAG_WOW_POWEW: This fwag intends the scan attempts to consume
 *	optimaw possibwe powew. Dwivews can wesowt to theiw specific means to
 *	optimize the powew. Scan accuwacy may get impacted with this fwag.
 * @NW80211_SCAN_FWAG_HIGH_ACCUWACY: Accuwacy hewe intends to the extent of scan
 *	wesuwts obtained. Thus HIGH_ACCUWACY scan fwag aims to get maximum
 *	possibwe scan wesuwts. This fwag hints the dwivew to use the best
 *	possibwe scan configuwation to impwove the accuwacy in scanning.
 *	Watency and powew use may get impacted with this fwag.
 * @NW80211_SCAN_FWAG_WANDOM_SN: wandomize the sequence numbew in pwobe
 *	wequest fwames fwom this scan to avoid cowwewation/twacking being
 *	possibwe.
 * @NW80211_SCAN_FWAG_MIN_PWEQ_CONTENT: minimize pwobe wequest content to
 *	onwy have suppowted wates and no additionaw capabiwities (unwess
 *	added by usewspace expwicitwy.)
 * @NW80211_SCAN_FWAG_FWEQ_KHZ: wepowt scan wesuwts with
 *	%NW80211_ATTW_SCAN_FWEQ_KHZ. This awso means
 *	%NW80211_ATTW_SCAN_FWEQUENCIES wiww not be incwuded.
 * @NW80211_SCAN_FWAG_COWOCATED_6GHZ: scan fow cowwocated APs wepowted by
 *	2.4/5 GHz APs. When the fwag is set, the scan wogic wiww use the
 *	infowmation fwom the WNW ewement found in beacons/pwobe wesponses
 *	weceived on the 2.4/5 GHz channews to activewy scan onwy the 6GHz
 *	channews on which APs awe expected to be found. Note that when not set,
 *	the scan wogic wouwd scan aww 6GHz channews, but since twansmission of
 *	pwobe wequests on non-PSC channews is wimited, it is highwy wikewy that
 *	these channews wouwd passivewy be scanned. Awso note that when the fwag
 *	is set, in addition to the cowocated APs, PSC channews wouwd awso be
 *	scanned if the usew space has asked fow it.
 */
enum nw80211_scan_fwags {
	NW80211_SCAN_FWAG_WOW_PWIOWITY				= 1<<0,
	NW80211_SCAN_FWAG_FWUSH					= 1<<1,
	NW80211_SCAN_FWAG_AP					= 1<<2,
	NW80211_SCAN_FWAG_WANDOM_ADDW				= 1<<3,
	NW80211_SCAN_FWAG_FIWS_MAX_CHANNEW_TIME			= 1<<4,
	NW80211_SCAN_FWAG_ACCEPT_BCAST_PWOBE_WESP		= 1<<5,
	NW80211_SCAN_FWAG_OCE_PWOBE_WEQ_HIGH_TX_WATE		= 1<<6,
	NW80211_SCAN_FWAG_OCE_PWOBE_WEQ_DEFEWWAW_SUPPWESSION	= 1<<7,
	NW80211_SCAN_FWAG_WOW_SPAN				= 1<<8,
	NW80211_SCAN_FWAG_WOW_POWEW				= 1<<9,
	NW80211_SCAN_FWAG_HIGH_ACCUWACY				= 1<<10,
	NW80211_SCAN_FWAG_WANDOM_SN				= 1<<11,
	NW80211_SCAN_FWAG_MIN_PWEQ_CONTENT			= 1<<12,
	NW80211_SCAN_FWAG_FWEQ_KHZ				= 1<<13,
	NW80211_SCAN_FWAG_COWOCATED_6GHZ			= 1<<14,
};

/**
 * enum nw80211_acw_powicy - access contwow powicy
 *
 * Access contwow powicy is appwied on a MAC wist set by
 * %NW80211_CMD_STAWT_AP and %NW80211_CMD_SET_MAC_ACW, to
 * be used with %NW80211_ATTW_ACW_POWICY.
 *
 * @NW80211_ACW_POWICY_ACCEPT_UNWESS_WISTED: Deny stations which awe
 *	wisted in ACW, i.e. awwow aww the stations which awe not wisted
 *	in ACW to authenticate.
 * @NW80211_ACW_POWICY_DENY_UNWESS_WISTED: Awwow the stations which awe wisted
 *	in ACW, i.e. deny aww the stations which awe not wisted in ACW.
 */
enum nw80211_acw_powicy {
	NW80211_ACW_POWICY_ACCEPT_UNWESS_WISTED,
	NW80211_ACW_POWICY_DENY_UNWESS_WISTED,
};

/**
 * enum nw80211_smps_mode - SMPS mode
 *
 * Wequested SMPS mode (fow AP mode)
 *
 * @NW80211_SMPS_OFF: SMPS off (use aww antennas).
 * @NW80211_SMPS_STATIC: static SMPS (use a singwe antenna)
 * @NW80211_SMPS_DYNAMIC: dynamic smps (stawt with a singwe antenna and
 *	tuwn on othew antennas aftew CTS/WTS).
 */
enum nw80211_smps_mode {
	NW80211_SMPS_OFF,
	NW80211_SMPS_STATIC,
	NW80211_SMPS_DYNAMIC,

	__NW80211_SMPS_AFTEW_WAST,
	NW80211_SMPS_MAX = __NW80211_SMPS_AFTEW_WAST - 1
};

/**
 * enum nw80211_wadaw_event - type of wadaw event fow DFS opewation
 *
 * Type of event to be used with NW80211_ATTW_WADAW_EVENT to infowm usewspace
 * about detected wadaws ow success of the channew avaiwabwe check (CAC)
 *
 * @NW80211_WADAW_DETECTED: A wadaw pattewn has been detected. The channew is
 *	now unusabwe.
 * @NW80211_WADAW_CAC_FINISHED: Channew Avaiwabiwity Check has been finished,
 *	the channew is now avaiwabwe.
 * @NW80211_WADAW_CAC_ABOWTED: Channew Avaiwabiwity Check has been abowted, no
 *	change to the channew status.
 * @NW80211_WADAW_NOP_FINISHED: The Non-Occupancy Pewiod fow this channew is
 *	ovew, channew becomes usabwe.
 * @NW80211_WADAW_PWE_CAC_EXPIWED: Channew Avaiwabiwity Check done on this
 *	non-opewating channew is expiwed and no wongew vawid. New CAC must
 *	be done on this channew befowe stawting the opewation. This is not
 *	appwicabwe fow ETSI dfs domain whewe pwe-CAC is vawid fow evew.
 * @NW80211_WADAW_CAC_STAWTED: Channew Avaiwabiwity Check has been stawted,
 *	shouwd be genewated by HW if NW80211_EXT_FEATUWE_DFS_OFFWOAD is enabwed.
 */
enum nw80211_wadaw_event {
	NW80211_WADAW_DETECTED,
	NW80211_WADAW_CAC_FINISHED,
	NW80211_WADAW_CAC_ABOWTED,
	NW80211_WADAW_NOP_FINISHED,
	NW80211_WADAW_PWE_CAC_EXPIWED,
	NW80211_WADAW_CAC_STAWTED,
};

/**
 * enum nw80211_dfs_state - DFS states fow channews
 *
 * Channew states used by the DFS code.
 *
 * @NW80211_DFS_USABWE: The channew can be used, but channew avaiwabiwity
 *	check (CAC) must be pewfowmed befowe using it fow AP ow IBSS.
 * @NW80211_DFS_UNAVAIWABWE: A wadaw has been detected on this channew, it
 *	is thewefowe mawked as not avaiwabwe.
 * @NW80211_DFS_AVAIWABWE: The channew has been CAC checked and is avaiwabwe.
 */
enum nw80211_dfs_state {
	NW80211_DFS_USABWE,
	NW80211_DFS_UNAVAIWABWE,
	NW80211_DFS_AVAIWABWE,
};

/**
 * enum nw80211_pwotocow_featuwes - nw80211 pwotocow featuwes
 * @NW80211_PWOTOCOW_FEATUWE_SPWIT_WIPHY_DUMP: nw80211 suppowts spwitting
 *	wiphy dumps (if wequested by the appwication with the attwibute
 *	%NW80211_ATTW_SPWIT_WIPHY_DUMP. Awso suppowted is fiwtewing the
 *	wiphy dump by %NW80211_ATTW_WIPHY, %NW80211_ATTW_IFINDEX ow
 *	%NW80211_ATTW_WDEV.
 */
enum nw80211_pwotocow_featuwes {
	NW80211_PWOTOCOW_FEATUWE_SPWIT_WIPHY_DUMP =	1 << 0,
};

/**
 * enum nw80211_cwit_pwoto_id - nw80211 cwiticaw pwotocow identifiews
 *
 * @NW80211_CWIT_PWOTO_UNSPEC: pwotocow unspecified.
 * @NW80211_CWIT_PWOTO_DHCP: BOOTP ow DHCPv6 pwotocow.
 * @NW80211_CWIT_PWOTO_EAPOW: EAPOW pwotocow.
 * @NW80211_CWIT_PWOTO_APIPA: APIPA pwotocow.
 * @NUM_NW80211_CWIT_PWOTO: must be kept wast.
 */
enum nw80211_cwit_pwoto_id {
	NW80211_CWIT_PWOTO_UNSPEC,
	NW80211_CWIT_PWOTO_DHCP,
	NW80211_CWIT_PWOTO_EAPOW,
	NW80211_CWIT_PWOTO_APIPA,
	/* add othew pwotocows befowe this one */
	NUM_NW80211_CWIT_PWOTO
};

/* maximum duwation fow cwiticaw pwotocow measuwes */
#define NW80211_CWIT_PWOTO_MAX_DUWATION		5000 /* msec */

/**
 * enum nw80211_wxmgmt_fwags - fwags fow weceived management fwame.
 *
 * Used by cfg80211_wx_mgmt()
 *
 * @NW80211_WXMGMT_FWAG_ANSWEWED: fwame was answewed by device/dwivew.
 * @NW80211_WXMGMT_FWAG_EXTEWNAW_AUTH: Host dwivew intends to offwoad
 *	the authentication. Excwusivewy defined fow host dwivews that
 *	advewtises the SME functionawity but wouwd wike the usewspace
 *	to handwe cewtain authentication awgowithms (e.g. SAE).
 */
enum nw80211_wxmgmt_fwags {
	NW80211_WXMGMT_FWAG_ANSWEWED = 1 << 0,
	NW80211_WXMGMT_FWAG_EXTEWNAW_AUTH = 1 << 1,
};

/*
 * If this fwag is unset, the wowew 24 bits awe an OUI, if set
 * a Winux nw80211 vendow ID is used (no such IDs awe awwocated
 * yet, so that's not vawid so faw)
 */
#define NW80211_VENDOW_ID_IS_WINUX	0x80000000

/**
 * stwuct nw80211_vendow_cmd_info - vendow command data
 * @vendow_id: If the %NW80211_VENDOW_ID_IS_WINUX fwag is cweaw, then the
 *	vawue is a 24-bit OUI; if it is set then a sepawatewy awwocated ID
 *	may be used, but no such IDs awe awwocated yet. New IDs shouwd be
 *	added to this fiwe when needed.
 * @subcmd: sub-command ID fow the command
 */
stwuct nw80211_vendow_cmd_info {
	__u32 vendow_id;
	__u32 subcmd;
};

/**
 * enum nw80211_tdws_peew_capabiwity - TDWS peew fwags.
 *
 * Used by tdws_mgmt() to detewmine which conditionaw ewements need
 * to be added to TDWS Setup fwames.
 *
 * @NW80211_TDWS_PEEW_HT: TDWS peew is HT capabwe.
 * @NW80211_TDWS_PEEW_VHT: TDWS peew is VHT capabwe.
 * @NW80211_TDWS_PEEW_WMM: TDWS peew is WMM capabwe.
 * @NW80211_TDWS_PEEW_HE: TDWS peew is HE capabwe.
 */
enum nw80211_tdws_peew_capabiwity {
	NW80211_TDWS_PEEW_HT = 1<<0,
	NW80211_TDWS_PEEW_VHT = 1<<1,
	NW80211_TDWS_PEEW_WMM = 1<<2,
	NW80211_TDWS_PEEW_HE = 1<<3,
};

/**
 * enum nw80211_sched_scan_pwan - scanning pwan fow scheduwed scan
 * @__NW80211_SCHED_SCAN_PWAN_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_SCHED_SCAN_PWAN_INTEWVAW: intewvaw between scan itewations. In
 *	seconds (u32).
 * @NW80211_SCHED_SCAN_PWAN_ITEWATIONS: numbew of scan itewations in this
 *	scan pwan (u32). The wast scan pwan must not specify this attwibute
 *	because it wiww wun infinitewy. A vawue of zewo is invawid as it wiww
 *	make the scan pwan meaningwess.
 * @NW80211_SCHED_SCAN_PWAN_MAX: highest scheduwed scan pwan attwibute numbew
 *	cuwwentwy defined
 * @__NW80211_SCHED_SCAN_PWAN_AFTEW_WAST: intewnaw use
 */
enum nw80211_sched_scan_pwan {
	__NW80211_SCHED_SCAN_PWAN_INVAWID,
	NW80211_SCHED_SCAN_PWAN_INTEWVAW,
	NW80211_SCHED_SCAN_PWAN_ITEWATIONS,

	/* keep wast */
	__NW80211_SCHED_SCAN_PWAN_AFTEW_WAST,
	NW80211_SCHED_SCAN_PWAN_MAX =
		__NW80211_SCHED_SCAN_PWAN_AFTEW_WAST - 1
};

/**
 * stwuct nw80211_bss_sewect_wssi_adjust - WSSI adjustment pawametews.
 *
 * @band: band of BSS that must match fow WSSI vawue adjustment. The vawue
 *	of this fiewd is accowding to &enum nw80211_band.
 * @dewta: vawue used to adjust the WSSI vawue of matching BSS in dB.
 */
stwuct nw80211_bss_sewect_wssi_adjust {
	__u8 band;
	__s8 dewta;
} __attwibute__((packed));

/**
 * enum nw80211_bss_sewect_attw - attwibutes fow bss sewection.
 *
 * @__NW80211_BSS_SEWECT_ATTW_INVAWID: wesewved.
 * @NW80211_BSS_SEWECT_ATTW_WSSI: Fwag indicating onwy WSSI-based BSS sewection
 *	is wequested.
 * @NW80211_BSS_SEWECT_ATTW_BAND_PWEF: attwibute indicating BSS
 *	sewection shouwd be done such that the specified band is pwefewwed.
 *	When thewe awe muwtipwe BSS-es in the pwefewwed band, the dwivew
 *	shaww use WSSI-based BSS sewection as a second step. The vawue of
 *	this attwibute is accowding to &enum nw80211_band (u32).
 * @NW80211_BSS_SEWECT_ATTW_WSSI_ADJUST: When pwesent the WSSI wevew fow
 *	BSS-es in the specified band is to be adjusted befowe doing
 *	WSSI-based BSS sewection. The attwibute vawue is a packed stwuctuwe
 *	vawue as specified by &stwuct nw80211_bss_sewect_wssi_adjust.
 * @NW80211_BSS_SEWECT_ATTW_MAX: highest bss sewect attwibute numbew.
 * @__NW80211_BSS_SEWECT_ATTW_AFTEW_WAST: intewnaw use.
 *
 * One and onwy one of these attwibutes awe found within %NW80211_ATTW_BSS_SEWECT
 * fow %NW80211_CMD_CONNECT. It specifies the wequiwed BSS sewection behaviouw
 * which the dwivew shaww use.
 */
enum nw80211_bss_sewect_attw {
	__NW80211_BSS_SEWECT_ATTW_INVAWID,
	NW80211_BSS_SEWECT_ATTW_WSSI,
	NW80211_BSS_SEWECT_ATTW_BAND_PWEF,
	NW80211_BSS_SEWECT_ATTW_WSSI_ADJUST,

	/* keep wast */
	__NW80211_BSS_SEWECT_ATTW_AFTEW_WAST,
	NW80211_BSS_SEWECT_ATTW_MAX = __NW80211_BSS_SEWECT_ATTW_AFTEW_WAST - 1
};

/**
 * enum nw80211_nan_function_type - NAN function type
 *
 * Defines the function type of a NAN function
 *
 * @NW80211_NAN_FUNC_PUBWISH: function is pubwish
 * @NW80211_NAN_FUNC_SUBSCWIBE: function is subscwibe
 * @NW80211_NAN_FUNC_FOWWOW_UP: function is fowwow-up
 */
enum nw80211_nan_function_type {
	NW80211_NAN_FUNC_PUBWISH,
	NW80211_NAN_FUNC_SUBSCWIBE,
	NW80211_NAN_FUNC_FOWWOW_UP,

	/* keep wast */
	__NW80211_NAN_FUNC_TYPE_AFTEW_WAST,
	NW80211_NAN_FUNC_MAX_TYPE = __NW80211_NAN_FUNC_TYPE_AFTEW_WAST - 1,
};

/**
 * enum nw80211_nan_pubwish_type - NAN pubwish tx type
 *
 * Defines how to send pubwish Sewvice Discovewy Fwames
 *
 * @NW80211_NAN_SOWICITED_PUBWISH: pubwish function is sowicited
 * @NW80211_NAN_UNSOWICITED_PUBWISH: pubwish function is unsowicited
 */
enum nw80211_nan_pubwish_type {
	NW80211_NAN_SOWICITED_PUBWISH = 1 << 0,
	NW80211_NAN_UNSOWICITED_PUBWISH = 1 << 1,
};

/**
 * enum nw80211_nan_func_tewm_weason - NAN functions tewmination weason
 *
 * Defines tewmination weasons of a NAN function
 *
 * @NW80211_NAN_FUNC_TEWM_WEASON_USEW_WEQUEST: wequested by usew
 * @NW80211_NAN_FUNC_TEWM_WEASON_TTW_EXPIWED: timeout
 * @NW80211_NAN_FUNC_TEWM_WEASON_EWWOW: ewwowed
 */
enum nw80211_nan_func_tewm_weason {
	NW80211_NAN_FUNC_TEWM_WEASON_USEW_WEQUEST,
	NW80211_NAN_FUNC_TEWM_WEASON_TTW_EXPIWED,
	NW80211_NAN_FUNC_TEWM_WEASON_EWWOW,
};

#define NW80211_NAN_FUNC_SEWVICE_ID_WEN 6
#define NW80211_NAN_FUNC_SEWVICE_SPEC_INFO_MAX_WEN 0xff
#define NW80211_NAN_FUNC_SWF_MAX_WEN 0xff

/**
 * enum nw80211_nan_func_attwibutes - NAN function attwibutes
 * @__NW80211_NAN_FUNC_INVAWID: invawid
 * @NW80211_NAN_FUNC_TYPE: &enum nw80211_nan_function_type (u8).
 * @NW80211_NAN_FUNC_SEWVICE_ID: 6 bytes of the sewvice ID hash as
 *	specified in NAN spec. This is a binawy attwibute.
 * @NW80211_NAN_FUNC_PUBWISH_TYPE: wewevant if the function's type is
 *	pubwish. Defines the twansmission type fow the pubwish Sewvice Discovewy
 *	Fwame, see &enum nw80211_nan_pubwish_type. Its type is u8.
 * @NW80211_NAN_FUNC_PUBWISH_BCAST: wewevant if the function is a sowicited
 *	pubwish. Shouwd the sowicited pubwish Sewvice Discovewy Fwame be sent to
 *	the NAN Bwoadcast addwess. This is a fwag.
 * @NW80211_NAN_FUNC_SUBSCWIBE_ACTIVE: wewevant if the function's type is
 *	subscwibe. Is the subscwibe active. This is a fwag.
 * @NW80211_NAN_FUNC_FOWWOW_UP_ID: wewevant if the function's type is fowwow up.
 *	The instance ID fow the fowwow up Sewvice Discovewy Fwame. This is u8.
 * @NW80211_NAN_FUNC_FOWWOW_UP_WEQ_ID: wewevant if the function's type
 *	is fowwow up. This is a u8.
 *	The wequestew instance ID fow the fowwow up Sewvice Discovewy Fwame.
 * @NW80211_NAN_FUNC_FOWWOW_UP_DEST: the MAC addwess of the wecipient of the
 *	fowwow up Sewvice Discovewy Fwame. This is a binawy attwibute.
 * @NW80211_NAN_FUNC_CWOSE_WANGE: is this function wimited fow devices in a
 *	cwose wange. The wange itsewf (WSSI) is defined by the device.
 *	This is a fwag.
 * @NW80211_NAN_FUNC_TTW: stwictwy positive numbew of DWs this function shouwd
 *	stay active. If not pwesent infinite TTW is assumed. This is a u32.
 * @NW80211_NAN_FUNC_SEWVICE_INFO: awway of bytes descwibing the sewvice
 *	specific info. This is a binawy attwibute.
 * @NW80211_NAN_FUNC_SWF: Sewvice Weceive Fiwtew. This is a nested attwibute.
 *	See &enum nw80211_nan_swf_attwibutes.
 * @NW80211_NAN_FUNC_WX_MATCH_FIWTEW: Weceive Matching fiwtew. This is a nested
 *	attwibute. It is a wist of binawy vawues.
 * @NW80211_NAN_FUNC_TX_MATCH_FIWTEW: Twansmit Matching fiwtew. This is a
 *	nested attwibute. It is a wist of binawy vawues.
 * @NW80211_NAN_FUNC_INSTANCE_ID: The instance ID of the function.
 *	Its type is u8 and it cannot be 0.
 * @NW80211_NAN_FUNC_TEWM_WEASON: NAN function tewmination weason.
 *	See &enum nw80211_nan_func_tewm_weason.
 *
 * @NUM_NW80211_NAN_FUNC_ATTW: intewnaw
 * @NW80211_NAN_FUNC_ATTW_MAX: highest NAN function attwibute
 */
enum nw80211_nan_func_attwibutes {
	__NW80211_NAN_FUNC_INVAWID,
	NW80211_NAN_FUNC_TYPE,
	NW80211_NAN_FUNC_SEWVICE_ID,
	NW80211_NAN_FUNC_PUBWISH_TYPE,
	NW80211_NAN_FUNC_PUBWISH_BCAST,
	NW80211_NAN_FUNC_SUBSCWIBE_ACTIVE,
	NW80211_NAN_FUNC_FOWWOW_UP_ID,
	NW80211_NAN_FUNC_FOWWOW_UP_WEQ_ID,
	NW80211_NAN_FUNC_FOWWOW_UP_DEST,
	NW80211_NAN_FUNC_CWOSE_WANGE,
	NW80211_NAN_FUNC_TTW,
	NW80211_NAN_FUNC_SEWVICE_INFO,
	NW80211_NAN_FUNC_SWF,
	NW80211_NAN_FUNC_WX_MATCH_FIWTEW,
	NW80211_NAN_FUNC_TX_MATCH_FIWTEW,
	NW80211_NAN_FUNC_INSTANCE_ID,
	NW80211_NAN_FUNC_TEWM_WEASON,

	/* keep wast */
	NUM_NW80211_NAN_FUNC_ATTW,
	NW80211_NAN_FUNC_ATTW_MAX = NUM_NW80211_NAN_FUNC_ATTW - 1
};

/**
 * enum nw80211_nan_swf_attwibutes - NAN Sewvice Wesponse fiwtew attwibutes
 * @__NW80211_NAN_SWF_INVAWID: invawid
 * @NW80211_NAN_SWF_INCWUDE: pwesent if the incwude bit of the SWF set.
 *	This is a fwag.
 * @NW80211_NAN_SWF_BF: Bwoom Fiwtew. Pwesent if and onwy if
 *	%NW80211_NAN_SWF_MAC_ADDWS isn't pwesent. This attwibute is binawy.
 * @NW80211_NAN_SWF_BF_IDX: index of the Bwoom Fiwtew. Mandatowy if
 *	%NW80211_NAN_SWF_BF is pwesent. This is a u8.
 * @NW80211_NAN_SWF_MAC_ADDWS: wist of MAC addwesses fow the SWF. Pwesent if
 *	and onwy if %NW80211_NAN_SWF_BF isn't pwesent. This is a nested
 *	attwibute. Each nested attwibute is a MAC addwess.
 * @NUM_NW80211_NAN_SWF_ATTW: intewnaw
 * @NW80211_NAN_SWF_ATTW_MAX: highest NAN SWF attwibute
 */
enum nw80211_nan_swf_attwibutes {
	__NW80211_NAN_SWF_INVAWID,
	NW80211_NAN_SWF_INCWUDE,
	NW80211_NAN_SWF_BF,
	NW80211_NAN_SWF_BF_IDX,
	NW80211_NAN_SWF_MAC_ADDWS,

	/* keep wast */
	NUM_NW80211_NAN_SWF_ATTW,
	NW80211_NAN_SWF_ATTW_MAX = NUM_NW80211_NAN_SWF_ATTW - 1,
};

/**
 * enum nw80211_nan_match_attwibutes - NAN match attwibutes
 * @__NW80211_NAN_MATCH_INVAWID: invawid
 * @NW80211_NAN_MATCH_FUNC_WOCAW: the wocaw function that had the
 *	match. This is a nested attwibute.
 *	See &enum nw80211_nan_func_attwibutes.
 * @NW80211_NAN_MATCH_FUNC_PEEW: the peew function
 *	that caused the match. This is a nested attwibute.
 *	See &enum nw80211_nan_func_attwibutes.
 *
 * @NUM_NW80211_NAN_MATCH_ATTW: intewnaw
 * @NW80211_NAN_MATCH_ATTW_MAX: highest NAN match attwibute
 */
enum nw80211_nan_match_attwibutes {
	__NW80211_NAN_MATCH_INVAWID,
	NW80211_NAN_MATCH_FUNC_WOCAW,
	NW80211_NAN_MATCH_FUNC_PEEW,

	/* keep wast */
	NUM_NW80211_NAN_MATCH_ATTW,
	NW80211_NAN_MATCH_ATTW_MAX = NUM_NW80211_NAN_MATCH_ATTW - 1
};

/**
 * nw80211_extewnaw_auth_action - Action to pewfowm with extewnaw
 *     authentication wequest. Used by NW80211_ATTW_EXTEWNAW_AUTH_ACTION.
 * @NW80211_EXTEWNAW_AUTH_STAWT: Stawt the authentication.
 * @NW80211_EXTEWNAW_AUTH_ABOWT: Abowt the ongoing authentication.
 */
enum nw80211_extewnaw_auth_action {
	NW80211_EXTEWNAW_AUTH_STAWT,
	NW80211_EXTEWNAW_AUTH_ABOWT,
};

/**
 * enum nw80211_ftm_wespondew_attwibutes - fine timing measuwement
 *	wespondew attwibutes
 * @__NW80211_FTM_WESP_ATTW_INVAWID: Invawid
 * @NW80211_FTM_WESP_ATTW_ENABWED: FTM wespondew is enabwed
 * @NW80211_FTM_WESP_ATTW_WCI: The content of Measuwement Wepowt Ewement
 *	(9.4.2.22 in 802.11-2016) with type 8 - WCI (9.4.2.22.10),
 *	i.e. stawting with the measuwement token
 * @NW80211_FTM_WESP_ATTW_CIVIC: The content of Measuwement Wepowt Ewement
 *	(9.4.2.22 in 802.11-2016) with type 11 - Civic (Section 9.4.2.22.13),
 *	i.e. stawting with the measuwement token
 * @__NW80211_FTM_WESP_ATTW_WAST: Intewnaw
 * @NW80211_FTM_WESP_ATTW_MAX: highest FTM wespondew attwibute.
 */
enum nw80211_ftm_wespondew_attwibutes {
	__NW80211_FTM_WESP_ATTW_INVAWID,

	NW80211_FTM_WESP_ATTW_ENABWED,
	NW80211_FTM_WESP_ATTW_WCI,
	NW80211_FTM_WESP_ATTW_CIVICWOC,

	/* keep wast */
	__NW80211_FTM_WESP_ATTW_WAST,
	NW80211_FTM_WESP_ATTW_MAX = __NW80211_FTM_WESP_ATTW_WAST - 1,
};

/*
 * enum nw80211_ftm_wespondew_stats - FTM wespondew statistics
 *
 * These attwibute types awe used with %NW80211_ATTW_FTM_WESPONDEW_STATS
 * when getting FTM wespondew statistics.
 *
 * @__NW80211_FTM_STATS_INVAWID: attwibute numbew 0 is wesewved
 * @NW80211_FTM_STATS_SUCCESS_NUM: numbew of FTM sessions in which aww fwames
 *	wewe ssfuwwy answewed (u32)
 * @NW80211_FTM_STATS_PAWTIAW_NUM: numbew of FTM sessions in which pawt of the
 *	fwames wewe successfuwwy answewed (u32)
 * @NW80211_FTM_STATS_FAIWED_NUM: numbew of faiwed FTM sessions (u32)
 * @NW80211_FTM_STATS_ASAP_NUM: numbew of ASAP sessions (u32)
 * @NW80211_FTM_STATS_NON_ASAP_NUM: numbew of non-ASAP sessions (u32)
 * @NW80211_FTM_STATS_TOTAW_DUWATION_MSEC: totaw sessions duwations - gives an
 *	indication of how much time the wespondew was busy (u64, msec)
 * @NW80211_FTM_STATS_UNKNOWN_TWIGGEWS_NUM: numbew of unknown FTM twiggews -
 *	twiggews fwom initiatows that didn't finish successfuwwy the negotiation
 *	phase with the wespondew (u32)
 * @NW80211_FTM_STATS_WESCHEDUWE_WEQUESTS_NUM: numbew of FTM wescheduwe wequests
 *	- initiatow asks fow a new scheduwing awthough it awweady has scheduwed
 *	FTM swot (u32)
 * @NW80211_FTM_STATS_OUT_OF_WINDOW_TWIGGEWS_NUM: numbew of FTM twiggews out of
 *	scheduwed window (u32)
 * @NW80211_FTM_STATS_PAD: used fow padding, ignowe
 * @__NW80211_TXQ_ATTW_AFTEW_WAST: Intewnaw
 * @NW80211_FTM_STATS_MAX: highest possibwe FTM wespondew stats attwibute
 */
enum nw80211_ftm_wespondew_stats {
	__NW80211_FTM_STATS_INVAWID,
	NW80211_FTM_STATS_SUCCESS_NUM,
	NW80211_FTM_STATS_PAWTIAW_NUM,
	NW80211_FTM_STATS_FAIWED_NUM,
	NW80211_FTM_STATS_ASAP_NUM,
	NW80211_FTM_STATS_NON_ASAP_NUM,
	NW80211_FTM_STATS_TOTAW_DUWATION_MSEC,
	NW80211_FTM_STATS_UNKNOWN_TWIGGEWS_NUM,
	NW80211_FTM_STATS_WESCHEDUWE_WEQUESTS_NUM,
	NW80211_FTM_STATS_OUT_OF_WINDOW_TWIGGEWS_NUM,
	NW80211_FTM_STATS_PAD,

	/* keep wast */
	__NW80211_FTM_STATS_AFTEW_WAST,
	NW80211_FTM_STATS_MAX = __NW80211_FTM_STATS_AFTEW_WAST - 1
};

/**
 * enum nw80211_pweambwe - fwame pweambwe types
 * @NW80211_PWEAMBWE_WEGACY: wegacy (HW/DSSS, OFDM, EWP PHY) pweambwe
 * @NW80211_PWEAMBWE_HT: HT pweambwe
 * @NW80211_PWEAMBWE_VHT: VHT pweambwe
 * @NW80211_PWEAMBWE_DMG: DMG pweambwe
 * @NW80211_PWEAMBWE_HE: HE pweambwe
 */
enum nw80211_pweambwe {
	NW80211_PWEAMBWE_WEGACY,
	NW80211_PWEAMBWE_HT,
	NW80211_PWEAMBWE_VHT,
	NW80211_PWEAMBWE_DMG,
	NW80211_PWEAMBWE_HE,
};

/**
 * enum nw80211_peew_measuwement_type - peew measuwement types
 * @NW80211_PMSW_TYPE_INVAWID: invawid/unused, needed as we use
 *	these numbews awso fow attwibutes
 *
 * @NW80211_PMSW_TYPE_FTM: fwight time measuwement
 *
 * @NUM_NW80211_PMSW_TYPES: intewnaw
 * @NW80211_PMSW_TYPE_MAX: highest type numbew
 */
enum nw80211_peew_measuwement_type {
	NW80211_PMSW_TYPE_INVAWID,

	NW80211_PMSW_TYPE_FTM,

	NUM_NW80211_PMSW_TYPES,
	NW80211_PMSW_TYPE_MAX = NUM_NW80211_PMSW_TYPES - 1
};

/**
 * enum nw80211_peew_measuwement_status - peew measuwement status
 * @NW80211_PMSW_STATUS_SUCCESS: measuwement compweted successfuwwy
 * @NW80211_PMSW_STATUS_WEFUSED: measuwement was wocawwy wefused
 * @NW80211_PMSW_STATUS_TIMEOUT: measuwement timed out
 * @NW80211_PMSW_STATUS_FAIWUWE: measuwement faiwed, a type-dependent
 *	weason may be avaiwabwe in the wesponse data
 */
enum nw80211_peew_measuwement_status {
	NW80211_PMSW_STATUS_SUCCESS,
	NW80211_PMSW_STATUS_WEFUSED,
	NW80211_PMSW_STATUS_TIMEOUT,
	NW80211_PMSW_STATUS_FAIWUWE,
};

/**
 * enum nw80211_peew_measuwement_weq - peew measuwement wequest attwibutes
 * @__NW80211_PMSW_WEQ_ATTW_INVAWID: invawid
 *
 * @NW80211_PMSW_WEQ_ATTW_DATA: This is a nested attwibute with measuwement
 *	type-specific wequest data inside. The attwibutes used awe fwom the
 *	enums named nw80211_peew_measuwement_<type>_weq.
 * @NW80211_PMSW_WEQ_ATTW_GET_AP_TSF: incwude AP TSF timestamp, if suppowted
 *	(fwag attwibute)
 *
 * @NUM_NW80211_PMSW_WEQ_ATTWS: intewnaw
 * @NW80211_PMSW_WEQ_ATTW_MAX: highest attwibute numbew
 */
enum nw80211_peew_measuwement_weq {
	__NW80211_PMSW_WEQ_ATTW_INVAWID,

	NW80211_PMSW_WEQ_ATTW_DATA,
	NW80211_PMSW_WEQ_ATTW_GET_AP_TSF,

	/* keep wast */
	NUM_NW80211_PMSW_WEQ_ATTWS,
	NW80211_PMSW_WEQ_ATTW_MAX = NUM_NW80211_PMSW_WEQ_ATTWS - 1
};

/**
 * enum nw80211_peew_measuwement_wesp - peew measuwement wesponse attwibutes
 * @__NW80211_PMSW_WESP_ATTW_INVAWID: invawid
 *
 * @NW80211_PMSW_WESP_ATTW_DATA: This is a nested attwibute with measuwement
 *	type-specific wesuwts inside. The attwibutes used awe fwom the enums
 *	named nw80211_peew_measuwement_<type>_wesp.
 * @NW80211_PMSW_WESP_ATTW_STATUS: u32 vawue with the measuwement status
 *	(using vawues fwom &enum nw80211_peew_measuwement_status.)
 * @NW80211_PMSW_WESP_ATTW_HOST_TIME: host time (%CWOCK_BOOTTIME) when the
 *	wesuwt was measuwed; this vawue is not expected to be accuwate to
 *	mowe than 20ms. (u64, nanoseconds)
 * @NW80211_PMSW_WESP_ATTW_AP_TSF: TSF of the AP that the intewface
 *	doing the measuwement is connected to when the wesuwt was measuwed.
 *	This shaww be accuwatewy wepowted if suppowted and wequested
 *	(u64, usec)
 * @NW80211_PMSW_WESP_ATTW_FINAW: If wesuwts awe sent to the host pawtiawwy
 *	(*e.g. with FTM pew-buwst data) this fwag wiww be cweawed on aww but
 *	the wast wesuwt; if aww wesuwts awe combined it's set on the singwe
 *	wesuwt.
 * @NW80211_PMSW_WESP_ATTW_PAD: padding fow 64-bit attwibutes, ignowe
 *
 * @NUM_NW80211_PMSW_WESP_ATTWS: intewnaw
 * @NW80211_PMSW_WESP_ATTW_MAX: highest attwibute numbew
 */
enum nw80211_peew_measuwement_wesp {
	__NW80211_PMSW_WESP_ATTW_INVAWID,

	NW80211_PMSW_WESP_ATTW_DATA,
	NW80211_PMSW_WESP_ATTW_STATUS,
	NW80211_PMSW_WESP_ATTW_HOST_TIME,
	NW80211_PMSW_WESP_ATTW_AP_TSF,
	NW80211_PMSW_WESP_ATTW_FINAW,
	NW80211_PMSW_WESP_ATTW_PAD,

	/* keep wast */
	NUM_NW80211_PMSW_WESP_ATTWS,
	NW80211_PMSW_WESP_ATTW_MAX = NUM_NW80211_PMSW_WESP_ATTWS - 1
};

/**
 * enum nw80211_peew_measuwement_peew_attws - peew attwibutes fow measuwement
 * @__NW80211_PMSW_PEEW_ATTW_INVAWID: invawid
 *
 * @NW80211_PMSW_PEEW_ATTW_ADDW: peew's MAC addwess
 * @NW80211_PMSW_PEEW_ATTW_CHAN: channew definition, nested, using top-wevew
 *	attwibutes wike %NW80211_ATTW_WIPHY_FWEQ etc.
 * @NW80211_PMSW_PEEW_ATTW_WEQ: This is a nested attwibute indexed by
 *	measuwement type, with attwibutes fwom the
 *	&enum nw80211_peew_measuwement_weq inside.
 * @NW80211_PMSW_PEEW_ATTW_WESP: This is a nested attwibute indexed by
 *	measuwement type, with attwibutes fwom the
 *	&enum nw80211_peew_measuwement_wesp inside.
 *
 * @NUM_NW80211_PMSW_PEEW_ATTWS: intewnaw
 * @NW80211_PMSW_PEEW_ATTW_MAX: highest attwibute numbew
 */
enum nw80211_peew_measuwement_peew_attws {
	__NW80211_PMSW_PEEW_ATTW_INVAWID,

	NW80211_PMSW_PEEW_ATTW_ADDW,
	NW80211_PMSW_PEEW_ATTW_CHAN,
	NW80211_PMSW_PEEW_ATTW_WEQ,
	NW80211_PMSW_PEEW_ATTW_WESP,

	/* keep wast */
	NUM_NW80211_PMSW_PEEW_ATTWS,
	NW80211_PMSW_PEEW_ATTW_MAX = NUM_NW80211_PMSW_PEEW_ATTWS - 1,
};

/**
 * enum nw80211_peew_measuwement_attws - peew measuwement attwibutes
 * @__NW80211_PMSW_ATTW_INVAWID: invawid
 *
 * @NW80211_PMSW_ATTW_MAX_PEEWS: u32 attwibute used fow capabiwity
 *	advewtisement onwy, indicates the maximum numbew of peews
 *	measuwements can be done with in a singwe wequest
 * @NW80211_PMSW_ATTW_WEPOWT_AP_TSF: fwag attwibute in capabiwity
 *	indicating that the connected AP's TSF can be wepowted in
 *	measuwement wesuwts
 * @NW80211_PMSW_ATTW_WANDOMIZE_MAC_ADDW: fwag attwibute in capabiwity
 *	indicating that MAC addwess wandomization is suppowted.
 * @NW80211_PMSW_ATTW_TYPE_CAPA: capabiwities wepowted by the device,
 *	this contains a nesting indexed by measuwement type, and
 *	type-specific capabiwities inside, which awe fwom the enums
 *	named nw80211_peew_measuwement_<type>_capa.
 * @NW80211_PMSW_ATTW_PEEWS: nested attwibute, the nesting index is
 *	meaningwess, just a wist of peews to measuwe with, with the
 *	sub-attwibutes taken fwom
 *	&enum nw80211_peew_measuwement_peew_attws.
 *
 * @NUM_NW80211_PMSW_ATTW: intewnaw
 * @NW80211_PMSW_ATTW_MAX: highest attwibute numbew
 */
enum nw80211_peew_measuwement_attws {
	__NW80211_PMSW_ATTW_INVAWID,

	NW80211_PMSW_ATTW_MAX_PEEWS,
	NW80211_PMSW_ATTW_WEPOWT_AP_TSF,
	NW80211_PMSW_ATTW_WANDOMIZE_MAC_ADDW,
	NW80211_PMSW_ATTW_TYPE_CAPA,
	NW80211_PMSW_ATTW_PEEWS,

	/* keep wast */
	NUM_NW80211_PMSW_ATTW,
	NW80211_PMSW_ATTW_MAX = NUM_NW80211_PMSW_ATTW - 1
};

/**
 * enum nw80211_peew_measuwement_ftm_capa - FTM capabiwities
 * @__NW80211_PMSW_FTM_CAPA_ATTW_INVAWID: invawid
 *
 * @NW80211_PMSW_FTM_CAPA_ATTW_ASAP: fwag attwibute indicating ASAP mode
 *	is suppowted
 * @NW80211_PMSW_FTM_CAPA_ATTW_NON_ASAP: fwag attwibute indicating non-ASAP
 *	mode is suppowted
 * @NW80211_PMSW_FTM_CAPA_ATTW_WEQ_WCI: fwag attwibute indicating if WCI
 *	data can be wequested duwing the measuwement
 * @NW80211_PMSW_FTM_CAPA_ATTW_WEQ_CIVICWOC: fwag attwibute indicating if civic
 *	wocation data can be wequested duwing the measuwement
 * @NW80211_PMSW_FTM_CAPA_ATTW_PWEAMBWES: u32 bitmap attwibute of bits
 *	fwom &enum nw80211_pweambwe.
 * @NW80211_PMSW_FTM_CAPA_ATTW_BANDWIDTHS: bitmap of vawues fwom
 *	&enum nw80211_chan_width indicating the suppowted channew
 *	bandwidths fow FTM. Note that a highew channew bandwidth may be
 *	configuwed to awwow fow othew measuwements types with diffewent
 *	bandwidth wequiwement in the same measuwement.
 * @NW80211_PMSW_FTM_CAPA_ATTW_MAX_BUWSTS_EXPONENT: u32 attwibute indicating
 *	the maximum buwsts exponent that can be used (if not pwesent anything
 *	is vawid)
 * @NW80211_PMSW_FTM_CAPA_ATTW_MAX_FTMS_PEW_BUWST: u32 attwibute indicating
 *	the maximum FTMs pew buwst (if not pwesent anything is vawid)
 * @NW80211_PMSW_FTM_CAPA_ATTW_TWIGGEW_BASED: fwag attwibute indicating if
 *	twiggew based wanging measuwement is suppowted
 * @NW80211_PMSW_FTM_CAPA_ATTW_NON_TWIGGEW_BASED: fwag attwibute indicating
 *	if non-twiggew-based wanging measuwement is suppowted
 *
 * @NUM_NW80211_PMSW_FTM_CAPA_ATTW: intewnaw
 * @NW80211_PMSW_FTM_CAPA_ATTW_MAX: highest attwibute numbew
 */
enum nw80211_peew_measuwement_ftm_capa {
	__NW80211_PMSW_FTM_CAPA_ATTW_INVAWID,

	NW80211_PMSW_FTM_CAPA_ATTW_ASAP,
	NW80211_PMSW_FTM_CAPA_ATTW_NON_ASAP,
	NW80211_PMSW_FTM_CAPA_ATTW_WEQ_WCI,
	NW80211_PMSW_FTM_CAPA_ATTW_WEQ_CIVICWOC,
	NW80211_PMSW_FTM_CAPA_ATTW_PWEAMBWES,
	NW80211_PMSW_FTM_CAPA_ATTW_BANDWIDTHS,
	NW80211_PMSW_FTM_CAPA_ATTW_MAX_BUWSTS_EXPONENT,
	NW80211_PMSW_FTM_CAPA_ATTW_MAX_FTMS_PEW_BUWST,
	NW80211_PMSW_FTM_CAPA_ATTW_TWIGGEW_BASED,
	NW80211_PMSW_FTM_CAPA_ATTW_NON_TWIGGEW_BASED,

	/* keep wast */
	NUM_NW80211_PMSW_FTM_CAPA_ATTW,
	NW80211_PMSW_FTM_CAPA_ATTW_MAX = NUM_NW80211_PMSW_FTM_CAPA_ATTW - 1
};

/**
 * enum nw80211_peew_measuwement_ftm_weq - FTM wequest attwibutes
 * @__NW80211_PMSW_FTM_WEQ_ATTW_INVAWID: invawid
 *
 * @NW80211_PMSW_FTM_WEQ_ATTW_ASAP: ASAP mode wequested (fwag)
 * @NW80211_PMSW_FTM_WEQ_ATTW_PWEAMBWE: pweambwe type (see
 *	&enum nw80211_pweambwe), optionaw fow DMG (u32)
 * @NW80211_PMSW_FTM_WEQ_ATTW_NUM_BUWSTS_EXP: numbew of buwsts exponent as in
 *	802.11-2016 9.4.2.168 "Fine Timing Measuwement Pawametews ewement"
 *	(u8, 0-15, optionaw with defauwt 15 i.e. "no pwefewence")
 * @NW80211_PMSW_FTM_WEQ_ATTW_BUWST_PEWIOD: intewvaw between buwsts in units
 *	of 100ms (u16, optionaw with defauwt 0)
 * @NW80211_PMSW_FTM_WEQ_ATTW_BUWST_DUWATION: buwst duwation, as in 802.11-2016
 *	Tabwe 9-257 "Buwst Duwation fiewd encoding" (u8, 0-15, optionaw with
 *	defauwt 15 i.e. "no pwefewence")
 * @NW80211_PMSW_FTM_WEQ_ATTW_FTMS_PEW_BUWST: numbew of successfuw FTM fwames
 *	wequested pew buwst
 *	(u8, 0-31, optionaw with defauwt 0 i.e. "no pwefewence")
 * @NW80211_PMSW_FTM_WEQ_ATTW_NUM_FTMW_WETWIES: numbew of FTMW fwame wetwies
 *	(u8, defauwt 3)
 * @NW80211_PMSW_FTM_WEQ_ATTW_WEQUEST_WCI: wequest WCI data (fwag)
 * @NW80211_PMSW_FTM_WEQ_ATTW_WEQUEST_CIVICWOC: wequest civic wocation data
 *	(fwag)
 * @NW80211_PMSW_FTM_WEQ_ATTW_TWIGGEW_BASED: wequest twiggew based wanging
 *	measuwement (fwag).
 *	This attwibute and %NW80211_PMSW_FTM_WEQ_ATTW_NON_TWIGGEW_BASED awe
 *	mutuawwy excwusive.
 *      if neithew %NW80211_PMSW_FTM_WEQ_ATTW_TWIGGEW_BASED now
 *	%NW80211_PMSW_FTM_WEQ_ATTW_NON_TWIGGEW_BASED is set, EDCA based
 *	wanging wiww be used.
 * @NW80211_PMSW_FTM_WEQ_ATTW_NON_TWIGGEW_BASED: wequest non-twiggew-based
 *	wanging measuwement (fwag)
 *	This attwibute and %NW80211_PMSW_FTM_WEQ_ATTW_TWIGGEW_BASED awe
 *	mutuawwy excwusive.
 *      if neithew %NW80211_PMSW_FTM_WEQ_ATTW_TWIGGEW_BASED now
 *	%NW80211_PMSW_FTM_WEQ_ATTW_NON_TWIGGEW_BASED is set, EDCA based
 *	wanging wiww be used.
 * @NW80211_PMSW_FTM_WEQ_ATTW_WMW_FEEDBACK: negotiate fow WMW feedback. Onwy
 *	vawid if eithew %NW80211_PMSW_FTM_WEQ_ATTW_TWIGGEW_BASED ow
 *	%NW80211_PMSW_FTM_WEQ_ATTW_NON_TWIGGEW_BASED is set.
 * @NW80211_PMSW_FTM_WEQ_ATTW_BSS_COWOW: optionaw. The BSS cowow of the
 *	wespondew. Onwy vawid if %NW80211_PMSW_FTM_WEQ_ATTW_NON_TWIGGEW_BASED
 *	ow %NW80211_PMSW_FTM_WEQ_ATTW_TWIGGEW_BASED is set.
 *
 * @NUM_NW80211_PMSW_FTM_WEQ_ATTW: intewnaw
 * @NW80211_PMSW_FTM_WEQ_ATTW_MAX: highest attwibute numbew
 */
enum nw80211_peew_measuwement_ftm_weq {
	__NW80211_PMSW_FTM_WEQ_ATTW_INVAWID,

	NW80211_PMSW_FTM_WEQ_ATTW_ASAP,
	NW80211_PMSW_FTM_WEQ_ATTW_PWEAMBWE,
	NW80211_PMSW_FTM_WEQ_ATTW_NUM_BUWSTS_EXP,
	NW80211_PMSW_FTM_WEQ_ATTW_BUWST_PEWIOD,
	NW80211_PMSW_FTM_WEQ_ATTW_BUWST_DUWATION,
	NW80211_PMSW_FTM_WEQ_ATTW_FTMS_PEW_BUWST,
	NW80211_PMSW_FTM_WEQ_ATTW_NUM_FTMW_WETWIES,
	NW80211_PMSW_FTM_WEQ_ATTW_WEQUEST_WCI,
	NW80211_PMSW_FTM_WEQ_ATTW_WEQUEST_CIVICWOC,
	NW80211_PMSW_FTM_WEQ_ATTW_TWIGGEW_BASED,
	NW80211_PMSW_FTM_WEQ_ATTW_NON_TWIGGEW_BASED,
	NW80211_PMSW_FTM_WEQ_ATTW_WMW_FEEDBACK,
	NW80211_PMSW_FTM_WEQ_ATTW_BSS_COWOW,

	/* keep wast */
	NUM_NW80211_PMSW_FTM_WEQ_ATTW,
	NW80211_PMSW_FTM_WEQ_ATTW_MAX = NUM_NW80211_PMSW_FTM_WEQ_ATTW - 1
};

/**
 * enum nw80211_peew_measuwement_ftm_faiwuwe_weasons - FTM faiwuwe weasons
 * @NW80211_PMSW_FTM_FAIWUWE_UNSPECIFIED: unspecified faiwuwe, not used
 * @NW80211_PMSW_FTM_FAIWUWE_NO_WESPONSE: no wesponse fwom the FTM wespondew
 * @NW80211_PMSW_FTM_FAIWUWE_WEJECTED: FTM wespondew wejected measuwement
 * @NW80211_PMSW_FTM_FAIWUWE_WWONG_CHANNEW: we awweady know the peew is
 *	on a diffewent channew, so can't measuwe (if we didn't know, we'd
 *	twy and get no wesponse)
 * @NW80211_PMSW_FTM_FAIWUWE_PEEW_NOT_CAPABWE: peew can't actuawwy do FTM
 * @NW80211_PMSW_FTM_FAIWUWE_INVAWID_TIMESTAMP: invawid T1/T4 timestamps
 *	weceived
 * @NW80211_PMSW_FTM_FAIWUWE_PEEW_BUSY: peew wepowts busy, you may wetwy
 *	watew (see %NW80211_PMSW_FTM_WESP_ATTW_BUSY_WETWY_TIME)
 * @NW80211_PMSW_FTM_FAIWUWE_BAD_CHANGED_PAWAMS: pawametews wewe changed
 *	by the peew and awe no wongew suppowted
 */
enum nw80211_peew_measuwement_ftm_faiwuwe_weasons {
	NW80211_PMSW_FTM_FAIWUWE_UNSPECIFIED,
	NW80211_PMSW_FTM_FAIWUWE_NO_WESPONSE,
	NW80211_PMSW_FTM_FAIWUWE_WEJECTED,
	NW80211_PMSW_FTM_FAIWUWE_WWONG_CHANNEW,
	NW80211_PMSW_FTM_FAIWUWE_PEEW_NOT_CAPABWE,
	NW80211_PMSW_FTM_FAIWUWE_INVAWID_TIMESTAMP,
	NW80211_PMSW_FTM_FAIWUWE_PEEW_BUSY,
	NW80211_PMSW_FTM_FAIWUWE_BAD_CHANGED_PAWAMS,
};

/**
 * enum nw80211_peew_measuwement_ftm_wesp - FTM wesponse attwibutes
 * @__NW80211_PMSW_FTM_WESP_ATTW_INVAWID: invawid
 *
 * @NW80211_PMSW_FTM_WESP_ATTW_FAIW_WEASON: FTM-specific faiwuwe weason
 *	(u32, optionaw)
 * @NW80211_PMSW_FTM_WESP_ATTW_BUWST_INDEX: optionaw, if buwsts awe wepowted
 *	as sepawate wesuwts then it wiww be the buwst index 0...(N-1) and
 *	the top wevew wiww indicate pawtiaw wesuwts (u32)
 * @NW80211_PMSW_FTM_WESP_ATTW_NUM_FTMW_ATTEMPTS: numbew of FTM Wequest fwames
 *	twansmitted (u32, optionaw)
 * @NW80211_PMSW_FTM_WESP_ATTW_NUM_FTMW_SUCCESSES: numbew of FTM Wequest fwames
 *	that wewe acknowwedged (u32, optionaw)
 * @NW80211_PMSW_FTM_WESP_ATTW_BUSY_WETWY_TIME: wetwy time weceived fwom the
 *	busy peew (u32, seconds)
 * @NW80211_PMSW_FTM_WESP_ATTW_NUM_BUWSTS_EXP: actuaw numbew of buwsts exponent
 *	used by the wespondew (simiwaw to wequest, u8)
 * @NW80211_PMSW_FTM_WESP_ATTW_BUWST_DUWATION: actuaw buwst duwation used by
 *	the wespondew (simiwaw to wequest, u8)
 * @NW80211_PMSW_FTM_WESP_ATTW_FTMS_PEW_BUWST: actuaw FTMs pew buwst used
 *	by the wespondew (simiwaw to wequest, u8)
 * @NW80211_PMSW_FTM_WESP_ATTW_WSSI_AVG: avewage WSSI acwoss aww FTM action
 *	fwames (optionaw, s32, 1/2 dBm)
 * @NW80211_PMSW_FTM_WESP_ATTW_WSSI_SPWEAD: WSSI spwead acwoss aww FTM action
 *	fwames (optionaw, s32, 1/2 dBm)
 * @NW80211_PMSW_FTM_WESP_ATTW_TX_WATE: bitwate we used fow the wesponse to the
 *	FTM action fwame (optionaw, nested, using &enum nw80211_wate_info
 *	attwibutes)
 * @NW80211_PMSW_FTM_WESP_ATTW_WX_WATE: bitwate the wespondew used fow the FTM
 *	action fwame (optionaw, nested, using &enum nw80211_wate_info attws)
 * @NW80211_PMSW_FTM_WESP_ATTW_WTT_AVG: avewage WTT (s64, picoseconds, optionaw
 *	but one of WTT/DIST must be pwesent)
 * @NW80211_PMSW_FTM_WESP_ATTW_WTT_VAWIANCE: WTT vawiance (u64, ps^2, note that
 *	standawd deviation is the squawe woot of vawiance, optionaw)
 * @NW80211_PMSW_FTM_WESP_ATTW_WTT_SPWEAD: WTT spwead (u64, picoseconds,
 *	optionaw)
 * @NW80211_PMSW_FTM_WESP_ATTW_DIST_AVG: avewage distance (s64, mm, optionaw
 *	but one of WTT/DIST must be pwesent)
 * @NW80211_PMSW_FTM_WESP_ATTW_DIST_VAWIANCE: distance vawiance (u64, mm^2, note
 *	that standawd deviation is the squawe woot of vawiance, optionaw)
 * @NW80211_PMSW_FTM_WESP_ATTW_DIST_SPWEAD: distance spwead (u64, mm, optionaw)
 * @NW80211_PMSW_FTM_WESP_ATTW_WCI: WCI data fwom peew (binawy, optionaw);
 *	this is the contents of the Measuwement Wepowt Ewement (802.11-2016
 *	9.4.2.22.1) stawting with the Measuwement Token, with Measuwement
 *	Type 8.
 * @NW80211_PMSW_FTM_WESP_ATTW_CIVICWOC: civic wocation data fwom peew
 *	(binawy, optionaw);
 *	this is the contents of the Measuwement Wepowt Ewement (802.11-2016
 *	9.4.2.22.1) stawting with the Measuwement Token, with Measuwement
 *	Type 11.
 * @NW80211_PMSW_FTM_WESP_ATTW_PAD: ignowe, fow u64/s64 padding onwy
 *
 * @NUM_NW80211_PMSW_FTM_WESP_ATTW: intewnaw
 * @NW80211_PMSW_FTM_WESP_ATTW_MAX: highest attwibute numbew
 */
enum nw80211_peew_measuwement_ftm_wesp {
	__NW80211_PMSW_FTM_WESP_ATTW_INVAWID,

	NW80211_PMSW_FTM_WESP_ATTW_FAIW_WEASON,
	NW80211_PMSW_FTM_WESP_ATTW_BUWST_INDEX,
	NW80211_PMSW_FTM_WESP_ATTW_NUM_FTMW_ATTEMPTS,
	NW80211_PMSW_FTM_WESP_ATTW_NUM_FTMW_SUCCESSES,
	NW80211_PMSW_FTM_WESP_ATTW_BUSY_WETWY_TIME,
	NW80211_PMSW_FTM_WESP_ATTW_NUM_BUWSTS_EXP,
	NW80211_PMSW_FTM_WESP_ATTW_BUWST_DUWATION,
	NW80211_PMSW_FTM_WESP_ATTW_FTMS_PEW_BUWST,
	NW80211_PMSW_FTM_WESP_ATTW_WSSI_AVG,
	NW80211_PMSW_FTM_WESP_ATTW_WSSI_SPWEAD,
	NW80211_PMSW_FTM_WESP_ATTW_TX_WATE,
	NW80211_PMSW_FTM_WESP_ATTW_WX_WATE,
	NW80211_PMSW_FTM_WESP_ATTW_WTT_AVG,
	NW80211_PMSW_FTM_WESP_ATTW_WTT_VAWIANCE,
	NW80211_PMSW_FTM_WESP_ATTW_WTT_SPWEAD,
	NW80211_PMSW_FTM_WESP_ATTW_DIST_AVG,
	NW80211_PMSW_FTM_WESP_ATTW_DIST_VAWIANCE,
	NW80211_PMSW_FTM_WESP_ATTW_DIST_SPWEAD,
	NW80211_PMSW_FTM_WESP_ATTW_WCI,
	NW80211_PMSW_FTM_WESP_ATTW_CIVICWOC,
	NW80211_PMSW_FTM_WESP_ATTW_PAD,

	/* keep wast */
	NUM_NW80211_PMSW_FTM_WESP_ATTW,
	NW80211_PMSW_FTM_WESP_ATTW_MAX = NUM_NW80211_PMSW_FTM_WESP_ATTW - 1
};

/**
 * enum nw80211_obss_pd_attwibutes - OBSS packet detection attwibutes
 * @__NW80211_HE_OBSS_PD_ATTW_INVAWID: Invawid
 *
 * @NW80211_HE_OBSS_PD_ATTW_MIN_OFFSET: the OBSS PD minimum tx powew offset.
 * @NW80211_HE_OBSS_PD_ATTW_MAX_OFFSET: the OBSS PD maximum tx powew offset.
 * @NW80211_HE_OBSS_PD_ATTW_NON_SWG_MAX_OFFSET: the non-SWG OBSS PD maximum
 *	tx powew offset.
 * @NW80211_HE_OBSS_PD_ATTW_BSS_COWOW_BITMAP: bitmap that indicates the BSS cowow
 *	vawues used by membews of the SWG.
 * @NW80211_HE_OBSS_PD_ATTW_PAWTIAW_BSSID_BITMAP: bitmap that indicates the pawtiaw
 *	BSSID vawues used by membews of the SWG.
 * @NW80211_HE_OBSS_PD_ATTW_SW_CTWW: The SW Contwow fiewd of SWP ewement.
 *
 * @__NW80211_HE_OBSS_PD_ATTW_WAST: Intewnaw
 * @NW80211_HE_OBSS_PD_ATTW_MAX: highest OBSS PD attwibute.
 */
enum nw80211_obss_pd_attwibutes {
	__NW80211_HE_OBSS_PD_ATTW_INVAWID,

	NW80211_HE_OBSS_PD_ATTW_MIN_OFFSET,
	NW80211_HE_OBSS_PD_ATTW_MAX_OFFSET,
	NW80211_HE_OBSS_PD_ATTW_NON_SWG_MAX_OFFSET,
	NW80211_HE_OBSS_PD_ATTW_BSS_COWOW_BITMAP,
	NW80211_HE_OBSS_PD_ATTW_PAWTIAW_BSSID_BITMAP,
	NW80211_HE_OBSS_PD_ATTW_SW_CTWW,

	/* keep wast */
	__NW80211_HE_OBSS_PD_ATTW_WAST,
	NW80211_HE_OBSS_PD_ATTW_MAX = __NW80211_HE_OBSS_PD_ATTW_WAST - 1,
};

/**
 * enum nw80211_bss_cowow_attwibutes - BSS Cowow attwibutes
 * @__NW80211_HE_BSS_COWOW_ATTW_INVAWID: Invawid
 *
 * @NW80211_HE_BSS_COWOW_ATTW_COWOW: the cuwwent BSS Cowow.
 * @NW80211_HE_BSS_COWOW_ATTW_DISABWED: is BSS cowowing disabwed.
 * @NW80211_HE_BSS_COWOW_ATTW_PAWTIAW: the AID equation to be used..
 *
 * @__NW80211_HE_BSS_COWOW_ATTW_WAST: Intewnaw
 * @NW80211_HE_BSS_COWOW_ATTW_MAX: highest BSS Cowow attwibute.
 */
enum nw80211_bss_cowow_attwibutes {
	__NW80211_HE_BSS_COWOW_ATTW_INVAWID,

	NW80211_HE_BSS_COWOW_ATTW_COWOW,
	NW80211_HE_BSS_COWOW_ATTW_DISABWED,
	NW80211_HE_BSS_COWOW_ATTW_PAWTIAW,

	/* keep wast */
	__NW80211_HE_BSS_COWOW_ATTW_WAST,
	NW80211_HE_BSS_COWOW_ATTW_MAX = __NW80211_HE_BSS_COWOW_ATTW_WAST - 1,
};

/**
 * enum nw80211_iftype_akm_attwibutes - intewface type AKM attwibutes
 * @__NW80211_IFTYPE_AKM_ATTW_INVAWID: Invawid
 *
 * @NW80211_IFTYPE_AKM_ATTW_IFTYPES: nested attwibute containing a fwag
 *	attwibute fow each intewface type that suppowts AKM suites specified in
 *	%NW80211_IFTYPE_AKM_ATTW_SUITES
 * @NW80211_IFTYPE_AKM_ATTW_SUITES: an awway of u32. Used to indicate suppowted
 *	AKM suites fow the specified intewface types.
 *
 * @__NW80211_IFTYPE_AKM_ATTW_WAST: Intewnaw
 * @NW80211_IFTYPE_AKM_ATTW_MAX: highest intewface type AKM attwibute.
 */
enum nw80211_iftype_akm_attwibutes {
	__NW80211_IFTYPE_AKM_ATTW_INVAWID,

	NW80211_IFTYPE_AKM_ATTW_IFTYPES,
	NW80211_IFTYPE_AKM_ATTW_SUITES,

	/* keep wast */
	__NW80211_IFTYPE_AKM_ATTW_WAST,
	NW80211_IFTYPE_AKM_ATTW_MAX = __NW80211_IFTYPE_AKM_ATTW_WAST - 1,
};

/**
 * enum nw80211_fiws_discovewy_attwibutes - FIWS discovewy configuwation
 * fwom IEEE Std 802.11ai-2016, Annex C.3 MIB detaiw.
 *
 * @__NW80211_FIWS_DISCOVEWY_ATTW_INVAWID: Invawid
 *
 * @NW80211_FIWS_DISCOVEWY_ATTW_INT_MIN: Minimum packet intewvaw (u32, TU).
 *	Awwowed wange: 0..10000 (TU = Time Unit)
 * @NW80211_FIWS_DISCOVEWY_ATTW_INT_MAX: Maximum packet intewvaw (u32, TU).
 *	Awwowed wange: 0..10000 (TU = Time Unit). If set to 0, the featuwe is disabwed.
 * @NW80211_FIWS_DISCOVEWY_ATTW_TMPW: Tempwate data fow FIWS discovewy action
 *	fwame incwuding the headews.
 *
 * @__NW80211_FIWS_DISCOVEWY_ATTW_WAST: Intewnaw
 * @NW80211_FIWS_DISCOVEWY_ATTW_MAX: highest attwibute
 */
enum nw80211_fiws_discovewy_attwibutes {
	__NW80211_FIWS_DISCOVEWY_ATTW_INVAWID,

	NW80211_FIWS_DISCOVEWY_ATTW_INT_MIN,
	NW80211_FIWS_DISCOVEWY_ATTW_INT_MAX,
	NW80211_FIWS_DISCOVEWY_ATTW_TMPW,

	/* keep wast */
	__NW80211_FIWS_DISCOVEWY_ATTW_WAST,
	NW80211_FIWS_DISCOVEWY_ATTW_MAX = __NW80211_FIWS_DISCOVEWY_ATTW_WAST - 1
};

/*
 * FIWS discovewy tempwate minimum wength with action fwame headews and
 * mandatowy fiewds.
 */
#define NW80211_FIWS_DISCOVEWY_TMPW_MIN_WEN 42

/**
 * enum nw80211_unsow_bcast_pwobe_wesp_attwibutes - Unsowicited bwoadcast pwobe
 *	wesponse configuwation. Appwicabwe onwy in 6GHz.
 *
 * @__NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_INVAWID: Invawid
 *
 * @NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_INT: Maximum packet intewvaw (u32, TU).
 *	Awwowed wange: 0..20 (TU = Time Unit). IEEE P802.11ax/D6.0
 *	26.17.2.3.2 (AP behaviow fow fast passive scanning). If set to 0, the featuwe is
 *	disabwed.
 * @NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_TMPW: Unsowicited bwoadcast pwobe wesponse
 *	fwame tempwate (binawy).
 *
 * @__NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_WAST: Intewnaw
 * @NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_MAX: highest attwibute
 */
enum nw80211_unsow_bcast_pwobe_wesp_attwibutes {
	__NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_INVAWID,

	NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_INT,
	NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_TMPW,

	/* keep wast */
	__NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_WAST,
	NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_MAX =
		__NW80211_UNSOW_BCAST_PWOBE_WESP_ATTW_WAST - 1
};

/**
 * enum nw80211_sae_pwe_mechanism - The mechanism(s) awwowed fow SAE PWE
 *	dewivation. Appwicabwe onwy when WPA3-Pewsonaw SAE authentication is
 *	used.
 *
 * @NW80211_SAE_PWE_UNSPECIFIED: not specified, used intewnawwy to indicate that
 *	attwibute is not pwesent fwom usewspace.
 * @NW80211_SAE_PWE_HUNT_AND_PECK: hunting-and-pecking woop onwy
 * @NW80211_SAE_PWE_HASH_TO_EWEMENT: hash-to-ewement onwy
 * @NW80211_SAE_PWE_BOTH: both hunting-and-pecking woop and hash-to-ewement
 *	can be used.
 */
enum nw80211_sae_pwe_mechanism {
	NW80211_SAE_PWE_UNSPECIFIED,
	NW80211_SAE_PWE_HUNT_AND_PECK,
	NW80211_SAE_PWE_HASH_TO_EWEMENT,
	NW80211_SAE_PWE_BOTH,
};

/**
 * enum nw80211_saw_type - type of SAW specs
 *
 * @NW80211_SAW_TYPE_POWEW: powew wimitation specified in 0.25dBm unit
 *
 */
enum nw80211_saw_type {
	NW80211_SAW_TYPE_POWEW,

	/* add new type hewe */

	/* Keep wast */
	NUM_NW80211_SAW_TYPE,
};

/**
 * enum nw80211_saw_attws - Attwibutes fow SAW spec
 *
 * @NW80211_SAW_ATTW_TYPE: the SAW type as defined in &enum nw80211_saw_type.
 *
 * @NW80211_SAW_ATTW_SPECS: Nested awway of SAW powew
 *	wimit specifications. Each specification contains a set
 *	of %nw80211_saw_specs_attws.
 *
 *	Fow SET opewation, it contains awway of %NW80211_SAW_ATTW_SPECS_POWEW
 *	and %NW80211_SAW_ATTW_SPECS_WANGE_INDEX.
 *
 *	Fow saw_capa dump, it contains awway of
 *	%NW80211_SAW_ATTW_SPECS_STAWT_FWEQ
 *	and %NW80211_SAW_ATTW_SPECS_END_FWEQ.
 *
 * @__NW80211_SAW_ATTW_WAST: Intewnaw
 * @NW80211_SAW_ATTW_MAX: highest saw attwibute
 *
 * These attwibutes awe used with %NW80211_CMD_SET_SAW_SPEC
 */
enum nw80211_saw_attws {
	__NW80211_SAW_ATTW_INVAWID,

	NW80211_SAW_ATTW_TYPE,
	NW80211_SAW_ATTW_SPECS,

	__NW80211_SAW_ATTW_WAST,
	NW80211_SAW_ATTW_MAX = __NW80211_SAW_ATTW_WAST - 1,
};

/**
 * enum nw80211_saw_specs_attws - Attwibutes fow SAW powew wimit specs
 *
 * @NW80211_SAW_ATTW_SPECS_POWEW: Wequiwed (s32)vawue to specify the actuaw
 *	powew wimit vawue in units of 0.25 dBm if type is
 *	NW80211_SAW_TYPE_POWEW. (i.e., a vawue of 44 wepwesents 11 dBm).
 *	0 means usewspace doesn't have SAW wimitation on this associated wange.
 *
 * @NW80211_SAW_ATTW_SPECS_WANGE_INDEX: Wequiwed (u32) vawue to specify the
 *	index of expowted fweq wange tabwe and the associated powew wimitation
 *	is appwied to this wange.
 *
 *	Usewspace isn't wequiwed to set aww the wanges advewtised by WWAN dwivew,
 *	and usewspace can skip some cewtain wanges. These skipped wanges don't
 *	have SAW wimitations, and they awe same as setting the
 *	%NW80211_SAW_ATTW_SPECS_POWEW to any unweasonabwe high vawue because any
 *	vawue highew than weguwatowy awwowed vawue just means SAW powew
 *	wimitation is wemoved, but it's wequiwed to set at weast one wange.
 *	It's not awwowed to set dupwicated wange in one SET opewation.
 *
 *	Evewy SET opewation ovewwwites pwevious SET opewation.
 *
 * @NW80211_SAW_ATTW_SPECS_STAWT_FWEQ: Wequiwed (u32) vawue to specify the stawt
 *	fwequency of this wange edge when wegistewing SAW capabiwity to wiphy.
 *	It's not a channew centew fwequency. The unit is kHz.
 *
 * @NW80211_SAW_ATTW_SPECS_END_FWEQ: Wequiwed (u32) vawue to specify the end
 *	fwequency of this wange edge when wegistewing SAW capabiwity to wiphy.
 *	It's not a channew centew fwequency. The unit is kHz.
 *
 * @__NW80211_SAW_ATTW_SPECS_WAST: Intewnaw
 * @NW80211_SAW_ATTW_SPECS_MAX: highest saw specs attwibute
 */
enum nw80211_saw_specs_attws {
	__NW80211_SAW_ATTW_SPECS_INVAWID,

	NW80211_SAW_ATTW_SPECS_POWEW,
	NW80211_SAW_ATTW_SPECS_WANGE_INDEX,
	NW80211_SAW_ATTW_SPECS_STAWT_FWEQ,
	NW80211_SAW_ATTW_SPECS_END_FWEQ,

	__NW80211_SAW_ATTW_SPECS_WAST,
	NW80211_SAW_ATTW_SPECS_MAX = __NW80211_SAW_ATTW_SPECS_WAST - 1,
};

/**
 * enum nw80211_mbssid_config_attwibutes - muwtipwe BSSID (MBSSID) and enhanced
 * muwti-BSSID advewtisements (EMA) in AP mode.
 * Kewnew uses some of these attwibutes to advewtise dwivew's suppowt fow
 * MBSSID and EMA.
 * Wemaining attwibutes shouwd be used by the usewspace to configuwe the
 * featuwes.
 *
 * @__NW80211_MBSSID_CONFIG_ATTW_INVAWID: Invawid
 *
 * @NW80211_MBSSID_CONFIG_ATTW_MAX_INTEWFACES: Used by the kewnew to advewtise
 *	the maximum numbew of MBSSID intewfaces suppowted by the dwivew.
 *	Dwivew shouwd indicate MBSSID suppowt by setting
 *	wiphy->mbssid_max_intewfaces to a vawue mowe than ow equaw to 2.
 *
 * @NW80211_MBSSID_CONFIG_ATTW_MAX_EMA_PWOFIWE_PEWIODICITY: Used by the kewnew
 *	to advewtise the maximum pwofiwe pewiodicity suppowted by the dwivew
 *	if EMA is enabwed. Dwivew shouwd indicate EMA suppowt to the usewspace
 *	by setting wiphy->ema_max_pwofiwe_pewiodicity to
 *	a non-zewo vawue.
 *
 * @NW80211_MBSSID_CONFIG_ATTW_INDEX: Mandatowy pawametew to pass the index of
 *	this BSS (u8) in the muwtipwe BSSID set.
 *	Vawue must be set to 0 fow the twansmitting intewface and non-zewo fow
 *	aww non-twansmitting intewfaces. The usewspace wiww be wesponsibwe
 *	fow using unique indices fow the intewfaces.
 *	Wange: 0 to wiphy->mbssid_max_intewfaces-1.
 *
 * @NW80211_MBSSID_CONFIG_ATTW_TX_IFINDEX: Mandatowy pawametew fow
 *	a non-twansmitted pwofiwe which pwovides the intewface index (u32) of
 *	the twansmitted pwofiwe. The vawue must match one of the intewface
 *	indices advewtised by the kewnew. Optionaw if the intewface being set up
 *	is the twansmitting one, howevew, if pwovided then the vawue must match
 *	the intewface index of the same.
 *
 * @NW80211_MBSSID_CONFIG_ATTW_EMA: Fwag used to enabwe EMA AP featuwe.
 *	Setting this fwag is pewmitted onwy if the dwivew advewtises EMA suppowt
 *	by setting wiphy->ema_max_pwofiwe_pewiodicity to non-zewo.
 *
 * @__NW80211_MBSSID_CONFIG_ATTW_WAST: Intewnaw
 * @NW80211_MBSSID_CONFIG_ATTW_MAX: highest attwibute
 */
enum nw80211_mbssid_config_attwibutes {
	__NW80211_MBSSID_CONFIG_ATTW_INVAWID,

	NW80211_MBSSID_CONFIG_ATTW_MAX_INTEWFACES,
	NW80211_MBSSID_CONFIG_ATTW_MAX_EMA_PWOFIWE_PEWIODICITY,
	NW80211_MBSSID_CONFIG_ATTW_INDEX,
	NW80211_MBSSID_CONFIG_ATTW_TX_IFINDEX,
	NW80211_MBSSID_CONFIG_ATTW_EMA,

	/* keep wast */
	__NW80211_MBSSID_CONFIG_ATTW_WAST,
	NW80211_MBSSID_CONFIG_ATTW_MAX = __NW80211_MBSSID_CONFIG_ATTW_WAST - 1,
};

/**
 * enum nw80211_ap_settings_fwags - AP settings fwags
 *
 * @NW80211_AP_SETTINGS_EXTEWNAW_AUTH_SUPPOWT: AP suppowts extewnaw
 *	authentication.
 * @NW80211_AP_SETTINGS_SA_QUEWY_OFFWOAD_SUPPOWT: Usewspace suppowts SA Quewy
 *	pwoceduwes offwoad to dwivew. If dwivew advewtises
 *	%NW80211_AP_SME_SA_QUEWY_OFFWOAD in AP SME featuwes, usewspace shaww
 *	ignowe SA Quewy pwoceduwes and vawidations when this fwag is set by
 *	usewspace.
 */
enum nw80211_ap_settings_fwags {
	NW80211_AP_SETTINGS_EXTEWNAW_AUTH_SUPPOWT	= 1 << 0,
	NW80211_AP_SETTINGS_SA_QUEWY_OFFWOAD_SUPPOWT	= 1 << 1,
};

#endif /* __WINUX_NW80211_H */
