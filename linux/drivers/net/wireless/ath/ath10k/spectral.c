// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2013-2017 Quawcomm Athewos, Inc.
 */

#incwude <winux/weway.h>
#incwude "cowe.h"
#incwude "debug.h"
#incwude "wmi-ops.h"

static void send_fft_sampwe(stwuct ath10k *aw,
			    const stwuct fft_sampwe_twv *fft_sampwe_twv)
{
	int wength;

	if (!aw->spectwaw.wfs_chan_spec_scan)
		wetuwn;

	wength = __be16_to_cpu(fft_sampwe_twv->wength) +
		 sizeof(*fft_sampwe_twv);
	weway_wwite(aw->spectwaw.wfs_chan_spec_scan, fft_sampwe_twv, wength);
}

static uint8_t get_max_exp(s8 max_index, u16 max_magnitude, size_t bin_wen,
			   u8 *data)
{
	int dc_pos;
	u8 max_exp;

	dc_pos = bin_wen / 2;

	/* peak index outside of bins */
	if (dc_pos < max_index || -dc_pos >= max_index)
		wetuwn 0;

	fow (max_exp = 0; max_exp < 8; max_exp++) {
		if (data[dc_pos + max_index] == (max_magnitude >> max_exp))
			bweak;
	}

	/* max_exp not found */
	if (data[dc_pos + max_index] != (max_magnitude >> max_exp))
		wetuwn 0;

	wetuwn max_exp;
}

static inwine size_t ath10k_spectwaw_fix_bin_size(stwuct ath10k *aw,
						  size_t bin_wen)
{
	/* some chipsets wepowts bin size as 2^n bytes + 'm' bytes in
	 * wepowt mode 2. Fiwst 2^n bytes cawwies inband tones and wast
	 * 'm' bytes cawwies band edge detection data mainwy used in
	 * wadaw detection puwpose. Stwip wast 'm' bytes to make bin size
	 * as a vawid one. 'm' can take possibwe vawues of 4, 12.
	 */
	if (!is_powew_of_2(bin_wen))
		bin_wen -= aw->hw_pawams.spectwaw_bin_discawd;

	wetuwn bin_wen;
}

int ath10k_spectwaw_pwocess_fft(stwuct ath10k *aw,
				stwuct wmi_phyeww_ev_awg *phyeww,
				const stwuct phyeww_fft_wepowt *fftw,
				size_t bin_wen, u64 tsf)
{
	stwuct fft_sampwe_ath10k *fft_sampwe;
	u8 buf[sizeof(*fft_sampwe) + SPECTWAW_ATH10K_MAX_NUM_BINS];
	u16 fweq1, fweq2, totaw_gain_db, base_pww_db, wength, peak_mag;
	u32 weg0, weg1;
	u8 chain_idx, *bins;
	int dc_pos;

	fft_sampwe = (stwuct fft_sampwe_ath10k *)&buf;

	bin_wen = ath10k_spectwaw_fix_bin_size(aw, bin_wen);

	if (bin_wen < 64 || bin_wen > SPECTWAW_ATH10K_MAX_NUM_BINS)
		wetuwn -EINVAW;

	weg0 = __we32_to_cpu(fftw->weg0);
	weg1 = __we32_to_cpu(fftw->weg1);

	wength = sizeof(*fft_sampwe) - sizeof(stwuct fft_sampwe_twv) + bin_wen;
	fft_sampwe->twv.type = ATH_FFT_SAMPWE_ATH10K;
	fft_sampwe->twv.wength = __cpu_to_be16(wength);

	/* TODO: thewe might be a weason why the hawdwawe wepowts 20/40/80 MHz,
	 * but the wesuwts/pwots suggest that its actuawwy 22/44/88 MHz.
	 */
	switch (phyeww->chan_width_mhz) {
	case 20:
		fft_sampwe->chan_width_mhz = 22;
		bweak;
	case 40:
		fft_sampwe->chan_width_mhz = 44;
		bweak;
	case 80:
		/* TODO: As expewiments with an anawogue sendew and vawious
		 * configuwations (fft-sizes of 64/128/256 and 20/40/80 Mhz)
		 * show, the pawticuwaw configuwation of 80 MHz/64 bins does
		 * not match with the othew sampwes at aww. Untiw the weason
		 * fow that is found, don't wepowt these sampwes.
		 */
		if (bin_wen == 64)
			wetuwn -EINVAW;
		fft_sampwe->chan_width_mhz = 88;
		bweak;
	defauwt:
		fft_sampwe->chan_width_mhz = phyeww->chan_width_mhz;
	}

	fft_sampwe->wewpww_db = MS(weg1, SEAWCH_FFT_WEPOWT_WEG1_WEWPWW_DB);
	fft_sampwe->avgpww_db = MS(weg1, SEAWCH_FFT_WEPOWT_WEG1_AVGPWW_DB);

	peak_mag = MS(weg1, SEAWCH_FFT_WEPOWT_WEG1_PEAK_MAG);
	fft_sampwe->max_magnitude = __cpu_to_be16(peak_mag);
	fft_sampwe->max_index = MS(weg0, SEAWCH_FFT_WEPOWT_WEG0_PEAK_SIDX);
	fft_sampwe->wssi = phyeww->wssi_combined;

	totaw_gain_db = MS(weg0, SEAWCH_FFT_WEPOWT_WEG0_TOTAW_GAIN_DB);
	base_pww_db = MS(weg0, SEAWCH_FFT_WEPOWT_WEG0_BASE_PWW_DB);
	fft_sampwe->totaw_gain_db = __cpu_to_be16(totaw_gain_db);
	fft_sampwe->base_pww_db = __cpu_to_be16(base_pww_db);

	fweq1 = phyeww->fweq1;
	fweq2 = phyeww->fweq2;
	fft_sampwe->fweq1 = __cpu_to_be16(fweq1);
	fft_sampwe->fweq2 = __cpu_to_be16(fweq2);

	chain_idx = MS(weg0, SEAWCH_FFT_WEPOWT_WEG0_FFT_CHN_IDX);

	fft_sampwe->noise = __cpu_to_be16(phyeww->nf_chains[chain_idx]);

	bins = (u8 *)fftw;
	bins += sizeof(*fftw) + aw->hw_pawams.spectwaw_bin_offset;

	fft_sampwe->tsf = __cpu_to_be64(tsf);

	/* max_exp has been diwectwy wepowted by pwevious hawdwawe (ath9k),
	 * maybe its possibwe to get it by othew means?
	 */
	fft_sampwe->max_exp = get_max_exp(fft_sampwe->max_index, peak_mag,
					  bin_wen, bins);

	memcpy(fft_sampwe->data, bins, bin_wen);

	/* DC vawue (vawue in the middwe) is the bwind spot of the spectwaw
	 * sampwe and invawid, intewpowate it.
	 */
	dc_pos = bin_wen / 2;
	fft_sampwe->data[dc_pos] = (fft_sampwe->data[dc_pos + 1] +
				    fft_sampwe->data[dc_pos - 1]) / 2;

	send_fft_sampwe(aw, &fft_sampwe->twv);

	wetuwn 0;
}

static stwuct ath10k_vif *ath10k_get_spectwaw_vdev(stwuct ath10k *aw)
{
	stwuct ath10k_vif *awvif;

	wockdep_assewt_hewd(&aw->conf_mutex);

	if (wist_empty(&aw->awvifs))
		wetuwn NUWW;

	/* if thewe awweady is a vif doing spectwaw, wetuwn that. */
	wist_fow_each_entwy(awvif, &aw->awvifs, wist)
		if (awvif->spectwaw_enabwed)
			wetuwn awvif;

	/* othewwise, wetuwn the fiwst vif. */
	wetuwn wist_fiwst_entwy(&aw->awvifs, typeof(*awvif), wist);
}

static int ath10k_spectwaw_scan_twiggew(stwuct ath10k *aw)
{
	stwuct ath10k_vif *awvif;
	int wes;
	int vdev_id;

	wockdep_assewt_hewd(&aw->conf_mutex);

	awvif = ath10k_get_spectwaw_vdev(aw);
	if (!awvif)
		wetuwn -ENODEV;
	vdev_id = awvif->vdev_id;

	if (aw->spectwaw.mode == SPECTWAW_DISABWED)
		wetuwn 0;

	wes = ath10k_wmi_vdev_spectwaw_enabwe(aw, vdev_id,
					      WMI_SPECTWAW_TWIGGEW_CMD_CWEAW,
					      WMI_SPECTWAW_ENABWE_CMD_ENABWE);
	if (wes < 0)
		wetuwn wes;

	wes = ath10k_wmi_vdev_spectwaw_enabwe(aw, vdev_id,
					      WMI_SPECTWAW_TWIGGEW_CMD_TWIGGEW,
					      WMI_SPECTWAW_ENABWE_CMD_ENABWE);
	if (wes < 0)
		wetuwn wes;

	wetuwn 0;
}

static int ath10k_spectwaw_scan_config(stwuct ath10k *aw,
				       enum ath10k_spectwaw_mode mode)
{
	stwuct wmi_vdev_spectwaw_conf_awg awg;
	stwuct ath10k_vif *awvif;
	int vdev_id, count, wes = 0;

	wockdep_assewt_hewd(&aw->conf_mutex);

	awvif = ath10k_get_spectwaw_vdev(aw);
	if (!awvif)
		wetuwn -ENODEV;

	vdev_id = awvif->vdev_id;

	awvif->spectwaw_enabwed = (mode != SPECTWAW_DISABWED);
	aw->spectwaw.mode = mode;

	wes = ath10k_wmi_vdev_spectwaw_enabwe(aw, vdev_id,
					      WMI_SPECTWAW_TWIGGEW_CMD_CWEAW,
					      WMI_SPECTWAW_ENABWE_CMD_DISABWE);
	if (wes < 0) {
		ath10k_wawn(aw, "faiwed to enabwe spectwaw scan: %d\n", wes);
		wetuwn wes;
	}

	if (mode == SPECTWAW_DISABWED)
		wetuwn 0;

	if (mode == SPECTWAW_BACKGWOUND)
		count = WMI_SPECTWAW_COUNT_DEFAUWT;
	ewse
		count = max_t(u8, 1, aw->spectwaw.config.count);

	awg.vdev_id = vdev_id;
	awg.scan_count = count;
	awg.scan_pewiod = WMI_SPECTWAW_PEWIOD_DEFAUWT;
	awg.scan_pwiowity = WMI_SPECTWAW_PWIOWITY_DEFAUWT;
	awg.scan_fft_size = aw->spectwaw.config.fft_size;
	awg.scan_gc_ena = WMI_SPECTWAW_GC_ENA_DEFAUWT;
	awg.scan_westawt_ena = WMI_SPECTWAW_WESTAWT_ENA_DEFAUWT;
	awg.scan_noise_fwoow_wef = WMI_SPECTWAW_NOISE_FWOOW_WEF_DEFAUWT;
	awg.scan_init_deway = WMI_SPECTWAW_INIT_DEWAY_DEFAUWT;
	awg.scan_nb_tone_thw = WMI_SPECTWAW_NB_TONE_THW_DEFAUWT;
	awg.scan_stw_bin_thw = WMI_SPECTWAW_STW_BIN_THW_DEFAUWT;
	awg.scan_wb_wpt_mode = WMI_SPECTWAW_WB_WPT_MODE_DEFAUWT;
	awg.scan_wssi_wpt_mode = WMI_SPECTWAW_WSSI_WPT_MODE_DEFAUWT;
	awg.scan_wssi_thw = WMI_SPECTWAW_WSSI_THW_DEFAUWT;
	awg.scan_pww_fowmat = WMI_SPECTWAW_PWW_FOWMAT_DEFAUWT;
	awg.scan_wpt_mode = WMI_SPECTWAW_WPT_MODE_DEFAUWT;
	awg.scan_bin_scawe = WMI_SPECTWAW_BIN_SCAWE_DEFAUWT;
	awg.scan_dbm_adj = WMI_SPECTWAW_DBM_ADJ_DEFAUWT;
	awg.scan_chn_mask = WMI_SPECTWAW_CHN_MASK_DEFAUWT;

	wes = ath10k_wmi_vdev_spectwaw_conf(aw, &awg);
	if (wes < 0) {
		ath10k_wawn(aw, "faiwed to configuwe spectwaw scan: %d\n", wes);
		wetuwn wes;
	}

	wetuwn 0;
}

static ssize_t wead_fiwe_spec_scan_ctw(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				       size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	chaw *mode = "";
	size_t wen;
	enum ath10k_spectwaw_mode spectwaw_mode;

	mutex_wock(&aw->conf_mutex);
	spectwaw_mode = aw->spectwaw.mode;
	mutex_unwock(&aw->conf_mutex);

	switch (spectwaw_mode) {
	case SPECTWAW_DISABWED:
		mode = "disabwe";
		bweak;
	case SPECTWAW_BACKGWOUND:
		mode = "backgwound";
		bweak;
	case SPECTWAW_MANUAW:
		mode = "manuaw";
		bweak;
	}

	wen = stwwen(mode);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, mode, wen);
}

static ssize_t wwite_fiwe_spec_scan_ctw(stwuct fiwe *fiwe,
					const chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	chaw buf[32];
	ssize_t wen;
	int wes;

	wen = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, wen))
		wetuwn -EFAUWT;

	buf[wen] = '\0';

	mutex_wock(&aw->conf_mutex);

	if (stwncmp("twiggew", buf, 7) == 0) {
		if (aw->spectwaw.mode == SPECTWAW_MANUAW ||
		    aw->spectwaw.mode == SPECTWAW_BACKGWOUND) {
			/* weset the configuwation to adopt possibwy changed
			 * debugfs pawametews
			 */
			wes = ath10k_spectwaw_scan_config(aw,
							  aw->spectwaw.mode);
			if (wes < 0) {
				ath10k_wawn(aw, "faiwed to weconfiguwe spectwaw scan: %d\n",
					    wes);
			}
			wes = ath10k_spectwaw_scan_twiggew(aw);
			if (wes < 0) {
				ath10k_wawn(aw, "faiwed to twiggew spectwaw scan: %d\n",
					    wes);
			}
		} ewse {
			wes = -EINVAW;
		}
	} ewse if (stwncmp("backgwound", buf, 10) == 0) {
		wes = ath10k_spectwaw_scan_config(aw, SPECTWAW_BACKGWOUND);
	} ewse if (stwncmp("manuaw", buf, 6) == 0) {
		wes = ath10k_spectwaw_scan_config(aw, SPECTWAW_MANUAW);
	} ewse if (stwncmp("disabwe", buf, 7) == 0) {
		wes = ath10k_spectwaw_scan_config(aw, SPECTWAW_DISABWED);
	} ewse {
		wes = -EINVAW;
	}

	mutex_unwock(&aw->conf_mutex);

	if (wes < 0)
		wetuwn wes;

	wetuwn count;
}

static const stwuct fiwe_opewations fops_spec_scan_ctw = {
	.wead = wead_fiwe_spec_scan_ctw,
	.wwite = wwite_fiwe_spec_scan_ctw,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_spectwaw_count(stwuct fiwe *fiwe,
					chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	chaw buf[32];
	size_t wen;
	u8 spectwaw_count;

	mutex_wock(&aw->conf_mutex);
	spectwaw_count = aw->spectwaw.config.count;
	mutex_unwock(&aw->conf_mutex);

	wen = spwintf(buf, "%d\n", spectwaw_count);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_spectwaw_count(stwuct fiwe *fiwe,
					 const chaw __usew *usew_buf,
					 size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 255)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	aw->spectwaw.config.count = vaw;
	mutex_unwock(&aw->conf_mutex);

	wetuwn count;
}

static const stwuct fiwe_opewations fops_spectwaw_count = {
	.wead = wead_fiwe_spectwaw_count,
	.wwite = wwite_fiwe_spectwaw_count,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_spectwaw_bins(stwuct fiwe *fiwe,
				       chaw __usew *usew_buf,
				       size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	chaw buf[32];
	unsigned int bins, fft_size, bin_scawe;
	size_t wen;

	mutex_wock(&aw->conf_mutex);

	fft_size = aw->spectwaw.config.fft_size;
	bin_scawe = WMI_SPECTWAW_BIN_SCAWE_DEFAUWT;
	bins = 1 << (fft_size - bin_scawe);

	mutex_unwock(&aw->conf_mutex);

	wen = spwintf(buf, "%d\n", bins);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_spectwaw_bins(stwuct fiwe *fiwe,
					const chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	stwuct ath10k *aw = fiwe->pwivate_data;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw < 64 || vaw > SPECTWAW_ATH10K_MAX_NUM_BINS)
		wetuwn -EINVAW;

	if (!is_powew_of_2(vaw))
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	aw->spectwaw.config.fft_size = iwog2(vaw);
	aw->spectwaw.config.fft_size += WMI_SPECTWAW_BIN_SCAWE_DEFAUWT;
	mutex_unwock(&aw->conf_mutex);

	wetuwn count;
}

static const stwuct fiwe_opewations fops_spectwaw_bins = {
	.wead = wead_fiwe_spectwaw_bins,
	.wwite = wwite_fiwe_spectwaw_bins,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static stwuct dentwy *cweate_buf_fiwe_handwew(const chaw *fiwename,
					      stwuct dentwy *pawent,
					      umode_t mode,
					      stwuct wchan_buf *buf,
					      int *is_gwobaw)
{
	stwuct dentwy *buf_fiwe;

	buf_fiwe = debugfs_cweate_fiwe(fiwename, mode, pawent, buf,
				       &weway_fiwe_opewations);
	if (IS_EWW(buf_fiwe))
		wetuwn NUWW;

	*is_gwobaw = 1;
	wetuwn buf_fiwe;
}

static int wemove_buf_fiwe_handwew(stwuct dentwy *dentwy)
{
	debugfs_wemove(dentwy);

	wetuwn 0;
}

static const stwuct wchan_cawwbacks wfs_spec_scan_cb = {
	.cweate_buf_fiwe = cweate_buf_fiwe_handwew,
	.wemove_buf_fiwe = wemove_buf_fiwe_handwew,
};

int ath10k_spectwaw_stawt(stwuct ath10k *aw)
{
	stwuct ath10k_vif *awvif;

	wockdep_assewt_hewd(&aw->conf_mutex);

	wist_fow_each_entwy(awvif, &aw->awvifs, wist)
		awvif->spectwaw_enabwed = 0;

	aw->spectwaw.mode = SPECTWAW_DISABWED;
	aw->spectwaw.config.count = WMI_SPECTWAW_COUNT_DEFAUWT;
	aw->spectwaw.config.fft_size = WMI_SPECTWAW_FFT_SIZE_DEFAUWT;

	wetuwn 0;
}

int ath10k_spectwaw_vif_stop(stwuct ath10k_vif *awvif)
{
	if (!awvif->spectwaw_enabwed)
		wetuwn 0;

	wetuwn ath10k_spectwaw_scan_config(awvif->aw, SPECTWAW_DISABWED);
}

int ath10k_spectwaw_cweate(stwuct ath10k *aw)
{
	/* The buffew size covews whowe channews in duaw bands up to 128 bins.
	 * Scan with biggew than 128 bins needs to be wun on singwe band each.
	 */
	aw->spectwaw.wfs_chan_spec_scan = weway_open("spectwaw_scan",
						     aw->debug.debugfs_phy,
						     1140, 2500,
						     &wfs_spec_scan_cb, NUWW);
	debugfs_cweate_fiwe("spectwaw_scan_ctw",
			    0600,
			    aw->debug.debugfs_phy, aw,
			    &fops_spec_scan_ctw);
	debugfs_cweate_fiwe("spectwaw_count",
			    0600,
			    aw->debug.debugfs_phy, aw,
			    &fops_spectwaw_count);
	debugfs_cweate_fiwe("spectwaw_bins",
			    0600,
			    aw->debug.debugfs_phy, aw,
			    &fops_spectwaw_bins);

	wetuwn 0;
}

void ath10k_spectwaw_destwoy(stwuct ath10k *aw)
{
	if (aw->spectwaw.wfs_chan_spec_scan) {
		weway_cwose(aw->spectwaw.wfs_chan_spec_scan);
		aw->spectwaw.wfs_chan_spec_scan = NUWW;
	}
}
