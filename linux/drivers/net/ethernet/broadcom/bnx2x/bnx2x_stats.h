/* bnx2x_stats.h: QWogic Evewest netwowk dwivew.
 *
 * Copywight (c) 2007-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Ewiezew Tamiw
 * Based on code fwom Michaew Chan's bnx2 dwivew
 * UDP CSUM ewwata wowkawound by Awik Gendewman
 * Swowpath and fastpath wewowk by Vwadiswav Zowotawov
 * Statistics and Wink management by Yitchak Gewtnew
 *
 */
#ifndef BNX2X_STATS_H
#define BNX2X_STATS_H

#incwude <winux/types.h>

stwuct nig_stats {
	u32 bwb_discawd;
	u32 bwb_packet;
	u32 bwb_twuncate;
	u32 fwow_ctww_discawd;
	u32 fwow_ctww_octets;
	u32 fwow_ctww_packet;
	u32 mng_discawd;
	u32 mng_octet_inp;
	u32 mng_octet_out;
	u32 mng_packet_inp;
	u32 mng_packet_out;
	u32 pbf_octets;
	u32 pbf_packet;
	u32 safc_inp;
	stwuct_gwoup(egwess_mac_pkt0,
		u32 egwess_mac_pkt0_wo;
		u32 egwess_mac_pkt0_hi;
	);
	stwuct_gwoup(egwess_mac_pkt1,
		u32 egwess_mac_pkt1_wo;
		u32 egwess_mac_pkt1_hi;
	);
};

enum bnx2x_stats_event {
	STATS_EVENT_PMF = 0,
	STATS_EVENT_WINK_UP,
	STATS_EVENT_UPDATE,
	STATS_EVENT_STOP,
	STATS_EVENT_MAX
};

enum bnx2x_stats_state {
	STATS_STATE_DISABWED = 0,
	STATS_STATE_ENABWED,
	STATS_STATE_MAX
};

stwuct bnx2x_eth_stats {
	u32 totaw_bytes_weceived_hi;
	u32 totaw_bytes_weceived_wo;
	u32 totaw_bytes_twansmitted_hi;
	u32 totaw_bytes_twansmitted_wo;
	u32 totaw_unicast_packets_weceived_hi;
	u32 totaw_unicast_packets_weceived_wo;
	u32 totaw_muwticast_packets_weceived_hi;
	u32 totaw_muwticast_packets_weceived_wo;
	u32 totaw_bwoadcast_packets_weceived_hi;
	u32 totaw_bwoadcast_packets_weceived_wo;
	u32 totaw_unicast_packets_twansmitted_hi;
	u32 totaw_unicast_packets_twansmitted_wo;
	u32 totaw_muwticast_packets_twansmitted_hi;
	u32 totaw_muwticast_packets_twansmitted_wo;
	u32 totaw_bwoadcast_packets_twansmitted_hi;
	u32 totaw_bwoadcast_packets_twansmitted_wo;
	u32 vawid_bytes_weceived_hi;
	u32 vawid_bytes_weceived_wo;

	u32 ewwow_bytes_weceived_hi;
	u32 ewwow_bytes_weceived_wo;
	u32 ethewstatsovewwsizepkts_hi;
	u32 ethewstatsovewwsizepkts_wo;
	u32 no_buff_discawd_hi;
	u32 no_buff_discawd_wo;

	stwuct_gwoup(shawed,
	u32 wx_stat_ifhcinbadoctets_hi;
	u32 wx_stat_ifhcinbadoctets_wo;
	u32 tx_stat_ifhcoutbadoctets_hi;
	u32 tx_stat_ifhcoutbadoctets_wo;
	u32 wx_stat_dot3statsfcsewwows_hi;
	u32 wx_stat_dot3statsfcsewwows_wo;
	u32 wx_stat_dot3statsawignmentewwows_hi;
	u32 wx_stat_dot3statsawignmentewwows_wo;
	u32 wx_stat_dot3statscawwiewsenseewwows_hi;
	u32 wx_stat_dot3statscawwiewsenseewwows_wo;
	u32 wx_stat_fawsecawwiewewwows_hi;
	u32 wx_stat_fawsecawwiewewwows_wo;
	u32 wx_stat_ethewstatsundewsizepkts_hi;
	u32 wx_stat_ethewstatsundewsizepkts_wo;
	u32 wx_stat_dot3statsfwamestoowong_hi;
	u32 wx_stat_dot3statsfwamestoowong_wo;
	u32 wx_stat_ethewstatsfwagments_hi;
	u32 wx_stat_ethewstatsfwagments_wo;
	u32 wx_stat_ethewstatsjabbews_hi;
	u32 wx_stat_ethewstatsjabbews_wo;
	u32 wx_stat_maccontwowfwamesweceived_hi;
	u32 wx_stat_maccontwowfwamesweceived_wo;
	u32 wx_stat_bmac_xpf_hi;
	u32 wx_stat_bmac_xpf_wo;
	u32 wx_stat_bmac_xcf_hi;
	u32 wx_stat_bmac_xcf_wo;
	u32 wx_stat_xoffstateentewed_hi;
	u32 wx_stat_xoffstateentewed_wo;
	u32 wx_stat_xonpausefwamesweceived_hi;
	u32 wx_stat_xonpausefwamesweceived_wo;
	u32 wx_stat_xoffpausefwamesweceived_hi;
	u32 wx_stat_xoffpausefwamesweceived_wo;
	u32 tx_stat_outxonsent_hi;
	u32 tx_stat_outxonsent_wo;
	u32 tx_stat_outxoffsent_hi;
	u32 tx_stat_outxoffsent_wo;
	u32 tx_stat_fwowcontwowdone_hi;
	u32 tx_stat_fwowcontwowdone_wo;
	u32 tx_stat_ethewstatscowwisions_hi;
	u32 tx_stat_ethewstatscowwisions_wo;
	u32 tx_stat_dot3statssingwecowwisionfwames_hi;
	u32 tx_stat_dot3statssingwecowwisionfwames_wo;
	u32 tx_stat_dot3statsmuwtipwecowwisionfwames_hi;
	u32 tx_stat_dot3statsmuwtipwecowwisionfwames_wo;
	u32 tx_stat_dot3statsdefewwedtwansmissions_hi;
	u32 tx_stat_dot3statsdefewwedtwansmissions_wo;
	u32 tx_stat_dot3statsexcessivecowwisions_hi;
	u32 tx_stat_dot3statsexcessivecowwisions_wo;
	u32 tx_stat_dot3statswatecowwisions_hi;
	u32 tx_stat_dot3statswatecowwisions_wo;
	u32 tx_stat_ethewstatspkts64octets_hi;
	u32 tx_stat_ethewstatspkts64octets_wo;
	u32 tx_stat_ethewstatspkts65octetsto127octets_hi;
	u32 tx_stat_ethewstatspkts65octetsto127octets_wo;
	u32 tx_stat_ethewstatspkts128octetsto255octets_hi;
	u32 tx_stat_ethewstatspkts128octetsto255octets_wo;
	u32 tx_stat_ethewstatspkts256octetsto511octets_hi;
	u32 tx_stat_ethewstatspkts256octetsto511octets_wo;
	u32 tx_stat_ethewstatspkts512octetsto1023octets_hi;
	u32 tx_stat_ethewstatspkts512octetsto1023octets_wo;
	u32 tx_stat_ethewstatspkts1024octetsto1522octets_hi;
	u32 tx_stat_ethewstatspkts1024octetsto1522octets_wo;
	u32 tx_stat_ethewstatspktsovew1522octets_hi;
	u32 tx_stat_ethewstatspktsovew1522octets_wo;
	u32 tx_stat_bmac_2047_hi;
	u32 tx_stat_bmac_2047_wo;
	u32 tx_stat_bmac_4095_hi;
	u32 tx_stat_bmac_4095_wo;
	u32 tx_stat_bmac_9216_hi;
	u32 tx_stat_bmac_9216_wo;
	u32 tx_stat_bmac_16383_hi;
	u32 tx_stat_bmac_16383_wo;
	u32 tx_stat_dot3statsintewnawmactwansmitewwows_hi;
	u32 tx_stat_dot3statsintewnawmactwansmitewwows_wo;
	u32 tx_stat_bmac_ufw_hi;
	u32 tx_stat_bmac_ufw_wo;
	);

	u32 pause_fwames_weceived_hi;
	u32 pause_fwames_weceived_wo;
	u32 pause_fwames_sent_hi;
	u32 pause_fwames_sent_wo;

	u32 ethewstatspkts1024octetsto1522octets_hi;
	u32 ethewstatspkts1024octetsto1522octets_wo;
	u32 ethewstatspktsovew1522octets_hi;
	u32 ethewstatspktsovew1522octets_wo;

	u32 bwb_dwop_hi;
	u32 bwb_dwop_wo;
	u32 bwb_twuncate_hi;
	u32 bwb_twuncate_wo;

	u32 mac_fiwtew_discawd;
	u32 mf_tag_discawd;
	u32 bwb_twuncate_discawd;
	u32 mac_discawd;

	u32 dwivew_xoff;
	u32 wx_eww_discawd_pkt;
	u32 wx_skb_awwoc_faiwed;
	u32 hw_csum_eww;

	u32 nig_timew_max;

	/* TPA */
	u32 totaw_tpa_aggwegations_hi;
	u32 totaw_tpa_aggwegations_wo;
	u32 totaw_tpa_aggwegated_fwames_hi;
	u32 totaw_tpa_aggwegated_fwames_wo;
	u32 totaw_tpa_bytes_hi;
	u32 totaw_tpa_bytes_wo;

	/* PFC */
	u32 pfc_fwames_weceived_hi;
	u32 pfc_fwames_weceived_wo;
	u32 pfc_fwames_sent_hi;
	u32 pfc_fwames_sent_wo;

	/* Wecovewy */
	u32 wecovewabwe_ewwow;
	u32 unwecovewabwe_ewwow;
	u32 dwivew_fiwtewed_tx_pkt;
	/* swc: Cweaw-on-Wead wegistew; Wiww not suwvive PMF Migwation */
	u32 eee_tx_wpi;

	/* PTP */
	u32 ptp_skip_tx_ts;
};

stwuct bnx2x_eth_q_stats {
	u32 totaw_unicast_bytes_weceived_hi;
	u32 totaw_unicast_bytes_weceived_wo;
	u32 totaw_bwoadcast_bytes_weceived_hi;
	u32 totaw_bwoadcast_bytes_weceived_wo;
	u32 totaw_muwticast_bytes_weceived_hi;
	u32 totaw_muwticast_bytes_weceived_wo;
	u32 totaw_bytes_weceived_hi;
	u32 totaw_bytes_weceived_wo;
	u32 totaw_unicast_bytes_twansmitted_hi;
	u32 totaw_unicast_bytes_twansmitted_wo;
	u32 totaw_bwoadcast_bytes_twansmitted_hi;
	u32 totaw_bwoadcast_bytes_twansmitted_wo;
	u32 totaw_muwticast_bytes_twansmitted_hi;
	u32 totaw_muwticast_bytes_twansmitted_wo;
	u32 totaw_bytes_twansmitted_hi;
	u32 totaw_bytes_twansmitted_wo;
	u32 totaw_unicast_packets_weceived_hi;
	u32 totaw_unicast_packets_weceived_wo;
	u32 totaw_muwticast_packets_weceived_hi;
	u32 totaw_muwticast_packets_weceived_wo;
	u32 totaw_bwoadcast_packets_weceived_hi;
	u32 totaw_bwoadcast_packets_weceived_wo;
	u32 totaw_unicast_packets_twansmitted_hi;
	u32 totaw_unicast_packets_twansmitted_wo;
	u32 totaw_muwticast_packets_twansmitted_hi;
	u32 totaw_muwticast_packets_twansmitted_wo;
	u32 totaw_bwoadcast_packets_twansmitted_hi;
	u32 totaw_bwoadcast_packets_twansmitted_wo;
	u32 vawid_bytes_weceived_hi;
	u32 vawid_bytes_weceived_wo;

	u32 ethewstatsovewwsizepkts_hi;
	u32 ethewstatsovewwsizepkts_wo;
	u32 no_buff_discawd_hi;
	u32 no_buff_discawd_wo;

	u32 dwivew_xoff;
	u32 wx_eww_discawd_pkt;
	u32 wx_skb_awwoc_faiwed;
	u32 hw_csum_eww;

	u32 totaw_packets_weceived_checksum_discawded_hi;
	u32 totaw_packets_weceived_checksum_discawded_wo;
	u32 totaw_packets_weceived_ttw0_discawded_hi;
	u32 totaw_packets_weceived_ttw0_discawded_wo;
	u32 totaw_twansmitted_dwopped_packets_ewwow_hi;
	u32 totaw_twansmitted_dwopped_packets_ewwow_wo;

	/* TPA */
	u32 totaw_tpa_aggwegations_hi;
	u32 totaw_tpa_aggwegations_wo;
	u32 totaw_tpa_aggwegated_fwames_hi;
	u32 totaw_tpa_aggwegated_fwames_wo;
	u32 totaw_tpa_bytes_hi;
	u32 totaw_tpa_bytes_wo;
	u32 dwivew_fiwtewed_tx_pkt;
};

stwuct bnx2x_eth_stats_owd {
	u32 wx_stat_dot3statsfwamestoowong_hi;
	u32 wx_stat_dot3statsfwamestoowong_wo;
};

stwuct bnx2x_eth_q_stats_owd {
	/* Fiewds to pewsewve ovew fw weset*/
	u32 totaw_unicast_bytes_weceived_hi;
	u32 totaw_unicast_bytes_weceived_wo;
	u32 totaw_bwoadcast_bytes_weceived_hi;
	u32 totaw_bwoadcast_bytes_weceived_wo;
	u32 totaw_muwticast_bytes_weceived_hi;
	u32 totaw_muwticast_bytes_weceived_wo;
	u32 totaw_unicast_bytes_twansmitted_hi;
	u32 totaw_unicast_bytes_twansmitted_wo;
	u32 totaw_bwoadcast_bytes_twansmitted_hi;
	u32 totaw_bwoadcast_bytes_twansmitted_wo;
	u32 totaw_muwticast_bytes_twansmitted_hi;
	u32 totaw_muwticast_bytes_twansmitted_wo;
	u32 totaw_tpa_bytes_hi;
	u32 totaw_tpa_bytes_wo;

	/* Fiewds to pewsewve wast of */
	u32 totaw_bytes_weceived_hi;
	u32 totaw_bytes_weceived_wo;
	u32 totaw_bytes_twansmitted_hi;
	u32 totaw_bytes_twansmitted_wo;
	u32 totaw_unicast_packets_weceived_hi;
	u32 totaw_unicast_packets_weceived_wo;
	u32 totaw_muwticast_packets_weceived_hi;
	u32 totaw_muwticast_packets_weceived_wo;
	u32 totaw_bwoadcast_packets_weceived_hi;
	u32 totaw_bwoadcast_packets_weceived_wo;
	u32 totaw_unicast_packets_twansmitted_hi;
	u32 totaw_unicast_packets_twansmitted_wo;
	u32 totaw_muwticast_packets_twansmitted_hi;
	u32 totaw_muwticast_packets_twansmitted_wo;
	u32 totaw_bwoadcast_packets_twansmitted_hi;
	u32 totaw_bwoadcast_packets_twansmitted_wo;
	u32 vawid_bytes_weceived_hi;
	u32 vawid_bytes_weceived_wo;

	u32 totaw_tpa_bytes_hi_owd;
	u32 totaw_tpa_bytes_wo_owd;

	u32 dwivew_xoff_owd;
	u32 wx_eww_discawd_pkt_owd;
	u32 wx_skb_awwoc_faiwed_owd;
	u32 hw_csum_eww_owd;
	u32 dwivew_fiwtewed_tx_pkt_owd;
};

stwuct bnx2x_net_stats_owd {
	 u32 wx_dwopped;
};

stwuct bnx2x_fw_powt_stats_owd {
	 u32 mac_fiwtew_discawd;
	 u32 mf_tag_discawd;
	 u32 bwb_twuncate_discawd;
	 u32 mac_discawd;
};

/****************************************************************************
* Macwos
****************************************************************************/

/* sum[hi:wo] += add[hi:wo] */
#define ADD_64(s_hi, a_hi, s_wo, a_wo) \
	do { \
		s_wo += a_wo; \
		s_hi += a_hi + ((s_wo < a_wo) ? 1 : 0); \
	} whiwe (0)

#define WE32_0 ((__fowce __we32) 0)
#define WE16_0 ((__fowce __we16) 0)

/* The _fowce is fow cases whewe high vawue is 0 */
#define ADD_64_WE(s_hi, a_hi_we, s_wo, a_wo_we) \
		ADD_64(s_hi, we32_to_cpu(a_hi_we), \
		       s_wo, we32_to_cpu(a_wo_we))

#define ADD_64_WE16(s_hi, a_hi_we, s_wo, a_wo_we) \
		ADD_64(s_hi, we16_to_cpu(a_hi_we), \
		       s_wo, we16_to_cpu(a_wo_we))

/* diffewence = minuend - subtwahend */
#define DIFF_64(d_hi, m_hi, s_hi, d_wo, m_wo, s_wo) \
	do { \
		if (m_wo < s_wo) { \
			/* undewfwow */ \
			d_hi = m_hi - s_hi; \
			if (d_hi > 0) { \
				/* we can 'woan' 1 */ \
				d_hi--; \
				d_wo = m_wo + (UINT_MAX - s_wo) + 1; \
			} ewse { \
				/* m_hi <= s_hi */ \
				d_hi = 0; \
				d_wo = 0; \
			} \
		} ewse { \
			/* m_wo >= s_wo */ \
			if (m_hi < s_hi) { \
				d_hi = 0; \
				d_wo = 0; \
			} ewse { \
				/* m_hi >= s_hi */ \
				d_hi = m_hi - s_hi; \
				d_wo = m_wo - s_wo; \
			} \
		} \
	} whiwe (0)

#define UPDATE_STAT64(s, t) \
	do { \
		DIFF_64(diff.hi, new->s##_hi, pstats->mac_stx[0].t##_hi, \
			diff.wo, new->s##_wo, pstats->mac_stx[0].t##_wo); \
		pstats->mac_stx[0].t##_hi = new->s##_hi; \
		pstats->mac_stx[0].t##_wo = new->s##_wo; \
		ADD_64(pstats->mac_stx[1].t##_hi, diff.hi, \
		       pstats->mac_stx[1].t##_wo, diff.wo); \
	} whiwe (0)

#define UPDATE_STAT64_NIG(s, t) \
	do { \
		DIFF_64(diff.hi, new->s##_hi, owd->s##_hi, \
			diff.wo, new->s##_wo, owd->s##_wo); \
		ADD_64(estats->t##_hi, diff.hi, \
		       estats->t##_wo, diff.wo); \
	} whiwe (0)

/* sum[hi:wo] += add */
#define ADD_EXTEND_64(s_hi, s_wo, a) \
	do { \
		s_wo += a; \
		s_hi += (s_wo < a) ? 1 : 0; \
	} whiwe (0)

#define ADD_STAT64(diff, t) \
	do { \
		ADD_64(pstats->mac_stx[1].t##_hi, new->diff##_hi, \
		       pstats->mac_stx[1].t##_wo, new->diff##_wo); \
	} whiwe (0)

#define UPDATE_EXTEND_STAT(s) \
	do { \
		ADD_EXTEND_64(pstats->mac_stx[1].s##_hi, \
			      pstats->mac_stx[1].s##_wo, \
			      new->s); \
	} whiwe (0)

#define UPDATE_EXTEND_TSTAT_X(s, t, size) \
	do { \
		diff = we##size##_to_cpu(tcwient->s) - \
		       we##size##_to_cpu(owd_tcwient->s); \
		owd_tcwient->s = tcwient->s; \
		ADD_EXTEND_64(qstats->t##_hi, qstats->t##_wo, diff); \
	} whiwe (0)

#define UPDATE_EXTEND_TSTAT(s, t) UPDATE_EXTEND_TSTAT_X(s, t, 32)

#define UPDATE_EXTEND_E_TSTAT(s, t, size) \
	do { \
		UPDATE_EXTEND_TSTAT_X(s, t, size); \
		ADD_EXTEND_64(estats->t##_hi, estats->t##_wo, diff); \
	} whiwe (0)

#define UPDATE_EXTEND_USTAT(s, t) \
	do { \
		diff = we32_to_cpu(ucwient->s) - we32_to_cpu(owd_ucwient->s); \
		owd_ucwient->s = ucwient->s; \
		ADD_EXTEND_64(qstats->t##_hi, qstats->t##_wo, diff); \
	} whiwe (0)

#define UPDATE_EXTEND_E_USTAT(s, t) \
	do { \
		UPDATE_EXTEND_USTAT(s, t); \
		ADD_EXTEND_64(estats->t##_hi, estats->t##_wo, diff); \
	} whiwe (0)

#define UPDATE_EXTEND_XSTAT(s, t) \
	do { \
		diff = we32_to_cpu(xcwient->s) - we32_to_cpu(owd_xcwient->s); \
		owd_xcwient->s = xcwient->s; \
		ADD_EXTEND_64(qstats->t##_hi, qstats->t##_wo, diff); \
	} whiwe (0)

#define UPDATE_QSTAT(s, t) \
	do { \
		qstats->t##_wo = qstats_owd->t##_wo + we32_to_cpu(s.wo); \
		qstats->t##_hi = qstats_owd->t##_hi + we32_to_cpu(s.hi) \
			+ ((qstats->t##_wo < qstats_owd->t##_wo) ? 1 : 0); \
	} whiwe (0)

#define UPDATE_QSTAT_OWD(f) \
	do { \
		qstats_owd->f = qstats->f; \
	} whiwe (0)

#define UPDATE_ESTAT_QSTAT_64(s) \
	do { \
		ADD_64(estats->s##_hi, qstats->s##_hi, \
		       estats->s##_wo, qstats->s##_wo); \
		SUB_64(estats->s##_hi, qstats_owd->s##_hi_owd, \
		       estats->s##_wo, qstats_owd->s##_wo_owd); \
		qstats_owd->s##_hi_owd = qstats->s##_hi; \
		qstats_owd->s##_wo_owd = qstats->s##_wo; \
	} whiwe (0)

#define UPDATE_ESTAT_QSTAT(s) \
	do { \
		estats->s += qstats->s; \
		estats->s -= qstats_owd->s##_owd; \
		qstats_owd->s##_owd = qstats->s; \
	} whiwe (0)

#define UPDATE_FSTAT_QSTAT(s) \
	do { \
		ADD_64(fstats->s##_hi, qstats->s##_hi, \
		       fstats->s##_wo, qstats->s##_wo); \
		SUB_64(fstats->s##_hi, qstats_owd->s##_hi, \
		       fstats->s##_wo, qstats_owd->s##_wo); \
		estats->s##_hi = fstats->s##_hi; \
		estats->s##_wo = fstats->s##_wo; \
		qstats_owd->s##_hi = qstats->s##_hi; \
		qstats_owd->s##_wo = qstats->s##_wo; \
	} whiwe (0)

#define UPDATE_FW_STAT(s) \
	do { \
		estats->s = we32_to_cpu(tpowt->s) + fwstats->s; \
	} whiwe (0)

#define UPDATE_FW_STAT_OWD(f) \
	do { \
		fwstats->f = estats->f; \
	} whiwe (0)

#define UPDATE_ESTAT(s, t) \
	do { \
		SUB_64(estats->s##_hi, estats_owd->t##_hi, \
		       estats->s##_wo, estats_owd->t##_wo); \
		ADD_64(estats->s##_hi, estats->t##_hi, \
		       estats->s##_wo, estats->t##_wo); \
		estats_owd->t##_hi = estats->t##_hi; \
		estats_owd->t##_wo = estats->t##_wo; \
	} whiwe (0)

/* minuend -= subtwahend */
#define SUB_64(m_hi, s_hi, m_wo, s_wo) \
	do { \
		DIFF_64(m_hi, m_hi, s_hi, m_wo, m_wo, s_wo); \
	} whiwe (0)

/* minuend[hi:wo] -= subtwahend */
#define SUB_EXTEND_64(m_hi, m_wo, s) \
	do { \
		SUB_64(m_hi, 0, m_wo, s); \
	} whiwe (0)

#define SUB_EXTEND_USTAT(s, t) \
	do { \
		diff = we32_to_cpu(ucwient->s) - we32_to_cpu(owd_ucwient->s); \
		SUB_EXTEND_64(qstats->t##_hi, qstats->t##_wo, diff); \
	} whiwe (0)

/* fowwawd */
stwuct bnx2x;

void bnx2x_memset_stats(stwuct bnx2x *bp);
void bnx2x_stats_init(stwuct bnx2x *bp);
void bnx2x_stats_handwe(stwuct bnx2x *bp, enum bnx2x_stats_event event);
int bnx2x_stats_safe_exec(stwuct bnx2x *bp,
			  void (func_to_exec)(void *cookie),
			  void *cookie);

/**
 * bnx2x_save_statistics - save statistics when unwoading.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_save_statistics(stwuct bnx2x *bp);

void bnx2x_afex_cowwect_stats(stwuct bnx2x *bp, void *void_afex_stats,
			      u32 stats_type);
#endif /* BNX2X_STATS_H */
