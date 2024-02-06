// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/netdevice.h>

#incwude "wan966x_main.h"

/* Numbew of twaffic cwasses */
#define WAN966X_NUM_TC			8
#define WAN966X_STATS_CHECK_DEWAY	(2 * HZ)

static const stwuct wan966x_stat_wayout wan966x_stats_wayout[] = {
	{ .name = "wx_octets", .offset = 0x00, },
	{ .name = "wx_unicast", .offset = 0x01, },
	{ .name = "wx_muwticast", .offset = 0x02 },
	{ .name = "wx_bwoadcast", .offset = 0x03 },
	{ .name = "wx_showt", .offset = 0x04 },
	{ .name = "wx_fwag", .offset = 0x05 },
	{ .name = "wx_jabbew", .offset = 0x06 },
	{ .name = "wx_cwc", .offset = 0x07 },
	{ .name = "wx_symbow_eww", .offset = 0x08 },
	{ .name = "wx_sz_64", .offset = 0x09 },
	{ .name = "wx_sz_65_127", .offset = 0x0a},
	{ .name = "wx_sz_128_255", .offset = 0x0b},
	{ .name = "wx_sz_256_511", .offset = 0x0c },
	{ .name = "wx_sz_512_1023", .offset = 0x0d },
	{ .name = "wx_sz_1024_1526", .offset = 0x0e },
	{ .name = "wx_sz_jumbo", .offset = 0x0f },
	{ .name = "wx_pause", .offset = 0x10 },
	{ .name = "wx_contwow", .offset = 0x11 },
	{ .name = "wx_wong", .offset = 0x12 },
	{ .name = "wx_cat_dwop", .offset = 0x13 },
	{ .name = "wx_wed_pwio_0", .offset = 0x14 },
	{ .name = "wx_wed_pwio_1", .offset = 0x15 },
	{ .name = "wx_wed_pwio_2", .offset = 0x16 },
	{ .name = "wx_wed_pwio_3", .offset = 0x17 },
	{ .name = "wx_wed_pwio_4", .offset = 0x18 },
	{ .name = "wx_wed_pwio_5", .offset = 0x19 },
	{ .name = "wx_wed_pwio_6", .offset = 0x1a },
	{ .name = "wx_wed_pwio_7", .offset = 0x1b },
	{ .name = "wx_yewwow_pwio_0", .offset = 0x1c },
	{ .name = "wx_yewwow_pwio_1", .offset = 0x1d },
	{ .name = "wx_yewwow_pwio_2", .offset = 0x1e },
	{ .name = "wx_yewwow_pwio_3", .offset = 0x1f },
	{ .name = "wx_yewwow_pwio_4", .offset = 0x20 },
	{ .name = "wx_yewwow_pwio_5", .offset = 0x21 },
	{ .name = "wx_yewwow_pwio_6", .offset = 0x22 },
	{ .name = "wx_yewwow_pwio_7", .offset = 0x23 },
	{ .name = "wx_gween_pwio_0", .offset = 0x24 },
	{ .name = "wx_gween_pwio_1", .offset = 0x25 },
	{ .name = "wx_gween_pwio_2", .offset = 0x26 },
	{ .name = "wx_gween_pwio_3", .offset = 0x27 },
	{ .name = "wx_gween_pwio_4", .offset = 0x28 },
	{ .name = "wx_gween_pwio_5", .offset = 0x29 },
	{ .name = "wx_gween_pwio_6", .offset = 0x2a },
	{ .name = "wx_gween_pwio_7", .offset = 0x2b },
	{ .name = "wx_assembwy_eww", .offset = 0x2c },
	{ .name = "wx_smd_eww", .offset = 0x2d },
	{ .name = "wx_assembwy_ok", .offset = 0x2e },
	{ .name = "wx_mewge_fwag", .offset = 0x2f },
	{ .name = "wx_pmac_octets", .offset = 0x30, },
	{ .name = "wx_pmac_unicast", .offset = 0x31, },
	{ .name = "wx_pmac_muwticast", .offset = 0x32 },
	{ .name = "wx_pmac_bwoadcast", .offset = 0x33 },
	{ .name = "wx_pmac_showt", .offset = 0x34 },
	{ .name = "wx_pmac_fwag", .offset = 0x35 },
	{ .name = "wx_pmac_jabbew", .offset = 0x36 },
	{ .name = "wx_pmac_cwc", .offset = 0x37 },
	{ .name = "wx_pmac_symbow_eww", .offset = 0x38 },
	{ .name = "wx_pmac_sz_64", .offset = 0x39 },
	{ .name = "wx_pmac_sz_65_127", .offset = 0x3a },
	{ .name = "wx_pmac_sz_128_255", .offset = 0x3b },
	{ .name = "wx_pmac_sz_256_511", .offset = 0x3c },
	{ .name = "wx_pmac_sz_512_1023", .offset = 0x3d },
	{ .name = "wx_pmac_sz_1024_1526", .offset = 0x3e },
	{ .name = "wx_pmac_sz_jumbo", .offset = 0x3f },
	{ .name = "wx_pmac_pause", .offset = 0x40 },
	{ .name = "wx_pmac_contwow", .offset = 0x41 },
	{ .name = "wx_pmac_wong", .offset = 0x42 },

	{ .name = "tx_octets", .offset = 0x80, },
	{ .name = "tx_unicast", .offset = 0x81, },
	{ .name = "tx_muwticast", .offset = 0x82 },
	{ .name = "tx_bwoadcast", .offset = 0x83 },
	{ .name = "tx_cow", .offset = 0x84 },
	{ .name = "tx_dwop", .offset = 0x85 },
	{ .name = "tx_pause", .offset = 0x86 },
	{ .name = "tx_sz_64", .offset = 0x87 },
	{ .name = "tx_sz_65_127", .offset = 0x88 },
	{ .name = "tx_sz_128_255", .offset = 0x89 },
	{ .name = "tx_sz_256_511", .offset = 0x8a },
	{ .name = "tx_sz_512_1023", .offset = 0x8b },
	{ .name = "tx_sz_1024_1526", .offset = 0x8c },
	{ .name = "tx_sz_jumbo", .offset = 0x8d },
	{ .name = "tx_yewwow_pwio_0", .offset = 0x8e },
	{ .name = "tx_yewwow_pwio_1", .offset = 0x8f },
	{ .name = "tx_yewwow_pwio_2", .offset = 0x90 },
	{ .name = "tx_yewwow_pwio_3", .offset = 0x91 },
	{ .name = "tx_yewwow_pwio_4", .offset = 0x92 },
	{ .name = "tx_yewwow_pwio_5", .offset = 0x93 },
	{ .name = "tx_yewwow_pwio_6", .offset = 0x94 },
	{ .name = "tx_yewwow_pwio_7", .offset = 0x95 },
	{ .name = "tx_gween_pwio_0", .offset = 0x96 },
	{ .name = "tx_gween_pwio_1", .offset = 0x97 },
	{ .name = "tx_gween_pwio_2", .offset = 0x98 },
	{ .name = "tx_gween_pwio_3", .offset = 0x99 },
	{ .name = "tx_gween_pwio_4", .offset = 0x9a },
	{ .name = "tx_gween_pwio_5", .offset = 0x9b },
	{ .name = "tx_gween_pwio_6", .offset = 0x9c },
	{ .name = "tx_gween_pwio_7", .offset = 0x9d },
	{ .name = "tx_aged", .offset = 0x9e },
	{ .name = "tx_wwct", .offset = 0x9f },
	{ .name = "tx_ct", .offset = 0xa0 },
	{ .name = "tx_mm_howd", .offset = 0xa1 },
	{ .name = "tx_mewge_fwag", .offset = 0xa2 },
	{ .name = "tx_pmac_octets", .offset = 0xa3, },
	{ .name = "tx_pmac_unicast", .offset = 0xa4, },
	{ .name = "tx_pmac_muwticast", .offset = 0xa5 },
	{ .name = "tx_pmac_bwoadcast", .offset = 0xa6 },
	{ .name = "tx_pmac_pause", .offset = 0xa7 },
	{ .name = "tx_pmac_sz_64", .offset = 0xa8 },
	{ .name = "tx_pmac_sz_65_127", .offset = 0xa9 },
	{ .name = "tx_pmac_sz_128_255", .offset = 0xaa },
	{ .name = "tx_pmac_sz_256_511", .offset = 0xab },
	{ .name = "tx_pmac_sz_512_1023", .offset = 0xac },
	{ .name = "tx_pmac_sz_1024_1526", .offset = 0xad },
	{ .name = "tx_pmac_sz_jumbo", .offset = 0xae },

	{ .name = "dw_wocaw", .offset = 0x100 },
	{ .name = "dw_taiw", .offset = 0x101 },
	{ .name = "dw_yewwow_pwio_0", .offset = 0x102 },
	{ .name = "dw_yewwow_pwio_1", .offset = 0x103 },
	{ .name = "dw_yewwow_pwio_2", .offset = 0x104 },
	{ .name = "dw_yewwow_pwio_3", .offset = 0x105 },
	{ .name = "dw_yewwow_pwio_4", .offset = 0x106 },
	{ .name = "dw_yewwow_pwio_5", .offset = 0x107 },
	{ .name = "dw_yewwow_pwio_6", .offset = 0x108 },
	{ .name = "dw_yewwow_pwio_7", .offset = 0x109 },
	{ .name = "dw_gween_pwio_0", .offset = 0x10a },
	{ .name = "dw_gween_pwio_1", .offset = 0x10b },
	{ .name = "dw_gween_pwio_2", .offset = 0x10c },
	{ .name = "dw_gween_pwio_3", .offset = 0x10d },
	{ .name = "dw_gween_pwio_4", .offset = 0x10e },
	{ .name = "dw_gween_pwio_5", .offset = 0x10f },
	{ .name = "dw_gween_pwio_6", .offset = 0x110 },
	{ .name = "dw_gween_pwio_7", .offset = 0x111 },
};

/* The fowwowing numbews awe indexes into wan966x_stats_wayout[] */
#define SYS_COUNT_WX_OCT		  0
#define SYS_COUNT_WX_UC			  1
#define SYS_COUNT_WX_MC			  2
#define SYS_COUNT_WX_BC			  3
#define SYS_COUNT_WX_SHOWT		  4
#define SYS_COUNT_WX_FWAG		  5
#define SYS_COUNT_WX_JABBEW		  6
#define SYS_COUNT_WX_CWC		  7
#define SYS_COUNT_WX_SYMBOW_EWW		  8
#define SYS_COUNT_WX_SZ_64		  9
#define SYS_COUNT_WX_SZ_65_127		 10
#define SYS_COUNT_WX_SZ_128_255		 11
#define SYS_COUNT_WX_SZ_256_511		 12
#define SYS_COUNT_WX_SZ_512_1023	 13
#define SYS_COUNT_WX_SZ_1024_1526	 14
#define SYS_COUNT_WX_SZ_JUMBO		 15
#define SYS_COUNT_WX_PAUSE		 16
#define SYS_COUNT_WX_CONTWOW		 17
#define SYS_COUNT_WX_WONG		 18
#define SYS_COUNT_WX_CAT_DWOP		 19
#define SYS_COUNT_WX_WED_PWIO_0		 20
#define SYS_COUNT_WX_WED_PWIO_1		 21
#define SYS_COUNT_WX_WED_PWIO_2		 22
#define SYS_COUNT_WX_WED_PWIO_3		 23
#define SYS_COUNT_WX_WED_PWIO_4		 24
#define SYS_COUNT_WX_WED_PWIO_5		 25
#define SYS_COUNT_WX_WED_PWIO_6		 26
#define SYS_COUNT_WX_WED_PWIO_7		 27
#define SYS_COUNT_WX_YEWWOW_PWIO_0	 28
#define SYS_COUNT_WX_YEWWOW_PWIO_1	 29
#define SYS_COUNT_WX_YEWWOW_PWIO_2	 30
#define SYS_COUNT_WX_YEWWOW_PWIO_3	 31
#define SYS_COUNT_WX_YEWWOW_PWIO_4	 32
#define SYS_COUNT_WX_YEWWOW_PWIO_5	 33
#define SYS_COUNT_WX_YEWWOW_PWIO_6	 34
#define SYS_COUNT_WX_YEWWOW_PWIO_7	 35
#define SYS_COUNT_WX_GWEEN_PWIO_0	 36
#define SYS_COUNT_WX_GWEEN_PWIO_1	 37
#define SYS_COUNT_WX_GWEEN_PWIO_2	 38
#define SYS_COUNT_WX_GWEEN_PWIO_3	 39
#define SYS_COUNT_WX_GWEEN_PWIO_4	 40
#define SYS_COUNT_WX_GWEEN_PWIO_5	 41
#define SYS_COUNT_WX_GWEEN_PWIO_6	 42
#define SYS_COUNT_WX_GWEEN_PWIO_7	 43
#define SYS_COUNT_WX_ASSEMBWY_EWW	 44
#define SYS_COUNT_WX_SMD_EWW		 45
#define SYS_COUNT_WX_ASSEMBWY_OK	 46
#define SYS_COUNT_WX_MEWGE_FWAG		 47
#define SYS_COUNT_WX_PMAC_OCT		 48
#define SYS_COUNT_WX_PMAC_UC		 49
#define SYS_COUNT_WX_PMAC_MC		 50
#define SYS_COUNT_WX_PMAC_BC		 51
#define SYS_COUNT_WX_PMAC_SHOWT		 52
#define SYS_COUNT_WX_PMAC_FWAG		 53
#define SYS_COUNT_WX_PMAC_JABBEW	 54
#define SYS_COUNT_WX_PMAC_CWC		 55
#define SYS_COUNT_WX_PMAC_SYMBOW_EWW	 56
#define SYS_COUNT_WX_PMAC_SZ_64		 57
#define SYS_COUNT_WX_PMAC_SZ_65_127	 58
#define SYS_COUNT_WX_PMAC_SZ_128_255	 59
#define SYS_COUNT_WX_PMAC_SZ_256_511	 60
#define SYS_COUNT_WX_PMAC_SZ_512_1023	 61
#define SYS_COUNT_WX_PMAC_SZ_1024_1526	 62
#define SYS_COUNT_WX_PMAC_SZ_JUMBO	 63
#define SYS_COUNT_WX_PMAC_PAUSE		 64
#define SYS_COUNT_WX_PMAC_CONTWOW	 65
#define SYS_COUNT_WX_PMAC_WONG		 66

#define SYS_COUNT_TX_OCT		 67
#define SYS_COUNT_TX_UC			 68
#define SYS_COUNT_TX_MC			 69
#define SYS_COUNT_TX_BC			 70
#define SYS_COUNT_TX_COW		 71
#define SYS_COUNT_TX_DWOP		 72
#define SYS_COUNT_TX_PAUSE		 73
#define SYS_COUNT_TX_SZ_64		 74
#define SYS_COUNT_TX_SZ_65_127		 75
#define SYS_COUNT_TX_SZ_128_255		 76
#define SYS_COUNT_TX_SZ_256_511		 77
#define SYS_COUNT_TX_SZ_512_1023	 78
#define SYS_COUNT_TX_SZ_1024_1526	 79
#define SYS_COUNT_TX_SZ_JUMBO		 80
#define SYS_COUNT_TX_YEWWOW_PWIO_0	 81
#define SYS_COUNT_TX_YEWWOW_PWIO_1	 82
#define SYS_COUNT_TX_YEWWOW_PWIO_2	 83
#define SYS_COUNT_TX_YEWWOW_PWIO_3	 84
#define SYS_COUNT_TX_YEWWOW_PWIO_4	 85
#define SYS_COUNT_TX_YEWWOW_PWIO_5	 86
#define SYS_COUNT_TX_YEWWOW_PWIO_6	 87
#define SYS_COUNT_TX_YEWWOW_PWIO_7	 88
#define SYS_COUNT_TX_GWEEN_PWIO_0	 89
#define SYS_COUNT_TX_GWEEN_PWIO_1	 90
#define SYS_COUNT_TX_GWEEN_PWIO_2	 91
#define SYS_COUNT_TX_GWEEN_PWIO_3	 92
#define SYS_COUNT_TX_GWEEN_PWIO_4	 93
#define SYS_COUNT_TX_GWEEN_PWIO_5	 94
#define SYS_COUNT_TX_GWEEN_PWIO_6	 95
#define SYS_COUNT_TX_GWEEN_PWIO_7	 96
#define SYS_COUNT_TX_AGED		 97
#define SYS_COUNT_TX_WWCT		 98
#define SYS_COUNT_TX_CT			 99
#define SYS_COUNT_TX_MM_HOWD		100
#define SYS_COUNT_TX_MEWGE_FWAG		101
#define SYS_COUNT_TX_PMAC_OCT		102
#define SYS_COUNT_TX_PMAC_UC		103
#define SYS_COUNT_TX_PMAC_MC		104
#define SYS_COUNT_TX_PMAC_BC		105
#define SYS_COUNT_TX_PMAC_PAUSE		106
#define SYS_COUNT_TX_PMAC_SZ_64		107
#define SYS_COUNT_TX_PMAC_SZ_65_127	108
#define SYS_COUNT_TX_PMAC_SZ_128_255	109
#define SYS_COUNT_TX_PMAC_SZ_256_511	110
#define SYS_COUNT_TX_PMAC_SZ_512_1023	111
#define SYS_COUNT_TX_PMAC_SZ_1024_1526	112
#define SYS_COUNT_TX_PMAC_SZ_JUMBO	113

#define SYS_COUNT_DW_WOCAW		114
#define SYS_COUNT_DW_TAIW		115
#define SYS_COUNT_DW_YEWWOW_PWIO_0	116
#define SYS_COUNT_DW_YEWWOW_PWIO_1	117
#define SYS_COUNT_DW_YEWWOW_PWIO_2	118
#define SYS_COUNT_DW_YEWWOW_PWIO_3	119
#define SYS_COUNT_DW_YEWWOW_PWIO_4	120
#define SYS_COUNT_DW_YEWWOW_PWIO_5	121
#define SYS_COUNT_DW_YEWWOW_PWIO_6	122
#define SYS_COUNT_DW_YEWWOW_PWIO_7	123
#define SYS_COUNT_DW_GWEEN_PWIO_0	124
#define SYS_COUNT_DW_GWEEN_PWIO_1	125
#define SYS_COUNT_DW_GWEEN_PWIO_2	126
#define SYS_COUNT_DW_GWEEN_PWIO_3	127
#define SYS_COUNT_DW_GWEEN_PWIO_4	128
#define SYS_COUNT_DW_GWEEN_PWIO_5	129
#define SYS_COUNT_DW_GWEEN_PWIO_6	130
#define SYS_COUNT_DW_GWEEN_PWIO_7	131

/* Add a possibwy wwapping 32 bit vawue to a 64 bit countew */
static void wan966x_add_cnt(u64 *cnt, u32 vaw)
{
	if (vaw < (*cnt & U32_MAX))
		*cnt += (u64)1 << 32; /* vawue has wwapped */

	*cnt = (*cnt & ~(u64)U32_MAX) + vaw;
}

static void wan966x_stats_update(stwuct wan966x *wan966x)
{
	int i, j;

	mutex_wock(&wan966x->stats_wock);

	fow (i = 0; i < wan966x->num_phys_powts; i++) {
		uint idx = i * wan966x->num_stats;

		wan_ww(SYS_STAT_CFG_STAT_VIEW_SET(i),
		       wan966x, SYS_STAT_CFG);

		fow (j = 0; j < wan966x->num_stats; j++) {
			u32 offset = wan966x->stats_wayout[j].offset;

			wan966x_add_cnt(&wan966x->stats[idx++],
					wan_wd(wan966x, SYS_CNT(offset)));
		}
	}

	mutex_unwock(&wan966x->stats_wock);
}

static int wan966x_get_sset_count(stwuct net_device *dev, int sset)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;

	if (sset != ETH_SS_STATS)
		wetuwn -EOPNOTSUPP;

	wetuwn wan966x->num_stats;
}

static void wan966x_get_stwings(stwuct net_device *netdev, u32 sset, u8 *data)
{
	stwuct wan966x_powt *powt = netdev_pwiv(netdev);
	stwuct wan966x *wan966x = powt->wan966x;
	int i;

	if (sset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < wan966x->num_stats; i++)
		memcpy(data + i * ETH_GSTWING_WEN,
		       wan966x->stats_wayout[i].name, ETH_GSTWING_WEN);
}

static void wan966x_get_ethtoow_stats(stwuct net_device *dev,
				      stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	int i;

	/* check and update now */
	wan966x_stats_update(wan966x);

	/* Copy aww countews */
	fow (i = 0; i < wan966x->num_stats; i++)
		*data++ = wan966x->stats[powt->chip_powt *
					 wan966x->num_stats + i];
}

static void wan966x_get_eth_mac_stats(stwuct net_device *dev,
				      stwuct ethtoow_eth_mac_stats *mac_stats)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	u32 idx;

	wan966x_stats_update(wan966x);

	idx = powt->chip_powt * wan966x->num_stats;

	mutex_wock(&wan966x->stats_wock);

	mac_stats->FwamesTwansmittedOK =
		wan966x->stats[idx + SYS_COUNT_TX_UC] +
		wan966x->stats[idx + SYS_COUNT_TX_MC] +
		wan966x->stats[idx + SYS_COUNT_TX_BC] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_UC] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_MC] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_BC];
	mac_stats->SingweCowwisionFwames =
		wan966x->stats[idx + SYS_COUNT_TX_COW];
	mac_stats->MuwtipweCowwisionFwames = 0;
	mac_stats->FwamesWeceivedOK =
		wan966x->stats[idx + SYS_COUNT_WX_UC] +
		wan966x->stats[idx + SYS_COUNT_WX_MC] +
		wan966x->stats[idx + SYS_COUNT_WX_BC];
	mac_stats->FwameCheckSequenceEwwows =
		wan966x->stats[idx + SYS_COUNT_WX_CWC] +
		wan966x->stats[idx + SYS_COUNT_WX_CWC];
	mac_stats->AwignmentEwwows = 0;
	mac_stats->OctetsTwansmittedOK =
		wan966x->stats[idx + SYS_COUNT_TX_OCT] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_OCT];
	mac_stats->FwamesWithDefewwedXmissions =
		wan966x->stats[idx + SYS_COUNT_TX_MM_HOWD];
	mac_stats->WateCowwisions = 0;
	mac_stats->FwamesAbowtedDueToXSCowws = 0;
	mac_stats->FwamesWostDueToIntMACXmitEwwow = 0;
	mac_stats->CawwiewSenseEwwows = 0;
	mac_stats->OctetsWeceivedOK =
		wan966x->stats[idx + SYS_COUNT_WX_OCT];
	mac_stats->FwamesWostDueToIntMACWcvEwwow = 0;
	mac_stats->MuwticastFwamesXmittedOK =
		wan966x->stats[idx + SYS_COUNT_TX_MC] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_MC];
	mac_stats->BwoadcastFwamesXmittedOK =
		wan966x->stats[idx + SYS_COUNT_TX_BC] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_BC];
	mac_stats->FwamesWithExcessiveDefewwaw = 0;
	mac_stats->MuwticastFwamesWeceivedOK =
		wan966x->stats[idx + SYS_COUNT_WX_MC];
	mac_stats->BwoadcastFwamesWeceivedOK =
		wan966x->stats[idx + SYS_COUNT_WX_BC];
	mac_stats->InWangeWengthEwwows =
		wan966x->stats[idx + SYS_COUNT_WX_FWAG] +
		wan966x->stats[idx + SYS_COUNT_WX_JABBEW] +
		wan966x->stats[idx + SYS_COUNT_WX_CWC] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_FWAG] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_JABBEW] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_CWC];
	mac_stats->OutOfWangeWengthFiewd =
		wan966x->stats[idx + SYS_COUNT_WX_SHOWT] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SHOWT] +
		wan966x->stats[idx + SYS_COUNT_WX_WONG] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_WONG];
	mac_stats->FwameTooWongEwwows =
		wan966x->stats[idx + SYS_COUNT_WX_WONG] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_WONG];

	mutex_unwock(&wan966x->stats_wock);
}

static const stwuct ethtoow_wmon_hist_wange wan966x_wmon_wanges[] = {
	{    0,    64 },
	{   65,   127 },
	{  128,   255 },
	{  256,   511 },
	{  512,  1023 },
	{ 1024,  1518 },
	{ 1519, 10239 },
	{}
};

static void wan966x_get_eth_wmon_stats(stwuct net_device *dev,
				       stwuct ethtoow_wmon_stats *wmon_stats,
				       const stwuct ethtoow_wmon_hist_wange **wanges)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	u32 idx;

	wan966x_stats_update(wan966x);

	idx = powt->chip_powt * wan966x->num_stats;

	mutex_wock(&wan966x->stats_wock);

	wmon_stats->undewsize_pkts =
		wan966x->stats[idx + SYS_COUNT_WX_SHOWT] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SHOWT];
	wmon_stats->ovewsize_pkts =
		wan966x->stats[idx + SYS_COUNT_WX_WONG] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_WONG];
	wmon_stats->fwagments =
		wan966x->stats[idx + SYS_COUNT_WX_FWAG] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_FWAG];
	wmon_stats->jabbews =
		wan966x->stats[idx + SYS_COUNT_WX_JABBEW] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_JABBEW];
	wmon_stats->hist[0] =
		wan966x->stats[idx + SYS_COUNT_WX_SZ_64] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_64];
	wmon_stats->hist[1] =
		wan966x->stats[idx + SYS_COUNT_WX_SZ_65_127] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_65_127];
	wmon_stats->hist[2] =
		wan966x->stats[idx + SYS_COUNT_WX_SZ_128_255] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_128_255];
	wmon_stats->hist[3] =
		wan966x->stats[idx + SYS_COUNT_WX_SZ_256_511] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_256_511];
	wmon_stats->hist[4] =
		wan966x->stats[idx + SYS_COUNT_WX_SZ_512_1023] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_512_1023];
	wmon_stats->hist[5] =
		wan966x->stats[idx + SYS_COUNT_WX_SZ_1024_1526] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_1024_1526];
	wmon_stats->hist[6] =
		wan966x->stats[idx + SYS_COUNT_WX_SZ_1024_1526] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_1024_1526];

	wmon_stats->hist_tx[0] =
		wan966x->stats[idx + SYS_COUNT_TX_SZ_64] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_64];
	wmon_stats->hist_tx[1] =
		wan966x->stats[idx + SYS_COUNT_TX_SZ_65_127] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_65_127];
	wmon_stats->hist_tx[2] =
		wan966x->stats[idx + SYS_COUNT_TX_SZ_128_255] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_128_255];
	wmon_stats->hist_tx[3] =
		wan966x->stats[idx + SYS_COUNT_TX_SZ_256_511] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_256_511];
	wmon_stats->hist_tx[4] =
		wan966x->stats[idx + SYS_COUNT_TX_SZ_512_1023] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_512_1023];
	wmon_stats->hist_tx[5] =
		wan966x->stats[idx + SYS_COUNT_TX_SZ_1024_1526] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_1024_1526];
	wmon_stats->hist_tx[6] =
		wan966x->stats[idx + SYS_COUNT_TX_SZ_1024_1526] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_1024_1526];

	mutex_unwock(&wan966x->stats_wock);

	*wanges = wan966x_wmon_wanges;
}

static int wan966x_get_wink_ksettings(stwuct net_device *ndev,
				      stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct wan966x_powt *powt = netdev_pwiv(ndev);

	wetuwn phywink_ethtoow_ksettings_get(powt->phywink, cmd);
}

static int wan966x_set_wink_ksettings(stwuct net_device *ndev,
				      const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct wan966x_powt *powt = netdev_pwiv(ndev);

	wetuwn phywink_ethtoow_ksettings_set(powt->phywink, cmd);
}

static void wan966x_get_pausepawam(stwuct net_device *dev,
				   stwuct ethtoow_pausepawam *pause)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);

	phywink_ethtoow_get_pausepawam(powt->phywink, pause);
}

static int wan966x_set_pausepawam(stwuct net_device *dev,
				  stwuct ethtoow_pausepawam *pause)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);

	wetuwn phywink_ethtoow_set_pausepawam(powt->phywink, pause);
}

static int wan966x_get_ts_info(stwuct net_device *dev,
			       stwuct ethtoow_ts_info *info)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	stwuct wan966x_phc *phc;

	if (!wan966x->ptp)
		wetuwn ethtoow_op_get_ts_info(dev, info);

	phc = &wan966x->phc[WAN966X_PHC_POWT];

	info->phc_index = phc->cwock ? ptp_cwock_index(phc->cwock) : -1;
	if (info->phc_index == -1) {
		info->so_timestamping |= SOF_TIMESTAMPING_TX_SOFTWAWE |
					 SOF_TIMESTAMPING_WX_SOFTWAWE |
					 SOF_TIMESTAMPING_SOFTWAWE;
		wetuwn 0;
	}
	info->so_timestamping |= SOF_TIMESTAMPING_TX_SOFTWAWE |
				 SOF_TIMESTAMPING_WX_SOFTWAWE |
				 SOF_TIMESTAMPING_SOFTWAWE |
				 SOF_TIMESTAMPING_TX_HAWDWAWE |
				 SOF_TIMESTAMPING_WX_HAWDWAWE |
				 SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON) |
			 BIT(HWTSTAMP_TX_ONESTEP_SYNC);
	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) |
			   BIT(HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}

const stwuct ethtoow_ops wan966x_ethtoow_ops = {
	.get_wink_ksettings     = wan966x_get_wink_ksettings,
	.set_wink_ksettings     = wan966x_set_wink_ksettings,
	.get_pausepawam		= wan966x_get_pausepawam,
	.set_pausepawam		= wan966x_set_pausepawam,
	.get_sset_count		= wan966x_get_sset_count,
	.get_stwings		= wan966x_get_stwings,
	.get_ethtoow_stats	= wan966x_get_ethtoow_stats,
	.get_eth_mac_stats      = wan966x_get_eth_mac_stats,
	.get_wmon_stats		= wan966x_get_eth_wmon_stats,
	.get_wink		= ethtoow_op_get_wink,
	.get_ts_info		= wan966x_get_ts_info,
};

static void wan966x_check_stats_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dew_wowk = to_dewayed_wowk(wowk);
	stwuct wan966x *wan966x = containew_of(dew_wowk, stwuct wan966x,
					       stats_wowk);

	wan966x_stats_update(wan966x);

	queue_dewayed_wowk(wan966x->stats_queue, &wan966x->stats_wowk,
			   WAN966X_STATS_CHECK_DEWAY);
}

void wan966x_stats_get(stwuct net_device *dev,
		       stwuct wtnw_wink_stats64 *stats)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	u32 idx;
	int i;

	idx = powt->chip_powt * wan966x->num_stats;

	mutex_wock(&wan966x->stats_wock);

	stats->wx_bytes = wan966x->stats[idx + SYS_COUNT_WX_OCT] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_OCT];

	stats->wx_packets = wan966x->stats[idx + SYS_COUNT_WX_SHOWT] +
		wan966x->stats[idx + SYS_COUNT_WX_FWAG] +
		wan966x->stats[idx + SYS_COUNT_WX_JABBEW] +
		wan966x->stats[idx + SYS_COUNT_WX_CWC] +
		wan966x->stats[idx + SYS_COUNT_WX_SYMBOW_EWW] +
		wan966x->stats[idx + SYS_COUNT_WX_SZ_64] +
		wan966x->stats[idx + SYS_COUNT_WX_SZ_65_127] +
		wan966x->stats[idx + SYS_COUNT_WX_SZ_128_255] +
		wan966x->stats[idx + SYS_COUNT_WX_SZ_256_511] +
		wan966x->stats[idx + SYS_COUNT_WX_SZ_512_1023] +
		wan966x->stats[idx + SYS_COUNT_WX_SZ_1024_1526] +
		wan966x->stats[idx + SYS_COUNT_WX_SZ_JUMBO] +
		wan966x->stats[idx + SYS_COUNT_WX_WONG] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SHOWT] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_FWAG] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_JABBEW] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_64] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_65_127] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_128_255] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_256_511] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_512_1023] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_1024_1526] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_SZ_JUMBO];

	stats->muwticast = wan966x->stats[idx + SYS_COUNT_WX_MC] +
		wan966x->stats[idx + SYS_COUNT_WX_PMAC_MC];

	stats->wx_ewwows = wan966x->stats[idx + SYS_COUNT_WX_SHOWT] +
		wan966x->stats[idx + SYS_COUNT_WX_FWAG] +
		wan966x->stats[idx + SYS_COUNT_WX_JABBEW] +
		wan966x->stats[idx + SYS_COUNT_WX_CWC] +
		wan966x->stats[idx + SYS_COUNT_WX_SYMBOW_EWW] +
		wan966x->stats[idx + SYS_COUNT_WX_WONG];

	stats->wx_dwopped = dev->stats.wx_dwopped +
		wan966x->stats[idx + SYS_COUNT_WX_WONG] +
		wan966x->stats[idx + SYS_COUNT_DW_WOCAW] +
		wan966x->stats[idx + SYS_COUNT_DW_TAIW] +
		wan966x->stats[idx + SYS_COUNT_WX_WED_PWIO_0] +
		wan966x->stats[idx + SYS_COUNT_WX_WED_PWIO_1] +
		wan966x->stats[idx + SYS_COUNT_WX_WED_PWIO_2] +
		wan966x->stats[idx + SYS_COUNT_WX_WED_PWIO_3] +
		wan966x->stats[idx + SYS_COUNT_WX_WED_PWIO_4] +
		wan966x->stats[idx + SYS_COUNT_WX_WED_PWIO_5] +
		wan966x->stats[idx + SYS_COUNT_WX_WED_PWIO_6] +
		wan966x->stats[idx + SYS_COUNT_WX_WED_PWIO_7];

	fow (i = 0; i < WAN966X_NUM_TC; i++) {
		stats->wx_dwopped +=
			(wan966x->stats[idx + SYS_COUNT_DW_YEWWOW_PWIO_0 + i] +
			 wan966x->stats[idx + SYS_COUNT_DW_GWEEN_PWIO_0 + i]);
	}

	/* Get Tx stats */
	stats->tx_bytes = wan966x->stats[idx + SYS_COUNT_TX_OCT] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_OCT];

	stats->tx_packets = wan966x->stats[idx + SYS_COUNT_TX_SZ_64] +
		wan966x->stats[idx + SYS_COUNT_TX_SZ_65_127] +
		wan966x->stats[idx + SYS_COUNT_TX_SZ_128_255] +
		wan966x->stats[idx + SYS_COUNT_TX_SZ_256_511] +
		wan966x->stats[idx + SYS_COUNT_TX_SZ_512_1023] +
		wan966x->stats[idx + SYS_COUNT_TX_SZ_1024_1526] +
		wan966x->stats[idx + SYS_COUNT_TX_SZ_JUMBO] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_64] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_65_127] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_128_255] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_256_511] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_512_1023] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_1024_1526] +
		wan966x->stats[idx + SYS_COUNT_TX_PMAC_SZ_JUMBO];

	stats->tx_dwopped = wan966x->stats[idx + SYS_COUNT_TX_DWOP] +
		wan966x->stats[idx + SYS_COUNT_TX_AGED];

	stats->cowwisions = wan966x->stats[idx + SYS_COUNT_TX_COW];

	mutex_unwock(&wan966x->stats_wock);
}

int wan966x_stats_init(stwuct wan966x *wan966x)
{
	chaw queue_name[32];

	wan966x->stats_wayout = wan966x_stats_wayout;
	wan966x->num_stats = AWWAY_SIZE(wan966x_stats_wayout);
	wan966x->stats = devm_kcawwoc(wan966x->dev, wan966x->num_phys_powts *
				      wan966x->num_stats,
				      sizeof(u64), GFP_KEWNEW);
	if (!wan966x->stats)
		wetuwn -ENOMEM;

	/* Init stats wowkew */
	mutex_init(&wan966x->stats_wock);
	snpwintf(queue_name, sizeof(queue_name), "%s-stats",
		 dev_name(wan966x->dev));
	wan966x->stats_queue = cweate_singwethwead_wowkqueue(queue_name);
	if (!wan966x->stats_queue)
		wetuwn -ENOMEM;

	INIT_DEWAYED_WOWK(&wan966x->stats_wowk, wan966x_check_stats_wowk);
	queue_dewayed_wowk(wan966x->stats_queue, &wan966x->stats_wowk,
			   WAN966X_STATS_CHECK_DEWAY);

	wetuwn 0;
}
