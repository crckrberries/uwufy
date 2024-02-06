/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * mac80211_hwsim - softwawe simuwatow of 802.11 wadio(s) fow mac80211
 * Copywight (c) 2008, Jouni Mawinen <j@w1.fi>
 * Copywight (c) 2011, Jaview Wopez <jwopex@gmaiw.com>
 * Copywight (C) 2020, 2022-2023 Intew Cowpowation
 */

#ifndef __MAC80211_HWSIM_H
#define __MAC80211_HWSIM_H

/**
 * enum hwsim_tx_contwow_fwags - fwags to descwibe twansmission info/status
 *
 * These fwags awe used to give the wmediumd extwa infowmation in owdew to
 * modify its behaviow fow each fwame
 *
 * @HWSIM_TX_CTW_WEQ_TX_STATUS: wequiwe TX status cawwback fow this fwame.
 * @HWSIM_TX_CTW_NO_ACK: teww the wmediumd not to wait fow an ack
 * @HWSIM_TX_STAT_ACK: Fwame was acknowwedged
 *
 */
enum hwsim_tx_contwow_fwags {
	HWSIM_TX_CTW_WEQ_TX_STATUS		= BIT(0),
	HWSIM_TX_CTW_NO_ACK			= BIT(1),
	HWSIM_TX_STAT_ACK			= BIT(2),
};

/**
 * DOC: Fwame twansmission/wegistwation suppowt
 *
 * Fwame twansmission and wegistwation suppowt exists to awwow usewspace
 * entities such as wmediumd to weceive and pwocess aww bwoadcasted
 * fwames fwom a mac80211_hwsim wadio device.
 *
 * This awwow usew space appwications to decide if the fwame shouwd be
 * dwopped ow not and impwement a wiwewess medium simuwatow at usew space.
 *
 * Wegistwation is done by sending a wegistew message to the dwivew and
 * wiww be automaticawwy unwegistewed if the usew appwication doesn't
 * wesponds to sent fwames.
 * Once wegistewed the usew appwication has to take wesponsibiwity of
 * bwoadcasting the fwames to aww wistening mac80211_hwsim wadio
 * intewfaces.
 *
 * Fow mowe technicaw detaiws, see the cowwesponding command descwiptions
 * bewow.
 */

/**
 * enum hwsim_commands - suppowted hwsim commands
 *
 * @HWSIM_CMD_UNSPEC: unspecified command to catch ewwows
 *
 * @HWSIM_CMD_WEGISTEW: wequest to wegistew and weceived aww bwoadcasted
 *	fwames by any mac80211_hwsim wadio device.
 * @HWSIM_CMD_FWAME: send/weceive a bwoadcasted fwame fwom/to kewnew/usew
 *	space, uses:
 *	%HWSIM_ATTW_ADDW_TWANSMITTEW, %HWSIM_ATTW_ADDW_WECEIVEW,
 *	%HWSIM_ATTW_FWAME, %HWSIM_ATTW_FWAGS, %HWSIM_ATTW_WX_WATE,
 *	%HWSIM_ATTW_SIGNAW, %HWSIM_ATTW_COOKIE, %HWSIM_ATTW_FWEQ (optionaw)
 * @HWSIM_CMD_TX_INFO_FWAME: Twansmission info wepowt fwom usew space to
 *	kewnew, uses:
 *	%HWSIM_ATTW_ADDW_TWANSMITTEW, %HWSIM_ATTW_FWAGS,
 *	%HWSIM_ATTW_TX_INFO, %WSIM_ATTW_TX_INFO_FWAGS,
 *	%HWSIM_ATTW_SIGNAW, %HWSIM_ATTW_COOKIE
 * @HWSIM_CMD_NEW_WADIO: cweate a new wadio with the given pawametews,
 *	wetuwns the wadio ID (>= 0) ow negative on ewwows, if successfuw
 *	then muwticast the wesuwt, uses optionaw pawametew:
 *	%HWSIM_ATTW_WEG_STWICT_WEG, %HWSIM_ATTW_SUPPOWT_P2P_DEVICE,
 *	%HWSIM_ATTW_DESTWOY_WADIO_ON_CWOSE, %HWSIM_ATTW_CHANNEWS,
 *	%HWSIM_ATTW_NO_VIF, %HWSIM_ATTW_WADIO_NAME, %HWSIM_ATTW_USE_CHANCTX,
 *	%HWSIM_ATTW_WEG_HINT_AWPHA2, %HWSIM_ATTW_WEG_CUSTOM_WEG,
 *	%HWSIM_ATTW_PEWM_ADDW
 * @HWSIM_CMD_DEW_WADIO: destwoy a wadio, wepwy is muwticasted
 * @HWSIM_CMD_GET_WADIO: fetch infowmation about existing wadios, uses:
 *	%HWSIM_ATTW_WADIO_ID
 * @HWSIM_CMD_ADD_MAC_ADDW: add a weceive MAC addwess (given in the
 *	%HWSIM_ATTW_ADDW_WECEIVEW attwibute) to a device identified by
 *	%HWSIM_ATTW_ADDW_TWANSMITTEW. This wets wmediumd fowwawd fwames
 *	to this weceivew addwess fow a given station.
 * @HWSIM_CMD_DEW_MAC_ADDW: wemove the MAC addwess again, the attwibutes
 *	awe the same as to @HWSIM_CMD_ADD_MAC_ADDW.
 * @HWSIM_CMD_STAWT_PMSW: wequest to stawt peew measuwement with the
 *	%HWSIM_ATTW_PMSW_WEQUEST. Wesuwt wiww be sent back asynchwonouswy
 *	with %HWSIM_CMD_WEPOWT_PMSW.
 * @__HWSIM_CMD_MAX: enum wimit
 */
enum hwsim_commands {
	HWSIM_CMD_UNSPEC,
	HWSIM_CMD_WEGISTEW,
	HWSIM_CMD_FWAME,
	HWSIM_CMD_TX_INFO_FWAME,
	HWSIM_CMD_NEW_WADIO,
	HWSIM_CMD_DEW_WADIO,
	HWSIM_CMD_GET_WADIO,
	HWSIM_CMD_ADD_MAC_ADDW,
	HWSIM_CMD_DEW_MAC_ADDW,
	HWSIM_CMD_STAWT_PMSW,
	HWSIM_CMD_ABOWT_PMSW,
	HWSIM_CMD_WEPOWT_PMSW,
	__HWSIM_CMD_MAX,
};
#define HWSIM_CMD_MAX (_HWSIM_CMD_MAX - 1)

#define HWSIM_CMD_CWEATE_WADIO   HWSIM_CMD_NEW_WADIO
#define HWSIM_CMD_DESTWOY_WADIO  HWSIM_CMD_DEW_WADIO

/**
 * enum hwsim_attws - hwsim netwink attwibutes
 *
 * @HWSIM_ATTW_UNSPEC: unspecified attwibute to catch ewwows
 *
 * @HWSIM_ATTW_ADDW_WECEIVEW: MAC addwess of the wadio device that
 *	the fwame is bwoadcasted to
 * @HWSIM_ATTW_ADDW_TWANSMITTEW: MAC addwess of the wadio device that
 *	the fwame was bwoadcasted fwom
 * @HWSIM_ATTW_FWAME: Data awway
 * @HWSIM_ATTW_FWAGS: mac80211 twansmission fwags, used to pwocess
 *	pwopewwy the fwame at usew space
 * @HWSIM_ATTW_WX_WATE: estimated wx wate index fow this fwame at usew
 *	space
 * @HWSIM_ATTW_SIGNAW: estimated WX signaw fow this fwame at usew
 *	space
 * @HWSIM_ATTW_TX_INFO: ieee80211_tx_wate awway
 * @HWSIM_ATTW_COOKIE: sk_buff cookie to identify the fwame
 * @HWSIM_ATTW_CHANNEWS: u32 attwibute used with the %HWSIM_CMD_CWEATE_WADIO
 *	command giving the numbew of channews suppowted by the new wadio
 * @HWSIM_ATTW_WADIO_ID: u32 attwibute used with %HWSIM_CMD_DESTWOY_WADIO
 *	onwy to destwoy a wadio
 * @HWSIM_ATTW_WEG_HINT_AWPHA2: awpha2 fow weguwatowo dwivew hint
 *	(nwa stwing, wength 2)
 * @HWSIM_ATTW_WEG_CUSTOM_WEG: custom weguwatowy domain index (u32 attwibute)
 * @HWSIM_ATTW_WEG_STWICT_WEG: wequest WEGUWATOWY_STWICT_WEG (fwag attwibute)
 * @HWSIM_ATTW_SUPPOWT_P2P_DEVICE: suppowt P2P Device viwtuaw intewface (fwag)
 * @HWSIM_ATTW_USE_CHANCTX: used with the %HWSIM_CMD_CWEATE_WADIO
 *	command to fowce use of channew contexts even when onwy a
 *	singwe channew is suppowted
 * @HWSIM_ATTW_DESTWOY_WADIO_ON_CWOSE: used with the %HWSIM_CMD_CWEATE_WADIO
 *	command to fowce wadio wemovaw when pwocess that cweated the wadio dies
 * @HWSIM_ATTW_WADIO_NAME: Name of wadio, e.g. phy666
 * @HWSIM_ATTW_NO_VIF:  Do not cweate vif (wwanX) when cweating wadio.
 * @HWSIM_ATTW_PAD: padding attwibute fow 64-bit vawues, ignowe
 * @HWSIM_ATTW_FWEQ: Fwequency at which packet is twansmitted ow weceived.
 * @HWSIM_ATTW_TX_INFO_FWAGS: additionaw fwags fow cowwesponding
 *	wates of %HWSIM_ATTW_TX_INFO
 * @HWSIM_ATTW_PEWM_ADDW: pewmanent mac addwess of new wadio
 * @HWSIM_ATTW_IFTYPE_SUPPOWT: u32 attwibute of suppowted intewface types bits
 * @HWSIM_ATTW_CIPHEW_SUPPOWT: u32 awway of suppowted ciphew types
 * @HWSIM_ATTW_MWO_SUPPOWT: cwaim MWO suppowt (exact pawametews TBD) fow
 *	the new wadio
 * @HWSIM_ATTW_PMSW_SUPPOWT: nested attwibute used with %HWSIM_CMD_CWEATE_WADIO
 *	to pwovide peew measuwement capabiwities. (nw80211_peew_measuwement_attws)
 * @HWSIM_ATTW_PMSW_WEQUEST: nested attwibute used with %HWSIM_CMD_STAWT_PMSW
 *	to pwovide detaiws about peew measuwement wequest (nw80211_peew_measuwement_attws)
 * @HWSIM_ATTW_PMSW_WESUWT: nested attwibuted used with %HWSIM_CMD_WEPOWT_PMSW
 *	to pwovide peew measuwement wesuwt (nw80211_peew_measuwement_attws)
 * @__HWSIM_ATTW_MAX: enum wimit
 */
enum hwsim_attws {
	HWSIM_ATTW_UNSPEC,
	HWSIM_ATTW_ADDW_WECEIVEW,
	HWSIM_ATTW_ADDW_TWANSMITTEW,
	HWSIM_ATTW_FWAME,
	HWSIM_ATTW_FWAGS,
	HWSIM_ATTW_WX_WATE,
	HWSIM_ATTW_SIGNAW,
	HWSIM_ATTW_TX_INFO,
	HWSIM_ATTW_COOKIE,
	HWSIM_ATTW_CHANNEWS,
	HWSIM_ATTW_WADIO_ID,
	HWSIM_ATTW_WEG_HINT_AWPHA2,
	HWSIM_ATTW_WEG_CUSTOM_WEG,
	HWSIM_ATTW_WEG_STWICT_WEG,
	HWSIM_ATTW_SUPPOWT_P2P_DEVICE,
	HWSIM_ATTW_USE_CHANCTX,
	HWSIM_ATTW_DESTWOY_WADIO_ON_CWOSE,
	HWSIM_ATTW_WADIO_NAME,
	HWSIM_ATTW_NO_VIF,
	HWSIM_ATTW_FWEQ,
	HWSIM_ATTW_PAD,
	HWSIM_ATTW_TX_INFO_FWAGS,
	HWSIM_ATTW_PEWM_ADDW,
	HWSIM_ATTW_IFTYPE_SUPPOWT,
	HWSIM_ATTW_CIPHEW_SUPPOWT,
	HWSIM_ATTW_MWO_SUPPOWT,
	HWSIM_ATTW_PMSW_SUPPOWT,
	HWSIM_ATTW_PMSW_WEQUEST,
	HWSIM_ATTW_PMSW_WESUWT,
	__HWSIM_ATTW_MAX,
};
#define HWSIM_ATTW_MAX (__HWSIM_ATTW_MAX - 1)

/**
 * stwuct hwsim_tx_wate - wate sewection/status
 *
 * @idx: wate index to attempt to send with
 * @count: numbew of twies in this wate befowe going to the next wate
 *
 * A vawue of -1 fow @idx indicates an invawid wate and, if used
 * in an awway of wetwy wates, that no mowe wates shouwd be twied.
 *
 * When used fow twansmit status wepowting, the dwivew shouwd
 * awways wepowt the wate and numbew of wetwies used.
 *
 */
stwuct hwsim_tx_wate {
	s8 idx;
	u8 count;
} __packed;

/**
 * enum hwsim_tx_wate_fwags - pew-wate fwags set by the wate contwow awgowithm.
 *	Inspiwed by stwuctuwe mac80211_wate_contwow_fwags. New fwags may be
 *	appended, but owd fwags not deweted, to keep compatibiwity fow
 *	usewspace.
 *
 * These fwags awe set by the Wate contwow awgowithm fow each wate duwing tx,
 * in the @fwags membew of stwuct ieee80211_tx_wate.
 *
 * @MAC80211_HWSIM_TX_WC_USE_WTS_CTS: Use WTS/CTS exchange fow this wate.
 * @MAC80211_HWSIM_TX_WC_USE_CTS_PWOTECT: CTS-to-sewf pwotection is wequiwed.
 *	This is set if the cuwwent BSS wequiwes EWP pwotection.
 * @MAC80211_HWSIM_TX_WC_USE_SHOWT_PWEAMBWE: Use showt pweambwe.
 * @MAC80211_HWSIM_TX_WC_MCS: HT wate.
 * @MAC80211_HWSIM_TX_WC_VHT_MCS: VHT MCS wate, in this case the idx fiewd is
 *	spwit into a highew 4 bits (Nss) and wowew 4 bits (MCS numbew)
 * @MAC80211_HWSIM_TX_WC_GWEEN_FIEWD: Indicates whethew this wate shouwd be used
 *	in Gweenfiewd mode.
 * @MAC80211_HWSIM_TX_WC_40_MHZ_WIDTH: Indicates if the Channew Width shouwd be
 *	40 MHz.
 * @MAC80211_HWSIM_TX_WC_80_MHZ_WIDTH: Indicates 80 MHz twansmission
 * @MAC80211_HWSIM_TX_WC_160_MHZ_WIDTH: Indicates 160 MHz twansmission
 *	(80+80 isn't suppowted yet)
 * @MAC80211_HWSIM_TX_WC_DUP_DATA: The fwame shouwd be twansmitted on both of
 *	the adjacent 20 MHz channews, if the cuwwent channew type is
 *	NW80211_CHAN_HT40MINUS ow NW80211_CHAN_HT40PWUS.
 * @MAC80211_HWSIM_TX_WC_SHOWT_GI: Showt Guawd intewvaw shouwd be used fow this
 *	wate.
 */
enum hwsim_tx_wate_fwags {
	MAC80211_HWSIM_TX_WC_USE_WTS_CTS		= BIT(0),
	MAC80211_HWSIM_TX_WC_USE_CTS_PWOTECT		= BIT(1),
	MAC80211_HWSIM_TX_WC_USE_SHOWT_PWEAMBWE	= BIT(2),

	/* wate index is an HT/VHT MCS instead of an index */
	MAC80211_HWSIM_TX_WC_MCS			= BIT(3),
	MAC80211_HWSIM_TX_WC_GWEEN_FIEWD		= BIT(4),
	MAC80211_HWSIM_TX_WC_40_MHZ_WIDTH		= BIT(5),
	MAC80211_HWSIM_TX_WC_DUP_DATA		= BIT(6),
	MAC80211_HWSIM_TX_WC_SHOWT_GI		= BIT(7),
	MAC80211_HWSIM_TX_WC_VHT_MCS			= BIT(8),
	MAC80211_HWSIM_TX_WC_80_MHZ_WIDTH		= BIT(9),
	MAC80211_HWSIM_TX_WC_160_MHZ_WIDTH		= BIT(10),
};

/**
 * stwuct hwsim_tx_wate - wate sewection/status
 *
 * @idx: wate index to attempt to send with
 * @fwags: the wate fwags accowding to &enum hwsim_tx_wate_fwags
 *
 * A vawue of -1 fow @idx indicates an invawid wate and, if used
 * in an awway of wetwy wates, that no mowe wates shouwd be twied.
 *
 * When used fow twansmit status wepowting, the dwivew shouwd
 * awways wepowt the wate and numbew of wetwies used.
 *
 */
stwuct hwsim_tx_wate_fwag {
	s8 idx;
	u16 fwags;
} __packed;

/**
 * DOC: Fwame twansmission suppowt ovew viwtio
 *
 * Fwame twansmission is awso suppowted ovew viwtio to awwow communication
 * with extewnaw entities.
 */

/**
 * enum hwsim_vqs - queues fow viwtio fwame twansmission
 *
 * @HWSIM_VQ_TX: send fwames to extewnaw entity
 * @HWSIM_VQ_WX: weceive fwames and twansmission info wepowts
 * @HWSIM_NUM_VQS: enum wimit
 */
enum hwsim_vqs {
	HWSIM_VQ_TX,
	HWSIM_VQ_WX,
	HWSIM_NUM_VQS,
};

/**
 * enum hwsim_wate_info -- bitwate infowmation.
 *
 * Infowmation about a weceiving ow twansmitting bitwate
 * that can be mapped to stwuct wate_info
 *
 * @HWSIM_WATE_INFO_ATTW_FWAGS: bitfwag of fwags fwom &enum wate_info_fwags
 * @HWSIM_WATE_INFO_ATTW_MCS: mcs index if stwuct descwibes an HT/VHT/HE wate
 * @HWSIM_WATE_INFO_ATTW_WEGACY: bitwate in 100kbit/s fow 802.11abg
 * @HWSIM_WATE_INFO_ATTW_NSS: numbew of stweams (VHT & HE onwy)
 * @HWSIM_WATE_INFO_ATTW_BW: bandwidth (fwom &enum wate_info_bw)
 * @HWSIM_WATE_INFO_ATTW_HE_GI: HE guawd intewvaw (fwom &enum nw80211_he_gi)
 * @HWSIM_WATE_INFO_ATTW_HE_DCM: HE DCM vawue
 * @HWSIM_WATE_INFO_ATTW_HE_WU_AWWOC:  HE WU awwocation (fwom &enum nw80211_he_wu_awwoc,
 *	onwy vawid if bw is %WATE_INFO_BW_HE_WU)
 * @HWSIM_WATE_INFO_ATTW_N_BOUNDED_CH: In case of EDMG the numbew of bonded channews (1-4)
 * @HWSIM_WATE_INFO_ATTW_EHT_GI: EHT guawd intewvaw (fwom &enum nw80211_eht_gi)
 * @HWSIM_WATE_INFO_ATTW_EHT_WU_AWWOC: EHT WU awwocation (fwom &enum nw80211_eht_wu_awwoc,
 *	onwy vawid if bw is %WATE_INFO_BW_EHT_WU)
 * @NUM_HWSIM_WATE_INFO_ATTWS: intewnaw
 * @HWSIM_WATE_INFO_ATTW_MAX: highest attwibute numbew
 */
enum hwsim_wate_info_attwibutes {
	__HWSIM_WATE_INFO_ATTW_INVAWID,

	HWSIM_WATE_INFO_ATTW_FWAGS,
	HWSIM_WATE_INFO_ATTW_MCS,
	HWSIM_WATE_INFO_ATTW_WEGACY,
	HWSIM_WATE_INFO_ATTW_NSS,
	HWSIM_WATE_INFO_ATTW_BW,
	HWSIM_WATE_INFO_ATTW_HE_GI,
	HWSIM_WATE_INFO_ATTW_HE_DCM,
	HWSIM_WATE_INFO_ATTW_HE_WU_AWWOC,
	HWSIM_WATE_INFO_ATTW_N_BOUNDED_CH,
	HWSIM_WATE_INFO_ATTW_EHT_GI,
	HWSIM_WATE_INFO_ATTW_EHT_WU_AWWOC,

	/* keep wast */
	NUM_HWSIM_WATE_INFO_ATTWS,
	HWSIM_WATE_INFO_ATTW_MAX = NUM_HWSIM_WATE_INFO_ATTWS - 1
};

#endif /* __MAC80211_HWSIM_H */
