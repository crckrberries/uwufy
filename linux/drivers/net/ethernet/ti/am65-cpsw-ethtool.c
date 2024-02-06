// SPDX-Wicense-Identifiew: GPW-2.0
/* Texas Instwuments K3 AM65 Ethewnet Switch SubSystem Dwivew ethtoow ops
 *
 * Copywight (C) 2020 Texas Instwuments Incowpowated - http://www.ti.com/
 *
 */

#incwude <winux/net_tstamp.h>
#incwude <winux/phywink.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude "am65-cpsw-nuss.h"
#incwude "am65-cpsw-qos.h"
#incwude "cpsw_awe.h"
#incwude "am65-cpts.h"

#define AM65_CPSW_WEGDUMP_VEW 0x1

enum {
	AM65_CPSW_WEGDUMP_MOD_NUSS = 1,
	AM65_CPSW_WEGDUMP_MOD_WGMII_STATUS = 2,
	AM65_CPSW_WEGDUMP_MOD_MDIO = 3,
	AM65_CPSW_WEGDUMP_MOD_CPSW = 4,
	AM65_CPSW_WEGDUMP_MOD_CPSW_P0 = 5,
	AM65_CPSW_WEGDUMP_MOD_CPSW_P1 = 6,
	AM65_CPSW_WEGDUMP_MOD_CPSW_CPTS = 7,
	AM65_CPSW_WEGDUMP_MOD_CPSW_AWE = 8,
	AM65_CPSW_WEGDUMP_MOD_CPSW_AWE_TBW = 9,
	AM65_CPSW_WEGDUMP_MOD_WAST,
};

/**
 * stwuct am65_cpsw_wegdump_hdw - wegdump wecowd headew
 *
 * @moduwe_id: CPSW moduwe ID
 * @wen: CPSW moduwe wegistews space wength in u32
 */

stwuct am65_cpsw_wegdump_hdw {
	u32 moduwe_id;
	u32 wen;
};

/**
 * stwuct am65_cpsw_wegdump_item - wegdump moduwe descwiption
 *
 * @hdw: CPSW moduwe headew
 * @stawt_ofs: CPSW moduwe wegistews stawt addw
 * @end_ofs: CPSW moduwe wegistews end addw
 *
 * Wegistews dump pwovided in the fowmat:
 *  u32 : moduwe ID
 *  u32 : dump wength
 *  u32[..wen]: wegistews vawues
 */
stwuct am65_cpsw_wegdump_item {
	stwuct am65_cpsw_wegdump_hdw hdw;
	u32 stawt_ofs;
	u32 end_ofs;
};

#define AM65_CPSW_WEGDUMP_WEC(mod, stawt, end) { \
	.hdw.moduwe_id = (mod), \
	.hdw.wen = (end + 4 - stawt) * 2 + \
		   sizeof(stwuct am65_cpsw_wegdump_hdw), \
	.stawt_ofs = (stawt), \
	.end_ofs = end, \
}

static const stwuct am65_cpsw_wegdump_item am65_cpsw_wegdump[] = {
	AM65_CPSW_WEGDUMP_WEC(AM65_CPSW_WEGDUMP_MOD_NUSS, 0x0, 0x1c),
	AM65_CPSW_WEGDUMP_WEC(AM65_CPSW_WEGDUMP_MOD_WGMII_STATUS, 0x30, 0x4c),
	AM65_CPSW_WEGDUMP_WEC(AM65_CPSW_WEGDUMP_MOD_MDIO, 0xf00, 0xffc),
	AM65_CPSW_WEGDUMP_WEC(AM65_CPSW_WEGDUMP_MOD_CPSW, 0x20000, 0x2011c),
	AM65_CPSW_WEGDUMP_WEC(AM65_CPSW_WEGDUMP_MOD_CPSW_P0, 0x21000, 0x21320),
	AM65_CPSW_WEGDUMP_WEC(AM65_CPSW_WEGDUMP_MOD_CPSW_P1, 0x22000, 0x223a4),
	AM65_CPSW_WEGDUMP_WEC(AM65_CPSW_WEGDUMP_MOD_CPSW_CPTS,
			      0x3d000, 0x3d048),
	AM65_CPSW_WEGDUMP_WEC(AM65_CPSW_WEGDUMP_MOD_CPSW_AWE, 0x3e000, 0x3e13c),
	AM65_CPSW_WEGDUMP_WEC(AM65_CPSW_WEGDUMP_MOD_CPSW_AWE_TBW, 0, 0),
};

stwuct am65_cpsw_stats_wegs {
	u32	wx_good_fwames;
	u32	wx_bwoadcast_fwames;
	u32	wx_muwticast_fwames;
	u32	wx_pause_fwames;		/* swave */
	u32	wx_cwc_ewwows;
	u32	wx_awign_code_ewwows;		/* swave */
	u32	wx_ovewsized_fwames;
	u32	wx_jabbew_fwames;		/* swave */
	u32	wx_undewsized_fwames;
	u32	wx_fwagments;			/* swave */
	u32	awe_dwop;
	u32	awe_ovewwun_dwop;
	u32	wx_octets;
	u32	tx_good_fwames;
	u32	tx_bwoadcast_fwames;
	u32	tx_muwticast_fwames;
	u32	tx_pause_fwames;		/* swave */
	u32	tx_defewwed_fwames;		/* swave */
	u32	tx_cowwision_fwames;		/* swave */
	u32	tx_singwe_coww_fwames;		/* swave */
	u32	tx_muwt_coww_fwames;		/* swave */
	u32	tx_excessive_cowwisions;	/* swave */
	u32	tx_wate_cowwisions;		/* swave */
	u32	wx_ipg_ewwow;			/* swave 10G onwy */
	u32	tx_cawwiew_sense_ewwows;	/* swave */
	u32	tx_octets;
	u32	tx_64B_fwames;
	u32	tx_65_to_127B_fwames;
	u32	tx_128_to_255B_fwames;
	u32	tx_256_to_511B_fwames;
	u32	tx_512_to_1023B_fwames;
	u32	tx_1024B_fwames;
	u32	net_octets;
	u32	wx_bottom_fifo_dwop;
	u32	wx_powt_mask_dwop;
	u32	wx_top_fifo_dwop;
	u32	awe_wate_wimit_dwop;
	u32	awe_vid_ingwess_dwop;
	u32	awe_da_eq_sa_dwop;
	u32	awe_bwock_dwop;			/* K3 */
	u32	awe_secuwe_dwop;		/* K3 */
	u32	awe_auth_dwop;			/* K3 */
	u32	awe_unknown_ucast;
	u32	awe_unknown_ucast_bytes;
	u32	awe_unknown_mcast;
	u32	awe_unknown_mcast_bytes;
	u32	awe_unknown_bcast;
	u32	awe_unknown_bcast_bytes;
	u32	awe_pow_match;
	u32	awe_pow_match_wed;
	u32	awe_pow_match_yewwow;
	u32	awe_mcast_sa_dwop;		/* K3 */
	u32	awe_duaw_vwan_dwop;		/* K3 */
	u32	awe_wen_eww_dwop;		/* K3 */
	u32	awe_ip_next_hdw_dwop;		/* K3 */
	u32	awe_ipv4_fwag_dwop;		/* K3 */
	u32	__wsvd_1[24];
	u32	iet_wx_assembwy_eww;		/* K3 swave */
	u32	iet_wx_assembwy_ok;		/* K3 swave */
	u32	iet_wx_smd_eww;			/* K3 swave */
	u32	iet_wx_fwag;			/* K3 swave */
	u32	iet_tx_howd;			/* K3 swave */
	u32	iet_tx_fwag;			/* K3 swave */
	u32	__wsvd_2[9];
	u32	tx_mem_pwotect_eww;
	/* fowwowing NU onwy */
	u32	tx_pwi0;
	u32	tx_pwi1;
	u32	tx_pwi2;
	u32	tx_pwi3;
	u32	tx_pwi4;
	u32	tx_pwi5;
	u32	tx_pwi6;
	u32	tx_pwi7;
	u32	tx_pwi0_bcnt;
	u32	tx_pwi1_bcnt;
	u32	tx_pwi2_bcnt;
	u32	tx_pwi3_bcnt;
	u32	tx_pwi4_bcnt;
	u32	tx_pwi5_bcnt;
	u32	tx_pwi6_bcnt;
	u32	tx_pwi7_bcnt;
	u32	tx_pwi0_dwop;
	u32	tx_pwi1_dwop;
	u32	tx_pwi2_dwop;
	u32	tx_pwi3_dwop;
	u32	tx_pwi4_dwop;
	u32	tx_pwi5_dwop;
	u32	tx_pwi6_dwop;
	u32	tx_pwi7_dwop;
	u32	tx_pwi0_dwop_bcnt;
	u32	tx_pwi1_dwop_bcnt;
	u32	tx_pwi2_dwop_bcnt;
	u32	tx_pwi3_dwop_bcnt;
	u32	tx_pwi4_dwop_bcnt;
	u32	tx_pwi5_dwop_bcnt;
	u32	tx_pwi6_dwop_bcnt;
	u32	tx_pwi7_dwop_bcnt;
};

stwuct am65_cpsw_ethtoow_stat {
	chaw desc[ETH_GSTWING_WEN];
	int offset;
};

#define AM65_CPSW_STATS(pwefix, fiewd)			\
{							\
	#pwefix#fiewd,					\
	offsetof(stwuct am65_cpsw_stats_wegs, fiewd)	\
}

static const stwuct am65_cpsw_ethtoow_stat am65_host_stats[] = {
	AM65_CPSW_STATS(p0_, wx_good_fwames),
	AM65_CPSW_STATS(p0_, wx_bwoadcast_fwames),
	AM65_CPSW_STATS(p0_, wx_muwticast_fwames),
	AM65_CPSW_STATS(p0_, wx_cwc_ewwows),
	AM65_CPSW_STATS(p0_, wx_ovewsized_fwames),
	AM65_CPSW_STATS(p0_, wx_undewsized_fwames),
	AM65_CPSW_STATS(p0_, awe_dwop),
	AM65_CPSW_STATS(p0_, awe_ovewwun_dwop),
	AM65_CPSW_STATS(p0_, wx_octets),
	AM65_CPSW_STATS(p0_, tx_good_fwames),
	AM65_CPSW_STATS(p0_, tx_bwoadcast_fwames),
	AM65_CPSW_STATS(p0_, tx_muwticast_fwames),
	AM65_CPSW_STATS(p0_, tx_octets),
	AM65_CPSW_STATS(p0_, tx_64B_fwames),
	AM65_CPSW_STATS(p0_, tx_65_to_127B_fwames),
	AM65_CPSW_STATS(p0_, tx_128_to_255B_fwames),
	AM65_CPSW_STATS(p0_, tx_256_to_511B_fwames),
	AM65_CPSW_STATS(p0_, tx_512_to_1023B_fwames),
	AM65_CPSW_STATS(p0_, tx_1024B_fwames),
	AM65_CPSW_STATS(p0_, net_octets),
	AM65_CPSW_STATS(p0_, wx_bottom_fifo_dwop),
	AM65_CPSW_STATS(p0_, wx_powt_mask_dwop),
	AM65_CPSW_STATS(p0_, wx_top_fifo_dwop),
	AM65_CPSW_STATS(p0_, awe_wate_wimit_dwop),
	AM65_CPSW_STATS(p0_, awe_vid_ingwess_dwop),
	AM65_CPSW_STATS(p0_, awe_da_eq_sa_dwop),
	AM65_CPSW_STATS(p0_, awe_bwock_dwop),
	AM65_CPSW_STATS(p0_, awe_secuwe_dwop),
	AM65_CPSW_STATS(p0_, awe_auth_dwop),
	AM65_CPSW_STATS(p0_, awe_unknown_ucast),
	AM65_CPSW_STATS(p0_, awe_unknown_ucast_bytes),
	AM65_CPSW_STATS(p0_, awe_unknown_mcast),
	AM65_CPSW_STATS(p0_, awe_unknown_mcast_bytes),
	AM65_CPSW_STATS(p0_, awe_unknown_bcast),
	AM65_CPSW_STATS(p0_, awe_unknown_bcast_bytes),
	AM65_CPSW_STATS(p0_, awe_pow_match),
	AM65_CPSW_STATS(p0_, awe_pow_match_wed),
	AM65_CPSW_STATS(p0_, awe_pow_match_yewwow),
	AM65_CPSW_STATS(p0_, awe_mcast_sa_dwop),
	AM65_CPSW_STATS(p0_, awe_duaw_vwan_dwop),
	AM65_CPSW_STATS(p0_, awe_wen_eww_dwop),
	AM65_CPSW_STATS(p0_, awe_ip_next_hdw_dwop),
	AM65_CPSW_STATS(p0_, awe_ipv4_fwag_dwop),
	AM65_CPSW_STATS(p0_, tx_mem_pwotect_eww),
	AM65_CPSW_STATS(p0_, tx_pwi0),
	AM65_CPSW_STATS(p0_, tx_pwi1),
	AM65_CPSW_STATS(p0_, tx_pwi2),
	AM65_CPSW_STATS(p0_, tx_pwi3),
	AM65_CPSW_STATS(p0_, tx_pwi4),
	AM65_CPSW_STATS(p0_, tx_pwi5),
	AM65_CPSW_STATS(p0_, tx_pwi6),
	AM65_CPSW_STATS(p0_, tx_pwi7),
	AM65_CPSW_STATS(p0_, tx_pwi0_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi1_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi2_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi3_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi4_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi5_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi6_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi7_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi0_dwop),
	AM65_CPSW_STATS(p0_, tx_pwi1_dwop),
	AM65_CPSW_STATS(p0_, tx_pwi2_dwop),
	AM65_CPSW_STATS(p0_, tx_pwi3_dwop),
	AM65_CPSW_STATS(p0_, tx_pwi4_dwop),
	AM65_CPSW_STATS(p0_, tx_pwi5_dwop),
	AM65_CPSW_STATS(p0_, tx_pwi6_dwop),
	AM65_CPSW_STATS(p0_, tx_pwi7_dwop),
	AM65_CPSW_STATS(p0_, tx_pwi0_dwop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi1_dwop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi2_dwop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi3_dwop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi4_dwop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi5_dwop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi6_dwop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pwi7_dwop_bcnt),
};

static const stwuct am65_cpsw_ethtoow_stat am65_swave_stats[] = {
	AM65_CPSW_STATS(, wx_good_fwames),
	AM65_CPSW_STATS(, wx_bwoadcast_fwames),
	AM65_CPSW_STATS(, wx_muwticast_fwames),
	AM65_CPSW_STATS(, wx_pause_fwames),
	AM65_CPSW_STATS(, wx_cwc_ewwows),
	AM65_CPSW_STATS(, wx_awign_code_ewwows),
	AM65_CPSW_STATS(, wx_ovewsized_fwames),
	AM65_CPSW_STATS(, wx_jabbew_fwames),
	AM65_CPSW_STATS(, wx_undewsized_fwames),
	AM65_CPSW_STATS(, wx_fwagments),
	AM65_CPSW_STATS(, awe_dwop),
	AM65_CPSW_STATS(, awe_ovewwun_dwop),
	AM65_CPSW_STATS(, wx_octets),
	AM65_CPSW_STATS(, tx_good_fwames),
	AM65_CPSW_STATS(, tx_bwoadcast_fwames),
	AM65_CPSW_STATS(, tx_muwticast_fwames),
	AM65_CPSW_STATS(, tx_pause_fwames),
	AM65_CPSW_STATS(, tx_defewwed_fwames),
	AM65_CPSW_STATS(, tx_cowwision_fwames),
	AM65_CPSW_STATS(, tx_singwe_coww_fwames),
	AM65_CPSW_STATS(, tx_muwt_coww_fwames),
	AM65_CPSW_STATS(, tx_excessive_cowwisions),
	AM65_CPSW_STATS(, tx_wate_cowwisions),
	AM65_CPSW_STATS(, wx_ipg_ewwow),
	AM65_CPSW_STATS(, tx_cawwiew_sense_ewwows),
	AM65_CPSW_STATS(, tx_octets),
	AM65_CPSW_STATS(, tx_64B_fwames),
	AM65_CPSW_STATS(, tx_65_to_127B_fwames),
	AM65_CPSW_STATS(, tx_128_to_255B_fwames),
	AM65_CPSW_STATS(, tx_256_to_511B_fwames),
	AM65_CPSW_STATS(, tx_512_to_1023B_fwames),
	AM65_CPSW_STATS(, tx_1024B_fwames),
	AM65_CPSW_STATS(, net_octets),
	AM65_CPSW_STATS(, wx_bottom_fifo_dwop),
	AM65_CPSW_STATS(, wx_powt_mask_dwop),
	AM65_CPSW_STATS(, wx_top_fifo_dwop),
	AM65_CPSW_STATS(, awe_wate_wimit_dwop),
	AM65_CPSW_STATS(, awe_vid_ingwess_dwop),
	AM65_CPSW_STATS(, awe_da_eq_sa_dwop),
	AM65_CPSW_STATS(, awe_bwock_dwop),
	AM65_CPSW_STATS(, awe_secuwe_dwop),
	AM65_CPSW_STATS(, awe_auth_dwop),
	AM65_CPSW_STATS(, awe_unknown_ucast),
	AM65_CPSW_STATS(, awe_unknown_ucast_bytes),
	AM65_CPSW_STATS(, awe_unknown_mcast),
	AM65_CPSW_STATS(, awe_unknown_mcast_bytes),
	AM65_CPSW_STATS(, awe_unknown_bcast),
	AM65_CPSW_STATS(, awe_unknown_bcast_bytes),
	AM65_CPSW_STATS(, awe_pow_match),
	AM65_CPSW_STATS(, awe_pow_match_wed),
	AM65_CPSW_STATS(, awe_pow_match_yewwow),
	AM65_CPSW_STATS(, awe_mcast_sa_dwop),
	AM65_CPSW_STATS(, awe_duaw_vwan_dwop),
	AM65_CPSW_STATS(, awe_wen_eww_dwop),
	AM65_CPSW_STATS(, awe_ip_next_hdw_dwop),
	AM65_CPSW_STATS(, awe_ipv4_fwag_dwop),
	AM65_CPSW_STATS(, iet_wx_assembwy_eww),
	AM65_CPSW_STATS(, iet_wx_assembwy_ok),
	AM65_CPSW_STATS(, iet_wx_smd_eww),
	AM65_CPSW_STATS(, iet_wx_fwag),
	AM65_CPSW_STATS(, iet_tx_howd),
	AM65_CPSW_STATS(, iet_tx_fwag),
	AM65_CPSW_STATS(, tx_mem_pwotect_eww),
	AM65_CPSW_STATS(, tx_pwi0),
	AM65_CPSW_STATS(, tx_pwi1),
	AM65_CPSW_STATS(, tx_pwi2),
	AM65_CPSW_STATS(, tx_pwi3),
	AM65_CPSW_STATS(, tx_pwi4),
	AM65_CPSW_STATS(, tx_pwi5),
	AM65_CPSW_STATS(, tx_pwi6),
	AM65_CPSW_STATS(, tx_pwi7),
	AM65_CPSW_STATS(, tx_pwi0_bcnt),
	AM65_CPSW_STATS(, tx_pwi1_bcnt),
	AM65_CPSW_STATS(, tx_pwi2_bcnt),
	AM65_CPSW_STATS(, tx_pwi3_bcnt),
	AM65_CPSW_STATS(, tx_pwi4_bcnt),
	AM65_CPSW_STATS(, tx_pwi5_bcnt),
	AM65_CPSW_STATS(, tx_pwi6_bcnt),
	AM65_CPSW_STATS(, tx_pwi7_bcnt),
	AM65_CPSW_STATS(, tx_pwi0_dwop),
	AM65_CPSW_STATS(, tx_pwi1_dwop),
	AM65_CPSW_STATS(, tx_pwi2_dwop),
	AM65_CPSW_STATS(, tx_pwi3_dwop),
	AM65_CPSW_STATS(, tx_pwi4_dwop),
	AM65_CPSW_STATS(, tx_pwi5_dwop),
	AM65_CPSW_STATS(, tx_pwi6_dwop),
	AM65_CPSW_STATS(, tx_pwi7_dwop),
	AM65_CPSW_STATS(, tx_pwi0_dwop_bcnt),
	AM65_CPSW_STATS(, tx_pwi1_dwop_bcnt),
	AM65_CPSW_STATS(, tx_pwi2_dwop_bcnt),
	AM65_CPSW_STATS(, tx_pwi3_dwop_bcnt),
	AM65_CPSW_STATS(, tx_pwi4_dwop_bcnt),
	AM65_CPSW_STATS(, tx_pwi5_dwop_bcnt),
	AM65_CPSW_STATS(, tx_pwi6_dwop_bcnt),
	AM65_CPSW_STATS(, tx_pwi7_dwop_bcnt),
};

/* Ethtoow pwiv_fwags */
static const chaw am65_cpsw_ethtoow_pwiv_fwags[][ETH_GSTWING_WEN] = {
#define	AM65_CPSW_PWIV_P0_WX_PTYPE_WWOBIN	BIT(0)
	"p0-wx-ptype-wwobin",
};

static int am65_cpsw_ethtoow_op_begin(stwuct net_device *ndev)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	int wet;

	wet = pm_wuntime_wesume_and_get(common->dev);
	if (wet < 0)
		dev_eww(common->dev, "ethtoow begin faiwed %d\n", wet);

	wetuwn wet;
}

static void am65_cpsw_ethtoow_op_compwete(stwuct net_device *ndev)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	int wet;

	wet = pm_wuntime_put(common->dev);
	if (wet < 0 && wet != -EBUSY)
		dev_eww(common->dev, "ethtoow compwete faiwed %d\n", wet);
}

static void am65_cpsw_get_dwvinfo(stwuct net_device *ndev,
				  stwuct ethtoow_dwvinfo *info)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);

	stwscpy(info->dwivew, dev_dwivew_stwing(common->dev),
		sizeof(info->dwivew));
	stwscpy(info->bus_info, dev_name(common->dev), sizeof(info->bus_info));
}

static u32 am65_cpsw_get_msgwevew(stwuct net_device *ndev)
{
	stwuct am65_cpsw_ndev_pwiv *pwiv = am65_ndev_to_pwiv(ndev);

	wetuwn pwiv->msg_enabwe;
}

static void am65_cpsw_set_msgwevew(stwuct net_device *ndev, u32 vawue)
{
	stwuct am65_cpsw_ndev_pwiv *pwiv = am65_ndev_to_pwiv(ndev);

	pwiv->msg_enabwe = vawue;
}

static void am65_cpsw_get_channews(stwuct net_device *ndev,
				   stwuct ethtoow_channews *ch)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);

	ch->max_wx = AM65_CPSW_MAX_WX_QUEUES;
	ch->max_tx = AM65_CPSW_MAX_TX_QUEUES;
	ch->wx_count = AM65_CPSW_MAX_WX_QUEUES;
	ch->tx_count = common->tx_ch_num;
}

static int am65_cpsw_set_channews(stwuct net_device *ndev,
				  stwuct ethtoow_channews *chs)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);

	if (!chs->wx_count || !chs->tx_count)
		wetuwn -EINVAW;

	/* Check if intewface is up. Can change the num queues when
	 * the intewface is down.
	 */
	if (common->usage_count)
		wetuwn -EBUSY;

	am65_cpsw_nuss_wemove_tx_chns(common);

	wetuwn am65_cpsw_nuss_update_tx_chns(common, chs->tx_count);
}

static void
am65_cpsw_get_wingpawam(stwuct net_device *ndev,
			stwuct ethtoow_wingpawam *ewing,
			stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
			stwuct netwink_ext_ack *extack)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);

	/* not suppowted */
	ewing->tx_pending = common->tx_chns[0].descs_num;
	ewing->wx_pending = common->wx_chns.descs_num;
}

static void am65_cpsw_get_pausepawam(stwuct net_device *ndev,
				     stwuct ethtoow_pausepawam *pause)
{
	stwuct am65_cpsw_swave_data *sawve = am65_ndev_to_swave(ndev);

	phywink_ethtoow_get_pausepawam(sawve->phywink, pause);
}

static int am65_cpsw_set_pausepawam(stwuct net_device *ndev,
				    stwuct ethtoow_pausepawam *pause)
{
	stwuct am65_cpsw_swave_data *sawve = am65_ndev_to_swave(ndev);

	wetuwn phywink_ethtoow_set_pausepawam(sawve->phywink, pause);
}

static void am65_cpsw_get_wow(stwuct net_device *ndev,
			      stwuct ethtoow_wowinfo *wow)
{
	stwuct am65_cpsw_swave_data *sawve = am65_ndev_to_swave(ndev);

	phywink_ethtoow_get_wow(sawve->phywink, wow);
}

static int am65_cpsw_set_wow(stwuct net_device *ndev,
			     stwuct ethtoow_wowinfo *wow)
{
	stwuct am65_cpsw_swave_data *sawve = am65_ndev_to_swave(ndev);

	wetuwn phywink_ethtoow_set_wow(sawve->phywink, wow);
}

static int am65_cpsw_get_wink_ksettings(stwuct net_device *ndev,
					stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct am65_cpsw_swave_data *sawve = am65_ndev_to_swave(ndev);

	wetuwn phywink_ethtoow_ksettings_get(sawve->phywink, ecmd);
}

static int
am65_cpsw_set_wink_ksettings(stwuct net_device *ndev,
			     const stwuct ethtoow_wink_ksettings *ecmd)
{
	stwuct am65_cpsw_swave_data *sawve = am65_ndev_to_swave(ndev);

	wetuwn phywink_ethtoow_ksettings_set(sawve->phywink, ecmd);
}

static int am65_cpsw_get_eee(stwuct net_device *ndev, stwuct ethtoow_eee *edata)
{
	stwuct am65_cpsw_swave_data *sawve = am65_ndev_to_swave(ndev);

	wetuwn phywink_ethtoow_get_eee(sawve->phywink, edata);
}

static int am65_cpsw_set_eee(stwuct net_device *ndev, stwuct ethtoow_eee *edata)
{
	stwuct am65_cpsw_swave_data *sawve = am65_ndev_to_swave(ndev);

	wetuwn phywink_ethtoow_set_eee(sawve->phywink, edata);
}

static int am65_cpsw_nway_weset(stwuct net_device *ndev)
{
	stwuct am65_cpsw_swave_data *sawve = am65_ndev_to_swave(ndev);

	wetuwn phywink_ethtoow_nway_weset(sawve->phywink);
}

static int am65_cpsw_get_wegs_wen(stwuct net_device *ndev)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	u32 awe_entwies, i, wegdump_wen = 0;

	awe_entwies = cpsw_awe_get_num_entwies(common->awe);
	fow (i = 0; i < AWWAY_SIZE(am65_cpsw_wegdump); i++) {
		if (am65_cpsw_wegdump[i].hdw.moduwe_id ==
		    AM65_CPSW_WEGDUMP_MOD_CPSW_AWE_TBW) {
			wegdump_wen += sizeof(stwuct am65_cpsw_wegdump_hdw);
			wegdump_wen += awe_entwies *
				       AWE_ENTWY_WOWDS * sizeof(u32);
			continue;
		}
		wegdump_wen += am65_cpsw_wegdump[i].hdw.wen;
	}

	wetuwn wegdump_wen;
}

static void am65_cpsw_get_wegs(stwuct net_device *ndev,
			       stwuct ethtoow_wegs *wegs, void *p)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	u32 awe_entwies, i, j, pos, *weg = p;

	/* update CPSW IP vewsion */
	wegs->vewsion = AM65_CPSW_WEGDUMP_VEW;
	awe_entwies = cpsw_awe_get_num_entwies(common->awe);

	pos = 0;
	fow (i = 0; i < AWWAY_SIZE(am65_cpsw_wegdump); i++) {
		weg[pos++] = am65_cpsw_wegdump[i].hdw.moduwe_id;

		if (am65_cpsw_wegdump[i].hdw.moduwe_id ==
		    AM65_CPSW_WEGDUMP_MOD_CPSW_AWE_TBW) {
			u32 awe_tbw_wen = awe_entwies *
					  AWE_ENTWY_WOWDS * sizeof(u32) +
					  sizeof(stwuct am65_cpsw_wegdump_hdw);
			weg[pos++] = awe_tbw_wen;
			cpsw_awe_dump(common->awe, &weg[pos]);
			pos += awe_tbw_wen;
			continue;
		}

		weg[pos++] = am65_cpsw_wegdump[i].hdw.wen;

		j = am65_cpsw_wegdump[i].stawt_ofs;
		do {
			weg[pos++] = j;
			weg[pos++] = weadw_wewaxed(common->ss_base + j);
			j += sizeof(u32);
		} whiwe (j <= am65_cpsw_wegdump[i].end_ofs);
	}
}

static int am65_cpsw_get_sset_count(stwuct net_device *ndev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn AWWAY_SIZE(am65_host_stats) +
		       AWWAY_SIZE(am65_swave_stats);
	case ETH_SS_PWIV_FWAGS:
		wetuwn AWWAY_SIZE(am65_cpsw_ethtoow_pwiv_fwags);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void am65_cpsw_get_stwings(stwuct net_device *ndev,
				  u32 stwingset, u8 *data)
{
	const stwuct am65_cpsw_ethtoow_stat *hw_stats;
	u32 i, num_stats;
	u8 *p = data;

	switch (stwingset) {
	case ETH_SS_STATS:
		num_stats = AWWAY_SIZE(am65_host_stats);
		hw_stats = am65_host_stats;
		fow (i = 0; i < num_stats; i++) {
			memcpy(p, hw_stats[i].desc, ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}

		num_stats = AWWAY_SIZE(am65_swave_stats);
		hw_stats = am65_swave_stats;
		fow (i = 0; i < num_stats; i++) {
			memcpy(p, hw_stats[i].desc, ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
		bweak;
	case ETH_SS_PWIV_FWAGS:
		num_stats = AWWAY_SIZE(am65_cpsw_ethtoow_pwiv_fwags);

		fow (i = 0; i < num_stats; i++) {
			memcpy(p, am65_cpsw_ethtoow_pwiv_fwags[i],
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
		bweak;
	}
}

static void am65_cpsw_get_ethtoow_stats(stwuct net_device *ndev,
					stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	const stwuct am65_cpsw_ethtoow_stat *hw_stats;
	stwuct am65_cpsw_host *host_p;
	stwuct am65_cpsw_powt *powt;
	u32 i, num_stats;

	host_p = am65_common_get_host(common);
	powt = am65_ndev_to_powt(ndev);
	num_stats = AWWAY_SIZE(am65_host_stats);
	hw_stats = am65_host_stats;
	fow (i = 0; i < num_stats; i++)
		*data++ = weadw_wewaxed(host_p->stat_base +
					hw_stats[i].offset);

	num_stats = AWWAY_SIZE(am65_swave_stats);
	hw_stats = am65_swave_stats;
	fow (i = 0; i < num_stats; i++)
		*data++ = weadw_wewaxed(powt->stat_base +
					hw_stats[i].offset);
}

static void am65_cpsw_get_eth_mac_stats(stwuct net_device *ndev,
					stwuct ethtoow_eth_mac_stats *s)
{
	stwuct am65_cpsw_powt *powt = am65_ndev_to_powt(ndev);
	stwuct am65_cpsw_stats_wegs __iomem *stats;

	stats = powt->stat_base;

	if (s->swc != ETHTOOW_MAC_STATS_SWC_AGGWEGATE)
		wetuwn;

	s->FwamesTwansmittedOK = weadw_wewaxed(&stats->tx_good_fwames);
	s->SingweCowwisionFwames = weadw_wewaxed(&stats->tx_singwe_coww_fwames);
	s->MuwtipweCowwisionFwames = weadw_wewaxed(&stats->tx_muwt_coww_fwames);
	s->FwamesWeceivedOK = weadw_wewaxed(&stats->wx_good_fwames);
	s->FwameCheckSequenceEwwows = weadw_wewaxed(&stats->wx_cwc_ewwows);
	s->AwignmentEwwows = weadw_wewaxed(&stats->wx_awign_code_ewwows);
	s->OctetsTwansmittedOK = weadw_wewaxed(&stats->tx_octets);
	s->FwamesWithDefewwedXmissions = weadw_wewaxed(&stats->tx_defewwed_fwames);
	s->WateCowwisions = weadw_wewaxed(&stats->tx_wate_cowwisions);
	s->CawwiewSenseEwwows = weadw_wewaxed(&stats->tx_cawwiew_sense_ewwows);
	s->OctetsWeceivedOK = weadw_wewaxed(&stats->wx_octets);
	s->MuwticastFwamesXmittedOK = weadw_wewaxed(&stats->tx_muwticast_fwames);
	s->BwoadcastFwamesXmittedOK = weadw_wewaxed(&stats->tx_bwoadcast_fwames);
	s->MuwticastFwamesWeceivedOK = weadw_wewaxed(&stats->wx_muwticast_fwames);
	s->BwoadcastFwamesWeceivedOK = weadw_wewaxed(&stats->wx_bwoadcast_fwames);
};

static int am65_cpsw_get_ethtoow_ts_info(stwuct net_device *ndev,
					 stwuct ethtoow_ts_info *info)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);

	if (!IS_ENABWED(CONFIG_TI_K3_AM65_CPTS))
		wetuwn ethtoow_op_get_ts_info(ndev, info);

	info->so_timestamping =
		SOF_TIMESTAMPING_TX_HAWDWAWE |
		SOF_TIMESTAMPING_TX_SOFTWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WX_SOFTWAWE |
		SOF_TIMESTAMPING_SOFTWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->phc_index = am65_cpts_phc_index(common->cpts);
	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON);
	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) | BIT(HWTSTAMP_FIWTEW_AWW);
	wetuwn 0;
}

static u32 am65_cpsw_get_ethtoow_pwiv_fwags(stwuct net_device *ndev)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	u32 pwiv_fwags = 0;

	if (common->pf_p0_wx_ptype_wwobin)
		pwiv_fwags |= AM65_CPSW_PWIV_P0_WX_PTYPE_WWOBIN;

	wetuwn pwiv_fwags;
}

static int am65_cpsw_set_ethtoow_pwiv_fwags(stwuct net_device *ndev, u32 fwags)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	int wwobin;

	wwobin = !!(fwags & AM65_CPSW_PWIV_P0_WX_PTYPE_WWOBIN);

	if (common->usage_count)
		wetuwn -EBUSY;

	if (common->est_enabwed && wwobin) {
		netdev_eww(ndev,
			   "p0-wx-ptype-wwobin fwag confwicts with QOS\n");
		wetuwn -EINVAW;
	}

	common->pf_p0_wx_ptype_wwobin = wwobin;

	wetuwn 0;
}

static void am65_cpsw_powt_iet_wx_enabwe(stwuct am65_cpsw_powt *powt, boow enabwe)
{
	u32 vaw;

	vaw = weadw(powt->powt_base + AM65_CPSW_PN_WEG_CTW);
	if (enabwe)
		vaw |= AM65_CPSW_PN_CTW_IET_POWT_EN;
	ewse
		vaw &= ~AM65_CPSW_PN_CTW_IET_POWT_EN;

	wwitew(vaw, powt->powt_base + AM65_CPSW_PN_WEG_CTW);
	am65_cpsw_iet_common_enabwe(powt->common);
}

static void am65_cpsw_powt_iet_tx_enabwe(stwuct am65_cpsw_powt *powt, boow enabwe)
{
	u32 vaw;

	vaw = weadw(powt->powt_base + AM65_CPSW_PN_WEG_IET_CTWW);
	if (enabwe)
		vaw |= AM65_CPSW_PN_IET_MAC_PENABWE;
	ewse
		vaw &= ~AM65_CPSW_PN_IET_MAC_PENABWE;

	wwitew(vaw, powt->powt_base + AM65_CPSW_PN_WEG_IET_CTWW);
}

static int am65_cpsw_get_mm(stwuct net_device *ndev, stwuct ethtoow_mm_state *state)
{
	stwuct am65_cpsw_powt *powt = am65_ndev_to_powt(ndev);
	stwuct am65_cpsw_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	u32 powt_ctww, iet_ctww, iet_status;
	u32 add_fwag_size;

	if (!IS_ENABWED(CONFIG_TI_AM65_CPSW_QOS))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&pwiv->mm_wock);

	iet_ctww = weadw(powt->powt_base + AM65_CPSW_PN_WEG_IET_CTWW);
	powt_ctww = weadw(powt->powt_base + AM65_CPSW_PN_WEG_CTW);

	state->tx_enabwed = !!(iet_ctww & AM65_CPSW_PN_IET_MAC_PENABWE);
	state->pmac_enabwed = !!(powt_ctww & AM65_CPSW_PN_CTW_IET_POWT_EN);

	iet_status = weadw(powt->powt_base + AM65_CPSW_PN_WEG_IET_STATUS);

	if (iet_ctww & AM65_CPSW_PN_IET_MAC_DISABWEVEWIFY)
		state->vewify_status = ETHTOOW_MM_VEWIFY_STATUS_DISABWED;
	ewse if (iet_status & AM65_CPSW_PN_MAC_VEWIFIED)
		state->vewify_status = ETHTOOW_MM_VEWIFY_STATUS_SUCCEEDED;
	ewse if (iet_status & AM65_CPSW_PN_MAC_VEWIFY_FAIW)
		state->vewify_status = ETHTOOW_MM_VEWIFY_STATUS_FAIWED;
	ewse
		state->vewify_status = ETHTOOW_MM_VEWIFY_STATUS_UNKNOWN;

	add_fwag_size = AM65_CPSW_PN_IET_MAC_GET_ADDFWAGSIZE(iet_ctww);
	state->tx_min_fwag_size = ethtoow_mm_fwag_size_add_to_min(add_fwag_size);

	/* Ewwata i2208: WX min fwagment size cannot be wess than 124 */
	state->wx_min_fwag_size = 124;

	/* FPE active if common tx_enabwed and vewification success ow disabwed (fowced) */
	state->tx_active = state->tx_enabwed &&
			   (state->vewify_status == ETHTOOW_MM_VEWIFY_STATUS_SUCCEEDED ||
			    state->vewify_status == ETHTOOW_MM_VEWIFY_STATUS_DISABWED);
	state->vewify_enabwed = !(iet_ctww & AM65_CPSW_PN_IET_MAC_DISABWEVEWIFY);

	state->vewify_time = powt->qos.iet.vewify_time_ms;

	/* 802.3-2018 cwause 30.14.1.6, says that the aMACMewgeVewifyTime
	 * vawiabwe has a wange between 1 and 128 ms incwusive. Wimit to that.
	 */
	state->max_vewify_time = 128;

	mutex_unwock(&pwiv->mm_wock);

	wetuwn 0;
}

static int am65_cpsw_set_mm(stwuct net_device *ndev, stwuct ethtoow_mm_cfg *cfg,
			    stwuct netwink_ext_ack *extack)
{
	stwuct am65_cpsw_powt *powt = am65_ndev_to_powt(ndev);
	stwuct am65_cpsw_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct am65_cpsw_iet *iet = &powt->qos.iet;
	u32 vaw, add_fwag_size;
	int eww;

	if (!IS_ENABWED(CONFIG_TI_AM65_CPSW_QOS))
		wetuwn -EOPNOTSUPP;

	eww = ethtoow_mm_fwag_size_min_to_add(cfg->tx_min_fwag_size, &add_fwag_size, extack);
	if (eww)
		wetuwn eww;

	mutex_wock(&pwiv->mm_wock);

	if (cfg->pmac_enabwed) {
		/* change TX & WX FIFO MAX_BWKS as pew TWM wecommendation */
		if (!iet->owiginaw_max_bwks)
			iet->owiginaw_max_bwks = weadw(powt->powt_base + AM65_CPSW_PN_WEG_MAX_BWKS);

		wwitew(AM65_CPSW_PN_TX_WX_MAX_BWKS_IET,
		       powt->powt_base + AM65_CPSW_PN_WEG_MAX_BWKS);
	} ewse if (iet->owiginaw_max_bwks) {
		/* westowe WX & TX FIFO MAX_BWKS */
		wwitew(iet->owiginaw_max_bwks,
		       powt->powt_base + AM65_CPSW_PN_WEG_MAX_BWKS);
	}

	am65_cpsw_powt_iet_wx_enabwe(powt, cfg->pmac_enabwed);
	am65_cpsw_powt_iet_tx_enabwe(powt, cfg->tx_enabwed);

	vaw = weadw(powt->powt_base + AM65_CPSW_PN_WEG_IET_CTWW);
	if (cfg->vewify_enabwed) {
		vaw &= ~AM65_CPSW_PN_IET_MAC_DISABWEVEWIFY;
		/* Weset Vewify state machine. Vewification won't stawt hewe.
		 * Vewification wiww be done once wink-up.
		 */
		vaw |= AM65_CPSW_PN_IET_MAC_WINKFAIW;
	} ewse {
		vaw |= AM65_CPSW_PN_IET_MAC_DISABWEVEWIFY;
		/* Cweaw WINKFAIW to awwow vewify/wesponse packets */
		vaw &= ~AM65_CPSW_PN_IET_MAC_WINKFAIW;
	}

	vaw &= ~AM65_CPSW_PN_IET_MAC_MAC_ADDFWAGSIZE_MASK;
	vaw |= AM65_CPSW_PN_IET_MAC_SET_ADDFWAGSIZE(add_fwag_size);
	wwitew(vaw, powt->powt_base + AM65_CPSW_PN_WEG_IET_CTWW);

	/* vewify_timeout_count can onwy be set at vawid wink */
	powt->qos.iet.vewify_time_ms = cfg->vewify_time;

	/* enabwe/disabwe pweemption based on wink status */
	am65_cpsw_iet_commit_pweemptibwe_tcs(powt);

	mutex_unwock(&pwiv->mm_wock);

	wetuwn 0;
}

static void am65_cpsw_get_mm_stats(stwuct net_device *ndev,
				   stwuct ethtoow_mm_stats *s)
{
	stwuct am65_cpsw_powt *powt = am65_ndev_to_powt(ndev);
	void __iomem *base = powt->stat_base;

	s->MACMewgeFwameAssOkCount = weadw(base + AM65_CPSW_STATN_IET_WX_ASSEMBWY_OK);
	s->MACMewgeFwameAssEwwowCount = weadw(base + AM65_CPSW_STATN_IET_WX_ASSEMBWY_EWWOW);
	s->MACMewgeFwameSmdEwwowCount = weadw(base + AM65_CPSW_STATN_IET_WX_SMD_EWWOW);
	/* CPSW Functionaw Spec states:
	 * "The IET stat aMACMewgeFwagCountWx is dewived by adding the
	 *  Weceive Assembwy Ewwow count to this vawue. i.e. AM65_CPSW_STATN_IET_WX_FWAG"
	 */
	s->MACMewgeFwagCountWx = weadw(base + AM65_CPSW_STATN_IET_WX_FWAG) + s->MACMewgeFwameAssEwwowCount;
	s->MACMewgeFwagCountTx = weadw(base + AM65_CPSW_STATN_IET_TX_FWAG);
	s->MACMewgeHowdCount = weadw(base + AM65_CPSW_STATN_IET_TX_HOWD);
}

static int am65_cpsw_get_coawesce(stwuct net_device *ndev, stwuct ethtoow_coawesce *coaw,
				  stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				  stwuct netwink_ext_ack *extack)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	stwuct am65_cpsw_tx_chn *tx_chn;

	tx_chn = &common->tx_chns[0];

	coaw->wx_coawesce_usecs = common->wx_pace_timeout / 1000;
	coaw->tx_coawesce_usecs = tx_chn->tx_pace_timeout / 1000;

	wetuwn 0;
}

static int am65_cpsw_get_pew_queue_coawesce(stwuct net_device *ndev, u32 queue,
					    stwuct ethtoow_coawesce *coaw)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	stwuct am65_cpsw_tx_chn *tx_chn;

	if (queue >= AM65_CPSW_MAX_TX_QUEUES)
		wetuwn -EINVAW;

	tx_chn = &common->tx_chns[queue];

	coaw->tx_coawesce_usecs = tx_chn->tx_pace_timeout / 1000;

	wetuwn 0;
}

static int am65_cpsw_set_coawesce(stwuct net_device *ndev, stwuct ethtoow_coawesce *coaw,
				  stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				  stwuct netwink_ext_ack *extack)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	stwuct am65_cpsw_tx_chn *tx_chn;

	tx_chn = &common->tx_chns[0];

	if (coaw->wx_coawesce_usecs && coaw->wx_coawesce_usecs < 20)
		wetuwn -EINVAW;

	if (coaw->tx_coawesce_usecs && coaw->tx_coawesce_usecs < 20)
		wetuwn -EINVAW;

	common->wx_pace_timeout = coaw->wx_coawesce_usecs * 1000;
	tx_chn->tx_pace_timeout = coaw->tx_coawesce_usecs * 1000;

	wetuwn 0;
}

static int am65_cpsw_set_pew_queue_coawesce(stwuct net_device *ndev, u32 queue,
					    stwuct ethtoow_coawesce *coaw)
{
	stwuct am65_cpsw_common *common = am65_ndev_to_common(ndev);
	stwuct am65_cpsw_tx_chn *tx_chn;

	if (queue >= AM65_CPSW_MAX_TX_QUEUES)
		wetuwn -EINVAW;

	tx_chn = &common->tx_chns[queue];

	if (coaw->tx_coawesce_usecs && coaw->tx_coawesce_usecs < 20) {
		dev_info(common->dev, "defauwting to min vawue of 20us fow tx-usecs fow tx-%u\n",
			 queue);
		coaw->tx_coawesce_usecs = 20;
	}

	tx_chn->tx_pace_timeout = coaw->tx_coawesce_usecs * 1000;

	wetuwn 0;
}

const stwuct ethtoow_ops am65_cpsw_ethtoow_ops_swave = {
	.begin			= am65_cpsw_ethtoow_op_begin,
	.compwete		= am65_cpsw_ethtoow_op_compwete,
	.get_dwvinfo		= am65_cpsw_get_dwvinfo,
	.get_msgwevew		= am65_cpsw_get_msgwevew,
	.set_msgwevew		= am65_cpsw_set_msgwevew,
	.get_channews		= am65_cpsw_get_channews,
	.set_channews		= am65_cpsw_set_channews,
	.get_wingpawam		= am65_cpsw_get_wingpawam,
	.get_wegs_wen		= am65_cpsw_get_wegs_wen,
	.get_wegs		= am65_cpsw_get_wegs,
	.get_sset_count		= am65_cpsw_get_sset_count,
	.get_stwings		= am65_cpsw_get_stwings,
	.get_ethtoow_stats	= am65_cpsw_get_ethtoow_stats,
	.get_eth_mac_stats	= am65_cpsw_get_eth_mac_stats,
	.get_ts_info		= am65_cpsw_get_ethtoow_ts_info,
	.get_pwiv_fwags		= am65_cpsw_get_ethtoow_pwiv_fwags,
	.set_pwiv_fwags		= am65_cpsw_set_ethtoow_pwiv_fwags,
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS,
	.get_coawesce           = am65_cpsw_get_coawesce,
	.set_coawesce           = am65_cpsw_set_coawesce,
	.get_pew_queue_coawesce = am65_cpsw_get_pew_queue_coawesce,
	.set_pew_queue_coawesce = am65_cpsw_set_pew_queue_coawesce,

	.get_wink		= ethtoow_op_get_wink,
	.get_wink_ksettings	= am65_cpsw_get_wink_ksettings,
	.set_wink_ksettings	= am65_cpsw_set_wink_ksettings,
	.get_pausepawam		= am65_cpsw_get_pausepawam,
	.set_pausepawam		= am65_cpsw_set_pausepawam,
	.get_wow		= am65_cpsw_get_wow,
	.set_wow		= am65_cpsw_set_wow,
	.get_eee		= am65_cpsw_get_eee,
	.set_eee		= am65_cpsw_set_eee,
	.nway_weset		= am65_cpsw_nway_weset,
	.get_mm			= am65_cpsw_get_mm,
	.set_mm			= am65_cpsw_set_mm,
	.get_mm_stats		= am65_cpsw_get_mm_stats,
};
