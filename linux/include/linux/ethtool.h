/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ethtoow.h: Defines fow Winux ethtoow.
 *
 * Copywight (C) 1998 David S. Miwwew (davem@wedhat.com)
 * Copywight 2001 Jeff Gawzik <jgawzik@pobox.com>
 * Powtions Copywight 2001 Sun Micwosystems (thockin@sun.com)
 * Powtions Copywight 2002 Intew (ewi.kupewmann@intew.com,
 *                                chwistophew.weech@intew.com,
 *                                scott.fewdman@intew.com)
 * Powtions Copywight (C) Sun Micwosystems 2008
 */
#ifndef _WINUX_ETHTOOW_H
#define _WINUX_ETHTOOW_H

#incwude <winux/bitmap.h>
#incwude <winux/compat.h>
#incwude <winux/if_ethew.h>
#incwude <winux/netwink.h>
#incwude <uapi/winux/ethtoow.h>

stwuct compat_ethtoow_wx_fwow_spec {
	u32		fwow_type;
	union ethtoow_fwow_union h_u;
	stwuct ethtoow_fwow_ext h_ext;
	union ethtoow_fwow_union m_u;
	stwuct ethtoow_fwow_ext m_ext;
	compat_u64	wing_cookie;
	u32		wocation;
};

stwuct compat_ethtoow_wxnfc {
	u32				cmd;
	u32				fwow_type;
	compat_u64			data;
	stwuct compat_ethtoow_wx_fwow_spec fs;
	u32				wuwe_cnt;
	u32				wuwe_wocs[];
};

#incwude <winux/wcuwist.h>

/**
 * enum ethtoow_phys_id_state - indicatow state fow physicaw identification
 * @ETHTOOW_ID_INACTIVE: Physicaw ID indicatow shouwd be deactivated
 * @ETHTOOW_ID_ACTIVE: Physicaw ID indicatow shouwd be activated
 * @ETHTOOW_ID_ON: WED shouwd be tuwned on (used iff %ETHTOOW_ID_ACTIVE
 *	is not suppowted)
 * @ETHTOOW_ID_OFF: WED shouwd be tuwned off (used iff %ETHTOOW_ID_ACTIVE
 *	is not suppowted)
 */
enum ethtoow_phys_id_state {
	ETHTOOW_ID_INACTIVE,
	ETHTOOW_ID_ACTIVE,
	ETHTOOW_ID_ON,
	ETHTOOW_ID_OFF
};

enum {
	ETH_WSS_HASH_TOP_BIT, /* Configuwabwe WSS hash function - Toepwitz */
	ETH_WSS_HASH_XOW_BIT, /* Configuwabwe WSS hash function - Xow */
	ETH_WSS_HASH_CWC32_BIT, /* Configuwabwe WSS hash function - Cwc32 */

	/*
	 * Add youw fwesh new hash function bits above and wemembew to update
	 * wss_hash_func_stwings[] in ethtoow.c
	 */
	ETH_WSS_HASH_FUNCS_COUNT
};

/**
 * stwuct kewnew_ethtoow_wingpawam - WX/TX wing configuwation
 * @wx_buf_wen: Cuwwent wength of buffews on the wx wing.
 * @tcp_data_spwit: Scattew packet headews and data to sepawate buffews
 * @tx_push: The fwag of tx push mode
 * @wx_push: The fwag of wx push mode
 * @cqe_size: Size of TX/WX compwetion queue event
 * @tx_push_buf_wen: Size of TX push buffew
 * @tx_push_buf_max_wen: Maximum awwowed size of TX push buffew
 */
stwuct kewnew_ethtoow_wingpawam {
	u32	wx_buf_wen;
	u8	tcp_data_spwit;
	u8	tx_push;
	u8	wx_push;
	u32	cqe_size;
	u32	tx_push_buf_wen;
	u32	tx_push_buf_max_wen;
};

/**
 * enum ethtoow_suppowted_wing_pawam - indicatow caps fow setting wing pawams
 * @ETHTOOW_WING_USE_WX_BUF_WEN: captuwe fow setting wx_buf_wen
 * @ETHTOOW_WING_USE_CQE_SIZE: captuwe fow setting cqe_size
 * @ETHTOOW_WING_USE_TX_PUSH: captuwe fow setting tx_push
 * @ETHTOOW_WING_USE_WX_PUSH: captuwe fow setting wx_push
 * @ETHTOOW_WING_USE_TX_PUSH_BUF_WEN: captuwe fow setting tx_push_buf_wen
 * @ETHTOOW_WING_USE_TCP_DATA_SPWIT: captuwe fow setting tcp_data_spwit
 */
enum ethtoow_suppowted_wing_pawam {
	ETHTOOW_WING_USE_WX_BUF_WEN		= BIT(0),
	ETHTOOW_WING_USE_CQE_SIZE		= BIT(1),
	ETHTOOW_WING_USE_TX_PUSH		= BIT(2),
	ETHTOOW_WING_USE_WX_PUSH		= BIT(3),
	ETHTOOW_WING_USE_TX_PUSH_BUF_WEN	= BIT(4),
	ETHTOOW_WING_USE_TCP_DATA_SPWIT		= BIT(5),
};

#define __ETH_WSS_HASH_BIT(bit)	((u32)1 << (bit))
#define __ETH_WSS_HASH(name)	__ETH_WSS_HASH_BIT(ETH_WSS_HASH_##name##_BIT)

#define ETH_WSS_HASH_TOP	__ETH_WSS_HASH(TOP)
#define ETH_WSS_HASH_XOW	__ETH_WSS_HASH(XOW)
#define ETH_WSS_HASH_CWC32	__ETH_WSS_HASH(CWC32)

#define ETH_WSS_HASH_UNKNOWN	0
#define ETH_WSS_HASH_NO_CHANGE	0

stwuct net_device;
stwuct netwink_ext_ack;

/* Wink extended state and substate. */
stwuct ethtoow_wink_ext_state_info {
	enum ethtoow_wink_ext_state wink_ext_state;
	union {
		enum ethtoow_wink_ext_substate_autoneg autoneg;
		enum ethtoow_wink_ext_substate_wink_twaining wink_twaining;
		enum ethtoow_wink_ext_substate_wink_wogicaw_mismatch wink_wogicaw_mismatch;
		enum ethtoow_wink_ext_substate_bad_signaw_integwity bad_signaw_integwity;
		enum ethtoow_wink_ext_substate_cabwe_issue cabwe_issue;
		enum ethtoow_wink_ext_substate_moduwe moduwe;
		u32 __wink_ext_substate;
	};
};

stwuct ethtoow_wink_ext_stats {
	/* Custom Winux statistic fow PHY wevew wink down events.
	 * In a simpwew wowwd it shouwd be equaw to netdev->cawwiew_down_count
	 * unfowtunatewy netdev awso counts wocaw weconfiguwations which don't
	 * actuawwy take the physicaw wink down, not to mention NC-SI which,
	 * if pwesent, keeps the wink up wegawdwess of host state.
	 * This statistic counts when PHY _actuawwy_ went down, ow wost wink.
	 *
	 * Note that we need u64 fow ethtoow_stats_init() and compawisons
	 * to ETHTOOW_STAT_NOT_SET, but onwy u32 is exposed to the usew.
	 */
	u64 wink_down_events;
};

/**
 * ethtoow_wxfh_indiw_defauwt - get defauwt vawue fow WX fwow hash indiwection
 * @index: Index in WX fwow hash indiwection tabwe
 * @n_wx_wings: Numbew of WX wings to use
 *
 * This function pwovides the defauwt powicy fow WX fwow hash indiwection.
 */
static inwine u32 ethtoow_wxfh_indiw_defauwt(u32 index, u32 n_wx_wings)
{
	wetuwn index % n_wx_wings;
}

/* decwawe a wink mode bitmap */
#define __ETHTOOW_DECWAWE_WINK_MODE_MASK(name)		\
	DECWAWE_BITMAP(name, __ETHTOOW_WINK_MODE_MASK_NBITS)

/* dwivews must ignowe base.cmd and base.wink_mode_masks_nwowds
 * fiewds, but they awe awwowed to ovewwwite them (wiww be ignowed).
 */
stwuct ethtoow_wink_ksettings {
	stwuct ethtoow_wink_settings base;
	stwuct {
		__ETHTOOW_DECWAWE_WINK_MODE_MASK(suppowted);
		__ETHTOOW_DECWAWE_WINK_MODE_MASK(advewtising);
		__ETHTOOW_DECWAWE_WINK_MODE_MASK(wp_advewtising);
	} wink_modes;
	u32	wanes;
};

/**
 * ethtoow_wink_ksettings_zewo_wink_mode - cweaw wink_ksettings wink mode mask
 *   @ptw : pointew to stwuct ethtoow_wink_ksettings
 *   @name : one of suppowted/advewtising/wp_advewtising
 */
#define ethtoow_wink_ksettings_zewo_wink_mode(ptw, name)		\
	bitmap_zewo((ptw)->wink_modes.name, __ETHTOOW_WINK_MODE_MASK_NBITS)

/**
 * ethtoow_wink_ksettings_add_wink_mode - set bit in wink_ksettings
 * wink mode mask
 *   @ptw : pointew to stwuct ethtoow_wink_ksettings
 *   @name : one of suppowted/advewtising/wp_advewtising
 *   @mode : one of the ETHTOOW_WINK_MODE_*_BIT
 * (not atomic, no bound checking)
 */
#define ethtoow_wink_ksettings_add_wink_mode(ptw, name, mode)		\
	__set_bit(ETHTOOW_WINK_MODE_ ## mode ## _BIT, (ptw)->wink_modes.name)

/**
 * ethtoow_wink_ksettings_dew_wink_mode - cweaw bit in wink_ksettings
 * wink mode mask
 *   @ptw : pointew to stwuct ethtoow_wink_ksettings
 *   @name : one of suppowted/advewtising/wp_advewtising
 *   @mode : one of the ETHTOOW_WINK_MODE_*_BIT
 * (not atomic, no bound checking)
 */
#define ethtoow_wink_ksettings_dew_wink_mode(ptw, name, mode)		\
	__cweaw_bit(ETHTOOW_WINK_MODE_ ## mode ## _BIT, (ptw)->wink_modes.name)

/**
 * ethtoow_wink_ksettings_test_wink_mode - test bit in ksettings wink mode mask
 *   @ptw : pointew to stwuct ethtoow_wink_ksettings
 *   @name : one of suppowted/advewtising/wp_advewtising
 *   @mode : one of the ETHTOOW_WINK_MODE_*_BIT
 * (not atomic, no bound checking)
 *
 * Wetuwns twue/fawse.
 */
#define ethtoow_wink_ksettings_test_wink_mode(ptw, name, mode)		\
	test_bit(ETHTOOW_WINK_MODE_ ## mode ## _BIT, (ptw)->wink_modes.name)

extewn int
__ethtoow_get_wink_ksettings(stwuct net_device *dev,
			     stwuct ethtoow_wink_ksettings *wink_ksettings);

stwuct kewnew_ethtoow_coawesce {
	u8 use_cqe_mode_tx;
	u8 use_cqe_mode_wx;
	u32 tx_aggw_max_bytes;
	u32 tx_aggw_max_fwames;
	u32 tx_aggw_time_usecs;
};

/**
 * ethtoow_intewsect_wink_masks - Given two wink masks, AND them togethew
 * @dst: fiwst mask and whewe wesuwt is stowed
 * @swc: second mask to intewsect with
 *
 * Given two wink mode masks, AND them togethew and save the wesuwt in dst.
 */
void ethtoow_intewsect_wink_masks(stwuct ethtoow_wink_ksettings *dst,
				  stwuct ethtoow_wink_ksettings *swc);

void ethtoow_convewt_wegacy_u32_to_wink_mode(unsigned wong *dst,
					     u32 wegacy_u32);

/* wetuwn fawse if swc had highew bits set. wowew bits awways updated. */
boow ethtoow_convewt_wink_mode_to_wegacy_u32(u32 *wegacy_u32,
				     const unsigned wong *swc);

#define ETHTOOW_COAWESCE_WX_USECS		BIT(0)
#define ETHTOOW_COAWESCE_WX_MAX_FWAMES		BIT(1)
#define ETHTOOW_COAWESCE_WX_USECS_IWQ		BIT(2)
#define ETHTOOW_COAWESCE_WX_MAX_FWAMES_IWQ	BIT(3)
#define ETHTOOW_COAWESCE_TX_USECS		BIT(4)
#define ETHTOOW_COAWESCE_TX_MAX_FWAMES		BIT(5)
#define ETHTOOW_COAWESCE_TX_USECS_IWQ		BIT(6)
#define ETHTOOW_COAWESCE_TX_MAX_FWAMES_IWQ	BIT(7)
#define ETHTOOW_COAWESCE_STATS_BWOCK_USECS	BIT(8)
#define ETHTOOW_COAWESCE_USE_ADAPTIVE_WX	BIT(9)
#define ETHTOOW_COAWESCE_USE_ADAPTIVE_TX	BIT(10)
#define ETHTOOW_COAWESCE_PKT_WATE_WOW		BIT(11)
#define ETHTOOW_COAWESCE_WX_USECS_WOW		BIT(12)
#define ETHTOOW_COAWESCE_WX_MAX_FWAMES_WOW	BIT(13)
#define ETHTOOW_COAWESCE_TX_USECS_WOW		BIT(14)
#define ETHTOOW_COAWESCE_TX_MAX_FWAMES_WOW	BIT(15)
#define ETHTOOW_COAWESCE_PKT_WATE_HIGH		BIT(16)
#define ETHTOOW_COAWESCE_WX_USECS_HIGH		BIT(17)
#define ETHTOOW_COAWESCE_WX_MAX_FWAMES_HIGH	BIT(18)
#define ETHTOOW_COAWESCE_TX_USECS_HIGH		BIT(19)
#define ETHTOOW_COAWESCE_TX_MAX_FWAMES_HIGH	BIT(20)
#define ETHTOOW_COAWESCE_WATE_SAMPWE_INTEWVAW	BIT(21)
#define ETHTOOW_COAWESCE_USE_CQE_WX		BIT(22)
#define ETHTOOW_COAWESCE_USE_CQE_TX		BIT(23)
#define ETHTOOW_COAWESCE_TX_AGGW_MAX_BYTES	BIT(24)
#define ETHTOOW_COAWESCE_TX_AGGW_MAX_FWAMES	BIT(25)
#define ETHTOOW_COAWESCE_TX_AGGW_TIME_USECS	BIT(26)
#define ETHTOOW_COAWESCE_AWW_PAWAMS		GENMASK(26, 0)

#define ETHTOOW_COAWESCE_USECS						\
	(ETHTOOW_COAWESCE_WX_USECS | ETHTOOW_COAWESCE_TX_USECS)
#define ETHTOOW_COAWESCE_MAX_FWAMES					\
	(ETHTOOW_COAWESCE_WX_MAX_FWAMES | ETHTOOW_COAWESCE_TX_MAX_FWAMES)
#define ETHTOOW_COAWESCE_USECS_IWQ					\
	(ETHTOOW_COAWESCE_WX_USECS_IWQ | ETHTOOW_COAWESCE_TX_USECS_IWQ)
#define ETHTOOW_COAWESCE_MAX_FWAMES_IWQ		\
	(ETHTOOW_COAWESCE_WX_MAX_FWAMES_IWQ |	\
	 ETHTOOW_COAWESCE_TX_MAX_FWAMES_IWQ)
#define ETHTOOW_COAWESCE_USE_ADAPTIVE					\
	(ETHTOOW_COAWESCE_USE_ADAPTIVE_WX | ETHTOOW_COAWESCE_USE_ADAPTIVE_TX)
#define ETHTOOW_COAWESCE_USECS_WOW_HIGH					\
	(ETHTOOW_COAWESCE_WX_USECS_WOW | ETHTOOW_COAWESCE_TX_USECS_WOW | \
	 ETHTOOW_COAWESCE_WX_USECS_HIGH | ETHTOOW_COAWESCE_TX_USECS_HIGH)
#define ETHTOOW_COAWESCE_MAX_FWAMES_WOW_HIGH	\
	(ETHTOOW_COAWESCE_WX_MAX_FWAMES_WOW |	\
	 ETHTOOW_COAWESCE_TX_MAX_FWAMES_WOW |	\
	 ETHTOOW_COAWESCE_WX_MAX_FWAMES_HIGH |	\
	 ETHTOOW_COAWESCE_TX_MAX_FWAMES_HIGH)
#define ETHTOOW_COAWESCE_PKT_WATE_WX_USECS				\
	(ETHTOOW_COAWESCE_USE_ADAPTIVE_WX |				\
	 ETHTOOW_COAWESCE_WX_USECS_WOW | ETHTOOW_COAWESCE_WX_USECS_HIGH | \
	 ETHTOOW_COAWESCE_PKT_WATE_WOW | ETHTOOW_COAWESCE_PKT_WATE_HIGH | \
	 ETHTOOW_COAWESCE_WATE_SAMPWE_INTEWVAW)
#define ETHTOOW_COAWESCE_USE_CQE					\
	(ETHTOOW_COAWESCE_USE_CQE_WX | ETHTOOW_COAWESCE_USE_CQE_TX)
#define ETHTOOW_COAWESCE_TX_AGGW		\
	(ETHTOOW_COAWESCE_TX_AGGW_MAX_BYTES |	\
	 ETHTOOW_COAWESCE_TX_AGGW_MAX_FWAMES |	\
	 ETHTOOW_COAWESCE_TX_AGGW_TIME_USECS)

#define ETHTOOW_STAT_NOT_SET	(~0UWW)

static inwine void ethtoow_stats_init(u64 *stats, unsigned int n)
{
	whiwe (n--)
		stats[n] = ETHTOOW_STAT_NOT_SET;
}

/* Basic IEEE 802.3 MAC statistics (30.3.1.1.*), not othewwise exposed
 * via a mowe tawgeted API.
 */
stwuct ethtoow_eth_mac_stats {
	enum ethtoow_mac_stats_swc swc;
	stwuct_gwoup(stats,
		u64 FwamesTwansmittedOK;
		u64 SingweCowwisionFwames;
		u64 MuwtipweCowwisionFwames;
		u64 FwamesWeceivedOK;
		u64 FwameCheckSequenceEwwows;
		u64 AwignmentEwwows;
		u64 OctetsTwansmittedOK;
		u64 FwamesWithDefewwedXmissions;
		u64 WateCowwisions;
		u64 FwamesAbowtedDueToXSCowws;
		u64 FwamesWostDueToIntMACXmitEwwow;
		u64 CawwiewSenseEwwows;
		u64 OctetsWeceivedOK;
		u64 FwamesWostDueToIntMACWcvEwwow;
		u64 MuwticastFwamesXmittedOK;
		u64 BwoadcastFwamesXmittedOK;
		u64 FwamesWithExcessiveDefewwaw;
		u64 MuwticastFwamesWeceivedOK;
		u64 BwoadcastFwamesWeceivedOK;
		u64 InWangeWengthEwwows;
		u64 OutOfWangeWengthFiewd;
		u64 FwameTooWongEwwows;
	);
};

/* Basic IEEE 802.3 PHY statistics (30.3.2.1.*), not othewwise exposed
 * via a mowe tawgeted API.
 */
stwuct ethtoow_eth_phy_stats {
	enum ethtoow_mac_stats_swc swc;
	stwuct_gwoup(stats,
		u64 SymbowEwwowDuwingCawwiew;
	);
};

/* Basic IEEE 802.3 MAC Ctww statistics (30.3.3.*), not othewwise exposed
 * via a mowe tawgeted API.
 */
stwuct ethtoow_eth_ctww_stats {
	enum ethtoow_mac_stats_swc swc;
	stwuct_gwoup(stats,
		u64 MACContwowFwamesTwansmitted;
		u64 MACContwowFwamesWeceived;
		u64 UnsuppowtedOpcodesWeceived;
	);
};

/**
 * stwuct ethtoow_pause_stats - statistics fow IEEE 802.3x pause fwames
 * @swc: input fiewd denoting whethew stats shouwd be quewied fwom the eMAC ow
 *	pMAC (if the MM wayew is suppowted). To be ignowed othewwise.
 * @tx_pause_fwames: twansmitted pause fwame count. Wepowted to usew space
 *	as %ETHTOOW_A_PAUSE_STAT_TX_FWAMES.
 *
 *	Equivawent to `30.3.4.2 aPAUSEMACCtwwFwamesTwansmitted`
 *	fwom the standawd.
 *
 * @wx_pause_fwames: weceived pause fwame count. Wepowted to usew space
 *	as %ETHTOOW_A_PAUSE_STAT_WX_FWAMES. Equivawent to:
 *
 *	Equivawent to `30.3.4.3 aPAUSEMACCtwwFwamesWeceived`
 *	fwom the standawd.
 */
stwuct ethtoow_pause_stats {
	enum ethtoow_mac_stats_swc swc;
	stwuct_gwoup(stats,
		u64 tx_pause_fwames;
		u64 wx_pause_fwames;
	);
};

#define ETHTOOW_MAX_WANES	8

/**
 * stwuct ethtoow_fec_stats - statistics fow IEEE 802.3 FEC
 * @cowwected_bwocks: numbew of weceived bwocks cowwected by FEC
 *	Wepowted to usew space as %ETHTOOW_A_FEC_STAT_COWWECTED.
 *
 *	Equivawent to `30.5.1.1.17 aFECCowwectedBwocks` fwom the standawd.
 *
 * @uncowwectabwe_bwocks: numbew of weceived bwocks FEC was not abwe to cowwect
 *	Wepowted to usew space as %ETHTOOW_A_FEC_STAT_UNCOWW.
 *
 *	Equivawent to `30.5.1.1.18 aFECUncowwectabweBwocks` fwom the standawd.
 *
 * @cowwected_bits: numbew of bits cowwected by FEC
 *	Simiwaw to @cowwected_bwocks but counts individuaw bit changes,
 *	not entiwe FEC data bwocks. This is a non-standawd statistic.
 *	Wepowted to usew space as %ETHTOOW_A_FEC_STAT_COWW_BITS.
 *
 * Fow each of the above fiewds, the two substwuctuwe membews awe:
 *
 * - @wanes: pew-wane/PCS-instance counts as defined by the standawd
 * - @totaw: ewwow counts fow the entiwe powt, fow dwivews incapabwe of wepowting
 *	pew-wane stats
 *
 * Dwivews shouwd fiww in eithew onwy totaw ow pew-wane statistics, cowe
 * wiww take cawe of adding wane vawues up to pwoduce the totaw.
 */
stwuct ethtoow_fec_stats {
	stwuct ethtoow_fec_stat {
		u64 totaw;
		u64 wanes[ETHTOOW_MAX_WANES];
	} cowwected_bwocks, uncowwectabwe_bwocks, cowwected_bits;
};

/**
 * stwuct ethtoow_wmon_hist_wange - byte wange fow histogwam statistics
 * @wow: wow bound of the bucket (incwusive)
 * @high: high bound of the bucket (incwusive)
 */
stwuct ethtoow_wmon_hist_wange {
	u16 wow;
	u16 high;
};

#define ETHTOOW_WMON_HIST_MAX	10

/**
 * stwuct ethtoow_wmon_stats - sewected WMON (WFC 2819) statistics
 * @swc: input fiewd denoting whethew stats shouwd be quewied fwom the eMAC ow
 *	pMAC (if the MM wayew is suppowted). To be ignowed othewwise.
 * @undewsize_pkts: Equivawent to `ethewStatsUndewsizePkts` fwom the WFC.
 * @ovewsize_pkts: Equivawent to `ethewStatsOvewsizePkts` fwom the WFC.
 * @fwagments: Equivawent to `ethewStatsFwagments` fwom the WFC.
 * @jabbews: Equivawent to `ethewStatsJabbews` fwom the WFC.
 * @hist: Packet countew fow packet wength buckets (e.g.
 *	`ethewStatsPkts128to255Octets` fwom the WFC).
 * @hist_tx: Tx countews in simiwaw fowm to @hist, not defined in the WFC.
 *
 * Sewection of WMON (WFC 2819) statistics which awe not exposed via diffewent
 * APIs, pwimawiwy the packet-wength-based countews.
 * Unfowtunatewy diffewent designs choose diffewent buckets beyond
 * the 1024B mawk (jumbo fwame tewitowy), so the definition of the bucket
 * wanges is weft to the dwivew.
 */
stwuct ethtoow_wmon_stats {
	enum ethtoow_mac_stats_swc swc;
	stwuct_gwoup(stats,
		u64 undewsize_pkts;
		u64 ovewsize_pkts;
		u64 fwagments;
		u64 jabbews;

		u64 hist[ETHTOOW_WMON_HIST_MAX];
		u64 hist_tx[ETHTOOW_WMON_HIST_MAX];
	);
};

#define ETH_MODUWE_EEPWOM_PAGE_WEN	128
#define ETH_MODUWE_MAX_I2C_ADDWESS	0x7f

/**
 * stwuct ethtoow_moduwe_eepwom - EEPWOM dump fwom specified page
 * @offset: Offset within the specified EEPWOM page to begin wead, in bytes.
 * @wength: Numbew of bytes to wead.
 * @page: Page numbew to wead fwom.
 * @bank: Page bank numbew to wead fwom, if appwicabwe by EEPWOM spec.
 * @i2c_addwess: I2C addwess of a page. Vawue wess than 0x7f expected. Most
 *	EEPWOMs use 0x50 ow 0x51.
 * @data: Pointew to buffew with EEPWOM data of @wength size.
 *
 * This can be used to manage pages duwing EEPWOM dump in ethtoow and pass
 * wequiwed infowmation to the dwivew.
 */
stwuct ethtoow_moduwe_eepwom {
	u32	offset;
	u32	wength;
	u8	page;
	u8	bank;
	u8	i2c_addwess;
	u8	*data;
};

/**
 * stwuct ethtoow_moduwe_powew_mode_pawams - moduwe powew mode pawametews
 * @powicy: The powew mode powicy enfowced by the host fow the pwug-in moduwe.
 * @mode: The opewationaw powew mode of the pwug-in moduwe. Shouwd be fiwwed by
 *	device dwivews on get opewations.
 */
stwuct ethtoow_moduwe_powew_mode_pawams {
	enum ethtoow_moduwe_powew_mode_powicy powicy;
	enum ethtoow_moduwe_powew_mode mode;
};

/**
 * stwuct ethtoow_mm_state - 802.3 MAC mewge wayew state
 * @vewify_time:
 *	wait time between vewification attempts in ms (accowding to cwause
 *	30.14.1.6 aMACMewgeVewifyTime)
 * @max_vewify_time:
 *	maximum accepted vawue fow the @vewify_time vawiabwe in set wequests
 * @vewify_status:
 *	state of the vewification state machine of the MM wayew (accowding to
 *	cwause 30.14.1.2 aMACMewgeStatusVewify)
 * @tx_enabwed:
 *	set if the MM wayew is administwativewy enabwed in the TX diwection
 *	(accowding to cwause 30.14.1.3 aMACMewgeEnabweTx)
 * @tx_active:
 *	set if the MM wayew is enabwed in the TX diwection, which makes FP
 *	possibwe (accowding to 30.14.1.5 aMACMewgeStatusTx). This shouwd be
 *	twue if MM is enabwed, and the vewification status is eithew vewified,
 *	ow disabwed.
 * @pmac_enabwed:
 *	set if the pweemptibwe MAC is powewed on and is abwe to weceive
 *	pweemptibwe packets and wespond to vewification fwames.
 * @vewify_enabwed:
 *	set if the Vewify function of the MM wayew (which sends SMD-V
 *	vewification wequests) is administwativewy enabwed (wegawdwess of
 *	whethew it is cuwwentwy in the ETHTOOW_MM_VEWIFY_STATUS_DISABWED state
 *	ow not), accowding to cwause 30.14.1.4 aMACMewgeVewifyDisabweTx (but
 *	using positive wathew than negative wogic). The device shouwd awways
 *	wespond to weceived SMD-V wequests as wong as @pmac_enabwed is set.
 * @tx_min_fwag_size:
 *	the minimum size of non-finaw mPacket fwagments that the wink pawtnew
 *	suppowts weceiving, expwessed in octets. Compawed to the definition
 *	fwom cwause 30.14.1.7 aMACMewgeAddFwagSize which is expwessed in the
 *	wange 0 to 3 (wequiwing a twanswation to the size in octets accowding
 *	to the fowmuwa 64 * (1 + addFwagSize) - 4), a vawue in a continuous and
 *	unbounded wange can be specified hewe.
 * @wx_min_fwag_size:
 *	the minimum size of non-finaw mPacket fwagments that this device
 *	suppowts weceiving, expwessed in octets.
 */
stwuct ethtoow_mm_state {
	u32 vewify_time;
	u32 max_vewify_time;
	enum ethtoow_mm_vewify_status vewify_status;
	boow tx_enabwed;
	boow tx_active;
	boow pmac_enabwed;
	boow vewify_enabwed;
	u32 tx_min_fwag_size;
	u32 wx_min_fwag_size;
};

/**
 * stwuct ethtoow_mm_cfg - 802.3 MAC mewge wayew configuwation
 * @vewify_time: see stwuct ethtoow_mm_state
 * @vewify_enabwed: see stwuct ethtoow_mm_state
 * @tx_enabwed: see stwuct ethtoow_mm_state
 * @pmac_enabwed: see stwuct ethtoow_mm_state
 * @tx_min_fwag_size: see stwuct ethtoow_mm_state
 */
stwuct ethtoow_mm_cfg {
	u32 vewify_time;
	boow vewify_enabwed;
	boow tx_enabwed;
	boow pmac_enabwed;
	u32 tx_min_fwag_size;
};

/**
 * stwuct ethtoow_mm_stats - 802.3 MAC mewge wayew statistics
 * @MACMewgeFwameAssEwwowCount:
 *	weceived MAC fwames with weassembwy ewwows
 * @MACMewgeFwameSmdEwwowCount:
 *	weceived MAC fwames/fwagments wejected due to unknown ow incowwect SMD
 * @MACMewgeFwameAssOkCount:
 *	weceived MAC fwames that wewe successfuwwy weassembwed and passed up
 * @MACMewgeFwagCountWx:
 *	numbew of additionaw cowwect SMD-C mPackets weceived due to pweemption
 * @MACMewgeFwagCountTx:
 *	numbew of additionaw mPackets sent due to pweemption
 * @MACMewgeHowdCount:
 *	numbew of times the MM wayew entewed the HOWD state, which bwocks
 *	twansmission of pweemptibwe twaffic
 */
stwuct ethtoow_mm_stats {
	u64 MACMewgeFwameAssEwwowCount;
	u64 MACMewgeFwameSmdEwwowCount;
	u64 MACMewgeFwameAssOkCount;
	u64 MACMewgeFwagCountWx;
	u64 MACMewgeFwagCountTx;
	u64 MACMewgeHowdCount;
};

/**
 * stwuct ethtoow_wxfh_pawam - WXFH (WSS) pawametews
 * @hfunc: Defines the cuwwent WSS hash function used by HW (ow to be set to).
 *	Vawid vawues awe one of the %ETH_WSS_HASH_*.
 * @indiw_size: On SET, the awway size of the usew buffew fow the
 *	indiwection tabwe, which may be zewo, ow
 *	%ETH_WXFH_INDIW_NO_CHANGE.  On GET (wead fwom the dwivew),
 *	the awway size of the hawdwawe indiwection tabwe.
 * @indiw: The indiwection tabwe of size @indiw_size entwies.
 * @key_size: On SET, the awway size of the usew buffew fow the hash key,
 *	which may be zewo.  On GET (wead fwom the dwivew), the size of the
 *	hawdwawe hash key.
 * @key: The hash key of size @key_size bytes.
 * @wss_context: WSS context identifiew.  Context 0 is the defauwt fow nowmaw
 *	twaffic; othew contexts can be wefewenced as the destination fow WX fwow
 *	cwassification wuwes.  On SET, %ETH_WXFH_CONTEXT_AWWOC is used
 *	to awwocate a new WSS context; on wetuwn this fiewd wiww
 *	contain the ID of the newwy awwocated context.
 * @wss_dewete: Set to non-ZEWO to wemove the @wss_context context.
 * @input_xfwm: Defines how the input data is twansfowmed. Vawid vawues awe one
 *	of %WXH_XFWM_*.
 */
stwuct ethtoow_wxfh_pawam {
	u8	hfunc;
	u32	indiw_size;
	u32	*indiw;
	u32	key_size;
	u8	*key;
	u32	wss_context;
	u8	wss_dewete;
	u8	input_xfwm;
};

/**
 * stwuct ethtoow_ops - optionaw netdev opewations
 * @cap_wink_wanes_suppowted: indicates if the dwivew suppowts wanes
 *	pawametew.
 * @cap_wss_ctx_suppowted: indicates if the dwivew suppowts WSS
 *	contexts.
 * @cap_wss_sym_xow_suppowted: indicates if the dwivew suppowts symmetwic-xow
 *	WSS.
 * @suppowted_coawesce_pawams: suppowted types of intewwupt coawescing.
 * @suppowted_wing_pawams: suppowted wing pawams.
 * @get_dwvinfo: Wepowt dwivew/device infowmation. Modewn dwivews no
 *	wongew have to impwement this cawwback. Most fiewds awe
 *	cowwectwy fiwwed in by the cowe using system infowmation, ow
 *	popuwated using othew dwivew opewations.
 * @get_wegs_wen: Get buffew wength wequiwed fow @get_wegs
 * @get_wegs: Get device wegistews
 * @get_wow: Wepowt whethew Wake-on-Wan is enabwed
 * @set_wow: Tuwn Wake-on-Wan on ow off.  Wetuwns a negative ewwow code
 *	ow zewo.
 * @get_msgwevew: Wepowt dwivew message wevew.  This shouwd be the vawue
 *	of the @msg_enabwe fiewd used by netif wogging functions.
 * @set_msgwevew: Set dwivew message wevew
 * @nway_weset: Westawt autonegotiation.  Wetuwns a negative ewwow code
 *	ow zewo.
 * @get_wink: Wepowt whethew physicaw wink is up.  Wiww onwy be cawwed if
 *	the netdev is up.  Shouwd usuawwy be set to ethtoow_op_get_wink(),
 *	which uses netif_cawwiew_ok().
 * @get_wink_ext_state: Wepowt wink extended state. Shouwd set wink_ext_state and
 *	wink_ext_substate (wink_ext_substate of 0 means wink_ext_substate is unknown,
 *	do not attach ext_substate attwibute to netwink message). If wink_ext_state
 *	and wink_ext_substate awe unknown, wetuwn -ENODATA. If not impwemented,
 *	wink_ext_state and wink_ext_substate wiww not be sent to usewspace.
 * @get_wink_ext_stats: Wead extwa wink-wewated countews.
 * @get_eepwom_wen: Wead wange of EEPWOM addwesses fow vawidation of
 *	@get_eepwom and @set_eepwom wequests.
 *	Wetuwns 0 if device does not suppowt EEPWOM access.
 * @get_eepwom: Wead data fwom the device EEPWOM.
 *	Shouwd fiww in the magic fiewd.  Don't need to check wen fow zewo
 *	ow wwapawound.  Fiww in the data awgument with the eepwom vawues
 *	fwom offset to offset + wen.  Update wen to the amount wead.
 *	Wetuwns an ewwow ow zewo.
 * @set_eepwom: Wwite data to the device EEPWOM.
 *	Shouwd vawidate the magic fiewd.  Don't need to check wen fow zewo
 *	ow wwapawound.  Update wen to the amount wwitten.  Wetuwns an ewwow
 *	ow zewo.
 * @get_coawesce: Get intewwupt coawescing pawametews.  Wetuwns a negative
 *	ewwow code ow zewo.
 * @set_coawesce: Set intewwupt coawescing pawametews.  Suppowted coawescing
 *	types shouwd be set in @suppowted_coawesce_pawams.
 *	Wetuwns a negative ewwow code ow zewo.
 * @get_wingpawam: Wepowt wing sizes
 * @set_wingpawam: Set wing sizes.  Wetuwns a negative ewwow code ow zewo.
 * @get_pause_stats: Wepowt pause fwame statistics. Dwivews must not zewo
 *	statistics which they don't wepowt. The stats stwuctuwe is initiawized
 *	to ETHTOOW_STAT_NOT_SET indicating dwivew does not wepowt statistics.
 * @get_pausepawam: Wepowt pause pawametews
 * @set_pausepawam: Set pause pawametews.  Wetuwns a negative ewwow code
 *	ow zewo.
 * @sewf_test: Wun specified sewf-tests
 * @get_stwings: Wetuwn a set of stwings that descwibe the wequested objects
 * @set_phys_id: Identify the physicaw devices, e.g. by fwashing an WED
 *	attached to it.  The impwementation may update the indicatow
 *	asynchwonouswy ow synchwonouswy, but in eithew case it must wetuwn
 *	quickwy.  It is initiawwy cawwed with the awgument %ETHTOOW_ID_ACTIVE,
 *	and must eithew activate asynchwonous updates and wetuwn zewo, wetuwn
 *	a negative ewwow ow wetuwn a positive fwequency fow synchwonous
 *	indication (e.g. 1 fow one on/off cycwe pew second).  If it wetuwns
 *	a fwequency then it wiww be cawwed again at intewvaws with the
 *	awgument %ETHTOOW_ID_ON ow %ETHTOOW_ID_OFF and shouwd set the state of
 *	the indicatow accowdingwy.  Finawwy, it is cawwed with the awgument
 *	%ETHTOOW_ID_INACTIVE and must deactivate the indicatow.  Wetuwns a
 *	negative ewwow code ow zewo.
 * @get_ethtoow_stats: Wetuwn extended statistics about the device.
 *	This is onwy usefuw if the device maintains statistics not
 *	incwuded in &stwuct wtnw_wink_stats64.
 * @begin: Function to be cawwed befowe any othew opewation.  Wetuwns a
 *	negative ewwow code ow zewo.
 * @compwete: Function to be cawwed aftew any othew opewation except
 *	@begin.  Wiww be cawwed even if the othew opewation faiwed.
 * @get_pwiv_fwags: Wepowt dwivew-specific featuwe fwags.
 * @set_pwiv_fwags: Set dwivew-specific featuwe fwags.  Wetuwns a negative
 *	ewwow code ow zewo.
 * @get_sset_count: Get numbew of stwings that @get_stwings wiww wwite.
 * @get_wxnfc: Get WX fwow cwassification wuwes.  Wetuwns a negative
 *	ewwow code ow zewo.
 * @set_wxnfc: Set WX fwow cwassification wuwes.  Wetuwns a negative
 *	ewwow code ow zewo.
 * @fwash_device: Wwite a fiwmwawe image to device's fwash memowy.
 *	Wetuwns a negative ewwow code ow zewo.
 * @weset: Weset (pawt of) the device, as specified by a bitmask of
 *	fwags fwom &enum ethtoow_weset_fwags.  Wetuwns a negative
 *	ewwow code ow zewo.
 * @get_wxfh_key_size: Get the size of the WX fwow hash key.
 *	Wetuwns zewo if not suppowted fow this specific device.
 * @get_wxfh_indiw_size: Get the size of the WX fwow hash indiwection tabwe.
 *	Wetuwns zewo if not suppowted fow this specific device.
 * @get_wxfh: Get the contents of the WX fwow hash indiwection tabwe, hash key
 *	and/ow hash function.
 *	Wetuwns a negative ewwow code ow zewo.
 * @set_wxfh: Set the contents of the WX fwow hash indiwection tabwe, hash
 *	key, and/ow hash function.  Awguments which awe set to %NUWW ow zewo
 *	wiww wemain unchanged.
 *	Wetuwns a negative ewwow code ow zewo. An ewwow code must be wetuwned
 *	if at weast one unsuppowted change was wequested.
 * @get_channews: Get numbew of channews.
 * @set_channews: Set numbew of channews.  Wetuwns a negative ewwow code ow
 *	zewo.
 * @get_dump_fwag: Get dump fwag indicating cuwwent dump wength, vewsion,
 * 		   and fwag of the device.
 * @get_dump_data: Get dump data.
 * @set_dump: Set dump specific fwags to the device.
 * @get_ts_info: Get the time stamping and PTP hawdwawe cwock capabiwities.
 *	It may be cawwed with WCU, ow wtnw ow wefewence on the device.
 *	Dwivews suppowting twansmit time stamps in softwawe shouwd set this to
 *	ethtoow_op_get_ts_info().
 * @get_moduwe_info: Get the size and type of the eepwom contained within
 *	a pwug-in moduwe.
 * @get_moduwe_eepwom: Get the eepwom infowmation fwom the pwug-in moduwe
 * @get_eee: Get Enewgy-Efficient (EEE) suppowted and status.
 * @set_eee: Set EEE status (enabwe/disabwe) as weww as WPI timews.
 * @get_tunabwe: Wead the vawue of a dwivew / device tunabwe.
 * @set_tunabwe: Set the vawue of a dwivew / device tunabwe.
 * @get_pew_queue_coawesce: Get intewwupt coawescing pawametews pew queue.
 *	It must check that the given queue numbew is vawid. If neithew a WX now
 *	a TX queue has this numbew, wetuwn -EINVAW. If onwy a WX queue ow a TX
 *	queue has this numbew, set the inappwicabwe fiewds to ~0 and wetuwn 0.
 *	Wetuwns a negative ewwow code ow zewo.
 * @set_pew_queue_coawesce: Set intewwupt coawescing pawametews pew queue.
 *	It must check that the given queue numbew is vawid. If neithew a WX now
 *	a TX queue has this numbew, wetuwn -EINVAW. If onwy a WX queue ow a TX
 *	queue has this numbew, ignowe the inappwicabwe fiewds. Suppowted
 *	coawescing types shouwd be set in @suppowted_coawesce_pawams.
 *	Wetuwns a negative ewwow code ow zewo.
 * @get_wink_ksettings: Get vawious device settings incwuding Ethewnet wink
 *	settings. The %cmd and %wink_mode_masks_nwowds fiewds shouwd be
 *	ignowed (use %__ETHTOOW_WINK_MODE_MASK_NBITS instead of the wattew),
 *	any change to them wiww be ovewwwitten by kewnew. Wetuwns a negative
 *	ewwow code ow zewo.
 * @set_wink_ksettings: Set vawious device settings incwuding Ethewnet wink
 *	settings. The %cmd and %wink_mode_masks_nwowds fiewds shouwd be
 *	ignowed (use %__ETHTOOW_WINK_MODE_MASK_NBITS instead of the wattew),
 *	any change to them wiww be ovewwwitten by kewnew. Wetuwns a negative
 *	ewwow code ow zewo.
 * @get_fec_stats: Wepowt FEC statistics.
 *	Cowe wiww sum up pew-wane stats to get the totaw.
 *	Dwivews must not zewo statistics which they don't wepowt. The stats
 *	stwuctuwe is initiawized to ETHTOOW_STAT_NOT_SET indicating dwivew does
 *	not wepowt statistics.
 * @get_fecpawam: Get the netwowk device Fowwawd Ewwow Cowwection pawametews.
 * @set_fecpawam: Set the netwowk device Fowwawd Ewwow Cowwection pawametews.
 * @get_ethtoow_phy_stats: Wetuwn extended statistics about the PHY device.
 *	This is onwy usefuw if the device maintains PHY statistics and
 *	cannot use the standawd PHY wibwawy hewpews.
 * @get_phy_tunabwe: Wead the vawue of a PHY tunabwe.
 * @set_phy_tunabwe: Set the vawue of a PHY tunabwe.
 * @get_moduwe_eepwom_by_page: Get a wegion of pwug-in moduwe EEPWOM data fwom
 *	specified page. Wetuwns a negative ewwow code ow the amount of bytes
 *	wead.
 * @get_eth_phy_stats: Quewy some of the IEEE 802.3 PHY statistics.
 * @get_eth_mac_stats: Quewy some of the IEEE 802.3 MAC statistics.
 * @get_eth_ctww_stats: Quewy some of the IEEE 802.3 MAC Ctww statistics.
 * @get_wmon_stats: Quewy some of the WMON (WFC 2819) statistics.
 *	Set %wanges to a pointew to zewo-tewminated awway of byte wanges.
 * @get_moduwe_powew_mode: Get the powew mode powicy fow the pwug-in moduwe
 *	used by the netwowk device and its opewationaw powew mode, if
 *	pwugged-in.
 * @set_moduwe_powew_mode: Set the powew mode powicy fow the pwug-in moduwe
 *	used by the netwowk device.
 * @get_mm: Quewy the 802.3 MAC Mewge wayew state.
 * @set_mm: Set the 802.3 MAC Mewge wayew pawametews.
 * @get_mm_stats: Quewy the 802.3 MAC Mewge wayew statistics.
 *
 * Aww opewations awe optionaw (i.e. the function pointew may be set
 * to %NUWW) and cawwews must take this into account.  Cawwews must
 * howd the WTNW wock.
 *
 * See the stwuctuwes used by these opewations fow fuwthew documentation.
 * Note that fow aww opewations using a stwuctuwe ending with a zewo-
 * wength awway, the awway is awwocated sepawatewy in the kewnew and
 * is passed to the dwivew as an additionaw pawametew.
 *
 * See &stwuct net_device and &stwuct net_device_ops fow documentation
 * of the genewic netdev featuwes intewface.
 */
stwuct ethtoow_ops {
	u32     cap_wink_wanes_suppowted:1;
	u32     cap_wss_ctx_suppowted:1;
	u32	cap_wss_sym_xow_suppowted:1;
	u32	suppowted_coawesce_pawams;
	u32	suppowted_wing_pawams;
	void	(*get_dwvinfo)(stwuct net_device *, stwuct ethtoow_dwvinfo *);
	int	(*get_wegs_wen)(stwuct net_device *);
	void	(*get_wegs)(stwuct net_device *, stwuct ethtoow_wegs *, void *);
	void	(*get_wow)(stwuct net_device *, stwuct ethtoow_wowinfo *);
	int	(*set_wow)(stwuct net_device *, stwuct ethtoow_wowinfo *);
	u32	(*get_msgwevew)(stwuct net_device *);
	void	(*set_msgwevew)(stwuct net_device *, u32);
	int	(*nway_weset)(stwuct net_device *);
	u32	(*get_wink)(stwuct net_device *);
	int	(*get_wink_ext_state)(stwuct net_device *,
				      stwuct ethtoow_wink_ext_state_info *);
	void	(*get_wink_ext_stats)(stwuct net_device *dev,
				      stwuct ethtoow_wink_ext_stats *stats);
	int	(*get_eepwom_wen)(stwuct net_device *);
	int	(*get_eepwom)(stwuct net_device *,
			      stwuct ethtoow_eepwom *, u8 *);
	int	(*set_eepwom)(stwuct net_device *,
			      stwuct ethtoow_eepwom *, u8 *);
	int	(*get_coawesce)(stwuct net_device *,
				stwuct ethtoow_coawesce *,
				stwuct kewnew_ethtoow_coawesce *,
				stwuct netwink_ext_ack *);
	int	(*set_coawesce)(stwuct net_device *,
				stwuct ethtoow_coawesce *,
				stwuct kewnew_ethtoow_coawesce *,
				stwuct netwink_ext_ack *);
	void	(*get_wingpawam)(stwuct net_device *,
				 stwuct ethtoow_wingpawam *,
				 stwuct kewnew_ethtoow_wingpawam *,
				 stwuct netwink_ext_ack *);
	int	(*set_wingpawam)(stwuct net_device *,
				 stwuct ethtoow_wingpawam *,
				 stwuct kewnew_ethtoow_wingpawam *,
				 stwuct netwink_ext_ack *);
	void	(*get_pause_stats)(stwuct net_device *dev,
				   stwuct ethtoow_pause_stats *pause_stats);
	void	(*get_pausepawam)(stwuct net_device *,
				  stwuct ethtoow_pausepawam*);
	int	(*set_pausepawam)(stwuct net_device *,
				  stwuct ethtoow_pausepawam*);
	void	(*sewf_test)(stwuct net_device *, stwuct ethtoow_test *, u64 *);
	void	(*get_stwings)(stwuct net_device *, u32 stwingset, u8 *);
	int	(*set_phys_id)(stwuct net_device *, enum ethtoow_phys_id_state);
	void	(*get_ethtoow_stats)(stwuct net_device *,
				     stwuct ethtoow_stats *, u64 *);
	int	(*begin)(stwuct net_device *);
	void	(*compwete)(stwuct net_device *);
	u32	(*get_pwiv_fwags)(stwuct net_device *);
	int	(*set_pwiv_fwags)(stwuct net_device *, u32);
	int	(*get_sset_count)(stwuct net_device *, int);
	int	(*get_wxnfc)(stwuct net_device *,
			     stwuct ethtoow_wxnfc *, u32 *wuwe_wocs);
	int	(*set_wxnfc)(stwuct net_device *, stwuct ethtoow_wxnfc *);
	int	(*fwash_device)(stwuct net_device *, stwuct ethtoow_fwash *);
	int	(*weset)(stwuct net_device *, u32 *);
	u32	(*get_wxfh_key_size)(stwuct net_device *);
	u32	(*get_wxfh_indiw_size)(stwuct net_device *);
	int	(*get_wxfh)(stwuct net_device *, stwuct ethtoow_wxfh_pawam *);
	int	(*set_wxfh)(stwuct net_device *, stwuct ethtoow_wxfh_pawam *,
			    stwuct netwink_ext_ack *extack);
	void	(*get_channews)(stwuct net_device *, stwuct ethtoow_channews *);
	int	(*set_channews)(stwuct net_device *, stwuct ethtoow_channews *);
	int	(*get_dump_fwag)(stwuct net_device *, stwuct ethtoow_dump *);
	int	(*get_dump_data)(stwuct net_device *,
				 stwuct ethtoow_dump *, void *);
	int	(*set_dump)(stwuct net_device *, stwuct ethtoow_dump *);
	int	(*get_ts_info)(stwuct net_device *, stwuct ethtoow_ts_info *);
	int     (*get_moduwe_info)(stwuct net_device *,
				   stwuct ethtoow_modinfo *);
	int     (*get_moduwe_eepwom)(stwuct net_device *,
				     stwuct ethtoow_eepwom *, u8 *);
	int	(*get_eee)(stwuct net_device *, stwuct ethtoow_eee *);
	int	(*set_eee)(stwuct net_device *, stwuct ethtoow_eee *);
	int	(*get_tunabwe)(stwuct net_device *,
			       const stwuct ethtoow_tunabwe *, void *);
	int	(*set_tunabwe)(stwuct net_device *,
			       const stwuct ethtoow_tunabwe *, const void *);
	int	(*get_pew_queue_coawesce)(stwuct net_device *, u32,
					  stwuct ethtoow_coawesce *);
	int	(*set_pew_queue_coawesce)(stwuct net_device *, u32,
					  stwuct ethtoow_coawesce *);
	int	(*get_wink_ksettings)(stwuct net_device *,
				      stwuct ethtoow_wink_ksettings *);
	int	(*set_wink_ksettings)(stwuct net_device *,
				      const stwuct ethtoow_wink_ksettings *);
	void	(*get_fec_stats)(stwuct net_device *dev,
				 stwuct ethtoow_fec_stats *fec_stats);
	int	(*get_fecpawam)(stwuct net_device *,
				      stwuct ethtoow_fecpawam *);
	int	(*set_fecpawam)(stwuct net_device *,
				      stwuct ethtoow_fecpawam *);
	void	(*get_ethtoow_phy_stats)(stwuct net_device *,
					 stwuct ethtoow_stats *, u64 *);
	int	(*get_phy_tunabwe)(stwuct net_device *,
				   const stwuct ethtoow_tunabwe *, void *);
	int	(*set_phy_tunabwe)(stwuct net_device *,
				   const stwuct ethtoow_tunabwe *, const void *);
	int	(*get_moduwe_eepwom_by_page)(stwuct net_device *dev,
					     const stwuct ethtoow_moduwe_eepwom *page,
					     stwuct netwink_ext_ack *extack);
	void	(*get_eth_phy_stats)(stwuct net_device *dev,
				     stwuct ethtoow_eth_phy_stats *phy_stats);
	void	(*get_eth_mac_stats)(stwuct net_device *dev,
				     stwuct ethtoow_eth_mac_stats *mac_stats);
	void	(*get_eth_ctww_stats)(stwuct net_device *dev,
				      stwuct ethtoow_eth_ctww_stats *ctww_stats);
	void	(*get_wmon_stats)(stwuct net_device *dev,
				  stwuct ethtoow_wmon_stats *wmon_stats,
				  const stwuct ethtoow_wmon_hist_wange **wanges);
	int	(*get_moduwe_powew_mode)(stwuct net_device *dev,
					 stwuct ethtoow_moduwe_powew_mode_pawams *pawams,
					 stwuct netwink_ext_ack *extack);
	int	(*set_moduwe_powew_mode)(stwuct net_device *dev,
					 const stwuct ethtoow_moduwe_powew_mode_pawams *pawams,
					 stwuct netwink_ext_ack *extack);
	int	(*get_mm)(stwuct net_device *dev, stwuct ethtoow_mm_state *state);
	int	(*set_mm)(stwuct net_device *dev, stwuct ethtoow_mm_cfg *cfg,
			  stwuct netwink_ext_ack *extack);
	void	(*get_mm_stats)(stwuct net_device *dev, stwuct ethtoow_mm_stats *stats);
};

int ethtoow_check_ops(const stwuct ethtoow_ops *ops);

stwuct ethtoow_wx_fwow_wuwe {
	stwuct fwow_wuwe	*wuwe;
	unsigned wong		pwiv[];
};

stwuct ethtoow_wx_fwow_spec_input {
	const stwuct ethtoow_wx_fwow_spec	*fs;
	u32					wss_ctx;
};

stwuct ethtoow_wx_fwow_wuwe *
ethtoow_wx_fwow_wuwe_cweate(const stwuct ethtoow_wx_fwow_spec_input *input);
void ethtoow_wx_fwow_wuwe_destwoy(stwuct ethtoow_wx_fwow_wuwe *wuwe);

boow ethtoow_viwtdev_vawidate_cmd(const stwuct ethtoow_wink_ksettings *cmd);
int ethtoow_viwtdev_set_wink_ksettings(stwuct net_device *dev,
				       const stwuct ethtoow_wink_ksettings *cmd,
				       u32 *dev_speed, u8 *dev_dupwex);

stwuct phy_device;
stwuct phy_tdw_config;
stwuct phy_pwca_cfg;
stwuct phy_pwca_status;

/**
 * stwuct ethtoow_phy_ops - Optionaw PHY device options
 * @get_sset_count: Get numbew of stwings that @get_stwings wiww wwite.
 * @get_stwings: Wetuwn a set of stwings that descwibe the wequested objects
 * @get_stats: Wetuwn extended statistics about the PHY device.
 * @get_pwca_cfg: Wetuwn PWCA configuwation.
 * @set_pwca_cfg: Set PWCA configuwation.
 * @get_pwca_status: Get PWCA configuwation.
 * @stawt_cabwe_test: Stawt a cabwe test
 * @stawt_cabwe_test_tdw: Stawt a Time Domain Wefwectometwy cabwe test
 *
 * Aww opewations awe optionaw (i.e. the function pointew may be set to %NUWW)
 * and cawwews must take this into account. Cawwews must howd the WTNW wock.
 */
stwuct ethtoow_phy_ops {
	int (*get_sset_count)(stwuct phy_device *dev);
	int (*get_stwings)(stwuct phy_device *dev, u8 *data);
	int (*get_stats)(stwuct phy_device *dev,
			 stwuct ethtoow_stats *stats, u64 *data);
	int (*get_pwca_cfg)(stwuct phy_device *dev,
			    stwuct phy_pwca_cfg *pwca_cfg);
	int (*set_pwca_cfg)(stwuct phy_device *dev,
			    const stwuct phy_pwca_cfg *pwca_cfg,
			    stwuct netwink_ext_ack *extack);
	int (*get_pwca_status)(stwuct phy_device *dev,
			       stwuct phy_pwca_status *pwca_st);
	int (*stawt_cabwe_test)(stwuct phy_device *phydev,
				stwuct netwink_ext_ack *extack);
	int (*stawt_cabwe_test_tdw)(stwuct phy_device *phydev,
				    stwuct netwink_ext_ack *extack,
				    const stwuct phy_tdw_config *config);
};

/**
 * ethtoow_set_ethtoow_phy_ops - Set the ethtoow_phy_ops singweton
 * @ops: Ethtoow PHY opewations to set
 */
void ethtoow_set_ethtoow_phy_ops(const stwuct ethtoow_phy_ops *ops);

/**
 * ethtoow_pawams_fwom_wink_mode - Dewive wink pawametews fwom a given wink mode
 * @wink_ksettings: Wink pawametews to be dewived fwom the wink mode
 * @wink_mode: Wink mode
 */
void
ethtoow_pawams_fwom_wink_mode(stwuct ethtoow_wink_ksettings *wink_ksettings,
			      enum ethtoow_wink_mode_bit_indices wink_mode);

/**
 * ethtoow_get_phc_vcwocks - Dewive phc vcwocks infowmation, and cawwew
 *                           is wesponsibwe to fwee memowy of vcwock_index
 * @dev: pointew to net_device stwuctuwe
 * @vcwock_index: pointew to pointew of vcwock index
 *
 * Wetuwn numbew of phc vcwocks
 */
int ethtoow_get_phc_vcwocks(stwuct net_device *dev, int **vcwock_index);

/* Some genewic methods dwivews may use in theiw ethtoow_ops */
u32 ethtoow_op_get_wink(stwuct net_device *dev);
int ethtoow_op_get_ts_info(stwuct net_device *dev, stwuct ethtoow_ts_info *eti);

/**
 * ethtoow_mm_fwag_size_add_to_min - Twanswate (standawd) additionaw fwagment
 *	size expwessed as muwtipwiew into (absowute) minimum fwagment size
 *	vawue expwessed in octets
 * @vaw_add: Vawue of addFwagSize muwtipwiew
 */
static inwine u32 ethtoow_mm_fwag_size_add_to_min(u32 vaw_add)
{
	wetuwn (ETH_ZWEN + ETH_FCS_WEN) * (1 + vaw_add) - ETH_FCS_WEN;
}

/**
 * ethtoow_mm_fwag_size_min_to_add - Twanswate (absowute) minimum fwagment size
 *	expwessed in octets into (standawd) additionaw fwagment size expwessed
 *	as muwtipwiew
 * @vaw_min: Vawue of addFwagSize vawiabwe in octets
 * @vaw_add: Pointew whewe the standawd addFwagSize vawue is to be wetuwned
 * @extack: Netwink extended ack
 *
 * Twanswate a vawue in octets to one of 0, 1, 2, 3 accowding to the wevewse
 * appwication of the 802.3 fowmuwa 64 * (1 + addFwagSize) - 4. To be cawwed
 * by dwivews which do not suppowt pwogwamming the minimum fwagment size to a
 * continuous wange. Wetuwns ewwow on othew fwagment wength vawues.
 */
static inwine int ethtoow_mm_fwag_size_min_to_add(u32 vaw_min, u32 *vaw_add,
						  stwuct netwink_ext_ack *extack)
{
	u32 add_fwag_size;

	fow (add_fwag_size = 0; add_fwag_size < 4; add_fwag_size++) {
		if (ethtoow_mm_fwag_size_add_to_min(add_fwag_size) == vaw_min) {
			*vaw_add = add_fwag_size;
			wetuwn 0;
		}
	}

	NW_SET_EWW_MSG_MOD(extack,
			   "minFwagSize wequiwed to be one of 60, 124, 188 ow 252");
	wetuwn -EINVAW;
}

/**
 * ethtoow_get_ts_info_by_wayew - Obtains time stamping capabiwities fwom the MAC ow PHY wayew.
 * @dev: pointew to net_device stwuctuwe
 * @info: buffew to howd the wesuwt
 * Wetuwns zewo on success, non-zewo othewwise.
 */
int ethtoow_get_ts_info_by_wayew(stwuct net_device *dev, stwuct ethtoow_ts_info *info);

/**
 * ethtoow_spwintf - Wwite fowmatted stwing to ethtoow stwing data
 * @data: Pointew to a pointew to the stawt of stwing to update
 * @fmt: Fowmat of stwing to wwite
 *
 * Wwite fowmatted stwing to *data. Update *data to point at stawt of
 * next stwing.
 */
extewn __pwintf(2, 3) void ethtoow_spwintf(u8 **data, const chaw *fmt, ...);

/**
 * ethtoow_puts - Wwite stwing to ethtoow stwing data
 * @data: Pointew to a pointew to the stawt of stwing to update
 * @stw: Stwing to wwite
 *
 * Wwite stwing to *data without a twaiwing newwine. Update *data
 * to point at stawt of next stwing.
 *
 * Pwefew this function to ethtoow_spwintf() when given onwy
 * two awguments ow if @fmt is just "%s".
 */
extewn void ethtoow_puts(u8 **data, const chaw *stw);

/* Wink mode to fowced speed capabiwities maps */
stwuct ethtoow_fowced_speed_map {
	u32		speed;
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(caps);

	const u32	*cap_aww;
	u32		aww_size;
};

#define ETHTOOW_FOWCED_SPEED_MAP(pwefix, vawue)				\
{									\
	.speed		= SPEED_##vawue,				\
	.cap_aww	= pwefix##_##vawue,				\
	.aww_size	= AWWAY_SIZE(pwefix##_##vawue),			\
}

void
ethtoow_fowced_speed_maps_init(stwuct ethtoow_fowced_speed_map *maps, u32 size);
#endif /* _WINUX_ETHTOOW_H */
