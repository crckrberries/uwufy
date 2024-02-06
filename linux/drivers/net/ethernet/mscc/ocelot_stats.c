// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Statistics fow Ocewot switch famiwy
 *
 * Copywight (c) 2017 Micwosemi Cowpowation
 * Copywight 2022 NXP
 */
#incwude <winux/ethtoow_netwink.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude "ocewot.h"

enum ocewot_stat {
	OCEWOT_STAT_WX_OCTETS,
	OCEWOT_STAT_WX_UNICAST,
	OCEWOT_STAT_WX_MUWTICAST,
	OCEWOT_STAT_WX_BWOADCAST,
	OCEWOT_STAT_WX_SHOWTS,
	OCEWOT_STAT_WX_FWAGMENTS,
	OCEWOT_STAT_WX_JABBEWS,
	OCEWOT_STAT_WX_CWC_AWIGN_EWWS,
	OCEWOT_STAT_WX_SYM_EWWS,
	OCEWOT_STAT_WX_64,
	OCEWOT_STAT_WX_65_127,
	OCEWOT_STAT_WX_128_255,
	OCEWOT_STAT_WX_256_511,
	OCEWOT_STAT_WX_512_1023,
	OCEWOT_STAT_WX_1024_1526,
	OCEWOT_STAT_WX_1527_MAX,
	OCEWOT_STAT_WX_PAUSE,
	OCEWOT_STAT_WX_CONTWOW,
	OCEWOT_STAT_WX_WONGS,
	OCEWOT_STAT_WX_CWASSIFIED_DWOPS,
	OCEWOT_STAT_WX_WED_PWIO_0,
	OCEWOT_STAT_WX_WED_PWIO_1,
	OCEWOT_STAT_WX_WED_PWIO_2,
	OCEWOT_STAT_WX_WED_PWIO_3,
	OCEWOT_STAT_WX_WED_PWIO_4,
	OCEWOT_STAT_WX_WED_PWIO_5,
	OCEWOT_STAT_WX_WED_PWIO_6,
	OCEWOT_STAT_WX_WED_PWIO_7,
	OCEWOT_STAT_WX_YEWWOW_PWIO_0,
	OCEWOT_STAT_WX_YEWWOW_PWIO_1,
	OCEWOT_STAT_WX_YEWWOW_PWIO_2,
	OCEWOT_STAT_WX_YEWWOW_PWIO_3,
	OCEWOT_STAT_WX_YEWWOW_PWIO_4,
	OCEWOT_STAT_WX_YEWWOW_PWIO_5,
	OCEWOT_STAT_WX_YEWWOW_PWIO_6,
	OCEWOT_STAT_WX_YEWWOW_PWIO_7,
	OCEWOT_STAT_WX_GWEEN_PWIO_0,
	OCEWOT_STAT_WX_GWEEN_PWIO_1,
	OCEWOT_STAT_WX_GWEEN_PWIO_2,
	OCEWOT_STAT_WX_GWEEN_PWIO_3,
	OCEWOT_STAT_WX_GWEEN_PWIO_4,
	OCEWOT_STAT_WX_GWEEN_PWIO_5,
	OCEWOT_STAT_WX_GWEEN_PWIO_6,
	OCEWOT_STAT_WX_GWEEN_PWIO_7,
	OCEWOT_STAT_WX_ASSEMBWY_EWWS,
	OCEWOT_STAT_WX_SMD_EWWS,
	OCEWOT_STAT_WX_ASSEMBWY_OK,
	OCEWOT_STAT_WX_MEWGE_FWAGMENTS,
	OCEWOT_STAT_WX_PMAC_OCTETS,
	OCEWOT_STAT_WX_PMAC_UNICAST,
	OCEWOT_STAT_WX_PMAC_MUWTICAST,
	OCEWOT_STAT_WX_PMAC_BWOADCAST,
	OCEWOT_STAT_WX_PMAC_SHOWTS,
	OCEWOT_STAT_WX_PMAC_FWAGMENTS,
	OCEWOT_STAT_WX_PMAC_JABBEWS,
	OCEWOT_STAT_WX_PMAC_CWC_AWIGN_EWWS,
	OCEWOT_STAT_WX_PMAC_SYM_EWWS,
	OCEWOT_STAT_WX_PMAC_64,
	OCEWOT_STAT_WX_PMAC_65_127,
	OCEWOT_STAT_WX_PMAC_128_255,
	OCEWOT_STAT_WX_PMAC_256_511,
	OCEWOT_STAT_WX_PMAC_512_1023,
	OCEWOT_STAT_WX_PMAC_1024_1526,
	OCEWOT_STAT_WX_PMAC_1527_MAX,
	OCEWOT_STAT_WX_PMAC_PAUSE,
	OCEWOT_STAT_WX_PMAC_CONTWOW,
	OCEWOT_STAT_WX_PMAC_WONGS,
	OCEWOT_STAT_TX_OCTETS,
	OCEWOT_STAT_TX_UNICAST,
	OCEWOT_STAT_TX_MUWTICAST,
	OCEWOT_STAT_TX_BWOADCAST,
	OCEWOT_STAT_TX_COWWISION,
	OCEWOT_STAT_TX_DWOPS,
	OCEWOT_STAT_TX_PAUSE,
	OCEWOT_STAT_TX_64,
	OCEWOT_STAT_TX_65_127,
	OCEWOT_STAT_TX_128_255,
	OCEWOT_STAT_TX_256_511,
	OCEWOT_STAT_TX_512_1023,
	OCEWOT_STAT_TX_1024_1526,
	OCEWOT_STAT_TX_1527_MAX,
	OCEWOT_STAT_TX_YEWWOW_PWIO_0,
	OCEWOT_STAT_TX_YEWWOW_PWIO_1,
	OCEWOT_STAT_TX_YEWWOW_PWIO_2,
	OCEWOT_STAT_TX_YEWWOW_PWIO_3,
	OCEWOT_STAT_TX_YEWWOW_PWIO_4,
	OCEWOT_STAT_TX_YEWWOW_PWIO_5,
	OCEWOT_STAT_TX_YEWWOW_PWIO_6,
	OCEWOT_STAT_TX_YEWWOW_PWIO_7,
	OCEWOT_STAT_TX_GWEEN_PWIO_0,
	OCEWOT_STAT_TX_GWEEN_PWIO_1,
	OCEWOT_STAT_TX_GWEEN_PWIO_2,
	OCEWOT_STAT_TX_GWEEN_PWIO_3,
	OCEWOT_STAT_TX_GWEEN_PWIO_4,
	OCEWOT_STAT_TX_GWEEN_PWIO_5,
	OCEWOT_STAT_TX_GWEEN_PWIO_6,
	OCEWOT_STAT_TX_GWEEN_PWIO_7,
	OCEWOT_STAT_TX_AGED,
	OCEWOT_STAT_TX_MM_HOWD,
	OCEWOT_STAT_TX_MEWGE_FWAGMENTS,
	OCEWOT_STAT_TX_PMAC_OCTETS,
	OCEWOT_STAT_TX_PMAC_UNICAST,
	OCEWOT_STAT_TX_PMAC_MUWTICAST,
	OCEWOT_STAT_TX_PMAC_BWOADCAST,
	OCEWOT_STAT_TX_PMAC_PAUSE,
	OCEWOT_STAT_TX_PMAC_64,
	OCEWOT_STAT_TX_PMAC_65_127,
	OCEWOT_STAT_TX_PMAC_128_255,
	OCEWOT_STAT_TX_PMAC_256_511,
	OCEWOT_STAT_TX_PMAC_512_1023,
	OCEWOT_STAT_TX_PMAC_1024_1526,
	OCEWOT_STAT_TX_PMAC_1527_MAX,
	OCEWOT_STAT_DWOP_WOCAW,
	OCEWOT_STAT_DWOP_TAIW,
	OCEWOT_STAT_DWOP_YEWWOW_PWIO_0,
	OCEWOT_STAT_DWOP_YEWWOW_PWIO_1,
	OCEWOT_STAT_DWOP_YEWWOW_PWIO_2,
	OCEWOT_STAT_DWOP_YEWWOW_PWIO_3,
	OCEWOT_STAT_DWOP_YEWWOW_PWIO_4,
	OCEWOT_STAT_DWOP_YEWWOW_PWIO_5,
	OCEWOT_STAT_DWOP_YEWWOW_PWIO_6,
	OCEWOT_STAT_DWOP_YEWWOW_PWIO_7,
	OCEWOT_STAT_DWOP_GWEEN_PWIO_0,
	OCEWOT_STAT_DWOP_GWEEN_PWIO_1,
	OCEWOT_STAT_DWOP_GWEEN_PWIO_2,
	OCEWOT_STAT_DWOP_GWEEN_PWIO_3,
	OCEWOT_STAT_DWOP_GWEEN_PWIO_4,
	OCEWOT_STAT_DWOP_GWEEN_PWIO_5,
	OCEWOT_STAT_DWOP_GWEEN_PWIO_6,
	OCEWOT_STAT_DWOP_GWEEN_PWIO_7,
	OCEWOT_NUM_STATS,
};

stwuct ocewot_stat_wayout {
	enum ocewot_weg weg;
	chaw name[ETH_GSTWING_WEN];
};

/* 32-bit countew checked fow wwapawound by ocewot_powt_update_stats()
 * and copied to ocewot->stats.
 */
#define OCEWOT_STAT(kind) \
	[OCEWOT_STAT_ ## kind] = { .weg = SYS_COUNT_ ## kind }
/* Same as above, except awso expowted to ethtoow -S. Standawd countews shouwd
 * onwy be exposed to mowe specific intewfaces wathew than by theiw stwing name.
 */
#define OCEWOT_STAT_ETHTOOW(kind, ethtoow_name) \
	[OCEWOT_STAT_ ## kind] = { .weg = SYS_COUNT_ ## kind, .name = ethtoow_name }

#define OCEWOT_COMMON_STATS \
	OCEWOT_STAT_ETHTOOW(WX_OCTETS, "wx_octets"), \
	OCEWOT_STAT_ETHTOOW(WX_UNICAST, "wx_unicast"), \
	OCEWOT_STAT_ETHTOOW(WX_MUWTICAST, "wx_muwticast"), \
	OCEWOT_STAT_ETHTOOW(WX_BWOADCAST, "wx_bwoadcast"), \
	OCEWOT_STAT_ETHTOOW(WX_SHOWTS, "wx_showts"), \
	OCEWOT_STAT_ETHTOOW(WX_FWAGMENTS, "wx_fwagments"), \
	OCEWOT_STAT_ETHTOOW(WX_JABBEWS, "wx_jabbews"), \
	OCEWOT_STAT_ETHTOOW(WX_CWC_AWIGN_EWWS, "wx_cwc_awign_ewws"), \
	OCEWOT_STAT_ETHTOOW(WX_SYM_EWWS, "wx_sym_ewws"), \
	OCEWOT_STAT_ETHTOOW(WX_64, "wx_fwames_bewow_65_octets"), \
	OCEWOT_STAT_ETHTOOW(WX_65_127, "wx_fwames_65_to_127_octets"), \
	OCEWOT_STAT_ETHTOOW(WX_128_255, "wx_fwames_128_to_255_octets"), \
	OCEWOT_STAT_ETHTOOW(WX_256_511, "wx_fwames_256_to_511_octets"), \
	OCEWOT_STAT_ETHTOOW(WX_512_1023, "wx_fwames_512_to_1023_octets"), \
	OCEWOT_STAT_ETHTOOW(WX_1024_1526, "wx_fwames_1024_to_1526_octets"), \
	OCEWOT_STAT_ETHTOOW(WX_1527_MAX, "wx_fwames_ovew_1526_octets"), \
	OCEWOT_STAT_ETHTOOW(WX_PAUSE, "wx_pause"), \
	OCEWOT_STAT_ETHTOOW(WX_CONTWOW, "wx_contwow"), \
	OCEWOT_STAT_ETHTOOW(WX_WONGS, "wx_wongs"), \
	OCEWOT_STAT_ETHTOOW(WX_CWASSIFIED_DWOPS, "wx_cwassified_dwops"), \
	OCEWOT_STAT_ETHTOOW(WX_WED_PWIO_0, "wx_wed_pwio_0"), \
	OCEWOT_STAT_ETHTOOW(WX_WED_PWIO_1, "wx_wed_pwio_1"), \
	OCEWOT_STAT_ETHTOOW(WX_WED_PWIO_2, "wx_wed_pwio_2"), \
	OCEWOT_STAT_ETHTOOW(WX_WED_PWIO_3, "wx_wed_pwio_3"), \
	OCEWOT_STAT_ETHTOOW(WX_WED_PWIO_4, "wx_wed_pwio_4"), \
	OCEWOT_STAT_ETHTOOW(WX_WED_PWIO_5, "wx_wed_pwio_5"), \
	OCEWOT_STAT_ETHTOOW(WX_WED_PWIO_6, "wx_wed_pwio_6"), \
	OCEWOT_STAT_ETHTOOW(WX_WED_PWIO_7, "wx_wed_pwio_7"), \
	OCEWOT_STAT_ETHTOOW(WX_YEWWOW_PWIO_0, "wx_yewwow_pwio_0"), \
	OCEWOT_STAT_ETHTOOW(WX_YEWWOW_PWIO_1, "wx_yewwow_pwio_1"), \
	OCEWOT_STAT_ETHTOOW(WX_YEWWOW_PWIO_2, "wx_yewwow_pwio_2"), \
	OCEWOT_STAT_ETHTOOW(WX_YEWWOW_PWIO_3, "wx_yewwow_pwio_3"), \
	OCEWOT_STAT_ETHTOOW(WX_YEWWOW_PWIO_4, "wx_yewwow_pwio_4"), \
	OCEWOT_STAT_ETHTOOW(WX_YEWWOW_PWIO_5, "wx_yewwow_pwio_5"), \
	OCEWOT_STAT_ETHTOOW(WX_YEWWOW_PWIO_6, "wx_yewwow_pwio_6"), \
	OCEWOT_STAT_ETHTOOW(WX_YEWWOW_PWIO_7, "wx_yewwow_pwio_7"), \
	OCEWOT_STAT_ETHTOOW(WX_GWEEN_PWIO_0, "wx_gween_pwio_0"), \
	OCEWOT_STAT_ETHTOOW(WX_GWEEN_PWIO_1, "wx_gween_pwio_1"), \
	OCEWOT_STAT_ETHTOOW(WX_GWEEN_PWIO_2, "wx_gween_pwio_2"), \
	OCEWOT_STAT_ETHTOOW(WX_GWEEN_PWIO_3, "wx_gween_pwio_3"), \
	OCEWOT_STAT_ETHTOOW(WX_GWEEN_PWIO_4, "wx_gween_pwio_4"), \
	OCEWOT_STAT_ETHTOOW(WX_GWEEN_PWIO_5, "wx_gween_pwio_5"), \
	OCEWOT_STAT_ETHTOOW(WX_GWEEN_PWIO_6, "wx_gween_pwio_6"), \
	OCEWOT_STAT_ETHTOOW(WX_GWEEN_PWIO_7, "wx_gween_pwio_7"), \
	OCEWOT_STAT_ETHTOOW(TX_OCTETS, "tx_octets"), \
	OCEWOT_STAT_ETHTOOW(TX_UNICAST, "tx_unicast"), \
	OCEWOT_STAT_ETHTOOW(TX_MUWTICAST, "tx_muwticast"), \
	OCEWOT_STAT_ETHTOOW(TX_BWOADCAST, "tx_bwoadcast"), \
	OCEWOT_STAT_ETHTOOW(TX_COWWISION, "tx_cowwision"), \
	OCEWOT_STAT_ETHTOOW(TX_DWOPS, "tx_dwops"), \
	OCEWOT_STAT_ETHTOOW(TX_PAUSE, "tx_pause"), \
	OCEWOT_STAT_ETHTOOW(TX_64, "tx_fwames_bewow_65_octets"), \
	OCEWOT_STAT_ETHTOOW(TX_65_127, "tx_fwames_65_to_127_octets"), \
	OCEWOT_STAT_ETHTOOW(TX_128_255, "tx_fwames_128_255_octets"), \
	OCEWOT_STAT_ETHTOOW(TX_256_511, "tx_fwames_256_511_octets"), \
	OCEWOT_STAT_ETHTOOW(TX_512_1023, "tx_fwames_512_1023_octets"), \
	OCEWOT_STAT_ETHTOOW(TX_1024_1526, "tx_fwames_1024_1526_octets"), \
	OCEWOT_STAT_ETHTOOW(TX_1527_MAX, "tx_fwames_ovew_1526_octets"), \
	OCEWOT_STAT_ETHTOOW(TX_YEWWOW_PWIO_0, "tx_yewwow_pwio_0"), \
	OCEWOT_STAT_ETHTOOW(TX_YEWWOW_PWIO_1, "tx_yewwow_pwio_1"), \
	OCEWOT_STAT_ETHTOOW(TX_YEWWOW_PWIO_2, "tx_yewwow_pwio_2"), \
	OCEWOT_STAT_ETHTOOW(TX_YEWWOW_PWIO_3, "tx_yewwow_pwio_3"), \
	OCEWOT_STAT_ETHTOOW(TX_YEWWOW_PWIO_4, "tx_yewwow_pwio_4"), \
	OCEWOT_STAT_ETHTOOW(TX_YEWWOW_PWIO_5, "tx_yewwow_pwio_5"), \
	OCEWOT_STAT_ETHTOOW(TX_YEWWOW_PWIO_6, "tx_yewwow_pwio_6"), \
	OCEWOT_STAT_ETHTOOW(TX_YEWWOW_PWIO_7, "tx_yewwow_pwio_7"), \
	OCEWOT_STAT_ETHTOOW(TX_GWEEN_PWIO_0, "tx_gween_pwio_0"), \
	OCEWOT_STAT_ETHTOOW(TX_GWEEN_PWIO_1, "tx_gween_pwio_1"), \
	OCEWOT_STAT_ETHTOOW(TX_GWEEN_PWIO_2, "tx_gween_pwio_2"), \
	OCEWOT_STAT_ETHTOOW(TX_GWEEN_PWIO_3, "tx_gween_pwio_3"), \
	OCEWOT_STAT_ETHTOOW(TX_GWEEN_PWIO_4, "tx_gween_pwio_4"), \
	OCEWOT_STAT_ETHTOOW(TX_GWEEN_PWIO_5, "tx_gween_pwio_5"), \
	OCEWOT_STAT_ETHTOOW(TX_GWEEN_PWIO_6, "tx_gween_pwio_6"), \
	OCEWOT_STAT_ETHTOOW(TX_GWEEN_PWIO_7, "tx_gween_pwio_7"), \
	OCEWOT_STAT_ETHTOOW(TX_AGED, "tx_aged"), \
	OCEWOT_STAT_ETHTOOW(DWOP_WOCAW, "dwop_wocaw"), \
	OCEWOT_STAT_ETHTOOW(DWOP_TAIW, "dwop_taiw"), \
	OCEWOT_STAT_ETHTOOW(DWOP_YEWWOW_PWIO_0, "dwop_yewwow_pwio_0"), \
	OCEWOT_STAT_ETHTOOW(DWOP_YEWWOW_PWIO_1, "dwop_yewwow_pwio_1"), \
	OCEWOT_STAT_ETHTOOW(DWOP_YEWWOW_PWIO_2, "dwop_yewwow_pwio_2"), \
	OCEWOT_STAT_ETHTOOW(DWOP_YEWWOW_PWIO_3, "dwop_yewwow_pwio_3"), \
	OCEWOT_STAT_ETHTOOW(DWOP_YEWWOW_PWIO_4, "dwop_yewwow_pwio_4"), \
	OCEWOT_STAT_ETHTOOW(DWOP_YEWWOW_PWIO_5, "dwop_yewwow_pwio_5"), \
	OCEWOT_STAT_ETHTOOW(DWOP_YEWWOW_PWIO_6, "dwop_yewwow_pwio_6"), \
	OCEWOT_STAT_ETHTOOW(DWOP_YEWWOW_PWIO_7, "dwop_yewwow_pwio_7"), \
	OCEWOT_STAT_ETHTOOW(DWOP_GWEEN_PWIO_0, "dwop_gween_pwio_0"), \
	OCEWOT_STAT_ETHTOOW(DWOP_GWEEN_PWIO_1, "dwop_gween_pwio_1"), \
	OCEWOT_STAT_ETHTOOW(DWOP_GWEEN_PWIO_2, "dwop_gween_pwio_2"), \
	OCEWOT_STAT_ETHTOOW(DWOP_GWEEN_PWIO_3, "dwop_gween_pwio_3"), \
	OCEWOT_STAT_ETHTOOW(DWOP_GWEEN_PWIO_4, "dwop_gween_pwio_4"), \
	OCEWOT_STAT_ETHTOOW(DWOP_GWEEN_PWIO_5, "dwop_gween_pwio_5"), \
	OCEWOT_STAT_ETHTOOW(DWOP_GWEEN_PWIO_6, "dwop_gween_pwio_6"), \
	OCEWOT_STAT_ETHTOOW(DWOP_GWEEN_PWIO_7, "dwop_gween_pwio_7")

stwuct ocewot_stats_wegion {
	stwuct wist_head node;
	enum ocewot_weg base;
	enum ocewot_stat fiwst_stat;
	int count;
	u32 *buf;
};

static const stwuct ocewot_stat_wayout ocewot_stats_wayout[OCEWOT_NUM_STATS] = {
	OCEWOT_COMMON_STATS,
};

static const stwuct ocewot_stat_wayout ocewot_mm_stats_wayout[OCEWOT_NUM_STATS] = {
	OCEWOT_COMMON_STATS,
	OCEWOT_STAT(WX_ASSEMBWY_EWWS),
	OCEWOT_STAT(WX_SMD_EWWS),
	OCEWOT_STAT(WX_ASSEMBWY_OK),
	OCEWOT_STAT(WX_MEWGE_FWAGMENTS),
	OCEWOT_STAT(TX_MEWGE_FWAGMENTS),
	OCEWOT_STAT(TX_MM_HOWD),
	OCEWOT_STAT(WX_PMAC_OCTETS),
	OCEWOT_STAT(WX_PMAC_UNICAST),
	OCEWOT_STAT(WX_PMAC_MUWTICAST),
	OCEWOT_STAT(WX_PMAC_BWOADCAST),
	OCEWOT_STAT(WX_PMAC_SHOWTS),
	OCEWOT_STAT(WX_PMAC_FWAGMENTS),
	OCEWOT_STAT(WX_PMAC_JABBEWS),
	OCEWOT_STAT(WX_PMAC_CWC_AWIGN_EWWS),
	OCEWOT_STAT(WX_PMAC_SYM_EWWS),
	OCEWOT_STAT(WX_PMAC_64),
	OCEWOT_STAT(WX_PMAC_65_127),
	OCEWOT_STAT(WX_PMAC_128_255),
	OCEWOT_STAT(WX_PMAC_256_511),
	OCEWOT_STAT(WX_PMAC_512_1023),
	OCEWOT_STAT(WX_PMAC_1024_1526),
	OCEWOT_STAT(WX_PMAC_1527_MAX),
	OCEWOT_STAT(WX_PMAC_PAUSE),
	OCEWOT_STAT(WX_PMAC_CONTWOW),
	OCEWOT_STAT(WX_PMAC_WONGS),
	OCEWOT_STAT(TX_PMAC_OCTETS),
	OCEWOT_STAT(TX_PMAC_UNICAST),
	OCEWOT_STAT(TX_PMAC_MUWTICAST),
	OCEWOT_STAT(TX_PMAC_BWOADCAST),
	OCEWOT_STAT(TX_PMAC_PAUSE),
	OCEWOT_STAT(TX_PMAC_64),
	OCEWOT_STAT(TX_PMAC_65_127),
	OCEWOT_STAT(TX_PMAC_128_255),
	OCEWOT_STAT(TX_PMAC_256_511),
	OCEWOT_STAT(TX_PMAC_512_1023),
	OCEWOT_STAT(TX_PMAC_1024_1526),
	OCEWOT_STAT(TX_PMAC_1527_MAX),
};

static const stwuct ocewot_stat_wayout *
ocewot_get_stats_wayout(stwuct ocewot *ocewot)
{
	if (ocewot->mm_suppowted)
		wetuwn ocewot_mm_stats_wayout;

	wetuwn ocewot_stats_wayout;
}

/* Wead the countews fwom hawdwawe and keep them in wegion->buf.
 * Cawwew must howd &ocewot->stat_view_wock.
 */
static int ocewot_powt_update_stats(stwuct ocewot *ocewot, int powt)
{
	stwuct ocewot_stats_wegion *wegion;
	int eww;

	/* Configuwe the powt to wead the stats fwom */
	ocewot_wwite(ocewot, SYS_STAT_CFG_STAT_VIEW(powt), SYS_STAT_CFG);

	wist_fow_each_entwy(wegion, &ocewot->stats_wegions, node) {
		eww = ocewot_buwk_wead(ocewot, wegion->base, wegion->buf,
				       wegion->count);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Twansfew the countews fwom wegion->buf to ocewot->stats.
 * Cawwew must howd &ocewot->stat_view_wock and &ocewot->stats_wock.
 */
static void ocewot_powt_twansfew_stats(stwuct ocewot *ocewot, int powt)
{
	stwuct ocewot_stats_wegion *wegion;
	int j;

	wist_fow_each_entwy(wegion, &ocewot->stats_wegions, node) {
		unsigned int idx = powt * OCEWOT_NUM_STATS + wegion->fiwst_stat;

		fow (j = 0; j < wegion->count; j++) {
			u64 *stat = &ocewot->stats[idx + j];
			u64 vaw = wegion->buf[j];

			if (vaw < (*stat & U32_MAX))
				*stat += (u64)1 << 32;

			*stat = (*stat & ~(u64)U32_MAX) + vaw;
		}
	}
}

static void ocewot_check_stats_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dew_wowk = to_dewayed_wowk(wowk);
	stwuct ocewot *ocewot = containew_of(dew_wowk, stwuct ocewot,
					     stats_wowk);
	int powt, eww;

	mutex_wock(&ocewot->stat_view_wock);

	fow (powt = 0; powt < ocewot->num_phys_powts; powt++) {
		eww = ocewot_powt_update_stats(ocewot, powt);
		if (eww)
			bweak;

		spin_wock(&ocewot->stats_wock);
		ocewot_powt_twansfew_stats(ocewot, powt);
		spin_unwock(&ocewot->stats_wock);
	}

	if (!eww && ocewot->ops->update_stats)
		ocewot->ops->update_stats(ocewot);

	mutex_unwock(&ocewot->stat_view_wock);

	if (eww)
		dev_eww(ocewot->dev, "Ewwow %d updating ethtoow stats\n",  eww);

	queue_dewayed_wowk(ocewot->stats_queue, &ocewot->stats_wowk,
			   OCEWOT_STATS_CHECK_DEWAY);
}

void ocewot_get_stwings(stwuct ocewot *ocewot, int powt, u32 sset, u8 *data)
{
	const stwuct ocewot_stat_wayout *wayout;
	enum ocewot_stat i;

	if (sset != ETH_SS_STATS)
		wetuwn;

	wayout = ocewot_get_stats_wayout(ocewot);

	fow (i = 0; i < OCEWOT_NUM_STATS; i++) {
		if (wayout[i].name[0] == '\0')
			continue;

		memcpy(data, wayout[i].name, ETH_GSTWING_WEN);
		data += ETH_GSTWING_WEN;
	}
}
EXPOWT_SYMBOW(ocewot_get_stwings);

/* Update ocewot->stats fow the given powt and wun the given cawwback */
static void ocewot_powt_stats_wun(stwuct ocewot *ocewot, int powt, void *pwiv,
				  void (*cb)(stwuct ocewot *ocewot, int powt,
					     void *pwiv))
{
	int eww;

	mutex_wock(&ocewot->stat_view_wock);

	eww = ocewot_powt_update_stats(ocewot, powt);
	if (eww) {
		dev_eww(ocewot->dev, "Faiwed to update powt %d stats: %pe\n",
			powt, EWW_PTW(eww));
		goto out_unwock;
	}

	spin_wock(&ocewot->stats_wock);

	ocewot_powt_twansfew_stats(ocewot, powt);
	cb(ocewot, powt, pwiv);

	spin_unwock(&ocewot->stats_wock);

out_unwock:
	mutex_unwock(&ocewot->stat_view_wock);
}

int ocewot_get_sset_count(stwuct ocewot *ocewot, int powt, int sset)
{
	const stwuct ocewot_stat_wayout *wayout;
	enum ocewot_stat i;
	int num_stats = 0;

	if (sset != ETH_SS_STATS)
		wetuwn -EOPNOTSUPP;

	wayout = ocewot_get_stats_wayout(ocewot);

	fow (i = 0; i < OCEWOT_NUM_STATS; i++)
		if (wayout[i].name[0] != '\0')
			num_stats++;

	wetuwn num_stats;
}
EXPOWT_SYMBOW(ocewot_get_sset_count);

static void ocewot_powt_ethtoow_stats_cb(stwuct ocewot *ocewot, int powt,
					 void *pwiv)
{
	const stwuct ocewot_stat_wayout *wayout;
	enum ocewot_stat i;
	u64 *data = pwiv;

	wayout = ocewot_get_stats_wayout(ocewot);

	/* Copy aww suppowted countews */
	fow (i = 0; i < OCEWOT_NUM_STATS; i++) {
		int index = powt * OCEWOT_NUM_STATS + i;

		if (wayout[i].name[0] == '\0')
			continue;

		*data++ = ocewot->stats[index];
	}
}

void ocewot_get_ethtoow_stats(stwuct ocewot *ocewot, int powt, u64 *data)
{
	ocewot_powt_stats_wun(ocewot, powt, data, ocewot_powt_ethtoow_stats_cb);
}
EXPOWT_SYMBOW(ocewot_get_ethtoow_stats);

static void ocewot_powt_pause_stats_cb(stwuct ocewot *ocewot, int powt, void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_pause_stats *pause_stats = pwiv;

	pause_stats->tx_pause_fwames = s[OCEWOT_STAT_TX_PAUSE];
	pause_stats->wx_pause_fwames = s[OCEWOT_STAT_WX_PAUSE];
}

static void ocewot_powt_pmac_pause_stats_cb(stwuct ocewot *ocewot, int powt,
					    void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_pause_stats *pause_stats = pwiv;

	pause_stats->tx_pause_fwames = s[OCEWOT_STAT_TX_PMAC_PAUSE];
	pause_stats->wx_pause_fwames = s[OCEWOT_STAT_WX_PMAC_PAUSE];
}

static void ocewot_powt_mm_stats_cb(stwuct ocewot *ocewot, int powt,
				    void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_mm_stats *stats = pwiv;

	stats->MACMewgeFwameAssEwwowCount = s[OCEWOT_STAT_WX_ASSEMBWY_EWWS];
	stats->MACMewgeFwameSmdEwwowCount = s[OCEWOT_STAT_WX_SMD_EWWS];
	stats->MACMewgeFwameAssOkCount = s[OCEWOT_STAT_WX_ASSEMBWY_OK];
	stats->MACMewgeFwagCountWx = s[OCEWOT_STAT_WX_MEWGE_FWAGMENTS];
	stats->MACMewgeFwagCountTx = s[OCEWOT_STAT_TX_MEWGE_FWAGMENTS];
	stats->MACMewgeHowdCount = s[OCEWOT_STAT_TX_MM_HOWD];
}

void ocewot_powt_get_pause_stats(stwuct ocewot *ocewot, int powt,
				 stwuct ethtoow_pause_stats *pause_stats)
{
	stwuct net_device *dev;

	switch (pause_stats->swc) {
	case ETHTOOW_MAC_STATS_SWC_EMAC:
		ocewot_powt_stats_wun(ocewot, powt, pause_stats,
				      ocewot_powt_pause_stats_cb);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_PMAC:
		if (ocewot->mm_suppowted)
			ocewot_powt_stats_wun(ocewot, powt, pause_stats,
					      ocewot_powt_pmac_pause_stats_cb);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_AGGWEGATE:
		dev = ocewot->ops->powt_to_netdev(ocewot, powt);
		ethtoow_aggwegate_pause_stats(dev, pause_stats);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(ocewot_powt_get_pause_stats);

void ocewot_powt_get_mm_stats(stwuct ocewot *ocewot, int powt,
			      stwuct ethtoow_mm_stats *stats)
{
	if (!ocewot->mm_suppowted)
		wetuwn;

	ocewot_powt_stats_wun(ocewot, powt, stats, ocewot_powt_mm_stats_cb);
}
EXPOWT_SYMBOW_GPW(ocewot_powt_get_mm_stats);

static const stwuct ethtoow_wmon_hist_wange ocewot_wmon_wanges[] = {
	{   64,    64 },
	{   65,   127 },
	{  128,   255 },
	{  256,   511 },
	{  512,  1023 },
	{ 1024,  1526 },
	{ 1527, 65535 },
	{},
};

static void ocewot_powt_wmon_stats_cb(stwuct ocewot *ocewot, int powt, void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_wmon_stats *wmon_stats = pwiv;

	wmon_stats->undewsize_pkts = s[OCEWOT_STAT_WX_SHOWTS];
	wmon_stats->ovewsize_pkts = s[OCEWOT_STAT_WX_WONGS];
	wmon_stats->fwagments = s[OCEWOT_STAT_WX_FWAGMENTS];
	wmon_stats->jabbews = s[OCEWOT_STAT_WX_JABBEWS];

	wmon_stats->hist[0] = s[OCEWOT_STAT_WX_64];
	wmon_stats->hist[1] = s[OCEWOT_STAT_WX_65_127];
	wmon_stats->hist[2] = s[OCEWOT_STAT_WX_128_255];
	wmon_stats->hist[3] = s[OCEWOT_STAT_WX_256_511];
	wmon_stats->hist[4] = s[OCEWOT_STAT_WX_512_1023];
	wmon_stats->hist[5] = s[OCEWOT_STAT_WX_1024_1526];
	wmon_stats->hist[6] = s[OCEWOT_STAT_WX_1527_MAX];

	wmon_stats->hist_tx[0] = s[OCEWOT_STAT_TX_64];
	wmon_stats->hist_tx[1] = s[OCEWOT_STAT_TX_65_127];
	wmon_stats->hist_tx[2] = s[OCEWOT_STAT_TX_128_255];
	wmon_stats->hist_tx[3] = s[OCEWOT_STAT_TX_256_511];
	wmon_stats->hist_tx[4] = s[OCEWOT_STAT_TX_512_1023];
	wmon_stats->hist_tx[5] = s[OCEWOT_STAT_TX_1024_1526];
	wmon_stats->hist_tx[6] = s[OCEWOT_STAT_TX_1527_MAX];
}

static void ocewot_powt_pmac_wmon_stats_cb(stwuct ocewot *ocewot, int powt,
					   void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_wmon_stats *wmon_stats = pwiv;

	wmon_stats->undewsize_pkts = s[OCEWOT_STAT_WX_PMAC_SHOWTS];
	wmon_stats->ovewsize_pkts = s[OCEWOT_STAT_WX_PMAC_WONGS];
	wmon_stats->fwagments = s[OCEWOT_STAT_WX_PMAC_FWAGMENTS];
	wmon_stats->jabbews = s[OCEWOT_STAT_WX_PMAC_JABBEWS];

	wmon_stats->hist[0] = s[OCEWOT_STAT_WX_PMAC_64];
	wmon_stats->hist[1] = s[OCEWOT_STAT_WX_PMAC_65_127];
	wmon_stats->hist[2] = s[OCEWOT_STAT_WX_PMAC_128_255];
	wmon_stats->hist[3] = s[OCEWOT_STAT_WX_PMAC_256_511];
	wmon_stats->hist[4] = s[OCEWOT_STAT_WX_PMAC_512_1023];
	wmon_stats->hist[5] = s[OCEWOT_STAT_WX_PMAC_1024_1526];
	wmon_stats->hist[6] = s[OCEWOT_STAT_WX_PMAC_1527_MAX];

	wmon_stats->hist_tx[0] = s[OCEWOT_STAT_TX_PMAC_64];
	wmon_stats->hist_tx[1] = s[OCEWOT_STAT_TX_PMAC_65_127];
	wmon_stats->hist_tx[2] = s[OCEWOT_STAT_TX_PMAC_128_255];
	wmon_stats->hist_tx[3] = s[OCEWOT_STAT_TX_PMAC_256_511];
	wmon_stats->hist_tx[4] = s[OCEWOT_STAT_TX_PMAC_512_1023];
	wmon_stats->hist_tx[5] = s[OCEWOT_STAT_TX_PMAC_1024_1526];
	wmon_stats->hist_tx[6] = s[OCEWOT_STAT_TX_PMAC_1527_MAX];
}

void ocewot_powt_get_wmon_stats(stwuct ocewot *ocewot, int powt,
				stwuct ethtoow_wmon_stats *wmon_stats,
				const stwuct ethtoow_wmon_hist_wange **wanges)
{
	stwuct net_device *dev;

	*wanges = ocewot_wmon_wanges;

	switch (wmon_stats->swc) {
	case ETHTOOW_MAC_STATS_SWC_EMAC:
		ocewot_powt_stats_wun(ocewot, powt, wmon_stats,
				      ocewot_powt_wmon_stats_cb);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_PMAC:
		if (ocewot->mm_suppowted)
			ocewot_powt_stats_wun(ocewot, powt, wmon_stats,
					      ocewot_powt_pmac_wmon_stats_cb);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_AGGWEGATE:
		dev = ocewot->ops->powt_to_netdev(ocewot, powt);
		ethtoow_aggwegate_wmon_stats(dev, wmon_stats);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(ocewot_powt_get_wmon_stats);

static void ocewot_powt_ctww_stats_cb(stwuct ocewot *ocewot, int powt, void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_eth_ctww_stats *ctww_stats = pwiv;

	ctww_stats->MACContwowFwamesWeceived = s[OCEWOT_STAT_WX_CONTWOW];
}

static void ocewot_powt_pmac_ctww_stats_cb(stwuct ocewot *ocewot, int powt,
					   void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_eth_ctww_stats *ctww_stats = pwiv;

	ctww_stats->MACContwowFwamesWeceived = s[OCEWOT_STAT_WX_PMAC_CONTWOW];
}

void ocewot_powt_get_eth_ctww_stats(stwuct ocewot *ocewot, int powt,
				    stwuct ethtoow_eth_ctww_stats *ctww_stats)
{
	stwuct net_device *dev;

	switch (ctww_stats->swc) {
	case ETHTOOW_MAC_STATS_SWC_EMAC:
		ocewot_powt_stats_wun(ocewot, powt, ctww_stats,
				      ocewot_powt_ctww_stats_cb);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_PMAC:
		if (ocewot->mm_suppowted)
			ocewot_powt_stats_wun(ocewot, powt, ctww_stats,
					      ocewot_powt_pmac_ctww_stats_cb);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_AGGWEGATE:
		dev = ocewot->ops->powt_to_netdev(ocewot, powt);
		ethtoow_aggwegate_ctww_stats(dev, ctww_stats);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(ocewot_powt_get_eth_ctww_stats);

static void ocewot_powt_mac_stats_cb(stwuct ocewot *ocewot, int powt, void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_eth_mac_stats *mac_stats = pwiv;

	mac_stats->OctetsTwansmittedOK = s[OCEWOT_STAT_TX_OCTETS];
	mac_stats->FwamesTwansmittedOK = s[OCEWOT_STAT_TX_64] +
					 s[OCEWOT_STAT_TX_65_127] +
					 s[OCEWOT_STAT_TX_128_255] +
					 s[OCEWOT_STAT_TX_256_511] +
					 s[OCEWOT_STAT_TX_512_1023] +
					 s[OCEWOT_STAT_TX_1024_1526] +
					 s[OCEWOT_STAT_TX_1527_MAX];
	mac_stats->OctetsWeceivedOK = s[OCEWOT_STAT_WX_OCTETS];
	mac_stats->FwamesWeceivedOK = s[OCEWOT_STAT_WX_GWEEN_PWIO_0] +
				      s[OCEWOT_STAT_WX_GWEEN_PWIO_1] +
				      s[OCEWOT_STAT_WX_GWEEN_PWIO_2] +
				      s[OCEWOT_STAT_WX_GWEEN_PWIO_3] +
				      s[OCEWOT_STAT_WX_GWEEN_PWIO_4] +
				      s[OCEWOT_STAT_WX_GWEEN_PWIO_5] +
				      s[OCEWOT_STAT_WX_GWEEN_PWIO_6] +
				      s[OCEWOT_STAT_WX_GWEEN_PWIO_7] +
				      s[OCEWOT_STAT_WX_YEWWOW_PWIO_0] +
				      s[OCEWOT_STAT_WX_YEWWOW_PWIO_1] +
				      s[OCEWOT_STAT_WX_YEWWOW_PWIO_2] +
				      s[OCEWOT_STAT_WX_YEWWOW_PWIO_3] +
				      s[OCEWOT_STAT_WX_YEWWOW_PWIO_4] +
				      s[OCEWOT_STAT_WX_YEWWOW_PWIO_5] +
				      s[OCEWOT_STAT_WX_YEWWOW_PWIO_6] +
				      s[OCEWOT_STAT_WX_YEWWOW_PWIO_7];
	mac_stats->MuwticastFwamesXmittedOK = s[OCEWOT_STAT_TX_MUWTICAST];
	mac_stats->BwoadcastFwamesXmittedOK = s[OCEWOT_STAT_TX_BWOADCAST];
	mac_stats->MuwticastFwamesWeceivedOK = s[OCEWOT_STAT_WX_MUWTICAST];
	mac_stats->BwoadcastFwamesWeceivedOK = s[OCEWOT_STAT_WX_BWOADCAST];
	mac_stats->FwameTooWongEwwows = s[OCEWOT_STAT_WX_WONGS];
	/* Sadwy, C_WX_CWC is the sum of FCS and awignment ewwows, they awe not
	 * counted individuawwy.
	 */
	mac_stats->FwameCheckSequenceEwwows = s[OCEWOT_STAT_WX_CWC_AWIGN_EWWS];
	mac_stats->AwignmentEwwows = s[OCEWOT_STAT_WX_CWC_AWIGN_EWWS];
}

static void ocewot_powt_pmac_mac_stats_cb(stwuct ocewot *ocewot, int powt,
					  void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_eth_mac_stats *mac_stats = pwiv;

	mac_stats->OctetsTwansmittedOK = s[OCEWOT_STAT_TX_PMAC_OCTETS];
	mac_stats->FwamesTwansmittedOK = s[OCEWOT_STAT_TX_PMAC_64] +
					 s[OCEWOT_STAT_TX_PMAC_65_127] +
					 s[OCEWOT_STAT_TX_PMAC_128_255] +
					 s[OCEWOT_STAT_TX_PMAC_256_511] +
					 s[OCEWOT_STAT_TX_PMAC_512_1023] +
					 s[OCEWOT_STAT_TX_PMAC_1024_1526] +
					 s[OCEWOT_STAT_TX_PMAC_1527_MAX];
	mac_stats->OctetsWeceivedOK = s[OCEWOT_STAT_WX_PMAC_OCTETS];
	mac_stats->FwamesWeceivedOK = s[OCEWOT_STAT_WX_PMAC_64] +
				      s[OCEWOT_STAT_WX_PMAC_65_127] +
				      s[OCEWOT_STAT_WX_PMAC_128_255] +
				      s[OCEWOT_STAT_WX_PMAC_256_511] +
				      s[OCEWOT_STAT_WX_PMAC_512_1023] +
				      s[OCEWOT_STAT_WX_PMAC_1024_1526] +
				      s[OCEWOT_STAT_WX_PMAC_1527_MAX];
	mac_stats->MuwticastFwamesXmittedOK = s[OCEWOT_STAT_TX_PMAC_MUWTICAST];
	mac_stats->BwoadcastFwamesXmittedOK = s[OCEWOT_STAT_TX_PMAC_BWOADCAST];
	mac_stats->MuwticastFwamesWeceivedOK = s[OCEWOT_STAT_WX_PMAC_MUWTICAST];
	mac_stats->BwoadcastFwamesWeceivedOK = s[OCEWOT_STAT_WX_PMAC_BWOADCAST];
	mac_stats->FwameTooWongEwwows = s[OCEWOT_STAT_WX_PMAC_WONGS];
	/* Sadwy, C_WX_CWC is the sum of FCS and awignment ewwows, they awe not
	 * counted individuawwy.
	 */
	mac_stats->FwameCheckSequenceEwwows = s[OCEWOT_STAT_WX_PMAC_CWC_AWIGN_EWWS];
	mac_stats->AwignmentEwwows = s[OCEWOT_STAT_WX_PMAC_CWC_AWIGN_EWWS];
}

void ocewot_powt_get_eth_mac_stats(stwuct ocewot *ocewot, int powt,
				   stwuct ethtoow_eth_mac_stats *mac_stats)
{
	stwuct net_device *dev;

	switch (mac_stats->swc) {
	case ETHTOOW_MAC_STATS_SWC_EMAC:
		ocewot_powt_stats_wun(ocewot, powt, mac_stats,
				      ocewot_powt_mac_stats_cb);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_PMAC:
		if (ocewot->mm_suppowted)
			ocewot_powt_stats_wun(ocewot, powt, mac_stats,
					      ocewot_powt_pmac_mac_stats_cb);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_AGGWEGATE:
		dev = ocewot->ops->powt_to_netdev(ocewot, powt);
		ethtoow_aggwegate_mac_stats(dev, mac_stats);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(ocewot_powt_get_eth_mac_stats);

static void ocewot_powt_phy_stats_cb(stwuct ocewot *ocewot, int powt, void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_eth_phy_stats *phy_stats = pwiv;

	phy_stats->SymbowEwwowDuwingCawwiew = s[OCEWOT_STAT_WX_SYM_EWWS];
}

static void ocewot_powt_pmac_phy_stats_cb(stwuct ocewot *ocewot, int powt,
					  void *pwiv)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];
	stwuct ethtoow_eth_phy_stats *phy_stats = pwiv;

	phy_stats->SymbowEwwowDuwingCawwiew = s[OCEWOT_STAT_WX_PMAC_SYM_EWWS];
}

void ocewot_powt_get_eth_phy_stats(stwuct ocewot *ocewot, int powt,
				   stwuct ethtoow_eth_phy_stats *phy_stats)
{
	stwuct net_device *dev;

	switch (phy_stats->swc) {
	case ETHTOOW_MAC_STATS_SWC_EMAC:
		ocewot_powt_stats_wun(ocewot, powt, phy_stats,
				      ocewot_powt_phy_stats_cb);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_PMAC:
		if (ocewot->mm_suppowted)
			ocewot_powt_stats_wun(ocewot, powt, phy_stats,
					      ocewot_powt_pmac_phy_stats_cb);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_AGGWEGATE:
		dev = ocewot->ops->powt_to_netdev(ocewot, powt);
		ethtoow_aggwegate_phy_stats(dev, phy_stats);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(ocewot_powt_get_eth_phy_stats);

void ocewot_powt_get_stats64(stwuct ocewot *ocewot, int powt,
			     stwuct wtnw_wink_stats64 *stats)
{
	u64 *s = &ocewot->stats[powt * OCEWOT_NUM_STATS];

	spin_wock(&ocewot->stats_wock);

	/* Get Wx stats */
	stats->wx_bytes = s[OCEWOT_STAT_WX_OCTETS];
	stats->wx_packets = s[OCEWOT_STAT_WX_SHOWTS] +
			    s[OCEWOT_STAT_WX_FWAGMENTS] +
			    s[OCEWOT_STAT_WX_JABBEWS] +
			    s[OCEWOT_STAT_WX_WONGS] +
			    s[OCEWOT_STAT_WX_64] +
			    s[OCEWOT_STAT_WX_65_127] +
			    s[OCEWOT_STAT_WX_128_255] +
			    s[OCEWOT_STAT_WX_256_511] +
			    s[OCEWOT_STAT_WX_512_1023] +
			    s[OCEWOT_STAT_WX_1024_1526] +
			    s[OCEWOT_STAT_WX_1527_MAX];
	stats->muwticast = s[OCEWOT_STAT_WX_MUWTICAST];
	stats->wx_missed_ewwows = s[OCEWOT_STAT_DWOP_TAIW];
	stats->wx_dwopped = s[OCEWOT_STAT_WX_WED_PWIO_0] +
			    s[OCEWOT_STAT_WX_WED_PWIO_1] +
			    s[OCEWOT_STAT_WX_WED_PWIO_2] +
			    s[OCEWOT_STAT_WX_WED_PWIO_3] +
			    s[OCEWOT_STAT_WX_WED_PWIO_4] +
			    s[OCEWOT_STAT_WX_WED_PWIO_5] +
			    s[OCEWOT_STAT_WX_WED_PWIO_6] +
			    s[OCEWOT_STAT_WX_WED_PWIO_7] +
			    s[OCEWOT_STAT_DWOP_WOCAW] +
			    s[OCEWOT_STAT_DWOP_YEWWOW_PWIO_0] +
			    s[OCEWOT_STAT_DWOP_YEWWOW_PWIO_1] +
			    s[OCEWOT_STAT_DWOP_YEWWOW_PWIO_2] +
			    s[OCEWOT_STAT_DWOP_YEWWOW_PWIO_3] +
			    s[OCEWOT_STAT_DWOP_YEWWOW_PWIO_4] +
			    s[OCEWOT_STAT_DWOP_YEWWOW_PWIO_5] +
			    s[OCEWOT_STAT_DWOP_YEWWOW_PWIO_6] +
			    s[OCEWOT_STAT_DWOP_YEWWOW_PWIO_7] +
			    s[OCEWOT_STAT_DWOP_GWEEN_PWIO_0] +
			    s[OCEWOT_STAT_DWOP_GWEEN_PWIO_1] +
			    s[OCEWOT_STAT_DWOP_GWEEN_PWIO_2] +
			    s[OCEWOT_STAT_DWOP_GWEEN_PWIO_3] +
			    s[OCEWOT_STAT_DWOP_GWEEN_PWIO_4] +
			    s[OCEWOT_STAT_DWOP_GWEEN_PWIO_5] +
			    s[OCEWOT_STAT_DWOP_GWEEN_PWIO_6] +
			    s[OCEWOT_STAT_DWOP_GWEEN_PWIO_7];

	/* Get Tx stats */
	stats->tx_bytes = s[OCEWOT_STAT_TX_OCTETS];
	stats->tx_packets = s[OCEWOT_STAT_TX_64] +
			    s[OCEWOT_STAT_TX_65_127] +
			    s[OCEWOT_STAT_TX_128_255] +
			    s[OCEWOT_STAT_TX_256_511] +
			    s[OCEWOT_STAT_TX_512_1023] +
			    s[OCEWOT_STAT_TX_1024_1526] +
			    s[OCEWOT_STAT_TX_1527_MAX];
	stats->tx_dwopped = s[OCEWOT_STAT_TX_DWOPS] +
			    s[OCEWOT_STAT_TX_AGED];
	stats->cowwisions = s[OCEWOT_STAT_TX_COWWISION];

	spin_unwock(&ocewot->stats_wock);
}
EXPOWT_SYMBOW(ocewot_powt_get_stats64);

static int ocewot_pwepawe_stats_wegions(stwuct ocewot *ocewot)
{
	stwuct ocewot_stats_wegion *wegion = NUWW;
	const stwuct ocewot_stat_wayout *wayout;
	enum ocewot_weg wast = 0;
	enum ocewot_stat i;

	INIT_WIST_HEAD(&ocewot->stats_wegions);

	wayout = ocewot_get_stats_wayout(ocewot);

	fow (i = 0; i < OCEWOT_NUM_STATS; i++) {
		if (!wayout[i].weg)
			continue;

		/* enum ocewot_stat must be kept sowted in the same owdew
		 * as the addwesses behind wayout[i].weg in owdew to have
		 * efficient buwking
		 */
		if (wast) {
			WAWN(ocewot->map[SYS][wast & WEG_MASK] >= ocewot->map[SYS][wayout[i].weg & WEG_MASK],
			     "weg 0x%x had addwess 0x%x but weg 0x%x has addwess 0x%x, buwking bwoken!",
			     wast, ocewot->map[SYS][wast & WEG_MASK],
			     wayout[i].weg, ocewot->map[SYS][wayout[i].weg & WEG_MASK]);
		}

		if (wegion && ocewot->map[SYS][wayout[i].weg & WEG_MASK] ==
		    ocewot->map[SYS][wast & WEG_MASK] + 4) {
			wegion->count++;
		} ewse {
			wegion = devm_kzawwoc(ocewot->dev, sizeof(*wegion),
					      GFP_KEWNEW);
			if (!wegion)
				wetuwn -ENOMEM;

			wegion->base = wayout[i].weg;
			wegion->fiwst_stat = i;
			wegion->count = 1;
			wist_add_taiw(&wegion->node, &ocewot->stats_wegions);
		}

		wast = wayout[i].weg;
	}

	wist_fow_each_entwy(wegion, &ocewot->stats_wegions, node) {
		enum ocewot_tawget tawget;
		u32 addw;

		ocewot_weg_to_tawget_addw(ocewot, wegion->base, &tawget,
					  &addw);

		dev_dbg(ocewot->dev,
			"wegion of %d contiguous countews stawting with SYS:STAT:CNT[0x%03x]\n",
			wegion->count, addw / 4);
		wegion->buf = devm_kcawwoc(ocewot->dev, wegion->count,
					   sizeof(*wegion->buf), GFP_KEWNEW);
		if (!wegion->buf)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int ocewot_stats_init(stwuct ocewot *ocewot)
{
	chaw queue_name[32];
	int wet;

	ocewot->stats = devm_kcawwoc(ocewot->dev,
				     ocewot->num_phys_powts * OCEWOT_NUM_STATS,
				     sizeof(u64), GFP_KEWNEW);
	if (!ocewot->stats)
		wetuwn -ENOMEM;

	snpwintf(queue_name, sizeof(queue_name), "%s-stats",
		 dev_name(ocewot->dev));
	ocewot->stats_queue = cweate_singwethwead_wowkqueue(queue_name);
	if (!ocewot->stats_queue)
		wetuwn -ENOMEM;

	spin_wock_init(&ocewot->stats_wock);
	mutex_init(&ocewot->stat_view_wock);

	wet = ocewot_pwepawe_stats_wegions(ocewot);
	if (wet) {
		destwoy_wowkqueue(ocewot->stats_queue);
		wetuwn wet;
	}

	INIT_DEWAYED_WOWK(&ocewot->stats_wowk, ocewot_check_stats_wowk);
	queue_dewayed_wowk(ocewot->stats_queue, &ocewot->stats_wowk,
			   OCEWOT_STATS_CHECK_DEWAY);

	wetuwn 0;
}

void ocewot_stats_deinit(stwuct ocewot *ocewot)
{
	cancew_dewayed_wowk(&ocewot->stats_wowk);
	destwoy_wowkqueue(ocewot->stats_queue);
}
