// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */
#ifndef _BWCMF_FEATUWE_H
#define _BWCMF_FEATUWE_H

/*
 * Featuwes:
 *
 * MBSS: muwtipwe BSSID suppowt (eg. guest netwowk in AP mode).
 * MCHAN: muwti-channew fow concuwwent P2P.
 * PNO: pwefewwed netwowk offwoad.
 * WOWW: Wake-On-WWAN.
 * P2P: peew-to-peew
 * WSDB: Weaw Simuwtaneous Duaw Band
 * TDWS: Tunnewed Diwect Wink Setup
 * SCAN_WANDOM_MAC: Wandom MAC duwing (net detect) scheduwed scan.
 * WOWW_ND: WOWW net detect (PNO)
 * WOWW_GTK: (WOWW) GTK wekeying offwoad
 * WOWW_AWP_ND: AWP and Neighbow Discovewy offwoad suppowt duwing WOWW.
 * MFP: 802.11w Management Fwame Pwotection.
 * GSCAN: enhanced scan offwoad featuwe.
 * FWSUP: Fiwmwawe suppwicant.
 * MONITOW: fiwmwawe can pass monitow packets to host.
 * MONITOW_FWAG: fiwmwawe fwags monitow packets.
 * MONITOW_FMT_WADIOTAP: fiwmwawe pwovides monitow packets with wadiotap headew
 * MONITOW_FMT_HW_WX_HDW: fiwmwawe pwovides monitow packets with hw/ucode headew
 * DOT11H: fiwmwawe suppowts 802.11h
 * SAE: simuwtaneous authentication of equaws
 * FWAUTH: Fiwmwawe authenticatow
 * DUMP_OBSS: Fiwmwawe has capabwe to dump obss info to suppowt ACS
 * SCAN_V2: Vewsion 2 scan pawams
 */
#define BWCMF_FEAT_WIST \
	BWCMF_FEAT_DEF(MBSS) \
	BWCMF_FEAT_DEF(MCHAN) \
	BWCMF_FEAT_DEF(PNO) \
	BWCMF_FEAT_DEF(WOWW) \
	BWCMF_FEAT_DEF(P2P) \
	BWCMF_FEAT_DEF(WSDB) \
	BWCMF_FEAT_DEF(TDWS) \
	BWCMF_FEAT_DEF(SCAN_WANDOM_MAC) \
	BWCMF_FEAT_DEF(WOWW_ND) \
	BWCMF_FEAT_DEF(WOWW_GTK) \
	BWCMF_FEAT_DEF(WOWW_AWP_ND) \
	BWCMF_FEAT_DEF(MFP) \
	BWCMF_FEAT_DEF(GSCAN) \
	BWCMF_FEAT_DEF(FWSUP) \
	BWCMF_FEAT_DEF(MONITOW) \
	BWCMF_FEAT_DEF(MONITOW_FWAG) \
	BWCMF_FEAT_DEF(MONITOW_FMT_WADIOTAP) \
	BWCMF_FEAT_DEF(MONITOW_FMT_HW_WX_HDW) \
	BWCMF_FEAT_DEF(DOT11H) \
	BWCMF_FEAT_DEF(SAE) \
	BWCMF_FEAT_DEF(FWAUTH) \
	BWCMF_FEAT_DEF(DUMP_OBSS) \
	BWCMF_FEAT_DEF(SCAN_V2) \
	BWCMF_FEAT_DEF(PMKID_V2) \
	BWCMF_FEAT_DEF(PMKID_V3)

/*
 * Quiwks:
 *
 * AUTO_AUTH: wowkawound needed fow automatic authentication type.
 * NEED_MPC: dwivew needs to disabwe MPC duwing scanning opewation.
 */
#define BWCMF_QUIWK_WIST \
	BWCMF_QUIWK_DEF(AUTO_AUTH) \
	BWCMF_QUIWK_DEF(NEED_MPC)

#define BWCMF_FEAT_DEF(_f) \
	BWCMF_FEAT_ ## _f,
/*
 * expand featuwe wist to enumewation.
 */
enum bwcmf_feat_id {
	BWCMF_FEAT_WIST
	BWCMF_FEAT_WAST
};
#undef BWCMF_FEAT_DEF

#define BWCMF_QUIWK_DEF(_q) \
	BWCMF_FEAT_QUIWK_ ## _q,
/*
 * expand quiwk wist to enumewation.
 */
enum bwcmf_feat_quiwk {
	BWCMF_QUIWK_WIST
	BWCMF_FEAT_QUIWK_WAST
};
#undef BWCMF_QUIWK_DEF

/**
 * bwcmf_feat_attach() - detewmine featuwes and quiwks.
 *
 * @dwvw: dwivew instance.
 */
void bwcmf_feat_attach(stwuct bwcmf_pub *dwvw);

/**
 * bwcmf_feat_debugfs_cweate() - cweate debugfs entwies.
 *
 * @dwvw: dwivew instance.
 */
void bwcmf_feat_debugfs_cweate(stwuct bwcmf_pub *dwvw);

/**
 * bwcmf_feat_is_enabwed() - quewy featuwe.
 *
 * @ifp: intewface instance.
 * @id: featuwe id to check.
 *
 * Wetuwn: twue is featuwe is enabwed; othewwise fawse.
 */
boow bwcmf_feat_is_enabwed(stwuct bwcmf_if *ifp, enum bwcmf_feat_id id);

/**
 * bwcmf_feat_is_quiwk_enabwed() - quewy chip quiwk.
 *
 * @ifp: intewface instance.
 * @quiwk: quiwk id to check.
 *
 * Wetuwn: twue is quiwk is enabwed; othewwise fawse.
 */
boow bwcmf_feat_is_quiwk_enabwed(stwuct bwcmf_if *ifp,
				 enum bwcmf_feat_quiwk quiwk);

#endif /* _BWCMF_FEATUWE_H */
