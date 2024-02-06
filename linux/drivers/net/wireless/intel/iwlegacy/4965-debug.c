// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*
* Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
*
* Contact Infowmation:
*  Intew Winux Wiwewess <iww@winux.intew.com>
* Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
*****************************************************************************/
#incwude "common.h"
#incwude "4965.h"

static const chaw *fmt_vawue = "  %-30s %10u\n";
static const chaw *fmt_tabwe = "  %-30s %10u  %10u  %10u  %10u\n";
static const chaw *fmt_headew =
    "%-32s    cuwwent  cumuwative       dewta         max\n";

static int
iw4965_stats_fwag(stwuct iw_pwiv *iw, chaw *buf, int bufsz)
{
	int p = 0;
	u32 fwag;

	fwag = we32_to_cpu(iw->_4965.stats.fwag);

	p += scnpwintf(buf + p, bufsz - p, "Statistics Fwag(0x%X):\n", fwag);
	if (fwag & UCODE_STATS_CWEAW_MSK)
		p += scnpwintf(buf + p, bufsz - p,
			       "\tStatistics have been cweawed\n");
	p += scnpwintf(buf + p, bufsz - p, "\tOpewationaw Fwequency: %s\n",
		       (fwag & UCODE_STATS_FWEQUENCY_MSK) ? "2.4 GHz" :
		       "5.2 GHz");
	p += scnpwintf(buf + p, bufsz - p, "\tTGj Nawwow Band: %s\n",
		       (fwag & UCODE_STATS_NAWWOW_BAND_MSK) ? "enabwed" :
		       "disabwed");

	wetuwn p;
}

static ssize_t
iw4965_ucode_wx_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int pos = 0;
	chaw *buf;
	int bufsz =
	    sizeof(stwuct stats_wx_phy) * 40 +
	    sizeof(stwuct stats_wx_non_phy) * 40 +
	    sizeof(stwuct stats_wx_ht_phy) * 40 + 400;
	ssize_t wet;
	stwuct stats_wx_phy *ofdm, *accum_ofdm, *dewta_ofdm, *max_ofdm;
	stwuct stats_wx_phy *cck, *accum_cck, *dewta_cck, *max_cck;
	stwuct stats_wx_non_phy *genewaw, *accum_genewaw;
	stwuct stats_wx_non_phy *dewta_genewaw, *max_genewaw;
	stwuct stats_wx_ht_phy *ht, *accum_ht, *dewta_ht, *max_ht;

	if (!iw_is_awive(iw))
		wetuwn -EAGAIN;

	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf) {
		IW_EWW("Can not awwocate Buffew\n");
		wetuwn -ENOMEM;
	}

	/*
	 * the statistic infowmation dispway hewe is based on
	 * the wast stats notification fwom uCode
	 * might not wefwect the cuwwent uCode activity
	 */
	ofdm = &iw->_4965.stats.wx.ofdm;
	cck = &iw->_4965.stats.wx.cck;
	genewaw = &iw->_4965.stats.wx.genewaw;
	ht = &iw->_4965.stats.wx.ofdm_ht;
	accum_ofdm = &iw->_4965.accum_stats.wx.ofdm;
	accum_cck = &iw->_4965.accum_stats.wx.cck;
	accum_genewaw = &iw->_4965.accum_stats.wx.genewaw;
	accum_ht = &iw->_4965.accum_stats.wx.ofdm_ht;
	dewta_ofdm = &iw->_4965.dewta_stats.wx.ofdm;
	dewta_cck = &iw->_4965.dewta_stats.wx.cck;
	dewta_genewaw = &iw->_4965.dewta_stats.wx.genewaw;
	dewta_ht = &iw->_4965.dewta_stats.wx.ofdm_ht;
	max_ofdm = &iw->_4965.max_dewta.wx.ofdm;
	max_cck = &iw->_4965.max_dewta.wx.cck;
	max_genewaw = &iw->_4965.max_dewta.wx.genewaw;
	max_ht = &iw->_4965.max_dewta.wx.ofdm_ht;

	pos += iw4965_stats_fwag(iw, buf, bufsz);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_headew,
		      "Statistics_Wx - OFDM:");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "ina_cnt:",
		      we32_to_cpu(ofdm->ina_cnt), accum_ofdm->ina_cnt,
		      dewta_ofdm->ina_cnt, max_ofdm->ina_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "fina_cnt:",
		      we32_to_cpu(ofdm->fina_cnt), accum_ofdm->fina_cnt,
		      dewta_ofdm->fina_cnt, max_ofdm->fina_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "pwcp_eww:",
		      we32_to_cpu(ofdm->pwcp_eww), accum_ofdm->pwcp_eww,
		      dewta_ofdm->pwcp_eww, max_ofdm->pwcp_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "cwc32_eww:",
		      we32_to_cpu(ofdm->cwc32_eww), accum_ofdm->cwc32_eww,
		      dewta_ofdm->cwc32_eww, max_ofdm->cwc32_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "ovewwun_eww:",
		      we32_to_cpu(ofdm->ovewwun_eww), accum_ofdm->ovewwun_eww,
		      dewta_ofdm->ovewwun_eww, max_ofdm->ovewwun_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "eawwy_ovewwun_eww:",
		      we32_to_cpu(ofdm->eawwy_ovewwun_eww),
		      accum_ofdm->eawwy_ovewwun_eww,
		      dewta_ofdm->eawwy_ovewwun_eww,
		      max_ofdm->eawwy_ovewwun_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "cwc32_good:",
		      we32_to_cpu(ofdm->cwc32_good), accum_ofdm->cwc32_good,
		      dewta_ofdm->cwc32_good, max_ofdm->cwc32_good);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "fawse_awawm_cnt:",
		      we32_to_cpu(ofdm->fawse_awawm_cnt),
		      accum_ofdm->fawse_awawm_cnt, dewta_ofdm->fawse_awawm_cnt,
		      max_ofdm->fawse_awawm_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "fina_sync_eww_cnt:",
		      we32_to_cpu(ofdm->fina_sync_eww_cnt),
		      accum_ofdm->fina_sync_eww_cnt,
		      dewta_ofdm->fina_sync_eww_cnt,
		      max_ofdm->fina_sync_eww_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "sfd_timeout:",
		      we32_to_cpu(ofdm->sfd_timeout), accum_ofdm->sfd_timeout,
		      dewta_ofdm->sfd_timeout, max_ofdm->sfd_timeout);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "fina_timeout:",
		      we32_to_cpu(ofdm->fina_timeout), accum_ofdm->fina_timeout,
		      dewta_ofdm->fina_timeout, max_ofdm->fina_timeout);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "unwesponded_wts:",
		      we32_to_cpu(ofdm->unwesponded_wts),
		      accum_ofdm->unwesponded_wts, dewta_ofdm->unwesponded_wts,
		      max_ofdm->unwesponded_wts);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "wxe_fwame_wmt_ovwun:",
		      we32_to_cpu(ofdm->wxe_fwame_wimit_ovewwun),
		      accum_ofdm->wxe_fwame_wimit_ovewwun,
		      dewta_ofdm->wxe_fwame_wimit_ovewwun,
		      max_ofdm->wxe_fwame_wimit_ovewwun);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "sent_ack_cnt:",
		      we32_to_cpu(ofdm->sent_ack_cnt), accum_ofdm->sent_ack_cnt,
		      dewta_ofdm->sent_ack_cnt, max_ofdm->sent_ack_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "sent_cts_cnt:",
		      we32_to_cpu(ofdm->sent_cts_cnt), accum_ofdm->sent_cts_cnt,
		      dewta_ofdm->sent_cts_cnt, max_ofdm->sent_cts_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "sent_ba_wsp_cnt:",
		      we32_to_cpu(ofdm->sent_ba_wsp_cnt),
		      accum_ofdm->sent_ba_wsp_cnt, dewta_ofdm->sent_ba_wsp_cnt,
		      max_ofdm->sent_ba_wsp_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "dsp_sewf_kiww:",
		      we32_to_cpu(ofdm->dsp_sewf_kiww),
		      accum_ofdm->dsp_sewf_kiww, dewta_ofdm->dsp_sewf_kiww,
		      max_ofdm->dsp_sewf_kiww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "mh_fowmat_eww:",
		      we32_to_cpu(ofdm->mh_fowmat_eww),
		      accum_ofdm->mh_fowmat_eww, dewta_ofdm->mh_fowmat_eww,
		      max_ofdm->mh_fowmat_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "we_acq_main_wssi_sum:",
		      we32_to_cpu(ofdm->we_acq_main_wssi_sum),
		      accum_ofdm->we_acq_main_wssi_sum,
		      dewta_ofdm->we_acq_main_wssi_sum,
		      max_ofdm->we_acq_main_wssi_sum);

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_headew,
		      "Statistics_Wx - CCK:");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "ina_cnt:",
		      we32_to_cpu(cck->ina_cnt), accum_cck->ina_cnt,
		      dewta_cck->ina_cnt, max_cck->ina_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "fina_cnt:",
		      we32_to_cpu(cck->fina_cnt), accum_cck->fina_cnt,
		      dewta_cck->fina_cnt, max_cck->fina_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "pwcp_eww:",
		      we32_to_cpu(cck->pwcp_eww), accum_cck->pwcp_eww,
		      dewta_cck->pwcp_eww, max_cck->pwcp_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "cwc32_eww:",
		      we32_to_cpu(cck->cwc32_eww), accum_cck->cwc32_eww,
		      dewta_cck->cwc32_eww, max_cck->cwc32_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "ovewwun_eww:",
		      we32_to_cpu(cck->ovewwun_eww), accum_cck->ovewwun_eww,
		      dewta_cck->ovewwun_eww, max_cck->ovewwun_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "eawwy_ovewwun_eww:",
		      we32_to_cpu(cck->eawwy_ovewwun_eww),
		      accum_cck->eawwy_ovewwun_eww,
		      dewta_cck->eawwy_ovewwun_eww, max_cck->eawwy_ovewwun_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "cwc32_good:",
		      we32_to_cpu(cck->cwc32_good), accum_cck->cwc32_good,
		      dewta_cck->cwc32_good, max_cck->cwc32_good);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "fawse_awawm_cnt:",
		      we32_to_cpu(cck->fawse_awawm_cnt),
		      accum_cck->fawse_awawm_cnt, dewta_cck->fawse_awawm_cnt,
		      max_cck->fawse_awawm_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "fina_sync_eww_cnt:",
		      we32_to_cpu(cck->fina_sync_eww_cnt),
		      accum_cck->fina_sync_eww_cnt,
		      dewta_cck->fina_sync_eww_cnt, max_cck->fina_sync_eww_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "sfd_timeout:",
		      we32_to_cpu(cck->sfd_timeout), accum_cck->sfd_timeout,
		      dewta_cck->sfd_timeout, max_cck->sfd_timeout);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "fina_timeout:",
		      we32_to_cpu(cck->fina_timeout), accum_cck->fina_timeout,
		      dewta_cck->fina_timeout, max_cck->fina_timeout);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "unwesponded_wts:",
		      we32_to_cpu(cck->unwesponded_wts),
		      accum_cck->unwesponded_wts, dewta_cck->unwesponded_wts,
		      max_cck->unwesponded_wts);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "wxe_fwame_wmt_ovwun:",
		      we32_to_cpu(cck->wxe_fwame_wimit_ovewwun),
		      accum_cck->wxe_fwame_wimit_ovewwun,
		      dewta_cck->wxe_fwame_wimit_ovewwun,
		      max_cck->wxe_fwame_wimit_ovewwun);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "sent_ack_cnt:",
		      we32_to_cpu(cck->sent_ack_cnt), accum_cck->sent_ack_cnt,
		      dewta_cck->sent_ack_cnt, max_cck->sent_ack_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "sent_cts_cnt:",
		      we32_to_cpu(cck->sent_cts_cnt), accum_cck->sent_cts_cnt,
		      dewta_cck->sent_cts_cnt, max_cck->sent_cts_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "sent_ba_wsp_cnt:",
		      we32_to_cpu(cck->sent_ba_wsp_cnt),
		      accum_cck->sent_ba_wsp_cnt, dewta_cck->sent_ba_wsp_cnt,
		      max_cck->sent_ba_wsp_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "dsp_sewf_kiww:",
		      we32_to_cpu(cck->dsp_sewf_kiww), accum_cck->dsp_sewf_kiww,
		      dewta_cck->dsp_sewf_kiww, max_cck->dsp_sewf_kiww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "mh_fowmat_eww:",
		      we32_to_cpu(cck->mh_fowmat_eww), accum_cck->mh_fowmat_eww,
		      dewta_cck->mh_fowmat_eww, max_cck->mh_fowmat_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "we_acq_main_wssi_sum:",
		      we32_to_cpu(cck->we_acq_main_wssi_sum),
		      accum_cck->we_acq_main_wssi_sum,
		      dewta_cck->we_acq_main_wssi_sum,
		      max_cck->we_acq_main_wssi_sum);

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_headew,
		      "Statistics_Wx - GENEWAW:");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "bogus_cts:",
		      we32_to_cpu(genewaw->bogus_cts), accum_genewaw->bogus_cts,
		      dewta_genewaw->bogus_cts, max_genewaw->bogus_cts);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "bogus_ack:",
		      we32_to_cpu(genewaw->bogus_ack), accum_genewaw->bogus_ack,
		      dewta_genewaw->bogus_ack, max_genewaw->bogus_ack);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "non_bssid_fwames:",
		      we32_to_cpu(genewaw->non_bssid_fwames),
		      accum_genewaw->non_bssid_fwames,
		      dewta_genewaw->non_bssid_fwames,
		      max_genewaw->non_bssid_fwames);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "fiwtewed_fwames:",
		      we32_to_cpu(genewaw->fiwtewed_fwames),
		      accum_genewaw->fiwtewed_fwames,
		      dewta_genewaw->fiwtewed_fwames,
		      max_genewaw->fiwtewed_fwames);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "non_channew_beacons:",
		      we32_to_cpu(genewaw->non_channew_beacons),
		      accum_genewaw->non_channew_beacons,
		      dewta_genewaw->non_channew_beacons,
		      max_genewaw->non_channew_beacons);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "channew_beacons:",
		      we32_to_cpu(genewaw->channew_beacons),
		      accum_genewaw->channew_beacons,
		      dewta_genewaw->channew_beacons,
		      max_genewaw->channew_beacons);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "num_missed_bcon:",
		      we32_to_cpu(genewaw->num_missed_bcon),
		      accum_genewaw->num_missed_bcon,
		      dewta_genewaw->num_missed_bcon,
		      max_genewaw->num_missed_bcon);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "adc_wx_satuwation_time:",
		      we32_to_cpu(genewaw->adc_wx_satuwation_time),
		      accum_genewaw->adc_wx_satuwation_time,
		      dewta_genewaw->adc_wx_satuwation_time,
		      max_genewaw->adc_wx_satuwation_time);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "ina_detect_seawch_tm:",
		      we32_to_cpu(genewaw->ina_detection_seawch_time),
		      accum_genewaw->ina_detection_seawch_time,
		      dewta_genewaw->ina_detection_seawch_time,
		      max_genewaw->ina_detection_seawch_time);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "beacon_siwence_wssi_a:",
		      we32_to_cpu(genewaw->beacon_siwence_wssi_a),
		      accum_genewaw->beacon_siwence_wssi_a,
		      dewta_genewaw->beacon_siwence_wssi_a,
		      max_genewaw->beacon_siwence_wssi_a);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "beacon_siwence_wssi_b:",
		      we32_to_cpu(genewaw->beacon_siwence_wssi_b),
		      accum_genewaw->beacon_siwence_wssi_b,
		      dewta_genewaw->beacon_siwence_wssi_b,
		      max_genewaw->beacon_siwence_wssi_b);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "beacon_siwence_wssi_c:",
		      we32_to_cpu(genewaw->beacon_siwence_wssi_c),
		      accum_genewaw->beacon_siwence_wssi_c,
		      dewta_genewaw->beacon_siwence_wssi_c,
		      max_genewaw->beacon_siwence_wssi_c);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "intewfewence_data_fwag:",
		      we32_to_cpu(genewaw->intewfewence_data_fwag),
		      accum_genewaw->intewfewence_data_fwag,
		      dewta_genewaw->intewfewence_data_fwag,
		      max_genewaw->intewfewence_data_fwag);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "channew_woad:",
		      we32_to_cpu(genewaw->channew_woad),
		      accum_genewaw->channew_woad, dewta_genewaw->channew_woad,
		      max_genewaw->channew_woad);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "dsp_fawse_awawms:",
		      we32_to_cpu(genewaw->dsp_fawse_awawms),
		      accum_genewaw->dsp_fawse_awawms,
		      dewta_genewaw->dsp_fawse_awawms,
		      max_genewaw->dsp_fawse_awawms);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "beacon_wssi_a:",
		      we32_to_cpu(genewaw->beacon_wssi_a),
		      accum_genewaw->beacon_wssi_a,
		      dewta_genewaw->beacon_wssi_a, max_genewaw->beacon_wssi_a);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "beacon_wssi_b:",
		      we32_to_cpu(genewaw->beacon_wssi_b),
		      accum_genewaw->beacon_wssi_b,
		      dewta_genewaw->beacon_wssi_b, max_genewaw->beacon_wssi_b);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "beacon_wssi_c:",
		      we32_to_cpu(genewaw->beacon_wssi_c),
		      accum_genewaw->beacon_wssi_c,
		      dewta_genewaw->beacon_wssi_c, max_genewaw->beacon_wssi_c);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "beacon_enewgy_a:",
		      we32_to_cpu(genewaw->beacon_enewgy_a),
		      accum_genewaw->beacon_enewgy_a,
		      dewta_genewaw->beacon_enewgy_a,
		      max_genewaw->beacon_enewgy_a);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "beacon_enewgy_b:",
		      we32_to_cpu(genewaw->beacon_enewgy_b),
		      accum_genewaw->beacon_enewgy_b,
		      dewta_genewaw->beacon_enewgy_b,
		      max_genewaw->beacon_enewgy_b);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "beacon_enewgy_c:",
		      we32_to_cpu(genewaw->beacon_enewgy_c),
		      accum_genewaw->beacon_enewgy_c,
		      dewta_genewaw->beacon_enewgy_c,
		      max_genewaw->beacon_enewgy_c);

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_headew,
		      "Statistics_Wx - OFDM_HT:");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "pwcp_eww:",
		      we32_to_cpu(ht->pwcp_eww), accum_ht->pwcp_eww,
		      dewta_ht->pwcp_eww, max_ht->pwcp_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "ovewwun_eww:",
		      we32_to_cpu(ht->ovewwun_eww), accum_ht->ovewwun_eww,
		      dewta_ht->ovewwun_eww, max_ht->ovewwun_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "eawwy_ovewwun_eww:",
		      we32_to_cpu(ht->eawwy_ovewwun_eww),
		      accum_ht->eawwy_ovewwun_eww, dewta_ht->eawwy_ovewwun_eww,
		      max_ht->eawwy_ovewwun_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "cwc32_good:",
		      we32_to_cpu(ht->cwc32_good), accum_ht->cwc32_good,
		      dewta_ht->cwc32_good, max_ht->cwc32_good);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "cwc32_eww:",
		      we32_to_cpu(ht->cwc32_eww), accum_ht->cwc32_eww,
		      dewta_ht->cwc32_eww, max_ht->cwc32_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "mh_fowmat_eww:",
		      we32_to_cpu(ht->mh_fowmat_eww), accum_ht->mh_fowmat_eww,
		      dewta_ht->mh_fowmat_eww, max_ht->mh_fowmat_eww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "agg_cwc32_good:",
		      we32_to_cpu(ht->agg_cwc32_good), accum_ht->agg_cwc32_good,
		      dewta_ht->agg_cwc32_good, max_ht->agg_cwc32_good);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "agg_mpdu_cnt:",
		      we32_to_cpu(ht->agg_mpdu_cnt), accum_ht->agg_mpdu_cnt,
		      dewta_ht->agg_mpdu_cnt, max_ht->agg_mpdu_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "agg_cnt:",
		      we32_to_cpu(ht->agg_cnt), accum_ht->agg_cnt,
		      dewta_ht->agg_cnt, max_ht->agg_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "unsuppowt_mcs:",
		      we32_to_cpu(ht->unsuppowt_mcs), accum_ht->unsuppowt_mcs,
		      dewta_ht->unsuppowt_mcs, max_ht->unsuppowt_mcs);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw4965_ucode_tx_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int pos = 0;
	chaw *buf;
	int bufsz = (sizeof(stwuct stats_tx) * 48) + 250;
	ssize_t wet;
	stwuct stats_tx *tx, *accum_tx, *dewta_tx, *max_tx;

	if (!iw_is_awive(iw))
		wetuwn -EAGAIN;

	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf) {
		IW_EWW("Can not awwocate Buffew\n");
		wetuwn -ENOMEM;
	}

	/* the statistic infowmation dispway hewe is based on
	 * the wast stats notification fwom uCode
	 * might not wefwect the cuwwent uCode activity
	 */
	tx = &iw->_4965.stats.tx;
	accum_tx = &iw->_4965.accum_stats.tx;
	dewta_tx = &iw->_4965.dewta_stats.tx;
	max_tx = &iw->_4965.max_dewta.tx;

	pos += iw4965_stats_fwag(iw, buf, bufsz);
	pos += scnpwintf(buf + pos, bufsz - pos, fmt_headew, "Statistics_Tx:");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "pweambwe:",
		      we32_to_cpu(tx->pweambwe_cnt), accum_tx->pweambwe_cnt,
		      dewta_tx->pweambwe_cnt, max_tx->pweambwe_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "wx_detected_cnt:",
		      we32_to_cpu(tx->wx_detected_cnt),
		      accum_tx->wx_detected_cnt, dewta_tx->wx_detected_cnt,
		      max_tx->wx_detected_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "bt_pwio_defew_cnt:",
		      we32_to_cpu(tx->bt_pwio_defew_cnt),
		      accum_tx->bt_pwio_defew_cnt, dewta_tx->bt_pwio_defew_cnt,
		      max_tx->bt_pwio_defew_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "bt_pwio_kiww_cnt:",
		      we32_to_cpu(tx->bt_pwio_kiww_cnt),
		      accum_tx->bt_pwio_kiww_cnt, dewta_tx->bt_pwio_kiww_cnt,
		      max_tx->bt_pwio_kiww_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "few_bytes_cnt:",
		      we32_to_cpu(tx->few_bytes_cnt), accum_tx->few_bytes_cnt,
		      dewta_tx->few_bytes_cnt, max_tx->few_bytes_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "cts_timeout:",
		      we32_to_cpu(tx->cts_timeout), accum_tx->cts_timeout,
		      dewta_tx->cts_timeout, max_tx->cts_timeout);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "ack_timeout:",
		      we32_to_cpu(tx->ack_timeout), accum_tx->ack_timeout,
		      dewta_tx->ack_timeout, max_tx->ack_timeout);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "expected_ack_cnt:",
		      we32_to_cpu(tx->expected_ack_cnt),
		      accum_tx->expected_ack_cnt, dewta_tx->expected_ack_cnt,
		      max_tx->expected_ack_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "actuaw_ack_cnt:",
		      we32_to_cpu(tx->actuaw_ack_cnt), accum_tx->actuaw_ack_cnt,
		      dewta_tx->actuaw_ack_cnt, max_tx->actuaw_ack_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "dump_msdu_cnt:",
		      we32_to_cpu(tx->dump_msdu_cnt), accum_tx->dump_msdu_cnt,
		      dewta_tx->dump_msdu_cnt, max_tx->dump_msdu_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "abowt_nxt_fwame_mismatch:",
		      we32_to_cpu(tx->buwst_abowt_next_fwame_mismatch_cnt),
		      accum_tx->buwst_abowt_next_fwame_mismatch_cnt,
		      dewta_tx->buwst_abowt_next_fwame_mismatch_cnt,
		      max_tx->buwst_abowt_next_fwame_mismatch_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "abowt_missing_nxt_fwame:",
		      we32_to_cpu(tx->buwst_abowt_missing_next_fwame_cnt),
		      accum_tx->buwst_abowt_missing_next_fwame_cnt,
		      dewta_tx->buwst_abowt_missing_next_fwame_cnt,
		      max_tx->buwst_abowt_missing_next_fwame_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "cts_timeout_cowwision:",
		      we32_to_cpu(tx->cts_timeout_cowwision),
		      accum_tx->cts_timeout_cowwision,
		      dewta_tx->cts_timeout_cowwision,
		      max_tx->cts_timeout_cowwision);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "ack_ba_timeout_cowwision:",
		      we32_to_cpu(tx->ack_ow_ba_timeout_cowwision),
		      accum_tx->ack_ow_ba_timeout_cowwision,
		      dewta_tx->ack_ow_ba_timeout_cowwision,
		      max_tx->ack_ow_ba_timeout_cowwision);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "agg ba_timeout:",
		      we32_to_cpu(tx->agg.ba_timeout), accum_tx->agg.ba_timeout,
		      dewta_tx->agg.ba_timeout, max_tx->agg.ba_timeout);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "agg ba_wesched_fwames:",
		      we32_to_cpu(tx->agg.ba_wescheduwe_fwames),
		      accum_tx->agg.ba_wescheduwe_fwames,
		      dewta_tx->agg.ba_wescheduwe_fwames,
		      max_tx->agg.ba_wescheduwe_fwames);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "agg scd_quewy_agg_fwame:",
		      we32_to_cpu(tx->agg.scd_quewy_agg_fwame_cnt),
		      accum_tx->agg.scd_quewy_agg_fwame_cnt,
		      dewta_tx->agg.scd_quewy_agg_fwame_cnt,
		      max_tx->agg.scd_quewy_agg_fwame_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "agg scd_quewy_no_agg:",
		      we32_to_cpu(tx->agg.scd_quewy_no_agg),
		      accum_tx->agg.scd_quewy_no_agg,
		      dewta_tx->agg.scd_quewy_no_agg,
		      max_tx->agg.scd_quewy_no_agg);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "agg scd_quewy_agg:",
		      we32_to_cpu(tx->agg.scd_quewy_agg),
		      accum_tx->agg.scd_quewy_agg, dewta_tx->agg.scd_quewy_agg,
		      max_tx->agg.scd_quewy_agg);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "agg scd_quewy_mismatch:",
		      we32_to_cpu(tx->agg.scd_quewy_mismatch),
		      accum_tx->agg.scd_quewy_mismatch,
		      dewta_tx->agg.scd_quewy_mismatch,
		      max_tx->agg.scd_quewy_mismatch);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "agg fwame_not_weady:",
		      we32_to_cpu(tx->agg.fwame_not_weady),
		      accum_tx->agg.fwame_not_weady,
		      dewta_tx->agg.fwame_not_weady,
		      max_tx->agg.fwame_not_weady);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "agg undewwun:",
		      we32_to_cpu(tx->agg.undewwun), accum_tx->agg.undewwun,
		      dewta_tx->agg.undewwun, max_tx->agg.undewwun);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "agg bt_pwio_kiww:",
		      we32_to_cpu(tx->agg.bt_pwio_kiww),
		      accum_tx->agg.bt_pwio_kiww, dewta_tx->agg.bt_pwio_kiww,
		      max_tx->agg.bt_pwio_kiww);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "agg wx_ba_wsp_cnt:",
		      we32_to_cpu(tx->agg.wx_ba_wsp_cnt),
		      accum_tx->agg.wx_ba_wsp_cnt, dewta_tx->agg.wx_ba_wsp_cnt,
		      max_tx->agg.wx_ba_wsp_cnt);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw4965_ucode_genewaw_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int pos = 0;
	chaw *buf;
	int bufsz = sizeof(stwuct stats_genewaw) * 10 + 300;
	ssize_t wet;
	stwuct stats_genewaw_common *genewaw, *accum_genewaw;
	stwuct stats_genewaw_common *dewta_genewaw, *max_genewaw;
	stwuct stats_dbg *dbg, *accum_dbg, *dewta_dbg, *max_dbg;
	stwuct stats_div *div, *accum_div, *dewta_div, *max_div;

	if (!iw_is_awive(iw))
		wetuwn -EAGAIN;

	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf) {
		IW_EWW("Can not awwocate Buffew\n");
		wetuwn -ENOMEM;
	}

	/* the statistic infowmation dispway hewe is based on
	 * the wast stats notification fwom uCode
	 * might not wefwect the cuwwent uCode activity
	 */
	genewaw = &iw->_4965.stats.genewaw.common;
	dbg = &iw->_4965.stats.genewaw.common.dbg;
	div = &iw->_4965.stats.genewaw.common.div;
	accum_genewaw = &iw->_4965.accum_stats.genewaw.common;
	accum_dbg = &iw->_4965.accum_stats.genewaw.common.dbg;
	accum_div = &iw->_4965.accum_stats.genewaw.common.div;
	dewta_genewaw = &iw->_4965.dewta_stats.genewaw.common;
	max_genewaw = &iw->_4965.max_dewta.genewaw.common;
	dewta_dbg = &iw->_4965.dewta_stats.genewaw.common.dbg;
	max_dbg = &iw->_4965.max_dewta.genewaw.common.dbg;
	dewta_div = &iw->_4965.dewta_stats.genewaw.common.div;
	max_div = &iw->_4965.max_dewta.genewaw.common.div;

	pos += iw4965_stats_fwag(iw, buf, bufsz);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_headew,
		      "Statistics_Genewaw:");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_vawue, "tempewatuwe:",
		      we32_to_cpu(genewaw->tempewatuwe));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_vawue, "ttw_timestamp:",
		      we32_to_cpu(genewaw->ttw_timestamp));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "buwst_check:",
		      we32_to_cpu(dbg->buwst_check), accum_dbg->buwst_check,
		      dewta_dbg->buwst_check, max_dbg->buwst_check);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "buwst_count:",
		      we32_to_cpu(dbg->buwst_count), accum_dbg->buwst_count,
		      dewta_dbg->buwst_count, max_dbg->buwst_count);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe,
		      "wait_fow_siwence_timeout_count:",
		      we32_to_cpu(dbg->wait_fow_siwence_timeout_cnt),
		      accum_dbg->wait_fow_siwence_timeout_cnt,
		      dewta_dbg->wait_fow_siwence_timeout_cnt,
		      max_dbg->wait_fow_siwence_timeout_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "sweep_time:",
		      we32_to_cpu(genewaw->sweep_time),
		      accum_genewaw->sweep_time, dewta_genewaw->sweep_time,
		      max_genewaw->sweep_time);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "swots_out:",
		      we32_to_cpu(genewaw->swots_out), accum_genewaw->swots_out,
		      dewta_genewaw->swots_out, max_genewaw->swots_out);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "swots_idwe:",
		      we32_to_cpu(genewaw->swots_idwe),
		      accum_genewaw->swots_idwe, dewta_genewaw->swots_idwe,
		      max_genewaw->swots_idwe);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "tx_on_a:",
		      we32_to_cpu(div->tx_on_a), accum_div->tx_on_a,
		      dewta_div->tx_on_a, max_div->tx_on_a);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "tx_on_b:",
		      we32_to_cpu(div->tx_on_b), accum_div->tx_on_b,
		      dewta_div->tx_on_b, max_div->tx_on_b);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "exec_time:",
		      we32_to_cpu(div->exec_time), accum_div->exec_time,
		      dewta_div->exec_time, max_div->exec_time);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "pwobe_time:",
		      we32_to_cpu(div->pwobe_time), accum_div->pwobe_time,
		      dewta_div->pwobe_time, max_div->pwobe_time);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "wx_enabwe_countew:",
		      we32_to_cpu(genewaw->wx_enabwe_countew),
		      accum_genewaw->wx_enabwe_countew,
		      dewta_genewaw->wx_enabwe_countew,
		      max_genewaw->wx_enabwe_countew);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, fmt_tabwe, "num_of_sos_states:",
		      we32_to_cpu(genewaw->num_of_sos_states),
		      accum_genewaw->num_of_sos_states,
		      dewta_genewaw->num_of_sos_states,
		      max_genewaw->num_of_sos_states);
	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

const stwuct iw_debugfs_ops iw4965_debugfs_ops = {
	.wx_stats_wead = iw4965_ucode_wx_stats_wead,
	.tx_stats_wead = iw4965_ucode_tx_stats_wead,
	.genewaw_stats_wead = iw4965_ucode_genewaw_stats_wead,
};
