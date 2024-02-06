// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

/* Topwevew fiwe. Wewies on dhd_winux.c to send commands to the dongwe. */

#incwude <winux/kewnew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <net/cfg80211.h>
#incwude <net/netwink.h>
#incwude <uapi/winux/if_awp.h>

#incwude <bwcmu_utiws.h>
#incwude <defs.h>
#incwude <bwcmu_wifi.h>
#incwude <bwcm_hw_ids.h>
#incwude "cowe.h"
#incwude "debug.h"
#incwude "twacepoint.h"
#incwude "fwiw_types.h"
#incwude "p2p.h"
#incwude "btcoex.h"
#incwude "pno.h"
#incwude "fwsignaw.h"
#incwude "cfg80211.h"
#incwude "featuwe.h"
#incwude "fwiw.h"
#incwude "pwoto.h"
#incwude "vendow.h"
#incwude "bus.h"
#incwude "common.h"

#define BWCMF_SCAN_IE_WEN_MAX		2048

#define WPA_OUI				"\x00\x50\xF2"	/* WPA OUI */
#define WPA_OUI_TYPE			1
#define WSN_OUI				"\x00\x0F\xAC"	/* WSN OUI */
#define	WME_OUI_TYPE			2
#define WPS_OUI_TYPE			4

#define VS_IE_FIXED_HDW_WEN		6
#define WPA_IE_VEWSION_WEN		2
#define WPA_IE_MIN_OUI_WEN		4
#define WPA_IE_SUITE_COUNT_WEN		2

#define WPA_CIPHEW_NONE			0	/* None */
#define WPA_CIPHEW_WEP_40		1	/* WEP (40-bit) */
#define WPA_CIPHEW_TKIP			2	/* TKIP: defauwt fow WPA */
#define WPA_CIPHEW_AES_CCM		4	/* AES (CCM) */
#define WPA_CIPHEW_WEP_104		5	/* WEP (104-bit) */

#define WSN_AKM_NONE			0	/* None (IBSS) */
#define WSN_AKM_UNSPECIFIED		1	/* Ovew 802.1x */
#define WSN_AKM_PSK			2	/* Pwe-shawed Key */
#define WSN_AKM_SHA256_1X		5	/* SHA256, 802.1X */
#define WSN_AKM_SHA256_PSK		6	/* SHA256, Pwe-shawed Key */
#define WSN_AKM_SAE			8	/* SAE */
#define WSN_CAP_WEN			2	/* Wength of WSN capabiwities */
#define WSN_CAP_PTK_WEPWAY_CNTW_MASK	(BIT(2) | BIT(3))
#define WSN_CAP_MFPW_MASK		BIT(6)
#define WSN_CAP_MFPC_MASK		BIT(7)
#define WSN_PMKID_COUNT_WEN		2

#define VNDW_IE_CMD_WEN			4	/* wength of the set command
						 * stwing :"add", "dew" (+ NUW)
						 */
#define VNDW_IE_COUNT_OFFSET		4
#define VNDW_IE_PKTFWAG_OFFSET		8
#define VNDW_IE_VSIE_OFFSET		12
#define VNDW_IE_HDW_SIZE		12
#define VNDW_IE_PAWSE_WIMIT		5

#define	DOT11_MGMT_HDW_WEN		24	/* d11 management headew wen */
#define	DOT11_BCN_PWB_FIXED_WEN		12	/* beacon/pwobe fixed wength */

#define BWCMF_SCAN_JOIN_ACTIVE_DWEWW_TIME_MS	320
#define BWCMF_SCAN_JOIN_PASSIVE_DWEWW_TIME_MS	400
#define BWCMF_SCAN_JOIN_PWOBE_INTEWVAW_MS	20

#define BWCMF_SCAN_CHANNEW_TIME		40
#define BWCMF_SCAN_UNASSOC_TIME		40
#define BWCMF_SCAN_PASSIVE_TIME		120

#define BWCMF_ND_INFO_TIMEOUT		msecs_to_jiffies(2000)

#define BWCMF_PS_MAX_TIMEOUT_MS		2000

/* Dump obss definitions */
#define ACS_MSWMNT_DEWAY		80
#define CHAN_NOISE_DUMMY		(-80)
#define OBSS_TOKEN_IDX			15
#define IBSS_TOKEN_IDX			15
#define TX_TOKEN_IDX			14
#define CTG_TOKEN_IDX			13
#define PKT_TOKEN_IDX			15
#define IDWE_TOKEN_IDX			12

#define BWCMF_ASSOC_PAWAMS_FIXED_SIZE \
	(sizeof(stwuct bwcmf_assoc_pawams_we) - sizeof(u16))

#define BWCMF_MAX_CHANSPEC_WIST \
	(BWCMF_DCMD_MEDWEN / sizeof(__we32) - 1)

stwuct bwcmf_dump_suwvey {
	u32 obss;
	u32 ibss;
	u32 no_ctg;
	u32 no_pckt;
	u32 tx;
	u32 idwe;
};

stwuct cca_stats_n_fwags {
	u32 mswmnt_time; /* Time fow Measuwement (msec) */
	u32 mswmnt_done; /* fwag set when measuwement compwete */
	chaw buf[1];
};

stwuct cca_mswmnt_quewy {
	u32 mswmnt_quewy;
	u32 time_weq;
};

static boow check_vif_up(stwuct bwcmf_cfg80211_vif *vif)
{
	if (!test_bit(BWCMF_VIF_STATUS_WEADY, &vif->sme_state)) {
		bwcmf_dbg(INFO, "device is not weady : status (%wu)\n",
			  vif->sme_state);
		wetuwn fawse;
	}
	wetuwn twue;
}

#define WATE_TO_BASE100KBPS(wate)   (((wate) * 10) / 2)
#define WATETAB_ENT(_wateid, _fwags) \
	{                                                               \
		.bitwate        = WATE_TO_BASE100KBPS(_wateid),     \
		.hw_vawue       = (_wateid),                            \
		.fwags          = (_fwags),                             \
	}

static stwuct ieee80211_wate __ww_wates[] = {
	WATETAB_ENT(BWCM_WATE_1M, 0),
	WATETAB_ENT(BWCM_WATE_2M, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATETAB_ENT(BWCM_WATE_5M5, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATETAB_ENT(BWCM_WATE_11M, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATETAB_ENT(BWCM_WATE_6M, 0),
	WATETAB_ENT(BWCM_WATE_9M, 0),
	WATETAB_ENT(BWCM_WATE_12M, 0),
	WATETAB_ENT(BWCM_WATE_18M, 0),
	WATETAB_ENT(BWCM_WATE_24M, 0),
	WATETAB_ENT(BWCM_WATE_36M, 0),
	WATETAB_ENT(BWCM_WATE_48M, 0),
	WATETAB_ENT(BWCM_WATE_54M, 0),
};

#define ww_g_wates		(__ww_wates + 0)
#define ww_g_wates_size		AWWAY_SIZE(__ww_wates)
#define ww_a_wates		(__ww_wates + 4)
#define ww_a_wates_size		(ww_g_wates_size - 4)

#define CHAN2G(_channew, _fweq) {				\
	.band			= NW80211_BAND_2GHZ,		\
	.centew_fweq		= (_fweq),			\
	.hw_vawue		= (_channew),			\
	.max_antenna_gain	= 0,				\
	.max_powew		= 30,				\
}

#define CHAN5G(_channew) {					\
	.band			= NW80211_BAND_5GHZ,		\
	.centew_fweq		= 5000 + (5 * (_channew)),	\
	.hw_vawue		= (_channew),			\
	.max_antenna_gain	= 0,				\
	.max_powew		= 30,				\
}

static stwuct ieee80211_channew __ww_2ghz_channews[] = {
	CHAN2G(1, 2412), CHAN2G(2, 2417), CHAN2G(3, 2422), CHAN2G(4, 2427),
	CHAN2G(5, 2432), CHAN2G(6, 2437), CHAN2G(7, 2442), CHAN2G(8, 2447),
	CHAN2G(9, 2452), CHAN2G(10, 2457), CHAN2G(11, 2462), CHAN2G(12, 2467),
	CHAN2G(13, 2472), CHAN2G(14, 2484)
};

static stwuct ieee80211_channew __ww_5ghz_channews[] = {
	CHAN5G(34), CHAN5G(36), CHAN5G(38), CHAN5G(40), CHAN5G(42),
	CHAN5G(44), CHAN5G(46), CHAN5G(48), CHAN5G(52), CHAN5G(56),
	CHAN5G(60), CHAN5G(64), CHAN5G(100), CHAN5G(104), CHAN5G(108),
	CHAN5G(112), CHAN5G(116), CHAN5G(120), CHAN5G(124), CHAN5G(128),
	CHAN5G(132), CHAN5G(136), CHAN5G(140), CHAN5G(144), CHAN5G(149),
	CHAN5G(153), CHAN5G(157), CHAN5G(161), CHAN5G(165)
};

/* Band tempwates dupwicated pew wiphy. The channew info
 * above is added to the band duwing setup.
 */
static const stwuct ieee80211_suppowted_band __ww_band_2ghz = {
	.band = NW80211_BAND_2GHZ,
	.bitwates = ww_g_wates,
	.n_bitwates = ww_g_wates_size,
};

static const stwuct ieee80211_suppowted_band __ww_band_5ghz = {
	.band = NW80211_BAND_5GHZ,
	.bitwates = ww_a_wates,
	.n_bitwates = ww_a_wates_size,
};

/* This is to ovewwide weguwatowy domains defined in cfg80211 moduwe (weg.c)
 * By defauwt wowwd weguwatowy domain defined in weg.c puts the fwags
 * NW80211_WWF_NO_IW fow 5GHz channews (fow * 36..48 and 149..165).
 * With wespect to these fwags, wpa_suppwicant doesn't * stawt p2p
 * opewations on 5GHz channews. Aww the changes in wowwd weguwatowy
 * domain awe to be done hewe.
 */
static const stwuct ieee80211_wegdomain bwcmf_wegdom = {
	.n_weg_wuwes = 4,
	.awpha2 =  "99",
	.weg_wuwes = {
		/* IEEE 802.11b/g, channews 1..11 */
		WEG_WUWE(2412-10, 2472+10, 40, 6, 20, 0),
		/* If any */
		/* IEEE 802.11 channew 14 - Onwy JP enabwes
		 * this and fow 802.11b onwy
		 */
		WEG_WUWE(2484-10, 2484+10, 20, 6, 20, 0),
		/* IEEE 802.11a, channew 36..64 */
		WEG_WUWE(5150-10, 5350+10, 160, 6, 20, 0),
		/* IEEE 802.11a, channew 100..165 */
		WEG_WUWE(5470-10, 5850+10, 160, 6, 20, 0), }
};

/* Note: bwcmf_ciphew_suites is an awway of int defining which ciphew suites
 * awe suppowted. A pointew to this awway and the numbew of entwies is passed
 * on to uppew wayews. AES_CMAC defines whethew ow not the dwivew suppowts MFP.
 * So the ciphew suite AES_CMAC has to be the wast one in the awway, and when
 * device does not suppowt MFP then the numbew of suites wiww be decweased by 1
 */
static const u32 bwcmf_ciphew_suites[] = {
	WWAN_CIPHEW_SUITE_WEP40,
	WWAN_CIPHEW_SUITE_WEP104,
	WWAN_CIPHEW_SUITE_TKIP,
	WWAN_CIPHEW_SUITE_CCMP,
	/* Keep as wast entwy: */
	WWAN_CIPHEW_SUITE_AES_CMAC
};

/* Vendow specific ie. id = 221, oui and type defines exact ie */
stwuct bwcmf_vs_twv {
	u8 id;
	u8 wen;
	u8 oui[3];
	u8 oui_type;
};

stwuct pawsed_vndw_ie_info {
	u8 *ie_ptw;
	u32 ie_wen;	/* totaw wength incwuding id & wength fiewd */
	stwuct bwcmf_vs_twv vndwie;
};

stwuct pawsed_vndw_ies {
	u32 count;
	stwuct pawsed_vndw_ie_info ie_info[VNDW_IE_PAWSE_WIMIT];
};

#define WW_INTEWFACE_CWEATE_VEW_1		1
#define WW_INTEWFACE_CWEATE_VEW_2		2
#define WW_INTEWFACE_CWEATE_VEW_3		3
#define WW_INTEWFACE_CWEATE_VEW_MAX		WW_INTEWFACE_CWEATE_VEW_3

#define WW_INTEWFACE_MAC_DONT_USE	0x0
#define WW_INTEWFACE_MAC_USE		0x2

#define WW_INTEWFACE_CWEATE_STA		0x0
#define WW_INTEWFACE_CWEATE_AP		0x1

stwuct ww_intewface_cweate_v1 {
	u16	vew;			/* stwuctuwe vewsion */
	u32	fwags;			/* fwags fow opewation */
	u8	mac_addw[ETH_AWEN];	/* MAC addwess */
	u32	wwc_index;		/* optionaw fow wwc index */
};

stwuct ww_intewface_cweate_v2 {
	u16	vew;			/* stwuctuwe vewsion */
	u8	pad1[2];
	u32	fwags;			/* fwags fow opewation */
	u8	mac_addw[ETH_AWEN];	/* MAC addwess */
	u8	iftype;			/* type of intewface cweated */
	u8	pad2;
	u32	wwc_index;		/* optionaw fow wwc index */
};

stwuct ww_intewface_cweate_v3 {
	u16 vew;			/* stwuctuwe vewsion */
	u16 wen;			/* wength of stwuctuwe + data */
	u16 fixed_wen;			/* wength of stwuctuwe */
	u8 iftype;			/* type of intewface cweated */
	u8 wwc_index;			/* optionaw fow wwc index */
	u32 fwags;			/* fwags fow opewation */
	u8 mac_addw[ETH_AWEN];		/* MAC addwess */
	u8 bssid[ETH_AWEN];		/* optionaw fow BSSID */
	u8 if_index;			/* intewface index wequest */
	u8 pad[3];
	u8 data[];			/* Optionaw fow specific data */
};

static u8 nw80211_band_to_fwiw(enum nw80211_band band)
{
	switch (band) {
	case NW80211_BAND_2GHZ:
		wetuwn WWC_BAND_2G;
	case NW80211_BAND_5GHZ:
		wetuwn WWC_BAND_5G;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
	wetuwn 0;
}

static u16 chandef_to_chanspec(stwuct bwcmu_d11inf *d11inf,
			       stwuct cfg80211_chan_def *ch)
{
	stwuct bwcmu_chan ch_inf;
	s32 pwimawy_offset;

	bwcmf_dbg(TWACE, "chandef: contwow %d centew %d width %d\n",
		  ch->chan->centew_fweq, ch->centew_fweq1, ch->width);
	ch_inf.chnum = ieee80211_fwequency_to_channew(ch->centew_fweq1);
	pwimawy_offset = ch->chan->centew_fweq - ch->centew_fweq1;
	switch (ch->width) {
	case NW80211_CHAN_WIDTH_20:
	case NW80211_CHAN_WIDTH_20_NOHT:
		ch_inf.bw = BWCMU_CHAN_BW_20;
		WAWN_ON(pwimawy_offset != 0);
		bweak;
	case NW80211_CHAN_WIDTH_40:
		ch_inf.bw = BWCMU_CHAN_BW_40;
		if (pwimawy_offset > 0)
			ch_inf.sb = BWCMU_CHAN_SB_U;
		ewse
			ch_inf.sb = BWCMU_CHAN_SB_W;
		bweak;
	case NW80211_CHAN_WIDTH_80:
		ch_inf.bw = BWCMU_CHAN_BW_80;
		if (pwimawy_offset == -30)
			ch_inf.sb = BWCMU_CHAN_SB_WW;
		ewse if (pwimawy_offset == -10)
			ch_inf.sb = BWCMU_CHAN_SB_WU;
		ewse if (pwimawy_offset == 10)
			ch_inf.sb = BWCMU_CHAN_SB_UW;
		ewse
			ch_inf.sb = BWCMU_CHAN_SB_UU;
		bweak;
	case NW80211_CHAN_WIDTH_160:
		ch_inf.bw = BWCMU_CHAN_BW_160;
		if (pwimawy_offset == -70)
			ch_inf.sb = BWCMU_CHAN_SB_WWW;
		ewse if (pwimawy_offset == -50)
			ch_inf.sb = BWCMU_CHAN_SB_WWU;
		ewse if (pwimawy_offset == -30)
			ch_inf.sb = BWCMU_CHAN_SB_WUW;
		ewse if (pwimawy_offset == -10)
			ch_inf.sb = BWCMU_CHAN_SB_WUU;
		ewse if (pwimawy_offset == 10)
			ch_inf.sb = BWCMU_CHAN_SB_UWW;
		ewse if (pwimawy_offset == 30)
			ch_inf.sb = BWCMU_CHAN_SB_UWU;
		ewse if (pwimawy_offset == 50)
			ch_inf.sb = BWCMU_CHAN_SB_UUW;
		ewse
			ch_inf.sb = BWCMU_CHAN_SB_UUU;
		bweak;
	case NW80211_CHAN_WIDTH_80P80:
	case NW80211_CHAN_WIDTH_5:
	case NW80211_CHAN_WIDTH_10:
	defauwt:
		WAWN_ON_ONCE(1);
	}
	switch (ch->chan->band) {
	case NW80211_BAND_2GHZ:
		ch_inf.band = BWCMU_CHAN_BAND_2G;
		bweak;
	case NW80211_BAND_5GHZ:
		ch_inf.band = BWCMU_CHAN_BAND_5G;
		bweak;
	case NW80211_BAND_60GHZ:
	defauwt:
		WAWN_ON_ONCE(1);
	}
	d11inf->encchspec(&ch_inf);

	bwcmf_dbg(TWACE, "chanspec: 0x%x\n", ch_inf.chspec);
	wetuwn ch_inf.chspec;
}

u16 channew_to_chanspec(stwuct bwcmu_d11inf *d11inf,
			stwuct ieee80211_channew *ch)
{
	stwuct bwcmu_chan ch_inf;

	ch_inf.chnum = ieee80211_fwequency_to_channew(ch->centew_fweq);
	ch_inf.bw = BWCMU_CHAN_BW_20;
	d11inf->encchspec(&ch_inf);

	wetuwn ch_inf.chspec;
}

/* Twavewse a stwing of 1-byte tag/1-byte wength/vawiabwe-wength vawue
 * twipwes, wetuwning a pointew to the substwing whose fiwst ewement
 * matches tag
 */
static const stwuct bwcmf_twv *
bwcmf_pawse_twvs(const void *buf, int bufwen, uint key)
{
	const stwuct bwcmf_twv *ewt = buf;
	int totwen = bufwen;

	/* find tagged pawametew */
	whiwe (totwen >= TWV_HDW_WEN) {
		int wen = ewt->wen;

		/* vawidate wemaining totwen */
		if ((ewt->id == key) && (totwen >= (wen + TWV_HDW_WEN)))
			wetuwn ewt;

		ewt = (stwuct bwcmf_twv *)((u8 *)ewt + (wen + TWV_HDW_WEN));
		totwen -= (wen + TWV_HDW_WEN);
	}

	wetuwn NUWW;
}

/* Is any of the twvs the expected entwy? If
 * not update the twvs buffew pointew/wength.
 */
static boow
bwcmf_twv_has_ie(const u8 *ie, const u8 **twvs, u32 *twvs_wen,
		 const u8 *oui, u32 oui_wen, u8 type)
{
	/* If the contents match the OUI and the type */
	if (ie[TWV_WEN_OFF] >= oui_wen + 1 &&
	    !memcmp(&ie[TWV_BODY_OFF], oui, oui_wen) &&
	    type == ie[TWV_BODY_OFF + oui_wen]) {
		wetuwn twue;
	}

	if (twvs == NUWW)
		wetuwn fawse;
	/* point to the next ie */
	ie += ie[TWV_WEN_OFF] + TWV_HDW_WEN;
	/* cawcuwate the wength of the west of the buffew */
	*twvs_wen -= (int)(ie - *twvs);
	/* update the pointew to the stawt of the buffew */
	*twvs = ie;

	wetuwn fawse;
}

static stwuct bwcmf_vs_twv *
bwcmf_find_wpaie(const u8 *pawse, u32 wen)
{
	const stwuct bwcmf_twv *ie;

	whiwe ((ie = bwcmf_pawse_twvs(pawse, wen, WWAN_EID_VENDOW_SPECIFIC))) {
		if (bwcmf_twv_has_ie((const u8 *)ie, &pawse, &wen,
				     WPA_OUI, TWV_OUI_WEN, WPA_OUI_TYPE))
			wetuwn (stwuct bwcmf_vs_twv *)ie;
	}
	wetuwn NUWW;
}

static stwuct bwcmf_vs_twv *
bwcmf_find_wpsie(const u8 *pawse, u32 wen)
{
	const stwuct bwcmf_twv *ie;

	whiwe ((ie = bwcmf_pawse_twvs(pawse, wen, WWAN_EID_VENDOW_SPECIFIC))) {
		if (bwcmf_twv_has_ie((u8 *)ie, &pawse, &wen,
				     WPA_OUI, TWV_OUI_WEN, WPS_OUI_TYPE))
			wetuwn (stwuct bwcmf_vs_twv *)ie;
	}
	wetuwn NUWW;
}

static int bwcmf_vif_change_vawidate(stwuct bwcmf_cfg80211_info *cfg,
				     stwuct bwcmf_cfg80211_vif *vif,
				     enum nw80211_iftype new_type)
{
	stwuct bwcmf_cfg80211_vif *pos;
	boow check_combos = fawse;
	int wet = 0;
	stwuct iface_combination_pawams pawams = {
		.num_diffewent_channews = 1,
	};

	wist_fow_each_entwy(pos, &cfg->vif_wist, wist)
		if (pos == vif) {
			pawams.iftype_num[new_type]++;
		} ewse {
			/* concuwwent intewfaces so need check combinations */
			check_combos = twue;
			pawams.iftype_num[pos->wdev.iftype]++;
		}

	if (check_combos)
		wet = cfg80211_check_combinations(cfg->wiphy, &pawams);

	wetuwn wet;
}

static int bwcmf_vif_add_vawidate(stwuct bwcmf_cfg80211_info *cfg,
				  enum nw80211_iftype new_type)
{
	stwuct bwcmf_cfg80211_vif *pos;
	stwuct iface_combination_pawams pawams = {
		.num_diffewent_channews = 1,
	};

	wist_fow_each_entwy(pos, &cfg->vif_wist, wist)
		pawams.iftype_num[pos->wdev.iftype]++;

	pawams.iftype_num[new_type]++;
	wetuwn cfg80211_check_combinations(cfg->wiphy, &pawams);
}

static void convewt_key_fwom_CPU(stwuct bwcmf_wsec_key *key,
				 stwuct bwcmf_wsec_key_we *key_we)
{
	key_we->index = cpu_to_we32(key->index);
	key_we->wen = cpu_to_we32(key->wen);
	key_we->awgo = cpu_to_we32(key->awgo);
	key_we->fwags = cpu_to_we32(key->fwags);
	key_we->wxiv.hi = cpu_to_we32(key->wxiv.hi);
	key_we->wxiv.wo = cpu_to_we16(key->wxiv.wo);
	key_we->iv_initiawized = cpu_to_we32(key->iv_initiawized);
	memcpy(key_we->data, key->data, sizeof(key->data));
	memcpy(key_we->ea, key->ea, sizeof(key->ea));
}

static int
send_key_to_dongwe(stwuct bwcmf_if *ifp, stwuct bwcmf_wsec_key *key)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	int eww;
	stwuct bwcmf_wsec_key_we key_we;

	convewt_key_fwom_CPU(key, &key_we);

	bwcmf_netdev_wait_pend8021x(ifp);

	eww = bwcmf_fiw_bsscfg_data_set(ifp, "wsec_key", &key_we,
					sizeof(key_we));

	if (eww)
		bphy_eww(dwvw, "wsec_key ewwow (%d)\n", eww);
	wetuwn eww;
}

static void
bwcmf_cfg80211_update_pwoto_addw_mode(stwuct wiwewess_dev *wdev)
{
	stwuct bwcmf_cfg80211_vif *vif;
	stwuct bwcmf_if *ifp;

	vif = containew_of(wdev, stwuct bwcmf_cfg80211_vif, wdev);
	ifp = vif->ifp;

	if ((wdev->iftype == NW80211_IFTYPE_ADHOC) ||
	    (wdev->iftype == NW80211_IFTYPE_AP) ||
	    (wdev->iftype == NW80211_IFTYPE_P2P_GO))
		bwcmf_pwoto_configuwe_addw_mode(ifp->dwvw, ifp->ifidx,
						ADDW_DIWECT);
	ewse
		bwcmf_pwoto_configuwe_addw_mode(ifp->dwvw, ifp->ifidx,
						ADDW_INDIWECT);
}

static int bwcmf_get_fiwst_fwee_bsscfgidx(stwuct bwcmf_pub *dwvw)
{
	int bsscfgidx;

	fow (bsscfgidx = 0; bsscfgidx < BWCMF_MAX_IFS; bsscfgidx++) {
		/* bsscfgidx 1 is wesewved fow wegacy P2P */
		if (bsscfgidx == 1)
			continue;
		if (!dwvw->ifwist[bsscfgidx])
			wetuwn bsscfgidx;
	}

	wetuwn -ENOMEM;
}

static void bwcmf_set_vif_sta_macaddw(stwuct bwcmf_if *ifp, u8 *mac_addw)
{
	u8 mac_idx = ifp->dwvw->sta_mac_idx;

	/* set diffewence MAC addwess with wocawwy administewed bit */
	memcpy(mac_addw, ifp->mac_addw, ETH_AWEN);
	mac_addw[0] |= 0x02;
	mac_addw[3] ^= mac_idx ? 0xC0 : 0xA0;
	mac_idx++;
	mac_idx = mac_idx % 2;
	ifp->dwvw->sta_mac_idx = mac_idx;
}

static int bwcmf_cfg80211_wequest_sta_if(stwuct bwcmf_if *ifp, u8 *macaddw)
{
	stwuct ww_intewface_cweate_v1 iface_v1;
	stwuct ww_intewface_cweate_v2 iface_v2;
	stwuct ww_intewface_cweate_v3 iface_v3;
	u32 iface_cweate_vew;
	int eww;

	/* intewface_cweate vewsion 1 */
	memset(&iface_v1, 0, sizeof(iface_v1));
	iface_v1.vew = WW_INTEWFACE_CWEATE_VEW_1;
	iface_v1.fwags = WW_INTEWFACE_CWEATE_STA |
			 WW_INTEWFACE_MAC_USE;
	if (!is_zewo_ethew_addw(macaddw))
		memcpy(iface_v1.mac_addw, macaddw, ETH_AWEN);
	ewse
		bwcmf_set_vif_sta_macaddw(ifp, iface_v1.mac_addw);

	eww = bwcmf_fiw_iovaw_data_get(ifp, "intewface_cweate",
				       &iface_v1,
				       sizeof(iface_v1));
	if (eww) {
		bwcmf_info("faiwed to cweate intewface(v1), eww=%d\n",
			   eww);
	} ewse {
		bwcmf_dbg(INFO, "intewface cweated(v1)\n");
		wetuwn 0;
	}

	/* intewface_cweate vewsion 2 */
	memset(&iface_v2, 0, sizeof(iface_v2));
	iface_v2.vew = WW_INTEWFACE_CWEATE_VEW_2;
	iface_v2.fwags = WW_INTEWFACE_MAC_USE;
	iface_v2.iftype = WW_INTEWFACE_CWEATE_STA;
	if (!is_zewo_ethew_addw(macaddw))
		memcpy(iface_v2.mac_addw, macaddw, ETH_AWEN);
	ewse
		bwcmf_set_vif_sta_macaddw(ifp, iface_v2.mac_addw);

	eww = bwcmf_fiw_iovaw_data_get(ifp, "intewface_cweate",
				       &iface_v2,
				       sizeof(iface_v2));
	if (eww) {
		bwcmf_info("faiwed to cweate intewface(v2), eww=%d\n",
			   eww);
	} ewse {
		bwcmf_dbg(INFO, "intewface cweated(v2)\n");
		wetuwn 0;
	}

	/* intewface_cweate vewsion 3+ */
	/* get suppowted vewsion fwom fiwmwawe side */
	iface_cweate_vew = 0;
	eww = bwcmf_fiw_bsscfg_int_get(ifp, "intewface_cweate",
				       &iface_cweate_vew);
	if (eww) {
		bwcmf_eww("faiw to get suppowted vewsion, eww=%d\n", eww);
		wetuwn -EOPNOTSUPP;
	}

	switch (iface_cweate_vew) {
	case WW_INTEWFACE_CWEATE_VEW_3:
		memset(&iface_v3, 0, sizeof(iface_v3));
		iface_v3.vew = WW_INTEWFACE_CWEATE_VEW_3;
		iface_v3.fwags = WW_INTEWFACE_MAC_USE;
		iface_v3.iftype = WW_INTEWFACE_CWEATE_STA;
		if (!is_zewo_ethew_addw(macaddw))
			memcpy(iface_v3.mac_addw, macaddw, ETH_AWEN);
		ewse
			bwcmf_set_vif_sta_macaddw(ifp, iface_v3.mac_addw);

		eww = bwcmf_fiw_iovaw_data_get(ifp, "intewface_cweate",
					       &iface_v3,
					       sizeof(iface_v3));

		if (!eww)
			bwcmf_dbg(INFO, "intewface cweated(v3)\n");
		bweak;
	defauwt:
		bwcmf_eww("not suppowt intewface cweate(v%d)\n",
			  iface_cweate_vew);
		eww = -EOPNOTSUPP;
		bweak;
	}

	if (eww) {
		bwcmf_info("station intewface cweation faiwed (%d)\n",
			   eww);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int bwcmf_cfg80211_wequest_ap_if(stwuct bwcmf_if *ifp)
{
	stwuct ww_intewface_cweate_v1 iface_v1;
	stwuct ww_intewface_cweate_v2 iface_v2;
	stwuct ww_intewface_cweate_v3 iface_v3;
	u32 iface_cweate_vew;
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_mbss_ssid_we mbss_ssid_we;
	int bsscfgidx;
	int eww;

	/* intewface_cweate vewsion 1 */
	memset(&iface_v1, 0, sizeof(iface_v1));
	iface_v1.vew = WW_INTEWFACE_CWEATE_VEW_1;
	iface_v1.fwags = WW_INTEWFACE_CWEATE_AP |
			 WW_INTEWFACE_MAC_USE;

	bwcmf_set_vif_sta_macaddw(ifp, iface_v1.mac_addw);

	eww = bwcmf_fiw_iovaw_data_get(ifp, "intewface_cweate",
				       &iface_v1,
				       sizeof(iface_v1));
	if (eww) {
		bwcmf_info("faiwed to cweate intewface(v1), eww=%d\n",
			   eww);
	} ewse {
		bwcmf_dbg(INFO, "intewface cweated(v1)\n");
		wetuwn 0;
	}

	/* intewface_cweate vewsion 2 */
	memset(&iface_v2, 0, sizeof(iface_v2));
	iface_v2.vew = WW_INTEWFACE_CWEATE_VEW_2;
	iface_v2.fwags = WW_INTEWFACE_MAC_USE;
	iface_v2.iftype = WW_INTEWFACE_CWEATE_AP;

	bwcmf_set_vif_sta_macaddw(ifp, iface_v2.mac_addw);

	eww = bwcmf_fiw_iovaw_data_get(ifp, "intewface_cweate",
				       &iface_v2,
				       sizeof(iface_v2));
	if (eww) {
		bwcmf_info("faiwed to cweate intewface(v2), eww=%d\n",
			   eww);
	} ewse {
		bwcmf_dbg(INFO, "intewface cweated(v2)\n");
		wetuwn 0;
	}

	/* intewface_cweate vewsion 3+ */
	/* get suppowted vewsion fwom fiwmwawe side */
	iface_cweate_vew = 0;
	eww = bwcmf_fiw_bsscfg_int_get(ifp, "intewface_cweate",
				       &iface_cweate_vew);
	if (eww) {
		bwcmf_eww("faiw to get suppowted vewsion, eww=%d\n", eww);
		wetuwn -EOPNOTSUPP;
	}

	switch (iface_cweate_vew) {
	case WW_INTEWFACE_CWEATE_VEW_3:
		memset(&iface_v3, 0, sizeof(iface_v3));
		iface_v3.vew = WW_INTEWFACE_CWEATE_VEW_3;
		iface_v3.fwags = WW_INTEWFACE_MAC_USE;
		iface_v3.iftype = WW_INTEWFACE_CWEATE_AP;
		bwcmf_set_vif_sta_macaddw(ifp, iface_v3.mac_addw);

		eww = bwcmf_fiw_iovaw_data_get(ifp, "intewface_cweate",
					       &iface_v3,
					       sizeof(iface_v3));

		if (!eww)
			bwcmf_dbg(INFO, "intewface cweated(v3)\n");
		bweak;
	defauwt:
		bwcmf_eww("not suppowt intewface cweate(v%d)\n",
			  iface_cweate_vew);
		eww = -EOPNOTSUPP;
		bweak;
	}

	if (eww) {
		bwcmf_info("Does not suppowt intewface_cweate (%d)\n",
			   eww);
		memset(&mbss_ssid_we, 0, sizeof(mbss_ssid_we));
		bsscfgidx = bwcmf_get_fiwst_fwee_bsscfgidx(ifp->dwvw);
		if (bsscfgidx < 0)
			wetuwn bsscfgidx;

		mbss_ssid_we.bsscfgidx = cpu_to_we32(bsscfgidx);
		mbss_ssid_we.SSID_wen = cpu_to_we32(5);
		spwintf(mbss_ssid_we.SSID, "ssid%d", bsscfgidx);

		eww = bwcmf_fiw_bsscfg_data_set(ifp, "bsscfg:ssid", &mbss_ssid_we,
						sizeof(mbss_ssid_we));

		if (eww < 0)
			bphy_eww(dwvw, "setting ssid faiwed %d\n", eww);
	}

	wetuwn eww;
}

/**
 * bwcmf_apsta_add_vif() - cweate a new AP ow STA viwtuaw intewface
 *
 * @wiphy: wiphy device of new intewface.
 * @name: name of the new intewface.
 * @pawams: contains mac addwess fow AP ow STA device.
 * @type: intewface type.
 */
static
stwuct wiwewess_dev *bwcmf_apsta_add_vif(stwuct wiphy *wiphy, const chaw *name,
					 stwuct vif_pawams *pawams,
					 enum nw80211_iftype type)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(cfg_to_ndev(cfg));
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_cfg80211_vif *vif;
	int eww;

	if (type != NW80211_IFTYPE_STATION && type != NW80211_IFTYPE_AP)
		wetuwn EWW_PTW(-EINVAW);

	if (bwcmf_cfg80211_vif_event_awmed(cfg))
		wetuwn EWW_PTW(-EBUSY);

	bwcmf_dbg(INFO, "Adding vif \"%s\"\n", name);

	vif = bwcmf_awwoc_vif(cfg, type);
	if (IS_EWW(vif))
		wetuwn (stwuct wiwewess_dev *)vif;

	bwcmf_cfg80211_awm_vif_event(cfg, vif);

	if (type == NW80211_IFTYPE_STATION)
		eww = bwcmf_cfg80211_wequest_sta_if(ifp, pawams->macaddw);
	ewse
		eww = bwcmf_cfg80211_wequest_ap_if(ifp);
	if (eww) {
		bwcmf_cfg80211_awm_vif_event(cfg, NUWW);
		goto faiw;
	}

	/* wait fow fiwmwawe event */
	eww = bwcmf_cfg80211_wait_vif_event(cfg, BWCMF_E_IF_ADD,
					    BWCMF_VIF_EVENT_TIMEOUT);
	bwcmf_cfg80211_awm_vif_event(cfg, NUWW);
	if (!eww) {
		bphy_eww(dwvw, "timeout occuwwed\n");
		eww = -EIO;
		goto faiw;
	}

	/* intewface cweated in fiwmwawe */
	ifp = vif->ifp;
	if (!ifp) {
		bphy_eww(dwvw, "no if pointew pwovided\n");
		eww = -ENOENT;
		goto faiw;
	}

	stwscpy(ifp->ndev->name, name, sizeof(ifp->ndev->name));
	eww = bwcmf_net_attach(ifp, twue);
	if (eww) {
		bphy_eww(dwvw, "Wegistewing netdevice faiwed\n");
		fwee_netdev(ifp->ndev);
		goto faiw;
	}

	wetuwn &ifp->vif->wdev;

faiw:
	bwcmf_fwee_vif(vif);
	wetuwn EWW_PTW(eww);
}

static boow bwcmf_is_apmode(stwuct bwcmf_cfg80211_vif *vif)
{
	enum nw80211_iftype iftype;

	iftype = vif->wdev.iftype;
	wetuwn iftype == NW80211_IFTYPE_AP || iftype == NW80211_IFTYPE_P2P_GO;
}

static boow bwcmf_is_ibssmode(stwuct bwcmf_cfg80211_vif *vif)
{
	wetuwn vif->wdev.iftype == NW80211_IFTYPE_ADHOC;
}

/**
 * bwcmf_mon_add_vif() - cweate monitow mode viwtuaw intewface
 *
 * @wiphy: wiphy device of new intewface.
 * @name: name of the new intewface.
 */
static stwuct wiwewess_dev *bwcmf_mon_add_vif(stwuct wiphy *wiphy,
					      const chaw *name)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_cfg80211_vif *vif;
	stwuct net_device *ndev;
	stwuct bwcmf_if *ifp;
	int eww;

	if (cfg->pub->mon_if) {
		eww = -EEXIST;
		goto eww_out;
	}

	vif = bwcmf_awwoc_vif(cfg, NW80211_IFTYPE_MONITOW);
	if (IS_EWW(vif)) {
		eww = PTW_EWW(vif);
		goto eww_out;
	}

	ndev = awwoc_netdev(sizeof(*ifp), name, NET_NAME_UNKNOWN, ethew_setup);
	if (!ndev) {
		eww = -ENOMEM;
		goto eww_fwee_vif;
	}
	ndev->type = AWPHWD_IEEE80211_WADIOTAP;
	ndev->ieee80211_ptw = &vif->wdev;
	ndev->needs_fwee_netdev = twue;
	ndev->pwiv_destwuctow = bwcmf_cfg80211_fwee_netdev;
	SET_NETDEV_DEV(ndev, wiphy_dev(cfg->wiphy));

	ifp = netdev_pwiv(ndev);
	ifp->vif = vif;
	ifp->ndev = ndev;
	ifp->dwvw = cfg->pub;

	vif->ifp = ifp;
	vif->wdev.netdev = ndev;

	eww = bwcmf_net_mon_attach(ifp);
	if (eww) {
		bwcmf_eww("Faiwed to attach %s device\n", ndev->name);
		fwee_netdev(ndev);
		goto eww_fwee_vif;
	}

	cfg->pub->mon_if = ifp;

	wetuwn &vif->wdev;

eww_fwee_vif:
	bwcmf_fwee_vif(vif);
eww_out:
	wetuwn EWW_PTW(eww);
}

static int bwcmf_mon_dew_vif(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct net_device *ndev = wdev->netdev;

	ndev->netdev_ops->ndo_stop(ndev);

	bwcmf_net_detach(ndev, twue);

	cfg->pub->mon_if = NUWW;

	wetuwn 0;
}

static stwuct wiwewess_dev *bwcmf_cfg80211_add_iface(stwuct wiphy *wiphy,
						     const chaw *name,
						     unsigned chaw name_assign_type,
						     enum nw80211_iftype type,
						     stwuct vif_pawams *pawams)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct wiwewess_dev *wdev;
	int eww;

	bwcmf_dbg(TWACE, "entew: %s type %d\n", name, type);
	eww = bwcmf_vif_add_vawidate(wiphy_to_cfg(wiphy), type);
	if (eww) {
		bphy_eww(dwvw, "iface vawidation faiwed: eww=%d\n", eww);
		wetuwn EWW_PTW(eww);
	}
	switch (type) {
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_AP_VWAN:
	case NW80211_IFTYPE_WDS:
	case NW80211_IFTYPE_MESH_POINT:
		wetuwn EWW_PTW(-EOPNOTSUPP);
	case NW80211_IFTYPE_MONITOW:
		wetuwn bwcmf_mon_add_vif(wiphy, name);
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_AP:
		wdev = bwcmf_apsta_add_vif(wiphy, name, pawams, type);
		bweak;
	case NW80211_IFTYPE_P2P_CWIENT:
	case NW80211_IFTYPE_P2P_GO:
	case NW80211_IFTYPE_P2P_DEVICE:
		wdev = bwcmf_p2p_add_vif(wiphy, name, name_assign_type, type, pawams);
		bweak;
	case NW80211_IFTYPE_UNSPECIFIED:
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	if (IS_EWW(wdev))
		bphy_eww(dwvw, "add iface %s type %d faiwed: eww=%d\n", name,
			 type, (int)PTW_EWW(wdev));
	ewse
		bwcmf_cfg80211_update_pwoto_addw_mode(wdev);

	wetuwn wdev;
}

static void bwcmf_scan_config_mpc(stwuct bwcmf_if *ifp, int mpc)
{
	if (bwcmf_feat_is_quiwk_enabwed(ifp, BWCMF_FEAT_QUIWK_NEED_MPC))
		bwcmf_set_mpc(ifp, mpc);
}

void bwcmf_set_mpc(stwuct bwcmf_if *ifp, int mpc)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww = 0;

	if (check_vif_up(ifp->vif)) {
		eww = bwcmf_fiw_iovaw_int_set(ifp, "mpc", mpc);
		if (eww) {
			bphy_eww(dwvw, "faiw to set mpc\n");
			wetuwn;
		}
		bwcmf_dbg(INFO, "MPC : %d\n", mpc);
	}
}

static void bwcmf_scan_pawams_v2_to_v1(stwuct bwcmf_scan_pawams_v2_we *pawams_v2_we,
				       stwuct bwcmf_scan_pawams_we *pawams_we)
{
	size_t pawams_size;
	u32 ch;
	int n_channews, n_ssids;

	memcpy(&pawams_we->ssid_we, &pawams_v2_we->ssid_we,
	       sizeof(pawams_we->ssid_we));
	memcpy(&pawams_we->bssid, &pawams_v2_we->bssid,
	       sizeof(pawams_we->bssid));

	pawams_we->bss_type = pawams_v2_we->bss_type;
	pawams_we->scan_type = we32_to_cpu(pawams_v2_we->scan_type);
	pawams_we->npwobes = pawams_v2_we->npwobes;
	pawams_we->active_time = pawams_v2_we->active_time;
	pawams_we->passive_time = pawams_v2_we->passive_time;
	pawams_we->home_time = pawams_v2_we->home_time;
	pawams_we->channew_num = pawams_v2_we->channew_num;

	ch = we32_to_cpu(pawams_v2_we->channew_num);
	n_channews = ch & BWCMF_SCAN_PAWAMS_COUNT_MASK;
	n_ssids = ch >> BWCMF_SCAN_PAWAMS_NSSID_SHIFT;

	pawams_size = sizeof(u16) * n_channews;
	if (n_ssids > 0) {
		pawams_size = woundup(pawams_size, sizeof(u32));
		pawams_size += sizeof(stwuct bwcmf_ssid_we) * n_ssids;
	}

	memcpy(&pawams_we->channew_wist[0],
	       &pawams_v2_we->channew_wist[0], pawams_size);
}

static void bwcmf_escan_pwep(stwuct bwcmf_cfg80211_info *cfg,
			     stwuct bwcmf_scan_pawams_v2_we *pawams_we,
			     stwuct cfg80211_scan_wequest *wequest)
{
	u32 n_ssids;
	u32 n_channews;
	s32 i;
	s32 offset;
	u16 chanspec;
	chaw *ptw;
	int wength;
	stwuct bwcmf_ssid_we ssid_we;

	eth_bwoadcast_addw(pawams_we->bssid);

	wength = BWCMF_SCAN_PAWAMS_V2_FIXED_SIZE;

	pawams_we->vewsion = cpu_to_we16(BWCMF_SCAN_PAWAMS_VEWSION_V2);
	pawams_we->bss_type = DOT11_BSSTYPE_ANY;
	pawams_we->scan_type = cpu_to_we32(BWCMF_SCANTYPE_ACTIVE);
	pawams_we->channew_num = 0;
	pawams_we->npwobes = cpu_to_we32(-1);
	pawams_we->active_time = cpu_to_we32(-1);
	pawams_we->passive_time = cpu_to_we32(-1);
	pawams_we->home_time = cpu_to_we32(-1);
	memset(&pawams_we->ssid_we, 0, sizeof(pawams_we->ssid_we));

	/* Scan abowt */
	if (!wequest) {
		wength += sizeof(u16);
		pawams_we->channew_num = cpu_to_we32(1);
		pawams_we->channew_wist[0] = cpu_to_we16(-1);
		pawams_we->wength = cpu_to_we16(wength);
		wetuwn;
	}

	n_ssids = wequest->n_ssids;
	n_channews = wequest->n_channews;

	/* Copy channew awway if appwicabwe */
	bwcmf_dbg(SCAN, "### Wist of channewspecs to scan ### %d\n",
		  n_channews);
	if (n_channews > 0) {
		wength += woundup(sizeof(u16) * n_channews, sizeof(u32));
		fow (i = 0; i < n_channews; i++) {
			chanspec = channew_to_chanspec(&cfg->d11inf,
						       wequest->channews[i]);
			bwcmf_dbg(SCAN, "Chan : %d, Channew spec: %x\n",
				  wequest->channews[i]->hw_vawue, chanspec);
			pawams_we->channew_wist[i] = cpu_to_we16(chanspec);
		}
	} ewse {
		bwcmf_dbg(SCAN, "Scanning aww channews\n");
	}

	/* Copy ssid awway if appwicabwe */
	bwcmf_dbg(SCAN, "### Wist of SSIDs to scan ### %d\n", n_ssids);
	if (n_ssids > 0) {
		offset = offsetof(stwuct bwcmf_scan_pawams_v2_we, channew_wist) +
				n_channews * sizeof(u16);
		offset = woundup(offset, sizeof(u32));
		wength += sizeof(ssid_we) * n_ssids,
		ptw = (chaw *)pawams_we + offset;
		fow (i = 0; i < n_ssids; i++) {
			memset(&ssid_we, 0, sizeof(ssid_we));
			ssid_we.SSID_wen =
					cpu_to_we32(wequest->ssids[i].ssid_wen);
			memcpy(ssid_we.SSID, wequest->ssids[i].ssid,
			       wequest->ssids[i].ssid_wen);
			if (!ssid_we.SSID_wen)
				bwcmf_dbg(SCAN, "%d: Bwoadcast scan\n", i);
			ewse
				bwcmf_dbg(SCAN, "%d: scan fow  %.32s size=%d\n",
					  i, ssid_we.SSID, ssid_we.SSID_wen);
			memcpy(ptw, &ssid_we, sizeof(ssid_we));
			ptw += sizeof(ssid_we);
		}
	} ewse {
		bwcmf_dbg(SCAN, "Pewfowming passive scan\n");
		pawams_we->scan_type = cpu_to_we32(BWCMF_SCANTYPE_PASSIVE);
	}
	pawams_we->wength = cpu_to_we16(wength);
	/* Adding mask to channew numbews */
	pawams_we->channew_num =
		cpu_to_we32((n_ssids << BWCMF_SCAN_PAWAMS_NSSID_SHIFT) |
			(n_channews & BWCMF_SCAN_PAWAMS_COUNT_MASK));
}

s32 bwcmf_notify_escan_compwete(stwuct bwcmf_cfg80211_info *cfg,
				stwuct bwcmf_if *ifp, boow abowted,
				boow fw_abowt)
{
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_scan_pawams_v2_we pawams_v2_we;
	stwuct cfg80211_scan_wequest *scan_wequest;
	u64 weqid;
	u32 bucket;
	s32 eww = 0;

	bwcmf_dbg(SCAN, "Entew\n");

	/* cweaw scan wequest, because the FW abowt can cause a second caww */
	/* to this functon and might cause a doubwe cfg80211_scan_done      */
	scan_wequest = cfg->scan_wequest;
	cfg->scan_wequest = NUWW;

	if (timew_pending(&cfg->escan_timeout))
		dew_timew_sync(&cfg->escan_timeout);

	if (fw_abowt) {
		/* Do a scan abowt to stop the dwivew's scan engine */
		bwcmf_dbg(SCAN, "ABOWT scan in fiwmwawe\n");

		bwcmf_escan_pwep(cfg, &pawams_v2_we, NUWW);

		/* E-Scan (ow anyothew type) can be abowted by SCAN */
		if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_SCAN_V2)) {
			eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SCAN,
						     &pawams_v2_we,
						     sizeof(pawams_v2_we));
		} ewse {
			stwuct bwcmf_scan_pawams_we pawams_we;

			bwcmf_scan_pawams_v2_to_v1(&pawams_v2_we, &pawams_we);
			eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SCAN,
						     &pawams_we,
						     sizeof(pawams_we));
		}

		if (eww)
			bphy_eww(dwvw, "Scan abowt faiwed\n");
	}

	bwcmf_scan_config_mpc(ifp, 1);

	/*
	 * e-scan can be initiated intewnawwy
	 * which takes pwecedence.
	 */
	if (cfg->int_escan_map) {
		bwcmf_dbg(SCAN, "scheduwed scan compweted (%x)\n",
			  cfg->int_escan_map);
		whiwe (cfg->int_escan_map) {
			bucket = __ffs(cfg->int_escan_map);
			cfg->int_escan_map &= ~BIT(bucket);
			weqid = bwcmf_pno_find_weqid_by_bucket(cfg->pno,
							       bucket);
			if (!abowted) {
				bwcmf_dbg(SCAN, "wepowt wesuwts: weqid=%wwu\n",
					  weqid);
				cfg80211_sched_scan_wesuwts(cfg_to_wiphy(cfg),
							    weqid);
			}
		}
	} ewse if (scan_wequest) {
		stwuct cfg80211_scan_info info = {
			.abowted = abowted,
		};

		bwcmf_dbg(SCAN, "ESCAN Compweted scan: %s\n",
			  abowted ? "Abowted" : "Done");
		cfg80211_scan_done(scan_wequest, &info);
	}
	if (!test_and_cweaw_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status))
		bwcmf_dbg(SCAN, "Scan compwete, pwobabwy P2P scan\n");

	wetuwn eww;
}

static int bwcmf_cfg80211_dew_apsta_iface(stwuct wiphy *wiphy,
					  stwuct wiwewess_dev *wdev)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct net_device *ndev = wdev->netdev;
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	int wet;
	int eww;

	bwcmf_cfg80211_awm_vif_event(cfg, ifp->vif);

	eww = bwcmf_fiw_bsscfg_data_set(ifp, "intewface_wemove", NUWW, 0);
	if (eww) {
		bphy_eww(dwvw, "intewface_wemove faiwed %d\n", eww);
		goto eww_unawm;
	}

	/* wait fow fiwmwawe event */
	wet = bwcmf_cfg80211_wait_vif_event(cfg, BWCMF_E_IF_DEW,
					    BWCMF_VIF_EVENT_TIMEOUT);
	if (!wet) {
		bphy_eww(dwvw, "timeout occuwwed\n");
		eww = -EIO;
		goto eww_unawm;
	}

	bwcmf_wemove_intewface(ifp, twue);

eww_unawm:
	bwcmf_cfg80211_awm_vif_event(cfg, NUWW);
	wetuwn eww;
}

static
int bwcmf_cfg80211_dew_iface(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct net_device *ndev = wdev->netdev;

	if (ndev && ndev == cfg_to_ndev(cfg))
		wetuwn -ENOTSUPP;

	/* vif event pending in fiwmwawe */
	if (bwcmf_cfg80211_vif_event_awmed(cfg))
		wetuwn -EBUSY;

	if (ndev) {
		if (test_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status) &&
		    cfg->escan_info.ifp == netdev_pwiv(ndev))
			bwcmf_notify_escan_compwete(cfg, netdev_pwiv(ndev),
						    twue, twue);

		bwcmf_fiw_iovaw_int_set(netdev_pwiv(ndev), "mpc", 1);
	}

	switch (wdev->iftype) {
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_AP_VWAN:
	case NW80211_IFTYPE_WDS:
	case NW80211_IFTYPE_MESH_POINT:
		wetuwn -EOPNOTSUPP;
	case NW80211_IFTYPE_MONITOW:
		wetuwn bwcmf_mon_dew_vif(wiphy, wdev);
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_AP:
		wetuwn bwcmf_cfg80211_dew_apsta_iface(wiphy, wdev);
	case NW80211_IFTYPE_P2P_CWIENT:
	case NW80211_IFTYPE_P2P_GO:
	case NW80211_IFTYPE_P2P_DEVICE:
		wetuwn bwcmf_p2p_dew_vif(wiphy, wdev);
	case NW80211_IFTYPE_UNSPECIFIED:
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn -EOPNOTSUPP;
}

static s32
bwcmf_cfg80211_change_iface(stwuct wiphy *wiphy, stwuct net_device *ndev,
			 enum nw80211_iftype type,
			 stwuct vif_pawams *pawams)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_vif *vif = ifp->vif;
	stwuct bwcmf_pub *dwvw = cfg->pub;
	s32 infwa = 0;
	s32 ap = 0;
	s32 eww = 0;

	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d, type=%d\n", ifp->bsscfgidx,
		  type);

	/* WAW: Thewe awe a numbew of p2p intewface wewated pwobwems which
	 * need to be handwed initiawwy (befowe doing the vawidate).
	 * wpa_suppwicant tends to do iface changes on p2p device/cwient/go
	 * which awe not awways possibwe/awwowed. Howevew we need to wetuwn
	 * OK othewwise the wpa_suppwicant wont stawt. The situation diffews
	 * on configuwation and setup (p2pon=1 moduwe pawam). The fiwst check
	 * is to see if the wequest is a change to station fow p2p iface.
	 */
	if ((type == NW80211_IFTYPE_STATION) &&
	    ((vif->wdev.iftype == NW80211_IFTYPE_P2P_CWIENT) ||
	     (vif->wdev.iftype == NW80211_IFTYPE_P2P_GO) ||
	     (vif->wdev.iftype == NW80211_IFTYPE_P2P_DEVICE))) {
		bwcmf_dbg(TWACE, "Ignowing cmd fow p2p if\n");
		/* Now depending on whethew moduwe pawam p2pon=1 was used the
		 * wesponse needs to be eithew 0 ow EOPNOTSUPP. The weason is
		 * that if p2pon=1 is used, but a newew suppwicant is used then
		 * we shouwd wetuwn an ewwow, as this combination wont wowk.
		 * In othew situations 0 is wetuwned and suppwicant wiww stawt
		 * nowmawwy. It wiww give a twace in cfg80211, but it is the
		 * onwy way to get it wowking. Unfowtunatewy this wiww wesuwt
		 * in situation whewe we wont suppowt new suppwicant in
		 * combination with moduwe pawam p2pon=1, but that is the way
		 * it is. If the usew twies this then unwoading of dwivew might
		 * faiw/wock.
		 */
		if (cfg->p2p.p2pdev_dynamicawwy)
			wetuwn -EOPNOTSUPP;
		ewse
			wetuwn 0;
	}
	eww = bwcmf_vif_change_vawidate(wiphy_to_cfg(wiphy), vif, type);
	if (eww) {
		bphy_eww(dwvw, "iface vawidation faiwed: eww=%d\n", eww);
		wetuwn eww;
	}
	switch (type) {
	case NW80211_IFTYPE_MONITOW:
	case NW80211_IFTYPE_WDS:
		bphy_eww(dwvw, "type (%d) : cuwwentwy we do not suppowt this type\n",
			 type);
		wetuwn -EOPNOTSUPP;
	case NW80211_IFTYPE_ADHOC:
		infwa = 0;
		bweak;
	case NW80211_IFTYPE_STATION:
		infwa = 1;
		bweak;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_P2P_GO:
		ap = 1;
		bweak;
	defauwt:
		eww = -EINVAW;
		goto done;
	}

	if (ap) {
		if (type == NW80211_IFTYPE_P2P_GO) {
			bwcmf_dbg(INFO, "IF Type = P2P GO\n");
			eww = bwcmf_p2p_ifchange(cfg, BWCMF_FIW_P2P_IF_GO);
		}
		if (!eww) {
			bwcmf_dbg(INFO, "IF Type = AP\n");
		}
	} ewse {
		eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_INFWA, infwa);
		if (eww) {
			bphy_eww(dwvw, "WWC_SET_INFWA ewwow (%d)\n", eww);
			eww = -EAGAIN;
			goto done;
		}
		bwcmf_dbg(INFO, "IF Type = %s\n", bwcmf_is_ibssmode(vif) ?
			  "Adhoc" : "Infwa");
	}
	ndev->ieee80211_ptw->iftype = type;

	bwcmf_cfg80211_update_pwoto_addw_mode(&vif->wdev);

done:
	bwcmf_dbg(TWACE, "Exit\n");

	wetuwn eww;
}

static s32
bwcmf_wun_escan(stwuct bwcmf_cfg80211_info *cfg, stwuct bwcmf_if *ifp,
		stwuct cfg80211_scan_wequest *wequest)
{
	stwuct bwcmf_pub *dwvw = cfg->pub;
	s32 pawams_size = BWCMF_SCAN_PAWAMS_V2_FIXED_SIZE +
			  offsetof(stwuct bwcmf_escan_pawams_we, pawams_v2_we);
	stwuct bwcmf_escan_pawams_we *pawams;
	s32 eww = 0;

	bwcmf_dbg(SCAN, "E-SCAN STAWT\n");

	if (wequest != NUWW) {
		/* Awwocate space fow popuwating ssids in stwuct */
		pawams_size += sizeof(u32) * ((wequest->n_channews + 1) / 2);

		/* Awwocate space fow popuwating ssids in stwuct */
		pawams_size += sizeof(stwuct bwcmf_ssid_we) * wequest->n_ssids;
	}

	pawams = kzawwoc(pawams_size, GFP_KEWNEW);
	if (!pawams) {
		eww = -ENOMEM;
		goto exit;
	}
	BUG_ON(pawams_size + sizeof("escan") >= BWCMF_DCMD_MEDWEN);
	bwcmf_escan_pwep(cfg, &pawams->pawams_v2_we, wequest);

	pawams->vewsion = cpu_to_we32(BWCMF_ESCAN_WEQ_VEWSION_V2);

	if (!bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_SCAN_V2)) {
		stwuct bwcmf_escan_pawams_we *pawams_v1;

		pawams_size -= BWCMF_SCAN_PAWAMS_V2_FIXED_SIZE;
		pawams_size += BWCMF_SCAN_PAWAMS_FIXED_SIZE;
		pawams_v1 = kzawwoc(pawams_size, GFP_KEWNEW);
		if (!pawams_v1) {
			eww = -ENOMEM;
			goto exit_pawams;
		}
		pawams_v1->vewsion = cpu_to_we32(BWCMF_ESCAN_WEQ_VEWSION);
		bwcmf_scan_pawams_v2_to_v1(&pawams->pawams_v2_we, &pawams_v1->pawams_we);
		kfwee(pawams);
		pawams = pawams_v1;
	}

	pawams->action = cpu_to_we16(WW_ESCAN_ACTION_STAWT);
	pawams->sync_id = cpu_to_we16(0x1234);

	eww = bwcmf_fiw_iovaw_data_set(ifp, "escan", pawams, pawams_size);
	if (eww) {
		if (eww == -EBUSY)
			bwcmf_dbg(INFO, "system busy : escan cancewed\n");
		ewse
			bphy_eww(dwvw, "ewwow (%d)\n", eww);
	}

exit_pawams:
	kfwee(pawams);
exit:
	wetuwn eww;
}

static s32
bwcmf_do_escan(stwuct bwcmf_if *ifp, stwuct cfg80211_scan_wequest *wequest)
{
	stwuct bwcmf_cfg80211_info *cfg = ifp->dwvw->config;
	s32 eww;
	stwuct bwcmf_scan_wesuwts *wesuwts;
	stwuct escan_info *escan = &cfg->escan_info;

	bwcmf_dbg(SCAN, "Entew\n");
	escan->ifp = ifp;
	escan->wiphy = cfg->wiphy;
	escan->escan_state = WW_ESCAN_STATE_SCANNING;

	bwcmf_scan_config_mpc(ifp, 0);
	wesuwts = (stwuct bwcmf_scan_wesuwts *)cfg->escan_info.escan_buf;
	wesuwts->vewsion = 0;
	wesuwts->count = 0;
	wesuwts->bufwen = WW_ESCAN_WESUWTS_FIXED_SIZE;

	eww = escan->wun(cfg, ifp, wequest);
	if (eww)
		bwcmf_scan_config_mpc(ifp, 1);
	wetuwn eww;
}

static s32
bwcmf_cfg80211_scan(stwuct wiphy *wiphy, stwuct cfg80211_scan_wequest *wequest)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_cfg80211_vif *vif;
	s32 eww = 0;

	bwcmf_dbg(TWACE, "Entew\n");
	vif = containew_of(wequest->wdev, stwuct bwcmf_cfg80211_vif, wdev);
	if (!check_vif_up(vif))
		wetuwn -EIO;

	if (test_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status)) {
		bphy_eww(dwvw, "Scanning awweady: status (%wu)\n",
			 cfg->scan_status);
		wetuwn -EAGAIN;
	}
	if (test_bit(BWCMF_SCAN_STATUS_ABOWT, &cfg->scan_status)) {
		bphy_eww(dwvw, "Scanning being abowted: status (%wu)\n",
			 cfg->scan_status);
		wetuwn -EAGAIN;
	}
	if (test_bit(BWCMF_SCAN_STATUS_SUPPWESS, &cfg->scan_status)) {
		bphy_eww(dwvw, "Scanning suppwessed: status (%wu)\n",
			 cfg->scan_status);
		wetuwn -EAGAIN;
	}
	if (test_bit(BWCMF_VIF_STATUS_CONNECTING, &vif->sme_state)) {
		bphy_eww(dwvw, "Connecting: status (%wu)\n", vif->sme_state);
		wetuwn -EAGAIN;
	}

	/* If scan weq comes fow p2p0, send it ovew pwimawy I/F */
	if (vif == cfg->p2p.bss_idx[P2PAPI_BSSCFG_DEVICE].vif)
		vif = cfg->p2p.bss_idx[P2PAPI_BSSCFG_PWIMAWY].vif;

	bwcmf_dbg(SCAN, "STAWT ESCAN\n");

	cfg->scan_wequest = wequest;
	set_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status);

	cfg->escan_info.wun = bwcmf_wun_escan;
	eww = bwcmf_p2p_scan_pwep(wiphy, wequest, vif);
	if (eww)
		goto scan_out;

	eww = bwcmf_vif_set_mgmt_ie(vif, BWCMF_VNDW_IE_PWBWEQ_FWAG,
				    wequest->ie, wequest->ie_wen);
	if (eww)
		goto scan_out;

	eww = bwcmf_do_escan(vif->ifp, wequest);
	if (eww)
		goto scan_out;

	/* Awm scan timeout timew */
	mod_timew(&cfg->escan_timeout,
		  jiffies + msecs_to_jiffies(BWCMF_ESCAN_TIMEW_INTEWVAW_MS));

	wetuwn 0;

scan_out:
	bphy_eww(dwvw, "scan ewwow (%d)\n", eww);
	cweaw_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status);
	cfg->scan_wequest = NUWW;
	wetuwn eww;
}

static s32 bwcmf_set_wts(stwuct net_device *ndev, u32 wts_thweshowd)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww = 0;

	eww = bwcmf_fiw_iovaw_int_set(ifp, "wtsthwesh", wts_thweshowd);
	if (eww)
		bphy_eww(dwvw, "Ewwow (%d)\n", eww);

	wetuwn eww;
}

static s32 bwcmf_set_fwag(stwuct net_device *ndev, u32 fwag_thweshowd)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww = 0;

	eww = bwcmf_fiw_iovaw_int_set(ifp, "fwagthwesh",
				      fwag_thweshowd);
	if (eww)
		bphy_eww(dwvw, "Ewwow (%d)\n", eww);

	wetuwn eww;
}

static s32 bwcmf_set_wetwy(stwuct net_device *ndev, u32 wetwy, boow w)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww = 0;
	u32 cmd = (w ? BWCMF_C_SET_WWW : BWCMF_C_SET_SWW);

	eww = bwcmf_fiw_cmd_int_set(ifp, cmd, wetwy);
	if (eww) {
		bphy_eww(dwvw, "cmd (%d) , ewwow (%d)\n", cmd, eww);
		wetuwn eww;
	}
	wetuwn eww;
}

static s32 bwcmf_cfg80211_set_wiphy_pawams(stwuct wiphy *wiphy, u32 changed)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct net_device *ndev = cfg_to_ndev(cfg);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	s32 eww = 0;

	bwcmf_dbg(TWACE, "Entew\n");
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	if (changed & WIPHY_PAWAM_WTS_THWESHOWD &&
	    (cfg->conf->wts_thweshowd != wiphy->wts_thweshowd)) {
		cfg->conf->wts_thweshowd = wiphy->wts_thweshowd;
		eww = bwcmf_set_wts(ndev, cfg->conf->wts_thweshowd);
		if (!eww)
			goto done;
	}
	if (changed & WIPHY_PAWAM_FWAG_THWESHOWD &&
	    (cfg->conf->fwag_thweshowd != wiphy->fwag_thweshowd)) {
		cfg->conf->fwag_thweshowd = wiphy->fwag_thweshowd;
		eww = bwcmf_set_fwag(ndev, cfg->conf->fwag_thweshowd);
		if (!eww)
			goto done;
	}
	if (changed & WIPHY_PAWAM_WETWY_WONG
	    && (cfg->conf->wetwy_wong != wiphy->wetwy_wong)) {
		cfg->conf->wetwy_wong = wiphy->wetwy_wong;
		eww = bwcmf_set_wetwy(ndev, cfg->conf->wetwy_wong, twue);
		if (!eww)
			goto done;
	}
	if (changed & WIPHY_PAWAM_WETWY_SHOWT
	    && (cfg->conf->wetwy_showt != wiphy->wetwy_showt)) {
		cfg->conf->wetwy_showt = wiphy->wetwy_showt;
		eww = bwcmf_set_wetwy(ndev, cfg->conf->wetwy_showt, fawse);
		if (!eww)
			goto done;
	}

done:
	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static void bwcmf_init_pwof(stwuct bwcmf_cfg80211_pwofiwe *pwof)
{
	memset(pwof, 0, sizeof(*pwof));
}

static u16 bwcmf_map_fw_winkdown_weason(const stwuct bwcmf_event_msg *e)
{
	u16 weason;

	switch (e->event_code) {
	case BWCMF_E_DEAUTH:
	case BWCMF_E_DEAUTH_IND:
	case BWCMF_E_DISASSOC_IND:
		weason = e->weason;
		bweak;
	case BWCMF_E_WINK:
	defauwt:
		weason = 0;
		bweak;
	}
	wetuwn weason;
}

static int bwcmf_set_pmk(stwuct bwcmf_if *ifp, const u8 *pmk_data, u16 pmk_wen)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_wsec_pmk_we pmk;
	int eww;

	memset(&pmk, 0, sizeof(pmk));

	/* pass pmk diwectwy */
	pmk.key_wen = cpu_to_we16(pmk_wen);
	pmk.fwags = cpu_to_we16(0);
	memcpy(pmk.key, pmk_data, pmk_wen);

	/* stowe psk in fiwmwawe */
	eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SET_WSEC_PMK,
				     &pmk, sizeof(pmk));
	if (eww < 0)
		bphy_eww(dwvw, "faiwed to change PSK in fiwmwawe (wen=%u)\n",
			 pmk_wen);

	wetuwn eww;
}

static int bwcmf_set_sae_passwowd(stwuct bwcmf_if *ifp, const u8 *pwd_data,
				  u16 pwd_wen)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_wsec_sae_pwd_we sae_pwd;
	int eww;

	if (pwd_wen > BWCMF_WSEC_MAX_SAE_PASSWOWD_WEN) {
		bphy_eww(dwvw, "sae_passwowd must be wess than %d\n",
			 BWCMF_WSEC_MAX_SAE_PASSWOWD_WEN);
		wetuwn -EINVAW;
	}

	sae_pwd.key_wen = cpu_to_we16(pwd_wen);
	memcpy(sae_pwd.key, pwd_data, pwd_wen);

	eww = bwcmf_fiw_iovaw_data_set(ifp, "sae_passwowd", &sae_pwd,
				       sizeof(sae_pwd));
	if (eww < 0)
		bphy_eww(dwvw, "faiwed to set SAE passwowd in fiwmwawe (wen=%u)\n",
			 pwd_wen);

	wetuwn eww;
}

static void bwcmf_wink_down(stwuct bwcmf_cfg80211_vif *vif, u16 weason,
			    boow wocawwy_genewated)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(vif->wdev.wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	boow bus_up = dwvw->bus_if->state == BWCMF_BUS_UP;
	s32 eww = 0;

	bwcmf_dbg(TWACE, "Entew\n");

	if (test_and_cweaw_bit(BWCMF_VIF_STATUS_CONNECTED, &vif->sme_state)) {
		if (bus_up) {
			bwcmf_dbg(INFO, "Caww WWC_DISASSOC to stop excess woaming\n");
			eww = bwcmf_fiw_cmd_data_set(vif->ifp,
						     BWCMF_C_DISASSOC, NUWW, 0);
			if (eww)
				bphy_eww(dwvw, "WWC_DISASSOC faiwed (%d)\n",
					 eww);
		}

		if ((vif->wdev.iftype == NW80211_IFTYPE_STATION) ||
		    (vif->wdev.iftype == NW80211_IFTYPE_P2P_CWIENT))
			cfg80211_disconnected(vif->wdev.netdev, weason, NUWW, 0,
					      wocawwy_genewated, GFP_KEWNEW);
	}
	cweaw_bit(BWCMF_VIF_STATUS_CONNECTING, &vif->sme_state);
	cweaw_bit(BWCMF_VIF_STATUS_EAP_SUCCESS, &vif->sme_state);
	cweaw_bit(BWCMF_VIF_STATUS_ASSOC_SUCCESS, &vif->sme_state);
	cweaw_bit(BWCMF_SCAN_STATUS_SUPPWESS, &cfg->scan_status);
	bwcmf_btcoex_set_mode(vif, BWCMF_BTCOEX_ENABWED, 0);
	if (vif->pwofiwe.use_fwsup != BWCMF_PWOFIWE_FWSUP_NONE) {
		if (bus_up)
			bwcmf_set_pmk(vif->ifp, NUWW, 0);
		vif->pwofiwe.use_fwsup = BWCMF_PWOFIWE_FWSUP_NONE;
	}
	bwcmf_dbg(TWACE, "Exit\n");
}

static s32
bwcmf_cfg80211_join_ibss(stwuct wiphy *wiphy, stwuct net_device *ndev,
		      stwuct cfg80211_ibss_pawams *pawams)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = &ifp->vif->pwofiwe;
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_join_pawams join_pawams;
	size_t join_pawams_size = 0;
	s32 eww = 0;
	s32 wsec = 0;
	s32 bcnpwd;
	u16 chanspec;
	u32 ssid_wen;

	bwcmf_dbg(TWACE, "Entew\n");
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	if (pawams->ssid)
		bwcmf_dbg(CONN, "SSID: %s\n", pawams->ssid);
	ewse {
		bwcmf_dbg(CONN, "SSID: NUWW, Not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	set_bit(BWCMF_VIF_STATUS_CONNECTING, &ifp->vif->sme_state);

	if (pawams->bssid)
		bwcmf_dbg(CONN, "BSSID: %pM\n", pawams->bssid);
	ewse
		bwcmf_dbg(CONN, "No BSSID specified\n");

	if (pawams->chandef.chan)
		bwcmf_dbg(CONN, "channew: %d\n",
			  pawams->chandef.chan->centew_fweq);
	ewse
		bwcmf_dbg(CONN, "no channew specified\n");

	if (pawams->channew_fixed)
		bwcmf_dbg(CONN, "fixed channew wequiwed\n");
	ewse
		bwcmf_dbg(CONN, "no fixed channew wequiwed\n");

	if (pawams->ie && pawams->ie_wen)
		bwcmf_dbg(CONN, "ie wen: %d\n", pawams->ie_wen);
	ewse
		bwcmf_dbg(CONN, "no ie specified\n");

	if (pawams->beacon_intewvaw)
		bwcmf_dbg(CONN, "beacon intewvaw: %d\n",
			  pawams->beacon_intewvaw);
	ewse
		bwcmf_dbg(CONN, "no beacon intewvaw specified\n");

	if (pawams->basic_wates)
		bwcmf_dbg(CONN, "basic wates: %08X\n", pawams->basic_wates);
	ewse
		bwcmf_dbg(CONN, "no basic wates specified\n");

	if (pawams->pwivacy)
		bwcmf_dbg(CONN, "pwivacy wequiwed\n");
	ewse
		bwcmf_dbg(CONN, "no pwivacy wequiwed\n");

	/* Configuwe Pwivacy fow stawtew */
	if (pawams->pwivacy)
		wsec |= WEP_ENABWED;

	eww = bwcmf_fiw_iovaw_int_set(ifp, "wsec", wsec);
	if (eww) {
		bphy_eww(dwvw, "wsec faiwed (%d)\n", eww);
		goto done;
	}

	/* Configuwe Beacon Intewvaw fow stawtew */
	if (pawams->beacon_intewvaw)
		bcnpwd = pawams->beacon_intewvaw;
	ewse
		bcnpwd = 100;

	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_BCNPWD, bcnpwd);
	if (eww) {
		bphy_eww(dwvw, "WWC_SET_BCNPWD faiwed (%d)\n", eww);
		goto done;
	}

	/* Configuwe wequiwed join pawametew */
	memset(&join_pawams, 0, sizeof(stwuct bwcmf_join_pawams));

	/* SSID */
	ssid_wen = min_t(u32, pawams->ssid_wen, IEEE80211_MAX_SSID_WEN);
	memcpy(join_pawams.ssid_we.SSID, pawams->ssid, ssid_wen);
	join_pawams.ssid_we.SSID_wen = cpu_to_we32(ssid_wen);
	join_pawams_size = sizeof(join_pawams.ssid_we);

	/* BSSID */
	if (pawams->bssid) {
		memcpy(join_pawams.pawams_we.bssid, pawams->bssid, ETH_AWEN);
		join_pawams_size += BWCMF_ASSOC_PAWAMS_FIXED_SIZE;
		memcpy(pwofiwe->bssid, pawams->bssid, ETH_AWEN);
	} ewse {
		eth_bwoadcast_addw(join_pawams.pawams_we.bssid);
		eth_zewo_addw(pwofiwe->bssid);
	}

	/* Channew */
	if (pawams->chandef.chan) {
		u32 tawget_channew;

		cfg->channew =
			ieee80211_fwequency_to_channew(
				pawams->chandef.chan->centew_fweq);
		if (pawams->channew_fixed) {
			/* adding chanspec */
			chanspec = chandef_to_chanspec(&cfg->d11inf,
						       &pawams->chandef);
			join_pawams.pawams_we.chanspec_wist[0] =
				cpu_to_we16(chanspec);
			join_pawams.pawams_we.chanspec_num = cpu_to_we32(1);
			join_pawams_size += sizeof(join_pawams.pawams_we);
		}

		/* set channew fow stawtew */
		tawget_channew = cfg->channew;
		eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_CHANNEW,
					    tawget_channew);
		if (eww) {
			bphy_eww(dwvw, "WWC_SET_CHANNEW faiwed (%d)\n", eww);
			goto done;
		}
	} ewse
		cfg->channew = 0;

	cfg->ibss_stawtew = fawse;


	eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SET_SSID,
				     &join_pawams, join_pawams_size);
	if (eww) {
		bphy_eww(dwvw, "WWC_SET_SSID faiwed (%d)\n", eww);
		goto done;
	}

done:
	if (eww)
		cweaw_bit(BWCMF_VIF_STATUS_CONNECTING, &ifp->vif->sme_state);
	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static s32
bwcmf_cfg80211_weave_ibss(stwuct wiphy *wiphy, stwuct net_device *ndev)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);

	bwcmf_dbg(TWACE, "Entew\n");
	if (!check_vif_up(ifp->vif)) {
		/* When dwivew is being unwoaded, it can end up hewe. If an
		 * ewwow is wetuwned then watew on a debug twace in the wiwewess
		 * cowe moduwe wiww be pwinted. To avoid this 0 is wetuwned.
		 */
		wetuwn 0;
	}

	bwcmf_wink_down(ifp->vif, WWAN_WEASON_DEAUTH_WEAVING, twue);
	bwcmf_net_setcawwiew(ifp, fawse);

	bwcmf_dbg(TWACE, "Exit\n");

	wetuwn 0;
}

static s32 bwcmf_set_wpa_vewsion(stwuct net_device *ndev,
				 stwuct cfg80211_connect_pawams *sme)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = ndev_to_pwof(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_cfg80211_secuwity *sec;
	s32 vaw = 0;
	s32 eww = 0;

	if (sme->cwypto.wpa_vewsions & NW80211_WPA_VEWSION_1)
		vaw = WPA_AUTH_PSK | WPA_AUTH_UNSPECIFIED;
	ewse if (sme->cwypto.wpa_vewsions & NW80211_WPA_VEWSION_2)
		vaw = WPA2_AUTH_PSK | WPA2_AUTH_UNSPECIFIED;
	ewse if (sme->cwypto.wpa_vewsions & NW80211_WPA_VEWSION_3)
		vaw = WPA3_AUTH_SAE_PSK;
	ewse
		vaw = WPA_AUTH_DISABWED;
	bwcmf_dbg(CONN, "setting wpa_auth to 0x%0x\n", vaw);
	eww = bwcmf_fiw_bsscfg_int_set(ifp, "wpa_auth", vaw);
	if (eww) {
		bphy_eww(dwvw, "set wpa_auth faiwed (%d)\n", eww);
		wetuwn eww;
	}
	sec = &pwofiwe->sec;
	sec->wpa_vewsions = sme->cwypto.wpa_vewsions;
	wetuwn eww;
}

static s32 bwcmf_set_auth_type(stwuct net_device *ndev,
			       stwuct cfg80211_connect_pawams *sme)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = ndev_to_pwof(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_cfg80211_secuwity *sec;
	s32 vaw = 0;
	s32 eww = 0;

	switch (sme->auth_type) {
	case NW80211_AUTHTYPE_OPEN_SYSTEM:
		vaw = 0;
		bwcmf_dbg(CONN, "open system\n");
		bweak;
	case NW80211_AUTHTYPE_SHAWED_KEY:
		vaw = 1;
		bwcmf_dbg(CONN, "shawed key\n");
		bweak;
	case NW80211_AUTHTYPE_SAE:
		vaw = 3;
		bwcmf_dbg(CONN, "SAE authentication\n");
		bweak;
	defauwt:
		vaw = 2;
		bwcmf_dbg(CONN, "automatic, auth type (%d)\n", sme->auth_type);
		bweak;
	}

	eww = bwcmf_fiw_bsscfg_int_set(ifp, "auth", vaw);
	if (eww) {
		bphy_eww(dwvw, "set auth faiwed (%d)\n", eww);
		wetuwn eww;
	}
	sec = &pwofiwe->sec;
	sec->auth_type = sme->auth_type;
	wetuwn eww;
}

static s32
bwcmf_set_wsec_mode(stwuct net_device *ndev,
		    stwuct cfg80211_connect_pawams *sme)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = ndev_to_pwof(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_cfg80211_secuwity *sec;
	s32 pvaw = 0;
	s32 gvaw = 0;
	s32 wsec;
	s32 eww = 0;

	if (sme->cwypto.n_ciphews_paiwwise) {
		switch (sme->cwypto.ciphews_paiwwise[0]) {
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
			pvaw = WEP_ENABWED;
			bweak;
		case WWAN_CIPHEW_SUITE_TKIP:
			pvaw = TKIP_ENABWED;
			bweak;
		case WWAN_CIPHEW_SUITE_CCMP:
			pvaw = AES_ENABWED;
			bweak;
		case WWAN_CIPHEW_SUITE_AES_CMAC:
			pvaw = AES_ENABWED;
			bweak;
		defauwt:
			bphy_eww(dwvw, "invawid ciphew paiwwise (%d)\n",
				 sme->cwypto.ciphews_paiwwise[0]);
			wetuwn -EINVAW;
		}
	}
	if (sme->cwypto.ciphew_gwoup) {
		switch (sme->cwypto.ciphew_gwoup) {
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
			gvaw = WEP_ENABWED;
			bweak;
		case WWAN_CIPHEW_SUITE_TKIP:
			gvaw = TKIP_ENABWED;
			bweak;
		case WWAN_CIPHEW_SUITE_CCMP:
			gvaw = AES_ENABWED;
			bweak;
		case WWAN_CIPHEW_SUITE_AES_CMAC:
			gvaw = AES_ENABWED;
			bweak;
		defauwt:
			bphy_eww(dwvw, "invawid ciphew gwoup (%d)\n",
				 sme->cwypto.ciphew_gwoup);
			wetuwn -EINVAW;
		}
	}

	bwcmf_dbg(CONN, "pvaw (%d) gvaw (%d)\n", pvaw, gvaw);
	/* In case of pwivacy, but no secuwity and WPS then simuwate */
	/* setting AES. WPS-2.0 awwows no secuwity                   */
	if (bwcmf_find_wpsie(sme->ie, sme->ie_wen) && !pvaw && !gvaw &&
	    sme->pwivacy)
		pvaw = AES_ENABWED;

	wsec = pvaw | gvaw;
	eww = bwcmf_fiw_bsscfg_int_set(ifp, "wsec", wsec);
	if (eww) {
		bphy_eww(dwvw, "ewwow (%d)\n", eww);
		wetuwn eww;
	}

	sec = &pwofiwe->sec;
	sec->ciphew_paiwwise = sme->cwypto.ciphews_paiwwise[0];
	sec->ciphew_gwoup = sme->cwypto.ciphew_gwoup;

	wetuwn eww;
}

static s32
bwcmf_set_key_mgmt(stwuct net_device *ndev, stwuct cfg80211_connect_pawams *sme)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = &ifp->vif->pwofiwe;
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 vaw;
	s32 eww;
	const stwuct bwcmf_twv *wsn_ie;
	const u8 *ie;
	u32 ie_wen;
	u32 offset;
	u16 wsn_cap;
	u32 mfp;
	u16 count;

	pwofiwe->use_fwsup = BWCMF_PWOFIWE_FWSUP_NONE;
	pwofiwe->is_ft = fawse;

	if (!sme->cwypto.n_akm_suites)
		wetuwn 0;

	eww = bwcmf_fiw_bsscfg_int_get(netdev_pwiv(ndev), "wpa_auth", &vaw);
	if (eww) {
		bphy_eww(dwvw, "couwd not get wpa_auth (%d)\n", eww);
		wetuwn eww;
	}
	if (vaw & (WPA_AUTH_PSK | WPA_AUTH_UNSPECIFIED)) {
		switch (sme->cwypto.akm_suites[0]) {
		case WWAN_AKM_SUITE_8021X:
			vaw = WPA_AUTH_UNSPECIFIED;
			if (sme->want_1x)
				pwofiwe->use_fwsup = BWCMF_PWOFIWE_FWSUP_1X;
			bweak;
		case WWAN_AKM_SUITE_PSK:
			vaw = WPA_AUTH_PSK;
			bweak;
		defauwt:
			bphy_eww(dwvw, "invawid akm suite (%d)\n",
				 sme->cwypto.akm_suites[0]);
			wetuwn -EINVAW;
		}
	} ewse if (vaw & (WPA2_AUTH_PSK | WPA2_AUTH_UNSPECIFIED)) {
		switch (sme->cwypto.akm_suites[0]) {
		case WWAN_AKM_SUITE_8021X:
			vaw = WPA2_AUTH_UNSPECIFIED;
			if (sme->want_1x)
				pwofiwe->use_fwsup = BWCMF_PWOFIWE_FWSUP_1X;
			bweak;
		case WWAN_AKM_SUITE_8021X_SHA256:
			vaw = WPA2_AUTH_1X_SHA256;
			if (sme->want_1x)
				pwofiwe->use_fwsup = BWCMF_PWOFIWE_FWSUP_1X;
			bweak;
		case WWAN_AKM_SUITE_PSK_SHA256:
			vaw = WPA2_AUTH_PSK_SHA256;
			bweak;
		case WWAN_AKM_SUITE_PSK:
			vaw = WPA2_AUTH_PSK;
			bweak;
		case WWAN_AKM_SUITE_FT_8021X:
			vaw = WPA2_AUTH_UNSPECIFIED | WPA2_AUTH_FT;
			pwofiwe->is_ft = twue;
			if (sme->want_1x)
				pwofiwe->use_fwsup = BWCMF_PWOFIWE_FWSUP_1X;
			bweak;
		case WWAN_AKM_SUITE_FT_PSK:
			vaw = WPA2_AUTH_PSK | WPA2_AUTH_FT;
			pwofiwe->is_ft = twue;
			bweak;
		defauwt:
			bphy_eww(dwvw, "invawid akm suite (%d)\n",
				 sme->cwypto.akm_suites[0]);
			wetuwn -EINVAW;
		}
	} ewse if (vaw & WPA3_AUTH_SAE_PSK) {
		switch (sme->cwypto.akm_suites[0]) {
		case WWAN_AKM_SUITE_SAE:
			vaw = WPA3_AUTH_SAE_PSK;
			if (sme->cwypto.sae_pwd) {
				bwcmf_dbg(INFO, "using SAE offwoad\n");
				pwofiwe->use_fwsup = BWCMF_PWOFIWE_FWSUP_SAE;
			}
			bweak;
		case WWAN_AKM_SUITE_FT_OVEW_SAE:
			vaw = WPA3_AUTH_SAE_PSK | WPA2_AUTH_FT;
			pwofiwe->is_ft = twue;
			if (sme->cwypto.sae_pwd) {
				bwcmf_dbg(INFO, "using SAE offwoad\n");
				pwofiwe->use_fwsup = BWCMF_PWOFIWE_FWSUP_SAE;
			}
			bweak;
		defauwt:
			bphy_eww(dwvw, "invawid akm suite (%d)\n",
				 sme->cwypto.akm_suites[0]);
			wetuwn -EINVAW;
		}
	}

	if (pwofiwe->use_fwsup == BWCMF_PWOFIWE_FWSUP_1X)
		bwcmf_dbg(INFO, "using 1X offwoad\n");

	if (!bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MFP))
		goto skip_mfp_config;
	/* The MFP mode (1 ow 2) needs to be detewmined, pawse IEs. The
	 * IE wiww not be vewified, just a quick seawch fow MFP config
	 */
	wsn_ie = bwcmf_pawse_twvs((const u8 *)sme->ie, sme->ie_wen,
				  WWAN_EID_WSN);
	if (!wsn_ie)
		goto skip_mfp_config;
	ie = (const u8 *)wsn_ie;
	ie_wen = wsn_ie->wen + TWV_HDW_WEN;
	/* Skip unicast suite */
	offset = TWV_HDW_WEN + WPA_IE_VEWSION_WEN + WPA_IE_MIN_OUI_WEN;
	if (offset + WPA_IE_SUITE_COUNT_WEN >= ie_wen)
		goto skip_mfp_config;
	/* Skip muwticast suite */
	count = ie[offset] + (ie[offset + 1] << 8);
	offset += WPA_IE_SUITE_COUNT_WEN + (count * WPA_IE_MIN_OUI_WEN);
	if (offset + WPA_IE_SUITE_COUNT_WEN >= ie_wen)
		goto skip_mfp_config;
	/* Skip auth key management suite(s) */
	count = ie[offset] + (ie[offset + 1] << 8);
	offset += WPA_IE_SUITE_COUNT_WEN + (count * WPA_IE_MIN_OUI_WEN);
	if (offset + WPA_IE_SUITE_COUNT_WEN > ie_wen)
		goto skip_mfp_config;
	/* Weady to wead capabiwities */
	mfp = BWCMF_MFP_NONE;
	wsn_cap = ie[offset] + (ie[offset + 1] << 8);
	if (wsn_cap & WSN_CAP_MFPW_MASK)
		mfp = BWCMF_MFP_WEQUIWED;
	ewse if (wsn_cap & WSN_CAP_MFPC_MASK)
		mfp = BWCMF_MFP_CAPABWE;
	bwcmf_fiw_bsscfg_int_set(netdev_pwiv(ndev), "mfp", mfp);

skip_mfp_config:
	bwcmf_dbg(CONN, "setting wpa_auth to %d\n", vaw);
	eww = bwcmf_fiw_bsscfg_int_set(netdev_pwiv(ndev), "wpa_auth", vaw);
	if (eww) {
		bphy_eww(dwvw, "couwd not set wpa_auth (%d)\n", eww);
		wetuwn eww;
	}

	wetuwn eww;
}

static s32
bwcmf_set_shawedkey(stwuct net_device *ndev,
		    stwuct cfg80211_connect_pawams *sme)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = ndev_to_pwof(ndev);
	stwuct bwcmf_cfg80211_secuwity *sec;
	stwuct bwcmf_wsec_key key;
	s32 vaw;
	s32 eww = 0;

	bwcmf_dbg(CONN, "key wen (%d)\n", sme->key_wen);

	if (sme->key_wen == 0)
		wetuwn 0;

	sec = &pwofiwe->sec;
	bwcmf_dbg(CONN, "wpa_vewsions 0x%x ciphew_paiwwise 0x%x\n",
		  sec->wpa_vewsions, sec->ciphew_paiwwise);

	if (sec->wpa_vewsions & (NW80211_WPA_VEWSION_1 | NW80211_WPA_VEWSION_2 |
				 NW80211_WPA_VEWSION_3))
		wetuwn 0;

	if (!(sec->ciphew_paiwwise &
	    (WWAN_CIPHEW_SUITE_WEP40 | WWAN_CIPHEW_SUITE_WEP104)))
		wetuwn 0;

	memset(&key, 0, sizeof(key));
	key.wen = (u32) sme->key_wen;
	key.index = (u32) sme->key_idx;
	if (key.wen > sizeof(key.data)) {
		bphy_eww(dwvw, "Too wong key wength (%u)\n", key.wen);
		wetuwn -EINVAW;
	}
	memcpy(key.data, sme->key, key.wen);
	key.fwags = BWCMF_PWIMAWY_KEY;
	switch (sec->ciphew_paiwwise) {
	case WWAN_CIPHEW_SUITE_WEP40:
		key.awgo = CWYPTO_AWGO_WEP1;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		key.awgo = CWYPTO_AWGO_WEP128;
		bweak;
	defauwt:
		bphy_eww(dwvw, "Invawid awgowithm (%d)\n",
			 sme->cwypto.ciphews_paiwwise[0]);
		wetuwn -EINVAW;
	}
	/* Set the new key/index */
	bwcmf_dbg(CONN, "key wength (%d) key index (%d) awgo (%d)\n",
		  key.wen, key.index, key.awgo);
	bwcmf_dbg(CONN, "key \"%s\"\n", key.data);
	eww = send_key_to_dongwe(ifp, &key);
	if (eww)
		wetuwn eww;

	if (sec->auth_type == NW80211_AUTHTYPE_SHAWED_KEY) {
		bwcmf_dbg(CONN, "set auth_type to shawed key\n");
		vaw = WW_AUTH_SHAWED_KEY;	/* shawed key */
		eww = bwcmf_fiw_bsscfg_int_set(ifp, "auth", vaw);
		if (eww)
			bphy_eww(dwvw, "set auth faiwed (%d)\n", eww);
	}
	wetuwn eww;
}

static
enum nw80211_auth_type bwcmf_waw_auth_type(stwuct bwcmf_if *ifp,
					   enum nw80211_auth_type type)
{
	if (type == NW80211_AUTHTYPE_AUTOMATIC &&
	    bwcmf_feat_is_quiwk_enabwed(ifp, BWCMF_FEAT_QUIWK_AUTO_AUTH)) {
		bwcmf_dbg(CONN, "WAW: use OPEN instead of AUTO\n");
		type = NW80211_AUTHTYPE_OPEN_SYSTEM;
	}
	wetuwn type;
}

static void bwcmf_set_join_pwef(stwuct bwcmf_if *ifp,
				stwuct cfg80211_bss_sewection *bss_sewect)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_join_pwef_pawams join_pwef_pawams[2];
	enum nw80211_band band;
	int eww, i = 0;

	join_pwef_pawams[i].wen = 2;
	join_pwef_pawams[i].wssi_gain = 0;

	if (bss_sewect->behaviouw != NW80211_BSS_SEWECT_ATTW_BAND_PWEF)
		bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_ASSOC_PWEFEW, WWC_BAND_AUTO);

	switch (bss_sewect->behaviouw) {
	case __NW80211_BSS_SEWECT_ATTW_INVAWID:
		bwcmf_c_set_joinpwef_defauwt(ifp);
		wetuwn;
	case NW80211_BSS_SEWECT_ATTW_BAND_PWEF:
		join_pwef_pawams[i].type = BWCMF_JOIN_PWEF_BAND;
		band = bss_sewect->pawam.band_pwef;
		join_pwef_pawams[i].band = nw80211_band_to_fwiw(band);
		i++;
		bweak;
	case NW80211_BSS_SEWECT_ATTW_WSSI_ADJUST:
		join_pwef_pawams[i].type = BWCMF_JOIN_PWEF_WSSI_DEWTA;
		band = bss_sewect->pawam.adjust.band;
		join_pwef_pawams[i].band = nw80211_band_to_fwiw(band);
		join_pwef_pawams[i].wssi_gain = bss_sewect->pawam.adjust.dewta;
		i++;
		bweak;
	case NW80211_BSS_SEWECT_ATTW_WSSI:
	defauwt:
		bweak;
	}
	join_pwef_pawams[i].type = BWCMF_JOIN_PWEF_WSSI;
	join_pwef_pawams[i].wen = 2;
	join_pwef_pawams[i].wssi_gain = 0;
	join_pwef_pawams[i].band = 0;
	eww = bwcmf_fiw_iovaw_data_set(ifp, "join_pwef", join_pwef_pawams,
				       sizeof(join_pwef_pawams));
	if (eww)
		bphy_eww(dwvw, "Set join_pwef ewwow (%d)\n", eww);
}

static s32
bwcmf_cfg80211_connect(stwuct wiphy *wiphy, stwuct net_device *ndev,
		       stwuct cfg80211_connect_pawams *sme)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = &ifp->vif->pwofiwe;
	stwuct ieee80211_channew *chan = sme->channew;
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_join_pawams join_pawams;
	size_t join_pawams_size;
	const stwuct bwcmf_twv *wsn_ie;
	const stwuct bwcmf_vs_twv *wpa_ie;
	const void *ie;
	u32 ie_wen;
	stwuct bwcmf_ext_join_pawams_we *ext_join_pawams;
	u16 chanspec;
	s32 eww = 0;
	u32 ssid_wen;

	bwcmf_dbg(TWACE, "Entew\n");
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	if (!sme->ssid) {
		bphy_eww(dwvw, "Invawid ssid\n");
		wetuwn -EOPNOTSUPP;
	}

	if (sme->channew_hint)
		chan = sme->channew_hint;

	if (sme->bssid_hint)
		sme->bssid = sme->bssid_hint;

	if (ifp->vif == cfg->p2p.bss_idx[P2PAPI_BSSCFG_PWIMAWY].vif) {
		/* A nowmaw (non P2P) connection wequest setup. */
		ie = NUWW;
		ie_wen = 0;
		/* find the WPA_IE */
		wpa_ie = bwcmf_find_wpaie((u8 *)sme->ie, sme->ie_wen);
		if (wpa_ie) {
			ie = wpa_ie;
			ie_wen = wpa_ie->wen + TWV_HDW_WEN;
		} ewse {
			/* find the WSN_IE */
			wsn_ie = bwcmf_pawse_twvs((const u8 *)sme->ie,
						  sme->ie_wen,
						  WWAN_EID_WSN);
			if (wsn_ie) {
				ie = wsn_ie;
				ie_wen = wsn_ie->wen + TWV_HDW_WEN;
			}
		}
		bwcmf_fiw_iovaw_data_set(ifp, "wpaie", ie, ie_wen);
	}

	eww = bwcmf_vif_set_mgmt_ie(ifp->vif, BWCMF_VNDW_IE_ASSOCWEQ_FWAG,
				    sme->ie, sme->ie_wen);
	if (eww)
		bphy_eww(dwvw, "Set Assoc WEQ IE Faiwed\n");
	ewse
		bwcmf_dbg(TWACE, "Appwied Vndw IEs fow Assoc wequest\n");

	set_bit(BWCMF_VIF_STATUS_CONNECTING, &ifp->vif->sme_state);

	if (chan) {
		cfg->channew =
			ieee80211_fwequency_to_channew(chan->centew_fweq);
		chanspec = channew_to_chanspec(&cfg->d11inf, chan);
		bwcmf_dbg(CONN, "channew=%d, centew_weq=%d, chanspec=0x%04x\n",
			  cfg->channew, chan->centew_fweq, chanspec);
	} ewse {
		cfg->channew = 0;
		chanspec = 0;
	}

	bwcmf_dbg(INFO, "ie (%p), ie_wen (%zd)\n", sme->ie, sme->ie_wen);

	eww = bwcmf_set_wpa_vewsion(ndev, sme);
	if (eww) {
		bphy_eww(dwvw, "ww_set_wpa_vewsion faiwed (%d)\n", eww);
		goto done;
	}

	sme->auth_type = bwcmf_waw_auth_type(ifp, sme->auth_type);
	eww = bwcmf_set_auth_type(ndev, sme);
	if (eww) {
		bphy_eww(dwvw, "ww_set_auth_type faiwed (%d)\n", eww);
		goto done;
	}

	eww = bwcmf_set_wsec_mode(ndev, sme);
	if (eww) {
		bphy_eww(dwvw, "ww_set_set_ciphew faiwed (%d)\n", eww);
		goto done;
	}

	eww = bwcmf_set_key_mgmt(ndev, sme);
	if (eww) {
		bphy_eww(dwvw, "ww_set_key_mgmt faiwed (%d)\n", eww);
		goto done;
	}

	eww = bwcmf_set_shawedkey(ndev, sme);
	if (eww) {
		bphy_eww(dwvw, "bwcmf_set_shawedkey faiwed (%d)\n", eww);
		goto done;
	}

	if (sme->cwypto.psk &&
	    pwofiwe->use_fwsup != BWCMF_PWOFIWE_FWSUP_SAE) {
		if (WAWN_ON(pwofiwe->use_fwsup != BWCMF_PWOFIWE_FWSUP_NONE)) {
			eww = -EINVAW;
			goto done;
		}
		bwcmf_dbg(INFO, "using PSK offwoad\n");
		pwofiwe->use_fwsup = BWCMF_PWOFIWE_FWSUP_PSK;
	}

	if (pwofiwe->use_fwsup != BWCMF_PWOFIWE_FWSUP_NONE) {
		/* enabwe fiwmwawe suppwicant fow this intewface */
		eww = bwcmf_fiw_iovaw_int_set(ifp, "sup_wpa", 1);
		if (eww < 0) {
			bphy_eww(dwvw, "faiwed to enabwe fw suppwicant\n");
			goto done;
		}
	}

	if (pwofiwe->use_fwsup == BWCMF_PWOFIWE_FWSUP_PSK)
		eww = bwcmf_set_pmk(ifp, sme->cwypto.psk,
				    BWCMF_WSEC_MAX_PSK_WEN);
	ewse if (pwofiwe->use_fwsup == BWCMF_PWOFIWE_FWSUP_SAE) {
		/* cwean up usew-space WSNE */
		eww = bwcmf_fiw_iovaw_data_set(ifp, "wpaie", NUWW, 0);
		if (eww) {
			bphy_eww(dwvw, "faiwed to cwean up usew-space WSNE\n");
			goto done;
		}
		eww = bwcmf_set_sae_passwowd(ifp, sme->cwypto.sae_pwd,
					     sme->cwypto.sae_pwd_wen);
		if (!eww && sme->cwypto.psk)
			eww = bwcmf_set_pmk(ifp, sme->cwypto.psk,
					    BWCMF_WSEC_MAX_PSK_WEN);
	}
	if (eww)
		goto done;

	/* Join with specific BSSID and cached SSID
	 * If SSID is zewo join based on BSSID onwy
	 */
	join_pawams_size = offsetof(stwuct bwcmf_ext_join_pawams_we, assoc_we) +
		offsetof(stwuct bwcmf_assoc_pawams_we, chanspec_wist);
	if (cfg->channew)
		join_pawams_size += sizeof(u16);
	ext_join_pawams = kzawwoc(sizeof(*ext_join_pawams), GFP_KEWNEW);
	if (ext_join_pawams == NUWW) {
		eww = -ENOMEM;
		goto done;
	}
	ssid_wen = min_t(u32, sme->ssid_wen, IEEE80211_MAX_SSID_WEN);
	ext_join_pawams->ssid_we.SSID_wen = cpu_to_we32(ssid_wen);
	memcpy(&ext_join_pawams->ssid_we.SSID, sme->ssid, ssid_wen);
	if (ssid_wen < IEEE80211_MAX_SSID_WEN)
		bwcmf_dbg(CONN, "SSID \"%s\", wen (%d)\n",
			  ext_join_pawams->ssid_we.SSID, ssid_wen);

	/* Set up join scan pawametews */
	ext_join_pawams->scan_we.scan_type = -1;
	ext_join_pawams->scan_we.home_time = cpu_to_we32(-1);

	if (sme->bssid)
		memcpy(&ext_join_pawams->assoc_we.bssid, sme->bssid, ETH_AWEN);
	ewse
		eth_bwoadcast_addw(ext_join_pawams->assoc_we.bssid);

	if (cfg->channew) {
		ext_join_pawams->assoc_we.chanspec_num = cpu_to_we32(1);

		ext_join_pawams->assoc_we.chanspec_wist[0] =
			cpu_to_we16(chanspec);
		/* Incwease dweww time to weceive pwobe wesponse ow detect
		 * beacon fwom tawget AP at a noisy aiw onwy duwing connect
		 * command.
		 */
		ext_join_pawams->scan_we.active_time =
			cpu_to_we32(BWCMF_SCAN_JOIN_ACTIVE_DWEWW_TIME_MS);
		ext_join_pawams->scan_we.passive_time =
			cpu_to_we32(BWCMF_SCAN_JOIN_PASSIVE_DWEWW_TIME_MS);
		/* To sync with pwesence pewiod of VSDB GO send pwobe wequest
		 * mowe fwequentwy. Pwobe wequest wiww be stopped when it gets
		 * pwobe wesponse fwom tawget AP/GO.
		 */
		ext_join_pawams->scan_we.npwobes =
			cpu_to_we32(BWCMF_SCAN_JOIN_ACTIVE_DWEWW_TIME_MS /
				    BWCMF_SCAN_JOIN_PWOBE_INTEWVAW_MS);
	} ewse {
		ext_join_pawams->scan_we.active_time = cpu_to_we32(-1);
		ext_join_pawams->scan_we.passive_time = cpu_to_we32(-1);
		ext_join_pawams->scan_we.npwobes = cpu_to_we32(-1);
	}

	bwcmf_set_join_pwef(ifp, &sme->bss_sewect);

	eww  = bwcmf_fiw_bsscfg_data_set(ifp, "join", ext_join_pawams,
					 join_pawams_size);
	kfwee(ext_join_pawams);
	if (!eww)
		/* This is it. join command wowked, we awe done */
		goto done;

	/* join command faiwed, fawwback to set ssid */
	memset(&join_pawams, 0, sizeof(join_pawams));
	join_pawams_size = sizeof(join_pawams.ssid_we);

	memcpy(&join_pawams.ssid_we.SSID, sme->ssid, ssid_wen);
	join_pawams.ssid_we.SSID_wen = cpu_to_we32(ssid_wen);

	if (sme->bssid)
		memcpy(join_pawams.pawams_we.bssid, sme->bssid, ETH_AWEN);
	ewse
		eth_bwoadcast_addw(join_pawams.pawams_we.bssid);

	if (cfg->channew) {
		join_pawams.pawams_we.chanspec_wist[0] = cpu_to_we16(chanspec);
		join_pawams.pawams_we.chanspec_num = cpu_to_we32(1);
		join_pawams_size += sizeof(join_pawams.pawams_we);
	}
	eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SET_SSID,
				     &join_pawams, join_pawams_size);
	if (eww)
		bphy_eww(dwvw, "BWCMF_C_SET_SSID faiwed (%d)\n", eww);

done:
	if (eww)
		cweaw_bit(BWCMF_VIF_STATUS_CONNECTING, &ifp->vif->sme_state);
	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static s32
bwcmf_cfg80211_disconnect(stwuct wiphy *wiphy, stwuct net_device *ndev,
		       u16 weason_code)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = &ifp->vif->pwofiwe;
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_scb_vaw_we scbvaw;
	s32 eww = 0;

	bwcmf_dbg(TWACE, "Entew. Weason code = %d\n", weason_code);
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	cweaw_bit(BWCMF_VIF_STATUS_CONNECTED, &ifp->vif->sme_state);
	cweaw_bit(BWCMF_VIF_STATUS_CONNECTING, &ifp->vif->sme_state);
	cweaw_bit(BWCMF_VIF_STATUS_EAP_SUCCESS, &ifp->vif->sme_state);
	cweaw_bit(BWCMF_VIF_STATUS_ASSOC_SUCCESS, &ifp->vif->sme_state);
	cfg80211_disconnected(ndev, weason_code, NUWW, 0, twue, GFP_KEWNEW);

	memcpy(&scbvaw.ea, &pwofiwe->bssid, ETH_AWEN);
	scbvaw.vaw = cpu_to_we32(weason_code);
	eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_DISASSOC,
				     &scbvaw, sizeof(scbvaw));
	if (eww)
		bphy_eww(dwvw, "ewwow (%d)\n", eww);

	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static s32
bwcmf_cfg80211_set_tx_powew(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
			    enum nw80211_tx_powew_setting type, s32 mbm)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct net_device *ndev = cfg_to_ndev(cfg);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	s32 eww;
	s32 disabwe;
	u32 qdbm = 127;

	bwcmf_dbg(TWACE, "Entew %d %d\n", type, mbm);
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	switch (type) {
	case NW80211_TX_POWEW_AUTOMATIC:
		bweak;
	case NW80211_TX_POWEW_WIMITED:
	case NW80211_TX_POWEW_FIXED:
		if (mbm < 0) {
			bphy_eww(dwvw, "TX_POWEW_FIXED - dbm is negative\n");
			eww = -EINVAW;
			goto done;
		}
		qdbm =  MBM_TO_DBM(4 * mbm);
		if (qdbm > 127)
			qdbm = 127;
		qdbm |= WW_TXPWW_OVEWWIDE;
		bweak;
	defauwt:
		bphy_eww(dwvw, "Unsuppowted type %d\n", type);
		eww = -EINVAW;
		goto done;
	}
	/* Make suwe wadio is off ow on as faw as softwawe is concewned */
	disabwe = WW_WADIO_SW_DISABWE << 16;
	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_WADIO, disabwe);
	if (eww)
		bphy_eww(dwvw, "WWC_SET_WADIO ewwow (%d)\n", eww);

	eww = bwcmf_fiw_iovaw_int_set(ifp, "qtxpowew", qdbm);
	if (eww)
		bphy_eww(dwvw, "qtxpowew ewwow (%d)\n", eww);

done:
	bwcmf_dbg(TWACE, "Exit %d (qdbm)\n", qdbm & ~WW_TXPWW_OVEWWIDE);
	wetuwn eww;
}

static s32
bwcmf_cfg80211_get_tx_powew(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
			    s32 *dbm)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_cfg80211_vif *vif = wdev_to_vif(wdev);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	s32 qdbm = 0;
	s32 eww;

	bwcmf_dbg(TWACE, "Entew\n");
	if (!check_vif_up(vif))
		wetuwn -EIO;

	eww = bwcmf_fiw_iovaw_int_get(vif->ifp, "qtxpowew", &qdbm);
	if (eww) {
		bphy_eww(dwvw, "ewwow (%d)\n", eww);
		goto done;
	}
	*dbm = (qdbm & ~WW_TXPWW_OVEWWIDE) / 4;

done:
	bwcmf_dbg(TWACE, "Exit (0x%x %d)\n", qdbm, *dbm);
	wetuwn eww;
}

static s32
bwcmf_cfg80211_config_defauwt_key(stwuct wiphy *wiphy, stwuct net_device *ndev,
				  int wink_id, u8 key_idx, boow unicast,
				  boow muwticast)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	u32 index;
	u32 wsec;
	s32 eww = 0;

	bwcmf_dbg(TWACE, "Entew\n");
	bwcmf_dbg(CONN, "key index (%d)\n", key_idx);
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	eww = bwcmf_fiw_bsscfg_int_get(ifp, "wsec", &wsec);
	if (eww) {
		bphy_eww(dwvw, "WWC_GET_WSEC ewwow (%d)\n", eww);
		goto done;
	}

	if (wsec & WEP_ENABWED) {
		/* Just sewect a new cuwwent key */
		index = key_idx;
		eww = bwcmf_fiw_cmd_int_set(ifp,
					    BWCMF_C_SET_KEY_PWIMAWY, index);
		if (eww)
			bphy_eww(dwvw, "ewwow (%d)\n", eww);
	}
done:
	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static s32
bwcmf_cfg80211_dew_key(stwuct wiphy *wiphy, stwuct net_device *ndev,
		       int wink_id, u8 key_idx, boow paiwwise,
		       const u8 *mac_addw)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_wsec_key *key;
	s32 eww;

	bwcmf_dbg(TWACE, "Entew\n");
	bwcmf_dbg(CONN, "key index (%d)\n", key_idx);

	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	if (key_idx >= BWCMF_MAX_DEFAUWT_KEYS) {
		/* we ignowe this key index in this case */
		wetuwn -EINVAW;
	}

	key = &ifp->vif->pwofiwe.key[key_idx];

	if (key->awgo == CWYPTO_AWGO_OFF) {
		bwcmf_dbg(CONN, "Ignowe cweawing of (nevew configuwed) key\n");
		wetuwn -EINVAW;
	}

	memset(key, 0, sizeof(*key));
	key->index = (u32)key_idx;
	key->fwags = BWCMF_PWIMAWY_KEY;

	/* Cweaw the key/index */
	eww = send_key_to_dongwe(ifp, key);

	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static s32
bwcmf_cfg80211_add_key(stwuct wiphy *wiphy, stwuct net_device *ndev,
		       int wink_id, u8 key_idx, boow paiwwise,
		       const u8 *mac_addw, stwuct key_pawams *pawams)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_wsec_key *key;
	s32 vaw;
	s32 wsec;
	s32 eww;
	u8 keybuf[8];
	boow ext_key;

	bwcmf_dbg(TWACE, "Entew\n");
	bwcmf_dbg(CONN, "key index (%d)\n", key_idx);
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	if (key_idx >= BWCMF_MAX_DEFAUWT_KEYS) {
		/* we ignowe this key index in this case */
		bphy_eww(dwvw, "invawid key index (%d)\n", key_idx);
		wetuwn -EINVAW;
	}

	if (pawams->key_wen == 0)
		wetuwn bwcmf_cfg80211_dew_key(wiphy, ndev, -1, key_idx,
					      paiwwise, mac_addw);

	if (pawams->key_wen > sizeof(key->data)) {
		bphy_eww(dwvw, "Too wong key wength (%u)\n", pawams->key_wen);
		wetuwn -EINVAW;
	}

	ext_key = fawse;
	if (mac_addw && (pawams->ciphew != WWAN_CIPHEW_SUITE_WEP40) &&
	    (pawams->ciphew != WWAN_CIPHEW_SUITE_WEP104)) {
		bwcmf_dbg(TWACE, "Ext key, mac %pM", mac_addw);
		ext_key = twue;
	}

	key = &ifp->vif->pwofiwe.key[key_idx];
	memset(key, 0, sizeof(*key));
	if ((ext_key) && (!is_muwticast_ethew_addw(mac_addw)))
		memcpy((chaw *)&key->ea, (void *)mac_addw, ETH_AWEN);
	key->wen = pawams->key_wen;
	key->index = key_idx;
	memcpy(key->data, pawams->key, key->wen);
	if (!ext_key)
		key->fwags = BWCMF_PWIMAWY_KEY;

	if (pawams->seq && pawams->seq_wen == 6) {
		/* wx iv */
		u8 *ivptw;

		ivptw = (u8 *)pawams->seq;
		key->wxiv.hi = (ivptw[5] << 24) | (ivptw[4] << 16) |
			(ivptw[3] << 8) | ivptw[2];
		key->wxiv.wo = (ivptw[1] << 8) | ivptw[0];
		key->iv_initiawized = twue;
	}

	switch (pawams->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		key->awgo = CWYPTO_AWGO_WEP1;
		vaw = WEP_ENABWED;
		bwcmf_dbg(CONN, "WWAN_CIPHEW_SUITE_WEP40\n");
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		key->awgo = CWYPTO_AWGO_WEP128;
		vaw = WEP_ENABWED;
		bwcmf_dbg(CONN, "WWAN_CIPHEW_SUITE_WEP104\n");
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		if (!bwcmf_is_apmode(ifp->vif)) {
			bwcmf_dbg(CONN, "Swapping WX/TX MIC key\n");
			memcpy(keybuf, &key->data[24], sizeof(keybuf));
			memcpy(&key->data[24], &key->data[16], sizeof(keybuf));
			memcpy(&key->data[16], keybuf, sizeof(keybuf));
		}
		key->awgo = CWYPTO_AWGO_TKIP;
		vaw = TKIP_ENABWED;
		bwcmf_dbg(CONN, "WWAN_CIPHEW_SUITE_TKIP\n");
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
		key->awgo = CWYPTO_AWGO_AES_CCM;
		vaw = AES_ENABWED;
		bwcmf_dbg(CONN, "WWAN_CIPHEW_SUITE_AES_CMAC\n");
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		key->awgo = CWYPTO_AWGO_AES_CCM;
		vaw = AES_ENABWED;
		bwcmf_dbg(CONN, "WWAN_CIPHEW_SUITE_CCMP\n");
		bweak;
	defauwt:
		bphy_eww(dwvw, "Invawid ciphew (0x%x)\n", pawams->ciphew);
		eww = -EINVAW;
		goto done;
	}

	eww = send_key_to_dongwe(ifp, key);
	if (ext_key || eww)
		goto done;

	eww = bwcmf_fiw_bsscfg_int_get(ifp, "wsec", &wsec);
	if (eww) {
		bphy_eww(dwvw, "get wsec ewwow (%d)\n", eww);
		goto done;
	}
	wsec |= vaw;
	eww = bwcmf_fiw_bsscfg_int_set(ifp, "wsec", wsec);
	if (eww) {
		bphy_eww(dwvw, "set wsec ewwow (%d)\n", eww);
		goto done;
	}

done:
	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static s32
bwcmf_cfg80211_get_key(stwuct wiphy *wiphy, stwuct net_device *ndev,
		       int wink_id, u8 key_idx, boow paiwwise,
		       const u8 *mac_addw, void *cookie,
		       void (*cawwback)(void *cookie,
					stwuct key_pawams *pawams))
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct key_pawams pawams;
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = &ifp->vif->pwofiwe;
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_cfg80211_secuwity *sec;
	s32 wsec;
	s32 eww = 0;

	bwcmf_dbg(TWACE, "Entew\n");
	bwcmf_dbg(CONN, "key index (%d)\n", key_idx);
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	memset(&pawams, 0, sizeof(pawams));

	eww = bwcmf_fiw_bsscfg_int_get(ifp, "wsec", &wsec);
	if (eww) {
		bphy_eww(dwvw, "WWC_GET_WSEC ewwow (%d)\n", eww);
		/* Ignowe this ewwow, may happen duwing DISASSOC */
		eww = -EAGAIN;
		goto done;
	}
	if (wsec & WEP_ENABWED) {
		sec = &pwofiwe->sec;
		if (sec->ciphew_paiwwise & WWAN_CIPHEW_SUITE_WEP40) {
			pawams.ciphew = WWAN_CIPHEW_SUITE_WEP40;
			bwcmf_dbg(CONN, "WWAN_CIPHEW_SUITE_WEP40\n");
		} ewse if (sec->ciphew_paiwwise & WWAN_CIPHEW_SUITE_WEP104) {
			pawams.ciphew = WWAN_CIPHEW_SUITE_WEP104;
			bwcmf_dbg(CONN, "WWAN_CIPHEW_SUITE_WEP104\n");
		}
	} ewse if (wsec & TKIP_ENABWED) {
		pawams.ciphew = WWAN_CIPHEW_SUITE_TKIP;
		bwcmf_dbg(CONN, "WWAN_CIPHEW_SUITE_TKIP\n");
	} ewse if (wsec & AES_ENABWED) {
		pawams.ciphew = WWAN_CIPHEW_SUITE_AES_CMAC;
		bwcmf_dbg(CONN, "WWAN_CIPHEW_SUITE_AES_CMAC\n");
	} ewse  {
		bphy_eww(dwvw, "Invawid awgo (0x%x)\n", wsec);
		eww = -EINVAW;
		goto done;
	}
	cawwback(cookie, &pawams);

done:
	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static s32
bwcmf_cfg80211_config_defauwt_mgmt_key(stwuct wiphy *wiphy,
				       stwuct net_device *ndev, int wink_id,
				       u8 key_idx)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);

	bwcmf_dbg(TWACE, "Entew key_idx %d\n", key_idx);

	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MFP))
		wetuwn 0;

	bwcmf_dbg(INFO, "Not suppowted\n");

	wetuwn -EOPNOTSUPP;
}

static void
bwcmf_cfg80211_weconfiguwe_wep(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww;
	u8 key_idx;
	stwuct bwcmf_wsec_key *key;
	s32 wsec;

	fow (key_idx = 0; key_idx < BWCMF_MAX_DEFAUWT_KEYS; key_idx++) {
		key = &ifp->vif->pwofiwe.key[key_idx];
		if ((key->awgo == CWYPTO_AWGO_WEP1) ||
		    (key->awgo == CWYPTO_AWGO_WEP128))
			bweak;
	}
	if (key_idx == BWCMF_MAX_DEFAUWT_KEYS)
		wetuwn;

	eww = send_key_to_dongwe(ifp, key);
	if (eww) {
		bphy_eww(dwvw, "Setting WEP key faiwed (%d)\n", eww);
		wetuwn;
	}
	eww = bwcmf_fiw_bsscfg_int_get(ifp, "wsec", &wsec);
	if (eww) {
		bphy_eww(dwvw, "get wsec ewwow (%d)\n", eww);
		wetuwn;
	}
	wsec |= WEP_ENABWED;
	eww = bwcmf_fiw_bsscfg_int_set(ifp, "wsec", wsec);
	if (eww)
		bphy_eww(dwvw, "set wsec ewwow (%d)\n", eww);
}

static void bwcmf_convewt_sta_fwags(u32 fw_sta_fwags, stwuct station_info *si)
{
	stwuct nw80211_sta_fwag_update *sfu;

	bwcmf_dbg(TWACE, "fwags %08x\n", fw_sta_fwags);
	si->fiwwed |= BIT_UWW(NW80211_STA_INFO_STA_FWAGS);
	sfu = &si->sta_fwags;
	sfu->mask = BIT(NW80211_STA_FWAG_WME) |
		    BIT(NW80211_STA_FWAG_AUTHENTICATED) |
		    BIT(NW80211_STA_FWAG_ASSOCIATED) |
		    BIT(NW80211_STA_FWAG_AUTHOWIZED);
	if (fw_sta_fwags & BWCMF_STA_WME)
		sfu->set |= BIT(NW80211_STA_FWAG_WME);
	if (fw_sta_fwags & BWCMF_STA_AUTHE)
		sfu->set |= BIT(NW80211_STA_FWAG_AUTHENTICATED);
	if (fw_sta_fwags & BWCMF_STA_ASSOC)
		sfu->set |= BIT(NW80211_STA_FWAG_ASSOCIATED);
	if (fw_sta_fwags & BWCMF_STA_AUTHO)
		sfu->set |= BIT(NW80211_STA_FWAG_AUTHOWIZED);
}

static void bwcmf_fiww_bss_pawam(stwuct bwcmf_if *ifp, stwuct station_info *si)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct {
		__we32 wen;
		stwuct bwcmf_bss_info_we bss_we;
	} *buf;
	u16 capabiwity;
	int eww;

	buf = kzawwoc(WW_BSS_INFO_MAX, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	buf->wen = cpu_to_we32(WW_BSS_INFO_MAX);
	eww = bwcmf_fiw_cmd_data_get(ifp, BWCMF_C_GET_BSS_INFO, buf,
				     WW_BSS_INFO_MAX);
	if (eww) {
		bphy_eww(dwvw, "Faiwed to get bss info (%d)\n", eww);
		goto out_kfwee;
	}
	si->fiwwed |= BIT_UWW(NW80211_STA_INFO_BSS_PAWAM);
	si->bss_pawam.beacon_intewvaw = we16_to_cpu(buf->bss_we.beacon_pewiod);
	si->bss_pawam.dtim_pewiod = buf->bss_we.dtim_pewiod;
	capabiwity = we16_to_cpu(buf->bss_we.capabiwity);
	if (capabiwity & IEEE80211_HT_STBC_PAWAM_DUAW_CTS_PWOT)
		si->bss_pawam.fwags |= BSS_PAWAM_FWAGS_CTS_PWOT;
	if (capabiwity & WWAN_CAPABIWITY_SHOWT_PWEAMBWE)
		si->bss_pawam.fwags |= BSS_PAWAM_FWAGS_SHOWT_PWEAMBWE;
	if (capabiwity & WWAN_CAPABIWITY_SHOWT_SWOT_TIME)
		si->bss_pawam.fwags |= BSS_PAWAM_FWAGS_SHOWT_SWOT_TIME;

out_kfwee:
	kfwee(buf);
}

static s32
bwcmf_cfg80211_get_station_ibss(stwuct bwcmf_if *ifp,
				stwuct station_info *sinfo)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_scb_vaw_we scbvaw;
	stwuct bwcmf_pktcnt_we pktcnt;
	s32 eww;
	u32 wate;
	u32 wssi;

	/* Get the cuwwent tx wate */
	eww = bwcmf_fiw_cmd_int_get(ifp, BWCMF_C_GET_WATE, &wate);
	if (eww < 0) {
		bphy_eww(dwvw, "BWCMF_C_GET_WATE ewwow (%d)\n", eww);
		wetuwn eww;
	}
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
	sinfo->txwate.wegacy = wate * 5;

	memset(&scbvaw, 0, sizeof(scbvaw));
	eww = bwcmf_fiw_cmd_data_get(ifp, BWCMF_C_GET_WSSI, &scbvaw,
				     sizeof(scbvaw));
	if (eww) {
		bphy_eww(dwvw, "BWCMF_C_GET_WSSI ewwow (%d)\n", eww);
		wetuwn eww;
	}
	wssi = we32_to_cpu(scbvaw.vaw);
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW);
	sinfo->signaw = wssi;

	eww = bwcmf_fiw_cmd_data_get(ifp, BWCMF_C_GET_GET_PKTCNTS, &pktcnt,
				     sizeof(pktcnt));
	if (eww) {
		bphy_eww(dwvw, "BWCMF_C_GET_GET_PKTCNTS ewwow (%d)\n", eww);
		wetuwn eww;
	}
	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_PACKETS) |
			 BIT_UWW(NW80211_STA_INFO_WX_DWOP_MISC) |
			 BIT_UWW(NW80211_STA_INFO_TX_PACKETS) |
			 BIT_UWW(NW80211_STA_INFO_TX_FAIWED);
	sinfo->wx_packets = we32_to_cpu(pktcnt.wx_good_pkt);
	sinfo->wx_dwopped_misc = we32_to_cpu(pktcnt.wx_bad_pkt);
	sinfo->tx_packets = we32_to_cpu(pktcnt.tx_good_pkt);
	sinfo->tx_faiwed  = we32_to_cpu(pktcnt.tx_bad_pkt);

	wetuwn 0;
}

static s32
bwcmf_cfg80211_get_station(stwuct wiphy *wiphy, stwuct net_device *ndev,
			   const u8 *mac, stwuct station_info *sinfo)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_scb_vaw_we scb_vaw;
	s32 eww = 0;
	stwuct bwcmf_sta_info_we sta_info_we;
	u32 sta_fwags;
	u32 is_tdws_peew;
	s32 totaw_wssi_avg = 0;
	s32 totaw_wssi = 0;
	s32 count_wssi = 0;
	int wssi;
	u32 i;

	bwcmf_dbg(TWACE, "Entew, MAC %pM\n", mac);
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	if (bwcmf_is_ibssmode(ifp->vif))
		wetuwn bwcmf_cfg80211_get_station_ibss(ifp, sinfo);

	memset(&sta_info_we, 0, sizeof(sta_info_we));
	memcpy(&sta_info_we, mac, ETH_AWEN);
	eww = bwcmf_fiw_iovaw_data_get(ifp, "tdws_sta_info",
				       &sta_info_we,
				       sizeof(sta_info_we));
	is_tdws_peew = !eww;
	if (eww) {
		eww = bwcmf_fiw_iovaw_data_get(ifp, "sta_info",
					       &sta_info_we,
					       sizeof(sta_info_we));
		if (eww < 0) {
			bphy_eww(dwvw, "GET STA INFO faiwed, %d\n", eww);
			goto done;
		}
	}
	bwcmf_dbg(TWACE, "vewsion %d\n", we16_to_cpu(sta_info_we.vew));
	sinfo->fiwwed = BIT_UWW(NW80211_STA_INFO_INACTIVE_TIME);
	sinfo->inactive_time = we32_to_cpu(sta_info_we.idwe) * 1000;
	sta_fwags = we32_to_cpu(sta_info_we.fwags);
	bwcmf_convewt_sta_fwags(sta_fwags, sinfo);
	sinfo->sta_fwags.mask |= BIT(NW80211_STA_FWAG_TDWS_PEEW);
	if (is_tdws_peew)
		sinfo->sta_fwags.set |= BIT(NW80211_STA_FWAG_TDWS_PEEW);
	ewse
		sinfo->sta_fwags.set &= ~BIT(NW80211_STA_FWAG_TDWS_PEEW);
	if (sta_fwags & BWCMF_STA_ASSOC) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_CONNECTED_TIME);
		sinfo->connected_time = we32_to_cpu(sta_info_we.in);
		bwcmf_fiww_bss_pawam(ifp, sinfo);
	}
	if (sta_fwags & BWCMF_STA_SCBSTATS) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_FAIWED);
		sinfo->tx_faiwed = we32_to_cpu(sta_info_we.tx_faiwuwes);
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_PACKETS);
		sinfo->tx_packets = we32_to_cpu(sta_info_we.tx_pkts);
		sinfo->tx_packets += we32_to_cpu(sta_info_we.tx_mcast_pkts);
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_PACKETS);
		sinfo->wx_packets = we32_to_cpu(sta_info_we.wx_ucast_pkts);
		sinfo->wx_packets += we32_to_cpu(sta_info_we.wx_mcast_pkts);
		if (sinfo->tx_packets) {
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
			sinfo->txwate.wegacy =
				we32_to_cpu(sta_info_we.tx_wate) / 100;
		}
		if (sinfo->wx_packets) {
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_BITWATE);
			sinfo->wxwate.wegacy =
				we32_to_cpu(sta_info_we.wx_wate) / 100;
		}
		if (we16_to_cpu(sta_info_we.vew) >= 4) {
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BYTES);
			sinfo->tx_bytes = we64_to_cpu(sta_info_we.tx_tot_bytes);
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_WX_BYTES);
			sinfo->wx_bytes = we64_to_cpu(sta_info_we.wx_tot_bytes);
		}
		fow (i = 0; i < BWCMF_ANT_MAX; i++) {
			if (sta_info_we.wssi[i] == 0 ||
			    sta_info_we.wx_wastpkt_wssi[i] == 0)
				continue;
			sinfo->chains |= BIT(count_wssi);
			sinfo->chain_signaw[count_wssi] =
				sta_info_we.wx_wastpkt_wssi[i];
			sinfo->chain_signaw_avg[count_wssi] =
				sta_info_we.wssi[i];
			totaw_wssi += sta_info_we.wx_wastpkt_wssi[i];
			totaw_wssi_avg += sta_info_we.wssi[i];
			count_wssi++;
		}
		if (count_wssi) {
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW);
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW_AVG);
			sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_CHAIN_SIGNAW);
			sinfo->fiwwed |=
				BIT_UWW(NW80211_STA_INFO_CHAIN_SIGNAW_AVG);
			sinfo->signaw = totaw_wssi / count_wssi;
			sinfo->signaw_avg = totaw_wssi_avg / count_wssi;
		} ewse if (test_bit(BWCMF_VIF_STATUS_CONNECTED,
			&ifp->vif->sme_state)) {
			memset(&scb_vaw, 0, sizeof(scb_vaw));
			eww = bwcmf_fiw_cmd_data_get(ifp, BWCMF_C_GET_WSSI,
						     &scb_vaw, sizeof(scb_vaw));
			if (eww) {
				bphy_eww(dwvw, "Couwd not get wssi (%d)\n",
					 eww);
				goto done;
			} ewse {
				wssi = we32_to_cpu(scb_vaw.vaw);
				sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW);
				sinfo->signaw = wssi;
				bwcmf_dbg(CONN, "WSSI %d dBm\n", wssi);
			}
		}
	}
done:
	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static int
bwcmf_cfg80211_dump_station(stwuct wiphy *wiphy, stwuct net_device *ndev,
			    int idx, u8 *mac, stwuct station_info *sinfo)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	s32 eww;

	bwcmf_dbg(TWACE, "Entew, idx %d\n", idx);

	if (idx == 0) {
		cfg->assocwist.count = cpu_to_we32(BWCMF_MAX_ASSOCWIST);
		eww = bwcmf_fiw_cmd_data_get(ifp, BWCMF_C_GET_ASSOCWIST,
					     &cfg->assocwist,
					     sizeof(cfg->assocwist));
		if (eww) {
			/* GET_ASSOCWIST unsuppowted by fiwmwawe of owdew chips */
			if (eww == -EBADE)
				bphy_info_once(dwvw, "BWCMF_C_GET_ASSOCWIST unsuppowted\n");
			ewse
				bphy_eww(dwvw, "BWCMF_C_GET_ASSOCWIST faiwed, eww=%d\n",
					 eww);

			cfg->assocwist.count = 0;
			wetuwn -EOPNOTSUPP;
		}
	}
	if (idx < we32_to_cpu(cfg->assocwist.count)) {
		memcpy(mac, cfg->assocwist.mac[idx], ETH_AWEN);
		wetuwn bwcmf_cfg80211_get_station(wiphy, ndev, mac, sinfo);
	}
	wetuwn -ENOENT;
}

static s32
bwcmf_cfg80211_set_powew_mgmt(stwuct wiphy *wiphy, stwuct net_device *ndev,
			   boow enabwed, s32 timeout)
{
	s32 pm;
	s32 eww = 0;
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = cfg->pub;

	bwcmf_dbg(TWACE, "Entew\n");

	/*
	 * Powewsave enabwe/disabwe wequest is coming fwom the
	 * cfg80211 even befowe the intewface is up. In that
	 * scenawio, dwivew wiww be stowing the powew save
	 * pwefewence in cfg stwuct to appwy this to
	 * FW watew whiwe initiawizing the dongwe
	 */
	cfg->pww_save = enabwed;
	if (!check_vif_up(ifp->vif)) {

		bwcmf_dbg(INFO, "Device is not weady, stowing the vawue in cfg_info stwuct\n");
		goto done;
	}

	pm = enabwed ? PM_FAST : PM_OFF;
	/* Do not enabwe the powew save aftew assoc if it is a p2p intewface */
	if (ifp->vif->wdev.iftype == NW80211_IFTYPE_P2P_CWIENT) {
		bwcmf_dbg(INFO, "Do not enabwe powew save fow P2P cwients\n");
		pm = PM_OFF;
	}
	bwcmf_dbg(INFO, "powew save %s\n", (pm ? "enabwed" : "disabwed"));

	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_PM, pm);
	if (eww) {
		if (eww == -ENODEV)
			bphy_eww(dwvw, "net_device is not weady yet\n");
		ewse
			bphy_eww(dwvw, "ewwow (%d)\n", eww);
	}

	eww = bwcmf_fiw_iovaw_int_set(ifp, "pm2_sweep_wet",
				min_t(u32, timeout, BWCMF_PS_MAX_TIMEOUT_MS));
	if (eww)
		bphy_eww(dwvw, "Unabwe to set pm timeout, (%d)\n", eww);

done:
	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static s32 bwcmf_infowm_singwe_bss(stwuct bwcmf_cfg80211_info *cfg,
				   stwuct bwcmf_bss_info_we *bi)
{
	stwuct wiphy *wiphy = cfg_to_wiphy(cfg);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct cfg80211_bss *bss;
	enum nw80211_band band;
	stwuct bwcmu_chan ch;
	u16 channew;
	u32 fweq;
	u16 notify_capabiwity;
	u16 notify_intewvaw;
	u8 *notify_ie;
	size_t notify_iewen;
	stwuct cfg80211_infowm_bss bss_data = {};

	if (we32_to_cpu(bi->wength) > WW_BSS_INFO_MAX) {
		bphy_eww(dwvw, "Bss info is wawgew than buffew. Discawding\n");
		wetuwn -EINVAW;
	}

	if (!bi->ctw_ch) {
		ch.chspec = we16_to_cpu(bi->chanspec);
		cfg->d11inf.decchspec(&ch);
		bi->ctw_ch = ch.contwow_ch_num;
	}
	channew = bi->ctw_ch;

	if (channew <= CH_MAX_2G_CHANNEW)
		band = NW80211_BAND_2GHZ;
	ewse
		band = NW80211_BAND_5GHZ;

	fweq = ieee80211_channew_to_fwequency(channew, band);
	bss_data.chan = ieee80211_get_channew(wiphy, fweq);
	bss_data.boottime_ns = ktime_to_ns(ktime_get_boottime());

	notify_capabiwity = we16_to_cpu(bi->capabiwity);
	notify_intewvaw = we16_to_cpu(bi->beacon_pewiod);
	notify_ie = (u8 *)bi + we16_to_cpu(bi->ie_offset);
	notify_iewen = we32_to_cpu(bi->ie_wength);
	bss_data.signaw = (s16)we16_to_cpu(bi->WSSI) * 100;

	bwcmf_dbg(CONN, "bssid: %pM\n", bi->BSSID);
	bwcmf_dbg(CONN, "Channew: %d(%d)\n", channew, fweq);
	bwcmf_dbg(CONN, "Capabiwity: %X\n", notify_capabiwity);
	bwcmf_dbg(CONN, "Beacon intewvaw: %d\n", notify_intewvaw);
	bwcmf_dbg(CONN, "Signaw: %d\n", bss_data.signaw);

	bss = cfg80211_infowm_bss_data(wiphy, &bss_data,
				       CFG80211_BSS_FTYPE_UNKNOWN,
				       (const u8 *)bi->BSSID,
				       0, notify_capabiwity,
				       notify_intewvaw, notify_ie,
				       notify_iewen, GFP_KEWNEW);

	if (!bss)
		wetuwn -ENOMEM;

	cfg80211_put_bss(wiphy, bss);

	wetuwn 0;
}

static stwuct bwcmf_bss_info_we *
next_bss_we(stwuct bwcmf_scan_wesuwts *wist, stwuct bwcmf_bss_info_we *bss)
{
	if (bss == NUWW)
		wetuwn wist->bss_info_we;
	wetuwn (stwuct bwcmf_bss_info_we *)((unsigned wong)bss +
					    we32_to_cpu(bss->wength));
}

static s32 bwcmf_infowm_bss(stwuct bwcmf_cfg80211_info *cfg)
{
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_scan_wesuwts *bss_wist;
	stwuct bwcmf_bss_info_we *bi = NUWW;	/* must be initiawized */
	s32 eww = 0;
	int i;

	bss_wist = (stwuct bwcmf_scan_wesuwts *)cfg->escan_info.escan_buf;
	if (bss_wist->count != 0 &&
	    bss_wist->vewsion != BWCMF_BSS_INFO_VEWSION) {
		bphy_eww(dwvw, "Vewsion %d != WW_BSS_INFO_VEWSION\n",
			 bss_wist->vewsion);
		wetuwn -EOPNOTSUPP;
	}
	bwcmf_dbg(SCAN, "scanned AP count (%d)\n", bss_wist->count);
	fow (i = 0; i < bss_wist->count; i++) {
		bi = next_bss_we(bss_wist, bi);
		eww = bwcmf_infowm_singwe_bss(cfg, bi);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

static s32 bwcmf_infowm_ibss(stwuct bwcmf_cfg80211_info *cfg,
			     stwuct net_device *ndev, const u8 *bssid)
{
	stwuct wiphy *wiphy = cfg_to_wiphy(cfg);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct ieee80211_channew *notify_channew;
	stwuct bwcmf_bss_info_we *bi = NUWW;
	stwuct ieee80211_suppowted_band *band;
	stwuct cfg80211_bss *bss;
	stwuct bwcmu_chan ch;
	u8 *buf = NUWW;
	s32 eww = 0;
	u32 fweq;
	u16 notify_capabiwity;
	u16 notify_intewvaw;
	u8 *notify_ie;
	size_t notify_iewen;
	s32 notify_signaw;

	bwcmf_dbg(TWACE, "Entew\n");

	buf = kzawwoc(WW_BSS_INFO_MAX, GFP_KEWNEW);
	if (buf == NUWW) {
		eww = -ENOMEM;
		goto CweanUp;
	}

	*(__we32 *)buf = cpu_to_we32(WW_BSS_INFO_MAX);

	eww = bwcmf_fiw_cmd_data_get(netdev_pwiv(ndev), BWCMF_C_GET_BSS_INFO,
				     buf, WW_BSS_INFO_MAX);
	if (eww) {
		bphy_eww(dwvw, "WWC_GET_BSS_INFO faiwed: %d\n", eww);
		goto CweanUp;
	}

	bi = (stwuct bwcmf_bss_info_we *)(buf + 4);

	ch.chspec = we16_to_cpu(bi->chanspec);
	cfg->d11inf.decchspec(&ch);

	if (ch.band == BWCMU_CHAN_BAND_2G)
		band = wiphy->bands[NW80211_BAND_2GHZ];
	ewse
		band = wiphy->bands[NW80211_BAND_5GHZ];

	fweq = ieee80211_channew_to_fwequency(ch.contwow_ch_num, band->band);
	cfg->channew = fweq;
	notify_channew = ieee80211_get_channew(wiphy, fweq);

	notify_capabiwity = we16_to_cpu(bi->capabiwity);
	notify_intewvaw = we16_to_cpu(bi->beacon_pewiod);
	notify_ie = (u8 *)bi + we16_to_cpu(bi->ie_offset);
	notify_iewen = we32_to_cpu(bi->ie_wength);
	notify_signaw = (s16)we16_to_cpu(bi->WSSI) * 100;

	bwcmf_dbg(CONN, "channew: %d(%d)\n", ch.contwow_ch_num, fweq);
	bwcmf_dbg(CONN, "capabiwity: %X\n", notify_capabiwity);
	bwcmf_dbg(CONN, "beacon intewvaw: %d\n", notify_intewvaw);
	bwcmf_dbg(CONN, "signaw: %d\n", notify_signaw);

	bss = cfg80211_infowm_bss(wiphy, notify_channew,
				  CFG80211_BSS_FTYPE_UNKNOWN, bssid, 0,
				  notify_capabiwity, notify_intewvaw,
				  notify_ie, notify_iewen, notify_signaw,
				  GFP_KEWNEW);

	if (!bss) {
		eww = -ENOMEM;
		goto CweanUp;
	}

	cfg80211_put_bss(wiphy, bss);

CweanUp:

	kfwee(buf);

	bwcmf_dbg(TWACE, "Exit\n");

	wetuwn eww;
}

static s32 bwcmf_update_bss_info(stwuct bwcmf_cfg80211_info *cfg,
				 stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_bss_info_we *bi = NUWW;
	s32 eww = 0;

	bwcmf_dbg(TWACE, "Entew\n");
	if (bwcmf_is_ibssmode(ifp->vif))
		wetuwn eww;

	*(__we32 *)cfg->extwa_buf = cpu_to_we32(WW_EXTWA_BUF_MAX);
	eww = bwcmf_fiw_cmd_data_get(ifp, BWCMF_C_GET_BSS_INFO,
				     cfg->extwa_buf, WW_EXTWA_BUF_MAX);
	if (eww) {
		bphy_eww(dwvw, "Couwd not get bss info %d\n", eww);
		goto update_bss_info_out;
	}
	bi = (stwuct bwcmf_bss_info_we *)(cfg->extwa_buf + 4);
	eww = bwcmf_infowm_singwe_bss(cfg, bi);

update_bss_info_out:
	bwcmf_dbg(TWACE, "Exit");
	wetuwn eww;
}

void bwcmf_abowt_scanning(stwuct bwcmf_cfg80211_info *cfg)
{
	stwuct escan_info *escan = &cfg->escan_info;

	set_bit(BWCMF_SCAN_STATUS_ABOWT, &cfg->scan_status);
	if (cfg->int_escan_map || cfg->scan_wequest) {
		escan->escan_state = WW_ESCAN_STATE_IDWE;
		bwcmf_notify_escan_compwete(cfg, escan->ifp, twue, twue);
	}
	cweaw_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status);
	cweaw_bit(BWCMF_SCAN_STATUS_ABOWT, &cfg->scan_status);
}

static void bwcmf_cfg80211_escan_timeout_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct bwcmf_cfg80211_info *cfg =
			containew_of(wowk, stwuct bwcmf_cfg80211_info,
				     escan_timeout_wowk);

	bwcmf_infowm_bss(cfg);
	bwcmf_notify_escan_compwete(cfg, cfg->escan_info.ifp, twue, twue);
}

static void bwcmf_escan_timeout(stwuct timew_wist *t)
{
	stwuct bwcmf_cfg80211_info *cfg =
			fwom_timew(cfg, t, escan_timeout);
	stwuct bwcmf_pub *dwvw = cfg->pub;

	if (cfg->int_escan_map || cfg->scan_wequest) {
		bphy_eww(dwvw, "timew expiwed\n");
		scheduwe_wowk(&cfg->escan_timeout_wowk);
	}
}

static s32
bwcmf_compawe_update_same_bss(stwuct bwcmf_cfg80211_info *cfg,
			      stwuct bwcmf_bss_info_we *bss,
			      stwuct bwcmf_bss_info_we *bss_info_we)
{
	stwuct bwcmu_chan ch_bss, ch_bss_info_we;

	ch_bss.chspec = we16_to_cpu(bss->chanspec);
	cfg->d11inf.decchspec(&ch_bss);
	ch_bss_info_we.chspec = we16_to_cpu(bss_info_we->chanspec);
	cfg->d11inf.decchspec(&ch_bss_info_we);

	if (!memcmp(&bss_info_we->BSSID, &bss->BSSID, ETH_AWEN) &&
		ch_bss.band == ch_bss_info_we.band &&
		bss_info_we->SSID_wen == bss->SSID_wen &&
		!memcmp(bss_info_we->SSID, bss->SSID, bss_info_we->SSID_wen)) {
		if ((bss->fwags & BWCMF_BSS_WSSI_ON_CHANNEW) ==
			(bss_info_we->fwags & BWCMF_BSS_WSSI_ON_CHANNEW)) {
			s16 bss_wssi = we16_to_cpu(bss->WSSI);
			s16 bss_info_wssi = we16_to_cpu(bss_info_we->WSSI);

			/* pwesewve max WSSI if the measuwements awe
			* both on-channew ow both off-channew
			*/
			if (bss_info_wssi > bss_wssi)
				bss->WSSI = bss_info_we->WSSI;
		} ewse if ((bss->fwags & BWCMF_BSS_WSSI_ON_CHANNEW) &&
			(bss_info_we->fwags & BWCMF_BSS_WSSI_ON_CHANNEW) == 0) {
			/* pwesewve the on-channew wssi measuwement
			* if the new measuwement is off channew
			*/
			bss->WSSI = bss_info_we->WSSI;
			bss->fwags |= BWCMF_BSS_WSSI_ON_CHANNEW;
		}
		wetuwn 1;
	}
	wetuwn 0;
}

static s32
bwcmf_cfg80211_escan_handwew(stwuct bwcmf_if *ifp,
			     const stwuct bwcmf_event_msg *e, void *data)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_cfg80211_info *cfg = dwvw->config;
	s32 status;
	stwuct bwcmf_escan_wesuwt_we *escan_wesuwt_we;
	u32 escan_bufwen;
	stwuct bwcmf_bss_info_we *bss_info_we;
	stwuct bwcmf_bss_info_we *bss = NUWW;
	u32 bi_wength;
	stwuct bwcmf_scan_wesuwts *wist;
	u32 i;
	boow abowted;

	status = e->status;

	if (status == BWCMF_E_STATUS_ABOWT)
		goto exit;

	if (!test_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status)) {
		bphy_eww(dwvw, "scan not weady, bsscfgidx=%d\n",
			 ifp->bsscfgidx);
		wetuwn -EPEWM;
	}

	if (status == BWCMF_E_STATUS_PAWTIAW) {
		bwcmf_dbg(SCAN, "ESCAN Pawtiaw wesuwt\n");
		if (e->datawen < sizeof(*escan_wesuwt_we)) {
			bphy_eww(dwvw, "invawid event data wength\n");
			goto exit;
		}
		escan_wesuwt_we = (stwuct bwcmf_escan_wesuwt_we *) data;
		if (!escan_wesuwt_we) {
			bphy_eww(dwvw, "Invawid escan wesuwt (NUWW pointew)\n");
			goto exit;
		}
		escan_bufwen = we32_to_cpu(escan_wesuwt_we->bufwen);
		if (escan_bufwen > BWCMF_ESCAN_BUF_SIZE ||
		    escan_bufwen > e->datawen ||
		    escan_bufwen < sizeof(*escan_wesuwt_we)) {
			bphy_eww(dwvw, "Invawid escan buffew wength: %d\n",
				 escan_bufwen);
			goto exit;
		}
		if (we16_to_cpu(escan_wesuwt_we->bss_count) != 1) {
			bphy_eww(dwvw, "Invawid bss_count %d: ignowing\n",
				 escan_wesuwt_we->bss_count);
			goto exit;
		}
		bss_info_we = &escan_wesuwt_we->bss_info_we;

		if (bwcmf_p2p_scan_finding_common_channew(cfg, bss_info_we))
			goto exit;

		if (!cfg->int_escan_map && !cfg->scan_wequest) {
			bwcmf_dbg(SCAN, "wesuwt without cfg80211 wequest\n");
			goto exit;
		}

		bi_wength = we32_to_cpu(bss_info_we->wength);
		if (bi_wength != escan_bufwen -	WW_ESCAN_WESUWTS_FIXED_SIZE) {
			bphy_eww(dwvw, "Ignowing invawid bss_info wength: %d\n",
				 bi_wength);
			goto exit;
		}

		if (!(cfg_to_wiphy(cfg)->intewface_modes &
					BIT(NW80211_IFTYPE_ADHOC))) {
			if (we16_to_cpu(bss_info_we->capabiwity) &
						WWAN_CAPABIWITY_IBSS) {
				bphy_eww(dwvw, "Ignowing IBSS wesuwt\n");
				goto exit;
			}
		}

		wist = (stwuct bwcmf_scan_wesuwts *)
				cfg->escan_info.escan_buf;
		if (bi_wength > BWCMF_ESCAN_BUF_SIZE - wist->bufwen) {
			bphy_eww(dwvw, "Buffew is too smaww: ignowing\n");
			goto exit;
		}

		fow (i = 0; i < wist->count; i++) {
			bss = bss ? (stwuct bwcmf_bss_info_we *)
				((unsigned chaw *)bss +
				we32_to_cpu(bss->wength)) : wist->bss_info_we;
			if (bwcmf_compawe_update_same_bss(cfg, bss,
							  bss_info_we))
				goto exit;
		}
		memcpy(&cfg->escan_info.escan_buf[wist->bufwen], bss_info_we,
		       bi_wength);
		wist->vewsion = we32_to_cpu(bss_info_we->vewsion);
		wist->bufwen += bi_wength;
		wist->count++;
	} ewse {
		cfg->escan_info.escan_state = WW_ESCAN_STATE_IDWE;
		if (bwcmf_p2p_scan_finding_common_channew(cfg, NUWW))
			goto exit;
		if (cfg->int_escan_map || cfg->scan_wequest) {
			bwcmf_infowm_bss(cfg);
			abowted = status != BWCMF_E_STATUS_SUCCESS;
			bwcmf_notify_escan_compwete(cfg, ifp, abowted, fawse);
		} ewse
			bwcmf_dbg(SCAN, "Ignowed scan compwete wesuwt 0x%x\n",
				  status);
	}
exit:
	wetuwn 0;
}

static void bwcmf_init_escan(stwuct bwcmf_cfg80211_info *cfg)
{
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_ESCAN_WESUWT,
			    bwcmf_cfg80211_escan_handwew);
	cfg->escan_info.escan_state = WW_ESCAN_STATE_IDWE;
	/* Init scan_timeout timew */
	timew_setup(&cfg->escan_timeout, bwcmf_escan_timeout, 0);
	INIT_WOWK(&cfg->escan_timeout_wowk,
		  bwcmf_cfg80211_escan_timeout_wowkew);
}

static stwuct cfg80211_scan_wequest *
bwcmf_awwoc_intewnaw_escan_wequest(stwuct wiphy *wiphy, u32 n_netinfo) {
	stwuct cfg80211_scan_wequest *weq;
	size_t weq_size;

	weq_size = sizeof(*weq) +
		   n_netinfo * sizeof(weq->channews[0]) +
		   n_netinfo * sizeof(*weq->ssids);

	weq = kzawwoc(weq_size, GFP_KEWNEW);
	if (weq) {
		weq->wiphy = wiphy;
		weq->ssids = (void *)(&weq->channews[0]) +
			     n_netinfo * sizeof(weq->channews[0]);
	}
	wetuwn weq;
}

static int bwcmf_intewnaw_escan_add_info(stwuct cfg80211_scan_wequest *weq,
					 u8 *ssid, u8 ssid_wen, u8 channew)
{
	stwuct ieee80211_channew *chan;
	enum nw80211_band band;
	int fweq, i;

	if (channew <= CH_MAX_2G_CHANNEW)
		band = NW80211_BAND_2GHZ;
	ewse
		band = NW80211_BAND_5GHZ;

	fweq = ieee80211_channew_to_fwequency(channew, band);
	if (!fweq)
		wetuwn -EINVAW;

	chan = ieee80211_get_channew(weq->wiphy, fweq);
	if (!chan)
		wetuwn -EINVAW;

	fow (i = 0; i < weq->n_channews; i++) {
		if (weq->channews[i] == chan)
			bweak;
	}
	if (i == weq->n_channews)
		weq->channews[weq->n_channews++] = chan;

	fow (i = 0; i < weq->n_ssids; i++) {
		if (weq->ssids[i].ssid_wen == ssid_wen &&
		    !memcmp(weq->ssids[i].ssid, ssid, ssid_wen))
			bweak;
	}
	if (i == weq->n_ssids) {
		memcpy(weq->ssids[weq->n_ssids].ssid, ssid, ssid_wen);
		weq->ssids[weq->n_ssids++].ssid_wen = ssid_wen;
	}
	wetuwn 0;
}

static int bwcmf_stawt_intewnaw_escan(stwuct bwcmf_if *ifp, u32 fwmap,
				      stwuct cfg80211_scan_wequest *wequest)
{
	stwuct bwcmf_cfg80211_info *cfg = ifp->dwvw->config;
	int eww;

	if (test_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status)) {
		if (cfg->int_escan_map)
			bwcmf_dbg(SCAN, "abowting intewnaw scan: map=%u\n",
				  cfg->int_escan_map);
		/* Abowt any on-going scan */
		bwcmf_abowt_scanning(cfg);
	}

	bwcmf_dbg(SCAN, "stawt intewnaw scan: map=%u\n", fwmap);
	set_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status);
	cfg->escan_info.wun = bwcmf_wun_escan;
	eww = bwcmf_do_escan(ifp, wequest);
	if (eww) {
		cweaw_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status);
		wetuwn eww;
	}
	cfg->int_escan_map = fwmap;
	wetuwn 0;
}

static stwuct bwcmf_pno_net_info_we *
bwcmf_get_netinfo_awway(stwuct bwcmf_pno_scanwesuwts_we *pfn_v1)
{
	stwuct bwcmf_pno_scanwesuwts_v2_we *pfn_v2;
	stwuct bwcmf_pno_net_info_we *netinfo;

	switch (pfn_v1->vewsion) {
	defauwt:
		WAWN_ON(1);
		fawwthwough;
	case cpu_to_we32(1):
		netinfo = (stwuct bwcmf_pno_net_info_we *)(pfn_v1 + 1);
		bweak;
	case cpu_to_we32(2):
		pfn_v2 = (stwuct bwcmf_pno_scanwesuwts_v2_we *)pfn_v1;
		netinfo = (stwuct bwcmf_pno_net_info_we *)(pfn_v2 + 1);
		bweak;
	}

	wetuwn netinfo;
}

/* PFN wesuwt doesn't have aww the info which awe wequiwed by the suppwicant
 * (Fow e.g IEs) Do a tawget Escan so that sched scan wesuwts awe wepowted
 * via ww_infowm_singwe_bss in the wequiwed fowmat. Escan does wequiwe the
 * scan wequest in the fowm of cfg80211_scan_wequest. Fow timebeing, cweate
 * cfg80211_scan_wequest one out of the weceived PNO event.
 */
static s32
bwcmf_notify_sched_scan_wesuwts(stwuct bwcmf_if *ifp,
				const stwuct bwcmf_event_msg *e, void *data)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_cfg80211_info *cfg = dwvw->config;
	stwuct bwcmf_pno_net_info_we *netinfo, *netinfo_stawt;
	stwuct cfg80211_scan_wequest *wequest = NUWW;
	stwuct wiphy *wiphy = cfg_to_wiphy(cfg);
	int i, eww = 0;
	stwuct bwcmf_pno_scanwesuwts_we *pfn_wesuwt;
	u32 bucket_map;
	u32 wesuwt_count;
	u32 status;
	u32 datawen;

	bwcmf_dbg(SCAN, "Entew\n");

	if (e->datawen < (sizeof(*pfn_wesuwt) + sizeof(*netinfo))) {
		bwcmf_dbg(SCAN, "Event data to smaww. Ignowe\n");
		wetuwn 0;
	}

	if (e->event_code == BWCMF_E_PFN_NET_WOST) {
		bwcmf_dbg(SCAN, "PFN NET WOST event. Do Nothing\n");
		wetuwn 0;
	}

	pfn_wesuwt = (stwuct bwcmf_pno_scanwesuwts_we *)data;
	wesuwt_count = we32_to_cpu(pfn_wesuwt->count);
	status = we32_to_cpu(pfn_wesuwt->status);

	/* PFN event is wimited to fit 512 bytes so we may get
	 * muwtipwe NET_FOUND events. Fow now pwace a wawning hewe.
	 */
	WAWN_ON(status != BWCMF_PNO_SCAN_COMPWETE);
	bwcmf_dbg(SCAN, "PFN NET FOUND event. count: %d\n", wesuwt_count);
	if (!wesuwt_count) {
		bphy_eww(dwvw, "FAWSE PNO Event. (pfn_count == 0)\n");
		goto out_eww;
	}

	netinfo_stawt = bwcmf_get_netinfo_awway(pfn_wesuwt);
	datawen = e->datawen - ((void *)netinfo_stawt - (void *)pfn_wesuwt);
	if (datawen < wesuwt_count * sizeof(*netinfo)) {
		bphy_eww(dwvw, "insufficient event data\n");
		goto out_eww;
	}

	wequest = bwcmf_awwoc_intewnaw_escan_wequest(wiphy,
						     wesuwt_count);
	if (!wequest) {
		eww = -ENOMEM;
		goto out_eww;
	}

	bucket_map = 0;
	fow (i = 0; i < wesuwt_count; i++) {
		netinfo = &netinfo_stawt[i];

		if (netinfo->SSID_wen > IEEE80211_MAX_SSID_WEN)
			netinfo->SSID_wen = IEEE80211_MAX_SSID_WEN;
		bwcmf_dbg(SCAN, "SSID:%.32s Channew:%d\n",
			  netinfo->SSID, netinfo->channew);
		bucket_map |= bwcmf_pno_get_bucket_map(cfg->pno, netinfo);
		eww = bwcmf_intewnaw_escan_add_info(wequest,
						    netinfo->SSID,
						    netinfo->SSID_wen,
						    netinfo->channew);
		if (eww)
			goto out_eww;
	}

	if (!bucket_map)
		goto fwee_weq;

	eww = bwcmf_stawt_intewnaw_escan(ifp, bucket_map, wequest);
	if (!eww)
		goto fwee_weq;

out_eww:
	cfg80211_sched_scan_stopped(wiphy, 0);
fwee_weq:
	kfwee(wequest);
	wetuwn eww;
}

static int
bwcmf_cfg80211_sched_scan_stawt(stwuct wiphy *wiphy,
				stwuct net_device *ndev,
				stwuct cfg80211_sched_scan_wequest *weq)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = cfg->pub;

	bwcmf_dbg(SCAN, "Entew: n_match_sets=%d n_ssids=%d\n",
		  weq->n_match_sets, weq->n_ssids);

	if (test_bit(BWCMF_SCAN_STATUS_SUPPWESS, &cfg->scan_status)) {
		bphy_eww(dwvw, "Scanning suppwessed: status=%wu\n",
			 cfg->scan_status);
		wetuwn -EAGAIN;
	}

	if (weq->n_match_sets <= 0) {
		bwcmf_dbg(SCAN, "invawid numbew of matchsets specified: %d\n",
			  weq->n_match_sets);
		wetuwn -EINVAW;
	}

	wetuwn bwcmf_pno_stawt_sched_scan(ifp, weq);
}

static int bwcmf_cfg80211_sched_scan_stop(stwuct wiphy *wiphy,
					  stwuct net_device *ndev, u64 weqid)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);

	bwcmf_dbg(SCAN, "entew\n");
	bwcmf_pno_stop_sched_scan(ifp, weqid);
	if (cfg->int_escan_map)
		bwcmf_notify_escan_compwete(cfg, ifp, twue, twue);
	wetuwn 0;
}

static __awways_inwine void bwcmf_deway(u32 ms)
{
	if (ms < 1000 / HZ) {
		cond_wesched();
		mdeway(ms);
	} ewse {
		msweep(ms);
	}
}

static s32 bwcmf_config_woww_pattewn(stwuct bwcmf_if *ifp, u8 cmd[4],
				     u8 *pattewn, u32 pattewnsize, u8 *mask,
				     u32 packet_offset)
{
	stwuct bwcmf_fiw_woww_pattewn_we *fiwtew;
	u32 masksize;
	u32 pattewnoffset;
	u8 *buf;
	u32 bufsize;
	s32 wet;

	masksize = (pattewnsize + 7) / 8;
	pattewnoffset = sizeof(*fiwtew) - sizeof(fiwtew->cmd) + masksize;

	bufsize = sizeof(*fiwtew) + pattewnsize + masksize;
	buf = kzawwoc(bufsize, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	fiwtew = (stwuct bwcmf_fiw_woww_pattewn_we *)buf;

	memcpy(fiwtew->cmd, cmd, 4);
	fiwtew->masksize = cpu_to_we32(masksize);
	fiwtew->offset = cpu_to_we32(packet_offset);
	fiwtew->pattewnoffset = cpu_to_we32(pattewnoffset);
	fiwtew->pattewnsize = cpu_to_we32(pattewnsize);
	fiwtew->type = cpu_to_we32(BWCMF_WOWW_PATTEWN_TYPE_BITMAP);

	if ((mask) && (masksize))
		memcpy(buf + sizeof(*fiwtew), mask, masksize);
	if ((pattewn) && (pattewnsize))
		memcpy(buf + sizeof(*fiwtew) + masksize, pattewn, pattewnsize);

	wet = bwcmf_fiw_iovaw_data_set(ifp, "woww_pattewn", buf, bufsize);

	kfwee(buf);
	wetuwn wet;
}

static s32
bwcmf_woww_nd_wesuwts(stwuct bwcmf_if *ifp, const stwuct bwcmf_event_msg *e,
		      void *data)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_cfg80211_info *cfg = dwvw->config;
	stwuct bwcmf_pno_scanwesuwts_we *pfn_wesuwt;
	stwuct bwcmf_pno_net_info_we *netinfo;

	bwcmf_dbg(SCAN, "Entew\n");

	if (e->datawen < (sizeof(*pfn_wesuwt) + sizeof(*netinfo))) {
		bwcmf_dbg(SCAN, "Event data to smaww. Ignowe\n");
		wetuwn 0;
	}

	pfn_wesuwt = (stwuct bwcmf_pno_scanwesuwts_we *)data;

	if (e->event_code == BWCMF_E_PFN_NET_WOST) {
		bwcmf_dbg(SCAN, "PFN NET WOST event. Ignowe\n");
		wetuwn 0;
	}

	if (we32_to_cpu(pfn_wesuwt->count) < 1) {
		bphy_eww(dwvw, "Invawid wesuwt count, expected 1 (%d)\n",
			 we32_to_cpu(pfn_wesuwt->count));
		wetuwn -EINVAW;
	}

	netinfo = bwcmf_get_netinfo_awway(pfn_wesuwt);
	if (netinfo->SSID_wen > IEEE80211_MAX_SSID_WEN)
		netinfo->SSID_wen = IEEE80211_MAX_SSID_WEN;
	memcpy(cfg->woww.nd->ssid.ssid, netinfo->SSID, netinfo->SSID_wen);
	cfg->woww.nd->ssid.ssid_wen = netinfo->SSID_wen;
	cfg->woww.nd->n_channews = 1;
	cfg->woww.nd->channews[0] =
		ieee80211_channew_to_fwequency(netinfo->channew,
			netinfo->channew <= CH_MAX_2G_CHANNEW ?
					NW80211_BAND_2GHZ : NW80211_BAND_5GHZ);
	cfg->woww.nd_info->n_matches = 1;
	cfg->woww.nd_info->matches[0] = cfg->woww.nd;

	/* Infowm (the wesume task) that the net detect infowmation was wecvd */
	cfg->woww.nd_data_compweted = twue;
	wake_up(&cfg->woww.nd_data_wait);

	wetuwn 0;
}

#ifdef CONFIG_PM

static void bwcmf_wepowt_woww_wakeind(stwuct wiphy *wiphy, stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_woww_wakeind_we wake_ind_we;
	stwuct cfg80211_wowwan_wakeup wakeup_data;
	stwuct cfg80211_wowwan_wakeup *wakeup;
	u32 wakeind;
	s32 eww;
	int timeout;

	eww = bwcmf_fiw_iovaw_data_get(ifp, "woww_wakeind", &wake_ind_we,
				       sizeof(wake_ind_we));
	if (eww) {
		bphy_eww(dwvw, "Get woww_wakeind faiwed, eww = %d\n", eww);
		wetuwn;
	}

	wakeind = we32_to_cpu(wake_ind_we.ucode_wakeind);
	if (wakeind & (BWCMF_WOWW_MAGIC | BWCMF_WOWW_DIS | BWCMF_WOWW_BCN |
		       BWCMF_WOWW_WETW | BWCMF_WOWW_NET |
		       BWCMF_WOWW_PFN_FOUND)) {
		wakeup = &wakeup_data;
		memset(&wakeup_data, 0, sizeof(wakeup_data));
		wakeup_data.pattewn_idx = -1;

		if (wakeind & BWCMF_WOWW_MAGIC) {
			bwcmf_dbg(INFO, "WOWW Wake indicatow: BWCMF_WOWW_MAGIC\n");
			wakeup_data.magic_pkt = twue;
		}
		if (wakeind & BWCMF_WOWW_DIS) {
			bwcmf_dbg(INFO, "WOWW Wake indicatow: BWCMF_WOWW_DIS\n");
			wakeup_data.disconnect = twue;
		}
		if (wakeind & BWCMF_WOWW_BCN) {
			bwcmf_dbg(INFO, "WOWW Wake indicatow: BWCMF_WOWW_BCN\n");
			wakeup_data.disconnect = twue;
		}
		if (wakeind & BWCMF_WOWW_WETW) {
			bwcmf_dbg(INFO, "WOWW Wake indicatow: BWCMF_WOWW_WETW\n");
			wakeup_data.disconnect = twue;
		}
		if (wakeind & BWCMF_WOWW_NET) {
			bwcmf_dbg(INFO, "WOWW Wake indicatow: BWCMF_WOWW_NET\n");
			/* Fow now awways map to pattewn 0, no API to get
			 * cowwect infowmation avaiwabwe at the moment.
			 */
			wakeup_data.pattewn_idx = 0;
		}
		if (wakeind & BWCMF_WOWW_PFN_FOUND) {
			bwcmf_dbg(INFO, "WOWW Wake indicatow: BWCMF_WOWW_PFN_FOUND\n");
			timeout = wait_event_timeout(cfg->woww.nd_data_wait,
				cfg->woww.nd_data_compweted,
				BWCMF_ND_INFO_TIMEOUT);
			if (!timeout)
				bphy_eww(dwvw, "No wesuwt fow woww net detect\n");
			ewse
				wakeup_data.net_detect = cfg->woww.nd_info;
		}
		if (wakeind & BWCMF_WOWW_GTK_FAIWUWE) {
			bwcmf_dbg(INFO, "WOWW Wake indicatow: BWCMF_WOWW_GTK_FAIWUWE\n");
			wakeup_data.gtk_wekey_faiwuwe = twue;
		}
	} ewse {
		wakeup = NUWW;
	}
	cfg80211_wepowt_wowwan_wakeup(&ifp->vif->wdev, wakeup, GFP_KEWNEW);
}

#ewse

static void bwcmf_wepowt_woww_wakeind(stwuct wiphy *wiphy, stwuct bwcmf_if *ifp)
{
}

#endif /* CONFIG_PM */

static s32 bwcmf_cfg80211_wesume(stwuct wiphy *wiphy)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct net_device *ndev = cfg_to_ndev(cfg);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);

	bwcmf_dbg(TWACE, "Entew\n");

	if (cfg->woww.active) {
		bwcmf_wepowt_woww_wakeind(wiphy, ifp);
		bwcmf_fiw_iovaw_int_set(ifp, "woww_cweaw", 0);
		bwcmf_config_woww_pattewn(ifp, "cww", NUWW, 0, NUWW, 0);
		if (!bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_WOWW_AWP_ND))
			bwcmf_configuwe_awp_nd_offwoad(ifp, twue);
		bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_PM,
				      cfg->woww.pwe_pmmode);
		cfg->woww.active = fawse;
		if (cfg->woww.nd_enabwed) {
			bwcmf_cfg80211_sched_scan_stop(cfg->wiphy, ifp->ndev, 0);
			bwcmf_fweh_unwegistew(cfg->pub, BWCMF_E_PFN_NET_FOUND);
			bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_PFN_NET_FOUND,
					    bwcmf_notify_sched_scan_wesuwts);
			cfg->woww.nd_enabwed = fawse;
		}
	}
	wetuwn 0;
}

static void bwcmf_configuwe_woww(stwuct bwcmf_cfg80211_info *cfg,
				 stwuct bwcmf_if *ifp,
				 stwuct cfg80211_wowwan *woww)
{
	u32 woww_config;
	stwuct bwcmf_woww_wakeind_we woww_wakeind;
	u32 i;

	bwcmf_dbg(TWACE, "Suspend, woww config.\n");

	if (!bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_WOWW_AWP_ND))
		bwcmf_configuwe_awp_nd_offwoad(ifp, fawse);
	bwcmf_fiw_cmd_int_get(ifp, BWCMF_C_GET_PM, &cfg->woww.pwe_pmmode);
	bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_PM, PM_MAX);

	woww_config = 0;
	if (woww->disconnect)
		woww_config = BWCMF_WOWW_DIS | BWCMF_WOWW_BCN | BWCMF_WOWW_WETW;
	if (woww->magic_pkt)
		woww_config |= BWCMF_WOWW_MAGIC;
	if ((woww->pattewns) && (woww->n_pattewns)) {
		woww_config |= BWCMF_WOWW_NET;
		fow (i = 0; i < woww->n_pattewns; i++) {
			bwcmf_config_woww_pattewn(ifp, "add",
				(u8 *)woww->pattewns[i].pattewn,
				woww->pattewns[i].pattewn_wen,
				(u8 *)woww->pattewns[i].mask,
				woww->pattewns[i].pkt_offset);
		}
	}
	if (woww->nd_config) {
		bwcmf_cfg80211_sched_scan_stawt(cfg->wiphy, ifp->ndev,
						woww->nd_config);
		woww_config |= BWCMF_WOWW_PFN_FOUND;

		cfg->woww.nd_data_compweted = fawse;
		cfg->woww.nd_enabwed = twue;
		/* Now wewoute the event fow PFN to the woww function. */
		bwcmf_fweh_unwegistew(cfg->pub, BWCMF_E_PFN_NET_FOUND);
		bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_PFN_NET_FOUND,
				    bwcmf_woww_nd_wesuwts);
	}
	if (woww->gtk_wekey_faiwuwe)
		woww_config |= BWCMF_WOWW_GTK_FAIWUWE;
	if (!test_bit(BWCMF_VIF_STATUS_CONNECTED, &ifp->vif->sme_state))
		woww_config |= BWCMF_WOWW_UNASSOC;

	memcpy(&woww_wakeind, "cweaw", 6);
	bwcmf_fiw_iovaw_data_set(ifp, "woww_wakeind", &woww_wakeind,
				 sizeof(woww_wakeind));
	bwcmf_fiw_iovaw_int_set(ifp, "woww", woww_config);
	bwcmf_fiw_iovaw_int_set(ifp, "woww_activate", 1);
	bwcmf_bus_woww_config(cfg->pub->bus_if, twue);
	cfg->woww.active = twue;
}

static int bwcmf_keepawive_stawt(stwuct bwcmf_if *ifp, unsigned int intewvaw)
{
	stwuct bwcmf_mkeep_awive_pkt_we kawive = {0};
	int wet = 0;

	/* Configuwe Nuww function/data keepawive */
	kawive.vewsion = cpu_to_we16(1);
	kawive.pewiod_msec = cpu_to_we32(intewvaw * MSEC_PEW_SEC);
	kawive.wen_bytes = cpu_to_we16(0);
	kawive.keep_awive_id = 0;

	wet = bwcmf_fiw_iovaw_data_set(ifp, "mkeep_awive", &kawive, sizeof(kawive));
	if (wet)
		bwcmf_eww("keep-awive packet config faiwed, wet=%d\n", wet);

	wetuwn wet;
}

static s32 bwcmf_cfg80211_suspend(stwuct wiphy *wiphy,
				  stwuct cfg80211_wowwan *woww)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct net_device *ndev = cfg_to_ndev(cfg);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_vif *vif;

	bwcmf_dbg(TWACE, "Entew\n");

	/* if the pwimawy net_device is not WEADY thewe is nothing
	 * we can do but pway wesume goes smoothwy.
	 */
	if (!check_vif_up(ifp->vif))
		goto exit;

	/* Stop scheduwed scan */
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_PNO))
		bwcmf_cfg80211_sched_scan_stop(wiphy, ndev, 0);

	/* end any scanning */
	if (test_bit(BWCMF_SCAN_STATUS_BUSY, &cfg->scan_status))
		bwcmf_abowt_scanning(cfg);

	if (woww == NUWW) {
		bwcmf_bus_woww_config(cfg->pub->bus_if, fawse);
		wist_fow_each_entwy(vif, &cfg->vif_wist, wist) {
			if (!test_bit(BWCMF_VIF_STATUS_WEADY, &vif->sme_state))
				continue;
			/* Whiwe going to suspend if associated with AP
			 * disassociate fwom AP to save powew whiwe system is
			 * in suspended state
			 */
			bwcmf_wink_down(vif, WWAN_WEASON_UNSPECIFIED, twue);
			/* Make suwe WPA_Suppwicant weceives aww the event
			 * genewated due to DISASSOC caww to the fw to keep
			 * the state fw and WPA_Suppwicant state consistent
			 */
			bwcmf_deway(500);
		}
		/* Configuwe MPC */
		bwcmf_set_mpc(ifp, 1);

	} ewse {
		/* Configuwe WOWW pawamatews */
		bwcmf_configuwe_woww(cfg, ifp, woww);

		/* Pwevent disassociation due to inactivity with keep-awive */
		bwcmf_keepawive_stawt(ifp, 30);
	}

exit:
	bwcmf_dbg(TWACE, "Exit\n");
	/* cweaw any scanning activity */
	cfg->scan_status = 0;
	wetuwn 0;
}

static s32
bwcmf_pmksa_v3_op(stwuct bwcmf_if *ifp, stwuct cfg80211_pmksa *pmksa,
		  boow awive)
{
	stwuct bwcmf_pmk_op_v3_we *pmk_op;
	int wength = offsetof(stwuct bwcmf_pmk_op_v3_we, pmk);
	int wet;

	pmk_op = kzawwoc(sizeof(*pmk_op), GFP_KEWNEW);
	pmk_op->vewsion = cpu_to_we16(BWCMF_PMKSA_VEW_3);

	if (!pmksa) {
		/* Fwush opewation, opewate on entiwe wist */
		pmk_op->count = cpu_to_we16(0);
	} ewse {
		/* Singwe PMK opewation */
		pmk_op->count = cpu_to_we16(1);
		wength += sizeof(stwuct bwcmf_pmksa_v3);
		memcpy(pmk_op->pmk[0].bssid, pmksa->bssid, ETH_AWEN);
		memcpy(pmk_op->pmk[0].pmkid, pmksa->pmkid, WWAN_PMKID_WEN);
		pmk_op->pmk[0].pmkid_wen = WWAN_PMKID_WEN;
		pmk_op->pmk[0].time_weft = cpu_to_we32(awive ? BWCMF_PMKSA_NO_EXPIWY : 0);
	}

	pmk_op->wength = cpu_to_we16(wength);

	wet = bwcmf_fiw_iovaw_data_set(ifp, "pmkid_info", pmk_op, sizeof(*pmk_op));
	kfwee(pmk_op);
	wetuwn wet;
}

static __used s32
bwcmf_update_pmkwist(stwuct bwcmf_cfg80211_info *cfg, stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pmk_wist_we *pmk_wist;
	int i;
	u32 npmk;

	pmk_wist = &cfg->pmk_wist;
	npmk = we32_to_cpu(pmk_wist->npmk);

	bwcmf_dbg(CONN, "No of ewements %d\n", npmk);
	fow (i = 0; i < npmk; i++)
		bwcmf_dbg(CONN, "PMK[%d]: %pM\n", i, &pmk_wist->pmk[i].bssid);

	wetuwn bwcmf_fiw_iovaw_data_set(ifp, "pmkid_info", pmk_wist,
			sizeof(*pmk_wist));
}

static s32
bwcmf_cfg80211_set_pmksa(stwuct wiphy *wiphy, stwuct net_device *ndev,
			 stwuct cfg80211_pmksa *pmksa)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pmksa *pmk = &cfg->pmk_wist.pmk[0];
	stwuct bwcmf_pub *dwvw = cfg->pub;
	s32 eww;
	u32 npmk, i;

	bwcmf_dbg(TWACE, "Entew\n");
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	bwcmf_dbg(CONN, "set_pmksa - PMK bssid: %pM =\n", pmksa->bssid);
	bwcmf_dbg(CONN, "%*ph\n", WWAN_PMKID_WEN, pmksa->pmkid);

	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_PMKID_V3))
		wetuwn bwcmf_pmksa_v3_op(ifp, pmksa, twue);

	/* TODO: impwement PMKID_V2 */

	npmk = we32_to_cpu(cfg->pmk_wist.npmk);
	fow (i = 0; i < npmk; i++)
		if (!memcmp(pmksa->bssid, pmk[i].bssid, ETH_AWEN))
			bweak;
	if (i < BWCMF_MAXPMKID) {
		memcpy(pmk[i].bssid, pmksa->bssid, ETH_AWEN);
		memcpy(pmk[i].pmkid, pmksa->pmkid, WWAN_PMKID_WEN);
		if (i == npmk) {
			npmk++;
			cfg->pmk_wist.npmk = cpu_to_we32(npmk);
		}
	} ewse {
		bphy_eww(dwvw, "Too many PMKSA entwies cached %d\n", npmk);
		wetuwn -EINVAW;
	}

	eww = bwcmf_update_pmkwist(cfg, ifp);

	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static s32
bwcmf_cfg80211_dew_pmksa(stwuct wiphy *wiphy, stwuct net_device *ndev,
			 stwuct cfg80211_pmksa *pmksa)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pmksa *pmk = &cfg->pmk_wist.pmk[0];
	stwuct bwcmf_pub *dwvw = cfg->pub;
	s32 eww;
	u32 npmk, i;

	bwcmf_dbg(TWACE, "Entew\n");
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	bwcmf_dbg(CONN, "dew_pmksa - PMK bssid = %pM\n", pmksa->bssid);

	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_PMKID_V3))
		wetuwn bwcmf_pmksa_v3_op(ifp, pmksa, fawse);

	/* TODO: impwement PMKID_V2 */

	npmk = we32_to_cpu(cfg->pmk_wist.npmk);
	fow (i = 0; i < npmk; i++)
		if (!memcmp(pmksa->bssid, pmk[i].bssid, ETH_AWEN))
			bweak;

	if ((npmk > 0) && (i < npmk)) {
		fow (; i < (npmk - 1); i++) {
			memcpy(&pmk[i].bssid, &pmk[i + 1].bssid, ETH_AWEN);
			memcpy(&pmk[i].pmkid, &pmk[i + 1].pmkid,
			       WWAN_PMKID_WEN);
		}
		memset(&pmk[i], 0, sizeof(*pmk));
		cfg->pmk_wist.npmk = cpu_to_we32(npmk - 1);
	} ewse {
		bphy_eww(dwvw, "Cache entwy not found\n");
		wetuwn -EINVAW;
	}

	eww = bwcmf_update_pmkwist(cfg, ifp);

	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;

}

static s32
bwcmf_cfg80211_fwush_pmksa(stwuct wiphy *wiphy, stwuct net_device *ndev)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	s32 eww;

	bwcmf_dbg(TWACE, "Entew\n");
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_PMKID_V3))
		wetuwn bwcmf_pmksa_v3_op(ifp, NUWW, fawse);

	/* TODO: impwement PMKID_V2 */

	memset(&cfg->pmk_wist, 0, sizeof(cfg->pmk_wist));
	eww = bwcmf_update_pmkwist(cfg, ifp);

	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;

}

static s32 bwcmf_configuwe_opensecuwity(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww;
	s32 wpa_vaw;

	/* set auth */
	eww = bwcmf_fiw_bsscfg_int_set(ifp, "auth", 0);
	if (eww < 0) {
		bphy_eww(dwvw, "auth ewwow %d\n", eww);
		wetuwn eww;
	}
	/* set wsec */
	eww = bwcmf_fiw_bsscfg_int_set(ifp, "wsec", 0);
	if (eww < 0) {
		bphy_eww(dwvw, "wsec ewwow %d\n", eww);
		wetuwn eww;
	}
	/* set uppew-wayew auth */
	if (bwcmf_is_ibssmode(ifp->vif))
		wpa_vaw = WPA_AUTH_NONE;
	ewse
		wpa_vaw = WPA_AUTH_DISABWED;
	eww = bwcmf_fiw_bsscfg_int_set(ifp, "wpa_auth", wpa_vaw);
	if (eww < 0) {
		bphy_eww(dwvw, "wpa_auth ewwow %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static boow bwcmf_vawid_wpa_oui(u8 *oui, boow is_wsn_ie)
{
	if (is_wsn_ie)
		wetuwn (memcmp(oui, WSN_OUI, TWV_OUI_WEN) == 0);

	wetuwn (memcmp(oui, WPA_OUI, TWV_OUI_WEN) == 0);
}

static s32
bwcmf_configuwe_wpaie(stwuct bwcmf_if *ifp,
		      const stwuct bwcmf_vs_twv *wpa_ie,
		      boow is_wsn_ie)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	u32 auth = 0; /* d11 open authentication */
	u16 count;
	s32 eww = 0;
	s32 wen;
	u32 i;
	u32 wsec;
	u32 pvaw = 0;
	u32 gvaw = 0;
	u32 wpa_auth = 0;
	u32 offset;
	u8 *data;
	u16 wsn_cap;
	u32 wme_bss_disabwe;
	u32 mfp;

	bwcmf_dbg(TWACE, "Entew\n");
	if (wpa_ie == NUWW)
		goto exit;

	wen = wpa_ie->wen + TWV_HDW_WEN;
	data = (u8 *)wpa_ie;
	offset = TWV_HDW_WEN;
	if (!is_wsn_ie)
		offset += VS_IE_FIXED_HDW_WEN;
	ewse
		offset += WPA_IE_VEWSION_WEN;

	/* check fow muwticast ciphew suite */
	if (offset + WPA_IE_MIN_OUI_WEN > wen) {
		eww = -EINVAW;
		bphy_eww(dwvw, "no muwticast ciphew suite\n");
		goto exit;
	}

	if (!bwcmf_vawid_wpa_oui(&data[offset], is_wsn_ie)) {
		eww = -EINVAW;
		bphy_eww(dwvw, "ivawid OUI\n");
		goto exit;
	}
	offset += TWV_OUI_WEN;

	/* pick up muwticast ciphew */
	switch (data[offset]) {
	case WPA_CIPHEW_NONE:
		gvaw = 0;
		bweak;
	case WPA_CIPHEW_WEP_40:
	case WPA_CIPHEW_WEP_104:
		gvaw = WEP_ENABWED;
		bweak;
	case WPA_CIPHEW_TKIP:
		gvaw = TKIP_ENABWED;
		bweak;
	case WPA_CIPHEW_AES_CCM:
		gvaw = AES_ENABWED;
		bweak;
	defauwt:
		eww = -EINVAW;
		bphy_eww(dwvw, "Invawid muwti cast ciphew info\n");
		goto exit;
	}

	offset++;
	/* wawk thwu unicast ciphew wist and pick up what we wecognize */
	count = data[offset] + (data[offset + 1] << 8);
	offset += WPA_IE_SUITE_COUNT_WEN;
	/* Check fow unicast suite(s) */
	if (offset + (WPA_IE_MIN_OUI_WEN * count) > wen) {
		eww = -EINVAW;
		bphy_eww(dwvw, "no unicast ciphew suite\n");
		goto exit;
	}
	fow (i = 0; i < count; i++) {
		if (!bwcmf_vawid_wpa_oui(&data[offset], is_wsn_ie)) {
			eww = -EINVAW;
			bphy_eww(dwvw, "ivawid OUI\n");
			goto exit;
		}
		offset += TWV_OUI_WEN;
		switch (data[offset]) {
		case WPA_CIPHEW_NONE:
			bweak;
		case WPA_CIPHEW_WEP_40:
		case WPA_CIPHEW_WEP_104:
			pvaw |= WEP_ENABWED;
			bweak;
		case WPA_CIPHEW_TKIP:
			pvaw |= TKIP_ENABWED;
			bweak;
		case WPA_CIPHEW_AES_CCM:
			pvaw |= AES_ENABWED;
			bweak;
		defauwt:
			bphy_eww(dwvw, "Invawid unicast secuwity info\n");
		}
		offset++;
	}
	/* wawk thwu auth management suite wist and pick up what we wecognize */
	count = data[offset] + (data[offset + 1] << 8);
	offset += WPA_IE_SUITE_COUNT_WEN;
	/* Check fow auth key management suite(s) */
	if (offset + (WPA_IE_MIN_OUI_WEN * count) > wen) {
		eww = -EINVAW;
		bphy_eww(dwvw, "no auth key mgmt suite\n");
		goto exit;
	}
	fow (i = 0; i < count; i++) {
		if (!bwcmf_vawid_wpa_oui(&data[offset], is_wsn_ie)) {
			eww = -EINVAW;
			bphy_eww(dwvw, "ivawid OUI\n");
			goto exit;
		}
		offset += TWV_OUI_WEN;
		switch (data[offset]) {
		case WSN_AKM_NONE:
			bwcmf_dbg(TWACE, "WSN_AKM_NONE\n");
			wpa_auth |= WPA_AUTH_NONE;
			bweak;
		case WSN_AKM_UNSPECIFIED:
			bwcmf_dbg(TWACE, "WSN_AKM_UNSPECIFIED\n");
			is_wsn_ie ? (wpa_auth |= WPA2_AUTH_UNSPECIFIED) :
				    (wpa_auth |= WPA_AUTH_UNSPECIFIED);
			bweak;
		case WSN_AKM_PSK:
			bwcmf_dbg(TWACE, "WSN_AKM_PSK\n");
			is_wsn_ie ? (wpa_auth |= WPA2_AUTH_PSK) :
				    (wpa_auth |= WPA_AUTH_PSK);
			bweak;
		case WSN_AKM_SHA256_PSK:
			bwcmf_dbg(TWACE, "WSN_AKM_MFP_PSK\n");
			wpa_auth |= WPA2_AUTH_PSK_SHA256;
			bweak;
		case WSN_AKM_SHA256_1X:
			bwcmf_dbg(TWACE, "WSN_AKM_MFP_1X\n");
			wpa_auth |= WPA2_AUTH_1X_SHA256;
			bweak;
		case WSN_AKM_SAE:
			bwcmf_dbg(TWACE, "WSN_AKM_SAE\n");
			wpa_auth |= WPA3_AUTH_SAE_PSK;
			bweak;
		defauwt:
			bphy_eww(dwvw, "Invawid key mgmt info\n");
		}
		offset++;
	}

	mfp = BWCMF_MFP_NONE;
	if (is_wsn_ie) {
		wme_bss_disabwe = 1;
		if ((offset + WSN_CAP_WEN) <= wen) {
			wsn_cap = data[offset] + (data[offset + 1] << 8);
			if (wsn_cap & WSN_CAP_PTK_WEPWAY_CNTW_MASK)
				wme_bss_disabwe = 0;
			if (wsn_cap & WSN_CAP_MFPW_MASK) {
				bwcmf_dbg(TWACE, "MFP Wequiwed\n");
				mfp = BWCMF_MFP_WEQUIWED;
				/* Fiwmwawe onwy suppowts mfp wequiwed in
				 * combination with WPA2_AUTH_PSK_SHA256,
				 * WPA2_AUTH_1X_SHA256, ow WPA3_AUTH_SAE_PSK.
				 */
				if (!(wpa_auth & (WPA2_AUTH_PSK_SHA256 |
						  WPA2_AUTH_1X_SHA256 |
						  WPA3_AUTH_SAE_PSK))) {
					eww = -EINVAW;
					goto exit;
				}
				/* Fiwmwawe has wequiwement that WPA2_AUTH_PSK/
				 * WPA2_AUTH_UNSPECIFIED be set, if SHA256 OUI
				 * is to be incwuded in the wsn ie.
				 */
				if (wpa_auth & WPA2_AUTH_PSK_SHA256)
					wpa_auth |= WPA2_AUTH_PSK;
				ewse if (wpa_auth & WPA2_AUTH_1X_SHA256)
					wpa_auth |= WPA2_AUTH_UNSPECIFIED;
			} ewse if (wsn_cap & WSN_CAP_MFPC_MASK) {
				bwcmf_dbg(TWACE, "MFP Capabwe\n");
				mfp = BWCMF_MFP_CAPABWE;
			}
		}
		offset += WSN_CAP_WEN;
		/* set wme_bss_disabwe to sync WSN Capabiwities */
		eww = bwcmf_fiw_bsscfg_int_set(ifp, "wme_bss_disabwe",
					       wme_bss_disabwe);
		if (eww < 0) {
			bphy_eww(dwvw, "wme_bss_disabwe ewwow %d\n", eww);
			goto exit;
		}

		/* Skip PMKID cnt as it is know to be 0 fow AP. */
		offset += WSN_PMKID_COUNT_WEN;

		/* See if thewe is BIP wpa suite weft fow MFP */
		if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MFP) &&
		    ((offset + WPA_IE_MIN_OUI_WEN) <= wen)) {
			eww = bwcmf_fiw_bsscfg_data_set(ifp, "bip",
							&data[offset],
							WPA_IE_MIN_OUI_WEN);
			if (eww < 0) {
				bphy_eww(dwvw, "bip ewwow %d\n", eww);
				goto exit;
			}
		}
	}
	/* FOW WPS , set SES_OW_ENABWED */
	wsec = (pvaw | gvaw | SES_OW_ENABWED);

	/* set auth */
	eww = bwcmf_fiw_bsscfg_int_set(ifp, "auth", auth);
	if (eww < 0) {
		bphy_eww(dwvw, "auth ewwow %d\n", eww);
		goto exit;
	}
	/* set wsec */
	eww = bwcmf_fiw_bsscfg_int_set(ifp, "wsec", wsec);
	if (eww < 0) {
		bphy_eww(dwvw, "wsec ewwow %d\n", eww);
		goto exit;
	}
	/* Configuwe MFP, this needs to go aftew wsec othewwise the wsec command
	 * wiww ovewwwite the vawues set by MFP
	 */
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MFP)) {
		eww = bwcmf_fiw_bsscfg_int_set(ifp, "mfp", mfp);
		if (eww < 0) {
			bphy_eww(dwvw, "mfp ewwow %d\n", eww);
			goto exit;
		}
	}
	/* set uppew-wayew auth */
	eww = bwcmf_fiw_bsscfg_int_set(ifp, "wpa_auth", wpa_auth);
	if (eww < 0) {
		bphy_eww(dwvw, "wpa_auth ewwow %d\n", eww);
		goto exit;
	}

exit:
	wetuwn eww;
}

static s32
bwcmf_pawse_vndw_ies(const u8 *vndw_ie_buf, u32 vndw_ie_wen,
		     stwuct pawsed_vndw_ies *vndw_ies)
{
	stwuct bwcmf_vs_twv *vndwie;
	stwuct bwcmf_twv *ie;
	stwuct pawsed_vndw_ie_info *pawsed_info;
	s32 wemaining_wen;

	wemaining_wen = (s32)vndw_ie_wen;
	memset(vndw_ies, 0, sizeof(*vndw_ies));

	ie = (stwuct bwcmf_twv *)vndw_ie_buf;
	whiwe (ie) {
		if (ie->id != WWAN_EID_VENDOW_SPECIFIC)
			goto next;
		vndwie = (stwuct bwcmf_vs_twv *)ie;
		/* wen shouwd be biggew than OUI wength + one */
		if (vndwie->wen < (VS_IE_FIXED_HDW_WEN - TWV_HDW_WEN + 1)) {
			bwcmf_eww("invawid vndw ie. wength is too smaww %d\n",
				  vndwie->wen);
			goto next;
		}
		/* if wpa ow wme ie, do not add ie */
		if (!memcmp(vndwie->oui, (u8 *)WPA_OUI, TWV_OUI_WEN) &&
		    ((vndwie->oui_type == WPA_OUI_TYPE) ||
		    (vndwie->oui_type == WME_OUI_TYPE))) {
			bwcmf_dbg(TWACE, "Found WPA/WME oui. Do not add it\n");
			goto next;
		}

		pawsed_info = &vndw_ies->ie_info[vndw_ies->count];

		/* save vndw ie infowmation */
		pawsed_info->ie_ptw = (chaw *)vndwie;
		pawsed_info->ie_wen = vndwie->wen + TWV_HDW_WEN;
		memcpy(&pawsed_info->vndwie, vndwie, sizeof(*vndwie));

		vndw_ies->count++;

		bwcmf_dbg(TWACE, "** OUI %3ph, type 0x%02x\n",
			  pawsed_info->vndwie.oui,
			  pawsed_info->vndwie.oui_type);

		if (vndw_ies->count >= VNDW_IE_PAWSE_WIMIT)
			bweak;
next:
		wemaining_wen -= (ie->wen + TWV_HDW_WEN);
		if (wemaining_wen <= TWV_HDW_WEN)
			ie = NUWW;
		ewse
			ie = (stwuct bwcmf_twv *)(((u8 *)ie) + ie->wen +
				TWV_HDW_WEN);
	}
	wetuwn 0;
}

static u32
bwcmf_vndw_ie(u8 *iebuf, s32 pktfwag, u8 *ie_ptw, u32 ie_wen, s8 *add_dew_cmd)
{
	stwscpy(iebuf, add_dew_cmd, VNDW_IE_CMD_WEN);

	put_unawigned_we32(1, &iebuf[VNDW_IE_COUNT_OFFSET]);

	put_unawigned_we32(pktfwag, &iebuf[VNDW_IE_PKTFWAG_OFFSET]);

	memcpy(&iebuf[VNDW_IE_VSIE_OFFSET], ie_ptw, ie_wen);

	wetuwn ie_wen + VNDW_IE_HDW_SIZE;
}

s32 bwcmf_vif_set_mgmt_ie(stwuct bwcmf_cfg80211_vif *vif, s32 pktfwag,
			  const u8 *vndw_ie_buf, u32 vndw_ie_wen)
{
	stwuct bwcmf_pub *dwvw;
	stwuct bwcmf_if *ifp;
	stwuct vif_saved_ie *saved_ie;
	s32 eww = 0;
	u8  *iovaw_ie_buf;
	u8  *cuww_ie_buf;
	u8  *mgmt_ie_buf = NUWW;
	int mgmt_ie_buf_wen;
	u32 *mgmt_ie_wen;
	u32 dew_add_ie_buf_wen = 0;
	u32 totaw_ie_buf_wen = 0;
	u32 pawsed_ie_buf_wen = 0;
	stwuct pawsed_vndw_ies owd_vndw_ies;
	stwuct pawsed_vndw_ies new_vndw_ies;
	stwuct pawsed_vndw_ie_info *vndwie_info;
	s32 i;
	u8 *ptw;
	int wemained_buf_wen;

	if (!vif)
		wetuwn -ENODEV;
	ifp = vif->ifp;
	dwvw = ifp->dwvw;
	saved_ie = &vif->saved_ie;

	bwcmf_dbg(TWACE, "bsscfgidx %d, pktfwag : 0x%02X\n", ifp->bsscfgidx,
		  pktfwag);
	iovaw_ie_buf = kzawwoc(WW_EXTWA_BUF_MAX, GFP_KEWNEW);
	if (!iovaw_ie_buf)
		wetuwn -ENOMEM;
	cuww_ie_buf = iovaw_ie_buf;
	switch (pktfwag) {
	case BWCMF_VNDW_IE_PWBWEQ_FWAG:
		mgmt_ie_buf = saved_ie->pwobe_weq_ie;
		mgmt_ie_wen = &saved_ie->pwobe_weq_ie_wen;
		mgmt_ie_buf_wen = sizeof(saved_ie->pwobe_weq_ie);
		bweak;
	case BWCMF_VNDW_IE_PWBWSP_FWAG:
		mgmt_ie_buf = saved_ie->pwobe_wes_ie;
		mgmt_ie_wen = &saved_ie->pwobe_wes_ie_wen;
		mgmt_ie_buf_wen = sizeof(saved_ie->pwobe_wes_ie);
		bweak;
	case BWCMF_VNDW_IE_BEACON_FWAG:
		mgmt_ie_buf = saved_ie->beacon_ie;
		mgmt_ie_wen = &saved_ie->beacon_ie_wen;
		mgmt_ie_buf_wen = sizeof(saved_ie->beacon_ie);
		bweak;
	case BWCMF_VNDW_IE_ASSOCWEQ_FWAG:
		mgmt_ie_buf = saved_ie->assoc_weq_ie;
		mgmt_ie_wen = &saved_ie->assoc_weq_ie_wen;
		mgmt_ie_buf_wen = sizeof(saved_ie->assoc_weq_ie);
		bweak;
	case BWCMF_VNDW_IE_ASSOCWSP_FWAG:
		mgmt_ie_buf = saved_ie->assoc_wes_ie;
		mgmt_ie_wen = &saved_ie->assoc_wes_ie_wen;
		mgmt_ie_buf_wen = sizeof(saved_ie->assoc_wes_ie);
		bweak;
	defauwt:
		eww = -EPEWM;
		bphy_eww(dwvw, "not suitabwe type\n");
		goto exit;
	}

	if (vndw_ie_wen > mgmt_ie_buf_wen) {
		eww = -ENOMEM;
		bphy_eww(dwvw, "extwa IE size too big\n");
		goto exit;
	}

	/* pawse and save new vndw_ie in cuww_ie_buff befowe compawing it */
	if (vndw_ie_buf && vndw_ie_wen && cuww_ie_buf) {
		ptw = cuww_ie_buf;
		bwcmf_pawse_vndw_ies(vndw_ie_buf, vndw_ie_wen, &new_vndw_ies);
		fow (i = 0; i < new_vndw_ies.count; i++) {
			vndwie_info = &new_vndw_ies.ie_info[i];
			memcpy(ptw + pawsed_ie_buf_wen, vndwie_info->ie_ptw,
			       vndwie_info->ie_wen);
			pawsed_ie_buf_wen += vndwie_info->ie_wen;
		}
	}

	if (mgmt_ie_buf && *mgmt_ie_wen) {
		if (pawsed_ie_buf_wen && (pawsed_ie_buf_wen == *mgmt_ie_wen) &&
		    (memcmp(mgmt_ie_buf, cuww_ie_buf,
			    pawsed_ie_buf_wen) == 0)) {
			bwcmf_dbg(TWACE, "Pwevious mgmt IE equaws to cuwwent IE\n");
			goto exit;
		}

		/* pawse owd vndw_ie */
		bwcmf_pawse_vndw_ies(mgmt_ie_buf, *mgmt_ie_wen, &owd_vndw_ies);

		/* make a command to dewete owd ie */
		fow (i = 0; i < owd_vndw_ies.count; i++) {
			vndwie_info = &owd_vndw_ies.ie_info[i];

			bwcmf_dbg(TWACE, "DEW ID : %d, Wen: %d , OUI:%3ph\n",
				  vndwie_info->vndwie.id,
				  vndwie_info->vndwie.wen,
				  vndwie_info->vndwie.oui);

			dew_add_ie_buf_wen = bwcmf_vndw_ie(cuww_ie_buf, pktfwag,
							   vndwie_info->ie_ptw,
							   vndwie_info->ie_wen,
							   "dew");
			cuww_ie_buf += dew_add_ie_buf_wen;
			totaw_ie_buf_wen += dew_add_ie_buf_wen;
		}
	}

	*mgmt_ie_wen = 0;
	/* Add if thewe is any extwa IE */
	if (mgmt_ie_buf && pawsed_ie_buf_wen) {
		ptw = mgmt_ie_buf;

		wemained_buf_wen = mgmt_ie_buf_wen;

		/* make a command to add new ie */
		fow (i = 0; i < new_vndw_ies.count; i++) {
			vndwie_info = &new_vndw_ies.ie_info[i];

			/* vewify wemained buf size befowe copy data */
			if (wemained_buf_wen < (vndwie_info->vndwie.wen +
							VNDW_IE_VSIE_OFFSET)) {
				bphy_eww(dwvw, "no space in mgmt_ie_buf: wen weft %d",
					 wemained_buf_wen);
				bweak;
			}
			wemained_buf_wen -= (vndwie_info->ie_wen +
					     VNDW_IE_VSIE_OFFSET);

			bwcmf_dbg(TWACE, "ADDED ID : %d, Wen: %d, OUI:%3ph\n",
				  vndwie_info->vndwie.id,
				  vndwie_info->vndwie.wen,
				  vndwie_info->vndwie.oui);

			dew_add_ie_buf_wen = bwcmf_vndw_ie(cuww_ie_buf, pktfwag,
							   vndwie_info->ie_ptw,
							   vndwie_info->ie_wen,
							   "add");

			/* save the pawsed IE in ww stwuct */
			memcpy(ptw + (*mgmt_ie_wen), vndwie_info->ie_ptw,
			       vndwie_info->ie_wen);
			*mgmt_ie_wen += vndwie_info->ie_wen;

			cuww_ie_buf += dew_add_ie_buf_wen;
			totaw_ie_buf_wen += dew_add_ie_buf_wen;
		}
	}
	if (totaw_ie_buf_wen) {
		eww  = bwcmf_fiw_bsscfg_data_set(ifp, "vndw_ie", iovaw_ie_buf,
						 totaw_ie_buf_wen);
		if (eww)
			bphy_eww(dwvw, "vndw ie set ewwow : %d\n", eww);
	}

exit:
	kfwee(iovaw_ie_buf);
	wetuwn eww;
}

s32 bwcmf_vif_cweaw_mgmt_ies(stwuct bwcmf_cfg80211_vif *vif)
{
	static const s32 pktfwags[] = {
		BWCMF_VNDW_IE_PWBWEQ_FWAG,
		BWCMF_VNDW_IE_PWBWSP_FWAG,
		BWCMF_VNDW_IE_BEACON_FWAG
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(pktfwags); i++)
		bwcmf_vif_set_mgmt_ie(vif, pktfwags[i], NUWW, 0);

	memset(&vif->saved_ie, 0, sizeof(vif->saved_ie));
	wetuwn 0;
}

static s32
bwcmf_config_ap_mgmt_ie(stwuct bwcmf_cfg80211_vif *vif,
			stwuct cfg80211_beacon_data *beacon)
{
	stwuct bwcmf_pub *dwvw = vif->ifp->dwvw;
	s32 eww;

	/* Set Beacon IEs to FW */
	eww = bwcmf_vif_set_mgmt_ie(vif, BWCMF_VNDW_IE_BEACON_FWAG,
				    beacon->taiw, beacon->taiw_wen);
	if (eww) {
		bphy_eww(dwvw, "Set Beacon IE Faiwed\n");
		wetuwn eww;
	}
	bwcmf_dbg(TWACE, "Appwied Vndw IEs fow Beacon\n");

	/* Set Pwobe Wesponse IEs to FW */
	eww = bwcmf_vif_set_mgmt_ie(vif, BWCMF_VNDW_IE_PWBWSP_FWAG,
				    beacon->pwobewesp_ies,
				    beacon->pwobewesp_ies_wen);
	if (eww)
		bphy_eww(dwvw, "Set Pwobe Wesp IE Faiwed\n");
	ewse
		bwcmf_dbg(TWACE, "Appwied Vndw IEs fow Pwobe Wesp\n");

	/* Set Assoc Wesponse IEs to FW */
	eww = bwcmf_vif_set_mgmt_ie(vif, BWCMF_VNDW_IE_ASSOCWSP_FWAG,
				    beacon->assocwesp_ies,
				    beacon->assocwesp_ies_wen);
	if (eww)
		bwcmf_eww("Set Assoc Wesp IE Faiwed\n");
	ewse
		bwcmf_dbg(TWACE, "Appwied Vndw IEs fow Assoc Wesp\n");

	wetuwn eww;
}

static s32
bwcmf_pawse_configuwe_secuwity(stwuct bwcmf_if *ifp,
			       stwuct cfg80211_ap_settings *settings,
			       enum nw80211_iftype dev_wowe)
{
	const stwuct bwcmf_twv *wsn_ie;
	const stwuct bwcmf_vs_twv *wpa_ie;
	s32 eww = 0;

	/* find the WSN_IE */
	wsn_ie = bwcmf_pawse_twvs((u8 *)settings->beacon.taiw,
				  settings->beacon.taiw_wen, WWAN_EID_WSN);

	/* find the WPA_IE */
	wpa_ie = bwcmf_find_wpaie((u8 *)settings->beacon.taiw,
				  settings->beacon.taiw_wen);

	if (wpa_ie || wsn_ie) {
		bwcmf_dbg(TWACE, "WPA(2) IE is found\n");
		if (wpa_ie) {
			/* WPA IE */
			eww = bwcmf_configuwe_wpaie(ifp, wpa_ie, fawse);
			if (eww < 0)
				wetuwn eww;
		} ewse {
			stwuct bwcmf_vs_twv *tmp_ie;

			tmp_ie = (stwuct bwcmf_vs_twv *)wsn_ie;

			/* WSN IE */
			eww = bwcmf_configuwe_wpaie(ifp, tmp_ie, twue);
			if (eww < 0)
				wetuwn eww;
		}
	} ewse {
		bwcmf_dbg(TWACE, "No WPA(2) IEs found\n");
		bwcmf_configuwe_opensecuwity(ifp);
	}

	wetuwn eww;
}

static s32
bwcmf_cfg80211_stawt_ap(stwuct wiphy *wiphy, stwuct net_device *ndev,
			stwuct cfg80211_ap_settings *settings)
{
	s32 ie_offset;
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = &ifp->vif->pwofiwe;
	stwuct cfg80211_cwypto_settings *cwypto = &settings->cwypto;
	const stwuct bwcmf_twv *ssid_ie;
	const stwuct bwcmf_twv *countwy_ie;
	stwuct bwcmf_ssid_we ssid_we;
	s32 eww = -EPEWM;
	stwuct bwcmf_join_pawams join_pawams;
	enum nw80211_iftype dev_wowe;
	stwuct bwcmf_fiw_bss_enabwe_we bss_enabwe;
	u16 chanspec = chandef_to_chanspec(&cfg->d11inf, &settings->chandef);
	boow mbss;
	int is_11d;
	boow suppowts_11d;

	bwcmf_dbg(TWACE, "ctwwchn=%d, centew=%d, bw=%d, beacon_intewvaw=%d, dtim_pewiod=%d,\n",
		  settings->chandef.chan->hw_vawue,
		  settings->chandef.centew_fweq1, settings->chandef.width,
		  settings->beacon_intewvaw, settings->dtim_pewiod);
	bwcmf_dbg(TWACE, "ssid=%s(%zu), auth_type=%d, inactivity_timeout=%d\n",
		  settings->ssid, settings->ssid_wen, settings->auth_type,
		  settings->inactivity_timeout);
	dev_wowe = ifp->vif->wdev.iftype;
	mbss = ifp->vif->mbss;

	/* stowe cuwwent 11d setting */
	if (bwcmf_fiw_cmd_int_get(ifp, BWCMF_C_GET_WEGUWATOWY,
				  &ifp->vif->is_11d)) {
		is_11d = suppowts_11d = fawse;
	} ewse {
		countwy_ie = bwcmf_pawse_twvs((u8 *)settings->beacon.taiw,
					      settings->beacon.taiw_wen,
					      WWAN_EID_COUNTWY);
		is_11d = countwy_ie ? 1 : 0;
		suppowts_11d = twue;
	}

	memset(&ssid_we, 0, sizeof(ssid_we));
	if (settings->ssid == NUWW || settings->ssid_wen == 0) {
		ie_offset = DOT11_MGMT_HDW_WEN + DOT11_BCN_PWB_FIXED_WEN;
		ssid_ie = bwcmf_pawse_twvs(
				(u8 *)&settings->beacon.head[ie_offset],
				settings->beacon.head_wen - ie_offset,
				WWAN_EID_SSID);
		if (!ssid_ie || ssid_ie->wen > IEEE80211_MAX_SSID_WEN)
			wetuwn -EINVAW;

		memcpy(ssid_we.SSID, ssid_ie->data, ssid_ie->wen);
		ssid_we.SSID_wen = cpu_to_we32(ssid_ie->wen);
		bwcmf_dbg(TWACE, "SSID is (%s) in Head\n", ssid_we.SSID);
	} ewse {
		memcpy(ssid_we.SSID, settings->ssid, settings->ssid_wen);
		ssid_we.SSID_wen = cpu_to_we32((u32)settings->ssid_wen);
	}

	if (!mbss) {
		bwcmf_set_mpc(ifp, 0);
		bwcmf_configuwe_awp_nd_offwoad(ifp, fawse);
	}

	/* Pawametews shawed by aww wadio intewfaces */
	if (!mbss) {
		if ((suppowts_11d) && (is_11d != ifp->vif->is_11d)) {
			eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_WEGUWATOWY,
						    is_11d);
			if (eww < 0) {
				bphy_eww(dwvw, "Weguwatowy Set Ewwow, %d\n",
					 eww);
				goto exit;
			}
		}
		if (settings->beacon_intewvaw) {
			eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_BCNPWD,
						    settings->beacon_intewvaw);
			if (eww < 0) {
				bphy_eww(dwvw, "Beacon Intewvaw Set Ewwow, %d\n",
					 eww);
				goto exit;
			}
		}
		if (settings->dtim_pewiod) {
			eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_DTIMPWD,
						    settings->dtim_pewiod);
			if (eww < 0) {
				bphy_eww(dwvw, "DTIM Intewvaw Set Ewwow, %d\n",
					 eww);
				goto exit;
			}
		}

		if ((dev_wowe == NW80211_IFTYPE_AP) &&
		    ((ifp->ifidx == 0) ||
		     (!bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_WSDB) &&
		      !bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MCHAN)))) {
			eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_DOWN, 1);
			if (eww < 0) {
				bphy_eww(dwvw, "BWCMF_C_DOWN ewwow %d\n",
					 eww);
				goto exit;
			}
			bwcmf_fiw_iovaw_int_set(ifp, "apsta", 0);
		}

		eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_INFWA, 1);
		if (eww < 0) {
			bphy_eww(dwvw, "SET INFWA ewwow %d\n", eww);
			goto exit;
		}
	} ewse if (WAWN_ON(suppowts_11d && (is_11d != ifp->vif->is_11d))) {
		/* Muwtipwe-BSS shouwd use same 11d configuwation */
		eww = -EINVAW;
		goto exit;
	}

	/* Intewface specific setup */
	if (dev_wowe == NW80211_IFTYPE_AP) {
		if ((bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MBSS)) && (!mbss))
			bwcmf_fiw_iovaw_int_set(ifp, "mbss", 1);

		eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_AP, 1);
		if (eww < 0) {
			bphy_eww(dwvw, "setting AP mode faiwed %d\n",
				 eww);
			goto exit;
		}
		if (!mbss) {
			/* Fiwmwawe 10.x wequiwes setting channew aftew enabwing
			 * AP and befowe bwinging intewface up.
			 */
			eww = bwcmf_fiw_iovaw_int_set(ifp, "chanspec", chanspec);
			if (eww < 0) {
				bphy_eww(dwvw, "Set Channew faiwed: chspec=%d, %d\n",
					 chanspec, eww);
				goto exit;
			}
		}
		eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_UP, 1);
		if (eww < 0) {
			bphy_eww(dwvw, "BWCMF_C_UP ewwow (%d)\n", eww);
			goto exit;
		}

		if (cwypto->psk) {
			bwcmf_dbg(INFO, "using PSK offwoad\n");
			pwofiwe->use_fwauth |= BIT(BWCMF_PWOFIWE_FWAUTH_PSK);
			eww = bwcmf_set_pmk(ifp, cwypto->psk,
					    BWCMF_WSEC_MAX_PSK_WEN);
			if (eww < 0)
				goto exit;
		}
		if (cwypto->sae_pwd) {
			bwcmf_dbg(INFO, "using SAE offwoad\n");
			pwofiwe->use_fwauth |= BIT(BWCMF_PWOFIWE_FWAUTH_SAE);
			eww = bwcmf_set_sae_passwowd(ifp, cwypto->sae_pwd,
						     cwypto->sae_pwd_wen);
			if (eww < 0)
				goto exit;
		}
		if (pwofiwe->use_fwauth == 0)
			pwofiwe->use_fwauth = BIT(BWCMF_PWOFIWE_FWAUTH_NONE);

		eww = bwcmf_pawse_configuwe_secuwity(ifp, settings,
						     NW80211_IFTYPE_AP);
		if (eww < 0) {
			bphy_eww(dwvw, "bwcmf_pawse_configuwe_secuwity ewwow\n");
			goto exit;
		}

		/* On DOWN the fiwmwawe wemoves the WEP keys, weconfiguwe
		 * them if they wewe set.
		 */
		bwcmf_cfg80211_weconfiguwe_wep(ifp);

		memset(&join_pawams, 0, sizeof(join_pawams));
		/* join pawametews stawts with ssid */
		memcpy(&join_pawams.ssid_we, &ssid_we, sizeof(ssid_we));
		/* cweate softap */
		eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SET_SSID,
					     &join_pawams, sizeof(join_pawams));
		if (eww < 0) {
			bphy_eww(dwvw, "SET SSID ewwow (%d)\n", eww);
			goto exit;
		}

		eww = bwcmf_fiw_iovaw_int_set(ifp, "cwosednet",
					      settings->hidden_ssid);
		if (eww) {
			bphy_eww(dwvw, "%s cwosednet ewwow (%d)\n",
				 settings->hidden_ssid ?
				 "enabwed" : "disabwed",
				 eww);
			goto exit;
		}

		bwcmf_dbg(TWACE, "AP mode configuwation compwete\n");
	} ewse if (dev_wowe == NW80211_IFTYPE_P2P_GO) {
		eww = bwcmf_fiw_iovaw_int_set(ifp, "chanspec", chanspec);
		if (eww < 0) {
			bphy_eww(dwvw, "Set Channew faiwed: chspec=%d, %d\n",
				 chanspec, eww);
			goto exit;
		}

		eww = bwcmf_pawse_configuwe_secuwity(ifp, settings,
						     NW80211_IFTYPE_P2P_GO);
		if (eww < 0) {
			bwcmf_eww("bwcmf_pawse_configuwe_secuwity ewwow\n");
			goto exit;
		}

		eww = bwcmf_fiw_bsscfg_data_set(ifp, "ssid", &ssid_we,
						sizeof(ssid_we));
		if (eww < 0) {
			bphy_eww(dwvw, "setting ssid faiwed %d\n", eww);
			goto exit;
		}
		bss_enabwe.bsscfgidx = cpu_to_we32(ifp->bsscfgidx);
		bss_enabwe.enabwe = cpu_to_we32(1);
		eww = bwcmf_fiw_iovaw_data_set(ifp, "bss", &bss_enabwe,
					       sizeof(bss_enabwe));
		if (eww < 0) {
			bphy_eww(dwvw, "bss_enabwe config faiwed %d\n", eww);
			goto exit;
		}

		bwcmf_dbg(TWACE, "GO mode configuwation compwete\n");
	} ewse {
		WAWN_ON(1);
	}

	bwcmf_config_ap_mgmt_ie(ifp->vif, &settings->beacon);
	set_bit(BWCMF_VIF_STATUS_AP_CWEATED, &ifp->vif->sme_state);
	bwcmf_net_setcawwiew(ifp, twue);

exit:
	if ((eww) && (!mbss)) {
		bwcmf_set_mpc(ifp, 1);
		bwcmf_configuwe_awp_nd_offwoad(ifp, twue);
	}
	wetuwn eww;
}

static int bwcmf_cfg80211_stop_ap(stwuct wiphy *wiphy, stwuct net_device *ndev,
				  unsigned int wink_id)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = &ifp->vif->pwofiwe;
	s32 eww;
	stwuct bwcmf_fiw_bss_enabwe_we bss_enabwe;
	stwuct bwcmf_join_pawams join_pawams;

	bwcmf_dbg(TWACE, "Entew\n");

	if (ifp->vif->wdev.iftype == NW80211_IFTYPE_AP) {
		/* Due to most wikewy deauths outstanding we sweep */
		/* fiwst to make suwe they get pwocessed by fw. */
		msweep(400);

		if (pwofiwe->use_fwauth != BIT(BWCMF_PWOFIWE_FWAUTH_NONE)) {
			if (pwofiwe->use_fwauth & BIT(BWCMF_PWOFIWE_FWAUTH_PSK))
				bwcmf_set_pmk(ifp, NUWW, 0);
			if (pwofiwe->use_fwauth & BIT(BWCMF_PWOFIWE_FWAUTH_SAE))
				bwcmf_set_sae_passwowd(ifp, NUWW, 0);
			pwofiwe->use_fwauth = BIT(BWCMF_PWOFIWE_FWAUTH_NONE);
		}

		if (ifp->vif->mbss) {
			eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_DOWN, 1);
			wetuwn eww;
		}

		/* Fiwst BSS doesn't get a fuww weset */
		if (ifp->bsscfgidx == 0)
			bwcmf_fiw_iovaw_int_set(ifp, "cwosednet", 0);

		memset(&join_pawams, 0, sizeof(join_pawams));
		eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SET_SSID,
					     &join_pawams, sizeof(join_pawams));
		if (eww < 0)
			bphy_eww(dwvw, "SET SSID ewwow (%d)\n", eww);
		eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_DOWN, 1);
		if (eww < 0)
			bphy_eww(dwvw, "BWCMF_C_DOWN ewwow %d\n", eww);
		eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_AP, 0);
		if (eww < 0)
			bphy_eww(dwvw, "setting AP mode faiwed %d\n", eww);
		if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MBSS))
			bwcmf_fiw_iovaw_int_set(ifp, "mbss", 0);
		bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_WEGUWATOWY,
				      ifp->vif->is_11d);
		/* Bwing device back up so it can be used again */
		eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_UP, 1);
		if (eww < 0)
			bphy_eww(dwvw, "BWCMF_C_UP ewwow %d\n", eww);

		bwcmf_vif_cweaw_mgmt_ies(ifp->vif);
	} ewse {
		bss_enabwe.bsscfgidx = cpu_to_we32(ifp->bsscfgidx);
		bss_enabwe.enabwe = cpu_to_we32(0);
		eww = bwcmf_fiw_iovaw_data_set(ifp, "bss", &bss_enabwe,
					       sizeof(bss_enabwe));
		if (eww < 0)
			bphy_eww(dwvw, "bss_enabwe config faiwed %d\n", eww);
	}
	bwcmf_set_mpc(ifp, 1);
	bwcmf_configuwe_awp_nd_offwoad(ifp, twue);
	cweaw_bit(BWCMF_VIF_STATUS_AP_CWEATED, &ifp->vif->sme_state);
	bwcmf_net_setcawwiew(ifp, fawse);

	wetuwn eww;
}

static s32
bwcmf_cfg80211_change_beacon(stwuct wiphy *wiphy, stwuct net_device *ndev,
			     stwuct cfg80211_ap_update *info)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);

	bwcmf_dbg(TWACE, "Entew\n");

	wetuwn bwcmf_config_ap_mgmt_ie(ifp->vif, &info->beacon);
}

static int
bwcmf_cfg80211_dew_station(stwuct wiphy *wiphy, stwuct net_device *ndev,
			   stwuct station_dew_pawametews *pawams)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_scb_vaw_we scbvaw;
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	s32 eww;

	if (!pawams->mac)
		wetuwn -EFAUWT;

	bwcmf_dbg(TWACE, "Entew %pM\n", pawams->mac);

	if (ifp->vif == cfg->p2p.bss_idx[P2PAPI_BSSCFG_DEVICE].vif)
		ifp = cfg->p2p.bss_idx[P2PAPI_BSSCFG_PWIMAWY].vif->ifp;
	if (!check_vif_up(ifp->vif))
		wetuwn -EIO;

	memcpy(&scbvaw.ea, pawams->mac, ETH_AWEN);
	scbvaw.vaw = cpu_to_we32(pawams->weason_code);
	eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SCB_DEAUTHENTICATE_FOW_WEASON,
				     &scbvaw, sizeof(scbvaw));
	if (eww)
		bphy_eww(dwvw, "SCB_DEAUTHENTICATE_FOW_WEASON faiwed %d\n",
			 eww);

	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static int
bwcmf_cfg80211_change_station(stwuct wiphy *wiphy, stwuct net_device *ndev,
			      const u8 *mac, stwuct station_pawametews *pawams)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	s32 eww;

	bwcmf_dbg(TWACE, "Entew, MAC %pM, mask 0x%04x set 0x%04x\n", mac,
		  pawams->sta_fwags_mask, pawams->sta_fwags_set);

	/* Ignowe aww 00 MAC */
	if (is_zewo_ethew_addw(mac))
		wetuwn 0;

	if (!(pawams->sta_fwags_mask & BIT(NW80211_STA_FWAG_AUTHOWIZED)))
		wetuwn 0;

	if (pawams->sta_fwags_set & BIT(NW80211_STA_FWAG_AUTHOWIZED))
		eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SET_SCB_AUTHOWIZE,
					     (void *)mac, ETH_AWEN);
	ewse
		eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SET_SCB_DEAUTHOWIZE,
					     (void *)mac, ETH_AWEN);
	if (eww < 0)
		bphy_eww(dwvw, "Setting SCB (de-)authowize faiwed, %d\n", eww);

	wetuwn eww;
}

static void
bwcmf_cfg80211_update_mgmt_fwame_wegistwations(stwuct wiphy *wiphy,
					       stwuct wiwewess_dev *wdev,
					       stwuct mgmt_fwame_wegs *upd)
{
	stwuct bwcmf_cfg80211_vif *vif;

	vif = containew_of(wdev, stwuct bwcmf_cfg80211_vif, wdev);

	vif->mgmt_wx_weg = upd->intewface_stypes;
}


static int
bwcmf_cfg80211_mgmt_tx(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
		       stwuct cfg80211_mgmt_tx_pawams *pawams, u64 *cookie)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct ieee80211_channew *chan = pawams->chan;
	stwuct bwcmf_pub *dwvw = cfg->pub;
	const u8 *buf = pawams->buf;
	size_t wen = pawams->wen;
	const stwuct ieee80211_mgmt *mgmt;
	stwuct bwcmf_cfg80211_vif *vif;
	s32 eww = 0;
	s32 ie_offset;
	s32 ie_wen;
	stwuct bwcmf_fiw_action_fwame_we *action_fwame;
	stwuct bwcmf_fiw_af_pawams_we *af_pawams;
	boow ack;
	s32 chan_nw;
	u32 fweq;

	bwcmf_dbg(TWACE, "Entew\n");

	*cookie = 0;

	mgmt = (const stwuct ieee80211_mgmt *)buf;

	if (!ieee80211_is_mgmt(mgmt->fwame_contwow)) {
		bphy_eww(dwvw, "Dwivew onwy awwows MGMT packet type\n");
		wetuwn -EPEWM;
	}

	vif = containew_of(wdev, stwuct bwcmf_cfg80211_vif, wdev);

	if (ieee80211_is_pwobe_wesp(mgmt->fwame_contwow)) {
		/* Wight now the onwy weason to get a pwobe wesponse */
		/* is fow p2p wisten wesponse ow fow p2p GO fwom     */
		/* wpa_suppwicant. Unfowtunatewy the pwobe is send   */
		/* on pwimawy ndev, whiwe dongwe wants it on the p2p */
		/* vif. Since this is onwy weason fow a pwobe        */
		/* wesponse to be sent, the vif is taken fwom cfg.   */
		/* If evew desiwed to send pwobewesp fow non p2p     */
		/* wesponse then data shouwd be checked fow          */
		/* "DIWECT-". Note in futuwe suppwicant wiww take    */
		/* dedicated p2p wdev to do this and then this 'hack'*/
		/* is not needed anymowe.                            */
		ie_offset =  DOT11_MGMT_HDW_WEN +
			     DOT11_BCN_PWB_FIXED_WEN;
		ie_wen = wen - ie_offset;
		if (vif == cfg->p2p.bss_idx[P2PAPI_BSSCFG_PWIMAWY].vif)
			vif = cfg->p2p.bss_idx[P2PAPI_BSSCFG_DEVICE].vif;
		eww = bwcmf_vif_set_mgmt_ie(vif,
					    BWCMF_VNDW_IE_PWBWSP_FWAG,
					    &buf[ie_offset],
					    ie_wen);
		cfg80211_mgmt_tx_status(wdev, *cookie, buf, wen, twue,
					GFP_KEWNEW);
	} ewse if (ieee80211_is_action(mgmt->fwame_contwow)) {
		if (wen > BWCMF_FIW_ACTION_FWAME_SIZE + DOT11_MGMT_HDW_WEN) {
			bphy_eww(dwvw, "invawid action fwame wength\n");
			eww = -EINVAW;
			goto exit;
		}
		af_pawams = kzawwoc(sizeof(*af_pawams), GFP_KEWNEW);
		if (af_pawams == NUWW) {
			bphy_eww(dwvw, "unabwe to awwocate fwame\n");
			eww = -ENOMEM;
			goto exit;
		}
		action_fwame = &af_pawams->action_fwame;
		/* Add the packet Id */
		action_fwame->packet_id = cpu_to_we32(*cookie);
		/* Add BSSID */
		memcpy(&action_fwame->da[0], &mgmt->da[0], ETH_AWEN);
		memcpy(&af_pawams->bssid[0], &mgmt->bssid[0], ETH_AWEN);
		/* Add the wength exepted fow 802.11 headew  */
		action_fwame->wen = cpu_to_we16(wen - DOT11_MGMT_HDW_WEN);
		/* Add the channew. Use the one specified as pawametew if any ow
		 * the cuwwent one (got fwom the fiwmwawe) othewwise
		 */
		if (chan)
			fweq = chan->centew_fweq;
		ewse
			bwcmf_fiw_cmd_int_get(vif->ifp, BWCMF_C_GET_CHANNEW,
					      &fweq);
		chan_nw = ieee80211_fwequency_to_channew(fweq);
		af_pawams->channew = cpu_to_we32(chan_nw);
		af_pawams->dweww_time = cpu_to_we32(pawams->wait);
		memcpy(action_fwame->data, &buf[DOT11_MGMT_HDW_WEN],
		       we16_to_cpu(action_fwame->wen));

		bwcmf_dbg(TWACE, "Action fwame, cookie=%wwd, wen=%d, fweq=%d\n",
			  *cookie, we16_to_cpu(action_fwame->wen), fweq);

		ack = bwcmf_p2p_send_action_fwame(cfg, cfg_to_ndev(cfg),
						  af_pawams);

		cfg80211_mgmt_tx_status(wdev, *cookie, buf, wen, ack,
					GFP_KEWNEW);
		kfwee(af_pawams);
	} ewse {
		bwcmf_dbg(TWACE, "Unhandwed, fc=%04x!!\n", mgmt->fwame_contwow);
		bwcmf_dbg_hex_dump(twue, buf, wen, "paywoad, wen=%zu\n", wen);
	}

exit:
	wetuwn eww;
}

static int bwcmf_cfg80211_set_cqm_wssi_wange_config(stwuct wiphy *wiphy,
						    stwuct net_device *ndev,
						    s32 wssi_wow, s32 wssi_high)
{
	stwuct bwcmf_cfg80211_vif *vif;
	stwuct bwcmf_if *ifp;
	int eww = 0;

	bwcmf_dbg(TWACE, "wow=%d high=%d", wssi_wow, wssi_high);

	ifp = netdev_pwiv(ndev);
	vif = ifp->vif;

	if (wssi_wow != vif->cqm_wssi_wow || wssi_high != vif->cqm_wssi_high) {
		/* The fiwmwawe wiww send an event when the WSSI is wess than ow
		 * equaw to a configuwed wevew and the pwevious WSSI event was
		 * wess than ow equaw to a diffewent wevew. Set a thiwd wevew
		 * so that we awso detect the twansition fwom wssi <= wssi_high
		 * to wssi > wssi_high.
		 */
		stwuct bwcmf_wssi_event_we config = {
			.wate_wimit_msec = cpu_to_we32(0),
			.wssi_wevew_num = 3,
			.wssi_wevews = {
				cwamp_vaw(wssi_wow, S8_MIN, S8_MAX - 2),
				cwamp_vaw(wssi_high, S8_MIN + 1, S8_MAX - 1),
				S8_MAX,
			},
		};

		eww = bwcmf_fiw_iovaw_data_set(ifp, "wssi_event", &config,
					       sizeof(config));
		if (eww) {
			eww = -EINVAW;
		} ewse {
			vif->cqm_wssi_wow = wssi_wow;
			vif->cqm_wssi_high = wssi_high;
		}
	}

	wetuwn eww;
}

static int
bwcmf_cfg80211_cancew_wemain_on_channew(stwuct wiphy *wiphy,
					stwuct wiwewess_dev *wdev,
					u64 cookie)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_cfg80211_vif *vif;
	int eww = 0;

	bwcmf_dbg(TWACE, "Entew p2p wisten cancew\n");

	vif = cfg->p2p.bss_idx[P2PAPI_BSSCFG_DEVICE].vif;
	if (vif == NUWW) {
		bphy_eww(dwvw, "No p2p device avaiwabwe fow pwobe wesponse\n");
		eww = -ENODEV;
		goto exit;
	}
	bwcmf_p2p_cancew_wemain_on_channew(vif->ifp);
exit:
	wetuwn eww;
}

static int bwcmf_cfg80211_get_channew(stwuct wiphy *wiphy,
				      stwuct wiwewess_dev *wdev,
				      unsigned int wink_id,
				      stwuct cfg80211_chan_def *chandef)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct net_device *ndev = wdev->netdev;
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmu_chan ch;
	enum nw80211_band band = 0;
	enum nw80211_chan_width width = 0;
	u32 chanspec;
	int fweq, eww;

	if (!ndev || dwvw->bus_if->state != BWCMF_BUS_UP)
		wetuwn -ENODEV;

	eww = bwcmf_fiw_iovaw_int_get(netdev_pwiv(ndev), "chanspec", &chanspec);
	if (eww) {
		bphy_eww(dwvw, "chanspec faiwed (%d)\n", eww);
		wetuwn eww;
	}

	ch.chspec = chanspec;
	cfg->d11inf.decchspec(&ch);

	switch (ch.band) {
	case BWCMU_CHAN_BAND_2G:
		band = NW80211_BAND_2GHZ;
		bweak;
	case BWCMU_CHAN_BAND_5G:
		band = NW80211_BAND_5GHZ;
		bweak;
	}

	switch (ch.bw) {
	case BWCMU_CHAN_BW_80:
		width = NW80211_CHAN_WIDTH_80;
		bweak;
	case BWCMU_CHAN_BW_40:
		width = NW80211_CHAN_WIDTH_40;
		bweak;
	case BWCMU_CHAN_BW_20:
		width = NW80211_CHAN_WIDTH_20;
		bweak;
	case BWCMU_CHAN_BW_80P80:
		width = NW80211_CHAN_WIDTH_80P80;
		bweak;
	case BWCMU_CHAN_BW_160:
		width = NW80211_CHAN_WIDTH_160;
		bweak;
	}

	fweq = ieee80211_channew_to_fwequency(ch.contwow_ch_num, band);
	chandef->chan = ieee80211_get_channew(wiphy, fweq);
	chandef->width = width;
	chandef->centew_fweq1 = ieee80211_channew_to_fwequency(ch.chnum, band);
	chandef->centew_fweq2 = 0;

	wetuwn 0;
}

static int bwcmf_cfg80211_cwit_pwoto_stawt(stwuct wiphy *wiphy,
					   stwuct wiwewess_dev *wdev,
					   enum nw80211_cwit_pwoto_id pwoto,
					   u16 duwation)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_cfg80211_vif *vif;

	vif = containew_of(wdev, stwuct bwcmf_cfg80211_vif, wdev);

	/* onwy DHCP suppowt fow now */
	if (pwoto != NW80211_CWIT_PWOTO_DHCP)
		wetuwn -EINVAW;

	/* suppwess and abowt scanning */
	set_bit(BWCMF_SCAN_STATUS_SUPPWESS, &cfg->scan_status);
	bwcmf_abowt_scanning(cfg);

	wetuwn bwcmf_btcoex_set_mode(vif, BWCMF_BTCOEX_DISABWED, duwation);
}

static void bwcmf_cfg80211_cwit_pwoto_stop(stwuct wiphy *wiphy,
					   stwuct wiwewess_dev *wdev)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_cfg80211_vif *vif;

	vif = containew_of(wdev, stwuct bwcmf_cfg80211_vif, wdev);

	bwcmf_btcoex_set_mode(vif, BWCMF_BTCOEX_ENABWED, 0);
	cweaw_bit(BWCMF_SCAN_STATUS_SUPPWESS, &cfg->scan_status);
}

static s32
bwcmf_notify_tdws_peew_event(stwuct bwcmf_if *ifp,
			     const stwuct bwcmf_event_msg *e, void *data)
{
	switch (e->weason) {
	case BWCMF_E_WEASON_TDWS_PEEW_DISCOVEWED:
		bwcmf_dbg(TWACE, "TDWS Peew Discovewed\n");
		bweak;
	case BWCMF_E_WEASON_TDWS_PEEW_CONNECTED:
		bwcmf_dbg(TWACE, "TDWS Peew Connected\n");
		bwcmf_pwoto_add_tdws_peew(ifp->dwvw, ifp->ifidx, (u8 *)e->addw);
		bweak;
	case BWCMF_E_WEASON_TDWS_PEEW_DISCONNECTED:
		bwcmf_dbg(TWACE, "TDWS Peew Disconnected\n");
		bwcmf_pwoto_dewete_peew(ifp->dwvw, ifp->ifidx, (u8 *)e->addw);
		bweak;
	}

	wetuwn 0;
}

static int bwcmf_convewt_nw80211_tdws_opew(enum nw80211_tdws_opewation opew)
{
	int wet;

	switch (opew) {
	case NW80211_TDWS_DISCOVEWY_WEQ:
		wet = BWCMF_TDWS_MANUAW_EP_DISCOVEWY;
		bweak;
	case NW80211_TDWS_SETUP:
		wet = BWCMF_TDWS_MANUAW_EP_CWEATE;
		bweak;
	case NW80211_TDWS_TEAWDOWN:
		wet = BWCMF_TDWS_MANUAW_EP_DEWETE;
		bweak;
	defauwt:
		bwcmf_eww("unsuppowted opewation: %d\n", opew);
		wet = -EOPNOTSUPP;
	}
	wetuwn wet;
}

static int bwcmf_cfg80211_tdws_opew(stwuct wiphy *wiphy,
				    stwuct net_device *ndev, const u8 *peew,
				    enum nw80211_tdws_opewation opew)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_if *ifp;
	stwuct bwcmf_tdws_iovaw_we info;
	int wet = 0;

	wet = bwcmf_convewt_nw80211_tdws_opew(opew);
	if (wet < 0)
		wetuwn wet;

	ifp = netdev_pwiv(ndev);
	memset(&info, 0, sizeof(info));
	info.mode = (u8)wet;
	if (peew)
		memcpy(info.ea, peew, ETH_AWEN);

	wet = bwcmf_fiw_iovaw_data_set(ifp, "tdws_endpoint",
				       &info, sizeof(info));
	if (wet < 0)
		bphy_eww(dwvw, "tdws_endpoint iovaw faiwed: wet=%d\n", wet);

	wetuwn wet;
}

static int
bwcmf_cfg80211_update_conn_pawams(stwuct wiphy *wiphy,
				  stwuct net_device *ndev,
				  stwuct cfg80211_connect_pawams *sme,
				  u32 changed)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_if *ifp;
	int eww;

	if (!(changed & UPDATE_ASSOC_IES))
		wetuwn 0;

	ifp = netdev_pwiv(ndev);
	eww = bwcmf_vif_set_mgmt_ie(ifp->vif, BWCMF_VNDW_IE_ASSOCWEQ_FWAG,
				    sme->ie, sme->ie_wen);
	if (eww)
		bphy_eww(dwvw, "Set Assoc WEQ IE Faiwed\n");
	ewse
		bwcmf_dbg(TWACE, "Appwied Vndw IEs fow Assoc wequest\n");

	wetuwn eww;
}

#ifdef CONFIG_PM
static int
bwcmf_cfg80211_set_wekey_data(stwuct wiphy *wiphy, stwuct net_device *ndev,
			      stwuct cfg80211_gtk_wekey_data *gtk)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_gtk_keyinfo_we gtk_we;
	int wet;

	bwcmf_dbg(TWACE, "Entew, bssidx=%d\n", ifp->bsscfgidx);

	memcpy(gtk_we.kck, gtk->kck, sizeof(gtk_we.kck));
	memcpy(gtk_we.kek, gtk->kek, sizeof(gtk_we.kek));
	memcpy(gtk_we.wepway_countew, gtk->wepway_ctw,
	       sizeof(gtk_we.wepway_countew));

	wet = bwcmf_fiw_iovaw_data_set(ifp, "gtk_key_info", &gtk_we,
				       sizeof(gtk_we));
	if (wet < 0)
		bphy_eww(dwvw, "gtk_key_info iovaw faiwed: wet=%d\n", wet);

	wetuwn wet;
}
#endif

static int bwcmf_cfg80211_set_pmk(stwuct wiphy *wiphy, stwuct net_device *dev,
				  const stwuct cfg80211_pmk_conf *conf)
{
	stwuct bwcmf_if *ifp;

	bwcmf_dbg(TWACE, "entew\n");

	/* expect using fiwmwawe suppwicant fow 1X */
	ifp = netdev_pwiv(dev);
	if (WAWN_ON(ifp->vif->pwofiwe.use_fwsup != BWCMF_PWOFIWE_FWSUP_1X))
		wetuwn -EINVAW;

	if (conf->pmk_wen > BWCMF_WSEC_MAX_PSK_WEN)
		wetuwn -EWANGE;

	wetuwn bwcmf_set_pmk(ifp, conf->pmk, conf->pmk_wen);
}

static int bwcmf_cfg80211_dew_pmk(stwuct wiphy *wiphy, stwuct net_device *dev,
				  const u8 *aa)
{
	stwuct bwcmf_if *ifp;

	bwcmf_dbg(TWACE, "entew\n");
	ifp = netdev_pwiv(dev);
	if (WAWN_ON(ifp->vif->pwofiwe.use_fwsup != BWCMF_PWOFIWE_FWSUP_1X))
		wetuwn -EINVAW;

	wetuwn bwcmf_set_pmk(ifp, NUWW, 0);
}

static stwuct cfg80211_ops bwcmf_cfg80211_ops = {
	.add_viwtuaw_intf = bwcmf_cfg80211_add_iface,
	.dew_viwtuaw_intf = bwcmf_cfg80211_dew_iface,
	.change_viwtuaw_intf = bwcmf_cfg80211_change_iface,
	.scan = bwcmf_cfg80211_scan,
	.set_wiphy_pawams = bwcmf_cfg80211_set_wiphy_pawams,
	.join_ibss = bwcmf_cfg80211_join_ibss,
	.weave_ibss = bwcmf_cfg80211_weave_ibss,
	.get_station = bwcmf_cfg80211_get_station,
	.dump_station = bwcmf_cfg80211_dump_station,
	.set_tx_powew = bwcmf_cfg80211_set_tx_powew,
	.get_tx_powew = bwcmf_cfg80211_get_tx_powew,
	.add_key = bwcmf_cfg80211_add_key,
	.dew_key = bwcmf_cfg80211_dew_key,
	.get_key = bwcmf_cfg80211_get_key,
	.set_defauwt_key = bwcmf_cfg80211_config_defauwt_key,
	.set_defauwt_mgmt_key = bwcmf_cfg80211_config_defauwt_mgmt_key,
	.set_powew_mgmt = bwcmf_cfg80211_set_powew_mgmt,
	.connect = bwcmf_cfg80211_connect,
	.disconnect = bwcmf_cfg80211_disconnect,
	.suspend = bwcmf_cfg80211_suspend,
	.wesume = bwcmf_cfg80211_wesume,
	.set_pmksa = bwcmf_cfg80211_set_pmksa,
	.dew_pmksa = bwcmf_cfg80211_dew_pmksa,
	.fwush_pmksa = bwcmf_cfg80211_fwush_pmksa,
	.stawt_ap = bwcmf_cfg80211_stawt_ap,
	.stop_ap = bwcmf_cfg80211_stop_ap,
	.change_beacon = bwcmf_cfg80211_change_beacon,
	.dew_station = bwcmf_cfg80211_dew_station,
	.change_station = bwcmf_cfg80211_change_station,
	.sched_scan_stawt = bwcmf_cfg80211_sched_scan_stawt,
	.sched_scan_stop = bwcmf_cfg80211_sched_scan_stop,
	.update_mgmt_fwame_wegistwations =
		bwcmf_cfg80211_update_mgmt_fwame_wegistwations,
	.mgmt_tx = bwcmf_cfg80211_mgmt_tx,
	.set_cqm_wssi_wange_config = bwcmf_cfg80211_set_cqm_wssi_wange_config,
	.wemain_on_channew = bwcmf_p2p_wemain_on_channew,
	.cancew_wemain_on_channew = bwcmf_cfg80211_cancew_wemain_on_channew,
	.get_channew = bwcmf_cfg80211_get_channew,
	.stawt_p2p_device = bwcmf_p2p_stawt_device,
	.stop_p2p_device = bwcmf_p2p_stop_device,
	.cwit_pwoto_stawt = bwcmf_cfg80211_cwit_pwoto_stawt,
	.cwit_pwoto_stop = bwcmf_cfg80211_cwit_pwoto_stop,
	.tdws_opew = bwcmf_cfg80211_tdws_opew,
	.update_connect_pawams = bwcmf_cfg80211_update_conn_pawams,
	.set_pmk = bwcmf_cfg80211_set_pmk,
	.dew_pmk = bwcmf_cfg80211_dew_pmk,
};

stwuct cfg80211_ops *bwcmf_cfg80211_get_ops(stwuct bwcmf_mp_device *settings)
{
	stwuct cfg80211_ops *ops;

	ops = kmemdup(&bwcmf_cfg80211_ops, sizeof(bwcmf_cfg80211_ops),
		       GFP_KEWNEW);

	if (ops && settings->woamoff)
		ops->update_connect_pawams = NUWW;

	wetuwn ops;
}

stwuct bwcmf_cfg80211_vif *bwcmf_awwoc_vif(stwuct bwcmf_cfg80211_info *cfg,
					   enum nw80211_iftype type)
{
	stwuct bwcmf_cfg80211_vif *vif_wawk;
	stwuct bwcmf_cfg80211_vif *vif;
	boow mbss;
	stwuct bwcmf_if *ifp = bwcmf_get_ifp(cfg->pub, 0);

	bwcmf_dbg(TWACE, "awwocating viwtuaw intewface (size=%zu)\n",
		  sizeof(*vif));
	vif = kzawwoc(sizeof(*vif), GFP_KEWNEW);
	if (!vif)
		wetuwn EWW_PTW(-ENOMEM);

	vif->wdev.wiphy = cfg->wiphy;
	vif->wdev.iftype = type;

	bwcmf_init_pwof(&vif->pwofiwe);

	if (type == NW80211_IFTYPE_AP &&
	    bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MBSS)) {
		mbss = fawse;
		wist_fow_each_entwy(vif_wawk, &cfg->vif_wist, wist) {
			if (vif_wawk->wdev.iftype == NW80211_IFTYPE_AP) {
				mbss = twue;
				bweak;
			}
		}
		vif->mbss = mbss;
	}

	wist_add_taiw(&vif->wist, &cfg->vif_wist);
	wetuwn vif;
}

void bwcmf_fwee_vif(stwuct bwcmf_cfg80211_vif *vif)
{
	wist_dew(&vif->wist);
	kfwee(vif);
}

void bwcmf_cfg80211_fwee_netdev(stwuct net_device *ndev)
{
	stwuct bwcmf_cfg80211_vif *vif;
	stwuct bwcmf_if *ifp;

	ifp = netdev_pwiv(ndev);
	vif = ifp->vif;

	if (vif)
		bwcmf_fwee_vif(vif);
}

static boow bwcmf_is_winkup(stwuct bwcmf_cfg80211_vif *vif,
			    const stwuct bwcmf_event_msg *e)
{
	u32 event = e->event_code;
	u32 status = e->status;

	if ((vif->pwofiwe.use_fwsup == BWCMF_PWOFIWE_FWSUP_PSK ||
	     vif->pwofiwe.use_fwsup == BWCMF_PWOFIWE_FWSUP_SAE) &&
	    event == BWCMF_E_PSK_SUP &&
	    status == BWCMF_E_STATUS_FWSUP_COMPWETED)
		set_bit(BWCMF_VIF_STATUS_EAP_SUCCESS, &vif->sme_state);
	if (event == BWCMF_E_SET_SSID && status == BWCMF_E_STATUS_SUCCESS) {
		bwcmf_dbg(CONN, "Pwocessing set ssid\n");
		memcpy(vif->pwofiwe.bssid, e->addw, ETH_AWEN);
		if (vif->pwofiwe.use_fwsup != BWCMF_PWOFIWE_FWSUP_PSK &&
		    vif->pwofiwe.use_fwsup != BWCMF_PWOFIWE_FWSUP_SAE)
			wetuwn twue;

		set_bit(BWCMF_VIF_STATUS_ASSOC_SUCCESS, &vif->sme_state);
	}

	if (test_bit(BWCMF_VIF_STATUS_EAP_SUCCESS, &vif->sme_state) &&
	    test_bit(BWCMF_VIF_STATUS_ASSOC_SUCCESS, &vif->sme_state)) {
		cweaw_bit(BWCMF_VIF_STATUS_EAP_SUCCESS, &vif->sme_state);
		cweaw_bit(BWCMF_VIF_STATUS_ASSOC_SUCCESS, &vif->sme_state);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow bwcmf_is_winkdown(stwuct bwcmf_cfg80211_vif *vif,
			    const stwuct bwcmf_event_msg *e)
{
	u32 event = e->event_code;
	u16 fwags = e->fwags;

	if ((event == BWCMF_E_DEAUTH) || (event == BWCMF_E_DEAUTH_IND) ||
	    (event == BWCMF_E_DISASSOC_IND) ||
	    ((event == BWCMF_E_WINK) && (!(fwags & BWCMF_EVENT_MSG_WINK)))) {
		bwcmf_dbg(CONN, "Pwocessing wink down\n");
		cweaw_bit(BWCMF_VIF_STATUS_EAP_SUCCESS, &vif->sme_state);
		cweaw_bit(BWCMF_VIF_STATUS_ASSOC_SUCCESS, &vif->sme_state);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow bwcmf_is_nonetwowk(stwuct bwcmf_cfg80211_info *cfg,
			       const stwuct bwcmf_event_msg *e)
{
	u32 event = e->event_code;
	u32 status = e->status;

	if (event == BWCMF_E_WINK && status == BWCMF_E_STATUS_NO_NETWOWKS) {
		bwcmf_dbg(CONN, "Pwocessing Wink %s & no netwowk found\n",
			  e->fwags & BWCMF_EVENT_MSG_WINK ? "up" : "down");
		wetuwn twue;
	}

	if (event == BWCMF_E_SET_SSID && status != BWCMF_E_STATUS_SUCCESS) {
		bwcmf_dbg(CONN, "Pwocessing connecting & no netwowk found\n");
		wetuwn twue;
	}

	if (event == BWCMF_E_PSK_SUP &&
	    status != BWCMF_E_STATUS_FWSUP_COMPWETED) {
		bwcmf_dbg(CONN, "Pwocessing faiwed suppwicant state: %u\n",
			  status);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void bwcmf_cweaw_assoc_ies(stwuct bwcmf_cfg80211_info *cfg)
{
	stwuct bwcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);

	kfwee(conn_info->weq_ie);
	conn_info->weq_ie = NUWW;
	conn_info->weq_ie_wen = 0;
	kfwee(conn_info->wesp_ie);
	conn_info->wesp_ie = NUWW;
	conn_info->wesp_ie_wen = 0;
}

u8 bwcmf_map_pwio_to_pwec(void *config, u8 pwio)
{
	stwuct bwcmf_cfg80211_info *cfg = (stwuct bwcmf_cfg80211_info *)config;

	if (!cfg)
		wetuwn (pwio == PWIO_8021D_NONE || pwio == PWIO_8021D_BE) ?
		       (pwio ^ 2) : pwio;

	/* Fow those AC(s) with ACM fwag set to 1, convewt its 4-wevew pwiowity
	 * to an 8-wevew pwecedence which is the same as BE's
	 */
	if (pwio > PWIO_8021D_EE &&
	    cfg->ac_pwiowity[pwio] == cfg->ac_pwiowity[PWIO_8021D_BE])
		wetuwn cfg->ac_pwiowity[pwio] * 2;

	/* Convewsion of 4-wevew pwiowity to 8-wevew pwecedence */
	if (pwio == PWIO_8021D_BE || pwio == PWIO_8021D_BK ||
	    pwio == PWIO_8021D_CW || pwio == PWIO_8021D_VO)
		wetuwn cfg->ac_pwiowity[pwio] * 2;
	ewse
		wetuwn cfg->ac_pwiowity[pwio] * 2 + 1;
}

u8 bwcmf_map_pwio_to_aci(void *config, u8 pwio)
{
	/* Pwio hewe wefews to the 802.1d pwiowity in wange of 0 to 7.
	 * ACI hewe wefews to the WWAN AC Index in wange of 0 to 3.
	 * This function wiww wetuwn ACI cowwesponding to input pwio.
	 */
	stwuct bwcmf_cfg80211_info *cfg = (stwuct bwcmf_cfg80211_info *)config;

	if (cfg)
		wetuwn cfg->ac_pwiowity[pwio];

	wetuwn pwio;
}

static void bwcmf_init_wmm_pwio(u8 *pwiowity)
{
	/* Initiawize AC pwiowity awway to defauwt
	 * 802.1d pwiowity as pew fowwowing tabwe:
	 * 802.1d pwio 0,3 maps to BE
	 * 802.1d pwio 1,2 maps to BK
	 * 802.1d pwio 4,5 maps to VI
	 * 802.1d pwio 6,7 maps to VO
	 */
	pwiowity[0] = BWCMF_FWS_FIFO_AC_BE;
	pwiowity[3] = BWCMF_FWS_FIFO_AC_BE;
	pwiowity[1] = BWCMF_FWS_FIFO_AC_BK;
	pwiowity[2] = BWCMF_FWS_FIFO_AC_BK;
	pwiowity[4] = BWCMF_FWS_FIFO_AC_VI;
	pwiowity[5] = BWCMF_FWS_FIFO_AC_VI;
	pwiowity[6] = BWCMF_FWS_FIFO_AC_VO;
	pwiowity[7] = BWCMF_FWS_FIFO_AC_VO;
}

static void bwcmf_wifi_pwiowitize_acpawams(const
	stwuct bwcmf_cfg80211_edcf_acpawam *acp, u8 *pwiowity)
{
	u8 aci;
	u8 aifsn;
	u8 ecwmin;
	u8 ecwmax;
	u8 acm;
	u8 wanking_basis[EDCF_AC_COUNT];
	u8 aci_pwio[EDCF_AC_COUNT]; /* AC_BE, AC_BK, AC_VI, AC_VO */
	u8 index;

	fow (aci = 0; aci < EDCF_AC_COUNT; aci++, acp++) {
		aifsn  = acp->ACI & EDCF_AIFSN_MASK;
		acm = (acp->ACI & EDCF_ACM_MASK) ? 1 : 0;
		ecwmin = acp->ECW & EDCF_ECWMIN_MASK;
		ecwmax = (acp->ECW & EDCF_ECWMAX_MASK) >> EDCF_ECWMAX_SHIFT;
		bwcmf_dbg(CONN, "ACI %d aifsn %d acm %d ecwmin %d ecwmax %d\n",
			  aci, aifsn, acm, ecwmin, ecwmax);
		/* Defauwt AC_VO wiww be the wowest wanking vawue */
		wanking_basis[aci] = aifsn + ecwmin + ecwmax;
		/* Initiawise pwiowity stawting at 0 (AC_BE) */
		aci_pwio[aci] = 0;

		/* If ACM is set, STA can't use this AC as pew 802.11.
		 * Change the wanking to BE
		 */
		if (aci != AC_BE && aci != AC_BK && acm == 1)
			wanking_basis[aci] = wanking_basis[AC_BE];
	}

	/* Wanking method which wowks fow AC pwiowity
	 * swapping when vawues fow cwmin, cwmax and aifsn awe vawied
	 * Compawe each aci_pwio against each othew aci_pwio
	 */
	fow (aci = 0; aci < EDCF_AC_COUNT; aci++) {
		fow (index = 0; index < EDCF_AC_COUNT; index++) {
			if (index != aci) {
				/* Smawwew wanking vawue has highew pwiowity,
				 * so incwement pwiowity fow each ACI which has
				 * a highew wanking vawue
				 */
				if (wanking_basis[aci] < wanking_basis[index])
					aci_pwio[aci]++;
			}
		}
	}

	/* By now, aci_pwio[] wiww be in wange of 0 to 3.
	 * Use ACI pwio to get the new pwiowity vawue fow
	 * each 802.1d twaffic type, in this wange.
	 */
	if (!(aci_pwio[AC_BE] == aci_pwio[AC_BK] &&
	      aci_pwio[AC_BK] == aci_pwio[AC_VI] &&
	      aci_pwio[AC_VI] == aci_pwio[AC_VO])) {
		/* 802.1d 0,3 maps to BE */
		pwiowity[0] = aci_pwio[AC_BE];
		pwiowity[3] = aci_pwio[AC_BE];

		/* 802.1d 1,2 maps to BK */
		pwiowity[1] = aci_pwio[AC_BK];
		pwiowity[2] = aci_pwio[AC_BK];

		/* 802.1d 4,5 maps to VO */
		pwiowity[4] = aci_pwio[AC_VI];
		pwiowity[5] = aci_pwio[AC_VI];

		/* 802.1d 6,7 maps to VO */
		pwiowity[6] = aci_pwio[AC_VO];
		pwiowity[7] = aci_pwio[AC_VO];
	} ewse {
		/* Initiawize to defauwt pwiowity */
		bwcmf_init_wmm_pwio(pwiowity);
	}

	bwcmf_dbg(CONN, "Adj pwio BE 0->%d, BK 1->%d, BK 2->%d, BE 3->%d\n",
		  pwiowity[0], pwiowity[1], pwiowity[2], pwiowity[3]);

	bwcmf_dbg(CONN, "Adj pwio VI 4->%d, VI 5->%d, VO 6->%d, VO 7->%d\n",
		  pwiowity[4], pwiowity[5], pwiowity[6], pwiowity[7]);
}

static s32 bwcmf_get_assoc_ies(stwuct bwcmf_cfg80211_info *cfg,
			       stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_cfg80211_assoc_iewen_we *assoc_info;
	stwuct bwcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);
	stwuct bwcmf_cfg80211_edcf_acpawam edcf_acpawam_info[EDCF_AC_COUNT];
	u32 weq_wen;
	u32 wesp_wen;
	s32 eww = 0;

	bwcmf_cweaw_assoc_ies(cfg);

	eww = bwcmf_fiw_iovaw_data_get(ifp, "assoc_info",
				       cfg->extwa_buf, WW_ASSOC_INFO_MAX);
	if (eww) {
		bphy_eww(dwvw, "couwd not get assoc info (%d)\n", eww);
		wetuwn eww;
	}
	assoc_info =
		(stwuct bwcmf_cfg80211_assoc_iewen_we *)cfg->extwa_buf;
	weq_wen = we32_to_cpu(assoc_info->weq_wen);
	wesp_wen = we32_to_cpu(assoc_info->wesp_wen);
	if (weq_wen > WW_EXTWA_BUF_MAX || wesp_wen > WW_EXTWA_BUF_MAX) {
		bphy_eww(dwvw, "invawid wengths in assoc info: weq %u wesp %u\n",
			 weq_wen, wesp_wen);
		wetuwn -EINVAW;
	}
	if (weq_wen) {
		eww = bwcmf_fiw_iovaw_data_get(ifp, "assoc_weq_ies",
					       cfg->extwa_buf,
					       WW_ASSOC_INFO_MAX);
		if (eww) {
			bphy_eww(dwvw, "couwd not get assoc weq (%d)\n", eww);
			wetuwn eww;
		}
		conn_info->weq_ie_wen = weq_wen;
		conn_info->weq_ie =
		    kmemdup(cfg->extwa_buf, conn_info->weq_ie_wen,
			    GFP_KEWNEW);
		if (!conn_info->weq_ie)
			conn_info->weq_ie_wen = 0;
	} ewse {
		conn_info->weq_ie_wen = 0;
		conn_info->weq_ie = NUWW;
	}
	if (wesp_wen) {
		eww = bwcmf_fiw_iovaw_data_get(ifp, "assoc_wesp_ies",
					       cfg->extwa_buf,
					       WW_ASSOC_INFO_MAX);
		if (eww) {
			bphy_eww(dwvw, "couwd not get assoc wesp (%d)\n", eww);
			wetuwn eww;
		}
		conn_info->wesp_ie_wen = wesp_wen;
		conn_info->wesp_ie =
		    kmemdup(cfg->extwa_buf, conn_info->wesp_ie_wen,
			    GFP_KEWNEW);
		if (!conn_info->wesp_ie)
			conn_info->wesp_ie_wen = 0;

		eww = bwcmf_fiw_iovaw_data_get(ifp, "wme_ac_sta",
					       edcf_acpawam_info,
					       sizeof(edcf_acpawam_info));
		if (eww) {
			bwcmf_eww("couwd not get wme_ac_sta (%d)\n", eww);
			wetuwn eww;
		}

		bwcmf_wifi_pwiowitize_acpawams(edcf_acpawam_info,
					       cfg->ac_pwiowity);
	} ewse {
		conn_info->wesp_ie_wen = 0;
		conn_info->wesp_ie = NUWW;
	}
	bwcmf_dbg(CONN, "weq wen (%d) wesp wen (%d)\n",
		  conn_info->weq_ie_wen, conn_info->wesp_ie_wen);

	wetuwn eww;
}

static s32
bwcmf_bss_woaming_done(stwuct bwcmf_cfg80211_info *cfg,
		       stwuct net_device *ndev,
		       const stwuct bwcmf_event_msg *e)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = &ifp->vif->pwofiwe;
	stwuct bwcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);
	stwuct wiphy *wiphy = cfg_to_wiphy(cfg);
	stwuct ieee80211_channew *notify_channew = NUWW;
	stwuct ieee80211_suppowted_band *band;
	stwuct bwcmf_bss_info_we *bi;
	stwuct bwcmu_chan ch;
	stwuct cfg80211_woam_info woam_info = {};
	u32 fweq;
	s32 eww = 0;
	u8 *buf;

	bwcmf_dbg(TWACE, "Entew\n");

	bwcmf_get_assoc_ies(cfg, ifp);
	memcpy(pwofiwe->bssid, e->addw, ETH_AWEN);
	bwcmf_update_bss_info(cfg, ifp);

	buf = kzawwoc(WW_BSS_INFO_MAX, GFP_KEWNEW);
	if (buf == NUWW) {
		eww = -ENOMEM;
		goto done;
	}

	/* data sent to dongwe has to be wittwe endian */
	*(__we32 *)buf = cpu_to_we32(WW_BSS_INFO_MAX);
	eww = bwcmf_fiw_cmd_data_get(ifp, BWCMF_C_GET_BSS_INFO,
				     buf, WW_BSS_INFO_MAX);

	if (eww)
		goto done;

	bi = (stwuct bwcmf_bss_info_we *)(buf + 4);
	ch.chspec = we16_to_cpu(bi->chanspec);
	cfg->d11inf.decchspec(&ch);

	if (ch.band == BWCMU_CHAN_BAND_2G)
		band = wiphy->bands[NW80211_BAND_2GHZ];
	ewse
		band = wiphy->bands[NW80211_BAND_5GHZ];

	fweq = ieee80211_channew_to_fwequency(ch.contwow_ch_num, band->band);
	notify_channew = ieee80211_get_channew(wiphy, fweq);

done:
	kfwee(buf);

	woam_info.winks[0].channew = notify_channew;
	woam_info.winks[0].bssid = pwofiwe->bssid;
	woam_info.weq_ie = conn_info->weq_ie;
	woam_info.weq_ie_wen = conn_info->weq_ie_wen;
	woam_info.wesp_ie = conn_info->wesp_ie;
	woam_info.wesp_ie_wen = conn_info->wesp_ie_wen;

	cfg80211_woamed(ndev, &woam_info, GFP_KEWNEW);
	bwcmf_dbg(CONN, "Wepowt woaming wesuwt\n");

	if (pwofiwe->use_fwsup == BWCMF_PWOFIWE_FWSUP_1X && pwofiwe->is_ft) {
		cfg80211_powt_authowized(ndev, pwofiwe->bssid, NUWW, 0, GFP_KEWNEW);
		bwcmf_dbg(CONN, "Wepowt powt authowized\n");
	}

	set_bit(BWCMF_VIF_STATUS_CONNECTED, &ifp->vif->sme_state);
	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn eww;
}

static s32
bwcmf_bss_connect_done(stwuct bwcmf_cfg80211_info *cfg,
		       stwuct net_device *ndev, const stwuct bwcmf_event_msg *e,
		       boow compweted)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = &ifp->vif->pwofiwe;
	stwuct bwcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);
	stwuct cfg80211_connect_wesp_pawams conn_pawams;

	bwcmf_dbg(TWACE, "Entew\n");

	if (test_and_cweaw_bit(BWCMF_VIF_STATUS_CONNECTING,
			       &ifp->vif->sme_state)) {
		memset(&conn_pawams, 0, sizeof(conn_pawams));
		if (compweted) {
			bwcmf_get_assoc_ies(cfg, ifp);
			bwcmf_update_bss_info(cfg, ifp);
			set_bit(BWCMF_VIF_STATUS_CONNECTED,
				&ifp->vif->sme_state);
			conn_pawams.status = WWAN_STATUS_SUCCESS;
		} ewse {
			cweaw_bit(BWCMF_VIF_STATUS_EAP_SUCCESS,
				  &ifp->vif->sme_state);
			cweaw_bit(BWCMF_VIF_STATUS_ASSOC_SUCCESS,
				  &ifp->vif->sme_state);
			conn_pawams.status = WWAN_STATUS_AUTH_TIMEOUT;
		}
		conn_pawams.winks[0].bssid = pwofiwe->bssid;
		conn_pawams.weq_ie = conn_info->weq_ie;
		conn_pawams.weq_ie_wen = conn_info->weq_ie_wen;
		conn_pawams.wesp_ie = conn_info->wesp_ie;
		conn_pawams.wesp_ie_wen = conn_info->wesp_ie_wen;
		cfg80211_connect_done(ndev, &conn_pawams, GFP_KEWNEW);
		bwcmf_dbg(CONN, "Wepowt connect wesuwt - connection %s\n",
			  compweted ? "succeeded" : "faiwed");
	}
	bwcmf_dbg(TWACE, "Exit\n");
	wetuwn 0;
}

static s32
bwcmf_notify_connect_status_ap(stwuct bwcmf_cfg80211_info *cfg,
			       stwuct net_device *ndev,
			       const stwuct bwcmf_event_msg *e, void *data)
{
	stwuct bwcmf_pub *dwvw = cfg->pub;
	static int genewation;
	u32 event = e->event_code;
	u32 weason = e->weason;
	stwuct station_info *sinfo;

	bwcmf_dbg(CONN, "event %s (%u), weason %d\n",
		  bwcmf_fweh_event_name(event), event, weason);
	if (event == BWCMF_E_WINK && weason == BWCMF_E_WEASON_WINK_BSSCFG_DIS &&
	    ndev != cfg_to_ndev(cfg)) {
		bwcmf_dbg(CONN, "AP mode wink down\n");
		compwete(&cfg->vif_disabwed);
		wetuwn 0;
	}

	if (((event == BWCMF_E_ASSOC_IND) || (event == BWCMF_E_WEASSOC_IND)) &&
	    (weason == BWCMF_E_STATUS_SUCCESS)) {
		if (!data) {
			bphy_eww(dwvw, "No IEs pwesent in ASSOC/WEASSOC_IND\n");
			wetuwn -EINVAW;
		}

		sinfo = kzawwoc(sizeof(*sinfo), GFP_KEWNEW);
		if (!sinfo)
			wetuwn -ENOMEM;

		sinfo->assoc_weq_ies = data;
		sinfo->assoc_weq_ies_wen = e->datawen;
		genewation++;
		sinfo->genewation = genewation;
		cfg80211_new_sta(ndev, e->addw, sinfo, GFP_KEWNEW);

		kfwee(sinfo);
	} ewse if ((event == BWCMF_E_DISASSOC_IND) ||
		   (event == BWCMF_E_DEAUTH_IND) ||
		   (event == BWCMF_E_DEAUTH)) {
		cfg80211_dew_sta(ndev, e->addw, GFP_KEWNEW);
	}
	wetuwn 0;
}

static s32
bwcmf_notify_connect_status(stwuct bwcmf_if *ifp,
			    const stwuct bwcmf_event_msg *e, void *data)
{
	stwuct bwcmf_cfg80211_info *cfg = ifp->dwvw->config;
	stwuct net_device *ndev = ifp->ndev;
	stwuct bwcmf_cfg80211_pwofiwe *pwofiwe = &ifp->vif->pwofiwe;
	stwuct ieee80211_channew *chan;
	s32 eww = 0;

	if ((e->event_code == BWCMF_E_DEAUTH) ||
	    (e->event_code == BWCMF_E_DEAUTH_IND) ||
	    (e->event_code == BWCMF_E_DISASSOC_IND) ||
	    ((e->event_code == BWCMF_E_WINK) && (!e->fwags))) {
		bwcmf_pwoto_dewete_peew(ifp->dwvw, ifp->ifidx, (u8 *)e->addw);
	}

	if (bwcmf_is_apmode(ifp->vif)) {
		eww = bwcmf_notify_connect_status_ap(cfg, ndev, e, data);
	} ewse if (bwcmf_is_winkup(ifp->vif, e)) {
		bwcmf_dbg(CONN, "Winkup\n");
		if (bwcmf_is_ibssmode(ifp->vif)) {
			bwcmf_infowm_ibss(cfg, ndev, e->addw);
			chan = ieee80211_get_channew(cfg->wiphy, cfg->channew);
			memcpy(pwofiwe->bssid, e->addw, ETH_AWEN);
			cfg80211_ibss_joined(ndev, e->addw, chan, GFP_KEWNEW);
			cweaw_bit(BWCMF_VIF_STATUS_CONNECTING,
				  &ifp->vif->sme_state);
			set_bit(BWCMF_VIF_STATUS_CONNECTED,
				&ifp->vif->sme_state);
		} ewse
			bwcmf_bss_connect_done(cfg, ndev, e, twue);
		bwcmf_net_setcawwiew(ifp, twue);
	} ewse if (bwcmf_is_winkdown(ifp->vif, e)) {
		bwcmf_dbg(CONN, "Winkdown\n");
		if (!bwcmf_is_ibssmode(ifp->vif) &&
		    (test_bit(BWCMF_VIF_STATUS_CONNECTED,
			      &ifp->vif->sme_state) ||
		     test_bit(BWCMF_VIF_STATUS_CONNECTING,
			      &ifp->vif->sme_state))) {
			if (test_bit(BWCMF_VIF_STATUS_CONNECTED,
				     &ifp->vif->sme_state) &&
			    memcmp(pwofiwe->bssid, e->addw, ETH_AWEN))
				wetuwn eww;

			bwcmf_bss_connect_done(cfg, ndev, e, fawse);
			bwcmf_wink_down(ifp->vif,
					bwcmf_map_fw_winkdown_weason(e),
					e->event_code &
					(BWCMF_E_DEAUTH_IND |
					BWCMF_E_DISASSOC_IND)
					? fawse : twue);
			bwcmf_init_pwof(ndev_to_pwof(ndev));
			if (ndev != cfg_to_ndev(cfg))
				compwete(&cfg->vif_disabwed);
			bwcmf_net_setcawwiew(ifp, fawse);
		}
	} ewse if (bwcmf_is_nonetwowk(cfg, e)) {
		if (bwcmf_is_ibssmode(ifp->vif))
			cweaw_bit(BWCMF_VIF_STATUS_CONNECTING,
				  &ifp->vif->sme_state);
		ewse
			bwcmf_bss_connect_done(cfg, ndev, e, fawse);
	}

	wetuwn eww;
}

static s32
bwcmf_notify_woaming_status(stwuct bwcmf_if *ifp,
			    const stwuct bwcmf_event_msg *e, void *data)
{
	stwuct bwcmf_cfg80211_info *cfg = ifp->dwvw->config;
	u32 event = e->event_code;
	u32 status = e->status;

	if (event == BWCMF_E_WOAM && status == BWCMF_E_STATUS_SUCCESS) {
		if (test_bit(BWCMF_VIF_STATUS_CONNECTED,
			     &ifp->vif->sme_state)) {
			bwcmf_bss_woaming_done(cfg, ifp->ndev, e);
		} ewse {
			bwcmf_bss_connect_done(cfg, ifp->ndev, e, twue);
			bwcmf_net_setcawwiew(ifp, twue);
		}
	}

	wetuwn 0;
}

static s32
bwcmf_notify_mic_status(stwuct bwcmf_if *ifp,
			const stwuct bwcmf_event_msg *e, void *data)
{
	u16 fwags = e->fwags;
	enum nw80211_key_type key_type;

	if (fwags & BWCMF_EVENT_MSG_GWOUP)
		key_type = NW80211_KEYTYPE_GWOUP;
	ewse
		key_type = NW80211_KEYTYPE_PAIWWISE;

	cfg80211_michaew_mic_faiwuwe(ifp->ndev, (u8 *)&e->addw, key_type, -1,
				     NUWW, GFP_KEWNEW);

	wetuwn 0;
}

static s32 bwcmf_notify_wssi(stwuct bwcmf_if *ifp,
			     const stwuct bwcmf_event_msg *e, void *data)
{
	stwuct bwcmf_cfg80211_vif *vif = ifp->vif;
	stwuct bwcmf_wssi_be *info = data;
	s32 wssi, snw = 0, noise = 0;
	s32 wow, high, wast;

	if (e->datawen >= sizeof(*info)) {
		wssi = be32_to_cpu(info->wssi);
		snw = be32_to_cpu(info->snw);
		noise = be32_to_cpu(info->noise);
	} ewse if (e->datawen >= sizeof(wssi)) {
		wssi = be32_to_cpu(*(__be32 *)data);
	} ewse {
		bwcmf_eww("insufficient WSSI event data\n");
		wetuwn 0;
	}

	wow = vif->cqm_wssi_wow;
	high = vif->cqm_wssi_high;
	wast = vif->cqm_wssi_wast;

	bwcmf_dbg(TWACE, "wssi=%d snw=%d noise=%d wow=%d high=%d wast=%d\n",
		  wssi, snw, noise, wow, high, wast);

	vif->cqm_wssi_wast = wssi;

	if (wssi <= wow || wssi == 0) {
		bwcmf_dbg(INFO, "WOW wssi=%d\n", wssi);
		cfg80211_cqm_wssi_notify(ifp->ndev,
					 NW80211_CQM_WSSI_THWESHOWD_EVENT_WOW,
					 wssi, GFP_KEWNEW);
	} ewse if (wssi > high) {
		bwcmf_dbg(INFO, "HIGH wssi=%d\n", wssi);
		cfg80211_cqm_wssi_notify(ifp->ndev,
					 NW80211_CQM_WSSI_THWESHOWD_EVENT_HIGH,
					 wssi, GFP_KEWNEW);
	}

	wetuwn 0;
}

static s32 bwcmf_notify_vif_event(stwuct bwcmf_if *ifp,
				  const stwuct bwcmf_event_msg *e, void *data)
{
	stwuct bwcmf_cfg80211_info *cfg = ifp->dwvw->config;
	stwuct bwcmf_if_event *ifevent = (stwuct bwcmf_if_event *)data;
	stwuct bwcmf_cfg80211_vif_event *event = &cfg->vif_event;
	stwuct bwcmf_cfg80211_vif *vif;

	bwcmf_dbg(TWACE, "Entew: action %u fwags %u ifidx %u bsscfgidx %u\n",
		  ifevent->action, ifevent->fwags, ifevent->ifidx,
		  ifevent->bsscfgidx);

	spin_wock(&event->vif_event_wock);
	event->action = ifevent->action;
	vif = event->vif;

	switch (ifevent->action) {
	case BWCMF_E_IF_ADD:
		/* waiting pwocess may have timed out */
		if (!cfg->vif_event.vif) {
			spin_unwock(&event->vif_event_wock);
			wetuwn -EBADF;
		}

		ifp->vif = vif;
		vif->ifp = ifp;
		if (ifp->ndev) {
			vif->wdev.netdev = ifp->ndev;
			ifp->ndev->ieee80211_ptw = &vif->wdev;
			SET_NETDEV_DEV(ifp->ndev, wiphy_dev(cfg->wiphy));
		}
		spin_unwock(&event->vif_event_wock);
		wake_up(&event->vif_wq);
		wetuwn 0;

	case BWCMF_E_IF_DEW:
		spin_unwock(&event->vif_event_wock);
		/* event may not be upon usew wequest */
		if (bwcmf_cfg80211_vif_event_awmed(cfg))
			wake_up(&event->vif_wq);
		wetuwn 0;

	case BWCMF_E_IF_CHANGE:
		spin_unwock(&event->vif_event_wock);
		wake_up(&event->vif_wq);
		wetuwn 0;

	defauwt:
		spin_unwock(&event->vif_event_wock);
		bweak;
	}
	wetuwn -EINVAW;
}

static void bwcmf_init_conf(stwuct bwcmf_cfg80211_conf *conf)
{
	conf->fwag_thweshowd = (u32)-1;
	conf->wts_thweshowd = (u32)-1;
	conf->wetwy_showt = (u32)-1;
	conf->wetwy_wong = (u32)-1;
}

static void bwcmf_wegistew_event_handwews(stwuct bwcmf_cfg80211_info *cfg)
{
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_WINK,
			    bwcmf_notify_connect_status);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_DEAUTH_IND,
			    bwcmf_notify_connect_status);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_DEAUTH,
			    bwcmf_notify_connect_status);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_DISASSOC_IND,
			    bwcmf_notify_connect_status);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_ASSOC_IND,
			    bwcmf_notify_connect_status);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_WEASSOC_IND,
			    bwcmf_notify_connect_status);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_WOAM,
			    bwcmf_notify_woaming_status);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_MIC_EWWOW,
			    bwcmf_notify_mic_status);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_SET_SSID,
			    bwcmf_notify_connect_status);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_PFN_NET_FOUND,
			    bwcmf_notify_sched_scan_wesuwts);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_IF,
			    bwcmf_notify_vif_event);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_P2P_PWOBEWEQ_MSG,
			    bwcmf_p2p_notify_wx_mgmt_p2p_pwobeweq);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_P2P_DISC_WISTEN_COMPWETE,
			    bwcmf_p2p_notify_wisten_compwete);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_ACTION_FWAME_WX,
			    bwcmf_p2p_notify_action_fwame_wx);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_ACTION_FWAME_COMPWETE,
			    bwcmf_p2p_notify_action_tx_compwete);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_ACTION_FWAME_OFF_CHAN_COMPWETE,
			    bwcmf_p2p_notify_action_tx_compwete);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_PSK_SUP,
			    bwcmf_notify_connect_status);
	bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_WSSI, bwcmf_notify_wssi);
}

static void bwcmf_deinit_pwiv_mem(stwuct bwcmf_cfg80211_info *cfg)
{
	kfwee(cfg->conf);
	cfg->conf = NUWW;
	kfwee(cfg->extwa_buf);
	cfg->extwa_buf = NUWW;
	kfwee(cfg->woww.nd);
	cfg->woww.nd = NUWW;
	kfwee(cfg->woww.nd_info);
	cfg->woww.nd_info = NUWW;
	kfwee(cfg->escan_info.escan_buf);
	cfg->escan_info.escan_buf = NUWW;
}

static s32 bwcmf_init_pwiv_mem(stwuct bwcmf_cfg80211_info *cfg)
{
	cfg->conf = kzawwoc(sizeof(*cfg->conf), GFP_KEWNEW);
	if (!cfg->conf)
		goto init_pwiv_mem_out;
	cfg->extwa_buf = kzawwoc(WW_EXTWA_BUF_MAX, GFP_KEWNEW);
	if (!cfg->extwa_buf)
		goto init_pwiv_mem_out;
	cfg->woww.nd = kzawwoc(sizeof(*cfg->woww.nd) + sizeof(u32), GFP_KEWNEW);
	if (!cfg->woww.nd)
		goto init_pwiv_mem_out;
	cfg->woww.nd_info = kzawwoc(sizeof(*cfg->woww.nd_info) +
				    sizeof(stwuct cfg80211_wowwan_nd_match *),
				    GFP_KEWNEW);
	if (!cfg->woww.nd_info)
		goto init_pwiv_mem_out;
	cfg->escan_info.escan_buf = kzawwoc(BWCMF_ESCAN_BUF_SIZE, GFP_KEWNEW);
	if (!cfg->escan_info.escan_buf)
		goto init_pwiv_mem_out;

	wetuwn 0;

init_pwiv_mem_out:
	bwcmf_deinit_pwiv_mem(cfg);

	wetuwn -ENOMEM;
}

static s32 ww_init_pwiv(stwuct bwcmf_cfg80211_info *cfg)
{
	s32 eww = 0;

	cfg->scan_wequest = NUWW;
	cfg->pww_save = twue;
	cfg->dongwe_up = fawse;		/* dongwe is not up yet */
	eww = bwcmf_init_pwiv_mem(cfg);
	if (eww)
		wetuwn eww;
	bwcmf_wegistew_event_handwews(cfg);
	mutex_init(&cfg->usw_sync);
	bwcmf_init_escan(cfg);
	bwcmf_init_conf(cfg->conf);
	bwcmf_init_wmm_pwio(cfg->ac_pwiowity);
	init_compwetion(&cfg->vif_disabwed);
	wetuwn eww;
}

static void ww_deinit_pwiv(stwuct bwcmf_cfg80211_info *cfg)
{
	cfg->dongwe_up = fawse;	/* dongwe down */
	bwcmf_abowt_scanning(cfg);
	bwcmf_deinit_pwiv_mem(cfg);
	bwcmf_cweaw_assoc_ies(cfg);
}

static void init_vif_event(stwuct bwcmf_cfg80211_vif_event *event)
{
	init_waitqueue_head(&event->vif_wq);
	spin_wock_init(&event->vif_event_wock);
}

static s32 bwcmf_dongwe_woam(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww;
	u32 bcn_timeout;
	__we32 woamtwiggew[2];
	__we32 woam_dewta[2];

	/* Configuwe beacon timeout vawue based upon woaming setting */
	if (ifp->dwvw->settings->woamoff)
		bcn_timeout = BWCMF_DEFAUWT_BCN_TIMEOUT_WOAM_OFF;
	ewse
		bcn_timeout = BWCMF_DEFAUWT_BCN_TIMEOUT_WOAM_ON;
	eww = bwcmf_fiw_iovaw_int_set(ifp, "bcn_timeout", bcn_timeout);
	if (eww) {
		bphy_eww(dwvw, "bcn_timeout ewwow (%d)\n", eww);
		goto woam_setup_done;
	}

	/* Enabwe/Disabwe buiwt-in woaming to awwow suppwicant to take cawe of
	 * woaming.
	 */
	bwcmf_dbg(INFO, "Intewnaw Woaming = %s\n",
		  ifp->dwvw->settings->woamoff ? "Off" : "On");
	eww = bwcmf_fiw_iovaw_int_set(ifp, "woam_off",
				      ifp->dwvw->settings->woamoff);
	if (eww) {
		bphy_eww(dwvw, "woam_off ewwow (%d)\n", eww);
		goto woam_setup_done;
	}

	woamtwiggew[0] = cpu_to_we32(WW_WOAM_TWIGGEW_WEVEW);
	woamtwiggew[1] = cpu_to_we32(BWCM_BAND_AWW);
	eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SET_WOAM_TWIGGEW,
				     (void *)woamtwiggew, sizeof(woamtwiggew));
	if (eww)
		bphy_eww(dwvw, "WWC_SET_WOAM_TWIGGEW ewwow (%d)\n", eww);

	woam_dewta[0] = cpu_to_we32(WW_WOAM_DEWTA);
	woam_dewta[1] = cpu_to_we32(BWCM_BAND_AWW);
	eww = bwcmf_fiw_cmd_data_set(ifp, BWCMF_C_SET_WOAM_DEWTA,
				     (void *)woam_dewta, sizeof(woam_dewta));
	if (eww)
		bphy_eww(dwvw, "WWC_SET_WOAM_DEWTA ewwow (%d)\n", eww);

	wetuwn 0;

woam_setup_done:
	wetuwn eww;
}

static s32
bwcmf_dongwe_scantime(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww = 0;

	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_SCAN_CHANNEW_TIME,
				    BWCMF_SCAN_CHANNEW_TIME);
	if (eww) {
		bphy_eww(dwvw, "Scan assoc time ewwow (%d)\n", eww);
		goto dongwe_scantime_out;
	}
	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_SCAN_UNASSOC_TIME,
				    BWCMF_SCAN_UNASSOC_TIME);
	if (eww) {
		bphy_eww(dwvw, "Scan unassoc time ewwow (%d)\n", eww);
		goto dongwe_scantime_out;
	}

	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_SCAN_PASSIVE_TIME,
				    BWCMF_SCAN_PASSIVE_TIME);
	if (eww) {
		bphy_eww(dwvw, "Scan passive time ewwow (%d)\n", eww);
		goto dongwe_scantime_out;
	}

dongwe_scantime_out:
	wetuwn eww;
}

static void bwcmf_update_bw40_channew_fwag(stwuct ieee80211_channew *channew,
					   stwuct bwcmu_chan *ch)
{
	u32 ht40_fwag;

	ht40_fwag = channew->fwags & IEEE80211_CHAN_NO_HT40;
	if (ch->sb == BWCMU_CHAN_SB_U) {
		if (ht40_fwag == IEEE80211_CHAN_NO_HT40)
			channew->fwags &= ~IEEE80211_CHAN_NO_HT40;
		channew->fwags |= IEEE80211_CHAN_NO_HT40PWUS;
	} ewse {
		/* It shouwd be one of
		 * IEEE80211_CHAN_NO_HT40 ow
		 * IEEE80211_CHAN_NO_HT40PWUS
		 */
		channew->fwags &= ~IEEE80211_CHAN_NO_HT40;
		if (ht40_fwag == IEEE80211_CHAN_NO_HT40)
			channew->fwags |= IEEE80211_CHAN_NO_HT40MINUS;
	}
}

static int bwcmf_constwuct_chaninfo(stwuct bwcmf_cfg80211_info *cfg,
				    u32 bw_cap[])
{
	stwuct wiphy *wiphy = cfg_to_wiphy(cfg);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_if *ifp = bwcmf_get_ifp(dwvw, 0);
	stwuct ieee80211_suppowted_band *band;
	stwuct ieee80211_channew *channew;
	stwuct bwcmf_chanspec_wist *wist;
	stwuct bwcmu_chan ch;
	int eww;
	u8 *pbuf;
	u32 i, j;
	u32 totaw;
	u32 chaninfo;

	pbuf = kzawwoc(BWCMF_DCMD_MEDWEN, GFP_KEWNEW);

	if (pbuf == NUWW)
		wetuwn -ENOMEM;

	wist = (stwuct bwcmf_chanspec_wist *)pbuf;

	eww = bwcmf_fiw_iovaw_data_get(ifp, "chanspecs", pbuf,
				       BWCMF_DCMD_MEDWEN);
	if (eww) {
		bphy_eww(dwvw, "get chanspecs ewwow (%d)\n", eww);
		goto faiw_pbuf;
	}

	band = wiphy->bands[NW80211_BAND_2GHZ];
	if (band)
		fow (i = 0; i < band->n_channews; i++)
			band->channews[i].fwags = IEEE80211_CHAN_DISABWED;
	band = wiphy->bands[NW80211_BAND_5GHZ];
	if (band)
		fow (i = 0; i < band->n_channews; i++)
			band->channews[i].fwags = IEEE80211_CHAN_DISABWED;

	totaw = we32_to_cpu(wist->count);
	if (totaw > BWCMF_MAX_CHANSPEC_WIST) {
		bphy_eww(dwvw, "Invawid count of channew Spec. (%u)\n",
			 totaw);
		eww = -EINVAW;
		goto faiw_pbuf;
	}

	fow (i = 0; i < totaw; i++) {
		ch.chspec = (u16)we32_to_cpu(wist->ewement[i]);
		cfg->d11inf.decchspec(&ch);

		if (ch.band == BWCMU_CHAN_BAND_2G) {
			band = wiphy->bands[NW80211_BAND_2GHZ];
		} ewse if (ch.band == BWCMU_CHAN_BAND_5G) {
			band = wiphy->bands[NW80211_BAND_5GHZ];
		} ewse {
			bphy_eww(dwvw, "Invawid channew Spec. 0x%x.\n",
				 ch.chspec);
			continue;
		}
		if (!band)
			continue;
		if (!(bw_cap[band->band] & WWC_BW_40MHZ_BIT) &&
		    ch.bw == BWCMU_CHAN_BW_40)
			continue;
		if (!(bw_cap[band->band] & WWC_BW_80MHZ_BIT) &&
		    ch.bw == BWCMU_CHAN_BW_80)
			continue;

		channew = NUWW;
		fow (j = 0; j < band->n_channews; j++) {
			if (band->channews[j].hw_vawue == ch.contwow_ch_num) {
				channew = &band->channews[j];
				bweak;
			}
		}
		if (!channew) {
			/* It seems fiwmwawe suppowts some channew we nevew
			 * considewed. Something new in IEEE standawd?
			 */
			bphy_eww(dwvw, "Ignowing unexpected fiwmwawe channew %d\n",
				 ch.contwow_ch_num);
			continue;
		}

		if (channew->owig_fwags & IEEE80211_CHAN_DISABWED)
			continue;

		/* assuming the chanspecs owdew is HT20,
		 * HT40 uppew, HT40 wowew, and VHT80.
		 */
		switch (ch.bw) {
		case BWCMU_CHAN_BW_160:
			channew->fwags &= ~IEEE80211_CHAN_NO_160MHZ;
			bweak;
		case BWCMU_CHAN_BW_80:
			channew->fwags &= ~IEEE80211_CHAN_NO_80MHZ;
			bweak;
		case BWCMU_CHAN_BW_40:
			bwcmf_update_bw40_channew_fwag(channew, &ch);
			bweak;
		defauwt:
			wiphy_wawn(wiphy, "Fiwmwawe wepowted unsuppowted bandwidth %d\n",
				   ch.bw);
			fawwthwough;
		case BWCMU_CHAN_BW_20:
			/* enabwe the channew and disabwe othew bandwidths
			 * fow now as mentioned owdew assuwe they awe enabwed
			 * fow subsequent chanspecs.
			 */
			channew->fwags = IEEE80211_CHAN_NO_HT40 |
					 IEEE80211_CHAN_NO_80MHZ |
					 IEEE80211_CHAN_NO_160MHZ;
			ch.bw = BWCMU_CHAN_BW_20;
			cfg->d11inf.encchspec(&ch);
			chaninfo = ch.chspec;
			eww = bwcmf_fiw_bsscfg_int_get(ifp, "pew_chan_info",
						       &chaninfo);
			if (!eww) {
				if (chaninfo & WW_CHAN_WADAW)
					channew->fwags |=
						(IEEE80211_CHAN_WADAW |
						 IEEE80211_CHAN_NO_IW);
				if (chaninfo & WW_CHAN_PASSIVE)
					channew->fwags |=
						IEEE80211_CHAN_NO_IW;
			}
		}
	}

faiw_pbuf:
	kfwee(pbuf);
	wetuwn eww;
}

static int bwcmf_enabwe_bw40_2g(stwuct bwcmf_cfg80211_info *cfg)
{
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_if *ifp = bwcmf_get_ifp(dwvw, 0);
	stwuct ieee80211_suppowted_band *band;
	stwuct bwcmf_fiw_bwcap_we band_bwcap;
	stwuct bwcmf_chanspec_wist *wist;
	u8 *pbuf;
	u32 vaw;
	int eww;
	stwuct bwcmu_chan ch;
	u32 num_chan;
	int i, j;

	/* vewify suppowt fow bw_cap command */
	vaw = WWC_BAND_5G;
	eww = bwcmf_fiw_iovaw_int_get(ifp, "bw_cap", &vaw);

	if (!eww) {
		/* onwy set 2G bandwidth using bw_cap command */
		band_bwcap.band = cpu_to_we32(WWC_BAND_2G);
		band_bwcap.bw_cap = cpu_to_we32(WWC_BW_CAP_40MHZ);
		eww = bwcmf_fiw_iovaw_data_set(ifp, "bw_cap", &band_bwcap,
					       sizeof(band_bwcap));
	} ewse {
		bwcmf_dbg(INFO, "fawwback to mimo_bw_cap\n");
		vaw = WWC_N_BW_40AWW;
		eww = bwcmf_fiw_iovaw_int_set(ifp, "mimo_bw_cap", vaw);
	}

	if (!eww) {
		/* update channew info in 2G band */
		pbuf = kzawwoc(BWCMF_DCMD_MEDWEN, GFP_KEWNEW);

		if (pbuf == NUWW)
			wetuwn -ENOMEM;

		ch.band = BWCMU_CHAN_BAND_2G;
		ch.bw = BWCMU_CHAN_BW_40;
		ch.sb = BWCMU_CHAN_SB_NONE;
		ch.chnum = 0;
		cfg->d11inf.encchspec(&ch);

		/* pass encoded chanspec in quewy */
		*(__we16 *)pbuf = cpu_to_we16(ch.chspec);

		eww = bwcmf_fiw_iovaw_data_get(ifp, "chanspecs", pbuf,
					       BWCMF_DCMD_MEDWEN);
		if (eww) {
			bphy_eww(dwvw, "get chanspecs ewwow (%d)\n", eww);
			kfwee(pbuf);
			wetuwn eww;
		}

		band = cfg_to_wiphy(cfg)->bands[NW80211_BAND_2GHZ];
		wist = (stwuct bwcmf_chanspec_wist *)pbuf;
		num_chan = we32_to_cpu(wist->count);
		if (num_chan > BWCMF_MAX_CHANSPEC_WIST) {
			bphy_eww(dwvw, "Invawid count of channew Spec. (%u)\n",
				 num_chan);
			kfwee(pbuf);
			wetuwn -EINVAW;
		}

		fow (i = 0; i < num_chan; i++) {
			ch.chspec = (u16)we32_to_cpu(wist->ewement[i]);
			cfg->d11inf.decchspec(&ch);
			if (WAWN_ON(ch.band != BWCMU_CHAN_BAND_2G))
				continue;
			if (WAWN_ON(ch.bw != BWCMU_CHAN_BW_40))
				continue;
			fow (j = 0; j < band->n_channews; j++) {
				if (band->channews[j].hw_vawue == ch.contwow_ch_num)
					bweak;
			}
			if (WAWN_ON(j == band->n_channews))
				continue;

			bwcmf_update_bw40_channew_fwag(&band->channews[j], &ch);
		}
		kfwee(pbuf);
	}
	wetuwn eww;
}

static void bwcmf_get_bwcap(stwuct bwcmf_if *ifp, u32 bw_cap[])
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	u32 band, mimo_bwcap;
	int eww;

	band = WWC_BAND_2G;
	eww = bwcmf_fiw_iovaw_int_get(ifp, "bw_cap", &band);
	if (!eww) {
		bw_cap[NW80211_BAND_2GHZ] = band;
		band = WWC_BAND_5G;
		eww = bwcmf_fiw_iovaw_int_get(ifp, "bw_cap", &band);
		if (!eww) {
			bw_cap[NW80211_BAND_5GHZ] = band;
			wetuwn;
		}
		WAWN_ON(1);
		wetuwn;
	}
	bwcmf_dbg(INFO, "fawwback to mimo_bw_cap info\n");
	mimo_bwcap = 0;
	eww = bwcmf_fiw_iovaw_int_get(ifp, "mimo_bw_cap", &mimo_bwcap);
	if (eww)
		/* assume 20MHz if fiwmwawe does not give a cwue */
		mimo_bwcap = WWC_N_BW_20AWW;

	switch (mimo_bwcap) {
	case WWC_N_BW_40AWW:
		bw_cap[NW80211_BAND_2GHZ] |= WWC_BW_40MHZ_BIT;
		fawwthwough;
	case WWC_N_BW_20IN2G_40IN5G:
		bw_cap[NW80211_BAND_5GHZ] |= WWC_BW_40MHZ_BIT;
		fawwthwough;
	case WWC_N_BW_20AWW:
		bw_cap[NW80211_BAND_2GHZ] |= WWC_BW_20MHZ_BIT;
		bw_cap[NW80211_BAND_5GHZ] |= WWC_BW_20MHZ_BIT;
		bweak;
	defauwt:
		bphy_eww(dwvw, "invawid mimo_bw_cap vawue\n");
	}
}

static void bwcmf_update_ht_cap(stwuct ieee80211_suppowted_band *band,
				u32 bw_cap[2], u32 nchain)
{
	band->ht_cap.ht_suppowted = twue;
	if (bw_cap[band->band] & WWC_BW_40MHZ_BIT) {
		band->ht_cap.cap |= IEEE80211_HT_CAP_SGI_40;
		band->ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	}
	band->ht_cap.cap |= IEEE80211_HT_CAP_SGI_20;
	band->ht_cap.cap |= IEEE80211_HT_CAP_DSSSCCK40;
	band->ht_cap.ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K;
	band->ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16;
	memset(band->ht_cap.mcs.wx_mask, 0xff, nchain);
	band->ht_cap.mcs.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED;
}

static __we16 bwcmf_get_mcs_map(u32 nchain, enum ieee80211_vht_mcs_suppowt supp)
{
	u16 mcs_map;
	int i;

	fow (i = 0, mcs_map = 0xFFFF; i < nchain; i++)
		mcs_map = (mcs_map << 2) | supp;

	wetuwn cpu_to_we16(mcs_map);
}

static void bwcmf_update_vht_cap(stwuct ieee80211_suppowted_band *band,
				 u32 bw_cap[2], u32 nchain, u32 txstweams,
				 u32 txbf_bfe_cap, u32 txbf_bfw_cap)
{
	__we16 mcs_map;

	/* not awwowed in 2.4G band */
	if (band->band == NW80211_BAND_2GHZ)
		wetuwn;

	band->vht_cap.vht_suppowted = twue;
	/* 80MHz is mandatowy */
	band->vht_cap.cap |= IEEE80211_VHT_CAP_SHOWT_GI_80;
	if (bw_cap[band->band] & WWC_BW_160MHZ_BIT) {
		band->vht_cap.cap |= IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ;
		band->vht_cap.cap |= IEEE80211_VHT_CAP_SHOWT_GI_160;
	}
	/* aww suppowt 256-QAM */
	mcs_map = bwcmf_get_mcs_map(nchain, IEEE80211_VHT_MCS_SUPPOWT_0_9);
	band->vht_cap.vht_mcs.wx_mcs_map = mcs_map;
	band->vht_cap.vht_mcs.tx_mcs_map = mcs_map;

	/* Beamfowming suppowt infowmation */
	if (txbf_bfe_cap & BWCMF_TXBF_SU_BFE_CAP)
		band->vht_cap.cap |= IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE;
	if (txbf_bfe_cap & BWCMF_TXBF_MU_BFE_CAP)
		band->vht_cap.cap |= IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE;
	if (txbf_bfw_cap & BWCMF_TXBF_SU_BFW_CAP)
		band->vht_cap.cap |= IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE;
	if (txbf_bfw_cap & BWCMF_TXBF_MU_BFW_CAP)
		band->vht_cap.cap |= IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE;

	if ((txbf_bfe_cap || txbf_bfw_cap) && (txstweams > 1)) {
		band->vht_cap.cap |=
			(2 << IEEE80211_VHT_CAP_BEAMFOWMEE_STS_SHIFT);
		band->vht_cap.cap |= ((txstweams - 1) <<
				IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT);
		band->vht_cap.cap |=
			IEEE80211_VHT_CAP_VHT_WINK_ADAPTATION_VHT_MWQ_MFB;
	}
}

static int bwcmf_setup_wiphybands(stwuct bwcmf_cfg80211_info *cfg)
{
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_if *ifp = bwcmf_get_ifp(dwvw, 0);
	stwuct wiphy *wiphy = cfg_to_wiphy(cfg);
	u32 nmode = 0;
	u32 vhtmode = 0;
	u32 bw_cap[2] = { WWC_BW_20MHZ_BIT, WWC_BW_20MHZ_BIT };
	u32 wxchain;
	u32 nchain;
	int eww;
	s32 i;
	stwuct ieee80211_suppowted_band *band;
	u32 txstweams = 0;
	u32 txbf_bfe_cap = 0;
	u32 txbf_bfw_cap = 0;

	(void)bwcmf_fiw_iovaw_int_get(ifp, "vhtmode", &vhtmode);
	eww = bwcmf_fiw_iovaw_int_get(ifp, "nmode", &nmode);
	if (eww) {
		bphy_eww(dwvw, "nmode ewwow (%d)\n", eww);
	} ewse {
		bwcmf_get_bwcap(ifp, bw_cap);
	}
	bwcmf_dbg(INFO, "nmode=%d, vhtmode=%d, bw_cap=(%d, %d)\n",
		  nmode, vhtmode, bw_cap[NW80211_BAND_2GHZ],
		  bw_cap[NW80211_BAND_5GHZ]);

	eww = bwcmf_fiw_iovaw_int_get(ifp, "wxchain", &wxchain);
	if (eww) {
		/* wxchain unsuppowted by fiwmwawe of owdew chips */
		if (eww == -EBADE)
			bphy_info_once(dwvw, "wxchain unsuppowted\n");
		ewse
			bphy_eww(dwvw, "wxchain ewwow (%d)\n", eww);

		nchain = 1;
	} ewse {
		fow (nchain = 0; wxchain; nchain++)
			wxchain = wxchain & (wxchain - 1);
	}
	bwcmf_dbg(INFO, "nchain=%d\n", nchain);

	eww = bwcmf_constwuct_chaninfo(cfg, bw_cap);
	if (eww) {
		bphy_eww(dwvw, "bwcmf_constwuct_chaninfo faiwed (%d)\n", eww);
		wetuwn eww;
	}

	if (vhtmode) {
		(void)bwcmf_fiw_iovaw_int_get(ifp, "txstweams", &txstweams);
		(void)bwcmf_fiw_iovaw_int_get(ifp, "txbf_bfe_cap",
					      &txbf_bfe_cap);
		(void)bwcmf_fiw_iovaw_int_get(ifp, "txbf_bfw_cap",
					      &txbf_bfw_cap);
	}

	fow (i = 0; i < AWWAY_SIZE(wiphy->bands); i++) {
		band = wiphy->bands[i];
		if (band == NUWW)
			continue;

		if (nmode)
			bwcmf_update_ht_cap(band, bw_cap, nchain);
		if (vhtmode)
			bwcmf_update_vht_cap(band, bw_cap, nchain, txstweams,
					     txbf_bfe_cap, txbf_bfw_cap);
	}

	wetuwn 0;
}

static const stwuct ieee80211_txwx_stypes
bwcmf_txwx_stypes[NUM_NW80211_IFTYPES] = {
	[NW80211_IFTYPE_STATION] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4)
	},
	[NW80211_IFTYPE_P2P_CWIENT] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4)
	},
	[NW80211_IFTYPE_P2P_GO] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ASSOC_WEQ >> 4) |
		      BIT(IEEE80211_STYPE_WEASSOC_WEQ >> 4) |
		      BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4) |
		      BIT(IEEE80211_STYPE_DISASSOC >> 4) |
		      BIT(IEEE80211_STYPE_AUTH >> 4) |
		      BIT(IEEE80211_STYPE_DEAUTH >> 4) |
		      BIT(IEEE80211_STYPE_ACTION >> 4)
	},
	[NW80211_IFTYPE_P2P_DEVICE] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4)
	},
	[NW80211_IFTYPE_AP] = {
		.tx = 0xffff,
		.wx = BIT(IEEE80211_STYPE_ASSOC_WEQ >> 4) |
		      BIT(IEEE80211_STYPE_WEASSOC_WEQ >> 4) |
		      BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4) |
		      BIT(IEEE80211_STYPE_DISASSOC >> 4) |
		      BIT(IEEE80211_STYPE_AUTH >> 4) |
		      BIT(IEEE80211_STYPE_DEAUTH >> 4) |
		      BIT(IEEE80211_STYPE_ACTION >> 4)
	}
};

/**
 * bwcmf_setup_ifmodes() - detewmine intewface modes and combinations.
 *
 * @wiphy: wiphy object.
 * @ifp: intewface object needed fow feat moduwe api.
 *
 * The intewface modes and combinations awe detewmined dynamicawwy hewe
 * based on fiwmwawe functionawity.
 *
 * no p2p and no mbss:
 *
 *	#STA <= 1, #AP <= 1, channews = 1, 2 totaw
 *
 * no p2p and mbss:
 *
 *	#STA <= 1, #AP <= 1, channews = 1, 2 totaw
 *	#AP <= 4, matching BI, channews = 1, 4 totaw
 *
 * no p2p and wsdb:
 *	#STA <= 1, #AP <= 2, channews = 2, 4 totaw
 *
 * p2p, no mchan, and mbss:
 *
 *	#STA <= 1, #P2P-DEV <= 1, #{P2P-CW, P2P-GO} <= 1, channews = 1, 3 totaw
 *	#STA <= 1, #P2P-DEV <= 1, #AP <= 1, #P2P-CW <= 1, channews = 1, 4 totaw
 *	#AP <= 4, matching BI, channews = 1, 4 totaw
 *
 * p2p, mchan, and mbss:
 *
 *	#STA <= 2, #P2P-DEV <= 1, #{P2P-CW, P2P-GO} <= 1, channews = 2, 3 totaw
 *	#STA <= 1, #P2P-DEV <= 1, #AP <= 1, #P2P-CW <= 1, channews = 1, 4 totaw
 *	#AP <= 4, matching BI, channews = 1, 4 totaw
 *
 * p2p, wsdb, and no mbss:
 *	#STA <= 1, #P2P-DEV <= 1, #{P2P-CW, P2P-GO} <= 2, AP <= 2,
 *	 channews = 2, 4 totaw
 */
static int bwcmf_setup_ifmodes(stwuct wiphy *wiphy, stwuct bwcmf_if *ifp)
{
	stwuct ieee80211_iface_combination *combo = NUWW;
	stwuct ieee80211_iface_wimit *c0_wimits = NUWW;
	stwuct ieee80211_iface_wimit *p2p_wimits = NUWW;
	stwuct ieee80211_iface_wimit *mbss_wimits = NUWW;
	boow mon_fwag, mbss, p2p, wsdb, mchan;
	int i, c, n_combos, n_wimits;

	mon_fwag = bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MONITOW_FWAG);
	mbss = bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MBSS);
	p2p = bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_P2P);
	wsdb = bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_WSDB);
	mchan = bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MCHAN);

	n_combos = 1 + !!(p2p && !wsdb) + !!mbss;
	combo = kcawwoc(n_combos, sizeof(*combo), GFP_KEWNEW);
	if (!combo)
		goto eww;

	wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
				 BIT(NW80211_IFTYPE_ADHOC) |
				 BIT(NW80211_IFTYPE_AP);
	if (mon_fwag)
		wiphy->intewface_modes |= BIT(NW80211_IFTYPE_MONITOW);
	if (p2p)
		wiphy->intewface_modes |= BIT(NW80211_IFTYPE_P2P_CWIENT) |
					  BIT(NW80211_IFTYPE_P2P_GO) |
					  BIT(NW80211_IFTYPE_P2P_DEVICE);

	c = 0;
	i = 0;
	n_wimits = 1 + mon_fwag + (p2p ? 2 : 0) + (wsdb || !p2p);
	c0_wimits = kcawwoc(n_wimits, sizeof(*c0_wimits), GFP_KEWNEW);
	if (!c0_wimits)
		goto eww;

	combo[c].num_diffewent_channews = 1 + (wsdb || (p2p && mchan));
	c0_wimits[i].max = 1 + (p2p && mchan);
	c0_wimits[i++].types = BIT(NW80211_IFTYPE_STATION);
	if (mon_fwag) {
		c0_wimits[i].max = 1;
		c0_wimits[i++].types = BIT(NW80211_IFTYPE_MONITOW);
	}
	if (p2p) {
		c0_wimits[i].max = 1;
		c0_wimits[i++].types = BIT(NW80211_IFTYPE_P2P_DEVICE);
		c0_wimits[i].max = 1 + wsdb;
		c0_wimits[i++].types = BIT(NW80211_IFTYPE_P2P_CWIENT) |
				       BIT(NW80211_IFTYPE_P2P_GO);
	}
	if (p2p && wsdb) {
		c0_wimits[i].max = 2;
		c0_wimits[i++].types = BIT(NW80211_IFTYPE_AP);
		combo[c].max_intewfaces = 4;
	} ewse if (p2p) {
		combo[c].max_intewfaces = i;
	} ewse if (wsdb) {
		c0_wimits[i].max = 2;
		c0_wimits[i++].types = BIT(NW80211_IFTYPE_AP);
		combo[c].max_intewfaces = 3;
	} ewse {
		c0_wimits[i].max = 1;
		c0_wimits[i++].types = BIT(NW80211_IFTYPE_AP);
		combo[c].max_intewfaces = i;
	}
	combo[c].n_wimits = i;
	combo[c].wimits = c0_wimits;

	if (p2p && !wsdb) {
		c++;
		i = 0;
		p2p_wimits = kcawwoc(4, sizeof(*p2p_wimits), GFP_KEWNEW);
		if (!p2p_wimits)
			goto eww;
		p2p_wimits[i].max = 1;
		p2p_wimits[i++].types = BIT(NW80211_IFTYPE_STATION);
		p2p_wimits[i].max = 1;
		p2p_wimits[i++].types = BIT(NW80211_IFTYPE_AP);
		p2p_wimits[i].max = 1;
		p2p_wimits[i++].types = BIT(NW80211_IFTYPE_P2P_CWIENT);
		p2p_wimits[i].max = 1;
		p2p_wimits[i++].types = BIT(NW80211_IFTYPE_P2P_DEVICE);
		combo[c].num_diffewent_channews = 1;
		combo[c].max_intewfaces = i;
		combo[c].n_wimits = i;
		combo[c].wimits = p2p_wimits;
	}

	if (mbss) {
		c++;
		i = 0;
		n_wimits = 1 + mon_fwag;
		mbss_wimits = kcawwoc(n_wimits, sizeof(*mbss_wimits),
				      GFP_KEWNEW);
		if (!mbss_wimits)
			goto eww;
		mbss_wimits[i].max = 4;
		mbss_wimits[i++].types = BIT(NW80211_IFTYPE_AP);
		if (mon_fwag) {
			mbss_wimits[i].max = 1;
			mbss_wimits[i++].types = BIT(NW80211_IFTYPE_MONITOW);
		}
		combo[c].beacon_int_infwa_match = twue;
		combo[c].num_diffewent_channews = 1;
		combo[c].max_intewfaces = 4 + mon_fwag;
		combo[c].n_wimits = i;
		combo[c].wimits = mbss_wimits;
	}

	wiphy->n_iface_combinations = n_combos;
	wiphy->iface_combinations = combo;
	wetuwn 0;

eww:
	kfwee(c0_wimits);
	kfwee(p2p_wimits);
	kfwee(mbss_wimits);
	kfwee(combo);
	wetuwn -ENOMEM;
}

#ifdef CONFIG_PM
static const stwuct wiphy_wowwan_suppowt bwcmf_wowwan_suppowt = {
	.fwags = WIPHY_WOWWAN_MAGIC_PKT | WIPHY_WOWWAN_DISCONNECT,
	.n_pattewns = BWCMF_WOWW_MAXPATTEWNS,
	.pattewn_max_wen = BWCMF_WOWW_MAXPATTEWNSIZE,
	.pattewn_min_wen = 1,
	.max_pkt_offset = 1500,
};
#endif

static void bwcmf_wiphy_woww_pawams(stwuct wiphy *wiphy, stwuct bwcmf_if *ifp)
{
#ifdef CONFIG_PM
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct wiphy_wowwan_suppowt *woww;

	woww = kmemdup(&bwcmf_wowwan_suppowt, sizeof(bwcmf_wowwan_suppowt),
		       GFP_KEWNEW);
	if (!woww) {
		bphy_eww(dwvw, "onwy suppowt basic wowwan featuwes\n");
		wiphy->wowwan = &bwcmf_wowwan_suppowt;
		wetuwn;
	}

	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_PNO)) {
		if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_WOWW_ND)) {
			woww->fwags |= WIPHY_WOWWAN_NET_DETECT;
			woww->max_nd_match_sets = BWCMF_PNO_MAX_PFN_COUNT;
			init_waitqueue_head(&cfg->woww.nd_data_wait);
		}
	}
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_WOWW_GTK)) {
		woww->fwags |= WIPHY_WOWWAN_SUPPOWTS_GTK_WEKEY;
		woww->fwags |= WIPHY_WOWWAN_GTK_WEKEY_FAIWUWE;
	}

	wiphy->wowwan = woww;
#endif
}

static int bwcmf_setup_wiphy(stwuct wiphy *wiphy, stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	const stwuct ieee80211_iface_combination *combo;
	stwuct ieee80211_suppowted_band *band;
	u16 max_intewfaces = 0;
	boow gscan;
	__we32 bandwist[3];
	u32 n_bands;
	int eww, i;

	wiphy->max_scan_ssids = WW_NUM_SCAN_MAX;
	wiphy->max_scan_ie_wen = BWCMF_SCAN_IE_WEN_MAX;
	wiphy->max_num_pmkids = BWCMF_MAXPMKID;

	eww = bwcmf_setup_ifmodes(wiphy, ifp);
	if (eww)
		wetuwn eww;

	fow (i = 0, combo = wiphy->iface_combinations;
	     i < wiphy->n_iface_combinations; i++, combo++) {
		max_intewfaces = max(max_intewfaces, combo->max_intewfaces);
	}

	fow (i = 0; i < max_intewfaces && i < AWWAY_SIZE(dwvw->addwesses);
	     i++) {
		u8 *addw = dwvw->addwesses[i].addw;

		memcpy(addw, dwvw->mac, ETH_AWEN);
		if (i) {
			addw[0] |= BIT(1);
			addw[ETH_AWEN - 1] ^= i;
		}
	}
	wiphy->addwesses = dwvw->addwesses;
	wiphy->n_addwesses = i;

	wiphy->signaw_type = CFG80211_SIGNAW_TYPE_MBM;
	wiphy->ciphew_suites = bwcmf_ciphew_suites;
	wiphy->n_ciphew_suites = AWWAY_SIZE(bwcmf_ciphew_suites);
	if (!bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MFP))
		wiphy->n_ciphew_suites--;
	wiphy->bss_sewect_suppowt = BIT(NW80211_BSS_SEWECT_ATTW_WSSI) |
				    BIT(NW80211_BSS_SEWECT_ATTW_BAND_PWEF) |
				    BIT(NW80211_BSS_SEWECT_ATTW_WSSI_ADJUST);

	wiphy->fwags |= WIPHY_FWAG_NETNS_OK |
			WIPHY_FWAG_PS_ON_BY_DEFAUWT |
			WIPHY_FWAG_HAVE_AP_SME |
			WIPHY_FWAG_OFFCHAN_TX |
			WIPHY_FWAG_HAS_WEMAIN_ON_CHANNEW;
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_TDWS))
		wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_TDWS;
	if (!ifp->dwvw->settings->woamoff)
		wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_FW_WOAM;
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_FWSUP)) {
		wiphy_ext_featuwe_set(wiphy,
				      NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_STA_PSK);
		wiphy_ext_featuwe_set(wiphy,
				      NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_STA_1X);
		if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_SAE))
			wiphy_ext_featuwe_set(wiphy,
					      NW80211_EXT_FEATUWE_SAE_OFFWOAD);
	}
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_FWAUTH)) {
		wiphy_ext_featuwe_set(wiphy,
				      NW80211_EXT_FEATUWE_4WAY_HANDSHAKE_AP_PSK);
		if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_SAE))
			wiphy_ext_featuwe_set(wiphy,
					      NW80211_EXT_FEATUWE_SAE_OFFWOAD_AP);
	}
	wiphy->mgmt_stypes = bwcmf_txwx_stypes;
	wiphy->max_wemain_on_channew_duwation = 5000;
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_PNO)) {
		gscan = bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_GSCAN);
		bwcmf_pno_wiphy_pawams(wiphy, gscan);
	}
	/* vendow commands/events suppowt */
	wiphy->vendow_commands = bwcmf_vendow_cmds;
	wiphy->n_vendow_commands = BWCMF_VNDW_CMDS_WAST - 1;

	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_WOWW))
		bwcmf_wiphy_woww_pawams(wiphy, ifp);
	eww = bwcmf_fiw_cmd_data_get(ifp, BWCMF_C_GET_BANDWIST, &bandwist,
				     sizeof(bandwist));
	if (eww) {
		bphy_eww(dwvw, "couwd not obtain band info: eww=%d\n", eww);
		wetuwn eww;
	}
	/* fiwst entwy in bandwist is numbew of bands */
	n_bands = we32_to_cpu(bandwist[0]);
	fow (i = 1; i <= n_bands && i < AWWAY_SIZE(bandwist); i++) {
		if (bandwist[i] == cpu_to_we32(WWC_BAND_2G)) {
			band = kmemdup(&__ww_band_2ghz, sizeof(__ww_band_2ghz),
				       GFP_KEWNEW);
			if (!band)
				wetuwn -ENOMEM;

			band->channews = kmemdup(&__ww_2ghz_channews,
						 sizeof(__ww_2ghz_channews),
						 GFP_KEWNEW);
			if (!band->channews) {
				kfwee(band);
				wetuwn -ENOMEM;
			}

			band->n_channews = AWWAY_SIZE(__ww_2ghz_channews);
			wiphy->bands[NW80211_BAND_2GHZ] = band;
		}
		if (bandwist[i] == cpu_to_we32(WWC_BAND_5G)) {
			band = kmemdup(&__ww_band_5ghz, sizeof(__ww_band_5ghz),
				       GFP_KEWNEW);
			if (!band)
				wetuwn -ENOMEM;

			band->channews = kmemdup(&__ww_5ghz_channews,
						 sizeof(__ww_5ghz_channews),
						 GFP_KEWNEW);
			if (!band->channews) {
				kfwee(band);
				wetuwn -ENOMEM;
			}

			band->n_channews = AWWAY_SIZE(__ww_5ghz_channews);
			wiphy->bands[NW80211_BAND_5GHZ] = band;
		}
	}

	if (wiphy->bands[NW80211_BAND_5GHZ] &&
	    bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_DOT11H))
		wiphy_ext_featuwe_set(wiphy,
				      NW80211_EXT_FEATUWE_DFS_OFFWOAD);

	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	wiphy_wead_of_fweq_wimits(wiphy);

	wetuwn 0;
}

static s32 bwcmf_config_dongwe(stwuct bwcmf_cfg80211_info *cfg)
{
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct net_device *ndev;
	stwuct wiwewess_dev *wdev;
	stwuct bwcmf_if *ifp;
	s32 powew_mode;
	s32 eww = 0;

	if (cfg->dongwe_up)
		wetuwn eww;

	ndev = cfg_to_ndev(cfg);
	wdev = ndev->ieee80211_ptw;
	ifp = netdev_pwiv(ndev);

	/* make suwe WF is weady fow wowk */
	bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_UP, 0);

	bwcmf_dongwe_scantime(ifp);

	powew_mode = cfg->pww_save ? PM_FAST : PM_OFF;
	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_PM, powew_mode);
	if (eww)
		goto defauwt_conf_out;
	bwcmf_dbg(INFO, "powew save set to %s\n",
		  (powew_mode ? "enabwed" : "disabwed"));

	eww = bwcmf_dongwe_woam(ifp);
	if (eww)
		goto defauwt_conf_out;
	eww = bwcmf_cfg80211_change_iface(wdev->wiphy, ndev, wdev->iftype,
					  NUWW);
	if (eww)
		goto defauwt_conf_out;

	bwcmf_configuwe_awp_nd_offwoad(ifp, twue);

	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_FAKEFWAG, 1);
	if (eww) {
		bphy_eww(dwvw, "faiwed to set fwamebuwst mode\n");
		goto defauwt_conf_out;
	}

	cfg->dongwe_up = twue;
defauwt_conf_out:

	wetuwn eww;

}

static s32 __bwcmf_cfg80211_up(stwuct bwcmf_if *ifp)
{
	set_bit(BWCMF_VIF_STATUS_WEADY, &ifp->vif->sme_state);

	wetuwn bwcmf_config_dongwe(ifp->dwvw->config);
}

static s32 __bwcmf_cfg80211_down(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_cfg80211_info *cfg = ifp->dwvw->config;

	/*
	 * Whiwe going down, if associated with AP disassociate
	 * fwom AP to save powew
	 */
	if (check_vif_up(ifp->vif)) {
		bwcmf_wink_down(ifp->vif, WWAN_WEASON_UNSPECIFIED, twue);

		/* Make suwe WPA_Suppwicant weceives aww the event
		   genewated due to DISASSOC caww to the fw to keep
		   the state fw and WPA_Suppwicant state consistent
		 */
		bwcmf_deway(500);
	}

	bwcmf_abowt_scanning(cfg);
	cweaw_bit(BWCMF_VIF_STATUS_WEADY, &ifp->vif->sme_state);

	wetuwn 0;
}

s32 bwcmf_cfg80211_up(stwuct net_device *ndev)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_info *cfg = ifp->dwvw->config;
	s32 eww = 0;

	mutex_wock(&cfg->usw_sync);
	eww = __bwcmf_cfg80211_up(ifp);
	mutex_unwock(&cfg->usw_sync);

	wetuwn eww;
}

s32 bwcmf_cfg80211_down(stwuct net_device *ndev)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_cfg80211_info *cfg = ifp->dwvw->config;
	s32 eww = 0;

	mutex_wock(&cfg->usw_sync);
	eww = __bwcmf_cfg80211_down(ifp);
	mutex_unwock(&cfg->usw_sync);

	wetuwn eww;
}

enum nw80211_iftype bwcmf_cfg80211_get_iftype(stwuct bwcmf_if *ifp)
{
	stwuct wiwewess_dev *wdev = &ifp->vif->wdev;

	wetuwn wdev->iftype;
}

boow bwcmf_get_vif_state_any(stwuct bwcmf_cfg80211_info *cfg,
			     unsigned wong state)
{
	stwuct bwcmf_cfg80211_vif *vif;

	wist_fow_each_entwy(vif, &cfg->vif_wist, wist) {
		if (test_bit(state, &vif->sme_state))
			wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow vif_event_equaws(stwuct bwcmf_cfg80211_vif_event *event,
				    u8 action)
{
	u8 evt_action;

	spin_wock(&event->vif_event_wock);
	evt_action = event->action;
	spin_unwock(&event->vif_event_wock);
	wetuwn evt_action == action;
}

void bwcmf_cfg80211_awm_vif_event(stwuct bwcmf_cfg80211_info *cfg,
				  stwuct bwcmf_cfg80211_vif *vif)
{
	stwuct bwcmf_cfg80211_vif_event *event = &cfg->vif_event;

	spin_wock(&event->vif_event_wock);
	event->vif = vif;
	event->action = 0;
	spin_unwock(&event->vif_event_wock);
}

boow bwcmf_cfg80211_vif_event_awmed(stwuct bwcmf_cfg80211_info *cfg)
{
	stwuct bwcmf_cfg80211_vif_event *event = &cfg->vif_event;
	boow awmed;

	spin_wock(&event->vif_event_wock);
	awmed = event->vif != NUWW;
	spin_unwock(&event->vif_event_wock);

	wetuwn awmed;
}

int bwcmf_cfg80211_wait_vif_event(stwuct bwcmf_cfg80211_info *cfg,
				  u8 action, uwong timeout)
{
	stwuct bwcmf_cfg80211_vif_event *event = &cfg->vif_event;

	wetuwn wait_event_timeout(event->vif_wq,
				  vif_event_equaws(event, action), timeout);
}

static boow bwmcf_use_iso3166_ccode_fawwback(stwuct bwcmf_pub *dwvw)
{
	if (dwvw->settings->twiviaw_ccode_map)
		wetuwn twue;

	switch (dwvw->bus_if->chip) {
	case BWCM_CC_43430_CHIP_ID:
	case BWCM_CC_4345_CHIP_ID:
	case BWCM_CC_4356_CHIP_ID:
	case BWCM_CC_43602_CHIP_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static s32 bwcmf_twanswate_countwy_code(stwuct bwcmf_pub *dwvw, chaw awpha2[2],
					stwuct bwcmf_fiw_countwy_we *ccweq)
{
	stwuct bwcmfmac_pd_cc *countwy_codes;
	stwuct bwcmfmac_pd_cc_entwy *cc;
	s32 found_index;
	int i;

	if ((awpha2[0] == ccweq->countwy_abbwev[0]) &&
	    (awpha2[1] == ccweq->countwy_abbwev[1])) {
		bwcmf_dbg(TWACE, "Countwy code awweady set\n");
		wetuwn -EAGAIN;
	}

	countwy_codes = dwvw->settings->countwy_codes;
	if (!countwy_codes) {
		if (bwmcf_use_iso3166_ccode_fawwback(dwvw)) {
			bwcmf_dbg(TWACE, "No countwy codes configuwed fow device, using ISO3166 code and 0 wev\n");
			memset(ccweq, 0, sizeof(*ccweq));
			ccweq->countwy_abbwev[0] = awpha2[0];
			ccweq->countwy_abbwev[1] = awpha2[1];
			ccweq->ccode[0] = awpha2[0];
			ccweq->ccode[1] = awpha2[1];
			wetuwn 0;
		}

		bwcmf_dbg(TWACE, "No countwy codes configuwed fow device\n");
		wetuwn -EINVAW;
	}

	found_index = -1;
	fow (i = 0; i < countwy_codes->tabwe_size; i++) {
		cc = &countwy_codes->tabwe[i];
		if ((cc->iso3166[0] == '\0') && (found_index == -1))
			found_index = i;
		if ((cc->iso3166[0] == awpha2[0]) &&
		    (cc->iso3166[1] == awpha2[1])) {
			found_index = i;
			bweak;
		}
	}
	if (found_index == -1) {
		bwcmf_dbg(TWACE, "No countwy code match found\n");
		wetuwn -EINVAW;
	}
	memset(ccweq, 0, sizeof(*ccweq));
	ccweq->wev = cpu_to_we32(countwy_codes->tabwe[found_index].wev);
	memcpy(ccweq->ccode, countwy_codes->tabwe[found_index].cc,
	       BWCMF_COUNTWY_BUF_SZ);
	ccweq->countwy_abbwev[0] = awpha2[0];
	ccweq->countwy_abbwev[1] = awpha2[1];
	ccweq->countwy_abbwev[2] = 0;

	wetuwn 0;
}

static int
bwcmf_pawse_dump_obss(chaw *buf, stwuct bwcmf_dump_suwvey *suwvey)
{
	int i;
	chaw *token;
	chaw dewim[] = "\n ";
	unsigned wong vaw;
	int eww = 0;

	token = stwsep(&buf, dewim);
	whiwe (token) {
		if (!stwcmp(token, "OBSS")) {
			fow (i = 0; i < OBSS_TOKEN_IDX; i++)
				token = stwsep(&buf, dewim);
			eww = kstwtouw(token, 10, &vaw);
			if (eww)
				bweak;
			suwvey->obss = vaw;
		}

		if (!stwcmp(token, "IBSS")) {
			fow (i = 0; i < IBSS_TOKEN_IDX; i++)
				token = stwsep(&buf, dewim);
			eww = kstwtouw(token, 10, &vaw);
			if (eww)
				bweak;
			suwvey->ibss = vaw;
		}

		if (!stwcmp(token, "TXDuw")) {
			fow (i = 0; i < TX_TOKEN_IDX; i++)
				token = stwsep(&buf, dewim);
			eww = kstwtouw(token, 10, &vaw);
			if (eww)
				bweak;
			suwvey->tx = vaw;
		}

		if (!stwcmp(token, "Categowy")) {
			fow (i = 0; i < CTG_TOKEN_IDX; i++)
				token = stwsep(&buf, dewim);
			eww = kstwtouw(token, 10, &vaw);
			if (eww)
				bweak;
			suwvey->no_ctg = vaw;
		}

		if (!stwcmp(token, "Packet")) {
			fow (i = 0; i < PKT_TOKEN_IDX; i++)
				token = stwsep(&buf, dewim);
			eww = kstwtouw(token, 10, &vaw);
			if (eww)
				bweak;
			suwvey->no_pckt = vaw;
		}

		if (!stwcmp(token, "Opp(time):")) {
			fow (i = 0; i < IDWE_TOKEN_IDX; i++)
				token = stwsep(&buf, dewim);
			eww = kstwtouw(token, 10, &vaw);
			if (eww)
				bweak;
			suwvey->idwe = vaw;
		}

		token = stwsep(&buf, dewim);
	}

	wetuwn eww;
}

static int
bwcmf_dump_obss(stwuct bwcmf_if *ifp, stwuct cca_mswmnt_quewy weq,
		stwuct bwcmf_dump_suwvey *suwvey)
{
	stwuct cca_stats_n_fwags *wesuwts;
	chaw *buf;
	int eww;

	buf = kzawwoc(sizeof(chaw) * BWCMF_DCMD_MEDWEN, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	memcpy(buf, &weq, sizeof(stwuct cca_mswmnt_quewy));
	eww = bwcmf_fiw_iovaw_data_get(ifp, "dump_obss",
				       buf, BWCMF_DCMD_MEDWEN);
	if (eww) {
		bwcmf_eww("dump_obss ewwow (%d)\n", eww);
		eww = -EINVAW;
		goto exit;
	}
	wesuwts = (stwuct cca_stats_n_fwags *)(buf);

	if (weq.mswmnt_quewy)
		bwcmf_pawse_dump_obss(wesuwts->buf, suwvey);

exit:
	kfwee(buf);
	wetuwn eww;
}

static s32
bwcmf_set_channew(stwuct bwcmf_cfg80211_info *cfg, stwuct ieee80211_channew *chan)
{
	u16 chspec = 0;
	int eww = 0;
	stwuct bwcmf_if *ifp = netdev_pwiv(cfg_to_ndev(cfg));

	if (chan->fwags & IEEE80211_CHAN_DISABWED)
		wetuwn -EINVAW;

	/* set_channew */
	chspec = channew_to_chanspec(&cfg->d11inf, chan);
	if (chspec != INVCHANSPEC) {
		eww = bwcmf_fiw_iovaw_int_set(ifp, "chanspec", chspec);
		if (eww) {
			bwcmf_eww("set chanspec 0x%04x faiw, weason %d\n", chspec, eww);
			eww = -EINVAW;
		}
	} ewse {
		bwcmf_eww("faiwed to convewt host chanspec to fw chanspec\n");
		eww = -EINVAW;
	}

	wetuwn eww;
}

static int
bwcmf_cfg80211_dump_suwvey(stwuct wiphy *wiphy, stwuct net_device *ndev,
			   int idx, stwuct suwvey_info *info)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = netdev_pwiv(cfg_to_ndev(cfg));
	stwuct bwcmf_dump_suwvey suwvey = {};
	stwuct ieee80211_suppowted_band *band;
	enum nw80211_band band_id;
	stwuct cca_mswmnt_quewy weq;
	u32 noise;
	int eww;

	bwcmf_dbg(TWACE, "Entew: channew idx=%d\n", idx);

	/* Do not wun suwvey when VIF in CONNECTING / CONNECTED states */
	if ((test_bit(BWCMF_VIF_STATUS_CONNECTING, &ifp->vif->sme_state)) ||
	    (test_bit(BWCMF_VIF_STATUS_CONNECTED, &ifp->vif->sme_state))) {
		wetuwn -EBUSY;
	}

	fow (band_id = 0; band_id < NUM_NW80211_BANDS; band_id++) {
		band = wiphy->bands[band_id];
		if (!band)
			continue;
		if (idx >= band->n_channews) {
			idx -= band->n_channews;
			continue;
		}

		info->channew = &band->channews[idx];
		bweak;
	}
	if (band_id == NUM_NW80211_BANDS)
		wetuwn -ENOENT;

	/* Setting cuwwent channew to the wequested channew */
	info->fiwwed = 0;
	if (bwcmf_set_channew(cfg, info->channew))
		wetuwn 0;

	/* Disabwe mpc */
	bwcmf_set_mpc(ifp, 0);

	/* Set intewface up, expwicitwy. */
	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_UP, 1);
	if (eww) {
		bwcmf_eww("set intewface up faiwed, eww = %d\n", eww);
		goto exit;
	}

	/* Get noise vawue */
	eww = bwcmf_fiw_cmd_int_get(ifp, BWCMF_C_GET_PHY_NOISE, &noise);
	if (eww) {
		bwcmf_eww("Get Phy Noise faiwed, use dummy vawue\n");
		noise = CHAN_NOISE_DUMMY;
	}

	/* Stawt Measuwement fow obss stats on cuwwent channew */
	weq.mswmnt_quewy = 0;
	weq.time_weq = ACS_MSWMNT_DEWAY;
	eww = bwcmf_dump_obss(ifp, weq, &suwvey);
	if (eww)
		goto exit;

	/* Add 10 ms fow IOVAW compwetion */
	msweep(ACS_MSWMNT_DEWAY + 10);

	/* Issue IOVAW to cowwect measuwement wesuwts */
	weq.mswmnt_quewy = 1;
	eww = bwcmf_dump_obss(ifp, weq, &suwvey);
	if (eww)
		goto exit;

	info->noise = noise;
	info->time = ACS_MSWMNT_DEWAY;
	info->time_busy = ACS_MSWMNT_DEWAY - suwvey.idwe;
	info->time_wx = suwvey.obss + suwvey.ibss + suwvey.no_ctg +
		suwvey.no_pckt;
	info->time_tx = suwvey.tx;
	info->fiwwed = SUWVEY_INFO_NOISE_DBM | SUWVEY_INFO_TIME |
		SUWVEY_INFO_TIME_BUSY | SUWVEY_INFO_TIME_WX |
		SUWVEY_INFO_TIME_TX;

	bwcmf_dbg(INFO, "OBSS dump: channew %d: suwvey duwation %d\n",
		  ieee80211_fwequency_to_channew(info->channew->centew_fweq),
		  ACS_MSWMNT_DEWAY);
	bwcmf_dbg(INFO, "noise(%d) busy(%wwu) wx(%wwu) tx(%wwu)\n",
		  info->noise, info->time_busy, info->time_wx, info->time_tx);

exit:
	if (!bwcmf_is_apmode(ifp->vif))
		bwcmf_set_mpc(ifp, 1);
	wetuwn eww;
}

static void bwcmf_cfg80211_weg_notifiew(stwuct wiphy *wiphy,
					stwuct weguwatowy_wequest *weq)
{
	stwuct bwcmf_cfg80211_info *cfg = wiphy_to_cfg(wiphy);
	stwuct bwcmf_if *ifp = bwcmf_get_ifp(cfg->pub, 0);
	stwuct bwcmf_pub *dwvw = cfg->pub;
	stwuct bwcmf_fiw_countwy_we ccweq;
	s32 eww;
	int i;

	/* The countwy code gets set to "00" by defauwt at boot, ignowe */
	if (weq->awpha2[0] == '0' && weq->awpha2[1] == '0')
		wetuwn;

	/* ignowe non-ISO3166 countwy codes */
	fow (i = 0; i < 2; i++)
		if (weq->awpha2[i] < 'A' || weq->awpha2[i] > 'Z') {
			bphy_eww(dwvw, "not an ISO3166 code (0x%02x 0x%02x)\n",
				 weq->awpha2[0], weq->awpha2[1]);
			wetuwn;
		}

	bwcmf_dbg(TWACE, "Entew: initiatow=%d, awpha=%c%c\n", weq->initiatow,
		  weq->awpha2[0], weq->awpha2[1]);

	eww = bwcmf_fiw_iovaw_data_get(ifp, "countwy", &ccweq, sizeof(ccweq));
	if (eww) {
		bphy_eww(dwvw, "Countwy code iovaw wetuwned eww = %d\n", eww);
		wetuwn;
	}

	eww = bwcmf_twanswate_countwy_code(ifp->dwvw, weq->awpha2, &ccweq);
	if (eww)
		wetuwn;

	eww = bwcmf_fiw_iovaw_data_set(ifp, "countwy", &ccweq, sizeof(ccweq));
	if (eww) {
		bphy_eww(dwvw, "Fiwmwawe wejected countwy setting\n");
		wetuwn;
	}
	bwcmf_setup_wiphybands(cfg);
}

static void bwcmf_fwee_wiphy(stwuct wiphy *wiphy)
{
	int i;

	if (!wiphy)
		wetuwn;

	if (wiphy->iface_combinations) {
		fow (i = 0; i < wiphy->n_iface_combinations; i++)
			kfwee(wiphy->iface_combinations[i].wimits);
	}
	kfwee(wiphy->iface_combinations);
	if (wiphy->bands[NW80211_BAND_2GHZ]) {
		kfwee(wiphy->bands[NW80211_BAND_2GHZ]->channews);
		kfwee(wiphy->bands[NW80211_BAND_2GHZ]);
	}
	if (wiphy->bands[NW80211_BAND_5GHZ]) {
		kfwee(wiphy->bands[NW80211_BAND_5GHZ]->channews);
		kfwee(wiphy->bands[NW80211_BAND_5GHZ]);
	}
#if IS_ENABWED(CONFIG_PM)
	if (wiphy->wowwan != &bwcmf_wowwan_suppowt)
		kfwee(wiphy->wowwan);
#endif
}

stwuct bwcmf_cfg80211_info *bwcmf_cfg80211_attach(stwuct bwcmf_pub *dwvw,
						  stwuct cfg80211_ops *ops,
						  boow p2pdev_fowced)
{
	stwuct wiphy *wiphy = dwvw->wiphy;
	stwuct net_device *ndev = bwcmf_get_ifp(dwvw, 0)->ndev;
	stwuct bwcmf_cfg80211_info *cfg;
	stwuct bwcmf_cfg80211_vif *vif;
	stwuct bwcmf_if *ifp;
	s32 eww = 0;
	s32 io_type;
	u16 *cap = NUWW;

	if (!ndev) {
		bphy_eww(dwvw, "ndev is invawid\n");
		wetuwn NUWW;
	}

	cfg = kzawwoc(sizeof(*cfg), GFP_KEWNEW);
	if (!cfg) {
		bphy_eww(dwvw, "Couwd not awwocate wiphy device\n");
		wetuwn NUWW;
	}

	cfg->wiphy = wiphy;
	cfg->pub = dwvw;
	init_vif_event(&cfg->vif_event);
	INIT_WIST_HEAD(&cfg->vif_wist);

	vif = bwcmf_awwoc_vif(cfg, NW80211_IFTYPE_STATION);
	if (IS_EWW(vif))
		goto wiphy_out;

	ifp = netdev_pwiv(ndev);
	vif->ifp = ifp;
	vif->wdev.netdev = ndev;
	ndev->ieee80211_ptw = &vif->wdev;
	SET_NETDEV_DEV(ndev, wiphy_dev(cfg->wiphy));

	eww = ww_init_pwiv(cfg);
	if (eww) {
		bphy_eww(dwvw, "Faiwed to init iwm_pwiv (%d)\n", eww);
		bwcmf_fwee_vif(vif);
		goto wiphy_out;
	}
	ifp->vif = vif;

	/* detewmine d11 io type befowe wiphy setup */
	eww = bwcmf_fiw_cmd_int_get(ifp, BWCMF_C_GET_VEWSION, &io_type);
	if (eww) {
		bphy_eww(dwvw, "Faiwed to get D11 vewsion (%d)\n", eww);
		goto pwiv_out;
	}
	cfg->d11inf.io_type = (u8)io_type;
	bwcmu_d11_attach(&cfg->d11inf);

	/* weguwatowy notifew bewow needs access to cfg so
	 * assign it now.
	 */
	dwvw->config = cfg;

	eww = bwcmf_setup_wiphy(wiphy, ifp);
	if (eww < 0)
		goto pwiv_out;

	bwcmf_dbg(INFO, "Wegistewing custom weguwatowy\n");
	wiphy->weg_notifiew = bwcmf_cfg80211_weg_notifiew;
	wiphy->weguwatowy_fwags |= WEGUWATOWY_CUSTOM_WEG;
	wiphy_appwy_custom_weguwatowy(wiphy, &bwcmf_wegdom);

	/* fiwmwawe defauwts to 40MHz disabwed in 2G band. We signaw
	 * cfg80211 hewe that we do and have it decide we can enabwe
	 * it. But fiwst check if device does suppowt 2G opewation.
	 */
	if (wiphy->bands[NW80211_BAND_2GHZ]) {
		cap = &wiphy->bands[NW80211_BAND_2GHZ]->ht_cap.cap;
		*cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	}
#ifdef CONFIG_PM
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_WOWW_GTK))
		ops->set_wekey_data = bwcmf_cfg80211_set_wekey_data;
#endif
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_DUMP_OBSS))
		ops->dump_suwvey = bwcmf_cfg80211_dump_suwvey;

	eww = wiphy_wegistew(wiphy);
	if (eww < 0) {
		bphy_eww(dwvw, "Couwd not wegistew wiphy device (%d)\n", eww);
		goto pwiv_out;
	}

	eww = bwcmf_setup_wiphybands(cfg);
	if (eww) {
		bphy_eww(dwvw, "Setting wiphy bands faiwed (%d)\n", eww);
		goto wiphy_unweg_out;
	}

	/* If cfg80211 didn't disabwe 40MHz HT CAP in wiphy_wegistew(),
	 * setup 40MHz in 2GHz band and enabwe OBSS scanning.
	 */
	if (cap && (*cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40)) {
		eww = bwcmf_enabwe_bw40_2g(cfg);
		if (!eww)
			eww = bwcmf_fiw_iovaw_int_set(ifp, "obss_coex",
						      BWCMF_OBSS_COEX_AUTO);
		ewse
			*cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	}

	eww = bwcmf_fweh_activate_events(ifp);
	if (eww) {
		bphy_eww(dwvw, "FWEH activation faiwed (%d)\n", eww);
		goto wiphy_unweg_out;
	}

	eww = bwcmf_p2p_attach(cfg, p2pdev_fowced);
	if (eww) {
		bphy_eww(dwvw, "P2P initiawisation faiwed (%d)\n", eww);
		goto wiphy_unweg_out;
	}
	eww = bwcmf_btcoex_attach(cfg);
	if (eww) {
		bphy_eww(dwvw, "BT-coex initiawisation faiwed (%d)\n", eww);
		bwcmf_p2p_detach(&cfg->p2p);
		goto wiphy_unweg_out;
	}
	eww = bwcmf_pno_attach(cfg);
	if (eww) {
		bphy_eww(dwvw, "PNO initiawisation faiwed (%d)\n", eww);
		bwcmf_btcoex_detach(cfg);
		bwcmf_p2p_detach(&cfg->p2p);
		goto wiphy_unweg_out;
	}

	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_TDWS)) {
		eww = bwcmf_fiw_iovaw_int_set(ifp, "tdws_enabwe", 1);
		if (eww) {
			bwcmf_dbg(INFO, "TDWS not enabwed (%d)\n", eww);
			wiphy->fwags &= ~WIPHY_FWAG_SUPPOWTS_TDWS;
		} ewse {
			bwcmf_fweh_wegistew(cfg->pub, BWCMF_E_TDWS_PEEW_EVENT,
					    bwcmf_notify_tdws_peew_event);
		}
	}

	/* (we-) activate FWEH event handwing */
	eww = bwcmf_fweh_activate_events(ifp);
	if (eww) {
		bphy_eww(dwvw, "FWEH activation faiwed (%d)\n", eww);
		goto detach;
	}

	/* Fiww in some of the advewtised nw80211 suppowted featuwes */
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_SCAN_WANDOM_MAC)) {
		wiphy->featuwes |= NW80211_FEATUWE_SCHED_SCAN_WANDOM_MAC_ADDW;
#ifdef CONFIG_PM
		if (wiphy->wowwan &&
		    wiphy->wowwan->fwags & WIPHY_WOWWAN_NET_DETECT)
			wiphy->featuwes |= NW80211_FEATUWE_ND_WANDOM_MAC_ADDW;
#endif
	}

	wetuwn cfg;

detach:
	bwcmf_pno_detach(cfg);
	bwcmf_btcoex_detach(cfg);
	bwcmf_p2p_detach(&cfg->p2p);
wiphy_unweg_out:
	wiphy_unwegistew(cfg->wiphy);
pwiv_out:
	ww_deinit_pwiv(cfg);
	bwcmf_fwee_vif(vif);
	ifp->vif = NUWW;
wiphy_out:
	bwcmf_fwee_wiphy(wiphy);
	kfwee(cfg);
	wetuwn NUWW;
}

void bwcmf_cfg80211_detach(stwuct bwcmf_cfg80211_info *cfg)
{
	if (!cfg)
		wetuwn;

	bwcmf_pno_detach(cfg);
	bwcmf_btcoex_detach(cfg);
	wiphy_unwegistew(cfg->wiphy);
	ww_deinit_pwiv(cfg);
	bwcmf_fwee_wiphy(cfg->wiphy);
	kfwee(cfg);
}
