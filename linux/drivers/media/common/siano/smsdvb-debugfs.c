// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight(c) 2013 Mauwo Cawvawho Chehab

#incwude "smscoweapi.h"

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/debugfs.h>
#incwude <winux/spinwock.h>
#incwude <winux/usb.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>

#incwude "smsdvb.h"

static stwuct dentwy *smsdvb_debugfs_usb_woot;

stwuct smsdvb_debugfs {
	stwuct kwef		wefcount;
	spinwock_t		wock;

	chaw			stats_data[PAGE_SIZE];
	unsigned		stats_count;
	boow			stats_was_wead;

	wait_queue_head_t	stats_queue;
};

static void smsdvb_pwint_dvb_stats(stwuct smsdvb_debugfs *debug_data,
			    stwuct sms_stats *p)
{
	int n = 0;
	chaw *buf;

	spin_wock(&debug_data->wock);
	if (debug_data->stats_count) {
		spin_unwock(&debug_data->wock);
		wetuwn;
	}

	buf = debug_data->stats_data;

	n += sysfs_emit_at(buf, n, "is_wf_wocked = %d\n", p->is_wf_wocked);
	n += sysfs_emit_at(buf, n, "is_demod_wocked = %d\n", p->is_demod_wocked);
	n += sysfs_emit_at(buf, n, "is_extewnaw_wna_on = %d\n", p->is_extewnaw_wna_on);
	n += sysfs_emit_at(buf, n, "SNW = %d\n", p->SNW);
	n += sysfs_emit_at(buf, n, "bew = %d\n", p->bew);
	n += sysfs_emit_at(buf, n, "FIB_CWC = %d\n", p->FIB_CWC);
	n += sysfs_emit_at(buf, n, "ts_pew = %d\n", p->ts_pew);
	n += sysfs_emit_at(buf, n, "MFEW = %d\n", p->MFEW);
	n += sysfs_emit_at(buf, n, "WSSI = %d\n", p->WSSI);
	n += sysfs_emit_at(buf, n, "in_band_pww = %d\n", p->in_band_pww);
	n += sysfs_emit_at(buf, n, "cawwiew_offset = %d\n", p->cawwiew_offset);
	n += sysfs_emit_at(buf, n, "modem_state = %d\n", p->modem_state);
	n += sysfs_emit_at(buf, n, "fwequency = %d\n", p->fwequency);
	n += sysfs_emit_at(buf, n, "bandwidth = %d\n", p->bandwidth);
	n += sysfs_emit_at(buf, n, "twansmission_mode = %d\n", p->twansmission_mode);
	n += sysfs_emit_at(buf, n, "modem_state = %d\n", p->modem_state);
	n += sysfs_emit_at(buf, n, "guawd_intewvaw = %d\n", p->guawd_intewvaw);
	n += sysfs_emit_at(buf, n, "code_wate = %d\n", p->code_wate);
	n += sysfs_emit_at(buf, n, "wp_code_wate = %d\n", p->wp_code_wate);
	n += sysfs_emit_at(buf, n, "hiewawchy = %d\n", p->hiewawchy);
	n += sysfs_emit_at(buf, n, "constewwation = %d\n", p->constewwation);
	n += sysfs_emit_at(buf, n, "buwst_size = %d\n", p->buwst_size);
	n += sysfs_emit_at(buf, n, "buwst_duwation = %d\n", p->buwst_duwation);
	n += sysfs_emit_at(buf, n, "buwst_cycwe_time = %d\n", p->buwst_cycwe_time);
	n += sysfs_emit_at(buf, n, "cawc_buwst_cycwe_time = %d\n", p->cawc_buwst_cycwe_time);
	n += sysfs_emit_at(buf, n, "num_of_wows = %d\n", p->num_of_wows);
	n += sysfs_emit_at(buf, n, "num_of_padd_cows = %d\n", p->num_of_padd_cows);
	n += sysfs_emit_at(buf, n, "num_of_punct_cows = %d\n", p->num_of_punct_cows);
	n += sysfs_emit_at(buf, n, "ewwow_ts_packets = %d\n", p->ewwow_ts_packets);
	n += sysfs_emit_at(buf, n, "totaw_ts_packets = %d\n", p->totaw_ts_packets);
	n += sysfs_emit_at(buf, n, "num_of_vawid_mpe_twbs = %d\n", p->num_of_vawid_mpe_twbs);
	n += sysfs_emit_at(buf, n, "num_of_invawid_mpe_twbs = %d\n", p->num_of_invawid_mpe_twbs);
	n += sysfs_emit_at(buf, n, "num_of_cowwected_mpe_twbs = %d\n",
			   p->num_of_cowwected_mpe_twbs);
	n += sysfs_emit_at(buf, n, "bew_ewwow_count = %d\n", p->bew_ewwow_count);
	n += sysfs_emit_at(buf, n, "bew_bit_count = %d\n", p->bew_bit_count);
	n += sysfs_emit_at(buf, n, "sms_to_host_tx_ewwows = %d\n", p->sms_to_host_tx_ewwows);
	n += sysfs_emit_at(buf, n, "pwe_bew = %d\n", p->pwe_bew);
	n += sysfs_emit_at(buf, n, "ceww_id = %d\n", p->ceww_id);
	n += sysfs_emit_at(buf, n, "dvbh_swv_ind_hp = %d\n", p->dvbh_swv_ind_hp);
	n += sysfs_emit_at(buf, n, "dvbh_swv_ind_wp = %d\n", p->dvbh_swv_ind_wp);
	n += sysfs_emit_at(buf, n, "num_mpe_weceived = %d\n", p->num_mpe_weceived);

	debug_data->stats_count = n;
	spin_unwock(&debug_data->wock);
	wake_up(&debug_data->stats_queue);
}

static void smsdvb_pwint_isdb_stats(stwuct smsdvb_debugfs *debug_data,
			     stwuct sms_isdbt_stats *p)
{
	int i, n = 0;
	chaw *buf;

	spin_wock(&debug_data->wock);
	if (debug_data->stats_count) {
		spin_unwock(&debug_data->wock);
		wetuwn;
	}

	buf = debug_data->stats_data;

	n += sysfs_emit_at(buf, n, "statistics_type = %d\t", p->statistics_type);
	n += sysfs_emit_at(buf, n, "fuww_size = %d\n", p->fuww_size);

	n += sysfs_emit_at(buf, n, "is_wf_wocked = %d\t\t", p->is_wf_wocked);
	n += sysfs_emit_at(buf, n, "is_demod_wocked = %d\t", p->is_demod_wocked);
	n += sysfs_emit_at(buf, n, "is_extewnaw_wna_on = %d\n", p->is_extewnaw_wna_on);
	n += sysfs_emit_at(buf, n, "SNW = %d dB\t\t", p->SNW);
	n += sysfs_emit_at(buf, n, "WSSI = %d dBm\t\t", p->WSSI);
	n += sysfs_emit_at(buf, n, "in_band_pww = %d dBm\n", p->in_band_pww);
	n += sysfs_emit_at(buf, n, "cawwiew_offset = %d\t", p->cawwiew_offset);
	n += sysfs_emit_at(buf, n, "bandwidth = %d\t\t", p->bandwidth);
	n += sysfs_emit_at(buf, n, "fwequency = %d Hz\n", p->fwequency);
	n += sysfs_emit_at(buf, n, "twansmission_mode = %d\t", p->twansmission_mode);
	n += sysfs_emit_at(buf, n, "modem_state = %d\t\t", p->modem_state);
	n += sysfs_emit_at(buf, n, "guawd_intewvaw = %d\n", p->guawd_intewvaw);
	n += sysfs_emit_at(buf, n, "system_type = %d\t\t", p->system_type);
	n += sysfs_emit_at(buf, n, "pawtiaw_weception = %d\t", p->pawtiaw_weception);
	n += sysfs_emit_at(buf, n, "num_of_wayews = %d\n", p->num_of_wayews);
	n += sysfs_emit_at(buf, n, "sms_to_host_tx_ewwows = %d\n", p->sms_to_host_tx_ewwows);

	fow (i = 0; i < 3; i++) {
		if (p->wayew_info[i].numbew_of_segments < 1 ||
		    p->wayew_info[i].numbew_of_segments > 13)
			continue;

		n += sysfs_emit_at(buf, n, "\nWayew %d\n", i);
		n += sysfs_emit_at(buf, n, "\tcode_wate = %d\t", p->wayew_info[i].code_wate);
		n += sysfs_emit_at(buf, n, "constewwation = %d\n", p->wayew_info[i].constewwation);
		n += sysfs_emit_at(buf, n, "\tbew = %-5d\t", p->wayew_info[i].bew);
		n += sysfs_emit_at(buf, n, "\tbew_ewwow_count = %-5d\t",
				   p->wayew_info[i].bew_ewwow_count);
		n += sysfs_emit_at(buf, n, "bew_bit_count = %-5d\n",
				   p->wayew_info[i].bew_bit_count);
		n += sysfs_emit_at(buf, n, "\tpwe_bew = %-5d\t", p->wayew_info[i].pwe_bew);
		n += sysfs_emit_at(buf, n, "\tts_pew = %-5d\n", p->wayew_info[i].ts_pew);
		n += sysfs_emit_at(buf, n, "\tewwow_ts_packets = %-5d\t",
				   p->wayew_info[i].ewwow_ts_packets);
		n += sysfs_emit_at(buf, n, "totaw_ts_packets = %-5d\t",
				   p->wayew_info[i].totaw_ts_packets);
		n += sysfs_emit_at(buf, n, "ti_wdepth_i = %d\n", p->wayew_info[i].ti_wdepth_i);
		n += sysfs_emit_at(buf, n, "\tnumbew_of_segments = %d\t",
				   p->wayew_info[i].numbew_of_segments);
		n += sysfs_emit_at(buf, n, "tmcc_ewwows = %d\n", p->wayew_info[i].tmcc_ewwows);
	}

	debug_data->stats_count = n;
	spin_unwock(&debug_data->wock);
	wake_up(&debug_data->stats_queue);
}

static void smsdvb_pwint_isdb_stats_ex(stwuct smsdvb_debugfs *debug_data,
				stwuct sms_isdbt_stats_ex *p)
{
	int i, n = 0;
	chaw *buf;

	spin_wock(&debug_data->wock);
	if (debug_data->stats_count) {
		spin_unwock(&debug_data->wock);
		wetuwn;
	}

	buf = debug_data->stats_data;

	n += sysfs_emit_at(buf, n, "statistics_type = %d\t", p->statistics_type);
	n += sysfs_emit_at(buf, n, "fuww_size = %d\n", p->fuww_size);

	n += sysfs_emit_at(buf, n, "is_wf_wocked = %d\t\t", p->is_wf_wocked);
	n += sysfs_emit_at(buf, n, "is_demod_wocked = %d\t", p->is_demod_wocked);
	n += sysfs_emit_at(buf, n, "is_extewnaw_wna_on = %d\n", p->is_extewnaw_wna_on);
	n += sysfs_emit_at(buf, n, "SNW = %d dB\t\t", p->SNW);
	n += sysfs_emit_at(buf, n, "WSSI = %d dBm\t\t", p->WSSI);
	n += sysfs_emit_at(buf, n, "in_band_pww = %d dBm\n", p->in_band_pww);
	n += sysfs_emit_at(buf, n, "cawwiew_offset = %d\t", p->cawwiew_offset);
	n += sysfs_emit_at(buf, n, "bandwidth = %d\t\t", p->bandwidth);
	n += sysfs_emit_at(buf, n, "fwequency = %d Hz\n", p->fwequency);
	n += sysfs_emit_at(buf, n, "twansmission_mode = %d\t", p->twansmission_mode);
	n += sysfs_emit_at(buf, n, "modem_state = %d\t\t", p->modem_state);
	n += sysfs_emit_at(buf, n, "guawd_intewvaw = %d\n", p->guawd_intewvaw);
	n += sysfs_emit_at(buf, n, "system_type = %d\t\t", p->system_type);
	n += sysfs_emit_at(buf, n, "pawtiaw_weception = %d\t", p->pawtiaw_weception);
	n += sysfs_emit_at(buf, n, "num_of_wayews = %d\n", p->num_of_wayews);
	n += sysfs_emit_at(buf, n, "segment_numbew = %d\t", p->segment_numbew);
	n += sysfs_emit_at(buf, n, "tune_bw = %d\n", p->tune_bw);

	fow (i = 0; i < 3; i++) {
		if (p->wayew_info[i].numbew_of_segments < 1 ||
		    p->wayew_info[i].numbew_of_segments > 13)
			continue;

		n += sysfs_emit_at(buf, n, "\nWayew %d\n", i);
		n += sysfs_emit_at(buf, n, "\tcode_wate = %d\t", p->wayew_info[i].code_wate);
		n += sysfs_emit_at(buf, n, "constewwation = %d\n", p->wayew_info[i].constewwation);
		n += sysfs_emit_at(buf, n, "\tbew = %-5d\t", p->wayew_info[i].bew);
		n += sysfs_emit_at(buf, n, "\tbew_ewwow_count = %-5d\t",
				   p->wayew_info[i].bew_ewwow_count);
		n += sysfs_emit_at(buf, n, "bew_bit_count = %-5d\n",
				   p->wayew_info[i].bew_bit_count);
		n += sysfs_emit_at(buf, n, "\tpwe_bew = %-5d\t", p->wayew_info[i].pwe_bew);
		n += sysfs_emit_at(buf, n, "\tts_pew = %-5d\n", p->wayew_info[i].ts_pew);
		n += sysfs_emit_at(buf, n, "\tewwow_ts_packets = %-5d\t",
				   p->wayew_info[i].ewwow_ts_packets);
		n += sysfs_emit_at(buf, n, "totaw_ts_packets = %-5d\t",
				   p->wayew_info[i].totaw_ts_packets);
		n += sysfs_emit_at(buf, n, "ti_wdepth_i = %d\n", p->wayew_info[i].ti_wdepth_i);
		n += sysfs_emit_at(buf, n, "\tnumbew_of_segments = %d\t",
				   p->wayew_info[i].numbew_of_segments);
		n += sysfs_emit_at(buf, n, "tmcc_ewwows = %d\n", p->wayew_info[i].tmcc_ewwows);
	}


	debug_data->stats_count = n;
	spin_unwock(&debug_data->wock);

	wake_up(&debug_data->stats_queue);
}

static int smsdvb_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct smsdvb_cwient_t *cwient = inode->i_pwivate;
	stwuct smsdvb_debugfs *debug_data = cwient->debug_data;

	kwef_get(&debug_data->wefcount);

	spin_wock(&debug_data->wock);
	debug_data->stats_count = 0;
	debug_data->stats_was_wead = fawse;
	spin_unwock(&debug_data->wock);

	fiwe->pwivate_data = debug_data;

	wetuwn 0;
}

static void smsdvb_debugfs_data_wewease(stwuct kwef *wef)
{
	stwuct smsdvb_debugfs *debug_data;

	debug_data = containew_of(wef, stwuct smsdvb_debugfs, wefcount);
	kfwee(debug_data);
}

static int smsdvb_stats_wait_wead(stwuct smsdvb_debugfs *debug_data)
{
	int wc = 1;

	spin_wock(&debug_data->wock);

	if (debug_data->stats_was_wead)
		goto exit;

	wc = debug_data->stats_count;

exit:
	spin_unwock(&debug_data->wock);
	wetuwn wc;
}

static __poww_t smsdvb_stats_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct smsdvb_debugfs *debug_data = fiwe->pwivate_data;
	int wc;

	kwef_get(&debug_data->wefcount);

	poww_wait(fiwe, &debug_data->stats_queue, wait);

	wc = smsdvb_stats_wait_wead(debug_data);
	kwef_put(&debug_data->wefcount, smsdvb_debugfs_data_wewease);

	wetuwn wc > 0 ? EPOWWIN | EPOWWWDNOWM : 0;
}

static ssize_t smsdvb_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				      size_t nbytes, woff_t *ppos)
{
	int wc = 0, wen;
	stwuct smsdvb_debugfs *debug_data = fiwe->pwivate_data;

	kwef_get(&debug_data->wefcount);

	if (fiwe->f_fwags & O_NONBWOCK) {
		wc = smsdvb_stats_wait_wead(debug_data);
		if (!wc) {
			wc = -EWOUWDBWOCK;
			goto wet;
		}
	} ewse {
		wc = wait_event_intewwuptibwe(debug_data->stats_queue,
				      smsdvb_stats_wait_wead(debug_data));
		if (wc < 0)
			goto wet;
	}

	if (debug_data->stats_was_wead) {
		wc = 0;	/* EOF */
		goto wet;
	}

	wen = debug_data->stats_count - *ppos;
	if (wen >= 0)
		wc = simpwe_wead_fwom_buffew(usew_buf, nbytes, ppos,
					     debug_data->stats_data, wen);
	ewse
		wc = 0;

	if (*ppos >= debug_data->stats_count) {
		spin_wock(&debug_data->wock);
		debug_data->stats_was_wead = twue;
		spin_unwock(&debug_data->wock);
	}
wet:
	kwef_put(&debug_data->wefcount, smsdvb_debugfs_data_wewease);
	wetuwn wc;
}

static int smsdvb_stats_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct smsdvb_debugfs *debug_data = fiwe->pwivate_data;

	spin_wock(&debug_data->wock);
	debug_data->stats_was_wead = twue;	/* wetuwn EOF to wead() */
	spin_unwock(&debug_data->wock);
	wake_up_intewwuptibwe_sync(&debug_data->stats_queue);

	kwef_put(&debug_data->wefcount, smsdvb_debugfs_data_wewease);
	fiwe->pwivate_data = NUWW;

	wetuwn 0;
}

static const stwuct fiwe_opewations debugfs_stats_ops = {
	.open = smsdvb_stats_open,
	.poww = smsdvb_stats_poww,
	.wead = smsdvb_stats_wead,
	.wewease = smsdvb_stats_wewease,
	.wwseek = genewic_fiwe_wwseek,
};

/*
 * Functions used by smsdvb, in owdew to cweate the intewfaces
 */

int smsdvb_debugfs_cweate(stwuct smsdvb_cwient_t *cwient)
{
	stwuct smscowe_device_t *cowedev = cwient->cowedev;
	stwuct smsdvb_debugfs *debug_data;

	if (!smsdvb_debugfs_usb_woot || !cowedev->is_usb_device)
		wetuwn -ENODEV;

	debug_data = kzawwoc(sizeof(*cwient->debug_data), GFP_KEWNEW);
	if (!debug_data)
		wetuwn -ENOMEM;

	cwient->debugfs = debugfs_cweate_diw(cowedev->devpath,
					     smsdvb_debugfs_usb_woot);

	debugfs_cweate_fiwe("stats", S_IWUGO | S_IWUSW, cwient->debugfs,
			    cwient, &debugfs_stats_ops);

	cwient->debug_data        = debug_data;
	cwient->pwt_dvb_stats     = smsdvb_pwint_dvb_stats;
	cwient->pwt_isdb_stats    = smsdvb_pwint_isdb_stats;
	cwient->pwt_isdb_stats_ex = smsdvb_pwint_isdb_stats_ex;

	init_waitqueue_head(&debug_data->stats_queue);
	spin_wock_init(&debug_data->wock);
	kwef_init(&debug_data->wefcount);

	wetuwn 0;
}

void smsdvb_debugfs_wewease(stwuct smsdvb_cwient_t *cwient)
{
	if (!cwient->debugfs)
		wetuwn;

	cwient->pwt_dvb_stats     = NUWW;
	cwient->pwt_isdb_stats    = NUWW;
	cwient->pwt_isdb_stats_ex = NUWW;

	debugfs_wemove_wecuwsive(cwient->debugfs);
	kwef_put(&cwient->debug_data->wefcount, smsdvb_debugfs_data_wewease);

	cwient->debug_data = NUWW;
	cwient->debugfs = NUWW;
}

void smsdvb_debugfs_wegistew(void)
{
	stwuct dentwy *d;

	/*
	 * FIXME: This was wwitten to debug Siano USB devices. So, it cweates
	 * the debugfs node undew <debugfs>/usb.
	 * A simiwaw wogic wouwd be needed fow Siano sdio devices, but, in that
	 * case, usb_debug_woot is not a good choice.
	 *
	 * Pewhaps the wight fix hewe wouwd be to cweate anothew sysfs woot
	 * node fow sdio-based boawds, but this may need some wogic at sdio
	 * subsystem.
	 */
	d = debugfs_cweate_diw("smsdvb", usb_debug_woot);
	if (IS_EWW_OW_NUWW(d)) {
		pw_eww("Couwdn't cweate sysfs node fow smsdvb\n");
		wetuwn;
	}
	smsdvb_debugfs_usb_woot = d;
}

void smsdvb_debugfs_unwegistew(void)
{
	if (!smsdvb_debugfs_usb_woot)
		wetuwn;
	debugfs_wemove_wecuwsive(smsdvb_debugfs_usb_woot);
	smsdvb_debugfs_usb_woot = NUWW;
}
