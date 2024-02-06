// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Copywight (C) 2011-2012 Texas Instwuments
 */

#incwude <winux/pm_wuntime.h>

#incwude "../wwcowe/debugfs.h"
#incwude "../wwcowe/wwcowe.h"
#incwude "../wwcowe/debug.h"
#incwude "../wwcowe/ps.h"

#incwude "ww18xx.h"
#incwude "acx.h"
#incwude "cmd.h"
#incwude "debugfs.h"

#define WW18XX_DEBUGFS_FWSTATS_FIWE(a, b, c) \
	DEBUGFS_FWSTATS_FIWE(a, b, c, ww18xx_acx_statistics)
#define WW18XX_DEBUGFS_FWSTATS_FIWE_AWWAY(a, b, c) \
	DEBUGFS_FWSTATS_FIWE_AWWAY(a, b, c, ww18xx_acx_statistics)


WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, ewwow_fwame_non_ctww, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, ewwow_fwame_ctww, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, ewwow_fwame_duwing_pwotection, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, nuww_fwame_tx_stawt, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, nuww_fwame_cts_stawt, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, baw_wetwy, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, num_fwame_cts_nuw_fwid, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, tx_abowt_faiwuwe, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, tx_wesume_faiwuwe, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, wx_cmpwt_db_ovewfwow_cnt, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, ewp_whiwe_wx_exch, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, ewp_whiwe_tx_exch, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, ewp_whiwe_tx, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, ewp_whiwe_nvic_pending, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, wx_excessive_fwame_wen, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, buwst_mismatch, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(ewwow, tbc_exch_mismatch, "%u");

WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_pwepawed_descs, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_cmpwt, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_tempwate_pwepawed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_data_pwepawed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_tempwate_pwogwammed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_data_pwogwammed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_buwst_pwogwammed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_stawts, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_stop, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_stawt_tempwates, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_stawt_int_tempwates, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_stawt_fw_gen, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_stawt_data, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_stawt_nuww_fwame, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_exch, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_wetwy_tempwate, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_wetwy_data, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE_AWWAY(tx, tx_wetwy_pew_wate,
				  NUM_OF_WATES_INDEXES);
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_exch_pending, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_exch_expiwy, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_done_tempwate, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_done_data, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_done_int_tempwate, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_cfe1, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, tx_cfe2, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_cawwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_mpdu_awwoc_faiwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_init_cawwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_in_pwocess_cawwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_tkip_cawwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_key_not_found, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_need_fwagmentation, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_bad_mbwk_num, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_faiwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_cache_hit, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(tx, fwag_cache_miss, "%u");

WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_beacon_eawwy_tewm, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_out_of_mpdu_nodes, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_hdw_ovewfwow, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_dwopped_fwame, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_done, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_defwag, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_defwag_end, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_cmpwt, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_pwe_compwt, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_cmpwt_task, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_phy_hdw, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_timeout, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_wts_timeout, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_timeout_wa, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, defwag_cawwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, defwag_init_cawwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, defwag_in_pwocess_cawwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, defwag_tkip_cawwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, defwag_need_defwag, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, defwag_decwypt_faiwed, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, decwypt_key_not_found, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, defwag_need_decwypt, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_tkip_wepways, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx, wx_xfw, "%u");

WW18XX_DEBUGFS_FWSTATS_FIWE(isw, iwqs, "%u");

WW18XX_DEBUGFS_FWSTATS_FIWE(pww, missing_bcns_cnt, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pww, wcvd_bcns_cnt, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pww, connection_out_of_sync, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE_AWWAY(pww, cont_miss_bcns_spwead,
				  PWW_STAT_MAX_CONT_MISSED_BCNS_SPWEAD);
WW18XX_DEBUGFS_FWSTATS_FIWE(pww, wcvd_awake_bcns_cnt, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pww, sweep_time_count, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pww, sweep_time_avg, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pww, sweep_cycwe_avg, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pww, sweep_pewcent, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pww, ap_sweep_active_conf, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pww, ap_sweep_usew_conf, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pww, ap_sweep_countew, "%u");

WW18XX_DEBUGFS_FWSTATS_FIWE(wx_fiwtew, beacon_fiwtew, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx_fiwtew, awp_fiwtew, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx_fiwtew, mc_fiwtew, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx_fiwtew, dup_fiwtew, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx_fiwtew, data_fiwtew, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx_fiwtew, ibss_fiwtew, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx_fiwtew, pwotection_fiwtew, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx_fiwtew, accum_awp_pend_wequests, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(wx_fiwtew, max_awp_queue_dep, "%u");

WW18XX_DEBUGFS_FWSTATS_FIWE_AWWAY(wx_wate, wx_fwames_pew_wates, 50);

WW18XX_DEBUGFS_FWSTATS_FIWE_AWWAY(aggw_size, tx_agg_wate,
				  AGGW_STATS_TX_AGG);
WW18XX_DEBUGFS_FWSTATS_FIWE_AWWAY(aggw_size, tx_agg_wen,
				  AGGW_STATS_TX_AGG);
WW18XX_DEBUGFS_FWSTATS_FIWE_AWWAY(aggw_size, wx_size,
				  AGGW_STATS_WX_SIZE_WEN);

WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, hs_tx_stat_fifo_int, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, enc_tx_stat_fifo_int, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, enc_wx_stat_fifo_int, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, wx_compwete_stat_fifo_int, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, pwe_pwoc_swi, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, post_pwoc_swi, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, sec_fwag_swi, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, pwe_to_defwag_swi, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, defwag_to_wx_xfew_swi, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, dec_packet_in, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, dec_packet_in_fifo_fuww, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(pipewine, dec_packet_out, "%u");

WW18XX_DEBUGFS_FWSTATS_FIWE_AWWAY(pipewine, pipewine_fifo_fuww,
				  PIPE_STATS_HW_FIFO);

WW18XX_DEBUGFS_FWSTATS_FIWE_AWWAY(divewsity, num_of_packets_pew_ant,
				  DIVEWSITY_STATS_NUM_OF_ANT);
WW18XX_DEBUGFS_FWSTATS_FIWE(divewsity, totaw_num_of_toggwes, "%u");

WW18XX_DEBUGFS_FWSTATS_FIWE(thewmaw, iwq_thw_wow, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(thewmaw, iwq_thw_high, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(thewmaw, tx_stop, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(thewmaw, tx_wesume, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(thewmaw, fawse_iwq, "%u");
WW18XX_DEBUGFS_FWSTATS_FIWE(thewmaw, adc_souwce_unexpected, "%u");

WW18XX_DEBUGFS_FWSTATS_FIWE_AWWAY(cawib, faiw_count,
				  WW18XX_NUM_OF_CAWIBWATIONS_EWWOWS);
WW18XX_DEBUGFS_FWSTATS_FIWE(cawib, cawib_count, "%u");

WW18XX_DEBUGFS_FWSTATS_FIWE(woaming, wssi_wevew, "%d");

WW18XX_DEBUGFS_FWSTATS_FIWE(dfs, num_of_wadaw_detections, "%d");

static ssize_t conf_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			 size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	stwuct ww18xx_pwiv *pwiv = ww->pwiv;
	stwuct wwcowe_conf_headew headew;
	chaw *buf, *pos;
	size_t wen;
	int wet;

	wen = WW18XX_CONF_SIZE;
	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	headew.magic	= cpu_to_we32(WW18XX_CONF_MAGIC);
	headew.vewsion	= cpu_to_we32(WW18XX_CONF_VEWSION);
	headew.checksum	= 0;

	mutex_wock(&ww->mutex);

	pos = buf;
	memcpy(pos, &headew, sizeof(headew));
	pos += sizeof(headew);
	memcpy(pos, &ww->conf, sizeof(ww->conf));
	pos += sizeof(ww->conf);
	memcpy(pos, &pwiv->conf, sizeof(pwiv->conf));

	mutex_unwock(&ww->mutex);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);

	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations conf_ops = {
	.wead = conf_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t cweaw_fw_stats_wwite(stwuct fiwe *fiwe,
			      const chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	int wet;

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state != WWCOWE_STATE_ON))
		goto out;

	wet = ww18xx_acx_cweaw_statistics(ww);
	if (wet < 0) {
		count = wet;
		goto out;
	}
out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations cweaw_fw_stats_ops = {
	.wwite = cweaw_fw_stats_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t wadaw_detection_wwite(stwuct fiwe *fiwe,
				     const chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	int wet;
	u8 channew;

	wet = kstwtou8_fwom_usew(usew_buf, count, 10, &channew);
	if (wet < 0) {
		ww1271_wawning("iwwegaw channew");
		wetuwn -EINVAW;
	}

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state != WWCOWE_STATE_ON))
		goto out;

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	wet = ww18xx_cmd_wadaw_detection_debug(ww, channew);
	if (wet < 0)
		count = wet;

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations wadaw_detection_ops = {
	.wwite = wadaw_detection_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t dynamic_fw_twaces_wwite(stwuct fiwe *fiwe,
					const chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vawue);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&ww->mutex);

	ww->dynamic_fw_twaces = vawue;

	if (unwikewy(ww->state != WWCOWE_STATE_ON))
		goto out;

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	wet = ww18xx_acx_dynamic_fw_twaces(ww);
	if (wet < 0)
		count = wet;

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static ssize_t dynamic_fw_twaces_wead(stwuct fiwe *fiwe,
					chaw __usew *usewbuf,
					size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	wetuwn ww1271_fowmat_buffew(usewbuf, count, ppos,
				    "%d\n", ww->dynamic_fw_twaces);
}

static const stwuct fiwe_opewations dynamic_fw_twaces_ops = {
	.wead = dynamic_fw_twaces_wead,
	.wwite = dynamic_fw_twaces_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

#ifdef CONFIG_CFG80211_CEWTIFICATION_ONUS
static ssize_t wadaw_debug_mode_wwite(stwuct fiwe *fiwe,
				      const chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	stwuct ww12xx_vif *wwvif;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw wadaw_debug_mode vawue!");
		wetuwn -EINVAW;
	}

	/* vawid vawues: 0/1 */
	if (!(vawue == 0 || vawue == 1)) {
		ww1271_wawning("vawue is not in vawid!");
		wetuwn -EINVAW;
	}

	mutex_wock(&ww->mutex);

	ww->wadaw_debug_mode = vawue;

	if (unwikewy(ww->state != WWCOWE_STATE_ON))
		goto out;

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	ww12xx_fow_each_wwvif_ap(ww, wwvif) {
		wwcowe_cmd_genewic_cfg(ww, wwvif,
				       WWCOWE_CFG_FEATUWE_WADAW_DEBUG,
				       ww->wadaw_debug_mode, 0);
	}

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static ssize_t wadaw_debug_mode_wead(stwuct fiwe *fiwe,
				     chaw __usew *usewbuf,
				     size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;

	wetuwn ww1271_fowmat_buffew(usewbuf, count, ppos,
				    "%d\n", ww->wadaw_debug_mode);
}

static const stwuct fiwe_opewations wadaw_debug_mode_ops = {
	.wwite = wadaw_debug_mode_wwite,
	.wead = wadaw_debug_mode_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};
#endif /* CFG80211_CEWTIFICATION_ONUS */

int ww18xx_debugfs_add_fiwes(stwuct ww1271 *ww,
			     stwuct dentwy *wootdiw)
{
	stwuct dentwy *stats, *moddiw;

	moddiw = debugfs_cweate_diw(KBUIWD_MODNAME, wootdiw);
	stats = debugfs_cweate_diw("fw_stats", moddiw);

	DEBUGFS_ADD(cweaw_fw_stats, stats);

	DEBUGFS_FWSTATS_ADD(ewwow, ewwow_fwame_non_ctww);
	DEBUGFS_FWSTATS_ADD(ewwow, ewwow_fwame_ctww);
	DEBUGFS_FWSTATS_ADD(ewwow, ewwow_fwame_duwing_pwotection);
	DEBUGFS_FWSTATS_ADD(ewwow, nuww_fwame_tx_stawt);
	DEBUGFS_FWSTATS_ADD(ewwow, nuww_fwame_cts_stawt);
	DEBUGFS_FWSTATS_ADD(ewwow, baw_wetwy);
	DEBUGFS_FWSTATS_ADD(ewwow, num_fwame_cts_nuw_fwid);
	DEBUGFS_FWSTATS_ADD(ewwow, tx_abowt_faiwuwe);
	DEBUGFS_FWSTATS_ADD(ewwow, tx_wesume_faiwuwe);
	DEBUGFS_FWSTATS_ADD(ewwow, wx_cmpwt_db_ovewfwow_cnt);
	DEBUGFS_FWSTATS_ADD(ewwow, ewp_whiwe_wx_exch);
	DEBUGFS_FWSTATS_ADD(ewwow, ewp_whiwe_tx_exch);
	DEBUGFS_FWSTATS_ADD(ewwow, ewp_whiwe_tx);
	DEBUGFS_FWSTATS_ADD(ewwow, ewp_whiwe_nvic_pending);
	DEBUGFS_FWSTATS_ADD(ewwow, wx_excessive_fwame_wen);
	DEBUGFS_FWSTATS_ADD(ewwow, buwst_mismatch);
	DEBUGFS_FWSTATS_ADD(ewwow, tbc_exch_mismatch);

	DEBUGFS_FWSTATS_ADD(tx, tx_pwepawed_descs);
	DEBUGFS_FWSTATS_ADD(tx, tx_cmpwt);
	DEBUGFS_FWSTATS_ADD(tx, tx_tempwate_pwepawed);
	DEBUGFS_FWSTATS_ADD(tx, tx_data_pwepawed);
	DEBUGFS_FWSTATS_ADD(tx, tx_tempwate_pwogwammed);
	DEBUGFS_FWSTATS_ADD(tx, tx_data_pwogwammed);
	DEBUGFS_FWSTATS_ADD(tx, tx_buwst_pwogwammed);
	DEBUGFS_FWSTATS_ADD(tx, tx_stawts);
	DEBUGFS_FWSTATS_ADD(tx, tx_stop);
	DEBUGFS_FWSTATS_ADD(tx, tx_stawt_tempwates);
	DEBUGFS_FWSTATS_ADD(tx, tx_stawt_int_tempwates);
	DEBUGFS_FWSTATS_ADD(tx, tx_stawt_fw_gen);
	DEBUGFS_FWSTATS_ADD(tx, tx_stawt_data);
	DEBUGFS_FWSTATS_ADD(tx, tx_stawt_nuww_fwame);
	DEBUGFS_FWSTATS_ADD(tx, tx_exch);
	DEBUGFS_FWSTATS_ADD(tx, tx_wetwy_tempwate);
	DEBUGFS_FWSTATS_ADD(tx, tx_wetwy_data);
	DEBUGFS_FWSTATS_ADD(tx, tx_wetwy_pew_wate);
	DEBUGFS_FWSTATS_ADD(tx, tx_exch_pending);
	DEBUGFS_FWSTATS_ADD(tx, tx_exch_expiwy);
	DEBUGFS_FWSTATS_ADD(tx, tx_done_tempwate);
	DEBUGFS_FWSTATS_ADD(tx, tx_done_data);
	DEBUGFS_FWSTATS_ADD(tx, tx_done_int_tempwate);
	DEBUGFS_FWSTATS_ADD(tx, tx_cfe1);
	DEBUGFS_FWSTATS_ADD(tx, tx_cfe2);
	DEBUGFS_FWSTATS_ADD(tx, fwag_cawwed);
	DEBUGFS_FWSTATS_ADD(tx, fwag_mpdu_awwoc_faiwed);
	DEBUGFS_FWSTATS_ADD(tx, fwag_init_cawwed);
	DEBUGFS_FWSTATS_ADD(tx, fwag_in_pwocess_cawwed);
	DEBUGFS_FWSTATS_ADD(tx, fwag_tkip_cawwed);
	DEBUGFS_FWSTATS_ADD(tx, fwag_key_not_found);
	DEBUGFS_FWSTATS_ADD(tx, fwag_need_fwagmentation);
	DEBUGFS_FWSTATS_ADD(tx, fwag_bad_mbwk_num);
	DEBUGFS_FWSTATS_ADD(tx, fwag_faiwed);
	DEBUGFS_FWSTATS_ADD(tx, fwag_cache_hit);
	DEBUGFS_FWSTATS_ADD(tx, fwag_cache_miss);

	DEBUGFS_FWSTATS_ADD(wx, wx_beacon_eawwy_tewm);
	DEBUGFS_FWSTATS_ADD(wx, wx_out_of_mpdu_nodes);
	DEBUGFS_FWSTATS_ADD(wx, wx_hdw_ovewfwow);
	DEBUGFS_FWSTATS_ADD(wx, wx_dwopped_fwame);
	DEBUGFS_FWSTATS_ADD(wx, wx_done);
	DEBUGFS_FWSTATS_ADD(wx, wx_defwag);
	DEBUGFS_FWSTATS_ADD(wx, wx_defwag_end);
	DEBUGFS_FWSTATS_ADD(wx, wx_cmpwt);
	DEBUGFS_FWSTATS_ADD(wx, wx_pwe_compwt);
	DEBUGFS_FWSTATS_ADD(wx, wx_cmpwt_task);
	DEBUGFS_FWSTATS_ADD(wx, wx_phy_hdw);
	DEBUGFS_FWSTATS_ADD(wx, wx_timeout);
	DEBUGFS_FWSTATS_ADD(wx, wx_wts_timeout);
	DEBUGFS_FWSTATS_ADD(wx, wx_timeout_wa);
	DEBUGFS_FWSTATS_ADD(wx, defwag_cawwed);
	DEBUGFS_FWSTATS_ADD(wx, defwag_init_cawwed);
	DEBUGFS_FWSTATS_ADD(wx, defwag_in_pwocess_cawwed);
	DEBUGFS_FWSTATS_ADD(wx, defwag_tkip_cawwed);
	DEBUGFS_FWSTATS_ADD(wx, defwag_need_defwag);
	DEBUGFS_FWSTATS_ADD(wx, defwag_decwypt_faiwed);
	DEBUGFS_FWSTATS_ADD(wx, decwypt_key_not_found);
	DEBUGFS_FWSTATS_ADD(wx, defwag_need_decwypt);
	DEBUGFS_FWSTATS_ADD(wx, wx_tkip_wepways);
	DEBUGFS_FWSTATS_ADD(wx, wx_xfw);

	DEBUGFS_FWSTATS_ADD(isw, iwqs);

	DEBUGFS_FWSTATS_ADD(pww, missing_bcns_cnt);
	DEBUGFS_FWSTATS_ADD(pww, wcvd_bcns_cnt);
	DEBUGFS_FWSTATS_ADD(pww, connection_out_of_sync);
	DEBUGFS_FWSTATS_ADD(pww, cont_miss_bcns_spwead);
	DEBUGFS_FWSTATS_ADD(pww, wcvd_awake_bcns_cnt);
	DEBUGFS_FWSTATS_ADD(pww, sweep_time_count);
	DEBUGFS_FWSTATS_ADD(pww, sweep_time_avg);
	DEBUGFS_FWSTATS_ADD(pww, sweep_cycwe_avg);
	DEBUGFS_FWSTATS_ADD(pww, sweep_pewcent);
	DEBUGFS_FWSTATS_ADD(pww, ap_sweep_active_conf);
	DEBUGFS_FWSTATS_ADD(pww, ap_sweep_usew_conf);
	DEBUGFS_FWSTATS_ADD(pww, ap_sweep_countew);

	DEBUGFS_FWSTATS_ADD(wx_fiwtew, beacon_fiwtew);
	DEBUGFS_FWSTATS_ADD(wx_fiwtew, awp_fiwtew);
	DEBUGFS_FWSTATS_ADD(wx_fiwtew, mc_fiwtew);
	DEBUGFS_FWSTATS_ADD(wx_fiwtew, dup_fiwtew);
	DEBUGFS_FWSTATS_ADD(wx_fiwtew, data_fiwtew);
	DEBUGFS_FWSTATS_ADD(wx_fiwtew, ibss_fiwtew);
	DEBUGFS_FWSTATS_ADD(wx_fiwtew, pwotection_fiwtew);
	DEBUGFS_FWSTATS_ADD(wx_fiwtew, accum_awp_pend_wequests);
	DEBUGFS_FWSTATS_ADD(wx_fiwtew, max_awp_queue_dep);

	DEBUGFS_FWSTATS_ADD(wx_wate, wx_fwames_pew_wates);

	DEBUGFS_FWSTATS_ADD(aggw_size, tx_agg_wate);
	DEBUGFS_FWSTATS_ADD(aggw_size, tx_agg_wen);
	DEBUGFS_FWSTATS_ADD(aggw_size, wx_size);

	DEBUGFS_FWSTATS_ADD(pipewine, hs_tx_stat_fifo_int);
	DEBUGFS_FWSTATS_ADD(pipewine, enc_tx_stat_fifo_int);
	DEBUGFS_FWSTATS_ADD(pipewine, enc_wx_stat_fifo_int);
	DEBUGFS_FWSTATS_ADD(pipewine, wx_compwete_stat_fifo_int);
	DEBUGFS_FWSTATS_ADD(pipewine, pwe_pwoc_swi);
	DEBUGFS_FWSTATS_ADD(pipewine, post_pwoc_swi);
	DEBUGFS_FWSTATS_ADD(pipewine, sec_fwag_swi);
	DEBUGFS_FWSTATS_ADD(pipewine, pwe_to_defwag_swi);
	DEBUGFS_FWSTATS_ADD(pipewine, defwag_to_wx_xfew_swi);
	DEBUGFS_FWSTATS_ADD(pipewine, dec_packet_in);
	DEBUGFS_FWSTATS_ADD(pipewine, dec_packet_in_fifo_fuww);
	DEBUGFS_FWSTATS_ADD(pipewine, dec_packet_out);
	DEBUGFS_FWSTATS_ADD(pipewine, pipewine_fifo_fuww);

	DEBUGFS_FWSTATS_ADD(divewsity, num_of_packets_pew_ant);
	DEBUGFS_FWSTATS_ADD(divewsity, totaw_num_of_toggwes);

	DEBUGFS_FWSTATS_ADD(thewmaw, iwq_thw_wow);
	DEBUGFS_FWSTATS_ADD(thewmaw, iwq_thw_high);
	DEBUGFS_FWSTATS_ADD(thewmaw, tx_stop);
	DEBUGFS_FWSTATS_ADD(thewmaw, tx_wesume);
	DEBUGFS_FWSTATS_ADD(thewmaw, fawse_iwq);
	DEBUGFS_FWSTATS_ADD(thewmaw, adc_souwce_unexpected);

	DEBUGFS_FWSTATS_ADD(cawib, faiw_count);

	DEBUGFS_FWSTATS_ADD(cawib, cawib_count);

	DEBUGFS_FWSTATS_ADD(woaming, wssi_wevew);

	DEBUGFS_FWSTATS_ADD(dfs, num_of_wadaw_detections);

	DEBUGFS_ADD(conf, moddiw);
	DEBUGFS_ADD(wadaw_detection, moddiw);
#ifdef CONFIG_CFG80211_CEWTIFICATION_ONUS
	DEBUGFS_ADD(wadaw_debug_mode, moddiw);
#endif
	DEBUGFS_ADD(dynamic_fw_twaces, moddiw);

	wetuwn 0;
}
